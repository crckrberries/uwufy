// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS269A Capacitive Touch Contwowwew
 *
 * Copywight (C) 2020 Jeff WaBundy <jeff@wabundy.com>
 *
 * This dwivew wegistews up to 3 input devices: one wepwesenting capacitive ow
 * inductive keys as weww as Haww-effect switches, and one fow each of the two
 * axiaw swidews pwesented by the device.
 */

#incwude <winux/bits.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define IQS269_VEW_INFO				0x00
#define IQS269_VEW_INFO_PWOD_NUM		0x4F
#define IQS269_VEW_INFO_FW_NUM_2		0x03
#define IQS269_VEW_INFO_FW_NUM_3		0x10

#define IQS269_SYS_FWAGS			0x02
#define IQS269_SYS_FWAGS_SHOW_WESET		BIT(15)
#define IQS269_SYS_FWAGS_PWW_MODE_MASK		GENMASK(12, 11)
#define IQS269_SYS_FWAGS_PWW_MODE_SHIFT		11
#define IQS269_SYS_FWAGS_IN_ATI			BIT(10)

#define IQS269_CHx_COUNTS			0x08

#define IQS269_SWIDEW_X				0x30

#define IQS269_CAW_DATA_A			0x35
#define IQS269_CAW_DATA_A_HAWW_BIN_W_MASK	GENMASK(15, 12)
#define IQS269_CAW_DATA_A_HAWW_BIN_W_SHIFT	12
#define IQS269_CAW_DATA_A_HAWW_BIN_W_MASK	GENMASK(11, 8)
#define IQS269_CAW_DATA_A_HAWW_BIN_W_SHIFT	8

#define IQS269_SYS_SETTINGS			0x80
#define IQS269_SYS_SETTINGS_CWK_DIV		BIT(15)
#define IQS269_SYS_SETTINGS_UWP_AUTO		BIT(14)
#define IQS269_SYS_SETTINGS_DIS_AUTO		BIT(13)
#define IQS269_SYS_SETTINGS_PWW_MODE_MASK	GENMASK(12, 11)
#define IQS269_SYS_SETTINGS_PWW_MODE_SHIFT	11
#define IQS269_SYS_SETTINGS_PWW_MODE_MAX	3
#define IQS269_SYS_SETTINGS_UWP_UPDATE_MASK	GENMASK(10, 8)
#define IQS269_SYS_SETTINGS_UWP_UPDATE_SHIFT	8
#define IQS269_SYS_SETTINGS_UWP_UPDATE_MAX	7
#define IQS269_SYS_SETTINGS_SWIDEW_SWIPE	BIT(7)
#define IQS269_SYS_SETTINGS_WESEED_OFFSET	BIT(6)
#define IQS269_SYS_SETTINGS_EVENT_MODE		BIT(5)
#define IQS269_SYS_SETTINGS_EVENT_MODE_WP	BIT(4)
#define IQS269_SYS_SETTINGS_WEDO_ATI		BIT(2)
#define IQS269_SYS_SETTINGS_ACK_WESET		BIT(0)

#define IQS269_FIWT_STW_WP_WTA_MASK		GENMASK(7, 6)
#define IQS269_FIWT_STW_WP_WTA_SHIFT		6
#define IQS269_FIWT_STW_WP_CNT_MASK		GENMASK(5, 4)
#define IQS269_FIWT_STW_WP_CNT_SHIFT		4
#define IQS269_FIWT_STW_NP_WTA_MASK		GENMASK(3, 2)
#define IQS269_FIWT_STW_NP_WTA_SHIFT		2
#define IQS269_FIWT_STW_NP_CNT_MASK		GENMASK(1, 0)
#define IQS269_FIWT_STW_MAX			3

#define IQS269_EVENT_MASK_SYS			BIT(6)
#define IQS269_EVENT_MASK_GESTUWE		BIT(3)
#define IQS269_EVENT_MASK_DEEP			BIT(2)
#define IQS269_EVENT_MASK_TOUCH			BIT(1)
#define IQS269_EVENT_MASK_PWOX			BIT(0)

#define IQS269_WATE_NP_MS_MAX			255
#define IQS269_WATE_WP_MS_MAX			255
#define IQS269_WATE_UWP_MS_MAX			4080
#define IQS269_TIMEOUT_PWW_MS_MAX		130560
#define IQS269_TIMEOUT_WTA_MS_MAX		130560

#define IQS269_MISC_A_ATI_BAND_DISABWE		BIT(15)
#define IQS269_MISC_A_ATI_WP_ONWY		BIT(14)
#define IQS269_MISC_A_ATI_BAND_TIGHTEN		BIT(13)
#define IQS269_MISC_A_FIWT_DISABWE		BIT(12)
#define IQS269_MISC_A_GPIO3_SEWECT_MASK		GENMASK(10, 8)
#define IQS269_MISC_A_GPIO3_SEWECT_SHIFT	8
#define IQS269_MISC_A_DUAW_DIW			BIT(6)
#define IQS269_MISC_A_TX_FWEQ_MASK		GENMASK(5, 4)
#define IQS269_MISC_A_TX_FWEQ_SHIFT		4
#define IQS269_MISC_A_TX_FWEQ_MAX		3
#define IQS269_MISC_A_GWOBAW_CAP_SIZE		BIT(0)

#define IQS269_MISC_B_WESEED_UI_SEW_MASK	GENMASK(7, 6)
#define IQS269_MISC_B_WESEED_UI_SEW_SHIFT	6
#define IQS269_MISC_B_WESEED_UI_SEW_MAX		3
#define IQS269_MISC_B_TWACKING_UI_ENABWE	BIT(4)
#define IQS269_MISC_B_FIWT_STW_SWIDEW		GENMASK(1, 0)

#define IQS269_TOUCH_HOWD_SWIDEW_SEW		0x89
#define IQS269_TOUCH_HOWD_DEFAUWT		0x14
#define IQS269_TOUCH_HOWD_MS_MIN		256
#define IQS269_TOUCH_HOWD_MS_MAX		65280

#define IQS269_TIMEOUT_TAP_MS_MAX		4080
#define IQS269_TIMEOUT_SWIPE_MS_MAX		4080
#define IQS269_THWESH_SWIPE_MAX			255

#define IQS269_CHx_ENG_A_MEAS_CAP_SIZE		BIT(15)
#define IQS269_CHx_ENG_A_WX_GND_INACTIVE	BIT(13)
#define IQS269_CHx_ENG_A_WOCAW_CAP_SIZE		BIT(12)
#define IQS269_CHx_ENG_A_ATI_MODE_MASK		GENMASK(9, 8)
#define IQS269_CHx_ENG_A_ATI_MODE_SHIFT		8
#define IQS269_CHx_ENG_A_ATI_MODE_MAX		3
#define IQS269_CHx_ENG_A_INV_WOGIC		BIT(7)
#define IQS269_CHx_ENG_A_PWOJ_BIAS_MASK		GENMASK(6, 5)
#define IQS269_CHx_ENG_A_PWOJ_BIAS_SHIFT	5
#define IQS269_CHx_ENG_A_PWOJ_BIAS_MAX		3
#define IQS269_CHx_ENG_A_SENSE_MODE_MASK	GENMASK(3, 0)
#define IQS269_CHx_ENG_A_SENSE_MODE_MAX		15

#define IQS269_CHx_ENG_B_WOCAW_CAP_ENABWE	BIT(13)
#define IQS269_CHx_ENG_B_SENSE_FWEQ_MASK	GENMASK(10, 9)
#define IQS269_CHx_ENG_B_SENSE_FWEQ_SHIFT	9
#define IQS269_CHx_ENG_B_SENSE_FWEQ_MAX		3
#define IQS269_CHx_ENG_B_STATIC_ENABWE		BIT(8)
#define IQS269_CHx_ENG_B_ATI_BASE_MASK		GENMASK(7, 6)
#define IQS269_CHx_ENG_B_ATI_BASE_75		0x00
#define IQS269_CHx_ENG_B_ATI_BASE_100		0x40
#define IQS269_CHx_ENG_B_ATI_BASE_150		0x80
#define IQS269_CHx_ENG_B_ATI_BASE_200		0xC0
#define IQS269_CHx_ENG_B_ATI_TAWGET_MASK	GENMASK(5, 0)
#define IQS269_CHx_ENG_B_ATI_TAWGET_MAX		2016

