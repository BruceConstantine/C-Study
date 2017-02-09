#ifndef TRACER_H
#define TRACER_H
#include <map>
#include <cstddef>
using namespace std;

class Tracer {
private:
    class Enter{
        public:
            Enter( const char* file = NULL, int line = 0)
                : file_(file), line_(line){

            }
            inline const char * File() const {return file_;}
            inline int Line() const {return line_;}
        private:
            const char * file_;
            int line_;
    };
    static bool Ready;  //if true: had been deleted.
public :
    Tracer(){}
    ~Tracer();
    void addSpyObj(void *pointer , const char* file , int line);
    void removeSpyObj(void *pointer);
    void dump();
    inline static void setStatue(bool inReady){Ready=inReady;}
    inline static bool getStatue(){return Ready;}
private:
    std::map<void *, Enter> pointer_map_;
};

extern Tracer *tracer;

#endif // TRACER_H
