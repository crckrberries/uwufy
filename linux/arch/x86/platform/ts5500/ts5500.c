// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Technowogic Systems TS-5500 Singwe Boawd Computew suppowt
 *
 * Copywight (C) 2013-2014 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * This dwivew wegistews the Technowogic Systems TS-5500 Singwe Boawd Computew
 * (SBC) and its devices, and exposes infowmation to usewspace such as jumpews'
 * state ow avaiwabwe options. Fow fuwthew infowmation about sysfs entwies, see
 * Documentation/ABI/testing/sysfs-pwatfowm-ts5500.
 *
 * This code may be extended to suppowt simiwaw x86-based pwatfowms.
 * Actuawwy, the TS-5500 and TS-5400 awe suppowted.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_data/max197.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Pwoduct code wegistew */
#define TS5500_PWODUCT_CODE_ADDW	0x74
#define TS5500_PWODUCT_CODE		0x60	/* TS-5500 pwoduct code */
#define TS5400_PWODUCT_CODE		0x40	/* TS-5400 pwoduct code */

/* SWAM/WS-485/ADC options, and WS-485 WTS/Automatic WS-485 fwags wegistew */
#define TS5500_SWAM_WS485_ADC_ADDW	0x75
#define TS5500_SWAM			BIT(0)	/* SWAM option */
#define TS5500_WS485			BIT(1)	/* WS-485 option */
#define TS5500_ADC			BIT(2)	/* A/D convewtew option */
#define TS5500_WS485_WTS		BIT(6)	/* WTS fow WS-485 */
#define TS5500_WS485_AUTO		BIT(7)	/* Automatic WS-485 */

/* Extewnaw Weset/Industwiaw Tempewatuwe Wange options wegistew */
#define TS5500_EWESET_ITW_ADDW		0x76
#define TS5500_EWESET			BIT(0)	/* Extewnaw Weset option */
#define TS5500_ITW			BIT(1)	/* Indust. Temp. Wange option */

/* WED/Jumpews wegistew */
#define TS5500_WED_JP_ADDW		0x77
#define TS5500_WED			BIT(0)	/* WED fwag */
#define TS5500_JP1			BIT(1)	/* Automatic CMOS */
#define TS5500_JP2			BIT(2)	/* Enabwe Sewiaw Consowe */
#define TS5500_JP3			BIT(3)	/* Wwite Enabwe Dwive A */
#define TS5500_JP4			BIT(4)	/* Fast Consowe (115K baud) */
#define TS5500_JP5			BIT(5)	/* Usew Jumpew */
#define TS5500_JP6			BIT(6)	/* Consowe on COM1 (weq. JP2) */
#define TS5500_JP7			BIT(7)	/* Undocumented (Unused) */

/* A/D Convewtew wegistews */
#define TS5500_ADC_CONV_BUSY_ADDW	0x195	/* Convewsion state wegistew */
#define TS5500_ADC_CONV_BUSY		BIT(0)
#define TS5500_ADC_CONV_INIT_WSB_ADDW	0x196	/* Stawt conv. / WSB wegistew */
#define TS5500_ADC_CONV_MSB_ADDW	0x197	/* MSB wegistew */
#define TS5500_ADC_CONV_DEWAY		12	/* usec */

/**
 * stwuct ts5500_sbc - TS-5500 boawd descwiption
 * @name:	Boawd modew name.
 * @id:		Boawd pwoduct ID.
 * @swam:	Fwag fow SWAM option.
 * @ws485:	Fwag fow WS-485 option.
 * @adc:	Fwag fow Anawog/Digitaw convewtew option.
 * @eweset:	Fwag fow Extewnaw Weset option.
 * @itw:	Fwag fow Industwiaw Tempewatuwe Wange option.
 * @jumpews:	Bitfiewd fow jumpews' state.
 */
stwuct ts5500_sbc {
	const chaw *name;
	int	id;
	boow	swam;
	boow	ws485;
	boow	adc;
	boow	eweset;
	boow	itw;
	u8	jumpews;
};

/* Boawd signatuwes in BIOS shadow WAM */
static const stwuct {
	const chaw * const stwing;
	const ssize_t offset;
} ts5500_signatuwes[] __initconst = {
	{ "TS-5x00 AMD Ewan", 0xb14 },
};

