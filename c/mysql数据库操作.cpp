#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main (int argc, char *argv[])
{
	MYSQL *conn_ptr;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row;
	char query[1024];
	int t,r;
	
	conn_ptr=mysql_init(NULL);
	if(!conn_ptr){
		fprintf(stderr, "mysql_init_failed/n");
		return EXIT_FAILURE;
	}

	conn_ptr = mysql_real_connect(conn_ptr,"localhost","root","123456","test",0,NULL,0);
	if( conn_ptr ){
		printf("Connection success\n");
	}else{
	   printf("Error connecting to database: %s\n", mysql_error(conn_ptr));
    }	
	
	mysql_query(conn_ptr, "insert into fcn(isp,iub,ise,ilf,pah)values(400,134,321,345,'test123')");
	//mysql_query(conn_ptr, "delete from pay where id = 201104010010");
	mysql_query(conn_ptr, "update fcn set pah='test_test' where isp = 100");

	sprintf(query, "select * from fcn");
	t=mysql_query(conn_ptr,query);
	
	if(t)
	{
		printf("Error making query:%s\n", mysql_error(conn_ptr));
	}
	else printf("Query made... \n");

	res=mysql_use_result(conn_ptr);



	unsigned int num_fields;
	unsigned int i;

	num_fields = mysql_num_fields(res);
	while ((row = mysql_fetch_row(res)))
	{
	   unsigned long *lengths;
	   lengths = mysql_fetch_lengths(res);
	   for(i = 0; i < num_fields; i++)
	   {
	       //printf("[%.*s] ", (int) lengths[i],row[i] ? row[i] : "NULL");	       
	       printf("%.*s  ", (int) lengths[i],row[i] ? row[i] : "NULL");
	   }
	   printf("\n");
	}
    mysql_close(conn_ptr);
    return 0;
}