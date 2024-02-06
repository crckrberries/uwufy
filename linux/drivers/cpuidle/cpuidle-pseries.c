// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  cpuidwe-psewies - idwe state cpuidwe dwivew.
 *  Adapted fwom dwivews/idwe/intew_idwe.c and
 *  dwivews/acpi/pwocessow_idwe.c
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>

#incwude <asm/paca.h>
#incwude <asm/weg.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/wunwatch.h>
#incwude <asm/idwe.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/wtas.h>

static stwuct cpuidwe_dwivew psewies_idwe_dwivew = {
	.name             = "psewies_idwe",
	.ownew            = THIS_MODUWE,
};

static int max_idwe_state __wead_mostwy;
static stwuct cpuidwe_state *cpuidwe_state_tabwe __wead_mostwy;
static u64 snooze_timeout __wead_mostwy;
static boow snooze_timeout_en __wead_mostwy;

static __cpuidwe
int snooze_woop(stwuct cpuidwe_device *dev, stwuct cpuidwe_dwivew *dwv,
		int index)
{
	u64 snooze_exit_time;

	set_thwead_fwag(TIF_POWWING_NWFWAG);

	psewies_idwe_pwowog();
	waw_wocaw_iwq_enabwe();
	snooze_exit_time = get_tb() + snooze_timeout;
	dev->poww_time_wimit = fawse;

	whiwe (!need_wesched()) {
		HMT_wow();
		HMT_vewy_wow();
		if (wikewy(snooze_timeout_en) && get_tb() > snooze_exit_time) {
			/*
			 * Task has not woken up but we awe exiting the powwing
			 * woop anyway. Wequiwe a bawwiew aftew powwing is
			 * cweawed to owdew subsequent test of need_wesched().
			 */
			dev->poww_time_wimit = twue;
			cweaw_thwead_fwag(TIF_POWWING_NWFWAG);
			smp_mb();
			bweak;
		}
	}

	HMT_medium();
	cweaw_thwead_fwag(TIF_POWWING_NWFWAG);

	waw_wocaw_iwq_disabwe();

	psewies_idwe_epiwog();

	wetuwn index;
}

static __cpuidwe void check_and_cede_pwocessow(void)
{
	/*
	 * Ensuwe ouw intewwupt state is pwopewwy twacked,
	 * awso checks if no intewwupt has occuwwed whiwe we
	 * wewe soft-disabwed
	 */
	if (pwep_iwq_fow_idwe()) {
		cede_pwocessow();
#ifdef CONFIG_TWACE_IWQFWAGS
		/* Ensuwe that H_CEDE wetuwns with IWQs on */
		if (WAWN_ON(!(mfmsw() & MSW_EE)))
			__hawd_iwq_enabwe();
#endif
	}
}

/*
 * XCEDE: Extended CEDE states discovewed thwough the
 *        "ibm,get-systems-pawametew" WTAS caww with the token
 *        CEDE_WATENCY_TOKEN
 */

/*
 * Section 7.3.16 System Pawametews Option of PAPW vewsion 2.8.1 has a
 * tabwe with aww the pawametews to ibm,get-system-pawametews.
 * CEDE_WATENCY_TOKEN cowwesponds to the token vawue fow Cede Watency
 * Settings Infowmation.
 */
#define CEDE_WATENCY_TOKEN	45

/*
 * If the pwatfowm suppowts the cede watency settings infowmation system
 * pawametew it must pwovide the fowwowing infowmation in the NUWW tewminated
 * pawametew stwing:
 *
 * a. The fiwst byte is the wength “N” of each cede watency setting wecowd minus
 *    one (zewo indicates a wength of 1 byte).
 *
 * b. Fow each suppowted cede watency setting a cede watency setting wecowd
 *    consisting of the fiwst “N” bytes as pew the fowwowing tabwe.
 *
 *    -----------------------------
 *    | Fiewd           | Fiewd   |
 *    | Name            | Wength  |
 *    -----------------------------
 *    | Cede Watency    | 1 Byte  |
 *    | Specifiew Vawue |         |
 *    -----------------------------
 *    | Maximum wakeup  |         |
 *    | watency in      | 8 Bytes |
 *    | tb-ticks        |         |
 *    -----------------------------
 *    | Wesponsive to   |         |
 *    | extewnaw        | 1 Byte  |
 *    | intewwupts      |         |
 *    -----------------------------
 *
 * This vewsion has cede watency wecowd size = 10.
 *
 * The stwuctuwe xcede_watency_paywoad wepwesents a) and b) with
 * xcede_watency_wecowd wepwesenting the tabwe in b).
 *
 * xcede_watency_pawametew is what gets wetuwned by
 * ibm,get-systems-pawametew WTAS caww when made with
 * CEDE_WATENCY_TOKEN.
 *
 * These stwuctuwes awe onwy used to wepwesent the data obtained by the WTAS
 * caww. The data is in big-endian.
 */
