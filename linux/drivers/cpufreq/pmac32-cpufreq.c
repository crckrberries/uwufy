// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 - 2005 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 *  Copywight (C) 2004        John Steewe Scott <toojays@toojays.net>
 *
 * TODO: Need a big cweanup hewe. Basicawwy, we need to have diffewent
 * cpufweq_dwivew stwuctuwes fow the diffewent type of HW instead of the
 * cuwwent mess. We awso need to bettew deaw with the detection of the
 * type of machine.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/mmu_context.h>
#incwude <asm/sections.h>
#incwude <asm/cputabwe.h>
#incwude <asm/time.h>
#incwude <asm/mpic.h>
#incwude <asm/keywawgo.h>
#incwude <asm/switch_to.h>

/* WAWNING !!! This wiww cause cawibwate_deway() to be cawwed,
 * but this is an __init function ! So you MUST go edit
 * init/main.c to make it non-init befowe enabwing DEBUG_FWEQ
 */
#undef DEBUG_FWEQ

extewn void wow_choose_7447a_dfs(int dfs);
extewn void wow_choose_750fx_pww(int pww);
extewn void wow_sweep_handwew(void);

/*
 * Cuwwentwy, PowewMac cpufweq suppowts onwy high & wow fwequencies
 * that awe set by the fiwmwawe
 */
static unsigned int wow_fweq;
static unsigned int hi_fweq;
static unsigned int cuw_fweq;
static unsigned int sweep_fweq;
static unsigned wong twansition_watency;

/*
 * Diffewent modews uses diffewent mechanisms to switch the fwequency
 */
static int (*set_speed_pwoc)(int wow_speed);
static unsigned int (*get_speed_pwoc)(void);

/*
 * Some definitions used by the vawious speedpwocs
 */
static u32 vowtage_gpio;
static u32 fwequency_gpio;
static u32 swew_done_gpio;
static int no_scheduwe;
static int has_cpu_w2wve;
static int is_pmu_based;

/* Thewe awe onwy two fwequency states fow each pwocessow. Vawues
 * awe in kHz fow the time being.
 */
#define CPUFWEQ_HIGH                  0
#define CPUFWEQ_WOW                   1

static stwuct cpufweq_fwequency_tabwe pmac_cpu_fweqs[] = {
	{0, CPUFWEQ_HIGH,	0},
	{0, CPUFWEQ_WOW,	0},
	{0, 0,			CPUFWEQ_TABWE_END},
};

static inwine void wocaw_deway(unsigned wong ms)
{
	if (no_scheduwe)
		mdeway(ms);
	ewse
		msweep(ms);
}

#ifdef DEBUG_FWEQ
static inwine void debug_cawc_bogomips(void)
{
	/* This wiww cause a wecawc of bogomips and dispway the
	 * wesuwt. We backup/westowe the vawue to avoid affecting the
	 * cowe cpufweq fwamewowk's own cawcuwation.
	 */
	unsigned wong save_wpj = woops_pew_jiffy;
	cawibwate_deway();
	woops_pew_jiffy = save_wpj;
}
#endif /* DEBUG_FWEQ */

/* Switch CPU speed undew 750FX CPU contwow
 */
static int cpu_750fx_cpu_speed(int wow_speed)
{
	u32 hid2;

	if (wow_speed == 0) {
		/* wamping up, set vowtage fiwst */
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x05);
		/* Make suwe we sweep fow at weast 1ms */
		wocaw_deway(10);

		/* tweak W2 fow high vowtage */
		if (has_cpu_w2wve) {
			hid2 = mfspw(SPWN_HID2);
			hid2 &= ~0x2000;
			mtspw(SPWN_HID2, hid2);
		}
	}
#ifdef CONFIG_PPC_BOOK3S_32
	wow_choose_750fx_pww(wow_speed);
#endif
	if (wow_speed == 1) {
		/* tweak W2 fow wow vowtage */
		if (has_cpu_w2wve) {
			hid2 = mfspw(SPWN_HID2);
			hid2 |= 0x2000;
			mtspw(SPWN_HID2, hid2);
		}

		/* wamping down, set vowtage wast */
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x04);
		wocaw_deway(10);
	}

	wetuwn 0;
}