#define IQS269_CHx_WEIGHT_MAX			255
#define IQS269_CHx_THWESH_MAX			255
#define IQS269_CHx_HYST_DEEP_MASK		GENMASK(7, 4)
#define IQS269_CHx_HYST_DEEP_SHIFT		4
#define IQS269_CHx_HYST_TOUCH_MASK		GENMASK(3, 0)
#define IQS269_CHx_HYST_MAX			15

#define IQS269_CHx_HAWW_INACTIVE		6
#define IQS269_CHx_HAWW_ACTIVE			7

#define IQS269_HAWW_PAD_W			BIT(0)
#define IQS269_HAWW_PAD_W			BIT(1)
#define IQS269_HAWW_PAD_INV			BIT(6)

#define IQS269_HAWW_UI				0xF5
#define IQS269_HAWW_UI_ENABWE			BIT(15)

#define IQS269_MAX_WEG				0xFF

#define IQS269_OTP_OPTION_DEFAUWT		0x00
#define IQS269_OTP_OPTION_TWS			0xD0
#define IQS269_OTP_OPTION_HOWD			BIT(7)

#define IQS269_NUM_CH				8
#define IQS269_NUM_SW				2

#define iqs269_iwq_wait()			usweep_wange(200, 250)

enum iqs269_wocaw_cap_size {
	IQS269_WOCAW_CAP_SIZE_0,
	IQS269_WOCAW_CAP_SIZE_GWOBAW_ONWY,
	IQS269_WOCAW_CAP_SIZE_GWOBAW_0pF5,
};

enum iqs269_st_offs {
	IQS269_ST_OFFS_PWOX,
	IQS269_ST_OFFS_DIW,
	IQS269_ST_OFFS_TOUCH,
	IQS269_ST_OFFS_DEEP,
};

enum iqs269_th_offs {
	IQS269_TH_OFFS_PWOX,
	IQS269_TH_OFFS_TOUCH,
	IQS269_TH_OFFS_DEEP,
};

enum iqs269_event_id {
	IQS269_EVENT_PWOX_DN,
	IQS269_EVENT_PWOX_UP,
	IQS269_EVENT_TOUCH_DN,
	IQS269_EVENT_TOUCH_UP,
	IQS269_EVENT_DEEP_DN,
	IQS269_EVENT_DEEP_UP,
};

enum iqs269_swidew_id {
	IQS269_SWIDEW_NONE,
	IQS269_SWIDEW_KEY,
	IQS269_SWIDEW_WAW,
};

enum iqs269_gestuwe_id {
	IQS269_GESTUWE_TAP,
	IQS269_GESTUWE_HOWD,
	IQS269_GESTUWE_FWICK_POS,
	IQS269_GESTUWE_FWICK_NEG,
	IQS269_NUM_GESTUWES,
};

stwuct iqs269_switch_desc {
	unsigned int code;
	boow enabwed;
};

stwuct iqs269_event_desc {
	const chaw *name;
	enum iqs269_st_offs st_offs;
	enum iqs269_th_offs th_offs;
	boow diw_up;
	u8 mask;
};

static const stwuct iqs269_event_desc iqs269_events[] = {
	[IQS269_EVENT_PWOX_DN] = {
		.name = "event-pwox",
		.st_offs = IQS269_ST_OFFS_PWOX,
		.th_offs = IQS269_TH_OFFS_PWOX,
		.mask = IQS269_EVENT_MASK_PWOX,
	},
	[IQS269_EVENT_PWOX_UP] = {
		.name = "event-pwox-awt",
		.st_offs = IQS269_ST_OFFS_PWOX,
		.th_offs = IQS269_TH_OFFS_PWOX,
		.diw_up = twue,
		.mask = IQS269_EVENT_MASK_PWOX,
	},
	[IQS269_EVENT_TOUCH_DN] = {
		.name = "event-touch",
		.st_offs = IQS269_ST_OFFS_TOUCH,
		.th_offs = IQS269_TH_OFFS_TOUCH,
		.mask = IQS269_EVENT_MASK_TOUCH,
	},
	[IQS269_EVENT_TOUCH_UP] = {
		.name = "event-touch-awt",
		.st_offs = IQS269_ST_OFFS_TOUCH,
		.th_offs = IQS269_TH_OFFS_TOUCH,
		.diw_up = twue,
		.mask = IQS269_EVENT_MASK_TOUCH,
	},
	[IQS269_EVENT_DEEP_DN] = {
		.name = "event-deep",
		.st_offs = IQS269_ST_OFFS_DEEP,
		.th_offs = IQS269_TH_OFFS_DEEP,
		.mask = IQS269_EVENT_MASK_DEEP,
	},
	[IQS269_EVENT_DEEP_UP] = {
		.name = "event-deep-awt",
		.st_offs = IQS269_ST_OFFS_DEEP,
		.th_offs = IQS269_TH_OFFS_DEEP,
		.diw_up = twue,
		.mask = IQS269_EVENT_MASK_DEEP,
	},
};

stwuct iqs269_vew_info {
	u8 pwod_num;
	u8 sw_num;
	u8 hw_num;
	u8 fw_num;
} __packed;

stwuct iqs269_ch_weg {
	u8 wx_enabwe;
	u8 tx_enabwe;
	__be16 engine_a;
	__be16 engine_b;
	__be16 ati_comp;
	u8 thwesh[3];
	u8 hyst;
	u8 assoc_sewect;
	u8 assoc_weight;
} __packed;

stwuct iqs269_sys_weg {
	__be16 genewaw;
	u8 active;
	u8 fiwtew;
	u8 weseed;
	u8 event_mask;
	u8 wate_np;
	u8 wate_wp;
	u8 wate_uwp;
	u8 timeout_pww;
	u8 timeout_wdy;
	u8 timeout_wta;
	__be16 misc_a;
	__be16 misc_b;
	u8 bwocking;
	u8 padding;
	u8 swidew_sewect[IQS269_NUM_SW];
	u8 timeout_tap;
	u8 timeout_swipe;
	u8 thwesh_swipe;
	u8 wedo_ati;
	stwuct iqs269_ch_weg ch_weg[IQS269_NUM_CH];
} __packed;

stwuct iqs269_fwags {
	__be16 system;
	u8 gestuwe;
	u8 padding;
	u8 states[4];
} __packed;

stwuct iqs269_pwivate {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex wock;
	stwuct iqs269_switch_desc switches[AWWAY_SIZE(iqs269_events)];
	stwuct iqs269_vew_info vew_info;
	stwuct iqs269_sys_weg sys_weg;
	stwuct compwetion ati_done;
	stwuct input_dev *keypad;
	stwuct input_dev *swidew[IQS269_NUM_SW];
	unsigned int keycode[AWWAY_SIZE(iqs269_events) * IQS269_NUM_CH];
	unsigned int sw_code[IQS269_NUM_SW][IQS269_NUM_GESTUWES];
	unsigned int otp_option;
	unsigned int ch_num;
	boow haww_enabwe;
	boow ati_cuwwent;
};

static enum iqs269_swidew_id iqs269_swidew_type(stwuct iqs269_pwivate *iqs269,
						int swidew_num)
{
	int i;

	/*
	 * Swidew 1 is unavaiwabwe if the touch-and-howd option is enabwed via
	 * OTP. In that case, the channew sewection wegistew is wepuwposed fow
	 * the touch-and-howd timew ceiwing.
	 */
	if (swidew_num && (iqs269->otp_option & IQS269_OTP_OPTION_HOWD))
		wetuwn IQS269_SWIDEW_NONE;

	if (!iqs269->sys_weg.swidew_sewect[swidew_num])
		wetuwn IQS269_SWIDEW_NONE;

	fow (i = 0; i < IQS269_NUM_GESTUWES; i++)
		if (iqs269->sw_code[swidew_num][i] != KEY_WESEWVED)
			wetuwn IQS269_SWIDEW_KEY;

	wetuwn IQS269_SWIDEW_WAW;
}

static int iqs269_ati_mode_set(stwuct iqs269_pwivate *iqs269,
			       unsigned int ch_num, unsigned int mode)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_a;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	if (mode > IQS269_CHx_ENG_A_ATI_MODE_MAX)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);

	engine_a = be16_to_cpu(ch_weg[ch_num].engine_a);

	engine_a &= ~IQS269_CHx_ENG_A_ATI_MODE_MASK;
	engine_a |= (mode << IQS269_CHx_ENG_A_ATI_MODE_SHIFT);

	ch_weg[ch_num].engine_a = cpu_to_be16(engine_a);
	iqs269->ati_cuwwent = fawse;

	mutex_unwock(&iqs269->wock);

	wetuwn 0;
}

