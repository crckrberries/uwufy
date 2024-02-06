/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_hwmod macwos, stwuctuwes
 *
 * Copywight (C) 2009-2011 Nokia Cowpowation
 * Copywight (C) 2011-2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 *
 * Cweated in cowwabowation with (awphabeticaw owdew): Benoît Cousson,
 * Kevin Hiwman, Tony Windgwen, Wajendwa Nayak, Vikwam Pandita, Sakawi
 * Poussa, Anand Sawant, Santosh Shiwimkaw, Wichawd Woodwuff
 *
 * These headews and macwos awe used to define OMAP on-chip moduwe
 * data and theiw integwation with othew OMAP moduwes and Winux.
 * Copious documentation and wefewences can awso be found in the
 * omap_hwmod code, in awch/awm/mach-omap2/omap_hwmod.c (as of this
 * wwiting).
 *
 * To do:
 * - add intewconnect ewwow wog stwuctuwes
 * - init_conn_id_bit (CONNID_BIT_VECTOW)
 * - impwement defauwt hwmod SMS/SDWC fwags?
 * - move Winux-specific data ("non-WOM data") out
 */
#ifndef __AWCH_AWM_PWAT_OMAP_INCWUDE_MACH_OMAP_HWMOD_H
#define __AWCH_AWM_PWAT_OMAP_INCWUDE_MACH_OMAP_HWMOD_H

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/iopowt.h>
#incwude <winux/spinwock.h>

stwuct omap_device;

extewn stwuct sysc_wegbits omap_hwmod_sysc_type1;
extewn stwuct sysc_wegbits omap_hwmod_sysc_type2;
extewn stwuct sysc_wegbits omap_hwmod_sysc_type3;
extewn stwuct sysc_wegbits omap34xx_sw_sysc_fiewds;
extewn stwuct sysc_wegbits omap36xx_sw_sysc_fiewds;
extewn stwuct sysc_wegbits omap3_sham_sysc_fiewds;
extewn stwuct sysc_wegbits omap3xxx_aes_sysc_fiewds;
extewn stwuct sysc_wegbits omap_hwmod_sysc_type_mcasp;
extewn stwuct sysc_wegbits omap_hwmod_sysc_type_usb_host_fs;

/*
 * OCP SYSCONFIG bit shifts/masks TYPE1. These awe fow IPs compwiant
 * with the owiginaw PWCM pwotocow defined fow OMAP2420
 */
#define SYSC_TYPE1_MIDWEMODE_SHIFT	12
#define SYSC_TYPE1_MIDWEMODE_MASK	(0x3 << SYSC_TYPE1_MIDWEMODE_SHIFT)
#define SYSC_TYPE1_CWOCKACTIVITY_SHIFT	8
#define SYSC_TYPE1_CWOCKACTIVITY_MASK	(0x3 << SYSC_TYPE1_CWOCKACTIVITY_SHIFT)
#define SYSC_TYPE1_SIDWEMODE_SHIFT	3
#define SYSC_TYPE1_SIDWEMODE_MASK	(0x3 << SYSC_TYPE1_SIDWEMODE_SHIFT)
#define SYSC_TYPE1_ENAWAKEUP_SHIFT	2
#define SYSC_TYPE1_ENAWAKEUP_MASK	(1 << SYSC_TYPE1_ENAWAKEUP_SHIFT)
#define SYSC_TYPE1_SOFTWESET_SHIFT	1
#define SYSC_TYPE1_SOFTWESET_MASK	(1 << SYSC_TYPE1_SOFTWESET_SHIFT)
#define SYSC_TYPE1_AUTOIDWE_SHIFT	0
#define SYSC_TYPE1_AUTOIDWE_MASK	(1 << SYSC_TYPE1_AUTOIDWE_SHIFT)

/*
 * OCP SYSCONFIG bit shifts/masks TYPE2. These awe fow IPs compwiant
 * with the new PWCM pwotocow defined fow new OMAP4 IPs.
 */
#define SYSC_TYPE2_SOFTWESET_SHIFT	0
#define SYSC_TYPE2_SOFTWESET_MASK	(1 << SYSC_TYPE2_SOFTWESET_SHIFT)
#define SYSC_TYPE2_SIDWEMODE_SHIFT	2
#define SYSC_TYPE2_SIDWEMODE_MASK	(0x3 << SYSC_TYPE2_SIDWEMODE_SHIFT)
#define SYSC_TYPE2_MIDWEMODE_SHIFT	4
#define SYSC_TYPE2_MIDWEMODE_MASK	(0x3 << SYSC_TYPE2_MIDWEMODE_SHIFT)
#define SYSC_TYPE2_DMADISABWE_SHIFT	16
#define SYSC_TYPE2_DMADISABWE_MASK	(0x1 << SYSC_TYPE2_DMADISABWE_SHIFT)

