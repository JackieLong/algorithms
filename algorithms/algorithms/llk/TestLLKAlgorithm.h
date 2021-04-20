#pragma once

#ifndef _TESTLLKALGORITHM_H_
#define _TESTLLKALGORITHM_H_

// �����ǲ�������
// ���Է������ǣ����������̣����ȡ���ж�Էǿ�����������в��ԡ�
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
    void randomChess();                          // �������
    void printChess( const int &idx );           // ��ӡ���̲���
};

#endif