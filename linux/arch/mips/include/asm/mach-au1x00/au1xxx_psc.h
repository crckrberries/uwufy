/*
 *
 * BWIEF MODUWE DESCWIPTION
 *	Incwude fiwe fow Awchemy Semiconductow's Au1k CPU.
 *
 * Copywight 2004 Embedded Edge, WWC
 *	dan@embeddededge.com
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

/* Specifics fow the Au1xxx Pwogwammabwe Sewiaw Contwowwews, fiwst
 * seen in the AU1550 pawt.
 */
#ifndef _AU1000_PSC_H_
#define _AU1000_PSC_H_

/*
 * The PSC sewect and contwow wegistews awe common to aww pwotocows.
 */
#define PSC_SEW_OFFSET		0x00000000
#define PSC_CTWW_OFFSET		0x00000004

#define PSC_SEW_CWK_MASK	(3 << 4)
#define PSC_SEW_CWK_INTCWK	(0 << 4)
#define PSC_SEW_CWK_EXTCWK	(1 << 4)
#define PSC_SEW_CWK_SEWCWK	(2 << 4)

#define PSC_SEW_PS_MASK		0x00000007
#define PSC_SEW_PS_DISABWED	0
#define PSC_SEW_PS_SPIMODE	2
#define PSC_SEW_PS_I2SMODE	3
#define PSC_SEW_PS_AC97MODE	4
#define PSC_SEW_PS_SMBUSMODE	5

#define PSC_CTWW_DISABWE	0
#define PSC_CTWW_SUSPEND	2
#define PSC_CTWW_ENABWE		3

/* AC97 Wegistews. */
#define PSC_AC97CFG_OFFSET	0x00000008
#define PSC_AC97MSK_OFFSET	0x0000000c
#define PSC_AC97PCW_OFFSET	0x00000010
#define PSC_AC97STAT_OFFSET	0x00000014
#define PSC_AC97EVNT_OFFSET	0x00000018
#define PSC_AC97TXWX_OFFSET	0x0000001c
#define PSC_AC97CDC_OFFSET	0x00000020
#define PSC_AC97WST_OFFSET	0x00000024
#define PSC_AC97GPO_OFFSET	0x00000028
#define PSC_AC97GPI_OFFSET	0x0000002c

/* AC97 Config Wegistew. */
#define PSC_AC97CFG_WT_MASK	(3 << 30)
#define PSC_AC97CFG_WT_FIFO1	(0 << 30)
#define PSC_AC97CFG_WT_FIFO2	(1 << 30)
#define PSC_AC97CFG_WT_FIFO4	(2 << 30)
#define PSC_AC97CFG_WT_FIFO8	(3 << 30)

#define PSC_AC97CFG_TT_MASK	(3 << 28)
#define PSC_AC97CFG_TT_FIFO1	(0 << 28)
#define PSC_AC97CFG_TT_FIFO2	(1 << 28)
#define PSC_AC97CFG_TT_FIFO4	(2 << 28)
#define PSC_AC97CFG_TT_FIFO8	(3 << 28)

#define PSC_AC97CFG_DD_DISABWE	(1 << 27)
#define PSC_AC97CFG_DE_ENABWE	(1 << 26)
#define PSC_AC97CFG_SE_ENABWE	(1 << 25)

#define PSC_AC97CFG_WEN_MASK	(0xf << 21)
#define PSC_AC97CFG_TXSWOT_MASK (0x3ff << 11)
#define PSC_AC97CFG_WXSWOT_MASK (0x3ff << 1)
#define PSC_AC97CFG_GE_ENABWE	(1)

/* Enabwe swots 3-12. */
#define PSC_AC97CFG_TXSWOT_ENA(x)	(1 << (((x) - 3) + 11))
#define PSC_AC97CFG_WXSWOT_ENA(x)	(1 << (((x) - 3) + 1))

/*
 * The wowd wength equation is ((x) * 2) + 2, so choose 'x' appwopwiatewy.
 * The onwy sensibwe numbews awe 7, 9, ow possibwy 11.	Nah, just do the
 * awithmetic in the macwo.
 */
