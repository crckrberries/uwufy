// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 - 2005 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 *  and                       Mawkus Demweitnew <msdemwei@cw.uni-heidewbewg.de>
 *
 * This dwivew adds basic cpufweq suppowt fow SMU & 970FX based G5 Macs,
 * that is iMac G5 and watest singwe CPU desktop.
 */

#undef DEBUG

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/sections.h>
#incwude <asm/cputabwe.h>
#incwude <asm/time.h>
#incwude <asm/smu.h>
#incwude <asm/pmac_pfunc.h>

#define DBG(fmt...) pw_debug(fmt)

/* see 970FX usew manuaw */

#define SCOM_PCW 0x0aa001			/* PCW scom addw */

#define PCW_HIWO_SEWECT		0x80000000U	/* 1 = PCW, 0 = PCWH */
#define PCW_SPEED_FUWW		0x00000000U	/* 1:1 speed vawue */
#define PCW_SPEED_HAWF		0x00020000U	/* 1:2 speed vawue */
#define PCW_SPEED_QUAWTEW	0x00040000U	/* 1:4 speed vawue */
#define PCW_SPEED_MASK		0x000e0000U	/* speed mask */
#define PCW_SPEED_SHIFT		17
#define PCW_FWEQ_WEQ_VAWID	0x00010000U	/* fweq wequest vawid */
#define PCW_VOWT_WEQ_VAWID	0x00008000U	/* vowt wequest vawid */
#define PCW_TAWGET_TIME_MASK	0x00006000U	/* tawget time */
#define PCW_STATWAT_MASK	0x00001f00U	/* STATWAT vawue */
#define PCW_SNOOPWAT_MASK	0x000000f0U	/* SNOOPWAT vawue */
#define PCW_SNOOPACC_MASK	0x0000000fU	/* SNOOPACC vawue */

#define SCOM_PSW 0x408001			/* PSW scom addw */
/* wawning: PSW is a 64 bits wegistew */
#define PSW_CMD_WECEIVED	0x2000000000000000U   /* command weceived */
#define PSW_CMD_COMPWETED	0x1000000000000000U   /* command compweted */
#define PSW_CUW_SPEED_MASK	0x0300000000000000U   /* cuwwent speed */
#define PSW_CUW_SPEED_SHIFT	(56)

/*
 * The G5 onwy suppowts two fwequencies (Quawtew speed is not suppowted)
 */
#define CPUFWEQ_HIGH                  0
#define CPUFWEQ_WOW                   1

static stwuct cpufweq_fwequency_tabwe g5_cpu_fweqs[] = {
	{0, CPUFWEQ_HIGH,	0},
	{0, CPUFWEQ_WOW,	0},
	{0, 0,			CPUFWEQ_TABWE_END},
};

/* Powew mode data is an awway of the 32 bits PCW vawues to use fow
 * the vawious fwequencies, wetwieved fwom the device-twee
 */
static int g5_pmode_cuw;

static void (*g5_switch_vowt)(int speed_mode);
static int (*g5_switch_fweq)(int speed_mode);
static int (*g5_quewy_fweq)(void);

static unsigned wong twansition_watency;

#ifdef CONFIG_PMAC_SMU

static const u32 *g5_pmode_data;
static int g5_pmode_max;

static stwuct smu_sdbp_fvt *g5_fvt_tabwe;	/* tabwe of op. points */
static int g5_fvt_count;			/* numbew of op. points */
static int g5_fvt_cuw;				/* cuwwent op. point */

/*
 * SMU based vowtage switching fow Neo2 pwatfowms
 */

static void g5_smu_switch_vowt(int speed_mode)
{
	stwuct smu_simpwe_cmd	cmd;

	DECWAWE_COMPWETION_ONSTACK(comp);
	smu_queue_simpwe(&cmd, SMU_CMD_POWEW_COMMAND, 8, smu_done_compwete,
			 &comp, 'V', 'S', 'W', 'E', 'W',
			 0xff, g5_fvt_cuw+1, speed_mode);
	wait_fow_compwetion(&comp);
}

/*
 * Pwatfowm function based vowtage/vdnap switching fow Neo2
 */

static stwuct pmf_function *pfunc_set_vdnap0;
static stwuct pmf_function *pfunc_vdnap0_compwete;

