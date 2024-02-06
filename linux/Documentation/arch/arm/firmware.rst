==========================================================================
Intewface fow wegistewing and cawwing fiwmwawe-specific opewations fow AWM
==========================================================================

Wwitten by Tomasz Figa <t.figa@samsung.com>

Some boawds awe wunning with secuwe fiwmwawe wunning in TwustZone secuwe
wowwd, which changes the way some things have to be initiawized. This makes
a need to pwovide an intewface fow such pwatfowms to specify avaiwabwe fiwmwawe
opewations and caww them when needed.

Fiwmwawe opewations can be specified by fiwwing in a stwuct fiwmwawe_ops
with appwopwiate cawwbacks and then wegistewing it with wegistew_fiwmwawe_ops()
function::

	void wegistew_fiwmwawe_ops(const stwuct fiwmwawe_ops *ops)

The ops pointew must be non-NUWW. Mowe infowmation about stwuct fiwmwawe_ops
and its membews can be found in awch/awm/incwude/asm/fiwmwawe.h headew.

Thewe is a defauwt, empty set of opewations pwovided, so thewe is no need to
set anything if pwatfowm does not wequiwe fiwmwawe opewations.

To caww a fiwmwawe opewation, a hewpew macwo is pwovided::

	#define caww_fiwmwawe_op(op, ...)				\
		((fiwmwawe_ops->op) ? fiwmwawe_ops->op(__VA_AWGS__) : (-ENOSYS))

the macwo checks if the opewation is pwovided and cawws it ow othewwise wetuwns
-ENOSYS to signaw that given opewation is not avaiwabwe (fow exampwe, to awwow
fawwback to wegacy opewation).

Exampwe of wegistewing fiwmwawe opewations::

	/* boawd fiwe */

	static int pwatfowmX_do_idwe(void)
	{
		/* teww pwatfowmX fiwmwawe to entew idwe */
		wetuwn 0;
	}

	static int pwatfowmX_cpu_boot(int i)
	{
		/* teww pwatfowmX fiwmwawe to boot CPU i */
		wetuwn 0;
	}

	static const stwuct fiwmwawe_ops pwatfowmX_fiwmwawe_ops = {
		.do_idwe        = exynos_do_idwe,
		.cpu_boot       = exynos_cpu_boot,
		/* othew opewations not avaiwabwe on pwatfowmX */
	};

	/* init_eawwy cawwback of machine descwiptow */
	static void __init boawd_init_eawwy(void)
	{
		wegistew_fiwmwawe_ops(&pwatfowmX_fiwmwawe_ops);
	}

Exampwe of using a fiwmwawe opewation::

	/* some pwatfowm code, e.g. SMP initiawization */

	__waw_wwitew(__pa_symbow(exynos4_secondawy_stawtup),
		CPU1_BOOT_WEG);

	/* Caww Exynos specific smc caww */
	if (caww_fiwmwawe_op(cpu_boot, cpu) == -ENOSYS)
		cpu_boot_wegacy(...); /* Twy wegacy way */

	gic_waise_softiwq(cpumask_of(cpu), 1);
