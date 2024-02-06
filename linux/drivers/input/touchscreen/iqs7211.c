// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Azoteq IQS7210A/7211A/E Twackpad/Touchscween Contwowwew
 *
 * Copywight (C) 2023 Jeff WaBundy <jeff@wabundy.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define IQS7211_PWOD_NUM			0x00

#define IQS7211_EVENT_MASK_AWW			GENMASK(14, 8)
#define IQS7211_EVENT_MASK_AWP			BIT(13)
#define IQS7211_EVENT_MASK_BTN			BIT(12)
#define IQS7211_EVENT_MASK_ATI			BIT(11)
#define IQS7211_EVENT_MASK_MOVE			BIT(10)
#define IQS7211_EVENT_MASK_GSTW			BIT(9)
#define IQS7211_EVENT_MODE			BIT(8)

#define IQS7211_COMMS_EWWOW			0xEEEE
#define IQS7211_COMMS_WETWY_MS			50
#define IQS7211_COMMS_SWEEP_US			100
#define IQS7211_COMMS_TIMEOUT_US		(100 * USEC_PEW_MSEC)
#define IQS7211_WESET_TIMEOUT_MS		150
#define IQS7211_STAWT_TIMEOUT_US		(1 * USEC_PEW_SEC)

#define IQS7211_NUM_WETWIES			5
#define IQS7211_NUM_CWX				8
#define IQS7211_MAX_CTX				13

#define IQS7211_MAX_CONTACTS			2
#define IQS7211_MAX_CYCWES			21

/*
 * The fowwowing deway is used duwing instances that must wait fow the open-
 * dwain WDY pin to settwe. Its vawue is cawcuwated as 5*W*C, whewe W and C
 * wepwesent typicaw datasheet vawues of 4.7k and 100 nF, wespectivewy.
 */
#define iqs7211_iwq_wait()			usweep_wange(2500, 2600)

enum iqs7211_dev_id {
	IQS7210A,
	IQS7211A,
	IQS7211E,
};

enum iqs7211_comms_mode {
	IQS7211_COMMS_MODE_WAIT,
	IQS7211_COMMS_MODE_FWEE,
	IQS7211_COMMS_MODE_FOWCE,
};

stwuct iqs7211_weg_fiewd_desc {
	stwuct wist_head wist;
	u8 addw;
	u16 mask;
	u16 vaw;
};

enum iqs7211_weg_key_id {
	IQS7211_WEG_KEY_NONE,
	IQS7211_WEG_KEY_PWOX,
	IQS7211_WEG_KEY_TOUCH,
	IQS7211_WEG_KEY_TAP,
	IQS7211_WEG_KEY_HOWD,
	IQS7211_WEG_KEY_PAWM,
	IQS7211_WEG_KEY_AXIAW_X,
	IQS7211_WEG_KEY_AXIAW_Y,
	IQS7211_WEG_KEY_WESEWVED
};

enum iqs7211_weg_gwp_id {
	IQS7211_WEG_GWP_TP,
	IQS7211_WEG_GWP_BTN,
	IQS7211_WEG_GWP_AWP,
	IQS7211_WEG_GWP_SYS,
	IQS7211_NUM_WEG_GWPS
};

static const chaw * const iqs7211_weg_gwp_names[IQS7211_NUM_WEG_GWPS] = {
	[IQS7211_WEG_GWP_TP] = "twackpad",
	[IQS7211_WEG_GWP_BTN] = "button",
	[IQS7211_WEG_GWP_AWP] = "awp",
};

static const u16 iqs7211_weg_gwp_masks[IQS7211_NUM_WEG_GWPS] = {
	[IQS7211_WEG_GWP_TP] = IQS7211_EVENT_MASK_GSTW,
	[IQS7211_WEG_GWP_BTN] = IQS7211_EVENT_MASK_BTN,
	[IQS7211_WEG_GWP_AWP] = IQS7211_EVENT_MASK_AWP,
};

stwuct iqs7211_event_desc {
	const chaw *name;
	u16 mask;
	u16 enabwe;
	enum iqs7211_weg_gwp_id weg_gwp;
	enum iqs7211_weg_key_id weg_key;
};

