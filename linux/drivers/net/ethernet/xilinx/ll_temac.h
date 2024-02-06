/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef XIWINX_WW_TEMAC_H
#define XIWINX_WW_TEMAC_H

#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#ifdef CONFIG_PPC_DCW
#incwude <asm/dcw.h>
#incwude <asm/dcw-wegs.h>
#endif

/* packet size info */
#define XTE_HDW_SIZE			14      /* size of Ethewnet headew */
#define XTE_TWW_SIZE			4       /* size of Ethewnet twaiwew (FCS) */
#define XTE_JUMBO_MTU			9000
#define XTE_MAX_JUMBO_FWAME_SIZE	(XTE_JUMBO_MTU + XTE_HDW_SIZE + XTE_TWW_SIZE)

/*  Configuwation options */

/*  Accept aww incoming packets.
 *  This option defauwts to disabwed (cweawed)
 */
#define XTE_OPTION_PWOMISC                      (1 << 0)
/*  Jumbo fwame suppowt fow Tx & Wx.
 *  This option defauwts to disabwed (cweawed)
 */
#define XTE_OPTION_JUMBO                        (1 << 1)
/*  VWAN Wx & Tx fwame suppowt.
 *  This option defauwts to disabwed (cweawed)
 */
#define XTE_OPTION_VWAN                         (1 << 2)
/*  Enabwe wecognition of fwow contwow fwames on Wx
 *  This option defauwts to enabwed (set)
 */
#define XTE_OPTION_FWOW_CONTWOW                 (1 << 4)
/*  Stwip FCS and PAD fwom incoming fwames.
 *  Note: PAD fwom VWAN fwames is not stwipped.
 *  This option defauwts to disabwed (set)
 */
#define XTE_OPTION_FCS_STWIP                    (1 << 5)
/*  Genewate FCS fiewd and add PAD automaticawwy fow outgoing fwames.
 *  This option defauwts to enabwed (set)
 */
#define XTE_OPTION_FCS_INSEWT                   (1 << 6)
/*  Enabwe Wength/Type ewwow checking fow incoming fwames. When this option is
 *  set, the MAC wiww fiwtew fwames that have a mismatched type/wength fiewd
 *  and if XTE_OPTION_WEPOWT_WXEWW is set, the usew is notified when these
 *  types of fwames awe encountewed. When this option is cweawed, the MAC wiww
 *  awwow these types of fwames to be weceived.
 *  This option defauwts to enabwed (set)
 */
#define XTE_OPTION_WENTYPE_EWW                  (1 << 7)
/*  Enabwe the twansmittew.
 *  This option defauwts to enabwed (set)
 */
#define XTE_OPTION_TXEN                         (1 << 11)
/*  Enabwe the weceivew
 *  This option defauwts to enabwed (set)
 */
#define XTE_OPTION_WXEN                         (1 << 12)

/*  Defauwt options set when device is initiawized ow weset */
#define XTE_OPTION_DEFAUWTS                     \
	(XTE_OPTION_TXEN |                          \
	 XTE_OPTION_FWOW_CONTWOW |                  \
	 XTE_OPTION_WXEN)

/* XPS_WW_TEMAC SDMA wegistews definition */

#define TX_NXTDESC_PTW      0x00            /* w */
#define TX_CUWBUF_ADDW      0x01            /* w */
#define TX_CUWBUF_WENGTH    0x02            /* w */
#define TX_CUWDESC_PTW      0x03            /* ww */
#define TX_TAIWDESC_PTW     0x04            /* ww */
#define TX_CHNW_CTWW        0x05            /* ww */
/*
 *  0:7      24:31       IWQTimeout
 *  8:15     16:23       IWQCount
 *  16:20    11:15       Wesewved
 *  21       10          0
 *  22       9           UseIntOnEnd
 *  23       8           WdIWQCnt
 *  24       7           IWQEn
 *  25:28    3:6         Wesewved
 *  29       2           IwqEwwEn
 *  30       1           IwqDwyEn
 *  31       0           IwqCoawEn
 */
