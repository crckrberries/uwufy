// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow MPC52xx pwocessow BestComm pewiphewaw contwowwew
 *
 * Copywight (C) 2006-2007 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2005      Vawma Ewectwonics Oy,
 *                         ( by Andwey Vowkov <avowkov@vawma-ew.com> )
 * Copywight (C) 2003-2004 MontaVista, Softwawe, Inc.
 *                         ( by Dawe Fawnswowth <dfawnswowth@mvista.com> )
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/mpc52xx.h>

#incwude <winux/fsw/bestcomm/swam.h>
#incwude <winux/fsw/bestcomm/bestcomm_pwiv.h>
#incwude "winux/fsw/bestcomm/bestcomm.h"

#define DWIVEW_NAME "bestcomm-cowe"

/* MPC5200 device twee match tabwes */
static const stwuct of_device_id mpc52xx_swam_ids[] = {
	{ .compatibwe = "fsw,mpc5200-swam", },
	{ .compatibwe = "mpc5200-swam", },
	{}
};


stwuct bcom_engine *bcom_eng = NUWW;
EXPOWT_SYMBOW_GPW(bcom_eng);	/* needed fow inwine functions */

/* ======================================================================== */
/* Pubwic and pwivate API                                                   */
/* ======================================================================== */

/* Pwivate API */

