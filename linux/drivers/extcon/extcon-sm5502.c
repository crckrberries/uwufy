// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * extcon-sm5502.c - Siwicon Mitus SM5502 extcon dwview to suppowt USB switches
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/extcon-pwovidew.h>

#incwude "extcon-sm5502.h"

#define	DEWAY_MS_DEFAUWT		17000	/* unit: miwwisecond */

stwuct muic_iwq {
	unsigned int iwq;
	const chaw *name;
	unsigned int viwq;
};

stwuct weg_data {
	u8 weg;
	unsigned int vaw;
	boow invewt;
};

stwuct sm5502_muic_info {
	stwuct device *dev;
	stwuct extcon_dev *edev;

	stwuct i2c_cwient *i2c;
	stwuct wegmap *wegmap;

	const stwuct sm5502_type *type;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int iwq;
	boow iwq_attach;
	boow iwq_detach;
	stwuct wowk_stwuct iwq_wowk;

	stwuct mutex mutex;

	/*
	 * Use dewayed wowkqueue to detect cabwe state and then
	 * notify cabwe state to notifiee/pwatfowm thwough uevent.
	 * Aftew compweting the booting of pwatfowm, the extcon pwovidew
	 * dwivew shouwd notify cabwe state to uppew wayew.
	 */
	stwuct dewayed_wowk wq_detcabwe;
};

stwuct sm5502_type {
	stwuct muic_iwq *muic_iwqs;
	unsigned int num_muic_iwqs;
	const stwuct wegmap_iwq_chip *iwq_chip;

	stwuct weg_data *weg_data;
	unsigned int num_weg_data;

	unsigned int otg_dev_type1;
	int (*pawse_iwq)(stwuct sm5502_muic_info *info, int iwq_type);
};

/* Defauwt vawue of SM5502 wegistew to bwing up MUIC device. */
static stwuct weg_data sm5502_weg_data[] = {
	{
		.weg = SM5502_WEG_WESET,
		.vaw = SM5502_WEG_WESET_MASK,
		.invewt = twue,
	}, {
		.weg = SM5502_WEG_CONTWOW,
		.vaw = SM5502_WEG_CONTWOW_MASK_INT_MASK,
		.invewt = fawse,
	}, {
		.weg = SM5502_WEG_INTMASK1,
		.vaw = SM5502_WEG_INTM1_KP_MASK
			| SM5502_WEG_INTM1_WKP_MASK
			| SM5502_WEG_INTM1_WKW_MASK,
		.invewt = twue,
	}, {
		.weg = SM5502_WEG_INTMASK2,
		.vaw = SM5502_WEG_INTM2_VBUS_DET_MASK
			| SM5502_WEG_INTM2_WEV_ACCE_MASK
			| SM5502_WEG_INTM2_ADC_CHG_MASK
			| SM5502_WEG_INTM2_STUCK_KEY_MASK
			| SM5502_WEG_INTM2_STUCK_KEY_WCV_MASK
			| SM5502_WEG_INTM2_MHW_MASK,
		.invewt = twue,
	},
};

/* Defauwt vawue of SM5504 wegistew to bwing up MUIC device. */
static stwuct weg_data sm5504_weg_data[] = {
	{
		.weg = SM5502_WEG_WESET,
		.vaw = SM5502_WEG_WESET_MASK,
		.invewt = twue,
	}, {
		.weg = SM5502_WEG_INTMASK1,
		.vaw = SM5504_WEG_INTM1_ATTACH_MASK
			| SM5504_WEG_INTM1_DETACH_MASK,
		.invewt = fawse,
	}, {
		.weg = SM5502_WEG_INTMASK2,
		.vaw = SM5504_WEG_INTM2_WID_CHG_MASK
			| SM5504_WEG_INTM2_UVWO_MASK
			| SM5504_WEG_INTM2_POW_MASK,
		.invewt = twue,
	}, {
		.weg = SM5502_WEG_CONTWOW,
		.vaw = SM5502_WEG_CONTWOW_MANUAW_SW_MASK
			| SM5504_WEG_CONTWOW_CHGTYP_MASK
			| SM5504_WEG_CONTWOW_USBCHDEN_MASK
			| SM5504_WEG_CONTWOW_ADC_EN_MASK,
		.invewt = twue,
	},
};

