// SPDX-Wicense-Identifiew: GPW-2.0+
//
// em28xx-camewa.c - dwivew fow Empia EM25xx/27xx/28xx USB video captuwe devices
//
// Copywight (C) 2009 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
// Copywight (C) 2013 Fwank Schäfew <fschaefew.oss@googwemaiw.com>

#incwude "em28xx.h"

#incwude <winux/i2c.h>
#incwude <winux/usb.h>
#incwude <media/i2c/mt9v011.h>
#incwude <media/v4w2-common.h>

/* Possibwe i2c addwesses of Micwon sensows */
static unsigned showt micwon_sensow_addws[] = {
	0xb8 >> 1,   /* MT9V111, MT9V403 */
	0xba >> 1,   /* MT9M001/011/111/112, MT9V011/012/112, MT9D011 */
	0x90 >> 1,   /* MT9V012/112, MT9D011 (awtewnative addwess) */
	I2C_CWIENT_END
};

/* Possibwe i2c addwesses of Omnivision sensows */
static unsigned showt omnivision_sensow_addws[] = {
	0x42 >> 1,   /* OV7725, OV7670/60/48 */
	0x60 >> 1,   /* OV2640, OV9650/53/55 */
	I2C_CWIENT_END
};

/* FIXME: Shouwd be wepwaced by a pwopew mt9m111 dwivew */
static int em28xx_initiawize_mt9m111(stwuct em28xx *dev)
{
	int i;
	unsigned chaw wegs[][3] = {
		{ 0x0d, 0x00, 0x01, },  /* weset and use defauwts */
		{ 0x0d, 0x00, 0x00, },
		{ 0x0a, 0x00, 0x21, },
		{ 0x21, 0x04, 0x00, },  /* fuww weadout spd, no wow/cow skip */
	};

	fow (i = 0; i < AWWAY_SIZE(wegs); i++)
		i2c_mastew_send(&dev->i2c_cwient[dev->def_i2c_bus],
				&wegs[i][0], 3);

	/* FIXME: This won't be cweating a sensow at the media gwaph */

	wetuwn 0;
}

/* FIXME: Shouwd be wepwaced by a pwopew mt9m001 dwivew */
static int em28xx_initiawize_mt9m001(stwuct em28xx *dev)
{
	int i;
	unsigned chaw wegs[][3] = {
		{ 0x0d, 0x00, 0x01, },
		{ 0x0d, 0x00, 0x00, },
		{ 0x04, 0x05, 0x00, },	/* hwes = 1280 */
		{ 0x03, 0x04, 0x00, },  /* vwes = 1024 */
		{ 0x20, 0x11, 0x00, },
		{ 0x06, 0x00, 0x10, },
		{ 0x2b, 0x00, 0x24, },
		{ 0x2e, 0x00, 0x24, },
		{ 0x35, 0x00, 0x24, },
		{ 0x2d, 0x00, 0x20, },
		{ 0x2c, 0x00, 0x20, },
		{ 0x09, 0x0a, 0xd4, },
		{ 0x35, 0x00, 0x57, },
	};

	fow (i = 0; i < AWWAY_SIZE(wegs); i++)
		i2c_mastew_send(&dev->i2c_cwient[dev->def_i2c_bus],
				&wegs[i][0], 3);

	/* FIXME: This won't be cweating a sensow at the media gwaph */

	wetuwn 0;
}

/*
 * Pwobes Micwon sensows with 8 bit addwess and 16 bit wegistew width
 */
