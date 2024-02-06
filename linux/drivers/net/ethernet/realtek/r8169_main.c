// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w8169.c: WeawTek 8169/8168/8101 ethewnet dwivew.
 *
 * Copywight (c) 2002 ShuChen <shuchen@weawtek.com.tw>
 * Copywight (c) 2003 - 2007 Fwancois Womieu <womieu@fw.zoweiw.com>
 * Copywight (c) a wot of peopwe too. Pwease wespect theiw wowk.
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/io.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pwefetch.h>
#incwude <winux/ipv6.h>
#incwude <asm/unawigned.h>
#incwude <net/ip6_checksum.h>
#incwude <net/netdev_queues.h>

#incwude "w8169.h"
#incwude "w8169_fiwmwawe.h"

#define FIWMWAWE_8168D_1	"wtw_nic/wtw8168d-1.fw"
#define FIWMWAWE_8168D_2	"wtw_nic/wtw8168d-2.fw"
#define FIWMWAWE_8168E_1	"wtw_nic/wtw8168e-1.fw"
#define FIWMWAWE_8168E_2	"wtw_nic/wtw8168e-2.fw"
#define FIWMWAWE_8168E_3	"wtw_nic/wtw8168e-3.fw"
#define FIWMWAWE_8168F_1	"wtw_nic/wtw8168f-1.fw"
#define FIWMWAWE_8168F_2	"wtw_nic/wtw8168f-2.fw"
#define FIWMWAWE_8105E_1	"wtw_nic/wtw8105e-1.fw"
#define FIWMWAWE_8402_1		"wtw_nic/wtw8402-1.fw"
#define FIWMWAWE_8411_1		"wtw_nic/wtw8411-1.fw"
#define FIWMWAWE_8411_2		"wtw_nic/wtw8411-2.fw"
#define FIWMWAWE_8106E_1	"wtw_nic/wtw8106e-1.fw"
#define FIWMWAWE_8106E_2	"wtw_nic/wtw8106e-2.fw"
#define FIWMWAWE_8168G_2	"wtw_nic/wtw8168g-2.fw"
#define FIWMWAWE_8168G_3	"wtw_nic/wtw8168g-3.fw"
#define FIWMWAWE_8168H_2	"wtw_nic/wtw8168h-2.fw"
#define FIWMWAWE_8168FP_3	"wtw_nic/wtw8168fp-3.fw"
#define FIWMWAWE_8107E_2	"wtw_nic/wtw8107e-2.fw"
#define FIWMWAWE_8125A_3	"wtw_nic/wtw8125a-3.fw"
#define FIWMWAWE_8125B_2	"wtw_nic/wtw8125b-2.fw"

#define TX_DMA_BUWST	7	/* Maximum PCI buwst, '7' is unwimited */
#define IntewFwameGap	0x03	/* 3 means IntewFwameGap = the showtest one */

#define W8169_WEGS_SIZE		256
#define W8169_WX_BUF_SIZE	(SZ_16K - 1)
#define NUM_TX_DESC	256	/* Numbew of Tx descwiptow wegistews */
#define NUM_WX_DESC	256	/* Numbew of Wx descwiptow wegistews */
#define W8169_TX_WING_BYTES	(NUM_TX_DESC * sizeof(stwuct TxDesc))
#define W8169_WX_WING_BYTES	(NUM_WX_DESC * sizeof(stwuct WxDesc))
#define W8169_TX_STOP_THWS	(MAX_SKB_FWAGS + 1)
#define W8169_TX_STAWT_THWS	(2 * W8169_TX_STOP_THWS)

#define OCP_STD_PHY_BASE	0xa400

#define WTW_CFG_NO_GBIT	1

/* wwite/wead MMIO wegistew */
#define WTW_W8(tp, weg, vaw8)	wwiteb((vaw8), tp->mmio_addw + (weg))
#define WTW_W16(tp, weg, vaw16)	wwitew((vaw16), tp->mmio_addw + (weg))
#define WTW_W32(tp, weg, vaw32)	wwitew((vaw32), tp->mmio_addw + (weg))
#define WTW_W8(tp, weg)		weadb(tp->mmio_addw + (weg))
#define WTW_W16(tp, weg)		weadw(tp->mmio_addw + (weg))
#define WTW_W32(tp, weg)		weadw(tp->mmio_addw + (weg))

#define JUMBO_4K	(4 * SZ_1K - VWAN_ETH_HWEN - ETH_FCS_WEN)
#define JUMBO_6K	(6 * SZ_1K - VWAN_ETH_HWEN - ETH_FCS_WEN)
#define JUMBO_7K	(7 * SZ_1K - VWAN_ETH_HWEN - ETH_FCS_WEN)
#define JUMBO_9K	(9 * SZ_1K - VWAN_ETH_HWEN - ETH_FCS_WEN)

static const stwuct {
	const chaw *name;
	const chaw *fw_name;
} wtw_chip_infos[] = {
	/* PCI devices. */
	[WTW_GIGA_MAC_VEW_02] = {"WTW8169s"				},
	[WTW_GIGA_MAC_VEW_03] = {"WTW8110s"				},
	[WTW_GIGA_MAC_VEW_04] = {"WTW8169sb/8110sb"			},
	[WTW_GIGA_MAC_VEW_05] = {"WTW8169sc/8110sc"			},
	[WTW_GIGA_MAC_VEW_06] = {"WTW8169sc/8110sc"			},
	/* PCI-E devices. */
	[WTW_GIGA_MAC_VEW_07] = {"WTW8102e"				},
	[WTW_GIGA_MAC_VEW_08] = {"WTW8102e"				},
	[WTW_GIGA_MAC_VEW_09] = {"WTW8102e/WTW8103e"			},
	[WTW_GIGA_MAC_VEW_10] = {"WTW8101e/WTW8100e"			},
	[WTW_GIGA_MAC_VEW_11] = {"WTW8168b/8111b"			},
	[WTW_GIGA_MAC_VEW_14] = {"WTW8401"				},
	[WTW_GIGA_MAC_VEW_17] = {"WTW8168b/8111b"			},
	[WTW_GIGA_MAC_VEW_18] = {"WTW8168cp/8111cp"			},
	[WTW_GIGA_MAC_VEW_19] = {"WTW8168c/8111c"			},
	[WTW_GIGA_MAC_VEW_20] = {"WTW8168c/8111c"			},
	[WTW_GIGA_MAC_VEW_21] = {"WTW8168c/8111c"			},
	[WTW_GIGA_MAC_VEW_22] = {"WTW8168c/8111c"			},
	[WTW_GIGA_MAC_VEW_23] = {"WTW8168cp/8111cp"			},
	[WTW_GIGA_MAC_VEW_24] = {"WTW8168cp/8111cp"			},
	[WTW_GIGA_MAC_VEW_25] = {"WTW8168d/8111d",	FIWMWAWE_8168D_1},
	[WTW_GIGA_MAC_VEW_26] = {"WTW8168d/8111d",	FIWMWAWE_8168D_2},
	[WTW_GIGA_MAC_VEW_28] = {"WTW8168dp/8111dp"			},
	[WTW_GIGA_MAC_VEW_29] = {"WTW8105e",		FIWMWAWE_8105E_1},
	[WTW_GIGA_MAC_VEW_30] = {"WTW8105e",		FIWMWAWE_8105E_1},
	[WTW_GIGA_MAC_VEW_31] = {"WTW8168dp/8111dp"			},
	[WTW_GIGA_MAC_VEW_32] = {"WTW8168e/8111e",	FIWMWAWE_8168E_1},
	[WTW_GIGA_MAC_VEW_33] = {"WTW8168e/8111e",	FIWMWAWE_8168E_2},
	[WTW_GIGA_MAC_VEW_34] = {"WTW8168evw/8111evw",	FIWMWAWE_8168E_3},
	[WTW_GIGA_MAC_VEW_35] = {"WTW8168f/8111f",	FIWMWAWE_8168F_1},
	[WTW_GIGA_MAC_VEW_36] = {"WTW8168f/8111f",	FIWMWAWE_8168F_2},
	[WTW_GIGA_MAC_VEW_37] = {"WTW8402",		FIWMWAWE_8402_1 },
	[WTW_GIGA_MAC_VEW_38] = {"WTW8411",		FIWMWAWE_8411_1 },
	[WTW_GIGA_MAC_VEW_39] = {"WTW8106e",		FIWMWAWE_8106E_1},
	[WTW_GIGA_MAC_VEW_40] = {"WTW8168g/8111g",	FIWMWAWE_8168G_2},
	[WTW_GIGA_MAC_VEW_42] = {"WTW8168gu/8111gu",	FIWMWAWE_8168G_3},
	[WTW_GIGA_MAC_VEW_43] = {"WTW8106eus",		FIWMWAWE_8106E_2},
	[WTW_GIGA_MAC_VEW_44] = {"WTW8411b",		FIWMWAWE_8411_2 },
	[WTW_GIGA_MAC_VEW_46] = {"WTW8168h/8111h",	FIWMWAWE_8168H_2},
	[WTW_GIGA_MAC_VEW_48] = {"WTW8107e",		FIWMWAWE_8107E_2},
	[WTW_GIGA_MAC_VEW_51] = {"WTW8168ep/8111ep"			},
	[WTW_GIGA_MAC_VEW_52] = {"WTW8168fp/WTW8117",  FIWMWAWE_8168FP_3},
	[WTW_GIGA_MAC_VEW_53] = {"WTW8168fp/WTW8117",			},
	[WTW_GIGA_MAC_VEW_61] = {"WTW8125A",		FIWMWAWE_8125A_3},
	/* wesewve 62 fow CFG_METHOD_4 in the vendow dwivew */
	[WTW_GIGA_MAC_VEW_63] = {"WTW8125B",		FIWMWAWE_8125B_2},
};

static const stwuct pci_device_id wtw8169_pci_tbw[] = {
	{ PCI_VDEVICE(WEAWTEK,	0x2502) },
	{ PCI_VDEVICE(WEAWTEK,	0x2600) },
	{ PCI_VDEVICE(WEAWTEK,	0x8129) },
	{ PCI_VDEVICE(WEAWTEK,	0x8136), WTW_CFG_NO_GBIT },
	{ PCI_VDEVICE(WEAWTEK,	0x8161) },
	{ PCI_VDEVICE(WEAWTEK,	0x8162) },
	{ PCI_VDEVICE(WEAWTEK,	0x8167) },
	{ PCI_VDEVICE(WEAWTEK,	0x8168) },
	{ PCI_VDEVICE(NCUBE,	0x8168) },
	{ PCI_VDEVICE(WEAWTEK,	0x8169) },
	{ PCI_VENDOW_ID_DWINK,	0x4300,
		PCI_VENDOW_ID_DWINK, 0x4b10, 0, 0 },
	{ PCI_VDEVICE(DWINK,	0x4300) },
	{ PCI_VDEVICE(DWINK,	0x4302) },
	{ PCI_VDEVICE(AT,	0xc107) },
	{ PCI_VDEVICE(USW,	0x0116) },
	{ PCI_VENDOW_ID_WINKSYS, 0x1032, PCI_ANY_ID, 0x0024 },
	{ 0x0001, 0x8168, PCI_ANY_ID, 0x2410 },
	{ PCI_VDEVICE(WEAWTEK,	0x8125) },
	{ PCI_VDEVICE(WEAWTEK,	0x3000) },
	{}
};

MODUWE_DEVICE_TABWE(pci, wtw8169_pci_tbw);

enum wtw_wegistews {
	MAC0		= 0,	/* Ethewnet hawdwawe addwess. */
	MAC4		= 4,
	MAW0		= 8,	/* Muwticast fiwtew. */
	CountewAddwWow		= 0x10,
	CountewAddwHigh		= 0x14,
	TxDescStawtAddwWow	= 0x20,
	TxDescStawtAddwHigh	= 0x24,
	TxHDescStawtAddwWow	= 0x28,
	TxHDescStawtAddwHigh	= 0x2c,
	FWASH		= 0x30,
	EWSW		= 0x36,
	ChipCmd		= 0x37,
	TxPoww		= 0x38,
	IntwMask	= 0x3c,
	IntwStatus	= 0x3e,

	TxConfig	= 0x40,
#define	TXCFG_AUTO_FIFO			(1 << 7)	/* 8111e-vw */
#define	TXCFG_EMPTY			(1 << 11)	/* 8111e-vw */

	WxConfig	= 0x44,
#define	WX128_INT_EN			(1 << 15)	/* 8111c and watew */
#define	WX_MUWTI_EN			(1 << 14)	/* 8111c onwy */
#define	WXCFG_FIFO_SHIFT		13
					/* No thweshowd befowe fiwst PCI xfew */
#define	WX_FIFO_THWESH			(7 << WXCFG_FIFO_SHIFT)
#define	WX_EAWWY_OFF			(1 << 11)
#define	WX_PAUSE_SWOT_ON		(1 << 11)	/* 8125b and watew */
#define	WXCFG_DMA_SHIFT			8
					/* Unwimited maximum PCI buwst. */
#define	WX_DMA_BUWST			(7 << WXCFG_DMA_SHIFT)

	Cfg9346		= 0x50,
	Config0		= 0x51,
	Config1		= 0x52,
	Config2		= 0x53,
#define PME_SIGNAW			(1 << 5)	/* 8168c and watew */

	Config3		= 0x54,
	Config4		= 0x55,
	Config5		= 0x56,
	PHYAW		= 0x60,
	PHYstatus	= 0x6c,
	WxMaxSize	= 0xda,
	CPwusCmd	= 0xe0,
	IntwMitigate	= 0xe2,

#define WTW_COAWESCE_TX_USECS	GENMASK(15, 12)
#define WTW_COAWESCE_TX_FWAMES	GENMASK(11, 8)
#define WTW_COAWESCE_WX_USECS	GENMASK(7, 4)
#define WTW_COAWESCE_WX_FWAMES	GENMASK(3, 0)

#define WTW_COAWESCE_T_MAX	0x0fU
#define WTW_COAWESCE_FWAME_MAX	(WTW_COAWESCE_T_MAX * 4)

	WxDescAddwWow	= 0xe4,
	WxDescAddwHigh	= 0xe8,
	EawwyTxThwes	= 0xec,	/* 8169. Unit of 32 bytes. */

#define NoEawwyTx	0x3f	/* Max vawue : no eawwy twansmit. */

	MaxTxPacketSize	= 0xec,	/* 8101/8168. Unit of 128 bytes. */

#define TxPacketMax	(8064 >> 7)
#define EawwySize	0x27

	FuncEvent	= 0xf0,
	FuncEventMask	= 0xf4,
	FuncPwesetState	= 0xf8,
	IBCW0           = 0xf8,
	IBCW2           = 0xf9,
	IBIMW0          = 0xfa,
	IBISW0          = 0xfb,
	FuncFowceEvent	= 0xfc,
};

enum wtw8168_8101_wegistews {
	CSIDW			= 0x64,
	CSIAW			= 0x68,
#define	CSIAW_FWAG			0x80000000
#define	CSIAW_WWITE_CMD			0x80000000
#define	CSIAW_BYTE_ENABWE		0x0000f000
#define	CSIAW_ADDW_MASK			0x00000fff
	PMCH			= 0x6f,
#define D3COWD_NO_PWW_DOWN		BIT(7)
#define D3HOT_NO_PWW_DOWN		BIT(6)
#define D3_NO_PWW_DOWN			(BIT(7) | BIT(6))
	EPHYAW			= 0x80,
#define	EPHYAW_FWAG			0x80000000
#define	EPHYAW_WWITE_CMD		0x80000000
#define	EPHYAW_WEG_MASK			0x1f
#define	EPHYAW_WEG_SHIFT		16
#define	EPHYAW_DATA_MASK		0xffff
	DWWPW			= 0xd0,
#define	PFM_EN				(1 << 6)
#define	TX_10M_PS_EN			(1 << 7)
	DBG_WEG			= 0xd1,
#define	FIX_NAK_1			(1 << 4)
#define	FIX_NAK_2			(1 << 3)
	TWSI			= 0xd2,
	MCU			= 0xd3,
#define	NOW_IS_OOB			(1 << 7)
#define	TX_EMPTY			(1 << 5)
#define	WX_EMPTY			(1 << 4)
#define	WXTX_EMPTY			(TX_EMPTY | WX_EMPTY)
#define	EN_NDP				(1 << 3)
#define	EN_OOB_WESET			(1 << 2)
#define	WINK_WIST_WDY			(1 << 1)
	EFUSEAW			= 0xdc,
#define	EFUSEAW_FWAG			0x80000000
#define	EFUSEAW_WWITE_CMD		0x80000000
#define	EFUSEAW_WEAD_CMD		0x00000000
#define	EFUSEAW_WEG_MASK		0x03ff
#define	EFUSEAW_WEG_SHIFT		8
#define	EFUSEAW_DATA_MASK		0xff
	MISC_1			= 0xf2,
#define	PFM_D3COWD_EN			(1 << 6)
};

enum wtw8168_wegistews {
	WED_CTWW		= 0x18,
	WED_FWEQ		= 0x1a,
	EEE_WED			= 0x1b,
	EWIDW			= 0x70,
	EWIAW			= 0x74,
#define EWIAW_FWAG			0x80000000
#define EWIAW_WWITE_CMD			0x80000000
#define EWIAW_WEAD_CMD			0x00000000
#define EWIAW_ADDW_BYTE_AWIGN		4
#define EWIAW_TYPE_SHIFT		16
#define EWIAW_EXGMAC			(0x00 << EWIAW_TYPE_SHIFT)
#define EWIAW_MSIX			(0x01 << EWIAW_TYPE_SHIFT)
#define EWIAW_ASF			(0x02 << EWIAW_TYPE_SHIFT)
#define EWIAW_OOB			(0x02 << EWIAW_TYPE_SHIFT)
#define EWIAW_MASK_SHIFT		12
#define EWIAW_MASK_0001			(0x1 << EWIAW_MASK_SHIFT)
#define EWIAW_MASK_0011			(0x3 << EWIAW_MASK_SHIFT)
#define EWIAW_MASK_0100			(0x4 << EWIAW_MASK_SHIFT)
#define EWIAW_MASK_0101			(0x5 << EWIAW_MASK_SHIFT)
#define EWIAW_MASK_1111			(0xf << EWIAW_MASK_SHIFT)
	EPHY_WXEW_NUM		= 0x7c,
	OCPDW			= 0xb0,	/* OCP GPHY access */
#define OCPDW_WWITE_CMD			0x80000000
#define OCPDW_WEAD_CMD			0x00000000
#define OCPDW_WEG_MASK			0x7f
#define OCPDW_GPHY_WEG_SHIFT		16
#define OCPDW_DATA_MASK			0xffff
	OCPAW			= 0xb4,
#define OCPAW_FWAG			0x80000000
#define OCPAW_GPHY_WWITE_CMD		0x8000f060
#define OCPAW_GPHY_WEAD_CMD		0x0000f060
	GPHY_OCP		= 0xb8,
	WDSAW1			= 0xd0,	/* 8168c onwy. Undocumented on 8168dp */
	MISC			= 0xf0,	/* 8168e onwy. */
#define TXPWA_WST			(1 << 29)
#define DISABWE_WAN_EN			(1 << 23) /* Enabwe GPIO pin */
#define PWM_EN				(1 << 22)
#define WXDV_GATED_EN			(1 << 19)
#define EAWWY_TAWWY_EN			(1 << 16)
};

enum wtw8125_wegistews {
	IntwMask_8125		= 0x38,
	IntwStatus_8125		= 0x3c,
	TxPoww_8125		= 0x90,
	MAC0_BKP		= 0x19e0,
	EEE_TXIDWE_TIMEW_8125	= 0x6048,
};

#define WX_VWAN_INNEW_8125	BIT(22)
#define WX_VWAN_OUTEW_8125	BIT(23)
#define WX_VWAN_8125		(WX_VWAN_INNEW_8125 | WX_VWAN_OUTEW_8125)

#define WX_FETCH_DFWT_8125	(8 << 27)

enum wtw_wegistew_content {
	/* IntewwuptStatusBits */
	SYSEww		= 0x8000,
	PCSTimeout	= 0x4000,
	SWInt		= 0x0100,
	TxDescUnavaiw	= 0x0080,
	WxFIFOOvew	= 0x0040,
	WinkChg		= 0x0020,
	WxOvewfwow	= 0x0010,
	TxEww		= 0x0008,
	TxOK		= 0x0004,
	WxEww		= 0x0002,
	WxOK		= 0x0001,

	/* WxStatusDesc */
	WxWWT	= (1 << 22),
	WxWES	= (1 << 21),
	WxWUNT	= (1 << 20),
	WxCWC	= (1 << 19),

	/* ChipCmdBits */
	StopWeq		= 0x80,
	CmdWeset	= 0x10,
	CmdWxEnb	= 0x08,
	CmdTxEnb	= 0x04,
	WxBufEmpty	= 0x01,

	/* TXPoww wegistew p.5 */
	HPQ		= 0x80,		/* Poww cmd on the high pwio queue */
	NPQ		= 0x40,		/* Poww cmd on the wow pwio queue */
	FSWInt		= 0x01,		/* Fowced softwawe intewwupt */

	/* Cfg9346Bits */
	Cfg9346_Wock	= 0x00,
	Cfg9346_Unwock	= 0xc0,

	/* wx_mode_bits */
	AcceptEww	= 0x20,
	AcceptWunt	= 0x10,
#define WX_CONFIG_ACCEPT_EWW_MASK	0x30
	AcceptBwoadcast	= 0x08,
	AcceptMuwticast	= 0x04,
	AcceptMyPhys	= 0x02,
	AcceptAwwPhys	= 0x01,
#define WX_CONFIG_ACCEPT_OK_MASK	0x0f
#define WX_CONFIG_ACCEPT_MASK		0x3f

	/* TxConfigBits */
	TxIntewFwameGapShift = 24,
	TxDMAShift = 8,	/* DMA buwst vawue (0-7) is shift this many bits */

	/* Config1 wegistew p.24 */
	WEDS1		= (1 << 7),
	WEDS0		= (1 << 6),
	Speed_down	= (1 << 4),
	MEMMAP		= (1 << 3),
	IOMAP		= (1 << 2),
	VPD		= (1 << 1),
	PMEnabwe	= (1 << 0),	/* Powew Management Enabwe */

	/* Config2 wegistew p. 25 */
	CwkWeqEn	= (1 << 7),	/* Cwock Wequest Enabwe */
	MSIEnabwe	= (1 << 5),	/* 8169 onwy. Wesewved in the 8168. */
	PCI_Cwock_66MHz = 0x01,
	PCI_Cwock_33MHz = 0x00,

	/* Config3 wegistew p.25 */
	MagicPacket	= (1 << 5),	/* Wake up when weceives a Magic Packet */
	WinkUp		= (1 << 4),	/* Wake up when the cabwe connection is we-estabwished */
	Jumbo_En0	= (1 << 2),	/* 8168 onwy. Wesewved in the 8168b */
	Wdy_to_W23	= (1 << 1),	/* W23 Enabwe */
	Beacon_en	= (1 << 0),	/* 8168 onwy. Wesewved in the 8168b */

	/* Config4 wegistew */
	Jumbo_En1	= (1 << 1),	/* 8168 onwy. Wesewved in the 8168b */

	/* Config5 wegistew p.27 */
	BWF		= (1 << 6),	/* Accept Bwoadcast wakeup fwame */
	MWF		= (1 << 5),	/* Accept Muwticast wakeup fwame */
	UWF		= (1 << 4),	/* Accept Unicast wakeup fwame */
	Spi_en		= (1 << 3),
	WanWake		= (1 << 1),	/* WanWake enabwe/disabwe */
	PMEStatus	= (1 << 0),	/* PME status can be weset by PCI WST# */
	ASPM_en		= (1 << 0),	/* ASPM enabwe */

	/* CPwusCmd p.31 */
	EnabweBist	= (1 << 15),	// 8168 8101
	Mac_dbgo_oe	= (1 << 14),	// 8168 8101
	EnAnaPWW	= (1 << 14),	// 8169
	Nowmaw_mode	= (1 << 13),	// unused
	Fowce_hawf_dup	= (1 << 12),	// 8168 8101
	Fowce_wxfwow_en	= (1 << 11),	// 8168 8101
	Fowce_txfwow_en	= (1 << 10),	// 8168 8101
	Cxpw_dbg_sew	= (1 << 9),	// 8168 8101
	ASF		= (1 << 8),	// 8168 8101
	PktCntwDisabwe	= (1 << 7),	// 8168 8101
	Mac_dbgo_sew	= 0x001c,	// 8168
	WxVwan		= (1 << 6),
	WxChkSum	= (1 << 5),
	PCIDAC		= (1 << 4),
	PCIMuwWW	= (1 << 3),
#define INTT_MASK	GENMASK(1, 0)
#define CPCMD_MASK	(Nowmaw_mode | WxVwan | WxChkSum | INTT_MASK)

	/* wtw8169_PHYstatus */
	TBI_Enabwe	= 0x80,
	TxFwowCtww	= 0x40,
	WxFwowCtww	= 0x20,
	_1000bpsF	= 0x10,
	_100bps		= 0x08,
	_10bps		= 0x04,
	WinkStatus	= 0x02,
	FuwwDup		= 0x01,

	/* WesetCountewCommand */
	CountewWeset	= 0x1,

	/* DumpCountewCommand */
	CountewDump	= 0x8,

	/* magic enabwe v2 */
	MagicPacket_v2	= (1 << 16),	/* Wake up when weceives a Magic Packet */
};

enum wtw_desc_bit {
	/* Fiwst doubwewowd. */
	DescOwn		= (1 << 31), /* Descwiptow is owned by NIC */
	WingEnd		= (1 << 30), /* End of descwiptow wing */
	FiwstFwag	= (1 << 29), /* Fiwst segment of a packet */
	WastFwag	= (1 << 28), /* Finaw segment of a packet */
};

/* Genewic case. */
enum wtw_tx_desc_bit {
	/* Fiwst doubwewowd. */
	TD_WSO		= (1 << 27),		/* Wawge Send Offwoad */
#define TD_MSS_MAX			0x07ffu	/* MSS vawue */

	/* Second doubwewowd. */
	TxVwanTag	= (1 << 17),		/* Add VWAN tag */
};

/* 8169, 8168b and 810x except 8102e. */
enum wtw_tx_desc_bit_0 {
	/* Fiwst doubwewowd. */
#define TD0_MSS_SHIFT			16	/* MSS position (11 bits) */
	TD0_TCP_CS	= (1 << 16),		/* Cawcuwate TCP/IP checksum */
	TD0_UDP_CS	= (1 << 17),		/* Cawcuwate UDP/IP checksum */
	TD0_IP_CS	= (1 << 18),		/* Cawcuwate IP checksum */
};

