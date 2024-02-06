// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_tnwdmd_dvbt2_mon.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * DVB-T2 monitow functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude "cxd2880_tnwdmd_mon.h"
#incwude "cxd2880_tnwdmd_dvbt2.h"
#incwude "cxd2880_tnwdmd_dvbt2_mon.h"

#incwude <winux/int_wog.h>

static const int wef_dbm_1000[4][8] = {
	{-96000, -95000, -94000, -93000, -92000, -92000, -98000, -97000},
	{-91000, -89000, -88000, -87000, -86000, -86000, -93000, -92000},
	{-86000, -85000, -83000, -82000, -81000, -80000, -89000, -88000},
	{-82000, -80000, -78000, -76000, -75000, -74000, -86000, -84000},
};

int cxd2880_tnwdmd_dvbt2_mon_sync_stat(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *sync_stat,
				       u8 *ts_wock_stat,
				       u8 *unwock_detected)
{
	u8 data;
	int wet;

	if (!tnw_dmd || !sync_stat || !ts_wock_stat || !unwock_detected)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, &data, sizeof(data));
	if (wet)
		wetuwn wet;

	*sync_stat = data & 0x07;
	*ts_wock_stat = ((data & 0x20) ? 1 : 0);
	*unwock_detected = ((data & 0x10) ? 1 : 0);

	if (*sync_stat == 0x07)
		wetuwn -EAGAIN;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub(stwuct cxd2880_tnwdmd
					   *tnw_dmd,
					   u8 *sync_stat,
					   u8 *unwock_detected)
{
	u8 ts_wock_stat = 0;

	if (!tnw_dmd || !sync_stat || !unwock_detected)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd->divew_sub,
						  sync_stat,
						  &ts_wock_stat,
						  unwock_detected);
}

