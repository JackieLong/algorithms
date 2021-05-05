#pragma once

#ifndef _TOH_H_
#define _TOH_H_

#include <vector>
#include <functional>
#include "../Macro.h"

NS_ALGORITHM_BEGIN

struct Pole
{
    std::vector<int> data;
    int              id;
};

// ��ŵ���㷨��
//
// ������start�ϵ�Բ���Զ�����n��Բ�̣��ƶ�������goal����temp��Ϊ�����塱���ӡ�
//
static void TOH( int n, Pole &start, Pole &goal, Pole &temp, std::function<void()> callback )
{
    if( start.data.empty() || n <= 0 ) { return; }      // ����Ϊ�գ��ƶ����

    TOH( n - 1, start, temp, goal, callback );          //��n-1�����Ӵ�start�ƶ���temp��goal������ġ�

    if( !start.data.empty() )
    {
        //�����ƶ�����ˣ�goal��Ϊ��������Ӧ���Ѿ�����
        //��ʱstart��ʣ������µ������ƶ���goal��
        goal.data.push_back( start.data.back() );
        start.data.pop_back();
    }

    if( callback ) { callback(); }                      // ��ӡ��ǰ�������ӵ�����

    //����ִ����ϣ�temp��������n-1��Բ�̣�start�ǿյ����ӣ�goal��Ŀ��������1��Բ��
    //�������Ĺ������ǰ�temp�����ϵ�Բ���ƶ���goal�����ϣ�start������Ϊ���档
    TOH( n - 1, temp, goal, start, callback );
}

// ��ŵ���㷨��
//
// ������start�ϵ�Բ�̣��ƶ�������goal����temp��Ϊ�����塱���ӡ�
//
static void TOH( Pole &start, Pole &goal, Pole &temp )
{
    int maxSize = start.data.size() + 2;
    std::function<void()> printPoleStatus = [&]
    {
        for( int i = 0; i < maxSize; i++ )
        {
            if( start.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", start.data[maxSize - i - 1] ); }

            if( goal.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", goal.data[maxSize - i - 1] ); }

            if( temp.data.size() < maxSize - i ) { printf( "-  " ); }
            else { printf( "%d  ", temp.data[maxSize - i - 1] ); }

            printf( "\n" );
        }
        printf( "********************************************************\n" );
    };

    TOH( start.data.size(), start, goal, temp, printPoleStatus );
}

NS_ALGORITHM_END

#endif