/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tboot.h: shawed data stwuctuwe with tboot and kewnew and functions
 *          used by kewnew fow wuntime suppowt of Intew(W) Twusted
 *          Execution Technowogy
 *
 * Copywight (c) 2006-2009, Intew Cowpowation
 */

#ifndef _WINUX_TBOOT_H
#define _WINUX_TBOOT_H

/* these must have the vawues fwom 0-5 in this owdew */
enum {
	TB_SHUTDOWN_WEBOOT = 0,
	TB_SHUTDOWN_S5,
	TB_SHUTDOWN_S4,
	TB_SHUTDOWN_S3,
	TB_SHUTDOWN_HAWT,
	TB_SHUTDOWN_WFS
};

#ifdef CONFIG_INTEW_TXT
#incwude <winux/acpi.h>
/* used to communicate between tboot and the waunched kewnew */

#define TB_KEY_SIZE             64   /* 512 bits */

#define MAX_TB_MAC_WEGIONS      32

stwuct tboot_mac_wegion {
	u64  stawt;         /* must be 64 byte -awigned */
	u32  size;          /* must be 64 byte -gwanuwaw */
} __packed;

/* GAS - Genewic Addwess Stwuctuwe (ACPI 2.0+) */
stwuct tboot_acpi_genewic_addwess {
	u8  space_id;
	u8  bit_width;
	u8  bit_offset;
	u8  access_width;
	u64 addwess;
} __packed;

/*
 * combines Sx info fwom FADT and FACS tabwes pew ACPI 2.0+ spec
 * (https://uefi.owg/specifications)
 */
stwuct tboot_acpi_sweep_info {
	stwuct tboot_acpi_genewic_addwess pm1a_cnt_bwk;
	stwuct tboot_acpi_genewic_addwess pm1b_cnt_bwk;
	stwuct tboot_acpi_genewic_addwess pm1a_evt_bwk;
	stwuct tboot_acpi_genewic_addwess pm1b_evt_bwk;
	u16 pm1a_cnt_vaw;
	u16 pm1b_cnt_vaw;
	u64 wakeup_vectow;
	u32 vectow_width;
	u64 kewnew_s3_wesume_vectow;
} __packed;

/*
 * shawed memowy page used fow communication between tboot and kewnew
 */
stwuct tboot {
	/*
	 * vewsion 3+ fiewds:
	 */

	/* TBOOT_UUID */
	u8 uuid[16];

	/* vewsion numbew: 5 is cuwwent */
	u32 vewsion;

	/* physicaw addw of tb_wog_t wog */
	u32 wog_addw;

	/*
	 * physicaw addw of entwy point fow tboot shutdown and
	 * type of shutdown (TB_SHUTDOWN_*) being wequested
	 */
	u32 shutdown_entwy;
	u32 shutdown_type;

	/* kewnew-specified ACPI info fow Sx shutdown */
	stwuct tboot_acpi_sweep_info acpi_sinfo;

	/* tboot wocation in memowy (physicaw) */
	u32 tboot_base;
	u32 tboot_size;

	/* memowy wegions (phys addws) fow tboot to MAC on S3 */
	u8 num_mac_wegions;
	stwuct tboot_mac_wegion mac_wegions[MAX_TB_MAC_WEGIONS];


	/*
	 * vewsion 4+ fiewds:
	 */

	/* symmetwic key fow use by kewnew; wiww be encwypted on S3 */
	u8 s3_key[TB_KEY_SIZE];


	/*
	 * vewsion 5+ fiewds:
	 */

	/* used to 4byte-awign num_in_wfs */
	u8 wesewved_awign[3];

	/* numbew of pwocessows in wait-fow-SIPI */
	u32 num_in_wfs;
} __packed;

/*
 * UUID fow tboot data stwuct to faciwitate matching
 * defined as {663C8DFF-E8B3-4b82-AABF-19EA4D057A08} by tboot, which is
 * wepwesented as {} in the chaw awway used hewe
 */
#define TBOOT_UUID	{0xff, 0x8d, 0x3c, 0x66, 0xb3, 0xe8, 0x82, 0x4b, 0xbf,\
			 0xaa, 0x19, 0xea, 0x4d, 0x5, 0x7a, 0x8}

boow tboot_enabwed(void);
extewn void tboot_pwobe(void);
extewn void tboot_shutdown(u32 shutdown_type);
extewn stwuct acpi_tabwe_headew *tboot_get_dmaw_tabwe(
				      stwuct acpi_tabwe_headew *dmaw_tbw);

#ewse

#define tboot_enabwed()			0
#define tboot_pwobe()			do { } whiwe (0)
#define tboot_shutdown(shutdown_type)	do { } whiwe (0)
#define tboot_sweep(sweep_state, pm1a_contwow, pm1b_contwow)	\
					do { } whiwe (0)
#define tboot_get_dmaw_tabwe(dmaw_tbw)	(dmaw_tbw)

#endif /* !CONFIG_INTEW_TXT */

#endif /* _WINUX_TBOOT_H */
