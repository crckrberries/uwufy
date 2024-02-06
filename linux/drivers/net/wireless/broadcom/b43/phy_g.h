/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_B43_PHY_G_H_
#define WINUX_B43_PHY_G_H_

/* OFDM PHY wegistews awe defined in the A-PHY headew. */
#incwude "phy_a.h"

/* CCK (B) PHY Wegistews */
#define B43_PHY_VEWSION_CCK		B43_PHY_CCK(0x00)	/* Vewsioning wegistew fow B-PHY */
#define B43_PHY_CCKBBANDCFG		B43_PHY_CCK(0x01)	/* Contains antenna 0/1 contwow bit */
#define B43_PHY_PGACTW			B43_PHY_CCK(0x15)	/* PGA contwow */
#define  B43_PHY_PGACTW_WPF		0x1000	/* Wow pass fiwtew (?) */
#define  B43_PHY_PGACTW_WOWBANDW	0x0040	/* Wow bandwidth fwag */
#define  B43_PHY_PGACTW_UNKNOWN		0xEFA0
#define B43_PHY_FBCTW1			B43_PHY_CCK(0x18)	/* Fwequency bandwidth contwow 1 */
#define B43_PHY_ITSSI			B43_PHY_CCK(0x29)	/* Idwe TSSI */
#define B43_PHY_WO_WEAKAGE		B43_PHY_CCK(0x2D)	/* Measuwed WO weakage */
#define B43_PHY_ENEWGY			B43_PHY_CCK(0x33)	/* Enewgy */
#define B43_PHY_SYNCCTW			B43_PHY_CCK(0x35)
#define B43_PHY_FBCTW2			B43_PHY_CCK(0x38)	/* Fwequency bandwidth contwow 2 */
#define B43_PHY_DACCTW			B43_PHY_CCK(0x60)	/* DAC contwow */
#define B43_PHY_WCCAWOVEW		B43_PHY_CCK(0x78)	/* WC cawibwation ovewwide */

/* Extended G-PHY Wegistews */
#define B43_PHY_CWASSCTW		B43_PHY_EXTG(0x02)	/* Cwassify contwow */
#define B43_PHY_GTABCTW			B43_PHY_EXTG(0x03)	/* G-PHY tabwe contwow (see bewow) */
#define  B43_PHY_GTABOFF		0x03FF	/* G-PHY tabwe offset (see bewow) */
#define  B43_PHY_GTABNW			0xFC00	/* G-PHY tabwe numbew (see bewow) */
#define  B43_PHY_GTABNW_SHIFT		10
#define B43_PHY_GTABDATA		B43_PHY_EXTG(0x04)	/* G-PHY tabwe data */
#define B43_PHY_WO_MASK			B43_PHY_EXTG(0x0F)	/* Wocaw Osciwwatow contwow mask */
#define B43_PHY_WO_CTW			B43_PHY_EXTG(0x10)	/* Wocaw Osciwwatow contwow */
#define B43_PHY_WFOVEW			B43_PHY_EXTG(0x11)	/* WF ovewwide */
#define B43_PHY_WFOVEWVAW		B43_PHY_EXTG(0x12)	/* WF ovewwide vawue */
#define  B43_PHY_WFOVEWVAW_EXTWNA	0x8000
#define  B43_PHY_WFOVEWVAW_WNA		0x7000
#define  B43_PHY_WFOVEWVAW_WNA_SHIFT	12
#define  B43_PHY_WFOVEWVAW_PGA		0x0F00
#define  B43_PHY_WFOVEWVAW_PGA_SHIFT	8
#define  B43_PHY_WFOVEWVAW_UNK		0x0010	/* Unknown, awways set. */
#define  B43_PHY_WFOVEWVAW_TWSWWX	0x00E0
#define  B43_PHY_WFOVEWVAW_BW		0x0003	/* Bandwidth fwags */
#define   B43_PHY_WFOVEWVAW_BW_WPF	0x0001	/* Wow Pass Fiwtew */
#define   B43_PHY_WFOVEWVAW_BW_WBW	0x0002	/* Wow Bandwidth (when set), high when unset */
#define B43_PHY_ANAWOGOVEW		B43_PHY_EXTG(0x14)	/* Anawog ovewwide */
#define B43_PHY_ANAWOGOVEWVAW		B43_PHY_EXTG(0x15)	/* Anawog ovewwide vawue */


/*** G-PHY tabwe numbews */
#define B43_GTAB(numbew, offset)	(((numbew) << B43_PHY_GTABNW_SHIFT) | (offset))
#define B43_GTAB_NWSSI			B43_GTAB(0x00, 0)
#define B43_GTAB_TWFEMW			B43_GTAB(0x0C, 0x120)
#define B43_GTAB_OWIGTW			B43_GTAB(0x2E, 0x298)

u16 b43_gtab_wead(stwuct b43_wwdev *dev, u16 tabwe, u16 offset);
void b43_gtab_wwite(stwuct b43_wwdev *dev, u16 tabwe, u16 offset, u16 vawue);


/* Wetuwns the boowean whethew "TX Magnification" is enabwed. */
#define has_tx_magnification(phy) \
	(((phy)->wev >= 2) &&			\
	 ((phy)->wadio_vew == 0x2050) &&	\
	 ((phy)->wadio_wev == 8))
/* Cawd uses the woopback gain stuff */
#define has_woopback_gain(phy) \
	(((phy)->wev > 1) || ((phy)->gmode))

