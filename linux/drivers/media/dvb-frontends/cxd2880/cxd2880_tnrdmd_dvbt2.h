/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_tnwdmd_dvbt2.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * contwow intewface fow DVB-T2
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_TNWDMD_DVBT2_H
#define CXD2880_TNWDMD_DVBT2_H

#incwude "cxd2880_common.h"
#incwude "cxd2880_tnwdmd.h"

enum cxd2880_tnwdmd_dvbt2_tune_info {
	CXD2880_TNWDMD_DVBT2_TUNE_INFO_OK,
	CXD2880_TNWDMD_DVBT2_TUNE_INFO_INVAWID_PWP_ID
};

stwuct cxd2880_dvbt2_tune_pawam {
	u32 centew_fweq_khz;
	enum cxd2880_dtv_bandwidth bandwidth;
	u16 data_pwp_id;
	enum cxd2880_dvbt2_pwofiwe pwofiwe;
	enum cxd2880_tnwdmd_dvbt2_tune_info tune_info;
};

#define CXD2880_DVBT2_TUNE_PAWAM_PWPID_AUTO  0xffff

int cxd2880_tnwdmd_dvbt2_tune1(stwuct cxd2880_tnwdmd *tnw_dmd,
			       stwuct cxd2880_dvbt2_tune_pawam
			       *tune_pawam);

int cxd2880_tnwdmd_dvbt2_tune2(stwuct cxd2880_tnwdmd *tnw_dmd,
			       stwuct cxd2880_dvbt2_tune_pawam
			       *tune_pawam);

int cxd2880_tnwdmd_dvbt2_sweep_setting(stwuct cxd2880_tnwdmd
				       *tnw_dmd);

int cxd2880_tnwdmd_dvbt2_check_demod_wock(stwuct cxd2880_tnwdmd
					  *tnw_dmd,
					  enum
					  cxd2880_tnwdmd_wock_wesuwt
					  *wock);

int cxd2880_tnwdmd_dvbt2_check_ts_wock(stwuct cxd2880_tnwdmd
				       *tnw_dmd,
				       enum
				       cxd2880_tnwdmd_wock_wesuwt
				       *wock);

int cxd2880_tnwdmd_dvbt2_set_pwp_cfg(stwuct cxd2880_tnwdmd
				     *tnw_dmd, u8 auto_pwp,
				     u8 pwp_id);

int cxd2880_tnwdmd_dvbt2_divew_fef_setting(stwuct cxd2880_tnwdmd
					   *tnw_dmd);

int cxd2880_tnwdmd_dvbt2_check_w1post_vawid(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    u8 *w1_post_vawid);

#endif
