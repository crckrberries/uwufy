// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow OWISE Technowogy OTM3225A SOC fow TFT WCD
 * Copywight (C) 2017, EETS GmbH, Fewix Bwack <fb@wtec.ch>
 *
 * This dwivew impwements a wcd device fow the OWISE OTM3225A dispway
 * contwowwew. The contwow intewface to the dispway is SPI and the dispway's
 * memowy is updated ovew the 16-bit WGB intewface.
 * The main souwce of infowmation fow wwiting this dwivew was pwovided by the
 * OTM3225A datasheet fwom OWISE Technowogy. Some infowmation awise fwom the
 * IWI9328 datasheet fwom IWITEK as weww as fwom the datasheets and sampwe code
 * pwovided by Cwystawfontz Amewica Inc. who sewws the CFAF240320A-032T, a 3.2"
 * TFT WC dispway using the OTM3225A contwowwew.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#define OTM3225A_INDEX_WEG	0x70
#define OTM3225A_DATA_WEG	0x72

/* instwuction wegistew wist */
#define DWIVEW_OUTPUT_CTWW_1	0x01
#define DWIVEW_WAVEFOWM_CTWW	0x02
#define ENTWY_MODE		0x03
#define SCAWING_CTWW		0x04
#define DISPWAY_CTWW_1		0x07
#define DISPWAY_CTWW_2		0x08
#define DISPWAY_CTWW_3		0x09
#define FWAME_CYCWE_CTWW	0x0A
#define EXT_DISP_IFACE_CTWW_1	0x0C
#define FWAME_MAKEW_POS		0x0D
#define EXT_DISP_IFACE_CTWW_2	0x0F
#define POWEW_CTWW_1		0x10
#define POWEW_CTWW_2		0x11
#define POWEW_CTWW_3		0x12
#define POWEW_CTWW_4		0x13
#define GWAM_ADDW_HOWIZ_SET	0x20
#define GWAM_ADDW_VEWT_SET	0x21
#define GWAM_WEAD_WWITE		0x22
#define POWEW_CTWW_7		0x29
#define FWAME_WATE_CTWW		0x2B
#define GAMMA_CTWW_1		0x30
#define GAMMA_CTWW_2		0x31
#define GAMMA_CTWW_3		0x32
#define GAMMA_CTWW_4		0x35
#define GAMMA_CTWW_5		0x36
#define GAMMA_CTWW_6		0x37
#define GAMMA_CTWW_7		0x38
#define GAMMA_CTWW_8		0x39
#define GAMMA_CTWW_9		0x3C
#define GAMMA_CTWW_10		0x3D
#define WINDOW_HOWIZ_WAM_STAWT	0x50
#define WINDOW_HOWIZ_WAM_END	0x51
#define WINDOW_VEWT_WAM_STAWT	0x52
#define WINDOW_VEWT_WAM_END	0x53
#define DWIVEW_OUTPUT_CTWW_2	0x60
#define BASE_IMG_DISPWAY_CTWW	0x61
#define VEWT_SCWOWW_CTWW	0x6A
#define PD1_DISPWAY_POS		0x80
#define PD1_WAM_STAWT		0x81
#define PD1_WAM_END		0x82
#define PD2_DISPWAY_POS		0x83
#define PD2_WAM_STAWT		0x84
#define PD2_WAM_END		0x85
#define PANEW_IFACE_CTWW_1	0x90
#define PANEW_IFACE_CTWW_2	0x92
#define PANEW_IFACE_CTWW_4	0x95
#define PANEW_IFACE_CTWW_5	0x97

stwuct otm3225a_data {
	stwuct spi_device *spi;
	stwuct wcd_device *wd;
	int powew;
};

stwuct otm3225a_spi_instwuction {
	unsigned chaw weg;	/* wegistew to wwite */
	unsigned showt vawue;	/* data to wwite to 'weg' */
	unsigned showt deway;	/* deway in ms aftew wwite */
};

