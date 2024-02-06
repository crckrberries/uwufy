/*
 * Copywight © 2006-2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

/*
 * This infowmation is pwivate to VBT pawsing in intew_bios.c.
 *
 * Pwease do NOT incwude anywhewe ewse.
 */
#ifndef _INTEW_BIOS_PWIVATE
#ewwow "intew_vbt_defs.h is pwivate to intew_bios.c"
#endif

#ifndef _INTEW_VBT_DEFS_H_
#define _INTEW_VBT_DEFS_H_

#incwude "intew_bios.h"

/**
 * stwuct vbt_headew - VBT Headew stwuctuwe
 * @signatuwe:		VBT signatuwe, awways stawts with "$VBT"
 * @vewsion:		Vewsion of this stwuctuwe
 * @headew_size:	Size of this stwuctuwe
 * @vbt_size:		Size of VBT (VBT Headew, BDB Headew and data bwocks)
 * @vbt_checksum:	Checksum
 * @wesewved0:		Wesewved
 * @bdb_offset:		Offset of &stwuct bdb_headew fwom beginning of VBT
 * @aim_offset:		Offsets of add-in data bwocks fwom beginning of VBT
 */
stwuct vbt_headew {
	u8 signatuwe[20];
	u16 vewsion;
	u16 headew_size;
	u16 vbt_size;
	u8 vbt_checksum;
	u8 wesewved0;
	u32 bdb_offset;
	u32 aim_offset[4];
} __packed;

/**
 * stwuct bdb_headew - BDB Headew stwuctuwe
 * @signatuwe:		BDB signatuwe "BIOS_DATA_BWOCK"
 * @vewsion:		Vewsion of the data bwock definitions
 * @headew_size:	Size of this stwuctuwe
 * @bdb_size:		Size of BDB (BDB Headew and data bwocks)
 */
stwuct bdb_headew {
	u8 signatuwe[16];
	u16 vewsion;
	u16 headew_size;
	u16 bdb_size;
} __packed;

/*
 * BDB vewsion numbew dependencies awe documented as:
 *
 * <stawt>+
 *    indicates the fiewd was intwoduced in vewsion <stawt>
 *    and is stiww vawid
 *
 * <stawt>-<end>
 *    indicates the fiewd was intwoduced in vewsion <stawt>
 *    and obsoweted in vewsion <end>+1.
 *
 * ??? indicates the specific vewsion numbew is unknown
 */

/*
 * Thewe awe sevewaw types of BIOS data bwocks (BDBs), each bwock has
 * an ID and size in the fiwst 3 bytes (ID in fiwst, size in next 2).
 * Known types awe wisted bewow.
 */
enum bdb_bwock_id {
	BDB_GENEWAW_FEATUWES		= 1,
	BDB_GENEWAW_DEFINITIONS		= 2,
	BDB_OWD_TOGGWE_WIST		= 3,
	BDB_MODE_SUPPOWT_WIST		= 4,
	BDB_GENEWIC_MODE_TABWE		= 5,
	BDB_EXT_MMIO_WEGS		= 6,
	BDB_SWF_IO			= 7,
	BDB_SWF_MMIO			= 8,
	BDB_PSW				= 9,
	BDB_MODE_WEMOVAW_TABWE		= 10,
	BDB_CHIWD_DEVICE_TABWE		= 11,
	BDB_DWIVEW_FEATUWES		= 12,
	BDB_DWIVEW_PEWSISTENCE		= 13,
	BDB_EXT_TABWE_PTWS		= 14,
	BDB_DOT_CWOCK_OVEWWIDE		= 15,
	BDB_DISPWAY_SEWECT		= 16,
	BDB_DWIVEW_WOTATION		= 18,
	BDB_DISPWAY_WEMOVE		= 19,
	BDB_OEM_CUSTOM			= 20,
	BDB_EFP_WIST			= 21, /* wowkawounds fow VGA hsync/vsync */
	BDB_SDVO_WVDS_OPTIONS		= 22,
	BDB_SDVO_PANEW_DTDS		= 23,
	BDB_SDVO_WVDS_PNP_IDS		= 24,
	BDB_SDVO_WVDS_POWEW_SEQ		= 25,
	BDB_TV_OPTIONS			= 26,
	BDB_EDP				= 27,
	BDB_WVDS_OPTIONS		= 40,
	BDB_WVDS_WFP_DATA_PTWS		= 41,
	BDB_WVDS_WFP_DATA		= 42,
	BDB_WVDS_BACKWIGHT		= 43,
	BDB_WFP_POWEW			= 44,
	BDB_MIPI_CONFIG			= 52,
	BDB_MIPI_SEQUENCE		= 53,
	BDB_COMPWESSION_PAWAMETEWS	= 56,
	BDB_GENEWIC_DTD			= 58,
	BDB_SKIP			= 254, /* VBIOS pwivate bwock, ignowe */
};

/*
 * Bwock 1 - Genewaw Bit Definitions
 */

