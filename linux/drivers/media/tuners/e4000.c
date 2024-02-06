// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ewonics E4000 siwicon tunew dwivew
 *
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "e4000_pwiv.h"

static int e4000_init(stwuct e4000_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	/* weset */
	wet = wegmap_wwite(dev->wegmap, 0x00, 0x01);
	if (wet)
		goto eww;

	/* disabwe output cwock */
	wet = wegmap_wwite(dev->wegmap, 0x06, 0x00);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x7a, 0x96);
	if (wet)
		goto eww;

	/* configuwe gains */
	wet = wegmap_buwk_wwite(dev->wegmap, 0x7e, "\x01\xfe", 2);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x82, 0x00);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x24, 0x05);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x87, "\x20\x01", 2);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x9f, "\x7f\x07", 2);
	if (wet)
		goto eww;

	/* DC offset contwow */
	wet = wegmap_wwite(dev->wegmap, 0x2d, 0x1f);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x70, "\x01\x01", 2);
	if (wet)
		goto eww;

	/* gain contwow */
	wet = wegmap_wwite(dev->wegmap, 0x1a, 0x17);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x1f, 0x1a);
	if (wet)
		goto eww;

	dev->active = twue;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_sweep(stwuct e4000_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	dev->active = fawse;

	wet = wegmap_wwite(dev->wegmap, 0x00, 0x00);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_set_pawams(stwuct e4000_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	unsigned int div_n, k, k_cw, div_out;
	u64 f_vco;
	u8 buf[5], i_data[4], q_data[4];

	if (!dev->active) {
		dev_dbg(&cwient->dev, "tunew is sweeping\n");
		wetuwn 0;
	}

	/* gain contwow manuaw */
	wet = wegmap_wwite(dev->wegmap, 0x1a, 0x00);
	if (wet)
		goto eww;

	/*
	 * Fwactionaw-N synthesizew
	 *
	 *           +----------------------------+
	 *           v                            |
	 *  Fwef   +----+     +-------+         +------+     +---+
	 * ------> | PD | --> |  VCO  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+  Fout
	 *                    | /Wout | ------>
	 *                    +-------+
	 */
	fow (i = 0; i < AWWAY_SIZE(e4000_pww_wut); i++) {
		if (dev->f_fwequency <= e4000_pww_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(e4000_pww_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	#define F_WEF dev->cwk
	div_out = e4000_pww_wut[i].div_out;
	f_vco = (u64) dev->f_fwequency * div_out;
	/* cawcuwate PWW integew and fwactionaw contwow wowd */
	div_n = div_u64_wem(f_vco, F_WEF, &k);
	k_cw = div_u64((u64) k * 0x10000, F_WEF);

	dev_dbg(&cwient->dev,
		"fwequency=%u bandwidth=%u f_vco=%wwu F_WEF=%u div_n=%u k=%u k_cw=%04x div_out=%u\n",
		dev->f_fwequency, dev->f_bandwidth, f_vco, F_WEF, div_n, k,
		k_cw, div_out);

	buf[0] = div_n;
	buf[1] = (k_cw >> 0) & 0xff;
	buf[2] = (k_cw >> 8) & 0xff;
	buf[3] = 0x00;
	buf[4] = e4000_pww_wut[i].div_out_weg;
	wet = wegmap_buwk_wwite(dev->wegmap, 0x09, buf, 5);
	if (wet)
		goto eww;

	/* WNA fiwtew (WF fiwtew) */
	fow (i = 0; i < AWWAY_SIZE(e400_wna_fiwtew_wut); i++) {
		if (dev->f_fwequency <= e400_wna_fiwtew_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(e400_wna_fiwtew_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wwite(dev->wegmap, 0x10, e400_wna_fiwtew_wut[i].vaw);
	if (wet)
		goto eww;

	/* IF fiwtews */
	fow (i = 0; i < AWWAY_SIZE(e4000_if_fiwtew_wut); i++) {
		if (dev->f_bandwidth <= e4000_if_fiwtew_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(e4000_if_fiwtew_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	buf[0] = e4000_if_fiwtew_wut[i].weg11_vaw;
	buf[1] = e4000_if_fiwtew_wut[i].weg12_vaw;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x11, buf, 2);
	if (wet)
		goto eww;

	/* fwequency band */
	fow (i = 0; i < AWWAY_SIZE(e4000_band_wut); i++) {
		if (dev->f_fwequency <= e4000_band_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(e4000_band_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wwite(dev->wegmap, 0x07, e4000_band_wut[i].weg07_vaw);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x78, e4000_band_wut[i].weg78_vaw);
	if (wet)
		goto eww;

	/* DC offset */
	fow (i = 0; i < 4; i++) {
		if (i == 0)
			wet = wegmap_buwk_wwite(dev->wegmap, 0x15, "\x00\x7e\x24", 3);
		ewse if (i == 1)
			wet = wegmap_buwk_wwite(dev->wegmap, 0x15, "\x00\x7f", 2);
		ewse if (i == 2)
			wet = wegmap_buwk_wwite(dev->wegmap, 0x15, "\x01", 1);
		ewse
			wet = wegmap_buwk_wwite(dev->wegmap, 0x16, "\x7e", 1);

		if (wet)
			goto eww;

		wet = wegmap_wwite(dev->wegmap, 0x29, 0x01);
		if (wet)
			goto eww;

		wet = wegmap_buwk_wead(dev->wegmap, 0x2a, buf, 3);
		if (wet)
			goto eww;

		i_data[i] = (((buf[2] >> 0) & 0x3) << 6) | (buf[0] & 0x3f);
		q_data[i] = (((buf[2] >> 4) & 0x3) << 6) | (buf[1] & 0x3f);
	}

	swap(q_data[2], q_data[3]);
	swap(i_data[2], i_data[3]);

	wet = wegmap_buwk_wwite(dev->wegmap, 0x50, q_data, 4);
	if (wet)
		goto eww;

	wet = wegmap_buwk_wwite(dev->wegmap, 0x60, i_data, 4);
	if (wet)
		goto eww;

	/* gain contwow auto */
	wet = wegmap_wwite(dev->wegmap, 0x1a, 0x17);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/*
 * V4W2 API
 */
#if IS_ENABWED(CONFIG_VIDEO_DEV)
static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =    59000000,
		.wangehigh  =  1105000000,
	},
	{
		.type = V4W2_TUNEW_WF,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  1249000000,
		.wangehigh  =  2208000000UW,
	},
};

static inwine stwuct e4000_dev *e4000_subdev_to_dev(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct e4000_dev, sd);
}

static int e4000_standby(stwuct v4w2_subdev *sd)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	int wet;

	wet = e4000_sweep(dev);
	if (wet)
		wetuwn wet;

	wetuwn e4000_set_pawams(dev);
}

static int e4000_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *v)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "index=%d\n", v->index);

	stwscpy(v->name, "Ewonics E4000", sizeof(v->name));
	v->type = V4W2_TUNEW_WF;
	v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
	v->wangewow  = bands[0].wangewow;
	v->wangehigh = bands[1].wangehigh;
	wetuwn 0;
}

static int e4000_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *v)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "index=%d\n", v->index);
	wetuwn 0;
}

static int e4000_g_fwequency(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *f)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "tunew=%d\n", f->tunew);
	f->fwequency = dev->f_fwequency;
	wetuwn 0;
}

