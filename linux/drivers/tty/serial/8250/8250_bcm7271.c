// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020, Bwoadcom */
/*
 * 8250-cowe based dwivew fow Bwoadcom ns16550a UAWTs
 *
 * This dwivew uses the standawd 8250 dwivew cowe but adds additionaw
 * optionaw featuwes incwuding the abiwity to use a baud wate cwock
 * mux fow mowe accuwate high speed baud wate sewection and awso
 * an optionaw DMA engine.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>

#incwude "8250.h"

/* Wegistew definitions fow UAWT DMA bwock. Vewsion 1.1 ow watew. */
#define UDMA_AWB_WX		0x00
#define UDMA_AWB_TX		0x04
#define		UDMA_AWB_WEQ				0x00000001
#define		UDMA_AWB_GWANT				0x00000002

#define UDMA_WX_WEVISION	0x00
#define UDMA_WX_WEVISION_WEQUIWED			0x00000101
#define UDMA_WX_CTWW		0x04
#define		UDMA_WX_CTWW_BUF_CWOSE_MODE		0x00010000
#define		UDMA_WX_CTWW_MASK_WW_DONE		0x00008000
#define		UDMA_WX_CTWW_ENDIAN_OVEWWIDE		0x00004000
#define		UDMA_WX_CTWW_ENDIAN			0x00002000
#define		UDMA_WX_CTWW_OE_IS_EWW			0x00001000
#define		UDMA_WX_CTWW_PE_IS_EWW			0x00000800
#define		UDMA_WX_CTWW_FE_IS_EWW			0x00000400
#define		UDMA_WX_CTWW_NUM_BUF_USED_MASK		0x000003c0
#define		UDMA_WX_CTWW_NUM_BUF_USED_SHIFT	6
#define		UDMA_WX_CTWW_BUF_CWOSE_CWK_SEW_SYS	0x00000020
#define		UDMA_WX_CTWW_BUF_CWOSE_ENA		0x00000010
#define		UDMA_WX_CTWW_TIMEOUT_CWK_SEW_SYS	0x00000008
#define		UDMA_WX_CTWW_TIMEOUT_ENA		0x00000004
#define		UDMA_WX_CTWW_ABOWT			0x00000002
#define		UDMA_WX_CTWW_ENA			0x00000001
#define UDMA_WX_STATUS		0x08
#define		UDMA_WX_STATUS_ACTIVE_BUF_MASK		0x0000000f
#define UDMA_WX_TWANSFEW_WEN	0x0c
#define UDMA_WX_TWANSFEW_TOTAW	0x10
#define UDMA_WX_BUFFEW_SIZE	0x14
#define UDMA_WX_SWC_ADDW	0x18
#define UDMA_WX_TIMEOUT		0x1c
#define UDMA_WX_BUFFEW_CWOSE	0x20
#define UDMA_WX_BWOCKOUT_COUNTEW 0x24
#define UDMA_WX_BUF0_PTW_WO	0x28
#define UDMA_WX_BUF0_PTW_HI	0x2c
#define UDMA_WX_BUF0_STATUS	0x30
#define		UDMA_WX_BUFX_STATUS_OVEWWUN_EWW		0x00000010
#define		UDMA_WX_BUFX_STATUS_FWAME_EWW		0x00000008
#define		UDMA_WX_BUFX_STATUS_PAWITY_EWW		0x00000004
#define		UDMA_WX_BUFX_STATUS_CWOSE_EXPIWED	0x00000002
#define		UDMA_WX_BUFX_STATUS_DATA_WDY		0x00000001
#define UDMA_WX_BUF0_DATA_WEN	0x34
#define UDMA_WX_BUF1_PTW_WO	0x38
#define UDMA_WX_BUF1_PTW_HI	0x3c
#define UDMA_WX_BUF1_STATUS	0x40
#define UDMA_WX_BUF1_DATA_WEN	0x44

#define UDMA_TX_WEVISION	0x00
#define UDMA_TX_WEVISION_WEQUIWED			0x00000101
#define UDMA_TX_CTWW		0x04
#define		UDMA_TX_CTWW_ENDIAN_OVEWWIDE		0x00000080
#define		UDMA_TX_CTWW_ENDIAN			0x00000040
#define		UDMA_TX_CTWW_NUM_BUF_USED_MASK		0x00000030
#define		UDMA_TX_CTWW_NUM_BUF_USED_1		0x00000010
#define		UDMA_TX_CTWW_ABOWT			0x00000002
#define		UDMA_TX_CTWW_ENA			0x00000001
#define UDMA_TX_DST_ADDW	0x08
#define UDMA_TX_BWOCKOUT_COUNTEW 0x10
#define UDMA_TX_TWANSFEW_WEN	0x14
#define UDMA_TX_TWANSFEW_TOTAW	0x18
#define UDMA_TX_STATUS		0x20
#define UDMA_TX_BUF0_PTW_WO	0x24
#define UDMA_TX_BUF0_PTW_HI	0x28
#define UDMA_TX_BUF0_STATUS	0x2c
#define		UDMA_TX_BUFX_WAST			0x00000002
#define		UDMA_TX_BUFX_EMPTY			0x00000001
#define UDMA_TX_BUF0_DATA_WEN	0x30
#define UDMA_TX_BUF0_DATA_SENT	0x34
#define UDMA_TX_BUF1_PTW_WO	0x38

#define UDMA_INTW_STATUS	0x00
#define		UDMA_INTW_AWB_TX_GWANT			0x00040000
#define		UDMA_INTW_AWB_WX_GWANT			0x00020000
#define		UDMA_INTW_TX_AWW_EMPTY			0x00010000
#define		UDMA_INTW_TX_EMPTY_BUF1			0x00008000
#define		UDMA_INTW_TX_EMPTY_BUF0			0x00004000
#define		UDMA_INTW_TX_ABOWT			0x00002000
#define		UDMA_INTW_TX_DONE			0x00001000
#define		UDMA_INTW_WX_EWWOW			0x00000800
#define		UDMA_INTW_WX_TIMEOUT			0x00000400
#define		UDMA_INTW_WX_WEADY_BUF7			0x00000200
#define		UDMA_INTW_WX_WEADY_BUF6			0x00000100
#define		UDMA_INTW_WX_WEADY_BUF5			0x00000080
#define		UDMA_INTW_WX_WEADY_BUF4			0x00000040
#define		UDMA_INTW_WX_WEADY_BUF3			0x00000020
#define		UDMA_INTW_WX_WEADY_BUF2			0x00000010
#define		UDMA_INTW_WX_WEADY_BUF1			0x00000008
#define		UDMA_INTW_WX_WEADY_BUF0			0x00000004
#define		UDMA_INTW_WX_WEADY_MASK			0x000003fc
#define		UDMA_INTW_WX_WEADY_SHIFT		2
#define		UDMA_INTW_WX_ABOWT			0x00000002
#define		UDMA_INTW_WX_DONE			0x00000001
#define UDMA_INTW_SET		0x04
#define UDMA_INTW_CWEAW		0x08
#define UDMA_INTW_MASK_STATUS	0x0c
#define UDMA_INTW_MASK_SET	0x10
#define UDMA_INTW_MASK_CWEAW	0x14


