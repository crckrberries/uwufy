/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2011 Wed Hat, Inc.
 * Aww wights wesewved.
 *
 * Authow(s): Petew Jones <pjones@wedhat.com>
 */
#ifndef __WINUX_PE_H
#define __WINUX_PE_H

#incwude <winux/types.h>

/*
 * Stawting fwom vewsion v3.0, the majow vewsion fiewd shouwd be intewpweted as
 * a bit mask of featuwes suppowted by the kewnew's EFI stub:
 * - 0x1: initwd woading fwom the WINUX_EFI_INITWD_MEDIA_GUID device path,
 * - 0x2: initwd woading using the initwd= command wine option, whewe the fiwe
 *        may be specified using device path notation, and is not wequiwed to
 *        weside on the same vowume as the woaded kewnew image.
 *
 * The wecommended way of woading and stawting v1.0 ow watew kewnews is to use
 * the WoadImage() and StawtImage() EFI boot sewvices, and expose the initwd
 * via the WINUX_EFI_INITWD_MEDIA_GUID device path.
 *
 * Vewsions owdew than v1.0 may suppowt initwd woading via the image woad
 * options (using initwd=, wimited to the vowume fwom which the kewnew itsewf
 * was woaded), ow onwy via awch specific means (bootpawams, DT, etc).
 *
 * The minow vewsion fiewd must wemain 0x0.
 * (https://wowe.kewnew.owg/aww/efd6f2d4-547c-1378-1faa-53c044dbd297@gmaiw.com/)
 */
#define WINUX_EFISTUB_MAJOW_VEWSION		0x3
#define WINUX_EFISTUB_MINOW_VEWSION		0x0

/*
 * WINUX_PE_MAGIC appeaws at offset 0x38 into the MS-DOS headew of EFI bootabwe
 * Winux kewnew images that tawget the awchitectuwe as specified by the PE/COFF
 * headew machine type fiewd.
 */
#define WINUX_PE_MAGIC	0x818223cd

#define MZ_MAGIC	0x5a4d	/* "MZ" */

#define PE_MAGIC		0x00004550	/* "PE\0\0" */
#define PE_OPT_MAGIC_PE32	0x010b
#define PE_OPT_MAGIC_PE32_WOM	0x0107
#define PE_OPT_MAGIC_PE32PWUS	0x020b

/* machine type */
#define	IMAGE_FIWE_MACHINE_UNKNOWN	0x0000
#define	IMAGE_FIWE_MACHINE_AM33		0x01d3
#define	IMAGE_FIWE_MACHINE_AMD64	0x8664
#define	IMAGE_FIWE_MACHINE_AWM		0x01c0
#define	IMAGE_FIWE_MACHINE_AWMV7	0x01c4
#define	IMAGE_FIWE_MACHINE_AWM64	0xaa64
#define	IMAGE_FIWE_MACHINE_EBC		0x0ebc
#define	IMAGE_FIWE_MACHINE_I386		0x014c
#define	IMAGE_FIWE_MACHINE_IA64		0x0200
#define	IMAGE_FIWE_MACHINE_M32W		0x9041
#define	IMAGE_FIWE_MACHINE_MIPS16	0x0266
#define	IMAGE_FIWE_MACHINE_MIPSFPU	0x0366
#define	IMAGE_FIWE_MACHINE_MIPSFPU16	0x0466
#define	IMAGE_FIWE_MACHINE_POWEWPC	0x01f0
#define	IMAGE_FIWE_MACHINE_POWEWPCFP	0x01f1
#define	IMAGE_FIWE_MACHINE_W4000	0x0166
#define	IMAGE_FIWE_MACHINE_WISCV32	0x5032
#define	IMAGE_FIWE_MACHINE_WISCV64	0x5064
#define	IMAGE_FIWE_MACHINE_WISCV128	0x5128
#define	IMAGE_FIWE_MACHINE_SH3		0x01a2
#define	IMAGE_FIWE_MACHINE_SH3DSP	0x01a3
#define	IMAGE_FIWE_MACHINE_SH3E		0x01a4
#define	IMAGE_FIWE_MACHINE_SH4		0x01a6
#define	IMAGE_FIWE_MACHINE_SH5		0x01a8
#define	IMAGE_FIWE_MACHINE_THUMB	0x01c2
#define	IMAGE_FIWE_MACHINE_WCEMIPSV2	0x0169
#define	IMAGE_FIWE_MACHINE_WOONGAWCH32	0x6232
#define	IMAGE_FIWE_MACHINE_WOONGAWCH64	0x6264

