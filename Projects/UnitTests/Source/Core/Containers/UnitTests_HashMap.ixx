// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

#include "Core/Minimal/Headers.h"

#include <unordered_map>

export module UnitTests_HashMap;

import jpt.TypeDefs;
import jpt.Utilities;
import jpt.Function;
import jpt.HashMap;

bool UnitTest_HashMap_Trivial()
{
    jpt::HashMap<char, int32> map;

    // Adding
    map.Add('a', 0);
    map.Add('b', 1);
    map.Add('c', 2);
    map['a'] = 3;
    map['d'] = 4;
    map['e'] = 5;

    JPT_ENSURE(map['a'] == 3);
    JPT_ENSURE(map['b'] == 1);
    JPT_ENSURE(map['c'] == 2);
    JPT_ENSURE(map['d'] == 4);
    JPT_ENSURE(map['e'] == 5);

    // Erasing
    map.Erase('e');

    // Searching
    JPT_ENSURE(map.Contains('a'));
    JPT_ENSURE(!map.Contains('e'));
    JPT_ENSURE(map.Find('a')->second == 3);
    JPT_ENSURE(map.Find('e') == map.end());

    // Modifiying
    //JPT_LOG(map);
    map.Clear();
    //JPT_LOG(map);

    // Capacity
    JPT_ENSURE(map.IsEmpty());

    return true;
}

bool UnitTest_HashMap_Trivial_Copy()
{
    jpt::HashMap<char, int32> map{ {'a', 1},{'b', 2},{'c', 3} };
    JPT_ENSURE(map['a'] == 1);
    JPT_ENSURE(map['b'] == 2);
    JPT_ENSURE(map['c'] == 3);
    JPT_ENSURE(map.Count() == 3);

    jpt::HashMap<char, int32> otherMap(map);
    JPT_ENSURE(otherMap['a'] == 1);
    JPT_ENSURE(otherMap['b'] == 2);
    JPT_ENSURE(otherMap['c'] == 3);
    JPT_ENSURE(otherMap.Count() == 3);

    jpt::HashMap<char, int32> otherMap2;
    otherMap2 = otherMap;
    JPT_ENSURE(otherMap2['a'] == 1);
    JPT_ENSURE(otherMap2['b'] == 2);
    JPT_ENSURE(otherMap2['c'] == 3);
    JPT_ENSURE(otherMap2.Count() == 3);

    //JPT_LOG(map);
    //JPT_LOG(otherMap);
    //JPT_LOG(otherMap2);

    return true;
}

bool UnitTest_HashMap_Trivial_Move()
{
    jpt::HashMap<char, int32> map{ {'a', 1},{'b', 2},{'c', 3} };
    JPT_ENSURE(map['a'] == 1);
    JPT_ENSURE(map['b'] == 2);
    JPT_ENSURE(map['c'] == 3);
    JPT_ENSURE(map.Count() == 3);

    jpt::HashMap<char, int32> otherMap(jpt::Move(map));
    JPT_ENSURE(otherMap['a'] == 1);
    JPT_ENSURE(otherMap['b'] == 2);
    JPT_ENSURE(otherMap['c'] == 3);
    JPT_ENSURE(otherMap.Count() == 3);
    JPT_ENSURE(map.IsEmpty());

    jpt::HashMap<char, int32> otherMap2;
    otherMap2 = jpt::Move(otherMap);
    JPT_ENSURE(otherMap2['a'] == 1);
    JPT_ENSURE(otherMap2['b'] == 2);
    JPT_ENSURE(otherMap2['c'] == 3);
    JPT_ENSURE(otherMap2.Count() == 3);
    JPT_ENSURE(otherMap.IsEmpty());

    //JPT_LOG(map);
    //JPT_LOG(otherMap);
    //JPT_LOG(otherMap2);

    return true;
}

bool UnitTest_HashMap_NonTrivial()
{
    jpt::HashMap<jpt::String, jpt::String> map;

    // Inserting
    map.Add("Champ A", "Aatrox");
    map.Add("Champ B", "Darius");
    map.Add("Champ C", "Jax");
    map["Champ A"] =  "Morde";
    map["Champ D"] =  "Nasus";
    map["Champ E"] =  "Zac";

    // Inserting
    JPT_ENSURE(map["Champ A"] == "Morde");
    JPT_ENSURE(map["Champ B"] == "Darius");
    JPT_ENSURE(map["Champ C"] == "Jax");
    JPT_ENSURE(map["Champ D"] == "Nasus");
    JPT_ENSURE(map["Champ E"] == "Zac");

    // Erasing
    map.Erase("Champ E");

    // Searching
    JPT_ENSURE(map.Contains("Champ A"));
    JPT_ENSURE(!map.Contains("Champ E"));
    JPT_ENSURE(map.Find("Champ A")->second == "Morde");
    JPT_ENSURE(map.Find("Champ E") == map.end());

    // Modifiying
    //JPT_LOG(map);
    map.Clear();
    //JPT_LOG(map);

    // Capacity
    JPT_ENSURE(map.IsEmpty());

    return true;
}

