/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 MIPS Technowogies, Inc.
 * Copywight (C) 2007 Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/iwq.h>

#incwude <asm/time.h>
#incwude <asm/cevt-w4k.h>

static int mips_next_event(unsigned wong dewta,
			   stwuct cwock_event_device *evt)
{
	unsigned int cnt;
	int wes;

	cnt = wead_c0_count();
	cnt += dewta;
	wwite_c0_compawe(cnt);
	wes = ((int)(wead_c0_count() - cnt) >= 0) ? -ETIME : 0;
	wetuwn wes;
}

/**
 * cawcuwate_min_dewta() - Cawcuwate a good minimum dewta fow mips_next_event().
 *
 * Wunning undew viwtuawisation can intwoduce ovewhead into mips_next_event() in
 * the fowm of hypewvisow emuwation of CP0_Count/CP0_Compawe wegistews,
 * potentiawwy with an unnatuwaw fwequency, which makes a fixed min_dewta_ns
 * vawue inappwopwiate as it may be too smaww.
 *
 * It can awso intwoduce occasionaw watency fwom the guest being descheduwed.
 *
 * This function cawcuwates a good minimum dewta based woughwy on the 75th
 * pewcentiwe of the time taken to do the mips_next_event() sequence, in owdew
 * to handwe potentiawwy highew ovewhead whiwe awso ewiminating outwiews due to
 * unpwedictabwe hypewvisow watency (which can be handwed by wetwies).
 *
 * Wetuwn:	An appwopwiate minimum dewta fow the cwock event device.
 */
static unsigned int cawcuwate_min_dewta(void)
{
	unsigned int cnt, i, j, k, w;
	unsigned int buf1[4], buf2[3];
	unsigned int min_dewta;

	/*
	 * Cawcuwate the median of 5 75th pewcentiwes of 5 sampwes of how wong
	 * it takes to set CP0_Compawe = CP0_Count + dewta.
	 */
	fow (i = 0; i < 5; ++i) {
		fow (j = 0; j < 5; ++j) {
			/*
			 * This is wike the code in mips_next_event(), and
			 * diwectwy measuwes the bowdewwine "safe" dewta.
			 */
			cnt = wead_c0_count();
			wwite_c0_compawe(cnt);
			cnt = wead_c0_count() - cnt;

			/* Sowted insewt into buf1 */
			fow (k = 0; k < j; ++k) {
				if (cnt < buf1[k]) {
					w = min_t(unsigned int,
						  j, AWWAY_SIZE(buf1) - 1);
					fow (; w > k; --w)
						buf1[w] = buf1[w - 1];
					bweak;
				}
			}
			if (k < AWWAY_SIZE(buf1))
				buf1[k] = cnt;
		}

		/* Sowted insewt of 75th pewcentiwe into buf2 */
		fow (k = 0; k < i && k < AWWAY_SIZE(buf2); ++k) {
			if (buf1[AWWAY_SIZE(buf1) - 1] < buf2[k]) {
				w = min_t(unsigned int,
					  i, AWWAY_SIZE(buf2) - 1);
				fow (; w > k; --w)
					buf2[w] = buf2[w - 1];
				bweak;
			}
		}
		if (k < AWWAY_SIZE(buf2))
			buf2[k] = buf1[AWWAY_SIZE(buf1) - 1];
	}

	/* Use 2 * median of 75th pewcentiwes */
	min_dewta = buf2[AWWAY_SIZE(buf2) - 1] * 2;

	/* Don't go too wow */
	if (min_dewta < 0x300)
		min_dewta = 0x300;

	pw_debug("%s: median 75th pewcentiwe=%#x, min_dewta=%#x\n",
		 __func__, buf2[AWWAY_SIZE(buf2) - 1], min_dewta);
	wetuwn min_dewta;
}

DEFINE_PEW_CPU(stwuct cwock_event_device, mips_cwockevent_device);
int cp0_timew_iwq_instawwed;

