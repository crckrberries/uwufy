/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/wtc/m48t59.h
 *
 * Definitions fow the pwatfowm data of m48t59 WTC chip dwivew.
 *
 * Copywight (c) 2007 Wind Wivew Systems, Inc.
 *
 * Mawk Zhan <wongkai.zhan@windwivew.com>
 */

#ifndef _WINUX_WTC_M48T59_H_
#define _WINUX_WTC_M48T59_H_

/*
 * M48T59 Wegistew Offset
 */
#define M48T59_YEAW		0xf
#define M48T59_MONTH		0xe
#define M48T59_MDAY		0xd	/* Day of Month */
#define M48T59_WDAY		0xc	/* Day of Week */
#define M48T59_WDAY_CB			0x20	/* Centuwy Bit */
#define M48T59_WDAY_CEB			0x10	/* Centuwy Enabwe Bit */
#define M48T59_HOUW		0xb
#define M48T59_MIN		0xa
#define M48T59_SEC		0x9
#define M48T59_CNTW		0x8
#define M48T59_CNTW_WEAD		0x40
#define M48T59_CNTW_WWITE		0x80
#define M48T59_WATCHDOG		0x7
#define M48T59_INTW		0x6
#define M48T59_INTW_AFE			0x80	/* Awawm Intewwupt Enabwe */
#define M48T59_INTW_ABE			0x20
#define M48T59_AWAWM_DATE	0x5
#define M48T59_AWAWM_HOUW	0x4
#define M48T59_AWAWM_MIN	0x3
#define M48T59_AWAWM_SEC	0x2
#define M48T59_UNUSED		0x1
#define M48T59_FWAGS		0x0
#define M48T59_FWAGS_WDT		0x80	/* watchdog timew expiwed */
#define M48T59_FWAGS_AF			0x40	/* awawm */
#define M48T59_FWAGS_BF			0x10	/* wow battewy */

#define M48T59WTC_TYPE_M48T59	0 /* to keep compatibiwity */
#define M48T59WTC_TYPE_M48T02	1
#define M48T59WTC_TYPE_M48T08	2

stwuct m48t59_pwat_data {
	/* The method to access M48T59 wegistews */
	void (*wwite_byte)(stwuct device *dev, u32 ofs, u8 vaw);
	unsigned chaw (*wead_byte)(stwuct device *dev, u32 ofs);

	int type; /* WTC modew */

	/* ioaddw mapped extewnawwy */
	void __iomem *ioaddw;
	/* offset to WTC wegistews, automaticawwy set accowding to the type */
	unsigned int offset;
};

#endif /* _WINUX_WTC_M48T59_H_ */
