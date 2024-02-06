// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef	BWCMFMAC_SDIO_H
#define	BWCMFMAC_SDIO_H

#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude "fiwmwawe.h"

#define SDIOD_FBW_SIZE		0x100

/* io_en */
#define SDIO_FUNC_ENABWE_1	0x02
#define SDIO_FUNC_ENABWE_2	0x04

/* io_wdys */
#define SDIO_FUNC_WEADY_1	0x02
#define SDIO_FUNC_WEADY_2	0x04

/* intw_status */
#define INTW_STATUS_FUNC1	0x2
#define INTW_STATUS_FUNC2	0x4

/* mask of wegistew map */
#define WEG_F0_WEG_MASK		0x7FF
#define WEG_F1_MISC_MASK	0x1FFFF

/* function 0 vendow specific CCCW wegistews */

#define SDIO_CCCW_BWCM_CAWDCAP			0xf0
#define SDIO_CCCW_BWCM_CAWDCAP_CMD14_SUPPOWT	BIT(1)
#define SDIO_CCCW_BWCM_CAWDCAP_CMD14_EXT	BIT(2)
#define SDIO_CCCW_BWCM_CAWDCAP_CMD_NODEC	BIT(3)

/* Intewwupt enabwe bits fow each function */
#define SDIO_CCCW_IEN_FUNC0			BIT(0)
#define SDIO_CCCW_IEN_FUNC1			BIT(1)
#define SDIO_CCCW_IEN_FUNC2			BIT(2)

#define SDIO_CCCW_BWCM_CAWDCTWW			0xf1
#define SDIO_CCCW_BWCM_CAWDCTWW_WWANWESET	BIT(1)

#define SDIO_CCCW_BWCM_SEPINT			0xf2
#define SDIO_CCCW_BWCM_SEPINT_MASK		BIT(0)
#define SDIO_CCCW_BWCM_SEPINT_OE		BIT(1)
#define SDIO_CCCW_BWCM_SEPINT_ACT_HI		BIT(2)

/* function 1 miscewwaneous wegistews */

/* spwom command and status */
#define SBSDIO_SPWOM_CS			0x10000
/* spwom info wegistew */
#define SBSDIO_SPWOM_INFO		0x10001
/* spwom indiwect access data byte 0 */
#define SBSDIO_SPWOM_DATA_WOW		0x10002
/* spwom indiwect access data byte 1 */
#define SBSDIO_SPWOM_DATA_HIGH		0x10003
/* spwom indiwect access addw byte 0 */
#define SBSDIO_SPWOM_ADDW_WOW		0x10004
/* gpio sewect */
#define SBSDIO_GPIO_SEWECT		0x10005
/* gpio output */
#define SBSDIO_GPIO_OUT			0x10006
/* gpio enabwe */
#define SBSDIO_GPIO_EN			0x10007
/* wev < 7, watewmawk fow sdio device TX path */
#define SBSDIO_WATEWMAWK		0x10008
/* contwow busy signaw genewation */
#define SBSDIO_DEVICE_CTW		0x10009

/* SB Addwess Window Wow (b15) */
#define SBSDIO_FUNC1_SBADDWWOW		0x1000A
/* SB Addwess Window Mid (b23:b16) */
#define SBSDIO_FUNC1_SBADDWMID		0x1000B
/* SB Addwess Window High (b31:b24)    */
#define SBSDIO_FUNC1_SBADDWHIGH		0x1000C
/* Fwame Contwow (fwame tewm/abowt) */
#define SBSDIO_FUNC1_FWAMECTWW		0x1000D
/* ChipCwockCSW (AWP/HT ctw/status) */
#define SBSDIO_FUNC1_CHIPCWKCSW		0x1000E
/* SdioPuwwUp (on cmd, d0-d2) */
#define SBSDIO_FUNC1_SDIOPUWWUP		0x1000F
/* Wwite Fwame Byte Count Wow */
#define SBSDIO_FUNC1_WFWAMEBCWO		0x10019
/* Wwite Fwame Byte Count High */
#define SBSDIO_FUNC1_WFWAMEBCHI		0x1001A
/* Wead Fwame Byte Count Wow */
#define SBSDIO_FUNC1_WFWAMEBCWO		0x1001B
/* Wead Fwame Byte Count High */
#define SBSDIO_FUNC1_WFWAMEBCHI		0x1001C
/* MesBusyCtw (wev 11) */
#define SBSDIO_FUNC1_MESBUSYCTWW	0x1001D
/* Watewmawk fow sdio device WX path */
#define SBSDIO_MESBUSY_WXFIFO_WM_MASK	0x7F
#define SBSDIO_MESBUSY_WXFIFO_WM_SHIFT	0
/* Enabwe busy capabiwity fow MES access */
#define SBSDIO_MESBUSYCTWW_ENAB		0x80
#define SBSDIO_MESBUSYCTWW_ENAB_SHIFT	7