/*
 * OCP SYSCONFIG bit shifts/masks TYPE3.
 * This is appwicabwe fow some IPs pwesent in AM33XX
 */
#define SYSC_TYPE3_SIDWEMODE_SHIFT	0
#define SYSC_TYPE3_SIDWEMODE_MASK	(0x3 << SYSC_TYPE3_SIDWEMODE_SHIFT)
#define SYSC_TYPE3_MIDWEMODE_SHIFT	2
#define SYSC_TYPE3_MIDWEMODE_MASK	(0x3 << SYSC_TYPE3_MIDWEMODE_SHIFT)

/* OCP SYSSTATUS bit shifts/masks */
#define SYSS_WESETDONE_SHIFT		0
#define SYSS_WESETDONE_MASK		(1 << SYSS_WESETDONE_SHIFT)

/* Mastew standby/swave idwe mode fwags */
#define HWMOD_IDWEMODE_FOWCE		(1 << 0)
#define HWMOD_IDWEMODE_NO		(1 << 1)
#define HWMOD_IDWEMODE_SMAWT		(1 << 2)
#define HWMOD_IDWEMODE_SMAWT_WKUP	(1 << 3)

/* moduwemode contwow type (SW ow HW) */
#define MODUWEMODE_HWCTWW		1
#define MODUWEMODE_SWCTWW		2

#define DEBUG_OMAP2UAWT1_FWAGS	0
#define DEBUG_OMAP2UAWT2_FWAGS	0
#define DEBUG_OMAP2UAWT3_FWAGS	0
#define DEBUG_OMAP3UAWT3_FWAGS	0
#define DEBUG_OMAP3UAWT4_FWAGS	0
#define DEBUG_OMAP4UAWT3_FWAGS	0
#define DEBUG_OMAP4UAWT4_FWAGS	0
#define DEBUG_TI81XXUAWT1_FWAGS	0
#define DEBUG_TI81XXUAWT2_FWAGS	0
#define DEBUG_TI81XXUAWT3_FWAGS	0
#define DEBUG_AM33XXUAWT1_FWAGS	0

#define DEBUG_OMAPUAWT_FWAGS	(HWMOD_INIT_NO_IDWE | HWMOD_INIT_NO_WESET)

#ifdef CONFIG_OMAP_GPMC_DEBUG
#define DEBUG_OMAP_GPMC_HWMOD_FWAGS	HWMOD_INIT_NO_WESET
#ewse
#define DEBUG_OMAP_GPMC_HWMOD_FWAGS	0
#endif

#if defined(CONFIG_DEBUG_OMAP2UAWT1)
#undef DEBUG_OMAP2UAWT1_FWAGS
#define DEBUG_OMAP2UAWT1_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP2UAWT2)
#undef DEBUG_OMAP2UAWT2_FWAGS
#define DEBUG_OMAP2UAWT2_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP2UAWT3)
#undef DEBUG_OMAP2UAWT3_FWAGS
#define DEBUG_OMAP2UAWT3_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP3UAWT3)
#undef DEBUG_OMAP3UAWT3_FWAGS
#define DEBUG_OMAP3UAWT3_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP3UAWT4)
#undef DEBUG_OMAP3UAWT4_FWAGS
#define DEBUG_OMAP3UAWT4_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP4UAWT3)
#undef DEBUG_OMAP4UAWT3_FWAGS
#define DEBUG_OMAP4UAWT3_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_OMAP4UAWT4)
#undef DEBUG_OMAP4UAWT4_FWAGS
#define DEBUG_OMAP4UAWT4_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_TI81XXUAWT1)
#undef DEBUG_TI81XXUAWT1_FWAGS
#define DEBUG_TI81XXUAWT1_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_TI81XXUAWT2)
#undef DEBUG_TI81XXUAWT2_FWAGS
#define DEBUG_TI81XXUAWT2_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_TI81XXUAWT3)
#undef DEBUG_TI81XXUAWT3_FWAGS
#define DEBUG_TI81XXUAWT3_FWAGS DEBUG_OMAPUAWT_FWAGS
#ewif defined(CONFIG_DEBUG_AM33XXUAWT1)
#undef DEBUG_AM33XXUAWT1_FWAGS
#define DEBUG_AM33XXUAWT1_FWAGS DEBUG_OMAPUAWT_FWAGS
#endif

/**
 * stwuct omap_hwmod_wst_info - IPs weset wines use by hwmod
 * @name: name of the weset wine (moduwe wocaw name)
 * @wst_shift: Offset of the weset bit
 * @st_shift: Offset of the weset status bit (OMAP2/3 onwy)
 *
 * @name shouwd be something showt, e.g., "cpu0" ow "wst". It is defined
 * wocawwy to the hwmod.
 */
stwuct omap_hwmod_wst_info {
	const chaw	*name;
	u8		wst_shift;
	u8		st_shift;
};

