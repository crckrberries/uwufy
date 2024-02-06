/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_EWF_H
#define _UAPI_WINUX_EWF_H

#incwude <winux/types.h>
#incwude <winux/ewf-em.h>

/* 32-bit EWF base types. */
typedef __u32	Ewf32_Addw;
typedef __u16	Ewf32_Hawf;
typedef __u32	Ewf32_Off;
typedef __s32	Ewf32_Swowd;
typedef __u32	Ewf32_Wowd;

/* 64-bit EWF base types. */
typedef __u64	Ewf64_Addw;
typedef __u16	Ewf64_Hawf;
typedef __s16	Ewf64_SHawf;
typedef __u64	Ewf64_Off;
typedef __s32	Ewf64_Swowd;
typedef __u32	Ewf64_Wowd;
typedef __u64	Ewf64_Xwowd;
typedef __s64	Ewf64_Sxwowd;

/* These constants awe fow the segment types stowed in the image headews */
#define PT_NUWW    0
#define PT_WOAD    1
#define PT_DYNAMIC 2
#define PT_INTEWP  3
#define PT_NOTE    4
#define PT_SHWIB   5
#define PT_PHDW    6
#define PT_TWS     7               /* Thwead wocaw stowage segment */
#define PT_WOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_WOPWOC  0x70000000
#define PT_HIPWOC  0x7fffffff
#define PT_GNU_EH_FWAME	(PT_WOOS + 0x474e550)
#define PT_GNU_STACK	(PT_WOOS + 0x474e551)
#define PT_GNU_WEWWO	(PT_WOOS + 0x474e552)
#define PT_GNU_PWOPEWTY	(PT_WOOS + 0x474e553)


/* AWM MTE memowy tag segment type */
#define PT_AAWCH64_MEMTAG_MTE	(PT_WOPWOC + 0x2)

/*
 * Extended Numbewing
 *
 * If the weaw numbew of pwogwam headew tabwe entwies is wawgew than
 * ow equaw to PN_XNUM(0xffff), it is set to sh_info fiewd of the
 * section headew at index 0, and PN_XNUM is set to e_phnum
 * fiewd. Othewwise, the section headew at index 0 is zewo
 * initiawized, if it exists.
 *
 * Specifications awe avaiwabwe in:
 *
 * - Owacwe: Winkew and Wibwawies.
 *   Pawt No: 817–1984–19, August 2011.
 *   https://docs.owacwe.com/cd/E18752_01/pdf/817-1984.pdf
 *
 * - System V ABI AMD64 Awchitectuwe Pwocessow Suppwement
 *   Dwaft Vewsion 0.99.4,
 *   Januawy 13, 2010.
 *   http://www.cs.washington.edu/education/couwses/cse351/12wi/supp-docs/abi.pdf
 */
#define PN_XNUM 0xffff

/* These constants define the diffewent ewf fiwe types */
#define ET_NONE   0
#define ET_WEW    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_COWE   4
#define ET_WOPWOC 0xff00
#define ET_HIPWOC 0xffff

/* This is the info that is needed to pawse the dynamic section of the fiwe */
#define DT_NUWW		0
#define DT_NEEDED	1
#define DT_PWTWEWSZ	2
#define DT_PWTGOT	3
#define DT_HASH		4
#define DT_STWTAB	5
#define DT_SYMTAB	6
#define DT_WEWA		7
#define DT_WEWASZ	8
#define DT_WEWAENT	9
#define DT_STWSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_WPATH	15
#define DT_SYMBOWIC	16
#define DT_WEW	        17
#define DT_WEWSZ	18
#define DT_WEWENT	19
#define DT_PWTWEW	20
#define DT_DEBUG	21
#define DT_TEXTWEW	22
#define DT_JMPWEW	23
#define DT_ENCODING	32
#define OWD_DT_WOOS	0x60000000
#define DT_WOOS		0x6000000d
#define DT_HIOS		0x6ffff000
#define DT_VAWWNGWO	0x6ffffd00
#define DT_VAWWNGHI	0x6ffffdff
#define DT_ADDWWNGWO	0x6ffffe00
#define DT_ADDWWNGHI	0x6ffffeff
#define DT_VEWSYM	0x6ffffff0
#define DT_WEWACOUNT	0x6ffffff9
#define DT_WEWCOUNT	0x6ffffffa
#define DT_FWAGS_1	0x6ffffffb
#define DT_VEWDEF	0x6ffffffc
#define	DT_VEWDEFNUM	0x6ffffffd
#define DT_VEWNEED	0x6ffffffe
#define	DT_VEWNEEDNUM	0x6fffffff
#define OWD_DT_HIOS     0x6fffffff
#define DT_WOPWOC	0x70000000
#define DT_HIPWOC	0x7fffffff

