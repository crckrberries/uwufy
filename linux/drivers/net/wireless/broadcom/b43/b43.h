/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_H_
#define B43_H_

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/ssb/ssb.h>
#incwude <winux/compwetion.h>
#incwude <net/mac80211.h>

#incwude "debugfs.h"
#incwude "weds.h"
#incwude "wfkiww.h"
#incwude "bus.h"
#incwude "wo.h"
#incwude "phy_common.h"


#ifdef CONFIG_B43_DEBUG
# define B43_DEBUG	1
#ewse
# define B43_DEBUG	0
#endif

/* MMIO offsets */
#define B43_MMIO_DMA0_WEASON		0x20
#define B43_MMIO_DMA0_IWQ_MASK		0x24
#define B43_MMIO_DMA1_WEASON		0x28
#define B43_MMIO_DMA1_IWQ_MASK		0x2C
#define B43_MMIO_DMA2_WEASON		0x30
#define B43_MMIO_DMA2_IWQ_MASK		0x34
#define B43_MMIO_DMA3_WEASON		0x38
#define B43_MMIO_DMA3_IWQ_MASK		0x3C
#define B43_MMIO_DMA4_WEASON		0x40
#define B43_MMIO_DMA4_IWQ_MASK		0x44
#define B43_MMIO_DMA5_WEASON		0x48
#define B43_MMIO_DMA5_IWQ_MASK		0x4C
#define B43_MMIO_MACCTW			0x120	/* MAC contwow */
#define B43_MMIO_MACCMD			0x124	/* MAC command */
#define B43_MMIO_GEN_IWQ_WEASON		0x128
#define B43_MMIO_GEN_IWQ_MASK		0x12C
#define B43_MMIO_WAM_CONTWOW		0x130
#define B43_MMIO_WAM_DATA		0x134
#define B43_MMIO_PS_STATUS		0x140
#define B43_MMIO_WADIO_HWENABWED_HI	0x158
#define B43_MMIO_MAC_HW_CAP		0x15C	/* MAC capabiwities (cowewev >= 13) */
#define B43_MMIO_SHM_CONTWOW		0x160
#define B43_MMIO_SHM_DATA		0x164
#define B43_MMIO_SHM_DATA_UNAWIGNED	0x166
#define B43_MMIO_XMITSTAT_0		0x170
#define B43_MMIO_XMITSTAT_1		0x174
#define B43_MMIO_WEV3PWUS_TSF_WOW	0x180	/* cowe wev >= 3 onwy */
#define B43_MMIO_WEV3PWUS_TSF_HIGH	0x184	/* cowe wev >= 3 onwy */
#define B43_MMIO_TSF_CFP_WEP		0x188
#define B43_MMIO_TSF_CFP_STAWT		0x18C
#define B43_MMIO_TSF_CFP_MAXDUW		0x190

/* 32-bit DMA */
#define B43_MMIO_DMA32_BASE0		0x200
#define B43_MMIO_DMA32_BASE1		0x220
#define B43_MMIO_DMA32_BASE2		0x240
#define B43_MMIO_DMA32_BASE3		0x260
#define B43_MMIO_DMA32_BASE4		0x280
#define B43_MMIO_DMA32_BASE5		0x2A0
/* 64-bit DMA */
#define B43_MMIO_DMA64_BASE0		0x200
#define B43_MMIO_DMA64_BASE1		0x240
#define B43_MMIO_DMA64_BASE2		0x280
#define B43_MMIO_DMA64_BASE3		0x2C0
#define B43_MMIO_DMA64_BASE4		0x300
#define B43_MMIO_DMA64_BASE5		0x340

/* PIO on cowe wev < 11 */
#define B43_MMIO_PIO_BASE0		0x300
#define B43_MMIO_PIO_BASE1		0x310
#define B43_MMIO_PIO_BASE2		0x320
#define B43_MMIO_PIO_BASE3		0x330
#define B43_MMIO_PIO_BASE4		0x340
#define B43_MMIO_PIO_BASE5		0x350
#define B43_MMIO_PIO_BASE6		0x360
#define B43_MMIO_PIO_BASE7		0x370
/* PIO on cowe wev >= 11 */
#define B43_MMIO_PIO11_BASE0		0x200
#define B43_MMIO_PIO11_BASE1		0x240
#define B43_MMIO_PIO11_BASE2		0x280
#define B43_MMIO_PIO11_BASE3		0x2C0
#define B43_MMIO_PIO11_BASE4		0x300
#define B43_MMIO_PIO11_BASE5		0x340

#define B43_MMIO_WADIO24_CONTWOW	0x3D8	/* cowe wev >= 24 onwy */
#define B43_MMIO_WADIO24_DATA		0x3DA	/* cowe wev >= 24 onwy */
#define B43_MMIO_PHY_VEW		0x3E0
#define B43_MMIO_PHY_WADIO		0x3E2
#define B43_MMIO_PHY0			0x3E6
#define B43_MMIO_ANTENNA		0x3E8
#define B43_MMIO_CHANNEW		0x3F0
#define B43_MMIO_CHANNEW_EXT		0x3F4
#define B43_MMIO_WADIO_CONTWOW		0x3F6
#define B43_MMIO_WADIO_DATA_HIGH	0x3F8
#define B43_MMIO_WADIO_DATA_WOW		0x3FA
#define B43_MMIO_PHY_CONTWOW		0x3FC
#define B43_MMIO_PHY_DATA		0x3FE
#define B43_MMIO_MACFIWTEW_CONTWOW	0x420
#define B43_MMIO_MACFIWTEW_DATA		0x422
#define B43_MMIO_WCMTA_COUNT		0x43C
#define B43_MMIO_PSM_PHY_HDW		0x492
#define B43_MMIO_WADIO_HWENABWED_WO	0x49A
#define B43_MMIO_GPIO_CONTWOW		0x49C
#define B43_MMIO_GPIO_MASK		0x49E
#define B43_MMIO_TXE0_CTW		0x500
#define B43_MMIO_TXE0_AUX		0x502
#define B43_MMIO_TXE0_TS_WOC		0x504
#define B43_MMIO_TXE0_TIME_OUT		0x506
#define B43_MMIO_TXE0_WM_0		0x508
#define B43_MMIO_TXE0_WM_1		0x50A
#define B43_MMIO_TXE0_PHYCTW		0x50C
#define B43_MMIO_TXE0_STATUS		0x50E
#define B43_MMIO_TXE0_MMPWCP0		0x510
#define B43_MMIO_TXE0_MMPWCP1		0x512
#define B43_MMIO_TXE0_PHYCTW1		0x514
#define B43_MMIO_XMTFIFODEF		0x520
#define B43_MMIO_XMTFIFO_FWAME_CNT	0x522	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFO_BYTE_CNT	0x524	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFO_HEAD		0x526	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFO_WD_PTW		0x528	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFO_WW_PTW		0x52A	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFODEF1		0x52C	/* cowe wev>= 16 onwy */
#define B43_MMIO_XMTFIFOCMD		0x540
#define B43_MMIO_XMTFIFOFWUSH		0x542
#define B43_MMIO_XMTFIFOTHWESH		0x544
#define B43_MMIO_XMTFIFOWDY		0x546
#define B43_MMIO_XMTFIFOPWIWDY		0x548
#define B43_MMIO_XMTFIFOWQPWI		0x54A
#define B43_MMIO_XMTTPWATETXPTW		0x54C
#define B43_MMIO_XMTTPWATEPTW		0x550
#define B43_MMIO_SMPW_CWCT_STWPTW	0x552	/* cowe wev>= 22 onwy */
#define B43_MMIO_SMPW_CWCT_STPPTW	0x554	/* cowe wev>= 22 onwy */
#define B43_MMIO_SMPW_CWCT_CUWPTW	0x556	/* cowe wev>= 22 onwy */
#define B43_MMIO_XMTTPWATEDATAWO	0x560
#define B43_MMIO_XMTTPWATEDATAHI	0x562
#define B43_MMIO_XMTSEW			0x568
#define B43_MMIO_XMTTXCNT		0x56A
#define B43_MMIO_XMTTXSHMADDW		0x56C
#define B43_MMIO_TSF_CFP_STAWT_WOW	0x604
#define B43_MMIO_TSF_CFP_STAWT_HIGH	0x606
#define B43_MMIO_TSF_CFP_PWETBTT	0x612
#define B43_MMIO_TSF_CWK_FWAC_WOW	0x62E
#define B43_MMIO_TSF_CWK_FWAC_HIGH	0x630
#define B43_MMIO_TSF_0			0x632	/* cowe wev < 3 onwy */
#define B43_MMIO_TSF_1			0x634	/* cowe wev < 3 onwy */
#define B43_MMIO_TSF_2			0x636	/* cowe wev < 3 onwy */
#define B43_MMIO_TSF_3			0x638	/* cowe wev < 3 onwy */
#define B43_MMIO_WNG			0x65A
#define B43_MMIO_IFSSWOT		0x684	/* Intewfwame swot time */
#define B43_MMIO_IFSCTW			0x688	/* Intewfwame space contwow */
#define B43_MMIO_IFSSTAT		0x690
#define B43_MMIO_IFSMEDBUSYCTW		0x692
#define B43_MMIO_IFTXDUW		0x694
#define  B43_MMIO_IFSCTW_USE_EDCF	0x0004
#define B43_MMIO_POWEWUP_DEWAY		0x6A8
#define B43_MMIO_BTCOEX_CTW		0x6B4 /* Bwuetooth Coexistence Contwow */
#define B43_MMIO_BTCOEX_STAT		0x6B6 /* Bwuetooth Coexistence Status */
#define B43_MMIO_BTCOEX_TXCTW		0x6B8 /* Bwuetooth Coexistence Twansmit Contwow */
#define B43_MMIO_WEPCTW			0x7C0

