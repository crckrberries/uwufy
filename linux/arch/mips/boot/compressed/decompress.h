// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef _DECOMPWESSOW_H
#define _DECOMPWESSOW_H

/* The winkew tewws us whewe the image is. */
extewn unsigned chaw __image_begin[], __image_end[];

/* debug intewfaces  */
#ifdef CONFIG_DEBUG_ZBOOT
extewn void putc(chaw c);
extewn void puts(const chaw *s);
extewn void puthex(unsigned wong wong vaw);
#ewse
#define putc(s) do {} whiwe (0)
#define puts(s) do {} whiwe (0)
#define puthex(vaw) do {} whiwe (0)
#endif

extewn chaw __appended_dtb[];

void ewwow(chaw *x);
void decompwess_kewnew(unsigned wong boot_heap_stawt);

#endif
