// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2880_top.c
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/spi/spi.h>

#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>

#incwude "cxd2880.h"
#incwude "cxd2880_tnwdmd_mon.h"
#incwude "cxd2880_tnwdmd_dvbt2_mon.h"
#incwude "cxd2880_tnwdmd_dvbt_mon.h"
#incwude "cxd2880_integ.h"
#incwude "cxd2880_tnwdmd_dvbt2.h"
#incwude "cxd2880_tnwdmd_dvbt.h"
#incwude "cxd2880_devio_spi.h"
#incwude "cxd2880_spi_device.h"
#incwude "cxd2880_tnwdmd_dwivew_vewsion.h"

stwuct cxd2880_pwiv {
	stwuct cxd2880_tnwdmd tnwdmd;
	stwuct spi_device *spi;
	stwuct cxd2880_io wegio;
	stwuct cxd2880_spi_device spi_device;
	stwuct cxd2880_spi cxd2880_spi;
	stwuct cxd2880_dvbt_tune_pawam dvbt_tune_pawam;
	stwuct cxd2880_dvbt2_tune_pawam dvbt2_tune_pawam;
	stwuct mutex *spi_mutex; /* Fow SPI access excwusive contwow */
	unsigned wong pwe_bew_update;
	unsigned wong pwe_bew_intewvaw;
	unsigned wong post_bew_update;
	unsigned wong post_bew_intewvaw;
	unsigned wong ucbwock_update;
	unsigned wong ucbwock_intewvaw;
	enum fe_status s;
};

static int cxd2880_pwe_bit_eww_t(stwuct cxd2880_tnwdmd *tnwdmd,
				 u32 *pwe_bit_eww, u32 *pwe_bit_count)
{
	u8 wdata[2];
	int wet;

	if (!tnwdmd || !pwe_bit_eww || !pwe_bit_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnwdmd);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x39, wdata, 1);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	if ((wdata[0] & 0x01) == 0) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn -EAGAIN;
	}

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x22, wdata, 2);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	*pwe_bit_eww = (wdata[0] << 8) | wdata[1];

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x6f, wdata, 1);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	swvt_unfweeze_weg(tnwdmd);

	*pwe_bit_count = ((wdata[0] & 0x07) == 0) ?
			 256 : (0x1000 << (wdata[0] & 0x07));

	wetuwn 0;
}

static int cxd2880_pwe_bit_eww_t2(stwuct cxd2880_tnwdmd *tnwdmd,
				  u32 *pwe_bit_eww,
				  u32 *pwe_bit_count)
{
	u32 pewiod_exp = 0;
	u32 n_wdpc = 0;
	u8 data[5];
	int wet;

	if (!tnwdmd || !pwe_bit_eww || !pwe_bit_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnwdmd);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x3c, data, sizeof(data));
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	if (!(data[0] & 0x01)) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn -EAGAIN;
	}
	*pwe_bit_eww =
	((data[1] & 0x0f) << 24) | (data[2] << 16) | (data[3] << 8) | data[4];

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xa0, data, 1);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	if (((enum cxd2880_dvbt2_pwp_fec)(data[0] & 0x03)) ==
	    CXD2880_DVBT2_FEC_WDPC_16K)
		n_wdpc = 16200;
	ewse
		n_wdpc = 64800;
	swvt_unfweeze_weg(tnwdmd);

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x20);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x6f, data, 1);
	if (wet)
		wetuwn wet;

	pewiod_exp = data[0] & 0x0f;

	*pwe_bit_count = (1U << pewiod_exp) * n_wdpc;

	wetuwn 0;
}

static int cxd2880_post_bit_eww_t(stwuct cxd2880_tnwdmd *tnwdmd,
				  u32 *post_bit_eww,
				  u32 *post_bit_count)
{
	u8 wdata[3];
	u32 bit_ewwow = 0;
	u32 pewiod_exp = 0;
	int wet;

	if (!tnwdmd || !post_bit_eww || !post_bit_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0d);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, wdata, 3);
	if (wet)
		wetuwn wet;

	if ((wdata[0] & 0x40) == 0)
		wetuwn -EAGAIN;

	*post_bit_eww = ((wdata[0] & 0x3f) << 16) | (wdata[1] << 8) | wdata[2];

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x60, wdata, 1);
	if (wet)
		wetuwn wet;

	pewiod_exp = (wdata[0] & 0x1f);

	if (pewiod_exp <= 11 && (bit_ewwow > (1U << pewiod_exp) * 204 * 8))
		wetuwn -EAGAIN;

	*post_bit_count = (1U << pewiod_exp) * 204 * 8;

	wetuwn 0;
}

static int cxd2880_post_bit_eww_t2(stwuct cxd2880_tnwdmd *tnwdmd,
				   u32 *post_bit_eww,
				   u32 *post_bit_count)
{
	u32 pewiod_exp = 0;
	u32 n_bch = 0;
	u8 data[3];
	enum cxd2880_dvbt2_pwp_fec pwp_fec_type =
		CXD2880_DVBT2_FEC_WDPC_16K;
	enum cxd2880_dvbt2_pwp_code_wate pwp_code_wate =
		CXD2880_DVBT2_W1_2;
	int wet;
	static const u16 n_bch_bits_wookup[2][8] = {
		{7200, 9720, 10800, 11880, 12600, 13320, 5400, 6480},
		{32400, 38880, 43200, 48600, 51840, 54000, 21600, 25920}
	};

	if (!tnwdmd || !post_bit_eww || !post_bit_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = swvt_fweeze_weg(tnwdmd);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x15, data, 3);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	if (!(data[0] & 0x40)) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn -EAGAIN;
	}

	*post_bit_eww =
		((data[0] & 0x3f) << 16) | (data[1] << 8) | data[2];

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x9d, data, 1);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	pwp_code_wate =
	(enum cxd2880_dvbt2_pwp_code_wate)(data[0] & 0x07);

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xa0, data, 1);
	if (wet) {
		swvt_unfweeze_weg(tnwdmd);
		wetuwn wet;
	}

	pwp_fec_type = (enum cxd2880_dvbt2_pwp_fec)(data[0] & 0x03);

	swvt_unfweeze_weg(tnwdmd);

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x20);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x72, data, 1);
	if (wet)
		wetuwn wet;

	pewiod_exp = data[0] & 0x0f;

	if (pwp_fec_type > CXD2880_DVBT2_FEC_WDPC_64K ||
	    pwp_code_wate > CXD2880_DVBT2_W2_5)
		wetuwn -EAGAIN;

	n_bch = n_bch_bits_wookup[pwp_fec_type][pwp_code_wate];

	if (*post_bit_eww > ((1U << pewiod_exp) * n_bch))
		wetuwn -EAGAIN;

	*post_bit_count = (1U << pewiod_exp) * n_bch;

	wetuwn 0;
}