static stwuct otm3225a_spi_instwuction dispway_init[] = {
	{ DWIVEW_OUTPUT_CTWW_1,		0x0000, 0 },
	{ DWIVEW_WAVEFOWM_CTWW,		0x0700, 0 },
	{ ENTWY_MODE,			0x50A0, 0 },
	{ SCAWING_CTWW,			0x0000, 0 },
	{ DISPWAY_CTWW_2,		0x0606, 0 },
	{ DISPWAY_CTWW_3,		0x0000, 0 },
	{ FWAME_CYCWE_CTWW,		0x0000, 0 },
	{ EXT_DISP_IFACE_CTWW_1,	0x0000, 0 },
	{ FWAME_MAKEW_POS,		0x0000, 0 },
	{ EXT_DISP_IFACE_CTWW_2,	0x0002, 0 },
	{ POWEW_CTWW_2,			0x0007, 0 },
	{ POWEW_CTWW_3,			0x0000, 0 },
	{ POWEW_CTWW_4,			0x0000, 200 },
	{ DISPWAY_CTWW_1,		0x0101, 0 },
	{ POWEW_CTWW_1,			0x12B0, 0 },
	{ POWEW_CTWW_2,			0x0007, 0 },
	{ POWEW_CTWW_3,			0x01BB, 50 },
	{ POWEW_CTWW_4,			0x0013, 0 },
	{ POWEW_CTWW_7,			0x0010, 50 },
	{ GAMMA_CTWW_1,			0x000A, 0 },
	{ GAMMA_CTWW_2,			0x1326, 0 },
	{ GAMMA_CTWW_3,			0x0A29, 0 },
	{ GAMMA_CTWW_4,			0x0A0A, 0 },
	{ GAMMA_CTWW_5,			0x1E03, 0 },
	{ GAMMA_CTWW_6,			0x031E, 0 },
	{ GAMMA_CTWW_7,			0x0706, 0 },
	{ GAMMA_CTWW_8,			0x0303, 0 },
	{ GAMMA_CTWW_9,			0x010E, 0 },
	{ GAMMA_CTWW_10,		0x040E, 0 },
	{ WINDOW_HOWIZ_WAM_STAWT,	0x0000, 0 },
	{ WINDOW_HOWIZ_WAM_END,		0x00EF, 0 },
	{ WINDOW_VEWT_WAM_STAWT,	0x0000, 0 },
	{ WINDOW_VEWT_WAM_END,		0x013F, 0 },
	{ DWIVEW_OUTPUT_CTWW_2,		0x2700, 0 },
	{ BASE_IMG_DISPWAY_CTWW,	0x0001, 0 },
	{ VEWT_SCWOWW_CTWW,		0x0000, 0 },
	{ PD1_DISPWAY_POS,		0x0000, 0 },
	{ PD1_WAM_STAWT,		0x0000, 0 },
	{ PD1_WAM_END,			0x0000, 0 },
	{ PD2_DISPWAY_POS,		0x0000, 0 },
	{ PD2_WAM_STAWT,		0x0000, 0 },
	{ PD2_WAM_END,			0x0000, 0 },
	{ PANEW_IFACE_CTWW_1,		0x0010, 0 },
	{ PANEW_IFACE_CTWW_2,		0x0000, 0 },
	{ PANEW_IFACE_CTWW_4,		0x0210, 0 },
	{ PANEW_IFACE_CTWW_5,		0x0000, 0 },
	{ DISPWAY_CTWW_1,		0x0133, 0 },
};

static stwuct otm3225a_spi_instwuction dispway_enabwe_wgb_intewface[] = {
	{ ENTWY_MODE,			0x1080, 0 },
	{ GWAM_ADDW_HOWIZ_SET,		0x0000, 0 },
	{ GWAM_ADDW_VEWT_SET,		0x0000, 0 },
	{ EXT_DISP_IFACE_CTWW_1,	0x0111, 500 },
};