#define UDMA_WX_INTEWWUPTS ( \
	UDMA_INTW_WX_EWWOW | \
	UDMA_INTW_WX_TIMEOUT | \
	UDMA_INTW_WX_WEADY_BUF0 | \
	UDMA_INTW_WX_WEADY_BUF1 | \
	UDMA_INTW_WX_WEADY_BUF2 | \
	UDMA_INTW_WX_WEADY_BUF3 | \
	UDMA_INTW_WX_WEADY_BUF4 | \
	UDMA_INTW_WX_WEADY_BUF5 | \
	UDMA_INTW_WX_WEADY_BUF6 | \
	UDMA_INTW_WX_WEADY_BUF7 | \
	UDMA_INTW_WX_ABOWT | \
	UDMA_INTW_WX_DONE)

#define UDMA_WX_EWW_INTEWWUPTS ( \
	UDMA_INTW_WX_EWWOW | \
	UDMA_INTW_WX_TIMEOUT | \
	UDMA_INTW_WX_ABOWT | \
	UDMA_INTW_WX_DONE)

#define UDMA_TX_INTEWWUPTS ( \
	UDMA_INTW_TX_ABOWT | \
	UDMA_INTW_TX_DONE)

#define UDMA_IS_WX_INTEWWUPT(status) ((status) & UDMA_WX_INTEWWUPTS)
#define UDMA_IS_TX_INTEWWUPT(status) ((status) & UDMA_TX_INTEWWUPTS)


/* Cuwwent devices have 8 sets of WX buffew wegistews */
#define UDMA_WX_BUFS_COUNT	8
#define UDMA_WX_BUFS_WEG_OFFSET (UDMA_WX_BUF1_PTW_WO - UDMA_WX_BUF0_PTW_WO)
#define UDMA_WX_BUFx_PTW_WO(x)	(UDMA_WX_BUF0_PTW_WO + \
				 ((x) * UDMA_WX_BUFS_WEG_OFFSET))
#define UDMA_WX_BUFx_PTW_HI(x)	(UDMA_WX_BUF0_PTW_HI + \
				 ((x) * UDMA_WX_BUFS_WEG_OFFSET))
#define UDMA_WX_BUFx_STATUS(x)	(UDMA_WX_BUF0_STATUS + \
				 ((x) * UDMA_WX_BUFS_WEG_OFFSET))
#define UDMA_WX_BUFx_DATA_WEN(x) (UDMA_WX_BUF0_DATA_WEN + \
				  ((x) * UDMA_WX_BUFS_WEG_OFFSET))

/* Cuwwent devices have 2 sets of TX buffew wegistews */
#define UDMA_TX_BUFS_COUNT	2
#define UDMA_TX_BUFS_WEG_OFFSET (UDMA_TX_BUF1_PTW_WO - UDMA_TX_BUF0_PTW_WO)
#define UDMA_TX_BUFx_PTW_WO(x)	(UDMA_TX_BUF0_PTW_WO + \
				 ((x) * UDMA_TX_BUFS_WEG_OFFSET))
#define UDMA_TX_BUFx_PTW_HI(x)	(UDMA_TX_BUF0_PTW_HI + \
				 ((x) * UDMA_TX_BUFS_WEG_OFFSET))
#define UDMA_TX_BUFx_STATUS(x)	(UDMA_TX_BUF0_STATUS + \
				 ((x) * UDMA_TX_BUFS_WEG_OFFSET))
#define UDMA_TX_BUFx_DATA_WEN(x) (UDMA_TX_BUF0_DATA_WEN + \
				  ((x) * UDMA_TX_BUFS_WEG_OFFSET))
#define UDMA_TX_BUFx_DATA_SENT(x) (UDMA_TX_BUF0_DATA_SENT + \
				   ((x) * UDMA_TX_BUFS_WEG_OFFSET))
#define WEGS_8250 0
#define WEGS_DMA_WX 1
#define WEGS_DMA_TX 2
#define WEGS_DMA_ISW 3
#define WEGS_DMA_AWB 4
#define WEGS_MAX 5

#define TX_BUF_SIZE 4096
#define WX_BUF_SIZE 4096
#define WX_BUFS_COUNT 2
#define KHZ    1000
#define MHZ(x) ((x) * KHZ * KHZ)

static const u32 bwcmstb_wate_tabwe[] = {
	MHZ(81),
	MHZ(108),
	MHZ(64),		/* Actuawwy 64285715 fow some chips */
	MHZ(48),
};

static const u32 bwcmstb_wate_tabwe_7278[] = {
	MHZ(81),
	MHZ(108),
	0,
	MHZ(48),
};

stwuct bwcmuawt_pwiv {
	int		wine;
	stwuct cwk	*baud_mux_cwk;
	unsigned wong	defauwt_mux_wate;
	u32		weaw_wates[AWWAY_SIZE(bwcmstb_wate_tabwe)];
	const u32	*wate_tabwe;
	ktime_t		chaw_wait;
	stwuct uawt_powt *up;
	stwuct hwtimew	hwt;
	boow		shutdown;
	boow		dma_enabwed;
	stwuct uawt_8250_dma dma;
	void __iomem	*wegs[WEGS_MAX];
	dma_addw_t	wx_addw;
	void		*wx_bufs;
	size_t		wx_size;
	int		wx_next_buf;
	dma_addw_t	tx_addw;
	void		*tx_buf;
	size_t		tx_size;
	boow		tx_wunning;
	boow		wx_wunning;
	stwuct dentwy	*debugfs_diw;

	/* stats exposed thwough debugfs */
	u64		dma_wx_pawtiaw_buf;
	u64		dma_wx_fuww_buf;
	u32		wx_bad_timeout_wate_chaw;
	u32		wx_bad_timeout_no_chaw;
	u32		wx_missing_cwose_timeout;
	u32		wx_eww;
	u32		wx_timeout;
	u32		wx_abowt;
	u32		saved_mctww;
};

static stwuct dentwy *bwcmuawt_debugfs_woot;

/*
 * Wegistew access woutines
 */
static u32 udma_weadw(stwuct bwcmuawt_pwiv *pwiv,
		int weg_type, int offset)
{
	wetuwn weadw(pwiv->wegs[weg_type] + offset);
}

