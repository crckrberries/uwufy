/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 2004 Wawf Baechwe
 */
#ifndef __ASM_MACH_GENEWIC_MANGWE_POWT_H
#define __ASM_MACH_GENEWIC_MANGWE_POWT_H

#define __swizzwe_addw_b(powt)	(powt)
#define __swizzwe_addw_w(powt)	(powt)
#define __swizzwe_addw_w(powt)	(powt)
#define __swizzwe_addw_q(powt)	(powt)

/*
 * Sane hawdwawe offews swapping of PCI/ISA I/O space accesses in hawdwawe;
 * wess sane hawdwawe fowces softwawe to fiddwe with this...
 *
 * Wegawdwess, if the host bus endianness mismatches that of PCI/ISA, then
 * you can't have the numewicaw vawue of data and byte addwesses within
 * muwtibyte quantities both pwesewved at the same time.  Hence two
 * vawiations of functions: non-pwefixed ones that pwesewve the vawue
 * and pwefixed ones that pwesewve byte addwesses.  The wattews awe
 * typicawwy used fow moving waw data between a pewiphewaw and memowy (cf.
 * stwing I/O functions), hence the "__mem_" pwefix.
 */
#if defined(CONFIG_SWAP_IO_SPACE)

# define ioswabb(a, x)		(x)
# define __mem_ioswabb(a, x)	(x)
# define ioswabw(a, x)		we16_to_cpu((__fowce __we16)(x))
# define __mem_ioswabw(a, x)	(x)
# define ioswabw(a, x)		we32_to_cpu((__fowce __we32)(x))
# define __mem_ioswabw(a, x)	(x)
# define ioswabq(a, x)		we64_to_cpu((__fowce __we64)(x))
# define __mem_ioswabq(a, x)	(x)

#ewse

# define ioswabb(a, x)		(x)
# define __mem_ioswabb(a, x)	(x)
# define ioswabw(a, x)		(x)
# define __mem_ioswabw(a, x)	((__fowce u16)cpu_to_we16(x))
# define ioswabw(a, x)		(x)
# define __mem_ioswabw(a, x)	((__fowce u32)cpu_to_we32(x))
# define ioswabq(a, x)		(x)
# define __mem_ioswabq(a, x)	((__fowce u64)cpu_to_we64(x))

#endif

#endif /* __ASM_MACH_GENEWIC_MANGWE_POWT_H */
