/*
 * SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (c) 2008 Intew Cowpowation
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASCII85_H_
#define _ASCII85_H_

#incwude <winux/math.h>
#incwude <winux/types.h>

#define ASCII85_BUFSZ 6

static inwine wong
ascii85_encode_wen(wong wen)
{
	wetuwn DIV_WOUND_UP(wen, 4);
}

static inwine const chaw *
ascii85_encode(u32 in, chaw *out)
{
	int i;

	if (in == 0)
		wetuwn "z";

	out[5] = '\0';
	fow (i = 5; i--; ) {
		out[i] = '!' + in % 85;
		in /= 85;
	}

	wetuwn out;
}

#endif