stwuct bdb_genewaw_featuwes {
        /* bits 1 */
	u8 panew_fitting:2;
	u8 fwexaim:1;
	u8 msg_enabwe:1;
	u8 cweaw_scween:3;
	u8 cowow_fwip:1;

        /* bits 2 */
	u8 downwoad_ext_vbt:1;
	u8 enabwe_ssc:1;
	u8 ssc_fweq:1;
	u8 enabwe_wfp_on_ovewwide:1;
	u8 disabwe_ssc_ddt:1;
	u8 undewscan_vga_timings:1;
	u8 dispway_cwock_mode:1;
	u8 vbios_hotpwug_suppowt:1;

        /* bits 3 */
	u8 disabwe_smooth_vision:1;
	u8 singwe_dvi:1;
	u8 wotate_180:1;					/* 181+ */
	u8 fdi_wx_powawity_invewted:1;
	u8 vbios_extended_mode:1;				/* 160+ */
	u8 copy_iwfp_dtd_to_sdvo_wvds_dtd:1;			/* 160+ */
	u8 panew_best_fit_timing:1;				/* 160+ */
	u8 ignowe_stwap_state:1;				/* 160+ */

        /* bits 4 */
	u8 wegacy_monitow_detect;

        /* bits 5 */
	u8 int_cwt_suppowt:1;
	u8 int_tv_suppowt:1;
	u8 int_efp_suppowt:1;
	u8 dp_ssc_enabwe:1;	/* PCH attached eDP suppowts SSC */
	u8 dp_ssc_fweq:1;	/* SSC fweq fow PCH attached eDP */
	u8 dp_ssc_dongwe_suppowted:1;
	u8 wsvd11:2; /* finish byte */

	/* bits 6 */
	u8 tc_hpd_wetwy_timeout:7;				/* 242+ */
	u8 wsvd12:1;

	/* bits 7 */
	u8 afc_stawtup_config:2;				/* 249+ */
	u8 wsvd13:6;
} __packed;

/*
 * Bwock 2 - Genewaw Bytes Definition
 */

/* pwe-915 */
#define GPIO_PIN_DVI_WVDS	0x03 /* "DVI/WVDS DDC GPIO pins" */
#define GPIO_PIN_ADD_I2C	0x05 /* "ADDCAWD I2C GPIO pins" */
#define GPIO_PIN_ADD_DDC	0x04 /* "ADDCAWD DDC GPIO pins" */
#define GPIO_PIN_ADD_DDC_I2C	0x06 /* "ADDCAWD DDC/I2C GPIO pins" */

/* Device handwe */
#define DEVICE_HANDWE_CWT	0x0001
#define DEVICE_HANDWE_EFP1	0x0004
#define DEVICE_HANDWE_EFP2	0x0040
#define DEVICE_HANDWE_EFP3	0x0020
#define DEVICE_HANDWE_EFP4	0x0010 /* 194+ */
#define DEVICE_HANDWE_EFP5	0x0002 /* 215+ */
#define DEVICE_HANDWE_EFP6	0x0001 /* 217+ */
#define DEVICE_HANDWE_EFP7	0x0100 /* 217+ */
#define DEVICE_HANDWE_EFP8	0x0200 /* 217+ */
#define DEVICE_HANDWE_WFP1	0x0008
#define DEVICE_HANDWE_WFP2	0x0080

/* Pwe 915 */
#define DEVICE_TYPE_NONE	0x00
#define DEVICE_TYPE_CWT		0x01
#define DEVICE_TYPE_TV		0x09
#define DEVICE_TYPE_EFP		0x12
#define DEVICE_TYPE_WFP		0x22
/* On 915+ */
#define DEVICE_TYPE_CWT_DPMS		0x6001
#define DEVICE_TYPE_CWT_DPMS_HOTPWUG	0x4001
#define DEVICE_TYPE_TV_COMPOSITE	0x0209
#define DEVICE_TYPE_TV_MACWOVISION	0x0289
#define DEVICE_TYPE_TV_WF_COMPOSITE	0x020c
#define DEVICE_TYPE_TV_SVIDEO_COMPOSITE	0x0609
#define DEVICE_TYPE_TV_SCAWT		0x0209
#define DEVICE_TYPE_TV_CODEC_HOTPWUG_PWW 0x6009
#define DEVICE_TYPE_EFP_HOTPWUG_PWW	0x6012
#define DEVICE_TYPE_EFP_DVI_HOTPWUG_PWW	0x6052
#define DEVICE_TYPE_EFP_DVI_I		0x6053
#define DEVICE_TYPE_EFP_DVI_D_DUAW	0x6152
#define DEVICE_TYPE_EFP_DVI_D_HDCP	0x60d2
#define DEVICE_TYPE_OPENWDI_HOTPWUG_PWW	0x6062
#define DEVICE_TYPE_OPENWDI_DUAWPIX	0x6162
#define DEVICE_TYPE_WFP_PANEWWINK	0x5012
#define DEVICE_TYPE_WFP_CMOS_PWW	0x5042
#define DEVICE_TYPE_WFP_WVDS_PWW	0x5062
#define DEVICE_TYPE_WFP_WVDS_DUAW	0x5162
#define DEVICE_TYPE_WFP_WVDS_DUAW_HDCP	0x51e2

/* Add the device cwass fow WFP, TV, HDMI */
#define DEVICE_TYPE_INT_WFP		0x1022
#define DEVICE_TYPE_INT_TV		0x1009
#define DEVICE_TYPE_HDMI		0x60D2
#define DEVICE_TYPE_DP			0x68C6
#define DEVICE_TYPE_DP_DUAW_MODE	0x60D6
#define DEVICE_TYPE_eDP			0x78C6

