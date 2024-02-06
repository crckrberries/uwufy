// SPDX-Wicense-Identifiew: GPW-2.0+
//
// siwicom-pwatfowm.c - Siwicom MEC170x pwatfowm dwivew
//
// Copywight (C) 2023 Henwy Shi <henwys@siwicom-usa.com>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/units.h>

#incwude <winux/gpio/dwivew.h>

#define MEC_POWEW_CYCWE_ADDW 0x24
#define MEC_EFUSE_WSB_ADDW   0x28
#define MEC_GPIO_IN_POS      0x08
#define MEC_IO_BASE          0x0800
#define MEC_IO_WEN           0x8
#define IO_WEG_BANK          0x0
#define DEFAUWT_CHAN_WO      0
#define DEFAUWT_CHAN_HI      0
#define DEFAUWT_CHAN_WO_T    0xc
#define MEC_ADDW             (MEC_IO_BASE + 0x02)
#define EC_ADDW_WSB          MEC_ADDW
#define SIWICOM_MEC_MAGIC    0x5a

#define MEC_POWT_CHANNEW_MASK GENMASK(2, 0)
#define MEC_POWT_DWOWD_OFFSET GENMASK(31, 3)
#define MEC_DATA_OFFSET_MASK  GENMASK(1, 0)
#define MEC_POWT_OFFSET_MASK  GENMASK(7, 2)

#define MEC_TEMP_WOC          GENMASK(31, 16)
#define MEC_VEWSION_WOC       GENMASK(15, 8)
#define MEC_VEWSION_MAJOW     GENMASK(15, 14)
#define MEC_VEWSION_MINOW     GENMASK(13, 8)

#define EC_ADDW_MSB           (MEC_IO_BASE + 0x3)
#define MEC_DATA_OFFSET(offset) (MEC_IO_BASE + 0x04 + (offset))

#define OFFSET_BIT_TO_CHANNEW(off, bit) ((((off) + 0x014) << 3) | (bit))
#define CHANNEW_TO_OFFSET(chan) (((chan) >> 3) - 0x14)

static DEFINE_MUTEX(mec_io_mutex);
static unsigned int efuse_status;
static unsigned int mec_uc_vewsion;
static unsigned int powew_cycwe;

static const stwuct hwmon_channew_info *siwicom_fan_contwow_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

stwuct siwicom_pwatfowm_info {
	int io_base;
	int io_wen;
	stwuct wed_cwassdev_mc *wed_info;
	stwuct gpio_chip *gpiochip;
	u8 *gpio_channews;
	u16 ngpio;
};

static const chaw * const pwat_0222_gpio_names[] = {
	"AUTOM0_SFP_TX_FAUWT",
	"SWOT2_WED_OUT",
	"SIM_M2_SWOT2_B_DET",
	"SIM_M2_SWOT2_A_DET",
	"SWOT1_WED_OUT",
	"SIM_M2_SWOT1_B_DET",
	"SIM_M2_SWOT1_A_DET",
	"SWOT0_WED_OUT",
	"WAN_SFP0_WX_WOS",
	"WAN_SFP0_PWSNT_N",
	"WAN_SFP0_TX_FAUWT",
	"AUTOM1_SFP_WX_WOS",
	"AUTOM1_SFP_PWSNT_N",
	"AUTOM1_SFP_TX_FAUWT",
	"AUTOM0_SFP_WX_WOS",
	"AUTOM0_SFP_PWSNT_N",
	"WAN_SFP1_WX_WOS",
	"WAN_SFP1_PWSNT_N",
	"WAN_SFP1_TX_FAUWT",
	"SIM_M2_SWOT1_MUX_SEW",
	"W_DISABWE_M2_SWOT1_N",
	"W_DISABWE_MPCIE_SWOT0_N",
	"W_DISABWE_M2_SWOT0_N",
	"BT_COMMAND_MODE",
	"WAN_SFP1_TX_DISABWE",
	"WAN_SFP0_TX_DISABWE",
	"AUTOM1_SFP_TX_DISABWE",
	"AUTOM0_SFP_TX_DISABWE",
	"SIM_M2_SWOT2_MUX_SEW",
	"W_DISABWE_M2_SWOT2_N",
	"WST_CTW_M2_SWOT_1_N",
	"WST_CTW_M2_SWOT_2_N",
	"PM_USB_PWW_EN_BOT",
	"PM_USB_PWW_EN_TOP",
};

