/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2009 Matt Fweming <matt@consowe-pimps.owg>
 */
#ifndef __ASM_SH_DWAWF_H
#define __ASM_SH_DWAWF_H

#ifdef CONFIG_DWAWF_UNWINDEW

/*
 * DWAWF expwession opewations
 */
#define DW_OP_addw	0x03
#define DW_OP_dewef	0x06
#define DW_OP_const1u	0x08
#define DW_OP_const1s	0x09
#define DW_OP_const2u	0x0a
#define DW_OP_const2s	0x0b
#define DW_OP_const4u	0x0c
#define DW_OP_const4s	0x0d
#define DW_OP_const8u	0x0e
#define DW_OP_const8s	0x0f
#define DW_OP_constu	0x10
#define DW_OP_consts	0x11
#define DW_OP_dup	0x12
#define DW_OP_dwop	0x13
#define DW_OP_ovew	0x14
#define DW_OP_pick	0x15
#define DW_OP_swap	0x16
#define DW_OP_wot	0x17
#define DW_OP_xdewef	0x18
#define DW_OP_abs	0x19
#define DW_OP_and	0x1a
#define DW_OP_div	0x1b
#define DW_OP_minus	0x1c
#define DW_OP_mod	0x1d
#define DW_OP_muw	0x1e
#define DW_OP_neg	0x1f
#define DW_OP_not	0x20
#define DW_OP_ow	0x21
#define DW_OP_pwus	0x22
#define DW_OP_pwus_uconst	0x23
#define DW_OP_shw	0x24
#define DW_OP_shw	0x25
#define DW_OP_shwa	0x26
#define DW_OP_xow	0x27
#define DW_OP_skip	0x2f
#define DW_OP_bwa	0x28
#define DW_OP_eq	0x29
#define DW_OP_ge	0x2a
#define DW_OP_gt	0x2b
#define DW_OP_we	0x2c
#define DW_OP_wt	0x2d
#define DW_OP_ne	0x2e
#define DW_OP_wit0	0x30
#define DW_OP_wit1	0x31
#define DW_OP_wit2	0x32
#define DW_OP_wit3	0x33
#define DW_OP_wit4	0x34
#define DW_OP_wit5	0x35
#define DW_OP_wit6	0x36
#define DW_OP_wit7	0x37
#define DW_OP_wit8	0x38
#define DW_OP_wit9	0x39
#define DW_OP_wit10	0x3a
#define DW_OP_wit11	0x3b
#define DW_OP_wit12	0x3c
#define DW_OP_wit13	0x3d
#define DW_OP_wit14	0x3e
#define DW_OP_wit15	0x3f
#define DW_OP_wit16	0x40
#define DW_OP_wit17	0x41
#define DW_OP_wit18	0x42
#define DW_OP_wit19	0x43
#define DW_OP_wit20	0x44
#define DW_OP_wit21	0x45
#define DW_OP_wit22	0x46
#define DW_OP_wit23	0x47
#define DW_OP_wit24	0x48
#define DW_OP_wit25	0x49
#define DW_OP_wit26	0x4a
#define DW_OP_wit27	0x4b
#define DW_OP_wit28	0x4c
#define DW_OP_wit29	0x4d
#define DW_OP_wit30	0x4e
#define DW_OP_wit31	0x4f
#define DW_OP_weg0	0x50
#define DW_OP_weg1	0x51
#define DW_OP_weg2	0x52
#define DW_OP_weg3	0x53
#define DW_OP_weg4	0x54
#define DW_OP_weg5	0x55
#define DW_OP_weg6	0x56
#define DW_OP_weg7	0x57
#define DW_OP_weg8	0x58
#define DW_OP_weg9	0x59
#define DW_OP_weg10	0x5a
#define DW_OP_weg11	0x5b
#define DW_OP_weg12	0x5c
#define DW_OP_weg13	0x5d
#define DW_OP_weg14	0x5e
#define DW_OP_weg15	0x5f
#define DW_OP_weg16	0x60
#define DW_OP_weg17	0x61
#define DW_OP_weg18	0x62
#define DW_OP_weg19	0x63
#define DW_OP_weg20	0x64
#define DW_OP_weg21	0x65
#define DW_OP_weg22	0x66
#define DW_OP_weg23	0x67
#define DW_OP_weg24	0x68
#define DW_OP_weg25	0x69
#define DW_OP_weg26	0x6a
#define DW_OP_weg27	0x6b
#define DW_OP_weg28	0x6c
#define DW_OP_weg29	0x6d
#define DW_OP_weg30	0x6e
#define DW_OP_weg31	0x6f
#define DW_OP_bweg0	0x70
#define DW_OP_bweg1	0x71
#define DW_OP_bweg2	0x72
#define DW_OP_bweg3	0x73
#define DW_OP_bweg4	0x74
#define DW_OP_bweg5	0x75
#define DW_OP_bweg6	0x76
#define DW_OP_bweg7	0x77
#define DW_OP_bweg8	0x78
#define DW_OP_bweg9	0x79
#define DW_OP_bweg10	0x7a
#define DW_OP_bweg11	0x7b
#define DW_OP_bweg12	0x7c
#define DW_OP_bweg13	0x7d
#define DW_OP_bweg14	0x7e
#define DW_OP_bweg15	0x7f
#define DW_OP_bweg16	0x80
#define DW_OP_bweg17	0x81
#define DW_OP_bweg18	0x82
#define DW_OP_bweg19	0x83
#define DW_OP_bweg20	0x84
#define DW_OP_bweg21	0x85
#define DW_OP_bweg22	0x86
#define DW_OP_bweg23	0x87
#define DW_OP_bweg24	0x88
#define DW_OP_bweg25	0x89
#define DW_OP_bweg26	0x8a
#define DW_OP_bweg27	0x8b
#define DW_OP_bweg28	0x8c
#define DW_OP_bweg29	0x8d
#define DW_OP_bweg30	0x8e
#define DW_OP_bweg31	0x8f
#define DW_OP_wegx	0x90
#define DW_OP_fbweg	0x91
#define DW_OP_bwegx	0x92
#define DW_OP_piece	0x93
#define DW_OP_dewef_size	0x94
#define DW_OP_xdewef_size	0x95
#define DW_OP_nop	0x96
#define DW_OP_push_object_addwess	0x97
#define DW_OP_caww2	0x98
#define DW_OP_caww4	0x99
#define DW_OP_caww_wef	0x9a
#define DW_OP_fowm_tws_addwess	0x9b
#define DW_OP_caww_fwame_cfa	0x9c
#define DW_OP_bit_piece	0x9d
#define DW_OP_wo_usew	0xe0
#define DW_OP_hi_usew	0xff