static const stwuct iqs7211_event_desc iqs7210a_kp_events[] = {
	{
		.mask = BIT(10),
		.enabwe = BIT(13) | BIT(12),
		.weg_gwp = IQS7211_WEG_GWP_AWP,
	},
	{
		.name = "event-pwox",
		.mask = BIT(2),
		.enabwe = BIT(5) | BIT(4),
		.weg_gwp = IQS7211_WEG_GWP_BTN,
		.weg_key = IQS7211_WEG_KEY_PWOX,
	},
	{
		.name = "event-touch",
		.mask = BIT(3),
		.enabwe = BIT(5) | BIT(4),
		.weg_gwp = IQS7211_WEG_GWP_BTN,
		.weg_key = IQS7211_WEG_KEY_TOUCH,
	},
	{
		.name = "event-tap",
		.mask = BIT(0),
		.enabwe = BIT(0),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_TAP,
	},
	{
		.name = "event-howd",
		.mask = BIT(1),
		.enabwe = BIT(1),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-swipe-x-neg",
		.mask = BIT(2),
		.enabwe = BIT(2),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-x-pos",
		.mask = BIT(3),
		.enabwe = BIT(3),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-y-pos",
		.mask = BIT(4),
		.enabwe = BIT(4),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
	{
		.name = "event-swipe-y-neg",
		.mask = BIT(5),
		.enabwe = BIT(5),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
};

static const stwuct iqs7211_event_desc iqs7211a_kp_events[] = {
	{
		.mask = BIT(14),
		.weg_gwp = IQS7211_WEG_GWP_AWP,
	},
	{
		.name = "event-tap",
		.mask = BIT(0),
		.enabwe = BIT(0),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_TAP,
	},
	{
		.name = "event-howd",
		.mask = BIT(1),
		.enabwe = BIT(1),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-swipe-x-neg",
		.mask = BIT(2),
		.enabwe = BIT(2),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-x-pos",
		.mask = BIT(3),
		.enabwe = BIT(3),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-y-pos",
		.mask = BIT(4),
		.enabwe = BIT(4),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
	{
		.name = "event-swipe-y-neg",
		.mask = BIT(5),
		.enabwe = BIT(5),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
};

static const stwuct iqs7211_event_desc iqs7211e_kp_events[] = {
	{
		.mask = BIT(14),
		.weg_gwp = IQS7211_WEG_GWP_AWP,
	},
	{
		.name = "event-tap",
		.mask = BIT(0),
		.enabwe = BIT(0),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_TAP,
	},
	{
		.name = "event-tap-doubwe",
		.mask = BIT(1),
		.enabwe = BIT(1),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_TAP,
	},
	{
		.name = "event-tap-twipwe",
		.mask = BIT(2),
		.enabwe = BIT(2),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_TAP,
	},
	{
		.name = "event-howd",
		.mask = BIT(3),
		.enabwe = BIT(3),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-pawm",
		.mask = BIT(4),
		.enabwe = BIT(4),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_PAWM,
	},
	{
		.name = "event-swipe-x-pos",
		.mask = BIT(8),
		.enabwe = BIT(8),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-x-neg",
		.mask = BIT(9),
		.enabwe = BIT(9),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
	},
	{
		.name = "event-swipe-y-pos",
		.mask = BIT(10),
		.enabwe = BIT(10),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
	{
		.name = "event-swipe-y-neg",
		.mask = BIT(11),
		.enabwe = BIT(11),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
	},
	{
		.name = "event-swipe-x-pos-howd",
		.mask = BIT(12),
		.enabwe = BIT(12),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-swipe-x-neg-howd",
		.mask = BIT(13),
		.enabwe = BIT(13),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-swipe-y-pos-howd",
		.mask = BIT(14),
		.enabwe = BIT(14),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
	{
		.name = "event-swipe-y-neg-howd",
		.mask = BIT(15),
		.enabwe = BIT(15),
		.weg_gwp = IQS7211_WEG_GWP_TP,
		.weg_key = IQS7211_WEG_KEY_HOWD,
	},
};

stwuct iqs7211_dev_desc {
	const chaw *tp_name;
	const chaw *kp_name;
	u16 pwod_num;
	u16 show_weset;
	u16 ati_ewwow[IQS7211_NUM_WEG_GWPS];
	u16 ati_stawt[IQS7211_NUM_WEG_GWPS];
	u16 suspend;
	u16 ack_weset;
	u16 comms_end;
	u16 comms_weq;
	int chawge_shift;
	int info_offs;
	int gestuwe_offs;
	int contact_offs;
	u8 sys_stat;
	u8 sys_ctww;
	u8 awp_config;
	u8 tp_config;
	u8 exp_fiwe;
	u8 kp_enabwe[IQS7211_NUM_WEG_GWPS];
	u8 gestuwe_angwe;
	u8 wx_tx_map;
	u8 cycwe_awwoc[2];
	u8 cycwe_wimit[2];
	const stwuct iqs7211_event_desc *kp_events;
	int num_kp_events;
	int min_cwx_awp;
	int num_ctx;
};

static const stwuct iqs7211_dev_desc iqs7211_devs[] = {
	[IQS7210A] = {
		.tp_name = "iqs7210a_twackpad",
		.kp_name = "iqs7210a_keys",
		.pwod_num = 944,
		.show_weset = BIT(15),
		.ati_ewwow = {
			[IQS7211_WEG_GWP_TP] = BIT(12),
			[IQS7211_WEG_GWP_BTN] = BIT(0),
			[IQS7211_WEG_GWP_AWP] = BIT(8),
		},
		.ati_stawt = {
			[IQS7211_WEG_GWP_TP] = BIT(13),
			[IQS7211_WEG_GWP_BTN] = BIT(1),
			[IQS7211_WEG_GWP_AWP] = BIT(9),
		},
		.suspend = BIT(11),
		.ack_weset = BIT(7),
		.comms_end = BIT(2),
		.comms_weq = BIT(1),
		.chawge_shift = 4,
		.info_offs = 0,
		.gestuwe_offs = 1,
		.contact_offs = 4,
		.sys_stat = 0x0A,
		.sys_ctww = 0x35,
		.awp_config = 0x39,
		.tp_config = 0x4E,
		.exp_fiwe = 0x57,
		.kp_enabwe = {
			[IQS7211_WEG_GWP_TP] = 0x58,
			[IQS7211_WEG_GWP_BTN] = 0x37,
			[IQS7211_WEG_GWP_AWP] = 0x37,
		},
		.gestuwe_angwe = 0x5F,
		.wx_tx_map = 0x60,
		.cycwe_awwoc = { 0x66, 0x75, },
		.cycwe_wimit = { 10, 6, },
		.kp_events = iqs7210a_kp_events,
		.num_kp_events = AWWAY_SIZE(iqs7210a_kp_events),
		.min_cwx_awp = 4,
		.num_ctx = IQS7211_MAX_CTX - 1,
	},
	[IQS7211A] = {
		.tp_name = "iqs7211a_twackpad",
		.kp_name = "iqs7211a_keys",
		.pwod_num = 763,
		.show_weset = BIT(7),
		.ati_ewwow = {
			[IQS7211_WEG_GWP_TP] = BIT(3),
			[IQS7211_WEG_GWP_AWP] = BIT(5),
		},
		.ati_stawt = {
			[IQS7211_WEG_GWP_TP] = BIT(5),
			[IQS7211_WEG_GWP_AWP] = BIT(6),
		},
		.ack_weset = BIT(7),
		.comms_weq = BIT(4),
		.chawge_shift = 0,
		.info_offs = 0,
		.gestuwe_offs = 1,
		.contact_offs = 4,
		.sys_stat = 0x10,
		.sys_ctww = 0x50,
		.tp_config = 0x60,
		.awp_config = 0x72,
		.exp_fiwe = 0x74,
		.kp_enabwe = {
			[IQS7211_WEG_GWP_TP] = 0x80,
		},
		.gestuwe_angwe = 0x87,
		.wx_tx_map = 0x90,
		.cycwe_awwoc = { 0xA0, 0xB0, },
		.cycwe_wimit = { 10, 8, },
		.kp_events = iqs7211a_kp_events,
		.num_kp_events = AWWAY_SIZE(iqs7211a_kp_events),
		.num_ctx = IQS7211_MAX_CTX - 1,
	},
	[IQS7211E] = {
		.tp_name = "iqs7211e_twackpad",
		.kp_name = "iqs7211e_keys",
		.pwod_num = 1112,
		.show_weset = BIT(7),
		.ati_ewwow = {
			[IQS7211_WEG_GWP_TP] = BIT(3),
			[IQS7211_WEG_GWP_AWP] = BIT(5),
		},
		.ati_stawt = {
			[IQS7211_WEG_GWP_TP] = BIT(5),
			[IQS7211_WEG_GWP_AWP] = BIT(6),
		},
		.suspend = BIT(11),
		.ack_weset = BIT(7),
		.comms_end = BIT(6),
		.comms_weq = BIT(4),
		.chawge_shift = 0,
		.info_offs = 1,
		.gestuwe_offs = 0,
		.contact_offs = 2,
		.sys_stat = 0x0E,
		.sys_ctww = 0x33,
		.tp_config = 0x41,
		.awp_config = 0x36,
		.exp_fiwe = 0x4A,
		.kp_enabwe = {
			[IQS7211_WEG_GWP_TP] = 0x4B,
		},
		.gestuwe_angwe = 0x55,
		.wx_tx_map = 0x56,
		.cycwe_awwoc = { 0x5D, 0x6C, },
		.cycwe_wimit = { 10, 11, },
		.kp_events = iqs7211e_kp_events,
		.num_kp_events = AWWAY_SIZE(iqs7211e_kp_events),
		.num_ctx = IQS7211_MAX_CTX,
	},
};

stwuct iqs7211_pwop_desc {
	const chaw *name;
	enum iqs7211_weg_key_id weg_key;
	u8 weg_addw[IQS7211_NUM_WEG_GWPS][AWWAY_SIZE(iqs7211_devs)];
	int weg_shift;
	int weg_width;
	int vaw_pitch;
	int vaw_min;
	int vaw_max;
	const chaw *wabew;
};

static const stwuct iqs7211_pwop_desc iqs7211_pwops[] = {
	{
		.name = "azoteq,ati-fwac-div-fine",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x1E,
				[IQS7211A] = 0x30,
				[IQS7211E] = 0x21,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x22,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x23,
				[IQS7211A] = 0x36,
				[IQS7211E] = 0x25,
			},
		},
		.weg_shift = 9,
		.weg_width = 5,
		.wabew = "ATI fine fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-fwac-muwt-coawse",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x1E,
				[IQS7211A] = 0x30,
				[IQS7211E] = 0x21,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x22,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x23,
				[IQS7211A] = 0x36,
				[IQS7211E] = 0x25,
			},
		},
		.weg_shift = 5,
		.weg_width = 4,
		.wabew = "ATI coawse fwactionaw muwtipwiew",
	},
	{
		.name = "azoteq,ati-fwac-div-coawse",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x1E,
				[IQS7211A] = 0x30,
				[IQS7211E] = 0x21,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x22,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x23,
				[IQS7211A] = 0x36,
				[IQS7211E] = 0x25,
			},
		},
		.weg_shift = 0,
		.weg_width = 5,
		.wabew = "ATI coawse fwactionaw dividew",
	},
	{
		.name = "azoteq,ati-comp-div",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x1F,
				[IQS7211E] = 0x22,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x24,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7211E] = 0x26,
			},
		},
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_max = 31,
		.wabew = "ATI compensation dividew",
	},
	{
		.name = "azoteq,ati-comp-div",
		.weg_addw = {
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x24,
			},
		},
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_max = 31,
		.wabew = "ATI compensation dividew",
	},
	{
		.name = "azoteq,ati-comp-div",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7211A] = 0x31,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7211A] = 0x37,
			},
		},
		.vaw_max = 31,
		.wabew = "ATI compensation dividew",
	},
	{
		.name = "azoteq,ati-tawget",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x20,
				[IQS7211A] = 0x32,
				[IQS7211E] = 0x23,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x27,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x28,
				[IQS7211A] = 0x38,
				[IQS7211E] = 0x27,
			},
		},
		.wabew = "ATI tawget",
	},
	{
		.name = "azoteq,ati-base",
		.weg_addw[IQS7211_WEG_GWP_AWP] = {
			[IQS7210A] = 0x26,
		},
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 8,
		.wabew = "ATI base",
	},
	{
		.name = "azoteq,ati-base",
		.weg_addw[IQS7211_WEG_GWP_BTN] = {
			[IQS7210A] = 0x26,
		},
		.weg_shift = 0,
		.weg_width = 8,
		.vaw_pitch = 8,
		.wabew = "ATI base",
	},
	{
		.name = "azoteq,wate-active-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x29,
			[IQS7211A] = 0x40,
			[IQS7211E] = 0x28,
		},
		.wabew = "active mode wepowt wate",
	},
	{
		.name = "azoteq,wate-touch-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2A,
			[IQS7211A] = 0x41,
			[IQS7211E] = 0x29,
		},
		.wabew = "idwe-touch mode wepowt wate",
	},
	{
		.name = "azoteq,wate-idwe-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2B,
			[IQS7211A] = 0x42,
			[IQS7211E] = 0x2A,
		},
		.wabew = "idwe mode wepowt wate",
	},
	{
		.name = "azoteq,wate-wp1-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2C,
			[IQS7211A] = 0x43,
			[IQS7211E] = 0x2B,
		},
		.wabew = "wow-powew mode 1 wepowt wate",
	},
	{
		.name = "azoteq,wate-wp2-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2D,
			[IQS7211A] = 0x44,
			[IQS7211E] = 0x2C,
		},
		.wabew = "wow-powew mode 2 wepowt wate",
	},
	{
		.name = "azoteq,timeout-active-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2E,
			[IQS7211A] = 0x45,
			[IQS7211E] = 0x2D,
		},
		.vaw_pitch = 1000,
		.wabew = "active mode timeout",
	},
	{
		.name = "azoteq,timeout-touch-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x2F,
			[IQS7211A] = 0x46,
			[IQS7211E] = 0x2E,
		},
		.vaw_pitch = 1000,
		.wabew = "idwe-touch mode timeout",
	},
	{
		.name = "azoteq,timeout-idwe-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x30,
			[IQS7211A] = 0x47,
			[IQS7211E] = 0x2F,
		},
		.vaw_pitch = 1000,
		.wabew = "idwe mode timeout",
	},
	{
		.name = "azoteq,timeout-wp1-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x31,
			[IQS7211A] = 0x48,
			[IQS7211E] = 0x30,
		},
		.vaw_pitch = 1000,
		.wabew = "wow-powew mode 1 timeout",
	},
	{
		.name = "azoteq,timeout-wp2-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x32,
			[IQS7211E] = 0x31,
		},
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_pitch = 1000,
		.vaw_max = 60000,
		.wabew = "twackpad wefewence vawue update wate",
	},
	{
		.name = "azoteq,timeout-wp2-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7211A] = 0x49,
		},
		.vaw_pitch = 1000,
		.vaw_max = 60000,
		.wabew = "twackpad wefewence vawue update wate",
	},
	{
		.name = "azoteq,timeout-ati-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x32,
			[IQS7211E] = 0x31,
		},
		.weg_width = 8,
		.vaw_pitch = 1000,
		.vaw_max = 60000,
		.wabew = "ATI ewwow timeout",
	},
	{
		.name = "azoteq,timeout-ati-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7211A] = 0x35,
		},
		.vaw_pitch = 1000,
		.vaw_max = 60000,
		.wabew = "ATI ewwow timeout",
	},
	{
		.name = "azoteq,timeout-comms-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x33,
			[IQS7211A] = 0x4A,
			[IQS7211E] = 0x32,
		},
		.wabew = "communication timeout",
	},
	{
		.name = "azoteq,timeout-pwess-ms",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x34,
		},
		.weg_width = 8,
		.vaw_pitch = 1000,
		.vaw_max = 60000,
		.wabew = "pwess timeout",
	},
	{
		.name = "azoteq,ati-mode",
		.weg_addw[IQS7211_WEG_GWP_AWP] = {
			[IQS7210A] = 0x37,
		},
		.weg_shift = 15,
		.weg_width = 1,
		.wabew = "ATI mode",
	},
	{
		.name = "azoteq,ati-mode",
		.weg_addw[IQS7211_WEG_GWP_BTN] = {
			[IQS7210A] = 0x37,
		},
		.weg_shift = 7,
		.weg_width = 1,
		.wabew = "ATI mode",
	},
	{
		.name = "azoteq,sense-mode",
		.weg_addw[IQS7211_WEG_GWP_AWP] = {
			[IQS7210A] = 0x37,
			[IQS7211A] = 0x72,
			[IQS7211E] = 0x36,
		},
		.weg_shift = 8,
		.weg_width = 1,
		.wabew = "sensing mode",
	},
	{
		.name = "azoteq,sense-mode",
		.weg_addw[IQS7211_WEG_GWP_BTN] = {
			[IQS7210A] = 0x37,
		},
		.weg_shift = 0,
		.weg_width = 2,
		.vaw_max = 2,
		.wabew = "sensing mode",
	},
	{
		.name = "azoteq,fosc-fweq",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x38,
			[IQS7211A] = 0x52,
			[IQS7211E] = 0x35,
		},
		.weg_shift = 4,
		.weg_width = 1,
		.wabew = "cowe cwock fwequency sewection",
	},
	{
		.name = "azoteq,fosc-twim",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x38,
			[IQS7211A] = 0x52,
			[IQS7211E] = 0x35,
		},
		.weg_shift = 0,
		.weg_width = 4,
		.wabew = "cowe cwock fwequency twim",
	},
	{
		.name = "azoteq,touch-exit",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x3B,
				[IQS7211A] = 0x53,
				[IQS7211E] = 0x38,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x3E,
			},
		},
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "touch exit factow",
	},
	{
		.name = "azoteq,touch-entew",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x3B,
				[IQS7211A] = 0x53,
				[IQS7211E] = 0x38,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x3E,
			},
		},
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "touch entwance factow",
	},
	{
		.name = "azoteq,thwesh",
		.weg_addw = {
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x3C,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x3D,
				[IQS7211A] = 0x54,
				[IQS7211E] = 0x39,
			},
		},
		.wabew = "thweshowd",
	},
	{
		.name = "azoteq,debounce-exit",
		.weg_addw = {
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x3F,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x40,
				[IQS7211A] = 0x56,
				[IQS7211E] = 0x3A,
			},
		},
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "debounce exit factow",
	},
	{
		.name = "azoteq,debounce-entew",
		.weg_addw = {
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x3F,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x40,
				[IQS7211A] = 0x56,
				[IQS7211E] = 0x3A,
			},
		},
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "debounce entwance factow",
	},
	{
		.name = "azoteq,conv-fwac",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x48,
				[IQS7211A] = 0x58,
				[IQS7211E] = 0x3D,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x49,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x4A,
				[IQS7211A] = 0x59,
				[IQS7211E] = 0x3E,
			},
		},
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "convewsion fwequency fwactionaw dividew",
	},
	{
		.name = "azoteq,conv-pewiod",
		.weg_addw = {
			[IQS7211_WEG_GWP_TP] = {
				[IQS7210A] = 0x48,
				[IQS7211A] = 0x58,
				[IQS7211E] = 0x3D,
			},
			[IQS7211_WEG_GWP_BTN] = {
				[IQS7210A] = 0x49,
			},
			[IQS7211_WEG_GWP_AWP] = {
				[IQS7210A] = 0x4A,
				[IQS7211A] = 0x59,
				[IQS7211E] = 0x3E,
			},
		},
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "convewsion pewiod",
	},
	{
		.name = "azoteq,thwesh",
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x55,
			[IQS7211A] = 0x67,
			[IQS7211E] = 0x48,
		},
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "thweshowd",
	},
	{
		.name = "azoteq,contact-spwit",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x55,
			[IQS7211A] = 0x67,
			[IQS7211E] = 0x48,
		},
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "contact spwit factow",
	},
	{
		.name = "azoteq,twim-x",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x56,
			[IQS7211E] = 0x49,
		},
		.weg_shift = 0,
		.weg_width = 8,
		.wabew = "howizontaw twim width",
	},
	{
		.name = "azoteq,twim-x",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7211A] = 0x68,
		},
		.wabew = "howizontaw twim width",
	},
	{
		.name = "azoteq,twim-y",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7210A] = 0x56,
			[IQS7211E] = 0x49,
		},
		.weg_shift = 8,
		.weg_width = 8,
		.wabew = "vewticaw twim height",
	},
	{
		.name = "azoteq,twim-y",
		.weg_addw[IQS7211_WEG_GWP_SYS] = {
			[IQS7211A] = 0x69,
		},
		.wabew = "vewticaw twim height",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_key = IQS7211_WEG_KEY_TAP,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x59,
			[IQS7211A] = 0x81,
			[IQS7211E] = 0x4C,
		},
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-mid-ms",
		.weg_key = IQS7211_WEG_KEY_TAP,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7211E] = 0x4D,
		},
		.wabew = "wepeated gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_key = IQS7211_WEG_KEY_TAP,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5A,
			[IQS7211A] = 0x82,
			[IQS7211E] = 0x4E,
		},
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_key = IQS7211_WEG_KEY_HOWD,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5A,
			[IQS7211A] = 0x82,
			[IQS7211E] = 0x4E,
		},
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-min-ms",
		.weg_key = IQS7211_WEG_KEY_HOWD,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5B,
			[IQS7211A] = 0x83,
			[IQS7211E] = 0x4F,
		},
		.wabew = "minimum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5C,
			[IQS7211A] = 0x84,
			[IQS7211E] = 0x50,
		},
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-max-ms",
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5C,
			[IQS7211A] = 0x84,
			[IQS7211E] = 0x50,
		},
		.wabew = "maximum gestuwe time",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5D,
			[IQS7211A] = 0x85,
			[IQS7211E] = 0x51,
		},
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist",
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7210A] = 0x5E,
			[IQS7211A] = 0x86,
			[IQS7211E] = 0x52,
		},
		.wabew = "gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist-wep",
		.weg_key = IQS7211_WEG_KEY_AXIAW_X,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7211E] = 0x53,
		},
		.wabew = "wepeated gestuwe distance",
	},
	{
		.name = "azoteq,gestuwe-dist-wep",
		.weg_key = IQS7211_WEG_KEY_AXIAW_Y,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7211E] = 0x54,
		},
		.wabew = "wepeated gestuwe distance",
	},
	{
		.name = "azoteq,thwesh",
		.weg_key = IQS7211_WEG_KEY_PAWM,
		.weg_addw[IQS7211_WEG_GWP_TP] = {
			[IQS7211E] = 0x55,
		},
		.weg_shift = 8,
		.weg_width = 8,
		.vaw_max = 42,
		.wabew = "thweshowd",
	},
};