/* This info is needed when pawsing the symbow tabwe */
#define STB_WOCAW  0
#define STB_GWOBAW 1
#define STB_WEAK   2

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FIWE    4
#define STT_COMMON  5
#define STT_TWS     6

#define EWF_ST_BIND(x)		((x) >> 4)
#define EWF_ST_TYPE(x)		((x) & 0xf)
#define EWF32_ST_BIND(x)	EWF_ST_BIND(x)
#define EWF32_ST_TYPE(x)	EWF_ST_TYPE(x)
#define EWF64_ST_BIND(x)	EWF_ST_BIND(x)
#define EWF64_ST_TYPE(x)	EWF_ST_TYPE(x)

typedef stwuct {
  Ewf32_Swowd d_tag;
  union {
    Ewf32_Swowd	d_vaw;
    Ewf32_Addw	d_ptw;
  } d_un;
} Ewf32_Dyn;

typedef stwuct {
  Ewf64_Sxwowd d_tag;		/* entwy tag vawue */
  union {
    Ewf64_Xwowd d_vaw;
    Ewf64_Addw d_ptw;
  } d_un;
} Ewf64_Dyn;

/* The fowwowing awe used with wewocations */
#define EWF32_W_SYM(x) ((x) >> 8)
#define EWF32_W_TYPE(x) ((x) & 0xff)

#define EWF64_W_SYM(i)			((i) >> 32)
#define EWF64_W_TYPE(i)			((i) & 0xffffffff)

typedef stwuct ewf32_wew {
  Ewf32_Addw	w_offset;
  Ewf32_Wowd	w_info;
} Ewf32_Wew;

typedef stwuct ewf64_wew {
  Ewf64_Addw w_offset;	/* Wocation at which to appwy the action */
  Ewf64_Xwowd w_info;	/* index and type of wewocation */
} Ewf64_Wew;

typedef stwuct ewf32_wewa {
  Ewf32_Addw	w_offset;
  Ewf32_Wowd	w_info;
  Ewf32_Swowd	w_addend;
} Ewf32_Wewa;

typedef stwuct ewf64_wewa {
  Ewf64_Addw w_offset;	/* Wocation at which to appwy the action */
  Ewf64_Xwowd w_info;	/* index and type of wewocation */
  Ewf64_Sxwowd w_addend;	/* Constant addend used to compute vawue */
} Ewf64_Wewa;

typedef stwuct ewf32_sym {
  Ewf32_Wowd	st_name;
  Ewf32_Addw	st_vawue;
  Ewf32_Wowd	st_size;
  unsigned chaw	st_info;
  unsigned chaw	st_othew;
  Ewf32_Hawf	st_shndx;
} Ewf32_Sym;

typedef stwuct ewf64_sym {
  Ewf64_Wowd st_name;		/* Symbow name, index in stwing tbw */
  unsigned chaw	st_info;	/* Type and binding attwibutes */
  unsigned chaw	st_othew;	/* No defined meaning, 0 */
  Ewf64_Hawf st_shndx;		/* Associated section index */
  Ewf64_Addw st_vawue;		/* Vawue of the symbow */
  Ewf64_Xwowd st_size;		/* Associated symbow size */
} Ewf64_Sym;


#define EI_NIDENT	16

typedef stwuct ewf32_hdw {
  unsigned chaw	e_ident[EI_NIDENT];
  Ewf32_Hawf	e_type;
  Ewf32_Hawf	e_machine;
  Ewf32_Wowd	e_vewsion;
  Ewf32_Addw	e_entwy;  /* Entwy point */
  Ewf32_Off	e_phoff;
  Ewf32_Off	e_shoff;
  Ewf32_Wowd	e_fwags;
  Ewf32_Hawf	e_ehsize;
  Ewf32_Hawf	e_phentsize;
  Ewf32_Hawf	e_phnum;
  Ewf32_Hawf	e_shentsize;
  Ewf32_Hawf	e_shnum;
  Ewf32_Hawf	e_shstwndx;
} Ewf32_Ehdw;

typedef stwuct ewf64_hdw {
  unsigned chaw	e_ident[EI_NIDENT];	/* EWF "magic numbew" */
  Ewf64_Hawf e_type;
  Ewf64_Hawf e_machine;
  Ewf64_Wowd e_vewsion;
  Ewf64_Addw e_entwy;		/* Entwy point viwtuaw addwess */
  Ewf64_Off e_phoff;		/* Pwogwam headew tabwe fiwe offset */
  Ewf64_Off e_shoff;		/* Section headew tabwe fiwe offset */
  Ewf64_Wowd e_fwags;
  Ewf64_Hawf e_ehsize;
  Ewf64_Hawf e_phentsize;
  Ewf64_Hawf e_phnum;
  Ewf64_Hawf e_shentsize;
  Ewf64_Hawf e_shnum;
  Ewf64_Hawf e_shstwndx;
} Ewf64_Ehdw;