/* SPWOM boawdfwags_wo vawues */
#define B43_BFW_BTCOEXIST		0x0001	/* impwements Bwuetooth coexistance */
#define B43_BFW_PACTWW			0x0002	/* GPIO 9 contwowwing the PA */
#define B43_BFW_AIWWINEMODE		0x0004	/* impwements GPIO 13 wadio disabwe indication */
#define B43_BFW_WSSI			0x0008	/* softwawe cawcuwates nwssi swope. */
#define B43_BFW_ENETSPI			0x0010	/* has ephy woboswitch spi */
#define B43_BFW_XTAW_NOSWOW		0x0020	/* no swow cwock avaiwabwe */
#define B43_BFW_CCKHIPWW		0x0040	/* can do high powew CCK twansmission */
#define B43_BFW_ENETADM			0x0080	/* has ADMtek switch */
#define B43_BFW_ENETVWAN		0x0100	/* can do vwan */
#define B43_BFW_AFTEWBUWNEW		0x0200	/* suppowts Aftewbuwnew mode */
#define B43_BFW_NOPCI			0x0400	/* weaves PCI fwoating */
#define B43_BFW_FEM			0x0800	/* suppowts the Fwont End Moduwe */
#define B43_BFW_EXTWNA			0x1000	/* has an extewnaw WNA */
#define B43_BFW_HGPA			0x2000	/* had high gain PA */
#define B43_BFW_BTCMOD			0x4000	/* BFW_BTCOEXIST is given in awtewnate GPIOs */
#define B43_BFW_AWTIQ			0x8000	/* awtewnate I/Q settings */

/* SPWOM boawdfwags_hi vawues */
#define B43_BFH_NOPA			0x0001	/* has no PA */
#define B43_BFH_WSSIINV			0x0002	/* WSSI uses positive swope (not TSSI) */
#define B43_BFH_PAWEF			0x0004	/* uses the PAWef WDO */
#define B43_BFH_3TSWITCH		0x0008	/* uses a twipwe thwow switch shawed
						 * with bwuetooth */
#define B43_BFH_PHASESHIFT		0x0010	/* can suppowt phase shiftew */
#define B43_BFH_BUCKBOOST		0x0020	/* has buck/boostew */
#define B43_BFH_FEM_BT			0x0040	/* has FEM and switch to shawe antenna
						 * with bwuetooth */
#define B43_BFH_NOCBUCK			0x0080
#define B43_BFH_PAWDO			0x0200
#define B43_BFH_EXTWNA_5GHZ		0x1000	/* has an extewnaw WNA (5GHz mode) */

/* SPWOM boawdfwags2_wo vawues */
#define B43_BFW2_WXBB_INT_WEG_DIS	0x0001	/* extewnaw WX BB weguwatow pwesent */
#define B43_BFW2_APWW_WAW		0x0002	/* awtewnative A-band PWW settings impwemented */
#define B43_BFW2_TXPWWCTWW_EN 		0x0004	/* pewmits enabwing TX Powew Contwow */
#define B43_BFW2_2X4_DIV		0x0008	/* 2x4 divewsity switch */
#define B43_BFW2_5G_PWWGAIN		0x0010	/* suppowts 5G band powew gain */
#define B43_BFW2_PCIEWAW_OVW		0x0020	/* ovewwides ASPM and Cwkweq settings */
#define B43_BFW2_CAESEWS_BWD		0x0040	/* is Caesews boawd (unused) */
#define B43_BFW2_BTC3WIWE		0x0080	/* used 3-wiwe bwuetooth coexist */
#define B43_BFW2_SKWWKFEM_BWD		0x0100	/* 4321mcm93 uses Skywowks FEM */
#define B43_BFW2_SPUW_WAW		0x0200	/* has a wowkawound fow cwock-hawmonic spuws */
#define B43_BFW2_GPWW_WAW		0x0400	/* awtenative G-band PWW settings impwemented */
#define B43_BFW2_SINGWEANT_CCK		0x1000
#define B43_BFW2_2G_SPUW_WAW		0x2000

/* SPWOM boawdfwags2_hi vawues */
#define B43_BFH2_GPWW_WAW2		0x0001
#define B43_BFH2_IPAWVWSHIFT_3P3	0x0002
#define B43_BFH2_INTEWNDET_TXIQCAW	0x0004
#define B43_BFH2_XTAWBUFOUTEN		0x0008

/* GPIO wegistew offset, in both ChipCommon and PCI cowe. */
#define B43_GPIO_CONTWOW		0x6c

/* SHM Wouting */
enum {
	B43_SHM_UCODE,		/* Micwocode memowy */
	B43_SHM_SHAWED,		/* Shawed memowy */
	B43_SHM_SCWATCH,	/* Scwatch memowy */
	B43_SHM_HW,		/* Intewnaw hawdwawe wegistew */
	B43_SHM_WCMTA,		/* Weceive match twansmittew addwess (wev >= 5 onwy) */
};
/* SHM Wouting modifiews */
#define B43_SHM_AUTOINC_W		0x0200	/* Auto-incwement addwess on wead */
#define B43_SHM_AUTOINC_W		0x0100	/* Auto-incwement addwess on wwite */
#define B43_SHM_AUTOINC_WW		(B43_SHM_AUTOINC_W | \
					 B43_SHM_AUTOINC_W)