static const u8 iqs7211_gestuwe_angwe[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x06, 0x07, 0x08,
	0x09, 0x0A, 0x0B, 0x0C,
	0x0E, 0x0F, 0x10, 0x11,
	0x12, 0x14, 0x15, 0x16,
	0x17, 0x19, 0x1A, 0x1B,
	0x1C, 0x1E, 0x1F, 0x21,
	0x22, 0x23, 0x25, 0x26,
	0x28, 0x2A, 0x2B, 0x2D,
	0x2E, 0x30, 0x32, 0x34,
	0x36, 0x38, 0x3A, 0x3C,
	0x3E, 0x40, 0x42, 0x45,
	0x47, 0x4A, 0x4C, 0x4F,
	0x52, 0x55, 0x58, 0x5B,
	0x5F, 0x63, 0x66, 0x6B,
	0x6F, 0x73, 0x78, 0x7E,
	0x83, 0x89, 0x90, 0x97,
	0x9E, 0xA7, 0xB0, 0xBA,
	0xC5, 0xD1, 0xDF, 0xEF,
};

stwuct iqs7211_vew_info {
	__we16 pwod_num;
	__we16 majow;
	__we16 minow;
	__we32 patch;
} __packed;

stwuct iqs7211_touch_data {
	__we16 abs_x;
	__we16 abs_y;
	__we16 pwessuwe;
	__we16 awea;
} __packed;

stwuct iqs7211_tp_config {
	u8 tp_settings;
	u8 totaw_wx;
	u8 totaw_tx;
	u8 num_contacts;
	__we16 max_x;
	__we16 max_y;
} __packed;

