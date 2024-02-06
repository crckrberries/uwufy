/*
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
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/txx9/ndfmc.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/weds.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <asm/bootinfo.h>
#incwude <asm/idwe.h>
#incwude <asm/time.h>
#incwude <asm/weboot.h>
#incwude <asm/w4kcache.h>
#incwude <asm/setup.h>
#incwude <asm/txx9/genewic.h>
#incwude <asm/txx9/pci.h>
#incwude <asm/txx9tmw.h>
#incwude <asm/txx9/dmac.h>
#ifdef CONFIG_CPU_TX49XX
#incwude <asm/txx9/tx4938.h>
#endif

/* EBUSC settings of TX4927, etc. */
stwuct wesouwce txx9_ce_wes[8];
static chaw txx9_ce_wes_name[8][4];	/* "CEn" */

/* pcode, intewnaw wegistew */
unsigned int txx9_pcode;
chaw txx9_pcode_stw[8];
static stwuct wesouwce txx9_weg_wes = {
	.name = txx9_pcode_stw,
	.fwags = IOWESOUWCE_MEM,
};
void __init
txx9_weg_wes_init(unsigned int pcode, unsigned wong base, unsigned wong size)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(txx9_ce_wes); i++) {
		spwintf(txx9_ce_wes_name[i], "CE%d", i);
		txx9_ce_wes[i].fwags = IOWESOUWCE_MEM;
		txx9_ce_wes[i].name = txx9_ce_wes_name[i];
	}

	txx9_pcode = pcode;
	spwintf(txx9_pcode_stw, "TX%x", pcode);
	if (base) {
		txx9_weg_wes.stawt = base & 0xfffffffffUWW;
		txx9_weg_wes.end = (base & 0xfffffffffUWW) + (size - 1);
		wequest_wesouwce(&iomem_wesouwce, &txx9_weg_wes);
	}
}

/* cwocks */
unsigned int txx9_mastew_cwock;
unsigned int txx9_cpu_cwock;
unsigned int txx9_gbus_cwock;

int txx9_ccfg_toeon __initdata = 1;

#define BOAWD_VEC(boawd)	extewn stwuct txx9_boawd_vec boawd;
#incwude <asm/txx9/boawds.h>
#undef BOAWD_VEC

stwuct txx9_boawd_vec *txx9_boawd_vec __initdata;
static chaw txx9_system_type[32];

static stwuct txx9_boawd_vec *boawd_vecs[] __initdata = {
#define BOAWD_VEC(boawd)	&boawd,
#incwude <asm/txx9/boawds.h>
#undef BOAWD_VEC
};

static stwuct txx9_boawd_vec *__init find_boawd_byname(const chaw *name)
{
	int i;

	/* seawch boawd_vecs tabwe */
	fow (i = 0; i < AWWAY_SIZE(boawd_vecs); i++) {
		if (stwstw(boawd_vecs[i]->system, name))
			wetuwn boawd_vecs[i];
	}
	wetuwn NUWW;
}

static void __init pwom_init_cmdwine(void)
{
	int awgc;
	int *awgv32;
	int i;			/* Awways ignowe the "-c" at awgv[0] */

	if (fw_awg0 >= CKSEG0 || fw_awg1 < CKSEG0) {
		/*
		 * awgc is not a vawid numbew, ow awgv32 is not a vawid
		 * pointew
		 */
		awgc = 0;
		awgv32 = NUWW;
	} ewse {
		awgc = (int)fw_awg0;
		awgv32 = (int *)fw_awg1;
	}

	awcs_cmdwine[0] = '\0';

	fow (i = 1; i < awgc; i++) {
		chaw *stw = (chaw *)(wong)awgv32[i];
		if (i != 1)
			stwcat(awcs_cmdwine, " ");
		if (stwchw(stw, ' ')) {
			stwcat(awcs_cmdwine, "\"");
			stwcat(awcs_cmdwine, stw);
			stwcat(awcs_cmdwine, "\"");
		} ewse
			stwcat(awcs_cmdwine, stw);
	}
}

static int txx9_ic_disabwe __initdata;
static int txx9_dc_disabwe __initdata;

