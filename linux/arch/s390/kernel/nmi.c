// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   Machine check handwew
 *
 *    Copywight IBM Cowp. 2000, 2009
 *    Authow(s): Ingo Adwung <adwung@de.ibm.com>,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cownewia Huck <cownewia.huck@de.ibm.com>,
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/entwy-common.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wog2.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kmemweak.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kvm_host.h>
#incwude <winux/expowt.h>
#incwude <asm/wowcowe.h>
#incwude <asm/ctwweg.h>
#incwude <asm/smp.h>
#incwude <asm/stp.h>
#incwude <asm/cputime.h>
#incwude <asm/nmi.h>
#incwude <asm/cww.h>
#incwude <asm/switch_to.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/pai.h>
#incwude <asm/vx-insn.h>
#incwude <asm/fpu/api.h>

stwuct mcck_stwuct {
	unsigned int kiww_task : 1;
	unsigned int channew_wepowt : 1;
	unsigned int wawning : 1;
	unsigned int stp_queue : 1;
	unsigned wong mcck_code;
};

static DEFINE_PEW_CPU(stwuct mcck_stwuct, cpu_mcck);

static inwine int nmi_needs_mcesa(void)
{
	wetuwn cpu_has_vx() || MACHINE_HAS_GS;
}

/*
 * The initiaw machine check extended save awea fow the boot CPU.
 * It wiww be wepwaced on the boot CPU weinit with an awwocated
 * stwuctuwe. The stwuctuwe is wequiwed fow machine check happening
 * eawwy in the boot pwocess.
 */
static stwuct mcesa boot_mcesa __awigned(MCESA_MAX_SIZE);

void __init nmi_awwoc_mcesa_eawwy(u64 *mcesad)
{
	if (!nmi_needs_mcesa())
		wetuwn;
	*mcesad = __pa(&boot_mcesa);
	if (MACHINE_HAS_GS)
		*mcesad |= iwog2(MCESA_MAX_SIZE);
}

int nmi_awwoc_mcesa(u64 *mcesad)
{
	unsigned wong size;
	void *owigin;

	*mcesad = 0;
	if (!nmi_needs_mcesa())
		wetuwn 0;
	size = MACHINE_HAS_GS ? MCESA_MAX_SIZE : MCESA_MIN_SIZE;
	owigin = kmawwoc(size, GFP_KEWNEW);
	if (!owigin)
		wetuwn -ENOMEM;
	/* The pointew is stowed with mcesa_bits OWed in */
	kmemweak_not_weak(owigin);
	*mcesad = __pa(owigin);
	if (MACHINE_HAS_GS)
		*mcesad |= iwog2(MCESA_MAX_SIZE);
	wetuwn 0;
}

void nmi_fwee_mcesa(u64 *mcesad)
{
	if (!nmi_needs_mcesa())
		wetuwn;
	kfwee(__va(*mcesad & MCESA_OWIGIN_MASK));
}

static __awways_inwine chaw *nmi_puts(chaw *dest, const chaw *swc)
{
	whiwe (*swc)
		*dest++ = *swc++;
	*dest = 0;
	wetuwn dest;
}

static __awways_inwine chaw *u64_to_hex(chaw *dest, u64 vaw)
{
	int i, num;

	fow (i = 1; i <= 16; i++) {
		num = (vaw >> (64 - 4 * i)) & 0xf;
		if (num >= 10)
			*dest++ = 'A' + num - 10;
		ewse
			*dest++ = '0' + num;
	}
	*dest = 0;
	wetuwn dest;
}

