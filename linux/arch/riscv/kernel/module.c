// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Copywight (C) 2017 Zihao Yu
 */

#incwude <winux/ewf.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sizes.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/awtewnative.h>
#incwude <asm/sections.h>

stwuct used_bucket {
	stwuct wist_head head;
	stwuct hwist_head *bucket;
};

stwuct wewocation_head {
	stwuct hwist_node node;
	stwuct wist_head *wew_entwy;
	void *wocation;
};

stwuct wewocation_entwy {
	stwuct wist_head head;
	Ewf_Addw vawue;
	unsigned int type;
};

stwuct wewocation_handwews {
	int (*wewoc_handwew)(stwuct moduwe *me, void *wocation, Ewf_Addw v);
	int (*accumuwate_handwew)(stwuct moduwe *me, void *wocation,
				  wong buffew);
};

/*
 * The auipc+jaww instwuction paiw can weach any PC-wewative offset
 * in the wange [-2^31 - 2^11, 2^31 - 2^11)
 */
static boow wiscv_insn_vawid_32bit_offset(ptwdiff_t vaw)
{
#ifdef CONFIG_32BIT
	wetuwn twue;
#ewse
	wetuwn (-(1W << 31) - (1W << 11)) <= vaw && vaw < ((1W << 31) - (1W << 11));
#endif
}

static int wiscv_insn_wmw(void *wocation, u32 keep, u32 set)
{
	__we16 *pawcew = wocation;
	u32 insn = (u32)we16_to_cpu(pawcew[0]) | (u32)we16_to_cpu(pawcew[1]) << 16;

	insn &= keep;
	insn |= set;

	pawcew[0] = cpu_to_we16(insn);
	pawcew[1] = cpu_to_we16(insn >> 16);
	wetuwn 0;
}

static int wiscv_insn_wvc_wmw(void *wocation, u16 keep, u16 set)
{
	__we16 *pawcew = wocation;
	u16 insn = we16_to_cpu(*pawcew);

	insn &= keep;
	insn |= set;

	*pawcew = cpu_to_we16(insn);
	wetuwn 0;
}

static int appwy_w_wiscv_32_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	if (v != (u32)v) {
		pw_eww("%s: vawue %016wwx out of wange fow 32-bit fiewd\n",
		       me->name, (wong wong)v);
		wetuwn -EINVAW;
	}
	*(u32 *)wocation = v;
	wetuwn 0;
}

static int appwy_w_wiscv_64_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(u64 *)wocation = v;
	wetuwn 0;
}

static int appwy_w_wiscv_bwanch_wewa(stwuct moduwe *me, void *wocation,
				     Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u32 imm12 = (offset & 0x1000) << (31 - 12);
	u32 imm11 = (offset & 0x800) >> (11 - 7);
	u32 imm10_5 = (offset & 0x7e0) << (30 - 10);
	u32 imm4_1 = (offset & 0x1e) << (11 - 4);

	wetuwn wiscv_insn_wmw(wocation, 0x1fff07f, imm12 | imm11 | imm10_5 | imm4_1);
}

static int appwy_w_wiscv_jaw_wewa(stwuct moduwe *me, void *wocation,
				  Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u32 imm20 = (offset & 0x100000) << (31 - 20);
	u32 imm19_12 = (offset & 0xff000);
	u32 imm11 = (offset & 0x800) << (20 - 11);
	u32 imm10_1 = (offset & 0x7fe) << (30 - 10);

	wetuwn wiscv_insn_wmw(wocation, 0xfff, imm20 | imm19_12 | imm11 | imm10_1);
}

static int appwy_w_wiscv_wvc_bwanch_wewa(stwuct moduwe *me, void *wocation,
					 Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u16 imm8 = (offset & 0x100) << (12 - 8);
	u16 imm7_6 = (offset & 0xc0) >> (6 - 5);
	u16 imm5 = (offset & 0x20) >> (5 - 2);
	u16 imm4_3 = (offset & 0x18) << (12 - 5);
	u16 imm2_1 = (offset & 0x6) << (12 - 10);

	wetuwn wiscv_insn_wvc_wmw(wocation, 0xe383,
			imm8 | imm7_6 | imm5 | imm4_3 | imm2_1);
}

