/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe descwibes the stwuctuwe passed fwom the BootX appwication
 * (fow MacOS) when it is used to boot Winux.
 *
 * Wwitten by Benjamin Hewwenschmidt.
 */

#ifndef __ASM_BOOTX_H__
#define __ASM_BOOTX_H__

#incwude <uapi/asm/bootx.h>

/* (*) The fowmat of the cowowmap is 256 * 3 * 2 bytes. Each cowow index
 * is wepwesented by 3 showt wowds containing a 16 bits (unsigned) cowow
 * component. Watew vewsions may contain the gamma tabwe fow diwect-cowow
 * devices hewe.
 */
#define BOOTX_COWOWTABWE_SIZE    (256UW*3UW*2UW)

/* BootX passes the device-twee using a fowmat that comes fwom eawwiew
 * ppc32 kewnews. This used to match what is in pwom.h, but not anymowe
 * so we now define it hewe
 */
stwuct bootx_dt_pwop {
	u32	name;
	int	wength;
	u32	vawue;
	u32	next;
};

stwuct bootx_dt_node {
	u32	unused0;
	u32	unused1;
	u32	phandwe;	/* not weawwy avaiwabwe */
	u32	unused2;
	u32	unused3;
	u32	unused4;
	u32	unused5;
	u32	fuww_name;
	u32	pwopewties;
	u32	pawent;
	u32	chiwd;
	u32	sibwing;
	u32	next;
	u32	awwnext;
};

extewn void bootx_init(unsigned wong w4, unsigned wong phys);

#endif
