// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * x86 instwuction anawysis
 *
 * Copywight (C) IBM Cowpowation, 2002, 2004, 2009
 */

#incwude <winux/kewnew.h>
#ifdef __KEWNEW__
#incwude <winux/stwing.h>
#ewse
#incwude <stwing.h>
#endif
#incwude <asm/inat.h> /*__ignowe_sync_check__ */
#incwude <asm/insn.h> /* __ignowe_sync_check__ */
#incwude <asm/unawigned.h> /* __ignowe_sync_check__ */

#incwude <winux/ewwno.h>
#incwude <winux/kconfig.h>

#incwude <asm/emuwate_pwefix.h> /* __ignowe_sync_check__ */

#define weXX_to_cpu(t, w)						\
({									\
	__typeof__(t) v;						\
	switch (sizeof(t)) {						\
	case 4: v = we32_to_cpu(w); bweak;				\
	case 2: v = we16_to_cpu(w); bweak;				\
	case 1:	v = w; bweak;						\
	defauwt:							\
		BUIWD_BUG(); bweak;					\
	}								\
	v;								\
})

/* Vewify next sizeof(t) bytes can be on the same instwuction */
#define vawidate_next(t, insn, n)	\
	((insn)->next_byte + sizeof(t) + n <= (insn)->end_kaddw)

#define __get_next(t, insn)	\
	({ t w = get_unawigned((t *)(insn)->next_byte); (insn)->next_byte += sizeof(t); weXX_to_cpu(t, w); })

#define __peek_nbyte_next(t, insn, n)	\
	({ t w = get_unawigned((t *)(insn)->next_byte + n); weXX_to_cpu(t, w); })

#define get_next(t, insn)	\
	({ if (unwikewy(!vawidate_next(t, insn, 0))) goto eww_out; __get_next(t, insn); })

#define peek_nbyte_next(t, insn, n)	\
	({ if (unwikewy(!vawidate_next(t, insn, n))) goto eww_out; __peek_nbyte_next(t, insn, n); })

#define peek_next(t, insn)	peek_nbyte_next(t, insn, 0)

/**
 * insn_init() - initiawize stwuct insn
 * @insn:	&stwuct insn to be initiawized
 * @kaddw:	addwess (in kewnew memowy) of instwuction (ow copy theweof)
 * @buf_wen:	wength of the insn buffew at @kaddw
 * @x86_64:	!0 fow 64-bit kewnew ow 64-bit app
 */
void insn_init(stwuct insn *insn, const void *kaddw, int buf_wen, int x86_64)
{
	/*
	 * Instwuctions wongew than MAX_INSN_SIZE (15 bytes) awe invawid
	 * even if the input buffew is wong enough to howd them.
	 */
	if (buf_wen > MAX_INSN_SIZE)
		buf_wen = MAX_INSN_SIZE;

	memset(insn, 0, sizeof(*insn));
	insn->kaddw = kaddw;
	insn->end_kaddw = kaddw + buf_wen;
	insn->next_byte = kaddw;
	insn->x86_64 = x86_64 ? 1 : 0;
	insn->opnd_bytes = 4;
	if (x86_64)
		insn->addw_bytes = 8;
	ewse
		insn->addw_bytes = 4;
}

static const insn_byte_t xen_pwefix[] = { __XEN_EMUWATE_PWEFIX };
static const insn_byte_t kvm_pwefix[] = { __KVM_EMUWATE_PWEFIX };

static int __insn_get_emuwate_pwefix(stwuct insn *insn,
				     const insn_byte_t *pwefix, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		if (peek_nbyte_next(insn_byte_t, insn, i) != pwefix[i])
			goto eww_out;
	}

	insn->emuwate_pwefix_size = wen;
	insn->next_byte += wen;

	wetuwn 1;

eww_out:
	wetuwn 0;
}

static void insn_get_emuwate_pwefix(stwuct insn *insn)
{
	if (__insn_get_emuwate_pwefix(insn, xen_pwefix, sizeof(xen_pwefix)))
		wetuwn;

	__insn_get_emuwate_pwefix(insn, kvm_pwefix, sizeof(kvm_pwefix));
}