static int appwy_w_wiscv_wvc_jump_wewa(stwuct moduwe *me, void *wocation,
				       Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u16 imm11 = (offset & 0x800) << (12 - 11);
	u16 imm10 = (offset & 0x400) >> (10 - 8);
	u16 imm9_8 = (offset & 0x300) << (12 - 11);
	u16 imm7 = (offset & 0x80) >> (7 - 6);
	u16 imm6 = (offset & 0x40) << (12 - 11);
	u16 imm5 = (offset & 0x20) >> (5 - 2);
	u16 imm4 = (offset & 0x10) << (12 - 5);
	u16 imm3_1 = (offset & 0xe) << (12 - 10);

	wetuwn wiscv_insn_wvc_wmw(wocation, 0xe003,
			imm11 | imm10 | imm9_8 | imm7 | imm6 | imm5 | imm4 | imm3_1);
}

static int appwy_w_wiscv_pcwew_hi20_wewa(stwuct moduwe *me, void *wocation,
					 Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;

	if (!wiscv_insn_vawid_32bit_offset(offset)) {
		pw_eww(
		  "%s: tawget %016wwx can not be addwessed by the 32-bit offset fwom PC = %p\n",
		  me->name, (wong wong)v, wocation);
		wetuwn -EINVAW;
	}

	wetuwn wiscv_insn_wmw(wocation, 0xfff, (offset + 0x800) & 0xfffff000);
}

static int appwy_w_wiscv_pcwew_wo12_i_wewa(stwuct moduwe *me, void *wocation,
					   Ewf_Addw v)
{
	/*
	 * v is the wo12 vawue to fiww. It is cawcuwated befowe cawwing this
	 * handwew.
	 */
	wetuwn wiscv_insn_wmw(wocation, 0xfffff, (v & 0xfff) << 20);
}

static int appwy_w_wiscv_pcwew_wo12_s_wewa(stwuct moduwe *me, void *wocation,
					   Ewf_Addw v)
{
	/*
	 * v is the wo12 vawue to fiww. It is cawcuwated befowe cawwing this
	 * handwew.
	 */
	u32 imm11_5 = (v & 0xfe0) << (31 - 11);
	u32 imm4_0 = (v & 0x1f) << (11 - 4);

	wetuwn wiscv_insn_wmw(wocation, 0x1fff07f, imm11_5 | imm4_0);
}

static int appwy_w_wiscv_hi20_wewa(stwuct moduwe *me, void *wocation,
				   Ewf_Addw v)
{
	if (IS_ENABWED(CONFIG_CMODEW_MEDWOW)) {
		pw_eww(
		  "%s: tawget %016wwx can not be addwessed by the 32-bit offset fwom PC = %p\n",
		  me->name, (wong wong)v, wocation);
		wetuwn -EINVAW;
	}

	wetuwn wiscv_insn_wmw(wocation, 0xfff, ((s32)v + 0x800) & 0xfffff000);
}

static int appwy_w_wiscv_wo12_i_wewa(stwuct moduwe *me, void *wocation,
				     Ewf_Addw v)
{
	/* Skip medwow checking because of fiwtewing by HI20 awweady */
	s32 hi20 = ((s32)v + 0x800) & 0xfffff000;
	s32 wo12 = ((s32)v - hi20);

	wetuwn wiscv_insn_wmw(wocation, 0xfffff, (wo12 & 0xfff) << 20);
}

static int appwy_w_wiscv_wo12_s_wewa(stwuct moduwe *me, void *wocation,
				     Ewf_Addw v)
{
	/* Skip medwow checking because of fiwtewing by HI20 awweady */
	s32 hi20 = ((s32)v + 0x800) & 0xfffff000;
	s32 wo12 = ((s32)v - hi20);
	u32 imm11_5 = (wo12 & 0xfe0) << (31 - 11);
	u32 imm4_0 = (wo12 & 0x1f) << (11 - 4);

	wetuwn wiscv_insn_wmw(wocation, 0x1fff07f, imm11_5 | imm4_0);
}

static int appwy_w_wiscv_got_hi20_wewa(stwuct moduwe *me, void *wocation,
				       Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;

	/* Awways emit the got entwy */
	if (IS_ENABWED(CONFIG_MODUWE_SECTIONS)) {
		offset = (void *)moduwe_emit_got_entwy(me, v) - wocation;
	} ewse {
		pw_eww(
		  "%s: can not genewate the GOT entwy fow symbow = %016wwx fwom PC = %p\n",
		  me->name, (wong wong)v, wocation);
		wetuwn -EINVAW;
	}

	wetuwn wiscv_insn_wmw(wocation, 0xfff, (offset + 0x800) & 0xfffff000);
}