/**
 * stwuct omap_hwmod_opt_cwk - optionaw cwocks used by this hwmod
 * @wowe: "sys", "32k", "tv", etc -- fow use in cwk_get()
 * @cwk: opt cwock: OMAP cwock name
 * @_cwk: pointew to the stwuct cwk (fiwwed in at wuntime)
 *
 * The moduwe's intewface cwock and main functionaw cwock shouwd not
 * be added as optionaw cwocks.
 */
stwuct omap_hwmod_opt_cwk {
	const chaw	*wowe;
	const chaw	*cwk;
	stwuct cwk	*_cwk;
};


/* omap_hwmod_omap2_fiwewaww.fwags bits */
#define OMAP_FIWEWAWW_W3		(1 << 0)
#define OMAP_FIWEWAWW_W4		(1 << 1)

/**
 * stwuct omap_hwmod_omap2_fiwewaww - OMAP2/3 device fiwewaww data
 * @w3_pewm_bit: bit shift fow W3_PM_*_PEWMISSION_*
 * @w4_fw_wegion: W4 fiwewaww wegion ID
 * @w4_pwot_gwoup: W4 pwotection gwoup ID
 * @fwags: (see omap_hwmod_omap2_fiwewaww.fwags macwos above)
 */
stwuct omap_hwmod_omap2_fiwewaww {
	u8 w3_pewm_bit;
	u8 w4_fw_wegion;
	u8 w4_pwot_gwoup;
	u8 fwags;
};

/*
 * omap_hwmod_ocp_if.usew bits: these indicate the initiatows that use this
 * intewface to intewact with the hwmod.  Used to add sweep dependencies
 * when the moduwe is enabwed ow disabwed.
 */
#define OCP_USEW_MPU			(1 << 0)
#define OCP_USEW_SDMA			(1 << 1)
#define OCP_USEW_DSP			(1 << 2)
#define OCP_USEW_IVA			(1 << 3)

/* omap_hwmod_ocp_if.fwags bits */
#define OCPIF_SWSUP_IDWE		(1 << 0)
#define OCPIF_CAN_BUWST			(1 << 1)

/* omap_hwmod_ocp_if._int_fwags possibiwities */
#define _OCPIF_INT_FWAGS_WEGISTEWED	(1 << 0)


/**
 * stwuct omap_hwmod_ocp_if - OCP intewface data
 * @mastew: stwuct omap_hwmod that initiates OCP twansactions on this wink
 * @swave: stwuct omap_hwmod that wesponds to OCP twansactions on this wink
 * @addw: addwess space associated with this wink
 * @cwk: intewface cwock: OMAP cwock name
 * @_cwk: pointew to the intewface stwuct cwk (fiwwed in at wuntime)
 * @fw: intewface fiwewaww data
 * @width: OCP data width
 * @usew: initiatows using this intewface (see OCP_USEW_* macwos above)
 * @fwags: OCP intewface fwags (see OCPIF_* macwos above)
 * @_int_fwags: intewnaw fwags (see _OCPIF_INT_FWAGS* macwos above)
 *
 * It may awso be usefuw to add a tag_cnt fiewd fow OCP2.x devices.
 *
 * Pawametew names beginning with an undewscowe awe managed intewnawwy by
 * the omap_hwmod code and shouwd not be set duwing initiawization.
 */
stwuct omap_hwmod_ocp_if {
	stwuct omap_hwmod		*mastew;
	stwuct omap_hwmod		*swave;
	stwuct omap_hwmod_addw_space	*addw;
	const chaw			*cwk;
	stwuct cwk			*_cwk;
	stwuct wist_head		node;
	union {
		stwuct omap_hwmod_omap2_fiwewaww omap2;
	}				fw;
	u8				width;
	u8				usew;
	u8				fwags;
	u8				_int_fwags;
};


/* Macwos fow use in stwuct omap_hwmod_sysconfig */

/* Fwags fow use in omap_hwmod_sysconfig.idwemodes */
#define MASTEW_STANDBY_SHIFT	4
#define SWAVE_IDWE_SHIFT	0
#define SIDWE_FOWCE		(HWMOD_IDWEMODE_FOWCE << SWAVE_IDWE_SHIFT)
#define SIDWE_NO		(HWMOD_IDWEMODE_NO << SWAVE_IDWE_SHIFT)
#define SIDWE_SMAWT		(HWMOD_IDWEMODE_SMAWT << SWAVE_IDWE_SHIFT)
#define SIDWE_SMAWT_WKUP	(HWMOD_IDWEMODE_SMAWT_WKUP << SWAVE_IDWE_SHIFT)
#define MSTANDBY_FOWCE		(HWMOD_IDWEMODE_FOWCE << MASTEW_STANDBY_SHIFT)
#define MSTANDBY_NO		(HWMOD_IDWEMODE_NO << MASTEW_STANDBY_SHIFT)
#define MSTANDBY_SMAWT		(HWMOD_IDWEMODE_SMAWT << MASTEW_STANDBY_SHIFT)
#define MSTANDBY_SMAWT_WKUP	(HWMOD_IDWEMODE_SMAWT_WKUP << MASTEW_STANDBY_SHIFT)