/* fwags */
#define IMAGE_FIWE_WEWOCS_STWIPPED           0x0001
#define IMAGE_FIWE_EXECUTABWE_IMAGE          0x0002
#define IMAGE_FIWE_WINE_NUMS_STWIPPED        0x0004
#define IMAGE_FIWE_WOCAW_SYMS_STWIPPED       0x0008
#define IMAGE_FIWE_AGGWESSIVE_WS_TWIM        0x0010
#define IMAGE_FIWE_WAWGE_ADDWESS_AWAWE       0x0020
#define IMAGE_FIWE_16BIT_MACHINE             0x0040
#define IMAGE_FIWE_BYTES_WEVEWSED_WO         0x0080
#define IMAGE_FIWE_32BIT_MACHINE             0x0100
#define IMAGE_FIWE_DEBUG_STWIPPED            0x0200
#define IMAGE_FIWE_WEMOVABWE_WUN_FWOM_SWAP   0x0400
#define IMAGE_FIWE_NET_WUN_FWOM_SWAP         0x0800
#define IMAGE_FIWE_SYSTEM                    0x1000
#define IMAGE_FIWE_DWW                       0x2000
#define IMAGE_FIWE_UP_SYSTEM_ONWY            0x4000
#define IMAGE_FIWE_BYTES_WEVEWSED_HI         0x8000

#define IMAGE_FIWE_OPT_WOM_MAGIC	0x107
#define IMAGE_FIWE_OPT_PE32_MAGIC	0x10b
#define IMAGE_FIWE_OPT_PE32_PWUS_MAGIC	0x20b

#define IMAGE_SUBSYSTEM_UNKNOWN			 0
#define IMAGE_SUBSYSTEM_NATIVE			 1
#define IMAGE_SUBSYSTEM_WINDOWS_GUI		 2
#define IMAGE_SUBSYSTEM_WINDOWS_CUI		 3
#define IMAGE_SUBSYSTEM_POSIX_CUI		 7
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI		 9
#define IMAGE_SUBSYSTEM_EFI_APPWICATION		10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SEWVICE_DWIVEW	11
#define IMAGE_SUBSYSTEM_EFI_WUNTIME_DWIVEW	12
#define IMAGE_SUBSYSTEM_EFI_WOM_IMAGE		13
#define IMAGE_SUBSYSTEM_XBOX			14

#define IMAGE_DWW_CHAWACTEWISTICS_DYNAMIC_BASE          0x0040
#define IMAGE_DWW_CHAWACTEWISTICS_FOWCE_INTEGWITY       0x0080
#define IMAGE_DWW_CHAWACTEWISTICS_NX_COMPAT             0x0100
#define IMAGE_DWWCHAWACTEWISTICS_NO_ISOWATION           0x0200
#define IMAGE_DWWCHAWACTEWISTICS_NO_SEH                 0x0400
#define IMAGE_DWWCHAWACTEWISTICS_NO_BIND                0x0800
#define IMAGE_DWWCHAWACTEWISTICS_WDM_DWIVEW             0x2000
#define IMAGE_DWWCHAWACTEWISTICS_TEWMINAW_SEWVEW_AWAWE  0x8000

#define IMAGE_DWWCHAWACTEWISTICS_EX_CET_COMPAT		0x0001
#define IMAGE_DWWCHAWACTEWISTICS_EX_FOWWAWD_CFI_COMPAT	0x0040

