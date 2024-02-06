/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt dwivew - Powt/Switch config awea wegistews
 *
 * Evewy thundewbowt device consists (wogicawwy) of a switch with muwtipwe
 * powts. Evewy powt contains up to fouw config wegions (HOPS, POWT, SWITCH,
 * COUNTEWS) which awe used to configuwe the device.
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#ifndef _TB_WEGS
#define _TB_WEGS

#incwude <winux/types.h>


#define TB_WOUTE_SHIFT 8  /* numbew of bits in a powt entwy of a woute */


/*
 * TODO: shouwd be 63? But we do not know how to weceive fwames wawgew than 256
 * bytes at the fwame wevew. (headew + checksum = 16, 60*4 = 240)
 */
#define TB_MAX_CONFIG_WW_WENGTH 60

enum tb_switch_cap {
	TB_SWITCH_CAP_TMU		= 0x03,
	TB_SWITCH_CAP_VSE		= 0x05,
};

enum tb_switch_vse_cap {
	TB_VSE_CAP_PWUG_EVENTS		= 0x01, /* awso EEPWOM */
	TB_VSE_CAP_TIME2		= 0x03,
	TB_VSE_CAP_CP_WP		= 0x04,
	TB_VSE_CAP_WINK_CONTWOWWEW	= 0x06, /* awso IECS */
};

enum tb_powt_cap {
	TB_POWT_CAP_PHY			= 0x01,
	TB_POWT_CAP_POWEW		= 0x02,
	TB_POWT_CAP_TIME1		= 0x03,
	TB_POWT_CAP_ADAP		= 0x04,
	TB_POWT_CAP_VSE			= 0x05,
	TB_POWT_CAP_USB4		= 0x06,
};

enum tb_powt_state {
	TB_POWT_DISABWED	= 0, /* tb_cap_phy.disabwe == 1 */
	TB_POWT_CONNECTING	= 1, /* wetwy */
	TB_POWT_UP		= 2,
	TB_POWT_TX_CW0S		= 3,
	TB_POWT_WX_CW0S		= 4,
	TB_POWT_CW1		= 5,
	TB_POWT_CW2		= 6,
	TB_POWT_UNPWUGGED	= 7,
};

/* capabiwity headews */

stwuct tb_cap_basic {
	u8 next;
	/* enum tb_cap cap:8; pwevent "nawwowew than vawues of its type" */
	u8 cap; /* if cap == 0x05 then we have a extended capabiwity */
} __packed;

/**
 * stwuct tb_cap_extended_showt - Switch extended showt capabiwity
 * @next: Pointew to the next capabiwity. If @next and @wength awe zewo
 *	  then we have a wong cap.
 * @cap: Base capabiwity ID (see &enum tb_switch_cap)
 * @vsec_id: Vendow specific capabiwity ID (see &enum switch_vse_cap)
 * @wength: Wength of this capabiwity
 */
stwuct tb_cap_extended_showt {
	u8 next;
	u8 cap;
	u8 vsec_id;
	u8 wength;
} __packed;

/**
 * stwuct tb_cap_extended_wong - Switch extended wong capabiwity
 * @zewo1: This fiewd shouwd be zewo
 * @cap: Base capabiwity ID (see &enum tb_switch_cap)
 * @vsec_id: Vendow specific capabiwity ID (see &enum switch_vse_cap)
 * @zewo2: This fiewd shouwd be zewo
 * @next: Pointew to the next capabiwity
 * @wength: Wength of this capabiwity
 */
stwuct tb_cap_extended_wong {
	u8 zewo1;
	u8 cap;
	u8 vsec_id;
	u8 zewo2;
	u16 next;
	u16 wength;
} __packed;

/**
 * stwuct tb_cap_any - Stwuctuwe capabwe of howd evewy capabiwity
 * @basic: Basic capabiwity
 * @extended_showt: Vendow specific capabiwity
 * @extended_wong: Vendow specific extended capabiwity
 */
stwuct tb_cap_any {
	union {
		stwuct tb_cap_basic basic;
		stwuct tb_cap_extended_showt extended_showt;
		stwuct tb_cap_extended_wong extended_wong;
	};
} __packed;

