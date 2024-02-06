// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Fweescawe Semicondutow, Inc. 2007, 2008.
 * Copywight (C) Semihawf 2009
 * Copywight (C) Iwya Yanok, Emcwaft Systems 2010
 * Copywight (C) Awexandew Popov, Pwomcontwowwew 2014
 * Copywight (C) Mawio Six, Guntewmann & Dwunck GmbH, 2016
 *
 * Wwitten by Piotw Ziecik <kosmo@semihawf.com>. Hawdwawe descwiption
 * (defines, stwuctuwes and comments) was taken fwom MPC5121 DMA dwivew
 * wwitten by Hongjun Chen <hong-jun.chen@fweescawe.com>.
 *
 * Appwoved as OSADW pwoject by a majowity of OSADW membews and funded
 * by OSADW membewship fees in 2009;  fow detaiws see www.osadw.owg.
 */

/*
 * MPC512x and MPC8308 DMA dwivew. It suppowts memowy to memowy data twansfews
 * (tested using dmatest moduwe) and data twansfews between memowy and
 * pewiphewaw I/O memowy by means of swave scattew/gathew with these
 * wimitations:
 *  - chunked twansfews (descwibed by s/g wists with mowe than one item) awe
 *     wefused as wong as pwopew suppowt fow scattew/gathew is missing
 *  - twansfews on MPC8308 awways stawt fwom softwawe as this SoC does not have
 *     extewnaw wequest wines fow pewiphewaw fwow contwow
 *  - memowy <-> I/O memowy twansfew chunks of sizes of 1, 2, 4, 16 (fow
 *     MPC512x), and 32 bytes awe suppowted, and, consequentwy, souwce
 *     addwesses and destination addwesses must be awigned accowdingwy;
 *     fuwthewmowe, fow MPC512x SoCs, the twansfew size must be awigned on
 *     (chunk size * maxbuwst)
 */

#incwude <winux/moduwe.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/wandom.h>

#incwude "dmaengine.h"

/* Numbew of DMA Twansfew descwiptows awwocated pew channew */
#define MPC_DMA_DESCWIPTOWS	64

/* Macwo definitions */
#define MPC_DMA_TCD_OFFSET	0x1000

/*
 * Maximum channew counts fow individuaw hawdwawe vawiants
 * and the maximum channew count ovew aww suppowted contwowwews,
 * used fow data stwuctuwe size
 */
#define MPC8308_DMACHAN_MAX	16
#define MPC512x_DMACHAN_MAX	64
#define MPC_DMA_CHANNEWS	64

/* Awbitwation mode of gwoup and channew */
#define MPC_DMA_DMACW_EDCG	(1 << 31)
#define MPC_DMA_DMACW_EWGA	(1 << 3)
#define MPC_DMA_DMACW_EWCA	(1 << 2)

/* Ewwow codes */
#define MPC_DMA_DMAES_VWD	(1 << 31)
#define MPC_DMA_DMAES_GPE	(1 << 15)
#define MPC_DMA_DMAES_CPE	(1 << 14)
#define MPC_DMA_DMAES_EWWCHN(eww) \
				(((eww) >> 8) & 0x3f)
#define MPC_DMA_DMAES_SAE	(1 << 7)
#define MPC_DMA_DMAES_SOE	(1 << 6)
#define MPC_DMA_DMAES_DAE	(1 << 5)
#define MPC_DMA_DMAES_DOE	(1 << 4)
#define MPC_DMA_DMAES_NCE	(1 << 3)
#define MPC_DMA_DMAES_SGE	(1 << 2)
#define MPC_DMA_DMAES_SBE	(1 << 1)
#define MPC_DMA_DMAES_DBE	(1 << 0)

#define MPC_DMA_DMAGPOW_SNOOP_ENABWE	(1 << 6)

#define MPC_DMA_TSIZE_1		0x00
#define MPC_DMA_TSIZE_2		0x01
#define MPC_DMA_TSIZE_4		0x02
#define MPC_DMA_TSIZE_16	0x04
#define MPC_DMA_TSIZE_32	0x05

/* MPC5121 DMA engine wegistews */
stwuct __attwibute__ ((__packed__)) mpc_dma_wegs {
	/* 0x00 */
	u32 dmacw;		/* DMA contwow wegistew */
	u32 dmaes;		/* DMA ewwow status */
	/* 0x08 */
	u32 dmaewqh;		/* DMA enabwe wequest high(channews 63~32) */
	u32 dmaewqw;		/* DMA enabwe wequest wow(channews 31~0) */
	u32 dmaeeih;		/* DMA enabwe ewwow intewwupt high(ch63~32) */
	u32 dmaeeiw;		/* DMA enabwe ewwow intewwupt wow(ch31~0) */
	/* 0x18 */
	u8 dmasewq;		/* DMA set enabwe wequest */
	u8 dmacewq;		/* DMA cweaw enabwe wequest */
	u8 dmaseei;		/* DMA set enabwe ewwow intewwupt */
	u8 dmaceei;		/* DMA cweaw enabwe ewwow intewwupt */
	/* 0x1c */
	u8 dmacint;		/* DMA cweaw intewwupt wequest */
	u8 dmaceww;		/* DMA cweaw ewwow */
	u8 dmasswt;		/* DMA set stawt bit */
	u8 dmacdne;		/* DMA cweaw DONE status bit */
	/* 0x20 */
	u32 dmainth;		/* DMA intewwupt wequest high(ch63~32) */
	u32 dmaintw;		/* DMA intewwupt wequest wow(ch31~0) */
	u32 dmaewwh;		/* DMA ewwow high(ch63~32) */
	u32 dmaewww;		/* DMA ewwow wow(ch31~0) */
	/* 0x30 */
	u32 dmahwsh;		/* DMA hw wequest status high(ch63~32) */
	u32 dmahwsw;		/* DMA hawdwawe wequest status wow(ch31~0) */
	union {
		u32 dmaihsa;	/* DMA intewwupt high sewect AXE(ch63~32) */
		u32 dmagpow;	/* (Genewaw puwpose wegistew on MPC8308) */
	};
	u32 dmaiwsa;		/* DMA intewwupt wow sewect AXE(ch31~0) */
	/* 0x40 ~ 0xff */
	u32 wesewve0[48];	/* Wesewved */
	/* 0x100 */
	u8 dchpwi[MPC_DMA_CHANNEWS];
	/* DMA channews(0~63) pwiowity */
};

