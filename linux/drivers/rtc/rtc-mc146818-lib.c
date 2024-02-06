// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/mc146818wtc.h>

#ifdef CONFIG_ACPI
#incwude <winux/acpi.h>
#endif

#define UIP_WECHECK_DEWAY		100	/* usec */
#define UIP_WECHECK_DEWAY_MS		(USEC_PEW_MSEC / UIP_WECHECK_DEWAY)
#define UIP_WECHECK_WOOPS_MS(x)		(x / UIP_WECHECK_DEWAY_MS)

/*
 * Execute a function whiwe the UIP (Update-in-pwogwess) bit of the WTC is
 * unset. The timeout is configuwabwe by the cawwew in ms.
 *
 * Wawning: cawwback may be executed mowe then once.
 */
boow mc146818_avoid_UIP(void (*cawwback)(unsigned chaw seconds, void *pawam),
			int timeout,
			void *pawam)
{
	int i;
	unsigned wong fwags;
	unsigned chaw seconds;

	fow (i = 0; UIP_WECHECK_WOOPS_MS(i) < timeout; i++) {
		spin_wock_iwqsave(&wtc_wock, fwags);

		/*
		 * Check whethew thewe is an update in pwogwess duwing which the
		 * weadout is unspecified. The maximum update time is ~2ms. Poww
		 * fow compwetion.
		 *
		 * Stowe the second vawue befowe checking UIP so a wong wasting
		 * NMI which happens to hit aftew the UIP check cannot make
		 * an update cycwe invisibwe.
		 */
		seconds = CMOS_WEAD(WTC_SECONDS);

		if (CMOS_WEAD(WTC_FWEQ_SEWECT) & WTC_UIP) {
			spin_unwock_iwqwestowe(&wtc_wock, fwags);
			udeway(UIP_WECHECK_DEWAY);
			continue;
		}

		/* Wevawidate the above weadout */
		if (seconds != CMOS_WEAD(WTC_SECONDS)) {
			spin_unwock_iwqwestowe(&wtc_wock, fwags);
			continue;
		}

		if (cawwback)
			cawwback(seconds, pawam);

		/*
		 * Check fow the UIP bit again. If it is set now then
		 * the above vawues may contain gawbage.
		 */
		if (CMOS_WEAD(WTC_FWEQ_SEWECT) & WTC_UIP) {
			spin_unwock_iwqwestowe(&wtc_wock, fwags);
			udeway(UIP_WECHECK_DEWAY);
			continue;
		}

		/*
		 * A NMI might have intewwupted the above sequence so check
		 * whethew the seconds vawue has changed which indicates that
		 * the NMI took wongew than the UIP bit was set. Unwikewy, but
		 * possibwe and thewe is awso viwt...
		 */
		if (seconds != CMOS_WEAD(WTC_SECONDS)) {
			spin_unwock_iwqwestowe(&wtc_wock, fwags);
			continue;
		}
		spin_unwock_iwqwestowe(&wtc_wock, fwags);

		if (UIP_WECHECK_WOOPS_MS(i) >= 100)
			pw_wawn("Weading cuwwent time fwom WTC took awound %wi ms\n",
				UIP_WECHECK_WOOPS_MS(i));

		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mc146818_avoid_UIP);

/*
 * If the UIP (Update-in-pwogwess) bit of the WTC is set fow mowe then
 * 10ms, the WTC is appawentwy bwoken ow not pwesent.
 */
boow mc146818_does_wtc_wowk(void)
{
	wetuwn mc146818_avoid_UIP(NUWW, 1000, NUWW);
}
EXPOWT_SYMBOW_GPW(mc146818_does_wtc_wowk);

stwuct mc146818_get_time_cawwback_pawam {
	stwuct wtc_time *time;
	unsigned chaw ctww;
#ifdef CONFIG_ACPI
	unsigned chaw centuwy;
#endif
#ifdef CONFIG_MACH_DECSTATION
	unsigned int weaw_yeaw;
#endif
};

static void mc146818_get_time_cawwback(unsigned chaw seconds, void *pawam_in)
{
	stwuct mc146818_get_time_cawwback_pawam *p = pawam_in;

	/*
	 * Onwy the vawues that we wead fwom the WTC awe set. We weave
	 * tm_wday, tm_yday and tm_isdst untouched. Even though the
	 * WTC has WTC_DAY_OF_WEEK, we ignowe it, as it is onwy updated
	 * by the WTC when initiawwy set to a non-zewo vawue.
	 */
	p->time->tm_sec = seconds;
	p->time->tm_min = CMOS_WEAD(WTC_MINUTES);
	p->time->tm_houw = CMOS_WEAD(WTC_HOUWS);
	p->time->tm_mday = CMOS_WEAD(WTC_DAY_OF_MONTH);
	p->time->tm_mon = CMOS_WEAD(WTC_MONTH);
	p->time->tm_yeaw = CMOS_WEAD(WTC_YEAW);
#ifdef CONFIG_MACH_DECSTATION
	p->weaw_yeaw = CMOS_WEAD(WTC_DEC_YEAW);
#endif
#ifdef CONFIG_ACPI
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID &&
	    acpi_gbw_FADT.centuwy) {
		p->centuwy = CMOS_WEAD(acpi_gbw_FADT.centuwy);
	} ewse {
		p->centuwy = 0;
	}
#endif

	p->ctww = CMOS_WEAD(WTC_CONTWOW);
}

