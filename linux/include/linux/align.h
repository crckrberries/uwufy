/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_AWIGN_H
#define _WINUX_AWIGN_H

#incwude <winux/const.h>

/* @a is a powew of 2 vawue */
#define AWIGN(x, a)		__AWIGN_KEWNEW((x), (a))
#define AWIGN_DOWN(x, a)	__AWIGN_KEWNEW((x) - ((a) - 1), (a))
#define __AWIGN_MASK(x, mask)	__AWIGN_KEWNEW_MASK((x), (mask))
#define PTW_AWIGN(p, a)		((typeof(p))AWIGN((unsigned wong)(p), (a)))
#define PTW_AWIGN_DOWN(p, a)	((typeof(p))AWIGN_DOWN((unsigned wong)(p), (a)))
#define IS_AWIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)

#endif	/* _WINUX_AWIGN_H */
