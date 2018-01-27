#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define M 20//定义阶数最大值




typedef int KeyType;
typedef int Status;
typedef struct {  //记录的结构定义
	KeyType key;
	char data;
}Record;


typedef struct BTNode {        //B树结点类型定义
	int keynum;      //结点中关键字个数，即结点的大小
	KeyType key[M + 1]; //关键字，key[0]未用
	struct BTNode *parent; //双亲结点指针
	struct BTNode *ptr[M + 1];//孩子结点指针数组
	Record *recptr[M + 1];    //记录指针向量，0号单元未用
}BTNode, *BTree;  //B树结点和B树类型


typedef struct {
	BTree pt;  //指向找到的结点
	int i;  //1<=i<=m,在结点中的关键字位序
	int tag;  //1:查找成功，0:查找失败
}result, *resultPtr;  //B树的查找结果类型


//接口定义


void CreatBTree(BTree&T, int n, int m);
/*
初始条件:初始化关键字个数n大于等于0，B树的阶数m大于3小于等于20
操作结果:构建一颗阶数为m,含有n个关键字的B树
*/

void ShowBTree(BTree T, short  x);
/*
递归以凹入表形式显示B树T,每层的缩进量为x，初始缩进量为8
*/

void SearchBTree(BTree T, int k, result &r);
/*
初始条件:树T存在
操作结果:在m阶B数T上查找关键字k，返回p{pt,i,tag}
*/


void InsertBTree(BTree &T, int k, BTree q, int i, int m);
/*
初始条件:树T存在
操作结果:在B树T上结点p->pt的key[i]和key[i+1]之间插入关键字k
*/


void DeleteBTree(BTree p, int i, int m, BTree &T);
/*
初始条件:B树上p结点存在
操作结果:删除B树T上结点p->pt的关键字k
*/

void CountBTreeKey(BTree T, int &j);
/*
初始条件：树T存在
操作结果：计算关键字个数
*/

void CountBTreeNode(BTree T, int &j);
/*
初始条件：树T存在
操作结果：计算有效结点的个数
*/

void PrintBTree(BTree T);
/*
初始条件:树T存在
操作结果:中序遍历B树
*/


void DestroyBTree(BTree T);
/*
初始条件:树T存在
操作结果:销毁B树
*/


int menu();
/*
输出选择菜单
*/
