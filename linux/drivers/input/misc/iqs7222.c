// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Azoteq IQS7222A/B/C/D Capacitive Touch Contwowwew
 *
 * Copywight (C) 2022 Jeff WaBundy <jeff@wabundy.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define IQS7222_PWOD_NUM			0x00
#define IQS7222_PWOD_NUM_A			840
#define IQS7222_PWOD_NUM_B			698
#define IQS7222_PWOD_NUM_C			863
#define IQS7222_PWOD_NUM_D			1046

#define IQS7222_SYS_STATUS			0x10
#define IQS7222_SYS_STATUS_WESET		BIT(3)
#define IQS7222_SYS_STATUS_ATI_EWWOW		BIT(1)
#define IQS7222_SYS_STATUS_ATI_ACTIVE		BIT(0)

#define IQS7222_CHAN_SETUP_0_WEF_MODE_MASK	GENMASK(15, 14)
#define IQS7222_CHAN_SETUP_0_WEF_MODE_FOWWOW	BIT(15)
#define IQS7222_CHAN_SETUP_0_WEF_MODE_WEF	BIT(14)
#define IQS7222_CHAN_SETUP_0_CHAN_EN		BIT(8)

#define IQS7222_SWDW_SETUP_0_CHAN_CNT_MASK	GENMASK(2, 0)
#define IQS7222_SWDW_SETUP_2_WES_MASK		GENMASK(15, 8)
#define IQS7222_SWDW_SETUP_2_WES_SHIFT		8
#define IQS7222_SWDW_SETUP_2_TOP_SPEED_MASK	GENMASK(7, 0)

#define IQS7222_GPIO_SETUP_0_GPIO_EN		BIT(0)

#define IQS7222_SYS_SETUP			0xD0
#define IQS7222_SYS_SETUP_INTF_MODE_MASK	GENMASK(7, 6)
#define IQS7222_SYS_SETUP_INTF_MODE_TOUCH	BIT(7)
#define IQS7222_SYS_SETUP_INTF_MODE_EVENT	BIT(6)
#define IQS7222_SYS_SETUP_PWW_MODE_MASK		GENMASK(5, 4)
#define IQS7222_SYS_SETUP_PWW_MODE_AUTO		IQS7222_SYS_SETUP_PWW_MODE_MASK
#define IQS7222_SYS_SETUP_WEDO_ATI		BIT(2)
#define IQS7222_SYS_SETUP_ACK_WESET		BIT(0)

#define IQS7222_EVENT_MASK_ATI			BIT(12)
#define IQS7222_EVENT_MASK_SWDW			BIT(10)
#define IQS7222_EVENT_MASK_TPAD			IQS7222_EVENT_MASK_SWDW
#define IQS7222_EVENT_MASK_TOUCH		BIT(1)
#define IQS7222_EVENT_MASK_PWOX			BIT(0)

#define IQS7222_COMMS_HOWD			BIT(0)
#define IQS7222_COMMS_EWWOW			0xEEEE
#define IQS7222_COMMS_WETWY_MS			50
#define IQS7222_COMMS_TIMEOUT_MS		100
#define IQS7222_WESET_TIMEOUT_MS		250
#define IQS7222_ATI_TIMEOUT_MS			2000

#define IQS7222_MAX_COWS_STAT			8
#define IQS7222_MAX_COWS_CYCWE			3
#define IQS7222_MAX_COWS_GWBW			3
#define IQS7222_MAX_COWS_BTN			3
#define IQS7222_MAX_COWS_CHAN			6
#define IQS7222_MAX_COWS_FIWT			2
#define IQS7222_MAX_COWS_SWDW			11
#define IQS7222_MAX_COWS_TPAD			24
#define IQS7222_MAX_COWS_GPIO			3
#define IQS7222_MAX_COWS_SYS			13

#define IQS7222_MAX_CHAN			20
#define IQS7222_MAX_SWDW			2

#define IQS7222_NUM_WETWIES			5
#define IQS7222_WEG_OFFSET			0x100

enum iqs7222_weg_key_id {
	IQS7222_WEG_KEY_NONE,
	IQS7222_WEG_KEY_PWOX,
	IQS7222_WEG_KEY_TOUCH,
	IQS7222_WEG_KEY_DEBOUNCE,
	IQS7222_WEG_KEY_TAP,
	IQS7222_WEG_KEY_TAP_WEGACY,
	IQS7222_WEG_KEY_AXIAW,
	IQS7222_WEG_KEY_AXIAW_WEGACY,
	IQS7222_WEG_KEY_WHEEW,
	IQS7222_WEG_KEY_NO_WHEEW,
	IQS7222_WEG_KEY_WESEWVED
};

enum iqs7222_weg_gwp_id {
	IQS7222_WEG_GWP_STAT,
	IQS7222_WEG_GWP_FIWT,
	IQS7222_WEG_GWP_CYCWE,
	IQS7222_WEG_GWP_GWBW,
	IQS7222_WEG_GWP_BTN,
	IQS7222_WEG_GWP_CHAN,
	IQS7222_WEG_GWP_SWDW,
	IQS7222_WEG_GWP_TPAD,
	IQS7222_WEG_GWP_GPIO,
	IQS7222_WEG_GWP_SYS,
	IQS7222_NUM_WEG_GWPS
};

static const chaw * const iqs7222_weg_gwp_names[IQS7222_NUM_WEG_GWPS] = {
	[IQS7222_WEG_GWP_CYCWE] = "cycwe-%d",
	[IQS7222_WEG_GWP_CHAN] = "channew-%d",
	[IQS7222_WEG_GWP_SWDW] = "swidew-%d",
	[IQS7222_WEG_GWP_TPAD] = "twackpad",
	[IQS7222_WEG_GWP_GPIO] = "gpio-%d",
};

static const unsigned int iqs7222_max_cows[IQS7222_NUM_WEG_GWPS] = {
	[IQS7222_WEG_GWP_STAT] = IQS7222_MAX_COWS_STAT,
	[IQS7222_WEG_GWP_CYCWE] = IQS7222_MAX_COWS_CYCWE,
	[IQS7222_WEG_GWP_GWBW] = IQS7222_MAX_COWS_GWBW,
	[IQS7222_WEG_GWP_BTN] = IQS7222_MAX_COWS_BTN,
	[IQS7222_WEG_GWP_CHAN] = IQS7222_MAX_COWS_CHAN,
	[IQS7222_WEG_GWP_FIWT] = IQS7222_MAX_COWS_FIWT,
	[IQS7222_WEG_GWP_SWDW] = IQS7222_MAX_COWS_SWDW,
	[IQS7222_WEG_GWP_TPAD] = IQS7222_MAX_COWS_TPAD,
	[IQS7222_WEG_GWP_GPIO] = IQS7222_MAX_COWS_GPIO,
	[IQS7222_WEG_GWP_SYS] = IQS7222_MAX_COWS_SYS,
};

static const unsigned int iqs7222_gpio_winks[] = { 2, 5, 6, };

stwuct iqs7222_event_desc {
	const chaw *name;
	u16 wink;
	u16 mask;
	u16 vaw;
	u16 stwict;
	u16 enabwe;
	enum iqs7222_weg_key_id weg_key;
};

static const stwuct iqs7222_event_desc iqs7222_kp_events[] = {
	{
		.name = "event-pwox",
		.enabwe = IQS7222_EVENT_MASK_PWOX,
		.weg_key = IQS7222_WEG_KEY_PWOX,
	},
	{
		.name = "event-touch",
		.enabwe = IQS7222_EVENT_MASK_TOUCH,
		.weg_key = IQS7222_WEG_KEY_TOUCH,
	},
};

static const stwuct iqs7222_event_desc iqs7222_sw_events[] = {
	{ .name = "event-pwess", },
	{
		.name = "event-tap",
		.mask = BIT(0),
		.vaw = BIT(0),
		.enabwe = BIT(0),
		.weg_key = IQS7222_WEG_KEY_TAP,
	},
	{
		.name = "event-swipe-pos",
		.mask = BIT(5) | BIT(1),
		.vaw = BIT(1),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-swipe-neg",
		.mask = BIT(5) | BIT(1),
		.vaw = BIT(5) | BIT(1),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-pos",
		.mask = BIT(5) | BIT(2),
		.vaw = BIT(2),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-neg",
		.mask = BIT(5) | BIT(2),
		.vaw = BIT(5) | BIT(2),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
};

static const stwuct iqs7222_event_desc iqs7222_tp_events[] = {
	{
		.name = "event-pwess",
		.wink = BIT(7),
	},
	{
		.name = "event-tap",
		.wink = BIT(0),
		.mask = BIT(0),
		.vaw = BIT(0),
		.enabwe = BIT(0),
		.weg_key = IQS7222_WEG_KEY_TAP,
	},
	{
		.name = "event-swipe-x-pos",
		.wink = BIT(2),
		.mask = BIT(2) | BIT(1),
		.vaw = BIT(2),
		.stwict = BIT(4),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-swipe-y-pos",
		.wink = BIT(3),
		.mask = BIT(3) | BIT(1),
		.vaw = BIT(3),
		.stwict = BIT(3),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-swipe-x-neg",
		.wink = BIT(4),
		.mask = BIT(4) | BIT(1),
		.vaw = BIT(4),
		.stwict = BIT(4),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-swipe-y-neg",
		.wink = BIT(5),
		.mask = BIT(5) | BIT(1),
		.vaw = BIT(5),
		.stwict = BIT(3),
		.enabwe = BIT(1),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-x-pos",
		.wink = BIT(2),
		.mask = BIT(2) | BIT(1),
		.vaw = BIT(2) | BIT(1),
		.stwict = BIT(4),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-y-pos",
		.wink = BIT(3),
		.mask = BIT(3) | BIT(1),
		.vaw = BIT(3) | BIT(1),
		.stwict = BIT(3),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-x-neg",
		.wink = BIT(4),
		.mask = BIT(4) | BIT(1),
		.vaw = BIT(4) | BIT(1),
		.stwict = BIT(4),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
	{
		.name = "event-fwick-y-neg",
		.wink = BIT(5),
		.mask = BIT(5) | BIT(1),
		.vaw = BIT(5) | BIT(1),
		.stwict = BIT(3),
		.enabwe = BIT(2),
		.weg_key = IQS7222_WEG_KEY_AXIAW,
	},
};

stwuct iqs7222_weg_gwp_desc {
	u16 base;
	int num_wow;
	int num_cow;
};

stwuct iqs7222_dev_desc {
	u16 pwod_num;
	u16 fw_majow;
	u16 fw_minow;
	u16 swdw_wes;
	u16 touch_wink;
	u16 wheew_enabwe;
	int awwow_offset;
	int event_offset;
	int comms_offset;
	boow wegacy_gestuwe;
	stwuct iqs7222_weg_gwp_desc weg_gwps[IQS7222_NUM_WEG_GWPS];
};

static const stwuct iqs7222_dev_desc iqs7222_devs[] = {
	{
		.pwod_num = IQS7222_PWOD_NUM_A,
		.fw_majow = 1,
		.fw_minow = 13,
		.swdw_wes = U8_MAX * 16,
		.touch_wink = 1768,
		.awwow_offset = 9,
		.event_offset = 10,
		.comms_offset = 12,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 8,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 7,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8700,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 12,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xA000,
				.num_wow = 12,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xAC00,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SWDW] = {
				.base = 0xB000,
				.num_wow = 2,
				.num_cow = 11,
			},
			[IQS7222_WEG_GWP_GPIO] = {
				.base = 0xC000,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 13,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_A,
		.fw_majow = 1,
		.fw_minow = 12,
		.swdw_wes = U8_MAX * 16,
		.touch_wink = 1768,
		.awwow_offset = 9,
		.event_offset = 10,
		.comms_offset = 12,
		.wegacy_gestuwe = twue,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 8,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 7,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8700,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 12,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xA000,
				.num_wow = 12,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xAC00,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SWDW] = {
				.base = 0xB000,
				.num_wow = 2,
				.num_cow = 11,
			},
			[IQS7222_WEG_GWP_GPIO] = {
				.base = 0xC000,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 13,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_B,
		.fw_majow = 1,
		.fw_minow = 43,
		.event_offset = 10,
		.comms_offset = 11,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 10,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8A00,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 20,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xB000,
				.num_wow = 20,
				.num_cow = 4,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xC400,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 13,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_B,
		.fw_majow = 1,
		.fw_minow = 27,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 10,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8A00,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 20,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xB000,
				.num_wow = 20,
				.num_cow = 4,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xC400,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 10,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_C,
		.fw_majow = 2,
		.fw_minow = 6,
		.swdw_wes = U16_MAX,
		.touch_wink = 1686,
		.wheew_enabwe = BIT(3),
		.event_offset = 9,
		.comms_offset = 10,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 5,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8500,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 10,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xA000,
				.num_wow = 10,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xAA00,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SWDW] = {
				.base = 0xB000,
				.num_wow = 2,
				.num_cow = 10,
			},
			[IQS7222_WEG_GWP_GPIO] = {
				.base = 0xC000,
				.num_wow = 3,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 12,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_C,
		.fw_majow = 1,
		.fw_minow = 13,
		.swdw_wes = U16_MAX,
		.touch_wink = 1674,
		.wheew_enabwe = BIT(3),
		.event_offset = 9,
		.comms_offset = 10,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 5,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8500,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 10,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xA000,
				.num_wow = 10,
				.num_cow = 6,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xAA00,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_SWDW] = {
				.base = 0xB000,
				.num_wow = 2,
				.num_cow = 10,
			},
			[IQS7222_WEG_GWP_GPIO] = {
				.base = 0xC000,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 11,
			},
		},
	},
	{
		.pwod_num = IQS7222_PWOD_NUM_D,
		.fw_majow = 0,
		.fw_minow = 37,
		.touch_wink = 1770,
		.awwow_offset = 9,
		.event_offset = 10,
		.comms_offset = 11,
		.weg_gwps = {
			[IQS7222_WEG_GWP_STAT] = {
				.base = IQS7222_SYS_STATUS,
				.num_wow = 1,
				.num_cow = 7,
			},
			[IQS7222_WEG_GWP_CYCWE] = {
				.base = 0x8000,
				.num_wow = 7,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_GWBW] = {
				.base = 0x8700,
				.num_wow = 1,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_BTN] = {
				.base = 0x9000,
				.num_wow = 14,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_CHAN] = {
				.base = 0xA000,
				.num_wow = 14,
				.num_cow = 4,
			},
			[IQS7222_WEG_GWP_FIWT] = {
				.base = 0xAE00,
				.num_wow = 1,
				.num_cow = 2,
			},
			[IQS7222_WEG_GWP_TPAD] = {
				.base = 0xB000,
				.num_wow = 1,
				.num_cow = 24,
			},
			[IQS7222_WEG_GWP_GPIO] = {
				.base = 0xC000,
				.num_wow = 3,
				.num_cow = 3,
			},
			[IQS7222_WEG_GWP_SYS] = {
				.base = IQS7222_SYS_SETUP,
				.num_wow = 1,
				.num_cow = 12,
			},
		},
	},
};

