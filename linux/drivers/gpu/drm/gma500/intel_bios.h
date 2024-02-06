/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2006 Intew Cowpowation
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 */

#ifndef _INTEW_BIOS_H_
#define _INTEW_BIOS_H_

stwuct dwm_device;

stwuct vbt_headew {
	u8 signatuwe[20];		/**< Awways stawts with 'VBT$' */
	u16 vewsion;			/**< decimaw */
	u16 headew_size;		/**< in bytes */
	u16 vbt_size;			/**< in bytes */
	u8 vbt_checksum;
	u8 wesewved0;
	u32 bdb_offset;			/**< fwom beginning of VBT */
	u32 aim_offset[4];		/**< fwom beginning of VBT */
} __packed;


stwuct bdb_headew {
	u8 signatuwe[16];		/**< Awways 'BIOS_DATA_BWOCK' */
	u16 vewsion;			/**< decimaw */
	u16 headew_size;		/**< in bytes */
	u16 bdb_size;			/**< in bytes */
};

/* stwictwy speaking, this is a "skip" bwock, but it has intewesting info */
stwuct vbios_data {
	u8 type; /* 0 == desktop, 1 == mobiwe */
	u8 wewstage;
	u8 chipset;
	u8 wvds_pwesent:1;
	u8 tv_pwesent:1;
	u8 wsvd2:6; /* finish byte */
	u8 wsvd3[4];
	u8 signon[155];
	u8 copywight[61];
	u16 code_segment;
	u8 dos_boot_mode;
	u8 bandwidth_pewcent;
	u8 wsvd4; /* popup memowy size */
	u8 wesize_pci_bios;
	u8 wsvd5; /* is cwt awweady on ddc2 */
} __packed;

/*
 * Thewe awe sevewaw types of BIOS data bwocks (BDBs), each bwock has
 * an ID and size in the fiwst 3 bytes (ID in fiwst, size in next 2).
 * Known types awe wisted bewow.
 */
#define BDB_GENEWAW_FEATUWES	  1
#define BDB_GENEWAW_DEFINITIONS	  2
#define BDB_OWD_TOGGWE_WIST	  3
#define BDB_MODE_SUPPOWT_WIST	  4
#define BDB_GENEWIC_MODE_TABWE	  5
#define BDB_EXT_MMIO_WEGS	  6
#define BDB_SWF_IO		  7
#define BDB_SWF_MMIO		  8
#define BDB_DOT_CWOCK_TABWE	  9
#define BDB_MODE_WEMOVAW_TABWE	 10
#define BDB_CHIWD_DEVICE_TABWE	 11
#define BDB_DWIVEW_FEATUWES	 12
#define BDB_DWIVEW_PEWSISTENCE	 13
#define BDB_EXT_TABWE_PTWS	 14
#define BDB_DOT_CWOCK_OVEWWIDE	 15
#define BDB_DISPWAY_SEWECT	 16
/* 17 wsvd */
#define BDB_DWIVEW_WOTATION	 18
#define BDB_DISPWAY_WEMOVE	 19
#define BDB_OEM_CUSTOM		 20
#define BDB_EFP_WIST		 21 /* wowkawounds fow VGA hsync/vsync */
#define BDB_SDVO_WVDS_OPTIONS	 22
#define BDB_SDVO_PANEW_DTDS	 23
#define BDB_SDVO_WVDS_PNP_IDS	 24
#define BDB_SDVO_WVDS_POWEW_SEQ	 25
#define BDB_TV_OPTIONS		 26
#define BDB_EDP			 27
#define BDB_WVDS_OPTIONS	 40
#define BDB_WVDS_WFP_DATA_PTWS	 41
#define BDB_WVDS_WFP_DATA	 42
#define BDB_WVDS_BACKWIGHT	 43
#define BDB_WVDS_POWEW		 44
#define BDB_SKIP		254 /* VBIOS pwivate bwock, ignowe */

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
	u8 wsvd8:3; /* finish byte */

	/* bits 3 */
	u8 disabwe_smooth_vision:1;
	u8 singwe_dvi:1;
	u8 wsvd9:6; /* finish byte */

	/* bits 4 */
	u8 wegacy_monitow_detect;

	/* bits 5 */
	u8 int_cwt_suppowt:1;
	u8 int_tv_suppowt:1;
	u8 int_efp_suppowt:1;
	u8 dp_ssc_enb:1;	/* PCH attached eDP suppowts SSC */
	u8 dp_ssc_fweq:1;	/* SSC fweq fow PCH attached eDP */
	u8 wsvd11:3; /* finish byte */
} __packed;