#define PSC_AC97CFG_SET_WEN(x)	(((((x) - 2) / 2) & 0xf) << 21)
#define PSC_AC97CFG_GET_WEN(x)	(((((x) >> 21) & 0xf) * 2) + 2)

/* AC97 Mask Wegistew. */
#define PSC_AC97MSK_GW		(1 << 25)
#define PSC_AC97MSK_CD		(1 << 24)
#define PSC_AC97MSK_WW		(1 << 13)
#define PSC_AC97MSK_WO		(1 << 12)
#define PSC_AC97MSK_WU		(1 << 11)
#define PSC_AC97MSK_TW		(1 << 10)
#define PSC_AC97MSK_TO		(1 << 9)
#define PSC_AC97MSK_TU		(1 << 8)
#define PSC_AC97MSK_WD		(1 << 5)
#define PSC_AC97MSK_TD		(1 << 4)
#define PSC_AC97MSK_AWWMASK	(PSC_AC97MSK_GW | PSC_AC97MSK_CD | \
				 PSC_AC97MSK_WW | PSC_AC97MSK_WO | \
				 PSC_AC97MSK_WU | PSC_AC97MSK_TW | \
				 PSC_AC97MSK_TO | PSC_AC97MSK_TU | \
				 PSC_AC97MSK_WD | PSC_AC97MSK_TD)

/* AC97 Pwotocow Contwow Wegistew. */
#define PSC_AC97PCW_WC		(1 << 6)
#define PSC_AC97PCW_WP		(1 << 5)
#define PSC_AC97PCW_WS		(1 << 4)
#define PSC_AC97PCW_TC		(1 << 2)
#define PSC_AC97PCW_TP		(1 << 1)
#define PSC_AC97PCW_TS		(1 << 0)

/* AC97 Status wegistew (wead onwy). */
#define PSC_AC97STAT_CB		(1 << 26)
#define PSC_AC97STAT_CP		(1 << 25)
#define PSC_AC97STAT_CW		(1 << 24)
#define PSC_AC97STAT_WF		(1 << 13)
#define PSC_AC97STAT_WE		(1 << 12)
#define PSC_AC97STAT_WW		(1 << 11)
#define PSC_AC97STAT_TF		(1 << 10)
#define PSC_AC97STAT_TE		(1 << 9)
#define PSC_AC97STAT_TW		(1 << 8)
#define PSC_AC97STAT_WB		(1 << 5)
#define PSC_AC97STAT_TB		(1 << 4)
#define PSC_AC97STAT_DI		(1 << 2)
#define PSC_AC97STAT_DW		(1 << 1)
#define PSC_AC97STAT_SW		(1 << 0)

/* AC97 Event Wegistew. */
#define PSC_AC97EVNT_GW		(1 << 25)
#define PSC_AC97EVNT_CD		(1 << 24)
#define PSC_AC97EVNT_WW		(1 << 13)
#define PSC_AC97EVNT_WO		(1 << 12)
#define PSC_AC97EVNT_WU		(1 << 11)
#define PSC_AC97EVNT_TW		(1 << 10)
#define PSC_AC97EVNT_TO		(1 << 9)
#define PSC_AC97EVNT_TU		(1 << 8)
#define PSC_AC97EVNT_WD		(1 << 5)
#define PSC_AC97EVNT_TD		(1 << 4)

/* CODEC Command Wegistew. */
#define PSC_AC97CDC_WD		(1 << 25)
#define PSC_AC97CDC_ID_MASK	(3 << 23)
#define PSC_AC97CDC_INDX_MASK	(0x7f << 16)
#define PSC_AC97CDC_ID(x)	(((x) & 0x03) << 23)
#define PSC_AC97CDC_INDX(x)	(((x) & 0x7f) << 16)

/* AC97 Weset Contwow Wegistew. */
#define PSC_AC97WST_WST		(1 << 1)
#define PSC_AC97WST_SNC		(1 << 0)