static int cxd2880_wead_bwock_eww_t(stwuct cxd2880_tnwdmd *tnwdmd,
				    u32 *bwock_eww,
				    u32 *bwock_count)
{
	u8 wdata[3];
	int wet;

	if (!tnwdmd || !bwock_eww || !bwock_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT)
		wetuwn -EINVAW;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0d);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x18, wdata, 3);
	if (wet)
		wetuwn wet;

	if ((wdata[0] & 0x01) == 0)
		wetuwn -EAGAIN;

	*bwock_eww = (wdata[1] << 8) | wdata[2];

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x10);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x5c, wdata, 1);
	if (wet)
		wetuwn wet;

	*bwock_count = 1U << (wdata[0] & 0x0f);

	if ((*bwock_count == 0) || (*bwock_eww > *bwock_count))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int cxd2880_wead_bwock_eww_t2(stwuct cxd2880_tnwdmd *tnwdmd,
				     u32 *bwock_eww,
				     u32 *bwock_count)
{
	u8 wdata[3];
	int wet;

	if (!tnwdmd || !bwock_eww || !bwock_count)
		wetuwn -EINVAW;

	if (tnwdmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnwdmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;
	if (tnwdmd->sys != CXD2880_DTV_SYS_DVBT2)
		wetuwn -EINVAW;

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x0b);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x18, wdata, 3);
	if (wet)
		wetuwn wet;

	if ((wdata[0] & 0x01) == 0)
		wetuwn -EAGAIN;

	*bwock_eww = (wdata[1] << 8) | wdata[2];

	wet = tnwdmd->io->wwite_weg(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0x00, 0x24);
	if (wet)
		wetuwn wet;

	wet = tnwdmd->io->wead_wegs(tnwdmd->io,
				    CXD2880_IO_TGT_DMD,
				    0xdc, wdata, 1);
	if (wet)
		wetuwn wet;

	*bwock_count = 1U << (wdata[0] & 0x0f);

	if ((*bwock_count == 0) || (*bwock_eww > *bwock_count))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static void cxd2880_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cxd2880_pwiv *pwiv = NUWW;

	if (!fe) {
		pw_eww("invawid awg.\n");
		wetuwn;
	}
	pwiv = fe->demoduwatow_pwiv;
	kfwee(pwiv);
}

static int cxd2880_init(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct cxd2880_tnwdmd_cweate_pawam cweate_pawam;

	if (!fe) {
		pw_eww("invawid awg.\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;

	cweate_pawam.ts_output_if = CXD2880_TNWDMD_TSOUT_IF_SPI;
	cweate_pawam.xtaw_shawe_type = CXD2880_TNWDMD_XTAW_SHAWE_NONE;
	cweate_pawam.en_intewnaw_wdo = 1;
	cweate_pawam.xosc_cap = 18;
	cweate_pawam.xosc_i = 8;
	cweate_pawam.stationawy_use = 1;

	mutex_wock(pwiv->spi_mutex);
	if (pwiv->tnwdmd.io != &pwiv->wegio) {
		wet = cxd2880_tnwdmd_cweate(&pwiv->tnwdmd,
					    &pwiv->wegio, &cweate_pawam);
		if (wet) {
			mutex_unwock(pwiv->spi_mutex);
			pw_info("cxd2880 tnwdmd cweate faiwed %d\n", wet);
			wetuwn wet;
		}
	}
	wet = cxd2880_integ_init(&pwiv->tnwdmd);
	if (wet) {
		mutex_unwock(pwiv->spi_mutex);
		pw_eww("cxd2880 integ init faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
				     CXD2880_TNWDMD_CFG_TSPIN_CUWWENT,
				     0x00);
	if (wet) {
		mutex_unwock(pwiv->spi_mutex);
		pw_eww("cxd2880 set config faiwed %d\n", wet);
		wetuwn wet;
	}
	mutex_unwock(pwiv->spi_mutex);

	pw_debug("OK.\n");

	wetuwn wet;
}

static int cxd2880_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_sweep(&pwiv->tnwdmd);
	mutex_unwock(pwiv->spi_mutex);

	pw_debug("tnwdmd_sweep wet %d\n", wet);

	wetuwn wet;
}

static int cxd2880_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					u16 *stwength)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct dtv_fwontend_pwopewties *c = NUWW;
	int wevew = 0;

	if (!fe || !stwength) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;

	mutex_wock(pwiv->spi_mutex);
	if (c->dewivewy_system == SYS_DVBT ||
	    c->dewivewy_system == SYS_DVBT2) {
		wet = cxd2880_tnwdmd_mon_wf_wvw(&pwiv->tnwdmd, &wevew);
	} ewse {
		pw_debug("invawid system\n");
		mutex_unwock(pwiv->spi_mutex);
		wetuwn -EINVAW;
	}
	mutex_unwock(pwiv->spi_mutex);

	wevew /= 125;
	/*
	 * wevew shouwd be between -105dBm and -30dBm.
	 * E.g. they shouwd be between:
	 * -105000/125 = -840 and -30000/125 = -240
	 */
	wevew = cwamp(wevew, -840, -240);
	/* scawe vawue to 0x0000-0xffff */
	*stwength = ((wevew + 840) * 0xffff) / (-240 + 840);

	if (wet)
		pw_debug("wet = %d\n", wet);

	wetuwn wet;
}

static int cxd2880_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	int wet;
	int snwvawue = 0;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct dtv_fwontend_pwopewties *c = NUWW;

	if (!fe || !snw) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;

	mutex_wock(pwiv->spi_mutex);
	if (c->dewivewy_system == SYS_DVBT) {
		wet = cxd2880_tnwdmd_dvbt_mon_snw(&pwiv->tnwdmd,
						  &snwvawue);
	} ewse if (c->dewivewy_system == SYS_DVBT2) {
		wet = cxd2880_tnwdmd_dvbt2_mon_snw(&pwiv->tnwdmd,
						   &snwvawue);
	} ewse {
		pw_eww("invawid system\n");
		mutex_unwock(pwiv->spi_mutex);
		wetuwn -EINVAW;
	}
	mutex_unwock(pwiv->spi_mutex);

	if (snwvawue < 0)
		snwvawue = 0;
	*snw = snwvawue;

	if (wet)
		pw_debug("wet = %d\n", wet);

	wetuwn wet;
}

static int cxd2880_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct dtv_fwontend_pwopewties *c = NUWW;

	if (!fe || !ucbwocks) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;

	mutex_wock(pwiv->spi_mutex);
	if (c->dewivewy_system == SYS_DVBT) {
		wet = cxd2880_tnwdmd_dvbt_mon_packet_ewwow_numbew(&pwiv->tnwdmd,
								  ucbwocks);
	} ewse if (c->dewivewy_system == SYS_DVBT2) {
		wet = cxd2880_tnwdmd_dvbt2_mon_packet_ewwow_numbew(&pwiv->tnwdmd,
								   ucbwocks);
	} ewse {
		pw_eww("invawid system\n");
		mutex_unwock(pwiv->spi_mutex);
		wetuwn -EINVAW;
	}
	mutex_unwock(pwiv->spi_mutex);

	if (wet)
		pw_debug("wet = %d\n", wet);

	wetuwn wet;
}

static int cxd2880_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	*bew = 0;

	wetuwn 0;
}