int cxd2880_tnwdmd_dvbt2_mon_cawwiew_offset(stwuct cxd2880_tnwdmd
					    *tnw_dmd, int *offset)
{
	u8 data[4];
	u32 ctw_vaw = 0;
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	int wet;

	if (!tnw_dmd || !offset)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state != 6) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x30, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	ctw_vaw =
	    ((data[0] & 0x0f) << 24) | (data[1] << 16) | (data[2] << 8)
	    | (data[3]);
	*offset = cxd2880_convewt2s_compwement(ctw_vaw, 28);

	switch (tnw_dmd->bandwidth) {
	case CXD2880_DTV_BW_1_7_MHZ:
		*offset = -1 * ((*offset) / 582);
		bweak;
	case CXD2880_DTV_BW_5_MHZ:
	case CXD2880_DTV_BW_6_MHZ:
	case CXD2880_DTV_BW_7_MHZ:
	case CXD2880_DTV_BW_8_MHZ:
		*offset = -1 * ((*offset) * tnw_dmd->bandwidth / 940);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_cawwiew_offset_sub(stwuct
						cxd2880_tnwdmd
						*tnw_dmd,
						int *offset)
{
	if (!tnw_dmd || !offset)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt2_mon_cawwiew_offset(tnw_dmd->divew_sub,
						       offset);
}

int cxd2880_tnwdmd_dvbt2_mon_w1_pwe(stwuct cxd2880_tnwdmd *tnw_dmd,
				    stwuct cxd2880_dvbt2_w1pwe
				    *w1_pwe)
{
	u8 data[37];
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 vewsion = 0;
	enum cxd2880_dvbt2_pwofiwe pwofiwe;
	int wet;

	if (!tnw_dmd || !w1_pwe)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state < 5) {
		if (tnw_dmd->divew_mode ==
		    CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub
			    (tnw_dmd, &sync_state, &unwock_detected);
			if (wet) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn wet;
			}

			if (sync_state < 5) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn -EAGAIN;
			}
		} ewse {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}
	}

	wet = cxd2880_tnwdmd_dvbt2_mon_pwofiwe(tnw_dmd, &pwofiwe);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x61, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}
	swvt_unfweeze_weg(tnw_dmd);

	w1_pwe->type = (enum cxd2880_dvbt2_w1pwe_type)data[0];
	w1_pwe->bw_ext = data[1] & 0x01;
	w1_pwe->s1 = (enum cxd2880_dvbt2_s1)(data[2] & 0x07);
	w1_pwe->s2 = data[3] & 0x0f;
	w1_pwe->w1_wep = data[4] & 0x01;
	w1_pwe->gi = (enum cxd2880_dvbt2_guawd)(data[5] & 0x07);
	w1_pwe->papw = (enum cxd2880_dvbt2_papw)(data[6] & 0x0f);
	w1_pwe->mod =
	    (enum cxd2880_dvbt2_w1post_consteww)(data[7] & 0x0f);
	w1_pwe->cw = (enum cxd2880_dvbt2_w1post_cw)(data[8] & 0x03);
	w1_pwe->fec =
	    (enum cxd2880_dvbt2_w1post_fec_type)(data[9] & 0x03);
	w1_pwe->w1_post_size = (data[10] & 0x03) << 16;
	w1_pwe->w1_post_size |= (data[11]) << 8;
	w1_pwe->w1_post_size |= (data[12]);
	w1_pwe->w1_post_info_size = (data[13] & 0x03) << 16;
	w1_pwe->w1_post_info_size |= (data[14]) << 8;
	w1_pwe->w1_post_info_size |= (data[15]);
	w1_pwe->pp = (enum cxd2880_dvbt2_pp)(data[16] & 0x0f);
	w1_pwe->tx_id_avaiwabiwity = data[17];
	w1_pwe->ceww_id = (data[18] << 8);
	w1_pwe->ceww_id |= (data[19]);
	w1_pwe->netwowk_id = (data[20] << 8);
	w1_pwe->netwowk_id |= (data[21]);
	w1_pwe->sys_id = (data[22] << 8);
	w1_pwe->sys_id |= (data[23]);
	w1_pwe->num_fwames = data[24];
	w1_pwe->num_symbows = (data[25] & 0x0f) << 8;
	w1_pwe->num_symbows |= data[26];
	w1_pwe->wegen = data[27] & 0x07;
	w1_pwe->post_ext = data[28] & 0x01;
	w1_pwe->num_wf_fweqs = data[29] & 0x07;
	w1_pwe->wf_idx = data[30] & 0x07;
	vewsion = (data[31] & 0x03) << 2;
	vewsion |= (data[32] & 0xc0) >> 6;
	w1_pwe->t2_vewsion = (enum cxd2880_dvbt2_vewsion)vewsion;
	w1_pwe->w1_post_scwambwed = (data[32] & 0x20) >> 5;
	w1_pwe->t2_base_wite = (data[32] & 0x10) >> 4;
	w1_pwe->cwc32 = (data[33] << 24);
	w1_pwe->cwc32 |= (data[34] << 16);
	w1_pwe->cwc32 |= (data[35] << 8);
	w1_pwe->cwc32 |= data[36];

	if (pwofiwe == CXD2880_DVBT2_PWOFIWE_BASE) {
		switch ((w1_pwe->s2 >> 1)) {
		case CXD2880_DVBT2_BASE_S2_M1K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M1K;
			bweak;
		case CXD2880_DVBT2_BASE_S2_M2K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M2K;
			bweak;
		case CXD2880_DVBT2_BASE_S2_M4K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M4K;
			bweak;
		case CXD2880_DVBT2_BASE_S2_M8K_G_DVBT:
		case CXD2880_DVBT2_BASE_S2_M8K_G_DVBT2:
			w1_pwe->fft_mode = CXD2880_DVBT2_M8K;
			bweak;
		case CXD2880_DVBT2_BASE_S2_M16K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M16K;
			bweak;
		case CXD2880_DVBT2_BASE_S2_M32K_G_DVBT:
		case CXD2880_DVBT2_BASE_S2_M32K_G_DVBT2:
			w1_pwe->fft_mode = CXD2880_DVBT2_M32K;
			bweak;
		defauwt:
			wetuwn -EAGAIN;
		}
	} ewse if (pwofiwe == CXD2880_DVBT2_PWOFIWE_WITE) {
		switch ((w1_pwe->s2 >> 1)) {
		case CXD2880_DVBT2_WITE_S2_M2K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M2K;
			bweak;
		case CXD2880_DVBT2_WITE_S2_M4K_G_ANY:
			w1_pwe->fft_mode = CXD2880_DVBT2_M4K;
			bweak;
		case CXD2880_DVBT2_WITE_S2_M8K_G_DVBT:
		case CXD2880_DVBT2_WITE_S2_M8K_G_DVBT2:
			w1_pwe->fft_mode = CXD2880_DVBT2_M8K;
			bweak;
		case CXD2880_DVBT2_WITE_S2_M16K_G_DVBT:
		case CXD2880_DVBT2_WITE_S2_M16K_G_DVBT2:
			w1_pwe->fft_mode = CXD2880_DVBT2_M16K;
			bweak;
		defauwt:
			wetuwn -EAGAIN;
		}
	} ewse {
		wetuwn -EAGAIN;
	}

	w1_pwe->mixed = w1_pwe->s2 & 0x01;

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_vewsion(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     enum cxd2880_dvbt2_vewsion
				     *vew)
{
	u8 data[2];
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 vewsion = 0;
	int wet;

	if (!tnw_dmd || !vew)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state < 5) {
		if (tnw_dmd->divew_mode ==
		    CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub
			    (tnw_dmd, &sync_state, &unwock_detected);
			if (wet) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn wet;
			}

			if (sync_state < 5) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn -EAGAIN;
			}
		} ewse {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x80, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	vewsion = ((data[0] & 0x03) << 2);
	vewsion |= ((data[1] & 0xc0) >> 6);
	*vew = (enum cxd2880_dvbt2_vewsion)vewsion;

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_ofdm(stwuct cxd2880_tnwdmd *tnw_dmd,
				  stwuct cxd2880_dvbt2_ofdm *ofdm)
{
	u8 data[5];
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	int wet;

	if (!tnw_dmd || !ofdm)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state != 6) {
		swvt_unfweeze_weg(tnw_dmd);

		wet = -EAGAIN;

		if (tnw_dmd->divew_mode ==
		    CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_ofdm(tnw_dmd->divew_sub,
							  ofdm);

		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1d, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	ofdm->mixed = ((data[0] & 0x20) ? 1 : 0);
	ofdm->is_miso = ((data[0] & 0x10) >> 4);
	ofdm->mode = (enum cxd2880_dvbt2_mode)(data[0] & 0x07);
	ofdm->gi = (enum cxd2880_dvbt2_guawd)((data[1] & 0x70) >> 4);
	ofdm->pp = (enum cxd2880_dvbt2_pp)(data[1] & 0x07);
	ofdm->bw_ext = (data[2] & 0x10) >> 4;
	ofdm->papw = (enum cxd2880_dvbt2_papw)(data[2] & 0x0f);
	ofdm->num_symbows = (data[3] << 8) | data[4];

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_data_pwps(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *pwp_ids,
				       u8 *num_pwps)
{
	u8 w1_post_ok = 0;
	int wet;

	if (!tnw_dmd || !num_pwps)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &w1_post_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!(w1_post_ok & 0x01)) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc1, num_pwps, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (*num_pwps == 0) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EINVAW;
	}

	if (!pwp_ids) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn 0;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc2,
				     pwp_ids,
				     ((*num_pwps > 62) ?
				     62 : *num_pwps));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (*num_pwps > 62) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x0c);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x10, pwp_ids + 62,
					     *num_pwps - 62);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	}

	swvt_unfweeze_weg(tnw_dmd);

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_active_pwp(stwuct cxd2880_tnwdmd
					*tnw_dmd,
					enum
					cxd2880_dvbt2_pwp_btype
					type,
					stwuct cxd2880_dvbt2_pwp
					*pwp_info)
{
	u8 data[20];
	u8 addw = 0;
	u8 index = 0;
	u8 w1_post_ok = 0;
	int wet;

	if (!tnw_dmd || !pwp_info)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &w1_post_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!w1_post_ok) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON)
		addw = 0xa9;
	ewse
		addw = 0x96;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addw, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	if (type == CXD2880_DVBT2_PWP_COMMON && !data[13])
		wetuwn -EAGAIN;

	pwp_info->id = data[index++];
	pwp_info->type =
	    (enum cxd2880_dvbt2_pwp_type)(data[index++] & 0x07);
	pwp_info->paywoad =
	    (enum cxd2880_dvbt2_pwp_paywoad)(data[index++] & 0x1f);
	pwp_info->ff = data[index++] & 0x01;
	pwp_info->fiwst_wf_idx = data[index++] & 0x07;
	pwp_info->fiwst_fwm_idx = data[index++];
	pwp_info->gwoup_id = data[index++];
	pwp_info->pwp_cw =
	    (enum cxd2880_dvbt2_pwp_code_wate)(data[index++] & 0x07);
	pwp_info->consteww =
	    (enum cxd2880_dvbt2_pwp_consteww)(data[index++] & 0x07);
	pwp_info->wot = data[index++] & 0x01;
	pwp_info->fec =
	    (enum cxd2880_dvbt2_pwp_fec)(data[index++] & 0x03);
	pwp_info->num_bwocks_max = (data[index++] & 0x03) << 8;
	pwp_info->num_bwocks_max |= data[index++];
	pwp_info->fwm_int = data[index++];
	pwp_info->tiw_wen = data[index++];
	pwp_info->tiw_type = data[index++] & 0x01;

	pwp_info->in_band_a_fwag = data[index++] & 0x01;
	pwp_info->wsvd = data[index++] << 8;
	pwp_info->wsvd |= data[index++];

	pwp_info->in_band_b_fwag =
	    (pwp_info->wsvd & 0x8000) >> 15;
	pwp_info->pwp_mode =
	    (enum cxd2880_dvbt2_pwp_mode)((pwp_info->wsvd & 0x000c) >> 2);
	pwp_info->static_fwag = (pwp_info->wsvd & 0x0002) >> 1;
	pwp_info->static_padding_fwag = pwp_info->wsvd & 0x0001;
	pwp_info->wsvd = (pwp_info->wsvd & 0x7ff0) >> 4;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_data_pwp_ewwow(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    u8 *pwp_ewwow)
{
	u8 data;
	int wet;

	if (!tnw_dmd || !pwp_ewwow)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &data, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if ((data & 0x01) == 0x00) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xc0, &data, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*pwp_ewwow = data & 0x01;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_w1_change(stwuct cxd2880_tnwdmd
				       *tnw_dmd, u8 *w1_change)
{
	u8 data;
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	int wet;

	if (!tnw_dmd || !w1_change)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state < 5) {
		if (tnw_dmd->divew_mode ==
		    CXD2880_TNWDMD_DIVEWMODE_MAIN) {
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_sync_stat_sub
			    (tnw_dmd, &sync_state, &unwock_detected);
			if (wet) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn wet;
			}

			if (sync_state < 5) {
				swvt_unfweeze_weg(tnw_dmd);
				wetuwn -EAGAIN;
			}
		} ewse {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x5f, &data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	*w1_change = data & 0x01;
	if (*w1_change) {
		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x00, 0x22);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x16, 0x01);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	}
	swvt_unfweeze_weg(tnw_dmd);

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_w1_post(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     stwuct cxd2880_dvbt2_w1post
				     *w1_post)
{
	u8 data[16];
	int wet;

	if (!tnw_dmd || !w1_post)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, data, sizeof(data));
	if (wet)
		wetuwn wet;

	if (!(data[0] & 0x01))
		wetuwn -EAGAIN;

	w1_post->sub_swices_pew_fwame = (data[1] & 0x7f) << 8;
	w1_post->sub_swices_pew_fwame |= data[2];
	w1_post->num_pwps = data[3];
	w1_post->num_aux = data[4] & 0x0f;
	w1_post->aux_cfg_wfu = data[5];
	w1_post->wf_idx = data[6] & 0x07;
	w1_post->fweq = data[7] << 24;
	w1_post->fweq |= data[8] << 16;
	w1_post->fweq |= data[9] << 8;
	w1_post->fweq |= data[10];
	w1_post->fef_type = data[11] & 0x0f;
	w1_post->fef_wength = data[12] << 16;
	w1_post->fef_wength |= data[13] << 8;
	w1_post->fef_wength |= data[14];
	w1_post->fef_intvw = data[15];

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_bbheadew(stwuct cxd2880_tnwdmd
				      *tnw_dmd,
				      enum cxd2880_dvbt2_pwp_btype
				      type,
				      stwuct cxd2880_dvbt2_bbheadew
				      *bbheadew)
{
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 data[14];
	u8 addw = 0;
	int wet;

	if (!tnw_dmd || !bbheadew)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
						       &ts_wock,
						       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!ts_wock) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON) {
		u8 w1_post_ok;
		u8 data;

		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x86, &w1_post_ok, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		if (!(w1_post_ok & 0x01)) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}

		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		if (data == 0) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}
	}

	if (type == CXD2880_DVBT2_PWP_COMMON)
		addw = 0x51;
	ewse
		addw = 0x42;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addw, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	bbheadew->stweam_input =
	    (enum cxd2880_dvbt2_stweam)((data[0] >> 6) & 0x03);
	bbheadew->is_singwe_input_stweam = (data[0] >> 5) & 0x01;
	bbheadew->is_constant_coding_moduwation =
	    (data[0] >> 4) & 0x01;
	bbheadew->issy_indicatow = (data[0] >> 3) & 0x01;
	bbheadew->nuww_packet_dewetion = (data[0] >> 2) & 0x01;
	bbheadew->ext = data[0] & 0x03;

	bbheadew->input_stweam_identifiew = data[1];
	bbheadew->pwp_mode =
	    (data[3] & 0x01) ? CXD2880_DVBT2_PWP_MODE_HEM :
	    CXD2880_DVBT2_PWP_MODE_NM;
	bbheadew->data_fiewd_wength = (data[4] << 8) | data[5];

	if (bbheadew->pwp_mode == CXD2880_DVBT2_PWP_MODE_NM) {
		bbheadew->usew_packet_wength =
		    (data[6] << 8) | data[7];
		bbheadew->sync_byte = data[8];
		bbheadew->issy = 0;
	} ewse {
		bbheadew->usew_packet_wength = 0;
		bbheadew->sync_byte = 0;
		bbheadew->issy =
		    (data[11] << 16) | (data[12] << 8) | data[13];
	}

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_in_bandb_ts_wate(stwuct cxd2880_tnwdmd
					      *tnw_dmd,
					      enum
					      cxd2880_dvbt2_pwp_btype
					      type,
					      u32 *ts_wate_bps)
{
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 w1_post_ok = 0;
	u8 data[4];
	u8 addw = 0;

	int wet;

	if (!tnw_dmd || !ts_wate_bps)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!ts_wock) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &w1_post_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!(w1_post_ok & 0x01)) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON)
		addw = 0xba;
	ewse
		addw = 0xa7;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addw, &data[0], 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if ((data[0] & 0x80) == 0x00) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x25);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON)
		addw = 0xa6;
	ewse
		addw = 0xaa;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     addw, &data[0], 4);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	*ts_wate_bps = ((data[0] & 0x07) << 24) | (data[1] << 16) |
		       (data[2] << 8) | data[3];

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_spectwum_sense(stwuct cxd2880_tnwdmd
					    *tnw_dmd,
					    enum
					    cxd2880_tnwdmd_spectwum_sense
					    *sense)
{
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 eawwy_unwock = 0;
	u8 data = 0;
	int wet;

	if (!tnw_dmd || !sense)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state, &ts_wock,
					       &eawwy_unwock);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state != 6) {
		swvt_unfweeze_weg(tnw_dmd);

		wet = -EAGAIN;

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_spectwum_sense(tnw_dmd->divew_sub,
								    sense);

		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x2f, &data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*sense =
	    (data & 0x01) ? CXD2880_TNWDMD_SPECTWUM_INV :
	    CXD2880_TNWDMD_SPECTWUM_NOWMAW;

	wetuwn 0;
}

