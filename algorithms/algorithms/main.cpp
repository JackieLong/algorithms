
#include "llk/LLKAlgorithm.h"
#include "inner_sort/InnerSortAlgorithm.h"
#include "search/SearchAlgorithm.h"

using namespace std;

int main()
{
    // ***************************************************************
    //
    // 测试连连看算法
    //
    // ***************************************************************
    //TestLLKAlgorithm testLLK;
    //testLLK.test_turn0Corner_bool();
    //testLLK.test_turn0Corner_callback();
    //testLLK.test_turn0Corner_vertical();
    //testLLK.test_turn0Corner_horizontal();
    //testLLK.test_turn1Corner();
    //testLLK.test_turn1Corner_bool();
    //testLLK.test_turn2Corner();
    //testLLK.test_turn2Corner_bool();
    //testLLK.test_path();
    //testLLK.test_path_bool();
    //testLLK.test_path_bool_1();

    // ***************************************************************
    //
    // 测试内排序算法
    //
    // ***************************************************************
    //TestInnerSortAlgorithm testSort;
    //testSort.test( InnerSortAlgorithm::Algorithm::INSERT );
    //testSort.test( InnerSortAlgorithm::Algorithm::SELECTION );
    //testSort.test( InnerSortAlgorithm::Algorithm::BUBBLE );
    //testSort.test( InnerSortAlgorithm::Algorithm::SHELL );
    //testSort.test( InnerSortAlgorithm::Algorithm::MERGE );
    //testSort.test( InnerSortAlgorithm::Algorithm::QUICK );
    //testSort.test( InnerSortAlgorithm::Algorithm::HEAP );
    //testSort.test( InnerSortAlgorithm::Algorithm::COUNT );
    //testSort.test( InnerSortAlgorithm::Algorithm::BUCKET );
    //testSort.test( InnerSortAlgorithm::Algorithm::BASE );

    // ***************************************************************
    //
    // 测试查找算法
    //
    // ***************************************************************
    TestSearchAlgorithm testSearch;
    testSearch.test( SearchAlgorithm::Algorithm::Binary );
    testSearch.test( SearchAlgorithm::Algorithm::Binary_Recur );
    return 0;
}
