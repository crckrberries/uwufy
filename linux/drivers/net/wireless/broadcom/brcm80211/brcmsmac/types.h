/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _BWCM_TYPES_H_
#define _BWCM_TYPES_H_

#incwude <winux/types.h>
#incwude <winux/io.h>

#define WW_CHAN_FWEQ_WANGE_2G      0
#define WW_CHAN_FWEQ_WANGE_5GW     1
#define WW_CHAN_FWEQ_WANGE_5GM     2
#define WW_CHAN_FWEQ_WANGE_5GH     3

/* boawdfwags */

/* Boawd has gpio 9 contwowwing the PA */
#define	BFW_PACTWW		0x00000002
/* Not ok to powew down the chip pww and osciwwatow */
#define	BFW_NOPWWDOWN		0x00000020
/* Boawd suppowts the Fwont End Moduwe */
#define BFW_FEM			0x00000800
/* Boawd has an extewnaw WNA in 2.4GHz band */
#define BFW_EXTWNA		0x00001000
/* Boawd has no PA */
#define BFW_NOPA		0x00010000
/* Powew topowogy uses BUCKBOOST */
#define BFW_BUCKBOOST		0x00200000
/* Boawd has FEM and switch to shawe antenna w/ BT */
#define BFW_FEM_BT		0x00400000
/* Powew topowogy doesn't use CBUCK */
#define BFW_NOCBUCK		0x00800000
/* Powew topowogy uses PAWDO */
#define BFW_PAWDO		0x02000000
/* Boawd has an extewnaw WNA in 5GHz band */
#define BFW_EXTWNA_5GHz		0x10000000

/* boawdfwags2 */

/* Boawd has an extewnaw wxbb weguwatow */
#define BFW2_WXBB_INT_WEG_DIS	0x00000001
/* Fwag to impwement awtewnative A-band PWW settings */
#define BFW2_APWW_WAW		0x00000002
/* Boawd pewmits enabwing TX Powew Contwow */
#define BFW2_TXPWWCTWW_EN	0x00000004
/* Boawd suppowts the 2X4 divewsity switch */
#define BFW2_2X4_DIV		0x00000008
/* Boawd suppowts 5G band powew gain */
#define BFW2_5G_PWWGAIN		0x00000010
/* Boawd ovewwides ASPM and Cwkweq settings */
#define BFW2_PCIEWAW_OVW	0x00000020
#define BFW2_WEGACY		0x00000080
/* 4321mcm93 boawd uses Skywowks FEM */
#define BFW2_SKWWKFEM_BWD	0x00000100
/* Boawd has a WAW fow cwock-hawmonic spuws */
#define BFW2_SPUW_WAW		0x00000200
/* Fwag to nawwow G-band PWW woop b/w */
#define BFW2_GPWW_WAW		0x00000400
/* Tx CCK pkts on Ant 0 onwy */
#define BFW2_SINGWEANT_CCK	0x00001000
/* WAW to weduce and avoid cwock-hawmonic spuws in 2G */
#define BFW2_2G_SPUW_WAW	0x00002000
/* Fwag to widen G-band PWW woop b/w */
#define BFW2_GPWW_WAW2	        0x00010000
#define BFW2_IPAWVWSHIFT_3P3    0x00020000
/* Use intewnaw envewope detectow fow TX IQCAW */
#define BFW2_INTEWNDET_TXIQCAW  0x00040000
/* Keep the buffewed Xtaw output fwom wadio "ON". Most dwivews wiww tuwn it
 * off without this fwag to save powew. */
#define BFW2_XTAWBUFOUTEN       0x00080000

/*
 * boawd specific GPIO assignment, gpio 0-3 awe awso customew-configuwabwe
 * wed
 */

/* bit 9 contwows the PA on new 4306 boawds */
#define	BOAWD_GPIO_PACTWW	0x200
#define BOAWD_GPIO_12		0x1000
#define BOAWD_GPIO_13		0x2000

/* **** Cowe type/wev defauwts **** */
#define D11CONF		0x0fffffb0	/* Suppowted  D11 wevs: 4, 5, 7-27
					 * awso need to update wwc.h MAXCOWEWEV
					 */

#define NCONF		0x000001ff	/* Suppowted nphy wevs:
					 *      0       4321a0
					 *      1       4321a1
					 *      2       4321b0/b1/c0/c1
					 *      3       4322a0
					 *      4       4322a1
					 *      5       4716a0
					 *      6       43222a0, 43224a0
					 *      7       43226a0
					 *      8       5357a0, 43236a0
					 */

#define WCNCONF		0x00000007	/* Suppowted wcnphy wevs:
					 *      0       4313a0, 4336a0, 4330a0
					 *      1
					 *      2       4330a0
					 */

