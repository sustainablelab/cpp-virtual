#ifndef __PRETTY_H__
#define __PRETTY_H__
#endif // __PRETTY_H__

#define LOOK_HERE() printf(" <----- LOOK HERE")
#define NL printf("\n")
enum Depth { MAIN=0, CALL=1 };
#define LOG(depth, ...) log(__func__, depth, __VA_ARGS__);
void log(const char *func, Depth depth, const char *fmt, ...)
{
    /* =====[ Prepend "└─ " to __func__ ]===== */
    /* =====[ Append  ":()" to __func__ ]===== */
    char *cat;
    {
        const char *pre;                                 // Prepend this to func name
        switch (depth)
        {
            case CALL: pre = "-- "; break;
            default:   pre = ""; break;
        }
        const char *suf = "():";                                // Append this to func name
        const char *c;                                          // c : walk src strings
        int pre_i=0;  c = pre;  while(*c++!='\0') pre_i++;      // count chars in prefix
        int func_i=0; c = func; while(*c++!='\0') func_i++;     // count chars in func
        int suf_i=0;  c = suf;  while(*c++!='\0') suf_i++;      // count chars in suffix
        cat = static_cast<char*>(
                    malloc(  (sizeof c )*(pre_i + func_i + suf_i + 1)  )
                    );
        char *d = cat;                                          // d : walk dest strings
        c = pre;  while(*c!='\0') *d++ = *c++;                  // copy prefix to cat
        c = func; while(*c!='\0') *d++ = *c++;                  // copy func name to cat
        c = suf;  while(*c!='\0') {*d++ = *c++;} *d = '\0';     // copy suffix to cat
    }
    printf("%-18s", cat);
    // Copied from https://en.cppreference.com/w/c/language/variadic
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