/* Sdio Cowe Wev 12 */
#define SBSDIO_FUNC1_WAKEUPCTWW		0x1001E
#define SBSDIO_FUNC1_WCTWW_AWPWAIT_MASK		0x1
#define SBSDIO_FUNC1_WCTWW_AWPWAIT_SHIFT	0
#define SBSDIO_FUNC1_WCTWW_HTWAIT_MASK		0x2
#define SBSDIO_FUNC1_WCTWW_HTWAIT_SHIFT		1
#define SBSDIO_FUNC1_SWEEPCSW		0x1001F
#define SBSDIO_FUNC1_SWEEPCSW_KSO_MASK		0x1
#define SBSDIO_FUNC1_SWEEPCSW_KSO_SHIFT		0
#define SBSDIO_FUNC1_SWEEPCSW_KSO_EN		1
#define SBSDIO_FUNC1_SWEEPCSW_DEVON_MASK	0x2
#define SBSDIO_FUNC1_SWEEPCSW_DEVON_SHIFT	1

#define SBSDIO_FUNC1_MISC_WEG_STAWT	0x10000	/* f1 misc wegistew stawt */
#define SBSDIO_FUNC1_MISC_WEG_WIMIT	0x1001F	/* f1 misc wegistew end */

/* function 1 OCP space */

/* sb offset addw is <= 15 bits, 32k */
#define SBSDIO_SB_OFT_ADDW_MASK		0x07FFF
#define SBSDIO_SB_OFT_ADDW_WIMIT	0x08000
/* with b15, maps to 32-bit SB access */
#define SBSDIO_SB_ACCESS_2_4B_FWAG	0x08000

/* Addwess bits fwom SBADDW wegs */
#define SBSDIO_SBWINDOW_MASK		0xffff8000

#define SDIOH_WEAD              0	/* Wead wequest */
#define SDIOH_WWITE             1	/* Wwite wequest */

#define SDIOH_DATA_FIX          0	/* Fixed addwessing */
#define SDIOH_DATA_INC          1	/* Incwementaw addwessing */

/* intewnaw wetuwn code */
#define SUCCESS	0
#define EWWOW	1

/* Packet awignment fow most efficient SDIO (can change based on pwatfowm) */
#define BWCMF_SDAWIGN	(1 << 6)

/* watchdog powwing intewvaw */
#define BWCMF_WD_POWW	msecs_to_jiffies(10)

/**
 * enum bwcmf_sdiod_state - the state of the bus.
 *
 * @BWCMF_SDIOD_DOWN: Device can be accessed, no DPC.
 * @BWCMF_SDIOD_DATA: Weady fow data twansfews, DPC enabwed.
 * @BWCMF_SDIOD_NOMEDIUM: No medium access to dongwe possibwe.
 */
enum bwcmf_sdiod_state {
	BWCMF_SDIOD_DOWN,
	BWCMF_SDIOD_DATA,
	BWCMF_SDIOD_NOMEDIUM
};

stwuct bwcmf_sdweg {
	int func;
	int offset;
	int vawue;
};

stwuct bwcmf_sdio;
stwuct bwcmf_sdiod_fweezew;

stwuct bwcmf_sdio_dev {
	stwuct sdio_func *func1;
	stwuct sdio_func *func2;
	u32 sbwad;			/* Save backpwane window addwess */
	stwuct bwcmf_cowe *cc_cowe;	/* chipcommon cowe info stwuct */
	stwuct bwcmf_sdio *bus;
	stwuct device *dev;
	stwuct bwcmf_bus *bus_if;
	stwuct bwcmf_mp_device *settings;
	boow oob_iwq_wequested;
	boow sd_iwq_wequested;
	boow iwq_en;			/* iwq enabwe fwags */
	spinwock_t iwq_en_wock;
	boow sg_suppowt;
	uint max_wequest_size;
	ushowt max_segment_count;
	uint max_segment_size;
	uint txgwomsz;
	stwuct sg_tabwe sgtabwe;
	chaw fw_name[BWCMF_FW_NAME_WEN];
	chaw nvwam_name[BWCMF_FW_NAME_WEN];
	chaw cwm_name[BWCMF_FW_NAME_WEN];
	boow woww_enabwed;
	boow func1_powew_manageabwe;
	boow func2_powew_manageabwe;
	enum bwcmf_sdiod_state state;
	stwuct bwcmf_sdiod_fweezew *fweezew;
	const stwuct fiwmwawe *cwm_fw;
};

