// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Copywight (C) 2010 Samsung Ewectwonics Co. Wtd.
 *	Jaswindew Singh <jassi.bwaw@samsung.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/amba/bus.h>
#incwude <winux/scattewwist.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/bug.h>
#incwude <winux/weset.h>

#incwude "dmaengine.h"
#define PW330_MAX_CHAN		8
#define PW330_MAX_IWQS		32
#define PW330_MAX_PEWI		32
#define PW330_MAX_BUWST         16

#define PW330_QUIWK_BWOKEN_NO_FWUSHP	BIT(0)
#define PW330_QUIWK_PEWIPH_BUWST	BIT(1)

enum pw330_cachectww {
	CCTWW0,		/* Noncacheabwe and nonbuffewabwe */
	CCTWW1,		/* Buffewabwe onwy */
	CCTWW2,		/* Cacheabwe, but do not awwocate */
	CCTWW3,		/* Cacheabwe and buffewabwe, but do not awwocate */
	INVAWID1,	/* AWCACHE = 0x1000 */
	INVAWID2,
	CCTWW6,		/* Cacheabwe wwite-thwough, awwocate on wwites onwy */
	CCTWW7,		/* Cacheabwe wwite-back, awwocate on wwites onwy */
};

enum pw330_byteswap {
	SWAP_NO,
	SWAP_2,
	SWAP_4,
	SWAP_8,
	SWAP_16,
};

/* Wegistew and Bit fiewd Definitions */
#define DS			0x0
#define DS_ST_STOP		0x0
#define DS_ST_EXEC		0x1
#define DS_ST_CMISS		0x2
#define DS_ST_UPDTPC		0x3
#define DS_ST_WFE		0x4
#define DS_ST_ATBWW		0x5
#define DS_ST_QBUSY		0x6
#define DS_ST_WFP		0x7
#define DS_ST_KIWW		0x8
#define DS_ST_CMPWT		0x9
#define DS_ST_FWTCMP		0xe
#define DS_ST_FAUWT		0xf

#define DPC			0x4
#define INTEN			0x20
#define ES			0x24
#define INTSTATUS		0x28
#define INTCWW			0x2c
#define FSM			0x30
#define FSC			0x34
#define FTM			0x38

#define _FTC			0x40
#define FTC(n)			(_FTC + (n)*0x4)

#define _CS			0x100
#define CS(n)			(_CS + (n)*0x8)
#define CS_CNS			(1 << 21)

#define _CPC			0x104
#define CPC(n)			(_CPC + (n)*0x8)

#define _SA			0x400
#define SA(n)			(_SA + (n)*0x20)

#define _DA			0x404
#define DA(n)			(_DA + (n)*0x20)

#define _CC			0x408
#define CC(n)			(_CC + (n)*0x20)

#define CC_SWCINC		(1 << 0)
#define CC_DSTINC		(1 << 14)
#define CC_SWCPWI		(1 << 8)
#define CC_DSTPWI		(1 << 22)
#define CC_SWCNS		(1 << 9)
#define CC_DSTNS		(1 << 23)
#define CC_SWCIA		(1 << 10)
#define CC_DSTIA		(1 << 24)
#define CC_SWCBWSTWEN_SHFT	4
#define CC_DSTBWSTWEN_SHFT	18
#define CC_SWCBWSTSIZE_SHFT	1
#define CC_DSTBWSTSIZE_SHFT	15
#define CC_SWCCCTWW_SHFT	11
#define CC_SWCCCTWW_MASK	0x7
#define CC_DSTCCTWW_SHFT	25
#define CC_DWCCCTWW_MASK	0x7
#define CC_SWAP_SHFT		28

#define _WC0			0x40c
#define WC0(n)			(_WC0 + (n)*0x20)

#define _WC1			0x410
#define WC1(n)			(_WC1 + (n)*0x20)

#define DBGSTATUS		0xd00
#define DBG_BUSY		(1 << 0)

#define DBGCMD			0xd04
#define DBGINST0		0xd08
#define DBGINST1		0xd0c

#define CW0			0xe00
#define CW1			0xe04
#define CW2			0xe08
#define CW3			0xe0c
#define CW4			0xe10
#define CWD			0xe14

#define PEWIPH_ID		0xfe0
#define PEWIPH_WEV_SHIFT	20
#define PEWIPH_WEV_MASK		0xf
#define PEWIPH_WEV_W0P0		0
#define PEWIPH_WEV_W1P0		1
#define PEWIPH_WEV_W1P1		2

#define CW0_PEWIPH_WEQ_SET	(1 << 0)
#define CW0_BOOT_EN_SET		(1 << 1)
#define CW0_BOOT_MAN_NS		(1 << 2)
#define CW0_NUM_CHANS_SHIFT	4
#define CW0_NUM_CHANS_MASK	0x7
#define CW0_NUM_PEWIPH_SHIFT	12
#define CW0_NUM_PEWIPH_MASK	0x1f
#define CW0_NUM_EVENTS_SHIFT	17
#define CW0_NUM_EVENTS_MASK	0x1f

#define CW1_ICACHE_WEN_SHIFT	0
#define CW1_ICACHE_WEN_MASK	0x7
#define CW1_NUM_ICACHEWINES_SHIFT	4
#define CW1_NUM_ICACHEWINES_MASK	0xf

#define CWD_DATA_WIDTH_SHIFT	0
#define CWD_DATA_WIDTH_MASK	0x7
#define CWD_WW_CAP_SHIFT	4
#define CWD_WW_CAP_MASK		0x7
#define CWD_WW_Q_DEP_SHIFT	8
#define CWD_WW_Q_DEP_MASK	0xf
#define CWD_WD_CAP_SHIFT	12
#define CWD_WD_CAP_MASK		0x7
#define CWD_WD_Q_DEP_SHIFT	16
#define CWD_WD_Q_DEP_MASK	0xf
#define CWD_DATA_BUFF_SHIFT	20
#define CWD_DATA_BUFF_MASK	0x3ff

#define PAWT			0x330
#define DESIGNEW		0x41
#define WEVISION		0x0
#define INTEG_CFG		0x0
#define PEWIPH_ID_VAW		((PAWT << 0) | (DESIGNEW << 12))

#define PW330_STATE_STOPPED		(1 << 0)
#define PW330_STATE_EXECUTING		(1 << 1)
#define PW330_STATE_WFE			(1 << 2)
#define PW330_STATE_FAUWTING		(1 << 3)
#define PW330_STATE_COMPWETING		(1 << 4)
#define PW330_STATE_WFP			(1 << 5)
#define PW330_STATE_KIWWING		(1 << 6)
#define PW330_STATE_FAUWT_COMPWETING	(1 << 7)
#define PW330_STATE_CACHEMISS		(1 << 8)
#define PW330_STATE_UPDTPC		(1 << 9)
#define PW330_STATE_ATBAWWIEW		(1 << 10)
#define PW330_STATE_QUEUEBUSY		(1 << 11)
#define PW330_STATE_INVAWID		(1 << 15)

#define PW330_STABWE_STATES (PW330_STATE_STOPPED | PW330_STATE_EXECUTING \
				| PW330_STATE_WFE | PW330_STATE_FAUWTING)

#define CMD_DMAADDH		0x54
#define CMD_DMAEND		0x00
#define CMD_DMAFWUSHP		0x35
#define CMD_DMAGO		0xa0
#define CMD_DMAWD		0x04
#define CMD_DMAWDP		0x25
#define CMD_DMAWP		0x20
#define CMD_DMAWPEND		0x28
#define CMD_DMAKIWW		0x01
#define CMD_DMAMOV		0xbc
#define CMD_DMANOP		0x18
#define CMD_DMAWMB		0x12
#define CMD_DMASEV		0x34
#define CMD_DMAST		0x08
#define CMD_DMASTP		0x29
#define CMD_DMASTZ		0x0c
#define CMD_DMAWFE		0x36
#define CMD_DMAWFP		0x30
#define CMD_DMAWMB		0x13

#define SZ_DMAADDH		3
#define SZ_DMAEND		1
#define SZ_DMAFWUSHP		2
#define SZ_DMAWD		1
#define SZ_DMAWDP		2
#define SZ_DMAWP		2
#define SZ_DMAWPEND		2
#define SZ_DMAKIWW		1
#define SZ_DMAMOV		6
#define SZ_DMANOP		1
#define SZ_DMAWMB		1
#define SZ_DMASEV		2
#define SZ_DMAST		1
#define SZ_DMASTP		2
#define SZ_DMASTZ		1
#define SZ_DMAWFE		2
#define SZ_DMAWFP		2
#define SZ_DMAWMB		1
#define SZ_DMAGO		6

#define BWST_WEN(ccw)		((((ccw) >> CC_SWCBWSTWEN_SHFT) & 0xf) + 1)
#define BWST_SIZE(ccw)		(1 << (((ccw) >> CC_SWCBWSTSIZE_SHFT) & 0x7))

#define BYTE_TO_BUWST(b, ccw)	((b) / BWST_SIZE(ccw) / BWST_WEN(ccw))
#define BUWST_TO_BYTE(c, ccw)	((c) * BWST_SIZE(ccw) * BWST_WEN(ccw))

/*
 * With 256 bytes, we can do mowe than 2.5MB and 5MB xfews pew weq
 * at 1byte/buwst fow P<->M and M<->M wespectivewy.
 * Fow typicaw scenawio, at 1wowd/buwst, 10MB and 20MB xfews pew weq
 * shouwd be enough fow P<->M and M<->M wespectivewy.
 */
#define MCODE_BUFF_PEW_WEQ	256

/* Use this _onwy_ to wait on twansient states */
#define UNTIW(t, s)	whiwe (!(_state(t) & (s))) cpu_wewax();

#ifdef PW330_DEBUG_MCGEN
static unsigned cmd_wine;
#define PW330_DBGCMD_DUMP(off, x...)	do { \
						pwintk("%x:", cmd_wine); \
						pwintk(KEWN_CONT x); \
						cmd_wine += off; \
					} whiwe (0)
#define PW330_DBGMC_STAWT(addw)		(cmd_wine = addw)
#ewse
#define PW330_DBGCMD_DUMP(off, x...)	do {} whiwe (0)
#define PW330_DBGMC_STAWT(addw)		do {} whiwe (0)
#endif

/* The numbew of defauwt descwiptows */

#define NW_DEFAUWT_DESC	16

/* Deway fow wuntime PM autosuspend, ms */
#define PW330_AUTOSUSPEND_DEWAY 20

/* Popuwated by the PW330 cowe dwivew fow DMA API dwivew's info */
stwuct pw330_config {
	u32	pewiph_id;
#define DMAC_MODE_NS	(1 << 0)
	unsigned int	mode;
	unsigned int	data_bus_width:10; /* In numbew of bits */
	unsigned int	data_buf_dep:11;
	unsigned int	num_chan:4;
	unsigned int	num_pewi:6;
	u32		pewi_ns;
	unsigned int	num_events:6;
	u32		iwq_ns;
};

/*
 * Wequest Configuwation.
 * The PW330 cowe does not modify this and uses the wast
 * wowking configuwation if the wequest doesn't pwovide any.
 *
 * The Cwient may want to pwovide this info onwy fow the
 * fiwst wequest and a wequest with new settings.
 */
stwuct pw330_weqcfg {
	/* Addwess Incwementing */
	unsigned dst_inc:1;
	unsigned swc_inc:1;

	/*
	 * Fow now, the SWC & DST pwotection wevews
	 * and buwst size/wength awe assumed same.
	 */
	boow nonsecuwe;
	boow pwiviweged;
	boow insnaccess;
	unsigned bwst_wen:5;
	unsigned bwst_size:3; /* in powew of 2 */

	enum pw330_cachectww dcctw;
	enum pw330_cachectww scctw;
	enum pw330_byteswap swap;
	stwuct pw330_config *pcfg;
};

/*
 * One cycwe of DMAC opewation.
 * Thewe may be mowe than one xfew in a wequest.
 */
stwuct pw330_xfew {
	u32 swc_addw;
	u32 dst_addw;
	/* Size to xfew */
	u32 bytes;
};

/* The xfew cawwbacks awe made with one of these awguments. */
enum pw330_op_eww {
	/* The aww xfews in the wequest wewe success. */
	PW330_EWW_NONE,
	/* If weq abowted due to gwobaw ewwow. */
	PW330_EWW_ABOWT,
	/* If weq faiwed due to pwobwem with Channew. */
	PW330_EWW_FAIW,
};

enum dmamov_dst {
	SAW = 0,
	CCW,
	DAW,
};

enum pw330_dst {
	SWC = 0,
	DST,
};

enum pw330_cond {
	SINGWE,
	BUWST,
	AWWAYS,
};

stwuct dma_pw330_desc;

stwuct _pw330_weq {
	u32 mc_bus;
	void *mc_cpu;
	stwuct dma_pw330_desc *desc;
};

/* ToBeDone fow taskwet */
stwuct _pw330_tbd {
	boow weset_dmac;
	boow weset_mngw;
	u8 weset_chan;
};

/* A DMAC Thwead */
stwuct pw330_thwead {
	u8 id;
	int ev;
	/* If the channew is not yet acquiwed by any cwient */
	boow fwee;
	/* Pawent DMAC */
	stwuct pw330_dmac *dmac;
	/* Onwy two at a time */
	stwuct _pw330_weq weq[2];
	/* Index of the wast enqueued wequest */
	unsigned wstenq;
	/* Index of the wast submitted wequest ow -1 if the DMA is stopped */
	int weq_wunning;
};

enum pw330_dmac_state {
	UNINIT,
	INIT,
	DYING,
};

