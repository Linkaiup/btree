#include "BTree.h"


void CreatBTree(BTree &T, int n, int m) {//����һ�Ž���Ϊm,����n���ؼ��ֵ�B��(3<=m<=M,0<=n<=10000)
										 //����B��
	int i, j;
	resultPtr p = NULL;
	p = (result*)malloc(sizeof(result));
	srand((unsigned)time(NULL));
	if (n == 0)
		printf("�ѳɹ���ʼ��һ�ÿ�����\n");
	else {
		for (j = 0; j < n; j++) {
			i = rand() % 1000;//���������i
			SearchBTree(T, i, *p);//����i����λ��
			InsertBTree(T, i, p->pt, p->i, m);  //���в���
		}
		printf("����B���ɹ���\n");
	}
}

void CountBTreeKey(BTree T, int &j) {
	//����ؼ��ָ���  
	int i = 1;
	if (NULL != T) //��Ϊ�ս��ʱֹͣ�ý������
	{
		for (; i <= T->keynum; i++)
		{
			CountBTreeKey(T->ptr[i - 1], j);    //�ݹ�����������ӽ��
			j++;                              //ͳ�ƹؼ��ָ���
		}
		CountBTreeKey(T->ptr[i - 1], j);  //�������һ�����ǽ��
	}
}


void CountBTreeNode(BTree T, int &j) {
	//������Ч������  
	int i = 1;
	if (NULL != T) //��Ϊ�ս��ʱֹͣ�ý������
	{
		for (; i <= T->keynum; i++)
		{
			CountBTreeNode(T->ptr[i - 1], j);    //�ݹ�����������ӽ��
		}
		CountBTreeNode(T->ptr[i - 1], j);  //�������һ�����ǽ��
		j++;                //ͳ�ƽ�����
	}
}


void PrintBTree(BTree T) {
	//�������B��
	int i = 1;
	if (NULL != T) {
		for (; i <= T->keynum; i++) {
			PrintBTree(T->ptr[i - 1]);
			printf("%d  ", T->key[i]);
		}
		PrintBTree(T->ptr[i - 1]);
	}
}


int Search(BTree p, int k) {
	int i = 1;
	while (i <= p->keynum&&k > p->key[i])
		i++;
	return i;
}

void  ShowBTree(BTree T, short  x)
// �ݹ��԰������ʽ��ʾB��T,ÿ���������Ϊx����ʼ������Ϊ8  
{
	if (!T) return;
	int     i;
	printf("\n");
	for (i = 0; i <= x; i++) putchar(' ');           // ����x  
	for (i = 1; i <= T->keynum; i++)                //�����ǰ�������йؼ���
	{
		printf("%d,", T->key[i]);
	}
	for (i = 0; i <= T->keynum; i++)              // �ݹ���ʾ�������ؼ���  
		ShowBTree(T->ptr[i], x + 7);
}


void SearchBTree(BTree T, int k, result &r) {
	//��m��B��T�ϲ��ҹؼ���k������(pt,i,tag)
	//�����ҳɹ���������ֵtag=1,ָ��pt���½���е�i���ؼ��ֵ���k;����
	//����ֵtag=0������k�Ĺؼ��ּ�¼Ӧ������ָ��pt��ָ����е�i-1���͵�i���ؼ��ּ�
	int i = 0, found = 0;
	BTree p = T, q = NULL;
	while (p != NULL && 0 == found) {
		i = Search(p, k);//��p->key[1..keynum]�в���p->key[i-1]<k<=p->p->key[i]
		if (i > 0 && p->key[i] == k)
			found = 1;//�ҵ�����ؼ���
		else {
			q = p;
			p = p->ptr[i - 1];
		}
	}
	if (1 == found) {//���ҳɹ�
		r.pt = p;
		r.i = i;
		r.tag = 1;
	}
	else {//���Ҳ��ɹ�������key�Ĳ���λ��i
		r.pt = q;
		r.i = i;
		r.tag = 0;
	}
}


void split(BTree &q, int s, BTree &ap) {
	//��q�����ѳ�������㣬ǰһ�뱣������һ�������½��ap
	int i, j, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//�����½��ap
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1, j = 1; i <= n; i++, j++) {//��һ������ap���
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= n - s; i++) {
		if (ap->ptr[i])
			ap->ptr[i]->parent = ap;//��ap���к��ӽ��ָ��ap
	}
	q->keynum = s - 1;//q����ǰһ�뱣�����޸�keynum
}


void newroot(BTree &T, BTree p, int x, BTree ap) {//�����µĸ����
	T = (BTNode*)malloc(sizeof(BTNode));
	T->keynum = 1;
	T->ptr[0] = p;
	T->ptr[1] = ap;
	T->key[1] = x;
	if (p != NULL) p->parent = T;
	if (ap != NULL) ap->parent = T;
	T->parent = NULL;//�¸���˫���ǿ�ָ��
}


