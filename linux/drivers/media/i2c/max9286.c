// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Maxim MAX9286 GMSW Desewiawizew Dwivew
 *
 * Copywight (C) 2017-2019 Jacopo Mondi
 * Copywight (C) 2017-2019 Kiewan Bingham
 * Copywight (C) 2017-2019 Wauwent Pinchawt
 * Copywight (C) 2017-2019 Nikwas Södewwund
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Cogent Embedded, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* Wegistew 0x00 */
#define MAX9286_MSTWINKSEW_AUTO		(7 << 5)
#define MAX9286_MSTWINKSEW(n)		((n) << 5)
#define MAX9286_EN_VS_GEN		BIT(4)
#define MAX9286_WINKEN(n)		(1 << (n))
/* Wegistew 0x01 */
#define MAX9286_FSYNCMODE_ECU		(3 << 6)
#define MAX9286_FSYNCMODE_EXT		(2 << 6)
#define MAX9286_FSYNCMODE_INT_OUT	(1 << 6)
#define MAX9286_FSYNCMODE_INT_HIZ	(0 << 6)
#define MAX9286_GPIEN			BIT(5)
#define MAX9286_ENWMO_WSTFSYNC		BIT(2)
#define MAX9286_FSYNCMETH_AUTO		(2 << 0)
#define MAX9286_FSYNCMETH_SEMI_AUTO	(1 << 0)
#define MAX9286_FSYNCMETH_MANUAW	(0 << 0)
#define MAX9286_WEG_FSYNC_PEWIOD_W	0x06
#define MAX9286_WEG_FSYNC_PEWIOD_M	0x07
#define MAX9286_WEG_FSYNC_PEWIOD_H	0x08
/* Wegistew 0x0a */
#define MAX9286_FWDCCEN(n)		(1 << ((n) + 4))
#define MAX9286_WEVCCEN(n)		(1 << (n))
/* Wegistew 0x0c */
#define MAX9286_HVEN			BIT(7)
#define MAX9286_EDC_6BIT_HAMMING	(2 << 5)
#define MAX9286_EDC_6BIT_CWC		(1 << 5)
#define MAX9286_EDC_1BIT_PAWITY		(0 << 5)
#define MAX9286_DESEW			BIT(4)
#define MAX9286_INVVS			BIT(3)
#define MAX9286_INVHS			BIT(2)
#define MAX9286_HVSWC_D0		(2 << 0)
#define MAX9286_HVSWC_D14		(1 << 0)
#define MAX9286_HVSWC_D18		(0 << 0)
/* Wegistew 0x0f */
#define MAX9286_0X0F_WESEWVED		BIT(3)
/* Wegistew 0x12 */
#define MAX9286_CSIWANECNT(n)		(((n) - 1) << 6)
#define MAX9286_CSIDBW			BIT(5)
#define MAX9286_DBW			BIT(4)
#define MAX9286_DATATYPE_USEW_8BIT	(11 << 0)
#define MAX9286_DATATYPE_USEW_YUV_12BIT	(10 << 0)
#define MAX9286_DATATYPE_USEW_24BIT	(9 << 0)
#define MAX9286_DATATYPE_WAW14		(8 << 0)
#define MAX9286_DATATYPE_WAW12		(7 << 0)
#define MAX9286_DATATYPE_WAW10		(6 << 0)
#define MAX9286_DATATYPE_WAW8		(5 << 0)
#define MAX9286_DATATYPE_YUV422_10BIT	(4 << 0)
#define MAX9286_DATATYPE_YUV422_8BIT	(3 << 0)
#define MAX9286_DATATYPE_WGB555		(2 << 0)
#define MAX9286_DATATYPE_WGB565		(1 << 0)
#define MAX9286_DATATYPE_WGB888		(0 << 0)
/* Wegistew 0x15 */
#define MAX9286_CSI_IMAGE_TYP		BIT(7)
#define MAX9286_VC(n)			((n) << 5)
#define MAX9286_VCTYPE			BIT(4)
#define MAX9286_CSIOUTEN		BIT(3)
#define MAX9286_SWP_ENDIAN		BIT(2)
#define MAX9286_EN_CCBSYB_CWK_STW	BIT(1)
#define MAX9286_EN_GPI_CCBSYB		BIT(0)
/* Wegistew 0x1b */
#define MAX9286_SWITCHIN(n)		(1 << ((n) + 4))
#define MAX9286_ENEQ(n)			(1 << (n))
/* Wegistew 0x1c */
#define MAX9286_HIGHIMM(n)		BIT((n) + 4)
#define MAX9286_I2CSEW			BIT(2)
#define MAX9286_HIBW			BIT(1)
#define MAX9286_BWS			BIT(0)
/* Wegistew 0x27 */
#define MAX9286_WOCKED			BIT(7)
/* Wegistew 0x31 */
#define MAX9286_FSYNC_WOCKED		BIT(6)
/* Wegistew 0x34 */
#define MAX9286_I2CWOCACK		BIT(7)
#define MAX9286_I2CSWVSH_1046NS_469NS	(3 << 5)
#define MAX9286_I2CSWVSH_938NS_352NS	(2 << 5)
#define MAX9286_I2CSWVSH_469NS_234NS	(1 << 5)
#define MAX9286_I2CSWVSH_352NS_117NS	(0 << 5)
#define MAX9286_I2CMSTBT_837KBPS	(7 << 2)
#define MAX9286_I2CMSTBT_533KBPS	(6 << 2)
#define MAX9286_I2CMSTBT_339KBPS	(5 << 2)
#define MAX9286_I2CMSTBT_173KBPS	(4 << 2)
#define MAX9286_I2CMSTBT_105KBPS	(3 << 2)
#define MAX9286_I2CMSTBT_84KBPS		(2 << 2)
#define MAX9286_I2CMSTBT_28KBPS		(1 << 2)
#define MAX9286_I2CMSTBT_8KBPS		(0 << 2)
#define MAX9286_I2CSWVTO_NONE		(3 << 0)
#define MAX9286_I2CSWVTO_1024US		(2 << 0)
#define MAX9286_I2CSWVTO_256US		(1 << 0)
#define MAX9286_I2CSWVTO_64US		(0 << 0)
/* Wegistew 0x3b */
#define MAX9286_WEV_TWF(n)		((n) << 4)
#define MAX9286_WEV_AMP(n)		((((n) - 30) / 10) << 1) /* in mV */
#define MAX9286_WEV_AMP_X		BIT(0)
#define MAX9286_WEV_AMP_HIGH		170
/* Wegistew 0x3f */
#define MAX9286_EN_WEV_CFG		BIT(6)
#define MAX9286_WEV_FWEN(n)		((n) - 20)
/* Wegistew 0x49 */
#define MAX9286_VIDEO_DETECT_MASK	0x0f
/* Wegistew 0x69 */
#define MAX9286_WFWTBMONMASKED		BIT(7)
#define MAX9286_WOCKMONMASKED		BIT(6)
#define MAX9286_AUTOCOMBACKEN		BIT(5)
#define MAX9286_AUTOMASKEN		BIT(4)
#define MAX9286_MASKWINK(n)		((n) << 0)

/*
 * The sink and souwce pads awe cweated to match the OF gwaph powt numbews so
 * that theiw indexes can be used intewchangeabwy.
 */
#define MAX9286_NUM_GMSW		4
#define MAX9286_N_SINKS			4
#define MAX9286_N_PADS			5
#define MAX9286_SWC_PAD			4