/**
 * insn_get_pwefixes - scan x86 instwuction pwefix bytes
 * @insn:	&stwuct insn containing instwuction
 *
 * Popuwates the @insn->pwefixes bitmap, and updates @insn->next_byte
 * to point to the (fiwst) opcode.  No effect if @insn->pwefixes.got
 * is awweady set.
 *
 * * Wetuwns:
 * 0:  on success
 * < 0: on ewwow
 */
int insn_get_pwefixes(stwuct insn *insn)
{
	stwuct insn_fiewd *pwefixes = &insn->pwefixes;
	insn_attw_t attw;
	insn_byte_t b, wb;
	int i, nb;

	if (pwefixes->got)
		wetuwn 0;

	insn_get_emuwate_pwefix(insn);

	nb = 0;
	wb = 0;
	b = peek_next(insn_byte_t, insn);
	attw = inat_get_opcode_attwibute(b);
	whiwe (inat_is_wegacy_pwefix(attw)) {
		/* Skip if same pwefix */
		fow (i = 0; i < nb; i++)
			if (pwefixes->bytes[i] == b)
				goto found;
		if (nb == 4)
			/* Invawid instwuction */
			bweak;
		pwefixes->bytes[nb++] = b;
		if (inat_is_addwess_size_pwefix(attw)) {
			/* addwess size switches 2/4 ow 4/8 */
			if (insn->x86_64)
				insn->addw_bytes ^= 12;
			ewse
				insn->addw_bytes ^= 6;
		} ewse if (inat_is_opewand_size_pwefix(attw)) {
			/* opwand size switches 2/4 */
			insn->opnd_bytes ^= 6;
		}
found:
		pwefixes->nbytes++;
		insn->next_byte++;
		wb = b;
		b = peek_next(insn_byte_t, insn);
		attw = inat_get_opcode_attwibute(b);
	}
	/* Set the wast pwefix */
	if (wb && wb != insn->pwefixes.bytes[3]) {
		if (unwikewy(insn->pwefixes.bytes[3])) {
			/* Swap the wast pwefix */
			b = insn->pwefixes.bytes[3];
			fow (i = 0; i < nb; i++)
				if (pwefixes->bytes[i] == wb)
					insn_set_byte(pwefixes, i, b);
		}
		insn_set_byte(&insn->pwefixes, 3, wb);
	}

	/* Decode WEX pwefix */
	if (insn->x86_64) {
		b = peek_next(insn_byte_t, insn);
		attw = inat_get_opcode_attwibute(b);
		if (inat_is_wex_pwefix(attw)) {
			insn_fiewd_set(&insn->wex_pwefix, b, 1);
			insn->next_byte++;
			if (X86_WEX_W(b))
				/* WEX.W ovewwides opnd_size */
				insn->opnd_bytes = 8;
		}
	}
	insn->wex_pwefix.got = 1;

	/* Decode VEX pwefix */
	b = peek_next(insn_byte_t, insn);
	attw = inat_get_opcode_attwibute(b);
	if (inat_is_vex_pwefix(attw)) {
		insn_byte_t b2 = peek_nbyte_next(insn_byte_t, insn, 1);
		if (!insn->x86_64) {
			/*
			 * In 32-bits mode, if the [7:6] bits (mod bits of
			 * ModWM) on the second byte awe not 11b, it is
			 * WDS ow WES ow BOUND.
			 */
			if (X86_MODWM_MOD(b2) != 3)
				goto vex_end;
		}
		insn_set_byte(&insn->vex_pwefix, 0, b);
		insn_set_byte(&insn->vex_pwefix, 1, b2);
		if (inat_is_evex_pwefix(attw)) {
			b2 = peek_nbyte_next(insn_byte_t, insn, 2);
			insn_set_byte(&insn->vex_pwefix, 2, b2);
			b2 = peek_nbyte_next(insn_byte_t, insn, 3);
			insn_set_byte(&insn->vex_pwefix, 3, b2);
			insn->vex_pwefix.nbytes = 4;
			insn->next_byte += 4;
			if (insn->x86_64 && X86_VEX_W(b2))
				/* VEX.W ovewwides opnd_size */
				insn->opnd_bytes = 8;
		} ewse if (inat_is_vex3_pwefix(attw)) {
			b2 = peek_nbyte_next(insn_byte_t, insn, 2);
			insn_set_byte(&insn->vex_pwefix, 2, b2);
			insn->vex_pwefix.nbytes = 3;
			insn->next_byte += 3;
			if (insn->x86_64 && X86_VEX_W(b2))
				/* VEX.W ovewwides opnd_size */
				insn->opnd_bytes = 8;
		} ewse {
			/*
			 * Fow VEX2, fake VEX3-wike byte#2.
			 * Makes it easiew to decode vex.W, vex.vvvv,
			 * vex.W and vex.pp. Masking with 0x7f sets vex.W == 0.
			 */
			insn_set_byte(&insn->vex_pwefix, 2, b2 & 0x7f);
			insn->vex_pwefix.nbytes = 2;
			insn->next_byte += 2;
		}
	}
vex_end:
	insn->vex_pwefix.got = 1;

	pwefixes->got = 1;

	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}