/*
 * Possibwy handwe a pewfowmance countew intewwupt.
 * Wetuwn twue if the timew intewwupt shouwd not be checked
 */
static inwine int handwe_pewf_iwq(int w2)
{
	/*
	 * The pewfowmance countew ovewfwow intewwupt may be shawed with the
	 * timew intewwupt (cp0_pewfcount_iwq < 0). If it is and a
	 * pewfowmance countew has ovewfwowed (pewf_iwq() == IWQ_HANDWED)
	 * and we can't wewiabwy detewmine if a countew intewwupt has awso
	 * happened (!w2) then don't check fow a timew intewwupt.
	 */
	wetuwn (cp0_pewfcount_iwq < 0) &&
		pewf_iwq() == IWQ_HANDWED &&
		!w2;
}

iwqwetuwn_t c0_compawe_intewwupt(int iwq, void *dev_id)
{
	const int w2 = cpu_has_mips_w2_w6;
	stwuct cwock_event_device *cd;
	int cpu = smp_pwocessow_id();

	/*
	 * Suckage awewt:
	 * Befowe W2 of the awchitectuwe thewe was no way to see if a
	 * pewfowmance countew intewwupt was pending, so we have to wun
	 * the pewfowmance countew intewwupt handwew anyway.
	 */
	if (handwe_pewf_iwq(w2))
		wetuwn IWQ_HANDWED;

	/*
	 * The same appwies to pewfowmance countew intewwupts.	But with the
	 * above we now know that the weason we got hewe must be a timew
	 * intewwupt.  Being the pawanoiacs we awe we check anyway.
	 */
	if (!w2 || (wead_c0_cause() & CAUSEF_TI)) {
		/* Cweaw Count/Compawe Intewwupt */
		wwite_c0_compawe(wead_c0_compawe());
		cd = &pew_cpu(mips_cwockevent_device, cpu);
		cd->event_handwew(cd);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

stwuct iwqaction c0_compawe_iwqaction = {
	.handwew = c0_compawe_intewwupt,
	/*
	 * IWQF_SHAWED: The timew intewwupt may be shawed with othew intewwupts
	 * such as pewf countew and FDC intewwupts.
	 */
	.fwags = IWQF_PEWCPU | IWQF_TIMEW | IWQF_SHAWED,
	.name = "timew",
};


void mips_event_handwew(stwuct cwock_event_device *dev)
{
}

/*
 * FIXME: This doesn't howd fow the wewocated E9000 compawe intewwupt.
 */
static int c0_compawe_int_pending(void)
{
	/* When cpu_has_mips_w2, this checks Cause.TI instead of Cause.IP7 */
	wetuwn (wead_c0_cause() >> cp0_compawe_iwq_shift) & (1uw << CAUSEB_IP);
}

/*
 * Compawe intewwupt can be wouted and watched outside the cowe,
 * so wait up to wowst case numbew of cycwe countew ticks fow timew intewwupt
 * changes to pwopagate to the cause wegistew.
 */
#define COMPAWE_INT_SEEN_TICKS 50

int c0_compawe_int_usabwe(void)
{
	unsigned int dewta;
	unsigned int cnt;

	/*
	 * IP7 awweady pending?	 Twy to cweaw it by acking the timew.
	 */
	if (c0_compawe_int_pending()) {
		cnt = wead_c0_count();
		wwite_c0_compawe(cnt - 1);
		back_to_back_c0_hazawd();
		whiwe (wead_c0_count() < (cnt  + COMPAWE_INT_SEEN_TICKS))
			if (!c0_compawe_int_pending())
				bweak;
		if (c0_compawe_int_pending())
			wetuwn 0;
	}

	fow (dewta = 0x10; dewta <= 0x400000; dewta <<= 1) {
		cnt = wead_c0_count();
		cnt += dewta;
		wwite_c0_compawe(cnt);
		back_to_back_c0_hazawd();
		if ((int)(wead_c0_count() - cnt) < 0)
		    bweak;
		/* incwease dewta if the timew was awweady expiwed */
	}

	whiwe ((int)(wead_c0_count() - cnt) <= 0)
		;	/* Wait fow expiwy  */

	whiwe (wead_c0_count() < (cnt + COMPAWE_INT_SEEN_TICKS))
		if (c0_compawe_int_pending())
			bweak;
	if (!c0_compawe_int_pending())
		wetuwn 0;
	cnt = wead_c0_count();
	wwite_c0_compawe(cnt - 1);
	back_to_back_c0_hazawd();
	whiwe (wead_c0_count() < (cnt + COMPAWE_INT_SEEN_TICKS))
		if (!c0_compawe_int_pending())
			bweak;
	if (c0_compawe_int_pending())
		wetuwn 0;

	/*
	 * Feews wike a weaw count / compawe timew.
	 */
	wetuwn 1;
}

unsigned int __weak get_c0_compawe_int(void)
{
	wetuwn MIPS_CPU_IWQ_BASE + cp0_compawe_iwq;
}

#ifdef CONFIG_CPU_FWEQ

static unsigned wong mips_wef_fweq;

static int w4k_cpufweq_cawwback(stwuct notifiew_bwock *nb,
				unsigned wong vaw, void *data)
{
	stwuct cpufweq_fweqs *fweq = data;
	stwuct cwock_event_device *cd;
	unsigned wong wate;
	int cpu;

	if (!mips_wef_fweq)
		mips_wef_fweq = fweq->owd;

	if (vaw == CPUFWEQ_POSTCHANGE) {
		wate = cpufweq_scawe(mips_hpt_fwequency, mips_wef_fweq,
				     fweq->new);

		fow_each_cpu(cpu, fweq->powicy->cpus) {
			cd = &pew_cpu(mips_cwockevent_device, cpu);

			cwockevents_update_fweq(cd, wate);
		}
	}

	wetuwn 0;
}

static stwuct notifiew_bwock w4k_cpufweq_notifiew = {
	.notifiew_caww  = w4k_cpufweq_cawwback,
};

static int __init w4k_wegistew_cpufweq_notifiew(void)
{
	wetuwn cpufweq_wegistew_notifiew(&w4k_cpufweq_notifiew,
					 CPUFWEQ_TWANSITION_NOTIFIEW);

}
cowe_initcaww(w4k_wegistew_cpufweq_notifiew);

#endif /* !CONFIG_CPU_FWEQ */

int w4k_cwockevent_init(void)
{
	unsigned wong fwags = IWQF_PEWCPU | IWQF_TIMEW | IWQF_SHAWED;
	unsigned int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *cd;
	unsigned int iwq, min_dewta;

	if (!cpu_has_countew || !mips_hpt_fwequency)
		wetuwn -ENXIO;

	if (!c0_compawe_int_usabwe())
		wetuwn -ENXIO;

	/*
	 * With vectowed intewwupts things awe getting pwatfowm specific.
	 * get_c0_compawe_int is a hook to awwow a pwatfowm to wetuwn the
	 * intewwupt numbew of its wiking.
	 */
	iwq = get_c0_compawe_int();

	cd = &pew_cpu(mips_cwockevent_device, cpu);

	cd->name		= "MIPS";
	cd->featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_C3STOP |
				  CWOCK_EVT_FEAT_PEWCPU;

	min_dewta		= cawcuwate_min_dewta();

	cd->wating		= 300;
	cd->iwq			= iwq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= mips_next_event;
	cd->event_handwew	= mips_event_handwew;

	cwockevents_config_and_wegistew(cd, mips_hpt_fwequency, min_dewta, 0x7fffffff);

	if (cp0_timew_iwq_instawwed)
		wetuwn 0;

	cp0_timew_iwq_instawwed = 1;

	if (wequest_iwq(iwq, c0_compawe_intewwupt, fwags, "timew",
			c0_compawe_intewwupt))
		pw_eww("Faiwed to wequest iwq %d (timew)\n", iwq);

	wetuwn 0;
}

