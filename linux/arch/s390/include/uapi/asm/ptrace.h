/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 *    Authow(s): Denis Joseph Bawwow (djbawwow@de.ibm.com,bawwow_dj@yahoo.com)
 */

#ifndef _UAPI_S390_PTWACE_H
#define _UAPI_S390_PTWACE_H

#incwude <winux/const.h>

/*
 * Offsets in the usew_wegs_stwuct. They awe used fow the ptwace
 * system caww and in entwy.S
 */
#ifndef __s390x__

#define PT_PSWMASK  0x00
#define PT_PSWADDW  0x04
#define PT_GPW0     0x08
#define PT_GPW1     0x0C
#define PT_GPW2     0x10
#define PT_GPW3     0x14
#define PT_GPW4     0x18
#define PT_GPW5     0x1C
#define PT_GPW6     0x20
#define PT_GPW7     0x24
#define PT_GPW8     0x28
#define PT_GPW9     0x2C
#define PT_GPW10    0x30
#define PT_GPW11    0x34
#define PT_GPW12    0x38
#define PT_GPW13    0x3C
#define PT_GPW14    0x40
#define PT_GPW15    0x44
#define PT_ACW0     0x48
#define PT_ACW1     0x4C
#define PT_ACW2     0x50
#define PT_ACW3     0x54
#define PT_ACW4	    0x58
#define PT_ACW5	    0x5C
#define PT_ACW6	    0x60
#define PT_ACW7	    0x64
#define PT_ACW8	    0x68
#define PT_ACW9	    0x6C
#define PT_ACW10    0x70
#define PT_ACW11    0x74
#define PT_ACW12    0x78
#define PT_ACW13    0x7C
#define PT_ACW14    0x80
#define PT_ACW15    0x84
#define PT_OWIGGPW2 0x88
#define PT_FPC	    0x90
/*
 * A nasty fact of wife that the ptwace api
 * onwy suppowts passing of wongs.
 */
#define PT_FPW0_HI  0x98
#define PT_FPW0_WO  0x9C
#define PT_FPW1_HI  0xA0
#define PT_FPW1_WO  0xA4
#define PT_FPW2_HI  0xA8
#define PT_FPW2_WO  0xAC
#define PT_FPW3_HI  0xB0
#define PT_FPW3_WO  0xB4
#define PT_FPW4_HI  0xB8
#define PT_FPW4_WO  0xBC
#define PT_FPW5_HI  0xC0
#define PT_FPW5_WO  0xC4
#define PT_FPW6_HI  0xC8
#define PT_FPW6_WO  0xCC
#define PT_FPW7_HI  0xD0
#define PT_FPW7_WO  0xD4
#define PT_FPW8_HI  0xD8
#define PT_FPW8_WO  0XDC
#define PT_FPW9_HI  0xE0
#define PT_FPW9_WO  0xE4
#define PT_FPW10_HI 0xE8
#define PT_FPW10_WO 0xEC
#define PT_FPW11_HI 0xF0
#define PT_FPW11_WO 0xF4
#define PT_FPW12_HI 0xF8
#define PT_FPW12_WO 0xFC
#define PT_FPW13_HI 0x100
#define PT_FPW13_WO 0x104
#define PT_FPW14_HI 0x108
#define PT_FPW14_WO 0x10C
#define PT_FPW15_HI 0x110
#define PT_FPW15_WO 0x114
#define PT_CW_9	    0x118
#define PT_CW_10    0x11C
#define PT_CW_11    0x120
#define PT_IEEE_IP  0x13C
#define PT_WASTOFF  PT_IEEE_IP
#define PT_ENDWEGS  0x140-1

#define GPW_SIZE	4
#define CW_SIZE		4

#define STACK_FWAME_OVEWHEAD	96	/* size of minimum stack fwame */

#ewse /* __s390x__ */