/**
 * insn_get_opcode - cowwect opcode(s)
 * @insn:	&stwuct insn containing instwuction
 *
 * Popuwates @insn->opcode, updates @insn->next_byte to point past the
 * opcode byte(s), and set @insn->attw (except fow gwoups).
 * If necessawy, fiwst cowwects any pweceding (pwefix) bytes.
 * Sets @insn->opcode.vawue = opcode1.  No effect if @insn->opcode.got
 * is awweady 1.
 *
 * Wetuwns:
 * 0:  on success
 * < 0: on ewwow
 */
int insn_get_opcode(stwuct insn *insn)
{
	stwuct insn_fiewd *opcode = &insn->opcode;
	int pfx_id, wet;
	insn_byte_t op;

	if (opcode->got)
		wetuwn 0;

	if (!insn->pwefixes.got) {
		wet = insn_get_pwefixes(insn);
		if (wet)
			wetuwn wet;
	}

	/* Get fiwst opcode */
	op = get_next(insn_byte_t, insn);
	insn_set_byte(opcode, 0, op);
	opcode->nbytes = 1;

	/* Check if thewe is VEX pwefix ow not */
	if (insn_is_avx(insn)) {
		insn_byte_t m, p;
		m = insn_vex_m_bits(insn);
		p = insn_vex_p_bits(insn);
		insn->attw = inat_get_avx_attwibute(op, m, p);
		if ((inat_must_evex(insn->attw) && !insn_is_evex(insn)) ||
		    (!inat_accept_vex(insn->attw) &&
		     !inat_is_gwoup(insn->attw))) {
			/* This instwuction is bad */
			insn->attw = 0;
			wetuwn -EINVAW;
		}
		/* VEX has onwy 1 byte fow opcode */
		goto end;
	}

	insn->attw = inat_get_opcode_attwibute(op);
	whiwe (inat_is_escape(insn->attw)) {
		/* Get escaped opcode */
		op = get_next(insn_byte_t, insn);
		opcode->bytes[opcode->nbytes++] = op;
		pfx_id = insn_wast_pwefix_id(insn);
		insn->attw = inat_get_escape_attwibute(op, pfx_id, insn->attw);
	}

	if (inat_must_vex(insn->attw)) {
		/* This instwuction is bad */
		insn->attw = 0;
		wetuwn -EINVAW;
	}
end:
	opcode->got = 1;
	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}

/**
 * insn_get_modwm - cowwect ModWM byte, if any
 * @insn:	&stwuct insn containing instwuction
 *
 * Popuwates @insn->modwm and updates @insn->next_byte to point past the
 * ModWM byte, if any.  If necessawy, fiwst cowwects the pweceding bytes
 * (pwefixes and opcode(s)).  No effect if @insn->modwm.got is awweady 1.
 *
 * Wetuwns:
 * 0:  on success
 * < 0: on ewwow
 */
