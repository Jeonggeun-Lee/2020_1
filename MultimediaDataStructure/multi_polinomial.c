#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 1000
#define MAX_FACT_NUM 100
#define MAX_TERM_NUM 100
#define MAX_DEGREE 50

void clear_space(const char expr[MAX_LEN],char temp_expr[MAX_LEN]);
void change_power(const char *expr, char *new_expr);
int num_of_fact(const char *expr);
void seperate_fact(char **fact_arr,char *expr);
void strip(char *fact);
char last_oper(const char *fact);
char *cons_add_x(char *fact);
void x_add_1(char *fact);
void minus_add_plus(char *fact);
void delete_first_plus(char *fact);
void normalize(char *fact);
int deg_of_fact(const char *fact);

typedef struct{
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

polynomial fact_to_poly(char *fact);
void printPoly(polynomial);
polynomial multiPoly(polynomial, polynomial);
polynomial solve(polynomial *,int);

int main(){
	char expr[MAX_LEN];
	char temp_expr[MAX_LEN];
	char new_expr[MAX_LEN];
	int fact_num;
	char *fact_arr[MAX_FACT_NUM];
	int i;
	printf("?");
	gets(expr);
	clear_space(expr,temp_expr);
	change_power(temp_expr,new_expr);
	fact_num = num_of_fact(new_expr);
	for(i=0; i<fact_num; ++i)
	{
		fact_arr[i] = (char *)malloc(MAX_LEN);
	}
	seperate_fact(fact_arr,new_expr);
	for(i=0;i<fact_num;++i)
	{
		normalize(fact_arr[i]);
	}
	polynomial p_arr[fact_num];
	for(i=0; i< fact_num; ++i)
	{
		p_arr[i] = fact_to_poly(fact_arr[i]);
	}
	polynomial R;
	R = solve(p_arr,fact_num);
	printPoly(R);

	return 0;
}
//다항식을 받는다
//빈칸을 제거한다
//**를 ^로 바꾼다
//곱셈의 개수를 세서 다항식의 개수를 센다
//곱셈의 개수만큼 구조체 polynomial을 만든다
//곱셈단위로 곱셈된  다항식을 자른다

////자른 다항식을 정규화 한다
//괄호가 있다면 없앤다
//상수항이 있다면 뒤에 x^0을 붙인다
//맨 앞의 x 앞에 1을 붙인다
//x 바로 앞에+ 나 - 가 있다면 x 앞에 1을 붙인다
//-가 있다면 앞에 +를 붙인다
//맨앞에 +가 있다면 지운다

//덧셈의 개수를 세서 항의 개수를 센다
//항의 개수만큼 구조체 term의 배열을 만든다
//덧셈 단위로 덧셈된 항을 자른다
//구조체 polynomial에 넣는다
//polynomial들을 곱한다
void clear_space(const char expr[MAX_LEN],char temp_expr[MAX_LEN])
{
	int len = strlen(expr);
	int i=0,j=0;
	for(i=0; i<len; ++i)
	{
		if(expr[i]!=' ')
		{
			temp_expr[j] = expr[i];
			++j;
		}
	}
	temp_expr[j]='\0';
}
void change_power(const char expr[MAX_LEN], char new_expr[MAX_LEN])
{
	int len = strlen(expr);
	int i,j;
	char buff;
	j=0;
	for(i = 0; i<len;)
	{
		buff = expr[i];
		if(buff != '*')
		{
			new_expr[j] = buff;
			++i;
			++j;
		}
		else if(buff == '*')
		{
			if( expr[i+1] != '*')
			{
				new_expr[j] = buff;
				++i;
				++j;
			}
			else if( expr[i+1] == '*')
			{
				new_expr[j] = '^';
				i += 2;
				++j;
			}
		}
	}
	new_expr[j] = '\0';
}
int num_of_fact(const char *expr)
{
	int i=0;
	int len = strlen(expr);
	int sum = 0;
	for(i=0; i<len; ++i)
	{
		if(expr[i]=='*') ++sum;
	}
	return sum+1;
}
void seperate_fact(char **fact_arr, char *expr)
{
	int i=0;
	char *temp_fact;

	temp_fact = strtok(expr,"*");
	strcpy(fact_arr[i],temp_fact);
	while(1)
	{
		++i;
		temp_fact = strtok(NULL,"*");
		if(temp_fact==NULL) break;
		strcpy(fact_arr[i],temp_fact);
	}
}
void strip(char *fact)
{
	int len;
	int i;
	char temp_fact[MAX_LEN];
	strcpy(temp_fact,fact);
	if( *(fact)=='(')
	{
		len = strlen(fact);
		memmove(fact,temp_fact+1,len-2);
	}
	fact[len-2]='\0';
}
char last_oper(const char *fact)
{
	char oper = '\0';
	int len = strlen(fact);
	int i=0;
	for(i=0; i<len; ++i)
	{
		if(fact[i] == '+' || fact[i] == '-' || fact[i] == '^') oper = fact[i];
	}
	return oper;
}
char *cons_add_x(char *fact)
{
	if(last_oper(fact) == '^') return fact;
	int len = strlen(fact);
	
	char *temp_fact = (char *)malloc(MAX_LEN);
	strcpy(temp_fact, fact);
	if(temp_fact[len-1]>='0' && temp_fact[len-1] <='9')
	{
		strcat(temp_fact,"x^0\0");
	}
	return temp_fact;
}
void x_add_1(char *fact)
{
	char *temp_fact = (char *)malloc(MAX_LEN);
	if(fact[0] == 'x')
	{
		temp_fact[0] = '1';
	}
	strcat(temp_fact,fact);
	strcpy(fact,temp_fact);
}
void minus_add_plus(char *fact)
{
	int len = strlen(fact);
	char *temp_fact = (char *)malloc(MAX_LEN);
	int i,j;
	char buff;
	j = 0;
	for(i=0; i<len;)
	{
		buff = fact[i];
		if(buff != '-')
		{
			temp_fact[j] = buff;
			++i;
			++j;
		}
		else if(buff == '-')
		{
			temp_fact[j] = '+';
			++j;
			temp_fact[j] = buff;
			++i;
			++j;
		}
	}
	temp_fact[j]='\0';
	strcpy(fact, temp_fact);
}
void delete_first_plus(char *fact)
{
	int len = strlen(fact);
	if(fact[0]=='+')
	{
		char *temp_fact = (char *)malloc(MAX_LEN);
		memcpy(temp_fact,fact+1,len-1);
		temp_fact[len-1] = '\0';
		strcpy(fact, temp_fact);
	}
}
void normalize(char *fact)
{
	char *temp_fact = (char *)malloc(MAX_LEN);
	strcpy(temp_fact, fact);
	strip(temp_fact);
	temp_fact = cons_add_x(temp_fact);
	x_add_1(temp_fact);
	minus_add_plus(temp_fact);
	delete_first_plus(temp_fact);
	strcpy(fact, temp_fact);
}

int num_of_term(const char *fact)
{
	int sum=0;
	int i;
	int len = strlen(fact);
	for(i=0; i<len; ++i)
	{
		if(fact[i] == '+') ++sum;
	}
	return sum+1;
}

int deg_of_fact(const char *fact)
{
	int deg=0;
	int len = strlen(fact);
	int i;
	for(i=0; i<len;++i)
	{
		if(fact[i] == '^')
		{
			if(fact[i+1]-'0' > deg) deg = fact[i+1]-'0';
			i++;
		}
	}
	return deg;
}

polynomial fact_to_poly(char *fact)
{
	polynomial p;
	if(strcmp(fact,"0x^0")==0)
	{
		p.degree = 0;
		p.coef[0] = 0;
		return p;
	}
	p.degree = deg_of_fact(fact);
	int i;
	for(i=0; i<=p.degree; ++i)
	{
		p.coef[i]=0;
	}
		
	int deg;
	float coef;
	char *tok = strtok(fact,"+");
	sscanf(tok,"%fx^%d",&coef,&deg);
	p.coef[p.degree-deg] = coef;
	while(1)
	{
		tok = strtok(NULL, "+");
		if(tok==NULL) break;
		sscanf(tok,"%fx^%d",&coef,&deg);
		p.coef[p.degree-deg] = coef;
	}
	return p;
}
void printPoly(polynomial P)
{
	if(P.degree == 0 && P.coef[0] == 0)
	{
		printf("0\n");
		return;
	}
	int i, degree;
	degree = P.degree;
	for(i=0; i<=P.degree; ++i)
	{
		if(P.coef[i]==0)
		{
			degree--;
			continue;
		}
		if(i !=0 && P.coef[i]>=0) printf(" +");
		else printf(" ");
		if(i!=P.degree) printf("%fx**%d",P.coef[i], degree--);
		else {
			printf("%f",P.coef[i]);
			degree--;
		}
	}
	printf("\n");
}

polynomial multiPoly(polynomial P, polynomial Q)
{
	polynomial R;
	R.degree = 0;
	R.coef[0]=0;
	if(P.degree == 0 && P.coef[0]==0) return R;
	if(Q.degree == 0 && Q.coef[0]==0) return R;
	R.degree = P.degree + Q.degree;
	int i,j;
	for(i=0; i<=R.degree; ++i)
	{
		R.coef[i] = 0;
	}
	for(i = P.degree; i>=0; --i)
	{
		for(j = Q.degree; j>=0; --j)
		{
			R.coef[i+j] += P.coef[i]*Q.coef[j];
		}
	}
	return R;
}
polynomial solve(polynomial *p_arr, int fact_num)
{
	polynomial R;
	R.degree = 0;
	R.coef[0] = 1;
	int i;
	for(i=0; i<fact_num; ++i)
	{
		R = multiPoly(R, p_arr[i]);
	}

	return R;
}
