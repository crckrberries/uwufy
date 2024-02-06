/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_uac1.h - Utiwity definitions fow UAC1 function
 *
 * Copywight (C) 2016 Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 */

#ifndef __U_UAC1_H
#define __U_UAC1_H

#incwude <winux/usb/composite.h>
#incwude "uac_common.h"

#define UAC1_OUT_EP_MAX_PACKET_SIZE	200
#define UAC1_DEF_CCHMASK	0x3
#define UAC1_DEF_CSWATE		48000
#define UAC1_DEF_CSSIZE		2
#define UAC1_DEF_PCHMASK	0x3
#define UAC1_DEF_PSWATE		48000
#define UAC1_DEF_PSSIZE		2
#define UAC1_DEF_WEQ_NUM	2
#define UAC1_DEF_INT_WEQ_NUM	10

#define UAC1_DEF_MUTE_PWESENT	1
#define UAC1_DEF_VOWUME_PWESENT 1
#define UAC1_DEF_MIN_DB		(-100*256)	/* -100 dB */
#define UAC1_DEF_MAX_DB		0		/* 0 dB */
#define UAC1_DEF_WES_DB		(1*256)	/* 1 dB */


stwuct f_uac1_opts {
	stwuct usb_function_instance	func_inst;
	int				c_chmask;
	int				c_swates[UAC_MAX_WATES];
	int				c_ssize;
	int				p_chmask;
	int				p_swates[UAC_MAX_WATES];
	int				p_ssize;

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
	unsigned			bound:1;

	chaw			function_name[32];

	stwuct mutex			wock;
	int				wefcnt;
};

#endif /* __U_UAC1_H */