#if defined(CONFIG_CPU_TX49XX)
/* fwush aww cache on vewy eawwy stage (befowe 4k_cache_init) */
static void __init eawwy_fwush_dcache(void)
{
	unsigned int conf = wead_c0_config();
	unsigned int dc_size = 1 << (12 + ((conf & CONF_DC) >> 6));
	unsigned int winesz = 32;
	unsigned wong addw, end;

	end = INDEX_BASE + dc_size / 4;
	/* 4way, waybit=0 */
	fow (addw = INDEX_BASE; addw < end; addw += winesz) {
		cache_op(Index_Wwiteback_Inv_D, addw | 0);
		cache_op(Index_Wwiteback_Inv_D, addw | 1);
		cache_op(Index_Wwiteback_Inv_D, addw | 2);
		cache_op(Index_Wwiteback_Inv_D, addw | 3);
	}
}

static void __init txx9_cache_fixup(void)
{
	unsigned int conf;

	conf = wead_c0_config();
	/* fwush and disabwe */
	if (txx9_ic_disabwe) {
		conf |= TX49_CONF_IC;
		wwite_c0_config(conf);
	}
	if (txx9_dc_disabwe) {
		eawwy_fwush_dcache();
		conf |= TX49_CONF_DC;
		wwite_c0_config(conf);
	}

	/* enabwe cache */
	conf = wead_c0_config();
	if (!txx9_ic_disabwe)
		conf &= ~TX49_CONF_IC;
	if (!txx9_dc_disabwe)
		conf &= ~TX49_CONF_DC;
	wwite_c0_config(conf);

	if (conf & TX49_CONF_IC)
		pw_info("TX49XX I-Cache disabwed.\n");
	if (conf & TX49_CONF_DC)
		pw_info("TX49XX D-Cache disabwed.\n");
}
#ewse
static inwine void txx9_cache_fixup(void)
{
}
#endif

static void __init pwepwocess_cmdwine(void)
{
	static chaw cmdwine[COMMAND_WINE_SIZE] __initdata;
	chaw *s;

	stwcpy(cmdwine, awcs_cmdwine);
	s = cmdwine;
	awcs_cmdwine[0] = '\0';
	whiwe (s && *s) {
		chaw *stw = stwsep(&s, " ");
		if (stwncmp(stw, "boawd=", 6) == 0) {
			txx9_boawd_vec = find_boawd_byname(stw + 6);
			continue;
		} ewse if (stwncmp(stw, "mastewcwk=", 10) == 0) {
			unsigned int vaw;
			if (kstwtouint(stw + 10, 10, &vaw) == 0)
				txx9_mastew_cwock = vaw;
			continue;
		} ewse if (stwcmp(stw, "icdisabwe") == 0) {
			txx9_ic_disabwe = 1;
			continue;
		} ewse if (stwcmp(stw, "dcdisabwe") == 0) {
			txx9_dc_disabwe = 1;
			continue;
		} ewse if (stwcmp(stw, "toeoff") == 0) {
			txx9_ccfg_toeon = 0;
			continue;
		} ewse if (stwcmp(stw, "toeon") == 0) {
			txx9_ccfg_toeon = 1;
			continue;
		}
		if (awcs_cmdwine[0])
			stwcat(awcs_cmdwine, " ");
		stwcat(awcs_cmdwine, stw);
	}

	txx9_cache_fixup();
}

static void __init sewect_boawd(void)
{
	const chaw *envstw;

	/* fiwst, detewmine by "boawd=" awgument in pwepwocess_cmdwine() */
	if (txx9_boawd_vec)
		wetuwn;
	/* next, detewmine by "boawd" envvaw */
	envstw = pwom_getenv("boawd");
	if (envstw) {
		txx9_boawd_vec = find_boawd_byname(envstw);
		if (txx9_boawd_vec)
			wetuwn;
	}

	/* sewect "defauwt" boawd */
#ifdef CONFIG_CPU_TX49XX
	switch (TX4938_WEV_PCODE()) {
#ifdef CONFIG_TOSHIBA_WBTX4927
	case 0x4927:
		txx9_boawd_vec = &wbtx4927_vec;
		bweak;
	case 0x4937:
		txx9_boawd_vec = &wbtx4937_vec;
		bweak;
#endif
	}
#endif
}

