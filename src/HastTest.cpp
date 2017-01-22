#include <string>
#include <thread>
#include "HashMap.h"

void testSingleThreadStringKey()
{
    CTSL::HashMap<std::string, int> stringMap(1001);

    stringMap.insert("test1", 200);
    stringMap.insert("test2", 670);
    stringMap.insert("test3", 203);

    int value;
    if(stringMap.find("test1", value))
    {
        std::cout << "Found value " << value << " for key \"test1\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test1\"" << std::endl;
    }

    if(stringMap.find("test4", value))
    {
        std::cout << "Found value " << value << " for key \"test4\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test4\"" << std::endl;
    }
    stringMap.insert("test1", 680);
    if(stringMap.find("test1", value))
    {
        std::cout << "Found value " << value << " for key \"test1\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test1\"" << std::endl;
    }
    
    stringMap.erase("test1");
    if(stringMap.find("test1", value))
    {
        std::cout << "Found value " << value << " for key \"test1\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test1\"" << std::endl;
    }

    stringMap.insert("test1", 8680);
    if(stringMap.find("test1", value))
    {
        std::cout << "Found value " << value << " for key \"test1\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test1\"" << std::endl;
    }

    stringMap.clear();
    if(stringMap.find("test1", value))
    {
        std::cout << "Found value " << value << " for key \"test1\"" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key \"test1\"" << std::endl;
    }
}


void testSingleThreadIntegerKey()
{
    CTSL::HashMap<int, int> integerMap(29);

    integerMap.insert(10, 200);
    integerMap.insert(20, 670);
    integerMap.insert(15, 203);

    int value;
    if(integerMap.find(20, value))
    {
        std::cout << "Found value " << value << " for key 20" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 20" << std::endl;
    }

    if(integerMap.find(25, value))
    {
        std::cout << "Found value " << value << " for key 25" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 25" << std::endl;
    }
    integerMap.insert(20, 680);
    if(integerMap.find(20, value))
    {
        std::cout << "Found value " << value << " for key 20" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 20" << std::endl;
    }
    
    integerMap.erase(20);
    if(integerMap.find(20, value))
    {
        std::cout << "Found value " << value << " for key 20" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 20" << std::endl;
    }

    integerMap.insert(20, 8680);
    if(integerMap.find(20, value))
    {
        std::cout << "Found value " << value << " for key 20" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 20" << std::endl;
    }

    integerMap.clear();
    if(integerMap.find(20, value))
    {
        std::cout << "Found value " << value << " for key 20" << std::endl;
    }
    else
    {
        std::cout << "Did not find value  for key 20" << std::endl;
    }
}

void testSingleThread()
{
    //Single threaded test with keys as std::string and integer
    testSingleThreadStringKey();
    testSingleThreadIntegerKey();   
}

void testMultiThreadIntegerKey_Func1(CTSL::HashMap<int, int> &integerMap)
{
    std::cout << "Entering thread 1" << std::endl;
    integerMap.insert(10, 200);
    integerMap.insert(20, 670);
    integerMap.insert(15, 203);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int value;
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    if(integerMap.find(25, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 25 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 25 in HashMap " << &integerMap  << std::endl;
    }
    integerMap.insert(20, 680);
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 20 in HashMap " << &integerMap  << std::endl;
    }
    
    integerMap.erase(20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    integerMap.insert(20, 8680);
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    integerMap.clear();
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 1: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 1: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }
}

void testMultiThreadIntegerKey_Func2(CTSL::HashMap<int, int> &integerMap)
{
    std::cout << "Entering thread 2" << std::endl;
    integerMap.insert(10, 2002);
    integerMap.insert(20, 6702);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    integerMap.insert(25, 2035);
    integerMap.insert(250, 2035);

    int value;
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    if(integerMap.find(25, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 25 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 25 in HashMap " << &integerMap << std::endl;
    }
    integerMap.insert(20, 6876);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 20 in HashMap " << &integerMap <<std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }
    
    integerMap.erase(20);
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    integerMap.insert(20, 10005);
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }

    integerMap.clear();
    if(integerMap.find(20, value))
    {
        std::cout << "Thread 2: Found value " << value << " for key 20 in HashMap " << &integerMap << std::endl;
    }
    else
    {
        std::cout << "Thread 2: Did not find value  for key 20 in HashMap " << &integerMap << std::endl;
    }
}

int main()
{
    testSingleThread(); //Single threaded test  
    
    //Multi threaded test with two threads
    CTSL::HashMap<int, int> integerMap;
    std::thread firstThread(testMultiThreadIntegerKey_Func1, ref(integerMap));
    std::thread secondThread(testMultiThreadIntegerKey_Func2, ref(integerMap));

    firstThread.join();
    secondThread.join();

    return 0;

}

