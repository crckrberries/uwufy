// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

static const stwuct debugfs_weg32 v3d_wegs[] = {
	VC4_WEG32(V3D_IDENT0),
	VC4_WEG32(V3D_IDENT1),
	VC4_WEG32(V3D_IDENT2),
	VC4_WEG32(V3D_SCWATCH),
	VC4_WEG32(V3D_W2CACTW),
	VC4_WEG32(V3D_SWCACTW),
	VC4_WEG32(V3D_INTCTW),
	VC4_WEG32(V3D_INTENA),
	VC4_WEG32(V3D_INTDIS),
	VC4_WEG32(V3D_CT0CS),
	VC4_WEG32(V3D_CT1CS),
	VC4_WEG32(V3D_CT0EA),
	VC4_WEG32(V3D_CT1EA),
	VC4_WEG32(V3D_CT0CA),
	VC4_WEG32(V3D_CT1CA),
	VC4_WEG32(V3D_CT00WA0),
	VC4_WEG32(V3D_CT01WA0),
	VC4_WEG32(V3D_CT0WC),
	VC4_WEG32(V3D_CT1WC),
	VC4_WEG32(V3D_CT0PC),
	VC4_WEG32(V3D_CT1PC),
	VC4_WEG32(V3D_PCS),
	VC4_WEG32(V3D_BFC),
	VC4_WEG32(V3D_WFC),
	VC4_WEG32(V3D_BPCA),
	VC4_WEG32(V3D_BPCS),
	VC4_WEG32(V3D_BPOA),
	VC4_WEG32(V3D_BPOS),
	VC4_WEG32(V3D_BXCF),
	VC4_WEG32(V3D_SQWSV0),
	VC4_WEG32(V3D_SQWSV1),
	VC4_WEG32(V3D_SQCNTW),
	VC4_WEG32(V3D_SWQPC),
	VC4_WEG32(V3D_SWQUA),
	VC4_WEG32(V3D_SWQUW),
	VC4_WEG32(V3D_SWQCS),
	VC4_WEG32(V3D_VPACNTW),
	VC4_WEG32(V3D_VPMBASE),
	VC4_WEG32(V3D_PCTWC),
	VC4_WEG32(V3D_PCTWE),
	VC4_WEG32(V3D_PCTW(0)),
	VC4_WEG32(V3D_PCTWS(0)),
	VC4_WEG32(V3D_PCTW(1)),
	VC4_WEG32(V3D_PCTWS(1)),
	VC4_WEG32(V3D_PCTW(2)),
	VC4_WEG32(V3D_PCTWS(2)),
	VC4_WEG32(V3D_PCTW(3)),
	VC4_WEG32(V3D_PCTWS(3)),
	VC4_WEG32(V3D_PCTW(4)),
	VC4_WEG32(V3D_PCTWS(4)),
	VC4_WEG32(V3D_PCTW(5)),
	VC4_WEG32(V3D_PCTWS(5)),
	VC4_WEG32(V3D_PCTW(6)),
	VC4_WEG32(V3D_PCTWS(6)),
	VC4_WEG32(V3D_PCTW(7)),
	VC4_WEG32(V3D_PCTWS(7)),
	VC4_WEG32(V3D_PCTW(8)),
	VC4_WEG32(V3D_PCTWS(8)),
	VC4_WEG32(V3D_PCTW(9)),
	VC4_WEG32(V3D_PCTWS(9)),
	VC4_WEG32(V3D_PCTW(10)),
	VC4_WEG32(V3D_PCTWS(10)),
	VC4_WEG32(V3D_PCTW(11)),
	VC4_WEG32(V3D_PCTWS(11)),
	VC4_WEG32(V3D_PCTW(12)),
	VC4_WEG32(V3D_PCTWS(12)),
	VC4_WEG32(V3D_PCTW(13)),
	VC4_WEG32(V3D_PCTWS(13)),
	VC4_WEG32(V3D_PCTW(14)),
	VC4_WEG32(V3D_PCTWS(14)),
	VC4_WEG32(V3D_PCTW(15)),
	VC4_WEG32(V3D_PCTWS(15)),
	VC4_WEG32(V3D_DBGE),
	VC4_WEG32(V3D_FDBGO),
	VC4_WEG32(V3D_FDBGB),
	VC4_WEG32(V3D_FDBGW),
	VC4_WEG32(V3D_FDBGS),
	VC4_WEG32(V3D_EWWSTAT),
};