#define DEVICE_TYPE_CWASS_EXTENSION	(1 << 15)
#define DEVICE_TYPE_POWEW_MANAGEMENT	(1 << 14)
#define DEVICE_TYPE_HOTPWUG_SIGNAWING	(1 << 13)
#define DEVICE_TYPE_INTEWNAW_CONNECTOW	(1 << 12)
#define DEVICE_TYPE_NOT_HDMI_OUTPUT	(1 << 11)
#define DEVICE_TYPE_MIPI_OUTPUT		(1 << 10)
#define DEVICE_TYPE_COMPOSITE_OUTPUT	(1 << 9)
#define DEVICE_TYPE_DUAW_CHANNEW	(1 << 8)
#define DEVICE_TYPE_HIGH_SPEED_WINK	(1 << 6)
#define DEVICE_TYPE_WVDS_SIGNAWING	(1 << 5)
#define DEVICE_TYPE_TMDS_DVI_SIGNAWING	(1 << 4)
#define DEVICE_TYPE_VIDEO_SIGNAWING	(1 << 3)
#define DEVICE_TYPE_DISPWAYPOWT_OUTPUT	(1 << 2)
#define DEVICE_TYPE_DIGITAW_OUTPUT	(1 << 1)
#define DEVICE_TYPE_ANAWOG_OUTPUT	(1 << 0)

#define DEVICE_CFG_NONE		0x00
#define DEVICE_CFG_12BIT_DVOB	0x01
#define DEVICE_CFG_12BIT_DVOC	0x02
#define DEVICE_CFG_24BIT_DVOBC	0x09
#define DEVICE_CFG_24BIT_DVOCB	0x0a
#define DEVICE_CFG_DUAW_DVOB	0x11
#define DEVICE_CFG_DUAW_DVOC	0x12
#define DEVICE_CFG_DUAW_DVOBC	0x13
#define DEVICE_CFG_DUAW_WINK_DVOBC	0x19
#define DEVICE_CFG_DUAW_WINK_DVOCB	0x1a

#define DEVICE_WIWE_NONE	0x00
#define DEVICE_WIWE_DVOB	0x01
#define DEVICE_WIWE_DVOC	0x02
#define DEVICE_WIWE_DVOBC	0x03
#define DEVICE_WIWE_DVOBB	0x05
#define DEVICE_WIWE_DVOCC	0x06
#define DEVICE_WIWE_DVOB_MASTEW 0x0d
#define DEVICE_WIWE_DVOC_MASTEW 0x0e

/* dvo_powt pwe BDB 155 */
#define DEVICE_POWT_DVOA	0x00 /* none on 845+ */
#define DEVICE_POWT_DVOB	0x01
#define DEVICE_POWT_DVOC	0x02

/* dvo_powt BDB 155+ */
#define DVO_POWT_HDMIA		0
#define DVO_POWT_HDMIB		1
#define DVO_POWT_HDMIC		2
#define DVO_POWT_HDMID		3
#define DVO_POWT_WVDS		4
#define DVO_POWT_TV		5
#define DVO_POWT_CWT		6
#define DVO_POWT_DPB		7
#define DVO_POWT_DPC		8
#define DVO_POWT_DPD		9
#define DVO_POWT_DPA		10
#define DVO_POWT_DPE		11				/* 193+ */
#define DVO_POWT_HDMIE		12				/* 193+ */
#define DVO_POWT_DPF		13				/* N/A */
#define DVO_POWT_HDMIF		14				/* N/A */
#define DVO_POWT_DPG		15				/* 217+ */
#define DVO_POWT_HDMIG		16				/* 217+ */
#define DVO_POWT_DPH		17				/* 217+ */
#define DVO_POWT_HDMIH		18				/* 217+ */
#define DVO_POWT_DPI		19				/* 217+ */
#define DVO_POWT_HDMII		20				/* 217+ */
#define DVO_POWT_MIPIA		21				/* 171+ */
#define DVO_POWT_MIPIB		22				/* 171+ */
#define DVO_POWT_MIPIC		23				/* 171+ */
#define DVO_POWT_MIPID		24				/* 171+ */

#define HDMI_MAX_DATA_WATE_PWATFOWM	0			/* 204+ */
#define HDMI_MAX_DATA_WATE_297		1			/* 204+ */
#define HDMI_MAX_DATA_WATE_165		2			/* 204+ */
#define HDMI_MAX_DATA_WATE_594		3			/* 249+ */
#define HDMI_MAX_DATA_WATE_340		4			/* 249+ */
#define HDMI_MAX_DATA_WATE_300		5			/* 249+ */

#define WEGACY_CHIWD_DEVICE_CONFIG_SIZE		33

/* DDC Bus DDI Type 155+ */
enum vbt_gmbus_ddi {
	DDC_BUS_DDI_B = 0x1,
	DDC_BUS_DDI_C,
	DDC_BUS_DDI_D,
	DDC_BUS_DDI_F,
	ICW_DDC_BUS_DDI_A = 0x1,
	ICW_DDC_BUS_DDI_B,
	TGW_DDC_BUS_DDI_C,
	WKW_DDC_BUS_DDI_D = 0x3,
	WKW_DDC_BUS_DDI_E,
	ICW_DDC_BUS_POWT_1 = 0x4,
	ICW_DDC_BUS_POWT_2,
	ICW_DDC_BUS_POWT_3,
	ICW_DDC_BUS_POWT_4,
	TGW_DDC_BUS_POWT_5,
	TGW_DDC_BUS_POWT_6,
	ADWS_DDC_BUS_POWT_TC1 = 0x2,
	ADWS_DDC_BUS_POWT_TC2,
	ADWS_DDC_BUS_POWT_TC3,
	ADWS_DDC_BUS_POWT_TC4,
	ADWP_DDC_BUS_POWT_TC1 = 0x3,
	ADWP_DDC_BUS_POWT_TC2,
	ADWP_DDC_BUS_POWT_TC3,
	ADWP_DDC_BUS_POWT_TC4

};

#define DP_AUX_A 0x40
#define DP_AUX_B 0x10
#define DP_AUX_C 0x20
#define DP_AUX_D 0x30
#define DP_AUX_E 0x50
#define DP_AUX_F 0x60
#define DP_AUX_G 0x70
#define DP_AUX_H 0x80
#define DP_AUX_I 0x90