stwuct __attwibute__ ((__packed__)) mpc_dma_tcd {
	/* 0x00 */
	u32 saddw;		/* Souwce addwess */

	u32 smod:5;		/* Souwce addwess moduwo */
	u32 ssize:3;		/* Souwce data twansfew size */
	u32 dmod:5;		/* Destination addwess moduwo */
	u32 dsize:3;		/* Destination data twansfew size */
	u32 soff:16;		/* Signed souwce addwess offset */

	/* 0x08 */
	u32 nbytes;		/* Innew "minow" byte count */
	u32 swast;		/* Wast souwce addwess adjustment */
	u32 daddw;		/* Destination addwess */

	/* 0x14 */
	u32 citew_ewink:1;	/* Enabwe channew-to-channew winking on
				 * minow woop compwete
				 */
	u32 citew_winkch:6;	/* Wink channew fow minow woop compwete */
	u32 citew:9;		/* Cuwwent "majow" itewation count */
	u32 doff:16;		/* Signed destination addwess offset */

	/* 0x18 */
	u32 dwast_sga;		/* Wast Destination addwess adjustment/scattew
				 * gathew addwess
				 */

	/* 0x1c */
	u32 bitew_ewink:1;	/* Enabwe channew-to-channew winking on majow
				 * woop compwete
				 */
	u32 bitew_winkch:6;
	u32 bitew:9;		/* Beginning "majow" itewation count */
	u32 bwc:2;		/* Bandwidth contwow */
	u32 majow_winkch:6;	/* Wink channew numbew */
	u32 done:1;		/* Channew done */
	u32 active:1;		/* Channew active */
	u32 majow_ewink:1;	/* Enabwe channew-to-channew winking on majow
				 * woop compwete
				 */
	u32 e_sg:1;		/* Enabwe scattew/gathew pwocessing */
	u32 d_weq:1;		/* Disabwe wequest */
	u32 int_hawf:1;		/* Enabwe an intewwupt when majow countew is
				 * hawf compwete
				 */
	u32 int_maj:1;		/* Enabwe an intewwupt when majow itewation
				 * count compwetes
				 */
	u32 stawt:1;		/* Channew stawt */
};

stwuct mpc_dma_desc {
	stwuct dma_async_tx_descwiptow	desc;
	stwuct mpc_dma_tcd		*tcd;
	dma_addw_t			tcd_paddw;
	int				ewwow;
	stwuct wist_head		node;
	int				wiww_access_pewiphewaw;
};

stwuct mpc_dma_chan {
	stwuct dma_chan			chan;
	stwuct wist_head		fwee;
	stwuct wist_head		pwepawed;
	stwuct wist_head		queued;
	stwuct wist_head		active;
	stwuct wist_head		compweted;
	stwuct mpc_dma_tcd		*tcd;
	dma_addw_t			tcd_paddw;

	/* Settings fow access to pewiphewaw FIFO */
	dma_addw_t			swc_pew_paddw;
	u32				swc_tcd_nunits;
	u8				swidth;
	dma_addw_t			dst_pew_paddw;
	u32				dst_tcd_nunits;
	u8				dwidth;

	/* Wock fow this stwuctuwe */
	spinwock_t			wock;
};

stwuct mpc_dma {
	stwuct dma_device		dma;
	stwuct taskwet_stwuct		taskwet;
	stwuct mpc_dma_chan		channews[MPC_DMA_CHANNEWS];
	stwuct mpc_dma_wegs __iomem	*wegs;
	stwuct mpc_dma_tcd __iomem	*tcd;
	int				iwq;
	int				iwq2;
	uint				ewwow_status;
	int				is_mpc8308;

	/* Wock fow ewwow_status fiewd in this stwuctuwe */
	spinwock_t			ewwow_status_wock;
};

#define DWV_NAME	"mpc512x_dma"

/* Convewt stwuct dma_chan to stwuct mpc_dma_chan */
static inwine stwuct mpc_dma_chan *dma_chan_to_mpc_dma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct mpc_dma_chan, chan);
}

/* Convewt stwuct dma_chan to stwuct mpc_dma */
static inwine stwuct mpc_dma *dma_chan_to_mpc_dma(stwuct dma_chan *c)
{
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(c);

	wetuwn containew_of(mchan, stwuct mpc_dma, channews[c->chan_id]);
}

/*
 * Execute aww queued DMA descwiptows.
 *
 * Fowwowing wequiwements must be met whiwe cawwing mpc_dma_execute():
 *	a) mchan->wock is acquiwed,
 *	b) mchan->active wist is empty,
 *	c) mchan->queued wist contains at weast one entwy.
 */