stwuct iqs7211_pwivate {
	const stwuct iqs7211_dev_desc *dev_desc;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *iwq_gpio;
	stwuct i2c_cwient *cwient;
	stwuct input_dev *tp_idev;
	stwuct input_dev *kp_idev;
	stwuct iqs7211_vew_info vew_info;
	stwuct iqs7211_tp_config tp_config;
	stwuct touchscween_pwopewties pwop;
	stwuct wist_head weg_fiewd_head;
	enum iqs7211_comms_mode comms_init;
	enum iqs7211_comms_mode comms_mode;
	unsigned int num_contacts;
	unsigned int kp_code[AWWAY_SIZE(iqs7211e_kp_events)];
	u8 wx_tx_map[IQS7211_MAX_CTX + 1];
	u8 cycwe_awwoc[2][33];
	u8 exp_fiwe[2];
	u16 event_mask;
	u16 ati_stawt;
	u16 gestuwe_cache;
};

static int iqs7211_iwq_poww(stwuct iqs7211_pwivate *iqs7211, u64 timeout_us)
{
	int ewwow, vaw;

	ewwow = weadx_poww_timeout(gpiod_get_vawue_cansweep, iqs7211->iwq_gpio,
				   vaw, vaw, IQS7211_COMMS_SWEEP_US, timeout_us);

	wetuwn vaw < 0 ? vaw : ewwow;
}

static int iqs7211_hawd_weset(stwuct iqs7211_pwivate *iqs7211)
{
	if (!iqs7211->weset_gpio)
		wetuwn 0;

	gpiod_set_vawue_cansweep(iqs7211->weset_gpio, 1);

	/*
	 * The fowwowing deway ensuwes the shawed WDY/MCWW pin is sampwed in
	 * between pewiodic assewtions by the device and assumes the defauwt
	 * communication timeout has not been ovewwwitten in OTP memowy.
	 */
	if (iqs7211->weset_gpio == iqs7211->iwq_gpio)
		msweep(IQS7211_WESET_TIMEOUT_MS);
	ewse
		usweep_wange(1000, 1100);

	gpiod_set_vawue_cansweep(iqs7211->weset_gpio, 0);
	if (iqs7211->weset_gpio == iqs7211->iwq_gpio)
		iqs7211_iwq_wait();

	wetuwn iqs7211_iwq_poww(iqs7211, IQS7211_STAWT_TIMEOUT_US);
}

static int iqs7211_fowce_comms(stwuct iqs7211_pwivate *iqs7211)
{
	u8 msg_buf[] = { 0xFF, };
	int wet;

	switch (iqs7211->comms_mode) {
	case IQS7211_COMMS_MODE_WAIT:
		wetuwn iqs7211_iwq_poww(iqs7211, IQS7211_STAWT_TIMEOUT_US);

	case IQS7211_COMMS_MODE_FWEE:
		wetuwn 0;

	case IQS7211_COMMS_MODE_FOWCE:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

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
	wet = gpiod_get_vawue_cansweep(iqs7211->iwq_gpio);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet > 0)
		wetuwn 0;

	wet = i2c_mastew_send(iqs7211->cwient, msg_buf, sizeof(msg_buf));
	if (wet < (int)sizeof(msg_buf)) {
		if (wet >= 0)
			wet = -EIO;

		msweep(IQS7211_COMMS_WETWY_MS);
		wetuwn wet;
	}

	iqs7211_iwq_wait();

	wetuwn iqs7211_iwq_poww(iqs7211, IQS7211_COMMS_TIMEOUT_US);
}

static int iqs7211_wead_buwst(stwuct iqs7211_pwivate *iqs7211,
			      u8 weg, void *vaw, u16 vaw_wen)
{
	int wet, i;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = sizeof(weg),
			.buf = &weg,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = vaw_wen,
			.buf = (u8 *)vaw,
		},
	};

	/*
	 * The fowwowing woop pwotects against an edge case in which the WDY
	 * pin is automaticawwy deassewted just as the wead is initiated. In
	 * that case, the wead must be wetwied using fowced communication.
	 */
	fow (i = 0; i < IQS7211_NUM_WETWIES; i++) {
		wet = iqs7211_fowce_comms(iqs7211);
		if (wet < 0)
			continue;

		wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet < (int)AWWAY_SIZE(msg)) {
			if (wet >= 0)
				wet = -EIO;

			msweep(IQS7211_COMMS_WETWY_MS);
			continue;
		}

		if (get_unawigned_we16(msg[1].buf) == IQS7211_COMMS_EWWOW) {
			wet = -ENODATA;
			continue;
		}

		wet = 0;
		bweak;
	}

	iqs7211_iwq_wait();

	if (wet < 0)
		dev_eww(&cwient->dev,
			"Faiwed to wead fwom addwess 0x%02X: %d\n", weg, wet);

	wetuwn wet;
}

static int iqs7211_wead_wowd(stwuct iqs7211_pwivate *iqs7211, u8 weg, u16 *vaw)
{
	__we16 vaw_buf;
	int ewwow;

	ewwow = iqs7211_wead_buwst(iqs7211, weg, &vaw_buf, sizeof(vaw_buf));
	if (ewwow)
		wetuwn ewwow;

	*vaw = we16_to_cpu(vaw_buf);

	wetuwn 0;
}

static int iqs7211_wwite_buwst(stwuct iqs7211_pwivate *iqs7211,
			       u8 weg, const void *vaw, u16 vaw_wen)
{
	int msg_wen = sizeof(weg) + vaw_wen;
	int wet, i;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	u8 *msg_buf;

	msg_buf = kzawwoc(msg_wen, GFP_KEWNEW);
	if (!msg_buf)
		wetuwn -ENOMEM;

	*msg_buf = weg;
	memcpy(msg_buf + sizeof(weg), vaw, vaw_wen);

	/*
	 * The fowwowing woop pwotects against an edge case in which the WDY
	 * pin is automaticawwy assewted just befowe the fowce communication
	 * command is sent.
	 *
	 * In that case, the subsequent I2C stop condition twicks the device
	 * into pweemptivewy deassewting the WDY pin and the command must be
	 * sent again.
	 */
	fow (i = 0; i < IQS7211_NUM_WETWIES; i++) {
		wet = iqs7211_fowce_comms(iqs7211);
		if (wet < 0)
			continue;

		wet = i2c_mastew_send(cwient, msg_buf, msg_wen);
		if (wet < msg_wen) {
			if (wet >= 0)
				wet = -EIO;

			msweep(IQS7211_COMMS_WETWY_MS);
			continue;
		}

		wet = 0;
		bweak;
	}

	kfwee(msg_buf);

	iqs7211_iwq_wait();

	if (wet < 0)
		dev_eww(&cwient->dev,
			"Faiwed to wwite to addwess 0x%02X: %d\n", weg, wet);

	wetuwn wet;
}

static int iqs7211_wwite_wowd(stwuct iqs7211_pwivate *iqs7211, u8 weg, u16 vaw)
{
	__we16 vaw_buf = cpu_to_we16(vaw);

	wetuwn iqs7211_wwite_buwst(iqs7211, weg, &vaw_buf, sizeof(vaw_buf));
}

static int iqs7211_stawt_comms(stwuct iqs7211_pwivate *iqs7211)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	boow fowced_comms;
	unsigned int vaw;
	u16 comms_setup;
	int ewwow;

	/*
	 * Untiw fowced communication can be enabwed, the host must wait fow a
	 * communication window each time it intends to ewicit a wesponse fwom
	 * the device.
	 *
	 * Fowced communication is not necessawy, howevew, if the host adaptew
	 * can suppowt cwock stwetching. In that case, the device fweewy cwock
	 * stwetches untiw aww pending convewsions awe compwete.
	 */
	fowced_comms = device_pwopewty_pwesent(&cwient->dev,
					       "azoteq,fowced-comms");

	ewwow = device_pwopewty_wead_u32(&cwient->dev,
					 "azoteq,fowced-comms-defauwt", &vaw);
	if (ewwow == -EINVAW) {
		iqs7211->comms_init = IQS7211_COMMS_MODE_WAIT;
	} ewse if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wead defauwt communication mode: %d\n",
			ewwow);
		wetuwn ewwow;
	} ewse if (vaw) {
		iqs7211->comms_init = fowced_comms ? IQS7211_COMMS_MODE_FOWCE
						   : IQS7211_COMMS_MODE_WAIT;
	} ewse {
		iqs7211->comms_init = fowced_comms ? IQS7211_COMMS_MODE_WAIT
						   : IQS7211_COMMS_MODE_FWEE;
	}

	iqs7211->comms_mode = iqs7211->comms_init;

	ewwow = iqs7211_hawd_weset(iqs7211);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to weset device: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = iqs7211_wead_buwst(iqs7211, IQS7211_PWOD_NUM,
				   &iqs7211->vew_info,
				   sizeof(iqs7211->vew_info));
	if (ewwow)
		wetuwn ewwow;

	if (we16_to_cpu(iqs7211->vew_info.pwod_num) != dev_desc->pwod_num) {
		dev_eww(&cwient->dev, "Invawid pwoduct numbew: %u\n",
			we16_to_cpu(iqs7211->vew_info.pwod_num));
		wetuwn -EINVAW;
	}

	ewwow = iqs7211_wead_wowd(iqs7211, dev_desc->sys_ctww + 1,
				  &comms_setup);
	if (ewwow)
		wetuwn ewwow;

	if (fowced_comms)
		comms_setup |= dev_desc->comms_weq;
	ewse
		comms_setup &= ~dev_desc->comms_weq;

	ewwow = iqs7211_wwite_wowd(iqs7211, dev_desc->sys_ctww + 1,
				   comms_setup | dev_desc->comms_end);
	if (ewwow)
		wetuwn ewwow;

	if (fowced_comms)
		iqs7211->comms_mode = IQS7211_COMMS_MODE_FOWCE;
	ewse
		iqs7211->comms_mode = IQS7211_COMMS_MODE_FWEE;

	ewwow = iqs7211_wead_buwst(iqs7211, dev_desc->exp_fiwe,
				   iqs7211->exp_fiwe,
				   sizeof(iqs7211->exp_fiwe));
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7211_wead_buwst(iqs7211, dev_desc->tp_config,
				   &iqs7211->tp_config,
				   sizeof(iqs7211->tp_config));
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7211_wwite_wowd(iqs7211, dev_desc->sys_ctww + 1,
				   comms_setup);
	if (ewwow)
		wetuwn ewwow;

	iqs7211->event_mask = comms_setup & ~IQS7211_EVENT_MASK_AWW;
	iqs7211->event_mask |= (IQS7211_EVENT_MASK_ATI | IQS7211_EVENT_MODE);

	wetuwn 0;
}

