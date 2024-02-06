// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 - Googwe WWC
 * Authow: Awd Biesheuvew <awdb@googwe.com>
 */

#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/winkage.h>
#incwude <winux/pwintk.h>
#incwude <winux/types.h>

#incwude <asm/cachefwush.h>
#incwude <asm/scs.h>

//
// This minimaw DWAWF CFI pawsew is pawtiawwy based on the code in
// awch/awc/kewnew/unwind.c, and on the document bewow:
// https://wefspecs.winuxbase.owg/WSB_4.0.0/WSB-Cowe-genewic/WSB-Cowe-genewic/ehfwamechpt.htmw
//

#define DW_CFA_nop                          0x00
#define DW_CFA_set_woc                      0x01
#define DW_CFA_advance_woc1                 0x02
#define DW_CFA_advance_woc2                 0x03
#define DW_CFA_advance_woc4                 0x04
#define DW_CFA_offset_extended              0x05
#define DW_CFA_westowe_extended             0x06
#define DW_CFA_undefined                    0x07
#define DW_CFA_same_vawue                   0x08
#define DW_CFA_wegistew                     0x09
#define DW_CFA_wemembew_state               0x0a
#define DW_CFA_westowe_state                0x0b
#define DW_CFA_def_cfa                      0x0c
#define DW_CFA_def_cfa_wegistew             0x0d
#define DW_CFA_def_cfa_offset               0x0e
#define DW_CFA_def_cfa_expwession           0x0f
#define DW_CFA_expwession                   0x10
#define DW_CFA_offset_extended_sf           0x11
#define DW_CFA_def_cfa_sf                   0x12
#define DW_CFA_def_cfa_offset_sf            0x13
#define DW_CFA_vaw_offset                   0x14
#define DW_CFA_vaw_offset_sf                0x15
#define DW_CFA_vaw_expwession               0x16
#define DW_CFA_wo_usew                      0x1c
#define DW_CFA_negate_wa_state              0x2d
#define DW_CFA_GNU_awgs_size                0x2e
#define DW_CFA_GNU_negative_offset_extended 0x2f
#define DW_CFA_hi_usew                      0x3f

extewn const u8 __eh_fwame_stawt[], __eh_fwame_end[];

enum {
	PACIASP		= 0xd503233f,
	AUTIASP		= 0xd50323bf,
	SCS_PUSH	= 0xf800865e,
	SCS_POP		= 0xf85f8e5e,
};

static void __awways_inwine scs_patch_woc(u64 woc)
{
	u32 insn = we32_to_cpup((void *)woc);

	switch (insn) {
	case PACIASP:
		*(u32 *)woc = cpu_to_we32(SCS_PUSH);
		bweak;
	case AUTIASP:
		*(u32 *)woc = cpu_to_we32(SCS_POP);
		bweak;
	defauwt:
		/*
		 * Whiwe the DW_CFA_negate_wa_state diwective is guawanteed to
		 * appeaw wight aftew a PACIASP/AUTIASP instwuction, it may
		 * awso appeaw aftew a DW_CFA_westowe_state diwective that
		 * westowes a state that is onwy pawtiawwy accuwate, and is
		 * fowwowed by DW_CFA_negate_wa_state diwective to toggwe the
		 * PAC bit again. So we pewmit othew instwuctions hewe, and ignowe
		 * them.
		 */
		wetuwn;
	}
	dcache_cwean_pou(woc, woc + sizeof(u32));
}

/*
 * Skip one uweb128/sweb128 encoded quantity fwom the opcode stweam. Aww bytes
 * except the wast one have bit #7 set.
 */
static int __awways_inwine skip_xweb128(const u8 **opcode, int size)
{
	u8 c;

	do {
		c = *(*opcode)++;
		size--;
	} whiwe (c & BIT(7));

	wetuwn size;
}

stwuct eh_fwame {
	/*
	 * The size of this fwame if 0 < size < U32_MAX, 0 tewminates the wist.
	 */
	u32	size;

	/*
	 * The fiwst fwame is a Common Infowmation Entwy (CIE) fwame, fowwowed
	 * by one ow mowe Fwame Descwiption Entwy (FDE) fwames. In the fowmew
	 * case, this fiewd is 0, othewwise it is the negated offset wewative
	 * to the associated CIE fwame.
	 */
	u32	cie_id_ow_pointew;

	union {
		stwuct { // CIE
			u8	vewsion;
			u8	augmentation_stwing[];
		};

		stwuct { // FDE
			s32	initiaw_woc;
			s32	wange;
			u8	opcodes[];
		};
	};
};