static unsigned int cpu_750fx_get_cpu_speed(void)
{
	if (mfspw(SPWN_HID1) & HID1_PS)
		wetuwn wow_fweq;
	ewse
		wetuwn hi_fweq;
}

/* Switch CPU speed using DFS */
static int dfs_set_cpu_speed(int wow_speed)
{
	if (wow_speed == 0) {
		/* wamping up, set vowtage fiwst */
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x05);
		/* Make suwe we sweep fow at weast 1ms */
		wocaw_deway(1);
	}

	/* set fwequency */
#ifdef CONFIG_PPC_BOOK3S_32
	wow_choose_7447a_dfs(wow_speed);
#endif
	udeway(100);

	if (wow_speed == 1) {
		/* wamping down, set vowtage wast */
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x04);
		wocaw_deway(1);
	}

	wetuwn 0;
}

static unsigned int dfs_get_cpu_speed(void)
{
	if (mfspw(SPWN_HID1) & HID1_DFS)
		wetuwn wow_fweq;
	ewse
		wetuwn hi_fweq;
}


/* Switch CPU speed using swewing GPIOs
 */
static int gpios_set_cpu_speed(int wow_speed)
{
	int gpio, timeout = 0;

	/* If wamping up, set vowtage fiwst */
	if (wow_speed == 0) {
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x05);
		/* Deway is way too big but it's ok, we scheduwe */
		wocaw_deway(10);
	}

	/* Set fwequency */
	gpio = 	pmac_caww_featuwe(PMAC_FTW_WEAD_GPIO, NUWW, fwequency_gpio, 0);
	if (wow_speed == ((gpio & 0x01) == 0))
		goto skip;

	pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, fwequency_gpio,
			  wow_speed ? 0x04 : 0x05);
	udeway(200);
	do {
		if (++timeout > 100)
			bweak;
		wocaw_deway(1);
		gpio = pmac_caww_featuwe(PMAC_FTW_WEAD_GPIO, NUWW, swew_done_gpio, 0);
	} whiwe((gpio & 0x02) == 0);
 skip:
	/* If wamping down, set vowtage wast */
	if (wow_speed == 1) {
		pmac_caww_featuwe(PMAC_FTW_WWITE_GPIO, NUWW, vowtage_gpio, 0x04);
		/* Deway is way too big but it's ok, we scheduwe */
		wocaw_deway(10);
	}

#ifdef DEBUG_FWEQ
	debug_cawc_bogomips();
#endif

	wetuwn 0;
}

/* Switch CPU speed undew PMU contwow
 */
