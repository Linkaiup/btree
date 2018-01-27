#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define M 20//����������ֵ




typedef int KeyType;
typedef int Status;
typedef struct {  //��¼�Ľṹ����
	KeyType key;
	char data;
}Record;


typedef struct BTNode {        //B��������Ͷ���
	int keynum;      //����йؼ��ָ����������Ĵ�С
	KeyType key[M + 1]; //�ؼ��֣�key[0]δ��
	struct BTNode *parent; //˫�׽��ָ��
	struct BTNode *ptr[M + 1];//���ӽ��ָ������
	Record *recptr[M + 1];    //��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;  //B������B������


typedef struct {
	BTree pt;  //ָ���ҵ��Ľ��
	int i;  //1<=i<=m,�ڽ���еĹؼ���λ��
	int tag;  //1:���ҳɹ���0:����ʧ��
}result, *resultPtr;  //B���Ĳ��ҽ������


//�ӿڶ���


void CreatBTree(BTree&T, int n, int m);
/*
��ʼ����:��ʼ���ؼ��ָ���n���ڵ���0��B���Ľ���m����3С�ڵ���20
�������:����һ�Ž���Ϊm,����n���ؼ��ֵ�B��
*/

void ShowBTree(BTree T, short  x);
/*
�ݹ��԰������ʽ��ʾB��T,ÿ���������Ϊx����ʼ������Ϊ8
*/

void SearchBTree(BTree T, int k, result &r);
/*
��ʼ����:��T����
�������:��m��B��T�ϲ��ҹؼ���k������p{pt,i,tag}
*/


void InsertBTree(BTree &T, int k, BTree q, int i, int m);
/*
��ʼ����:��T����
�������:��B��T�Ͻ��p->pt��key[i]��key[i+1]֮�����ؼ���k
*/


void DeleteBTree(BTree p, int i, int m, BTree &T);
/*
��ʼ����:B����p������
�������:ɾ��B��T�Ͻ��p->pt�Ĺؼ���k
*/

void CountBTreeKey(BTree T, int &j);
/*
��ʼ��������T����
�������������ؼ��ָ���
*/

void CountBTreeNode(BTree T, int &j);
/*
��ʼ��������T����
���������������Ч���ĸ���
*/

void PrintBTree(BTree T);
/*
��ʼ����:��T����
�������:�������B��
*/


void DestroyBTree(BTree T);
/*
��ʼ����:��T����
�������:����B��
*/


int menu();
/*
���ѡ��˵�
*/