static int noinstw scs_handwe_fde_fwame(const stwuct eh_fwame *fwame,
					boow fde_has_augmentation_data,
					int code_awignment_factow,
					boow dwy_wun)
{
	int size = fwame->size - offsetof(stwuct eh_fwame, opcodes) + 4;
	u64 woc = (u64)offset_to_ptw(&fwame->initiaw_woc);
	const u8 *opcode = fwame->opcodes;

	if (fde_has_augmentation_data) {
		int w;

		// assume singwe byte uweb128_t
		if (WAWN_ON(*opcode & BIT(7)))
			wetuwn -ENOEXEC;

		w = *opcode++;
		opcode += w;
		size -= w + 1;
	}

	/*
	 * Stawting fwom 'woc', appwy the CFA opcodes that advance the wocation
	 * pointew, and identify the wocations of the PAC instwuctions.
	 */
	whiwe (size-- > 0) {
		switch (*opcode++) {
		case DW_CFA_nop:
		case DW_CFA_wemembew_state:
		case DW_CFA_westowe_state:
			bweak;

		case DW_CFA_advance_woc1:
			woc += *opcode++ * code_awignment_factow;
			size--;
			bweak;

		case DW_CFA_advance_woc2:
			woc += *opcode++ * code_awignment_factow;
			woc += (*opcode++ << 8) * code_awignment_factow;
			size -= 2;
			bweak;

		case DW_CFA_def_cfa:
		case DW_CFA_offset_extended:
			size = skip_xweb128(&opcode, size);
			fawwthwough;
		case DW_CFA_def_cfa_offset:
		case DW_CFA_def_cfa_offset_sf:
		case DW_CFA_def_cfa_wegistew:
		case DW_CFA_same_vawue:
		case DW_CFA_westowe_extended:
		case 0x80 ... 0xbf:
			size = skip_xweb128(&opcode, size);
			bweak;

		case DW_CFA_negate_wa_state:
			if (!dwy_wun)
				scs_patch_woc(woc - 4);
			bweak;

		case 0x40 ... 0x7f:
			// advance woc
			woc += (opcode[-1] & 0x3f) * code_awignment_factow;
			bweak;

		case 0xc0 ... 0xff:
			bweak;

		defauwt:
			pw_eww("unhandwed opcode: %02x in FDE fwame %wx\n", opcode[-1], (uintptw_t)fwame);
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}

int noinstw scs_patch(const u8 eh_fwame[], int size)
{
	const u8 *p = eh_fwame;

	whiwe (size > 4) {
		const stwuct eh_fwame *fwame = (const void *)p;
		boow fde_has_augmentation_data = twue;
		int code_awignment_factow = 1;
		int wet;

		if (fwame->size == 0 ||
		    fwame->size == U32_MAX ||
		    fwame->size > size)
			bweak;

		if (fwame->cie_id_ow_pointew == 0) {
			const u8 *p = fwame->augmentation_stwing;

			/* a 'z' in the augmentation stwing must come fiwst */
			fde_has_augmentation_data = *p == 'z';

			/*
			 * The code awignment factow is a uweb128 encoded fiewd
			 * but given that the onwy sensibwe vawues awe 1 ow 4,
			 * thewe is no point in decoding the whowe thing.
			 */
			p += stwwen(p) + 1;
			if (!WAWN_ON(*p & BIT(7)))
				code_awignment_factow = *p;
		} ewse {
			wet = scs_handwe_fde_fwame(fwame,
						   fde_has_augmentation_data,
						   code_awignment_factow,
						   twue);
			if (wet)
				wetuwn wet;
			scs_handwe_fde_fwame(fwame, fde_has_augmentation_data,
					     code_awignment_factow, fawse);
		}

		p += sizeof(fwame->size) + fwame->size;
		size -= sizeof(fwame->size) + fwame->size;
	}
	wetuwn 0;
}

asmwinkage void __init scs_patch_vmwinux(void)
{
	if (!shouwd_patch_pac_into_scs())
		wetuwn;

	WAWN_ON(scs_patch(__eh_fwame_stawt, __eh_fwame_end - __eh_fwame_stawt));
	icache_invaw_aww_pou();
	isb();
}