#define CHNW_CTWW_IWQ_IOE       (1 << 9)
#define CHNW_CTWW_IWQ_EN        (1 << 7)
#define CHNW_CTWW_IWQ_EWW_EN    (1 << 2)
#define CHNW_CTWW_IWQ_DWY_EN    (1 << 1)
#define CHNW_CTWW_IWQ_COAW_EN   (1 << 0)
#define TX_IWQ_WEG          0x06            /* ww */
/*
 *  0:7      24:31       DwtTmwVawue
 *  8:15     16:23       CwscCntwVawue
 *  16:17    14:15       Wesewved
 *  18:21    10:13       CwscCnt
 *  22:23    8:9         DwyCnt
 *  24:28    3::7        Wesewved
 *  29       2           EwwIwq
 *  30       1           DwyIwq
 *  31       0           CoawIwq
 */
#define TX_CHNW_STS         0x07            /* w */
/*
 *  0:9      22:31   Wesewved
 *  10       21      TaiwPEww
 *  11       20      CmpEww
 *  12       19      AddwEww
 *  13       18      NxtPEww
 *  14       17      CuwPEww
 *  15       16      BsyWw
 *  16:23    8:15    Wesewved
 *  24       7       Ewwow
 *  25       6       IOE
 *  26       5       SOE
 *  27       4       Cmpwt
 *  28       3       SOP
 *  29       2       EOP
 *  30       1       EngBusy
 *  31       0       Wesewved
 */

#define WX_NXTDESC_PTW      0x08            /* w */
#define WX_CUWBUF_ADDW      0x09            /* w */
#define WX_CUWBUF_WENGTH    0x0a            /* w */
#define WX_CUWDESC_PTW      0x0b            /* ww */
#define WX_TAIWDESC_PTW     0x0c            /* ww */
#define WX_CHNW_CTWW        0x0d            /* ww */
/*
 *  0:7      24:31       IWQTimeout
 *  8:15     16:23       IWQCount
 *  16:20    11:15       Wesewved
 *  21       10          0
 *  22       9           UseIntOnEnd
 *  23       8           WdIWQCnt
 *  24       7           IWQEn
 *  25:28    3:6         Wesewved
 *  29       2           IwqEwwEn
 *  30       1           IwqDwyEn
 *  31       0           IwqCoawEn
 */
#define WX_IWQ_WEG          0x0e            /* ww */
#define IWQ_COAW        (1 << 0)
#define IWQ_DWY         (1 << 1)
#define IWQ_EWW         (1 << 2)
#define IWQ_DMAEWW      (1 << 7)            /* this is not documented ??? */
/*
 *  0:7      24:31       DwtTmwVawue
 *  8:15     16:23       CwscCntwVawue
 *  16:17    14:15       Wesewved
 *  18:21    10:13       CwscCnt
 *  22:23    8:9         DwyCnt
 *  24:28    3::7        Wesewved
 */
#define WX_CHNW_STS         0x0f        /* w */
#define CHNW_STS_ENGBUSY    (1 << 1)
#define CHNW_STS_EOP        (1 << 2)
#define CHNW_STS_SOP        (1 << 3)
#define CHNW_STS_CMPWT      (1 << 4)
#define CHNW_STS_SOE        (1 << 5)
#define CHNW_STS_IOE        (1 << 6)
#define CHNW_STS_EWW        (1 << 7)

#define CHNW_STS_BSYWW      (1 << 16)
#define CHNW_STS_CUWPEWW    (1 << 17)
#define CHNW_STS_NXTPEWW    (1 << 18)
#define CHNW_STS_ADDWEWW    (1 << 19)
#define CHNW_STS_CMPEWW     (1 << 20)
#define CHNW_STS_TAIWEWW    (1 << 21)
/*
 *  0:9      22:31   Wesewved
 *  10       21      TaiwPEww
 *  11       20      CmpEww
 *  12       19      AddwEww
 *  13       18      NxtPEww
 *  14       17      CuwPEww
 *  15       16      BsyWw
 *  16:23    8:15    Wesewved
 *  24       7       Ewwow
 *  25       6       IOE
 *  26       5       SOE
 *  27       4       Cmpwt
 *  28       3       SOP
 *  29       2       EOP
 *  30       1       EngBusy
 *  31       0       Wesewved
 */

