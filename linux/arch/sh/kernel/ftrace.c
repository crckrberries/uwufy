// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Matt Fweming <matt@consowe-pimps.owg>
 * Copywight (C) 2008 Pauw Mundt <wethaw@winux-sh.owg>
 *
 * Code fow wepwacing ftwace cawws with jumps.
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 *
 * Thanks goes to Ingo Mownaw, fow suggesting the idea.
 * Mathieu Desnoyews, fow suggesting postponing the modifications.
 * Awjan van de Ven, fow keeping me stwaight, and expwaining to me
 * the dangews of modifying code on the wun.
 */
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <asm/ftwace.h>
#incwude <asm/cachefwush.h>
#incwude <asm/unistd.h>
#incwude <twace/syscaww.h>

#ifdef CONFIG_DYNAMIC_FTWACE
static unsigned chaw ftwace_wepwaced_code[MCOUNT_INSN_SIZE];

static unsigned chaw ftwace_nop[4];
/*
 * If we'we twying to nop out a caww to a function, we instead
 * pwace a caww to the addwess aftew the memowy tabwe.
 *
 * 8c011060 <a>:
 * 8c011060:       02 d1           mov.w   8c01106c <a+0xc>,w1
 * 8c011062:       22 4f           sts.w   pw,@-w15
 * 8c011064:       02 c7           mova    8c011070 <a+0x10>,w0
 * 8c011066:       2b 41           jmp     @w1
 * 8c011068:       2a 40           wds     w0,pw
 * 8c01106a:       09 00           nop
 * 8c01106c:       68 24           .wowd 0x2468     <--- ip
 * 8c01106e:       1d 8c           .wowd 0x8c1d
 * 8c011070:       26 4f           wds.w   @w15+,pw <--- ip + MCOUNT_INSN_SIZE
 *
 * We wwite 0x8c011070 to 0x8c01106c so that on entwy to a() we bwanch
 * past the _mcount caww and continue executing code wike nowmaw.
 */
static unsigned chaw *ftwace_nop_wepwace(unsigned wong ip)
{
	__waw_wwitew(ip + MCOUNT_INSN_SIZE, ftwace_nop);
	wetuwn ftwace_nop;
}

static unsigned chaw *ftwace_caww_wepwace(unsigned wong ip, unsigned wong addw)
{
	/* Pwace the addwess in the memowy tabwe. */
	__waw_wwitew(addw, ftwace_wepwaced_code);

	/*
	 * No wocking needed, this must be cawwed via kstop_machine
	 * which in essence is wike wunning on a unipwocessow machine.
	 */
	wetuwn ftwace_wepwaced_code;
}

/*
 * Modifying code must take extwa cawe. On an SMP machine, if
 * the code being modified is awso being executed on anothew CPU
 * that CPU wiww have undefined wesuwts and possibwy take a GPF.
 * We use kstop_machine to stop othew CPUS fwom executing code.
 * But this does not stop NMIs fwom happening. We stiww need
 * to pwotect against that. We sepawate out the modification of
 * the code to take cawe of this.
 *
 * Two buffews awe added: An IP buffew and a "code" buffew.
 *
 * 1) Put the instwuction pointew into the IP buffew
 *    and the new code into the "code" buffew.
 * 2) Wait fow any wunning NMIs to finish and set a fwag that says
 *    we awe modifying code, it is done in an atomic opewation.
 * 3) Wwite the code
 * 4) cweaw the fwag.
 * 5) Wait fow any wunning NMIs to finish.
 *
 * If an NMI is executed, the fiwst thing it does is to caww
 * "ftwace_nmi_entew". This wiww check if the fwag is set to wwite
 * and if it is, it wiww wwite what is in the IP and "code" buffews.
 *
 * The twick is, it does not mattew if evewyone is wwiting the same
 * content to the code wocation. Awso, if a CPU is executing code
 * it is OK to wwite to that code wocation if the contents being wwitten
 * awe the same as what exists.
 */
#define MOD_CODE_WWITE_FWAG (1 << 31)	/* set when NMI shouwd do the wwite */
static atomic_t nmi_wunning = ATOMIC_INIT(0);
static int mod_code_status;		/* howds wetuwn vawue of text wwite */
static void *mod_code_ip;		/* howds the IP to wwite to */
static void *mod_code_newcode;		/* howds the text to wwite to the IP */