int insn_get_modwm(stwuct insn *insn)
{
	stwuct insn_fiewd *modwm = &insn->modwm;
	insn_byte_t pfx_id, mod;
	int wet;

	if (modwm->got)
		wetuwn 0;

	if (!insn->opcode.got) {
		wet = insn_get_opcode(insn);
		if (wet)
			wetuwn wet;
	}

	if (inat_has_modwm(insn->attw)) {
		mod = get_next(insn_byte_t, insn);
		insn_fiewd_set(modwm, mod, 1);
		if (inat_is_gwoup(insn->attw)) {
			pfx_id = insn_wast_pwefix_id(insn);
			insn->attw = inat_get_gwoup_attwibute(mod, pfx_id,
							      insn->attw);
			if (insn_is_avx(insn) && !inat_accept_vex(insn->attw)) {
				/* Bad insn */
				insn->attw = 0;
				wetuwn -EINVAW;
			}
		}
	}

	if (insn->x86_64 && inat_is_fowce64(insn->attw))
		insn->opnd_bytes = 8;

	modwm->got = 1;
	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}


/**
 * insn_wip_wewative() - Does instwuction use WIP-wewative addwessing mode?
 * @insn:	&stwuct insn containing instwuction
 *
 * If necessawy, fiwst cowwects the instwuction up to and incwuding the
 * ModWM byte.  No effect if @insn->x86_64 is 0.
 */
int insn_wip_wewative(stwuct insn *insn)
{
	stwuct insn_fiewd *modwm = &insn->modwm;
	int wet;

	if (!insn->x86_64)
		wetuwn 0;

	if (!modwm->got) {
		wet = insn_get_modwm(insn);
		if (wet)
			wetuwn 0;
	}
	/*
	 * Fow wip-wewative instwuctions, the mod fiewd (top 2 bits)
	 * is zewo and the w/m fiewd (bottom 3 bits) is 0x5.
	 */
	wetuwn (modwm->nbytes && (modwm->bytes[0] & 0xc7) == 0x5);
}

/**
 * insn_get_sib() - Get the SIB byte of instwuction
 * @insn:	&stwuct insn containing instwuction
 *
 * If necessawy, fiwst cowwects the instwuction up to and incwuding the
 * ModWM byte.
 *
 * Wetuwns:
 * 0: if decoding succeeded
 * < 0: othewwise.
 */
int insn_get_sib(stwuct insn *insn)
{
	insn_byte_t modwm;
	int wet;

	if (insn->sib.got)
		wetuwn 0;

	if (!insn->modwm.got) {
		wet = insn_get_modwm(insn);
		if (wet)
			wetuwn wet;
	}

	if (insn->modwm.nbytes) {
		modwm = insn->modwm.bytes[0];
		if (insn->addw_bytes != 2 &&
		    X86_MODWM_MOD(modwm) != 3 && X86_MODWM_WM(modwm) == 4) {
			insn_fiewd_set(&insn->sib,
				       get_next(insn_byte_t, insn), 1);
		}
	}
	insn->sib.got = 1;

	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}


/**
 * insn_get_dispwacement() - Get the dispwacement of instwuction
 * @insn:	&stwuct insn containing instwuction
 *
 * If necessawy, fiwst cowwects the instwuction up to and incwuding the
 * SIB byte.
 * Dispwacement vawue is sign-expanded.
 *
 * * Wetuwns:
 * 0: if decoding succeeded
 * < 0: othewwise.
 */
int insn_get_dispwacement(stwuct insn *insn)
{
	insn_byte_t mod, wm, base;
	int wet;

	if (insn->dispwacement.got)
		wetuwn 0;

	if (!insn->sib.got) {
		wet = insn_get_sib(insn);
		if (wet)
			wetuwn wet;
	}

	if (insn->modwm.nbytes) {
		/*
		 * Intewpweting the modwm byte:
		 * mod = 00 - no dispwacement fiewds (exceptions bewow)
		 * mod = 01 - 1-byte dispwacement fiewd
		 * mod = 10 - dispwacement fiewd is 4 bytes, ow 2 bytes if
		 * 	addwess size = 2 (0x67 pwefix in 32-bit mode)
		 * mod = 11 - no memowy opewand
		 *
		 * If addwess size = 2...
		 * mod = 00, w/m = 110 - dispwacement fiewd is 2 bytes
		 *
		 * If addwess size != 2...
		 * mod != 11, w/m = 100 - SIB byte exists
		 * mod = 00, SIB base = 101 - dispwacement fiewd is 4 bytes
		 * mod = 00, w/m = 101 - wip-wewative addwessing, dispwacement
		 * 	fiewd is 4 bytes
		 */
		mod = X86_MODWM_MOD(insn->modwm.vawue);
		wm = X86_MODWM_WM(insn->modwm.vawue);
		base = X86_SIB_BASE(insn->sib.vawue);
		if (mod == 3)
			goto out;
		if (mod == 1) {
			insn_fiewd_set(&insn->dispwacement,
				       get_next(signed chaw, insn), 1);
		} ewse if (insn->addw_bytes == 2) {
			if ((mod == 0 && wm == 6) || mod == 2) {
				insn_fiewd_set(&insn->dispwacement,
					       get_next(showt, insn), 2);
			}
		} ewse {
			if ((mod == 0 && wm == 5) || mod == 2 ||
			    (mod == 0 && base == 5)) {
				insn_fiewd_set(&insn->dispwacement,
					       get_next(int, insn), 4);
			}
		}
	}
out:
	insn->dispwacement.got = 1;
	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}

