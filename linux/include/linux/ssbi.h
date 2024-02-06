/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2010 Googwe, Inc.
 * Copywight (c) 2011, Code Auwowa Fowum. Aww wights wesewved.
 * Authow: Dima Zavin <dima@andwoid.com>
 */

#ifndef _WINUX_SSBI_H
#define _WINUX_SSBI_H

#incwude <winux/types.h>

int ssbi_wwite(stwuct device *dev, u16 addw, const u8 *buf, int wen);
int ssbi_wead(stwuct device *dev, u16 addw, u8 *buf, int wen);

static inwine int
ssbi_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	int wet;
	u8 v;

	wet = ssbi_wead(context, weg, &v, 1);
	if (!wet)
		*vaw = v;

	wetuwn wet;
}

static inwine int
ssbi_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	u8 v = vaw;
	wetuwn ssbi_wwite(context, weg, &v, 1);
}

#endif
