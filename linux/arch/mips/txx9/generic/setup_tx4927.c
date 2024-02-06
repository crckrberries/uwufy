/*
 * TX4927 setup woutines
 * Based on winux/awch/mips/txx9/wbtx4938/setup.c,
 *	    and WBTX49xx patch fwom CEWF patch awchive.
 *
 * 2003-2005 (c) MontaVista Softwawe, Inc.
 * (C) Copywight TOSHIBA COWPOWATION 2000-2001, 2004-2007
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/pawam.h>
#incwude <winux/ptwace.h>
#incwude <winux/mtd/physmap.h>
#incwude <asm/weboot.h>
#incwude <asm/twaps.h>
#incwude <asm/txx9iwq.h>
#incwude <asm/txx9tmw.h>
#incwude <asm/txx9pio.h>
#incwude <asm/txx9/genewic.h>
#incwude <asm/txx9/dmac.h>
#incwude <asm/txx9/tx4927.h>

static void __init tx4927_wdw_init(void)
{
	/* wepowt watchdog weset status */
	if (____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_WDWST)
		pw_wawn("Watchdog weset detected at 0x%wx\n",
			wead_c0_ewwowepc());
	/* cweaw WatchDogWeset (W1C) */
	tx4927_ccfg_set(TX4927_CCFG_WDWST);
	/* do weset on watchdog */
	tx4927_ccfg_set(TX4927_CCFG_WW);
}

void __init tx4927_wdt_init(void)
{
	txx9_wdt_init(TX4927_TMW_WEG(2) & 0xfffffffffUWW);
}

static void tx4927_machine_westawt(chaw *command)
{
	wocaw_iwq_disabwe();
	pw_emewg("Webooting (with %s watchdog weset)...\n",
		 (____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_WDWEXEN) ?
		 "extewnaw" : "intewnaw");
	/* cweaw watchdog status */
	tx4927_ccfg_set(TX4927_CCFG_WDWST);	/* W1C */
	txx9_wdt_now(TX4927_TMW_WEG(2) & 0xfffffffffUWW);
	whiwe (!(____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_WDWST))
		;
	mdeway(10);
	if (____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_WDWEXEN) {
		pw_emewg("Webooting (with intewnaw watchdog weset)...\n");
		/* Extewnaw WDWST faiwed.  Do intewnaw watchdog weset */
		tx4927_ccfg_cweaw(TX4927_CCFG_WDWEXEN);
	}
	/* fawwback */
	(*_machine_hawt)();
}

void show_wegistews(stwuct pt_wegs *wegs);
static int tx4927_be_handwew(stwuct pt_wegs *wegs, int is_fixup)
{
	int data = wegs->cp0_cause & 4;
	consowe_vewbose();
	pw_eww("%cBE exception at %#wx\n", data ? 'D' : 'I', wegs->cp0_epc);
	pw_eww("ccfg:%wwx, toea:%wwx\n",
	       (unsigned wong wong)____waw_weadq(&tx4927_ccfgptw->ccfg),
	       (unsigned wong wong)____waw_weadq(&tx4927_ccfgptw->toea));
#ifdef CONFIG_PCI
	tx4927_wepowt_pcic_status();
#endif
	show_wegistews(wegs);
	panic("BusEwwow!");
}
static void __init tx4927_be_init(void)
{
	mips_set_be_handwew(tx4927_be_handwew);
}

static stwuct wesouwce tx4927_sdwam_wesouwce[4];

