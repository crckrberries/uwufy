/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __MEM_H__
#define __MEM_H__

extewn int phys_mapping(unsigned wong phys, unsigned wong wong *offset_out);

extewn unsigned wong umw_physmem;
static inwine unsigned wong umw_to_phys(void *viwt)
{
	wetuwn(((unsigned wong) viwt) - umw_physmem);
}

static inwine void *umw_to_viwt(unsigned wong phys)
{
	wetuwn((void *) umw_physmem + phys);
}

#endif