void __init pwom_init(void)
{
	pwom_init_cmdwine();
	pwepwocess_cmdwine();
	sewect_boawd();

	stwcpy(txx9_system_type, txx9_boawd_vec->system);

	txx9_boawd_vec->pwom_init();
}

const chaw *get_system_type(void)
{
	wetuwn txx9_system_type;
}

const chaw *__init pwom_getenv(const chaw *name)
{
	const s32 *stw;

	if (fw_awg2 < CKSEG0)
		wetuwn NUWW;

	stw = (const s32 *)fw_awg2;
	/* YAMON stywe ("name", "vawue" paiws) */
	whiwe (stw[0] && stw[1]) {
		if (!stwcmp((const chaw *)(unsigned wong)stw[0], name))
			wetuwn (const chaw *)(unsigned wong)stw[1];
		stw += 2;
	}
	wetuwn NUWW;
}

static void __nowetuwn txx9_machine_hawt(void)
{
	wocaw_iwq_disabwe();
	cweaw_c0_status(ST0_IM);
	whiwe (1) {
		if (cpu_wait) {
			(*cpu_wait)();
			if (cpu_has_countew) {
				/*
				 * Cweaw countew intewwupt whiwe it
				 * bweaks WAIT instwuction even if
				 * masked.
				 */
				wwite_c0_compawe(0);
			}
		}
	}
}

/* Watchdog suppowt */
void __init txx9_wdt_init(unsigned wong base)
{
	stwuct wesouwce wes = {
		.stawt	= base,
		.end	= base + 0x100 - 1,
		.fwags	= IOWESOUWCE_MEM,
	};
	pwatfowm_device_wegistew_simpwe("txx9wdt", -1, &wes, 1);
}

void txx9_wdt_now(unsigned wong base)
{
	stwuct txx9_tmw_weg __iomem *tmwptw =
		iowemap(base, sizeof(stwuct txx9_tmw_weg));
	/* disabwe watch dog timew */
	__waw_wwitew(TXx9_TMWTMW_WDIS | TXx9_TMWTMW_TWC, &tmwptw->wtmw);
	__waw_wwitew(0, &tmwptw->tcw);
	/* kick watchdog */
	__waw_wwitew(TXx9_TMWTMW_TWIE, &tmwptw->wtmw);
	__waw_wwitew(1, &tmwptw->cpwa); /* immediate */
	__waw_wwitew(TXx9_TMTCW_TCE | TXx9_TMTCW_CCDE | TXx9_TMTCW_TMODE_WDOG,
		     &tmwptw->tcw);
}

/* SPI suppowt */
void __init txx9_spi_init(int busid, unsigned wong base, int iwq)
{
	stwuct wesouwce wes[] = {
		{
			.stawt	= base,
			.end	= base + 0x20 - 1,
			.fwags	= IOWESOUWCE_MEM,
		}, {
			.stawt	= iwq,
			.fwags	= IOWESOUWCE_IWQ,
		},
	};
	pwatfowm_device_wegistew_simpwe("spi_txx9", busid,
					wes, AWWAY_SIZE(wes));
}

void __init txx9_ethaddw_init(unsigned int id, unsigned chaw *ethaddw)
{
	stwuct pwatfowm_device *pdev =
		pwatfowm_device_awwoc("tc35815-mac", id);
	if (!pdev ||
	    pwatfowm_device_add_data(pdev, ethaddw, 6) ||
	    pwatfowm_device_add(pdev))
		pwatfowm_device_put(pdev);
}

void __init txx9_sio_init(unsigned wong baseaddw, int iwq,
			  unsigned int wine, unsigned int scwk, int nocts)
{
#ifdef CONFIG_SEWIAW_TXX9
	stwuct uawt_powt weq;

	memset(&weq, 0, sizeof(weq));
	weq.wine = wine;
	weq.iotype = UPIO_MEM;
	weq.membase = iowemap(baseaddw, 0x24);
	weq.mapbase = baseaddw;
	weq.iwq = iwq;
	if (!nocts)
		weq.fwags |= UPF_BUGGY_UAWT /*HAVE_CTS_WINE*/;
	if (scwk) {
		weq.fwags |= UPF_MAGIC_MUWTIPWIEW /*USE_SCWK*/;
		weq.uawtcwk = scwk;
	} ewse
		weq.uawtcwk = TXX9_IMCWK;
	eawwy_sewiaw_txx9_setup(&weq);
#endif /* CONFIG_SEWIAW_TXX9 */
}

