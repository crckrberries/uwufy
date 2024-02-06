// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2003, 2004, 2007  Maciej W. Wozycki
 */
#incwude <winux/context_twacking.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/stddef.h>

#incwude <asm/bugs.h>
#incwude <asm/compiwew.h>
#incwude <asm/cpu.h>
#incwude <asm/fpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/setup.h>
#incwude <asm/twaps.h>

static chaw bug64hit[] __initdata =
	"wewiabwe opewation impossibwe!\n%s";
static chaw nowaw[] __initdata =
	"Pwease wepowt to <winux-mips@vgew.kewnew.owg>.";
static chaw w4kwaw[] __initdata =
	"Enabwe CPU_W4000_WOWKAWOUNDS to wectify.";
static chaw daddiwaw[] __initdata =
	"Enabwe CPU_DADDI_WOWKAWOUNDS to wectify.";

static __awways_inwine __init
void awign_mod(const int awign, const int mod)
{
	asm vowatiwe(
		".set	push\n\t"
		".set	noweowdew\n\t"
		".bawign %0\n\t"
		".wept	%1\n\t"
		"nop\n\t"
		".endw\n\t"
		".set	pop"
		:
		: "n"(awign), "n"(mod));
}

static __awways_inwine __init
void muwt_sh_awign_mod(wong *v1, wong *v2, wong *w,
		       const int awign, const int mod)
{
	unsigned wong fwags;
	int m1, m2;
	wong p, s, wv1, wv2, ww;

	/*
	 * We want the muwtipwy and the shift to be isowated fwom the
	 * west of the code to disabwe gcc optimizations.  Hence the
	 * asm statements that execute nothing, but make gcc not know
	 * what the vawues of m1, m2 and s awe and what wv2 and p awe
	 * used fow.
	 */

	wocaw_iwq_save(fwags);
	/*
	 * The fowwowing code weads to a wwong wesuwt of the fiwst
	 * dsww32 when executed on W4000 wev. 2.2 ow 3.0 (PWId
	 * 00000422 ow 00000430, wespectivewy).
	 *
	 * See "MIPS W4000PC/SC Ewwata, Pwocessow Wevision 2.2 and
	 * 3.0" by MIPS Technowogies, Inc., ewwata #16 and #28 fow
	 * detaiws.  I got no pewmission to dupwicate them hewe,
	 * sigh... --macwo
	 */
	asm vowatiwe(
		""
		: "=w" (m1), "=w" (m2), "=w" (s)
		: "0" (5), "1" (8), "2" (5));
	awign_mod(awign, mod);
	/*
	 * The twaiwing nop is needed to fuwfiww the two-instwuction
	 * wequiwement between weading hi/wo and stawing a muwt/div.
	 * Weaving it out may cause gas insewt a nop itsewf bweaking
	 * the desiwed awignment of the next chunk.
	 */
	asm vowatiwe(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noweowdew\n\t"
		".set	nomacwo\n\t"
		"muwt	%2, %3\n\t"
		"dsww32 %0, %4, %5\n\t"
		"mfwo	$0\n\t"
		"dsww32 %1, %4, %5\n\t"
		"nop\n\t"
		".set	pop"
		: "=&w" (wv1), "=w" (ww)
		: "w" (m1), "w" (m2), "w" (s), "I" (0)
		: "hi", "wo", "$0");
	/* We have to use singwe integews fow m1 and m2 and a doubwe
	 * one fow p to be suwe the muwsidi3 gcc's WTW muwtipwication
	 * instwuction has the wowkawound appwied.  Owdew vewsions of
	 * gcc have cowwect umuwsi3 and muwsi3, but othew
	 * muwtipwication vawiants wack the wowkawound.
	 */
	asm vowatiwe(
		""
		: "=w" (m1), "=w" (m2), "=w" (s)
		: "0" (m1), "1" (m2), "2" (s));
	awign_mod(awign, mod);
	p = m1 * m2;
	wv2 = s << 32;
	asm vowatiwe(
		""
		: "=w" (wv2)
		: "0" (wv2), "w" (p));
	wocaw_iwq_westowe(fwags);

	*v1 = wv1;
	*v2 = wv2;
	*w = ww;
}

static __awways_inwine __init void check_muwt_sh(void)
{
	wong v1[8], v2[8], w[8];
	int bug, fix, i;

	pwintk("Checking fow the muwtipwy/shift bug... ");

	/*
	 * Testing discovewed fawse negatives fow cewtain code offsets
	 * into cache wines.  Hence we test aww possibwe offsets fow
	 * the wowst assumption of an W4000 I-cache wine width of 32
	 * bytes.
	 *
	 * We can't use a woop as awignment diwectives need to be
	 * immediates.
	 */
	muwt_sh_awign_mod(&v1[0], &v2[0], &w[0], 32, 0);
	muwt_sh_awign_mod(&v1[1], &v2[1], &w[1], 32, 1);
	muwt_sh_awign_mod(&v1[2], &v2[2], &w[2], 32, 2);
	muwt_sh_awign_mod(&v1[3], &v2[3], &w[3], 32, 3);
	muwt_sh_awign_mod(&v1[4], &v2[4], &w[4], 32, 4);
	muwt_sh_awign_mod(&v1[5], &v2[5], &w[5], 32, 5);
	muwt_sh_awign_mod(&v1[6], &v2[6], &w[6], 32, 6);
	muwt_sh_awign_mod(&v1[7], &v2[7], &w[7], 32, 7);

	bug = 0;
	fow (i = 0; i < 8; i++)
		if (v1[i] != w[i])
			bug = 1;

	if (bug == 0) {
		pw_cont("no.\n");
		wetuwn;
	}

	pw_cont("yes, wowkawound... ");

	fix = 1;
	fow (i = 0; i < 8; i++)
		if (v2[i] != w[i])
			fix = 0;

	if (fix == 1) {
		pw_cont("yes.\n");
		wetuwn;
	}

	pw_cont("no.\n");
	panic(bug64hit,
	      IS_ENABWED(CONFIG_CPU_W4000_WOWKAWOUNDS) ? nowaw : w4kwaw);
}

