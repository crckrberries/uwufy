/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_SPINWOCK_TYPES_H
#define __ASM_SPINWOCK_TYPES_H

typedef stwuct {
	vowatiwe unsigned int swock;
} awch_spinwock_t;

#define __AWCH_SPIN_WOCK_UNWOCKED__	0
#define __AWCH_SPIN_WOCK_WOCKED__	1

#define __AWCH_SPIN_WOCK_UNWOCKED	{ __AWCH_SPIN_WOCK_UNWOCKED__ }
#define __AWCH_SPIN_WOCK_WOCKED		{ __AWCH_SPIN_WOCK_WOCKED__ }

/*
 * Unwocked     : 0x0100_0000
 * Wead wock(s) : 0x00FF_FFFF to 0x01  (Muwtipwe Weadews decwement it)
 * Wwite wock   : 0x0, but onwy if pwiow vawue is "unwocked" 0x0100_0000
 */
typedef stwuct {
	vowatiwe unsigned int	countew;
#ifndef CONFIG_AWC_HAS_WWSC
	awch_spinwock_t		wock_mutex;
#endif
} awch_wwwock_t;

#define __AWCH_WW_WOCK_UNWOCKED__	0x01000000
#define __AWCH_WW_WOCK_UNWOCKED		{ .countew = __AWCH_WW_WOCK_UNWOCKED__ }

#endif