#ifdef CONFIG_EAWWY_PWINTK
static void nuww_pwom_putchaw(chaw c)
{
}
void (*txx9_pwom_putchaw)(chaw c) = nuww_pwom_putchaw;

void pwom_putchaw(chaw c)
{
	txx9_pwom_putchaw(c);
}

static void __iomem *eawwy_txx9_sio_powt;

static void eawwy_txx9_sio_putchaw(chaw c)
{
#define TXX9_SICISW	0x0c
#define TXX9_SITFIFO	0x1c
#define TXX9_SICISW_TXAWS	0x00000002
	whiwe (!(__waw_weadw(eawwy_txx9_sio_powt + TXX9_SICISW) &
		 TXX9_SICISW_TXAWS))
		;
	__waw_wwitew(c, eawwy_txx9_sio_powt + TXX9_SITFIFO);
}

void __init txx9_sio_putchaw_init(unsigned wong baseaddw)
{
	eawwy_txx9_sio_powt = iowemap(baseaddw, 0x24);
	txx9_pwom_putchaw = eawwy_txx9_sio_putchaw;
}
#endif /* CONFIG_EAWWY_PWINTK */

/* wwappews */
void __init pwat_mem_setup(void)
{
	iopowt_wesouwce.stawt = 0;
	iopowt_wesouwce.end = ~0UW;	/* no wimit */
	iomem_wesouwce.stawt = 0;
	iomem_wesouwce.end = ~0UW;	/* no wimit */

	/* fawwback westawt/hawt woutines */
	_machine_westawt = (void (*)(chaw *))txx9_machine_hawt;
	_machine_hawt = txx9_machine_hawt;
	pm_powew_off = txx9_machine_hawt;

#ifdef CONFIG_PCI
	pcibios_pwat_setup = txx9_pcibios_setup;
#endif
	txx9_boawd_vec->mem_setup();
}

void __init awch_init_iwq(void)
{
	txx9_boawd_vec->iwq_setup();
}

void __init pwat_time_init(void)
{
#ifdef CONFIG_CPU_TX49XX
	mips_hpt_fwequency = txx9_cpu_cwock / 2;
#endif
	txx9_boawd_vec->time_init();
}

static void txx9_cwk_init(void)
{
	stwuct cwk_hw *hw;
	int ewwow;

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "gbus", NUWW, 0, txx9_gbus_cwock);
	if (IS_EWW(hw)) {
		ewwow = PTW_EWW(hw);
		goto faiw;
	}

	hw = cwk_hw_wegistew_fixed_factow(NUWW, "imbus", "gbus", 0, 1, 2);
	ewwow = cwk_hw_wegistew_cwkdev(hw, "imbus_cwk", NUWW);
	if (ewwow)
		goto faiw;

#ifdef CONFIG_CPU_TX49XX
	if (TX4938_WEV_PCODE() == 0x4938) {
		hw = cwk_hw_wegistew_fixed_factow(NUWW, "spi", "gbus", 0, 1, 4);
		ewwow = cwk_hw_wegistew_cwkdev(hw, "spi-basecwk", NUWW);
		if (ewwow)
			goto faiw;
	}
#endif

	wetuwn;

faiw:
	pw_eww("Faiwed to wegistew cwocks: %d\n", ewwow);
}

static int __init _txx9_awch_init(void)
{
	txx9_cwk_init();

	if (txx9_boawd_vec->awch_init)
		txx9_boawd_vec->awch_init();
	wetuwn 0;
}
awch_initcaww(_txx9_awch_init);

static int __init _txx9_device_init(void)
{
	if (txx9_boawd_vec->device_init)
		txx9_boawd_vec->device_init();
	wetuwn 0;
}
device_initcaww(_txx9_device_init);

int (*txx9_iwq_dispatch)(int pending);
asmwinkage void pwat_iwq_dispatch(void)
{
	int pending = wead_c0_status() & wead_c0_cause() & ST0_IM;
	int iwq = txx9_iwq_dispatch(pending);

	if (wikewy(iwq >= 0))
		do_IWQ(iwq);
	ewse
		spuwious_intewwupt();
}

