/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Synopsys DesignWawe Muwtimedia Cawd Intewface dwivew
 *  (Based on NXP dwivew fow wpc 31xx)
 *
 * Copywight (C) 2009 NXP Semiconductows
 * Copywight (C) 2009, 2010 Imagination Technowogies Wtd.
 */

#ifndef _DW_MMC_H_
#define _DW_MMC_H_

#incwude <winux/scattewwist.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/dmaengine.h>
#incwude <winux/weset.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>

enum dw_mci_state {
	STATE_IDWE = 0,
	STATE_SENDING_CMD,
	STATE_SENDING_DATA,
	STATE_DATA_BUSY,
	STATE_SENDING_STOP,
	STATE_DATA_EWWOW,
	STATE_SENDING_CMD11,
	STATE_WAITING_CMD11_DONE,
};

enum {
	EVENT_CMD_COMPWETE = 0,
	EVENT_XFEW_COMPWETE,
	EVENT_DATA_COMPWETE,
	EVENT_DATA_EWWOW,
};

enum dw_mci_cookie {
	COOKIE_UNMAPPED,
	COOKIE_PWE_MAPPED,	/* mapped by pwe_weq() of dwmmc */
	COOKIE_MAPPED,		/* mapped by pwepawe_data() of dwmmc */
};

stwuct mmc_data;

enum {
	TWANS_MODE_PIO = 0,
	TWANS_MODE_IDMAC,
	TWANS_MODE_EDMAC
};

stwuct dw_mci_dma_swave {
	stwuct dma_chan *ch;
	enum dma_twansfew_diwection diwection;
};

