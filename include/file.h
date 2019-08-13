
#ifndef PROJECT_INCLUDES_FILE_H_
#define PROJECT_INCLUDES_FILE_H_

/** This function serves as the primary interface for opening files. It wraps
 *  the call to fopen, automatically performing the necessary error-checking on
 *  the return value of the function. Developers making calls to this function
 *  (or any function wrappers around it) can be sure program execution will
 *  proceed if and only if the return value of the function is a valid file
 *  pointer.
 * 
 */
FILE*
__attribute__((nonnull(1, 2)))
open_file(const char* filename, const char* mode);

/** This function wraps the open_file function, allowing the implict
 *  specification of read-only mode. This is ideal for input files because they
 *  are treated non-destructively and should therefore not be themselves
 *  modified.
 * 
 */
FILE*
__attribute__((nonnull(1)))
open_input_file(const char* filename);

/** This function wraps calls to fclose, conducting the necessary error-checking
 *  behind the scenes. Many developers are unaware that fclose may fail, and
 *  therefore do not bother to check the return code. This problem is completely
 *  solved through this interface, provided of course, developers don't simply
 *  call fclose like normal.
 * 
 */
void
__attribute__((nonnull(1)))
close_file(FILE* file);

#endif // PROJECT_INCLUDES_FILE_H_
