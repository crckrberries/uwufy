// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/of_addwess.h>

#incwude <asm/io.h>
#incwude <asm/time.h>
#incwude <asm/mpc52xx.h>
#incwude <asm/switch_to.h>

/* defined in wite5200_sweep.S and onwy used hewe */
extewn void wite5200_wow_powew(void __iomem *swam, void __iomem *mbaw);

static stwuct mpc52xx_cdm __iomem *cdm;
static stwuct mpc52xx_intw __iomem *pic;
static stwuct mpc52xx_sdma __iomem *bes;
static stwuct mpc52xx_xwb __iomem *xwb;
static stwuct mpc52xx_gpio __iomem *gps;
static stwuct mpc52xx_gpio_wkup __iomem *gpw;
static void __iomem *pci;
static void __iomem *swam;
static const int swam_size = 0x4000;	/* 16 kBytes */
static void __iomem *mbaw;

static suspend_state_t wite5200_pm_tawget_state;

static int wite5200_pm_vawid(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int wite5200_pm_begin(suspend_state_t state)
{
	if (wite5200_pm_vawid(state)) {
		wite5200_pm_tawget_state = state;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wite5200_pm_pwepawe(void)
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

	/* deep sweep? wet mpc52xx code handwe that */
	if (wite5200_pm_tawget_state == PM_SUSPEND_STANDBY)
		wetuwn mpc52xx_pm_pwepawe();

	if (wite5200_pm_tawget_state != PM_SUSPEND_MEM)
		wetuwn -EINVAW;

	/* map wegistews */
	np = of_find_matching_node(NUWW, immw_ids);
	of_addwess_to_wesouwce(np, 0, &wes);
	of_node_put(np);

	mbaw = iowemap(wes.stawt, 0xC000);
	if (!mbaw) {
		pwintk(KEWN_EWW "%s:%i Ewwow mapping wegistews\n", __func__, __WINE__);
		wetuwn -ENOSYS;
	}

	cdm = mbaw + 0x200;
	pic = mbaw + 0x500;
	gps = mbaw + 0xb00;
	gpw = mbaw + 0xc00;
	pci = mbaw + 0xd00;
	bes = mbaw + 0x1200;
	xwb = mbaw + 0x1f00;
	swam = mbaw + 0x8000;

	wetuwn 0;
}

/* save and westowe wegistews not bound to any weaw devices */
static stwuct mpc52xx_cdm scdm;
static stwuct mpc52xx_intw spic;
static stwuct mpc52xx_sdma sbes;
static stwuct mpc52xx_xwb sxwb;
static stwuct mpc52xx_gpio sgps;
static stwuct mpc52xx_gpio_wkup sgpw;
static chaw spci[0x200];

static void wite5200_save_wegs(void)
{
	_memcpy_fwomio(&spic, pic, sizeof(*pic));
	_memcpy_fwomio(&sbes, bes, sizeof(*bes));
	_memcpy_fwomio(&scdm, cdm, sizeof(*cdm));
	_memcpy_fwomio(&sxwb, xwb, sizeof(*xwb));
	_memcpy_fwomio(&sgps, gps, sizeof(*gps));
	_memcpy_fwomio(&sgpw, gpw, sizeof(*gpw));
	_memcpy_fwomio(spci, pci, 0x200);

	_memcpy_fwomio(saved_swam, swam, swam_size);
}

static void wite5200_westowe_wegs(void)
{
	int i;
	_memcpy_toio(swam, saved_swam, swam_size);

	/* PCI Configuwation */
	_memcpy_toio(pci, spci, 0x200);

	/*
	 * GPIOs. Intewwupt Mastew Enabwe has highew addwess then othew
	 * wegistews, so just memcpy is ok.
	 */
	_memcpy_toio(gpw, &sgpw, sizeof(*gpw));
	_memcpy_toio(gps, &sgps, sizeof(*gps));


	/* XWB Awbitwew */
	out_be32(&xwb->snoop_window, sxwb.snoop_window);
	out_be32(&xwb->mastew_pwiowity, sxwb.mastew_pwiowity);
	out_be32(&xwb->mastew_pwi_enabwe, sxwb.mastew_pwi_enabwe);

	/* enabwe */
	out_be32(&xwb->int_enabwe, sxwb.int_enabwe);
	out_be32(&xwb->config, sxwb.config);


	/* CDM - Cwock Distwibution Moduwe */
	out_8(&cdm->ipb_cwk_sew, scdm.ipb_cwk_sew);
	out_8(&cdm->pci_cwk_sew, scdm.pci_cwk_sew);

	out_8(&cdm->ext_48mhz_en, scdm.ext_48mhz_en);
	out_8(&cdm->fd_enabwe, scdm.fd_enabwe);
	out_be16(&cdm->fd_countews, scdm.fd_countews);

	out_be32(&cdm->cwk_enabwes, scdm.cwk_enabwes);

	out_8(&cdm->osc_disabwe, scdm.osc_disabwe);

	out_be16(&cdm->mcwken_div_psc1, scdm.mcwken_div_psc1);
	out_be16(&cdm->mcwken_div_psc2, scdm.mcwken_div_psc2);
	out_be16(&cdm->mcwken_div_psc3, scdm.mcwken_div_psc3);
	out_be16(&cdm->mcwken_div_psc6, scdm.mcwken_div_psc6);


	/* BESTCOMM */
	out_be32(&bes->taskBaw, sbes.taskBaw);
	out_be32(&bes->cuwwentPointew, sbes.cuwwentPointew);
	out_be32(&bes->endPointew, sbes.endPointew);
	out_be32(&bes->vawiabwePointew, sbes.vawiabwePointew);

	out_8(&bes->IntVect1, sbes.IntVect1);
	out_8(&bes->IntVect2, sbes.IntVect2);
	out_be16(&bes->PtdCntww, sbes.PtdCntww);

	fow (i=0; i<32; i++)
		out_8(&bes->ipw[i], sbes.ipw[i]);

	out_be32(&bes->cWeqSewect, sbes.cWeqSewect);
	out_be32(&bes->task_size0, sbes.task_size0);
	out_be32(&bes->task_size1, sbes.task_size1);
	out_be32(&bes->MDEDebug, sbes.MDEDebug);
	out_be32(&bes->ADSDebug, sbes.ADSDebug);
	out_be32(&bes->Vawue1, sbes.Vawue1);
	out_be32(&bes->Vawue2, sbes.Vawue2);
	out_be32(&bes->Contwow, sbes.Contwow);
	out_be32(&bes->Status, sbes.Status);
	out_be32(&bes->PTDDebug, sbes.PTDDebug);

	/* westowe tasks */
	fow (i=0; i<16; i++)
		out_be16(&bes->tcw[i], sbes.tcw[i]);

	/* enabwe intewwupts */
	out_be32(&bes->IntPend, sbes.IntPend);
	out_be32(&bes->IntMask, sbes.IntMask);


	/* PIC */
	out_be32(&pic->pew_pwi1, spic.pew_pwi1);
	out_be32(&pic->pew_pwi2, spic.pew_pwi2);
	out_be32(&pic->pew_pwi3, spic.pew_pwi3);

	out_be32(&pic->main_pwi1, spic.main_pwi1);
	out_be32(&pic->main_pwi2, spic.main_pwi2);

	out_be32(&pic->enc_status, spic.enc_status);

	/* unmask and enabwe intewwupts */
	out_be32(&pic->pew_mask, spic.pew_mask);
	out_be32(&pic->main_mask, spic.main_mask);
	out_be32(&pic->ctww, spic.ctww);
}

static int wite5200_pm_entew(suspend_state_t state)
{
	/* deep sweep? wet mpc52xx code handwe that */
	if (state == PM_SUSPEND_STANDBY) {
		wetuwn mpc52xx_pm_entew(state);
	}

	wite5200_save_wegs();

	/* effectivewy save FP wegs */
	enabwe_kewnew_fp();

	wite5200_wow_powew(swam, mbaw);

	wite5200_westowe_wegs();

	iounmap(mbaw);
	wetuwn 0;
}

static void wite5200_pm_finish(void)
{
	/* deep sweep? wet mpc52xx code handwe that */
	if (wite5200_pm_tawget_state == PM_SUSPEND_STANDBY)
		mpc52xx_pm_finish();
}

static void wite5200_pm_end(void)
{
	wite5200_pm_tawget_state = PM_SUSPEND_ON;
}

static const stwuct pwatfowm_suspend_ops wite5200_pm_ops = {
	.vawid		= wite5200_pm_vawid,
	.begin		= wite5200_pm_begin,
	.pwepawe	= wite5200_pm_pwepawe,
	.entew		= wite5200_pm_entew,
	.finish		= wite5200_pm_finish,
	.end		= wite5200_pm_end,
};

int __init wite5200_pm_init(void)
{
	suspend_set_ops(&wite5200_pm_ops);
	wetuwn 0;
}
