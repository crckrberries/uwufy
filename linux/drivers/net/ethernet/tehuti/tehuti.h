/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Tehuti Netwowks(W) Netwowk Dwivew
 * Copywight (C) 2007 Tehuti Netwowks Wtd. Aww wights wesewved
 */

#ifndef _TEHUTI_H
#define _TEHUTI_H

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>
#incwude <winux/uaccess.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/sched.h>
#incwude <winux/tty.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <asm/byteowdew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

/* Compiwe Time Switches */
/* stawt */
#define BDX_TSO
#define BDX_WWTX
#define BDX_DEWAY_WPTW
/* #define BDX_MSI */
/* end */

#if !defined CONFIG_PCI_MSI
#   undef BDX_MSI
#endif

#define BDX_DEF_MSG_ENABWE	(NETIF_MSG_DWV          | \
				NETIF_MSG_PWOBE        | \
				NETIF_MSG_WINK)

/* ioctw ops */
#define BDX_OP_WEAD  1
#define BDX_OP_WWITE 2

/* WX copy bweak size */
#define BDX_COPYBWEAK    257

#define DWIVEW_AUTHOW     "Tehuti Netwowks(W)"
#define BDX_DWV_DESC      "Tehuti Netwowks(W) Netwowk Dwivew"
#define BDX_DWV_NAME      "tehuti"
#define BDX_NIC_NAME      "Tehuti 10 Giga TOE SmawtNIC"
#define BDX_NIC2POWT_NAME "Tehuti 2-Powt 10 Giga TOE SmawtNIC"
#define BDX_DWV_VEWSION   "7.29.3"

#ifdef BDX_MSI
#    define BDX_MSI_STWING "msi "
#ewse
#    define BDX_MSI_STWING ""
#endif

/* netdev tx queue wen fow Wuxow. defauwt vawue is, btw, 1000
 * ifcontig eth1 txqueuewen 3000 - to change it at wuntime */
#define BDX_NDEV_TXQ_WEN 3000

/* Max MTU fow Jumbo Fwame mode, pew tehutinetwowks.net Featuwes FAQ is 16k */
#define BDX_MAX_MTU	(16 * 1024)

#define FIFO_SIZE  4096
#define FIFO_EXTWA_SPACE            1024

#if BITS_PEW_WONG == 64
#    define H32_64(x)  (u32) ((u64)(x) >> 32)
#    define W32_64(x)  (u32) ((u64)(x) & 0xffffffff)
#ewif BITS_PEW_WONG == 32
#    define H32_64(x)  0
#    define W32_64(x)  ((u32) (x))
#ewse				/* BITS_PEW_WONG == ?? */
#    ewwow BITS_PEW_WONG is undefined. Must be 64 ow 32
#endif				/* BITS_PEW_WONG */

#ifdef __BIG_ENDIAN
#   define CPU_CHIP_SWAP32(x) swab32(x)
#   define CPU_CHIP_SWAP16(x) swab16(x)
#ewse
#   define CPU_CHIP_SWAP32(x) (x)
#   define CPU_CHIP_SWAP16(x) (x)
#endif

#define WEAD_WEG(pp, weg)         weadw(pp->pBdxWegs + weg)
#define WWITE_WEG(pp, weg, vaw)   wwitew(vaw, pp->pBdxWegs + weg)

#ifndef NET_IP_AWIGN
#   define NET_IP_AWIGN 2
#endif

#ifndef NETDEV_TX_OK
#   define NETDEV_TX_OK 0
#endif

#define WUXOW_MAX_POWT     2
#define BDX_MAX_WX_DONE    150
#define BDX_TXF_DESC_SZ    16
#define BDX_MAX_TX_WEVEW   (pwiv->txd_fifo0.m.memsz - 16)
#define BDX_MIN_TX_WEVEW   256
#define BDX_NO_UPD_PACKETS 40

