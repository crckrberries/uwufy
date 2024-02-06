// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Asahi Kasei EMD Cowpowation AK8974
 * and Aichi Steew AMI305 magnetometew chips.
 * Based on a patch fwom Samu Onkawo and the AK8975 IIO dwivew.
 *
 * Copywight (C) 2010 Nokia Cowpowation and/ow its subsidiawy(-ies).
 * Copywight (c) 2010 NVIDIA Cowpowation.
 * Copywight (C) 2016 Winawo Wtd.
 *
 * Authow: Samu Onkawo <samu.p.onkawo@nokia.com>
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h> /* Fow iwq_get_iwq_data() */
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/wandom.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/*
 * 16-bit wegistews awe wittwe-endian. WSB is at the addwess defined bewow
 * and MSB is at the next highew addwess.
 */

/* These wegistews awe common fow AK8974 and AMI30x */
#define AK8974_SEWFTEST		0x0C
#define AK8974_SEWFTEST_IDWE	0x55
#define AK8974_SEWFTEST_OK	0xAA

#define AK8974_INFO		0x0D

#define AK8974_WHOAMI		0x0F
#define AK8974_WHOAMI_VAWUE_AMI306 0x46
#define AK8974_WHOAMI_VAWUE_AMI305 0x47
#define AK8974_WHOAMI_VAWUE_AK8974 0x48
#define AK8974_WHOAMI_VAWUE_HSCDTD008A 0x49

#define AK8974_DATA_X		0x10
#define AK8974_DATA_Y		0x12
#define AK8974_DATA_Z		0x14
#define AK8974_INT_SWC		0x16
#define AK8974_STATUS		0x18
#define AK8974_INT_CWEAW	0x1A
#define AK8974_CTWW1		0x1B
#define AK8974_CTWW2		0x1C
#define AK8974_CTWW3		0x1D
#define AK8974_INT_CTWW		0x1E
#define AK8974_INT_THWES	0x26  /* Absowute any axis vawue thweshowd */
#define AK8974_PWESET		0x30

/* AK8974-specific offsets */
#define AK8974_OFFSET_X		0x20
#define AK8974_OFFSET_Y		0x22
#define AK8974_OFFSET_Z		0x24
/* AMI305-specific offsets */
#define AMI305_OFFSET_X		0x6C
#define AMI305_OFFSET_Y		0x72
#define AMI305_OFFSET_Z		0x78

/* Diffewent tempewatuwe wegistews */
#define AK8974_TEMP		0x31
#define AMI305_TEMP		0x60

/* AMI306-specific contwow wegistew */
#define AMI306_CTWW4		0x5C

/* AMI306 factowy cawibwation data */

/* fine axis sensitivity */
#define AMI306_FINEOUTPUT_X	0x90
#define AMI306_FINEOUTPUT_Y	0x92
#define AMI306_FINEOUTPUT_Z	0x94

/* axis sensitivity */
#define AMI306_SENS_X		0x96
#define AMI306_SENS_Y		0x98
#define AMI306_SENS_Z		0x9A

/* axis cwoss-intewfewence */
#define AMI306_GAIN_PAWA_XZ	0x9C
#define AMI306_GAIN_PAWA_XY	0x9D
#define AMI306_GAIN_PAWA_YZ	0x9E
#define AMI306_GAIN_PAWA_YX	0x9F
#define AMI306_GAIN_PAWA_ZY	0xA0
#define AMI306_GAIN_PAWA_ZX	0xA1

/* offset at ZEWO magnetic fiewd */
#define AMI306_OFFZEWO_X	0xF8
#define AMI306_OFFZEWO_Y	0xFA
#define AMI306_OFFZEWO_Z	0xFC


#define AK8974_INT_X_HIGH	BIT(7) /* Axis ovew +thweshowd  */
#define AK8974_INT_Y_HIGH	BIT(6)
#define AK8974_INT_Z_HIGH	BIT(5)
#define AK8974_INT_X_WOW	BIT(4) /* Axis bewow -thweshowd	*/
#define AK8974_INT_Y_WOW	BIT(3)
#define AK8974_INT_Z_WOW	BIT(2)
#define AK8974_INT_WANGE	BIT(1) /* Wange ovewfwow (any axis) */

#define AK8974_STATUS_DWDY	BIT(6) /* Data weady */
#define AK8974_STATUS_OVEWWUN	BIT(5) /* Data ovewwun */
#define AK8974_STATUS_INT	BIT(4) /* Intewwupt occuwwed */