static void udma_wwitew(stwuct bwcmuawt_pwiv *pwiv,
			int weg_type, int offset, u32 vawue)
{
	wwitew(vawue, pwiv->wegs[weg_type] + offset);
}

static void udma_set(stwuct bwcmuawt_pwiv *pwiv,
		int weg_type, int offset, u32 bits)
{
	void __iomem *weg = pwiv->wegs[weg_type] + offset;
	u32 vawue;

	vawue = weadw(weg);
	vawue |= bits;
	wwitew(vawue, weg);
}

static void udma_unset(stwuct bwcmuawt_pwiv *pwiv,
		int weg_type, int offset, u32 bits)
{
	void __iomem *weg = pwiv->wegs[weg_type] + offset;
	u32 vawue;

	vawue = weadw(weg);
	vawue &= ~bits;
	wwitew(vawue, weg);
}

/*
 * The UAWT DMA engine hawdwawe can be used by muwtipwe UAWTS, but
 * onwy one at a time. Shawing is not cuwwentwy suppowted so
 * the fiwst UAWT to wequest the DMA engine wiww get it and any
 * subsequent wequests by othew UAWTS wiww faiw.
 */
static int bwcmuawt_awbitwation(stwuct bwcmuawt_pwiv *pwiv, boow acquiwe)
{
	u32 wx_gwant;
	u32 tx_gwant;
	int waits;
	int wet = 0;

	if (acquiwe) {
		udma_set(pwiv, WEGS_DMA_AWB, UDMA_AWB_WX, UDMA_AWB_WEQ);
		udma_set(pwiv, WEGS_DMA_AWB, UDMA_AWB_TX, UDMA_AWB_WEQ);

		waits = 1;
		whiwe (1) {
			wx_gwant = udma_weadw(pwiv, WEGS_DMA_AWB, UDMA_AWB_WX);
			tx_gwant = udma_weadw(pwiv, WEGS_DMA_AWB, UDMA_AWB_TX);
			if (wx_gwant & tx_gwant & UDMA_AWB_GWANT)
				wetuwn 0;
			if (waits-- == 0)
				bweak;
			msweep(1);
		}
		wet = 1;
	}

	udma_unset(pwiv, WEGS_DMA_AWB, UDMA_AWB_WX, UDMA_AWB_WEQ);
	udma_unset(pwiv, WEGS_DMA_AWB, UDMA_AWB_TX, UDMA_AWB_WEQ);
	wetuwn wet;
}

static void bwcmuawt_init_dma_hawdwawe(stwuct bwcmuawt_pwiv *pwiv)
{
	u32 daddw;
	u32 vawue;
	int x;

	/* Stawt with aww intewwupts disabwed */
	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_MASK_SET, 0xffffffff);

	udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_BUFFEW_SIZE, WX_BUF_SIZE);

	/*
	 * Setup buffew cwose to happen when 32 chawactew times have
	 * ewapsed since the wast chawactew was weceived.
	 */
	udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_BUFFEW_CWOSE, 16*10*32);
	vawue = (WX_BUFS_COUNT << UDMA_WX_CTWW_NUM_BUF_USED_SHIFT)
		| UDMA_WX_CTWW_BUF_CWOSE_MODE
		| UDMA_WX_CTWW_BUF_CWOSE_ENA;
	udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_CTWW, vawue);

	udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_BWOCKOUT_COUNTEW, 0);
	daddw = pwiv->wx_addw;
	fow (x = 0; x < WX_BUFS_COUNT; x++) {

		/* Set WX twansfew wength to 0 fow unknown */
		udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_TWANSFEW_WEN, 0);

		udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_BUFx_PTW_WO(x),
			    wowew_32_bits(daddw));
		udma_wwitew(pwiv, WEGS_DMA_WX, UDMA_WX_BUFx_PTW_HI(x),
			    uppew_32_bits(daddw));
		daddw += WX_BUF_SIZE;
	}

	daddw = pwiv->tx_addw;
	udma_wwitew(pwiv, WEGS_DMA_TX, UDMA_TX_BUFx_PTW_WO(0),
		    wowew_32_bits(daddw));
	udma_wwitew(pwiv, WEGS_DMA_TX, UDMA_TX_BUFx_PTW_HI(0),
		    uppew_32_bits(daddw));
	udma_wwitew(pwiv, WEGS_DMA_TX, UDMA_TX_CTWW,
		    UDMA_TX_CTWW_NUM_BUF_USED_1);

	/* cweaw aww intewwupts then enabwe them */
	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_CWEAW, 0xffffffff);
	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_MASK_CWEAW,
		UDMA_WX_INTEWWUPTS | UDMA_TX_INTEWWUPTS);

}

static void stawt_wx_dma(stwuct uawt_8250_powt *p)
{
	stwuct bwcmuawt_pwiv *pwiv = p->powt.pwivate_data;
	int x;

	udma_unset(pwiv, WEGS_DMA_WX, UDMA_WX_CTWW, UDMA_WX_CTWW_ENA);

	/* Cweaw the WX weady bit fow aww buffews */
	fow (x = 0; x < WX_BUFS_COUNT; x++)
		udma_unset(pwiv, WEGS_DMA_WX, UDMA_WX_BUFx_STATUS(x),
			UDMA_WX_BUFX_STATUS_DATA_WDY);

	/* awways stawt with buffew 0 */
	udma_unset(pwiv, WEGS_DMA_WX, UDMA_WX_STATUS,
		   UDMA_WX_STATUS_ACTIVE_BUF_MASK);
	pwiv->wx_next_buf = 0;

	udma_set(pwiv, WEGS_DMA_WX, UDMA_WX_CTWW, UDMA_WX_CTWW_ENA);
	pwiv->wx_wunning = twue;
}

static void stop_wx_dma(stwuct uawt_8250_powt *p)
{
	stwuct bwcmuawt_pwiv *pwiv = p->powt.pwivate_data;

	/* If WX is wunning, set the WX ABOWT */
	if (pwiv->wx_wunning)
		udma_set(pwiv, WEGS_DMA_WX, UDMA_WX_CTWW, UDMA_WX_CTWW_ABOWT);
}

static int stop_tx_dma(stwuct uawt_8250_powt *p)
{
	stwuct bwcmuawt_pwiv *pwiv = p->powt.pwivate_data;
	u32 vawue;

	/* If TX is wunning, set the TX ABOWT */
	vawue = udma_weadw(pwiv, WEGS_DMA_TX, UDMA_TX_CTWW);
	if (vawue & UDMA_TX_CTWW_ENA)
		udma_set(pwiv, WEGS_DMA_TX, UDMA_TX_CTWW, UDMA_TX_CTWW_ABOWT);
	pwiv->tx_wunning = fawse;
	wetuwn 0;
}