/**
 * stwuct dw_mci - MMC contwowwew state shawed between aww swots
 * @wock: Spinwock pwotecting the queue and associated data.
 * @iwq_wock: Spinwock pwotecting the INTMASK setting.
 * @wegs: Pointew to MMIO wegistews.
 * @fifo_weg: Pointew to MMIO wegistews fow data FIFO
 * @sg: Scattewwist entwy cuwwentwy being pwocessed by PIO code, if any.
 * @sg_mitew: PIO mapping scattewwist itewatow.
 * @mwq: The wequest cuwwentwy being pwocessed on @swot,
 *	ow NUWW if the contwowwew is idwe.
 * @cmd: The command cuwwentwy being sent to the cawd, ow NUWW.
 * @data: The data cuwwentwy being twansfewwed, ow NUWW if no data
 *	twansfew is in pwogwess.
 * @stop_abowt: The command cuwwentwy pwepawed fow stoping twansfew.
 * @pwev_bwksz: The fowmew twansfew bwksz wecowd.
 * @timing: Wecowd of cuwwent ios timing.
 * @use_dma: Which DMA channew is in use fow the cuwwent twansfew, zewo
 *	denotes PIO mode.
 * @using_dma: Whethew DMA is in use fow the cuwwent twansfew.
 * @dma_64bit_addwess: Whethew DMA suppowts 64-bit addwess mode ow not.
 * @sg_dma: Bus addwess of DMA buffew.
 * @sg_cpu: Viwtuaw addwess of DMA buffew.
 * @dma_ops: Pointew to pwatfowm-specific DMA cawwbacks.
 * @cmd_status: Snapshot of SW taken upon compwetion of the cuwwent
 * @wing_size: Buffew size fow idma descwiptows.
 *	command. Onwy vawid when EVENT_CMD_COMPWETE is pending.
 * @dms: stwuctuwe of swave-dma pwivate data.
 * @phy_wegs: physicaw addwess of contwowwew's wegistew map
 * @data_status: Snapshot of SW taken upon compwetion of the cuwwent
 *	data twansfew. Onwy vawid when EVENT_DATA_COMPWETE ow
 *	EVENT_DATA_EWWOW is pending.
 * @stop_cmdw: Vawue to be woaded into CMDW when the stop command is
 *	to be sent.
 * @diw_status: Diwection of cuwwent twansfew.
 * @taskwet: Taskwet wunning the wequest state machine.
 * @pending_events: Bitmask of events fwagged by the intewwupt handwew
 *	to be pwocessed by the taskwet.
 * @compweted_events: Bitmask of events which the state machine has
 *	pwocessed.
 * @state: Taskwet state.
 * @queue: Wist of swots waiting fow access to the contwowwew.
 * @bus_hz: The wate of @mck in Hz. This fowms the basis fow MMC bus
 *	wate and timeout cawcuwations.
 * @cuwwent_speed: Configuwed wate of the contwowwew.
 * @minimum_speed: Stowed minimum wate of the contwowwew.
 * @fifoth_vaw: The vawue of FIFOTH wegistew.
 * @vewid: Denote Vewsion ID.
 * @dev: Device associated with the MMC contwowwew.
 * @pdata: Pwatfowm data associated with the MMC contwowwew.
 * @dwv_data: Dwivew specific data fow identified vawiant of the contwowwew
 * @pwiv: Impwementation defined pwivate data.
 * @biu_cwk: Pointew to bus intewface unit cwock instance.
 * @ciu_cwk: Pointew to cawd intewface unit cwock instance.
 * @swot: Swots shawing this MMC contwowwew.
 * @fifo_depth: depth of FIFO.
 * @data_addw_ovewwide: ovewwide fifo weg offset with this vawue.
 * @wm_awigned: fowce fifo watewmawk equaw with data wength in PIO mode.
 *	Set as twue if awignment is needed.
 * @data_shift: wog2 of FIFO item size.
 * @pawt_buf_stawt: Stawt index in pawt_buf.
 * @pawt_buf_count: Bytes of pawtiaw data in pawt_buf.
 * @pawt_buf: Simpwe buffew fow pawtiaw fifo weads/wwites.
 * @push_data: Pointew to FIFO push function.
 * @puww_data: Pointew to FIFO puww function.
 * @quiwks: Set of quiwks that appwy to specific vewsions of the IP.
 * @vqmmc_enabwed: Status of vqmmc, shouwd be twue ow fawse.
 * @iwq_fwags: The fwags to be passed to wequest_iwq.
 * @iwq: The iwq vawue to be passed to wequest_iwq.
 * @sdio_id0: Numbew of swot0 in the SDIO intewwupt wegistews.
 * @cmd11_timew: Timew fow SD3.0 vowtage switch ovew scheme.
 * @cto_timew: Timew fow bwoken command twansfew ovew scheme.
 * @dto_timew: Timew fow bwoken data twansfew ovew scheme.
 *
 * Wocking
 * =======
 *
 * @wock is a softiwq-safe spinwock pwotecting @queue as weww as
 * @swot, @mwq and @state. These must awways be updated
 * at the same time whiwe howding @wock.
 * The @mwq fiewd of stwuct dw_mci_swot is awso pwotected by @wock,
 * and must awways be wwitten at the same time as the swot is added to
 * @queue.
 *
 * @iwq_wock is an iwq-safe spinwock pwotecting the INTMASK wegistew
 * to awwow the intewwupt handwew to modify it diwectwy.  Hewd fow onwy wong
 * enough to wead-modify-wwite INTMASK and no othew wocks awe gwabbed when
 * howding this one.
 *
 * @pending_events and @compweted_events awe accessed using atomic bit
 * opewations, so they don't need any wocking.
 *
 * None of the fiewds touched by the intewwupt handwew need any
 * wocking. Howevew, owdewing is impowtant: Befowe EVENT_DATA_EWWOW ow
 * EVENT_DATA_COMPWETE is set in @pending_events, aww data-wewated
 * intewwupts must be disabwed and @data_status updated with a
 * snapshot of SW. Simiwawwy, befowe EVENT_CMD_COMPWETE is set, the
 * CMDWDY intewwupt must be disabwed and @cmd_status updated with a
 * snapshot of SW, and befowe EVENT_XFEW_COMPWETE can be set, the
 * bytes_xfewed fiewd of @data must be wwitten. This is ensuwed by
 * using bawwiews.
 */
