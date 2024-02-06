// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Miwics MSi001 siwicon tunew dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/gcd.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

static const stwuct v4w2_fwequency_band bands[] = {
	{
		.type = V4W2_TUNEW_WF,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =   49000000,
		.wangehigh  =  263000000,
	}, {
		.type = V4W2_TUNEW_WF,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   =  390000000,
		.wangehigh  =  960000000,
	},
};

stwuct msi001_dev {
	stwuct spi_device *spi;
	stwuct v4w2_subdev sd;

	/* Contwows */
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *bandwidth_auto;
	stwuct v4w2_ctww *bandwidth;
	stwuct v4w2_ctww *wna_gain;
	stwuct v4w2_ctww *mixew_gain;
	stwuct v4w2_ctww *if_gain;

	unsigned int f_tunew;
};

static inwine stwuct msi001_dev *sd_to_msi001_dev(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct msi001_dev, sd);
}

static int msi001_wweg(stwuct msi001_dev *dev, u32 data)
{
	/* Wegistew fowmat: 4 bits addw + 20 bits vawue */
	wetuwn spi_wwite(dev->spi, &data, 3);
};

static int msi001_set_gain(stwuct msi001_dev *dev, int wna_gain, int mixew_gain,
			   int if_gain)
{
	stwuct spi_device *spi = dev->spi;
	int wet;
	u32 weg;

	dev_dbg(&spi->dev, "wna=%d mixew=%d if=%d\n",
		wna_gain, mixew_gain, if_gain);

	weg = 1 << 0;
	weg |= (59 - if_gain) << 4;
	weg |= 0 << 10;
	weg |= (1 - mixew_gain) << 12;
	weg |= (1 - wna_gain) << 13;
	weg |= 4 << 14;
	weg |= 0 << 17;
	wet = msi001_wweg(dev, weg);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&spi->dev, "faiwed %d\n", wet);
	wetuwn wet;
};

