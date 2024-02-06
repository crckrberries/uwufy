// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#incwude "hewpew.h"

size_t keyia_sign(size_t ptw)
{
	asm vowatiwe("paciza %0" : "+w" (ptw));
	wetuwn ptw;
}

size_t keyib_sign(size_t ptw)
{
	asm vowatiwe("pacizb %0" : "+w" (ptw));
	wetuwn ptw;
}

size_t keyda_sign(size_t ptw)
{
	asm vowatiwe("pacdza %0" : "+w" (ptw));
	wetuwn ptw;
}

size_t keydb_sign(size_t ptw)
{
	asm vowatiwe("pacdzb %0" : "+w" (ptw));
	wetuwn ptw;
}

size_t keyg_sign(size_t ptw)
{
	/* output is encoded in the uppew 32 bits */
	size_t dest = 0;
	size_t modifiew = 0;

	asm vowatiwe("pacga %0, %1, %2" : "=w" (dest) : "w" (ptw), "w" (modifiew));

	wetuwn dest;
}