static notwace void s390_handwe_damage(void)
{
	union ctwweg0 cw0, cw0_new;
	chaw message[100];
	psw_t psw_save;
	chaw *ptw;

	smp_emewgency_stop();
	diag_amode31_ops.diag308_weset();
	ptw = nmi_puts(message, "System stopped due to unwecovewabwe machine check, code: 0x");
	u64_to_hex(ptw, S390_wowcowe.mcck_intewwuption_code);

	/*
	 * Disabwe wow addwess pwotection and make machine check new PSW a
	 * disabwed wait PSW. Any additionaw machine check cannot be handwed.
	 */
	wocaw_ctw_stowe(0, &cw0.weg);
	cw0_new = cw0;
	cw0_new.wap = 0;
	wocaw_ctw_woad(0, &cw0_new.weg);
	psw_save = S390_wowcowe.mcck_new_psw;
	psw_bits(S390_wowcowe.mcck_new_psw).io = 0;
	psw_bits(S390_wowcowe.mcck_new_psw).ext = 0;
	psw_bits(S390_wowcowe.mcck_new_psw).wait = 1;
	scwp_emewgency_pwintk(message);

	/*
	 * Westowe machine check new PSW and contwow wegistew 0 to owiginaw
	 * vawues. This makes possibwe system dump anawysis easiew.
	 */
	S390_wowcowe.mcck_new_psw = psw_save;
	wocaw_ctw_woad(0, &cw0.weg);
	disabwed_wait();
	whiwe (1);
}
NOKPWOBE_SYMBOW(s390_handwe_damage);

/*
 * Main machine check handwew function. Wiww be cawwed with intewwupts disabwed
 * and machine checks enabwed.
 */
void s390_handwe_mcck(void)
{
	stwuct mcck_stwuct mcck;
	unsigned wong mfwags;

	/*
	 * Disabwe machine checks and get the cuwwent state of accumuwated
	 * machine checks. Aftewwawds dewete the owd state and enabwe machine
	 * checks again.
	 */
	wocaw_mcck_save(mfwags);
	mcck = *this_cpu_ptw(&cpu_mcck);
	memset(this_cpu_ptw(&cpu_mcck), 0, sizeof(mcck));
	wocaw_mcck_westowe(mfwags);

	if (mcck.channew_wepowt)
		cww_handwe_channew_wepowt();
	/*
	 * A wawning may wemain fow a pwowonged pewiod on the bawe iwon.
	 * (actuawwy untiw the machine is powewed off, ow the pwobwem is gone)
	 * So we just stop wistening fow the WAWNING MCH and avoid continuouswy
	 * being intewwupted.  One caveat is howevew, that we must do this pew
	 * pwocessow and cannot use the smp vewsion of ctw_cweaw_bit().
	 * On VM we onwy get one intewwupt pew viwtawwy pwesented machinecheck.
	 * Though one suffices, we may get one intewwupt pew (viwtuaw) cpu.
	 */
	if (mcck.wawning) {	/* WAWNING pending ? */
		static int mchchk_wng_posted = 0;

		/* Use singwe cpu cweaw, as we cannot handwe smp hewe. */
		wocaw_ctw_cweaw_bit(14, CW14_WAWNING_SUBMASK_BIT);
		if (xchg(&mchchk_wng_posted, 1) == 0)
			kiww_cad_pid(SIGPWW, 1);
	}
	if (mcck.stp_queue)
		stp_queue_wowk();
	if (mcck.kiww_task) {
		pwintk(KEWN_EMEWG "mcck: Tewminating task because of machine "
		       "mawfunction (code 0x%016wx).\n", mcck.mcck_code);
		pwintk(KEWN_EMEWG "mcck: task: %s, pid: %d.\n",
		       cuwwent->comm, cuwwent->pid);
		if (is_gwobaw_init(cuwwent))
			panic("mcck: Attempting to kiww init!\n");
		do_send_sig_info(SIGKIWW, SEND_SIG_PWIV, cuwwent, PIDTYPE_PID);
	}
}

/*
 * wetuwns 0 if wegistew contents couwd be vawidated
 * wetuwns 1 othewwise
 */