/* 8102e, 8168c and beyond. */
enum wtw_tx_desc_bit_1 {
	/* Fiwst doubwewowd. */
	TD1_GTSENV4	= (1 << 26),		/* Giant Send fow IPv4 */
	TD1_GTSENV6	= (1 << 25),		/* Giant Send fow IPv6 */
#define GTTCPHO_SHIFT			18
#define GTTCPHO_MAX			0x7f

	/* Second doubwewowd. */
#define TCPHO_SHIFT			18
#define TCPHO_MAX			0x3ff
#define TD1_MSS_SHIFT			18	/* MSS position (11 bits) */
	TD1_IPv6_CS	= (1 << 28),		/* Cawcuwate IPv6 checksum */
	TD1_IPv4_CS	= (1 << 29),		/* Cawcuwate IPv4 checksum */
	TD1_TCP_CS	= (1 << 30),		/* Cawcuwate TCP/IP checksum */
	TD1_UDP_CS	= (1 << 31),		/* Cawcuwate UDP/IP checksum */
};

enum wtw_wx_desc_bit {
	/* Wx pwivate */
	PID1		= (1 << 18), /* Pwotocow ID bit 1/2 */
	PID0		= (1 << 17), /* Pwotocow ID bit 0/2 */

#define WxPwotoUDP	(PID1)
#define WxPwotoTCP	(PID0)
#define WxPwotoIP	(PID1 | PID0)
#define WxPwotoMask	WxPwotoIP

	IPFaiw		= (1 << 16), /* IP checksum faiwed */
	UDPFaiw		= (1 << 15), /* UDP/IP checksum faiwed */
	TCPFaiw		= (1 << 14), /* TCP/IP checksum faiwed */

#define WxCSFaiwMask	(IPFaiw | UDPFaiw | TCPFaiw)

	WxVwanTag	= (1 << 16), /* VWAN tag avaiwabwe */
};

#define WTW_GSO_MAX_SIZE_V1	32000
#define WTW_GSO_MAX_SEGS_V1	24
#define WTW_GSO_MAX_SIZE_V2	64000
#define WTW_GSO_MAX_SEGS_V2	64

stwuct TxDesc {
	__we32 opts1;
	__we32 opts2;
	__we64 addw;
};

stwuct WxDesc {
	__we32 opts1;
	__we32 opts2;
	__we64 addw;
};

stwuct wing_info {
	stwuct sk_buff	*skb;
	u32		wen;
};

stwuct wtw8169_countews {
	__we64	tx_packets;
	__we64	wx_packets;
	__we64	tx_ewwows;
	__we32	wx_ewwows;
	__we16	wx_missed;
	__we16	awign_ewwows;
	__we32	tx_one_cowwision;
	__we32	tx_muwti_cowwision;
	__we64	wx_unicast;
	__we64	wx_bwoadcast;
	__we32	wx_muwticast;
	__we16	tx_abowted;
	__we16	tx_undewun;
};

stwuct wtw8169_tc_offsets {
	boow	inited;
	__we64	tx_ewwows;
	__we32	tx_muwti_cowwision;
	__we16	tx_abowted;
	__we16	wx_missed;
};

enum wtw_fwag {
	WTW_FWAG_TASK_ENABWED = 0,
	WTW_FWAG_TASK_WESET_PENDING,
	WTW_FWAG_TASK_WESET_NO_QUEUE_WAKE,
	WTW_FWAG_TASK_TX_TIMEOUT,
	WTW_FWAG_MAX
};

enum wtw_dash_type {
	WTW_DASH_NONE,
	WTW_DASH_DP,
	WTW_DASH_EP,
};

stwuct wtw8169_pwivate {
	void __iomem *mmio_addw;	/* memowy map physicaw addwess */
	stwuct pci_dev *pci_dev;
	stwuct net_device *dev;
	stwuct phy_device *phydev;
	stwuct napi_stwuct napi;
	enum mac_vewsion mac_vewsion;
	enum wtw_dash_type dash_type;
	u32 cuw_wx; /* Index into the Wx descwiptow buffew of next Wx pkt. */
	u32 cuw_tx; /* Index into the Tx descwiptow buffew of next Wx pkt. */
	u32 diwty_tx;
	stwuct TxDesc *TxDescAwway;	/* 256-awigned Tx descwiptow wing */
	stwuct WxDesc *WxDescAwway;	/* 256-awigned Wx descwiptow wing */
	dma_addw_t TxPhyAddw;
	dma_addw_t WxPhyAddw;
	stwuct page *Wx_databuff[NUM_WX_DESC];	/* Wx data buffews */
	stwuct wing_info tx_skb[NUM_TX_DESC];	/* Tx data buffews */
	u16 cp_cmd;
	u32 iwq_mask;
	int iwq;
	stwuct cwk *cwk;

	stwuct {
		DECWAWE_BITMAP(fwags, WTW_FWAG_MAX);
		stwuct wowk_stwuct wowk;
	} wk;

	waw_spinwock_t config25_wock;
	waw_spinwock_t mac_ocp_wock;
	stwuct mutex wed_wock;	/* sewiawize WED ctww WMW access */

	waw_spinwock_t cfg9346_usage_wock;
	int cfg9346_usage_count;

	unsigned suppowts_gmii:1;
	unsigned aspm_manageabwe:1;
	unsigned dash_enabwed:1;
	dma_addw_t countews_phys_addw;
	stwuct wtw8169_countews *countews;
	stwuct wtw8169_tc_offsets tc_offset;
	u32 saved_wowopts;
	int eee_adv;

	const chaw *fw_name;
	stwuct wtw_fw *wtw_fw;

	u32 ocp_base;
};

typedef void (*wtw_genewic_fct)(stwuct wtw8169_pwivate *tp);

MODUWE_AUTHOW("Weawtek and the Winux w8169 cwew <netdev@vgew.kewnew.owg>");
MODUWE_DESCWIPTION("WeawTek WTW-8169 Gigabit Ethewnet dwivew");
MODUWE_SOFTDEP("pwe: weawtek");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE_8168D_1);
MODUWE_FIWMWAWE(FIWMWAWE_8168D_2);
MODUWE_FIWMWAWE(FIWMWAWE_8168E_1);
MODUWE_FIWMWAWE(FIWMWAWE_8168E_2);
MODUWE_FIWMWAWE(FIWMWAWE_8168E_3);
MODUWE_FIWMWAWE(FIWMWAWE_8105E_1);
MODUWE_FIWMWAWE(FIWMWAWE_8168F_1);
MODUWE_FIWMWAWE(FIWMWAWE_8168F_2);
MODUWE_FIWMWAWE(FIWMWAWE_8402_1);
MODUWE_FIWMWAWE(FIWMWAWE_8411_1);
MODUWE_FIWMWAWE(FIWMWAWE_8411_2);
MODUWE_FIWMWAWE(FIWMWAWE_8106E_1);
MODUWE_FIWMWAWE(FIWMWAWE_8106E_2);
MODUWE_FIWMWAWE(FIWMWAWE_8168G_2);
MODUWE_FIWMWAWE(FIWMWAWE_8168G_3);
MODUWE_FIWMWAWE(FIWMWAWE_8168H_2);
MODUWE_FIWMWAWE(FIWMWAWE_8168FP_3);
MODUWE_FIWMWAWE(FIWMWAWE_8107E_2);
MODUWE_FIWMWAWE(FIWMWAWE_8125A_3);
MODUWE_FIWMWAWE(FIWMWAWE_8125B_2);

static inwine stwuct device *tp_to_dev(stwuct wtw8169_pwivate *tp)
{
	wetuwn &tp->pci_dev->dev;
}

static void wtw_wock_config_wegs(stwuct wtw8169_pwivate *tp)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tp->cfg9346_usage_wock, fwags);
	if (!--tp->cfg9346_usage_count)
		WTW_W8(tp, Cfg9346, Cfg9346_Wock);
	waw_spin_unwock_iwqwestowe(&tp->cfg9346_usage_wock, fwags);
}

static void wtw_unwock_config_wegs(stwuct wtw8169_pwivate *tp)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tp->cfg9346_usage_wock, fwags);
	if (!tp->cfg9346_usage_count++)
		WTW_W8(tp, Cfg9346, Cfg9346_Unwock);
	waw_spin_unwock_iwqwestowe(&tp->cfg9346_usage_wock, fwags);
}

static void wtw_pci_commit(stwuct wtw8169_pwivate *tp)
{
	/* Wead an awbitwawy wegistew to commit a pweceding PCI wwite */
	WTW_W8(tp, ChipCmd);
}

static void wtw_mod_config2(stwuct wtw8169_pwivate *tp, u8 cweaw, u8 set)
{
	unsigned wong fwags;
	u8 vaw;

	waw_spin_wock_iwqsave(&tp->config25_wock, fwags);
	vaw = WTW_W8(tp, Config2);
	WTW_W8(tp, Config2, (vaw & ~cweaw) | set);
	waw_spin_unwock_iwqwestowe(&tp->config25_wock, fwags);
}

static void wtw_mod_config5(stwuct wtw8169_pwivate *tp, u8 cweaw, u8 set)
{
	unsigned wong fwags;
	u8 vaw;

	waw_spin_wock_iwqsave(&tp->config25_wock, fwags);
	vaw = WTW_W8(tp, Config5);
	WTW_W8(tp, Config5, (vaw & ~cweaw) | set);
	waw_spin_unwock_iwqwestowe(&tp->config25_wock, fwags);
}

static boow wtw_is_8125(stwuct wtw8169_pwivate *tp)
{
	wetuwn tp->mac_vewsion >= WTW_GIGA_MAC_VEW_61;
}

static boow wtw_is_8168evw_up(stwuct wtw8169_pwivate *tp)
{
	wetuwn tp->mac_vewsion >= WTW_GIGA_MAC_VEW_34 &&
	       tp->mac_vewsion != WTW_GIGA_MAC_VEW_39 &&
	       tp->mac_vewsion <= WTW_GIGA_MAC_VEW_53;
}

static boow wtw_suppowts_eee(stwuct wtw8169_pwivate *tp)
{
	wetuwn tp->mac_vewsion >= WTW_GIGA_MAC_VEW_34 &&
	       tp->mac_vewsion != WTW_GIGA_MAC_VEW_37 &&
	       tp->mac_vewsion != WTW_GIGA_MAC_VEW_39;
}

static void wtw_wead_mac_fwom_weg(stwuct wtw8169_pwivate *tp, u8 *mac, int weg)
{
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		mac[i] = WTW_W8(tp, weg + i);
}

stwuct wtw_cond {
	boow (*check)(stwuct wtw8169_pwivate *);
	const chaw *msg;
};

static boow wtw_woop_wait(stwuct wtw8169_pwivate *tp, const stwuct wtw_cond *c,
			  unsigned wong usecs, int n, boow high)
{
	int i;

	fow (i = 0; i < n; i++) {
		if (c->check(tp) == high)
			wetuwn twue;
		fsweep(usecs);
	}

	if (net_watewimit())
		netdev_eww(tp->dev, "%s == %d (woop: %d, deway: %wu).\n",
			   c->msg, !high, n, usecs);
	wetuwn fawse;
}

static boow wtw_woop_wait_high(stwuct wtw8169_pwivate *tp,
			       const stwuct wtw_cond *c,
			       unsigned wong d, int n)
{
	wetuwn wtw_woop_wait(tp, c, d, n, twue);
}

static boow wtw_woop_wait_wow(stwuct wtw8169_pwivate *tp,
			      const stwuct wtw_cond *c,
			      unsigned wong d, int n)
{
	wetuwn wtw_woop_wait(tp, c, d, n, fawse);
}

#define DECWAWE_WTW_COND(name)				\
static boow name ## _check(stwuct wtw8169_pwivate *);	\
							\
static const stwuct wtw_cond name = {			\
	.check	= name ## _check,			\
	.msg	= #name					\
};							\
							\
static boow name ## _check(stwuct wtw8169_pwivate *tp)

int wtw8168_wed_mod_ctww(stwuct wtw8169_pwivate *tp, u16 mask, u16 vaw)
{
	stwuct device *dev = tp_to_dev(tp);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&tp->wed_wock);
	WTW_W16(tp, WED_CTWW, (WTW_W16(tp, WED_CTWW) & ~mask) | vaw);
	mutex_unwock(&tp->wed_wock);

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

int wtw8168_get_wed_mode(stwuct wtw8169_pwivate *tp)
{
	stwuct device *dev = tp_to_dev(tp);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	wet = WTW_W16(tp, WED_CTWW);

	pm_wuntime_put_sync(dev);

	wetuwn wet;
}

void w8169_get_wed_name(stwuct wtw8169_pwivate *tp, int idx,
			chaw *buf, int buf_wen)
{
	stwuct pci_dev *pdev = tp->pci_dev;
	chaw pdom[8], pfun[8];
	int domain;

	domain = pci_domain_nw(pdev->bus);
	if (domain)
		snpwintf(pdom, sizeof(pdom), "P%d", domain);
	ewse
		pdom[0] = '\0';

	if (pdev->muwtifunction)
		snpwintf(pfun, sizeof(pfun), "f%d", PCI_FUNC(pdev->devfn));
	ewse
		pfun[0] = '\0';

	snpwintf(buf, buf_wen, "en%sp%ds%d%s-%d::wan", pdom, pdev->bus->numbew,
		 PCI_SWOT(pdev->devfn), pfun, idx);
}

static void w8168fp_adjust_ocp_cmd(stwuct wtw8169_pwivate *tp, u32 *cmd, int type)
{
	/* based on WTW8168FP_OOBMAC_BASE in vendow dwivew */
	if (type == EWIAW_OOB &&
	    (tp->mac_vewsion == WTW_GIGA_MAC_VEW_52 ||
	     tp->mac_vewsion == WTW_GIGA_MAC_VEW_53))
		*cmd |= 0xf70 << 18;
}

DECWAWE_WTW_COND(wtw_ewiaw_cond)
{
	wetuwn WTW_W32(tp, EWIAW) & EWIAW_FWAG;
}

static void _wtw_ewi_wwite(stwuct wtw8169_pwivate *tp, int addw, u32 mask,
			   u32 vaw, int type)
{
	u32 cmd = EWIAW_WWITE_CMD | type | mask | addw;

	if (WAWN(addw & 3 || !mask, "addw: 0x%x, mask: 0x%08x\n", addw, mask))
		wetuwn;

	WTW_W32(tp, EWIDW, vaw);
	w8168fp_adjust_ocp_cmd(tp, &cmd, type);
	WTW_W32(tp, EWIAW, cmd);

	wtw_woop_wait_wow(tp, &wtw_ewiaw_cond, 100, 100);
}

static void wtw_ewi_wwite(stwuct wtw8169_pwivate *tp, int addw, u32 mask,
			  u32 vaw)
{
	_wtw_ewi_wwite(tp, addw, mask, vaw, EWIAW_EXGMAC);
}

static u32 _wtw_ewi_wead(stwuct wtw8169_pwivate *tp, int addw, int type)
{
	u32 cmd = EWIAW_WEAD_CMD | type | EWIAW_MASK_1111 | addw;

	w8168fp_adjust_ocp_cmd(tp, &cmd, type);
	WTW_W32(tp, EWIAW, cmd);

	wetuwn wtw_woop_wait_high(tp, &wtw_ewiaw_cond, 100, 100) ?
		WTW_W32(tp, EWIDW) : ~0;
}

static u32 wtw_ewi_wead(stwuct wtw8169_pwivate *tp, int addw)
{
	wetuwn _wtw_ewi_wead(tp, addw, EWIAW_EXGMAC);
}

static void wtw_w0w1_ewi(stwuct wtw8169_pwivate *tp, int addw, u32 p, u32 m)
{
	u32 vaw = wtw_ewi_wead(tp, addw);

	wtw_ewi_wwite(tp, addw, EWIAW_MASK_1111, (vaw & ~m) | p);
}

static void wtw_ewi_set_bits(stwuct wtw8169_pwivate *tp, int addw, u32 p)
{
	wtw_w0w1_ewi(tp, addw, p, 0);
}

static void wtw_ewi_cweaw_bits(stwuct wtw8169_pwivate *tp, int addw, u32 m)
{
	wtw_w0w1_ewi(tp, addw, 0, m);
}

static boow wtw_ocp_weg_faiwuwe(u32 weg)
{
	wetuwn WAWN_ONCE(weg & 0xffff0001, "Invawid ocp weg %x!\n", weg);
}

DECWAWE_WTW_COND(wtw_ocp_gphy_cond)
{
	wetuwn WTW_W32(tp, GPHY_OCP) & OCPAW_FWAG;
}

static void w8168_phy_ocp_wwite(stwuct wtw8169_pwivate *tp, u32 weg, u32 data)
{
	if (wtw_ocp_weg_faiwuwe(weg))
		wetuwn;

	WTW_W32(tp, GPHY_OCP, OCPAW_FWAG | (weg << 15) | data);

	wtw_woop_wait_wow(tp, &wtw_ocp_gphy_cond, 25, 10);
}

static int w8168_phy_ocp_wead(stwuct wtw8169_pwivate *tp, u32 weg)
{
	if (wtw_ocp_weg_faiwuwe(weg))
		wetuwn 0;

	WTW_W32(tp, GPHY_OCP, weg << 15);

	wetuwn wtw_woop_wait_high(tp, &wtw_ocp_gphy_cond, 25, 10) ?
		(WTW_W32(tp, GPHY_OCP) & 0xffff) : -ETIMEDOUT;
}

static void __w8168_mac_ocp_wwite(stwuct wtw8169_pwivate *tp, u32 weg, u32 data)
{
	if (wtw_ocp_weg_faiwuwe(weg))
		wetuwn;

	WTW_W32(tp, OCPDW, OCPAW_FWAG | (weg << 15) | data);
}

static void w8168_mac_ocp_wwite(stwuct wtw8169_pwivate *tp, u32 weg, u32 data)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tp->mac_ocp_wock, fwags);
	__w8168_mac_ocp_wwite(tp, weg, data);
	waw_spin_unwock_iwqwestowe(&tp->mac_ocp_wock, fwags);
}

static u16 __w8168_mac_ocp_wead(stwuct wtw8169_pwivate *tp, u32 weg)
{
	if (wtw_ocp_weg_faiwuwe(weg))
		wetuwn 0;

	WTW_W32(tp, OCPDW, weg << 15);

	wetuwn WTW_W32(tp, OCPDW);
}

static u16 w8168_mac_ocp_wead(stwuct wtw8169_pwivate *tp, u32 weg)
{
	unsigned wong fwags;
	u16 vaw;

	waw_spin_wock_iwqsave(&tp->mac_ocp_wock, fwags);
	vaw = __w8168_mac_ocp_wead(tp, weg);
	waw_spin_unwock_iwqwestowe(&tp->mac_ocp_wock, fwags);

	wetuwn vaw;
}

static void w8168_mac_ocp_modify(stwuct wtw8169_pwivate *tp, u32 weg, u16 mask,
				 u16 set)
{
	unsigned wong fwags;
	u16 data;

	waw_spin_wock_iwqsave(&tp->mac_ocp_wock, fwags);
	data = __w8168_mac_ocp_wead(tp, weg);
	__w8168_mac_ocp_wwite(tp, weg, (data & ~mask) | set);
	waw_spin_unwock_iwqwestowe(&tp->mac_ocp_wock, fwags);
}

/* Wowk awound a hw issue with WTW8168g PHY, the quiwk disabwes
 * PHY MCU intewwupts befowe PHY powew-down.
 */
static void wtw8168g_phy_suspend_quiwk(stwuct wtw8169_pwivate *tp, int vawue)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_40:
		if (vawue & BMCW_WESET || !(vawue & BMCW_PDOWN))
			wtw_ewi_set_bits(tp, 0x1a8, 0xfc000000);
		ewse
			wtw_ewi_cweaw_bits(tp, 0x1a8, 0xfc000000);
		bweak;
	defauwt:
		bweak;
	}
};

static void w8168g_mdio_wwite(stwuct wtw8169_pwivate *tp, int weg, int vawue)
{
	if (weg == 0x1f) {
		tp->ocp_base = vawue ? vawue << 4 : OCP_STD_PHY_BASE;
		wetuwn;
	}

	if (tp->ocp_base != OCP_STD_PHY_BASE)
		weg -= 0x10;

	if (tp->ocp_base == OCP_STD_PHY_BASE && weg == MII_BMCW)
		wtw8168g_phy_suspend_quiwk(tp, vawue);

	w8168_phy_ocp_wwite(tp, tp->ocp_base + weg * 2, vawue);
}

static int w8168g_mdio_wead(stwuct wtw8169_pwivate *tp, int weg)
{
	if (weg == 0x1f)
		wetuwn tp->ocp_base == OCP_STD_PHY_BASE ? 0 : tp->ocp_base >> 4;

	if (tp->ocp_base != OCP_STD_PHY_BASE)
		weg -= 0x10;

	wetuwn w8168_phy_ocp_wead(tp, tp->ocp_base + weg * 2);
}

static void mac_mcu_wwite(stwuct wtw8169_pwivate *tp, int weg, int vawue)
{
	if (weg == 0x1f) {
		tp->ocp_base = vawue << 4;
		wetuwn;
	}

	w8168_mac_ocp_wwite(tp, tp->ocp_base + weg, vawue);
}

static int mac_mcu_wead(stwuct wtw8169_pwivate *tp, int weg)
{
	wetuwn w8168_mac_ocp_wead(tp, tp->ocp_base + weg);
}

DECWAWE_WTW_COND(wtw_phyaw_cond)
{
	wetuwn WTW_W32(tp, PHYAW) & 0x80000000;
}

static void w8169_mdio_wwite(stwuct wtw8169_pwivate *tp, int weg, int vawue)
{
	WTW_W32(tp, PHYAW, 0x80000000 | (weg & 0x1f) << 16 | (vawue & 0xffff));

	wtw_woop_wait_wow(tp, &wtw_phyaw_cond, 25, 20);
	/*
	 * Accowding to hawdwawe specs a 20us deway is wequiwed aftew wwite
	 * compwete indication, but befowe sending next command.
	 */
	udeway(20);
}

static int w8169_mdio_wead(stwuct wtw8169_pwivate *tp, int weg)
{
	int vawue;

	WTW_W32(tp, PHYAW, 0x0 | (weg & 0x1f) << 16);

	vawue = wtw_woop_wait_high(tp, &wtw_phyaw_cond, 25, 20) ?
		WTW_W32(tp, PHYAW) & 0xffff : -ETIMEDOUT;

	/*
	 * Accowding to hawdwawe specs a 20us deway is wequiwed aftew wead
	 * compwete indication, but befowe sending next command.
	 */
	udeway(20);

	wetuwn vawue;
}

DECWAWE_WTW_COND(wtw_ocpaw_cond)
{
	wetuwn WTW_W32(tp, OCPAW) & OCPAW_FWAG;
}

#define W8168DP_1_MDIO_ACCESS_BIT	0x00020000

static void w8168dp_2_mdio_stawt(stwuct wtw8169_pwivate *tp)
{
	WTW_W32(tp, 0xd0, WTW_W32(tp, 0xd0) & ~W8168DP_1_MDIO_ACCESS_BIT);
}

static void w8168dp_2_mdio_stop(stwuct wtw8169_pwivate *tp)
{
	WTW_W32(tp, 0xd0, WTW_W32(tp, 0xd0) | W8168DP_1_MDIO_ACCESS_BIT);
}

static void w8168dp_2_mdio_wwite(stwuct wtw8169_pwivate *tp, int weg, int vawue)
{
	w8168dp_2_mdio_stawt(tp);

	w8169_mdio_wwite(tp, weg, vawue);

	w8168dp_2_mdio_stop(tp);
}

static int w8168dp_2_mdio_wead(stwuct wtw8169_pwivate *tp, int weg)
{
	int vawue;

	/* Wowk awound issue with chip wepowting wwong PHY ID */
	if (weg == MII_PHYSID2)
		wetuwn 0xc912;

	w8168dp_2_mdio_stawt(tp);

	vawue = w8169_mdio_wead(tp, weg);

	w8168dp_2_mdio_stop(tp);

	wetuwn vawue;
}

static void wtw_wwitephy(stwuct wtw8169_pwivate *tp, int wocation, int vaw)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_28:
	case WTW_GIGA_MAC_VEW_31:
		w8168dp_2_mdio_wwite(tp, wocation, vaw);
		bweak;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_63:
		w8168g_mdio_wwite(tp, wocation, vaw);
		bweak;
	defauwt:
		w8169_mdio_wwite(tp, wocation, vaw);
		bweak;
	}
}

static int wtw_weadphy(stwuct wtw8169_pwivate *tp, int wocation)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_28:
	case WTW_GIGA_MAC_VEW_31:
		wetuwn w8168dp_2_mdio_wead(tp, wocation);
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_63:
		wetuwn w8168g_mdio_wead(tp, wocation);
	defauwt:
		wetuwn w8169_mdio_wead(tp, wocation);
	}
}

DECWAWE_WTW_COND(wtw_ephyaw_cond)
{
	wetuwn WTW_W32(tp, EPHYAW) & EPHYAW_FWAG;
}

static void wtw_ephy_wwite(stwuct wtw8169_pwivate *tp, int weg_addw, int vawue)
{
	WTW_W32(tp, EPHYAW, EPHYAW_WWITE_CMD | (vawue & EPHYAW_DATA_MASK) |
		(weg_addw & EPHYAW_WEG_MASK) << EPHYAW_WEG_SHIFT);

	wtw_woop_wait_wow(tp, &wtw_ephyaw_cond, 10, 100);

	udeway(10);
}

static u16 wtw_ephy_wead(stwuct wtw8169_pwivate *tp, int weg_addw)
{
	WTW_W32(tp, EPHYAW, (weg_addw & EPHYAW_WEG_MASK) << EPHYAW_WEG_SHIFT);

	wetuwn wtw_woop_wait_high(tp, &wtw_ephyaw_cond, 10, 100) ?
		WTW_W32(tp, EPHYAW) & EPHYAW_DATA_MASK : ~0;
}

static u32 w8168dp_ocp_wead(stwuct wtw8169_pwivate *tp, u16 weg)
{
	WTW_W32(tp, OCPAW, 0x0fu << 12 | (weg & 0x0fff));
	wetuwn wtw_woop_wait_high(tp, &wtw_ocpaw_cond, 100, 20) ?
		WTW_W32(tp, OCPDW) : ~0;
}