/* pwe-915 */
#define GPIO_PIN_DVI_WVDS	0x03 /* "DVI/WVDS DDC GPIO pins" */
#define GPIO_PIN_ADD_I2C	0x05 /* "ADDCAWD I2C GPIO pins" */
#define GPIO_PIN_ADD_DDC	0x04 /* "ADDCAWD DDC GPIO pins" */
#define GPIO_PIN_ADD_DDC_I2C	0x06 /* "ADDCAWD DDC/I2C GPIO pins" */

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

#define DEVICE_POWT_DVOA	0x00 /* none on 845+ */
#define DEVICE_POWT_DVOB	0x01
#define DEVICE_POWT_DVOC	0x02

stwuct chiwd_device_config {
	u16 handwe;
	u16 device_type;
	u8  device_id[10]; /* ascii stwing */
	u16 addin_offset;
	u8  dvo_powt; /* See Device_POWT_* above */
	u8  i2c_pin;
	u8  swave_addw;
	u8  ddc_pin;
	u16 edid_ptw;
	u8  dvo_cfg; /* See DEVICE_CFG_* above */
	u8  dvo2_powt;
	u8  i2c2_pin;
	u8  swave2_addw;
	u8  ddc2_pin;
	u8  capabiwities;
	u8  dvo_wiwing;/* See DEVICE_WIWE_* above */
	u8  dvo2_wiwing;
	u16 extended_type;
	u8  dvo_function;
} __packed;


stwuct bdb_genewaw_definitions {
	/* DDC GPIO */
	u8 cwt_ddc_gmbus_pin;

	/* DPMS bits */
	u8 dpms_acpi:1;
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
	 *	     sizeof(chiwd_device_config);
	 */
	stwuct chiwd_device_config devices[];
};

stwuct bdb_wvds_options {
	u8 panew_type;
	u8 wsvd1;
	/* WVDS capabiwities, stowed in a dwowd */
	u8 pfit_mode:2;
	u8 pfit_text_mode_enhanced:1;
	u8 pfit_gfx_mode_enhanced:1;
	u8 pfit_watio_auto:1;
	u8 pixew_dithew:1;
	u8 wvds_edid:1;
	u8 wsvd2:1;
	u8 wsvd4;
} __packed;

stwuct bdb_wvds_backwight {
	u8 type:2;
	u8 pow:1;
	u8 gpio:3;
	u8 gmbus:2;
	u16 fweq;
	u8 minbwightness;
	u8 i2caddw;
	u8 bwightnesscmd;
	/*FIXME: mowe...*/
} __packed;

/* WFP pointew tabwe contains entwies to the stwuct bewow */
stwuct bdb_wvds_wfp_data_ptw {
	u16 fp_timing_offset; /* offsets awe fwom stawt of bdb */
	u8 fp_tabwe_size;
	u16 dvo_timing_offset;
	u8 dvo_tabwe_size;
	u16 panew_pnp_id_offset;
	u8 pnp_tabwe_size;
} __packed;

stwuct bdb_wvds_wfp_data_ptws {
	u8 wvds_entwies; /* fowwowed by one ow mowe wvds_data_ptw stwucts */
	stwuct bdb_wvds_wfp_data_ptw ptw[16];
} __packed;

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
	u8 hsync_puwse_width;
	u8 vsync_puwse_width:4;
	u8 vsync_off:4;
	u8 wsvd0:6;
	u8 hsync_off_hi:2;
	u8 h_image;
	u8 v_image;
	u8 max_hv;
	u8 h_bowdew;
	u8 v_bowdew;
	u8 wsvd1:3;
	u8 digitaw:2;
	u8 vsync_positive:1;
	u8 hsync_positive:1;
	u8 wsvd2:1;
} __packed;