bool UnitTest_HashMap_NonTrivial_Copy()
{
    jpt::HashMap<jpt::String, jpt::String> map{ {"Champ A", "Aatrox"},{"Champ B","Jax"},{"Champ C", "Darius"} };
    JPT_ENSURE(map["Champ A"] == "Aatrox");
    JPT_ENSURE(map["Champ B"] == "Jax"   );
    JPT_ENSURE(map["Champ C"] == "Darius");
    JPT_ENSURE(map.Count() == 3);

    jpt::HashMap<jpt::String, jpt::String> otherMap(map);
    JPT_ENSURE(otherMap["Champ A"] == "Aatrox");
    JPT_ENSURE(otherMap["Champ B"] == "Jax"   );
    JPT_ENSURE(otherMap["Champ C"] == "Darius");
    JPT_ENSURE(otherMap.Count() == 3);

    jpt::HashMap<jpt::String, jpt::String> otherMap2;
    otherMap2 = otherMap;
    JPT_ENSURE(otherMap2["Champ A"] == "Aatrox");
    JPT_ENSURE(otherMap2["Champ B"] == "Jax"   );
    JPT_ENSURE(otherMap2["Champ C"] == "Darius");
    JPT_ENSURE(otherMap2.Count() == 3);

    //JPT_LOG(map);
    //JPT_LOG(otherMap);
    //JPT_LOG(otherMap2);

    return true;
}

bool UnitTest_HashMap_NonTrivial_Move()
{
    jpt::HashMap<jpt::String, jpt::String> map{ {"Champ A", "Aatrox"},{"Champ B","Jax"},{"Champ C", "Darius"} };
    JPT_ENSURE(map["Champ A"] == "Aatrox");
    JPT_ENSURE(map["Champ B"] == "Jax");
    JPT_ENSURE(map["Champ C"] == "Darius");
    JPT_ENSURE(map.Count() == 3);

    jpt::HashMap<jpt::String, jpt::String> otherMap(jpt::Move(map));
    JPT_ENSURE(otherMap["Champ A"] == "Aatrox");
    JPT_ENSURE(otherMap["Champ B"] == "Jax"   );
    JPT_ENSURE(otherMap["Champ C"] == "Darius");
    JPT_ENSURE(otherMap.Count() == 3);

    jpt::HashMap<jpt::String, jpt::String> otherMap2;
    otherMap2 = jpt::Move(otherMap);
    JPT_ENSURE(otherMap2["Champ A"] == "Aatrox");
    JPT_ENSURE(otherMap2["Champ B"] == "Jax"   );
    JPT_ENSURE(otherMap2["Champ C"] == "Darius");
    JPT_ENSURE(otherMap2.Count() == 3);

    //JPT_LOG(map);
    //JPT_LOG(otherMap);
    //JPT_LOG(otherMap2);

    return true;
}

void Func(int32& num)
{
    ++num;
}

bool UnitTest_HashMap_Function()
{
    auto lambda = [](int32& num)->void
        {
            num += 2;
        };
    
    jpt::HashMap<jpt::String, jpt::Function<void(int32&)>> map;
    map["Func1"] = Func;
    map["Func2"] = lambda;

    int32 i = 0;

    map["Func1"](i);
    JPT_ENSURE(i == 1);
    
    map["Func2"](i);
    JPT_ENSURE(i == 3);

    lambda(i);
    JPT_ENSURE(i == 5);

    return true;
}

bool UnitTest_HashMap_Erase()
{
    jpt::HashMap<int32, int32> hashMap;

    JPT_ENSURE(hashMap.Count() == 0);

    hashMap.Add(1, 1);
    hashMap.Add(2, 2);

    JPT_ENSURE(hashMap.Count() == 2);

    hashMap.Erase(1);

    JPT_ENSURE(hashMap.Count() == 1);

    return true;
}

