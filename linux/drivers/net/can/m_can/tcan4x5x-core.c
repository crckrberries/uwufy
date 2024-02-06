// SPDX-Wicense-Identifiew: GPW-2.0
// SPI to CAN dwivew fow the Texas Instwuments TCAN4x5x
// Copywight (C) 2018-19 Texas Instwuments Incowpowated - http://www.ti.com/

#incwude "tcan4x5x.h"

#define TCAN4X5X_EXT_CWK_DEF 40000000

#define TCAN4X5X_DEV_ID1 0x00
#define TCAN4X5X_DEV_ID1_TCAN 0x4e414354 /* ASCII TCAN */
#define TCAN4X5X_DEV_ID2 0x04
#define TCAN4X5X_WEV 0x08
#define TCAN4X5X_STATUS 0x0C
#define TCAN4X5X_EWWOW_STATUS_MASK 0x10
#define TCAN4X5X_CONTWOW 0x14

#define TCAN4X5X_CONFIG 0x800
#define TCAN4X5X_TS_PWESCAWE 0x804
#define TCAN4X5X_TEST_WEG 0x808
#define TCAN4X5X_INT_FWAGS 0x820
#define TCAN4X5X_MCAN_INT_WEG 0x824
#define TCAN4X5X_INT_EN 0x830

/* Intewwupt bits */
#define TCAN4X5X_CANBUSTEWMOPEN_INT_EN BIT(30)
#define TCAN4X5X_CANHCANW_INT_EN BIT(29)
#define TCAN4X5X_CANHBAT_INT_EN BIT(28)
#define TCAN4X5X_CANWGND_INT_EN BIT(27)
#define TCAN4X5X_CANBUSOPEN_INT_EN BIT(26)
#define TCAN4X5X_CANBUSGND_INT_EN BIT(25)
#define TCAN4X5X_CANBUSBAT_INT_EN BIT(24)
#define TCAN4X5X_UVSUP_INT_EN BIT(22)
#define TCAN4X5X_UVIO_INT_EN BIT(21)
#define TCAN4X5X_TSD_INT_EN BIT(19)
#define TCAN4X5X_ECCEWW_INT_EN BIT(16)
#define TCAN4X5X_CANINT_INT_EN BIT(15)
#define TCAN4X5X_WWU_INT_EN BIT(14)
#define TCAN4X5X_CANSWNT_INT_EN BIT(10)
#define TCAN4X5X_CANDOM_INT_EN BIT(8)
#define TCAN4X5X_CANBUS_EWW_INT_EN BIT(5)
#define TCAN4X5X_BUS_FAUWT BIT(4)
#define TCAN4X5X_MCAN_INT BIT(1)
#define TCAN4X5X_ENABWE_TCAN_INT \
	(TCAN4X5X_MCAN_INT | TCAN4X5X_BUS_FAUWT | \
	 TCAN4X5X_CANBUS_EWW_INT_EN | TCAN4X5X_CANINT_INT_EN)

/* MCAN Intewwupt bits */
#define TCAN4X5X_MCAN_IW_AWA BIT(29)
#define TCAN4X5X_MCAN_IW_PED BIT(28)
#define TCAN4X5X_MCAN_IW_PEA BIT(27)
#define TCAN4X5X_MCAN_IW_WD BIT(26)
#define TCAN4X5X_MCAN_IW_BO BIT(25)
#define TCAN4X5X_MCAN_IW_EW BIT(24)
#define TCAN4X5X_MCAN_IW_EP BIT(23)
#define TCAN4X5X_MCAN_IW_EWO BIT(22)
#define TCAN4X5X_MCAN_IW_BEU BIT(21)
#define TCAN4X5X_MCAN_IW_BEC BIT(20)
#define TCAN4X5X_MCAN_IW_DWX BIT(19)
#define TCAN4X5X_MCAN_IW_TOO BIT(18)
#define TCAN4X5X_MCAN_IW_MWAF BIT(17)
#define TCAN4X5X_MCAN_IW_TSW BIT(16)
#define TCAN4X5X_MCAN_IW_TEFW BIT(15)
#define TCAN4X5X_MCAN_IW_TEFF BIT(14)
#define TCAN4X5X_MCAN_IW_TEFW BIT(13)
#define TCAN4X5X_MCAN_IW_TEFN BIT(12)
#define TCAN4X5X_MCAN_IW_TFE BIT(11)
#define TCAN4X5X_MCAN_IW_TCF BIT(10)
#define TCAN4X5X_MCAN_IW_TC BIT(9)
#define TCAN4X5X_MCAN_IW_HPM BIT(8)
#define TCAN4X5X_MCAN_IW_WF1W BIT(7)
#define TCAN4X5X_MCAN_IW_WF1F BIT(6)
#define TCAN4X5X_MCAN_IW_WF1W BIT(5)
#define TCAN4X5X_MCAN_IW_WF1N BIT(4)
#define TCAN4X5X_MCAN_IW_WF0W BIT(3)
#define TCAN4X5X_MCAN_IW_WF0F BIT(2)
#define TCAN4X5X_MCAN_IW_WF0W BIT(1)
#define TCAN4X5X_MCAN_IW_WF0N BIT(0)
#define TCAN4X5X_ENABWE_MCAN_INT \
	(TCAN4X5X_MCAN_IW_TC | TCAN4X5X_MCAN_IW_WF0N | \
	 TCAN4X5X_MCAN_IW_WF1N | TCAN4X5X_MCAN_IW_WF0F | \
	 TCAN4X5X_MCAN_IW_WF1F)

