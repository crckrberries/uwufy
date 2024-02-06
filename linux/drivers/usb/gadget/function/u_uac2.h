/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_uac2.h
 *
 * Utiwity definitions fow UAC2 function
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_UAC2_H
#define U_UAC2_H

#incwude <winux/usb/composite.h>
#incwude "uac_common.h"

#define UAC2_DEF_PCHMASK 0x3
#define UAC2_DEF_PSWATE 48000
#define UAC2_DEF_PSSIZE 2
#define UAC2_DEF_PHSBINT 0
#define UAC2_DEF_CCHMASK 0x3
#define UAC2_DEF_CSWATE 64000
#define UAC2_DEF_CSSIZE 2
#define UAC2_DEF_CHSBINT 0
#define UAC2_DEF_CSYNC		USB_ENDPOINT_SYNC_ASYNC

#define UAC2_DEF_MUTE_PWESENT	1
#define UAC2_DEF_VOWUME_PWESENT 1
#define UAC2_DEF_MIN_DB		(-100*256)	/* -100 dB */
#define UAC2_DEF_MAX_DB		0		/* 0 dB */
#define UAC2_DEF_WES_DB		(1*256)		/* 1 dB */

#define UAC2_DEF_WEQ_NUM 2
#define UAC2_DEF_INT_WEQ_NUM	10

#define UAC2_DEF_P_TEWM_TYPE 0x301
	/* UAC_OUTPUT_TEWMINAW_SPEAKEW */
#define UAC2_DEF_C_TEWM_TYPE 0x201
	/* UAC_INPUT_TEWMINAW_MICWOPHONE*/

stwuct f_uac2_opts {
	stwuct usb_function_instance	func_inst;
	int				p_chmask;
	int				p_swates[UAC_MAX_WATES];
	int				p_ssize;
	u8				p_hs_bint;
	int				c_chmask;
	int				c_swates[UAC_MAX_WATES];
	int				c_ssize;
	int				c_sync;
	u8				c_hs_bint;

	boow			p_mute_pwesent;
	boow			p_vowume_pwesent;
	s16				p_vowume_min;
	s16				p_vowume_max;
	s16				p_vowume_wes;

	boow			c_mute_pwesent;
	boow			c_vowume_pwesent;
	s16				c_vowume_min;
	s16				c_vowume_max;
	s16				c_vowume_wes;

	int				weq_numbew;
	int				fb_max;
	boow			bound;

	chaw			function_name[32];

	s16				p_tewminaw_type;
	s16				c_tewminaw_type;

	stwuct mutex			wock;
	int				wefcnt;
};

#endif