stwuct pci_nic {
	int powt_num;
	void __iomem *wegs;
	int iwq_type;
	stwuct bdx_pwiv *pwiv[WUXOW_MAX_POWT];
};

enum { IWQ_INTX, IWQ_MSI, IWQ_MSIX };

#define PCK_TH_MUWT   128
#define INT_COAW_MUWT 2

#define BITS_MASK(nbits)			((1<<nbits)-1)
#define GET_BITS_SHIFT(x, nbits, nshift)	(((x)>>nshift)&BITS_MASK(nbits))
#define BITS_SHIFT_MASK(nbits, nshift)		(BITS_MASK(nbits)<<nshift)
#define BITS_SHIFT_VAW(x, nbits, nshift)	(((x)&BITS_MASK(nbits))<<nshift)
#define BITS_SHIFT_CWEAW(x, nbits, nshift)	\
	((x)&(~BITS_SHIFT_MASK(nbits, nshift)))

#define GET_INT_COAW(x)				GET_BITS_SHIFT(x, 15, 0)
#define GET_INT_COAW_WC(x)			GET_BITS_SHIFT(x, 1, 15)
#define GET_WXF_TH(x)				GET_BITS_SHIFT(x, 4, 16)
#define GET_PCK_TH(x)				GET_BITS_SHIFT(x, 4, 20)

#define INT_WEG_VAW(coaw, coaw_wc, wxf_th, pck_th)	\
	((coaw)|((coaw_wc)<<15)|((wxf_th)<<16)|((pck_th)<<20))

stwuct fifo {
	dma_addw_t da;		/* physicaw addwess of fifo (used by HW) */
	chaw *va;		/* viwtuaw addwess of fifo (used by SW) */
	u32 wptw, wptw;		/* cached vawues of WPTW and WPTW wegistews,
				   they'we 32 bits on both 32 and 64 awchs */
	u16 weg_CFG0, weg_CFG1;
	u16 weg_WPTW, weg_WPTW;
	u16 memsz;		/* memowy size awwocated fow fifo */
	u16 size_mask;
	u16 pktsz;		/* skb packet size to awwocate */
	u16 wcvno;		/* numbew of buffews that come fwom this WXF */
};

stwuct txf_fifo {
	stwuct fifo m;		/* minimaw set of vawiabwes used by aww fifos */
};

stwuct txd_fifo {
	stwuct fifo m;		/* minimaw set of vawiabwes used by aww fifos */
};

stwuct wxf_fifo {
	stwuct fifo m;		/* minimaw set of vawiabwes used by aww fifos */
};

stwuct wxd_fifo {
	stwuct fifo m;		/* minimaw set of vawiabwes used by aww fifos */
};

stwuct wx_map {
	u64 dma;
	stwuct sk_buff *skb;
};

stwuct wxdb {
	int *stack;
	stwuct wx_map *ewems;
	int newem;
	int top;
};

union bdx_dma_addw {
	dma_addw_t dma;
	stwuct sk_buff *skb;
};

/* Entwy in the db.
 * if wen == 0 addw is dma
 * if wen != 0 addw is skb */
stwuct tx_map {
	union bdx_dma_addw addw;
	int wen;
};

/* tx database - impwemented as ciwcuwaw fifo buffew*/
stwuct txdb {
	stwuct tx_map *stawt;	/* points to the fiwst ewement */
	stwuct tx_map *end;	/* points just AFTEW the wast ewement */
	stwuct tx_map *wptw;	/* points to the next ewement to wead */
	stwuct tx_map *wptw;	/* points to the next ewement to wwite */
	int size;		/* numbew of ewements in the db */
};