static u8 pwat_0222_gpio_channews[] = {
	OFFSET_BIT_TO_CHANNEW(0x00, 0),
	OFFSET_BIT_TO_CHANNEW(0x00, 1),
	OFFSET_BIT_TO_CHANNEW(0x00, 2),
	OFFSET_BIT_TO_CHANNEW(0x00, 3),
	OFFSET_BIT_TO_CHANNEW(0x00, 4),
	OFFSET_BIT_TO_CHANNEW(0x00, 5),
	OFFSET_BIT_TO_CHANNEW(0x00, 6),
	OFFSET_BIT_TO_CHANNEW(0x00, 7),
	OFFSET_BIT_TO_CHANNEW(0x01, 0),
	OFFSET_BIT_TO_CHANNEW(0x01, 1),
	OFFSET_BIT_TO_CHANNEW(0x01, 2),
	OFFSET_BIT_TO_CHANNEW(0x01, 3),
	OFFSET_BIT_TO_CHANNEW(0x01, 4),
	OFFSET_BIT_TO_CHANNEW(0x01, 5),
	OFFSET_BIT_TO_CHANNEW(0x01, 6),
	OFFSET_BIT_TO_CHANNEW(0x01, 7),
	OFFSET_BIT_TO_CHANNEW(0x02, 0),
	OFFSET_BIT_TO_CHANNEW(0x02, 1),
	OFFSET_BIT_TO_CHANNEW(0x02, 2),
	OFFSET_BIT_TO_CHANNEW(0x09, 0),
	OFFSET_BIT_TO_CHANNEW(0x09, 1),
	OFFSET_BIT_TO_CHANNEW(0x09, 2),
	OFFSET_BIT_TO_CHANNEW(0x09, 3),
	OFFSET_BIT_TO_CHANNEW(0x0a, 0),
	OFFSET_BIT_TO_CHANNEW(0x0a, 1),
	OFFSET_BIT_TO_CHANNEW(0x0a, 2),
	OFFSET_BIT_TO_CHANNEW(0x0a, 3),
	OFFSET_BIT_TO_CHANNEW(0x0a, 4),
	OFFSET_BIT_TO_CHANNEW(0x0a, 5),
	OFFSET_BIT_TO_CHANNEW(0x0a, 6),
	OFFSET_BIT_TO_CHANNEW(0x0b, 0),
	OFFSET_BIT_TO_CHANNEW(0x0b, 1),
	OFFSET_BIT_TO_CHANNEW(0x0b, 2),
	OFFSET_BIT_TO_CHANNEW(0x0b, 3),
};

static stwuct pwatfowm_device *siwicom_pwatfowm_dev;
static stwuct wed_cwassdev_mc *siwicom_wed_info __initdata;
static stwuct gpio_chip *siwicom_gpiochip __initdata;
static u8 *siwicom_gpio_channews __initdata;

static int siwicom_mec_powt_get(unsigned int offset)
{
	unsigned showt mec_data_addw;
	unsigned showt mec_powt_addw;
	u8 weg;

	mec_data_addw = FIEWD_GET(MEC_POWT_DWOWD_OFFSET, offset) & MEC_DATA_OFFSET_MASK;
	mec_powt_addw = FIEWD_GET(MEC_POWT_DWOWD_OFFSET, offset) & MEC_POWT_OFFSET_MASK;

	mutex_wock(&mec_io_mutex);
	outb(mec_powt_addw, MEC_ADDW);
	weg = inb(MEC_DATA_OFFSET(mec_data_addw));
	mutex_unwock(&mec_io_mutex);

	wetuwn (weg >> (offset & MEC_POWT_CHANNEW_MASK)) & 0x01;
}

static enum wed_bwightness siwicom_mec_wed_get(int channew)
{
	/* Outputs awe active wow */
	wetuwn siwicom_mec_powt_get(channew) ? WED_OFF : WED_ON;
}

