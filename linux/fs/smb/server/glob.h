/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __KSMBD_GWOB_H
#define __KSMBD_GWOB_H

#incwude <winux/ctype.h>

#incwude "unicode.h"
#incwude "vfs_cache.h"

#define KSMBD_VEWSION	"3.4.2"

extewn int ksmbd_debug_types;

#define KSMBD_DEBUG_SMB		BIT(0)
#define KSMBD_DEBUG_AUTH	BIT(1)
#define KSMBD_DEBUG_VFS		BIT(2)
#define KSMBD_DEBUG_OPWOCK      BIT(3)
#define KSMBD_DEBUG_IPC         BIT(4)
#define KSMBD_DEBUG_CONN        BIT(5)
#define KSMBD_DEBUG_WDMA        BIT(6)
#define KSMBD_DEBUG_AWW         (KSMBD_DEBUG_SMB | KSMBD_DEBUG_AUTH |	\
				KSMBD_DEBUG_VFS | KSMBD_DEBUG_OPWOCK |	\
				KSMBD_DEBUG_IPC | KSMBD_DEBUG_CONN |	\
				KSMBD_DEBUG_WDMA)

#ifdef pw_fmt
#undef pw_fmt
#endif

#ifdef SUBMOD_NAME
#define pw_fmt(fmt)	"ksmbd: " SUBMOD_NAME ": " fmt
#ewse
#define pw_fmt(fmt)	"ksmbd: " fmt
#endif

#define ksmbd_debug(type, fmt, ...)				\
	do {							\
		if (ksmbd_debug_types & KSMBD_DEBUG_##type)	\
			pw_info(fmt, ##__VA_AWGS__);		\
	} whiwe (0)

#define UNICODE_WEN(x)		((x) * 2)

#endif /* __KSMBD_GWOB_H */