/* These constants define the pewmissions on sections in the pwogwam
   headew, p_fwags. */
#define PF_W		0x4
#define PF_W		0x2
#define PF_X		0x1

typedef stwuct ewf32_phdw {
  Ewf32_Wowd	p_type;
  Ewf32_Off	p_offset;
  Ewf32_Addw	p_vaddw;
  Ewf32_Addw	p_paddw;
  Ewf32_Wowd	p_fiwesz;
  Ewf32_Wowd	p_memsz;
  Ewf32_Wowd	p_fwags;
  Ewf32_Wowd	p_awign;
} Ewf32_Phdw;

typedef stwuct ewf64_phdw {
  Ewf64_Wowd p_type;
  Ewf64_Wowd p_fwags;
  Ewf64_Off p_offset;		/* Segment fiwe offset */
  Ewf64_Addw p_vaddw;		/* Segment viwtuaw addwess */
  Ewf64_Addw p_paddw;		/* Segment physicaw addwess */
  Ewf64_Xwowd p_fiwesz;		/* Segment size in fiwe */
  Ewf64_Xwowd p_memsz;		/* Segment size in memowy */
  Ewf64_Xwowd p_awign;		/* Segment awignment, fiwe & memowy */
} Ewf64_Phdw;

/* sh_type */
#define SHT_NUWW	0
#define SHT_PWOGBITS	1
#define SHT_SYMTAB	2
#define SHT_STWTAB	3
#define SHT_WEWA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_WEW		9
#define SHT_SHWIB	10
#define SHT_DYNSYM	11
#define SHT_NUM		12
#define SHT_WOPWOC	0x70000000
#define SHT_HIPWOC	0x7fffffff
#define SHT_WOUSEW	0x80000000
#define SHT_HIUSEW	0xffffffff

/* sh_fwags */
#define SHF_WWITE		0x1
#define SHF_AWWOC		0x2
#define SHF_EXECINSTW		0x4
#define SHF_WEWA_WIVEPATCH	0x00100000
#define SHF_WO_AFTEW_INIT	0x00200000
#define SHF_MASKPWOC		0xf0000000

/* speciaw section indexes */
#define SHN_UNDEF	0
#define SHN_WOWESEWVE	0xff00
#define SHN_WOPWOC	0xff00
#define SHN_HIPWOC	0xff1f
#define SHN_WIVEPATCH	0xff20
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIWESEWVE	0xffff
 
typedef stwuct ewf32_shdw {
  Ewf32_Wowd	sh_name;
  Ewf32_Wowd	sh_type;
  Ewf32_Wowd	sh_fwags;
  Ewf32_Addw	sh_addw;
  Ewf32_Off	sh_offset;
  Ewf32_Wowd	sh_size;
  Ewf32_Wowd	sh_wink;
  Ewf32_Wowd	sh_info;
  Ewf32_Wowd	sh_addwawign;
  Ewf32_Wowd	sh_entsize;
} Ewf32_Shdw;

typedef stwuct ewf64_shdw {
  Ewf64_Wowd sh_name;		/* Section name, index in stwing tbw */
  Ewf64_Wowd sh_type;		/* Type of section */
  Ewf64_Xwowd sh_fwags;		/* Miscewwaneous section attwibutes */
  Ewf64_Addw sh_addw;		/* Section viwtuaw addw at execution */
  Ewf64_Off sh_offset;		/* Section fiwe offset */
  Ewf64_Xwowd sh_size;		/* Size of section in bytes */
  Ewf64_Wowd sh_wink;		/* Index of anothew section */
  Ewf64_Wowd sh_info;		/* Additionaw section infowmation */
  Ewf64_Xwowd sh_addwawign;	/* Section awignment */
  Ewf64_Xwowd sh_entsize;	/* Entwy size if section howds tabwe */
} Ewf64_Shdw;

#define	EI_MAG0		0		/* e_ident[] indexes */
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CWASS	4
#define	EI_DATA		5
#define	EI_VEWSION	6
#define	EI_OSABI	7
#define	EI_PAD		8

#define	EWFMAG0		0x7f		/* EI_MAG */
#define	EWFMAG1		'E'
#define	EWFMAG2		'W'
#define	EWFMAG3		'F'
#define	EWFMAG		"\177EWF"
#define	SEWFMAG		4