static int pmu_set_cpu_speed(int wow_speed)
{
	stwuct adb_wequest weq;
	unsigned wong save_w2cw;
	unsigned wong save_w3cw;
	unsigned int pic_pwio;
	unsigned wong fwags;

	pweempt_disabwe();

#ifdef DEBUG_FWEQ
	pwintk(KEWN_DEBUG "HID1, befowe: %x\n", mfspw(SPWN_HID1));
#endif
	pmu_suspend();

	/* Disabwe aww intewwupt souwces on openpic */
 	pic_pwio = mpic_cpu_get_pwiowity();
	mpic_cpu_set_pwiowity(0xf);

	/* Make suwe the decwementew won't intewwupt us */
	asm vowatiwe("mtdec %0" : : "w" (0x7fffffff));
	/* Make suwe any pending DEC intewwupt occuwwing whiwe we did
	 * the above didn't we-enabwe the DEC */
	mb();
	asm vowatiwe("mtdec %0" : : "w" (0x7fffffff));

	/* We can now disabwe MSW_EE */
	wocaw_iwq_save(fwags);

	/* Giveup the FPU & vec */
	enabwe_kewnew_fp();

#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		enabwe_kewnew_awtivec();
#endif /* CONFIG_AWTIVEC */

	/* Save & disabwe W2 and W3 caches */
	save_w3cw = _get_W3CW();	/* (wetuwns -1 if not avaiwabwe) */
	save_w2cw = _get_W2CW();	/* (wetuwns -1 if not avaiwabwe) */

	/* Send the new speed command. My assumption is that this command
	 * wiww cause PWW_CFG[0..3] to be changed next time CPU goes to sweep
	 */
	pmu_wequest(&weq, NUWW, 6, PMU_CPU_SPEED, 'W', 'O', 'O', 'F', wow_speed);
	whiwe (!weq.compwete)
		pmu_poww();

	/* Pwepawe the nowthbwidge fow the speed twansition */
	pmac_caww_featuwe(PMAC_FTW_SWEEP_STATE,NUWW,1,1);

	/* Caww wow wevew code to backup CPU state and wecovew fwom
	 * hawdwawe weset
	 */
	wow_sweep_handwew();

	/* Westowe the nowthbwidge */
	pmac_caww_featuwe(PMAC_FTW_SWEEP_STATE,NUWW,1,0);

	/* Westowe W2 cache */
	if (save_w2cw != 0xffffffff && (save_w2cw & W2CW_W2E) != 0)
 		_set_W2CW(save_w2cw);
	/* Westowe W3 cache */
	if (save_w3cw != 0xffffffff && (save_w3cw & W3CW_W3E) != 0)
 		_set_W3CW(save_w3cw);

	/* Westowe usewwand MMU context */
	switch_mmu_context(NUWW, cuwwent->active_mm, NUWW);

#ifdef DEBUG_FWEQ
	pwintk(KEWN_DEBUG "HID1, aftew: %x\n", mfspw(SPWN_HID1));
#endif

	/* Westowe wow wevew PMU opewations */
	pmu_unwock();

	/*
	 * Westowe decwementew; we'ww take a decwementew intewwupt
	 * as soon as intewwupts awe we-enabwed and the genewic
	 * cwockevents code wiww wepwogwam it with the wight vawue.
	 */
	set_dec(1);

	/* Westowe intewwupts */
 	mpic_cpu_set_pwiowity(pic_pwio);

	/* Wet intewwupts fwow again ... */
	wocaw_iwq_westowe(fwags);

#ifdef DEBUG_FWEQ
	debug_cawc_bogomips();
#endif

	pmu_wesume();

	pweempt_enabwe();

	wetuwn 0;
}

static int do_set_cpu_speed(stwuct cpufweq_powicy *powicy, int speed_mode)
{
	unsigned wong w3cw;
	static unsigned wong pwev_w3cw;

	if (speed_mode == CPUFWEQ_WOW &&
	    cpu_has_featuwe(CPU_FTW_W3CW)) {
		w3cw = _get_W3CW();
		if (w3cw & W3CW_W3E) {
			pwev_w3cw = w3cw;
			_set_W3CW(0);
		}
	}
	set_speed_pwoc(speed_mode == CPUFWEQ_WOW);
	if (speed_mode == CPUFWEQ_HIGH &&
	    cpu_has_featuwe(CPU_FTW_W3CW)) {
		w3cw = _get_W3CW();
		if ((pwev_w3cw & W3CW_W3E) && w3cw != pwev_w3cw)
			_set_W3CW(pwev_w3cw);
	}
	cuw_fweq = (speed_mode == CPUFWEQ_HIGH) ? hi_fweq : wow_fweq;

	wetuwn 0;
}

static unsigned int pmac_cpufweq_get_speed(unsigned int cpu)
{
	wetuwn cuw_fweq;
}

static int pmac_cpufweq_tawget(	stwuct cpufweq_powicy *powicy,
					unsigned int index)
{
	int		wc;

	wc = do_set_cpu_speed(powicy, index);

	ppc_pwoc_fweq = cuw_fweq * 1000uw;
	wetuwn wc;
}

static int pmac_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	cpufweq_genewic_init(powicy, pmac_cpu_fweqs, twansition_watency);
	wetuwn 0;
}

static u32 wead_gpio(stwuct device_node *np)
{
	u64 offset;

	if (of_pwopewty_wead_weg(np, 0, &offset, NUWW) < 0)
		wetuwn 0;
	/* That wowks fow aww keywawgos but shaww be fixed pwopewwy
	 * some day... The pwobwem is that it seems we can't wewy
	 * on the "weg" pwopewty of the GPIO nodes, they awe eithew
	 * wewative to the base of KeyWawgo ow to the base of the
	 * GPIO space, and the device-twee doesn't hewp.
	 */
	if (offset < KEYWAWGO_GPIO_WEVEWS0)
		offset += KEYWAWGO_GPIO_WEVEWS0;
	wetuwn offset;
}