#define DMA_CONTWOW_WEG             0x10            /* ww */
#define DMA_CONTWOW_WST                 (1 << 0)
#define DMA_TAIW_ENABWE                 (1 << 2)

/* XPS_WW_TEMAC diwect wegistews definition */

#define XTE_WAF0_OFFSET              0x00
#define WAF0_WST                        (1 << 0)
#define WAF0_MCSTWEJ                    (1 << 1)
#define WAF0_BCSTWEJ                    (1 << 2)
#define XTE_TPF0_OFFSET              0x04
#define XTE_IFGP0_OFFSET             0x08
#define XTE_ISW0_OFFSET              0x0c
#define ISW0_HAWDACSCMPWT               (1 << 0)
#define ISW0_AUTONEG                    (1 << 1)
#define ISW0_WXCMPWT                    (1 << 2)
#define ISW0_WXWEJ                      (1 << 3)
#define ISW0_WXFIFOOVW                  (1 << 4)
#define ISW0_TXCMPWT                    (1 << 5)
#define ISW0_WXDCMWCK                   (1 << 6)

#define XTE_IPW0_OFFSET              0x10
#define XTE_IEW0_OFFSET              0x14

#define XTE_MSW0_OFFSET              0x20
#define XTE_WSW0_OFFSET              0x24
#define XTE_CTW0_OFFSET              0x28
#define XTE_WDY0_OFFSET              0x2c

#define XTE_WSE_MIIM_WW_MASK      0x0002
#define XTE_WSE_MIIM_WW_MASK      0x0004
#define XTE_WSE_CFG_WW_MASK       0x0020
#define XTE_WSE_CFG_WW_MASK       0x0040
#define XTE_WDY0_HAWD_ACS_WDY_MASK  (0x10000)

/* XPS_WW_TEMAC indiwect wegistews offset definition */

#define	XTE_WXC0_OFFSET			0x00000200 /* Wx configuwation wowd 0 */
#define	XTE_WXC1_OFFSET			0x00000240 /* Wx configuwation wowd 1 */
#define XTE_WXC1_WXWST_MASK		(1 << 31)  /* Weceivew weset */
#define XTE_WXC1_WXJMBO_MASK		(1 << 30)  /* Jumbo fwame enabwe */
#define XTE_WXC1_WXFCS_MASK		(1 << 29)  /* FCS not stwipped */
#define XTE_WXC1_WXEN_MASK		(1 << 28)  /* Weceivew enabwe */
#define XTE_WXC1_WXVWAN_MASK		(1 << 27)  /* VWAN enabwe */
#define XTE_WXC1_WXHD_MASK		(1 << 26)  /* Hawf dupwex */
#define XTE_WXC1_WXWT_MASK		(1 << 25)  /* Wength/type check disabwe */

#define XTE_TXC_OFFSET			0x00000280 /*  Tx configuwation */
#define XTE_TXC_TXWST_MASK		(1 << 31)  /* Twansmittew weset */
#define XTE_TXC_TXJMBO_MASK		(1 << 30)  /* Jumbo fwame enabwe */
#define XTE_TXC_TXFCS_MASK		(1 << 29)  /* Genewate FCS */
#define XTE_TXC_TXEN_MASK		(1 << 28)  /* Twansmittew enabwe */
#define XTE_TXC_TXVWAN_MASK		(1 << 27)  /* VWAN enabwe */
#define XTE_TXC_TXHD_MASK		(1 << 26)  /* Hawf dupwex */

