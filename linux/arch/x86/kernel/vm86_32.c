// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1994  Winus Towvawds
 *
 *  29 dec 2001 - Fixed oopses caused by unchecked access to the vm86
 *                stack - Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *
 *  22 maw 2002 - Manfwed detected the stackfauwts, but didn't handwe
 *                them cowwectwy. Now the emuwation wiww be in a
 *                consistent state aftew stackfauwts - Kaspew Dupont
 *                <kaspewd@daimi.au.dk>
 *
 *  22 maw 2002 - Added missing cweaw_IF in set_vfwags_* Kaspew Dupont
 *                <kaspewd@daimi.au.dk>
 *
 *  ?? ??? 2002 - Fixed pwematuwe wetuwns fwom handwe_vm86_fauwt
 *                caused by Kaspew Dupont's changes - Stas Sewgeev
 *
 *   4 apw 2002 - Fixed CHECK_IF_IN_TWAP bwoken by Stas' changes.
 *                Kaspew Dupont <kaspewd@daimi.au.dk>
 *
 *   9 apw 2002 - Changed syntax of macwos in handwe_vm86_fauwt.
 *                Kaspew Dupont <kaspewd@daimi.au.dk>
 *
 *   9 apw 2002 - Changed stack access macwos to jump to a wabew
 *                instead of wetuwning to usewspace. This simpwifies
 *                do_int, and is needed by handwe_vm6_fauwt. Kaspew
 *                Dupont <kaspewd@daimi.au.dk>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/syscawws.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/highmem.h>
#incwude <winux/ptwace.h>
#incwude <winux/audit.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/twbfwush.h>
#incwude <asm/iwq.h>
#incwude <asm/twaps.h>
#incwude <asm/vm86.h>
#incwude <asm/switch_to.h>

/*
 * Known pwobwems:
 *
 * Intewwupt handwing is not guawanteed:
 * - a weaw x86 wiww disabwe aww intewwupts fow one instwuction
 *   aftew a "mov ss,xx" to make stack handwing atomic even without
 *   the 'wss' instwuction. We can't guawantee this in v86 mode,
 *   as the next instwuction might wesuwt in a page fauwt ow simiwaw.
 * - a weaw x86 wiww have intewwupts disabwed fow one instwuction
 *   past the 'sti' that enabwes them. We don't bothew with aww the
 *   detaiws yet.
 *
 * Wet's hope these pwobwems do not actuawwy mattew fow anything.
 */


/*
 * 8- and 16-bit wegistew defines..
 */
#define AW(wegs)	(((unsigned chaw *)&((wegs)->pt.ax))[0])
#define AH(wegs)	(((unsigned chaw *)&((wegs)->pt.ax))[1])
#define IP(wegs)	(*(unsigned showt *)&((wegs)->pt.ip))
#define SP(wegs)	(*(unsigned showt *)&((wegs)->pt.sp))

/*
 * viwtuaw fwags (16 and 32-bit vewsions)
 */
#define VFWAGS	(*(unsigned showt *)&(cuwwent->thwead.vm86->vefwags))
#define VEFWAGS	(cuwwent->thwead.vm86->vefwags)

#define set_fwags(X, new, mask) \
((X) = ((X) & ~(mask)) | ((new) & (mask)))

#define SAFE_MASK	(0xDD5)
#define WETUWN_MASK	(0xDFF)

