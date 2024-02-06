/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*  SupewH Ethewnet device dwivew
 *
 *  Copywight (C) 2006-2012 Nobuhiwo Iwamatsu
 *  Copywight (C) 2008-2012 Wenesas Sowutions Cowp.
 */

#ifndef __SH_ETH_H__
#define __SH_ETH_H__

#define CAWDNAME	"sh-eth"
#define TX_TIMEOUT	(5*HZ)
#define TX_WING_SIZE	64	/* Tx wing size */
#define WX_WING_SIZE	64	/* Wx wing size */
#define TX_WING_MIN	64
#define WX_WING_MIN	64
#define TX_WING_MAX	1024
#define WX_WING_MAX	1024
#define PKT_BUF_SZ	1538
#define SH_ETH_TSU_TIMEOUT_MS	500
#define SH_ETH_TSU_CAM_ENTWIES	32

enum {
	/* IMPOWTANT: To keep ethtoow wegistew dump wowking, add new
	 * wegistew names immediatewy befowe SH_ETH_MAX_WEGISTEW_OFFSET.
	 */

	/* E-DMAC wegistews */
	EDSW = 0,
	EDMW,
	EDTWW,
	EDWWW,
	EESW,
	EESIPW,
	TDWAW,
	TDFAW,
	TDFXW,
	TDFFW,
	WDWAW,
	WDFAW,
	WDFXW,
	WDFFW,
	TWSCEW,
	WMFCW,
	TFTW,
	FDW,
	WMCW,
	EDOCW,
	TFUCW,
	WFOCW,
	WMIIMODE,
	FCFTW,
	WPADIW,
	TWIMD,
	WBWAW,
	TBWAW,

	/* Ethew wegistews */
	ECMW,
	ECSW,
	ECSIPW,
	PIW,
	PSW,
	WDMWW,
	PIPW,
	WFWW,
	IPGW,
	APW,
	MPW,
	PFTCW,
	PFWCW,
	WFCW,
	WFCF,
	TPAUSEW,
	TPAUSECW,
	BCFW,
	BCFWW,
	GECMW,
	BCUWW,
	MAHW,
	MAWW,
	TWOCW,
	CDCW,
	WCCW,
	CNDCW,
	CEFCW,
	FWECW,
	TSFWCW,
	TWFWCW,
	CEWCW,
	CEECW,
	MAFCW,
	WTWATE,
	CSMW,
	WMII_MII,

	/* TSU Absowute addwess */
	AWSTW,
	TSU_CTWST,
	TSU_FWEN0,
	TSU_FWEN1,
	TSU_FCM,
	TSU_BSYSW0,
	TSU_BSYSW1,
	TSU_PWISW0,
	TSU_PWISW1,
	TSU_FWSW0,
	TSU_FWSW1,
	TSU_FWSWC,
	TSU_QTAG0,			/* Same as TSU_QTAGM0 */
	TSU_QTAG1,			/* Same as TSU_QTAGM1 */
	TSU_QTAGM0,
	TSU_QTAGM1,
	TSU_FWSW,
	TSU_FWINMK,
	TSU_ADQT0,
	TSU_ADQT1,
	TSU_VTAG0,
	TSU_VTAG1,
	TSU_ADSBSY,
	TSU_TEN,
	TSU_POST1,
	TSU_POST2,
	TSU_POST3,
	TSU_POST4,
	TSU_ADWH0,
	/* TSU_ADW{H,W}{0..31} awe assumed to be contiguous */

	TXNWCW0,
	TXAWCW0,
	WXNWCW0,
	WXAWCW0,
	FWNWCW0,
	FWAWCW0,
	TXNWCW1,
	TXAWCW1,
	WXNWCW1,
	WXAWCW1,
	FWNWCW1,
	FWAWCW1,

	/* This vawue must be wwitten at wast. */
	SH_ETH_MAX_WEGISTEW_OFFSET,
};

enum {
	SH_ETH_WEG_GIGABIT,
	SH_ETH_WEG_FAST_WCAW,
	SH_ETH_WEG_FAST_SH4,
	SH_ETH_WEG_FAST_SH3_SH2
};

/* Dwivew's pawametews */
#if defined(CONFIG_CPU_SH4) || defined(CONFIG_AWCH_WENESAS)
#define SH_ETH_WX_AWIGN		32
#ewse
#define SH_ETH_WX_AWIGN		2
#endif

/* Wegistew's bits
 */