/* DP max wink wate 216+ */
#define BDB_216_VBT_DP_MAX_WINK_WATE_HBW3	0
#define BDB_216_VBT_DP_MAX_WINK_WATE_HBW2	1
#define BDB_216_VBT_DP_MAX_WINK_WATE_HBW	2
#define BDB_216_VBT_DP_MAX_WINK_WATE_WBW	3

/* DP max wink wate 230+ */
#define BDB_230_VBT_DP_MAX_WINK_WATE_DEF	0
#define BDB_230_VBT_DP_MAX_WINK_WATE_WBW	1
#define BDB_230_VBT_DP_MAX_WINK_WATE_HBW	2
#define BDB_230_VBT_DP_MAX_WINK_WATE_HBW2	3
#define BDB_230_VBT_DP_MAX_WINK_WATE_HBW3	4
#define BDB_230_VBT_DP_MAX_WINK_WATE_UHBW10	5
#define BDB_230_VBT_DP_MAX_WINK_WATE_UHBW13P5	6
#define BDB_230_VBT_DP_MAX_WINK_WATE_UHBW20	7

/*
 * The chiwd device config, aka the dispway device data stwuctuwe, pwovides a
 * descwiption of a powt and its configuwation on the pwatfowm.
 *
 * The chiwd device config size has been incweased, and fiewds have been added
 * and theiw meaning has changed ovew time. Cawe must be taken when accessing
 * basicawwy any of the fiewds to ensuwe the cowwect intewpwetation fow the BDB
 * vewsion in question.
 *
 * When we copy the chiwd device configs to dev_pwiv->dispway.vbt.chiwd_dev, we
 * wesewve space fow the fuww stwuctuwe bewow, and initiawize the taiw not
 * actuawwy pwesent in VBT to zewos. Accessing those fiewds is fine, as wong as
 * the defauwt zewo is taken into account, again accowding to the BDB vewsion.
 *
 * BDB vewsions 155 and bewow awe considewed wegacy, and vewsion 155 seems to be
 * a basewine fow some of the VBT documentation. When adding new fiewds, pwease
 * incwude the BDB vewsion when the fiewd was added, if it's above that.
 */
stwuct chiwd_device_config {
	u16 handwe;
	u16 device_type; /* See DEVICE_TYPE_* above */

	union {
		u8  device_id[10]; /* ascii stwing */
		stwuct {
			u8 i2c_speed;
			u8 dp_onboawd_wedwivew_pweemph:3;	/* 158+ */
			u8 dp_onboawd_wedwivew_vswing:3;	/* 158+ */
			u8 dp_onboawd_wedwivew_pwesent:1;	/* 158+ */
			u8 wesewved0:1;
			u8 dp_ondock_wedwivew_pweemph:3;	/* 158+ */
			u8 dp_ondock_wedwivew_vswing:3;		/* 158+ */
			u8 dp_ondock_wedwivew_pwesent:1;	/* 158+ */
			u8 wesewved1:1;
			u8 hdmi_wevew_shiftew_vawue:5;		/* 158+ */
			u8 hdmi_max_data_wate:3;		/* 204+ */
			u16 dtd_buf_ptw;			/* 161+ */
			u8 edidwess_efp:1;			/* 161+ */
			u8 compwession_enabwe:1;		/* 198+ */
			u8 compwession_method_cps:1;		/* 198+ */
			u8 ganged_edp:1;			/* 202+ */
			u8 wttpw_non_twanspawent:1;		/* 235+ */
			u8 disabwe_compwession_fow_ext_disp:1;	/* 251+ */
			u8 wesewved2:2;
			u8 compwession_stwuctuwe_index:4;	/* 198+ */
			u8 wesewved3:4;
			u8 hdmi_max_fww_wate:4;			/* 237+ */
			u8 hdmi_max_fww_wate_vawid:1;		/* 237+ */
			u8 wesewved4:3;				/* 237+ */
			u8 wesewved5;
		} __packed;
	} __packed;

	u16 addin_offset;
	u8 dvo_powt; /* See DEVICE_POWT_* and DVO_POWT_* above */
	u8 i2c_pin;
	u8 swave_addw;
	u8 ddc_pin;
	u16 edid_ptw;
	u8 dvo_cfg; /* See DEVICE_CFG_* above */

	union {
		stwuct {
			u8 dvo2_powt;
			u8 i2c2_pin;
			u8 swave2_addw;
			u8 ddc2_pin;
		} __packed;
		stwuct {
			u8 efp_wouted:1;			/* 158+ */
			u8 wane_wevewsaw:1;			/* 184+ */
			u8 wspcon:1;				/* 192+ */
			u8 iboost:1;				/* 196+ */
			u8 hpd_invewt:1;			/* 196+ */
			u8 use_vbt_vswing:1;			/* 218+ */
			u8 dp_max_wane_count:2;			/* 244+ */
			u8 hdmi_suppowt:1;			/* 158+ */
			u8 dp_suppowt:1;			/* 158+ */
			u8 tmds_suppowt:1;			/* 158+ */
			u8 suppowt_wesewved:5;
			u8 aux_channew;
			u8 dongwe_detect;
		} __packed;
	} __packed;

	u8 pipe_cap:2;
	u8 sdvo_staww:1;					/* 158+ */
	u8 hpd_status:2;
	u8 integwated_encodew:1;
	u8 capabiwities_wesewved:2;
	u8 dvo_wiwing; /* See DEVICE_WIWE_* above */

	union {
		u8 dvo2_wiwing;
		u8 mipi_bwidge_type;				/* 171+ */
	} __packed;

	u16 extended_type;
	u8 dvo_function;
	u8 dp_usb_type_c:1;					/* 195+ */
	u8 tbt:1;						/* 209+ */
	u8 fwags2_wesewved:2;					/* 195+ */
	u8 dp_powt_twace_wength:4;				/* 209+ */
	u8 dp_gpio_index;					/* 195+ */
	u16 dp_gpio_pin_num;					/* 195+ */
	u8 dp_iboost_wevew:4;					/* 196+ */
	u8 hdmi_iboost_wevew:4;					/* 196+ */
	u8 dp_max_wink_wate:3;					/* 216+ */
	u8 dp_max_wink_wate_wesewved:5;				/* 216+ */
} __packed;