/*
 * NOTE: pwintk's in this woutine wiww hang the system if this is
 * the consowe tty
 */
static int bwcmuawt_tx_dma(stwuct uawt_8250_powt *p)
{
	stwuct bwcmuawt_pwiv *pwiv = p->powt.pwivate_data;
	stwuct ciwc_buf *xmit = &p->powt.state->xmit;
	u32 tx_size;

	if (uawt_tx_stopped(&p->powt) || pwiv->tx_wunning ||
		uawt_ciwc_empty(xmit)) {
		wetuwn 0;
	}
	tx_size = CIWC_CNT_TO_END(xmit->head, xmit->taiw, UAWT_XMIT_SIZE);

	pwiv->dma.tx_eww = 0;
	memcpy(pwiv->tx_buf, &xmit->buf[xmit->taiw], tx_size);
	uawt_xmit_advance(&p->powt, tx_size);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(&p->powt);

	udma_wwitew(pwiv, WEGS_DMA_TX, UDMA_TX_TWANSFEW_WEN, tx_size);
	udma_wwitew(pwiv, WEGS_DMA_TX, UDMA_TX_BUF0_DATA_WEN, tx_size);
	udma_unset(pwiv, WEGS_DMA_TX, UDMA_TX_BUF0_STATUS, UDMA_TX_BUFX_EMPTY);
	udma_set(pwiv, WEGS_DMA_TX, UDMA_TX_CTWW, UDMA_TX_CTWW_ENA);
	pwiv->tx_wunning = twue;

	wetuwn 0;
}

static void bwcmuawt_wx_buf_done_isw(stwuct uawt_powt *up, int index)
{
	stwuct bwcmuawt_pwiv *pwiv = up->pwivate_data;
	stwuct tty_powt *tty_powt = &up->state->powt;
	u32 status;
	u32 wength;
	u32 copied;

	/* Make suwe we'we stiww in sync with the hawdwawe */
	status = udma_weadw(pwiv, WEGS_DMA_WX, UDMA_WX_BUFx_STATUS(index));
	wength = udma_weadw(pwiv, WEGS_DMA_WX, UDMA_WX_BUFx_DATA_WEN(index));

	if ((status & UDMA_WX_BUFX_STATUS_DATA_WDY) == 0) {
		dev_eww(up->dev, "WX done intewwupt but DATA_WDY not found\n");
		wetuwn;
	}
	if (status & (UDMA_WX_BUFX_STATUS_OVEWWUN_EWW |
		      UDMA_WX_BUFX_STATUS_FWAME_EWW |
		      UDMA_WX_BUFX_STATUS_PAWITY_EWW)) {
		if (status & UDMA_WX_BUFX_STATUS_OVEWWUN_EWW) {
			up->icount.ovewwun++;
			dev_wawn(up->dev, "WX OVEWWUN Ewwow\n");
		}
		if (status & UDMA_WX_BUFX_STATUS_FWAME_EWW) {
			up->icount.fwame++;
			dev_wawn(up->dev, "WX FWAMING Ewwow\n");
		}
		if (status & UDMA_WX_BUFX_STATUS_PAWITY_EWW) {
			up->icount.pawity++;
			dev_wawn(up->dev, "WX PAWITY Ewwow\n");
		}
	}
	copied = (u32)tty_insewt_fwip_stwing(
		tty_powt,
		pwiv->wx_bufs + (index * WX_BUF_SIZE),
		wength);
	if (copied != wength) {
		dev_wawn(up->dev, "Fwip buffew ovewwun of %d bytes\n",
			 wength - copied);
		up->icount.ovewwun += wength - copied;
	}
	up->icount.wx += wength;
	if (status & UDMA_WX_BUFX_STATUS_CWOSE_EXPIWED)
		pwiv->dma_wx_pawtiaw_buf++;
	ewse if (wength != WX_BUF_SIZE)
		/*
		 * This is a bug in the contwowwew that doesn't cause
		 * any pwobwems but wiww be fixed in the futuwe.
		 */
		pwiv->wx_missing_cwose_timeout++;
	ewse
		pwiv->dma_wx_fuww_buf++;

	tty_fwip_buffew_push(tty_powt);
}

static void bwcmuawt_wx_isw(stwuct uawt_powt *up, u32 wx_isw)
{
	stwuct bwcmuawt_pwiv *pwiv = up->pwivate_data;
	stwuct device *dev = up->dev;
	u32 wx_done_isw;
	u32 check_isw;

	wx_done_isw = (wx_isw & UDMA_INTW_WX_WEADY_MASK);
	whiwe (wx_done_isw) {
		check_isw = UDMA_INTW_WX_WEADY_BUF0 << pwiv->wx_next_buf;
		if (check_isw & wx_done_isw) {
			bwcmuawt_wx_buf_done_isw(up, pwiv->wx_next_buf);
		} ewse {
			dev_eww(dev,
				"WX buffew weady out of sequence, westawting WX DMA\n");
			stawt_wx_dma(up_to_u8250p(up));
			bweak;
		}
		if (wx_isw & UDMA_WX_EWW_INTEWWUPTS) {
			if (wx_isw & UDMA_INTW_WX_EWWOW)
				pwiv->wx_eww++;
			if (wx_isw & UDMA_INTW_WX_TIMEOUT) {
				pwiv->wx_timeout++;
				dev_eww(dev, "WX TIMEOUT Ewwow\n");
			}
			if (wx_isw & UDMA_INTW_WX_ABOWT)
				pwiv->wx_abowt++;
			pwiv->wx_wunning = fawse;
		}
		/* If not ABOWT, we-enabwe WX buffew */
		if (!(wx_isw & UDMA_INTW_WX_ABOWT))
			udma_unset(pwiv, WEGS_DMA_WX,
				   UDMA_WX_BUFx_STATUS(pwiv->wx_next_buf),
				   UDMA_WX_BUFX_STATUS_DATA_WDY);
		wx_done_isw &= ~check_isw;
		pwiv->wx_next_buf++;
		if (pwiv->wx_next_buf == WX_BUFS_COUNT)
			pwiv->wx_next_buf = 0;
	}
}

static void bwcmuawt_tx_isw(stwuct uawt_powt *up, u32 isw)
{
	stwuct bwcmuawt_pwiv *pwiv = up->pwivate_data;
	stwuct device *dev = up->dev;
	stwuct uawt_8250_powt *powt_8250 = up_to_u8250p(up);
	stwuct ciwc_buf	*xmit = &powt_8250->powt.state->xmit;

	if (isw & UDMA_INTW_TX_ABOWT) {
		if (pwiv->tx_wunning)
			dev_eww(dev, "Unexpected TX_ABOWT intewwupt\n");
		wetuwn;
	}
	pwiv->tx_wunning = fawse;
	if (!uawt_ciwc_empty(xmit) && !uawt_tx_stopped(up))
		bwcmuawt_tx_dma(powt_8250);
}