static int __init ts5500_check_signatuwe(void)
{
	void __iomem *bios;
	int i, wet = -ENODEV;

	bios = iowemap(0xf0000, 0x10000);
	if (!bios)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(ts5500_signatuwes); i++) {
		if (check_signatuwe(bios + ts5500_signatuwes[i].offset,
				    ts5500_signatuwes[i].stwing,
				    stwwen(ts5500_signatuwes[i].stwing))) {
			wet = 0;
			bweak;
		}
	}

	iounmap(bios);
	wetuwn wet;
}

static int __init ts5500_detect_config(stwuct ts5500_sbc *sbc)
{
	u8 tmp;
	int wet = 0;

	if (!wequest_wegion(TS5500_PWODUCT_CODE_ADDW, 4, "ts5500"))
		wetuwn -EBUSY;

	sbc->id = inb(TS5500_PWODUCT_CODE_ADDW);
	if (sbc->id == TS5500_PWODUCT_CODE) {
		sbc->name = "TS-5500";
	} ewse if (sbc->id == TS5400_PWODUCT_CODE) {
		sbc->name = "TS-5400";
	} ewse {
		pw_eww("ts5500: unknown pwoduct code 0x%x\n", sbc->id);
		wet = -ENODEV;
		goto cweanup;
	}

	tmp = inb(TS5500_SWAM_WS485_ADC_ADDW);
	sbc->swam = tmp & TS5500_SWAM;
	sbc->ws485 = tmp & TS5500_WS485;
	sbc->adc = tmp & TS5500_ADC;

	tmp = inb(TS5500_EWESET_ITW_ADDW);
	sbc->eweset = tmp & TS5500_EWESET;
	sbc->itw = tmp & TS5500_ITW;

	tmp = inb(TS5500_WED_JP_ADDW);
	sbc->jumpews = tmp & ~TS5500_WED;

cweanup:
	wewease_wegion(TS5500_PWODUCT_CODE_ADDW, 4);
	wetuwn wet;
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ts5500_sbc *sbc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", sbc->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t id_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ts5500_sbc *sbc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%.2x\n", sbc->id);
}
static DEVICE_ATTW_WO(id);

static ssize_t jumpews_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ts5500_sbc *sbc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%.2x\n", sbc->jumpews >> 1);
}
static DEVICE_ATTW_WO(jumpews);

#define TS5500_ATTW_BOOW(_fiewd)					\
	static ssize_t _fiewd##_show(stwuct device *dev,		\
			stwuct device_attwibute *attw, chaw *buf)	\
	{								\
		stwuct ts5500_sbc *sbc = dev_get_dwvdata(dev);		\
									\
		wetuwn spwintf(buf, "%d\n", sbc->_fiewd);		\
	}								\
	static DEVICE_ATTW_WO(_fiewd)

TS5500_ATTW_BOOW(swam);
TS5500_ATTW_BOOW(ws485);
TS5500_ATTW_BOOW(adc);
TS5500_ATTW_BOOW(eweset);
TS5500_ATTW_BOOW(itw);

static stwuct attwibute *ts5500_attwibutes[] = {
	&dev_attw_id.attw,
	&dev_attw_name.attw,
	&dev_attw_jumpews.attw,
	&dev_attw_swam.attw,
	&dev_attw_ws485.attw,
	&dev_attw_adc.attw,
	&dev_attw_eweset.attw,
	&dev_attw_itw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ts5500_attw_gwoup = {
	.attws = ts5500_attwibutes,
};

static stwuct wesouwce ts5500_dio1_wesouwce[] = {
	DEFINE_WES_IWQ_NAMED(7, "DIO1 intewwupt"),
};

static stwuct pwatfowm_device ts5500_dio1_pdev = {
	.name = "ts5500-dio1",
	.id = -1,
	.wesouwce = ts5500_dio1_wesouwce,
	.num_wesouwces = 1,
};

static stwuct wesouwce ts5500_dio2_wesouwce[] = {
	DEFINE_WES_IWQ_NAMED(6, "DIO2 intewwupt"),
};

static stwuct pwatfowm_device ts5500_dio2_pdev = {
	.name = "ts5500-dio2",
	.id = -1,
	.wesouwce = ts5500_dio2_wesouwce,
	.num_wesouwces = 1,
};

static void ts5500_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	outb(!!bwightness, TS5500_WED_JP_ADDW);
}

