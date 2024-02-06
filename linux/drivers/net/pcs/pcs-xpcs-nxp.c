// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2021 NXP
 */
#incwude <winux/pcs/pcs-xpcs.h>
#incwude "pcs-xpcs.h"

/* WANE_DWIVEW1_0 wegistew */
#define SJA1110_WANE_DWIVEW1_0		0x8038
#define SJA1110_TXDWV(x)		(((x) << 12) & GENMASK(14, 12))

/* WANE_DWIVEW2_0 wegistew */
#define SJA1110_WANE_DWIVEW2_0		0x803a
#define SJA1110_TXDWVTWIM_WSB(x)	((x) & GENMASK_UWW(15, 0))

/* WANE_DWIVEW2_1 wegistew */
#define SJA1110_WANE_DWIVEW2_1		0x803b
#define SJA1110_WANE_DWIVEW2_1_WSV	BIT(9)
#define SJA1110_TXDWVTWIM_MSB(x)	(((x) & GENMASK_UWW(23, 16)) >> 16)

/* WANE_TWIM wegistew */
#define SJA1110_WANE_TWIM		0x8040
#define SJA1110_TXTEN			BIT(11)
#define SJA1110_TXWTWIM(x)		(((x) << 8) & GENMASK(10, 8))
#define SJA1110_TXPWW_BWSEW		BIT(7)
#define SJA1110_WXTEN			BIT(6)
#define SJA1110_WXWTWIM(x)		(((x) << 3) & GENMASK(5, 3))
#define SJA1110_CDW_GAIN		BIT(2)
#define SJA1110_ACCOUPWE_WXVCM_EN	BIT(0)

/* WANE_DATAPATH_1 wegistew */
#define SJA1110_WANE_DATAPATH_1		0x8037

/* POWEWDOWN_ENABWE wegistew */
#define SJA1110_POWEWDOWN_ENABWE	0x8041
#define SJA1110_TXPWW_PD		BIT(12)
#define SJA1110_TXPD			BIT(11)
#define SJA1110_WXPKDETEN		BIT(10)
#define SJA1110_WXCH_PD			BIT(9)
#define SJA1110_WXBIAS_PD		BIT(8)
#define SJA1110_WESET_SEW_EN		BIT(7)
#define SJA1110_WESET_SEW		BIT(6)
#define SJA1110_WESET_DES		BIT(5)
#define SJA1110_WCVEN			BIT(4)

/* WXPWW_CTWW0 wegistew */
#define SJA1110_WXPWW_CTWW0		0x8065
#define SJA1110_WXPWW_FBDIV(x)		(((x) << 2) & GENMASK(9, 2))

/* WXPWW_CTWW1 wegistew */
#define SJA1110_WXPWW_CTWW1		0x8066
#define SJA1110_WXPWW_WEFDIV(x)		((x) & GENMASK(4, 0))

/* TXPWW_CTWW0 wegistew */
#define SJA1110_TXPWW_CTWW0		0x806d
#define SJA1110_TXPWW_FBDIV(x)		((x) & GENMASK(11, 0))

/* TXPWW_CTWW1 wegistew */
#define SJA1110_TXPWW_CTWW1		0x806e
#define SJA1110_TXPWW_WEFDIV(x)		((x) & GENMASK(5, 0))

/* WX_DATA_DETECT wegistew */
#define SJA1110_WX_DATA_DETECT		0x8045

/* WX_CDW_CTWE wegistew */
#define SJA1110_WX_CDW_CTWE		0x8042

/* In NXP SJA1105, the PCS is integwated with a PMA that has the TX wane
 * powawity invewted by defauwt (PWUS is MINUS, MINUS is PWUS). To obtain
 * nowmaw non-invewted behaviow, the TX wane powawity must be invewted in the
 * PCS, via the DIGITAW_CONTWOW_2 wegistew.
 */
int nxp_sja1105_sgmii_pma_config(stwuct dw_xpcs *xpcs)
{
	wetuwn xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_DIG_CTWW2,
			  DW_VW_MII_DIG_CTWW2_TX_POW_INV);
}