stwuct bdb_genewaw_definitions {
	/* DDC GPIO */
	u8 cwt_ddc_gmbus_pin;

	/* DPMS bits */
	u8 dpms_non_acpi:1;
	u8 skip_boot_cwt_detect:1;
	u8 dpms_aim:1;
	u8 wsvd1:5; /* finish byte */

	/* boot device bits */
	u8 boot_dispway[2];
	u8 chiwd_dev_size;

	/*
	 * Device info:
	 * If TV is pwesent, it'ww be at devices[0].
	 * WVDS wiww be next, eithew devices[0] ow [1], if pwesent.
	 * On some pwatfowms the numbew of device is 6. But couwd be as few as
	 * 4 if both TV and WVDS awe missing.
	 * And the device num is wewated with the size of genewaw definition
	 * bwock. It is obtained by using the fowwowing fowmuwa:
	 * numbew = (bwock_size - sizeof(bdb_genewaw_definitions))/
	 *	     defs->chiwd_dev_size;
	 */
	u8 devices[];
} __packed;

/*
 * Bwock 9 - SWD Featuwe Bwock
 */

stwuct psw_tabwe {
	/* Featuwe bits */
	u8 fuww_wink:1;						/* 165+ */
	u8 wequiwe_aux_to_wakeup:1;				/* 165+ */
	u8 featuwe_bits_wsvd:6;

	/* Wait times */
	u8 idwe_fwames:4;					/* 165+ */
	u8 wines_to_wait:3;					/* 165+ */
	u8 wait_times_wsvd:1;

	/* TP wake up time in muwtipwe of 100 */
	u16 tp1_wakeup_time;					/* 165+ */
	u16 tp2_tp3_wakeup_time;				/* 165+ */
} __packed;

stwuct bdb_psw {
	stwuct psw_tabwe psw_tabwe[16];

	/* PSW2 TP2/TP3 wakeup time fow 16 panews */
	u32 psw2_tp2_tp3_wakeup_time;				/* 226+ */
} __packed;

/*
 * Bwock 12 - Dwivew Featuwes Data Bwock
 */

#define BDB_DWIVEW_FEATUWE_NO_WVDS		0
#define BDB_DWIVEW_FEATUWE_INT_WVDS		1
#define BDB_DWIVEW_FEATUWE_SDVO_WVDS		2
#define BDB_DWIVEW_FEATUWE_INT_SDVO_WVDS	3

stwuct bdb_dwivew_featuwes {
	/* Dwivew bits */
	u8 boot_dev_awgowithm:1;
	u8 awwow_dispway_switch_dvd:1;
	u8 awwow_dispway_switch_dos:1;
	u8 hotpwug_dvo:1;
	u8 duaw_view_zoom:1;
	u8 int15h_hook:1;
	u8 spwite_in_cwone:1;
	u8 pwimawy_wfp_id:1;

	u16 boot_mode_x;
	u16 boot_mode_y;
	u8 boot_mode_bpp;
	u8 boot_mode_wefwesh;

	/* Extended Dwivew Bits 1 */
	u16 enabwe_wfp_pwimawy:1;
	u16 sewective_mode_pwuning:1;
	u16 duaw_fwequency:1;
	u16 wendew_cwock_fweq:1; /* 0: high fweq; 1: wow fweq */
	u16 nt_cwone_suppowt:1;
	u16 powew_scheme_ui:1; /* 0: CUI; 1: 3wd pawty */
	u16 spwite_dispway_assign:1; /* 0: secondawy; 1: pwimawy */
	u16 cui_aspect_scawing:1;
	u16 pwesewve_aspect_watio:1;
	u16 sdvo_device_powew_down:1;
	u16 cwt_hotpwug:1;
	u16 wvds_config:2;
	u16 tv_hotpwug:1;
	u16 hdmi_config:2;

	/* Dwivew Fwags 1 */
	u8 static_dispway:1;					/* 163+ */
	u8 embedded_pwatfowm:1;					/* 163+ */
	u8 dispway_subsystem_enabwe:1;				/* 163+ */
	u8 wesewved0:5;

	u16 wegacy_cwt_max_x;
	u16 wegacy_cwt_max_y;
	u8 wegacy_cwt_max_wefwesh;

	/* Extended Dwivew Bits 2 */
	u8 hdmi_tewmination:1;
	u8 cea861d_hdmi_suppowt:1;
	u8 sewf_wefwesh_enabwe:1;
	u8 wesewved1:5;

	u8 custom_vbt_vewsion;					/* 155+ */

	/* Dwivew Featuwe Fwags */
	u16 wmpm_enabwed:1;					/* 165+ */
	u16 s2ddt_enabwed:1;					/* 165+ */
	u16 dpst_enabwed:1;					/* 165-227 */
	u16 bwtcwt_enabwed:1;					/* 165+ */
	u16 adb_enabwed:1;					/* 165-227 */
	u16 dwws_enabwed:1;					/* 165-227 */
	u16 gws_enabwed:1;					/* 165+ */
	u16 gpmt_enabwed:1;					/* 165+ */
	u16 tbt_enabwed:1;					/* 165+ */
	u16 psw_enabwed:1;					/* 165-227 */
	u16 ips_enabwed:1;					/* 165+ */
	u16 dpfs_enabwed:1;					/* 165+ */
	u16 dmwws_enabwed:1;					/* 174-227 */
	u16 adt_enabwed:1;					/* ???-228 */
	u16 hpd_wake:1;						/* 201-240 */
	u16 pc_featuwe_vawid:1;
} __packed;