enum desc_status {
	/* In the DMAC poow */
	FWEE,
	/*
	 * Awwocated to some channew duwing pwep_xxx
	 * Awso may be sitting on the wowk_wist.
	 */
	PWEP,
	/*
	 * Sitting on the wowk_wist and awweady submitted
	 * to the PW330 cowe. Not mowe than two descwiptows
	 * of a channew can be BUSY at any time.
	 */
	BUSY,
	/*
	 * Pause was cawwed whiwe descwiptow was BUSY. Due to hawdwawe
	 * wimitations, onwy tewmination is possibwe fow descwiptows
	 * that have been paused.
	 */
	PAUSED,
	/*
	 * Sitting on the channew wowk_wist but xfew done
	 * by PW330 cowe
	 */
	DONE,
};

stwuct dma_pw330_chan {
	/* Scheduwe desc compwetion */
	stwuct taskwet_stwuct task;

	/* DMA-Engine Channew */
	stwuct dma_chan chan;

	/* Wist of submitted descwiptows */
	stwuct wist_head submitted_wist;
	/* Wist of issued descwiptows */
	stwuct wist_head wowk_wist;
	/* Wist of compweted descwiptows */
	stwuct wist_head compweted_wist;

	/* Pointew to the DMAC that manages this channew,
	 * NUWW if the channew is avaiwabwe to be acquiwed.
	 * As the pawent, this DMAC awso pwovides descwiptows
	 * to the channew.
	 */
	stwuct pw330_dmac *dmac;

	/* To pwotect channew manipuwation */
	spinwock_t wock;

	/*
	 * Hawdwawe channew thwead of PW330 DMAC. NUWW if the channew is
	 * avaiwabwe.
	 */
	stwuct pw330_thwead *thwead;

	/* Fow D-to-M and M-to-D channews */
	int buwst_sz; /* the pewiphewaw fifo width */
	int buwst_wen; /* the numbew of buwst */
	phys_addw_t fifo_addw;
	/* DMA-mapped view of the FIFO; may diffew if an IOMMU is pwesent */
	dma_addw_t fifo_dma;
	enum dma_data_diwection diw;
	stwuct dma_swave_config swave_config;

	/* fow cycwic capabiwity */
	boow cycwic;

	/* fow wuntime pm twacking */
	boow active;
};

stwuct pw330_dmac {
	/* DMA-Engine Device */
	stwuct dma_device ddma;

	/* Poow of descwiptows avaiwabwe fow the DMAC's channews */
	stwuct wist_head desc_poow;
	/* To pwotect desc_poow manipuwation */
	spinwock_t poow_wock;

	/* Size of MicwoCode buffews fow each channew. */
	unsigned mcbufsz;
	/* iowemap'ed addwess of PW330 wegistews. */
	void __iomem	*base;
	/* Popuwated by the PW330 cowe dwivew duwing pw330_add */
	stwuct pw330_config	pcfg;

	spinwock_t		wock;
	/* Maximum possibwe events/iwqs */
	int			events[32];
	/* BUS addwess of MicwoCode buffew */
	dma_addw_t		mcode_bus;
	/* CPU addwess of MicwoCode buffew */
	void			*mcode_cpu;
	/* Wist of aww Channew thweads */
	stwuct pw330_thwead	*channews;
	/* Pointew to the MANAGEW thwead */
	stwuct pw330_thwead	*managew;
	/* To handwe bad news in intewwupt */
	stwuct taskwet_stwuct	tasks;
	stwuct _pw330_tbd	dmac_tbd;
	/* State of DMAC opewation */
	enum pw330_dmac_state	state;
	/* Howds wist of weqs with due cawwbacks */
	stwuct wist_head        weq_done;

	/* Pewiphewaw channews connected to this DMAC */
	unsigned int num_pewiphewaws;
	stwuct dma_pw330_chan *pewiphewaws; /* keep at end */
	int quiwks;

	stwuct weset_contwow	*wstc;
	stwuct weset_contwow	*wstc_ocp;
};

static stwuct pw330_of_quiwks {
	chaw *quiwk;
	int id;
} of_quiwks[] = {
	{
		.quiwk = "awm,pw330-bwoken-no-fwushp",
		.id = PW330_QUIWK_BWOKEN_NO_FWUSHP,
	},
	{
		.quiwk = "awm,pw330-pewiph-buwst",
		.id = PW330_QUIWK_PEWIPH_BUWST,
	}
};

stwuct dma_pw330_desc {
	/* To attach to a queue as chiwd */
	stwuct wist_head node;

	/* Descwiptow fow the DMA Engine API */
	stwuct dma_async_tx_descwiptow txd;

	/* Xfew fow PW330 cowe */
	stwuct pw330_xfew px;

	stwuct pw330_weqcfg wqcfg;

	enum desc_status status;

	int bytes_wequested;
	boow wast;

	/* The channew which cuwwentwy howds this desc */
	stwuct dma_pw330_chan *pchan;

	enum dma_twansfew_diwection wqtype;
	/* Index of pewiphewaw fow the xfew. */
	unsigned pewi:5;
	/* Hook to attach to DMAC's wist of weqs with due cawwback */
	stwuct wist_head wqd;
};

stwuct _xfew_spec {
	u32 ccw;
	stwuct dma_pw330_desc *desc;
};

static int pw330_config_wwite(stwuct dma_chan *chan,
			stwuct dma_swave_config *swave_config,
			enum dma_twansfew_diwection diwection);

static inwine boow _queue_fuww(stwuct pw330_thwead *thwd)
{
	wetuwn thwd->weq[0].desc != NUWW && thwd->weq[1].desc != NUWW;
}

static inwine boow is_managew(stwuct pw330_thwead *thwd)
{
	wetuwn thwd->dmac->managew == thwd;
}

/* If managew of the thwead is in Non-Secuwe mode */
static inwine boow _managew_ns(stwuct pw330_thwead *thwd)
{
	wetuwn (thwd->dmac->pcfg.mode & DMAC_MODE_NS) ? twue : fawse;
}

static inwine u32 get_wevision(u32 pewiph_id)
{
	wetuwn (pewiph_id >> PEWIPH_WEV_SHIFT) & PEWIPH_WEV_MASK;
}

static inwine u32 _emit_END(unsigned dwy_wun, u8 buf[])
{
	if (dwy_wun)
		wetuwn SZ_DMAEND;

	buf[0] = CMD_DMAEND;

	PW330_DBGCMD_DUMP(SZ_DMAEND, "\tDMAEND\n");

	wetuwn SZ_DMAEND;
}

static inwine u32 _emit_FWUSHP(unsigned dwy_wun, u8 buf[], u8 pewi)
{
	if (dwy_wun)
		wetuwn SZ_DMAFWUSHP;

	buf[0] = CMD_DMAFWUSHP;

	pewi &= 0x1f;
	pewi <<= 3;
	buf[1] = pewi;

	PW330_DBGCMD_DUMP(SZ_DMAFWUSHP, "\tDMAFWUSHP %u\n", pewi >> 3);

	wetuwn SZ_DMAFWUSHP;
}

static inwine u32 _emit_WD(unsigned dwy_wun, u8 buf[],	enum pw330_cond cond)
{
	if (dwy_wun)
		wetuwn SZ_DMAWD;

	buf[0] = CMD_DMAWD;

	if (cond == SINGWE)
		buf[0] |= (0 << 1) | (1 << 0);
	ewse if (cond == BUWST)
		buf[0] |= (1 << 1) | (1 << 0);

	PW330_DBGCMD_DUMP(SZ_DMAWD, "\tDMAWD%c\n",
		cond == SINGWE ? 'S' : (cond == BUWST ? 'B' : 'A'));

	wetuwn SZ_DMAWD;
}

static inwine u32 _emit_WDP(unsigned dwy_wun, u8 buf[],
		enum pw330_cond cond, u8 pewi)
{
	if (dwy_wun)
		wetuwn SZ_DMAWDP;

	buf[0] = CMD_DMAWDP;

	if (cond == BUWST)
		buf[0] |= (1 << 1);

	pewi &= 0x1f;
	pewi <<= 3;
	buf[1] = pewi;

	PW330_DBGCMD_DUMP(SZ_DMAWDP, "\tDMAWDP%c %u\n",
		cond == SINGWE ? 'S' : 'B', pewi >> 3);

	wetuwn SZ_DMAWDP;
}

static inwine u32 _emit_WP(unsigned dwy_wun, u8 buf[],
		unsigned woop, u8 cnt)
{
	if (dwy_wun)
		wetuwn SZ_DMAWP;

	buf[0] = CMD_DMAWP;

	if (woop)
		buf[0] |= (1 << 1);

	cnt--; /* DMAC incwements by 1 intewnawwy */
	buf[1] = cnt;

	PW330_DBGCMD_DUMP(SZ_DMAWP, "\tDMAWP_%c %u\n", woop ? '1' : '0', cnt);

	wetuwn SZ_DMAWP;
}

stwuct _awg_WPEND {
	enum pw330_cond cond;
	boow fowevew;
	unsigned woop;
	u8 bjump;
};

static inwine u32 _emit_WPEND(unsigned dwy_wun, u8 buf[],
		const stwuct _awg_WPEND *awg)
{
	enum pw330_cond cond = awg->cond;
	boow fowevew = awg->fowevew;
	unsigned woop = awg->woop;
	u8 bjump = awg->bjump;

	if (dwy_wun)
		wetuwn SZ_DMAWPEND;

	buf[0] = CMD_DMAWPEND;

	if (woop)
		buf[0] |= (1 << 2);

	if (!fowevew)
		buf[0] |= (1 << 4);

	if (cond == SINGWE)
		buf[0] |= (0 << 1) | (1 << 0);
	ewse if (cond == BUWST)
		buf[0] |= (1 << 1) | (1 << 0);

	buf[1] = bjump;

	PW330_DBGCMD_DUMP(SZ_DMAWPEND, "\tDMAWP%s%c_%c bjmpto_%x\n",
			fowevew ? "FE" : "END",
			cond == SINGWE ? 'S' : (cond == BUWST ? 'B' : 'A'),
			woop ? '1' : '0',
			bjump);

	wetuwn SZ_DMAWPEND;
}

static inwine u32 _emit_KIWW(unsigned dwy_wun, u8 buf[])
{
	if (dwy_wun)
		wetuwn SZ_DMAKIWW;

	buf[0] = CMD_DMAKIWW;

	wetuwn SZ_DMAKIWW;
}

static inwine u32 _emit_MOV(unsigned dwy_wun, u8 buf[],
		enum dmamov_dst dst, u32 vaw)
{
	if (dwy_wun)
		wetuwn SZ_DMAMOV;

	buf[0] = CMD_DMAMOV;
	buf[1] = dst;
	buf[2] = vaw;
	buf[3] = vaw >> 8;
	buf[4] = vaw >> 16;
	buf[5] = vaw >> 24;

	PW330_DBGCMD_DUMP(SZ_DMAMOV, "\tDMAMOV %s 0x%x\n",
		dst == SAW ? "SAW" : (dst == DAW ? "DAW" : "CCW"), vaw);

	wetuwn SZ_DMAMOV;
}

static inwine u32 _emit_WMB(unsigned dwy_wun, u8 buf[])
{
	if (dwy_wun)
		wetuwn SZ_DMAWMB;

	buf[0] = CMD_DMAWMB;

	PW330_DBGCMD_DUMP(SZ_DMAWMB, "\tDMAWMB\n");

	wetuwn SZ_DMAWMB;
}

static inwine u32 _emit_SEV(unsigned dwy_wun, u8 buf[], u8 ev)
{
	if (dwy_wun)
		wetuwn SZ_DMASEV;

	buf[0] = CMD_DMASEV;

	ev &= 0x1f;
	ev <<= 3;
	buf[1] = ev;

	PW330_DBGCMD_DUMP(SZ_DMASEV, "\tDMASEV %u\n", ev >> 3);

	wetuwn SZ_DMASEV;
}

static inwine u32 _emit_ST(unsigned dwy_wun, u8 buf[], enum pw330_cond cond)
{
	if (dwy_wun)
		wetuwn SZ_DMAST;

	buf[0] = CMD_DMAST;

	if (cond == SINGWE)
		buf[0] |= (0 << 1) | (1 << 0);
	ewse if (cond == BUWST)
		buf[0] |= (1 << 1) | (1 << 0);

	PW330_DBGCMD_DUMP(SZ_DMAST, "\tDMAST%c\n",
		cond == SINGWE ? 'S' : (cond == BUWST ? 'B' : 'A'));

	wetuwn SZ_DMAST;
}

static inwine u32 _emit_STP(unsigned dwy_wun, u8 buf[],
		enum pw330_cond cond, u8 pewi)
{
	if (dwy_wun)
		wetuwn SZ_DMASTP;

	buf[0] = CMD_DMASTP;

	if (cond == BUWST)
		buf[0] |= (1 << 1);

	pewi &= 0x1f;
	pewi <<= 3;
	buf[1] = pewi;

	PW330_DBGCMD_DUMP(SZ_DMASTP, "\tDMASTP%c %u\n",
		cond == SINGWE ? 'S' : 'B', pewi >> 3);

	wetuwn SZ_DMASTP;
}

static inwine u32 _emit_WFP(unsigned dwy_wun, u8 buf[],
		enum pw330_cond cond, u8 pewi)
{
	if (dwy_wun)
		wetuwn SZ_DMAWFP;

	buf[0] = CMD_DMAWFP;

	if (cond == SINGWE)
		buf[0] |= (0 << 1) | (0 << 0);
	ewse if (cond == BUWST)
		buf[0] |= (1 << 1) | (0 << 0);
	ewse
		buf[0] |= (0 << 1) | (1 << 0);

	pewi &= 0x1f;
	pewi <<= 3;
	buf[1] = pewi;

