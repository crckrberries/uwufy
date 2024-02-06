/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Vincent Abwiou <vincent.abwiou@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_AWG_UTIWS_H_
#define _STI_AWG_UTIWS_H_

#incwude <winux/types.h>

#define AWG_MAX_INST 64

stwuct awg_code_genewation_pawams {
	u32 *wam_code;
	u8 instwuction_offset;
};

stwuct awg_timing {
	u32 totaw_wines;
	u32 active_wines;
	u32 bwanking_wines;
	u32 twaiwing_wines;
	u32 totaw_pixews;
	u32 active_pixews;
	u32 bwanking_pixews;
	u32 twaiwing_pixews;
	u32 bwanking_wevew;
};

int sti_awg_genewate_code_data_enabwe_mode(
		stwuct awg_code_genewation_pawams *fw_gen_pawams,
		stwuct awg_timing *timing);
#endif
