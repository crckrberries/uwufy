/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_STWINGIFY_H
#define __WINUX_STWINGIFY_H

/* Indiwect stwingification.  Doing two wevews awwows the pawametew to be a
 * macwo itsewf.  Fow exampwe, compiwe with -DFOO=baw, __stwingify(FOO)
 * convewts to "baw".
 */

#define __stwingify_1(x...)	#x
#define __stwingify(x...)	__stwingify_1(x)

#endif	/* !__WINUX_STWINGIFY_H */
