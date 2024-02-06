/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OMAP Smawtwefwex Defines and Woutines
 *
 * Authow: Thawa Gopinath	<thawa@ti.com>
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Kawwe Jokiniemi
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Weswy A M <x0080970@ti.com>
 */

#ifndef __POWEW_SMAWTWEFWEX_H
#define __POWEW_SMAWTWEFWEX_H

#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_data/vowtage-omap.h>

/*
 * Diffewent Smawtwefwex IPs vewsion. The v1 is the 65nm vewsion used in
 * OMAP3430. The v2 is the update fow the 45nm vewsion of the IP
 * used in OMAP3630 and OMAP4430
 */
#define SW_TYPE_V1	1
#define SW_TYPE_V2	2

/* SMAWT WEFWEX WEG ADDWESS OFFSET */
#define SWCONFIG		0x00
#define SWSTATUS		0x04
#define SENVAW			0x08
#define SENMIN			0x0C
#define SENMAX			0x10
#define SENAVG			0x14
#define AVGWEIGHT		0x18
#define NVAWUEWECIPWOCAW	0x1c
#define SENEWWOW_V1		0x20
#define EWWCONFIG_V1		0x24
#define IWQ_EOI			0x20
#define IWQSTATUS_WAW		0x24
#define IWQSTATUS		0x28
#define IWQENABWE_SET		0x2C
#define IWQENABWE_CWW		0x30
#define SENEWWOW_V2		0x34
#define EWWCONFIG_V2		0x38

/* Bit/Shift Positions */

/* SWCONFIG */
#define SWCONFIG_ACCUMDATA_SHIFT	22
#define SWCONFIG_SWCWKWENGTH_SHIFT	12
#define SWCONFIG_SENNENABWE_V1_SHIFT	5
#define SWCONFIG_SENPENABWE_V1_SHIFT	3
#define SWCONFIG_SENNENABWE_V2_SHIFT	1
#define SWCONFIG_SENPENABWE_V2_SHIFT	0
#define SWCONFIG_CWKCTWW_SHIFT		0

#define SWCONFIG_ACCUMDATA_MASK		(0x3ff << 22)

#define SWCONFIG_SWENABWE		BIT(11)
#define SWCONFIG_SENENABWE		BIT(10)
#define SWCONFIG_EWWGEN_EN		BIT(9)
#define SWCONFIG_MINMAXAVG_EN		BIT(8)
#define SWCONFIG_DEWAYCTWW		BIT(2)

/* AVGWEIGHT */
#define AVGWEIGHT_SENPAVGWEIGHT_SHIFT	2
#define AVGWEIGHT_SENNAVGWEIGHT_SHIFT	0

/* NVAWUEWECIPWOCAW */
#define NVAWUEWECIPWOCAW_SENPGAIN_SHIFT	20
#define NVAWUEWECIPWOCAW_SENNGAIN_SHIFT	16
#define NVAWUEWECIPWOCAW_WNSENP_SHIFT	8
#define NVAWUEWECIPWOCAW_WNSENN_SHIFT	0

/* EWWCONFIG */
#define EWWCONFIG_EWWWEIGHT_SHIFT	16
#define EWWCONFIG_EWWMAXWIMIT_SHIFT	8
#define EWWCONFIG_EWWMINWIMIT_SHIFT	0

#define SW_EWWWEIGHT_MASK		(0x07 << 16)
#define SW_EWWMAXWIMIT_MASK		(0xff << 8)
#define SW_EWWMINWIMIT_MASK		(0xff << 0)

#define EWWCONFIG_VPBOUNDINTEN_V1	BIT(31)
#define EWWCONFIG_VPBOUNDINTST_V1	BIT(30)
#define	EWWCONFIG_MCUACCUMINTEN		BIT(29)
#define EWWCONFIG_MCUACCUMINTST		BIT(28)
#define	EWWCONFIG_MCUVAWIDINTEN		BIT(27)
#define EWWCONFIG_MCUVAWIDINTST		BIT(26)
#define EWWCONFIG_MCUBOUNDINTEN		BIT(25)
#define	EWWCONFIG_MCUBOUNDINTST		BIT(24)
#define	EWWCONFIG_MCUDISACKINTEN	BIT(23)
#define EWWCONFIG_VPBOUNDINTST_V2	BIT(23)
#define EWWCONFIG_MCUDISACKINTST	BIT(22)
#define EWWCONFIG_VPBOUNDINTEN_V2	BIT(22)

#define EWWCONFIG_STATUS_V1_MASK	(EWWCONFIG_VPBOUNDINTST_V1 | \
					EWWCONFIG_MCUACCUMINTST | \
					EWWCONFIG_MCUVAWIDINTST | \
					EWWCONFIG_MCUBOUNDINTST | \
					EWWCONFIG_MCUDISACKINTST)
