#pragma once

#ifndef _TESTLLKALGORITHM_H_
#define _TESTLLKALGORITHM_H_

// 以下是测试用例
// 测试方法就是，随机多个棋盘，随机取其中多对非空棋子坐标进行测试。
class TestLLKAlgorithm
{
public:
    void test_turn0Corner_bool();
    void test_turn0Corner_callback();
    void test_turn0Corner_vertical();
    void test_turn0Corner_horizontal();
    void test_turn1Corner();
    void test_turn1Corner_bool();
    void test_turn2Corner();
    void test_turn2Corner_bool();
    void test_path();
    void test_path_bool();
    void test_path_bool_1();

private:
    void randomChess();                          // 随机棋牌
    void printChess( const int &idx );           // 打印棋盘布局
};

#endif