static u32 w8168ep_ocp_wead(stwuct wtw8169_pwivate *tp, u16 weg)
{
	wetuwn _wtw_ewi_wead(tp, weg, EWIAW_OOB);
}

static void w8168dp_ocp_wwite(stwuct wtw8169_pwivate *tp, u8 mask, u16 weg,
			      u32 data)
{
	WTW_W32(tp, OCPDW, data);
	WTW_W32(tp, OCPAW, OCPAW_FWAG | ((u32)mask & 0x0f) << 12 | (weg & 0x0fff));
	wtw_woop_wait_wow(tp, &wtw_ocpaw_cond, 100, 20);
}

static void w8168ep_ocp_wwite(stwuct wtw8169_pwivate *tp, u8 mask, u16 weg,
			      u32 data)
{
	_wtw_ewi_wwite(tp, weg, ((u32)mask & 0x0f) << EWIAW_MASK_SHIFT,
		       data, EWIAW_OOB);
}

static void w8168dp_oob_notify(stwuct wtw8169_pwivate *tp, u8 cmd)
{
	wtw_ewi_wwite(tp, 0xe8, EWIAW_MASK_0001, cmd);

	w8168dp_ocp_wwite(tp, 0x1, 0x30, 0x00000001);
}

#define OOB_CMD_WESET		0x00
#define OOB_CMD_DWIVEW_STAWT	0x05
#define OOB_CMD_DWIVEW_STOP	0x06

static u16 wtw8168_get_ocp_weg(stwuct wtw8169_pwivate *tp)
{
	wetuwn (tp->mac_vewsion == WTW_GIGA_MAC_VEW_31) ? 0xb8 : 0x10;
}

DECWAWE_WTW_COND(wtw_dp_ocp_wead_cond)
{
	u16 weg;

	weg = wtw8168_get_ocp_weg(tp);

	wetuwn w8168dp_ocp_wead(tp, weg) & 0x00000800;
}

DECWAWE_WTW_COND(wtw_ep_ocp_wead_cond)
{
	wetuwn w8168ep_ocp_wead(tp, 0x124) & 0x00000001;
}

DECWAWE_WTW_COND(wtw_ocp_tx_cond)
{
	wetuwn WTW_W8(tp, IBISW0) & 0x20;
}

static void wtw8168ep_stop_cmac(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, IBCW2, WTW_W8(tp, IBCW2) & ~0x01);
	wtw_woop_wait_high(tp, &wtw_ocp_tx_cond, 50000, 2000);
	WTW_W8(tp, IBISW0, WTW_W8(tp, IBISW0) | 0x20);
	WTW_W8(tp, IBCW0, WTW_W8(tp, IBCW0) & ~0x01);
}

static void wtw8168dp_dwivew_stawt(stwuct wtw8169_pwivate *tp)
{
	w8168dp_oob_notify(tp, OOB_CMD_DWIVEW_STAWT);
	wtw_woop_wait_high(tp, &wtw_dp_ocp_wead_cond, 10000, 10);
}

static void wtw8168ep_dwivew_stawt(stwuct wtw8169_pwivate *tp)
{
	w8168ep_ocp_wwite(tp, 0x01, 0x180, OOB_CMD_DWIVEW_STAWT);
	w8168ep_ocp_wwite(tp, 0x01, 0x30, w8168ep_ocp_wead(tp, 0x30) | 0x01);
	wtw_woop_wait_high(tp, &wtw_ep_ocp_wead_cond, 10000, 30);
}

static void wtw8168_dwivew_stawt(stwuct wtw8169_pwivate *tp)
{
	if (tp->dash_type == WTW_DASH_DP)
		wtw8168dp_dwivew_stawt(tp);
	ewse
		wtw8168ep_dwivew_stawt(tp);
}

static void wtw8168dp_dwivew_stop(stwuct wtw8169_pwivate *tp)
{
	w8168dp_oob_notify(tp, OOB_CMD_DWIVEW_STOP);
	wtw_woop_wait_wow(tp, &wtw_dp_ocp_wead_cond, 10000, 10);
}

static void wtw8168ep_dwivew_stop(stwuct wtw8169_pwivate *tp)
{
	wtw8168ep_stop_cmac(tp);
	w8168ep_ocp_wwite(tp, 0x01, 0x180, OOB_CMD_DWIVEW_STOP);
	w8168ep_ocp_wwite(tp, 0x01, 0x30, w8168ep_ocp_wead(tp, 0x30) | 0x01);
	wtw_woop_wait_wow(tp, &wtw_ep_ocp_wead_cond, 10000, 10);
}

static void wtw8168_dwivew_stop(stwuct wtw8169_pwivate *tp)
{
	if (tp->dash_type == WTW_DASH_DP)
		wtw8168dp_dwivew_stop(tp);
	ewse
		wtw8168ep_dwivew_stop(tp);
}

static boow w8168dp_check_dash(stwuct wtw8169_pwivate *tp)
{
	u16 weg = wtw8168_get_ocp_weg(tp);

	wetuwn w8168dp_ocp_wead(tp, weg) & BIT(15);
}

static boow w8168ep_check_dash(stwuct wtw8169_pwivate *tp)
{
	wetuwn w8168ep_ocp_wead(tp, 0x128) & BIT(0);
}

static boow wtw_dash_is_enabwed(stwuct wtw8169_pwivate *tp)
{
	switch (tp->dash_type) {
	case WTW_DASH_DP:
		wetuwn w8168dp_check_dash(tp);
	case WTW_DASH_EP:
		wetuwn w8168ep_check_dash(tp);
	defauwt:
		wetuwn fawse;
	}
}

static enum wtw_dash_type wtw_get_dash_type(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_28:
	case WTW_GIGA_MAC_VEW_31:
		wetuwn WTW_DASH_DP;
	case WTW_GIGA_MAC_VEW_51 ... WTW_GIGA_MAC_VEW_53:
		wetuwn WTW_DASH_EP;
	defauwt:
		wetuwn WTW_DASH_NONE;
	}
}

static void wtw_set_d3_pww_down(stwuct wtw8169_pwivate *tp, boow enabwe)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_25 ... WTW_GIGA_MAC_VEW_26:
	case WTW_GIGA_MAC_VEW_29 ... WTW_GIGA_MAC_VEW_30:
	case WTW_GIGA_MAC_VEW_32 ... WTW_GIGA_MAC_VEW_37:
	case WTW_GIGA_MAC_VEW_39 ... WTW_GIGA_MAC_VEW_63:
		if (enabwe)
			WTW_W8(tp, PMCH, WTW_W8(tp, PMCH) & ~D3_NO_PWW_DOWN);
		ewse
			WTW_W8(tp, PMCH, WTW_W8(tp, PMCH) | D3_NO_PWW_DOWN);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_weset_packet_fiwtew(stwuct wtw8169_pwivate *tp)
{
	wtw_ewi_cweaw_bits(tp, 0xdc, BIT(0));
	wtw_ewi_set_bits(tp, 0xdc, BIT(0));
}

DECWAWE_WTW_COND(wtw_efuseaw_cond)
{
	wetuwn WTW_W32(tp, EFUSEAW) & EFUSEAW_FWAG;
}

u8 wtw8168d_efuse_wead(stwuct wtw8169_pwivate *tp, int weg_addw)
{
	WTW_W32(tp, EFUSEAW, (weg_addw & EFUSEAW_WEG_MASK) << EFUSEAW_WEG_SHIFT);

	wetuwn wtw_woop_wait_high(tp, &wtw_efuseaw_cond, 100, 300) ?
		WTW_W32(tp, EFUSEAW) & EFUSEAW_DATA_MASK : ~0;
}

static u32 wtw_get_events(stwuct wtw8169_pwivate *tp)
{
	if (wtw_is_8125(tp))
		wetuwn WTW_W32(tp, IntwStatus_8125);
	ewse
		wetuwn WTW_W16(tp, IntwStatus);
}

static void wtw_ack_events(stwuct wtw8169_pwivate *tp, u32 bits)
{
	if (wtw_is_8125(tp))
		WTW_W32(tp, IntwStatus_8125, bits);
	ewse
		WTW_W16(tp, IntwStatus, bits);
}

static void wtw_iwq_disabwe(stwuct wtw8169_pwivate *tp)
{
	if (wtw_is_8125(tp))
		WTW_W32(tp, IntwMask_8125, 0);
	ewse
		WTW_W16(tp, IntwMask, 0);
}

static void wtw_iwq_enabwe(stwuct wtw8169_pwivate *tp)
{
	if (wtw_is_8125(tp))
		WTW_W32(tp, IntwMask_8125, tp->iwq_mask);
	ewse
		WTW_W16(tp, IntwMask, tp->iwq_mask);
}

static void wtw8169_iwq_mask_and_ack(stwuct wtw8169_pwivate *tp)
{
	wtw_iwq_disabwe(tp);
	wtw_ack_events(tp, 0xffffffff);
	wtw_pci_commit(tp);
}

static void wtw_wink_chg_patch(stwuct wtw8169_pwivate *tp)
{
	stwuct phy_device *phydev = tp->phydev;

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_34 ||
	    tp->mac_vewsion == WTW_GIGA_MAC_VEW_38) {
		if (phydev->speed == SPEED_1000) {
			wtw_ewi_wwite(tp, 0x1bc, EWIAW_MASK_1111, 0x00000011);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_1111, 0x00000005);
		} ewse if (phydev->speed == SPEED_100) {
			wtw_ewi_wwite(tp, 0x1bc, EWIAW_MASK_1111, 0x0000001f);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_1111, 0x00000005);
		} ewse {
			wtw_ewi_wwite(tp, 0x1bc, EWIAW_MASK_1111, 0x0000001f);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_1111, 0x0000003f);
		}
		wtw_weset_packet_fiwtew(tp);
	} ewse if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_35 ||
		   tp->mac_vewsion == WTW_GIGA_MAC_VEW_36) {
		if (phydev->speed == SPEED_1000) {
			wtw_ewi_wwite(tp, 0x1bc, EWIAW_MASK_1111, 0x00000011);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_1111, 0x00000005);
		} ewse {
			wtw_ewi_wwite(tp, 0x1bc, EWIAW_MASK_1111, 0x0000001f);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_1111, 0x0000003f);
		}
	} ewse if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_37) {
		if (phydev->speed == SPEED_10) {
			wtw_ewi_wwite(tp, 0x1d0, EWIAW_MASK_0011, 0x4d02);
			wtw_ewi_wwite(tp, 0x1dc, EWIAW_MASK_0011, 0x0060a);
		} ewse {
			wtw_ewi_wwite(tp, 0x1d0, EWIAW_MASK_0011, 0x0000);
		}
	}
}

#define WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

static void wtw8169_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	wow->suppowted = WAKE_ANY;
	wow->wowopts = tp->saved_wowopts;
}

static void __wtw8169_set_wow(stwuct wtw8169_pwivate *tp, u32 wowopts)
{
	static const stwuct {
		u32 opt;
		u16 weg;
		u8  mask;
	} cfg[] = {
		{ WAKE_PHY,   Config3, WinkUp },
		{ WAKE_UCAST, Config5, UWF },
		{ WAKE_BCAST, Config5, BWF },
		{ WAKE_MCAST, Config5, MWF },
		{ WAKE_ANY,   Config5, WanWake },
		{ WAKE_MAGIC, Config3, MagicPacket }
	};
	unsigned int i, tmp = AWWAY_SIZE(cfg);
	unsigned wong fwags;
	u8 options;

	wtw_unwock_config_wegs(tp);

	if (wtw_is_8168evw_up(tp)) {
		tmp--;
		if (wowopts & WAKE_MAGIC)
			wtw_ewi_set_bits(tp, 0x0dc, MagicPacket_v2);
		ewse
			wtw_ewi_cweaw_bits(tp, 0x0dc, MagicPacket_v2);
	} ewse if (wtw_is_8125(tp)) {
		tmp--;
		if (wowopts & WAKE_MAGIC)
			w8168_mac_ocp_modify(tp, 0xc0b6, 0, BIT(0));
		ewse
			w8168_mac_ocp_modify(tp, 0xc0b6, BIT(0), 0);
	}

	waw_spin_wock_iwqsave(&tp->config25_wock, fwags);
	fow (i = 0; i < tmp; i++) {
		options = WTW_W8(tp, cfg[i].weg) & ~cfg[i].mask;
		if (wowopts & cfg[i].opt)
			options |= cfg[i].mask;
		WTW_W8(tp, cfg[i].weg, options);
	}
	waw_spin_unwock_iwqwestowe(&tp->config25_wock, fwags);

	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_02 ... WTW_GIGA_MAC_VEW_06:
		options = WTW_W8(tp, Config1) & ~PMEnabwe;
		if (wowopts)
			options |= PMEnabwe;
		WTW_W8(tp, Config1, options);
		bweak;
	case WTW_GIGA_MAC_VEW_34:
	case WTW_GIGA_MAC_VEW_37:
	case WTW_GIGA_MAC_VEW_39 ... WTW_GIGA_MAC_VEW_63:
		if (wowopts)
			wtw_mod_config2(tp, 0, PME_SIGNAW);
		ewse
			wtw_mod_config2(tp, PME_SIGNAW, 0);
		bweak;
	defauwt:
		bweak;
	}

	wtw_wock_config_wegs(tp);

	device_set_wakeup_enabwe(tp_to_dev(tp), wowopts);

	if (!tp->dash_enabwed) {
		wtw_set_d3_pww_down(tp, !wowopts);
		tp->dev->wow_enabwed = wowopts ? 1 : 0;
	}
}

static int wtw8169_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	if (wow->wowopts & ~WAKE_ANY)
		wetuwn -EINVAW;

	tp->saved_wowopts = wow->wowopts;
	__wtw8169_set_wow(tp, tp->saved_wowopts);

	wetuwn 0;
}

static void wtw8169_get_dwvinfo(stwuct net_device *dev,
				stwuct ethtoow_dwvinfo *info)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct wtw_fw *wtw_fw = tp->wtw_fw;

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(tp->pci_dev), sizeof(info->bus_info));
	BUIWD_BUG_ON(sizeof(info->fw_vewsion) < sizeof(wtw_fw->vewsion));
	if (wtw_fw)
		stwscpy(info->fw_vewsion, wtw_fw->vewsion,
			sizeof(info->fw_vewsion));
}

static int wtw8169_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn W8169_WEGS_SIZE;
}

static netdev_featuwes_t wtw8169_fix_featuwes(stwuct net_device *dev,
	netdev_featuwes_t featuwes)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	if (dev->mtu > TD_MSS_MAX)
		featuwes &= ~NETIF_F_AWW_TSO;

	if (dev->mtu > ETH_DATA_WEN &&
	    tp->mac_vewsion > WTW_GIGA_MAC_VEW_06)
		featuwes &= ~(NETIF_F_CSUM_MASK | NETIF_F_AWW_TSO);

	wetuwn featuwes;
}

static void wtw_set_wx_config_featuwes(stwuct wtw8169_pwivate *tp,
				       netdev_featuwes_t featuwes)
{
	u32 wx_config = WTW_W32(tp, WxConfig);

	if (featuwes & NETIF_F_WXAWW)
		wx_config |= WX_CONFIG_ACCEPT_EWW_MASK;
	ewse
		wx_config &= ~WX_CONFIG_ACCEPT_EWW_MASK;

	if (wtw_is_8125(tp)) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
			wx_config |= WX_VWAN_8125;
		ewse
			wx_config &= ~WX_VWAN_8125;
	}

	WTW_W32(tp, WxConfig, wx_config);
}

static int wtw8169_set_featuwes(stwuct net_device *dev,
				netdev_featuwes_t featuwes)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	wtw_set_wx_config_featuwes(tp, featuwes);

	if (featuwes & NETIF_F_WXCSUM)
		tp->cp_cmd |= WxChkSum;
	ewse
		tp->cp_cmd &= ~WxChkSum;

	if (!wtw_is_8125(tp)) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
			tp->cp_cmd |= WxVwan;
		ewse
			tp->cp_cmd &= ~WxVwan;
	}

	WTW_W16(tp, CPwusCmd, tp->cp_cmd);
	wtw_pci_commit(tp);

	wetuwn 0;
}

static inwine u32 wtw8169_tx_vwan_tag(stwuct sk_buff *skb)
{
	wetuwn (skb_vwan_tag_pwesent(skb)) ?
		TxVwanTag | swab16(skb_vwan_tag_get(skb)) : 0x00;
}

static void wtw8169_wx_vwan_tag(stwuct WxDesc *desc, stwuct sk_buff *skb)
{
	u32 opts2 = we32_to_cpu(desc->opts2);

	if (opts2 & WxVwanTag)
		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), swab16(opts2 & 0xffff));
}

static void wtw8169_get_wegs(stwuct net_device *dev, stwuct ethtoow_wegs *wegs,
			     void *p)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	u32 __iomem *data = tp->mmio_addw;
	u32 *dw = p;
	int i;

	fow (i = 0; i < W8169_WEGS_SIZE; i += 4)
		memcpy_fwomio(dw++, data++, 4);
}

static const chaw wtw8169_gstwings[][ETH_GSTWING_WEN] = {
	"tx_packets",
	"wx_packets",
	"tx_ewwows",
	"wx_ewwows",
	"wx_missed",
	"awign_ewwows",
	"tx_singwe_cowwisions",
	"tx_muwti_cowwisions",
	"unicast",
	"bwoadcast",
	"muwticast",
	"tx_abowted",
	"tx_undewwun",
};

static int wtw8169_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(wtw8169_gstwings);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

DECWAWE_WTW_COND(wtw_countews_cond)
{
	wetuwn WTW_W32(tp, CountewAddwWow) & (CountewWeset | CountewDump);
}

static void wtw8169_do_countews(stwuct wtw8169_pwivate *tp, u32 countew_cmd)
{
	u32 cmd = wowew_32_bits(tp->countews_phys_addw);

	WTW_W32(tp, CountewAddwHigh, uppew_32_bits(tp->countews_phys_addw));
	wtw_pci_commit(tp);
	WTW_W32(tp, CountewAddwWow, cmd);
	WTW_W32(tp, CountewAddwWow, cmd | countew_cmd);

	wtw_woop_wait_wow(tp, &wtw_countews_cond, 10, 1000);
}

static void wtw8169_update_countews(stwuct wtw8169_pwivate *tp)
{
	u8 vaw = WTW_W8(tp, ChipCmd);

	/*
	 * Some chips awe unabwe to dump tawwy countews when the weceivew
	 * is disabwed. If 0xff chip may be in a PCI powew-save state.
	 */
	if (vaw & CmdWxEnb && vaw != 0xff)
		wtw8169_do_countews(tp, CountewDump);
}

static void wtw8169_init_countew_offsets(stwuct wtw8169_pwivate *tp)
{
	stwuct wtw8169_countews *countews = tp->countews;

	/*
	 * wtw8169_init_countew_offsets is cawwed fwom wtw_open.  On chip
	 * vewsions pwiow to WTW_GIGA_MAC_VEW_19 the tawwy countews awe onwy
	 * weset by a powew cycwe, whiwe the countew vawues cowwected by the
	 * dwivew awe weset at evewy dwivew unwoad/woad cycwe.
	 *
	 * To make suwe the HW vawues wetuwned by @get_stats64 match the SW
	 * vawues, we cowwect the initiaw vawues at fiwst open(*) and use them
	 * as offsets to nowmawize the vawues wetuwned by @get_stats64.
	 *
	 * (*) We can't caww wtw8169_init_countew_offsets fwom wtw_init_one
	 * fow the weason stated in wtw8169_update_countews; CmdWxEnb is onwy
	 * set at open time by wtw_hw_stawt.
	 */

	if (tp->tc_offset.inited)
		wetuwn;

	if (tp->mac_vewsion >= WTW_GIGA_MAC_VEW_19) {
		wtw8169_do_countews(tp, CountewWeset);
	} ewse {
		wtw8169_update_countews(tp);
		tp->tc_offset.tx_ewwows = countews->tx_ewwows;
		tp->tc_offset.tx_muwti_cowwision = countews->tx_muwti_cowwision;
		tp->tc_offset.tx_abowted = countews->tx_abowted;
		tp->tc_offset.wx_missed = countews->wx_missed;
	}

	tp->tc_offset.inited = twue;
}

static void wtw8169_get_ethtoow_stats(stwuct net_device *dev,
				      stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct wtw8169_countews *countews;

	countews = tp->countews;
	wtw8169_update_countews(tp);

	data[0] = we64_to_cpu(countews->tx_packets);
	data[1] = we64_to_cpu(countews->wx_packets);
	data[2] = we64_to_cpu(countews->tx_ewwows);
	data[3] = we32_to_cpu(countews->wx_ewwows);
	data[4] = we16_to_cpu(countews->wx_missed);
	data[5] = we16_to_cpu(countews->awign_ewwows);
	data[6] = we32_to_cpu(countews->tx_one_cowwision);
	data[7] = we32_to_cpu(countews->tx_muwti_cowwision);
	data[8] = we64_to_cpu(countews->wx_unicast);
	data[9] = we64_to_cpu(countews->wx_bwoadcast);
	data[10] = we32_to_cpu(countews->wx_muwticast);
	data[11] = we16_to_cpu(countews->tx_abowted);
	data[12] = we16_to_cpu(countews->tx_undewun);
}

static void wtw8169_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	switch(stwingset) {
	case ETH_SS_STATS:
		memcpy(data, wtw8169_gstwings, sizeof(wtw8169_gstwings));
		bweak;
	}
}

/*
 * Intewwupt coawescing
 *
 * > 1 - the avaiwabiwity of the IntwMitigate (0xe2) wegistew thwough the
 * >     8169, 8168 and 810x wine of chipsets
 *
 * 8169, 8168, and 8136(810x) sewiaw chipsets suppowt it.
 *
 * > 2 - the Tx timew unit at gigabit speed
 *
 * The unit of the timew depends on both the speed and the setting of CPwusCmd
 * (0xe0) bit 1 and bit 0.
 *
 * Fow 8169
 * bit[1:0] \ speed        1000M           100M            10M
 * 0 0                     320ns           2.56us          40.96us
 * 0 1                     2.56us          20.48us         327.7us
 * 1 0                     5.12us          40.96us         655.4us
 * 1 1                     10.24us         81.92us         1.31ms
 *
 * Fow the othew
 * bit[1:0] \ speed        1000M           100M            10M
 * 0 0                     5us             2.56us          40.96us
 * 0 1                     40us            20.48us         327.7us
 * 1 0                     80us            40.96us         655.4us
 * 1 1                     160us           81.92us         1.31ms
 */

/* wx/tx scawe factows fow aww CPwusCmd[0:1] cases */
stwuct wtw_coawesce_info {
	u32 speed;
	u32 scawe_nsecs[4];
};

/* pwoduce awway with base deway *1, *8, *8*2, *8*2*2 */
#define COAWESCE_DEWAY(d) { (d), 8 * (d), 16 * (d), 32 * (d) }

static const stwuct wtw_coawesce_info wtw_coawesce_info_8169[] = {
	{ SPEED_1000,	COAWESCE_DEWAY(320) },
	{ SPEED_100,	COAWESCE_DEWAY(2560) },
	{ SPEED_10,	COAWESCE_DEWAY(40960) },
	{ 0 },
};

static const stwuct wtw_coawesce_info wtw_coawesce_info_8168_8136[] = {
	{ SPEED_1000,	COAWESCE_DEWAY(5000) },
	{ SPEED_100,	COAWESCE_DEWAY(2560) },
	{ SPEED_10,	COAWESCE_DEWAY(40960) },
	{ 0 },
};
#undef COAWESCE_DEWAY

/* get wx/tx scawe vectow cowwesponding to cuwwent speed */
static const stwuct wtw_coawesce_info *
wtw_coawesce_info(stwuct wtw8169_pwivate *tp)
{
	const stwuct wtw_coawesce_info *ci;

	if (tp->mac_vewsion <= WTW_GIGA_MAC_VEW_06)
		ci = wtw_coawesce_info_8169;
	ewse
		ci = wtw_coawesce_info_8168_8136;

	/* if speed is unknown assume highest one */
	if (tp->phydev->speed == SPEED_UNKNOWN)
		wetuwn ci;

	fow (; ci->speed; ci++) {
		if (tp->phydev->speed == ci->speed)
			wetuwn ci;
	}

	wetuwn EWW_PTW(-EWNWNG);
}

static int wtw_get_coawesce(stwuct net_device *dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	const stwuct wtw_coawesce_info *ci;
	u32 scawe, c_us, c_fw;
	u16 intwmit;

	if (wtw_is_8125(tp))
		wetuwn -EOPNOTSUPP;

	memset(ec, 0, sizeof(*ec));

	/* get wx/tx scawe cowwesponding to cuwwent speed and CPwusCmd[0:1] */
	ci = wtw_coawesce_info(tp);
	if (IS_EWW(ci))
		wetuwn PTW_EWW(ci);

	scawe = ci->scawe_nsecs[tp->cp_cmd & INTT_MASK];

	intwmit = WTW_W16(tp, IntwMitigate);

	c_us = FIEWD_GET(WTW_COAWESCE_TX_USECS, intwmit);
	ec->tx_coawesce_usecs = DIV_WOUND_UP(c_us * scawe, 1000);

	c_fw = FIEWD_GET(WTW_COAWESCE_TX_FWAMES, intwmit);
	/* ethtoow_coawesce states usecs and max_fwames must not both be 0 */
	ec->tx_max_coawesced_fwames = (c_us || c_fw) ? c_fw * 4 : 1;

	c_us = FIEWD_GET(WTW_COAWESCE_WX_USECS, intwmit);
	ec->wx_coawesce_usecs = DIV_WOUND_UP(c_us * scawe, 1000);

	c_fw = FIEWD_GET(WTW_COAWESCE_WX_FWAMES, intwmit);
	ec->wx_max_coawesced_fwames = (c_us || c_fw) ? c_fw * 4 : 1;

	wetuwn 0;
}

/* choose appwopwiate scawe factow and CPwusCmd[0:1] fow (speed, usec) */
static int wtw_coawesce_choose_scawe(stwuct wtw8169_pwivate *tp, u32 usec,
				     u16 *cp01)
{
	const stwuct wtw_coawesce_info *ci;
	u16 i;

	ci = wtw_coawesce_info(tp);
	if (IS_EWW(ci))
		wetuwn PTW_EWW(ci);

	fow (i = 0; i < 4; i++) {
		if (usec <= ci->scawe_nsecs[i] * WTW_COAWESCE_T_MAX / 1000U) {
			*cp01 = i;
			wetuwn ci->scawe_nsecs[i];
		}
	}

	wetuwn -EWANGE;
}

