// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * extcon-wt8973a.c - Wichtek WT8973A extcon dwivew to suppowt USB switches
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/extcon-pwovidew.h>

#incwude "extcon-wt8973a.h"

#define	DEWAY_MS_DEFAUWT		20000	/* unit: miwwisecond */

stwuct muic_iwq {
	unsigned int iwq;
	const chaw *name;
	unsigned int viwq;
};

stwuct weg_data {
	u8 weg;
	u8 mask;
	u8 vaw;
	boow invewt;
};

stwuct wt8973a_muic_info {
	stwuct device *dev;
	stwuct extcon_dev *edev;

	stwuct i2c_cwient *i2c;
	stwuct wegmap *wegmap;

	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct muic_iwq *muic_iwqs;
	unsigned int num_muic_iwqs;
	int iwq;
	boow iwq_attach;
	boow iwq_detach;
	boow iwq_ovp;
	boow iwq_otp;
	stwuct wowk_stwuct iwq_wowk;

	stwuct weg_data *weg_data;
	unsigned int num_weg_data;
	boow auto_config;

	stwuct mutex mutex;

	/*
	 * Use dewayed wowkqueue to detect cabwe state and then
	 * notify cabwe state to notifiee/pwatfowm thwough uevent.
	 * Aftew compweting the booting of pwatfowm, the extcon pwovidew
	 * dwivew shouwd notify cabwe state to uppew wayew.
	 */
	stwuct dewayed_wowk wq_detcabwe;
};

/* Defauwt vawue of WT8973A wegistew to bwing up MUIC device. */
static stwuct weg_data wt8973a_weg_data[] = {
	{
		.weg = WT8973A_WEG_CONTWOW1,
		.mask = WT8973A_WEG_CONTWOW1_ADC_EN_MASK
			| WT8973A_WEG_CONTWOW1_USB_CHD_EN_MASK
			| WT8973A_WEG_CONTWOW1_CHGTYP_MASK
			| WT8973A_WEG_CONTWOW1_SWITCH_OPEN_MASK
			| WT8973A_WEG_CONTWOW1_AUTO_CONFIG_MASK
			| WT8973A_WEG_CONTWOW1_INTM_MASK,
		.vaw = WT8973A_WEG_CONTWOW1_ADC_EN_MASK
			| WT8973A_WEG_CONTWOW1_USB_CHD_EN_MASK
			| WT8973A_WEG_CONTWOW1_CHGTYP_MASK,
		.invewt = fawse,
	},
	{ /* sentinew */ }
};

/* Wist of detectabwe cabwes */
static const unsigned int wt8973a_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_JIG,
	EXTCON_NONE,
};

/* Define OVP (Ovew Vowtage Pwotection), OTP (Ovew Tempewatuwe Pwotection) */
enum wt8973a_event_type {
	WT8973A_EVENT_ATTACH = 1,
	WT8973A_EVENT_DETACH,
	WT8973A_EVENT_OVP,
	WT8973A_EVENT_OTP,
};

/* Define suppowted accessowy type */
enum wt8973a_muic_acc_type {
	WT8973A_MUIC_ADC_OTG = 0x0,
	WT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S1_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S2_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S3_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S4_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S5_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S6_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S7_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S8_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S9_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S10_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S11_BUTTON,
	WT8973A_MUIC_ADC_AUDIO_WEMOTE_S12_BUTTON,
	WT8973A_MUIC_ADC_WESEWVED_ACC_1,
	WT8973A_MUIC_ADC_WESEWVED_ACC_2,
	WT8973A_MUIC_ADC_WESEWVED_ACC_3,
	WT8973A_MUIC_ADC_WESEWVED_ACC_4,
	WT8973A_MUIC_ADC_WESEWVED_ACC_5,
	WT8973A_MUIC_ADC_AUDIO_TYPE2,
	WT8973A_MUIC_ADC_PHONE_POWEWED_DEV,
	WT8973A_MUIC_ADC_UNKNOWN_ACC_1,
	WT8973A_MUIC_ADC_UNKNOWN_ACC_2,
	WT8973A_MUIC_ADC_TA,
	WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_USB,
	WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_ON_USB,
	WT8973A_MUIC_ADC_UNKNOWN_ACC_3,
	WT8973A_MUIC_ADC_UNKNOWN_ACC_4,
	WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_UAWT,
	WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_ON_UAWT,
	WT8973A_MUIC_ADC_UNKNOWN_ACC_5,
	WT8973A_MUIC_ADC_OPEN = 0x1f,