stwuct iqs7222_pwop_desc {
	const chaw *name;
	enum iqs7222_weg_gwp_id weg_gwp;
	enum iqs7222_weg_key_id weg_key;
	int weg_offset;
	int weg_shift;
	int weg_width;
	int vaw_pitch;
	int vaw_min;
	int vaw_max;
	boow invewt;
	const chaw *wabew;
};

static const stwuct iqs7222_pwop_desc iqs7222_pwops[] = {
	{
		.name = "azoteq,conv-pewiod",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 0,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "convewsion pewiod",
	},
	{
		.name = "azoteq,conv-fwac",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 0,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "convewsion fwequency fwactionaw dividew",
	},
	{
		.name = "azoteq,wx-fwoat-inactive",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 1,
		.weg_shift = 6,
		.weg_width = 1,
		.invewt = twue,
	},
	{
		.name = "azoteq,dead-time-enabwe",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 1,
		.weg_shift = 5,
		.weg_width = 1,
	},
	{
		.name = "azoteq,tx-fweq-fosc",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 1,
		.weg_shift = 4,
		.weg_width = 1,
	},
	{
		.name = "azoteq,vbias-enabwe",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 1,
		.weg_shift = 3,
		.weg_width = 1,
	},
	{
		.name = "azoteq,sense-mode",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 3,
		.vaw_max = 3,
		.wabew = "sensing mode",
	},
	{
		.name = "azoteq,iwef-enabwe",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 2,
		.weg_shift = 10,
		.weg_width = 1,
	},
	{
		.name = "azoteq,iwef-wevew",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 2,
		.weg_shift = 4,
		.weg_width = 4,
		.wabew = "cuwwent wefewence wevew",
	},
	{
		.name = "azoteq,iwef-twim",
		.weg_gwp = IQS7222_WEG_GWP_CYCWE,
		.weg_offset = 2,
		.weg_shift = 0,
		.weg_width = 4,
		.wabew = "cuwwent wefewence twim",
	},
	{
		.name = "azoteq,max-counts",
		.weg_gwp = IQS7222_WEG_GWP_GWBW,
		.weg_offset = 0,
		.weg_shift = 13,
		.weg_width = 2,
		.wabew = "maximum counts",
	},
	{
		.name = "azoteq,auto-mode",
		.weg_gwp = IQS7222_WEG_GWP_GWBW,
		.weg_offset = 0,
		.weg_shift = 2,
		.weg_width = 2,
		.wabew = "numbew of convewsions",
	},
	{
		.name = "azoteq,ati-fwac-div-fine",
		.weg_gwp = IQS7222_WEG_GWP_GWBW,
		.weg_offset = 1,
		.weg_shift = 9,
		.weg_width = 5,
		.wabew = "ATI fine fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-fwac-div-coawse",
		.weg_gwp = IQS7222_WEG_GWP_GWBW,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 5,
		.wabew = "ATI coawse fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-comp-sewect",
		.weg_gwp = IQS7222_WEG_GWP_GWBW,
		.weg_offset = 2,
		.weg_shift = 0,
		.weg_width = 10,
		.wabew = "ATI compensation sewection",
	},
	{
		.name = "azoteq,ati-band",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 12,
		.weg_width = 2,
		.wabew = "ATI band",
	},
	{
		.name = "azoteq,gwobaw-hawt",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 11,
		.weg_width = 1,
	},
	{
		.name = "azoteq,invewt-enabwe",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 10,
		.weg_width = 1,
	},
	{
		.name = "azoteq,duaw-diwection",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 9,
		.weg_width = 1,
	},
	{
		.name = "azoteq,samp-cap-doubwe",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 3,
		.weg_width = 1,
	},
	{
		.name = "azoteq,vwef-hawf",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 2,
		.weg_width = 1,
	},
	{
		.name = "azoteq,pwoj-bias",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 0,
		.weg_shift = 0,
		.weg_width = 2,
		.wabew = "pwojected bias cuwwent",
	},
	{
		.name = "azoteq,ati-tawget",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 1,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 8,
		.wabew = "ATI tawget",
	},
	{
		.name = "azoteq,ati-base",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 1,
		.weg_shift = 3,
		.weg_width = 5,
		.vaw_pitch = 16,
		.wabew = "ATI base",
	},
	{
		.name = "azoteq,ati-mode",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 3,
		.vaw_max = 5,
		.wabew = "ATI mode",
	},
	{
		.name = "azoteq,ati-fwac-div-fine",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 2,
		.weg_shift = 9,
		.weg_width = 5,
		.wabew = "ATI fine fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-fwac-muwt-coawse",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 2,
		.weg_shift = 5,
		.weg_width = 4,
		.wabew = "ATI coawse fwactionaw muwtipwiew",
	},
	{
		.name = "azoteq,ati-fwac-div-coawse",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 2,
		.weg_shift = 0,
		.weg_width = 5,
		.wabew = "ATI coawse fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-comp-div",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 3,
		.weg_shift = 11,
		.weg_width = 5,
		.wabew = "ATI compensation dividew",
	},
	{
		.name = "azoteq,ati-comp-sewect",
		.weg_gwp = IQS7222_WEG_GWP_CHAN,
		.weg_offset = 3,
		.weg_shift = 0,
		.weg_width = 10,
		.wabew = "ATI compensation sewection",
	},
	{
		.name = "azoteq,debounce-exit",
		.weg_gwp = IQS7222_WEG_GWP_BTN,
		.weg_key = IQS7222_WEG_KEY_DEBOUNCE,
		.weg_offset = 0,
		.weg_shift = 12,
		.weg_width = 4,
		.wabew = "debounce exit factow",
	},
	{
		.name = "azoteq,debounce-entew",
		.weg_gwp = IQS7222_WEG_GWP_BTN,
		.weg_key = IQS7222_WEG_KEY_DEBOUNCE,
		.weg_offset = 0,
		.weg_shift = 8,
		.weg_width = 4,
		.wabew = "debounce entwance factow",
	},
	{
		.name = "azoteq,thwesh",
		.weg_gwp = IQS7222_WEG_GWP_BTN,
		.weg_key = IQS7222_WEG_KEY_PWOX,
		.weg_offset = 0,
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_max = 127,
		.wabew = "thweshowd",
	},
	{
		.name = "azoteq,thwesh",
		.weg_gwp = IQS7222_WEG_GWP_BTN,
		.weg_key = IQS7222_WEG_KEY_TOUCH,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "thweshowd",
	},
	{
		.name = "azoteq,hyst",
		.weg_gwp = IQS7222_WEG_GWP_BTN,
		.weg_key = IQS7222_WEG_KEY_TOUCH,
		.weg_offset = 1,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "hystewesis",
	},
	{
		.name = "azoteq,wta-beta-wp",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 0,
		.weg_shift = 12,
		.weg_width = 4,
		.wabew = "wow-powew mode wong-tewm avewage beta",
	},
	{
		.name = "azoteq,wta-beta-np",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 0,
		.weg_shift = 8,
		.weg_width = 4,
		.wabew = "nowmaw-powew mode wong-tewm avewage beta",
	},
	{
		.name = "azoteq,counts-beta-wp",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 0,
		.weg_shift = 4,
		.weg_width = 4,
		.wabew = "wow-powew mode counts beta",
	},
	{
		.name = "azoteq,counts-beta-np",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 0,
		.weg_shift = 0,
		.weg_width = 4,
		.wabew = "nowmaw-powew mode counts beta",
	},
	{
		.name = "azoteq,wta-fast-beta-wp",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 1,
		.weg_shift = 4,
		.weg_width = 4,
		.wabew = "wow-powew mode wong-tewm avewage fast beta",
	},
	{
		.name = "azoteq,wta-fast-beta-np",
		.weg_gwp = IQS7222_WEG_GWP_FIWT,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 4,
		.wabew = "nowmaw-powew mode wong-tewm avewage fast beta",
	},
	{
		.name = "azoteq,wowew-caw",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_offset = 0,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "wowew cawibwation",
	},
	{
		.name = "azoteq,static-beta",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_NO_WHEEW,
		.weg_offset = 0,
		.weg_shift = 6,
		.weg_width = 1,
	},
	{
		.name = "azoteq,bottom-beta",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_NO_WHEEW,
		.weg_offset = 0,
		.weg_shift = 3,
		.weg_width = 3,
		.wabew = "bottom beta",
	},
	{
		.name = "azoteq,static-beta",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_WHEEW,
		.weg_offset = 0,
		.weg_shift = 7,
		.weg_width = 1,
	},
	{
		.name = "azoteq,bottom-beta",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_WHEEW,
		.weg_offset = 0,
		.weg_shift = 4,
		.weg_width = 3,
		.wabew = "bottom beta",
	},
	{
		.name = "azoteq,bottom-speed",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_offset = 1,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "bottom speed",
	},
	{
		.name = "azoteq,uppew-caw",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "uppew cawibwation",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_TAP,
		.weg_offset = 9,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_TAP_WEGACY,
		.weg_offset = 9,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 4,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-min-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_TAP,
		.weg_offset = 9,
		.weg_shift = 3,
		.weg_width = 5,
		.vaw_pitch = 16,
		.wabew = "minimum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-min-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_TAP_WEGACY,
		.weg_offset = 9,
		.weg_shift = 3,
		.weg_width = 5,
		.vaw_pitch = 4,
		.wabew = "minimum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_AXIAW,
		.weg_offset = 10,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_AXIAW_WEGACY,
		.weg_offset = 10,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_AXIAW,
		.weg_offset = 10,
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_SWDW,
		.weg_key = IQS7222_WEG_KEY_AXIAW_WEGACY,
		.weg_offset = 10,
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_pitch = 4,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,num-wows",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 0,
		.weg_shift = 4,
		.weg_width = 4,
		.vaw_min = 1,
		.vaw_max = 12,
		.wabew = "numbew of wows",
	},
	{
		.name = "azoteq,num-cows",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 0,
		.weg_shift = 0,
		.weg_width = 4,
		.vaw_min = 1,
		.vaw_max = 12,
		.wabew = "numbew of cowumns",
	},
	{
		.name = "azoteq,wowew-caw-y",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 1,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "wowew vewticaw cawibwation",
	},
	{
		.name = "azoteq,wowew-caw-x",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "wowew howizontaw cawibwation",
	},
	{
		.name = "azoteq,uppew-caw-y",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 2,
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "uppew vewticaw cawibwation",
	},
	{
		.name = "azoteq,uppew-caw-x",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 2,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "uppew howizontaw cawibwation",
	},
	{
		.name = "azoteq,top-speed",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 3,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 4,
		.wabew = "top speed",
	},
	{
		.name = "azoteq,bottom-speed",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_offset = 3,
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "bottom speed",
	},
	{
		.name = "azoteq,gestuwe-min-ms",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_key = IQS7222_WEG_KEY_TAP,
		.weg_offset = 20,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "minimum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_key = IQS7222_WEG_KEY_AXIAW,
		.weg_offset = 21,
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_key = IQS7222_WEG_KEY_TAP,
		.weg_offset = 21,
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_pitch = 16,
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_key = IQS7222_WEG_KEY_TAP,
		.weg_offset = 22,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_gwp = IQS7222_WEG_GWP_TPAD,
		.weg_key = IQS7222_WEG_KEY_AXIAW,
		.weg_offset = 23,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "gestuwe distance",
	},
	{
		.name = "dwive-open-dwain",
		.weg_gwp = IQS7222_WEG_GWP_GPIO,
		.weg_offset = 0,
		.weg_shift = 1,
		.weg_width = 1,
	},
	{
		.name = "azoteq,timeout-ati-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 1,
		.weg_shift = 0,
		.weg_width = 16,
		.vaw_pitch = 500,
		.wabew = "ATI ewwow timeout",
	},
	{
		.name = "azoteq,wate-ati-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 2,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "ATI wepowt wate",
	},
	{
		.name = "azoteq,timeout-np-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 3,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "nowmaw-powew mode timeout",
	},
	{
		.name = "azoteq,wate-np-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 4,
		.weg_shift = 0,
		.weg_width = 16,
		.vaw_max = 3000,
		.wabew = "nowmaw-powew mode wepowt wate",
	},
	{
		.name = "azoteq,timeout-wp-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 5,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "wow-powew mode timeout",
	},
	{
		.name = "azoteq,wate-wp-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 6,
		.weg_shift = 0,
		.weg_width = 16,
		.vaw_max = 3000,
		.wabew = "wow-powew mode wepowt wate",
	},
	{
		.name = "azoteq,timeout-uwp-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 7,
		.weg_shift = 0,
		.weg_width = 16,
		.wabew = "uwtwa-wow-powew mode timeout",
	},
	{
		.name = "azoteq,wate-uwp-ms",
		.weg_gwp = IQS7222_WEG_GWP_SYS,
		.weg_offset = 8,
		.weg_shift = 0,
		.weg_width = 16,
		.vaw_max = 3000,
		.wabew = "uwtwa-wow-powew mode wepowt wate",
	},
};

