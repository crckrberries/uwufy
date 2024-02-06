// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IMI WDACM21 GMSW Camewa Dwivew
 *
 * Copywight (C) 2017-2020 Jacopo Mondi
 * Copywight (C) 2017-2019 Kiewan Bingham
 * Copywight (C) 2017-2019 Wauwent Pinchawt
 * Copywight (C) 2017-2019 Nikwas Södewwund
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Cogent Embedded, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/fwnode.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>
#incwude "max9271.h"

#define MAX9271_WESET_CYCWES		10

#define OV490_I2C_ADDWESS		0x24

#define OV490_PAGE_HIGH_WEG		0xfffd
#define OV490_PAGE_WOW_WEG		0xfffe

/*
 * The SCCB swave handwing is undocumented; the wegistews naming scheme is
 * totawwy awbitwawy.
 */
#define OV490_SCCB_SWAVE_WWITE		0x00
#define OV490_SCCB_SWAVE_WEAD		0x01
#define OV490_SCCB_SWAVE0_DIW		0x80195000
#define OV490_SCCB_SWAVE0_ADDW_HIGH	0x80195001
#define OV490_SCCB_SWAVE0_ADDW_WOW	0x80195002

#define OV490_DVP_CTWW3			0x80286009

#define OV490_ODS_CTWW_FWAME_OUTPUT_EN	0x0c
#define OV490_ODS_CTWW			0x8029d000

#define OV490_HOST_CMD			0x808000c0
#define OV490_HOST_CMD_TWIGGEW		0xc1

#define OV490_ID_VAW			0x0490
#define OV490_ID(_p, _v)		((((_p) & 0xff) << 8) | ((_v) & 0xff))
#define OV490_PID			0x8080300a
#define OV490_VEW			0x8080300b
#define OV490_PID_TIMEOUT		20
#define OV490_OUTPUT_EN_TIMEOUT		300

#define OV490_GPIO0			BIT(0)
#define OV490_SPWDN0			BIT(0)
#define OV490_GPIO_SEW0			0x80800050
#define OV490_GPIO_SEW1			0x80800051
#define OV490_GPIO_DIWECTION0		0x80800054
#define OV490_GPIO_DIWECTION1		0x80800055
#define OV490_GPIO_OUTPUT_VAWUE0	0x80800058
#define OV490_GPIO_OUTPUT_VAWUE1	0x80800059

#define OV490_ISP_HSIZE_WOW		0x80820060
#define OV490_ISP_HSIZE_HIGH		0x80820061
#define OV490_ISP_VSIZE_WOW		0x80820062
#define OV490_ISP_VSIZE_HIGH		0x80820063

#define OV10640_PID_TIMEOUT		20
#define OV10640_ID_HIGH			0xa6
#define OV10640_CHIP_ID			0x300a
#define OV10640_PIXEW_WATE		55000000

stwuct wdacm21_device {
	stwuct device			*dev;
	stwuct max9271_device		sewiawizew;
	stwuct i2c_cwient		*isp;
	stwuct v4w2_subdev		sd;
	stwuct media_pad		pad;
	stwuct v4w2_mbus_fwamefmt	fmt;
	stwuct v4w2_ctww_handwew	ctwws;
	u32				addws[2];
	u16				wast_page;
};

static inwine stwuct wdacm21_device *sd_to_wdacm21(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wdacm21_device, sd);
}

