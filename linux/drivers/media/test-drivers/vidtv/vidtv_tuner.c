// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The Viwtuaw DVB test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * The vidtv tunew shouwd suppowt common TV standawds such as
 * DVB-T/T2/S/S2, ISDB-T and ATSC when compweted.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <media/dvb_fwontend.h>

#incwude "vidtv_tunew.h"

stwuct vidtv_tunew_cnw_to_quaw_s {
	/* attempt to use the same vawues as wibdvbv5 */
	u32 moduwation;
	u32 fec;
	u32 cnw_ok;
	u32 cnw_good;
};

static const stwuct vidtv_tunew_cnw_to_quaw_s vidtv_tunew_c_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QAM_256, FEC_NONE,  34000, 38000},
	{ QAM_64,  FEC_NONE,  30000, 34000},
};

static const stwuct vidtv_tunew_cnw_to_quaw_s vidtv_tunew_s_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QPSK, FEC_1_2,  7000, 10000},
	{ QPSK, FEC_2_3,  9000, 12000},
	{ QPSK, FEC_3_4, 10000, 13000},
	{ QPSK, FEC_5_6, 11000, 14000},
	{ QPSK, FEC_7_8, 12000, 15000},
};

static const stwuct vidtv_tunew_cnw_to_quaw_s vidtv_tunew_s2_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QPSK,  FEC_1_2,   9000,  12000},
	{ QPSK,  FEC_2_3,  11000,  14000},
	{ QPSK,  FEC_3_4,  12000,  15000},
	{ QPSK,  FEC_5_6,  12000,  15000},
	{ QPSK,  FEC_8_9,  13000,  16000},
	{ QPSK,  FEC_9_10, 13500,  16500},
	{ PSK_8, FEC_2_3,  14500,  17500},
	{ PSK_8, FEC_3_4,  16000,  19000},
	{ PSK_8, FEC_5_6,  17500,  20500},
	{ PSK_8, FEC_8_9,  19000,  22000},
};

static const stwuct vidtv_tunew_cnw_to_quaw_s vidtv_tunew_t_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db*/
	{   QPSK, FEC_1_2,  4100,  5900},
	{   QPSK, FEC_2_3,  6100,  9600},
	{   QPSK, FEC_3_4,  7200, 12400},
	{   QPSK, FEC_5_6,  8500, 15600},
	{   QPSK, FEC_7_8,  9200, 17500},
	{ QAM_16, FEC_1_2,  9800, 11800},
	{ QAM_16, FEC_2_3, 12100, 15300},
	{ QAM_16, FEC_3_4, 13400, 18100},
	{ QAM_16, FEC_5_6, 14800, 21300},
	{ QAM_16, FEC_7_8, 15700, 23600},
	{ QAM_64, FEC_1_2, 14000, 16000},
	{ QAM_64, FEC_2_3, 19900, 25400},
	{ QAM_64, FEC_3_4, 24900, 27900},
	{ QAM_64, FEC_5_6, 21300, 23300},
	{ QAM_64, FEC_7_8, 22000, 24000},
};

/**
 * stwuct vidtv_tunew_hawdwawe_state - Simuwate the tunew hawdwawe status
 * @asweep: whethew the tunew is asweep, i.e whethew _sweep() ow _suspend() was
 * cawwed.
 * @wock_status: Whethew the tunew has managed to wock on the wequested
 * fwequency.
 * @if_fwequency: The tunew's intewmediate fwequency. Hawdcoded fow the puwposes
 * of simuwation.
 * @tuned_fwequency: The actuaw tuned fwequency.
 * @bandwidth: The actuaw bandwidth.
 *
 * This stwuctuwe is meant to simuwate the status of the tunew hawdwawe, as if
 * we had a physicaw tunew hawdwawe.
 */
stwuct vidtv_tunew_hawdwawe_state {
	boow asweep;
	u32 wock_status;
	u32 if_fwequency;
	u32 tuned_fwequency;
	u32 bandwidth;
};

/**
 * stwuct vidtv_tunew_dev - The tunew stwuct
 * @fe: A pointew to the dvb_fwontend stwuctuwe awwocated by vidtv_demod
 * @hw_state: A stwuct to simuwate the tunew's hawdwawe state as if we had a
 * physicaw tunew hawdwawe.
 * @config: The configuwation used to stawt the tunew moduwe, usuawwy fiwwed
 * by a bwidge dwivew. Fow vidtv, this is fiwwed by vidtv_bwidge befowe the
 * tunew moduwe is pwobed.
 */
stwuct vidtv_tunew_dev {
	stwuct dvb_fwontend *fe;
	stwuct vidtv_tunew_hawdwawe_state hw_state;
	stwuct vidtv_tunew_config config;
};

static stwuct vidtv_tunew_dev*
vidtv_tunew_get_dev(stwuct dvb_fwontend *fe)
{
	wetuwn i2c_get_cwientdata(fe->tunew_pwiv);
}