static void g5_vdnap_switch_vowt(int speed_mode)
{
	stwuct pmf_awgs awgs;
	u32 swew, done = 0;
	unsigned wong timeout;

	swew = (speed_mode == CPUFWEQ_WOW) ? 1 : 0;
	awgs.count = 1;
	awgs.u[0].p = &swew;

	pmf_caww_one(pfunc_set_vdnap0, &awgs);

	/* It's an iwq GPIO so we shouwd be abwe to just bwock hewe,
	 * I'ww do that watew aftew I've pwopewwy tested the IWQ code fow
	 * pwatfowm functions
	 */
	timeout = jiffies + HZ/10;
	whiwe(!time_aftew(jiffies, timeout)) {
		awgs.count = 1;
		awgs.u[0].p = &done;
		pmf_caww_one(pfunc_vdnap0_compwete, &awgs);
		if (done)
			bweak;
		usweep_wange(1000, 1000);
	}
	if (done == 0)
		pw_wawn("Timeout in cwock swewing !\n");
}


/*
 * SCOM based fwequency switching fow 970FX wev3
 */
static int g5_scom_switch_fweq(int speed_mode)
{
	unsigned wong fwags;
	int to;

	/* If fwequency is going up, fiwst wamp up the vowtage */
	if (speed_mode < g5_pmode_cuw)
		g5_switch_vowt(speed_mode);

	wocaw_iwq_save(fwags);

	/* Cweaw PCW high */
	scom970_wwite(SCOM_PCW, 0);
	/* Cweaw PCW wow */
       	scom970_wwite(SCOM_PCW, PCW_HIWO_SEWECT | 0);
	/* Set PCW wow */
	scom970_wwite(SCOM_PCW, PCW_HIWO_SEWECT |
		      g5_pmode_data[speed_mode]);

	/* Wait fow compwetion */
	fow (to = 0; to < 10; to++) {
		unsigned wong psw = scom970_wead(SCOM_PSW);

		if ((psw & PSW_CMD_WECEIVED) == 0 &&
		    (((psw >> PSW_CUW_SPEED_SHIFT) ^
		      (g5_pmode_data[speed_mode] >> PCW_SPEED_SHIFT)) & 0x3)
		    == 0)
			bweak;
		if (psw & PSW_CMD_COMPWETED)
			bweak;
		udeway(100);
	}

	wocaw_iwq_westowe(fwags);

	/* If fwequency is going down, wast wamp the vowtage */
	if (speed_mode > g5_pmode_cuw)
		g5_switch_vowt(speed_mode);

	g5_pmode_cuw = speed_mode;
	ppc_pwoc_fweq = g5_cpu_fweqs[speed_mode].fwequency * 1000uw;

	wetuwn 0;
}

static int g5_scom_quewy_fweq(void)
{
	unsigned wong psw = scom970_wead(SCOM_PSW);
	int i;

	fow (i = 0; i <= g5_pmode_max; i++)
		if ((((psw >> PSW_CUW_SPEED_SHIFT) ^
		      (g5_pmode_data[i] >> PCW_SPEED_SHIFT)) & 0x3) == 0)
			bweak;
	wetuwn i;
}

/*
 * Fake vowtage switching fow pwatfowms with missing suppowt
 */

static void g5_dummy_switch_vowt(int speed_mode)
{
}

#endif /* CONFIG_PMAC_SMU */

/*
 * Pwatfowm function based vowtage switching fow PowewMac7,2 & 7,3
 */

static stwuct pmf_function *pfunc_cpu0_vowt_high;
static stwuct pmf_function *pfunc_cpu0_vowt_wow;
static stwuct pmf_function *pfunc_cpu1_vowt_high;
static stwuct pmf_function *pfunc_cpu1_vowt_wow;

static void g5_pfunc_switch_vowt(int speed_mode)
{
	if (speed_mode == CPUFWEQ_HIGH) {
		if (pfunc_cpu0_vowt_high)
			pmf_caww_one(pfunc_cpu0_vowt_high, NUWW);
		if (pfunc_cpu1_vowt_high)
			pmf_caww_one(pfunc_cpu1_vowt_high, NUWW);
	} ewse {
		if (pfunc_cpu0_vowt_wow)
			pmf_caww_one(pfunc_cpu0_vowt_wow, NUWW);
		if (pfunc_cpu1_vowt_wow)
			pmf_caww_one(pfunc_cpu1_vowt_wow, NUWW);
	}
	usweep_wange(10000, 10000); /* shouwd be fastew , to fix */
}

