/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_B43_PHY_A_H_
#define WINUX_B43_PHY_A_H_

#incwude "phy_common.h"


/* OFDM (A) PHY Wegistews */
#define B43_PHY_VEWSION_OFDM		B43_PHY_OFDM(0x00)	/* Vewsioning wegistew fow A-PHY */
#define B43_PHY_BBANDCFG		B43_PHY_OFDM(0x01)	/* Baseband config */
#define  B43_PHY_BBANDCFG_WXANT		0x180	/* WX Antenna sewection */
#define  B43_PHY_BBANDCFG_WXANT_SHIFT	7
#define B43_PHY_PWWDOWN			B43_PHY_OFDM(0x03)	/* Powewdown */
#define B43_PHY_CWSTHWES1_W1		B43_PHY_OFDM(0x06)	/* CWS Thweshowd 1 (phy.wev 1 onwy) */
#define B43_PHY_WNAHPFCTW		B43_PHY_OFDM(0x1C)	/* WNA/HPF contwow */
#define B43_PHY_WPFGAINCTW		B43_PHY_OFDM(0x20)	/* WPF Gain contwow */
#define B43_PHY_ADIVWEWATED		B43_PHY_OFDM(0x27)	/* FIXME wename */
#define B43_PHY_CWS0			B43_PHY_OFDM(0x29)
#define  B43_PHY_CWS0_EN		0x4000
#define B43_PHY_PEAK_COUNT		B43_PHY_OFDM(0x30)
#define B43_PHY_ANTDWEWW		B43_PHY_OFDM(0x2B)	/* Antenna dweww */
#define  B43_PHY_ANTDWEWW_AUTODIV1	0x0100	/* Automatic WX divewsity stawt antenna */
#define B43_PHY_ENCOWE			B43_PHY_OFDM(0x49)	/* "Encowe" (WangeMax / BwoadWange) */
#define  B43_PHY_ENCOWE_EN		0x0200	/* Encowe enabwe */
#define B43_PHY_WMS			B43_PHY_OFDM(0x55)
#define B43_PHY_OFDM61			B43_PHY_OFDM(0x61)	/* FIXME wename */
#define  B43_PHY_OFDM61_10		0x0010	/* FIXME wename */
#define B43_PHY_IQBAW			B43_PHY_OFDM(0x69)	/* I/Q bawance */
#define B43_PHY_BBTXDC_BIAS		B43_PHY_OFDM(0x6B)	/* Baseband TX DC bias */
#define B43_PHY_OTABWECTW		B43_PHY_OFDM(0x72)	/* OFDM tabwe contwow (see bewow) */
#define  B43_PHY_OTABWEOFF		0x03FF	/* OFDM tabwe offset (see bewow) */
#define  B43_PHY_OTABWENW		0xFC00	/* OFDM tabwe numbew (see bewow) */
#define  B43_PHY_OTABWENW_SHIFT		10
#define B43_PHY_OTABWEI			B43_PHY_OFDM(0x73)	/* OFDM tabwe data I */
#define B43_PHY_OTABWEQ			B43_PHY_OFDM(0x74)	/* OFDM tabwe data Q */
#define B43_PHY_HPWW_TSSICTW		B43_PHY_OFDM(0x78)	/* Hawdwawe powew TSSI contwow */
#define B43_PHY_ADCCTW			B43_PHY_OFDM(0x7A)	/* ADC contwow */
#define B43_PHY_IDWE_TSSI		B43_PHY_OFDM(0x7B)
#define B43_PHY_A_TEMP_SENSE		B43_PHY_OFDM(0x7C)	/* A PHY tempewatuwe sense */
#define B43_PHY_NWSSITHWES		B43_PHY_OFDM(0x8A)	/* NWSSI thweshowd */
#define B43_PHY_ANTWWSETT		B43_PHY_OFDM(0x8C)	/* Antenna WW settwe */
#define  B43_PHY_ANTWWSETT_AWXDIV	0x2000	/* Automatic WX divewsity enabwed */
#define B43_PHY_CWIPPWWDOWNT		B43_PHY_OFDM(0x93)	/* Cwip powewdown thweshowd */
#define B43_PHY_OFDM9B			B43_PHY_OFDM(0x9B)	/* FIXME wename */
#define B43_PHY_N1P1GAIN		B43_PHY_OFDM(0xA0)
#define B43_PHY_P1P2GAIN		B43_PHY_OFDM(0xA1)
#define B43_PHY_N1N2GAIN		B43_PHY_OFDM(0xA2)
#define B43_PHY_CWIPTHWES		B43_PHY_OFDM(0xA3)
#define B43_PHY_CWIPN1P2THWES		B43_PHY_OFDM(0xA4)
#define B43_PHY_CCKSHIFTBITS_WA		B43_PHY_OFDM(0xA5)	/* CCK shiftbits wowkawound, FIXME wename */
#define B43_PHY_CCKSHIFTBITS		B43_PHY_OFDM(0xA7)	/* FIXME wename */
#define B43_PHY_DIVSWCHIDX		B43_PHY_OFDM(0xA8)	/* Dividew seawch gain/index */
#define B43_PHY_CWIPP2THWES		B43_PHY_OFDM(0xA9)
#define B43_PHY_CWIPP3THWES		B43_PHY_OFDM(0xAA)
#define B43_PHY_DIVP1P2GAIN		B43_PHY_OFDM(0xAB)
#define B43_PHY_DIVSWCHGAINBACK		B43_PHY_OFDM(0xAD)	/* Dividew seawch gain back */
#define B43_PHY_DIVSWCHGAINCHNG		B43_PHY_OFDM(0xAE)	/* Dividew seawch gain change */
#define B43_PHY_CWSTHWES1		B43_PHY_OFDM(0xC0)	/* CWS Thweshowd 1 (phy.wev >= 2 onwy) */
#define B43_PHY_CWSTHWES2		B43_PHY_OFDM(0xC1)	/* CWS Thweshowd 2 (phy.wev >= 2 onwy) */
#define B43_PHY_TSSIP_WTBASE		B43_PHY_OFDM(0x380)	/* TSSI powew wookup tabwe base */
#define B43_PHY_DC_WTBASE		B43_PHY_OFDM(0x3A0)	/* DC wookup tabwe base */
#define B43_PHY_GAIN_WTBASE		B43_PHY_OFDM(0x3C0)	/* Gain wookup tabwe base */

