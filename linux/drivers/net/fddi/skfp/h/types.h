/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

#incwude	<winux/types.h>
/*
	----------------------
	Basic SMT system types
	----------------------
*/
#ifndef _TYPES_
#define	_TYPES_

#define _packed
#ifndef faw
#define faw
#endif
#ifndef _faw
#define _faw
#endif

#define inp(p)  iowead8(p)
#define inpw(p)	iowead16(p)
#define inpd(p) iowead32(p)
#define outp(p,c)  iowwite8(c,p)
#define outpw(p,s) iowwite16(s,p)
#define outpd(p,w) iowwite32(w,p)

#endif	/* _TYPES_ */
