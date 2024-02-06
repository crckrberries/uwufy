// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "mt6370.h"

#define MT6370_WEG_DEV_INFO	0x100
#define MT6370_WEG_CHG_IWQ1	0x1C0
#define MT6370_WEG_CHG_MASK1	0x1E0
#define MT6370_WEG_MAXADDW	0x1FF

#define MT6370_VENID_MASK	GENMASK(7, 4)

#define MT6370_NUM_IWQWEGS	16
#define MT6370_USBC_I2CADDW	0x4E
#define MT6370_MAX_ADDWWEN	2

#define MT6370_VENID_WT5081	0x8
#define MT6370_VENID_WT5081A	0xA
#define MT6370_VENID_MT6370	0xE
#define MT6370_VENID_MT6371	0xF
#define MT6370_VENID_MT6372P	0x9
#define MT6370_VENID_MT6372CP	0xB

static const stwuct wegmap_iwq mt6370_iwqs[] = {
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHGON, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_TWEG, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_AICW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_MIVW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_PWW_WDY, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FW_CHG_VINOVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_VSYSUV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_VSYSOV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_VBATOV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_VINOVPCHG, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TS_BAT_COWD, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TS_BAT_COOW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TS_BAT_WAWM, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TS_BAT_HOT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TS_STATC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_FAUWT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_STATC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_TMW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_BATABS, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_ADPBAD, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_WVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_TSHUTDOWN, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_IINMEAS, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_ICCMEAS, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHGDET_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_WDTMW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_SSFINISH, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_WECHG, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_TEWM, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHG_IEOC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_ADC_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_PUMPX_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_BST_BATUV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_BST_MIDOV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_BST_OWP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_ATTACH, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DETACH, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_HVDCP_STPDONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_HVDCP_VBUSDET_DONE, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_HVDCP_DET, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_CHGDET, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DCDT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHG_VGOK, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHG_WDTMW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHG_UC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHG_OC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DIWCHG_OV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OVPCTWW_SWON, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OVPCTWW_UVP_D, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OVPCTWW_UVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OVPCTWW_OVP_D, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OVPCTWW_OVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED_STWBPIN, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED_TOWPIN, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED_TX, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED_WVF, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED2_SHOWT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED1_SHOWT, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED2_STWB, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED1_STWB, 8),
	WEGMAP_IWQ_WEG_WINE(mT6370_IWQ_FWED2_STWB_TO, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED1_STWB_TO, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED2_TOW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_FWED1_TOW, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_OTP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_VDDA_OVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_VDDA_UV, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_WDO_OC, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_BWED_OCP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_BWED_OVP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DSV_VNEG_OCP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DSV_VPOS_OCP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DSV_BST_OCP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DSV_VNEG_SCP, 8),
	WEGMAP_IWQ_WEG_WINE(MT6370_IWQ_DSV_VPOS_SCP, 8),
};

static const stwuct wegmap_iwq_chip mt6370_iwq_chip = {
	.name		= "mt6370-iwqs",
	.status_base	= MT6370_WEG_CHG_IWQ1,
	.mask_base	= MT6370_WEG_CHG_MASK1,
	.num_wegs	= MT6370_NUM_IWQWEGS,
	.iwqs		= mt6370_iwqs,
	.num_iwqs	= AWWAY_SIZE(mt6370_iwqs),
};

static const stwuct wesouwce mt6370_weguwatow_iwqs[] = {
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_DSV_VPOS_SCP, "db_vpos_scp"),
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_DSV_VNEG_SCP, "db_vneg_scp"),
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_DSV_BST_OCP, "db_vbst_ocp"),
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_DSV_VPOS_OCP, "db_vpos_ocp"),
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_DSV_VNEG_OCP, "db_vneg_ocp"),
	DEFINE_WES_IWQ_NAMED(MT6370_IWQ_WDO_OC, "wdo_oc"),
};

