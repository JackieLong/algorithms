#include "test/TestInnerSortAlgorithm.h"
#include "test/TestLLKAlgorithm.h"
#include "test/TestSearchAlgorithm.h"
#include "Algorithm.h"

using namespace std;

int main()
{
    // ***************************************************************
    //
    // ≤‚ ‘¡¨¡¨ø¥À„∑®
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
    // ≤‚ ‘ƒ⁄≈≈–ÚÀ„∑®
    //
    // ***************************************************************
    //TestInnerSortAlgorithm testSort;
    //testSort.test( TestInnerSortAlgorithm::Algorithm::INSERT );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::SELECTION );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::BUBBLE );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::SHELL );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::MERGE );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::QUICK );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::HEAP );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::COUNT );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::BUCKET );
    //testSort.test( TestInnerSortAlgorithm::Algorithm::BASE );

    // ***************************************************************
    //
    // ≤‚ ‘≤È’“À„∑®
    //
    // ***************************************************************
    //TestSearchAlgorithm testSearch;
    //testSearch.testBinary();
    //testSearch.testBinaryRecur();

    // ***************************************************************
    //
    // ≤‚ ‘∫∫≈µÀ˛À„∑®
    //
    // ***************************************************************
    Algorithm::Pole start, goal, temp;
    start.data = { 6, 5, 4, 3, 2, 1 };
    Algorithm::TOH( start, goal, temp );

    return 0;
}