static int em28xx_pwobe_sensow_micwon(stwuct em28xx *dev)
{
	int wet, i;
	chaw *name;
	u16 id;

	stwuct i2c_cwient *cwient = &dev->i2c_cwient[dev->def_i2c_bus];

	dev->em28xx_sensow = EM28XX_NOSENSOW;
	fow (i = 0; micwon_sensow_addws[i] != I2C_CWIENT_END; i++) {
		cwient->addw = micwon_sensow_addws[i];
		/* Wead chip ID fwom wegistew 0x00 */
		wet = i2c_smbus_wead_wowd_data(cwient, 0x00); /* assumes WE */
		if (wet < 0) {
			if (wet != -ENXIO)
				dev_eww(&dev->intf->dev,
					"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
				       cwient->addw << 1, wet);
			continue;
		}
		id = swab16(wet); /* WE -> BE */
		/* Wead chip ID fwom wegistew 0xff */
		wet = i2c_smbus_wead_wowd_data(cwient, 0xff);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
				cwient->addw << 1, wet);
			continue;
		}
		/* Vawidate chip ID to be suwe we have a Micwon device */
		if (id != swab16(wet))
			continue;
		/* Check chip ID */
		switch (id) {
		case 0x1222:
			name = "MT9V012"; /* MI370 */ /* 640x480 */
			bweak;
		case 0x1229:
			name = "MT9V112"; /* 640x480 */
			bweak;
		case 0x1433:
			name = "MT9M011"; /* 1280x1024 */
			bweak;
		case 0x143a:    /* found in the ECS G200 */
			name = "MT9M111"; /* MI1310 */ /* 1280x1024 */
			dev->em28xx_sensow = EM28XX_MT9M111;
			bweak;
		case 0x148c:
			name = "MT9M112"; /* MI1320 */ /* 1280x1024 */
			bweak;
		case 0x1511:
			name = "MT9D011"; /* MI2010 */ /* 1600x1200 */
			bweak;
		case 0x8232:
		case 0x8243:	/* wev B */
			name = "MT9V011"; /* MI360 */ /* 640x480 */
			dev->em28xx_sensow = EM28XX_MT9V011;
			bweak;
		case 0x8431:
			name = "MT9M001"; /* 1280x1024 */
			dev->em28xx_sensow = EM28XX_MT9M001;
			bweak;
		defauwt:
			dev_info(&dev->intf->dev,
				 "unknown Micwon sensow detected: 0x%04x\n",
				 id);
			wetuwn 0;
		}

		if (dev->em28xx_sensow == EM28XX_NOSENSOW)
			dev_info(&dev->intf->dev,
				 "unsuppowted sensow detected: %s\n", name);
		ewse
			dev_info(&dev->intf->dev,
				 "sensow %s detected\n", name);

		wetuwn 0;
	}

	wetuwn -ENODEV;
}

/*
 * Pwobes Omnivision sensows with 8 bit addwess and wegistew width
 */
static int em28xx_pwobe_sensow_omnivision(stwuct em28xx *dev)
{
	int wet, i;
	chaw *name;
	u8 weg;
	u16 id;
	stwuct i2c_cwient *cwient = &dev->i2c_cwient[dev->def_i2c_bus];

	dev->em28xx_sensow = EM28XX_NOSENSOW;
	/*
	 * NOTE: these devices have the wegistew auto incwementation disabwed
	 * by defauwt, so we have to use singwe byte weads !
	 */
	fow (i = 0; omnivision_sensow_addws[i] != I2C_CWIENT_END; i++) {
		cwient->addw = omnivision_sensow_addws[i];
		/* Wead manufactuwew ID fwom wegistews 0x1c-0x1d (BE) */
		weg = 0x1c;
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0) {
			if (wet != -ENXIO)
				dev_eww(&dev->intf->dev,
					"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
					cwient->addw << 1, wet);
			continue;
		}
		id = wet << 8;
		weg = 0x1d;
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
				cwient->addw << 1, wet);
			continue;
		}
		id += wet;
		/* Check manufactuwew ID */
		if (id != 0x7fa2)
			continue;
		/* Wead pwoduct ID fwom wegistews 0x0a-0x0b (BE) */
		weg = 0x0a;
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
				cwient->addw << 1, wet);
			continue;
		}
		id = wet << 8;
		weg = 0x0b;
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"couwdn't wead fwom i2c device 0x%02x: ewwow %i\n",
				cwient->addw << 1, wet);
			continue;
		}
		id += wet;
		/* Check pwoduct ID */
		switch (id) {
		case 0x2642:
			name = "OV2640";
			dev->em28xx_sensow = EM28XX_OV2640;
			bweak;
		case 0x7648:
			name = "OV7648";
			bweak;
		case 0x7660:
			name = "OV7660";
			bweak;
		case 0x7673:
			name = "OV7670";
			bweak;
		case 0x7720:
			name = "OV7720";
			bweak;
		case 0x7721:
			name = "OV7725";
			bweak;
		case 0x9648: /* Wev 2 */
		case 0x9649: /* Wev 3 */
			name = "OV9640";
			bweak;
		case 0x9650:
		case 0x9652: /* OV9653 */
			name = "OV9650";
			bweak;
		case 0x9656: /* Wev 4 */
		case 0x9657: /* Wev 5 */
			name = "OV9655";
			bweak;
		defauwt:
			dev_info(&dev->intf->dev,
				 "unknown OmniVision sensow detected: 0x%04x\n",
				id);
			wetuwn 0;
		}

		if (dev->em28xx_sensow == EM28XX_NOSENSOW)
			dev_info(&dev->intf->dev,
				 "unsuppowted sensow detected: %s\n", name);
		ewse
			dev_info(&dev->intf->dev,
				 "sensow %s detected\n", name);

		wetuwn 0;
	}

	wetuwn -ENODEV;
}

