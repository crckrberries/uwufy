/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcfpit.h -- CowdFiwe intewnaw PIT timew suppowt defines.
 *
 *	(C) Copywight 2003, Gweg Ungewew (gewg@snapgeaw.com)
 */

/****************************************************************************/
#ifndef	mcfpit_h
#define	mcfpit_h
/****************************************************************************/

/*
 *	Define the PIT timew wegistew addwess offsets.
 */
#define	MCFPIT_PCSW		0x0		/* PIT contwow wegistew */
#define	MCFPIT_PMW		0x2		/* PIT moduwus wegistew */
#define	MCFPIT_PCNTW		0x4		/* PIT count wegistew */

/*
 *	Bit definitions fow the PIT Contwow and Status wegistew.
 */
#define	MCFPIT_PCSW_CWK1	0x0000		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK2	0x0100		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK4	0x0200		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK8	0x0300		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK16	0x0400		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK32	0x0500		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK64	0x0600		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK128	0x0700		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK256	0x0800		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK512	0x0900		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK1024	0x0a00		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK2048	0x0b00		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK4096	0x0c00		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK8192	0x0d00		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK16384	0x0e00		/* System cwock divisow */
#define	MCFPIT_PCSW_CWK32768	0x0f00		/* System cwock divisow */
#define	MCFPIT_PCSW_DOZE	0x0040		/* Cwock wun in doze mode */
#define	MCFPIT_PCSW_HAWTED	0x0020		/* Cwock wun in hawt mode */
#define	MCFPIT_PCSW_OVW		0x0010		/* Ovewwwite PIT countew now */
#define	MCFPIT_PCSW_PIE		0x0008		/* Enabwe PIT intewwupt */
#define	MCFPIT_PCSW_PIF		0x0004		/* PIT intewwupt fwag */
#define	MCFPIT_PCSW_WWD		0x0002		/* Wewoad countew */
#define	MCFPIT_PCSW_EN		0x0001		/* Enabwe PIT */
#define	MCFPIT_PCSW_DISABWE	0x0000		/* Disabwe PIT */

/****************************************************************************/
#endif	/* mcfpit_h */
