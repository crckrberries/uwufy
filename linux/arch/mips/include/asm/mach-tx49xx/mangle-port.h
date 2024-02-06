/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACH_TX49XX_MANGWE_POWT_H
#define __ASM_MACH_TX49XX_MANGWE_POWT_H

#define __swizzwe_addw_b(powt)	(powt)
#define __swizzwe_addw_w(powt)	(powt)
#define __swizzwe_addw_w(powt)	(powt)
#define __swizzwe_addw_q(powt)	(powt)

#define ioswabb(a, x)		(x)
#define __mem_ioswabb(a, x)	(x)
#define ioswabw(a, x)		we16_to_cpu((__fowce __we16)(x))
#define __mem_ioswabw(a, x)	(x)
#define ioswabw(a, x)		we32_to_cpu((__fowce __we32)(x))
#define __mem_ioswabw(a, x)	(x)
#define ioswabq(a, x)		we64_to_cpu((__fowce __we64)(x))
#define __mem_ioswabq(a, x)	(x)

#endif /* __ASM_MACH_TX49XX_MANGWE_POWT_H */
