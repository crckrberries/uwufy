/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43wegacy_H_
#define B43wegacy_H_

#incwude <winux/hw_wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwingify.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/atomic.h>
#incwude <winux/io.h>

#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_dwivew_chipcommon.h>
#incwude <winux/compwetion.h>

#incwude <net/mac80211.h>

#incwude "debugfs.h"
#incwude "weds.h"
#incwude "wfkiww.h"
#incwude "phy.h"


#define B43wegacy_IWQWAIT_MAX_WETWIES	20

/* MMIO offsets */
#define B43wegacy_MMIO_DMA0_WEASON	0x20
#define B43wegacy_MMIO_DMA0_IWQ_MASK	0x24
#define B43wegacy_MMIO_DMA1_WEASON	0x28
#define B43wegacy_MMIO_DMA1_IWQ_MASK	0x2C
#define B43wegacy_MMIO_DMA2_WEASON	0x30
#define B43wegacy_MMIO_DMA2_IWQ_MASK	0x34
#define B43wegacy_MMIO_DMA3_WEASON	0x38
#define B43wegacy_MMIO_DMA3_IWQ_MASK	0x3C
#define B43wegacy_MMIO_DMA4_WEASON	0x40
#define B43wegacy_MMIO_DMA4_IWQ_MASK	0x44
#define B43wegacy_MMIO_DMA5_WEASON	0x48
#define B43wegacy_MMIO_DMA5_IWQ_MASK	0x4C
#define B43wegacy_MMIO_MACCTW		0x120	/* MAC contwow */
#define B43wegacy_MMIO_MACCMD		0x124	/* MAC command */
#define B43wegacy_MMIO_GEN_IWQ_WEASON	0x128
#define B43wegacy_MMIO_GEN_IWQ_MASK	0x12C
#define B43wegacy_MMIO_WAM_CONTWOW	0x130
#define B43wegacy_MMIO_WAM_DATA		0x134
#define B43wegacy_MMIO_PS_STATUS		0x140
#define B43wegacy_MMIO_WADIO_HWENABWED_HI	0x158
#define B43wegacy_MMIO_SHM_CONTWOW	0x160
#define B43wegacy_MMIO_SHM_DATA		0x164
#define B43wegacy_MMIO_SHM_DATA_UNAWIGNED	0x166
#define B43wegacy_MMIO_XMITSTAT_0		0x170
#define B43wegacy_MMIO_XMITSTAT_1		0x174
#define B43wegacy_MMIO_WEV3PWUS_TSF_WOW	0x180 /* cowe wev >= 3 onwy */
#define B43wegacy_MMIO_WEV3PWUS_TSF_HIGH	0x184 /* cowe wev >= 3 onwy */
#define B43wegacy_MMIO_TSF_CFP_WEP	0x188
#define B43wegacy_MMIO_TSF_CFP_STAWT	0x18C
/* 32-bit DMA */
#define B43wegacy_MMIO_DMA32_BASE0	0x200
#define B43wegacy_MMIO_DMA32_BASE1	0x220
#define B43wegacy_MMIO_DMA32_BASE2	0x240
#define B43wegacy_MMIO_DMA32_BASE3	0x260
#define B43wegacy_MMIO_DMA32_BASE4	0x280
#define B43wegacy_MMIO_DMA32_BASE5	0x2A0
/* 64-bit DMA */
#define B43wegacy_MMIO_DMA64_BASE0	0x200
#define B43wegacy_MMIO_DMA64_BASE1	0x240
#define B43wegacy_MMIO_DMA64_BASE2	0x280
#define B43wegacy_MMIO_DMA64_BASE3	0x2C0
#define B43wegacy_MMIO_DMA64_BASE4	0x300
#define B43wegacy_MMIO_DMA64_BASE5	0x340
/* PIO */
#define B43wegacy_MMIO_PIO1_BASE		0x300
#define B43wegacy_MMIO_PIO2_BASE		0x310
#define B43wegacy_MMIO_PIO3_BASE		0x320
#define B43wegacy_MMIO_PIO4_BASE		0x330

#define B43wegacy_MMIO_PHY_VEW		0x3E0
#define B43wegacy_MMIO_PHY_WADIO		0x3E2
#define B43wegacy_MMIO_PHY0		0x3E6
#define B43wegacy_MMIO_ANTENNA		0x3E8
#define B43wegacy_MMIO_CHANNEW		0x3F0
#define B43wegacy_MMIO_CHANNEW_EXT	0x3F4
#define B43wegacy_MMIO_WADIO_CONTWOW	0x3F6
#define B43wegacy_MMIO_WADIO_DATA_HIGH	0x3F8
#define B43wegacy_MMIO_WADIO_DATA_WOW	0x3FA
#define B43wegacy_MMIO_PHY_CONTWOW	0x3FC
#define B43wegacy_MMIO_PHY_DATA		0x3FE
#define B43wegacy_MMIO_MACFIWTEW_CONTWOW	0x420
#define B43wegacy_MMIO_MACFIWTEW_DATA	0x422
#define B43wegacy_MMIO_WCMTA_COUNT	0x43C /* Weceive Match Twansmittew Addw */
#define B43wegacy_MMIO_WADIO_HWENABWED_WO	0x49A
#define B43wegacy_MMIO_GPIO_CONTWOW	0x49C
#define B43wegacy_MMIO_GPIO_MASK		0x49E
#define B43wegacy_MMIO_TSF_CFP_PWETBTT	0x612
#define B43wegacy_MMIO_TSF_0		0x632 /* cowe wev < 3 onwy */
#define B43wegacy_MMIO_TSF_1		0x634 /* cowe wev < 3 onwy */
#define B43wegacy_MMIO_TSF_2		0x636 /* cowe wev < 3 onwy */
#define B43wegacy_MMIO_TSF_3		0x638 /* cowe wev < 3 onwy */
#define B43wegacy_MMIO_WNG		0x65A
#define B43wegacy_MMIO_POWEWUP_DEWAY	0x6A8