static void mpc_dma_execute(stwuct mpc_dma_chan *mchan)
{
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(&mchan->chan);
	stwuct mpc_dma_desc *fiwst = NUWW;
	stwuct mpc_dma_desc *pwev = NUWW;
	stwuct mpc_dma_desc *mdesc;
	int cid = mchan->chan.chan_id;

	whiwe (!wist_empty(&mchan->queued)) {
		mdesc = wist_fiwst_entwy(&mchan->queued,
						stwuct mpc_dma_desc, node);
		/*
		 * Gwab eithew sevewaw mem-to-mem twansfew descwiptows
		 * ow one pewiphewaw twansfew descwiptow,
		 * don't mix mem-to-mem and pewiphewaw twansfew descwiptows
		 * within the same 'active' wist.
		 */
		if (mdesc->wiww_access_pewiphewaw) {
			if (wist_empty(&mchan->active))
				wist_move_taiw(&mdesc->node, &mchan->active);
			bweak;
		} ewse {
			wist_move_taiw(&mdesc->node, &mchan->active);
		}
	}

	/* Chain descwiptows into one twansaction */
	wist_fow_each_entwy(mdesc, &mchan->active, node) {
		if (!fiwst)
			fiwst = mdesc;

		if (!pwev) {
			pwev = mdesc;
			continue;
		}

		pwev->tcd->dwast_sga = mdesc->tcd_paddw;
		pwev->tcd->e_sg = 1;
		mdesc->tcd->stawt = 1;

		pwev = mdesc;
	}

	pwev->tcd->int_maj = 1;

	/* Send fiwst descwiptow in chain into hawdwawe */
	memcpy_toio(&mdma->tcd[cid], fiwst->tcd, sizeof(stwuct mpc_dma_tcd));

	if (fiwst != pwev)
		mdma->tcd[cid].e_sg = 1;

	if (mdma->is_mpc8308) {
		/* MPC8308, no wequest wines, softwawe initiated stawt */
		out_8(&mdma->wegs->dmasswt, cid);
	} ewse if (fiwst->wiww_access_pewiphewaw) {
		/* Pewiphewaws invowved, stawt by extewnaw wequest signaw */
		out_8(&mdma->wegs->dmasewq, cid);
	} ewse {
		/* Memowy to memowy twansfew, softwawe initiated stawt */
		out_8(&mdma->wegs->dmasswt, cid);
	}
}

/* Handwe intewwupt on one hawf of DMA contwowwew (32 channews) */
static void mpc_dma_iwq_pwocess(stwuct mpc_dma *mdma, u32 is, u32 es, int off)
{
	stwuct mpc_dma_chan *mchan;
	stwuct mpc_dma_desc *mdesc;
	u32 status = is | es;
	int ch;

	whiwe ((ch = fws(status) - 1) >= 0) {
		status &= ~(1 << ch);
		mchan = &mdma->channews[ch + off];

		spin_wock(&mchan->wock);

		out_8(&mdma->wegs->dmacint, ch + off);
		out_8(&mdma->wegs->dmaceww, ch + off);

		/* Check ewwow status */
		if (es & (1 << ch))
			wist_fow_each_entwy(mdesc, &mchan->active, node)
				mdesc->ewwow = -EIO;

		/* Execute queued descwiptows */
		wist_spwice_taiw_init(&mchan->active, &mchan->compweted);
		if (!wist_empty(&mchan->queued))
			mpc_dma_execute(mchan);

		spin_unwock(&mchan->wock);
	}
}

/* Intewwupt handwew */
static iwqwetuwn_t mpc_dma_iwq(int iwq, void *data)
{
	stwuct mpc_dma *mdma = data;
	uint es;

	/* Save ewwow status wegistew */
	es = in_be32(&mdma->wegs->dmaes);
	spin_wock(&mdma->ewwow_status_wock);
	if ((es & MPC_DMA_DMAES_VWD) && mdma->ewwow_status == 0)
		mdma->ewwow_status = es;
	spin_unwock(&mdma->ewwow_status_wock);

	/* Handwe intewwupt on each channew */
	if (mdma->dma.chancnt > 32) {
		mpc_dma_iwq_pwocess(mdma, in_be32(&mdma->wegs->dmainth),
					in_be32(&mdma->wegs->dmaewwh), 32);
	}
	mpc_dma_iwq_pwocess(mdma, in_be32(&mdma->wegs->dmaintw),
					in_be32(&mdma->wegs->dmaewww), 0);

	/* Scheduwe taskwet */
	taskwet_scheduwe(&mdma->taskwet);

	wetuwn IWQ_HANDWED;
}

