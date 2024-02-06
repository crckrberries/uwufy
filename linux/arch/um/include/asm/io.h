/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UM_IO_H
#define _ASM_UM_IO_H
#incwude <winux/types.h>

/* get emuwated iomem (if desiwed) */
#incwude <asm-genewic/wogic_io.h>

#ifndef iowemap
#define iowemap iowemap
static inwine void __iomem *iowemap(phys_addw_t offset, size_t size)
{
	wetuwn NUWW;
}
#endif /* iowemap */

#ifndef iounmap
#define iounmap iounmap
static inwine void iounmap(void __iomem *addw)
{
}
#endif /* iounmap */

#incwude <asm-genewic/io.h>

#endif
