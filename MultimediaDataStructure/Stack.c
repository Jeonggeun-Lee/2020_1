#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Bool{ false = 0, true = 1 };
typedef enum Bool Bool;

struct Node
{
	char data[20];
	struct Node *next;
};
typedef struct Node Node;

struct Multi_stack
{
	int n;
	int s;
	int all_el_num;
	Node *head_ptr;
	Node **barrier;
	int *cumul_num;
	int *sub_st_el_num;
	Node *null_node;
};
typedef struct Multi_stack Multi_stack;

void init_stack(Multi_stack *st,int n, int s);

void print_stack(Multi_stack st);
Node *create_node(int selected_st_number, int cumul_number);
void push(int selected_st_number, int cumulated_number, Multi_stack *st);
Node *pop(int selected_st_number, Multi_stack *st);

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	int s = atoi(argv[2]);
	Multi_stack st;
	init_stack(&st, n, s);
	print_stack(st);
	srand(time(NULL));
	int sel;
	int pp;
	int i;
	for(i=1; i<=s*3; ++i)
	{
		sel = rand()%n+1;
		pp = rand()%2+1;
		if(pp == 1) push(sel, st.cumul_num[sel],&st);
		else pop(sel, &st);
		print_stack(st);
	}

	return 0;
}

void init_stack(Multi_stack *st, int n, int s)
{
	int i;
	st->n = n;
	st->s = s;
	st->all_el_num = 0;
	st->head_ptr = NULL;
	st->barrier = (Node **)malloc(sizeof(Node *)*(n+1));
	for(i = 0; i<=n; ++i) st->barrier[i] = NULL;
	st->cumul_num = (int *)malloc(sizeof(int)*(n+1));
	for(i = 1; i<=n; ++i) st->cumul_num[i] = 0;
	st->sub_st_el_num = (int *)malloc(sizeof(int)*(n+1));
	for(i = 1; i<=n; ++i) st->sub_st_el_num[i] = 0;
	st->null_node = (Node *)malloc(sizeof(Node));
	strcpy(st->null_node->data,"\0");
	st->null_node->next = NULL;
}

void print_stack(Multi_stack st)
{
	int i;
	Node *it;

	printf("\n");
	printf("MULTIPLE STACK STRUCTURE: \n");
	if(st.all_el_num == 0)
	{
		for(i=1; i<=st.n; ++i)
			printf(" <-barrier_%d",i);
		printf("\n\n");
		return;
	}
	for(i = 1; i<=st.n; ++i)
		if(st.barrier[i] == NULL)
			printf(" <-barrier_%d",i);
	printf("\n");
	for(it = st.head_ptr; it != NULL; it = it->next)
	{
		printf("%s",it->data);
		for(i=1; i<=st.n; ++i) if(st.barrier[i] == it) printf(" <-barrier_%d",i);
		printf("\n");
	}
	printf("\n");
}

Node *create_node(int selected_st_number, int cumul_number)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	sprintf(new_node->data, "st%d_%d", selected_st_number, cumul_number);
	new_node->next = NULL;
	return new_node;
}

void push(int selected_st_number, int cumul_number, Multi_stack *st)
{
	printf("Try to push in substack %d\n",selected_st_number);
	if(st->all_el_num >= st->s)
	{
		printf("stack_overflow\n");
		return;
	}
	st->null_node->next = st->head_ptr;
	int i;
	for(i=0; i<=st->n; ++i)
		if(st->barrier[i] == NULL) st->barrier[i] = st->null_node;
	Node **selected_barrier = &(st->barrier[selected_st_number]);
	Node *prev_barrier = *(selected_barrier-1);
	Node *temp = prev_barrier->next;
	Node *new_node = create_node(selected_st_number, cumul_number+1);
	prev_barrier->next = new_node;
	new_node->next = temp;
	if(st->sub_st_el_num[selected_st_number]==0)
	{
		for(i=selected_st_number+1; i<=st->n; ++i)
			if(st->barrier[i] == st->barrier[selected_st_number]) st->barrier[i] = st->barrier[i]->next;
		st->barrier[selected_st_number] = st->barrier[selected_st_number]->next;
	}
	st->sub_st_el_num[selected_st_number]++;
	st->cumul_num[selected_st_number]++;
	st->all_el_num++;
	st->head_ptr = st->null_node->next;
	for(i=0; i<=st->n; ++i)
		if(st->barrier[i] == st->null_node)
			st->barrier[i] = NULL;
	st->null_node->next = NULL;
	printf("Succeeded to push in substack %d: ", selected_st_number);
	printf("%s\n",new_node->data);
}

Node *pop(int selected_st_number, Multi_stack *st)
{
	printf("Try to pop from substack %d\n",selected_st_number);
	if(st->sub_st_el_num[selected_st_number] == 0)
	{
		printf("stack_under_flow\n");
		return NULL;
	}
	st->null_node->next = st->head_ptr;
	int i;
	for(i=0; i<=st->n; ++i)
		if(st->barrier[i] == NULL) st->barrier[i] = st->null_node;
	Node **selected_barrier = &(st->barrier[selected_st_number]);
	Node *prev_barrier = *(selected_barrier-1);
	Node *temp = prev_barrier->next;
	if(st->sub_st_el_num[selected_st_number]==1)
		for(i=selected_st_number; i<=st->n; ++i)
			if(st->barrier[i] == temp) st->barrier[i] = prev_barrier;
	prev_barrier->next = temp->next;
	st->sub_st_el_num[selected_st_number]--;
	st->all_el_num--;
	st->head_ptr = st->null_node->next;
	for(i=0; i<=st->n; ++i)
		if(st->barrier[i] == st->null_node)
			st->barrier[i] = NULL;
	st->null_node->next = NULL;
	printf("Succeeded to pop from substack %d: ", selected_st_number);
	printf("%s\n",temp->data);
	return temp;
}
