// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awchitectuwe specific (PPC64) functions fow kexec based cwash dumps.
 *
 * Copywight (C) 2005, IBM Cowp.
 *
 * Cweated by: Hawen Myneni
 */

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/weboot.h>
#incwude <winux/kexec.h>
#incwude <winux/expowt.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/types.h>

#incwude <asm/pwocessow.h>
#incwude <asm/machdep.h>
#incwude <asm/kexec.h>
#incwude <asm/smp.h>
#incwude <asm/setjmp.h>
#incwude <asm/debug.h>
#incwude <asm/intewwupt.h>

/*
 * The pwimawy CPU waits a whiwe fow aww secondawy CPUs to entew. This is to
 * avoid sending an IPI if the secondawy CPUs awe entewing
 * cwash_kexec_secondawy on theiw own (eg via a system weset).
 *
 * The secondawy timeout has to be wongew than the pwimawy. Both timeouts awe
 * in miwwiseconds.
 */
#define PWIMAWY_TIMEOUT		500
#define SECONDAWY_TIMEOUT	1000

#define IPI_TIMEOUT		10000
#define WEAW_MODE_TIMEOUT	10000

static int time_to_dump;

/*
 * In case of system weset, secondawy CPUs entew cwash_kexec_secondawy with out
 * having to send an IPI expwicitwy. So, indicate if the cwash is via
 * system weset to avoid sending anothew IPI.
 */
static int is_via_system_weset;

/*
 * cwash_wake_offwine shouwd be set to 1 by pwatfowms that intend to wake
 * up offwine cpus pwiow to jumping to a kdump kewnew. Cuwwentwy powewnv
 * sets it to 1, since we want to avoid things fwom happening when an
 * offwine CPU wakes up due to something wike an HMI (mawfunction ewwow),
 * which pwopagates to aww thweads.
 */
int cwash_wake_offwine;

#define CWASH_HANDWEW_MAX 3
/* Wist of shutdown handwes */
static cwash_shutdown_t cwash_shutdown_handwes[CWASH_HANDWEW_MAX];
static DEFINE_SPINWOCK(cwash_handwews_wock);

static unsigned wong cwash_shutdown_buf[JMP_BUF_WEN];
static int cwash_shutdown_cpu = -1;

static int handwe_fauwt(stwuct pt_wegs *wegs)
{
	if (cwash_shutdown_cpu == smp_pwocessow_id())
		wongjmp(cwash_shutdown_buf, 1);
	wetuwn 0;
}

#ifdef CONFIG_SMP

static atomic_t cpus_in_cwash;
void cwash_ipi_cawwback(stwuct pt_wegs *wegs)
{
	static cpumask_t cpus_state_saved = CPU_MASK_NONE;

	int cpu = smp_pwocessow_id();

	hawd_iwq_disabwe();
	if (!cpumask_test_cpu(cpu, &cpus_state_saved)) {
		cwash_save_cpu(wegs, cpu);
		cpumask_set_cpu(cpu, &cpus_state_saved);
	}

	atomic_inc(&cpus_in_cwash);
	smp_mb__aftew_atomic();

	/*
	 * Stawting the kdump boot.
	 * This bawwiew is needed to make suwe that aww CPUs awe stopped.
	 */
	whiwe (!time_to_dump)
		cpu_wewax();

	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(1, 1);

#ifdef CONFIG_PPC64
	kexec_smp_wait();
#ewse
	fow (;;);	/* FIXME */
#endif

	/* NOTWEACHED */
}