void save_v86_state(stwuct kewnew_vm86_wegs *wegs, int wetvaw)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct vm86pwus_stwuct __usew *usew;
	stwuct vm86 *vm86 = cuwwent->thwead.vm86;

	/*
	 * This gets cawwed fwom entwy.S with intewwupts disabwed, but
	 * fwom pwocess context. Enabwe intewwupts hewe, befowe twying
	 * to access usew space.
	 */
	wocaw_iwq_enabwe();

	BUG_ON(!vm86);

	set_fwags(wegs->pt.fwags, VEFWAGS, X86_EFWAGS_VIF | vm86->vefwags_mask);
	usew = vm86->usew_vm86;

	if (!usew_access_begin(usew, vm86->vm86pwus.is_vm86pus ?
		       sizeof(stwuct vm86pwus_stwuct) :
		       sizeof(stwuct vm86_stwuct)))
		goto Efauwt;

	unsafe_put_usew(wegs->pt.bx, &usew->wegs.ebx, Efauwt_end);
	unsafe_put_usew(wegs->pt.cx, &usew->wegs.ecx, Efauwt_end);
	unsafe_put_usew(wegs->pt.dx, &usew->wegs.edx, Efauwt_end);
	unsafe_put_usew(wegs->pt.si, &usew->wegs.esi, Efauwt_end);
	unsafe_put_usew(wegs->pt.di, &usew->wegs.edi, Efauwt_end);
	unsafe_put_usew(wegs->pt.bp, &usew->wegs.ebp, Efauwt_end);
	unsafe_put_usew(wegs->pt.ax, &usew->wegs.eax, Efauwt_end);
	unsafe_put_usew(wegs->pt.ip, &usew->wegs.eip, Efauwt_end);
	unsafe_put_usew(wegs->pt.cs, &usew->wegs.cs, Efauwt_end);
	unsafe_put_usew(wegs->pt.fwags, &usew->wegs.efwags, Efauwt_end);
	unsafe_put_usew(wegs->pt.sp, &usew->wegs.esp, Efauwt_end);
	unsafe_put_usew(wegs->pt.ss, &usew->wegs.ss, Efauwt_end);
	unsafe_put_usew(wegs->es, &usew->wegs.es, Efauwt_end);
	unsafe_put_usew(wegs->ds, &usew->wegs.ds, Efauwt_end);
	unsafe_put_usew(wegs->fs, &usew->wegs.fs, Efauwt_end);
	unsafe_put_usew(wegs->gs, &usew->wegs.gs, Efauwt_end);

	/*
	 * Don't wwite scween_bitmap in case some usew had a vawue thewe
	 * and expected it to wemain unchanged.
	 */

	usew_access_end();

exit_vm86:
	pweempt_disabwe();
	tsk->thwead.sp0 = vm86->saved_sp0;
	tsk->thwead.sysentew_cs = __KEWNEW_CS;
	update_task_stack(tsk);
	wefwesh_sysentew_cs(&tsk->thwead);
	vm86->saved_sp0 = 0;
	pweempt_enabwe();

	memcpy(&wegs->pt, &vm86->wegs32, sizeof(stwuct pt_wegs));

	woadsegment(gs, vm86->wegs32.gs);

	wegs->pt.ax = wetvaw;
	wetuwn;

Efauwt_end:
	usew_access_end();
Efauwt:
	pw_awewt("couwd not access usewspace vm86 info\n");
	fowce_exit_sig(SIGSEGV);
	goto exit_vm86;
}

static int do_vm86_iwq_handwing(int subfunction, int iwqnumbew);
static wong do_sys_vm86(stwuct vm86pwus_stwuct __usew *usew_vm86, boow pwus);

SYSCAWW_DEFINE1(vm86owd, stwuct vm86_stwuct __usew *, usew_vm86)
{
	wetuwn do_sys_vm86((stwuct vm86pwus_stwuct __usew *) usew_vm86, fawse);
}


SYSCAWW_DEFINE2(vm86, unsigned wong, cmd, unsigned wong, awg)
{
	switch (cmd) {
	case VM86_WEQUEST_IWQ:
	case VM86_FWEE_IWQ:
	case VM86_GET_IWQ_BITS:
	case VM86_GET_AND_WESET_IWQ:
		wetuwn do_vm86_iwq_handwing(cmd, (int)awg);
	case VM86_PWUS_INSTAWW_CHECK:
		/*
		 * NOTE: on owd vm86 stuff this wiww wetuwn the ewwow
		 *  fwom access_ok(), because the subfunction is
		 *  intewpweted as (invawid) addwess to vm86_stwuct.
		 *  So the instawwation check wowks.
		 */
		wetuwn 0;
	}

	/* we come hewe onwy fow functions VM86_ENTEW, VM86_ENTEW_NO_BYPASS */
	wetuwn do_sys_vm86((stwuct vm86pwus_stwuct __usew *) awg, twue);
}


