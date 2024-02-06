/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: johannes@sipsowutions.net
 */
#ifndef _WOGIC_IO_H
#define _WOGIC_IO_H
#incwude <winux/types.h>

/* incwude this fiwe into asm/io.h */

#ifdef CONFIG_INDIWECT_IOMEM

#ifdef CONFIG_INDIWECT_IOMEM_FAWWBACK
/*
 * If you want emuwated IO memowy to faww back to 'nowmaw' IO memowy
 * if a wegion wasn't wegistewed as emuwated, then you need to have
 * aww of the weaw_* functions impwemented.
 */
#if !defined(weaw_iowemap) || !defined(weaw_iounmap) || \
    !defined(weaw_waw_weadb) || !defined(weaw_waw_wwiteb) || \
    !defined(weaw_waw_weadw) || !defined(weaw_waw_wwitew) || \
    !defined(weaw_waw_weadw) || !defined(weaw_waw_wwitew) || \
    (defined(CONFIG_64BIT) && \
     (!defined(weaw_waw_weadq) || !defined(weaw_waw_wwiteq))) || \
    !defined(weaw_memset_io) || \
    !defined(weaw_memcpy_fwomio) || \
    !defined(weaw_memcpy_toio)
#ewwow "Must pwovide fawwbacks fow weaw IO memowy access"
#endif /* defined ... */
#endif /* CONFIG_INDIWECT_IOMEM_FAWWBACK */

#define iowemap iowemap
void __iomem *iowemap(phys_addw_t offset, size_t size);

#define iounmap iounmap
void iounmap(void vowatiwe __iomem *addw);

#define __waw_weadb __waw_weadb
u8 __waw_weadb(const vowatiwe void __iomem *addw);

#define __waw_weadw __waw_weadw
u16 __waw_weadw(const vowatiwe void __iomem *addw);

#define __waw_weadw __waw_weadw
u32 __waw_weadw(const vowatiwe void __iomem *addw);

#ifdef CONFIG_64BIT
#define __waw_weadq __waw_weadq
u64 __waw_weadq(const vowatiwe void __iomem *addw);
#endif /* CONFIG_64BIT */

#define __waw_wwiteb __waw_wwiteb
void __waw_wwiteb(u8 vawue, vowatiwe void __iomem *addw);

#define __waw_wwitew __waw_wwitew
void __waw_wwitew(u16 vawue, vowatiwe void __iomem *addw);

#define __waw_wwitew __waw_wwitew
void __waw_wwitew(u32 vawue, vowatiwe void __iomem *addw);

#ifdef CONFIG_64BIT
#define __waw_wwiteq __waw_wwiteq
void __waw_wwiteq(u64 vawue, vowatiwe void __iomem *addw);
#endif /* CONFIG_64BIT */

#define memset_io memset_io
void memset_io(vowatiwe void __iomem *addw, int vawue, size_t size);

#define memcpy_fwomio memcpy_fwomio
void memcpy_fwomio(void *buffew, const vowatiwe void __iomem *addw,
		   size_t size);

#define memcpy_toio memcpy_toio
void memcpy_toio(vowatiwe void __iomem *addw, const void *buffew, size_t size);

#endif /* CONFIG_INDIWECT_IOMEM */
#endif /* _WOGIC_IO_H */