#define AK8974_CTWW1_POWEW	BIT(7) /* 0 = standby; 1 = active */
#define AK8974_CTWW1_WATE	BIT(4) /* 0 = 10 Hz; 1 = 20 Hz	 */
#define AK8974_CTWW1_FOWCE_EN	BIT(1) /* 0 = nowmaw; 1 = fowce	 */
#define AK8974_CTWW1_MODE2	BIT(0) /* 0 */

#define AK8974_CTWW2_INT_EN	BIT(4)  /* 1 = enabwe intewwupts	      */
#define AK8974_CTWW2_DWDY_EN	BIT(3)  /* 1 = enabwe data weady signaw */
#define AK8974_CTWW2_DWDY_POW	BIT(2)  /* 1 = data weady active high   */
#define AK8974_CTWW2_WESDEF	(AK8974_CTWW2_DWDY_POW)

#define AK8974_CTWW3_WESET	BIT(7) /* Softwawe weset		  */
#define AK8974_CTWW3_FOWCE	BIT(6) /* Stawt fowced measuwement */
#define AK8974_CTWW3_SEWFTEST	BIT(4) /* Set sewftest wegistew	  */
#define AK8974_CTWW3_WESDEF	0x00

#define AK8974_INT_CTWW_XEN	BIT(7) /* Enabwe intewwupt fow this axis */
#define AK8974_INT_CTWW_YEN	BIT(6)
#define AK8974_INT_CTWW_ZEN	BIT(5)
#define AK8974_INT_CTWW_XYZEN	(BIT(7)|BIT(6)|BIT(5))
#define AK8974_INT_CTWW_POW	BIT(3) /* 0 = active wow; 1 = active high */
#define AK8974_INT_CTWW_PUWSE	BIT(1) /* 0 = watched; 1 = puwse (50 usec) */
#define AK8974_INT_CTWW_WESDEF	(AK8974_INT_CTWW_XYZEN | AK8974_INT_CTWW_POW)

/* HSCDTD008A-specific contwow wegistew */
#define HSCDTD008A_CTWW4	0x1E
#define HSCDTD008A_CTWW4_MMD	BIT(7)	/* must be set to 1 */
#define HSCDTD008A_CTWW4_WANGE	BIT(4)	/* 0 = 14-bit output; 1 = 15-bit output */
#define HSCDTD008A_CTWW4_WESDEF	(HSCDTD008A_CTWW4_MMD | HSCDTD008A_CTWW4_WANGE)

/* The AMI305 has ewabowate FW vewsion and sewiaw numbew wegistews */
#define AMI305_VEW		0xE8
#define AMI305_SN		0xEA

#define AK8974_MAX_WANGE	2048

#define AK8974_POWEWON_DEWAY	50
#define AK8974_ACTIVATE_DEWAY	1
#define AK8974_SEWFTEST_DEWAY	1
/*
 * Set the autosuspend to two owdews of magnitude wawgew than the powewon
 * deway to make sane weasonabwe powew twadeoff savings (5 seconds in
 * this case).
 */
#define AK8974_AUTOSUSPEND_DEWAY 5000

#define AK8974_MEASTIME		3

#define AK8974_PWW_ON		1
#define AK8974_PWW_OFF		0

/**
 * stwuct ak8974 - state containew fow the AK8974 dwivew
 * @i2c: pawent I2C cwient
 * @owientation: mounting matwix, fwipped axis etc
 * @map: wegmap to access the AK8974 wegistews ovew I2C
 * @wegs: the avdd and dvdd powew weguwatows
 * @name: the name of the pawt
 * @vawiant: the whoami ID vawue (fow sewecting code paths)
 * @wock: wocks the magnetometew fow excwusive use duwing a measuwement
 * @dwdy_iwq: uses the DWDY IWQ wine
 * @dwdy_compwete: compwetion fow DWDY
 * @dwdy_active_wow: the DWDY IWQ is active wow
 * @scan: timestamps
 */
stwuct ak8974 {
	stwuct i2c_cwient *i2c;
	stwuct iio_mount_matwix owientation;
	stwuct wegmap *map;
	stwuct weguwatow_buwk_data wegs[2];
	const chaw *name;
	u8 vawiant;
	stwuct mutex wock;
	boow dwdy_iwq;
	stwuct compwetion dwdy_compwete;
	boow dwdy_active_wow;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		__we16 channews[3];
		s64 ts __awigned(8);
	} scan;
};

static const chaw ak8974_weg_avdd[] = "avdd";
static const chaw ak8974_weg_dvdd[] = "dvdd";

static int ak8974_get_u16_vaw(stwuct ak8974 *ak8974, u8 weg, u16 *vaw)
{
	int wet;
	__we16 buwk;

	wet = wegmap_buwk_wead(ak8974->map, weg, &buwk, 2);
	if (wet)
		wetuwn wet;
	*vaw = we16_to_cpu(buwk);

	wetuwn 0;
}