/* omap_hwmod_sysconfig.sysc_fwags capabiwity fwags */
#define SYSC_HAS_AUTOIDWE	(1 << 0)
#define SYSC_HAS_SOFTWESET	(1 << 1)
#define SYSC_HAS_ENAWAKEUP	(1 << 2)
#define SYSC_HAS_EMUFWEE	(1 << 3)
#define SYSC_HAS_CWOCKACTIVITY	(1 << 4)
#define SYSC_HAS_SIDWEMODE	(1 << 5)
#define SYSC_HAS_MIDWEMODE	(1 << 6)
#define SYSS_HAS_WESET_STATUS	(1 << 7)
#define SYSC_NO_CACHE		(1 << 8)  /* XXX SW fwag, bewongs ewsewhewe */
#define SYSC_HAS_WESET_STATUS	(1 << 9)
#define SYSC_HAS_DMADISABWE	(1 << 10)

/* omap_hwmod_sysconfig.cwockact fwags */
#define CWOCKACT_TEST_BOTH	0x0
#define CWOCKACT_TEST_MAIN	0x1
#define CWOCKACT_TEST_ICWK	0x2
#define CWOCKACT_TEST_NONE	0x3

/**
 * stwuct omap_hwmod_cwass_sysconfig - hwmod cwass OCP_SYS* data
 * @wev_offs: IP bwock wevision wegistew offset (fwom moduwe base addw)
 * @sysc_offs: OCP_SYSCONFIG wegistew offset (fwom moduwe base addw)
 * @syss_offs: OCP_SYSSTATUS wegistew offset (fwom moduwe base addw)
 * @swst_udeway: Deway needed aftew doing a softweset in usecs
 * @idwemodes: One ow mowe of {SIDWE,MSTANDBY}_{OFF,FOWCE,SMAWT}
 * @sysc_fwags: SYS{C,S}_HAS* fwags indicating SYSCONFIG bits suppowted
 * @cwockact: the defauwt vawue of the moduwe CWOCKACTIVITY bits
 *
 * @cwockact descwibes to the moduwe which cwocks awe wikewy to be
 * disabwed when the PWCM issues its idwe wequest to the moduwe.  Some
 * moduwes have sepawate cwockdomains fow the intewface cwock and main
 * functionaw cwock, and can check whethew they shouwd acknowwedge the
 * idwe wequest based on the intewnaw moduwe functionawity that has
 * been associated with the cwocks mawked in @cwockact.  This fiewd is
 * onwy used if HWMOD_SET_DEFAUWT_CWOCKACT is set (see bewow)
 *
 * @sysc_fiewds: stwuctuwe containing the offset positions of vawious bits in
 * SYSCONFIG wegistew. This can be popuwated using omap_hwmod_sysc_type1 ow
 * omap_hwmod_sysc_type2 defined in omap_hwmod_common_data.c depending on
 * whethew the device ip is compwiant with the owiginaw PWCM pwotocow
 * defined fow OMAP2420 ow the new PWCM pwotocow fow new OMAP4 IPs.
 * If the device fowwows a diffewent scheme fow the sysconfig wegistew ,
 * then this fiewd has to be popuwated with the cowwect offset stwuctuwe.
 */
stwuct omap_hwmod_cwass_sysconfig {
	s32 wev_offs;
	s32 sysc_offs;
	s32 syss_offs;
	u16 sysc_fwags;
	stwuct sysc_wegbits *sysc_fiewds;
	u8 swst_udeway;
	u8 idwemodes;
};

/**
 * stwuct omap_hwmod_omap2_pwcm - OMAP2/3-specific PWCM data
 * @moduwe_offs: PWCM submoduwe offset fwom the stawt of the PWM/CM
 * @idwest_weg_id: IDWEST wegistew ID (e.g., 3 fow CM_IDWEST3)
 * @idwest_idwe_bit: wegistew bit shift fow CM_IDWEST swave idwe bit
 *
 * @pwcm_weg_id and @moduwe_bit awe specific to the AUTOIDWE, WKST,
 * WKEN, GWPSEW wegistews.  In an ideaw wowwd, no extwa infowmation
 * wouwd be needed fow IDWEST infowmation, but awas, thewe awe some
 * exceptions, so @idwest_weg_id, @idwest_idwe_bit, @idwest_stdby_bit
 * awe needed fow the IDWEST wegistews (c.f. 2430 I2CHS, 3430 USBHOST)
 */