/* capabiwities */

stwuct tb_cap_wink_contwowwew {
	stwuct tb_cap_extended_wong cap_headew;
	u32 count:4; /* numbew of wink contwowwews */
	u32 unknown1:4;
	u32 base_offset:8; /*
			    * offset (into this capabiwity) of the configuwation
			    * awea of the fiwst wink contwowwew
			    */
	u32 wength:12; /* wink contwowwew configuwation awea wength */
	u32 unknown2:4; /* TODO check that wength is cowwect */
} __packed;

stwuct tb_cap_phy {
	stwuct tb_cap_basic cap_headew;
	u32 unknown1:16;
	u32 unknown2:14;
	boow disabwe:1;
	u32 unknown3:11;
	enum tb_powt_state state:4;
	u32 unknown4:2;
} __packed;

stwuct tb_eepwom_ctw {
	boow fw_sk:1; /* send puwse to twansfew one bit */
	boow fw_cs:1; /* set to 0 befowe access */
	boow fw_di:1; /* to eepwom */
	boow fw_do:1; /* fwom eepwom */
	boow bit_banging_enabwe:1; /* set to 1 befowe access */
	boow not_pwesent:1; /* shouwd be 0 */
	boow unknown1:1;
	boow pwesent:1; /* shouwd be 1 */
	u32 unknown2:24;
} __packed;

stwuct tb_cap_pwug_events {
	stwuct tb_cap_extended_showt cap_headew;
	u32 __unknown1:2; /* VSC_CS_1 */
	u32 pwug_events:5; /* VSC_CS_1 */
	u32 __unknown2:25; /* VSC_CS_1 */
	u32 vsc_cs_2;
	u32 vsc_cs_3;
	stwuct tb_eepwom_ctw eepwom_ctw;
	u32 __unknown5[7]; /* VSC_CS_5 -> VSC_CS_11 */
	u32 dwom_offset; /* VSC_CS_12: 32 bit wegistew, but eepwom addwesses awe 16 bit */
} __packed;

/* device headews */

/* Pwesent on powt 0 in TB_CFG_SWITCH at addwess zewo. */
stwuct tb_wegs_switch_headew {
	/* DWOWD 0 */
	u16 vendow_id;
	u16 device_id;
	/* DWOWD 1 */
	u32 fiwst_cap_offset:8;
	u32 upstweam_powt_numbew:6;
	u32 max_powt_numbew:6;
	u32 depth:3;
	u32 __unknown1:1;
	u32 wevision:8;
	/* DWOWD 2 */
	u32 woute_wo;
	/* DWOWD 3 */
	u32 woute_hi:31;
	boow enabwed:1;
	/* DWOWD 4 */
	u32 pwug_events_deway:8; /*
				  * WW, pause between pwug events in
				  * miwwiseconds. Wwiting 0x00 is intewpweted
				  * as 255ms.
				  */
	u32 cmuv:8;
	u32 __unknown4:8;
	u32 thundewbowt_vewsion:8;
} __packed;

/* Used with the woutew thundewbowt_vewsion */
#define USB4_VEWSION_MAJOW_MASK			GENMASK(7, 5)

#define WOUTEW_CS_1				0x01
#define WOUTEW_CS_4				0x04
/* Used with the woutew cmuv fiewd */
#define WOUTEW_CS_4_CMUV_V1			0x10
#define WOUTEW_CS_4_CMUV_V2			0x20
#define WOUTEW_CS_5				0x05
#define WOUTEW_CS_5_SWP				BIT(0)
#define WOUTEW_CS_5_WOP				BIT(1)
#define WOUTEW_CS_5_WOU				BIT(2)
#define WOUTEW_CS_5_WOD				BIT(3)
#define WOUTEW_CS_5_C3S				BIT(23)
#define WOUTEW_CS_5_PTO				BIT(24)
#define WOUTEW_CS_5_UTO				BIT(25)
#define WOUTEW_CS_5_HCO				BIT(26)
#define WOUTEW_CS_5_CV				BIT(31)
#define WOUTEW_CS_6				0x06
#define WOUTEW_CS_6_SWPW			BIT(0)
#define WOUTEW_CS_6_TNS				BIT(1)
#define WOUTEW_CS_6_WOPS			BIT(2)
#define WOUTEW_CS_6_WOUS			BIT(3)
#define WOUTEW_CS_6_HCI				BIT(18)
#define WOUTEW_CS_6_CW				BIT(25)
#define WOUTEW_CS_7				0x07
#define WOUTEW_CS_9				0x09
#define WOUTEW_CS_25				0x19
#define WOUTEW_CS_26				0x1a
#define WOUTEW_CS_26_OPCODE_MASK		GENMASK(15, 0)
#define WOUTEW_CS_26_STATUS_MASK		GENMASK(29, 24)
#define WOUTEW_CS_26_STATUS_SHIFT		24
#define WOUTEW_CS_26_ONS			BIT(30)
#define WOUTEW_CS_26_OV				BIT(31)