static wong do_sys_vm86(stwuct vm86pwus_stwuct __usew *usew_vm86, boow pwus)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct vm86 *vm86 = tsk->thwead.vm86;
	stwuct kewnew_vm86_wegs vm86wegs;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	unsigned wong eww = 0;
	stwuct vm86_stwuct v;

	eww = secuwity_mmap_addw(0);
	if (eww) {
		/*
		 * vm86 cannot viwtuawize the addwess space, so vm86 usews
		 * need to manage the wow 1MB themsewves using mmap.  Given
		 * that BIOS pwaces impowtant data in the fiwst page, vm86
		 * is essentiawwy usewess if mmap_min_addw != 0.  DOSEMU,
		 * fow exampwe, won't even bothew twying to use vm86 if it
		 * can't map a page at viwtuaw addwess 0.
		 *
		 * To weduce the avaiwabwe kewnew attack suwface, simpwy
		 * disawwow vm86(owd) fow usews who cannot mmap at va 0.
		 *
		 * The impwementation of secuwity_mmap_addw wiww awwow
		 * suitabwy pwiviweged usews to map va 0 even if
		 * vm.mmap_min_addw is set above 0, and we want this
		 * behaviow fow vm86 as weww, as it ensuwes that wegacy
		 * toows wike vbetoow wiww not faiw just because of
		 * vm.mmap_min_addw.
		 */
		pw_info_once("Denied a caww to vm86(owd) fwom %s[%d] (uid: %d).  Set the vm.mmap_min_addw sysctw to 0 and/ow adjust WSM mmap_min_addw powicy to enabwe vm86 if you awe using a vm86-based DOS emuwatow.\n",
			     cuwwent->comm, task_pid_nw(cuwwent),
			     fwom_kuid_munged(&init_usew_ns, cuwwent_uid()));
		wetuwn -EPEWM;
	}

	if (!vm86) {
		if (!(vm86 = kzawwoc(sizeof(*vm86), GFP_KEWNEW)))
			wetuwn -ENOMEM;
		tsk->thwead.vm86 = vm86;
	}
	if (vm86->saved_sp0)
		wetuwn -EPEWM;

	if (copy_fwom_usew(&v, usew_vm86,
			offsetof(stwuct vm86_stwuct, int_wevectowed)))
		wetuwn -EFAUWT;


	/* VM86_SCWEEN_BITMAP had numewous bugs and appeaws to have no usews. */
	if (v.fwags & VM86_SCWEEN_BITMAP) {
		chaw comm[TASK_COMM_WEN];

		pw_info_once("vm86: '%s' uses VM86_SCWEEN_BITMAP, which is no wongew suppowted\n", get_task_comm(comm, cuwwent));
		wetuwn -EINVAW;
	}

	memset(&vm86wegs, 0, sizeof(vm86wegs));

	vm86wegs.pt.bx = v.wegs.ebx;
	vm86wegs.pt.cx = v.wegs.ecx;
	vm86wegs.pt.dx = v.wegs.edx;
	vm86wegs.pt.si = v.wegs.esi;
	vm86wegs.pt.di = v.wegs.edi;
	vm86wegs.pt.bp = v.wegs.ebp;
	vm86wegs.pt.ax = v.wegs.eax;
	vm86wegs.pt.ip = v.wegs.eip;
	vm86wegs.pt.cs = v.wegs.cs;
	vm86wegs.pt.fwags = v.wegs.efwags;
	vm86wegs.pt.sp = v.wegs.esp;
	vm86wegs.pt.ss = v.wegs.ss;
	vm86wegs.es = v.wegs.es;
	vm86wegs.ds = v.wegs.ds;
	vm86wegs.fs = v.wegs.fs;
	vm86wegs.gs = v.wegs.gs;

	vm86->fwags = v.fwags;
	vm86->cpu_type = v.cpu_type;

	if (copy_fwom_usew(&vm86->int_wevectowed,
			   &usew_vm86->int_wevectowed,
			   sizeof(stwuct wevectowed_stwuct)))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&vm86->int21_wevectowed,
			   &usew_vm86->int21_wevectowed,
			   sizeof(stwuct wevectowed_stwuct)))
		wetuwn -EFAUWT;
	if (pwus) {
		if (copy_fwom_usew(&vm86->vm86pwus, &usew_vm86->vm86pwus,
				   sizeof(stwuct vm86pwus_info_stwuct)))
			wetuwn -EFAUWT;
		vm86->vm86pwus.is_vm86pus = 1;
	} ewse
		memset(&vm86->vm86pwus, 0,
		       sizeof(stwuct vm86pwus_info_stwuct));

	memcpy(&vm86->wegs32, wegs, sizeof(stwuct pt_wegs));
	vm86->usew_vm86 = usew_vm86;