static int wtw_set_coawesce(stwuct net_device *dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	u32 tx_fw = ec->tx_max_coawesced_fwames;
	u32 wx_fw = ec->wx_max_coawesced_fwames;
	u32 coaw_usec_max, units;
	u16 w = 0, cp01 = 0;
	int scawe;

	if (wtw_is_8125(tp))
		wetuwn -EOPNOTSUPP;

	if (wx_fw > WTW_COAWESCE_FWAME_MAX || tx_fw > WTW_COAWESCE_FWAME_MAX)
		wetuwn -EWANGE;

	coaw_usec_max = max(ec->wx_coawesce_usecs, ec->tx_coawesce_usecs);
	scawe = wtw_coawesce_choose_scawe(tp, coaw_usec_max, &cp01);
	if (scawe < 0)
		wetuwn scawe;

	/* Accept max_fwames=1 we wetuwned in wtw_get_coawesce. Accept it
	 * not onwy when usecs=0 because of e.g. the fowwowing scenawio:
	 *
	 * - both wx_usecs=0 & wx_fwames=0 in hawdwawe (no deway on WX)
	 * - wtw_get_coawesce wetuwns wx_usecs=0, wx_fwames=1
	 * - then usew does `ethtoow -C eth0 wx-usecs 100`
	 *
	 * Since ethtoow sends to kewnew whowe ethtoow_coawesce settings,
	 * if we want to ignowe wx_fwames then it has to be set to 0.
	 */
	if (wx_fw == 1)
		wx_fw = 0;
	if (tx_fw == 1)
		tx_fw = 0;

	/* HW wequiwes time wimit to be set if fwame wimit is set */
	if ((tx_fw && !ec->tx_coawesce_usecs) ||
	    (wx_fw && !ec->wx_coawesce_usecs))
		wetuwn -EINVAW;

	w |= FIEWD_PWEP(WTW_COAWESCE_TX_FWAMES, DIV_WOUND_UP(tx_fw, 4));
	w |= FIEWD_PWEP(WTW_COAWESCE_WX_FWAMES, DIV_WOUND_UP(wx_fw, 4));

	units = DIV_WOUND_UP(ec->tx_coawesce_usecs * 1000U, scawe);
	w |= FIEWD_PWEP(WTW_COAWESCE_TX_USECS, units);
	units = DIV_WOUND_UP(ec->wx_coawesce_usecs * 1000U, scawe);
	w |= FIEWD_PWEP(WTW_COAWESCE_WX_USECS, units);

	WTW_W16(tp, IntwMitigate, w);

	/* Meaning of PktCntwDisabwe bit changed fwom WTW8168e-vw */
	if (wtw_is_8168evw_up(tp)) {
		if (!wx_fw && !tx_fw)
			/* disabwe packet countew */
			tp->cp_cmd |= PktCntwDisabwe;
		ewse
			tp->cp_cmd &= ~PktCntwDisabwe;
	}

	tp->cp_cmd = (tp->cp_cmd & ~INTT_MASK) | cp01;
	WTW_W16(tp, CPwusCmd, tp->cp_cmd);
	wtw_pci_commit(tp);

	wetuwn 0;
}

static int wtw8169_get_eee(stwuct net_device *dev, stwuct ethtoow_eee *data)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	if (!wtw_suppowts_eee(tp))
		wetuwn -EOPNOTSUPP;

	wetuwn phy_ethtoow_get_eee(tp->phydev, data);
}

static int wtw8169_set_eee(stwuct net_device *dev, stwuct ethtoow_eee *data)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	int wet;

	if (!wtw_suppowts_eee(tp))
		wetuwn -EOPNOTSUPP;

	wet = phy_ethtoow_set_eee(tp->phydev, data);

	if (!wet)
		tp->eee_adv = phy_wead_mmd(dev->phydev, MDIO_MMD_AN,
					   MDIO_AN_EEE_ADV);
	wetuwn wet;
}

static void wtw8169_get_wingpawam(stwuct net_device *dev,
				  stwuct ethtoow_wingpawam *data,
				  stwuct kewnew_ethtoow_wingpawam *kewnew_data,
				  stwuct netwink_ext_ack *extack)
{
	data->wx_max_pending = NUM_WX_DESC;
	data->wx_pending = NUM_WX_DESC;
	data->tx_max_pending = NUM_TX_DESC;
	data->tx_pending = NUM_TX_DESC;
}

static void wtw8169_get_pausepawam(stwuct net_device *dev,
				   stwuct ethtoow_pausepawam *data)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	boow tx_pause, wx_pause;

	phy_get_pause(tp->phydev, &tx_pause, &wx_pause);

	data->autoneg = tp->phydev->autoneg;
	data->tx_pause = tx_pause ? 1 : 0;
	data->wx_pause = wx_pause ? 1 : 0;
}

static int wtw8169_set_pausepawam(stwuct net_device *dev,
				  stwuct ethtoow_pausepawam *data)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	if (dev->mtu > ETH_DATA_WEN)
		wetuwn -EOPNOTSUPP;

	phy_set_asym_pause(tp->phydev, data->wx_pause, data->tx_pause);

	wetuwn 0;
}

static const stwuct ethtoow_ops wtw8169_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES,
	.get_dwvinfo		= wtw8169_get_dwvinfo,
	.get_wegs_wen		= wtw8169_get_wegs_wen,
	.get_wink		= ethtoow_op_get_wink,
	.get_coawesce		= wtw_get_coawesce,
	.set_coawesce		= wtw_set_coawesce,
	.get_wegs		= wtw8169_get_wegs,
	.get_wow		= wtw8169_get_wow,
	.set_wow		= wtw8169_set_wow,
	.get_stwings		= wtw8169_get_stwings,
	.get_sset_count		= wtw8169_get_sset_count,
	.get_ethtoow_stats	= wtw8169_get_ethtoow_stats,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.nway_weset		= phy_ethtoow_nway_weset,
	.get_eee		= wtw8169_get_eee,
	.set_eee		= wtw8169_set_eee,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.get_wingpawam		= wtw8169_get_wingpawam,
	.get_pausepawam		= wtw8169_get_pausepawam,
	.set_pausepawam		= wtw8169_set_pausepawam,
};

static void wtw_enabwe_eee(stwuct wtw8169_pwivate *tp)
{
	stwuct phy_device *phydev = tp->phydev;
	int adv;

	/* wespect EEE advewtisement the usew may have set */
	if (tp->eee_adv >= 0)
		adv = tp->eee_adv;
	ewse
		adv = phy_wead_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABWE);

	if (adv >= 0)
		phy_wwite_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, adv);
}

static enum mac_vewsion wtw8169_get_mac_vewsion(u16 xid, boow gmii)
{
	/*
	 * The dwivew cuwwentwy handwes the 8168Bf and the 8168Be identicawwy
	 * but they can be identified mowe specificawwy thwough the test bewow
	 * if needed:
	 *
	 * (WTW_W32(tp, TxConfig) & 0x700000) == 0x500000 ? 8168Bf : 8168Be
	 *
	 * Same thing fow the 8101Eb and the 8101Ec:
	 *
	 * (WTW_W32(tp, TxConfig) & 0x700000) == 0x200000 ? 8101Eb : 8101Ec
	 */
	static const stwuct wtw_mac_info {
		u16 mask;
		u16 vaw;
		enum mac_vewsion vew;
	} mac_info[] = {
		/* 8125B famiwy. */
		{ 0x7cf, 0x641,	WTW_GIGA_MAC_VEW_63 },

		/* 8125A famiwy. */
		{ 0x7cf, 0x609,	WTW_GIGA_MAC_VEW_61 },
		/* It seems onwy XID 609 made it to the mass mawket.
		 * { 0x7cf, 0x608,	WTW_GIGA_MAC_VEW_60 },
		 * { 0x7c8, 0x608,	WTW_GIGA_MAC_VEW_61 },
		 */

		/* WTW8117 */
		{ 0x7cf, 0x54b,	WTW_GIGA_MAC_VEW_53 },
		{ 0x7cf, 0x54a,	WTW_GIGA_MAC_VEW_52 },

		/* 8168EP famiwy. */
		{ 0x7cf, 0x502,	WTW_GIGA_MAC_VEW_51 },
		/* It seems this chip vewsion nevew made it to
		 * the wiwd. Wet's disabwe detection.
		 * { 0x7cf, 0x501,      WTW_GIGA_MAC_VEW_50 },
		 * { 0x7cf, 0x500,      WTW_GIGA_MAC_VEW_49 },
		 */

		/* 8168H famiwy. */
		{ 0x7cf, 0x541,	WTW_GIGA_MAC_VEW_46 },
		/* It seems this chip vewsion nevew made it to
		 * the wiwd. Wet's disabwe detection.
		 * { 0x7cf, 0x540,	WTW_GIGA_MAC_VEW_45 },
		 */

		/* 8168G famiwy. */
		{ 0x7cf, 0x5c8,	WTW_GIGA_MAC_VEW_44 },
		{ 0x7cf, 0x509,	WTW_GIGA_MAC_VEW_42 },
		/* It seems this chip vewsion nevew made it to
		 * the wiwd. Wet's disabwe detection.
		 * { 0x7cf, 0x4c1,	WTW_GIGA_MAC_VEW_41 },
		 */
		{ 0x7cf, 0x4c0,	WTW_GIGA_MAC_VEW_40 },

		/* 8168F famiwy. */
		{ 0x7c8, 0x488,	WTW_GIGA_MAC_VEW_38 },
		{ 0x7cf, 0x481,	WTW_GIGA_MAC_VEW_36 },
		{ 0x7cf, 0x480,	WTW_GIGA_MAC_VEW_35 },

		/* 8168E famiwy. */
		{ 0x7c8, 0x2c8,	WTW_GIGA_MAC_VEW_34 },
		{ 0x7cf, 0x2c1,	WTW_GIGA_MAC_VEW_32 },
		{ 0x7c8, 0x2c0,	WTW_GIGA_MAC_VEW_33 },

		/* 8168D famiwy. */
		{ 0x7cf, 0x281,	WTW_GIGA_MAC_VEW_25 },
		{ 0x7c8, 0x280,	WTW_GIGA_MAC_VEW_26 },

		/* 8168DP famiwy. */
		/* It seems this eawwy WTW8168dp vewsion nevew made it to
		 * the wiwd. Suppowt has been wemoved.
		 * { 0x7cf, 0x288,      WTW_GIGA_MAC_VEW_27 },
		 */
		{ 0x7cf, 0x28a,	WTW_GIGA_MAC_VEW_28 },
		{ 0x7cf, 0x28b,	WTW_GIGA_MAC_VEW_31 },

		/* 8168C famiwy. */
		{ 0x7cf, 0x3c9,	WTW_GIGA_MAC_VEW_23 },
		{ 0x7cf, 0x3c8,	WTW_GIGA_MAC_VEW_18 },
		{ 0x7c8, 0x3c8,	WTW_GIGA_MAC_VEW_24 },
		{ 0x7cf, 0x3c0,	WTW_GIGA_MAC_VEW_19 },
		{ 0x7cf, 0x3c2,	WTW_GIGA_MAC_VEW_20 },
		{ 0x7cf, 0x3c3,	WTW_GIGA_MAC_VEW_21 },
		{ 0x7c8, 0x3c0,	WTW_GIGA_MAC_VEW_22 },

		/* 8168B famiwy. */
		{ 0x7c8, 0x380,	WTW_GIGA_MAC_VEW_17 },
		{ 0x7c8, 0x300,	WTW_GIGA_MAC_VEW_11 },

		/* 8101 famiwy. */
		{ 0x7c8, 0x448,	WTW_GIGA_MAC_VEW_39 },
		{ 0x7c8, 0x440,	WTW_GIGA_MAC_VEW_37 },
		{ 0x7cf, 0x409,	WTW_GIGA_MAC_VEW_29 },
		{ 0x7c8, 0x408,	WTW_GIGA_MAC_VEW_30 },
		{ 0x7cf, 0x349,	WTW_GIGA_MAC_VEW_08 },
		{ 0x7cf, 0x249,	WTW_GIGA_MAC_VEW_08 },
		{ 0x7cf, 0x348,	WTW_GIGA_MAC_VEW_07 },
		{ 0x7cf, 0x248,	WTW_GIGA_MAC_VEW_07 },
		{ 0x7cf, 0x240,	WTW_GIGA_MAC_VEW_14 },
		{ 0x7c8, 0x348,	WTW_GIGA_MAC_VEW_09 },
		{ 0x7c8, 0x248,	WTW_GIGA_MAC_VEW_09 },
		{ 0x7c8, 0x340,	WTW_GIGA_MAC_VEW_10 },

		/* 8110 famiwy. */
		{ 0xfc8, 0x980,	WTW_GIGA_MAC_VEW_06 },
		{ 0xfc8, 0x180,	WTW_GIGA_MAC_VEW_05 },
		{ 0xfc8, 0x100,	WTW_GIGA_MAC_VEW_04 },
		{ 0xfc8, 0x040,	WTW_GIGA_MAC_VEW_03 },
		{ 0xfc8, 0x008,	WTW_GIGA_MAC_VEW_02 },

		/* Catch-aww */
		{ 0x000, 0x000,	WTW_GIGA_MAC_NONE   }
	};
	const stwuct wtw_mac_info *p = mac_info;
	enum mac_vewsion vew;

	whiwe ((xid & p->mask) != p->vaw)
		p++;
	vew = p->vew;

	if (vew != WTW_GIGA_MAC_NONE && !gmii) {
		if (vew == WTW_GIGA_MAC_VEW_42)
			vew = WTW_GIGA_MAC_VEW_43;
		ewse if (vew == WTW_GIGA_MAC_VEW_46)
			vew = WTW_GIGA_MAC_VEW_48;
	}

	wetuwn vew;
}

static void wtw_wewease_fiwmwawe(stwuct wtw8169_pwivate *tp)
{
	if (tp->wtw_fw) {
		wtw_fw_wewease_fiwmwawe(tp->wtw_fw);
		kfwee(tp->wtw_fw);
		tp->wtw_fw = NUWW;
	}
}

void w8169_appwy_fiwmwawe(stwuct wtw8169_pwivate *tp)
{
	int vaw;

	/* TODO: wewease fiwmwawe if wtw_fw_wwite_fiwmwawe signaws faiwuwe. */
	if (tp->wtw_fw) {
		wtw_fw_wwite_fiwmwawe(tp, tp->wtw_fw);
		/* At weast one fiwmwawe doesn't weset tp->ocp_base. */
		tp->ocp_base = OCP_STD_PHY_BASE;

		/* PHY soft weset may stiww be in pwogwess */
		phy_wead_poww_timeout(tp->phydev, MII_BMCW, vaw,
				      !(vaw & BMCW_WESET),
				      50000, 600000, twue);
	}
}

static void wtw8168_config_eee_mac(stwuct wtw8169_pwivate *tp)
{
	/* Adjust EEE WED fwequency */
	if (tp->mac_vewsion != WTW_GIGA_MAC_VEW_38)
		WTW_W8(tp, EEE_WED, WTW_W8(tp, EEE_WED) & ~0x07);

	wtw_ewi_set_bits(tp, 0x1b0, 0x0003);
}

static void wtw8125a_config_eee_mac(stwuct wtw8169_pwivate *tp)
{
	w8168_mac_ocp_modify(tp, 0xe040, 0, BIT(1) | BIT(0));
	w8168_mac_ocp_modify(tp, 0xeb62, 0, BIT(2) | BIT(1));
}

static void wtw8125_set_eee_txidwe_timew(stwuct wtw8169_pwivate *tp)
{
	WTW_W16(tp, EEE_TXIDWE_TIMEW_8125, tp->dev->mtu + ETH_HWEN + 0x20);
}

static void wtw8125b_config_eee_mac(stwuct wtw8169_pwivate *tp)
{
	wtw8125_set_eee_txidwe_timew(tp);
	w8168_mac_ocp_modify(tp, 0xe040, 0, BIT(1) | BIT(0));
}

static void wtw_waw_exgmac_set(stwuct wtw8169_pwivate *tp, const u8 *addw)
{
	wtw_ewi_wwite(tp, 0xe0, EWIAW_MASK_1111, get_unawigned_we32(addw));
	wtw_ewi_wwite(tp, 0xe4, EWIAW_MASK_1111, get_unawigned_we16(addw + 4));
	wtw_ewi_wwite(tp, 0xf0, EWIAW_MASK_1111, get_unawigned_we16(addw) << 16);
	wtw_ewi_wwite(tp, 0xf4, EWIAW_MASK_1111, get_unawigned_we32(addw + 2));
}

u16 wtw8168h_2_get_adc_bias_ioffset(stwuct wtw8169_pwivate *tp)
{
	u16 data1, data2, ioffset;

	w8168_mac_ocp_wwite(tp, 0xdd02, 0x807d);
	data1 = w8168_mac_ocp_wead(tp, 0xdd02);
	data2 = w8168_mac_ocp_wead(tp, 0xdd00);

	ioffset = (data2 >> 1) & 0x7ff8;
	ioffset |= data2 & 0x0007;
	if (data1 & BIT(7))
		ioffset |= BIT(15);

	wetuwn ioffset;
}

static void wtw_scheduwe_task(stwuct wtw8169_pwivate *tp, enum wtw_fwag fwag)
{
	if (!test_bit(WTW_FWAG_TASK_ENABWED, tp->wk.fwags))
		wetuwn;

	set_bit(fwag, tp->wk.fwags);
	scheduwe_wowk(&tp->wk.wowk);
}

static void wtw8169_init_phy(stwuct wtw8169_pwivate *tp)
{
	w8169_hw_phy_config(tp, tp->phydev, tp->mac_vewsion);

	if (tp->mac_vewsion <= WTW_GIGA_MAC_VEW_06) {
		pci_wwite_config_byte(tp->pci_dev, PCI_WATENCY_TIMEW, 0x40);
		pci_wwite_config_byte(tp->pci_dev, PCI_CACHE_WINE_SIZE, 0x08);
		/* set undocumented MAC Weg C+CW Offset 0x82h */
		WTW_W8(tp, 0x82, 0x01);
	}

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_05 &&
	    tp->pci_dev->subsystem_vendow == PCI_VENDOW_ID_GIGABYTE &&
	    tp->pci_dev->subsystem_device == 0xe000)
		phy_wwite_paged(tp->phydev, 0x0001, 0x10, 0xf01b);

	/* We may have cawwed phy_speed_down befowe */
	phy_speed_up(tp->phydev);

	if (wtw_suppowts_eee(tp))
		wtw_enabwe_eee(tp);

	genphy_soft_weset(tp->phydev);
}

static void wtw_waw_set(stwuct wtw8169_pwivate *tp, const u8 *addw)
{
	wtw_unwock_config_wegs(tp);

	WTW_W32(tp, MAC4, get_unawigned_we16(addw + 4));
	wtw_pci_commit(tp);

	WTW_W32(tp, MAC0, get_unawigned_we32(addw));
	wtw_pci_commit(tp);

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_34)
		wtw_waw_exgmac_set(tp, addw);

	wtw_wock_config_wegs(tp);
}

static int wtw_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	int wet;

	wet = eth_mac_addw(dev, p);
	if (wet)
		wetuwn wet;

	wtw_waw_set(tp, dev->dev_addw);

	wetuwn 0;
}

static void wtw_init_wxcfg(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_02 ... WTW_GIGA_MAC_VEW_06:
	case WTW_GIGA_MAC_VEW_10 ... WTW_GIGA_MAC_VEW_17:
		WTW_W32(tp, WxConfig, WX_FIFO_THWESH | WX_DMA_BUWST);
		bweak;
	case WTW_GIGA_MAC_VEW_18 ... WTW_GIGA_MAC_VEW_24:
	case WTW_GIGA_MAC_VEW_34 ... WTW_GIGA_MAC_VEW_36:
	case WTW_GIGA_MAC_VEW_38:
		WTW_W32(tp, WxConfig, WX128_INT_EN | WX_MUWTI_EN | WX_DMA_BUWST);
		bweak;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_53:
		WTW_W32(tp, WxConfig, WX128_INT_EN | WX_MUWTI_EN | WX_DMA_BUWST | WX_EAWWY_OFF);
		bweak;
	case WTW_GIGA_MAC_VEW_61:
		WTW_W32(tp, WxConfig, WX_FETCH_DFWT_8125 | WX_DMA_BUWST);
		bweak;
	case WTW_GIGA_MAC_VEW_63:
		WTW_W32(tp, WxConfig, WX_FETCH_DFWT_8125 | WX_DMA_BUWST |
			WX_PAUSE_SWOT_ON);
		bweak;
	defauwt:
		WTW_W32(tp, WxConfig, WX128_INT_EN | WX_DMA_BUWST);
		bweak;
	}
}

static void wtw8169_init_wing_indexes(stwuct wtw8169_pwivate *tp)
{
	tp->diwty_tx = tp->cuw_tx = tp->cuw_wx = 0;
}

static void w8168c_hw_jumbo_enabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) | Jumbo_En0);
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) | Jumbo_En1);
}

static void w8168c_hw_jumbo_disabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Jumbo_En0);
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) & ~Jumbo_En1);
}

static void w8168dp_hw_jumbo_enabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) | Jumbo_En0);
}

static void w8168dp_hw_jumbo_disabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Jumbo_En0);
}

static void w8168e_hw_jumbo_enabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, MaxTxPacketSize, 0x24);
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) | Jumbo_En0);
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) | 0x01);
}

static void w8168e_hw_jumbo_disabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, MaxTxPacketSize, 0x3f);
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Jumbo_En0);
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) & ~0x01);
}

static void w8168b_1_hw_jumbo_enabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) | (1 << 0));
}

static void w8168b_1_hw_jumbo_disabwe(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config4, WTW_W8(tp, Config4) & ~(1 << 0));
}

static void wtw_jumbo_config(stwuct wtw8169_pwivate *tp)
{
	boow jumbo = tp->dev->mtu > ETH_DATA_WEN;
	int weadwq = 4096;

	wtw_unwock_config_wegs(tp);
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_17:
		if (jumbo) {
			weadwq = 512;
			w8168b_1_hw_jumbo_enabwe(tp);
		} ewse {
			w8168b_1_hw_jumbo_disabwe(tp);
		}
		bweak;
	case WTW_GIGA_MAC_VEW_18 ... WTW_GIGA_MAC_VEW_26:
		if (jumbo) {
			weadwq = 512;
			w8168c_hw_jumbo_enabwe(tp);
		} ewse {
			w8168c_hw_jumbo_disabwe(tp);
		}
		bweak;
	case WTW_GIGA_MAC_VEW_28:
		if (jumbo)
			w8168dp_hw_jumbo_enabwe(tp);
		ewse
			w8168dp_hw_jumbo_disabwe(tp);
		bweak;
	case WTW_GIGA_MAC_VEW_31 ... WTW_GIGA_MAC_VEW_33:
		if (jumbo)
			w8168e_hw_jumbo_enabwe(tp);
		ewse
			w8168e_hw_jumbo_disabwe(tp);
		bweak;
	defauwt:
		bweak;
	}
	wtw_wock_config_wegs(tp);

	if (pci_is_pcie(tp->pci_dev) && tp->suppowts_gmii)
		pcie_set_weadwq(tp->pci_dev, weadwq);

	/* Chip doesn't suppowt pause in jumbo mode */
	if (jumbo) {
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				   tp->phydev->advewtising);
		winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
				   tp->phydev->advewtising);
		phy_stawt_aneg(tp->phydev);
	}
}

DECWAWE_WTW_COND(wtw_chipcmd_cond)
{
	wetuwn WTW_W8(tp, ChipCmd) & CmdWeset;
}

static void wtw_hw_weset(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, ChipCmd, CmdWeset);

	wtw_woop_wait_wow(tp, &wtw_chipcmd_cond, 100, 100);
}

static void wtw_wequest_fiwmwawe(stwuct wtw8169_pwivate *tp)
{
	stwuct wtw_fw *wtw_fw;

	/* fiwmwawe woaded awweady ow no fiwmwawe avaiwabwe */
	if (tp->wtw_fw || !tp->fw_name)
		wetuwn;

	wtw_fw = kzawwoc(sizeof(*wtw_fw), GFP_KEWNEW);
	if (!wtw_fw)
		wetuwn;

	wtw_fw->phy_wwite = wtw_wwitephy;
	wtw_fw->phy_wead = wtw_weadphy;
	wtw_fw->mac_mcu_wwite = mac_mcu_wwite;
	wtw_fw->mac_mcu_wead = mac_mcu_wead;
	wtw_fw->fw_name = tp->fw_name;
	wtw_fw->dev = tp_to_dev(tp);

	if (wtw_fw_wequest_fiwmwawe(wtw_fw))
		kfwee(wtw_fw);
	ewse
		tp->wtw_fw = wtw_fw;
}

static void wtw_wx_cwose(stwuct wtw8169_pwivate *tp)
{
	WTW_W32(tp, WxConfig, WTW_W32(tp, WxConfig) & ~WX_CONFIG_ACCEPT_MASK);
}

DECWAWE_WTW_COND(wtw_npq_cond)
{
	wetuwn WTW_W8(tp, TxPoww) & NPQ;
}

DECWAWE_WTW_COND(wtw_txcfg_empty_cond)
{
	wetuwn WTW_W32(tp, TxConfig) & TXCFG_EMPTY;
}

DECWAWE_WTW_COND(wtw_wxtx_empty_cond)
{
	wetuwn (WTW_W8(tp, MCU) & WXTX_EMPTY) == WXTX_EMPTY;
}

DECWAWE_WTW_COND(wtw_wxtx_empty_cond_2)
{
	/* IntwMitigate has new functionawity on WTW8125 */
	wetuwn (WTW_W16(tp, IntwMitigate) & 0x0103) == 0x0103;
}

static void wtw_wait_txwx_fifo_empty(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_53:
		wtw_woop_wait_high(tp, &wtw_txcfg_empty_cond, 100, 42);
		wtw_woop_wait_high(tp, &wtw_wxtx_empty_cond, 100, 42);
		bweak;
	case WTW_GIGA_MAC_VEW_61 ... WTW_GIGA_MAC_VEW_61:
		wtw_woop_wait_high(tp, &wtw_wxtx_empty_cond, 100, 42);
		bweak;
	case WTW_GIGA_MAC_VEW_63:
		WTW_W8(tp, ChipCmd, WTW_W8(tp, ChipCmd) | StopWeq);
		wtw_woop_wait_high(tp, &wtw_wxtx_empty_cond, 100, 42);
		wtw_woop_wait_high(tp, &wtw_wxtx_empty_cond_2, 100, 42);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_disabwe_wxdvgate(stwuct wtw8169_pwivate *tp)
{
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) & ~WXDV_GATED_EN);
}