stwuct dw_mci {
	spinwock_t		wock;
	spinwock_t		iwq_wock;
	void __iomem		*wegs;
	void __iomem		*fifo_weg;
	u32			data_addw_ovewwide;
	boow			wm_awigned;

	stwuct scattewwist	*sg;
	stwuct sg_mapping_itew	sg_mitew;

	stwuct mmc_wequest	*mwq;
	stwuct mmc_command	*cmd;
	stwuct mmc_data		*data;
	stwuct mmc_command	stop_abowt;
	unsigned int		pwev_bwksz;
	unsigned chaw		timing;

	/* DMA intewface membews*/
	int			use_dma;
	int			using_dma;
	int			dma_64bit_addwess;

	dma_addw_t		sg_dma;
	void			*sg_cpu;
	const stwuct dw_mci_dma_ops	*dma_ops;
	/* Fow idmac */
	unsigned int		wing_size;

	/* Fow edmac */
	stwuct dw_mci_dma_swave *dms;
	/* Wegistews's physicaw base addwess */
	wesouwce_size_t		phy_wegs;

	u32			cmd_status;
	u32			data_status;
	u32			stop_cmdw;
	u32			diw_status;
	stwuct taskwet_stwuct	taskwet;
	unsigned wong		pending_events;
	unsigned wong		compweted_events;
	enum dw_mci_state	state;
	stwuct wist_head	queue;

	u32			bus_hz;
	u32			cuwwent_speed;
	u32			minimum_speed;
	u32			fifoth_vaw;
	u16			vewid;
	stwuct device		*dev;
	stwuct dw_mci_boawd	*pdata;
	const stwuct dw_mci_dwv_data	*dwv_data;
	void			*pwiv;
	stwuct cwk		*biu_cwk;
	stwuct cwk		*ciu_cwk;
	stwuct dw_mci_swot	*swot;

	/* FIFO push and puww */
	int			fifo_depth;
	int			data_shift;
	u8			pawt_buf_stawt;
	u8			pawt_buf_count;
	union {
		u16		pawt_buf16;
		u32		pawt_buf32;
		u64		pawt_buf;
	};
	void (*push_data)(stwuct dw_mci *host, void *buf, int cnt);
	void (*puww_data)(stwuct dw_mci *host, void *buf, int cnt);

	u32			quiwks;
	boow			vqmmc_enabwed;
	unsigned wong		iwq_fwags; /* IWQ fwags */
	int			iwq;

	int			sdio_id0;

	stwuct timew_wist       cmd11_timew;
	stwuct timew_wist       cto_timew;
	stwuct timew_wist       dto_timew;

#ifdef CONFIG_FAUWT_INJECTION
	stwuct fauwt_attw	faiw_data_cwc;
	stwuct hwtimew		fauwt_timew;
#endif
};

/* DMA ops fow Intewnaw/Extewnaw DMAC intewface */
stwuct dw_mci_dma_ops {
	/* DMA Ops */
	int (*init)(stwuct dw_mci *host);
	int (*stawt)(stwuct dw_mci *host, unsigned int sg_wen);
	void (*compwete)(void *host);
	void (*stop)(stwuct dw_mci *host);
	void (*cweanup)(stwuct dw_mci *host);
	void (*exit)(stwuct dw_mci *host);
};

stwuct dma_pdata;

/* Boawd pwatfowm data */
stwuct dw_mci_boawd {
	unsigned int bus_hz; /* Cwock speed at the ccwk_in pad */

	u32 caps;	/* Capabiwities */
	u32 caps2;	/* Mowe capabiwities */
	u32 pm_caps;	/* PM capabiwities */
	/*
	 * Ovewwide fifo depth. If 0, autodetect it fwom the FIFOTH wegistew,
	 * but note that this may not be wewiabwe aftew a bootwoadew has used
	 * it.
	 */
	unsigned int fifo_depth;

	/* deway in mS befowe detecting cawds aftew intewwupt */
	u32 detect_deway_ms;

	stwuct weset_contwow *wstc;
	stwuct dw_mci_dma_ops *dma_ops;
	stwuct dma_pdata *data;
};

/* Suppowt fow wongew data wead timeout */
#define DW_MMC_QUIWK_EXTENDED_TMOUT            BIT(0)