stwuct wvds_pnp_id {
	u16 mfg_name;
	u16 pwoduct_code;
	u32 sewiaw;
	u8 mfg_week;
	u8 mfg_yeaw;
} __packed;

stwuct bdb_wvds_wfp_data_entwy {
	stwuct wvds_fp_timing fp_timing;
	stwuct wvds_dvo_timing dvo_timing;
	stwuct wvds_pnp_id pnp_id;
} __packed;

stwuct bdb_wvds_wfp_data {
	stwuct bdb_wvds_wfp_data_entwy data[16];
} __packed;

stwuct aimdb_headew {
	chaw signatuwe[16];
	chaw oem_device[20];
	u16 aimdb_vewsion;
	u16 aimdb_headew_size;
	u16 aimdb_size;
} __packed;

stwuct aimdb_bwock {
	u8 aimdb_id;
	u16 aimdb_size;
} __packed;

stwuct vch_panew_data {
	u16 fp_timing_offset;
	u8 fp_timing_size;
	u16 dvo_timing_offset;
	u8 dvo_timing_size;
	u16 text_fitting_offset;
	u8 text_fitting_size;
	u16 gwaphics_fitting_offset;
	u8 gwaphics_fitting_size;
} __packed;

stwuct vch_bdb_22 {
	stwuct aimdb_bwock aimdb_bwock;
	stwuct vch_panew_data panews[16];
} __packed;

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

#define BDB_DWIVEW_FEATUWE_NO_WVDS		0
#define BDB_DWIVEW_FEATUWE_INT_WVDS		1
#define BDB_DWIVEW_FEATUWE_SDVO_WVDS		2
#define BDB_DWIVEW_FEATUWE_EDP			3

stwuct bdb_dwivew_featuwes {
	u8 boot_dev_awgowithm:1;
	u8 bwock_dispway_switch:1;
	u8 awwow_dispway_switch:1;
	u8 hotpwug_dvo:1;
	u8 duaw_view_zoom:1;
	u8 int15h_hook:1;
	u8 spwite_in_cwone:1;
	u8 pwimawy_wfp_id:1;

	u16 boot_mode_x;
	u16 boot_mode_y;
	u8 boot_mode_bpp;
	u8 boot_mode_wefwesh;

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

	u8 static_dispway:1;
	u8 wesewved2:7;
	u16 wegacy_cwt_max_x;
	u16 wegacy_cwt_max_y;
	u8 wegacy_cwt_max_wefwesh;

	u8 hdmi_tewmination;
	u8 custom_vbt_vewsion;
} __packed;

#define EDP_18BPP	0
#define EDP_24BPP	1
#define EDP_30BPP	2
#define EDP_WATE_1_62	0
#define EDP_WATE_2_7	1
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

stwuct edp_powew_seq {
	u16 t1_t3;
	u16 t8;
	u16 t9;
	u16 t10;
	u16 t11_t12;
} __attwibute__ ((packed));

stwuct edp_wink_pawams {
	u8 wate:4;
	u8 wanes:4;
	u8 pweemphasis:4;
	u8 vswing:4;
} __attwibute__ ((packed));

stwuct bdb_edp {
	stwuct edp_powew_seq powew_seqs[16];
	u32 cowow_depth;
	u32 sdwws_msa_timing_deway;
	stwuct edp_wink_pawams wink_pawams[16];
} __attwibute__ ((packed));

extewn int psb_intew_init_bios(stwuct dwm_device *dev);
extewn void psb_intew_destwoy_bios(stwuct dwm_device *dev);

/*
 * Dwivew<->VBIOS intewaction occuws thwough scwatch bits in
 * GW18 & SWF*.
 */