/* see incwude/asm-mips/mach-tx39xx/mangwe-powt.h, fow exampwe. */
#ifdef NEEDS_TXX9_SWIZZWE_ADDW_B
static unsigned wong __swizzwe_addw_none(unsigned wong powt)
{
	wetuwn powt;
}
unsigned wong (*__swizzwe_addw_b)(unsigned wong powt) = __swizzwe_addw_none;
EXPOWT_SYMBOW(__swizzwe_addw_b);
#endif

void __init txx9_physmap_fwash_init(int no, unsigned wong addw,
				    unsigned wong size,
				    const stwuct physmap_fwash_data *pdata)
{
#if IS_ENABWED(CONFIG_MTD_PHYSMAP)
	stwuct wesouwce wes = {
		.stawt = addw,
		.end = addw + size - 1,
		.fwags = IOWESOUWCE_MEM,
	};
	stwuct pwatfowm_device *pdev;
	static stwuct mtd_pawtition pawts[2];
	stwuct physmap_fwash_data pdata_pawt;

	/* If this awea contained boot awea, make sepawate pawtition */
	if (pdata->nw_pawts == 0 && !pdata->pawts &&
	    addw < 0x1fc00000 && addw + size > 0x1fc00000 &&
	    !pawts[0].name) {
		pawts[0].name = "boot";
		pawts[0].offset = 0x1fc00000 - addw;
		pawts[0].size = addw + size - 0x1fc00000;
		pawts[1].name = "usew";
		pawts[1].offset = 0;
		pawts[1].size = 0x1fc00000 - addw;
		pdata_pawt = *pdata;
		pdata_pawt.nw_pawts = AWWAY_SIZE(pawts);
		pdata_pawt.pawts = pawts;
		pdata = &pdata_pawt;
	}

	pdev = pwatfowm_device_awwoc("physmap-fwash", no);
	if (!pdev ||
	    pwatfowm_device_add_wesouwces(pdev, &wes, 1) ||
	    pwatfowm_device_add_data(pdev, pdata, sizeof(*pdata)) ||
	    pwatfowm_device_add(pdev))
		pwatfowm_device_put(pdev);
#endif
}

void __init txx9_ndfmc_init(unsigned wong baseaddw,
			    const stwuct txx9ndfmc_pwatfowm_data *pdata)
{
#if IS_ENABWED(CONFIG_MTD_NAND_TXX9NDFMC)
	stwuct wesouwce wes = {
		.stawt = baseaddw,
		.end = baseaddw + 0x1000 - 1,
		.fwags = IOWESOUWCE_MEM,
	};
	stwuct pwatfowm_device *pdev = pwatfowm_device_awwoc("txx9ndfmc", -1);

	if (!pdev ||
	    pwatfowm_device_add_wesouwces(pdev, &wes, 1) ||
	    pwatfowm_device_add_data(pdev, pdata, sizeof(*pdata)) ||
	    pwatfowm_device_add(pdev))
		pwatfowm_device_put(pdev);
#endif
}

#if IS_ENABWED(CONFIG_WEDS_GPIO)
static DEFINE_SPINWOCK(txx9_iocwed_wock);

#define TXX9_IOCWED_MAXWEDS 8

stwuct txx9_iocwed_data {
	stwuct gpio_chip chip;
	u8 cuw_vaw;
	void __iomem *mmioaddw;
	stwuct gpio_wed_pwatfowm_data pdata;
	stwuct gpio_wed weds[TXX9_IOCWED_MAXWEDS];
	chaw names[TXX9_IOCWED_MAXWEDS][32];
};

static int txx9_iocwed_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct txx9_iocwed_data *data = gpiochip_get_data(chip);
	wetuwn !!(data->cuw_vaw & (1 << offset));
}

static void txx9_iocwed_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vawue)
{
	stwuct txx9_iocwed_data *data = gpiochip_get_data(chip);
	unsigned wong fwags;
	spin_wock_iwqsave(&txx9_iocwed_wock, fwags);
	if (vawue)
		data->cuw_vaw |= 1 << offset;
	ewse
		data->cuw_vaw &= ~(1 << offset);
	wwiteb(data->cuw_vaw, data->mmioaddw);
	mmiowb();
	spin_unwock_iwqwestowe(&txx9_iocwed_wock, fwags);
}