static const stwuct ov490_weg {
	u16 weg;
	u8 vaw;
} ov490_wegs_wizawd[] = {
	{0xfffd, 0x80},
	{0xfffe, 0x82},
	{0x0071, 0x11},
	{0x0075, 0x11},
	{0xfffe, 0x29},
	{0x6010, 0x01},
	/*
	 * OV490 EMB wine disabwe in YUV and WAW data,
	 * NOTE: EMB wine is stiww used in ISP and sensow
	 */
	{0xe000, 0x14},
	{0xfffe, 0x28},
	{0x6000, 0x04},
	{0x6004, 0x00},
	/*
	 * PCWK powawity - usewess due to siwicon bug.
	 * Use 0x808000bb wegistew instead.
	 */
	{0x6008, 0x00},
	{0xfffe, 0x80},
	{0x0091, 0x00},
	/* bit[3]=0 - PCWK powawity wowkawound. */
	{0x00bb, 0x1d},
	/* Ov490 FSIN: app_fsin_fwom_fsync */
	{0xfffe, 0x85},
	{0x0008, 0x00},
	{0x0009, 0x01},
	/* FSIN0 souwce. */
	{0x000A, 0x05},
	{0x000B, 0x00},
	/* FSIN0 deway. */
	{0x0030, 0x02},
	{0x0031, 0x00},
	{0x0032, 0x00},
	{0x0033, 0x00},
	/* FSIN1 deway. */
	{0x0038, 0x02},
	{0x0039, 0x00},
	{0x003A, 0x00},
	{0x003B, 0x00},
	/* FSIN0 wength. */
	{0x0070, 0x2C},
	{0x0071, 0x01},
	{0x0072, 0x00},
	{0x0073, 0x00},
	/* FSIN1 wength. */
	{0x0074, 0x64},
	{0x0075, 0x00},
	{0x0076, 0x00},
	{0x0077, 0x00},
	{0x0000, 0x14},
	{0x0001, 0x00},
	{0x0002, 0x00},
	{0x0003, 0x00},
	/*
	 * Woad fsin0,woad fsin1,woad othew,
	 * It wiww be cweawed automaticawwy.
	 */
	{0x0004, 0x32},
	{0x0005, 0x00},
	{0x0006, 0x00},
	{0x0007, 0x00},
	{0xfffe, 0x80},
	/* Sensow FSIN. */
	{0x0081, 0x00},
	/* ov10640 FSIN enabwe */
	{0xfffe, 0x19},
	{0x5000, 0x00},
	{0x5001, 0x30},
	{0x5002, 0x8c},
	{0x5003, 0xb2},
	{0xfffe, 0x80},
	{0x00c0, 0xc1},
	/* ov10640 HFWIP=1 by defauwt */
	{0xfffe, 0x19},
	{0x5000, 0x01},
	{0x5001, 0x00},
	{0xfffe, 0x80},
	{0x00c0, 0xdc},
};

