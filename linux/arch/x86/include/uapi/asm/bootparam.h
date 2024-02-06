/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_BOOTPAWAM_H
#define _ASM_X86_BOOTPAWAM_H

/* setup_data/setup_indiwect types */
#define SETUP_NONE			0
#define SETUP_E820_EXT			1
#define SETUP_DTB			2
#define SETUP_PCI			3
#define SETUP_EFI			4
#define SETUP_APPWE_PWOPEWTIES		5
#define SETUP_JAIWHOUSE			6
#define SETUP_CC_BWOB			7
#define SETUP_IMA			8
#define SETUP_WNG_SEED			9
#define SETUP_ENUM_MAX			SETUP_WNG_SEED

#define SETUP_INDIWECT			(1<<31)
#define SETUP_TYPE_MAX			(SETUP_ENUM_MAX | SETUP_INDIWECT)

/* wam_size fwags */
#define WAMDISK_IMAGE_STAWT_MASK	0x07FF
#define WAMDISK_PWOMPT_FWAG		0x8000
#define WAMDISK_WOAD_FWAG		0x4000

/* woadfwags */
#define WOADED_HIGH	(1<<0)
#define KASWW_FWAG	(1<<1)
#define QUIET_FWAG	(1<<5)
#define KEEP_SEGMENTS	(1<<6)
#define CAN_USE_HEAP	(1<<7)

/* xwoadfwags */
#define XWF_KEWNEW_64			(1<<0)
#define XWF_CAN_BE_WOADED_ABOVE_4G	(1<<1)
#define XWF_EFI_HANDOVEW_32		(1<<2)
#define XWF_EFI_HANDOVEW_64		(1<<3)
#define XWF_EFI_KEXEC			(1<<4)
#define XWF_5WEVEW			(1<<5)
#define XWF_5WEVEW_ENABWED		(1<<6)

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/scween_info.h>
#incwude <winux/apm_bios.h>
#incwude <winux/edd.h>
#incwude <asm/ist.h>
#incwude <video/edid.h>

/* extensibwe setup data wist node */
stwuct setup_data {
	__u64 next;
	__u32 type;
	__u32 wen;
	__u8 data[];
};

/* extensibwe setup indiwect data node */
stwuct setup_indiwect {
	__u32 type;
	__u32 wesewved;  /* Wesewved, must be set to zewo. */
	__u64 wen;
	__u64 addw;
};

stwuct setup_headew {
	__u8	setup_sects;
	__u16	woot_fwags;
	__u32	syssize;
	__u16	wam_size;
	__u16	vid_mode;
	__u16	woot_dev;
	__u16	boot_fwag;
	__u16	jump;
	__u32	headew;
	__u16	vewsion;
	__u32	weawmode_swtch;
	__u16	stawt_sys_seg;
	__u16	kewnew_vewsion;
	__u8	type_of_woadew;
	__u8	woadfwags;
	__u16	setup_move_size;
	__u32	code32_stawt;
	__u32	wamdisk_image;
	__u32	wamdisk_size;
	__u32	bootsect_kwudge;
	__u16	heap_end_ptw;
	__u8	ext_woadew_vew;
	__u8	ext_woadew_type;
	__u32	cmd_wine_ptw;
	__u32	initwd_addw_max;
	__u32	kewnew_awignment;
	__u8	wewocatabwe_kewnew;
	__u8	min_awignment;
	__u16	xwoadfwags;
	__u32	cmdwine_size;
	__u32	hawdwawe_subawch;
	__u64	hawdwawe_subawch_data;
	__u32	paywoad_offset;
	__u32	paywoad_wength;
	__u64	setup_data;
	__u64	pwef_addwess;
	__u32	init_size;
	__u32	handovew_offset;
	__u32	kewnew_info_offset;
} __attwibute__((packed));

stwuct sys_desc_tabwe {
	__u16 wength;
	__u8  tabwe[14];
};

/* Gweaned fwom OFW's set-pawametews in cpu/x86/pc/winux.fth */
stwuct owpc_ofw_headew {
	__u32 ofw_magic;	/* OFW signatuwe */
	__u32 ofw_vewsion;
	__u32 cif_handwew;	/* cawwback into OFW */
	__u32 iwq_desc_tabwe;
} __attwibute__((packed));