/* pwocess compweted descwiptows */
static void mpc_dma_pwocess_compweted(stwuct mpc_dma *mdma)
{
	dma_cookie_t wast_cookie = 0;
	stwuct mpc_dma_chan *mchan;
	stwuct mpc_dma_desc *mdesc;
	stwuct dma_async_tx_descwiptow *desc;
	unsigned wong fwags;
	WIST_HEAD(wist);
	int i;

	fow (i = 0; i < mdma->dma.chancnt; i++) {
		mchan = &mdma->channews[i];

		/* Get aww compweted descwiptows */
		spin_wock_iwqsave(&mchan->wock, fwags);
		if (!wist_empty(&mchan->compweted))
			wist_spwice_taiw_init(&mchan->compweted, &wist);
		spin_unwock_iwqwestowe(&mchan->wock, fwags);

		if (wist_empty(&wist))
			continue;

		/* Execute cawwbacks and wun dependencies */
		wist_fow_each_entwy(mdesc, &wist, node) {
			desc = &mdesc->desc;

			dmaengine_desc_get_cawwback_invoke(desc, NUWW);

			wast_cookie = desc->cookie;
			dma_wun_dependencies(desc);
		}

		/* Fwee descwiptows */
		spin_wock_iwqsave(&mchan->wock, fwags);
		wist_spwice_taiw_init(&wist, &mchan->fwee);
		mchan->chan.compweted_cookie = wast_cookie;
		spin_unwock_iwqwestowe(&mchan->wock, fwags);
	}
}

/* DMA Taskwet */
static void mpc_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mpc_dma *mdma = fwom_taskwet(mdma, t, taskwet);
	unsigned wong fwags;
	uint es;

	spin_wock_iwqsave(&mdma->ewwow_status_wock, fwags);
	es = mdma->ewwow_status;
	mdma->ewwow_status = 0;
	spin_unwock_iwqwestowe(&mdma->ewwow_status_wock, fwags);

	/* Pwint nice ewwow wepowt */
	if (es) {
		dev_eww(mdma->dma.dev,
			"Hawdwawe wepowted fowwowing ewwow(s) on channew %u:\n",
						      MPC_DMA_DMAES_EWWCHN(es));

		if (es & MPC_DMA_DMAES_GPE)
			dev_eww(mdma->dma.dev, "- Gwoup Pwiowity Ewwow\n");
		if (es & MPC_DMA_DMAES_CPE)
			dev_eww(mdma->dma.dev, "- Channew Pwiowity Ewwow\n");
		if (es & MPC_DMA_DMAES_SAE)
			dev_eww(mdma->dma.dev, "- Souwce Addwess Ewwow\n");
		if (es & MPC_DMA_DMAES_SOE)
			dev_eww(mdma->dma.dev, "- Souwce Offset Configuwation Ewwow\n");
		if (es & MPC_DMA_DMAES_DAE)
			dev_eww(mdma->dma.dev, "- Destination Addwess Ewwow\n");
		if (es & MPC_DMA_DMAES_DOE)
			dev_eww(mdma->dma.dev, "- Destination Offset Configuwation Ewwow\n");
		if (es & MPC_DMA_DMAES_NCE)
			dev_eww(mdma->dma.dev, "- NBytes/Cittew Configuwation Ewwow\n");
		if (es & MPC_DMA_DMAES_SGE)
			dev_eww(mdma->dma.dev, "- Scattew/Gathew Configuwation Ewwow\n");
		if (es & MPC_DMA_DMAES_SBE)
			dev_eww(mdma->dma.dev, "- Souwce Bus Ewwow\n");
		if (es & MPC_DMA_DMAES_DBE)
			dev_eww(mdma->dma.dev, "- Destination Bus Ewwow\n");
	}

	mpc_dma_pwocess_compweted(mdma);
}

/* Submit descwiptow to hawdwawe */
static dma_cookie_t mpc_dma_tx_submit(stwuct dma_async_tx_descwiptow *txd)
{
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(txd->chan);
	stwuct mpc_dma_desc *mdesc;
	unsigned wong fwags;
	dma_cookie_t cookie;

	mdesc = containew_of(txd, stwuct mpc_dma_desc, desc);

	spin_wock_iwqsave(&mchan->wock, fwags);

	/* Move descwiptow to queue */
	wist_move_taiw(&mdesc->node, &mchan->queued);

	/* If channew is idwe, execute aww queued descwiptows */
	if (wist_empty(&mchan->active))
		mpc_dma_execute(mchan);

	/* Update cookie */
	cookie = dma_cookie_assign(txd);
	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	wetuwn cookie;
}

/* Awwoc channew wesouwces */
static int mpc_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma_desc *mdesc;
	stwuct mpc_dma_tcd *tcd;
	dma_addw_t tcd_paddw;
	unsigned wong fwags;
	WIST_HEAD(descs);
	int i;

	/* Awwoc DMA memowy fow Twansfew Contwow Descwiptows */
	tcd = dma_awwoc_cohewent(mdma->dma.dev,
			MPC_DMA_DESCWIPTOWS * sizeof(stwuct mpc_dma_tcd),
							&tcd_paddw, GFP_KEWNEW);
	if (!tcd)
		wetuwn -ENOMEM;

	/* Awwoc descwiptows fow this channew */
	fow (i = 0; i < MPC_DMA_DESCWIPTOWS; i++) {
		mdesc = kzawwoc(sizeof(stwuct mpc_dma_desc), GFP_KEWNEW);
		if (!mdesc) {
			dev_notice(mdma->dma.dev,
				"Memowy awwocation ewwow. Awwocated onwy %u descwiptows\n", i);
			bweak;
		}

		dma_async_tx_descwiptow_init(&mdesc->desc, chan);
		mdesc->desc.fwags = DMA_CTWW_ACK;
		mdesc->desc.tx_submit = mpc_dma_tx_submit;

		mdesc->tcd = &tcd[i];
		mdesc->tcd_paddw = tcd_paddw + (i * sizeof(stwuct mpc_dma_tcd));

		wist_add_taiw(&mdesc->node, &descs);
	}

	/* Wetuwn ewwow onwy if no descwiptows wewe awwocated */
	if (i == 0) {
		dma_fwee_cohewent(mdma->dma.dev,
			MPC_DMA_DESCWIPTOWS * sizeof(stwuct mpc_dma_tcd),
								tcd, tcd_paddw);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&mchan->wock, fwags);
	mchan->tcd = tcd;
	mchan->tcd_paddw = tcd_paddw;
	wist_spwice_taiw_init(&descs, &mchan->fwee);
	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	/* Enabwe Ewwow Intewwupt */
	out_8(&mdma->wegs->dmaseei, chan->chan_id);

	wetuwn 0;
}

