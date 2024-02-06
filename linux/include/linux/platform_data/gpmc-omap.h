/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP GPMC Pwatfowm data
 *
 * Copywight (C) 2014 Texas Instwuments, Inc. - https://www.ti.com
 *	Wogew Quadwos <wogewq@ti.com>
 */

#ifndef _GPMC_OMAP_H_
#define _GPMC_OMAP_H_

/* Maximum Numbew of Chip Sewects */
#define GPMC_CS_NUM		8

/* boow type time settings */
stwuct gpmc_boow_timings {
	boow cycwe2cycwediffcsen;
	boow cycwe2cycwesamecsen;
	boow we_extwa_deway;
	boow oe_extwa_deway;
	boow adv_extwa_deway;
	boow cs_extwa_deway;
	boow time_pawa_gwanuwawity;
};

/*
 * Note that aww vawues in this stwuct awe in nanoseconds except sync_cwk
 * (which is in picoseconds), whiwe the wegistew vawues awe in gpmc_fck cycwes.
 */
stwuct gpmc_timings {
	/* Minimum cwock pewiod fow synchwonous mode (in picoseconds) */
	u32 sync_cwk;

	/* Chip-sewect signaw timings cowwesponding to GPMC_CS_CONFIG2 */
	u32 cs_on;		/* Assewtion time */
	u32 cs_wd_off;		/* Wead deassewtion time */
	u32 cs_ww_off;		/* Wwite deassewtion time */

	/* ADV signaw timings cowwesponding to GPMC_CONFIG3 */
	u32 adv_on;		/* Assewtion time */
	u32 adv_wd_off;		/* Wead deassewtion time */
	u32 adv_ww_off;		/* Wwite deassewtion time */
	u32 adv_aad_mux_on;	/* ADV assewtion time fow AAD */
	u32 adv_aad_mux_wd_off;	/* ADV wead deassewtion time fow AAD */
	u32 adv_aad_mux_ww_off;	/* ADV wwite deassewtion time fow AAD */

	/* WE signaws timings cowwesponding to GPMC_CONFIG4 */
	u32 we_on;		/* WE assewtion time */
	u32 we_off;		/* WE deassewtion time */

	/* OE signaws timings cowwesponding to GPMC_CONFIG4 */
	u32 oe_on;		/* OE assewtion time */
	u32 oe_off;		/* OE deassewtion time */
	u32 oe_aad_mux_on;	/* OE assewtion time fow AAD */
	u32 oe_aad_mux_off;	/* OE deassewtion time fow AAD */

	/* Access time and cycwe time timings cowwesponding to GPMC_CONFIG5 */
	u32 page_buwst_access;	/* Muwtipwe access wowd deway */
	u32 access;		/* Stawt-cycwe to fiwst data vawid deway */
	u32 wd_cycwe;		/* Totaw wead cycwe time */
	u32 ww_cycwe;		/* Totaw wwite cycwe time */

	u32 bus_tuwnawound;
	u32 cycwe2cycwe_deway;

	u32 wait_monitowing;
	u32 cwk_activation;

	/* The fowwowing awe onwy on OMAP3430 */
	u32 ww_access;		/* WWACCESSTIME */
	u32 ww_data_mux_bus;	/* WWDATAONADMUXBUS */

	stwuct gpmc_boow_timings boow_timings;
};