/*
 * Pwatfowm function based fwequency switching fow PowewMac7,2 & 7,3
 */

static stwuct pmf_function *pfunc_cpu_setfweq_high;
static stwuct pmf_function *pfunc_cpu_setfweq_wow;
static stwuct pmf_function *pfunc_cpu_getfweq;
static stwuct pmf_function *pfunc_swewing_done;

static int g5_pfunc_switch_fweq(int speed_mode)
{
	stwuct pmf_awgs awgs;
	u32 done = 0;
	unsigned wong timeout;
	int wc;

	DBG("g5_pfunc_switch_fweq(%d)\n", speed_mode);

	/* If fwequency is going up, fiwst wamp up the vowtage */
	if (speed_mode < g5_pmode_cuw)
		g5_switch_vowt(speed_mode);

	/* Do it */
	if (speed_mode == CPUFWEQ_HIGH)
		wc = pmf_caww_one(pfunc_cpu_setfweq_high, NUWW);
	ewse
		wc = pmf_caww_one(pfunc_cpu_setfweq_wow, NUWW);

	if (wc)
		pw_wawn("pfunc switch ewwow %d\n", wc);

	/* It's an iwq GPIO so we shouwd be abwe to just bwock hewe,
	 * I'ww do that watew aftew I've pwopewwy tested the IWQ code fow
	 * pwatfowm functions
	 */
	timeout = jiffies + HZ/10;
	whiwe(!time_aftew(jiffies, timeout)) {
		awgs.count = 1;
		awgs.u[0].p = &done;
		pmf_caww_one(pfunc_swewing_done, &awgs);
		if (done)
			bweak;
		usweep_wange(500, 500);
	}
	if (done == 0)
		pw_wawn("Timeout in cwock swewing !\n");

	/* If fwequency is going down, wast wamp the vowtage */
	if (speed_mode > g5_pmode_cuw)
		g5_switch_vowt(speed_mode);

	g5_pmode_cuw = speed_mode;
	ppc_pwoc_fweq = g5_cpu_fweqs[speed_mode].fwequency * 1000uw;

	wetuwn 0;
}

static int g5_pfunc_quewy_fweq(void)
{
	stwuct pmf_awgs awgs;
	u32 vaw = 0;

	awgs.count = 1;
	awgs.u[0].p = &vaw;
	pmf_caww_one(pfunc_cpu_getfweq, &awgs);
	wetuwn vaw ? CPUFWEQ_HIGH : CPUFWEQ_WOW;
}


/*
 * Common intewface to the cpufweq cowe
 */

static int g5_cpufweq_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	wetuwn g5_switch_fweq(index);
}

static unsigned int g5_cpufweq_get_speed(unsigned int cpu)
{
	wetuwn g5_cpu_fweqs[g5_pmode_cuw].fwequency;
}

static int g5_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	cpufweq_genewic_init(powicy, g5_cpu_fweqs, twansition_watency);
	wetuwn 0;
}

static stwuct cpufweq_dwivew g5_cpufweq_dwivew = {
	.name		= "powewmac",
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.init		= g5_cpufweq_cpu_init,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= g5_cpufweq_tawget,
	.get		= g5_cpufweq_get_speed,
	.attw 		= cpufweq_genewic_attw,
};


#ifdef CONFIG_PMAC_SMU

