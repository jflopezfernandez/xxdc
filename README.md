
# Introduction

This is a rewrite of the xxd utility written by Juergen Weigert. The original
program is still awesome, but with the passage of time the code has become
needlessly arcane.

The original source includes special handlers for compiling on Microsoft Visual
Studio, Unix, VAX, Amiga, etc., and it even contains a table for handling EBCDIC
to ASCII conversions. (If you don't know what EBCDIC is, thank you for proving
my point.)

For this reason, I felt a rewrite was definitely in order. The current version
makes no special provisions for any operating system whatsoever, relying solely
on standard C for all operations.

> Note: Windows users may have to use `#define _CRT_SECURE_NO_WARNINGS`

# Usage

Like the original xxd, xxdc is a command-line utility that prints a hex and
ASCII view of an input file. If you're familiar with the HxD program on Windows,
it's basically the same thing, with much less features and on a terminal.

```bash
[jflopezfernandez@MAN02 xxdc]$ ./xxdc xxdc | head
00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
00000010: 0300 3e00 0100 0000 f012 0000 0000 0000  ..>.............
00000020: 4000 0000 0000 0000 083c 0000 0000 0000  @........<......
00000030: 0000 0000 4000 3800 0b00 4000 1d00 1c00  ....@.8...@.....
00000040: 0600 0000 0400 0000 4000 0000 0000 0000  ........@.......
00000050: 4000 0000 0000 0000 4000 0000 0000 0000  @.......@.......
00000060: 6802 0000 0000 0000 6802 0000 0000 0000  h.......h.......
00000070: 0800 0000 0000 0000 0300 0000 0400 0000  ................
00000080: a802 0000 0000 0000 a802 0000 0000 0000  ................
00000090: a802 0000 0000 0000 1c00 0000 0000 0000  ................
```

# Caveats

The rewrite is a work in progress and pull requests are welcome. Keep in mind
that while xxdc will output exactly the same thing as xxd in the `en-US` locale
provided you called xxd with no options, xxd has infinitely more features than
xxdc in its current form, and xxdc should only be considered a replacement in
the most basic situations at the moment.

# External Links

The source for the original xxd utility may be found [here](https://github.com/vim/vim/blob/master/src/xxd/xxd.c).

# Additional Notes

Juergen Weigert was awesome and released his utility under the GPL 2, which
was at the time the most recent version of the GNU General Public License. I am
releasing this rewritten version under the GPLv3, as it has been [updated](https://www.gnu.org/licenses/rms-why-gplv3.en.html) to solve
some problems with the GPLv2.