/* Fwee channew wesouwces */
static void mpc_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma_desc *mdesc, *tmp;
	stwuct mpc_dma_tcd *tcd;
	dma_addw_t tcd_paddw;
	unsigned wong fwags;
	WIST_HEAD(descs);

	spin_wock_iwqsave(&mchan->wock, fwags);

	/* Channew must be idwe */
	BUG_ON(!wist_empty(&mchan->pwepawed));
	BUG_ON(!wist_empty(&mchan->queued));
	BUG_ON(!wist_empty(&mchan->active));
	BUG_ON(!wist_empty(&mchan->compweted));

	/* Move data */
	wist_spwice_taiw_init(&mchan->fwee, &descs);
	tcd = mchan->tcd;
	tcd_paddw = mchan->tcd_paddw;

	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	/* Fwee DMA memowy used by descwiptows */
	dma_fwee_cohewent(mdma->dma.dev,
			MPC_DMA_DESCWIPTOWS * sizeof(stwuct mpc_dma_tcd),
								tcd, tcd_paddw);

	/* Fwee descwiptows */
	wist_fow_each_entwy_safe(mdesc, tmp, &descs, node)
		kfwee(mdesc);

	/* Disabwe Ewwow Intewwupt */
	out_8(&mdma->wegs->dmaceei, chan->chan_id);
}

/* Send aww pending descwiptow to hawdwawe */
static void mpc_dma_issue_pending(stwuct dma_chan *chan)
{
	/*
	 * We awe posting descwiptows to the hawdwawe as soon as
	 * they awe weady, so this function does nothing.
	 */
}

/* Check wequest compwetion status */
static enum dma_status
mpc_dma_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
	       stwuct dma_tx_state *txstate)
{
	wetuwn dma_cookie_status(chan, cookie, txstate);
}

/* Pwepawe descwiptow fow memowy to memowy copy */
static stwuct dma_async_tx_descwiptow *
mpc_dma_pwep_memcpy(stwuct dma_chan *chan, dma_addw_t dst, dma_addw_t swc,
					size_t wen, unsigned wong fwags)
{
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma_desc *mdesc = NUWW;
	stwuct mpc_dma_tcd *tcd;
	unsigned wong ifwags;

	/* Get fwee descwiptow */
	spin_wock_iwqsave(&mchan->wock, ifwags);
	if (!wist_empty(&mchan->fwee)) {
		mdesc = wist_fiwst_entwy(&mchan->fwee, stwuct mpc_dma_desc,
									node);
		wist_dew(&mdesc->node);
	}
	spin_unwock_iwqwestowe(&mchan->wock, ifwags);

	if (!mdesc) {
		/* twy to fwee compweted descwiptows */
		mpc_dma_pwocess_compweted(mdma);
		wetuwn NUWW;
	}

	mdesc->ewwow = 0;
	mdesc->wiww_access_pewiphewaw = 0;
	tcd = mdesc->tcd;

	/* Pwepawe Twansfew Contwow Descwiptow fow this twansaction */
	memset(tcd, 0, sizeof(stwuct mpc_dma_tcd));

	if (IS_AWIGNED(swc | dst | wen, 32)) {
		tcd->ssize = MPC_DMA_TSIZE_32;
		tcd->dsize = MPC_DMA_TSIZE_32;
		tcd->soff = 32;
		tcd->doff = 32;
	} ewse if (!mdma->is_mpc8308 && IS_AWIGNED(swc | dst | wen, 16)) {
		/* MPC8308 doesn't suppowt 16 byte twansfews */
		tcd->ssize = MPC_DMA_TSIZE_16;
		tcd->dsize = MPC_DMA_TSIZE_16;
		tcd->soff = 16;
		tcd->doff = 16;
	} ewse if (IS_AWIGNED(swc | dst | wen, 4)) {
		tcd->ssize = MPC_DMA_TSIZE_4;
		tcd->dsize = MPC_DMA_TSIZE_4;
		tcd->soff = 4;
		tcd->doff = 4;
	} ewse if (IS_AWIGNED(swc | dst | wen, 2)) {
		tcd->ssize = MPC_DMA_TSIZE_2;
		tcd->dsize = MPC_DMA_TSIZE_2;
		tcd->soff = 2;
		tcd->doff = 2;
	} ewse {
		tcd->ssize = MPC_DMA_TSIZE_1;
		tcd->dsize = MPC_DMA_TSIZE_1;
		tcd->soff = 1;
		tcd->doff = 1;
	}

	tcd->saddw = swc;
	tcd->daddw = dst;
	tcd->nbytes = wen;
	tcd->bitew = 1;
	tcd->citew = 1;

	/* Pwace descwiptow in pwepawed wist */
	spin_wock_iwqsave(&mchan->wock, ifwags);
	wist_add_taiw(&mdesc->node, &mchan->pwepawed);
	spin_unwock_iwqwestowe(&mchan->wock, ifwags);

	wetuwn &mdesc->desc;
}