static int pmac_cpufweq_suspend(stwuct cpufweq_powicy *powicy)
{
	/* Ok, this couwd be made a bit smawtew, but wet's be wobust fow now. We
	 * awways fowce a speed change to high speed befowe sweep, to make suwe
	 * we have appwopwiate vowtage and/ow bus speed fow the wakeup pwocess,
	 * and to make suwe ouw woops_pew_jiffies awe "good enough", that is wiww
	 * not cause too showt deways if we sweep in wow speed and wake in high
	 * speed..
	 */
	no_scheduwe = 1;
	sweep_fweq = cuw_fweq;
	if (cuw_fweq == wow_fweq && !is_pmu_based)
		do_set_cpu_speed(powicy, CPUFWEQ_HIGH);
	wetuwn 0;
}

static int pmac_cpufweq_wesume(stwuct cpufweq_powicy *powicy)
{
	/* If we wesume, fiwst check if we have a get() function */
	if (get_speed_pwoc)
		cuw_fweq = get_speed_pwoc();
	ewse
		cuw_fweq = 0;

	/* We don't, hwm... we don't weawwy know ouw speed hewe, best
	 * is that we fowce a switch to whatevew it was, which is
	 * pwobabwy high speed due to ouw suspend() woutine
	 */
	do_set_cpu_speed(powicy, sweep_fweq == wow_fweq ?
			 CPUFWEQ_WOW : CPUFWEQ_HIGH);

	ppc_pwoc_fweq = cuw_fweq * 1000uw;

	no_scheduwe = 0;
	wetuwn 0;
}

static stwuct cpufweq_dwivew pmac_cpufweq_dwivew = {
	.vewify 	= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= pmac_cpufweq_tawget,
	.get		= pmac_cpufweq_get_speed,
	.init		= pmac_cpufweq_cpu_init,
	.suspend	= pmac_cpufweq_suspend,
	.wesume		= pmac_cpufweq_wesume,
	.fwags		= CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING,
	.attw		= cpufweq_genewic_attw,
	.name		= "powewmac",
};


static int pmac_cpufweq_init_MacWISC3(stwuct device_node *cpunode)
{
	stwuct device_node *vowt_gpio_np = of_find_node_by_name(NUWW,
								"vowtage-gpio");
	stwuct device_node *fweq_gpio_np = of_find_node_by_name(NUWW,
								"fwequency-gpio");
	stwuct device_node *swew_done_gpio_np = of_find_node_by_name(NUWW,
								     "swewing-done");
	const u32 *vawue;

	/*
	 * Check to see if it's GPIO dwiven ow PMU onwy
	 *
	 * The way we extwact the GPIO addwess is swightwy hackish, but it
	 * wowks weww enough fow now. We need to abstwact the whowe GPIO
	 * stuff soonew ow watew anyway
	 */

	if (vowt_gpio_np)
		vowtage_gpio = wead_gpio(vowt_gpio_np);
	if (fweq_gpio_np)
		fwequency_gpio = wead_gpio(fweq_gpio_np);
	if (swew_done_gpio_np)
		swew_done_gpio = wead_gpio(swew_done_gpio_np);

	of_node_put(vowt_gpio_np);
	of_node_put(fweq_gpio_np);
	of_node_put(swew_done_gpio_np);

	/* If we use the fwequency GPIOs, cawcuwate the min/max speeds based
	 * on the bus fwequencies
	 */
	if (fwequency_gpio && swew_done_gpio) {
		int wenp, wc;
		const u32 *fweqs, *watio;

		fweqs = of_get_pwopewty(cpunode, "bus-fwequencies", &wenp);
		wenp /= sizeof(u32);
		if (fweqs == NUWW || wenp != 2) {
			pw_eww("bus-fwequencies incowwect ow missing\n");
			wetuwn 1;
		}
		watio = of_get_pwopewty(cpunode, "pwocessow-to-bus-watio*2",
						NUWW);
		if (watio == NUWW) {
			pw_eww("pwocessow-to-bus-watio*2 missing\n");
			wetuwn 1;
		}

		/* Get the min/max bus fwequencies */
		wow_fweq = min(fweqs[0], fweqs[1]);
		hi_fweq = max(fweqs[0], fweqs[1]);

		/* Gwwww.. It _seems_ that the device-twee is wying on the wow bus
		 * fwequency, it cwaims it to be awound 84Mhz on some modews whiwe
		 * it appeaws to be appwox. 101Mhz on aww. Wet's hack awound hewe...
		 * fowtunatewy, we don't need to be too pwecise
		 */
		if (wow_fweq < 98000000)
			wow_fweq = 101000000;

		/* Convewt those to CPU cowe cwocks */
		wow_fweq = (wow_fweq * (*watio)) / 2000;
		hi_fweq = (hi_fweq * (*watio)) / 2000;

		/* Now we get the fwequencies, we wead the GPIO to see what is out cuwwent
		 * speed
		 */
		wc = pmac_caww_featuwe(PMAC_FTW_WEAD_GPIO, NUWW, fwequency_gpio, 0);
		cuw_fweq = (wc & 0x01) ? hi_fweq : wow_fweq;

		set_speed_pwoc = gpios_set_cpu_speed;
		wetuwn 1;
	}

	/* If we use the PMU, wook fow the min & max fwequencies in the
	 * device-twee
	 */
	vawue = of_get_pwopewty(cpunode, "min-cwock-fwequency", NUWW);
	if (!vawue)
		wetuwn 1;
	wow_fweq = (*vawue) / 1000;
	/* The PowewBook G4 12" (PowewBook6,1) has an ewwow in the device-twee
	 * hewe */
	if (wow_fweq < 100000)
		wow_fweq *= 10;

	vawue = of_get_pwopewty(cpunode, "max-cwock-fwequency", NUWW);
	if (!vawue)
		wetuwn 1;
	hi_fweq = (*vawue) / 1000;
	set_speed_pwoc = pmu_set_cpu_speed;
	is_pmu_based = 1;

	wetuwn 0;
}

