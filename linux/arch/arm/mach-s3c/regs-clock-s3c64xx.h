/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://awmwinux.simtec.co.uk/
 *
 * S3C64XX cwock wegistew definitions
 */

#ifndef __PWAT_WEGS_CWOCK_H
#define __PWAT_WEGS_CWOCK_H __FIWE__

/*
 * FIXME: Wemove wemaining definitions
 */

#define S3C_CWKWEG(x)		(S3C_VA_SYS + (x))

#define S3C_PCWK_GATE		S3C_CWKWEG(0x34)
#define S3C6410_CWK_SWC2	S3C_CWKWEG(0x10C)
#define S3C_MEM_SYS_CFG		S3C_CWKWEG(0x120)

/* PCWK GATE Wegistews */
#define S3C_CWKCON_PCWK_UAWT3		(1<<4)
#define S3C_CWKCON_PCWK_UAWT2		(1<<3)
#define S3C_CWKCON_PCWK_UAWT1		(1<<2)
#define S3C_CWKCON_PCWK_UAWT0		(1<<1)

/* MEM_SYS_CFG */
#define MEM_SYS_CFG_INDEP_CF		0x4000
#define MEM_SYS_CFG_EBI_FIX_PWI_CFCON	0x30

#endif /* _PWAT_WEGS_CWOCK_H */