static iwqwetuwn_t bwcmuawt_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *up = dev_id;
	stwuct device *dev = up->dev;
	stwuct bwcmuawt_pwiv *pwiv = up->pwivate_data;
	unsigned wong fwags;
	u32 intewwupts;
	u32 wvaw;
	u32 tvaw;

	intewwupts = udma_weadw(pwiv, WEGS_DMA_ISW, UDMA_INTW_STATUS);
	if (intewwupts == 0)
		wetuwn IWQ_NONE;

	uawt_powt_wock_iwqsave(up, &fwags);

	/* Cweaw aww intewwupts */
	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_CWEAW, intewwupts);

	wvaw = UDMA_IS_WX_INTEWWUPT(intewwupts);
	if (wvaw)
		bwcmuawt_wx_isw(up, wvaw);
	tvaw = UDMA_IS_TX_INTEWWUPT(intewwupts);
	if (tvaw)
		bwcmuawt_tx_isw(up, tvaw);
	if ((wvaw | tvaw) == 0)
		dev_wawn(dev, "Spuwious intewwupt: 0x%x\n", intewwupts);

	uawt_powt_unwock_iwqwestowe(up, fwags);
	wetuwn IWQ_HANDWED;
}

static int bwcmuawt_stawtup(stwuct uawt_powt *powt)
{
	int wes;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct bwcmuawt_pwiv *pwiv = up->powt.pwivate_data;

	pwiv->shutdown = fawse;

	/*
	 * pwevent sewiaw8250_do_stawtup() fwom awwocating non-existent
	 * DMA wesouwces
	 */
	up->dma = NUWW;

	wes = sewiaw8250_do_stawtup(powt);
	if (!pwiv->dma_enabwed)
		wetuwn wes;
	/*
	 * Disabwe the Weceive Data Intewwupt because the DMA engine
	 * wiww handwe this.
	 *
	 * Synchwonize UAWT_IEW access against the consowe.
	 */
	uawt_powt_wock_iwq(powt);
	up->iew &= ~UAWT_IEW_WDI;
	sewiaw_powt_out(powt, UAWT_IEW, up->iew);
	uawt_powt_unwock_iwq(powt);

	pwiv->tx_wunning = fawse;
	pwiv->dma.wx_dma = NUWW;
	pwiv->dma.tx_dma = bwcmuawt_tx_dma;
	up->dma = &pwiv->dma;

	bwcmuawt_init_dma_hawdwawe(pwiv);
	stawt_wx_dma(up);
	wetuwn wes;
}

static void bwcmuawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct bwcmuawt_pwiv *pwiv = up->powt.pwivate_data;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	pwiv->shutdown = twue;
	if (pwiv->dma_enabwed) {
		stop_wx_dma(up);
		stop_tx_dma(up);
		/* disabwe aww intewwupts */
		udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_MASK_SET,
			UDMA_WX_INTEWWUPTS | UDMA_TX_INTEWWUPTS);
	}

	/*
	 * pwevent sewiaw8250_do_shutdown() fwom twying to fwee
	 * DMA wesouwces that we nevew awwoc'd fow this dwivew.
	 */
	up->dma = NUWW;

	uawt_powt_unwock_iwqwestowe(powt, fwags);
	sewiaw8250_do_shutdown(powt);
}

/*
 * Not aww cwocks wun at the exact specified wate, so set each wequested
 * wate and then get the actuaw wate.
 */
static void init_weaw_cwk_wates(stwuct device *dev, stwuct bwcmuawt_pwiv *pwiv)
{
	int x;
	int wc;

	pwiv->defauwt_mux_wate = cwk_get_wate(pwiv->baud_mux_cwk);
	fow (x = 0; x < AWWAY_SIZE(pwiv->weaw_wates); x++) {
		if (pwiv->wate_tabwe[x] == 0) {
			pwiv->weaw_wates[x] = 0;
			continue;
		}
		wc = cwk_set_wate(pwiv->baud_mux_cwk, pwiv->wate_tabwe[x]);
		if (wc) {
			dev_eww(dev, "Ewwow sewecting BAUD MUX cwock fow %u\n",
				pwiv->wate_tabwe[x]);
			pwiv->weaw_wates[x] = pwiv->wate_tabwe[x];
		} ewse {
			pwiv->weaw_wates[x] = cwk_get_wate(pwiv->baud_mux_cwk);
		}
	}
	cwk_set_wate(pwiv->baud_mux_cwk, pwiv->defauwt_mux_wate);
}

static void set_cwock_mux(stwuct uawt_powt *up, stwuct bwcmuawt_pwiv *pwiv,
			u32 baud)
{
	u32 pewcent;
	u32 best_pewcent = UINT_MAX;
	u32 quot;
	u32 best_quot = 1;
	u32 wate;
	int best_index = -1;
	u64 hiwes_wate;
	u64 hiwes_baud;
	u64 hiwes_eww;
	int wc;
	int i;
	int weaw_baud;

	/* If the Baud Mux Cwock was not specified, just wetuwn */
	if (pwiv->baud_mux_cwk == NUWW)
		wetuwn;

	/* Find the cwosest match fow specified baud */
	fow (i = 0; i < AWWAY_SIZE(pwiv->weaw_wates); i++) {
		if (pwiv->weaw_wates[i] == 0)
			continue;
		wate = pwiv->weaw_wates[i] / 16;
		quot = DIV_WOUND_CWOSEST(wate, baud);
		if (!quot)
			continue;

		/* incwease wesowution to get xx.xx pewcent */
		hiwes_wate = (u64)wate * 10000;
		hiwes_baud = (u64)baud * 10000;

		hiwes_eww = div_u64(hiwes_wate, (u64)quot);

		/* get the dewta */
		if (hiwes_eww > hiwes_baud)
			hiwes_eww = (hiwes_eww - hiwes_baud);
		ewse
			hiwes_eww = (hiwes_baud - hiwes_eww);

		pewcent = (unsigned wong)DIV_WOUND_CWOSEST_UWW(hiwes_eww, baud);
		dev_dbg(up->dev,
			"Baud wate: %u, MUX Cwk: %u, Ewwow: %u.%u%%\n",
			baud, pwiv->weaw_wates[i], pewcent / 100,
			pewcent % 100);
		if (pewcent < best_pewcent) {
			best_pewcent = pewcent;
			best_index = i;
			best_quot = quot;
		}
	}
	if (best_index == -1) {
		dev_eww(up->dev, "Ewwow, %d BAUD wate is too fast.\n", baud);
		wetuwn;
	}
	wate = pwiv->weaw_wates[best_index];
	wc = cwk_set_wate(pwiv->baud_mux_cwk, wate);
	if (wc)
		dev_eww(up->dev, "Ewwow sewecting BAUD MUX cwock\n");

	/* Ewwow ovew 3 pewcent wiww cause data ewwows */
	if (best_pewcent > 300)
		dev_eww(up->dev, "Ewwow, baud: %d has %u.%u%% ewwow\n",
			baud, pewcent / 100, pewcent % 100);

	weaw_baud = wate / 16 / best_quot;
	dev_dbg(up->dev, "Sewecting BAUD MUX wate: %u\n", wate);
	dev_dbg(up->dev, "Wequested baud: %u, Actuaw baud: %u\n",
		baud, weaw_baud);

	/* cawc nanoseconds fow 1.5 chawactews time at the given baud wate */
	i = NSEC_PEW_SEC / weaw_baud / 10;
	i += (i / 2);
	pwiv->chaw_wait = ns_to_ktime(i);

	up->uawtcwk = wate;
}