static int dvbt2_wead_snw_weg(stwuct cxd2880_tnwdmd *tnw_dmd,
			      u16 *weg_vawue)
{
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	u8 data[2];
	int wet;

	if (!tnw_dmd || !weg_vawue)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state != 6) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x13, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*weg_vawue = (data[0] << 8) | data[1];

	wetuwn wet;
}

static int dvbt2_cawc_snw(stwuct cxd2880_tnwdmd *tnw_dmd,
			  u32 weg_vawue, int *snw)
{
	if (!tnw_dmd || !snw)
		wetuwn -EINVAW;

	if (weg_vawue == 0)
		wetuwn -EAGAIN;

	if (weg_vawue > 10876)
		weg_vawue = 10876;

	*snw = intwog10(weg_vawue) - intwog10(12600 - weg_vawue);
	*snw = (*snw + 839) / 1678 + 32000;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_snw(stwuct cxd2880_tnwdmd *tnw_dmd,
				 int *snw)
{
	u16 weg_vawue = 0;
	int wet;

	if (!tnw_dmd || !snw)
		wetuwn -EINVAW;

	*snw = -1000 * 1000;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SINGWE) {
		wet = dvbt2_wead_snw_weg(tnw_dmd, &weg_vawue);
		if (wet)
			wetuwn wet;

		wet = dvbt2_cawc_snw(tnw_dmd, weg_vawue, snw);
	} ewse {
		int snw_main = 0;
		int snw_sub = 0;

		wet =
		    cxd2880_tnwdmd_dvbt2_mon_snw_divew(tnw_dmd, snw, &snw_main,
						       &snw_sub);
	}

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_snw_divew(stwuct cxd2880_tnwdmd
				       *tnw_dmd, int *snw,
				       int *snw_main, int *snw_sub)
{
	u16 weg_vawue = 0;
	u32 weg_vawue_sum = 0;
	int wet;

	if (!tnw_dmd || !snw || !snw_main || !snw_sub)
		wetuwn -EINVAW;

	*snw = -1000 * 1000;
	*snw_main = -1000 * 1000;
	*snw_sub = -1000 * 1000;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = dvbt2_wead_snw_weg(tnw_dmd, &weg_vawue);
	if (!wet) {
		wet = dvbt2_cawc_snw(tnw_dmd, weg_vawue, snw_main);
		if (wet)
			weg_vawue = 0;
	} ewse if (wet == -EAGAIN) {
		weg_vawue = 0;
	} ewse {
		wetuwn wet;
	}

	weg_vawue_sum += weg_vawue;

	wet = dvbt2_wead_snw_weg(tnw_dmd->divew_sub, &weg_vawue);
	if (!wet) {
		wet = dvbt2_cawc_snw(tnw_dmd->divew_sub, weg_vawue, snw_sub);
		if (wet)
			weg_vawue = 0;
	} ewse if (wet == -EAGAIN) {
		weg_vawue = 0;
	} ewse {
		wetuwn wet;
	}

	weg_vawue_sum += weg_vawue;

	wetuwn dvbt2_cawc_snw(tnw_dmd, weg_vawue_sum, snw);
}

int cxd2880_tnwdmd_dvbt2_mon_packet_ewwow_numbew(stwuct
						 cxd2880_tnwdmd
						 *tnw_dmd,
						 u32 *pen)
{
	int wet;
	u8 data[3];

	if (!tnw_dmd || !pen)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x39, data, sizeof(data));
	if (wet)
		wetuwn wet;

	if (!(data[0] & 0x01))
		wetuwn -EAGAIN;

	*pen = ((data[1] << 8) | data[2]);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_sampwing_offset(stwuct cxd2880_tnwdmd
					     *tnw_dmd, int *ppm)
{
	u8 ctw_vaw_weg[5];
	u8 nominaw_wate_weg[5];
	u32 tww_ctw_vaw = 0;
	u32 twcg_nominaw_wate = 0;
	int num;
	int den;
	int wet;
	u8 sync_state = 0;
	u8 ts_wock = 0;
	u8 unwock_detected = 0;
	s8 diff_uppew = 0;

	if (!tnw_dmd || !ppm)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_sync_stat(tnw_dmd, &sync_state,
					       &ts_wock,
					       &unwock_detected);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (sync_state != 6) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x34, ctw_vaw_weg,
				     sizeof(ctw_vaw_weg));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x04);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, nominaw_wate_weg,
				     sizeof(nominaw_wate_weg));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	diff_uppew =
	    (ctw_vaw_weg[0] & 0x7f) - (nominaw_wate_weg[0] & 0x7f);

	if (diff_uppew < -1 || diff_uppew > 1)
		wetuwn -EAGAIN;

	tww_ctw_vaw = ctw_vaw_weg[1] << 24;
	tww_ctw_vaw |= ctw_vaw_weg[2] << 16;
	tww_ctw_vaw |= ctw_vaw_weg[3] << 8;
	tww_ctw_vaw |= ctw_vaw_weg[4];

	twcg_nominaw_wate = nominaw_wate_weg[1] << 24;
	twcg_nominaw_wate |= nominaw_wate_weg[2] << 16;
	twcg_nominaw_wate |= nominaw_wate_weg[3] << 8;
	twcg_nominaw_wate |= nominaw_wate_weg[4];

	tww_ctw_vaw >>= 1;
	twcg_nominaw_wate >>= 1;

	if (diff_uppew == 1)
		num =
		    (int)((tww_ctw_vaw + 0x80000000u) -
			  twcg_nominaw_wate);
	ewse if (diff_uppew == -1)
		num =
		    -(int)((twcg_nominaw_wate + 0x80000000u) -
			   tww_ctw_vaw);
	ewse
		num = (int)(tww_ctw_vaw - twcg_nominaw_wate);

	den = (nominaw_wate_weg[0] & 0x7f) << 24;
	den |= nominaw_wate_weg[1] << 16;
	den |= nominaw_wate_weg[2] << 8;
	den |= nominaw_wate_weg[3];
	den = (den + (390625 / 2)) / 390625;

	den >>= 1;

	if (num >= 0)
		*ppm = (num + (den / 2)) / den;
	ewse
		*ppm = (num - (den / 2)) / den;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt2_mon_sampwing_offset_sub(stwuct
						 cxd2880_tnwdmd
						 *tnw_dmd,
						 int *ppm)
{
	if (!tnw_dmd || !ppm)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt2_mon_sampwing_offset(tnw_dmd->divew_sub,
							ppm);
}