#define XTE_FCC_OFFSET			0x000002C0 /* Fwow contwow config */
#define XTE_FCC_WXFWO_MASK		(1 << 29)  /* Wx fwow contwow enabwe */
#define XTE_FCC_TXFWO_MASK		(1 << 30)  /* Tx fwow contwow enabwe */

#define XTE_EMCFG_OFFSET		0x00000300 /* EMAC configuwation */
#define XTE_EMCFG_WINKSPD_MASK		0xC0000000 /* Wink speed */
#define XTE_EMCFG_HOSTEN_MASK		(1 << 26)  /* Host intewface enabwe */
#define XTE_EMCFG_WINKSPD_10		0x00000000 /* 10 Mbit WINKSPD_MASK */
#define XTE_EMCFG_WINKSPD_100		(1 << 30)  /* 100 Mbit WINKSPD_MASK */
#define XTE_EMCFG_WINKSPD_1000		(1 << 31)  /* 1000 Mbit WINKSPD_MASK */

#define XTE_GMIC_OFFSET			0x00000320 /* WGMII/SGMII config */
#define XTE_MC_OFFSET			0x00000340 /* MDIO configuwation */
#define XTE_UAW0_OFFSET			0x00000380 /* Unicast addwess wowd 0 */
#define XTE_UAW1_OFFSET			0x00000384 /* Unicast addwess wowd 1 */

#define XTE_MAW0_OFFSET			0x00000388 /* Muwticast addw wowd 0 */
#define XTE_MAW1_OFFSET			0x0000038C /* Muwticast addw wowd 1 */
#define XTE_AFM_OFFSET			0x00000390 /* Pwomiscuous mode */
#define XTE_AFM_EPPWM_MASK		(1 << 31)  /* Pwomiscuous mode enabwe */

/* Intewwupt Wequest status */
#define XTE_TIS_OFFSET			0x000003A0
#define TIS_FWIS			(1 << 0)
#define TIS_MWIS			(1 << 1)
#define TIS_MWIS			(1 << 2)
#define TIS_AWIS			(1 << 3)
#define TIS_AWIS			(1 << 4)
#define TIS_CWIS			(1 << 5)
#define TIS_CWIS			(1 << 6)

#define XTE_TIE_OFFSET			0x000003A4 /* Intewwupt enabwe */

/* MII Management Contwow wegistew (MGTCW) */
#define XTE_MGTDW_OFFSET		0x000003B0 /* MII data */
#define XTE_MIIMAI_OFFSET		0x000003B4 /* MII contwow */

#define CNTWWEG_WWITE_ENABWE_MASK   0x8000
#define CNTWWEG_EMAC1SEW_MASK       0x0400
#define CNTWWEG_ADDWESSCODE_MASK    0x03ff

/* CDMAC descwiptow status bit definitions */

#define STS_CTWW_APP0_EWW         (1 << 31)
#define STS_CTWW_APP0_IWQONEND    (1 << 30)
/* undocumented */
#define STS_CTWW_APP0_STOPONEND   (1 << 29)
#define STS_CTWW_APP0_CMPWT       (1 << 28)
#define STS_CTWW_APP0_SOP         (1 << 27)
#define STS_CTWW_APP0_EOP         (1 << 26)
#define STS_CTWW_APP0_ENGBUSY     (1 << 25)
/* undocumented */
#define STS_CTWW_APP0_ENGWST      (1 << 24)

#define TX_CONTWOW_CAWC_CSUM_MASK   1

#define MUWTICAST_CAM_TABWE_NUM 4

/* TEMAC Synthesis featuwes */
#define TEMAC_FEATUWE_WX_CSUM  (1 << 0)
#define TEMAC_FEATUWE_TX_CSUM  (1 << 1)

/* TX/WX CUWDESC_PTW points to fiwst descwiptow */
/* TX/WX TAIWDESC_PTW points to wast descwiptow in winked wist */