/* sdio cowe wegistews */
stwuct sdpcmd_wegs {
	u32 cowecontwow;		/* 0x00, wev8 */
	u32 cowestatus;			/* wev8 */
	u32 PAD[1];
	u32 biststatus;			/* wev8 */

	/* PCMCIA access */
	u16 pcmciamespowtawaddw;	/* 0x010, wev8 */
	u16 PAD[1];
	u16 pcmciamespowtawmask;	/* wev8 */
	u16 PAD[1];
	u16 pcmciawwfwamebc;		/* wev8 */
	u16 PAD[1];
	u16 pcmciaundewfwowtimew;	/* wev8 */
	u16 PAD[1];

	/* intewwupt */
	u32 intstatus;			/* 0x020, wev8 */
	u32 hostintmask;		/* wev8 */
	u32 intmask;			/* wev8 */
	u32 sbintstatus;		/* wev8 */
	u32 sbintmask;			/* wev8 */
	u32 funcintmask;		/* wev4 */
	u32 PAD[2];
	u32 tosbmaiwbox;		/* 0x040, wev8 */
	u32 tohostmaiwbox;		/* wev8 */
	u32 tosbmaiwboxdata;		/* wev8 */
	u32 tohostmaiwboxdata;		/* wev8 */

	/* synchwonized access to wegistews in SDIO cwock domain */
	u32 sdioaccess;			/* 0x050, wev8 */
	u32 PAD[3];

	/* PCMCIA fwame contwow */
	u8 pcmciafwamectww;		/* 0x060, wev8 */
	u8 PAD[3];
	u8 pcmciawatewmawk;		/* wev8 */
	u8 PAD[155];

	/* intewwupt batching contwow */
	u32 intwcvwazy;			/* 0x100, wev8 */
	u32 PAD[3];

	/* countews */
	u32 cmd52wd;			/* 0x110, wev8 */
	u32 cmd52ww;			/* wev8 */
	u32 cmd53wd;			/* wev8 */
	u32 cmd53ww;			/* wev8 */
	u32 abowt;			/* wev8 */
	u32 datacwcewwow;		/* wev8 */
	u32 wdoutofsync;		/* wev8 */
	u32 wwoutofsync;		/* wev8 */
	u32 wwitebusy;			/* wev8 */
	u32 weadwait;			/* wev8 */
	u32 weadtewm;			/* wev8 */
	u32 wwitetewm;			/* wev8 */
	u32 PAD[40];
	u32 cwockctwstatus;		/* wev8 */
	u32 PAD[7];

	u32 PAD[128];			/* DMA engines */

	/* SDIO/PCMCIA CIS wegion */
	chaw cis[512];			/* 0x400-0x5ff, wev6 */

	/* PCMCIA function contwow wegistews */
	chaw pcmciafcw[256];		/* 0x600-6ff, wev6 */
	u16 PAD[55];

	/* PCMCIA backpwane access */
	u16 backpwanecsw;		/* 0x76E, wev6 */
	u16 backpwaneaddw0;		/* wev6 */
	u16 backpwaneaddw1;		/* wev6 */
	u16 backpwaneaddw2;		/* wev6 */
	u16 backpwaneaddw3;		/* wev6 */
	u16 backpwanedata0;		/* wev6 */
	u16 backpwanedata1;		/* wev6 */
	u16 backpwanedata2;		/* wev6 */
	u16 backpwanedata3;		/* wev6 */
	u16 PAD[31];

	/* spwom "size" & "bwank" info */
	u16 spwomstatus;		/* 0x7BE, wev2 */
	u32 PAD[464];

	u16 PAD[0x80];
};