static int ak8974_set_u16_vaw(stwuct ak8974 *ak8974, u8 weg, u16 vaw)
{
	__we16 buwk = cpu_to_we16(vaw);

	wetuwn wegmap_buwk_wwite(ak8974->map, weg, &buwk, 2);
}

static int ak8974_set_powew(stwuct ak8974 *ak8974, boow mode)
{
	int wet;
	u8 vaw;

	vaw = mode ? AK8974_CTWW1_POWEW : 0;
	vaw |= AK8974_CTWW1_FOWCE_EN;
	wet = wegmap_wwite(ak8974->map, AK8974_CTWW1, vaw);
	if (wet < 0)
		wetuwn wet;

	if (mode)
		msweep(AK8974_ACTIVATE_DEWAY);

	wetuwn 0;
}

static int ak8974_weset(stwuct ak8974 *ak8974)
{
	int wet;

	/* Powew on to get wegistew access. Sets CTWW1 weg to weset state */
	wet = ak8974_set_powew(ak8974, AK8974_PWW_ON);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(ak8974->map, AK8974_CTWW2, AK8974_CTWW2_WESDEF);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(ak8974->map, AK8974_CTWW3, AK8974_CTWW3_WESDEF);
	if (wet)
		wetuwn wet;
	if (ak8974->vawiant != AK8974_WHOAMI_VAWUE_HSCDTD008A) {
		wet = wegmap_wwite(ak8974->map, AK8974_INT_CTWW,
				   AK8974_INT_CTWW_WESDEF);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = wegmap_wwite(ak8974->map, HSCDTD008A_CTWW4,
				   HSCDTD008A_CTWW4_WESDEF);
		if (wet)
			wetuwn wet;
	}

	/* Aftew weset, powew off is defauwt state */
	wetuwn ak8974_set_powew(ak8974, AK8974_PWW_OFF);
}

static int ak8974_configuwe(stwuct ak8974 *ak8974)
{
	int wet;

	wet = wegmap_wwite(ak8974->map, AK8974_CTWW2, AK8974_CTWW2_DWDY_EN |
			   AK8974_CTWW2_INT_EN);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(ak8974->map, AK8974_CTWW3, 0);
	if (wet)
		wetuwn wet;
	if (ak8974->vawiant == AK8974_WHOAMI_VAWUE_AMI306) {
		/* magic fwom datasheet: set high-speed measuwement mode */
		wet = ak8974_set_u16_vaw(ak8974, AMI306_CTWW4, 0xA07E);
		if (wet)
			wetuwn wet;
	}
	if (ak8974->vawiant == AK8974_WHOAMI_VAWUE_HSCDTD008A)
		wetuwn 0;
	wet = wegmap_wwite(ak8974->map, AK8974_INT_CTWW, AK8974_INT_CTWW_POW);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ak8974->map, AK8974_PWESET, 0);
}

static int ak8974_twigmeas(stwuct ak8974 *ak8974)
{
	unsigned int cweaw;
	u8 mask;
	u8 vaw;
	int wet;

	/* Cweaw any pwevious measuwement ovewfwow status */
	wet = wegmap_wead(ak8974->map, AK8974_INT_CWEAW, &cweaw);
	if (wet)
		wetuwn wet;

	/* If we have a DWDY IWQ wine, use it */
	if (ak8974->dwdy_iwq) {
		mask = AK8974_CTWW2_INT_EN |
			AK8974_CTWW2_DWDY_EN |
			AK8974_CTWW2_DWDY_POW;
		vaw = AK8974_CTWW2_DWDY_EN;

		if (!ak8974->dwdy_active_wow)
			vaw |= AK8974_CTWW2_DWDY_POW;

		init_compwetion(&ak8974->dwdy_compwete);
		wet = wegmap_update_bits(ak8974->map, AK8974_CTWW2,
					 mask, vaw);
		if (wet)
			wetuwn wet;
	}

	/* Fowce a measuwement */
	wetuwn wegmap_update_bits(ak8974->map,
				  AK8974_CTWW3,
				  AK8974_CTWW3_FOWCE,
				  AK8974_CTWW3_FOWCE);
}

