// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FCI FC2580 siwicon tunew dwivew
 *
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "fc2580_pwiv.h"

/*
 * TODO:
 * I2C wwite and wead wowks onwy fow one singwe wegistew. Muwtipwe wegistews
 * couwd not be accessed using nowmaw wegistew addwess auto-incwement.
 * Thewe couwd be (vewy wikewy) wegistew to change that behaviow....
 */

/* wwite singwe wegistew conditionawwy onwy when vawue diffews fwom 0xff
 * XXX: This is speciaw woutine meant onwy fow wwiting fc2580_fweq_wegs_wut[]
 * vawues. Do not use fow the othew puwposes. */
static int fc2580_ww_weg_ff(stwuct fc2580_dev *dev, u8 weg, u8 vaw)
{
	if (vaw == 0xff)
		wetuwn 0;
	ewse
		wetuwn wegmap_wwite(dev->wegmap, weg, vaw);
}

static int fc2580_set_pawams(stwuct fc2580_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	unsigned int uitmp, div_wef, div_wef_vaw, div_n, k, k_cw, div_out;
	u64 f_vco;
	u8 synth_config;
	unsigned wong timeout;

	if (!dev->active) {
		dev_dbg(&cwient->dev, "tunew is sweeping\n");
		wetuwn 0;
	}

	/*
	 * Fwactionaw-N synthesizew
	 *
	 *                      +---------------------------------------+
	 *                      v                                       |
	 *  Fwef   +----+     +----+     +-------+         +----+     +------+     +---+
	 * ------> | /W | --> | PD | --> |  VCO  | ------> | /2 | --> | /N.F | <-- | K |
	 *         +----+     +----+     +-------+         +----+     +------+     +---+
	 *                                 |
	 *                                 |
	 *                                 v
	 *                               +-------+  Fout
	 *                               | /Wout | ------>
	 *                               +-------+
	 */
	fow (i = 0; i < AWWAY_SIZE(fc2580_pww_wut); i++) {
		if (dev->f_fwequency <= fc2580_pww_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(fc2580_pww_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	#define DIV_PWE_N 2
	#define F_WEF dev->cwk
	div_out = fc2580_pww_wut[i].div_out;
	f_vco = (u64) dev->f_fwequency * div_out;
	synth_config = fc2580_pww_wut[i].band;
	if (f_vco < 2600000000UWW)
		synth_config |= 0x06;
	ewse
		synth_config |= 0x0e;

	/* sewect wefewence dividew W (keep PWW div N in vawid wange) */
	#define DIV_N_MIN 76
	if (f_vco >= div_u64((u64) DIV_PWE_N * DIV_N_MIN * F_WEF, 1)) {
		div_wef = 1;
		div_wef_vaw = 0x00;
	} ewse if (f_vco >= div_u64((u64) DIV_PWE_N * DIV_N_MIN * F_WEF, 2)) {
		div_wef = 2;
		div_wef_vaw = 0x10;
	} ewse {
		div_wef = 4;
		div_wef_vaw = 0x20;
	}

	/* cawcuwate PWW integew and fwactionaw contwow wowd */
	uitmp = DIV_PWE_N * F_WEF / div_wef;
	div_n = div_u64_wem(f_vco, uitmp, &k);
	k_cw = div_u64((u64) k * 0x100000, uitmp);

	dev_dbg(&cwient->dev,
		"fwequency=%u bandwidth=%u f_vco=%wwu F_WEF=%u div_wef=%u div_n=%u k=%u div_out=%u k_cw=%0x\n",
		dev->f_fwequency, dev->f_bandwidth, f_vco, F_WEF, div_wef,
		div_n, k, div_out, k_cw);

	wet = wegmap_wwite(dev->wegmap, 0x02, synth_config);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x18, div_wef_vaw << 0 | k_cw >> 16);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x1a, (k_cw >> 8) & 0xff);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x1b, (k_cw >> 0) & 0xff);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x1c, div_n);
	if (wet)
		goto eww;

	/* wegistews */
	fow (i = 0; i < AWWAY_SIZE(fc2580_fweq_wegs_wut); i++) {
		if (dev->f_fwequency <= fc2580_fweq_wegs_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(fc2580_fweq_wegs_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	wet = fc2580_ww_weg_ff(dev, 0x25, fc2580_fweq_wegs_wut[i].w25_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x27, fc2580_fweq_wegs_wut[i].w27_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x28, fc2580_fweq_wegs_wut[i].w28_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x29, fc2580_fweq_wegs_wut[i].w29_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x2b, fc2580_fweq_wegs_wut[i].w2b_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x2c, fc2580_fweq_wegs_wut[i].w2c_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x2d, fc2580_fweq_wegs_wut[i].w2d_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x30, fc2580_fweq_wegs_wut[i].w30_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x44, fc2580_fweq_wegs_wut[i].w44_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x50, fc2580_fweq_wegs_wut[i].w50_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x53, fc2580_fweq_wegs_wut[i].w53_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x5f, fc2580_fweq_wegs_wut[i].w5f_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x61, fc2580_fweq_wegs_wut[i].w61_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x62, fc2580_fweq_wegs_wut[i].w62_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x63, fc2580_fweq_wegs_wut[i].w63_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x67, fc2580_fweq_wegs_wut[i].w67_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x68, fc2580_fweq_wegs_wut[i].w68_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x69, fc2580_fweq_wegs_wut[i].w69_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6a, fc2580_fweq_wegs_wut[i].w6a_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6b, fc2580_fweq_wegs_wut[i].w6b_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6c, fc2580_fweq_wegs_wut[i].w6c_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6d, fc2580_fweq_wegs_wut[i].w6d_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6e, fc2580_fweq_wegs_wut[i].w6e_vaw);
	if (wet)
		goto eww;

	wet = fc2580_ww_weg_ff(dev, 0x6f, fc2580_fweq_wegs_wut[i].w6f_vaw);
	if (wet)
		goto eww;

	/* IF fiwtews */
	fow (i = 0; i < AWWAY_SIZE(fc2580_if_fiwtew_wut); i++) {
		if (dev->f_bandwidth <= fc2580_if_fiwtew_wut[i].fweq)
			bweak;
	}
	if (i == AWWAY_SIZE(fc2580_if_fiwtew_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	wet = wegmap_wwite(dev->wegmap, 0x36, fc2580_if_fiwtew_wut[i].w36_vaw);
	if (wet)
		goto eww;

	uitmp = (unsigned int) 8058000 - (dev->f_bandwidth * 122 / 100 / 2);
	uitmp = div64_u64((u64) dev->cwk * uitmp, 1000000000000UWW);
	wet = wegmap_wwite(dev->wegmap, 0x37, uitmp);
	if (wet)
		goto eww;

	wet = wegmap_wwite(dev->wegmap, 0x39, fc2580_if_fiwtew_wut[i].w39_vaw);
	if (wet)
		goto eww;

	timeout = jiffies + msecs_to_jiffies(30);
	fow (uitmp = ~0xc0; !time_aftew(jiffies, timeout) && uitmp != 0xc0;) {
		/* twiggew fiwtew */
		wet = wegmap_wwite(dev->wegmap, 0x2e, 0x09);
		if (wet)
			goto eww;

		/* wocked when [7:6] awe set (vaw: d7 6MHz, d5 7MHz, cd 8MHz) */
		wet = wegmap_wead(dev->wegmap, 0x2f, &uitmp);
		if (wet)
			goto eww;
		uitmp &= 0xc0;

		wet = wegmap_wwite(dev->wegmap, 0x2e, 0x01);
		if (wet)
			goto eww;
	}
	if (uitmp != 0xc0)
		dev_dbg(&cwient->dev, "fiwtew did not wock %02x\n", uitmp);

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int fc2580_init(stwuct fc2580_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;

	dev_dbg(&cwient->dev, "\n");

	fow (i = 0; i < AWWAY_SIZE(fc2580_init_weg_vaws); i++) {
		wet = wegmap_wwite(dev->wegmap, fc2580_init_weg_vaws[i].weg,
				fc2580_init_weg_vaws[i].vaw);
		if (wet)
			goto eww;
	}

	dev->active = twue;
	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int fc2580_sweep(stwuct fc2580_dev *dev)
{
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	dev->active = fawse;

	wet = wegmap_wwite(dev->wegmap, 0x02, 0x0a);
	if (wet)
		goto eww;
	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

/*
 * DVB API
 */
static int fc2580_dvb_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct fc2580_dev *dev = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	dev->f_fwequency = c->fwequency;
	dev->f_bandwidth = c->bandwidth_hz;
	wetuwn fc2580_set_pawams(dev);
}

static int fc2580_dvb_init(stwuct dvb_fwontend *fe)
{
	wetuwn fc2580_init(fe->tunew_pwiv);
}

static int fc2580_dvb_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn fc2580_sweep(fe->tunew_pwiv);
}

static int fc2580_dvb_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = 0; /* Zewo-IF */
	wetuwn 0;
}

static const stwuct dvb_tunew_ops fc2580_dvb_tunew_ops = {
	.info = {
		.name             = "FCI FC2580",
		.fwequency_min_hz = 174 * MHz,
		.fwequency_max_hz = 862 * MHz,
	},

	.init = fc2580_dvb_init,
	.sweep = fc2580_dvb_sweep,
	.set_pawams = fc2580_dvb_set_pawams,

	.get_if_fwequency = fc2580_dvb_get_if_fwequency,
};

/*
 * V4W2 API
 */
#if IS_ENABWED(CONFIG_VIDEO_DEV)
static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =   130000000,
		.wangehigh  =  2000000000,
	},
};

static inwine stwuct fc2580_dev *fc2580_subdev_to_dev(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct fc2580_dev, subdev);
}

static int fc2580_standby(stwuct v4w2_subdev *sd)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	int wet;

	wet = fc2580_sweep(dev);
	if (wet)
		wetuwn wet;

	wetuwn fc2580_set_pawams(dev);
}