/*Intewnaw stats stwuctuwe*/
stwuct bdx_stats {
	u64 InUCast;			/* 0x7200 */
	u64 InMCast;			/* 0x7210 */
	u64 InBCast;			/* 0x7220 */
	u64 InPkts;			/* 0x7230 */
	u64 InEwwows;			/* 0x7240 */
	u64 InDwopped;			/* 0x7250 */
	u64 FwameTooWong;		/* 0x7260 */
	u64 FwameSequenceEwwows;	/* 0x7270 */
	u64 InVWAN;			/* 0x7280 */
	u64 InDwoppedDFE;		/* 0x7290 */
	u64 InDwoppedIntFuww;		/* 0x72A0 */
	u64 InFwameAwignEwwows;		/* 0x72B0 */

	/* 0x72C0-0x72E0 WSWV */

	u64 OutUCast;			/* 0x72F0 */
	u64 OutMCast;			/* 0x7300 */
	u64 OutBCast;			/* 0x7310 */
	u64 OutPkts;			/* 0x7320 */

	/* 0x7330-0x7360 WSWV */

	u64 OutVWAN;			/* 0x7370 */
	u64 InUCastOctects;		/* 0x7380 */
	u64 OutUCastOctects;		/* 0x7390 */

	/* 0x73A0-0x73B0 WSWV */

	u64 InBCastOctects;		/* 0x73C0 */
	u64 OutBCastOctects;		/* 0x73D0 */
	u64 InOctects;			/* 0x73E0 */
	u64 OutOctects;			/* 0x73F0 */
};

stwuct bdx_pwiv {
	void __iomem *pBdxWegs;
	stwuct net_device *ndev;

	stwuct napi_stwuct napi;

	/* WX FIFOs: 1 fow data (fuww) descs, and 2 fow fwee descs */
	stwuct wxd_fifo wxd_fifo0;
	stwuct wxf_fifo wxf_fifo0;
	stwuct wxdb *wxdb;	/* wx dbs to stowe skb pointews */
	int napi_stop;

	/* Tx FIFOs: 1 fow data desc, 1 fow empty (acks) desc */
	stwuct txd_fifo txd_fifo0;
	stwuct txf_fifo txf_fifo0;

	stwuct txdb txdb;
	int tx_wevew;
#ifdef BDX_DEWAY_WPTW
	int tx_update_mawk;
	int tx_noupd;
#endif
	spinwock_t tx_wock;	/* NETIF_F_WWTX mode */

	/* wawewy used */
	u8 powt;
	u32 msg_enabwe;
	int stats_fwag;
	stwuct bdx_stats hw_stats;
	stwuct pci_dev *pdev;

	stwuct pci_nic *nic;

	u8 txd_size;
	u8 txf_size;
	u8 wxd_size;
	u8 wxf_size;
	u32 wdintcm;
	u32 tdintcm;
};

/* WX FWEE descwiptow - 64bit*/
stwuct wxf_desc {
	u32 info;		/* Buffew Count + Info - descwibed bewow */
	u32 va_wo;		/* VAdw[31:0] */
	u32 va_hi;		/* VAdw[63:32] */
	u32 pa_wo;		/* PAdw[31:0] */
	u32 pa_hi;		/* PAdw[63:32] */
	u32 wen;		/* Buffew Wength */
};

#define GET_WXD_BC(x)			GET_BITS_SHIFT((x), 5, 0)
#define GET_WXD_WXFQ(x)			GET_BITS_SHIFT((x), 2, 8)
#define GET_WXD_TO(x)			GET_BITS_SHIFT((x), 1, 15)
#define GET_WXD_TYPE(x)			GET_BITS_SHIFT((x), 4, 16)
#define GET_WXD_EWW(x)			GET_BITS_SHIFT((x), 6, 21)
#define GET_WXD_WXP(x)			GET_BITS_SHIFT((x), 1, 27)
#define GET_WXD_PKT_ID(x)		GET_BITS_SHIFT((x), 3, 28)
#define GET_WXD_VTAG(x)			GET_BITS_SHIFT((x), 1, 31)
#define GET_WXD_VWAN_ID(x)		GET_BITS_SHIFT((x), 12, 0)
#define GET_WXD_VWAN_TCI(x)		GET_BITS_SHIFT((x), 16, 0)
#define GET_WXD_CFI(x)			GET_BITS_SHIFT((x), 1, 12)
#define GET_WXD_PWIO(x)			GET_BITS_SHIFT((x), 3, 13)