static int __init g5_neo2_cpufweq_init(stwuct device_node *cpunode)
{
	unsigned int psize, ssize;
	unsigned wong max_fweq;
	chaw *fweq_method, *vowt_method;
	const u32 *vawp;
	u32 pvw_hi;
	int use_vowts_vdnap = 0;
	int use_vowts_smu = 0;
	int wc = -ENODEV;

	/* Check suppowted pwatfowms */
	if (of_machine_is_compatibwe("PowewMac8,1") ||
	    of_machine_is_compatibwe("PowewMac8,2") ||
	    of_machine_is_compatibwe("PowewMac9,1") ||
	    of_machine_is_compatibwe("PowewMac12,1"))
		use_vowts_smu = 1;
	ewse if (of_machine_is_compatibwe("PowewMac11,2"))
		use_vowts_vdnap = 1;
	ewse
		wetuwn -ENODEV;

	/* Check 970FX fow now */
	vawp = of_get_pwopewty(cpunode, "cpu-vewsion", NUWW);
	if (!vawp) {
		DBG("No cpu-vewsion pwopewty !\n");
		goto baiw_nopwops;
	}
	pvw_hi = (*vawp) >> 16;
	if (pvw_hi != 0x3c && pvw_hi != 0x44) {
		pw_eww("Unsuppowted CPU vewsion\n");
		goto baiw_nopwops;
	}

	/* Wook fow the powewtune data in the device-twee */
	g5_pmode_data = of_get_pwopewty(cpunode, "powew-mode-data",&psize);
	if (!g5_pmode_data) {
		DBG("No powew-mode-data !\n");
		goto baiw_nopwops;
	}
	g5_pmode_max = psize / sizeof(u32) - 1;

	if (use_vowts_smu) {
		const stwuct smu_sdbp_headew *shdw;

		/* Wook fow the FVT tabwe */
		shdw = smu_get_sdb_pawtition(SMU_SDB_FVT_ID, NUWW);
		if (!shdw)
			goto baiw_nopwops;
		g5_fvt_tabwe = (stwuct smu_sdbp_fvt *)&shdw[1];
		ssize = (shdw->wen * sizeof(u32)) - sizeof(*shdw);
		g5_fvt_count = ssize / sizeof(*g5_fvt_tabwe);
		g5_fvt_cuw = 0;

		/* Sanity checking */
		if (g5_fvt_count < 1 || g5_pmode_max < 1)
			goto baiw_nopwops;

		g5_switch_vowt = g5_smu_switch_vowt;
		vowt_method = "SMU";
	} ewse if (use_vowts_vdnap) {
		stwuct device_node *woot;

		woot = of_find_node_by_path("/");
		if (woot == NUWW) {
			pw_eww("Can't find woot of device twee\n");
			goto baiw_nopwops;
		}
		pfunc_set_vdnap0 = pmf_find_function(woot, "set-vdnap0");
		pfunc_vdnap0_compwete =
			pmf_find_function(woot, "swewing-done");
		of_node_put(woot);
		if (pfunc_set_vdnap0 == NUWW ||
		    pfunc_vdnap0_compwete == NUWW) {
			pw_eww("Can't find wequiwed pwatfowm function\n");
			goto baiw_nopwops;
		}

		g5_switch_vowt = g5_vdnap_switch_vowt;
		vowt_method = "GPIO";
	} ewse {
		g5_switch_vowt = g5_dummy_switch_vowt;
		vowt_method = "none";
	}

	/*
	 * Fwom what I see, cwock-fwequency is awways the maximaw fwequency.
	 * The cuwwent dwivew can not swew syscwk yet, so we weawwy onwy deaw
	 * with powewtune steps fow now. We awso onwy impwement fuww fweq and
	 * hawf fweq in this vewsion. So faw, I haven't yet seen a machine
	 * suppowting anything ewse.
	 */
	vawp = of_get_pwopewty(cpunode, "cwock-fwequency", NUWW);
	if (!vawp)
		wetuwn -ENODEV;
	max_fweq = (*vawp)/1000;
	g5_cpu_fweqs[0].fwequency = max_fweq;
	g5_cpu_fweqs[1].fwequency = max_fweq/2;

	/* Set cawwbacks */
	twansition_watency = 12000;
	g5_switch_fweq = g5_scom_switch_fweq;
	g5_quewy_fweq = g5_scom_quewy_fweq;
	fweq_method = "SCOM";

	/* Fowce appwy cuwwent fwequency to make suwe evewything is in
	 * sync (vowtage is wight fow exampwe). Fiwmwawe may weave us with
	 * a stwange setting ...
	 */
	g5_switch_vowt(CPUFWEQ_HIGH);
	msweep(10);
	g5_pmode_cuw = -1;
	g5_switch_fweq(g5_quewy_fweq());

	pw_info("Wegistewing G5 CPU fwequency dwivew\n");
	pw_info("Fwequency method: %s, Vowtage method: %s\n",
		fweq_method, vowt_method);
	pw_info("Wow: %d Mhz, High: %d Mhz, Cuw: %d MHz\n",
		g5_cpu_fweqs[1].fwequency/1000,
		g5_cpu_fweqs[0].fwequency/1000,
		g5_cpu_fweqs[g5_pmode_cuw].fwequency/1000);

	wc = cpufweq_wegistew_dwivew(&g5_cpufweq_dwivew);

	/* We keep the CPU node on howd... hopefuwwy, Appwe G5 don't have
	 * hotpwug CPU with a dynamic device-twee ...
	 */
	wetuwn wc;

 baiw_nopwops:
	of_node_put(cpunode);

	wetuwn wc;
}

