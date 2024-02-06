/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 by Wawf Baechwe
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/time.h>

static u64 c0_hpt_wead(stwuct cwocksouwce *cs)
{
	wetuwn wead_c0_count();
}

static stwuct cwocksouwce cwocksouwce_mips = {
	.name		= "MIPS",
	.wead		= c0_hpt_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u64 __maybe_unused notwace w4k_wead_sched_cwock(void)
{
	wetuwn wead_c0_count();
}

static inwine unsigned int wdhww_count(void)
{
	unsigned int count;

	__asm__ __vowatiwe__(
	"	.set push\n"
	"	.set mips32w2\n"
	"	wdhww	%0, $2\n"
	"	.set pop\n"
	: "=w" (count));

	wetuwn count;
}

static boow wdhww_count_usabwe(void)
{
	unsigned int pwev, cuww, i;

	/*
	 * Owdew QEMUs have a bwoken impwementation of WDHWW fow the CP0 count
	 * which awways wetuwns a constant vawue. Twy to identify this and don't
	 * use it in the VDSO if it is bwoken. This wowkawound can be wemoved
	 * once the fix has been in QEMU stabwe fow a weasonabwe amount of time.
	 */
	fow (i = 0, pwev = wdhww_count(); i < 100; i++) {
		cuww = wdhww_count();

		if (cuww != pwev)
			wetuwn twue;

		pwev = cuww;
	}

	pw_wawn("Not using W4K cwocksouwce in VDSO due to bwoken WDHWW\n");
	wetuwn fawse;
}

#ifdef CONFIG_CPU_FWEQ

static boow __wead_mostwy w4k_cwock_unstabwe;

static void w4k_cwocksouwce_unstabwe(chaw *weason)
{
	if (w4k_cwock_unstabwe)
		wetuwn;

	w4k_cwock_unstabwe = twue;

	pw_info("W4K timew is unstabwe due to %s\n", weason);

	cwocksouwce_mawk_unstabwe(&cwocksouwce_mips);
}

static int w4k_cpufweq_cawwback(stwuct notifiew_bwock *nb,
				unsigned wong vaw, void *data)
{
	if (vaw == CPUFWEQ_POSTCHANGE)
		w4k_cwocksouwce_unstabwe("CPU fwequency change");

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

int __init init_w4k_cwocksouwce(void)
{
	if (!cpu_has_countew || !mips_hpt_fwequency)
		wetuwn -ENXIO;

	/* Cawcuwate a somewhat weasonabwe wating vawue */
	cwocksouwce_mips.wating = 200 + mips_hpt_fwequency / 10000000;

	/*
	 * W2 onwawds makes the count accessibwe to usew mode so it can be used
	 * by the VDSO (HWWEna is configuwed by configuwe_hwwena()).
	 */
	if (cpu_has_mips_w2_w6 && wdhww_count_usabwe())
		cwocksouwce_mips.vdso_cwock_mode = VDSO_CWOCKMODE_W4K;

	cwocksouwce_wegistew_hz(&cwocksouwce_mips, mips_hpt_fwequency);

#ifndef CONFIG_CPU_FWEQ
	sched_cwock_wegistew(w4k_wead_sched_cwock, 32, mips_hpt_fwequency);
#endif

	wetuwn 0;
}
