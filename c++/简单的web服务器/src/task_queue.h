/**************************************************************
* Copyright (c) 2012,surfing
* All rights reserved.
* Filename��task_queue.h
* Description���������������ı����ͷ���
***************************************************************/
/**************************************************************
* Version��1.0.0
* Original_Author��chengzhip
* Date��2013-05-14
* Modified_Author��
* Modified_Description��
* Modified_Date: 
***************************************************************/

#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_


extern "C"
{
	#include <stdlib.h>
}
#include <iostream>

//using namespace std;



namespace baselib
{
template <typename T>

class queue
{
public:
  queue(int init = 10);
  bool is_empty() const;//�ж϶����Ƿ�Ϊ��
  void queue_trav() const;//����ѭ������
  int get_queue_len() const;//���ض�����Ԫ�ظ���

  bool en_queue(T e);
  bool de_queue();

private:
  int size;//��������洢�ռ䣬��Ԫ��Ϊ��λ
  int front;//����ͷָ��
  int rear;//����βָ��
  T *base;//�洢�ռ��ַ
};

template <typename T>
queue<T>::queue(int init)
{
  size = init;//��ʼ��С
  base = new T[size];
  if(!base)
  	  exit(1);//�洢����ʧ��
  front = rear = 0;//��ջ��Ԫ�ظ���
}

//��ȡ���г���
template <typename T>
int queue<T>::get_queue_len() const
{
  return ((rear-front+size)%size);
}

//���б���
template <typename T>
void queue<T>::queue_trav() const
{
  int length = (rear-front+size)%size;
  std::cout<<"from end to start��"<<std::endl;
  while(length--)
  { 
    std::cout<<base[front+length]<<" ";
  }
  std::cout<<std::endl;
}

//���
template <typename T>
bool queue<T>::en_queue(T e)
{
  if((rear+1)%size==front)
  {//������
   std::cout<<"queue is full!"<<std::endl;
     return false;
  }
  else
  {
    base[rear] = e;
    rear = (rear+1)%size;
    return true;
  }
}

template <typename T>
bool queue<T>::de_queue()
{//���п�
  if(front==rear)
  {
    return false;
  }
  front = (front+1)%size;
  return true;
}
}

#endif