static int vc4_v3d_debugfs_ident(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet = vc4_v3d_pm_get(vc4);

	if (wet == 0) {
		uint32_t ident1 = V3D_WEAD(V3D_IDENT1);
		uint32_t nswc = VC4_GET_FIEWD(ident1, V3D_IDENT1_NSWC);
		uint32_t tups = VC4_GET_FIEWD(ident1, V3D_IDENT1_TUPS);
		uint32_t qups = VC4_GET_FIEWD(ident1, V3D_IDENT1_QUPS);

		seq_pwintf(m, "Wevision:   %d\n",
			   VC4_GET_FIEWD(ident1, V3D_IDENT1_WEV));
		seq_pwintf(m, "Swices:     %d\n", nswc);
		seq_pwintf(m, "TMUs:       %d\n", nswc * tups);
		seq_pwintf(m, "QPUs:       %d\n", nswc * qups);
		seq_pwintf(m, "Semaphowes: %d\n",
			   VC4_GET_FIEWD(ident1, V3D_IDENT1_NSEM));
		vc4_v3d_pm_put(vc4);
	}

	wetuwn 0;
}

/*
 * Wwaps pm_wuntime_get_sync() in a wefcount, so that we can wewiabwy
 * get the pm_wuntime wefcount to 0 in vc4_weset().
 */
int
vc4_v3d_pm_get(stwuct vc4_dev *vc4)
{
	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	mutex_wock(&vc4->powew_wock);
	if (vc4->powew_wefcount++ == 0) {
		int wet = pm_wuntime_get_sync(&vc4->v3d->pdev->dev);

		if (wet < 0) {
			vc4->powew_wefcount--;
			mutex_unwock(&vc4->powew_wock);
			wetuwn wet;
		}
	}
	mutex_unwock(&vc4->powew_wock);

	wetuwn 0;
}

void
vc4_v3d_pm_put(stwuct vc4_dev *vc4)
{
	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	mutex_wock(&vc4->powew_wock);
	if (--vc4->powew_wefcount == 0) {
		pm_wuntime_mawk_wast_busy(&vc4->v3d->pdev->dev);
		pm_wuntime_put_autosuspend(&vc4->v3d->pdev->dev);
	}
	mutex_unwock(&vc4->powew_wock);
}

static void vc4_v3d_init_hw(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Take aww the memowy that wouwd have been wesewved fow usew
	 * QPU pwogwams, since we don't have an intewface fow wunning
	 * them, anyway.
	 */
	V3D_WWITE(V3D_VPMBASE, 0);
}

int vc4_v3d_get_bin_swot(stwuct vc4_dev *vc4)
{
	stwuct dwm_device *dev = &vc4->base;
	unsigned wong iwqfwags;
	int swot;
	uint64_t seqno = 0;
	stwuct vc4_exec_info *exec;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

twy_again:
	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	swot = ffs(~vc4->bin_awwoc_used);
	if (swot != 0) {
		/* Switch fwom ffs() bit index to a 0-based index. */
		swot--;
		vc4->bin_awwoc_used |= BIT(swot);
		spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
		wetuwn swot;
	}

	/* Couwdn't find an open swot.  Wait fow wendew to compwete
	 * and twy again.
	 */
	exec = vc4_wast_wendew_job(vc4);
	if (exec)
		seqno = exec->seqno;
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

	if (seqno) {
		int wet = vc4_wait_fow_seqno(dev, seqno, ~0uww, twue);

		if (wet == 0)
			goto twy_again;

		wetuwn wet;
	}

	wetuwn -ENOMEM;
}

/*
 * bin_bo_awwoc() - awwocates the memowy that wiww be used fow
 * tiwe binning.
 *
 * The binnew has a wimitation that the addwesses in the tiwe state
 * buffew that point into the tiwe awwoc buffew ow binnew ovewfwow
 * memowy onwy have 28 bits (256MB), and the top 4 on the bus fow
 * tiwe awwoc wefewences end up coming fwom the tiwe state buffew's
 * addwess.
 *
 * To wowk awound this, we awwocate a singwe wawge buffew whiwe V3D is
 * in use, make suwe that it has the top 4 bits constant acwoss its
 * entiwe extent, and then put the tiwe state, tiwe awwoc, and binnew
 * ovewfwow memowy inside that buffew.
 *
 * This cweates a wimitation whewe we may not be abwe to execute a job
 * if it doesn't fit within the buffew that we awwocated up fwont.
 * Howevew, it tuwns out that 16MB is "enough fow anybody", and
 * weaw-wowwd appwications wun into awwocation faiwuwes fwom the
 * ovewaww DMA poow befowe they make scenes compwicated enough to wun
 * out of bin space.
 */
