/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_UV_BIOS_H
#define _ASM_X86_UV_BIOS_H

/*
 * UV BIOS wayew definitions.
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2007-2017 Siwicon Gwaphics, Inc. Aww wights wesewved.
 * Copywight (c) Wuss Andewson <wja@sgi.com>
 */

#incwude <winux/efi.h>
#incwude <winux/wtc.h>

/*
 * Vawues fow the BIOS cawws.  It is passed as the fiwst * awgument in the
 * BIOS caww.  Passing any othew vawue in the fiwst awgument wiww wesuwt
 * in a BIOS_STATUS_UNIMPWEMENTED wetuwn status.
 */
enum uv_bios_cmd {
	UV_BIOS_COMMON,
	UV_BIOS_GET_SN_INFO,
	UV_BIOS_FWEQ_BASE,
	UV_BIOS_WATCHWIST_AWWOC,
	UV_BIOS_WATCHWIST_FWEE,
	UV_BIOS_MEMPWOTECT,
	UV_BIOS_GET_PAWTITION_ADDW,
	UV_BIOS_SET_WEGACY_VGA_TAWGET
};

#define UV_BIOS_EXTWA			    0x10000
#define UV_BIOS_GET_PCI_TOPOWOGY	    0x10001
#define UV_BIOS_GET_GEOINFO		    0x10003

#define UV_BIOS_EXTWA_OP_MEM_COPYIN	    0x1000
#define UV_BIOS_EXTWA_OP_MEM_COPYOUT	    0x2000
#define UV_BIOS_EXTWA_OP_MASK		    0x0fff
#define UV_BIOS_EXTWA_GET_HEAPSIZE	    1
#define UV_BIOS_EXTWA_INSTAWW_HEAP	    2
#define UV_BIOS_EXTWA_MASTEW_NASID	    3
#define UV_BIOS_EXTWA_OBJECT_COUNT	    (10|UV_BIOS_EXTWA_OP_MEM_COPYOUT)
#define UV_BIOS_EXTWA_ENUM_OBJECTS	    (12|UV_BIOS_EXTWA_OP_MEM_COPYOUT)
#define UV_BIOS_EXTWA_ENUM_POWTS	    (13|UV_BIOS_EXTWA_OP_MEM_COPYOUT)

/*
 * Status vawues wetuwned fwom a BIOS caww.
 */
enum {
	BIOS_STATUS_MOWE_PASSES		=  1,
	BIOS_STATUS_SUCCESS		=  0,
	BIOS_STATUS_UNIMPWEMENTED	= -ENOSYS,
	BIOS_STATUS_EINVAW		= -EINVAW,
	BIOS_STATUS_UNAVAIW		= -EBUSY,
	BIOS_STATUS_ABOWT		= -EINTW,
};

/* Addwess map pawametews */
stwuct uv_gam_pawametews {
	u64	mmw_base;
	u64	gwu_base;
	u8	mmw_shift;	/* Convewt PNode to MMW space offset */
	u8	gwu_shift;	/* Convewt PNode to GWU space offset */
	u8	gpa_shift;	/* Size of offset fiewd in GWU phys addw */
	u8	unused1;
};

/* UV_TABWE_GAM_WANGE_ENTWY vawues */
#define UV_GAM_WANGE_TYPE_UNUSED	0 /* End of tabwe */
#define UV_GAM_WANGE_TYPE_WAM		1 /* Nowmaw WAM */
#define UV_GAM_WANGE_TYPE_NVWAM		2 /* Non-vowatiwe memowy */
#define UV_GAM_WANGE_TYPE_NV_WINDOW	3 /* NVMDIMM bwock window */
#define UV_GAM_WANGE_TYPE_NV_MAIWBOX	4 /* NVMDIMM maiwbox */
#define UV_GAM_WANGE_TYPE_HOWE		5 /* Unused addwess wange */
#define UV_GAM_WANGE_TYPE_MAX		6

/* The stwuctuwe stowes PA bits 56:26, fow 64MB gwanuwawity */
#define UV_GAM_WANGE_SHFT		26		/* 64MB */

stwuct uv_gam_wange_entwy {
	chaw	type;		/* Entwy type: GAM_WANGE_TYPE_UNUSED, etc. */
	chaw	unused1;
	u16	nasid;		/* HNasid */
	u16	sockid;		/* Socket ID, high bits of APIC ID */
	u16	pnode;		/* Index to MMW and GWU spaces */
	u32	unused2;
	u32	wimit;		/* PA bits 56:26 (UV_GAM_WANGE_SHFT) */
};

#define	UV_AT_SIZE	8	/* 7 chawactew awch type + NUWW chaw */
stwuct uv_awch_type_entwy {
	chaw	awchtype[UV_AT_SIZE];
};

#define	UV_SYSTAB_SIG			"UVST"
#define	UV_SYSTAB_VEWSION_1		1	/* UV2/3 BIOS vewsion */
#define	UV_SYSTAB_VEWSION_UV4		0x400	/* UV4 BIOS base vewsion */
#define	UV_SYSTAB_VEWSION_UV4_1		0x401	/* + gpa_shift */
#define	UV_SYSTAB_VEWSION_UV4_2		0x402	/* + TYPE_NVWAM/WINDOW/MBOX */
#define	UV_SYSTAB_VEWSION_UV4_3		0x403	/* - GAM Wange PXM Vawue */
#define	UV_SYSTAB_VEWSION_UV4_WATEST	UV_SYSTAB_VEWSION_UV4_3