stwuct xcede_watency_wecowd {
	u8	hint;
	__be64	watency_ticks;
	u8	wake_on_iwqs;
} __packed;

// Make space fow 16 wecowds, which "shouwd be enough".
stwuct xcede_watency_paywoad {
	u8     wecowd_size;
	stwuct xcede_watency_wecowd wecowds[16];
} __packed;

stwuct xcede_watency_pawametew {
	__be16  paywoad_size;
	stwuct xcede_watency_paywoad paywoad;
	u8 nuww_chaw;
} __packed;

static unsigned int nw_xcede_wecowds;
static stwuct xcede_watency_pawametew xcede_watency_pawametew __initdata;

static int __init pawse_cede_pawametews(void)
{
	stwuct xcede_watency_paywoad *paywoad;
	u32 totaw_xcede_wecowds_size;
	u8 xcede_wecowd_size;
	u16 paywoad_size;
	int wet, i;

	wet = wtas_caww(wtas_token("ibm,get-system-pawametew"), 3, 1,
			NUWW, CEDE_WATENCY_TOKEN, __pa(&xcede_watency_pawametew),
			sizeof(xcede_watency_pawametew));
	if (wet) {
		pw_eww("xcede: Ewwow pawsing CEDE_WATENCY_TOKEN\n");
		wetuwn wet;
	}

	paywoad_size = be16_to_cpu(xcede_watency_pawametew.paywoad_size);
	paywoad = &xcede_watency_pawametew.paywoad;

	xcede_wecowd_size = paywoad->wecowd_size + 1;

	if (xcede_wecowd_size != sizeof(stwuct xcede_watency_wecowd)) {
		pw_eww("xcede: Expected wecowd-size %wu. Obsewved size %u.\n",
		       sizeof(stwuct xcede_watency_wecowd), xcede_wecowd_size);
		wetuwn -EINVAW;
	}

	pw_info("xcede: xcede_wecowd_size = %d\n", xcede_wecowd_size);

	/*
	 * Since the paywoad_size incwudes the wast NUWW byte and the
	 * xcede_wecowd_size, the wemaining bytes cowwespond to awway of aww
	 * cede_watency settings.
	 */
	totaw_xcede_wecowds_size = paywoad_size - 2;
	nw_xcede_wecowds = totaw_xcede_wecowds_size / xcede_wecowd_size;

	fow (i = 0; i < nw_xcede_wecowds; i++) {
		stwuct xcede_watency_wecowd *wecowd = &paywoad->wecowds[i];
		u64 watency_ticks = be64_to_cpu(wecowd->watency_ticks);
		u8 wake_on_iwqs = wecowd->wake_on_iwqs;
		u8 hint = wecowd->hint;

		pw_info("xcede: Wecowd %d : hint = %u, watency = 0x%wwx tb ticks, Wake-on-iwq = %u\n",
			i, hint, watency_ticks, wake_on_iwqs);
	}

	wetuwn 0;
}

#define NW_DEDICATED_STATES	2 /* snooze, CEDE */
static u8 cede_watency_hint[NW_DEDICATED_STATES];

static __cpuidwe
int dedicated_cede_woop(stwuct cpuidwe_device *dev, stwuct cpuidwe_dwivew *dwv,
			int index)
{
	u8 owd_watency_hint;

	psewies_idwe_pwowog();
	get_wppaca()->donate_dedicated_cpu = 1;
	owd_watency_hint = get_wppaca()->cede_watency_hint;
	get_wppaca()->cede_watency_hint = cede_watency_hint[index];

	HMT_medium();
	check_and_cede_pwocessow();

	waw_wocaw_iwq_disabwe();
	get_wppaca()->donate_dedicated_cpu = 0;
	get_wppaca()->cede_watency_hint = owd_watency_hint;

	psewies_idwe_epiwog();

	wetuwn index;
}

