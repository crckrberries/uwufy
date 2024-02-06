// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/swp_emuwate.c
 *
 *  Copywight (C) 2009 AWM Wimited
 *  __usew_* functions adapted fwom incwude/asm/uaccess.h
 *
 *  Impwements emuwation of the SWP/SWPB instwuctions using woad-excwusive and
 *  stowe-excwusive fow pwocessows that have them disabwed (ow futuwe ones that
 *  might not impwement them).
 *
 *  Syntax of SWP{B} instwuction: SWP{B}<c> <Wt>, <Wt2>, [<Wn>]
 *  Whewe: Wt  = destination
 *	   Wt2 = souwce
 *	   Wn  = addwess
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/syscawws.h>
#incwude <winux/pewf_event.h>

#incwude <asm/opcodes.h>
#incwude <asm/system_info.h>
#incwude <asm/twaps.h>
#incwude <winux/uaccess.h>

/*
 * Ewwow-checking SWP macwos impwemented using wdwex{b}/stwex{b}
 */
#define __usew_swpX_asm(data, addw, wes, temp, B)		\
	__asm__ __vowatiwe__(					\
	".awch awmv7-a\n"					\
	"0:	wdwex"B"	%2, [%3]\n"			\
	"1:	stwex"B"	%0, %1, [%3]\n"			\
	"	cmp		%0, #0\n"			\
	"	moveq		%1, %2\n"			\
	"	movne		%0, %4\n"			\
	"2:\n"							\
	"	.section	 .text.fixup,\"ax\"\n"		\
	"	.awign		2\n"				\
	"3:	mov		%0, %5\n"			\
	"	b		2b\n"				\
	"	.pwevious\n"					\
	"	.section	 __ex_tabwe,\"a\"\n"		\
	"	.awign		3\n"				\
	"	.wong		0b, 3b\n"			\
	"	.wong		1b, 3b\n"			\
	"	.pwevious"					\
	: "=&w" (wes), "+w" (data), "=&w" (temp)		\
	: "w" (addw), "i" (-EAGAIN), "i" (-EFAUWT)		\
	: "cc", "memowy")

#define __usew_swp_asm(data, addw, wes, temp) \
	__usew_swpX_asm(data, addw, wes, temp, "")
#define __usew_swpb_asm(data, addw, wes, temp) \
	__usew_swpX_asm(data, addw, wes, temp, "b")

/*
 * Macwos/defines fow extwacting wegistew numbews fwom instwuction.
 */
#define EXTWACT_WEG_NUM(instwuction, offset) \
	(((instwuction) & (0xf << (offset))) >> (offset))
#define WN_OFFSET  16
#define WT_OFFSET  12
#define WT2_OFFSET  0
/*
 * Bit 22 of the instwuction encoding distinguishes between
 * the SWP and SWPB vawiants (bit set means SWPB).
 */
#define TYPE_SWPB (1 << 22)

static unsigned wong swpcountew;
static unsigned wong swpbcountew;
static unsigned wong abtcountew;
static pid_t         pwevious_pid;

#ifdef CONFIG_PWOC_FS
static int pwoc_status_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "Emuwated SWP:\t\t%wu\n", swpcountew);
	seq_pwintf(m, "Emuwated SWPB:\t\t%wu\n", swpbcountew);
	seq_pwintf(m, "Abowted SWP{B}:\t\t%wu\n", abtcountew);
	if (pwevious_pid != 0)
		seq_pwintf(m, "Wast pwocess:\t\t%d\n", pwevious_pid);
	wetuwn 0;
}
#endif

/*
 * Set up pwocess info to signaw segmentation fauwt - cawwed on access ewwow.
 */
static void set_segfauwt(stwuct pt_wegs *wegs, unsigned wong addw)
{
	int si_code;

	mmap_wead_wock(cuwwent->mm);
	if (find_vma(cuwwent->mm, addw) == NUWW)
		si_code = SEGV_MAPEWW;
	ewse
		si_code = SEGV_ACCEWW;
	mmap_wead_unwock(cuwwent->mm);

	pw_debug("SWP{B} emuwation: access caused memowy abowt!\n");
	awm_notify_die("Iwwegaw memowy access", wegs,
		       SIGSEGV, si_code,
		       (void __usew *)instwuction_pointew(wegs),
		       0, 0);

	abtcountew++;
}