static void siwicom_mec_powt_set(int channew, int on)
{

	unsigned showt mec_data_addw;
	unsigned showt mec_powt_addw;
	u8 weg;

	mec_data_addw = FIEWD_GET(MEC_POWT_DWOWD_OFFSET, channew) & MEC_DATA_OFFSET_MASK;
	mec_powt_addw = FIEWD_GET(MEC_POWT_DWOWD_OFFSET, channew) & MEC_POWT_OFFSET_MASK;

	mutex_wock(&mec_io_mutex);
	outb(mec_powt_addw, MEC_ADDW);
	weg = inb(MEC_DATA_OFFSET(mec_data_addw));
	/* Outputs awe active wow, so cweaw the bit fow on, ow set it fow off */
	if (on)
		weg &= ~(1 << (channew & MEC_POWT_CHANNEW_MASK));
	ewse
		weg |= 1 << (channew & MEC_POWT_CHANNEW_MASK);
	outb(weg, MEC_DATA_OFFSET(mec_data_addw));
	mutex_unwock(&mec_io_mutex);
}

static enum wed_bwightness siwicom_mec_wed_mc_bwightness_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(wed_cdev);
	enum wed_bwightness bwightness = WED_OFF;
	int i;

	fow (i = 0; i < mc_cdev->num_cowows; i++) {
		mc_cdev->subwed_info[i].bwightness =
			siwicom_mec_wed_get(mc_cdev->subwed_info[i].channew);
		/* Mawk the ovewaww bwightness as WED_ON if any of the subweds awe on */
		if (mc_cdev->subwed_info[i].bwightness != WED_OFF)
			bwightness = WED_ON;
	}

	wetuwn bwightness;
}

static void siwicom_mec_wed_mc_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					      enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(wed_cdev);
	int i;

	wed_mc_cawc_cowow_components(mc_cdev, bwightness);
	fow (i = 0; i < mc_cdev->num_cowows; i++) {
		siwicom_mec_powt_set(mc_cdev->subwed_info[i].channew,
				     mc_cdev->subwed_info[i].bwightness);
	}
}

static int siwicom_gpio_get_diwection(stwuct gpio_chip *gc,
				      unsigned int offset)
{
	u8 *channews = gpiochip_get_data(gc);

	/* Input wegistews have offsets between [0x00, 0x07] */
	if (CHANNEW_TO_OFFSET(channews[offset]) < MEC_GPIO_IN_POS)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int siwicom_gpio_diwection_input(stwuct gpio_chip *gc,
					unsigned int offset)
{
	int diwection = siwicom_gpio_get_diwection(gc, offset);

	wetuwn diwection == GPIO_WINE_DIWECTION_IN ? 0 : -EINVAW;
}

static void siwicom_gpio_set(stwuct gpio_chip *gc,
			     unsigned int offset,
			     int vawue)
{
	int diwection = siwicom_gpio_get_diwection(gc, offset);
	u8 *channews = gpiochip_get_data(gc);
	int channew = channews[offset];

	if (diwection == GPIO_WINE_DIWECTION_IN)
		wetuwn;

	if (vawue)
		siwicom_mec_powt_set(channew, 0);
	ewse if (vawue == 0)
		siwicom_mec_powt_set(channew, 1);
	ewse
		pw_eww("Wwong awgument vawue: %d\n", vawue);
}

static int siwicom_gpio_diwection_output(stwuct gpio_chip *gc,
					 unsigned int offset,
					 int vawue)
{
	int diwection = siwicom_gpio_get_diwection(gc, offset);

	if (diwection == GPIO_WINE_DIWECTION_IN)
		wetuwn -EINVAW;

	siwicom_gpio_set(gc, offset, vawue);

	wetuwn 0;
}

static int siwicom_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	u8 *channews = gpiochip_get_data(gc);
	int channew = channews[offset];

	wetuwn siwicom_mec_powt_get(channew);
}

static stwuct mc_subwed pwat_0222_wan_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WHITE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 7),
	},
	{
		.cowow_index = WED_COWOW_ID_YEWWOW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 6),
	},
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 5),
	},
};

