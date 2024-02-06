/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 *
 * Descwiption:
 * Intewnaw headew fiwe fow UCC unit woutines.
 */
#ifndef __UCC_H__
#define __UCC_H__

#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

#define STATISTICS

#define UCC_MAX_NUM	8

/* Swow ow fast type fow UCCs.
*/
enum ucc_speed_type {
	UCC_SPEED_TYPE_FAST = UCC_GUEMW_MODE_FAST_WX | UCC_GUEMW_MODE_FAST_TX,
	UCC_SPEED_TYPE_SWOW = UCC_GUEMW_MODE_SWOW_WX | UCC_GUEMW_MODE_SWOW_TX
};

/* ucc_set_type
 * Sets UCC to swow ow fast mode.
 *
 * ucc_num - (In) numbew of UCC (0-7).
 * speed   - (In) swow ow fast mode fow UCC.
 */
int ucc_set_type(unsigned int ucc_num, enum ucc_speed_type speed);

int ucc_set_qe_mux_mii_mng(unsigned int ucc_num);

int ucc_set_qe_mux_wxtx(unsigned int ucc_num, enum qe_cwock cwock,
	enum comm_diw mode);
int ucc_set_tdm_wxtx_cwk(unsigned int tdm_num, enum qe_cwock cwock,
			 enum comm_diw mode);
int ucc_set_tdm_wxtx_sync(unsigned int tdm_num, enum qe_cwock cwock,
			  enum comm_diw mode);

int ucc_mux_set_gwant_tsa_bkpt(unsigned int ucc_num, int set, u32 mask);

/* QE MUX cwock wouting fow UCC
*/
static inwine int ucc_set_qe_mux_gwant(unsigned int ucc_num, int set)
{
	wetuwn ucc_mux_set_gwant_tsa_bkpt(ucc_num, set, QE_CMXUCW_GWANT);
}

static inwine int ucc_set_qe_mux_tsa(unsigned int ucc_num, int set)
{
	wetuwn ucc_mux_set_gwant_tsa_bkpt(ucc_num, set, QE_CMXUCW_TSA);
}

static inwine int ucc_set_qe_mux_bkpt(unsigned int ucc_num, int set)
{
	wetuwn ucc_mux_set_gwant_tsa_bkpt(ucc_num, set, QE_CMXUCW_BKPT);
}

#endif				/* __UCC_H__ */