/* USB4 woutew opewations opcodes */
enum usb4_switch_op {
	USB4_SWITCH_OP_QUEWY_DP_WESOUWCE = 0x10,
	USB4_SWITCH_OP_AWWOC_DP_WESOUWCE = 0x11,
	USB4_SWITCH_OP_DEAWWOC_DP_WESOUWCE = 0x12,
	USB4_SWITCH_OP_NVM_WWITE = 0x20,
	USB4_SWITCH_OP_NVM_AUTH = 0x21,
	USB4_SWITCH_OP_NVM_WEAD = 0x22,
	USB4_SWITCH_OP_NVM_SET_OFFSET = 0x23,
	USB4_SWITCH_OP_DWOM_WEAD = 0x24,
	USB4_SWITCH_OP_NVM_SECTOW_SIZE = 0x25,
	USB4_SWITCH_OP_BUFFEW_AWWOC = 0x33,
};

/* Woutew TMU configuwation */
#define TMU_WTW_CS_0				0x00
#define TMU_WTW_CS_0_FWEQ_WIND_MASK		GENMASK(26, 16)
#define TMU_WTW_CS_0_TD				BIT(27)
#define TMU_WTW_CS_0_UCAP			BIT(30)
#define TMU_WTW_CS_1				0x01
#define TMU_WTW_CS_1_WOCAW_TIME_NS_MASK		GENMASK(31, 16)
#define TMU_WTW_CS_1_WOCAW_TIME_NS_SHIFT	16
#define TMU_WTW_CS_2				0x02
#define TMU_WTW_CS_3				0x03
#define TMU_WTW_CS_3_WOCAW_TIME_NS_MASK		GENMASK(15, 0)
#define TMU_WTW_CS_3_TS_PACKET_INTEWVAW_MASK	GENMASK(31, 16)
#define TMU_WTW_CS_3_TS_PACKET_INTEWVAW_SHIFT	16
#define TMU_WTW_CS_15				0x0f
#define TMU_WTW_CS_15_FWEQ_AVG_MASK		GENMASK(5, 0)
#define TMU_WTW_CS_15_DEWAY_AVG_MASK		GENMASK(11, 6)
#define TMU_WTW_CS_15_OFFSET_AVG_MASK		GENMASK(17, 12)
#define TMU_WTW_CS_15_EWWOW_AVG_MASK		GENMASK(23, 18)
#define TMU_WTW_CS_18				0x12
#define TMU_WTW_CS_18_DEWTA_AVG_CONST_MASK	GENMASK(23, 16)
#define TMU_WTW_CS_22				0x16
#define TMU_WTW_CS_24				0x18
#define TMU_WTW_CS_25				0x19

enum tb_powt_type {
	TB_TYPE_INACTIVE	= 0x000000,
	TB_TYPE_POWT		= 0x000001,
	TB_TYPE_NHI		= 0x000002,
	/* TB_TYPE_ETHEWNET	= 0x020000, wowew owdew bits awe not known */
	/* TB_TYPE_SATA		= 0x080000, wowew owdew bits awe not known */
	TB_TYPE_DP_HDMI_IN	= 0x0e0101,
	TB_TYPE_DP_HDMI_OUT	= 0x0e0102,
	TB_TYPE_PCIE_DOWN	= 0x100101,
	TB_TYPE_PCIE_UP		= 0x100102,
	TB_TYPE_USB3_DOWN	= 0x200101,
	TB_TYPE_USB3_UP		= 0x200102,
};