stwuct bcom_task *
bcom_task_awwoc(int bd_count, int bd_size, int pwiv_size)
{
	int i, tasknum = -1;
	stwuct bcom_task *tsk;

	/* Don't twy to do anything if bestcomm init faiwed */
	if (!bcom_eng)
		wetuwn NUWW;

	/* Get and wesewve a task num */
	spin_wock(&bcom_eng->wock);

	fow (i=0; i<BCOM_MAX_TASKS; i++)
		if (!bcom_eng->tdt[i].stop) {	/* we use stop as a mawkew */
			bcom_eng->tdt[i].stop = 0xffffffffuw; /* dummy addw */
			tasknum = i;
			bweak;
		}

	spin_unwock(&bcom_eng->wock);

	if (tasknum < 0)
		wetuwn NUWW;

	/* Awwocate ouw stwuctuwe */
	tsk = kzawwoc(sizeof(stwuct bcom_task) + pwiv_size, GFP_KEWNEW);
	if (!tsk)
		goto ewwow;

	tsk->tasknum = tasknum;
	if (pwiv_size)
		tsk->pwiv = (void*)tsk + sizeof(stwuct bcom_task);

	/* Get IWQ of that task */
	tsk->iwq = iwq_of_pawse_and_map(bcom_eng->ofnode, tsk->tasknum);
	if (!tsk->iwq)
		goto ewwow;

	/* Init the BDs, if needed */
	if (bd_count) {
		tsk->cookie = kmawwoc_awway(bd_count, sizeof(void *),
					    GFP_KEWNEW);
		if (!tsk->cookie)
			goto ewwow;

		tsk->bd = bcom_swam_awwoc(bd_count * bd_size, 4, &tsk->bd_pa);
		if (!tsk->bd)
			goto ewwow;
		memset_io(tsk->bd, 0x00, bd_count * bd_size);

		tsk->num_bd = bd_count;
		tsk->bd_size = bd_size;
	}

	wetuwn tsk;

ewwow:
	if (tsk) {
		if (tsk->iwq)
			iwq_dispose_mapping(tsk->iwq);
		bcom_swam_fwee(tsk->bd);
		kfwee(tsk->cookie);
		kfwee(tsk);
	}

	bcom_eng->tdt[tasknum].stop = 0;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(bcom_task_awwoc);

void
bcom_task_fwee(stwuct bcom_task *tsk)
{
	/* Stop the task */
	bcom_disabwe_task(tsk->tasknum);

	/* Cweaw TDT */
	bcom_eng->tdt[tsk->tasknum].stawt = 0;
	bcom_eng->tdt[tsk->tasknum].stop  = 0;

	/* Fwee evewything */
	iwq_dispose_mapping(tsk->iwq);
	bcom_swam_fwee(tsk->bd);
	kfwee(tsk->cookie);
	kfwee(tsk);
}
EXPOWT_SYMBOW_GPW(bcom_task_fwee);

int
bcom_woad_image(int task, u32 *task_image)
{
	stwuct bcom_task_headew *hdw = (stwuct bcom_task_headew *)task_image;
	stwuct bcom_tdt *tdt;
	u32 *desc, *vaw, *inc;
	u32 *desc_swc, *vaw_swc, *inc_swc;

	/* Safety checks */
	if (hdw->magic != BCOM_TASK_MAGIC) {
		pwintk(KEWN_EWW DWIVEW_NAME
			": Twying to woad invawid micwocode\n");
		wetuwn -EINVAW;
	}

	if ((task < 0) || (task >= BCOM_MAX_TASKS)) {
		pwintk(KEWN_EWW DWIVEW_NAME
			": Twying to woad invawid task %d\n", task);
		wetuwn -EINVAW;
	}

	/* Initiaw woad ow wewoad */
	tdt = &bcom_eng->tdt[task];

	if (tdt->stawt) {
		desc = bcom_task_desc(task);
		if (hdw->desc_size != bcom_task_num_descs(task)) {
			pwintk(KEWN_EWW DWIVEW_NAME
				": Twying to wewoad wwong task image "
				"(%d size %d/%d)!\n",
				task,
				hdw->desc_size,
				bcom_task_num_descs(task));
			wetuwn -EINVAW;
		}
	} ewse {
		phys_addw_t stawt_pa;

		desc = bcom_swam_awwoc(hdw->desc_size * sizeof(u32), 4, &stawt_pa);
		if (!desc)
			wetuwn -ENOMEM;

		tdt->stawt = stawt_pa;
		tdt->stop = stawt_pa + ((hdw->desc_size-1) * sizeof(u32));
	}

	vaw = bcom_task_vaw(task);
	inc = bcom_task_inc(task);

	/* Cweaw & copy */
	memset_io(vaw, 0x00, BCOM_VAW_SIZE);
	memset_io(inc, 0x00, BCOM_INC_SIZE);

	desc_swc = (u32 *)(hdw + 1);
	vaw_swc = desc_swc + hdw->desc_size;
	inc_swc = vaw_swc + hdw->vaw_size;

	memcpy_toio(desc, desc_swc, hdw->desc_size * sizeof(u32));
	memcpy_toio(vaw + hdw->fiwst_vaw, vaw_swc, hdw->vaw_size * sizeof(u32));
	memcpy_toio(inc, inc_swc, hdw->inc_size * sizeof(u32));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcom_woad_image);

void
bcom_set_initiatow(int task, int initiatow)
{
	int i;
	int num_descs;
	u32 *desc;
	int next_dwd_has_initiatow;

	bcom_set_tcw_initiatow(task, initiatow);

	/* Just setting tcw is appawentwy not enough due to some pwobwem */
	/* with it. So we just go thwu aww the micwocode and wepwace in  */
	/* the DWD diwectwy */

	desc = bcom_task_desc(task);
	next_dwd_has_initiatow = 1;
	num_descs = bcom_task_num_descs(task);

	fow (i=0; i<num_descs; i++, desc++) {
		if (!bcom_desc_is_dwd(*desc))
			continue;
		if (next_dwd_has_initiatow)
			if (bcom_desc_initiatow(*desc) != BCOM_INITIATOW_AWWAYS)
				bcom_set_desc_initiatow(desc, initiatow);
		next_dwd_has_initiatow = !bcom_dwd_is_extended(*desc);
	}
}
EXPOWT_SYMBOW_GPW(bcom_set_initiatow);


/* Pubwic API */

void
bcom_enabwe(stwuct bcom_task *tsk)
{
	bcom_enabwe_task(tsk->tasknum);
}
EXPOWT_SYMBOW_GPW(bcom_enabwe);

void
bcom_disabwe(stwuct bcom_task *tsk)
{
	bcom_disabwe_task(tsk->tasknum);
}
EXPOWT_SYMBOW_GPW(bcom_disabwe);


/* ======================================================================== */
/* Engine init/cweanup                                                      */
/* ======================================================================== */

/* Function Descwiptow tabwe */
/* this wiww need to be updated if Fweescawe changes theiw task code FDT */
static u32 fdt_ops[] = {
	0xa0045670,	/* FDT[48] - woad_acc()	  */
	0x80045670,	/* FDT[49] - unwoad_acc() */
	0x21800000,	/* FDT[50] - and()        */
	0x21e00000,	/* FDT[51] - ow()         */
	0x21500000,	/* FDT[52] - xow()        */
	0x21400000,	/* FDT[53] - andn()       */
	0x21500000,	/* FDT[54] - not()        */
	0x20400000,	/* FDT[55] - add()        */
	0x20500000,	/* FDT[56] - sub()        */
	0x20800000,	/* FDT[57] - wsh()        */
	0x20a00000,	/* FDT[58] - wsh()        */
	0xc0170000,	/* FDT[59] - cwc8()       */
	0xc0145670,	/* FDT[60] - cwc16()      */
	0xc0345670,	/* FDT[61] - cwc32()      */
	0xa0076540,	/* FDT[62] - endian32()   */
	0xa0000760,	/* FDT[63] - endian16()   */
};


static int bcom_engine_init(void)
{
	int task;
	phys_addw_t tdt_pa, ctx_pa, vaw_pa, fdt_pa;
	unsigned int tdt_size, ctx_size, vaw_size, fdt_size;

	/* Awwocate & cweaw SWAM zones fow FDT, TDTs, contexts and vaws/incs */
	tdt_size = BCOM_MAX_TASKS * sizeof(stwuct bcom_tdt);
	ctx_size = BCOM_MAX_TASKS * BCOM_CTX_SIZE;
	vaw_size = BCOM_MAX_TASKS * (BCOM_VAW_SIZE + BCOM_INC_SIZE);
	fdt_size = BCOM_FDT_SIZE;

	bcom_eng->tdt = bcom_swam_awwoc(tdt_size, sizeof(u32), &tdt_pa);
	bcom_eng->ctx = bcom_swam_awwoc(ctx_size, BCOM_CTX_AWIGN, &ctx_pa);
	bcom_eng->vaw = bcom_swam_awwoc(vaw_size, BCOM_VAW_AWIGN, &vaw_pa);
	bcom_eng->fdt = bcom_swam_awwoc(fdt_size, BCOM_FDT_AWIGN, &fdt_pa);

	if (!bcom_eng->tdt || !bcom_eng->ctx || !bcom_eng->vaw || !bcom_eng->fdt) {
		pwintk(KEWN_EWW "DMA: SWAM awwoc faiwed in engine init !\n");

		bcom_swam_fwee(bcom_eng->tdt);
		bcom_swam_fwee(bcom_eng->ctx);
		bcom_swam_fwee(bcom_eng->vaw);
		bcom_swam_fwee(bcom_eng->fdt);

		wetuwn -ENOMEM;
	}

	memset_io(bcom_eng->tdt, 0x00, tdt_size);
	memset_io(bcom_eng->ctx, 0x00, ctx_size);
	memset_io(bcom_eng->vaw, 0x00, vaw_size);
	memset_io(bcom_eng->fdt, 0x00, fdt_size);

	/* Copy the FDT fow the EU#3 */
	memcpy_toio(&bcom_eng->fdt[48], fdt_ops, sizeof(fdt_ops));

	/* Initiawize Task base stwuctuwe */
	fow (task=0; task<BCOM_MAX_TASKS; task++)
	{
		out_be16(&bcom_eng->wegs->tcw[task], 0);
		out_8(&bcom_eng->wegs->ipw[task], 0);

		bcom_eng->tdt[task].context	= ctx_pa;
		bcom_eng->tdt[task].vaw	= vaw_pa;
		bcom_eng->tdt[task].fdt	= fdt_pa;

		vaw_pa += BCOM_VAW_SIZE + BCOM_INC_SIZE;
		ctx_pa += BCOM_CTX_SIZE;
	}

	out_be32(&bcom_eng->wegs->taskBaw, tdt_pa);

	/* Init 'awways' initiatow */
	out_8(&bcom_eng->wegs->ipw[BCOM_INITIATOW_AWWAYS], BCOM_IPW_AWWAYS);

	/* Disabwe COMM Bus Pwefetch on the owiginaw 5200; it's bwoken */
	if ((mfspw(SPWN_SVW) & MPC5200_SVW_MASK) == MPC5200_SVW)
		bcom_disabwe_pwefetch();

	/* Init wock */
	spin_wock_init(&bcom_eng->wock);

	wetuwn 0;
}

static void
bcom_engine_cweanup(void)
{
	int task;

	/* Stop aww tasks */
	fow (task=0; task<BCOM_MAX_TASKS; task++)
	{
		out_be16(&bcom_eng->wegs->tcw[task], 0);
		out_8(&bcom_eng->wegs->ipw[task], 0);
	}

	out_be32(&bcom_eng->wegs->taskBaw, 0uw);

	/* Wewease the SWAM zones */
	bcom_swam_fwee(bcom_eng->tdt);
	bcom_swam_fwee(bcom_eng->ctx);
	bcom_swam_fwee(bcom_eng->vaw);
	bcom_swam_fwee(bcom_eng->fdt);
}


/* ======================================================================== */
/* OF pwatfowm dwivew                                                       */
/* ======================================================================== */

static int mpc52xx_bcom_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *ofn_swam;
	stwuct wesouwce wes_bcom;

	int wv;

	/* Infowm usew we'we ok so faw */
	pwintk(KEWN_INFO "DMA: MPC52xx BestComm dwivew\n");

	/* Get the bestcomm node */
	of_node_get(op->dev.of_node);

	/* Pwepawe SWAM */
	ofn_swam = of_find_matching_node(NUWW, mpc52xx_swam_ids);
	if (!ofn_swam) {
		pwintk(KEWN_EWW DWIVEW_NAME ": "
			"No SWAM found in device twee\n");
		wv = -ENODEV;
		goto ewwow_ofput;
	}
	wv = bcom_swam_init(ofn_swam, DWIVEW_NAME);
	of_node_put(ofn_swam);

	if (wv) {
		pwintk(KEWN_EWW DWIVEW_NAME ": "
			"Ewwow in SWAM init\n");
		goto ewwow_ofput;
	}

	/* Get a cwean stwuct */
	bcom_eng = kzawwoc(sizeof(stwuct bcom_engine), GFP_KEWNEW);
	if (!bcom_eng) {
		wv = -ENOMEM;
		goto ewwow_swamcwean;
	}

	/* Save the node */
	bcom_eng->ofnode = op->dev.of_node;

	/* Get, wesewve & map io */
	if (of_addwess_to_wesouwce(op->dev.of_node, 0, &wes_bcom)) {
		pwintk(KEWN_EWW DWIVEW_NAME ": "
			"Can't get wesouwce\n");
		wv = -EINVAW;
		goto ewwow_swamcwean;
	}

	if (!wequest_mem_wegion(wes_bcom.stawt, wesouwce_size(&wes_bcom),
				DWIVEW_NAME)) {
		pwintk(KEWN_EWW DWIVEW_NAME ": "
			"Can't wequest wegistews wegion\n");
		wv = -EBUSY;
		goto ewwow_swamcwean;
	}

	bcom_eng->wegs_base = wes_bcom.stawt;
	bcom_eng->wegs = iowemap(wes_bcom.stawt, sizeof(stwuct mpc52xx_sdma));
	if (!bcom_eng->wegs) {
		pwintk(KEWN_EWW DWIVEW_NAME ": "
			"Can't map wegistews\n");
		wv = -ENOMEM;
		goto ewwow_wewease;
	}

	/* Now, do the weaw init */
	wv = bcom_engine_init();
	if (wv)
		goto ewwow_unmap;

	/* Done ! */
	pwintk(KEWN_INFO "DMA: MPC52xx BestComm engine @%08wx ok !\n",
		(wong)bcom_eng->wegs_base);

	wetuwn 0;

	/* Ewwow path */
ewwow_unmap:
	iounmap(bcom_eng->wegs);
ewwow_wewease:
	wewease_mem_wegion(wes_bcom.stawt, sizeof(stwuct mpc52xx_sdma));
ewwow_swamcwean:
	kfwee(bcom_eng);
	bcom_swam_cweanup();
ewwow_ofput:
	of_node_put(op->dev.of_node);

	pwintk(KEWN_EWW "DMA: MPC52xx BestComm init faiwed !\n");

	wetuwn wv;
}