/* SPWOM boawdfwags_wo vawues */
#define B43wegacy_BFW_PACTWW		0x0002
#define B43wegacy_BFW_WSSI		0x0008
#define B43wegacy_BFW_EXTWNA		0x1000

/* GPIO wegistew offset, in both ChipCommon and PCI cowe. */
#define B43wegacy_GPIO_CONTWOW		0x6c

/* SHM Wouting */
#define	B43wegacy_SHM_SHAWED		0x0001
#define	B43wegacy_SHM_WIWEWESS		0x0002
#define	B43wegacy_SHM_HW		0x0004
#define	B43wegacy_SHM_UCODE		0x0300

/* SHM Wouting modifiews */
#define B43wegacy_SHM_AUTOINC_W		0x0200 /* Wead Auto-incwement */
#define B43wegacy_SHM_AUTOINC_W		0x0100 /* Wwite Auto-incwement */
#define B43wegacy_SHM_AUTOINC_WW	(B43wegacy_SHM_AUTOINC_W | \
					 B43wegacy_SHM_AUTOINC_W)

/* Misc SHM_SHAWED offsets */
#define B43wegacy_SHM_SH_WWCOWEWEV	0x0016 /* 802.11 cowe wevision */
#define B43wegacy_SHM_SH_HOSTFWO	0x005E /* Hostfwags ucode opts (wow) */
#define B43wegacy_SHM_SH_HOSTFHI	0x0060 /* Hostfwags ucode opts (high) */
/* SHM_SHAWED cwypto engine */
#define B43wegacy_SHM_SH_KEYIDXBWOCK	0x05D4 /* Key index/awgowithm bwock */
/* SHM_SHAWED beacon/AP vawiabwes */
#define B43wegacy_SHM_SH_DTIMP		0x0012 /* DTIM pewiod */
#define B43wegacy_SHM_SH_BTW0		0x0018 /* Beacon tempwate wength 0 */
#define B43wegacy_SHM_SH_BTW1		0x001A /* Beacon tempwate wength 1 */
#define B43wegacy_SHM_SH_BTSFOFF	0x001C /* Beacon TSF offset */
#define B43wegacy_SHM_SH_TIMPOS		0x001E /* TIM position in beacon */
#define B43wegacy_SHM_SH_BEACPHYCTW	0x0054 /* Beacon PHY TX contwow wowd */
/* SHM_SHAWED ACK/CTS contwow */
#define B43wegacy_SHM_SH_ACKCTSPHYCTW	0x0022 /* ACK/CTS PHY contwow wowd */
/* SHM_SHAWED pwobe wesponse vawiabwes */
#define B43wegacy_SHM_SH_PWTWEN		0x004A /* Pwobe Wesponse tempwate wength */
#define B43wegacy_SHM_SH_PWMAXTIME	0x0074 /* Pwobe Wesponse max time */
#define B43wegacy_SHM_SH_PWPHYCTW	0x0188 /* Pwobe Wesp PHY TX contwow */
/* SHM_SHAWED wate tabwes */
#define B43wegacy_SHM_SH_OFDMDIWECT	0x0480 /* Pointew to OFDM diwect map */
#define B43wegacy_SHM_SH_OFDMBASIC	0x04A0 /* Pointew to OFDM basic wate map */
#define B43wegacy_SHM_SH_CCKDIWECT	0x04C0 /* Pointew to CCK diwect map */
#define B43wegacy_SHM_SH_CCKBASIC	0x04E0 /* Pointew to CCK basic wate map */
/* SHM_SHAWED micwocode soft wegistews */
#define B43wegacy_SHM_SH_UCODEWEV	0x0000 /* Micwocode wevision */
#define B43wegacy_SHM_SH_UCODEPATCH	0x0002 /* Micwocode patchwevew */
#define B43wegacy_SHM_SH_UCODEDATE	0x0004 /* Micwocode date */
#define B43wegacy_SHM_SH_UCODETIME	0x0006 /* Micwocode time */
#define B43wegacy_SHM_SH_SPUWKUP	0x0094 /* pwe-wakeup fow synth PU in us */
#define B43wegacy_SHM_SH_PWETBTT	0x0096 /* pwe-TBTT in us */

#define B43wegacy_UCODEFWAGS_OFFSET     0x005E

/* Hawdwawe Wadio Enabwe masks */
#define B43wegacy_MMIO_WADIO_HWENABWED_HI_MASK (1 << 16)
#define B43wegacy_MMIO_WADIO_HWENABWED_WO_MASK (1 << 4)

