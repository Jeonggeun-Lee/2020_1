#include "MyShapes.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#define NUM_MAX 30
#define INPUT_MAX 100
#define CANVAS_WIDTH 100
#define CANVAS_HEIGHT 100

void Draw_all(Shape **, Canvas &);
void Post_routine(Shape **sh_arr, Canvas &canvas);
void Add(char sh_type, int n1, int n2, int n3, int n4, Shape **sh_arr, int &last_ind, Canvas &canvas);
void Move(int ind, int dx, int dy, Shape **sh_arr);
void Process(char type, int n1, int n2, int n3, int n4, Shape **sh_arr, int &last_ind, Canvas &canvas);
void Arr_del(Shape **sh_arr);

int main(int argc, char const *argv[])
{
  Shape *sh_arr[NUM_MAX] = {
      NULL,
  };
  int last_ind = -1;
  char input[INPUT_MAX];
  char type;
  int n1 = 0, n2 = 0, n3 = 0, n4 = 0;

  Canvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
  canvas.print();
  while (true)
  {
    gets(input);
    if (input[0] == 'q')
      break;
    else if (input[0] == 'l' || input[0] == 'r')
      sscanf(input, "%c %d %d %d %d", &type, &n1, &n2, &n3, &n4);
    else if (input[0] == 'v' || input[0] == 'h' || input[0] == 's' || input[0] == 'm')
      sscanf(input, "%c %d %d %d", &type, &n1, &n2, &n3);
    Process(type, n1, n2, n3, n4, sh_arr, last_ind, canvas);
  }
  Arr_del(sh_arr);
  // 예제 코드 끝

  /**
   * Main.cpp : 과제 1-2 를 수행하기 위해 이 아래에 로직을 구현하시오
   * 
   * 동적으로 키보드의 입력을 받아서 해당하는 도형을 Canvas에 추가해서 그리거나 프로그램을 종료하는 프로그램
   * 
   * [입력 방식]
   * Line : l x1 y1 x2 y2<엔터>       ==> 예) l 10 10 20 20<엔터>
   * Rect : r x y width height<엔터>  ==> 예) r 10 20 40 20<엔터>
   * VLine : v x y length<엔터>       ==> 예) v 10 20 5<엔터>
   * HLine : h x y length<엔터>       ==> 예) v 10 20 5<엔터>
   * Square : s x y length<엔터>      ==> 예) s 10 20 5<엔터>
   * 종료 : q<엔터>
   * 
   * [참고]
   * 입력 및 입력 값 확인을 위해서 아래의 함수들을 적절히 조합하여 사용하면 유용하다.
   * 
   * gets : https://modoocode.com/45
   * char* gets(char* str); // 엔터를 입력 받을 때 까지 문자열을 입력 받음
   * 
   * sscanf : https://modoocode.com/67
   * int sscanf(const char* str, const char* format, ...); // 데이터를 특정 포멧으로 입력 받고 그 갯수를 반환
   * 
   **/
  return 0;
}

void Draw_all(Shape **sh_arr, Canvas &canvas)
{
  int i;
  for (i = 0; i < NUM_MAX; ++i)
  {
    if (sh_arr[i] != NULL)
    {
      sh_arr[i]->draw(canvas, "O");
    }
  }
}

void Post_routine(Shape **sh_arr, Canvas &canvas)
{
  canvas.clear();
  Draw_all(sh_arr, canvas);
  canvas.print();
}

void Add(char sh_type, int n1, int n2, int n3, int n4, Shape **sh_arr, int &last_ind, Canvas &canvas)
{
  if (last_ind == 29)
  {
    printf("no more shape\n");
    return;
  }
  ++last_ind;
  switch (sh_type)
  {
  case 'l':
    sh_arr[last_ind] = new Line(n1, n2, n3, n4);
    break;
  case 'r':
    sh_arr[last_ind] = new Rect(n1, n2, n3, n4);
    break;
  case 'v':
    sh_arr[last_ind] = new VLine(n1, n2, n3);
    break;
  case 'h':
    sh_arr[last_ind] = new HLine(n1, n2, n3);
    break;
  case 's':
    sh_arr[last_ind] = new Square(n1, n2, n3);
    break;
  default:
    break;
  }
}

void Move(int ind, int dx, int dy, Shape **sh_arr)
{
  sh_arr[ind]->move(dx, dy);
}

void Process(char type, int n1, int n2, int n3, int n4, Shape **sh_arr, int &last_ind, Canvas &canvas)
{
  if (type == 'm')
    Move(n1, n2, n3, sh_arr);
  else
  {
    Add(type, n1, n2, n3, n4, sh_arr, last_ind, canvas);
  }
  Post_routine(sh_arr, canvas);
}

void Arr_del(Shape **sh_arr)
{
  int i;
  for (i = 0; i < NUM_MAX; ++i)
  {
    if (sh_arr[i] != NULL)
      delete sh_arr[i];
  }
}