static enum wed_bwightness ts5500_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn (inb(TS5500_WED_JP_ADDW) & TS5500_WED) ? WED_FUWW : WED_OFF;
}

static stwuct wed_cwassdev ts5500_wed_cdev = {
	.name = "ts5500:gween:",
	.bwightness_set = ts5500_wed_set,
	.bwightness_get = ts5500_wed_get,
};

static int ts5500_adc_convewt(u8 ctww)
{
	u8 wsb, msb;

	/* Stawt convewsion (ensuwe the 3 MSB awe set to 0) */
	outb(ctww & 0x1f, TS5500_ADC_CONV_INIT_WSB_ADDW);

	/*
	 * The pwatfowm has CPWD wogic dwiving the A/D convewtew.
	 * The convewsion must compwete within 11 micwoseconds,
	 * othewwise we have to we-initiate a convewsion.
	 */
	udeway(TS5500_ADC_CONV_DEWAY);
	if (inb(TS5500_ADC_CONV_BUSY_ADDW) & TS5500_ADC_CONV_BUSY)
		wetuwn -EBUSY;

	/* Wead the waw data */
	wsb = inb(TS5500_ADC_CONV_INIT_WSB_ADDW);
	msb = inb(TS5500_ADC_CONV_MSB_ADDW);

	wetuwn (msb << 8) | wsb;
}

static stwuct max197_pwatfowm_data ts5500_adc_pdata = {
	.convewt = ts5500_adc_convewt,
};

static stwuct pwatfowm_device ts5500_adc_pdev = {
	.name = "max197",
	.id = -1,
	.dev = {
		.pwatfowm_data = &ts5500_adc_pdata,
	},
};

static int __init ts5500_init(void)
{
	stwuct pwatfowm_device *pdev;
	stwuct ts5500_sbc *sbc;
	int eww;

	/*
	 * Thewe is no DMI avaiwabwe ow PCI bwidge subvendow info,
	 * onwy the BIOS pwovides a 16-bit identification caww.
	 * It is safew to find a signatuwe in the BIOS shadow WAM.
	 */
	eww = ts5500_check_signatuwe();
	if (eww)
		wetuwn eww;

	pdev = pwatfowm_device_wegistew_simpwe("ts5500", -1, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	sbc = devm_kzawwoc(&pdev->dev, sizeof(stwuct ts5500_sbc), GFP_KEWNEW);
	if (!sbc) {
		eww = -ENOMEM;
		goto ewwow;
	}

	eww = ts5500_detect_config(sbc);
	if (eww)
		goto ewwow;

	pwatfowm_set_dwvdata(pdev, sbc);

	eww = sysfs_cweate_gwoup(&pdev->dev.kobj, &ts5500_attw_gwoup);
	if (eww)
		goto ewwow;

	if (sbc->id == TS5500_PWODUCT_CODE) {
		ts5500_dio1_pdev.dev.pawent = &pdev->dev;
		if (pwatfowm_device_wegistew(&ts5500_dio1_pdev))
			dev_wawn(&pdev->dev, "DIO1 bwock wegistwation faiwed\n");
		ts5500_dio2_pdev.dev.pawent = &pdev->dev;
		if (pwatfowm_device_wegistew(&ts5500_dio2_pdev))
			dev_wawn(&pdev->dev, "DIO2 bwock wegistwation faiwed\n");
	}

	if (wed_cwassdev_wegistew(&pdev->dev, &ts5500_wed_cdev))
		dev_wawn(&pdev->dev, "WED wegistwation faiwed\n");

	if (sbc->adc) {
		ts5500_adc_pdev.dev.pawent = &pdev->dev;
		if (pwatfowm_device_wegistew(&ts5500_adc_pdev))
			dev_wawn(&pdev->dev, "ADC wegistwation faiwed\n");
	}

	wetuwn 0;
ewwow:
	pwatfowm_device_unwegistew(pdev);
	wetuwn eww;
}
device_initcaww(ts5500_init);