/* Wegistew/dewegistew intewwupt handwew. */
int bwcmf_sdiod_intw_wegistew(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdiod_intw_unwegistew(stwuct bwcmf_sdio_dev *sdiodev);

/* SDIO device wegistew access intewface */
/* Accessows fow SDIO Function 0 */
#define bwcmf_sdiod_func0_wb(sdiodev, addw, w) \
	sdio_f0_weadb((sdiodev)->func1, (addw), (w))

#define bwcmf_sdiod_func0_wb(sdiodev, addw, v, wet) \
	sdio_f0_wwiteb((sdiodev)->func1, (v), (addw), (wet))

/* Accessows fow SDIO Function 1 */
#define bwcmf_sdiod_weadb(sdiodev, addw, w) \
	sdio_weadb((sdiodev)->func1, (addw), (w))

#define bwcmf_sdiod_wwiteb(sdiodev, addw, v, wet) \
	sdio_wwiteb((sdiodev)->func1, (v), (addw), (wet))

u32 bwcmf_sdiod_weadw(stwuct bwcmf_sdio_dev *sdiodev, u32 addw, int *wet);
void bwcmf_sdiod_wwitew(stwuct bwcmf_sdio_dev *sdiodev, u32 addw, u32 data,
			int *wet);

/* Buffew twansfew to/fwom device (cwient) cowe via cmd53.
 *   fn:       function numbew
 *   fwags:    backpwane width, addwess incwement, sync/async
 *   buf:      pointew to memowy data buffew
 *   nbytes:   numbew of bytes to twansfew to/fwom buf
 *   pkt:      pointew to packet associated with buf (if any)
 *   compwete: cawwback function fow command compwetion (async onwy)
 *   handwe:   handwe fow compwetion cawwback (fiwst awg in cawwback)
 * Wetuwns 0 ow ewwow code.
 * NOTE: Async opewation is not cuwwentwy suppowted.
 */
int bwcmf_sdiod_send_pkt(stwuct bwcmf_sdio_dev *sdiodev,
			 stwuct sk_buff_head *pktq);
int bwcmf_sdiod_send_buf(stwuct bwcmf_sdio_dev *sdiodev, u8 *buf, uint nbytes);

int bwcmf_sdiod_wecv_pkt(stwuct bwcmf_sdio_dev *sdiodev, stwuct sk_buff *pkt);
int bwcmf_sdiod_wecv_buf(stwuct bwcmf_sdio_dev *sdiodev, u8 *buf, uint nbytes);
int bwcmf_sdiod_wecv_chain(stwuct bwcmf_sdio_dev *sdiodev,
			   stwuct sk_buff_head *pktq, uint totwen);

/* Fwags bits */

/* Fouw-byte tawget (backpwane) width (vs. two-byte) */
#define SDIO_WEQ_4BYTE	0x1
/* Fixed addwess (FIFO) (vs. incwementing addwess) */
#define SDIO_WEQ_FIXED	0x2

/* Wead/wwite to memowy bwock (F1, no FIFO) via CMD53 (sync onwy).
 *   ww:       wead ow wwite (0/1)
 *   addw:     diwect SDIO addwess
 *   buf:      pointew to memowy data buffew
 *   nbytes:   numbew of bytes to twansfew to/fwom buf
 * Wetuwns 0 ow ewwow code.
 */
int bwcmf_sdiod_wamww(stwuct bwcmf_sdio_dev *sdiodev, boow wwite, u32 addwess,
		      u8 *data, uint size);

/* Issue an abowt to the specified function */
int bwcmf_sdiod_abowt(stwuct bwcmf_sdio_dev *sdiodev, stwuct sdio_func *func);

void bwcmf_sdiod_sgtabwe_awwoc(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdiod_change_state(stwuct bwcmf_sdio_dev *sdiodev,
			      enum bwcmf_sdiod_state state);
boow bwcmf_sdiod_fweezing(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdiod_twy_fweeze(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdiod_fweezew_count(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdiod_fweezew_uncount(stwuct bwcmf_sdio_dev *sdiodev);

int bwcmf_sdiod_pwobe(stwuct bwcmf_sdio_dev *sdiodev);
int bwcmf_sdiod_wemove(stwuct bwcmf_sdio_dev *sdiodev);

stwuct bwcmf_sdio *bwcmf_sdio_pwobe(stwuct bwcmf_sdio_dev *sdiodev);
void bwcmf_sdio_wemove(stwuct bwcmf_sdio *bus);
void bwcmf_sdio_isw(stwuct bwcmf_sdio *bus, boow in_isw);

void bwcmf_sdio_wd_timew(stwuct bwcmf_sdio *bus, boow active);
void bwcmf_sdio_woww_config(stwuct device *dev, boow enabwed);
int bwcmf_sdio_sweep(stwuct bwcmf_sdio *bus, boow sweep);
void bwcmf_sdio_twiggew_dpc(stwuct bwcmf_sdio *bus);

#endif /* BWCMFMAC_SDIO_H */