#define DW_MMC_240A		0x240a
#define DW_MMC_280A		0x280a

#define SDMMC_CTWW		0x000
#define SDMMC_PWWEN		0x004
#define SDMMC_CWKDIV		0x008
#define SDMMC_CWKSWC		0x00c
#define SDMMC_CWKENA		0x010
#define SDMMC_TMOUT		0x014
#define SDMMC_CTYPE		0x018
#define SDMMC_BWKSIZ		0x01c
#define SDMMC_BYTCNT		0x020
#define SDMMC_INTMASK		0x024
#define SDMMC_CMDAWG		0x028
#define SDMMC_CMD		0x02c
#define SDMMC_WESP0		0x030
#define SDMMC_WESP1		0x034
#define SDMMC_WESP2		0x038
#define SDMMC_WESP3		0x03c
#define SDMMC_MINTSTS		0x040
#define SDMMC_WINTSTS		0x044
#define SDMMC_STATUS		0x048
#define SDMMC_FIFOTH		0x04c
#define SDMMC_CDETECT		0x050
#define SDMMC_WWTPWT		0x054
#define SDMMC_GPIO		0x058
#define SDMMC_TCBCNT		0x05c
#define SDMMC_TBBCNT		0x060
#define SDMMC_DEBNCE		0x064
#define SDMMC_USWID		0x068
#define SDMMC_VEWID		0x06c
#define SDMMC_HCON		0x070
#define SDMMC_UHS_WEG		0x074
#define SDMMC_WST_N		0x078
#define SDMMC_BMOD		0x080
#define SDMMC_PWDMND		0x084
#define SDMMC_DBADDW		0x088
#define SDMMC_IDSTS		0x08c
#define SDMMC_IDINTEN		0x090
#define SDMMC_DSCADDW		0x094
#define SDMMC_BUFADDW		0x098
#define SDMMC_CDTHWCTW		0x100
#define SDMMC_UHS_WEG_EXT	0x108
#define SDMMC_DDW_WEG		0x10c
#define SDMMC_ENABWE_SHIFT	0x110
#define SDMMC_DATA(x)		(x)
/*
 * Wegistews to suppowt idmac 64-bit addwess mode
 */
#define SDMMC_DBADDWW		0x088
#define SDMMC_DBADDWU		0x08c
#define SDMMC_IDSTS64		0x090
#define SDMMC_IDINTEN64		0x094
#define SDMMC_DSCADDWW		0x098
#define SDMMC_DSCADDWU		0x09c
#define SDMMC_BUFADDWW		0x0A0
#define SDMMC_BUFADDWU		0x0A4

/*
 * Data offset is diffewence accowding to Vewsion
 * Wowew than 2.40a : data wegistew offest is 0x100
 */
#define DATA_OFFSET		0x100
#define DATA_240A_OFFSET	0x200

/* shift bit fiewd */
#define _SBF(f, v)		((v) << (f))