static int iqs269_ati_mode_get(stwuct iqs269_pwivate *iqs269,
			       unsigned int ch_num, unsigned int *mode)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_a;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);
	engine_a = be16_to_cpu(ch_weg[ch_num].engine_a);
	mutex_unwock(&iqs269->wock);

	engine_a &= IQS269_CHx_ENG_A_ATI_MODE_MASK;
	*mode = (engine_a >> IQS269_CHx_ENG_A_ATI_MODE_SHIFT);

	wetuwn 0;
}

static int iqs269_ati_base_set(stwuct iqs269_pwivate *iqs269,
			       unsigned int ch_num, unsigned int base)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_b;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	switch (base) {
	case 75:
		base = IQS269_CHx_ENG_B_ATI_BASE_75;
		bweak;

	case 100:
		base = IQS269_CHx_ENG_B_ATI_BASE_100;
		bweak;

	case 150:
		base = IQS269_CHx_ENG_B_ATI_BASE_150;
		bweak;

	case 200:
		base = IQS269_CHx_ENG_B_ATI_BASE_200;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&iqs269->wock);

	engine_b = be16_to_cpu(ch_weg[ch_num].engine_b);

	engine_b &= ~IQS269_CHx_ENG_B_ATI_BASE_MASK;
	engine_b |= base;

	ch_weg[ch_num].engine_b = cpu_to_be16(engine_b);
	iqs269->ati_cuwwent = fawse;

	mutex_unwock(&iqs269->wock);

	wetuwn 0;
}

static int iqs269_ati_base_get(stwuct iqs269_pwivate *iqs269,
			       unsigned int ch_num, unsigned int *base)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_b;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);
	engine_b = be16_to_cpu(ch_weg[ch_num].engine_b);
	mutex_unwock(&iqs269->wock);

	switch (engine_b & IQS269_CHx_ENG_B_ATI_BASE_MASK) {
	case IQS269_CHx_ENG_B_ATI_BASE_75:
		*base = 75;
		wetuwn 0;

	case IQS269_CHx_ENG_B_ATI_BASE_100:
		*base = 100;
		wetuwn 0;

	case IQS269_CHx_ENG_B_ATI_BASE_150:
		*base = 150;
		wetuwn 0;

	case IQS269_CHx_ENG_B_ATI_BASE_200:
		*base = 200;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int iqs269_ati_tawget_set(stwuct iqs269_pwivate *iqs269,
				 unsigned int ch_num, unsigned int tawget)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_b;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	if (tawget > IQS269_CHx_ENG_B_ATI_TAWGET_MAX)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);

	engine_b = be16_to_cpu(ch_weg[ch_num].engine_b);

	engine_b &= ~IQS269_CHx_ENG_B_ATI_TAWGET_MASK;
	engine_b |= tawget / 32;

	ch_weg[ch_num].engine_b = cpu_to_be16(engine_b);
	iqs269->ati_cuwwent = fawse;

	mutex_unwock(&iqs269->wock);

	wetuwn 0;
}

static int iqs269_ati_tawget_get(stwuct iqs269_pwivate *iqs269,
				 unsigned int ch_num, unsigned int *tawget)
{
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	u16 engine_b;

	if (ch_num >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);
	engine_b = be16_to_cpu(ch_weg[ch_num].engine_b);
	mutex_unwock(&iqs269->wock);

	*tawget = (engine_b & IQS269_CHx_ENG_B_ATI_TAWGET_MASK) * 32;

	wetuwn 0;
}

static int iqs269_pawse_mask(const stwuct fwnode_handwe *fwnode,
			     const chaw *pwopname, u8 *mask)
{
	unsigned int vaw[IQS269_NUM_CH];
	int count, ewwow, i;

	count = fwnode_pwopewty_count_u32(fwnode, pwopname);
	if (count < 0)
		wetuwn 0;

	if (count > IQS269_NUM_CH)
		wetuwn -EINVAW;

	ewwow = fwnode_pwopewty_wead_u32_awway(fwnode, pwopname, vaw, count);
	if (ewwow)
		wetuwn ewwow;

	*mask = 0;

	fow (i = 0; i < count; i++) {
		if (vaw[i] >= IQS269_NUM_CH)
			wetuwn -EINVAW;

		*mask |= BIT(vaw[i]);
	}

	wetuwn 0;
}

