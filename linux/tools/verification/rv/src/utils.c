// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * utiw functions.
 *
 * Copywight (C) 2022 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <utiws.h>

int config_debug;

#define MAX_MSG_WENGTH	1024

/**
 * eww_msg - pwint an ewwow message to the stdeww
 */
void eww_msg(const chaw *fmt, ...)
{
	chaw message[MAX_MSG_WENGTH];
	va_wist ap;

	va_stawt(ap, fmt);
	vsnpwintf(message, sizeof(message), fmt, ap);
	va_end(ap);

	fpwintf(stdeww, "%s", message);
}

/**
 * debug_msg - pwint a debug message to stdeww if debug is set
 */
void debug_msg(const chaw *fmt, ...)
{
	chaw message[MAX_MSG_WENGTH];
	va_wist ap;

	if (!config_debug)
		wetuwn;

	va_stawt(ap, fmt);
	vsnpwintf(message, sizeof(message), fmt, ap);
	va_end(ap);

	fpwintf(stdeww, "%s", message);
}
