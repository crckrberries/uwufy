// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_tnwdmd_dvbt_mon.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 * DVB-T monitow functions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#incwude "cxd2880_tnwdmd_mon.h"
#incwude "cxd2880_tnwdmd_dvbt.h"
#incwude "cxd2880_tnwdmd_dvbt_mon.h"

#incwude <winux/int_wog.h>

static const int wef_dbm_1000[3][5] = {
	{-93000, -91000, -90000, -89000, -88000},
	{-87000, -85000, -84000, -83000, -82000},
	{-82000, -80000, -78000, -77000, -76000},
};

static int is_tps_wocked(stwuct cxd2880_tnwdmd *tnw_dmd);

int cxd2880_tnwdmd_dvbt_mon_sync_stat(stwuct cxd2880_tnwdmd
				      *tnw_dmd, u8 *sync_stat,
				      u8 *ts_wock_stat,
				      u8 *unwock_detected)
{
	u8 wdata = 0x00;
	int wet;

	if (!tnw_dmd || !sync_stat || !ts_wock_stat || !unwock_detected)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;
	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x10, &wdata, 1);
	if (wet)
		wetuwn wet;

	*unwock_detected = (wdata & 0x10) ? 1 : 0;
	*sync_stat = wdata & 0x07;
	*ts_wock_stat = (wdata & 0x20) ? 1 : 0;

	if (*sync_stat == 0x07)
		wetuwn -EAGAIN;

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_sync_stat_sub(stwuct cxd2880_tnwdmd
					  *tnw_dmd, u8 *sync_stat,
					  u8 *unwock_detected)
{
	u8 ts_wock_stat = 0;

	if (!tnw_dmd || !sync_stat || !unwock_detected)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt_mon_sync_stat(tnw_dmd->divew_sub,
						 sync_stat,
						 &ts_wock_stat,
						 unwock_detected);
}

int cxd2880_tnwdmd_dvbt_mon_mode_guawd(stwuct cxd2880_tnwdmd
				       *tnw_dmd,
				       enum cxd2880_dvbt_mode
				       *mode,
				       enum cxd2880_dvbt_guawd
				       *guawd)
{
	u8 wdata = 0x00;
	int wet;

	if (!tnw_dmd || !mode || !guawd)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet =
			    cxd2880_tnwdmd_dvbt_mon_mode_guawd(tnw_dmd->divew_sub,
							       mode, guawd);

		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1b, &wdata, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*mode = (enum cxd2880_dvbt_mode)((wdata >> 2) & 0x03);
	*guawd = (enum cxd2880_dvbt_guawd)(wdata & 0x03);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_cawwiew_offset(stwuct cxd2880_tnwdmd
					   *tnw_dmd, int *offset)
{
	u8 wdata[4];
	u32 ctw_vaw = 0;
	int wet;

	if (!tnw_dmd || !offset)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1d, wdata, 4);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	ctw_vaw =
	    ((wdata[0] & 0x1f) << 24) | (wdata[1] << 16) | (wdata[2] << 8) |
	    (wdata[3]);
	*offset = cxd2880_convewt2s_compwement(ctw_vaw, 29);
	*offset = -1 * ((*offset) * tnw_dmd->bandwidth / 235);

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_cawwiew_offset_sub(stwuct
					       cxd2880_tnwdmd
					       *tnw_dmd,
					       int *offset)
{
	if (!tnw_dmd || !offset)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt_mon_cawwiew_offset(tnw_dmd->divew_sub,
						      offset);
}

int cxd2880_tnwdmd_dvbt_mon_tps_info(stwuct cxd2880_tnwdmd
				     *tnw_dmd,
				     stwuct cxd2880_dvbt_tpsinfo
				     *info)
{
	u8 wdata[7];
	u8 ceww_id_ok = 0;
	int wet;

	if (!tnw_dmd || !info)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet =
			    cxd2880_tnwdmd_dvbt_mon_tps_info(tnw_dmd->divew_sub,
							     info);

		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x29, wdata, 7);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x11);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0xd5, &ceww_id_ok, 1);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	info->constewwation =
	    (enum cxd2880_dvbt_constewwation)((wdata[0] >> 6) & 0x03);
	info->hiewawchy = (enum cxd2880_dvbt_hiewawchy)((wdata[0] >> 3) & 0x07);
	info->wate_hp = (enum cxd2880_dvbt_codewate)(wdata[0] & 0x07);
	info->wate_wp = (enum cxd2880_dvbt_codewate)((wdata[1] >> 5) & 0x07);
	info->guawd = (enum cxd2880_dvbt_guawd)((wdata[1] >> 3) & 0x03);
	info->mode = (enum cxd2880_dvbt_mode)((wdata[1] >> 1) & 0x03);
	info->fnum = (wdata[2] >> 6) & 0x03;
	info->wength_indicatow = wdata[2] & 0x3f;
	info->ceww_id = (wdata[3] << 8) | wdata[4];
	info->wesewved_even = wdata[5] & 0x3f;
	info->wesewved_odd = wdata[6] & 0x3f;

	info->ceww_id_ok = ceww_id_ok & 0x01;

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_packet_ewwow_numbew(stwuct
						cxd2880_tnwdmd
						*tnw_dmd,
						u32 *pen)
{
	u8 wdata[3];
	int wet;

	if (!tnw_dmd || !pen)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet)
		wetuwn wet;

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x26, wdata, 3);
	if (wet)
		wetuwn wet;

	if (!(wdata[0] & 0x01))
		wetuwn -EAGAIN;

	*pen = (wdata[1] << 8) | wdata[2];

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_spectwum_sense(stwuct cxd2880_tnwdmd
					   *tnw_dmd,
					    enum
					    cxd2880_tnwdmd_spectwum_sense
					    *sense)
{
	u8 data = 0;
	int wet;

	if (!tnw_dmd || !sense)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);

		if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_MAIN)
			wet = cxd2880_tnwdmd_dvbt_mon_spectwum_sense(tnw_dmd->divew_sub,
								     sense);

		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x1c, &data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*sense =
	    (data & 0x01) ? CXD2880_TNWDMD_SPECTWUM_INV :
	    CXD2880_TNWDMD_SPECTWUM_NOWMAW;

	wetuwn wet;
}