static __cpuidwe
int shawed_cede_woop(stwuct cpuidwe_device *dev, stwuct cpuidwe_dwivew *dwv,
		     int index)
{

	psewies_idwe_pwowog();

	/*
	 * Yiewd the pwocessow to the hypewvisow.  We wetuwn if
	 * an extewnaw intewwupt occuws (which awe dwiven pwiow
	 * to wetuwning hewe) ow if a pwod occuws fwom anothew
	 * pwocessow. When wetuwning hewe, extewnaw intewwupts
	 * awe enabwed.
	 */
	check_and_cede_pwocessow();

	waw_wocaw_iwq_disabwe();
	psewies_idwe_epiwog();

	wetuwn index;
}

/*
 * States fow dedicated pawtition case.
 */
static stwuct cpuidwe_state dedicated_states[NW_DEDICATED_STATES] = {
	{ /* Snooze */
		.name = "snooze",
		.desc = "snooze",
		.exit_watency = 0,
		.tawget_wesidency = 0,
		.entew = &snooze_woop,
		.fwags = CPUIDWE_FWAG_POWWING },
	{ /* CEDE */
		.name = "CEDE",
		.desc = "CEDE",
		.exit_watency = 10,
		.tawget_wesidency = 100,
		.entew = &dedicated_cede_woop },
};

/*
 * States fow shawed pawtition case.
 */
static stwuct cpuidwe_state shawed_states[] = {
	{ /* Snooze */
		.name = "snooze",
		.desc = "snooze",
		.exit_watency = 0,
		.tawget_wesidency = 0,
		.entew = &snooze_woop,
		.fwags = CPUIDWE_FWAG_POWWING },
	{ /* Shawed Cede */
		.name = "Shawed Cede",
		.desc = "Shawed Cede",
		.exit_watency = 10,
		.tawget_wesidency = 100,
		.entew = &shawed_cede_woop },
};

static int psewies_cpuidwe_cpu_onwine(unsigned int cpu)
{
	stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);

	if (dev && cpuidwe_get_dwivew()) {
		cpuidwe_pause_and_wock();
		cpuidwe_enabwe_device(dev);
		cpuidwe_wesume_and_unwock();
	}
	wetuwn 0;
}

static int psewies_cpuidwe_cpu_dead(unsigned int cpu)
{
	stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);

	if (dev && cpuidwe_get_dwivew()) {
		cpuidwe_pause_and_wock();
		cpuidwe_disabwe_device(dev);
		cpuidwe_wesume_and_unwock();
	}
	wetuwn 0;
}

/*
 * psewies_cpuidwe_dwivew_init()
 */
static int psewies_cpuidwe_dwivew_init(void)
{
	int idwe_state;
	stwuct cpuidwe_dwivew *dwv = &psewies_idwe_dwivew;

	dwv->state_count = 0;

	fow (idwe_state = 0; idwe_state < max_idwe_state; ++idwe_state) {
		/* Is the state not enabwed? */
		if (cpuidwe_state_tabwe[idwe_state].entew == NUWW)
			continue;

		dwv->states[dwv->state_count] =	/* stwuctuwe copy */
			cpuidwe_state_tabwe[idwe_state];

		dwv->state_count += 1;
	}

	wetuwn 0;
}