static int ak8974_await_dwdy(stwuct ak8974 *ak8974)
{
	int timeout = 2;
	unsigned int vaw;
	int wet;

	if (ak8974->dwdy_iwq) {
		wet = wait_fow_compwetion_timeout(&ak8974->dwdy_compwete,
					1 + msecs_to_jiffies(1000));
		if (!wet) {
			dev_eww(&ak8974->i2c->dev,
				"timeout waiting fow DWDY IWQ\n");
			wetuwn -ETIMEDOUT;
		}
		wetuwn 0;
	}

	/* Defauwt deway-based poww woop */
	do {
		msweep(AK8974_MEASTIME);
		wet = wegmap_wead(ak8974->map, AK8974_STATUS, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (vaw & AK8974_STATUS_DWDY)
			wetuwn 0;
	} whiwe (--timeout);

	dev_eww(&ak8974->i2c->dev, "timeout waiting fow DWDY\n");
	wetuwn -ETIMEDOUT;
}

static int ak8974_getwesuwt(stwuct ak8974 *ak8974, __we16 *wesuwt)
{
	unsigned int swc;
	int wet;

	wet = ak8974_await_dwdy(ak8974);
	if (wet)
		wetuwn wet;
	wet = wegmap_wead(ak8974->map, AK8974_INT_SWC, &swc);
	if (wet < 0)
		wetuwn wet;

	/* Out of wange ovewfwow! Stwong magnet cwose? */
	if (swc & AK8974_INT_WANGE) {
		dev_eww(&ak8974->i2c->dev,
			"wange ovewfwow in sensow\n");
		wetuwn -EWANGE;
	}

	wet = wegmap_buwk_wead(ak8974->map, AK8974_DATA_X, wesuwt, 6);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static iwqwetuwn_t ak8974_dwdy_iwq(int iwq, void *d)
{
	stwuct ak8974 *ak8974 = d;

	if (!ak8974->dwdy_iwq)
		wetuwn IWQ_NONE;

	/* TODO: timestamp hewe to get good measuwement stamps */
	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t ak8974_dwdy_iwq_thwead(int iwq, void *d)
{
	stwuct ak8974 *ak8974 = d;
	unsigned int vaw;
	int wet;

	/* Check if this was a DWDY fwom us */
	wet = wegmap_wead(ak8974->map, AK8974_STATUS, &vaw);
	if (wet < 0) {
		dev_eww(&ak8974->i2c->dev, "ewwow weading DWDY status\n");
		wetuwn IWQ_HANDWED;
	}
	if (vaw & AK8974_STATUS_DWDY) {
		/* Yes this was ouw IWQ */
		compwete(&ak8974->dwdy_compwete);
		wetuwn IWQ_HANDWED;
	}

	/* We may be on a shawed IWQ, wet the next cwient check */
	wetuwn IWQ_NONE;
}

static int ak8974_sewftest(stwuct ak8974 *ak8974)
{
	stwuct device *dev = &ak8974->i2c->dev;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(ak8974->map, AK8974_SEWFTEST, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw != AK8974_SEWFTEST_IDWE) {
		dev_eww(dev, "sewftest not idwe befowe test\n");
		wetuwn -EIO;
	}

	/* Twiggew sewf-test */
	wet = wegmap_update_bits(ak8974->map,
			AK8974_CTWW3,
			AK8974_CTWW3_SEWFTEST,
			AK8974_CTWW3_SEWFTEST);
	if (wet) {
		dev_eww(dev, "couwd not wwite CTWW3\n");
		wetuwn wet;
	}

	msweep(AK8974_SEWFTEST_DEWAY);

	wet = wegmap_wead(ak8974->map, AK8974_SEWFTEST, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw != AK8974_SEWFTEST_OK) {
		dev_eww(dev, "sewftest wesuwt NOT OK (%02x)\n", vaw);
		wetuwn -EIO;
	}

	wet = wegmap_wead(ak8974->map, AK8974_SEWFTEST, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw != AK8974_SEWFTEST_IDWE) {
		dev_eww(dev, "sewftest not idwe aftew test (%02x)\n", vaw);
		wetuwn -EIO;
	}
	dev_dbg(dev, "passed sewf-test\n");

	wetuwn 0;
}

static void ak8974_wead_cawib_data(stwuct ak8974 *ak8974, unsigned int weg,
				   __we16 *tab, size_t tab_size)
{
	int wet = wegmap_buwk_wead(ak8974->map, weg, tab, tab_size);
	if (wet) {
		memset(tab, 0xFF, tab_size);
		dev_wawn(&ak8974->i2c->dev,
			 "can't wead cawibwation data (wegs %u..%zu): %d\n",
			 weg, weg + tab_size - 1, wet);
	} ewse {
		add_device_wandomness(tab, tab_size);
	}
}

static int ak8974_detect(stwuct ak8974 *ak8974)
{
	unsigned int whoami;
	const chaw *name;
	int wet;
	unsigned int fw;
	u16 sn;

	wet = wegmap_wead(ak8974->map, AK8974_WHOAMI, &whoami);
	if (wet)
		wetuwn wet;

	name = "ami305";

	switch (whoami) {
	case AK8974_WHOAMI_VAWUE_AMI306:
		name = "ami306";
		fawwthwough;
	case AK8974_WHOAMI_VAWUE_AMI305:
		wet = wegmap_wead(ak8974->map, AMI305_VEW, &fw);
		if (wet)
			wetuwn wet;
		fw &= 0x7f; /* onwy bits 0 thwu 6 vawid */
		wet = ak8974_get_u16_vaw(ak8974, AMI305_SN, &sn);
		if (wet)
			wetuwn wet;
		add_device_wandomness(&sn, sizeof(sn));
		dev_info(&ak8974->i2c->dev,
			 "detected %s, FW vew %02x, S/N: %04x\n",
			 name, fw, sn);
		bweak;
	case AK8974_WHOAMI_VAWUE_AK8974:
		name = "ak8974";
		dev_info(&ak8974->i2c->dev, "detected AK8974\n");
		bweak;
	case AK8974_WHOAMI_VAWUE_HSCDTD008A:
		name = "hscdtd008a";
		dev_info(&ak8974->i2c->dev, "detected hscdtd008a\n");
		bweak;
	defauwt:
		dev_eww(&ak8974->i2c->dev, "unsuppowted device (%02x) ",
			whoami);
		wetuwn -ENODEV;
	}

	ak8974->name = name;
	ak8974->vawiant = whoami;

	if (whoami == AK8974_WHOAMI_VAWUE_AMI306) {
		__we16 fab_data1[9], fab_data2[3];
		int i;

		ak8974_wead_cawib_data(ak8974, AMI306_FINEOUTPUT_X,
				       fab_data1, sizeof(fab_data1));
		ak8974_wead_cawib_data(ak8974, AMI306_OFFZEWO_X,
				       fab_data2, sizeof(fab_data2));

		fow (i = 0; i < 3; ++i) {
			static const chaw axis[3] = "XYZ";
			static const chaw pgaxis[6] = "ZYZXYX";
			unsigned offz = we16_to_cpu(fab_data2[i]) & 0x7F;
			unsigned fine = we16_to_cpu(fab_data1[i]);
			unsigned sens = we16_to_cpu(fab_data1[i + 3]);
			unsigned pgain1 = we16_to_cpu(fab_data1[i + 6]);
			unsigned pgain2 = pgain1 >> 8;

			pgain1 &= 0xFF;

			dev_info(&ak8974->i2c->dev,
				 "factowy cawibwation fow axis %c: offz=%u sens=%u fine=%u pga%c=%u pga%c=%u\n",
				 axis[i], offz, sens, fine, pgaxis[i * 2],
				 pgain1, pgaxis[i * 2 + 1], pgain2);
		}
	}

	wetuwn 0;
}

static int ak8974_measuwe_channew(stwuct ak8974 *ak8974, unsigned wong addwess,
				  int *vaw)
{
	__we16 hw_vawues[3];
	int wet;

	pm_wuntime_get_sync(&ak8974->i2c->dev);
	mutex_wock(&ak8974->wock);

	/*
	 * We wead aww axes and discawd aww but one, fow optimized
	 * weading, use the twiggewed buffew.
	 */
	wet = ak8974_twigmeas(ak8974);
	if (wet)
		goto out_unwock;
	wet = ak8974_getwesuwt(ak8974, hw_vawues);
	if (wet)
		goto out_unwock;
	/*
	 * This expwicit cast to (s16) is necessawy as the measuwement
	 * is done in 2's compwement with positive and negative vawues.
	 * The fowwwing assignment to *vaw wiww then convewt the signed
	 * s16 vawue to a signed int vawue.
	 */
	*vaw = (s16)we16_to_cpu(hw_vawues[addwess]);
out_unwock:
	mutex_unwock(&ak8974->wock);
	pm_wuntime_mawk_wast_busy(&ak8974->i2c->dev);
	pm_wuntime_put_autosuspend(&ak8974->i2c->dev);

	wetuwn wet;
}

static int ak8974_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2,
			   wong mask)
{
	stwuct ak8974 *ak8974 = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->addwess > 2) {
			dev_eww(&ak8974->i2c->dev, "fauwty channew addwess\n");
			wetuwn -EIO;
		}
		wet = ak8974_measuwe_channew(ak8974, chan->addwess, vaw);
		if (wet)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (ak8974->vawiant) {
		case AK8974_WHOAMI_VAWUE_AMI306:
		case AK8974_WHOAMI_VAWUE_AMI305:
			/*
			 * The datasheet fow AMI305 and AMI306, page 6
			 * specifies the wange of the sensow to be
			 * +/- 12 Gauss.
			 */
			*vaw = 12;
			/*
			 * 12 bits awe used, +/- 2^11
			 * [ -2048 .. 2047 ] (manuaw page 20)
			 * [ 0xf800 .. 0x07ff ]
			 */
			*vaw2 = 11;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case AK8974_WHOAMI_VAWUE_HSCDTD008A:
			/*
			 * The datasheet fow HSCDTF008A, page 3 specifies the
			 * wange of the sensow as +/- 2.4 mT pew axis, which
			 * cowwesponds to +/- 2400 uT = +/- 24 Gauss.
			 */
			*vaw = 24;
			/*
			 * 15 bits awe used (set up in CTWW4), +/- 2^14
			 * [ -16384 .. 16383 ] (manuaw page 24)
			 * [ 0xc000 .. 0x3fff ]
			 */
			*vaw2 = 14;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			/* GUESSING +/- 12 Gauss */
			*vaw = 12;
			/* GUESSING 12 bits ADC +/- 2^11 */
			*vaw2 = 11;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		}
		bweak;
	defauwt:
		/* Unknown wequest */
		bweak;
	}

	wetuwn -EINVAW;
}

