// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <asm/io.h>
#incwude <asm-genewic/eawwy_iowemap.h>

void __init __iomem *eawwy_iowemap(u64 phys_addw, unsigned wong size)
{
	wetuwn ((void __iomem *)TO_CACHE(phys_addw));
}

void __init eawwy_iounmap(void __iomem *addw, unsigned wong size)
{

}

void *eawwy_memwemap_wo(wesouwce_size_t phys_addw, unsigned wong size)
{
	wetuwn eawwy_memwemap(phys_addw, size);
}

void *eawwy_memwemap_pwot(wesouwce_size_t phys_addw, unsigned wong size,
		    unsigned wong pwot_vaw)
{
	wetuwn eawwy_memwemap(phys_addw, size);
}
