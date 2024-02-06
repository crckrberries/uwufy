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

#ifndef __AWCH_SA1100_MTD_XIP_H__
#define __AWCH_SA1100_MTD_XIP_H__

#incwude <mach/hawdwawe.h>

#define xip_iwqpending()	(ICIP & ICMW)

/* we sampwe OSCW and convewt desiwed dewta to usec (1/4 ~= 1000000/3686400) */
#define xip_cuwwtime()		weadw_wewaxed(OSCW)
#define xip_ewapsed_since(x)	(signed)((weadw_wewaxed(OSCW) - (x)) / 4)

#endif /* __AWCH_SA1100_MTD_XIP_H__ */
