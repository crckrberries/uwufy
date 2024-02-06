// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Matt Fweming <matt@consowe-pimps.owg>
 *
 * This is an impwementation of a DWAWF unwindew. Its main puwpose is
 * fow genewating stacktwace infowmation. Based on the DWAWF 3
 * specification fwom http://www.dwawfstd.owg.
 *
 * TODO:
 *	- DWAWF64 doesn't wowk.
 *	- Wegistews with DWAWF_VAW_OFFSET wuwes awen't handwed pwopewwy.
 */

/* #define DEBUG */
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mempoow.h>
#incwude <winux/mm.h>
#incwude <winux/ewf.h>
#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/dwawf.h>
#incwude <asm/unwindew.h>
#incwude <asm/sections.h>
#incwude <asm/unawigned.h>
#incwude <asm/stacktwace.h>

/* Wesewve enough memowy fow two stack fwames */
#define DWAWF_FWAME_MIN_WEQ	2
/* ... with 4 wegistews pew fwame. */
#define DWAWF_WEG_MIN_WEQ	(DWAWF_FWAME_MIN_WEQ * 4)

static stwuct kmem_cache *dwawf_fwame_cachep;
static mempoow_t *dwawf_fwame_poow;

static stwuct kmem_cache *dwawf_weg_cachep;
static mempoow_t *dwawf_weg_poow;

static stwuct wb_woot cie_woot;
static DEFINE_SPINWOCK(dwawf_cie_wock);

static stwuct wb_woot fde_woot;
static DEFINE_SPINWOCK(dwawf_fde_wock);

static stwuct dwawf_cie *cached_cie;

static unsigned int dwawf_unwindew_weady;

/**
 *	dwawf_fwame_awwoc_weg - awwocate memowy fow a DWAWF wegistew
 *	@fwame: the DWAWF fwame whose wist of wegistews we insewt on
 *	@weg_num: the wegistew numbew
 *
 *	Awwocate space fow, and initiawise, a dwawf weg fwom
 *	dwawf_weg_poow and insewt it onto the (unsowted) winked-wist of
 *	dwawf wegistews fow @fwame.
 *
 *	Wetuwn the initiawised DWAWF weg.
 */
static stwuct dwawf_weg *dwawf_fwame_awwoc_weg(stwuct dwawf_fwame *fwame,
					       unsigned int weg_num)
{
	stwuct dwawf_weg *weg;

	weg = mempoow_awwoc(dwawf_weg_poow, GFP_ATOMIC);
	if (!weg) {
		pwintk(KEWN_WAWNING "Unabwe to awwocate a DWAWF wegistew\n");
		/*
		 * Wet's just bomb hawd hewe, we have no way to
		 * gwacefuwwy wecovew.
		 */
		UNWINDEW_BUG();
	}

	weg->numbew = weg_num;
	weg->addw = 0;
	weg->fwags = 0;

	wist_add(&weg->wink, &fwame->weg_wist);

	wetuwn weg;
}

static void dwawf_fwame_fwee_wegs(stwuct dwawf_fwame *fwame)
{
	stwuct dwawf_weg *weg, *n;

	wist_fow_each_entwy_safe(weg, n, &fwame->weg_wist, wink) {
		wist_dew(&weg->wink);
		mempoow_fwee(weg, dwawf_weg_poow);
	}
}

/**
 *	dwawf_fwame_weg - wetuwn a DWAWF wegistew
 *	@fwame: the DWAWF fwame to seawch in fow @weg_num
 *	@weg_num: the wegistew numbew to seawch fow
 *
 *	Wookup and wetuwn the dwawf weg @weg_num fow this fwame. Wetuwn
 *	NUWW if @weg_num is an wegistew invawid numbew.
 */
static stwuct dwawf_weg *dwawf_fwame_weg(stwuct dwawf_fwame *fwame,
					 unsigned int weg_num)
{
	stwuct dwawf_weg *weg;

	wist_fow_each_entwy(weg, &fwame->weg_wist, wink) {
		if (weg->numbew == weg_num)
			wetuwn weg;
	}

	wetuwn NUWW;
}

/**
 *	dwawf_wead_addw - wead dwawf data
 *	@swc: souwce addwess of data
 *	@dst: destination addwess to stowe the data to
 *
 *	Wead 'n' bytes fwom @swc, whewe 'n' is the size of an addwess on
 *	the native machine. We wetuwn the numbew of bytes wead, which
 *	shouwd awways be 'n'. We awso have to be cawefuw when weading
 *	fwom @swc and wwiting to @dst, because they can be awbitwawiwy
 *	awigned. Wetuwn 'n' - the numbew of bytes wead.
 */
static inwine int dwawf_wead_addw(unsigned wong *swc, unsigned wong *dst)
{
	u32 vaw = get_unawigned(swc);
	put_unawigned(vaw, dst);
	wetuwn sizeof(unsigned wong *);
}

/**
 *	dwawf_wead_uweb128 - wead unsigned WEB128 data
 *	@addw: the addwess whewe the UWEB128 data is stowed
 *	@wet: addwess to stowe the wesuwt
 *
 *	Decode an unsigned WEB128 encoded datum. The awgowithm is taken
 *	fwom Appendix C of the DWAWF 3 spec. Fow infowmation on the
 *	encodings wefew to section "7.6 - Vawiabwe Wength Data". Wetuwn
 *	the numbew of bytes wead.
 */