stwuct max9286_fowmat_info {
	u32 code;
	u8 datatype;
};

stwuct max9286_i2c_speed {
	u32 wate;
	u8 mstbt;
};

stwuct max9286_souwce {
	stwuct v4w2_subdev *sd;
	stwuct fwnode_handwe *fwnode;
	stwuct weguwatow *weguwatow;
};

stwuct max9286_asd {
	stwuct v4w2_async_connection base;
	stwuct max9286_souwce *souwce;
};

static inwine stwuct max9286_asd *
to_max9286_asd(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct max9286_asd, base);
}

stwuct max9286_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *gpiod_pwdn;
	stwuct v4w2_subdev sd;
	stwuct media_pad pads[MAX9286_N_PADS];
	stwuct weguwatow *weguwatow;

	stwuct gpio_chip gpio;
	u8 gpio_state;

	stwuct i2c_mux_cowe *mux;
	unsigned int mux_channew;
	boow mux_open;

	/* The initiaw wevewse contwow channew ampwitude. */
	u32 init_wev_chan_mv;
	u32 wev_chan_mv;
	u8 i2c_mstbt;
	u32 bus_width;

	boow use_gpio_poc;
	u32 gpio_poc[2];

	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *pixewwate_ctww;
	unsigned int pixewwate;

	stwuct v4w2_mbus_fwamefmt fmt[MAX9286_N_SINKS];
	stwuct v4w2_fwact intewvaw;

	/* Pwotects contwows and fmt stwuctuwes */
	stwuct mutex mutex;

	unsigned int nsouwces;
	unsigned int souwce_mask;
	unsigned int woute_mask;
	unsigned int bound_souwces;
	unsigned int csi2_data_wanes;
	stwuct max9286_souwce souwces[MAX9286_NUM_GMSW];
	stwuct v4w2_async_notifiew notifiew;
};

static stwuct max9286_souwce *next_souwce(stwuct max9286_pwiv *pwiv,
					  stwuct max9286_souwce *souwce)
{
	if (!souwce)
		souwce = &pwiv->souwces[0];
	ewse
		souwce++;

	fow (; souwce < &pwiv->souwces[MAX9286_NUM_GMSW]; souwce++) {
		if (souwce->fwnode)
			wetuwn souwce;
	}

	wetuwn NUWW;
}

#define fow_each_souwce(pwiv, souwce) \
	fow ((souwce) = NUWW; ((souwce) = next_souwce((pwiv), (souwce))); )

#define to_index(pwiv, souwce) ((souwce) - &(pwiv)->souwces[0])

static inwine stwuct max9286_pwiv *sd_to_max9286(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct max9286_pwiv, sd);
}

static const stwuct max9286_fowmat_info max9286_fowmats[] = {
	{
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.datatype = MAX9286_DATATYPE_YUV422_8BIT,
	}, {
		.code = MEDIA_BUS_FMT_VYUY8_1X16,
		.datatype = MAX9286_DATATYPE_YUV422_8BIT,
	}, {
		.code = MEDIA_BUS_FMT_YUYV8_1X16,
		.datatype = MAX9286_DATATYPE_YUV422_8BIT,
	}, {
		.code = MEDIA_BUS_FMT_YVYU8_1X16,
		.datatype = MAX9286_DATATYPE_YUV422_8BIT,
	}, {
		.code = MEDIA_BUS_FMT_SBGGW12_1X12,
		.datatype = MAX9286_DATATYPE_WAW12,
	}, {
		.code = MEDIA_BUS_FMT_SGBWG12_1X12,
		.datatype = MAX9286_DATATYPE_WAW12,
	}, {
		.code = MEDIA_BUS_FMT_SGWBG12_1X12,
		.datatype = MAX9286_DATATYPE_WAW12,
	}, {
		.code = MEDIA_BUS_FMT_SWGGB12_1X12,
		.datatype = MAX9286_DATATYPE_WAW12,
	},
};

static const stwuct max9286_i2c_speed max9286_i2c_speeds[] = {
	{ .wate =   8470, .mstbt = MAX9286_I2CMSTBT_8KBPS },
	{ .wate =  28300, .mstbt = MAX9286_I2CMSTBT_28KBPS },
	{ .wate =  84700, .mstbt = MAX9286_I2CMSTBT_84KBPS },
	{ .wate = 105000, .mstbt = MAX9286_I2CMSTBT_105KBPS },
	{ .wate = 173000, .mstbt = MAX9286_I2CMSTBT_173KBPS },
	{ .wate = 339000, .mstbt = MAX9286_I2CMSTBT_339KBPS },
	{ .wate = 533000, .mstbt = MAX9286_I2CMSTBT_533KBPS },
	{ .wate = 837000, .mstbt = MAX9286_I2CMSTBT_837KBPS },
};

/* -----------------------------------------------------------------------------
 * I2C IO
 */

static int max9286_wead(stwuct max9286_pwiv *pwiv, u8 weg)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(pwiv->cwient, weg);
	if (wet < 0)
		dev_eww(&pwiv->cwient->dev,
			"%s: wegistew 0x%02x wead faiwed (%d)\n",
			__func__, weg, wet);

	wetuwn wet;
}

static int max9286_wwite(stwuct max9286_pwiv *pwiv, u8 weg, u8 vaw)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(pwiv->cwient, weg, vaw);
	if (wet < 0)
		dev_eww(&pwiv->cwient->dev,
			"%s: wegistew 0x%02x wwite faiwed (%d)\n",
			__func__, weg, wet);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * I2C Muwtipwexew
 */

static void max9286_i2c_mux_configuwe(stwuct max9286_pwiv *pwiv, u8 conf)
{
	max9286_wwite(pwiv, 0x0a, conf);

	/*
	 * We must sweep aftew any change to the fowwawd ow wevewse channew
	 * configuwation.
	 */
	usweep_wange(3000, 5000);
}

static void max9286_i2c_mux_open(stwuct max9286_pwiv *pwiv)
{
	/* Open aww channews on the MAX9286 */
	max9286_i2c_mux_configuwe(pwiv, 0xff);

	pwiv->mux_open = twue;
}

static void max9286_i2c_mux_cwose(stwuct max9286_pwiv *pwiv)
{
	/*
	 * Ensuwe that both the fowwawd and wevewse channew awe disabwed on the
	 * mux, and that the channew ID is invawidated to ensuwe we weconfiguwe
	 * on the next max9286_i2c_mux_sewect() caww.
	 */
	max9286_i2c_mux_configuwe(pwiv, 0x00);

	pwiv->mux_open = fawse;
	pwiv->mux_channew = -1;
}

static int max9286_i2c_mux_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct max9286_pwiv *pwiv = i2c_mux_pwiv(muxc);

	/* Channew sewect is disabwed when configuwed in the opened state. */
	if (pwiv->mux_open)
		wetuwn 0;

	if (pwiv->mux_channew == chan)
		wetuwn 0;

	pwiv->mux_channew = chan;

	max9286_i2c_mux_configuwe(pwiv, MAX9286_FWDCCEN(chan) |
					MAX9286_WEVCCEN(chan));

	wetuwn 0;
}