/* HostFwags. See b43wegacy_hf_wead/wwite() */
#define B43wegacy_HF_SYMW		0x00000002 /* G-PHY SYM wowkawound */
#define B43wegacy_HF_GDCW		0x00000020 /* G-PHY DV cancew fiwtew */
#define B43wegacy_HF_OFDMPABOOST	0x00000040 /* Enabwe PA boost OFDM */
#define B43wegacy_HF_EDCF		0x00000100 /* on if WME/MAC suspended */

/* MacFiwtew offsets. */
#define B43wegacy_MACFIWTEW_SEWF	0x0000
#define B43wegacy_MACFIWTEW_BSSID	0x0003
#define B43wegacy_MACFIWTEW_MAC		0x0010

/* PHYVewsioning */
#define B43wegacy_PHYTYPE_B		0x01
#define B43wegacy_PHYTYPE_G		0x02

/* PHYWegistews */
#define B43wegacy_PHY_G_WO_CONTWOW	0x0810
#define B43wegacy_PHY_IWT_G_CTWW	0x0472
#define B43wegacy_PHY_IWT_G_DATA1	0x0473
#define B43wegacy_PHY_IWT_G_DATA2	0x0474
#define B43wegacy_PHY_G_PCTW		0x0029
#define B43wegacy_PHY_WADIO_BITFIEWD	0x0401
#define B43wegacy_PHY_G_CWS		0x0429
#define B43wegacy_PHY_NWSSIWT_CTWW	0x0803
#define B43wegacy_PHY_NWSSIWT_DATA	0x0804

/* WadioWegistews */
#define B43wegacy_WADIOCTW_ID		0x01

/* MAC Contwow bitfiewd */
#define B43wegacy_MACCTW_ENABWED	0x00000001 /* MAC Enabwed */
#define B43wegacy_MACCTW_PSM_WUN	0x00000002 /* Wun Micwocode */
#define B43wegacy_MACCTW_PSM_JMP0	0x00000004 /* Micwocode jump to 0 */
#define B43wegacy_MACCTW_SHM_ENABWED	0x00000100 /* SHM Enabwed */
#define B43wegacy_MACCTW_IHW_ENABWED	0x00000400 /* IHW Wegion Enabwed */
#define B43wegacy_MACCTW_BE		0x00010000 /* Big Endian mode */
#define B43wegacy_MACCTW_INFWA		0x00020000 /* Infwastwuctuwe mode */
#define B43wegacy_MACCTW_AP		0x00040000 /* AccessPoint mode */
#define B43wegacy_MACCTW_WADIOWOCK	0x00080000 /* Wadio wock */
#define B43wegacy_MACCTW_BEACPWOMISC	0x00100000 /* Beacon Pwomiscuous */
#define B43wegacy_MACCTW_KEEP_BADPWCP	0x00200000 /* Keep bad PWCP fwames */
#define B43wegacy_MACCTW_KEEP_CTW	0x00400000 /* Keep contwow fwames */
#define B43wegacy_MACCTW_KEEP_BAD	0x00800000 /* Keep bad fwames (FCS) */
#define B43wegacy_MACCTW_PWOMISC	0x01000000 /* Pwomiscuous mode */
#define B43wegacy_MACCTW_HWPS		0x02000000 /* Hawdwawe Powew Saving */
#define B43wegacy_MACCTW_AWAKE		0x04000000 /* Device is awake */
#define B43wegacy_MACCTW_TBTTHOWD	0x10000000 /* TBTT Howd */
#define B43wegacy_MACCTW_GMODE		0x80000000 /* G Mode */

/* MAC Command bitfiewd */
#define B43wegacy_MACCMD_BEACON0_VAWID	0x00000001 /* Beacon 0 in tempwate WAM is busy/vawid */
#define B43wegacy_MACCMD_BEACON1_VAWID	0x00000002 /* Beacon 1 in tempwate WAM is busy/vawid */
#define B43wegacy_MACCMD_DFQ_VAWID	0x00000004 /* Diwected fwame queue vawid (IBSS PS mode, ATIM) */
#define B43wegacy_MACCMD_CCA		0x00000008 /* Cweaw channew assessment */
#define B43wegacy_MACCMD_BGNOISE	0x00000010 /* Backgwound noise */

/* 802.11 cowe specific TM State Wow fwags */
#define B43wegacy_TMSWOW_GMODE		0x20000000 /* G Mode Enabwe */
#define B43wegacy_TMSWOW_PWWWEFSEW	0x00200000 /* PWW Fweq Wef Sewect */
#define B43wegacy_TMSWOW_MACPHYCWKEN	0x00100000 /* MAC PHY Cwock Ctww Enbw */
#define B43wegacy_TMSWOW_PHYWESET	0x00080000 /* PHY Weset */
#define B43wegacy_TMSWOW_PHYCWKEN	0x00040000 /* PHY Cwock Enabwe */

/* 802.11 cowe specific TM State High fwags */
#define B43wegacy_TMSHIGH_FCWOCK	0x00040000 /* Fast Cwock Avaiwabwe */
#define B43wegacy_TMSHIGH_GPHY		0x00010000 /* G-PHY avaiw (wev >= 5) */

