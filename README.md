# 数据结构之 B 树的 C 语言实现

### 基本操作：

CreatBTree(&T, n, m); 

​	初始条件：初始化关键字个数n大于等于0，B树的阶数m大于3小于等于20。 

​	操作结果：构建一棵阶数为m，含有n个关键字的B树。

SearchBTree(T, k, &p);

​	初始条件：树T存在。 

​	操作结果：在m阶B树t上查找关键字k，返回(pt,i,tag) 。

Split(BTree &q,int s, BTree &ap)；

​	初始条件：结点q存在 

​	操作结果：将q结点分裂成两个结点，前一半保留，后一半移入新结点ap

Newroot(BTree&T, BTree p, int x, BTree ap)

​	操作结果：生成新的根结点

InsertBTree(&T, k, p->pt, p->i, m); 

​	初始条件：树T存在，p->pt指向T中某个结点 

​	操作结果：在B树T上结点p->pt的key[i]和key[i+1]之间插入关键字k

Successor(BTree&p, int i)

​	初始条件：结点p存在 ，子树A[i]存在

​	操作结果：在A[i]子树中找出最下层非终端结点的最小关键字代替结点中关键字key[i]。

Restore(BTree&p, int i, int m, BTree &T)；

​	初始条件：结点p存在 

​	操作结果：调整B树 

PrintBTree(T); 

​	初始条件：树T存在

​	操作结果：中序遍历B树 

CountBTreeKey(BTreeT,int &j)

​	初始条件：树T存在

​	操作结果：计算关键字个数

CountBTreeNode(BTreeT,int &j)

​	初始条件：树T存在

​	操作结果：计算有效结点的个数

DeleteBTree(p->pt, p->i, m, T); 

​	初始条件：树T存在，p->pt指向T中某个结点

​	操作结果：删除B树T上结点p->pt的关键字k
