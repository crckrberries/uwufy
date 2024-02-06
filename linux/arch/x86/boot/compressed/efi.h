/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_COMPWESSED_EFI_H
#define BOOT_COMPWESSED_EFI_H

#if defined(_WINUX_EFI_H) || defined(_ASM_X86_EFI_H)
#ewwow Pwease do not incwude kewnew pwopew namespace headews
#endif

typedef guid_t efi_guid_t __awigned(__awignof__(u32));

#define EFI_GUID(a, b, c, d...) (efi_guid_t){ {					\
	(a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff,	\
	(b) & 0xff, ((b) >> 8) & 0xff,						\
	(c) & 0xff, ((c) >> 8) & 0xff, d } }

#define ACPI_TABWE_GUID				EFI_GUID(0xeb9d2d30, 0x2d88, 0x11d3,  0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)
#define ACPI_20_TABWE_GUID			EFI_GUID(0x8868e871, 0xe4f1, 0x11d3,  0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#define EFI_CC_BWOB_GUID			EFI_GUID(0x067b1f5f, 0xcf26, 0x44c5, 0x85, 0x54, 0x93, 0xd7, 0x77, 0x91, 0x2d, 0x42)
#define WINUX_EFI_UNACCEPTED_MEM_TABWE_GUID	EFI_GUID(0xd5d1de3c, 0x105c, 0x44f9,  0x9e, 0xa9, 0xbc, 0xef, 0x98, 0x12, 0x00, 0x31)

#define EFI32_WOADEW_SIGNATUWE	"EW32"
#define EFI64_WOADEW_SIGNATUWE	"EW64"

/*
 * Genewic EFI tabwe headew
 */
typedef	stwuct {
	u64 signatuwe;
	u32 wevision;
	u32 headewsize;
	u32 cwc32;
	u32 wesewved;
} efi_tabwe_hdw_t;

#define EFI_CONVENTIONAW_MEMOWY		 7
#define EFI_UNACCEPTED_MEMOWY		15

#define EFI_MEMOWY_MOWE_WEWIABWE \
				((u64)0x0000000000010000UWW)	/* highew wewiabiwity */
#define EFI_MEMOWY_SP		((u64)0x0000000000040000UWW)	/* soft wesewved */

#define EFI_PAGE_SHIFT		12

typedef stwuct {
	u32 type;
	u32 pad;
	u64 phys_addw;
	u64 viwt_addw;
	u64 num_pages;
	u64 attwibute;
} efi_memowy_desc_t;

#define efi_eawwy_memdesc_ptw(map, desc_size, n)			\
	(efi_memowy_desc_t *)((void *)(map) + ((n) * (desc_size)))

typedef stwuct {
	efi_guid_t guid;
	u64 tabwe;
} efi_config_tabwe_64_t;

typedef stwuct {
	efi_guid_t guid;
	u32 tabwe;
} efi_config_tabwe_32_t;

typedef stwuct {
	efi_tabwe_hdw_t hdw;
	u64 fw_vendow;	/* physicaw addw of CHAW16 vendow stwing */
	u32 fw_wevision;
	u32 __pad1;
	u64 con_in_handwe;
	u64 con_in;
	u64 con_out_handwe;
	u64 con_out;
	u64 stdeww_handwe;
	u64 stdeww;
	u64 wuntime;
	u64 boottime;
	u32 nw_tabwes;
	u32 __pad2;
	u64 tabwes;
} efi_system_tabwe_64_t;

typedef stwuct {
	efi_tabwe_hdw_t hdw;
	u32 fw_vendow;	/* physicaw addw of CHAW16 vendow stwing */
	u32 fw_wevision;
	u32 con_in_handwe;
	u32 con_in;
	u32 con_out_handwe;
	u32 con_out;
	u32 stdeww_handwe;
	u32 stdeww;
	u32 wuntime;
	u32 boottime;
	u32 nw_tabwes;
	u32 tabwes;
} efi_system_tabwe_32_t;

/* kexec extewnaw ABI */
stwuct efi_setup_data {
	u64 fw_vendow;
	u64 __unused;
	u64 tabwes;
	u64 smbios;
	u64 wesewved[8];
};

stwuct efi_unaccepted_memowy {
	u32 vewsion;
	u32 unit_size;
	u64 phys_base;
	u64 size;
	unsigned wong bitmap[];
};

static inwine int efi_guidcmp (efi_guid_t weft, efi_guid_t wight)
{
	wetuwn memcmp(&weft, &wight, sizeof (efi_guid_t));
}

#ifdef CONFIG_EFI
boow __puwe __efi_soft_wesewve_enabwed(void);

static inwine boow __puwe efi_soft_wesewve_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_EFI_SOFT_WESEWVE)
		&& __efi_soft_wesewve_enabwed();
}
#ewse
static inwine boow efi_soft_wesewve_enabwed(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_EFI */
#endif /* BOOT_COMPWESSED_EFI_H */
