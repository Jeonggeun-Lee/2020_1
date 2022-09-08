#ifndef __SHAPES_H__
#define __SHAPES_H__
#include "BaseShape.h"

class Line : public Shape
{
private:
    Point end_p;

public:
    Line(int x1, int y1, int x2, int y2) : Shape(x1, y1), end_p(x2, y2) {}
    virtual void draw(Canvas &canvas, string val = "O")
    {
        Shape::draw(canvas, val);
        canvas.draw(end_p.getX(), end_p.getY(), val);
        int x1 = Shape::p.getX();
        int y1 = Shape::p.getY();
        int x2 = end_p.getX();
        int y2 = end_p.getY();
        int i, j;
        int xs, xl;
        int ys, yl;
        xl = Max(x1, x2);
        if (xl == x1)
            xs = x2;
        else
            xs = x1;
        yl = Max(y1, y2);
        if (yl == y1)
            ys = y2;
        else
            ys = y1;
        if (xs == xl && ys == yl)
            return;
        if (xs == xl)
        {
            for (j = ys; j <= yl; ++j)
                canvas.draw(xs, j, val);
            return;
        }
        else if (ys == yl)
        {
            for (i = xs; i <= xl; ++i)
                canvas.draw(ys, i, val);
            return;
        }
        else
        {
            for (i = xs; i <= xl; ++i)
                for (j = ys; j <= yl; ++j)
                {
                    if (Round((float)(y2 - y1) / (float)(x2 - x1) * (i - x1) + y1) == j)
                        canvas.draw(i, j, val);
                }
        }
    }
    virtual void move(int dx, int dy)
    {
        Shape::move(dx, dy);
        end_p.move(dx, dy);
    }
};

class VLine : public Shape
{
private:
    int len;

public:
    VLine(int x, int y, int len) : Shape(x, y), len(len) {}
    virtual void draw(Canvas &canvas, string val = "O")
    {
        Shape::draw(canvas, val);
        int x = Shape::p.getX();
        int y = Shape::p.getY();
        int i;
        if (len > 0)
        {
            for (i = 0; i <= len; ++i)
            {
                canvas.draw(x, y + i, val);
            }
        }
        else if (len < 0)
        {
            for (i = 0; i >= len; --i)
            {
                canvas.draw(x, y + i, val);
            }
        }
    }
    virtual void move(int dx, int dy)
    {
        Shape::move(dx, dy);
    }
};

class HLine : public Shape
{
private:
    int len;

public:
    HLine(int x, int y, int len) : Shape(x, y), len(len) {}
    virtual void draw(Canvas &canvas, string val = "O")
    {
        Shape::draw(canvas, val);
        int x = Shape::p.getX();
        int y = Shape::p.getY();
        int i;
        if (len > 0)
        {
            for (i = 0; i <= len; ++i)
            {
                canvas.draw(x + i, y, val);
            }
        }
        else if (len < 0)
        {
            for (i = 0; i >= len; --i)
            {
                canvas.draw(x + i, y, val);
            }
        }
    }
    virtual void move(int dx, int dy)
    {
        Shape::move(dx, dy);
    }
};

class Rect : public Shape
{
private:
    HLine hLNear;
    HLine hLFar;
    VLine vLNear;
    VLine vLFar;

public:
    Rect(int x, int y, int xLen, int yLen)
        : Shape(x, y), hLNear(x, y, xLen), hLFar(x, y + yLen, xLen), vLNear(x, y, yLen), vLFar(x + xLen, y, yLen)
    {
    }
    virtual void draw(Canvas &canvas, string val = "O")
    {
        Shape::draw(canvas, val);
        hLNear.draw(canvas, val);
        hLFar.draw(canvas, val);
        vLNear.draw(canvas, val);
        vLFar.draw(canvas, val);
    }
    virtual void move(int dx, int dy)
    {
        Shape::move(dx, dy);
        hLNear.move(dx, dy);
        hLFar.move(dx, dy);
        vLNear.move(dx, dy);
        vLFar.move(dx, dy);
    }
};

class Square : public Shape
{
private:
    Rect rect;

public:
    Square(int x, int y, int len)
        : Shape(x, y), rect(x, y, len, len)
    {
    }
    virtual void draw(Canvas &canvas, string val = "O")
    {
        Shape::draw(canvas, val);
        rect.draw(canvas, val);
    }
    virtual void move(int dx, int dy)
    {
        Shape::move(dx, dy);
        rect.move(dx, dy);
    }
};

/**
 * MyShapes.h : 과제 1-1 을 수행하기 위해 구현 해야 하는 파일
 * 
 * [문제]
 * BaseShape.h 의 Shape 클래스를 상속 받은 Line, Rect, VLine, HLine, Square 을 구현하시오
 * 
 * [조건]
 * 모든 도형은 생성 시점에 각자가 필요한 값을 입력 받아서 저장 해야 한다.
 * 모든 도형(Shape)은 각자의 적절한 규칙으로 그리기(draw) 및 이동(move)이 가능해야 한다.
 * 
 * 1. Line (선)
 * 양 끝점을 입력 받고, 두 점을 잇는 선을 그린다.
 * 
 * 2. Rect (사각형)
 * 시작 위치와 가로 세로를 입력 받고, 조건에 맞는 사각형을 그린다.
 * 
 * 3. VLine (수직선)
 * 한 점과 길이를 입력 받고, 수직선을 그린다.
 * 
 * 4. HLine (수평선)
 * 한 점과 길이를 입력 받고, 수평선을 그린다.
 * 
 * 5. Square (정사각형)
 * 시작 위치와 길이를 입력 받고, 정 사각형을 그린다.
 * 
 **/

#endif