//DoublyCircularLinkedList.c
//멀티미디어공학과 2017113547 이정근

//노드의 개수를 실행시 인수로 입력받는다
//노드를 생성한다

//랜덤 시드를 설정한다

////가위바위보 게임을 한다
//랜덤 값을 받는다
//사용자가 값을 입력한다
//값을 비교한다
//승패를 결정한다

////*computer_ptr를 이동한다
//컴퓨터가 이기면 win++ 지면 lose++
//win>=3이면 win=0으로 변경하고 현재 노드 오른쪽에 노드를 삽입한다
//lose>=3이면 현재 노드를 삭제하고 *computer_ptr을 왼쪽으로 이동한다
//컴퓨터가 이기면 오른쪽으로 이동한다

////전체 노드의 구조를 화면에 출력한다
//-노드 구조 시작-
//노드 하나의 구조 Win:n/Lose:m/Computer
//노드1
//노드2
//...
//-노드 구조 끝-

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

void print_arg_err();

typedef struct node
{
	struct node *left;
	int win;
	int lose;
	struct node *right;
} Node;

Node *gen_list(int);
enum Win_lose{ LOSE=0, DRAW, WIN };
typedef enum Win_lose Win_lose;
enum RSP{ ROCK=1, SCISSORS, PAPER };
typedef enum RSP RSP;
Win_lose RSP_game(RSP x, RSP y);
int choice();
void insert_node(Node *);
void delete_node(Node *);
Node *move(Node *computer_ptr, RSP result, Node **head_ptr);
void print_list(Node *, Node *);

int main(int argc, char *argv[])
{
	if( argc != 2 || atoi(argv[1])==0 )
	{
		print_arg_err();
		return 1;
	}

	int node_num = atoi(argv[1]);
	
	Node *head = gen_list(node_num);
	Node *computer_ptr = head;
	
	print_list(head, computer_ptr);
	srand(time(NULL));
	
	int c;
	while(1)
	{
		c = choice();
		if(c == 4) break;
		else computer_ptr = move(computer_ptr, c,&head);
		print_list(head, computer_ptr);
		
		if(head == NULL)
		{
			printf("더이상 노드가 없습니다. 프로그램을 끝냅니다.\n");
			break;
		}
	}
	return 0;
}
void print_arg_err()
{
	printf("Argument Error\n");
	printf("Argument Description: execution_file_name initial_node_number(>=1)\n");
}
Node *gen_list(int node_num)
{
	Node *head;
	head = (Node *)malloc(sizeof(Node));
	head->right = head;
	head->left = head;
	int i;
	for(i=2; i<=node_num; ++i) insert_node(head);
	return head;
}
Win_lose RSP_game(RSP x, RSP y)
{
	if(x == y) return DRAW;
	if(x == ROCK)
	{
		if(y == SCISSORS) return WIN;
		else return LOSE;
	}
	else if(x == SCISSORS)
	{
		if(y == PAPER) return WIN;
		else return LOSE;
	}
	else
	{
		if(y == ROCK) return WIN;
		else return LOSE;
	}
}

int choice()
{
	RSP com;
	int user;
	Win_lose result;
	while(1)
	{
		com = rand()%3;
		printf(">선택하세요 (1.가위, 2.바위, 3.보, 4.끝내기)?");
		scanf("%d",&user);
		if(user == 4)
		{
			printf("프로그램을 끝냅니다.\n");
			return user;
		}
		result = RSP_game(com, user);
		if(result == WIN || result == LOSE) break;
		printf("결과: 비겼습니다. 다시 합니다.\n");
	}
	if(result == WIN) printf("결과: 컴퓨터가 이겼습니다. 오른쪽으로 이동하겠습니다.\n");
	else printf("결과: 컴퓨터가 졌습니다. 왼쪽으로 이동하겠습니다.\n");
	return result;
}
void insert_node(Node *pre)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->win = 0;
	new_node->lose = 0;
	Node *right = pre->right;
	pre->right = new_node;
	new_node->right = right;
	new_node->left = pre;
	right->left = new_node;
}
void delete_node(Node *cur)
{
	Node *left = cur->left;
	Node *right = cur->right;
	left->right = right;
	right->left = left;
}
	
Node *move(Node *computer_ptr, RSP result, Node **head_ptr)
{
	if(result == WIN)
	{
		computer_ptr->win++;
		if(computer_ptr->win >= 3)
		{	
			computer_ptr->win = 0;
			insert_node(computer_ptr);
		}
		computer_ptr = computer_ptr->right;
	}
	else if(result == LOSE)
	{
		computer_ptr->lose++;
		Node *temp = computer_ptr;
		computer_ptr = computer_ptr->left;
		if(temp->lose >= 3)
		{
			if(temp == *head_ptr)
			{
				*head_ptr = (*head_ptr)->left;
			}
			delete_node(temp);
			if(computer_ptr == temp)
			{
				*head_ptr = NULL;
				computer_ptr = NULL;
			}
		}
	}
	return computer_ptr;
}

void print_list(Node *head, Node *com)
{
	Node *cur = head;
	printf("\n");
	printf("-노드 구조 시작(리스트 끝과 이중연결)-\n");
	if(head != NULL)
		while(1)
		{
			printf("win:%d/lose:%d",cur->win,cur->lose);
			if(cur == com)
			{
				printf("/Computer");
			}
			printf("\n");
			printf("  ^  |\n");
			printf("  |  v\n");
			cur = cur->right;
			if(cur == head) break;
		}
	printf("-노드 구조 끝(리스트 시작과 이중연결)-\n");
	printf("\n");
}