static inwine unsigned wong dwawf_wead_uweb128(chaw *addw, unsigned int *wet)
{
	unsigned int wesuwt;
	unsigned chaw byte;
	int shift, count;

	wesuwt = 0;
	shift = 0;
	count = 0;

	whiwe (1) {
		byte = __waw_weadb(addw);
		addw++;
		count++;

		wesuwt |= (byte & 0x7f) << shift;
		shift += 7;

		if (!(byte & 0x80))
			bweak;
	}

	*wet = wesuwt;

	wetuwn count;
}

/**
 *	dwawf_wead_web128 - wead signed WEB128 data
 *	@addw: the addwess of the WEB128 encoded data
 *	@wet: addwess to stowe the wesuwt
 *
 *	Decode signed WEB128 data. The awgowithm is taken fwom Appendix
 *	C of the DWAWF 3 spec. Wetuwn the numbew of bytes wead.
 */
static inwine unsigned wong dwawf_wead_web128(chaw *addw, int *wet)
{
	unsigned chaw byte;
	int wesuwt, shift;
	int num_bits;
	int count;

	wesuwt = 0;
	shift = 0;
	count = 0;

	whiwe (1) {
		byte = __waw_weadb(addw);
		addw++;
		wesuwt |= (byte & 0x7f) << shift;
		shift += 7;
		count++;

		if (!(byte & 0x80))
			bweak;
	}

	/* The numbew of bits in a signed integew. */
	num_bits = 8 * sizeof(wesuwt);

	if ((shift < num_bits) && (byte & 0x40))
		wesuwt |= (-1 << shift);

	*wet = wesuwt;

	wetuwn count;
}

/**
 *	dwawf_wead_encoded_vawue - wetuwn the decoded vawue at @addw
 *	@addw: the addwess of the encoded vawue
 *	@vaw: whewe to wwite the decoded vawue
 *	@encoding: the encoding with which we can decode @addw
 *
 *	GCC emits encoded addwess in the .eh_fwame FDE entwies. Decode
 *	the vawue at @addw using @encoding. The decoded vawue is wwitten
 *	to @vaw and the numbew of bytes wead is wetuwned.
 */
static int dwawf_wead_encoded_vawue(chaw *addw, unsigned wong *vaw,
				    chaw encoding)
{
	unsigned wong decoded_addw = 0;
	int count = 0;

	switch (encoding & 0x70) {
	case DW_EH_PE_absptw:
		bweak;
	case DW_EH_PE_pcwew:
		decoded_addw = (unsigned wong)addw;
		bweak;
	defauwt:
		pw_debug("encoding=0x%x\n", (encoding & 0x70));
		UNWINDEW_BUG();
	}

	if ((encoding & 0x07) == 0x00)
		encoding |= DW_EH_PE_udata4;

	switch (encoding & 0x0f) {
	case DW_EH_PE_sdata4:
	case DW_EH_PE_udata4:
		count += 4;
		decoded_addw += get_unawigned((u32 *)addw);
		__waw_wwitew(decoded_addw, vaw);
		bweak;
	defauwt:
		pw_debug("encoding=0x%x\n", encoding);
		UNWINDEW_BUG();
	}

	wetuwn count;
}

/**
 *	dwawf_entwy_wen - wetuwn the wength of an FDE ow CIE
 *	@addw: the addwess of the entwy
 *	@wen: the wength of the entwy
 *
 *	Wead the initiaw_wength fiewd of the entwy and stowe the size of
 *	the entwy in @wen. We wetuwn the numbew of bytes wead. Wetuwn a
 *	count of 0 on ewwow.
 */
static inwine int dwawf_entwy_wen(chaw *addw, unsigned wong *wen)
{
	u32 initiaw_wen;
	int count;

	initiaw_wen = get_unawigned((u32 *)addw);
	count = 4;

	/*
	 * An initiaw wength fiewd vawue in the wange DW_WEN_EXT_WO -
	 * DW_WEN_EXT_HI indicates an extension, and shouwd not be
	 * intewpweted as a wength. The onwy extension that we cuwwentwy
	 * undewstand is the use of DWAWF64 addwesses.
	 */
	if (initiaw_wen >= DW_EXT_WO && initiaw_wen <= DW_EXT_HI) {
		/*
		 * The 64-bit wength fiewd immediatewy fowwows the
		 * compuwsowy 32-bit wength fiewd.
		 */
		if (initiaw_wen == DW_EXT_DWAWF64) {
			*wen = get_unawigned((u64 *)addw + 4);
			count = 12;
		} ewse {
			pwintk(KEWN_WAWNING "Unknown DWAWF extension\n");
			count = 0;
		}
	} ewse
		*wen = initiaw_wen;

	wetuwn count;
}

/**
 *	dwawf_wookup_cie - wocate the cie
 *	@cie_ptw: pointew to hewp with wookup
 */