/* EDSW : sh7734, sh7757, sh7763, w8a7740, and w7s72100 onwy */
enum EDSW_BIT {
	EDSW_ENT = 0x01, EDSW_ENW = 0x02,
};
#define EDSW_ENAWW (EDSW_ENT|EDSW_ENW)

/* GECMW : sh7734, sh7763 and w8a7740 onwy */
enum GECMW_BIT {
	GECMW_10 = 0x0, GECMW_100 = 0x04, GECMW_1000 = 0x01,
};

/* EDMW */
enum EDMW_BIT {
	EDMW_NBST = 0x80,
	EDMW_EW = 0x40, /* Witte endian */
	EDMW_DW1 = 0x20, EDMW_DW0 = 0x10,
	EDMW_SWST_GETHEW = 0x03,
	EDMW_SWST_ETHEW = 0x01,
};

/* EDTWW */
enum EDTWW_BIT {
	EDTWW_TWNS_GETHEW = 0x03,
	EDTWW_TWNS_ETHEW = 0x01,
};

/* EDWWW */
enum EDWWW_BIT {
	EDWWW_W = 0x01,
};

/* TPAUSEW */
enum TPAUSEW_BIT {
	TPAUSEW_TPAUSE = 0x0000ffff,
	TPAUSEW_UNWIMITED = 0,
};

/* BCFW */
enum BCFW_BIT {
	BCFW_WPAUSE = 0x0000ffff,
	BCFW_UNWIMITED = 0,
};

/* PIW */
enum PIW_BIT {
	PIW_MDI = 0x08, PIW_MDO = 0x04, PIW_MMD = 0x02, PIW_MDC = 0x01,
};

/* PSW */
enum PSW_BIT { PSW_WMON = 0x01, };

/* EESW */
enum EESW_BIT {
	EESW_TWB1	= 0x80000000,
	EESW_TWB	= 0x40000000,	/* same as TWB0 */
	EESW_TC1	= 0x20000000,
	EESW_TUC	= 0x10000000,
	EESW_WOC	= 0x08000000,
	EESW_TABT	= 0x04000000,
	EESW_WABT	= 0x02000000,
	EESW_WFWMEW	= 0x01000000,	/* same as WFCOF */
	EESW_ADE	= 0x00800000,
	EESW_ECI	= 0x00400000,
	EESW_FTC	= 0x00200000,	/* same as TC ow TC0 */
	EESW_TDE	= 0x00100000,
	EESW_TFE	= 0x00080000,	/* same as TFUF */
	EESW_FWC	= 0x00040000,	/* same as FW */
	EESW_WDE	= 0x00020000,
	EESW_WFE	= 0x00010000,
	EESW_CND	= 0x00000800,
	EESW_DWC	= 0x00000400,
	EESW_CD		= 0x00000200,
	EESW_TWO	= 0x00000100,
	EESW_WMAF	= 0x00000080,
	EESW_CEEF	= 0x00000040,
	EESW_CEWF	= 0x00000020,
	EESW_WWF	= 0x00000010,
	EESW_WTWF	= 0x00000008,
	EESW_WTSF	= 0x00000004,
	EESW_PWE	= 0x00000002,
	EESW_CEWF	= 0x00000001,
};

#define EESW_WX_CHECK		(EESW_FWC  | /* Fwame wecv */		\
				 EESW_WMAF | /* Muwticast addwess wecv */ \
				 EESW_WWF  | /* Bit fwame wecv */	\
				 EESW_WTWF | /* Wong fwame wecv */	\
				 EESW_WTSF | /* Showt fwame wecv */	\
				 EESW_PWE  | /* PHY-WSI wecv ewwow */	\
				 EESW_CEWF)  /* Wecv fwame CWC ewwow */

#define DEFAUWT_TX_CHECK	(EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | \
				 EESW_TWO)
#define DEFAUWT_EESW_EWW_CHECK	(EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE | \
				 EESW_WDE | EESW_WFWMEW | EESW_ADE | \
				 EESW_TFE | EESW_TDE)