void Insert(BTree &q, int i, int x, BTree ap) {//x��ap�ֱ�嵽q->key[i]��q->ptr[i]
	int j, n = q->keynum;
	for (j = n; j >= i; j--) {
		q->key[j + 1] = q->key[j];//�ؼ���ָ�������һλ
		q->ptr[j + 1] = q->ptr[j];//���ӽ��ָ�������һλ
	}
	q->key[i] = x;//��ֵ
	q->ptr[i] = ap;
	if (ap != NULL) ap->parent = q;
	q->keynum++;//�ؼ�����+1
}


void InsertBTree(BTree &T, int k, BTree q, int i, int m) {
	//��B��T��q����key[i-1]��key[i]֮�����ؼ���k
	//�����������,����˫��ָ����б�Ҫ�Ľ����ѵ���,ʹT����m�׵�B��
	int x, s, finished = 0, neednewroot = 0;
	BTree ap;
	if (NULL == q)//qΪ�գ����½������
		newroot(T, NULL, k, NULL);
	else {
		x = k;
		ap = NULL;
		while (0 == neednewroot && 0 == finished) {
			Insert(q, i, x, ap);//key��ap�ֱ�嵽q->key[i]��q->ptr[i]
			if (q->keynum < m) finished = 1;//�������
			else {//����q���
				s = (m + 1) / 2;
				split(q, s, ap);
				x = q->key[s];
				if (q->parent != NULL) {
					q = q->parent;
					i = Search(q, x);//��˫�׽���в���x�Ĳ���λ��
				}
				else neednewroot = 1;
			}
		}//while
		if (1 == neednewroot)//T�ǿ������߸�����ѷ���Ϊq��ap���
			newroot(T, q, x, ap);//���ɺ���Ϣ(q,x,ap)���µĸ����T
	}
}


void Successor(BTree &p, int i) {//�ɺ�����²���ն˽�����С�ؼ��ִ������йؼ���key[i]��
	BTNode *temp;
	temp = p->ptr[i];
	for (; NULL != temp->ptr[0]; temp = temp->ptr[0]);//�ҳ��ؼ��ֵĺ��
	p->key[i] = temp->key[1];
	p = temp;
}


