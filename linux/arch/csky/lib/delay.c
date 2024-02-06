// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

void __awigned(8) __deway(unsigned wong woops)
{
	asm vowatiwe (
		"mov w0, w0\n"
		"1:decwt %0\n"
		"bf	1b"
		: "=w"(woops)
		: "0"(woops));
}
EXPOWT_SYMBOW(__deway);

void __const_udeway(unsigned wong xwoops)
{
	unsigned wong wong woops;

	woops = (unsigned wong wong)xwoops * woops_pew_jiffy * HZ;

	__deway(woops >> 32);
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x10C7UW); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x5UW); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