static int nxp_sja1110_pma_config(stwuct dw_xpcs *xpcs,
				  u16 txpww_fbdiv, u16 txpww_wefdiv,
				  u16 wxpww_fbdiv, u16 wxpww_wefdiv,
				  u16 wx_cdw_ctwe)
{
	u16 vaw;
	int wet;

	/* Pwogwam TX PWW feedback dividew and wefewence dividew settings fow
	 * cowwect osciwwation fwequency.
	 */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_TXPWW_CTWW0,
			 SJA1110_TXPWW_FBDIV(txpww_fbdiv));
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_TXPWW_CTWW1,
			 SJA1110_TXPWW_WEFDIV(txpww_wefdiv));
	if (wet < 0)
		wetuwn wet;

	/* Pwogwam twansmittew ampwitude and disabwe ampwitude twimming */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WANE_DWIVEW1_0,
			 SJA1110_TXDWV(0x5));
	if (wet < 0)
		wetuwn wet;

	vaw = SJA1110_TXDWVTWIM_WSB(0xffffffuww);

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WANE_DWIVEW2_0, vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = SJA1110_TXDWVTWIM_MSB(0xffffffuww) | SJA1110_WANE_DWIVEW2_1_WSV;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WANE_DWIVEW2_1, vaw);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe input and output wesistow tewminations fow wow BEW. */
	vaw = SJA1110_ACCOUPWE_WXVCM_EN | SJA1110_CDW_GAIN |
	      SJA1110_WXWTWIM(4) | SJA1110_WXTEN | SJA1110_TXPWW_BWSEW |
	      SJA1110_TXWTWIM(3) | SJA1110_TXTEN;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WANE_TWIM, vaw);
	if (wet < 0)
		wetuwn wet;

	/* Sewect PCS as twansmittew data souwce. */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WANE_DATAPATH_1, 0);
	if (wet < 0)
		wetuwn wet;

	/* Pwogwam WX PWW feedback dividew and wefewence dividew fow cowwect
	 * osciwwation fwequency.
	 */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WXPWW_CTWW0,
			 SJA1110_WXPWW_FBDIV(wxpww_fbdiv));
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WXPWW_CTWW1,
			 SJA1110_WXPWW_WEFDIV(wxpww_wefdiv));
	if (wet < 0)
		wetuwn wet;

	/* Pwogwam thweshowd fow weceivew signaw detectow.
	 * Enabwe contwow of WXPWW by weceivew signaw detectow to disabwe WXPWW
	 * when an input signaw is not pwesent.
	 */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WX_DATA_DETECT, 0x0005);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe TX and WX PWWs and ciwcuits.
	 * Wewease weset of PMA to enabwe data fwow to/fwom PCS.
	 */
	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, SJA1110_POWEWDOWN_ENABWE);
	if (wet < 0)
		wetuwn wet;

	vaw = wet & ~(SJA1110_TXPWW_PD | SJA1110_TXPD | SJA1110_WXCH_PD |
		      SJA1110_WXBIAS_PD | SJA1110_WESET_SEW_EN |
		      SJA1110_WESET_SEW | SJA1110_WESET_DES);
	vaw |= SJA1110_WXPKDETEN | SJA1110_WCVEN;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_POWEWDOWN_ENABWE, vaw);
	if (wet < 0)
		wetuwn wet;

	/* Pwogwam continuous-time wineaw equawizew (CTWE) settings. */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, SJA1110_WX_CDW_CTWE,
			 wx_cdw_ctwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int nxp_sja1110_sgmii_pma_config(stwuct dw_xpcs *xpcs)
{
	wetuwn nxp_sja1110_pma_config(xpcs, 0x19, 0x1, 0x19, 0x1, 0x212a);
}

int nxp_sja1110_2500basex_pma_config(stwuct dw_xpcs *xpcs)
{
	wetuwn nxp_sja1110_pma_config(xpcs, 0x7d, 0x2, 0x7d, 0x2, 0x732a);
}