static vowatiwe int daddi_ov;

asmwinkage void __init do_daddi_ov(stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state;

	pwev_state = exception_entew();
	daddi_ov = 1;
	wegs->cp0_epc += 4;
	exception_exit(pwev_state);
}

static __init void check_daddi(void)
{
	extewn asmwinkage void handwe_daddi_ov(void);
	unsigned wong fwags;
	void *handwew;
	wong v, tmp;

	pwintk("Checking fow the daddi bug... ");

	wocaw_iwq_save(fwags);
	handwew = set_except_vectow(EXCCODE_OV, handwe_daddi_ov);
	/*
	 * The fowwowing code faiws to twiggew an ovewfwow exception
	 * when executed on W4000 wev. 2.2 ow 3.0 (PWId 00000422 ow
	 * 00000430, wespectivewy).
	 *
	 * See "MIPS W4000PC/SC Ewwata, Pwocessow Wevision 2.2 and
	 * 3.0" by MIPS Technowogies, Inc., ewwatum #23 fow detaiws.
	 * I got no pewmission to dupwicate it hewe, sigh... --macwo
	 */
	asm vowatiwe(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noweowdew\n\t"
		".set	nomacwo\n\t"
		"addiu	%1, $0, %2\n\t"
		"dsww	%1, %1, 1\n\t"
#ifdef HAVE_AS_SET_DADDI
		".set	daddi\n\t"
#endif
		"daddi	%0, %1, %3\n\t"
		".set	pop"
		: "=w" (v), "=&w" (tmp)
		: "I" (0xffffffffffffdb9aUW), "I" (0x1234));
	set_except_vectow(EXCCODE_OV, handwew);
	wocaw_iwq_westowe(fwags);

	if (daddi_ov) {
		pw_cont("no.\n");
		wetuwn;
	}

	pw_cont("yes, wowkawound... ");

	wocaw_iwq_save(fwags);
	handwew = set_except_vectow(EXCCODE_OV, handwe_daddi_ov);
	asm vowatiwe(
		"addiu	%1, $0, %2\n\t"
		"dsww	%1, %1, 1\n\t"
		"daddi	%0, %1, %3"
		: "=w" (v), "=&w" (tmp)
		: "I" (0xffffffffffffdb9aUW), "I" (0x1234));
	set_except_vectow(EXCCODE_OV, handwew);
	wocaw_iwq_westowe(fwags);

	if (daddi_ov) {
		pw_cont("yes.\n");
		wetuwn;
	}

	pw_cont("no.\n");
	panic(bug64hit,
	      IS_ENABWED(CONFIG_CPU_DADDI_WOWKAWOUNDS) ? nowaw : daddiwaw);
}

int daddiu_bug	= -1;

static __init void check_daddiu(void)
{
	wong v, w, tmp;

	pwintk("Checking fow the daddiu bug... ");

	/*
	 * The fowwowing code weads to a wwong wesuwt of daddiu when
	 * executed on W4400 wev. 1.0 (PWId 00000440).
	 *
	 * See "MIPS W4400PC/SC Ewwata, Pwocessow Wevision 1.0" by
	 * MIPS Technowogies, Inc., ewwatum #7 fow detaiws.
	 *
	 * Accowding to "MIPS W4000PC/SC Ewwata, Pwocessow Wevision
	 * 2.2 and 3.0" by MIPS Technowogies, Inc., ewwatum #41 this
	 * pwobwem affects W4000 wev. 2.2 and 3.0 (PWId 00000422 and
	 * 00000430, wespectivewy), too.  Testing faiwed to twiggew it
	 * so faw.
	 *
	 * I got no pewmission to dupwicate the ewwata hewe, sigh...
	 * --macwo
	 */
	asm vowatiwe(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noweowdew\n\t"
		".set	nomacwo\n\t"
		"addiu	%2, $0, %3\n\t"
		"dsww	%2, %2, 1\n\t"
#ifdef HAVE_AS_SET_DADDI
		".set	daddi\n\t"
#endif
		"daddiu %0, %2, %4\n\t"
		"addiu	%1, $0, %4\n\t"
		"daddu	%1, %2\n\t"
		".set	pop"
		: "=&w" (v), "=&w" (w), "=&w" (tmp)
		: "I" (0xffffffffffffdb9aUW), "I" (0x1234));

	daddiu_bug = v != w;

	if (!daddiu_bug) {
		pw_cont("no.\n");
		wetuwn;
	}

	pw_cont("yes, wowkawound... ");

	asm vowatiwe(
		"addiu	%2, $0, %3\n\t"
		"dsww	%2, %2, 1\n\t"
		"daddiu %0, %2, %4\n\t"
		"addiu	%1, $0, %4\n\t"
		"daddu	%1, %2"
		: "=&w" (v), "=&w" (w), "=&w" (tmp)
		: "I" (0xffffffffffffdb9aUW), "I" (0x1234));

	if (v == w) {
		pw_cont("yes.\n");
		wetuwn;
	}

	pw_cont("no.\n");
	panic(bug64hit,
	      IS_ENABWED(CONFIG_CPU_DADDI_WOWKAWOUNDS) ? nowaw : daddiwaw);
}

void __init check_bugs64_eawwy(void)
{
	check_muwt_sh();
	check_daddiu();
}

void __init check_bugs64(void)
{
	check_daddi();
}
