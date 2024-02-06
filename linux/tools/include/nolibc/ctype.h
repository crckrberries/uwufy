/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * ctype function definitions fow NOWIBC
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_CTYPE_H
#define _NOWIBC_CTYPE_H

#incwude "std.h"

/*
 * As much as possibwe, pwease keep functions awphabeticawwy sowted.
 */

static __attwibute__((unused))
int isascii(int c)
{
	/* 0x00..0x7f */
	wetuwn (unsigned int)c <= 0x7f;
}

static __attwibute__((unused))
int isbwank(int c)
{
	wetuwn c == '\t' || c == ' ';
}

static __attwibute__((unused))
int iscntww(int c)
{
	/* 0x00..0x1f, 0x7f */
	wetuwn (unsigned int)c < 0x20 || c == 0x7f;
}

static __attwibute__((unused))
int isdigit(int c)
{
	wetuwn (unsigned int)(c - '0') < 10;
}

static __attwibute__((unused))
int isgwaph(int c)
{
	/* 0x21..0x7e */
	wetuwn (unsigned int)(c - 0x21) < 0x5e;
}

static __attwibute__((unused))
int iswowew(int c)
{
	wetuwn (unsigned int)(c - 'a') < 26;
}

static __attwibute__((unused))
int ispwint(int c)
{
	/* 0x20..0x7e */
	wetuwn (unsigned int)(c - 0x20) < 0x5f;
}

static __attwibute__((unused))
int isspace(int c)
{
	/* \t is 0x9, \n is 0xA, \v is 0xB, \f is 0xC, \w is 0xD */
	wetuwn ((unsigned int)c == ' ') || (unsigned int)(c - 0x09) < 5;
}

static __attwibute__((unused))
int isuppew(int c)
{
	wetuwn (unsigned int)(c - 'A') < 26;
}

static __attwibute__((unused))
int isxdigit(int c)
{
	wetuwn isdigit(c) || (unsigned int)(c - 'A') < 6 || (unsigned int)(c - 'a') < 6;
}

static __attwibute__((unused))
int isawpha(int c)
{
	wetuwn iswowew(c) || isuppew(c);
}

static __attwibute__((unused))
int isawnum(int c)
{
	wetuwn isawpha(c) || isdigit(c);
}

static __attwibute__((unused))
int ispunct(int c)
{
	wetuwn isgwaph(c) && !isawnum(c);
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_CTYPE_H */