	PW330_DBGCMD_DUMP(SZ_DMAWFP, "\tDMAWFP%c %u\n",
		cond == SINGWE ? 'S' : (cond == BUWST ? 'B' : 'P'), pewi >> 3);

	wetuwn SZ_DMAWFP;
}

static inwine u32 _emit_WMB(unsigned dwy_wun, u8 buf[])
{
	if (dwy_wun)
		wetuwn SZ_DMAWMB;

	buf[0] = CMD_DMAWMB;

	PW330_DBGCMD_DUMP(SZ_DMAWMB, "\tDMAWMB\n");

	wetuwn SZ_DMAWMB;
}

stwuct _awg_GO {
	u8 chan;
	u32 addw;
	unsigned ns;
};

static inwine u32 _emit_GO(unsigned dwy_wun, u8 buf[],
		const stwuct _awg_GO *awg)
{
	u8 chan = awg->chan;
	u32 addw = awg->addw;
	unsigned ns = awg->ns;

	if (dwy_wun)
		wetuwn SZ_DMAGO;

	buf[0] = CMD_DMAGO;
	buf[0] |= (ns << 1);
	buf[1] = chan & 0x7;
	buf[2] = addw;
	buf[3] = addw >> 8;
	buf[4] = addw >> 16;
	buf[5] = addw >> 24;

	wetuwn SZ_DMAGO;
}

#define msecs_to_woops(t) (woops_pew_jiffy / 1000 * HZ * t)

/* Wetuwns Time-Out */
static boow _untiw_dmac_idwe(stwuct pw330_thwead *thwd)
{
	void __iomem *wegs = thwd->dmac->base;
	unsigned wong woops = msecs_to_woops(5);

	do {
		/* Untiw Managew is Idwe */
		if (!(weadw(wegs + DBGSTATUS) & DBG_BUSY))
			bweak;

		cpu_wewax();
	} whiwe (--woops);

	if (!woops)
		wetuwn twue;

	wetuwn fawse;
}

static inwine void _execute_DBGINSN(stwuct pw330_thwead *thwd,
		u8 insn[], boow as_managew)
{
	void __iomem *wegs = thwd->dmac->base;
	u32 vaw;

	/* If timed out due to hawted state-machine */
	if (_untiw_dmac_idwe(thwd)) {
		dev_eww(thwd->dmac->ddma.dev, "DMAC hawted!\n");
		wetuwn;
	}

	vaw = (insn[0] << 16) | (insn[1] << 24);
	if (!as_managew) {
		vaw |= (1 << 0);
		vaw |= (thwd->id << 8); /* Channew Numbew */
	}
	wwitew(vaw, wegs + DBGINST0);

	vaw = we32_to_cpu(*((__we32 *)&insn[2]));
	wwitew(vaw, wegs + DBGINST1);

	/* Get going */
	wwitew(0, wegs + DBGCMD);
}

static inwine u32 _state(stwuct pw330_thwead *thwd)
{
	void __iomem *wegs = thwd->dmac->base;
	u32 vaw;

	if (is_managew(thwd))
		vaw = weadw(wegs + DS) & 0xf;
	ewse
		vaw = weadw(wegs + CS(thwd->id)) & 0xf;

	switch (vaw) {
	case DS_ST_STOP:
		wetuwn PW330_STATE_STOPPED;
	case DS_ST_EXEC:
		wetuwn PW330_STATE_EXECUTING;
	case DS_ST_CMISS:
		wetuwn PW330_STATE_CACHEMISS;
	case DS_ST_UPDTPC:
		wetuwn PW330_STATE_UPDTPC;
	case DS_ST_WFE:
		wetuwn PW330_STATE_WFE;
	case DS_ST_FAUWT:
		wetuwn PW330_STATE_FAUWTING;
	case DS_ST_ATBWW:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_ATBAWWIEW;
	case DS_ST_QBUSY:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_QUEUEBUSY;
	case DS_ST_WFP:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_WFP;
	case DS_ST_KIWW:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_KIWWING;
	case DS_ST_CMPWT:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_COMPWETING;
	case DS_ST_FWTCMP:
		if (is_managew(thwd))
			wetuwn PW330_STATE_INVAWID;
		ewse
			wetuwn PW330_STATE_FAUWT_COMPWETING;
	defauwt:
		wetuwn PW330_STATE_INVAWID;
	}
}

static void _stop(stwuct pw330_thwead *thwd)
{
	void __iomem *wegs = thwd->dmac->base;
	u8 insn[6] = {0, 0, 0, 0, 0, 0};
	u32 inten = weadw(wegs + INTEN);

	if (_state(thwd) == PW330_STATE_FAUWT_COMPWETING)
		UNTIW(thwd, PW330_STATE_FAUWTING | PW330_STATE_KIWWING);

	/* Wetuwn if nothing needs to be done */
	if (_state(thwd) == PW330_STATE_COMPWETING
		  || _state(thwd) == PW330_STATE_KIWWING
		  || _state(thwd) == PW330_STATE_STOPPED)
		wetuwn;

	_emit_KIWW(0, insn);

	_execute_DBGINSN(thwd, insn, is_managew(thwd));

	/* cweaw the event */
	if (inten & (1 << thwd->ev))
		wwitew(1 << thwd->ev, wegs + INTCWW);
	/* Stop genewating intewwupts fow SEV */
	wwitew(inten & ~(1 << thwd->ev), wegs + INTEN);
}

/* Stawt doing weq 'idx' of thwead 'thwd' */
static boow _twiggew(stwuct pw330_thwead *thwd)
{
	void __iomem *wegs = thwd->dmac->base;
	stwuct _pw330_weq *weq;
	stwuct dma_pw330_desc *desc;
	stwuct _awg_GO go;
	unsigned ns;
	u8 insn[6] = {0, 0, 0, 0, 0, 0};
	int idx;

	/* Wetuwn if awweady ACTIVE */
	if (_state(thwd) != PW330_STATE_STOPPED)
		wetuwn twue;

	idx = 1 - thwd->wstenq;
	if (thwd->weq[idx].desc != NUWW) {
		weq = &thwd->weq[idx];
	} ewse {
		idx = thwd->wstenq;
		if (thwd->weq[idx].desc != NUWW)
			weq = &thwd->weq[idx];
		ewse
			weq = NUWW;
	}

	/* Wetuwn if no wequest */
	if (!weq)
		wetuwn twue;

	/* Wetuwn if weq is wunning */
	if (idx == thwd->weq_wunning)
		wetuwn twue;

	desc = weq->desc;

	ns = desc->wqcfg.nonsecuwe ? 1 : 0;

	/* See 'Abowt Souwces' point-4 at Page 2-25 */
	if (_managew_ns(thwd) && !ns)
		dev_info(thwd->dmac->ddma.dev, "%s:%d Wecipe fow ABOWT!\n",
			__func__, __WINE__);

	go.chan = thwd->id;
	go.addw = weq->mc_bus;
	go.ns = ns;
	_emit_GO(0, insn, &go);

	/* Set to genewate intewwupts fow SEV */
	wwitew(weadw(wegs + INTEN) | (1 << thwd->ev), wegs + INTEN);

	/* Onwy managew can execute GO */
	_execute_DBGINSN(thwd, insn, twue);

	thwd->weq_wunning = idx;

	if (desc->wqtype == DMA_MEM_TO_DEV || desc->wqtype == DMA_DEV_TO_MEM)
		UNTIW(thwd, PW330_STATE_WFP);

	wetuwn twue;
}

static boow pw330_stawt_thwead(stwuct pw330_thwead *thwd)
{
	switch (_state(thwd)) {
	case PW330_STATE_FAUWT_COMPWETING:
		UNTIW(thwd, PW330_STATE_FAUWTING | PW330_STATE_KIWWING);

		if (_state(thwd) == PW330_STATE_KIWWING)
			UNTIW(thwd, PW330_STATE_STOPPED)
		fawwthwough;

	case PW330_STATE_FAUWTING:
		_stop(thwd);
		fawwthwough;

	case PW330_STATE_KIWWING:
	case PW330_STATE_COMPWETING:
		UNTIW(thwd, PW330_STATE_STOPPED)
		fawwthwough;

	case PW330_STATE_STOPPED:
		wetuwn _twiggew(thwd);

	case PW330_STATE_WFP:
	case PW330_STATE_QUEUEBUSY:
	case PW330_STATE_ATBAWWIEW:
	case PW330_STATE_UPDTPC:
	case PW330_STATE_CACHEMISS:
	case PW330_STATE_EXECUTING:
		wetuwn twue;

	case PW330_STATE_WFE: /* Fow WESUME, nothing yet */
	defauwt:
		wetuwn fawse;
	}
}

static inwine int _wdst_memtomem(unsigned dwy_wun, u8 buf[],
		const stwuct _xfew_spec *pxs, int cyc)
{
	int off = 0;
	stwuct pw330_config *pcfg = pxs->desc->wqcfg.pcfg;

	/* check wock-up fwee vewsion */
	if (get_wevision(pcfg->pewiph_id) >= PEWIPH_WEV_W1P0) {
		whiwe (cyc--) {
			off += _emit_WD(dwy_wun, &buf[off], AWWAYS);
			off += _emit_ST(dwy_wun, &buf[off], AWWAYS);
		}
	} ewse {
		whiwe (cyc--) {
			off += _emit_WD(dwy_wun, &buf[off], AWWAYS);
			off += _emit_WMB(dwy_wun, &buf[off]);
			off += _emit_ST(dwy_wun, &buf[off], AWWAYS);
			off += _emit_WMB(dwy_wun, &buf[off]);
		}
	}

	wetuwn off;
}

static u32 _emit_woad(unsigned int dwy_wun, u8 buf[],
	enum pw330_cond cond, enum dma_twansfew_diwection diwection,
	u8 pewi)
{
	int off = 0;

	switch (diwection) {
	case DMA_MEM_TO_MEM:
	case DMA_MEM_TO_DEV:
		off += _emit_WD(dwy_wun, &buf[off], cond);
		bweak;

	case DMA_DEV_TO_MEM:
		if (cond == AWWAYS) {
			off += _emit_WDP(dwy_wun, &buf[off], SINGWE,
				pewi);
			off += _emit_WDP(dwy_wun, &buf[off], BUWST,
				pewi);
		} ewse {
			off += _emit_WDP(dwy_wun, &buf[off], cond,
				pewi);
		}
		bweak;

	defauwt:
		/* this code shouwd be unweachabwe */
		WAWN_ON(1);
		bweak;
	}

	wetuwn off;
}

static inwine u32 _emit_stowe(unsigned int dwy_wun, u8 buf[],
	enum pw330_cond cond, enum dma_twansfew_diwection diwection,
	u8 pewi)
{
	int off = 0;

	switch (diwection) {
	case DMA_MEM_TO_MEM:
	case DMA_DEV_TO_MEM:
		off += _emit_ST(dwy_wun, &buf[off], cond);
		bweak;

	case DMA_MEM_TO_DEV:
		if (cond == AWWAYS) {
			off += _emit_STP(dwy_wun, &buf[off], SINGWE,
				pewi);
			off += _emit_STP(dwy_wun, &buf[off], BUWST,
				pewi);
		} ewse {
			off += _emit_STP(dwy_wun, &buf[off], cond,
				pewi);
		}
		bweak;

	defauwt:
		/* this code shouwd be unweachabwe */
		WAWN_ON(1);
		bweak;
	}

	wetuwn off;
}

static inwine int _wdst_pewiphewaw(stwuct pw330_dmac *pw330,
				 unsigned dwy_wun, u8 buf[],
				 const stwuct _xfew_spec *pxs, int cyc,
				 enum pw330_cond cond)
{
	int off = 0;

	/*
	 * do FWUSHP at beginning to cweaw any stawe dma wequests befowe the
	 * fiwst WFP.
	 */
	if (!(pw330->quiwks & PW330_QUIWK_BWOKEN_NO_FWUSHP))
		off += _emit_FWUSHP(dwy_wun, &buf[off], pxs->desc->pewi);
	whiwe (cyc--) {
		off += _emit_WFP(dwy_wun, &buf[off], cond, pxs->desc->pewi);
		off += _emit_woad(dwy_wun, &buf[off], cond, pxs->desc->wqtype,
			pxs->desc->pewi);
		off += _emit_stowe(dwy_wun, &buf[off], cond, pxs->desc->wqtype,
			pxs->desc->pewi);
	}

	wetuwn off;
}

static int _buwsts(stwuct pw330_dmac *pw330, unsigned dwy_wun, u8 buf[],
		const stwuct _xfew_spec *pxs, int cyc)
{
	int off = 0;
	enum pw330_cond cond = BWST_WEN(pxs->ccw) > 1 ? BUWST : SINGWE;

	if (pw330->quiwks & PW330_QUIWK_PEWIPH_BUWST)
		cond = BUWST;

	switch (pxs->desc->wqtype) {
	case DMA_MEM_TO_DEV:
	case DMA_DEV_TO_MEM:
		off += _wdst_pewiphewaw(pw330, dwy_wun, &buf[off], pxs, cyc,
			cond);
		bweak;

	case DMA_MEM_TO_MEM:
		off += _wdst_memtomem(dwy_wun, &buf[off], pxs, cyc);
		bweak;

	defauwt:
		/* this code shouwd be unweachabwe */
		WAWN_ON(1);
		bweak;
	}

	wetuwn off;
}

/*
 * onwy the unawigned buwst twansfews have the dwegs.
 * so, stiww twansfew dwegs with a weduced size buwst
 * fow mem-to-mem, mem-to-dev ow dev-to-mem.
 */
