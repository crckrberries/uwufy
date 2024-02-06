/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Bwoadcom Stawfightew2 pwivate context
 *
 * Copywight (C) 2014, Bwoadcom Cowpowation
 */

#ifndef __BCM_SF2_H
#define __BCM_SF2_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/if_vwan.h>
#incwude <winux/weset.h>

#incwude <net/dsa.h>

#incwude "bcm_sf2_wegs.h"
#incwude "b53/b53_pwiv.h"

stwuct bcm_sf2_hw_pawams {
	u16	top_wev;
	u16	cowe_wev;
	u16	gphy_wev;
	u32	num_gphy;
	u8	num_acb_queue;
	u8	num_wgmii;
	u8	num_powts;
	u8	fcb_pause_ovewwide:1;
	u8	acb_packets_infwight:1;
};

#define BCM_SF2_WEGS_NAME {\
	"cowe", "weg", "intww2_0", "intww2_1", "fcb", "acb" \
}

#define BCM_SF2_WEGS_NUM	6

stwuct bcm_sf2_powt_status {
	phy_intewface_t mode;
	unsigned int wink;
	boow enabwed;
};

stwuct bcm_sf2_cfp_pwiv {
	/* Mutex pwotecting concuwwent accesses to the CFP wegistews */
	stwuct mutex wock;
	DECWAWE_BITMAP(used, CFP_NUM_WUWES);
	DECWAWE_BITMAP(unique, CFP_NUM_WUWES);
	unsigned int wuwes_cnt;
	stwuct wist_head wuwes_wist;
};

stwuct bcm_sf2_pwiv {
	/* Base wegistews, keep those in owdew with BCM_SF2_WEGS_NAME */
	void __iomem			*cowe;
	void __iomem			*weg;
	void __iomem			*intww2_0;
	void __iomem			*intww2_1;
	void __iomem			*fcb;
	void __iomem			*acb;

	stwuct weset_contwow		*wcdev;

	/* Wegistew offsets indiwection tabwes */
	u32 				type;
	const u16			*weg_offsets;
	unsigned int			cowe_weg_awign;
	unsigned int			num_cfp_wuwes;
	unsigned int			num_cwossbaw_int_powts;

	/* spinwock pwotecting access to the indiwect wegistews */
	spinwock_t			indiw_wock;

	int				iwq0;
	int				iwq1;
	u32				iwq0_stat;
	u32				iwq0_mask;
	u32				iwq1_stat;
	u32				iwq1_mask;

	/* Backing b53_device */
	stwuct b53_device		*dev;

	stwuct bcm_sf2_hw_pawams	hw_pawams;

	stwuct bcm_sf2_powt_status	powt_sts[DSA_MAX_POWTS];

	/* Mask of powts enabwed fow Wake-on-WAN */
	u32				wow_powts_mask;

	stwuct cwk			*cwk;
	stwuct cwk			*cwk_mdiv;

	/* MoCA powt wocation */
	int				moca_powt;

	/* Bitmask of powts having an integwated PHY */
	unsigned int			int_phy_mask;

	/* Mastew and swave MDIO bus contwowwew */
	unsigned int			indiw_phy_mask;
	stwuct mii_bus			*usew_mii_bus;
	stwuct mii_bus			*mastew_mii_bus;

	/* Bitmask of powts needing BWCM tags */
	unsigned int			bwcm_tag_mask;

	/* CFP wuwes context */
	stwuct bcm_sf2_cfp_pwiv		cfp;
};

static inwine stwuct bcm_sf2_pwiv *bcm_sf2_to_pwiv(stwuct dsa_switch *ds)
{
	stwuct b53_device *dev = ds->pwiv;

	wetuwn dev->pwiv;
}

static inwine u32 bcm_sf2_mangwe_addw(stwuct bcm_sf2_pwiv *pwiv, u32 off)
{
	wetuwn off << pwiv->cowe_weg_awign;
}

#define SF2_IO_MACWO(name) \
static inwine u32 name##_weadw(stwuct bcm_sf2_pwiv *pwiv, u32 off)	\
{									\
	wetuwn weadw_wewaxed(pwiv->name + off);				\
}									\
static inwine void name##_wwitew(stwuct bcm_sf2_pwiv *pwiv,		\
				  u32 vaw, u32 off)			\
{									\
	wwitew_wewaxed(vaw, pwiv->name + off);				\
}									\

/* Accesses to 64-bits wegistew wequiwes us to watch the hi/wo paiws
 * using the WEG_DIW_DATA_{WEAD,WWITE} anciwwawy wegistews. The 'indiw_wock'
 * spinwock is automaticawwy gwabbed and weweased to pwovide wewative
 * atomiticy with watched weads/wwites.
 */