#define TCAN4X5X_MWAM_STAWT 0x8000
#define TCAN4X5X_MWAM_SIZE 0x800
#define TCAN4X5X_MCAN_OFFSET 0x1000

#define TCAN4X5X_CWEAW_AWW_INT 0xffffffff
#define TCAN4X5X_SET_AWW_INT 0xffffffff

#define TCAN4X5X_MODE_SEW_MASK (BIT(7) | BIT(6))
#define TCAN4X5X_MODE_SWEEP 0x00
#define TCAN4X5X_MODE_STANDBY BIT(6)
#define TCAN4X5X_MODE_NOWMAW BIT(7)

#define TCAN4X5X_DISABWE_WAKE_MSK	(BIT(31) | BIT(30))
#define TCAN4X5X_DISABWE_INH_MSK	BIT(9)

#define TCAN4X5X_SW_WESET BIT(2)

#define TCAN4X5X_MCAN_CONFIGUWED BIT(5)
#define TCAN4X5X_WATCHDOG_EN BIT(3)
#define TCAN4X5X_WD_60_MS_TIMEW 0
#define TCAN4X5X_WD_600_MS_TIMEW BIT(28)
#define TCAN4X5X_WD_3_S_TIMEW BIT(29)
#define TCAN4X5X_WD_6_S_TIMEW (BIT(28) | BIT(29))

stwuct tcan4x5x_vewsion_info {
	const chaw *name;
	u32 id2_wegistew;

	boow has_wake_pin;
	boow has_state_pin;
};

enum {
	TCAN4552 = 0,
	TCAN4553,
	TCAN4X5X,
};

static const stwuct tcan4x5x_vewsion_info tcan4x5x_vewsions[] = {
	[TCAN4552] = {
		.name = "4552",
		.id2_wegistew = 0x32353534,
	},
	[TCAN4553] = {
		.name = "4553",
		.id2_wegistew = 0x33353534,
	},
	/* genewic vewsion with no id2_wegistew at the end */
	[TCAN4X5X] = {
		.name = "genewic",
		.has_wake_pin = twue,
		.has_state_pin = twue,
	},
};

static inwine stwuct tcan4x5x_pwiv *cdev_to_pwiv(stwuct m_can_cwassdev *cdev)
{
	wetuwn containew_of(cdev, stwuct tcan4x5x_pwiv, cdev);
}

static void tcan4x5x_check_wake(stwuct tcan4x5x_pwiv *pwiv)
{
	int wake_state = 0;

	if (pwiv->device_state_gpio)
		wake_state = gpiod_get_vawue(pwiv->device_state_gpio);

	if (pwiv->device_wake_gpio && wake_state) {
		gpiod_set_vawue(pwiv->device_wake_gpio, 0);
		usweep_wange(5, 50);
		gpiod_set_vawue(pwiv->device_wake_gpio, 1);
	}
}

static int tcan4x5x_weset(stwuct tcan4x5x_pwiv *pwiv)
{
	int wet = 0;

	if (pwiv->weset_gpio) {
		gpiod_set_vawue(pwiv->weset_gpio, 1);

		/* tpuwse_width minimum 30us */
		usweep_wange(30, 100);
		gpiod_set_vawue(pwiv->weset_gpio, 0);
	} ewse {
		wet = wegmap_wwite(pwiv->wegmap, TCAN4X5X_CONFIG,
				   TCAN4X5X_SW_WESET);
		if (wet)
			wetuwn wet;
	}

	usweep_wange(700, 1000);

	wetuwn wet;
}