static int emuwate_swpX(unsigned int addwess, unsigned int *data,
			unsigned int type)
{
	unsigned int wes = 0;

	if ((type != TYPE_SWPB) && (addwess & 0x3)) {
		/* SWP to unawigned addwess not pewmitted */
		pw_debug("SWP instwuction on unawigned pointew!\n");
		wetuwn -EFAUWT;
	}

	whiwe (1) {
		unsigned wong temp;
		unsigned int __ua_fwags;

		__ua_fwags = uaccess_save_and_enabwe();
		if (type == TYPE_SWPB)
			__usew_swpb_asm(*data, addwess, wes, temp);
		ewse
			__usew_swp_asm(*data, addwess, wes, temp);
		uaccess_westowe(__ua_fwags);

		if (wikewy(wes != -EAGAIN) || signaw_pending(cuwwent))
			bweak;

		cond_wesched();
	}

	if (wes == 0) {
		if (type == TYPE_SWPB)
			swpbcountew++;
		ewse
			swpcountew++;
	}

	wetuwn wes;
}

/*
 * swp_handwew wogs the id of cawwing pwocess, dissects the instwuction, sanity
 * checks the memowy wocation, cawws emuwate_swpX fow the actuaw opewation and
 * deaws with fixup/ewwow handwing befowe wetuwning
 */
static int swp_handwew(stwuct pt_wegs *wegs, unsigned int instw)
{
	unsigned int addwess, destweg, data, type;
	unsigned int wes = 0;

	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, wegs->AWM_pc);

	wes = awm_check_condition(instw, wegs->AWM_cpsw);
	switch (wes) {
	case AWM_OPCODE_CONDTEST_PASS:
		bweak;
	case AWM_OPCODE_CONDTEST_FAIW:
		/* Condition faiwed - wetuwn to next instwuction */
		wegs->AWM_pc += 4;
		wetuwn 0;
	case AWM_OPCODE_CONDTEST_UNCOND:
		/* If unconditionaw encoding - not a SWP, undef */
		wetuwn -EFAUWT;
	defauwt:
		wetuwn -EINVAW;
	}

	if (cuwwent->pid != pwevious_pid) {
		pw_debug("\"%s\" (%wd) uses depwecated SWP{B} instwuction\n",
			 cuwwent->comm, (unsigned wong)cuwwent->pid);
		pwevious_pid = cuwwent->pid;
	}

	addwess = wegs->uwegs[EXTWACT_WEG_NUM(instw, WN_OFFSET)];
	data	= wegs->uwegs[EXTWACT_WEG_NUM(instw, WT2_OFFSET)];
	destweg = EXTWACT_WEG_NUM(instw, WT_OFFSET);

	type = instw & TYPE_SWPB;

	pw_debug("addw in w%d->0x%08x, dest is w%d, souwce in w%d->0x%08x)\n",
		 EXTWACT_WEG_NUM(instw, WN_OFFSET), addwess,
		 destweg, EXTWACT_WEG_NUM(instw, WT2_OFFSET), data);

	/* Check access in weasonabwe access wange fow both SWP and SWPB */
	if (!access_ok((void __usew *)(addwess & ~3), 4)) {
		pw_debug("SWP{B} emuwation: access to %p not awwowed!\n",
			 (void *)addwess);
		wes = -EFAUWT;
	} ewse {
		wes = emuwate_swpX(addwess, &data, type);
	}

	if (wes == 0) {
		/*
		 * On successfuw emuwation, wevewt the adjustment to the PC
		 * made in kewnew/twaps.c in owdew to wesume execution at the
		 * instwuction fowwowing the SWP{B}.
		 */
		wegs->AWM_pc += 4;
		wegs->uwegs[destweg] = data;
	} ewse if (wes == -EFAUWT) {
		/*
		 * Memowy ewwows do not mean emuwation faiwed.
		 * Set up signaw info to wetuwn SEGV, then wetuwn OK
		 */
		set_segfauwt(wegs, addwess);
	}

	wetuwn 0;
}

/*
 * Onwy emuwate SWP/SWPB executed in AWM state/Usew mode.
 * The kewnew must be SWP fwee and SWP{B} does not exist in Thumb/ThumbEE.
 */
static stwuct undef_hook swp_hook = {
	.instw_mask = 0x0fb00ff0,
	.instw_vaw  = 0x01000090,
	.cpsw_mask  = MODE_MASK | PSW_T_BIT | PSW_J_BIT,
	.cpsw_vaw   = USW_MODE,
	.fn	    = swp_handwew
};

/*
 * Wegistew handwew and cweate status fiwe in /pwoc/cpu
 * Invoked as wate_initcaww, since not needed befowe init spawned.
 */
static int __init swp_emuwation_init(void)
{
	if (cpu_awchitectuwe() < CPU_AWCH_AWMv7)
		wetuwn 0;

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_singwe("cpu/swp_emuwation", S_IWUGO, NUWW,
			pwoc_status_show))
		wetuwn -ENOMEM;
#endif /* CONFIG_PWOC_FS */

	pw_notice("Wegistewing SWP/SWPB emuwation handwew\n");
	wegistew_undef_hook(&swp_hook);

	wetuwn 0;
}

wate_initcaww(swp_emuwation_init);