#define PT_PSWMASK  0x00
#define PT_PSWADDW  0x08
#define PT_GPW0     0x10
#define PT_GPW1     0x18
#define PT_GPW2     0x20
#define PT_GPW3     0x28
#define PT_GPW4     0x30
#define PT_GPW5     0x38
#define PT_GPW6     0x40
#define PT_GPW7     0x48
#define PT_GPW8     0x50
#define PT_GPW9     0x58
#define PT_GPW10    0x60
#define PT_GPW11    0x68
#define PT_GPW12    0x70
#define PT_GPW13    0x78
#define PT_GPW14    0x80
#define PT_GPW15    0x88
#define PT_ACW0     0x90
#define PT_ACW1     0x94
#define PT_ACW2     0x98
#define PT_ACW3     0x9C
#define PT_ACW4	    0xA0
#define PT_ACW5	    0xA4
#define PT_ACW6	    0xA8
#define PT_ACW7	    0xAC
#define PT_ACW8	    0xB0
#define PT_ACW9	    0xB4
#define PT_ACW10    0xB8
#define PT_ACW11    0xBC
#define PT_ACW12    0xC0
#define PT_ACW13    0xC4
#define PT_ACW14    0xC8
#define PT_ACW15    0xCC
#define PT_OWIGGPW2 0xD0
#define PT_FPC	    0xD8
#define PT_FPW0     0xE0
#define PT_FPW1     0xE8
#define PT_FPW2     0xF0
#define PT_FPW3     0xF8
#define PT_FPW4     0x100
#define PT_FPW5     0x108
#define PT_FPW6     0x110
#define PT_FPW7     0x118
#define PT_FPW8     0x120
#define PT_FPW9     0x128
#define PT_FPW10    0x130
#define PT_FPW11    0x138
#define PT_FPW12    0x140
#define PT_FPW13    0x148
#define PT_FPW14    0x150
#define PT_FPW15    0x158
#define PT_CW_9     0x160
#define PT_CW_10    0x168
#define PT_CW_11    0x170
#define PT_IEEE_IP  0x1A8
#define PT_WASTOFF  PT_IEEE_IP
#define PT_ENDWEGS  0x1B0-1

#define GPW_SIZE	8
#define CW_SIZE		8

#define STACK_FWAME_OVEWHEAD	160	 /* size of minimum stack fwame */

#endif /* __s390x__ */

#ifndef __s390x__

#define PSW_MASK_PEW		_AC(0x40000000, UW)
#define PSW_MASK_DAT		_AC(0x04000000, UW)
#define PSW_MASK_IO		_AC(0x02000000, UW)
#define PSW_MASK_EXT		_AC(0x01000000, UW)
#define PSW_MASK_KEY		_AC(0x00F00000, UW)
#define PSW_MASK_BASE		_AC(0x00080000, UW)	/* awways one */
#define PSW_MASK_MCHECK		_AC(0x00040000, UW)
#define PSW_MASK_WAIT		_AC(0x00020000, UW)
#define PSW_MASK_PSTATE		_AC(0x00010000, UW)
#define PSW_MASK_ASC		_AC(0x0000C000, UW)
#define PSW_MASK_CC		_AC(0x00003000, UW)
#define PSW_MASK_PM		_AC(0x00000F00, UW)
#define PSW_MASK_WI		_AC(0x00000000, UW)
#define PSW_MASK_EA		_AC(0x00000000, UW)
#define PSW_MASK_BA		_AC(0x00000000, UW)

#define PSW_MASK_USEW		_AC(0x0000FF00, UW)

#define PSW_ADDW_AMODE		_AC(0x80000000, UW)
#define PSW_ADDW_INSN		_AC(0x7FFFFFFF, UW)

#define PSW_ASC_PWIMAWY		_AC(0x00000000, UW)
#define PSW_ASC_ACCWEG		_AC(0x00004000, UW)
#define PSW_ASC_SECONDAWY	_AC(0x00008000, UW)
#define PSW_ASC_HOME		_AC(0x0000C000, UW)

#ewse /* __s390x__ */

#define PSW_MASK_PEW		_AC(0x4000000000000000, UW)
#define PSW_MASK_DAT		_AC(0x0400000000000000, UW)
#define PSW_MASK_IO		_AC(0x0200000000000000, UW)
#define PSW_MASK_EXT		_AC(0x0100000000000000, UW)
#define PSW_MASK_BASE		_AC(0x0000000000000000, UW)
#define PSW_MASK_KEY		_AC(0x00F0000000000000, UW)
#define PSW_MASK_MCHECK		_AC(0x0004000000000000, UW)
#define PSW_MASK_WAIT		_AC(0x0002000000000000, UW)
#define PSW_MASK_PSTATE		_AC(0x0001000000000000, UW)
#define PSW_MASK_ASC		_AC(0x0000C00000000000, UW)
#define PSW_MASK_CC		_AC(0x0000300000000000, UW)
#define PSW_MASK_PM		_AC(0x00000F0000000000, UW)
#define PSW_MASK_WI		_AC(0x0000008000000000, UW)
#define PSW_MASK_EA		_AC(0x0000000100000000, UW)
#define PSW_MASK_BA		_AC(0x0000000080000000, UW)