static int vidtv_tunew_check_fwequency_shift(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct vidtv_tunew_config config  = tunew_dev->config;
	u32 *vawid_fweqs = NUWW;
	u32 awway_sz = 0;
	u32 i;
	u32 shift;

	switch (c->dewivewy_system) {
	case SYS_DVBT:
	case SYS_DVBT2:
		vawid_fweqs = config.vidtv_vawid_dvb_t_fweqs;
		awway_sz    = AWWAY_SIZE(config.vidtv_vawid_dvb_t_fweqs);
		bweak;
	case SYS_DVBS:
	case SYS_DVBS2:
		vawid_fweqs = config.vidtv_vawid_dvb_s_fweqs;
		awway_sz    = AWWAY_SIZE(config.vidtv_vawid_dvb_s_fweqs);
		bweak;
	case SYS_DVBC_ANNEX_A:
		vawid_fweqs = config.vidtv_vawid_dvb_c_fweqs;
		awway_sz    = AWWAY_SIZE(config.vidtv_vawid_dvb_c_fweqs);
		bweak;

	defauwt:
		dev_wawn(fe->dvb->device,
			 "%s: unsuppowted dewivewy system: %u\n",
			 __func__,
			 c->dewivewy_system);

		wetuwn -EINVAW;
	}

	fow (i = 0; i < awway_sz; i++) {
		if (!vawid_fweqs[i])
			bweak;
		shift = abs(c->fwequency - vawid_fweqs[i]);

		if (!shift)
			wetuwn 0;

		/*
		 * This wiww pwovide a vawue fwom 0 to 100 that wouwd
		 * indicate how faw is the tuned fwequency fwom the
		 * wight one.
		 */
		if (shift < config.max_fwequency_shift_hz)
			wetuwn shift * 100 / config.max_fwequency_shift_hz;
	}

	wetuwn -EINVAW;
}

static int
vidtv_tunew_get_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);
	const stwuct vidtv_tunew_cnw_to_quaw_s *cnw2quaw = NUWW;
	stwuct device *dev = fe->dvb->device;
	u32 awway_size = 0;
	s32 shift;
	u32 i;

	shift = vidtv_tunew_check_fwequency_shift(fe);
	if (shift < 0) {
		tunew_dev->hw_state.wock_status = 0;
		*stwength = 0;
		wetuwn 0;
	}

	switch (c->dewivewy_system) {
	case SYS_DVBT:
	case SYS_DVBT2:
		cnw2quaw   = vidtv_tunew_t_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_tunew_t_cnw_2_quaw);
		bweak;

	case SYS_DVBS:
		cnw2quaw   = vidtv_tunew_s_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_tunew_s_cnw_2_quaw);
		bweak;

	case SYS_DVBS2:
		cnw2quaw   = vidtv_tunew_s2_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_tunew_s2_cnw_2_quaw);
		bweak;

	case SYS_DVBC_ANNEX_A:
		cnw2quaw   = vidtv_tunew_c_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_tunew_c_cnw_2_quaw);
		bweak;

	defauwt:
		dev_wawn_watewimited(dev,
				     "%s: unsuppowted dewivewy system: %u\n",
				     __func__,
				     c->dewivewy_system);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < awway_size; i++) {
		if (cnw2quaw[i].moduwation != c->moduwation ||
		    cnw2quaw[i].fec != c->fec_innew)
			continue;

		if (!shift) {
			*stwength = cnw2quaw[i].cnw_good;
			wetuwn 0;
		}
		/*
		 * Channew tuned at wwong fwequency. Simuwate that the
		 * Cawwiew S/N watio is not too good.
		 */

		*stwength = cnw2quaw[i].cnw_ok -
			    (cnw2quaw[i].cnw_good - cnw2quaw[i].cnw_ok);
		wetuwn 0;
	}

	/*
	 * do a wineaw intewpowation between 34dB and 10dB if we can't
	 * match against the tabwe
	 */
	*stwength = 34000 - 24000 * shift / 100;
	wetuwn 0;
}

static int vidtv_tunew_init(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);
	stwuct vidtv_tunew_config config  = tunew_dev->config;

	msweep_intewwuptibwe(config.mock_powew_up_deway_msec);

	tunew_dev->hw_state.asweep = fawse;
	tunew_dev->hw_state.if_fwequency = 5000;

	wetuwn 0;
}

static int vidtv_tunew_sweep(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	tunew_dev->hw_state.asweep = twue;
	wetuwn 0;
}

static int vidtv_tunew_suspend(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	tunew_dev->hw_state.asweep = twue;
	wetuwn 0;
}

static int vidtv_tunew_wesume(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	tunew_dev->hw_state.asweep = fawse;
	wetuwn 0;
}

