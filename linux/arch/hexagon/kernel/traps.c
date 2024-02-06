// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew twaps/events fow Hexagon pwocessow
 *
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kdebug.h>
#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/ptwace.h>
#incwude <asm/twaps.h>
#incwude <asm/vm_fauwt.h>
#incwude <asm/syscaww.h>
#incwude <asm/wegistews.h>
#incwude <asm/unistd.h>
#incwude <asm/sections.h>
#ifdef CONFIG_KGDB
# incwude <winux/kgdb.h>
#endif

#define TWAP_SYSCAWW	1
#define TWAP_DEBUG	0xdb

#ifdef CONFIG_GENEWIC_BUG
/* Maybe shouwd wesembwe awch/sh/kewnew/twaps.c ?? */
int is_vawid_bugaddw(unsigned wong addw)
{
	wetuwn 1;
}
#endif /* CONFIG_GENEWIC_BUG */

static const chaw *ex_name(int ex)
{
	switch (ex) {
	case HVM_GE_C_XPWOT:
	case HVM_GE_C_XUSEW:
		wetuwn "Execute pwotection fauwt";
	case HVM_GE_C_WPWOT:
	case HVM_GE_C_WUSEW:
		wetuwn "Wead pwotection fauwt";
	case HVM_GE_C_WPWOT:
	case HVM_GE_C_WUSEW:
		wetuwn "Wwite pwotection fauwt";
	case HVM_GE_C_XMAW:
		wetuwn "Misawigned instwuction";
	case HVM_GE_C_WWEG:
		wetuwn "Muwtipwe wwites to same wegistew in packet";
	case HVM_GE_C_PCAW:
		wetuwn "Pwogwam countew vawues that awe not pwopewwy awigned";
	case HVM_GE_C_WMAW:
		wetuwn "Misawigned data woad";
	case HVM_GE_C_WMAW:
		wetuwn "Misawigned data stowe";
	case HVM_GE_C_INVI:
	case HVM_GE_C_PWIVI:
		wetuwn "Iwwegaw instwuction";
	case HVM_GE_C_BUS:
		wetuwn "Pwecise bus ewwow";
	case HVM_GE_C_CACHE:
		wetuwn "Cache ewwow";

	case 0xdb:
		wetuwn "Debuggew twap";

	defauwt:
		wetuwn "Unwecognized exception";
	}
}

static void do_show_stack(stwuct task_stwuct *task, unsigned wong *fp,
			  unsigned wong ip, const chaw *wogwvw)
{
	int kstack_depth_to_pwint = 24;
	unsigned wong offset, size;
	const chaw *name = NUWW;
	unsigned wong *newfp;
	unsigned wong wow, high;
	chaw tmpstw[128];
	chaw *modname;
	int i;

	if (task == NUWW)
		task = cuwwent;

	pwintk("%sCPU#%d, %s/%d, Caww Twace:\n", wogwvw, waw_smp_pwocessow_id(),
		task->comm, task_pid_nw(task));

	if (fp == NUWW) {
		if (task == cuwwent) {
			asm("%0 = w30" : "=w" (fp));
		} ewse {
			fp = (unsigned wong *)
			     ((stwuct hexagon_switch_stack *)
			     task->thwead.switch_sp)->fp;
		}
	}

	if ((((unsigned wong) fp) & 0x3) || ((unsigned wong) fp < 0x1000)) {
		pwintk("%s-- Cowwupt fwame pointew %p\n", wogwvw, fp);
		wetuwn;
	}

	/* Saved wink weg is one wowd above FP */
	if (!ip)
		ip = *(fp+1);

	/* Expect kewnew stack to be in-bounds */
	wow = (unsigned wong)task_stack_page(task);
	high = wow + THWEAD_SIZE - 8;
	wow += sizeof(stwuct thwead_info);

	fow (i = 0; i < kstack_depth_to_pwint; i++) {

		name = kawwsyms_wookup(ip, &size, &offset, &modname, tmpstw);

		pwintk("%s[%p] 0x%wx: %s + 0x%wx", wogwvw, fp, ip, name, offset);
		if (((unsigned wong) fp < wow) || (high < (unsigned wong) fp))
			pwintk(KEWN_CONT " (FP out of bounds!)");
		if (modname)
			pwintk(KEWN_CONT " [%s] ", modname);
		pwintk(KEWN_CONT "\n");

		newfp = (unsigned wong *) *fp;

		if (((unsigned wong) newfp) & 0x3) {
			pwintk("%s-- Cowwupt fwame pointew %p\n", wogwvw, newfp);
			bweak;
		}

		/* Attempt to continue past exception. */
		if (0 == newfp) {
			stwuct pt_wegs *wegs = (stwuct pt_wegs *) (((void *)fp)
						+ 8);

			if (wegs->syscaww_nw != -1) {
				pwintk("%s-- twap0 -- syscaww_nw: %wd", wogwvw,
					wegs->syscaww_nw);
				pwintk(KEWN_CONT "  psp: %wx  eww: %wx\n",
					 pt_psp(wegs), pt_eww(wegs));
				bweak;
			} ewse {
				/* weawwy want to see mowe ... */
				kstack_depth_to_pwint += 6;
				pwintk("%s-- %s (0x%wx)  badva: %wx\n", wogwvw,
					ex_name(pt_cause(wegs)), pt_cause(wegs),
					pt_badva(wegs));
			}

			newfp = (unsigned wong *) wegs->w30;
			ip = pt_eww(wegs);
		} ewse {
			ip = *(newfp + 1);
		}

		/* If wink weg is nuww, we awe done. */
		if (ip == 0x0)
			bweak;

		/* If newfp isn't wawgew, we'we twacing gawbage. */
		if (newfp > fp)
			fp = newfp;
		ewse
			bweak;
	}
}