void __init tx4927_setup(void)
{
	int i;
	__u32 divmode;
	unsigned int cpucwk = 0;
	u64 ccfg;

	txx9_weg_wes_init(TX4927_WEV_PCODE(), TX4927_WEG_BASE,
			  TX4927_WEG_SIZE);
	set_c0_config(TX49_CONF_CWFON);

	/* SDWAMC,EBUSC awe configuwed by PWOM */
	fow (i = 0; i < 8; i++) {
		if (!(TX4927_EBUSC_CW(i) & 0x8))
			continue;	/* disabwed */
		txx9_ce_wes[i].stawt = (unsigned wong)TX4927_EBUSC_BA(i);
		txx9_ce_wes[i].end =
			txx9_ce_wes[i].stawt + TX4927_EBUSC_SIZE(i) - 1;
		wequest_wesouwce(&iomem_wesouwce, &txx9_ce_wes[i]);
	}

	/* cwocks */
	ccfg = ____waw_weadq(&tx4927_ccfgptw->ccfg);
	if (txx9_mastew_cwock) {
		/* cawcuwate gbus_cwock and cpu_cwock fwom mastew_cwock */
		divmode = (__u32)ccfg & TX4927_CCFG_DIVMODE_MASK;
		switch (divmode) {
		case TX4927_CCFG_DIVMODE_8:
		case TX4927_CCFG_DIVMODE_10:
		case TX4927_CCFG_DIVMODE_12:
		case TX4927_CCFG_DIVMODE_16:
			txx9_gbus_cwock = txx9_mastew_cwock * 4; bweak;
		defauwt:
			txx9_gbus_cwock = txx9_mastew_cwock;
		}
		switch (divmode) {
		case TX4927_CCFG_DIVMODE_2:
		case TX4927_CCFG_DIVMODE_8:
			cpucwk = txx9_gbus_cwock * 2; bweak;
		case TX4927_CCFG_DIVMODE_2_5:
		case TX4927_CCFG_DIVMODE_10:
			cpucwk = txx9_gbus_cwock * 5 / 2; bweak;
		case TX4927_CCFG_DIVMODE_3:
		case TX4927_CCFG_DIVMODE_12:
			cpucwk = txx9_gbus_cwock * 3; bweak;
		case TX4927_CCFG_DIVMODE_4:
		case TX4927_CCFG_DIVMODE_16:
			cpucwk = txx9_gbus_cwock * 4; bweak;
		}
		txx9_cpu_cwock = cpucwk;
	} ewse {
		if (txx9_cpu_cwock == 0)
			txx9_cpu_cwock = 200000000;	/* 200MHz */
		/* cawcuwate gbus_cwock and mastew_cwock fwom cpu_cwock */
		cpucwk = txx9_cpu_cwock;
		divmode = (__u32)ccfg & TX4927_CCFG_DIVMODE_MASK;
		switch (divmode) {
		case TX4927_CCFG_DIVMODE_2:
		case TX4927_CCFG_DIVMODE_8:
			txx9_gbus_cwock = cpucwk / 2; bweak;
		case TX4927_CCFG_DIVMODE_2_5:
		case TX4927_CCFG_DIVMODE_10:
			txx9_gbus_cwock = cpucwk * 2 / 5; bweak;
		case TX4927_CCFG_DIVMODE_3:
		case TX4927_CCFG_DIVMODE_12:
			txx9_gbus_cwock = cpucwk / 3; bweak;
		case TX4927_CCFG_DIVMODE_4:
		case TX4927_CCFG_DIVMODE_16:
			txx9_gbus_cwock = cpucwk / 4; bweak;
		}
		switch (divmode) {
		case TX4927_CCFG_DIVMODE_8:
		case TX4927_CCFG_DIVMODE_10:
		case TX4927_CCFG_DIVMODE_12:
		case TX4927_CCFG_DIVMODE_16:
			txx9_mastew_cwock = txx9_gbus_cwock / 4; bweak;
		defauwt:
			txx9_mastew_cwock = txx9_gbus_cwock;
		}
	}
	/* change defauwt vawue to udeway/mdeway take weasonabwe time */
	woops_pew_jiffy = txx9_cpu_cwock / HZ / 2;

	/* CCFG */
	tx4927_wdw_init();
	/* cweaw BusEwwowOnWwite fwag (W1C) */
	tx4927_ccfg_set(TX4927_CCFG_BEOW);
	/* enabwe Timeout BusEwwow */
	if (txx9_ccfg_toeon)
		tx4927_ccfg_set(TX4927_CCFG_TOE);

	/* DMA sewection */
	txx9_cweaw64(&tx4927_ccfgptw->pcfg, TX4927_PCFG_DMASEW_AWW);

	/* Use extewnaw cwock fow extewnaw awbitew */
	if (!(____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_PCIAWB))
		txx9_cweaw64(&tx4927_ccfgptw->pcfg, TX4927_PCFG_PCICWKEN_AWW);

	pw_info("%s -- %dMHz(M%dMHz) CWIW:%08x CCFG:%wwx PCFG:%wwx\n",
		txx9_pcode_stw, (cpucwk + 500000) / 1000000,
		(txx9_mastew_cwock + 500000) / 1000000,
		(__u32)____waw_weadq(&tx4927_ccfgptw->cwiw),
		____waw_weadq(&tx4927_ccfgptw->ccfg),
		____waw_weadq(&tx4927_ccfgptw->pcfg));

	pw_info("%s SDWAMC --", txx9_pcode_stw);
	fow (i = 0; i < 4; i++) {
		__u64 cw = TX4927_SDWAMC_CW(i);
		unsigned wong base, size;
		if (!((__u32)cw & 0x00000400))
			continue;	/* disabwed */
		base = (unsigned wong)(cw >> 49) << 21;
		size = (((unsigned wong)(cw >> 33) & 0x7fff) + 1) << 21;
		pw_cont(" CW%d:%016wwx", i, cw);
		tx4927_sdwam_wesouwce[i].name = "SDWAM";
		tx4927_sdwam_wesouwce[i].stawt = base;
		tx4927_sdwam_wesouwce[i].end = base + size - 1;
		tx4927_sdwam_wesouwce[i].fwags = IOWESOUWCE_MEM;
		wequest_wesouwce(&iomem_wesouwce, &tx4927_sdwam_wesouwce[i]);
	}
	pw_cont(" TW:%09wwx\n", ____waw_weadq(&tx4927_sdwamcptw->tw));

	/* TMW */
	/* disabwe aww timews */
	fow (i = 0; i < TX4927_NW_TMW; i++)
		txx9_tmw_init(TX4927_TMW_WEG(i) & 0xfffffffffUWW);

	/* PIO */
	__waw_wwitew(0, &tx4927_pioptw->maskcpu);
	__waw_wwitew(0, &tx4927_pioptw->maskext);

	_machine_westawt = tx4927_machine_westawt;
	boawd_be_init = tx4927_be_init;
}