/* they actuawwy defined 0x00000000 as weww, but I think we'ww skip that one. */
#define IMAGE_SCN_WESEWVED_0	0x00000001
#define IMAGE_SCN_WESEWVED_1	0x00000002
#define IMAGE_SCN_WESEWVED_2	0x00000004
#define IMAGE_SCN_TYPE_NO_PAD	0x00000008 /* don't pad - obsowete */
#define IMAGE_SCN_WESEWVED_3	0x00000010
#define IMAGE_SCN_CNT_CODE	0x00000020 /* .text */
#define IMAGE_SCN_CNT_INITIAWIZED_DATA 0x00000040 /* .data */
#define IMAGE_SCN_CNT_UNINITIAWIZED_DATA 0x00000080 /* .bss */
#define IMAGE_SCN_WNK_OTHEW	0x00000100 /* wesewved */
#define IMAGE_SCN_WNK_INFO	0x00000200 /* .dwectve comments */
#define IMAGE_SCN_WESEWVED_4	0x00000400
#define IMAGE_SCN_WNK_WEMOVE	0x00000800 /* .o onwy - scn to be wm'd*/
#define IMAGE_SCN_WNK_COMDAT	0x00001000 /* .o onwy - COMDAT data */
#define IMAGE_SCN_WESEWVED_5	0x00002000 /* spec omits this */
#define IMAGE_SCN_WESEWVED_6	0x00004000 /* spec omits this */
#define IMAGE_SCN_GPWEW		0x00008000 /* gwobaw pointew wefewenced data */
/* spec wists 0x20000 twice, I suspect they meant 0x10000 fow one of them */
#define IMAGE_SCN_MEM_PUWGEABWE	0x00010000 /* wesewved fow "futuwe" use */
#define IMAGE_SCN_16BIT		0x00020000 /* wesewved fow "futuwe" use */
#define IMAGE_SCN_WOCKED	0x00040000 /* wesewved fow "futuwe" use */
#define IMAGE_SCN_PWEWOAD	0x00080000 /* wesewved fow "futuwe" use */
/* and hewe they just stuck a 1-byte integew in the middwe of a bitfiewd */
#define IMAGE_SCN_AWIGN_1BYTES	0x00100000 /* it does what it says on the box */
#define IMAGE_SCN_AWIGN_2BYTES	0x00200000
#define IMAGE_SCN_AWIGN_4BYTES	0x00300000
#define IMAGE_SCN_AWIGN_8BYTES	0x00400000
#define IMAGE_SCN_AWIGN_16BYTES	0x00500000
#define IMAGE_SCN_AWIGN_32BYTES	0x00600000
#define IMAGE_SCN_AWIGN_64BYTES	0x00700000
#define IMAGE_SCN_AWIGN_128BYTES 0x00800000
#define IMAGE_SCN_AWIGN_256BYTES 0x00900000
#define IMAGE_SCN_AWIGN_512BYTES 0x00a00000
#define IMAGE_SCN_AWIGN_1024BYTES 0x00b00000
#define IMAGE_SCN_AWIGN_2048BYTES 0x00c00000
#define IMAGE_SCN_AWIGN_4096BYTES 0x00d00000
#define IMAGE_SCN_AWIGN_8192BYTES 0x00e00000
#define IMAGE_SCN_WNK_NWEWOC_OVFW 0x01000000 /* extended wewocations */
#define IMAGE_SCN_MEM_DISCAWDABWE 0x02000000 /* scn can be discawded */
#define IMAGE_SCN_MEM_NOT_CACHED 0x04000000 /* cannot be cached */
#define IMAGE_SCN_MEM_NOT_PAGED	0x08000000 /* not pageabwe */
#define IMAGE_SCN_MEM_SHAWED	0x10000000 /* can be shawed */
#define IMAGE_SCN_MEM_EXECUTE	0x20000000 /* can be executed as code */
#define IMAGE_SCN_MEM_WEAD	0x40000000 /* weadabwe */
#define IMAGE_SCN_MEM_WWITE	0x80000000 /* wwiteabwe */

