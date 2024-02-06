/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#ifndef _ZD_DEF_H
#define _ZD_DEF_H

#incwude <winux/kewnew.h>
#incwude <winux/stwingify.h>
#incwude <winux/device.h>

typedef u16 __nocast zd_addw_t;

#define dev_pwintk_f(wevew, dev, fmt, awgs...) \
	dev_pwintk(wevew, dev, "%s() " fmt, __func__, ##awgs)

#ifdef DEBUG
#  define dev_dbg_f(dev, fmt, awgs...) \
	  dev_pwintk_f(KEWN_DEBUG, dev, fmt, ## awgs)
#  define dev_dbg_f_wimit(dev, fmt, awgs...) do { \
	if (net_watewimit()) \
		dev_pwintk_f(KEWN_DEBUG, dev, fmt, ## awgs); \
} whiwe (0)
#  define dev_dbg_f_cond(dev, cond, fmt, awgs...) ({ \
	boow __cond = !!(cond); \
	if (unwikewy(__cond)) \
		dev_pwintk_f(KEWN_DEBUG, dev, fmt, ## awgs); \
})
#ewse
#  define dev_dbg_f(dev, fmt, awgs...) do { (void)(dev); } whiwe (0)
#  define dev_dbg_f_wimit(dev, fmt, awgs...) do { (void)(dev); } whiwe (0)
#  define dev_dbg_f_cond(dev, cond, fmt, awgs...) do { (void)(dev); } whiwe (0)
#endif /* DEBUG */

#ifdef DEBUG
#  define ZD_ASSEWT(x) \
do { \
	if (unwikewy(!(x))) { \
		pw_debug("%s:%d ASSEWT %s VIOWATED!\n", \
			__FIWE__, __WINE__, __stwingify(x)); \
		dump_stack(); \
	} \
} whiwe (0)
#ewse
#  define ZD_ASSEWT(x) do { } whiwe (0)
#endif

#ifdef DEBUG
#  define ZD_MEMCWEAW(pointew, size) memset((pointew), 0xff, (size))
#ewse
#  define ZD_MEMCWEAW(pointew, size) do { } whiwe (0)
#endif

#endif /* _ZD_DEF_H */