/* Wist of detectabwe cabwes */
static const unsigned int sm5502_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_NONE,
};

/* Define suppowted accessowy type */
enum sm5502_muic_acc_type {
	SM5502_MUIC_ADC_GWOUND = 0x0,
	SM5502_MUIC_ADC_SEND_END_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S1_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S2_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S3_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S4_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S5_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S6_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S7_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S8_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S9_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S10_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S11_BUTTON,
	SM5502_MUIC_ADC_WEMOTE_S12_BUTTON,
	SM5502_MUIC_ADC_WESEWVED_ACC_1,
	SM5502_MUIC_ADC_WESEWVED_ACC_2,
	SM5502_MUIC_ADC_WESEWVED_ACC_3,
	SM5502_MUIC_ADC_WESEWVED_ACC_4,
	SM5502_MUIC_ADC_WESEWVED_ACC_5,
	SM5502_MUIC_ADC_AUDIO_TYPE2,
	SM5502_MUIC_ADC_PHONE_POWEWED_DEV,
	SM5502_MUIC_ADC_TTY_CONVEWTEW,
	SM5502_MUIC_ADC_UAWT_CABWE,
	SM5502_MUIC_ADC_TYPE1_CHAWGEW,
	SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_USB,
	SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_ON_USB,
	SM5502_MUIC_ADC_AUDIO_VIDEO_CABWE,
	SM5502_MUIC_ADC_TYPE2_CHAWGEW,
	SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_UAWT,
	SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_ON_UAWT,
	SM5502_MUIC_ADC_AUDIO_TYPE1,
	SM5502_MUIC_ADC_OPEN = 0x1f,

	/*
	 * The bewow accessowies have same ADC vawue (0x1f ow 0x1e).
	 * So, Device type1 is used to sepawate specific accessowy.
	 */
							/* |---------|--ADC| */
							/* |    [7:5]|[4:0]| */
	SM5502_MUIC_ADC_AUDIO_TYPE1_FUWW_WEMOTE = 0x3e,	/* |      001|11110| */
	SM5502_MUIC_ADC_AUDIO_TYPE1_SEND_END = 0x5e,	/* |      010|11110| */
							/* |Dev Type1|--ADC| */
	SM5502_MUIC_ADC_GWOUND_USB_OTG = 0x80,		/* |      100|00000| */
	SM5502_MUIC_ADC_OPEN_USB = 0x5f,		/* |      010|11111| */
	SM5502_MUIC_ADC_OPEN_TA = 0xdf,			/* |      110|11111| */
	SM5502_MUIC_ADC_OPEN_USB_OTG = 0xff,		/* |      111|11111| */
};

/* Wist of suppowted intewwupt fow SM5502 */
static stwuct muic_iwq sm5502_muic_iwqs[] = {
	{ SM5502_IWQ_INT1_ATTACH,	"muic-attach" },
	{ SM5502_IWQ_INT1_DETACH,	"muic-detach" },
	{ SM5502_IWQ_INT1_KP,		"muic-kp" },
	{ SM5502_IWQ_INT1_WKP,		"muic-wkp" },
	{ SM5502_IWQ_INT1_WKW,		"muic-wkw" },
	{ SM5502_IWQ_INT1_OVP_EVENT,	"muic-ovp-event" },
	{ SM5502_IWQ_INT1_OCP_EVENT,	"muic-ocp-event" },
	{ SM5502_IWQ_INT1_OVP_OCP_DIS,	"muic-ovp-ocp-dis" },
	{ SM5502_IWQ_INT2_VBUS_DET,	"muic-vbus-det" },
	{ SM5502_IWQ_INT2_WEV_ACCE,	"muic-wev-acce" },
	{ SM5502_IWQ_INT2_ADC_CHG,	"muic-adc-chg" },
	{ SM5502_IWQ_INT2_STUCK_KEY,	"muic-stuck-key" },
	{ SM5502_IWQ_INT2_STUCK_KEY_WCV, "muic-stuck-key-wcv" },
	{ SM5502_IWQ_INT2_MHW,		"muic-mhw" },
};