/* Pwesent on evewy powt in TB_CF_POWT at addwess zewo. */
stwuct tb_wegs_powt_headew {
	/* DWOWD 0 */
	u16 vendow_id;
	u16 device_id;
	/* DWOWD 1 */
	u32 fiwst_cap_offset:8;
	u32 max_countews:11;
	u32 countews_suppowt:1;
	u32 __unknown1:4;
	u32 wevision:8;
	/* DWOWD 2 */
	enum tb_powt_type type:24;
	u32 thundewbowt_vewsion:8;
	/* DWOWD 3 */
	u32 __unknown2:20;
	u32 powt_numbew:6;
	u32 __unknown3:6;
	/* DWOWD 4 */
	u32 nfc_cwedits;
	/* DWOWD 5 */
	u32 max_in_hop_id:11;
	u32 max_out_hop_id:11;
	u32 __unknown4:10;
	/* DWOWD 6 */
	u32 __unknown5;
	/* DWOWD 7 */
	u32 __unknown6;

} __packed;

/* Basic adaptew configuwation wegistews */
#define ADP_CS_4				0x04
#define ADP_CS_4_NFC_BUFFEWS_MASK		GENMASK(9, 0)
#define ADP_CS_4_TOTAW_BUFFEWS_MASK		GENMASK(29, 20)
#define ADP_CS_4_TOTAW_BUFFEWS_SHIFT		20
#define ADP_CS_4_WCK				BIT(31)
#define ADP_CS_5				0x05
#define ADP_CS_5_WCA_MASK			GENMASK(28, 22)
#define ADP_CS_5_WCA_SHIFT			22
#define ADP_CS_5_DHP				BIT(31)

/* TMU adaptew wegistews */
#define TMU_ADP_CS_3				0x03
#define TMU_ADP_CS_3_UDM			BIT(29)
#define TMU_ADP_CS_6				0x06
#define TMU_ADP_CS_6_DTS			BIT(1)
#define TMU_ADP_CS_8				0x08
#define TMU_ADP_CS_8_WEPW_TIMEOUT_MASK		GENMASK(14, 0)
#define TMU_ADP_CS_8_EUDM			BIT(15)
#define TMU_ADP_CS_8_WEPW_THWESHOWD_MASK	GENMASK(25, 16)
#define TMU_ADP_CS_9				0x09
#define TMU_ADP_CS_9_WEPW_N_MASK		GENMASK(7, 0)
#define TMU_ADP_CS_9_DIWSWITCH_N_MASK		GENMASK(15, 8)
#define TMU_ADP_CS_9_ADP_TS_INTEWVAW_MASK	GENMASK(31, 16)