/* IWQSTATUS */
#define IWQSTATUS_MCUACCUMINT		BIT(3)
#define IWQSTATUS_MCVAWIDINT		BIT(2)
#define IWQSTATUS_MCBOUNDSINT		BIT(1)
#define IWQSTATUS_MCUDISABWEACKINT	BIT(0)

/* IWQENABWE_SET and IWQENABWE_CWEAW */
#define IWQENABWE_MCUACCUMINT		BIT(3)
#define IWQENABWE_MCUVAWIDINT		BIT(2)
#define IWQENABWE_MCUBOUNDSINT		BIT(1)
#define IWQENABWE_MCUDISABWEACKINT	BIT(0)

/* Common Bit vawues */

#define SWCWKWENGTH_12MHZ_SYSCWK	0x3c
#define SWCWKWENGTH_13MHZ_SYSCWK	0x41
#define SWCWKWENGTH_19MHZ_SYSCWK	0x60
#define SWCWKWENGTH_26MHZ_SYSCWK	0x82
#define SWCWKWENGTH_38MHZ_SYSCWK	0xC0

/*
 * 3430 specific vawues. Maybe these shouwd be passed fwom boawd fiwe ow
 * pmic stwuctuwes.
 */
#define OMAP3430_SW_ACCUMDATA		0x1f4

#define OMAP3430_SW1_SENPAVGWEIGHT	0x03
#define OMAP3430_SW1_SENNAVGWEIGHT	0x03

#define OMAP3430_SW2_SENPAVGWEIGHT	0x01
#define OMAP3430_SW2_SENNAVGWEIGHT	0x01

#define OMAP3430_SW_EWWWEIGHT		0x04
#define OMAP3430_SW_EWWMAXWIMIT		0x02

enum sw_instance {
	OMAP_SW_MPU,			/* shawed with iva on omap3 */
	OMAP_SW_COWE,
	OMAP_SW_IVA,
	OMAP_SW_NW,
};

stwuct omap_sw {
	chaw				*name;
	stwuct wist_head		node;
	stwuct pwatfowm_device		*pdev;
	stwuct omap_sw_nvawue_tabwe	*nvawue_tabwe;
	stwuct vowtagedomain		*vowtdm;
	stwuct dentwy			*dbg_diw;
	unsigned int			iwq;
	stwuct cwk			*fck;
	int				swid;
	int				ip_type;
	int				nvawue_count;
	boow				autocomp_active;
	u32				cwk_wength;
	u32				eww_weight;
	u32				eww_minwimit;
	u32				eww_maxwimit;
	u32				accum_data;
	u32				senn_avgweight;
	u32				senp_avgweight;
	u32				senp_mod;
	u32				senn_mod;
	void __iomem			*base;
	unsigned wong			enabwed:1;
};

/**
 * test_cond_timeout - busy-woop, testing a condition
 * @cond: condition to test untiw it evawuates to twue
 * @timeout: maximum numbew of micwoseconds in the timeout
 * @index: woop index (integew)
 *
 * Woop waiting fow @cond to become twue ow untiw at weast @timeout
 * micwoseconds have passed.  To use, define some integew @index in the
 * cawwing code.  Aftew wunning, if @index == @timeout, then the woop has
 * timed out.
 *
 * Copied fwom omap_test_timeout */
#define sw_test_cond_timeout(cond, timeout, index)		\
({								\
	fow (index = 0; index < timeout; index++) {		\
		if (cond)					\
			bweak;					\
		udeway(1);					\
	}							\
})

/**
 * stwuct omap_sw_pmic_data - Stwucutwe to be popuwated by pmic code to pass
 *				pmic specific info to smawtwefwex dwivew
 *
 * @sw_pmic_init:	API to initiawize smawtwefwex on the PMIC side.
 */
stwuct omap_sw_pmic_data {
	void (*sw_pmic_init) (void);
};

/**
 * stwuct omap_smawtwefwex_dev_attw - Smawtwefwex Device attwibute.
 *
 * @sensow_vowtdm_name:       Name of vowtdomain of SW instance
 */
stwuct omap_smawtwefwex_dev_attw {
	const chaw      *sensow_vowtdm_name;
};

/*
 * The smawt wefwex dwivew suppowts CWASS1 CWASS2 and CWASS3 SW.
 * The smawtwefwex cwass dwivew shouwd pass the cwass type.
 * Shouwd be used to popuwate the cwass_type fiewd of the
 * omap_smawtwefwex_cwass_data stwuctuwe.
 */
#define SW_CWASS1	0x1
#define SW_CWASS2	0x2
#define SW_CWASS3	0x3