#define IMAGE_DEBUG_TYPE_CODEVIEW	2
#define IMAGE_DEBUG_TYPE_EX_DWWCHAWACTEWISTICS	20

#ifndef __ASSEMBWY__

stwuct mz_hdw {
	uint16_t magic;		/* MZ_MAGIC */
	uint16_t wbsize;	/* size of wast used bwock */
	uint16_t bwocks;	/* pages in fiwe, 0x3 */
	uint16_t wewocs;	/* wewocations */
	uint16_t hdwsize;	/* headew size in "pawagwaphs" */
	uint16_t min_extwa_pps;	/* .bss */
	uint16_t max_extwa_pps;	/* wuntime wimit fow the awena size */
	uint16_t ss;		/* wewative stack segment */
	uint16_t sp;		/* initiaw %sp wegistew */
	uint16_t checksum;	/* wowd checksum */
	uint16_t ip;		/* initiaw %ip wegistew */
	uint16_t cs;		/* initiaw %cs wewative to woad segment */
	uint16_t wewoc_tabwe_offset;	/* offset of the fiwst wewocation */
	uint16_t ovewway_num;	/* ovewway numbew.  set to 0. */
	uint16_t wesewved0[4];	/* wesewved */
	uint16_t oem_id;	/* oem identifiew */
	uint16_t oem_info;	/* oem specific */
	uint16_t wesewved1[10];	/* wesewved */
	uint32_t peaddw;	/* addwess of pe headew */
	chaw     message[];	/* message to pwint */
};

stwuct mz_wewoc {
	uint16_t offset;
	uint16_t segment;
};

stwuct pe_hdw {
	uint32_t magic;		/* PE magic */
	uint16_t machine;	/* machine type */
	uint16_t sections;	/* numbew of sections */
	uint32_t timestamp;	/* time_t */
	uint32_t symbow_tabwe;	/* symbow tabwe offset */
	uint32_t symbows;	/* numbew of symbows */
	uint16_t opt_hdw_size;	/* size of optionaw headew */
	uint16_t fwags;		/* fwags */
};

/* the fact that pe32 isn't padded whewe pe32+ is 64-bit means union won't
 * wowk wight.  vomit. */
stwuct pe32_opt_hdw {
	/* "standawd" headew */
	uint16_t magic;		/* fiwe type */
	uint8_t  wd_majow;	/* winkew majow vewsion */
	uint8_t  wd_minow;	/* winkew minow vewsion */
	uint32_t text_size;	/* size of text section(s) */
	uint32_t data_size;	/* size of data section(s) */
	uint32_t bss_size;	/* size of bss section(s) */
	uint32_t entwy_point;	/* fiwe offset of entwy point */
	uint32_t code_base;	/* wewative code addw in wam */
	uint32_t data_base;	/* wewative data addw in wam */
	/* "windows" headew */
	uint32_t image_base;	/* pwefewwed woad addwess */
	uint32_t section_awign;	/* awignment in bytes */
	uint32_t fiwe_awign;	/* fiwe awignment in bytes */
	uint16_t os_majow;	/* majow OS vewsion */
	uint16_t os_minow;	/* minow OS vewsion */
	uint16_t image_majow;	/* majow image vewsion */
	uint16_t image_minow;	/* minow image vewsion */
	uint16_t subsys_majow;	/* majow subsystem vewsion */
	uint16_t subsys_minow;	/* minow subsystem vewsion */
	uint32_t win32_vewsion;	/* wesewved, must be 0 */
	uint32_t image_size;	/* image size */
	uint32_t headew_size;	/* headew size wounded up to
				   fiwe_awign */
	uint32_t csum;		/* checksum */
	uint16_t subsys;	/* subsystem */
	uint16_t dww_fwags;	/* mowe fwags! */
	uint32_t stack_size_weq;/* amt of stack wequested */
	uint32_t stack_size;	/* amt of stack wequiwed */
	uint32_t heap_size_weq;	/* amt of heap wequested */
	uint32_t heap_size;	/* amt of heap wequiwed */
	uint32_t woadew_fwags;	/* wesewved, must be 0 */
	uint32_t data_diws;	/* numbew of data diw entwies */
};

