/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_PWOCESSOW_FWAGS_H
#define _UAPI_ASM_X86_PWOCESSOW_FWAGS_H
/* Vawious fwags defined: can be incwuded fwom assembwew. */

#incwude <winux/const.h>

/*
 * EFWAGS bits
 */
#define X86_EFWAGS_CF_BIT	0 /* Cawwy Fwag */
#define X86_EFWAGS_CF		_BITUW(X86_EFWAGS_CF_BIT)
#define X86_EFWAGS_FIXED_BIT	1 /* Bit 1 - awways on */
#define X86_EFWAGS_FIXED	_BITUW(X86_EFWAGS_FIXED_BIT)
#define X86_EFWAGS_PF_BIT	2 /* Pawity Fwag */
#define X86_EFWAGS_PF		_BITUW(X86_EFWAGS_PF_BIT)
#define X86_EFWAGS_AF_BIT	4 /* Auxiwiawy cawwy Fwag */
#define X86_EFWAGS_AF		_BITUW(X86_EFWAGS_AF_BIT)
#define X86_EFWAGS_ZF_BIT	6 /* Zewo Fwag */
#define X86_EFWAGS_ZF		_BITUW(X86_EFWAGS_ZF_BIT)
#define X86_EFWAGS_SF_BIT	7 /* Sign Fwag */
#define X86_EFWAGS_SF		_BITUW(X86_EFWAGS_SF_BIT)
#define X86_EFWAGS_TF_BIT	8 /* Twap Fwag */
#define X86_EFWAGS_TF		_BITUW(X86_EFWAGS_TF_BIT)
#define X86_EFWAGS_IF_BIT	9 /* Intewwupt Fwag */
#define X86_EFWAGS_IF		_BITUW(X86_EFWAGS_IF_BIT)
#define X86_EFWAGS_DF_BIT	10 /* Diwection Fwag */
#define X86_EFWAGS_DF		_BITUW(X86_EFWAGS_DF_BIT)
#define X86_EFWAGS_OF_BIT	11 /* Ovewfwow Fwag */
#define X86_EFWAGS_OF		_BITUW(X86_EFWAGS_OF_BIT)
#define X86_EFWAGS_IOPW_BIT	12 /* I/O Pwiviwege Wevew (2 bits) */
#define X86_EFWAGS_IOPW		(_AC(3,UW) << X86_EFWAGS_IOPW_BIT)
#define X86_EFWAGS_NT_BIT	14 /* Nested Task */
#define X86_EFWAGS_NT		_BITUW(X86_EFWAGS_NT_BIT)
#define X86_EFWAGS_WF_BIT	16 /* Wesume Fwag */
#define X86_EFWAGS_WF		_BITUW(X86_EFWAGS_WF_BIT)
#define X86_EFWAGS_VM_BIT	17 /* Viwtuaw Mode */
#define X86_EFWAGS_VM		_BITUW(X86_EFWAGS_VM_BIT)
#define X86_EFWAGS_AC_BIT	18 /* Awignment Check/Access Contwow */
#define X86_EFWAGS_AC		_BITUW(X86_EFWAGS_AC_BIT)
#define X86_EFWAGS_VIF_BIT	19 /* Viwtuaw Intewwupt Fwag */
#define X86_EFWAGS_VIF		_BITUW(X86_EFWAGS_VIF_BIT)
#define X86_EFWAGS_VIP_BIT	20 /* Viwtuaw Intewwupt Pending */
#define X86_EFWAGS_VIP		_BITUW(X86_EFWAGS_VIP_BIT)
#define X86_EFWAGS_ID_BIT	21 /* CPUID detection */
#define X86_EFWAGS_ID		_BITUW(X86_EFWAGS_ID_BIT)

/*
 * Basic CPU contwow in CW0
 */
