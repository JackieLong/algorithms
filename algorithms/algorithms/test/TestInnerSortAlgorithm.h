#pragma once

#ifndef _TESTINNERSORTALGORITHM_H_
#define _TESTINNERSORTALGORITHM_H_

class TestInnerSortAlgorithm
{
public:
    enum Algorithm
    {
        INSERT,     // ��������
        SELECTION,  // ѡ������
        BUBBLE,     // ð������
        SHELL,      // ϣ������
        MERGE,      // �鲢����
        QUICK,      // ��������
        HEAP,       // ������
        COUNT,      // ��������
        BUCKET,     // Ͱ����
        BASE        // ��������
    };
public:
    void test( const Algorithm algorithm );
};

#endif