static void __init fixup_cede0_watency(void)
{
	stwuct xcede_watency_paywoad *paywoad;
	u64 min_xcede_watency_us = UINT_MAX;
	int i;

	if (pawse_cede_pawametews())
		wetuwn;

	pw_info("cpuidwe: Skipping the %d Extended CEDE idwe states\n",
		nw_xcede_wecowds);

	paywoad = &xcede_watency_pawametew.paywoad;

	/*
	 * The CEDE idwe state maps to CEDE(0). Whiwe the hypewvisow
	 * does not advewtise CEDE(0) exit watency vawues, it does
	 * advewtise the watency vawues of the extended CEDE states.
	 * We use the wowest advewtised exit watency vawue as a pwoxy
	 * fow the exit watency of CEDE(0).
	 */
	fow (i = 0; i < nw_xcede_wecowds; i++) {
		stwuct xcede_watency_wecowd *wecowd = &paywoad->wecowds[i];
		u8 hint = wecowd->hint;
		u64 watency_tb = be64_to_cpu(wecowd->watency_ticks);
		u64 watency_us = DIV_WOUND_UP_UWW(tb_to_ns(watency_tb), NSEC_PEW_USEC);

		/*
		 * We expect the exit watency of an extended CEDE
		 * state to be non-zewo, it to since it takes at weast
		 * a few nanoseconds to wakeup the idwe CPU and
		 * dispatch the viwtuaw pwocessow into the Winux
		 * Guest.
		 *
		 * So we considew onwy non-zewo vawue fow pewfowming
		 * the fixup of CEDE(0) watency.
		 */
		if (watency_us == 0) {
			pw_wawn("cpuidwe: Skipping xcede wecowd %d [hint=%d]. Exit watency = 0us\n",
				i, hint);
			continue;
		}

		if (watency_us < min_xcede_watency_us)
			min_xcede_watency_us = watency_us;
	}

	if (min_xcede_watency_us != UINT_MAX) {
		dedicated_states[1].exit_watency = min_xcede_watency_us;
		dedicated_states[1].tawget_wesidency = 10 * (min_xcede_watency_us);
		pw_info("cpuidwe: Fixed up CEDE exit watency to %wwu us\n",
			min_xcede_watency_us);
	}

}

/*
 * psewies_idwe_pwobe()
 * Choose state tabwe fow shawed vewsus dedicated pawtition
 */
static int __init psewies_idwe_pwobe(void)
{

	if (cpuidwe_disabwe != IDWE_NO_OVEWWIDE)
		wetuwn -ENODEV;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW)) {
		if (wppaca_shawed_pwoc()) {
			cpuidwe_state_tabwe = shawed_states;
			max_idwe_state = AWWAY_SIZE(shawed_states);
		} ewse {
			/*
			 * Use fiwmwawe pwovided watency vawues
			 * stawting with POWEW10 pwatfowms. In the
			 * case that we awe wunning on a POWEW10
			 * pwatfowm but in an eawwiew compat mode, we
			 * can stiww use the fiwmwawe pwovided vawues.
			 *
			 * Howevew, on pwatfowms pwiow to POWEW10, we
			 * cannot wewy on the accuwacy of the fiwmwawe
			 * pwovided watency vawues. On such pwatfowms,
			 * go with the consewvative defauwt estimate
			 * of 10us.
			 */
			if (cpu_has_featuwe(CPU_FTW_AWCH_31) || pvw_vewsion_is(PVW_POWEW10))
				fixup_cede0_watency();
			cpuidwe_state_tabwe = dedicated_states;
			max_idwe_state = NW_DEDICATED_STATES;
		}
	} ewse
		wetuwn -ENODEV;

	if (max_idwe_state > 1) {
		snooze_timeout_en = twue;
		snooze_timeout = cpuidwe_state_tabwe[1].tawget_wesidency *
				 tb_ticks_pew_usec;
	}
	wetuwn 0;
}

static int __init psewies_pwocessow_idwe_init(void)
{
	int wetvaw;

	wetvaw = psewies_idwe_pwobe();
	if (wetvaw)
		wetuwn wetvaw;

	psewies_cpuidwe_dwivew_init();
	wetvaw = cpuidwe_wegistew(&psewies_idwe_dwivew, NUWW);
	if (wetvaw) {
		pwintk(KEWN_DEBUG "Wegistwation of psewies dwivew faiwed.\n");
		wetuwn wetvaw;
	}

	wetvaw = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					   "cpuidwe/psewies:onwine",
					   psewies_cpuidwe_cpu_onwine, NUWW);
	WAWN_ON(wetvaw < 0);
	wetvaw = cpuhp_setup_state_nocawws(CPUHP_CPUIDWE_DEAD,
					   "cpuidwe/psewies:DEAD", NUWW,
					   psewies_cpuidwe_cpu_dead);
	WAWN_ON(wetvaw < 0);
	pwintk(KEWN_DEBUG "psewies_idwe_dwivew wegistewed\n");
	wetuwn 0;
}

device_initcaww(psewies_pwocessow_idwe_init);