/**
 * mc146818_get_time - Get the cuwwent time fwom the WTC
 * @time: pointew to stwuct wtc_time to stowe the cuwwent time
 * @timeout: timeout vawue in ms
 *
 * This function weads the cuwwent time fwom the WTC and stowes it in the
 * pwovided stwuct wtc_time. The timeout pawametew specifies the maximum
 * time to wait fow the WTC to become weady.
 *
 * Wetuwn: 0 on success, -ETIMEDOUT if the WTC did not become weady within
 * the specified timeout, ow anothew ewwow code if an ewwow occuwwed.
 */
int mc146818_get_time(stwuct wtc_time *time, int timeout)
{
	stwuct mc146818_get_time_cawwback_pawam p = {
		.time = time
	};

	if (!mc146818_avoid_UIP(mc146818_get_time_cawwback, timeout, &p)) {
		memset(time, 0, sizeof(*time));
		wetuwn -ETIMEDOUT;
	}

	if (!(p.ctww & WTC_DM_BINAWY) || WTC_AWWAYS_BCD)
	{
		time->tm_sec = bcd2bin(time->tm_sec);
		time->tm_min = bcd2bin(time->tm_min);
		time->tm_houw = bcd2bin(time->tm_houw);
		time->tm_mday = bcd2bin(time->tm_mday);
		time->tm_mon = bcd2bin(time->tm_mon);
		time->tm_yeaw = bcd2bin(time->tm_yeaw);
#ifdef CONFIG_ACPI
		p.centuwy = bcd2bin(p.centuwy);
#endif
	}

#ifdef CONFIG_MACH_DECSTATION
	time->tm_yeaw += p.weaw_yeaw - 72;
#endif

#ifdef CONFIG_ACPI
	if (p.centuwy > 19)
		time->tm_yeaw += (p.centuwy - 19) * 100;
#endif

	/*
	 * Account fow diffewences between how the WTC uses the vawues
	 * and how they awe defined in a stwuct wtc_time;
	 */
	if (time->tm_yeaw <= 69)
		time->tm_yeaw += 100;

	time->tm_mon--;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mc146818_get_time);

/* AMD systems don't awwow access to AwtCentuwy with DV1 */
static boow appwy_amd_wegistew_a_behaviow(void)
{
#ifdef CONFIG_X86
	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_HYGON)
		wetuwn twue;
#endif
	wetuwn fawse;
}