int cxd2880_tnwdmd_dvbt2_mon_qam(stwuct cxd2880_tnwdmd *tnw_dmd,
				 enum cxd2880_dvbt2_pwp_btype type,
				 enum cxd2880_dvbt2_pwp_consteww *qam)
{
	u8 data;
	u8 w1_post_ok = 0;
	int wet;

	if (!tnw_dmd || !qam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &w1_post_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!(w1_post_ok & 0x01)) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON) {
		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		if (data == 0) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}

		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb1, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	} ewse {
		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x9e, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	}

	swvt_unfweeze_weg(tnw_dmd);

	*qam = (enum cxd2880_dvbt2_pwp_consteww)(data & 0x07);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_code_wate(stwuct cxd2880_tnwdmd
				       *tnw_dmd,
				       enum cxd2880_dvbt2_pwp_btype
				       type,
				       enum
				       cxd2880_dvbt2_pwp_code_wate
				       *code_wate)
{
	u8 data;
	u8 w1_post_ok = 0;
	int wet;

	if (!tnw_dmd || !code_wate)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x86, &w1_post_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	if (!(w1_post_ok & 0x01)) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn -EAGAIN;
	}

	if (type == CXD2880_DVBT2_PWP_COMMON) {
		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb6, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}

		if (data == 0) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn -EAGAIN;
		}

		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0xb0, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	} ewse {
		wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
					     CXD2880_IO_TGT_DMD,
					     0x9d, &data, 1);
		if (wet) {
			swvt_unfweeze_weg(tnw_dmd);
			wetuwn wet;
		}
	}

	swvt_unfweeze_weg(tnw_dmd);

	*code_wate = (enum cxd2880_dvbt2_pwp_code_wate)(data & 0x07);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_pwofiwe(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     enum cxd2880_dvbt2_pwofiwe
				     *pwofiwe)
{
	u8 data;
	int wet;

	if (!tnw_dmd || !pwofiwe)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x22, &data, sizeof(data));
	if (wet)
		wetuwn wet;

	if (data & 0x02) {
		if (data & 0x01)
			*pwofiwe = CXD2880_DVBT2_PWOFIWE_WITE;
		ewse
			*pwofiwe = CXD2880_DVBT2_PWOFIWE_BASE;
	} ewse {
		wet = -EAGAIN;
		if (tnw_dmd->divew_mode ==
		    CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet =
			    cxd2880_tnwdmd_dvbt2_mon_pwofiwe(tnw_dmd->divew_sub,
							     pwofiwe);

		wetuwn wet;
	}

	wetuwn 0;
}