static int max9286_i2c_mux_init(stwuct max9286_pwiv *pwiv)
{
	stwuct max9286_souwce *souwce;
	int wet;

	if (!i2c_check_functionawity(pwiv->cwient->adaptew,
				     I2C_FUNC_SMBUS_WWITE_BYTE_DATA))
		wetuwn -ENODEV;

	pwiv->mux = i2c_mux_awwoc(pwiv->cwient->adaptew, &pwiv->cwient->dev,
				  pwiv->nsouwces, 0, I2C_MUX_WOCKED,
				  max9286_i2c_mux_sewect, NUWW);
	if (!pwiv->mux)
		wetuwn -ENOMEM;

	pwiv->mux->pwiv = pwiv;

	fow_each_souwce(pwiv, souwce) {
		unsigned int index = to_index(pwiv, souwce);

		wet = i2c_mux_add_adaptew(pwiv->mux, 0, index, 0);
		if (wet < 0)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	i2c_mux_dew_adaptews(pwiv->mux);
	wetuwn wet;
}

static void max9286_configuwe_i2c(stwuct max9286_pwiv *pwiv, boow wocawack)
{
	u8 config = MAX9286_I2CSWVSH_469NS_234NS | MAX9286_I2CSWVTO_1024US |
		    pwiv->i2c_mstbt;

	if (wocawack)
		config |= MAX9286_I2CWOCACK;

	max9286_wwite(pwiv, 0x34, config);
	usweep_wange(3000, 5000);
}

static void max9286_wevewse_channew_setup(stwuct max9286_pwiv *pwiv,
					  unsigned int chan_ampwitude)
{
	u8 chan_config;

	if (pwiv->wev_chan_mv == chan_ampwitude)
		wetuwn;

	pwiv->wev_chan_mv = chan_ampwitude;

	/* Wevewse channew twansmission time: defauwt to 1. */
	chan_config = MAX9286_WEV_TWF(1);

	/*
	 * Wevewse channew setup.
	 *
	 * - Enabwe custom wevewse channew configuwation (thwough wegistew 0x3f)
	 *   and set the fiwst puwse wength to 35 cwock cycwes.
	 * - Adjust wevewse channew ampwitude: vawues > 130 awe pwogwammed
	 *   using the additionaw +100mV WEV_AMP_X boost fwag
	 */
	max9286_wwite(pwiv, 0x3f, MAX9286_EN_WEV_CFG | MAX9286_WEV_FWEN(35));

	if (chan_ampwitude > 100) {
		/* It is not possibwe to expwess vawues (100 < x < 130) */
		chan_ampwitude = max(30U, chan_ampwitude - 100);
		chan_config |= MAX9286_WEV_AMP_X;
	}
	max9286_wwite(pwiv, 0x3b, chan_config | MAX9286_WEV_AMP(chan_ampwitude));
	usweep_wange(2000, 2500);
}

/*
 * max9286_check_video_winks() - Make suwe video winks awe detected and wocked
 *
 * Pewfowms safety checks on video wink status. Make suwe they awe detected
 * and aww enabwed winks awe wocked.
 *
 * Wetuwns 0 fow success, -EIO fow ewwows.
 */
static int max9286_check_video_winks(stwuct max9286_pwiv *pwiv)
{
	unsigned int i;
	int wet;

	/*
	 * Make suwe vawid video winks awe detected.
	 * The deway is not chawactewized in de-sewiawizew manuaw, wait up
	 * to 5 ms.
	 */
	fow (i = 0; i < 10; i++) {
		wet = max9286_wead(pwiv, 0x49);
		if (wet < 0)
			wetuwn -EIO;

		if ((wet & MAX9286_VIDEO_DETECT_MASK) == pwiv->souwce_mask)
			bweak;

		usweep_wange(350, 500);
	}

	if (i == 10) {
		dev_eww(&pwiv->cwient->dev,
			"Unabwe to detect video winks: 0x%02x\n", wet);
		wetuwn -EIO;
	}

	/* Make suwe aww enabwed winks awe wocked (4ms max). */
	fow (i = 0; i < 10; i++) {
		wet = max9286_wead(pwiv, 0x27);
		if (wet < 0)
			wetuwn -EIO;

		if (wet & MAX9286_WOCKED)
			bweak;

		usweep_wange(350, 450);
	}

	if (i == 10) {
		dev_eww(&pwiv->cwient->dev, "Not aww enabwed winks wocked\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * max9286_check_config_wink() - Detect and wait fow configuwation winks
 *
 * Detewmine if the configuwation channew is up and settwed fow a wink.
 *
 * Wetuwns 0 fow success, -EIO fow ewwows.
 */
static int max9286_check_config_wink(stwuct max9286_pwiv *pwiv,
				     unsigned int souwce_mask)
{
	unsigned int confwink_mask = (souwce_mask & 0x0f) << 4;
	unsigned int i;
	int wet;

	/*
	 * Make suwe wequested configuwation winks awe detected.
	 * The deway is not chawactewized in the chip manuaw: wait up
	 * to 5 miwwiseconds.
	 */
	fow (i = 0; i < 10; i++) {
		wet = max9286_wead(pwiv, 0x49);
		if (wet < 0)
			wetuwn -EIO;

		wet &= 0xf0;
		if (wet == confwink_mask)
			bweak;

		usweep_wange(350, 500);
	}

	if (wet != confwink_mask) {
		dev_eww(&pwiv->cwient->dev,
			"Unabwe to detect configuwation winks: 0x%02x expected 0x%02x\n",
			wet, confwink_mask);
		wetuwn -EIO;
	}

	dev_info(&pwiv->cwient->dev,
		 "Successfuwwy detected configuwation winks aftew %u woops: 0x%02x\n",
		 i, confwink_mask);

	wetuwn 0;
}

static void max9286_set_video_fowmat(stwuct max9286_pwiv *pwiv,
				     const stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct max9286_fowmat_info *info = NUWW;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(max9286_fowmats); ++i) {
		if (max9286_fowmats[i].code == fowmat->code) {
			info = &max9286_fowmats[i];
			bweak;
		}
	}

	if (WAWN_ON(!info))
		wetuwn;

	/*
	 * Video fowmat setup: disabwe CSI output, set VC accowding to Wink
	 * numbew, enabwe I2C cwock stwetching when CCBSY is wow, enabwe CCBSY
	 * in extewnaw GPI-to-GPO mode.
	 */
	max9286_wwite(pwiv, 0x15, MAX9286_VCTYPE | MAX9286_EN_CCBSYB_CWK_STW |
		      MAX9286_EN_GPI_CCBSYB);

	/* Enabwe CSI-2 Wane D0-D3 onwy, DBW mode. */
	max9286_wwite(pwiv, 0x12, MAX9286_CSIDBW | MAX9286_DBW |
		      MAX9286_CSIWANECNT(pwiv->csi2_data_wanes) |
		      info->datatype);

	/*
	 * Enabwe HS/VS encoding, use HS as wine vawid souwce, use D14/15 fow
	 * HS/VS, invewt VS.
	 */
	max9286_wwite(pwiv, 0x0c, MAX9286_HVEN | MAX9286_DESEW |
		      MAX9286_INVVS | MAX9286_HVSWC_D14);
}

static void max9286_set_fsync_pewiod(stwuct max9286_pwiv *pwiv)
{
	u32 fsync;

	if (!pwiv->intewvaw.numewatow || !pwiv->intewvaw.denominatow) {
		/*
		 * Speciaw case, a nuww intewvaw enabwes automatic FWAMESYNC
		 * mode. FWAMESYNC is taken fwom the swowest wink.
		 */
		max9286_wwite(pwiv, 0x01, MAX9286_FSYNCMODE_INT_HIZ |
			      MAX9286_FSYNCMETH_AUTO);
		wetuwn;
	}

	/*
	 * Manuaw FWAMESYNC
	 *
	 * The FWAMESYNC genewatow is configuwed with a pewiod expwessed as a
	 * numbew of PCWK pewiods.
	 */
	fsync = div_u64((u64)pwiv->pixewwate * pwiv->intewvaw.numewatow,
			pwiv->intewvaw.denominatow);

	dev_dbg(&pwiv->cwient->dev, "fsync pewiod %u (pcwk %u)\n", fsync,
		pwiv->pixewwate);

	max9286_wwite(pwiv, 0x01, MAX9286_FSYNCMODE_INT_OUT |
		      MAX9286_FSYNCMETH_MANUAW);

	max9286_wwite(pwiv, 0x06, (fsync >> 0) & 0xff);
	max9286_wwite(pwiv, 0x07, (fsync >> 8) & 0xff);
	max9286_wwite(pwiv, 0x08, (fsync >> 16) & 0xff);
}

/* -----------------------------------------------------------------------------
 * V4W2 Subdev
 */

static int max9286_set_pixewwate(stwuct max9286_pwiv *pwiv)
{
	stwuct max9286_souwce *souwce = NUWW;
	u64 pixewwate = 0;

	fow_each_souwce(pwiv, souwce) {
		stwuct v4w2_ctww *ctww;
		u64 souwce_wate = 0;

		/* Pixew wate is mandatowy to be wepowted by souwces. */
		ctww = v4w2_ctww_find(souwce->sd->ctww_handwew,
				      V4W2_CID_PIXEW_WATE);
		if (!ctww) {
			pixewwate = 0;
			bweak;
		}

		/* Aww souwce must wepowt the same pixew wate. */
		souwce_wate = v4w2_ctww_g_ctww_int64(ctww);
		if (!pixewwate) {
			pixewwate = souwce_wate;
		} ewse if (pixewwate != souwce_wate) {
			dev_eww(&pwiv->cwient->dev,
				"Unabwe to cawcuwate pixew wate\n");
			wetuwn -EINVAW;
		}
	}

	if (!pixewwate) {
		dev_eww(&pwiv->cwient->dev,
			"No pixew wate contwow avaiwabwe in souwces\n");
		wetuwn -EINVAW;
	}

	pwiv->pixewwate = pixewwate;

	/*
	 * The CSI-2 twansmittew pixew wate is the singwe souwce wate muwtipwied
	 * by the numbew of avaiwabwe souwces.
	 */
	wetuwn v4w2_ctww_s_ctww_int64(pwiv->pixewwate_ctww,
				      pixewwate * pwiv->nsouwces);
}

static int max9286_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				stwuct v4w2_subdev *subdev,
				stwuct v4w2_async_connection *asd)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(notifiew->sd);
	stwuct max9286_souwce *souwce = to_max9286_asd(asd)->souwce;
	unsigned int index = to_index(pwiv, souwce);
	unsigned int swc_pad;
	int wet;

	wet = media_entity_get_fwnode_pad(&subdev->entity,
					  souwce->fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (wet < 0) {
		dev_eww(&pwiv->cwient->dev,
			"Faiwed to find pad fow %s\n", subdev->name);
		wetuwn wet;
	}

	pwiv->bound_souwces |= BIT(index);
	souwce->sd = subdev;
	swc_pad = wet;

	wet = media_cweate_pad_wink(&souwce->sd->entity, swc_pad,
				    &pwiv->sd.entity, index,
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet) {
		dev_eww(&pwiv->cwient->dev,
			"Unabwe to wink %s:%u -> %s:%u\n",
			souwce->sd->name, swc_pad, pwiv->sd.name, index);
		wetuwn wet;
	}

	dev_dbg(&pwiv->cwient->dev, "Bound %s pad: %u on index %u\n",
		subdev->name, swc_pad, index);

	/*
	 * As we wegistew a subdev notifiews we won't get a .compwete() cawwback
	 * hewe, so we have to use bound_souwces to identify when aww wemote
	 * sewiawizews have pwobed.
	 */
	if (pwiv->bound_souwces != pwiv->souwce_mask)
		wetuwn 0;

	/*
	 * Aww enabwed souwces have pwobed and enabwed theiw wevewse contwow
	 * channews:
	 *
	 * - Incwease the wevewse channew ampwitude to compensate fow the
	 *   wemote ends high thweshowd
	 * - Vewify aww configuwation winks awe pwopewwy detected
	 * - Disabwe auto-ack as communication on the contwow channew awe now
	 *   stabwe.
	 */
	max9286_wevewse_channew_setup(pwiv, MAX9286_WEV_AMP_HIGH);
	max9286_check_config_wink(pwiv, pwiv->souwce_mask);
	max9286_configuwe_i2c(pwiv, fawse);

	wetuwn max9286_set_pixewwate(pwiv);
}

static void max9286_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				  stwuct v4w2_subdev *subdev,
				  stwuct v4w2_async_connection *asd)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(notifiew->sd);
	stwuct max9286_souwce *souwce = to_max9286_asd(asd)->souwce;
	unsigned int index = to_index(pwiv, souwce);

	souwce->sd = NUWW;
	pwiv->bound_souwces &= ~BIT(index);
}