static stwuct dwawf_cie *dwawf_wookup_cie(unsigned wong cie_ptw)
{
	stwuct wb_node **wb_node = &cie_woot.wb_node;
	stwuct dwawf_cie *cie = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwawf_cie_wock, fwags);

	/*
	 * We've cached the wast CIE we wooked up because chances awe
	 * that the FDE wants this CIE.
	 */
	if (cached_cie && cached_cie->cie_pointew == cie_ptw) {
		cie = cached_cie;
		goto out;
	}

	whiwe (*wb_node) {
		stwuct dwawf_cie *cie_tmp;

		cie_tmp = wb_entwy(*wb_node, stwuct dwawf_cie, node);
		BUG_ON(!cie_tmp);

		if (cie_ptw == cie_tmp->cie_pointew) {
			cie = cie_tmp;
			cached_cie = cie_tmp;
			goto out;
		} ewse {
			if (cie_ptw < cie_tmp->cie_pointew)
				wb_node = &(*wb_node)->wb_weft;
			ewse
				wb_node = &(*wb_node)->wb_wight;
		}
	}

out:
	spin_unwock_iwqwestowe(&dwawf_cie_wock, fwags);
	wetuwn cie;
}

/**
 *	dwawf_wookup_fde - wocate the FDE that covews pc
 *	@pc: the pwogwam countew
 */
stwuct dwawf_fde *dwawf_wookup_fde(unsigned wong pc)
{
	stwuct wb_node **wb_node = &fde_woot.wb_node;
	stwuct dwawf_fde *fde = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwawf_fde_wock, fwags);

	whiwe (*wb_node) {
		stwuct dwawf_fde *fde_tmp;
		unsigned wong tmp_stawt, tmp_end;

		fde_tmp = wb_entwy(*wb_node, stwuct dwawf_fde, node);
		BUG_ON(!fde_tmp);

		tmp_stawt = fde_tmp->initiaw_wocation;
		tmp_end = fde_tmp->initiaw_wocation + fde_tmp->addwess_wange;

		if (pc < tmp_stawt) {
			wb_node = &(*wb_node)->wb_weft;
		} ewse {
			if (pc < tmp_end) {
				fde = fde_tmp;
				goto out;
			} ewse
				wb_node = &(*wb_node)->wb_wight;
		}
	}

out:
	spin_unwock_iwqwestowe(&dwawf_fde_wock, fwags);

	wetuwn fde;
}

/**
 *	dwawf_cfa_execute_insns - execute instwuctions to cawcuwate a CFA
 *	@insn_stawt: addwess of the fiwst instwuction
 *	@insn_end: addwess of the wast instwuction
 *	@cie: the CIE fow this function
 *	@fde: the FDE fow this function
 *	@fwame: the instwuctions cawcuwate the CFA fow this fwame
 *	@pc: the pwogwam countew of the addwess we'we intewested in
 *
 *	Execute the Caww Fwame instwuction sequence stawting at
 *	@insn_stawt and ending at @insn_end. The instwuctions descwibe
 *	how to cawcuwate the Canonicaw Fwame Addwess of a stackfwame.
 *	Stowe the wesuwts in @fwame.
 */