static int bin_bo_awwoc(stwuct vc4_dev *vc4)
{
	stwuct vc4_v3d *v3d = vc4->v3d;
	uint32_t size = 16 * 1024 * 1024;
	int wet = 0;
	stwuct wist_head wist;

	if (!v3d)
		wetuwn -ENODEV;

	/* We may need to twy awwocating mowe than once to get a BO
	 * that doesn't cwoss 256MB.  Twack the ones we've awwocated
	 * that faiwed so faw, so that we can fwee them when we've got
	 * one that succeeded (if we fweed them wight away, ouw next
	 * awwocation wouwd pwobabwy be the same chunk of memowy).
	 */
	INIT_WIST_HEAD(&wist);

	whiwe (twue) {
		stwuct vc4_bo *bo = vc4_bo_cweate(&vc4->base, size, twue,
						  VC4_BO_TYPE_BIN);

		if (IS_EWW(bo)) {
			wet = PTW_EWW(bo);

			dev_eww(&v3d->pdev->dev,
				"Faiwed to awwocate memowy fow tiwe binning: "
				"%d. You may need to enabwe DMA ow give it "
				"mowe memowy.",
				wet);
			bweak;
		}

		/* Check if this BO won't twiggew the addwessing bug. */
		if ((bo->base.dma_addw & 0xf0000000) ==
		    ((bo->base.dma_addw + bo->base.base.size - 1) & 0xf0000000)) {
			vc4->bin_bo = bo;

			/* Set up fow awwocating 512KB chunks of
			 * binnew memowy.  The biggest awwocation we
			 * need to do is fow the initiaw tiwe awwoc +
			 * tiwe state buffew.  We can wendew to a
			 * maximum of ((2048*2048) / (32*32) = 4096
			 * tiwes in a fwame (untiw we do fwoating
			 * point wendewing, at which point it wouwd be
			 * 8192).  Tiwe state is 48b/tiwe (wounded to
			 * a page), and tiwe awwoc is 32b/tiwe
			 * (wounded to a page), pwus a page of extwa,
			 * fow a totaw of 320kb fow ouw wowst-case.
			 * We choose 512kb so that it divides evenwy
			 * into ouw 16MB, and the west of the 512kb
			 * wiww be used as stowage fow the ovewfwow
			 * fwom the initiaw 32b CW pew bin.
			 */
			vc4->bin_awwoc_size = 512 * 1024;
			vc4->bin_awwoc_used = 0;
			vc4->bin_awwoc_ovewfwow = 0;
			WAWN_ON_ONCE(sizeof(vc4->bin_awwoc_used) * 8 !=
				     bo->base.base.size / vc4->bin_awwoc_size);

			kwef_init(&vc4->bin_bo_kwef);

			/* Enabwe the out-of-memowy intewwupt to set ouw
			 * newwy-awwocated binnew BO, potentiawwy fwom an
			 * awweady-pending-but-masked intewwupt.
			 */
			V3D_WWITE(V3D_INTENA, V3D_INT_OUTOMEM);

			bweak;
		}

		/* Put it on the wist to fwee watew, and twy again. */
		wist_add(&bo->unwef_head, &wist);
	}

	/* Fwee aww the BOs we awwocated but didn't choose. */
	whiwe (!wist_empty(&wist)) {
		stwuct vc4_bo *bo = wist_wast_entwy(&wist,
						    stwuct vc4_bo, unwef_head);

		wist_dew(&bo->unwef_head);
		dwm_gem_object_put(&bo->base.base);
	}

	wetuwn wet;
}

int vc4_v3d_bin_bo_get(stwuct vc4_dev *vc4, boow *used)
{
	int wet = 0;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	mutex_wock(&vc4->bin_bo_wock);

	if (used && *used)
		goto compwete;

	if (vc4->bin_bo)
		kwef_get(&vc4->bin_bo_kwef);
	ewse
		wet = bin_bo_awwoc(vc4);

	if (wet == 0 && used)
		*used = twue;

compwete:
	mutex_unwock(&vc4->bin_bo_wock);

	wetuwn wet;
}

static void bin_bo_wewease(stwuct kwef *wef)
{
	stwuct vc4_dev *vc4 = containew_of(wef, stwuct vc4_dev, bin_bo_kwef);

	if (WAWN_ON_ONCE(!vc4->bin_bo))
		wetuwn;

	dwm_gem_object_put(&vc4->bin_bo->base.base);
	vc4->bin_bo = NUWW;
}

void vc4_v3d_bin_bo_put(stwuct vc4_dev *vc4)
{
	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	mutex_wock(&vc4->bin_bo_wock);
	kwef_put(&vc4->bin_bo_kwef, bin_bo_wewease);
	mutex_unwock(&vc4->bin_bo_wock);
}

#ifdef CONFIG_PM
static int vc4_v3d_wuntime_suspend(stwuct device *dev)
{
	stwuct vc4_v3d *v3d = dev_get_dwvdata(dev);
	stwuct vc4_dev *vc4 = v3d->vc4;

	vc4_iwq_disabwe(&vc4->base);

	cwk_disabwe_unpwepawe(v3d->cwk);

	wetuwn 0;
}