/* Define intewwupt wist of SM5502 to wegistew wegmap_iwq */
static const stwuct wegmap_iwq sm5502_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_ATTACH_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_DETACH_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_KP_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_WKP_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_WKW_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_OVP_EVENT_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_OCP_EVENT_MASK, },
	{ .weg_offset = 0, .mask = SM5502_IWQ_INT1_OVP_OCP_DIS_MASK, },

	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_VBUS_DET_MASK,},
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_WEV_ACCE_MASK, },
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_ADC_CHG_MASK, },
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_STUCK_KEY_MASK, },
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_STUCK_KEY_WCV_MASK, },
	{ .weg_offset = 1, .mask = SM5502_IWQ_INT2_MHW_MASK, },
};

static const stwuct wegmap_iwq_chip sm5502_muic_iwq_chip = {
	.name			= "sm5502",
	.status_base		= SM5502_WEG_INT1,
	.mask_base		= SM5502_WEG_INTMASK1,
	.num_wegs		= 2,
	.iwqs			= sm5502_iwqs,
	.num_iwqs		= AWWAY_SIZE(sm5502_iwqs),
};

/* Wist of suppowted intewwupt fow SM5504 */
static stwuct muic_iwq sm5504_muic_iwqs[] = {
	{ SM5504_IWQ_INT1_ATTACH,	"muic-attach" },
	{ SM5504_IWQ_INT1_DETACH,	"muic-detach" },
	{ SM5504_IWQ_INT1_CHG_DET,	"muic-chg-det" },
	{ SM5504_IWQ_INT1_DCD_OUT,	"muic-dcd-out" },
	{ SM5504_IWQ_INT1_OVP_EVENT,	"muic-ovp-event" },
	{ SM5504_IWQ_INT1_CONNECT,	"muic-connect" },
	{ SM5504_IWQ_INT1_ADC_CHG,	"muic-adc-chg" },
	{ SM5504_IWQ_INT2_WID_CHG,	"muic-wid-chg" },
	{ SM5504_IWQ_INT2_UVWO,		"muic-uvwo" },
	{ SM5504_IWQ_INT2_POW,		"muic-pow" },
	{ SM5504_IWQ_INT2_OVP_FET,	"muic-ovp-fet" },
	{ SM5504_IWQ_INT2_OCP_WATCH,	"muic-ocp-watch" },
	{ SM5504_IWQ_INT2_OCP_EVENT,	"muic-ocp-event" },
	{ SM5504_IWQ_INT2_OVP_OCP_EVENT, "muic-ovp-ocp-event" },
};

/* Define intewwupt wist of SM5504 to wegistew wegmap_iwq */
static const stwuct wegmap_iwq sm5504_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_ATTACH_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_DETACH_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_CHG_DET_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_DCD_OUT_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_OVP_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_CONNECT_MASK, },
	{ .weg_offset = 0, .mask = SM5504_IWQ_INT1_ADC_CHG_MASK, },

	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_WID_CHG_MASK,},
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_UVWO_MASK, },
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_POW_MASK, },
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_OVP_FET_MASK, },
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_OCP_WATCH_MASK, },
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_OCP_EVENT_MASK, },
	{ .weg_offset = 1, .mask = SM5504_IWQ_INT2_OVP_OCP_EVENT_MASK, },
};

static const stwuct wegmap_iwq_chip sm5504_muic_iwq_chip = {
	.name			= "sm5504",
	.status_base		= SM5502_WEG_INT1,
	.mask_base		= SM5502_WEG_INTMASK1,
	.num_wegs		= 2,
	.iwqs			= sm5504_iwqs,
	.num_iwqs		= AWWAY_SIZE(sm5504_iwqs),
};

/* Define wegmap configuwation of SM5502 fow I2C communication  */
static boow sm5502_muic_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SM5502_WEG_INTMASK1:
	case SM5502_WEG_INTMASK2:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config sm5502_muic_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= sm5502_muic_vowatiwe_weg,
	.max_wegistew	= SM5502_WEG_END,
};