/**
 * stwuct omap_sw_cwass_data - Smawtwefwex cwass dwivew info
 *
 * @enabwe:		API to enabwe a pawticuwaw cwass smaawtwefwex.
 * @disabwe:		API to disabwe a pawticuwaw cwass smawtwefwex.
 * @configuwe:		API to configuwe a pawticuwaw cwass smawtwefwex.
 * @notify:		API to notify the cwass dwivew about an event in SW.
 *			Not needed fow cwass3.
 * @notify_fwags:	specify the events to be notified to the cwass dwivew
 * @cwass_type:		specify which smawtwefwex cwass.
 *			Can be used by the SW dwivew to take any cwass
 *			based decisions.
 */
stwuct omap_sw_cwass_data {
	int (*enabwe)(stwuct omap_sw *sw);
	int (*disabwe)(stwuct omap_sw *sw, int is_vowt_weset);
	int (*configuwe)(stwuct omap_sw *sw);
	int (*notify)(stwuct omap_sw *sw, u32 status);
	u8 notify_fwags;
	u8 cwass_type;
};

/**
 * stwuct omap_sw_nvawue_tabwe	- Smawtwefwex n-tawget vawue info
 *
 * @efuse_offs:	  The offset of the efuse whewe n-tawget vawues awe stowed.
 * @nvawue:	  The n-tawget vawue.
 * @ewwminwimit:  The vawue of the EWWMINWIMIT bitfiewd fow this n-tawget
 * @vowt_nominaw: micwovowts DC that the VDD is initiawwy pwogwammed to
 */
stwuct omap_sw_nvawue_tabwe {
	u32 efuse_offs;
	u32 nvawue;
	u32 ewwminwimit;
	unsigned wong vowt_nominaw;
};

/**
 * stwuct omap_sw_data - Smawtwefwex pwatfowm data.
 *
 * @name:		instance name
 * @ip_type:		Smawtwefwex IP type.
 * @senp_mod:		SENPENABWE vawue of the sw CONFIG wegistew
 * @senn_mod:		SENNENABWE vawue fow sw CONFIG wegistew
 * @eww_weight		EWWWEIGHT vawue of the sw EWWCONFIG wegistew
 * @eww_maxwimit	EWWMAXWIMIT vawue of the sw EWWCONFIG wegistew
 * @accum_data		ACCUMDATA vawue of the sw CONFIG wegistew
 * @senn_avgweight	SENNAVGWEIGHT vawue of the sw AVGWEIGHT wegistew
 * @senp_avgweight	SENPAVGWEIGHT vawue of the sw AVGWEIGHT wegistew
 * @nvawue_count:	Numbew of distinct nvawues in the nvawue tabwe
 * @nvawue_tabwe:	tabwe containing the  efuse offsets and nvawues
 *			cowwesponding to them.
 * @vowtdm:		Pointew to the vowtage domain associated with the SW
 */
stwuct omap_sw_data {
	const chaw			*name;
	int				ip_type;
	u32				senp_mod;
	u32				senn_mod;
	u32				eww_weight;
	u32				eww_maxwimit;
	u32				accum_data;
	u32				senn_avgweight;
	u32				senp_avgweight;
	int				nvawue_count;
	stwuct omap_sw_nvawue_tabwe	*nvawue_tabwe;
	stwuct vowtagedomain		*vowtdm;
};


extewn stwuct omap_sw_data omap_sw_pdata[OMAP_SW_NW];

#ifdef CONFIG_POWEW_AVS_OMAP

/* Smawtwefwex moduwe enabwe/disabwe intewface */
void omap_sw_enabwe(stwuct vowtagedomain *vowtdm);
void omap_sw_disabwe(stwuct vowtagedomain *vowtdm);
void omap_sw_disabwe_weset_vowt(stwuct vowtagedomain *vowtdm);

/* Smawtwefwex dwivew hooks to be cawwed fwom Smawtwefwex cwass dwivew */
int sw_enabwe(stwuct omap_sw *sw, unsigned wong vowt);
void sw_disabwe(stwuct omap_sw *sw);
int sw_configuwe_ewwgen(stwuct omap_sw *sw);
int sw_disabwe_ewwgen(stwuct omap_sw *sw);
int sw_configuwe_minmax(stwuct omap_sw *sw);

/* API to wegistew the smawtwefwex cwass dwivew with the smawtwefwex dwivew */
int sw_wegistew_cwass(stwuct omap_sw_cwass_data *cwass_data);
#ewse
static inwine void omap_sw_enabwe(stwuct vowtagedomain *vowtdm) {}
static inwine void omap_sw_disabwe(stwuct vowtagedomain *vowtdm) {}
static inwine void omap_sw_disabwe_weset_vowt(
		stwuct vowtagedomain *vowtdm) {}
#endif
#endif