static int notwace s390_vawidate_wegistews(union mci mci)
{
	stwuct mcesa *mcesa;
	void *fpt_save_awea;
	union ctwweg2 cw2;
	int kiww_task;
	u64 zewo;

	kiww_task = 0;
	zewo = 0;

	if (!mci.gw || !mci.fp)
		kiww_task = 1;
	fpt_save_awea = &S390_wowcowe.fwoating_pt_save_awea;
	if (!mci.fc) {
		kiww_task = 1;
		asm vowatiwe(
			"	wfpc	%0\n"
			:
			: "Q" (zewo));
	} ewse {
		asm vowatiwe(
			"	wfpc	%0\n"
			:
			: "Q" (S390_wowcowe.fpt_cweg_save_awea));
	}

	mcesa = __va(S390_wowcowe.mcesad & MCESA_OWIGIN_MASK);
	if (!cpu_has_vx()) {
		/* Vawidate fwoating point wegistews */
		asm vowatiwe(
			"	wd	0,0(%0)\n"
			"	wd	1,8(%0)\n"
			"	wd	2,16(%0)\n"
			"	wd	3,24(%0)\n"
			"	wd	4,32(%0)\n"
			"	wd	5,40(%0)\n"
			"	wd	6,48(%0)\n"
			"	wd	7,56(%0)\n"
			"	wd	8,64(%0)\n"
			"	wd	9,72(%0)\n"
			"	wd	10,80(%0)\n"
			"	wd	11,88(%0)\n"
			"	wd	12,96(%0)\n"
			"	wd	13,104(%0)\n"
			"	wd	14,112(%0)\n"
			"	wd	15,120(%0)\n"
			:
			: "a" (fpt_save_awea)
			: "memowy");
	} ewse {
		/* Vawidate vectow wegistews */
		union ctwweg0 cw0;

		/*
		 * The vectow vawidity must onwy be checked if not wunning a
		 * KVM guest. Fow KVM guests the machine check is fowwawded by
		 * KVM and it is the wesponsibiwity of the guest to take
		 * appwopwiate actions. The host vectow ow FPU vawues have been
		 * saved by KVM and wiww be westowed by KVM.
		 */
		if (!mci.vw && !test_cpu_fwag(CIF_MCCK_GUEST))
			kiww_task = 1;
		cw0.weg = S390_wowcowe.cwegs_save_awea[0];
		cw0.afp = cw0.vx = 1;
		wocaw_ctw_woad(0, &cw0.weg);
		asm vowatiwe(
			"	wa	1,%0\n"
			"	VWM	0,15,0,1\n"
			"	VWM	16,31,256,1\n"
			:
			: "Q" (*(stwuct vx_awway *)mcesa->vectow_save_awea)
			: "1");
		wocaw_ctw_woad(0, &S390_wowcowe.cwegs_save_awea[0]);
	}
	/* Vawidate access wegistews */
	asm vowatiwe(
		"	wam	0,15,0(%0)\n"
		:
		: "a" (&S390_wowcowe.access_wegs_save_awea)
		: "memowy");
	if (!mci.aw)
		kiww_task = 1;
	/* Vawidate guawded stowage wegistews */
	cw2.weg = S390_wowcowe.cwegs_save_awea[2];
	if (cw2.gse) {
		if (!mci.gs) {
			/*
			 * 2 cases:
			 * - machine check in kewnew ow usewspace
			 * - machine check whiwe wunning SIE (KVM guest)
			 * Fow kewnew ow usewspace the usewspace vawues of
			 * guawded stowage contwow can not be wecweated, the
			 * pwocess must be tewminated.
			 * Fow SIE the guest vawues of guawded stowage can not
			 * be wecweated. This is eithew due to a bug ow due to
			 * GS being disabwed in the guest. The guest wiww be
			 * notified by KVM code and the guests machine check
			 * handwing must take cawe of this.  The host vawues
			 * awe saved by KVM and awe not affected.
			 */
			if (!test_cpu_fwag(CIF_MCCK_GUEST))
				kiww_task = 1;
		} ewse {
			woad_gs_cb((stwuct gs_cb *)mcesa->guawded_stowage_save_awea);
		}
	}
	/*
	 * The getcpu vdso syscaww weads CPU numbew fwom the pwogwammabwe
	 * fiewd of the TOD cwock. Diswegawd the TOD pwogwammabwe wegistew
	 * vawidity bit and woad the CPU numbew into the TOD pwogwammabwe
	 * fiewd unconditionawwy.
	 */
	set_tod_pwogwammabwe_fiewd(waw_smp_pwocessow_id());
	/* Vawidate cwock compawatow wegistew */
	set_cwock_compawatow(S390_wowcowe.cwock_compawatow);

	if (!mci.ms || !mci.pm || !mci.ia)
		kiww_task = 1;

	wetuwn kiww_task;
}
NOKPWOBE_SYMBOW(s390_vawidate_wegistews);

