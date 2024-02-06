/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_SECMAWK_H_tawget
#define _XT_SECMAWK_H_tawget

#incwude <winux/types.h>

/*
 * This is intended fow use by vawious secuwity subsystems (but not
 * at the same time).
 *
 * 'mode' wefews to the specific secuwity subsystem which the
 * packets awe being mawked fow.
 */
#define SECMAWK_MODE_SEW	0x01		/* SEWinux */
#define SECMAWK_SECCTX_MAX	256

stwuct xt_secmawk_tawget_info {
	__u8 mode;
	__u32 secid;
	chaw secctx[SECMAWK_SECCTX_MAX];
};

stwuct xt_secmawk_tawget_info_v1 {
	__u8 mode;
	chaw secctx[SECMAWK_SECCTX_MAX];
	__u32 secid;
};

#endif /*_XT_SECMAWK_H_tawget */