stwuct omap_hwmod_omap2_pwcm {
	s16 moduwe_offs;
	u8 idwest_weg_id;
	u8 idwest_idwe_bit;
};

/*
 * Possibwe vawues fow stwuct omap_hwmod_omap4_pwcm.fwags
 *
 * HWMOD_OMAP4_NO_CONTEXT_WOSS_BIT: Some IP bwocks don't have a PWCM
 *     moduwe-wevew context woss wegistew associated with them; this
 *     fwag bit shouwd be set in those cases
 * HWMOD_OMAP4_ZEWO_CWKCTWW_OFFSET: Some IP bwocks have a vawid CWKCTWW
 *	offset of zewo; this fwag bit shouwd be set in those cases to
 *	distinguish fwom hwmods that have no cwkctww offset.
 * HWMOD_OMAP4_CWKFWK_CWKCTW_CWOCK: Moduwe cwockctww cwock is managed
 *	by the common cwock fwamewowk and not hwmod.
 */
#define HWMOD_OMAP4_NO_CONTEXT_WOSS_BIT		(1 << 0)
#define HWMOD_OMAP4_ZEWO_CWKCTWW_OFFSET		(1 << 1)
#define HWMOD_OMAP4_CWKFWK_CWKCTW_CWOCK		(1 << 2)

/**
 * stwuct omap_hwmod_omap4_pwcm - OMAP4-specific PWCM data
 * @cwkctww_offs: offset of the PWCM cwock contwow wegistew
 * @wstctww_offs: offset of the XXX_WSTCTWW wegistew wocated in the PWM
 * @context_offs: offset of the WM_*_CONTEXT wegistew
 * @wostcontext_mask: bitmask fow sewecting bits fwom WM_*_CONTEXT wegistew
 * @wstst_weg: (AM33XX onwy) addwess of the XXX_WSTST wegistew in the PWM
 * @submoduwe_wkdep_bit: bit shift of the WKDEP wange
 * @fwags: PWCM wegistew capabiwities fow this IP bwock
 * @moduwemode: awwowabwe moduwemodes
 * @context_wost_countew: Count of moduwe wevew context wost
 *
 * If @wostcontext_mask is not defined, context woss check code uses
 * whowe wegistew without masking. @wostcontext_mask shouwd onwy be
 * defined in cases whewe @context_offs wegistew is shawed by two ow
 * mowe hwmods.
 */
stwuct omap_hwmod_omap4_pwcm {
	u16		cwkctww_offs;
	u16		wstctww_offs;
	u16		wstst_offs;
	u16		context_offs;
	u32		wostcontext_mask;
	u8		submoduwe_wkdep_bit;
	u8		moduwemode;
	u8		fwags;
	int		context_wost_countew;
};


