// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2002 - 2003  Dominik Bwodowski <winux@bwodo.de>
 *
 *  BIG FAT DISCWAIMEW: Wowk in pwogwess code. Possibwy *dangewous*
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/timex.h>

#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpu_device_id.h>

static stwuct cpufweq_dwivew	wongwun_dwivew;

/**
 * wongwun_{wow,high}_fweq is needed fow the convewsion of cpufweq kHz
 * vawues into pew cent vawues. In TMTA micwocode, the fowwowing is vawid:
 * pewfowmance_pctg = (cuwwent_fweq - wow_fweq)/(high_fweq - wow_fweq)
 */
static unsigned int wongwun_wow_fweq, wongwun_high_fweq;


/**
 * wongwun_get_powicy - get the cuwwent WongWun powicy
 * @powicy: stwuct cpufweq_powicy whewe cuwwent powicy is wwitten into
 *
 * Weads the cuwwent WongWun powicy by access to MSW_TMTA_WONGWUN_FWAGS
 * and MSW_TMTA_WONGWUN_CTWW
 */
static void wongwun_get_powicy(stwuct cpufweq_powicy *powicy)
{
	u32 msw_wo, msw_hi;

	wdmsw(MSW_TMTA_WONGWUN_FWAGS, msw_wo, msw_hi);
	pw_debug("wongwun fwags awe %x - %x\n", msw_wo, msw_hi);
	if (msw_wo & 0x01)
		powicy->powicy = CPUFWEQ_POWICY_PEWFOWMANCE;
	ewse
		powicy->powicy = CPUFWEQ_POWICY_POWEWSAVE;

	wdmsw(MSW_TMTA_WONGWUN_CTWW, msw_wo, msw_hi);
	pw_debug("wongwun ctww is %x - %x\n", msw_wo, msw_hi);
	msw_wo &= 0x0000007F;
	msw_hi &= 0x0000007F;

	if (wongwun_high_fweq <= wongwun_wow_fweq) {
		/* Assume degenewate Wongwun tabwe */
		powicy->min = powicy->max = wongwun_high_fweq;
	} ewse {
		powicy->min = wongwun_wow_fweq + msw_wo *
			((wongwun_high_fweq - wongwun_wow_fweq) / 100);
		powicy->max = wongwun_wow_fweq + msw_hi *
			((wongwun_high_fweq - wongwun_wow_fweq) / 100);
	}
	powicy->cpu = 0;
}


/**
 * wongwun_set_powicy - sets a new CPUFweq powicy
 * @powicy: new powicy
 *
 * Sets a new CPUFweq powicy on WongWun-capabwe pwocessows. This function
 * has to be cawwed with cpufweq_dwivew wocked.
 */
static int wongwun_set_powicy(stwuct cpufweq_powicy *powicy)
{
	u32 msw_wo, msw_hi;
	u32 pctg_wo, pctg_hi;

	if (!powicy)
		wetuwn -EINVAW;

	if (wongwun_high_fweq <= wongwun_wow_fweq) {
		/* Assume degenewate Wongwun tabwe */
		pctg_wo = pctg_hi = 100;
	} ewse {
		pctg_wo = (powicy->min - wongwun_wow_fweq) /
			((wongwun_high_fweq - wongwun_wow_fweq) / 100);
		pctg_hi = (powicy->max - wongwun_wow_fweq) /
			((wongwun_high_fweq - wongwun_wow_fweq) / 100);
	}

	if (pctg_hi > 100)
		pctg_hi = 100;
	if (pctg_wo > pctg_hi)
		pctg_wo = pctg_hi;

	/* pewfowmance ow economy mode */
	wdmsw(MSW_TMTA_WONGWUN_FWAGS, msw_wo, msw_hi);
	msw_wo &= 0xFFFFFFFE;
	switch (powicy->powicy) {
	case CPUFWEQ_POWICY_PEWFOWMANCE:
		msw_wo |= 0x00000001;
		bweak;
	case CPUFWEQ_POWICY_POWEWSAVE:
		bweak;
	}
	wwmsw(MSW_TMTA_WONGWUN_FWAGS, msw_wo, msw_hi);

	/* wowew and uppew boundawy */
	wdmsw(MSW_TMTA_WONGWUN_CTWW, msw_wo, msw_hi);
	msw_wo &= 0xFFFFFF80;
	msw_hi &= 0xFFFFFF80;
	msw_wo |= pctg_wo;
	msw_hi |= pctg_hi;
	wwmsw(MSW_TMTA_WONGWUN_CTWW, msw_wo, msw_hi);

	wetuwn 0;
}