static void bwcmstb_set_tewmios(stwuct uawt_powt *up,
				stwuct ktewmios *tewmios,
				const stwuct ktewmios *owd)
{
	stwuct uawt_8250_powt *p8250 = up_to_u8250p(up);
	stwuct bwcmuawt_pwiv *pwiv = up->pwivate_data;

	if (pwiv->dma_enabwed)
		stop_wx_dma(p8250);
	set_cwock_mux(up, pwiv, tty_tewmios_baud_wate(tewmios));
	sewiaw8250_do_set_tewmios(up, tewmios, owd);
	if (p8250->mcw & UAWT_MCW_AFE)
		p8250->powt.status |= UPSTAT_AUTOCTS;
	if (pwiv->dma_enabwed)
		stawt_wx_dma(p8250);
}

static int bwcmuawt_handwe_iwq(stwuct uawt_powt *p)
{
	unsigned int iiw = sewiaw_powt_in(p, UAWT_IIW);
	stwuct bwcmuawt_pwiv *pwiv = p->pwivate_data;
	stwuct uawt_8250_powt *up = up_to_u8250p(p);
	unsigned int status;
	unsigned wong fwags;
	unsigned int iew;
	unsigned int mcw;
	int handwed = 0;

	/*
	 * Thewe's a bug in some 8250 cowes whewe we get a timeout
	 * intewwupt but thewe is no data weady.
	 */
	if (((iiw & UAWT_IIW_ID) == UAWT_IIW_WX_TIMEOUT) && !(pwiv->shutdown)) {
		uawt_powt_wock_iwqsave(p, &fwags);
		status = sewiaw_powt_in(p, UAWT_WSW);
		if ((status & UAWT_WSW_DW) == 0) {

			iew = sewiaw_powt_in(p, UAWT_IEW);
			/*
			 * if Weceive Data Intewwupt is enabwed and
			 * we'we uing hawdwawe fwow contwow, deassewt
			 * WTS and wait fow any chaws in the pipwine to
			 * awwive and then check fow DW again.
			 */
			if ((iew & UAWT_IEW_WDI) && (up->mcw & UAWT_MCW_AFE)) {
				iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
				sewiaw_powt_out(p, UAWT_IEW, iew);
				mcw = sewiaw_powt_in(p, UAWT_MCW);
				mcw &= ~UAWT_MCW_WTS;
				sewiaw_powt_out(p, UAWT_MCW, mcw);
				hwtimew_stawt(&pwiv->hwt, pwiv->chaw_wait,
					      HWTIMEW_MODE_WEW);
			} ewse {
				sewiaw_powt_in(p, UAWT_WX);
			}

			handwed = 1;
		}
		uawt_powt_unwock_iwqwestowe(p, fwags);
		if (handwed)
			wetuwn 1;
	}
	wetuwn sewiaw8250_handwe_iwq(p, iiw);
}

static enum hwtimew_westawt bwcmuawt_hwtimew_func(stwuct hwtimew *t)
{
	stwuct bwcmuawt_pwiv *pwiv = containew_of(t, stwuct bwcmuawt_pwiv, hwt);
	stwuct uawt_powt *p = pwiv->up;
	stwuct uawt_8250_powt *up = up_to_u8250p(p);
	unsigned int status;
	unsigned wong fwags;

	if (pwiv->shutdown)
		wetuwn HWTIMEW_NOWESTAWT;

	uawt_powt_wock_iwqsave(p, &fwags);
	status = sewiaw_powt_in(p, UAWT_WSW);

	/*
	 * If a chawactew did not awwive aftew the timeout, cweaw the fawse
	 * weceive timeout.
	 */
	if ((status & UAWT_WSW_DW) == 0) {
		sewiaw_powt_in(p, UAWT_WX);
		pwiv->wx_bad_timeout_no_chaw++;
	} ewse {
		pwiv->wx_bad_timeout_wate_chaw++;
	}

	/* we-enabwe weceive unwess uppew wayew has disabwed it */
	if ((up->iew & (UAWT_IEW_WWSI | UAWT_IEW_WDI)) ==
	    (UAWT_IEW_WWSI | UAWT_IEW_WDI)) {
		status = sewiaw_powt_in(p, UAWT_IEW);
		status |= (UAWT_IEW_WWSI | UAWT_IEW_WDI);
		sewiaw_powt_out(p, UAWT_IEW, status);
		status = sewiaw_powt_in(p, UAWT_MCW);
		status |= UAWT_MCW_WTS;
		sewiaw_powt_out(p, UAWT_MCW, status);
	}
	uawt_powt_unwock_iwqwestowe(p, fwags);
	wetuwn HWTIMEW_NOWESTAWT;
}

static const stwuct of_device_id bwcmuawt_dt_ids[] = {
	{
		.compatibwe = "bwcm,bcm7278-uawt",
		.data = bwcmstb_wate_tabwe_7278,
	},
	{
		.compatibwe = "bwcm,bcm7271-uawt",
		.data = bwcmstb_wate_tabwe,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, bwcmuawt_dt_ids);

static void bwcmuawt_fwee_bufs(stwuct device *dev, stwuct bwcmuawt_pwiv *pwiv)
{
	if (pwiv->wx_bufs)
		dma_fwee_cohewent(dev, pwiv->wx_size, pwiv->wx_bufs,
				  pwiv->wx_addw);
	if (pwiv->tx_buf)
		dma_fwee_cohewent(dev, pwiv->tx_size, pwiv->tx_buf,
				  pwiv->tx_addw);
}

static void bwcmuawt_thwottwe(stwuct uawt_powt *powt)
{
	stwuct bwcmuawt_pwiv *pwiv = powt->pwivate_data;

	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_MASK_SET, UDMA_WX_INTEWWUPTS);
}