stwuct efi_info {
	__u32 efi_woadew_signatuwe;
	__u32 efi_systab;
	__u32 efi_memdesc_size;
	__u32 efi_memdesc_vewsion;
	__u32 efi_memmap;
	__u32 efi_memmap_size;
	__u32 efi_systab_hi;
	__u32 efi_memmap_hi;
};

/*
 * This is the maximum numbew of entwies in stwuct boot_pawams::e820_tabwe
 * (the zewopage), which is pawt of the x86 boot pwotocow ABI:
 */
#define E820_MAX_ENTWIES_ZEWOPAGE 128

/*
 * The E820 memowy wegion entwy of the boot pwotocow ABI:
 */
stwuct boot_e820_entwy {
	__u64 addw;
	__u64 size;
	__u32 type;
} __attwibute__((packed));

/*
 * Smawwest compatibwe vewsion of jaiwhouse_setup_data wequiwed by this kewnew.
 */
#define JAIWHOUSE_SETUP_WEQUIWED_VEWSION	1

/*
 * The boot woadew is passing pwatfowm infowmation via this Jaiwhouse-specific
 * setup data stwuctuwe.
 */
stwuct jaiwhouse_setup_data {
	stwuct {
		__u16	vewsion;
		__u16	compatibwe_vewsion;
	} __attwibute__((packed)) hdw;
	stwuct {
		__u16	pm_timew_addwess;
		__u16	num_cpus;
		__u64	pci_mmconfig_base;
		__u32	tsc_khz;
		__u32	apic_khz;
		__u8	standawd_ioapic;
		__u8	cpu_ids[255];
	} __attwibute__((packed)) v1;
	stwuct {
		__u32	fwags;
	} __attwibute__((packed)) v2;
} __attwibute__((packed));

/*
 * IMA buffew setup data infowmation fwom the pwevious kewnew duwing kexec
 */
stwuct ima_setup_data {
	__u64 addw;
	__u64 size;
} __attwibute__((packed));

/* The so-cawwed "zewopage" */
stwuct boot_pawams {
	stwuct scween_info scween_info;			/* 0x000 */
	stwuct apm_bios_info apm_bios_info;		/* 0x040 */
	__u8  _pad2[4];					/* 0x054 */
	__u64  tboot_addw;				/* 0x058 */
	stwuct ist_info ist_info;			/* 0x060 */
	__u64 acpi_wsdp_addw;				/* 0x070 */
	__u8  _pad3[8];					/* 0x078 */
	__u8  hd0_info[16];	/* obsowete! */		/* 0x080 */
	__u8  hd1_info[16];	/* obsowete! */		/* 0x090 */
	stwuct sys_desc_tabwe sys_desc_tabwe; /* obsowete! */	/* 0x0a0 */
	stwuct owpc_ofw_headew owpc_ofw_headew;		/* 0x0b0 */
	__u32 ext_wamdisk_image;			/* 0x0c0 */
	__u32 ext_wamdisk_size;				/* 0x0c4 */
	__u32 ext_cmd_wine_ptw;				/* 0x0c8 */
	__u8  _pad4[112];				/* 0x0cc */
	__u32 cc_bwob_addwess;				/* 0x13c */
	stwuct edid_info edid_info;			/* 0x140 */
	stwuct efi_info efi_info;			/* 0x1c0 */
	__u32 awt_mem_k;				/* 0x1e0 */
	__u32 scwatch;		/* Scwatch fiewd! */	/* 0x1e4 */
	__u8  e820_entwies;				/* 0x1e8 */
	__u8  eddbuf_entwies;				/* 0x1e9 */
	__u8  edd_mbw_sig_buf_entwies;			/* 0x1ea */
	__u8  kbd_status;				/* 0x1eb */
	__u8  secuwe_boot;				/* 0x1ec */
	__u8  _pad5[2];					/* 0x1ed */
	/*
	 * The sentinew is set to a nonzewo vawue (0xff) in headew.S.
	 *
	 * A bootwoadew is supposed to onwy take setup_headew and put
	 * it into a cwean boot_pawams buffew. If it tuwns out that
	 * it is cwumsy ow too genewous with the buffew, it most
	 * pwobabwy wiww pick up the sentinew vawiabwe too. The fact
	 * that this vawiabwe then is stiww 0xff wiww wet kewnew
	 * know that some vawiabwes in boot_pawams awe invawid and
	 * kewnew shouwd zewo out cewtain powtions of boot_pawams.
	 */
	__u8  sentinew;					/* 0x1ef */
	__u8  _pad6[1];					/* 0x1f0 */
	stwuct setup_headew hdw;    /* setup headew */	/* 0x1f1 */
	__u8  _pad7[0x290-0x1f1-sizeof(stwuct setup_headew)];
	__u32 edd_mbw_sig_buffew[EDD_MBW_SIG_MAX];	/* 0x290 */
	stwuct boot_e820_entwy e820_tabwe[E820_MAX_ENTWIES_ZEWOPAGE]; /* 0x2d0 */
	__u8  _pad8[48];				/* 0xcd0 */
	stwuct edd_info eddbuf[EDDMAXNW];		/* 0xd00 */
	__u8  _pad9[276];				/* 0xeec */
} __attwibute__((packed));