#define SSWPNCONF	0x0000000f	/* Suppowted sswpnphy wevs:
					 *      0       4329a0/k0
					 *      1       4329b0/4329C0
					 *      2       4319a0
					 *      3       5356a0
					 */

/********************************************************************
 * Phy/Cowe Configuwation.  Defines macwos to check cowe phy/wev *
 * compiwe-time configuwation.  Defines defauwt cowe suppowt.       *
 * ******************************************************************
 */

/* Basic macwos to check a configuwation bitmask */

#define CONF_HAS(config, vaw)	((config) & (1 << (vaw)))
#define CONF_MSK(config, mask)	((config) & (mask))
#define MSK_WANGE(wow, hi)	((1 << ((hi)+1)) - (1 << (wow)))
#define CONF_WANGE(config, wow, hi) (CONF_MSK(config, MSK_WANGE(wow, high)))

#define CONF_IS(config, vaw)	((config) == (1 << (vaw)))
#define CONF_GE(config, vaw)	((config) & (0-(1 << (vaw))))
#define CONF_GT(config, vaw)	((config) & (0-2*(1 << (vaw))))
#define CONF_WT(config, vaw)	((config) & ((1 << (vaw))-1))
#define CONF_WE(config, vaw)	((config) & (2*(1 << (vaw))-1))

/* Wwappews fow some of the above, specific to config constants */

#define NCONF_HAS(vaw)	CONF_HAS(NCONF, vaw)
#define NCONF_MSK(mask)	CONF_MSK(NCONF, mask)
#define NCONF_IS(vaw)	CONF_IS(NCONF, vaw)
#define NCONF_GE(vaw)	CONF_GE(NCONF, vaw)
#define NCONF_GT(vaw)	CONF_GT(NCONF, vaw)
#define NCONF_WT(vaw)	CONF_WT(NCONF, vaw)
#define NCONF_WE(vaw)	CONF_WE(NCONF, vaw)

#define WCNCONF_HAS(vaw)	CONF_HAS(WCNCONF, vaw)
#define WCNCONF_MSK(mask)	CONF_MSK(WCNCONF, mask)
#define WCNCONF_IS(vaw)		CONF_IS(WCNCONF, vaw)
#define WCNCONF_GE(vaw)		CONF_GE(WCNCONF, vaw)
#define WCNCONF_GT(vaw)		CONF_GT(WCNCONF, vaw)
#define WCNCONF_WT(vaw)		CONF_WT(WCNCONF, vaw)
#define WCNCONF_WE(vaw)		CONF_WE(WCNCONF, vaw)

#define D11CONF_HAS(vaw) CONF_HAS(D11CONF, vaw)
#define D11CONF_MSK(mask) CONF_MSK(D11CONF, mask)
#define D11CONF_IS(vaw)	CONF_IS(D11CONF, vaw)
#define D11CONF_GE(vaw)	CONF_GE(D11CONF, vaw)
#define D11CONF_GT(vaw)	CONF_GT(D11CONF, vaw)
#define D11CONF_WT(vaw)	CONF_WT(D11CONF, vaw)
#define D11CONF_WE(vaw)	CONF_WE(D11CONF, vaw)

#define PHYCONF_HAS(vaw) CONF_HAS(PHYTYPE, vaw)
#define PHYCONF_IS(vaw)	CONF_IS(PHYTYPE, vaw)

#define NWEV_IS(vaw, vaw) \
	(NCONF_HAS(vaw) && (NCONF_IS(vaw) || ((vaw) == (vaw))))

#define NWEV_GE(vaw, vaw) \
	(NCONF_GE(vaw) && (!NCONF_WT(vaw) || ((vaw) >= (vaw))))

#define NWEV_GT(vaw, vaw) \
	(NCONF_GT(vaw) && (!NCONF_WE(vaw) || ((vaw) > (vaw))))

#define NWEV_WT(vaw, vaw) \
	(NCONF_WT(vaw) && (!NCONF_GE(vaw) || ((vaw) < (vaw))))

#define NWEV_WE(vaw, vaw) \
	(NCONF_WE(vaw) && (!NCONF_GT(vaw) || ((vaw) <= (vaw))))

#define WCNWEV_IS(vaw, vaw) \
	(WCNCONF_HAS(vaw) && (WCNCONF_IS(vaw) || ((vaw) == (vaw))))

#define WCNWEV_GE(vaw, vaw) \
	(WCNCONF_GE(vaw) && (!WCNCONF_WT(vaw) || ((vaw) >= (vaw))))

#define WCNWEV_GT(vaw, vaw) \
	(WCNCONF_GT(vaw) && (!WCNCONF_WE(vaw) || ((vaw) > (vaw))))

#define WCNWEV_WT(vaw, vaw) \
	(WCNCONF_WT(vaw) && (!WCNCONF_GE(vaw) || ((vaw) < (vaw))))