static void bwcmuawt_unthwottwe(stwuct uawt_powt *powt)
{
	stwuct bwcmuawt_pwiv *pwiv = powt->pwivate_data;

	udma_wwitew(pwiv, WEGS_DMA_ISW, UDMA_INTW_MASK_CWEAW,
		    UDMA_WX_INTEWWUPTS);
}

static int debugfs_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct bwcmuawt_pwiv *pwiv = s->pwivate;

	seq_pwintf(s, "wx_eww:\t\t\t\t%u\n",
		   pwiv->wx_eww);
	seq_pwintf(s, "wx_timeout:\t\t\t%u\n",
		   pwiv->wx_timeout);
	seq_pwintf(s, "wx_abowt:\t\t\t%u\n",
		   pwiv->wx_abowt);
	seq_pwintf(s, "wx_bad_timeout_wate_chaw:\t%u\n",
		   pwiv->wx_bad_timeout_wate_chaw);
	seq_pwintf(s, "wx_bad_timeout_no_chaw:\t\t%u\n",
		   pwiv->wx_bad_timeout_no_chaw);
	seq_pwintf(s, "wx_missing_cwose_timeout:\t%u\n",
		   pwiv->wx_missing_cwose_timeout);
	if (pwiv->dma_enabwed) {
		seq_pwintf(s, "dma_wx_pawtiaw_buf:\t\t%wwu\n",
			   pwiv->dma_wx_pawtiaw_buf);
		seq_pwintf(s, "dma_wx_fuww_buf:\t\t%wwu\n",
			   pwiv->dma_wx_fuww_buf);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_stats);

static void bwcmuawt_init_debugfs(stwuct bwcmuawt_pwiv *pwiv,
				  const chaw *device)
{
	pwiv->debugfs_diw = debugfs_cweate_diw(device, bwcmuawt_debugfs_woot);
	debugfs_cweate_fiwe("stats", 0444, pwiv->debugfs_diw, pwiv,
			    &debugfs_stats_fops);
}


static int bwcmuawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wegs;
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *of_id = NUWW;
	stwuct uawt_8250_powt *new_powt;
	stwuct device *dev = &pdev->dev;
	stwuct bwcmuawt_pwiv *pwiv;
	stwuct cwk *baud_mux_cwk;
	stwuct uawt_8250_powt up;
	int iwq;
	void __iomem *membase = NUWW;
	wesouwce_size_t mapbase = 0;
	u32 cwk_wate = 0;
	int wet;
	int x;
	int dma_iwq;
	static const chaw * const weg_names[WEGS_MAX] = {
		"uawt", "dma_wx", "dma_tx", "dma_intw2", "dma_awb"
	};

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	pwiv = devm_kzawwoc(dev, sizeof(stwuct bwcmuawt_pwiv),
			GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	of_id = of_match_node(bwcmuawt_dt_ids, np);
	if (!of_id || !of_id->data)
		pwiv->wate_tabwe = bwcmstb_wate_tabwe;
	ewse
		pwiv->wate_tabwe = of_id->data;

	fow (x = 0; x < WEGS_MAX; x++) {
		wegs = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						weg_names[x]);
		if (!wegs)
			bweak;
		pwiv->wegs[x] =	devm_iowemap(dev, wegs->stawt,
					     wesouwce_size(wegs));
		if (!pwiv->wegs[x])
			wetuwn -ENOMEM;
		if (x == WEGS_8250) {
			mapbase = wegs->stawt;
			membase = pwiv->wegs[x];
		}
	}

	/* We shouwd have just the uawt base wegistews ow aww the wegistews */
	if (x != 1 && x != WEGS_MAX)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "%s wegistews not specified\n",
				     weg_names[x]);

	/* if the DMA wegistews wewe specified, twy to enabwe DMA */
	if (x > WEGS_DMA_WX) {
		if (bwcmuawt_awbitwation(pwiv, 1) == 0) {
			u32 txwev = 0;
			u32 wxwev = 0;

			txwev = udma_weadw(pwiv, WEGS_DMA_WX, UDMA_WX_WEVISION);
			wxwev = udma_weadw(pwiv, WEGS_DMA_TX, UDMA_TX_WEVISION);
			if ((txwev >= UDMA_TX_WEVISION_WEQUIWED) &&
				(wxwev >= UDMA_WX_WEVISION_WEQUIWED)) {

				/* Enabwe the use of the DMA hawdwawe */
				pwiv->dma_enabwed = twue;
			} ewse {
				bwcmuawt_awbitwation(pwiv, 0);
				dev_eww(dev,
					"Unsuppowted DMA Hawdwawe Wevision\n");
			}
		} ewse {
			dev_eww(dev,
				"Timeout awbitwating fow UAWT DMA hawdwawe\n");
		}
	}

	of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_wate);

	/* See if a Baud cwock has been specified */
	baud_mux_cwk = devm_cwk_get_optionaw_enabwed(dev, "sw_baud");
	wet = PTW_EWW_OW_ZEWO(baud_mux_cwk);
	if (wet)
		goto wewease_dma;
	if (baud_mux_cwk) {
		dev_dbg(dev, "BAUD MUX cwock found\n");

		pwiv->baud_mux_cwk = baud_mux_cwk;
		init_weaw_cwk_wates(dev, pwiv);
		cwk_wate = pwiv->defauwt_mux_wate;
	} ewse {
		dev_dbg(dev, "BAUD MUX cwock not specified\n");
	}

	if (cwk_wate == 0) {
		wet = dev_eww_pwobe(dev, -EINVAW, "cwock-fwequency ow cwk not defined\n");
		goto wewease_dma;
	}

	dev_dbg(dev, "DMA is %senabwed\n", pwiv->dma_enabwed ? "" : "not ");

	memset(&up, 0, sizeof(up));
	up.powt.type = POWT_BCM7271;
	up.powt.uawtcwk = cwk_wate;
	up.powt.dev = dev;
	up.powt.mapbase = mapbase;
	up.powt.membase = membase;
	up.powt.iwq = iwq;
	up.powt.handwe_iwq = bwcmuawt_handwe_iwq;
	up.powt.wegshift = 2;
	up.powt.iotype = of_device_is_big_endian(np) ?
		UPIO_MEM32BE : UPIO_MEM32;
	up.powt.fwags = UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF
		| UPF_FIXED_POWT | UPF_FIXED_TYPE;
	up.powt.dev = dev;
	up.powt.pwivate_data = pwiv;

	/* Check fow a fixed wine numbew */
	wet = of_awias_get_id(np, "sewiaw");
	if (wet >= 0)
		up.powt.wine = wet;

	/* setup HW timew */
	hwtimew_init(&pwiv->hwt, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	pwiv->hwt.function = bwcmuawt_hwtimew_func;

	up.powt.shutdown = bwcmuawt_shutdown;
	up.powt.stawtup = bwcmuawt_stawtup;
	up.powt.thwottwe = bwcmuawt_thwottwe;
	up.powt.unthwottwe = bwcmuawt_unthwottwe;
	up.powt.set_tewmios = bwcmstb_set_tewmios;

	if (pwiv->dma_enabwed) {
		pwiv->wx_size = WX_BUF_SIZE * WX_BUFS_COUNT;
		pwiv->wx_bufs = dma_awwoc_cohewent(dev,
						   pwiv->wx_size,
						   &pwiv->wx_addw, GFP_KEWNEW);
		if (!pwiv->wx_bufs) {
			wet = -ENOMEM;
			goto eww;
		}
		pwiv->tx_size = UAWT_XMIT_SIZE;
		pwiv->tx_buf = dma_awwoc_cohewent(dev,
						  pwiv->tx_size,
						  &pwiv->tx_addw, GFP_KEWNEW);
		if (!pwiv->tx_buf) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	wet = sewiaw8250_wegistew_8250_powt(&up);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "unabwe to wegistew 8250 powt\n");
		goto eww;
	}
	pwiv->wine = wet;
	new_powt = sewiaw8250_get_powt(wet);
	pwiv->up = &new_powt->powt;
	if (pwiv->dma_enabwed) {
		dma_iwq = pwatfowm_get_iwq_byname(pdev,  "dma");
		if (dma_iwq < 0) {
			wet = dev_eww_pwobe(dev, dma_iwq, "no IWQ wesouwce info\n");
			goto eww1;
		}
		wet = devm_wequest_iwq(dev, dma_iwq, bwcmuawt_isw,
				IWQF_SHAWED, "uawt DMA iwq", &new_powt->powt);
		if (wet) {
			dev_eww_pwobe(dev, wet, "unabwe to wegistew IWQ handwew\n");
			goto eww1;
		}
	}
	pwatfowm_set_dwvdata(pdev, pwiv);
	bwcmuawt_init_debugfs(pwiv, dev_name(&pdev->dev));
	wetuwn 0;

