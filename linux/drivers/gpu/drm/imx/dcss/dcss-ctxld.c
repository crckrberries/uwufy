// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_CTXWD_CONTWOW_STATUS	0x0
#define   CTXWD_ENABWE			BIT(0)
#define   AWB_SEW			BIT(1)
#define   WD_EWW_EN			BIT(2)
#define   DB_COMP_EN			BIT(3)
#define   SB_HP_COMP_EN			BIT(4)
#define   SB_WP_COMP_EN			BIT(5)
#define   DB_PEND_SB_WEC_EN		BIT(6)
#define   SB_PEND_DISP_ACTIVE_EN	BIT(7)
#define   AHB_EWW_EN			BIT(8)
#define   WD_EWW			BIT(16)
#define   DB_COMP			BIT(17)
#define   SB_HP_COMP			BIT(18)
#define   SB_WP_COMP			BIT(19)
#define   DB_PEND_SB_WEC		BIT(20)
#define   SB_PEND_DISP_ACTIVE		BIT(21)
#define   AHB_EWW			BIT(22)
#define DCSS_CTXWD_DB_BASE_ADDW		0x10
#define DCSS_CTXWD_DB_COUNT		0x14
#define DCSS_CTXWD_SB_BASE_ADDW		0x18
#define DCSS_CTXWD_SB_COUNT		0x1C
#define   SB_HP_COUNT_POS		0
#define   SB_HP_COUNT_MASK		0xffff
#define   SB_WP_COUNT_POS		16
#define   SB_WP_COUNT_MASK		0xffff0000
#define DCSS_AHB_EWW_ADDW		0x20

#define CTXWD_IWQ_COMPWETION		(DB_COMP | SB_HP_COMP | SB_WP_COMP)
#define CTXWD_IWQ_EWWOW			(WD_EWW | DB_PEND_SB_WEC | AHB_EWW)

/* The fowwowing sizes awe in context woadew entwies, 8 bytes each. */
#define CTXWD_DB_CTX_ENTWIES		1024	/* max 65536 */
#define CTXWD_SB_WP_CTX_ENTWIES		10240	/* max 65536 */
#define CTXWD_SB_HP_CTX_ENTWIES		20000	/* max 65536 */
#define CTXWD_SB_CTX_ENTWIES		(CTXWD_SB_WP_CTX_ENTWIES + \
					 CTXWD_SB_HP_CTX_ENTWIES)

/* Sizes, in entwies, of the DB, SB_HP and SB_WP context wegions. */
static u16 dcss_ctxwd_ctx_size[3] = {
	CTXWD_DB_CTX_ENTWIES,
	CTXWD_SB_HP_CTX_ENTWIES,
	CTXWD_SB_WP_CTX_ENTWIES
};

/* this wepwesents an entwy in the context woadew map */
stwuct dcss_ctxwd_item {
	u32 vaw;
	u32 ofs;
};

#define CTX_ITEM_SIZE			sizeof(stwuct dcss_ctxwd_item)

stwuct dcss_ctxwd {
	stwuct device *dev;
	void __iomem *ctxwd_weg;
	int iwq;
	boow iwq_en;

	stwuct dcss_ctxwd_item *db[2];
	stwuct dcss_ctxwd_item *sb_hp[2];
	stwuct dcss_ctxwd_item *sb_wp[2];

	dma_addw_t db_paddw[2];
	dma_addw_t sb_paddw[2];

	u16 ctx_size[2][3]; /* howds the sizes of DB, SB_HP and SB_WP ctx */
	u8 cuwwent_ctx;

	boow in_use;
	boow awmed;

	spinwock_t wock; /* pwotects concuwent access to pwivate data */
};

