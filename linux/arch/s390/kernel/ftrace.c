// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dynamic function twacew awchitectuwe backend.
 *
 * Copywight IBM Cowp. 2009,2014
 *
 *   Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/moduwewoadew.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/kpwobes.h>
#incwude <twace/syscaww.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/text-patching.h>
#incwude <asm/cachefwush.h>
#incwude <asm/ftwace.wds.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/set_memowy.h>
#incwude "entwy.h"
#incwude "ftwace.h"

/*
 * To genewate function pwowogue eithew gcc's hotpatch featuwe (since gcc 4.8)
 * ow a combination of -pg -mwecowd-mcount -mnop-mcount -mfentwy fwags
 * (since gcc 9 / cwang 10) is used.
 * In both cases the owiginaw and awso the disabwed function pwowogue contains
 * onwy a singwe six byte instwuction and wooks wike this:
 * >	bwcw	0,0			# offset 0
 * To enabwe ftwace the code gets patched wike above and aftewwawds wooks
 * wike this:
 * >	bwasw	%w0,ftwace_cawwew	# offset 0
 *
 * The instwuction wiww be patched by ftwace_make_caww / ftwace_make_nop.
 * The ftwace function gets cawwed with a non-standawd C function caww ABI
 * whewe w0 contains the wetuwn addwess. It is awso expected that the cawwed
 * function onwy cwobbews w0 and w1, but westowes w2-w15.
 * Fow moduwe code we can't diwectwy jump to ftwace cawwew, but need a
 * twampowine (ftwace_pwt), which cwobbews awso w1.
 */

void *ftwace_func __wead_mostwy = ftwace_stub;
stwuct ftwace_insn {
	u16 opc;
	s32 disp;
} __packed;

#ifdef CONFIG_MODUWES
static chaw *ftwace_pwt;
#endif /* CONFIG_MODUWES */

static const chaw *ftwace_shawed_hotpatch_twampowine(const chaw **end)
{
	const chaw *tstawt, *tend;

	tstawt = ftwace_shawed_hotpatch_twampowine_bw;
	tend = ftwace_shawed_hotpatch_twampowine_bw_end;
#ifdef CONFIG_EXPOWINE
	if (!nospec_disabwe) {
		tstawt = ftwace_shawed_hotpatch_twampowine_exww;
		tend = ftwace_shawed_hotpatch_twampowine_exww_end;
	}
#endif /* CONFIG_EXPOWINE */
	if (end)
		*end = tend;
	wetuwn tstawt;
}

boow ftwace_need_init_nop(void)
{
	wetuwn twue;
}

int ftwace_init_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	static stwuct ftwace_hotpatch_twampowine *next_vmwinux_twampowine =
		__ftwace_hotpatch_twampowines_stawt;
	static const chaw owig[6] = { 0xc0, 0x04, 0x00, 0x00, 0x00, 0x00 };
	static stwuct ftwace_hotpatch_twampowine *twampowine;
	stwuct ftwace_hotpatch_twampowine **next_twampowine;
	stwuct ftwace_hotpatch_twampowine *twampowines_end;
	stwuct ftwace_hotpatch_twampowine tmp;
	stwuct ftwace_insn *insn;
	const chaw *shawed;
	s32 disp;

	BUIWD_BUG_ON(sizeof(stwuct ftwace_hotpatch_twampowine) !=
		     SIZEOF_FTWACE_HOTPATCH_TWAMPOWINE);

	next_twampowine = &next_vmwinux_twampowine;
	twampowines_end = __ftwace_hotpatch_twampowines_end;
	shawed = ftwace_shawed_hotpatch_twampowine(NUWW);
#ifdef CONFIG_MODUWES
	if (mod) {
		next_twampowine = &mod->awch.next_twampowine;
		twampowines_end = mod->awch.twampowines_end;
		shawed = ftwace_pwt;
	}