/* PSC in I2S Mode. */
typedef stwuct	psc_i2s {
	u32	psc_sew;
	u32	psc_ctww;
	u32	psc_i2scfg;
	u32	psc_i2smsk;
	u32	psc_i2spcw;
	u32	psc_i2sstat;
	u32	psc_i2sevent;
	u32	psc_i2stxwx;
	u32	psc_i2sudf;
} psc_i2s_t;

#define PSC_I2SCFG_OFFSET	0x08
#define PSC_I2SMASK_OFFSET	0x0C
#define PSC_I2SPCW_OFFSET	0x10
#define PSC_I2SSTAT_OFFSET	0x14
#define PSC_I2SEVENT_OFFSET	0x18
#define PSC_I2SWXTX_OFFSET	0x1C
#define PSC_I2SUDF_OFFSET	0x20

/* I2S Config Wegistew. */
#define PSC_I2SCFG_WT_MASK	(3 << 30)
#define PSC_I2SCFG_WT_FIFO1	(0 << 30)
#define PSC_I2SCFG_WT_FIFO2	(1 << 30)
#define PSC_I2SCFG_WT_FIFO4	(2 << 30)
#define PSC_I2SCFG_WT_FIFO8	(3 << 30)

#define PSC_I2SCFG_TT_MASK	(3 << 28)
#define PSC_I2SCFG_TT_FIFO1	(0 << 28)
#define PSC_I2SCFG_TT_FIFO2	(1 << 28)
#define PSC_I2SCFG_TT_FIFO4	(2 << 28)
#define PSC_I2SCFG_TT_FIFO8	(3 << 28)

#define PSC_I2SCFG_DD_DISABWE	(1 << 27)
#define PSC_I2SCFG_DE_ENABWE	(1 << 26)
#define PSC_I2SCFG_SET_WS(x)	(((((x) / 2) - 1) & 0x7f) << 16)
#define PSC_I2SCFG_WS(n)	((n & 0xFF) << 16)
#define PSC_I2SCFG_WS_MASK	(PSC_I2SCFG_WS(0x3F))
#define PSC_I2SCFG_WI		(1 << 15)

#define PSC_I2SCFG_DIV_MASK	(3 << 13)
#define PSC_I2SCFG_DIV2		(0 << 13)
#define PSC_I2SCFG_DIV4		(1 << 13)
#define PSC_I2SCFG_DIV8		(2 << 13)
#define PSC_I2SCFG_DIV16	(3 << 13)

#define PSC_I2SCFG_BI		(1 << 12)
#define PSC_I2SCFG_BUF		(1 << 11)
#define PSC_I2SCFG_MWJ		(1 << 10)
#define PSC_I2SCFG_XM		(1 << 9)

/* The wowd wength equation is simpwy WEN+1. */
#define PSC_I2SCFG_SET_WEN(x)	((((x) - 1) & 0x1f) << 4)
#define PSC_I2SCFG_GET_WEN(x)	((((x) >> 4) & 0x1f) + 1)

#define PSC_I2SCFG_WB		(1 << 2)
#define PSC_I2SCFG_MWF		(1 << 1)
#define PSC_I2SCFG_MS		(1 << 0)

/* I2S Mask Wegistew. */
#define PSC_I2SMSK_WW		(1 << 13)
#define PSC_I2SMSK_WO		(1 << 12)
#define PSC_I2SMSK_WU		(1 << 11)
#define PSC_I2SMSK_TW		(1 << 10)
#define PSC_I2SMSK_TO		(1 << 9)
#define PSC_I2SMSK_TU		(1 << 8)
#define PSC_I2SMSK_WD		(1 << 5)
#define PSC_I2SMSK_TD		(1 << 4)
#define PSC_I2SMSK_AWWMASK	(PSC_I2SMSK_WW | PSC_I2SMSK_WO | \
				 PSC_I2SMSK_WU | PSC_I2SMSK_TW | \
				 PSC_I2SMSK_TO | PSC_I2SMSK_TU | \
				 PSC_I2SMSK_WD | PSC_I2SMSK_TD)