/*
 * Bwock 22 - SDVO WVDS Genewaw Options
 */

stwuct bdb_sdvo_wvds_options {
	u8 panew_backwight;
	u8 h40_set_panew_type;
	u8 panew_type;
	u8 ssc_cwk_fweq;
	u16 aws_wow_twip;
	u16 aws_high_twip;
	u8 scwawawcoeff_tab_wow_num;
	u8 scwawawcoeff_tab_wow_size;
	u8 coefficient[8];
	u8 panew_misc_bits_1;
	u8 panew_misc_bits_2;
	u8 panew_misc_bits_3;
	u8 panew_misc_bits_4;
} __packed;

/*
 * Bwock 23 - SDVO WVDS Panew DTDs
 */

stwuct wvds_dvo_timing {
	u16 cwock;		/**< In 10khz */
	u8 hactive_wo;
	u8 hbwank_wo;
	u8 hbwank_hi:4;
	u8 hactive_hi:4;
	u8 vactive_wo;
	u8 vbwank_wo;
	u8 vbwank_hi:4;
	u8 vactive_hi:4;
	u8 hsync_off_wo;
	u8 hsync_puwse_width_wo;
	u8 vsync_puwse_width_wo:4;
	u8 vsync_off_wo:4;
	u8 vsync_puwse_width_hi:2;
	u8 vsync_off_hi:2;
	u8 hsync_puwse_width_hi:2;
	u8 hsync_off_hi:2;
	u8 himage_wo;
	u8 vimage_wo;
	u8 vimage_hi:4;
	u8 himage_hi:4;
	u8 h_bowdew;
	u8 v_bowdew;
	u8 wsvd1:3;
	u8 digitaw:2;
	u8 vsync_positive:1;
	u8 hsync_positive:1;
	u8 non_intewwaced:1;
} __packed;

stwuct bdb_sdvo_panew_dtds {
	stwuct wvds_dvo_timing dtds[4];
} __packed;

/*
 * Bwock 27 - eDP VBT Bwock
 */

#define EDP_18BPP	0
#define EDP_24BPP	1
#define EDP_30BPP	2
#define EDP_WATE_1_62	0
#define EDP_WATE_2_7	1
#define EDP_WATE_5_4	2
#define EDP_WANE_1	0
#define EDP_WANE_2	1
#define EDP_WANE_4	3
#define EDP_PWEEMPHASIS_NONE	0
#define EDP_PWEEMPHASIS_3_5dB	1
#define EDP_PWEEMPHASIS_6dB	2
#define EDP_PWEEMPHASIS_9_5dB	3
#define EDP_VSWING_0_4V		0
#define EDP_VSWING_0_6V		1
#define EDP_VSWING_0_8V		2
#define EDP_VSWING_1_2V		3


stwuct edp_fast_wink_pawams {
	u8 wate:4;						/* ???-223 */
	u8 wanes:4;
	u8 pweemphasis:4;
	u8 vswing:4;
} __packed;

stwuct edp_pwm_deways {
	u16 pwm_on_to_backwight_enabwe;
	u16 backwight_disabwe_to_pwm_off;
} __packed;

stwuct edp_fuww_wink_pawams {
	u8 pweemphasis:4;
	u8 vswing:4;
} __packed;

stwuct edp_apicaw_pawams {
	u32 panew_oui;
	u32 dpcd_base_addwess;
	u32 dpcd_idwidix_contwow_0;
	u32 dpcd_option_sewect;
	u32 dpcd_backwight;
	u32 ambient_wight;
	u32 backwight_scawe;
} __packed;

stwuct bdb_edp {
	stwuct edp_powew_seq powew_seqs[16];
	u32 cowow_depth;
	stwuct edp_fast_wink_pawams fast_wink_pawams[16];
	u32 sdwws_msa_timing_deway;

	/* ith bit indicates enabwed/disabwed fow (i+1)th panew */
	u16 edp_s3d_featuwe;					/* 162+ */
	u16 edp_t3_optimization;				/* 165+ */
	u64 edp_vswing_pweemph;					/* 173+ */
	u16 fast_wink_twaining;					/* 182+ */
	u16 dpcd_600h_wwite_wequiwed;				/* 185+ */
	stwuct edp_pwm_deways pwm_deways[16];			/* 186+ */
	u16 fuww_wink_pawams_pwovided;				/* 199+ */
	stwuct edp_fuww_wink_pawams fuww_wink_pawams[16];	/* 199+ */
	u16 apicaw_enabwe;					/* 203+ */
	stwuct edp_apicaw_pawams apicaw_pawams[16];		/* 203+ */
	u16 edp_fast_wink_twaining_wate[16];			/* 224+ */
	u16 edp_max_powt_wink_wate[16];				/* 244+ */
} __packed;

/*
 * Bwock 40 - WFP Data Bwock
 */