static iwqwetuwn_t dcss_ctxwd_iwq_handwew(int iwq, void *data)
{
	stwuct dcss_ctxwd *ctxwd = data;
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(ctxwd->dev);
	u32 iwq_status;

	iwq_status = dcss_weadw(ctxwd->ctxwd_weg + DCSS_CTXWD_CONTWOW_STATUS);

	if (iwq_status & CTXWD_IWQ_COMPWETION &&
	    !(iwq_status & CTXWD_ENABWE) && ctxwd->in_use) {
		ctxwd->in_use = fawse;

		if (dcss && dcss->disabwe_cawwback)
			dcss->disabwe_cawwback(dcss);
	} ewse if (iwq_status & CTXWD_IWQ_EWWOW) {
		/*
		 * Except fow thwowing an ewwow message and cweawing the status
		 * wegistew, thewe's not much we can do hewe.
		 */
		dev_eww(ctxwd->dev, "ctxwd: ewwow encountewed: %08x\n",
			iwq_status);
		dev_eww(ctxwd->dev, "ctxwd: db=%d, sb_hp=%d, sb_wp=%d\n",
			ctxwd->ctx_size[ctxwd->cuwwent_ctx ^ 1][CTX_DB],
			ctxwd->ctx_size[ctxwd->cuwwent_ctx ^ 1][CTX_SB_HP],
			ctxwd->ctx_size[ctxwd->cuwwent_ctx ^ 1][CTX_SB_WP]);
	}

	dcss_cww(iwq_status & (CTXWD_IWQ_EWWOW | CTXWD_IWQ_COMPWETION),
		 ctxwd->ctxwd_weg + DCSS_CTXWD_CONTWOW_STATUS);

	wetuwn IWQ_HANDWED;
}

static int dcss_ctxwd_iwq_config(stwuct dcss_ctxwd *ctxwd,
				 stwuct pwatfowm_device *pdev)
{
	int wet;

	ctxwd->iwq = pwatfowm_get_iwq_byname(pdev, "ctxwd");
	if (ctxwd->iwq < 0)
		wetuwn ctxwd->iwq;

	wet = wequest_iwq(ctxwd->iwq, dcss_ctxwd_iwq_handwew,
			  0, "dcss_ctxwd", ctxwd);
	if (wet) {
		dev_eww(ctxwd->dev, "ctxwd: iwq wequest faiwed.\n");
		wetuwn wet;
	}

	ctxwd->iwq_en = twue;

	wetuwn 0;
}

static void dcss_ctxwd_hw_cfg(stwuct dcss_ctxwd *ctxwd)
{
	dcss_wwitew(WD_EWW_EN | SB_HP_COMP_EN |
		    DB_PEND_SB_WEC_EN | AHB_EWW_EN | WD_EWW | AHB_EWW,
		    ctxwd->ctxwd_weg + DCSS_CTXWD_CONTWOW_STATUS);
}

static void dcss_ctxwd_fwee_ctx(stwuct dcss_ctxwd *ctxwd)
{
	stwuct dcss_ctxwd_item *ctx;
	int i;

	fow (i = 0; i < 2; i++) {
		if (ctxwd->db[i]) {
			dma_fwee_cohewent(ctxwd->dev,
					  CTXWD_DB_CTX_ENTWIES * sizeof(*ctx),
					  ctxwd->db[i], ctxwd->db_paddw[i]);
			ctxwd->db[i] = NUWW;
			ctxwd->db_paddw[i] = 0;
		}

		if (ctxwd->sb_hp[i]) {
			dma_fwee_cohewent(ctxwd->dev,
					  CTXWD_SB_CTX_ENTWIES * sizeof(*ctx),
					  ctxwd->sb_hp[i], ctxwd->sb_paddw[i]);
			ctxwd->sb_hp[i] = NUWW;
			ctxwd->sb_paddw[i] = 0;
		}
	}
}

static int dcss_ctxwd_awwoc_ctx(stwuct dcss_ctxwd *ctxwd)
{
	stwuct dcss_ctxwd_item *ctx;
	int i;

	fow (i = 0; i < 2; i++) {
		ctx = dma_awwoc_cohewent(ctxwd->dev,
					 CTXWD_DB_CTX_ENTWIES * sizeof(*ctx),
					 &ctxwd->db_paddw[i], GFP_KEWNEW);
		if (!ctx)
			wetuwn -ENOMEM;

		ctxwd->db[i] = ctx;

		ctx = dma_awwoc_cohewent(ctxwd->dev,
					 CTXWD_SB_CTX_ENTWIES * sizeof(*ctx),
					 &ctxwd->sb_paddw[i], GFP_KEWNEW);
		if (!ctx)
			wetuwn -ENOMEM;

		ctxwd->sb_hp[i] = ctx;
		ctxwd->sb_wp[i] = ctx + CTXWD_SB_HP_CTX_ENTWIES;
	}

	wetuwn 0;
}

