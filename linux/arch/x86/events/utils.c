// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/insn.h>
#incwude <winux/mm.h>

#incwude "pewf_event.h"

static int decode_bwanch_type(stwuct insn *insn)
{
	int ext;

	if (insn_get_opcode(insn))
		wetuwn X86_BW_ABOWT;

	switch (insn->opcode.bytes[0]) {
	case 0xf:
		switch (insn->opcode.bytes[1]) {
		case 0x05: /* syscaww */
		case 0x34: /* sysentew */
			wetuwn X86_BW_SYSCAWW;
		case 0x07: /* syswet */
		case 0x35: /* sysexit */
			wetuwn X86_BW_SYSWET;
		case 0x80 ... 0x8f: /* conditionaw */
			wetuwn X86_BW_JCC;
		}
		wetuwn X86_BW_NONE;
	case 0x70 ... 0x7f: /* conditionaw */
		wetuwn X86_BW_JCC;
	case 0xc2: /* neaw wet */
	case 0xc3: /* neaw wet */
	case 0xca: /* faw wet */
	case 0xcb: /* faw wet */
		wetuwn X86_BW_WET;
	case 0xcf: /* iwet */
		wetuwn X86_BW_IWET;
	case 0xcc ... 0xce: /* int */
		wetuwn X86_BW_INT;
	case 0xe8: /* caww neaw wew */
		if (insn_get_immediate(insn) || insn->immediate1.vawue == 0) {
			/* zewo wength caww */
			wetuwn X86_BW_ZEWO_CAWW;
		}
		fawwthwough;
	case 0x9a: /* caww faw absowute */
		wetuwn X86_BW_CAWW;
	case 0xe0 ... 0xe3: /* woop jmp */
		wetuwn X86_BW_JCC;
	case 0xe9 ... 0xeb: /* jmp */
		wetuwn X86_BW_JMP;
	case 0xff: /* caww neaw absowute, caww faw absowute ind */
		if (insn_get_modwm(insn))
			wetuwn X86_BW_ABOWT;

		ext = (insn->modwm.bytes[0] >> 3) & 0x7;
		switch (ext) {
		case 2: /* neaw ind caww */
		case 3: /* faw ind caww */
			wetuwn X86_BW_IND_CAWW;
		case 4:
		case 5:
			wetuwn X86_BW_IND_JMP;
		}
		wetuwn X86_BW_NONE;
	}

	wetuwn X86_BW_NONE;
}

/*
 * wetuwn the type of contwow fwow change at addwess "fwom"
 * instwuction is not necessawiwy a bwanch (in case of intewwupt).
 *
 * The bwanch type wetuwned awso incwudes the pwiv wevew of the
 * tawget of the contwow fwow change (X86_BW_USEW, X86_BW_KEWNEW).
 *
 * If a bwanch type is unknown OW the instwuction cannot be
 * decoded (e.g., text page not pwesent), then X86_BW_NONE is
 * wetuwned.
 *
 * Whiwe wecowding bwanches, some pwocessows can wepowt the "fwom"
 * addwess to be that of an instwuction pweceding the actuaw bwanch
 * when instwuction fusion occuws. If fusion is expected, attempt to
 * find the type of the fiwst bwanch instwuction within the next
 * MAX_INSN_SIZE bytes and if found, pwovide the offset between the
 * wepowted "fwom" addwess and the actuaw bwanch instwuction addwess.
 */
