
#include "elf.h"

/** This is the C-string null terminator, represented by the hex value 0x00. It
 *  is explicitly defined, rather than using 0 or NULL, for the purpose of
 *  semantic clarity.
 * 
 */
#define NUL '\0'

/** This is the entry point of the program. There are as of yet no options for
 *  the user to customize or configure the execution of the program. The program
 *  simply expects at least one filename to process.
 * 
 */
int main(int argc, const char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "No input(s).\n");
        exit(EXIT_FAILURE);
    }

    while (*++argv) {
        /** The input file is opened via a call to the open_input_file function,
         *  which is a wrapper around the fopen function call. This interface
         *  includes the necessary error checking and mode arguments to ensure
         *  program execution proceeds if and only if the call to fopen is
         *  successful.
         * 
         */
        FILE* input_file = open_input_file(*argv);

        /** This counter is used to print the current line's offset at the
         *  beginning of every line. It is incremented on every character read.
         * 
         */
        size_t total_characters_read = 0;

        /** The file's hex output should be printed in lines of eight columns,
         *  each consisting of four ASCII characters. Since each byte of the
         *  file is being converted to two ASCII characters, each four character
         *  column really represents two bytes in the original binary.
         * 
         */
        size_t characters_in_current_column = 0;

        /** This buffer keeps track of the characters read into the current
         *  line. Without a buffer, we would have to use fseek to rewind to the
         *  start of the current line and reread the input, which is not just
         *  needlessly complicated, but would also render the standard library's
         *  IO buffering completely useless, as there is no way to buffer that
         *  without doing this.
         * 
         */
        int line_buffer[16];

        /** This pointer is used to iterate through the line buffer without
         *  having to resort to a while or a for loop.
         * 
         */
        int* buffer_position_pointer = line_buffer;

        /* Clear the line buffer */
        memset(line_buffer, 0, 16 * sizeof (int));

        while (TRUE) {
            /** The program should print only sixteen bytes per row, in columns
             *  of two bytes each. Once we hit the end of a line, as indicated
             *  by the total_characters_read variable being evenly divisible by
             *  16, we iterate through the line buffer, printing out the ASCII
             *  version of the binary file.
             * 
             */
            if (total_characters_read % 16 == 0) {
                /** Only iterate through the line buffer and print a newline if
                 *  we have already read characters from the file.
                 * 
                 */
                if (total_characters_read) {
                    /* Print column and ASCII view separator */
                    putc(' ', stdout);

                    /** Iterate through the line buffer and print out the ASCII
                     *  equivalent values of the contents therein.
                     * 
                     */
                    for (size_t i = 0; i < 16; ++i) {
                        if (isspace(line_buffer[i])) {
                            putc('.', stdout);
                        } else if (isgraph(line_buffer[i])) {
                            putc(line_buffer[i], stdout);
                        } else {
                            putc('.', stdout);
                        }
                    }

                    /* Print newline character to terminate the current line */
                    putc('\n', stdout);
                }

                /** This will print the current offset of the next line, as you
                 *  would see in programs like xxd or objdump.
                 * 
                 */
                printf("%08lx: ", total_characters_read);

                /* Clear the line buffer */
                memset(line_buffer, 0, 16 * sizeof (int));

                /* Reset the buffer position pointer */
                buffer_position_pointer = line_buffer;
            }

            /** This is the character at the current head of the input stream.
             * 
             */
            int current_character = fgetc(input_file);

            /** Break out of the processing loop once we hit the end of the
             *  current input file. Some systems, particulary Linux, are kind
             *  of weird about the final newline, sometimes allowing the
             *  console prompt to be printed in the middle of a line. This looks
             *  weird and is mostly just annoying, so print a final newline char
             *  just in case.
             * 
             */
            if (current_character == EOF) {
                putc('\n', stdout);

                break;
            }

            /** If the current character was not the end of file marker, add it
             *  to the input buffer.
             * 
             */
            *buffer_position_pointer++ = current_character;

            /* Print the hexadecimal version of the current character */
            printf("%02x", current_character);

            /* Increment the number of characters in the current column */
            ++characters_in_current_column;

            /** Characters in hexadecimal should be printed in groups of two for
             *  a total of four characters per column. This is the check that
             *  makes that magic happen.
             * 
             */
            if (characters_in_current_column == 2) {
                /* Print the column separator */
                putc(' ', stdout);

                /* Reset the column's character count */
                characters_in_current_column = 0;
            }

            /* Increment the total number of characters read */
            ++total_characters_read;
        }

        /** Some platforms are kind of weird about final newlines. Windows will
         *  always print a final newline in cmd, but linux will allow the
         *  console prompt to start in the middle of a line, which is just
         *  annoying. Print a final newline character to prevent this from
         *  happening.
         * 
         */
        putc('\n', stdout);

        /** Each input file is closed via a call to the close_file interface,
         *  which is simply a wrapper around the fclose function. As the
         *  close_file documentation will attest, the return value of fclose is
         *  rarely checked, so this wrapper was written to still not have to
         *  check the return value without risking an error going unnoticed.
         * 
         */
        close_file(input_file);
    }

    return EXIT_SUCCESS;
}