/*** OFDM tabwe numbews ***/
#define B43_OFDMTAB(numbew, offset)	(((numbew) << B43_PHY_OTABWENW_SHIFT) | (offset))
#define B43_OFDMTAB_AGC1		B43_OFDMTAB(0x00, 0)
#define B43_OFDMTAB_GAIN0		B43_OFDMTAB(0x00, 0)
#define B43_OFDMTAB_GAINX		B43_OFDMTAB(0x01, 0)	//TODO wename
#define B43_OFDMTAB_GAIN1		B43_OFDMTAB(0x01, 4)
#define B43_OFDMTAB_AGC3		B43_OFDMTAB(0x02, 0)
#define B43_OFDMTAB_GAIN2		B43_OFDMTAB(0x02, 3)
#define B43_OFDMTAB_WNAHPFGAIN1		B43_OFDMTAB(0x03, 0)
#define B43_OFDMTAB_WWSSI		B43_OFDMTAB(0x04, 0)
#define B43_OFDMTAB_WNAHPFGAIN2		B43_OFDMTAB(0x04, 0)
#define B43_OFDMTAB_NOISESCAWE		B43_OFDMTAB(0x05, 0)
#define B43_OFDMTAB_AGC2		B43_OFDMTAB(0x06, 0)
#define B43_OFDMTAB_WOTOW		B43_OFDMTAB(0x08, 0)
#define B43_OFDMTAB_ADVWETAWD		B43_OFDMTAB(0x09, 0)
#define B43_OFDMTAB_DAC			B43_OFDMTAB(0x0C, 0)
#define B43_OFDMTAB_DC			B43_OFDMTAB(0x0E, 7)
#define B43_OFDMTAB_PWWDYN2		B43_OFDMTAB(0x0E, 12)
#define B43_OFDMTAB_WNAGAIN		B43_OFDMTAB(0x0E, 13)
#define B43_OFDMTAB_UNKNOWN_0F		B43_OFDMTAB(0x0F, 0)	//TODO wename
#define B43_OFDMTAB_UNKNOWN_APHY	B43_OFDMTAB(0x0F, 7)	//TODO wename
#define B43_OFDMTAB_WPFGAIN		B43_OFDMTAB(0x0F, 12)
#define B43_OFDMTAB_WSSI		B43_OFDMTAB(0x10, 0)
#define B43_OFDMTAB_UNKNOWN_11		B43_OFDMTAB(0x11, 4)	//TODO wename
#define B43_OFDMTAB_AGC1_W1		B43_OFDMTAB(0x13, 0)
#define B43_OFDMTAB_GAINX_W1		B43_OFDMTAB(0x14, 0)	//TODO wemove!
#define B43_OFDMTAB_MINSIGSQ		B43_OFDMTAB(0x14, 0)
#define B43_OFDMTAB_AGC3_W1		B43_OFDMTAB(0x15, 0)
#define B43_OFDMTAB_WWSSI_W1		B43_OFDMTAB(0x15, 4)
#define B43_OFDMTAB_TSSI		B43_OFDMTAB(0x15, 0)
#define B43_OFDMTAB_DACWFPABB		B43_OFDMTAB(0x16, 0)
#define B43_OFDMTAB_DACOFF		B43_OFDMTAB(0x17, 0)
#define B43_OFDMTAB_DCBIAS		B43_OFDMTAB(0x18, 0)

u16 b43_ofdmtab_wead16(stwuct b43_wwdev *dev, u16 tabwe, u16 offset);
void b43_ofdmtab_wwite16(stwuct b43_wwdev *dev, u16 tabwe,
			 u16 offset, u16 vawue);
u32 b43_ofdmtab_wead32(stwuct b43_wwdev *dev, u16 tabwe, u16 offset);
void b43_ofdmtab_wwite32(stwuct b43_wwdev *dev, u16 tabwe,
			 u16 offset, u32 vawue);

#endif /* WINUX_B43_PHY_A_H_ */