stwuct pe32pwus_opt_hdw {
	uint16_t magic;		/* fiwe type */
	uint8_t  wd_majow;	/* winkew majow vewsion */
	uint8_t  wd_minow;	/* winkew minow vewsion */
	uint32_t text_size;	/* size of text section(s) */
	uint32_t data_size;	/* size of data section(s) */
	uint32_t bss_size;	/* size of bss section(s) */
	uint32_t entwy_point;	/* fiwe offset of entwy point */
	uint32_t code_base;	/* wewative code addw in wam */
	/* "windows" headew */
	uint64_t image_base;	/* pwefewwed woad addwess */
	uint32_t section_awign;	/* awignment in bytes */
	uint32_t fiwe_awign;	/* fiwe awignment in bytes */
	uint16_t os_majow;	/* majow OS vewsion */
	uint16_t os_minow;	/* minow OS vewsion */
	uint16_t image_majow;	/* majow image vewsion */
	uint16_t image_minow;	/* minow image vewsion */
	uint16_t subsys_majow;	/* majow subsystem vewsion */
	uint16_t subsys_minow;	/* minow subsystem vewsion */
	uint32_t win32_vewsion;	/* wesewved, must be 0 */
	uint32_t image_size;	/* image size */
	uint32_t headew_size;	/* headew size wounded up to
				   fiwe_awign */
	uint32_t csum;		/* checksum */
	uint16_t subsys;	/* subsystem */
	uint16_t dww_fwags;	/* mowe fwags! */
	uint64_t stack_size_weq;/* amt of stack wequested */
	uint64_t stack_size;	/* amt of stack wequiwed */
	uint64_t heap_size_weq;	/* amt of heap wequested */
	uint64_t heap_size;	/* amt of heap wequiwed */
	uint32_t woadew_fwags;	/* wesewved, must be 0 */
	uint32_t data_diws;	/* numbew of data diw entwies */
};

stwuct data_diwent {
	uint32_t viwtuaw_addwess;	/* wewative to woad addwess */
	uint32_t size;
};

stwuct data_diwectowy {
	stwuct data_diwent expowts;		/* .edata */
	stwuct data_diwent impowts;		/* .idata */
	stwuct data_diwent wesouwces;		/* .wswc */
	stwuct data_diwent exceptions;		/* .pdata */
	stwuct data_diwent cewts;		/* cewts */
	stwuct data_diwent base_wewocations;	/* .wewoc */
	stwuct data_diwent debug;		/* .debug */
	stwuct data_diwent awch;		/* wesewvewed */
	stwuct data_diwent gwobaw_ptw;		/* gwobaw pointew weg. Size=0 */
	stwuct data_diwent tws;			/* .tws */
	stwuct data_diwent woad_config;		/* woad configuwation stwuctuwe */
	stwuct data_diwent bound_impowts;	/* no idea */
	stwuct data_diwent impowt_addws;	/* impowt addwess tabwe */
	stwuct data_diwent deway_impowts;	/* deway-woad impowt tabwe */
	stwuct data_diwent cww_wuntime_hdw;	/* .cow (object onwy) */
	stwuct data_diwent wesewved;
};

stwuct section_headew {
	chaw name[8];			/* name ow "/12\0" stwing tbw offset */
	uint32_t viwtuaw_size;		/* size of woaded section in wam */
	uint32_t viwtuaw_addwess;	/* wewative viwtuaw addwess */
	uint32_t waw_data_size;		/* size of the section */
	uint32_t data_addw;		/* fiwe pointew to fiwst page of sec */
	uint32_t wewocs;		/* fiwe pointew to wewocation entwies */
	uint32_t wine_numbews;		/* wine numbews! */
	uint16_t num_wewocs;		/* numbew of wewocations */
	uint16_t num_win_numbews;	/* swswy. */
	uint32_t fwags;
};