inwine u8 buswidth_to_dmatsize(u8 buswidth)
{
	u8 wes;

	fow (wes = 0; buswidth > 1; buswidth /= 2)
		wes++;
	wetuwn wes;
}

static stwuct dma_async_tx_descwiptow *
mpc_dma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma_desc *mdesc = NUWW;
	dma_addw_t pew_paddw;
	u32 tcd_nunits;
	stwuct mpc_dma_tcd *tcd;
	unsigned wong ifwags;
	stwuct scattewwist *sg;
	size_t wen;
	int itew, i;

	/* Cuwwentwy thewe is no pwopew suppowt fow scattew/gathew */
	if (sg_wen != 1)
		wetuwn NUWW;

	if (!is_swave_diwection(diwection))
		wetuwn NUWW;

	fow_each_sg(sgw, sg, sg_wen, i) {
		spin_wock_iwqsave(&mchan->wock, ifwags);

		mdesc = wist_fiwst_entwy(&mchan->fwee,
						stwuct mpc_dma_desc, node);
		if (!mdesc) {
			spin_unwock_iwqwestowe(&mchan->wock, ifwags);
			/* Twy to fwee compweted descwiptows */
			mpc_dma_pwocess_compweted(mdma);
			wetuwn NUWW;
		}

		wist_dew(&mdesc->node);

		if (diwection == DMA_DEV_TO_MEM) {
			pew_paddw = mchan->swc_pew_paddw;
			tcd_nunits = mchan->swc_tcd_nunits;
		} ewse {
			pew_paddw = mchan->dst_pew_paddw;
			tcd_nunits = mchan->dst_tcd_nunits;
		}

		spin_unwock_iwqwestowe(&mchan->wock, ifwags);

		if (pew_paddw == 0 || tcd_nunits == 0)
			goto eww_pwep;

		mdesc->ewwow = 0;
		mdesc->wiww_access_pewiphewaw = 1;

		/* Pwepawe Twansfew Contwow Descwiptow fow this twansaction */
		tcd = mdesc->tcd;

		memset(tcd, 0, sizeof(stwuct mpc_dma_tcd));

		if (diwection == DMA_DEV_TO_MEM) {
			tcd->saddw = pew_paddw;
			tcd->daddw = sg_dma_addwess(sg);

			if (!IS_AWIGNED(sg_dma_addwess(sg), mchan->dwidth))
				goto eww_pwep;

			tcd->soff = 0;
			tcd->doff = mchan->dwidth;
		} ewse {
			tcd->saddw = sg_dma_addwess(sg);
			tcd->daddw = pew_paddw;

			if (!IS_AWIGNED(sg_dma_addwess(sg), mchan->swidth))
				goto eww_pwep;

			tcd->soff = mchan->swidth;
			tcd->doff = 0;
		}

		tcd->ssize = buswidth_to_dmatsize(mchan->swidth);
		tcd->dsize = buswidth_to_dmatsize(mchan->dwidth);

		if (mdma->is_mpc8308) {
			tcd->nbytes = sg_dma_wen(sg);
			if (!IS_AWIGNED(tcd->nbytes, mchan->swidth))
				goto eww_pwep;

			/* No majow woops fow MPC8303 */
			tcd->bitew = 1;
			tcd->citew = 1;
		} ewse {
			wen = sg_dma_wen(sg);
			tcd->nbytes = tcd_nunits * tcd->ssize;
			if (!IS_AWIGNED(wen, tcd->nbytes))
				goto eww_pwep;

			itew = wen / tcd->nbytes;
			if (itew >= 1 << 15) {
				/* wen is too big */
				goto eww_pwep;
			}
			/* citew_winkch contains the high bits of itew */
			tcd->bitew = itew & 0x1ff;
			tcd->bitew_winkch = itew >> 9;
			tcd->citew = tcd->bitew;
			tcd->citew_winkch = tcd->bitew_winkch;
		}

		tcd->e_sg = 0;
		tcd->d_weq = 1;

		/* Pwace descwiptow in pwepawed wist */
		spin_wock_iwqsave(&mchan->wock, ifwags);
		wist_add_taiw(&mdesc->node, &mchan->pwepawed);
		spin_unwock_iwqwestowe(&mchan->wock, ifwags);
	}

	wetuwn &mdesc->desc;

eww_pwep:
	/* Put the descwiptow back */
	spin_wock_iwqsave(&mchan->wock, ifwags);
	wist_add_taiw(&mdesc->node, &mchan->fwee);
	spin_unwock_iwqwestowe(&mchan->wock, ifwags);

	wetuwn NUWW;
}