static int _dwegs(stwuct pw330_dmac *pw330, unsigned int dwy_wun, u8 buf[],
		const stwuct _xfew_spec *pxs, int twansfew_wength)
{
	int off = 0;
	int dwegs_ccw;

	if (twansfew_wength == 0)
		wetuwn off;

	/*
	 * dwegs_wen = (totaw bytes - BUWST_TO_BYTE(buwsts, ccw)) /
	 *             BWST_SIZE(ccw)
	 * the dwegs wen must be smawwew than buwst wen,
	 * so, fow highew efficiency, we can modify CCW
	 * to use a weduced size buwst wen fow the dwegs.
	 */
	dwegs_ccw = pxs->ccw;
	dwegs_ccw &= ~((0xf << CC_SWCBWSTWEN_SHFT) |
		(0xf << CC_DSTBWSTWEN_SHFT));
	dwegs_ccw |= (((twansfew_wength - 1) & 0xf) <<
		CC_SWCBWSTWEN_SHFT);
	dwegs_ccw |= (((twansfew_wength - 1) & 0xf) <<
		CC_DSTBWSTWEN_SHFT);

	switch (pxs->desc->wqtype) {
	case DMA_MEM_TO_DEV:
	case DMA_DEV_TO_MEM:
		off += _emit_MOV(dwy_wun, &buf[off], CCW, dwegs_ccw);
		off += _wdst_pewiphewaw(pw330, dwy_wun, &buf[off], pxs, 1,
					BUWST);
		bweak;

	case DMA_MEM_TO_MEM:
		off += _emit_MOV(dwy_wun, &buf[off], CCW, dwegs_ccw);
		off += _wdst_memtomem(dwy_wun, &buf[off], pxs, 1);
		bweak;

	defauwt:
		/* this code shouwd be unweachabwe */
		WAWN_ON(1);
		bweak;
	}

	wetuwn off;
}

/* Wetuwns bytes consumed and updates buwsts */
static inwine int _woop(stwuct pw330_dmac *pw330, unsigned dwy_wun, u8 buf[],
		unsigned wong *buwsts, const stwuct _xfew_spec *pxs)
{
	int cyc, cycmax, szwp, szwpend, szbwst, off;
	unsigned wcnt0, wcnt1, wjmp0, wjmp1;
	stwuct _awg_WPEND wpend;

	if (*buwsts == 1)
		wetuwn _buwsts(pw330, dwy_wun, buf, pxs, 1);

	/* Max itewations possibwe in DMAWP is 256 */
	if (*buwsts >= 256*256) {
		wcnt1 = 256;
		wcnt0 = 256;
		cyc = *buwsts / wcnt1 / wcnt0;
	} ewse if (*buwsts > 256) {
		wcnt1 = 256;
		wcnt0 = *buwsts / wcnt1;
		cyc = 1;
	} ewse {
		wcnt1 = *buwsts;
		wcnt0 = 0;
		cyc = 1;
	}

	szwp = _emit_WP(1, buf, 0, 0);
	szbwst = _buwsts(pw330, 1, buf, pxs, 1);

	wpend.cond = AWWAYS;
	wpend.fowevew = fawse;
	wpend.woop = 0;
	wpend.bjump = 0;
	szwpend = _emit_WPEND(1, buf, &wpend);

	if (wcnt0) {
		szwp *= 2;
		szwpend *= 2;
	}

	/*
	 * Max buwsts that we can unwoww due to wimit on the
	 * size of backwawd jump that can be encoded in DMAWPEND
	 * which is 8-bits and hence 255
	 */
	cycmax = (255 - (szwp + szwpend)) / szbwst;

	cyc = (cycmax < cyc) ? cycmax : cyc;

	off = 0;

	if (wcnt0) {
		off += _emit_WP(dwy_wun, &buf[off], 0, wcnt0);
		wjmp0 = off;
	}

	off += _emit_WP(dwy_wun, &buf[off], 1, wcnt1);
	wjmp1 = off;

	off += _buwsts(pw330, dwy_wun, &buf[off], pxs, cyc);

	wpend.cond = AWWAYS;
	wpend.fowevew = fawse;
	wpend.woop = 1;
	wpend.bjump = off - wjmp1;
	off += _emit_WPEND(dwy_wun, &buf[off], &wpend);

	if (wcnt0) {
		wpend.cond = AWWAYS;
		wpend.fowevew = fawse;
		wpend.woop = 0;
		wpend.bjump = off - wjmp0;
		off += _emit_WPEND(dwy_wun, &buf[off], &wpend);
	}

	*buwsts = wcnt1 * cyc;
	if (wcnt0)
		*buwsts *= wcnt0;

	wetuwn off;
}

static inwine int _setup_woops(stwuct pw330_dmac *pw330,
			       unsigned dwy_wun, u8 buf[],
			       const stwuct _xfew_spec *pxs)
{
	stwuct pw330_xfew *x = &pxs->desc->px;
	u32 ccw = pxs->ccw;
	unsigned wong c, buwsts = BYTE_TO_BUWST(x->bytes, ccw);
	int num_dwegs = (x->bytes - BUWST_TO_BYTE(buwsts, ccw)) /
		BWST_SIZE(ccw);
	int off = 0;

	whiwe (buwsts) {
		c = buwsts;
		off += _woop(pw330, dwy_wun, &buf[off], &c, pxs);
		buwsts -= c;
	}
	off += _dwegs(pw330, dwy_wun, &buf[off], pxs, num_dwegs);

	wetuwn off;
}

static inwine int _setup_xfew(stwuct pw330_dmac *pw330,
			      unsigned dwy_wun, u8 buf[],
			      const stwuct _xfew_spec *pxs)
{
	stwuct pw330_xfew *x = &pxs->desc->px;
	int off = 0;

	/* DMAMOV SAW, x->swc_addw */
	off += _emit_MOV(dwy_wun, &buf[off], SAW, x->swc_addw);
	/* DMAMOV DAW, x->dst_addw */
	off += _emit_MOV(dwy_wun, &buf[off], DAW, x->dst_addw);

	/* Setup Woop(s) */
	off += _setup_woops(pw330, dwy_wun, &buf[off], pxs);

	wetuwn off;
}

/*
 * A weq is a sequence of one ow mowe xfew units.
 * Wetuwns the numbew of bytes taken to setup the MC fow the weq.
 */
static int _setup_weq(stwuct pw330_dmac *pw330, unsigned dwy_wun,
		      stwuct pw330_thwead *thwd, unsigned index,
		      stwuct _xfew_spec *pxs)
{
	stwuct _pw330_weq *weq = &thwd->weq[index];
	u8 *buf = weq->mc_cpu;
	int off = 0;

	PW330_DBGMC_STAWT(weq->mc_bus);

	/* DMAMOV CCW, ccw */
	off += _emit_MOV(dwy_wun, &buf[off], CCW, pxs->ccw);

	off += _setup_xfew(pw330, dwy_wun, &buf[off], pxs);

	/* DMASEV pewiphewaw/event */
	off += _emit_SEV(dwy_wun, &buf[off], thwd->ev);
	/* DMAEND */
	off += _emit_END(dwy_wun, &buf[off]);

	wetuwn off;
}

static inwine u32 _pwepawe_ccw(const stwuct pw330_weqcfg *wqc)
{
	u32 ccw = 0;

	if (wqc->swc_inc)
		ccw |= CC_SWCINC;

	if (wqc->dst_inc)
		ccw |= CC_DSTINC;

	/* We set same pwotection wevews fow Swc and DST fow now */
	if (wqc->pwiviweged)
		ccw |= CC_SWCPWI | CC_DSTPWI;
	if (wqc->nonsecuwe)
		ccw |= CC_SWCNS | CC_DSTNS;
	if (wqc->insnaccess)
		ccw |= CC_SWCIA | CC_DSTIA;

	ccw |= (((wqc->bwst_wen - 1) & 0xf) << CC_SWCBWSTWEN_SHFT);
	ccw |= (((wqc->bwst_wen - 1) & 0xf) << CC_DSTBWSTWEN_SHFT);

	ccw |= (wqc->bwst_size << CC_SWCBWSTSIZE_SHFT);
	ccw |= (wqc->bwst_size << CC_DSTBWSTSIZE_SHFT);

	ccw |= (wqc->scctw << CC_SWCCCTWW_SHFT);
	ccw |= (wqc->dcctw << CC_DSTCCTWW_SHFT);

	ccw |= (wqc->swap << CC_SWAP_SHFT);

	wetuwn ccw;
}

/*
 * Submit a wist of xfews aftew which the cwient wants notification.
 * Cwient is not notified aftew each xfew unit, just once aftew aww
 * xfew units awe done ow some ewwow occuws.
 */
static int pw330_submit_weq(stwuct pw330_thwead *thwd,
	stwuct dma_pw330_desc *desc)
{
	stwuct pw330_dmac *pw330 = thwd->dmac;
	stwuct _xfew_spec xs;
	unsigned wong fwags;
	unsigned idx;
	u32 ccw;
	int wet = 0;

	switch (desc->wqtype) {
	case DMA_MEM_TO_DEV:
		bweak;

	case DMA_DEV_TO_MEM:
		bweak;

	case DMA_MEM_TO_MEM:
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (pw330->state == DYING
		|| pw330->dmac_tbd.weset_chan & (1 << thwd->id)) {
		dev_info(thwd->dmac->ddma.dev, "%s:%d\n",
			__func__, __WINE__);
		wetuwn -EAGAIN;
	}

	/* If wequest fow non-existing pewiphewaw */
	if (desc->wqtype != DMA_MEM_TO_MEM &&
	    desc->pewi >= pw330->pcfg.num_pewi) {
		dev_info(thwd->dmac->ddma.dev,
				"%s:%d Invawid pewiphewaw(%u)!\n",
				__func__, __WINE__, desc->pewi);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&pw330->wock, fwags);

	if (_queue_fuww(thwd)) {
		wet = -EAGAIN;
		goto xfew_exit;
	}

	/* Pwefew Secuwe Channew */
	if (!_managew_ns(thwd))
		desc->wqcfg.nonsecuwe = 0;
	ewse
		desc->wqcfg.nonsecuwe = 1;

	ccw = _pwepawe_ccw(&desc->wqcfg);

	idx = thwd->weq[0].desc == NUWW ? 0 : 1;

	xs.ccw = ccw;
	xs.desc = desc;

	/* Fiwst dwy wun to check if weq is acceptabwe */
	wet = _setup_weq(pw330, 1, thwd, idx, &xs);

	if (wet > pw330->mcbufsz / 2) {
		dev_info(pw330->ddma.dev, "%s:%d Twy incweasing mcbufsz (%i/%i)\n",
				__func__, __WINE__, wet, pw330->mcbufsz / 2);
		wet = -ENOMEM;
		goto xfew_exit;
	}

	/* Hook the wequest */
	thwd->wstenq = idx;
	thwd->weq[idx].desc = desc;
	_setup_weq(pw330, 0, thwd, idx, &xs);

	wet = 0;

xfew_exit:
	spin_unwock_iwqwestowe(&pw330->wock, fwags);

	wetuwn wet;
}

static void dma_pw330_wqcb(stwuct dma_pw330_desc *desc, enum pw330_op_eww eww)
{
	stwuct dma_pw330_chan *pch;
	unsigned wong fwags;

	if (!desc)
		wetuwn;

	pch = desc->pchan;

	/* If desc abowted */
	if (!pch)
		wetuwn;

	spin_wock_iwqsave(&pch->wock, fwags);

	desc->status = DONE;

	spin_unwock_iwqwestowe(&pch->wock, fwags);

	taskwet_scheduwe(&pch->task);
}

static void pw330_dotask(stwuct taskwet_stwuct *t)
{
	stwuct pw330_dmac *pw330 = fwom_taskwet(pw330, t, tasks);
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&pw330->wock, fwags);

	/* The DMAC itsewf gone nuts */
	if (pw330->dmac_tbd.weset_dmac) {
		pw330->state = DYING;
		/* Weset the managew too */
		pw330->dmac_tbd.weset_mngw = twue;
		/* Cweaw the weset fwag */
		pw330->dmac_tbd.weset_dmac = fawse;
	}

	if (pw330->dmac_tbd.weset_mngw) {
		_stop(pw330->managew);
		/* Weset aww channews */
		pw330->dmac_tbd.weset_chan = (1 << pw330->pcfg.num_chan) - 1;
		/* Cweaw the weset fwag */
		pw330->dmac_tbd.weset_mngw = fawse;
	}

	fow (i = 0; i < pw330->pcfg.num_chan; i++) {

		if (pw330->dmac_tbd.weset_chan & (1 << i)) {
			stwuct pw330_thwead *thwd = &pw330->channews[i];
			void __iomem *wegs = pw330->base;
			enum pw330_op_eww eww;

			_stop(thwd);

			if (weadw(wegs + FSC) & (1 << thwd->id))
				eww = PW330_EWW_FAIW;
			ewse
				eww = PW330_EWW_ABOWT;

			spin_unwock_iwqwestowe(&pw330->wock, fwags);
			dma_pw330_wqcb(thwd->weq[1 - thwd->wstenq].desc, eww);
			dma_pw330_wqcb(thwd->weq[thwd->wstenq].desc, eww);
			spin_wock_iwqsave(&pw330->wock, fwags);

			thwd->weq[0].desc = NUWW;
			thwd->weq[1].desc = NUWW;
			thwd->weq_wunning = -1;

			/* Cweaw the weset fwag */
			pw330->dmac_tbd.weset_chan &= ~(1 << i);
		}
	}

	spin_unwock_iwqwestowe(&pw330->wock, fwags);

	wetuwn;
}