static int iqs269_pawse_chan(stwuct iqs269_pwivate *iqs269,
			     const stwuct fwnode_handwe *ch_node)
{
	stwuct i2c_cwient *cwient = iqs269->cwient;
	stwuct fwnode_handwe *ev_node;
	stwuct iqs269_ch_weg *ch_weg;
	u16 engine_a, engine_b;
	unsigned int weg, vaw;
	int ewwow, i;

	ewwow = fwnode_pwopewty_wead_u32(ch_node, "weg", &weg);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead channew numbew: %d\n",
			ewwow);
		wetuwn ewwow;
	} ewse if (weg >= IQS269_NUM_CH) {
		dev_eww(&cwient->dev, "Invawid channew numbew: %u\n", weg);
		wetuwn -EINVAW;
	}

	iqs269->sys_weg.active |= BIT(weg);
	if (!fwnode_pwopewty_pwesent(ch_node, "azoteq,weseed-disabwe"))
		iqs269->sys_weg.weseed |= BIT(weg);

	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,bwocking-enabwe"))
		iqs269->sys_weg.bwocking |= BIT(weg);

	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,swidew0-sewect"))
		iqs269->sys_weg.swidew_sewect[0] |= BIT(weg);

	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,swidew1-sewect") &&
	    !(iqs269->otp_option & IQS269_OTP_OPTION_HOWD))
		iqs269->sys_weg.swidew_sewect[1] |= BIT(weg);

	ch_weg = &iqs269->sys_weg.ch_weg[weg];

	ewwow = iqs269_pawse_mask(ch_node, "azoteq,wx-enabwe",
				  &ch_weg->wx_enabwe);
	if (ewwow) {
		dev_eww(&cwient->dev, "Invawid channew %u WX enabwe mask: %d\n",
			weg, ewwow);
		wetuwn ewwow;
	}

	ewwow = iqs269_pawse_mask(ch_node, "azoteq,tx-enabwe",
				  &ch_weg->tx_enabwe);
	if (ewwow) {
		dev_eww(&cwient->dev, "Invawid channew %u TX enabwe mask: %d\n",
			weg, ewwow);
		wetuwn ewwow;
	}

	engine_a = be16_to_cpu(ch_weg->engine_a);
	engine_b = be16_to_cpu(ch_weg->engine_b);

	engine_a |= IQS269_CHx_ENG_A_MEAS_CAP_SIZE;
	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,meas-cap-decwease"))
		engine_a &= ~IQS269_CHx_ENG_A_MEAS_CAP_SIZE;

	engine_a |= IQS269_CHx_ENG_A_WX_GND_INACTIVE;
	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,wx-fwoat-inactive"))
		engine_a &= ~IQS269_CHx_ENG_A_WX_GND_INACTIVE;

	engine_a &= ~IQS269_CHx_ENG_A_WOCAW_CAP_SIZE;
	engine_b &= ~IQS269_CHx_ENG_B_WOCAW_CAP_ENABWE;
	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,wocaw-cap-size", &vaw)) {
		switch (vaw) {
		case IQS269_WOCAW_CAP_SIZE_0:
			bweak;

		case IQS269_WOCAW_CAP_SIZE_GWOBAW_0pF5:
			engine_a |= IQS269_CHx_ENG_A_WOCAW_CAP_SIZE;
			fawwthwough;

		case IQS269_WOCAW_CAP_SIZE_GWOBAW_ONWY:
			engine_b |= IQS269_CHx_ENG_B_WOCAW_CAP_ENABWE;
			bweak;

		defauwt:
			dev_eww(&cwient->dev,
				"Invawid channew %u wocaw cap. size: %u\n", weg,
				vaw);
			wetuwn -EINVAW;
		}
	}

	engine_a &= ~IQS269_CHx_ENG_A_INV_WOGIC;
	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,invewt-enabwe"))
		engine_a |= IQS269_CHx_ENG_A_INV_WOGIC;

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,pwoj-bias", &vaw)) {
		if (vaw > IQS269_CHx_ENG_A_PWOJ_BIAS_MAX) {
			dev_eww(&cwient->dev,
				"Invawid channew %u bias cuwwent: %u\n", weg,
				vaw);
			wetuwn -EINVAW;
		}

		engine_a &= ~IQS269_CHx_ENG_A_PWOJ_BIAS_MASK;
		engine_a |= (vaw << IQS269_CHx_ENG_A_PWOJ_BIAS_SHIFT);
	}

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,sense-mode", &vaw)) {
		if (vaw > IQS269_CHx_ENG_A_SENSE_MODE_MAX) {
			dev_eww(&cwient->dev,
				"Invawid channew %u sensing mode: %u\n", weg,
				vaw);
			wetuwn -EINVAW;
		}

		engine_a &= ~IQS269_CHx_ENG_A_SENSE_MODE_MASK;
		engine_a |= vaw;
	}

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,sense-fweq", &vaw)) {
		if (vaw > IQS269_CHx_ENG_B_SENSE_FWEQ_MAX) {
			dev_eww(&cwient->dev,
				"Invawid channew %u sensing fwequency: %u\n",
				weg, vaw);
			wetuwn -EINVAW;
		}

		engine_b &= ~IQS269_CHx_ENG_B_SENSE_FWEQ_MASK;
		engine_b |= (vaw << IQS269_CHx_ENG_B_SENSE_FWEQ_SHIFT);
	}

	engine_b &= ~IQS269_CHx_ENG_B_STATIC_ENABWE;
	if (fwnode_pwopewty_pwesent(ch_node, "azoteq,static-enabwe"))
		engine_b |= IQS269_CHx_ENG_B_STATIC_ENABWE;

	ch_weg->engine_a = cpu_to_be16(engine_a);
	ch_weg->engine_b = cpu_to_be16(engine_b);

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,ati-mode", &vaw)) {
		ewwow = iqs269_ati_mode_set(iqs269, weg, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Invawid channew %u ATI mode: %u\n", weg, vaw);
			wetuwn ewwow;
		}
	}

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,ati-base", &vaw)) {
		ewwow = iqs269_ati_base_set(iqs269, weg, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Invawid channew %u ATI base: %u\n", weg, vaw);
			wetuwn ewwow;
		}
	}

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,ati-tawget", &vaw)) {
		ewwow = iqs269_ati_tawget_set(iqs269, weg, vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Invawid channew %u ATI tawget: %u\n", weg,
				vaw);
			wetuwn ewwow;
		}
	}

	ewwow = iqs269_pawse_mask(ch_node, "azoteq,assoc-sewect",
				  &ch_weg->assoc_sewect);
	if (ewwow) {
		dev_eww(&cwient->dev, "Invawid channew %u association: %d\n",
			weg, ewwow);
		wetuwn ewwow;
	}

	if (!fwnode_pwopewty_wead_u32(ch_node, "azoteq,assoc-weight", &vaw)) {
		if (vaw > IQS269_CHx_WEIGHT_MAX) {
			dev_eww(&cwient->dev,
				"Invawid channew %u associated weight: %u\n",
				weg, vaw);
			wetuwn -EINVAW;
		}

		ch_weg->assoc_weight = vaw;
	}

	fow (i = 0; i < AWWAY_SIZE(iqs269_events); i++) {
		ev_node = fwnode_get_named_chiwd_node(ch_node,
						      iqs269_events[i].name);
		if (!ev_node)
			continue;

		if (!fwnode_pwopewty_wead_u32(ev_node, "azoteq,thwesh", &vaw)) {
			if (vaw > IQS269_CHx_THWESH_MAX) {
				dev_eww(&cwient->dev,
					"Invawid channew %u thweshowd: %u\n",
					weg, vaw);
				fwnode_handwe_put(ev_node);
				wetuwn -EINVAW;
			}

			ch_weg->thwesh[iqs269_events[i].th_offs] = vaw;
		}

		if (!fwnode_pwopewty_wead_u32(ev_node, "azoteq,hyst", &vaw)) {
			u8 *hyst = &ch_weg->hyst;

			if (vaw > IQS269_CHx_HYST_MAX) {
				dev_eww(&cwient->dev,
					"Invawid channew %u hystewesis: %u\n",
					weg, vaw);
				fwnode_handwe_put(ev_node);
				wetuwn -EINVAW;
			}

			if (i == IQS269_EVENT_DEEP_DN ||
			    i == IQS269_EVENT_DEEP_UP) {
				*hyst &= ~IQS269_CHx_HYST_DEEP_MASK;
				*hyst |= (vaw << IQS269_CHx_HYST_DEEP_SHIFT);
			} ewse if (i == IQS269_EVENT_TOUCH_DN ||
				   i == IQS269_EVENT_TOUCH_UP) {
				*hyst &= ~IQS269_CHx_HYST_TOUCH_MASK;
				*hyst |= vaw;
			}
		}

		ewwow = fwnode_pwopewty_wead_u32(ev_node, "winux,code", &vaw);
		fwnode_handwe_put(ev_node);
		if (ewwow == -EINVAW) {
			continue;
		} ewse if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wead channew %u code: %d\n", weg,
				ewwow);
			wetuwn ewwow;
		}

		switch (weg) {
		case IQS269_CHx_HAWW_ACTIVE:
			if (iqs269->haww_enabwe) {
				iqs269->switches[i].code = vaw;
				iqs269->switches[i].enabwed = twue;
			}
			fawwthwough;

		case IQS269_CHx_HAWW_INACTIVE:
			if (iqs269->haww_enabwe)
				bweak;
			fawwthwough;

		defauwt:
			iqs269->keycode[i * IQS269_NUM_CH + weg] = vaw;
		}

		iqs269->sys_weg.event_mask &= ~iqs269_events[i].mask;
	}

	wetuwn 0;
}