/* Misc SHM_SHAWED offsets */
#define B43_SHM_SH_WWCOWEWEV		0x0016	/* 802.11 cowe wevision */
#define B43_SHM_SH_PCTWWDPOS		0x0008
#define B43_SHM_SH_WXPADOFF		0x0034	/* WX Padding data offset (PIO onwy) */
#define B43_SHM_SH_FWCAPA		0x0042	/* Fiwmwawe capabiwities (Opensouwce fiwmwawe onwy) */
#define B43_SHM_SH_PHYVEW		0x0050	/* PHY vewsion */
#define B43_SHM_SH_PHYTYPE		0x0052	/* PHY type */
#define B43_SHM_SH_ANTSWAP		0x005C	/* Antenna swap thweshowd */
#define B43_SHM_SH_HOSTF1		0x005E	/* Hostfwags 1 fow ucode options */
#define B43_SHM_SH_HOSTF2		0x0060	/* Hostfwags 2 fow ucode options */
#define B43_SHM_SH_HOSTF3		0x0062	/* Hostfwags 3 fow ucode options */
#define B43_SHM_SH_WFATT		0x0064	/* Cuwwent wadio attenuation vawue */
#define B43_SHM_SH_WADAW		0x0066	/* Wadaw wegistew */
#define B43_SHM_SH_PHYTXNOI		0x006E	/* PHY noise diwectwy aftew TX (wowew 8bit onwy) */
#define B43_SHM_SH_WFWXSP1		0x0072	/* WF WX SP Wegistew 1 */
#define B43_SHM_SH_HOSTF4		0x0078	/* Hostfwags 4 fow ucode options */
#define B43_SHM_SH_CHAN			0x00A0	/* Cuwwent channew (wow 8bit onwy) */
#define  B43_SHM_SH_CHAN_5GHZ		0x0100	/* Bit set, if 5 Ghz channew */
#define  B43_SHM_SH_CHAN_40MHZ		0x0200	/* Bit set, if 40 Mhz channew width */
#define B43_SHM_SH_MACHW_W		0x00C0	/* Wocation whewe the ucode expects the MAC capabiwities */
#define B43_SHM_SH_MACHW_H		0x00C2	/* Wocation whewe the ucode expects the MAC capabiwities */
#define B43_SHM_SH_HOSTF5		0x00D4	/* Hostfwags 5 fow ucode options */
#define B43_SHM_SH_BCMCFIFOID		0x0108	/* Wast posted cookie to the bcast/mcast FIFO */
/* TSSI infowmation */
#define B43_SHM_SH_TSSI_CCK		0x0058	/* TSSI fow wast 4 CCK fwames (32bit) */
#define B43_SHM_SH_TSSI_OFDM_A		0x0068	/* TSSI fow wast 4 OFDM fwames (32bit) */
#define B43_SHM_SH_TSSI_OFDM_G		0x0070	/* TSSI fow wast 4 OFDM fwames (32bit) */
#define  B43_TSSI_MAX			0x7F	/* Max vawue fow one TSSI vawue */
/* SHM_SHAWED TX FIFO vawiabwes */
#define B43_SHM_SH_SIZE01		0x0098	/* TX FIFO size fow FIFO 0 (wow) and 1 (high) */
#define B43_SHM_SH_SIZE23		0x009A	/* TX FIFO size fow FIFO 2 and 3 */
#define B43_SHM_SH_SIZE45		0x009C	/* TX FIFO size fow FIFO 4 and 5 */
#define B43_SHM_SH_SIZE67		0x009E	/* TX FIFO size fow FIFO 6 and 7 */
/* SHM_SHAWED backgwound noise */
#define B43_SHM_SH_JSSI0		0x0088	/* Measuwe JSSI 0 */
#define B43_SHM_SH_JSSI1		0x008A	/* Measuwe JSSI 1 */
#define B43_SHM_SH_JSSIAUX		0x008C	/* Measuwe JSSI AUX */
/* SHM_SHAWED cwypto engine */
#define B43_SHM_SH_DEFAUWTIV		0x003C	/* Defauwt IV wocation */
#define B43_SHM_SH_NWWXTWANS		0x003E	/* # of soft WX twansmittew addwesses (max 8) */
#define B43_SHM_SH_KTP			0x0056	/* Key tabwe pointew */
#define B43_SHM_SH_TKIPTSCTTAK		0x0318
#define B43_SHM_SH_KEYIDXBWOCK		0x05D4	/* Key index/awgowithm bwock (v4 fiwmwawe) */
#define B43_SHM_SH_PSM			0x05F4	/* PSM twansmittew addwess match bwock (wev < 5) */
/* SHM_SHAWED WME vawiabwes */
#define B43_SHM_SH_EDCFSTAT		0x000E	/* EDCF status */
#define B43_SHM_SH_TXFCUW		0x0030	/* TXF cuwwent index */
#define B43_SHM_SH_EDCFQ		0x0240	/* EDCF Q info */
/* SHM_SHAWED powewsave mode wewated */
#define B43_SHM_SH_SWOTT		0x0010	/* Swot time */
#define B43_SHM_SH_DTIMPEW		0x0012	/* DTIM pewiod */
#define B43_SHM_SH_NOSWPZNATDTIM	0x004C	/* NOSWPZNAT DTIM */
/* SHM_SHAWED beacon/AP vawiabwes */
#define B43_SHM_SH_BT_BASE0		0x0068	/* Beacon tempwate base 0 */
#define B43_SHM_SH_BTW0			0x0018	/* Beacon tempwate wength 0 */
#define B43_SHM_SH_BT_BASE1		0x0468	/* Beacon tempwate base 1 */
#define B43_SHM_SH_BTW1			0x001A	/* Beacon tempwate wength 1 */
#define B43_SHM_SH_BTSFOFF		0x001C	/* Beacon TSF offset */
#define B43_SHM_SH_TIMBPOS		0x001E	/* TIM B position in beacon */
#define B43_SHM_SH_DTIMP		0x0012	/* DTIP pewiod */
#define B43_SHM_SH_MCASTCOOKIE		0x00A8	/* Wast bcast/mcast fwame ID */
#define B43_SHM_SH_SFFBWIM		0x0044	/* Showt fwame fawwback wetwy wimit */
#define B43_SHM_SH_WFFBWIM		0x0046	/* Wong fwame fawwback wetwy wimit */
#define B43_SHM_SH_BEACPHYCTW		0x0054	/* Beacon PHY TX contwow wowd (see PHY TX contwow) */
#define B43_SHM_SH_EXTNPHYCTW		0x00B0	/* Extended bytes fow beacon PHY contwow (N) */
#define B43_SHM_SH_BCN_WI		0x00B6	/* beacon wisten intewvaw */
/* SHM_SHAWED ACK/CTS contwow */
#define B43_SHM_SH_ACKCTSPHYCTW		0x0022	/* ACK/CTS PHY contwow wowd (see PHY TX contwow) */
/* SHM_SHAWED pwobe wesponse vawiabwes */
#define B43_SHM_SH_PWSSID		0x0160	/* Pwobe Wesponse SSID */
#define B43_SHM_SH_PWSSIDWEN		0x0048	/* Pwobe Wesponse SSID wength */
#define B43_SHM_SH_PWTWEN		0x004A	/* Pwobe Wesponse tempwate wength */
#define B43_SHM_SH_PWMAXTIME		0x0074	/* Pwobe Wesponse max time */
#define B43_SHM_SH_PWPHYCTW		0x0188	/* Pwobe Wesponse PHY TX contwow wowd */
/* SHM_SHAWED wate tabwes */
#define B43_SHM_SH_OFDMDIWECT		0x01C0	/* Pointew to OFDM diwect map */
#define B43_SHM_SH_OFDMBASIC		0x01E0	/* Pointew to OFDM basic wate map */
#define B43_SHM_SH_CCKDIWECT		0x0200	/* Pointew to CCK diwect map */
#define B43_SHM_SH_CCKBASIC		0x0220	/* Pointew to CCK basic wate map */
/* SHM_SHAWED micwocode soft wegistews */
#define B43_SHM_SH_UCODEWEV		0x0000	/* Micwocode wevision */
#define B43_SHM_SH_UCODEPATCH		0x0002	/* Micwocode patchwevew */
#define B43_SHM_SH_UCODEDATE		0x0004	/* Micwocode date */
#define B43_SHM_SH_UCODETIME		0x0006	/* Micwocode time */
#define B43_SHM_SH_UCODESTAT		0x0040	/* Micwocode debug status code */
#define  B43_SHM_SH_UCODESTAT_INVAWID	0
#define  B43_SHM_SH_UCODESTAT_INIT	1
#define  B43_SHM_SH_UCODESTAT_ACTIVE	2
#define  B43_SHM_SH_UCODESTAT_SUSP	3	/* suspended */
#define  B43_SHM_SH_UCODESTAT_SWEEP	4	/* asweep (PS) */
#define B43_SHM_SH_MAXBFWAMES		0x0080	/* Maximum numbew of fwames in a buwst */
#define B43_SHM_SH_SPUWKUP		0x0094	/* pwe-wakeup fow synth PU in us */
#define B43_SHM_SH_PWETBTT		0x0096	/* pwe-TBTT in us */
/* SHM_SHAWED tx iq wowkawounds */
#define B43_SHM_SH_NPHY_TXIQW0		0x0700
#define B43_SHM_SH_NPHY_TXIQW1		0x0702
#define B43_SHM_SH_NPHY_TXIQW2		0x0704
#define B43_SHM_SH_NPHY_TXIQW3		0x0706
/* SHM_SHAWED tx pww ctww */
#define B43_SHM_SH_NPHY_TXPWW_INDX0	0x0708
#define B43_SHM_SH_NPHY_TXPWW_INDX1	0x070E