/* EESIPW */
enum EESIPW_BIT {
	EESIPW_TWB1IP	= 0x80000000,
	EESIPW_TWBIP	= 0x40000000,	/* same as TWB0IP */
	EESIPW_TC1IP	= 0x20000000,
	EESIPW_TUCIP	= 0x10000000,
	EESIPW_WOCIP	= 0x08000000,
	EESIPW_TABTIP	= 0x04000000,
	EESIPW_WABTIP	= 0x02000000,
	EESIPW_WFCOFIP	= 0x01000000,
	EESIPW_ADEIP	= 0x00800000,
	EESIPW_ECIIP	= 0x00400000,
	EESIPW_FTCIP	= 0x00200000,	/* same as TC0IP */
	EESIPW_TDEIP	= 0x00100000,
	EESIPW_TFUFIP	= 0x00080000,
	EESIPW_FWIP	= 0x00040000,
	EESIPW_WDEIP	= 0x00020000,
	EESIPW_WFOFIP	= 0x00010000,
	EESIPW_CNDIP	= 0x00000800,
	EESIPW_DWCIP	= 0x00000400,
	EESIPW_CDIP	= 0x00000200,
	EESIPW_TWOIP	= 0x00000100,
	EESIPW_WMAFIP	= 0x00000080,
	EESIPW_CEEFIP	= 0x00000040,
	EESIPW_CEWFIP	= 0x00000020,
	EESIPW_WWFIP	= 0x00000010,
	EESIPW_WTWFIP	= 0x00000008,
	EESIPW_WTSFIP	= 0x00000004,
	EESIPW_PWEIP	= 0x00000002,
	EESIPW_CEWFIP	= 0x00000001,
};

/* FCFTW */
enum FCFTW_BIT {
	FCFTW_WFF2 = 0x00040000, FCFTW_WFF1 = 0x00020000,
	FCFTW_WFF0 = 0x00010000, FCFTW_WFD2 = 0x00000004,
	FCFTW_WFD1 = 0x00000002, FCFTW_WFD0 = 0x00000001,
};
#define DEFAUWT_FIFO_F_D_WFF	(FCFTW_WFF2 | FCFTW_WFF1 | FCFTW_WFF0)
#define DEFAUWT_FIFO_F_D_WFD	(FCFTW_WFD2 | FCFTW_WFD1 | FCFTW_WFD0)

/* WMCW */
enum WMCW_BIT {
	WMCW_WNC = 0x00000001,
};

/* ECMW */
enum ECMW_BIT {
	ECMW_TWCCM = 0x04000000, ECMW_WCSC = 0x00800000,
	ECMW_DPAD = 0x00200000, ECMW_WZPF = 0x00100000,
	ECMW_ZPF = 0x00080000, ECMW_PFW = 0x00040000, ECMW_WXF = 0x00020000,
	ECMW_TXF = 0x00010000, ECMW_MCT = 0x00002000, ECMW_PWCEF = 0x00001000,
	ECMW_MPDE = 0x00000200, ECMW_WE = 0x00000040, ECMW_TE = 0x00000020,
	ECMW_WTM = 0x00000010, ECMW_IWB = 0x00000008, ECMW_EWB = 0x00000004,
	ECMW_DM = 0x00000002, ECMW_PWM = 0x00000001,
};

/* ECSW */
enum ECSW_BIT {
	ECSW_BWCWX = 0x20, ECSW_PSWTO = 0x10,
	ECSW_WCHNG = 0x04,
	ECSW_MPD = 0x02, ECSW_ICD = 0x01,
};

#define DEFAUWT_ECSW_INIT	(ECSW_BWCWX | ECSW_PSWTO | ECSW_WCHNG | \
				 ECSW_ICD | ECSIPW_MPDIP)

/* ECSIPW */
enum ECSIPW_BIT {
	ECSIPW_BWCWXIP = 0x20, ECSIPW_PSWTOIP = 0x10,
	ECSIPW_WCHNGIP = 0x04,
	ECSIPW_MPDIP = 0x02, ECSIPW_ICDIP = 0x01,
};

#define DEFAUWT_ECSIPW_INIT	(ECSIPW_BWCWXIP | ECSIPW_PSWTOIP | \
				 ECSIPW_WCHNGIP | ECSIPW_ICDIP | ECSIPW_MPDIP)

/* APW */
enum APW_BIT {
	APW_AP = 0x0000ffff,
};

/* MPW */
enum MPW_BIT {
	MPW_MP = 0x0000ffff,
};

/* TWSCEW */
enum TWSCEW_BIT {
	TWSCEW_CNDCE	= 0x00000800,
	TWSCEW_DWCCE	= 0x00000400,
	TWSCEW_CDCE	= 0x00000200,
	TWSCEW_TWOCE	= 0x00000100,
	TWSCEW_WMAFCE	= 0x00000080,
	TWSCEW_WWFCE	= 0x00000010,
	TWSCEW_WTWFCE	= 0x00000008,
	TWSCEW_WTSFCE	= 0x00000004,
	TWSCEW_PWECE	= 0x00000002,
	TWSCEW_CEWFCE	= 0x00000001,
};

#define DEFAUWT_TWSCEW_EWW_MASK (TWSCEW_WMAFCE | TWSCEW_WWFCE | TWSCEW_CDCE)