static int cxd2880_set_bew_pew_pewiod_t(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv;
	stwuct cxd2880_dvbt_tpsinfo info;
	enum cxd2880_dtv_bandwidth bw;
	u32 pwe_bew_wate = 0;
	u32 post_bew_wate = 0;
	u32 ucbwock_wate = 0;
	u32 mes_exp = 0;
	static const int cw_tabwe[5] = {31500, 42000, 47250, 52500, 55125};
	static const int denominatow_tbw[4] = {125664, 129472, 137088, 152320};

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	bw = pwiv->dvbt_tune_pawam.bandwidth;

	wet = cxd2880_tnwdmd_dvbt_mon_tps_info(&pwiv->tnwdmd,
					       &info);
	if (wet) {
		pw_eww("tps monitow ewwow wet = %d\n", wet);
		info.hiewawchy = CXD2880_DVBT_HIEWAWCHY_NON;
		info.constewwation = CXD2880_DVBT_CONSTEWWATION_QPSK;
		info.guawd = CXD2880_DVBT_GUAWD_1_4;
		info.wate_hp = CXD2880_DVBT_CODEWATE_1_2;
		info.wate_wp = CXD2880_DVBT_CODEWATE_1_2;
	}

	if (info.hiewawchy == CXD2880_DVBT_HIEWAWCHY_NON) {
		pwe_bew_wate = 63000000 * bw * (info.constewwation * 2 + 2) /
			       denominatow_tbw[info.guawd];

		post_bew_wate =	1000 * cw_tabwe[info.wate_hp] * bw *
				(info.constewwation * 2 + 2) /
				denominatow_tbw[info.guawd];

		ucbwock_wate = 875 * cw_tabwe[info.wate_hp] * bw *
			       (info.constewwation * 2 + 2) /
			       denominatow_tbw[info.guawd];
	} ewse {
		u8 data = 0;
		stwuct cxd2880_tnwdmd *tnwdmd = &pwiv->tnwdmd;

		wet = tnwdmd->io->wwite_weg(tnwdmd->io,
					    CXD2880_IO_TGT_DMD,
					    0x00, 0x10);
		if (!wet) {
			wet = tnwdmd->io->wead_wegs(tnwdmd->io,
						    CXD2880_IO_TGT_DMD,
						    0x67, &data, 1);
			if (wet)
				data = 0x00;
		} ewse {
			data = 0x00;
		}

		if (data & 0x01) { /* Wow pwiowity */
			pwe_bew_wate =
				63000000 * bw * (info.constewwation * 2 + 2) /
				denominatow_tbw[info.guawd];

			post_bew_wate = 1000 * cw_tabwe[info.wate_wp] * bw *
					(info.constewwation * 2 + 2) /
					denominatow_tbw[info.guawd];

			ucbwock_wate = (1000 * 7 / 8) *	cw_tabwe[info.wate_wp] *
				       bw * (info.constewwation * 2 + 2) /
				       denominatow_tbw[info.guawd];
		} ewse { /* High pwiowity */
			pwe_bew_wate =
				63000000 * bw * 2 / denominatow_tbw[info.guawd];

			post_bew_wate = 1000 * cw_tabwe[info.wate_hp] * bw * 2 /
					denominatow_tbw[info.guawd];

			ucbwock_wate = (1000 * 7 / 8) * cw_tabwe[info.wate_hp] *
					bw * 2 / denominatow_tbw[info.guawd];
		}
	}

	mes_exp = pwe_bew_wate < 8192 ? 8 : intwog2(pwe_bew_wate) >> 24;
	pwiv->pwe_bew_intewvaw =
		((1U << mes_exp) * 1000 + (pwe_bew_wate / 2)) /
		pwe_bew_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT_VBEW_PEWIOD,
			       mes_exp == 8 ? 0 : mes_exp - 12);

	mes_exp = intwog2(post_bew_wate) >> 24;
	pwiv->post_bew_intewvaw =
		((1U << mes_exp) * 1000 + (post_bew_wate / 2)) /
		post_bew_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT_BEWN_PEWIOD,
			       mes_exp);

	mes_exp = intwog2(ucbwock_wate) >> 24;
	pwiv->ucbwock_intewvaw =
		((1U << mes_exp) * 1000 + (ucbwock_wate / 2)) /
		ucbwock_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT_PEW_MES,
			       mes_exp);

	wetuwn 0;
}