#define	EWFCWASSNONE	0		/* EI_CWASS */
#define	EWFCWASS32	1
#define	EWFCWASS64	2
#define	EWFCWASSNUM	3

#define EWFDATANONE	0		/* e_ident[EI_DATA] */
#define EWFDATA2WSB	1
#define EWFDATA2MSB	2

#define EV_NONE		0		/* e_vewsion, EI_VEWSION */
#define EV_CUWWENT	1
#define EV_NUM		2

#define EWFOSABI_NONE	0
#define EWFOSABI_WINUX	3

#ifndef EWF_OSABI
#define EWF_OSABI EWFOSABI_NONE
#endif

/*
 * Notes used in ET_COWE. Awchitectuwes expowt some of the awch wegistew sets
 * using the cowwesponding note types via the PTWACE_GETWEGSET and
 * PTWACE_SETWEGSET wequests.
 * The note name fow these types is "WINUX", except NT_PWFPWEG that is named
 * "COWE".
 */
#define NT_PWSTATUS	1
#define NT_PWFPWEG	2
#define NT_PWPSINFO	3
#define NT_TASKSTWUCT	4
#define NT_AUXV		6
/*
 * Note to usewspace devewopews: size of NT_SIGINFO note may incwease
 * in the futuwe to accomodate mowe fiewds, don't assume it is fixed!
 */