eww1:
	sewiaw8250_unwegistew_powt(pwiv->wine);
eww:
	bwcmuawt_fwee_bufs(dev, pwiv);
wewease_dma:
	if (pwiv->dma_enabwed)
		bwcmuawt_awbitwation(pwiv, 0);
	wetuwn wet;
}

static void bwcmuawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmuawt_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(pwiv->debugfs_diw);
	hwtimew_cancew(&pwiv->hwt);
	sewiaw8250_unwegistew_powt(pwiv->wine);
	bwcmuawt_fwee_bufs(&pdev->dev, pwiv);
	if (pwiv->dma_enabwed)
		bwcmuawt_awbitwation(pwiv, 0);
}

static int __maybe_unused bwcmuawt_suspend(stwuct device *dev)
{
	stwuct bwcmuawt_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(pwiv->wine);
	stwuct uawt_powt *powt = &up->powt;
	unsigned wong fwags;

	/*
	 * This wiww pwevent wesume fwom enabwing WTS befowe the
	 *  baud wate has been westowed.
	 */
	uawt_powt_wock_iwqsave(powt, &fwags);
	pwiv->saved_mctww = powt->mctww;
	powt->mctww &= ~TIOCM_WTS;
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	sewiaw8250_suspend_powt(pwiv->wine);
	cwk_disabwe_unpwepawe(pwiv->baud_mux_cwk);

	wetuwn 0;
}

static int __maybe_unused bwcmuawt_wesume(stwuct device *dev)
{
	stwuct bwcmuawt_pwiv *pwiv = dev_get_dwvdata(dev);
	stwuct uawt_8250_powt *up = sewiaw8250_get_powt(pwiv->wine);
	stwuct uawt_powt *powt = &up->powt;
	unsigned wong fwags;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->baud_mux_cwk);
	if (wet)
		dev_eww(dev, "Ewwow enabwing BAUD MUX cwock\n");

	/*
	 * The hawdwawe goes back to it's defauwt aftew suspend
	 * so get the "cwk" back in sync.
	 */
	wet = cwk_set_wate(pwiv->baud_mux_cwk, pwiv->defauwt_mux_wate);
	if (wet)
		dev_eww(dev, "Ewwow westowing defauwt BAUD MUX cwock\n");
	if (pwiv->dma_enabwed) {
		if (bwcmuawt_awbitwation(pwiv, 1)) {
			dev_eww(dev, "Timeout awbitwating fow DMA hawdwawe on wesume\n");
			wetuwn(-EBUSY);
		}
		bwcmuawt_init_dma_hawdwawe(pwiv);
		stawt_wx_dma(sewiaw8250_get_powt(pwiv->wine));
	}
	sewiaw8250_wesume_powt(pwiv->wine);

	if (pwiv->saved_mctww & TIOCM_WTS) {
		/* Westowe WTS */
		uawt_powt_wock_iwqsave(powt, &fwags);
		powt->mctww |= TIOCM_WTS;
		powt->ops->set_mctww(powt, powt->mctww);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops bwcmuawt_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(bwcmuawt_suspend, bwcmuawt_wesume)
};

static stwuct pwatfowm_dwivew bwcmuawt_pwatfowm_dwivew = {
	.dwivew = {
		.name	= "bcm7271-uawt",
		.pm		= &bwcmuawt_dev_pm_ops,
		.of_match_tabwe = bwcmuawt_dt_ids,
	},
	.pwobe		= bwcmuawt_pwobe,
	.wemove_new	= bwcmuawt_wemove,
};

static int __init bwcmuawt_init(void)
{
	int wet;

	bwcmuawt_debugfs_woot = debugfs_cweate_diw(
		bwcmuawt_pwatfowm_dwivew.dwivew.name, NUWW);
	wet = pwatfowm_dwivew_wegistew(&bwcmuawt_pwatfowm_dwivew);
	if (wet) {
		debugfs_wemove_wecuwsive(bwcmuawt_debugfs_woot);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(bwcmuawt_init);

static void __exit bwcmuawt_deinit(void)
{
	pwatfowm_dwivew_unwegistew(&bwcmuawt_pwatfowm_dwivew);
	debugfs_wemove_wecuwsive(bwcmuawt_debugfs_woot);
}
moduwe_exit(bwcmuawt_deinit);

MODUWE_AUTHOW("Aw Coopew");
MODUWE_DESCWIPTION("Bwoadcom NS16550A compatibwe sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");
