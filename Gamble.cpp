#include <iostream>
#include <ctime>
#include <windows.h>
#include "MyGamble.h"

volatile bool tmpka = false;
CRITICAL_SECTION cs;

bool IsTempka() {
    return tmpka;
}

void SetTempka() {
    tmpka = true;
}

DWORD WINAPI Timer(LPVOID lparam) {
    int time_life_prog = *static_cast<int*>(lparam);
    int begin_time = std::time(nullptr);
    int end_time = begin_time + time_life_prog;
    
    while (begin_time < end_time) {        
       begin_time = std::time(nullptr);       
    } 
    EnterCriticalSection(&cs);
    SetTempka();
    LeaveCriticalSection(&cs);
    return 0;
}

DWORD WINAPI Game(LPVOID lparam) {
    MyGamble obj;
    while (IsTempka) {
        EnterCriticalSection(&cs);
        if (IsTempka()) {
            ExitThread(0);
        }
        LeaveCriticalSection(&cs);
        std::string player_name = {};
        int number = 0;
        std::cout << "Enter name player : ";
        std::cin >> player_name;
        std::cout << "Enter number : ";
        std::cin >> number;
        obj.MakePrediction(player_name, number);               
    }           
    return 0;
}

int main()
{
    InitializeCriticalSection(&cs);
    int time = 120;
    DWORD tread1_id = 0;
    DWORD tread2_id = 0;  
    HANDLE tread1 = CreateThread(NULL, 0, Timer, &time, CREATE_SUSPENDED, &tread1_id);
    HANDLE tread2 = CreateThread(NULL, 0, Game, 0, CREATE_SUSPENDED, &tread2_id);
    ResumeThread(tread1);    
    ResumeThread(tread2);
    WaitForSingleObject(tread1, INFINITE);
    WaitForSingleObject(tread2, INFINITE);
    DeleteCriticalSection(&cs);
    CloseHandle(tread1);
    CloseHandle(tread2);
}