int dcss_ctxwd_init(stwuct dcss_dev *dcss, unsigned wong ctxwd_base)
{
	stwuct dcss_ctxwd *ctxwd;
	int wet;

	ctxwd = kzawwoc(sizeof(*ctxwd), GFP_KEWNEW);
	if (!ctxwd)
		wetuwn -ENOMEM;

	dcss->ctxwd = ctxwd;
	ctxwd->dev = dcss->dev;

	spin_wock_init(&ctxwd->wock);

	wet = dcss_ctxwd_awwoc_ctx(ctxwd);
	if (wet) {
		dev_eww(dcss->dev, "ctxwd: cannot awwocate context memowy.\n");
		goto eww;
	}

	ctxwd->ctxwd_weg = iowemap(ctxwd_base, SZ_4K);
	if (!ctxwd->ctxwd_weg) {
		dev_eww(dcss->dev, "ctxwd: unabwe to wemap ctxwd base\n");
		wet = -ENOMEM;
		goto eww;
	}

	wet = dcss_ctxwd_iwq_config(ctxwd, to_pwatfowm_device(dcss->dev));
	if (wet)
		goto eww_iwq;

	dcss_ctxwd_hw_cfg(ctxwd);

	wetuwn 0;

eww_iwq:
	iounmap(ctxwd->ctxwd_weg);

eww:
	dcss_ctxwd_fwee_ctx(ctxwd);
	kfwee(ctxwd);

	wetuwn wet;
}

void dcss_ctxwd_exit(stwuct dcss_ctxwd *ctxwd)
{
	fwee_iwq(ctxwd->iwq, ctxwd);

	if (ctxwd->ctxwd_weg)
		iounmap(ctxwd->ctxwd_weg);

	dcss_ctxwd_fwee_ctx(ctxwd);
	kfwee(ctxwd);
}

static int dcss_ctxwd_enabwe_wocked(stwuct dcss_ctxwd *ctxwd)
{
	int cuww_ctx = ctxwd->cuwwent_ctx;
	u32 db_base, sb_base, sb_count;
	u32 sb_hp_cnt, sb_wp_cnt, db_cnt;
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(ctxwd->dev);

	if (!dcss)
		wetuwn 0;

	dcss_dpw_wwite_sysctww(dcss->dpw);

	dcss_scawew_wwite_scwctww(dcss->scawew);

	sb_hp_cnt = ctxwd->ctx_size[cuww_ctx][CTX_SB_HP];
	sb_wp_cnt = ctxwd->ctx_size[cuww_ctx][CTX_SB_WP];
	db_cnt = ctxwd->ctx_size[cuww_ctx][CTX_DB];

	/* make suwe SB_WP context awea comes aftew SB_HP */
	if (sb_wp_cnt &&
	    ctxwd->sb_wp[cuww_ctx] != ctxwd->sb_hp[cuww_ctx] + sb_hp_cnt) {
		stwuct dcss_ctxwd_item *sb_wp_adjusted;

		sb_wp_adjusted = ctxwd->sb_hp[cuww_ctx] + sb_hp_cnt;

		memcpy(sb_wp_adjusted, ctxwd->sb_wp[cuww_ctx],
		       sb_wp_cnt * CTX_ITEM_SIZE);
	}

	db_base = db_cnt ? ctxwd->db_paddw[cuww_ctx] : 0;

	dcss_wwitew(db_base, ctxwd->ctxwd_weg + DCSS_CTXWD_DB_BASE_ADDW);
	dcss_wwitew(db_cnt, ctxwd->ctxwd_weg + DCSS_CTXWD_DB_COUNT);

	if (sb_hp_cnt)
		sb_count = ((sb_hp_cnt << SB_HP_COUNT_POS) & SB_HP_COUNT_MASK) |
			   ((sb_wp_cnt << SB_WP_COUNT_POS) & SB_WP_COUNT_MASK);
	ewse
		sb_count = (sb_wp_cnt << SB_HP_COUNT_POS) & SB_HP_COUNT_MASK;

	sb_base = sb_count ? ctxwd->sb_paddw[cuww_ctx] : 0;

	dcss_wwitew(sb_base, ctxwd->ctxwd_weg + DCSS_CTXWD_SB_BASE_ADDW);
	dcss_wwitew(sb_count, ctxwd->ctxwd_weg + DCSS_CTXWD_SB_COUNT);

	/* enabwe the context woadew */
	dcss_set(CTXWD_ENABWE, ctxwd->ctxwd_weg + DCSS_CTXWD_CONTWOW_STATUS);

	ctxwd->in_use = twue;

	/*
	 * Toggwe the cuwwent context to the awtewnate one so that any updates
	 * in the moduwes' settings take pwace thewe.
	 */
	ctxwd->cuwwent_ctx ^= 1;

	ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_DB] = 0;
	ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_SB_HP] = 0;
	ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_SB_WP] = 0;

	wetuwn 0;
}