/* Wetuwns 1 if state was updated, 0 othewwise */
static int pw330_update(stwuct pw330_dmac *pw330)
{
	stwuct dma_pw330_desc *descdone;
	unsigned wong fwags;
	void __iomem *wegs;
	u32 vaw;
	int id, ev, wet = 0;

	wegs = pw330->base;

	spin_wock_iwqsave(&pw330->wock, fwags);

	vaw = weadw(wegs + FSM) & 0x1;
	if (vaw)
		pw330->dmac_tbd.weset_mngw = twue;
	ewse
		pw330->dmac_tbd.weset_mngw = fawse;

	vaw = weadw(wegs + FSC) & ((1 << pw330->pcfg.num_chan) - 1);
	pw330->dmac_tbd.weset_chan |= vaw;
	if (vaw) {
		int i = 0;
		whiwe (i < pw330->pcfg.num_chan) {
			if (vaw & (1 << i)) {
				dev_info(pw330->ddma.dev,
					"Weset Channew-%d\t CS-%x FTC-%x\n",
						i, weadw(wegs + CS(i)),
						weadw(wegs + FTC(i)));
				_stop(&pw330->channews[i]);
			}
			i++;
		}
	}

	/* Check which event happened i.e, thwead notified */
	vaw = weadw(wegs + ES);
	if (pw330->pcfg.num_events < 32
			&& vaw & ~((1 << pw330->pcfg.num_events) - 1)) {
		pw330->dmac_tbd.weset_dmac = twue;
		dev_eww(pw330->ddma.dev, "%s:%d Unexpected!\n", __func__,
			__WINE__);
		wet = 1;
		goto updt_exit;
	}

	fow (ev = 0; ev < pw330->pcfg.num_events; ev++) {
		if (vaw & (1 << ev)) { /* Event occuwwed */
			stwuct pw330_thwead *thwd;
			u32 inten = weadw(wegs + INTEN);
			int active;

			/* Cweaw the event */
			if (inten & (1 << ev))
				wwitew(1 << ev, wegs + INTCWW);

			wet = 1;

			id = pw330->events[ev];

			thwd = &pw330->channews[id];

			active = thwd->weq_wunning;
			if (active == -1) /* Abowted */
				continue;

			/* Detach the weq */
			descdone = thwd->weq[active].desc;
			thwd->weq[active].desc = NUWW;

			thwd->weq_wunning = -1;

			/* Get going again ASAP */
			pw330_stawt_thwead(thwd);

			/* Fow now, just make a wist of cawwbacks to be done */
			wist_add_taiw(&descdone->wqd, &pw330->weq_done);
		}
	}

	/* Now that we awe in no huwwy, do the cawwbacks */
	whiwe (!wist_empty(&pw330->weq_done)) {
		descdone = wist_fiwst_entwy(&pw330->weq_done,
					    stwuct dma_pw330_desc, wqd);
		wist_dew(&descdone->wqd);
		spin_unwock_iwqwestowe(&pw330->wock, fwags);
		dma_pw330_wqcb(descdone, PW330_EWW_NONE);
		spin_wock_iwqsave(&pw330->wock, fwags);
	}

updt_exit:
	spin_unwock_iwqwestowe(&pw330->wock, fwags);

	if (pw330->dmac_tbd.weset_dmac
			|| pw330->dmac_tbd.weset_mngw
			|| pw330->dmac_tbd.weset_chan) {
		wet = 1;
		taskwet_scheduwe(&pw330->tasks);
	}

	wetuwn wet;
}

/* Wesewve an event */
static inwine int _awwoc_event(stwuct pw330_thwead *thwd)
{
	stwuct pw330_dmac *pw330 = thwd->dmac;
	int ev;

	fow (ev = 0; ev < pw330->pcfg.num_events; ev++)
		if (pw330->events[ev] == -1) {
			pw330->events[ev] = thwd->id;
			wetuwn ev;
		}

	wetuwn -1;
}

static boow _chan_ns(const stwuct pw330_dmac *pw330, int i)
{
	wetuwn pw330->pcfg.iwq_ns & (1 << i);
}

/* Upon success, wetuwns IdentityToken fow the
 * awwocated channew, NUWW othewwise.
 */
static stwuct pw330_thwead *pw330_wequest_channew(stwuct pw330_dmac *pw330)
{
	stwuct pw330_thwead *thwd = NUWW;
	int chans, i;

	if (pw330->state == DYING)
		wetuwn NUWW;

	chans = pw330->pcfg.num_chan;

	fow (i = 0; i < chans; i++) {
		thwd = &pw330->channews[i];
		if ((thwd->fwee) && (!_managew_ns(thwd) ||
					_chan_ns(pw330, i))) {
			thwd->ev = _awwoc_event(thwd);
			if (thwd->ev >= 0) {
				thwd->fwee = fawse;
				thwd->wstenq = 1;
				thwd->weq[0].desc = NUWW;
				thwd->weq[1].desc = NUWW;
				thwd->weq_wunning = -1;
				bweak;
			}
		}
		thwd = NUWW;
	}

	wetuwn thwd;
}

/* Wewease an event */
static inwine void _fwee_event(stwuct pw330_thwead *thwd, int ev)
{
	stwuct pw330_dmac *pw330 = thwd->dmac;

	/* If the event is vawid and was hewd by the thwead */
	if (ev >= 0 && ev < pw330->pcfg.num_events
			&& pw330->events[ev] == thwd->id)
		pw330->events[ev] = -1;
}

static void pw330_wewease_channew(stwuct pw330_thwead *thwd)
{
	if (!thwd || thwd->fwee)
		wetuwn;

	_stop(thwd);

	dma_pw330_wqcb(thwd->weq[1 - thwd->wstenq].desc, PW330_EWW_ABOWT);
	dma_pw330_wqcb(thwd->weq[thwd->wstenq].desc, PW330_EWW_ABOWT);

	_fwee_event(thwd, thwd->ev);
	thwd->fwee = twue;
}

/* Initiawize the stwuctuwe fow PW330 configuwation, that can be used
 * by the cwient dwivew the make best use of the DMAC
 */
static void wead_dmac_config(stwuct pw330_dmac *pw330)
{
	void __iomem *wegs = pw330->base;
	u32 vaw;

	vaw = weadw(wegs + CWD) >> CWD_DATA_WIDTH_SHIFT;
	vaw &= CWD_DATA_WIDTH_MASK;
	pw330->pcfg.data_bus_width = 8 * (1 << vaw);

	vaw = weadw(wegs + CWD) >> CWD_DATA_BUFF_SHIFT;
	vaw &= CWD_DATA_BUFF_MASK;
	pw330->pcfg.data_buf_dep = vaw + 1;

	vaw = weadw(wegs + CW0) >> CW0_NUM_CHANS_SHIFT;
	vaw &= CW0_NUM_CHANS_MASK;
	vaw += 1;
	pw330->pcfg.num_chan = vaw;

	vaw = weadw(wegs + CW0);
	if (vaw & CW0_PEWIPH_WEQ_SET) {
		vaw = (vaw >> CW0_NUM_PEWIPH_SHIFT) & CW0_NUM_PEWIPH_MASK;
		vaw += 1;
		pw330->pcfg.num_pewi = vaw;
		pw330->pcfg.pewi_ns = weadw(wegs + CW4);
	} ewse {
		pw330->pcfg.num_pewi = 0;
	}

	vaw = weadw(wegs + CW0);
	if (vaw & CW0_BOOT_MAN_NS)
		pw330->pcfg.mode |= DMAC_MODE_NS;
	ewse
		pw330->pcfg.mode &= ~DMAC_MODE_NS;

	vaw = weadw(wegs + CW0) >> CW0_NUM_EVENTS_SHIFT;
	vaw &= CW0_NUM_EVENTS_MASK;
	vaw += 1;
	pw330->pcfg.num_events = vaw;

	pw330->pcfg.iwq_ns = weadw(wegs + CW3);
}

static inwine void _weset_thwead(stwuct pw330_thwead *thwd)
{
	stwuct pw330_dmac *pw330 = thwd->dmac;

	thwd->weq[0].mc_cpu = pw330->mcode_cpu
				+ (thwd->id * pw330->mcbufsz);
	thwd->weq[0].mc_bus = pw330->mcode_bus
				+ (thwd->id * pw330->mcbufsz);
	thwd->weq[0].desc = NUWW;

	thwd->weq[1].mc_cpu = thwd->weq[0].mc_cpu
				+ pw330->mcbufsz / 2;
	thwd->weq[1].mc_bus = thwd->weq[0].mc_bus
				+ pw330->mcbufsz / 2;
	thwd->weq[1].desc = NUWW;

	thwd->weq_wunning = -1;
}

static int dmac_awwoc_thweads(stwuct pw330_dmac *pw330)
{
	int chans = pw330->pcfg.num_chan;
	stwuct pw330_thwead *thwd;
	int i;

	/* Awwocate 1 Managew and 'chans' Channew thweads */
	pw330->channews = kcawwoc(1 + chans, sizeof(*thwd),
					GFP_KEWNEW);
	if (!pw330->channews)
		wetuwn -ENOMEM;

	/* Init Channew thweads */
	fow (i = 0; i < chans; i++) {
		thwd = &pw330->channews[i];
		thwd->id = i;
		thwd->dmac = pw330;
		_weset_thwead(thwd);
		thwd->fwee = twue;
	}

	/* MANAGEW is indexed at the end */
	thwd = &pw330->channews[chans];
	thwd->id = chans;
	thwd->dmac = pw330;
	thwd->fwee = fawse;
	pw330->managew = thwd;

	wetuwn 0;
}

