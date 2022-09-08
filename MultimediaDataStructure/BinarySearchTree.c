/*
STRUCT DESCRIPTION

/(Root)
  r(right child of Root)
  |r(right child of right child of Root)
  |L(left child of right child of Root)
  L(left child of Root)
   r(right child of left child of Root)
   L(left child of left child of Root)

If a node is NULL, it's position can be filled with NULL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
	char *key;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

struct BST{
	Node *root;
	int el_num;
};
typedef struct BST BST;

Node *gen_node(const char *key);
void init_BST(BST *t);
void locate(BST *,int, Node *, char ***, int *, int, int, int);
void show(BST t);
Node *search(BST *t, const char *key);
Node *parent_node_by_key(BST *t, const char *key);
Node *parent_node(BST *, Node *);
void insert(BST *t, const char *key);
void delete(BST *t, const char *key);
int height(BST t);
Node *max_left(Node *);
void menu();

int main()
{
	BST t;
	init_BST(&t);
	char input[100];
	char ch;
	char str[100];
	while(1){
		menu();
		printf(">");
		fgets(input,100,stdin);
		sscanf(input,"%c %s",&ch,str);
		if(ch == 'I') insert(&t,str);
		else if(ch == 'S')
		{
			if(search(&t, str)!=NULL)printf("%s exists in tree\n",str);
			else printf("%s does not exist in tree\n",str);
		}
		else if(ch == 'D') delete(&t, str);
		else if(ch == 'Q')
		{
			printf("Quit program. Bye.\n");
			break;
		}
		else continue;
		show(t);
	}
	return 0;
}

Node *gen_node(const char *key)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	if(key == NULL)new_node->key = NULL;
	else
	{
		new_node->key = (char *)malloc( sizeof(char)*(strlen(key)+1) );
		strcpy(new_node->key, key);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

void init_BST(BST *t)
{
	t->root = NULL;
	t->el_num = 0;
}

void DFS(Node *subroot, int *global_h, int local_h)
{
	if(subroot == NULL) return;
	local_h++;
	if(local_h>*global_h) *global_h = local_h;
	DFS(subroot->left, global_h, local_h);
	DFS(subroot->right, global_h, local_h);
}
int height(BST t)
{
	int global_h = -1;
	int local_h = -1;
	DFS(t.root, &global_h, local_h);
	return global_h;
}
void locate(BST *t, int is_right_child, Node *cur_node, char ***canvas, int *node_num, int height, int row, int column)
{
	if(*node_num >= row-1) return;
	if(height >= column-1) return;
	(*node_num)++;
	height++;
	
	if(cur_node == NULL)
	{
		canvas[*node_num][height] = (char *)malloc(7);
		if(is_right_child) strcpy(canvas[*node_num][height],"r NULL");
		else strcpy(canvas[*node_num][height],"L NULL");
		return;
	}
	
	else
	{
		canvas[*node_num][height] = (char *)malloc( strlen(cur_node->key)+4 );
		if(is_right_child == 1) strcpy(canvas[*node_num][height],"r");
		else if(is_right_child== 0)strcpy(canvas[*node_num][height],"L");
		else strcpy(canvas[*node_num][height],"/");
		strcat(canvas[*node_num][height],"(");
		strcat(canvas[*node_num][height],cur_node->key);
		strcat(canvas[*node_num][height],")");
		locate(t, 1,cur_node->right, canvas, node_num, height, row, column);
		locate(t, 0,cur_node->left, canvas, node_num, height, row, column);
	}
}
void show(BST t)
{
	if(t.root==NULL)
	{
		printf("BINARY SEARCH TREE HAS NO ELEMENT\n");
		return;
	}
	printf("==========STRUCT OF BINARY SEARCH TREE==========\n");
	int i,j;
	int row, column;
	row = 1;
	int tree_height = height(t);
	for(i=0; i<=tree_height; i++) row *= 2;
	row--;
	column = tree_height+1;
	char ***canvas = (char ***)malloc(sizeof(char **)*row);
	for(i=0; i<row; i++)
		canvas[i] = (char **)malloc(sizeof(char *)*column);
	for(i=0; i<row; i++)
		for(j=0; j< column; j++)
			canvas[i][j] = NULL;
	int node_num = -1;
	int height = -1;
	locate(&t,-1, t.root, canvas, &node_num, height, row, column);
	for(j=0; j<column; j++)
	{
		for(i=1; i<row; i++)
		{
			if(canvas[i][j] == NULL)
			{
				if(canvas[i-1][j] != NULL)
				{
					if(canvas[i-1][j][0] == 'r' || canvas[i-1][j][0] == '|')
					{
						int k;
						int to_bottom = 0;
						for(k=i; k<row; k++) if(canvas[k][j] != NULL && canvas[k][j][0] == 'L') to_bottom = 1;
						if(to_bottom)
						{
							canvas[i][j] = (char *)malloc(2);
							strcpy(canvas[i][j],"|");
						}
					}
				}
			}
		}
	}
	for(i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			printf(" ");
			if(canvas[i][j] != NULL)
			{
				printf("%s",canvas[i][j]);
			}
			else printf(" ");
		}
		printf("\n");	
	}
	printf("===============END OF THE STRUCT================\n");
}
	
Node *search(BST *t, const char *key)
{
	Node *temp;
	temp = t->root;
	while(temp !=NULL && strcmp(key,temp->key) != 0)
	{
		if(strcmp(key,temp->key)<0) temp = temp->left;
		else temp = temp->right;
	}
	return temp;
}

Node *parent_node_by_key(BST *t,const char *key)
{
	Node *parent=NULL;
	Node *temp = t->root;
	while(temp != NULL)
	{
		parent = temp;
		if(strcmp(key,temp->key)<0)temp = temp->left;
		else temp = temp->right;
	}
	return parent;
}
Node *parent_node(BST *t, Node *child)
{
	Node *parent=NULL;
	Node *temp = t->root;
	while(temp != NULL && temp != child)
	{
		parent = temp;
		if(strcmp(child->key,temp->key)<0)temp = temp->left;
		else temp = temp->right;
	}
	return parent;
}

void insert(BST *t, const char *key)
{
	if(search(t, key)!=NULL)
	{
		printf("Already exist element. Cannot insert.\n");
		return;
	}
	t->el_num++;
	Node *new_node = gen_node(key);
	if(t->root==NULL)
	{
		t->root = new_node;
		return;
	}
	Node *parent = parent_node_by_key(t, key);
	if(strcmp(key, parent->key)<0) parent->left = new_node;
	else parent->right = new_node;
}

Node *max_left(Node *subroot)
{
	Node *temp = subroot->left;
	while(temp->right != NULL)
		temp = temp->right;
	return temp;
}

void delete(BST *t, const char *key)
{
	Node *target = search(t, key);
	Node *max_l;
	Node *max_l_parent;
	Node *left;
	Node *right;

	if(target == NULL)
	{
		printf("Not exist element. Cannot delete.\n");
		return;
	}
	t->el_num--;
	if(target == t->root)
	{
		if(target->left==NULL)
		{
			t->root = target->right;
			return;
		}
		max_l = max_left(target);
		max_l_parent = parent_node(t,max_l);
		if(max_l_parent == target)
		{
			t->root = max_l;
			max_l->right = target->right;
			return;
		}
		max_l_parent->right = max_l->left;
		left = target->left;
		right = target->right;
		t->root = max_l;
		max_l->left = left;
		max_l->right = right;
	}
	else
	{
		Node *parent = parent_node(t,target);
		Node **lr;
		if(target == parent->left) lr = &(parent->left);
		else lr = &(parent->right);
		if(target->left == NULL)
		{
			*(lr) = target->right;
			return;
		}
		max_l = max_left(target);
		max_l_parent = parent_node(t, max_l);
		if(max_l_parent == target)
		{
			*(lr) = max_l;
			max_l->right = target->right;
			return;
		}
		max_l_parent->right = max_l->left;
		left = target->left;
		right = target->right;
		*(lr) = max_l;
		max_l->left = left;
		max_l->right = right;
	}
}

void menu()
{
	printf("\n");
	printf("Insert: I string\n");
	printf("Search: S string\n");
	printf("Delete: D string\n");
	printf("Quit: Q\n");
	printf("\n");
}