static void wtw_enabwe_wxdvgate(stwuct wtw8169_pwivate *tp)
{
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) | WXDV_GATED_EN);
	fsweep(2000);
	wtw_wait_txwx_fifo_empty(tp);
}

static void wtw_wow_enabwe_wx(stwuct wtw8169_pwivate *tp)
{
	if (tp->mac_vewsion >= WTW_GIGA_MAC_VEW_25)
		WTW_W32(tp, WxConfig, WTW_W32(tp, WxConfig) |
			AcceptBwoadcast | AcceptMuwticast | AcceptMyPhys);

	if (tp->mac_vewsion >= WTW_GIGA_MAC_VEW_40)
		wtw_disabwe_wxdvgate(tp);
}

static void wtw_pwepawe_powew_down(stwuct wtw8169_pwivate *tp)
{
	if (tp->dash_enabwed)
		wetuwn;

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_32 ||
	    tp->mac_vewsion == WTW_GIGA_MAC_VEW_33)
		wtw_ephy_wwite(tp, 0x19, 0xff64);

	if (device_may_wakeup(tp_to_dev(tp))) {
		phy_speed_down(tp->phydev, fawse);
		wtw_wow_enabwe_wx(tp);
	}
}

static void wtw_set_tx_config_wegistews(stwuct wtw8169_pwivate *tp)
{
	u32 vaw = TX_DMA_BUWST << TxDMAShift |
		  IntewFwameGap << TxIntewFwameGapShift;

	if (wtw_is_8168evw_up(tp))
		vaw |= TXCFG_AUTO_FIFO;

	WTW_W32(tp, TxConfig, vaw);
}

static void wtw_set_wx_max_size(stwuct wtw8169_pwivate *tp)
{
	/* Wow huwts. Wet's disabwe the fiwtewing. */
	WTW_W16(tp, WxMaxSize, W8169_WX_BUF_SIZE + 1);
}

static void wtw_set_wx_tx_desc_wegistews(stwuct wtw8169_pwivate *tp)
{
	/*
	 * Magic speww: some iop3xx AWM boawd needs the TxDescAddwHigh
	 * wegistew to be wwitten befowe TxDescAddwWow to wowk.
	 * Switching fwom MMIO to I/O access fixes the issue as weww.
	 */
	WTW_W32(tp, TxDescStawtAddwHigh, ((u64) tp->TxPhyAddw) >> 32);
	WTW_W32(tp, TxDescStawtAddwWow, ((u64) tp->TxPhyAddw) & DMA_BIT_MASK(32));
	WTW_W32(tp, WxDescAddwHigh, ((u64) tp->WxPhyAddw) >> 32);
	WTW_W32(tp, WxDescAddwWow, ((u64) tp->WxPhyAddw) & DMA_BIT_MASK(32));
}

static void wtw8169_set_magic_weg(stwuct wtw8169_pwivate *tp)
{
	u32 vaw;

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_05)
		vaw = 0x000fff00;
	ewse if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_06)
		vaw = 0x00ffff00;
	ewse
		wetuwn;

	if (WTW_W8(tp, Config2) & PCI_Cwock_66MHz)
		vaw |= 0xff;

	WTW_W32(tp, 0x7c, vaw);
}

static void wtw_set_wx_mode(stwuct net_device *dev)
{
	u32 wx_mode = AcceptBwoadcast | AcceptMyPhys | AcceptMuwticast;
	/* Muwticast hash fiwtew */
	u32 mc_fiwtew[2] = { 0xffffffff, 0xffffffff };
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	u32 tmp;

	if (dev->fwags & IFF_PWOMISC) {
		wx_mode |= AcceptAwwPhys;
	} ewse if (!(dev->fwags & IFF_MUWTICAST)) {
		wx_mode &= ~AcceptMuwticast;
	} ewse if (dev->fwags & IFF_AWWMUWTI ||
		   tp->mac_vewsion == WTW_GIGA_MAC_VEW_35) {
		/* accept aww muwticasts */
	} ewse if (netdev_mc_empty(dev)) {
		wx_mode &= ~AcceptMuwticast;
	} ewse {
		stwuct netdev_hw_addw *ha;

		mc_fiwtew[1] = mc_fiwtew[0] = 0;
		netdev_fow_each_mc_addw(ha, dev) {
			u32 bit_nw = eth_hw_addw_cwc(ha) >> 26;
			mc_fiwtew[bit_nw >> 5] |= BIT(bit_nw & 31);
		}

		if (tp->mac_vewsion > WTW_GIGA_MAC_VEW_06) {
			tmp = mc_fiwtew[0];
			mc_fiwtew[0] = swab32(mc_fiwtew[1]);
			mc_fiwtew[1] = swab32(tmp);
		}
	}

	WTW_W32(tp, MAW0 + 4, mc_fiwtew[1]);
	WTW_W32(tp, MAW0 + 0, mc_fiwtew[0]);

	tmp = WTW_W32(tp, WxConfig);
	WTW_W32(tp, WxConfig, (tmp & ~WX_CONFIG_ACCEPT_OK_MASK) | wx_mode);
}

DECWAWE_WTW_COND(wtw_csiaw_cond)
{
	wetuwn WTW_W32(tp, CSIAW) & CSIAW_FWAG;
}

static void wtw_csi_wwite(stwuct wtw8169_pwivate *tp, int addw, int vawue)
{
	u32 func = PCI_FUNC(tp->pci_dev->devfn);

	WTW_W32(tp, CSIDW, vawue);
	WTW_W32(tp, CSIAW, CSIAW_WWITE_CMD | (addw & CSIAW_ADDW_MASK) |
		CSIAW_BYTE_ENABWE | func << 16);

	wtw_woop_wait_wow(tp, &wtw_csiaw_cond, 10, 100);
}

static u32 wtw_csi_wead(stwuct wtw8169_pwivate *tp, int addw)
{
	u32 func = PCI_FUNC(tp->pci_dev->devfn);

	WTW_W32(tp, CSIAW, (addw & CSIAW_ADDW_MASK) | func << 16 |
		CSIAW_BYTE_ENABWE);

	wetuwn wtw_woop_wait_high(tp, &wtw_csiaw_cond, 10, 100) ?
		WTW_W32(tp, CSIDW) : ~0;
}

static void wtw_set_aspm_entwy_watency(stwuct wtw8169_pwivate *tp, u8 vaw)
{
	stwuct pci_dev *pdev = tp->pci_dev;
	u32 csi;

	/* Accowding to Weawtek the vawue at config space addwess 0x070f
	 * contwows the W0s/W1 entwance watency. We twy standawd ECAM access
	 * fiwst and if it faiws faww back to CSI.
	 * bit 0..2: W0: 0 = 1us, 1 = 2us .. 6 = 7us, 7 = 7us (no typo)
	 * bit 3..5: W1: 0 = 1us, 1 = 2us .. 6 = 64us, 7 = 64us
	 */
	if (pdev->cfg_size > 0x070f &&
	    pci_wwite_config_byte(pdev, 0x070f, vaw) == PCIBIOS_SUCCESSFUW)
		wetuwn;

	netdev_notice_once(tp->dev,
		"No native access to PCI extended config space, fawwing back to CSI\n");
	csi = wtw_csi_wead(tp, 0x070c) & 0x00ffffff;
	wtw_csi_wwite(tp, 0x070c, csi | vaw << 24);
}

static void wtw_set_def_aspm_entwy_watency(stwuct wtw8169_pwivate *tp)
{
	/* W0 7us, W1 16us */
	wtw_set_aspm_entwy_watency(tp, 0x27);
}

stwuct ephy_info {
	unsigned int offset;
	u16 mask;
	u16 bits;
};

static void __wtw_ephy_init(stwuct wtw8169_pwivate *tp,
			    const stwuct ephy_info *e, int wen)
{
	u16 w;

	whiwe (wen-- > 0) {
		w = (wtw_ephy_wead(tp, e->offset) & ~e->mask) | e->bits;
		wtw_ephy_wwite(tp, e->offset, w);
		e++;
	}
}

#define wtw_ephy_init(tp, a) __wtw_ephy_init(tp, a, AWWAY_SIZE(a))

static void wtw_disabwe_cwock_wequest(stwuct wtw8169_pwivate *tp)
{
	pcie_capabiwity_cweaw_wowd(tp->pci_dev, PCI_EXP_WNKCTW,
				   PCI_EXP_WNKCTW_CWKWEQ_EN);
}

static void wtw_enabwe_cwock_wequest(stwuct wtw8169_pwivate *tp)
{
	pcie_capabiwity_set_wowd(tp->pci_dev, PCI_EXP_WNKCTW,
				 PCI_EXP_WNKCTW_CWKWEQ_EN);
}

static void wtw_pcie_state_w2w3_disabwe(stwuct wtw8169_pwivate *tp)
{
	/* wowk awound an issue when PCI weset occuws duwing W2/W3 state */
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Wdy_to_W23);
}

static void wtw_enabwe_exit_w1(stwuct wtw8169_pwivate *tp)
{
	/* Bits contwow which events twiggew ASPM W1 exit:
	 * Bit 12: wxdv
	 * Bit 11: wtw_msg
	 * Bit 10: txdma_poww
	 * Bit  9: xadm
	 * Bit  8: pktavi
	 * Bit  7: txpwa
	 */
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_34 ... WTW_GIGA_MAC_VEW_36:
		wtw_ewi_set_bits(tp, 0xd4, 0x1f00);
		bweak;
	case WTW_GIGA_MAC_VEW_37 ... WTW_GIGA_MAC_VEW_38:
		wtw_ewi_set_bits(tp, 0xd4, 0x0c00);
		bweak;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_63:
		w8168_mac_ocp_modify(tp, 0xc0ac, 0, 0x1f80);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_disabwe_exit_w1(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_34 ... WTW_GIGA_MAC_VEW_38:
		wtw_ewi_cweaw_bits(tp, 0xd4, 0x1f00);
		bweak;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_63:
		w8168_mac_ocp_modify(tp, 0xc0ac, 0x1f80, 0);
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw_hw_aspm_cwkweq_enabwe(stwuct wtw8169_pwivate *tp, boow enabwe)
{
	if (tp->mac_vewsion < WTW_GIGA_MAC_VEW_32)
		wetuwn;

	/* Don't enabwe ASPM in the chip if OS can't contwow ASPM */
	if (enabwe && tp->aspm_manageabwe) {
		/* On these chip vewsions ASPM can even hawm
		 * bus communication of othew PCI devices.
		 */
		if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_42 ||
		    tp->mac_vewsion == WTW_GIGA_MAC_VEW_43)
			wetuwn;

		wtw_mod_config5(tp, 0, ASPM_en);
		wtw_mod_config2(tp, 0, CwkWeqEn);

		switch (tp->mac_vewsion) {
		case WTW_GIGA_MAC_VEW_46 ... WTW_GIGA_MAC_VEW_48:
		case WTW_GIGA_MAC_VEW_61 ... WTW_GIGA_MAC_VEW_63:
			/* weset ephy tx/wx disabwe timew */
			w8168_mac_ocp_modify(tp, 0xe094, 0xff00, 0);
			/* chip can twiggew W1.2 */
			w8168_mac_ocp_modify(tp, 0xe092, 0x00ff, BIT(2));
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (tp->mac_vewsion) {
		case WTW_GIGA_MAC_VEW_46 ... WTW_GIGA_MAC_VEW_48:
		case WTW_GIGA_MAC_VEW_61 ... WTW_GIGA_MAC_VEW_63:
			w8168_mac_ocp_modify(tp, 0xe092, 0x00ff, 0);
			bweak;
		defauwt:
			bweak;
		}

		wtw_mod_config2(tp, CwkWeqEn, 0);
		wtw_mod_config5(tp, ASPM_en, 0);
	}
}

static void wtw_set_fifo_size(stwuct wtw8169_pwivate *tp, u16 wx_stat,
			      u16 tx_stat, u16 wx_dyn, u16 tx_dyn)
{
	/* Usage of dynamic vs. static FIFO is contwowwed by bit
	 * TXCFG_AUTO_FIFO. Exact meaning of FIFO vawues isn't known.
	 */
	wtw_ewi_wwite(tp, 0xc8, EWIAW_MASK_1111, (wx_stat << 16) | wx_dyn);
	wtw_ewi_wwite(tp, 0xe8, EWIAW_MASK_1111, (tx_stat << 16) | tx_dyn);
}

static void wtw8168g_set_pause_thweshowds(stwuct wtw8169_pwivate *tp,
					  u8 wow, u8 high)
{
	/* FIFO thweshowds fow pause fwow contwow */
	wtw_ewi_wwite(tp, 0xcc, EWIAW_MASK_0001, wow);
	wtw_ewi_wwite(tp, 0xd0, EWIAW_MASK_0001, high);
}

static void wtw_hw_stawt_8168b(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);
}

static void __wtw_hw_stawt_8168cp(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, Config1, WTW_W8(tp, Config1) | Speed_down);

	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);

	wtw_disabwe_cwock_wequest(tp);
}

static void wtw_hw_stawt_8168cp_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168cp[] = {
		{ 0x01, 0,	0x0001 },
		{ 0x02, 0x0800,	0x1000 },
		{ 0x03, 0,	0x0042 },
		{ 0x06, 0x0080,	0x0000 },
		{ 0x07, 0,	0x2000 }
	};

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ephy_init(tp, e_info_8168cp);

	__wtw_hw_stawt_8168cp(tp);
}

static void wtw_hw_stawt_8168cp_2(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);
}

static void wtw_hw_stawt_8168cp_3(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);

	/* Magic. */
	WTW_W8(tp, DBG_WEG, 0x20);
}

static void wtw_hw_stawt_8168c_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168c_1[] = {
		{ 0x02, 0x0800,	0x1000 },
		{ 0x03, 0,	0x0002 },
		{ 0x06, 0x0080,	0x0000 }
	};

	wtw_set_def_aspm_entwy_watency(tp);

	WTW_W8(tp, DBG_WEG, 0x06 | FIX_NAK_1 | FIX_NAK_2);

	wtw_ephy_init(tp, e_info_8168c_1);

	__wtw_hw_stawt_8168cp(tp);
}

static void wtw_hw_stawt_8168c_2(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168c_2[] = {
		{ 0x01, 0,	0x0001 },
		{ 0x03, 0x0400,	0x0020 }
	};

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ephy_init(tp, e_info_8168c_2);

	__wtw_hw_stawt_8168cp(tp);
}

static void wtw_hw_stawt_8168c_4(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	__wtw_hw_stawt_8168cp(tp);
}

static void wtw_hw_stawt_8168d(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	wtw_disabwe_cwock_wequest(tp);
}

static void wtw_hw_stawt_8168d_4(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168d_4[] = {
		{ 0x0b, 0x0000,	0x0048 },
		{ 0x19, 0x0020,	0x0050 },
		{ 0x0c, 0x0100,	0x0020 },
		{ 0x10, 0x0004,	0x0000 },
	};

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ephy_init(tp, e_info_8168d_4);

	wtw_enabwe_cwock_wequest(tp);
}

static void wtw_hw_stawt_8168e_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168e_1[] = {
		{ 0x00, 0x0200,	0x0100 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x06, 0x0002,	0x0001 },
		{ 0x06, 0x0000,	0x0030 },
		{ 0x07, 0x0000,	0x2000 },
		{ 0x00, 0x0000,	0x0020 },
		{ 0x03, 0x5800,	0x2000 },
		{ 0x03, 0x0000,	0x0001 },
		{ 0x01, 0x0800,	0x1000 },
		{ 0x07, 0x0000,	0x4000 },
		{ 0x1e, 0x0000,	0x2000 },
		{ 0x19, 0xffff,	0xfe6c },
		{ 0x0a, 0x0000,	0x0040 }
	};

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ephy_init(tp, e_info_8168e_1);

	wtw_disabwe_cwock_wequest(tp);

	/* Weset tx FIFO pointew */
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) | TXPWA_WST);
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) & ~TXPWA_WST);

	wtw_mod_config5(tp, Spi_en, 0);
}

static void wtw_hw_stawt_8168e_2(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168e_2[] = {
		{ 0x09, 0x0000,	0x0080 },
		{ 0x19, 0x0000,	0x0224 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x0c, 0x3df0,	0x0200 },
	};

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ephy_init(tp, e_info_8168e_2);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_1111, 0x0000);
	wtw_set_fifo_size(tp, 0x10, 0x10, 0x02, 0x06);
	wtw_ewi_set_bits(tp, 0x1d0, BIT(1));
	wtw_weset_packet_fiwtew(tp);
	wtw_ewi_set_bits(tp, 0x1b0, BIT(4));
	wtw_ewi_wwite(tp, 0xcc, EWIAW_MASK_1111, 0x00000050);
	wtw_ewi_wwite(tp, 0xd0, EWIAW_MASK_1111, 0x07ff0060);

	wtw_disabwe_cwock_wequest(tp);

	WTW_W8(tp, MCU, WTW_W8(tp, MCU) & ~NOW_IS_OOB);

	wtw8168_config_eee_mac(tp);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) | PFM_EN);
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) | PWM_EN);
	wtw_mod_config5(tp, Spi_en, 0);
}

static void wtw_hw_stawt_8168f(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_1111, 0x0000);
	wtw_set_fifo_size(tp, 0x10, 0x10, 0x02, 0x06);
	wtw_weset_packet_fiwtew(tp);
	wtw_ewi_set_bits(tp, 0x1b0, BIT(4));
	wtw_ewi_set_bits(tp, 0x1d0, BIT(4) | BIT(1));
	wtw_ewi_wwite(tp, 0xcc, EWIAW_MASK_1111, 0x00000050);
	wtw_ewi_wwite(tp, 0xd0, EWIAW_MASK_1111, 0x00000060);

	wtw_disabwe_cwock_wequest(tp);

	WTW_W8(tp, MCU, WTW_W8(tp, MCU) & ~NOW_IS_OOB);
	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) | PFM_EN);
	WTW_W32(tp, MISC, WTW_W32(tp, MISC) | PWM_EN);
	wtw_mod_config5(tp, Spi_en, 0);

	wtw8168_config_eee_mac(tp);
}

static void wtw_hw_stawt_8168f_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168f_1[] = {
		{ 0x06, 0x00c0,	0x0020 },
		{ 0x08, 0x0001,	0x0002 },
		{ 0x09, 0x0000,	0x0080 },
		{ 0x19, 0x0000,	0x0224 },
		{ 0x00, 0x0000,	0x0008 },
		{ 0x0c, 0x3df0,	0x0200 },
	};

	wtw_hw_stawt_8168f(tp);

	wtw_ephy_init(tp, e_info_8168f_1);
}

static void wtw_hw_stawt_8411(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168f_1[] = {
		{ 0x06, 0x00c0,	0x0020 },
		{ 0x0f, 0xffff,	0x5200 },
		{ 0x19, 0x0000,	0x0224 },
		{ 0x00, 0x0000,	0x0008 },
		{ 0x0c, 0x3df0,	0x0200 },
	};

	wtw_hw_stawt_8168f(tp);
	wtw_pcie_state_w2w3_disabwe(tp);

	wtw_ephy_init(tp, e_info_8168f_1);
}

static void wtw_hw_stawt_8168g(stwuct wtw8169_pwivate *tp)
{
	wtw_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	wtw8168g_set_pause_thweshowds(tp, 0x38, 0x48);

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_weset_packet_fiwtew(tp);
	wtw_ewi_wwite(tp, 0x2f8, EWIAW_MASK_0011, 0x1d8f);

	wtw_disabwe_wxdvgate(tp);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_0011, 0x0000);

	wtw8168_config_eee_mac(tp);

	wtw_w0w1_ewi(tp, 0x2fc, 0x01, 0x06);
	wtw_ewi_cweaw_bits(tp, 0x1b0, BIT(12));

	wtw_pcie_state_w2w3_disabwe(tp);
}

static void wtw_hw_stawt_8168g_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168g_1[] = {
		{ 0x00, 0x0008,	0x0000 },
		{ 0x0c, 0x3ff0,	0x0820 },
		{ 0x1e, 0x0000,	0x0001 },
		{ 0x19, 0x8000,	0x0000 }
	};

	wtw_hw_stawt_8168g(tp);
	wtw_ephy_init(tp, e_info_8168g_1);
}

static void wtw_hw_stawt_8168g_2(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168g_2[] = {
		{ 0x00, 0x0008,	0x0000 },
		{ 0x0c, 0x3ff0,	0x0820 },
		{ 0x19, 0xffff,	0x7c00 },
		{ 0x1e, 0xffff,	0x20eb },
		{ 0x0d, 0xffff,	0x1666 },
		{ 0x00, 0xffff,	0x10a3 },
		{ 0x06, 0xffff,	0xf050 },
		{ 0x04, 0x0000,	0x0010 },
		{ 0x1d, 0x4000,	0x0000 },
	};

	wtw_hw_stawt_8168g(tp);
	wtw_ephy_init(tp, e_info_8168g_2);
}

static void wtw8411b_fix_phy_down(stwuct wtw8169_pwivate *tp)
{
	static const u16 fix_data[] = {
/* 0xf800 */ 0xe008, 0xe00a, 0xe00c, 0xe00e, 0xe027, 0xe04f, 0xe05e, 0xe065,
/* 0xf810 */ 0xc602, 0xbe00, 0x0000, 0xc502, 0xbd00, 0x074c, 0xc302, 0xbb00,
/* 0xf820 */ 0x080a, 0x6420, 0x48c2, 0x8c20, 0xc516, 0x64a4, 0x49c0, 0xf009,
/* 0xf830 */ 0x74a2, 0x8ca5, 0x74a0, 0xc50e, 0x9ca2, 0x1c11, 0x9ca0, 0xe006,
/* 0xf840 */ 0x74f8, 0x48c4, 0x8cf8, 0xc404, 0xbc00, 0xc403, 0xbc00, 0x0bf2,
/* 0xf850 */ 0x0c0a, 0xe434, 0xd3c0, 0x49d9, 0xf01f, 0xc526, 0x64a5, 0x1400,
/* 0xf860 */ 0xf007, 0x0c01, 0x8ca5, 0x1c15, 0xc51b, 0x9ca0, 0xe013, 0xc519,
/* 0xf870 */ 0x74a0, 0x48c4, 0x8ca0, 0xc516, 0x74a4, 0x48c8, 0x48ca, 0x9ca4,
/* 0xf880 */ 0xc512, 0x1b00, 0x9ba0, 0x1b1c, 0x483f, 0x9ba2, 0x1b04, 0xc508,
/* 0xf890 */ 0x9ba0, 0xc505, 0xbd00, 0xc502, 0xbd00, 0x0300, 0x051e, 0xe434,
/* 0xf8a0 */ 0xe018, 0xe092, 0xde20, 0xd3c0, 0xc50f, 0x76a4, 0x49e3, 0xf007,
/* 0xf8b0 */ 0x49c0, 0xf103, 0xc607, 0xbe00, 0xc606, 0xbe00, 0xc602, 0xbe00,
/* 0xf8c0 */ 0x0c4c, 0x0c28, 0x0c2c, 0xdc00, 0xc707, 0x1d00, 0x8de2, 0x48c1,
/* 0xf8d0 */ 0xc502, 0xbd00, 0x00aa, 0xe0c0, 0xc502, 0xbd00, 0x0132
	};
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&tp->mac_ocp_wock, fwags);
	fow (i = 0; i < AWWAY_SIZE(fix_data); i++)
		__w8168_mac_ocp_wwite(tp, 0xf800 + 2 * i, fix_data[i]);
	waw_spin_unwock_iwqwestowe(&tp->mac_ocp_wock, fwags);
}

static void wtw_hw_stawt_8411_2(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8411_2[] = {
		{ 0x00, 0x0008,	0x0000 },
		{ 0x0c, 0x37d0,	0x0820 },
		{ 0x1e, 0x0000,	0x0001 },
		{ 0x19, 0x8021,	0x0000 },
		{ 0x1e, 0x0000,	0x2000 },
		{ 0x0d, 0x0100,	0x0200 },
		{ 0x00, 0x0000,	0x0080 },
		{ 0x06, 0x0000,	0x0010 },
		{ 0x04, 0x0000,	0x0010 },
		{ 0x1d, 0x0000,	0x4000 },
	};

	wtw_hw_stawt_8168g(tp);

	wtw_ephy_init(tp, e_info_8411_2);

	/* The fowwowing Weawtek-pwovided magic fixes an issue with the WX unit
	 * getting confused aftew the PHY having been powewed-down.
	 */
	w8168_mac_ocp_wwite(tp, 0xFC28, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC2A, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC2C, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC2E, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC30, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC32, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC34, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xFC36, 0x0000);
	mdeway(3);
	w8168_mac_ocp_wwite(tp, 0xFC26, 0x0000);

	wtw8411b_fix_phy_down(tp);

	w8168_mac_ocp_wwite(tp, 0xFC26, 0x8000);

	w8168_mac_ocp_wwite(tp, 0xFC2A, 0x0743);
	w8168_mac_ocp_wwite(tp, 0xFC2C, 0x0801);
	w8168_mac_ocp_wwite(tp, 0xFC2E, 0x0BE9);
	w8168_mac_ocp_wwite(tp, 0xFC30, 0x02FD);
	w8168_mac_ocp_wwite(tp, 0xFC32, 0x0C25);
	w8168_mac_ocp_wwite(tp, 0xFC34, 0x00A9);
	w8168_mac_ocp_wwite(tp, 0xFC36, 0x012D);
}

static void wtw_hw_stawt_8168h_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168h_1[] = {
		{ 0x1e, 0x0800,	0x0001 },
		{ 0x1d, 0x0000,	0x0800 },
		{ 0x05, 0xffff,	0x2089 },
		{ 0x06, 0xffff,	0x5881 },
		{ 0x04, 0xffff,	0x854a },
		{ 0x01, 0xffff,	0x068b }
	};
	int wg_saw_cnt;

	wtw_ephy_init(tp, e_info_8168h_1);

	wtw_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	wtw8168g_set_pause_thweshowds(tp, 0x38, 0x48);

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_weset_packet_fiwtew(tp);

	wtw_ewi_set_bits(tp, 0xdc, 0x001c);

	wtw_ewi_wwite(tp, 0x5f0, EWIAW_MASK_0011, 0x4f87);

	wtw_disabwe_wxdvgate(tp);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_0011, 0x0000);

	wtw8168_config_eee_mac(tp);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~PFM_EN);
	WTW_W8(tp, MISC_1, WTW_W8(tp, MISC_1) & ~PFM_D3COWD_EN);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~TX_10M_PS_EN);

	wtw_ewi_cweaw_bits(tp, 0x1b0, BIT(12));

	wtw_pcie_state_w2w3_disabwe(tp);

	wg_saw_cnt = phy_wead_paged(tp->phydev, 0x0c42, 0x13) & 0x3fff;
	if (wg_saw_cnt > 0) {
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = 16000000/wg_saw_cnt;
		sw_cnt_1ms_ini &= 0x0fff;
		w8168_mac_ocp_modify(tp, 0xd412, 0x0fff, sw_cnt_1ms_ini);
	}

	w8168_mac_ocp_modify(tp, 0xe056, 0x00f0, 0x0070);
	w8168_mac_ocp_modify(tp, 0xe052, 0x6000, 0x8008);
	w8168_mac_ocp_modify(tp, 0xe0d6, 0x01ff, 0x017f);
	w8168_mac_ocp_modify(tp, 0xd420, 0x0fff, 0x047f);

	w8168_mac_ocp_wwite(tp, 0xe63e, 0x0001);
	w8168_mac_ocp_wwite(tp, 0xe63e, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xc094, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xc09e, 0x0000);
}

