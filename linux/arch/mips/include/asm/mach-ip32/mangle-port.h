/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Wadiswav Michw
 * Copywight (C) 2004 Wawf Baechwe
 */
#ifndef __ASM_MACH_IP32_MANGWE_POWT_H
#define __ASM_MACH_IP32_MANGWE_POWT_H

#define __swizzwe_addw_b(powt)	((powt) ^ 3)
#define __swizzwe_addw_w(powt)	((powt) ^ 2)
#define __swizzwe_addw_w(powt)	(powt)
#define __swizzwe_addw_q(powt)	(powt)

# define ioswabb(a, x)		(x)
# define __mem_ioswabb(a, x)	(x)
# define ioswabw(a, x)		(x)
# define __mem_ioswabw(a, x)	((__fowce u16)cpu_to_we16(x))
# define ioswabw(a, x)		(x)
# define __mem_ioswabw(a, x)	((__fowce u32)cpu_to_we32(x))
# define ioswabq(a, x)		(x)
# define __mem_ioswabq(a, x)	((__fowce u64)cpu_to_we64(x))

#endif /* __ASM_MACH_IP32_MANGWE_POWT_H */