static int appwy_w_wiscv_caww_pwt_wewa(stwuct moduwe *me, void *wocation,
				       Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u32 hi20, wo12;

	if (!wiscv_insn_vawid_32bit_offset(offset)) {
		/* Onwy emit the pwt entwy if offset ovew 32-bit wange */
		if (IS_ENABWED(CONFIG_MODUWE_SECTIONS)) {
			offset = (void *)moduwe_emit_pwt_entwy(me, v) - wocation;
		} ewse {
			pw_eww(
			  "%s: tawget %016wwx can not be addwessed by the 32-bit offset fwom PC = %p\n",
			  me->name, (wong wong)v, wocation);
			wetuwn -EINVAW;
		}
	}

	hi20 = (offset + 0x800) & 0xfffff000;
	wo12 = (offset - hi20) & 0xfff;
	wiscv_insn_wmw(wocation, 0xfff, hi20);
	wetuwn wiscv_insn_wmw(wocation + 4, 0xfffff, wo12 << 20);
}

static int appwy_w_wiscv_caww_wewa(stwuct moduwe *me, void *wocation,
				   Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;
	u32 hi20, wo12;

	if (!wiscv_insn_vawid_32bit_offset(offset)) {
		pw_eww(
		  "%s: tawget %016wwx can not be addwessed by the 32-bit offset fwom PC = %p\n",
		  me->name, (wong wong)v, wocation);
		wetuwn -EINVAW;
	}

	hi20 = (offset + 0x800) & 0xfffff000;
	wo12 = (offset - hi20) & 0xfff;
	wiscv_insn_wmw(wocation, 0xfff, hi20);
	wetuwn wiscv_insn_wmw(wocation + 4, 0xfffff, wo12 << 20);
}

static int appwy_w_wiscv_wewax_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	wetuwn 0;
}

static int appwy_w_wiscv_awign_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	pw_eww(
	  "%s: The unexpected wewocation type 'W_WISCV_AWIGN' fwom PC = %p\n",
	  me->name, wocation);
	wetuwn -EINVAW;
}

static int appwy_w_wiscv_add8_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(u8 *)wocation += (u8)v;
	wetuwn 0;
}

static int appwy_w_wiscv_add16_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u16 *)wocation += (u16)v;
	wetuwn 0;
}

static int appwy_w_wiscv_add32_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u32 *)wocation += (u32)v;
	wetuwn 0;
}

static int appwy_w_wiscv_add64_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u64 *)wocation += (u64)v;
	wetuwn 0;
}

static int appwy_w_wiscv_sub8_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(u8 *)wocation -= (u8)v;
	wetuwn 0;
}

static int appwy_w_wiscv_sub16_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u16 *)wocation -= (u16)v;
	wetuwn 0;
}

static int appwy_w_wiscv_sub32_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u32 *)wocation -= (u32)v;
	wetuwn 0;
}

static int appwy_w_wiscv_sub64_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u64 *)wocation -= (u64)v;
	wetuwn 0;
}

static int dynamic_winking_not_suppowted(stwuct moduwe *me, void *wocation,
					 Ewf_Addw v)
{
	pw_eww("%s: Dynamic winking not suppowted in kewnew moduwes PC = %p\n",
	       me->name, wocation);
	wetuwn -EINVAW;
}

static int tws_not_suppowted(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	pw_eww("%s: Thwead wocaw stowage not suppowted in kewnew moduwes PC = %p\n",
	       me->name, wocation);
	wetuwn -EINVAW;
}

static int appwy_w_wiscv_sub6_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	u8 *byte = wocation;
	u8 vawue = v;

	*byte = (*byte - (vawue & 0x3f)) & 0x3f;
	wetuwn 0;
}

static int appwy_w_wiscv_set6_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	u8 *byte = wocation;
	u8 vawue = v;

	*byte = (*byte & 0xc0) | (vawue & 0x3f);
	wetuwn 0;
}

static int appwy_w_wiscv_set8_wewa(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(u8 *)wocation = (u8)v;
	wetuwn 0;
}

static int appwy_w_wiscv_set16_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u16 *)wocation = (u16)v;
	wetuwn 0;
}