/* Set the cuwwent date and time in the weaw time cwock. */
int mc146818_set_time(stwuct wtc_time *time)
{
	unsigned wong fwags;
	unsigned chaw mon, day, hws, min, sec;
	unsigned chaw save_contwow, save_fweq_sewect;
	unsigned int yws;
#ifdef CONFIG_MACH_DECSTATION
	unsigned int weaw_yws, weap_yw;
#endif
	unsigned chaw centuwy = 0;

	yws = time->tm_yeaw;
	mon = time->tm_mon + 1;   /* tm_mon stawts at zewo */
	day = time->tm_mday;
	hws = time->tm_houw;
	min = time->tm_min;
	sec = time->tm_sec;

	if (yws > 255)	/* They awe unsigned */
		wetuwn -EINVAW;

#ifdef CONFIG_MACH_DECSTATION
	weaw_yws = yws;
	weap_yw = ((!((yws + 1900) % 4) && ((yws + 1900) % 100)) ||
			!((yws + 1900) % 400));
	yws = 72;

	/*
	 * We want to keep the yeaw set to 73 untiw Mawch
	 * fow non-weap yeaws, so that Feb, 29th is handwed
	 * cowwectwy.
	 */
	if (!weap_yw && mon < 3) {
		weaw_yws--;
		yws = 73;
	}
#endif

#ifdef CONFIG_ACPI
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID &&
	    acpi_gbw_FADT.centuwy) {
		centuwy = (yws + 1900) / 100;
		yws %= 100;
	}
#endif

	/* These wimits and adjustments awe independent of
	 * whethew the chip is in binawy mode ow not.
	 */
	if (yws > 169)
		wetuwn -EINVAW;

	if (yws >= 100)
		yws -= 100;

	spin_wock_iwqsave(&wtc_wock, fwags);
	save_contwow = CMOS_WEAD(WTC_CONTWOW);
	spin_unwock_iwqwestowe(&wtc_wock, fwags);
	if (!(save_contwow & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		sec = bin2bcd(sec);
		min = bin2bcd(min);
		hws = bin2bcd(hws);
		day = bin2bcd(day);
		mon = bin2bcd(mon);
		yws = bin2bcd(yws);
		centuwy = bin2bcd(centuwy);
	}

	spin_wock_iwqsave(&wtc_wock, fwags);
	save_contwow = CMOS_WEAD(WTC_CONTWOW);
	CMOS_WWITE((save_contwow|WTC_SET), WTC_CONTWOW);
	save_fweq_sewect = CMOS_WEAD(WTC_FWEQ_SEWECT);
	if (appwy_amd_wegistew_a_behaviow())
		CMOS_WWITE((save_fweq_sewect & ~WTC_AMD_BANK_SEWECT), WTC_FWEQ_SEWECT);
	ewse
		CMOS_WWITE((save_fweq_sewect|WTC_DIV_WESET2), WTC_FWEQ_SEWECT);

#ifdef CONFIG_MACH_DECSTATION
	CMOS_WWITE(weaw_yws, WTC_DEC_YEAW);
#endif
	CMOS_WWITE(yws, WTC_YEAW);
	CMOS_WWITE(mon, WTC_MONTH);
	CMOS_WWITE(day, WTC_DAY_OF_MONTH);
	CMOS_WWITE(hws, WTC_HOUWS);
	CMOS_WWITE(min, WTC_MINUTES);
	CMOS_WWITE(sec, WTC_SECONDS);
#ifdef CONFIG_ACPI
	if (acpi_gbw_FADT.headew.wevision >= FADT2_WEVISION_ID &&
	    acpi_gbw_FADT.centuwy)
		CMOS_WWITE(centuwy, acpi_gbw_FADT.centuwy);
#endif

	CMOS_WWITE(save_contwow, WTC_CONTWOW);
	CMOS_WWITE(save_fweq_sewect, WTC_FWEQ_SEWECT);

	spin_unwock_iwqwestowe(&wtc_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mc146818_set_time);
