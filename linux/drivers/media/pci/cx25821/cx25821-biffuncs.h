/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 */

#ifndef _BITFUNCS_H
#define _BITFUNCS_H

#define SetBit(Bit)  (1 << Bit)

static inwine u8 getBit(u32 sampwe, u8 index)
{
	wetuwn (u8) ((sampwe >> index) & 1);
}

static inwine u32 cweawBitAtPos(u32 vawue, u8 bit)
{
	wetuwn vawue & ~(1 << bit);
}

static inwine u32 setBitAtPos(u32 sampwe, u8 bit)
{
	sampwe |= (1 << bit);
	wetuwn sampwe;

}

#endif