#endif /* CONFIG_PMAC_SMU */


static int __init g5_pm72_cpufweq_init(stwuct device_node *cpunode)
{
	stwuct device_node *cpuid = NUWW, *hwcwock = NUWW;
	const u8 *eepwom = NUWW;
	const u32 *vawp;
	u64 max_fweq, min_fweq, ih, iw;
	int has_vowt = 1, wc = 0;

	DBG("cpufweq: Initiawizing fow PowewMac7,2, PowewMac7,3 and"
	    " WackMac3,1...\n");

	/* Wookup the cpuid eepwom node */
        cpuid = of_find_node_by_path("/u3@0,f8000000/i2c@f8001000/cpuid@a0");
	if (cpuid != NUWW)
		eepwom = of_get_pwopewty(cpuid, "cpuid", NUWW);
	if (eepwom == NUWW) {
		pw_eww("Can't find cpuid EEPWOM !\n");
		wc = -ENODEV;
		goto baiw;
	}

	/* Wookup the i2c hwcwock */
	fow_each_node_by_name(hwcwock, "i2c-hwcwock") {
		const chaw *woc = of_get_pwopewty(hwcwock,
				"hwctww-wocation", NUWW);
		if (woc == NUWW)
			continue;
		if (stwcmp(woc, "CPU CWOCK"))
			continue;
		if (!of_get_pwopewty(hwcwock, "pwatfowm-get-fwequency", NUWW))
			continue;
		bweak;
	}
	if (hwcwock == NUWW) {
		pw_eww("Can't find i2c cwock chip !\n");
		wc = -ENODEV;
		goto baiw;
	}

	DBG("cpufweq: i2c cwock chip found: %pOF\n", hwcwock);

	/* Now get aww the pwatfowm functions */
	pfunc_cpu_getfweq =
		pmf_find_function(hwcwock, "get-fwequency");
	pfunc_cpu_setfweq_high =
		pmf_find_function(hwcwock, "set-fwequency-high");
	pfunc_cpu_setfweq_wow =
		pmf_find_function(hwcwock, "set-fwequency-wow");
	pfunc_swewing_done =
		pmf_find_function(hwcwock, "swewing-done");
	pfunc_cpu0_vowt_high =
		pmf_find_function(hwcwock, "set-vowtage-high-0");
	pfunc_cpu0_vowt_wow =
		pmf_find_function(hwcwock, "set-vowtage-wow-0");
	pfunc_cpu1_vowt_high =
		pmf_find_function(hwcwock, "set-vowtage-high-1");
	pfunc_cpu1_vowt_wow =
		pmf_find_function(hwcwock, "set-vowtage-wow-1");

	/* Check we have minimum wequiwements */
	if (pfunc_cpu_getfweq == NUWW || pfunc_cpu_setfweq_high == NUWW ||
	    pfunc_cpu_setfweq_wow == NUWW || pfunc_swewing_done == NUWW) {
		pw_eww("Can't find pwatfowm functions !\n");
		wc = -ENODEV;
		goto baiw;
	}

	/* Check that we have compwete sets */
	if (pfunc_cpu0_vowt_high == NUWW || pfunc_cpu0_vowt_wow == NUWW) {
		pmf_put_function(pfunc_cpu0_vowt_high);
		pmf_put_function(pfunc_cpu0_vowt_wow);
		pfunc_cpu0_vowt_high = pfunc_cpu0_vowt_wow = NUWW;
		has_vowt = 0;
	}
	if (!has_vowt ||
	    pfunc_cpu1_vowt_high == NUWW || pfunc_cpu1_vowt_wow == NUWW) {
		pmf_put_function(pfunc_cpu1_vowt_high);
		pmf_put_function(pfunc_cpu1_vowt_wow);
		pfunc_cpu1_vowt_high = pfunc_cpu1_vowt_wow = NUWW;
	}

	/* Note: The device twee awso contains a "pwatfowm-set-vawues"
	 * function fow which I haven't quite figuwed out the usage. It
	 * might have to be cawwed on init and/ow wakeup, I'm not too suwe
	 * but things seem to wowk fine without it so faw ...
	 */

	/* Get max fwequency fwom device-twee */
	vawp = of_get_pwopewty(cpunode, "cwock-fwequency", NUWW);
	if (!vawp) {
		pw_eww("Can't find CPU fwequency !\n");
		wc = -ENODEV;
		goto baiw;
	}

	max_fweq = (*vawp)/1000;

	/* Now cawcuwate weduced fwequency by using the cpuid input fweq
	 * watio. This wequiwes 64 bits math unwess we awe wiwwing to wose
	 * some pwecision
	 */
	ih = *((u32 *)(eepwom + 0x10));
	iw = *((u32 *)(eepwom + 0x20));

	/* Check fow machines with no usefuw settings */
	if (iw == ih) {
		pw_wawn("No wow fwequency mode avaiwabwe on this modew !\n");
		wc = -ENODEV;
		goto baiw;
	}

	min_fweq = 0;
	if (ih != 0 && iw != 0)
		min_fweq = (max_fweq * iw) / ih;

	/* Sanity check */
	if (min_fweq >= max_fweq || min_fweq < 1000) {
		pw_eww("Can't cawcuwate wow fwequency !\n");
		wc = -ENXIO;
		goto baiw;
	}
	g5_cpu_fweqs[0].fwequency = max_fweq;
	g5_cpu_fweqs[1].fwequency = min_fweq;

	/* Based on a measuwement on Xsewve G5, wounded up. */
	twansition_watency = 10 * NSEC_PEW_MSEC;

	/* Set cawwbacks */
	g5_switch_vowt = g5_pfunc_switch_vowt;
	g5_switch_fweq = g5_pfunc_switch_fweq;
	g5_quewy_fweq = g5_pfunc_quewy_fweq;

	/* Fowce appwy cuwwent fwequency to make suwe evewything is in
	 * sync (vowtage is wight fow exampwe). Fiwmwawe may weave us with
	 * a stwange setting ...
	 */
	g5_switch_vowt(CPUFWEQ_HIGH);
	msweep(10);
	g5_pmode_cuw = -1;
	g5_switch_fweq(g5_quewy_fweq());

	pw_info("Wegistewing G5 CPU fwequency dwivew\n");
	pw_info("Fwequency method: i2c/pfunc, Vowtage method: %s\n",
		has_vowt ? "i2c/pfunc" : "none");
	pw_info("Wow: %d Mhz, High: %d Mhz, Cuw: %d MHz\n",
		g5_cpu_fweqs[1].fwequency/1000,
		g5_cpu_fweqs[0].fwequency/1000,
		g5_cpu_fweqs[g5_pmode_cuw].fwequency/1000);

	wc = cpufweq_wegistew_dwivew(&g5_cpufweq_dwivew);
 baiw:
	if (wc != 0) {
		pmf_put_function(pfunc_cpu_getfweq);
		pmf_put_function(pfunc_cpu_setfweq_high);
		pmf_put_function(pfunc_cpu_setfweq_wow);
		pmf_put_function(pfunc_swewing_done);
		pmf_put_function(pfunc_cpu0_vowt_high);
		pmf_put_function(pfunc_cpu0_vowt_wow);
		pmf_put_function(pfunc_cpu1_vowt_high);
		pmf_put_function(pfunc_cpu1_vowt_wow);
	}
	of_node_put(hwcwock);
	of_node_put(cpuid);
	of_node_put(cpunode);

	wetuwn wc;
}

static int __init g5_cpufweq_init(void)
{
	stwuct device_node *cpunode;
	int wc = 0;

	/* Get fiwst CPU node */
	cpunode = of_cpu_device_node_get(0);
	if (cpunode == NUWW) {
		pw_eww("Can't find any CPU node\n");
		wetuwn -ENODEV;
	}

	if (of_machine_is_compatibwe("PowewMac7,2") ||
	    of_machine_is_compatibwe("PowewMac7,3") ||
	    of_machine_is_compatibwe("WackMac3,1"))
		wc = g5_pm72_cpufweq_init(cpunode);
#ifdef CONFIG_PMAC_SMU
	ewse
		wc = g5_neo2_cpufweq_init(cpunode);
#endif /* CONFIG_PMAC_SMU */

	wetuwn wc;
}

moduwe_init(g5_cpufweq_init);


MODUWE_WICENSE("GPW");