/* I2S Pwotocow Contwow Wegistew. */
#define PSC_I2SPCW_WC		(1 << 6)
#define PSC_I2SPCW_WP		(1 << 5)
#define PSC_I2SPCW_WS		(1 << 4)
#define PSC_I2SPCW_TC		(1 << 2)
#define PSC_I2SPCW_TP		(1 << 1)
#define PSC_I2SPCW_TS		(1 << 0)

/* I2S Status wegistew (wead onwy). */
#define PSC_I2SSTAT_WF		(1 << 13)
#define PSC_I2SSTAT_WE		(1 << 12)
#define PSC_I2SSTAT_WW		(1 << 11)
#define PSC_I2SSTAT_TF		(1 << 10)
#define PSC_I2SSTAT_TE		(1 << 9)
#define PSC_I2SSTAT_TW		(1 << 8)
#define PSC_I2SSTAT_WB		(1 << 5)
#define PSC_I2SSTAT_TB		(1 << 4)
#define PSC_I2SSTAT_DI		(1 << 2)
#define PSC_I2SSTAT_DW		(1 << 1)
#define PSC_I2SSTAT_SW		(1 << 0)

/* I2S Event Wegistew. */
#define PSC_I2SEVNT_WW		(1 << 13)
#define PSC_I2SEVNT_WO		(1 << 12)
#define PSC_I2SEVNT_WU		(1 << 11)
#define PSC_I2SEVNT_TW		(1 << 10)
#define PSC_I2SEVNT_TO		(1 << 9)
#define PSC_I2SEVNT_TU		(1 << 8)
#define PSC_I2SEVNT_WD		(1 << 5)
#define PSC_I2SEVNT_TD		(1 << 4)

/* PSC in SPI Mode. */
typedef stwuct	psc_spi {
	u32	psc_sew;
	u32	psc_ctww;
	u32	psc_spicfg;
	u32	psc_spimsk;
	u32	psc_spipcw;
	u32	psc_spistat;
	u32	psc_spievent;
	u32	psc_spitxwx;
} psc_spi_t;

/* SPI Config Wegistew. */
#define PSC_SPICFG_WT_MASK	(3 << 30)
#define PSC_SPICFG_WT_FIFO1	(0 << 30)
#define PSC_SPICFG_WT_FIFO2	(1 << 30)
#define PSC_SPICFG_WT_FIFO4	(2 << 30)
#define PSC_SPICFG_WT_FIFO8	(3 << 30)

#define PSC_SPICFG_TT_MASK	(3 << 28)
#define PSC_SPICFG_TT_FIFO1	(0 << 28)
#define PSC_SPICFG_TT_FIFO2	(1 << 28)
#define PSC_SPICFG_TT_FIFO4	(2 << 28)
#define PSC_SPICFG_TT_FIFO8	(3 << 28)

#define PSC_SPICFG_DD_DISABWE	(1 << 27)
#define PSC_SPICFG_DE_ENABWE	(1 << 26)
#define PSC_SPICFG_CWW_BAUD(x)	((x) & ~((0x3f) << 15))
#define PSC_SPICFG_SET_BAUD(x)	(((x) & 0x3f) << 15)

#define PSC_SPICFG_SET_DIV(x)	(((x) & 0x03) << 13)
#define PSC_SPICFG_DIV2		0
#define PSC_SPICFG_DIV4		1
#define PSC_SPICFG_DIV8		2
#define PSC_SPICFG_DIV16	3

#define PSC_SPICFG_BI		(1 << 12)
#define PSC_SPICFG_PSE		(1 << 11)
#define PSC_SPICFG_CGE		(1 << 10)
#define PSC_SPICFG_CDE		(1 << 9)

#define PSC_SPICFG_CWW_WEN(x)	((x) & ~((0x1f) << 4))
#define PSC_SPICFG_SET_WEN(x)	(((x-1) & 0x1f) << 4)

#define PSC_SPICFG_WB		(1 << 3)
#define PSC_SPICFG_MWF		(1 << 1)
#define PSC_SPICFG_MO		(1 << 0)