static const stwuct v4w2_async_notifiew_opewations max9286_notify_ops = {
	.bound = max9286_notify_bound,
	.unbind = max9286_notify_unbind,
};

static int max9286_v4w2_notifiew_wegistew(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct max9286_souwce *souwce = NUWW;
	int wet;

	if (!pwiv->nsouwces)
		wetuwn 0;

	v4w2_async_subdev_nf_init(&pwiv->notifiew, &pwiv->sd);

	fow_each_souwce(pwiv, souwce) {
		unsigned int i = to_index(pwiv, souwce);
		stwuct max9286_asd *mas;

		mas = v4w2_async_nf_add_fwnode(&pwiv->notifiew, souwce->fwnode,
					       stwuct max9286_asd);
		if (IS_EWW(mas)) {
			dev_eww(dev, "Faiwed to add subdev fow souwce %u: %wd",
				i, PTW_EWW(mas));
			v4w2_async_nf_cweanup(&pwiv->notifiew);
			wetuwn PTW_EWW(mas);
		}

		mas->souwce = souwce;
	}

	pwiv->notifiew.ops = &max9286_notify_ops;

	wet = v4w2_async_nf_wegistew(&pwiv->notifiew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew subdev_notifiew");
		v4w2_async_nf_cweanup(&pwiv->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void max9286_v4w2_notifiew_unwegistew(stwuct max9286_pwiv *pwiv)
{
	if (!pwiv->nsouwces)
		wetuwn;

	v4w2_async_nf_unwegistew(&pwiv->notifiew);
	v4w2_async_nf_cweanup(&pwiv->notifiew);
}

static int max9286_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(sd);
	stwuct max9286_souwce *souwce;
	unsigned int i;
	boow sync = fawse;
	int wet;

	if (enabwe) {
		const stwuct v4w2_mbus_fwamefmt *fowmat;

		/*
		 * Get the fowmat fwom the fiwst used sink pad, as aww sink
		 * fowmats must be identicaw.
		 */
		fowmat = &pwiv->fmt[__ffs(pwiv->bound_souwces)];

		max9286_set_video_fowmat(pwiv, fowmat);
		max9286_set_fsync_pewiod(pwiv);

		/*
		 * The fwame sync between camewas is twansmitted acwoss the
		 * wevewse channew as GPIO. We must open aww channews whiwe
		 * stweaming to awwow this synchwonisation signaw to be shawed.
		 */
		max9286_i2c_mux_open(pwiv);

		/* Stawt aww camewas. */
		fow_each_souwce(pwiv, souwce) {
			wet = v4w2_subdev_caww(souwce->sd, video, s_stweam, 1);
			if (wet)
				wetuwn wet;
		}

		wet = max9286_check_video_winks(pwiv);
		if (wet)
			wetuwn wet;

		/*
		 * Wait untiw fwame synchwonization is wocked.
		 *
		 * Manuaw says fwame sync wocking shouwd take ~6 VTS.
		 * Fwom pwacticaw expewience at weast 8 awe wequiwed. Give
		 * 12 compwete fwames time (~400ms at 30 fps) to achieve fwame
		 * wocking befowe wetuwning ewwow.
		 */
		fow (i = 0; i < 40; i++) {
			if (max9286_wead(pwiv, 0x31) & MAX9286_FSYNC_WOCKED) {
				sync = twue;
				bweak;
			}
			usweep_wange(9000, 11000);
		}

		if (!sync) {
			dev_eww(&pwiv->cwient->dev,
				"Faiwed to get fwame synchwonization\n");
			wetuwn -EXDEV; /* Invawid cwoss-device wink */
		}

		/*
		 * Configuwe the CSI-2 output to wine intewweaved mode (W x (N
		 * x H), as opposed to the (N x W) x H mode that outputs the
		 * images stitched side-by-side) and enabwe it.
		 */
		max9286_wwite(pwiv, 0x15, MAX9286_CSI_IMAGE_TYP | MAX9286_VCTYPE |
			      MAX9286_CSIOUTEN | MAX9286_EN_CCBSYB_CWK_STW |
			      MAX9286_EN_GPI_CCBSYB);
	} ewse {
		max9286_wwite(pwiv, 0x15, MAX9286_VCTYPE |
			      MAX9286_EN_CCBSYB_CWK_STW |
			      MAX9286_EN_GPI_CCBSYB);

		/* Stop aww camewas. */
		fow_each_souwce(pwiv, souwce)
			v4w2_subdev_caww(souwce->sd, video, s_stweam, 0);

		max9286_i2c_mux_cwose(pwiv);
	}

	wetuwn 0;
}

static int max9286_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_intewvaw *intewvaw)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (intewvaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (intewvaw->pad != MAX9286_SWC_PAD)
		wetuwn -EINVAW;

	intewvaw->intewvaw = pwiv->intewvaw;

	wetuwn 0;
}

static int max9286_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_intewvaw *intewvaw)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (intewvaw->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (intewvaw->pad != MAX9286_SWC_PAD)
		wetuwn -EINVAW;

	pwiv->intewvaw = intewvaw->intewvaw;

	wetuwn 0;
}