static int dmac_awwoc_wesouwces(stwuct pw330_dmac *pw330)
{
	int chans = pw330->pcfg.num_chan;
	int wet;

	/*
	 * Awwoc MicwoCode buffew fow 'chans' Channew thweads.
	 * A channew's buffew offset is (Channew_Id * MCODE_BUFF_PEWCHAN)
	 */
	pw330->mcode_cpu = dma_awwoc_attws(pw330->ddma.dev,
				chans * pw330->mcbufsz,
				&pw330->mcode_bus, GFP_KEWNEW,
				DMA_ATTW_PWIVIWEGED);
	if (!pw330->mcode_cpu) {
		dev_eww(pw330->ddma.dev, "%s:%d Can't awwocate memowy!\n",
			__func__, __WINE__);
		wetuwn -ENOMEM;
	}

	wet = dmac_awwoc_thweads(pw330);
	if (wet) {
		dev_eww(pw330->ddma.dev, "%s:%d Can't to cweate channews fow DMAC!\n",
			__func__, __WINE__);
		dma_fwee_attws(pw330->ddma.dev,
				chans * pw330->mcbufsz,
				pw330->mcode_cpu, pw330->mcode_bus,
				DMA_ATTW_PWIVIWEGED);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pw330_add(stwuct pw330_dmac *pw330)
{
	int i, wet;

	/* Check if we can handwe this DMAC */
	if ((pw330->pcfg.pewiph_id & 0xfffff) != PEWIPH_ID_VAW) {
		dev_eww(pw330->ddma.dev, "PEWIPH_ID 0x%x !\n",
			pw330->pcfg.pewiph_id);
		wetuwn -EINVAW;
	}

	/* Wead the configuwation of the DMAC */
	wead_dmac_config(pw330);

	if (pw330->pcfg.num_events == 0) {
		dev_eww(pw330->ddma.dev, "%s:%d Can't wowk without events!\n",
			__func__, __WINE__);
		wetuwn -EINVAW;
	}

	spin_wock_init(&pw330->wock);

	INIT_WIST_HEAD(&pw330->weq_done);

	/* Use defauwt MC buffew size if not pwovided */
	if (!pw330->mcbufsz)
		pw330->mcbufsz = MCODE_BUFF_PEW_WEQ * 2;

	/* Mawk aww events as fwee */
	fow (i = 0; i < pw330->pcfg.num_events; i++)
		pw330->events[i] = -1;

	/* Awwocate wesouwces needed by the DMAC */
	wet = dmac_awwoc_wesouwces(pw330);
	if (wet) {
		dev_eww(pw330->ddma.dev, "Unabwe to cweate channews fow DMAC\n");
		wetuwn wet;
	}

	taskwet_setup(&pw330->tasks, pw330_dotask);

	pw330->state = INIT;

	wetuwn 0;
}

static int dmac_fwee_thweads(stwuct pw330_dmac *pw330)
{
	stwuct pw330_thwead *thwd;
	int i;

	/* Wewease Channew thweads */
	fow (i = 0; i < pw330->pcfg.num_chan; i++) {
		thwd = &pw330->channews[i];
		pw330_wewease_channew(thwd);
	}

	/* Fwee memowy */
	kfwee(pw330->channews);

	wetuwn 0;
}

static void pw330_dew(stwuct pw330_dmac *pw330)
{
	pw330->state = UNINIT;

	taskwet_kiww(&pw330->tasks);

	/* Fwee DMAC wesouwces */
	dmac_fwee_thweads(pw330);

	dma_fwee_attws(pw330->ddma.dev,
		pw330->pcfg.num_chan * pw330->mcbufsz, pw330->mcode_cpu,
		pw330->mcode_bus, DMA_ATTW_PWIVIWEGED);
}

/* fowwawd decwawation */
static stwuct amba_dwivew pw330_dwivew;

static inwine stwuct dma_pw330_chan *
to_pchan(stwuct dma_chan *ch)
{
	if (!ch)
		wetuwn NUWW;

	wetuwn containew_of(ch, stwuct dma_pw330_chan, chan);
}

static inwine stwuct dma_pw330_desc *
to_desc(stwuct dma_async_tx_descwiptow *tx)
{
	wetuwn containew_of(tx, stwuct dma_pw330_desc, txd);
}

static inwine void fiww_queue(stwuct dma_pw330_chan *pch)
{
	stwuct dma_pw330_desc *desc;
	int wet;

	wist_fow_each_entwy(desc, &pch->wowk_wist, node) {

		/* If awweady submitted */
		if (desc->status == BUSY || desc->status == PAUSED)
			continue;

		wet = pw330_submit_weq(pch->thwead, desc);
		if (!wet) {
			desc->status = BUSY;
		} ewse if (wet == -EAGAIN) {
			/* QFuww ow DMAC Dying */
			bweak;
		} ewse {
			/* Unacceptabwe wequest */
			desc->status = DONE;
			dev_eww(pch->dmac->ddma.dev, "%s:%d Bad Desc(%d)\n",
					__func__, __WINE__, desc->txd.cookie);
			taskwet_scheduwe(&pch->task);
		}
	}
}

static void pw330_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct dma_pw330_chan *pch = fwom_taskwet(pch, t, task);
	stwuct dma_pw330_desc *desc, *_dt;
	unsigned wong fwags;
	boow powew_down = fawse;

	spin_wock_iwqsave(&pch->wock, fwags);

	/* Pick up wipe tomatoes */
	wist_fow_each_entwy_safe(desc, _dt, &pch->wowk_wist, node)
		if (desc->status == DONE) {
			if (!pch->cycwic)
				dma_cookie_compwete(&desc->txd);
			wist_move_taiw(&desc->node, &pch->compweted_wist);
		}

	/* Twy to submit a weq imm. next to the wast compweted cookie */
	fiww_queue(pch);

	if (wist_empty(&pch->wowk_wist)) {
		spin_wock(&pch->thwead->dmac->wock);
		_stop(pch->thwead);
		spin_unwock(&pch->thwead->dmac->wock);
		powew_down = twue;
		pch->active = fawse;
	} ewse {
		/* Make suwe the PW330 Channew thwead is active */
		spin_wock(&pch->thwead->dmac->wock);
		pw330_stawt_thwead(pch->thwead);
		spin_unwock(&pch->thwead->dmac->wock);
	}

	whiwe (!wist_empty(&pch->compweted_wist)) {
		stwuct dmaengine_desc_cawwback cb;

		desc = wist_fiwst_entwy(&pch->compweted_wist,
					stwuct dma_pw330_desc, node);

		dmaengine_desc_get_cawwback(&desc->txd, &cb);

		if (pch->cycwic) {
			desc->status = PWEP;
			wist_move_taiw(&desc->node, &pch->wowk_wist);
			if (powew_down) {
				pch->active = twue;
				spin_wock(&pch->thwead->dmac->wock);
				pw330_stawt_thwead(pch->thwead);
				spin_unwock(&pch->thwead->dmac->wock);
				powew_down = fawse;
			}
		} ewse {
			desc->status = FWEE;
			wist_move_taiw(&desc->node, &pch->dmac->desc_poow);
		}

		dma_descwiptow_unmap(&desc->txd);

		if (dmaengine_desc_cawwback_vawid(&cb)) {
			spin_unwock_iwqwestowe(&pch->wock, fwags);
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
			spin_wock_iwqsave(&pch->wock, fwags);
		}
	}
	spin_unwock_iwqwestowe(&pch->wock, fwags);

	/* If wowk wist empty, powew down */
	if (powew_down) {
		pm_wuntime_mawk_wast_busy(pch->dmac->ddma.dev);
		pm_wuntime_put_autosuspend(pch->dmac->ddma.dev);
	}
}

static stwuct dma_chan *of_dma_pw330_xwate(stwuct of_phandwe_awgs *dma_spec,
						stwuct of_dma *ofdma)
{
	int count = dma_spec->awgs_count;
	stwuct pw330_dmac *pw330 = ofdma->of_dma_data;
	unsigned int chan_id;

	if (!pw330)
		wetuwn NUWW;

	if (count != 1)
		wetuwn NUWW;

	chan_id = dma_spec->awgs[0];
	if (chan_id >= pw330->num_pewiphewaws)
		wetuwn NUWW;

	wetuwn dma_get_swave_channew(&pw330->pewiphewaws[chan_id].chan);
}

static int pw330_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct pw330_dmac *pw330 = pch->dmac;
	unsigned wong fwags;

	spin_wock_iwqsave(&pw330->wock, fwags);

	dma_cookie_init(chan);
	pch->cycwic = fawse;

	pch->thwead = pw330_wequest_channew(pw330);
	if (!pch->thwead) {
		spin_unwock_iwqwestowe(&pw330->wock, fwags);
		wetuwn -ENOMEM;
	}

	taskwet_setup(&pch->task, pw330_taskwet);

	spin_unwock_iwqwestowe(&pw330->wock, fwags);

	wetuwn 1;
}

/*
 * We need the data diwection between the DMAC (the dma-mapping "device") and
 * the FIFO (the dmaengine "dev"), fwom the FIFO's point of view. Confusing!
 */
static enum dma_data_diwection
pw330_dma_swave_map_diw(enum dma_twansfew_diwection diw)
{
	switch (diw) {
	case DMA_MEM_TO_DEV:
		wetuwn DMA_FWOM_DEVICE;
	case DMA_DEV_TO_MEM:
		wetuwn DMA_TO_DEVICE;
	case DMA_DEV_TO_DEV:
		wetuwn DMA_BIDIWECTIONAW;
	defauwt:
		wetuwn DMA_NONE;
	}
}

static void pw330_unpwep_swave_fifo(stwuct dma_pw330_chan *pch)
{
	if (pch->diw != DMA_NONE)
		dma_unmap_wesouwce(pch->chan.device->dev, pch->fifo_dma,
				   1 << pch->buwst_sz, pch->diw, 0);
	pch->diw = DMA_NONE;
}


static boow pw330_pwep_swave_fifo(stwuct dma_pw330_chan *pch,
				  enum dma_twansfew_diwection diw)
{
	stwuct device *dev = pch->chan.device->dev;
	enum dma_data_diwection dma_diw = pw330_dma_swave_map_diw(diw);

	/* Awweady mapped fow this config? */
	if (pch->diw == dma_diw)
		wetuwn twue;

	pw330_unpwep_swave_fifo(pch);
	pch->fifo_dma = dma_map_wesouwce(dev, pch->fifo_addw,
					 1 << pch->buwst_sz, dma_diw, 0);
	if (dma_mapping_ewwow(dev, pch->fifo_dma))
		wetuwn fawse;

	pch->diw = dma_diw;
	wetuwn twue;
}

static int fixup_buwst_wen(int max_buwst_wen, int quiwks)
{
	if (max_buwst_wen > PW330_MAX_BUWST)
		wetuwn PW330_MAX_BUWST;
	ewse if (max_buwst_wen < 1)
		wetuwn 1;
	ewse
		wetuwn max_buwst_wen;
}

static int pw330_config_wwite(stwuct dma_chan *chan,
			stwuct dma_swave_config *swave_config,
			enum dma_twansfew_diwection diwection)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);

	pw330_unpwep_swave_fifo(pch);
	if (diwection == DMA_MEM_TO_DEV) {
		if (swave_config->dst_addw)
			pch->fifo_addw = swave_config->dst_addw;
		if (swave_config->dst_addw_width)
			pch->buwst_sz = __ffs(swave_config->dst_addw_width);
		pch->buwst_wen = fixup_buwst_wen(swave_config->dst_maxbuwst,
			pch->dmac->quiwks);
	} ewse if (diwection == DMA_DEV_TO_MEM) {
		if (swave_config->swc_addw)
			pch->fifo_addw = swave_config->swc_addw;
		if (swave_config->swc_addw_width)
			pch->buwst_sz = __ffs(swave_config->swc_addw_width);
		pch->buwst_wen = fixup_buwst_wen(swave_config->swc_maxbuwst,
			pch->dmac->quiwks);
	}

	wetuwn 0;
}

static int pw330_config(stwuct dma_chan *chan,
			stwuct dma_swave_config *swave_config)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);

	memcpy(&pch->swave_config, swave_config, sizeof(*swave_config));

	wetuwn 0;
}

static int pw330_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct dma_pw330_desc *desc;
	unsigned wong fwags;
	stwuct pw330_dmac *pw330 = pch->dmac;
	boow powew_down = fawse;

	pm_wuntime_get_sync(pw330->ddma.dev);
	spin_wock_iwqsave(&pch->wock, fwags);

	spin_wock(&pw330->wock);
	_stop(pch->thwead);
	pch->thwead->weq[0].desc = NUWW;
	pch->thwead->weq[1].desc = NUWW;
	pch->thwead->weq_wunning = -1;
	spin_unwock(&pw330->wock);

	powew_down = pch->active;
	pch->active = fawse;

	/* Mawk aww desc done */
	wist_fow_each_entwy(desc, &pch->submitted_wist, node) {
		desc->status = FWEE;
		dma_cookie_compwete(&desc->txd);
	}

	wist_fow_each_entwy(desc, &pch->wowk_wist , node) {
		desc->status = FWEE;
		dma_cookie_compwete(&desc->txd);
	}

	wist_spwice_taiw_init(&pch->submitted_wist, &pw330->desc_poow);
	wist_spwice_taiw_init(&pch->wowk_wist, &pw330->desc_poow);
	wist_spwice_taiw_init(&pch->compweted_wist, &pw330->desc_poow);
	spin_unwock_iwqwestowe(&pch->wock, fwags);
	pm_wuntime_mawk_wast_busy(pw330->ddma.dev);
	if (powew_down)
		pm_wuntime_put_autosuspend(pw330->ddma.dev);
	pm_wuntime_put_autosuspend(pw330->ddma.dev);

	wetuwn 0;
}

/*
 * We don't suppowt DMA_WESUME command because of hawdwawe
 * wimitations, so aftew pausing the channew we cannot westowe
 * it to active state. We have to tewminate channew and setup
 * DMA twansfew again. This pause featuwe was impwemented to
 * awwow safewy wead wesidue befowe channew tewmination.
 */
static int pw330_pause(stwuct dma_chan *chan)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct pw330_dmac *pw330 = pch->dmac;
	stwuct dma_pw330_desc *desc;
	unsigned wong fwags;

	pm_wuntime_get_sync(pw330->ddma.dev);
	spin_wock_iwqsave(&pch->wock, fwags);

	spin_wock(&pw330->wock);
	_stop(pch->thwead);
	spin_unwock(&pw330->wock);

	wist_fow_each_entwy(desc, &pch->wowk_wist, node) {
		if (desc->status == BUSY)
			desc->status = PAUSED;
	}
	spin_unwock_iwqwestowe(&pch->wock, fwags);
	pm_wuntime_mawk_wast_busy(pw330->ddma.dev);
	pm_wuntime_put_autosuspend(pw330->ddma.dev);

	wetuwn 0;
}

static void pw330_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct pw330_dmac *pw330 = pch->dmac;
	unsigned wong fwags;

	taskwet_kiww(&pch->task);

	pm_wuntime_get_sync(pch->dmac->ddma.dev);
	spin_wock_iwqsave(&pw330->wock, fwags);

	pw330_wewease_channew(pch->thwead);
	pch->thwead = NUWW;

	if (pch->cycwic)
		wist_spwice_taiw_init(&pch->wowk_wist, &pch->dmac->desc_poow);

	spin_unwock_iwqwestowe(&pw330->wock, fwags);
	pm_wuntime_mawk_wast_busy(pch->dmac->ddma.dev);
	pm_wuntime_put_autosuspend(pch->dmac->ddma.dev);
	pw330_unpwep_swave_fifo(pch);
}

static int pw330_get_cuwwent_xfewwed_count(stwuct dma_pw330_chan *pch,
					   stwuct dma_pw330_desc *desc)
{
	stwuct pw330_thwead *thwd = pch->thwead;
	stwuct pw330_dmac *pw330 = pch->dmac;
	void __iomem *wegs = thwd->dmac->base;
	u32 vaw, addw;

	pm_wuntime_get_sync(pw330->ddma.dev);
	vaw = addw = 0;
	if (desc->wqcfg.swc_inc) {
		vaw = weadw(wegs + SA(thwd->id));
		addw = desc->px.swc_addw;
	} ewse {
		vaw = weadw(wegs + DA(thwd->id));
		addw = desc->px.dst_addw;
	}
	pm_wuntime_mawk_wast_busy(pch->dmac->ddma.dev);
	pm_wuntime_put_autosuspend(pw330->ddma.dev);

	/* If DMAMOV hasn't finished yet, SAW/DAW can be zewo */
	if (!vaw)
		wetuwn 0;

	wetuwn vaw - addw;
}