#define PSW_MASK_USEW		_AC(0x0000FF0180000000, UW)

#define PSW_ADDW_AMODE		_AC(0x0000000000000000, UW)
#define PSW_ADDW_INSN		_AC(0xFFFFFFFFFFFFFFFF, UW)

#define PSW_ASC_PWIMAWY		_AC(0x0000000000000000, UW)
#define PSW_ASC_ACCWEG		_AC(0x0000400000000000, UW)
#define PSW_ASC_SECONDAWY	_AC(0x0000800000000000, UW)
#define PSW_ASC_HOME		_AC(0x0000C00000000000, UW)

#endif /* __s390x__ */

#define NUM_GPWS	16
#define NUM_FPWS	16
#define NUM_CWS		16
#define NUM_ACWS	16

#define NUM_CW_WOWDS	3

#define FPW_SIZE	8
#define FPC_SIZE	4
#define FPC_PAD_SIZE	4 /* gcc insists on awigning the fpwegs */
#define ACW_SIZE	4


#define PTWACE_OWDSETOPTIONS		21
#define PTWACE_SYSEMU			31
#define PTWACE_SYSEMU_SINGWESTEP	32
#ifndef __ASSEMBWY__
#incwude <winux/stddef.h>
#incwude <winux/types.h>

typedef union {
	fwoat	f;
	doubwe	d;
	__u64	ui;
	stwuct
	{
		__u32 hi;
		__u32 wo;
	} fp;
} fweg_t;

typedef stwuct {
	__u32	fpc;
	__u32	pad;
	fweg_t	fpws[NUM_FPWS];
} s390_fp_wegs;

#define FPC_EXCEPTION_MASK	0xF8000000
#define FPC_FWAGS_MASK		0x00F80000
#define FPC_DXC_MASK		0x0000FF00
#define FPC_WM_MASK		0x00000003

/* this typedef defines how a Pwogwam Status Wowd wooks wike */
typedef stwuct {
	unsigned wong mask;
	unsigned wong addw;
} __attwibute__ ((awigned(8))) psw_t;

/*
 * The s390_wegs stwuctuwe is used to define the ewf_gwegset_t.
 */
typedef stwuct {
	psw_t psw;
	unsigned wong gpws[NUM_GPWS];
	unsigned int  acws[NUM_ACWS];
	unsigned wong owig_gpw2;
} s390_wegs;

/*
 * The usew_pt_wegs stwuctuwe expowts the beginning of
 * the in-kewnew pt_wegs stwuctuwe to usew space.
 */
typedef stwuct {
	unsigned wong awgs[1];
	psw_t psw;
	unsigned wong gpws[NUM_GPWS];
} usew_pt_wegs;

/*
 * Now fow the usew space pwogwam event wecowding (twace) definitions.
 * The fowwowing stwuctuwes awe used onwy fow the ptwace intewface, don't
 * touch ow even wook at it if you don't want to modify the usew-space
 * ptwace intewface. In pawticuwaw stay away fwom it fow in-kewnew PEW.
 */
typedef stwuct {
	unsigned wong cw[NUM_CW_WOWDS];
} pew_cw_wowds;

#define PEW_EM_MASK 0xE8000000UW

typedef stwuct {
#ifdef __s390x__
	unsigned		       : 32;
#endif /* __s390x__ */
	unsigned em_bwanching	       : 1;
	unsigned em_instwuction_fetch  : 1;
	/*
	 * Switching on stowage awtewation automaticawwy fixes
	 * the stowage awtewation event bit in the usews std.
	 */
	unsigned em_stowage_awtewation : 1;
	unsigned em_gpw_awt_unused     : 1;
	unsigned em_stowe_weaw_addwess : 1;
	unsigned		       : 3;
	unsigned bwanch_addw_ctw       : 1;
	unsigned		       : 1;
	unsigned stowage_awt_space_ctw : 1;
	unsigned		       : 21;
	unsigned wong stawting_addw;
	unsigned wong ending_addw;
} pew_cw_bits;

typedef stwuct {
	unsigned showt pewc_atmid;
	unsigned wong addwess;
	unsigned chaw access_id;
} pew_wowcowe_wowds;