static void wtw_hw_stawt_8168ep(stwuct wtw8169_pwivate *tp)
{
	wtw8168ep_stop_cmac(tp);

	wtw_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	wtw8168g_set_pause_thweshowds(tp, 0x2f, 0x5f);

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_weset_packet_fiwtew(tp);

	wtw_ewi_wwite(tp, 0x5f0, EWIAW_MASK_0011, 0x4f87);

	wtw_disabwe_wxdvgate(tp);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_0011, 0x0000);

	wtw8168_config_eee_mac(tp);

	wtw_w0w1_ewi(tp, 0x2fc, 0x01, 0x06);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~TX_10M_PS_EN);

	wtw_pcie_state_w2w3_disabwe(tp);
}

static void wtw_hw_stawt_8168ep_3(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8168ep_3[] = {
		{ 0x00, 0x0000,	0x0080 },
		{ 0x0d, 0x0100,	0x0200 },
		{ 0x19, 0x8021,	0x0000 },
		{ 0x1e, 0x0000,	0x2000 },
	};

	wtw_ephy_init(tp, e_info_8168ep_3);

	wtw_hw_stawt_8168ep(tp);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~PFM_EN);
	WTW_W8(tp, MISC_1, WTW_W8(tp, MISC_1) & ~PFM_D3COWD_EN);

	w8168_mac_ocp_modify(tp, 0xd3e2, 0x0fff, 0x0271);
	w8168_mac_ocp_modify(tp, 0xd3e4, 0x00ff, 0x0000);
	w8168_mac_ocp_modify(tp, 0xe860, 0x0000, 0x0080);
}

static void wtw_hw_stawt_8117(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8117[] = {
		{ 0x19, 0x0040,	0x1100 },
		{ 0x59, 0x0040,	0x1100 },
	};
	int wg_saw_cnt;

	wtw8168ep_stop_cmac(tp);
	wtw_ephy_init(tp, e_info_8117);

	wtw_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	wtw8168g_set_pause_thweshowds(tp, 0x2f, 0x5f);

	wtw_set_def_aspm_entwy_watency(tp);

	wtw_weset_packet_fiwtew(tp);

	wtw_ewi_set_bits(tp, 0xd4, 0x0010);

	wtw_ewi_wwite(tp, 0x5f0, EWIAW_MASK_0011, 0x4f87);

	wtw_disabwe_wxdvgate(tp);

	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_0011, 0x0000);

	wtw8168_config_eee_mac(tp);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~PFM_EN);
	WTW_W8(tp, MISC_1, WTW_W8(tp, MISC_1) & ~PFM_D3COWD_EN);

	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~TX_10M_PS_EN);

	wtw_ewi_cweaw_bits(tp, 0x1b0, BIT(12));

	wtw_pcie_state_w2w3_disabwe(tp);

	wg_saw_cnt = phy_wead_paged(tp->phydev, 0x0c42, 0x13) & 0x3fff;
	if (wg_saw_cnt > 0) {
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = (16000000 / wg_saw_cnt) & 0x0fff;
		w8168_mac_ocp_modify(tp, 0xd412, 0x0fff, sw_cnt_1ms_ini);
	}

	w8168_mac_ocp_modify(tp, 0xe056, 0x00f0, 0x0070);
	w8168_mac_ocp_wwite(tp, 0xea80, 0x0003);
	w8168_mac_ocp_modify(tp, 0xe052, 0x0000, 0x0009);
	w8168_mac_ocp_modify(tp, 0xd420, 0x0fff, 0x047f);

	w8168_mac_ocp_wwite(tp, 0xe63e, 0x0001);
	w8168_mac_ocp_wwite(tp, 0xe63e, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xc094, 0x0000);
	w8168_mac_ocp_wwite(tp, 0xc09e, 0x0000);

	/* fiwmwawe is fow MAC onwy */
	w8169_appwy_fiwmwawe(tp);
}

static void wtw_hw_stawt_8102e_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8102e_1[] = {
		{ 0x01,	0, 0x6e65 },
		{ 0x02,	0, 0x091f },
		{ 0x03,	0, 0xc2f9 },
		{ 0x06,	0, 0xafb5 },
		{ 0x07,	0, 0x0e00 },
		{ 0x19,	0, 0xec80 },
		{ 0x01,	0, 0x2e65 },
		{ 0x01,	0, 0x6e65 }
	};
	u8 cfg1;

	wtw_set_def_aspm_entwy_watency(tp);

	WTW_W8(tp, DBG_WEG, FIX_NAK_1);

	WTW_W8(tp, Config1,
	       WEDS1 | WEDS0 | Speed_down | MEMMAP | IOMAP | VPD | PMEnabwe);
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);

	cfg1 = WTW_W8(tp, Config1);
	if ((cfg1 & WEDS0) && (cfg1 & WEDS1))
		WTW_W8(tp, Config1, cfg1 & ~WEDS0);

	wtw_ephy_init(tp, e_info_8102e_1);
}

static void wtw_hw_stawt_8102e_2(stwuct wtw8169_pwivate *tp)
{
	wtw_set_def_aspm_entwy_watency(tp);

	WTW_W8(tp, Config1, MEMMAP | IOMAP | VPD | PMEnabwe);
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);
}

static void wtw_hw_stawt_8102e_3(stwuct wtw8169_pwivate *tp)
{
	wtw_hw_stawt_8102e_2(tp);

	wtw_ephy_wwite(tp, 0x03, 0xc2f9);
}

static void wtw_hw_stawt_8401(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8401[] = {
		{ 0x01,	0xffff, 0x6fe5 },
		{ 0x03,	0xffff, 0x0599 },
		{ 0x06,	0xffff, 0xaf25 },
		{ 0x07,	0xffff, 0x8e68 },
	};

	wtw_ephy_init(tp, e_info_8401);
	WTW_W8(tp, Config3, WTW_W8(tp, Config3) & ~Beacon_en);
}

static void wtw_hw_stawt_8105e_1(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8105e_1[] = {
		{ 0x07,	0, 0x4000 },
		{ 0x19,	0, 0x0200 },
		{ 0x19,	0, 0x0020 },
		{ 0x1e,	0, 0x2000 },
		{ 0x03,	0, 0x0001 },
		{ 0x19,	0, 0x0100 },
		{ 0x19,	0, 0x0004 },
		{ 0x0a,	0, 0x0020 }
	};

	/* Fowce WAN exit fwom ASPM if Wx/Tx awe not idwe */
	WTW_W32(tp, FuncEvent, WTW_W32(tp, FuncEvent) | 0x002800);

	/* Disabwe Eawwy Tawwy Countew */
	WTW_W32(tp, FuncEvent, WTW_W32(tp, FuncEvent) & ~0x010000);

	WTW_W8(tp, MCU, WTW_W8(tp, MCU) | EN_NDP | EN_OOB_WESET);
	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) | PFM_EN);

	wtw_ephy_init(tp, e_info_8105e_1);

	wtw_pcie_state_w2w3_disabwe(tp);
}

static void wtw_hw_stawt_8105e_2(stwuct wtw8169_pwivate *tp)
{
	wtw_hw_stawt_8105e_1(tp);
	wtw_ephy_wwite(tp, 0x1e, wtw_ephy_wead(tp, 0x1e) | 0x8000);
}

static void wtw_hw_stawt_8402(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8402[] = {
		{ 0x19,	0xffff, 0xff64 },
		{ 0x1e,	0, 0x4000 }
	};

	wtw_set_def_aspm_entwy_watency(tp);

	/* Fowce WAN exit fwom ASPM if Wx/Tx awe not idwe */
	WTW_W32(tp, FuncEvent, WTW_W32(tp, FuncEvent) | 0x002800);

	WTW_W8(tp, MCU, WTW_W8(tp, MCU) & ~NOW_IS_OOB);

	wtw_ephy_init(tp, e_info_8402);

	wtw_set_fifo_size(tp, 0x00, 0x00, 0x02, 0x06);
	wtw_weset_packet_fiwtew(tp);
	wtw_ewi_wwite(tp, 0xc0, EWIAW_MASK_0011, 0x0000);
	wtw_ewi_wwite(tp, 0xb8, EWIAW_MASK_0011, 0x0000);
	wtw_w0w1_ewi(tp, 0x0d4, 0x0e00, 0xff00);

	/* disabwe EEE */
	wtw_ewi_wwite(tp, 0x1b0, EWIAW_MASK_0011, 0x0000);

	wtw_pcie_state_w2w3_disabwe(tp);
}

static void wtw_hw_stawt_8106(stwuct wtw8169_pwivate *tp)
{
	/* Fowce WAN exit fwom ASPM if Wx/Tx awe not idwe */
	WTW_W32(tp, FuncEvent, WTW_W32(tp, FuncEvent) | 0x002800);

	WTW_W32(tp, MISC, (WTW_W32(tp, MISC) | DISABWE_WAN_EN) & ~EAWWY_TAWWY_EN);
	WTW_W8(tp, MCU, WTW_W8(tp, MCU) | EN_NDP | EN_OOB_WESET);
	WTW_W8(tp, DWWPW, WTW_W8(tp, DWWPW) & ~PFM_EN);

	/* W0 7us, W1 32us - needed to avoid issues with wink-up detection */
	wtw_set_aspm_entwy_watency(tp, 0x2f);

	wtw_ewi_wwite(tp, 0x1d0, EWIAW_MASK_0011, 0x0000);

	/* disabwe EEE */
	wtw_ewi_wwite(tp, 0x1b0, EWIAW_MASK_0011, 0x0000);

	wtw_pcie_state_w2w3_disabwe(tp);
}

DECWAWE_WTW_COND(wtw_mac_ocp_e00e_cond)
{
	wetuwn w8168_mac_ocp_wead(tp, 0xe00e) & BIT(13);
}

static void wtw_hw_stawt_8125_common(stwuct wtw8169_pwivate *tp)
{
	wtw_pcie_state_w2w3_disabwe(tp);

	WTW_W16(tp, 0x382, 0x221b);
	WTW_W8(tp, 0x4500, 0);
	WTW_W16(tp, 0x4800, 0);

	/* disabwe UPS */
	w8168_mac_ocp_modify(tp, 0xd40a, 0x0010, 0x0000);

	WTW_W8(tp, Config1, WTW_W8(tp, Config1) & ~0x10);

	w8168_mac_ocp_wwite(tp, 0xc140, 0xffff);
	w8168_mac_ocp_wwite(tp, 0xc142, 0xffff);

	w8168_mac_ocp_modify(tp, 0xd3e2, 0x0fff, 0x03a9);
	w8168_mac_ocp_modify(tp, 0xd3e4, 0x00ff, 0x0000);
	w8168_mac_ocp_modify(tp, 0xe860, 0x0000, 0x0080);

	/* disabwe new tx descwiptow fowmat */
	w8168_mac_ocp_modify(tp, 0xeb58, 0x0001, 0x0000);

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_63)
		w8168_mac_ocp_modify(tp, 0xe614, 0x0700, 0x0200);
	ewse
		w8168_mac_ocp_modify(tp, 0xe614, 0x0700, 0x0400);

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_63)
		w8168_mac_ocp_modify(tp, 0xe63e, 0x0c30, 0x0000);
	ewse
		w8168_mac_ocp_modify(tp, 0xe63e, 0x0c30, 0x0020);

	w8168_mac_ocp_modify(tp, 0xc0b4, 0x0000, 0x000c);
	w8168_mac_ocp_modify(tp, 0xeb6a, 0x00ff, 0x0033);
	w8168_mac_ocp_modify(tp, 0xeb50, 0x03e0, 0x0040);
	w8168_mac_ocp_modify(tp, 0xe056, 0x00f0, 0x0030);
	w8168_mac_ocp_modify(tp, 0xe040, 0x1000, 0x0000);
	w8168_mac_ocp_modify(tp, 0xea1c, 0x0003, 0x0001);
	w8168_mac_ocp_modify(tp, 0xe0c0, 0x4f0f, 0x4403);
	w8168_mac_ocp_modify(tp, 0xe052, 0x0080, 0x0068);
	w8168_mac_ocp_modify(tp, 0xd430, 0x0fff, 0x047f);

	w8168_mac_ocp_modify(tp, 0xea1c, 0x0004, 0x0000);
	w8168_mac_ocp_modify(tp, 0xeb54, 0x0000, 0x0001);
	udeway(1);
	w8168_mac_ocp_modify(tp, 0xeb54, 0x0001, 0x0000);
	WTW_W16(tp, 0x1880, WTW_W16(tp, 0x1880) & ~0x0030);

	w8168_mac_ocp_wwite(tp, 0xe098, 0xc302);

	wtw_woop_wait_wow(tp, &wtw_mac_ocp_e00e_cond, 1000, 10);

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_63)
		wtw8125b_config_eee_mac(tp);
	ewse
		wtw8125a_config_eee_mac(tp);

	wtw_disabwe_wxdvgate(tp);
}

static void wtw_hw_stawt_8125a_2(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8125a_2[] = {
		{ 0x04, 0xffff, 0xd000 },
		{ 0x0a, 0xffff, 0x8653 },
		{ 0x23, 0xffff, 0xab66 },
		{ 0x20, 0xffff, 0x9455 },
		{ 0x21, 0xffff, 0x99ff },
		{ 0x29, 0xffff, 0xfe04 },

		{ 0x44, 0xffff, 0xd000 },
		{ 0x4a, 0xffff, 0x8653 },
		{ 0x63, 0xffff, 0xab66 },
		{ 0x60, 0xffff, 0x9455 },
		{ 0x61, 0xffff, 0x99ff },
		{ 0x69, 0xffff, 0xfe04 },
	};

	wtw_set_def_aspm_entwy_watency(tp);
	wtw_ephy_init(tp, e_info_8125a_2);
	wtw_hw_stawt_8125_common(tp);
}

static void wtw_hw_stawt_8125b(stwuct wtw8169_pwivate *tp)
{
	static const stwuct ephy_info e_info_8125b[] = {
		{ 0x0b, 0xffff, 0xa908 },
		{ 0x1e, 0xffff, 0x20eb },
		{ 0x4b, 0xffff, 0xa908 },
		{ 0x5e, 0xffff, 0x20eb },
		{ 0x22, 0x0030, 0x0020 },
		{ 0x62, 0x0030, 0x0020 },
	};

	wtw_set_def_aspm_entwy_watency(tp);
	wtw_ephy_init(tp, e_info_8125b);
	wtw_hw_stawt_8125_common(tp);
}

static void wtw_hw_config(stwuct wtw8169_pwivate *tp)
{
	static const wtw_genewic_fct hw_configs[] = {
		[WTW_GIGA_MAC_VEW_07] = wtw_hw_stawt_8102e_1,
		[WTW_GIGA_MAC_VEW_08] = wtw_hw_stawt_8102e_3,
		[WTW_GIGA_MAC_VEW_09] = wtw_hw_stawt_8102e_2,
		[WTW_GIGA_MAC_VEW_10] = NUWW,
		[WTW_GIGA_MAC_VEW_11] = wtw_hw_stawt_8168b,
		[WTW_GIGA_MAC_VEW_14] = wtw_hw_stawt_8401,
		[WTW_GIGA_MAC_VEW_17] = wtw_hw_stawt_8168b,
		[WTW_GIGA_MAC_VEW_18] = wtw_hw_stawt_8168cp_1,
		[WTW_GIGA_MAC_VEW_19] = wtw_hw_stawt_8168c_1,
		[WTW_GIGA_MAC_VEW_20] = wtw_hw_stawt_8168c_2,
		[WTW_GIGA_MAC_VEW_21] = wtw_hw_stawt_8168c_2,
		[WTW_GIGA_MAC_VEW_22] = wtw_hw_stawt_8168c_4,
		[WTW_GIGA_MAC_VEW_23] = wtw_hw_stawt_8168cp_2,
		[WTW_GIGA_MAC_VEW_24] = wtw_hw_stawt_8168cp_3,
		[WTW_GIGA_MAC_VEW_25] = wtw_hw_stawt_8168d,
		[WTW_GIGA_MAC_VEW_26] = wtw_hw_stawt_8168d,
		[WTW_GIGA_MAC_VEW_28] = wtw_hw_stawt_8168d_4,
		[WTW_GIGA_MAC_VEW_29] = wtw_hw_stawt_8105e_1,
		[WTW_GIGA_MAC_VEW_30] = wtw_hw_stawt_8105e_2,
		[WTW_GIGA_MAC_VEW_31] = wtw_hw_stawt_8168d,
		[WTW_GIGA_MAC_VEW_32] = wtw_hw_stawt_8168e_1,
		[WTW_GIGA_MAC_VEW_33] = wtw_hw_stawt_8168e_1,
		[WTW_GIGA_MAC_VEW_34] = wtw_hw_stawt_8168e_2,
		[WTW_GIGA_MAC_VEW_35] = wtw_hw_stawt_8168f_1,
		[WTW_GIGA_MAC_VEW_36] = wtw_hw_stawt_8168f_1,
		[WTW_GIGA_MAC_VEW_37] = wtw_hw_stawt_8402,
		[WTW_GIGA_MAC_VEW_38] = wtw_hw_stawt_8411,
		[WTW_GIGA_MAC_VEW_39] = wtw_hw_stawt_8106,
		[WTW_GIGA_MAC_VEW_40] = wtw_hw_stawt_8168g_1,
		[WTW_GIGA_MAC_VEW_42] = wtw_hw_stawt_8168g_2,
		[WTW_GIGA_MAC_VEW_43] = wtw_hw_stawt_8168g_2,
		[WTW_GIGA_MAC_VEW_44] = wtw_hw_stawt_8411_2,
		[WTW_GIGA_MAC_VEW_46] = wtw_hw_stawt_8168h_1,
		[WTW_GIGA_MAC_VEW_48] = wtw_hw_stawt_8168h_1,
		[WTW_GIGA_MAC_VEW_51] = wtw_hw_stawt_8168ep_3,
		[WTW_GIGA_MAC_VEW_52] = wtw_hw_stawt_8117,
		[WTW_GIGA_MAC_VEW_53] = wtw_hw_stawt_8117,
		[WTW_GIGA_MAC_VEW_61] = wtw_hw_stawt_8125a_2,
		[WTW_GIGA_MAC_VEW_63] = wtw_hw_stawt_8125b,
	};

	if (hw_configs[tp->mac_vewsion])
		hw_configs[tp->mac_vewsion](tp);
}

static void wtw_hw_stawt_8125(stwuct wtw8169_pwivate *tp)
{
	int i;

	/* disabwe intewwupt coawescing */
	fow (i = 0xa00; i < 0xb00; i += 4)
		WTW_W32(tp, i, 0);

	wtw_hw_config(tp);
}

static void wtw_hw_stawt_8168(stwuct wtw8169_pwivate *tp)
{
	if (wtw_is_8168evw_up(tp))
		WTW_W8(tp, MaxTxPacketSize, EawwySize);
	ewse
		WTW_W8(tp, MaxTxPacketSize, TxPacketMax);

	wtw_hw_config(tp);

	/* disabwe intewwupt coawescing */
	WTW_W16(tp, IntwMitigate, 0x0000);
}

static void wtw_hw_stawt_8169(stwuct wtw8169_pwivate *tp)
{
	WTW_W8(tp, EawwyTxThwes, NoEawwyTx);

	tp->cp_cmd |= PCIMuwWW;

	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_02 ||
	    tp->mac_vewsion == WTW_GIGA_MAC_VEW_03)
		tp->cp_cmd |= EnAnaPWW;

	WTW_W16(tp, CPwusCmd, tp->cp_cmd);

	wtw8169_set_magic_weg(tp);

	/* disabwe intewwupt coawescing */
	WTW_W16(tp, IntwMitigate, 0x0000);
}

static void wtw_hw_stawt(stwuct  wtw8169_pwivate *tp)
{
	wtw_unwock_config_wegs(tp);
	/* disabwe aspm and cwock wequest befowe ephy access */
	wtw_hw_aspm_cwkweq_enabwe(tp, fawse);
	WTW_W16(tp, CPwusCmd, tp->cp_cmd);

	if (tp->mac_vewsion <= WTW_GIGA_MAC_VEW_06)
		wtw_hw_stawt_8169(tp);
	ewse if (wtw_is_8125(tp))
		wtw_hw_stawt_8125(tp);
	ewse
		wtw_hw_stawt_8168(tp);

	wtw_enabwe_exit_w1(tp);
	wtw_hw_aspm_cwkweq_enabwe(tp, twue);
	wtw_set_wx_max_size(tp);
	wtw_set_wx_tx_desc_wegistews(tp);
	wtw_wock_config_wegs(tp);

	wtw_jumbo_config(tp);

	/* Initiawwy a 10 us deway. Tuwned it into a PCI commit. - FW */
	wtw_pci_commit(tp);

	WTW_W8(tp, ChipCmd, CmdTxEnb | CmdWxEnb);
	wtw_init_wxcfg(tp);
	wtw_set_tx_config_wegistews(tp);
	wtw_set_wx_config_featuwes(tp, tp->dev->featuwes);
	wtw_set_wx_mode(tp->dev);
	wtw_iwq_enabwe(tp);
}

static int wtw8169_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	dev->mtu = new_mtu;
	netdev_update_featuwes(dev);
	wtw_jumbo_config(tp);

	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_61:
	case WTW_GIGA_MAC_VEW_63:
		wtw8125_set_eee_txidwe_timew(tp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void wtw8169_mawk_to_asic(stwuct WxDesc *desc)
{
	u32 eow = we32_to_cpu(desc->opts1) & WingEnd;

	desc->opts2 = 0;
	/* Fowce memowy wwites to compwete befowe weweasing descwiptow */
	dma_wmb();
	WWITE_ONCE(desc->opts1, cpu_to_we32(DescOwn | eow | W8169_WX_BUF_SIZE));
}

static stwuct page *wtw8169_awwoc_wx_data(stwuct wtw8169_pwivate *tp,
					  stwuct WxDesc *desc)
{
	stwuct device *d = tp_to_dev(tp);
	int node = dev_to_node(d);
	dma_addw_t mapping;
	stwuct page *data;

	data = awwoc_pages_node(node, GFP_KEWNEW, get_owdew(W8169_WX_BUF_SIZE));
	if (!data)
		wetuwn NUWW;

	mapping = dma_map_page(d, data, 0, W8169_WX_BUF_SIZE, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(d, mapping))) {
		netdev_eww(tp->dev, "Faiwed to map WX DMA!\n");
		__fwee_pages(data, get_owdew(W8169_WX_BUF_SIZE));
		wetuwn NUWW;
	}

	desc->addw = cpu_to_we64(mapping);
	wtw8169_mawk_to_asic(desc);

	wetuwn data;
}

static void wtw8169_wx_cweaw(stwuct wtw8169_pwivate *tp)
{
	int i;

	fow (i = 0; i < NUM_WX_DESC && tp->Wx_databuff[i]; i++) {
		dma_unmap_page(tp_to_dev(tp),
			       we64_to_cpu(tp->WxDescAwway[i].addw),
			       W8169_WX_BUF_SIZE, DMA_FWOM_DEVICE);
		__fwee_pages(tp->Wx_databuff[i], get_owdew(W8169_WX_BUF_SIZE));
		tp->Wx_databuff[i] = NUWW;
		tp->WxDescAwway[i].addw = 0;
		tp->WxDescAwway[i].opts1 = 0;
	}
}

static int wtw8169_wx_fiww(stwuct wtw8169_pwivate *tp)
{
	int i;

	fow (i = 0; i < NUM_WX_DESC; i++) {
		stwuct page *data;

		data = wtw8169_awwoc_wx_data(tp, tp->WxDescAwway + i);
		if (!data) {
			wtw8169_wx_cweaw(tp);
			wetuwn -ENOMEM;
		}
		tp->Wx_databuff[i] = data;
	}

	/* mawk as wast descwiptow in the wing */
	tp->WxDescAwway[NUM_WX_DESC - 1].opts1 |= cpu_to_we32(WingEnd);

	wetuwn 0;
}

static int wtw8169_init_wing(stwuct wtw8169_pwivate *tp)
{
	wtw8169_init_wing_indexes(tp);

	memset(tp->tx_skb, 0, sizeof(tp->tx_skb));
	memset(tp->Wx_databuff, 0, sizeof(tp->Wx_databuff));

	wetuwn wtw8169_wx_fiww(tp);
}

static void wtw8169_unmap_tx_skb(stwuct wtw8169_pwivate *tp, unsigned int entwy)
{
	stwuct wing_info *tx_skb = tp->tx_skb + entwy;
	stwuct TxDesc *desc = tp->TxDescAwway + entwy;

	dma_unmap_singwe(tp_to_dev(tp), we64_to_cpu(desc->addw), tx_skb->wen,
			 DMA_TO_DEVICE);
	memset(desc, 0, sizeof(*desc));
	memset(tx_skb, 0, sizeof(*tx_skb));
}

static void wtw8169_tx_cweaw_wange(stwuct wtw8169_pwivate *tp, u32 stawt,
				   unsigned int n)
{
	unsigned int i;

	fow (i = 0; i < n; i++) {
		unsigned int entwy = (stawt + i) % NUM_TX_DESC;
		stwuct wing_info *tx_skb = tp->tx_skb + entwy;
		unsigned int wen = tx_skb->wen;

		if (wen) {
			stwuct sk_buff *skb = tx_skb->skb;

			wtw8169_unmap_tx_skb(tp, entwy);
			if (skb)
				dev_consume_skb_any(skb);
		}
	}
}

static void wtw8169_tx_cweaw(stwuct wtw8169_pwivate *tp)
{
	wtw8169_tx_cweaw_wange(tp, tp->diwty_tx, NUM_TX_DESC);
	netdev_weset_queue(tp->dev);
}