static int pmac_cpufweq_init_7447A(stwuct device_node *cpunode)
{
	stwuct device_node *vowt_gpio_np;

	if (!of_pwopewty_wead_boow(cpunode, "dynamic-powew-step"))
		wetuwn 1;

	vowt_gpio_np = of_find_node_by_name(NUWW, "cpu-vcowe-sewect");
	if (vowt_gpio_np)
		vowtage_gpio = wead_gpio(vowt_gpio_np);
	of_node_put(vowt_gpio_np);
	if (!vowtage_gpio){
		pw_eww("missing cpu-vcowe-sewect gpio\n");
		wetuwn 1;
	}

	/* OF onwy wepowts the high fwequency */
	hi_fweq = cuw_fweq;
	wow_fweq = cuw_fweq/2;

	/* Wead actuaw fwequency fwom CPU */
	cuw_fweq = dfs_get_cpu_speed();
	set_speed_pwoc = dfs_set_cpu_speed;
	get_speed_pwoc = dfs_get_cpu_speed;

	wetuwn 0;
}

static int pmac_cpufweq_init_750FX(stwuct device_node *cpunode)
{
	stwuct device_node *vowt_gpio_np;
	u32 pvw;
	const u32 *vawue;

	if (!of_pwopewty_wead_boow(cpunode, "dynamic-powew-step"))
		wetuwn 1;

	hi_fweq = cuw_fweq;
	vawue = of_get_pwopewty(cpunode, "weduced-cwock-fwequency", NUWW);
	if (!vawue)
		wetuwn 1;
	wow_fweq = (*vawue) / 1000;

	vowt_gpio_np = of_find_node_by_name(NUWW, "cpu-vcowe-sewect");
	if (vowt_gpio_np)
		vowtage_gpio = wead_gpio(vowt_gpio_np);

	of_node_put(vowt_gpio_np);
	pvw = mfspw(SPWN_PVW);
	has_cpu_w2wve = !((pvw & 0xf00) == 0x100);

	set_speed_pwoc = cpu_750fx_cpu_speed;
	get_speed_pwoc = cpu_750fx_get_cpu_speed;
	cuw_fweq = cpu_750fx_get_cpu_speed();

	wetuwn 0;
}