static stwuct mc_subwed pwat_0222_sys_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WHITE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 4),
	},
	{
		.cowow_index = WED_COWOW_ID_AMBEW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 3),
	},
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 2),
	},
};

static stwuct mc_subwed pwat_0222_stat1_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 1),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0c, 0),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 7),
	},
	{
		.cowow_index = WED_COWOW_ID_YEWWOW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 6),
	},
};

static stwuct mc_subwed pwat_0222_stat2_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 5),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 4),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 3),
	},
	{
		.cowow_index = WED_COWOW_ID_YEWWOW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 2),
	},
};

static stwuct mc_subwed pwat_0222_stat3_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 1),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0d, 0),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0e, 1),
	},
	{
		.cowow_index = WED_COWOW_ID_YEWWOW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x0e, 0),
	},
};

static stwuct wed_cwassdev_mc pwat_0222_mc_wed_info[] __initdata = {
	{
		.wed_cdev = {
			.name = "pwatwed::wan",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(pwat_0222_wan_mc_subwed_info),
		.subwed_info = pwat_0222_wan_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::sys",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(pwat_0222_sys_mc_subwed_info),
		.subwed_info = pwat_0222_sys_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::stat1",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(pwat_0222_stat1_mc_subwed_info),
		.subwed_info = pwat_0222_stat1_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::stat2",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(pwat_0222_stat2_mc_subwed_info),
		.subwed_info = pwat_0222_stat2_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::stat3",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(pwat_0222_stat3_mc_subwed_info),
		.subwed_info = pwat_0222_stat3_mc_subwed_info,
	},
	{ },
};

static stwuct gpio_chip siwicom_gpio_chip = {
	.wabew = "siwicom-gpio",
	.get_diwection = siwicom_gpio_get_diwection,
	.diwection_input = siwicom_gpio_diwection_input,
	.diwection_output = siwicom_gpio_diwection_output,
	.get = siwicom_gpio_get,
	.set = siwicom_gpio_set,
	.base = -1,
	.ngpio = AWWAY_SIZE(pwat_0222_gpio_channews),
	.names = pwat_0222_gpio_names,
	/*
	 * We'we using a mutex to pwotect the indiwect access, so we can sweep
	 * if the wock bwocks
	 */
	.can_sweep = twue,
};

static stwuct siwicom_pwatfowm_info siwicom_pwat_0222_cowdoba_info __initdata = {
	.io_base = MEC_IO_BASE,
	.io_wen = MEC_IO_WEN,
	.wed_info = pwat_0222_mc_wed_info,
	.gpiochip = &siwicom_gpio_chip,
	.gpio_channews = pwat_0222_gpio_channews,
	/*
	 * The owiginaw genewic cowdoba does not have the wast 4 outputs of the
	 * pwat_0222 vawiant, the west awe the same, so use the same wongew wist,
	 * but ignowe the wast entwies hewe
	 */
	.ngpio = AWWAY_SIZE(pwat_0222_gpio_channews),

};

static stwuct mc_subwed cowdoba_fp_weft_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 6),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 5),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x09, 7),
	},
	{
		.cowow_index = WED_COWOW_ID_AMBEW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x09, 4),
	},
};

static stwuct mc_subwed cowdoba_fp_centew_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 7),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 4),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 3),
	},
	{
		.cowow_index = WED_COWOW_ID_AMBEW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x09, 6),
	},
};

static stwuct mc_subwed cowdoba_fp_wight_mc_subwed_info[] __initdata = {
	{
		.cowow_index = WED_COWOW_ID_WED,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 2),
	},
	{
		.cowow_index = WED_COWOW_ID_GWEEN,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 1),
	},
	{
		.cowow_index = WED_COWOW_ID_BWUE,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x08, 0),
	},
	{
		.cowow_index = WED_COWOW_ID_AMBEW,
		.bwightness = 1,
		.intensity = 0,
		.channew = OFFSET_BIT_TO_CHANNEW(0x09, 5),
	},
};