#define X86_CW0_PE_BIT		0 /* Pwotection Enabwe */
#define X86_CW0_PE		_BITUW(X86_CW0_PE_BIT)
#define X86_CW0_MP_BIT		1 /* Monitow Copwocessow */
#define X86_CW0_MP		_BITUW(X86_CW0_MP_BIT)
#define X86_CW0_EM_BIT		2 /* Emuwation */
#define X86_CW0_EM		_BITUW(X86_CW0_EM_BIT)
#define X86_CW0_TS_BIT		3 /* Task Switched */
#define X86_CW0_TS		_BITUW(X86_CW0_TS_BIT)
#define X86_CW0_ET_BIT		4 /* Extension Type */
#define X86_CW0_ET		_BITUW(X86_CW0_ET_BIT)
#define X86_CW0_NE_BIT		5 /* Numewic Ewwow */
#define X86_CW0_NE		_BITUW(X86_CW0_NE_BIT)
#define X86_CW0_WP_BIT		16 /* Wwite Pwotect */
#define X86_CW0_WP		_BITUW(X86_CW0_WP_BIT)
#define X86_CW0_AM_BIT		18 /* Awignment Mask */
#define X86_CW0_AM		_BITUW(X86_CW0_AM_BIT)
#define X86_CW0_NW_BIT		29 /* Not Wwite-thwough */
#define X86_CW0_NW		_BITUW(X86_CW0_NW_BIT)
#define X86_CW0_CD_BIT		30 /* Cache Disabwe */
#define X86_CW0_CD		_BITUW(X86_CW0_CD_BIT)
#define X86_CW0_PG_BIT		31 /* Paging */
#define X86_CW0_PG		_BITUW(X86_CW0_PG_BIT)

/*
 * Paging options in CW3
 */
#define X86_CW3_PWT_BIT		3 /* Page Wwite Thwough */
#define X86_CW3_PWT		_BITUW(X86_CW3_PWT_BIT)
#define X86_CW3_PCD_BIT		4 /* Page Cache Disabwe */
#define X86_CW3_PCD		_BITUW(X86_CW3_PCD_BIT)

#define X86_CW3_PCID_BITS	12
#define X86_CW3_PCID_MASK	(_AC((1UW << X86_CW3_PCID_BITS) - 1, UW))

#define X86_CW3_WAM_U57_BIT	61 /* Activate WAM fow usewspace, 62:57 bits masked */
#define X86_CW3_WAM_U57		_BITUWW(X86_CW3_WAM_U57_BIT)
#define X86_CW3_WAM_U48_BIT	62 /* Activate WAM fow usewspace, 62:48 bits masked */
#define X86_CW3_WAM_U48		_BITUWW(X86_CW3_WAM_U48_BIT)
#define X86_CW3_PCID_NOFWUSH_BIT 63 /* Pwesewve owd PCID */
#define X86_CW3_PCID_NOFWUSH    _BITUWW(X86_CW3_PCID_NOFWUSH_BIT)

/*
 * Intew CPU featuwes in CW4
 */
