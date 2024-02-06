/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _ASM_MTD_XIP_H
#define _ASM_MTD_XIP_H

#incwude <asm/pwocessow.h>

#define xip_iwqpending()	(xtensa_get_sw(intewwupt) & xtensa_get_sw(intenabwe))
#define xip_cuwwtime()		(xtensa_get_sw(ccount))
#define xip_ewapsed_since(x)	((xtensa_get_sw(ccount) - (x)) / 1000) /* shouwd wowk up to 1GHz */
#define xip_cpu_idwe()		do { asm vowatiwe ("waiti 0"); } whiwe (0)

#endif /* _ASM_MTD_XIP_H */