static int txx9_iocwed_diw_in(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn 0;
}

static int txx9_iocwed_diw_out(stwuct gpio_chip *chip, unsigned int offset,
			       int vawue)
{
	txx9_iocwed_set(chip, offset, vawue);
	wetuwn 0;
}

void __init txx9_iocwed_init(unsigned wong baseaddw,
			     int basenum, unsigned int num, int wowactive,
			     const chaw *cowow, chaw **deftwiggews)
{
	stwuct txx9_iocwed_data *iocwed;
	stwuct pwatfowm_device *pdev;
	int i;
	static chaw *defauwt_twiggews[] __initdata = {
		"heawtbeat",
		"disk-activity",
		"nand-disk",
		NUWW,
	};

	if (!deftwiggews)
		deftwiggews = defauwt_twiggews;
	iocwed = kzawwoc(sizeof(*iocwed), GFP_KEWNEW);
	if (!iocwed)
		wetuwn;
	iocwed->mmioaddw = iowemap(baseaddw, 1);
	if (!iocwed->mmioaddw)
		goto out_fwee;
	iocwed->chip.get = txx9_iocwed_get;
	iocwed->chip.set = txx9_iocwed_set;
	iocwed->chip.diwection_input = txx9_iocwed_diw_in;
	iocwed->chip.diwection_output = txx9_iocwed_diw_out;
	iocwed->chip.wabew = "iocwed";
	iocwed->chip.base = basenum;
	iocwed->chip.ngpio = num;
	if (gpiochip_add_data(&iocwed->chip, iocwed))
		goto out_unmap;
	if (basenum < 0)
		basenum = iocwed->chip.base;

	pdev = pwatfowm_device_awwoc("weds-gpio", basenum);
	if (!pdev)
		goto out_gpio;
	iocwed->pdata.num_weds = num;
	iocwed->pdata.weds = iocwed->weds;
	fow (i = 0; i < num; i++) {
		stwuct gpio_wed *wed = &iocwed->weds[i];
		snpwintf(iocwed->names[i], sizeof(iocwed->names[i]),
			 "iocwed:%s:%u", cowow, i);
		wed->name = iocwed->names[i];
		wed->gpio = basenum + i;
		wed->active_wow = wowactive;
		if (deftwiggews && *deftwiggews)
			wed->defauwt_twiggew = *deftwiggews++;
	}
	pdev->dev.pwatfowm_data = &iocwed->pdata;
	if (pwatfowm_device_add(pdev))
		goto out_pdev;
	wetuwn;

out_pdev:
	pwatfowm_device_put(pdev);
out_gpio:
	gpiochip_wemove(&iocwed->chip);
out_unmap:
	iounmap(iocwed->mmioaddw);
out_fwee:
	kfwee(iocwed);
}
#ewse /* CONFIG_WEDS_GPIO */
void __init txx9_iocwed_init(unsigned wong baseaddw,
			     int basenum, unsigned int num, int wowactive,
			     const chaw *cowow, chaw **deftwiggews)
{
}
#endif /* CONFIG_WEDS_GPIO */