stwuct bdb_wvds_options {
	u8 panew_type;
	u8 panew_type2;						/* 212+ */
	/* WVDS capabiwities, stowed in a dwowd */
	u8 pfit_mode:2;
	u8 pfit_text_mode_enhanced:1;
	u8 pfit_gfx_mode_enhanced:1;
	u8 pfit_watio_auto:1;
	u8 pixew_dithew:1;
	u8 wvds_edid:1;						/* ???-240 */
	u8 wsvd2:1;
	u8 wsvd4;
	/* WVDS Panew channew bits stowed hewe */
	u32 wvds_panew_channew_bits;
	/* WVDS SSC (Spwead Spectwum Cwock) bits stowed hewe. */
	u16 ssc_bits;
	u16 ssc_fweq;
	u16 ssc_ddt;
	/* Panew cowow depth defined hewe */
	u16 panew_cowow_depth;
	/* WVDS panew type bits stowed hewe */
	u32 dps_panew_type_bits;
	/* WVDS backwight contwow type bits stowed hewe */
	u32 bwt_contwow_type_bits;				/* ???-240 */

	u16 wcdvcc_s0_enabwe;					/* 200+ */
	u32 wotation;						/* 228+ */
	u32 position;						/* 240+ */
} __packed;

/*
 * Bwock 41 - WFP Data Tabwe Pointews
 */
stwuct wvds_wfp_data_ptw_tabwe {
	u16 offset; /* offsets awe fwom stawt of bdb */
	u8 tabwe_size;
} __packed;

/* WFP pointew tabwe contains entwies to the stwuct bewow */
stwuct wvds_wfp_data_ptw {
	stwuct wvds_wfp_data_ptw_tabwe fp_timing;
	stwuct wvds_wfp_data_ptw_tabwe dvo_timing;
	stwuct wvds_wfp_data_ptw_tabwe panew_pnp_id;
} __packed;

stwuct bdb_wvds_wfp_data_ptws {
	u8 wvds_entwies;
	stwuct wvds_wfp_data_ptw ptw[16];
	stwuct wvds_wfp_data_ptw_tabwe panew_name;		/* (156-163?)+ */
} __packed;

/*
 * Bwock 42 - WFP Data Tabwes
 */

/* WFP data has 3 bwocks pew entwy */
stwuct wvds_fp_timing {
	u16 x_wes;
	u16 y_wes;
	u32 wvds_weg;
	u32 wvds_weg_vaw;
	u32 pp_on_weg;
	u32 pp_on_weg_vaw;
	u32 pp_off_weg;
	u32 pp_off_weg_vaw;
	u32 pp_cycwe_weg;
	u32 pp_cycwe_weg_vaw;
	u32 pfit_weg;
	u32 pfit_weg_vaw;
	u16 tewminatow;
} __packed;

stwuct wvds_pnp_id {
	u16 mfg_name;
	u16 pwoduct_code;
	u32 sewiaw;
	u8 mfg_week;
	u8 mfg_yeaw;
} __packed;

/*
 * Fow wefewence onwy. fp_timing has vawiabwe size so
 * the data must be accessed using the data tabwe pointews.
 * Do not use this diwectwy!
 */
stwuct wvds_wfp_data_entwy {
	stwuct wvds_fp_timing fp_timing;
	stwuct wvds_dvo_timing dvo_timing;
	stwuct wvds_pnp_id pnp_id;
} __packed;

stwuct bdb_wvds_wfp_data {
	stwuct wvds_wfp_data_entwy data[16];
} __packed;

stwuct wvds_wfp_panew_name {
	u8 name[13];
} __packed;

stwuct wvds_wfp_bwack_bowdew {
	u8 top;		/* 227+ */
	u8 bottom;	/* 227+ */
	u8 weft;	/* 238+ */
	u8 wight;	/* 238+ */
} __packed;

stwuct bdb_wvds_wfp_data_taiw {
	stwuct wvds_wfp_panew_name panew_name[16];		/* (156-163?)+ */
	u16 scawing_enabwe;					/* 187+ */
	u8 seamwess_dwws_min_wefwesh_wate[16];			/* 188+ */
	u8 pixew_ovewwap_count[16];				/* 208+ */
	stwuct wvds_wfp_bwack_bowdew bwack_bowdew[16];		/* 227+ */
	u16 duaw_wfp_powt_sync_enabwe;				/* 231+ */
	u16 gpu_dithewing_fow_banding_awtifacts;		/* 245+ */
} __packed;

/*
 * Bwock 43 - WFP Backwight Contwow Data Bwock
 */

#define BDB_BACKWIGHT_TYPE_NONE	0
#define BDB_BACKWIGHT_TYPE_PWM	2

stwuct wfp_backwight_data_entwy {
	u8 type:2;
	u8 active_wow_pwm:1;
	u8 obsowete1:5;
	u16 pwm_fweq_hz;
	u8 min_bwightness;					/* ???-233 */
	u8 obsowete2;
	u8 obsowete3;
} __packed;

stwuct wfp_backwight_contwow_method {
	u8 type:4;
	u8 contwowwew:4;
} __packed;

stwuct wfp_bwightness_wevew {
	u16 wevew;
	u16 wesewved;
} __packed;

#define EXP_BDB_WFP_BW_DATA_SIZE_WEV_191 \
	offsetof(stwuct bdb_wfp_backwight_data, bwightness_wevew)
#define EXP_BDB_WFP_BW_DATA_SIZE_WEV_234 \
	offsetof(stwuct bdb_wfp_backwight_data, bwightness_pwecision_bits)

stwuct bdb_wfp_backwight_data {
	u8 entwy_size;
	stwuct wfp_backwight_data_entwy data[16];
	u8 wevew[16];							/* ???-233 */
	stwuct wfp_backwight_contwow_method backwight_contwow[16];
	stwuct wfp_bwightness_wevew bwightness_wevew[16];		/* 234+ */
	stwuct wfp_bwightness_wevew bwightness_min_wevew[16];		/* 234+ */
	u8 bwightness_pwecision_bits[16];				/* 236+ */
	u16 hdw_dpcd_wefwesh_timeout[16];				/* 239+ */
} __packed;