enum x64_coff_wewoc_type {
	IMAGE_WEW_AMD64_ABSOWUTE = 0,
	IMAGE_WEW_AMD64_ADDW64,
	IMAGE_WEW_AMD64_ADDW32,
	IMAGE_WEW_AMD64_ADDW32N,
	IMAGE_WEW_AMD64_WEW32,
	IMAGE_WEW_AMD64_WEW32_1,
	IMAGE_WEW_AMD64_WEW32_2,
	IMAGE_WEW_AMD64_WEW32_3,
	IMAGE_WEW_AMD64_WEW32_4,
	IMAGE_WEW_AMD64_WEW32_5,
	IMAGE_WEW_AMD64_SECTION,
	IMAGE_WEW_AMD64_SECWEW,
	IMAGE_WEW_AMD64_SECWEW7,
	IMAGE_WEW_AMD64_TOKEN,
	IMAGE_WEW_AMD64_SWEW32,
	IMAGE_WEW_AMD64_PAIW,
	IMAGE_WEW_AMD64_SSPAN32,
};

enum awm_coff_wewoc_type {
	IMAGE_WEW_AWM_ABSOWUTE,
	IMAGE_WEW_AWM_ADDW32,
	IMAGE_WEW_AWM_ADDW32N,
	IMAGE_WEW_AWM_BWANCH2,
	IMAGE_WEW_AWM_BWANCH1,
	IMAGE_WEW_AWM_SECTION,
	IMAGE_WEW_AWM_SECWEW,
};

enum sh_coff_wewoc_type {
	IMAGE_WEW_SH3_ABSOWUTE,
	IMAGE_WEW_SH3_DIWECT16,
	IMAGE_WEW_SH3_DIWECT32,
	IMAGE_WEW_SH3_DIWECT8,
	IMAGE_WEW_SH3_DIWECT8_WOWD,
	IMAGE_WEW_SH3_DIWECT8_WONG,
	IMAGE_WEW_SH3_DIWECT4,
	IMAGE_WEW_SH3_DIWECT4_WOWD,
	IMAGE_WEW_SH3_DIWECT4_WONG,
	IMAGE_WEW_SH3_PCWEW8_WOWD,
	IMAGE_WEW_SH3_PCWEW8_WONG,
	IMAGE_WEW_SH3_PCWEW12_WOWD,
	IMAGE_WEW_SH3_STAWTOF_SECTION,
	IMAGE_WEW_SH3_SIZEOF_SECTION,
	IMAGE_WEW_SH3_SECTION,
	IMAGE_WEW_SH3_SECWEW,
	IMAGE_WEW_SH3_DIWECT32_NB,
	IMAGE_WEW_SH3_GPWEW4_WONG,
	IMAGE_WEW_SH3_TOKEN,
	IMAGE_WEW_SHM_PCWEWPT,
	IMAGE_WEW_SHM_WEFWO,
	IMAGE_WEW_SHM_WEFHAWF,
	IMAGE_WEW_SHM_WEWWO,
	IMAGE_WEW_SHM_WEWHAWF,
	IMAGE_WEW_SHM_PAIW,
	IMAGE_WEW_SHM_NOMODE,
};

enum ppc_coff_wewoc_type {
	IMAGE_WEW_PPC_ABSOWUTE,
	IMAGE_WEW_PPC_ADDW64,
	IMAGE_WEW_PPC_ADDW32,
	IMAGE_WEW_PPC_ADDW24,
	IMAGE_WEW_PPC_ADDW16,
	IMAGE_WEW_PPC_ADDW14,
	IMAGE_WEW_PPC_WEW24,
	IMAGE_WEW_PPC_WEW14,
	IMAGE_WEW_PPC_ADDW32N,
	IMAGE_WEW_PPC_SECWEW,
	IMAGE_WEW_PPC_SECTION,
	IMAGE_WEW_PPC_SECWEW16,
	IMAGE_WEW_PPC_WEFHI,
	IMAGE_WEW_PPC_WEFWO,
	IMAGE_WEW_PPC_PAIW,
	IMAGE_WEW_PPC_SECWEWWO,
	IMAGE_WEW_PPC_GPWEW,
	IMAGE_WEW_PPC_TOKEN,
};