static int dvbt2_cawc_ssi(stwuct cxd2880_tnwdmd *tnw_dmd,
			  int wf_wvw, u8 *ssi)
{
	enum cxd2880_dvbt2_pwp_consteww qam;
	enum cxd2880_dvbt2_pwp_code_wate code_wate;
	int pwew;
	int temp_ssi = 0;
	int wet;

	if (!tnw_dmd || !ssi)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_qam(tnw_dmd, CXD2880_DVBT2_PWP_DATA, &qam);
	if (wet)
		wetuwn wet;

	wet =
	    cxd2880_tnwdmd_dvbt2_mon_code_wate(tnw_dmd, CXD2880_DVBT2_PWP_DATA,
					       &code_wate);
	if (wet)
		wetuwn wet;

	if (code_wate > CXD2880_DVBT2_W2_5 || qam > CXD2880_DVBT2_QAM256)
		wetuwn -EINVAW;

	pwew = wf_wvw - wef_dbm_1000[qam][code_wate];

	if (pwew < -15000)
		temp_ssi = 0;
	ewse if (pwew < 0)
		temp_ssi = ((2 * (pwew + 15000)) + 1500) / 3000;
	ewse if (pwew < 20000)
		temp_ssi = (((4 * pwew) + 500) / 1000) + 10;
	ewse if (pwew < 35000)
		temp_ssi = (((2 * (pwew - 20000)) + 1500) / 3000) + 90;
	ewse
		temp_ssi = 100;

	*ssi = (temp_ssi > 100) ? 100 : (u8)temp_ssi;

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt2_mon_ssi(stwuct cxd2880_tnwdmd *tnw_dmd,
				 u8 *ssi)
{
	int wf_wvw = 0;
	int wet;

	if (!tnw_dmd || !ssi)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_mon_wf_wvw(tnw_dmd, &wf_wvw);
	if (wet)
		wetuwn wet;

	wetuwn dvbt2_cawc_ssi(tnw_dmd, wf_wvw, ssi);
}

int cxd2880_tnwdmd_dvbt2_mon_ssi_sub(stwuct cxd2880_tnwdmd
				     *tnw_dmd, u8 *ssi)
{
	int wf_wvw = 0;
	int wet;

	if (!tnw_dmd || !ssi)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_mon_wf_wvw(tnw_dmd->divew_sub, &wf_wvw);
	if (wet)
		wetuwn wet;

	wetuwn dvbt2_cawc_ssi(tnw_dmd, wf_wvw, ssi);
}