bool UnitTest_HashMap_Grow()
{
    jpt::HashMap<int32, int32> hashMap;

    for (int32 i = 0; i < 1000; ++i)
	{
		hashMap.Add(i, i * 2);
	}
    JPT_ENSURE(hashMap.Count() == 1000);

    for (int32 i = 0; i < 1000; ++i)
    {
        JPT_ENSURE(hashMap.Contains(i));
        JPT_ENSURE(hashMap[i] == i * 2);
        JPT_ENSURE(hashMap.Find(i)->second == i * 2);
    } 
    JPT_ENSURE(hashMap.Count() == 1000);

    return true;
}

bool UnitTest_HashMap_Iterate_Erase()
{
    jpt::HashMap<char, int32> hashMap
    { 
        { 'a', 0 }, 
        { 'b', 1 }, 
        { 'c', 2 },
        { 'd', 3 },
        { 'e', 4 }
    };

    JPT_ENSURE(hashMap.Count() == 5);
    JPT_ENSURE(hashMap.Find('a')->second == 0);
    JPT_ENSURE(hashMap.Find('b')->second == 1);
    JPT_ENSURE(hashMap.Find('c')->second == 2);
    JPT_ENSURE(hashMap.Find('d')->second == 3);
    JPT_ENSURE(hashMap.Find('e')->second == 4);

    for (auto itr = hashMap.begin(); itr != hashMap.end();)
	{
        if (itr->first == 'e' || itr->first == 'b')
        {
            itr = hashMap.Erase(itr);
		}
		else
		{
			++itr;
        }
	}

    JPT_ENSURE(hashMap.Count() == 3);
    JPT_ENSURE(hashMap.Find('a')->second == 0);
    JPT_ENSURE(hashMap.Find('c')->second == 2);
    JPT_ENSURE(hashMap.Find('d')->second == 3);
    JPT_ENSURE(hashMap.Find('e') == hashMap.end());
    JPT_ENSURE(hashMap.Find('b') == hashMap.end());

    return true;
}

bool UnitTest_HashMap_Iterate_Erase_String()
{
    jpt::HashMap<jpt::String, jpt::String> hashMap
    { 
        { "Engine", "Jupiter" },
        { "Client", "UnitTests" },
        { "Platform", "Windows" },
		{ "Language", "C++" },
		{ "Version", "1.0" }
    };

    JPT_ENSURE(hashMap.Count() == 5);

    JPT_ENSURE(hashMap.Find("Engine")->second == "Jupiter");
    JPT_ENSURE(hashMap.Find("Client")->second == "UnitTests");
    JPT_ENSURE(hashMap.Find("Platform")->second == "Windows");
    JPT_ENSURE(hashMap.Find("Language")->second == "C++");
    JPT_ENSURE(hashMap.Find("Version")->second == "1.0");

    for (auto itr = hashMap.begin(); itr != hashMap.end();)
	{
		if (itr->first == "Client" || itr->first == "Language")
		{
			itr = hashMap.Erase(itr);
		}
		else
		{
			++itr;
		}
	}

    JPT_ENSURE(hashMap.Count() == 3);

    JPT_ENSURE(hashMap.Find("Engine")->second == "Jupiter");
    JPT_ENSURE(hashMap.Find("Client") == hashMap.end());
    JPT_ENSURE(hashMap.Find("Platform")->second == "Windows");
    JPT_ENSURE(hashMap.Find("Language") == hashMap.end());
    JPT_ENSURE(hashMap.Find("Version")->second == "1.0");

    return true;
}

export bool RunUnitTests_HashMap()
{
    JPT_ENSURE(UnitTest_HashMap_Trivial());
    JPT_ENSURE(UnitTest_HashMap_Trivial_Copy());
    JPT_ENSURE(UnitTest_HashMap_Trivial_Move());

    JPT_ENSURE(UnitTest_HashMap_NonTrivial());
    JPT_ENSURE(UnitTest_HashMap_NonTrivial_Copy());
    JPT_ENSURE(UnitTest_HashMap_NonTrivial_Move());
    
    JPT_ENSURE(UnitTest_HashMap_Function());
    JPT_ENSURE(UnitTest_HashMap_Erase());
    JPT_ENSURE(UnitTest_HashMap_Grow());

    JPT_ENSURE(UnitTest_HashMap_Iterate_Erase());
    JPT_ENSURE(UnitTest_HashMap_Iterate_Erase_String());

    return true;
}