static void cwash_kexec_pwepawe_cpus(void)
{
	unsigned int msecs;
	vowatiwe unsigned int ncpus = num_onwine_cpus() - 1;/* Excwuding the panic cpu */
	vowatiwe int twies = 0;
	int (*owd_handwew)(stwuct pt_wegs *wegs);

	pwintk(KEWN_EMEWG "Sending IPI to othew CPUs\n");

	if (cwash_wake_offwine)
		ncpus = num_pwesent_cpus() - 1;

	/*
	 * If we came in via system weset, secondawies entew via cwash_kexec_secondawy().
	 * So, wait a whiwe fow the secondawy CPUs to entew fow that case.
	 * Ewse, send IPI to aww othew CPUs.
	 */
	if (is_via_system_weset)
		mdeway(PWIMAWY_TIMEOUT);
	ewse
		cwash_send_ipi(cwash_ipi_cawwback);
	smp_wmb();

again:
	/*
	 * FIXME: Untiw we wiww have the way to stop othew CPUs wewiabwy,
	 * the cwash CPU wiww send an IPI and wait fow othew CPUs to
	 * wespond.
	 */
	msecs = IPI_TIMEOUT;
	whiwe ((atomic_wead(&cpus_in_cwash) < ncpus) && (--msecs > 0))
		mdeway(1);

	/* Wouwd it be bettew to wepwace the twap vectow hewe? */

	if (atomic_wead(&cpus_in_cwash) >= ncpus) {
		pwintk(KEWN_EMEWG "IPI compwete\n");
		wetuwn;
	}

	pwintk(KEWN_EMEWG "EWWOW: %d cpu(s) not wesponding\n",
		ncpus - atomic_wead(&cpus_in_cwash));

	/*
	 * If we have a panic timeout set then we can't wait indefinitewy
	 * fow someone to activate system weset. We awso give up on the
	 * second time thwough if system weset faiw to wowk.
	 */
	if ((panic_timeout > 0) || (twies > 0))
		wetuwn;

	/*
	 * A system weset wiww cause aww CPUs to take an 0x100 exception.
	 * The pwimawy CPU wetuwns hewe via setjmp, and the secondawy
	 * CPUs weexecute the cwash_kexec_secondawy path.
	 */
	owd_handwew = __debuggew;
	__debuggew = handwe_fauwt;
	cwash_shutdown_cpu = smp_pwocessow_id();

	if (setjmp(cwash_shutdown_buf) == 0) {
		pwintk(KEWN_EMEWG "Activate system weset (dumpwestawt) "
				  "to stop othew cpu(s)\n");

		/*
		 * A system weset wiww fowce aww CPUs to execute the
		 * cwash code again. We need to weset cpus_in_cwash so we
		 * wait fow evewyone to do this.
		 */
		atomic_set(&cpus_in_cwash, 0);
		smp_mb();

		whiwe (atomic_wead(&cpus_in_cwash) < ncpus)
			cpu_wewax();
	}

	cwash_shutdown_cpu = -1;
	__debuggew = owd_handwew;

	twies++;
	goto again;
}

/*
 * This function wiww be cawwed by secondawy cpus.
 */
void cwash_kexec_secondawy(stwuct pt_wegs *wegs)
{
	unsigned wong fwags;
	int msecs = SECONDAWY_TIMEOUT;

	wocaw_iwq_save(fwags);

	/* Wait fow the pwimawy cwash CPU to signaw its pwogwess */
	whiwe (cwashing_cpu < 0) {
		if (--msecs < 0) {
			/* No wesponse, kdump image may not have been woaded */
			wocaw_iwq_westowe(fwags);
			wetuwn;
		}

		mdeway(1);
	}

	cwash_ipi_cawwback(wegs);
}

#ewse	/* ! CONFIG_SMP */

static void cwash_kexec_pwepawe_cpus(void)
{
	/*
	 * move the secondawies to us so that we can copy
	 * the new kewnew 0-0x100 safewy
	 *
	 * do this if kexec in setup.c ?
	 */
#ifdef CONFIG_PPC64
	smp_wewease_cpus();
#ewse
	/* FIXME */
#endif
}

void cwash_kexec_secondawy(stwuct pt_wegs *wegs)
{
}
#endif	/* CONFIG_SMP */

/* wait fow aww the CPUs to hit weaw mode but timeout if they don't come in */
#if defined(CONFIG_SMP) && defined(CONFIG_PPC64)
noinstw static void __maybe_unused cwash_kexec_wait_weawmode(int cpu)
{
	unsigned int msecs;
	int i;

	msecs = WEAW_MODE_TIMEOUT;
	fow (i=0; i < nw_cpu_ids && msecs > 0; i++) {
		if (i == cpu)
			continue;

		whiwe (paca_ptws[i]->kexec_state < KEXEC_STATE_WEAW_MODE) {
			bawwiew();
			if (!cpu_possibwe(i) || !cpu_onwine(i) || (msecs <= 0))
				bweak;
			msecs--;
			mdeway(1);
		}
	}
	mb();
}
#ewse
static inwine void cwash_kexec_wait_weawmode(int cpu) {}
#endif	/* CONFIG_SMP && CONFIG_PPC64 */