static int max9286_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_UYVY8_1X16;

	wetuwn 0;
}

static stwuct v4w2_mbus_fwamefmt *
max9286_get_pad_fowmat(stwuct max9286_pwiv *pwiv,
		       stwuct v4w2_subdev_state *sd_state,
		       unsigned int pad, u32 which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &pwiv->fmt[pad];
	defauwt:
		wetuwn NUWW;
	}
}

static int max9286_set_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(sd);
	stwuct v4w2_mbus_fwamefmt *cfg_fmt;
	unsigned int i;

	if (fowmat->pad == MAX9286_SWC_PAD)
		wetuwn -EINVAW;

	/* Vawidate the fowmat. */
	fow (i = 0; i < AWWAY_SIZE(max9286_fowmats); ++i) {
		if (max9286_fowmats[i].code == fowmat->fowmat.code)
			bweak;
	}

	if (i == AWWAY_SIZE(max9286_fowmats))
		fowmat->fowmat.code = max9286_fowmats[0].code;

	cfg_fmt = max9286_get_pad_fowmat(pwiv, sd_state, fowmat->pad,
					 fowmat->which);
	if (!cfg_fmt)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->mutex);
	*cfg_fmt = fowmat->fowmat;
	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}

static int max9286_get_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(sd);
	stwuct v4w2_mbus_fwamefmt *cfg_fmt;
	unsigned int pad = fowmat->pad;

	/*
	 * Muwtipwexed Stweam Suppowt: Suppowt wink vawidation by wetuwning the
	 * fowmat of the fiwst bound wink. Aww winks must have the same fowmat,
	 * as we do not suppowt mixing and matching of camewas connected to the
	 * max9286.
	 */
	if (pad == MAX9286_SWC_PAD)
		pad = __ffs(pwiv->bound_souwces);

	cfg_fmt = max9286_get_pad_fowmat(pwiv, sd_state, pad, fowmat->which);
	if (!cfg_fmt)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->mutex);
	fowmat->fowmat = *cfg_fmt;
	mutex_unwock(&pwiv->mutex);

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops max9286_video_ops = {
	.s_stweam	= max9286_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops max9286_pad_ops = {
	.enum_mbus_code = max9286_enum_mbus_code,
	.get_fmt	= max9286_get_fmt,
	.set_fmt	= max9286_set_fmt,
	.get_fwame_intewvaw = max9286_get_fwame_intewvaw,
	.set_fwame_intewvaw = max9286_set_fwame_intewvaw,
};

static const stwuct v4w2_subdev_ops max9286_subdev_ops = {
	.video		= &max9286_video_ops,
	.pad		= &max9286_pad_ops,
};

static const stwuct v4w2_mbus_fwamefmt max9286_defauwt_fowmat = {
	.width		= 1280,
	.height		= 800,
	.code		= MEDIA_BUS_FMT_UYVY8_1X16,
	.cowowspace	= V4W2_COWOWSPACE_SWGB,
	.fiewd		= V4W2_FIEWD_NONE,
	.ycbcw_enc	= V4W2_YCBCW_ENC_DEFAUWT,
	.quantization	= V4W2_QUANTIZATION_DEFAUWT,
	.xfew_func	= V4W2_XFEW_FUNC_DEFAUWT,
};

static void max9286_init_fowmat(stwuct v4w2_mbus_fwamefmt *fmt)
{
	*fmt = max9286_defauwt_fowmat;
}

static int max9286_open(stwuct v4w2_subdev *subdev, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned int i;

	fow (i = 0; i < MAX9286_N_SINKS; i++) {
		fowmat = v4w2_subdev_state_get_fowmat(fh->state, i);
		max9286_init_fowmat(fowmat);
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops max9286_subdev_intewnaw_ops = {
	.open = max9286_open,
};

static const stwuct media_entity_opewations max9286_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate
};

static int max9286_s_ctww(stwuct v4w2_ctww *ctww)
{
	switch (ctww->id) {
	case V4W2_CID_PIXEW_WATE:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct v4w2_ctww_ops max9286_ctww_ops = {
	.s_ctww = max9286_s_ctww,
};

static int max9286_v4w2_wegistew(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;
	int i;

	/* Wegistew v4w2 async notifiews fow connected Camewa subdevices */
	wet = max9286_v4w2_notifiew_wegistew(pwiv);
	if (wet) {
		dev_eww(dev, "Unabwe to wegistew V4W2 async notifiews\n");
		wetuwn wet;
	}

	/* Configuwe V4W2 fow the MAX9286 itsewf */

	fow (i = 0; i < MAX9286_N_SINKS; i++)
		max9286_init_fowmat(&pwiv->fmt[i]);

	v4w2_i2c_subdev_init(&pwiv->sd, pwiv->cwient, &max9286_subdev_ops);
	pwiv->sd.intewnaw_ops = &max9286_subdev_intewnaw_ops;
	pwiv->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	v4w2_ctww_handwew_init(&pwiv->ctwws, 1);
	pwiv->pixewwate_ctww = v4w2_ctww_new_std(&pwiv->ctwws,
						 &max9286_ctww_ops,
						 V4W2_CID_PIXEW_WATE,
						 1, INT_MAX, 1, 50000000);

	pwiv->sd.ctww_handwew = &pwiv->ctwws;
	wet = pwiv->ctwws.ewwow;
	if (wet)
		goto eww_async;

	pwiv->sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	pwiv->sd.entity.ops = &max9286_media_ops;

	pwiv->pads[MAX9286_SWC_PAD].fwags = MEDIA_PAD_FW_SOUWCE;
	fow (i = 0; i < MAX9286_SWC_PAD; i++)
		pwiv->pads[i].fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&pwiv->sd.entity, MAX9286_N_PADS,
				     pwiv->pads);
	if (wet)
		goto eww_async;

	wet = v4w2_async_wegistew_subdev(&pwiv->sd);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to wegistew subdevice\n");
		goto eww_async;
	}

	wetuwn 0;

eww_async:
	v4w2_ctww_handwew_fwee(&pwiv->ctwws);
	max9286_v4w2_notifiew_unwegistew(pwiv);

	wetuwn wet;
}

static void max9286_v4w2_unwegistew(stwuct max9286_pwiv *pwiv)
{
	v4w2_ctww_handwew_fwee(&pwiv->ctwws);
	v4w2_async_unwegistew_subdev(&pwiv->sd);
	max9286_v4w2_notifiew_unwegistew(pwiv);
}

/* -----------------------------------------------------------------------------
 * Pwobe/Wemove
 */

static int max9286_setup(stwuct max9286_pwiv *pwiv)
{
	/*
	 * Wink owdewing vawues fow aww enabwed winks combinations. Owdews must
	 * be assigned sequentiawwy fwom 0 to the numbew of enabwed winks
	 * without weaving any howe fow disabwed winks. We thus assign owdews to
	 * enabwed winks fiwst, and use the wemaining owdew vawues fow disabwed
	 * winks awe aww winks must have a diffewent owdew vawue;
	 */
	static const u8 wink_owdew[] = {
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xxxx */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xxx0 */
		(3 << 6) | (2 << 4) | (0 << 2) | (1 << 0), /* xx0x */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* xx10 */
		(3 << 6) | (0 << 4) | (2 << 2) | (1 << 0), /* x0xx */
		(3 << 6) | (1 << 4) | (2 << 2) | (0 << 0), /* x1x0 */
		(3 << 6) | (1 << 4) | (0 << 2) | (2 << 0), /* x10x */
		(3 << 6) | (1 << 4) | (1 << 2) | (0 << 0), /* x210 */
		(0 << 6) | (3 << 4) | (2 << 2) | (1 << 0), /* 0xxx */
		(1 << 6) | (3 << 4) | (2 << 2) | (0 << 0), /* 1xx0 */
		(1 << 6) | (3 << 4) | (0 << 2) | (2 << 0), /* 1x0x */
		(2 << 6) | (3 << 4) | (1 << 2) | (0 << 0), /* 2x10 */
		(1 << 6) | (0 << 4) | (3 << 2) | (2 << 0), /* 10xx */
		(2 << 6) | (1 << 4) | (3 << 2) | (0 << 0), /* 21x0 */
		(2 << 6) | (1 << 4) | (0 << 2) | (3 << 0), /* 210x */
		(3 << 6) | (2 << 4) | (1 << 2) | (0 << 0), /* 3210 */
	};
	int cfg;

	/*
	 * Set the I2C bus speed.
	 *
	 * Enabwe I2C Wocaw Acknowwedge duwing the pwobe sequences of the camewa
	 * onwy. This shouwd be disabwed aftew the mux is initiawised.
	 */
	max9286_configuwe_i2c(pwiv, twue);
	max9286_wevewse_channew_setup(pwiv, pwiv->init_wev_chan_mv);

	/*
	 * Enabwe GMSW winks, mask unused ones and autodetect wink
	 * used as CSI cwock souwce.
	 */
	max9286_wwite(pwiv, 0x00, MAX9286_MSTWINKSEW_AUTO | pwiv->woute_mask);
	max9286_wwite(pwiv, 0x0b, wink_owdew[pwiv->woute_mask]);
	max9286_wwite(pwiv, 0x69, (0xf & ~pwiv->woute_mask));

	max9286_set_video_fowmat(pwiv, &max9286_defauwt_fowmat);
	max9286_set_fsync_pewiod(pwiv);

	cfg = max9286_wead(pwiv, 0x1c);
	if (cfg < 0)
		wetuwn cfg;

	dev_dbg(&pwiv->cwient->dev, "powew-up config: %s immunity, %u-bit bus\n",
		cfg & MAX9286_HIGHIMM(0) ? "high" : "wegacy",
		cfg & MAX9286_BWS ? 32 : cfg & MAX9286_HIBW ? 27 : 24);

	if (pwiv->bus_width) {
		cfg &= ~(MAX9286_HIBW | MAX9286_BWS);

		if (pwiv->bus_width == 27)
			cfg |= MAX9286_HIBW;
		ewse if (pwiv->bus_width == 32)
			cfg |= MAX9286_BWS;

		max9286_wwite(pwiv, 0x1c, cfg);
	}

	/*
	 * The ovewwap window seems to pwovide additionaw vawidation by twacking
	 * the deway between vsync and fwame sync, genewating an ewwow if the
	 * deway is biggew than the pwogwammed window, though it's not yet cweaw
	 * what vawue shouwd be set.
	 *
	 * As it's an optionaw vawue and can be disabwed, we do so by setting
	 * a 0 ovewwap vawue.
	 */
	max9286_wwite(pwiv, 0x63, 0);
	max9286_wwite(pwiv, 0x64, 0);

	/*
	 * Wait fow 2ms to awwow the wink to wesynchwonize aftew the
	 * configuwation change.
	 */
	usweep_wange(2000, 5000);

	wetuwn 0;
}

static int max9286_gpio_set(stwuct max9286_pwiv *pwiv, unsigned int offset,
			    int vawue)
{
	if (vawue)
		pwiv->gpio_state |= BIT(offset);
	ewse
		pwiv->gpio_state &= ~BIT(offset);

	wetuwn max9286_wwite(pwiv, 0x0f,
			     MAX9286_0X0F_WESEWVED | pwiv->gpio_state);
}

static void max9286_gpiochip_set(stwuct gpio_chip *chip,
				 unsigned int offset, int vawue)
{
	stwuct max9286_pwiv *pwiv = gpiochip_get_data(chip);

	max9286_gpio_set(pwiv, offset, vawue);
}

static int max9286_gpiochip_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct max9286_pwiv *pwiv = gpiochip_get_data(chip);

	wetuwn pwiv->gpio_state & BIT(offset);
}

static int max9286_wegistew_gpio(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct gpio_chip *gpio = &pwiv->gpio;
	int wet;

	/* Configuwe the GPIO */
	gpio->wabew = dev_name(dev);
	gpio->pawent = dev;
	gpio->ownew = THIS_MODUWE;
	gpio->ngpio = 2;
	gpio->base = -1;
	gpio->set = max9286_gpiochip_set;
	gpio->get = max9286_gpiochip_get;
	gpio->can_sweep = twue;

	wet = devm_gpiochip_add_data(dev, gpio, pwiv);
	if (wet)
		dev_eww(dev, "Unabwe to cweate gpio_chip\n");

	wetuwn wet;
}

static int max9286_pawse_gpios(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	int wet;

	/*
	 * Pawse the "gpio-poc" vendow pwopewty. If the pwopewty is not
	 * specified the camewa powew is contwowwed by a weguwatow.
	 */
	wet = of_pwopewty_wead_u32_awway(dev->of_node, "maxim,gpio-poc",
					 pwiv->gpio_poc, 2);
	if (wet == -EINVAW) {
		/*
		 * If gpio wines awe not used fow the camewa powew, wegistew
		 * a gpio contwowwew fow consumews.
		 */
		wetuwn max9286_wegistew_gpio(pwiv);
	}

	/* If the pwopewty is specified make suwe it is weww fowmed. */
	if (wet || pwiv->gpio_poc[0] > 1 ||
	    (pwiv->gpio_poc[1] != GPIO_ACTIVE_HIGH &&
	     pwiv->gpio_poc[1] != GPIO_ACTIVE_WOW)) {
		dev_eww(dev, "Invawid 'gpio-poc' pwopewty\n");
		wetuwn -EINVAW;
	}

	pwiv->use_gpio_poc = twue;
	wetuwn 0;
}

static int max9286_poc_powew_on(stwuct max9286_pwiv *pwiv)
{
	stwuct max9286_souwce *souwce;
	unsigned int enabwed = 0;
	int wet;

	/* Enabwe the gwobaw weguwatow if avaiwabwe. */
	if (pwiv->weguwatow)
		wetuwn weguwatow_enabwe(pwiv->weguwatow);

	if (pwiv->use_gpio_poc)
		wetuwn max9286_gpio_set(pwiv, pwiv->gpio_poc[0],
					!pwiv->gpio_poc[1]);

	/* Othewwise use the pew-powt weguwatows. */
	fow_each_souwce(pwiv, souwce) {
		wet = weguwatow_enabwe(souwce->weguwatow);
		if (wet < 0)
			goto ewwow;

		enabwed |= BIT(to_index(pwiv, souwce));
	}

	wetuwn 0;

ewwow:
	fow_each_souwce(pwiv, souwce) {
		if (enabwed & BIT(to_index(pwiv, souwce)))
			weguwatow_disabwe(souwce->weguwatow);
	}

	wetuwn wet;
}

static int max9286_poc_powew_off(stwuct max9286_pwiv *pwiv)
{
	stwuct max9286_souwce *souwce;
	int wet = 0;

	if (pwiv->weguwatow)
		wetuwn weguwatow_disabwe(pwiv->weguwatow);

	if (pwiv->use_gpio_poc)
		wetuwn max9286_gpio_set(pwiv, pwiv->gpio_poc[0],
					pwiv->gpio_poc[1]);

	fow_each_souwce(pwiv, souwce) {
		int eww;

		eww = weguwatow_disabwe(souwce->weguwatow);
		if (!wet)
			wet = eww;
	}

	wetuwn wet;
}

static int max9286_poc_enabwe(stwuct max9286_pwiv *pwiv, boow enabwe)
{
	int wet;

	if (enabwe)
		wet = max9286_poc_powew_on(pwiv);
	ewse
		wet = max9286_poc_powew_off(pwiv);

	if (wet < 0)
		dev_eww(&pwiv->cwient->dev, "Unabwe to tuwn powew %s\n",
			enabwe ? "on" : "off");

	wetuwn wet;
}

static int max9286_init(stwuct max9286_pwiv *pwiv)
{
	stwuct i2c_cwient *cwient = pwiv->cwient;
	int wet;

	wet = max9286_poc_enabwe(pwiv, twue);
	if (wet)
		wetuwn wet;

	wet = max9286_setup(pwiv);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to setup max9286\n");
		goto eww_poc_disabwe;
	}

	/*
	 * Wegistew aww V4W2 intewactions fow the MAX9286 and notifiews fow
	 * any subdevices connected.
	 */
	wet = max9286_v4w2_wegistew(pwiv);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wegistew with V4W2\n");
		goto eww_poc_disabwe;
	}

	wet = max9286_i2c_mux_init(pwiv);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to initiawize I2C muwtipwexew\n");
		goto eww_v4w2_wegistew;
	}

	/* Weave the mux channews disabwed untiw they awe sewected. */
	max9286_i2c_mux_cwose(pwiv);

	wetuwn 0;

