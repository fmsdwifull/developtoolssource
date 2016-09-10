#ifndef INOTIFY_H
#define INOTIFY_H


#define MAX_CHANNEL  100
#define DATENUM 50


typedef struct{
	int secs;
	char name[50];
}_find3f;

typedef struct{
	int date_wd;
	char datefile2[3][50];
}_hashwd2;

typedef struct{
    FILE *fp; //the file which is  opening file
    int  wdid;//the wd which is inotifying channel
    char channel[20];
    _hashwd2 hashwd2;
}_hash;

typedef struct{
    int id[3];//the wd which is inotify datafiles
    char channel[20];
    char datefile[3][20];

}_hashwd;

typedef struct elem{
	int sec;
	char filename[50]; 
}Elem;



typedef struct{
    int  have_data;
    char channel_text[30];
	char filedate_text[30];
}_tx;


#endif