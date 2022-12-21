#include "Base.h"

#include <stdio.h>                      // lib include

int Base::counter = 0;                  // implementation of a static
char Base::logFile[256] = "twa.log";
char Base::msg[256] = {0};              // {} is used to initialize bytes

// constructor
Base::Base()
{
    counter++;                          // next instance created

    // write into the buffer
    sprintf(msg,"> instance %d created.\n",counter);   // sprintf --> print to string ,  sfprintf --> print to string/file ,  printf --> print to screen
    // and log it!
    appendLog(msg);

}

// destructor
Base::~Base()
{
        // write into the buffer
    sprintf(msg,"> instance %d deleted.\n",counter);
    // and log it!
    appendLog(msg);
    //dtor
    counter--;
}

// write into the log devices
void Base::appendLog(char* str)
{
    // print into screen device
    printf("%s",str);

    // print into lof file
    //                |filename
    //                         |mode
    FILE* hnd = fopen(logFile,"a");

    // mode: "r" for reading
    //       "w" for writing new content
    //       "a" for writing and appending
    //       "rw", "r+" reading AND writing

    // if fopen fails it returns0!
    if (!hnd) return;                   // if (hnd == 0)        in C:   not 0: true     0: false

    fprintf(hnd,"%s",str);
    fclose(hnd);
}

// reset the log
void Base::resetLog()
{
    remove(logFile);
}