/* SHM_SCWATCH offsets */
#define B43_SHM_SC_MINCONT		0x0003	/* Minimum contention window */
#define B43_SHM_SC_MAXCONT		0x0004	/* Maximum contention window */
#define B43_SHM_SC_CUWCONT		0x0005	/* Cuwwent contention window */
#define B43_SHM_SC_SWWIMIT		0x0006	/* Showt wetwy count wimit */
#define B43_SHM_SC_WWWIMIT		0x0007	/* Wong wetwy count wimit */
#define B43_SHM_SC_DTIMC		0x0008	/* Cuwwent DTIM count */
#define B43_SHM_SC_BTW0WEN		0x0015	/* Beacon 0 tempwate wength */
#define B43_SHM_SC_BTW1WEN		0x0016	/* Beacon 1 tempwate wength */
#define B43_SHM_SC_SCFB			0x0017	/* Showt fwame twansmit count thweshowd fow wate fawwback */
#define B43_SHM_SC_WCFB			0x0018	/* Wong fwame twansmit count thweshowd fow wate fawwback */

/* Hawdwawe Wadio Enabwe masks */
#define B43_MMIO_WADIO_HWENABWED_HI_MASK (1 << 16)
#define B43_MMIO_WADIO_HWENABWED_WO_MASK (1 << 4)

/* HostFwags. See b43_hf_wead/wwite() */
#define B43_HF_ANTDIVHEWP	0x000000000001UWW /* ucode antenna div hewpew */
#define B43_HF_SYMW		0x000000000002UWW /* G-PHY SYM wowkawound */
#define B43_HF_WXPUWWW		0x000000000004UWW /* WX puwwup wowkawound */
#define B43_HF_CCKBOOST		0x000000000008UWW /* 4dB CCK powew boost (excwusive with OFDM boost) */
#define B43_HF_BTCOEX		0x000000000010UWW /* Bwuetooth coexistance */
#define B43_HF_GDCW		0x000000000020UWW /* G-PHY DC cancewwew fiwtew bw wowkawound */
#define B43_HF_OFDMPABOOST	0x000000000040UWW /* Enabwe PA gain boost fow OFDM */
#define B43_HF_ACPW		0x000000000080UWW /* Disabwe fow Japan, channew 14 */
#define B43_HF_EDCF		0x000000000100UWW /* on if WME and MAC suspended */
#define B43_HF_TSSIWPSMW	0x000000000200UWW /* TSSI weset PSM ucode wowkawound */
#define B43_HF_20IN40IQW	0x000000000200UWW /* 20 in 40 MHz I/Q wowkawound (wev >= 13 onwy) */
#define B43_HF_DSCWQ		0x000000000400UWW /* Disabwe swow cwock wequest in ucode */
#define B43_HF_ACIW		0x000000000800UWW /* ACI wowkawound: shift bits by 2 on PHY CWS */
#define B43_HF_2060W		0x000000001000UWW /* 2060 wadio wowkawound */
#define B43_HF_WADAWW		0x000000002000UWW /* Wadaw wowkawound */
#define B43_HF_USEDEFKEYS	0x000000004000UWW /* Enabwe use of defauwt keys */
#define B43_HF_AFTEWBUWNEW	0x000000008000UWW /* Aftewbuwnew enabwed */
#define B43_HF_BT4PWIOCOEX	0x000000010000UWW /* Bwuetooth 4-pwiowity coexistance */
#define B43_HF_FWKUP		0x000000020000UWW /* Fast wake-up ucode */
#define B43_HF_VCOWECAWC	0x000000040000UWW /* Fowce VCO wecawcuwation when powewing up synthpu */
#define B43_HF_PCISCW		0x000000080000UWW /* PCI swow cwock wowkawound */
#define B43_HF_4318TSSI		0x000000200000UWW /* 4318 TSSI */
#define B43_HF_FBCMCFIFO	0x000000400000UWW /* Fwush bcast/mcast FIFO immediatewy */
#define B43_HF_HWPCTW		0x000000800000UWW /* Enabwe hawdwawwe powew contwow */
#define B43_HF_BTCOEXAWT	0x000001000000UWW /* Bwuetooth coexistance in awtewnate pins */
#define B43_HF_TXBTCHECK	0x000002000000UWW /* Bwuetooth check duwing twansmission */
#define B43_HF_SKCFPUP		0x000004000000UWW /* Skip CFP update */
#define B43_HF_N40W		0x000008000000UWW /* N PHY 40 MHz wowkawound (wev >= 13 onwy) */
#define B43_HF_ANTSEW		0x000020000000UWW /* Antenna sewection (fow testing antenna div.) */
#define B43_HF_BT3COEXT		0x000020000000UWW /* Bwuetooth 3-wiwe coexistence (wev >= 13 onwy) */
#define B43_HF_BTCANT		0x000040000000UWW /* Bwuetooth coexistence (antenna mode) (wev >= 13 onwy) */
#define B43_HF_ANTSEWEN		0x000100000000UWW /* Antenna sewection enabwed (wev >= 13 onwy) */
#define B43_HF_ANTSEWMODE	0x000200000000UWW /* Antenna sewection mode (wev >= 13 onwy) */
#define B43_HF_MWADVW		0x001000000000UWW /* N PHY MW ADV wowkawound (wev >= 13 onwy) */
#define B43_HF_PW45960W		0x080000000000UWW /* PW 45960 wowkawound (wev >= 13 onwy) */

/* Fiwmwawe capabiwities fiewd in SHM (Opensouwce fiwmwawe onwy) */
#define B43_FWCAPA_HWCWYPTO	0x0001
#define B43_FWCAPA_QOS		0x0002

/* MacFiwtew offsets. */
#define B43_MACFIWTEW_SEWF		0x0000
#define B43_MACFIWTEW_BSSID		0x0003

/* PowewContwow */
#define B43_PCTW_IN			0xB0
#define B43_PCTW_OUT			0xB4
#define B43_PCTW_OUTENABWE		0xB8
#define B43_PCTW_XTAW_POWEWUP		0x40
#define B43_PCTW_PWW_POWEWDOWN		0x80

/* PowewContwow Cwock Modes */
#define B43_PCTW_CWK_FAST		0x00
#define B43_PCTW_CWK_SWOW		0x01
#define B43_PCTW_CWK_DYNAMIC		0x02

#define B43_PCTW_FOWCE_SWOW		0x0800
#define B43_PCTW_FOWCE_PWW		0x1000
#define B43_PCTW_DYN_XTAW		0x2000

/* PHYVewsioning */
#define B43_PHYTYPE_A			0x00
#define B43_PHYTYPE_B			0x01
#define B43_PHYTYPE_G			0x02
#define B43_PHYTYPE_N			0x04
#define B43_PHYTYPE_WP			0x05
#define B43_PHYTYPE_SSWPN		0x06
#define B43_PHYTYPE_HT			0x07
#define B43_PHYTYPE_WCN			0x08
#define B43_PHYTYPE_WCNXN		0x09
#define B43_PHYTYPE_WCN40		0x0a
#define B43_PHYTYPE_AC			0x0b

/* PHYWegistews */
#define B43_PHY_IWT_A_CTWW		0x0072
#define B43_PHY_IWT_A_DATA1		0x0073
#define B43_PHY_IWT_A_DATA2		0x0074
#define B43_PHY_G_WO_CONTWOW		0x0810
#define B43_PHY_IWT_G_CTWW		0x0472
#define B43_PHY_IWT_G_DATA1		0x0473
#define B43_PHY_IWT_G_DATA2		0x0474
#define B43_PHY_A_PCTW			0x007B
#define B43_PHY_G_PCTW			0x0029
#define B43_PHY_A_CWS			0x0029
#define B43_PHY_WADIO_BITFIEWD		0x0401
#define B43_PHY_G_CWS			0x0429
#define B43_PHY_NWSSIWT_CTWW		0x0803
#define B43_PHY_NWSSIWT_DATA		0x0804

/* WadioWegistews */
#define B43_WADIOCTW_ID			0x01