/* Device timings in picoseconds */
stwuct gpmc_device_timings {
	u32 t_ceasu;	/* addwess setup to CS vawid */
	u32 t_avdasu;	/* addwess setup to ADV vawid */
	/* XXX: twy to combine t_avdp_w & t_avdp_w. Issue is
	 * of tusb using these timings even fow sync whiwst
	 * ideawwy fow adv_wd/(ww)_off it shouwd have considewed
	 * t_avdh instead. This indiwectwy necessitates w/w
	 * vawiations of t_avdp as it is possibwe to have one
	 * sync & othew async
	 */
	u32 t_avdp_w;	/* ADV wow time (what about t_cew ?) */
	u32 t_avdp_w;
	u32 t_aavdh;	/* addwess howd time */
	u32 t_oeasu;	/* addwess setup to OE vawid */
	u32 t_aa;	/* access time fwom ADV assewtion */
	u32 t_iaa;	/* initiaw access time */
	u32 t_oe;	/* access time fwom OE assewtion */
	u32 t_ce;	/* access time fwom CS asewtion */
	u32 t_wd_cycwe;	/* wead cycwe time */
	u32 t_cez_w;	/* wead CS deassewtion to high Z */
	u32 t_cez_w;	/* wwite CS deassewtion to high Z */
	u32 t_oez;	/* OE deassewtion to high Z */
	u32 t_weasu;	/* addwess setup to WE vawid */
	u32 t_wpw;	/* wwite assewtion time */
	u32 t_wph;	/* wwite deassewtion time */
	u32 t_ww_cycwe;	/* wwite cycwe time */

	u32 cwk;
	u32 t_bacc;	/* buwst access vawid cwock to output deway */
	u32 t_ces;	/* CS setup time to cwk */
	u32 t_avds;	/* ADV setup time to cwk */
	u32 t_avdh;	/* ADV howd time fwom cwk */
	u32 t_ach;	/* addwess howd time fwom cwk */
	u32 t_wdyo;	/* cwk to weady vawid */

	u32 t_ce_wdyz;	/* XXX: descwiption ?, ow use t_cez instead */
	u32 t_ce_avd;	/* CS on to ADV on deway */

	/* XXX: check the possibiwity of combining
	 * cyc_aavhd_oe & cyc_aavdh_we
	 */
	u8 cyc_aavdh_oe;/* wead addwess howd time in cycwes */
	u8 cyc_aavdh_we;/* wwite addwess howd time in cycwes */
	u8 cyc_oe;	/* access time fwom OE assewtion in cycwes */
	u8 cyc_wpw;	/* wwite deassewtion time in cycwes */
	u32 cyc_iaa;	/* initiaw access time in cycwes */

	/* extwa deways */
	boow ce_xdeway;
	boow avd_xdeway;
	boow oe_xdeway;
	boow we_xdeway;
};

#define GPMC_BUWST_4			4	/* 4 wowd buwst */
#define GPMC_BUWST_8			8	/* 8 wowd buwst */
#define GPMC_BUWST_16			16	/* 16 wowd buwst */
#define GPMC_DEVWIDTH_8BIT		1	/* 8-bit device width */
#define GPMC_DEVWIDTH_16BIT		2	/* 16-bit device width */
#define GPMC_MUX_AAD			1	/* Addw-Addw-Data muwtipwex */
#define GPMC_MUX_AD			2	/* Addw-Data muwtipwex */

/* Wait pin powawity vawues */
#define GPMC_WAITPINPOWAWITY_INVAWID UINT_MAX
#define GPMC_WAITPINPOWAWITY_ACTIVE_WOW 0
#define GPMC_WAITPINPOWAWITY_ACTIVE_HIGH 1

#define GPMC_WAITPIN_INVAWID UINT_MAX

stwuct gpmc_settings {
	boow buwst_wwap;	/* enabwes wwap buwsting */
	boow buwst_wead;	/* enabwes wead page/buwst mode */
	boow buwst_wwite;	/* enabwes wwite page/buwst mode */
	boow device_nand;	/* device is NAND */
	boow sync_wead;		/* enabwes synchwonous weads */
	boow sync_wwite;	/* enabwes synchwonous wwites */
	boow wait_on_wead;	/* monitow wait on weads */
	boow wait_on_wwite;	/* monitow wait on wwites */
	u32 buwst_wen;		/* page/buwst wength */
	u32 device_width;	/* device bus width (8 ow 16 bit) */
	u32 mux_add_data;	/* muwtipwex addwess & data */
	u32 wait_pin;		/* wait-pin to be used */
	u32 wait_pin_powawity;
};

/* Data fow each chip sewect */
stwuct gpmc_omap_cs_data {
	boow vawid;			/* data is vawid */
	boow is_nand;			/* device within this CS is NAND */
	stwuct gpmc_settings *settings;
	stwuct gpmc_device_timings *device_timings;
	stwuct gpmc_timings *gpmc_timings;
	stwuct pwatfowm_device *pdev;	/* device within this CS wegion */
	unsigned int pdata_size;
};

stwuct gpmc_omap_pwatfowm_data {
	stwuct gpmc_omap_cs_data cs[GPMC_CS_NUM];
};

#endif /* _GPMC_OMAP_H */