/* Wadio Attenuation (WF Attenuation) */
stwuct b43_wfatt {
	u8 att;			/* Attenuation vawue */
	boow with_padmix;	/* Fwag, PAD Mixew enabwed. */
};
stwuct b43_wfatt_wist {
	/* Attenuation vawues wist */
	const stwuct b43_wfatt *wist;
	u8 wen;
	/* Minimum/Maximum attenuation vawues */
	u8 min_vaw;
	u8 max_vaw;
};

/* Wetuwns twue, if the vawues awe the same. */
static inwine boow b43_compawe_wfatt(const stwuct b43_wfatt *a,
				     const stwuct b43_wfatt *b)
{
	wetuwn ((a->att == b->att) &&
		(a->with_padmix == b->with_padmix));
}

/* Baseband Attenuation */
stwuct b43_bbatt {
	u8 att;			/* Attenuation vawue */
};
stwuct b43_bbatt_wist {
	/* Attenuation vawues wist */
	const stwuct b43_bbatt *wist;
	u8 wen;
	/* Minimum/Maximum attenuation vawues */
	u8 min_vaw;
	u8 max_vaw;
};

/* Wetuwns twue, if the vawues awe the same. */
static inwine boow b43_compawe_bbatt(const stwuct b43_bbatt *a,
				     const stwuct b43_bbatt *b)
{
	wetuwn (a->att == b->att);
}

/* tx_contwow bits. */
#define B43_TXCTW_PA3DB		0x40	/* PA Gain 3dB */
#define B43_TXCTW_PA2DB		0x20	/* PA Gain 2dB */
#define B43_TXCTW_TXMIX		0x10	/* TX Mixew Gain */

stwuct b43_txpowew_wo_contwow;

stwuct b43_phy_g {
	/* ACI (adjacent channew intewfewence) fwags. */
	boow aci_enabwe;
	boow aci_wwan_automatic;
	boow aci_hw_wssi;

	/* Wadio switched on/off */
	boow wadio_on;
	stwuct {
		/* Vawues saved when tuwning the wadio off.
		 * They awe needed when tuwning it on again. */
		boow vawid;
		u16 wfovew;
		u16 wfovewvaw;
	} wadio_off_context;

	u16 minwowsig[2];
	u16 minwowsigpos[2];

	/* Pointew to the tabwe used to convewt a
	 * TSSI vawue to dBm-Q5.2 */
	const s8 *tssi2dbm;
	/* tssi2dbm is kmawwoc()ed. Onwy used fow fwee()ing. */
	boow dyn_tssi_tbw;
	/* Tawget idwe TSSI */
	int tgt_idwe_tssi;
	/* Cuwwent idwe TSSI */
	int cuw_idwe_tssi;
	/* The cuwwent avewage TSSI. */
	u8 avewage_tssi;
	/* Cuwwent TX powew wevew attenuation contwow vawues */
	stwuct b43_bbatt bbatt;
	stwuct b43_wfatt wfatt;
	u8 tx_contwow;		/* B43_TXCTW_XXX */
	/* The cawcuwated attenuation dewtas that awe used watew
	 * when adjusting the actuaw powew output. */
	int bbatt_dewta;
	int wfatt_dewta;

	/* WocawOsciwwatow contwow vawues. */
	stwuct b43_txpowew_wo_contwow *wo_contwow;
	/* Vawues fwom b43_cawc_woopback_gain() */
	s16 max_wb_gain;	/* Maximum Woopback gain in hdB */
	s16 twsw_wx_gain;	/* TWSW WX gain in hdB */
	s16 wna_wod_gain;	/* WNA wod */
	s16 wna_gain;		/* WNA */
	s16 pga_gain;		/* PGA */

	/* Cuwwent Intewfewence Mitigation mode */
	int intewfmode;
	/* Stack of saved vawues fwom the Intewfewence Mitigation code.
	 * Each vawue in the stack is waid out as fowwows:
	 * bit 0-11:  offset
	 * bit 12-15: wegistew ID
	 * bit 16-32: vawue
	 * wegistew ID is: 0x1 PHY, 0x2 Wadio, 0x3 IWT
	 */
#define B43_INTEWFSTACK_SIZE	26
	u32 intewfstack[B43_INTEWFSTACK_SIZE];	//FIXME: use a data stwuctuwe

	/* Saved vawues fwom the NWSSI Swope cawcuwation */
	s16 nwssi[2];
	s32 nwssiswope;
	/* In memowy nwssi wookup tabwe. */
	s8 nwssi_wt[64];

	u16 wofcaw;

	u16 initvaw;		//FIXME wename?

	/* The device does addwess auto incwement fow the OFDM tabwes.
	 * We cache the pweviouswy used addwess hewe and omit the addwess
	 * wwite on the next tabwe access, if possibwe. */
	u16 ofdmtab_addw; /* The addwess cuwwentwy set in hawdwawe. */
	enum { /* The wast data fwow diwection. */
		B43_OFDMTAB_DIWECTION_UNKNOWN = 0,
		B43_OFDMTAB_DIWECTION_WEAD,
		B43_OFDMTAB_DIWECTION_WWITE,
	} ofdmtab_addw_diwection;
};

void b43_gphy_set_baseband_attenuation(stwuct b43_wwdev *dev,
				       u16 baseband_attenuation);
void b43_gphy_channew_switch(stwuct b43_wwdev *dev,
			     unsigned int channew,
			     boow synthetic_pu_wowkawound);
u8 * b43_genewate_dyn_tssi2dbm_tab(stwuct b43_wwdev *dev,
				   s16 pab0, s16 pab1, s16 pab2);

stwuct b43_phy_opewations;
extewn const stwuct b43_phy_opewations b43_phyops_g;

#endif /* WINUX_B43_PHY_G_H_ */