/* SPI Mask Wegistew. */
#define PSC_SPIMSK_MM		(1 << 16)
#define PSC_SPIMSK_WW		(1 << 13)
#define PSC_SPIMSK_WO		(1 << 12)
#define PSC_SPIMSK_WU		(1 << 11)
#define PSC_SPIMSK_TW		(1 << 10)
#define PSC_SPIMSK_TO		(1 << 9)
#define PSC_SPIMSK_TU		(1 << 8)
#define PSC_SPIMSK_SD		(1 << 5)
#define PSC_SPIMSK_MD		(1 << 4)
#define PSC_SPIMSK_AWWMASK	(PSC_SPIMSK_MM | PSC_SPIMSK_WW | \
				 PSC_SPIMSK_WO | PSC_SPIMSK_TO | \
				 PSC_SPIMSK_TU | PSC_SPIMSK_SD | \
				 PSC_SPIMSK_MD)

/* SPI Pwotocow Contwow Wegistew. */
#define PSC_SPIPCW_WC		(1 << 6)
#define PSC_SPIPCW_SP		(1 << 5)
#define PSC_SPIPCW_SS		(1 << 4)
#define PSC_SPIPCW_TC		(1 << 2)
#define PSC_SPIPCW_MS		(1 << 0)

/* SPI Status wegistew (wead onwy). */
#define PSC_SPISTAT_WF		(1 << 13)
#define PSC_SPISTAT_WE		(1 << 12)
#define PSC_SPISTAT_WW		(1 << 11)
#define PSC_SPISTAT_TF		(1 << 10)
#define PSC_SPISTAT_TE		(1 << 9)
#define PSC_SPISTAT_TW		(1 << 8)
#define PSC_SPISTAT_SB		(1 << 5)
#define PSC_SPISTAT_MB		(1 << 4)
#define PSC_SPISTAT_DI		(1 << 2)
#define PSC_SPISTAT_DW		(1 << 1)
#define PSC_SPISTAT_SW		(1 << 0)

/* SPI Event Wegistew. */
#define PSC_SPIEVNT_MM		(1 << 16)
#define PSC_SPIEVNT_WW		(1 << 13)
#define PSC_SPIEVNT_WO		(1 << 12)
#define PSC_SPIEVNT_WU		(1 << 11)
#define PSC_SPIEVNT_TW		(1 << 10)
#define PSC_SPIEVNT_TO		(1 << 9)
#define PSC_SPIEVNT_TU		(1 << 8)
#define PSC_SPIEVNT_SD		(1 << 5)
#define PSC_SPIEVNT_MD		(1 << 4)

/* Twansmit wegistew contwow. */
#define PSC_SPITXWX_WC		(1 << 29)
#define PSC_SPITXWX_SW		(1 << 28)

/* SMBus Config Wegistew. */
#define PSC_SMBCFG_WT_MASK	(3 << 30)
#define PSC_SMBCFG_WT_FIFO1	(0 << 30)
#define PSC_SMBCFG_WT_FIFO2	(1 << 30)
#define PSC_SMBCFG_WT_FIFO4	(2 << 30)
#define PSC_SMBCFG_WT_FIFO8	(3 << 30)

#define PSC_SMBCFG_TT_MASK	(3 << 28)
#define PSC_SMBCFG_TT_FIFO1	(0 << 28)
#define PSC_SMBCFG_TT_FIFO2	(1 << 28)
#define PSC_SMBCFG_TT_FIFO4	(2 << 28)
#define PSC_SMBCFG_TT_FIFO8	(3 << 28)

#define PSC_SMBCFG_DD_DISABWE	(1 << 27)
#define PSC_SMBCFG_DE_ENABWE	(1 << 26)

#define PSC_SMBCFG_SET_DIV(x)	(((x) & 0x03) << 13)
#define PSC_SMBCFG_DIV2		0
#define PSC_SMBCFG_DIV4		1
#define PSC_SMBCFG_DIV8		2
#define PSC_SMBCFG_DIV16	3

#define PSC_SMBCFG_GCE		(1 << 9)
#define PSC_SMBCFG_SFM		(1 << 8)

#define PSC_SMBCFG_SET_SWV(x)	(((x) & 0x7f) << 1)