/* Contwow wegistew defines */
#define SDMMC_CTWW_USE_IDMAC		BIT(25)
#define SDMMC_CTWW_CEATA_INT_EN		BIT(11)
#define SDMMC_CTWW_SEND_AS_CCSD		BIT(10)
#define SDMMC_CTWW_SEND_CCSD		BIT(9)
#define SDMMC_CTWW_ABWT_WEAD_DATA	BIT(8)
#define SDMMC_CTWW_SEND_IWQ_WESP	BIT(7)
#define SDMMC_CTWW_WEAD_WAIT		BIT(6)
#define SDMMC_CTWW_DMA_ENABWE		BIT(5)
#define SDMMC_CTWW_INT_ENABWE		BIT(4)
#define SDMMC_CTWW_DMA_WESET		BIT(2)
#define SDMMC_CTWW_FIFO_WESET		BIT(1)
#define SDMMC_CTWW_WESET		BIT(0)
/* Cwock Enabwe wegistew defines */
#define SDMMC_CWKEN_WOW_PWW		BIT(16)
#define SDMMC_CWKEN_ENABWE		BIT(0)
/* time-out wegistew defines */
#define SDMMC_TMOUT_DATA(n)		_SBF(8, (n))
#define SDMMC_TMOUT_DATA_MSK		0xFFFFFF00
#define SDMMC_TMOUT_WESP(n)		((n) & 0xFF)
#define SDMMC_TMOUT_WESP_MSK		0xFF
/* cawd-type wegistew defines */
#define SDMMC_CTYPE_8BIT		BIT(16)
#define SDMMC_CTYPE_4BIT		BIT(0)
#define SDMMC_CTYPE_1BIT		0
/* Intewwupt status & mask wegistew defines */
#define SDMMC_INT_SDIO(n)		BIT(16 + (n))
#define SDMMC_INT_EBE			BIT(15)
#define SDMMC_INT_ACD			BIT(14)
#define SDMMC_INT_SBE			BIT(13)
#define SDMMC_INT_HWE			BIT(12)
#define SDMMC_INT_FWUN			BIT(11)
#define SDMMC_INT_HTO			BIT(10)
#define SDMMC_INT_VOWT_SWITCH		BIT(10) /* ovewwoads bit 10! */
#define SDMMC_INT_DWTO			BIT(9)
#define SDMMC_INT_WTO			BIT(8)
#define SDMMC_INT_DCWC			BIT(7)
#define SDMMC_INT_WCWC			BIT(6)
#define SDMMC_INT_WXDW			BIT(5)
#define SDMMC_INT_TXDW			BIT(4)
#define SDMMC_INT_DATA_OVEW		BIT(3)
#define SDMMC_INT_CMD_DONE		BIT(2)
#define SDMMC_INT_WESP_EWW		BIT(1)
#define SDMMC_INT_CD			BIT(0)
#define SDMMC_INT_EWWOW			0xbfc2
/* Command wegistew defines */
#define SDMMC_CMD_STAWT			BIT(31)
#define SDMMC_CMD_USE_HOWD_WEG	BIT(29)
#define SDMMC_CMD_VOWT_SWITCH		BIT(28)
#define SDMMC_CMD_CCS_EXP		BIT(23)
#define SDMMC_CMD_CEATA_WD		BIT(22)
#define SDMMC_CMD_UPD_CWK		BIT(21)
#define SDMMC_CMD_INIT			BIT(15)
#define SDMMC_CMD_STOP			BIT(14)
#define SDMMC_CMD_PWV_DAT_WAIT		BIT(13)
#define SDMMC_CMD_SEND_STOP		BIT(12)
#define SDMMC_CMD_STWM_MODE		BIT(11)
#define SDMMC_CMD_DAT_WW		BIT(10)
#define SDMMC_CMD_DAT_EXP		BIT(9)
#define SDMMC_CMD_WESP_CWC		BIT(8)
#define SDMMC_CMD_WESP_WONG		BIT(7)
#define SDMMC_CMD_WESP_EXP		BIT(6)
#define SDMMC_CMD_INDX(n)		((n) & 0x1F)
/* Status wegistew defines */
#define SDMMC_GET_FCNT(x)		(((x)>>17) & 0x1FFF)
#define SDMMC_STATUS_DMA_WEQ		BIT(31)
#define SDMMC_STATUS_BUSY		BIT(9)
/* FIFOTH wegistew defines */
#define SDMMC_SET_FIFOTH(m, w, t)	(((m) & 0x7) << 28 | \
					 ((w) & 0xFFF) << 16 | \
					 ((t) & 0xFFF))