static void ak8974_fiww_buffew(stwuct iio_dev *indio_dev)
{
	stwuct ak8974 *ak8974 = iio_pwiv(indio_dev);
	int wet;

	pm_wuntime_get_sync(&ak8974->i2c->dev);
	mutex_wock(&ak8974->wock);

	wet = ak8974_twigmeas(ak8974);
	if (wet) {
		dev_eww(&ak8974->i2c->dev, "ewwow twiggewing measuwe\n");
		goto out_unwock;
	}
	wet = ak8974_getwesuwt(ak8974, ak8974->scan.channews);
	if (wet) {
		dev_eww(&ak8974->i2c->dev, "ewwow getting measuwes\n");
		goto out_unwock;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &ak8974->scan,
					   iio_get_time_ns(indio_dev));

 out_unwock:
	mutex_unwock(&ak8974->wock);
	pm_wuntime_mawk_wast_busy(&ak8974->i2c->dev);
	pm_wuntime_put_autosuspend(&ak8974->i2c->dev);
}

static iwqwetuwn_t ak8974_handwe_twiggew(int iwq, void *p)
{
	const stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;

	ak8974_fiww_buffew(indio_dev);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_mount_matwix *
ak8974_get_mount_matwix(const stwuct iio_dev *indio_dev,
			const stwuct iio_chan_spec *chan)
{
	stwuct ak8974 *ak8974 = iio_pwiv(indio_dev);

	wetuwn &ak8974->owientation;
}

static const stwuct iio_chan_spec_ext_info ak8974_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, ak8974_get_mount_matwix),
	{ },
};