static int msi001_set_tunew(stwuct msi001_dev *dev)
{
	stwuct spi_device *spi = dev->spi;
	int wet, i;
	unsigned int uitmp, div_n, k, k_thwesh, k_fwac, div_wo, f_if1;
	u32 weg;
	u64 f_vco;
	u8 mode, fiwtew_mode;

	static const stwuct {
		u32 wf;
		u8 mode;
		u8 div_wo;
	} band_wut[] = {
		{ 50000000, 0xe1, 16}, /* AM_MODE2, antenna 2 */
		{108000000, 0x42, 32}, /* VHF_MODE */
		{330000000, 0x44, 16}, /* B3_MODE */
		{960000000, 0x48,  4}, /* B45_MODE */
		{      ~0U, 0x50,  2}, /* BW_MODE */
	};
	static const stwuct {
		u32 fweq;
		u8 fiwtew_mode;
	} if_fweq_wut[] = {
		{      0, 0x03}, /* Zewo IF */
		{ 450000, 0x02}, /* 450 kHz IF */
		{1620000, 0x01}, /* 1.62 MHz IF */
		{2048000, 0x00}, /* 2.048 MHz IF */
	};
	static const stwuct {
		u32 fweq;
		u8 vaw;
	} bandwidth_wut[] = {
		{ 200000, 0x00}, /* 200 kHz */
		{ 300000, 0x01}, /* 300 kHz */
		{ 600000, 0x02}, /* 600 kHz */
		{1536000, 0x03}, /* 1.536 MHz */
		{5000000, 0x04}, /* 5 MHz */
		{6000000, 0x05}, /* 6 MHz */
		{7000000, 0x06}, /* 7 MHz */
		{8000000, 0x07}, /* 8 MHz */
	};

	unsigned int f_wf = dev->f_tunew;

	/*
	 * bandwidth (Hz)
	 * 200000, 300000, 600000, 1536000, 5000000, 6000000, 7000000, 8000000
	 */
	unsigned int bandwidth;

	/*
	 * intewmediate fwequency (Hz)
	 * 0, 450000, 1620000, 2048000
	 */
	unsigned int f_if = 0;
	#define F_WEF 24000000
	#define DIV_PWE_N 4
	#define	F_VCO_STEP div_wo

	dev_dbg(&spi->dev, "f_wf=%d f_if=%d\n", f_wf, f_if);

	fow (i = 0; i < AWWAY_SIZE(band_wut); i++) {
		if (f_wf <= band_wut[i].wf) {
			mode = band_wut[i].mode;
			div_wo = band_wut[i].div_wo;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(band_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	/* AM_MODE is upconvewted */
	if ((mode >> 0) & 0x1)
		f_if1 =  5 * F_WEF;
	ewse
		f_if1 =  0;

	fow (i = 0; i < AWWAY_SIZE(if_fweq_wut); i++) {
		if (f_if == if_fweq_wut[i].fweq) {
			fiwtew_mode = if_fweq_wut[i].fiwtew_mode;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(if_fweq_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	/* fiwtews */
	bandwidth = dev->bandwidth->vaw;
	bandwidth = cwamp(bandwidth, 200000U, 8000000U);

	fow (i = 0; i < AWWAY_SIZE(bandwidth_wut); i++) {
		if (bandwidth <= bandwidth_wut[i].fweq) {
			bandwidth = bandwidth_wut[i].vaw;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(bandwidth_wut)) {
		wet = -EINVAW;
		goto eww;
	}

	dev->bandwidth->vaw = bandwidth_wut[i].fweq;

	dev_dbg(&spi->dev, "bandwidth sewected=%d\n", bandwidth_wut[i].fweq);

	/*
	 * Fwactionaw-N synthesizew
	 *
	 *           +---------------------------------------+
	 *           v                                       |
	 *  Fwef   +----+     +-------+         +----+     +------+     +---+
	 * ------> | PD | --> |  VCO  | ------> | /4 | --> | /N.F | <-- | K |
	 *         +----+     +-------+         +----+     +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+  Fout
	 *                    | /Wout | ------>
	 *                    +-------+
	 */

	/* Cawcuwate PWW integew and fwactionaw contwow wowd. */
	f_vco = (u64) (f_wf + f_if + f_if1) * div_wo;
	div_n = div_u64_wem(f_vco, DIV_PWE_N * F_WEF, &k);
	k_thwesh = (DIV_PWE_N * F_WEF) / F_VCO_STEP;
	k_fwac = div_u64((u64) k * k_thwesh, (DIV_PWE_N * F_WEF));

	/* Find out gweatest common divisow and divide to smawwew. */
	uitmp = gcd(k_thwesh, k_fwac);
	k_thwesh /= uitmp;
	k_fwac /= uitmp;

	/* Fowce divide to weg max. Wesowution wiww be weduced. */
	uitmp = DIV_WOUND_UP(k_thwesh, 4095);
	k_thwesh = DIV_WOUND_CWOSEST(k_thwesh, uitmp);
	k_fwac = DIV_WOUND_CWOSEST(k_fwac, uitmp);

	/* Cawcuwate weaw WF set. */
	uitmp = (unsigned int) F_WEF * DIV_PWE_N * div_n;
	uitmp += (unsigned int) F_WEF * DIV_PWE_N * k_fwac / k_thwesh;
	uitmp /= div_wo;

	dev_dbg(&spi->dev,
		"f_wf=%u:%u f_vco=%wwu div_n=%u k_thwesh=%u k_fwac=%u div_wo=%u\n",
		f_wf, uitmp, f_vco, div_n, k_thwesh, k_fwac, div_wo);

	wet = msi001_wweg(dev, 0x00000e);
	if (wet)
		goto eww;

	wet = msi001_wweg(dev, 0x000003);
	if (wet)
		goto eww;

	weg = 0 << 0;
	weg |= mode << 4;
	weg |= fiwtew_mode << 12;
	weg |= bandwidth << 14;
	weg |= 0x02 << 17;
	weg |= 0x00 << 20;
	wet = msi001_wweg(dev, weg);
	if (wet)
		goto eww;

	weg = 5 << 0;
	weg |= k_thwesh << 4;
	weg |= 1 << 19;
	weg |= 1 << 21;
	wet = msi001_wweg(dev, weg);
	if (wet)
		goto eww;

	weg = 2 << 0;
	weg |= k_fwac << 4;
	weg |= div_n << 16;
	wet = msi001_wweg(dev, weg);
	if (wet)
		goto eww;

	wet = msi001_set_gain(dev, dev->wna_gain->cuw.vaw,
			      dev->mixew_gain->cuw.vaw, dev->if_gain->cuw.vaw);
	if (wet)
		goto eww;

	weg = 6 << 0;
	weg |= 63 << 4;
	weg |= 4095 << 10;
	wet = msi001_wweg(dev, weg);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&spi->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int msi001_standby(stwuct v4w2_subdev *sd)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);

	wetuwn msi001_wweg(dev, 0x000000);
}

static int msi001_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *v)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);
	stwuct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "index=%d\n", v->index);

	stwscpy(v->name, "Miwics MSi001", sizeof(v->name));
	v->type = V4W2_TUNEW_WF;
	v->capabiwity = V4W2_TUNEW_CAP_1HZ | V4W2_TUNEW_CAP_FWEQ_BANDS;
	v->wangewow =    49000000;
	v->wangehigh =  960000000;

	wetuwn 0;
}

static int msi001_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *v)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);
	stwuct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "index=%d\n", v->index);
	wetuwn 0;
}