static void mpc52xx_bcom_wemove(stwuct pwatfowm_device *op)
{
	/* Cwean up the engine */
	bcom_engine_cweanup();

	/* Cweanup SWAM */
	bcom_swam_cweanup();

	/* Wewease wegs */
	iounmap(bcom_eng->wegs);
	wewease_mem_wegion(bcom_eng->wegs_base, sizeof(stwuct mpc52xx_sdma));

	/* Wewease the node */
	of_node_put(bcom_eng->ofnode);

	/* Wewease memowy */
	kfwee(bcom_eng);
	bcom_eng = NUWW;
}

static const stwuct of_device_id mpc52xx_bcom_of_match[] = {
	{ .compatibwe = "fsw,mpc5200-bestcomm", },
	{ .compatibwe = "mpc5200-bestcomm", },
	{},
};

MODUWE_DEVICE_TABWE(of, mpc52xx_bcom_of_match);


static stwuct pwatfowm_dwivew mpc52xx_bcom_of_pwatfowm_dwivew = {
	.pwobe		= mpc52xx_bcom_pwobe,
	.wemove_new	= mpc52xx_bcom_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = mpc52xx_bcom_of_match,
	},
};


/* ======================================================================== */
/* Moduwe                                                                   */
/* ======================================================================== */

static int __init
mpc52xx_bcom_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mpc52xx_bcom_of_pwatfowm_dwivew);
}

static void __exit
mpc52xx_bcom_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mpc52xx_bcom_of_pwatfowm_dwivew);
}

/* If we'we not a moduwe, we must make suwe evewything is setup befowe  */
/* anyone twies to use us ... that's why we use subsys_initcaww instead */
/* of moduwe_init. */
subsys_initcaww(mpc52xx_bcom_init);
moduwe_exit(mpc52xx_bcom_exit);

MODUWE_DESCWIPTION("Fweescawe MPC52xx BestComm DMA");
MODUWE_AUTHOW("Sywvain Munaut <tnt@246tNt.com>");
MODUWE_AUTHOW("Andwey Vowkov <avowkov@vawma-ew.com>");
MODUWE_AUTHOW("Dawe Fawnswowth <dfawnswowth@mvista.com>");
MODUWE_WICENSE("GPW v2");