void Remove(BTree &p, int i) {   //�ӽ��p��ɾ��key[i]
	int j;
	int n = p->keynum;
	for (j = i; j < n; j++) {  //�ؼ�������
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;
}


void Restore(BTree &p, int i, int m, BTree &T) {//����B��
	int j;
	BTree ap = p->parent;
	BTree lc, rc, pr;
	int finished = 0, r = 0;
	while (0 == finished) {
		r = 0;
		while (ap->ptr[r] != p)//ȷ��p��ap������λ��
			r++;
		if (r == 0) {
			r++;
			lc = NULL;
			rc = ap->ptr[r];
		}
		else if (r == ap->keynum) {
			rc = NULL;
			lc = ap->ptr[r - 1];
		}
		else {
			lc = ap->ptr[r - 1];
			rc = ap->ptr[r + 1];
		}
		if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2)) {//�����ֵܽ�ؼ���
			p->keynum++;
			for (j = p->keynum; j > 1; j--) {//���ؼ�������
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];//���ײ��뵽���
			p->ptr[1] = p->ptr[0];
			p->ptr[0] = lc->ptr[lc->keynum];
			if (NULL != p->ptr[0])//�޸�p�е���Ů�ĸ����Ϊp
				p->ptr[0]->parent = p;
			ap->key[r] = lc->key[lc->keynum];//���ֵ����Ƶ�����λ��
			lc->keynum--;
			finished = 1;
			break;
		}
		else if (ap->keynum > r&&rc != NULL && (rc->keynum > (m - 1) / 2)) {
			p->keynum++;
			p->key[p->keynum] = ap->key[r];//���ײ��뵽���
			p->ptr[p->keynum] = rc->ptr[0];
			if (NULL != p->ptr[p->keynum]) {//�޸�p�е���Ů�ĸ����Ϊp
				p->ptr[p->keynum]->parent = p;
			}
			ap->key[r] = rc->key[1];//���ֵ����Ƶ�����λ��
			rc->ptr[0] = rc->ptr[1];
			for (j = 1; j < rc->keynum; j++) {//���ֵܽ��ؼ�������
				rc->key[j] = rc->key[j + 1];
				rc->ptr[j] = rc->ptr[j + 1];
			}
			rc->keynum--;
			finished = 1;
			break;
		}
		r = 0;
		while (ap->ptr[r] != p) r++;//����ȷ��p��ap������λ��
		if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2)) {//�����ֵܺϲ�
			lc = ap->ptr[r - 1];
			p->keynum++;
			for (j = p->keynum; j > 1; j--) {//��p���ؼ��ֺ�ָ������1λ
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];//�����Ĺؼ�����p�ϲ�
			p->ptr[1] = p->ptr[0];//�����ֵ�����һ��ָ��
			ap->ptr[r + 1] = lc;
			for (j = 1; j <= lc->keynum + p->keynum; j++) {//�����p�йؼ����Ƶ�p���ֵ���
				lc->key[lc->keynum + j] = p->key[j];
				lc->ptr[lc->keynum + j] = p->ptr[j];
			}
			if (p->ptr[0]) {//�޸�p�е���Ů�ĸ����Ϊlc
				for (j = 1; j <= p->keynum; j++) {
					p->ptr[p->keynum + j]->parent = lc;
				}
			}
			lc->keynum = lc->keynum + p->keynum;//�ϲ���Ĺؼ��ָ���
			ap->keynum--;
			pr = p;
			free(pr);//�ͷ�p���ռ�
			pr = NULL;
			p = lc;
		}
		else {//�����ֵܺϲ�
			rc = ap->ptr[r + 1];
			if (r == 0) r++;
			p->keynum++;
			p->key[p->keynum] = ap->key[r];//�����Ĺؼ�����p�ϲ�
			p->ptr[p->keynum] = rc->ptr[0];//�����ֵ�����һ��ָ��
			rc->keynum = p->keynum + rc->keynum;//�ϲ���ؼ��ֵĸ���
			ap->ptr[r - 1] = rc;
			for (j = 1; j <= (rc->keynum - p->keynum); j++) {//��p���ֵܵĹؼ��ֺ�ָ������
				rc->key[p->keynum + j] = rc->key[j];
				rc->ptr[p->keynum + j] = rc->ptr[j];
			}
			for (j = 1; j <= p->keynum; j++) {//�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ���
				rc->key[j] = p->key[j];
				rc->ptr[j] = p->ptr[j];
			}
			rc->ptr[0] = p->ptr[0];
			if (p->ptr[0]) {//�޸�p�е���Ů�ĸ����Ϊrc
				for (j = 1; j <= p->keynum; j++) {
					p->ptr[p->keynum + j]->parent = rc;
				}
			}
			for (j = r; j < ap->keynum; j++) {//��������йؼ��ֺ�ָ������
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;//�����Ĺؼ��ָ�����1
			pr = p;
			free(pr);//�ͷ�p���ռ�
			pr = NULL;
			p = rc;
		}
		ap = ap->parent;
		if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap&&p->parent->keynum > 0)) {
			finished = 1;
		}
		else if (NULL == ap) {//����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
			pr = T;
			T = p;//���������
			free(pr);
			pr = NULL;
			finished = 1;
		}
		p = p->parent;
	}
}


void DeleteBTree(BTree p, int i, int m, BTree &T) {
	//ɾ��B����p����i���ؼ���
	if (p->ptr[i - 1] != NULL) {
		Successor(p, i);         //���������²���ն˽��
		DeleteBTree(p, 1, m, T);      //�ɺ�����²���ն˽�����С�ؼ��ִ�����
	}
	else {//�������²���ն˽��
		Remove(p, i);  //�ӽ��p��ɾ��key[i]
		if (p->keynum < (m - 1) / 2)  //ɾ����ؼ��ָ���С��(m-1)/2
			Restore(p, i, m, T); //����B��
	}
}


void DestroyBTree(BTree T) {
	int i = 1;
	if (NULL != T) {
		for (; i <= T->keynum; i++) {
			DestroyBTree(T->ptr[i - 1]);
		}
		free(T);
	}
}


int menu() {//�˵�
	int choice;
	printf("\n\n\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t _____________���ȴ���B���ٽ��в�����__________\n");
	printf("\t\t\t|                  B�����Խ���                 |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   1.����B��            2.B�����Ĳ���       |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   3.B�����Ĳ���      4.B������ɾ��       |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   5.B���ı���          6.B�������           |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   7.B���Ľ����Ŀ      8.B���Ĺؼ�����       |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   9.B���Ĵݻ�		   0.�˳�				 |\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|              16���繤��(4)��                 |\n");
	printf("\t\t\t|                 3116005057                   |\n");
	printf("\t\t\t|                    �ֿ�                      |\n");
	printf("\t\t\t|********************S**************************|\n");
	do {
		printf("\t\t\t��ѡ���ܣ�����1-9����һ�����֣�:");
		scanf_s("%d", &choice);
	} while (choice<0 || choice>9);//����Ƿ�����
	return choice;
}