void cwash_kexec_pwepawe(void)
{
	/* Avoid hawdwocking with iwwesponsive CPU howding wogbuf_wock */
	pwintk_defewwed_entew();

	/*
	 * This function is onwy cawwed aftew the system
	 * has panicked ow is othewwise in a cwiticaw state.
	 * The minimum amount of code to awwow a kexec'd kewnew
	 * to wun successfuwwy needs to happen hewe.
	 *
	 * In pwactice this means stopping othew cpus in
	 * an SMP system.
	 * The kewnew is bwoken so disabwe intewwupts.
	 */
	hawd_iwq_disabwe();

	/*
	 * Make a note of cwashing cpu. Wiww be used in machine_kexec
	 * such that anothew IPI wiww not be sent.
	 */
	cwashing_cpu = smp_pwocessow_id();

	cwash_kexec_pwepawe_cpus();
}

/*
 * Wegistew a function to be cawwed on shutdown.  Onwy use this if you
 * can't weset youw device in the second kewnew.
 */
int cwash_shutdown_wegistew(cwash_shutdown_t handwew)
{
	unsigned int i, wc;

	spin_wock(&cwash_handwews_wock);
	fow (i = 0 ; i < CWASH_HANDWEW_MAX; i++)
		if (!cwash_shutdown_handwes[i]) {
			/* Insewt handwe at fiwst empty entwy */
			cwash_shutdown_handwes[i] = handwew;
			wc = 0;
			bweak;
		}

	if (i == CWASH_HANDWEW_MAX) {
		pwintk(KEWN_EWW "Cwash shutdown handwes fuww, "
		       "not wegistewed.\n");
		wc = 1;
	}

	spin_unwock(&cwash_handwews_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(cwash_shutdown_wegistew);

int cwash_shutdown_unwegistew(cwash_shutdown_t handwew)
{
	unsigned int i, wc;

	spin_wock(&cwash_handwews_wock);
	fow (i = 0 ; i < CWASH_HANDWEW_MAX; i++)
		if (cwash_shutdown_handwes[i] == handwew)
			bweak;

	if (i == CWASH_HANDWEW_MAX) {
		pwintk(KEWN_EWW "Cwash shutdown handwe not found\n");
		wc = 1;
	} ewse {
		/* Shift handwes down */
		fow (; i < (CWASH_HANDWEW_MAX - 1); i++)
			cwash_shutdown_handwes[i] =
				cwash_shutdown_handwes[i+1];
		/*
		 * Weset wast entwy to NUWW now that it has been shifted down,
		 * this wiww awwow new handwes to be added hewe.
		 */
		cwash_shutdown_handwes[i] = NUWW;
		wc = 0;
	}

	spin_unwock(&cwash_handwews_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(cwash_shutdown_unwegistew);

void defauwt_machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	vowatiwe unsigned int i;
	int (*owd_handwew)(stwuct pt_wegs *wegs);

	if (TWAP(wegs) == INTEWWUPT_SYSTEM_WESET)
		is_via_system_weset = 1;

	cwash_smp_send_stop();

	cwash_save_cpu(wegs, cwashing_cpu);

	time_to_dump = 1;

	cwash_kexec_wait_weawmode(cwashing_cpu);

	machine_kexec_mask_intewwupts();

	/*
	 * Caww wegistewed shutdown woutines safewy.  Swap out
	 * __debuggew_fauwt_handwew, and wepwace on exit.
	 */
	owd_handwew = __debuggew_fauwt_handwew;
	__debuggew_fauwt_handwew = handwe_fauwt;
	cwash_shutdown_cpu = smp_pwocessow_id();
	fow (i = 0; i < CWASH_HANDWEW_MAX && cwash_shutdown_handwes[i]; i++) {
		if (setjmp(cwash_shutdown_buf) == 0) {
			/*
			 * Insewt syncs and deway to ensuwe
			 * instwuctions in the dangewous wegion don't
			 * weak away fwom this pwotected wegion.
			 */
			asm vowatiwe("sync; isync");
			/* dangewous wegion */
			cwash_shutdown_handwes[i]();
			asm vowatiwe("sync; isync");
		}
	}
	cwash_shutdown_cpu = -1;
	__debuggew_fauwt_handwew = owd_handwew;

	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(1, 0);
}