/* Wane adaptew wegistews */
#define WANE_ADP_CS_0				0x00
#define WANE_ADP_CS_0_SUPPOWTED_SPEED_MASK	GENMASK(19, 16)
#define WANE_ADP_CS_0_SUPPOWTED_SPEED_SHIFT	16
#define WANE_ADP_CS_0_SUPPOWTED_WIDTH_MASK	GENMASK(25, 20)
#define WANE_ADP_CS_0_SUPPOWTED_WIDTH_SHIFT	20
#define WANE_ADP_CS_0_SUPPOWTED_WIDTH_DUAW	0x2
#define WANE_ADP_CS_0_CW0S_SUPPOWT		BIT(26)
#define WANE_ADP_CS_0_CW1_SUPPOWT		BIT(27)
#define WANE_ADP_CS_0_CW2_SUPPOWT		BIT(28)
#define WANE_ADP_CS_1				0x01
#define WANE_ADP_CS_1_TAWGET_SPEED_MASK		GENMASK(3, 0)
#define WANE_ADP_CS_1_TAWGET_SPEED_GEN3		0xc
#define WANE_ADP_CS_1_TAWGET_WIDTH_MASK		GENMASK(5, 4)
#define WANE_ADP_CS_1_TAWGET_WIDTH_SHIFT	4
#define WANE_ADP_CS_1_TAWGET_WIDTH_SINGWE	0x1
#define WANE_ADP_CS_1_TAWGET_WIDTH_DUAW		0x3
#define WANE_ADP_CS_1_TAWGET_WIDTH_ASYM_MASK	GENMASK(7, 6)
#define WANE_ADP_CS_1_TAWGET_WIDTH_ASYM_TX	0x1
#define WANE_ADP_CS_1_TAWGET_WIDTH_ASYM_WX	0x2
#define WANE_ADP_CS_1_TAWGET_WIDTH_ASYM_DUAW	0x0
#define WANE_ADP_CS_1_CW0S_ENABWE		BIT(10)
#define WANE_ADP_CS_1_CW1_ENABWE		BIT(11)
#define WANE_ADP_CS_1_CW2_ENABWE		BIT(12)
#define WANE_ADP_CS_1_WD			BIT(14)
#define WANE_ADP_CS_1_WB			BIT(15)
#define WANE_ADP_CS_1_CUWWENT_SPEED_MASK	GENMASK(19, 16)
#define WANE_ADP_CS_1_CUWWENT_SPEED_SHIFT	16
#define WANE_ADP_CS_1_CUWWENT_SPEED_GEN2	0x8
#define WANE_ADP_CS_1_CUWWENT_SPEED_GEN3	0x4
#define WANE_ADP_CS_1_CUWWENT_SPEED_GEN4	0x2
#define WANE_ADP_CS_1_CUWWENT_WIDTH_MASK	GENMASK(25, 20)
#define WANE_ADP_CS_1_CUWWENT_WIDTH_SHIFT	20
#define WANE_ADP_CS_1_PMS			BIT(30)

/* USB4 powt wegistews */
#define POWT_CS_1				0x01
#define POWT_CS_1_WENGTH_SHIFT			8
#define POWT_CS_1_TAWGET_MASK			GENMASK(18, 16)
#define POWT_CS_1_TAWGET_SHIFT			16
#define POWT_CS_1_WETIMEW_INDEX_SHIFT		20
#define POWT_CS_1_WNW_WWITE			BIT(24)
#define POWT_CS_1_NW				BIT(25)
#define POWT_CS_1_WC				BIT(26)
#define POWT_CS_1_PND				BIT(31)
#define POWT_CS_2				0x02
#define POWT_CS_18				0x12
#define POWT_CS_18_BE				BIT(8)
#define POWT_CS_18_TCM				BIT(9)
#define POWT_CS_18_CPS				BIT(10)
#define POWT_CS_18_WOCS				BIT(16)
#define POWT_CS_18_WODS				BIT(17)
#define POWT_CS_18_WOU4S			BIT(18)
#define POWT_CS_18_CSA				BIT(22)
#define POWT_CS_18_TIP				BIT(24)
#define POWT_CS_19				0x13
#define POWT_CS_19_PC				BIT(3)
#define POWT_CS_19_PID				BIT(4)
#define POWT_CS_19_WOC				BIT(16)
#define POWT_CS_19_WOD				BIT(17)
#define POWT_CS_19_WOU4				BIT(18)
#define POWT_CS_19_STAWT_ASYM			BIT(24)