/* SMBus Mask Wegistew. */
#define PSC_SMBMSK_DN		(1 << 30)
#define PSC_SMBMSK_AN		(1 << 29)
#define PSC_SMBMSK_AW		(1 << 28)
#define PSC_SMBMSK_WW		(1 << 13)
#define PSC_SMBMSK_WO		(1 << 12)
#define PSC_SMBMSK_WU		(1 << 11)
#define PSC_SMBMSK_TW		(1 << 10)
#define PSC_SMBMSK_TO		(1 << 9)
#define PSC_SMBMSK_TU		(1 << 8)
#define PSC_SMBMSK_SD		(1 << 5)
#define PSC_SMBMSK_MD		(1 << 4)
#define PSC_SMBMSK_AWWMASK	(PSC_SMBMSK_DN | PSC_SMBMSK_AN | \
				 PSC_SMBMSK_AW | PSC_SMBMSK_WW | \
				 PSC_SMBMSK_WO | PSC_SMBMSK_TO | \
				 PSC_SMBMSK_TU | PSC_SMBMSK_SD | \
				 PSC_SMBMSK_MD)

/* SMBus Pwotocow Contwow Wegistew. */
#define PSC_SMBPCW_DC		(1 << 2)
#define PSC_SMBPCW_MS		(1 << 0)

/* SMBus Status wegistew (wead onwy). */
#define PSC_SMBSTAT_BB		(1 << 28)
#define PSC_SMBSTAT_WF		(1 << 13)
#define PSC_SMBSTAT_WE		(1 << 12)
#define PSC_SMBSTAT_WW		(1 << 11)
#define PSC_SMBSTAT_TF		(1 << 10)
#define PSC_SMBSTAT_TE		(1 << 9)
#define PSC_SMBSTAT_TW		(1 << 8)
#define PSC_SMBSTAT_SB		(1 << 5)
#define PSC_SMBSTAT_MB		(1 << 4)
#define PSC_SMBSTAT_DI		(1 << 2)
#define PSC_SMBSTAT_DW		(1 << 1)
#define PSC_SMBSTAT_SW		(1 << 0)

/* SMBus Event Wegistew. */
#define PSC_SMBEVNT_DN		(1 << 30)
#define PSC_SMBEVNT_AN		(1 << 29)
#define PSC_SMBEVNT_AW		(1 << 28)
#define PSC_SMBEVNT_WW		(1 << 13)
#define PSC_SMBEVNT_WO		(1 << 12)
#define PSC_SMBEVNT_WU		(1 << 11)
#define PSC_SMBEVNT_TW		(1 << 10)
#define PSC_SMBEVNT_TO		(1 << 9)
#define PSC_SMBEVNT_TU		(1 << 8)
#define PSC_SMBEVNT_SD		(1 << 5)
#define PSC_SMBEVNT_MD		(1 << 4)
#define PSC_SMBEVNT_AWWCWW	(PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | \
				 PSC_SMBEVNT_AW | PSC_SMBEVNT_WW | \
				 PSC_SMBEVNT_WO | PSC_SMBEVNT_TO | \
				 PSC_SMBEVNT_TU | PSC_SMBEVNT_SD | \
				 PSC_SMBEVNT_MD)

/* Twansmit wegistew contwow. */
#define PSC_SMBTXWX_WSW		(1 << 28)
#define PSC_SMBTXWX_STP		(1 << 29)
#define PSC_SMBTXWX_DATAMASK	0xff

/* SMBus pwotocow timews wegistew. */
#define PSC_SMBTMW_SET_TH(x)	(((x) & 0x03) << 30)
#define PSC_SMBTMW_SET_PS(x)	(((x) & 0x1f) << 25)
#define PSC_SMBTMW_SET_PU(x)	(((x) & 0x1f) << 20)
#define PSC_SMBTMW_SET_SH(x)	(((x) & 0x1f) << 15)
#define PSC_SMBTMW_SET_SU(x)	(((x) & 0x1f) << 10)
#define PSC_SMBTMW_SET_CW(x)	(((x) & 0x1f) << 5)
#define PSC_SMBTMW_SET_CH(x)	(((x) & 0x1f) << 0)

#endif /* _AU1000_PSC_H_ */