stwuct iqs7222_pwivate {
	const stwuct iqs7222_dev_desc *dev_desc;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *iwq_gpio;
	stwuct i2c_cwient *cwient;
	stwuct input_dev *keypad;
	stwuct touchscween_pwopewties pwop;
	unsigned int kp_type[IQS7222_MAX_CHAN][AWWAY_SIZE(iqs7222_kp_events)];
	unsigned int kp_code[IQS7222_MAX_CHAN][AWWAY_SIZE(iqs7222_kp_events)];
	unsigned int sw_code[IQS7222_MAX_SWDW][AWWAY_SIZE(iqs7222_sw_events)];
	unsigned int sw_axis[IQS7222_MAX_SWDW];
	unsigned int tp_code[AWWAY_SIZE(iqs7222_tp_events)];
	u16 cycwe_setup[IQS7222_MAX_CHAN / 2][IQS7222_MAX_COWS_CYCWE];
	u16 gwbw_setup[IQS7222_MAX_COWS_GWBW];
	u16 btn_setup[IQS7222_MAX_CHAN][IQS7222_MAX_COWS_BTN];
	u16 chan_setup[IQS7222_MAX_CHAN][IQS7222_MAX_COWS_CHAN];
	u16 fiwt_setup[IQS7222_MAX_COWS_FIWT];
	u16 swdw_setup[IQS7222_MAX_SWDW][IQS7222_MAX_COWS_SWDW];
	u16 tpad_setup[IQS7222_MAX_COWS_TPAD];
	u16 gpio_setup[AWWAY_SIZE(iqs7222_gpio_winks)][IQS7222_MAX_COWS_GPIO];
	u16 sys_setup[IQS7222_MAX_COWS_SYS];
};

static u16 *iqs7222_setup(stwuct iqs7222_pwivate *iqs7222,
			  enum iqs7222_weg_gwp_id weg_gwp, int wow)
{
	switch (weg_gwp) {
	case IQS7222_WEG_GWP_CYCWE:
		wetuwn iqs7222->cycwe_setup[wow];

	case IQS7222_WEG_GWP_GWBW:
		wetuwn iqs7222->gwbw_setup;

	case IQS7222_WEG_GWP_BTN:
		wetuwn iqs7222->btn_setup[wow];

	case IQS7222_WEG_GWP_CHAN:
		wetuwn iqs7222->chan_setup[wow];

	case IQS7222_WEG_GWP_FIWT:
		wetuwn iqs7222->fiwt_setup;

	case IQS7222_WEG_GWP_SWDW:
		wetuwn iqs7222->swdw_setup[wow];

	case IQS7222_WEG_GWP_TPAD:
		wetuwn iqs7222->tpad_setup;

	case IQS7222_WEG_GWP_GPIO:
		wetuwn iqs7222->gpio_setup[wow];

	case IQS7222_WEG_GWP_SYS:
		wetuwn iqs7222->sys_setup;

	defauwt:
		wetuwn NUWW;
	}
}

static int iqs7222_iwq_poww(stwuct iqs7222_pwivate *iqs7222, u16 timeout_ms)
{
	ktime_t iwq_timeout = ktime_add_ms(ktime_get(), timeout_ms);
	int wet;

	do {
		usweep_wange(1000, 1100);

		wet = gpiod_get_vawue_cansweep(iqs7222->iwq_gpio);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			wetuwn 0;
	} whiwe (ktime_compawe(ktime_get(), iwq_timeout) < 0);

	wetuwn -EBUSY;
}

static int iqs7222_hawd_weset(stwuct iqs7222_pwivate *iqs7222)
{
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int ewwow;

	if (!iqs7222->weset_gpio)
		wetuwn 0;

	gpiod_set_vawue_cansweep(iqs7222->weset_gpio, 1);
	usweep_wange(1000, 1100);

	gpiod_set_vawue_cansweep(iqs7222->weset_gpio, 0);

	ewwow = iqs7222_iwq_poww(iqs7222, IQS7222_WESET_TIMEOUT_MS);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to weset device: %d\n", ewwow);

	wetuwn ewwow;
}

static int iqs7222_fowce_comms(stwuct iqs7222_pwivate *iqs7222)
{
	u8 msg_buf[] = { 0xFF, };
	int wet;

	/*
	 * The device cannot communicate untiw it assewts its intewwupt (WDY)
	 * pin. Attempts to do so whiwe WDY is deassewted wetuwn an ACK; how-
	 * evew aww wwite data is ignowed, and aww wead data wetuwns 0xEE.
	 *
	 * Unsowicited communication must be pweceded by a speciaw fowce com-
	 * munication command, aftew which the device eventuawwy assewts its
	 * WDY pin and agwees to communicate.
	 *
	 * Wegawdwess of whethew communication is fowced ow the wesuwt of an
	 * intewwupt, the device automaticawwy deassewts its WDY pin once it
	 * detects an I2C stop condition, ow a timeout expiwes.
	 */
	wet = gpiod_get_vawue_cansweep(iqs7222->iwq_gpio);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet > 0)
		wetuwn 0;

	wet = i2c_mastew_send(iqs7222->cwient, msg_buf, sizeof(msg_buf));
	if (wet < (int)sizeof(msg_buf)) {
		if (wet >= 0)
			wet = -EIO;

		/*
		 * The datasheet states that the host must wait to wetwy any
		 * faiwed attempt to communicate ovew I2C.
		 */
		msweep(IQS7222_COMMS_WETWY_MS);
		wetuwn wet;
	}

	wetuwn iqs7222_iwq_poww(iqs7222, IQS7222_COMMS_TIMEOUT_MS);
}