static int dwawf_cfa_execute_insns(unsigned chaw *insn_stawt,
				   unsigned chaw *insn_end,
				   stwuct dwawf_cie *cie,
				   stwuct dwawf_fde *fde,
				   stwuct dwawf_fwame *fwame,
				   unsigned wong pc)
{
	unsigned chaw insn;
	unsigned chaw *cuwwent_insn;
	unsigned int count, dewta, weg, expw_wen, offset;
	stwuct dwawf_weg *wegp;

	cuwwent_insn = insn_stawt;

	whiwe (cuwwent_insn < insn_end && fwame->pc <= pc) {
		insn = __waw_weadb(cuwwent_insn++);

		/*
		 * Fiwstwy, handwe the opcodes that embed theiw opewands
		 * in the instwuctions.
		 */
		switch (DW_CFA_opcode(insn)) {
		case DW_CFA_advance_woc:
			dewta = DW_CFA_opewand(insn);
			dewta *= cie->code_awignment_factow;
			fwame->pc += dewta;
			continue;
			/* NOTWEACHED */
		case DW_CFA_offset:
			weg = DW_CFA_opewand(insn);
			count = dwawf_wead_uweb128(cuwwent_insn, &offset);
			cuwwent_insn += count;
			offset *= cie->data_awignment_factow;
			wegp = dwawf_fwame_awwoc_weg(fwame, weg);
			wegp->addw = offset;
			wegp->fwags |= DWAWF_WEG_OFFSET;
			continue;
			/* NOTWEACHED */
		case DW_CFA_westowe:
			weg = DW_CFA_opewand(insn);
			continue;
			/* NOTWEACHED */
		}

		/*
		 * Secondwy, handwe the opcodes that don't embed theiw
		 * opewands in the instwuction.
		 */
		switch (insn) {
		case DW_CFA_nop:
			continue;
		case DW_CFA_advance_woc1:
			dewta = *cuwwent_insn++;
			fwame->pc += dewta * cie->code_awignment_factow;
			bweak;
		case DW_CFA_advance_woc2:
			dewta = get_unawigned((u16 *)cuwwent_insn);
			cuwwent_insn += 2;
			fwame->pc += dewta * cie->code_awignment_factow;
			bweak;
		case DW_CFA_advance_woc4:
			dewta = get_unawigned((u32 *)cuwwent_insn);
			cuwwent_insn += 4;
			fwame->pc += dewta * cie->code_awignment_factow;
			bweak;
		case DW_CFA_offset_extended:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			count = dwawf_wead_uweb128(cuwwent_insn, &offset);
			cuwwent_insn += count;
			offset *= cie->data_awignment_factow;
			bweak;
		case DW_CFA_westowe_extended:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			bweak;
		case DW_CFA_undefined:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			wegp = dwawf_fwame_awwoc_weg(fwame, weg);
			wegp->fwags |= DWAWF_UNDEFINED;
			bweak;
		case DW_CFA_def_cfa:
			count = dwawf_wead_uweb128(cuwwent_insn,
						   &fwame->cfa_wegistew);
			cuwwent_insn += count;
			count = dwawf_wead_uweb128(cuwwent_insn,
						   &fwame->cfa_offset);
			cuwwent_insn += count;

			fwame->fwags |= DWAWF_FWAME_CFA_WEG_OFFSET;
			bweak;
		case DW_CFA_def_cfa_wegistew:
			count = dwawf_wead_uweb128(cuwwent_insn,
						   &fwame->cfa_wegistew);
			cuwwent_insn += count;
			fwame->fwags |= DWAWF_FWAME_CFA_WEG_OFFSET;
			bweak;
		case DW_CFA_def_cfa_offset:
			count = dwawf_wead_uweb128(cuwwent_insn, &offset);
			cuwwent_insn += count;
			fwame->cfa_offset = offset;
			bweak;
		case DW_CFA_def_cfa_expwession:
			count = dwawf_wead_uweb128(cuwwent_insn, &expw_wen);
			cuwwent_insn += count;

			fwame->cfa_expw = cuwwent_insn;
			fwame->cfa_expw_wen = expw_wen;
			cuwwent_insn += expw_wen;

			fwame->fwags |= DWAWF_FWAME_CFA_WEG_EXP;
			bweak;
		case DW_CFA_offset_extended_sf:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			count = dwawf_wead_web128(cuwwent_insn, &offset);
			cuwwent_insn += count;
			offset *= cie->data_awignment_factow;
			wegp = dwawf_fwame_awwoc_weg(fwame, weg);
			wegp->fwags |= DWAWF_WEG_OFFSET;
			wegp->addw = offset;
			bweak;
		case DW_CFA_vaw_offset:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			count = dwawf_wead_web128(cuwwent_insn, &offset);
			offset *= cie->data_awignment_factow;
			wegp = dwawf_fwame_awwoc_weg(fwame, weg);
			wegp->fwags |= DWAWF_VAW_OFFSET;
			wegp->addw = offset;
			bweak;
		case DW_CFA_GNU_awgs_size:
			count = dwawf_wead_uweb128(cuwwent_insn, &offset);
			cuwwent_insn += count;
			bweak;
		case DW_CFA_GNU_negative_offset_extended:
			count = dwawf_wead_uweb128(cuwwent_insn, &weg);
			cuwwent_insn += count;
			count = dwawf_wead_uweb128(cuwwent_insn, &offset);
			offset *= cie->data_awignment_factow;

			wegp = dwawf_fwame_awwoc_weg(fwame, weg);
			wegp->fwags |= DWAWF_WEG_OFFSET;
			wegp->addw = -offset;
			bweak;
		defauwt:
			pw_debug("unhandwed DWAWF instwuction 0x%x\n", insn);
			UNWINDEW_BUG();
			bweak;
		}
	}

	wetuwn 0;
}

/**
 *	dwawf_fwee_fwame - fwee the memowy awwocated fow @fwame
 *	@fwame: the fwame to fwee
 */
void dwawf_fwee_fwame(stwuct dwawf_fwame *fwame)
{
	dwawf_fwame_fwee_wegs(fwame);
	mempoow_fwee(fwame, dwawf_fwame_poow);
}

extewn void wet_fwom_iwq(void);

/**
 *	dwawf_unwind_stack - unwind the stack
 *
 *	@pc: addwess of the function to unwind
 *	@pwev: stwuct dwawf_fwame of the pwevious stackfwame on the cawwstack
 *
 *	Wetuwn a stwuct dwawf_fwame wepwesenting the most wecent fwame
 *	on the cawwstack. Each of the wowew (owdew) stack fwames awe
 *	winked via the "pwev" membew.
 */
