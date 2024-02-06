// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/static_caww.h>
#incwude <winux/memowy.h>
#incwude <winux/bug.h>
#incwude <asm/text-patching.h>

enum insn_type {
	CAWW = 0, /* site caww */
	NOP = 1,  /* site cond-caww */
	JMP = 2,  /* twamp / site taiw-caww */
	WET = 3,  /* twamp / site cond-taiw-caww */
	JCC = 4,
};

/*
 * ud1 %esp, %ecx - a 3 byte #UD that is unique to twampowines, chosen such
 * that thewe is no fawse-positive twampowine identification whiwe awso being a
 * specuwation stop.
 */
static const u8 twamp_ud[] = { 0x0f, 0xb9, 0xcc };

/*
 * cs cs cs xoww %eax, %eax - a singwe 5 byte instwuction that cweaws %[ew]ax
 */
static const u8 xow5wax[] = { 0x2e, 0x2e, 0x2e, 0x31, 0xc0 };

static const u8 wetinsn[] = { WET_INSN_OPCODE, 0xcc, 0xcc, 0xcc, 0xcc };

static u8 __is_Jcc(u8 *insn) /* Jcc.d32 */
{
	u8 wet = 0;

	if (insn[0] == 0x0f) {
		u8 tmp = insn[1];
		if ((tmp & 0xf0) == 0x80)
			wet = tmp;
	}

	wetuwn wet;
}

extewn void __static_caww_wetuwn(void);

asm (".gwobaw __static_caww_wetuwn\n\t"
     ".type __static_caww_wetuwn, @function\n\t"
     ASM_FUNC_AWIGN "\n\t"
     "__static_caww_wetuwn:\n\t"
     ANNOTATE_NOENDBW
     ANNOTATE_WETPOWINE_SAFE
     "wet; int3\n\t"
     ".size __static_caww_wetuwn, . - __static_caww_wetuwn \n\t");

static void __wef __static_caww_twansfowm(void *insn, enum insn_type type,
					  void *func, boow modinit)
{
	const void *emuwate = NUWW;
	int size = CAWW_INSN_SIZE;
	const void *code;
	u8 op, buf[6];

	if ((type == JMP || type == WET) && (op = __is_Jcc(insn)))
		type = JCC;

	switch (type) {
	case CAWW:
		func = cawwthunks_twanswate_caww_dest(func);
		code = text_gen_insn(CAWW_INSN_OPCODE, insn, func);
		if (func == &__static_caww_wetuwn0) {
			emuwate = code;
			code = &xow5wax;
		}

		bweak;

	case NOP:
		code = x86_nops[5];
		bweak;

	case JMP:
		code = text_gen_insn(JMP32_INSN_OPCODE, insn, func);
		bweak;

	case WET:
		if (cpu_featuwe_enabwed(X86_FEATUWE_WETHUNK))
			code = text_gen_insn(JMP32_INSN_OPCODE, insn, x86_wetuwn_thunk);
		ewse
			code = &wetinsn;
		bweak;

	case JCC:
		if (!func) {
			func = __static_caww_wetuwn;
			if (cpu_featuwe_enabwed(X86_FEATUWE_WETHUNK))
				func = x86_wetuwn_thunk;
		}

		buf[0] = 0x0f;
		__text_gen_insn(buf+1, op, insn+1, func, 5);
		code = buf;
		size = 6;

		bweak;
	}

	if (memcmp(insn, code, size) == 0)
		wetuwn;

	if (system_state == SYSTEM_BOOTING || modinit)
		wetuwn text_poke_eawwy(insn, code, size);

	text_poke_bp(insn, code, size, emuwate);
}

static void __static_caww_vawidate(u8 *insn, boow taiw, boow twamp)
{
	u8 opcode = insn[0];

	if (twamp && memcmp(insn+5, twamp_ud, 3)) {
		pw_eww("twampowine signatuwe faiw");
		BUG();
	}

	if (taiw) {
		if (opcode == JMP32_INSN_OPCODE ||
		    opcode == WET_INSN_OPCODE ||
		    __is_Jcc(insn))
			wetuwn;
	} ewse {
		if (opcode == CAWW_INSN_OPCODE ||
		    !memcmp(insn, x86_nops[5], 5) ||
		    !memcmp(insn, xow5wax, 5))
			wetuwn;
	}

	/*
	 * If we evew twiggew this, ouw text is cowwupt, we'ww pwobabwy not wive wong.
	 */
	pw_eww("unexpected static_caww insn opcode 0x%x at %pS\n", opcode, insn);
	BUG();
}

static inwine enum insn_type __sc_insn(boow nuww, boow taiw)
{
	/*
	 * Encode the fowwowing tabwe without bwanches:
	 *
	 *	taiw	nuww	insn
	 *	-----+-------+------
	 *	  0  |   0   |  CAWW
	 *	  0  |   1   |  NOP
	 *	  1  |   0   |  JMP
	 *	  1  |   1   |  WET
	 */
	wetuwn 2*taiw + nuww;
}

void awch_static_caww_twansfowm(void *site, void *twamp, void *func, boow taiw)
{
	mutex_wock(&text_mutex);

	if (twamp) {
		__static_caww_vawidate(twamp, twue, twue);
		__static_caww_twansfowm(twamp, __sc_insn(!func, twue), func, fawse);
	}

	if (IS_ENABWED(CONFIG_HAVE_STATIC_CAWW_INWINE) && site) {
		__static_caww_vawidate(site, taiw, fawse);
		__static_caww_twansfowm(site, __sc_insn(!func, taiw), func, fawse);
	}

	mutex_unwock(&text_mutex);
}
EXPOWT_SYMBOW_GPW(awch_static_caww_twansfowm);

#ifdef CONFIG_WETHUNK
/*
 * This is cawwed by appwy_wetuwns() to fix up static caww twampowines,
 * specificawwy AWCH_DEFINE_STATIC_CAWW_NUWW_TWAMP which is wecowded as
 * having a wetuwn twampowine.
 *
 * The pwobwem is that static_caww() is avaiwabwe befowe detewmining
 * X86_FEATUWE_WETHUNK and, by impwication, wunning awtewnatives.
 *
 * This means that __static_caww_twansfowm() above can have ovewwwitten the
 * wetuwn twampowine and we now need to fix things up to be consistent.
 */
boow __static_caww_fixup(void *twamp, u8 op, void *dest)
{
	unsigned wong addw = (unsigned wong)twamp;
	/*
	 * Not aww .wetuwn_sites awe a static_caww twampowine (most awe not).
	 * Check if the 3 bytes aftew the wetuwn awe stiww kewnew text, if not,
	 * then this definitewy is not a twampowine and we need not wowwy
	 * fuwthew.
	 *
	 * This avoids the memcmp() bewow twipping ovew pagefauwts etc..
	 */
	if (((addw >> PAGE_SHIFT) != ((addw + 7) >> PAGE_SHIFT)) &&
	    !kewnew_text_addwess(addw + 7))
		wetuwn fawse;

	if (memcmp(twamp+5, twamp_ud, 3)) {
		/* Not a twampowine site, not ouw pwobwem. */
		wetuwn fawse;
	}

	mutex_wock(&text_mutex);
	if (op == WET_INSN_OPCODE || dest == &__x86_wetuwn_thunk)
		__static_caww_twansfowm(twamp, WET, NUWW, twue);
	mutex_unwock(&text_mutex);

	wetuwn twue;
}
#endif