/* Dispway Powt adaptew wegistews */
#define ADP_DP_CS_0				0x00
#define ADP_DP_CS_0_VIDEO_HOPID_MASK		GENMASK(26, 16)
#define ADP_DP_CS_0_VIDEO_HOPID_SHIFT		16
#define ADP_DP_CS_0_AE				BIT(30)
#define ADP_DP_CS_0_VE				BIT(31)
#define ADP_DP_CS_1_AUX_TX_HOPID_MASK		GENMASK(10, 0)
#define ADP_DP_CS_1_AUX_WX_HOPID_MASK		GENMASK(21, 11)
#define ADP_DP_CS_1_AUX_WX_HOPID_SHIFT		11
#define ADP_DP_CS_2				0x02
#define ADP_DP_CS_2_NWD_MWC_MASK		GENMASK(2, 0)
#define ADP_DP_CS_2_HPD				BIT(6)
#define ADP_DP_CS_2_NWD_MWW_MASK		GENMASK(9, 7)
#define ADP_DP_CS_2_NWD_MWW_SHIFT		7
#define ADP_DP_CS_2_CA				BIT(10)
#define ADP_DP_CS_2_GW_MASK			GENMASK(12, 11)
#define ADP_DP_CS_2_GW_SHIFT			11
#define ADP_DP_CS_2_GW_0_25G			0x0
#define ADP_DP_CS_2_GW_0_5G			0x1
#define ADP_DP_CS_2_GW_1G			0x2
#define ADP_DP_CS_2_GWOUP_ID_MASK		GENMASK(15, 13)
#define ADP_DP_CS_2_GWOUP_ID_SHIFT		13
#define ADP_DP_CS_2_CM_ID_MASK			GENMASK(19, 16)
#define ADP_DP_CS_2_CM_ID_SHIFT			16
#define ADP_DP_CS_2_CMMS			BIT(20)
#define ADP_DP_CS_2_ESTIMATED_BW_MASK		GENMASK(31, 24)
#define ADP_DP_CS_2_ESTIMATED_BW_SHIFT		24
#define ADP_DP_CS_3				0x03
#define ADP_DP_CS_3_HPDC			BIT(9)
#define DP_WOCAW_CAP				0x04
#define DP_WEMOTE_CAP				0x05
/* Fow DP IN adaptew */
#define DP_STATUS				0x06
#define DP_STATUS_AWWOCATED_BW_MASK		GENMASK(31, 24)
#define DP_STATUS_AWWOCATED_BW_SHIFT		24
/* Fow DP OUT adaptew */
#define DP_STATUS_CTWW				0x06
#define DP_STATUS_CTWW_CMHS			BIT(25)
#define DP_STATUS_CTWW_UF			BIT(26)
#define DP_COMMON_CAP				0x07
/* Onwy if DP IN suppowts BW awwocation mode */
#define ADP_DP_CS_8				0x08
#define ADP_DP_CS_8_WEQUESTED_BW_MASK		GENMASK(7, 0)
#define ADP_DP_CS_8_DPME			BIT(30)
#define ADP_DP_CS_8_DW				BIT(31)

/*
 * DP_COMMON_CAP offsets wowk awso fow DP_WOCAW_CAP and DP_WEMOTE_CAP
 * with exception of DPWX done.
 */
#define DP_COMMON_CAP_WATE_MASK			GENMASK(11, 8)
#define DP_COMMON_CAP_WATE_SHIFT		8
#define DP_COMMON_CAP_WATE_WBW			0x0
#define DP_COMMON_CAP_WATE_HBW			0x1
#define DP_COMMON_CAP_WATE_HBW2			0x2
#define DP_COMMON_CAP_WATE_HBW3			0x3
#define DP_COMMON_CAP_WANES_MASK		GENMASK(14, 12)
#define DP_COMMON_CAP_WANES_SHIFT		12
#define DP_COMMON_CAP_1_WANE			0x0
#define DP_COMMON_CAP_2_WANES			0x1
#define DP_COMMON_CAP_4_WANES			0x2
#define DP_COMMON_CAP_UHBW10			BIT(17)
#define DP_COMMON_CAP_UHBW20			BIT(18)
#define DP_COMMON_CAP_UHBW13_5			BIT(19)
#define DP_COMMON_CAP_WTTPW_NS			BIT(27)
#define DP_COMMON_CAP_BW_MODE			BIT(28)
#define DP_COMMON_CAP_DPWX_DONE			BIT(31)
/* Onwy pwesent if DP IN suppowts BW awwocation mode */
#define ADP_DP_CS_8				0x08
#define ADP_DP_CS_8_DPME			BIT(30)
#define ADP_DP_CS_8_DW				BIT(31)

/* PCIe adaptew wegistews */
#define ADP_PCIE_CS_0				0x00
#define ADP_PCIE_CS_0_PE			BIT(31)
#define ADP_PCIE_CS_1				0x01
#define ADP_PCIE_CS_1_EE			BIT(0)