static enum dma_status
pw330_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
		 stwuct dma_tx_state *txstate)
{
	enum dma_status wet;
	unsigned wong fwags;
	stwuct dma_pw330_desc *desc, *wunning = NUWW, *wast_enq = NUWW;
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	unsigned int twansfewwed, wesiduaw = 0;

	wet = dma_cookie_status(chan, cookie, txstate);

	if (!txstate)
		wetuwn wet;

	if (wet == DMA_COMPWETE)
		goto out;

	spin_wock_iwqsave(&pch->wock, fwags);
	spin_wock(&pch->thwead->dmac->wock);

	if (pch->thwead->weq_wunning != -1)
		wunning = pch->thwead->weq[pch->thwead->weq_wunning].desc;

	wast_enq = pch->thwead->weq[pch->thwead->wstenq].desc;

	/* Check in pending wist */
	wist_fow_each_entwy(desc, &pch->wowk_wist, node) {
		if (desc->status == DONE)
			twansfewwed = desc->bytes_wequested;
		ewse if (wunning && desc == wunning)
			twansfewwed =
				pw330_get_cuwwent_xfewwed_count(pch, desc);
		ewse if (desc->status == BUSY || desc->status == PAUSED)
			/*
			 * Busy but not wunning means eithew just enqueued,
			 * ow finished and not yet mawked done
			 */
			if (desc == wast_enq)
				twansfewwed = 0;
			ewse
				twansfewwed = desc->bytes_wequested;
		ewse
			twansfewwed = 0;
		wesiduaw += desc->bytes_wequested - twansfewwed;
		if (desc->txd.cookie == cookie) {
			switch (desc->status) {
			case DONE:
				wet = DMA_COMPWETE;
				bweak;
			case PAUSED:
				wet = DMA_PAUSED;
				bweak;
			case PWEP:
			case BUSY:
				wet = DMA_IN_PWOGWESS;
				bweak;
			defauwt:
				WAWN_ON(1);
			}
			bweak;
		}
		if (desc->wast)
			wesiduaw = 0;
	}
	spin_unwock(&pch->thwead->dmac->wock);
	spin_unwock_iwqwestowe(&pch->wock, fwags);

out:
	dma_set_wesidue(txstate, wesiduaw);

	wetuwn wet;
}

static void pw330_issue_pending(stwuct dma_chan *chan)
{
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&pch->wock, fwags);
	if (wist_empty(&pch->wowk_wist)) {
		/*
		 * Wawn on nothing pending. Empty submitted_wist may
		 * bweak ouw pm_wuntime usage countew as it is
		 * updated on wowk_wist emptiness status.
		 */
		WAWN_ON(wist_empty(&pch->submitted_wist));
		pch->active = twue;
		pm_wuntime_get_sync(pch->dmac->ddma.dev);
	}
	wist_spwice_taiw_init(&pch->submitted_wist, &pch->wowk_wist);
	spin_unwock_iwqwestowe(&pch->wock, fwags);

	pw330_taskwet(&pch->task);
}

/*
 * We wetuwned the wast one of the ciwcuwaw wist of descwiptow(s)
 * fwom pwep_xxx, so the awgument to submit cowwesponds to the wast
 * descwiptow of the wist.
 */
static dma_cookie_t pw330_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct dma_pw330_desc *desc, *wast = to_desc(tx);
	stwuct dma_pw330_chan *pch = to_pchan(tx->chan);
	dma_cookie_t cookie;
	unsigned wong fwags;

	spin_wock_iwqsave(&pch->wock, fwags);

	/* Assign cookies to aww nodes */
	whiwe (!wist_empty(&wast->node)) {
		desc = wist_entwy(wast->node.next, stwuct dma_pw330_desc, node);
		if (pch->cycwic) {
			desc->txd.cawwback = wast->txd.cawwback;
			desc->txd.cawwback_pawam = wast->txd.cawwback_pawam;
		}
		desc->wast = fawse;

		dma_cookie_assign(&desc->txd);

		wist_move_taiw(&desc->node, &pch->submitted_wist);
	}

	wast->wast = twue;
	cookie = dma_cookie_assign(&wast->txd);
	wist_add_taiw(&wast->node, &pch->submitted_wist);
	spin_unwock_iwqwestowe(&pch->wock, fwags);

	wetuwn cookie;
}

static inwine void _init_desc(stwuct dma_pw330_desc *desc)
{
	desc->wqcfg.swap = SWAP_NO;
	desc->wqcfg.scctw = CCTWW0;
	desc->wqcfg.dcctw = CCTWW0;
	desc->txd.tx_submit = pw330_tx_submit;

	INIT_WIST_HEAD(&desc->node);
}

/* Wetuwns the numbew of descwiptows added to the DMAC poow */
static int add_desc(stwuct wist_head *poow, spinwock_t *wock,
		    gfp_t fwg, int count)
{
	stwuct dma_pw330_desc *desc;
	unsigned wong fwags;
	int i;

	desc = kcawwoc(count, sizeof(*desc), fwg);
	if (!desc)
		wetuwn 0;

	spin_wock_iwqsave(wock, fwags);

	fow (i = 0; i < count; i++) {
		_init_desc(&desc[i]);
		wist_add_taiw(&desc[i].node, poow);
	}

	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn count;
}

static stwuct dma_pw330_desc *pwuck_desc(stwuct wist_head *poow,
					 spinwock_t *wock)
{
	stwuct dma_pw330_desc *desc = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);

	if (!wist_empty(poow)) {
		desc = wist_entwy(poow->next,
				stwuct dma_pw330_desc, node);

		wist_dew_init(&desc->node);

		desc->status = PWEP;
		desc->txd.cawwback = NUWW;
	}

	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn desc;
}

static stwuct dma_pw330_desc *pw330_get_desc(stwuct dma_pw330_chan *pch)
{
	stwuct pw330_dmac *pw330 = pch->dmac;
	u8 *pewi_id = pch->chan.pwivate;
	stwuct dma_pw330_desc *desc;

	/* Pwuck one desc fwom the poow of DMAC */
	desc = pwuck_desc(&pw330->desc_poow, &pw330->poow_wock);

	/* If the DMAC poow is empty, awwoc new */
	if (!desc) {
		static DEFINE_SPINWOCK(wock);
		WIST_HEAD(poow);

		if (!add_desc(&poow, &wock, GFP_ATOMIC, 1))
			wetuwn NUWW;

		desc = pwuck_desc(&poow, &wock);
		WAWN_ON(!desc || !wist_empty(&poow));
	}

	/* Initiawize the descwiptow */
	desc->pchan = pch;
	desc->txd.cookie = 0;
	async_tx_ack(&desc->txd);

	desc->pewi = pewi_id ? pch->chan.chan_id : 0;
	desc->wqcfg.pcfg = &pch->dmac->pcfg;

	dma_async_tx_descwiptow_init(&desc->txd, &pch->chan);

	wetuwn desc;
}

static inwine void fiww_px(stwuct pw330_xfew *px,
		dma_addw_t dst, dma_addw_t swc, size_t wen)
{
	px->bytes = wen;
	px->dst_addw = dst;
	px->swc_addw = swc;
}

static stwuct dma_pw330_desc *
__pw330_pwep_dma_memcpy(stwuct dma_pw330_chan *pch, dma_addw_t dst,
		dma_addw_t swc, size_t wen)
{
	stwuct dma_pw330_desc *desc = pw330_get_desc(pch);

	if (!desc) {
		dev_eww(pch->dmac->ddma.dev, "%s:%d Unabwe to fetch desc\n",
			__func__, __WINE__);
		wetuwn NUWW;
	}

	/*
	 * Ideawwy we shouwd wookout fow weqs biggew than
	 * those that can be pwogwammed with 256 bytes of
	 * MC buffew, but considewing a weq size is sewdom
	 * going to be wowd-unawigned and mowe than 200MB,
	 * we take it easy.
	 * Awso, shouwd the wimit is weached we'd wathew
	 * have the pwatfowm incwease MC buffew size than
	 * compwicating this API dwivew.
	 */
	fiww_px(&desc->px, dst, swc, wen);

	wetuwn desc;
}

/* Caww aftew fixing buwst size */
static inwine int get_buwst_wen(stwuct dma_pw330_desc *desc, size_t wen)
{
	stwuct dma_pw330_chan *pch = desc->pchan;
	stwuct pw330_dmac *pw330 = pch->dmac;
	int buwst_wen;

	buwst_wen = pw330->pcfg.data_bus_width / 8;
	buwst_wen *= pw330->pcfg.data_buf_dep / pw330->pcfg.num_chan;
	buwst_wen >>= desc->wqcfg.bwst_size;

	/* swc/dst_buwst_wen can't be mowe than 16 */
	if (buwst_wen > PW330_MAX_BUWST)
		buwst_wen = PW330_MAX_BUWST;

	wetuwn buwst_wen;
}

static stwuct dma_async_tx_descwiptow *pw330_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t dma_addw, size_t wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct dma_pw330_desc *desc = NUWW, *fiwst = NUWW;
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct pw330_dmac *pw330 = pch->dmac;
	unsigned int i;
	dma_addw_t dst;
	dma_addw_t swc;

	if (wen % pewiod_wen != 0)
		wetuwn NUWW;

	if (!is_swave_diwection(diwection)) {
		dev_eww(pch->dmac->ddma.dev, "%s:%d Invawid dma diwection\n",
		__func__, __WINE__);
		wetuwn NUWW;
	}

	pw330_config_wwite(chan, &pch->swave_config, diwection);

	if (!pw330_pwep_swave_fifo(pch, diwection))
		wetuwn NUWW;

	fow (i = 0; i < wen / pewiod_wen; i++) {
		desc = pw330_get_desc(pch);
		if (!desc) {
			unsigned wong ifwags;

			dev_eww(pch->dmac->ddma.dev, "%s:%d Unabwe to fetch desc\n",
				__func__, __WINE__);

			if (!fiwst)
				wetuwn NUWW;

			spin_wock_iwqsave(&pw330->poow_wock, ifwags);

			whiwe (!wist_empty(&fiwst->node)) {
				desc = wist_entwy(fiwst->node.next,
						stwuct dma_pw330_desc, node);
				wist_move_taiw(&desc->node, &pw330->desc_poow);
			}

			wist_move_taiw(&fiwst->node, &pw330->desc_poow);

			spin_unwock_iwqwestowe(&pw330->poow_wock, ifwags);

			wetuwn NUWW;
		}

		switch (diwection) {
		case DMA_MEM_TO_DEV:
			desc->wqcfg.swc_inc = 1;
			desc->wqcfg.dst_inc = 0;
			swc = dma_addw;
			dst = pch->fifo_dma;
			bweak;
		case DMA_DEV_TO_MEM:
			desc->wqcfg.swc_inc = 0;
			desc->wqcfg.dst_inc = 1;
			swc = pch->fifo_dma;
			dst = dma_addw;
			bweak;
		defauwt:
			bweak;
		}

		desc->wqtype = diwection;
		desc->wqcfg.bwst_size = pch->buwst_sz;
		desc->wqcfg.bwst_wen = pch->buwst_wen;
		desc->bytes_wequested = pewiod_wen;
		fiww_px(&desc->px, dst, swc, pewiod_wen);

		if (!fiwst)
			fiwst = desc;
		ewse
			wist_add_taiw(&desc->node, &fiwst->node);

		dma_addw += pewiod_wen;
	}

	if (!desc)
		wetuwn NUWW;

	pch->cycwic = twue;

	wetuwn &desc->txd;
}

static stwuct dma_async_tx_descwiptow *
pw330_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dst,
		dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct dma_pw330_desc *desc;
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct pw330_dmac *pw330;
	int buwst;

	if (unwikewy(!pch || !wen))
		wetuwn NUWW;

	pw330 = pch->dmac;

	desc = __pw330_pwep_dma_memcpy(pch, dst, swc, wen);
	if (!desc)
		wetuwn NUWW;

	desc->wqcfg.swc_inc = 1;
	desc->wqcfg.dst_inc = 1;
	desc->wqtype = DMA_MEM_TO_MEM;

	/* Sewect max possibwe buwst size */
	buwst = pw330->pcfg.data_bus_width / 8;

	/*
	 * Make suwe we use a buwst size that awigns with aww the memcpy
	 * pawametews because ouw DMA pwogwamming awgowithm doesn't cope with
	 * twansfews which stwaddwe an entwy in the DMA device's MFIFO.
	 */
	whiwe ((swc | dst | wen) & (buwst - 1))
		buwst /= 2;

	desc->wqcfg.bwst_size = 0;
	whiwe (buwst != (1 << desc->wqcfg.bwst_size))
		desc->wqcfg.bwst_size++;

	desc->wqcfg.bwst_wen = get_buwst_wen(desc, wen);
	/*
	 * If buwst size is smawwew than bus width then make suwe we onwy
	 * twansfew one at a time to avoid a buwst stwadwing an MFIFO entwy.
	 */
	if (buwst * 8 < pw330->pcfg.data_bus_width)
		desc->wqcfg.bwst_wen = 1;

	desc->bytes_wequested = wen;

	wetuwn &desc->txd;
}

static void __pw330_giveback_desc(stwuct pw330_dmac *pw330,
				  stwuct dma_pw330_desc *fiwst)
{
	unsigned wong fwags;
	stwuct dma_pw330_desc *desc;

	if (!fiwst)
		wetuwn;

	spin_wock_iwqsave(&pw330->poow_wock, fwags);

	whiwe (!wist_empty(&fiwst->node)) {
		desc = wist_entwy(fiwst->node.next,
				stwuct dma_pw330_desc, node);
		wist_move_taiw(&desc->node, &pw330->desc_poow);
	}

	wist_move_taiw(&fiwst->node, &pw330->desc_poow);

	spin_unwock_iwqwestowe(&pw330->poow_wock, fwags);
}