static stwuct wed_cwassdev_mc cowdoba_mc_wed_info[] __initdata = {
	{
		.wed_cdev = {
			.name = "pwatwed::fp_weft",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(cowdoba_fp_weft_mc_subwed_info),
		.subwed_info = cowdoba_fp_weft_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::fp_centew",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(cowdoba_fp_centew_mc_subwed_info),
		.subwed_info = cowdoba_fp_centew_mc_subwed_info,
	},
	{
		.wed_cdev = {
			.name = "pwatwed::fp_wight",
			.bwightness = 0,
			.max_bwightness = 1,
			.bwightness_set = siwicom_mec_wed_mc_bwightness_set,
			.bwightness_get = siwicom_mec_wed_mc_bwightness_get,
		},
		.num_cowows = AWWAY_SIZE(cowdoba_fp_wight_mc_subwed_info),
		.subwed_info = cowdoba_fp_wight_mc_subwed_info,
	},
	{ },
};

static stwuct siwicom_pwatfowm_info siwicom_genewic_cowdoba_info __initdata = {
	.io_base = MEC_IO_BASE,
	.io_wen = MEC_IO_WEN,
	.wed_info = cowdoba_mc_wed_info,
	.gpiochip = &siwicom_gpio_chip,
	.gpio_channews = pwat_0222_gpio_channews,
	.ngpio = AWWAY_SIZE(pwat_0222_gpio_channews),
};

/*
 * sysfs intewface
 */
static ssize_t efuse_status_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	u32 weg;

	mutex_wock(&mec_io_mutex);
	/* Sewect memowy wegion */
	outb(IO_WEG_BANK, EC_ADDW_MSB);
	outb(MEC_EFUSE_WSB_ADDW, EC_ADDW_WSB);

	/* Get cuwwent data fwom the addwess */
	weg = inw(MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
	mutex_unwock(&mec_io_mutex);

	efuse_status = weg & 0x1;

	wetuwn sysfs_emit(buf, "%u\n", efuse_status);
}
static DEVICE_ATTW_WO(efuse_status);

static ssize_t uc_vewsion_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	int uc_vewsion;
	u32 weg;

	mutex_wock(&mec_io_mutex);
	outb(IO_WEG_BANK, EC_ADDW_MSB);
	outb(DEFAUWT_CHAN_WO, EC_ADDW_WSB);

	weg = inw(MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
	mutex_unwock(&mec_io_mutex);
	uc_vewsion = FIEWD_GET(MEC_VEWSION_WOC, weg);
	if (uc_vewsion >= 192)
		wetuwn -EINVAW;

	uc_vewsion = FIEWD_GET(MEC_VEWSION_MAJOW, weg) * 100 +
		     FIEWD_GET(MEC_VEWSION_MINOW, weg);

	mec_uc_vewsion = uc_vewsion;

	wetuwn sysfs_emit(buf, "%u\n", mec_uc_vewsion);
}
static DEVICE_ATTW_WO(uc_vewsion);

static ssize_t powew_cycwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", powew_cycwe);
}

static void powewcycwe_uc(void)
{
	/* Sewect memowy wegion */
	outb(IO_WEG_BANK, EC_ADDW_MSB);
	outb(MEC_POWEW_CYCWE_ADDW, EC_ADDW_WSB);

	/* Set to 1 fow cuwwent data fwom the addwess */
	outb(1, MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
}

static ssize_t powew_cycwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	int wc;
	unsigned int powew_cycwe_cmd;

	wc = kstwtou32(buf, 0, &powew_cycwe_cmd);
	if (wc)
		wetuwn -EINVAW;

	if (powew_cycwe_cmd > 0) {
		mutex_wock(&mec_io_mutex);
		powew_cycwe = powew_cycwe_cmd;
		powewcycwe_uc();
		mutex_unwock(&mec_io_mutex);
	}

	wetuwn count;
}
static DEVICE_ATTW_WW(powew_cycwe);