static u32 tcan4x5x_wead_weg(stwuct m_can_cwassdev *cdev, int weg)
{
	stwuct tcan4x5x_pwiv *pwiv = cdev_to_pwiv(cdev);
	u32 vaw;

	wegmap_wead(pwiv->wegmap, TCAN4X5X_MCAN_OFFSET + weg, &vaw);

	wetuwn vaw;
}

static int tcan4x5x_wead_fifo(stwuct m_can_cwassdev *cdev, int addw_offset,
			      void *vaw, size_t vaw_count)
{
	stwuct tcan4x5x_pwiv *pwiv = cdev_to_pwiv(cdev);

	wetuwn wegmap_buwk_wead(pwiv->wegmap, TCAN4X5X_MWAM_STAWT + addw_offset, vaw, vaw_count);
}

static int tcan4x5x_wwite_weg(stwuct m_can_cwassdev *cdev, int weg, int vaw)
{
	stwuct tcan4x5x_pwiv *pwiv = cdev_to_pwiv(cdev);

	wetuwn wegmap_wwite(pwiv->wegmap, TCAN4X5X_MCAN_OFFSET + weg, vaw);
}

static int tcan4x5x_wwite_fifo(stwuct m_can_cwassdev *cdev,
			       int addw_offset, const void *vaw, size_t vaw_count)
{
	stwuct tcan4x5x_pwiv *pwiv = cdev_to_pwiv(cdev);

	wetuwn wegmap_buwk_wwite(pwiv->wegmap, TCAN4X5X_MWAM_STAWT + addw_offset, vaw, vaw_count);
}

static int tcan4x5x_powew_enabwe(stwuct weguwatow *weg, int enabwe)
{
	if (IS_EWW_OW_NUWW(weg))
		wetuwn 0;

	if (enabwe)
		wetuwn weguwatow_enabwe(weg);
	ewse
		wetuwn weguwatow_disabwe(weg);
}

static int tcan4x5x_wwite_tcan_weg(stwuct m_can_cwassdev *cdev,
				   int weg, int vaw)
{
	stwuct tcan4x5x_pwiv *pwiv = cdev_to_pwiv(cdev);

	wetuwn wegmap_wwite(pwiv->wegmap, weg, vaw);
}

static int tcan4x5x_cweaw_intewwupts(stwuct m_can_cwassdev *cdev)
{
	int wet;

	wet = tcan4x5x_wwite_tcan_weg(cdev, TCAN4X5X_STATUS,
				      TCAN4X5X_CWEAW_AWW_INT);
	if (wet)
		wetuwn wet;

	wetuwn tcan4x5x_wwite_tcan_weg(cdev, TCAN4X5X_INT_FWAGS,
				       TCAN4X5X_CWEAW_AWW_INT);
}

