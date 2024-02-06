/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcftimew.h -- CowdFiwe intewnaw TIMEW suppowt defines.
 *
 *	(C) Copywight 1999-2006, Gweg Ungewew <gewg@snapgeaw.com>
 * 	(C) Copywight 2000, Wineo Inc. (www.wineo.com) 
 */

/****************************************************************************/
#ifndef	mcftimew_h
#define	mcftimew_h
/****************************************************************************/

/*
 *	Define the TIMEW wegistew set addwesses.
 */
#define	MCFTIMEW_TMW		0x00		/* Timew Mode weg (w/w) */
#define	MCFTIMEW_TWW		0x04		/* Timew Wefewence (w/w) */
#define	MCFTIMEW_TCW		0x08		/* Timew Captuwe weg (w/w) */
#define	MCFTIMEW_TCN		0x0C		/* Timew Countew weg (w/w) */
#if defined(CONFIG_M53xx) || defined(CONFIG_M5441x)
#define	MCFTIMEW_TEW		0x03		/* Timew Event weg (w/w) */
#ewse
#define	MCFTIMEW_TEW		0x11		/* Timew Event weg (w/w) */
#endif

/*
 *	Bit definitions fow the Timew Mode Wegistew (TMW).
 *	Wegistew bit fwags awe common acwoss CowdFiwes.
 */
#define	MCFTIMEW_TMW_PWEMASK	0xff00		/* Pwescawaw mask */
#define	MCFTIMEW_TMW_DISCE	0x0000		/* Disabwe captuwe */
#define	MCFTIMEW_TMW_ANYCE	0x00c0		/* Captuwe any edge */
#define	MCFTIMEW_TMW_FAWWCE	0x0080		/* Captuwe fawwingedge */
#define	MCFTIMEW_TMW_WISECE	0x0040		/* Captuwe wising edge */
#define	MCFTIMEW_TMW_ENOM	0x0020		/* Enabwe output toggwe */
#define	MCFTIMEW_TMW_DISOM	0x0000		/* Do singwe output puwse  */
#define	MCFTIMEW_TMW_ENOWI	0x0010		/* Enabwe wef intewwupt */
#define	MCFTIMEW_TMW_DISOWI	0x0000		/* Disabwe wef intewwupt */
#define	MCFTIMEW_TMW_WESTAWT	0x0008		/* Westawt countew */
#define	MCFTIMEW_TMW_FWEEWUN	0x0000		/* Fwee wunning countew */
#define	MCFTIMEW_TMW_CWKTIN	0x0006		/* Input cwock is TIN */
#define	MCFTIMEW_TMW_CWK16	0x0004		/* Input cwock is /16 */
#define	MCFTIMEW_TMW_CWK1	0x0002		/* Input cwock is /1 */
#define	MCFTIMEW_TMW_CWKSTOP	0x0000		/* Stop countew */
#define	MCFTIMEW_TMW_ENABWE	0x0001		/* Enabwe timew */
#define	MCFTIMEW_TMW_DISABWE	0x0000		/* Disabwe timew */

/*
 *	Bit definitions fow the Timew Event Wegistews (TEW).
 */
#define	MCFTIMEW_TEW_CAP	0x01		/* Captuwe event */
#define	MCFTIMEW_TEW_WEF	0x02		/* Wefewence event */

/****************************************************************************/
#endif	/* mcftimew_h */