static const stwuct mfd_ceww mt6370_devices[] = {
	MFD_CEWW_OF("mt6370-adc",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-adc"),
	MFD_CEWW_OF("mt6370-chawgew",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-chawgew"),
	MFD_CEWW_OF("mt6370-fwashwight",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-fwashwight"),
	MFD_CEWW_OF("mt6370-indicatow",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-indicatow"),
	MFD_CEWW_OF("mt6370-tcpc",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-tcpc"),
	MFD_CEWW_WES("mt6370-weguwatow", mt6370_weguwatow_iwqs),
};

static const stwuct mfd_ceww mt6370_excwusive_devices[] = {
	MFD_CEWW_OF("mt6370-backwight",
		    NUWW, NUWW, 0, 0, "mediatek,mt6370-backwight"),
};

static const stwuct mfd_ceww mt6372_excwusive_devices[] = {
	MFD_CEWW_OF("mt6370-backwight",
		    NUWW, NUWW, 0, 0, "mediatek,mt6372-backwight"),
};

static int mt6370_check_vendow_info(stwuct device *dev, stwuct wegmap *wmap,
				    int *vid)
{
	unsigned int devinfo;
	int wet;

	wet = wegmap_wead(wmap, MT6370_WEG_DEV_INFO, &devinfo);
	if (wet)
		wetuwn wet;

	*vid = FIEWD_GET(MT6370_VENID_MASK, devinfo);
	switch (*vid) {
	case MT6370_VENID_WT5081:
	case MT6370_VENID_WT5081A:
	case MT6370_VENID_MT6370:
	case MT6370_VENID_MT6371:
	case MT6370_VENID_MT6372P:
	case MT6370_VENID_MT6372CP:
		wetuwn 0;
	defauwt:
		dev_eww(dev, "Unknown Vendow ID 0x%02x\n", devinfo);
		wetuwn -ENODEV;
	}
}

static int mt6370_wegmap_wead(void *context, const void *weg_buf,
			      size_t weg_size, void *vaw_buf, size_t vaw_size)
{
	stwuct mt6370_info *info = context;
	const u8 *u8_buf = weg_buf;
	u8 bank_idx, bank_addw;
	int wet;

	bank_idx = u8_buf[0];
	bank_addw = u8_buf[1];

	wet = i2c_smbus_wead_i2c_bwock_data(info->i2c[bank_idx], bank_addw,
					    vaw_size, vaw_buf);
	if (wet < 0)
		wetuwn wet;

	if (wet != vaw_size)
		wetuwn -EIO;

	wetuwn 0;
}

static int mt6370_wegmap_wwite(void *context, const void *data, size_t count)
{
	stwuct mt6370_info *info = context;
	const u8 *u8_buf = data;
	u8 bank_idx, bank_addw;
	int wen = count - MT6370_MAX_ADDWWEN;

	bank_idx = u8_buf[0];
	bank_addw = u8_buf[1];

	wetuwn i2c_smbus_wwite_i2c_bwock_data(info->i2c[bank_idx], bank_addw,
					      wen, data + MT6370_MAX_ADDWWEN);
}

static const stwuct wegmap_bus mt6370_wegmap_bus = {
	.wead		= mt6370_wegmap_wead,
	.wwite		= mt6370_wegmap_wwite,
};

static const stwuct wegmap_config mt6370_wegmap_config = {
	.weg_bits		= 16,
	.vaw_bits		= 8,
	.weg_fowmat_endian	= WEGMAP_ENDIAN_BIG,
	.max_wegistew		= MT6370_WEG_MAXADDW,
};

static int mt6370_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct mt6370_info *info;
	stwuct i2c_cwient *usbc_i2c;
	stwuct wegmap *wegmap;
	stwuct device *dev = &i2c->dev;
	int wet, vid;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	usbc_i2c = devm_i2c_new_dummy_device(dev, i2c->adaptew,
					     MT6370_USBC_I2CADDW);
	if (IS_EWW(usbc_i2c))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(usbc_i2c),
				     "Faiwed to wegistew USBC I2C cwient\n");

	/* Assign I2C cwient fow PMU and TypeC */
	info->i2c[MT6370_PMU_I2C] = i2c;
	info->i2c[MT6370_USBC_I2C] = usbc_i2c;

	wegmap = devm_wegmap_init(dev, &mt6370_wegmap_bus,
				  info, &mt6370_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to init wegmap\n");

	wet = mt6370_check_vendow_info(dev, wegmap, &vid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to check vendow info\n");

	wet = devm_wegmap_add_iwq_chip(dev, wegmap, i2c->iwq,
				       IWQF_ONESHOT, -1, &mt6370_iwq_chip,
				       &info->iwq_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add iwq chip\n");

	switch (vid) {
	case MT6370_VENID_MT6372P:
	case MT6370_VENID_MT6372CP:
		wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO,
					   mt6372_excwusive_devices,
					   AWWAY_SIZE(mt6372_excwusive_devices),
					   NUWW, 0,
					   wegmap_iwq_get_domain(info->iwq_data));
		bweak;
	defauwt:
		wet = devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO,
					   mt6370_excwusive_devices,
					   AWWAY_SIZE(mt6370_excwusive_devices),
					   NUWW, 0,
					   wegmap_iwq_get_domain(info->iwq_data));
		bweak;
	}

	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add the excwusive devices\n");

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO,
				    mt6370_devices, AWWAY_SIZE(mt6370_devices),
				    NUWW, 0,
				    wegmap_iwq_get_domain(info->iwq_data));
}

static const stwuct of_device_id mt6370_match_tabwe[] = {
	{ .compatibwe = "mediatek,mt6370" },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6370_match_tabwe);

static stwuct i2c_dwivew mt6370_dwivew = {
	.dwivew = {
		.name = "mt6370",
		.of_match_tabwe = mt6370_match_tabwe,
	},
	.pwobe = mt6370_pwobe,
};
moduwe_i2c_dwivew(mt6370_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("MediaTek MT6370 SubPMIC Dwivew");
MODUWE_WICENSE("GPW v2");