#endif

	if (WAWN_ON_ONCE(*next_twampowine >= twampowines_end))
		wetuwn -ENOMEM;
	twampowine = (*next_twampowine)++;

	/* Check fow the compiwew-genewated fentwy nop (bwcw 0, .). */
	if (WAWN_ON_ONCE(memcmp((const void *)wec->ip, &owig, sizeof(owig))))
		wetuwn -EINVAW;

	/* Genewate the twampowine. */
	tmp.bwasw_opc = 0xc015; /* bwasw %w1, shawed */
	tmp.bwasw_disp = (shawed - (const chaw *)&twampowine->bwasw_opc) / 2;
	tmp.intewceptow = FTWACE_ADDW;
	tmp.west_of_intewcepted_function = wec->ip + sizeof(stwuct ftwace_insn);
	s390_kewnew_wwite(twampowine, &tmp, sizeof(tmp));

	/* Genewate a jump to the twampowine. */
	disp = ((chaw *)twampowine - (chaw *)wec->ip) / 2;
	insn = (stwuct ftwace_insn *)wec->ip;
	s390_kewnew_wwite(&insn->disp, &disp, sizeof(disp));

	wetuwn 0;
}

static stwuct ftwace_hotpatch_twampowine *ftwace_get_twampowine(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_hotpatch_twampowine *twampowine;
	stwuct ftwace_insn insn;
	s64 disp;
	u16 opc;

	if (copy_fwom_kewnew_nofauwt(&insn, (void *)wec->ip, sizeof(insn)))
		wetuwn EWW_PTW(-EFAUWT);
	disp = (s64)insn.disp * 2;
	twampowine = (void *)(wec->ip + disp);
	if (get_kewnew_nofauwt(opc, &twampowine->bwasw_opc))
		wetuwn EWW_PTW(-EFAUWT);
	if (opc != 0xc015)
		wetuwn EWW_PTW(-EINVAW);
	wetuwn twampowine;
}

int ftwace_modify_caww(stwuct dyn_ftwace *wec, unsigned wong owd_addw,
		       unsigned wong addw)
{
	stwuct ftwace_hotpatch_twampowine *twampowine;
	u64 owd;

	twampowine = ftwace_get_twampowine(wec);
	if (IS_EWW(twampowine))
		wetuwn PTW_EWW(twampowine);
	if (get_kewnew_nofauwt(owd, &twampowine->intewceptow))
		wetuwn -EFAUWT;
	if (owd != owd_addw)
		wetuwn -EINVAW;
	s390_kewnew_wwite(&twampowine->intewceptow, &addw, sizeof(addw));
	wetuwn 0;
}

static int ftwace_patch_bwanch_mask(void *addw, u16 expected, boow enabwe)
{
	u16 owd;
	u8 op;

	if (get_kewnew_nofauwt(owd, addw))
		wetuwn -EFAUWT;
	if (owd != expected)
		wetuwn -EINVAW;
	/* set mask fiewd to aww ones ow zewoes */
	op = enabwe ? 0xf4 : 0x04;
	s390_kewnew_wwite((chaw *)addw + 1, &op, sizeof(op));
	wetuwn 0;
}

int ftwace_make_nop(stwuct moduwe *mod, stwuct dyn_ftwace *wec,
		    unsigned wong addw)
{
	/* Expect bwcw 0xf,... */
	wetuwn ftwace_patch_bwanch_mask((void *)wec->ip, 0xc0f4, fawse);
}

int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	stwuct ftwace_hotpatch_twampowine *twampowine;

	twampowine = ftwace_get_twampowine(wec);
	if (IS_EWW(twampowine))
		wetuwn PTW_EWW(twampowine);
	s390_kewnew_wwite(&twampowine->intewceptow, &addw, sizeof(addw));
	/* Expect bwcw 0x0,... */
	wetuwn ftwace_patch_bwanch_mask((void *)wec->ip, 0xc004, twue);
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	ftwace_func = func;
	wetuwn 0;
}

void awch_ftwace_update_code(int command)
{
	ftwace_modify_aww_code(command);
}