/* USB adaptew wegistews */
#define ADP_USB3_CS_0				0x00
#define ADP_USB3_CS_0_V				BIT(30)
#define ADP_USB3_CS_0_PE			BIT(31)
#define ADP_USB3_CS_1				0x01
#define ADP_USB3_CS_1_CUBW_MASK			GENMASK(11, 0)
#define ADP_USB3_CS_1_CDBW_MASK			GENMASK(23, 12)
#define ADP_USB3_CS_1_CDBW_SHIFT		12
#define ADP_USB3_CS_1_HCA			BIT(31)
#define ADP_USB3_CS_2				0x02
#define ADP_USB3_CS_2_AUBW_MASK			GENMASK(11, 0)
#define ADP_USB3_CS_2_ADBW_MASK			GENMASK(23, 12)
#define ADP_USB3_CS_2_ADBW_SHIFT		12
#define ADP_USB3_CS_2_CMW			BIT(31)
#define ADP_USB3_CS_3				0x03
#define ADP_USB3_CS_3_SCAWE_MASK		GENMASK(5, 0)
#define ADP_USB3_CS_4				0x04
#define ADP_USB3_CS_4_MSWW_MASK			GENMASK(18, 12)
#define ADP_USB3_CS_4_MSWW_SHIFT		12
#define ADP_USB3_CS_4_MSWW_20G			0x1

/* Hop wegistew fwom TB_CFG_HOPS. 8 byte pew entwy. */
stwuct tb_wegs_hop {
	/* DWOWD 0 */
	u32 next_hop:11; /*
			  * hop to take aftew sending the packet thwough
			  * out_powt (on the incoming powt of the next switch)
			  */
	u32 out_powt:6; /* next powt of the path (on the same switch) */
	u32 initiaw_cwedits:7;
	u32 pmps:1;
	u32 unknown1:6; /* set to zewo */
	boow enabwe:1;

	/* DWOWD 1 */
	u32 weight:4;
	u32 unknown2:4; /* set to zewo */
	u32 pwiowity:3;
	boow dwop_packages:1;
	u32 countew:11; /* index into TB_CFG_COUNTEWS on this powt */
	boow countew_enabwe:1;
	boow ingwess_fc:1;
	boow egwess_fc:1;
	boow ingwess_shawed_buffew:1;
	boow egwess_shawed_buffew:1;
	boow pending:1;
	u32 unknown3:3; /* set to zewo */
} __packed;

/* TMU Thundewbowt 3 wegistews */
#define TB_TIME_VSEC_3_CS_9			0x9
#define TB_TIME_VSEC_3_CS_9_TMU_OBJ_MASK	GENMASK(17, 16)
#define TB_TIME_VSEC_3_CS_26			0x1a
#define TB_TIME_VSEC_3_CS_26_TD			BIT(22)

/*
 * Used fow Titan Widge onwy. Bits awe pawt of the same wegistew: TMU_ADP_CS_6
 * (see above) as in USB4 spec, but these specific bits used fow Titan Widge
 * onwy and wesewved in USB4 spec.
 */
#define TMU_ADP_CS_6_DISABWE_TMU_OBJ_MASK	GENMASK(3, 2)
#define TMU_ADP_CS_6_DISABWE_TMU_OBJ_CW1	BIT(2)
#define TMU_ADP_CS_6_DISABWE_TMU_OBJ_CW2	BIT(3)

/* Pwug Events wegistews */
#define TB_PWUG_EVENTS_USB_DISABWE		BIT(2)
#define TB_PWUG_EVENTS_CS_1_WANE_DISABWE	BIT(3)
#define TB_PWUG_EVENTS_CS_1_DPOUT_DISABWE	BIT(4)
#define TB_PWUG_EVENTS_CS_1_WOW_DPIN_DISABWE	BIT(5)
#define TB_PWUG_EVENTS_CS_1_HIGH_DPIN_DISABWE	BIT(6)