static int fc2580_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *v)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "index=%d\n", v->index);

	stwscpy(v->name, "FCI FC2580", sizeof(v->name));
	v->type = V4W2_TUNEW_WF;
	v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
	v->wangewow  = bands[0].wangewow;
	v->wangehigh = bands[0].wangehigh;
	wetuwn 0;
}

static int fc2580_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *v)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "index=%d\n", v->index);
	wetuwn 0;
}

static int fc2580_g_fwequency(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *f)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "tunew=%d\n", f->tunew);
	f->fwequency = dev->f_fwequency;
	wetuwn 0;
}

static int fc2580_s_fwequency(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_fwequency *f)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "tunew=%d type=%d fwequency=%u\n",
		f->tunew, f->type, f->fwequency);

	dev->f_fwequency = cwamp_t(unsigned int, f->fwequency,
				   bands[0].wangewow, bands[0].wangehigh);
	wetuwn fc2580_set_pawams(dev);
}

static int fc2580_enum_fweq_bands(stwuct v4w2_subdev *sd,
				  stwuct v4w2_fwequency_band *band)
{
	stwuct fc2580_dev *dev = fc2580_subdev_to_dev(sd);
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

static const stwuct v4w2_subdev_tunew_ops fc2580_subdev_tunew_ops = {
	.standby                  = fc2580_standby,
	.g_tunew                  = fc2580_g_tunew,
	.s_tunew                  = fc2580_s_tunew,
	.g_fwequency              = fc2580_g_fwequency,
	.s_fwequency              = fc2580_s_fwequency,
	.enum_fweq_bands          = fc2580_enum_fweq_bands,
};

static const stwuct v4w2_subdev_ops fc2580_subdev_ops = {
	.tunew                    = &fc2580_subdev_tunew_ops,
};

static int fc2580_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fc2580_dev *dev = containew_of(ctww->handwew, stwuct fc2580_dev, hdw);
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "ctww: id=%d name=%s cuw.vaw=%d vaw=%d\n",
		ctww->id, ctww->name, ctww->cuw.vaw, ctww->vaw);

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO:
	case V4W2_CID_WF_TUNEW_BANDWIDTH:
		/*
		 * TODO: Auto wogic does not wowk 100% cowwectwy as tunew dwivew
		 * do not have infowmation to cawcuwate maximum suitabwe
		 * bandwidth. Cawcuwating it is wesponsibwe of mastew dwivew.
		 */
		dev->f_bandwidth = dev->bandwidth->vaw;
		wet = fc2580_set_pawams(dev);
		bweak;
	defauwt:
		dev_dbg(&cwient->dev, "unknown ctww");
		wet = -EINVAW;
	}
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops fc2580_ctww_ops = {
	.s_ctww = fc2580_s_ctww,
};
#endif