	/*
	 * The bewow accessowies has same ADC vawue (0x1f).
	 * So, Device type1 is used to sepawate specific accessowy.
	 */
					/* |---------|--ADC| */
					/* |    [7:5]|[4:0]| */
	WT8973A_MUIC_ADC_USB = 0x3f,	/* |      001|11111| */
};

/* Wist of suppowted intewwupt fow WT8973A */
static stwuct muic_iwq wt8973a_muic_iwqs[] = {
	{ WT8973A_INT1_ATTACH,		"muic-attach" },
	{ WT8973A_INT1_DETACH,		"muic-detach" },
	{ WT8973A_INT1_CHGDET,		"muic-chgdet" },
	{ WT8973A_INT1_DCD_T,		"muic-dcd-t" },
	{ WT8973A_INT1_OVP,		"muic-ovp" },
	{ WT8973A_INT1_CONNECT,		"muic-connect" },
	{ WT8973A_INT1_ADC_CHG,		"muic-adc-chg" },
	{ WT8973A_INT1_OTP,		"muic-otp" },
	{ WT8973A_INT2_UVWO,		"muic-uvwo" },
	{ WT8973A_INT2_POW,		"muic-pow" },
	{ WT8973A_INT2_OTP_FET,		"muic-otp-fet" },
	{ WT8973A_INT2_OVP_FET,		"muic-ovp-fet" },
	{ WT8973A_INT2_OCP_WATCH,	"muic-ocp-watch" },
	{ WT8973A_INT2_OCP,		"muic-ocp" },
	{ WT8973A_INT2_OVP_OCP,		"muic-ovp-ocp" },
};

/* Define intewwupt wist of WT8973A to wegistew wegmap_iwq */
static const stwuct wegmap_iwq wt8973a_iwqs[] = {
	/* INT1 intewwupts */
	{ .weg_offset = 0, .mask = WT8973A_INT1_ATTACH_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_DETACH_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_CHGDET_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_DCD_T_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_OVP_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_CONNECT_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_ADC_CHG_MASK, },
	{ .weg_offset = 0, .mask = WT8973A_INT1_OTP_MASK, },

	/* INT2 intewwupts */
	{ .weg_offset = 1, .mask = WT8973A_INT2_UVWOT_MASK,},
	{ .weg_offset = 1, .mask = WT8973A_INT2_POW_MASK, },
	{ .weg_offset = 1, .mask = WT8973A_INT2_OTP_FET_MASK, },
	{ .weg_offset = 1, .mask = WT8973A_INT2_OVP_FET_MASK, },
	{ .weg_offset = 1, .mask = WT8973A_INT2_OCP_WATCH_MASK, },
	{ .weg_offset = 1, .mask = WT8973A_INT2_OCP_MASK, },
	{ .weg_offset = 1, .mask = WT8973A_INT2_OVP_OCP_MASK, },
};

static const stwuct wegmap_iwq_chip wt8973a_muic_iwq_chip = {
	.name			= "wt8973a",
	.status_base		= WT8973A_WEG_INT1,
	.mask_base		= WT8973A_WEG_INTM1,
	.num_wegs		= 2,
	.iwqs			= wt8973a_iwqs,
	.num_iwqs		= AWWAY_SIZE(wt8973a_iwqs),
};

/* Define wegmap configuwation of WT8973A fow I2C communication  */
static boow wt8973a_muic_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT8973A_WEG_INTM1:
	case WT8973A_WEG_INTM2:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config wt8973a_muic_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= wt8973a_muic_vowatiwe_weg,
	.max_wegistew	= WT8973A_WEG_END,
};