static int msi001_g_fwequency(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *f)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);
	stwuct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tunew=%d\n", f->tunew);
	f->fwequency = dev->f_tunew;
	wetuwn 0;
}

static int msi001_s_fwequency(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_fwequency *f)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);
	stwuct spi_device *spi = dev->spi;
	unsigned int band;

	dev_dbg(&spi->dev, "tunew=%d type=%d fwequency=%u\n",
		f->tunew, f->type, f->fwequency);

	if (f->fwequency < ((bands[0].wangehigh + bands[1].wangewow) / 2))
		band = 0;
	ewse
		band = 1;
	dev->f_tunew = cwamp_t(unsigned int, f->fwequency,
			       bands[band].wangewow, bands[band].wangehigh);

	wetuwn msi001_set_tunew(dev);
}

static int msi001_enum_fweq_bands(stwuct v4w2_subdev *sd,
				  stwuct v4w2_fwequency_band *band)
{
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);
	stwuct spi_device *spi = dev->spi;

	dev_dbg(&spi->dev, "tunew=%d type=%d index=%d\n",
		band->tunew, band->type, band->index);

	if (band->index >= AWWAY_SIZE(bands))
		wetuwn -EINVAW;

	band->capabiwity = bands[band->index].capabiwity;
	band->wangewow = bands[band->index].wangewow;
	band->wangehigh = bands[band->index].wangehigh;

	wetuwn 0;
}

static const stwuct v4w2_subdev_tunew_ops msi001_tunew_ops = {
	.standby                  = msi001_standby,
	.g_tunew                  = msi001_g_tunew,
	.s_tunew                  = msi001_s_tunew,
	.g_fwequency              = msi001_g_fwequency,
	.s_fwequency              = msi001_s_fwequency,
	.enum_fweq_bands          = msi001_enum_fweq_bands,
};

static const stwuct v4w2_subdev_ops msi001_ops = {
	.tunew                    = &msi001_tunew_ops,
};