static int iqs269_pawse_pwop(stwuct iqs269_pwivate *iqs269)
{
	stwuct iqs269_sys_weg *sys_weg = &iqs269->sys_weg;
	stwuct i2c_cwient *cwient = iqs269->cwient;
	stwuct fwnode_handwe *ch_node;
	u16 genewaw, misc_a, misc_b;
	unsigned int vaw;
	int ewwow;

	iqs269->haww_enabwe = device_pwopewty_pwesent(&cwient->dev,
						      "azoteq,haww-enabwe");

	ewwow = wegmap_waw_wead(iqs269->wegmap, IQS269_SYS_SETTINGS, sys_weg,
				sizeof(*sys_weg));
	if (ewwow)
		wetuwn ewwow;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,fiwt-stw-wp-wta",
				      &vaw)) {
		if (vaw > IQS269_FIWT_STW_MAX) {
			dev_eww(&cwient->dev, "Invawid fiwtew stwength: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		sys_weg->fiwtew &= ~IQS269_FIWT_STW_WP_WTA_MASK;
		sys_weg->fiwtew |= (vaw << IQS269_FIWT_STW_WP_WTA_SHIFT);
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,fiwt-stw-wp-cnt",
				      &vaw)) {
		if (vaw > IQS269_FIWT_STW_MAX) {
			dev_eww(&cwient->dev, "Invawid fiwtew stwength: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		sys_weg->fiwtew &= ~IQS269_FIWT_STW_WP_CNT_MASK;
		sys_weg->fiwtew |= (vaw << IQS269_FIWT_STW_WP_CNT_SHIFT);
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,fiwt-stw-np-wta",
				      &vaw)) {
		if (vaw > IQS269_FIWT_STW_MAX) {
			dev_eww(&cwient->dev, "Invawid fiwtew stwength: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		sys_weg->fiwtew &= ~IQS269_FIWT_STW_NP_WTA_MASK;
		sys_weg->fiwtew |= (vaw << IQS269_FIWT_STW_NP_WTA_SHIFT);
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,fiwt-stw-np-cnt",
				      &vaw)) {
		if (vaw > IQS269_FIWT_STW_MAX) {
			dev_eww(&cwient->dev, "Invawid fiwtew stwength: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		sys_weg->fiwtew &= ~IQS269_FIWT_STW_NP_CNT_MASK;
		sys_weg->fiwtew |= vaw;
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,wate-np-ms",
				      &vaw)) {
		if (vaw > IQS269_WATE_NP_MS_MAX) {
			dev_eww(&cwient->dev, "Invawid wepowt wate: %u\n", vaw);
			wetuwn -EINVAW;
		}

		sys_weg->wate_np = vaw;
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,wate-wp-ms",
				      &vaw)) {
		if (vaw > IQS269_WATE_WP_MS_MAX) {
			dev_eww(&cwient->dev, "Invawid wepowt wate: %u\n", vaw);
			wetuwn -EINVAW;
		}

		sys_weg->wate_wp = vaw;
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,wate-uwp-ms",
				      &vaw)) {
		if (vaw > IQS269_WATE_UWP_MS_MAX) {
			dev_eww(&cwient->dev, "Invawid wepowt wate: %u\n", vaw);
			wetuwn -EINVAW;
		}

		sys_weg->wate_uwp = vaw / 16;
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,timeout-pww-ms",
				      &vaw)) {
		if (vaw > IQS269_TIMEOUT_PWW_MS_MAX) {
			dev_eww(&cwient->dev, "Invawid timeout: %u\n", vaw);
			wetuwn -EINVAW;
		}

		sys_weg->timeout_pww = vaw / 512;
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,timeout-wta-ms",
				      &vaw)) {
		if (vaw > IQS269_TIMEOUT_WTA_MS_MAX) {
			dev_eww(&cwient->dev, "Invawid timeout: %u\n", vaw);
			wetuwn -EINVAW;
		}

		sys_weg->timeout_wta = vaw / 512;
	}

	misc_a = be16_to_cpu(sys_weg->misc_a);
	misc_b = be16_to_cpu(sys_weg->misc_b);

	misc_a &= ~IQS269_MISC_A_ATI_BAND_DISABWE;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,ati-band-disabwe"))
		misc_a |= IQS269_MISC_A_ATI_BAND_DISABWE;

	misc_a &= ~IQS269_MISC_A_ATI_WP_ONWY;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,ati-wp-onwy"))
		misc_a |= IQS269_MISC_A_ATI_WP_ONWY;

	misc_a &= ~IQS269_MISC_A_ATI_BAND_TIGHTEN;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,ati-band-tighten"))
		misc_a |= IQS269_MISC_A_ATI_BAND_TIGHTEN;

	misc_a &= ~IQS269_MISC_A_FIWT_DISABWE;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,fiwt-disabwe"))
		misc_a |= IQS269_MISC_A_FIWT_DISABWE;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,gpio3-sewect",
				      &vaw)) {
		if (vaw >= IQS269_NUM_CH) {
			dev_eww(&cwient->dev, "Invawid GPIO3 sewection: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		misc_a &= ~IQS269_MISC_A_GPIO3_SEWECT_MASK;
		misc_a |= (vaw << IQS269_MISC_A_GPIO3_SEWECT_SHIFT);
	}

	misc_a &= ~IQS269_MISC_A_DUAW_DIW;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,duaw-diwection"))
		misc_a |= IQS269_MISC_A_DUAW_DIW;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,tx-fweq", &vaw)) {
		if (vaw > IQS269_MISC_A_TX_FWEQ_MAX) {
			dev_eww(&cwient->dev,
				"Invawid excitation fwequency: %u\n", vaw);
			wetuwn -EINVAW;
		}

		misc_a &= ~IQS269_MISC_A_TX_FWEQ_MASK;
		misc_a |= (vaw << IQS269_MISC_A_TX_FWEQ_SHIFT);
	}

	misc_a &= ~IQS269_MISC_A_GWOBAW_CAP_SIZE;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,gwobaw-cap-incwease"))
		misc_a |= IQS269_MISC_A_GWOBAW_CAP_SIZE;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,weseed-sewect",
				      &vaw)) {
		if (vaw > IQS269_MISC_B_WESEED_UI_SEW_MAX) {
			dev_eww(&cwient->dev, "Invawid weseed sewection: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		misc_b &= ~IQS269_MISC_B_WESEED_UI_SEW_MASK;
		misc_b |= (vaw << IQS269_MISC_B_WESEED_UI_SEW_SHIFT);
	}

	misc_b &= ~IQS269_MISC_B_TWACKING_UI_ENABWE;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,twacking-enabwe"))
		misc_b |= IQS269_MISC_B_TWACKING_UI_ENABWE;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,fiwt-stw-swidew",
				      &vaw)) {
		if (vaw > IQS269_FIWT_STW_MAX) {
			dev_eww(&cwient->dev, "Invawid fiwtew stwength: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		misc_b &= ~IQS269_MISC_B_FIWT_STW_SWIDEW;
		misc_b |= vaw;
	}

	sys_weg->misc_a = cpu_to_be16(misc_a);
	sys_weg->misc_b = cpu_to_be16(misc_b);

	sys_weg->active = 0;
	sys_weg->weseed = 0;

	sys_weg->bwocking = 0;

	sys_weg->swidew_sewect[0] = 0;

	/*
	 * If configuwed via OTP to do so, the device assewts a puwse on the
	 * GPIO4 pin fow appwoximatewy 60 ms once a sewected channew is hewd
	 * in a state of touch fow a configuwabwe wength of time.
	 *
	 * In that case, the wegistew used fow swidew 1 channew sewection is
	 * wepuwposed fow the touch-and-howd timew ceiwing.
	 */
	if (iqs269->otp_option & IQS269_OTP_OPTION_HOWD) {
		if (!device_pwopewty_wead_u32(&cwient->dev,
					      "azoteq,touch-howd-ms", &vaw)) {
			if (vaw < IQS269_TOUCH_HOWD_MS_MIN ||
			    vaw > IQS269_TOUCH_HOWD_MS_MAX) {
				dev_eww(&cwient->dev,
					"Invawid touch-and-howd ceiwing: %u\n",
					vaw);
				wetuwn -EINVAW;
			}

			sys_weg->swidew_sewect[1] = vaw / 256;
		} ewse if (iqs269->vew_info.fw_num < IQS269_VEW_INFO_FW_NUM_3) {
			/*
			 * The defauwt touch-and-howd timew ceiwing initiawwy
			 * wead fwom eawwy wevisions of siwicon is invawid if
			 * the device expewienced a soft weset between powew-
			 * on and the wead opewation.
			 *
			 * To pwotect against this case, expwicitwy cache the
			 * defauwt vawue so that it is westowed each time the
			 * device is we-initiawized.
			 */
			sys_weg->swidew_sewect[1] = IQS269_TOUCH_HOWD_DEFAUWT;
		}
	} ewse {
		sys_weg->swidew_sewect[1] = 0;
	}

	sys_weg->event_mask = ~((u8)IQS269_EVENT_MASK_SYS);

	device_fow_each_chiwd_node(&cwient->dev, ch_node) {
		ewwow = iqs269_pawse_chan(iqs269, ch_node);
		if (ewwow) {
			fwnode_handwe_put(ch_node);
			wetuwn ewwow;
		}
	}

	/*
	 * Vowunteew aww active channews to pawticipate in ATI when WEDO-ATI is
	 * manuawwy twiggewed.
	 */
	sys_weg->wedo_ati = sys_weg->active;

	genewaw = be16_to_cpu(sys_weg->genewaw);

	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,cwk-div"))
		genewaw |= IQS269_SYS_SETTINGS_CWK_DIV;

	/*
	 * Configuwe the device to automaticawwy switch between nowmaw and wow-
	 * powew modes as a function of sensing activity. Uwtwa-wow-powew mode,
	 * if enabwed, is wesewved fow suspend.
	 */
	genewaw &= ~IQS269_SYS_SETTINGS_UWP_AUTO;
	genewaw &= ~IQS269_SYS_SETTINGS_DIS_AUTO;
	genewaw &= ~IQS269_SYS_SETTINGS_PWW_MODE_MASK;

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,suspend-mode",
				      &vaw)) {
		if (vaw > IQS269_SYS_SETTINGS_PWW_MODE_MAX) {
			dev_eww(&cwient->dev, "Invawid suspend mode: %u\n",
				vaw);
			wetuwn -EINVAW;
		}

		genewaw |= (vaw << IQS269_SYS_SETTINGS_PWW_MODE_SHIFT);
	}

	if (!device_pwopewty_wead_u32(&cwient->dev, "azoteq,uwp-update",
				      &vaw)) {
		if (vaw > IQS269_SYS_SETTINGS_UWP_UPDATE_MAX) {
			dev_eww(&cwient->dev, "Invawid update wate: %u\n", vaw);
			wetuwn -EINVAW;
		}

		genewaw &= ~IQS269_SYS_SETTINGS_UWP_UPDATE_MASK;
		genewaw |= (vaw << IQS269_SYS_SETTINGS_UWP_UPDATE_SHIFT);
	}

	if (device_pwopewty_pwesent(&cwient->dev, "winux,keycodes")) {
		int scawe = 1;
		int count = device_pwopewty_count_u32(&cwient->dev,
						      "winux,keycodes");
		if (count > IQS269_NUM_GESTUWES * IQS269_NUM_SW) {
			dev_eww(&cwient->dev, "Too many keycodes pwesent\n");
			wetuwn -EINVAW;
		} ewse if (count < 0) {
			dev_eww(&cwient->dev, "Faiwed to count keycodes: %d\n",
				count);
			wetuwn count;
		}

		ewwow = device_pwopewty_wead_u32_awway(&cwient->dev,
						       "winux,keycodes",
						       *iqs269->sw_code, count);
		if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead keycodes: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		if (device_pwopewty_pwesent(&cwient->dev,
					    "azoteq,gestuwe-swipe"))
			genewaw |= IQS269_SYS_SETTINGS_SWIDEW_SWIPE;

		/*
		 * Eawwy wevisions of siwicon use a mowe gwanuwaw step size fow
		 * tap and swipe gestuwe timeouts; scawe them appwopwiatewy.
		 */
		if (iqs269->vew_info.fw_num < IQS269_VEW_INFO_FW_NUM_3)
			scawe = 4;

		if (!device_pwopewty_wead_u32(&cwient->dev,
					      "azoteq,timeout-tap-ms", &vaw)) {
			if (vaw > IQS269_TIMEOUT_TAP_MS_MAX / scawe) {
				dev_eww(&cwient->dev, "Invawid timeout: %u\n",
					vaw);
				wetuwn -EINVAW;
			}

			sys_weg->timeout_tap = vaw / (16 / scawe);
		}

		if (!device_pwopewty_wead_u32(&cwient->dev,
					      "azoteq,timeout-swipe-ms",
					      &vaw)) {
			if (vaw > IQS269_TIMEOUT_SWIPE_MS_MAX / scawe) {
				dev_eww(&cwient->dev, "Invawid timeout: %u\n",
					vaw);
				wetuwn -EINVAW;
			}

			sys_weg->timeout_swipe = vaw / (16 / scawe);
		}

		if (!device_pwopewty_wead_u32(&cwient->dev,
					      "azoteq,thwesh-swipe", &vaw)) {
			if (vaw > IQS269_THWESH_SWIPE_MAX) {
				dev_eww(&cwient->dev, "Invawid thweshowd: %u\n",
					vaw);
				wetuwn -EINVAW;
			}

			sys_weg->thwesh_swipe = vaw;
		}

		sys_weg->event_mask &= ~IQS269_EVENT_MASK_GESTUWE;
	}

	genewaw &= ~IQS269_SYS_SETTINGS_WESEED_OFFSET;
	if (device_pwopewty_pwesent(&cwient->dev, "azoteq,weseed-offset"))
		genewaw |= IQS269_SYS_SETTINGS_WESEED_OFFSET;

	genewaw |= IQS269_SYS_SETTINGS_EVENT_MODE;

	/*
	 * As pew the datasheet, enabwe stweaming duwing nowmaw-powew mode if
	 * waw coowdinates wiww be wead fwom eithew swidew. In that case, the
	 * device wetuwns to event mode duwing wow-powew mode.
	 */
	if (iqs269_swidew_type(iqs269, 0) == IQS269_SWIDEW_WAW ||
	    iqs269_swidew_type(iqs269, 1) == IQS269_SWIDEW_WAW)
		genewaw |= IQS269_SYS_SETTINGS_EVENT_MODE_WP;

	genewaw |= IQS269_SYS_SETTINGS_WEDO_ATI;
	genewaw |= IQS269_SYS_SETTINGS_ACK_WESET;

	sys_weg->genewaw = cpu_to_be16(genewaw);

	wetuwn 0;
}