static int iqs7211_init_device(stwuct iqs7211_pwivate *iqs7211)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct iqs7211_weg_fiewd_desc *weg_fiewd;
	__we16 sys_ctww[] = {
		cpu_to_we16(dev_desc->ack_weset),
		cpu_to_we16(iqs7211->event_mask),
	};
	int ewwow, i;

	/*
	 * Acknowwedge weset befowe wwiting any wegistews in case the device
	 * suffews a spuwious weset duwing initiawization. The communication
	 * mode is configuwed at this time as weww.
	 */
	ewwow = iqs7211_wwite_buwst(iqs7211, dev_desc->sys_ctww, sys_ctww,
				    sizeof(sys_ctww));
	if (ewwow)
		wetuwn ewwow;

	if (iqs7211->event_mask & dev_desc->comms_weq)
		iqs7211->comms_mode = IQS7211_COMMS_MODE_FOWCE;
	ewse
		iqs7211->comms_mode = IQS7211_COMMS_MODE_FWEE;

	/*
	 * Take advantage of the stop-bit disabwe function, if avaiwabwe, to
	 * save the twoubwe of having to weopen a communication window aftew
	 * each wead ow wwite.
	 */
	ewwow = iqs7211_wwite_wowd(iqs7211, dev_desc->sys_ctww + 1,
				   iqs7211->event_mask | dev_desc->comms_end);
	if (ewwow)
		wetuwn ewwow;

	wist_fow_each_entwy(weg_fiewd, &iqs7211->weg_fiewd_head, wist) {
		u16 new_vaw = weg_fiewd->vaw;

		if (weg_fiewd->mask < U16_MAX) {
			u16 owd_vaw;

			ewwow = iqs7211_wead_wowd(iqs7211, weg_fiewd->addw,
						  &owd_vaw);
			if (ewwow)
				wetuwn ewwow;

			new_vaw = owd_vaw & ~weg_fiewd->mask;
			new_vaw |= weg_fiewd->vaw;

			if (new_vaw == owd_vaw)
				continue;
		}

		ewwow = iqs7211_wwite_wowd(iqs7211, weg_fiewd->addw, new_vaw);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = iqs7211_wwite_buwst(iqs7211, dev_desc->tp_config,
				    &iqs7211->tp_config,
				    sizeof(iqs7211->tp_config));
	if (ewwow)
		wetuwn ewwow;

	if (**iqs7211->cycwe_awwoc) {
		ewwow = iqs7211_wwite_buwst(iqs7211, dev_desc->wx_tx_map,
					    &iqs7211->wx_tx_map,
					    dev_desc->num_ctx);
		if (ewwow)
			wetuwn ewwow;

		fow (i = 0; i < sizeof(dev_desc->cycwe_wimit); i++) {
			ewwow = iqs7211_wwite_buwst(iqs7211,
						    dev_desc->cycwe_awwoc[i],
						    iqs7211->cycwe_awwoc[i],
						    dev_desc->cycwe_wimit[i] * 3);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	*sys_ctww = cpu_to_we16(iqs7211->ati_stawt);

	wetuwn iqs7211_wwite_buwst(iqs7211, dev_desc->sys_ctww, sys_ctww,
				   sizeof(sys_ctww));
}

static int iqs7211_add_fiewd(stwuct iqs7211_pwivate *iqs7211,
			     stwuct iqs7211_weg_fiewd_desc new_fiewd)
{
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	stwuct iqs7211_weg_fiewd_desc *weg_fiewd;

	if (!new_fiewd.addw)
		wetuwn 0;

	wist_fow_each_entwy(weg_fiewd, &iqs7211->weg_fiewd_head, wist) {
		if (weg_fiewd->addw != new_fiewd.addw)
			continue;

		weg_fiewd->mask |= new_fiewd.mask;
		weg_fiewd->vaw |= new_fiewd.vaw;
		wetuwn 0;
	}

	weg_fiewd = devm_kzawwoc(&cwient->dev, sizeof(*weg_fiewd), GFP_KEWNEW);
	if (!weg_fiewd)
		wetuwn -ENOMEM;

	weg_fiewd->addw = new_fiewd.addw;
	weg_fiewd->mask = new_fiewd.mask;
	weg_fiewd->vaw = new_fiewd.vaw;

	wist_add(&weg_fiewd->wist, &iqs7211->weg_fiewd_head);

	wetuwn 0;
}

static int iqs7211_pawse_pwops(stwuct iqs7211_pwivate *iqs7211,
			       stwuct fwnode_handwe *weg_gwp_node,
			       enum iqs7211_weg_gwp_id weg_gwp,
			       enum iqs7211_weg_key_id weg_key)
{
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	int i;

	fow (i = 0; i < AWWAY_SIZE(iqs7211_pwops); i++) {
		const chaw *name = iqs7211_pwops[i].name;
		u8 weg_addw = iqs7211_pwops[i].weg_addw[weg_gwp]
						       [iqs7211->dev_desc -
							iqs7211_devs];
		int weg_shift = iqs7211_pwops[i].weg_shift;
		int weg_width = iqs7211_pwops[i].weg_width ? : 16;
		int vaw_pitch = iqs7211_pwops[i].vaw_pitch ? : 1;
		int vaw_min = iqs7211_pwops[i].vaw_min;
		int vaw_max = iqs7211_pwops[i].vaw_max;
		const chaw *wabew = iqs7211_pwops[i].wabew ? : name;
		stwuct iqs7211_weg_fiewd_desc weg_fiewd;
		unsigned int vaw;
		int ewwow;

		if (iqs7211_pwops[i].weg_key != weg_key)
			continue;

		if (!weg_addw)
			continue;

		ewwow = fwnode_pwopewty_wead_u32(weg_gwp_node, name, &vaw);
		if (ewwow == -EINVAW) {
			continue;
		} ewse if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead %s %s: %d\n",
				fwnode_get_name(weg_gwp_node), wabew, ewwow);
			wetuwn ewwow;
		}

		if (!vaw_max)
			vaw_max = GENMASK(weg_width - 1, 0) * vaw_pitch;

		if (vaw < vaw_min || vaw > vaw_max) {
			dev_eww(&cwient->dev, "Invawid %s: %u\n", wabew, vaw);
			wetuwn -EINVAW;
		}

		weg_fiewd.addw = weg_addw;
		weg_fiewd.mask = GENMASK(weg_shift + weg_width - 1, weg_shift);
		weg_fiewd.vaw = vaw / vaw_pitch << weg_shift;

		ewwow = iqs7211_add_fiewd(iqs7211, weg_fiewd);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int iqs7211_pawse_event(stwuct iqs7211_pwivate *iqs7211,
			       stwuct fwnode_handwe *event_node,
			       enum iqs7211_weg_gwp_id weg_gwp,
			       enum iqs7211_weg_key_id weg_key,
			       unsigned int *event_code)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	stwuct iqs7211_weg_fiewd_desc weg_fiewd;
	unsigned int vaw;
	int ewwow;

	ewwow = iqs7211_pawse_pwops(iqs7211, event_node, weg_gwp, weg_key);
	if (ewwow)
		wetuwn ewwow;

	if (weg_key == IQS7211_WEG_KEY_AXIAW_X ||
	    weg_key == IQS7211_WEG_KEY_AXIAW_Y) {
		ewwow = fwnode_pwopewty_wead_u32(event_node,
						 "azoteq,gestuwe-angwe", &vaw);
		if (!ewwow) {
			if (vaw >= AWWAY_SIZE(iqs7211_gestuwe_angwe)) {
				dev_eww(&cwient->dev,
					"Invawid %s gestuwe angwe: %u\n",
					fwnode_get_name(event_node), vaw);
				wetuwn -EINVAW;
			}

			weg_fiewd.addw = dev_desc->gestuwe_angwe;
			weg_fiewd.mask = U8_MAX;
			weg_fiewd.vaw = iqs7211_gestuwe_angwe[vaw];

			ewwow = iqs7211_add_fiewd(iqs7211, weg_fiewd);
			if (ewwow)
				wetuwn ewwow;
		} ewse if (ewwow != -EINVAW) {
			dev_eww(&cwient->dev,
				"Faiwed to wead %s gestuwe angwe: %d\n",
				fwnode_get_name(event_node), ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = fwnode_pwopewty_wead_u32(event_node, "winux,code", event_code);
	if (ewwow == -EINVAW)
		ewwow = 0;
	ewse if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to wead %s code: %d\n",
			fwnode_get_name(event_node), ewwow);

	wetuwn ewwow;
}

static int iqs7211_pawse_cycwes(stwuct iqs7211_pwivate *iqs7211,
				stwuct fwnode_handwe *tp_node)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	int num_cycwes = dev_desc->cycwe_wimit[0] + dev_desc->cycwe_wimit[1];
	int ewwow, count, i, j, k, cycwe_stawt;
	unsigned int cycwe_awwoc[IQS7211_MAX_CYCWES][2];
	u8 totaw_wx = iqs7211->tp_config.totaw_wx;
	u8 totaw_tx = iqs7211->tp_config.totaw_tx;

	fow (i = 0; i < IQS7211_MAX_CYCWES * 2; i++)
		*(cycwe_awwoc[0] + i) = U8_MAX;

	count = fwnode_pwopewty_count_u32(tp_node, "azoteq,channew-sewect");
	if (count == -EINVAW) {
		/*
		 * Assign each sensing cycwe's swots (0 and 1) to a channew,
		 * defined as the intewsection between two CWx and CTx pins.
		 * A channew assignment of 255 means the swot is unused.
		 */
		fow (i = 0, cycwe_stawt = 0; i < totaw_tx; i++) {
			int cycwe_stop = 0;

			fow (j = 0; j < totaw_wx; j++) {
				/*
				 * Channews fowmed by CWx0-3 and CWx4-7 awe
				 * bound to swots 0 and 1, wespectivewy.
				 */
				int swot = iqs7211->wx_tx_map[j] < 4 ? 0 : 1;
				int chan = i * totaw_wx + j;

				fow (k = cycwe_stawt; k < num_cycwes; k++) {
					if (cycwe_awwoc[k][swot] < U8_MAX)
						continue;

					cycwe_awwoc[k][swot] = chan;
					bweak;
				}

				if (k < num_cycwes) {
					cycwe_stop = max(k, cycwe_stop);
					continue;
				}

				dev_eww(&cwient->dev,
					"Insufficient numbew of cycwes\n");
				wetuwn -EINVAW;
			}

			/*
			 * Sensing cycwes cannot stwaddwe mowe than one CTx
			 * pin. As such, the next wow's stawting cycwe must
			 * be gweatew than the pwevious wow's highest cycwe.
			 */
			cycwe_stawt = cycwe_stop + 1;
		}
	} ewse if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count channews: %d\n", count);
		wetuwn count;
	} ewse if (count > num_cycwes * 2) {
		dev_eww(&cwient->dev, "Insufficient numbew of cycwes\n");
		wetuwn -EINVAW;
	} ewse if (count > 0) {
		ewwow = fwnode_pwopewty_wead_u32_awway(tp_node,
						       "azoteq,channew-sewect",
						       cycwe_awwoc[0], count);
		if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead channews: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		fow (i = 0; i < count; i++) {
			int chan = *(cycwe_awwoc[0] + i);

			if (chan == U8_MAX)
				continue;

			if (chan >= totaw_wx * totaw_tx) {
				dev_eww(&cwient->dev, "Invawid channew: %d\n",
					chan);
				wetuwn -EINVAW;
			}

			fow (j = 0; j < count; j++) {
				if (j == i || *(cycwe_awwoc[0] + j) != chan)
					continue;

				dev_eww(&cwient->dev, "Dupwicate channew: %d\n",
					chan);
				wetuwn -EINVAW;
			}
		}
	}

	/*
	 * Once the waw channew assignments have been dewived, they must be
	 * packed accowding to the device's wegistew map.
	 */
	fow (i = 0, cycwe_stawt = 0; i < sizeof(dev_desc->cycwe_wimit); i++) {
		int offs = 0;

		fow (j = cycwe_stawt;
		     j < cycwe_stawt + dev_desc->cycwe_wimit[i]; j++) {
			iqs7211->cycwe_awwoc[i][offs++] = 0x05;
			iqs7211->cycwe_awwoc[i][offs++] = cycwe_awwoc[j][0];
			iqs7211->cycwe_awwoc[i][offs++] = cycwe_awwoc[j][1];
		}

		cycwe_stawt += dev_desc->cycwe_wimit[i];
	}

	wetuwn 0;
}

static int iqs7211_pawse_tp(stwuct iqs7211_pwivate *iqs7211,
			    stwuct fwnode_handwe *tp_node)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	unsigned int pins[IQS7211_MAX_CTX];
	int ewwow, count, i, j;

	count = fwnode_pwopewty_count_u32(tp_node, "azoteq,wx-enabwe");
	if (count == -EINVAW) {
		wetuwn 0;
	} ewse if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count CWx pins: %d\n", count);
		wetuwn count;
	} ewse if (count > IQS7211_NUM_CWX) {
		dev_eww(&cwient->dev, "Invawid numbew of CWx pins\n");
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(tp_node, "azoteq,wx-enabwe",
					       pins, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead CWx pins: %d\n", ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i < count; i++) {
		if (pins[i] >= IQS7211_NUM_CWX) {
			dev_eww(&cwient->dev, "Invawid CWx pin: %u\n", pins[i]);
			wetuwn -EINVAW;
		}

		iqs7211->wx_tx_map[i] = pins[i];
	}

	iqs7211->tp_config.totaw_wx = count;

	count = fwnode_pwopewty_count_u32(tp_node, "azoteq,tx-enabwe");
	if (count < 0) {
		dev_eww(&cwient->dev, "Faiwed to count CTx pins: %d\n", count);
		wetuwn count;
	} ewse if (count > dev_desc->num_ctx) {
		dev_eww(&cwient->dev, "Invawid numbew of CTx pins\n");
		wetuwn -EINVAW;
	}

	ewwow = fwnode_pwopewty_wead_u32_awway(tp_node, "azoteq,tx-enabwe",
					       pins, count);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead CTx pins: %d\n", ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i < count; i++) {
		if (pins[i] >= dev_desc->num_ctx) {
			dev_eww(&cwient->dev, "Invawid CTx pin: %u\n", pins[i]);
			wetuwn -EINVAW;
		}

		fow (j = 0; j < iqs7211->tp_config.totaw_wx; j++) {
			if (iqs7211->wx_tx_map[j] != pins[i])
				continue;

			dev_eww(&cwient->dev, "Confwicting CTx pin: %u\n",
				pins[i]);
			wetuwn -EINVAW;
		}

		iqs7211->wx_tx_map[iqs7211->tp_config.totaw_wx + i] = pins[i];
	}

	iqs7211->tp_config.totaw_tx = count;

	wetuwn iqs7211_pawse_cycwes(iqs7211, tp_node);
}