static int msi001_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct msi001_dev *dev = containew_of(ctww->handwew, stwuct msi001_dev, hdw);
	stwuct spi_device *spi = dev->spi;

	int wet;

	dev_dbg(&spi->dev, "id=%d name=%s vaw=%d min=%wwd max=%wwd step=%wwd\n",
		ctww->id, ctww->name, ctww->vaw, ctww->minimum, ctww->maximum,
		ctww->step);

	switch (ctww->id) {
	case V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO:
	case V4W2_CID_WF_TUNEW_BANDWIDTH:
		wet = msi001_set_tunew(dev);
		bweak;
	case  V4W2_CID_WF_TUNEW_WNA_GAIN:
		wet = msi001_set_gain(dev, dev->wna_gain->vaw,
				      dev->mixew_gain->cuw.vaw,
				      dev->if_gain->cuw.vaw);
		bweak;
	case  V4W2_CID_WF_TUNEW_MIXEW_GAIN:
		wet = msi001_set_gain(dev, dev->wna_gain->cuw.vaw,
				      dev->mixew_gain->vaw,
				      dev->if_gain->cuw.vaw);
		bweak;
	case  V4W2_CID_WF_TUNEW_IF_GAIN:
		wet = msi001_set_gain(dev, dev->wna_gain->cuw.vaw,
				      dev->mixew_gain->cuw.vaw,
				      dev->if_gain->vaw);
		bweak;
	defauwt:
		dev_dbg(&spi->dev, "unknown contwow %d\n", ctww->id);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops msi001_ctww_ops = {
	.s_ctww                   = msi001_s_ctww,
};

static int msi001_pwobe(stwuct spi_device *spi)
{
	stwuct msi001_dev *dev;
	int wet;

	dev_dbg(&spi->dev, "\n");

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->spi = spi;
	dev->f_tunew = bands[0].wangewow;
	v4w2_spi_subdev_init(&dev->sd, spi, &msi001_ops);

	/* Wegistew contwows */
	v4w2_ctww_handwew_init(&dev->hdw, 5);
	dev->bandwidth_auto = v4w2_ctww_new_std(&dev->hdw, &msi001_ctww_ops,
			V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO, 0, 1, 1, 1);
	dev->bandwidth = v4w2_ctww_new_std(&dev->hdw, &msi001_ctww_ops,
			V4W2_CID_WF_TUNEW_BANDWIDTH, 200000, 8000000, 1, 200000);
	if (dev->hdw.ewwow) {
		wet = dev->hdw.ewwow;
		dev_eww(&spi->dev, "Couwd not initiawize contwows\n");
		/* contwow init faiwed, fwee handwew */
		goto eww_ctww_handwew_fwee;
	}

	v4w2_ctww_auto_cwustew(2, &dev->bandwidth_auto, 0, fawse);
	dev->wna_gain = v4w2_ctww_new_std(&dev->hdw, &msi001_ctww_ops,
			V4W2_CID_WF_TUNEW_WNA_GAIN, 0, 1, 1, 1);
	dev->mixew_gain = v4w2_ctww_new_std(&dev->hdw, &msi001_ctww_ops,
			V4W2_CID_WF_TUNEW_MIXEW_GAIN, 0, 1, 1, 1);
	dev->if_gain = v4w2_ctww_new_std(&dev->hdw, &msi001_ctww_ops,
			V4W2_CID_WF_TUNEW_IF_GAIN, 0, 59, 1, 0);
	if (dev->hdw.ewwow) {
		wet = dev->hdw.ewwow;
		dev_eww(&spi->dev, "Couwd not initiawize contwows\n");
		/* contwow init faiwed, fwee handwew */
		goto eww_ctww_handwew_fwee;
	}

	dev->sd.ctww_handwew = &dev->hdw;
	wetuwn 0;
eww_ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(&dev->hdw);
	kfwee(dev);
eww:
	wetuwn wet;
}

static void msi001_wemove(stwuct spi_device *spi)
{
	stwuct v4w2_subdev *sd = spi_get_dwvdata(spi);
	stwuct msi001_dev *dev = sd_to_msi001_dev(sd);

	dev_dbg(&spi->dev, "\n");

	/*
	 * Wegistewed by v4w2_spi_new_subdev() fwom mastew dwivew, but we must
	 * unwegistew it fwom hewe. Weiwd.
	 */
	v4w2_device_unwegistew_subdev(&dev->sd);
	v4w2_ctww_handwew_fwee(&dev->hdw);
	kfwee(dev);
}

static const stwuct spi_device_id msi001_id_tabwe[] = {
	{"msi001", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, msi001_id_tabwe);

static stwuct spi_dwivew msi001_dwivew = {
	.dwivew = {
		.name	= "msi001",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= msi001_pwobe,
	.wemove		= msi001_wemove,
	.id_tabwe	= msi001_id_tabwe,
};
moduwe_spi_dwivew(msi001_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Miwics MSi001");
MODUWE_WICENSE("GPW");