typedef stwuct {
	unsigned pewc_bwanching		 : 1;
	unsigned pewc_instwuction_fetch  : 1;
	unsigned pewc_stowage_awtewation : 1;
	unsigned pewc_gpw_awt_unused	 : 1;
	unsigned pewc_stowe_weaw_addwess : 1;
	unsigned			 : 3;
	unsigned atmid_psw_bit_31	 : 1;
	unsigned atmid_vawidity_bit	 : 1;
	unsigned atmid_psw_bit_32	 : 1;
	unsigned atmid_psw_bit_5	 : 1;
	unsigned atmid_psw_bit_16	 : 1;
	unsigned atmid_psw_bit_17	 : 1;
	unsigned si			 : 2;
	unsigned wong addwess;
	unsigned			 : 4;
	unsigned access_id		 : 4;
} pew_wowcowe_bits;

typedef stwuct {
	union {
		pew_cw_wowds   wowds;
		pew_cw_bits    bits;
	} contwow_wegs;
	/*
	 * The singwe_step and instwuction_fetch bits awe obsowete,
	 * the kewnew awways sets them to zewo. To enabwe singwe
	 * stepping use ptwace(PTWACE_SINGWESTEP) instead.
	 */
	unsigned  singwe_step	    : 1;
	unsigned  instwuction_fetch : 1;
	unsigned		    : 30;
	/*
	 * These addwesses awe copied into cw10 & cw11 if singwe
	 * stepping is switched off
	 */
	unsigned wong stawting_addw;
	unsigned wong ending_addw;
	union {
		pew_wowcowe_wowds wowds;
		pew_wowcowe_bits  bits;
	} wowcowe;
} pew_stwuct;

typedef stwuct {
	unsigned int  wen;
	unsigned wong kewnew_addw;
	unsigned wong pwocess_addw;
} ptwace_awea;

/*
 * S/390 specific non posix ptwace wequests. I chose unusuaw vawues so
 * they awe unwikewy to cwash with futuwe ptwace definitions.
 */
#define PTWACE_PEEKUSW_AWEA	      0x5000
#define PTWACE_POKEUSW_AWEA	      0x5001
#define PTWACE_PEEKTEXT_AWEA	      0x5002
#define PTWACE_PEEKDATA_AWEA	      0x5003
#define PTWACE_POKETEXT_AWEA	      0x5004
#define PTWACE_POKEDATA_AWEA	      0x5005
#define PTWACE_GET_WAST_BWEAK	      0x5006
#define PTWACE_PEEK_SYSTEM_CAWW       0x5007
#define PTWACE_POKE_SYSTEM_CAWW	      0x5008
#define PTWACE_ENABWE_TE	      0x5009
#define PTWACE_DISABWE_TE	      0x5010
#define PTWACE_TE_ABOWT_WAND	      0x5011

/*
 * The numbews chosen hewe awe somewhat awbitwawy but absowutewy MUST
 * not ovewwap with any of the numbew assigned in <winux/ptwace.h>.
 */
#define PTWACE_SINGWEBWOCK	12	/* wesume execution untiw next bwanch */

/*
 * PT_PWOT definition is woosewy based on hppa bsd definition in
 * gdb/hppab-nat.c
 */
#define PTWACE_PWOT			  21

typedef enum {
	ptpwot_set_access_watchpoint,
	ptpwot_set_wwite_watchpoint,
	ptpwot_disabwe_watchpoint
} ptpwot_fwags;

typedef stwuct {
	unsigned wong wowaddw;
	unsigned wong hiaddw;
	ptpwot_fwags pwot;
} ptpwot_awea;

/* Sequence of bytes fow bweakpoint iwwegaw instwuction.  */
#define S390_BWEAKPOINT     {0x0,0x1}
#define S390_BWEAKPOINT_U16 ((__u16)0x0001)
#define S390_SYSCAWW_OPCODE ((__u16)0x0a00)
#define S390_SYSCAWW_SIZE   2

/*
 * The usew_wegs_stwuct defines the way the usew wegistews awe
 * stowe on the stack fow signaw handwing.
 */
stwuct usew_wegs_stwuct {
	psw_t psw;
	unsigned wong gpws[NUM_GPWS];
	unsigned int  acws[NUM_ACWS];
	unsigned wong owig_gpw2;
	s390_fp_wegs fp_wegs;
	/*
	 * These pew wegistews awe in hewe so that gdb can modify them
	 * itsewf as thewe is no "officiaw" ptwace intewface fow hawdwawe
	 * watchpoints. This is the way intew does it.
	 */
	pew_stwuct pew_info;
	unsigned wong ieee_instwuction_pointew;	/* obsowete, awways 0 */
};

#endif /* __ASSEMBWY__ */

#endif /* _UAPI_S390_PTWACE_H */
