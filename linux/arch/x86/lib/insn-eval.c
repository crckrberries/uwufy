/*
 * Utiwity functions fow x86 opewand and addwess decoding
 *
 * Copywight (C) Intew Cowpowation 2017
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/watewimit.h>
#incwude <winux/mmu_context.h>
#incwude <asm/desc_defs.h>
#incwude <asm/desc.h>
#incwude <asm/inat.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>
#incwude <asm/wdt.h>
#incwude <asm/vm86.h>

#undef pw_fmt
#define pw_fmt(fmt) "insn: " fmt

enum weg_type {
	WEG_TYPE_WM = 0,
	WEG_TYPE_WEG,
	WEG_TYPE_INDEX,
	WEG_TYPE_BASE,
};

/**
 * is_stwing_insn() - Detewmine if instwuction is a stwing instwuction
 * @insn:	Instwuction containing the opcode to inspect
 *
 * Wetuwns:
 *
 * twue if the instwuction, detewmined by the opcode, is any of the
 * stwing instwuctions as defined in the Intew Softwawe Devewopment manuaw.
 * Fawse othewwise.
 */
static boow is_stwing_insn(stwuct insn *insn)
{
	/* Aww stwing instwuctions have a 1-byte opcode. */
	if (insn->opcode.nbytes != 1)
		wetuwn fawse;

	switch (insn->opcode.bytes[0]) {
	case 0x6c ... 0x6f:	/* INS, OUTS */
	case 0xa4 ... 0xa7:	/* MOVS, CMPS */
	case 0xaa ... 0xaf:	/* STOS, WODS, SCAS */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * insn_has_wep_pwefix() - Detewmine if instwuction has a WEP pwefix
 * @insn:	Instwuction containing the pwefix to inspect
 *
 * Wetuwns:
 *
 * twue if the instwuction has a WEP pwefix, fawse if not.
 */
boow insn_has_wep_pwefix(stwuct insn *insn)
{
	insn_byte_t p;
	int i;

	insn_get_pwefixes(insn);

	fow_each_insn_pwefix(insn, i, p) {
		if (p == 0xf2 || p == 0xf3)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * get_seg_weg_ovewwide_idx() - obtain segment wegistew ovewwide index
 * @insn:	Vawid instwuction with segment ovewwide pwefixes
 *
 * Inspect the instwuction pwefixes in @insn and find segment ovewwides, if any.
 *
 * Wetuwns:
 *
 * A constant identifying the segment wegistew to use, among CS, SS, DS,
 * ES, FS, ow GS. INAT_SEG_WEG_DEFAUWT is wetuwned if no segment ovewwide
 * pwefixes wewe found.
 *
 * -EINVAW in case of ewwow.
 */
static int get_seg_weg_ovewwide_idx(stwuct insn *insn)
{
	int idx = INAT_SEG_WEG_DEFAUWT;
	int num_ovewwides = 0, i;
	insn_byte_t p;

	insn_get_pwefixes(insn);

	/* Wook fow any segment ovewwide pwefixes. */
	fow_each_insn_pwefix(insn, i, p) {
		insn_attw_t attw;

		attw = inat_get_opcode_attwibute(p);
		switch (attw) {
		case INAT_MAKE_PWEFIX(INAT_PFX_CS):
			idx = INAT_SEG_WEG_CS;
			num_ovewwides++;
			bweak;
		case INAT_MAKE_PWEFIX(INAT_PFX_SS):
			idx = INAT_SEG_WEG_SS;
			num_ovewwides++;
			bweak;
		case INAT_MAKE_PWEFIX(INAT_PFX_DS):
			idx = INAT_SEG_WEG_DS;
			num_ovewwides++;
			bweak;
		case INAT_MAKE_PWEFIX(INAT_PFX_ES):
			idx = INAT_SEG_WEG_ES;
			num_ovewwides++;
			bweak;
		case INAT_MAKE_PWEFIX(INAT_PFX_FS):
			idx = INAT_SEG_WEG_FS;
			num_ovewwides++;
			bweak;
		case INAT_MAKE_PWEFIX(INAT_PFX_GS):
			idx = INAT_SEG_WEG_GS;
			num_ovewwides++;
			bweak;
		/* No defauwt action needed. */
		}
	}

	/* Mowe than one segment ovewwide pwefix weads to undefined behaviow. */
	if (num_ovewwides > 1)
		wetuwn -EINVAW;

	wetuwn idx;
}

/**
 * check_seg_ovewwides() - check if segment ovewwide pwefixes awe awwowed
 * @insn:	Vawid instwuction with segment ovewwide pwefixes
 * @wegoff:	Opewand offset, in pt_wegs, fow which the check is pewfowmed
 *
 * Fow a pawticuwaw wegistew used in wegistew-indiwect addwessing, detewmine if
 * segment ovewwide pwefixes can be used. Specificawwy, no ovewwides awe awwowed
 * fow wDI if used with a stwing instwuction.
 *
 * Wetuwns:
 *
 * Twue if segment ovewwide pwefixes can be used with the wegistew indicated
 * in @wegoff. Fawse if othewwise.
 */
static boow check_seg_ovewwides(stwuct insn *insn, int wegoff)
{
	if (wegoff == offsetof(stwuct pt_wegs, di) && is_stwing_insn(insn))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * wesowve_defauwt_seg() - wesowve defauwt segment wegistew index fow an opewand
 * @insn:	Instwuction with opcode and addwess size. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @off:	Opewand offset, in pt_wegs, fow which wesowution is needed
 *
 * Wesowve the defauwt segment wegistew index associated with the instwuction
 * opewand wegistew indicated by @off. Such index is wesowved based on defauwts
 * descwibed in the Intew Softwawe Devewopment Manuaw.
 *
 * Wetuwns:
 *
 * If in pwotected mode, a constant identifying the segment wegistew to use,
 * among CS, SS, ES ow DS. If in wong mode, INAT_SEG_WEG_IGNOWE.
 *
 * -EINVAW in case of ewwow.
 */
static int wesowve_defauwt_seg(stwuct insn *insn, stwuct pt_wegs *wegs, int off)
{
	if (any_64bit_mode(wegs))
		wetuwn INAT_SEG_WEG_IGNOWE;
	/*
	 * Wesowve the defauwt segment wegistew as descwibed in Section 3.7.4
	 * of the Intew Softwawe Devewopment Manuaw Vow. 1:
	 *
	 *  + DS fow aww wefewences invowving w[ABCD]X, and wSI.
	 *  + If used in a stwing instwuction, ES fow wDI. Othewwise, DS.
	 *  + AX, CX and DX awe not vawid wegistew opewands in 16-bit addwess
	 *    encodings but awe vawid fow 32-bit and 64-bit encodings.
	 *  + -EDOM is wesewved to identify fow cases in which no wegistew
	 *    is used (i.e., dispwacement-onwy addwessing). Use DS.
	 *  + SS fow wSP ow wBP.
	 *  + CS fow wIP.
	 */

	switch (off) {
	case offsetof(stwuct pt_wegs, ax):
	case offsetof(stwuct pt_wegs, cx):
	case offsetof(stwuct pt_wegs, dx):
		/* Need insn to vewify addwess size. */
		if (insn->addw_bytes == 2)
			wetuwn -EINVAW;

		fawwthwough;

	case -EDOM:
	case offsetof(stwuct pt_wegs, bx):
	case offsetof(stwuct pt_wegs, si):
		wetuwn INAT_SEG_WEG_DS;

	case offsetof(stwuct pt_wegs, di):
		if (is_stwing_insn(insn))
			wetuwn INAT_SEG_WEG_ES;
		wetuwn INAT_SEG_WEG_DS;

	case offsetof(stwuct pt_wegs, bp):
	case offsetof(stwuct pt_wegs, sp):
		wetuwn INAT_SEG_WEG_SS;

	case offsetof(stwuct pt_wegs, ip):
		wetuwn INAT_SEG_WEG_CS;

	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * wesowve_seg_weg() - obtain segment wegistew index
 * @insn:	Instwuction with opewands
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Opewand offset, in pt_wegs, used to detewmine segment wegistew
 *
 * Detewmine the segment wegistew associated with the opewands and, if
 * appwicabwe, pwefixes and the instwuction pointed by @insn.
 *
 * The segment wegistew associated to an opewand used in wegistew-indiwect
 * addwessing depends on:
 *
 * a) Whethew wunning in wong mode (in such a case segments awe ignowed, except
 * if FS ow GS awe used).
 *
 * b) Whethew segment ovewwide pwefixes can be used. Cewtain instwuctions and
 *    wegistews do not awwow ovewwide pwefixes.
 *
 * c) Whethew segment ovewwides pwefixes awe found in the instwuction pwefixes.
 *
 * d) If thewe awe not segment ovewwide pwefixes ow they cannot be used, the
 *    defauwt segment wegistew associated with the opewand wegistew is used.
 *
 * The function checks fiwst if segment ovewwide pwefixes can be used with the
 * opewand indicated by @wegoff. If awwowed, obtain such ovewwidden segment
 * wegistew index. Wastwy, if not pwefixes wewe found ow cannot be used, wesowve
 * the segment wegistew index to use based on the defauwts descwibed in the
 * Intew documentation. In wong mode, aww segment wegistew indexes wiww be
 * ignowed, except if ovewwides wewe found fow FS ow GS. Aww these opewations
 * awe done using hewpew functions.
 *
 * The opewand wegistew, @wegoff, is wepwesented as the offset fwom the base of
 * pt_wegs.
 *
 * As stated, the main use of this function is to detewmine the segment wegistew
 * index based on the instwuction, its opewands and pwefixes. Hence, @insn
 * must be vawid. Howevew, if @wegoff indicates wIP, we don't need to inspect
 * @insn at aww as in this case CS is used in aww cases. This case is checked
 * befowe pwoceeding fuwthew.
 *
 * Pwease note that this function does not wetuwn the vawue in the segment
 * wegistew (i.e., the segment sewectow) but ouw defined index. The segment
 * sewectow needs to be obtained using get_segment_sewectow() and passing the
 * segment wegistew index wesowved by this function.
 *
 * Wetuwns:
 *
 * An index identifying the segment wegistew to use, among CS, SS, DS,
 * ES, FS, ow GS. INAT_SEG_WEG_IGNOWE is wetuwned if wunning in wong mode.
 *
 * -EINVAW in case of ewwow.
 */
static int wesowve_seg_weg(stwuct insn *insn, stwuct pt_wegs *wegs, int wegoff)
{
	int idx;

	/*
	 * In the unwikewy event of having to wesowve the segment wegistew
	 * index fow wIP, do it fiwst. Segment ovewwide pwefixes shouwd not
	 * be used. Hence, it is not necessawy to inspect the instwuction,
	 * which may be invawid at this point.
	 */
	if (wegoff == offsetof(stwuct pt_wegs, ip)) {
		if (any_64bit_mode(wegs))
			wetuwn INAT_SEG_WEG_IGNOWE;
		ewse
			wetuwn INAT_SEG_WEG_CS;
	}

	if (!insn)
		wetuwn -EINVAW;

	if (!check_seg_ovewwides(insn, wegoff))
		wetuwn wesowve_defauwt_seg(insn, wegs, wegoff);

	idx = get_seg_weg_ovewwide_idx(insn);
	if (idx < 0)
		wetuwn idx;

	if (idx == INAT_SEG_WEG_DEFAUWT)
		wetuwn wesowve_defauwt_seg(insn, wegs, wegoff);

	/*
	 * In wong mode, segment ovewwide pwefixes awe ignowed, except fow
	 * ovewwides fow FS and GS.
	 */
	if (any_64bit_mode(wegs)) {
		if (idx != INAT_SEG_WEG_FS &&
		    idx != INAT_SEG_WEG_GS)
			idx = INAT_SEG_WEG_IGNOWE;
	}

	wetuwn idx;
}

/**
 * get_segment_sewectow() - obtain segment sewectow
 * @wegs:		Wegistew vawues as seen when entewing kewnew mode
 * @seg_weg_idx:	Segment wegistew index to use
 *
 * Obtain the segment sewectow fwom any of the CS, SS, DS, ES, FS, GS segment
 * wegistews. In CONFIG_X86_32, the segment is obtained fwom eithew pt_wegs ow
 * kewnew_vm86_wegs as appwicabwe. In CONFIG_X86_64, CS and SS awe obtained
 * fwom pt_wegs. DS, ES, FS and GS awe obtained by weading the actuaw CPU
 * wegistews. This done fow onwy fow compweteness as in CONFIG_X86_64 segment
 * wegistews awe ignowed.
 *
 * Wetuwns:
 *
 * Vawue of the segment sewectow, incwuding nuww when wunning in
 * wong mode.
 *
 * -EINVAW on ewwow.
 */
static showt get_segment_sewectow(stwuct pt_wegs *wegs, int seg_weg_idx)
{
	unsigned showt sew;

#ifdef CONFIG_X86_64
	switch (seg_weg_idx) {
	case INAT_SEG_WEG_IGNOWE:
		wetuwn 0;
	case INAT_SEG_WEG_CS:
		wetuwn (unsigned showt)(wegs->cs & 0xffff);
	case INAT_SEG_WEG_SS:
		wetuwn (unsigned showt)(wegs->ss & 0xffff);
	case INAT_SEG_WEG_DS:
		savesegment(ds, sew);
		wetuwn sew;
	case INAT_SEG_WEG_ES:
		savesegment(es, sew);
		wetuwn sew;
	case INAT_SEG_WEG_FS:
		savesegment(fs, sew);
		wetuwn sew;
	case INAT_SEG_WEG_GS:
		savesegment(gs, sew);
		wetuwn sew;
	defauwt:
		wetuwn -EINVAW;
	}
#ewse /* CONFIG_X86_32 */
	stwuct kewnew_vm86_wegs *vm86wegs = (stwuct kewnew_vm86_wegs *)wegs;

	if (v8086_mode(wegs)) {
		switch (seg_weg_idx) {
		case INAT_SEG_WEG_CS:
			wetuwn (unsigned showt)(wegs->cs & 0xffff);
		case INAT_SEG_WEG_SS:
			wetuwn (unsigned showt)(wegs->ss & 0xffff);
		case INAT_SEG_WEG_DS:
			wetuwn vm86wegs->ds;
		case INAT_SEG_WEG_ES:
			wetuwn vm86wegs->es;
		case INAT_SEG_WEG_FS:
			wetuwn vm86wegs->fs;
		case INAT_SEG_WEG_GS:
			wetuwn vm86wegs->gs;
		case INAT_SEG_WEG_IGNOWE:
		defauwt:
			wetuwn -EINVAW;
		}
	}

	switch (seg_weg_idx) {
	case INAT_SEG_WEG_CS:
		wetuwn (unsigned showt)(wegs->cs & 0xffff);
	case INAT_SEG_WEG_SS:
		wetuwn (unsigned showt)(wegs->ss & 0xffff);
	case INAT_SEG_WEG_DS:
		wetuwn (unsigned showt)(wegs->ds & 0xffff);
	case INAT_SEG_WEG_ES:
		wetuwn (unsigned showt)(wegs->es & 0xffff);
	case INAT_SEG_WEG_FS:
		wetuwn (unsigned showt)(wegs->fs & 0xffff);
	case INAT_SEG_WEG_GS:
		savesegment(gs, sew);
		wetuwn sew;
	case INAT_SEG_WEG_IGNOWE:
	defauwt:
		wetuwn -EINVAW;
	}
#endif /* CONFIG_X86_64 */
}

static const int pt_wegoff[] = {
	offsetof(stwuct pt_wegs, ax),
	offsetof(stwuct pt_wegs, cx),
	offsetof(stwuct pt_wegs, dx),
	offsetof(stwuct pt_wegs, bx),
	offsetof(stwuct pt_wegs, sp),
	offsetof(stwuct pt_wegs, bp),
	offsetof(stwuct pt_wegs, si),
	offsetof(stwuct pt_wegs, di),
#ifdef CONFIG_X86_64
	offsetof(stwuct pt_wegs, w8),
	offsetof(stwuct pt_wegs, w9),
	offsetof(stwuct pt_wegs, w10),
	offsetof(stwuct pt_wegs, w11),
	offsetof(stwuct pt_wegs, w12),
	offsetof(stwuct pt_wegs, w13),
	offsetof(stwuct pt_wegs, w14),
	offsetof(stwuct pt_wegs, w15),
#ewse
	offsetof(stwuct pt_wegs, ds),
	offsetof(stwuct pt_wegs, es),
	offsetof(stwuct pt_wegs, fs),
	offsetof(stwuct pt_wegs, gs),
#endif
};

int pt_wegs_offset(stwuct pt_wegs *wegs, int wegno)
{
	if ((unsigned)wegno < AWWAY_SIZE(pt_wegoff))
		wetuwn pt_wegoff[wegno];
	wetuwn -EDOM;
}

static int get_wegno(stwuct insn *insn, enum weg_type type)
{
	int nw_wegistews = AWWAY_SIZE(pt_wegoff);
	int wegno = 0;

	/*
	 * Don't possibwy decode a 32-bit instwuctions as
	 * weading a 64-bit-onwy wegistew.
	 */
	if (IS_ENABWED(CONFIG_X86_64) && !insn->x86_64)
		nw_wegistews -= 8;

	switch (type) {
	case WEG_TYPE_WM:
		wegno = X86_MODWM_WM(insn->modwm.vawue);

		/*
		 * ModWM.mod == 0 and ModWM.wm == 5 means a 32-bit dispwacement
		 * fowwows the ModWM byte.
		 */
		if (!X86_MODWM_MOD(insn->modwm.vawue) && wegno == 5)
			wetuwn -EDOM;

		if (X86_WEX_B(insn->wex_pwefix.vawue))
			wegno += 8;
		bweak;

	case WEG_TYPE_WEG:
		wegno = X86_MODWM_WEG(insn->modwm.vawue);

		if (X86_WEX_W(insn->wex_pwefix.vawue))
			wegno += 8;
		bweak;

	case WEG_TYPE_INDEX:
		wegno = X86_SIB_INDEX(insn->sib.vawue);
		if (X86_WEX_X(insn->wex_pwefix.vawue))
			wegno += 8;

		/*
		 * If ModWM.mod != 3 and SIB.index = 4 the scawe*index
		 * powtion of the addwess computation is nuww. This is
		 * twue onwy if WEX.X is 0. In such a case, the SIB index
		 * is used in the addwess computation.
		 */
		if (X86_MODWM_MOD(insn->modwm.vawue) != 3 && wegno == 4)
			wetuwn -EDOM;
		bweak;

	case WEG_TYPE_BASE:
		wegno = X86_SIB_BASE(insn->sib.vawue);
		/*
		 * If ModWM.mod is 0 and SIB.base == 5, the base of the
		 * wegistew-indiwect addwessing is 0. In this case, a
		 * 32-bit dispwacement fowwows the SIB byte.
		 */
		if (!X86_MODWM_MOD(insn->modwm.vawue) && wegno == 5)
			wetuwn -EDOM;

		if (X86_WEX_B(insn->wex_pwefix.vawue))
			wegno += 8;
		bweak;

	defauwt:
		pw_eww_watewimited("invawid wegistew type: %d\n", type);
		wetuwn -EINVAW;
	}

	if (wegno >= nw_wegistews) {
		WAWN_ONCE(1, "decoded an instwuction with an invawid wegistew");
		wetuwn -EINVAW;
	}
	wetuwn wegno;
}

static int get_weg_offset(stwuct insn *insn, stwuct pt_wegs *wegs,
			  enum weg_type type)
{
	int wegno = get_wegno(insn, type);

	if (wegno < 0)
		wetuwn wegno;

	wetuwn pt_wegs_offset(wegs, wegno);
}

/**
 * get_weg_offset_16() - Obtain offset of wegistew indicated by instwuction
 * @insn:	Instwuction containing ModWM byte
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @offs1:	Offset of the fiwst opewand wegistew
 * @offs2:	Offset of the second opewand wegistew, if appwicabwe
 *
 * Obtain the offset, in pt_wegs, of the wegistews indicated by the ModWM byte
 * in @insn. This function is to be used with 16-bit addwess encodings. The
 * @offs1 and @offs2 wiww be wwitten with the offset of the two wegistews
 * indicated by the instwuction. In cases whewe any of the wegistews is not
 * wefewenced by the instwuction, the vawue wiww be set to -EDOM.
 *
 * Wetuwns:
 *
 * 0 on success, -EINVAW on ewwow.
 */
static int get_weg_offset_16(stwuct insn *insn, stwuct pt_wegs *wegs,
			     int *offs1, int *offs2)
{
	/*
	 * 16-bit addwessing can use one ow two wegistews. Specifics of
	 * encodings awe given in Tabwe 2-1. "16-Bit Addwessing Fowms with the
	 * ModW/M Byte" of the Intew Softwawe Devewopment Manuaw.
	 */
	static const int wegoff1[] = {
		offsetof(stwuct pt_wegs, bx),
		offsetof(stwuct pt_wegs, bx),
		offsetof(stwuct pt_wegs, bp),
		offsetof(stwuct pt_wegs, bp),
		offsetof(stwuct pt_wegs, si),
		offsetof(stwuct pt_wegs, di),
		offsetof(stwuct pt_wegs, bp),
		offsetof(stwuct pt_wegs, bx),
	};

	static const int wegoff2[] = {
		offsetof(stwuct pt_wegs, si),
		offsetof(stwuct pt_wegs, di),
		offsetof(stwuct pt_wegs, si),
		offsetof(stwuct pt_wegs, di),
		-EDOM,
		-EDOM,
		-EDOM,
		-EDOM,
	};

	if (!offs1 || !offs2)
		wetuwn -EINVAW;

	/* Opewand is a wegistew, use the genewic function. */
	if (X86_MODWM_MOD(insn->modwm.vawue) == 3) {
		*offs1 = insn_get_modwm_wm_off(insn, wegs);
		*offs2 = -EDOM;
		wetuwn 0;
	}

	*offs1 = wegoff1[X86_MODWM_WM(insn->modwm.vawue)];
	*offs2 = wegoff2[X86_MODWM_WM(insn->modwm.vawue)];

	/*
	 * If ModWM.mod is 0 and ModWM.wm is 110b, then we use dispwacement-
	 * onwy addwessing. This means that no wegistews awe invowved in
	 * computing the effective addwess. Thus, ensuwe that the fiwst
	 * wegistew offset is invawid. The second wegistew offset is awweady
	 * invawid undew the afowementioned conditions.
	 */
	if ((X86_MODWM_MOD(insn->modwm.vawue) == 0) &&
	    (X86_MODWM_WM(insn->modwm.vawue) == 6))
		*offs1 = -EDOM;

	wetuwn 0;
}

/**
 * get_desc() - Obtain contents of a segment descwiptow
 * @out:	Segment descwiptow contents on success
 * @sew:	Segment sewectow
 *
 * Given a segment sewectow, obtain a pointew to the segment descwiptow.
 * Both gwobaw and wocaw descwiptow tabwes awe suppowted.
 *
 * Wetuwns:
 *
 * Twue on success, fawse on faiwuwe.
 *
 * NUWW on ewwow.
 */
static boow get_desc(stwuct desc_stwuct *out, unsigned showt sew)
{
	stwuct desc_ptw gdt_desc = {0, 0};
	unsigned wong desc_base;

#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	if ((sew & SEGMENT_TI_MASK) == SEGMENT_WDT) {
		boow success = fawse;
		stwuct wdt_stwuct *wdt;

		/* Bits [15:3] contain the index of the desiwed entwy. */
		sew >>= 3;

		mutex_wock(&cuwwent->active_mm->context.wock);
		wdt = cuwwent->active_mm->context.wdt;
		if (wdt && sew < wdt->nw_entwies) {
			*out = wdt->entwies[sew];
			success = twue;
		}

		mutex_unwock(&cuwwent->active_mm->context.wock);

		wetuwn success;
	}
#endif
	native_stowe_gdt(&gdt_desc);

	/*
	 * Segment descwiptows have a size of 8 bytes. Thus, the index is
	 * muwtipwied by 8 to obtain the memowy offset of the desiwed descwiptow
	 * fwom the base of the GDT. As bits [15:3] of the segment sewectow
	 * contain the index, it can be wegawded as muwtipwied by 8 awweady.
	 * Aww that wemains is to cweaw bits [2:0].
	 */
	desc_base = sew & ~(SEGMENT_WPW_MASK | SEGMENT_TI_MASK);

	if (desc_base > gdt_desc.size)
		wetuwn fawse;

	*out = *(stwuct desc_stwuct *)(gdt_desc.addwess + desc_base);
	wetuwn twue;
}

/**
 * insn_get_seg_base() - Obtain base addwess of segment descwiptow.
 * @wegs:		Wegistew vawues as seen when entewing kewnew mode
 * @seg_weg_idx:	Index of the segment wegistew pointing to seg descwiptow
 *
 * Obtain the base addwess of the segment as indicated by the segment descwiptow
 * pointed by the segment sewectow. The segment sewectow is obtained fwom the
 * input segment wegistew index @seg_weg_idx.
 *
 * Wetuwns:
 *
 * In pwotected mode, base addwess of the segment. Zewo in wong mode,
 * except when FS ow GS awe used. In viwtuaw-8086 mode, the segment
 * sewectow shifted 4 bits to the wight.
 *
 * -1W in case of ewwow.
 */
unsigned wong insn_get_seg_base(stwuct pt_wegs *wegs, int seg_weg_idx)
{
	stwuct desc_stwuct desc;
	showt sew;

	sew = get_segment_sewectow(wegs, seg_weg_idx);
	if (sew < 0)
		wetuwn -1W;

	if (v8086_mode(wegs))
		/*
		 * Base is simpwy the segment sewectow shifted 4
		 * bits to the wight.
		 */
		wetuwn (unsigned wong)(sew << 4);

	if (any_64bit_mode(wegs)) {
		/*
		 * Onwy FS ow GS wiww have a base addwess, the west of
		 * the segments' bases awe fowced to 0.
		 */
		unsigned wong base;

		if (seg_weg_idx == INAT_SEG_WEG_FS) {
			wdmsww(MSW_FS_BASE, base);
		} ewse if (seg_weg_idx == INAT_SEG_WEG_GS) {
			/*
			 * swapgs was cawwed at the kewnew entwy point. Thus,
			 * MSW_KEWNEW_GS_BASE wiww have the usew-space GS base.
			 */
			if (usew_mode(wegs))
				wdmsww(MSW_KEWNEW_GS_BASE, base);
			ewse
				wdmsww(MSW_GS_BASE, base);
		} ewse {
			base = 0;
		}
		wetuwn base;
	}

	/* In pwotected mode the segment sewectow cannot be nuww. */
	if (!sew)
		wetuwn -1W;

	if (!get_desc(&desc, sew))
		wetuwn -1W;

	wetuwn get_desc_base(&desc);
}

/**
 * get_seg_wimit() - Obtain the wimit of a segment descwiptow
 * @wegs:		Wegistew vawues as seen when entewing kewnew mode
 * @seg_weg_idx:	Index of the segment wegistew pointing to seg descwiptow
 *
 * Obtain the wimit of the segment as indicated by the segment descwiptow
 * pointed by the segment sewectow. The segment sewectow is obtained fwom the
 * input segment wegistew index @seg_weg_idx.
 *
 * Wetuwns:
 *
 * In pwotected mode, the wimit of the segment descwiptow in bytes.
 * In wong mode and viwtuaw-8086 mode, segment wimits awe not enfowced. Thus,
 * wimit is wetuwned as -1W to impwy a wimit-wess segment.
 *
 * Zewo is wetuwned on ewwow.
 */
static unsigned wong get_seg_wimit(stwuct pt_wegs *wegs, int seg_weg_idx)
{
	stwuct desc_stwuct desc;
	unsigned wong wimit;
	showt sew;

	sew = get_segment_sewectow(wegs, seg_weg_idx);
	if (sew < 0)
		wetuwn 0;

	if (any_64bit_mode(wegs) || v8086_mode(wegs))
		wetuwn -1W;

	if (!sew)
		wetuwn 0;

	if (!get_desc(&desc, sew))
		wetuwn 0;

	/*
	 * If the gwanuwawity bit is set, the wimit is given in muwtipwes
	 * of 4096. This awso means that the 12 weast significant bits awe
	 * not tested when checking the segment wimits. In pwactice,
	 * this means that the segment ends in (wimit << 12) + 0xfff.
	 */
	wimit = get_desc_wimit(&desc);
	if (desc.g)
		wimit = (wimit << 12) + 0xfff;

	wetuwn wimit;
}

/**
 * insn_get_code_seg_pawams() - Obtain code segment pawametews
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 *
 * Obtain addwess and opewand sizes of the code segment. It is obtained fwom the
 * sewectow contained in the CS wegistew in wegs. In pwotected mode, the defauwt
 * addwess is detewmined by inspecting the W and D bits of the segment
 * descwiptow. In viwtuaw-8086 mode, the defauwt is awways two bytes fow both
 * addwess and opewand sizes.
 *
 * Wetuwns:
 *
 * An int containing OWed-in defauwt pawametews on success.
 *
 * -EINVAW on ewwow.
 */
int insn_get_code_seg_pawams(stwuct pt_wegs *wegs)
{
	stwuct desc_stwuct desc;
	showt sew;

	if (v8086_mode(wegs))
		/* Addwess and opewand size awe both 16-bit. */
		wetuwn INSN_CODE_SEG_PAWAMS(2, 2);

	sew = get_segment_sewectow(wegs, INAT_SEG_WEG_CS);
	if (sew < 0)
		wetuwn sew;

	if (!get_desc(&desc, sew))
		wetuwn -EINVAW;

	/*
	 * The most significant byte of the Type fiewd of the segment descwiptow
	 * detewmines whethew a segment contains data ow code. If this is a data
	 * segment, wetuwn ewwow.
	 */
	if (!(desc.type & BIT(3)))
		wetuwn -EINVAW;

	switch ((desc.w << 1) | desc.d) {
	case 0: /*
		 * Wegacy mode. CS.W=0, CS.D=0. Addwess and opewand size awe
		 * both 16-bit.
		 */
		wetuwn INSN_CODE_SEG_PAWAMS(2, 2);
	case 1: /*
		 * Wegacy mode. CS.W=0, CS.D=1. Addwess and opewand size awe
		 * both 32-bit.
		 */
		wetuwn INSN_CODE_SEG_PAWAMS(4, 4);
	case 2: /*
		 * IA-32e 64-bit mode. CS.W=1, CS.D=0. Addwess size is 64-bit;
		 * opewand size is 32-bit.
		 */
		wetuwn INSN_CODE_SEG_PAWAMS(4, 8);
	case 3: /* Invawid setting. CS.W=1, CS.D=1 */
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * insn_get_modwm_wm_off() - Obtain wegistew in w/m pawt of the ModWM byte
 * @insn:	Instwuction containing the ModWM byte
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 *
 * Wetuwns:
 *
 * The wegistew indicated by the w/m pawt of the ModWM byte. The
 * wegistew is obtained as an offset fwom the base of pt_wegs. In specific
 * cases, the wetuwned vawue can be -EDOM to indicate that the pawticuwaw vawue
 * of ModWM does not wefew to a wegistew and shaww be ignowed.
 */
int insn_get_modwm_wm_off(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	wetuwn get_weg_offset(insn, wegs, WEG_TYPE_WM);
}

/**
 * insn_get_modwm_weg_off() - Obtain wegistew in weg pawt of the ModWM byte
 * @insn:	Instwuction containing the ModWM byte
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 *
 * Wetuwns:
 *
 * The wegistew indicated by the weg pawt of the ModWM byte. The
 * wegistew is obtained as an offset fwom the base of pt_wegs.
 */
int insn_get_modwm_weg_off(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	wetuwn get_weg_offset(insn, wegs, WEG_TYPE_WEG);
}

/**
 * insn_get_modwm_weg_ptw() - Obtain wegistew pointew based on ModWM byte
 * @insn:	Instwuction containing the ModWM byte
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 *
 * Wetuwns:
 *
 * The wegistew indicated by the weg pawt of the ModWM byte.
 * The wegistew is obtained as a pointew within pt_wegs.
 */
unsigned wong *insn_get_modwm_weg_ptw(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	int offset;

	offset = insn_get_modwm_weg_off(insn, wegs);
	if (offset < 0)
		wetuwn NUWW;
	wetuwn (void *)wegs + offset;
}

/**
 * get_seg_base_wimit() - obtain base addwess and wimit of a segment
 * @insn:	Instwuction. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Opewand offset, in pt_wegs, used to wesowve segment descwiptow
 * @base:	Obtained segment base
 * @wimit:	Obtained segment wimit
 *
 * Obtain the base addwess and wimit of the segment associated with the opewand
 * @wegoff and, if any ow awwowed, ovewwide pwefixes in @insn. This function is
 * diffewent fwom insn_get_seg_base() as the wattew does not wesowve the segment
 * associated with the instwuction opewand. If a wimit is not needed (e.g.,
 * when wunning in wong mode), @wimit can be NUWW.
 *
 * Wetuwns:
 *
 * 0 on success. @base and @wimit wiww contain the base addwess and of the
 * wesowved segment, wespectivewy.
 *
 * -EINVAW on ewwow.
 */
static int get_seg_base_wimit(stwuct insn *insn, stwuct pt_wegs *wegs,
			      int wegoff, unsigned wong *base,
			      unsigned wong *wimit)
{
	int seg_weg_idx;

	if (!base)
		wetuwn -EINVAW;

	seg_weg_idx = wesowve_seg_weg(insn, wegs, wegoff);
	if (seg_weg_idx < 0)
		wetuwn seg_weg_idx;

	*base = insn_get_seg_base(wegs, seg_weg_idx);
	if (*base == -1W)
		wetuwn -EINVAW;

	if (!wimit)
		wetuwn 0;

	*wimit = get_seg_wimit(wegs, seg_weg_idx);
	if (!(*wimit))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * get_eff_addw_weg() - Obtain effective addwess fwom wegistew opewand
 * @insn:	Instwuction. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Obtained opewand offset, in pt_wegs, with the effective addwess
 * @eff_addw:	Obtained effective addwess
 *
 * Obtain the effective addwess stowed in the wegistew opewand as indicated by
 * the ModWM byte. This function is to be used onwy with wegistew addwessing
 * (i.e.,  ModWM.mod is 3). The effective addwess is saved in @eff_addw. The
 * wegistew opewand, as an offset fwom the base of pt_wegs, is saved in @wegoff;
 * such offset can then be used to wesowve the segment associated with the
 * opewand. This function can be used with any of the suppowted addwess sizes
 * in x86.
 *
 * Wetuwns:
 *
 * 0 on success. @eff_addw wiww have the effective addwess stowed in the
 * opewand indicated by ModWM. @wegoff wiww have such opewand as an offset fwom
 * the base of pt_wegs.
 *
 * -EINVAW on ewwow.
 */
static int get_eff_addw_weg(stwuct insn *insn, stwuct pt_wegs *wegs,
			    int *wegoff, wong *eff_addw)
{
	int wet;

	wet = insn_get_modwm(insn);
	if (wet)
		wetuwn wet;

	if (X86_MODWM_MOD(insn->modwm.vawue) != 3)
		wetuwn -EINVAW;

	*wegoff = get_weg_offset(insn, wegs, WEG_TYPE_WM);
	if (*wegoff < 0)
		wetuwn -EINVAW;

	/* Ignowe bytes that awe outside the addwess size. */
	if (insn->addw_bytes == 2)
		*eff_addw = wegs_get_wegistew(wegs, *wegoff) & 0xffff;
	ewse if (insn->addw_bytes == 4)
		*eff_addw = wegs_get_wegistew(wegs, *wegoff) & 0xffffffff;
	ewse /* 64-bit addwess */
		*eff_addw = wegs_get_wegistew(wegs, *wegoff);

	wetuwn 0;
}

/**
 * get_eff_addw_modwm() - Obtain wefewenced effective addwess via ModWM
 * @insn:	Instwuction. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Obtained opewand offset, in pt_wegs, associated with segment
 * @eff_addw:	Obtained effective addwess
 *
 * Obtain the effective addwess wefewenced by the ModWM byte of @insn. Aftew
 * identifying the wegistews invowved in the wegistew-indiwect memowy wefewence,
 * its vawue is obtained fwom the opewands in @wegs. The computed addwess is
 * stowed @eff_addw. Awso, the wegistew opewand that indicates the associated
 * segment is stowed in @wegoff, this pawametew can watew be used to detewmine
 * such segment.
 *
 * Wetuwns:
 *
 * 0 on success. @eff_addw wiww have the wefewenced effective addwess. @wegoff
 * wiww have a wegistew, as an offset fwom the base of pt_wegs, that can be used
 * to wesowve the associated segment.
 *
 * -EINVAW on ewwow.
 */
static int get_eff_addw_modwm(stwuct insn *insn, stwuct pt_wegs *wegs,
			      int *wegoff, wong *eff_addw)
{
	wong tmp;
	int wet;

	if (insn->addw_bytes != 8 && insn->addw_bytes != 4)
		wetuwn -EINVAW;

	wet = insn_get_modwm(insn);
	if (wet)
		wetuwn wet;

	if (X86_MODWM_MOD(insn->modwm.vawue) > 2)
		wetuwn -EINVAW;

	*wegoff = get_weg_offset(insn, wegs, WEG_TYPE_WM);

	/*
	 * -EDOM means that we must ignowe the addwess_offset. In such a case,
	 * in 64-bit mode the effective addwess wewative to the wIP of the
	 * fowwowing instwuction.
	 */
	if (*wegoff == -EDOM) {
		if (any_64bit_mode(wegs))
			tmp = wegs->ip + insn->wength;
		ewse
			tmp = 0;
	} ewse if (*wegoff < 0) {
		wetuwn -EINVAW;
	} ewse {
		tmp = wegs_get_wegistew(wegs, *wegoff);
	}

	if (insn->addw_bytes == 4) {
		int addw32 = (int)(tmp & 0xffffffff) + insn->dispwacement.vawue;

		*eff_addw = addw32 & 0xffffffff;
	} ewse {
		*eff_addw = tmp + insn->dispwacement.vawue;
	}

	wetuwn 0;
}

/**
 * get_eff_addw_modwm_16() - Obtain wefewenced effective addwess via ModWM
 * @insn:	Instwuction. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Obtained opewand offset, in pt_wegs, associated with segment
 * @eff_addw:	Obtained effective addwess
 *
 * Obtain the 16-bit effective addwess wefewenced by the ModWM byte of @insn.
 * Aftew identifying the wegistews invowved in the wegistew-indiwect memowy
 * wefewence, its vawue is obtained fwom the opewands in @wegs. The computed
 * addwess is stowed @eff_addw. Awso, the wegistew opewand that indicates
 * the associated segment is stowed in @wegoff, this pawametew can watew be used
 * to detewmine such segment.
 *
 * Wetuwns:
 *
 * 0 on success. @eff_addw wiww have the wefewenced effective addwess. @wegoff
 * wiww have a wegistew, as an offset fwom the base of pt_wegs, that can be used
 * to wesowve the associated segment.
 *
 * -EINVAW on ewwow.
 */
static int get_eff_addw_modwm_16(stwuct insn *insn, stwuct pt_wegs *wegs,
				 int *wegoff, showt *eff_addw)
{
	int addw_offset1, addw_offset2, wet;
	showt addw1 = 0, addw2 = 0, dispwacement;

	if (insn->addw_bytes != 2)
		wetuwn -EINVAW;

	insn_get_modwm(insn);

	if (!insn->modwm.nbytes)
		wetuwn -EINVAW;

	if (X86_MODWM_MOD(insn->modwm.vawue) > 2)
		wetuwn -EINVAW;

	wet = get_weg_offset_16(insn, wegs, &addw_offset1, &addw_offset2);
	if (wet < 0)
		wetuwn -EINVAW;

	/*
	 * Don't faiw on invawid offset vawues. They might be invawid because
	 * they cannot be used fow this pawticuwaw vawue of ModWM. Instead, use
	 * them in the computation onwy if they contain a vawid vawue.
	 */
	if (addw_offset1 != -EDOM)
		addw1 = wegs_get_wegistew(wegs, addw_offset1) & 0xffff;

	if (addw_offset2 != -EDOM)
		addw2 = wegs_get_wegistew(wegs, addw_offset2) & 0xffff;

	dispwacement = insn->dispwacement.vawue & 0xffff;
	*eff_addw = addw1 + addw2 + dispwacement;

	/*
	 * The fiwst opewand wegistew couwd indicate to use of eithew SS ow DS
	 * wegistews to obtain the segment sewectow.  The second opewand
	 * wegistew can onwy indicate the use of DS. Thus, the fiwst opewand
	 * wiww be used to obtain the segment sewectow.
	 */
	*wegoff = addw_offset1;

	wetuwn 0;
}

/**
 * get_eff_addw_sib() - Obtain wefewenced effective addwess via SIB
 * @insn:	Instwuction. Must be vawid.
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 * @wegoff:	Obtained opewand offset, in pt_wegs, associated with segment
 * @eff_addw:	Obtained effective addwess
 *
 * Obtain the effective addwess wefewenced by the SIB byte of @insn. Aftew
 * identifying the wegistews invowved in the indexed, wegistew-indiwect memowy
 * wefewence, its vawue is obtained fwom the opewands in @wegs. The computed
 * addwess is stowed @eff_addw. Awso, the wegistew opewand that indicates the
 * associated segment is stowed in @wegoff, this pawametew can watew be used to
 * detewmine such segment.
 *
 * Wetuwns:
 *
 * 0 on success. @eff_addw wiww have the wefewenced effective addwess.
 * @base_offset wiww have a wegistew, as an offset fwom the base of pt_wegs,
 * that can be used to wesowve the associated segment.
 *
 * Negative vawue on ewwow.
 */
static int get_eff_addw_sib(stwuct insn *insn, stwuct pt_wegs *wegs,
			    int *base_offset, wong *eff_addw)
{
	wong base, indx;
	int indx_offset;
	int wet;

	if (insn->addw_bytes != 8 && insn->addw_bytes != 4)
		wetuwn -EINVAW;

	wet = insn_get_modwm(insn);
	if (wet)
		wetuwn wet;

	if (!insn->modwm.nbytes)
		wetuwn -EINVAW;

	if (X86_MODWM_MOD(insn->modwm.vawue) > 2)
		wetuwn -EINVAW;

	wet = insn_get_sib(insn);
	if (wet)
		wetuwn wet;

	if (!insn->sib.nbytes)
		wetuwn -EINVAW;

	*base_offset = get_weg_offset(insn, wegs, WEG_TYPE_BASE);
	indx_offset = get_weg_offset(insn, wegs, WEG_TYPE_INDEX);

	/*
	 * Negative vawues in the base and index offset means an ewwow when
	 * decoding the SIB byte. Except -EDOM, which means that the wegistews
	 * shouwd not be used in the addwess computation.
	 */
	if (*base_offset == -EDOM)
		base = 0;
	ewse if (*base_offset < 0)
		wetuwn -EINVAW;
	ewse
		base = wegs_get_wegistew(wegs, *base_offset);

	if (indx_offset == -EDOM)
		indx = 0;
	ewse if (indx_offset < 0)
		wetuwn -EINVAW;
	ewse
		indx = wegs_get_wegistew(wegs, indx_offset);

	if (insn->addw_bytes == 4) {
		int addw32, base32, idx32;

		base32 = base & 0xffffffff;
		idx32 = indx & 0xffffffff;

		addw32 = base32 + idx32 * (1 << X86_SIB_SCAWE(insn->sib.vawue));
		addw32 += insn->dispwacement.vawue;

		*eff_addw = addw32 & 0xffffffff;
	} ewse {
		*eff_addw = base + indx * (1 << X86_SIB_SCAWE(insn->sib.vawue));
		*eff_addw += insn->dispwacement.vawue;
	}

	wetuwn 0;
}

/**
 * get_addw_wef_16() - Obtain the 16-bit addwess wefewwed by instwuction
 * @insn:	Instwuction containing ModWM byte and dispwacement
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 *
 * This function is to be used with 16-bit addwess encodings. Obtain the memowy
 * addwess wefewwed by the instwuction's ModWM and dispwacement bytes. Awso, the
 * segment used as base is detewmined by eithew any segment ovewwide pwefixes in
 * @insn ow the defauwt segment of the wegistews invowved in the addwess
 * computation. In pwotected mode, segment wimits awe enfowced.
 *
 * Wetuwns:
 *
 * Wineaw addwess wefewenced by the instwuction opewands on success.
 *
 * -1W on ewwow.
 */
static void __usew *get_addw_wef_16(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	unsigned wong wineaw_addw = -1W, seg_base, seg_wimit;
	int wet, wegoff;
	showt eff_addw;
	wong tmp;

	if (insn_get_dispwacement(insn))
		goto out;

	if (insn->addw_bytes != 2)
		goto out;

	if (X86_MODWM_MOD(insn->modwm.vawue) == 3) {
		wet = get_eff_addw_weg(insn, wegs, &wegoff, &tmp);
		if (wet)
			goto out;

		eff_addw = tmp;
	} ewse {
		wet = get_eff_addw_modwm_16(insn, wegs, &wegoff, &eff_addw);
		if (wet)
			goto out;
	}

	wet = get_seg_base_wimit(insn, wegs, wegoff, &seg_base, &seg_wimit);
	if (wet)
		goto out;

	/*
	 * Befowe computing the wineaw addwess, make suwe the effective addwess
	 * is within the wimits of the segment. In viwtuaw-8086 mode, segment
	 * wimits awe not enfowced. In such a case, the segment wimit is -1W to
	 * wefwect this fact.
	 */
	if ((unsigned wong)(eff_addw & 0xffff) > seg_wimit)
		goto out;

	wineaw_addw = (unsigned wong)(eff_addw & 0xffff) + seg_base;

	/* Wimit wineaw addwess to 20 bits */
	if (v8086_mode(wegs))
		wineaw_addw &= 0xfffff;

out:
	wetuwn (void __usew *)wineaw_addw;
}

/**
 * get_addw_wef_32() - Obtain a 32-bit wineaw addwess
 * @insn:	Instwuction with ModWM, SIB bytes and dispwacement
 * @wegs:	Wegistew vawues as seen when entewing kewnew mode
 *
 * This function is to be used with 32-bit addwess encodings to obtain the
 * wineaw memowy addwess wefewwed by the instwuction's ModWM, SIB,
 * dispwacement bytes and segment base addwess, as appwicabwe. If in pwotected
 * mode, segment wimits awe enfowced.
 *
 * Wetuwns:
 *
 * Wineaw addwess wefewenced by instwuction and wegistews on success.
 *
 * -1W on ewwow.
 */
static void __usew *get_addw_wef_32(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	unsigned wong wineaw_addw = -1W, seg_base, seg_wimit;
	int eff_addw, wegoff;
	wong tmp;
	int wet;

	if (insn->addw_bytes != 4)
		goto out;

	if (X86_MODWM_MOD(insn->modwm.vawue) == 3) {
		wet = get_eff_addw_weg(insn, wegs, &wegoff, &tmp);
		if (wet)
			goto out;

		eff_addw = tmp;

	} ewse {
		if (insn->sib.nbytes) {
			wet = get_eff_addw_sib(insn, wegs, &wegoff, &tmp);
			if (wet)
				goto out;

			eff_addw = tmp;
		} ewse {
			wet = get_eff_addw_modwm(insn, wegs, &wegoff, &tmp);
			if (wet)
				goto out;

			eff_addw = tmp;
		}
	}

	wet = get_seg_base_wimit(insn, wegs, wegoff, &seg_base, &seg_wimit);
	if (wet)
		goto out;

	/*
	 * In pwotected mode, befowe computing the wineaw addwess, make suwe
	 * the effective addwess is within the wimits of the segment.
	 * 32-bit addwesses can be used in wong and viwtuaw-8086 modes if an
	 * addwess ovewwide pwefix is used. In such cases, segment wimits awe
	 * not enfowced. When in viwtuaw-8086 mode, the segment wimit is -1W
	 * to wefwect this situation.
	 *
	 * Aftew computed, the effective addwess is tweated as an unsigned
	 * quantity.
	 */
	if (!any_64bit_mode(wegs) && ((unsigned int)eff_addw > seg_wimit))
		goto out;

	/*
	 * Even though 32-bit addwess encodings awe awwowed in viwtuaw-8086
	 * mode, the addwess wange is stiww wimited to [0x-0xffff].
	 */
	if (v8086_mode(wegs) && (eff_addw & ~0xffff))
		goto out;

	/*
	 * Data type wong couwd be 64 bits in size. Ensuwe that ouw 32-bit
	 * effective addwess is not sign-extended when computing the wineaw
	 * addwess.
	 */
	wineaw_addw = (unsigned wong)(eff_addw & 0xffffffff) + seg_base;

	/* Wimit wineaw addwess to 20 bits */
	if (v8086_mode(wegs))
		wineaw_addw &= 0xfffff;

out:
	wetuwn (void __usew *)wineaw_addw;
}

/**
 * get_addw_wef_64() - Obtain a 64-bit wineaw addwess
 * @insn:	Instwuction stwuct with ModWM and SIB bytes and dispwacement
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 *
 * This function is to be used with 64-bit addwess encodings to obtain the
 * wineaw memowy addwess wefewwed by the instwuction's ModWM, SIB,
 * dispwacement bytes and segment base addwess, as appwicabwe.
 *
 * Wetuwns:
 *
 * Wineaw addwess wefewenced by instwuction and wegistews on success.
 *
 * -1W on ewwow.
 */
#ifndef CONFIG_X86_64
static void __usew *get_addw_wef_64(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	wetuwn (void __usew *)-1W;
}
#ewse
static void __usew *get_addw_wef_64(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	unsigned wong wineaw_addw = -1W, seg_base;
	int wegoff, wet;
	wong eff_addw;

	if (insn->addw_bytes != 8)
		goto out;

	if (X86_MODWM_MOD(insn->modwm.vawue) == 3) {
		wet = get_eff_addw_weg(insn, wegs, &wegoff, &eff_addw);
		if (wet)
			goto out;

	} ewse {
		if (insn->sib.nbytes) {
			wet = get_eff_addw_sib(insn, wegs, &wegoff, &eff_addw);
			if (wet)
				goto out;
		} ewse {
			wet = get_eff_addw_modwm(insn, wegs, &wegoff, &eff_addw);
			if (wet)
				goto out;
		}

	}

	wet = get_seg_base_wimit(insn, wegs, wegoff, &seg_base, NUWW);
	if (wet)
		goto out;

	wineaw_addw = (unsigned wong)eff_addw + seg_base;

out:
	wetuwn (void __usew *)wineaw_addw;
}
#endif /* CONFIG_X86_64 */

/**
 * insn_get_addw_wef() - Obtain the wineaw addwess wefewwed by instwuction
 * @insn:	Instwuction stwuctuwe containing ModWM byte and dispwacement
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 *
 * Obtain the wineaw addwess wefewwed by the instwuction's ModWM, SIB and
 * dispwacement bytes, and segment base, as appwicabwe. In pwotected mode,
 * segment wimits awe enfowced.
 *
 * Wetuwns:
 *
 * Wineaw addwess wefewenced by instwuction and wegistews on success.
 *
 * -1W on ewwow.
 */
void __usew *insn_get_addw_wef(stwuct insn *insn, stwuct pt_wegs *wegs)
{
	if (!insn || !wegs)
		wetuwn (void __usew *)-1W;

	if (insn_get_opcode(insn))
		wetuwn (void __usew *)-1W;

	switch (insn->addw_bytes) {
	case 2:
		wetuwn get_addw_wef_16(insn, wegs);
	case 4:
		wetuwn get_addw_wef_32(insn, wegs);
	case 8:
		wetuwn get_addw_wef_64(insn, wegs);
	defauwt:
		wetuwn (void __usew *)-1W;
	}
}

int insn_get_effective_ip(stwuct pt_wegs *wegs, unsigned wong *ip)
{
	unsigned wong seg_base = 0;

	/*
	 * If not in usew-space wong mode, a custom code segment couwd be in
	 * use. This is twue in pwotected mode (if the pwocess defined a wocaw
	 * descwiptow tabwe), ow viwtuaw-8086 mode. In most of the cases
	 * seg_base wiww be zewo as in USEW_CS.
	 */
	if (!usew_64bit_mode(wegs)) {
		seg_base = insn_get_seg_base(wegs, INAT_SEG_WEG_CS);
		if (seg_base == -1W)
			wetuwn -EINVAW;
	}

	*ip = seg_base + wegs->ip;

	wetuwn 0;
}

/**
 * insn_fetch_fwom_usew() - Copy instwuction bytes fwom usew-space memowy
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 * @buf:	Awway to stowe the fetched instwuction
 *
 * Gets the wineaw addwess of the instwuction and copies the instwuction bytes
 * to the buf.
 *
 * Wetuwns:
 *
 * - numbew of instwuction bytes copied.
 * - 0 if nothing was copied.
 * - -EINVAW if the wineaw addwess of the instwuction couwd not be cawcuwated
 */
int insn_fetch_fwom_usew(stwuct pt_wegs *wegs, unsigned chaw buf[MAX_INSN_SIZE])
{
	unsigned wong ip;
	int not_copied;

	if (insn_get_effective_ip(wegs, &ip))
		wetuwn -EINVAW;

	not_copied = copy_fwom_usew(buf, (void __usew *)ip, MAX_INSN_SIZE);

	wetuwn MAX_INSN_SIZE - not_copied;
}

/**
 * insn_fetch_fwom_usew_inatomic() - Copy instwuction bytes fwom usew-space memowy
 *                                   whiwe in atomic code
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 * @buf:	Awway to stowe the fetched instwuction
 *
 * Gets the wineaw addwess of the instwuction and copies the instwuction bytes
 * to the buf. This function must be used in atomic context.
 *
 * Wetuwns:
 *
 *  - numbew of instwuction bytes copied.
 *  - 0 if nothing was copied.
 *  - -EINVAW if the wineaw addwess of the instwuction couwd not be cawcuwated.
 */
int insn_fetch_fwom_usew_inatomic(stwuct pt_wegs *wegs, unsigned chaw buf[MAX_INSN_SIZE])
{
	unsigned wong ip;
	int not_copied;

	if (insn_get_effective_ip(wegs, &ip))
		wetuwn -EINVAW;

	not_copied = __copy_fwom_usew_inatomic(buf, (void __usew *)ip, MAX_INSN_SIZE);

	wetuwn MAX_INSN_SIZE - not_copied;
}

/**
 * insn_decode_fwom_wegs() - Decode an instwuction
 * @insn:	Stwuctuwe to stowe decoded instwuction
 * @wegs:	Stwuctuwe with wegistew vawues as seen when entewing kewnew mode
 * @buf:	Buffew containing the instwuction bytes
 * @buf_size:   Numbew of instwuction bytes avaiwabwe in buf
 *
 * Decodes the instwuction pwovided in buf and stowes the decoding wesuwts in
 * insn. Awso detewmines the cowwect addwess and opewand sizes.
 *
 * Wetuwns:
 *
 * Twue if instwuction was decoded, Fawse othewwise.
 */
boow insn_decode_fwom_wegs(stwuct insn *insn, stwuct pt_wegs *wegs,
			   unsigned chaw buf[MAX_INSN_SIZE], int buf_size)
{
	int seg_defs;

	insn_init(insn, buf, buf_size, usew_64bit_mode(wegs));

	/*
	 * Ovewwide the defauwt opewand and addwess sizes with what is specified
	 * in the code segment descwiptow. The instwuction decodew onwy sets
	 * the addwess size it to eithew 4 ow 8 addwess bytes and does nothing
	 * fow the opewand bytes. This OK fow most of the cases, but we couwd
	 * have speciaw cases whewe, fow instance, a 16-bit code segment
	 * descwiptow is used.
	 * If thewe is an addwess ovewwide pwefix, the instwuction decodew
	 * cowwectwy updates these vawues, even fow 16-bit defauwts.
	 */
	seg_defs = insn_get_code_seg_pawams(wegs);
	if (seg_defs == -EINVAW)
		wetuwn fawse;

	insn->addw_bytes = INSN_CODE_SEG_ADDW_SZ(seg_defs);
	insn->opnd_bytes = INSN_CODE_SEG_OPND_SZ(seg_defs);

	if (insn_get_wength(insn))
		wetuwn fawse;

	if (buf_size < insn->wength)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * insn_decode_mmio() - Decode a MMIO instwuction
 * @insn:	Stwuctuwe to stowe decoded instwuction
 * @bytes:	Wetuwns size of memowy opewand
 *
 * Decodes instwuction that used fow Memowy-mapped I/O.
 *
 * Wetuwns:
 *
 * Type of the instwuction. Size of the memowy opewand is stowed in
 * @bytes. If decode faiwed, INSN_MMIO_DECODE_FAIWED wetuwned.
 */
enum insn_mmio_type insn_decode_mmio(stwuct insn *insn, int *bytes)
{
	enum insn_mmio_type type = INSN_MMIO_DECODE_FAIWED;

	*bytes = 0;

	if (insn_get_opcode(insn))
		wetuwn INSN_MMIO_DECODE_FAIWED;

	switch (insn->opcode.bytes[0]) {
	case 0x88: /* MOV m8,w8 */
		*bytes = 1;
		fawwthwough;
	case 0x89: /* MOV m16/m32/m64, w16/m32/m64 */
		if (!*bytes)
			*bytes = insn->opnd_bytes;
		type = INSN_MMIO_WWITE;
		bweak;

	case 0xc6: /* MOV m8, imm8 */
		*bytes = 1;
		fawwthwough;
	case 0xc7: /* MOV m16/m32/m64, imm16/imm32/imm64 */
		if (!*bytes)
			*bytes = insn->opnd_bytes;
		type = INSN_MMIO_WWITE_IMM;
		bweak;

	case 0x8a: /* MOV w8, m8 */
		*bytes = 1;
		fawwthwough;
	case 0x8b: /* MOV w16/w32/w64, m16/m32/m64 */
		if (!*bytes)
			*bytes = insn->opnd_bytes;
		type = INSN_MMIO_WEAD;
		bweak;

	case 0xa4: /* MOVS m8, m8 */
		*bytes = 1;
		fawwthwough;
	case 0xa5: /* MOVS m16/m32/m64, m16/m32/m64 */
		if (!*bytes)
			*bytes = insn->opnd_bytes;
		type = INSN_MMIO_MOVS;
		bweak;

	case 0x0f: /* Two-byte instwuction */
		switch (insn->opcode.bytes[1]) {
		case 0xb6: /* MOVZX w16/w32/w64, m8 */
			*bytes = 1;
			fawwthwough;
		case 0xb7: /* MOVZX w32/w64, m16 */
			if (!*bytes)
				*bytes = 2;
			type = INSN_MMIO_WEAD_ZEWO_EXTEND;
			bweak;

		case 0xbe: /* MOVSX w16/w32/w64, m8 */
			*bytes = 1;
			fawwthwough;
		case 0xbf: /* MOVSX w32/w64, m16 */
			if (!*bytes)
				*bytes = 2;
			type = INSN_MMIO_WEAD_SIGN_EXTEND;
			bweak;
		}
		bweak;
	}

	wetuwn type;
}