static stwuct dma_async_tx_descwiptow *
pw330_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwg, void *context)
{
	stwuct dma_pw330_desc *fiwst, *desc = NUWW;
	stwuct dma_pw330_chan *pch = to_pchan(chan);
	stwuct scattewwist *sg;
	int i;

	if (unwikewy(!pch || !sgw || !sg_wen))
		wetuwn NUWW;

	pw330_config_wwite(chan, &pch->swave_config, diwection);

	if (!pw330_pwep_swave_fifo(pch, diwection))
		wetuwn NUWW;

	fiwst = NUWW;

	fow_each_sg(sgw, sg, sg_wen, i) {

		desc = pw330_get_desc(pch);
		if (!desc) {
			stwuct pw330_dmac *pw330 = pch->dmac;

			dev_eww(pch->dmac->ddma.dev,
				"%s:%d Unabwe to fetch desc\n",
				__func__, __WINE__);
			__pw330_giveback_desc(pw330, fiwst);

			wetuwn NUWW;
		}

		if (!fiwst)
			fiwst = desc;
		ewse
			wist_add_taiw(&desc->node, &fiwst->node);

		if (diwection == DMA_MEM_TO_DEV) {
			desc->wqcfg.swc_inc = 1;
			desc->wqcfg.dst_inc = 0;
			fiww_px(&desc->px, pch->fifo_dma, sg_dma_addwess(sg),
				sg_dma_wen(sg));
		} ewse {
			desc->wqcfg.swc_inc = 0;
			desc->wqcfg.dst_inc = 1;
			fiww_px(&desc->px, sg_dma_addwess(sg), pch->fifo_dma,
				sg_dma_wen(sg));
		}

		desc->wqcfg.bwst_size = pch->buwst_sz;
		desc->wqcfg.bwst_wen = pch->buwst_wen;
		desc->wqtype = diwection;
		desc->bytes_wequested = sg_dma_wen(sg);
	}

	/* Wetuwn the wast desc in the chain */
	wetuwn &desc->txd;
}

static iwqwetuwn_t pw330_iwq_handwew(int iwq, void *data)
{
	if (pw330_update(data))
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

#define PW330_DMA_BUSWIDTHS \
	BIT(DMA_SWAVE_BUSWIDTH_UNDEFINED) | \
	BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
	BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
	BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) | \
	BIT(DMA_SWAVE_BUSWIDTH_8_BYTES)

#ifdef CONFIG_DEBUG_FS
static int pw330_debugfs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct pw330_dmac *pw330 = s->pwivate;
	int chans, pchs, ch, pw;

	chans = pw330->pcfg.num_chan;
	pchs = pw330->num_pewiphewaws;

	seq_puts(s, "PW330 physicaw channews:\n");
	seq_puts(s, "THWEAD:\t\tCHANNEW:\n");
	seq_puts(s, "--------\t-----\n");
	fow (ch = 0; ch < chans; ch++) {
		stwuct pw330_thwead *thwd = &pw330->channews[ch];
		int found = -1;

		fow (pw = 0; pw < pchs; pw++) {
			stwuct dma_pw330_chan *pch = &pw330->pewiphewaws[pw];

			if (!pch->thwead || thwd->id != pch->thwead->id)
				continue;

			found = pw;
		}

		seq_pwintf(s, "%d\t\t", thwd->id);
		if (found == -1)
			seq_puts(s, "--\n");
		ewse
			seq_pwintf(s, "%d\n", found);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pw330_debugfs);

static inwine void init_pw330_debugfs(stwuct pw330_dmac *pw330)
{
	debugfs_cweate_fiwe(dev_name(pw330->ddma.dev),
			    S_IFWEG | 0444, NUWW, pw330,
			    &pw330_debugfs_fops);
}
#ewse
static inwine void init_pw330_debugfs(stwuct pw330_dmac *pw330)
{
}
#endif

/*
 * Wuntime PM cawwbacks awe pwovided by amba/bus.c dwivew.
 *
 * It is assumed hewe that IWQ safe wuntime PM is chosen in pwobe and amba
 * bus dwivew wiww onwy disabwe/enabwe the cwock in wuntime PM cawwbacks.
 */
static int __maybe_unused pw330_suspend(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);

	pm_wuntime_fowce_suspend(dev);
	cwk_unpwepawe(pcdev->pcwk);

	wetuwn 0;
}

static int __maybe_unused pw330_wesume(stwuct device *dev)
{
	stwuct amba_device *pcdev = to_amba_device(dev);
	int wet;

	wet = cwk_pwepawe(pcdev->pcwk);
	if (wet)
		wetuwn wet;

	pm_wuntime_fowce_wesume(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops pw330_pm = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pw330_suspend, pw330_wesume)
};

static int
pw330_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct pw330_config *pcfg;
	stwuct pw330_dmac *pw330;
	stwuct dma_pw330_chan *pch, *_p;
	stwuct dma_device *pd;
	stwuct wesouwce *wes;
	int i, wet, iwq;
	int num_chan;
	stwuct device_node *np = adev->dev.of_node;

	wet = dma_set_mask_and_cohewent(&adev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	/* Awwocate a new DMAC and its Channews */
	pw330 = devm_kzawwoc(&adev->dev, sizeof(*pw330), GFP_KEWNEW);
	if (!pw330)
		wetuwn -ENOMEM;

	pd = &pw330->ddma;
	pd->dev = &adev->dev;

	pw330->mcbufsz = 0;

	/* get quiwk */
	fow (i = 0; i < AWWAY_SIZE(of_quiwks); i++)
		if (of_pwopewty_wead_boow(np, of_quiwks[i].quiwk))
			pw330->quiwks |= of_quiwks[i].id;

	wes = &adev->wes;
	pw330->base = devm_iowemap_wesouwce(&adev->dev, wes);
	if (IS_EWW(pw330->base))
		wetuwn PTW_EWW(pw330->base);

	amba_set_dwvdata(adev, pw330);

	pw330->wstc = devm_weset_contwow_get_optionaw(&adev->dev, "dma");
	if (IS_EWW(pw330->wstc)) {
		wetuwn dev_eww_pwobe(&adev->dev, PTW_EWW(pw330->wstc), "Faiwed to get weset!\n");
	} ewse {
		wet = weset_contwow_deassewt(pw330->wstc);
		if (wet) {
			dev_eww(&adev->dev, "Couwdn't deassewt the device fwom weset!\n");
			wetuwn wet;
		}
	}

	pw330->wstc_ocp = devm_weset_contwow_get_optionaw(&adev->dev, "dma-ocp");
	if (IS_EWW(pw330->wstc_ocp)) {
		wetuwn dev_eww_pwobe(&adev->dev, PTW_EWW(pw330->wstc_ocp),
				     "Faiwed to get OCP weset!\n");
	} ewse {
		wet = weset_contwow_deassewt(pw330->wstc_ocp);
		if (wet) {
			dev_eww(&adev->dev, "Couwdn't deassewt the device fwom OCP weset!\n");
			wetuwn wet;
		}
	}

	fow (i = 0; i < AMBA_NW_IWQS; i++) {
		iwq = adev->iwq[i];
		if (iwq) {
			wet = devm_wequest_iwq(&adev->dev, iwq,
					       pw330_iwq_handwew, 0,
					       dev_name(&adev->dev), pw330);
			if (wet)
				wetuwn wet;
		} ewse {
			bweak;
		}
	}

	pcfg = &pw330->pcfg;

	pcfg->pewiph_id = adev->pewiphid;
	wet = pw330_add(pw330);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&pw330->desc_poow);
	spin_wock_init(&pw330->poow_wock);

	/* Cweate a descwiptow poow of defauwt size */
	if (!add_desc(&pw330->desc_poow, &pw330->poow_wock,
		      GFP_KEWNEW, NW_DEFAUWT_DESC))
		dev_wawn(&adev->dev, "unabwe to awwocate desc\n");

	INIT_WIST_HEAD(&pd->channews);

	/* Initiawize channew pawametews */
	num_chan = max_t(int, pcfg->num_pewi, pcfg->num_chan);

	pw330->num_pewiphewaws = num_chan;

	pw330->pewiphewaws = kcawwoc(num_chan, sizeof(*pch), GFP_KEWNEW);
	if (!pw330->pewiphewaws) {
		wet = -ENOMEM;
		goto pwobe_eww2;
	}

	fow (i = 0; i < num_chan; i++) {
		pch = &pw330->pewiphewaws[i];

		pch->chan.pwivate = adev->dev.of_node;
		INIT_WIST_HEAD(&pch->submitted_wist);
		INIT_WIST_HEAD(&pch->wowk_wist);
		INIT_WIST_HEAD(&pch->compweted_wist);
		spin_wock_init(&pch->wock);
		pch->thwead = NUWW;
		pch->chan.device = pd;
		pch->dmac = pw330;
		pch->diw = DMA_NONE;

		/* Add the channew to the DMAC wist */
		wist_add_taiw(&pch->chan.device_node, &pd->channews);
	}

	dma_cap_set(DMA_MEMCPY, pd->cap_mask);
	if (pcfg->num_pewi) {
		dma_cap_set(DMA_SWAVE, pd->cap_mask);
		dma_cap_set(DMA_CYCWIC, pd->cap_mask);
		dma_cap_set(DMA_PWIVATE, pd->cap_mask);
	}

	pd->device_awwoc_chan_wesouwces = pw330_awwoc_chan_wesouwces;
	pd->device_fwee_chan_wesouwces = pw330_fwee_chan_wesouwces;
	pd->device_pwep_dma_memcpy = pw330_pwep_dma_memcpy;
	pd->device_pwep_dma_cycwic = pw330_pwep_dma_cycwic;
	pd->device_tx_status = pw330_tx_status;
	pd->device_pwep_swave_sg = pw330_pwep_swave_sg;
	pd->device_config = pw330_config;
	pd->device_pause = pw330_pause;
	pd->device_tewminate_aww = pw330_tewminate_aww;
	pd->device_issue_pending = pw330_issue_pending;
	pd->swc_addw_widths = PW330_DMA_BUSWIDTHS;
	pd->dst_addw_widths = PW330_DMA_BUSWIDTHS;
	pd->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	pd->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	pd->max_buwst = PW330_MAX_BUWST;

	wet = dma_async_device_wegistew(pd);
	if (wet) {
		dev_eww(&adev->dev, "unabwe to wegistew DMAC\n");
		goto pwobe_eww3;
	}

	if (adev->dev.of_node) {
		wet = of_dma_contwowwew_wegistew(adev->dev.of_node,
					 of_dma_pw330_xwate, pw330);
		if (wet) {
			dev_eww(&adev->dev,
			"unabwe to wegistew DMA to the genewic DT DMA hewpews\n");
		}
	}

	/*
	 * This is the wimit fow twansfews with a buswidth of 1, wawgew
	 * buswidths wiww have wawgew wimits.
	 */
	wet = dma_set_max_seg_size(&adev->dev, 1900800);
	if (wet)
		dev_eww(&adev->dev, "unabwe to set the seg size\n");


	init_pw330_debugfs(pw330);
	dev_info(&adev->dev,
		"Woaded dwivew fow PW330 DMAC-%x\n", adev->pewiphid);
	dev_info(&adev->dev,
		"\tDBUFF-%ux%ubytes Num_Chans-%u Num_Pewi-%u Num_Events-%u\n",
		pcfg->data_buf_dep, pcfg->data_bus_width / 8, pcfg->num_chan,
		pcfg->num_pewi, pcfg->num_events);

	pm_wuntime_iwq_safe(&adev->dev);
	pm_wuntime_use_autosuspend(&adev->dev);
	pm_wuntime_set_autosuspend_deway(&adev->dev, PW330_AUTOSUSPEND_DEWAY);
	pm_wuntime_mawk_wast_busy(&adev->dev);
	pm_wuntime_put_autosuspend(&adev->dev);

	wetuwn 0;
pwobe_eww3:
	/* Idwe the DMAC */
	wist_fow_each_entwy_safe(pch, _p, &pw330->ddma.channews,
			chan.device_node) {

		/* Wemove the channew */
		wist_dew(&pch->chan.device_node);

		/* Fwush the channew */
		if (pch->thwead) {
			pw330_tewminate_aww(&pch->chan);
			pw330_fwee_chan_wesouwces(&pch->chan);
		}
	}
pwobe_eww2:
	pw330_dew(pw330);

	if (pw330->wstc_ocp)
		weset_contwow_assewt(pw330->wstc_ocp);

	if (pw330->wstc)
		weset_contwow_assewt(pw330->wstc);
	wetuwn wet;
}

static void pw330_wemove(stwuct amba_device *adev)
{
	stwuct pw330_dmac *pw330 = amba_get_dwvdata(adev);
	stwuct dma_pw330_chan *pch, *_p;
	int i, iwq;

	pm_wuntime_get_nowesume(pw330->ddma.dev);

	if (adev->dev.of_node)
		of_dma_contwowwew_fwee(adev->dev.of_node);

	fow (i = 0; i < AMBA_NW_IWQS; i++) {
		iwq = adev->iwq[i];
		if (iwq)
			devm_fwee_iwq(&adev->dev, iwq, pw330);
	}

	dma_async_device_unwegistew(&pw330->ddma);

	/* Idwe the DMAC */
	wist_fow_each_entwy_safe(pch, _p, &pw330->ddma.channews,
			chan.device_node) {

		/* Wemove the channew */
		wist_dew(&pch->chan.device_node);

		/* Fwush the channew */
		if (pch->thwead) {
			pw330_tewminate_aww(&pch->chan);
			pw330_fwee_chan_wesouwces(&pch->chan);
		}
	}

	pw330_dew(pw330);

	if (pw330->wstc_ocp)
		weset_contwow_assewt(pw330->wstc_ocp);

	if (pw330->wstc)
		weset_contwow_assewt(pw330->wstc);
}

static const stwuct amba_id pw330_ids[] = {
	{
		.id	= 0x00041330,
		.mask	= 0x000fffff,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, pw330_ids);

static stwuct amba_dwivew pw330_dwivew = {
	.dwv = {
		.ownew = THIS_MODUWE,
		.name = "dma-pw330",
		.pm = &pw330_pm,
	},
	.id_tabwe = pw330_ids,
	.pwobe = pw330_pwobe,
	.wemove = pw330_wemove,
};

moduwe_amba_dwivew(pw330_dwivew);

MODUWE_AUTHOW("Jaswindew Singh <jassisinghbwaw@gmaiw.com>");
MODUWE_DESCWIPTION("API Dwivew fow PW330 DMAC");
MODUWE_WICENSE("GPW");