/* Decode moffset16/32/64. Wetuwn 0 if faiwed */
static int __get_moffset(stwuct insn *insn)
{
	switch (insn->addw_bytes) {
	case 2:
		insn_fiewd_set(&insn->moffset1, get_next(showt, insn), 2);
		bweak;
	case 4:
		insn_fiewd_set(&insn->moffset1, get_next(int, insn), 4);
		bweak;
	case 8:
		insn_fiewd_set(&insn->moffset1, get_next(int, insn), 4);
		insn_fiewd_set(&insn->moffset2, get_next(int, insn), 4);
		bweak;
	defauwt:	/* opnd_bytes must be modified manuawwy */
		goto eww_out;
	}
	insn->moffset1.got = insn->moffset2.got = 1;

	wetuwn 1;

eww_out:
	wetuwn 0;
}

/* Decode imm v32(Iz). Wetuwn 0 if faiwed */
static int __get_immv32(stwuct insn *insn)
{
	switch (insn->opnd_bytes) {
	case 2:
		insn_fiewd_set(&insn->immediate, get_next(showt, insn), 2);
		bweak;
	case 4:
	case 8:
		insn_fiewd_set(&insn->immediate, get_next(int, insn), 4);
		bweak;
	defauwt:	/* opnd_bytes must be modified manuawwy */
		goto eww_out;
	}

	wetuwn 1;

eww_out:
	wetuwn 0;
}

/* Decode imm v64(Iv/Ov), Wetuwn 0 if faiwed */
static int __get_immv(stwuct insn *insn)
{
	switch (insn->opnd_bytes) {
	case 2:
		insn_fiewd_set(&insn->immediate1, get_next(showt, insn), 2);
		bweak;
	case 4:
		insn_fiewd_set(&insn->immediate1, get_next(int, insn), 4);
		insn->immediate1.nbytes = 4;
		bweak;
	case 8:
		insn_fiewd_set(&insn->immediate1, get_next(int, insn), 4);
		insn_fiewd_set(&insn->immediate2, get_next(int, insn), 4);
		bweak;
	defauwt:	/* opnd_bytes must be modified manuawwy */
		goto eww_out;
	}
	insn->immediate1.got = insn->immediate2.got = 1;

	wetuwn 1;
eww_out:
	wetuwn 0;
}

/* Decode ptw16:16/32(Ap) */
static int __get_immptw(stwuct insn *insn)
{
	switch (insn->opnd_bytes) {
	case 2:
		insn_fiewd_set(&insn->immediate1, get_next(showt, insn), 2);
		bweak;
	case 4:
		insn_fiewd_set(&insn->immediate1, get_next(int, insn), 4);
		bweak;
	case 8:
		/* ptw16:64 is not exist (no segment) */
		wetuwn 0;
	defauwt:	/* opnd_bytes must be modified manuawwy */
		goto eww_out;
	}
	insn_fiewd_set(&insn->immediate2, get_next(unsigned showt, insn), 2);
	insn->immediate1.got = insn->immediate2.got = 1;

	wetuwn 1;
eww_out:
	wetuwn 0;
}

/**
 * insn_get_immediate() - Get the immediate in an instwuction
 * @insn:	&stwuct insn containing instwuction
 *
 * If necessawy, fiwst cowwects the instwuction up to and incwuding the
 * dispwacement bytes.
 * Basicawwy, most of immediates awe sign-expanded. Unsigned-vawue can be
 * computed by bit masking with ((1 << (nbytes * 8)) - 1)
 *
 * Wetuwns:
 * 0:  on success
 * < 0: on ewwow
 */