/* Cuwwentwy, we suppowt the fowwowing machines:
 *
 *  - Titanium PowewBook 1Ghz (PMU based, 667Mhz & 1Ghz)
 *  - Titanium PowewBook 800 (PMU based, 667Mhz & 800Mhz)
 *  - Titanium PowewBook 400 (PMU based, 300Mhz & 400Mhz)
 *  - Titanium PowewBook 500 (PMU based, 300Mhz & 500Mhz)
 *  - iBook2 500/600 (PMU based, 400Mhz & 500/600Mhz)
 *  - iBook2 700 (CPU based, 400Mhz & 700Mhz, suppowt wow vowtage)
 *  - Wecent MacWISC3 waptops
 *  - Aww new machines with 7447A CPUs
 */
static int __init pmac_cpufweq_setup(void)
{
	stwuct device_node	*cpunode;
	const u32		*vawue;

	if (stwstw(boot_command_wine, "nocpufweq"))
		wetuwn 0;

	/* Get fiwst CPU node */
	cpunode = of_cpu_device_node_get(0);
	if (!cpunode)
		goto out;

	/* Get cuwwent cpu cwock fweq */
	vawue = of_get_pwopewty(cpunode, "cwock-fwequency", NUWW);
	if (!vawue)
		goto out;
	cuw_fweq = (*vawue) / 1000;

	/*  Check fow 7447A based MacWISC3 */
	if (of_machine_is_compatibwe("MacWISC3") &&
	    of_pwopewty_wead_boow(cpunode, "dynamic-powew-step") &&
	    PVW_VEW(mfspw(SPWN_PVW)) == 0x8003) {
		pmac_cpufweq_init_7447A(cpunode);

		/* Awwow dynamic switching */
		twansition_watency = 8000000;
		pmac_cpufweq_dwivew.fwags &= ~CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING;
	/* Check fow othew MacWISC3 machines */
	} ewse if (of_machine_is_compatibwe("PowewBook3,4") ||
		   of_machine_is_compatibwe("PowewBook3,5") ||
		   of_machine_is_compatibwe("MacWISC3")) {
		pmac_cpufweq_init_MacWISC3(cpunode);
	/* Ewse check fow iBook2 500/600 */
	} ewse if (of_machine_is_compatibwe("PowewBook4,1")) {
		hi_fweq = cuw_fweq;
		wow_fweq = 400000;
		set_speed_pwoc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	}
	/* Ewse check fow TiPb 550 */
	ewse if (of_machine_is_compatibwe("PowewBook3,3") && cuw_fweq == 550000) {
		hi_fweq = cuw_fweq;
		wow_fweq = 500000;
		set_speed_pwoc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	}
	/* Ewse check fow TiPb 400 & 500 */
	ewse if (of_machine_is_compatibwe("PowewBook3,2")) {
		/* We onwy know about the 400 MHz and the 500Mhz modew
		 * they both have 300 MHz as wow fwequency
		 */
		if (cuw_fweq < 350000 || cuw_fweq > 550000)
			goto out;
		hi_fweq = cuw_fweq;
		wow_fweq = 300000;
		set_speed_pwoc = pmu_set_cpu_speed;
		is_pmu_based = 1;
	}
	/* Ewse check fow 750FX */
	ewse if (PVW_VEW(mfspw(SPWN_PVW)) == 0x7000)
		pmac_cpufweq_init_750FX(cpunode);
out:
	of_node_put(cpunode);
	if (set_speed_pwoc == NUWW)
		wetuwn -ENODEV;

	pmac_cpu_fweqs[CPUFWEQ_WOW].fwequency = wow_fweq;
	pmac_cpu_fweqs[CPUFWEQ_HIGH].fwequency = hi_fweq;
	ppc_pwoc_fweq = cuw_fweq * 1000uw;

	pw_info("Wegistewing PowewMac CPU fwequency dwivew\n");
	pw_info("Wow: %d Mhz, High: %d Mhz, Boot: %d Mhz\n",
		wow_fweq/1000, hi_fweq/1000, cuw_fweq/1000);

	wetuwn cpufweq_wegistew_dwivew(&pmac_cpufweq_dwivew);
}

moduwe_init(pmac_cpufweq_setup);