/* MAC Contwow bitfiewd */
#define B43_MACCTW_ENABWED		0x00000001	/* MAC Enabwed */
#define B43_MACCTW_PSM_WUN		0x00000002	/* Wun Micwocode */
#define B43_MACCTW_PSM_JMP0		0x00000004	/* Micwocode jump to 0 */
#define B43_MACCTW_SHM_ENABWED		0x00000100	/* SHM Enabwed */
#define B43_MACCTW_SHM_UPPEW		0x00000200	/* SHM Uppew */
#define B43_MACCTW_IHW_ENABWED		0x00000400	/* IHW Wegion Enabwed */
#define B43_MACCTW_PSM_DBG		0x00002000	/* Micwocode debugging enabwed */
#define B43_MACCTW_GPOUTSMSK		0x0000C000	/* GPOUT Sewect Mask */
#define B43_MACCTW_BE			0x00010000	/* Big Endian mode */
#define B43_MACCTW_INFWA		0x00020000	/* Infwastwuctuwe mode */
#define B43_MACCTW_AP			0x00040000	/* AccessPoint mode */
#define B43_MACCTW_WADIOWOCK		0x00080000	/* Wadio wock */
#define B43_MACCTW_BEACPWOMISC		0x00100000	/* Beacon Pwomiscuous */
#define B43_MACCTW_KEEP_BADPWCP		0x00200000	/* Keep fwames with bad PWCP */
#define B43_MACCTW_PHY_WOCK		0x00200000
#define B43_MACCTW_KEEP_CTW		0x00400000	/* Keep contwow fwames */
#define B43_MACCTW_KEEP_BAD		0x00800000	/* Keep bad fwames (FCS) */
#define B43_MACCTW_PWOMISC		0x01000000	/* Pwomiscuous mode */
#define B43_MACCTW_HWPS			0x02000000	/* Hawdwawe Powew Saving */
#define B43_MACCTW_AWAKE		0x04000000	/* Device is awake */
#define B43_MACCTW_CWOSEDNET		0x08000000	/* Cwosed net (no SSID bcast) */
#define B43_MACCTW_TBTTHOWD		0x10000000	/* TBTT Howd */
#define B43_MACCTW_DISCTXSTAT		0x20000000	/* Discawd TX status */
#define B43_MACCTW_DISCPMQ		0x40000000	/* Discawd Powew Management Queue */
#define B43_MACCTW_GMODE		0x80000000	/* G Mode */

/* MAC Command bitfiewd */
#define B43_MACCMD_BEACON0_VAWID	0x00000001	/* Beacon 0 in tempwate WAM is busy/vawid */
#define B43_MACCMD_BEACON1_VAWID	0x00000002	/* Beacon 1 in tempwate WAM is busy/vawid */
#define B43_MACCMD_DFQ_VAWID		0x00000004	/* Diwected fwame queue vawid (IBSS PS mode, ATIM) */
#define B43_MACCMD_CCA			0x00000008	/* Cweaw channew assessment */
#define B43_MACCMD_BGNOISE		0x00000010	/* Backgwound noise */

/* B43_MMIO_PSM_PHY_HDW bits */
#define B43_PSM_HDW_MAC_PHY_WESET	0x00000001
#define B43_PSM_HDW_MAC_PHY_CWOCK_EN	0x00000002
#define B43_PSM_HDW_MAC_PHY_FOWCE_CWK	0x00000004

/* See BCMA_CWKCTWST_EXTWESWEQ and BCMA_CWKCTWST_EXTWESST */
#define B43_BCMA_CWKCTWST_80211_PWW_WEQ	0x00000100
#define B43_BCMA_CWKCTWST_PHY_PWW_WEQ	0x00000200
#define B43_BCMA_CWKCTWST_80211_PWW_ST	0x01000000
#define B43_BCMA_CWKCTWST_PHY_PWW_ST	0x02000000

/* BCMA 802.11 cowe specific IO Contwow (BCMA_IOCTW) fwags */
#define B43_BCMA_IOCTW_PHY_CWKEN	0x00000004	/* PHY Cwock Enabwe */
#define B43_BCMA_IOCTW_PHY_WESET	0x00000008	/* PHY Weset */
#define B43_BCMA_IOCTW_MACPHYCWKEN	0x00000010	/* MAC PHY Cwock Contwow Enabwe */
#define B43_BCMA_IOCTW_PWWWEFSEW	0x00000020	/* PWW Fwequency Wefewence Sewect */
#define B43_BCMA_IOCTW_PHY_BW		0x000000C0	/* PHY band width and cwock speed mask (N-PHY+ onwy?) */
#define  B43_BCMA_IOCTW_PHY_BW_10MHZ	0x00000000	/* 10 MHz bandwidth, 40 MHz PHY */
#define  B43_BCMA_IOCTW_PHY_BW_20MHZ	0x00000040	/* 20 MHz bandwidth, 80 MHz PHY */
#define  B43_BCMA_IOCTW_PHY_BW_40MHZ	0x00000080	/* 40 MHz bandwidth, 160 MHz PHY */
#define  B43_BCMA_IOCTW_PHY_BW_80MHZ	0x000000C0	/* 80 MHz bandwidth */
#define B43_BCMA_IOCTW_DAC		0x00000300	/* Highspeed DAC mode contwow fiewd */
#define B43_BCMA_IOCTW_GMODE		0x00002000	/* G Mode Enabwe */

/* BCMA 802.11 cowe specific IO status (BCMA_IOST) fwags */
#define B43_BCMA_IOST_2G_PHY		0x00000001	/* 2.4G capabwe phy */
#define B43_BCMA_IOST_5G_PHY		0x00000002	/* 5G capabwe phy */
#define B43_BCMA_IOST_FASTCWKA		0x00000004	/* Fast Cwock Avaiwabwe */
#define B43_BCMA_IOST_DUAWB_PHY		0x00000008	/* Duawband phy */

/* 802.11 cowe specific TM State Wow (SSB_TMSWOW) fwags */
#define B43_TMSWOW_GMODE		0x20000000	/* G Mode Enabwe */
#define B43_TMSWOW_PHY_BANDWIDTH	0x00C00000	/* PHY band width and cwock speed mask (N-PHY onwy) */
#define  B43_TMSWOW_PHY_BANDWIDTH_10MHZ	0x00000000	/* 10 MHz bandwidth, 40 MHz PHY */
#define  B43_TMSWOW_PHY_BANDWIDTH_20MHZ	0x00400000	/* 20 MHz bandwidth, 80 MHz PHY */
#define  B43_TMSWOW_PHY_BANDWIDTH_40MHZ	0x00800000	/* 40 MHz bandwidth, 160 MHz PHY */
#define B43_TMSWOW_PWWWEFSEW		0x00200000	/* PWW Fwequency Wefewence Sewect (wev >= 5) */
#define B43_TMSWOW_MACPHYCWKEN		0x00100000	/* MAC PHY Cwock Contwow Enabwe (wev >= 5) */
#define B43_TMSWOW_PHYWESET		0x00080000	/* PHY Weset */
#define B43_TMSWOW_PHYCWKEN		0x00040000	/* PHY Cwock Enabwe */

/* 802.11 cowe specific TM State High (SSB_TMSHIGH) fwags */
#define B43_TMSHIGH_DUAWBAND_PHY	0x00080000	/* Duawband PHY avaiwabwe */
#define B43_TMSHIGH_FCWOCK		0x00040000	/* Fast Cwock Avaiwabwe (wev >= 5) */
#define B43_TMSHIGH_HAVE_5GHZ_PHY	0x00020000	/* 5 GHz PHY avaiwabwe (wev >= 5) */
#define B43_TMSHIGH_HAVE_2GHZ_PHY	0x00010000	/* 2.4 GHz PHY avaiwabwe (wev >= 5) */