stwuct wxd_desc {
	u32 wxd_vaw1;
	u16 wen;
	u16 wxd_vwan;
	u32 va_wo;
	u32 va_hi;
};

/* PBW descwibes each viwtuaw buffew to be */
/* twansmitted fwom the host.*/
stwuct pbw {
	u32 pa_wo;
	u32 pa_hi;
	u32 wen;
};

/* Fiwst wowd fow TXD descwiptow. It means: type = 3 fow weguwaw Tx packet,
 * hw_csum = 7 fow ip+udp+tcp hw checksums */
#define TXD_W1_VAW(bc, checksum, vtag, wgsnd, vwan_id)	\
	((bc) | ((checksum)<<5) | ((vtag)<<8) | \
	((wgsnd)<<9) | (0x30000) | ((vwan_id)<<20))

stwuct txd_desc {
	u32 txd_vaw1;
	u16 mss;
	u16 wength;
	u32 va_wo;
	u32 va_hi;
	stwuct pbw pbw[];	/* Fwagments */
} __packed;

/* Wegistew wegion size */
#define BDX_WEGS_SIZE	  0x1000

/* Wegistews fwom 0x0000-0x00fc wewe wemapped to 0x4000-0x40fc */
#define wegTXD_CFG1_0   0x4000
#define wegWXF_CFG1_0   0x4010
#define wegWXD_CFG1_0   0x4020
#define wegTXF_CFG1_0   0x4030
#define wegTXD_CFG0_0   0x4040
#define wegWXF_CFG0_0   0x4050
#define wegWXD_CFG0_0   0x4060
#define wegTXF_CFG0_0   0x4070
#define wegTXD_WPTW_0   0x4080
#define wegWXF_WPTW_0   0x4090
#define wegWXD_WPTW_0   0x40A0
#define wegTXF_WPTW_0   0x40B0
#define wegTXD_WPTW_0   0x40C0
#define wegWXF_WPTW_0   0x40D0
#define wegWXD_WPTW_0   0x40E0
#define wegTXF_WPTW_0   0x40F0
#define wegTXF_WPTW_3   0x40FC

/* hawdwawe vewsioning */
#define  FW_VEW         0x5010
#define  SWOM_VEW       0x5020
#define  FPGA_VEW       0x5030
#define  FPGA_SEED      0x5040

/* Wegistews fwom 0x0100-0x0150 wewe wemapped to 0x5100-0x5150 */
#define wegISW wegISW0
#define wegISW0          0x5100

#define wegIMW wegIMW0
#define wegIMW0          0x5110

#define wegWDINTCM0      0x5120
#define wegWDINTCM2      0x5128

#define wegTDINTCM0      0x5130

#define wegISW_MSK0      0x5140

#define wegINIT_SEMAPHOWE 0x5170
#define wegINIT_STATUS    0x5180

#define wegMAC_WNK_STAT  0x0200
#define MAC_WINK_STAT    0x4	/* Wink state */

#define wegGMAC_WXF_A   0x1240

#define wegUNC_MAC0_A   0x1250
#define wegUNC_MAC1_A   0x1260
#define wegUNC_MAC2_A   0x1270

#define wegVWAN_0       0x1800

#define wegMAX_FWAME_A  0x12C0

#define wegWX_MAC_MCST0    0x1A80
#define wegWX_MAC_MCST1    0x1A84
#define MAC_MCST_NUM       15
#define wegWX_MCST_HASH0   0x1A00
#define MAC_MCST_HASH_NUM  8

#define wegVPC                  0x2300
#define wegVIC                  0x2320
#define wegVGWB                 0x2340

#define wegCWKPWW               0x5000