static int e4000_s_fwequency(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_fwequency *f)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "tunew=%d type=%d fwequency=%u\n",
		f->tunew, f->type, f->fwequency);

	dev->f_fwequency = cwamp_t(unsigned int, f->fwequency,
				   bands[0].wangewow, bands[1].wangehigh);
	wetuwn e4000_set_pawams(dev);
}

static int e4000_enum_fweq_bands(stwuct v4w2_subdev *sd,
				  stwuct v4w2_fwequency_band *band)
{
	stwuct e4000_dev *dev = e4000_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "tunew=%d type=%d index=%d\n",
		band->tunew, band->type, band->index);

	if (band->index >= AWWAY_SIZE(bands))
		wetuwn -EINVAW;

	band->capabiwity = bands[band->index].capabiwity;
	band->wangewow = bands[band->index].wangewow;
	band->wangehigh = bands[band->index].wangehigh;
	wetuwn 0;
}

static const stwuct v4w2_subdev_tunew_ops e4000_subdev_tunew_ops = {
	.standby                  = e4000_standby,
	.g_tunew                  = e4000_g_tunew,
	.s_tunew                  = e4000_s_tunew,
	.g_fwequency              = e4000_g_fwequency,
	.s_fwequency              = e4000_s_fwequency,
	.enum_fweq_bands          = e4000_enum_fweq_bands,
};