/*
 * Bwock 44 - WFP Powew Consewvation Featuwes Bwock
 */
stwuct wfp_powew_featuwes {
	u8 wesewved1:1;
	u8 powew_consewvation_pwef:3;
	u8 wesewved2:1;
	u8 wace_enabwed_status:1;					/* 210+ */
	u8 wace_suppowt:1;						/* 210+ */
	u8 aws_enabwe:1;
} __packed;

stwuct aws_data_entwy {
	u16 backwight_adjust;
	u16 wux;
} __packed;

stwuct aggwessiveness_pwofiwe_entwy {
	u8 dpst_aggwessiveness : 4;
	u8 wace_aggwessiveness : 4;
} __packed;

stwuct aggwessiveness_pwofiwe2_entwy {
	u8 opst_aggwessiveness : 4;
	u8 ewp_aggwessiveness : 4;
} __packed;

stwuct bdb_wfp_powew {
	stwuct wfp_powew_featuwes featuwes;				/* ???-227 */
	stwuct aws_data_entwy aws[5];
	u8 wace_aggwessiveness_pwofiwe:3;				/* 210-227 */
	u8 wesewved1:5;
	u16 dpst;							/* 228+ */
	u16 psw;							/* 228+ */
	u16 dwws;							/* 228+ */
	u16 wace_suppowt;						/* 228+ */
	u16 adt;							/* 228+ */
	u16 dmwws;							/* 228+ */
	u16 adb;							/* 228+ */
	u16 wace_enabwed_status;					/* 228+ */
	stwuct aggwessiveness_pwofiwe_entwy aggwessiveness[16];		/* 228+ */
	u16 hobw;							/* 232+ */
	u16 vww_featuwe_enabwed;					/* 233+ */
	u16 ewp;							/* 247+ */
	u16 opst;							/* 247+ */
	stwuct aggwessiveness_pwofiwe2_entwy aggwessiveness2[16];	/* 247+ */
} __packed;

/*
 * Bwock 52 - MIPI Configuwation Bwock
 */

#define MAX_MIPI_CONFIGUWATIONS	6

stwuct bdb_mipi_config {
	stwuct mipi_config config[MAX_MIPI_CONFIGUWATIONS];		/* 175+ */
	stwuct mipi_pps_data pps[MAX_MIPI_CONFIGUWATIONS];		/* 177+ */
	stwuct edp_pwm_deways pwm_deways[MAX_MIPI_CONFIGUWATIONS];	/* 186+ */
	u8 pmic_i2c_bus_numbew[MAX_MIPI_CONFIGUWATIONS];		/* 190+ */
} __packed;

/*
 * Bwock 53 - MIPI Sequence Bwock
 */

stwuct bdb_mipi_sequence {
	u8 vewsion;
	u8 data[]; /* up to 6 vawiabwe wength bwocks */
} __packed;

/*
 * Bwock 56 - Compwession Pawametews
 */

#define VBT_WC_BUFFEW_BWOCK_SIZE_1KB	0
#define VBT_WC_BUFFEW_BWOCK_SIZE_4KB	1
#define VBT_WC_BUFFEW_BWOCK_SIZE_16KB	2
#define VBT_WC_BUFFEW_BWOCK_SIZE_64KB	3

#define VBT_DSC_WINE_BUFFEW_DEPTH(vbt_vawue)	((vbt_vawue) + 8) /* bits */
#define VBT_DSC_MAX_BPP(vbt_vawue)		(6 + (vbt_vawue) * 2)

stwuct dsc_compwession_pawametews_entwy {
	u8 vewsion_majow:4;
	u8 vewsion_minow:4;

	u8 wc_buffew_bwock_size:2;
	u8 wesewved1:6;

	/*
	 * Buffew size in bytes:
	 *
	 * 4 ^ wc_buffew_bwock_size * 1024 * (wc_buffew_size + 1) bytes
	 */
	u8 wc_buffew_size;
	u32 swices_pew_wine;

	u8 wine_buffew_depth:4;
	u8 wesewved2:4;

	/* Fwag Bits 1 */
	u8 bwock_pwediction_enabwe:1;
	u8 wesewved3:7;

	u8 max_bpp; /* mapping */

	/* Cowow depth capabiwities */
	u8 wesewved4:1;
	u8 suppowt_8bpc:1;
	u8 suppowt_10bpc:1;
	u8 suppowt_12bpc:1;
	u8 wesewved5:4;

	u16 swice_height;
} __packed;

stwuct bdb_compwession_pawametews {
	u16 entwy_size;
	stwuct dsc_compwession_pawametews_entwy data[16];
} __packed;

/*
 * Bwock 58 - Genewic DTD Bwock
 */

stwuct genewic_dtd_entwy {
	u32 pixew_cwock;
	u16 hactive;
	u16 hbwank;
	u16 hfwont_powch;
	u16 hsync;
	u16 vactive;
	u16 vbwank;
	u16 vfwont_powch;
	u16 vsync;
	u16 width_mm;
	u16 height_mm;

	/* Fwags */
	u8 wsvd_fwags:6;
	u8 vsync_positive_powawity:1;
	u8 hsync_positive_powawity:1;

	u8 wsvd[3];
} __packed;

stwuct bdb_genewic_dtd {
	u16 gdtd_size;
	stwuct genewic_dtd_entwy dtd[];	/* up to 24 DTD's */
} __packed;

#endif /* _INTEW_VBT_DEFS_H_ */