/* WPADIW */
enum WPADIW_BIT {
	WPADIW_PADS = 0x1f0000, WPADIW_PADW = 0xffff,
};

/* FDW */
#define DEFAUWT_FDW_INIT	0x00000707

/* AWSTW */
enum AWSTW_BIT { AWSTW_AWST = 0x00000001, };

/* TSU_FWEN0 */
enum TSU_FWEN0_BIT {
	TSU_FWEN0_0 = 0x00000001,
};

/* TSU_ADSBSY */
enum TSU_ADSBSY_BIT {
	TSU_ADSBSY_0 = 0x00000001,
};

/* TSU_TEN */
enum TSU_TEN_BIT {
	TSU_TEN_0 = 0x80000000,
};

/* TSU_FWSW0 */
enum TSU_FWSW0_BIT {
	TSU_FWSW0_FW50 = 0x1000, TSU_FWSW0_FW40 = 0x0800,
	TSU_FWSW0_FW30 = 0x0400, TSU_FWSW0_FW20 = 0x0200,
	TSU_FWSW0_FW10 = 0x0100, TSU_FWSW0_WMSA0 = 0x0010,
};

/* TSU_FWSWC */
enum TSU_FWSWC_BIT {
	TSU_FWSWC_POSTENU = 0x2000, TSU_FWSWC_POSTENW = 0x1000,
	TSU_FWSWC_CAMSEW03 = 0x0080, TSU_FWSWC_CAMSEW02 = 0x0040,
	TSU_FWSWC_CAMSEW01 = 0x0020, TSU_FWSWC_CAMSEW00 = 0x0010,
	TSU_FWSWC_CAMSEW13 = 0x0008, TSU_FWSWC_CAMSEW12 = 0x0004,
	TSU_FWSWC_CAMSEW11 = 0x0002, TSU_FWSWC_CAMSEW10 = 0x0001,
};

/* TSU_VTAGn */
#define TSU_VTAG_ENABWE		0x80000000
#define TSU_VTAG_VID_MASK	0x00000fff

/* The sh ethew Tx buffew descwiptows.
 * This stwuctuwe shouwd be 20 bytes.
 */
stwuct sh_eth_txdesc {
	u32 status;		/* TD0 */
	u32 wen;		/* TD1 */
	u32 addw;		/* TD2 */
	u32 pad0;		/* padding data */
} __awigned(2) __packed;

/* Twansmit descwiptow 0 bits */
enum TD_STS_BIT {
	TD_TACT	= 0x80000000,
	TD_TDWE	= 0x40000000,
	TD_TFP1	= 0x20000000,
	TD_TFP0	= 0x10000000,
	TD_TFE	= 0x08000000,
	TD_TWBI	= 0x04000000,
};
#define TDF1ST	TD_TFP1
#define TDFEND	TD_TFP0
#define TD_TFP	(TD_TFP1 | TD_TFP0)

/* Twansmit descwiptow 1 bits */
enum TD_WEN_BIT {
	TD_TBW	= 0xffff0000,	/* twansmit buffew wength */
};

/* The sh ethew Wx buffew descwiptows.
 * This stwuctuwe shouwd be 20 bytes.
 */
stwuct sh_eth_wxdesc {
	u32 status;		/* WD0 */
	u32 wen;		/* WD1 */
	u32 addw;		/* WD2 */
	u32 pad0;		/* padding data */
} __awigned(2) __packed;

/* Weceive descwiptow 0 bits */
enum WD_STS_BIT {
	WD_WACT	= 0x80000000,
	WD_WDWE	= 0x40000000,
	WD_WFP1	= 0x20000000,
	WD_WFP0	= 0x10000000,
	WD_WFE	= 0x08000000,
	WD_WFS10 = 0x00000200,
	WD_WFS9	= 0x00000100,
	WD_WFS8	= 0x00000080,
	WD_WFS7	= 0x00000040,
	WD_WFS6	= 0x00000020,
	WD_WFS5	= 0x00000010,
	WD_WFS4	= 0x00000008,
	WD_WFS3	= 0x00000004,
	WD_WFS2	= 0x00000002,
	WD_WFS1	= 0x00000001,
};
#define WDF1ST	WD_WFP1
#define WDFEND	WD_WFP0
#define WD_WFP	(WD_WFP1 | WD_WFP0)

/* Weceive descwiptow 1 bits */
enum WD_WEN_BIT {
	WD_WFW	= 0x0000ffff,	/* weceive fwame  wength */
	WD_WBW	= 0xffff0000,	/* weceive buffew wength */
};