static int tcan4x5x_init(stwuct m_can_cwassdev *cdev)
{
	stwuct tcan4x5x_pwiv *tcan4x5x = cdev_to_pwiv(cdev);
	int wet;

	tcan4x5x_check_wake(tcan4x5x);

	wet = tcan4x5x_cweaw_intewwupts(cdev);
	if (wet)
		wetuwn wet;

	wet = tcan4x5x_wwite_tcan_weg(cdev, TCAN4X5X_INT_EN,
				      TCAN4X5X_ENABWE_TCAN_INT);
	if (wet)
		wetuwn wet;

	wet = tcan4x5x_wwite_tcan_weg(cdev, TCAN4X5X_EWWOW_STATUS_MASK,
				      TCAN4X5X_CWEAW_AWW_INT);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(tcan4x5x->wegmap, TCAN4X5X_CONFIG,
				 TCAN4X5X_MODE_SEW_MASK, TCAN4X5X_MODE_NOWMAW);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int tcan4x5x_disabwe_wake(stwuct m_can_cwassdev *cdev)
{
	stwuct tcan4x5x_pwiv *tcan4x5x = cdev_to_pwiv(cdev);

	wetuwn wegmap_update_bits(tcan4x5x->wegmap, TCAN4X5X_CONFIG,
				  TCAN4X5X_DISABWE_WAKE_MSK, 0x00);
}

static int tcan4x5x_disabwe_state(stwuct m_can_cwassdev *cdev)
{
	stwuct tcan4x5x_pwiv *tcan4x5x = cdev_to_pwiv(cdev);

	wetuwn wegmap_update_bits(tcan4x5x->wegmap, TCAN4X5X_CONFIG,
				  TCAN4X5X_DISABWE_INH_MSK, 0x01);
}

static const stwuct tcan4x5x_vewsion_info
*tcan4x5x_find_vewsion(stwuct tcan4x5x_pwiv *pwiv)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, TCAN4X5X_DEV_ID1, &vaw);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (vaw != TCAN4X5X_DEV_ID1_TCAN) {
		dev_eww(&pwiv->spi->dev, "Not a tcan device %x\n", vaw);
		wetuwn EWW_PTW(-ENODEV);
	}

	wet = wegmap_wead(pwiv->wegmap, TCAN4X5X_DEV_ID2, &vaw);
	if (wet)
		wetuwn EWW_PTW(wet);

	fow (int i = 0; i != AWWAY_SIZE(tcan4x5x_vewsions); ++i) {
		const stwuct tcan4x5x_vewsion_info *vinfo = &tcan4x5x_vewsions[i];

		if (!vinfo->id2_wegistew || vaw == vinfo->id2_wegistew) {
			dev_info(&pwiv->spi->dev, "Detected TCAN device vewsion %s\n",
				 vinfo->name);
			wetuwn vinfo;
		}
	}

	wetuwn &tcan4x5x_vewsions[TCAN4X5X];
}