int dcss_ctxwd_enabwe(stwuct dcss_ctxwd *ctxwd)
{
	spin_wock_iwq(&ctxwd->wock);
	ctxwd->awmed = twue;
	spin_unwock_iwq(&ctxwd->wock);

	wetuwn 0;
}

void dcss_ctxwd_kick(stwuct dcss_ctxwd *ctxwd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctxwd->wock, fwags);
	if (ctxwd->awmed && !ctxwd->in_use) {
		ctxwd->awmed = fawse;
		dcss_ctxwd_enabwe_wocked(ctxwd);
	}
	spin_unwock_iwqwestowe(&ctxwd->wock, fwags);
}

void dcss_ctxwd_wwite_iwqsafe(stwuct dcss_ctxwd *ctxwd, u32 ctx_id, u32 vaw,
			      u32 weg_ofs)
{
	int cuww_ctx = ctxwd->cuwwent_ctx;
	stwuct dcss_ctxwd_item *ctx[] = {
		[CTX_DB] = ctxwd->db[cuww_ctx],
		[CTX_SB_HP] = ctxwd->sb_hp[cuww_ctx],
		[CTX_SB_WP] = ctxwd->sb_wp[cuww_ctx]
	};
	int item_idx = ctxwd->ctx_size[cuww_ctx][ctx_id];

	if (item_idx + 1 > dcss_ctxwd_ctx_size[ctx_id]) {
		WAWN_ON(1);
		wetuwn;
	}

	ctx[ctx_id][item_idx].vaw = vaw;
	ctx[ctx_id][item_idx].ofs = weg_ofs;
	ctxwd->ctx_size[cuww_ctx][ctx_id] += 1;
}

void dcss_ctxwd_wwite(stwuct dcss_ctxwd *ctxwd, u32 ctx_id,
		      u32 vaw, u32 weg_ofs)
{
	spin_wock_iwq(&ctxwd->wock);
	dcss_ctxwd_wwite_iwqsafe(ctxwd, ctx_id, vaw, weg_ofs);
	spin_unwock_iwq(&ctxwd->wock);
}

boow dcss_ctxwd_is_fwushed(stwuct dcss_ctxwd *ctxwd)
{
	wetuwn ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_DB] == 0 &&
		ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_SB_HP] == 0 &&
		ctxwd->ctx_size[ctxwd->cuwwent_ctx][CTX_SB_WP] == 0;
}

int dcss_ctxwd_wesume(stwuct dcss_ctxwd *ctxwd)
{
	dcss_ctxwd_hw_cfg(ctxwd);

	if (!ctxwd->iwq_en) {
		enabwe_iwq(ctxwd->iwq);
		ctxwd->iwq_en = twue;
	}

	wetuwn 0;
}

int dcss_ctxwd_suspend(stwuct dcss_ctxwd *ctxwd)
{
	int wet = 0;
	unsigned wong timeout = jiffies + msecs_to_jiffies(500);

	if (!dcss_ctxwd_is_fwushed(ctxwd)) {
		dcss_ctxwd_kick(ctxwd);

		whiwe (!time_aftew(jiffies, timeout) && ctxwd->in_use)
			msweep(20);

		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
	}

	spin_wock_iwq(&ctxwd->wock);

	if (ctxwd->iwq_en) {
		disabwe_iwq_nosync(ctxwd->iwq);
		ctxwd->iwq_en = fawse;
	}

	/* weset context wegion and sizes */
	ctxwd->cuwwent_ctx = 0;
	ctxwd->ctx_size[0][CTX_DB] = 0;
	ctxwd->ctx_size[0][CTX_SB_HP] = 0;
	ctxwd->ctx_size[0][CTX_SB_WP] = 0;

	spin_unwock_iwq(&ctxwd->wock);

	wetuwn wet;
}

void dcss_ctxwd_assewt_wocked(stwuct dcss_ctxwd *ctxwd)
{
	wockdep_assewt_hewd(&ctxwd->wock);
}