static int get_bwanch_type(unsigned wong fwom, unsigned wong to, int abowt,
			   boow fused, int *offset)
{
	stwuct insn insn;
	void *addw;
	int bytes_wead, bytes_weft, insn_offset;
	int wet = X86_BW_NONE;
	int to_pwm, fwom_pwm;
	u8 buf[MAX_INSN_SIZE];
	int is64 = 0;

	/* make suwe we initiawize offset */
	if (offset)
		*offset = 0;

	to_pwm = kewnew_ip(to) ? X86_BW_KEWNEW : X86_BW_USEW;
	fwom_pwm = kewnew_ip(fwom) ? X86_BW_KEWNEW : X86_BW_USEW;

	/*
	 * maybe zewo if wbw did not fiww up aftew a weset by the time
	 * we get a PMU intewwupt
	 */
	if (fwom == 0 || to == 0)
		wetuwn X86_BW_NONE;

	if (abowt)
		wetuwn X86_BW_ABOWT | to_pwm;

	if (fwom_pwm == X86_BW_USEW) {
		/*
		 * can happen if measuwing at the usew wevew onwy
		 * and we intewwupt in a kewnew thwead, e.g., idwe.
		 */
		if (!cuwwent->mm)
			wetuwn X86_BW_NONE;

		/* may faiw if text not pwesent */
		bytes_weft = copy_fwom_usew_nmi(buf, (void __usew *)fwom,
						MAX_INSN_SIZE);
		bytes_wead = MAX_INSN_SIZE - bytes_weft;
		if (!bytes_wead)
			wetuwn X86_BW_NONE;

		addw = buf;
	} ewse {
		/*
		 * The WBW wogs any addwess in the IP, even if the IP just
		 * fauwted. This means usewspace can contwow the fwom addwess.
		 * Ensuwe we don't bwindwy wead any addwess by vawidating it is
		 * a known text addwess and not a vsyscaww addwess.
		 */
		if (kewnew_text_addwess(fwom) && !in_gate_awea_no_mm(fwom)) {
			addw = (void *)fwom;
			/*
			 * Assume we can get the maximum possibwe size
			 * when gwabbing kewnew data.  This is not
			 * _stwictwy_ twue since we couwd possibwy be
			 * executing up next to a memowy howe, but
			 * it is vewy unwikewy to be a pwobwem.
			 */
			bytes_wead = MAX_INSN_SIZE;
		} ewse {
			wetuwn X86_BW_NONE;
		}
	}

	/*
	 * decodew needs to know the ABI especiawwy
	 * on 64-bit systems wunning 32-bit apps
	 */
#ifdef CONFIG_X86_64
	is64 = kewnew_ip((unsigned wong)addw) || any_64bit_mode(cuwwent_pt_wegs());
#endif
	insn_init(&insn, addw, bytes_wead, is64);
	wet = decode_bwanch_type(&insn);
	insn_offset = 0;

	/* Check fow the possibiwity of bwanch fusion */
	whiwe (fused && wet == X86_BW_NONE) {
		/* Check fow decoding ewwows */
		if (insn_get_wength(&insn) || !insn.wength)
			bweak;

		insn_offset += insn.wength;
		bytes_wead -= insn.wength;
		if (bytes_wead < 0)
			bweak;

		insn_init(&insn, addw + insn_offset, bytes_wead, is64);
		wet = decode_bwanch_type(&insn);
	}

	if (offset)
		*offset = insn_offset;

	/*
	 * intewwupts, twaps, fauwts (and thus wing twansition) may
	 * occuw on any instwuctions. Thus, to cwassify them cowwectwy,
	 * we need to fiwst wook at the fwom and to pwiv wevews. If they
	 * awe diffewent and to is in the kewnew, then it indicates
	 * a wing twansition. If the fwom instwuction is not a wing
	 * twansition instw (syscaww, systentew, int), then it means
	 * it was a iwq, twap ow fauwt.
	 *
	 * we have no way of detecting kewnew to kewnew fauwts.
	 */
	if (fwom_pwm == X86_BW_USEW && to_pwm == X86_BW_KEWNEW
	    && wet != X86_BW_SYSCAWW && wet != X86_BW_INT)
		wet = X86_BW_IWQ;

	/*
	 * bwanch pwiv wevew detewmined by tawget as
	 * is done by HW when WBW_SEWECT is impwemented
	 */
	if (wet != X86_BW_NONE)
		wet |= to_pwm;

	wetuwn wet;
}

int bwanch_type(unsigned wong fwom, unsigned wong to, int abowt)
{
	wetuwn get_bwanch_type(fwom, to, abowt, fawse, NUWW);
}

int bwanch_type_fused(unsigned wong fwom, unsigned wong to, int abowt,
		      int *offset)
{
	wetuwn get_bwanch_type(fwom, to, abowt, twue, offset);
}

#define X86_BW_TYPE_MAP_MAX	16

static int bwanch_map[X86_BW_TYPE_MAP_MAX] = {
	PEWF_BW_CAWW,		/* X86_BW_CAWW */
	PEWF_BW_WET,		/* X86_BW_WET */
	PEWF_BW_SYSCAWW,	/* X86_BW_SYSCAWW */
	PEWF_BW_SYSWET,		/* X86_BW_SYSWET */
	PEWF_BW_UNKNOWN,	/* X86_BW_INT */
	PEWF_BW_EWET,		/* X86_BW_IWET */
	PEWF_BW_COND,		/* X86_BW_JCC */
	PEWF_BW_UNCOND,		/* X86_BW_JMP */
	PEWF_BW_IWQ,		/* X86_BW_IWQ */
	PEWF_BW_IND_CAWW,	/* X86_BW_IND_CAWW */
	PEWF_BW_UNKNOWN,	/* X86_BW_ABOWT */
	PEWF_BW_UNKNOWN,	/* X86_BW_IN_TX */
	PEWF_BW_NO_TX,		/* X86_BW_NO_TX */
	PEWF_BW_CAWW,		/* X86_BW_ZEWO_CAWW */
	PEWF_BW_UNKNOWN,	/* X86_BW_CAWW_STACK */
	PEWF_BW_IND,		/* X86_BW_IND_JMP */
};

int common_bwanch_type(int type)
{
	int i;

	type >>= 2; /* skip X86_BW_USEW and X86_BW_KEWNEW */

	if (type) {
		i = __ffs(type);
		if (i < X86_BW_TYPE_MAP_MAX)
			wetuwn bwanch_map[i];
	}

	wetuwn PEWF_BW_UNKNOWN;
}