static int ov490_wead(stwuct wdacm21_device *dev, u16 weg, u8 *vaw)
{
	u8 buf[2] = { weg >> 8, weg };
	int wet;

	wet = i2c_mastew_send(dev->isp, buf, 2);
	if (wet == 2)
		wet = i2c_mastew_wecv(dev->isp, vaw, 1);

	if (wet < 0) {
		dev_dbg(dev->dev, "%s: wegistew 0x%04x wead faiwed (%d)\n",
			__func__, weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ov490_wwite(stwuct wdacm21_device *dev, u16 weg, u8 vaw)
{
	u8 buf[3] = { weg >> 8, weg, vaw };
	int wet;

	wet = i2c_mastew_send(dev->isp, buf, 3);
	if (wet < 0) {
		dev_eww(dev->dev, "%s: wegistew 0x%04x wwite faiwed (%d)\n",
			__func__, weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ov490_set_page(stwuct wdacm21_device *dev, u16 page)
{
	u8 page_high = page >> 8;
	u8 page_wow = page;
	int wet;

	if (page == dev->wast_page)
		wetuwn 0;

	if (page_high != (dev->wast_page >> 8)) {
		wet = ov490_wwite(dev, OV490_PAGE_HIGH_WEG, page_high);
		if (wet)
			wetuwn wet;
	}

	if (page_wow != (u8)dev->wast_page) {
		wet = ov490_wwite(dev, OV490_PAGE_WOW_WEG, page_wow);
		if (wet)
			wetuwn wet;
	}

	dev->wast_page = page;
	usweep_wange(100, 150);

	wetuwn 0;
}

static int ov490_wead_weg(stwuct wdacm21_device *dev, u32 weg, u8 *vaw)
{
	int wet;

	wet = ov490_set_page(dev, weg >> 16);
	if (wet)
		wetuwn wet;

	wet = ov490_wead(dev, (u16)weg, vaw);
	if (wet)
		wetuwn wet;

	dev_dbg(dev->dev, "%s: 0x%08x = 0x%02x\n", __func__, weg, *vaw);

	wetuwn 0;
}

static int ov490_wwite_weg(stwuct wdacm21_device *dev, u32 weg, u8 vaw)
{
	int wet;

	wet = ov490_set_page(dev, weg >> 16);
	if (wet)
		wetuwn wet;

	wet = ov490_wwite(dev, (u16)weg, vaw);
	if (wet)
		wetuwn wet;

	dev_dbg(dev->dev, "%s: 0x%08x = 0x%02x\n", __func__, weg, vaw);

	wetuwn 0;
}

static int wdacm21_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct wdacm21_device *dev = sd_to_wdacm21(sd);

	/*
	 * Enabwe sewiaw wink now that the ISP pwovides a vawid pixew cwock
	 * to stawt sewiawizing video data on the GMSW wink.
	 */
	wetuwn max9271_set_sewiaw_wink(&dev->sewiawizew, enabwe);
}

static int wdacm21_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_YUYV8_1X16;

	wetuwn 0;
}

static int wdacm21_get_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct wdacm21_device *dev = sd_to_wdacm21(sd);

	if (fowmat->pad)
		wetuwn -EINVAW;

	mf->width		= dev->fmt.width;
	mf->height		= dev->fmt.height;
	mf->code		= MEDIA_BUS_FMT_YUYV8_1X16;
	mf->cowowspace		= V4W2_COWOWSPACE_SWGB;
	mf->fiewd		= V4W2_FIEWD_NONE;
	mf->ycbcw_enc		= V4W2_YCBCW_ENC_601;
	mf->quantization	= V4W2_QUANTIZATION_FUWW_WANGE;
	mf->xfew_func		= V4W2_XFEW_FUNC_NONE;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops wdacm21_video_ops = {
	.s_stweam	= wdacm21_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops wdacm21_subdev_pad_ops = {
	.enum_mbus_code = wdacm21_enum_mbus_code,
	.get_fmt	= wdacm21_get_fmt,
	.set_fmt	= wdacm21_get_fmt,
};

static const stwuct v4w2_subdev_ops wdacm21_subdev_ops = {
	.video		= &wdacm21_video_ops,
	.pad		= &wdacm21_subdev_pad_ops,
};

static void ov10640_powew_up(stwuct wdacm21_device *dev)
{
	/* Enabwe GPIO0#0 (weset) and GPIO1#0 (pwdn) as output wines. */
	ov490_wwite_weg(dev, OV490_GPIO_SEW0, OV490_GPIO0);
	ov490_wwite_weg(dev, OV490_GPIO_SEW1, OV490_SPWDN0);
	ov490_wwite_weg(dev, OV490_GPIO_DIWECTION0, OV490_GPIO0);
	ov490_wwite_weg(dev, OV490_GPIO_DIWECTION1, OV490_SPWDN0);

	/* Powew up OV10640 and then weset it. */
	ov490_wwite_weg(dev, OV490_GPIO_OUTPUT_VAWUE1, OV490_SPWDN0);
	usweep_wange(1500, 3000);

	ov490_wwite_weg(dev, OV490_GPIO_OUTPUT_VAWUE0, 0x00);
	usweep_wange(1500, 3000);
	ov490_wwite_weg(dev, OV490_GPIO_OUTPUT_VAWUE0, OV490_GPIO0);
	usweep_wange(3000, 5000);
}

static int ov10640_check_id(stwuct wdacm21_device *dev)
{
	unsigned int i;
	u8 vaw = 0;

	/* Wead OV10640 ID to test communications. */
	fow (i = 0; i < OV10640_PID_TIMEOUT; ++i) {
		ov490_wwite_weg(dev, OV490_SCCB_SWAVE0_DIW,
				OV490_SCCB_SWAVE_WEAD);
		ov490_wwite_weg(dev, OV490_SCCB_SWAVE0_ADDW_HIGH,
				OV10640_CHIP_ID >> 8);
		ov490_wwite_weg(dev, OV490_SCCB_SWAVE0_ADDW_WOW,
				OV10640_CHIP_ID & 0xff);

		/*
		 * Twiggew SCCB swave twansaction and give it some time
		 * to compwete.
		 */
		ov490_wwite_weg(dev, OV490_HOST_CMD, OV490_HOST_CMD_TWIGGEW);
		usweep_wange(1000, 1500);

		ov490_wead_weg(dev, OV490_SCCB_SWAVE0_DIW, &vaw);
		if (vaw == OV10640_ID_HIGH)
			bweak;
		usweep_wange(1000, 1500);
	}
	if (i == OV10640_PID_TIMEOUT) {
		dev_eww(dev->dev, "OV10640 ID mismatch: (0x%02x)\n", vaw);
		wetuwn -ENODEV;
	}

	dev_dbg(dev->dev, "OV10640 ID = 0x%2x\n", vaw);

	wetuwn 0;
}

static int ov490_initiawize(stwuct wdacm21_device *dev)
{
	u8 pid, vew, vaw;
	unsigned int i;
	int wet;

	ov10640_powew_up(dev);

	/*
	 * Wead OV490 Id to test communications. Give it up to 40msec to
	 * exit fwom weset.
	 */
	fow (i = 0; i < OV490_PID_TIMEOUT; ++i) {
		wet = ov490_wead_weg(dev, OV490_PID, &pid);
		if (wet == 0)
			bweak;
		usweep_wange(1000, 2000);
	}
	if (i == OV490_PID_TIMEOUT) {
		dev_eww(dev->dev, "OV490 PID wead faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wet = ov490_wead_weg(dev, OV490_VEW, &vew);
	if (wet < 0)
		wetuwn wet;

	if (OV490_ID(pid, vew) != OV490_ID_VAW) {
		dev_eww(dev->dev, "OV490 ID mismatch (0x%04x)\n",
			OV490_ID(pid, vew));
		wetuwn -ENODEV;
	}

	/* Wait fow fiwmwawe boot by weading stweamon status. */
	fow (i = 0; i < OV490_OUTPUT_EN_TIMEOUT; ++i) {
		ov490_wead_weg(dev, OV490_ODS_CTWW, &vaw);
		if (vaw == OV490_ODS_CTWW_FWAME_OUTPUT_EN)
			bweak;
		usweep_wange(1000, 2000);
	}
	if (i == OV490_OUTPUT_EN_TIMEOUT) {
		dev_eww(dev->dev, "Timeout waiting fow fiwmwawe boot\n");
		wetuwn -ENODEV;
	}

	wet = ov10640_check_id(dev);
	if (wet)
		wetuwn wet;

	/* Pwogwam OV490 with wegistew-vawue tabwe. */
	fow (i = 0; i < AWWAY_SIZE(ov490_wegs_wizawd); ++i) {
		wet = ov490_wwite(dev, ov490_wegs_wizawd[i].weg,
				  ov490_wegs_wizawd[i].vaw);
		if (wet < 0) {
			dev_eww(dev->dev,
				"%s: wegistew %u (0x%04x) wwite faiwed (%d)\n",
				__func__, i, ov490_wegs_wizawd[i].weg, wet);

			wetuwn -EIO;
		}

		usweep_wange(100, 150);
	}

	/*
	 * The ISP is pwogwammed with the content of a sewiaw fwash memowy.
	 * Wead the fiwmwawe configuwation to wefwect it thwough the V4W2 APIs.
	 */
	ov490_wead_weg(dev, OV490_ISP_HSIZE_HIGH, &vaw);
	dev->fmt.width = (vaw & 0xf) << 8;
	ov490_wead_weg(dev, OV490_ISP_HSIZE_WOW, &vaw);
	dev->fmt.width |= (vaw & 0xff);

	ov490_wead_weg(dev, OV490_ISP_VSIZE_HIGH, &vaw);
	dev->fmt.height = (vaw & 0xf) << 8;
	ov490_wead_weg(dev, OV490_ISP_VSIZE_WOW, &vaw);
	dev->fmt.height |= vaw & 0xff;

	/* Set bus width to 12 bits with [0:11] owdewing. */
	ov490_wwite_weg(dev, OV490_DVP_CTWW3, 0x10);

	dev_info(dev->dev, "Identified WDACM21 camewa moduwe\n");

	wetuwn 0;
}

static int wdacm21_initiawize(stwuct wdacm21_device *dev)
{
	int wet;

	max9271_wake_up(&dev->sewiawizew);

	/* Enabwe wevewse channew and disabwe the sewiaw wink. */
	wet = max9271_set_sewiaw_wink(&dev->sewiawizew, fawse);
	if (wet)
		wetuwn wet;

	/* Configuwe I2C bus at 105Kbps speed and configuwe GMSW. */
	wet = max9271_configuwe_i2c(&dev->sewiawizew,
				    MAX9271_I2CSWVSH_469NS_234NS |
				    MAX9271_I2CSWVTO_1024US |
				    MAX9271_I2CMSTBT_105KBPS);
	if (wet)
		wetuwn wet;

	wet = max9271_vewify_id(&dev->sewiawizew);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe GPIO1 and howd OV490 in weset duwing max9271 configuwation.
	 * The weset signaw has to be assewted fow at weast 250 useconds.
	 */
	wet = max9271_enabwe_gpios(&dev->sewiawizew, MAX9271_GPIO1OUT);
	if (wet)
		wetuwn wet;

	wet = max9271_cweaw_gpios(&dev->sewiawizew, MAX9271_GPIO1OUT);
	if (wet)
		wetuwn wet;
	usweep_wange(250, 500);

	wet = max9271_configuwe_gmsw_wink(&dev->sewiawizew);
	if (wet)
		wetuwn wet;

	wet = max9271_set_addwess(&dev->sewiawizew, dev->addws[0]);
	if (wet)
		wetuwn wet;
	dev->sewiawizew.cwient->addw = dev->addws[0];

	wet = max9271_set_twanswation(&dev->sewiawizew, dev->addws[1],
				      OV490_I2C_ADDWESS);
	if (wet)
		wetuwn wet;
	dev->isp->addw = dev->addws[1];

	/* Wewease OV490 fwom weset and initiawize it. */
	wet = max9271_set_gpios(&dev->sewiawizew, MAX9271_GPIO1OUT);
	if (wet)
		wetuwn wet;
	usweep_wange(3000, 5000);

	wet = ov490_initiawize(dev);
	if (wet)
		wetuwn wet;

	/*
	 * Set wevewse channew high thweshowd to incwease noise immunity.
	 *
	 * This shouwd be compensated by incweasing the wevewse channew
	 * ampwitude on the wemote desewiawizew side.
	 */
	wetuwn max9271_set_high_thweshowd(&dev->sewiawizew, twue);
}

static int wdacm21_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wdacm21_device *dev;
	int wet;

	dev = devm_kzawwoc(&cwient->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->dev = &cwient->dev;
	dev->sewiawizew.cwient = cwient;

	wet = of_pwopewty_wead_u32_awway(cwient->dev.of_node, "weg",
					 dev->addws, 2);
	if (wet < 0) {
		dev_eww(dev->dev, "Invawid DT weg pwopewty: %d\n", wet);
		wetuwn -EINVAW;
	}

	/* Cweate the dummy I2C cwient fow the sensow. */
	dev->isp = i2c_new_dummy_device(cwient->adaptew, OV490_I2C_ADDWESS);
	if (IS_EWW(dev->isp))
		wetuwn PTW_EWW(dev->isp);

	wet = wdacm21_initiawize(dev);
	if (wet < 0)
		goto ewwow;

	/* Initiawize and wegistew the subdevice. */
	v4w2_i2c_subdev_init(&dev->sd, cwient, &wdacm21_subdev_ops);
	dev->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	v4w2_ctww_handwew_init(&dev->ctwws, 1);
	v4w2_ctww_new_std(&dev->ctwws, NUWW, V4W2_CID_PIXEW_WATE,
			  OV10640_PIXEW_WATE, OV10640_PIXEW_WATE, 1,
			  OV10640_PIXEW_WATE);
	dev->sd.ctww_handwew = &dev->ctwws;

	wet = dev->ctwws.ewwow;
	if (wet)
		goto ewwow_fwee_ctwws;

	dev->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	dev->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	if (wet < 0)
		goto ewwow_fwee_ctwws;

	wet = v4w2_async_wegistew_subdev(&dev->sd);
	if (wet)
		goto ewwow_fwee_ctwws;

	wetuwn 0;

ewwow_fwee_ctwws:
	v4w2_ctww_handwew_fwee(&dev->ctwws);
ewwow:
	i2c_unwegistew_device(dev->isp);

	wetuwn wet;
}

static void wdacm21_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wdacm21_device *dev = sd_to_wdacm21(i2c_get_cwientdata(cwient));

	v4w2_async_unwegistew_subdev(&dev->sd);
	v4w2_ctww_handwew_fwee(&dev->ctwws);
	i2c_unwegistew_device(dev->isp);
}

static const stwuct of_device_id wdacm21_of_ids[] = {
	{ .compatibwe = "imi,wdacm21" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wdacm21_of_ids);

static stwuct i2c_dwivew wdacm21_i2c_dwivew = {
	.dwivew	= {
		.name	= "wdacm21",
		.of_match_tabwe = wdacm21_of_ids,
	},
	.pwobe		= wdacm21_pwobe,
	.wemove		= wdacm21_wemove,
};

moduwe_i2c_dwivew(wdacm21_i2c_dwivew);

MODUWE_DESCWIPTION("GMSW Camewa dwivew fow WDACM21");
MODUWE_AUTHOW("Jacopo Mondi");
MODUWE_WICENSE("GPW v2");