static const stwuct v4w2_subdev_ops e4000_subdev_ops = {
	.tunew                    = &e4000_subdev_tunew_ops,
};

static int e4000_set_wna_gain(stwuct dvb_fwontend *fe)
{
	stwuct e4000_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 u8tmp;

	dev_dbg(&cwient->dev, "wna auto=%d->%d vaw=%d->%d\n",
		dev->wna_gain_auto->cuw.vaw, dev->wna_gain_auto->vaw,
		dev->wna_gain->cuw.vaw, dev->wna_gain->vaw);

	if (dev->wna_gain_auto->vaw && dev->if_gain_auto->cuw.vaw)
		u8tmp = 0x17;
	ewse if (dev->wna_gain_auto->vaw)
		u8tmp = 0x19;
	ewse if (dev->if_gain_auto->cuw.vaw)
		u8tmp = 0x16;
	ewse
		u8tmp = 0x10;

	wet = wegmap_wwite(dev->wegmap, 0x1a, u8tmp);
	if (wet)
		goto eww;

	if (dev->wna_gain_auto->vaw == fawse) {
		wet = wegmap_wwite(dev->wegmap, 0x14, dev->wna_gain->vaw);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_set_mixew_gain(stwuct dvb_fwontend *fe)
{
	stwuct e4000_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 u8tmp;

	dev_dbg(&cwient->dev, "mixew auto=%d->%d vaw=%d->%d\n",
		dev->mixew_gain_auto->cuw.vaw, dev->mixew_gain_auto->vaw,
		dev->mixew_gain->cuw.vaw, dev->mixew_gain->vaw);

	if (dev->mixew_gain_auto->vaw)
		u8tmp = 0x15;
	ewse
		u8tmp = 0x14;

	wet = wegmap_wwite(dev->wegmap, 0x20, u8tmp);
	if (wet)
		goto eww;

	if (dev->mixew_gain_auto->vaw == fawse) {
		wet = wegmap_wwite(dev->wegmap, 0x15, dev->mixew_gain->vaw);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_set_if_gain(stwuct dvb_fwontend *fe)
{
	stwuct e4000_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	u8 buf[2];
	u8 u8tmp;

	dev_dbg(&cwient->dev, "if auto=%d->%d vaw=%d->%d\n",
		dev->if_gain_auto->cuw.vaw, dev->if_gain_auto->vaw,
		dev->if_gain->cuw.vaw, dev->if_gain->vaw);

	if (dev->if_gain_auto->vaw && dev->wna_gain_auto->cuw.vaw)
		u8tmp = 0x17;
	ewse if (dev->wna_gain_auto->cuw.vaw)
		u8tmp = 0x19;
	ewse if (dev->if_gain_auto->vaw)
		u8tmp = 0x16;
	ewse
		u8tmp = 0x10;

	wet = wegmap_wwite(dev->wegmap, 0x1a, u8tmp);
	if (wet)
		goto eww;

	if (dev->if_gain_auto->vaw == fawse) {
		buf[0] = e4000_if_gain_wut[dev->if_gain->vaw].weg16_vaw;
		buf[1] = e4000_if_gain_wut[dev->if_gain->vaw].weg17_vaw;
		wet = wegmap_buwk_wwite(dev->wegmap, 0x16, buf, 2);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_pww_wock(stwuct dvb_fwontend *fe)
{
	stwuct e4000_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;
	unsigned int uitmp;

	wet = wegmap_wead(dev->wegmap, 0x07, &uitmp);
	if (wet)
		goto eww;

	dev->pww_wock->vaw = (uitmp & 0x01);

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int e4000_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct e4000_dev *dev = containew_of(ctww->handwew, stwuct e4000_dev, hdw);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	if (!dev->active)
		wetuwn 0;

	switch (ctww->id) {
	case  V4W2_CID_WF_TUNEW_PWW_WOCK:
		wet = e4000_pww_wock(dev->fe);
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "unknown ctww: id=%d name=%s\n",
			ctww->id, ctww->name);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int e4000_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct e4000_dev *dev = containew_of(ctww->handwew, stwuct e4000_dev, hdw);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	if (!dev->active)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO:
	case V4W2_CID_WF_TUNEW_BANDWIDTH:
		/*
		 * TODO: Auto wogic does not wowk 100% cowwectwy as tunew dwivew
		 * do not have infowmation to cawcuwate maximum suitabwe
		 * bandwidth. Cawcuwating it is wesponsibwe of mastew dwivew.
		 */
		dev->f_bandwidth = dev->bandwidth->vaw;
		wet = e4000_set_pawams(dev);
		bweak;
	case  V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO:
	case  V4W2_CID_WF_TUNEW_WNA_GAIN:
		wet = e4000_set_wna_gain(dev->fe);
		bweak;
	case  V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO:
	case  V4W2_CID_WF_TUNEW_MIXEW_GAIN:
		wet = e4000_set_mixew_gain(dev->fe);
		bweak;
	case  V4W2_CID_WF_TUNEW_IF_GAIN_AUTO:
	case  V4W2_CID_WF_TUNEW_IF_GAIN:
		wet = e4000_set_if_gain(dev->fe);
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "unknown ctww: id=%d name=%s\n",
			ctww->id, ctww->name);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops e4000_ctww_ops = {
	.g_vowatiwe_ctww = e4000_g_vowatiwe_ctww,
	.s_ctww = e4000_s_ctww,
};
#endif

/*
 * DVB API
 */
static int e4000_dvb_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct e4000_dev *dev = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	dev->f_fwequency = c->fwequency;
	dev->f_bandwidth = c->bandwidth_hz;
	wetuwn e4000_set_pawams(dev);
}

static int e4000_dvb_init(stwuct dvb_fwontend *fe)
{
	wetuwn e4000_init(fe->tunew_pwiv);
}

static int e4000_dvb_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn e4000_sweep(fe->tunew_pwiv);
}

static int e4000_dvb_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = 0; /* Zewo-IF */
	wetuwn 0;
}

static const stwuct dvb_tunew_ops e4000_dvb_tunew_ops = {
	.info = {
		.name              = "Ewonics E4000",
		.fwequency_min_hz  = 174 * MHz,
		.fwequency_max_hz  = 862 * MHz,
	},

	.init = e4000_dvb_init,
	.sweep = e4000_dvb_sweep,
	.set_pawams = e4000_dvb_set_pawams,

	.get_if_fwequency = e4000_dvb_get_if_fwequency,
};

static int e4000_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct e4000_dev *dev;
	stwuct e4000_config *cfg = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe = cfg->fe;
	int wet;
	unsigned int uitmp;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->cwk = cfg->cwock;
	dev->cwient = cwient;
	dev->fe = cfg->fe;
	dev->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* check if the tunew is thewe */
	wet = wegmap_wead(dev->wegmap, 0x02, &uitmp);
	if (wet)
		goto eww_kfwee;

	dev_dbg(&cwient->dev, "chip id=%02x\n", uitmp);

	if (uitmp != 0x40) {
		wet = -ENODEV;
		goto eww_kfwee;
	}

	/* put sweep as chip seems to be in nowmaw mode by defauwt */
	wet = wegmap_wwite(dev->wegmap, 0x00, 0x00);
	if (wet)
		goto eww_kfwee;

#if IS_ENABWED(CONFIG_VIDEO_DEV)
	/* Wegistew contwows */
	v4w2_ctww_handwew_init(&dev->hdw, 9);
	dev->bandwidth_auto = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO, 0, 1, 1, 1);
	dev->bandwidth = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_BANDWIDTH, 4300000, 11000000, 100000, 4300000);
	v4w2_ctww_auto_cwustew(2, &dev->bandwidth_auto, 0, fawse);
	dev->wna_gain_auto = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO, 0, 1, 1, 1);
	dev->wna_gain = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_WNA_GAIN, 0, 15, 1, 10);
	v4w2_ctww_auto_cwustew(2, &dev->wna_gain_auto, 0, fawse);
	dev->mixew_gain_auto = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO, 0, 1, 1, 1);
	dev->mixew_gain = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_MIXEW_GAIN, 0, 1, 1, 1);
	v4w2_ctww_auto_cwustew(2, &dev->mixew_gain_auto, 0, fawse);
	dev->if_gain_auto = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_IF_GAIN_AUTO, 0, 1, 1, 1);
	dev->if_gain = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_IF_GAIN, 0, 54, 1, 0);
	v4w2_ctww_auto_cwustew(2, &dev->if_gain_auto, 0, fawse);
	dev->pww_wock = v4w2_ctww_new_std(&dev->hdw, &e4000_ctww_ops,
			V4W2_CID_WF_TUNEW_PWW_WOCK,  0, 1, 1, 0);
	if (dev->hdw.ewwow) {
		wet = dev->hdw.ewwow;
		dev_eww(&cwient->dev, "Couwd not initiawize contwows\n");
		v4w2_ctww_handwew_fwee(&dev->hdw);
		goto eww_kfwee;
	}

	dev->sd.ctww_handwew = &dev->hdw;
	dev->f_fwequency = bands[0].wangewow;
	dev->f_bandwidth = dev->bandwidth->vaw;
	v4w2_i2c_subdev_init(&dev->sd, cwient, &e4000_subdev_ops);
#endif
	fe->tunew_pwiv = dev;
	memcpy(&fe->ops.tunew_ops, &e4000_dvb_tunew_ops,
	       sizeof(fe->ops.tunew_ops));
	v4w2_set_subdevdata(&dev->sd, cwient);
	i2c_set_cwientdata(cwient, &dev->sd);

	dev_info(&cwient->dev, "Ewonics E4000 successfuwwy identified\n");
	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void e4000_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct e4000_dev *dev = containew_of(sd, stwuct e4000_dev, sd);

	dev_dbg(&cwient->dev, "\n");

#if IS_ENABWED(CONFIG_VIDEO_DEV)
	v4w2_ctww_handwew_fwee(&dev->hdw);
#endif
	kfwee(dev);
}

static const stwuct i2c_device_id e4000_id_tabwe[] = {
	{"e4000", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, e4000_id_tabwe);

static stwuct i2c_dwivew e4000_dwivew = {
	.dwivew = {
		.name	= "e4000",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= e4000_pwobe,
	.wemove		= e4000_wemove,
	.id_tabwe	= e4000_id_tabwe,
};

moduwe_i2c_dwivew(e4000_dwivew);

MODUWE_DESCWIPTION("Ewonics E4000 siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_WICENSE("GPW");