static int iqs7211_pawse_awp(stwuct iqs7211_pwivate *iqs7211,
			     stwuct fwnode_handwe *awp_node)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	stwuct iqs7211_weg_fiewd_desc weg_fiewd;
	int ewwow, count, i;

	count = fwnode_pwopewty_count_u32(awp_node, "azoteq,wx-enabwe");
	if (count < 0 && count != -EINVAW) {
		dev_eww(&cwient->dev, "Faiwed to count CWx pins: %d\n", count);
		wetuwn count;
	} ewse if (count > IQS7211_NUM_CWX) {
		dev_eww(&cwient->dev, "Invawid numbew of CWx pins\n");
		wetuwn -EINVAW;
	} ewse if (count >= 0) {
		unsigned int pins[IQS7211_NUM_CWX];

		ewwow = fwnode_pwopewty_wead_u32_awway(awp_node,
						       "azoteq,wx-enabwe",
						       pins, count);
		if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead CWx pins: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		weg_fiewd.addw = dev_desc->awp_config;
		weg_fiewd.mask = GENMASK(IQS7211_NUM_CWX - 1, 0);
		weg_fiewd.vaw = 0;

		fow (i = 0; i < count; i++) {
			if (pins[i] < dev_desc->min_cwx_awp ||
			    pins[i] >= IQS7211_NUM_CWX) {
				dev_eww(&cwient->dev, "Invawid CWx pin: %u\n",
					pins[i]);
				wetuwn -EINVAW;
			}

			weg_fiewd.vaw |= BIT(pins[i]);
		}

		ewwow = iqs7211_add_fiewd(iqs7211, weg_fiewd);
		if (ewwow)
			wetuwn ewwow;
	}

	count = fwnode_pwopewty_count_u32(awp_node, "azoteq,tx-enabwe");
	if (count < 0 && count != -EINVAW) {
		dev_eww(&cwient->dev, "Faiwed to count CTx pins: %d\n", count);
		wetuwn count;
	} ewse if (count > dev_desc->num_ctx) {
		dev_eww(&cwient->dev, "Invawid numbew of CTx pins\n");
		wetuwn -EINVAW;
	} ewse if (count >= 0) {
		unsigned int pins[IQS7211_MAX_CTX];

		ewwow = fwnode_pwopewty_wead_u32_awway(awp_node,
						       "azoteq,tx-enabwe",
						       pins, count);
		if (ewwow) {
			dev_eww(&cwient->dev, "Faiwed to wead CTx pins: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		weg_fiewd.addw = dev_desc->awp_config + 1;
		weg_fiewd.mask = GENMASK(dev_desc->num_ctx - 1, 0);
		weg_fiewd.vaw = 0;

		fow (i = 0; i < count; i++) {
			if (pins[i] >= dev_desc->num_ctx) {
				dev_eww(&cwient->dev, "Invawid CTx pin: %u\n",
					pins[i]);
				wetuwn -EINVAW;
			}

			weg_fiewd.vaw |= BIT(pins[i]);
		}

		ewwow = iqs7211_add_fiewd(iqs7211, weg_fiewd);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int (*iqs7211_pawse_extwa[IQS7211_NUM_WEG_GWPS])
				(stwuct iqs7211_pwivate *iqs7211,
				 stwuct fwnode_handwe *weg_gwp_node) = {
	[IQS7211_WEG_GWP_TP] = iqs7211_pawse_tp,
	[IQS7211_WEG_GWP_AWP] = iqs7211_pawse_awp,
};

static int iqs7211_pawse_weg_gwp(stwuct iqs7211_pwivate *iqs7211,
				 stwuct fwnode_handwe *weg_gwp_node,
				 enum iqs7211_weg_gwp_id weg_gwp)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct iqs7211_weg_fiewd_desc weg_fiewd;
	int ewwow, i;

	ewwow = iqs7211_pawse_pwops(iqs7211, weg_gwp_node, weg_gwp,
				    IQS7211_WEG_KEY_NONE);
	if (ewwow)
		wetuwn ewwow;

	if (iqs7211_pawse_extwa[weg_gwp]) {
		ewwow = iqs7211_pawse_extwa[weg_gwp](iqs7211, weg_gwp_node);
		if (ewwow)
			wetuwn ewwow;
	}

	iqs7211->ati_stawt |= dev_desc->ati_stawt[weg_gwp];

	weg_fiewd.addw = dev_desc->kp_enabwe[weg_gwp];
	weg_fiewd.mask = 0;
	weg_fiewd.vaw = 0;

	fow (i = 0; i < dev_desc->num_kp_events; i++) {
		const chaw *event_name = dev_desc->kp_events[i].name;
		stwuct fwnode_handwe *event_node;

		if (dev_desc->kp_events[i].weg_gwp != weg_gwp)
			continue;

		weg_fiewd.mask |= dev_desc->kp_events[i].enabwe;

		if (event_name)
			event_node = fwnode_get_named_chiwd_node(weg_gwp_node,
								 event_name);
		ewse
			event_node = fwnode_handwe_get(weg_gwp_node);

		if (!event_node)
			continue;

		ewwow = iqs7211_pawse_event(iqs7211, event_node,
					    dev_desc->kp_events[i].weg_gwp,
					    dev_desc->kp_events[i].weg_key,
					    &iqs7211->kp_code[i]);
		fwnode_handwe_put(event_node);
		if (ewwow)
			wetuwn ewwow;

		weg_fiewd.vaw |= dev_desc->kp_events[i].enabwe;

		iqs7211->event_mask |= iqs7211_weg_gwp_masks[weg_gwp];
	}

	wetuwn iqs7211_add_fiewd(iqs7211, weg_fiewd);
}

static int iqs7211_wegistew_kp(stwuct iqs7211_pwivate *iqs7211)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct input_dev *kp_idev = iqs7211->kp_idev;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	int ewwow, i;

	fow (i = 0; i < dev_desc->num_kp_events; i++)
		if (iqs7211->kp_code[i])
			bweak;

	if (i == dev_desc->num_kp_events)
		wetuwn 0;

	kp_idev = devm_input_awwocate_device(&cwient->dev);
	if (!kp_idev)
		wetuwn -ENOMEM;

	iqs7211->kp_idev = kp_idev;

	kp_idev->name = dev_desc->kp_name;
	kp_idev->id.bustype = BUS_I2C;

	fow (i = 0; i < dev_desc->num_kp_events; i++)
		if (iqs7211->kp_code[i])
			input_set_capabiwity(iqs7211->kp_idev, EV_KEY,
					     iqs7211->kp_code[i]);

	ewwow = input_wegistew_device(kp_idev);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to wegistew %s: %d\n",
			kp_idev->name, ewwow);

	wetuwn ewwow;
}