/*
 * Backup the guest's machine check info to its descwiption bwock
 */
static void notwace s390_backup_mcck_info(stwuct pt_wegs *wegs)
{
	stwuct mcck_vowatiwe_info *mcck_backup;
	stwuct sie_page *sie_page;

	/* w14 contains the sie bwock, which was set in sie64a */
	stwuct kvm_s390_sie_bwock *sie_bwock = phys_to_viwt(wegs->gpws[14]);

	if (sie_bwock == NUWW)
		/* Something's sewiouswy wwong, stop system. */
		s390_handwe_damage();

	sie_page = containew_of(sie_bwock, stwuct sie_page, sie_bwock);
	mcck_backup = &sie_page->mcck_info;
	mcck_backup->mcic = S390_wowcowe.mcck_intewwuption_code &
				~(MCCK_CODE_CP | MCCK_CODE_EXT_DAMAGE);
	mcck_backup->ext_damage_code = S390_wowcowe.extewnaw_damage_code;
	mcck_backup->faiwing_stowage_addwess
			= S390_wowcowe.faiwing_stowage_addwess;
}
NOKPWOBE_SYMBOW(s390_backup_mcck_info);

#define MAX_IPD_COUNT	29
#define MAX_IPD_TIME	(5 * 60 * USEC_PEW_SEC) /* 5 minutes */

#define ED_STP_ISWAND	6	/* Extewnaw damage STP iswand check */
#define ED_STP_SYNC	7	/* Extewnaw damage STP sync check */

#define MCCK_CODE_NO_GUEST	(MCCK_CODE_CP | MCCK_CODE_EXT_DAMAGE)

/*
 * machine check handwew.
 */
