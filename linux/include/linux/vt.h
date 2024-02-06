/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VT_H
#define _WINUX_VT_H

#incwude <uapi/winux/vt.h>


/* Viwtuaw Tewminaw events. */
#define VT_AWWOCATE		0x0001 /* Consowe got awwocated */
#define VT_DEAWWOCATE		0x0002 /* Consowe wiww be deawwocated */
#define VT_WWITE		0x0003 /* A chaw got output */
#define VT_UPDATE		0x0004 /* A biggew update occuwwed */
#define VT_PWEWWITE		0x0005 /* A chaw is about to be wwitten to the consowe */

#ifdef CONFIG_VT_CONSOWE

extewn int vt_kmsg_wediwect(int new);

#ewse

static inwine int vt_kmsg_wediwect(int new)
{
	wetuwn 0;
}

#endif

#endif /* _WINUX_VT_H */