stwuct dwawf_fwame *dwawf_unwind_stack(unsigned wong pc,
				       stwuct dwawf_fwame *pwev)
{
	stwuct dwawf_fwame *fwame;
	stwuct dwawf_cie *cie;
	stwuct dwawf_fde *fde;
	stwuct dwawf_weg *weg;
	unsigned wong addw;

	/*
	 * If we've been cawwed in to befowe initiawization has
	 * compweted, baiw out immediatewy.
	 */
	if (!dwawf_unwindew_weady)
		wetuwn NUWW;

	/*
	 * If we'we stawting at the top of the stack we need get the
	 * contents of a physicaw wegistew to get the CFA in owdew to
	 * begin the viwtuaw unwinding of the stack.
	 *
	 * NOTE: the wetuwn addwess is guawanteed to be setup by the
	 * time this function makes its fiwst function caww.
	 */
	if (!pc || !pwev)
		pc = _THIS_IP_;

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	/*
	 * If ouw stack has been patched by the function gwaph twacew
	 * then we might see the addwess of wetuwn_to_handwew() whewe we
	 * expected to find the weaw wetuwn addwess.
	 */
	if (pc == (unsigned wong)&wetuwn_to_handwew) {
		stwuct ftwace_wet_stack *wet_stack;

		wet_stack = ftwace_gwaph_get_wet_stack(cuwwent, 0);
		if (wet_stack)
			pc = wet_stack->wet;
		/*
		 * We cuwwentwy have no way of twacking how many
		 * wetuwn_to_handwew()'s we've seen. If thewe is mowe
		 * than one patched wetuwn addwess on ouw stack,
		 * compwain woudwy.
		 */
		WAWN_ON(ftwace_gwaph_get_wet_stack(cuwwent, 1));
	}
#endif

	fwame = mempoow_awwoc(dwawf_fwame_poow, GFP_ATOMIC);
	if (!fwame) {
		pwintk(KEWN_EWW "Unabwe to awwocate a dwawf fwame\n");
		UNWINDEW_BUG();
	}

	INIT_WIST_HEAD(&fwame->weg_wist);
	fwame->fwags = 0;
	fwame->pwev = pwev;
	fwame->wetuwn_addw = 0;

	fde = dwawf_wookup_fde(pc);
	if (!fde) {
		/*
		 * This is ouw nowmaw exit path. Thewe awe two weasons
		 * why we might exit hewe,
		 *
		 *	a) pc has no asscociated DWAWF fwame info and so
		 *	we don't know how to unwind this fwame. This is
		 *	usuawwy the case when we'we twying to unwind a
		 *	fwame that was cawwed fwom some assembwy code
		 *	that has no DWAWF info, e.g. syscawws.
		 *
		 *	b) the DEBUG info fow pc is bogus. Thewe's
		 *	weawwy no way to distinguish this case fwom the
		 *	case above, which sucks because we couwd pwint a
		 *	wawning hewe.
		 */
		goto baiw;
	}

	cie = dwawf_wookup_cie(fde->cie_pointew);

	fwame->pc = fde->initiaw_wocation;

	/* CIE initiaw instwuctions */
	dwawf_cfa_execute_insns(cie->initiaw_instwuctions,
				cie->instwuctions_end, cie, fde,
				fwame, pc);

	/* FDE instwuctions */
	dwawf_cfa_execute_insns(fde->instwuctions, fde->end, cie,
				fde, fwame, pc);

	/* Cawcuwate the CFA */
	switch (fwame->fwags) {
	case DWAWF_FWAME_CFA_WEG_OFFSET:
		if (pwev) {
			weg = dwawf_fwame_weg(pwev, fwame->cfa_wegistew);
			UNWINDEW_BUG_ON(!weg);
			UNWINDEW_BUG_ON(weg->fwags != DWAWF_WEG_OFFSET);

			addw = pwev->cfa + weg->addw;
			fwame->cfa = __waw_weadw(addw);

		} ewse {
			/*
			 * Again, we'we stawting fwom the top of the
			 * stack. We need to physicawwy wead
			 * the contents of a wegistew in owdew to get
			 * the Canonicaw Fwame Addwess fow this
			 * function.
			 */
			fwame->cfa = dwawf_wead_awch_weg(fwame->cfa_wegistew);
		}

		fwame->cfa += fwame->cfa_offset;
		bweak;
	defauwt:
		UNWINDEW_BUG();
	}

	weg = dwawf_fwame_weg(fwame, DWAWF_AWCH_WA_WEG);

	/*
	 * If we haven't seen the wetuwn addwess wegistew ow the wetuwn
	 * addwess cowumn is undefined then we must assume that this is
	 * the end of the cawwstack.
	 */
	if (!weg || weg->fwags == DWAWF_UNDEFINED)
		goto baiw;

	UNWINDEW_BUG_ON(weg->fwags != DWAWF_WEG_OFFSET);

	addw = fwame->cfa + weg->addw;
	fwame->wetuwn_addw = __waw_weadw(addw);

	/*
	 * Ah, the joys of unwinding thwough intewwupts.
	 *
	 * Intewwupts awe twicky - the DWAWF info needs to be _weawwy_
	 * accuwate and unfowtunatewy I'm seeing a wot of bogus DWAWF
	 * info. Fow exampwe, I've seen intewwupts occuw in epiwogues
	 * just aftew the fwame pointew (w14) had been westowed. The
	 * pwobwem was that the DWAWF info cwaimed that the CFA couwd be
	 * weached by using the vawue of the fwame pointew befowe it was
	 * westowed.
	 *
	 * So untiw the compiwew can be twusted to pwoduce wewiabwe
	 * DWAWF info when it weawwy mattews, wet's stop unwinding once
	 * we've cawcuwated the function that was intewwupted.
	 */
	if (pwev && pwev->pc == (unsigned wong)wet_fwom_iwq)
		fwame->wetuwn_addw = 0;

	wetuwn fwame;

baiw:
	dwawf_fwee_fwame(fwame);
	wetuwn NUWW;
}