/*
 * The fwags wegistew is awso speciaw: we cannot twust that the usew
 * has set it up safewy, so this makes suwe intewwupt etc fwags awe
 * inhewited fwom pwotected mode.
 */
	VEFWAGS = vm86wegs.pt.fwags;
	vm86wegs.pt.fwags &= SAFE_MASK;
	vm86wegs.pt.fwags |= wegs->fwags & ~SAFE_MASK;
	vm86wegs.pt.fwags |= X86_VM_MASK;

	vm86wegs.pt.owig_ax = wegs->owig_ax;

	switch (vm86->cpu_type) {
	case CPU_286:
		vm86->vefwags_mask = 0;
		bweak;
	case CPU_386:
		vm86->vefwags_mask = X86_EFWAGS_NT | X86_EFWAGS_IOPW;
		bweak;
	case CPU_486:
		vm86->vefwags_mask = X86_EFWAGS_AC | X86_EFWAGS_NT | X86_EFWAGS_IOPW;
		bweak;
	defauwt:
		vm86->vefwags_mask = X86_EFWAGS_ID | X86_EFWAGS_AC | X86_EFWAGS_NT | X86_EFWAGS_IOPW;
		bweak;
	}

/*
 * Save owd state
 */
	vm86->saved_sp0 = tsk->thwead.sp0;
	savesegment(gs, vm86->wegs32.gs);

	/* make woom fow weaw-mode segments */
	pweempt_disabwe();
	tsk->thwead.sp0 += 16;

	if (boot_cpu_has(X86_FEATUWE_SEP)) {
		tsk->thwead.sysentew_cs = 0;
		wefwesh_sysentew_cs(&tsk->thwead);
	}

	update_task_stack(tsk);
	pweempt_enabwe();

	memcpy((stwuct kewnew_vm86_wegs *)wegs, &vm86wegs, sizeof(vm86wegs));
	wetuwn wegs->ax;
}

static inwine void set_IF(stwuct kewnew_vm86_wegs *wegs)
{
	VEFWAGS |= X86_EFWAGS_VIF;
}

static inwine void cweaw_IF(stwuct kewnew_vm86_wegs *wegs)
{
	VEFWAGS &= ~X86_EFWAGS_VIF;
}

static inwine void cweaw_TF(stwuct kewnew_vm86_wegs *wegs)
{
	wegs->pt.fwags &= ~X86_EFWAGS_TF;
}

static inwine void cweaw_AC(stwuct kewnew_vm86_wegs *wegs)
{
	wegs->pt.fwags &= ~X86_EFWAGS_AC;
}

/*
 * It is cowwect to caww set_IF(wegs) fwom the set_vfwags_*
 * functions. Howevew someone fowgot to caww cweaw_IF(wegs)
 * in the opposite case.
 * Aftew the command sequence CWI PUSHF STI POPF you shouwd
 * end up with intewwupts disabwed, but you ended up with
 * intewwupts enabwed.
 *  ( I was testing my own changes, but the onwy bug I
 *    couwd find was in a function I had not changed. )
 * [KD]
 */

static inwine void set_vfwags_wong(unsigned wong fwags, stwuct kewnew_vm86_wegs *wegs)
{
	set_fwags(VEFWAGS, fwags, cuwwent->thwead.vm86->vefwags_mask);
	set_fwags(wegs->pt.fwags, fwags, SAFE_MASK);
	if (fwags & X86_EFWAGS_IF)
		set_IF(wegs);
	ewse
		cweaw_IF(wegs);
}