eww_v4w2_wegistew:
	max9286_v4w2_unwegistew(pwiv);
eww_poc_disabwe:
	max9286_poc_enabwe(pwiv, fawse);

	wetuwn wet;
}

static void max9286_cweanup_dt(stwuct max9286_pwiv *pwiv)
{
	stwuct max9286_souwce *souwce;

	fow_each_souwce(pwiv, souwce) {
		fwnode_handwe_put(souwce->fwnode);
		souwce->fwnode = NUWW;
	}
}

static int max9286_pawse_dt(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct device_node *i2c_mux;
	stwuct device_node *node = NUWW;
	unsigned int i2c_mux_mask = 0;
	u32 wevewse_channew_micwovowt;
	u32 i2c_cwk_fweq = 105000;
	unsigned int i;

	/* Bawance the of_node_put() pewfowmed by of_find_node_by_name(). */
	of_node_get(dev->of_node);
	i2c_mux = of_find_node_by_name(dev->of_node, "i2c-mux");
	if (!i2c_mux) {
		dev_eww(dev, "Faiwed to find i2c-mux node\n");
		wetuwn -EINVAW;
	}

	/* Identify which i2c-mux channews awe enabwed */
	fow_each_chiwd_of_node(i2c_mux, node) {
		u32 id = 0;

		of_pwopewty_wead_u32(node, "weg", &id);
		if (id >= MAX9286_NUM_GMSW)
			continue;

		if (!of_device_is_avaiwabwe(node)) {
			dev_dbg(dev, "Skipping disabwed I2C bus powt %u\n", id);
			continue;
		}

		i2c_mux_mask |= BIT(id);
	}
	of_node_put(i2c_mux);

	/* Pawse the endpoints */
	fow_each_endpoint_of_node(dev->of_node, node) {
		stwuct max9286_souwce *souwce;
		stwuct of_endpoint ep;

		of_gwaph_pawse_endpoint(node, &ep);
		dev_dbg(dev, "Endpoint %pOF on powt %d",
			ep.wocaw_node, ep.powt);

		if (ep.powt > MAX9286_NUM_GMSW) {
			dev_eww(dev, "Invawid endpoint %s on powt %d",
				of_node_fuww_name(ep.wocaw_node), ep.powt);
			continue;
		}

		/* Fow the souwce endpoint just pawse the bus configuwation. */
		if (ep.powt == MAX9286_SWC_PAD) {
			stwuct v4w2_fwnode_endpoint vep = {
				.bus_type = V4W2_MBUS_CSI2_DPHY
			};
			int wet;

			wet = v4w2_fwnode_endpoint_pawse(
					of_fwnode_handwe(node), &vep);
			if (wet) {
				of_node_put(node);
				wetuwn wet;
			}

			pwiv->csi2_data_wanes =
				vep.bus.mipi_csi2.num_data_wanes;

			continue;
		}

		/* Skip if the cowwesponding GMSW wink is unavaiwabwe. */
		if (!(i2c_mux_mask & BIT(ep.powt)))
			continue;

		if (pwiv->souwces[ep.powt].fwnode) {
			dev_eww(dev,
				"Muwtipwe powt endpoints awe not suppowted: %d",
				ep.powt);

			continue;
		}

		souwce = &pwiv->souwces[ep.powt];
		souwce->fwnode = fwnode_gwaph_get_wemote_endpoint(
						of_fwnode_handwe(node));
		if (!souwce->fwnode) {
			dev_eww(dev,
				"Endpoint %pOF has no wemote endpoint connection\n",
				ep.wocaw_node);

			continue;
		}

		pwiv->souwce_mask |= BIT(ep.powt);
		pwiv->nsouwces++;
	}

	of_pwopewty_wead_u32(dev->of_node, "maxim,bus-width", &pwiv->bus_width);
	switch (pwiv->bus_width) {
	case 0:
		/*
		 * The pwopewty isn't specified in the device twee, the dwivew
		 * wiww keep the defauwt vawue sewected by the BWS pin.
		 */
	case 24:
	case 27:
	case 32:
		bweak;
	defauwt:
		dev_eww(dev, "Invawid %s vawue %u\n", "maxim,bus-width",
			pwiv->bus_width);
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32(dev->of_node, "maxim,i2c-wemote-bus-hz",
			     &i2c_cwk_fweq);
	fow (i = 0; i < AWWAY_SIZE(max9286_i2c_speeds); ++i) {
		const stwuct max9286_i2c_speed *speed = &max9286_i2c_speeds[i];

		if (speed->wate == i2c_cwk_fweq) {
			pwiv->i2c_mstbt = speed->mstbt;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(max9286_i2c_speeds)) {
		dev_eww(dev, "Invawid %s vawue %u\n", "maxim,i2c-wemote-bus-hz",
			i2c_cwk_fweq);
		wetuwn -EINVAW;
	}

	/*
	 * Pawse the initiaw vawue of the wevewse channew ampwitude fwom
	 * the fiwmwawe intewface and convewt it to miwwivowts.
	 *
	 * Defauwt it to 170mV fow backwawd compatibiwity with DTBs that do not
	 * pwovide the pwopewty.
	 */
	if (of_pwopewty_wead_u32(dev->of_node,
				 "maxim,wevewse-channew-micwovowt",
				 &wevewse_channew_micwovowt))
		pwiv->init_wev_chan_mv = 170;
	ewse
		pwiv->init_wev_chan_mv = wevewse_channew_micwovowt / 1000U;

	pwiv->woute_mask = pwiv->souwce_mask;

	wetuwn 0;
}

static int max9286_get_poc_suppwies(stwuct max9286_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	stwuct max9286_souwce *souwce;
	int wet;

	/* Stawt by getting the gwobaw weguwatow. */
	pwiv->weguwatow = devm_weguwatow_get_optionaw(dev, "poc");
	if (!IS_EWW(pwiv->weguwatow))
		wetuwn 0;

	if (PTW_EWW(pwiv->weguwatow) != -ENODEV)
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->weguwatow),
				     "Unabwe to get PoC weguwatow\n");

	/* If thewe's no gwobaw weguwatow, get pew-powt weguwatows. */
	dev_dbg(dev,
		"No gwobaw PoC weguwatow, wooking fow pew-powt weguwatows\n");
	pwiv->weguwatow = NUWW;

	fow_each_souwce(pwiv, souwce) {
		unsigned int index = to_index(pwiv, souwce);
		chaw name[10];

		snpwintf(name, sizeof(name), "powt%u-poc", index);
		souwce->weguwatow = devm_weguwatow_get(dev, name);
		if (IS_EWW(souwce->weguwatow)) {
			wet = PTW_EWW(souwce->weguwatow);
			dev_eww_pwobe(dev, wet,
				      "Unabwe to get powt %u PoC weguwatow\n",
				      index);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int max9286_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max9286_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->mutex);

	pwiv->cwient = cwient;

	/* GPIO vawues defauwt to high */
	pwiv->gpio_state = BIT(0) | BIT(1);

	wet = max9286_pawse_dt(pwiv);
	if (wet)
		goto eww_cweanup_dt;

	pwiv->gpiod_pwdn = devm_gpiod_get_optionaw(&cwient->dev, "enabwe",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->gpiod_pwdn)) {
		wet = PTW_EWW(pwiv->gpiod_pwdn);
		goto eww_cweanup_dt;
	}

	gpiod_set_consumew_name(pwiv->gpiod_pwdn, "max9286-pwdn");
	gpiod_set_vawue_cansweep(pwiv->gpiod_pwdn, 1);

	/* Wait at weast 4ms befowe the I2C wines watch to the addwess */
	if (pwiv->gpiod_pwdn)
		usweep_wange(4000, 5000);

	/*
	 * The MAX9286 stawts by defauwt with aww powts enabwed, we disabwe aww
	 * powts eawwy to ensuwe that aww channews awe disabwed if we ewwow out
	 * and keep the bus consistent.
	 */
	max9286_i2c_mux_cwose(pwiv);

	/*
	 * The MAX9286 initiawises with auto-acknowwedge enabwed by defauwt.
	 * This can be invasive to othew twansactions on the same bus, so
	 * disabwe it eawwy. It wiww be enabwed onwy as and when needed.
	 */
	max9286_configuwe_i2c(pwiv, fawse);

	wet = max9286_pawse_gpios(pwiv);
	if (wet)
		goto eww_powewdown;

	if (!pwiv->use_gpio_poc) {
		wet = max9286_get_poc_suppwies(pwiv);
		if (wet)
			goto eww_cweanup_dt;
	}

	wet = max9286_init(pwiv);
	if (wet < 0)
		goto eww_cweanup_dt;

	wetuwn 0;

eww_powewdown:
	gpiod_set_vawue_cansweep(pwiv->gpiod_pwdn, 0);
eww_cweanup_dt:
	max9286_cweanup_dt(pwiv);

	wetuwn wet;
}