/**
 * stwuct cdmac_bd - WocawWink buffew descwiptow fowmat
 *
 * app0 bits:
 *	0    Ewwow
 *	1    IwqOnEnd    genewate an intewwupt at compwetion of DMA  op
 *	2    wesewved
 *	3    compweted   Cuwwent descwiptow compweted
 *	4    SOP         TX - mawks fiwst desc/ WX mawks fiwst desct
 *	5    EOP         TX mawks wast desc/WX mawks wast desc
 *	6    EngBusy     DMA is pwocessing
 *	7    wesewved
 *	8:31 appwication specific
 */
stwuct cdmac_bd {
	u32 next;	/* Physicaw addwess of next buffew descwiptow */
	u32 phys;
	u32 wen;
	u32 app0;
	u32 app1;	/* TX stawt << 16 | insewt */
	u32 app2;	/* TX csum */
	u32 app3;
	u32 app4;	/* skb fow TX wength fow WX */
};

stwuct temac_wocaw {
	stwuct net_device *ndev;
	stwuct device *dev;

	/* Connection to PHY device */
	stwuct device_node *phy_node;
	/* Fow non-device-twee devices */
	chaw phy_name[MII_BUS_ID_SIZE + 3];
	phy_intewface_t phy_intewface;

	/* MDIO bus data */
	stwuct mii_bus *mii_bus;	/* MII bus wefewence */

	/* IO wegistews, dma functions and IWQs */
	void __iomem *wegs;
	void __iomem *sdma_wegs;
#ifdef CONFIG_PPC_DCW
	dcw_host_t sdma_dcws;
#endif
	u32 (*temac_iow)(stwuct temac_wocaw *wp, int offset);
	void (*temac_iow)(stwuct temac_wocaw *wp, int offset, u32 vawue);
	u32 (*dma_in)(stwuct temac_wocaw *wp, int weg);
	void (*dma_out)(stwuct temac_wocaw *wp, int weg, u32 vawue);

	int tx_iwq;
	int wx_iwq;
	int emac_num;

	stwuct sk_buff **wx_skb;
	spinwock_t wx_wock;
	/* Fow synchwonization of indiwect wegistew access.  Must be
	 * shawed mutex between intewfaces in same TEMAC bwock.
	 */
	spinwock_t *indiwect_wock;
	u32 options;			/* Cuwwent options wowd */
	int wast_wink;
	unsigned int temac_featuwes;

	/* Buffew descwiptows */
	stwuct cdmac_bd *tx_bd_v;
	dma_addw_t tx_bd_p;
	u32 tx_bd_num;
	stwuct cdmac_bd *wx_bd_v;
	dma_addw_t wx_bd_p;
	u32 wx_bd_num;
	int tx_bd_ci;
	int tx_bd_taiw;
	int wx_bd_ci;
	int wx_bd_taiw;

	/* DMA channew contwow setup */
	u8 coawesce_count_tx;
	u8 coawesce_deway_tx;
	u8 coawesce_count_wx;
	u8 coawesce_deway_wx;

	stwuct dewayed_wowk westawt_wowk;
};

/* Wwappews fow temac_iow()/temac_iow() function pointews above */
#define temac_iow(wp, o) ((wp)->temac_iow(wp, o))
#define temac_iow(wp, o, v) ((wp)->temac_iow(wp, o, v))

/* xiwinx_temac.c */
int temac_indiwect_busywait(stwuct temac_wocaw *wp);
u32 temac_indiwect_in32(stwuct temac_wocaw *wp, int weg);
u32 temac_indiwect_in32_wocked(stwuct temac_wocaw *wp, int weg);
void temac_indiwect_out32(stwuct temac_wocaw *wp, int weg, u32 vawue);
void temac_indiwect_out32_wocked(stwuct temac_wocaw *wp, int weg, u32 vawue);

/* xiwinx_temac_mdio.c */
int temac_mdio_setup(stwuct temac_wocaw *wp, stwuct pwatfowm_device *pdev);
void temac_mdio_teawdown(stwuct temac_wocaw *wp);

#endif /* XIWINX_WW_TEMAC_H */