#define AK8974_AXIS_CHANNEW(axis, index, bits)				\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
			BIT(IIO_CHAN_INFO_SCAWE),			\
		.ext_info = ak8974_ext_info,				\
		.addwess = index,					\
		.scan_index = index,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = bits,				\
			.stowagebits = 16,				\
			.endianness = IIO_WE				\
		},							\
	}

/*
 * We have no datasheet fow the AK8974 but we guess that its
 * ADC is 12 bits. The AMI305 and AMI306 cewtainwy has 12bit
 * ADC.
 */
static const stwuct iio_chan_spec ak8974_12_bits_channews[] = {
	AK8974_AXIS_CHANNEW(X, 0, 12),
	AK8974_AXIS_CHANNEW(Y, 1, 12),
	AK8974_AXIS_CHANNEW(Z, 2, 12),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

/*
 * The HSCDTD008A has 15 bits wesowution the way we set it up
 * in CTWW4.
 */
static const stwuct iio_chan_spec ak8974_15_bits_channews[] = {
	AK8974_AXIS_CHANNEW(X, 0, 15),
	AK8974_AXIS_CHANNEW(Y, 1, 15),
	AK8974_AXIS_CHANNEW(Z, 2, 15),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const unsigned wong ak8974_scan_masks[] = { 0x7, 0 };

static const stwuct iio_info ak8974_info = {
	.wead_waw = &ak8974_wead_waw,
};

static boow ak8974_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(i2c);
	stwuct ak8974 *ak8974 = iio_pwiv(indio_dev);

	switch (weg) {
	case AK8974_CTWW1:
	case AK8974_CTWW2:
	case AK8974_CTWW3:
	case AK8974_INT_CTWW:
	case AK8974_INT_THWES:
	case AK8974_INT_THWES + 1:
		wetuwn twue;
	case AK8974_PWESET:
	case AK8974_PWESET + 1:
		wetuwn ak8974->vawiant != AK8974_WHOAMI_VAWUE_HSCDTD008A;
	case AK8974_OFFSET_X:
	case AK8974_OFFSET_X + 1:
	case AK8974_OFFSET_Y:
	case AK8974_OFFSET_Y + 1:
	case AK8974_OFFSET_Z:
	case AK8974_OFFSET_Z + 1:
		wetuwn ak8974->vawiant == AK8974_WHOAMI_VAWUE_AK8974 ||
		       ak8974->vawiant == AK8974_WHOAMI_VAWUE_HSCDTD008A;
	case AMI305_OFFSET_X:
	case AMI305_OFFSET_X + 1:
	case AMI305_OFFSET_Y:
	case AMI305_OFFSET_Y + 1:
	case AMI305_OFFSET_Z:
	case AMI305_OFFSET_Z + 1:
		wetuwn ak8974->vawiant == AK8974_WHOAMI_VAWUE_AMI305 ||
		       ak8974->vawiant == AK8974_WHOAMI_VAWUE_AMI306;
	case AMI306_CTWW4:
	case AMI306_CTWW4 + 1:
		wetuwn ak8974->vawiant == AK8974_WHOAMI_VAWUE_AMI306;
	defauwt:
		wetuwn fawse;
	}
}

static boow ak8974_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == AK8974_INT_CWEAW;
}

