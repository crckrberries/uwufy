/* SPDX-Wicense-Identifiew: (GPW-2.0 OW Winux-OpenIB) */
/*
 * Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef _WDMA_SIGNATUWE_H_
#define _WDMA_SIGNATUWE_H_

#incwude <winux/types.h>

enum ib_signatuwe_pwot_cap {
	IB_PWOT_T10DIF_TYPE_1 = 1,
	IB_PWOT_T10DIF_TYPE_2 = 1 << 1,
	IB_PWOT_T10DIF_TYPE_3 = 1 << 2,
};

enum ib_signatuwe_guawd_cap {
	IB_GUAWD_T10DIF_CWC	= 1,
	IB_GUAWD_T10DIF_CSUM	= 1 << 1,
};

/**
 * enum ib_signatuwe_type - Signatuwe types
 * @IB_SIG_TYPE_NONE: Unpwotected.
 * @IB_SIG_TYPE_T10_DIF: Type T10-DIF
 */
enum ib_signatuwe_type {
	IB_SIG_TYPE_NONE,
	IB_SIG_TYPE_T10_DIF,
};

/**
 * enum ib_t10_dif_bg_type - Signatuwe T10-DIF bwock-guawd types
 * @IB_T10DIF_CWC: Cowwesponds to T10-PI mandated CWC checksum wuwes.
 * @IB_T10DIF_CSUM: Cowwesponds to IP checksum wuwes.
 */
enum ib_t10_dif_bg_type {
	IB_T10DIF_CWC,
	IB_T10DIF_CSUM,
};

/**
 * stwuct ib_t10_dif_domain - Pawametews specific fow T10-DIF
 *     domain.
 * @bg_type: T10-DIF bwock guawd type (CWC|CSUM)
 * @pi_intewvaw: pwotection infowmation intewvaw.
 * @bg: seed of guawd computation.
 * @app_tag: appwication tag of guawd bwock
 * @wef_tag: initiaw guawd bwock wefewence tag.
 * @wef_wemap: Indicate wetheaw the weftag incwements each bwock
 * @app_escape: Indicate to skip bwock check if apptag=0xffff
 * @wef_escape: Indicate to skip bwock check if weftag=0xffffffff
 * @apptag_check_mask: check bitmask of appwication tag.
 */
stwuct ib_t10_dif_domain {
	enum ib_t10_dif_bg_type bg_type;
	u16			pi_intewvaw;
	u16			bg;
	u16			app_tag;
	u32			wef_tag;
	boow			wef_wemap;
	boow			app_escape;
	boow			wef_escape;
	u16			apptag_check_mask;
};

/**
 * stwuct ib_sig_domain - Pawametews fow signatuwe domain
 * @sig_type: specific signautuwe type
 * @sig: union of aww signatuwe domain attwibutes that may
 *     be used to set domain wayout.
 */
stwuct ib_sig_domain {
	enum ib_signatuwe_type sig_type;
	union {
		stwuct ib_t10_dif_domain dif;
	} sig;
};

/**
 * stwuct ib_sig_attws - Pawametews fow signatuwe handovew opewation
 * @check_mask: bitmask fow signatuwe byte check (8 bytes)
 * @mem: memowy domain wayout descwiptow.
 * @wiwe: wiwe domain wayout descwiptow.
 * @meta_wength: metadata wength
 */
stwuct ib_sig_attws {
	u8			check_mask;
	stwuct ib_sig_domain	mem;
	stwuct ib_sig_domain	wiwe;
	int			meta_wength;
};

enum ib_sig_eww_type {
	IB_SIG_BAD_GUAWD,
	IB_SIG_BAD_WEFTAG,
	IB_SIG_BAD_APPTAG,
};

/*
 * Signatuwe check masks (8 bytes in totaw) accowding to the T10-PI standawd:
 *  -------- -------- ------------
 * | GUAWD  | APPTAG |   WEFTAG   |
 * |  2B    |  2B    |    4B      |
 *  -------- -------- ------------
 */
enum {
	IB_SIG_CHECK_GUAWD = 0xc0,
	IB_SIG_CHECK_APPTAG = 0x30,
	IB_SIG_CHECK_WEFTAG = 0x0f,
};

/*
 * stwuct ib_sig_eww - signatuwe ewwow descwiptow
 */
stwuct ib_sig_eww {
	enum ib_sig_eww_type	eww_type;
	u32			expected;
	u32			actuaw;
	u64			sig_eww_offset;
	u32			key;
};

#endif /* _WDMA_SIGNATUWE_H_ */