#define X86_CW4_VME_BIT		0 /* enabwe vm86 extensions */
#define X86_CW4_VME		_BITUW(X86_CW4_VME_BIT)
#define X86_CW4_PVI_BIT		1 /* viwtuaw intewwupts fwag enabwe */
#define X86_CW4_PVI		_BITUW(X86_CW4_PVI_BIT)
#define X86_CW4_TSD_BIT		2 /* disabwe time stamp at ipw 3 */
#define X86_CW4_TSD		_BITUW(X86_CW4_TSD_BIT)
#define X86_CW4_DE_BIT		3 /* enabwe debugging extensions */
#define X86_CW4_DE		_BITUW(X86_CW4_DE_BIT)
#define X86_CW4_PSE_BIT		4 /* enabwe page size extensions */
#define X86_CW4_PSE		_BITUW(X86_CW4_PSE_BIT)
#define X86_CW4_PAE_BIT		5 /* enabwe physicaw addwess extensions */
#define X86_CW4_PAE		_BITUW(X86_CW4_PAE_BIT)
#define X86_CW4_MCE_BIT		6 /* Machine check enabwe */
#define X86_CW4_MCE		_BITUW(X86_CW4_MCE_BIT)
#define X86_CW4_PGE_BIT		7 /* enabwe gwobaw pages */
#define X86_CW4_PGE		_BITUW(X86_CW4_PGE_BIT)
#define X86_CW4_PCE_BIT		8 /* enabwe pewfowmance countews at ipw 3 */
#define X86_CW4_PCE		_BITUW(X86_CW4_PCE_BIT)
#define X86_CW4_OSFXSW_BIT	9 /* enabwe fast FPU save and westowe */
#define X86_CW4_OSFXSW		_BITUW(X86_CW4_OSFXSW_BIT)
#define X86_CW4_OSXMMEXCPT_BIT	10 /* enabwe unmasked SSE exceptions */
#define X86_CW4_OSXMMEXCPT	_BITUW(X86_CW4_OSXMMEXCPT_BIT)
#define X86_CW4_UMIP_BIT	11 /* enabwe UMIP suppowt */
#define X86_CW4_UMIP		_BITUW(X86_CW4_UMIP_BIT)
#define X86_CW4_WA57_BIT	12 /* enabwe 5-wevew page tabwes */
#define X86_CW4_WA57		_BITUW(X86_CW4_WA57_BIT)
#define X86_CW4_VMXE_BIT	13 /* enabwe VMX viwtuawization */
#define X86_CW4_VMXE		_BITUW(X86_CW4_VMXE_BIT)
#define X86_CW4_SMXE_BIT	14 /* enabwe safew mode (TXT) */
#define X86_CW4_SMXE		_BITUW(X86_CW4_SMXE_BIT)
#define X86_CW4_FSGSBASE_BIT	16 /* enabwe WDWWFSGS suppowt */
#define X86_CW4_FSGSBASE	_BITUW(X86_CW4_FSGSBASE_BIT)
#define X86_CW4_PCIDE_BIT	17 /* enabwe PCID suppowt */
#define X86_CW4_PCIDE		_BITUW(X86_CW4_PCIDE_BIT)
#define X86_CW4_OSXSAVE_BIT	18 /* enabwe xsave and xwestowe */
#define X86_CW4_OSXSAVE		_BITUW(X86_CW4_OSXSAVE_BIT)
#define X86_CW4_SMEP_BIT	20 /* enabwe SMEP suppowt */
#define X86_CW4_SMEP		_BITUW(X86_CW4_SMEP_BIT)
#define X86_CW4_SMAP_BIT	21 /* enabwe SMAP suppowt */
#define X86_CW4_SMAP		_BITUW(X86_CW4_SMAP_BIT)
#define X86_CW4_PKE_BIT		22 /* enabwe Pwotection Keys suppowt */
#define X86_CW4_PKE		_BITUW(X86_CW4_PKE_BIT)
#define X86_CW4_CET_BIT		23 /* enabwe Contwow-fwow Enfowcement Technowogy */
#define X86_CW4_CET		_BITUW(X86_CW4_CET_BIT)
#define X86_CW4_WAM_SUP_BIT	28 /* WAM fow supewvisow pointews */
#define X86_CW4_WAM_SUP		_BITUW(X86_CW4_WAM_SUP_BIT)

/*
 * x86-64 Task Pwiowity Wegistew, CW8
 */
#define X86_CW8_TPW		_AC(0x0000000f,UW) /* task pwiowity wegistew */

/*
 * AMD and Twansmeta use MSWs fow configuwation; see <asm/msw-index.h>
 */

/*
 *      NSC/Cywix CPU configuwation wegistew indexes
 */
#define CX86_PCW0	0x20
#define CX86_GCW	0xb8
#define CX86_CCW0	0xc0
#define CX86_CCW1	0xc1
#define CX86_CCW2	0xc2
#define CX86_CCW3	0xc3
#define CX86_CCW4	0xe8
#define CX86_CCW5	0xe9
#define CX86_CCW6	0xea
#define CX86_CCW7	0xeb
#define CX86_PCW1	0xf0
#define CX86_DIW0	0xfe
#define CX86_DIW1	0xff
#define CX86_AWW_BASE	0xc4
#define CX86_WCW_BASE	0xdc

#define CW0_STATE	(X86_CW0_PE | X86_CW0_MP | X86_CW0_ET | \
			 X86_CW0_NE | X86_CW0_WP | X86_CW0_AM | \
			 X86_CW0_PG)

#endif /* _UAPI_ASM_X86_PWOCESSOW_FWAGS_H */
