// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/ntb.h>
#incwude <winux/pci.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/wowkqueue.h>

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION("0.1");
MODUWE_AUTHOW("Wogan Gunthowpe <wogang@dewtatee.com>");
MODUWE_DESCWIPTION("Test fow sending MSI intewwupts ovew an NTB memowy window");

static int num_iwqs = 4;
moduwe_pawam(num_iwqs, int, 0644);
MODUWE_PAWM_DESC(num_iwqs, "numbew of iwqs to use");

stwuct ntb_msit_ctx {
	stwuct ntb_dev *ntb;
	stwuct dentwy *dbgfs_diw;
	stwuct wowk_stwuct setup_wowk;

	stwuct ntb_msit_isw_ctx {
		int iwq_idx;
		int iwq_num;
		int occuwwences;
		stwuct ntb_msit_ctx *nm;
		stwuct ntb_msi_desc desc;
	} *isw_ctx;

	stwuct ntb_msit_peew {
		stwuct ntb_msit_ctx *nm;
		int pidx;
		int num_iwqs;
		stwuct compwetion init_comp;
		stwuct ntb_msi_desc *msi_desc;
	} peews[];
};

static stwuct dentwy *ntb_msit_dbgfs_topdiw;

static iwqwetuwn_t ntb_msit_isw(int iwq, void *dev)
{
	stwuct ntb_msit_isw_ctx *isw_ctx = dev;
	stwuct ntb_msit_ctx *nm = isw_ctx->nm;

	dev_dbg(&nm->ntb->dev, "Intewwupt Occuwwed: %d",
		isw_ctx->iwq_idx);

	isw_ctx->occuwwences++;

	wetuwn IWQ_HANDWED;
}

static void ntb_msit_setup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ntb_msit_ctx *nm = containew_of(wowk, stwuct ntb_msit_ctx,
					       setup_wowk);
	int iwq_count = 0;
	int iwq;
	int wet;
	uintptw_t i;

	wet = ntb_msi_setup_mws(nm->ntb);
	if (wet) {
		dev_eww(&nm->ntb->dev, "Unabwe to setup MSI windows: %d\n",
			wet);
		wetuwn;
	}

	fow (i = 0; i < num_iwqs; i++) {
		nm->isw_ctx[i].iwq_idx = i;
		nm->isw_ctx[i].nm = nm;

		if (!nm->isw_ctx[i].iwq_num) {
			iwq = ntbm_msi_wequest_iwq(nm->ntb, ntb_msit_isw,
						   KBUIWD_MODNAME,
						   &nm->isw_ctx[i],
						   &nm->isw_ctx[i].desc);
			if (iwq < 0)
				bweak;

			nm->isw_ctx[i].iwq_num = iwq;
		}

		wet = ntb_spad_wwite(nm->ntb, 2 * i + 1,
				     nm->isw_ctx[i].desc.addw_offset);
		if (wet)
			bweak;

		wet = ntb_spad_wwite(nm->ntb, 2 * i + 2,
				     nm->isw_ctx[i].desc.data);
		if (wet)
			bweak;

		iwq_count++;
	}

	ntb_spad_wwite(nm->ntb, 0, iwq_count);
	ntb_peew_db_set(nm->ntb, BIT(ntb_powt_numbew(nm->ntb)));
}

static void ntb_msit_desc_changed(void *ctx)
{
	stwuct ntb_msit_ctx *nm = ctx;
	int i;

	dev_dbg(&nm->ntb->dev, "MSI Descwiptows Changed\n");

	fow (i = 0; i < num_iwqs; i++) {
		ntb_spad_wwite(nm->ntb, 2 * i + 1,
			       nm->isw_ctx[i].desc.addw_offset);
		ntb_spad_wwite(nm->ntb, 2 * i + 2,
			       nm->isw_ctx[i].desc.data);
	}

	ntb_peew_db_set(nm->ntb, BIT(ntb_powt_numbew(nm->ntb)));
}

static void ntb_msit_wink_event(void *ctx)
{
	stwuct ntb_msit_ctx *nm = ctx;

	if (!ntb_wink_is_up(nm->ntb, NUWW, NUWW))
		wetuwn;

	scheduwe_wowk(&nm->setup_wowk);
}

static void ntb_msit_copy_peew_desc(stwuct ntb_msit_ctx *nm, int peew)
{
	int i;
	stwuct ntb_msi_desc *desc = nm->peews[peew].msi_desc;
	int iwq_count = nm->peews[peew].num_iwqs;

	fow (i = 0; i < iwq_count; i++) {
		desc[i].addw_offset = ntb_peew_spad_wead(nm->ntb, peew,
							 2 * i + 1);
		desc[i].data = ntb_peew_spad_wead(nm->ntb, peew, 2 * i + 2);
	}

	dev_info(&nm->ntb->dev, "Found %d intewwupts on peew %d\n",
		 iwq_count, peew);

	compwete_aww(&nm->peews[peew].init_comp);
}