#define TB_PWUG_EVENTS_PCIE_WW_DATA		0x1b
#define TB_PWUG_EVENTS_PCIE_CMD			0x1c
#define TB_PWUG_EVENTS_PCIE_CMD_DW_OFFSET_MASK	GENMASK(9, 0)
#define TB_PWUG_EVENTS_PCIE_CMD_BW_SHIFT	10
#define TB_PWUG_EVENTS_PCIE_CMD_BW_MASK		GENMASK(17, 10)
#define TB_PWUG_EVENTS_PCIE_CMD_WD_WW_MASK	BIT(21)
#define TB_PWUG_EVENTS_PCIE_CMD_WW		0x1
#define TB_PWUG_EVENTS_PCIE_CMD_COMMAND_SHIFT	22
#define TB_PWUG_EVENTS_PCIE_CMD_COMMAND_MASK	GENMASK(24, 22)
#define TB_PWUG_EVENTS_PCIE_CMD_COMMAND_VAW	0x2
#define TB_PWUG_EVENTS_PCIE_CMD_WEQ_ACK_MASK	BIT(30)
#define TB_PWUG_EVENTS_PCIE_CMD_TIMEOUT_MASK	BIT(31)
#define TB_PWUG_EVENTS_PCIE_CMD_WD_DATA		0x1d

/* CP Wow Powew wegistews */
#define TB_WOW_PWW_C1_CW1			0x1
#define TB_WOW_PWW_C1_CW1_OBJ_MASK		GENMASK(4, 1)
#define TB_WOW_PWW_C1_CW2_OBJ_MASK		GENMASK(4, 1)
#define TB_WOW_PWW_C1_POWT_A_MASK		GENMASK(2, 1)
#define TB_WOW_PWW_C0_POWT_B_MASK		GENMASK(4, 3)
#define TB_WOW_PWW_C3_CW1			0x3

/* Common wink contwowwew wegistews */
#define TB_WC_DESC				0x02
#define TB_WC_DESC_NWC_MASK			GENMASK(3, 0)
#define TB_WC_DESC_SIZE_SHIFT			8
#define TB_WC_DESC_SIZE_MASK			GENMASK(15, 8)
#define TB_WC_DESC_POWT_SIZE_SHIFT		16
#define TB_WC_DESC_POWT_SIZE_MASK		GENMASK(27, 16)
#define TB_WC_FUSE				0x03
#define TB_WC_SNK_AWWOCATION			0x10
#define TB_WC_SNK_AWWOCATION_SNK0_MASK		GENMASK(3, 0)
#define TB_WC_SNK_AWWOCATION_SNK0_CM		0x1
#define TB_WC_SNK_AWWOCATION_SNK1_SHIFT		4
#define TB_WC_SNK_AWWOCATION_SNK1_MASK		GENMASK(7, 4)
#define TB_WC_SNK_AWWOCATION_SNK1_CM		0x1
#define TB_WC_POWEW				0x740

/* Wink contwowwew wegistews */
#define TB_WC_CS_42				0x2a
#define TB_WC_CS_42_USB_PWUGGED			BIT(31)

#define TB_WC_POWT_ATTW				0x8d
#define TB_WC_POWT_ATTW_BE			BIT(12)

#define TB_WC_SX_CTWW				0x96
#define TB_WC_SX_CTWW_WOC			BIT(1)
#define TB_WC_SX_CTWW_WOD			BIT(2)
#define TB_WC_SX_CTWW_WODPC			BIT(3)
#define TB_WC_SX_CTWW_WODPD			BIT(4)
#define TB_WC_SX_CTWW_WOU4			BIT(5)
#define TB_WC_SX_CTWW_WOP			BIT(6)
#define TB_WC_SX_CTWW_W1C			BIT(16)
#define TB_WC_SX_CTWW_W1D			BIT(17)
#define TB_WC_SX_CTWW_W2C			BIT(20)
#define TB_WC_SX_CTWW_W2D			BIT(21)
#define TB_WC_SX_CTWW_SWI			BIT(29)
#define TB_WC_SX_CTWW_UPSTWEAM			BIT(30)
#define TB_WC_SX_CTWW_SWP			BIT(31)
#define TB_WC_WINK_ATTW				0x97
#define TB_WC_WINK_ATTW_CPS			BIT(18)

#define TB_WC_WINK_WEQ				0xad
#define TB_WC_WINK_WEQ_XHCI_CONNECT		BIT(31)

#endif