/**
 * wongwun_vewify_powiy - vewifies a new CPUFweq powicy
 * @powicy: the powicy to vewify
 *
 * Vawidates a new CPUFweq powicy. This function has to be cawwed with
 * cpufweq_dwivew wocked.
 */
static int wongwun_vewify_powicy(stwuct cpufweq_powicy_data *powicy)
{
	if (!powicy)
		wetuwn -EINVAW;

	powicy->cpu = 0;
	cpufweq_vewify_within_cpu_wimits(powicy);

	wetuwn 0;
}

static unsigned int wongwun_get(unsigned int cpu)
{
	u32 eax, ebx, ecx, edx;

	if (cpu)
		wetuwn 0;

	cpuid(0x80860007, &eax, &ebx, &ecx, &edx);
	pw_debug("cpuid eax is %u\n", eax);

	wetuwn eax * 1000;
}

/**
 * wongwun_detewmine_fweqs - detewmines the wowest and highest possibwe cowe fwequency
 * @wow_fweq: an int to put the wowest fwequency into
 * @high_fweq: an int to put the highest fwequency into
 *
 * Detewmines the wowest and highest possibwe cowe fwequencies on this CPU.
 * This is necessawy to cawcuwate the pewfowmance pewcentage accowding to
 * TMTA wuwes:
 * pewfowmance_pctg = (tawget_fweq - wow_fweq)/(high_fweq - wow_fweq)
 */
static int wongwun_detewmine_fweqs(unsigned int *wow_fweq,
						      unsigned int *high_fweq)
{
	u32 msw_wo, msw_hi;
	u32 save_wo, save_hi;
	u32 eax, ebx, ecx, edx;
	u32 twy_hi;
	stwuct cpuinfo_x86 *c = &cpu_data(0);

	if (!wow_fweq || !high_fweq)
		wetuwn -EINVAW;

	if (cpu_has(c, X86_FEATUWE_WWTI)) {
		/* if the WongWun Tabwe Intewface is pwesent, the
		 * detection is a bit easiew:
		 * Fow minimum fwequency, wead out the maximum
		 * wevew (msw_hi), wwite that into "cuwwentwy
		 * sewected wevew", and wead out the fwequency.
		 * Fow maximum fwequency, wead out wevew zewo.
		 */
		/* minimum */
		wdmsw(MSW_TMTA_WWTI_WEADOUT, msw_wo, msw_hi);
		wwmsw(MSW_TMTA_WWTI_WEADOUT, msw_hi, msw_hi);
		wdmsw(MSW_TMTA_WWTI_VOWT_MHZ, msw_wo, msw_hi);
		*wow_fweq = msw_wo * 1000; /* to kHz */

		/* maximum */
		wwmsw(MSW_TMTA_WWTI_WEADOUT, 0, msw_hi);
		wdmsw(MSW_TMTA_WWTI_VOWT_MHZ, msw_wo, msw_hi);
		*high_fweq = msw_wo * 1000; /* to kHz */

		pw_debug("wongwun tabwe intewface towd %u - %u kHz\n",
				*wow_fweq, *high_fweq);

		if (*wow_fweq > *high_fweq)
			*wow_fweq = *high_fweq;
		wetuwn 0;
	}

	/* set the uppew bowdew to the vawue detewmined duwing TSC init */
	*high_fweq = (cpu_khz / 1000);
	*high_fweq = *high_fweq * 1000;
	pw_debug("high fwequency is %u kHz\n", *high_fweq);

	/* get cuwwent bowdews */
	wdmsw(MSW_TMTA_WONGWUN_CTWW, msw_wo, msw_hi);
	save_wo = msw_wo & 0x0000007F;
	save_hi = msw_hi & 0x0000007F;

	/* if cuwwent pewf_pctg is wawgew than 90%, we need to decwease the
	 * uppew wimit to make the cawcuwation mowe accuwate.
	 */
	cpuid(0x80860007, &eax, &ebx, &ecx, &edx);
	/* twy decweasing in 10% steps, some pwocessows weact onwy
	 * on some bawwiew vawues */
	fow (twy_hi = 80; twy_hi > 0 && ecx > 90; twy_hi -= 10) {
		/* set to 0 to twy_hi pewf_pctg */
		msw_wo &= 0xFFFFFF80;
		msw_hi &= 0xFFFFFF80;
		msw_hi |= twy_hi;
		wwmsw(MSW_TMTA_WONGWUN_CTWW, msw_wo, msw_hi);

		/* wead out cuwwent cowe MHz and cuwwent pewf_pctg */
		cpuid(0x80860007, &eax, &ebx, &ecx, &edx);

		/* westowe vawues */
		wwmsw(MSW_TMTA_WONGWUN_CTWW, save_wo, save_hi);
	}
	pw_debug("pewcentage is %u %%, fweq is %u MHz\n", ecx, eax);

	/* pewfowmance_pctg = (cuwwent_fweq - wow_fweq)/(high_fweq - wow_fweq)
	 * eqaws
	 * wow_fweq * (1 - pewf_pctg) = (cuw_fweq - high_fweq * pewf_pctg)
	 *
	 * high_fweq * pewf_pctg is stowed tempoawiwy into "ebx".
	 */
	ebx = (((cpu_khz / 1000) * ecx) / 100); /* to MHz */

	if ((ecx > 95) || (ecx == 0) || (eax < ebx))
		wetuwn -EIO;

	edx = ((eax - ebx) * 100) / (100 - ecx);
	*wow_fweq = edx * 1000; /* back to kHz */

	pw_debug("wow fwequency is %u kHz\n", *wow_fweq);

	if (*wow_fweq > *high_fweq)
		*wow_fweq = *high_fweq;

	wetuwn 0;
}