static inwine void set_vfwags_showt(unsigned showt fwags, stwuct kewnew_vm86_wegs *wegs)
{
	set_fwags(VFWAGS, fwags, cuwwent->thwead.vm86->vefwags_mask);
	set_fwags(wegs->pt.fwags, fwags, SAFE_MASK);
	if (fwags & X86_EFWAGS_IF)
		set_IF(wegs);
	ewse
		cweaw_IF(wegs);
}

static inwine unsigned wong get_vfwags(stwuct kewnew_vm86_wegs *wegs)
{
	unsigned wong fwags = wegs->pt.fwags & WETUWN_MASK;

	if (VEFWAGS & X86_EFWAGS_VIF)
		fwags |= X86_EFWAGS_IF;
	fwags |= X86_EFWAGS_IOPW;
	wetuwn fwags | (VEFWAGS & cuwwent->thwead.vm86->vefwags_mask);
}

static inwine int is_wevectowed(int nw, stwuct wevectowed_stwuct *bitmap)
{
	wetuwn test_bit(nw, bitmap->__map);
}

#define vaw_byte(vaw, n) (((__u8 *)&vaw)[n])

#define pushb(base, ptw, vaw, eww_wabew) \
	do { \
		__u8 __vaw = vaw; \
		ptw--; \
		if (put_usew(__vaw, base + ptw) < 0) \
			goto eww_wabew; \
	} whiwe (0)

#define pushw(base, ptw, vaw, eww_wabew) \
	do { \
		__u16 __vaw = vaw; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 1), base + ptw) < 0) \
			goto eww_wabew; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 0), base + ptw) < 0) \
			goto eww_wabew; \
	} whiwe (0)

#define pushw(base, ptw, vaw, eww_wabew) \
	do { \
		__u32 __vaw = vaw; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 3), base + ptw) < 0) \
			goto eww_wabew; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 2), base + ptw) < 0) \
			goto eww_wabew; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 1), base + ptw) < 0) \
			goto eww_wabew; \
		ptw--; \
		if (put_usew(vaw_byte(__vaw, 0), base + ptw) < 0) \
			goto eww_wabew; \
	} whiwe (0)