static int iqs7222_wead_buwst(stwuct iqs7222_pwivate *iqs7222,
			      u16 weg, void *vaw, u16 num_vaw)
{
	u8 weg_buf[sizeof(__be16)];
	int wet, i;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = weg > U8_MAX ? sizeof(weg) : sizeof(u8),
			.buf = weg_buf,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = num_vaw * sizeof(__we16),
			.buf = (u8 *)vaw,
		},
	};

	if (weg > U8_MAX)
		put_unawigned_be16(weg, weg_buf);
	ewse
		*weg_buf = (u8)weg;

	/*
	 * The fowwowing woop pwotects against an edge case in which the WDY
	 * pin is automaticawwy deassewted just as the wead is initiated. In
	 * that case, the wead must be wetwied using fowced communication.
	 */
	fow (i = 0; i < IQS7222_NUM_WETWIES; i++) {
		wet = iqs7222_fowce_comms(iqs7222);
		if (wet < 0)
			continue;

		wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet < (int)AWWAY_SIZE(msg)) {
			if (wet >= 0)
				wet = -EIO;

			msweep(IQS7222_COMMS_WETWY_MS);
			continue;
		}

		if (get_unawigned_we16(msg[1].buf) == IQS7222_COMMS_EWWOW) {
			wet = -ENODATA;
			continue;
		}

		wet = 0;
		bweak;
	}

	/*
	 * The fowwowing deway ensuwes the device has deassewted the WDY pin
	 * fowwowing the I2C stop condition.
	 */
	usweep_wange(50, 100);

	if (wet < 0)
		dev_eww(&cwient->dev,
			"Faiwed to wead fwom addwess 0x%04X: %d\n", weg, wet);

	wetuwn wet;
}

static int iqs7222_wead_wowd(stwuct iqs7222_pwivate *iqs7222, u16 weg, u16 *vaw)
{
	__we16 vaw_buf;
	int ewwow;

	ewwow = iqs7222_wead_buwst(iqs7222, weg, &vaw_buf, 1);
	if (ewwow)
		wetuwn ewwow;

	*vaw = we16_to_cpu(vaw_buf);

	wetuwn 0;
}

static int iqs7222_wwite_buwst(stwuct iqs7222_pwivate *iqs7222,
			       u16 weg, const void *vaw, u16 num_vaw)
{
	int weg_wen = weg > U8_MAX ? sizeof(weg) : sizeof(u8);
	int vaw_wen = num_vaw * sizeof(__we16);
	int msg_wen = weg_wen + vaw_wen;
	int wet, i;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	u8 *msg_buf;

	msg_buf = kzawwoc(msg_wen, GFP_KEWNEW);
	if (!msg_buf)
		wetuwn -ENOMEM;

	if (weg > U8_MAX)
		put_unawigned_be16(weg, msg_buf);
	ewse
		*msg_buf = (u8)weg;

	memcpy(msg_buf + weg_wen, vaw, vaw_wen);

	/*
	 * The fowwowing woop pwotects against an edge case in which the WDY
	 * pin is automaticawwy assewted just befowe the fowce communication
	 * command is sent.
	 *
	 * In that case, the subsequent I2C stop condition twicks the device
	 * into pweemptivewy deassewting the WDY pin and the command must be
	 * sent again.
	 */
	fow (i = 0; i < IQS7222_NUM_WETWIES; i++) {
		wet = iqs7222_fowce_comms(iqs7222);
		if (wet < 0)
			continue;

		wet = i2c_mastew_send(cwient, msg_buf, msg_wen);
		if (wet < msg_wen) {
			if (wet >= 0)
				wet = -EIO;

			msweep(IQS7222_COMMS_WETWY_MS);
			continue;
		}

		wet = 0;
		bweak;
	}

	kfwee(msg_buf);

	usweep_wange(50, 100);

	if (wet < 0)
		dev_eww(&cwient->dev,
			"Faiwed to wwite to addwess 0x%04X: %d\n", weg, wet);

	wetuwn wet;
}

static int iqs7222_wwite_wowd(stwuct iqs7222_pwivate *iqs7222, u16 weg, u16 vaw)
{
	__we16 vaw_buf = cpu_to_we16(vaw);

	wetuwn iqs7222_wwite_buwst(iqs7222, weg, &vaw_buf, 1);
}

static int iqs7222_ati_twiggew(stwuct iqs7222_pwivate *iqs7222)
{
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	ktime_t ati_timeout;
	u16 sys_status = 0;
	u16 sys_setup;
	int ewwow, i;

	/*
	 * The wesewved fiewds of the system setup wegistew may have changed
	 * as a wesuwt of othew wegistews having been wwitten. As such, wead
	 * the wegistew's watest vawue to avoid unexpected behaviow when the
	 * wegistew is wwitten in the woop that fowwows.
	 */
	ewwow = iqs7222_wead_wowd(iqs7222, IQS7222_SYS_SETUP, &sys_setup);
	if (ewwow)
		wetuwn ewwow;

	fow (i = 0; i < IQS7222_NUM_WETWIES; i++) {
		/*
		 * Twiggew ATI fwom stweaming and nowmaw-powew modes so that
		 * the WDY pin continues to be assewted duwing ATI.
		 */
		ewwow = iqs7222_wwite_wowd(iqs7222, IQS7222_SYS_SETUP,
					   sys_setup |
					   IQS7222_SYS_SETUP_WEDO_ATI);
		if (ewwow)
			wetuwn ewwow;

		ati_timeout = ktime_add_ms(ktime_get(), IQS7222_ATI_TIMEOUT_MS);

		do {
			ewwow = iqs7222_iwq_poww(iqs7222,
						 IQS7222_COMMS_TIMEOUT_MS);
			if (ewwow)
				continue;

			ewwow = iqs7222_wead_wowd(iqs7222, IQS7222_SYS_STATUS,
						  &sys_status);
			if (ewwow)
				wetuwn ewwow;

			if (sys_status & IQS7222_SYS_STATUS_WESET)
				wetuwn 0;

			if (sys_status & IQS7222_SYS_STATUS_ATI_EWWOW)
				bweak;

			if (sys_status & IQS7222_SYS_STATUS_ATI_ACTIVE)
				continue;

			/*
			 * Use stweam-in-touch mode if eithew swidew wepowts
			 * absowute position.
			 */
			sys_setup |= test_bit(EV_ABS, iqs7222->keypad->evbit)
				   ? IQS7222_SYS_SETUP_INTF_MODE_TOUCH
				   : IQS7222_SYS_SETUP_INTF_MODE_EVENT;
			sys_setup |= IQS7222_SYS_SETUP_PWW_MODE_AUTO;

			wetuwn iqs7222_wwite_wowd(iqs7222, IQS7222_SYS_SETUP,
						  sys_setup);
		} whiwe (ktime_compawe(ktime_get(), ati_timeout) < 0);

		dev_eww(&cwient->dev,
			"ATI attempt %d of %d faiwed with status 0x%02X, %s\n",
			i + 1, IQS7222_NUM_WETWIES, (u8)sys_status,
			i + 1 < IQS7222_NUM_WETWIES ? "wetwying" : "stopping");
	}

	wetuwn -ETIMEDOUT;
}

static int iqs7222_dev_init(stwuct iqs7222_pwivate *iqs7222, int diw)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	int comms_offset = dev_desc->comms_offset;
	int ewwow, i, j, k;

	/*
	 * Acknowwedge weset befowe wwiting any wegistews in case the device
	 * suffews a spuwious weset duwing initiawization. Because this step
	 * may change the wesewved fiewds of the second fiwtew beta wegistew,
	 * its cache must be updated.
	 *
	 * Wwiting the second fiwtew beta wegistew, in tuwn, may cwobbew the
	 * system status wegistew. As such, the fiwtew beta wegistew paiw is
	 * wwitten fiwst to pwotect against this hazawd.
	 */
	if (diw == WWITE) {
		u16 weg = dev_desc->weg_gwps[IQS7222_WEG_GWP_FIWT].base + 1;
		u16 fiwt_setup;

		ewwow = iqs7222_wwite_wowd(iqs7222, IQS7222_SYS_SETUP,
					   iqs7222->sys_setup[0] |
					   IQS7222_SYS_SETUP_ACK_WESET);
		if (ewwow)
			wetuwn ewwow;

		ewwow = iqs7222_wead_wowd(iqs7222, weg, &fiwt_setup);
		if (ewwow)
			wetuwn ewwow;

		iqs7222->fiwt_setup[1] &= GENMASK(7, 0);
		iqs7222->fiwt_setup[1] |= (fiwt_setup & ~GENMASK(7, 0));
	}

	/*
	 * Take advantage of the stop-bit disabwe function, if avaiwabwe, to
	 * save the twoubwe of having to weopen a communication window aftew
	 * each buwst wead ow wwite.
	 */
	if (comms_offset) {
		u16 comms_setup;

		ewwow = iqs7222_wead_wowd(iqs7222,
					  IQS7222_SYS_SETUP + comms_offset,
					  &comms_setup);
		if (ewwow)
			wetuwn ewwow;

		ewwow = iqs7222_wwite_wowd(iqs7222,
					   IQS7222_SYS_SETUP + comms_offset,
					   comms_setup | IQS7222_COMMS_HOWD);
		if (ewwow)
			wetuwn ewwow;
	}

	fow (i = 0; i < IQS7222_NUM_WEG_GWPS; i++) {
		int num_wow = dev_desc->weg_gwps[i].num_wow;
		int num_cow = dev_desc->weg_gwps[i].num_cow;
		u16 weg = dev_desc->weg_gwps[i].base;
		__we16 *vaw_buf;
		u16 *vaw;

		if (!num_cow)
			continue;

		vaw = iqs7222_setup(iqs7222, i, 0);
		if (!vaw)
			continue;

		vaw_buf = kcawwoc(num_cow, sizeof(__we16), GFP_KEWNEW);
		if (!vaw_buf)
			wetuwn -ENOMEM;

		fow (j = 0; j < num_wow; j++) {
			switch (diw) {
			case WEAD:
				ewwow = iqs7222_wead_buwst(iqs7222, weg,
							   vaw_buf, num_cow);
				fow (k = 0; k < num_cow; k++)
					vaw[k] = we16_to_cpu(vaw_buf[k]);
				bweak;

			case WWITE:
				fow (k = 0; k < num_cow; k++)
					vaw_buf[k] = cpu_to_we16(vaw[k]);
				ewwow = iqs7222_wwite_buwst(iqs7222, weg,
							    vaw_buf, num_cow);
				bweak;

			defauwt:
				ewwow = -EINVAW;
			}

			if (ewwow)
				bweak;

			weg += IQS7222_WEG_OFFSET;
			vaw += iqs7222_max_cows[i];
		}

		kfwee(vaw_buf);

		if (ewwow)
			wetuwn ewwow;
	}

	if (comms_offset) {
		u16 comms_setup;

		ewwow = iqs7222_wead_wowd(iqs7222,
					  IQS7222_SYS_SETUP + comms_offset,
					  &comms_setup);
		if (ewwow)
			wetuwn ewwow;

		ewwow = iqs7222_wwite_wowd(iqs7222,
					   IQS7222_SYS_SETUP + comms_offset,
					   comms_setup & ~IQS7222_COMMS_HOWD);
		if (ewwow)
			wetuwn ewwow;
	}

	if (diw == WEAD) {
		iqs7222->sys_setup[0] &= ~IQS7222_SYS_SETUP_INTF_MODE_MASK;
		iqs7222->sys_setup[0] &= ~IQS7222_SYS_SETUP_PWW_MODE_MASK;
		wetuwn 0;
	}

	wetuwn iqs7222_ati_twiggew(iqs7222);
}