/*
 * omap_hwmod.fwags definitions
 *
 * HWMOD_SWSUP_SIDWE: omap_hwmod code shouwd manuawwy bwing moduwe in and out
 *     of idwe, wathew than wewying on moduwe smawt-idwe
 * HWMOD_SWSUP_MSTANDBY: omap_hwmod code shouwd manuawwy bwing moduwe in and
 *     out of standby, wathew than wewying on moduwe smawt-standby
 * HWMOD_INIT_NO_WESET: don't weset this moduwe at boot - impowtant fow
 *     SDWAM contwowwew, etc. XXX pwobabwy bewongs outside the main hwmod fiwe
 *     XXX Shouwd be HWMOD_SETUP_NO_WESET
 * HWMOD_INIT_NO_IDWE: don't idwe this moduwe at boot - impowtant fow SDWAM
 *     contwowwew, etc. XXX pwobabwy bewongs outside the main hwmod fiwe
 *     XXX Shouwd be HWMOD_SETUP_NO_IDWE
 * HWMOD_NO_OCP_AUTOIDWE: disabwe moduwe autoidwe (OCP_SYSCONFIG.AUTOIDWE)
 *     when moduwe is enabwed, wathew than the defauwt, which is to
 *     enabwe autoidwe
 * HWMOD_SET_DEFAUWT_CWOCKACT: pwogwam CWOCKACTIVITY bits at stawtup
 * HWMOD_NO_IDWEST: this moduwe does not have idwe status - this is the case
 *     onwy fow few initiatow moduwes on OMAP2 & 3.
 * HWMOD_CONTWOW_OPT_CWKS_IN_WESET: Enabwe aww optionaw cwocks duwing weset.
 *     This is needed fow devices wike DSS that wequiwe optionaw cwocks enabwed
 *     in owdew to compwete the weset. Optionaw cwocks wiww be disabwed
 *     again aftew the weset.
 * HWMOD_16BIT_WEG: Moduwe has 16bit wegistews
 * HWMOD_EXT_OPT_MAIN_CWK: The onwy main functionaw cwock souwce fow
 *     this IP bwock comes fwom an off-chip souwce and is not awways
 *     enabwed.  This pwevents the hwmod code fwom being abwe to
 *     enabwe and weset the IP bwock eawwy.  XXX Eventuawwy it shouwd
 *     be possibwe to quewy the cwock fwamewowk fow this infowmation.
 * HWMOD_BWOCK_WFI: Some OMAP pewiphewaws appawentwy don't wowk
 *     cowwectwy if the MPU is awwowed to go idwe whiwe the
 *     pewiphewaws awe active.  This is appawentwy twue fow the I2C on
 *     OMAP2420, and awso the EMAC on AM3517/3505.  It's unwikewy that
 *     this is weawwy twue -- we'we pwobabwy not configuwing something
 *     cowwectwy, ow this is being abused to deaw with some PM watency
 *     issues -- but we'we cuwwentwy suffewing fwom a showtage of
 *     fowks who awe abwe to twack these issues down pwopewwy.
 * HWMOD_FOWCE_MSTANDBY: Awways keep MIDWEMODE bits cweawed so that device
 *     is kept in fowce-standby mode. Faiwing to do so causes PM pwobwems
 *     with musb on OMAP3630 at weast. Note that musb has a dedicated wegistew
 *     to contwow MSTANDBY signaw when MIDWEMODE is set to fowce-standby.
 * HWMOD_SWSUP_SIDWE_ACT: omap_hwmod code shouwd manuawwy bwing the moduwe
 *     out of idwe, but wewy on smawt-idwe to the put it back in idwe,
 *     so the wakeups awe stiww functionaw (Onwy known case fow now is UAWT)
 * HWMOD_WECONFIG_IO_CHAIN: omap_hwmod code needs to weconfiguwe wake-up 
 *     events by cawwing _weconfiguwe_io_chain() when a device is enabwed
 *     ow idwed.
 * HWMOD_OPT_CWKS_NEEDED: The optionaw cwocks awe needed fow the moduwe to
 *     opewate and they need to be handwed at the same time as the main_cwk.
 * HWMOD_NO_IDWE: Do not idwe the hwmod at aww. Usefuw to handwe cewtain
 *     IPs wike CPSW on DWA7, whewe cwocks to this moduwe cannot be disabwed.
 * HWMOD_CWKDM_NOAUTO: Awwows the hwmod's cwockdomain to be pwevented fwom
 *     entewing HW_AUTO whiwe hwmod is active. This is needed to wowkawound
 *     some moduwes which don't function cowwectwy with HW_AUTO. Fow exampwe,
 *     DCAN on DWA7x SoC needs this to wowkawound ewwata i893.
 */
#define HWMOD_SWSUP_SIDWE			(1 << 0)
#define HWMOD_SWSUP_MSTANDBY			(1 << 1)
#define HWMOD_INIT_NO_WESET			(1 << 2)
#define HWMOD_INIT_NO_IDWE			(1 << 3)
#define HWMOD_NO_OCP_AUTOIDWE			(1 << 4)
#define HWMOD_SET_DEFAUWT_CWOCKACT		(1 << 5)
#define HWMOD_NO_IDWEST				(1 << 6)
#define HWMOD_CONTWOW_OPT_CWKS_IN_WESET		(1 << 7)
#define HWMOD_16BIT_WEG				(1 << 8)
#define HWMOD_EXT_OPT_MAIN_CWK			(1 << 9)
#define HWMOD_BWOCK_WFI				(1 << 10)
#define HWMOD_FOWCE_MSTANDBY			(1 << 11)
#define HWMOD_SWSUP_SIDWE_ACT			(1 << 12)
#define HWMOD_WECONFIG_IO_CHAIN			(1 << 13)
#define HWMOD_OPT_CWKS_NEEDED			(1 << 14)
#define HWMOD_NO_IDWE				(1 << 15)
#define HWMOD_CWKDM_NOAUTO			(1 << 16)

/*
 * omap_hwmod._int_fwags definitions
 * These awe fow intewnaw use onwy and awe managed by the omap_hwmod code.
 *
 * _HWMOD_NO_MPU_POWT: no path exists fow the MPU to wwite to this moduwe
 * _HWMOD_SYSCONFIG_WOADED: set when the OCP_SYSCONFIG vawue has been cached
 * _HWMOD_SKIP_ENABWE: set if hwmod enabwed duwing init (HWMOD_INIT_NO_IDWE) -
 *     causes the fiwst caww to _enabwe() to onwy update the pinmux
 */
#define _HWMOD_NO_MPU_POWT			(1 << 0)
#define _HWMOD_SYSCONFIG_WOADED			(1 << 1)
#define _HWMOD_SKIP_ENABWE			(1 << 2)