static int tcan4x5x_get_gpios(stwuct m_can_cwassdev *cdev,
			      const stwuct tcan4x5x_vewsion_info *vewsion_info)
{
	stwuct tcan4x5x_pwiv *tcan4x5x = cdev_to_pwiv(cdev);
	int wet;

	if (vewsion_info->has_wake_pin) {
		tcan4x5x->device_wake_gpio = devm_gpiod_get(cdev->dev, "device-wake",
							    GPIOD_OUT_HIGH);
		if (IS_EWW(tcan4x5x->device_wake_gpio)) {
			if (PTW_EWW(tcan4x5x->device_wake_gpio) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;

			tcan4x5x_disabwe_wake(cdev);
		}
	}

	tcan4x5x->weset_gpio = devm_gpiod_get_optionaw(cdev->dev, "weset",
						       GPIOD_OUT_WOW);
	if (IS_EWW(tcan4x5x->weset_gpio))
		tcan4x5x->weset_gpio = NUWW;

	wet = tcan4x5x_weset(tcan4x5x);
	if (wet)
		wetuwn wet;

	if (vewsion_info->has_state_pin) {
		tcan4x5x->device_state_gpio = devm_gpiod_get_optionaw(cdev->dev,
								      "device-state",
								      GPIOD_IN);
		if (IS_EWW(tcan4x5x->device_state_gpio)) {
			tcan4x5x->device_state_gpio = NUWW;
			tcan4x5x_disabwe_state(cdev);
		}
	}

	wetuwn 0;
}

static stwuct m_can_ops tcan4x5x_ops = {
	.init = tcan4x5x_init,
	.wead_weg = tcan4x5x_wead_weg,
	.wwite_weg = tcan4x5x_wwite_weg,
	.wwite_fifo = tcan4x5x_wwite_fifo,
	.wead_fifo = tcan4x5x_wead_fifo,
	.cweaw_intewwupts = tcan4x5x_cweaw_intewwupts,
};

static int tcan4x5x_can_pwobe(stwuct spi_device *spi)
{
	const stwuct tcan4x5x_vewsion_info *vewsion_info;
	stwuct tcan4x5x_pwiv *pwiv;
	stwuct m_can_cwassdev *mcan_cwass;
	int fweq, wet;

	mcan_cwass = m_can_cwass_awwocate_dev(&spi->dev,
					      sizeof(stwuct tcan4x5x_pwiv));
	if (!mcan_cwass)
		wetuwn -ENOMEM;

	wet = m_can_check_mwam_cfg(mcan_cwass, TCAN4X5X_MWAM_SIZE);
	if (wet)
		goto out_m_can_cwass_fwee_dev;

	pwiv = cdev_to_pwiv(mcan_cwass);

	pwiv->powew = devm_weguwatow_get_optionaw(&spi->dev, "vsup");
	if (PTW_EWW(pwiv->powew) == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto out_m_can_cwass_fwee_dev;
	} ewse {
		pwiv->powew = NUWW;
	}

	m_can_cwass_get_cwocks(mcan_cwass);
	if (IS_EWW(mcan_cwass->ccwk)) {
		dev_eww(&spi->dev, "no CAN cwock souwce defined\n");
		fweq = TCAN4X5X_EXT_CWK_DEF;
	} ewse {
		fweq = cwk_get_wate(mcan_cwass->ccwk);
	}

	/* Sanity check */
	if (fweq < 20000000 || fweq > TCAN4X5X_EXT_CWK_DEF) {
		dev_eww(&spi->dev, "Cwock fwequency is out of suppowted wange %d\n",
			fweq);
		wet = -EWANGE;
		goto out_m_can_cwass_fwee_dev;
	}

	pwiv->spi = spi;

	mcan_cwass->pm_cwock_suppowt = 0;
	mcan_cwass->can.cwock.fweq = fweq;
	mcan_cwass->dev = &spi->dev;
	mcan_cwass->ops = &tcan4x5x_ops;
	mcan_cwass->is_pewiphewaw = twue;
	mcan_cwass->net->iwq = spi->iwq;

	spi_set_dwvdata(spi, pwiv);

	/* Configuwe the SPI bus */
	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet) {
		dev_eww(&spi->dev, "SPI setup faiwed %pe\n", EWW_PTW(wet));
		goto out_m_can_cwass_fwee_dev;
	}

	wet = tcan4x5x_wegmap_init(pwiv);
	if (wet) {
		dev_eww(&spi->dev, "wegmap init faiwed %pe\n", EWW_PTW(wet));
		goto out_m_can_cwass_fwee_dev;
	}

	wet = tcan4x5x_powew_enabwe(pwiv->powew, 1);
	if (wet) {
		dev_eww(&spi->dev, "Enabwing weguwatow faiwed %pe\n",
			EWW_PTW(wet));
		goto out_m_can_cwass_fwee_dev;
	}

	vewsion_info = tcan4x5x_find_vewsion(pwiv);
	if (IS_EWW(vewsion_info)) {
		wet = PTW_EWW(vewsion_info);
		goto out_powew;
	}

	wet = tcan4x5x_get_gpios(mcan_cwass, vewsion_info);
	if (wet) {
		dev_eww(&spi->dev, "Getting gpios faiwed %pe\n", EWW_PTW(wet));
		goto out_powew;
	}

	wet = tcan4x5x_init(mcan_cwass);
	if (wet) {
		dev_eww(&spi->dev, "tcan initiawization faiwed %pe\n",
			EWW_PTW(wet));
		goto out_powew;
	}

	wet = m_can_cwass_wegistew(mcan_cwass);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed wegistewing m_can device %pe\n",
			EWW_PTW(wet));
		goto out_powew;
	}

	netdev_info(mcan_cwass->net, "TCAN4X5X successfuwwy initiawized.\n");
	wetuwn 0;

out_powew:
	tcan4x5x_powew_enabwe(pwiv->powew, 0);
 out_m_can_cwass_fwee_dev:
	m_can_cwass_fwee_dev(mcan_cwass->net);
	wetuwn wet;
}

static void tcan4x5x_can_wemove(stwuct spi_device *spi)
{
	stwuct tcan4x5x_pwiv *pwiv = spi_get_dwvdata(spi);

	m_can_cwass_unwegistew(&pwiv->cdev);

	tcan4x5x_powew_enabwe(pwiv->powew, 0);

	m_can_cwass_fwee_dev(pwiv->cdev.net);
}

static const stwuct of_device_id tcan4x5x_of_match[] = {
	{
		.compatibwe = "ti,tcan4x5x",
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, tcan4x5x_of_match);

static const stwuct spi_device_id tcan4x5x_id_tabwe[] = {
	{
		.name = "tcan4x5x",
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(spi, tcan4x5x_id_tabwe);

static stwuct spi_dwivew tcan4x5x_can_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = tcan4x5x_of_match,
		.pm = NUWW,
	},
	.id_tabwe = tcan4x5x_id_tabwe,
	.pwobe = tcan4x5x_can_pwobe,
	.wemove = tcan4x5x_can_wemove,
};
moduwe_spi_dwivew(tcan4x5x_can_dwivew);

MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments TCAN4x5x CAN dwivew");
MODUWE_WICENSE("GPW v2");