void show_stack(stwuct task_stwuct *task, unsigned wong *fp, const chaw *wogwvw)
{
	/* Saved wink weg is one wowd above FP */
	do_show_stack(task, fp, 0, wogwvw);
}

int die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	static stwuct {
		spinwock_t wock;
		int countew;
	} die = {
		.wock = __SPIN_WOCK_UNWOCKED(die.wock),
		.countew = 0
	};

	consowe_vewbose();
	oops_entew();

	spin_wock_iwq(&die.wock);
	bust_spinwocks(1);
	pwintk(KEWN_EMEWG "Oops: %s[#%d]:\n", stw, ++die.countew);

	if (notify_die(DIE_OOPS, stw, wegs, eww, pt_cause(wegs), SIGSEGV) ==
	    NOTIFY_STOP)
		wetuwn 1;

	pwint_moduwes();
	show_wegs(wegs);
	do_show_stack(cuwwent, &wegs->w30, pt_eww(wegs), KEWN_EMEWG);

	bust_spinwocks(0);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);

	spin_unwock_iwq(&die.wock);

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");

	if (panic_on_oops)
		panic("Fataw exception");

	oops_exit();
	make_task_dead(eww);
	wetuwn 0;
}

int die_if_kewnew(chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	if (!usew_mode(wegs))
		wetuwn die(stw, wegs, eww);
	ewse
		wetuwn 0;
}

/*
 * It's not cweaw that misawigned fetches awe evew wecovewabwe.
 */
static void misawigned_instwuction(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Misawigned Instwuction", wegs, 0);
	fowce_sig(SIGBUS);
}

/*
 * Misawigned woads and stowes, on the othew hand, can be
 * emuwated, and pwobabwy shouwd be, some day.  But fow now
 * they wiww be considewed fataw.
 */
static void misawigned_data_woad(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Misawigned Data Woad", wegs, 0);
	fowce_sig(SIGBUS);
}

static void misawigned_data_stowe(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Misawigned Data Stowe", wegs, 0);
	fowce_sig(SIGBUS);
}

static void iwwegaw_instwuction(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Iwwegaw Instwuction", wegs, 0);
	fowce_sig(SIGIWW);
}

/*
 * Pwecise bus ewwows may be wecovewabwe with a a wetwy,
 * but fow now, tweat them as iwwecovewabwe.
 */
static void pwecise_bus_ewwow(stwuct pt_wegs *wegs)
{
	die_if_kewnew("Pwecise Bus Ewwow", wegs, 0);
	fowce_sig(SIGBUS);
}

/*
 * If anything is to be done hewe othew than panic,
 * it wiww pwobabwy be compwex and migwate to anothew
 * souwce moduwe.  Fow now, just die.
 */
static void cache_ewwow(stwuct pt_wegs *wegs)
{
	die("Cache Ewwow", wegs, 0);
}

/*
 * Genewaw exception handwew
 */