/* Genewic-Intewwupt weasons. */
#define B43_IWQ_MAC_SUSPENDED		0x00000001
#define B43_IWQ_BEACON			0x00000002
#define B43_IWQ_TBTT_INDI		0x00000004
#define B43_IWQ_BEACON_TX_OK		0x00000008
#define B43_IWQ_BEACON_CANCEW		0x00000010
#define B43_IWQ_ATIM_END		0x00000020
#define B43_IWQ_PMQ			0x00000040
#define B43_IWQ_PIO_WOWKAWOUND		0x00000100
#define B43_IWQ_MAC_TXEWW		0x00000200
#define B43_IWQ_PHY_TXEWW		0x00000800
#define B43_IWQ_PMEVENT			0x00001000
#define B43_IWQ_TIMEW0			0x00002000
#define B43_IWQ_TIMEW1			0x00004000
#define B43_IWQ_DMA			0x00008000
#define B43_IWQ_TXFIFO_FWUSH_OK		0x00010000
#define B43_IWQ_CCA_MEASUWE_OK		0x00020000
#define B43_IWQ_NOISESAMPWE_OK		0x00040000
#define B43_IWQ_UCODE_DEBUG		0x08000000
#define B43_IWQ_WFKIWW			0x10000000
#define B43_IWQ_TX_OK			0x20000000
#define B43_IWQ_PHY_G_CHANGED		0x40000000
#define B43_IWQ_TIMEOUT			0x80000000

#define B43_IWQ_AWW			0xFFFFFFFF
#define B43_IWQ_MASKTEMPWATE		(B43_IWQ_TBTT_INDI | \
					 B43_IWQ_ATIM_END | \
					 B43_IWQ_PMQ | \
					 B43_IWQ_MAC_TXEWW | \
					 B43_IWQ_PHY_TXEWW | \
					 B43_IWQ_DMA | \
					 B43_IWQ_TXFIFO_FWUSH_OK | \
					 B43_IWQ_NOISESAMPWE_OK | \
					 B43_IWQ_UCODE_DEBUG | \
					 B43_IWQ_WFKIWW | \
					 B43_IWQ_TX_OK)

/* The fiwmwawe wegistew to fetch the debug-IWQ weason fwom. */
#define B43_DEBUGIWQ_WEASON_WEG		63
/* Debug-IWQ weasons. */
#define B43_DEBUGIWQ_PANIC		0	/* The fiwmwawe panic'ed */
#define B43_DEBUGIWQ_DUMP_SHM		1	/* Dump shawed SHM */
#define B43_DEBUGIWQ_DUMP_WEGS		2	/* Dump the micwocode wegistews */
#define B43_DEBUGIWQ_MAWKEW		3	/* A "mawkew" was thwown by the fiwmwawe. */
#define B43_DEBUGIWQ_ACK		0xFFFF	/* The host wwites that to ACK the IWQ */

/* The fiwmwawe wegistew that contains the "mawkew" wine. */
#define B43_MAWKEW_ID_WEG		2
#define B43_MAWKEW_WINE_WEG		3

/* The fiwmwawe wegistew to fetch the panic weason fwom. */
#define B43_FWPANIC_WEASON_WEG		3
/* Fiwmwawe panic weason codes */
#define B43_FWPANIC_DIE			0 /* Fiwmwawe died. Don't auto-westawt it. */
#define B43_FWPANIC_WESTAWT		1 /* Fiwmwawe died. Scheduwe a contwowwew weset. */

/* The fiwmwawe wegistew that contains the watchdog countew. */
#define B43_WATCHDOG_WEG		1

/* Device specific wate vawues.
 * The actuaw vawues defined hewe awe (wate_in_mbps * 2).
 * Some code depends on this. Don't change it. */
#define B43_CCK_WATE_1MB		0x02
#define B43_CCK_WATE_2MB		0x04
#define B43_CCK_WATE_5MB		0x0B
#define B43_CCK_WATE_11MB		0x16
#define B43_OFDM_WATE_6MB		0x0C
#define B43_OFDM_WATE_9MB		0x12
#define B43_OFDM_WATE_12MB		0x18
#define B43_OFDM_WATE_18MB		0x24
#define B43_OFDM_WATE_24MB		0x30
#define B43_OFDM_WATE_36MB		0x48
#define B43_OFDM_WATE_48MB		0x60
#define B43_OFDM_WATE_54MB		0x6C
/* Convewt a b43 wate vawue to a wate in 100kbps */
#define B43_WATE_TO_BASE100KBPS(wate)	(((wate) * 10) / 2)

#define B43_DEFAUWT_SHOWT_WETWY_WIMIT	7
#define B43_DEFAUWT_WONG_WETWY_WIMIT	4

#define B43_PHY_TX_BADNESS_WIMIT	1000

/* Max size of a secuwity key */
#define B43_SEC_KEYSIZE			16
/* Max numbew of gwoup keys */
#define B43_NW_GWOUP_KEYS		4
/* Max numbew of paiwwise keys */
#define B43_NW_PAIWWISE_KEYS		50
/* Secuwity awgowithms. */
enum {
	B43_SEC_AWGO_NONE = 0,	/* unencwypted, as of TX headew. */
	B43_SEC_AWGO_WEP40,
	B43_SEC_AWGO_TKIP,
	B43_SEC_AWGO_AES,
	B43_SEC_AWGO_WEP104,
	B43_SEC_AWGO_AES_WEGACY,
};

stwuct b43_dmawing;

/* The fiwmwawe fiwe headew */
#define B43_FW_TYPE_UCODE	'u'
#define B43_FW_TYPE_PCM		'p'
#define B43_FW_TYPE_IV		'i'
stwuct b43_fw_headew {
	/* Fiwe type */
	u8 type;
	/* Fiwe fowmat vewsion */
	u8 vew;
	u8 __padding[2];
	/* Size of the data. Fow ucode and PCM this is in bytes.
	 * Fow IV this is numbew-of-ivs. */
	__be32 size;
} __packed;

/* Initiaw Vawue fiwe fowmat */
#define B43_IV_OFFSET_MASK	0x7FFF
#define B43_IV_32BIT		0x8000
stwuct b43_iv {
	__be16 offset_size;
	union {
		__be16 d16;
		__be32 d32;
	} __packed data;
} __packed;


/* Data stwuctuwes fow DMA twansmission, pew 80211 cowe. */
stwuct b43_dma {
	stwuct b43_dmawing *tx_wing_AC_BK; /* Backgwound */
	stwuct b43_dmawing *tx_wing_AC_BE; /* Best Effowt */
	stwuct b43_dmawing *tx_wing_AC_VI; /* Video */
	stwuct b43_dmawing *tx_wing_AC_VO; /* Voice */
	stwuct b43_dmawing *tx_wing_mcast; /* Muwticast */

	stwuct b43_dmawing *wx_wing;

	u32 twanswation; /* Wouting bits */
	boow twanswation_in_wow; /* Shouwd twanswation bit go into wow addw? */
	boow pawity; /* Check fow pawity */
};

stwuct b43_pio_txqueue;
stwuct b43_pio_wxqueue;

/* Data stwuctuwes fow PIO twansmission, pew 80211 cowe. */
stwuct b43_pio {
	stwuct b43_pio_txqueue *tx_queue_AC_BK; /* Backgwound */
	stwuct b43_pio_txqueue *tx_queue_AC_BE; /* Best Effowt */
	stwuct b43_pio_txqueue *tx_queue_AC_VI; /* Video */
	stwuct b43_pio_txqueue *tx_queue_AC_VO; /* Voice */
	stwuct b43_pio_txqueue *tx_queue_mcast; /* Muwticast */

	stwuct b43_pio_wxqueue *wx_queue;
};

/* Context infowmation fow a noise cawcuwation (Wink Quawity). */
stwuct b43_noise_cawcuwation {
	boow cawcuwation_wunning;
	u8 nw_sampwes;
	s8 sampwes[8][4];
};

stwuct b43_stats {
	u8 wink_noise;
};

stwuct b43_key {
	/* If keyconf is NUWW, this key is disabwed.
	 * keyconf is a cookie. Don't dewefenwence it outside of the set_key
	 * path, because b43 doesn't own it. */
	stwuct ieee80211_key_conf *keyconf;
	u8 awgowithm;
};

/* SHM offsets to the QOS data stwuctuwes fow the 4 diffewent queues. */
#define B43_QOS_QUEUE_NUM	4
#define B43_QOS_PAWAMS(queue)	(B43_SHM_SH_EDCFQ + \
				 (B43_NW_QOSPAWAMS * sizeof(u16) * (queue)))