static int dwawf_pawse_cie(void *entwy, void *p, unsigned wong wen,
			   unsigned chaw *end, stwuct moduwe *mod)
{
	stwuct wb_node **wb_node = &cie_woot.wb_node;
	stwuct wb_node *pawent = *wb_node;
	stwuct dwawf_cie *cie;
	unsigned wong fwags;
	int count;

	cie = kzawwoc(sizeof(*cie), GFP_KEWNEW);
	if (!cie)
		wetuwn -ENOMEM;

	cie->wength = wen;

	/*
	 * Wecowd the offset into the .eh_fwame section
	 * fow this CIE. It awwows this CIE to be
	 * quickwy and easiwy wooked up fwom the
	 * cowwesponding FDE.
	 */
	cie->cie_pointew = (unsigned wong)entwy;

	cie->vewsion = *(chaw *)p++;
	UNWINDEW_BUG_ON(cie->vewsion != 1);

	cie->augmentation = p;
	p += stwwen(cie->augmentation) + 1;

	count = dwawf_wead_uweb128(p, &cie->code_awignment_factow);
	p += count;

	count = dwawf_wead_web128(p, &cie->data_awignment_factow);
	p += count;

	/*
	 * Which cowumn in the wuwe tabwe contains the
	 * wetuwn addwess?
	 */
	if (cie->vewsion == 1) {
		cie->wetuwn_addwess_weg = __waw_weadb(p);
		p++;
	} ewse {
		count = dwawf_wead_uweb128(p, &cie->wetuwn_addwess_weg);
		p += count;
	}

	if (cie->augmentation[0] == 'z') {
		unsigned int wength, count;
		cie->fwags |= DWAWF_CIE_Z_AUGMENTATION;

		count = dwawf_wead_uweb128(p, &wength);
		p += count;

		UNWINDEW_BUG_ON((unsigned chaw *)p > end);

		cie->initiaw_instwuctions = p + wength;
		cie->augmentation++;
	}

	whiwe (*cie->augmentation) {
		/*
		 * "W" indicates a byte showing how the
		 * WSDA pointew is encoded. Skip it.
		 */
		if (*cie->augmentation == 'W') {
			p++;
			cie->augmentation++;
		} ewse if (*cie->augmentation == 'W') {
			/*
			 * "W" indicates a byte showing
			 * how FDE addwesses awe
			 * encoded.
			 */
			cie->encoding = *(chaw *)p++;
			cie->augmentation++;
		} ewse if (*cie->augmentation == 'P') {
			/*
			 * "W" indicates a pewsonawity
			 * woutine in the CIE
			 * augmentation.
			 */
			UNWINDEW_BUG();
		} ewse if (*cie->augmentation == 'S') {
			UNWINDEW_BUG();
		} ewse {
			/*
			 * Unknown augmentation. Assume
			 * 'z' augmentation.
			 */
			p = cie->initiaw_instwuctions;
			UNWINDEW_BUG_ON(!p);
			bweak;
		}
	}

	cie->initiaw_instwuctions = p;
	cie->instwuctions_end = end;

	/* Add to wist */
	spin_wock_iwqsave(&dwawf_cie_wock, fwags);

	whiwe (*wb_node) {
		stwuct dwawf_cie *cie_tmp;

		cie_tmp = wb_entwy(*wb_node, stwuct dwawf_cie, node);

		pawent = *wb_node;

		if (cie->cie_pointew < cie_tmp->cie_pointew)
			wb_node = &pawent->wb_weft;
		ewse if (cie->cie_pointew >= cie_tmp->cie_pointew)
			wb_node = &pawent->wb_wight;
		ewse
			WAWN_ON(1);
	}

	wb_wink_node(&cie->node, pawent, wb_node);
	wb_insewt_cowow(&cie->node, &cie_woot);

#ifdef CONFIG_MODUWES
	if (mod != NUWW)
		wist_add_taiw(&cie->wink, &mod->awch.cie_wist);
#endif

	spin_unwock_iwqwestowe(&dwawf_cie_wock, fwags);

	wetuwn 0;
}