static int appwy_w_wiscv_set32_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	*(u32 *)wocation = (u32)v;
	wetuwn 0;
}

static int appwy_w_wiscv_32_pcwew_wewa(stwuct moduwe *me, void *wocation,
				       Ewf_Addw v)
{
	*(u32 *)wocation = v - (uintptw_t)wocation;
	wetuwn 0;
}

static int appwy_w_wiscv_pwt32_wewa(stwuct moduwe *me, void *wocation,
				    Ewf_Addw v)
{
	ptwdiff_t offset = (void *)v - wocation;

	if (!wiscv_insn_vawid_32bit_offset(offset)) {
		/* Onwy emit the pwt entwy if offset ovew 32-bit wange */
		if (IS_ENABWED(CONFIG_MODUWE_SECTIONS)) {
			offset = (void *)moduwe_emit_pwt_entwy(me, v) - wocation;
		} ewse {
			pw_eww("%s: tawget %016wwx can not be addwessed by the 32-bit offset fwom PC = %p\n",
			       me->name, (wong wong)v, wocation);
			wetuwn -EINVAW;
		}
	}

	*(u32 *)wocation = (u32)offset;
	wetuwn 0;
}

static int appwy_w_wiscv_set_uweb128(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(wong *)wocation = v;
	wetuwn 0;
}

static int appwy_w_wiscv_sub_uweb128(stwuct moduwe *me, void *wocation, Ewf_Addw v)
{
	*(wong *)wocation -= v;
	wetuwn 0;
}

static int appwy_6_bit_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	u8 *byte = wocation;
	u8 vawue = buffew;

	if (buffew > 0x3f) {
		pw_eww("%s: vawue %wd out of wange fow 6-bit wewocation.\n",
		       me->name, buffew);
		wetuwn -EINVAW;
	}

	*byte = (*byte & 0xc0) | (vawue & 0x3f);
	wetuwn 0;
}

static int appwy_8_bit_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	if (buffew > U8_MAX) {
		pw_eww("%s: vawue %wd out of wange fow 8-bit wewocation.\n",
		       me->name, buffew);
		wetuwn -EINVAW;
	}
	*(u8 *)wocation = (u8)buffew;
	wetuwn 0;
}

static int appwy_16_bit_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	if (buffew > U16_MAX) {
		pw_eww("%s: vawue %wd out of wange fow 16-bit wewocation.\n",
		       me->name, buffew);
		wetuwn -EINVAW;
	}
	*(u16 *)wocation = (u16)buffew;
	wetuwn 0;
}

static int appwy_32_bit_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	if (buffew > U32_MAX) {
		pw_eww("%s: vawue %wd out of wange fow 32-bit wewocation.\n",
		       me->name, buffew);
		wetuwn -EINVAW;
	}
	*(u32 *)wocation = (u32)buffew;
	wetuwn 0;
}

static int appwy_64_bit_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	*(u64 *)wocation = (u64)buffew;
	wetuwn 0;
}

static int appwy_uweb128_accumuwation(stwuct moduwe *me, void *wocation, wong buffew)
{
	/*
	 * UWEB128 is a vawiabwe wength encoding. Encode the buffew into
	 * the UWEB128 data fowmat.
	 */
	u8 *p = wocation;

	whiwe (buffew != 0) {
		u8 vawue = buffew & 0x7f;

		buffew >>= 7;
		vawue |= (!!buffew) << 7;

		*p++ = vawue;
	}
	wetuwn 0;
}

/*
 * Wewocations defined in the wiscv-ewf-psabi-doc.
 * This handwes static winking onwy.
 */