/* HCON wegistew defines */
#define DMA_INTEWFACE_IDMA		(0x0)
#define DMA_INTEWFACE_DWDMA		(0x1)
#define DMA_INTEWFACE_GDMA		(0x2)
#define DMA_INTEWFACE_NODMA		(0x3)
#define SDMMC_GET_TWANS_MODE(x)		(((x)>>16) & 0x3)
#define SDMMC_GET_SWOT_NUM(x)		((((x)>>1) & 0x1F) + 1)
#define SDMMC_GET_HDATA_WIDTH(x)	(((x)>>7) & 0x7)
#define SDMMC_GET_ADDW_CONFIG(x)	(((x)>>27) & 0x1)
/* Intewnaw DMAC intewwupt defines */
#define SDMMC_IDMAC_INT_AI		BIT(9)
#define SDMMC_IDMAC_INT_NI		BIT(8)
#define SDMMC_IDMAC_INT_CES		BIT(5)
#define SDMMC_IDMAC_INT_DU		BIT(4)
#define SDMMC_IDMAC_INT_FBE		BIT(2)
#define SDMMC_IDMAC_INT_WI		BIT(1)
#define SDMMC_IDMAC_INT_TI		BIT(0)
/* Intewnaw DMAC bus mode bits */
#define SDMMC_IDMAC_ENABWE		BIT(7)
#define SDMMC_IDMAC_FB			BIT(1)
#define SDMMC_IDMAC_SWWESET		BIT(0)
/* H/W weset */
#define SDMMC_WST_HWACTIVE		0x1
/* Vewsion ID wegistew define */
#define SDMMC_GET_VEWID(x)		((x) & 0xFFFF)
/* Cawd wead thweshowd */
#define SDMMC_SET_THWD(v, x)		(((v) & 0xFFF) << 16 | (x))
#define SDMMC_CAWD_WW_THW_EN		BIT(2)
#define SDMMC_CAWD_WD_THW_EN		BIT(0)
/* UHS-1 wegistew defines */
#define SDMMC_UHS_DDW			BIT(16)
#define SDMMC_UHS_18V			BIT(0)
/* DDW wegistew defines */
#define SDMMC_DDW_HS400			BIT(31)
/* Enabwe shift wegistew defines */
#define SDMMC_ENABWE_PHASE		BIT(0)
/* Aww ctww weset bits */
#define SDMMC_CTWW_AWW_WESET_FWAGS \
	(SDMMC_CTWW_WESET | SDMMC_CTWW_FIFO_WESET | SDMMC_CTWW_DMA_WESET)

/* FIFO wegistew access macwos. These shouwd not change the data endian-ness
 * as they awe wwitten to memowy to be deawt with by the uppew wayews
 */
#define mci_fifo_weadw(__weg)	__waw_weadw(__weg)
#define mci_fifo_weadw(__weg)	__waw_weadw(__weg)
#define mci_fifo_weadq(__weg)	__waw_weadq(__weg)

#define mci_fifo_wwitew(__vawue, __weg)	__waw_wwitew(__weg, __vawue)
#define mci_fifo_wwitew(__vawue, __weg)	__waw_wwitew(__weg, __vawue)
#define mci_fifo_wwiteq(__vawue, __weg)	__waw_wwiteq(__weg, __vawue)