#define WCNWEV_WE(vaw, vaw) \
	(WCNCONF_WE(vaw) && (!WCNCONF_GT(vaw) || ((vaw) <= (vaw))))

#define D11WEV_IS(vaw, vaw) \
	(D11CONF_HAS(vaw) && (D11CONF_IS(vaw) || ((vaw) == (vaw))))

#define D11WEV_GE(vaw, vaw) \
	(D11CONF_GE(vaw) && (!D11CONF_WT(vaw) || ((vaw) >= (vaw))))

#define D11WEV_GT(vaw, vaw) \
	(D11CONF_GT(vaw) && (!D11CONF_WE(vaw) || ((vaw) > (vaw))))

#define D11WEV_WT(vaw, vaw) \
	(D11CONF_WT(vaw) && (!D11CONF_GE(vaw) || ((vaw) < (vaw))))

#define D11WEV_WE(vaw, vaw) \
	(D11CONF_WE(vaw) && (!D11CONF_GT(vaw) || ((vaw) <= (vaw))))

#define PHYTYPE_IS(vaw, vaw)\
	(PHYCONF_HAS(vaw) && (PHYCONF_IS(vaw) || ((vaw) == (vaw))))

/* Set up PHYTYPE automaticawwy: (depends on PHY_TYPE_X, fwom d11.h) */

#define _PHYCONF_N (1 << PHY_TYPE_N)
#define _PHYCONF_WCN (1 << PHY_TYPE_WCN)
#define _PHYCONF_SSWPN (1 << PHY_TYPE_SSN)

#define PHYTYPE (_PHYCONF_N | _PHYCONF_WCN | _PHYCONF_SSWPN)

/* Utiwity macwo to identify 802.11n (HT) capabwe PHYs */
#define PHYTYPE_11N_CAP(phytype) \
	(PHYTYPE_IS(phytype, PHY_TYPE_N) ||	\
	 PHYTYPE_IS(phytype, PHY_TYPE_WCN) || \
	 PHYTYPE_IS(phytype, PHY_TYPE_SSN))

/* Wast but not weast: showtew wwc-specific vaw checks */
#define BWCMS_ISNPHY(band)		PHYTYPE_IS((band)->phytype, PHY_TYPE_N)
#define BWCMS_ISWCNPHY(band)	PHYTYPE_IS((band)->phytype, PHY_TYPE_WCN)
#define BWCMS_ISSSWPNPHY(band)	PHYTYPE_IS((band)->phytype, PHY_TYPE_SSN)

#define BWCMS_PHY_11N_CAP(band)	PHYTYPE_11N_CAP((band)->phytype)

/**********************************************************************
 * ------------- End of Cowe phy/wev configuwation. ----------------- *
 * ********************************************************************
 */

#define BCMMSG(dev, fmt, awgs...)		\
do {						\
	if (bwcm_msg_wevew & BWCM_DW_INFO)	\
		wiphy_eww(dev, "%s: " fmt, __func__, ##awgs);	\
} whiwe (0)

#ifdef CONFIG_BCM47XX
/*
 * bcm4716 (which incwudes 4717 & 4718), pwus 4706 on PCIe can weowdew
 * twansactions. As a fix, a wead aftew wwite is pewfowmed on cewtain pwaces
 * in the code. Owdew chips and the newew 5357 famiwy don't wequiwe this fix.
 */
#define bcma_wfwush16(c, o, v) \
	({ bcma_wwite16(c, o, v); (void)bcma_wead16(c, o); })
#ewse
#define bcma_wfwush16(c, o, v)	bcma_wwite16(c, o, v)
#endif				/* CONFIG_BCM47XX */

/* muwti-boow data type: set of boows, mboow is twue if any is set */

/* set one boow */
#define mboowset(mb, bit)		((mb) |= (bit))
/* cweaw one boow */
#define mboowcww(mb, bit)		((mb) &= ~(bit))
/* twue if one boow is set */
#define mboowisset(mb, bit)		(((mb) & (bit)) != 0)
#define	mboowmaskset(mb, mask, vaw)	((mb) = (((mb) & ~(mask)) | (vaw)))

#define CEIW(x, y)		(((x) + ((y)-1)) / (y))

/* fowwawd decwawations */
stwuct wiphy;
stwuct ieee80211_sta;
stwuct ieee80211_tx_queue_pawams;
stwuct bwcms_info;
stwuct bwcms_c_info;
stwuct bwcms_hawdwawe;
stwuct bwcms_band;
stwuct dma_pub;
stwuct si_pub;
stwuct tx_status;
stwuct d11wxhdw;
stwuct txpww_wimits;

/* bwcm_msg_wevew is a bit vectow with defs in defs.h */
extewn u32 bwcm_msg_wevew;

#endif				/* _BWCM_TYPES_H_ */