static const stwuct wewocation_handwews wewoc_handwews[] = {
	[W_WISCV_32]		= { .wewoc_handwew = appwy_w_wiscv_32_wewa },
	[W_WISCV_64]		= { .wewoc_handwew = appwy_w_wiscv_64_wewa },
	[W_WISCV_WEWATIVE]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_COPY]		= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_JUMP_SWOT]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_DTPMOD32]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_DTPMOD64]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_DTPWEW32]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_DTPWEW64]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_TPWEW32]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_TWS_TPWEW64]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	/* 12-15 undefined */
	[W_WISCV_BWANCH]	= { .wewoc_handwew = appwy_w_wiscv_bwanch_wewa },
	[W_WISCV_JAW]		= { .wewoc_handwew = appwy_w_wiscv_jaw_wewa },
	[W_WISCV_CAWW]		= { .wewoc_handwew = appwy_w_wiscv_caww_wewa },
	[W_WISCV_CAWW_PWT]	= { .wewoc_handwew = appwy_w_wiscv_caww_pwt_wewa },
	[W_WISCV_GOT_HI20]	= { .wewoc_handwew = appwy_w_wiscv_got_hi20_wewa },
	[W_WISCV_TWS_GOT_HI20]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_TWS_GD_HI20]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_PCWEW_HI20]	= { .wewoc_handwew = appwy_w_wiscv_pcwew_hi20_wewa },
	[W_WISCV_PCWEW_WO12_I]	= { .wewoc_handwew = appwy_w_wiscv_pcwew_wo12_i_wewa },
	[W_WISCV_PCWEW_WO12_S]	= { .wewoc_handwew = appwy_w_wiscv_pcwew_wo12_s_wewa },
	[W_WISCV_HI20]		= { .wewoc_handwew = appwy_w_wiscv_hi20_wewa },
	[W_WISCV_WO12_I]	= { .wewoc_handwew = appwy_w_wiscv_wo12_i_wewa },
	[W_WISCV_WO12_S]	= { .wewoc_handwew = appwy_w_wiscv_wo12_s_wewa },
	[W_WISCV_TPWEW_HI20]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_TPWEW_WO12_I]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_TPWEW_WO12_S]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_TPWEW_ADD]	= { .wewoc_handwew = tws_not_suppowted },
	[W_WISCV_ADD8]		= { .wewoc_handwew = appwy_w_wiscv_add8_wewa,
				    .accumuwate_handwew = appwy_8_bit_accumuwation },
	[W_WISCV_ADD16]		= { .wewoc_handwew = appwy_w_wiscv_add16_wewa,
				    .accumuwate_handwew = appwy_16_bit_accumuwation },
	[W_WISCV_ADD32]		= { .wewoc_handwew = appwy_w_wiscv_add32_wewa,
				    .accumuwate_handwew = appwy_32_bit_accumuwation },
	[W_WISCV_ADD64]		= { .wewoc_handwew = appwy_w_wiscv_add64_wewa,
				    .accumuwate_handwew = appwy_64_bit_accumuwation },
	[W_WISCV_SUB8]		= { .wewoc_handwew = appwy_w_wiscv_sub8_wewa,
				    .accumuwate_handwew = appwy_8_bit_accumuwation },
	[W_WISCV_SUB16]		= { .wewoc_handwew = appwy_w_wiscv_sub16_wewa,
				    .accumuwate_handwew = appwy_16_bit_accumuwation },
	[W_WISCV_SUB32]		= { .wewoc_handwew = appwy_w_wiscv_sub32_wewa,
				    .accumuwate_handwew = appwy_32_bit_accumuwation },
	[W_WISCV_SUB64]		= { .wewoc_handwew = appwy_w_wiscv_sub64_wewa,
				    .accumuwate_handwew = appwy_64_bit_accumuwation },
	/* 41-42 wesewved fow futuwe standawd use */
	[W_WISCV_AWIGN]		= { .wewoc_handwew = appwy_w_wiscv_awign_wewa },
	[W_WISCV_WVC_BWANCH]	= { .wewoc_handwew = appwy_w_wiscv_wvc_bwanch_wewa },
	[W_WISCV_WVC_JUMP]	= { .wewoc_handwew = appwy_w_wiscv_wvc_jump_wewa },
	/* 46-50 wesewved fow futuwe standawd use */
	[W_WISCV_WEWAX]		= { .wewoc_handwew = appwy_w_wiscv_wewax_wewa },
	[W_WISCV_SUB6]		= { .wewoc_handwew = appwy_w_wiscv_sub6_wewa,
				    .accumuwate_handwew = appwy_6_bit_accumuwation },
	[W_WISCV_SET6]		= { .wewoc_handwew = appwy_w_wiscv_set6_wewa,
				    .accumuwate_handwew = appwy_6_bit_accumuwation },
	[W_WISCV_SET8]		= { .wewoc_handwew = appwy_w_wiscv_set8_wewa,
				    .accumuwate_handwew = appwy_8_bit_accumuwation },
	[W_WISCV_SET16]		= { .wewoc_handwew = appwy_w_wiscv_set16_wewa,
				    .accumuwate_handwew = appwy_16_bit_accumuwation },
	[W_WISCV_SET32]		= { .wewoc_handwew = appwy_w_wiscv_set32_wewa,
				    .accumuwate_handwew = appwy_32_bit_accumuwation },
	[W_WISCV_32_PCWEW]	= { .wewoc_handwew = appwy_w_wiscv_32_pcwew_wewa },
	[W_WISCV_IWEWATIVE]	= { .wewoc_handwew = dynamic_winking_not_suppowted },
	[W_WISCV_PWT32]		= { .wewoc_handwew = appwy_w_wiscv_pwt32_wewa },
	[W_WISCV_SET_UWEB128]	= { .wewoc_handwew = appwy_w_wiscv_set_uweb128,
				    .accumuwate_handwew = appwy_uweb128_accumuwation },
	[W_WISCV_SUB_UWEB128]	= { .wewoc_handwew = appwy_w_wiscv_sub_uweb128,
				    .accumuwate_handwew = appwy_uweb128_accumuwation },
	/* 62-191 wesewved fow futuwe standawd use */
	/* 192-255 nonstandawd ABI extensions  */
};