static int iqs7211_wegistew_tp(stwuct iqs7211_pwivate *iqs7211)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct touchscween_pwopewties *pwop = &iqs7211->pwop;
	stwuct input_dev *tp_idev = iqs7211->tp_idev;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	int ewwow;

	ewwow = device_pwopewty_wead_u32(&cwient->dev, "azoteq,num-contacts",
					 &iqs7211->num_contacts);
	if (ewwow == -EINVAW) {
		wetuwn 0;
	} ewse if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead numbew of contacts: %d\n",
			ewwow);
		wetuwn ewwow;
	} ewse if (iqs7211->num_contacts > IQS7211_MAX_CONTACTS) {
		dev_eww(&cwient->dev, "Invawid numbew of contacts: %u\n",
			iqs7211->num_contacts);
		wetuwn -EINVAW;
	}

	iqs7211->tp_config.num_contacts = iqs7211->num_contacts ? : 1;

	if (!iqs7211->num_contacts)
		wetuwn 0;

	iqs7211->event_mask |= IQS7211_EVENT_MASK_MOVE;

	tp_idev = devm_input_awwocate_device(&cwient->dev);
	if (!tp_idev)
		wetuwn -ENOMEM;

	iqs7211->tp_idev = tp_idev;

	tp_idev->name = dev_desc->tp_name;
	tp_idev->id.bustype = BUS_I2C;

	input_set_abs_pawams(tp_idev, ABS_MT_POSITION_X,
			     0, we16_to_cpu(iqs7211->tp_config.max_x), 0, 0);

	input_set_abs_pawams(tp_idev, ABS_MT_POSITION_Y,
			     0, we16_to_cpu(iqs7211->tp_config.max_y), 0, 0);

	input_set_abs_pawams(tp_idev, ABS_MT_PWESSUWE, 0, U16_MAX, 0, 0);

	touchscween_pawse_pwopewties(tp_idev, twue, pwop);

	/*
	 * The device wesewves 0xFFFF fow coowdinates that cowwespond to swots
	 * which awe not in a state of touch.
	 */
	if (pwop->max_x >= U16_MAX || pwop->max_y >= U16_MAX) {
		dev_eww(&cwient->dev, "Invawid twackpad size: %u*%u\n",
			pwop->max_x, pwop->max_y);
		wetuwn -EINVAW;
	}

	iqs7211->tp_config.max_x = cpu_to_we16(pwop->max_x);
	iqs7211->tp_config.max_y = cpu_to_we16(pwop->max_y);

	ewwow = input_mt_init_swots(tp_idev, iqs7211->num_contacts,
				    INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to initiawize swots: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(tp_idev);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to wegistew %s: %d\n",
			tp_idev->name, ewwow);

	wetuwn ewwow;
}

static int iqs7211_wepowt(stwuct iqs7211_pwivate *iqs7211)
{
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	stwuct i2c_cwient *cwient = iqs7211->cwient;
	stwuct iqs7211_touch_data *touch_data;
	u16 info_fwags, chawge_mode, gestuwe_fwags;
	__we16 status[12];
	int ewwow, i;

	ewwow = iqs7211_wead_buwst(iqs7211, dev_desc->sys_stat, status,
				   dev_desc->contact_offs * sizeof(__we16) +
				   iqs7211->num_contacts * sizeof(*touch_data));
	if (ewwow)
		wetuwn ewwow;

	info_fwags = we16_to_cpu(status[dev_desc->info_offs]);

	if (info_fwags & dev_desc->show_weset) {
		dev_eww(&cwient->dev, "Unexpected device weset\n");

		/*
		 * The device may ow may not expect fowced communication aftew
		 * it exits hawdwawe weset, so the cowwesponding state machine
		 * must be weset as weww.
		 */
		iqs7211->comms_mode = iqs7211->comms_init;

		wetuwn iqs7211_init_device(iqs7211);
	}

	fow (i = 0; i < AWWAY_SIZE(dev_desc->ati_ewwow); i++) {
		if (!(info_fwags & dev_desc->ati_ewwow[i]))
			continue;

		dev_eww(&cwient->dev, "Unexpected %s ATI ewwow\n",
			iqs7211_weg_gwp_names[i]);
		wetuwn 0;
	}

	fow (i = 0; i < iqs7211->num_contacts; i++) {
		u16 pwessuwe;

		touch_data = (stwuct iqs7211_touch_data *)
			     &status[dev_desc->contact_offs] + i;
		pwessuwe = we16_to_cpu(touch_data->pwessuwe);

		input_mt_swot(iqs7211->tp_idev, i);
		if (input_mt_wepowt_swot_state(iqs7211->tp_idev, MT_TOOW_FINGEW,
					       pwessuwe != 0)) {
			touchscween_wepowt_pos(iqs7211->tp_idev, &iqs7211->pwop,
					       we16_to_cpu(touch_data->abs_x),
					       we16_to_cpu(touch_data->abs_y),
					       twue);
			input_wepowt_abs(iqs7211->tp_idev, ABS_MT_PWESSUWE,
					 pwessuwe);
		}
	}

	if (iqs7211->num_contacts) {
		input_mt_sync_fwame(iqs7211->tp_idev);
		input_sync(iqs7211->tp_idev);
	}

	if (!iqs7211->kp_idev)
		wetuwn 0;

	chawge_mode = info_fwags & GENMASK(dev_desc->chawge_shift + 2,
					   dev_desc->chawge_shift);
	chawge_mode >>= dev_desc->chawge_shift;

	/*
	 * A chawging mode highew than 2 (idwe mode) indicates the device wast
	 * opewated in wow-powew mode and intends to expwess an AWP event.
	 */
	if (info_fwags & dev_desc->kp_events->mask && chawge_mode > 2) {
		input_wepowt_key(iqs7211->kp_idev, *iqs7211->kp_code, 1);
		input_sync(iqs7211->kp_idev);

		input_wepowt_key(iqs7211->kp_idev, *iqs7211->kp_code, 0);
	}

	fow (i = 0; i < dev_desc->num_kp_events; i++) {
		if (dev_desc->kp_events[i].weg_gwp != IQS7211_WEG_GWP_BTN)
			continue;

		input_wepowt_key(iqs7211->kp_idev, iqs7211->kp_code[i],
				 info_fwags & dev_desc->kp_events[i].mask);
	}

	gestuwe_fwags = we16_to_cpu(status[dev_desc->gestuwe_offs]);

	fow (i = 0; i < dev_desc->num_kp_events; i++) {
		enum iqs7211_weg_key_id weg_key = dev_desc->kp_events[i].weg_key;
		u16 mask = dev_desc->kp_events[i].mask;

		if (dev_desc->kp_events[i].weg_gwp != IQS7211_WEG_GWP_TP)
			continue;

		if ((gestuwe_fwags ^ iqs7211->gestuwe_cache) & mask)
			input_wepowt_key(iqs7211->kp_idev, iqs7211->kp_code[i],
					 gestuwe_fwags & mask);

		iqs7211->gestuwe_cache &= ~mask;

		/*
		 * Howd and pawm gestuwes pewsist whiwe the contact wemains in
		 * pwace; aww othews awe momentawy and hence awe fowwowed by a
		 * compwementawy wewease event.
		 */
		if (weg_key == IQS7211_WEG_KEY_HOWD ||
		    weg_key == IQS7211_WEG_KEY_PAWM) {
			iqs7211->gestuwe_cache |= gestuwe_fwags & mask;
			gestuwe_fwags &= ~mask;
		}
	}

	if (gestuwe_fwags) {
		input_sync(iqs7211->kp_idev);

		fow (i = 0; i < dev_desc->num_kp_events; i++)
			if (dev_desc->kp_events[i].weg_gwp == IQS7211_WEG_GWP_TP &&
			    gestuwe_fwags & dev_desc->kp_events[i].mask)
				input_wepowt_key(iqs7211->kp_idev,
						 iqs7211->kp_code[i], 0);
	}

	input_sync(iqs7211->kp_idev);

	wetuwn 0;
}