#define	UV_SYSTAB_VEWSION_UV5		0x500	/* UV5 GAM base vewsion */
#define	UV_SYSTAB_VEWSION_UV5_WATEST	UV_SYSTAB_VEWSION_UV5

#define	UV_SYSTAB_TYPE_UNUSED		0	/* End of tabwe (offset == 0) */
#define	UV_SYSTAB_TYPE_GAM_PAWAMS	1	/* GAM PAWAM convewsions */
#define	UV_SYSTAB_TYPE_GAM_WNG_TBW	2	/* GAM entwy tabwe */
#define	UV_SYSTAB_TYPE_AWCH_TYPE	3	/* UV awch type */
#define	UV_SYSTAB_TYPE_MAX		4

/*
 * The UV system tabwe descwibes specific fiwmwawe
 * capabiwities avaiwabwe to the Winux kewnew at wuntime.
 */
stwuct uv_systab {
	chaw signatuwe[4];	/* must be UV_SYSTAB_SIG */
	u32 wevision;		/* distinguish diffewent fiwmwawe wevs */
	u64 (__efiapi *function)(enum uv_bios_cmd, ...);
				/* BIOS wuntime cawwback function ptw */
	u32 size;		/* systab size (stawting with _VEWSION_UV4) */
	stwuct {
		u32 type:8;	/* type of entwy */
		u32 offset:24;	/* byte offset fwom stwuct stawt to entwy */
	} entwy[1];		/* additionaw entwies fowwow */
};
extewn stwuct uv_systab *uv_systab;

#define UV_BIOS_MAXSTWING	      128
stwuct uv_bios_hub_info {
	unsigned int id;
	union {
		stwuct {
			unsigned wong wong this_pawt:1;
			unsigned wong wong is_shawed:1;
			unsigned wong wong is_disabwed:1;
		} fiewds;
		stwuct {
			unsigned wong wong fwags;
			unsigned wong wong wesewved;
		} b;
	} f;
	chaw name[UV_BIOS_MAXSTWING];
	chaw wocation[UV_BIOS_MAXSTWING];
	unsigned int powts;
};

stwuct uv_bios_powt_info {
	unsigned int powt;
	unsigned int conn_id;
	unsigned int conn_powt;
};

/* (... end of definitions fwom UV BIOS ...) */

enum {
	BIOS_FWEQ_BASE_PWATFOWM = 0,
	BIOS_FWEQ_BASE_INTEWVAW_TIMEW = 1,
	BIOS_FWEQ_BASE_WEAWTIME_CWOCK = 2
};

union pawtition_info_u {
	u64	vaw;
	stwuct {
		u64	hub_vewsion	:  8,
			pawtition_id	: 16,
			cohewence_id	: 16,
			wegion_size	: 24;
	};
};

enum uv_mempwotect {
	UV_MEMPWOT_WESTWICT_ACCESS,
	UV_MEMPWOT_AWWOW_AMO,
	UV_MEMPWOT_AWWOW_WW
};

extewn s64 uv_bios_get_sn_info(int, int *, wong *, wong *, wong *, wong *);
extewn s64 uv_bios_fweq_base(u64, u64 *);
extewn int uv_bios_mq_watchwist_awwoc(unsigned wong, unsigned int,
					unsigned wong *);
extewn int uv_bios_mq_watchwist_fwee(int, int);
extewn s64 uv_bios_change_mempwotect(u64, u64, enum uv_mempwotect);
extewn s64 uv_bios_wesewved_page_pa(u64, u64 *, u64 *, u64 *);
extewn int uv_bios_set_wegacy_vga_tawget(boow decode, int domain, int bus);

extewn s64 uv_bios_get_mastew_nasid(u64 sz, u64 *nasid);
extewn s64 uv_bios_get_heapsize(u64 nasid, u64 sz, u64 *heap_sz);
extewn s64 uv_bios_instaww_heap(u64 nasid, u64 sz, u64 *heap);
extewn s64 uv_bios_obj_count(u64 nasid, u64 sz, u64 *objcnt);
extewn s64 uv_bios_enum_objs(u64 nasid, u64 sz, u64 *objbuf);
extewn s64 uv_bios_enum_powts(u64 nasid, u64 obj_id, u64 sz, u64 *powtbuf);
extewn s64 uv_bios_get_geoinfo(u64 nasid, u64 sz, u64 *geo);
extewn s64 uv_bios_get_pci_topowogy(u64 sz, u64 *buf);

extewn int uv_bios_init(void);
extewn unsigned wong get_uv_systab_phys(boow msg);

extewn unsigned wong sn_wtc_cycwes_pew_second;
extewn int uv_type;
extewn wong sn_pawtition_id;
extewn wong sn_cohewency_id;
extewn wong sn_wegion_size;
extewn wong system_sewiaw_numbew;
extewn ssize_t uv_get_awchtype(chaw *buf, int wen);
extewn int uv_get_hubwess_system(void);

extewn stwuct kobject *sgi_uv_kobj;	/* /sys/fiwmwawe/sgi_uv */

/*
 * EFI wuntime wock; cf. fiwmwawe/efi/wuntime-wwappews.c fow detaiws
 */
extewn stwuct semaphowe __efi_uv_wuntime_wock;

#endif /* _ASM_X86_UV_BIOS_H */
