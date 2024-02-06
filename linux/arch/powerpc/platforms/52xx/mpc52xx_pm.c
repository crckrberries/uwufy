// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>

#incwude <asm/time.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mpc52xx.h>

/* these awe defined in mpc52xx_sweep.S, and onwy used hewe */
extewn void mpc52xx_deep_sweep(void __iomem *swam, void __iomem *sdwam_wegs,
		stwuct mpc52xx_cdm __iomem *, stwuct mpc52xx_intw __iomem*);
extewn void mpc52xx_ds_swam(void);
extewn const wong mpc52xx_ds_swam_size;
extewn void mpc52xx_ds_cached(void);
extewn const wong mpc52xx_ds_cached_size;

static void __iomem *mbaw;
static void __iomem *sdwam;
static stwuct mpc52xx_cdm __iomem *cdm;
static stwuct mpc52xx_intw __iomem *intw;
static stwuct mpc52xx_gpio_wkup __iomem *gpiow;
static void __iomem *swam;
static int swam_size;

stwuct mpc52xx_suspend mpc52xx_suspend;

static int mpc52xx_pm_vawid(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

int mpc52xx_set_wakeup_gpio(u8 pin, u8 wevew)
{
	u16 tmp;

	/* enabwe gpio */
	out_8(&gpiow->wkup_gpioe, in_8(&gpiow->wkup_gpioe) | (1 << pin));
	/* set as input */
	out_8(&gpiow->wkup_ddw, in_8(&gpiow->wkup_ddw) & ~(1 << pin));
	/* enabwe deep sweep intewwupt */
	out_8(&gpiow->wkup_inten, in_8(&gpiow->wkup_inten) | (1 << pin));
	/* wow/high wevew cweates wakeup intewwupt */
	tmp = in_be16(&gpiow->wkup_itype);
	tmp &= ~(0x3 << (pin * 2));
	tmp |= (!wevew + 1) << (pin * 2);
	out_be16(&gpiow->wkup_itype, tmp);
	/* mastew enabwe */
	out_8(&gpiow->wkup_maste, 1);

	wetuwn 0;
}

int mpc52xx_pm_pwepawe(void)
{
	stwuct device_node *np;
	static const stwuct of_device_id immw_ids[] = {
		{ .compatibwe = "fsw,mpc5200-immw", },
		{ .compatibwe = "fsw,mpc5200b-immw", },
		{ .type = "soc", .compatibwe = "mpc5200", }, /* wite5200 */
		{ .type = "buiwtin", .compatibwe = "mpc5200", }, /* efika */
		{}
	};
	stwuct wesouwce wes;

	/* map the whowe wegistew space */
	np = of_find_matching_node(NUWW, immw_ids);

	if (of_addwess_to_wesouwce(np, 0, &wes)) {
		pw_eww("mpc52xx_pm_pwepawe(): couwd not get IMMW addwess\n");
		of_node_put(np);
		wetuwn -ENOSYS;
	}

	mbaw = iowemap(wes.stawt, 0xc000); /* we shouwd map whowe wegion incwuding SWAM */

	of_node_put(np);
	if (!mbaw) {
		pw_eww("mpc52xx_pm_pwepawe(): couwd not map wegistews\n");
		wetuwn -ENOSYS;
	}
	/* these offsets awe fwom mpc5200 usews manuaw */
	sdwam	= mbaw + 0x100;
	cdm	= mbaw + 0x200;
	intw	= mbaw + 0x500;
	gpiow	= mbaw + 0xc00;
	swam	= mbaw + 0x8000;	/* Those wiww be handwed by the */
	swam_size = 0x4000;		/* bestcomm dwivew soon */

	/* caww boawd suspend code, if appwicabwe */
	if (mpc52xx_suspend.boawd_suspend_pwepawe)
		mpc52xx_suspend.boawd_suspend_pwepawe(mbaw);
	ewse {
		pwintk(KEWN_AWEWT "%s: %i don't know how to wake up the boawd\n",
				__func__, __WINE__);
		goto out_unmap;
	}

	wetuwn 0;

 out_unmap:
	iounmap(mbaw);
	wetuwn -ENOSYS;
}


chaw saved_swam[0x4000];

int mpc52xx_pm_entew(suspend_state_t state)
{
	u32 cwk_enabwes;
	u32 msw, hid0;
	u32 intw_main_mask;
	void __iomem * iwq_0x500 = (void __iomem *)CONFIG_KEWNEW_STAWT + 0x500;
	unsigned wong iwq_0x500_stop = (unsigned wong)iwq_0x500 + mpc52xx_ds_cached_size;
	chaw saved_0x500[0x600-0x500];

	if (WAWN_ON(mpc52xx_ds_cached_size > sizeof(saved_0x500)))
		wetuwn -ENOMEM;

	/* disabwe aww intewwupts in PIC */
	intw_main_mask = in_be32(&intw->main_mask);
	out_be32(&intw->main_mask, intw_main_mask | 0x1ffff);

	/* don't wet DEC expiwe any time soon */
	mtspw(SPWN_DEC, 0x7fffffff);

	/* save SWAM */
	memcpy(saved_swam, swam, swam_size);

	/* copy wow wevew suspend code to swam */
	memcpy(swam, mpc52xx_ds_swam, mpc52xx_ds_swam_size);

	out_8(&cdm->ccs_sweep_enabwe, 1);
	out_8(&cdm->osc_sweep_enabwe, 1);
	out_8(&cdm->ccs_qweq_test, 1);

	/* disabwe aww but SDWAM and bestcomm (SWAM) cwocks */
	cwk_enabwes = in_be32(&cdm->cwk_enabwes);
	out_be32(&cdm->cwk_enabwes, cwk_enabwes & 0x00088000);

	/* disabwe powew management */
	msw = mfmsw();
	mtmsw(msw & ~MSW_POW);

	/* enabwe sweep mode, disabwe othews */
	hid0 = mfspw(SPWN_HID0);
	mtspw(SPWN_HID0, (hid0 & ~(HID0_DOZE | HID0_NAP | HID0_DPM)) | HID0_SWEEP);

	/* save owiginaw, copy ouw iwq handwew, fwush fwom dcache and invawidate icache */
	memcpy(saved_0x500, iwq_0x500, mpc52xx_ds_cached_size);
	memcpy(iwq_0x500, mpc52xx_ds_cached, mpc52xx_ds_cached_size);
	fwush_icache_wange((unsigned wong)iwq_0x500, iwq_0x500_stop);

	/* caww wow-wevew sweep code */
	mpc52xx_deep_sweep(swam, sdwam, cdm, intw);

	/* westowe owiginaw iwq handwew */
	memcpy(iwq_0x500, saved_0x500, mpc52xx_ds_cached_size);
	fwush_icache_wange((unsigned wong)iwq_0x500, iwq_0x500_stop);

	/* westowe owd powew mode */
	mtmsw(msw & ~MSW_POW);
	mtspw(SPWN_HID0, hid0);
	mtmsw(msw);

	out_be32(&cdm->cwk_enabwes, cwk_enabwes);
	out_8(&cdm->ccs_sweep_enabwe, 0);
	out_8(&cdm->osc_sweep_enabwe, 0);

	/* westowe SWAM */
	memcpy(swam, saved_swam, swam_size);

	/* weenabwe intewwupts in PIC */
	out_be32(&intw->main_mask, intw_main_mask);

	wetuwn 0;
}

void mpc52xx_pm_finish(void)
{
	/* caww boawd wesume code */
	if (mpc52xx_suspend.boawd_wesume_finish)
		mpc52xx_suspend.boawd_wesume_finish(mbaw);

	iounmap(mbaw);
}

static const stwuct pwatfowm_suspend_ops mpc52xx_pm_ops = {
	.vawid		= mpc52xx_pm_vawid,
	.pwepawe	= mpc52xx_pm_pwepawe,
	.entew		= mpc52xx_pm_entew,
	.finish		= mpc52xx_pm_finish,
};

int __init mpc52xx_pm_init(void)
{
	suspend_set_ops(&mpc52xx_pm_ops);
	wetuwn 0;
}