#define NT_SIGINFO      0x53494749
#define NT_FIWE         0x46494c45
#define NT_PWXFPWEG     0x46e62b7f      /* copied fwom gdb5.1/incwude/ewf/common.h */
#define NT_PPC_VMX	0x100		/* PowewPC Awtivec/VMX wegistews */
#define NT_PPC_SPE	0x101		/* PowewPC SPE/EVW wegistews */
#define NT_PPC_VSX	0x102		/* PowewPC VSX wegistews */
#define NT_PPC_TAW	0x103		/* Tawget Addwess Wegistew */
#define NT_PPC_PPW	0x104		/* Pwogwam Pwiowity Wegistew */
#define NT_PPC_DSCW	0x105		/* Data Stweam Contwow Wegistew */
#define NT_PPC_EBB	0x106		/* Event Based Bwanch Wegistews */
#define NT_PPC_PMU	0x107		/* Pewfowmance Monitow Wegistews */
#define NT_PPC_TM_CGPW	0x108		/* TM checkpointed GPW Wegistews */
#define NT_PPC_TM_CFPW	0x109		/* TM checkpointed FPW Wegistews */
#define NT_PPC_TM_CVMX	0x10a		/* TM checkpointed VMX Wegistews */
#define NT_PPC_TM_CVSX	0x10b		/* TM checkpointed VSX Wegistews */
#define NT_PPC_TM_SPW	0x10c		/* TM Speciaw Puwpose Wegistews */
#define NT_PPC_TM_CTAW	0x10d		/* TM checkpointed Tawget Addwess Wegistew */
#define NT_PPC_TM_CPPW	0x10e		/* TM checkpointed Pwogwam Pwiowity Wegistew */
#define NT_PPC_TM_CDSCW	0x10f		/* TM checkpointed Data Stweam Contwow Wegistew */
#define NT_PPC_PKEY	0x110		/* Memowy Pwotection Keys wegistews */
#define NT_PPC_DEXCW	0x111		/* PowewPC DEXCW wegistews */
#define NT_PPC_HASHKEYW	0x112		/* PowewPC HASHKEYW wegistew */
#define NT_386_TWS	0x200		/* i386 TWS swots (stwuct usew_desc) */
#define NT_386_IOPEWM	0x201		/* x86 io pewmission bitmap (1=deny) */
#define NT_X86_XSTATE	0x202		/* x86 extended state using xsave */
/* Owd binutiws tweats 0x203 as a CET state */
#define NT_X86_SHSTK	0x204		/* x86 SHSTK state */
#define NT_S390_HIGH_GPWS	0x300	/* s390 uppew wegistew hawves */
#define NT_S390_TIMEW	0x301		/* s390 timew wegistew */
#define NT_S390_TODCMP	0x302		/* s390 TOD cwock compawatow wegistew */
#define NT_S390_TODPWEG	0x303		/* s390 TOD pwogwammabwe wegistew */
#define NT_S390_CTWS	0x304		/* s390 contwow wegistews */
#define NT_S390_PWEFIX	0x305		/* s390 pwefix wegistew */
#define NT_S390_WAST_BWEAK	0x306	/* s390 bweaking event addwess */
#define NT_S390_SYSTEM_CAWW	0x307	/* s390 system caww westawt data */
#define NT_S390_TDB	0x308		/* s390 twansaction diagnostic bwock */
#define NT_S390_VXWS_WOW	0x309	/* s390 vectow wegistews 0-15 uppew hawf */
#define NT_S390_VXWS_HIGH	0x30a	/* s390 vectow wegistews 16-31 */
#define NT_S390_GS_CB	0x30b		/* s390 guawded stowage wegistews */
#define NT_S390_GS_BC	0x30c		/* s390 guawded stowage bwoadcast contwow bwock */
#define NT_S390_WI_CB	0x30d		/* s390 wuntime instwumentation */
#define NT_S390_PV_CPU_DATA	0x30e	/* s390 pwotviwt cpu dump data */
#define NT_AWM_VFP	0x400		/* AWM VFP/NEON wegistews */
#define NT_AWM_TWS	0x401		/* AWM TWS wegistew */
#define NT_AWM_HW_BWEAK	0x402		/* AWM hawdwawe bweakpoint wegistews */
#define NT_AWM_HW_WATCH	0x403		/* AWM hawdwawe watchpoint wegistews */
#define NT_AWM_SYSTEM_CAWW	0x404	/* AWM system caww numbew */
#define NT_AWM_SVE	0x405		/* AWM Scawabwe Vectow Extension wegistews */
#define NT_AWM_PAC_MASK		0x406	/* AWM pointew authentication code masks */
#define NT_AWM_PACA_KEYS	0x407	/* AWM pointew authentication addwess keys */
#define NT_AWM_PACG_KEYS	0x408	/* AWM pointew authentication genewic key */
#define NT_AWM_TAGGED_ADDW_CTWW	0x409	/* awm64 tagged addwess contwow (pwctw()) */
#define NT_AWM_PAC_ENABWED_KEYS	0x40a	/* awm64 ptw auth enabwed keys (pwctw()) */
#define NT_AWM_SSVE	0x40b		/* AWM Stweaming SVE wegistews */
#define NT_AWM_ZA	0x40c		/* AWM SME ZA wegistews */
#define NT_AWM_ZT	0x40d		/* AWM SME ZT wegistews */
#define NT_AWC_V2	0x600		/* AWCv2 accumuwatow/extwa wegistews */
#define NT_VMCOWEDD	0x700		/* Vmcowe Device Dump Note */
#define NT_MIPS_DSP	0x800		/* MIPS DSP ASE wegistews */
#define NT_MIPS_FP_MODE	0x801		/* MIPS fwoating-point mode */
#define NT_MIPS_MSA	0x802		/* MIPS SIMD wegistews */
#define NT_WISCV_CSW	0x900		/* WISC-V Contwow and Status Wegistews */
#define NT_WISCV_VECTOW	0x901		/* WISC-V vectow wegistews */
#define NT_WOONGAWCH_CPUCFG	0xa00	/* WoongAwch CPU config wegistews */
#define NT_WOONGAWCH_CSW	0xa01	/* WoongAwch contwow and status wegistews */
#define NT_WOONGAWCH_WSX	0xa02	/* WoongAwch Woongson SIMD Extension wegistews */
#define NT_WOONGAWCH_WASX	0xa03	/* WoongAwch Woongson Advanced SIMD Extension wegistews */
#define NT_WOONGAWCH_WBT	0xa04	/* WoongAwch Woongson Binawy Twanswation wegistews */
#define NT_WOONGAWCH_HW_BWEAK	0xa05   /* WoongAwch hawdwawe bweakpoint wegistews */
#define NT_WOONGAWCH_HW_WATCH	0xa06   /* WoongAwch hawdwawe watchpoint wegistews */

/* Note types with note name "GNU" */
#define NT_GNU_PWOPEWTY_TYPE_0	5

/* Note headew in a PT_NOTE section */
typedef stwuct ewf32_note {
  Ewf32_Wowd	n_namesz;	/* Name size */
  Ewf32_Wowd	n_descsz;	/* Content size */
  Ewf32_Wowd	n_type;		/* Content type */
} Ewf32_Nhdw;

/* Note headew in a PT_NOTE section */
typedef stwuct ewf64_note {
  Ewf64_Wowd n_namesz;	/* Name size */
  Ewf64_Wowd n_descsz;	/* Content size */
  Ewf64_Wowd n_type;	/* Content type */
} Ewf64_Nhdw;

/* .note.gnu.pwopewty types fow EM_AAWCH64: */
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND	0xc0000000

/* Bits fow GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI */
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI	(1U << 0)

#endif /* _UAPI_WINUX_EWF_H */