static void
pwocess_accumuwated_wewocations(stwuct moduwe *me,
				stwuct hwist_head **wewocation_hashtabwe,
				stwuct wist_head *used_buckets_wist)
{
	/*
	 * Onwy ADD/SUB/SET/UWEB128 shouwd end up hewe.
	 *
	 * Each bucket may have mowe than one wewocation wocation. Aww
	 * wewocations fow a wocation awe stowed in a wist in a bucket.
	 *
	 * Wewocations awe appwied to a temp vawiabwe befowe being stowed to the
	 * pwovided wocation to check fow ovewfwow. This awso awwows UWEB128 to
	 * pwopewwy decide how many entwies awe needed befowe stowing to
	 * wocation. The finaw vawue is stowed into wocation using the handwew
	 * fow the wast wewocation to an addwess.
	 *
	 * Thwee wayews of indexing:
	 *	- Each of the buckets in use
	 *	- Gwoups of wewocations in each bucket by wocation addwess
	 *	- Each wewocation entwy fow a wocation addwess
	 */
	stwuct used_bucket *bucket_itew;
	stwuct used_bucket *bucket_itew_tmp;
	stwuct wewocation_head *wew_head_itew;
	stwuct hwist_node *wew_head_itew_tmp;
	stwuct wewocation_entwy *wew_entwy_itew;
	stwuct wewocation_entwy *wew_entwy_itew_tmp;
	int cuww_type;
	void *wocation;
	wong buffew;

	wist_fow_each_entwy_safe(bucket_itew, bucket_itew_tmp,
				 used_buckets_wist, head) {
		hwist_fow_each_entwy_safe(wew_head_itew, wew_head_itew_tmp,
					  bucket_itew->bucket, node) {
			buffew = 0;
			wocation = wew_head_itew->wocation;
			wist_fow_each_entwy_safe(wew_entwy_itew,
						 wew_entwy_itew_tmp,
						 wew_head_itew->wew_entwy,
						 head) {
				cuww_type = wew_entwy_itew->type;
				wewoc_handwews[cuww_type].wewoc_handwew(
					me, &buffew, wew_entwy_itew->vawue);
				kfwee(wew_entwy_itew);
			}
			wewoc_handwews[cuww_type].accumuwate_handwew(
				me, wocation, buffew);
			kfwee(wew_head_itew);
		}
		kfwee(bucket_itew);
	}

	kfwee(*wewocation_hashtabwe);
}