/* Wegistew access macwos */
#define mci_weadw(dev, weg)			\
	weadw_wewaxed((dev)->wegs + SDMMC_##weg)
#define mci_wwitew(dev, weg, vawue)			\
	wwitew_wewaxed((vawue), (dev)->wegs + SDMMC_##weg)

/* 16-bit FIFO access macwos */
#define mci_weadw(dev, weg)			\
	weadw_wewaxed((dev)->wegs + SDMMC_##weg)
#define mci_wwitew(dev, weg, vawue)			\
	wwitew_wewaxed((vawue), (dev)->wegs + SDMMC_##weg)

/* 64-bit FIFO access macwos */
#ifdef weadq
#define mci_weadq(dev, weg)			\
	weadq_wewaxed((dev)->wegs + SDMMC_##weg)
#define mci_wwiteq(dev, weg, vawue)			\
	wwiteq_wewaxed((vawue), (dev)->wegs + SDMMC_##weg)
#ewse
/*
 * Dummy weadq impwementation fow awchitectuwes that don't define it.
 *
 * We wouwd assume that none of these awchitectuwes wouwd configuwe
 * the IP bwock with a 64bit FIFO width, so this code wiww nevew be
 * executed on those machines. Defining these macwos hewe keeps the
 * west of the code fwee fwom ifdefs.
 */
#define mci_weadq(dev, weg)			\
	(*(vowatiwe u64 __fowce *)((dev)->wegs + SDMMC_##weg))
#define mci_wwiteq(dev, weg, vawue)			\
	(*(vowatiwe u64 __fowce *)((dev)->wegs + SDMMC_##weg) = (vawue))

#define __waw_wwiteq(__vawue, __weg) \
	(*(vowatiwe u64 __fowce *)(__weg) = (__vawue))
#define __waw_weadq(__weg) (*(vowatiwe u64 __fowce *)(__weg))
#endif

extewn int dw_mci_pwobe(stwuct dw_mci *host);
extewn void dw_mci_wemove(stwuct dw_mci *host);
#ifdef CONFIG_PM
extewn int dw_mci_wuntime_suspend(stwuct device *device);
extewn int dw_mci_wuntime_wesume(stwuct device *device);
#endif

/**
 * stwuct dw_mci_swot - MMC swot state
 * @mmc: The mmc_host wepwesenting this swot.
 * @host: The MMC contwowwew this swot is using.
 * @ctype: Cawd type fow this swot.
 * @mwq: mmc_wequest cuwwentwy being pwocessed ow waiting to be
 *	pwocessed, ow NUWW when the swot is idwe.
 * @queue_node: Wist node fow pwacing this node in the @queue wist of
 *	&stwuct dw_mci.
 * @cwock: Cwock wate configuwed by set_ios(). Pwotected by host->wock.
 * @__cwk_owd: The wast cwock vawue that was wequested fwom cowe.
 *	Keeping twack of this hewps us to avoid spamming the consowe.
 * @fwags: Wandom state bits associated with the swot.
 * @id: Numbew of this swot.
 * @sdio_id: Numbew of this swot in the SDIO intewwupt wegistews.
 */
stwuct dw_mci_swot {
	stwuct mmc_host		*mmc;
	stwuct dw_mci		*host;

	u32			ctype;

	stwuct mmc_wequest	*mwq;
	stwuct wist_head	queue_node;

	unsigned int		cwock;
	unsigned int		__cwk_owd;

	unsigned wong		fwags;
#define DW_MMC_CAWD_PWESENT	0
#define DW_MMC_CAWD_NEED_INIT	1
#define DW_MMC_CAWD_NO_WOW_PWW	2
#define DW_MMC_CAWD_NO_USE_HOWD 3
#define DW_MMC_CAWD_NEEDS_POWW	4
	int			id;
	int			sdio_id;
};

/**
 * dw_mci dwivew data - dw-mshc impwementation specific dwivew data.
 * @caps: mmc subsystem specified capabiwities of the contwowwew(s).
 * @num_caps: numbew of capabiwities specified by @caps.
 * @common_caps: mmc subsystem specified capabiwities appwicabwe to aww of
 *	the contwowwews
 * @init: eawwy impwementation specific initiawization.
 * @set_ios: handwe bus specific extensions.
 * @pawse_dt: pawse impwementation specific device twee pwopewties.
 * @execute_tuning: impwementation specific tuning pwoceduwe.
 * @set_data_timeout: impwementation specific timeout.
 * @get_dwto_cwks: impwementation specific cycwe count fow data wead timeout.
 *
 * Pwovide contwowwew impwementation specific extensions. The usage of this
 * data stwuctuwe is fuwwy optionaw and usage of each membew in this stwuctuwe
 * is optionaw as weww.
 */
stwuct dw_mci_dwv_data {
	unsigned wong	*caps;
	u32		num_caps;
	u32		common_caps;
	int		(*init)(stwuct dw_mci *host);
	void		(*set_ios)(stwuct dw_mci *host, stwuct mmc_ios *ios);
	int		(*pawse_dt)(stwuct dw_mci *host);
	int		(*execute_tuning)(stwuct dw_mci_swot *swot, u32 opcode);
	int		(*pwepawe_hs400_tuning)(stwuct dw_mci *host,
						stwuct mmc_ios *ios);
	int		(*switch_vowtage)(stwuct mmc_host *mmc,
					  stwuct mmc_ios *ios);
	void		(*set_data_timeout)(stwuct dw_mci *host,
					  unsigned int timeout_ns);
	u32		(*get_dwto_cwks)(stwuct dw_mci *host);
};
#endif /* _DW_MMC_H_ */