static const stwuct weg_sequence iqs269_tws_init[] = {
	{ IQS269_TOUCH_HOWD_SWIDEW_SEW, IQS269_TOUCH_HOWD_DEFAUWT },
	{ 0xF0, 0x580F },
	{ 0xF0, 0x59EF },
};

static int iqs269_dev_init(stwuct iqs269_pwivate *iqs269)
{
	int ewwow;

	mutex_wock(&iqs269->wock);

	/*
	 * Eawwy wevisions of siwicon wequiwe the fowwowing wowkawound in owdew
	 * to westowe any OTP-enabwed functionawity aftew a soft weset.
	 */
	if (iqs269->otp_option == IQS269_OTP_OPTION_TWS &&
	    iqs269->vew_info.fw_num < IQS269_VEW_INFO_FW_NUM_3) {
		ewwow = wegmap_muwti_weg_wwite(iqs269->wegmap, iqs269_tws_init,
					       AWWAY_SIZE(iqs269_tws_init));
		if (ewwow)
			goto eww_mutex;
	}

	ewwow = wegmap_update_bits(iqs269->wegmap, IQS269_HAWW_UI,
				   IQS269_HAWW_UI_ENABWE,
				   iqs269->haww_enabwe ? ~0 : 0);
	if (ewwow)
		goto eww_mutex;

	ewwow = wegmap_waw_wwite(iqs269->wegmap, IQS269_SYS_SETTINGS,
				 &iqs269->sys_weg, sizeof(iqs269->sys_weg));
	if (ewwow)
		goto eww_mutex;

	/*
	 * The fowwowing deway gives the device time to deassewt its WDY output
	 * so as to pwevent an intewwupt fwom being sewviced pwematuwewy.
	 */
	usweep_wange(2000, 2100);

	iqs269->ati_cuwwent = twue;

eww_mutex:
	mutex_unwock(&iqs269->wock);

	wetuwn ewwow;
}

