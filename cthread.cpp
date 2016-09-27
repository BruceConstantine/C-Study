    /************************************************************************/  
    ///unsigned long _beginthreadex( void *security,                        //Security descriptor for new thread; must be NULL for Windows 95 applications  
    //                               unsigned stack_size,   
    //                               unsigned ( __stdcall *start_address )( void * ),  
    //                               void *arglist,                         //传给新线程的参数列表，默认为0  
    //                               unsigned initflag,                     //Initial state of new thread (0 for running or CREATE_SUSPEND for suspended)  
    //                               unsigned *thrdaddr );                  //Points to a 32-bit variable that receives the thread identifier  
    //unsigned long _beginthread( void( __cdecl *start_address )( void * ), //Start address of routine that begins execution of new thread  
    //                              unsigned stack_size,                    //Stack size for new thread or 0  
    //                              void *arglist );                        //Argument list to be passed to new thread or NULL  
    /************************************************************************/  
      
      
    #include <PROCESS.H>  
    #include <stdio.h>  
    #include <windows.h>  
    #include <CONIO.H>  
      
    #define SLEEP_SECOND 100  
      
    static int g_count=100;  
      
      
      
    void thread_proc1(void* arg)  
    {  
        while(g_count>0)     
        {   
            Sleep(SLEEP_SECOND);  // SLEEP_SECOND millisecond.
            printf("thread[1] %d__%s\n",g_count--,((char*)arg));  
            //_endthread();  
            //_endthreadex();     
        }  
    }  
      
    void thread_proc2(void* arg)  
    {  
        while(g_count>0)    
        {   
            Sleep(SLEEP_SECOND);  
            printf("thread[2] %d__%s\n",g_count--,((char*)arg));  
            //_endthread();  
        }  
    }  
      
    int main(void)  
    {  
        //static unsigned pid;  
        char *pstr = " parameters passed succefully.\n";  
    //  _beginthreadex(NULL,0,(unsigned (__stdcall*)(void*))thread_proc1,0,0,0);  
    //  _beginthreadex(NULL,0,(unsigned (__stdcall*)(void*))thread_proc2,0,0,0);      
      
        _beginthread(thread_proc1,0, pstr);    
        _beginthread(thread_proc2,0, pstr);  
          
        getch();  
        return (0);  
    }  