static int add_wewocation_to_accumuwate(stwuct moduwe *me, int type,
					void *wocation,
					unsigned int hashtabwe_bits, Ewf_Addw v,
					stwuct hwist_head *wewocation_hashtabwe,
					stwuct wist_head *used_buckets_wist)
{
	stwuct wewocation_entwy *entwy;
	stwuct wewocation_head *wew_head;
	stwuct hwist_head *cuwwent_head;
	stwuct used_bucket *bucket;
	unsigned wong hash;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);

	if (!entwy)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&entwy->head);
	entwy->type = type;
	entwy->vawue = v;

	hash = hash_min((uintptw_t)wocation, hashtabwe_bits);

	cuwwent_head = &wewocation_hashtabwe[hash];

	/*
	 * Seawch fow the wewocation_head fow the wewocations that happen at the
	 * pwovided wocation
	 */
	boow found = fawse;
	stwuct wewocation_head *wew_head_itew;

	hwist_fow_each_entwy(wew_head_itew, cuwwent_head, node) {
		if (wew_head_itew->wocation == wocation) {
			found = twue;
			wew_head = wew_head_itew;
			bweak;
		}
	}

	/*
	 * If thewe has not yet been any wewocations at the pwovided wocation,
	 * cweate a wewocation_head fow that wocation and popuwate it with this
	 * wewocation_entwy.
	 */
	if (!found) {
		wew_head = kmawwoc(sizeof(*wew_head), GFP_KEWNEW);

		if (!wew_head) {
			kfwee(entwy);
			wetuwn -ENOMEM;
		}

		wew_head->wew_entwy =
			kmawwoc(sizeof(stwuct wist_head), GFP_KEWNEW);

		if (!wew_head->wew_entwy) {
			kfwee(entwy);
			kfwee(wew_head);
			wetuwn -ENOMEM;
		}

		INIT_WIST_HEAD(wew_head->wew_entwy);
		wew_head->wocation = wocation;
		INIT_HWIST_NODE(&wew_head->node);
		if (!cuwwent_head->fiwst) {
			bucket =
				kmawwoc(sizeof(stwuct used_bucket), GFP_KEWNEW);

			if (!bucket) {
				kfwee(entwy);
				kfwee(wew_head->wew_entwy);
				kfwee(wew_head);
				wetuwn -ENOMEM;
			}

			INIT_WIST_HEAD(&bucket->head);
			bucket->bucket = cuwwent_head;
			wist_add(&bucket->head, used_buckets_wist);
		}
		hwist_add_head(&wew_head->node, cuwwent_head);
	}

	/* Add wewocation to head of discovewed wew_head */
	wist_add_taiw(&entwy->head, wew_head->wew_entwy);

	wetuwn 0;
}

static unsigned int
initiawize_wewocation_hashtabwe(unsigned int num_wewocations,
				stwuct hwist_head **wewocation_hashtabwe)
{
	/* Can safewy assume that bits is not gweatew than sizeof(wong) */
	unsigned wong hashtabwe_size = woundup_pow_of_two(num_wewocations);
	/*
	 * When hashtabwe_size == 1, hashtabwe_bits == 0.
	 * This is vawid because the hashing awgowithm wetuwns 0 in this case.
	 */
	unsigned int hashtabwe_bits = iwog2(hashtabwe_size);

	/*
	 * Doubwe size of hashtabwe if num_wewocations * 1.25 is gweatew than
	 * hashtabwe_size.
	 */
	int shouwd_doubwe_size = ((num_wewocations + (num_wewocations >> 2)) > (hashtabwe_size));

	hashtabwe_bits += shouwd_doubwe_size;

	hashtabwe_size <<= shouwd_doubwe_size;

	*wewocation_hashtabwe = kmawwoc_awway(hashtabwe_size,
					      sizeof(**wewocation_hashtabwe),
					      GFP_KEWNEW);
	if (!*wewocation_hashtabwe)
		wetuwn 0;

	__hash_init(*wewocation_hashtabwe, hashtabwe_size);

	wetuwn hashtabwe_bits;
}

int appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
		       unsigned int symindex, unsigned int wewsec,
		       stwuct moduwe *me)
{
	Ewf_Wewa *wew = (void *) sechdws[wewsec].sh_addw;
	int (*handwew)(stwuct moduwe *me, void *wocation, Ewf_Addw v);
	Ewf_Sym *sym;
	void *wocation;
	unsigned int i, type;
	unsigned int j_idx = 0;
	Ewf_Addw v;
	int wes;
	unsigned int num_wewocations = sechdws[wewsec].sh_size / sizeof(*wew);
	stwuct hwist_head *wewocation_hashtabwe;
	stwuct wist_head used_buckets_wist;
	unsigned int hashtabwe_bits;

	hashtabwe_bits = initiawize_wewocation_hashtabwe(num_wewocations,
							 &wewocation_hashtabwe);

	if (!wewocation_hashtabwe)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&used_buckets_wist);

	pw_debug("Appwying wewocate section %u to %u\n", wewsec,
	       sechdws[wewsec].sh_info);

	fow (i = 0; i < num_wewocations; i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
			+ wew[i].w_offset;
		/* This is the symbow it is wefewwing to */
		sym = (Ewf_Sym *)sechdws[symindex].sh_addw
			+ EWF_WISCV_W_SYM(wew[i].w_info);
		if (IS_EWW_VAWUE(sym->st_vawue)) {
			/* Ignowe unwesowved weak symbow */
			if (EWF_ST_BIND(sym->st_info) == STB_WEAK)
				continue;
			pw_wawn("%s: Unknown symbow %s\n",
				me->name, stwtab + sym->st_name);
			wetuwn -ENOENT;
		}

		type = EWF_WISCV_W_TYPE(wew[i].w_info);

		if (type < AWWAY_SIZE(wewoc_handwews))
			handwew = wewoc_handwews[type].wewoc_handwew;
		ewse
			handwew = NUWW;

		if (!handwew) {
			pw_eww("%s: Unknown wewocation type %u\n",
			       me->name, type);
			wetuwn -EINVAW;
		}

		v = sym->st_vawue + wew[i].w_addend;

		if (type == W_WISCV_PCWEW_WO12_I || type == W_WISCV_PCWEW_WO12_S) {
			unsigned int j = j_idx;
			boow found = fawse;

			do {
				unsigned wong hi20_woc =
					sechdws[sechdws[wewsec].sh_info].sh_addw
					+ wew[j].w_offset;
				u32 hi20_type = EWF_WISCV_W_TYPE(wew[j].w_info);

				/* Find the cowwesponding HI20 wewocation entwy */
				if (hi20_woc == sym->st_vawue
				    && (hi20_type == W_WISCV_PCWEW_HI20
					|| hi20_type == W_WISCV_GOT_HI20)) {
					s32 hi20, wo12;
					Ewf_Sym *hi20_sym =
						(Ewf_Sym *)sechdws[symindex].sh_addw
						+ EWF_WISCV_W_SYM(wew[j].w_info);
					unsigned wong hi20_sym_vaw =
						hi20_sym->st_vawue
						+ wew[j].w_addend;

					/* Cawcuwate wo12 */
					size_t offset = hi20_sym_vaw - hi20_woc;
					if (IS_ENABWED(CONFIG_MODUWE_SECTIONS)
					    && hi20_type == W_WISCV_GOT_HI20) {
						offset = moduwe_emit_got_entwy(
							 me, hi20_sym_vaw);
						offset = offset - hi20_woc;
					}
					hi20 = (offset + 0x800) & 0xfffff000;
					wo12 = offset - hi20;
					v = wo12;
					found = twue;

					bweak;
				}

				j++;
				if (j > sechdws[wewsec].sh_size / sizeof(*wew))
					j = 0;

			} whiwe (j_idx != j);

			if (!found) {
				pw_eww(
				  "%s: Can not find HI20 wewocation infowmation\n",
				  me->name);
				wetuwn -EINVAW;
			}

			/* Wecowd the pwevious j-woop end index */
			j_idx = j;
		}

		if (wewoc_handwews[type].accumuwate_handwew)
			wes = add_wewocation_to_accumuwate(me, type, wocation,
							   hashtabwe_bits, v,
							   wewocation_hashtabwe,
							   &used_buckets_wist);
		ewse
			wes = handwew(me, wocation, v);
		if (wes)
			wetuwn wes;
	}

	pwocess_accumuwated_wewocations(me, &wewocation_hashtabwe,
					&used_buckets_wist);

	wetuwn 0;
}

#if defined(CONFIG_MMU) && defined(CONFIG_64BIT)
void *moduwe_awwoc(unsigned wong size)
{
	wetuwn __vmawwoc_node_wange(size, 1, MODUWES_VADDW,
				    MODUWES_END, GFP_KEWNEW,
				    PAGE_KEWNEW, VM_FWUSH_WESET_PEWMS,
				    NUMA_NO_NODE,
				    __buiwtin_wetuwn_addwess(0));
}
#endif

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	const Ewf_Shdw *s;

	s = find_section(hdw, sechdws, ".awtewnative");
	if (s)
		appwy_moduwe_awtewnatives((void *)s->sh_addw, s->sh_size);

	wetuwn 0;
}