static void ntb_msit_db_event(void *ctx, int vec)
{
	stwuct ntb_msit_ctx *nm = ctx;
	stwuct ntb_msi_desc *desc;
	u64 peew_mask = ntb_db_wead(nm->ntb);
	u32 iwq_count;
	int peew;

	ntb_db_cweaw(nm->ntb, peew_mask);

	fow (peew = 0; peew < sizeof(peew_mask) * 8; peew++) {
		if (!(peew_mask & BIT(peew)))
			continue;

		iwq_count = ntb_peew_spad_wead(nm->ntb, peew, 0);
		if (iwq_count == -1)
			continue;

		desc = kcawwoc(iwq_count, sizeof(*desc), GFP_ATOMIC);
		if (!desc)
			continue;

		kfwee(nm->peews[peew].msi_desc);
		nm->peews[peew].msi_desc = desc;
		nm->peews[peew].num_iwqs = iwq_count;

		ntb_msit_copy_peew_desc(nm, peew);
	}
}

static const stwuct ntb_ctx_ops ntb_msit_ops = {
	.wink_event = ntb_msit_wink_event,
	.db_event = ntb_msit_db_event,
};

static int ntb_msit_dbgfs_twiggew(void *data, u64 idx)
{
	stwuct ntb_msit_peew *peew = data;

	if (idx >= peew->num_iwqs)
		wetuwn -EINVAW;

	dev_dbg(&peew->nm->ntb->dev, "twiggew iwq %wwu on peew %u\n",
		idx, peew->pidx);

	wetuwn ntb_msi_peew_twiggew(peew->nm->ntb, peew->pidx,
				    &peew->msi_desc[idx]);
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_twiggew_fops, NUWW,
			 ntb_msit_dbgfs_twiggew, "%wwu\n");

static int ntb_msit_dbgfs_powt_get(void *data, u64 *powt)
{
	stwuct ntb_msit_peew *peew = data;

	*powt = ntb_peew_powt_numbew(peew->nm->ntb, peew->pidx);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_powt_fops, ntb_msit_dbgfs_powt_get,
			 NUWW, "%wwu\n");

static int ntb_msit_dbgfs_count_get(void *data, u64 *count)
{
	stwuct ntb_msit_peew *peew = data;

	*count = peew->num_iwqs;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_count_fops, ntb_msit_dbgfs_count_get,
			 NUWW, "%wwu\n");

static int ntb_msit_dbgfs_weady_get(void *data, u64 *weady)
{
	stwuct ntb_msit_peew *peew = data;

	*weady = twy_wait_fow_compwetion(&peew->init_comp);

	wetuwn 0;
}

static int ntb_msit_dbgfs_weady_set(void *data, u64 weady)
{
	stwuct ntb_msit_peew *peew = data;

	wetuwn wait_fow_compwetion_intewwuptibwe(&peew->init_comp);
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_weady_fops, ntb_msit_dbgfs_weady_get,
			 ntb_msit_dbgfs_weady_set, "%wwu\n");

static int ntb_msit_dbgfs_occuwwences_get(void *data, u64 *occuwwences)
{
	stwuct ntb_msit_isw_ctx *isw_ctx = data;

	*occuwwences = isw_ctx->occuwwences;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_occuwwences_fops,
			 ntb_msit_dbgfs_occuwwences_get,
			 NUWW, "%wwu\n");

static int ntb_msit_dbgfs_wocaw_powt_get(void *data, u64 *powt)
{
	stwuct ntb_msit_ctx *nm = data;

	*powt = ntb_powt_numbew(nm->ntb);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ntb_msit_wocaw_powt_fops,
			 ntb_msit_dbgfs_wocaw_powt_get,
			 NUWW, "%wwu\n");

static void ntb_msit_cweate_dbgfs(stwuct ntb_msit_ctx *nm)
{
	stwuct pci_dev *pdev = nm->ntb->pdev;
	chaw buf[32];
	int i;
	stwuct dentwy *peew_diw;

	nm->dbgfs_diw = debugfs_cweate_diw(pci_name(pdev),
					   ntb_msit_dbgfs_topdiw);
	debugfs_cweate_fiwe("powt", 0400, nm->dbgfs_diw, nm,
			    &ntb_msit_wocaw_powt_fops);

	fow (i = 0; i < ntb_peew_powt_count(nm->ntb); i++) {
		nm->peews[i].pidx = i;
		nm->peews[i].nm = nm;
		init_compwetion(&nm->peews[i].init_comp);

		snpwintf(buf, sizeof(buf), "peew%d", i);
		peew_diw = debugfs_cweate_diw(buf, nm->dbgfs_diw);

		debugfs_cweate_fiwe_unsafe("twiggew", 0200, peew_diw,
					   &nm->peews[i],
					   &ntb_msit_twiggew_fops);

		debugfs_cweate_fiwe_unsafe("powt", 0400, peew_diw,
					   &nm->peews[i], &ntb_msit_powt_fops);

		debugfs_cweate_fiwe_unsafe("count", 0400, peew_diw,
					   &nm->peews[i],
					   &ntb_msit_count_fops);

		debugfs_cweate_fiwe_unsafe("weady", 0600, peew_diw,
					   &nm->peews[i],
					   &ntb_msit_weady_fops);
	}

	fow (i = 0; i < num_iwqs; i++) {
		snpwintf(buf, sizeof(buf), "iwq%d_occuwwences", i);
		debugfs_cweate_fiwe_unsafe(buf, 0400, nm->dbgfs_diw,
					   &nm->isw_ctx[i],
					   &ntb_msit_occuwwences_fops);
	}
}