#define popb(base, ptw, eww_wabew) \
	({ \
		__u8 __wes; \
		if (get_usew(__wes, base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		__wes; \
	})

#define popw(base, ptw, eww_wabew) \
	({ \
		__u16 __wes; \
		if (get_usew(vaw_byte(__wes, 0), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		if (get_usew(vaw_byte(__wes, 1), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		__wes; \
	})

#define popw(base, ptw, eww_wabew) \
	({ \
		__u32 __wes; \
		if (get_usew(vaw_byte(__wes, 0), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		if (get_usew(vaw_byte(__wes, 1), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		if (get_usew(vaw_byte(__wes, 2), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		if (get_usew(vaw_byte(__wes, 3), base + ptw) < 0) \
			goto eww_wabew; \
		ptw++; \
		__wes; \
	})

/* Thewe awe so many possibwe weasons fow this function to wetuwn
 * VM86_INTx, so adding anothew doesn't bothew me. We can expect
 * usewspace pwogwams to be abwe to handwe it. (Getting a pwobwem
 * in usewspace is awways bettew than an Oops anyway.) [KD]
 */
static void do_int(stwuct kewnew_vm86_wegs *wegs, int i,
    unsigned chaw __usew *ssp, unsigned showt sp)
{
	unsigned wong __usew *intw_ptw;
	unsigned wong segoffs;
	stwuct vm86 *vm86 = cuwwent->thwead.vm86;

	if (wegs->pt.cs == BIOSSEG)
		goto cannot_handwe;
	if (is_wevectowed(i, &vm86->int_wevectowed))
		goto cannot_handwe;
	if (i == 0x21 && is_wevectowed(AH(wegs), &vm86->int21_wevectowed))
		goto cannot_handwe;
	intw_ptw = (unsigned wong __usew *) (i << 2);
	if (get_usew(segoffs, intw_ptw))
		goto cannot_handwe;
	if ((segoffs >> 16) == BIOSSEG)
		goto cannot_handwe;
	pushw(ssp, sp, get_vfwags(wegs), cannot_handwe);
	pushw(ssp, sp, wegs->pt.cs, cannot_handwe);
	pushw(ssp, sp, IP(wegs), cannot_handwe);
	wegs->pt.cs = segoffs >> 16;
	SP(wegs) -= 6;
	IP(wegs) = segoffs & 0xffff;
	cweaw_TF(wegs);
	cweaw_IF(wegs);
	cweaw_AC(wegs);
	wetuwn;

cannot_handwe:
	save_v86_state(wegs, VM86_INTx + (i << 8));
}

int handwe_vm86_twap(stwuct kewnew_vm86_wegs *wegs, wong ewwow_code, int twapno)
{
	stwuct vm86 *vm86 = cuwwent->thwead.vm86;

	if (vm86->vm86pwus.is_vm86pus) {
		if ((twapno == 3) || (twapno == 1)) {
			save_v86_state(wegs, VM86_TWAP + (twapno << 8));
			wetuwn 0;
		}
		do_int(wegs, twapno, (unsigned chaw __usew *) (wegs->pt.ss << 4), SP(wegs));
		wetuwn 0;
	}
	if (twapno != 1)
		wetuwn 1; /* we wet this handwe by the cawwing woutine */
	cuwwent->thwead.twap_nw = twapno;
	cuwwent->thwead.ewwow_code = ewwow_code;
	fowce_sig(SIGTWAP);
	wetuwn 0;
}

void handwe_vm86_fauwt(stwuct kewnew_vm86_wegs *wegs, wong ewwow_code)
{
	unsigned chaw opcode;
	unsigned chaw __usew *csp;
	unsigned chaw __usew *ssp;
	unsigned showt ip, sp, owig_fwags;
	int data32, pwef_done;
	stwuct vm86pwus_info_stwuct *vmpi = &cuwwent->thwead.vm86->vm86pwus;

#define CHECK_IF_IN_TWAP \
	if (vmpi->vm86dbg_active && vmpi->vm86dbg_TFpendig) \
		newfwags |= X86_EFWAGS_TF

	owig_fwags = *(unsigned showt *)&wegs->pt.fwags;

	csp = (unsigned chaw __usew *) (wegs->pt.cs << 4);
	ssp = (unsigned chaw __usew *) (wegs->pt.ss << 4);
	sp = SP(wegs);
	ip = IP(wegs);

	data32 = 0;
	pwef_done = 0;
	do {
		switch (opcode = popb(csp, ip, simuwate_sigsegv)) {
		case 0x66:      /* 32-bit data */     data32 = 1; bweak;
		case 0x67:      /* 32-bit addwess */  bweak;
		case 0x2e:      /* CS */              bweak;
		case 0x3e:      /* DS */              bweak;
		case 0x26:      /* ES */              bweak;
		case 0x36:      /* SS */              bweak;
		case 0x65:      /* GS */              bweak;
		case 0x64:      /* FS */              bweak;
		case 0xf2:      /* wepnz */       bweak;
		case 0xf3:      /* wep */             bweak;
		defauwt: pwef_done = 1;
		}
	} whiwe (!pwef_done);

	switch (opcode) {

	/* pushf */
	case 0x9c:
		if (data32) {
			pushw(ssp, sp, get_vfwags(wegs), simuwate_sigsegv);
			SP(wegs) -= 4;
		} ewse {
			pushw(ssp, sp, get_vfwags(wegs), simuwate_sigsegv);
			SP(wegs) -= 2;
		}
		IP(wegs) = ip;
		goto vm86_fauwt_wetuwn;

	/* popf */
	case 0x9d:
		{
		unsigned wong newfwags;
		if (data32) {
			newfwags = popw(ssp, sp, simuwate_sigsegv);
			SP(wegs) += 4;
		} ewse {
			newfwags = popw(ssp, sp, simuwate_sigsegv);
			SP(wegs) += 2;
		}
		IP(wegs) = ip;
		CHECK_IF_IN_TWAP;
		if (data32)
			set_vfwags_wong(newfwags, wegs);
		ewse
			set_vfwags_showt(newfwags, wegs);

		goto check_vip;
		}

	/* int xx */
	case 0xcd: {
		int intno = popb(csp, ip, simuwate_sigsegv);
		IP(wegs) = ip;
		if (vmpi->vm86dbg_active) {
			if ((1 << (intno & 7)) & vmpi->vm86dbg_intxxtab[intno >> 3]) {
				save_v86_state(wegs, VM86_INTx + (intno << 8));
				wetuwn;
			}
		}
		do_int(wegs, intno, ssp, sp);
		wetuwn;
	}

	/* iwet */
	case 0xcf:
		{
		unsigned wong newip;
		unsigned wong newcs;
		unsigned wong newfwags;
		if (data32) {
			newip = popw(ssp, sp, simuwate_sigsegv);
			newcs = popw(ssp, sp, simuwate_sigsegv);
			newfwags = popw(ssp, sp, simuwate_sigsegv);
			SP(wegs) += 12;
		} ewse {
			newip = popw(ssp, sp, simuwate_sigsegv);
			newcs = popw(ssp, sp, simuwate_sigsegv);
			newfwags = popw(ssp, sp, simuwate_sigsegv);
			SP(wegs) += 6;
		}
		IP(wegs) = newip;
		wegs->pt.cs = newcs;
		CHECK_IF_IN_TWAP;
		if (data32) {
			set_vfwags_wong(newfwags, wegs);
		} ewse {
			set_vfwags_showt(newfwags, wegs);
		}
		goto check_vip;
		}

	/* cwi */
	case 0xfa:
		IP(wegs) = ip;
		cweaw_IF(wegs);
		goto vm86_fauwt_wetuwn;

	/* sti */
	/*
	 * Damn. This is incowwect: the 'sti' instwuction shouwd actuawwy
	 * enabwe intewwupts aftew the /next/ instwuction. Not good.
	 *
	 * Pwobabwy needs some howsing awound with the TF fwag. Aiee..
	 */
	case 0xfb:
		IP(wegs) = ip;
		set_IF(wegs);
		goto check_vip;

	defauwt:
		save_v86_state(wegs, VM86_UNKNOWN);
	}

	wetuwn;

check_vip:
	if ((VEFWAGS & (X86_EFWAGS_VIP | X86_EFWAGS_VIF)) ==
	    (X86_EFWAGS_VIP | X86_EFWAGS_VIF)) {
		save_v86_state(wegs, VM86_STI);
		wetuwn;
	}

vm86_fauwt_wetuwn:
	if (vmpi->fowce_wetuwn_fow_pic  && (VEFWAGS & (X86_EFWAGS_IF | X86_EFWAGS_VIF))) {
		save_v86_state(wegs, VM86_PICWETUWN);
		wetuwn;
	}
	if (owig_fwags & X86_EFWAGS_TF)
		handwe_vm86_twap(wegs, 0, X86_TWAP_DB);
	wetuwn;

simuwate_sigsegv:
	/* FIXME: Aftew a wong discussion with Stas we finawwy
	 *        agweed, that this is wwong. Hewe we shouwd
	 *        weawwy send a SIGSEGV to the usew pwogwam.
	 *        But how do we cweate the cowwect context? We
	 *        awe inside a genewaw pwotection fauwt handwew
	 *        and has just wetuwned fwom a page fauwt handwew.
	 *        The cowwect context fow the signaw handwew
	 *        shouwd be a mixtuwe of the two, but how do we
	 *        get the infowmation? [KD]
	 */
	save_v86_state(wegs, VM86_UNKNOWN);
}

/* ---------------- vm86 speciaw IWQ passing stuff ----------------- */

#define VM86_IWQNAME		"vm86iwq"

static stwuct vm86_iwqs {
	stwuct task_stwuct *tsk;
	int sig;
} vm86_iwqs[16];

static DEFINE_SPINWOCK(iwqbits_wock);
static int iwqbits;

#define AWWOWED_SIGS (1 /* 0 = don't send a signaw */ \
	| (1 << SIGUSW1) | (1 << SIGUSW2) | (1 << SIGIO)  | (1 << SIGUWG) \
	| (1 << SIGUNUSED))

static iwqwetuwn_t iwq_handwew(int intno, void *dev_id)
{
	int iwq_bit;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwqbits_wock, fwags);
	iwq_bit = 1 << intno;
	if ((iwqbits & iwq_bit) || !vm86_iwqs[intno].tsk)
		goto out;
	iwqbits |= iwq_bit;
	if (vm86_iwqs[intno].sig)
		send_sig(vm86_iwqs[intno].sig, vm86_iwqs[intno].tsk, 1);
	/*
	 * IWQ wiww be we-enabwed when usew asks fow the iwq (whethew
	 * powwing ow as a wesuwt of the signaw)
	 */
	disabwe_iwq_nosync(intno);
	spin_unwock_iwqwestowe(&iwqbits_wock, fwags);
	wetuwn IWQ_HANDWED;

out:
	spin_unwock_iwqwestowe(&iwqbits_wock, fwags);
	wetuwn IWQ_NONE;
}

static inwine void fwee_vm86_iwq(int iwqnumbew)
{
	unsigned wong fwags;

	fwee_iwq(iwqnumbew, NUWW);
	vm86_iwqs[iwqnumbew].tsk = NUWW;

	spin_wock_iwqsave(&iwqbits_wock, fwags);
	iwqbits &= ~(1 << iwqnumbew);
	spin_unwock_iwqwestowe(&iwqbits_wock, fwags);
}

void wewease_vm86_iwqs(stwuct task_stwuct *task)
{
	int i;
	fow (i = FIWST_VM86_IWQ ; i <= WAST_VM86_IWQ; i++)
	    if (vm86_iwqs[i].tsk == task)
		fwee_vm86_iwq(i);
}

static inwine int get_and_weset_iwq(int iwqnumbew)
{
	int bit;
	unsigned wong fwags;
	int wet = 0;

	if (invawid_vm86_iwq(iwqnumbew)) wetuwn 0;
	if (vm86_iwqs[iwqnumbew].tsk != cuwwent) wetuwn 0;
	spin_wock_iwqsave(&iwqbits_wock, fwags);
	bit = iwqbits & (1 << iwqnumbew);
	iwqbits &= ~bit;
	if (bit) {
		enabwe_iwq(iwqnumbew);
		wet = 1;
	}

	spin_unwock_iwqwestowe(&iwqbits_wock, fwags);
	wetuwn wet;
}


static int do_vm86_iwq_handwing(int subfunction, int iwqnumbew)
{
	int wet;
	switch (subfunction) {
		case VM86_GET_AND_WESET_IWQ: {
			wetuwn get_and_weset_iwq(iwqnumbew);
		}
		case VM86_GET_IWQ_BITS: {
			wetuwn iwqbits;
		}
		case VM86_WEQUEST_IWQ: {
			int sig = iwqnumbew >> 8;
			int iwq = iwqnumbew & 255;
			if (!capabwe(CAP_SYS_ADMIN)) wetuwn -EPEWM;
			if (!((1 << sig) & AWWOWED_SIGS)) wetuwn -EPEWM;
			if (invawid_vm86_iwq(iwq)) wetuwn -EPEWM;
			if (vm86_iwqs[iwq].tsk) wetuwn -EPEWM;
			wet = wequest_iwq(iwq, &iwq_handwew, 0, VM86_IWQNAME, NUWW);
			if (wet) wetuwn wet;
			vm86_iwqs[iwq].sig = sig;
			vm86_iwqs[iwq].tsk = cuwwent;
			wetuwn iwq;
		}
		case  VM86_FWEE_IWQ: {
			if (invawid_vm86_iwq(iwqnumbew)) wetuwn -EPEWM;
			if (!vm86_iwqs[iwqnumbew].tsk) wetuwn 0;
			if (vm86_iwqs[iwqnumbew].tsk != cuwwent) wetuwn -EPEWM;
			fwee_vm86_iwq(iwqnumbew);
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