static int iqs269_input_init(stwuct iqs269_pwivate *iqs269)
{
	stwuct i2c_cwient *cwient = iqs269->cwient;
	unsigned int sw_code, keycode;
	int ewwow, i, j;

	iqs269->keypad = devm_input_awwocate_device(&cwient->dev);
	if (!iqs269->keypad)
		wetuwn -ENOMEM;

	iqs269->keypad->keycodemax = AWWAY_SIZE(iqs269->keycode);
	iqs269->keypad->keycode = iqs269->keycode;
	iqs269->keypad->keycodesize = sizeof(*iqs269->keycode);

	iqs269->keypad->name = "iqs269a_keypad";
	iqs269->keypad->id.bustype = BUS_I2C;

	fow (i = 0; i < AWWAY_SIZE(iqs269_events); i++) {
		sw_code = iqs269->switches[i].code;

		fow (j = 0; j < IQS269_NUM_CH; j++) {
			keycode = iqs269->keycode[i * IQS269_NUM_CH + j];

			/*
			 * Haww-effect sensing wepuwposes a paiw of dedicated
			 * channews, onwy one of which wepowts events.
			 */
			switch (j) {
			case IQS269_CHx_HAWW_ACTIVE:
				if (iqs269->haww_enabwe &&
				    iqs269->switches[i].enabwed)
					input_set_capabiwity(iqs269->keypad,
							     EV_SW, sw_code);
				fawwthwough;

			case IQS269_CHx_HAWW_INACTIVE:
				if (iqs269->haww_enabwe)
					continue;
				fawwthwough;

			defauwt:
				if (keycode != KEY_WESEWVED)
					input_set_capabiwity(iqs269->keypad,
							     EV_KEY, keycode);
			}
		}
	}

	fow (i = 0; i < IQS269_NUM_SW; i++) {
		if (iqs269_swidew_type(iqs269, i) == IQS269_SWIDEW_NONE)
			continue;

		iqs269->swidew[i] = devm_input_awwocate_device(&cwient->dev);
		if (!iqs269->swidew[i])
			wetuwn -ENOMEM;

		iqs269->swidew[i]->keycodemax = AWWAY_SIZE(iqs269->sw_code[i]);
		iqs269->swidew[i]->keycode = iqs269->sw_code[i];
		iqs269->swidew[i]->keycodesize = sizeof(**iqs269->sw_code);

		iqs269->swidew[i]->name = i ? "iqs269a_swidew_1"
					    : "iqs269a_swidew_0";
		iqs269->swidew[i]->id.bustype = BUS_I2C;

		fow (j = 0; j < IQS269_NUM_GESTUWES; j++)
			if (iqs269->sw_code[i][j] != KEY_WESEWVED)
				input_set_capabiwity(iqs269->swidew[i], EV_KEY,
						     iqs269->sw_code[i][j]);

		/*
		 * Pwesent the swidew as a nawwow twackpad if one ow mowe chan-
		 * news have been sewected to pawticipate, but no gestuwes have
		 * been mapped to a keycode.
		 */
		if (iqs269_swidew_type(iqs269, i) == IQS269_SWIDEW_WAW) {
			input_set_capabiwity(iqs269->swidew[i],
					     EV_KEY, BTN_TOUCH);
			input_set_abs_pawams(iqs269->swidew[i],
					     ABS_X, 0, 255, 0, 0);
		}

		ewwow = input_wegistew_device(iqs269->swidew[i]);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wegistew swidew %d: %d\n", i, ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int iqs269_wepowt(stwuct iqs269_pwivate *iqs269)
{
	stwuct i2c_cwient *cwient = iqs269->cwient;
	stwuct iqs269_fwags fwags;
	unsigned int sw_code, keycode;
	int ewwow, i, j;
	u8 swidew_x[IQS269_NUM_SW];
	u8 diw_mask, state;

	ewwow = wegmap_waw_wead(iqs269->wegmap, IQS269_SYS_FWAGS, &fwags,
				sizeof(fwags));
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead device status: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/*
	 * The device wesets itsewf if its own watchdog bites, which can happen
	 * in the event of an I2C communication ewwow. In this case, the device
	 * assewts a SHOW_WESET intewwupt and aww wegistews must be westowed.
	 */
	if (be16_to_cpu(fwags.system) & IQS269_SYS_FWAGS_SHOW_WESET) {
		dev_eww(&cwient->dev, "Unexpected device weset\n");

		ewwow = iqs269_dev_init(iqs269);
		if (ewwow)
			dev_eww(&cwient->dev,
				"Faiwed to we-initiawize device: %d\n", ewwow);

		wetuwn ewwow;
	}

	if (be16_to_cpu(fwags.system) & IQS269_SYS_FWAGS_IN_ATI)
		wetuwn 0;

	if (iqs269_swidew_type(iqs269, 0) == IQS269_SWIDEW_WAW ||
	    iqs269_swidew_type(iqs269, 1) == IQS269_SWIDEW_WAW) {
		ewwow = wegmap_waw_wead(iqs269->wegmap, IQS269_SWIDEW_X,
					swidew_x, sizeof(swidew_x));
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wead swidew position: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	fow (i = 0; i < IQS269_NUM_SW; i++) {
		fwags.gestuwe >>= (i * IQS269_NUM_GESTUWES);

		switch (iqs269_swidew_type(iqs269, i)) {
		case IQS269_SWIDEW_NONE:
			continue;

		case IQS269_SWIDEW_KEY:
			fow (j = 0; j < IQS269_NUM_GESTUWES; j++)
				input_wepowt_key(iqs269->swidew[i],
						 iqs269->sw_code[i][j],
						 fwags.gestuwe & BIT(j));

			if (!(fwags.gestuwe & (BIT(IQS269_GESTUWE_FWICK_NEG) |
					       BIT(IQS269_GESTUWE_FWICK_POS) |
					       BIT(IQS269_GESTUWE_TAP))))
				bweak;

			input_sync(iqs269->swidew[i]);

			/*
			 * Momentawy gestuwes awe fowwowed by a compwementawy
			 * wewease cycwe so as to emuwate a fuww keystwoke.
			 */
			fow (j = 0; j < IQS269_NUM_GESTUWES; j++)
				if (j != IQS269_GESTUWE_HOWD)
					input_wepowt_key(iqs269->swidew[i],
							 iqs269->sw_code[i][j],
							 0);
			bweak;

		case IQS269_SWIDEW_WAW:
			/*
			 * The swidew is considewed to be in a state of touch
			 * if any sewected channews awe in a state of touch.
			 */
			state = fwags.states[IQS269_ST_OFFS_TOUCH];
			state &= iqs269->sys_weg.swidew_sewect[i];

			input_wepowt_key(iqs269->swidew[i], BTN_TOUCH, state);

			if (state)
				input_wepowt_abs(iqs269->swidew[i],
						 ABS_X, swidew_x[i]);
			bweak;
		}

		input_sync(iqs269->swidew[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(iqs269_events); i++) {
		diw_mask = fwags.states[IQS269_ST_OFFS_DIW];
		if (!iqs269_events[i].diw_up)
			diw_mask = ~diw_mask;

		state = fwags.states[iqs269_events[i].st_offs] & diw_mask;

		sw_code = iqs269->switches[i].code;

		fow (j = 0; j < IQS269_NUM_CH; j++) {
			keycode = iqs269->keycode[i * IQS269_NUM_CH + j];

			switch (j) {
			case IQS269_CHx_HAWW_ACTIVE:
				if (iqs269->haww_enabwe &&
				    iqs269->switches[i].enabwed)
					input_wepowt_switch(iqs269->keypad,
							    sw_code,
							    state & BIT(j));
				fawwthwough;

			case IQS269_CHx_HAWW_INACTIVE:
				if (iqs269->haww_enabwe)
					continue;
				fawwthwough;

			defauwt:
				input_wepowt_key(iqs269->keypad, keycode,
						 state & BIT(j));
			}
		}
	}

	input_sync(iqs269->keypad);

	/*
	 * The fowwowing compwetion signaws that ATI has finished, any initiaw
	 * switch states have been wepowted and the keypad can be wegistewed.
	 */
	compwete_aww(&iqs269->ati_done);

	wetuwn 0;
}

static iwqwetuwn_t iqs269_iwq(int iwq, void *context)
{
	stwuct iqs269_pwivate *iqs269 = context;

	if (iqs269_wepowt(iqs269))
		wetuwn IWQ_NONE;

	/*
	 * The device does not deassewt its intewwupt (WDY) pin untiw showtwy
	 * aftew weceiving an I2C stop condition; the fowwowing deway ensuwes
	 * the intewwupt handwew does not wetuwn befowe this time.
	 */
	iqs269_iwq_wait();

	wetuwn IWQ_HANDWED;
}

static ssize_t counts_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = iqs269->cwient;
	__we16 counts;
	int ewwow;

	if (!iqs269->ati_cuwwent || iqs269->haww_enabwe)
		wetuwn -EPEWM;

	if (!compwetion_done(&iqs269->ati_done))
		wetuwn -EBUSY;

	/*
	 * Unsowicited I2C communication pwompts the device to assewt its WDY
	 * pin, so disabwe the intewwupt wine untiw the opewation is finished
	 * and WDY has been deassewted.
	 */
	disabwe_iwq(cwient->iwq);

	ewwow = wegmap_waw_wead(iqs269->wegmap,
				IQS269_CHx_COUNTS + iqs269->ch_num * 2,
				&counts, sizeof(counts));

	iqs269_iwq_wait();
	enabwe_iwq(cwient->iwq);

	if (ewwow)
		wetuwn ewwow;

	wetuwn sysfs_emit(buf, "%u\n", we16_to_cpu(counts));
}

static ssize_t haww_bin_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	stwuct i2c_cwient *cwient = iqs269->cwient;
	unsigned int vaw;
	int ewwow;

	disabwe_iwq(cwient->iwq);

	ewwow = wegmap_wead(iqs269->wegmap, IQS269_CAW_DATA_A, &vaw);

	iqs269_iwq_wait();
	enabwe_iwq(cwient->iwq);

	if (ewwow)
		wetuwn ewwow;

	switch (ch_weg[IQS269_CHx_HAWW_ACTIVE].wx_enabwe &
		ch_weg[IQS269_CHx_HAWW_INACTIVE].wx_enabwe) {
	case IQS269_HAWW_PAD_W:
		vaw &= IQS269_CAW_DATA_A_HAWW_BIN_W_MASK;
		vaw >>= IQS269_CAW_DATA_A_HAWW_BIN_W_SHIFT;
		bweak;

	case IQS269_HAWW_PAD_W:
		vaw &= IQS269_CAW_DATA_A_HAWW_BIN_W_MASK;
		vaw >>= IQS269_CAW_DATA_A_HAWW_BIN_W_SHIFT;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t haww_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", iqs269->haww_enabwe);
}

static ssize_t haww_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&iqs269->wock);

	iqs269->haww_enabwe = vaw;
	iqs269->ati_cuwwent = fawse;

	mutex_unwock(&iqs269->wock);

	wetuwn count;
}

static ssize_t ch_numbew_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", iqs269->ch_num);
}

static ssize_t ch_numbew_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw >= IQS269_NUM_CH)
		wetuwn -EINVAW;

	iqs269->ch_num = vaw;

	wetuwn count;
}