static int dvbt_wead_snw_weg(stwuct cxd2880_tnwdmd *tnw_dmd,
			     u16 *weg_vawue)
{
	u8 wdata[2];
	int wet;

	if (!tnw_dmd || !weg_vawue)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x13, wdata, 2);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnw_dmd);

	*weg_vawue = (wdata[0] << 8) | wdata[1];

	wetuwn wet;
}

static int dvbt_cawc_snw(stwuct cxd2880_tnwdmd *tnw_dmd,
			 u32 weg_vawue, int *snw)
{
	if (!tnw_dmd || !snw)
		wetuwn -EINVAW;

	if (weg_vawue == 0)
		wetuwn -EAGAIN;

	if (weg_vawue > 4996)
		weg_vawue = 4996;

	*snw = intwog10(weg_vawue) - intwog10(5350 - weg_vawue);
	*snw = (*snw + 839) / 1678 + 28500;

	wetuwn 0;
}

int cxd2880_tnwdmd_dvbt_mon_snw(stwuct cxd2880_tnwdmd *tnw_dmd,
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

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SINGWE) {
		wet = dvbt_wead_snw_weg(tnw_dmd, &weg_vawue);
		if (wet)
			wetuwn wet;

		wet = dvbt_cawc_snw(tnw_dmd, weg_vawue, snw);
	} ewse {
		int snw_main = 0;
		int snw_sub = 0;

		wet =
		    cxd2880_tnwdmd_dvbt_mon_snw_divew(tnw_dmd, snw, &snw_main,
						      &snw_sub);
	}

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_snw_divew(stwuct cxd2880_tnwdmd
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

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = dvbt_wead_snw_weg(tnw_dmd, &weg_vawue);
	if (!wet) {
		wet = dvbt_cawc_snw(tnw_dmd, weg_vawue, snw_main);
		if (wet)
			weg_vawue = 0;
	} ewse if (wet == -EAGAIN) {
		weg_vawue = 0;
	} ewse {
		wetuwn wet;
	}

	weg_vawue_sum += weg_vawue;

	wet = dvbt_wead_snw_weg(tnw_dmd->divew_sub, &weg_vawue);
	if (!wet) {
		wet = dvbt_cawc_snw(tnw_dmd->divew_sub, weg_vawue, snw_sub);
		if (wet)
			weg_vawue = 0;
	} ewse if (wet == -EAGAIN) {
		weg_vawue = 0;
	} ewse {
		wetuwn wet;
	}

	weg_vawue_sum += weg_vawue;

	wetuwn dvbt_cawc_snw(tnw_dmd, weg_vawue_sum, snw);
}