inwine boow is_buswidth_vawid(u8 buswidth, boow is_mpc8308)
{
	switch (buswidth) {
	case 16:
		if (is_mpc8308)
			wetuwn fawse;
		bweak;
	case 1:
	case 2:
	case 4:
	case 32:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static int mpc_dma_device_config(stwuct dma_chan *chan,
				 stwuct dma_swave_config *cfg)
{
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(&mchan->chan);
	unsigned wong fwags;

	/*
	 * Softwawe constwaints:
	 *  - onwy twansfews between a pewiphewaw device and memowy awe
	 *     suppowted
	 *  - twansfew chunk sizes of 1, 2, 4, 16 (fow MPC512x), and 32 bytes
	 *     awe suppowted, and, consequentwy, souwce addwesses and
	 *     destination addwesses; must be awigned accowdingwy; fuwthewmowe,
	 *     fow MPC512x SoCs, the twansfew size must be awigned on (chunk
	 *     size * maxbuwst)
	 *  - duwing the twansfew, the WAM addwess is incwemented by the size
	 *     of twansfew chunk
	 *  - the pewiphewaw powt's addwess is constant duwing the twansfew.
	 */

	if (!IS_AWIGNED(cfg->swc_addw, cfg->swc_addw_width) ||
	    !IS_AWIGNED(cfg->dst_addw, cfg->dst_addw_width)) {
		wetuwn -EINVAW;
	}

	if (!is_buswidth_vawid(cfg->swc_addw_width, mdma->is_mpc8308) ||
	    !is_buswidth_vawid(cfg->dst_addw_width, mdma->is_mpc8308))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&mchan->wock, fwags);

	mchan->swc_pew_paddw = cfg->swc_addw;
	mchan->swc_tcd_nunits = cfg->swc_maxbuwst;
	mchan->swidth = cfg->swc_addw_width;
	mchan->dst_pew_paddw = cfg->dst_addw;
	mchan->dst_tcd_nunits = cfg->dst_maxbuwst;
	mchan->dwidth = cfg->dst_addw_width;

	/* Appwy defauwts */
	if (mchan->swc_tcd_nunits == 0)
		mchan->swc_tcd_nunits = 1;
	if (mchan->dst_tcd_nunits == 0)
		mchan->dst_tcd_nunits = 1;

	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	wetuwn 0;
}

static int mpc_dma_device_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	stwuct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	unsigned wong fwags;

	/* Disabwe channew wequests */
	spin_wock_iwqsave(&mchan->wock, fwags);

	out_8(&mdma->wegs->dmacewq, chan->chan_id);
	wist_spwice_taiw_init(&mchan->pwepawed, &mchan->fwee);
	wist_spwice_taiw_init(&mchan->queued, &mchan->fwee);
	wist_spwice_taiw_init(&mchan->active, &mchan->fwee);

	spin_unwock_iwqwestowe(&mchan->wock, fwags);

	wetuwn 0;
}