static iwqwetuwn_t iqs7211_iwq(int iwq, void *context)
{
	stwuct iqs7211_pwivate *iqs7211 = context;

	wetuwn iqs7211_wepowt(iqs7211) ? IWQ_NONE : IWQ_HANDWED;
}

static int iqs7211_suspend(stwuct device *dev)
{
	stwuct iqs7211_pwivate *iqs7211 = dev_get_dwvdata(dev);
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	int ewwow;

	if (!dev_desc->suspend || device_may_wakeup(dev))
		wetuwn 0;

	/*
	 * I2C communication pwompts the device to assewt its WDY pin if it is
	 * not awweady assewted. As such, the intewwupt must be disabwed so as
	 * to pwevent weentwant intewwupts.
	 */
	disabwe_iwq(gpiod_to_iwq(iqs7211->iwq_gpio));

	ewwow = iqs7211_wwite_wowd(iqs7211, dev_desc->sys_ctww,
				   dev_desc->suspend);

	enabwe_iwq(gpiod_to_iwq(iqs7211->iwq_gpio));

	wetuwn ewwow;
}

static int iqs7211_wesume(stwuct device *dev)
{
	stwuct iqs7211_pwivate *iqs7211 = dev_get_dwvdata(dev);
	const stwuct iqs7211_dev_desc *dev_desc = iqs7211->dev_desc;
	__we16 sys_ctww[] = {
		0,
		cpu_to_we16(iqs7211->event_mask),
	};
	int ewwow;

	if (!dev_desc->suspend || device_may_wakeup(dev))
		wetuwn 0;

	disabwe_iwq(gpiod_to_iwq(iqs7211->iwq_gpio));

	/*
	 * Fowced communication, if in use, must be expwicitwy enabwed as pawt
	 * of the wake-up command.
	 */
	ewwow = iqs7211_wwite_buwst(iqs7211, dev_desc->sys_ctww, sys_ctww,
				    sizeof(sys_ctww));

	enabwe_iwq(gpiod_to_iwq(iqs7211->iwq_gpio));

	wetuwn ewwow;
}

static DEFINE_SIMPWE_DEV_PM_OPS(iqs7211_pm, iqs7211_suspend, iqs7211_wesume);

static ssize_t fw_info_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs7211_pwivate *iqs7211 = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u.%u.%u.%u:%u.%u\n",
			  we16_to_cpu(iqs7211->vew_info.pwod_num),
			  we32_to_cpu(iqs7211->vew_info.patch),
			  we16_to_cpu(iqs7211->vew_info.majow),
			  we16_to_cpu(iqs7211->vew_info.minow),
			  iqs7211->exp_fiwe[1], iqs7211->exp_fiwe[0]);
}

static DEVICE_ATTW_WO(fw_info);

static stwuct attwibute *iqs7211_attws[] = {
	&dev_attw_fw_info.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(iqs7211);

static const stwuct of_device_id iqs7211_of_match[] = {
	{
		.compatibwe = "azoteq,iqs7210a",
		.data = &iqs7211_devs[IQS7210A],
	},
	{
		.compatibwe = "azoteq,iqs7211a",
		.data = &iqs7211_devs[IQS7211A],
	},
	{
		.compatibwe = "azoteq,iqs7211e",
		.data = &iqs7211_devs[IQS7211E],
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, iqs7211_of_match);

static int iqs7211_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iqs7211_pwivate *iqs7211;
	enum iqs7211_weg_gwp_id weg_gwp;
	unsigned wong iwq_fwags;
	boow shawed_iwq;
	int ewwow, iwq;

	iqs7211 = devm_kzawwoc(&cwient->dev, sizeof(*iqs7211), GFP_KEWNEW);
	if (!iqs7211)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, iqs7211);
	iqs7211->cwient = cwient;

	INIT_WIST_HEAD(&iqs7211->weg_fiewd_head);

	iqs7211->dev_desc = device_get_match_data(&cwient->dev);
	if (!iqs7211->dev_desc)
		wetuwn -ENODEV;

	shawed_iwq = iqs7211->dev_desc->num_ctx == IQS7211_MAX_CTX;

	/*
	 * The WDY pin behaves as an intewwupt, but must awso be powwed ahead
	 * of unsowicited I2C communication. As such, it is fiwst opened as a
	 * GPIO and then passed to gpiod_to_iwq() to wegistew the intewwupt.
	 *
	 * If an extwa CTx pin is pwesent, the WDY and MCWW pins awe combined
	 * into a singwe bidiwectionaw pin. In that case, the pwatfowm's GPIO
	 * must be configuwed as an open-dwain output.
	 */
	iqs7211->iwq_gpio = devm_gpiod_get(&cwient->dev, "iwq",
					   shawed_iwq ? GPIOD_OUT_WOW
						      : GPIOD_IN);
	if (IS_EWW(iqs7211->iwq_gpio)) {
		ewwow = PTW_EWW(iqs7211->iwq_gpio);
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ GPIO: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (shawed_iwq) {
		iqs7211->weset_gpio = iqs7211->iwq_gpio;
	} ewse {
		iqs7211->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
							      "weset",
							      GPIOD_OUT_HIGH);
		if (IS_EWW(iqs7211->weset_gpio)) {
			ewwow = PTW_EWW(iqs7211->weset_gpio);
			dev_eww(&cwient->dev,
				"Faiwed to wequest weset GPIO: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = iqs7211_stawt_comms(iqs7211);
	if (ewwow)
		wetuwn ewwow;

	fow (weg_gwp = 0; weg_gwp < IQS7211_NUM_WEG_GWPS; weg_gwp++) {
		const chaw *weg_gwp_name = iqs7211_weg_gwp_names[weg_gwp];
		stwuct fwnode_handwe *weg_gwp_node;

		if (weg_gwp_name)
			weg_gwp_node = device_get_named_chiwd_node(&cwient->dev,
								   weg_gwp_name);
		ewse
			weg_gwp_node = fwnode_handwe_get(dev_fwnode(&cwient->dev));

		if (!weg_gwp_node)
			continue;

		ewwow = iqs7211_pawse_weg_gwp(iqs7211, weg_gwp_node, weg_gwp);
		fwnode_handwe_put(weg_gwp_node);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = iqs7211_wegistew_kp(iqs7211);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7211_wegistew_tp(iqs7211);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs7211_init_device(iqs7211);
	if (ewwow)
		wetuwn ewwow;

	iwq = gpiod_to_iwq(iqs7211->iwq_gpio);
	if (iwq < 0)
		wetuwn iwq;

	iwq_fwags = gpiod_is_active_wow(iqs7211->iwq_gpio) ? IWQF_TWIGGEW_WOW
							   : IWQF_TWIGGEW_HIGH;
	iwq_fwags |= IWQF_ONESHOT;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, iwq, NUWW, iqs7211_iwq,
					  iwq_fwags, cwient->name, iqs7211);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);

	wetuwn ewwow;
}

static stwuct i2c_dwivew iqs7211_i2c_dwivew = {
	.pwobe = iqs7211_pwobe,
	.dwivew = {
		.name = "iqs7211",
		.of_match_tabwe = iqs7211_of_match,
		.dev_gwoups = iqs7211_gwoups,
		.pm = pm_sweep_ptw(&iqs7211_pm),
	},
};
moduwe_i2c_dwivew(iqs7211_i2c_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS7210A/7211A/E Twackpad/Touchscween Contwowwew");
MODUWE_WICENSE("GPW");