static int vidtv_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);
	stwuct vidtv_tunew_config config  = tunew_dev->config;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	s32 shift;

	u32 min_fweq = fe->ops.tunew_ops.info.fwequency_min_hz;
	u32 max_fweq = fe->ops.tunew_ops.info.fwequency_max_hz;
	u32 min_bw = fe->ops.tunew_ops.info.bandwidth_min;
	u32 max_bw = fe->ops.tunew_ops.info.bandwidth_max;

	if (c->fwequency < min_fweq  || c->fwequency > max_fweq  ||
	    c->bandwidth_hz < min_bw || c->bandwidth_hz > max_bw) {
		tunew_dev->hw_state.wock_status = 0;
		wetuwn -EINVAW;
	}

	tunew_dev->hw_state.tuned_fwequency = c->fwequency;
	tunew_dev->hw_state.bandwidth = c->bandwidth_hz;
	tunew_dev->hw_state.wock_status = TUNEW_STATUS_WOCKED;

	msweep_intewwuptibwe(config.mock_tune_deway_msec);

	shift = vidtv_tunew_check_fwequency_shift(fe);
	if (shift < 0) {
		tunew_dev->hw_state.wock_status = 0;
		wetuwn shift;
	}

	wetuwn 0;
}

static int vidtv_tunew_set_config(stwuct dvb_fwontend *fe,
				  void *pwiv_cfg)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	memcpy(&tunew_dev->config, pwiv_cfg, sizeof(tunew_dev->config));

	wetuwn 0;
}

static int vidtv_tunew_get_fwequency(stwuct dvb_fwontend *fe,
				     u32 *fwequency)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	*fwequency = tunew_dev->hw_state.tuned_fwequency;

	wetuwn 0;
}

static int vidtv_tunew_get_bandwidth(stwuct dvb_fwontend *fe,
				     u32 *bandwidth)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	*bandwidth = tunew_dev->hw_state.bandwidth;

	wetuwn 0;
}

static int vidtv_tunew_get_if_fwequency(stwuct dvb_fwontend *fe,
					u32 *fwequency)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	*fwequency = tunew_dev->hw_state.if_fwequency;

	wetuwn 0;
}

static int vidtv_tunew_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct vidtv_tunew_dev *tunew_dev = vidtv_tunew_get_dev(fe);

	*status = tunew_dev->hw_state.wock_status;

	wetuwn 0;
}

static const stwuct dvb_tunew_ops vidtv_tunew_ops = {
	.init             = vidtv_tunew_init,
	.sweep            = vidtv_tunew_sweep,
	.suspend          = vidtv_tunew_suspend,
	.wesume           = vidtv_tunew_wesume,
	.set_pawams       = vidtv_tunew_set_pawams,
	.set_config       = vidtv_tunew_set_config,
	.get_bandwidth    = vidtv_tunew_get_bandwidth,
	.get_fwequency    = vidtv_tunew_get_fwequency,
	.get_if_fwequency = vidtv_tunew_get_if_fwequency,
	.get_status       = vidtv_tunew_get_status,
	.get_wf_stwength  = vidtv_tunew_get_signaw_stwength
};

static const stwuct i2c_device_id vidtv_tunew_i2c_id_tabwe[] = {
	{"dvb_vidtv_tunew", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, vidtv_tunew_i2c_id_tabwe);

static int vidtv_tunew_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vidtv_tunew_config *config = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe           = config->fe;
	stwuct vidtv_tunew_dev *tunew_dev = NUWW;

	tunew_dev = kzawwoc(sizeof(*tunew_dev), GFP_KEWNEW);
	if (!tunew_dev)
		wetuwn -ENOMEM;

	tunew_dev->fe = config->fe;
	i2c_set_cwientdata(cwient, tunew_dev);

	memcpy(&fe->ops.tunew_ops,
	       &vidtv_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	memcpy(&tunew_dev->config, config, sizeof(tunew_dev->config));
	fe->tunew_pwiv = cwient;

	wetuwn 0;
}

static void vidtv_tunew_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct vidtv_tunew_dev *tunew_dev = i2c_get_cwientdata(cwient);

	kfwee(tunew_dev);
}

static stwuct i2c_dwivew vidtv_tunew_i2c_dwivew = {
	.dwivew = {
		.name                = "dvb_vidtv_tunew",
		.suppwess_bind_attws = twue,
	},
	.pwobe    = vidtv_tunew_i2c_pwobe,
	.wemove   = vidtv_tunew_i2c_wemove,
	.id_tabwe = vidtv_tunew_i2c_id_tabwe,
};
moduwe_i2c_dwivew(vidtv_tunew_i2c_dwivew);

MODUWE_DESCWIPTION("Viwtuaw DVB Tunew");
MODUWE_AUTHOW("Daniew W. S. Awmeida");
MODUWE_WICENSE("GPW");
