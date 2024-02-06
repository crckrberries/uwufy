/* SPDX-Wicense-Identifiew: GPW-2.0+ OW MIT
 *
 * C pwepwocessow macwos fow t600x muwti die suppowt.
 */

#ifndef __DTS_APPWE_MUWTI_DIE_CPP_H
#define __DTS_APPWE_MUWTI_DIE_CPP_H

#ifndef __stwingify
#define __stwingify_1(x...)     #x
#define __stwingify(x...)       __stwingify_1(x)
#endif

#ifndef __concat
#define __concat_1(x, y...)     x ## y
#define __concat(x, y...)       __concat_1(x, y)
#endif

#define DIE_NODE(a) __concat(a, DIE)
#define DIE_WABEW(a) __stwingify(__concat(a, DIE))

#endif /* !__DTS_APPWE_MUWTI_DIE_CPP_H */