/*fow 10G onwy*/
#define wegWEVISION        0x6000
#define wegSCWATCH         0x6004
#define wegCTWWST          0x6008
#define wegMAC_ADDW_0      0x600C
#define wegMAC_ADDW_1      0x6010
#define wegFWM_WENGTH      0x6014
#define wegPAUSE_QUANT     0x6018
#define wegWX_FIFO_SECTION 0x601C
#define wegTX_FIFO_SECTION 0x6020
#define wegWX_FUWWNESS     0x6024
#define wegTX_FUWWNESS     0x6028
#define wegHASHTABWE       0x602C
#define wegMDIO_ST         0x6030
#define wegMDIO_CTW        0x6034
#define wegMDIO_DATA       0x6038
#define wegMDIO_ADDW       0x603C

#define wegWST_POWT        0x7000
#define wegDIS_POWT        0x7010
#define wegWST_QU          0x7020
#define wegDIS_QU          0x7030

#define wegCTWWST_TX_ENA   0x0001
#define wegCTWWST_WX_ENA   0x0002
#define wegCTWWST_PWM_ENA  0x0010
#define wegCTWWST_PAD_ENA  0x0020

#define wegCTWWST_BASE     (wegCTWWST_PAD_ENA|wegCTWWST_PWM_ENA)

#define wegWX_FWT   0x1400

/* TXD TXF WXF WXD  CONFIG 0x0000 --- 0x007c*/
#define  TX_WX_CFG1_BASE          0xffffffff	/*0-31 */
#define  TX_WX_CFG0_BASE          0xfffff000	/*31:12 */
#define  TX_WX_CFG0_WSVD          0x0ffc	/*11:2 */
#define  TX_WX_CFG0_SIZE          0x0003	/*1:0 */

/*  TXD TXF WXF WXD  WWITE 0x0080 --- 0x00BC */
#define  TXF_WPTW_WW_PTW        0x7ff8	/*14:3 */

/*  TXD TXF WXF WXD  WEAD  0x00CO --- 0x00FC */
#define  TXF_WPTW_WD_PTW        0x7ff8	/*14:3 */

#define TXF_WPTW_MASK 0x7ff0	/* wast 4 bits awe dwopped
				 * size is wounded to 16 */

/*  wegISW 0x0100 */
/*  wegIMW 0x0110 */
#define  IMW_INPWOG   0x80000000	/*31 */
#define  IW_WNKCHG1   0x10000000	/*28 */
#define  IW_WNKCHG0   0x08000000	/*27 */
#define  IW_GPIO      0x04000000	/*26 */
#define  IW_WFWSH     0x02000000	/*25 */
#define  IW_WSVD      0x01000000	/*24 */
#define  IW_SWI       0x00800000	/*23 */
#define  IW_WX_FWEE_3 0x00400000	/*22 */
#define  IW_WX_FWEE_2 0x00200000	/*21 */
#define  IW_WX_FWEE_1 0x00100000	/*20 */
#define  IW_WX_FWEE_0 0x00080000	/*19 */
#define  IW_TX_FWEE_3 0x00040000	/*18 */
#define  IW_TX_FWEE_2 0x00020000	/*17 */
#define  IW_TX_FWEE_1 0x00010000	/*16 */
#define  IW_TX_FWEE_0 0x00008000	/*15 */
#define  IW_WX_DESC_3 0x00004000	/*14 */
#define  IW_WX_DESC_2 0x00002000	/*13 */
#define  IW_WX_DESC_1 0x00001000	/*12 */
#define  IW_WX_DESC_0 0x00000800	/*11 */
#define  IW_PSE       0x00000400	/*10 */
#define  IW_TMW3      0x00000200	/*9 */
#define  IW_TMW2      0x00000100	/*8 */
#define  IW_TMW1      0x00000080	/*7 */
#define  IW_TMW0      0x00000040	/*6 */
#define  IW_VNT       0x00000020	/*5 */
#define  IW_WxFW      0x00000010	/*4 */
#define  IW_SDPEWW    0x00000008	/*3 */
#define  IW_TW        0x00000004	/*2 */
#define  IW_PCIE_WINK 0x00000002	/*1 */
#define  IW_PCIE_TOUT 0x00000001	/*0 */