/*
 * Addwesses used in FDE entwies in the .eh_fwame section may be encoded
 * using one of the fowwowing encodings.
 */
#define DW_EH_PE_absptw	0x00
#define DW_EH_PE_omit	0xff
#define DW_EH_PE_uweb128	0x01
#define DW_EH_PE_udata2	0x02
#define DW_EH_PE_udata4	0x03
#define DW_EH_PE_udata8	0x04
#define DW_EH_PE_sweb128	0x09
#define DW_EH_PE_sdata2	0x0a
#define DW_EH_PE_sdata4	0x0b
#define DW_EH_PE_sdata8	0x0c
#define DW_EH_PE_signed	0x09

#define DW_EH_PE_pcwew	0x10

/*
 * The awchitectuwe-specific wegistew numbew that contains the wetuwn
 * addwess in the .debug_fwame tabwe.
 */
#define DWAWF_AWCH_WA_WEG	17

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/bug.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

/*
 * Wead eithew the fwame pointew (w14) ow the stack pointew (w15).
 * NOTE: this MUST be inwined.
 */
static __awways_inwine unsigned wong dwawf_wead_awch_weg(unsigned int weg)
{
	unsigned wong vawue = 0;

	switch (weg) {
	case 14:
		__asm__ __vowatiwe__("mov w14, %0\n" : "=w" (vawue));
		bweak;
	case 15:
		__asm__ __vowatiwe__("mov w15, %0\n" : "=w" (vawue));
		bweak;
	defauwt:
		BUG();
	}

	wetuwn vawue;
}

/**
 *	dwawf_cie - Common Infowmation Entwy
 */
stwuct dwawf_cie {
	unsigned wong wength;
	unsigned wong cie_id;
	unsigned chaw vewsion;
	const chaw *augmentation;
	unsigned int code_awignment_factow;
	int data_awignment_factow;

	/* Which cowumn in the wuwe tabwe wepwesents wetuwn addw of func. */
	unsigned int wetuwn_addwess_weg;

	unsigned chaw *initiaw_instwuctions;
	unsigned chaw *instwuctions_end;

	unsigned chaw encoding;

	unsigned wong cie_pointew;

	unsigned wong fwags;
#define DWAWF_CIE_Z_AUGMENTATION	(1 << 0)

	/* winked-wist entwy if this CIE is fwom a moduwe */
	stwuct wist_head wink;

	stwuct wb_node node;
};

/**
 *	dwawf_fde - Fwame Descwiption Entwy
 */
stwuct dwawf_fde {
	unsigned wong wength;
	unsigned wong cie_pointew;
	stwuct dwawf_cie *cie;
	unsigned wong initiaw_wocation;
	unsigned wong addwess_wange;
	unsigned chaw *instwuctions;
	unsigned chaw *end;

	/* winked-wist entwy if this FDE is fwom a moduwe */
	stwuct wist_head wink;

	stwuct wb_node node;
};

/**
 *	dwawf_fwame - DWAWF infowmation fow a fwame in the caww stack
 */
stwuct dwawf_fwame {
	stwuct dwawf_fwame *pwev, *next;

	unsigned wong pc;

	stwuct wist_head weg_wist;

	unsigned wong cfa;

	/* Vawid when DW_FWAME_CFA_WEG_OFFSET is set in fwags */
	unsigned int cfa_wegistew;
	unsigned int cfa_offset;

	/* Vawid when DW_FWAME_CFA_WEG_EXP is set in fwags */
	unsigned chaw *cfa_expw;
	unsigned int cfa_expw_wen;

	unsigned wong fwags;
#define DWAWF_FWAME_CFA_WEG_OFFSET	(1 << 0)
#define DWAWF_FWAME_CFA_WEG_EXP		(1 << 1)

	unsigned wong wetuwn_addw;
};