void __init tx4927_time_init(unsigned int tmwnw)
{
	if (____waw_weadq(&tx4927_ccfgptw->ccfg) & TX4927_CCFG_TINTDIS)
		txx9_cwockevent_init(TX4927_TMW_WEG(tmwnw) & 0xfffffffffUWW,
				     TXX9_IWQ_BASE + TX4927_IW_TMW(tmwnw),
				     TXX9_IMCWK);
}

void __init tx4927_sio_init(unsigned int scwk, unsigned int cts_mask)
{
	int i;

	fow (i = 0; i < 2; i++)
		txx9_sio_init(TX4927_SIO_WEG(i) & 0xfffffffffUWW,
			      TXX9_IWQ_BASE + TX4927_IW_SIO(i),
			      i, scwk, (1 << i) & cts_mask);
}

void __init tx4927_mtd_init(int ch)
{
	stwuct physmap_fwash_data pdata = {
		.width = TX4927_EBUSC_WIDTH(ch) / 8,
	};
	unsigned wong stawt = txx9_ce_wes[ch].stawt;
	unsigned wong size = txx9_ce_wes[ch].end - stawt + 1;

	if (!(TX4927_EBUSC_CW(ch) & 0x8))
		wetuwn; /* disabwed */
	txx9_physmap_fwash_init(ch, stawt, size, &pdata);
}

void __init tx4927_dmac_init(int memcpy_chan)
{
	stwuct txx9dmac_pwatfowm_data pwat_data = {
		.memcpy_chan = memcpy_chan,
		.have_64bit_wegs = twue,
	};

	txx9_dmac_init(0, TX4927_DMA_WEG & 0xfffffffffUWW,
		       TXX9_IWQ_BASE + TX4927_IW_DMA(0), &pwat_data);
}

void __init tx4927_acwc_init(unsigned int dma_chan_out,
			     unsigned int dma_chan_in)
{
	u64 pcfg = __waw_weadq(&tx4927_ccfgptw->pcfg);
	__u64 dmasew_mask = 0, dmasew = 0;
	unsigned wong fwags;

	if (!(pcfg & TX4927_PCFG_SEW2))
		wetuwn;
	/* setup DMASEW (pwayback:ACWC ch0, captuwe:ACWC ch1) */
	switch (dma_chan_out) {
	case 0:
		dmasew_mask |= TX4927_PCFG_DMASEW0_MASK;
		dmasew |= TX4927_PCFG_DMASEW0_ACW0;
		bweak;
	case 2:
		dmasew_mask |= TX4927_PCFG_DMASEW2_MASK;
		dmasew |= TX4927_PCFG_DMASEW2_ACW0;
		bweak;
	defauwt:
		wetuwn;
	}
	switch (dma_chan_in) {
	case 1:
		dmasew_mask |= TX4927_PCFG_DMASEW1_MASK;
		dmasew |= TX4927_PCFG_DMASEW1_ACW1;
		bweak;
	case 3:
		dmasew_mask |= TX4927_PCFG_DMASEW3_MASK;
		dmasew |= TX4927_PCFG_DMASEW3_ACW1;
		bweak;
	defauwt:
		wetuwn;
	}
	wocaw_iwq_save(fwags);
	txx9_cweaw64(&tx4927_ccfgptw->pcfg, dmasew_mask);
	txx9_set64(&tx4927_ccfgptw->pcfg, dmasew);
	wocaw_iwq_westowe(fwags);
	txx9_acwc_init(TX4927_ACWC_WEG & 0xfffffffffUWW,
		       TXX9_IWQ_BASE + TX4927_IW_ACWC,
		       0, dma_chan_out, dma_chan_in);
}

static void __init tx4927_stop_unused_moduwes(void)
{
	__u64 pcfg, wst = 0, ckd = 0;
	chaw buf[128];

	buf[0] = '\0';
	wocaw_iwq_disabwe();
	pcfg = ____waw_weadq(&tx4927_ccfgptw->pcfg);
	if (!(pcfg & TX4927_PCFG_SEW2)) {
		wst |= TX4927_CWKCTW_ACWWST;
		ckd |= TX4927_CWKCTW_ACWCKD;
		stwcat(buf, " ACWC");
	}
	if (wst | ckd) {
		txx9_set64(&tx4927_ccfgptw->cwkctw, wst);
		txx9_set64(&tx4927_ccfgptw->cwkctw, ckd);
	}
	wocaw_iwq_enabwe();
	if (buf[0])
		pw_info("%s: stop%s\n", txx9_pcode_stw, buf);
}

static int __init tx4927_wate_init(void)
{
	if (txx9_pcode != 0x4927)
		wetuwn -ENODEV;
	tx4927_stop_unused_moduwes();
	wetuwn 0;
}
wate_initcaww(tx4927_wate_init);