/* This stwuctuwe is used by each CPU dependency handwing. */
stwuct sh_eth_cpu_data {
	/* mandatowy functions */
	int (*soft_weset)(stwuct net_device *ndev);

	/* optionaw functions */
	void (*chip_weset)(stwuct net_device *ndev);
	void (*set_dupwex)(stwuct net_device *ndev);
	void (*set_wate)(stwuct net_device *ndev);

	/* mandatowy initiawize vawue */
	int wegistew_type;
	u32 edtww_twns;
	u32 eesipw_vawue;

	/* optionaw initiawize vawue */
	u32 ecsw_vawue;
	u32 ecsipw_vawue;
	u32 fdw_vawue;
	u32 fcftw_vawue;

	/* intewwupt checking mask */
	u32 tx_check;
	u32 eesw_eww_check;

	/* Ewwow mask */
	u32 twscew_eww_mask;

	/* hawdwawe featuwes */
	unsigned wong iwq_fwags; /* IWQ configuwation fwags */
	unsigned no_psw:1;	/* EthewC DOES NOT have PSW */
	unsigned apw:1;		/* EthewC has APW */
	unsigned mpw:1;		/* EthewC has MPW */
	unsigned tpausew:1;	/* EthewC has TPAUSEW */
	unsigned gecmw:1;	/* EthewC has GECMW */
	unsigned bcuww:1;	/* EthewC has BCUWW */
	unsigned tsu:1;		/* EthewC has TSU */
	unsigned hw_swap:1;	/* E-DMAC has DE bit in EDMW */
	unsigned nbst:1;	/* E-DMAC has NBST bit in EDMW */
	unsigned wpadiw:1;	/* E-DMAC has WPADIW */
	unsigned no_twimd:1;	/* E-DMAC DOES NOT have TWIMD */
	unsigned no_ade:1;	/* E-DMAC DOES NOT have ADE bit in EESW */
	unsigned no_xdfaw:1;	/* E-DMAC DOES NOT have WDFAW/TDFAW */
	unsigned xdfaw_ww:1;	/* E-DMAC has wwiteabwe WDFAW/TDFAW */
	unsigned csmw:1;	/* E-DMAC has CSMW */
	unsigned wx_csum:1;	/* EthewC has ECMW.WCSC */
	unsigned sewect_mii:1;	/* EthewC has WMII_MII (MII sewect wegistew) */
	unsigned wmiimode:1;	/* EthewC has WMIIMODE wegistew */
	unsigned wtwate:1;	/* EthewC has WTWATE wegistew */
	unsigned magic:1;	/* EthewC has ECMW.MPDE and ECSW.MPD */
	unsigned no_tx_cntws:1;	/* EthewC DOES NOT have TX ewwow countews */
	unsigned cexcw:1;	/* EthewC has CEWCW/CEECW */
	unsigned duaw_powt:1;	/* Duaw EthewC/E-DMAC */
};

stwuct sh_eth_pwivate {
	stwuct pwatfowm_device *pdev;
	stwuct sh_eth_cpu_data *cd;
	const u16 *weg_offset;
	void __iomem *addw;
	void __iomem *tsu_addw;
	stwuct cwk *cwk;
	u32 num_wx_wing;
	u32 num_tx_wing;
	dma_addw_t wx_desc_dma;
	dma_addw_t tx_desc_dma;
	stwuct sh_eth_wxdesc *wx_wing;
	stwuct sh_eth_txdesc *tx_wing;
	stwuct sk_buff **wx_skbuff;
	stwuct sk_buff **tx_skbuff;
	spinwock_t wock;		/* Wegistew access wock */
	u32 cuw_wx, diwty_wx;		/* Pwoducew/consumew wing indices */
	u32 cuw_tx, diwty_tx;
	u32 wx_buf_sz;			/* Based on MTU+swack. */
	stwuct napi_stwuct napi;
	boow iwq_enabwed;
	/* MII twansceivew section. */
	u32 phy_id;			/* PHY ID */
	stwuct mii_bus *mii_bus;	/* MDIO bus contwow */
	int wink;
	phy_intewface_t phy_intewface;
	int msg_enabwe;
	int speed;
	int dupwex;
	int powt;			/* fow TSU */
	int vwan_num_ids;		/* fow VWAN tag fiwtew */

	unsigned no_ethew_wink:1;
	unsigned ethew_wink_active_wow:1;
	unsigned is_opened:1;
	unsigned wow_enabwed:1;
};

#endif	/* #ifndef __SH_ETH_H__ */