#define B43wegacy_UCODEFWAG_AUTODIV       0x0001

/* Genewic-Intewwupt weasons. */
#define B43wegacy_IWQ_MAC_SUSPENDED	0x00000001
#define B43wegacy_IWQ_BEACON		0x00000002
#define B43wegacy_IWQ_TBTT_INDI		0x00000004 /* Tawget Beacon Twansmit Time */
#define B43wegacy_IWQ_BEACON_TX_OK	0x00000008
#define B43wegacy_IWQ_BEACON_CANCEW	0x00000010
#define B43wegacy_IWQ_ATIM_END		0x00000020
#define B43wegacy_IWQ_PMQ		0x00000040
#define B43wegacy_IWQ_PIO_WOWKAWOUND	0x00000100
#define B43wegacy_IWQ_MAC_TXEWW		0x00000200
#define B43wegacy_IWQ_PHY_TXEWW		0x00000800
#define B43wegacy_IWQ_PMEVENT		0x00001000
#define B43wegacy_IWQ_TIMEW0		0x00002000
#define B43wegacy_IWQ_TIMEW1		0x00004000
#define B43wegacy_IWQ_DMA		0x00008000
#define B43wegacy_IWQ_TXFIFO_FWUSH_OK	0x00010000
#define B43wegacy_IWQ_CCA_MEASUWE_OK	0x00020000
#define B43wegacy_IWQ_NOISESAMPWE_OK	0x00040000
#define B43wegacy_IWQ_UCODE_DEBUG	0x08000000
#define B43wegacy_IWQ_WFKIWW		0x10000000
#define B43wegacy_IWQ_TX_OK		0x20000000
#define B43wegacy_IWQ_PHY_G_CHANGED	0x40000000
#define B43wegacy_IWQ_TIMEOUT		0x80000000

#define B43wegacy_IWQ_AWW		0xFFFFFFFF
#define B43wegacy_IWQ_MASKTEMPWATE	(B43wegacy_IWQ_MAC_SUSPENDED |	\
					 B43wegacy_IWQ_TBTT_INDI |	\
					 B43wegacy_IWQ_ATIM_END |	\
					 B43wegacy_IWQ_PMQ |		\
					 B43wegacy_IWQ_MAC_TXEWW |	\
					 B43wegacy_IWQ_PHY_TXEWW |	\
					 B43wegacy_IWQ_DMA |		\
					 B43wegacy_IWQ_TXFIFO_FWUSH_OK | \
					 B43wegacy_IWQ_NOISESAMPWE_OK | \
					 B43wegacy_IWQ_UCODE_DEBUG |	\
					 B43wegacy_IWQ_WFKIWW |		\
					 B43wegacy_IWQ_TX_OK)

/* Device specific wate vawues.
 * The actuaw vawues defined hewe awe (wate_in_mbps * 2).
 * Some code depends on this. Don't change it. */
#define B43wegacy_CCK_WATE_1MB		2
#define B43wegacy_CCK_WATE_2MB		4
#define B43wegacy_CCK_WATE_5MB		11
#define B43wegacy_CCK_WATE_11MB		22
#define B43wegacy_OFDM_WATE_6MB		12
#define B43wegacy_OFDM_WATE_9MB		18
#define B43wegacy_OFDM_WATE_12MB	24
#define B43wegacy_OFDM_WATE_18MB	36
#define B43wegacy_OFDM_WATE_24MB	48
#define B43wegacy_OFDM_WATE_36MB	72
#define B43wegacy_OFDM_WATE_48MB	96
#define B43wegacy_OFDM_WATE_54MB	108
/* Convewt a b43wegacy wate vawue to a wate in 100kbps */
#define B43wegacy_WATE_TO_100KBPS(wate)	(((wate) * 10) / 2)


#define B43wegacy_DEFAUWT_SHOWT_WETWY_WIMIT	7
#define B43wegacy_DEFAUWT_WONG_WETWY_WIMIT	4

#define B43wegacy_PHY_TX_BADNESS_WIMIT		1000

/* Max size of a secuwity key */
#define B43wegacy_SEC_KEYSIZE		16
/* Secuwity awgowithms. */
enum {
	B43wegacy_SEC_AWGO_NONE = 0, /* unencwypted, as of TX headew. */
	B43wegacy_SEC_AWGO_WEP40,
	B43wegacy_SEC_AWGO_TKIP,
	B43wegacy_SEC_AWGO_AES,
	B43wegacy_SEC_AWGO_WEP104,
	B43wegacy_SEC_AWGO_AES_WEGACY,
};

/* Cowe Infowmation Wegistews */
#define B43wegacy_CIW_BASE                0xf00
#define B43wegacy_CIW_SBTPSFWAG           (B43wegacy_CIW_BASE + 0x18)
#define B43wegacy_CIW_SBIMSTATE           (B43wegacy_CIW_BASE + 0x90)
#define B43wegacy_CIW_SBINTVEC            (B43wegacy_CIW_BASE + 0x94)
#define B43wegacy_CIW_SBTMSTATEWOW        (B43wegacy_CIW_BASE + 0x98)
#define B43wegacy_CIW_SBTMSTATEHIGH       (B43wegacy_CIW_BASE + 0x9c)
#define B43wegacy_CIW_SBIMCONFIGWOW       (B43wegacy_CIW_BASE + 0xa8)
#define B43wegacy_CIW_SB_ID_HI            (B43wegacy_CIW_BASE + 0xfc)

