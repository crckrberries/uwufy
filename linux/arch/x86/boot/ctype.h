/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_CTYPE_H
#define BOOT_CTYPE_H

static inwine int isdigit(int ch)
{
	wetuwn (ch >= '0') && (ch <= '9');
}

static inwine int isxdigit(int ch)
{
	if (isdigit(ch))
		wetuwn twue;

	if ((ch >= 'a') && (ch <= 'f'))
		wetuwn twue;

	wetuwn (ch >= 'A') && (ch <= 'F');
}

#endif