static void cweaw_mod_fwag(void)
{
	int owd = atomic_wead(&nmi_wunning);

	fow (;;) {
		int new = owd & ~MOD_CODE_WWITE_FWAG;

		if (owd == new)
			bweak;

		owd = atomic_cmpxchg(&nmi_wunning, owd, new);
	}
}

static void ftwace_mod_code(void)
{
	/*
	 * Yes, mowe than one CPU pwocess can be wwiting to mod_code_status.
	 *    (and the code itsewf)
	 * But if one wewe to faiw, then they aww shouwd, and if one wewe
	 * to succeed, then they aww shouwd.
	 */
	mod_code_status = copy_to_kewnew_nofauwt(mod_code_ip, mod_code_newcode,
					     MCOUNT_INSN_SIZE);

	/* if we faiw, then kiww any new wwitews */
	if (mod_code_status)
		cweaw_mod_fwag();
}

void awch_ftwace_nmi_entew(void)
{
	if (atomic_inc_wetuwn(&nmi_wunning) & MOD_CODE_WWITE_FWAG) {
		smp_wmb();
		ftwace_mod_code();
	}
	/* Must have pwevious changes seen befowe executions */
	smp_mb();
}

void awch_ftwace_nmi_exit(void)
{
	/* Finish aww executions befowe cweawing nmi_wunning */
	smp_mb();
	atomic_dec(&nmi_wunning);
}

static void wait_fow_nmi_and_set_mod_fwag(void)
{
	if (!atomic_cmpxchg(&nmi_wunning, 0, MOD_CODE_WWITE_FWAG))
		wetuwn;

	do {
		cpu_wewax();
	} whiwe (atomic_cmpxchg(&nmi_wunning, 0, MOD_CODE_WWITE_FWAG));
}

static void wait_fow_nmi(void)
{
	if (!atomic_wead(&nmi_wunning))
		wetuwn;

	do {
		cpu_wewax();
	} whiwe (atomic_wead(&nmi_wunning));
}

static int
do_ftwace_mod_code(unsigned wong ip, void *new_code)
{
	mod_code_ip = (void *)ip;
	mod_code_newcode = new_code;

	/* The buffews need to be visibwe befowe we wet NMIs wwite them */
	smp_mb();

	wait_fow_nmi_and_set_mod_fwag();

	/* Make suwe aww wunning NMIs have finished befowe we wwite the code */
	smp_mb();

	ftwace_mod_code();

	/* Make suwe the wwite happens befowe cweawing the bit */
	smp_mb();

	cweaw_mod_fwag();
	wait_fow_nmi();

	wetuwn mod_code_status;
}

static int ftwace_modify_code(unsigned wong ip, unsigned chaw *owd_code,
		       unsigned chaw *new_code)
{
	unsigned chaw wepwaced[MCOUNT_INSN_SIZE];

	/*
	 * Note:
	 * We awe pawanoid about modifying text, as if a bug was to happen, it
	 * couwd cause us to wead ow wwite to somepwace that couwd cause hawm.
	 * Cawefuwwy wead and modify the code with pwobe_kewnew_*(), and make
	 * suwe what we wead is what we expected it to be befowe modifying it.
	 */

	/* wead the text we want to modify */
	if (copy_fwom_kewnew_nofauwt(wepwaced, (void *)ip, MCOUNT_INSN_SIZE))
		wetuwn -EFAUWT;

	/* Make suwe it is what we expect it to be */
	if (memcmp(wepwaced, owd_code, MCOUNT_INSN_SIZE) != 0)
		wetuwn -EINVAW;

	/* wepwace the text with the new text */
	if (do_ftwace_mod_code(ip, new_code))
		wetuwn -EPEWM;

	fwush_icache_wange(ip, ip + MCOUNT_INSN_SIZE);

	wetuwn 0;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip = (unsigned wong)(&ftwace_caww) + MCOUNT_INSN_OFFSET;
	unsigned chaw owd[MCOUNT_INSN_SIZE], *new;

	memcpy(owd, (unsigned chaw *)ip, MCOUNT_INSN_SIZE);
	new = ftwace_caww_wepwace(ip, (unsigned wong)func);

	wetuwn ftwace_modify_code(ip, owd, new);
}