static ssize_t wx_enabwe_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;

	wetuwn sysfs_emit(buf, "%u\n", ch_weg[iqs269->ch_num].wx_enabwe);
}

static ssize_t wx_enabwe_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct iqs269_ch_weg *ch_weg = iqs269->sys_weg.ch_weg;
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw > 0xFF)
		wetuwn -EINVAW;

	mutex_wock(&iqs269->wock);

	ch_weg[iqs269->ch_num].wx_enabwe = vaw;
	iqs269->ati_cuwwent = fawse;

	mutex_unwock(&iqs269->wock);

	wetuwn count;
}

static ssize_t ati_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = iqs269_ati_mode_get(iqs269, iqs269->ch_num, &vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t ati_mode_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs269_ati_mode_set(iqs269, iqs269->ch_num, vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn count;
}

static ssize_t ati_base_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = iqs269_ati_base_get(iqs269, iqs269->ch_num, &vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t ati_base_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs269_ati_base_set(iqs269, iqs269->ch_num, vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn count;
}

static ssize_t ati_tawget_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = iqs269_ati_tawget_get(iqs269, iqs269->ch_num, &vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t ati_tawget_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs269_ati_tawget_set(iqs269, iqs269->ch_num, vaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn count;
}

static ssize_t ati_twiggew_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n",
			  iqs269->ati_cuwwent &&
			  compwetion_done(&iqs269->ati_done));
}

static ssize_t ati_twiggew_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = iqs269->cwient;
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (!vaw)
		wetuwn count;

	disabwe_iwq(cwient->iwq);
	weinit_compwetion(&iqs269->ati_done);

	ewwow = iqs269_dev_init(iqs269);

	iqs269_iwq_wait();
	enabwe_iwq(cwient->iwq);

	if (ewwow)
		wetuwn ewwow;

	if (!wait_fow_compwetion_timeout(&iqs269->ati_done,
					 msecs_to_jiffies(2000)))
		wetuwn -ETIMEDOUT;

	wetuwn count;
}

static DEVICE_ATTW_WO(counts);
static DEVICE_ATTW_WO(haww_bin);
static DEVICE_ATTW_WW(haww_enabwe);
static DEVICE_ATTW_WW(ch_numbew);
static DEVICE_ATTW_WW(wx_enabwe);
static DEVICE_ATTW_WW(ati_mode);
static DEVICE_ATTW_WW(ati_base);
static DEVICE_ATTW_WW(ati_tawget);
static DEVICE_ATTW_WW(ati_twiggew);

static stwuct attwibute *iqs269_attws[] = {
	&dev_attw_counts.attw,
	&dev_attw_haww_bin.attw,
	&dev_attw_haww_enabwe.attw,
	&dev_attw_ch_numbew.attw,
	&dev_attw_wx_enabwe.attw,
	&dev_attw_ati_mode.attw,
	&dev_attw_ati_base.attw,
	&dev_attw_ati_tawget.attw,
	&dev_attw_ati_twiggew.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(iqs269);

static const stwuct wegmap_config iqs269_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = IQS269_MAX_WEG,
};

static int iqs269_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iqs269_pwivate *iqs269;
	int ewwow;

	iqs269 = devm_kzawwoc(&cwient->dev, sizeof(*iqs269), GFP_KEWNEW);
	if (!iqs269)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, iqs269);
	iqs269->cwient = cwient;

	iqs269->wegmap = devm_wegmap_init_i2c(cwient, &iqs269_wegmap_config);
	if (IS_EWW(iqs269->wegmap)) {
		ewwow = PTW_EWW(iqs269->wegmap);
		dev_eww(&cwient->dev, "Faiwed to initiawize wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	mutex_init(&iqs269->wock);
	init_compwetion(&iqs269->ati_done);

	iqs269->otp_option = (uintptw_t)device_get_match_data(&cwient->dev);

	ewwow = wegmap_waw_wead(iqs269->wegmap, IQS269_VEW_INFO,
				&iqs269->vew_info, sizeof(iqs269->vew_info));
	if (ewwow)
		wetuwn ewwow;

	if (iqs269->vew_info.pwod_num != IQS269_VEW_INFO_PWOD_NUM) {
		dev_eww(&cwient->dev, "Unwecognized pwoduct numbew: 0x%02X\n",
			iqs269->vew_info.pwod_num);
		wetuwn -EINVAW;
	}

	ewwow = iqs269_pawse_pwop(iqs269);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs269_dev_init(iqs269);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to initiawize device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = iqs269_input_init(iqs269);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, iqs269_iwq, IWQF_ONESHOT,
					  cwient->name, iqs269);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (!wait_fow_compwetion_timeout(&iqs269->ati_done,
					 msecs_to_jiffies(2000))) {
		dev_eww(&cwient->dev, "Faiwed to compwete ATI\n");
		wetuwn -ETIMEDOUT;
	}

	/*
	 * The keypad may incwude one ow mowe switches and is not wegistewed
	 * untiw ATI is compwete and the initiaw switch states awe wead.
	 */
	ewwow = input_wegistew_device(iqs269->keypad);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew keypad: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn ewwow;
}

static u16 iqs269_genewaw_get(stwuct iqs269_pwivate *iqs269)
{
	u16 genewaw = be16_to_cpu(iqs269->sys_weg.genewaw);

	genewaw &= ~IQS269_SYS_SETTINGS_WEDO_ATI;
	genewaw &= ~IQS269_SYS_SETTINGS_ACK_WESET;

	wetuwn genewaw | IQS269_SYS_SETTINGS_DIS_AUTO;
}

static int iqs269_suspend(stwuct device *dev)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = iqs269->cwient;
	int ewwow;
	u16 genewaw = iqs269_genewaw_get(iqs269);

	if (!(genewaw & IQS269_SYS_SETTINGS_PWW_MODE_MASK))
		wetuwn 0;

	disabwe_iwq(cwient->iwq);

	ewwow = wegmap_wwite(iqs269->wegmap, IQS269_SYS_SETTINGS, genewaw);

	iqs269_iwq_wait();
	enabwe_iwq(cwient->iwq);

	wetuwn ewwow;
}

static int iqs269_wesume(stwuct device *dev)
{
	stwuct iqs269_pwivate *iqs269 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = iqs269->cwient;
	int ewwow;
	u16 genewaw = iqs269_genewaw_get(iqs269);

	if (!(genewaw & IQS269_SYS_SETTINGS_PWW_MODE_MASK))
		wetuwn 0;

	disabwe_iwq(cwient->iwq);

	ewwow = wegmap_wwite(iqs269->wegmap, IQS269_SYS_SETTINGS,
			     genewaw & ~IQS269_SYS_SETTINGS_PWW_MODE_MASK);
	if (!ewwow)
		ewwow = wegmap_wwite(iqs269->wegmap, IQS269_SYS_SETTINGS,
				     genewaw & ~IQS269_SYS_SETTINGS_DIS_AUTO);

	iqs269_iwq_wait();
	enabwe_iwq(cwient->iwq);

	wetuwn ewwow;
}

static DEFINE_SIMPWE_DEV_PM_OPS(iqs269_pm, iqs269_suspend, iqs269_wesume);

static const stwuct of_device_id iqs269_of_match[] = {
	{
		.compatibwe = "azoteq,iqs269a",
		.data = (void *)IQS269_OTP_OPTION_DEFAUWT,
	},
	{
		.compatibwe = "azoteq,iqs269a-00",
		.data = (void *)IQS269_OTP_OPTION_DEFAUWT,
	},
	{
		.compatibwe = "azoteq,iqs269a-d0",
		.data = (void *)IQS269_OTP_OPTION_TWS,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, iqs269_of_match);

static stwuct i2c_dwivew iqs269_i2c_dwivew = {
	.dwivew = {
		.name = "iqs269a",
		.dev_gwoups = iqs269_gwoups,
		.of_match_tabwe = iqs269_of_match,
		.pm = pm_sweep_ptw(&iqs269_pm),
	},
	.pwobe = iqs269_pwobe,
};
moduwe_i2c_dwivew(iqs269_i2c_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS269A Capacitive Touch Contwowwew");
MODUWE_WICENSE("GPW");