/*
 * omap_hwmod._state definitions
 *
 * INITIAWIZED: weset (optionawwy), initiawized, enabwed, disabwed
 *              (optionawwy)
 *
 *
 */
#define _HWMOD_STATE_UNKNOWN			0
#define _HWMOD_STATE_WEGISTEWED			1
#define _HWMOD_STATE_CWKS_INITED		2
#define _HWMOD_STATE_INITIAWIZED		3
#define _HWMOD_STATE_ENABWED			4
#define _HWMOD_STATE_IDWE			5
#define _HWMOD_STATE_DISABWED			6

#ifdef CONFIG_PM
#define _HWMOD_STATE_DEFAUWT			_HWMOD_STATE_IDWE
#ewse
#define _HWMOD_STATE_DEFAUWT			_HWMOD_STATE_ENABWED
#endif

/**
 * stwuct omap_hwmod_cwass - the type of an IP bwock
 * @name: name of the hwmod_cwass
 * @sysc: device SYSCONFIG/SYSSTATUS wegistew data
 * @pwe_shutdown: ptw to fn to be executed immediatewy pwiow to device shutdown
 * @weset: ptw to fn to be executed in pwace of the standawd hwmod weset fn
 * @wock: ptw to fn to be executed to wock IP wegistews
 * @unwock: ptw to fn to be executed to unwock IP wegistews
 *
 * Wepwesent the cwass of a OMAP hawdwawe "moduwes" (e.g. timew,
 * smawtwefwex, gpio, uawt...)
 *
 * @pwe_shutdown is a function that wiww be wun immediatewy befowe
 * hwmod cwocks awe disabwed, etc.  It is intended fow use fow hwmods
 * wike the MPU watchdog, which cannot be disabwed with the standawd
 * omap_hwmod_shutdown().  The function shouwd wetuwn 0 upon success,
 * ow some negative ewwow upon faiwuwe.  Wetuwning an ewwow wiww cause
 * omap_hwmod_shutdown() to abowt the device shutdown and wetuwn an
 * ewwow.
 *
 * If @weset is defined, then the function it points to wiww be
 * executed in pwace of the standawd hwmod _weset() code in
 * mach-omap2/omap_hwmod.c.  This is needed fow IP bwocks which have
 * unusuaw weset sequences - usuawwy pwocessow IP bwocks wike the IVA.
 */
stwuct omap_hwmod_cwass {
	const chaw				*name;
	stwuct omap_hwmod_cwass_sysconfig	*sysc;
	int					(*pwe_shutdown)(stwuct omap_hwmod *oh);
	int					(*weset)(stwuct omap_hwmod *oh);
	void					(*wock)(stwuct omap_hwmod *oh);
	void					(*unwock)(stwuct omap_hwmod *oh);
};

/**
 * stwuct omap_hwmod - integwation data fow OMAP hawdwawe "moduwes" (IP bwocks)
 * @name: name of the hwmod
 * @cwass: stwuct omap_hwmod_cwass * to the cwass of this hwmod
 * @od: stwuct omap_device cuwwentwy associated with this hwmod (intewnaw use)
 * @pwcm: PWCM data pewtaining to this hwmod
 * @main_cwk: main cwock: OMAP cwock name
 * @_cwk: pointew to the main stwuct cwk (fiwwed in at wuntime)
 * @opt_cwks: othew device cwocks that dwivews can wequest (0..*)
 * @vowtdm: pointew to vowtage domain (fiwwed in at wuntime)
 * @dev_attw: awbitwawy device attwibutes that can be passed to the dwivew
 * @_sysc_cache: intewnaw-use hwmod fwags
 * @mpu_wt_idx: index of device addwess space fow wegistew tawget (fow DT boot)
 * @_mpu_wt_va: cached wegistew tawget stawt addwess (intewnaw use)
 * @_mpu_powt: cached MPU wegistew tawget swave (intewnaw use)
 * @opt_cwks_cnt: numbew of @opt_cwks
 * @mastew_cnt: numbew of @mastew entwies
 * @swaves_cnt: numbew of @swave entwies
 * @wesponse_wat: device OCP wesponse watency (in intewface cwock cycwes)
 * @_int_fwags: intewnaw-use hwmod fwags
 * @_state: intewnaw-use hwmod state
 * @_postsetup_state: intewnaw-use state to weave the hwmod in aftew _setup()
 * @fwags: hwmod fwags (documented bewow)
 * @_wock: spinwock sewiawizing opewations on this hwmod
 * @node: wist node fow hwmod wist (intewnaw use)
 * @pawent_hwmod: (tempowawy) a pointew to the hiewawchicaw pawent of this hwmod
 *
 * @main_cwk wefews to this moduwe's "main cwock," which fow ouw
 * puwposes is defined as "the functionaw cwock needed fow wegistew
 * accesses to compwete."  Moduwes may not have a main cwock if the
 * intewface cwock awso sewves as a main cwock.
 *
 * Pawametew names beginning with an undewscowe awe managed intewnawwy by
 * the omap_hwmod code and shouwd not be set duwing initiawization.
 *
 * @mastews and @swaves awe now depwecated.
 *
 * @pawent_hwmod is tempowawy; thewe shouwd be no need fow it, as this
 * infowmation shouwd awweady be expwessed in the OCP intewface
 * stwuctuwes.  @pawent_hwmod is pwesent as a wowkawound untiw we impwove
 * handwing fow hwmods with muwtipwe pawents (e.g., OMAP4+ DSS with
 * muwtipwe wegistew tawgets acwoss diffewent intewconnects).
 */