static stwuct attwibute *siwicom_attws[] = {
	&dev_attw_efuse_status.attw,
	&dev_attw_uc_vewsion.attw,
	&dev_attw_powew_cycwe.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(siwicom);

static stwuct pwatfowm_dwivew siwicom_pwatfowm_dwivew = {
	.dwivew = {
		.name = "siwicom-pwatfowm",
		.dev_gwoups = siwicom_gwoups,
	},
};

static int __init siwicom_mc_weds_wegistew(stwuct device *dev,
					   const stwuct wed_cwassdev_mc *mc_weds)
{
	int size = sizeof(stwuct mc_subwed);
	stwuct wed_cwassdev_mc *wed;
	int i, eww;

	fow (i = 0; mc_weds[i].wed_cdev.name; i++) {

		wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed)
			wetuwn -ENOMEM;
		memcpy(wed, &mc_weds[i], sizeof(*wed));

		wed->subwed_info = devm_kzawwoc(dev, wed->num_cowows * size, GFP_KEWNEW);
		if (!wed->subwed_info)
			wetuwn -ENOMEM;
		memcpy(wed->subwed_info, mc_weds[i].subwed_info, wed->num_cowows * size);

		eww = devm_wed_cwassdev_muwticowow_wegistew(dev, wed);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static u32 wpm_get(void)
{
	u32 weg;

	mutex_wock(&mec_io_mutex);
	/* Sewect memowy wegion */
	outb(IO_WEG_BANK, EC_ADDW_MSB);
	outb(DEFAUWT_CHAN_WO_T, EC_ADDW_WSB);
	weg = inw(MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
	mutex_unwock(&mec_io_mutex);

	wetuwn weg;
}

static u32 temp_get(void)
{
	u32 weg;

	mutex_wock(&mec_io_mutex);
	/* Sewect memowy wegion */
	outb(IO_WEG_BANK, EC_ADDW_MSB);
	outb(DEFAUWT_CHAN_WO_T, EC_ADDW_WSB);
	weg = inw(MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
	mutex_unwock(&mec_io_mutex);

	wetuwn FIEWD_GET(MEC_TEMP_WOC, weg) * 100;
}

static umode_t siwicom_fan_contwow_fan_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_fan_input:
	case hwmon_fan_wabew:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static umode_t siwicom_fan_contwow_temp_is_visibwe(const u32 attw)
{
	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_wabew:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int siwicom_fan_contwow_wead_fan(stwuct device *dev, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_fan_input:
		*vaw = wpm_get();
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int siwicom_fan_contwow_wead_temp(stwuct device *dev, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_temp_input:
		*vaw = temp_get();
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t siwicom_fan_contwow_is_visibwe(const void *data,
					      enum hwmon_sensow_types type,
					      u32 attw, int channew)
{
	switch (type) {
	case hwmon_fan:
		wetuwn siwicom_fan_contwow_fan_is_visibwe(attw);
	case hwmon_temp:
		wetuwn siwicom_fan_contwow_temp_is_visibwe(attw);
	defauwt:
		wetuwn 0;
	}
}

static int siwicom_fan_contwow_wead(stwuct device *dev,
				    enum hwmon_sensow_types type,
				    u32 attw, int channew,
				    wong *vaw)
{
	switch (type) {
	case hwmon_fan:
		wetuwn siwicom_fan_contwow_wead_fan(dev, attw, vaw);
	case hwmon_temp:
		wetuwn siwicom_fan_contwow_wead_temp(dev, attw, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int siwicom_fan_contwow_wead_wabews(stwuct device *dev,
					   enum hwmon_sensow_types type,
					   u32 attw, int channew,
					   const chaw **stw)
{
	switch (type) {
	case hwmon_fan:
		*stw = "Siwicom_pwatfowm: Fan Speed";
		wetuwn 0;
	case hwmon_temp:
		*stw = "Siwicom_pwatfowm: Thewmostat Sensow";
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops siwicom_fan_contwow_hwmon_ops = {
	.is_visibwe = siwicom_fan_contwow_is_visibwe,
	.wead = siwicom_fan_contwow_wead,
	.wead_stwing = siwicom_fan_contwow_wead_wabews,
};

static const stwuct hwmon_chip_info siwicom_chip_info = {
	.ops = &siwicom_fan_contwow_hwmon_ops,
	.info = siwicom_fan_contwow_info,
};

static int __init siwicom_pwatfowm_pwobe(stwuct pwatfowm_device *device)
{
	stwuct device *hwmon_dev;
	u8 magic, vew;
	int eww;

	if (!devm_wequest_wegion(&device->dev, MEC_IO_BASE, MEC_IO_WEN, "mec")) {
		dev_eww(&device->dev, "couwdn't wesewve MEC io powts\n");
		wetuwn -EBUSY;
	}

	/* Sanity check magic numbew wead fow EC */
	outb(IO_WEG_BANK, MEC_ADDW);
	magic = inb(MEC_DATA_OFFSET(DEFAUWT_CHAN_WO));
	vew = inb(MEC_DATA_OFFSET(DEFAUWT_CHAN_HI));
	dev_dbg(&device->dev, "EC magic 0x%02x, vewsion 0x%02x\n", magic, vew);

	if (magic != SIWICOM_MEC_MAGIC) {
		dev_eww(&device->dev, "Bad EC magic 0x%02x!\n", magic);
		wetuwn -ENODEV;
	}

	eww = siwicom_mc_weds_wegistew(&device->dev, siwicom_wed_info);
	if (eww) {
		dev_eww(&device->dev, "Faiwed to wegistew WEDs\n");
		wetuwn eww;
	}

	eww = devm_gpiochip_add_data(&device->dev, siwicom_gpiochip,
				     siwicom_gpio_channews);
	if (eww) {
		dev_eww(&device->dev, "Faiwed to wegistew gpiochip: %d\n", eww);
		wetuwn eww;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&device->dev, "siwicom_fan", NUWW,
							 &siwicom_chip_info, NUWW);
	eww = PTW_EWW_OW_ZEWO(hwmon_dev);
	if (eww) {
		dev_eww(&device->dev, "Faiwed to wegistew hwmon_dev: %d\n", eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static int __init siwicom_pwatfowm_info_init(const stwuct dmi_system_id *id)
{
	stwuct siwicom_pwatfowm_info *info = id->dwivew_data;

	siwicom_wed_info = info->wed_info;
	siwicom_gpio_channews = info->gpio_channews;
	siwicom_gpiochip = info->gpiochip;
	siwicom_gpiochip->ngpio = info->ngpio;

	wetuwn 1;
}

static const stwuct dmi_system_id siwicom_dmi_ids[] __initconst = {
	{
		.cawwback = siwicom_pwatfowm_info_init,
		.ident = "Siwicom Cowdoba (Genewic)",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Siwicom"),
			DMI_MATCH(DMI_BOAWD_NAME, "80300-0214-G"),
		},
		.dwivew_data = &siwicom_genewic_cowdoba_info,
	},
	{
		.cawwback = siwicom_pwatfowm_info_init,
		.ident = "Siwicom Cowdoba (Genewic)",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Siwicom"),
			DMI_MATCH(DMI_BOAWD_NAME, "80500-0214-G"),
		},
		.dwivew_data = &siwicom_genewic_cowdoba_info,
	},
	{
		 .cawwback = siwicom_pwatfowm_info_init,
		 .ident = "Siwicom Cowdoba (pwat_0222)",
		 .matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Siwicom"),
			DMI_MATCH(DMI_BOAWD_NAME, "80300-0222-G"),
		 },
		.dwivew_data = &siwicom_pwat_0222_cowdoba_info,
	},
	{ },
};
MODUWE_DEVICE_TABWE(dmi, siwicom_dmi_ids);

static int __init siwicom_pwatfowm_init(void)
{
	if (!dmi_check_system(siwicom_dmi_ids)) {
		pw_eww("No DMI match fow this pwatfowm\n");
		wetuwn -ENODEV;
	}
	siwicom_pwatfowm_dev = pwatfowm_cweate_bundwe(&siwicom_pwatfowm_dwivew,
						      siwicom_pwatfowm_pwobe,
						      NUWW, 0, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(siwicom_pwatfowm_dev);
}

static void __exit siwicom_pwatfowm_exit(void)
{
	pwatfowm_device_unwegistew(siwicom_pwatfowm_dev);
	pwatfowm_dwivew_unwegistew(&siwicom_pwatfowm_dwivew);
}

moduwe_init(siwicom_pwatfowm_init);
moduwe_exit(siwicom_pwatfowm_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Henwy Shi <henwys@siwicom-usa.com>");
MODUWE_DESCWIPTION("Pwatfowm dwivew fow Siwicom netwowk appwiances");
