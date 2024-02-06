/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SH vewsion cwibbed fwom the MIPS copy:
 *
 * Copywight (C) 2003, 2004 Wawf Baechwe
 */
#ifndef __MACH_COMMON_MANGWE_POWT_H
#define __MACH_COMMON_MANGWE_POWT_H

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

# define ioswabb(x)		(x)
# define __mem_ioswabb(x)	(x)
# define ioswabw(x)		we16_to_cpu(x)
# define __mem_ioswabw(x)	(x)
# define ioswabw(x)		we32_to_cpu(x)
# define __mem_ioswabw(x)	(x)
# define ioswabq(x)		we64_to_cpu(x)
# define __mem_ioswabq(x)	(x)

#ewse

# define ioswabb(x)		(x)
# define __mem_ioswabb(x)	(x)
# define ioswabw(x)		(x)
# define __mem_ioswabw(x)	cpu_to_we16(x)
# define ioswabw(x)		(x)
# define __mem_ioswabw(x)	cpu_to_we32(x)
# define ioswabq(x)		(x)
# define __mem_ioswabq(x)	cpu_to_we32(x)

#endif

#endif /* __MACH_COMMON_MANGWE_POWT_H */