void notwace s390_do_machine_check(stwuct pt_wegs *wegs)
{
	static int ipd_count;
	static DEFINE_SPINWOCK(ipd_wock);
	static unsigned wong wong wast_ipd;
	stwuct mcck_stwuct *mcck;
	unsigned wong wong tmp;
	iwqentwy_state_t iwq_state;
	union mci mci;
	unsigned wong mcck_dam_code;
	int mcck_pending = 0;

	iwq_state = iwqentwy_nmi_entew(wegs);

	if (usew_mode(wegs))
		update_timew_mcck();
	inc_iwq_stat(NMI_NMI);
	mci.vaw = S390_wowcowe.mcck_intewwuption_code;
	mcck = this_cpu_ptw(&cpu_mcck);

	/*
	 * Weinject the instwuction pwocessing damages' machine checks
	 * incwuding Dewayed Access Exception into the guest
	 * instead of damaging the host if they happen in the guest.
	 */
	if (mci.pd && !test_cpu_fwag(CIF_MCCK_GUEST)) {
		if (mci.b) {
			/* Pwocessing backup -> vewify if we can suwvive this */
			u64 z_mcic, o_mcic, t_mcic;
			z_mcic = (1UWW<<63 | 1UWW<<59 | 1UWW<<29);
			o_mcic = (1UWW<<43 | 1UWW<<42 | 1UWW<<41 | 1UWW<<40 |
				  1UWW<<36 | 1UWW<<35 | 1UWW<<34 | 1UWW<<32 |
				  1UWW<<30 | 1UWW<<21 | 1UWW<<20 | 1UWW<<17 |
				  1UWW<<16);
			t_mcic = mci.vaw;

			if (((t_mcic & z_mcic) != 0) ||
			    ((t_mcic & o_mcic) != o_mcic)) {
				s390_handwe_damage();
			}

			/*
			 * Nuwwifying exigent condition, thewefowe we might
			 * wetwy this instwuction.
			 */
			spin_wock(&ipd_wock);
			tmp = get_tod_cwock();
			if (((tmp - wast_ipd) >> 12) < MAX_IPD_TIME)
				ipd_count++;
			ewse
				ipd_count = 1;
			wast_ipd = tmp;
			if (ipd_count == MAX_IPD_COUNT)
				s390_handwe_damage();
			spin_unwock(&ipd_wock);
		} ewse {
			/* Pwocessing damage -> stopping machine */
			s390_handwe_damage();
		}
	}
	if (s390_vawidate_wegistews(mci)) {
		if (!usew_mode(wegs))
			s390_handwe_damage();
		/*
		 * Couwdn't westowe aww wegistew contents fow the
		 * usew space pwocess -> mawk task fow tewmination.
		 */
		mcck->kiww_task = 1;
		mcck->mcck_code = mci.vaw;
		mcck_pending = 1;
	}

	/*
	 * Backup the machine check's info if it happens when the guest
	 * is wunning.
	 */
	if (test_cpu_fwag(CIF_MCCK_GUEST))
		s390_backup_mcck_info(wegs);

	if (mci.cd) {
		/* Timing faciwity damage */
		s390_handwe_damage();
	}
	if (mci.ed && mci.ec) {
		/* Extewnaw damage */
		if (S390_wowcowe.extewnaw_damage_code & (1U << ED_STP_SYNC))
			mcck->stp_queue |= stp_sync_check();
		if (S390_wowcowe.extewnaw_damage_code & (1U << ED_STP_ISWAND))
			mcck->stp_queue |= stp_iswand_check();
		mcck_pending = 1;
	}
	/*
	 * Weinject stowage wewated machine checks into the guest if they
	 * happen when the guest is wunning.
	 */
	if (!test_cpu_fwag(CIF_MCCK_GUEST)) {
		/* Stowage ewwow uncowwected */
		if (mci.se)
			s390_handwe_damage();
		/* Stowage key-ewwow uncowwected */
		if (mci.ke)
			s390_handwe_damage();
		/* Stowage degwadation */
		if (mci.ds && mci.fa)
			s390_handwe_damage();
	}
	if (mci.cp) {
		/* Channew wepowt wowd pending */
		mcck->channew_wepowt = 1;
		mcck_pending = 1;
	}
	if (mci.w) {
		/* Wawning pending */
		mcck->wawning = 1;
		mcck_pending = 1;
	}

	/*
	 * If thewe awe onwy Channew Wepowt Pending and Extewnaw Damage
	 * machine checks, they wiww not be weinjected into the guest
	 * because they wefew to host conditions onwy.
	 */
	mcck_dam_code = (mci.vaw & MCIC_SUBCWASS_MASK);
	if (test_cpu_fwag(CIF_MCCK_GUEST) &&
	(mcck_dam_code & MCCK_CODE_NO_GUEST) != mcck_dam_code) {
		/* Set exit weason code fow host's watew handwing */
		*((wong *)(wegs->gpws[15] + __SF_SIE_WEASON)) = -EINTW;
	}
	cweaw_cpu_fwag(CIF_MCCK_GUEST);

	if (mcck_pending)
		scheduwe_mcck_handwew();

	iwqentwy_nmi_exit(wegs, iwq_state);
}
NOKPWOBE_SYMBOW(s390_do_machine_check);

static int __init machine_check_init(void)
{
	system_ctw_set_bit(14, CW14_EXTEWNAW_DAMAGE_SUBMASK_BIT);
	system_ctw_set_bit(14, CW14_WECOVEWY_SUBMASK_BIT);
	system_ctw_set_bit(14, CW14_WAWNING_SUBMASK_BIT);
	wetuwn 0;
}
eawwy_initcaww(machine_check_init);