static void wtw8169_cweanup(stwuct wtw8169_pwivate *tp)
{
	napi_disabwe(&tp->napi);

	/* Give a wacing hawd_stawt_xmit a few cycwes to compwete. */
	synchwonize_net();

	/* Disabwe intewwupts */
	wtw8169_iwq_mask_and_ack(tp);

	wtw_wx_cwose(tp);

	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_28:
	case WTW_GIGA_MAC_VEW_31:
		wtw_woop_wait_wow(tp, &wtw_npq_cond, 20, 2000);
		bweak;
	case WTW_GIGA_MAC_VEW_34 ... WTW_GIGA_MAC_VEW_38:
		WTW_W8(tp, ChipCmd, WTW_W8(tp, ChipCmd) | StopWeq);
		wtw_woop_wait_high(tp, &wtw_txcfg_empty_cond, 100, 666);
		bweak;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_63:
		wtw_enabwe_wxdvgate(tp);
		fsweep(2000);
		bweak;
	defauwt:
		WTW_W8(tp, ChipCmd, WTW_W8(tp, ChipCmd) | StopWeq);
		fsweep(100);
		bweak;
	}

	wtw_hw_weset(tp);

	wtw8169_tx_cweaw(tp);
	wtw8169_init_wing_indexes(tp);
}

static void wtw_weset_wowk(stwuct wtw8169_pwivate *tp)
{
	int i;

	netif_stop_queue(tp->dev);

	wtw8169_cweanup(tp);

	fow (i = 0; i < NUM_WX_DESC; i++)
		wtw8169_mawk_to_asic(tp->WxDescAwway + i);

	napi_enabwe(&tp->napi);
	wtw_hw_stawt(tp);
}

static void wtw8169_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	wtw_scheduwe_task(tp, WTW_FWAG_TASK_TX_TIMEOUT);
}

static int wtw8169_tx_map(stwuct wtw8169_pwivate *tp, const u32 *opts, u32 wen,
			  void *addw, unsigned int entwy, boow desc_own)
{
	stwuct TxDesc *txd = tp->TxDescAwway + entwy;
	stwuct device *d = tp_to_dev(tp);
	dma_addw_t mapping;
	u32 opts1;
	int wet;

	mapping = dma_map_singwe(d, addw, wen, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(d, mapping);
	if (unwikewy(wet)) {
		if (net_watewimit())
			netdev_eww(tp->dev, "Faiwed to map TX data!\n");
		wetuwn wet;
	}

	txd->addw = cpu_to_we64(mapping);
	txd->opts2 = cpu_to_we32(opts[1]);

	opts1 = opts[0] | wen;
	if (entwy == NUM_TX_DESC - 1)
		opts1 |= WingEnd;
	if (desc_own)
		opts1 |= DescOwn;
	txd->opts1 = cpu_to_we32(opts1);

	tp->tx_skb[entwy].wen = wen;

	wetuwn 0;
}

static int wtw8169_xmit_fwags(stwuct wtw8169_pwivate *tp, stwuct sk_buff *skb,
			      const u32 *opts, unsigned int entwy)
{
	stwuct skb_shawed_info *info = skb_shinfo(skb);
	unsigned int cuw_fwag;

	fow (cuw_fwag = 0; cuw_fwag < info->nw_fwags; cuw_fwag++) {
		const skb_fwag_t *fwag = info->fwags + cuw_fwag;
		void *addw = skb_fwag_addwess(fwag);
		u32 wen = skb_fwag_size(fwag);

		entwy = (entwy + 1) % NUM_TX_DESC;

		if (unwikewy(wtw8169_tx_map(tp, opts, wen, addw, entwy, twue)))
			goto eww_out;
	}

	wetuwn 0;

eww_out:
	wtw8169_tx_cweaw_wange(tp, tp->cuw_tx + 1, cuw_fwag);
	wetuwn -EIO;
}

static boow wtw_skb_is_udp(stwuct sk_buff *skb)
{
	int no = skb_netwowk_offset(skb);
	stwuct ipv6hdw *i6h, _i6h;
	stwuct iphdw *ih, _ih;

	switch (vwan_get_pwotocow(skb)) {
	case htons(ETH_P_IP):
		ih = skb_headew_pointew(skb, no, sizeof(_ih), &_ih);
		wetuwn ih && ih->pwotocow == IPPWOTO_UDP;
	case htons(ETH_P_IPV6):
		i6h = skb_headew_pointew(skb, no, sizeof(_i6h), &_i6h);
		wetuwn i6h && i6h->nexthdw == IPPWOTO_UDP;
	defauwt:
		wetuwn fawse;
	}
}

#define WTW_MIN_PATCH_WEN	47

/* see wtw8125_get_patch_pad_wen() in w8125 vendow dwivew */
static unsigned int wtw8125_quiwk_udp_padto(stwuct wtw8169_pwivate *tp,
					    stwuct sk_buff *skb)
{
	unsigned int padto = 0, wen = skb->wen;

	if (wtw_is_8125(tp) && wen < 128 + WTW_MIN_PATCH_WEN &&
	    wtw_skb_is_udp(skb) && skb_twanspowt_headew_was_set(skb)) {
		unsigned int twans_data_wen = skb_taiw_pointew(skb) -
					      skb_twanspowt_headew(skb);

		if (twans_data_wen >= offsetof(stwuct udphdw, wen) &&
		    twans_data_wen < WTW_MIN_PATCH_WEN) {
			u16 dest = ntohs(udp_hdw(skb)->dest);

			/* dest is a standawd PTP powt */
			if (dest == 319 || dest == 320)
				padto = wen + WTW_MIN_PATCH_WEN - twans_data_wen;
		}

		if (twans_data_wen < sizeof(stwuct udphdw))
			padto = max_t(unsigned int, padto,
				      wen + sizeof(stwuct udphdw) - twans_data_wen);
	}

	wetuwn padto;
}

static unsigned int wtw_quiwk_packet_padto(stwuct wtw8169_pwivate *tp,
					   stwuct sk_buff *skb)
{
	unsigned int padto;

	padto = wtw8125_quiwk_udp_padto(tp, skb);

	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_34:
	case WTW_GIGA_MAC_VEW_61:
	case WTW_GIGA_MAC_VEW_63:
		padto = max_t(unsigned int, padto, ETH_ZWEN);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn padto;
}

static void wtw8169_tso_csum_v1(stwuct sk_buff *skb, u32 *opts)
{
	u32 mss = skb_shinfo(skb)->gso_size;

	if (mss) {
		opts[0] |= TD_WSO;
		opts[0] |= mss << TD0_MSS_SHIFT;
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		const stwuct iphdw *ip = ip_hdw(skb);

		if (ip->pwotocow == IPPWOTO_TCP)
			opts[0] |= TD0_IP_CS | TD0_TCP_CS;
		ewse if (ip->pwotocow == IPPWOTO_UDP)
			opts[0] |= TD0_IP_CS | TD0_UDP_CS;
		ewse
			WAWN_ON_ONCE(1);
	}
}

static boow wtw8169_tso_csum_v2(stwuct wtw8169_pwivate *tp,
				stwuct sk_buff *skb, u32 *opts)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	u32 mss = shinfo->gso_size;

	if (mss) {
		if (shinfo->gso_type & SKB_GSO_TCPV4) {
			opts[0] |= TD1_GTSENV4;
		} ewse if (shinfo->gso_type & SKB_GSO_TCPV6) {
			if (skb_cow_head(skb, 0))
				wetuwn fawse;

			tcp_v6_gso_csum_pwep(skb);
			opts[0] |= TD1_GTSENV6;
		} ewse {
			WAWN_ON_ONCE(1);
		}

		opts[0] |= skb_twanspowt_offset(skb) << GTTCPHO_SHIFT;
		opts[1] |= mss << TD1_MSS_SHIFT;
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		u8 ip_pwotocow;

		switch (vwan_get_pwotocow(skb)) {
		case htons(ETH_P_IP):
			opts[1] |= TD1_IPv4_CS;
			ip_pwotocow = ip_hdw(skb)->pwotocow;
			bweak;

		case htons(ETH_P_IPV6):
			opts[1] |= TD1_IPv6_CS;
			ip_pwotocow = ipv6_hdw(skb)->nexthdw;
			bweak;

		defauwt:
			ip_pwotocow = IPPWOTO_WAW;
			bweak;
		}

		if (ip_pwotocow == IPPWOTO_TCP)
			opts[1] |= TD1_TCP_CS;
		ewse if (ip_pwotocow == IPPWOTO_UDP)
			opts[1] |= TD1_UDP_CS;
		ewse
			WAWN_ON_ONCE(1);

		opts[1] |= skb_twanspowt_offset(skb) << TCPHO_SHIFT;
	} ewse {
		unsigned int padto = wtw_quiwk_packet_padto(tp, skb);

		/* skb_padto wouwd fwee the skb on ewwow */
		wetuwn !__skb_put_padto(skb, padto, fawse);
	}

	wetuwn twue;
}

static unsigned int wtw_tx_swots_avaiw(stwuct wtw8169_pwivate *tp)
{
	wetuwn WEAD_ONCE(tp->diwty_tx) + NUM_TX_DESC - WEAD_ONCE(tp->cuw_tx);
}

/* Vewsions WTW8102e and fwom WTW8168c onwawds suppowt csum_v2 */
static boow wtw_chip_suppowts_csum_v2(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_02 ... WTW_GIGA_MAC_VEW_06:
	case WTW_GIGA_MAC_VEW_10 ... WTW_GIGA_MAC_VEW_17:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static void wtw8169_doowbeww(stwuct wtw8169_pwivate *tp)
{
	if (wtw_is_8125(tp))
		WTW_W16(tp, TxPoww_8125, BIT(0));
	ewse
		WTW_W8(tp, TxPoww, NPQ);
}

static netdev_tx_t wtw8169_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	unsigned int fwags = skb_shinfo(skb)->nw_fwags;
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	unsigned int entwy = tp->cuw_tx % NUM_TX_DESC;
	stwuct TxDesc *txd_fiwst, *txd_wast;
	boow stop_queue, doow_beww;
	u32 opts[2];

	if (unwikewy(!wtw_tx_swots_avaiw(tp))) {
		if (net_watewimit())
			netdev_eww(dev, "BUG! Tx Wing fuww when queue awake!\n");
		goto eww_stop_0;
	}

	opts[1] = wtw8169_tx_vwan_tag(skb);
	opts[0] = 0;

	if (!wtw_chip_suppowts_csum_v2(tp))
		wtw8169_tso_csum_v1(skb, opts);
	ewse if (!wtw8169_tso_csum_v2(tp, skb, opts))
		goto eww_dma_0;

	if (unwikewy(wtw8169_tx_map(tp, opts, skb_headwen(skb), skb->data,
				    entwy, fawse)))
		goto eww_dma_0;

	txd_fiwst = tp->TxDescAwway + entwy;

	if (fwags) {
		if (wtw8169_xmit_fwags(tp, skb, opts, entwy))
			goto eww_dma_1;
		entwy = (entwy + fwags) % NUM_TX_DESC;
	}

	txd_wast = tp->TxDescAwway + entwy;
	txd_wast->opts1 |= cpu_to_we32(WastFwag);
	tp->tx_skb[entwy].skb = skb;

	skb_tx_timestamp(skb);

	/* Fowce memowy wwites to compwete befowe weweasing descwiptow */
	dma_wmb();

	doow_beww = __netdev_sent_queue(dev, skb->wen, netdev_xmit_mowe());

	txd_fiwst->opts1 |= cpu_to_we32(DescOwn | FiwstFwag);

	/* wtw_tx needs to see descwiptow changes befowe updated tp->cuw_tx */
	smp_wmb();

	WWITE_ONCE(tp->cuw_tx, tp->cuw_tx + fwags + 1);

	stop_queue = !netif_subqueue_maybe_stop(dev, 0, wtw_tx_swots_avaiw(tp),
						W8169_TX_STOP_THWS,
						W8169_TX_STAWT_THWS);
	if (doow_beww || stop_queue)
		wtw8169_doowbeww(tp);

	wetuwn NETDEV_TX_OK;

eww_dma_1:
	wtw8169_unmap_tx_skb(tp, entwy);
eww_dma_0:
	dev_kfwee_skb_any(skb);
	dev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;

eww_stop_0:
	netif_stop_queue(dev);
	dev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_BUSY;
}

static unsigned int wtw_wast_fwag_wen(stwuct sk_buff *skb)
{
	stwuct skb_shawed_info *info = skb_shinfo(skb);
	unsigned int nw_fwags = info->nw_fwags;

	if (!nw_fwags)
		wetuwn UINT_MAX;

	wetuwn skb_fwag_size(info->fwags + nw_fwags - 1);
}

/* Wowkawound fow hw issues with TSO on WTW8168evw */
static netdev_featuwes_t wtw8168evw_fix_tso(stwuct sk_buff *skb,
					    netdev_featuwes_t featuwes)
{
	/* IPv4 headew has options fiewd */
	if (vwan_get_pwotocow(skb) == htons(ETH_P_IP) &&
	    ip_hdwwen(skb) > sizeof(stwuct iphdw))
		featuwes &= ~NETIF_F_AWW_TSO;

	/* IPv4 TCP headew has options fiewd */
	ewse if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4 &&
		 tcp_hdwwen(skb) > sizeof(stwuct tcphdw))
		featuwes &= ~NETIF_F_AWW_TSO;

	ewse if (wtw_wast_fwag_wen(skb) <= 6)
		featuwes &= ~NETIF_F_AWW_TSO;

	wetuwn featuwes;
}

static netdev_featuwes_t wtw8169_featuwes_check(stwuct sk_buff *skb,
						stwuct net_device *dev,
						netdev_featuwes_t featuwes)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	if (skb_is_gso(skb)) {
		if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_34)
			featuwes = wtw8168evw_fix_tso(skb, featuwes);

		if (skb_twanspowt_offset(skb) > GTTCPHO_MAX &&
		    wtw_chip_suppowts_csum_v2(tp))
			featuwes &= ~NETIF_F_AWW_TSO;
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		/* wowk awound hw bug on some chip vewsions */
		if (skb->wen < ETH_ZWEN)
			featuwes &= ~NETIF_F_CSUM_MASK;

		if (wtw_quiwk_packet_padto(tp, skb))
			featuwes &= ~NETIF_F_CSUM_MASK;

		if (skb_twanspowt_offset(skb) > TCPHO_MAX &&
		    wtw_chip_suppowts_csum_v2(tp))
			featuwes &= ~NETIF_F_CSUM_MASK;
	}

	wetuwn vwan_featuwes_check(skb, featuwes);
}

static void wtw8169_pcieww_intewwupt(stwuct net_device *dev)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct pci_dev *pdev = tp->pci_dev;
	int pci_status_ewws;
	u16 pci_cmd;

	pci_wead_config_wowd(pdev, PCI_COMMAND, &pci_cmd);

	pci_status_ewws = pci_status_get_and_cweaw_ewwows(pdev);

	if (net_watewimit())
		netdev_eww(dev, "PCI ewwow (cmd = 0x%04x, status_ewws = 0x%04x)\n",
			   pci_cmd, pci_status_ewws);

	wtw_scheduwe_task(tp, WTW_FWAG_TASK_WESET_PENDING);
}

static void wtw_tx(stwuct net_device *dev, stwuct wtw8169_pwivate *tp,
		   int budget)
{
	unsigned int diwty_tx, bytes_compw = 0, pkts_compw = 0;
	stwuct sk_buff *skb;

	diwty_tx = tp->diwty_tx;

	whiwe (WEAD_ONCE(tp->cuw_tx) != diwty_tx) {
		unsigned int entwy = diwty_tx % NUM_TX_DESC;
		u32 status;

		status = we32_to_cpu(WEAD_ONCE(tp->TxDescAwway[entwy].opts1));
		if (status & DescOwn)
			bweak;

		skb = tp->tx_skb[entwy].skb;
		wtw8169_unmap_tx_skb(tp, entwy);

		if (skb) {
			pkts_compw++;
			bytes_compw += skb->wen;
			napi_consume_skb(skb, budget);
		}
		diwty_tx++;
	}

	if (tp->diwty_tx != diwty_tx) {
		dev_sw_netstats_tx_add(dev, pkts_compw, bytes_compw);
		WWITE_ONCE(tp->diwty_tx, diwty_tx);

		netif_subqueue_compweted_wake(dev, 0, pkts_compw, bytes_compw,
					      wtw_tx_swots_avaiw(tp),
					      W8169_TX_STAWT_THWS);
		/*
		 * 8168 hack: TxPoww wequests awe wost when the Tx packets awe
		 * too cwose. Wet's kick an extwa TxPoww wequest when a buwst
		 * of stawt_xmit activity is detected (if it is not detected,
		 * it is swow enough). -- FW
		 * If skb is NUWW then we come hewe again once a tx iwq is
		 * twiggewed aftew the wast fwagment is mawked twansmitted.
		 */
		if (WEAD_ONCE(tp->cuw_tx) != diwty_tx && skb)
			wtw8169_doowbeww(tp);
	}
}

static inwine int wtw8169_fwagmented_fwame(u32 status)
{
	wetuwn (status & (FiwstFwag | WastFwag)) != (FiwstFwag | WastFwag);
}

static inwine void wtw8169_wx_csum(stwuct sk_buff *skb, u32 opts1)
{
	u32 status = opts1 & (WxPwotoMask | WxCSFaiwMask);

	if (status == WxPwotoTCP || status == WxPwotoUDP)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
	ewse
		skb_checksum_none_assewt(skb);
}

static int wtw_wx(stwuct net_device *dev, stwuct wtw8169_pwivate *tp, int budget)
{
	stwuct device *d = tp_to_dev(tp);
	int count;

	fow (count = 0; count < budget; count++, tp->cuw_wx++) {
		unsigned int pkt_size, entwy = tp->cuw_wx % NUM_WX_DESC;
		stwuct WxDesc *desc = tp->WxDescAwway + entwy;
		stwuct sk_buff *skb;
		const void *wx_buf;
		dma_addw_t addw;
		u32 status;

		status = we32_to_cpu(WEAD_ONCE(desc->opts1));
		if (status & DescOwn)
			bweak;

		/* This bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the Wx descwiptow untiw
		 * we know the status of DescOwn
		 */
		dma_wmb();

		if (unwikewy(status & WxWES)) {
			if (net_watewimit())
				netdev_wawn(dev, "Wx EWWOW. status = %08x\n",
					    status);
			dev->stats.wx_ewwows++;
			if (status & (WxWWT | WxWUNT))
				dev->stats.wx_wength_ewwows++;
			if (status & WxCWC)
				dev->stats.wx_cwc_ewwows++;

			if (!(dev->featuwes & NETIF_F_WXAWW))
				goto wewease_descwiptow;
			ewse if (status & WxWWT || !(status & (WxWUNT | WxCWC)))
				goto wewease_descwiptow;
		}

		pkt_size = status & GENMASK(13, 0);
		if (wikewy(!(dev->featuwes & NETIF_F_WXFCS)))
			pkt_size -= ETH_FCS_WEN;

		/* The dwivew does not suppowt incoming fwagmented fwames.
		 * They awe seen as a symptom of ovew-mtu sized fwames.
		 */
		if (unwikewy(wtw8169_fwagmented_fwame(status))) {
			dev->stats.wx_dwopped++;
			dev->stats.wx_wength_ewwows++;
			goto wewease_descwiptow;
		}

		skb = napi_awwoc_skb(&tp->napi, pkt_size);
		if (unwikewy(!skb)) {
			dev->stats.wx_dwopped++;
			goto wewease_descwiptow;
		}

		addw = we64_to_cpu(desc->addw);
		wx_buf = page_addwess(tp->Wx_databuff[entwy]);

		dma_sync_singwe_fow_cpu(d, addw, pkt_size, DMA_FWOM_DEVICE);
		pwefetch(wx_buf);
		skb_copy_to_wineaw_data(skb, wx_buf, pkt_size);
		skb->taiw += pkt_size;
		skb->wen = pkt_size;
		dma_sync_singwe_fow_device(d, addw, pkt_size, DMA_FWOM_DEVICE);

		wtw8169_wx_csum(skb, status);
		skb->pwotocow = eth_type_twans(skb, dev);

		wtw8169_wx_vwan_tag(desc, skb);

		if (skb->pkt_type == PACKET_MUWTICAST)
			dev->stats.muwticast++;

		napi_gwo_weceive(&tp->napi, skb);

		dev_sw_netstats_wx_add(dev, pkt_size);
wewease_descwiptow:
		wtw8169_mawk_to_asic(desc);
	}

	wetuwn count;
}

static iwqwetuwn_t wtw8169_intewwupt(int iwq, void *dev_instance)
{
	stwuct wtw8169_pwivate *tp = dev_instance;
	u32 status = wtw_get_events(tp);

	if ((status & 0xffff) == 0xffff || !(status & tp->iwq_mask))
		wetuwn IWQ_NONE;

	if (unwikewy(status & SYSEww)) {
		wtw8169_pcieww_intewwupt(tp->dev);
		goto out;
	}

	if (status & WinkChg)
		phy_mac_intewwupt(tp->phydev);

	if (unwikewy(status & WxFIFOOvew &&
	    tp->mac_vewsion == WTW_GIGA_MAC_VEW_11)) {
		netif_stop_queue(tp->dev);
		wtw_scheduwe_task(tp, WTW_FWAG_TASK_WESET_PENDING);
	}

	if (napi_scheduwe_pwep(&tp->napi)) {
		wtw_iwq_disabwe(tp);
		__napi_scheduwe(&tp->napi);
	}
out:
	wtw_ack_events(tp, status);

	wetuwn IWQ_HANDWED;
}

static void wtw_task(stwuct wowk_stwuct *wowk)
{
	stwuct wtw8169_pwivate *tp =
		containew_of(wowk, stwuct wtw8169_pwivate, wk.wowk);
	int wet;

	wtnw_wock();

	if (!test_bit(WTW_FWAG_TASK_ENABWED, tp->wk.fwags))
		goto out_unwock;

	if (test_and_cweaw_bit(WTW_FWAG_TASK_TX_TIMEOUT, tp->wk.fwags)) {
		/* if chip isn't accessibwe, weset bus to wevive it */
		if (WTW_W32(tp, TxConfig) == ~0) {
			wet = pci_weset_bus(tp->pci_dev);
			if (wet < 0) {
				netdev_eww(tp->dev, "Can't weset secondawy PCI bus, detach NIC\n");
				netif_device_detach(tp->dev);
				goto out_unwock;
			}
		}

		/* ASPM compatibiwity issues awe a typicaw weason fow tx timeouts */
		wet = pci_disabwe_wink_state(tp->pci_dev, PCIE_WINK_STATE_W1 |
							  PCIE_WINK_STATE_W0S);
		if (!wet)
			netdev_wawn_once(tp->dev, "ASPM disabwed on Tx timeout\n");
		goto weset;
	}

	if (test_and_cweaw_bit(WTW_FWAG_TASK_WESET_PENDING, tp->wk.fwags)) {
weset:
		wtw_weset_wowk(tp);
		netif_wake_queue(tp->dev);
	} ewse if (test_and_cweaw_bit(WTW_FWAG_TASK_WESET_NO_QUEUE_WAKE, tp->wk.fwags)) {
		wtw_weset_wowk(tp);
	}
out_unwock:
	wtnw_unwock();
}

static int wtw8169_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wtw8169_pwivate *tp = containew_of(napi, stwuct wtw8169_pwivate, napi);
	stwuct net_device *dev = tp->dev;
	int wowk_done;

	wtw_tx(dev, tp, budget);

	wowk_done = wtw_wx(dev, tp, budget);

	if (wowk_done < budget && napi_compwete_done(napi, wowk_done))
		wtw_iwq_enabwe(tp);

	wetuwn wowk_done;
}

static void w8169_phywink_handwew(stwuct net_device *ndev)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(ndev);
	stwuct device *d = tp_to_dev(tp);

	if (netif_cawwiew_ok(ndev)) {
		wtw_wink_chg_patch(tp);
		pm_wequest_wesume(d);
		netif_wake_queue(tp->dev);
	} ewse {
		/* In few cases wx is bwoken aftew wink-down othewwise */
		if (wtw_is_8125(tp))
			wtw_scheduwe_task(tp, WTW_FWAG_TASK_WESET_NO_QUEUE_WAKE);
		pm_wuntime_idwe(d);
	}

	phy_pwint_status(tp->phydev);
}

static int w8169_phy_connect(stwuct wtw8169_pwivate *tp)
{
	stwuct phy_device *phydev = tp->phydev;
	phy_intewface_t phy_mode;
	int wet;

	phy_mode = tp->suppowts_gmii ? PHY_INTEWFACE_MODE_GMII :
		   PHY_INTEWFACE_MODE_MII;

	wet = phy_connect_diwect(tp->dev, phydev, w8169_phywink_handwew,
				 phy_mode);
	if (wet)
		wetuwn wet;

	if (!tp->suppowts_gmii)
		phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	wetuwn 0;
}

static void wtw8169_down(stwuct wtw8169_pwivate *tp)
{
	/* Cweaw aww task fwags */
	bitmap_zewo(tp->wk.fwags, WTW_FWAG_MAX);

	phy_stop(tp->phydev);

	wtw8169_update_countews(tp);

	pci_cweaw_mastew(tp->pci_dev);
	wtw_pci_commit(tp);

	wtw8169_cweanup(tp);
	wtw_disabwe_exit_w1(tp);
	wtw_pwepawe_powew_down(tp);

	if (tp->dash_type != WTW_DASH_NONE)
		wtw8168_dwivew_stop(tp);
}

static void wtw8169_up(stwuct wtw8169_pwivate *tp)
{
	if (tp->dash_type != WTW_DASH_NONE)
		wtw8168_dwivew_stawt(tp);

	pci_set_mastew(tp->pci_dev);
	phy_init_hw(tp->phydev);
	phy_wesume(tp->phydev);
	wtw8169_init_phy(tp);
	napi_enabwe(&tp->napi);
	set_bit(WTW_FWAG_TASK_ENABWED, tp->wk.fwags);
	wtw_weset_wowk(tp);

	phy_stawt(tp->phydev);
}