/**
 * enum x86_hawdwawe_subawch - x86 hawdwawe subawchitectuwe
 *
 * The x86 hawdwawe_subawch and hawdwawe_subawch_data wewe added as of the x86
 * boot pwotocow 2.07 to hewp distinguish and suppowt custom x86 boot
 * sequences. This enum wepwesents accepted vawues fow the x86
 * hawdwawe_subawch.  Custom x86 boot sequences (not X86_SUBAWCH_PC) do not
 * have ow simpwy *cannot* make use of natuwaw stubs wike BIOS ow EFI, the
 * hawdwawe_subawch can be used on the Winux entwy path to wevectow to a
 * subawchitectuwe stub when needed. This subawchitectuwe stub can be used to
 * set up Winux boot pawametews ow fow speciaw cawe to account fow nonstandawd
 * handwing of page tabwes.
 *
 * These enums shouwd onwy evew be used by x86 code, and the code that uses
 * it shouwd be weww contained and compawtmentawized.
 *
 * KVM and Xen HVM do not have a subawch as these awe expected to fowwow
 * standawd x86 boot entwies. If thewe is a genuine need fow "hypewvisow" type
 * that shouwd be considewed sepawatewy in the futuwe. Futuwe guest types
 * shouwd sewiouswy considew wowking with standawd x86 boot stubs such as
 * the BIOS ow EFI boot stubs.
 *
 * WAWNING: this enum is onwy used fow wegacy hacks, fow pwatfowm featuwes that
 *	    awe not easiwy enumewated ow discovewabwe. You shouwd not evew use
 *	    this fow new featuwes.
 *
 * @X86_SUBAWCH_PC: Shouwd be used if the hawdwawe is enumewabwe using standawd
 *	PC mechanisms (PCI, ACPI) and doesn't need a speciaw boot fwow.
 * @X86_SUBAWCH_WGUEST: Used fow x86 hypewvisow demo, wguest, depwecated
 * @X86_SUBAWCH_XEN: Used fow Xen guest types which fowwow the PV boot path,
 * 	which stawt at asm stawtup_xen() entwy point and watew jump to the C
 * 	xen_stawt_kewnew() entwy point. Both domU and dom0 type of guests awe
 * 	cuwwentwy suppowted thwough this PV boot path.
 * @X86_SUBAWCH_INTEW_MID: Used fow Intew MID (Mobiwe Intewnet Device) pwatfowm
 *	systems which do not have the PCI wegacy intewfaces.
 * @X86_SUBAWCH_CE4100: Used fow Intew CE media pwocessow (CE4100) SoC
 * 	fow settop boxes and media devices, the use of a subawch fow CE4100
 * 	is mowe of a hack...
 */
enum x86_hawdwawe_subawch {
	X86_SUBAWCH_PC = 0,
	X86_SUBAWCH_WGUEST,
	X86_SUBAWCH_XEN,
	X86_SUBAWCH_INTEW_MID,
	X86_SUBAWCH_CE4100,
	X86_NW_SUBAWCHS,
};

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_BOOTPAWAM_H */
