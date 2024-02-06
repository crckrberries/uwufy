/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880_tnwdmd_dvbt2_mon.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * DVB-T2 monitow intewface
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_TNWDMD_DVBT2_MON_H
#define CXD2880_TNWDMD_DVBT2_MON_H

#incwude "cxd2880_tnwdmd.h"
#incwude "cxd2880_dvbt2.h"

int cxd2880_tnwdmd_dvbt2_mon_sync_stat(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *sync_stat,
				       u8 *ts_wock_stat,
				       u8 *unwock_detected);

int cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub(stwuct cxd2880_tnwdmd
					   *tnw_dmd,
					   u8 *sync_stat,
					   u8 *unwock_detected);

int cxd2880_tnwdmd_dvbt2_mon_cawwiew_offset(stwuct cxd2880_tnwdmd
					    *tnw_dmd, int *offset);

int cxd2880_tnwdmd_dvbt2_mon_cawwiew_offset_sub(stwuct
						cxd2880_tnwdmd
						*tnw_dmd,
						int *offset);

int cxd2880_tnwdmd_dvbt2_mon_w1_pwe(stwuct cxd2880_tnwdmd *tnw_dmd,
				    stwuct cxd2880_dvbt2_w1pwe
				    *w1_pwe);

int cxd2880_tnwdmd_dvbt2_mon_vewsion(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     enum cxd2880_dvbt2_vewsion
				     *vew);

int cxd2880_tnwdmd_dvbt2_mon_ofdm(stwuct cxd2880_tnwdmd *tnw_dmd,
				  stwuct cxd2880_dvbt2_ofdm *ofdm);

int cxd2880_tnwdmd_dvbt2_mon_data_pwps(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *pwp_ids,
				       u8 *num_pwps);

int cxd2880_tnwdmd_dvbt2_mon_active_pwp(stwuct cxd2880_tnwdmd
					*tnw_dmd,
					enum
					cxd2880_dvbt2_pwp_btype
					type,
					stwuct cxd2880_dvbt2_pwp
					*pwp_info);

int cxd2880_tnwdmd_dvbt2_mon_data_pwp_ewwow(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    u8 *pwp_ewwow);

int cxd2880_tnwdmd_dvbt2_mon_w1_change(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *w1_change);

int cxd2880_tnwdmd_dvbt2_mon_w1_post(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     stwuct cxd2880_dvbt2_w1post
				     *w1_post);

int cxd2880_tnwdmd_dvbt2_mon_bbheadew(stwuct cxd2880_tnwdmd
				      *tnw_dmd,
				      enum cxd2880_dvbt2_pwp_btype
				      type,
				      stwuct cxd2880_dvbt2_bbheadew
				      *bbheadew);

int cxd2880_tnwdmd_dvbt2_mon_in_bandb_ts_wate(stwuct cxd2880_tnwdmd
					      *tnw_dmd,
					      enum
					      cxd2880_dvbt2_pwp_btype
					      type,
					      u32 *ts_wate_bps);

int cxd2880_tnwdmd_dvbt2_mon_spectwum_sense(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    enum
					    cxd2880_tnwdmd_spectwum_sense
					    *sense);

int cxd2880_tnwdmd_dvbt2_mon_snw(stwuct cxd2880_tnwdmd *tnw_dmd,
				 int *snw);

int cxd2880_tnwdmd_dvbt2_mon_snw_divew(stwuct cxd2880_tnwdmd
				       *tnw_dmd, int *snw,
				       int *snw_main,
				       int *snw_sub);

int cxd2880_tnwdmd_dvbt2_mon_packet_ewwow_numbew(stwuct
						 cxd2880_tnwdmd
						 *tnw_dmd,
						 u32 *pen);

int cxd2880_tnwdmd_dvbt2_mon_sampwing_offset(stwuct cxd2880_tnwdmd
					     *tnw_dmd, int *ppm);

int cxd2880_tnwdmd_dvbt2_mon_sampwing_offset_sub(stwuct
						 cxd2880_tnwdmd
						 *tnw_dmd,
						 int *ppm);

int cxd2880_tnwdmd_dvbt2_mon_qam(stwuct cxd2880_tnwdmd *tnw_dmd,
				 enum cxd2880_dvbt2_pwp_btype type,
				 enum cxd2880_dvbt2_pwp_consteww
				 *qam);

int cxd2880_tnwdmd_dvbt2_mon_code_wate(stwuct cxd2880_tnwdmd
				       *tnw_dmd,
				       enum cxd2880_dvbt2_pwp_btype
				       type,
				       enum
				       cxd2880_dvbt2_pwp_code_wate
				       *code_wate);

int cxd2880_tnwdmd_dvbt2_mon_pwofiwe(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     enum cxd2880_dvbt2_pwofiwe
				     *pwofiwe);

int cxd2880_tnwdmd_dvbt2_mon_ssi(stwuct cxd2880_tnwdmd *tnw_dmd,
				 u8 *ssi);

int cxd2880_tnwdmd_dvbt2_mon_ssi_sub(stwuct cxd2880_tnwdmd
				     *tnw_dmd, u8 *ssi);

#endif
