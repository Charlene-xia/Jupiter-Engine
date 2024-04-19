// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Headers.h"

export module UnitTests_LinkedList;

import jpt.Any;
import jpt.DynamicArray;
import jpt.LinkedList;
import jpt.String;
import jpt.Tuple;
import jpt.TypeDefs;
import jpt.Utilities;
import jpt.Variant;

auto locHelper = [](size_t i) -> const char*
    {
        switch (i)
        {
        case 0: return "Zero";
        case 1: return "One";
        case 2: return "Two";
        case 3: return "Three";
        case 4: return "Four";
        case 5: return "Five";
        case 6: return "Six";
        case 7: return "Seven";
        case 8: return "Eight";
        case 9: return "Nine";
        case 10: return "Ten";
        case 11: return "Eleven";
        case 12: return "Twelve";

        default: return "Error";
        }
    };

bool UnitTest_LinkedList_Trivial()
{
    jpt::LinkedList<int32> list{ 7,8,9 };

    int32& result1 = list.EmplaceBack(1);
    JPT_ENSURE(result1 == 1);
    result1 = 12;
    int32& result2 = list.EmplaceFront(0);
    JPT_ENSURE(result2 == 0);
    result2 = 5;
    list.AddBack(2);
    list.AddFront(-1);

    list.EmplaceAfter(list.begin() + 3, 1);
    list.AddBefore(list.begin() + 2, 3);
    list.AddAfter(list.begin() + (list.Count() - 1), 11);
    list.EmplaceBefore(list.begin() + 5, 0);

    list.PopBack();
    list.PopFront();

    jpt::LinkedList<int32> anotherList{ 5, 3, 7, 8, 0, 1, 9, 12, 2 };
    JPT_ENSURE(list == anotherList);

    jpt::LinkedList<int32> copiedList = anotherList;
    JPT_ENSURE(list == anotherList);
    JPT_ENSURE(list == copiedList);

    jpt::LinkedList<int32> movedList = jpt::Move(anotherList);
    JPT_ENSURE(list == movedList);
    JPT_ENSURE(list == copiedList);
    JPT_ENSURE(anotherList.IsEmpty());

    return true;
}

bool UnitTest_LinkedList_String()
{
    jpt::LinkedList<jpt::String> list{ "Seven", "Eight", "Nine" };

    jpt::String& result1 = list.EmplaceBack(locHelper(1));
    JPT_ENSURE(result1 == locHelper(1));
    result1 = locHelper(12);
    jpt::String& result2 = list.EmplaceFront(locHelper(0));
    JPT_ENSURE(result2 == locHelper(0));
    result2 = locHelper(5);
    list.AddBack(locHelper(2));
    list.AddFront(locHelper(1));

    list.EmplaceAfter(list.begin() + 3, locHelper(1));
    list.AddBefore(list.begin() + 2, locHelper(3));
    list.AddAfter(list.begin() + (list.Count() - 1), locHelper(11));
    list.EmplaceBefore(list.begin() + 5, locHelper(0));

    list.PopBack();
    list.PopFront();

    jpt::LinkedList<jpt::String> anotherList{ locHelper(5), locHelper(3),locHelper(7),locHelper(8),locHelper(0),locHelper(1),locHelper(9),locHelper(12),locHelper(2) };
    JPT_ENSURE(list == anotherList);

    jpt::LinkedList<jpt::String> copiedList = anotherList;
    JPT_ENSURE(list == anotherList);
    JPT_ENSURE(list == copiedList);

    jpt::LinkedList<jpt::String> movedList = jpt::Move(anotherList);
    JPT_ENSURE(list == movedList);
    JPT_ENSURE(list == copiedList);
    JPT_ENSURE(anotherList.IsEmpty());

    return true;
}

JPT_ENUM_UINT32(ETest2,
    Zero = 12,
    One,
    Two,
    Three,
    Four = (1 << 8),
    Five,
    Six);
bool UnitTest_LinkedList_Enum()
{
	jpt::LinkedList<ETest2> list{ ETest2::Zero, ETest2::Two, ETest2::Four };

    ETest2 test = list.Front();
    list.PopFront();
    JPT_ENSURE(test == ETest2::Zero);
    JPT_ENSURE(test.Value() == 12);
    JPT_ENSURE(test.ToString() == "Zero");

    test = list.Front();
    list.PopFront();
    JPT_ENSURE(test == ETest2::Two);
    JPT_ENSURE(test.Value() == 14);
    JPT_ENSURE(test.ToString() == "Two");

    test = list.Front();
    list.PopFront();
    JPT_ENSURE(test == ETest2::Four);
    JPT_ENSURE(test.Value() == 256);
    JPT_ENSURE(test.ToString() == "Four");

	return true;
}

bool UnitTest_LinkedList_Any()
{
    // Any's m_smallBuffer and m_pBuffer set correctly
    jpt::LinkedList<jpt::Any> list2{ 1.05f };
    JPT_ENSURE(list2.Front().As<float>() == 1.05f);

    // m_pBuffer not pointing to correct m_smallBuffer
    jpt::LinkedList<jpt::Any> list1;
    list1.EmplaceBack(1.05f);
    JPT_ENSURE(list1.Front().As<float>() == 1.05f);

    return true;
}

export bool RunUnitTests_LinkedList()
{
    JPT_ENSURE(UnitTest_LinkedList_Trivial());

    JPT_ENSURE(UnitTest_LinkedList_String());
    JPT_ENSURE(UnitTest_LinkedList_Enum());
    //JPT_ENSURE(UnitTest_LinkedList_Any());

    return true;
}