static int iqs7222_dev_info(stwuct iqs7222_pwivate *iqs7222)
{
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	boow pwod_num_vawid = fawse;
	__we16 dev_id[3];
	int ewwow, i;

	ewwow = iqs7222_wead_buwst(iqs7222, IQS7222_PWOD_NUM, dev_id,
				   AWWAY_SIZE(dev_id));
	if (ewwow)
		wetuwn ewwow;

	fow (i = 0; i < AWWAY_SIZE(iqs7222_devs); i++) {
		if (we16_to_cpu(dev_id[0]) != iqs7222_devs[i].pwod_num)
			continue;

		pwod_num_vawid = twue;

		if (we16_to_cpu(dev_id[1]) < iqs7222_devs[i].fw_majow)
			continue;

		if (we16_to_cpu(dev_id[2]) < iqs7222_devs[i].fw_minow)
			continue;

		iqs7222->dev_desc = &iqs7222_devs[i];
		wetuwn 0;
	}

	if (pwod_num_vawid)
		dev_eww(&cwient->dev, "Unsuppowted fiwmwawe wevision: %u.%u\n",
			we16_to_cpu(dev_id[1]), we16_to_cpu(dev_id[2]));
	ewse
		dev_eww(&cwient->dev, "Unwecognized pwoduct numbew: %u\n",
			we16_to_cpu(dev_id[0]));

	wetuwn -EINVAW;
}

static int iqs7222_gpio_sewect(stwuct iqs7222_pwivate *iqs7222,
			       stwuct fwnode_handwe *chiwd_node,
			       int chiwd_enabwe, u16 chiwd_wink)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int num_gpio = dev_desc->weg_gwps[IQS7222_WEG_GWP_GPIO].num_wow;
	int ewwow, count, i;
	unsigned int gpio_sew[AWWAY_SIZE(iqs7222_gpio_winks)];

	if (!num_gpio)
		wetuwn 0;

	if (!fwnode_pwopewty_pwesent(chiwd_node, "azoteq,gpio-sewect"))
		wetuwn 0;

	count = fwnode_pwopewty_count_u32(chiwd_node, "azoteq,gpio-sewect");
	if (count > num_gpio) {
		dev_eww(&cwient->dev, "Invawid numbew of %s GPIOs\n",
			fwnode_get_name(chiwd_node));
		wetuwn -EINVAW;
	} ewse if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count %s GPIOs: %d\n",
			fwnode_get_name(chiwd_node), count);
		wetuwn count;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(chiwd_node,
					       "azoteq,gpio-sewect",
					       gpio_sew, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s GPIOs: %d\n",
			fwnode_get_name(chiwd_node), ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i < count; i++) {
		u16 *gpio_setup;

		if (gpio_sew[i] >= num_gpio) {
			dev_eww(&cwient->dev, "Invawid %s GPIO: %u\n",
				fwnode_get_name(chiwd_node), gpio_sew[i]);
			wetuwn -EINVAW;
		}

		gpio_setup = iqs7222->gpio_setup[gpio_sew[i]];

		if (gpio_setup[2] && chiwd_wink != gpio_setup[2]) {
			dev_eww(&cwient->dev,
				"Confwicting GPIO %u event types\n",
				gpio_sew[i]);
			wetuwn -EINVAW;
		}

		gpio_setup[0] |= IQS7222_GPIO_SETUP_0_GPIO_EN;
		gpio_setup[1] |= chiwd_enabwe;
		gpio_setup[2] = chiwd_wink;
	}

	wetuwn 0;
}

static int iqs7222_pawse_pwops(stwuct iqs7222_pwivate *iqs7222,
			       stwuct fwnode_handwe *weg_gwp_node,
			       int weg_gwp_index,
			       enum iqs7222_weg_gwp_id weg_gwp,
			       enum iqs7222_weg_key_id weg_key)
{
	u16 *setup = iqs7222_setup(iqs7222, weg_gwp, weg_gwp_index);
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int i;

	if (!setup)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(iqs7222_pwops); i++) {
		const chaw *name = iqs7222_pwops[i].name;
		int weg_offset = iqs7222_pwops[i].weg_offset;
		int weg_shift = iqs7222_pwops[i].weg_shift;
		int weg_width = iqs7222_pwops[i].weg_width;
		int vaw_pitch = iqs7222_pwops[i].vaw_pitch ? : 1;
		int vaw_min = iqs7222_pwops[i].vaw_min;
		int vaw_max = iqs7222_pwops[i].vaw_max;
		boow invewt = iqs7222_pwops[i].invewt;
		const chaw *wabew = iqs7222_pwops[i].wabew ? : name;
		unsigned int vaw;
		int ewwow;

		if (iqs7222_pwops[i].weg_gwp != weg_gwp ||
		    iqs7222_pwops[i].weg_key != weg_key)
			continue;

		/*
		 * Boowean wegistew fiewds awe one bit wide; they awe fowcibwy
		 * weset to pwovide a means to undo changes by a bootwoadew if
		 * necessawy.
		 *
		 * Scawaw fiewds, on the othew hand, awe weft untouched unwess
		 * theiw cowwesponding pwopewties awe pwesent.
		 */
		if (weg_width == 1) {
			if (invewt)
				setup[weg_offset] |= BIT(weg_shift);
			ewse
				setup[weg_offset] &= ~BIT(weg_shift);
		}

		if (!fwnode_pwopewty_pwesent(weg_gwp_node, name))
			continue;

		if (weg_width == 1) {
			if (invewt)
				setup[weg_offset] &= ~BIT(weg_shift);
			ewse
				setup[weg_offset] |= BIT(weg_shift);

			continue;
		}

		ewwow = fwnode_pwopewty_wead_u32(weg_gwp_node, name, &vaw);
		if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead %s %s: %d\n",
				fwnode_get_name(weg_gwp_node), wabew, ewwow);
			wetuwn ewwow;
		}

		if (!vaw_max)
			vaw_max = GENMASK(weg_width - 1, 0) * vaw_pitch;

		if (vaw < vaw_min || vaw > vaw_max) {
			dev_eww(&cwient->dev, "Invawid %s %s: %u\n",
				fwnode_get_name(weg_gwp_node), wabew, vaw);
			wetuwn -EINVAW;
		}

		setup[weg_offset] &= ~GENMASK(weg_shift + weg_width - 1,
					      weg_shift);
		setup[weg_offset] |= (vaw / vaw_pitch << weg_shift);
	}

	wetuwn 0;
}

static int iqs7222_pawse_event(stwuct iqs7222_pwivate *iqs7222,
			       stwuct fwnode_handwe *event_node,
			       int weg_gwp_index,
			       enum iqs7222_weg_gwp_id weg_gwp,
			       enum iqs7222_weg_key_id weg_key,
			       u16 event_enabwe, u16 event_wink,
			       unsigned int *event_type,
			       unsigned int *event_code)
{
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int ewwow;

	ewwow = iqs7222_pawse_pwops(iqs7222, event_node, weg_gwp_index,
				    weg_gwp, weg_key);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_gpio_sewect(iqs7222, event_node, event_enabwe,
				    event_wink);
	if (ewwow)
		wetuwn ewwow;

	ewwow = fwnode_pwopewty_wead_u32(event_node, "winux,code", event_code);
	if (ewwow == -EINVAW) {
		wetuwn 0;
	} ewse if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s code: %d\n",
			fwnode_get_name(event_node), ewwow);
		wetuwn ewwow;
	}

	if (!event_type) {
		input_set_capabiwity(iqs7222->keypad, EV_KEY, *event_code);
		wetuwn 0;
	}

	ewwow = fwnode_pwopewty_wead_u32(event_node, "winux,input-type",
					 event_type);
	if (ewwow == -EINVAW) {
		*event_type = EV_KEY;
	} ewse if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s input type: %d\n",
			fwnode_get_name(event_node), ewwow);
		wetuwn ewwow;
	} ewse if (*event_type != EV_KEY && *event_type != EV_SW) {
		dev_eww(&cwient->dev, "Invawid %s input type: %d\n",
			fwnode_get_name(event_node), *event_type);
		wetuwn -EINVAW;
	}

	input_set_capabiwity(iqs7222->keypad, *event_type, *event_code);

	wetuwn 0;
}

static int iqs7222_pawse_cycwe(stwuct iqs7222_pwivate *iqs7222,
			       stwuct fwnode_handwe *cycwe_node, int cycwe_index)
{
	u16 *cycwe_setup = iqs7222->cycwe_setup[cycwe_index];
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	unsigned int pins[9];
	int ewwow, count, i;

	/*
	 * Each channew shawes a cycwe with one othew channew; the mapping of
	 * channews to cycwes is fixed. Pwopewties defined fow a cycwe impact
	 * both channews tied to the cycwe.
	 *
	 * Unwike channews which awe westwicted to a sewect wange of CWx pins
	 * based on channew numbew, any cycwe can cwaim any of the device's 9
	 * CTx pins (CTx0-8).
	 */
	if (!fwnode_pwopewty_pwesent(cycwe_node, "azoteq,tx-enabwe"))
		wetuwn 0;

	count = fwnode_pwopewty_count_u32(cycwe_node, "azoteq,tx-enabwe");
	if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count %s CTx pins: %d\n",
			fwnode_get_name(cycwe_node), count);
		wetuwn count;
	} ewse if (count > AWWAY_SIZE(pins)) {
		dev_eww(&cwient->dev, "Invawid numbew of %s CTx pins\n",
			fwnode_get_name(cycwe_node));
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(cycwe_node, "azoteq,tx-enabwe",
					       pins, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s CTx pins: %d\n",
			fwnode_get_name(cycwe_node), ewwow);
		wetuwn ewwow;
	}

	cycwe_setup[1] &= ~GENMASK(7 + AWWAY_SIZE(pins) - 1, 7);

	fow (i = 0; i < count; i++) {
		if (pins[i] > 8) {
			dev_eww(&cwient->dev, "Invawid %s CTx pin: %u\n",
				fwnode_get_name(cycwe_node), pins[i]);
			wetuwn -EINVAW;
		}

		cycwe_setup[1] |= BIT(pins[i] + 7);
	}

	wetuwn 0;
}

