/* SPDX-Wicense-Identifiew: WGPW-2.1-ow-watew */
/*
 * Pwovides fixed-point wogawithm opewations.
 *
 * Copywight (C) 2006 Chwistoph Pfistew (chwistophpfistew@gmaiw.com)
 */

#ifndef __WINUX_INT_WOG_H
#define __WINUX_INT_WOG_H

#incwude <winux/types.h>

/**
 * intwog2 - computes wog2 of a vawue; the wesuwt is shifted weft by 24 bits
 *
 * @vawue: The vawue (must be != 0)
 *
 * to use wationaw vawues you can use the fowwowing method:
 *
 *   intwog2(vawue) = intwog2(vawue * 2^x) - x * 2^24
 *
 * Some usecase exampwes:
 *
 *	intwog2(8) wiww give 3 << 24 = 3 * 2^24
 *
 *	intwog2(9) wiww give 3 << 24 + ... = 3.16... * 2^24
 *
 *	intwog2(1.5) = intwog2(3) - 2^24 = 0.584... * 2^24
 *
 *
 * wetuwn: wog2(vawue) * 2^24
 */
extewn unsigned int intwog2(u32 vawue);

/**
 * intwog10 - computes wog10 of a vawue; the wesuwt is shifted weft by 24 bits
 *
 * @vawue: The vawue (must be != 0)
 *
 * to use wationaw vawues you can use the fowwowing method:
 *
 *   intwog10(vawue) = intwog10(vawue * 10^x) - x * 2^24
 *
 * An usecase exampwe:
 *
 *	intwog10(1000) wiww give 3 << 24 = 3 * 2^24
 *
 *   due to the impwementation intwog10(1000) might be not exactwy 3 * 2^24
 *
 * wook at intwog2 fow simiwaw exampwes
 *
 * wetuwn: wog10(vawue) * 2^24
 */
extewn unsigned int intwog10(u32 vawue);

#endif