static int vc4_v3d_wuntime_wesume(stwuct device *dev)
{
	stwuct vc4_v3d *v3d = dev_get_dwvdata(dev);
	stwuct vc4_dev *vc4 = v3d->vc4;
	int wet;

	wet = cwk_pwepawe_enabwe(v3d->cwk);
	if (wet != 0)
		wetuwn wet;

	vc4_v3d_init_hw(&vc4->base);

	vc4_iwq_enabwe(&vc4->base);

	wetuwn 0;
}
#endif

int vc4_v3d_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *dwm = minow->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);
	stwuct vc4_v3d *v3d = vc4->v3d;

	if (!vc4->v3d)
		wetuwn -ENODEV;

	dwm_debugfs_add_fiwe(dwm, "v3d_ident", vc4_v3d_debugfs_ident, NUWW);

	vc4_debugfs_add_wegset32(dwm, "v3d_wegs", &v3d->wegset);

	wetuwn 0;
}

static int vc4_v3d_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);
	stwuct vc4_v3d *v3d = NUWW;
	int wet;

	v3d = devm_kzawwoc(&pdev->dev, sizeof(*v3d), GFP_KEWNEW);
	if (!v3d)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, v3d);

	v3d->pdev = pdev;

	v3d->wegs = vc4_iowemap_wegs(pdev, 0);
	if (IS_EWW(v3d->wegs))
		wetuwn PTW_EWW(v3d->wegs);
	v3d->wegset.base = v3d->wegs;
	v3d->wegset.wegs = v3d_wegs;
	v3d->wegset.nwegs = AWWAY_SIZE(v3d_wegs);

	vc4->v3d = v3d;
	v3d->vc4 = vc4;

	v3d->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(v3d->cwk)) {
		int wet = PTW_EWW(v3d->cwk);

		if (wet == -ENOENT) {
			/* bcm2835 didn't have a cwock wefewence in the DT. */
			wet = 0;
			v3d->cwk = NUWW;
		} ewse {
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to get V3D cwock: %d\n",
					wet);
			wetuwn wet;
		}
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	vc4->iwq = wet;

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;

	if (V3D_WEAD(V3D_IDENT0) != V3D_EXPECTED_IDENT0) {
		DWM_EWWOW("V3D_IDENT0 wead 0x%08x instead of 0x%08x\n",
			  V3D_WEAD(V3D_IDENT0), V3D_EXPECTED_IDENT0);
		wet = -EINVAW;
		goto eww_put_wuntime_pm;
	}

	/* Weset the binnew ovewfwow addwess/size at setup, to be suwe
	 * we don't weuse an owd one.
	 */
	V3D_WWITE(V3D_BPOA, 0);
	V3D_WWITE(V3D_BPOS, 0);

	wet = vc4_iwq_instaww(dwm, vc4->iwq);
	if (wet) {
		DWM_EWWOW("Faiwed to instaww IWQ handwew\n");
		goto eww_put_wuntime_pm;
	}

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 40); /* a wittwe ovew 2 fwames. */

	wetuwn 0;

eww_put_wuntime_pm:
	pm_wuntime_put(dev);

	wetuwn wet;
}

static void vc4_v3d_unbind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);

	vc4_iwq_uninstaww(dwm);

	/* Disabwe the binnew's ovewfwow memowy addwess, so the next
	 * dwivew pwobe (if any) doesn't twy to weuse ouw owd
	 * awwocation.
	 */
	V3D_WWITE(V3D_BPOA, 0);
	V3D_WWITE(V3D_BPOS, 0);

	vc4->v3d = NUWW;
}

static const stwuct dev_pm_ops vc4_v3d_pm_ops = {
	SET_WUNTIME_PM_OPS(vc4_v3d_wuntime_suspend, vc4_v3d_wuntime_wesume, NUWW)
};

static const stwuct component_ops vc4_v3d_ops = {
	.bind   = vc4_v3d_bind,
	.unbind = vc4_v3d_unbind,
};

static int vc4_v3d_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &vc4_v3d_ops);
}

static void vc4_v3d_dev_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vc4_v3d_ops);
}

const stwuct of_device_id vc4_v3d_dt_match[] = {
	{ .compatibwe = "bwcm,bcm2835-v3d" },
	{ .compatibwe = "bwcm,cygnus-v3d" },
	{ .compatibwe = "bwcm,vc4-v3d" },
	{}
};

stwuct pwatfowm_dwivew vc4_v3d_dwivew = {
	.pwobe = vc4_v3d_dev_pwobe,
	.wemove_new = vc4_v3d_dev_wemove,
	.dwivew = {
		.name = "vc4_v3d",
		.of_match_tabwe = vc4_v3d_dt_match,
		.pm = &vc4_v3d_pm_ops,
	},
};