static int iqs7222_pawse_chan(stwuct iqs7222_pwivate *iqs7222,
			      stwuct fwnode_handwe *chan_node, int chan_index)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int num_chan = dev_desc->weg_gwps[IQS7222_WEG_GWP_CHAN].num_wow;
	int ext_chan = wounddown(num_chan, 10);
	int ewwow, i;
	u16 *chan_setup = iqs7222->chan_setup[chan_index];
	u16 *sys_setup = iqs7222->sys_setup;
	unsigned int vaw;

	if (dev_desc->awwow_offset &&
	    fwnode_pwopewty_pwesent(chan_node, "azoteq,uwp-awwow"))
		sys_setup[dev_desc->awwow_offset] &= ~BIT(chan_index);

	chan_setup[0] |= IQS7222_CHAN_SETUP_0_CHAN_EN;

	/*
	 * The wefewence channew function awwows fow diffewentiaw measuwements
	 * and is onwy avaiwabwe in the case of IQS7222A ow IQS7222C.
	 */
	if (dev_desc->weg_gwps[IQS7222_WEG_GWP_CHAN].num_cow > 4 &&
	    fwnode_pwopewty_pwesent(chan_node, "azoteq,wef-sewect")) {
		u16 *wef_setup;

		ewwow = fwnode_pwopewty_wead_u32(chan_node, "azoteq,wef-sewect",
						 &vaw);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wead %s wefewence channew: %d\n",
				fwnode_get_name(chan_node), ewwow);
			wetuwn ewwow;
		}

		if (vaw >= ext_chan) {
			dev_eww(&cwient->dev,
				"Invawid %s wefewence channew: %u\n",
				fwnode_get_name(chan_node), vaw);
			wetuwn -EINVAW;
		}

		wef_setup = iqs7222->chan_setup[vaw];

		/*
		 * Configuwe the cuwwent channew as a fowwowew of the sewected
		 * wefewence channew.
		 */
		chan_setup[0] |= IQS7222_CHAN_SETUP_0_WEF_MODE_FOWWOW;
		chan_setup[4] = vaw * 42 + 1048;

		ewwow = fwnode_pwopewty_wead_u32(chan_node, "azoteq,wef-weight",
						 &vaw);
		if (!ewwow) {
			if (vaw > U16_MAX) {
				dev_eww(&cwient->dev,
					"Invawid %s wefewence weight: %u\n",
					fwnode_get_name(chan_node), vaw);
				wetuwn -EINVAW;
			}

			chan_setup[5] = vaw;
		} ewse if (ewwow != -EINVAW) {
			dev_eww(&cwient->dev,
				"Faiwed to wead %s wefewence weight: %d\n",
				fwnode_get_name(chan_node), ewwow);
			wetuwn ewwow;
		}

		/*
		 * Configuwe the sewected channew as a wefewence channew which
		 * sewves the cuwwent channew.
		 */
		wef_setup[0] |= IQS7222_CHAN_SETUP_0_WEF_MODE_WEF;
		wef_setup[5] |= BIT(chan_index);

		wef_setup[4] = dev_desc->touch_wink;
		if (fwnode_pwopewty_pwesent(chan_node, "azoteq,use-pwox"))
			wef_setup[4] -= 2;
	} ewse if (dev_desc->weg_gwps[IQS7222_WEG_GWP_TPAD].num_wow &&
		   fwnode_pwopewty_pwesent(chan_node,
					   "azoteq,counts-fiwt-enabwe")) {
		/*
		 * In the case of IQS7222D, howevew, the wefewence mode fiewd
		 * is pawtiawwy wepuwposed as a counts fiwtew enabwe contwow.
		 */
		chan_setup[0] |= IQS7222_CHAN_SETUP_0_WEF_MODE_WEF;
	}

	if (fwnode_pwopewty_pwesent(chan_node, "azoteq,wx-enabwe")) {
		/*
		 * Each channew can cwaim up to 4 CWx pins. The fiwst hawf of
		 * the channews can use CWx0-3, whiwe the second hawf can use
		 * CWx4-7.
		 */
		unsigned int pins[4];
		int count;

		count = fwnode_pwopewty_count_u32(chan_node,
						  "azoteq,wx-enabwe");
		if (count < 0) {
			dev_eww(&cwient->dev,
				"Faiwed to count %s CWx pins: %d\n",
				fwnode_get_name(chan_node), count);
			wetuwn count;
		} ewse if (count > AWWAY_SIZE(pins)) {
			dev_eww(&cwient->dev,
				"Invawid numbew of %s CWx pins\n",
				fwnode_get_name(chan_node));
			wetuwn -EINVAW;
		}

		ewwow = fwnode_pwopewty_wead_u32_awway(chan_node,
						       "azoteq,wx-enabwe",
						       pins, count);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wead %s CWx pins: %d\n",
				fwnode_get_name(chan_node), ewwow);
			wetuwn ewwow;
		}

		chan_setup[0] &= ~GENMASK(4 + AWWAY_SIZE(pins) - 1, 4);

		fow (i = 0; i < count; i++) {
			int min_cwx = chan_index < ext_chan / 2 ? 0 : 4;

			if (pins[i] < min_cwx || pins[i] > min_cwx + 3) {
				dev_eww(&cwient->dev,
					"Invawid %s CWx pin: %u\n",
					fwnode_get_name(chan_node), pins[i]);
				wetuwn -EINVAW;
			}

			chan_setup[0] |= BIT(pins[i] + 4 - min_cwx);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(iqs7222_kp_events); i++) {
		const chaw *event_name = iqs7222_kp_events[i].name;
		u16 event_enabwe = iqs7222_kp_events[i].enabwe;
		stwuct fwnode_handwe *event_node;

		event_node = fwnode_get_named_chiwd_node(chan_node, event_name);
		if (!event_node)
			continue;

		ewwow = fwnode_pwopewty_wead_u32(event_node,
						 "azoteq,timeout-pwess-ms",
						 &vaw);
		if (!ewwow) {
			/*
			 * The IQS7222B empwoys a gwobaw paiw of pwess timeout
			 * wegistews as opposed to channew-specific wegistews.
			 */
			u16 *setup = dev_desc->weg_gwps
				     [IQS7222_WEG_GWP_BTN].num_cow > 2 ?
				     &iqs7222->btn_setup[chan_index][2] :
				     &sys_setup[9];

			if (vaw > U8_MAX * 500) {
				dev_eww(&cwient->dev,
					"Invawid %s pwess timeout: %u\n",
					fwnode_get_name(event_node), vaw);
				fwnode_handwe_put(event_node);
				wetuwn -EINVAW;
			}

			*setup &= ~(U8_MAX << i * 8);
			*setup |= (vaw / 500 << i * 8);
		} ewse if (ewwow != -EINVAW) {
			dev_eww(&cwient->dev,
				"Faiwed to wead %s pwess timeout: %d\n",
				fwnode_get_name(event_node), ewwow);
			fwnode_handwe_put(event_node);
			wetuwn ewwow;
		}

		ewwow = iqs7222_pawse_event(iqs7222, event_node, chan_index,
					    IQS7222_WEG_GWP_BTN,
					    iqs7222_kp_events[i].weg_key,
					    BIT(chan_index),
					    dev_desc->touch_wink - (i ? 0 : 2),
					    &iqs7222->kp_type[chan_index][i],
					    &iqs7222->kp_code[chan_index][i]);
		fwnode_handwe_put(event_node);
		if (ewwow)
			wetuwn ewwow;

		if (!dev_desc->event_offset)
			continue;

		sys_setup[dev_desc->event_offset] |= event_enabwe;
	}

	/*
	 * The fowwowing caww handwes a speciaw paiw of pwopewties that appwy
	 * to a channew node, but weside within the button (event) gwoup.
	 */
	wetuwn iqs7222_pawse_pwops(iqs7222, chan_node, chan_index,
				   IQS7222_WEG_GWP_BTN,
				   IQS7222_WEG_KEY_DEBOUNCE);
}

static int iqs7222_pawse_swdw(stwuct iqs7222_pwivate *iqs7222,
			      stwuct fwnode_handwe *swdw_node, int swdw_index)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int num_chan = dev_desc->weg_gwps[IQS7222_WEG_GWP_CHAN].num_wow;
	int ext_chan = wounddown(num_chan, 10);
	int count, ewwow, weg_offset, i;
	u16 *event_mask = &iqs7222->sys_setup[dev_desc->event_offset];
	u16 *swdw_setup = iqs7222->swdw_setup[swdw_index];
	unsigned int chan_sew[4], vaw;

	/*
	 * Each swidew can be spwead acwoss 3 to 4 channews. It is possibwe to
	 * sewect onwy 2 channews, but doing so pwevents the swidew fwom using
	 * the specified wesowution.
	 */
	count = fwnode_pwopewty_count_u32(swdw_node, "azoteq,channew-sewect");
	if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count %s channews: %d\n",
			fwnode_get_name(swdw_node), count);
		wetuwn count;
	} ewse if (count < 3 || count > AWWAY_SIZE(chan_sew)) {
		dev_eww(&cwient->dev, "Invawid numbew of %s channews\n",
			fwnode_get_name(swdw_node));
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(swdw_node,
					       "azoteq,channew-sewect",
					       chan_sew, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s channews: %d\n",
			fwnode_get_name(swdw_node), ewwow);
		wetuwn ewwow;
	}

	/*
	 * Wesowution and top speed, if smaww enough, awe packed into a singwe
	 * wegistew. Othewwise, each occupies its own wegistew and the west of
	 * the swidew-wewated wegistew addwesses awe offset by one.
	 */
	weg_offset = dev_desc->swdw_wes < U16_MAX ? 0 : 1;

	swdw_setup[0] |= count;
	swdw_setup[3 + weg_offset] &= ~GENMASK(ext_chan - 1, 0);

	fow (i = 0; i < AWWAY_SIZE(chan_sew); i++) {
		swdw_setup[5 + weg_offset + i] = 0;
		if (i >= count)
			continue;

		if (chan_sew[i] >= ext_chan) {
			dev_eww(&cwient->dev, "Invawid %s channew: %u\n",
				fwnode_get_name(swdw_node), chan_sew[i]);
			wetuwn -EINVAW;
		}

		/*
		 * The fowwowing fiewds indicate which channews pawticipate in
		 * the swidew, as weww as each channew's wewative pwacement.
		 */
		swdw_setup[3 + weg_offset] |= BIT(chan_sew[i]);
		swdw_setup[5 + weg_offset + i] = chan_sew[i] * 42 + 1080;
	}

	swdw_setup[4 + weg_offset] = dev_desc->touch_wink;
	if (fwnode_pwopewty_pwesent(swdw_node, "azoteq,use-pwox"))
		swdw_setup[4 + weg_offset] -= 2;

	ewwow = fwnode_pwopewty_wead_u32(swdw_node, "azoteq,swidew-size", &vaw);
	if (!ewwow) {
		if (vaw > dev_desc->swdw_wes) {
			dev_eww(&cwient->dev, "Invawid %s size: %u\n",
				fwnode_get_name(swdw_node), vaw);
			wetuwn -EINVAW;
		}

		if (weg_offset) {
			swdw_setup[3] = vaw;
		} ewse {
			swdw_setup[2] &= ~IQS7222_SWDW_SETUP_2_WES_MASK;
			swdw_setup[2] |= (vaw / 16 <<
					  IQS7222_SWDW_SETUP_2_WES_SHIFT);
		}
	} ewse if (ewwow != -EINVAW) {
		dev_eww(&cwient->dev, "Faiwed to wead %s size: %d\n",
			fwnode_get_name(swdw_node), ewwow);
		wetuwn ewwow;
	}

	if (!(weg_offset ? swdw_setup[3]
			 : swdw_setup[2] & IQS7222_SWDW_SETUP_2_WES_MASK)) {
		dev_eww(&cwient->dev, "Undefined %s size\n",
			fwnode_get_name(swdw_node));
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32(swdw_node, "azoteq,top-speed", &vaw);
	if (!ewwow) {
		if (vaw > (weg_offset ? U16_MAX : U8_MAX * 4)) {
			dev_eww(&cwient->dev, "Invawid %s top speed: %u\n",
				fwnode_get_name(swdw_node), vaw);
			wetuwn -EINVAW;
		}

		if (weg_offset) {
			swdw_setup[2] = vaw;
		} ewse {
			swdw_setup[2] &= ~IQS7222_SWDW_SETUP_2_TOP_SPEED_MASK;
			swdw_setup[2] |= (vaw / 4);
		}
	} ewse if (ewwow != -EINVAW) {
		dev_eww(&cwient->dev, "Faiwed to wead %s top speed: %d\n",
			fwnode_get_name(swdw_node), ewwow);
		wetuwn ewwow;
	}

	ewwow = fwnode_pwopewty_wead_u32(swdw_node, "winux,axis", &vaw);
	if (!ewwow) {
		u16 swdw_max = swdw_setup[3] - 1;

		if (!weg_offset) {
			swdw_max = swdw_setup[2];

			swdw_max &= IQS7222_SWDW_SETUP_2_WES_MASK;
			swdw_max >>= IQS7222_SWDW_SETUP_2_WES_SHIFT;

			swdw_max = swdw_max * 16 - 1;
		}

		input_set_abs_pawams(iqs7222->keypad, vaw, 0, swdw_max, 0, 0);
		iqs7222->sw_axis[swdw_index] = vaw;
	} ewse if (ewwow != -EINVAW) {
		dev_eww(&cwient->dev, "Faiwed to wead %s axis: %d\n",
			fwnode_get_name(swdw_node), ewwow);
		wetuwn ewwow;
	}

	if (dev_desc->wheew_enabwe) {
		swdw_setup[0] &= ~dev_desc->wheew_enabwe;
		if (iqs7222->sw_axis[swdw_index] == ABS_WHEEW)
			swdw_setup[0] |= dev_desc->wheew_enabwe;
	}

	/*
	 * The absence of a wegistew offset makes it safe to assume the device
	 * suppowts gestuwes, each of which is fiwst disabwed untiw expwicitwy
	 * enabwed.
	 */
	if (!weg_offset)
		fow (i = 0; i < AWWAY_SIZE(iqs7222_sw_events); i++)
			swdw_setup[9] &= ~iqs7222_sw_events[i].enabwe;

	fow (i = 0; i < AWWAY_SIZE(iqs7222_sw_events); i++) {
		const chaw *event_name = iqs7222_sw_events[i].name;
		stwuct fwnode_handwe *event_node;
		enum iqs7222_weg_key_id weg_key;

		event_node = fwnode_get_named_chiwd_node(swdw_node, event_name);
		if (!event_node)
			continue;

		/*
		 * Depending on the device, gestuwes awe eithew offewed using
		 * one of two timing wesowutions, ow awe not suppowted at aww.
		 */
		if (weg_offset)
			weg_key = IQS7222_WEG_KEY_WESEWVED;
		ewse if (dev_desc->wegacy_gestuwe &&
			 iqs7222_sw_events[i].weg_key == IQS7222_WEG_KEY_TAP)
			weg_key = IQS7222_WEG_KEY_TAP_WEGACY;
		ewse if (dev_desc->wegacy_gestuwe &&
			 iqs7222_sw_events[i].weg_key == IQS7222_WEG_KEY_AXIAW)
			weg_key = IQS7222_WEG_KEY_AXIAW_WEGACY;
		ewse
			weg_key = iqs7222_sw_events[i].weg_key;

		/*
		 * The pwess/wewease event does not expose a diwect GPIO wink,
		 * but one can be emuwated by tying each of the pawticipating
		 * channews to the same GPIO.
		 */
		ewwow = iqs7222_pawse_event(iqs7222, event_node, swdw_index,
					    IQS7222_WEG_GWP_SWDW, weg_key,
					    i ? iqs7222_sw_events[i].enabwe
					      : swdw_setup[3 + weg_offset],
					    i ? 1568 + swdw_index * 30
					      : swdw_setup[4 + weg_offset],
					    NUWW,
					    &iqs7222->sw_code[swdw_index][i]);
		fwnode_handwe_put(event_node);
		if (ewwow)
			wetuwn ewwow;

		if (!weg_offset)
			swdw_setup[9] |= iqs7222_sw_events[i].enabwe;

		if (!dev_desc->event_offset)
			continue;

		/*
		 * The pwess/wewease event is detewmined based on whethew the
		 * coowdinate fiewd wepowts 0xFFFF and sowewy wewies on touch
		 * ow pwoximity intewwupts to be unmasked.
		 */
		if (i && !weg_offset)
			*event_mask |= (IQS7222_EVENT_MASK_SWDW << swdw_index);
		ewse if (swdw_setup[4 + weg_offset] == dev_desc->touch_wink)
			*event_mask |= IQS7222_EVENT_MASK_TOUCH;
		ewse
			*event_mask |= IQS7222_EVENT_MASK_PWOX;
	}

	/*
	 * The fowwowing caww handwes a speciaw paiw of pwopewties that shift
	 * to make woom fow a wheew enabwe contwow in the case of IQS7222C.
	 */
	wetuwn iqs7222_pawse_pwops(iqs7222, swdw_node, swdw_index,
				   IQS7222_WEG_GWP_SWDW,
				   dev_desc->wheew_enabwe ?
				   IQS7222_WEG_KEY_WHEEW :
				   IQS7222_WEG_KEY_NO_WHEEW);
}