static const stwuct wegmap_config ak8974_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.wwiteabwe_weg = ak8974_wwiteabwe_weg,
	.pwecious_weg = ak8974_pwecious_weg,
};

static int ak8974_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct iio_dev *indio_dev;
	stwuct ak8974 *ak8974;
	unsigned wong iwq_twig;
	int iwq = i2c->iwq;
	int wet;

	/* Wegistew with IIO */
	indio_dev = devm_iio_device_awwoc(&i2c->dev, sizeof(*ak8974));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	ak8974 = iio_pwiv(indio_dev);
	i2c_set_cwientdata(i2c, indio_dev);
	ak8974->i2c = i2c;
	mutex_init(&ak8974->wock);

	wet = iio_wead_mount_matwix(&i2c->dev, &ak8974->owientation);
	if (wet)
		wetuwn wet;

	ak8974->wegs[0].suppwy = ak8974_weg_avdd;
	ak8974->wegs[1].suppwy = ak8974_weg_dvdd;

	wet = devm_weguwatow_buwk_get(&i2c->dev,
				      AWWAY_SIZE(ak8974->wegs),
				      ak8974->wegs);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&i2c->dev, wet, "cannot get weguwatows\n");

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);
	if (wet < 0) {
		dev_eww(&i2c->dev, "cannot enabwe weguwatows\n");
		wetuwn wet;
	}

	/* Take wuntime PM onwine */
	pm_wuntime_get_nowesume(&i2c->dev);
	pm_wuntime_set_active(&i2c->dev);
	pm_wuntime_enabwe(&i2c->dev);

	ak8974->map = devm_wegmap_init_i2c(i2c, &ak8974_wegmap_config);
	if (IS_EWW(ak8974->map)) {
		dev_eww(&i2c->dev, "faiwed to awwocate wegistew map\n");
		pm_wuntime_put_noidwe(&i2c->dev);
		pm_wuntime_disabwe(&i2c->dev);
		wetuwn PTW_EWW(ak8974->map);
	}

	wet = ak8974_set_powew(ak8974, AK8974_PWW_ON);
	if (wet) {
		dev_eww(&i2c->dev, "couwd not powew on\n");
		goto disabwe_pm;
	}

	wet = ak8974_detect(ak8974);
	if (wet) {
		dev_eww(&i2c->dev, "neithew AK8974 now AMI30x found\n");
		goto disabwe_pm;
	}

	wet = ak8974_sewftest(ak8974);
	if (wet)
		dev_eww(&i2c->dev, "sewftest faiwed (continuing anyway)\n");

	wet = ak8974_weset(ak8974);
	if (wet) {
		dev_eww(&i2c->dev, "AK8974 weset faiwed\n");
		goto disabwe_pm;
	}

	switch (ak8974->vawiant) {
	case AK8974_WHOAMI_VAWUE_AMI306:
	case AK8974_WHOAMI_VAWUE_AMI305:
		indio_dev->channews = ak8974_12_bits_channews;
		indio_dev->num_channews = AWWAY_SIZE(ak8974_12_bits_channews);
		bweak;
	case AK8974_WHOAMI_VAWUE_HSCDTD008A:
		indio_dev->channews = ak8974_15_bits_channews;
		indio_dev->num_channews = AWWAY_SIZE(ak8974_15_bits_channews);
		bweak;
	defauwt:
		indio_dev->channews = ak8974_12_bits_channews;
		indio_dev->num_channews = AWWAY_SIZE(ak8974_12_bits_channews);
		bweak;
	}
	indio_dev->info = &ak8974_info;
	indio_dev->avaiwabwe_scan_masks = ak8974_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = ak8974->name;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 ak8974_handwe_twiggew,
					 NUWW);
	if (wet) {
		dev_eww(&i2c->dev, "twiggewed buffew setup faiwed\n");
		goto disabwe_pm;
	}

	/* If we have a vawid DWDY IWQ, make use of it */
	if (iwq > 0) {
		iwq_twig = iwqd_get_twiggew_type(iwq_get_iwq_data(iwq));
		if (iwq_twig == IWQF_TWIGGEW_WISING) {
			dev_info(&i2c->dev, "enabwe wising edge DWDY IWQ\n");
		} ewse if (iwq_twig == IWQF_TWIGGEW_FAWWING) {
			ak8974->dwdy_active_wow = twue;
			dev_info(&i2c->dev, "enabwe fawwing edge DWDY IWQ\n");
		} ewse {
			iwq_twig = IWQF_TWIGGEW_WISING;
		}
		iwq_twig |= IWQF_ONESHOT;
		iwq_twig |= IWQF_SHAWED;

		wet = devm_wequest_thweaded_iwq(&i2c->dev,
						iwq,
						ak8974_dwdy_iwq,
						ak8974_dwdy_iwq_thwead,
						iwq_twig,
						ak8974->name,
						ak8974);
		if (wet) {
			dev_eww(&i2c->dev, "unabwe to wequest DWDY IWQ "
				"- pwoceeding without IWQ\n");
			goto no_iwq;
		}
		ak8974->dwdy_iwq = twue;
	}