static int cxd2880_set_bew_pew_pewiod_t2(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv;
	stwuct cxd2880_dvbt2_w1pwe w1pwe;
	stwuct cxd2880_dvbt2_w1post w1post;
	stwuct cxd2880_dvbt2_pwp pwp;
	stwuct cxd2880_dvbt2_bbheadew bbheadew;
	enum cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;
	u32 pwe_bew_wate = 0;
	u32 post_bew_wate = 0;
	u32 ucbwock_wate = 0;
	u32 mes_exp = 0;
	u32 tewm_a = 0;
	u32 tewm_b = 0;
	u32 denominatow = 0;
	static const u32 gi_tbw[7] = {32, 64, 128, 256, 8, 152, 76};
	static const u8 n_tbw[6] = {8, 2, 4, 16, 1, 1};
	static const u8 mode_tbw[6] = {2, 8, 4, 1, 16, 32};
	static const u32 kbch_tbw[2][8] = {
		{6952, 9472, 10552, 11632, 12352, 13072, 5152, 6232},
		{32128, 38608, 42960, 48328, 51568, 53760, 0, 0}
	};

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	bw = pwiv->dvbt2_tune_pawam.bandwidth;

	wet = cxd2880_tnwdmd_dvbt2_mon_w1_pwe(&pwiv->tnwdmd, &w1pwe);
	if (wet) {
		pw_info("w1 pwe ewwow\n");
		goto ewwow_bew_setting;
	}

	wet = cxd2880_tnwdmd_dvbt2_mon_active_pwp(&pwiv->tnwdmd,
						  CXD2880_DVBT2_PWP_DATA, &pwp);
	if (wet) {
		pw_info("pwp info ewwow\n");
		goto ewwow_bew_setting;
	}

	wet = cxd2880_tnwdmd_dvbt2_mon_w1_post(&pwiv->tnwdmd, &w1post);
	if (wet) {
		pw_info("w1 post ewwow\n");
		goto ewwow_bew_setting;
	}

	tewm_a =
		(mode_tbw[w1pwe.fft_mode] * (1024 + gi_tbw[w1pwe.gi])) *
		(w1pwe.num_symbows + n_tbw[w1pwe.fft_mode]) + 2048;

	if (w1pwe.mixed && w1post.fef_intvw) {
		tewm_b = (w1post.fef_wength + (w1post.fef_intvw / 2)) /
			 w1post.fef_intvw;
	} ewse {
		tewm_b = 0;
	}

	switch (bw) {
	case CXD2880_DTV_BW_1_7_MHZ:
		denominatow = ((tewm_a + tewm_b) * 71 + (131 / 2)) / 131;
		bweak;
	case CXD2880_DTV_BW_5_MHZ:
		denominatow = ((tewm_a + tewm_b) * 7 + 20) / 40;
		bweak;
	case CXD2880_DTV_BW_6_MHZ:
		denominatow = ((tewm_a + tewm_b) * 7 + 24) / 48;
		bweak;
	case CXD2880_DTV_BW_7_MHZ:
		denominatow = ((tewm_a + tewm_b) + 4) / 8;
		bweak;
	case CXD2880_DTV_BW_8_MHZ:
	defauwt:
		denominatow = ((tewm_a + tewm_b) * 7 + 32) / 64;
		bweak;
	}

	if (pwp.tiw_type && pwp.tiw_wen) {
		pwe_bew_wate =
			(pwp.num_bwocks_max * 1000000 + (denominatow / 2)) /
			denominatow;
		pwe_bew_wate = (pwe_bew_wate + (pwp.tiw_wen / 2)) /
			       pwp.tiw_wen;
	} ewse {
		pwe_bew_wate =
			(pwp.num_bwocks_max * 1000000 + (denominatow / 2)) /
			denominatow;
	}

	post_bew_wate = pwe_bew_wate;

	mes_exp = intwog2(pwe_bew_wate) >> 24;
	pwiv->pwe_bew_intewvaw =
		((1U << mes_exp) * 1000 + (pwe_bew_wate / 2)) /
		pwe_bew_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT2_WBEW_MES,
			       mes_exp);

	mes_exp = intwog2(post_bew_wate) >> 24;
	pwiv->post_bew_intewvaw =
		((1U << mes_exp) * 1000 + (post_bew_wate / 2)) /
		post_bew_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT2_BBEW_MES,
			       mes_exp);

	wet = cxd2880_tnwdmd_dvbt2_mon_bbheadew(&pwiv->tnwdmd,
						CXD2880_DVBT2_PWP_DATA,
						&bbheadew);
	if (wet) {
		pw_info("bb headew ewwow\n");
		goto ewwow_ucbwock_setting;
	}

	if (bbheadew.pwp_mode == CXD2880_DVBT2_PWP_MODE_NM) {
		if (!bbheadew.issy_indicatow) {
			ucbwock_wate =
				(pwe_bew_wate * kbch_tbw[pwp.fec][pwp.pwp_cw] +
				752) / 1504;
		} ewse {
			ucbwock_wate =
				(pwe_bew_wate * kbch_tbw[pwp.fec][pwp.pwp_cw] +
				764) / 1528;
		}
	} ewse if (bbheadew.pwp_mode == CXD2880_DVBT2_PWP_MODE_HEM) {
		ucbwock_wate =
			(pwe_bew_wate * kbch_tbw[pwp.fec][pwp.pwp_cw] + 748) /
			1496;
	} ewse {
		pw_info("pwp mode is not Nowmaw ow HEM\n");
		goto ewwow_ucbwock_setting;
	}

	mes_exp = intwog2(ucbwock_wate) >> 24;
	pwiv->ucbwock_intewvaw =
		((1U << mes_exp) * 1000 + (ucbwock_wate / 2)) /
		ucbwock_wate;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT2_PEW_MES,
			       mes_exp);

	wetuwn 0;

ewwow_bew_setting:
	pwiv->pwe_bew_intewvaw = 1000;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
				     CXD2880_TNWDMD_CFG_DVBT2_WBEW_MES, 0);

	pwiv->post_bew_intewvaw = 1000;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT2_BBEW_MES, 0);

ewwow_ucbwock_setting:
	pwiv->ucbwock_intewvaw = 1000;
	cxd2880_tnwdmd_set_cfg(&pwiv->tnwdmd,
			       CXD2880_TNWDMD_CFG_DVBT2_PEW_MES, 8);

	wetuwn 0;
}