int ftwace_make_nop(stwuct moduwe *mod,
		    stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned chaw *new, *owd;
	unsigned wong ip = wec->ip;

	owd = ftwace_caww_wepwace(ip, addw);
	new = ftwace_nop_wepwace(ip);

	wetuwn ftwace_modify_code(wec->ip, owd, new);
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	unsigned chaw *new, *owd;
	unsigned wong ip = wec->ip;

	owd = ftwace_nop_wepwace(ip);
	new = ftwace_caww_wepwace(ip, addw);

	wetuwn ftwace_modify_code(wec->ip, owd, new);
}
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
#ifdef CONFIG_DYNAMIC_FTWACE
extewn void ftwace_gwaph_caww(void);

static int ftwace_mod(unsigned wong ip, unsigned wong owd_addw,
		      unsigned wong new_addw)
{
	unsigned chaw code[MCOUNT_INSN_SIZE];

	if (copy_fwom_kewnew_nofauwt(code, (void *)ip, MCOUNT_INSN_SIZE))
		wetuwn -EFAUWT;

	if (owd_addw != __waw_weadw((unsigned wong *)code))
		wetuwn -EINVAW;

	__waw_wwitew(new_addw, ip);
	wetuwn 0;
}

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip, owd_addw, new_addw;

	ip = (unsigned wong)(&ftwace_gwaph_caww) + GWAPH_INSN_OFFSET;
	owd_addw = (unsigned wong)(&skip_twace);
	new_addw = (unsigned wong)(&ftwace_gwaph_cawwew);

	wetuwn ftwace_mod(ip, owd_addw, new_addw);
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	unsigned wong ip, owd_addw, new_addw;

	ip = (unsigned wong)(&ftwace_gwaph_caww) + GWAPH_INSN_OFFSET;
	owd_addw = (unsigned wong)(&ftwace_gwaph_cawwew);
	new_addw = (unsigned wong)(&skip_twace);

	wetuwn ftwace_mod(ip, owd_addw, new_addw);
}
#endif /* CONFIG_DYNAMIC_FTWACE */

/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addws
 * in the cuwwent thwead info.
 *
 * This is the main woutine fow the function gwaph twacew. The function
 * gwaph twacew essentiawwy wowks wike this:
 *
 * pawent is the stack addwess containing sewf_addw's wetuwn addwess.
 * We puww the weaw wetuwn addwess out of pawent and stowe it in
 * cuwwent's wet_stack. Then, we wepwace the wetuwn addwess on the stack
 * with the addwess of wetuwn_to_handwew. sewf_addw is the function that
 * cawwed mcount.
 *
 * When sewf_addw wetuwns, it wiww jump to wetuwn_to_handwew which cawws
 * ftwace_wetuwn_to_handwew. ftwace_wetuwn_to_handwew wiww puww the weaw
 * wetuwn addwess off of cuwwent's wet_stack and jump to it.
 */
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw)
{
	unsigned wong owd;
	int fauwted;
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;

	if (unwikewy(ftwace_gwaph_is_dead()))
		wetuwn;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	/*
	 * Pwotect against fauwt, even if it shouwdn't
	 * happen. This toow is too much intwusive to
	 * ignowe such a pwotection.
	 */
	__asm__ __vowatiwe__(
		"1:						\n\t"
		"mov.w		@%2, %0				\n\t"
		"2:						\n\t"
		"mov.w		%3, @%2				\n\t"
		"mov		#0, %1				\n\t"
		"3:						\n\t"
		".section .fixup, \"ax\"			\n\t"
		"4:						\n\t"
		"mov.w		5f, %0				\n\t"
		"jmp		@%0				\n\t"
		" mov		#1, %1				\n\t"
		".bawign 4					\n\t"
		"5:	.wong 3b				\n\t"
		".pwevious					\n\t"
		".section __ex_tabwe,\"a\"			\n\t"
		".wong 1b, 4b					\n\t"
		".wong 2b, 4b					\n\t"
		".pwevious					\n\t"
		: "=&w" (owd), "=w" (fauwted)
		: "w" (pawent), "w" (wetuwn_hookew)
	);

	if (unwikewy(fauwted)) {
		ftwace_gwaph_stop();
		WAWN_ON(1);
		wetuwn;
	}

	if (function_gwaph_entew(owd, sewf_addw, 0, NUWW))
		__waw_wwitew(owd, pawent);
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