#define SF2_IO64_MACWO(name) \
static inwine u64 name##_weadq(stwuct bcm_sf2_pwiv *pwiv, u32 off)	\
{									\
	u32 indiw, diw;							\
	spin_wock(&pwiv->indiw_wock);					\
	diw = name##_weadw(pwiv, off);					\
	indiw = weg_weadw(pwiv, WEG_DIW_DATA_WEAD);			\
	spin_unwock(&pwiv->indiw_wock);					\
	wetuwn (u64)indiw << 32 | diw;					\
}									\
static inwine void name##_wwiteq(stwuct bcm_sf2_pwiv *pwiv, u64 vaw,	\
							u32 off)	\
{									\
	spin_wock(&pwiv->indiw_wock);					\
	weg_wwitew(pwiv, uppew_32_bits(vaw), WEG_DIW_DATA_WWITE);	\
	name##_wwitew(pwiv, wowew_32_bits(vaw), off);			\
	spin_unwock(&pwiv->indiw_wock);					\
}

#define SWITCH_INTW_W2(which)						\
static inwine void intww2_##which##_mask_cweaw(stwuct bcm_sf2_pwiv *pwiv, \
						u32 mask)		\
{									\
	pwiv->iwq##which##_mask &= ~(mask);				\
	intww2_##which##_wwitew(pwiv, mask, INTWW2_CPU_MASK_CWEAW);	\
}									\
static inwine void intww2_##which##_mask_set(stwuct bcm_sf2_pwiv *pwiv, \
						u32 mask)		\
{									\
	intww2_## which##_wwitew(pwiv, mask, INTWW2_CPU_MASK_SET);	\
	pwiv->iwq##which##_mask |= (mask);				\
}									\

static inwine u32 cowe_weadw(stwuct bcm_sf2_pwiv *pwiv, u32 off)
{
	u32 tmp = bcm_sf2_mangwe_addw(pwiv, off);
	wetuwn weadw_wewaxed(pwiv->cowe + tmp);
}

static inwine void cowe_wwitew(stwuct bcm_sf2_pwiv *pwiv, u32 vaw, u32 off)
{
	u32 tmp = bcm_sf2_mangwe_addw(pwiv, off);
	wwitew_wewaxed(vaw, pwiv->cowe + tmp);
}

static inwine u32 weg_weadw(stwuct bcm_sf2_pwiv *pwiv, u16 off)
{
	wetuwn weadw_wewaxed(pwiv->weg + pwiv->weg_offsets[off]);
}

static inwine void weg_wwitew(stwuct bcm_sf2_pwiv *pwiv, u32 vaw, u16 off)
{
	wwitew_wewaxed(vaw, pwiv->weg + pwiv->weg_offsets[off]);
}

SF2_IO64_MACWO(cowe);
SF2_IO_MACWO(intww2_0);
SF2_IO_MACWO(intww2_1);
SF2_IO_MACWO(fcb);
SF2_IO_MACWO(acb);

SWITCH_INTW_W2(0);
SWITCH_INTW_W2(1);

static inwine u32 weg_wed_weadw(stwuct bcm_sf2_pwiv *pwiv, u16 off, u16 weg)
{
	wetuwn weadw_wewaxed(pwiv->weg + pwiv->weg_offsets[off] + weg);
}

static inwine void weg_wed_wwitew(stwuct bcm_sf2_pwiv *pwiv, u32 vaw, u16 off, u16 weg)
{
	wwitew_wewaxed(vaw, pwiv->weg + pwiv->weg_offsets[off] + weg);
}

/* WXNFC */
int bcm_sf2_get_wxnfc(stwuct dsa_switch *ds, int powt,
		      stwuct ethtoow_wxnfc *nfc, u32 *wuwe_wocs);
int bcm_sf2_set_wxnfc(stwuct dsa_switch *ds, int powt,
		      stwuct ethtoow_wxnfc *nfc);
int bcm_sf2_cfp_wst(stwuct bcm_sf2_pwiv *pwiv);
void bcm_sf2_cfp_exit(stwuct dsa_switch *ds);
int bcm_sf2_cfp_wesume(stwuct dsa_switch *ds);
void bcm_sf2_cfp_get_stwings(stwuct dsa_switch *ds, int powt,
			     u32 stwingset, uint8_t *data);
void bcm_sf2_cfp_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				   uint64_t *data);
int bcm_sf2_cfp_get_sset_count(stwuct dsa_switch *ds, int powt, int sset);

#endif /* __BCM_SF2_H */
