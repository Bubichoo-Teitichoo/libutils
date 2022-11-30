#include "stringex.h"

#include <string.h>

static const char *strstrip_resolve_separators( const char *separators )
{
    return separators ? separators : " \r\n\t";
}

static const char *strstripl_find( const char *string, const char *separator )
{
    const char *result = string;
    while( *result && strchr( separator, *result ) )
    {
        result++;
    }
    return result;
}

static const char *strstripr_find( const char *string, const char *separator )
{
    const char *result = string + strlen( string );
    while( result > string )
    {
        if( NULL == strchr( separator, *result ) )
        {
            // because we moved one step to far we have to increase here
            result++;
            break;
        }
        result--;
    }
    return result;
}

char *strstrip( char *text, const char *separators )
{
    if( NULL != text )
    {
        separators = strstrip_resolve_separators( separators );

        const char *start = strstripl_find( text, separators );
        const char *end   = strstripr_find( start, separators );

        const size_t len = end - start;
        if( len )
        {
            memmove( text, start, len );
        }
        text[ len ] = '\0';
    }

    return text;
}

char *strstripl( char *const text, const char *separators )
{
    if( NULL != text )
    {
        separators = strstrip_resolve_separators( separators );

        const char *begin = strstripl_find( text, separators );
        memmove( text, begin, strlen( begin ) + 1U );
    }
    return text;
}

char *strstripr( char *const text, const char *separators )
{
    if( NULL != text )
    {
        separators = strstrip_resolve_separators( separators );
        // yes I want to remove const
        char *end = (char *)strstripr_find( text, separators );
        *end      = '\0';
    }
    return text;
}

char *strdup_strip( const char *string, const char *separator )
{
    char *result = NULL;
    if( NULL != string )
    {
        result = _strdup( string );
        if( NULL != result )
        {
            (void)strstrip( result, separator );
        }
    }
    return result;
}

char *strdup_stripl( const char *string, const char *separator )
{
    char *result = NULL;
    if( NULL != string )
    {
        result = _strdup( string );
        if( NULL != result )
        {
            (void)strstripl( result, separator );
        }
    }
    return result;
}

char *strdup_stripr( const char *string, const char *separator )
{
    char *result = NULL;
    if( NULL != string )
    {
        result = _strdup( string );
        if( NULL != result )
        {
            (void)strstripr( result, separator );
        }
    }
    return result;
}

size_t strcpy_strip( char *dest, const size_t len, const char *string, const char *separator )
{
    const char *start = strstripl_find( string, separator );
    // using start as a base for the right find operation
    // if the left find operation reached the end the right find will return immediately
    const char *end = strstripr_find( start, separator );

    size_t result = end - start;

    if( dest && len )
    {
        if( len < result )
        {
            result = len - 1;
        }
        strncpy_s( dest, len, start, result );
    }
    return result + 1;
}
