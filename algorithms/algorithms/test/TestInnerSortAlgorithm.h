#pragma once

#ifndef _TESTINNERSORTALGORITHM_H_
#define _TESTINNERSORTALGORITHM_H_

class TestInnerSortAlgorithm
{
public:
    enum Algorithm
    {
        INSERT,     // ╡ЕхКеепР
        SELECTION,  // я║тЯеепР
        BUBBLE,     // ц╟ещеепР
        SHELL,      // оё╤ШеепР
        MERGE,      // ╧И╡╒еепР
        QUICK,      // ©ЛкыеепР
        HEAP,       // ╤яеепР
        COUNT,      // ╪фйЩеепР
        BUCKET,     // м╟еепР
        BASE        // ╩ЫйЩеепР
    };
public:
    void test( const Algorithm algorithm );
};

#endif