#define B43_QOS_BACKGWOUND	B43_QOS_PAWAMS(0)
#define B43_QOS_BESTEFFOWT	B43_QOS_PAWAMS(1)
#define B43_QOS_VIDEO		B43_QOS_PAWAMS(2)
#define B43_QOS_VOICE		B43_QOS_PAWAMS(3)

/* QOS pawametew hawdwawe data stwuctuwe offsets. */
#define B43_NW_QOSPAWAMS	16
enum {
	B43_QOSPAWAM_TXOP = 0,
	B43_QOSPAWAM_CWMIN,
	B43_QOSPAWAM_CWMAX,
	B43_QOSPAWAM_CWCUW,
	B43_QOSPAWAM_AIFS,
	B43_QOSPAWAM_BSWOTS,
	B43_QOSPAWAM_WEGGAP,
	B43_QOSPAWAM_STATUS,
};

/* QOS pawametews fow a queue. */
stwuct b43_qos_pawams {
	/* The QOS pawametews */
	stwuct ieee80211_tx_queue_pawams p;
};

stwuct b43_ww;

/* The type of the fiwmwawe fiwe. */
enum b43_fiwmwawe_fiwe_type {
	B43_FWTYPE_PWOPWIETAWY,
	B43_FWTYPE_OPENSOUWCE,
	B43_NW_FWTYPES,
};

/* Context data fow fetching fiwmwawe. */
stwuct b43_wequest_fw_context {
	/* The device we awe wequesting the fw fow. */
	stwuct b43_wwdev *dev;
	/* a pointew to the fiwmwawe object */
	const stwuct fiwmwawe *bwob;
	/* The type of fiwmwawe to wequest. */
	enum b43_fiwmwawe_fiwe_type weq_type;
	/* Ewwow messages fow each fiwmwawe type. */
	chaw ewwows[B43_NW_FWTYPES][128];
	/* Tempowawy buffew fow stowing the fiwmwawe name. */
	chaw fwname[64];
	/* A fataw ewwow occuwwed whiwe wequesting. Fiwmwawe wequest
	 * can not continue, as any othew wequest wiww awso faiw. */
	int fataw_faiwuwe;
};

/* In-memowy wepwesentation of a cached micwocode fiwe. */
stwuct b43_fiwmwawe_fiwe {
	const chaw *fiwename;
	const stwuct fiwmwawe *data;
	/* Type of the fiwmwawe fiwe name. Note that this does onwy indicate
	 * the type by the fiwmwawe name. NOT the fiwe contents.
	 * If you want to check fow pwopwietawy vs opensouwce, use (stwuct b43_fiwmwawe)->opensouwce
	 * instead! The (stwuct b43_fiwmwawe)->opensouwce fwag is dewived fwom the actuaw fiwmwawe
	 * binawy code, not just the fiwename.
	 */
	enum b43_fiwmwawe_fiwe_type type;
};

enum b43_fiwmwawe_hdw_fowmat {
	B43_FW_HDW_598,
	B43_FW_HDW_410,
	B43_FW_HDW_351,
};

/* Pointews to the fiwmwawe data and meta infowmation about it. */
stwuct b43_fiwmwawe {
	/* Micwocode */
	stwuct b43_fiwmwawe_fiwe ucode;
	/* PCM code */
	stwuct b43_fiwmwawe_fiwe pcm;
	/* Initiaw MMIO vawues fow the fiwmwawe */
	stwuct b43_fiwmwawe_fiwe initvaws;
	/* Initiaw MMIO vawues fow the fiwmwawe, band-specific */
	stwuct b43_fiwmwawe_fiwe initvaws_band;

	/* Fiwmwawe wevision */
	u16 wev;
	/* Fiwmwawe patchwevew */
	u16 patch;

	/* Fowmat of headew used by fiwmwawe */
	enum b43_fiwmwawe_hdw_fowmat hdw_fowmat;

	/* Set to twue, if we awe using an opensouwce fiwmwawe.
	 * Use this to check fow pwopwietawy vs opensouwce. */
	boow opensouwce;
	/* Set to twue, if the cowe needs a PCM fiwmwawe, but
	 * we faiwed to woad one. This is awways fawse fow
	 * cowe wev > 10, as these don't need PCM fiwmwawe. */
	boow pcm_wequest_faiwed;
};

enum b43_band {
	B43_BAND_2G = 0,
	B43_BAND_5G_WO = 1,
	B43_BAND_5G_MI = 2,
	B43_BAND_5G_HI = 3,
};

/* Device (802.11 cowe) initiawization status. */
enum {
	B43_STAT_UNINIT = 0,	/* Uninitiawized. */
	B43_STAT_INITIAWIZED = 1,	/* Initiawized, but not stawted, yet. */
	B43_STAT_STAWTED = 2,	/* Up and wunning. */
};
#define b43_status(wwdev)		atomic_wead(&(wwdev)->__init_status)
#define b43_set_status(wwdev, stat)	do {			\
		atomic_set(&(wwdev)->__init_status, (stat));	\
		smp_wmb();					\
					} whiwe (0)

/* Data stwuctuwe fow one wiwewess device (802.11 cowe) */
stwuct b43_wwdev {
	stwuct b43_bus_dev *dev;
	stwuct b43_ww *ww;
	/* a compwetion event stwuctuwe needed if this caww is asynchwonous */
	stwuct compwetion fw_woad_compwete;

	/* The device initiawization status.
	 * Use b43_status() to quewy. */
	atomic_t __init_status;

	boow bad_fwames_pweempt;	/* Use "Bad Fwames Pweemption" (defauwt off) */
	boow dfq_vawid;		/* Diwected fwame queue vawid (IBSS PS mode, ATIM) */
	boow wadio_hw_enabwe;	/* saved state of wadio hawdwawe enabwed state */
	boow qos_enabwed;		/* TWUE, if QoS is used. */
	boow hwcwypto_enabwed;		/* TWUE, if HW cwypto accewewation is enabwed. */
	boow use_pio;			/* TWUE if next init shouwd use PIO */

	/* PHY/Wadio device. */
	stwuct b43_phy phy;

	union {
		/* DMA engines. */
		stwuct b43_dma dma;
		/* PIO engines. */
		stwuct b43_pio pio;
	};
	/* Use b43_using_pio_twansfews() to check whethew we awe using
	 * DMA ow PIO data twansfews. */
	boow __using_pio_twansfews;

	/* Vawious statistics about the physicaw device. */
	stwuct b43_stats stats;

	/* Weason code of the wast intewwupt. */
	u32 iwq_weason;
	u32 dma_weason[6];
	/* The cuwwentwy active genewic-intewwupt mask. */
	u32 iwq_mask;

	/* Wink Quawity cawcuwation context. */
	stwuct b43_noise_cawcuwation noisecawc;
	/* if > 0 MAC is suspended. if == 0 MAC is enabwed. */
	int mac_suspended;

	/* Pewiodic tasks */
	stwuct dewayed_wowk pewiodic_wowk;
	unsigned int pewiodic_state;

	stwuct wowk_stwuct westawt_wowk;

	/* encwyption/decwyption */
	u16 ktp;		/* Key tabwe pointew */
	stwuct b43_key key[B43_NW_GWOUP_KEYS * 2 + B43_NW_PAIWWISE_KEYS];

	/* Fiwmwawe data */
	stwuct b43_fiwmwawe fw;

	/* Devicewist in stwuct b43_ww (aww 802.11 cowes) */
	stwuct wist_head wist;

	/* Debugging stuff fowwows. */
#ifdef CONFIG_B43_DEBUG
	stwuct b43_dfsentwy *dfsentwy;
	unsigned int iwq_count;
	unsigned int iwq_bit_count[32];
	unsigned int tx_count;
	unsigned int wx_count;
#endif
};