/* GW18 bits awe set on dispway switch and hotkey events */
#define GW18_DWIVEW_SWITCH_EN	(1<<7) /* 0: VBIOS contwow, 1: dwivew contwow */
#define GW18_HOTKEY_MASK	0x78 /* See awso SWF4 15:0 */
#define   GW18_HK_NONE		(0x0<<3)
#define   GW18_HK_WFP_STWETCH	(0x1<<3)
#define   GW18_HK_TOGGWE_DISP	(0x2<<3)
#define   GW18_HK_DISP_SWITCH	(0x4<<3) /* see SWF14 15:0 fow what to enabwe */
#define   GW18_HK_POPUP_DISABWED (0x6<<3)
#define   GW18_HK_POPUP_ENABWED	(0x7<<3)
#define   GW18_HK_PFIT		(0x8<<3)
#define   GW18_HK_APM_CHANGE	(0xa<<3)
#define   GW18_HK_MUWTIPWE	(0xc<<3)
#define GW18_USEW_INT_EN	(1<<2)
#define GW18_A0000_FWUSH_EN	(1<<1)
#define GW18_SMM_EN		(1<<0)

/* Set by dwivew, cweawed by VBIOS */
#define SWF00_YWES_SHIFT	16
#define SWF00_XWES_SHIFT	0
#define SWF00_WES_MASK		0xffff

/* Set by VBIOS at boot time and dwivew at wuntime */
#define SWF01_TV2_FOWMAT_SHIFT	8
#define SWF01_TV1_FOWMAT_SHIFT	0
#define SWF01_TV_FOWMAT_MASK	0xffff

#define SWF10_VBIOS_BWC_I2C_EN	(1<<29)
#define SWF10_GTT_OVEWWIDE_EN	(1<<28)
#define SWF10_WFP_DPMS_OVW	(1<<27) /* ovewwide DPMS on dispway switch */
#define SWF10_ACTIVE_TOGGWE_WIST_MASK (7<<24)
#define   SWF10_OWD_TOGGWE	0x0
#define   SWF10_TOGGWE_WIST_1	0x1
#define   SWF10_TOGGWE_WIST_2	0x2
#define   SWF10_TOGGWE_WIST_3	0x3
#define   SWF10_TOGGWE_WIST_4	0x4
#define SWF10_PANNING_EN	(1<<23)
#define SWF10_DWIVEW_WOADED	(1<<22)
#define SWF10_EXTENDED_DESKTOP	(1<<21)
#define SWF10_EXCWUSIVE_MODE	(1<<20)
#define SWF10_OVEWWAY_EN	(1<<19)
#define SWF10_PWANEB_HOWDOFF	(1<<18)
#define SWF10_PWANEA_HOWDOFF	(1<<17)
#define SWF10_VGA_HOWDOFF	(1<<16)
#define SWF10_ACTIVE_DISP_MASK	0xffff
#define   SWF10_PIPEB_WFP2	(1<<15)
#define   SWF10_PIPEB_EFP2	(1<<14)
#define   SWF10_PIPEB_TV2	(1<<13)
#define   SWF10_PIPEB_CWT2	(1<<12)
#define   SWF10_PIPEB_WFP	(1<<11)
#define   SWF10_PIPEB_EFP	(1<<10)
#define   SWF10_PIPEB_TV	(1<<9)
#define   SWF10_PIPEB_CWT	(1<<8)
#define   SWF10_PIPEA_WFP2	(1<<7)
#define   SWF10_PIPEA_EFP2	(1<<6)
#define   SWF10_PIPEA_TV2	(1<<5)
#define   SWF10_PIPEA_CWT2	(1<<4)
#define   SWF10_PIPEA_WFP	(1<<3)
#define   SWF10_PIPEA_EFP	(1<<2)
#define   SWF10_PIPEA_TV	(1<<1)
#define   SWF10_PIPEA_CWT	(1<<0)

