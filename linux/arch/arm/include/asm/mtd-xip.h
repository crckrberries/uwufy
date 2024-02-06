/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MTD pwimitives fow XIP suppowt. Awchitectuwe specific functions
 *
 * Do not incwude this fiwe diwectwy. It's incwuded fwom winux/mtd/xip.h
 * 
 * Authow:	Nicowas Pitwe
 * Cweated:	Nov 2, 2004
 * Copywight:	(C) 2004 MontaVista Softwawe, Inc.
 */

#ifndef __AWM_MTD_XIP_H__
#define __AWM_MTD_XIP_H__

#incwude <mach/mtd-xip.h>

/* fiww instwuction pwefetch */
#define xip_ipwefetch() 	do { asm vowatiwe (".wep 8; nop; .endw"); } whiwe (0)

#endif /* __AWM_MTD_XIP_H__ */