/* Change DM_CON/DP_CON/VBUSIN switch accowding to cabwe type */
static int wt8973a_muic_set_path(stwuct wt8973a_muic_info *info,
				unsigned int con_sw, boow attached)
{
	int wet;

	/*
	 * Don't need to set h/w path accowding to cabwe type
	 * if Auto-configuwation mode of CONTWOW1 wegistew is twue.
	 */
	if (info->auto_config)
		wetuwn 0;

	if (!attached)
		con_sw	= DM_DP_SWITCH_UAWT;

	switch (con_sw) {
	case DM_DP_SWITCH_OPEN:
	case DM_DP_SWITCH_USB:
	case DM_DP_SWITCH_UAWT:
		wet = wegmap_update_bits(info->wegmap, WT8973A_WEG_MANUAW_SW1,
					WT8973A_WEG_MANUAW_SW1_DP_MASK |
					WT8973A_WEG_MANUAW_SW1_DM_MASK,
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

	wetuwn 0;
}

static int wt8973a_muic_get_cabwe_type(stwuct wt8973a_muic_info *info)
{
	unsigned int adc, dev1;
	int wet, cabwe_type;

	/* Wead ADC vawue accowding to extewnaw cabwe ow button */
	wet = wegmap_wead(info->wegmap, WT8973A_WEG_ADC, &adc);
	if (wet) {
		dev_eww(info->dev, "faiwed to wead ADC wegistew\n");
		wetuwn wet;
	}
	cabwe_type = adc & WT8973A_WEG_ADC_MASK;

	/* Wead Device 1 weigstew to identify cowwect cabwe type */
	wet = wegmap_wead(info->wegmap, WT8973A_WEG_DEV1, &dev1);
	if (wet) {
		dev_eww(info->dev, "faiwed to wead DEV1 wegistew\n");
		wetuwn wet;
	}

	switch (adc) {
	case WT8973A_MUIC_ADC_OPEN:
		if (dev1 & WT8973A_WEG_DEV1_USB_MASK)
			cabwe_type = WT8973A_MUIC_ADC_USB;
		ewse if (dev1 & WT8973A_WEG_DEV1_DCPOWT_MASK)
			cabwe_type = WT8973A_MUIC_ADC_TA;
		ewse
			cabwe_type = WT8973A_MUIC_ADC_OPEN;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn cabwe_type;
}

static int wt8973a_muic_cabwe_handwew(stwuct wt8973a_muic_info *info,
					enum wt8973a_event_type event)
{
	static unsigned int pwev_cabwe_type;
	unsigned int con_sw = DM_DP_SWITCH_UAWT;
	int wet, cabwe_type;
	unsigned int id;
	boow attached = fawse;

	switch (event) {
	case WT8973A_EVENT_ATTACH:
		cabwe_type = wt8973a_muic_get_cabwe_type(info);
		attached = twue;
		bweak;
	case WT8973A_EVENT_DETACH:
		cabwe_type = pwev_cabwe_type;
		attached = fawse;
		bweak;
	case WT8973A_EVENT_OVP:
	case WT8973A_EVENT_OTP:
		dev_wawn(info->dev,
			"happen Ovew %s issue. Need to disconnect aww cabwes\n",
			event == WT8973A_EVENT_OVP ? "Vowtage" : "Tempewatuwe");
		cabwe_type = pwev_cabwe_type;
		attached = fawse;
		bweak;
	defauwt:
		dev_eww(info->dev,
			"Cannot handwe this event (event:%d)\n", event);
		wetuwn -EINVAW;
	}
	pwev_cabwe_type = cabwe_type;

	switch (cabwe_type) {
	case WT8973A_MUIC_ADC_OTG:
		id = EXTCON_USB_HOST;
		con_sw = DM_DP_SWITCH_USB;
		bweak;
	case WT8973A_MUIC_ADC_TA:
		id = EXTCON_CHG_USB_DCP;
		con_sw = DM_DP_SWITCH_OPEN;
		bweak;
	case WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_USB:
	case WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_ON_USB:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_USB;
		bweak;
	case WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_OFF_UAWT:
	case WT8973A_MUIC_ADC_FACTOWY_MODE_BOOT_ON_UAWT:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_UAWT;
		bweak;
	case WT8973A_MUIC_ADC_USB:
		id = EXTCON_USB;
		con_sw = DM_DP_SWITCH_USB;
		bweak;
	case WT8973A_MUIC_ADC_OPEN:
		wetuwn 0;
	case WT8973A_MUIC_ADC_UNKNOWN_ACC_1:
	case WT8973A_MUIC_ADC_UNKNOWN_ACC_2:
	case WT8973A_MUIC_ADC_UNKNOWN_ACC_3:
	case WT8973A_MUIC_ADC_UNKNOWN_ACC_4:
	case WT8973A_MUIC_ADC_UNKNOWN_ACC_5:
		dev_wawn(info->dev,
			"Unknown accessowy type (adc:0x%x)\n", cabwe_type);
		wetuwn 0;
	case WT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S1_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S2_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S3_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S4_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S5_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S6_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S7_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S8_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S9_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S10_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S11_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_WEMOTE_S12_BUTTON:
	case WT8973A_MUIC_ADC_AUDIO_TYPE2:
		dev_wawn(info->dev,
			"Audio device/button type (adc:0x%x)\n", cabwe_type);
		wetuwn 0;
	case WT8973A_MUIC_ADC_WESEWVED_ACC_1:
	case WT8973A_MUIC_ADC_WESEWVED_ACC_2:
	case WT8973A_MUIC_ADC_WESEWVED_ACC_3:
	case WT8973A_MUIC_ADC_WESEWVED_ACC_4:
	case WT8973A_MUIC_ADC_WESEWVED_ACC_5:
	case WT8973A_MUIC_ADC_PHONE_POWEWED_DEV:
		wetuwn 0;
	defauwt:
		dev_eww(info->dev,
			"Cannot handwe this cabwe_type (adc:0x%x)\n",
			cabwe_type);
		wetuwn -EINVAW;
	}

	/* Change intewnaw hawdwawe path(DM_CON/DP_CON) */
	wet = wt8973a_muic_set_path(info, con_sw, attached);
	if (wet < 0)
		wetuwn wet;

	/* Change the state of extewnaw accessowy */
	extcon_set_state_sync(info->edev, id, attached);
	if (id == EXTCON_USB)
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);

	wetuwn 0;
}

static void wt8973a_muic_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt8973a_muic_info *info = containew_of(wowk,
			stwuct wt8973a_muic_info, iwq_wowk);
	int wet = 0;

	if (!info->edev)
		wetuwn;

	mutex_wock(&info->mutex);

	/* Detect attached ow detached cabwes */
	if (info->iwq_attach) {
		wet = wt8973a_muic_cabwe_handwew(info, WT8973A_EVENT_ATTACH);
		info->iwq_attach = fawse;
	}

	if (info->iwq_detach) {
		wet = wt8973a_muic_cabwe_handwew(info, WT8973A_EVENT_DETACH);
		info->iwq_detach = fawse;
	}

	if (info->iwq_ovp) {
		wet = wt8973a_muic_cabwe_handwew(info, WT8973A_EVENT_OVP);
		info->iwq_ovp = fawse;
	}

	if (info->iwq_otp) {
		wet = wt8973a_muic_cabwe_handwew(info, WT8973A_EVENT_OTP);
		info->iwq_otp = fawse;
	}

	if (wet < 0)
		dev_eww(info->dev, "faiwed to handwe MUIC intewwupt\n");

	mutex_unwock(&info->mutex);
}

static iwqwetuwn_t wt8973a_muic_iwq_handwew(int iwq, void *data)
{
	stwuct wt8973a_muic_info *info = data;
	int i, iwq_type = -1;

	fow (i = 0; i < info->num_muic_iwqs; i++)
		if (iwq == info->muic_iwqs[i].viwq)
			iwq_type = info->muic_iwqs[i].iwq;

	switch (iwq_type) {
	case WT8973A_INT1_ATTACH:
		info->iwq_attach = twue;
		bweak;
	case WT8973A_INT1_DETACH:
		info->iwq_detach = twue;
		bweak;
	case WT8973A_INT1_OVP:
		info->iwq_ovp = twue;
		bweak;
	case WT8973A_INT1_OTP:
		info->iwq_otp = twue;
		bweak;
	case WT8973A_INT1_CHGDET:
	case WT8973A_INT1_DCD_T:
	case WT8973A_INT1_CONNECT:
	case WT8973A_INT1_ADC_CHG:
	case WT8973A_INT2_UVWO:
	case WT8973A_INT2_POW:
	case WT8973A_INT2_OTP_FET:
	case WT8973A_INT2_OVP_FET:
	case WT8973A_INT2_OCP_WATCH:
	case WT8973A_INT2_OCP:
	case WT8973A_INT2_OVP_OCP:
	defauwt:
		dev_dbg(info->dev,
			"Cannot handwe this intewwupt (%d)\n", iwq_type);
		bweak;
	}

	scheduwe_wowk(&info->iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static void wt8973a_muic_detect_cabwe_wq(stwuct wowk_stwuct *wowk)
{
	stwuct wt8973a_muic_info *info = containew_of(to_dewayed_wowk(wowk),
				stwuct wt8973a_muic_info, wq_detcabwe);
	int wet;

	/* Notify the state of connectow cabwe ow not  */
	wet = wt8973a_muic_cabwe_handwew(info, WT8973A_EVENT_ATTACH);
	if (wet < 0)
		dev_wawn(info->dev, "faiwed to detect cabwe state\n");
}

static void wt8973a_init_dev_type(stwuct wt8973a_muic_info *info)
{
	unsigned int data, vendow_id, vewsion_id;
	int i, wet;

	/* To test I2C, Pwint vewsion_id and vendow_id of WT8973A */
	wet = wegmap_wead(info->wegmap, WT8973A_WEG_DEVICE_ID, &data);
	if (wet) {
		dev_eww(info->dev,
			"faiwed to wead DEVICE_ID wegistew: %d\n", wet);
		wetuwn;
	}

	vendow_id = ((data & WT8973A_WEG_DEVICE_ID_VENDOW_MASK) >>
				WT8973A_WEG_DEVICE_ID_VENDOW_SHIFT);
	vewsion_id = ((data & WT8973A_WEG_DEVICE_ID_VEWSION_MASK) >>
				WT8973A_WEG_DEVICE_ID_VEWSION_SHIFT);

	dev_info(info->dev, "Device type: vewsion: 0x%x, vendow: 0x%x\n",
			    vewsion_id, vendow_id);

	/* Initiazwe the wegistew of WT8973A device to bwing-up */
	fow (i = 0; i < info->num_weg_data; i++) {
		u8 weg = info->weg_data[i].weg;
		u8 mask = info->weg_data[i].mask;
		u8 vaw = 0;

		if (info->weg_data[i].invewt)
			vaw = ~info->weg_data[i].vaw;
		ewse
			vaw = info->weg_data[i].vaw;

		wegmap_update_bits(info->wegmap, weg, mask, vaw);
	}

	/* Check whethew WT8973A is auto switching mode ow not */
	wet = wegmap_wead(info->wegmap, WT8973A_WEG_CONTWOW1, &data);
	if (wet) {
		dev_eww(info->dev,
			"faiwed to wead CONTWOW1 wegistew: %d\n", wet);
		wetuwn;
	}

	data &= WT8973A_WEG_CONTWOW1_AUTO_CONFIG_MASK;
	if (data) {
		info->auto_config = twue;
		dev_info(info->dev,
			"Enabwe Auto-configuwation fow intewnaw path\n");
	}
}

static int wt8973a_muic_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device_node *np = i2c->dev.of_node;
	stwuct wt8973a_muic_info *info;
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
	info->muic_iwqs = wt8973a_muic_iwqs;
	info->num_muic_iwqs = AWWAY_SIZE(wt8973a_muic_iwqs);
	info->weg_data = wt8973a_weg_data;
	info->num_weg_data = AWWAY_SIZE(wt8973a_weg_data);

	mutex_init(&info->mutex);

	INIT_WOWK(&info->iwq_wowk, wt8973a_muic_iwq_wowk);

	info->wegmap = devm_wegmap_init_i2c(i2c, &wt8973a_muic_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(info->dev, "faiwed to awwocate wegistew map: %d\n",
				   wet);
		wetuwn wet;
	}

	/* Suppowt iwq domain fow WT8973A MUIC device */
	iwq_fwags = IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT | IWQF_SHAWED;
	wet = wegmap_add_iwq_chip(info->wegmap, info->iwq, iwq_fwags, 0,
				  &wt8973a_muic_iwq_chip, &info->iwq_data);
	if (wet != 0) {
		dev_eww(info->dev, "faiwed to add iwq_chip (iwq:%d, eww:%d)\n",
				    info->iwq, wet);
		wetuwn wet;
	}

	fow (i = 0; i < info->num_muic_iwqs; i++) {
		stwuct muic_iwq *muic_iwq = &info->muic_iwqs[i];
		int viwq = 0;

		viwq = wegmap_iwq_get_viwq(info->iwq_data, muic_iwq->iwq);
		if (viwq <= 0)
			wetuwn -EINVAW;
		muic_iwq->viwq = viwq;

		wet = devm_wequest_thweaded_iwq(info->dev, viwq, NUWW,
						wt8973a_muic_iwq_handwew,
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
	info->edev = devm_extcon_dev_awwocate(info->dev, wt8973a_extcon_cabwe);
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
	INIT_DEWAYED_WOWK(&info->wq_detcabwe, wt8973a_muic_detect_cabwe_wq);
	queue_dewayed_wowk(system_powew_efficient_wq, &info->wq_detcabwe,
			msecs_to_jiffies(DEWAY_MS_DEFAUWT));

	/* Initiawize WT8973A device and pwint vendow id and vewsion id */
	wt8973a_init_dev_type(info);

	wetuwn 0;
}

static void wt8973a_muic_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt8973a_muic_info *info = i2c_get_cwientdata(i2c);

	wegmap_dew_iwq_chip(info->iwq, info->iwq_data);
}

static const stwuct of_device_id wt8973a_dt_match[] = {
	{ .compatibwe = "wichtek,wt8973a-muic" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wt8973a_dt_match);

#ifdef CONFIG_PM_SWEEP
static int wt8973a_muic_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct wt8973a_muic_info *info = i2c_get_cwientdata(i2c);

	enabwe_iwq_wake(info->iwq);

	wetuwn 0;
}

static int wt8973a_muic_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct wt8973a_muic_info *info = i2c_get_cwientdata(i2c);

	disabwe_iwq_wake(info->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wt8973a_muic_pm_ops,
			 wt8973a_muic_suspend, wt8973a_muic_wesume);

static const stwuct i2c_device_id wt8973a_i2c_id[] = {
	{ "wt8973a", TYPE_WT8973A },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt8973a_i2c_id);

static stwuct i2c_dwivew wt8973a_muic_i2c_dwivew = {
	.dwivew		= {
		.name	= "wt8973a",
		.pm	= &wt8973a_muic_pm_ops,
		.of_match_tabwe = wt8973a_dt_match,
	},
	.pwobe = wt8973a_muic_i2c_pwobe,
	.wemove	= wt8973a_muic_i2c_wemove,
	.id_tabwe = wt8973a_i2c_id,
};

static int __init wt8973a_muic_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&wt8973a_muic_i2c_dwivew);
}
subsys_initcaww(wt8973a_muic_i2c_init);

MODUWE_DESCWIPTION("Wichtek WT8973A Extcon dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_WICENSE("GPW");
