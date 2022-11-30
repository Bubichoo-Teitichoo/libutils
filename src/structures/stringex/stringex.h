#if !defined( __STRINGEX_H__ )
#define __STRINGEX_H__

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
/// @param[in]		separators  null terminated list of characters to remove from @p string
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
/// @param[in]		separators  null terminated list of characters to remove from @p string
///
/// @retval char* @string
char *strstripl( char *text, const char *separators );

/// @brief Remove unwanted characters from end of a string.
///
/// @note: This function alters the input string. If you dont want to alter
///        the input consider using strdup_strip() oder strcpy_strip() instead.
///
/// @param[in,out]	string		String you want to remove unwanted character from
/// @param[in]		separators  null terminated list of characters to remove from @p string
///
/// @retval char* @p string
char *strstripr( char *text, const char *separators );

/// @brief Create a heap allocated copy of the given string and remove unwanted characters from begin and end.
///
/// The function will first create a duplicate of the string and then use strstrip()
/// to remove the unwanted characters.
///
/// @param[in] string		String you want to copy and strip
/// @param[in] separator	null terminated list of characters to remove from @p string
///
/// @retval NULL	if @p string is NULL or strdup() fails
/// @retval char*	pointer to the newly allocated string
char *strdup_strip( const char *string, const char *separator );

/// @brief Create a heap allocated copy of the given string and remove unwanted characters from the begin.
///
/// The function will first create a duplicate of the string and then use strstripl()
/// to remove the unwanted characters.
///
/// @param[in] string		String you want to copy and strip
/// @param[in] separator	null terminated list of characters to remove from @p string
///
/// @retval NULL	if @p string is NULL or strdup() fails
/// @retval char*	pointer to the newly allocated string
char *strdup_stripl( const char *string, const char *separator );

/// @brief Create a heap allocated copy of the given string and remove unwanted characters from the end.
///
/// The function will first create a duplicate of the string and then use strstripr()
/// to remove the unwanted characters.
///
/// @param[in] string		String you want to copy and strip
/// @param[in] separator	null terminated list of characters to remove from @p string
///
/// @retval NULL	if @p string is NULL or strdup() fails
/// @retval char*	pointer to the newly allocated string
char *strdup_stripr( const char *string, const char *separator );

/// 
/// @brief Copy a stripped version of @p string to @dest
/// 
/// @param[in,out]	dest		buffer the stripped version of @p string is 
///								copied to
/// @param[in]		len			maximum character to copy to @dest
/// @param[in]		string		null terminated string you want to copy and strip.
/// @param[in]		separator	null terminated list of characters that shall 
///								be remove from @p string
/// 
/// @returns	the maximum amount of character that would have been written
///				including the null terminator if @p dest was NULL or @p len was 0
/// @returns	the number of characters that where written including the null
///				terminator to @p dest but at most len
/// 
size_t strcpy_strip( char *dest, const size_t len, const char *string, const char *separator );
size_t strcpy_stripl( char *dest, const size_t len, const char *string, const char *separator );
size_t strcpy_stripr( char *dest, const size_t len, const char *string, const char *separator );

char *strdup_format( const char *fmt, ... );
char *strdup_vaformat( const char *fmt, va_list ap );

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
int string_stripr( string_t *string, const char *sep );
int string_stripl( string_t *string, const char *sep );

int string_split( const string_t *string, string_t **dest, size_t *len );

#endif   // __STRINGEX_H__