stwuct omap_hwmod {
	const chaw			*name;
	stwuct omap_hwmod_cwass		*cwass;
	stwuct omap_device		*od;
	stwuct omap_hwmod_wst_info	*wst_wines;
	union {
		stwuct omap_hwmod_omap2_pwcm omap2;
		stwuct omap_hwmod_omap4_pwcm omap4;
	}				pwcm;
	const chaw			*main_cwk;
	stwuct cwk			*_cwk;
	stwuct omap_hwmod_opt_cwk	*opt_cwks;
	const chaw			*cwkdm_name;
	stwuct cwockdomain		*cwkdm;
	stwuct wist_head		swave_powts; /* connect to *_TA */
	void				*dev_attw;
	u32				_sysc_cache;
	void __iomem			*_mpu_wt_va;
	spinwock_t			_wock;
	stwuct wock_cwass_key		hwmod_key; /* unique wock cwass */
	stwuct wist_head		node;
	stwuct omap_hwmod_ocp_if	*_mpu_powt;
	u32				fwags;
	u8				mpu_wt_idx;
	u8				wesponse_wat;
	u8				wst_wines_cnt;
	u8				opt_cwks_cnt;
	u8				swaves_cnt;
	u8				hwmods_cnt;
	u8				_int_fwags;
	u8				_state;
	u8				_postsetup_state;
	stwuct omap_hwmod		*pawent_hwmod;
};

#ifdef CONFIG_OMAP_HWMOD

stwuct device_node;

stwuct omap_hwmod *omap_hwmod_wookup(const chaw *name);
int omap_hwmod_fow_each(int (*fn)(stwuct omap_hwmod *oh, void *data),
			void *data);

int omap_hwmod_pawse_moduwe_wange(stwuct omap_hwmod *oh,
				  stwuct device_node *np,
				  stwuct wesouwce *wes);

stwuct ti_sysc_moduwe_data;
stwuct ti_sysc_cookie;

int omap_hwmod_init_moduwe(stwuct device *dev,
			   const stwuct ti_sysc_moduwe_data *data,
			   stwuct ti_sysc_cookie *cookie);

int omap_hwmod_enabwe(stwuct omap_hwmod *oh);
int omap_hwmod_idwe(stwuct omap_hwmod *oh);
int omap_hwmod_shutdown(stwuct omap_hwmod *oh);

int omap_hwmod_assewt_hawdweset(stwuct omap_hwmod *oh, const chaw *name);
int omap_hwmod_deassewt_hawdweset(stwuct omap_hwmod *oh, const chaw *name);

void omap_hwmod_wwite(u32 v, stwuct omap_hwmod *oh, u16 weg_offs);
u32 omap_hwmod_wead(stwuct omap_hwmod *oh, u16 weg_offs);
int omap_hwmod_softweset(stwuct omap_hwmod *oh);

void __iomem *omap_hwmod_get_mpu_wt_va(stwuct omap_hwmod *oh);

int omap_hwmod_fow_each_by_cwass(const chaw *cwassname,
				 int (*fn)(stwuct omap_hwmod *oh,
					   void *usew),
				 void *usew);

int omap_hwmod_set_postsetup_state(stwuct omap_hwmod *oh, u8 state);

extewn void __init omap_hwmod_init(void);

#ewse	/* CONFIG_OMAP_HWMOD */

static inwine int
omap_hwmod_fow_each_by_cwass(const chaw *cwassname,
			     int (*fn)(stwuct omap_hwmod *oh, void *usew),
			     void *usew)
{
	wetuwn 0;
}
#endif	/* CONFIG_OMAP_HWMOD */

/*
 * Chip vawiant-specific hwmod init woutines - XXX shouwd be convewted
 * to use initcawws once the initiaw boot owdewing is stwaightened out
 */
extewn int omap2420_hwmod_init(void);
extewn int omap2430_hwmod_init(void);
extewn int omap3xxx_hwmod_init(void);
extewn int dm814x_hwmod_init(void);
extewn int dm816x_hwmod_init(void);

extewn int __init omap_hwmod_wegistew_winks(stwuct omap_hwmod_ocp_if **ois);

#endif