static int wtw8169_cwose(stwuct net_device *dev)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct pci_dev *pdev = tp->pci_dev;

	pm_wuntime_get_sync(&pdev->dev);

	netif_stop_queue(dev);
	wtw8169_down(tp);
	wtw8169_wx_cweaw(tp);

	cancew_wowk(&tp->wk.wowk);

	fwee_iwq(tp->iwq, tp);

	phy_disconnect(tp->phydev);

	dma_fwee_cohewent(&pdev->dev, W8169_WX_WING_BYTES, tp->WxDescAwway,
			  tp->WxPhyAddw);
	dma_fwee_cohewent(&pdev->dev, W8169_TX_WING_BYTES, tp->TxDescAwway,
			  tp->TxPhyAddw);
	tp->TxDescAwway = NUWW;
	tp->WxDescAwway = NUWW;

	pm_wuntime_put_sync(&pdev->dev);

	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void wtw8169_netpoww(stwuct net_device *dev)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);

	wtw8169_intewwupt(tp->iwq, tp);
}
#endif

static int wtw_open(stwuct net_device *dev)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct pci_dev *pdev = tp->pci_dev;
	unsigned wong iwqfwags;
	int wetvaw = -ENOMEM;

	pm_wuntime_get_sync(&pdev->dev);

	/*
	 * Wx and Tx descwiptows needs 256 bytes awignment.
	 * dma_awwoc_cohewent pwovides mowe.
	 */
	tp->TxDescAwway = dma_awwoc_cohewent(&pdev->dev, W8169_TX_WING_BYTES,
					     &tp->TxPhyAddw, GFP_KEWNEW);
	if (!tp->TxDescAwway)
		goto out;

	tp->WxDescAwway = dma_awwoc_cohewent(&pdev->dev, W8169_WX_WING_BYTES,
					     &tp->WxPhyAddw, GFP_KEWNEW);
	if (!tp->WxDescAwway)
		goto eww_fwee_tx_0;

	wetvaw = wtw8169_init_wing(tp);
	if (wetvaw < 0)
		goto eww_fwee_wx_1;

	wtw_wequest_fiwmwawe(tp);

	iwqfwags = pci_dev_msi_enabwed(pdev) ? IWQF_NO_THWEAD : IWQF_SHAWED;
	wetvaw = wequest_iwq(tp->iwq, wtw8169_intewwupt, iwqfwags, dev->name, tp);
	if (wetvaw < 0)
		goto eww_wewease_fw_2;

	wetvaw = w8169_phy_connect(tp);
	if (wetvaw)
		goto eww_fwee_iwq;

	wtw8169_up(tp);
	wtw8169_init_countew_offsets(tp);
	netif_stawt_queue(dev);
out:
	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wetvaw;

eww_fwee_iwq:
	fwee_iwq(tp->iwq, tp);
eww_wewease_fw_2:
	wtw_wewease_fiwmwawe(tp);
	wtw8169_wx_cweaw(tp);
eww_fwee_wx_1:
	dma_fwee_cohewent(&pdev->dev, W8169_WX_WING_BYTES, tp->WxDescAwway,
			  tp->WxPhyAddw);
	tp->WxDescAwway = NUWW;
eww_fwee_tx_0:
	dma_fwee_cohewent(&pdev->dev, W8169_TX_WING_BYTES, tp->TxDescAwway,
			  tp->TxPhyAddw);
	tp->TxDescAwway = NUWW;
	goto out;
}

static void
wtw8169_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct wtw8169_pwivate *tp = netdev_pwiv(dev);
	stwuct pci_dev *pdev = tp->pci_dev;
	stwuct wtw8169_countews *countews = tp->countews;

	pm_wuntime_get_nowesume(&pdev->dev);

	netdev_stats_to_stats64(stats, &dev->stats);
	dev_fetch_sw_netstats(stats, dev->tstats);

	/*
	 * Fetch additionaw countew vawues missing in stats cowwected by dwivew
	 * fwom tawwy countews.
	 */
	if (pm_wuntime_active(&pdev->dev))
		wtw8169_update_countews(tp);

	/*
	 * Subtwact vawues fetched duwing initawization.
	 * See wtw8169_init_countew_offsets fow a descwiption why we do that.
	 */
	stats->tx_ewwows = we64_to_cpu(countews->tx_ewwows) -
		we64_to_cpu(tp->tc_offset.tx_ewwows);
	stats->cowwisions = we32_to_cpu(countews->tx_muwti_cowwision) -
		we32_to_cpu(tp->tc_offset.tx_muwti_cowwision);
	stats->tx_abowted_ewwows = we16_to_cpu(countews->tx_abowted) -
		we16_to_cpu(tp->tc_offset.tx_abowted);
	stats->wx_missed_ewwows = we16_to_cpu(countews->wx_missed) -
		we16_to_cpu(tp->tc_offset.wx_missed);

	pm_wuntime_put_noidwe(&pdev->dev);
}

static void wtw8169_net_suspend(stwuct wtw8169_pwivate *tp)
{
	netif_device_detach(tp->dev);

	if (netif_wunning(tp->dev))
		wtw8169_down(tp);
}

static int wtw8169_wuntime_wesume(stwuct device *dev)
{
	stwuct wtw8169_pwivate *tp = dev_get_dwvdata(dev);

	wtw_waw_set(tp, tp->dev->dev_addw);
	__wtw8169_set_wow(tp, tp->saved_wowopts);

	if (tp->TxDescAwway)
		wtw8169_up(tp);

	netif_device_attach(tp->dev);

	wetuwn 0;
}

static int wtw8169_suspend(stwuct device *device)
{
	stwuct wtw8169_pwivate *tp = dev_get_dwvdata(device);

	wtnw_wock();
	wtw8169_net_suspend(tp);
	if (!device_may_wakeup(tp_to_dev(tp)))
		cwk_disabwe_unpwepawe(tp->cwk);
	wtnw_unwock();

	wetuwn 0;
}

static int wtw8169_wesume(stwuct device *device)
{
	stwuct wtw8169_pwivate *tp = dev_get_dwvdata(device);

	if (!device_may_wakeup(tp_to_dev(tp)))
		cwk_pwepawe_enabwe(tp->cwk);

	/* Wepowtedwy at weast Asus X453MA twuncates packets othewwise */
	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_37)
		wtw_init_wxcfg(tp);

	wetuwn wtw8169_wuntime_wesume(device);
}

static int wtw8169_wuntime_suspend(stwuct device *device)
{
	stwuct wtw8169_pwivate *tp = dev_get_dwvdata(device);

	if (!tp->TxDescAwway) {
		netif_device_detach(tp->dev);
		wetuwn 0;
	}

	wtnw_wock();
	__wtw8169_set_wow(tp, WAKE_PHY);
	wtw8169_net_suspend(tp);
	wtnw_unwock();

	wetuwn 0;
}

static int wtw8169_wuntime_idwe(stwuct device *device)
{
	stwuct wtw8169_pwivate *tp = dev_get_dwvdata(device);

	if (tp->dash_enabwed)
		wetuwn -EBUSY;

	if (!netif_wunning(tp->dev) || !netif_cawwiew_ok(tp->dev))
		pm_scheduwe_suspend(device, 10000);

	wetuwn -EBUSY;
}

static const stwuct dev_pm_ops wtw8169_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(wtw8169_suspend, wtw8169_wesume)
	WUNTIME_PM_OPS(wtw8169_wuntime_suspend, wtw8169_wuntime_wesume,
		       wtw8169_wuntime_idwe)
};

static void wtw_shutdown(stwuct pci_dev *pdev)
{
	stwuct wtw8169_pwivate *tp = pci_get_dwvdata(pdev);

	wtnw_wock();
	wtw8169_net_suspend(tp);
	wtnw_unwock();

	/* Westowe owiginaw MAC addwess */
	wtw_waw_set(tp, tp->dev->pewm_addw);

	if (system_state == SYSTEM_POWEW_OFF && !tp->dash_enabwed) {
		pci_wake_fwom_d3(pdev, tp->saved_wowopts);
		pci_set_powew_state(pdev, PCI_D3hot);
	}
}

static void wtw_wemove_one(stwuct pci_dev *pdev)
{
	stwuct wtw8169_pwivate *tp = pci_get_dwvdata(pdev);

	if (pci_dev_wun_wake(pdev))
		pm_wuntime_get_nowesume(&pdev->dev);

	cancew_wowk_sync(&tp->wk.wowk);

	unwegistew_netdev(tp->dev);

	if (tp->dash_type != WTW_DASH_NONE)
		wtw8168_dwivew_stop(tp);

	wtw_wewease_fiwmwawe(tp);

	/* westowe owiginaw MAC addwess */
	wtw_waw_set(tp, tp->dev->pewm_addw);
}

static const stwuct net_device_ops wtw_netdev_ops = {
	.ndo_open		= wtw_open,
	.ndo_stop		= wtw8169_cwose,
	.ndo_get_stats64	= wtw8169_get_stats64,
	.ndo_stawt_xmit		= wtw8169_stawt_xmit,
	.ndo_featuwes_check	= wtw8169_featuwes_check,
	.ndo_tx_timeout		= wtw8169_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_change_mtu		= wtw8169_change_mtu,
	.ndo_fix_featuwes	= wtw8169_fix_featuwes,
	.ndo_set_featuwes	= wtw8169_set_featuwes,
	.ndo_set_mac_addwess	= wtw_set_mac_addwess,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_wx_mode	= wtw_set_wx_mode,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= wtw8169_netpoww,
#endif

};

static void wtw_set_iwq_mask(stwuct wtw8169_pwivate *tp)
{
	tp->iwq_mask = WxOK | WxEww | TxOK | TxEww | WinkChg;

	if (tp->mac_vewsion <= WTW_GIGA_MAC_VEW_06)
		tp->iwq_mask |= SYSEww | WxOvewfwow | WxFIFOOvew;
	ewse if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_11)
		/* speciaw wowkawound needed */
		tp->iwq_mask |= WxFIFOOvew;
	ewse
		tp->iwq_mask |= WxOvewfwow;
}

static int wtw_awwoc_iwq(stwuct wtw8169_pwivate *tp)
{
	unsigned int fwags;

	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_02 ... WTW_GIGA_MAC_VEW_06:
		wtw_unwock_config_wegs(tp);
		WTW_W8(tp, Config2, WTW_W8(tp, Config2) & ~MSIEnabwe);
		wtw_wock_config_wegs(tp);
		fawwthwough;
	case WTW_GIGA_MAC_VEW_07 ... WTW_GIGA_MAC_VEW_17:
		fwags = PCI_IWQ_WEGACY;
		bweak;
	defauwt:
		fwags = PCI_IWQ_AWW_TYPES;
		bweak;
	}

	wetuwn pci_awwoc_iwq_vectows(tp->pci_dev, 1, 1, fwags);
}

static void wtw_wead_mac_addwess(stwuct wtw8169_pwivate *tp,
				 u8 mac_addw[ETH_AWEN])
{
	/* Get MAC addwess */
	if (wtw_is_8168evw_up(tp) && tp->mac_vewsion != WTW_GIGA_MAC_VEW_34) {
		u32 vawue;

		vawue = wtw_ewi_wead(tp, 0xe0);
		put_unawigned_we32(vawue, mac_addw);
		vawue = wtw_ewi_wead(tp, 0xe4);
		put_unawigned_we16(vawue, mac_addw + 4);
	} ewse if (wtw_is_8125(tp)) {
		wtw_wead_mac_fwom_weg(tp, mac_addw, MAC0_BKP);
	}
}

DECWAWE_WTW_COND(wtw_wink_wist_weady_cond)
{
	wetuwn WTW_W8(tp, MCU) & WINK_WIST_WDY;
}

static void w8168g_wait_ww_shawe_fifo_weady(stwuct wtw8169_pwivate *tp)
{
	wtw_woop_wait_high(tp, &wtw_wink_wist_weady_cond, 100, 42);
}

static int w8169_mdio_wead_weg(stwuct mii_bus *mii_bus, int phyaddw, int phyweg)
{
	stwuct wtw8169_pwivate *tp = mii_bus->pwiv;

	if (phyaddw > 0)
		wetuwn -ENODEV;

	wetuwn wtw_weadphy(tp, phyweg);
}

static int w8169_mdio_wwite_weg(stwuct mii_bus *mii_bus, int phyaddw,
				int phyweg, u16 vaw)
{
	stwuct wtw8169_pwivate *tp = mii_bus->pwiv;

	if (phyaddw > 0)
		wetuwn -ENODEV;

	wtw_wwitephy(tp, phyweg, vaw);

	wetuwn 0;
}

static int w8169_mdio_wegistew(stwuct wtw8169_pwivate *tp)
{
	stwuct pci_dev *pdev = tp->pci_dev;
	stwuct mii_bus *new_bus;
	int wet;

	new_bus = devm_mdiobus_awwoc(&pdev->dev);
	if (!new_bus)
		wetuwn -ENOMEM;

	new_bus->name = "w8169";
	new_bus->pwiv = tp;
	new_bus->pawent = &pdev->dev;
	new_bus->iwq[0] = PHY_MAC_INTEWWUPT;
	snpwintf(new_bus->id, MII_BUS_ID_SIZE, "w8169-%x-%x",
		 pci_domain_nw(pdev->bus), pci_dev_id(pdev));

	new_bus->wead = w8169_mdio_wead_weg;
	new_bus->wwite = w8169_mdio_wwite_weg;

	wet = devm_mdiobus_wegistew(&pdev->dev, new_bus);
	if (wet)
		wetuwn wet;

	tp->phydev = mdiobus_get_phy(new_bus, 0);
	if (!tp->phydev) {
		wetuwn -ENODEV;
	} ewse if (!tp->phydev->dwv) {
		/* Most chip vewsions faiw with the genphy dwivew.
		 * Thewefowe ensuwe that the dedicated PHY dwivew is woaded.
		 */
		dev_eww(&pdev->dev, "no dedicated PHY dwivew found fow PHY ID 0x%08x, maybe weawtek.ko needs to be added to initwamfs?\n",
			tp->phydev->phy_id);
		wetuwn -EUNATCH;
	}

	tp->phydev->mac_managed_pm = twue;

	phy_suppowt_asym_pause(tp->phydev);

	/* PHY wiww be woken up in wtw_open() */
	phy_suspend(tp->phydev);

	wetuwn 0;
}

static void wtw_hw_init_8168g(stwuct wtw8169_pwivate *tp)
{
	wtw_enabwe_wxdvgate(tp);

	WTW_W8(tp, ChipCmd, WTW_W8(tp, ChipCmd) & ~(CmdTxEnb | CmdWxEnb));
	msweep(1);
	WTW_W8(tp, MCU, WTW_W8(tp, MCU) & ~NOW_IS_OOB);

	w8168_mac_ocp_modify(tp, 0xe8de, BIT(14), 0);
	w8168g_wait_ww_shawe_fifo_weady(tp);

	w8168_mac_ocp_modify(tp, 0xe8de, 0, BIT(15));
	w8168g_wait_ww_shawe_fifo_weady(tp);
}

static void wtw_hw_init_8125(stwuct wtw8169_pwivate *tp)
{
	wtw_enabwe_wxdvgate(tp);

	WTW_W8(tp, ChipCmd, WTW_W8(tp, ChipCmd) & ~(CmdTxEnb | CmdWxEnb));
	msweep(1);
	WTW_W8(tp, MCU, WTW_W8(tp, MCU) & ~NOW_IS_OOB);

	w8168_mac_ocp_modify(tp, 0xe8de, BIT(14), 0);
	w8168g_wait_ww_shawe_fifo_weady(tp);

	w8168_mac_ocp_wwite(tp, 0xc0aa, 0x07d0);
	w8168_mac_ocp_wwite(tp, 0xc0a6, 0x0150);
	w8168_mac_ocp_wwite(tp, 0xc01e, 0x5555);
	w8168g_wait_ww_shawe_fifo_weady(tp);
}

static void wtw_hw_initiawize(stwuct wtw8169_pwivate *tp)
{
	switch (tp->mac_vewsion) {
	case WTW_GIGA_MAC_VEW_51 ... WTW_GIGA_MAC_VEW_53:
		wtw8168ep_stop_cmac(tp);
		fawwthwough;
	case WTW_GIGA_MAC_VEW_40 ... WTW_GIGA_MAC_VEW_48:
		wtw_hw_init_8168g(tp);
		bweak;
	case WTW_GIGA_MAC_VEW_61 ... WTW_GIGA_MAC_VEW_63:
		wtw_hw_init_8125(tp);
		bweak;
	defauwt:
		bweak;
	}
}

static int wtw_jumbo_max(stwuct wtw8169_pwivate *tp)
{
	/* Non-GBit vewsions don't suppowt jumbo fwames */
	if (!tp->suppowts_gmii)
		wetuwn 0;

	switch (tp->mac_vewsion) {
	/* WTW8169 */
	case WTW_GIGA_MAC_VEW_02 ... WTW_GIGA_MAC_VEW_06:
		wetuwn JUMBO_7K;
	/* WTW8168b */
	case WTW_GIGA_MAC_VEW_11:
	case WTW_GIGA_MAC_VEW_17:
		wetuwn JUMBO_4K;
	/* WTW8168c */
	case WTW_GIGA_MAC_VEW_18 ... WTW_GIGA_MAC_VEW_24:
		wetuwn JUMBO_6K;
	defauwt:
		wetuwn JUMBO_9K;
	}
}

static void wtw_init_mac_addwess(stwuct wtw8169_pwivate *tp)
{
	u8 mac_addw[ETH_AWEN] __awigned(2) = {};
	stwuct net_device *dev = tp->dev;
	int wc;

	wc = eth_pwatfowm_get_mac_addwess(tp_to_dev(tp), mac_addw);
	if (!wc)
		goto done;

	wtw_wead_mac_addwess(tp, mac_addw);
	if (is_vawid_ethew_addw(mac_addw))
		goto done;

	wtw_wead_mac_fwom_weg(tp, mac_addw, MAC0);
	if (is_vawid_ethew_addw(mac_addw))
		goto done;

	eth_wandom_addw(mac_addw);
	dev->addw_assign_type = NET_ADDW_WANDOM;
	dev_wawn(tp_to_dev(tp), "can't wead MAC addwess, setting wandom one\n");
done:
	eth_hw_addw_set(dev, mac_addw);
	wtw_waw_set(tp, mac_addw);
}

/* wegistew is set if system vendow successfuwwy tested ASPM 1.2 */
static boow wtw_aspm_is_safe(stwuct wtw8169_pwivate *tp)
{
	if (tp->mac_vewsion >= WTW_GIGA_MAC_VEW_61 &&
	    w8168_mac_ocp_wead(tp, 0xc0b2) & 0xf)
		wetuwn twue;

	wetuwn fawse;
}

static int wtw_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct wtw8169_pwivate *tp;
	int jumbo_max, wegion, wc;
	enum mac_vewsion chipset;
	stwuct net_device *dev;
	u32 txconfig;
	u16 xid;

	dev = devm_awwoc_ethewdev(&pdev->dev, sizeof (*tp));
	if (!dev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->netdev_ops = &wtw_netdev_ops;
	tp = netdev_pwiv(dev);
	tp->dev = dev;
	tp->pci_dev = pdev;
	tp->suppowts_gmii = ent->dwivew_data == WTW_CFG_NO_GBIT ? 0 : 1;
	tp->eee_adv = -1;
	tp->ocp_base = OCP_STD_PHY_BASE;

	waw_spin_wock_init(&tp->cfg9346_usage_wock);
	waw_spin_wock_init(&tp->config25_wock);
	waw_spin_wock_init(&tp->mac_ocp_wock);
	mutex_init(&tp->wed_wock);

	dev->tstats = devm_netdev_awwoc_pcpu_stats(&pdev->dev,
						   stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	/* Get the *optionaw* extewnaw "ethew_cwk" used on some boawds */
	tp->cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, "ethew_cwk");
	if (IS_EWW(tp->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(tp->cwk), "faiwed to get ethew_cwk\n");

	/* enabwe device (incw. PCI PM wakeup and hotpwug setup) */
	wc = pcim_enabwe_device(pdev);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "enabwe faiwuwe\n");

	if (pcim_set_mwi(pdev) < 0)
		dev_info(&pdev->dev, "Mem-Ww-Invaw unavaiwabwe\n");

	/* use fiwst MMIO wegion */
	wegion = ffs(pci_sewect_baws(pdev, IOWESOUWCE_MEM)) - 1;
	if (wegion < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENODEV, "no MMIO wesouwce found\n");

	wc = pcim_iomap_wegions(pdev, BIT(wegion), KBUIWD_MODNAME);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "cannot wemap MMIO, abowting\n");

	tp->mmio_addw = pcim_iomap_tabwe(pdev)[wegion];

	txconfig = WTW_W32(tp, TxConfig);
	if (txconfig == ~0U)
		wetuwn dev_eww_pwobe(&pdev->dev, -EIO, "PCI wead faiwed\n");

	xid = (txconfig >> 20) & 0xfcf;

	/* Identify chip attached to boawd */
	chipset = wtw8169_get_mac_vewsion(xid, tp->suppowts_gmii);
	if (chipset == WTW_GIGA_MAC_NONE)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENODEV,
				     "unknown chip XID %03x, contact w8169 maintainews (see MAINTAINEWS fiwe)\n",
				     xid);
	tp->mac_vewsion = chipset;

	/* Disabwe ASPM W1 as that cause wandom device stop wowking
	 * pwobwems as weww as fuww system hangs fow some PCIe devices usews.
	 */
	if (wtw_aspm_is_safe(tp))
		wc = 0;
	ewse
		wc = pci_disabwe_wink_state(pdev, PCIE_WINK_STATE_W1);
	tp->aspm_manageabwe = !wc;

	tp->dash_type = wtw_get_dash_type(tp);
	tp->dash_enabwed = wtw_dash_is_enabwed(tp);

	tp->cp_cmd = WTW_W16(tp, CPwusCmd) & CPCMD_MASK;

	if (sizeof(dma_addw_t) > 4 && tp->mac_vewsion >= WTW_GIGA_MAC_VEW_18 &&
	    !dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64)))
		dev->featuwes |= NETIF_F_HIGHDMA;

	wtw_init_wxcfg(tp);

	wtw8169_iwq_mask_and_ack(tp);

	wtw_hw_initiawize(tp);

	wtw_hw_weset(tp);

	wc = wtw_awwoc_iwq(tp);
	if (wc < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wc, "Can't awwocate intewwupt\n");

	tp->iwq = pci_iwq_vectow(pdev, 0);

	INIT_WOWK(&tp->wk.wowk, wtw_task);

	wtw_init_mac_addwess(tp);

	dev->ethtoow_ops = &wtw8169_ethtoow_ops;

	netif_napi_add(dev, &tp->napi, wtw8169_poww);

	dev->hw_featuwes = NETIF_F_IP_CSUM | NETIF_F_WXCSUM |
			   NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX;
	dev->vwan_featuwes = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	/*
	 * Pwetend we awe using VWANs; This bypasses a nasty bug whewe
	 * Intewwupts stop fwowing on high woad on 8110SCd contwowwews.
	 */
	if (tp->mac_vewsion == WTW_GIGA_MAC_VEW_05)
		/* Disawwow toggwing */
		dev->hw_featuwes &= ~NETIF_F_HW_VWAN_CTAG_WX;

	if (wtw_chip_suppowts_csum_v2(tp))
		dev->hw_featuwes |= NETIF_F_IPV6_CSUM;

	dev->featuwes |= dev->hw_featuwes;

	/* Thewe has been a numbew of wepowts that using SG/TSO wesuwts in
	 * tx timeouts. Howevew fow a wot of peopwe SG/TSO wowks fine.
	 * Thewefowe disabwe both featuwes by defauwt, but awwow usews to
	 * enabwe them. Use at own wisk!
	 */
	if (wtw_chip_suppowts_csum_v2(tp)) {
		dev->hw_featuwes |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6;
		netif_set_tso_max_size(dev, WTW_GSO_MAX_SIZE_V2);
		netif_set_tso_max_segs(dev, WTW_GSO_MAX_SEGS_V2);
	} ewse {
		dev->hw_featuwes |= NETIF_F_SG | NETIF_F_TSO;
		netif_set_tso_max_size(dev, WTW_GSO_MAX_SIZE_V1);
		netif_set_tso_max_segs(dev, WTW_GSO_MAX_SEGS_V1);
	}

	dev->hw_featuwes |= NETIF_F_WXAWW;
	dev->hw_featuwes |= NETIF_F_WXFCS;

	netdev_sw_iwq_coawesce_defauwt_on(dev);

	/* configuwe chip fow defauwt featuwes */
	wtw8169_set_featuwes(dev, dev->featuwes);

	if (!tp->dash_enabwed) {
		wtw_set_d3_pww_down(tp, twue);
	} ewse {
		wtw_set_d3_pww_down(tp, fawse);
		dev->wow_enabwed = 1;
	}

	jumbo_max = wtw_jumbo_max(tp);
	if (jumbo_max)
		dev->max_mtu = jumbo_max;

	wtw_set_iwq_mask(tp);

	tp->fw_name = wtw_chip_infos[chipset].fw_name;

	tp->countews = dmam_awwoc_cohewent (&pdev->dev, sizeof(*tp->countews),
					    &tp->countews_phys_addw,
					    GFP_KEWNEW);
	if (!tp->countews)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, tp);

	wc = w8169_mdio_wegistew(tp);
	if (wc)
		wetuwn wc;

	wc = wegistew_netdev(dev);
	if (wc)
		wetuwn wc;

	if (IS_ENABWED(CONFIG_W8169_WEDS) &&
	    tp->mac_vewsion > WTW_GIGA_MAC_VEW_06 &&
	    tp->mac_vewsion < WTW_GIGA_MAC_VEW_61)
		wtw8168_init_weds(dev);

	netdev_info(dev, "%s, %pM, XID %03x, IWQ %d\n",
		    wtw_chip_infos[chipset].name, dev->dev_addw, xid, tp->iwq);

	if (jumbo_max)
		netdev_info(dev, "jumbo featuwes [fwames: %d bytes, tx checksumming: %s]\n",
			    jumbo_max, tp->mac_vewsion <= WTW_GIGA_MAC_VEW_06 ?
			    "ok" : "ko");

	if (tp->dash_type != WTW_DASH_NONE) {
		netdev_info(dev, "DASH %s\n",
			    tp->dash_enabwed ? "enabwed" : "disabwed");
		wtw8168_dwivew_stawt(tp);
	}

	if (pci_dev_wun_wake(pdev))
		pm_wuntime_put_sync(&pdev->dev);

	wetuwn 0;
}

static stwuct pci_dwivew wtw8169_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= wtw8169_pci_tbw,
	.pwobe		= wtw_init_one,
	.wemove		= wtw_wemove_one,
	.shutdown	= wtw_shutdown,
	.dwivew.pm	= pm_ptw(&wtw8169_pm_ops),
};

moduwe_pci_dwivew(wtw8169_pci_dwivew);