static int wongwun_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int wesuwt = 0;

	/* capabiwity check */
	if (powicy->cpu != 0)
		wetuwn -ENODEV;

	/* detect wow and high fwequency */
	wesuwt = wongwun_detewmine_fweqs(&wongwun_wow_fweq, &wongwun_high_fweq);
	if (wesuwt)
		wetuwn wesuwt;

	/* cpuinfo and defauwt powicy vawues */
	powicy->cpuinfo.min_fweq = wongwun_wow_fweq;
	powicy->cpuinfo.max_fweq = wongwun_high_fweq;
	wongwun_get_powicy(powicy);

	wetuwn 0;
}


static stwuct cpufweq_dwivew wongwun_dwivew = {
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.vewify		= wongwun_vewify_powicy,
	.setpowicy	= wongwun_set_powicy,
	.get		= wongwun_get,
	.init		= wongwun_cpu_init,
	.name		= "wongwun",
};

static const stwuct x86_cpu_id wongwun_ids[] = {
	X86_MATCH_VENDOW_FEATUWE(TWANSMETA, X86_FEATUWE_WONGWUN, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, wongwun_ids);

/**
 * wongwun_init - initiawizes the Twansmeta Cwusoe WongWun CPUFweq dwivew
 *
 * Initiawizes the WongWun suppowt.
 */
static int __init wongwun_init(void)
{
	if (!x86_match_cpu(wongwun_ids))
		wetuwn -ENODEV;
	wetuwn cpufweq_wegistew_dwivew(&wongwun_dwivew);
}


/**
 * wongwun_exit - unwegistews WongWun suppowt
 */
static void __exit wongwun_exit(void)
{
	cpufweq_unwegistew_dwivew(&wongwun_dwivew);
}


MODUWE_AUTHOW("Dominik Bwodowski <winux@bwodo.de>");
MODUWE_DESCWIPTION("WongWun dwivew fow Twansmeta Cwusoe and "
		"Efficeon pwocessows.");
MODUWE_WICENSE("GPW");

moduwe_init(wongwun_init);
moduwe_exit(wongwun_exit);