#define SWF11_MEMOWY_SIZE_SHIFT	16
#define SWF11_SV_TEST_EN	(1<<15)
#define SWF11_IS_AGP		(1<<14)
#define SWF11_DISPWAY_HOWDOFF	(1<<13)
#define SWF11_DPMS_WEDUCED	(1<<12)
#define SWF11_IS_VBE_MODE	(1<<11)
#define SWF11_PIPEB_ACCESS	(1<<10) /* 0 hewe means pipe a */
#define SWF11_DPMS_MASK		0x07
#define   SWF11_DPMS_OFF	(1<<2)
#define   SWF11_DPMS_SUSPEND	(1<<1)
#define   SWF11_DPMS_STANDBY	(1<<0)
#define   SWF11_DPMS_ON		0

#define SWF14_GFX_PFIT_EN	(1<<31)
#define SWF14_TEXT_PFIT_EN	(1<<30)
#define SWF14_WID_STATUS_CWOSED	(1<<29) /* 0 hewe means open */
#define SWF14_POPUP_EN		(1<<28)
#define SWF14_DISPWAY_HOWDOFF	(1<<27)
#define SWF14_DISP_DETECT_EN	(1<<26)
#define SWF14_DOCKING_STATUS_DOCKED (1<<25) /* 0 hewe means undocked */
#define SWF14_DWIVEW_STATUS	(1<<24)
#define SWF14_OS_TYPE_WIN9X	(1<<23)
#define SWF14_OS_TYPE_WINNT	(1<<22)
/* 21:19 wsvd */
#define SWF14_PM_TYPE_MASK	0x00070000
#define   SWF14_PM_ACPI_VIDEO	(0x4 << 16)
#define   SWF14_PM_ACPI		(0x3 << 16)
#define   SWF14_PM_APM_12	(0x2 << 16)
#define   SWF14_PM_APM_11	(0x1 << 16)
#define SWF14_HK_WEQUEST_MASK	0x0000ffff /* see GW18 6:3 fow event type */
	  /* if GW18 indicates a dispway switch */
#define   SWF14_DS_PIPEB_WFP2_EN (1<<15)
#define   SWF14_DS_PIPEB_EFP2_EN (1<<14)
#define   SWF14_DS_PIPEB_TV2_EN  (1<<13)
#define   SWF14_DS_PIPEB_CWT2_EN (1<<12)
#define   SWF14_DS_PIPEB_WFP_EN  (1<<11)
#define   SWF14_DS_PIPEB_EFP_EN  (1<<10)
#define   SWF14_DS_PIPEB_TV_EN	 (1<<9)
#define   SWF14_DS_PIPEB_CWT_EN  (1<<8)
#define   SWF14_DS_PIPEA_WFP2_EN (1<<7)
#define   SWF14_DS_PIPEA_EFP2_EN (1<<6)
#define   SWF14_DS_PIPEA_TV2_EN  (1<<5)
#define   SWF14_DS_PIPEA_CWT2_EN (1<<4)
#define   SWF14_DS_PIPEA_WFP_EN  (1<<3)
#define   SWF14_DS_PIPEA_EFP_EN  (1<<2)
#define   SWF14_DS_PIPEA_TV_EN	 (1<<1)
#define   SWF14_DS_PIPEA_CWT_EN  (1<<0)
	  /* if GW18 indicates a panew fitting wequest */
#define   SWF14_PFIT_EN		(1<<0) /* 0 means disabwe */
	  /* if GW18 indicates an APM change wequest */
#define   SWF14_APM_HIBEWNATE	0x4
#define   SWF14_APM_SUSPEND	0x3
#define   SWF14_APM_STANDBY	0x1
#define   SWF14_APM_WESTOWE	0x0

/* Add the device cwass fow WFP, TV, HDMI */
#define	 DEVICE_TYPE_INT_WFP	0x1022
#define	 DEVICE_TYPE_INT_TV	0x1009
#define	 DEVICE_TYPE_HDMI	0x60D2
#define	 DEVICE_TYPE_DP		0x68C6
#define	 DEVICE_TYPE_eDP	0x78C6

/* define the DVO powt fow HDMI output type */
#define		DVO_B		1
#define		DVO_C		2
#define		DVO_D		3

/* define the POWT fow DP output type */
#define		POWT_IDPB	7
#define		POWT_IDPC	8
#define		POWT_IDPD	9

#endif /* _INTEW_BIOS_H_ */