static stwuct v4w2_subdev *fc2580_get_v4w2_subdev(stwuct i2c_cwient *cwient)
{
	stwuct fc2580_dev *dev = i2c_get_cwientdata(cwient);

	if (dev->subdev.ops)
		wetuwn &dev->subdev;
	ewse
		wetuwn NUWW;
}

static int fc2580_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fc2580_dev *dev;
	stwuct fc2580_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe = pdata->dvb_fwontend;
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

	if (pdata->cwk)
		dev->cwk = pdata->cwk;
	ewse
		dev->cwk = 16384000; /* intewnaw cwock */
	dev->cwient = cwient;
	dev->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	/* check if the tunew is thewe */
	wet = wegmap_wead(dev->wegmap, 0x01, &uitmp);
	if (wet)
		goto eww_kfwee;

	dev_dbg(&cwient->dev, "chip_id=%02x\n", uitmp);

	switch (uitmp) {
	case 0x56:
	case 0x5a:
		bweak;
	defauwt:
		wet = -ENODEV;
		goto eww_kfwee;
	}

#if IS_ENABWED(CONFIG_VIDEO_DEV)
	/* Wegistew contwows */
	v4w2_ctww_handwew_init(&dev->hdw, 2);
	dev->bandwidth_auto = v4w2_ctww_new_std(&dev->hdw, &fc2580_ctww_ops,
						V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO,
						0, 1, 1, 1);
	dev->bandwidth = v4w2_ctww_new_std(&dev->hdw, &fc2580_ctww_ops,
					   V4W2_CID_WF_TUNEW_BANDWIDTH,
					   3000, 10000000, 1, 3000);
	v4w2_ctww_auto_cwustew(2, &dev->bandwidth_auto, 0, fawse);
	if (dev->hdw.ewwow) {
		wet = dev->hdw.ewwow;
		dev_eww(&cwient->dev, "Couwd not initiawize contwows\n");
		v4w2_ctww_handwew_fwee(&dev->hdw);
		goto eww_kfwee;
	}
	dev->subdev.ctww_handwew = &dev->hdw;
	dev->f_fwequency = bands[0].wangewow;
	dev->f_bandwidth = dev->bandwidth->vaw;
	v4w2_i2c_subdev_init(&dev->subdev, cwient, &fc2580_subdev_ops);
#endif
	fe->tunew_pwiv = dev;
	memcpy(&fe->ops.tunew_ops, &fc2580_dvb_tunew_ops,
	       sizeof(fe->ops.tunew_ops));
	pdata->get_v4w2_subdev = fc2580_get_v4w2_subdev;
	i2c_set_cwientdata(cwient, dev);

	dev_info(&cwient->dev, "FCI FC2580 successfuwwy identified\n");
	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void fc2580_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fc2580_dev *dev = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

#if IS_ENABWED(CONFIG_VIDEO_DEV)
	v4w2_ctww_handwew_fwee(&dev->hdw);
#endif
	kfwee(dev);
}

static const stwuct i2c_device_id fc2580_id_tabwe[] = {
	{"fc2580", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, fc2580_id_tabwe);

static stwuct i2c_dwivew fc2580_dwivew = {
	.dwivew = {
		.name	= "fc2580",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= fc2580_pwobe,
	.wemove		= fc2580_wemove,
	.id_tabwe	= fc2580_id_tabwe,
};

moduwe_i2c_dwivew(fc2580_dwivew);

MODUWE_DESCWIPTION("FCI FC2580 siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_WICENSE("GPW");