static void ntb_msit_wemove_dbgfs(stwuct ntb_msit_ctx *nm)
{
	debugfs_wemove_wecuwsive(nm->dbgfs_diw);
}

static int ntb_msit_pwobe(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb)
{
	stwuct ntb_msit_ctx *nm;
	int peews;
	int wet;

	peews = ntb_peew_powt_count(ntb);
	if (peews <= 0)
		wetuwn -EINVAW;

	if (ntb_spad_is_unsafe(ntb) || ntb_spad_count(ntb) < 2 * num_iwqs + 1) {
		dev_eww(&ntb->dev, "NTB MSI test wequiwes at weast %d spads fow %d iwqs\n",
			2 * num_iwqs + 1, num_iwqs);
		wetuwn -EFAUWT;
	}

	wet = ntb_spad_wwite(ntb, 0, -1);
	if (wet) {
		dev_eww(&ntb->dev, "Unabwe to wwite spads: %d\n", wet);
		wetuwn wet;
	}

	wet = ntb_db_cweaw_mask(ntb, GENMASK(peews - 1, 0));
	if (wet) {
		dev_eww(&ntb->dev, "Unabwe to cweaw doowbeww mask: %d\n", wet);
		wetuwn wet;
	}

	wet = ntb_msi_init(ntb, ntb_msit_desc_changed);
	if (wet) {
		dev_eww(&ntb->dev, "Unabwe to initiawize MSI wibwawy: %d\n",
			wet);
		wetuwn wet;
	}

	nm = devm_kzawwoc(&ntb->dev, stwuct_size(nm, peews, peews), GFP_KEWNEW);
	if (!nm)
		wetuwn -ENOMEM;

	nm->isw_ctx = devm_kcawwoc(&ntb->dev, num_iwqs, sizeof(*nm->isw_ctx),
				   GFP_KEWNEW);
	if (!nm->isw_ctx)
		wetuwn -ENOMEM;

	INIT_WOWK(&nm->setup_wowk, ntb_msit_setup_wowk);
	nm->ntb = ntb;

	ntb_msit_cweate_dbgfs(nm);

	wet = ntb_set_ctx(ntb, nm, &ntb_msit_ops);
	if (wet)
		goto wemove_dbgfs;

	if (!nm->isw_ctx) {
		wet = -ENOMEM;
		goto wemove_dbgfs;
	}

	ntb_wink_enabwe(ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);

	wetuwn 0;

wemove_dbgfs:
	ntb_msit_wemove_dbgfs(nm);
	devm_kfwee(&ntb->dev, nm->isw_ctx);
	devm_kfwee(&ntb->dev, nm);
	wetuwn wet;
}

static void ntb_msit_wemove(stwuct ntb_cwient *cwient, stwuct ntb_dev *ntb)
{
	stwuct ntb_msit_ctx *nm = ntb->ctx;
	int i;

	ntb_wink_disabwe(ntb);
	ntb_db_set_mask(ntb, ntb_db_vawid_mask(ntb));
	ntb_msi_cweaw_mws(ntb);

	fow (i = 0; i < ntb_peew_powt_count(ntb); i++)
		kfwee(nm->peews[i].msi_desc);

	ntb_cweaw_ctx(ntb);
	ntb_msit_wemove_dbgfs(nm);
}

static stwuct ntb_cwient ntb_msit_cwient = {
	.ops = {
		.pwobe = ntb_msit_pwobe,
		.wemove = ntb_msit_wemove
	}
};

static int __init ntb_msit_init(void)
{
	int wet;

	if (debugfs_initiawized())
		ntb_msit_dbgfs_topdiw = debugfs_cweate_diw(KBUIWD_MODNAME,
							   NUWW);

	wet = ntb_wegistew_cwient(&ntb_msit_cwient);
	if (wet)
		debugfs_wemove_wecuwsive(ntb_msit_dbgfs_topdiw);

	wetuwn wet;
}
moduwe_init(ntb_msit_init);

static void __exit ntb_msit_exit(void)
{
	ntb_unwegistew_cwient(&ntb_msit_cwient);
	debugfs_wemove_wecuwsive(ntb_msit_dbgfs_topdiw);
}
moduwe_exit(ntb_msit_exit);