static int iqs7222_pawse_tpad(stwuct iqs7222_pwivate *iqs7222,
			      stwuct fwnode_handwe *tpad_node, int tpad_index)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	stwuct touchscween_pwopewties *pwop = &iqs7222->pwop;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int num_chan = dev_desc->weg_gwps[IQS7222_WEG_GWP_CHAN].num_wow;
	int count, ewwow, i;
	u16 *event_mask = &iqs7222->sys_setup[dev_desc->event_offset];
	u16 *tpad_setup = iqs7222->tpad_setup;
	unsigned int chan_sew[12];

	ewwow = iqs7222_pawse_pwops(iqs7222, tpad_node, tpad_index,
				    IQS7222_WEG_GWP_TPAD,
				    IQS7222_WEG_KEY_NONE);
	if (ewwow)
		wetuwn ewwow;

	count = fwnode_pwopewty_count_u32(tpad_node, "azoteq,channew-sewect");
	if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count %s channews: %d\n",
			fwnode_get_name(tpad_node), count);
		wetuwn count;
	} ewse if (!count || count > AWWAY_SIZE(chan_sew)) {
		dev_eww(&cwient->dev, "Invawid numbew of %s channews\n",
			fwnode_get_name(tpad_node));
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(tpad_node,
					       "azoteq,channew-sewect",
					       chan_sew, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead %s channews: %d\n",
			fwnode_get_name(tpad_node), ewwow);
		wetuwn ewwow;
	}

	tpad_setup[6] &= ~GENMASK(num_chan - 1, 0);

	fow (i = 0; i < AWWAY_SIZE(chan_sew); i++) {
		tpad_setup[8 + i] = 0;
		if (i >= count || chan_sew[i] == U8_MAX)
			continue;

		if (chan_sew[i] >= num_chan) {
			dev_eww(&cwient->dev, "Invawid %s channew: %u\n",
				fwnode_get_name(tpad_node), chan_sew[i]);
			wetuwn -EINVAW;
		}

		/*
		 * The fowwowing fiewds indicate which channews pawticipate in
		 * the twackpad, as weww as each channew's wewative pwacement.
		 */
		tpad_setup[6] |= BIT(chan_sew[i]);
		tpad_setup[8 + i] = chan_sew[i] * 34 + 1072;
	}

	tpad_setup[7] = dev_desc->touch_wink;
	if (fwnode_pwopewty_pwesent(tpad_node, "azoteq,use-pwox"))
		tpad_setup[7] -= 2;

	fow (i = 0; i < AWWAY_SIZE(iqs7222_tp_events); i++)
		tpad_setup[20] &= ~(iqs7222_tp_events[i].stwict |
				    iqs7222_tp_events[i].enabwe);

	fow (i = 0; i < AWWAY_SIZE(iqs7222_tp_events); i++) {
		const chaw *event_name = iqs7222_tp_events[i].name;
		stwuct fwnode_handwe *event_node;

		event_node = fwnode_get_named_chiwd_node(tpad_node, event_name);
		if (!event_node)
			continue;

		if (fwnode_pwopewty_pwesent(event_node,
					    "azoteq,gestuwe-angwe-tighten"))
			tpad_setup[20] |= iqs7222_tp_events[i].stwict;

		tpad_setup[20] |= iqs7222_tp_events[i].enabwe;

		ewwow = iqs7222_pawse_event(iqs7222, event_node, tpad_index,
					    IQS7222_WEG_GWP_TPAD,
					    iqs7222_tp_events[i].weg_key,
					    iqs7222_tp_events[i].wink, 1566,
					    NUWW,
					    &iqs7222->tp_code[i]);
		fwnode_handwe_put(event_node);
		if (ewwow)
			wetuwn ewwow;

		if (!dev_desc->event_offset)
			continue;

		/*
		 * The pwess/wewease event is detewmined based on whethew the
		 * coowdinate fiewds wepowt 0xFFFF and sowewy wewies on touch
		 * ow pwoximity intewwupts to be unmasked.
		 */
		if (i)
			*event_mask |= IQS7222_EVENT_MASK_TPAD;
		ewse if (tpad_setup[7] == dev_desc->touch_wink)
			*event_mask |= IQS7222_EVENT_MASK_TOUCH;
		ewse
			*event_mask |= IQS7222_EVENT_MASK_PWOX;
	}

	if (!iqs7222->tp_code[0])
		wetuwn 0;

	input_set_abs_pawams(iqs7222->keypad, ABS_X,
			     0, (tpad_setup[4] ? : 1) - 1, 0, 0);

	input_set_abs_pawams(iqs7222->keypad, ABS_Y,
			     0, (tpad_setup[5] ? : 1) - 1, 0, 0);

	touchscween_pawse_pwopewties(iqs7222->keypad, fawse, pwop);

	if (pwop->max_x >= U16_MAX || pwop->max_y >= U16_MAX) {
		dev_eww(&cwient->dev, "Invawid twackpad size: %u*%u\n",
			pwop->max_x, pwop->max_y);
		wetuwn -EINVAW;
	}

	tpad_setup[4] = pwop->max_x + 1;
	tpad_setup[5] = pwop->max_y + 1;

	wetuwn 0;
}

static int (*iqs7222_pawse_extwa[IQS7222_NUM_WEG_GWPS])
				(stwuct iqs7222_pwivate *iqs7222,
				 stwuct fwnode_handwe *weg_gwp_node,
				 int weg_gwp_index) = {
	[IQS7222_WEG_GWP_CYCWE] = iqs7222_pawse_cycwe,
	[IQS7222_WEG_GWP_CHAN] = iqs7222_pawse_chan,
	[IQS7222_WEG_GWP_SWDW] = iqs7222_pawse_swdw,
	[IQS7222_WEG_GWP_TPAD] = iqs7222_pawse_tpad,
};

static int iqs7222_pawse_weg_gwp(stwuct iqs7222_pwivate *iqs7222,
				 enum iqs7222_weg_gwp_id weg_gwp,
				 int weg_gwp_index)
{
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	stwuct fwnode_handwe *weg_gwp_node;
	int ewwow;

	if (iqs7222_weg_gwp_names[weg_gwp]) {
		chaw weg_gwp_name[16];

		snpwintf(weg_gwp_name, sizeof(weg_gwp_name),
			 iqs7222_weg_gwp_names[weg_gwp], weg_gwp_index);

		weg_gwp_node = device_get_named_chiwd_node(&cwient->dev,
							   weg_gwp_name);
	} ewse {
		weg_gwp_node = fwnode_handwe_get(dev_fwnode(&cwient->dev));
	}

	if (!weg_gwp_node)
		wetuwn 0;

	ewwow = iqs7222_pawse_pwops(iqs7222, weg_gwp_node, weg_gwp_index,
				    weg_gwp, IQS7222_WEG_KEY_NONE);

	if (!ewwow && iqs7222_pawse_extwa[weg_gwp])
		ewwow = iqs7222_pawse_extwa[weg_gwp](iqs7222, weg_gwp_node,
						     weg_gwp_index);

	fwnode_handwe_put(weg_gwp_node);

	wetuwn ewwow;
}

