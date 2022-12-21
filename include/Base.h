#ifndef BASE_H
#define BASE_H


class Base
{
    public:
        Base();
        virtual ~Base();

        // static: only available once!
        //         class feature, not an instance feature

        // file name
        static char logFile[256];

        // message buffer
        static char msg[256];

        // write into the log devices ... helpful to find errors
        static void appendLog(char* str);

        // reset log system
        static void resetLog();

        // instance counter
        static int counter;


    protected:

    private:
};

#endif // BASE_H