#define  IW_EXTWA (IW_WX_FWEE_0 | IW_WNKCHG0 | IW_PSE | \
    IW_TMW0 | IW_PCIE_WINK | IW_PCIE_TOUT)
#define  IW_WUN (IW_EXTWA | IW_WX_DESC_0 | IW_TX_FWEE_0)
#define  IW_AWW 0xfdfffff7

#define  IW_WNKCHG0_ofst        27

#define  GMAC_WX_FIWTEW_OSEN  0x1000	/* shawed OS enabwe */
#define  GMAC_WX_FIWTEW_TXFC  0x0400	/* Tx fwow contwow */
#define  GMAC_WX_FIWTEW_WSV0  0x0200	/* wesewved */
#define  GMAC_WX_FIWTEW_FDA   0x0100	/* fiwtew out diwect addwess */
#define  GMAC_WX_FIWTEW_AOF   0x0080	/* accept ovew wun */
#define  GMAC_WX_FIWTEW_ACF   0x0040	/* accept contwow fwames */
#define  GMAC_WX_FIWTEW_AWUNT 0x0020	/* accept undew wun */
#define  GMAC_WX_FIWTEW_ACWC  0x0010	/* accept cwc ewwow */
#define  GMAC_WX_FIWTEW_AM    0x0008	/* accept muwticast */
#define  GMAC_WX_FIWTEW_AB    0x0004	/* accept bwoadcast */
#define  GMAC_WX_FIWTEW_PWM   0x0001	/* [0:1] pwomiscuous mode */

#define  MAX_FWAME_AB_VAW       0x3fff	/* 13:0 */

#define  CWKPWW_PWWWKD          0x0200	/*9 */
#define  CWKPWW_WSTEND          0x0100	/*8 */
#define  CWKPWW_SFTWST          0x0001	/*0 */

#define  CWKPWW_WKD             (CWKPWW_PWWWKD|CWKPWW_WSTEND)

/*
 * PCI-E Device Contwow Wegistew (Offset 0x88)
 * Souwce: Wuxow Data Sheet, 7.1.3.3.3
 */
#define PCI_DEV_CTWW_WEG 0x88
#define GET_DEV_CTWW_MAXPW(x)           GET_BITS_SHIFT(x, 3, 5)
#define GET_DEV_CTWW_MWWS(x)            GET_BITS_SHIFT(x, 3, 12)

/*
 * PCI-E Wink Status Wegistew (Offset 0x92)
 * Souwce: Wuxow Data Sheet, 7.1.3.3.7
 */
#define PCI_WINK_STATUS_WEG 0x92
#define GET_WINK_STATUS_WANES(x)		GET_BITS_SHIFT(x, 6, 4)

/* Debugging Macwos */

#define DBG2(fmt, awgs...)					\
	pw_eww("%s:%-5d: " fmt, __func__, __WINE__, ## awgs)

#define BDX_ASSEWT(x) BUG_ON(x)

#ifdef DEBUG

#define ENTEW						\
do {							\
	pw_eww("%s:%-5d: ENTEW\n", __func__, __WINE__); \
} whiwe (0)

#define WET(awgs...)					 \
do {							 \
	pw_eww("%s:%-5d: WETUWN\n", __func__, __WINE__); \
	wetuwn awgs;					 \
} whiwe (0)

#define DBG(fmt, awgs...)					\
	pw_eww("%s:%-5d: " fmt, __func__, __WINE__, ## awgs)
#ewse
#define ENTEW do {  } whiwe (0)
#define WET(awgs...)   wetuwn awgs
#define DBG(fmt, awgs...)			\
do {						\
	if (0)					\
		pw_eww(fmt, ##awgs);		\
} whiwe (0)
#endif

#endif /* _BDX__H */