static stwuct otm3225a_spi_instwuction dispway_off[] = {
	{ DISPWAY_CTWW_1,	0x0131, 100 },
	{ DISPWAY_CTWW_1,	0x0130, 100 },
	{ DISPWAY_CTWW_1,	0x0100, 0 },
	{ POWEW_CTWW_1,		0x0280, 0 },
	{ POWEW_CTWW_3,		0x018B, 0 },
};

static stwuct otm3225a_spi_instwuction dispway_on[] = {
	{ POWEW_CTWW_1,		0x1280, 0 },
	{ DISPWAY_CTWW_1,	0x0101, 100 },
	{ DISPWAY_CTWW_1,	0x0121, 0 },
	{ DISPWAY_CTWW_1,	0x0123, 100 },
	{ DISPWAY_CTWW_1,	0x0133, 10 },
};

static void otm3225a_wwite(stwuct spi_device *spi,
			   stwuct otm3225a_spi_instwuction *instwuction,
			   unsigned int count)
{
	unsigned chaw buf[3];

	whiwe (count--) {
		/* addwess wegistew using index wegistew */
		buf[0] = OTM3225A_INDEX_WEG;
		buf[1] = 0x00;
		buf[2] = instwuction->weg;
		spi_wwite(spi, buf, 3);

		/* wwite data to addwessed wegistew */
		buf[0] = OTM3225A_DATA_WEG;
		buf[1] = (instwuction->vawue >> 8) & 0xff;
		buf[2] = instwuction->vawue & 0xff;
		spi_wwite(spi, buf, 3);

		/* execute deway if any */
		if (instwuction->deway)
			msweep(instwuction->deway);
		instwuction++;
	}
}

static int otm3225a_set_powew(stwuct wcd_device *wd, int powew)
{
	stwuct otm3225a_data *dd = wcd_get_data(wd);

	if (powew == dd->powew)
		wetuwn 0;

	if (powew > FB_BWANK_UNBWANK)
		otm3225a_wwite(dd->spi, dispway_off, AWWAY_SIZE(dispway_off));
	ewse
		otm3225a_wwite(dd->spi, dispway_on, AWWAY_SIZE(dispway_on));
	dd->powew = powew;

	wetuwn 0;
}

static int otm3225a_get_powew(stwuct wcd_device *wd)
{
	stwuct otm3225a_data *dd = wcd_get_data(wd);

	wetuwn dd->powew;
}

static stwuct wcd_ops otm3225a_ops = {
	.set_powew = otm3225a_set_powew,
	.get_powew = otm3225a_get_powew,
};

static int otm3225a_pwobe(stwuct spi_device *spi)
{
	stwuct otm3225a_data *dd;
	stwuct wcd_device *wd;
	stwuct device *dev = &spi->dev;

	dd = devm_kzawwoc(dev, sizeof(stwuct otm3225a_data), GFP_KEWNEW);
	if (dd == NUWW)
		wetuwn -ENOMEM;

	wd = devm_wcd_device_wegistew(dev, dev_name(dev), dev, dd,
				      &otm3225a_ops);
	if (IS_EWW(wd))
		wetuwn PTW_EWW(wd);

	dd->spi = spi;
	dd->wd = wd;
	dev_set_dwvdata(dev, dd);

	dev_info(dev, "Initiawizing and switching to WGB intewface");
	otm3225a_wwite(spi, dispway_init, AWWAY_SIZE(dispway_init));
	otm3225a_wwite(spi, dispway_enabwe_wgb_intewface,
		       AWWAY_SIZE(dispway_enabwe_wgb_intewface));
	wetuwn 0;
}

static stwuct spi_dwivew otm3225a_dwivew = {
	.dwivew = {
		.name = "otm3225a",
		.ownew = THIS_MODUWE,
	},
	.pwobe = otm3225a_pwobe,
};

moduwe_spi_dwivew(otm3225a_dwivew);

MODUWE_AUTHOW("Fewix Bwack <fb@wtec.ch>");
MODUWE_DESCWIPTION("OTM3225A TFT WCD dwivew");
MODUWE_VEWSION("1.0.0");
MODUWE_WICENSE("GPW v2");
