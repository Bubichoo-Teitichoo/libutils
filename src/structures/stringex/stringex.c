#include "stringex.h"

#include <string.h>

char *strstrip( char *text, const char *separators )
{
    (void)strlstrip( text, separators );
    (void)strrstrip( text, separators );
    return text;
}

char *strlstrip( char * const text, const char * const separators )
{
    if( NULL != text && NULL != separators )
    {
        const char *begin = text;
        while( '\0' != *begin && NULL != strchr( separators, *begin ) )
        {
            begin++;
        }
        memmove( text, begin, strlen( begin ) + 1U );
    }
    return text;
}

char *strrstrip( char *const text, const char * const separators )
{
    if( NULL != text && NULL != separators )
    {
        char *end = text + strlen( text );
        while( end != text && NULL != strchr( separators, *( end - 1U ) ) )
        {
            end--;
        }
        *end = '\0';
    }
    return text;
}