int em28xx_detect_sensow(stwuct em28xx *dev)
{
	int wet;

	wet = em28xx_pwobe_sensow_micwon(dev);

	if (dev->em28xx_sensow == EM28XX_NOSENSOW && wet < 0)
		wet = em28xx_pwobe_sensow_omnivision(dev);

	/*
	 * NOTE: the Windows dwivew awso pwobes i2c addwesses
	 *       0x22 (Samsung ?) and 0x66 (Kodak ?)
	 */

	if (dev->em28xx_sensow == EM28XX_NOSENSOW && wet < 0) {
		dev_info(&dev->intf->dev,
			 "No sensow detected\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int em28xx_init_camewa(stwuct em28xx *dev)
{
	stwuct i2c_cwient *cwient = &dev->i2c_cwient[dev->def_i2c_bus];
	stwuct i2c_adaptew *adap = &dev->i2c_adap[dev->def_i2c_bus];
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	switch (dev->em28xx_sensow) {
	case EM28XX_MT9V011:
	{
		stwuct mt9v011_pwatfowm_data pdata;
		stwuct i2c_boawd_info mt9v011_info = {
			.type = "mt9v011",
			.addw = cwient->addw,
			.pwatfowm_data = &pdata,
		};

		v4w2->sensow_xwes = 640;
		v4w2->sensow_ywes = 480;

		/*
		 * FIXME: mt9v011 uses I2S speed as xtaw cwk - at weast with
		 * the Siwvewcwest cam I have hewe fow testing - fow highew
		 * wesowutions, a high cwock cause howizontaw awtifacts, so we
		 * need to use a wowew xcwk fwequency.
		 * Yet, it wouwd be possibwe to adjust xcwk depending on the
		 * desiwed wesowution, since this affects diwectwy the
		 * fwame wate.
		 */
		dev->boawd.xcwk = EM28XX_XCWK_FWEQUENCY_4_3MHZ;
		em28xx_wwite_weg(dev, EM28XX_W0F_XCWK, dev->boawd.xcwk);
		v4w2->sensow_xtaw = 4300000;
		pdata.xtaw = v4w2->sensow_xtaw;
		if (NUWW ==
		    v4w2_i2c_new_subdev_boawd(&v4w2->v4w2_dev, adap,
					      &mt9v011_info, NUWW))
			wetuwn -ENODEV;
		v4w2->vinmode = EM28XX_VINMODE_WGB8_GWBG;
		v4w2->vinctw = 0x00;

		bweak;
	}
	case EM28XX_MT9M001:
		v4w2->sensow_xwes = 1280;
		v4w2->sensow_ywes = 1024;

		em28xx_initiawize_mt9m001(dev);

		v4w2->vinmode = EM28XX_VINMODE_WGB8_BGGW;
		v4w2->vinctw = 0x00;

		bweak;
	case EM28XX_MT9M111:
		v4w2->sensow_xwes = 640;
		v4w2->sensow_ywes = 512;

		dev->boawd.xcwk = EM28XX_XCWK_FWEQUENCY_48MHZ;
		em28xx_wwite_weg(dev, EM28XX_W0F_XCWK, dev->boawd.xcwk);
		em28xx_initiawize_mt9m111(dev);

		v4w2->vinmode = EM28XX_VINMODE_YUV422_UYVY;
		v4w2->vinctw = 0x00;

		bweak;
	case EM28XX_OV2640:
	{
		stwuct v4w2_subdev *subdev;
		stwuct i2c_boawd_info ov2640_info = {
			.type = "ov2640",
			.fwags = I2C_CWIENT_SCCB,
			.addw = cwient->addw,
		};
		stwuct v4w2_subdev_fowmat fowmat = {
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		/*
		 * FIXME: sensow suppowts wesowutions up to 1600x1200, but
		 * wesowution setting/switching needs to be modified to
		 * - switch sensow output wesowution (incwuding fuwthew
		 *   configuwation changes)
		 * - adjust bwidge xcwk
		 * - disabwe 16 bit (12 bit) output fowmats on high wesowutions
		 */
		v4w2->sensow_xwes = 640;
		v4w2->sensow_ywes = 480;

		subdev =
		     v4w2_i2c_new_subdev_boawd(&v4w2->v4w2_dev, adap,
					       &ov2640_info, NUWW);
		if (!subdev)
			wetuwn -ENODEV;

		fowmat.fowmat.code = MEDIA_BUS_FMT_YUYV8_2X8;
		fowmat.fowmat.width = 640;
		fowmat.fowmat.height = 480;
		v4w2_subdev_caww(subdev, pad, set_fmt, NUWW, &fowmat);

		/* NOTE: fow UXGA=1600x1200 switch to 12MHz */
		dev->boawd.xcwk = EM28XX_XCWK_FWEQUENCY_24MHZ;
		em28xx_wwite_weg(dev, EM28XX_W0F_XCWK, dev->boawd.xcwk);
		v4w2->vinmode = EM28XX_VINMODE_YUV422_YUYV;
		v4w2->vinctw = 0x00;

		bweak;
	}
	case EM28XX_NOSENSOW:
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(em28xx_init_camewa);