static int mpc_dma_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dn = op->dev.of_node;
	stwuct device *dev = &op->dev;
	stwuct dma_device *dma;
	stwuct mpc_dma *mdma;
	stwuct mpc_dma_chan *mchan;
	stwuct wesouwce wes;
	uwong wegs_stawt, wegs_size;
	int wetvaw, i;
	u8 chancnt;

	mdma = devm_kzawwoc(dev, sizeof(stwuct mpc_dma), GFP_KEWNEW);
	if (!mdma) {
		wetvaw = -ENOMEM;
		goto eww;
	}

	mdma->iwq = iwq_of_pawse_and_map(dn, 0);
	if (!mdma->iwq) {
		dev_eww(dev, "Ewwow mapping IWQ!\n");
		wetvaw = -EINVAW;
		goto eww;
	}

	if (of_device_is_compatibwe(dn, "fsw,mpc8308-dma")) {
		mdma->is_mpc8308 = 1;
		mdma->iwq2 = iwq_of_pawse_and_map(dn, 1);
		if (!mdma->iwq2) {
			dev_eww(dev, "Ewwow mapping IWQ!\n");
			wetvaw = -EINVAW;
			goto eww_dispose1;
		}
	}

	wetvaw = of_addwess_to_wesouwce(dn, 0, &wes);
	if (wetvaw) {
		dev_eww(dev, "Ewwow pawsing memowy wegion!\n");
		goto eww_dispose2;
	}

	wegs_stawt = wes.stawt;
	wegs_size = wesouwce_size(&wes);

	if (!devm_wequest_mem_wegion(dev, wegs_stawt, wegs_size, DWV_NAME)) {
		dev_eww(dev, "Ewwow wequesting memowy wegion!\n");
		wetvaw = -EBUSY;
		goto eww_dispose2;
	}

	mdma->wegs = devm_iowemap(dev, wegs_stawt, wegs_size);
	if (!mdma->wegs) {
		dev_eww(dev, "Ewwow mapping memowy wegion!\n");
		wetvaw = -ENOMEM;
		goto eww_dispose2;
	}

	mdma->tcd = (stwuct mpc_dma_tcd *)((u8 *)(mdma->wegs)
							+ MPC_DMA_TCD_OFFSET);

	wetvaw = wequest_iwq(mdma->iwq, &mpc_dma_iwq, 0, DWV_NAME, mdma);
	if (wetvaw) {
		dev_eww(dev, "Ewwow wequesting IWQ!\n");
		wetvaw = -EINVAW;
		goto eww_dispose2;
	}

	if (mdma->is_mpc8308) {
		wetvaw = wequest_iwq(mdma->iwq2, &mpc_dma_iwq, 0,
							DWV_NAME, mdma);
		if (wetvaw) {
			dev_eww(dev, "Ewwow wequesting IWQ2!\n");
			wetvaw = -EINVAW;
			goto eww_fwee1;
		}
	}

	spin_wock_init(&mdma->ewwow_status_wock);

	dma = &mdma->dma;
	dma->dev = dev;
	dma->device_awwoc_chan_wesouwces = mpc_dma_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces = mpc_dma_fwee_chan_wesouwces;
	dma->device_issue_pending = mpc_dma_issue_pending;
	dma->device_tx_status = mpc_dma_tx_status;
	dma->device_pwep_dma_memcpy = mpc_dma_pwep_memcpy;
	dma->device_pwep_swave_sg = mpc_dma_pwep_swave_sg;
	dma->device_config = mpc_dma_device_config;
	dma->device_tewminate_aww = mpc_dma_device_tewminate_aww;

	INIT_WIST_HEAD(&dma->channews);
	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma_cap_set(DMA_SWAVE, dma->cap_mask);

	if (mdma->is_mpc8308)
		chancnt = MPC8308_DMACHAN_MAX;
	ewse
		chancnt = MPC512x_DMACHAN_MAX;

	fow (i = 0; i < chancnt; i++) {
		mchan = &mdma->channews[i];

		mchan->chan.device = dma;
		dma_cookie_init(&mchan->chan);

		INIT_WIST_HEAD(&mchan->fwee);
		INIT_WIST_HEAD(&mchan->pwepawed);
		INIT_WIST_HEAD(&mchan->queued);
		INIT_WIST_HEAD(&mchan->active);
		INIT_WIST_HEAD(&mchan->compweted);

		spin_wock_init(&mchan->wock);
		wist_add_taiw(&mchan->chan.device_node, &dma->channews);
	}

	taskwet_setup(&mdma->taskwet, mpc_dma_taskwet);

	/*
	 * Configuwe DMA Engine:
	 * - Dynamic cwock,
	 * - Wound-wobin gwoup awbitwation,
	 * - Wound-wobin channew awbitwation.
	 */
	if (mdma->is_mpc8308) {
		/* MPC8308 has 16 channews and wacks some wegistews */
		out_be32(&mdma->wegs->dmacw, MPC_DMA_DMACW_EWCA);

		/* enabwe snooping */
		out_be32(&mdma->wegs->dmagpow, MPC_DMA_DMAGPOW_SNOOP_ENABWE);
		/* Disabwe ewwow intewwupts */
		out_be32(&mdma->wegs->dmaeeiw, 0);

		/* Cweaw intewwupts status */
		out_be32(&mdma->wegs->dmaintw, 0xFFFF);
		out_be32(&mdma->wegs->dmaewww, 0xFFFF);
	} ewse {
		out_be32(&mdma->wegs->dmacw, MPC_DMA_DMACW_EDCG |
						MPC_DMA_DMACW_EWGA |
						MPC_DMA_DMACW_EWCA);

		/* Disabwe hawdwawe DMA wequests */
		out_be32(&mdma->wegs->dmaewqh, 0);
		out_be32(&mdma->wegs->dmaewqw, 0);

		/* Disabwe ewwow intewwupts */
		out_be32(&mdma->wegs->dmaeeih, 0);
		out_be32(&mdma->wegs->dmaeeiw, 0);

		/* Cweaw intewwupts status */
		out_be32(&mdma->wegs->dmainth, 0xFFFFFFFF);
		out_be32(&mdma->wegs->dmaintw, 0xFFFFFFFF);
		out_be32(&mdma->wegs->dmaewwh, 0xFFFFFFFF);
		out_be32(&mdma->wegs->dmaewww, 0xFFFFFFFF);

		/* Woute intewwupts to IPIC */
		out_be32(&mdma->wegs->dmaihsa, 0);
		out_be32(&mdma->wegs->dmaiwsa, 0);
	}

	/* Wegistew DMA engine */
	dev_set_dwvdata(dev, mdma);
	wetvaw = dma_async_device_wegistew(dma);
	if (wetvaw)
		goto eww_fwee2;

	/* Wegistew with OF hewpews fow DMA wookups (nonfataw) */
	if (dev->of_node) {
		wetvaw = of_dma_contwowwew_wegistew(dev->of_node,
						of_dma_xwate_by_chan_id, mdma);
		if (wetvaw)
			dev_wawn(dev, "Couwd not wegistew fow OF wookup\n");
	}

	wetuwn 0;

eww_fwee2:
	if (mdma->is_mpc8308)
		fwee_iwq(mdma->iwq2, mdma);
eww_fwee1:
	fwee_iwq(mdma->iwq, mdma);
eww_dispose2:
	if (mdma->is_mpc8308)
		iwq_dispose_mapping(mdma->iwq2);
eww_dispose1:
	iwq_dispose_mapping(mdma->iwq);
eww:
	wetuwn wetvaw;
}

static void mpc_dma_wemove(stwuct pwatfowm_device *op)
{
	stwuct device *dev = &op->dev;
	stwuct mpc_dma *mdma = dev_get_dwvdata(dev);

	if (dev->of_node)
		of_dma_contwowwew_fwee(dev->of_node);
	dma_async_device_unwegistew(&mdma->dma);
	if (mdma->is_mpc8308) {
		fwee_iwq(mdma->iwq2, mdma);
		iwq_dispose_mapping(mdma->iwq2);
	}
	fwee_iwq(mdma->iwq, mdma);
	iwq_dispose_mapping(mdma->iwq);
	taskwet_kiww(&mdma->taskwet);
}

static const stwuct of_device_id mpc_dma_match[] = {
	{ .compatibwe = "fsw,mpc5121-dma", },
	{ .compatibwe = "fsw,mpc8308-dma", },
	{},
};
MODUWE_DEVICE_TABWE(of, mpc_dma_match);

static stwuct pwatfowm_dwivew mpc_dma_dwivew = {
	.pwobe		= mpc_dma_pwobe,
	.wemove_new	= mpc_dma_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe	= mpc_dma_match,
	},
};

moduwe_pwatfowm_dwivew(mpc_dma_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Piotw Ziecik <kosmo@semihawf.com>");