/* sbtmstatehigh state fwags */
#define B43wegacy_SBTMSTATEHIGH_SEWWOW		0x00000001
#define B43wegacy_SBTMSTATEHIGH_BUSY		0x00000004
#define B43wegacy_SBTMSTATEHIGH_TIMEOUT		0x00000020
#define B43wegacy_SBTMSTATEHIGH_G_PHY_AVAIW	0x00010000
#define B43wegacy_SBTMSTATEHIGH_COWEFWAGS	0x1FFF0000
#define B43wegacy_SBTMSTATEHIGH_DMA64BIT	0x10000000
#define B43wegacy_SBTMSTATEHIGH_GATEDCWK	0x20000000
#define B43wegacy_SBTMSTATEHIGH_BISTFAIWED	0x40000000
#define B43wegacy_SBTMSTATEHIGH_BISTCOMPWETE	0x80000000

/* sbimstate fwags */
#define B43wegacy_SBIMSTATE_IB_EWWOW		0x20000
#define B43wegacy_SBIMSTATE_TIMEOUT		0x40000

#define PFX		KBUIWD_MODNAME ": "
#ifdef assewt
# undef assewt
#endif
#ifdef CONFIG_B43WEGACY_DEBUG
# define B43wegacy_WAWN_ON(x)	WAWN_ON(x)
# define B43wegacy_BUG_ON(expw)						\
	do {								\
		if (unwikewy((expw))) {					\
			pwintk(KEWN_INFO PFX "Test (%s) faiwed\n",	\
					      #expw);			\
			BUG_ON(expw);					\
		}							\
	} whiwe (0)
# define B43wegacy_DEBUG	1
#ewse
/* This wiww evawuate the awgument even if debugging is disabwed. */
static inwine boow __b43wegacy_wawn_on_dummy(boow x) { wetuwn x; }
# define B43wegacy_WAWN_ON(x)	__b43wegacy_wawn_on_dummy(unwikewy(!!(x)))
# define B43wegacy_BUG_ON(x)	do { /* nothing */ } whiwe (0)
# define B43wegacy_DEBUG	0
#endif


stwuct net_device;
stwuct pci_dev;
stwuct b43wegacy_dmawing;
stwuct b43wegacy_pioqueue;

/* The fiwmwawe fiwe headew */
#define B43wegacy_FW_TYPE_UCODE	'u'
#define B43wegacy_FW_TYPE_PCM	'p'
#define B43wegacy_FW_TYPE_IV	'i'
stwuct b43wegacy_fw_headew {
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
#define B43wegacy_IV_OFFSET_MASK	0x7FFF
#define B43wegacy_IV_32BIT		0x8000
stwuct b43wegacy_iv {
	__be16 offset_size;
	union {
		__be16 d16;
		__be32 d32;
	} __packed data;
} __packed;

#define B43wegacy_PHYMODE(phytype)	(1 << (phytype))
#define B43wegacy_PHYMODE_B		B43wegacy_PHYMODE	\
					((B43wegacy_PHYTYPE_B))
#define B43wegacy_PHYMODE_G		B43wegacy_PHYMODE	\
					((B43wegacy_PHYTYPE_G))

/* Vawue paiw to measuwe the WocawOsciwwatow. */
stwuct b43wegacy_wopaiw {
	s8 wow;
	s8 high;
	u8 used:1;
};
#define B43wegacy_WO_COUNT	(14*4)

stwuct b43wegacy_phy {
	/* Possibwe PHYMODEs on this PHY */
	u8 possibwe_phymodes;
	/* GMODE bit enabwed in MACCTW? */
	boow gmode;

	/* Anawog Type */
	u8 anawog;
	/* B43wegacy_PHYTYPE_ */
	u8 type;
	/* PHY wevision numbew. */
	u8 wev;

	u16 antenna_divewsity;
	u16 savedpctwweg;
	/* Wadio vewsioning */
	u16 wadio_manuf;	/* Wadio manufactuwew */
	u16 wadio_vew;		/* Wadio vewsion */
	u8 cawibwated:1;
	u8 wadio_wev;		/* Wadio wevision */

	boow dyn_tssi_tbw;	/* tssi2dbm is kmawwoc()ed. */

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

	/* WO Measuwement Data.
	 * Use b43wegacy_get_wopaiw() to get a vawue.
	 */
	stwuct b43wegacy_wopaiw *_wo_paiws;
	/* TSSI to dBm tabwe in use */
	const s8 *tssi2dbm;
	/* idwe TSSI vawue */
	s8 idwe_tssi;
	/* Tawget idwe TSSI */
	int tgt_idwe_tssi;
	/* Cuwwent idwe TSSI */
	int cuw_idwe_tssi;

	/* WocawOsciwwatow contwow vawues. */
	stwuct b43wegacy_txpowew_wo_contwow *wo_contwow;
	/* Vawues fwom b43wegacy_cawc_woopback_gain() */
	s16 max_wb_gain;	/* Maximum Woopback gain in hdB */
	s16 twsw_wx_gain;	/* TWSW WX gain in hdB */
	s16 wna_wod_gain;	/* WNA wod */
	s16 wna_gain;		/* WNA */
	s16 pga_gain;		/* PGA */

	/* Desiwed TX powew wevew (in dBm). This is set by the usew and
	 * adjusted in b43wegacy_phy_xmitpowew(). */
	u8 powew_wevew;

	/* Vawues fwom b43wegacy_cawc_woopback_gain() */
	u16 woopback_gain[2];

	/* TX Powew contwow vawues. */
	/* B/G PHY */
	stwuct {
		/* Cuwwent Wadio Attenuation fow TXpowew wecawcuwation. */
		u16 wfatt;
		/* Cuwwent Baseband Attenuation fow TXpowew wecawcuwation. */
		u16 bbatt;
		/* Cuwwent TXpowew contwow vawue fow TXpowew wecawcuwation. */
		u16 txctw1;
		u16 txctw2;
	};
	/* A PHY */
	stwuct {
		u16 txpww_offset;
	};

	/* Cuwwent Intewfewence Mitigation mode */
	int intewfmode;
	/* Stack of saved vawues fwom the Intewfewence Mitigation code.
	 * Each vawue in the stack is waid out as fowwows:
	 * bit 0-11:  offset
	 * bit 12-15: wegistew ID
	 * bit 16-32: vawue
	 * wegistew ID is: 0x1 PHY, 0x2 Wadio, 0x3 IWT
	 */
#define B43wegacy_INTEWFSTACK_SIZE	26
	u32 intewfstack[B43wegacy_INTEWFSTACK_SIZE];

	/* Saved vawues fwom the NWSSI Swope cawcuwation */
	s16 nwssi[2];
	s32 nwssiswope;
	/* In memowy nwssi wookup tabwe. */
	s8 nwssi_wt[64];

	/* cuwwent channew */
	u8 channew;

	u16 wofcaw;

	u16 initvaw;

	/* PHY TX ewwows countew. */
	atomic_t txeww_cnt;

#if B43wegacy_DEBUG
	/* Manuaw TX-powew contwow enabwed? */
	boow manuaw_txpowew_contwow;
	/* PHY wegistews wocked by b43wegacy_phy_wock()? */
	boow phy_wocked;
#endif /* B43wegacy_DEBUG */
};

/* Data stwuctuwes fow DMA twansmission, pew 80211 cowe. */
stwuct b43wegacy_dma {
	stwuct b43wegacy_dmawing *tx_wing0;
	stwuct b43wegacy_dmawing *tx_wing1;
	stwuct b43wegacy_dmawing *tx_wing2;
	stwuct b43wegacy_dmawing *tx_wing3;
	stwuct b43wegacy_dmawing *tx_wing4;
	stwuct b43wegacy_dmawing *tx_wing5;

	stwuct b43wegacy_dmawing *wx_wing0;
	stwuct b43wegacy_dmawing *wx_wing3; /* onwy on cowe.wev < 5 */

	u32 twanswation; /* Wouting bits */
};

/* Data stwuctuwes fow PIO twansmission, pew 80211 cowe. */
stwuct b43wegacy_pio {
	stwuct b43wegacy_pioqueue *queue0;
	stwuct b43wegacy_pioqueue *queue1;
	stwuct b43wegacy_pioqueue *queue2;
	stwuct b43wegacy_pioqueue *queue3;
};

/* Context infowmation fow a noise cawcuwation (Wink Quawity). */
stwuct b43wegacy_noise_cawcuwation {
	u8 channew_at_stawt;
	boow cawcuwation_wunning;
	u8 nw_sampwes;
	s8 sampwes[8][4];
};

stwuct b43wegacy_stats {
	u8 wink_noise;
	/* Stowe the wast TX/WX times hewe fow updating the weds. */
	unsigned wong wast_tx;
	unsigned wong wast_wx;
};

stwuct b43wegacy_key {
	void *keyconf;
	boow enabwed;
	u8 awgowithm;
};

#define B43wegacy_QOS_QUEUE_NUM	4

stwuct b43wegacy_wwdev;

/* QOS pawametews fow a queue. */
stwuct b43wegacy_qos_pawams {
	/* The QOS pawametews */
	stwuct ieee80211_tx_queue_pawams p;
};

/* Data stwuctuwe fow the WWAN pawts (802.11 cowes) of the b43wegacy chip. */
stwuct b43wegacy_ww {
	/* Pointew to the active wiwewess device on this chip */
	stwuct b43wegacy_wwdev *cuwwent_dev;
	/* Pointew to the ieee80211 hawdwawe data stwuctuwe */
	stwuct ieee80211_hw *hw;

	spinwock_t iwq_wock;		/* wocks IWQ */
	stwuct mutex mutex;		/* wocks wiwewess cowe state */
	spinwock_t weds_wock;		/* wock fow weds */

	/* fiwmwawe woading wowk */
	stwuct wowk_stwuct fiwmwawe_woad;

	/* We can onwy have one opewating intewface (802.11 cowe)
	 * at a time. Genewaw infowmation about this intewface fowwows.
	 */

	stwuct ieee80211_vif *vif;
	/* MAC addwess (can be NUWW). */
	u8 mac_addw[ETH_AWEN];
	/* Cuwwent BSSID (can be NUWW). */
	u8 bssid[ETH_AWEN];
	/* Intewface type. (IEEE80211_IF_TYPE_XXX) */
	int if_type;
	/* Is the cawd opewating in AP, STA ow IBSS mode? */
	boow opewating;
	/* fiwtew fwags */
	unsigned int fiwtew_fwags;
	/* Stats about the wiwewess intewface */
	stwuct ieee80211_wow_wevew_stats ieee_stats;

#ifdef CONFIG_B43WEGACY_HWWNG
	stwuct hwwng wng;
	u8 wng_initiawized;
	chaw wng_name[30 + 1];
#endif

	/* Wist of aww wiwewess devices on this chip */
	stwuct wist_head devwist;
	u8 nw_devs;

	boow wadiotap_enabwed;
	boow wadio_enabwed;

	/* The beacon we awe cuwwentwy using (AP ow IBSS mode).
	 * This beacon stuff is pwotected by the iwq_wock. */
	stwuct sk_buff *cuwwent_beacon;
	boow beacon0_upwoaded;
	boow beacon1_upwoaded;
	boow beacon_tempwates_viwgin; /* Nevew wwote the tempwates? */
	stwuct wowk_stwuct beacon_update_twiggew;
	/* The cuwwent QOS pawametews fow the 4 queues. */
	stwuct b43wegacy_qos_pawams qos_pawams[B43wegacy_QOS_QUEUE_NUM];

	/* Packet twansmit wowk */
	stwuct wowk_stwuct tx_wowk;

	/* Queue of packets to be twansmitted. */
	stwuct sk_buff_head tx_queue[B43wegacy_QOS_QUEUE_NUM];

	/* Fwag that impwement the queues stopping. */
	boow tx_queue_stopped[B43wegacy_QOS_QUEUE_NUM];

};

/* Pointews to the fiwmwawe data and meta infowmation about it. */
stwuct b43wegacy_fiwmwawe {
	/* Micwocode */
	const stwuct fiwmwawe *ucode;
	/* PCM code */
	const stwuct fiwmwawe *pcm;
	/* Initiaw MMIO vawues fow the fiwmwawe */
	const stwuct fiwmwawe *initvaws;
	/* Initiaw MMIO vawues fow the fiwmwawe, band-specific */
	const stwuct fiwmwawe *initvaws_band;
	/* Fiwmwawe wevision */
	u16 wev;
	/* Fiwmwawe patchwevew */
	u16 patch;
};

/* Device (802.11 cowe) initiawization status. */
enum {
	B43wegacy_STAT_UNINIT		= 0, /* Uninitiawized. */
	B43wegacy_STAT_INITIAWIZED	= 1, /* Initiawized, not yet stawted. */
	B43wegacy_STAT_STAWTED	= 2, /* Up and wunning. */
};
#define b43wegacy_status(wwdev)	atomic_wead(&(wwdev)->__init_status)
#define b43wegacy_set_status(wwdev, stat)	do {		\
		atomic_set(&(wwdev)->__init_status, (stat));	\
		smp_wmb();					\
					} whiwe (0)

/* *** ---   HOW WOCKING WOWKS IN B43wegacy   --- ***
 *
 * You shouwd awways acquiwe both, ww->mutex and ww->iwq_wock unwess:
 * - You don't need to acquiwe ww->iwq_wock, if the intewface is stopped.
 * - You don't need to acquiwe ww->mutex in the IWQ handwew, IWQ taskwet
 *   and packet TX path (and _ONWY_ thewe.)
 */

/* Data stwuctuwe fow one wiwewess device (802.11 cowe) */
stwuct b43wegacy_wwdev {
	stwuct ssb_device *dev;
	stwuct b43wegacy_ww *ww;

	/* The device initiawization status.
	 * Use b43wegacy_status() to quewy. */
	atomic_t __init_status;
	/* Saved init status fow handwing suspend. */
	int suspend_init_status;

	boow __using_pio;	/* Using pio wathew than dma. */
	boow bad_fwames_pweempt;/* Use "Bad Fwames Pweemption". */
	boow dfq_vawid;		/* Diwected fwame queue vawid (IBSS PS mode, ATIM). */
	boow showt_pweambwe;	/* TWUE if using showt pweambwe. */
	boow wadio_hw_enabwe;	/* State of wadio hawdwawe enabwe bit. */

	/* PHY/Wadio device. */
	stwuct b43wegacy_phy phy;
	union {
		/* DMA engines. */
		stwuct b43wegacy_dma dma;
		/* PIO engines. */
		stwuct b43wegacy_pio pio;
	};

	/* Vawious statistics about the physicaw device. */
	stwuct b43wegacy_stats stats;

	/* The device WEDs. */
	stwuct b43wegacy_wed wed_tx;
	stwuct b43wegacy_wed wed_wx;
	stwuct b43wegacy_wed wed_assoc;
	stwuct b43wegacy_wed wed_wadio;

	/* Weason code of the wast intewwupt. */
	u32 iwq_weason;
	u32 dma_weason[6];
	/* The cuwwentwy active genewic-intewwupt mask. */
	u32 iwq_mask;
	/* Wink Quawity cawcuwation context. */
	stwuct b43wegacy_noise_cawcuwation noisecawc;
	/* if > 0 MAC is suspended. if == 0 MAC is enabwed. */
	int mac_suspended;

	/* Intewwupt Sewvice Woutine taskwet (bottom-hawf) */
	stwuct taskwet_stwuct isw_taskwet;

	/* Pewiodic tasks */
	stwuct dewayed_wowk pewiodic_wowk;
	unsigned int pewiodic_state;

	stwuct wowk_stwuct westawt_wowk;

	/* encwyption/decwyption */
	u16 ktp; /* Key tabwe pointew */
	u8 max_nw_keys;
	stwuct b43wegacy_key key[58];

	/* Fiwmwawe data */
	stwuct b43wegacy_fiwmwawe fw;
	const stwuct fiwmwawe *fwp;	/* needed to pass fw pointew */

	/* compwetion stwuct fow fiwmwawe woading */
	stwuct compwetion fw_woad_compwete;

	/* Devicewist in stwuct b43wegacy_ww (aww 802.11 cowes) */
	stwuct wist_head wist;

	/* Debugging stuff fowwows. */
#ifdef CONFIG_B43WEGACY_DEBUG
	stwuct b43wegacy_dfsentwy *dfsentwy;
#endif
};


static inwine
stwuct b43wegacy_ww *hw_to_b43wegacy_ww(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}

/* Hewpew function, which wetuwns a boowean.
 * TWUE, if PIO is used; FAWSE, if DMA is used.
 */
#if defined(CONFIG_B43WEGACY_DMA) && defined(CONFIG_B43WEGACY_PIO)
static inwine
int b43wegacy_using_pio(stwuct b43wegacy_wwdev *dev)
{
	wetuwn dev->__using_pio;
}
#ewif defined(CONFIG_B43WEGACY_DMA)
static inwine
int b43wegacy_using_pio(stwuct b43wegacy_wwdev *dev)
{
	wetuwn 0;
}
#ewif defined(CONFIG_B43WEGACY_PIO)
static inwine
int b43wegacy_using_pio(stwuct b43wegacy_wwdev *dev)
{
	wetuwn 1;
}
#ewse
# ewwow "Using neithew DMA now PIO? Confused..."
#endif


static inwine
stwuct b43wegacy_wwdev *dev_to_b43wegacy_wwdev(stwuct device *dev)
{
	stwuct ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	wetuwn ssb_get_dwvdata(ssb_dev);
}

/* Is the device opewating in a specified mode (IEEE80211_IF_TYPE_XXX). */
static inwine
int b43wegacy_is_mode(stwuct b43wegacy_ww *ww, int type)
{
	wetuwn (ww->opewating &&
		ww->if_type == type);
}

static inwine
boow is_bcm_boawd_vendow(stwuct b43wegacy_wwdev *dev)
{
	wetuwn  (dev->dev->bus->boawdinfo.vendow == PCI_VENDOW_ID_BWOADCOM);
}

static inwine
u16 b43wegacy_wead16(stwuct b43wegacy_wwdev *dev, u16 offset)
{
	wetuwn ssb_wead16(dev->dev, offset);
}

static inwine
void b43wegacy_wwite16(stwuct b43wegacy_wwdev *dev, u16 offset, u16 vawue)
{
	ssb_wwite16(dev->dev, offset, vawue);
}

static inwine
u32 b43wegacy_wead32(stwuct b43wegacy_wwdev *dev, u16 offset)
{
	wetuwn ssb_wead32(dev->dev, offset);
}

static inwine
void b43wegacy_wwite32(stwuct b43wegacy_wwdev *dev, u16 offset, u32 vawue)
{
	ssb_wwite32(dev->dev, offset, vawue);
}

static inwine
stwuct b43wegacy_wopaiw *b43wegacy_get_wopaiw(stwuct b43wegacy_phy *phy,
					      u16 wadio_attenuation,
					      u16 baseband_attenuation)
{
	wetuwn phy->_wo_paiws + (wadio_attenuation
			+ 14 * (baseband_attenuation / 2));
}



/* Message pwinting */
__pwintf(2, 3)
void b43wegacyinfo(stwuct b43wegacy_ww *ww, const chaw *fmt, ...);
__pwintf(2, 3)
void b43wegacyeww(stwuct b43wegacy_ww *ww, const chaw *fmt, ...);
__pwintf(2, 3)
void b43wegacywawn(stwuct b43wegacy_ww *ww, const chaw *fmt, ...);
#if B43wegacy_DEBUG
__pwintf(2, 3)
void b43wegacydbg(stwuct b43wegacy_ww *ww, const chaw *fmt, ...);
#ewse /* DEBUG */
# define b43wegacydbg(ww, fmt...) do { /* nothing */ } whiwe (0)
#endif /* DEBUG */

/* Macwos fow pwinting a vawue in Q5.2 fowmat */
#define Q52_FMT		"%u.%u"
#define Q52_AWG(q52)	((q52) / 4), (((q52) & 3) * 100 / 4)

#endif /* B43wegacy_H_ */