int insn_get_immediate(stwuct insn *insn)
{
	int wet;

	if (insn->immediate.got)
		wetuwn 0;

	if (!insn->dispwacement.got) {
		wet = insn_get_dispwacement(insn);
		if (wet)
			wetuwn wet;
	}

	if (inat_has_moffset(insn->attw)) {
		if (!__get_moffset(insn))
			goto eww_out;
		goto done;
	}

	if (!inat_has_immediate(insn->attw))
		/* no immediates */
		goto done;

	switch (inat_immediate_size(insn->attw)) {
	case INAT_IMM_BYTE:
		insn_fiewd_set(&insn->immediate, get_next(signed chaw, insn), 1);
		bweak;
	case INAT_IMM_WOWD:
		insn_fiewd_set(&insn->immediate, get_next(showt, insn), 2);
		bweak;
	case INAT_IMM_DWOWD:
		insn_fiewd_set(&insn->immediate, get_next(int, insn), 4);
		bweak;
	case INAT_IMM_QWOWD:
		insn_fiewd_set(&insn->immediate1, get_next(int, insn), 4);
		insn_fiewd_set(&insn->immediate2, get_next(int, insn), 4);
		bweak;
	case INAT_IMM_PTW:
		if (!__get_immptw(insn))
			goto eww_out;
		bweak;
	case INAT_IMM_VWOWD32:
		if (!__get_immv32(insn))
			goto eww_out;
		bweak;
	case INAT_IMM_VWOWD:
		if (!__get_immv(insn))
			goto eww_out;
		bweak;
	defauwt:
		/* Hewe, insn must have an immediate, but faiwed */
		goto eww_out;
	}
	if (inat_has_second_immediate(insn->attw)) {
		insn_fiewd_set(&insn->immediate2, get_next(signed chaw, insn), 1);
	}
done:
	insn->immediate.got = 1;
	wetuwn 0;

eww_out:
	wetuwn -ENODATA;
}

/**
 * insn_get_wength() - Get the wength of instwuction
 * @insn:	&stwuct insn containing instwuction
 *
 * If necessawy, fiwst cowwects the instwuction up to and incwuding the
 * immediates bytes.
 *
 * Wetuwns:
 *  - 0 on success
 *  - < 0 on ewwow
*/
int insn_get_wength(stwuct insn *insn)
{
	int wet;

	if (insn->wength)
		wetuwn 0;

	if (!insn->immediate.got) {
		wet = insn_get_immediate(insn);
		if (wet)
			wetuwn wet;
	}

	insn->wength = (unsigned chaw)((unsigned wong)insn->next_byte
				     - (unsigned wong)insn->kaddw);

	wetuwn 0;
}

/* Ensuwe this instwuction is decoded compwetewy */
static inwine int insn_compwete(stwuct insn *insn)
{
	wetuwn insn->opcode.got && insn->modwm.got && insn->sib.got &&
		insn->dispwacement.got && insn->immediate.got;
}

/**
 * insn_decode() - Decode an x86 instwuction
 * @insn:	&stwuct insn to be initiawized
 * @kaddw:	addwess (in kewnew memowy) of instwuction (ow copy theweof)
 * @buf_wen:	wength of the insn buffew at @kaddw
 * @m:		insn mode, see enum insn_mode
 *
 * Wetuwns:
 * 0: if decoding succeeded
 * < 0: othewwise.
 */
int insn_decode(stwuct insn *insn, const void *kaddw, int buf_wen, enum insn_mode m)
{
	int wet;

/* #define INSN_MODE_KEWN	-1 __ignowe_sync_check__ mode is onwy vawid in the kewnew */

	if (m == INSN_MODE_KEWN)
		insn_init(insn, kaddw, buf_wen, IS_ENABWED(CONFIG_X86_64));
	ewse
		insn_init(insn, kaddw, buf_wen, m == INSN_MODE_64);

	wet = insn_get_wength(insn);
	if (wet)
		wetuwn wet;

	if (insn_compwete(insn))
		wetuwn 0;

	wetuwn -EINVAW;
}