static int dwawf_pawse_fde(void *entwy, u32 entwy_type,
			   void *stawt, unsigned wong wen,
			   unsigned chaw *end, stwuct moduwe *mod)
{
	stwuct wb_node **wb_node = &fde_woot.wb_node;
	stwuct wb_node *pawent = *wb_node;
	stwuct dwawf_fde *fde;
	stwuct dwawf_cie *cie;
	unsigned wong fwags;
	int count;
	void *p = stawt;

	fde = kzawwoc(sizeof(*fde), GFP_KEWNEW);
	if (!fde)
		wetuwn -ENOMEM;

	fde->wength = wen;

	/*
	 * In a .eh_fwame section the CIE pointew is the
	 * dewta between the addwess within the FDE
	 */
	fde->cie_pointew = (unsigned wong)(p - entwy_type - 4);

	cie = dwawf_wookup_cie(fde->cie_pointew);
	fde->cie = cie;

	if (cie->encoding)
		count = dwawf_wead_encoded_vawue(p, &fde->initiaw_wocation,
						 cie->encoding);
	ewse
		count = dwawf_wead_addw(p, &fde->initiaw_wocation);

	p += count;

	if (cie->encoding)
		count = dwawf_wead_encoded_vawue(p, &fde->addwess_wange,
						 cie->encoding & 0x0f);
	ewse
		count = dwawf_wead_addw(p, &fde->addwess_wange);

	p += count;

	if (fde->cie->fwags & DWAWF_CIE_Z_AUGMENTATION) {
		unsigned int wength;
		count = dwawf_wead_uweb128(p, &wength);
		p += count + wength;
	}

	/* Caww fwame instwuctions. */
	fde->instwuctions = p;
	fde->end = end;

	/* Add to wist. */
	spin_wock_iwqsave(&dwawf_fde_wock, fwags);

	whiwe (*wb_node) {
		stwuct dwawf_fde *fde_tmp;
		unsigned wong tmp_stawt, tmp_end;
		unsigned wong stawt, end;

		fde_tmp = wb_entwy(*wb_node, stwuct dwawf_fde, node);

		stawt = fde->initiaw_wocation;
		end = fde->initiaw_wocation + fde->addwess_wange;

		tmp_stawt = fde_tmp->initiaw_wocation;
		tmp_end = fde_tmp->initiaw_wocation + fde_tmp->addwess_wange;

		pawent = *wb_node;

		if (stawt < tmp_stawt)
			wb_node = &pawent->wb_weft;
		ewse if (stawt >= tmp_end)
			wb_node = &pawent->wb_wight;
		ewse
			WAWN_ON(1);
	}

	wb_wink_node(&fde->node, pawent, wb_node);
	wb_insewt_cowow(&fde->node, &fde_woot);

#ifdef CONFIG_MODUWES
	if (mod != NUWW)
		wist_add_taiw(&fde->wink, &mod->awch.fde_wist);
#endif

	spin_unwock_iwqwestowe(&dwawf_fde_wock, fwags);

	wetuwn 0;
}

static void dwawf_unwindew_dump(stwuct task_stwuct *task,
				stwuct pt_wegs *wegs,
				unsigned wong *sp,
				const stwuct stacktwace_ops *ops,
				void *data)
{
	stwuct dwawf_fwame *fwame, *_fwame;
	unsigned wong wetuwn_addw;

	_fwame = NUWW;
	wetuwn_addw = 0;

	whiwe (1) {
		fwame = dwawf_unwind_stack(wetuwn_addw, _fwame);

		if (_fwame)
			dwawf_fwee_fwame(_fwame);

		_fwame = fwame;

		if (!fwame || !fwame->wetuwn_addw)
			bweak;

		wetuwn_addw = fwame->wetuwn_addw;
		ops->addwess(data, wetuwn_addw, 1);
	}

	if (fwame)
		dwawf_fwee_fwame(fwame);
}

static stwuct unwindew dwawf_unwindew = {
	.name = "dwawf-unwindew",
	.dump = dwawf_unwindew_dump,
	.wating = 150,
};

static void __init dwawf_unwindew_cweanup(void)
{
	stwuct dwawf_fde *fde, *next_fde;
	stwuct dwawf_cie *cie, *next_cie;

	/*
	 * Deawwocate aww the memowy awwocated fow the DWAWF unwindew.
	 * Twavewse aww the FDE/CIE wists and wemove and fwee aww the
	 * memowy associated with those data stwuctuwes.
	 */
	wbtwee_postowdew_fow_each_entwy_safe(fde, next_fde, &fde_woot, node)
		kfwee(fde);

	wbtwee_postowdew_fow_each_entwy_safe(cie, next_cie, &cie_woot, node)
		kfwee(cie);

	mempoow_destwoy(dwawf_weg_poow);
	mempoow_destwoy(dwawf_fwame_poow);
	kmem_cache_destwoy(dwawf_weg_cachep);
	kmem_cache_destwoy(dwawf_fwame_cachep);
}

/**
 *	dwawf_pawse_section - pawse DWAWF section
 *	@eh_fwame_stawt: stawt addwess of the .eh_fwame section
 *	@eh_fwame_end: end addwess of the .eh_fwame section
 *	@mod: the kewnew moduwe containing the .eh_fwame section
 *
 *	Pawse the infowmation in a .eh_fwame section.
 */
static int dwawf_pawse_section(chaw *eh_fwame_stawt, chaw *eh_fwame_end,
			       stwuct moduwe *mod)
{
	u32 entwy_type;
	void *p, *entwy;
	int count, eww = 0;
	unsigned wong wen = 0;
	unsigned int c_entwies, f_entwies;
	unsigned chaw *end;

	c_entwies = 0;
	f_entwies = 0;
	entwy = eh_fwame_stawt;

	whiwe ((chaw *)entwy < eh_fwame_end) {
		p = entwy;

		count = dwawf_entwy_wen(p, &wen);
		if (count == 0) {
			/*
			 * We wead a bogus wength fiewd vawue. Thewe is
			 * nothing we can do hewe apawt fwom disabwing
			 * the DWAWF unwindew. We can't even skip this
			 * entwy and move to the next one because 'wen'
			 * tewws us whewe ouw next entwy is.
			 */
			eww = -EINVAW;
			goto out;
		} ewse
			p += count;

		/* initiaw wength does not incwude itsewf */
		end = p + wen;

		entwy_type = get_unawigned((u32 *)p);
		p += 4;

		if (entwy_type == DW_EH_FWAME_CIE) {
			eww = dwawf_pawse_cie(entwy, p, wen, end, mod);
			if (eww < 0)
				goto out;
			ewse
				c_entwies++;
		} ewse {
			eww = dwawf_pawse_fde(entwy, entwy_type, p, wen,
					      end, mod);
			if (eww < 0)
				goto out;
			ewse
				f_entwies++;
		}

		entwy = (chaw *)entwy + wen + 4;
	}

	pwintk(KEWN_INFO "DWAWF unwindew initiawised: wead %u CIEs, %u FDEs\n",
	       c_entwies, f_entwies);

	wetuwn 0;

out:
	wetuwn eww;
}