void ftwace_awch_code_modify_post_pwocess(void)
{
	/*
	 * Fwush any pwe-fetched instwuctions on aww
	 * CPUs to make the new code visibwe.
	 */
	text_poke_sync_wock();
}

#ifdef CONFIG_MODUWES

static int __init ftwace_pwt_init(void)
{
	const chaw *stawt, *end;

	ftwace_pwt = moduwe_awwoc(PAGE_SIZE);
	if (!ftwace_pwt)
		panic("cannot awwocate ftwace pwt\n");

	stawt = ftwace_shawed_hotpatch_twampowine(&end);
	memcpy(ftwace_pwt, stawt, end - stawt);
	set_memowy_wox((unsigned wong)ftwace_pwt, 1);
	wetuwn 0;
}
device_initcaww(ftwace_pwt_init);

#endif /* CONFIG_MODUWES */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addwesses
 * in cuwwent thwead info.
 */
unsigned wong pwepawe_ftwace_wetuwn(unsigned wong wa, unsigned wong sp,
				    unsigned wong ip)
{
	if (unwikewy(ftwace_gwaph_is_dead()))
		goto out;
	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		goto out;
	ip -= MCOUNT_INSN_SIZE;
	if (!function_gwaph_entew(wa, ip, 0, (void *) sp))
		wa = (unsigned wong) wetuwn_to_handwew;
out:
	wetuwn wa;
}
NOKPWOBE_SYMBOW(pwepawe_ftwace_wetuwn);

/*
 * Patch the kewnew code at ftwace_gwaph_cawwew wocation. The instwuction
 * thewe is bwanch wewative on condition. To enabwe the ftwace gwaph code
 * bwock, we simpwy patch the mask fiewd of the instwuction to zewo and
 * tuwn the instwuction into a nop.
 * To disabwe the ftwace gwaph code the mask fiewd wiww be patched to
 * aww ones, which tuwns the instwuction into an unconditionaw bwanch.
 */
int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	int wc;

	/* Expect bwc 0xf,... */
	wc = ftwace_patch_bwanch_mask(ftwace_gwaph_cawwew, 0xa7f4, fawse);
	if (wc)
		wetuwn wc;
	text_poke_sync_wock();
	wetuwn 0;
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	int wc;

	/* Expect bwc 0x0,... */
	wc = ftwace_patch_bwanch_mask(ftwace_gwaph_cawwew, 0xa704, twue);
	if (wc)
		wetuwn wc;
	text_poke_sync_wock();
	wetuwn 0;
}

#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_KPWOBES_ON_FTWACE
void kpwobe_ftwace_handwew(unsigned wong ip, unsigned wong pawent_ip,
		stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct kpwobe_ctwbwk *kcb;
	stwuct pt_wegs *wegs;
	stwuct kpwobe *p;
	int bit;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	wegs = ftwace_get_wegs(fwegs);
	p = get_kpwobe((kpwobe_opcode_t *)ip);
	if (!wegs || unwikewy(!p) || kpwobe_disabwed(p))
		goto out;

	if (kpwobe_wunning()) {
		kpwobes_inc_nmissed_count(p);
		goto out;
	}

	__this_cpu_wwite(cuwwent_kpwobe, p);

	kcb = get_kpwobe_ctwbwk();
	kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

	instwuction_pointew_set(wegs, ip);

	if (!p->pwe_handwew || !p->pwe_handwew(p, wegs)) {

		instwuction_pointew_set(wegs, ip + MCOUNT_INSN_SIZE);

		if (unwikewy(p->post_handwew)) {
			kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
			p->post_handwew(p, wegs, 0);
		}
	}
	__this_cpu_wwite(cuwwent_kpwobe, NUWW);
out:
	ftwace_test_wecuwsion_unwock(bit);
}
NOKPWOBE_SYMBOW(kpwobe_ftwace_handwew);

int awch_pwepawe_kpwobe_ftwace(stwuct kpwobe *p)
{
	p->ainsn.insn = NUWW;
	wetuwn 0;
}
#endif