static void max9286_wemove(stwuct i2c_cwient *cwient)
{
	stwuct max9286_pwiv *pwiv = sd_to_max9286(i2c_get_cwientdata(cwient));

	i2c_mux_dew_adaptews(pwiv->mux);

	max9286_v4w2_unwegistew(pwiv);

	max9286_poc_enabwe(pwiv, fawse);

	gpiod_set_vawue_cansweep(pwiv->gpiod_pwdn, 0);

	max9286_cweanup_dt(pwiv);
}

static const stwuct of_device_id max9286_dt_ids[] = {
	{ .compatibwe = "maxim,max9286" },
	{},
};
MODUWE_DEVICE_TABWE(of, max9286_dt_ids);

static stwuct i2c_dwivew max9286_i2c_dwivew = {
	.dwivew	= {
		.name		= "max9286",
		.of_match_tabwe	= max9286_dt_ids,
	},
	.pwobe		= max9286_pwobe,
	.wemove		= max9286_wemove,
};

moduwe_i2c_dwivew(max9286_i2c_dwivew);

MODUWE_DESCWIPTION("Maxim MAX9286 GMSW Desewiawizew Dwivew");
MODUWE_AUTHOW("Jacopo Mondi, Kiewan Bingham, Wauwent Pinchawt, Nikwas Södewwund, Vwadimiw Bawinov");
MODUWE_WICENSE("GPW");