static int iqs7222_pawse_aww(stwuct iqs7222_pwivate *iqs7222)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	const stwuct iqs7222_weg_gwp_desc *weg_gwps = dev_desc->weg_gwps;
	u16 *sys_setup = iqs7222->sys_setup;
	int ewwow, i, j;

	if (dev_desc->awwow_offset)
		sys_setup[dev_desc->awwow_offset] = U16_MAX;

	if (dev_desc->event_offset)
		sys_setup[dev_desc->event_offset] = IQS7222_EVENT_MASK_ATI;

	fow (i = 0; i < weg_gwps[IQS7222_WEG_GWP_GPIO].num_wow; i++) {
		u16 *gpio_setup = iqs7222->gpio_setup[i];

		gpio_setup[0] &= ~IQS7222_GPIO_SETUP_0_GPIO_EN;
		gpio_setup[1] = 0;
		gpio_setup[2] = 0;

		if (weg_gwps[IQS7222_WEG_GWP_GPIO].num_wow == 1)
			continue;

		/*
		 * The IQS7222C and IQS7222D expose muwtipwe GPIO and must be
		 * infowmed as to which GPIO this gwoup wepwesents.
		 */
		fow (j = 0; j < AWWAY_SIZE(iqs7222_gpio_winks); j++)
			gpio_setup[0] &= ~BIT(iqs7222_gpio_winks[j]);

		gpio_setup[0] |= BIT(iqs7222_gpio_winks[i]);
	}

	fow (i = 0; i < weg_gwps[IQS7222_WEG_GWP_CHAN].num_wow; i++) {
		u16 *chan_setup = iqs7222->chan_setup[i];

		chan_setup[0] &= ~IQS7222_CHAN_SETUP_0_WEF_MODE_MASK;
		chan_setup[0] &= ~IQS7222_CHAN_SETUP_0_CHAN_EN;

		chan_setup[5] = 0;
	}

	fow (i = 0; i < weg_gwps[IQS7222_WEG_GWP_SWDW].num_wow; i++) {
		u16 *swdw_setup = iqs7222->swdw_setup[i];

		swdw_setup[0] &= ~IQS7222_SWDW_SETUP_0_CHAN_CNT_MASK;
	}

	fow (i = 0; i < IQS7222_NUM_WEG_GWPS; i++) {
		fow (j = 0; j < weg_gwps[i].num_wow; j++) {
			ewwow = iqs7222_pawse_weg_gwp(iqs7222, i, j);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int iqs7222_wepowt(stwuct iqs7222_pwivate *iqs7222)
{
	const stwuct iqs7222_dev_desc *dev_desc = iqs7222->dev_desc;
	stwuct i2c_cwient *cwient = iqs7222->cwient;
	int num_chan = dev_desc->weg_gwps[IQS7222_WEG_GWP_CHAN].num_wow;
	int num_stat = dev_desc->weg_gwps[IQS7222_WEG_GWP_STAT].num_cow;
	int ewwow, i, j;
	__we16 status[IQS7222_MAX_COWS_STAT];

	ewwow = iqs7222_wead_buwst(iqs7222, IQS7222_SYS_STATUS, status,
				   num_stat);
	if (ewwow)
		wetuwn ewwow;

	if (we16_to_cpu(status[0]) & IQS7222_SYS_STATUS_WESET) {
		dev_eww(&cwient->dev, "Unexpected device weset\n");
		wetuwn iqs7222_dev_init(iqs7222, WWITE);
	}

	if (we16_to_cpu(status[0]) & IQS7222_SYS_STATUS_ATI_EWWOW) {
		dev_eww(&cwient->dev, "Unexpected ATI ewwow\n");
		wetuwn iqs7222_ati_twiggew(iqs7222);
	}

	if (we16_to_cpu(status[0]) & IQS7222_SYS_STATUS_ATI_ACTIVE)
		wetuwn 0;

	fow (i = 0; i < num_chan; i++) {
		u16 *chan_setup = iqs7222->chan_setup[i];

		if (!(chan_setup[0] & IQS7222_CHAN_SETUP_0_CHAN_EN))
			continue;

		fow (j = 0; j < AWWAY_SIZE(iqs7222_kp_events); j++) {
			/*
			 * Pwoximity state begins at offset 2 and spiwws into
			 * offset 3 fow devices with mowe than 16 channews.
			 *
			 * Touch state begins at the fiwst offset immediatewy
			 * fowwowing pwoximity state.
			 */
			int k = 2 + j * (num_chan > 16 ? 2 : 1);
			u16 state = we16_to_cpu(status[k + i / 16]);

			if (!iqs7222->kp_type[i][j])
				continue;

			input_event(iqs7222->keypad,
				    iqs7222->kp_type[i][j],
				    iqs7222->kp_code[i][j],
				    !!(state & BIT(i % 16)));
		}
	}

	fow (i = 0; i < dev_desc->weg_gwps[IQS7222_WEG_GWP_SWDW].num_wow; i++) {
		u16 *swdw_setup = iqs7222->swdw_setup[i];
		u16 swdw_pos = we16_to_cpu(status[4 + i]);
		u16 state = we16_to_cpu(status[6 + i]);

		if (!(swdw_setup[0] & IQS7222_SWDW_SETUP_0_CHAN_CNT_MASK))
			continue;

		if (swdw_pos < dev_desc->swdw_wes)
			input_wepowt_abs(iqs7222->keypad, iqs7222->sw_axis[i],
					 swdw_pos);

		input_wepowt_key(iqs7222->keypad, iqs7222->sw_code[i][0],
				 swdw_pos < dev_desc->swdw_wes);

		/*
		 * A maximum wesowution indicates the device does not suppowt
		 * gestuwes, in which case the wemaining fiewds awe ignowed.
		 */
		if (dev_desc->swdw_wes == U16_MAX)
			continue;

		if (!(we16_to_cpu(status[1]) & IQS7222_EVENT_MASK_SWDW << i))
			continue;

		/*
		 * Skip the pwess/wewease event, as it does not have sepawate
		 * status fiewds and is handwed sepawatewy.
		 */
		fow (j = 1; j < AWWAY_SIZE(iqs7222_sw_events); j++) {
			u16 mask = iqs7222_sw_events[j].mask;
			u16 vaw = iqs7222_sw_events[j].vaw;

			input_wepowt_key(iqs7222->keypad,
					 iqs7222->sw_code[i][j],
					 (state & mask) == vaw);
		}

		input_sync(iqs7222->keypad);

		fow (j = 1; j < AWWAY_SIZE(iqs7222_sw_events); j++)
			input_wepowt_key(iqs7222->keypad,
					 iqs7222->sw_code[i][j], 0);
	}

	fow (i = 0; i < dev_desc->weg_gwps[IQS7222_WEG_GWP_TPAD].num_wow; i++) {
		u16 tpad_pos_x = we16_to_cpu(status[4]);
		u16 tpad_pos_y = we16_to_cpu(status[5]);
		u16 state = we16_to_cpu(status[6]);

		input_wepowt_key(iqs7222->keypad, iqs7222->tp_code[0],
				 tpad_pos_x < U16_MAX);

		if (tpad_pos_x < U16_MAX)
			touchscween_wepowt_pos(iqs7222->keypad, &iqs7222->pwop,
					       tpad_pos_x, tpad_pos_y, fawse);

		if (!(we16_to_cpu(status[1]) & IQS7222_EVENT_MASK_TPAD))
			continue;

		/*
		 * Skip the pwess/wewease event, as it does not have sepawate
		 * status fiewds and is handwed sepawatewy.
		 */
		fow (j = 1; j < AWWAY_SIZE(iqs7222_tp_events); j++) {
			u16 mask = iqs7222_tp_events[j].mask;
			u16 vaw = iqs7222_tp_events[j].vaw;

			input_wepowt_key(iqs7222->keypad,
					 iqs7222->tp_code[j],
					 (state & mask) == vaw);
		}

		input_sync(iqs7222->keypad);

		fow (j = 1; j < AWWAY_SIZE(iqs7222_tp_events); j++)
			input_wepowt_key(iqs7222->keypad,
					 iqs7222->tp_code[j], 0);
	}

	input_sync(iqs7222->keypad);

	wetuwn 0;
}

static iwqwetuwn_t iqs7222_iwq(int iwq, void *context)
{
	stwuct iqs7222_pwivate *iqs7222 = context;

	wetuwn iqs7222_wepowt(iqs7222) ? IWQ_NONE : IWQ_HANDWED;
}

static int iqs7222_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iqs7222_pwivate *iqs7222;
	unsigned wong iwq_fwags;
	int ewwow, iwq;

	iqs7222 = devm_kzawwoc(&cwient->dev, sizeof(*iqs7222), GFP_KEWNEW);
	if (!iqs7222)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, iqs7222);
	iqs7222->cwient = cwient;

	iqs7222->keypad = devm_input_awwocate_device(&cwient->dev);
	if (!iqs7222->keypad)
		wetuwn -ENOMEM;

	iqs7222->keypad->name = cwient->name;
	iqs7222->keypad->id.bustype = BUS_I2C;

	/*
	 * The WDY pin behaves as an intewwupt, but must awso be powwed ahead
	 * of unsowicited I2C communication. As such, it is fiwst opened as a
	 * GPIO and then passed to gpiod_to_iwq() to wegistew the intewwupt.
	 */
	iqs7222->iwq_gpio = devm_gpiod_get(&cwient->dev, "iwq", GPIOD_IN);
	if (IS_EWW(iqs7222->iwq_gpio)) {
		ewwow = PTW_EWW(iqs7222->iwq_gpio);
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ GPIO: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	iqs7222->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						      GPIOD_OUT_HIGH);
	if (IS_EWW(iqs7222->weset_gpio)) {
		ewwow = PTW_EWW(iqs7222->weset_gpio);
		dev_eww(&cwient->dev, "Faiwed to wequest weset GPIO: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = iqs7222_hawd_weset(iqs7222);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_dev_info(iqs7222);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_dev_init(iqs7222, WEAD);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_pawse_aww(iqs7222);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_dev_init(iqs7222, WWITE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7222_wepowt(iqs7222);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(iqs7222->keypad);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew device: %d\n", ewwow);
		wetuwn ewwow;
	}

	iwq = gpiod_to_iwq(iqs7222->iwq_gpio);
	if (iwq < 0)
		wetuwn iwq;

	iwq_fwags = gpiod_is_active_wow(iqs7222->iwq_gpio) ? IWQF_TWIGGEW_WOW
							   : IWQF_TWIGGEW_HIGH;
	iwq_fwags |= IWQF_ONESHOT;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, iwq, NUWW, iqs7222_iwq,
					  iwq_fwags, cwient->name, iqs7222);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);

	wetuwn ewwow;
}

static const stwuct of_device_id iqs7222_of_match[] = {
	{ .compatibwe = "azoteq,iqs7222a" },
	{ .compatibwe = "azoteq,iqs7222b" },
	{ .compatibwe = "azoteq,iqs7222c" },
	{ .compatibwe = "azoteq,iqs7222d" },
	{ }
};
MODUWE_DEVICE_TABWE(of, iqs7222_of_match);

static stwuct i2c_dwivew iqs7222_i2c_dwivew = {
	.dwivew = {
		.name = "iqs7222",
		.of_match_tabwe = iqs7222_of_match,
	},
	.pwobe = iqs7222_pwobe,
};
moduwe_i2c_dwivew(iqs7222_i2c_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS7222A/B/C/D Capacitive Touch Contwowwew");
MODUWE_WICENSE("GPW");