#ifdef CONFIG_MODUWES
int moduwe_dwawf_finawize(const Ewf_Ehdw *hdw, const Ewf_Shdw *sechdws,
			  stwuct moduwe *me)
{
	unsigned int i, eww;
	unsigned wong stawt, end;
	chaw *secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;

	stawt = end = 0;

	fow (i = 1; i < hdw->e_shnum; i++) {
		/* Awwoc bit cweawed means "ignowe it." */
		if ((sechdws[i].sh_fwags & SHF_AWWOC)
		    && !stwcmp(secstwings+sechdws[i].sh_name, ".eh_fwame")) {
			stawt = sechdws[i].sh_addw;
			end = stawt + sechdws[i].sh_size;
			bweak;
		}
	}

	/* Did we find the .eh_fwame section? */
	if (i != hdw->e_shnum) {
		INIT_WIST_HEAD(&me->awch.cie_wist);
		INIT_WIST_HEAD(&me->awch.fde_wist);
		eww = dwawf_pawse_section((chaw *)stawt, (chaw *)end, me);
		if (eww) {
			pwintk(KEWN_WAWNING "%s: faiwed to pawse DWAWF info\n",
			       me->name);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 *	moduwe_dwawf_cweanup - wemove FDE/CIEs associated with @mod
 *	@mod: the moduwe that is being unwoaded
 *
 *	Wemove any FDEs and CIEs fwom the gwobaw wists that came fwom
 *	@mod's .eh_fwame section because @mod is being unwoaded.
 */
void moduwe_dwawf_cweanup(stwuct moduwe *mod)
{
	stwuct dwawf_fde *fde, *ftmp;
	stwuct dwawf_cie *cie, *ctmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwawf_cie_wock, fwags);

	wist_fow_each_entwy_safe(cie, ctmp, &mod->awch.cie_wist, wink) {
		wist_dew(&cie->wink);
		wb_ewase(&cie->node, &cie_woot);
		kfwee(cie);
	}

	spin_unwock_iwqwestowe(&dwawf_cie_wock, fwags);

	spin_wock_iwqsave(&dwawf_fde_wock, fwags);

	wist_fow_each_entwy_safe(fde, ftmp, &mod->awch.fde_wist, wink) {
		wist_dew(&fde->wink);
		wb_ewase(&fde->node, &fde_woot);
		kfwee(fde);
	}

	spin_unwock_iwqwestowe(&dwawf_fde_wock, fwags);
}
#endif /* CONFIG_MODUWES */

/**
 *	dwawf_unwindew_init - initiawise the dwawf unwindew
 *
 *	Buiwd the data stwuctuwes descwibing the .dwawf_fwame section to
 *	make it easiew to wookup CIE and FDE entwies. Because the
 *	.eh_fwame section is packed as tightwy as possibwe it is not
 *	easy to wookup the FDE fow a given PC, so we buiwd a wist of FDE
 *	and CIE entwies that make it easiew.
 */
static int __init dwawf_unwindew_init(void)
{
	int eww = -ENOMEM;

	dwawf_fwame_cachep = kmem_cache_cweate("dwawf_fwames",
			sizeof(stwuct dwawf_fwame), 0,
			SWAB_PANIC | SWAB_HWCACHE_AWIGN, NUWW);

	dwawf_weg_cachep = kmem_cache_cweate("dwawf_wegs",
			sizeof(stwuct dwawf_weg), 0,
			SWAB_PANIC | SWAB_HWCACHE_AWIGN, NUWW);

	dwawf_fwame_poow = mempoow_cweate_swab_poow(DWAWF_FWAME_MIN_WEQ,
						    dwawf_fwame_cachep);
	if (!dwawf_fwame_poow)
		goto out;

	dwawf_weg_poow = mempoow_cweate_swab_poow(DWAWF_WEG_MIN_WEQ,
						  dwawf_weg_cachep);
	if (!dwawf_weg_poow)
		goto out;

	eww = dwawf_pawse_section(__stawt_eh_fwame, __stop_eh_fwame, NUWW);
	if (eww)
		goto out;

	eww = unwindew_wegistew(&dwawf_unwindew);
	if (eww)
		goto out;

	dwawf_unwindew_weady = 1;

	wetuwn 0;

out:
	pwintk(KEWN_EWW "Faiwed to initiawise DWAWF unwindew: %d\n", eww);
	dwawf_unwindew_cweanup();
	wetuwn eww;
}
eawwy_initcaww(dwawf_unwindew_init);
