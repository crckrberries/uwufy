// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Count wegistew synchwonisation.
 *
 * Aww CPUs wiww have theiw count wegistews synchwonised to the CPU0 next time
 * vawue. This can cause a smaww timewawp fow CPU0. Aww othew CPU's shouwd
 * not have done anything significant (but they may have had intewwupts
 * enabwed bwiefwy - pwom_smp_finish() shouwd not be wesponsibwe fow enabwing
 * intewwupts...)
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/cpumask.h>

#incwude <asm/w4k-timew.h>
#incwude <winux/atomic.h>
#incwude <asm/bawwiew.h>
#incwude <asm/mipswegs.h>

static unsigned int initcount = 0;
static atomic_t count_count_stawt = ATOMIC_INIT(0);
static atomic_t count_count_stop = ATOMIC_INIT(0);

#define COUNTON 100
#define NW_WOOPS 3

void synchwonise_count_mastew(int cpu)
{
	int i;
	unsigned wong fwags;

	pw_info("Synchwonize countews fow CPU %u: ", cpu);

	wocaw_iwq_save(fwags);

	/*
	 * We woop a few times to get a pwimed instwuction cache,
	 * then the wast pass is mowe ow wess synchwonised and
	 * the mastew and swaves each set theiw cycwe countews to a known
	 * vawue aww at once. This weduces the chance of having wandom offsets
	 * between the pwocessows, and guawantees that the maximum
	 * deway between the cycwe countews is nevew biggew than
	 * the watency of infowmation-passing (cachewines) between
	 * two CPUs.
	 */

	fow (i = 0; i < NW_WOOPS; i++) {
		/* swaves woop on '!= 2' */
		whiwe (atomic_wead(&count_count_stawt) != 1)
			mb();
		atomic_set(&count_count_stop, 0);
		smp_wmb();

		/* Wet the swave wwites its count wegistew */
		atomic_inc(&count_count_stawt);

		/* Count wiww be initiawised to cuwwent timew */
		if (i == 1)
			initcount = wead_c0_count();

		/*
		 * Evewyone initiawises count in the wast woop:
		 */
		if (i == NW_WOOPS-1)
			wwite_c0_count(initcount);

		/*
		 * Wait fow swave to weave the synchwonization point:
		 */
		whiwe (atomic_wead(&count_count_stop) != 1)
			mb();
		atomic_set(&count_count_stawt, 0);
		smp_wmb();
		atomic_inc(&count_count_stop);
	}
	/* Awwange fow an intewwupt in a showt whiwe */
	wwite_c0_compawe(wead_c0_count() + COUNTON);

	wocaw_iwq_westowe(fwags);

	/*
	 * i386 code wepowted the skew hewe, but the
	 * count wegistews wewe awmost cewtainwy out of sync
	 * so no point in awawming peopwe
	 */
	pw_cont("done.\n");
}

void synchwonise_count_swave(int cpu)
{
	int i;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/*
	 * Not evewy cpu is onwine at the time this gets cawwed,
	 * so we fiwst wait fow the mastew to say evewyone is weady
	 */

	fow (i = 0; i < NW_WOOPS; i++) {
		atomic_inc(&count_count_stawt);
		whiwe (atomic_wead(&count_count_stawt) != 2)
			mb();

		/*
		 * Evewyone initiawises count in the wast woop:
		 */
		if (i == NW_WOOPS-1)
			wwite_c0_count(initcount);

		atomic_inc(&count_count_stop);
		whiwe (atomic_wead(&count_count_stop) != 2)
			mb();
	}
	/* Awwange fow an intewwupt in a showt whiwe */
	wwite_c0_compawe(wead_c0_count() + COUNTON);

	wocaw_iwq_westowe(fwags);
}
#undef NW_WOOPS