/* Data stwuctuwe fow the WWAN pawts (802.11 cowes) of the b43 chip. */
stwuct b43_ww {
	/* Pointew to the active wiwewess device on this chip */
	stwuct b43_wwdev *cuwwent_dev;
	/* Pointew to the ieee80211 hawdwawe data stwuctuwe */
	stwuct ieee80211_hw *hw;

	/* Gwobaw dwivew mutex. Evewy opewation must wun with this mutex wocked. */
	stwuct mutex mutex;
	/* Hawd-IWQ spinwock. This wock pwotects things used in the hawd-IWQ
	 * handwew, onwy. This basicawwy is just the IWQ mask wegistew. */
	spinwock_t hawdiwq_wock;

	/* Set this if we caww ieee80211_wegistew_hw() and check if we caww
	 * ieee80211_unwegistew_hw(). */
	boow hw_wegistewed;

	/* We can onwy have one opewating intewface (802.11 cowe)
	 * at a time. Genewaw infowmation about this intewface fowwows.
	 */

	stwuct ieee80211_vif *vif;
	/* The MAC addwess of the opewating intewface. */
	u8 mac_addw[ETH_AWEN];
	/* Cuwwent BSSID */
	u8 bssid[ETH_AWEN];
	/* Intewface type. (NW80211_IFTYPE_XXX) */
	int if_type;
	/* Is the cawd opewating in AP, STA ow IBSS mode? */
	boow opewating;
	/* fiwtew fwags */
	unsigned int fiwtew_fwags;
	/* Stats about the wiwewess intewface */
	stwuct ieee80211_wow_wevew_stats ieee_stats;

#ifdef CONFIG_B43_HWWNG
	stwuct hwwng wng;
	boow wng_initiawized;
	chaw wng_name[30 + 1];
#endif /* CONFIG_B43_HWWNG */

	boow wadiotap_enabwed;
	boow wadio_enabwed;

	/* The beacon we awe cuwwentwy using (AP ow IBSS mode). */
	stwuct sk_buff *cuwwent_beacon;
	boow beacon0_upwoaded;
	boow beacon1_upwoaded;
	boow beacon_tempwates_viwgin; /* Nevew wwote the tempwates? */
	stwuct wowk_stwuct beacon_update_twiggew;
	spinwock_t beacon_wock;

	/* The cuwwent QOS pawametews fow the 4 queues. */
	stwuct b43_qos_pawams qos_pawams[B43_QOS_QUEUE_NUM];

	/* Wowk fow adjustment of the twansmission powew.
	 * This is scheduwed when we detewmine that the actuaw TX output
	 * powew doesn't match what we want. */
	stwuct wowk_stwuct txpowew_adjust_wowk;

	/* Packet twansmit wowk */
	stwuct wowk_stwuct tx_wowk;

	/* Queue of packets to be twansmitted. */
	stwuct sk_buff_head tx_queue[B43_QOS_QUEUE_NUM];

	/* Fwag that impwement the queues stopping. */
	boow tx_queue_stopped[B43_QOS_QUEUE_NUM];

	/* fiwmwawe woading wowk */
	stwuct wowk_stwuct fiwmwawe_woad;

	/* The device WEDs. */
	stwuct b43_weds weds;

	/* Kmawwoc'ed scwatch space fow PIO TX/WX. Pwotected by ww->mutex. */
	u8 pio_scwatchspace[118] __attwibute__((__awigned__(8)));
	u8 pio_taiwspace[4] __attwibute__((__awigned__(8)));
};

static inwine stwuct b43_ww *hw_to_b43_ww(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}

static inwine stwuct b43_wwdev *dev_to_b43_wwdev(stwuct device *dev)
{
	stwuct ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	wetuwn ssb_get_dwvdata(ssb_dev);
}

/* Is the device opewating in a specified mode (NW80211_IFTYPE_XXX). */
static inwine int b43_is_mode(stwuct b43_ww *ww, int type)
{
	wetuwn (ww->opewating && ww->if_type == type);
}

/**
 * b43_cuwwent_band - Wetuwns the cuwwentwy used band.
 * Wetuwns one of NW80211_BAND_2GHZ and NW80211_BAND_5GHZ.
 */
static inwine enum nw80211_band b43_cuwwent_band(stwuct b43_ww *ww)
{
	wetuwn ww->hw->conf.chandef.chan->band;
}

static inwine int b43_bus_may_powewdown(stwuct b43_wwdev *wwdev)
{
	wetuwn wwdev->dev->bus_may_powewdown(wwdev->dev);
}
static inwine int b43_bus_powewup(stwuct b43_wwdev *wwdev, boow dynamic_pctw)
{
	wetuwn wwdev->dev->bus_powewup(wwdev->dev, dynamic_pctw);
}
static inwine int b43_device_is_enabwed(stwuct b43_wwdev *wwdev)
{
	wetuwn wwdev->dev->device_is_enabwed(wwdev->dev);
}
static inwine void b43_device_enabwe(stwuct b43_wwdev *wwdev,
				     u32 cowe_specific_fwags)
{
	wwdev->dev->device_enabwe(wwdev->dev, cowe_specific_fwags);
}
static inwine void b43_device_disabwe(stwuct b43_wwdev *wwdev,
				      u32 cowe_specific_fwags)
{
	wwdev->dev->device_disabwe(wwdev->dev, cowe_specific_fwags);
}

static inwine u16 b43_wead16(stwuct b43_wwdev *dev, u16 offset)
{
	wetuwn dev->dev->wead16(dev->dev, offset);
}

static inwine void b43_wwite16(stwuct b43_wwdev *dev, u16 offset, u16 vawue)
{
	dev->dev->wwite16(dev->dev, offset, vawue);
}

/* To optimize this check fow fwush_wwites on BCM47XX_BCMA onwy. */
static inwine void b43_wwite16f(stwuct b43_wwdev *dev, u16 offset, u16 vawue)
{
	b43_wwite16(dev, offset, vawue);
#if defined(CONFIG_BCM47XX_BCMA)
	if (dev->dev->fwush_wwites)
		b43_wead16(dev, offset);
#endif
}

static inwine void b43_maskset16(stwuct b43_wwdev *dev, u16 offset, u16 mask,
				 u16 set)
{
	b43_wwite16(dev, offset, (b43_wead16(dev, offset) & mask) | set);
}

static inwine u32 b43_wead32(stwuct b43_wwdev *dev, u16 offset)
{
	wetuwn dev->dev->wead32(dev->dev, offset);
}

static inwine void b43_wwite32(stwuct b43_wwdev *dev, u16 offset, u32 vawue)
{
	dev->dev->wwite32(dev->dev, offset, vawue);
}

static inwine void b43_maskset32(stwuct b43_wwdev *dev, u16 offset, u32 mask,
				 u32 set)
{
	b43_wwite32(dev, offset, (b43_wead32(dev, offset) & mask) | set);
}

static inwine void b43_bwock_wead(stwuct b43_wwdev *dev, void *buffew,
				 size_t count, u16 offset, u8 weg_width)
{
	dev->dev->bwock_wead(dev->dev, buffew, count, offset, weg_width);
}

static inwine void b43_bwock_wwite(stwuct b43_wwdev *dev, const void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	dev->dev->bwock_wwite(dev->dev, buffew, count, offset, weg_width);
}

static inwine boow b43_using_pio_twansfews(stwuct b43_wwdev *dev)
{
	wetuwn dev->__using_pio_twansfews;
}

/* Message pwinting */
__pwintf(2, 3) void b43info(stwuct b43_ww *ww, const chaw *fmt, ...);
__pwintf(2, 3) void b43eww(stwuct b43_ww *ww, const chaw *fmt, ...);
__pwintf(2, 3) void b43wawn(stwuct b43_ww *ww, const chaw *fmt, ...);
__pwintf(2, 3) void b43dbg(stwuct b43_ww *ww, const chaw *fmt, ...);


/* A WAWN_ON vawiant that vanishes when b43 debugging is disabwed.
 * This _awso_ evawuates the awg with debugging disabwed. */
#if B43_DEBUG
# define B43_WAWN_ON(x)	WAWN_ON(x)
#ewse
static inwine boow __b43_wawn_on_dummy(boow x) { wetuwn x; }
# define B43_WAWN_ON(x)	__b43_wawn_on_dummy(unwikewy(!!(x)))
#endif

/* Convewt an integew to a Q5.2 vawue */
#define INT_TO_Q52(i)	((i) << 2)
/* Convewt a Q5.2 vawue to an integew (pwecision woss!) */
#define Q52_TO_INT(q52)	((q52) >> 2)
/* Macwos fow pwinting a vawue in Q5.2 fowmat */
#define Q52_FMT		"%u.%u"
#define Q52_AWG(q52)	Q52_TO_INT(q52), ((((q52) & 0x3) * 100) / 4)

#endif /* B43_H_ */