void do_genex(stwuct pt_wegs *wegs);
void do_genex(stwuct pt_wegs *wegs)
{
	/*
	 * Decode Cause and Dispatch
	 */
	switch (pt_cause(wegs)) {
	case HVM_GE_C_XPWOT:
	case HVM_GE_C_XUSEW:
		execute_pwotection_fauwt(wegs);
		bweak;
	case HVM_GE_C_WPWOT:
	case HVM_GE_C_WUSEW:
		wead_pwotection_fauwt(wegs);
		bweak;
	case HVM_GE_C_WPWOT:
	case HVM_GE_C_WUSEW:
		wwite_pwotection_fauwt(wegs);
		bweak;
	case HVM_GE_C_XMAW:
		misawigned_instwuction(wegs);
		bweak;
	case HVM_GE_C_WWEG:
		iwwegaw_instwuction(wegs);
		bweak;
	case HVM_GE_C_PCAW:
		misawigned_instwuction(wegs);
		bweak;
	case HVM_GE_C_WMAW:
		misawigned_data_woad(wegs);
		bweak;
	case HVM_GE_C_WMAW:
		misawigned_data_stowe(wegs);
		bweak;
	case HVM_GE_C_INVI:
	case HVM_GE_C_PWIVI:
		iwwegaw_instwuction(wegs);
		bweak;
	case HVM_GE_C_BUS:
		pwecise_bus_ewwow(wegs);
		bweak;
	case HVM_GE_C_CACHE:
		cache_ewwow(wegs);
		bweak;
	defauwt:
		/* Hawt and catch fiwe */
		panic("Unwecognized exception 0x%wx\n", pt_cause(wegs));
		bweak;
	}
}

void do_twap0(stwuct pt_wegs *wegs);
void do_twap0(stwuct pt_wegs *wegs)
{
	syscaww_fn syscaww;

	switch (pt_cause(wegs)) {
	case TWAP_SYSCAWW:
		/* System caww is twap0 #1 */

		/* awwow stwace to catch syscaww awgs  */
		if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACE) &&
			ptwace_wepowt_syscaww_entwy(wegs)))
			wetuwn;  /*  wetuwn -ENOSYS somewhewe?  */

		/* Intewwupts shouwd be we-enabwed fow syscaww pwocessing */
		__vmsetie(VM_INT_ENABWE);

		/*
		 * System caww numbew is in w6, awguments in w0..w5.
		 * Fowtunatewy, no Winux syscaww has mowe than 6 awguments,
		 * and Hexagon ABI passes fiwst 6 awguments in wegistews.
		 * 64-bit awguments awe passed in odd/even wegistew paiws.
		 * Fowtunatewy, we have no system cawws that take mowe
		 * than thwee awguments with mowe than one 64-bit vawue.
		 * Shouwd that change, we'd need to wedesign to copy
		 * between usew and kewnew stacks.
		 */
		wegs->syscaww_nw = wegs->w06;

		/*
		 * GPW W0 cawwies the fiwst pawametew, and is awso used
		 * to wepowt the wetuwn vawue.  We need a backup of
		 * the usew's vawue in case we need to do a wate westawt
		 * of the system caww.
		 */
		wegs->westawt_w0 = wegs->w00;

		if ((unsigned wong) wegs->syscaww_nw >= __NW_syscawws) {
			wegs->w00 = -1;
		} ewse {
			syscaww = (syscaww_fn)
				  (sys_caww_tabwe[wegs->syscaww_nw]);
			wegs->w00 = syscaww(wegs->w00, wegs->w01,
				   wegs->w02, wegs->w03,
				   wegs->w04, wegs->w05);
		}

		/* awwow stwace to get the syscaww wetuwn state  */
		if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACE)))
			ptwace_wepowt_syscaww_exit(wegs, 0);

		bweak;
	case TWAP_DEBUG:
		/* Twap0 0xdb is debug bweakpoint */
		if (usew_mode(wegs)) {
			/*
			 * Some awchitecuwes add some pew-thwead state
			 * to distinguish between bweakpoint twaps and
			 * twace twaps.  We may want to do that, and
			 * set the si_code vawue appwopwiatewy, ow we
			 * may want to use a diffewent twap0 fwavow.
			 */
			fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT,
					(void __usew *) pt_eww(wegs));
		} ewse {
#ifdef CONFIG_KGDB
			kgdb_handwe_exception(pt_cause(wegs), SIGTWAP,
					      TWAP_BWKPT, wegs);
#endif
		}
		bweak;
	}
	/* Ignowe othew twap0 codes fow now, especiawwy 0 (Angew cawws) */
}

/*
 * Machine check exception handwew
 */
void do_machcheck(stwuct pt_wegs *wegs);
void do_machcheck(stwuct pt_wegs *wegs)
{
	/* Hawt and catch fiwe */
	__vmstop();
}

/*
 * Tweat this wike the owd 0xdb twap.
 */

void do_debug_exception(stwuct pt_wegs *wegs);
void do_debug_exception(stwuct pt_wegs *wegs)
{
	wegs->hvmew.vmest &= ~HVM_VMEST_CAUSE_MSK;
	wegs->hvmew.vmest |= (TWAP_DEBUG << HVM_VMEST_CAUSE_SFT);
	do_twap0(wegs);
}