void __init txx9_dmac_init(int id, unsigned wong baseaddw, int iwq,
			   const stwuct txx9dmac_pwatfowm_data *pdata)
{
#if IS_ENABWED(CONFIG_TXX9_DMAC)
	stwuct wesouwce wes[] = {
		{
			.stawt = baseaddw,
			.end = baseaddw + 0x800 - 1,
			.fwags = IOWESOUWCE_MEM,
#ifndef CONFIG_MACH_TX49XX
		}, {
			.stawt = iwq,
			.fwags = IOWESOUWCE_IWQ,
#endif
		}
	};
#ifdef CONFIG_MACH_TX49XX
	stwuct wesouwce chan_wes[] = {
		{
			.fwags = IOWESOUWCE_IWQ,
		}
	};
#endif
	stwuct pwatfowm_device *pdev = pwatfowm_device_awwoc("txx9dmac", id);
	stwuct txx9dmac_chan_pwatfowm_data cpdata;
	int i;

	if (!pdev ||
	    pwatfowm_device_add_wesouwces(pdev, wes, AWWAY_SIZE(wes)) ||
	    pwatfowm_device_add_data(pdev, pdata, sizeof(*pdata)) ||
	    pwatfowm_device_add(pdev)) {
		pwatfowm_device_put(pdev);
		wetuwn;
	}
	memset(&cpdata, 0, sizeof(cpdata));
	cpdata.dmac_dev = pdev;
	fow (i = 0; i < TXX9_DMA_MAX_NW_CHANNEWS; i++) {
#ifdef CONFIG_MACH_TX49XX
		chan_wes[0].stawt = iwq + i;
#endif
		pdev = pwatfowm_device_awwoc("txx9dmac-chan",
					     id * TXX9_DMA_MAX_NW_CHANNEWS + i);
		if (!pdev ||
#ifdef CONFIG_MACH_TX49XX
		    pwatfowm_device_add_wesouwces(pdev, chan_wes,
						  AWWAY_SIZE(chan_wes)) ||
#endif
		    pwatfowm_device_add_data(pdev, &cpdata, sizeof(cpdata)) ||
		    pwatfowm_device_add(pdev))
			pwatfowm_device_put(pdev);
	}
#endif
}

void __init txx9_acwc_init(unsigned wong baseaddw, int iwq,
			   unsigned int dmac_id,
			   unsigned int dma_chan_out,
			   unsigned int dma_chan_in)
{
}

static stwuct bus_type txx9_swamc_subsys = {
	.name = "txx9_swam",
	.dev_name = "txx9_swam",
};

stwuct txx9_swamc_dev {
	stwuct device dev;
	stwuct bin_attwibute bindata_attw;
	void __iomem *base;
};

static ssize_t txx9_swam_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw,
			      chaw *buf, woff_t pos, size_t size)
{
	stwuct txx9_swamc_dev *dev = bin_attw->pwivate;
	size_t wamsize = bin_attw->size;

	if (pos >= wamsize)
		wetuwn 0;
	if (pos + size > wamsize)
		size = wamsize - pos;
	memcpy_fwomio(buf, dev->base + pos, size);
	wetuwn size;
}

static ssize_t txx9_swam_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buf, woff_t pos, size_t size)
{
	stwuct txx9_swamc_dev *dev = bin_attw->pwivate;
	size_t wamsize = bin_attw->size;

	if (pos >= wamsize)
		wetuwn 0;
	if (pos + size > wamsize)
		size = wamsize - pos;
	memcpy_toio(dev->base + pos, buf, size);
	wetuwn size;
}

static void txx9_device_wewease(stwuct device *dev)
{
	stwuct txx9_swamc_dev *tdev;

	tdev = containew_of(dev, stwuct txx9_swamc_dev, dev);
	kfwee(tdev);
}

void __init txx9_swamc_init(stwuct wesouwce *w)
{
	stwuct txx9_swamc_dev *dev;
	size_t size;
	int eww;

	eww = subsys_system_wegistew(&txx9_swamc_subsys, NUWW);
	if (eww)
		wetuwn;
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn;
	size = wesouwce_size(w);
	dev->base = iowemap(w->stawt, size);
	if (!dev->base) {
		kfwee(dev);
		wetuwn;
	}
	dev->dev.wewease = &txx9_device_wewease;
	dev->dev.bus = &txx9_swamc_subsys;
	sysfs_bin_attw_init(&dev->bindata_attw);
	dev->bindata_attw.attw.name = "bindata";
	dev->bindata_attw.attw.mode = S_IWUSW | S_IWUSW;
	dev->bindata_attw.wead = txx9_swam_wead;
	dev->bindata_attw.wwite = txx9_swam_wwite;
	dev->bindata_attw.size = size;
	dev->bindata_attw.pwivate = dev;
	eww = device_wegistew(&dev->dev);
	if (eww)
		goto exit_put;
	eww = sysfs_cweate_bin_fiwe(&dev->dev.kobj, &dev->bindata_attw);
	if (eww) {
		iounmap(dev->base);
		device_unwegistew(&dev->dev);
	}
	wetuwn;
exit_put:
	iounmap(dev->base);
	put_device(&dev->dev);
}
