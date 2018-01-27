#include<stdio.h>
#include"BTree.h"


int main() {
	BTree T = NULL;
	result r;
	int choice, k, i, m, n,j;

	do {
		choice = menu();


		if (choice >= 0 && choice <= 10) {
			system("cls");//�Ѳ˵����
			switch (choice) {
			case 1:
				printf("������B���Ľ���m:(3<=m<=20)\n");
				scanf_s("%d", &m);
				printf("������B���ĳ�ʼ���ؼ��ָ���:(0<=n<=10000)\n");
				scanf_s("%d", &n);
				CreatBTree(T, n, m);
				break;
			case 2:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					printf("������Ҫ���ҵĹؼ��֣�\n");
					scanf_s("%d", &k);
					SearchBTree(T, k, r);
					if (r.tag) {
						printf("�ùؼ��ֵ�λ��Ϊ�ý���е�%d���ؼ���\n", r.i);
					}
					else {
						printf("�ùؼ��ֲ����ڣ�\n");
					}
				}
				break;
			case 3:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					printf("������Ҫ����Ĺؼ���k��\n");
					scanf_s("%d", &k);
					SearchBTree(T, k, r);
					InsertBTree(T, k, (&r)->pt, (&r)->i, m);
					printf("����ɹ���\n");
				}
				break;
			case 4:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					printf("B����״����\n");
					ShowBTree(T, 8);
					printf("\n");
					printf("������Ҫɾ��B��T�ϵĹؼ��֣�\n");
					scanf_s("%d", &i);
					SearchBTree(T, i, r);
					if (r.tag == 1) {
						DeleteBTree(r.pt, r.i, m, T);
						printf("ɾ���ɹ���\n");
					}
					else {
						printf("B�������޸ùؼ��֣�ɾ��ʧ��\n");
					}
				}
				break;
			case 5:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					printf("��ʱ��B������Ϊ��\n");
					PrintBTree(T);
					printf("\n");
				}
				break;
			case 6:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else
				{
					printf("B����״����\n");
					ShowBTree(T, 8);
				}
				break;
			case 7:
				j = 0;
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					CountBTreeNode(T, j);
					printf("��Ч���ĸ���Ϊ��%d\n", j);
				}
				break;
			case 8:
				j = 0;
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					CountBTreeKey(T, j);
					printf("�ؼ��ֵĸ���Ϊ��%d\n", j);
				}
				break;
			case 9:
				if (T == NULL)
					printf("Ŀǰ����Ϊ��,���ȴ���B��!\n");
				else {
					DestroyBTree(T);
					T = NULL;
					printf("���ٳɹ���\n");
				}
				break;
			default:;
			}
		}
	} while (choice > 0 && choice < 10);
	return 0;
}