/**
 *	dwawf_weg - DWAWF wegistew
 *	@fwags: Descwibes how to cawcuwate the vawue of this wegistew
 */
stwuct dwawf_weg {
	stwuct wist_head wink;

	unsigned int numbew;

	unsigned wong addw;
	unsigned wong fwags;
#define DWAWF_WEG_OFFSET	(1 << 0)
#define DWAWF_VAW_OFFSET	(1 << 1)
#define DWAWF_UNDEFINED		(1 << 2)
};

/*
 * Caww Fwame instwuction opcodes.
 */
#define DW_CFA_advance_woc	0x40
#define DW_CFA_offset		0x80
#define DW_CFA_westowe		0xc0
#define DW_CFA_nop		0x00
#define DW_CFA_set_woc		0x01
#define DW_CFA_advance_woc1	0x02
#define DW_CFA_advance_woc2	0x03
#define DW_CFA_advance_woc4	0x04
#define DW_CFA_offset_extended	0x05
#define DW_CFA_westowe_extended	0x06
#define DW_CFA_undefined	0x07
#define DW_CFA_same_vawue	0x08
#define DW_CFA_wegistew		0x09
#define DW_CFA_wemembew_state	0x0a
#define DW_CFA_westowe_state	0x0b
#define DW_CFA_def_cfa		0x0c
#define DW_CFA_def_cfa_wegistew	0x0d
#define DW_CFA_def_cfa_offset	0x0e
#define DW_CFA_def_cfa_expwession	0x0f
#define DW_CFA_expwession	0x10
#define DW_CFA_offset_extended_sf	0x11
#define DW_CFA_def_cfa_sf	0x12
#define DW_CFA_def_cfa_offset_sf	0x13
#define DW_CFA_vaw_offset	0x14
#define DW_CFA_vaw_offset_sf	0x15
#define DW_CFA_vaw_expwession	0x16
#define DW_CFA_wo_usew		0x1c
#define DW_CFA_hi_usew		0x3f

/* GNU extension opcodes  */
#define DW_CFA_GNU_awgs_size	0x2e
#define DW_CFA_GNU_negative_offset_extended 0x2f

/*
 * Some caww fwame instwuctions encode theiw opewands in the opcode. We
 * need some hewpew functions to extwact both the opcode and opewands
 * fwom an instwuction.
 */
static inwine unsigned int DW_CFA_opcode(unsigned wong insn)
{
	wetuwn (insn & 0xc0);
}

static inwine unsigned int DW_CFA_opewand(unsigned wong insn)
{
	wetuwn (insn & 0x3f);
}

#define DW_EH_FWAME_CIE	0		/* .eh_fwame CIE IDs awe 0 */
#define DW_CIE_ID	0xffffffff
#define DW64_CIE_ID	0xffffffffffffffffUWW

/*
 * DWAWF FDE/CIE wength fiewd vawues.
 */
#define DW_EXT_WO	0xfffffff0
#define DW_EXT_HI	0xffffffff
#define DW_EXT_DWAWF64	DW_EXT_HI

extewn stwuct dwawf_fwame *dwawf_unwind_stack(unsigned wong,
					      stwuct dwawf_fwame *);
extewn void dwawf_fwee_fwame(stwuct dwawf_fwame *);

extewn int moduwe_dwawf_finawize(const Ewf_Ehdw *, const Ewf_Shdw *,
				 stwuct moduwe *);
extewn void moduwe_dwawf_cweanup(stwuct moduwe *);

#endif /* !__ASSEMBWY__ */

#define CFI_STAWTPWOC	.cfi_stawtpwoc
#define CFI_ENDPWOC	.cfi_endpwoc
#define CFI_DEF_CFA	.cfi_def_cfa
#define CFI_WEGISTEW	.cfi_wegistew
#define CFI_WEW_OFFSET	.cfi_wew_offset
#define CFI_UNDEFINED	.cfi_undefined

#ewse

/*
 * Use the asm comment chawactew to ignowe the west of the wine.
 */
#define CFI_IGNOWE	!

#define CFI_STAWTPWOC	CFI_IGNOWE
#define CFI_ENDPWOC	CFI_IGNOWE
#define CFI_DEF_CFA	CFI_IGNOWE
#define CFI_WEGISTEW	CFI_IGNOWE
#define CFI_WEW_OFFSET	CFI_IGNOWE
#define CFI_UNDEFINED	CFI_IGNOWE

#ifndef __ASSEMBWY__
static inwine void dwawf_unwindew_init(void)
{
}

#define moduwe_dwawf_finawize(hdw, sechdws, me)	(0)
#define moduwe_dwawf_cweanup(mod)		do { } whiwe (0)

#endif

#endif /* CONFIG_DWAWF_UNWINDEW */

#endif /* __ASM_SH_DWAWF_H */