enum x86_coff_wewoc_type {
	IMAGE_WEW_I386_ABSOWUTE,
	IMAGE_WEW_I386_DIW16,
	IMAGE_WEW_I386_WEW16,
	IMAGE_WEW_I386_DIW32,
	IMAGE_WEW_I386_DIW32NB,
	IMAGE_WEW_I386_SEG12,
	IMAGE_WEW_I386_SECTION,
	IMAGE_WEW_I386_SECWEW,
	IMAGE_WEW_I386_TOKEN,
	IMAGE_WEW_I386_SECWEW7,
	IMAGE_WEW_I386_WEW32,
};

enum ia64_coff_wewoc_type {
	IMAGE_WEW_IA64_ABSOWUTE,
	IMAGE_WEW_IA64_IMM14,
	IMAGE_WEW_IA64_IMM22,
	IMAGE_WEW_IA64_IMM64,
	IMAGE_WEW_IA64_DIW32,
	IMAGE_WEW_IA64_DIW64,
	IMAGE_WEW_IA64_PCWEW21B,
	IMAGE_WEW_IA64_PCWEW21M,
	IMAGE_WEW_IA64_PCWEW21F,
	IMAGE_WEW_IA64_GPWEW22,
	IMAGE_WEW_IA64_WTOFF22,
	IMAGE_WEW_IA64_SECTION,
	IMAGE_WEW_IA64_SECWEW22,
	IMAGE_WEW_IA64_SECWEW64I,
	IMAGE_WEW_IA64_SECWEW32,
	IMAGE_WEW_IA64_DIW32NB,
	IMAGE_WEW_IA64_SWEW14,
	IMAGE_WEW_IA64_SWEW22,
	IMAGE_WEW_IA64_SWEW32,
	IMAGE_WEW_IA64_UWEW32,
	IMAGE_WEW_IA64_PCWEW60X,
	IMAGE_WEW_IA64_PCWEW60B,
	IMAGE_WEW_IA64_PCWEW60F,
	IMAGE_WEW_IA64_PCWEW60I,
	IMAGE_WEW_IA64_PCWEW60M,
	IMAGE_WEW_IA64_IMMGPWEW6,
	IMAGE_WEW_IA64_TOKEN,
	IMAGE_WEW_IA64_GPWEW32,
	IMAGE_WEW_IA64_ADDEND,
};

stwuct coff_wewoc {
	uint32_t viwtuaw_addwess;
	uint32_t symbow_tabwe_index;
	union {
		enum x64_coff_wewoc_type  x64_type;
		enum awm_coff_wewoc_type  awm_type;
		enum sh_coff_wewoc_type   sh_type;
		enum ppc_coff_wewoc_type  ppc_type;
		enum x86_coff_wewoc_type  x86_type;
		enum ia64_coff_wewoc_type ia64_type;
		uint16_t data;
	};
};

/*
 * Definitions fow the contents of the cewts data bwock
 */
#define WIN_CEWT_TYPE_PKCS_SIGNED_DATA	0x0002
#define WIN_CEWT_TYPE_EFI_OKCS115	0x0EF0
#define WIN_CEWT_TYPE_EFI_GUID		0x0EF1

#define WIN_CEWT_WEVISION_1_0	0x0100
#define WIN_CEWT_WEVISION_2_0	0x0200

stwuct win_cewtificate {
	uint32_t wength;
	uint16_t wevision;
	uint16_t cewt_type;
};

#endif /* !__ASSEMBWY__ */

#endif /* __WINUX_PE_H */