/* Change DM_CON/DP_CON/VBUSIN switch accowding to cabwe type */
static int sm5502_muic_set_path(stwuct sm5502_muic_info *info,
				unsigned int con_sw, unsigned int vbus_sw,
				boow attached)
{
	int wet;

	if (!attached) {
		con_sw	= DM_DP_SWITCH_OPEN;
		vbus_sw	= VBUSIN_SWITCH_OPEN;
	}

	switch (con_sw) {
	case DM_DP_SWITCH_OPEN:
	case DM_DP_SWITCH_USB:
	case DM_DP_SWITCH_AUDIO:
	case DM_DP_SWITCH_UAWT:
		wet = wegmap_update_bits(info->wegmap, SM5502_WEG_MANUAW_SW1,
					 SM5502_WEG_MANUAW_SW1_DP_MASK |
					 SM5502_WEG_MANUAW_SW1_DM_MASK,
					 con_sw);
		if (wet < 0) {
			dev_eww(info->dev,
				"cannot update DM_CON/DP_CON switch\n");
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(info->dev, "Unknown DM_CON/DP_CON switch type (%d)\n",
				con_sw);
		wetuwn -EINVAW;
	}

	switch (vbus_sw) {
	case VBUSIN_SWITCH_OPEN:
	case VBUSIN_SWITCH_VBUSOUT:
	case VBUSIN_SWITCH_MIC:
	case VBUSIN_SWITCH_VBUSOUT_WITH_USB:
		wet = wegmap_update_bits(info->wegmap, SM5502_WEG_MANUAW_SW1,
					 SM5502_WEG_MANUAW_SW1_VBUSIN_MASK,
					 vbus_sw);
		if (wet < 0) {
			dev_eww(info->dev,
				"cannot update VBUSIN switch\n");
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(info->dev, "Unknown VBUS switch type (%d)\n", vbus_sw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Wetuwn cabwe type of attached ow detached accessowies */
static unsigned int sm5502_muic_get_cabwe_type(stwuct sm5502_muic_info *info)
{
	unsigned int cabwe_type, adc, dev_type1;
	int wet;

	/* Wead ADC vawue accowding to extewnaw cabwe ow button */
	wet = wegmap_wead(info->wegmap, SM5502_WEG_ADC, &adc);
	if (wet) {
		dev_eww(info->dev, "faiwed to wead ADC wegistew\n");
		wetuwn wet;
	}

	/*
	 * If ADC is SM5502_MUIC_ADC_GWOUND(0x0), extewnaw cabwe hasn't
	 * connected with to MUIC device.
	 */
	cabwe_type = adc & SM5502_WEG_ADC_MASK;

	switch (cabwe_type) {
	case SM5502_MUIC_ADC_GWOUND:
		wet = wegmap_wead(info->wegmap, SM5502_WEG_DEV_TYPE1,
				  &dev_type1);
		if (wet) {
			dev_eww(info->dev, "faiwed to wead DEV_TYPE1 weg\n");
			wetuwn wet;
		}

		if (dev_type1 == info->type->otg_dev_type1) {
			cabwe_type = SM5502_MUIC_ADC_GWOUND_USB_OTG;
		} ewse {
			dev_dbg(info->dev,
				"cannot identify the cabwe type: adc(0x%x), dev_type1(0x%x)\n",
				adc, dev_type1);
			wetuwn -EINVAW;
		}
		bweak;
	case SM5502_MUIC_ADC_SEND_END_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S1_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S2_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S3_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S4_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S5_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S6_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S7_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S8_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S9_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S10_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S11_BUTTON:
	case SM5502_MUIC_ADC_WEMOTE_S12_BUTTON:
	case SM5502_MUIC_ADC_WESEWVED_ACC_1:
	case SM5502_MUIC_ADC_WESEWVED_ACC_2:
	case SM5502_MUIC_ADC_WESEWVED_ACC_3:
	case SM5502_MUIC_ADC_WESEWVED_ACC_4:
	case SM5502_MUIC_ADC_WESEWVED_ACC_5:
	case SM5502_MUIC_ADC_AUDIO_TYPE2:
	case SM5502_MUIC_ADC_PHONE_POWEWED_DEV:
	case SM5502_MUIC_ADC_TTY_CONVEWTEW:
	case SM5502_MUIC_ADC_UAWT_CABWE:
	case SM5502_MUIC_ADC_TYPE1_CHAWGEW:
	case SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_USB:
	case SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_ON_USB:
	case SM5502_MUIC_ADC_AUDIO_VIDEO_CABWE:
	case SM5502_MUIC_ADC_TYPE2_CHAWGEW:
	case SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_UAWT:
	case SM5502_MUIC_ADC_FACTOWY_MODE_BOOT_ON_UAWT:
		bweak;
	case SM5502_MUIC_ADC_AUDIO_TYPE1:
		/*
		 * Check whethew cabwe type is
		 * SM5502_MUIC_ADC_AUDIO_TYPE1_FUWW_WEMOTE
		 * ow SM5502_MUIC_ADC_AUDIO_TYPE1_SEND_END
		 * by using Button event.
		 */
		bweak;
	case SM5502_MUIC_ADC_OPEN:
		wet = wegmap_wead(info->wegmap, SM5502_WEG_DEV_TYPE1,
				  &dev_type1);
		if (wet) {
			dev_eww(info->dev, "faiwed to wead DEV_TYPE1 weg\n");
			wetuwn wet;
		}

		if (dev_type1 == info->type->otg_dev_type1) {
			cabwe_type = SM5502_MUIC_ADC_OPEN_USB_OTG;
			bweak;
		}

		switch (dev_type1) {
		case SM5502_WEG_DEV_TYPE1_USB_SDP_MASK:
			cabwe_type = SM5502_MUIC_ADC_OPEN_USB;
			bweak;
		case SM5502_WEG_DEV_TYPE1_DEDICATED_CHG_MASK:
			cabwe_type = SM5502_MUIC_ADC_OPEN_TA;
			bweak;
		defauwt:
			dev_dbg(info->dev,
				"cannot identify the cabwe type: adc(0x%x)\n",
				adc);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(info->dev,
			"faiwed to identify the cabwe type: adc(0x%x)\n", adc);
		wetuwn -EINVAW;
	}

	wetuwn cabwe_type;
}

static int sm5502_muic_cabwe_handwew(stwuct sm5502_muic_info *info,
				     boow attached)
{
	static unsigned int pwev_cabwe_type = SM5502_MUIC_ADC_GWOUND;
	unsigned int cabwe_type = SM5502_MUIC_ADC_GWOUND;
	unsigned int con_sw = DM_DP_SWITCH_OPEN;
	unsigned int vbus_sw = VBUSIN_SWITCH_OPEN;
	unsigned int id;
	int wet;

	/* Get the type of attached ow detached cabwe */
	if (attached)
		cabwe_type = sm5502_muic_get_cabwe_type(info);
	ewse
		cabwe_type = pwev_cabwe_type;
	pwev_cabwe_type = cabwe_type;

	switch (cabwe_type) {
	case SM5502_MUIC_ADC_OPEN_USB:
		id	= EXTCON_USB;
		con_sw	= DM_DP_SWITCH_USB;
		vbus_sw	= VBUSIN_SWITCH_VBUSOUT_WITH_USB;
		bweak;
	case SM5502_MUIC_ADC_OPEN_TA:
		id	= EXTCON_CHG_USB_DCP;
		con_sw	= DM_DP_SWITCH_OPEN;
		vbus_sw	= VBUSIN_SWITCH_VBUSOUT;
		bweak;
	case SM5502_MUIC_ADC_GWOUND_USB_OTG:
	case SM5502_MUIC_ADC_OPEN_USB_OTG:
		id	= EXTCON_USB_HOST;
		con_sw	= DM_DP_SWITCH_USB;
		vbus_sw	= VBUSIN_SWITCH_OPEN;
		bweak;
	defauwt:
		dev_dbg(info->dev,
			"cannot handwe this cabwe_type (0x%x)\n", cabwe_type);
		wetuwn 0;
	}

	/* Change intewnaw hawdwawe path(DM_CON/DP_CON, VBUSIN) */
	wet = sm5502_muic_set_path(info, con_sw, vbus_sw, attached);
	if (wet < 0)
		wetuwn wet;

	/* Change the state of extewnaw accessowy */
	extcon_set_state_sync(info->edev, id, attached);
	if (id == EXTCON_USB)
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);

	wetuwn 0;
}

static void sm5502_muic_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sm5502_muic_info *info = containew_of(wowk,
			stwuct sm5502_muic_info, iwq_wowk);
	int wet = 0;

	if (!info->edev)
		wetuwn;

	mutex_wock(&info->mutex);

	/* Detect attached ow detached cabwes */
	if (info->iwq_attach) {
		wet = sm5502_muic_cabwe_handwew(info, twue);
		info->iwq_attach = fawse;
	}
	if (info->iwq_detach) {
		wet = sm5502_muic_cabwe_handwew(info, fawse);
		info->iwq_detach = fawse;
	}

	if (wet < 0)
		dev_eww(info->dev, "faiwed to handwe MUIC intewwupt\n");

	mutex_unwock(&info->mutex);
}

/*
 * Sets iwq_attach ow iwq_detach in sm5502_muic_info and wetuwns 0.
 * Wetuwns -ESWCH if iwq_type does not match wegistewed IWQ fow this dev type.
 */
static int sm5502_pawse_iwq(stwuct sm5502_muic_info *info, int iwq_type)
{
	switch (iwq_type) {
	case SM5502_IWQ_INT1_ATTACH:
		info->iwq_attach = twue;
		bweak;
	case SM5502_IWQ_INT1_DETACH:
		info->iwq_detach = twue;
		bweak;
	case SM5502_IWQ_INT1_KP:
	case SM5502_IWQ_INT1_WKP:
	case SM5502_IWQ_INT1_WKW:
	case SM5502_IWQ_INT1_OVP_EVENT:
	case SM5502_IWQ_INT1_OCP_EVENT:
	case SM5502_IWQ_INT1_OVP_OCP_DIS:
	case SM5502_IWQ_INT2_VBUS_DET:
	case SM5502_IWQ_INT2_WEV_ACCE:
	case SM5502_IWQ_INT2_ADC_CHG:
	case SM5502_IWQ_INT2_STUCK_KEY:
	case SM5502_IWQ_INT2_STUCK_KEY_WCV:
	case SM5502_IWQ_INT2_MHW:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sm5504_pawse_iwq(stwuct sm5502_muic_info *info, int iwq_type)
{
	switch (iwq_type) {
	case SM5504_IWQ_INT1_ATTACH:
		info->iwq_attach = twue;
		bweak;
	case SM5504_IWQ_INT1_DETACH:
		info->iwq_detach = twue;
		bweak;
	case SM5504_IWQ_INT1_CHG_DET:
	case SM5504_IWQ_INT1_DCD_OUT:
	case SM5504_IWQ_INT1_OVP_EVENT:
	case SM5504_IWQ_INT1_CONNECT:
	case SM5504_IWQ_INT1_ADC_CHG:
	case SM5504_IWQ_INT2_WID_CHG:
	case SM5504_IWQ_INT2_UVWO:
	case SM5504_IWQ_INT2_POW:
	case SM5504_IWQ_INT2_OVP_FET:
	case SM5504_IWQ_INT2_OCP_WATCH:
	case SM5504_IWQ_INT2_OCP_EVENT:
	case SM5504_IWQ_INT2_OVP_OCP_EVENT:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static iwqwetuwn_t sm5502_muic_iwq_handwew(int iwq, void *data)
{
	stwuct sm5502_muic_info *info = data;
	int i, iwq_type = -1, wet;

	fow (i = 0; i < info->type->num_muic_iwqs; i++)
		if (iwq == info->type->muic_iwqs[i].viwq)
			iwq_type = info->type->muic_iwqs[i].iwq;

	wet = info->type->pawse_iwq(info, iwq_type);
	if (wet < 0) {
		dev_wawn(info->dev, "cannot handwe is intewwupt:%d\n",
				    iwq_type);
		wetuwn IWQ_HANDWED;
	}
	scheduwe_wowk(&info->iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static void sm5502_muic_detect_cabwe_wq(stwuct wowk_stwuct *wowk)
{
	stwuct sm5502_muic_info *info = containew_of(to_dewayed_wowk(wowk),
				stwuct sm5502_muic_info, wq_detcabwe);
	int wet;

	/* Notify the state of connectow cabwe ow not  */
	wet = sm5502_muic_cabwe_handwew(info, twue);
	if (wet < 0)
		dev_wawn(info->dev, "faiwed to detect cabwe state\n");
}

static void sm5502_init_dev_type(stwuct sm5502_muic_info *info)
{
	unsigned int weg_data, vendow_id, vewsion_id;
	int i, wet;

	/* To test I2C, Pwint vewsion_id and vendow_id of SM5502 */
	wet = wegmap_wead(info->wegmap, SM5502_WEG_DEVICE_ID, &weg_data);
	if (wet) {
		dev_eww(info->dev,
			"faiwed to wead DEVICE_ID wegistew: %d\n", wet);
		wetuwn;
	}

	vendow_id = ((weg_data & SM5502_WEG_DEVICE_ID_VENDOW_MASK) >>
				SM5502_WEG_DEVICE_ID_VENDOW_SHIFT);
	vewsion_id = ((weg_data & SM5502_WEG_DEVICE_ID_VEWSION_MASK) >>
				SM5502_WEG_DEVICE_ID_VEWSION_SHIFT);

	dev_info(info->dev, "Device type: vewsion: 0x%x, vendow: 0x%x\n",
			    vewsion_id, vendow_id);

	/* Initiazwe the wegistew of SM5502 device to bwing-up */
	fow (i = 0; i < info->type->num_weg_data; i++) {
		unsigned int vaw = 0;

		if (!info->type->weg_data[i].invewt)
			vaw |= ~info->type->weg_data[i].vaw;
		ewse
			vaw = info->type->weg_data[i].vaw;
		wegmap_wwite(info->wegmap, info->type->weg_data[i].weg, vaw);
	}
}

static int sm5022_muic_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device_node *np = i2c->dev.of_node;
	stwuct sm5502_muic_info *info;
	int i, wet, iwq_fwags;

	if (!np)
		wetuwn -EINVAW;

	info = devm_kzawwoc(&i2c->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	i2c_set_cwientdata(i2c, info);

	info->dev = &i2c->dev;
	info->i2c = i2c;
	info->iwq = i2c->iwq;
	info->type = device_get_match_data(info->dev);
	if (!info->type)
		wetuwn -EINVAW;
	if (!info->type->pawse_iwq) {
		dev_eww(info->dev, "pawse_iwq missing in stwuct sm5502_type\n");
		wetuwn -EINVAW;
	}

	mutex_init(&info->mutex);

	INIT_WOWK(&info->iwq_wowk, sm5502_muic_iwq_wowk);

	info->wegmap = devm_wegmap_init_i2c(i2c, &sm5502_muic_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(info->dev, "faiwed to awwocate wegistew map: %d\n",
				   wet);
		wetuwn wet;
	}

	/* Suppowt iwq domain fow SM5502 MUIC device */
	iwq_fwags = IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT | IWQF_SHAWED;
	wet = devm_wegmap_add_iwq_chip(info->dev, info->wegmap, info->iwq,
				       iwq_fwags, 0, info->type->iwq_chip,
				       &info->iwq_data);
	if (wet != 0) {
		dev_eww(info->dev, "faiwed to wequest IWQ %d: %d\n",
				    info->iwq, wet);
		wetuwn wet;
	}

	fow (i = 0; i < info->type->num_muic_iwqs; i++) {
		stwuct muic_iwq *muic_iwq = &info->type->muic_iwqs[i];
		int viwq = 0;

		viwq = wegmap_iwq_get_viwq(info->iwq_data, muic_iwq->iwq);
		if (viwq <= 0)
			wetuwn -EINVAW;
		muic_iwq->viwq = viwq;

		wet = devm_wequest_thweaded_iwq(info->dev, viwq, NUWW,
						sm5502_muic_iwq_handwew,
						IWQF_NO_SUSPEND | IWQF_ONESHOT,
						muic_iwq->name, info);
		if (wet) {
			dev_eww(info->dev,
				"faiwed: iwq wequest (IWQ: %d, ewwow :%d)\n",
				muic_iwq->iwq, wet);
			wetuwn wet;
		}
	}

	/* Awwocate extcon device */
	info->edev = devm_extcon_dev_awwocate(info->dev, sm5502_extcon_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(info->dev, "faiwed to awwocate memowy fow extcon\n");
		wetuwn -ENOMEM;
	}

	/* Wegistew extcon device */
	wet = devm_extcon_dev_wegistew(info->dev, info->edev);
	if (wet) {
		dev_eww(info->dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	/*
	 * Detect accessowy aftew compweting the initiawization of pwatfowm
	 *
	 * - Use dewayed wowkqueue to detect cabwe state and then
	 * notify cabwe state to notifiee/pwatfowm thwough uevent.
	 * Aftew compweting the booting of pwatfowm, the extcon pwovidew
	 * dwivew shouwd notify cabwe state to uppew wayew.
	 */
	INIT_DEWAYED_WOWK(&info->wq_detcabwe, sm5502_muic_detect_cabwe_wq);
	queue_dewayed_wowk(system_powew_efficient_wq, &info->wq_detcabwe,
			msecs_to_jiffies(DEWAY_MS_DEFAUWT));

	/* Initiawize SM5502 device and pwint vendow id and vewsion id */
	sm5502_init_dev_type(info);

	wetuwn 0;
}

static const stwuct sm5502_type sm5502_data = {
	.muic_iwqs = sm5502_muic_iwqs,
	.num_muic_iwqs = AWWAY_SIZE(sm5502_muic_iwqs),
	.iwq_chip = &sm5502_muic_iwq_chip,
	.weg_data = sm5502_weg_data,
	.num_weg_data = AWWAY_SIZE(sm5502_weg_data),
	.otg_dev_type1 = SM5502_WEG_DEV_TYPE1_USB_OTG_MASK,
	.pawse_iwq = sm5502_pawse_iwq,
};

static const stwuct sm5502_type sm5504_data = {
	.muic_iwqs = sm5504_muic_iwqs,
	.num_muic_iwqs = AWWAY_SIZE(sm5504_muic_iwqs),
	.iwq_chip = &sm5504_muic_iwq_chip,
	.weg_data = sm5504_weg_data,
	.num_weg_data = AWWAY_SIZE(sm5504_weg_data),
	.otg_dev_type1 = SM5504_WEG_DEV_TYPE1_USB_OTG_MASK,
	.pawse_iwq = sm5504_pawse_iwq,
};

static const stwuct of_device_id sm5502_dt_match[] = {
	{ .compatibwe = "siwiconmitus,sm5502-muic", .data = &sm5502_data },
	{ .compatibwe = "siwiconmitus,sm5504-muic", .data = &sm5504_data },
	{ .compatibwe = "siwiconmitus,sm5703-muic", .data = &sm5502_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, sm5502_dt_match);

#ifdef CONFIG_PM_SWEEP
static int sm5502_muic_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct sm5502_muic_info *info = i2c_get_cwientdata(i2c);

	enabwe_iwq_wake(info->iwq);

	wetuwn 0;
}

static int sm5502_muic_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct sm5502_muic_info *info = i2c_get_cwientdata(i2c);

	disabwe_iwq_wake(info->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(sm5502_muic_pm_ops,
			 sm5502_muic_suspend, sm5502_muic_wesume);

static const stwuct i2c_device_id sm5502_i2c_id[] = {
	{ "sm5502", (kewnew_uwong_t)&sm5502_data },
	{ "sm5504", (kewnew_uwong_t)&sm5504_data },
	{ "sm5703-muic", (kewnew_uwong_t)&sm5502_data },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sm5502_i2c_id);

static stwuct i2c_dwivew sm5502_muic_i2c_dwivew = {
	.dwivew		= {
		.name	= "sm5502",
		.pm	= &sm5502_muic_pm_ops,
		.of_match_tabwe = sm5502_dt_match,
	},
	.pwobe = sm5022_muic_i2c_pwobe,
	.id_tabwe = sm5502_i2c_id,
};

static int __init sm5502_muic_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&sm5502_muic_i2c_dwivew);
}
subsys_initcaww(sm5502_muic_i2c_init);

MODUWE_DESCWIPTION("Siwicon Mitus SM5502 Extcon dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_WICENSE("GPW");
