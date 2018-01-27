#include<stdio.h>
#include"BTree.h"


int main() {
	BTree T = NULL;
	result r;
	int choice, k, i, m, n,j;

	do {
		choice = menu();


		if (choice >= 0 && choice <= 10) {
			system("cls");//把菜单清除
			switch (choice) {
			case 1:
				printf("请输入B树的阶数m:(3<=m<=20)\n");
				scanf_s("%d", &m);
				printf("请输入B树的初始化关键字个数:(0<=n<=10000)\n");
				scanf_s("%d", &n);
				CreatBTree(T, n, m);
				break;
			case 2:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					printf("请输入要查找的关键字：\n");
					scanf_s("%d", &k);
					SearchBTree(T, k, r);
					if (r.tag) {
						printf("该关键字的位置为该结点中第%d个关键字\n", r.i);
					}
					else {
						printf("该关键字不存在！\n");
					}
				}
				break;
			case 3:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					printf("请输入要插入的关键字k：\n");
					scanf_s("%d", &k);
					SearchBTree(T, k, r);
					InsertBTree(T, k, (&r)->pt, (&r)->i, m);
					printf("插入成功！\n");
				}
				break;
			case 4:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					printf("B树形状如下\n");
					ShowBTree(T, 8);
					printf("\n");
					printf("请输入要删除B树T上的关键字：\n");
					scanf_s("%d", &i);
					SearchBTree(T, i, r);
					if (r.tag == 1) {
						DeleteBTree(r.pt, r.i, m, T);
						printf("删除成功！\n");
					}
					else {
						printf("B树上暂无该关键字！删除失败\n");
					}
				}
				break;
			case 5:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					printf("此时的B树序列为：\n");
					PrintBTree(T);
					printf("\n");
				}
				break;
			case 6:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else
				{
					printf("B树形状如下\n");
					ShowBTree(T, 8);
				}
				break;
			case 7:
				j = 0;
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					CountBTreeNode(T, j);
					printf("有效结点的个数为：%d\n", j);
				}
				break;
			case 8:
				j = 0;
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					CountBTreeKey(T, j);
					printf("关键字的个数为：%d\n", j);
				}
				break;
			case 9:
				if (T == NULL)
					printf("目前的树为空,请先创建B树!\n");
				else {
					DestroyBTree(T);
					T = NULL;
					printf("销毁成功！\n");
				}
				break;
			default:;
			}
		}
	} while (choice > 0 && choice < 10);
	return 0;
}