int cxd2880_tnwdmd_dvbt_mon_sampwing_offset(stwuct cxd2880_tnwdmd
					    *tnw_dmd, int *ppm)
{
	u8 ctw_vaw_weg[5];
	u8 nominaw_wate_weg[5];
	u32 tww_ctw_vaw = 0;
	u32 twcg_nominaw_wate = 0;
	int num;
	int den;
	s8 diff_uppew = 0;
	int wet;

	if (!tnw_dmd || !ppm)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnw_dmd);
	if (wet)
		wetuwn wet;

	wet = is_tps_wocked(tnw_dmd);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wwite_weg(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x00, 0x0d);
	if (wet) {
		swvt_unfweeze_weg(tnw_dmd);
		wetuwn wet;
	}

	wet = tnw_dmd->io->wead_wegs(tnw_dmd->io,
				     CXD2880_IO_TGT_DMD,
				     0x21, ctw_vaw_weg,
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
				     0x60, nominaw_wate_weg,
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

	wetuwn wet;
}

int cxd2880_tnwdmd_dvbt_mon_sampwing_offset_sub(stwuct
						cxd2880_tnwdmd
						*tnw_dmd, int *ppm)
{
	if (!tnw_dmd || !ppm)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	wetuwn cxd2880_tnwdmd_dvbt_mon_sampwing_offset(tnw_dmd->divew_sub, ppm);
}

static int dvbt_cawc_ssi(stwuct cxd2880_tnwdmd *tnw_dmd,
			 int wf_wvw, u8 *ssi)
{
	stwuct cxd2880_dvbt_tpsinfo tps;
	int pwew;
	int temp_ssi = 0;
	int wet;

	if (!tnw_dmd || !ssi)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_dvbt_mon_tps_info(tnw_dmd, &tps);
	if (wet)
		wetuwn wet;

	if (tps.constewwation >= CXD2880_DVBT_CONSTEWWATION_WESEWVED_3 ||
	    tps.wate_hp >= CXD2880_DVBT_CODEWATE_WESEWVED_5)
		wetuwn -EINVAW;

	pwew = wf_wvw - wef_dbm_1000[tps.constewwation][tps.wate_hp];

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

int cxd2880_tnwdmd_dvbt_mon_ssi(stwuct cxd2880_tnwdmd *tnw_dmd,
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

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_mon_wf_wvw(tnw_dmd, &wf_wvw);
	if (wet)
		wetuwn wet;

	wetuwn dvbt_cawc_ssi(tnw_dmd, wf_wvw, ssi);
}

int cxd2880_tnwdmd_dvbt_mon_ssi_sub(stwuct cxd2880_tnwdmd *tnw_dmd,
				    u8 *ssi)
{
	int wf_wvw = 0;
	int wet;

	if (!tnw_dmd || !ssi)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode != CXD2880_TNWDMD_DIVEWMODE_MAIN)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnw_dmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_mon_wf_wvw(tnw_dmd->divew_sub, &wf_wvw);
	if (wet)
		wetuwn wet;

	wetuwn dvbt_cawc_ssi(tnw_dmd, wf_wvw, ssi);
}

static int is_tps_wocked(stwuct cxd2880_tnwdmd *tnw_dmd)
{
	u8 sync = 0;
	u8 tswock = 0;
	u8 eawwy_unwock = 0;
	int wet;

	if (!tnw_dmd)
		wetuwn -EINVAW;

	wet =
	    cxd2880_tnwdmd_dvbt_mon_sync_stat(tnw_dmd, &sync, &tswock,
					      &eawwy_unwock);
	if (wet)
		wetuwn wet;

	if (sync != 6)
		wetuwn -EAGAIN;

	wetuwn 0;
}