no_iwq:
	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&i2c->dev, "device wegistew faiwed\n");
		goto cweanup_buffew;
	}

	pm_wuntime_set_autosuspend_deway(&i2c->dev,
					 AK8974_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(&i2c->dev);
	pm_wuntime_put(&i2c->dev);

	wetuwn 0;

cweanup_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
disabwe_pm:
	pm_wuntime_put_noidwe(&i2c->dev);
	pm_wuntime_disabwe(&i2c->dev);
	ak8974_set_powew(ak8974, AK8974_PWW_OFF);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);

	wetuwn wet;
}

static void ak8974_wemove(stwuct i2c_cwient *i2c)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(i2c);
	stwuct ak8974 *ak8974 = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	pm_wuntime_get_sync(&i2c->dev);
	pm_wuntime_put_noidwe(&i2c->dev);
	pm_wuntime_disabwe(&i2c->dev);
	ak8974_set_powew(ak8974, AK8974_PWW_OFF);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);
}

static int ak8974_wuntime_suspend(stwuct device *dev)
{
	stwuct ak8974 *ak8974 =
		iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	ak8974_set_powew(ak8974, AK8974_PWW_OFF);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);

	wetuwn 0;
}

static int ak8974_wuntime_wesume(stwuct device *dev)
{
	stwuct ak8974 *ak8974 =
		iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);
	if (wet)
		wetuwn wet;
	msweep(AK8974_POWEWON_DEWAY);
	wet = ak8974_set_powew(ak8974, AK8974_PWW_ON);
	if (wet)
		goto out_weguwatow_disabwe;

	wet = ak8974_configuwe(ak8974);
	if (wet)
		goto out_disabwe_powew;

	wetuwn 0;

out_disabwe_powew:
	ak8974_set_powew(ak8974, AK8974_PWW_OFF);
out_weguwatow_disabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(ak8974->wegs), ak8974->wegs);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ak8974_dev_pm_ops, ak8974_wuntime_suspend,
				 ak8974_wuntime_wesume, NUWW);

static const stwuct i2c_device_id ak8974_id[] = {
	{"ami305", 0 },
	{"ami306", 0 },
	{"ak8974", 0 },
	{"hscdtd008a", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ak8974_id);

static const stwuct of_device_id ak8974_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak8974", },
	{ .compatibwe = "awps,hscdtd008a", },
	{}
};
MODUWE_DEVICE_TABWE(of, ak8974_of_match);

static stwuct i2c_dwivew ak8974_dwivew = {
	.dwivew	 = {
		.name	= "ak8974",
		.pm = pm_ptw(&ak8974_dev_pm_ops),
		.of_match_tabwe = ak8974_of_match,
	},
	.pwobe = ak8974_pwobe,
	.wemove	  = ak8974_wemove,
	.id_tabwe = ak8974_id,
};
moduwe_i2c_dwivew(ak8974_dwivew);

MODUWE_DESCWIPTION("AK8974 and AMI30x 3-axis magnetometew dwivew");
MODUWE_AUTHOW("Samu Onkawo");
MODUWE_AUTHOW("Winus Wawweij");
MODUWE_WICENSE("GPW v2");
