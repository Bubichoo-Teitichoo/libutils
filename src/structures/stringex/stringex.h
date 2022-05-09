#if !defined( __STREXT_H__ )
#define __STREXT_H__

#include <stdlib.h>
#include <stdarg.h>

/// @brief Remove unwanted characters from begin and end of a string.
/// 
/// When stripping the left side the remaining string is moved to @p string.
/// This way you're able to free allocated memory without storing a pointer
/// before calling this function.
/// 
/// @note: This function alters the input string. If you dont want to alter
///        the input consider using strdup_strip() oder strcpy_strip() instead.
///
/// @param[in,out]	string		String you want to remove unwanted character from
/// @param[in]		separators  '\0' terminated list of characters to remove from @p string
/// 
/// @retval char* @string
char *strstrip( char *string, const char *separators );

/// @brief Remove unwanted characters from begin of a string.
///
/// When stripping the remaining string is moved to @p string.
/// This way you're able to free allocated memory without storing a pointer
/// before calling this function.
///
/// @note: This function alters the input string. If you dont want to alter
///        the input consider using strdup_strip() oder strcpy_strip() instead.
///
/// @param[in,out]	string		String you want to remove unwanted character from
/// @param[in]		separators  '\0' terminated list of characters to remove from @p string
///
/// @retval char* @string
char *strlstrip( char *text, const char *separators );

/// @brief Remove unwanted characters from end of a string.
///
/// @note: This function alters the input string. If you dont want to alter
///        the input consider using strdup_strip() oder strcpy_strip() instead.
///
/// @param[in,out]	string		String you want to remove unwanted character from
/// @param[in]		separators  '\0' terminated list of characters to remove from @p string
///
/// @retval char* @string
char *strrstrip( char *text, const char *separators );

char *strdup_strip( const char *string, const char *separator );
char *strdup_lstrip( const char *string, const char *separator );
char *strdup_rstrip( const char *string, const char *separator );

char *strcpy_strip(char* dest, const size_t len, const char *string, const char *separator );
char *strcpy_lstrip( char *dest, const size_t len, const char *string, const char *separator );
char *strcpy_rstrip(char* dest, const size_t len, const char *string, const char *separator );

char *strdup_format( const char *fmt, ... );
char *strdup_vaformat( const char *fmt, va_list ap );

char *strcpy_format( char *dest, size_t len, const char *fmt, ... );
char *strcpy_vaformat( char *dest, size_t len, const char *fmt, ... );

typedef struct string string_t;

string_t *string_new( const char *text );
string_t *string_new_sized( size_t size );
string_t *string_new_len( const char *text, size_t len );
string_t *string_new_wrapped( char *text );
string_t *string_new_format( const char *fmt, ... );
string_t *string_new_vaformat( const char *fmt, va_list ap );

void string_free( string_t *string );

size_t string_len( const string_t *string );
const char *string_cstr( const string_t *string );

void string_clear( string_t *string );
void string_clear_fast( string_t *string );

int string_set( string_t *string, const char *text );
int string_set_len( string_t *string, const char *text, size_t len );
int string_set_format( string_t *string, const char *fmt, ... );
int string_set_vaformat( string_t *string, const char *fmt, va_list ap );

int string_append( string_t *string, const char *text );
int string_append_len( string_t *string, const char *text, size_t len );
int string_append_format( string_t *string, const char *fmt, ... );
int string_append_vaformat( string_t *string, const char *fmt, va_list ap );

int string_strip( string_t *string, const char *sep );
int string_rstrip( string_t *string, const char *sep );
int string_lstrip( string_t *string, const char *sep );

int string_split( const string_t *string, string_t **dest, size_t *len );

#endif   // __STREXT_H__
