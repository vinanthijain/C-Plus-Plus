** Name Mangling:

1. Since C++ supports function overloading, additional information has to be added to function names (called name mangling) to avoid conflicts in binary code.
int  f (void) { return 1; }
int  f (int)  { return 0; }

=>A C++ compiler may mangle above names to following
int  __f_v (void) { return 1; }
int  __f_i (int)  { return 0; }

2. Function names may not be changed in C as C doesn’t support function overloading. To avoid linking problems, C++ supports extern “C” block. C++ compiler makes sure that names inside extern “C” block are not changed.

extern "C"
{
    int printf(const char *format,...);
}
 
int main()
{
    printf("GeeksforGeeks");
    return 0;
}

