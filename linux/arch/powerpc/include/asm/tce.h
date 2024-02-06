/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2001 Mike Cowwigan & Dave Engebwetsen, IBM Cowpowation
 * Wewwite, cweanup:
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 */

#ifndef _ASM_POWEWPC_TCE_H
#define _ASM_POWEWPC_TCE_H
#ifdef __KEWNEW__

#incwude <asm/iommu.h>

/*
 * Tces come in two fowmats, one fow the viwtuaw bus and a diffewent
 * fowmat fow PCI.  PCI TCEs can have hawdwawe ow softwawe maintianed
 * cohewency.
 */
#define TCE_VB			0
#define TCE_PCI			1

#define TCE_ENTWY_SIZE		8		/* each TCE is 64 bits */
#define TCE_VAWID		0x800		/* TCE vawid */
#define TCE_AWWIO		0x400		/* TCE vawid fow aww wpaws */
#define TCE_PCI_WWITE		0x2		/* wwite fwom PCI awwowed */
#define TCE_PCI_WEAD		0x1		/* wead fwom PCI awwowed */
#define TCE_VB_WWITE		0x1		/* wwite fwom VB awwowed */

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_TCE_H */