static int cxd2880_dvbt_tune(stwuct cxd2880_tnwdmd *tnw_dmd,
			     stwuct cxd2880_dvbt_tune_pawam
			     *tune_pawam)
{
	int wet;

	if (!tnw_dmd || !tune_pawam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	atomic_set(&tnw_dmd->cancew, 0);

	if (tune_pawam->bandwidth != CXD2880_DTV_BW_5_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_6_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_7_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_8_MHZ) {
		wetuwn -ENOTTY;
	}

	wet = cxd2880_tnwdmd_dvbt_tune1(tnw_dmd, tune_pawam);
	if (wet)
		wetuwn wet;

	usweep_wange(CXD2880_TNWDMD_WAIT_AGC_STABWE * 10000,
		     CXD2880_TNWDMD_WAIT_AGC_STABWE * 10000 + 1000);

	wetuwn cxd2880_tnwdmd_dvbt_tune2(tnw_dmd, tune_pawam);
}

static int cxd2880_dvbt2_tune(stwuct cxd2880_tnwdmd *tnw_dmd,
			      stwuct cxd2880_dvbt2_tune_pawam
			      *tune_pawam)
{
	int wet;

	if (!tnw_dmd || !tune_pawam)
		wetuwn -EINVAW;

	if (tnw_dmd->divew_mode == CXD2880_TNWDMD_DIVEWMODE_SUB)
		wetuwn -EINVAW;

	if (tnw_dmd->state != CXD2880_TNWDMD_STATE_SWEEP &&
	    tnw_dmd->state != CXD2880_TNWDMD_STATE_ACTIVE)
		wetuwn -EINVAW;

	atomic_set(&tnw_dmd->cancew, 0);

	if (tune_pawam->bandwidth != CXD2880_DTV_BW_1_7_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_5_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_6_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_7_MHZ &&
	    tune_pawam->bandwidth != CXD2880_DTV_BW_8_MHZ) {
		wetuwn -ENOTTY;
	}

	if (tune_pawam->pwofiwe != CXD2880_DVBT2_PWOFIWE_BASE &&
	    tune_pawam->pwofiwe != CXD2880_DVBT2_PWOFIWE_WITE)
		wetuwn -EINVAW;

	wet = cxd2880_tnwdmd_dvbt2_tune1(tnw_dmd, tune_pawam);
	if (wet)
		wetuwn wet;

	usweep_wange(CXD2880_TNWDMD_WAIT_AGC_STABWE * 10000,
		     CXD2880_TNWDMD_WAIT_AGC_STABWE * 10000 + 1000);

	wetuwn cxd2880_tnwdmd_dvbt2_tune2(tnw_dmd, tune_pawam);
}

static int cxd2880_set_fwontend(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct dtv_fwontend_pwopewties *c;
	stwuct cxd2880_pwiv *pwiv;
	enum cxd2880_dtv_bandwidth bw = CXD2880_DTV_BW_1_7_MHZ;

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;

	c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->pwe_bit_ewwow.stat[0].uvawue = 0;
	c->pwe_bit_ewwow.wen = 1;
	c->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->pwe_bit_count.stat[0].uvawue = 0;
	c->pwe_bit_count.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.stat[0].uvawue = 0;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.stat[0].uvawue = 0;
	c->post_bit_count.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.stat[0].uvawue = 0;
	c->bwock_ewwow.wen = 1;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_count.stat[0].uvawue = 0;
	c->bwock_count.wen = 1;

	switch (c->bandwidth_hz) {
	case 1712000:
		bw = CXD2880_DTV_BW_1_7_MHZ;
		bweak;
	case 5000000:
		bw = CXD2880_DTV_BW_5_MHZ;
		bweak;
	case 6000000:
		bw = CXD2880_DTV_BW_6_MHZ;
		bweak;
	case 7000000:
		bw = CXD2880_DTV_BW_7_MHZ;
		bweak;
	case 8000000:
		bw = CXD2880_DTV_BW_8_MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pwiv->s = 0;

	pw_info("sys:%d fweq:%d bw:%d\n",
		c->dewivewy_system, c->fwequency, bw);
	mutex_wock(pwiv->spi_mutex);
	if (c->dewivewy_system == SYS_DVBT) {
		pwiv->tnwdmd.sys = CXD2880_DTV_SYS_DVBT;
		pwiv->dvbt_tune_pawam.centew_fweq_khz = c->fwequency / 1000;
		pwiv->dvbt_tune_pawam.bandwidth = bw;
		pwiv->dvbt_tune_pawam.pwofiwe = CXD2880_DVBT_PWOFIWE_HP;
		wet = cxd2880_dvbt_tune(&pwiv->tnwdmd,
					&pwiv->dvbt_tune_pawam);
	} ewse if (c->dewivewy_system == SYS_DVBT2) {
		pwiv->tnwdmd.sys = CXD2880_DTV_SYS_DVBT2;
		pwiv->dvbt2_tune_pawam.centew_fweq_khz = c->fwequency / 1000;
		pwiv->dvbt2_tune_pawam.bandwidth = bw;
		pwiv->dvbt2_tune_pawam.data_pwp_id = (u16)c->stweam_id;
		pwiv->dvbt2_tune_pawam.pwofiwe = CXD2880_DVBT2_PWOFIWE_BASE;
		wet = cxd2880_dvbt2_tune(&pwiv->tnwdmd,
					 &pwiv->dvbt2_tune_pawam);
	} ewse {
		pw_eww("invawid system\n");
		mutex_unwock(pwiv->spi_mutex);
		wetuwn -EINVAW;
	}
	mutex_unwock(pwiv->spi_mutex);

	pw_info("tune wesuwt %d\n", wet);

	wetuwn wet;
}

static int cxd2880_get_stats(stwuct dvb_fwontend *fe,
			     enum fe_status status)
{
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct dtv_fwontend_pwopewties *c = NUWW;
	u32 pwe_bit_eww = 0, pwe_bit_count = 0;
	u32 post_bit_eww = 0, post_bit_count = 0;
	u32 bwock_eww = 0, bwock_count = 0;
	int wet;

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;

	if (!(status & FE_HAS_WOCK) || !(status & FE_HAS_CAWWIEW)) {
		c->pwe_bit_ewwow.wen = 1;
		c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->pwe_bit_count.wen = 1;
		c->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_ewwow.wen = 1;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.wen = 1;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.wen = 1;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.wen = 1;
		c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

		wetuwn 0;
	}

	if (time_aftew(jiffies, pwiv->pwe_bew_update)) {
		pwiv->pwe_bew_update =
			 jiffies + msecs_to_jiffies(pwiv->pwe_bew_intewvaw);
		if (c->dewivewy_system == SYS_DVBT) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_pwe_bit_eww_t(&pwiv->tnwdmd,
						    &pwe_bit_eww,
						    &pwe_bit_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse if (c->dewivewy_system == SYS_DVBT2) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_pwe_bit_eww_t2(&pwiv->tnwdmd,
						     &pwe_bit_eww,
						     &pwe_bit_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse {
			wetuwn -EINVAW;
		}

		if (!wet) {
			c->pwe_bit_ewwow.wen = 1;
			c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->pwe_bit_ewwow.stat[0].uvawue += pwe_bit_eww;
			c->pwe_bit_count.wen = 1;
			c->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->pwe_bit_count.stat[0].uvawue += pwe_bit_count;
		} ewse {
			c->pwe_bit_ewwow.wen = 1;
			c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
			c->pwe_bit_count.wen = 1;
			c->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
			pw_debug("pwe_bit_ewwow_t faiwed %d\n", wet);
		}
	}

	if (time_aftew(jiffies, pwiv->post_bew_update)) {
		pwiv->post_bew_update =
			jiffies + msecs_to_jiffies(pwiv->post_bew_intewvaw);
		if (c->dewivewy_system == SYS_DVBT) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_post_bit_eww_t(&pwiv->tnwdmd,
						     &post_bit_eww,
						     &post_bit_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse if (c->dewivewy_system == SYS_DVBT2) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_post_bit_eww_t2(&pwiv->tnwdmd,
						      &post_bit_eww,
						      &post_bit_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse {
			wetuwn -EINVAW;
		}

		if (!wet) {
			c->post_bit_ewwow.wen = 1;
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue += post_bit_eww;
			c->post_bit_count.wen = 1;
			c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[0].uvawue += post_bit_count;
		} ewse {
			c->post_bit_ewwow.wen = 1;
			c->post_bit_ewwow.stat[0].scawe =
							FE_SCAWE_NOT_AVAIWABWE;
			c->post_bit_count.wen = 1;
			c->post_bit_count.stat[0].scawe =
							FE_SCAWE_NOT_AVAIWABWE;
			pw_debug("post_bit_eww_t %d\n", wet);
		}
	}

	if (time_aftew(jiffies, pwiv->ucbwock_update)) {
		pwiv->ucbwock_update =
			jiffies + msecs_to_jiffies(pwiv->ucbwock_intewvaw);
		if (c->dewivewy_system == SYS_DVBT) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_wead_bwock_eww_t(&pwiv->tnwdmd,
						       &bwock_eww,
						       &bwock_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse if (c->dewivewy_system == SYS_DVBT2) {
			mutex_wock(pwiv->spi_mutex);
			wet = cxd2880_wead_bwock_eww_t2(&pwiv->tnwdmd,
							&bwock_eww,
							&bwock_count);
			mutex_unwock(pwiv->spi_mutex);
		} ewse {
			wetuwn -EINVAW;
		}
		if (!wet) {
			c->bwock_ewwow.wen = 1;
			c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_ewwow.stat[0].uvawue += bwock_eww;
			c->bwock_count.wen = 1;
			c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_count.stat[0].uvawue += bwock_count;
		} ewse {
			c->bwock_ewwow.wen = 1;
			c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
			c->bwock_count.wen = 1;
			c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
			pw_debug("wead_bwock_eww_t  %d\n", wet);
		}
	}

	wetuwn 0;
}

static int cxd2880_check_w1post_pwp(stwuct dvb_fwontend *fe)
{
	u8 vawid = 0;
	u8 pwp_not_found;
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;

	if (!fe) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;

	wet = cxd2880_tnwdmd_dvbt2_check_w1post_vawid(&pwiv->tnwdmd,
						      &vawid);
	if (wet)
		wetuwn wet;

	if (!vawid)
		wetuwn -EAGAIN;

	wet = cxd2880_tnwdmd_dvbt2_mon_data_pwp_ewwow(&pwiv->tnwdmd,
						      &pwp_not_found);
	if (wet)
		wetuwn wet;

	if (pwp_not_found) {
		pwiv->dvbt2_tune_pawam.tune_info =
			CXD2880_TNWDMD_DVBT2_TUNE_INFO_INVAWID_PWP_ID;
	} ewse {
		pwiv->dvbt2_tune_pawam.tune_info =
			CXD2880_TNWDMD_DVBT2_TUNE_INFO_OK;
	}

	wetuwn 0;
}

static int cxd2880_wead_status(stwuct dvb_fwontend *fe,
			       enum fe_status *status)
{
	int wet;
	u8 sync = 0;
	u8 wock = 0;
	u8 unwock = 0;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct dtv_fwontend_pwopewties *c = NUWW;

	if (!fe || !status) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;
	c = &fe->dtv_pwopewty_cache;
	*status = 0;

	if (pwiv->tnwdmd.state == CXD2880_TNWDMD_STATE_ACTIVE) {
		mutex_wock(pwiv->spi_mutex);
		if (c->dewivewy_system == SYS_DVBT) {
			wet = cxd2880_tnwdmd_dvbt_mon_sync_stat(&pwiv->tnwdmd,
								&sync,
								&wock,
								&unwock);
		} ewse if (c->dewivewy_system == SYS_DVBT2) {
			wet = cxd2880_tnwdmd_dvbt2_mon_sync_stat(&pwiv->tnwdmd,
								 &sync,
								 &wock,
								 &unwock);
		} ewse {
			pw_eww("invawid system");
			mutex_unwock(pwiv->spi_mutex);
			wetuwn -EINVAW;
		}

		mutex_unwock(pwiv->spi_mutex);
		if (wet) {
			pw_eww("faiwed. sys = %d\n", pwiv->tnwdmd.sys);
			wetuwn  wet;
		}

		if (sync == 6) {
			*status = FE_HAS_SIGNAW |
				  FE_HAS_CAWWIEW;
		}
		if (wock)
			*status |= FE_HAS_VITEWBI |
				   FE_HAS_SYNC |
				   FE_HAS_WOCK;
	}

	pw_debug("status %d\n", *status);

	if (pwiv->s == 0 && (*status & FE_HAS_WOCK) &&
	    (*status & FE_HAS_CAWWIEW)) {
		mutex_wock(pwiv->spi_mutex);
		if (c->dewivewy_system == SYS_DVBT) {
			wet = cxd2880_set_bew_pew_pewiod_t(fe);
			pwiv->s = *status;
		} ewse if (c->dewivewy_system == SYS_DVBT2) {
			wet = cxd2880_check_w1post_pwp(fe);
			if (!wet) {
				wet = cxd2880_set_bew_pew_pewiod_t2(fe);
				pwiv->s = *status;
			}
		} ewse {
			pw_eww("invawid system\n");
			mutex_unwock(pwiv->spi_mutex);
			wetuwn -EINVAW;
		}
		mutex_unwock(pwiv->spi_mutex);
	}

	cxd2880_get_stats(fe, *status);
	wetuwn  0;
}

static int cxd2880_tune(stwuct dvb_fwontend *fe,
			boow wetune,
			unsigned int mode_fwags,
			unsigned int *deway,
			enum fe_status *status)
{
	int wet;

	if (!fe || !deway || !status) {
		pw_eww("invawid awg.");
		wetuwn -EINVAW;
	}

	if (wetune) {
		wet = cxd2880_set_fwontend(fe);
		if (wet) {
			pw_eww("cxd2880_set_fwontend faiwed %d\n", wet);
			wetuwn wet;
		}
	}

	*deway = HZ / 5;

	wetuwn cxd2880_wead_status(fe, status);
}

static int cxd2880_get_fwontend_t(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *c)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	enum cxd2880_dvbt_mode mode = CXD2880_DVBT_MODE_2K;
	enum cxd2880_dvbt_guawd guawd = CXD2880_DVBT_GUAWD_1_32;
	stwuct cxd2880_dvbt_tpsinfo tps;
	enum cxd2880_tnwdmd_spectwum_sense sense;
	u16 snw = 0;
	int stwength = 0;

	if (!fe || !c) {
		pw_eww("invawid awg\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt_mon_mode_guawd(&pwiv->tnwdmd,
						 &mode, &guawd);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (mode) {
		case CXD2880_DVBT_MODE_2K:
			c->twansmission_mode = TWANSMISSION_MODE_2K;
			bweak;
		case CXD2880_DVBT_MODE_8K:
			c->twansmission_mode = TWANSMISSION_MODE_8K;
			bweak;
		defauwt:
			c->twansmission_mode = TWANSMISSION_MODE_2K;
			pw_debug("twansmission mode is invawid %d\n", mode);
			bweak;
		}
		switch (guawd) {
		case CXD2880_DVBT_GUAWD_1_32:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			bweak;
		case CXD2880_DVBT_GUAWD_1_16:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
			bweak;
		case CXD2880_DVBT_GUAWD_1_8:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
			bweak;
		case CXD2880_DVBT_GUAWD_1_4:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
			bweak;
		defauwt:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			pw_debug("guawd intewvaw is invawid %d\n",
				 guawd);
			bweak;
		}
	} ewse {
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		pw_debug("ModeGuawd eww %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt_mon_tps_info(&pwiv->tnwdmd, &tps);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (tps.hiewawchy) {
		case CXD2880_DVBT_HIEWAWCHY_NON:
			c->hiewawchy = HIEWAWCHY_NONE;
			bweak;
		case CXD2880_DVBT_HIEWAWCHY_1:
			c->hiewawchy = HIEWAWCHY_1;
			bweak;
		case CXD2880_DVBT_HIEWAWCHY_2:
			c->hiewawchy = HIEWAWCHY_2;
			bweak;
		case CXD2880_DVBT_HIEWAWCHY_4:
			c->hiewawchy = HIEWAWCHY_4;
			bweak;
		defauwt:
			c->hiewawchy = HIEWAWCHY_NONE;
			pw_debug("TPSInfo hiewawchy is invawid %d\n",
				 tps.hiewawchy);
			bweak;
		}

		switch (tps.wate_hp) {
		case CXD2880_DVBT_CODEWATE_1_2:
			c->code_wate_HP = FEC_1_2;
			bweak;
		case CXD2880_DVBT_CODEWATE_2_3:
			c->code_wate_HP = FEC_2_3;
			bweak;
		case CXD2880_DVBT_CODEWATE_3_4:
			c->code_wate_HP = FEC_3_4;
			bweak;
		case CXD2880_DVBT_CODEWATE_5_6:
			c->code_wate_HP = FEC_5_6;
			bweak;
		case CXD2880_DVBT_CODEWATE_7_8:
			c->code_wate_HP = FEC_7_8;
			bweak;
		defauwt:
			c->code_wate_HP = FEC_NONE;
			pw_debug("TPSInfo wateHP is invawid %d\n",
				 tps.wate_hp);
			bweak;
		}
		switch (tps.wate_wp) {
		case CXD2880_DVBT_CODEWATE_1_2:
			c->code_wate_WP = FEC_1_2;
			bweak;
		case CXD2880_DVBT_CODEWATE_2_3:
			c->code_wate_WP = FEC_2_3;
			bweak;
		case CXD2880_DVBT_CODEWATE_3_4:
			c->code_wate_WP = FEC_3_4;
			bweak;
		case CXD2880_DVBT_CODEWATE_5_6:
			c->code_wate_WP = FEC_5_6;
			bweak;
		case CXD2880_DVBT_CODEWATE_7_8:
			c->code_wate_WP = FEC_7_8;
			bweak;
		defauwt:
			c->code_wate_WP = FEC_NONE;
			pw_debug("TPSInfo wateWP is invawid %d\n",
				 tps.wate_wp);
			bweak;
		}
		switch (tps.constewwation) {
		case CXD2880_DVBT_CONSTEWWATION_QPSK:
			c->moduwation = QPSK;
			bweak;
		case CXD2880_DVBT_CONSTEWWATION_16QAM:
			c->moduwation = QAM_16;
			bweak;
		case CXD2880_DVBT_CONSTEWWATION_64QAM:
			c->moduwation = QAM_64;
			bweak;
		defauwt:
			c->moduwation = QPSK;
			pw_debug("TPSInfo constewwation is invawid %d\n",
				 tps.constewwation);
			bweak;
		}
	} ewse {
		c->hiewawchy = HIEWAWCHY_NONE;
		c->code_wate_HP = FEC_NONE;
		c->code_wate_WP = FEC_NONE;
		c->moduwation = QPSK;
		pw_debug("TPS info eww %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt_mon_spectwum_sense(&pwiv->tnwdmd, &sense);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (sense) {
		case CXD2880_TNWDMD_SPECTWUM_NOWMAW:
			c->invewsion = INVEWSION_OFF;
			bweak;
		case CXD2880_TNWDMD_SPECTWUM_INV:
			c->invewsion = INVEWSION_ON;
			bweak;
		defauwt:
			c->invewsion = INVEWSION_OFF;
			pw_debug("spectwum sense is invawid %d\n", sense);
			bweak;
		}
	} ewse {
		c->invewsion = INVEWSION_OFF;
		pw_debug("spectwum_sense %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_mon_wf_wvw(&pwiv->tnwdmd, &stwength);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->stwength.stat[0].svawue = stwength;
	} ewse {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		pw_debug("mon_wf_wvw %d\n", wet);
	}

	wet = cxd2880_wead_snw(fe, &snw);
	if (!wet) {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = snw;
	} ewse {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		pw_debug("wead_snw %d\n", wet);
	}

	wetuwn 0;
}

static int cxd2880_get_fwontend_t2(stwuct dvb_fwontend *fe,
				   stwuct dtv_fwontend_pwopewties *c)
{
	int wet;
	stwuct cxd2880_pwiv *pwiv = NUWW;
	stwuct cxd2880_dvbt2_w1pwe w1pwe;
	enum cxd2880_dvbt2_pwp_code_wate codewate;
	enum cxd2880_dvbt2_pwp_consteww qam;
	enum cxd2880_tnwdmd_spectwum_sense sense;
	u16 snw = 0;
	int stwength = 0;

	if (!fe || !c) {
		pw_eww("invawid awg.\n");
		wetuwn -EINVAW;
	}

	pwiv = fe->demoduwatow_pwiv;

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt2_mon_w1_pwe(&pwiv->tnwdmd, &w1pwe);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (w1pwe.fft_mode) {
		case CXD2880_DVBT2_M2K:
			c->twansmission_mode = TWANSMISSION_MODE_2K;
			bweak;
		case CXD2880_DVBT2_M8K:
			c->twansmission_mode = TWANSMISSION_MODE_8K;
			bweak;
		case CXD2880_DVBT2_M4K:
			c->twansmission_mode = TWANSMISSION_MODE_4K;
			bweak;
		case CXD2880_DVBT2_M1K:
			c->twansmission_mode = TWANSMISSION_MODE_1K;
			bweak;
		case CXD2880_DVBT2_M16K:
			c->twansmission_mode = TWANSMISSION_MODE_16K;
			bweak;
		case CXD2880_DVBT2_M32K:
			c->twansmission_mode = TWANSMISSION_MODE_32K;
			bweak;
		defauwt:
			c->twansmission_mode = TWANSMISSION_MODE_2K;
			pw_debug("W1Pwe fft_mode is invawid %d\n",
				 w1pwe.fft_mode);
			bweak;
		}
		switch (w1pwe.gi) {
		case CXD2880_DVBT2_G1_32:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			bweak;
		case CXD2880_DVBT2_G1_16:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
			bweak;
		case CXD2880_DVBT2_G1_8:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
			bweak;
		case CXD2880_DVBT2_G1_4:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
			bweak;
		case CXD2880_DVBT2_G1_128:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_128;
			bweak;
		case CXD2880_DVBT2_G19_128:
			c->guawd_intewvaw = GUAWD_INTEWVAW_19_128;
			bweak;
		case CXD2880_DVBT2_G19_256:
			c->guawd_intewvaw = GUAWD_INTEWVAW_19_256;
			bweak;
		defauwt:
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			pw_debug("W1Pwe guawd intewvaw is invawid %d\n",
				 w1pwe.gi);
			bweak;
		}
	} ewse {
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		pw_debug("W1Pwe eww %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt2_mon_code_wate(&pwiv->tnwdmd,
						 CXD2880_DVBT2_PWP_DATA,
						 &codewate);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (codewate) {
		case CXD2880_DVBT2_W1_2:
			c->fec_innew = FEC_1_2;
			bweak;
		case CXD2880_DVBT2_W3_5:
			c->fec_innew = FEC_3_5;
			bweak;
		case CXD2880_DVBT2_W2_3:
			c->fec_innew = FEC_2_3;
			bweak;
		case CXD2880_DVBT2_W3_4:
			c->fec_innew = FEC_3_4;
			bweak;
		case CXD2880_DVBT2_W4_5:
			c->fec_innew = FEC_4_5;
			bweak;
		case CXD2880_DVBT2_W5_6:
			c->fec_innew = FEC_5_6;
			bweak;
		defauwt:
			c->fec_innew = FEC_NONE;
			pw_debug("CodeWate is invawid %d\n", codewate);
			bweak;
		}
	} ewse {
		c->fec_innew = FEC_NONE;
		pw_debug("CodeWate %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt2_mon_qam(&pwiv->tnwdmd,
					   CXD2880_DVBT2_PWP_DATA,
					   &qam);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (qam) {
		case CXD2880_DVBT2_QPSK:
			c->moduwation = QPSK;
			bweak;
		case CXD2880_DVBT2_QAM16:
			c->moduwation = QAM_16;
			bweak;
		case CXD2880_DVBT2_QAM64:
			c->moduwation = QAM_64;
			bweak;
		case CXD2880_DVBT2_QAM256:
			c->moduwation = QAM_256;
			bweak;
		defauwt:
			c->moduwation = QPSK;
			pw_debug("QAM is invawid %d\n", qam);
			bweak;
		}
	} ewse {
		c->moduwation = QPSK;
		pw_debug("QAM %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_dvbt2_mon_spectwum_sense(&pwiv->tnwdmd, &sense);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		switch (sense) {
		case CXD2880_TNWDMD_SPECTWUM_NOWMAW:
			c->invewsion = INVEWSION_OFF;
			bweak;
		case CXD2880_TNWDMD_SPECTWUM_INV:
			c->invewsion = INVEWSION_ON;
			bweak;
		defauwt:
			c->invewsion = INVEWSION_OFF;
			pw_debug("spectwum sense is invawid %d\n", sense);
			bweak;
		}
	} ewse {
		c->invewsion = INVEWSION_OFF;
		pw_debug("SpectwumSense %d\n", wet);
	}

	mutex_wock(pwiv->spi_mutex);
	wet = cxd2880_tnwdmd_mon_wf_wvw(&pwiv->tnwdmd, &stwength);
	mutex_unwock(pwiv->spi_mutex);
	if (!wet) {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->stwength.stat[0].svawue = stwength;
	} ewse {
		c->stwength.wen = 1;
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		pw_debug("mon_wf_wvw %d\n", wet);
	}

	wet = cxd2880_wead_snw(fe, &snw);
	if (!wet) {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = snw;
	} ewse {
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		pw_debug("wead_snw %d\n", wet);
	}

	wetuwn 0;
}

static int cxd2880_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *pwops)
{
	int wet;

	if (!fe || !pwops) {
		pw_eww("invawid awg.");
		wetuwn -EINVAW;
	}

	pw_debug("system=%d\n", fe->dtv_pwopewty_cache.dewivewy_system);
	switch (fe->dtv_pwopewty_cache.dewivewy_system) {
	case SYS_DVBT:
		wet = cxd2880_get_fwontend_t(fe, pwops);
		bweak;
	case SYS_DVBT2:
		wet = cxd2880_get_fwontend_t2(fe, pwops);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static enum dvbfe_awgo cxd2880_get_fwontend_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static stwuct dvb_fwontend_ops cxd2880_dvbt_t2_ops = {
	.info = {
		.name = "Sony CXD2880",
		.fwequency_min_hz = 174 * MHz,
		.fwequency_max_hz = 862 * MHz,
		.fwequency_stepsize_hz = 1 * kHz,
		.caps = FE_CAN_INVEWSION_AUTO |
				FE_CAN_FEC_1_2 |
				FE_CAN_FEC_2_3 |
				FE_CAN_FEC_3_4 |
				FE_CAN_FEC_4_5 |
				FE_CAN_FEC_5_6	|
				FE_CAN_FEC_7_8	|
				FE_CAN_FEC_AUTO |
				FE_CAN_QPSK |
				FE_CAN_QAM_16 |
				FE_CAN_QAM_32 |
				FE_CAN_QAM_64 |
				FE_CAN_QAM_128 |
				FE_CAN_QAM_256 |
				FE_CAN_QAM_AUTO |
				FE_CAN_TWANSMISSION_MODE_AUTO |
				FE_CAN_GUAWD_INTEWVAW_AUTO |
				FE_CAN_2G_MODUWATION |
				FE_CAN_WECOVEW |
				FE_CAN_MUTE_TS,
	},
	.dewsys = { SYS_DVBT, SYS_DVBT2 },

	.wewease = cxd2880_wewease,
	.init = cxd2880_init,
	.sweep = cxd2880_sweep,
	.tune = cxd2880_tune,
	.set_fwontend = cxd2880_set_fwontend,
	.get_fwontend = cxd2880_get_fwontend,
	.wead_status = cxd2880_wead_status,
	.wead_bew = cxd2880_wead_bew,
	.wead_signaw_stwength = cxd2880_wead_signaw_stwength,
	.wead_snw = cxd2880_wead_snw,
	.wead_ucbwocks = cxd2880_wead_ucbwocks,
	.get_fwontend_awgo = cxd2880_get_fwontend_awgo,
};

stwuct dvb_fwontend *cxd2880_attach(stwuct dvb_fwontend *fe,
				    stwuct cxd2880_config *cfg)
{
	int wet;
	enum cxd2880_tnwdmd_chip_id chipid =
					CXD2880_TNWDMD_CHIP_ID_UNKNOWN;
	static stwuct cxd2880_pwiv *pwiv;
	u8 data = 0;

	if (!fe) {
		pw_eww("invawid awg.\n");
		wetuwn NUWW;
	}

	pwiv = kzawwoc(sizeof(stwuct cxd2880_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	pwiv->spi = cfg->spi;
	pwiv->spi_mutex = cfg->spi_mutex;
	pwiv->spi_device.spi = cfg->spi;

	memcpy(&fe->ops, &cxd2880_dvbt_t2_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	wet = cxd2880_spi_device_initiawize(&pwiv->spi_device,
					    CXD2880_SPI_MODE_0,
					    55000000);
	if (wet) {
		pw_eww("spi_device_initiawize faiwed. %d\n", wet);
		kfwee(pwiv);
		wetuwn NUWW;
	}

	wet = cxd2880_spi_device_cweate_spi(&pwiv->cxd2880_spi,
					    &pwiv->spi_device);
	if (wet) {
		pw_eww("spi_device_cweate_spi faiwed. %d\n", wet);
		kfwee(pwiv);
		wetuwn NUWW;
	}

	wet = cxd2880_io_spi_cweate(&pwiv->wegio, &pwiv->cxd2880_spi, 0);
	if (wet) {
		pw_eww("io_spi_cweate faiwed. %d\n", wet);
		kfwee(pwiv);
		wetuwn NUWW;
	}
	wet = pwiv->wegio.wwite_weg(&pwiv->wegio,
				    CXD2880_IO_TGT_SYS, 0x00, 0x00);
	if (wet) {
		pw_eww("set bank to 0x00 faiwed.\n");
		kfwee(pwiv);
		wetuwn NUWW;
	}
	wet = pwiv->wegio.wead_wegs(&pwiv->wegio,
				    CXD2880_IO_TGT_SYS, 0xfd, &data, 1);
	if (wet) {
		pw_eww("wead chip id faiwed.\n");
		kfwee(pwiv);
		wetuwn NUWW;
	}

	chipid = (enum cxd2880_tnwdmd_chip_id)data;
	if (chipid != CXD2880_TNWDMD_CHIP_ID_CXD2880_ES1_0X &&
	    chipid != CXD2880_TNWDMD_CHIP_ID_CXD2880_ES1_11) {
		pw_eww("chip id invawid.\n");
		kfwee(pwiv);
		wetuwn NUWW;
	}

	fe->demoduwatow_pwiv = pwiv;
	pw_info("CXD2880 dwivew vewsion: Vew %s\n",
		CXD2880_TNWDMD_DWIVEW_VEWSION);

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(cxd2880_attach);

MODUWE_DESCWIPTION("Sony CXD2880 DVB-T2/T tunew + demod dwivew");
MODUWE_AUTHOW("Sony Semiconductow Sowutions Cowpowation");
MODUWE_WICENSE("GPW v2");
