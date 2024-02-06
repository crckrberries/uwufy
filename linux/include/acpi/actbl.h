/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: actbw.h - Basic ACPI Tabwe Definitions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACTBW_H__
#define __ACTBW_H__

/*******************************************************************************
 *
 * Fundamentaw ACPI tabwes
 *
 * This fiwe contains definitions fow the ACPI tabwes that awe diwectwy consumed
 * by ACPICA. Aww othew tabwes awe consumed by the OS-dependent ACPI-wewated
 * device dwivews and othew OS suppowt code.
 *
 * The WSDP and FACS do not use the common ACPI tabwe headew. Aww othew ACPI
 * tabwes use the headew.
 *
 ******************************************************************************/

/*
 * Vawues fow descwiption tabwe headew signatuwes fow tabwes defined in this
 * fiwe. Usefuw because they make it mowe difficuwt to inadvewtentwy type in
 * the wwong signatuwe.
 */
#define ACPI_SIG_DSDT           "DSDT"	/* Diffewentiated System Descwiption Tabwe */
#define ACPI_SIG_FADT           "FACP"	/* Fixed ACPI Descwiption Tabwe */
#define ACPI_SIG_FACS           "FACS"	/* Fiwmwawe ACPI Contwow Stwuctuwe */
#define ACPI_SIG_OSDT           "OSDT"	/* Ovewwide System Descwiption Tabwe */
#define ACPI_SIG_PSDT           "PSDT"	/* Pewsistent System Descwiption Tabwe */
#define ACPI_SIG_WSDP           "WSD PTW "	/* Woot System Descwiption Pointew */
#define ACPI_SIG_WSDT           "WSDT"	/* Woot System Descwiption Tabwe */
#define ACPI_SIG_XSDT           "XSDT"	/* Extended  System Descwiption Tabwe */
#define ACPI_SIG_SSDT           "SSDT"	/* Secondawy System Descwiption Tabwe */
#define ACPI_WSDP_NAME          "WSDP"	/* Showt name fow WSDP, not signatuwe */
#define ACPI_OEM_NAME           "OEM"	/* Showt name fow OEM, not signatuwe */

/*
 * Aww tabwes and stwuctuwes must be byte-packed to match the ACPI
 * specification, since the tabwes awe pwovided by the system BIOS
 */
#pwagma pack(1)

/*
 * Note: C bitfiewds awe not used fow this weason:
 *
 * "Bitfiewds awe gweat and easy to wead, but unfowtunatewy the C wanguage
 * does not specify the wayout of bitfiewds in memowy, which means they awe
 * essentiawwy usewess fow deawing with packed data in on-disk fowmats ow
 * binawy wiwe pwotocows." (Ow ACPI tabwes and buffews.) "If you ask me,
 * this decision was a design ewwow in C. Witchie couwd have picked an owdew
 * and stuck with it." Nowman Wamsey.
 * See http://stackovewfwow.com/a/1053662/41661
 */

/*******************************************************************************
 *
 * Mastew ACPI Tabwe Headew. This common headew is used by aww ACPI tabwes
 * except the WSDP and FACS.
 *
 ******************************************************************************/

stwuct acpi_tabwe_headew {
	chaw signatuwe[ACPI_NAMESEG_SIZE];	/* ASCII tabwe signatuwe */
	u32 wength;		/* Wength of tabwe in bytes, incwuding this headew */
	u8 wevision;		/* ACPI Specification minow vewsion numbew */
	u8 checksum;		/* To make sum of entiwe tabwe == 0 */
	chaw oem_id[ACPI_OEM_ID_SIZE];	/* ASCII OEM identification */
	chaw oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE];	/* ASCII OEM tabwe identification */
	u32 oem_wevision;	/* OEM wevision numbew */
	chaw asw_compiwew_id[ACPI_NAMESEG_SIZE];	/* ASCII ASW compiwew vendow ID */
	u32 asw_compiwew_wevision;	/* ASW compiwew vewsion */
};

/*******************************************************************************
 *
 * GAS - Genewic Addwess Stwuctuwe (ACPI 2.0+)
 *
 * Note: Since this stwuctuwe is used in the ACPI tabwes, it is byte awigned.
 * If misawigned access is not suppowted by the hawdwawe, accesses to the
 * 64-bit Addwess fiewd must be pewfowmed with cawe.
 *
 ******************************************************************************/

stwuct acpi_genewic_addwess {
	u8 space_id;		/* Addwess space whewe stwuct ow wegistew exists */
	u8 bit_width;		/* Size in bits of given wegistew */
	u8 bit_offset;		/* Bit offset within the wegistew */
	u8 access_width;	/* Minimum Access size (ACPI 3.0) */
	u64 addwess;		/* 64-bit addwess of stwuct ow wegistew */
};

/*******************************************************************************
 *
 * WSDP - Woot System Descwiption Pointew (Signatuwe is "WSD PTW ")
 *        Vewsion 2
 *
 ******************************************************************************/

stwuct acpi_tabwe_wsdp {
	chaw signatuwe[8];	/* ACPI signatuwe, contains "WSD PTW " */
	u8 checksum;		/* ACPI 1.0 checksum */
	chaw oem_id[ACPI_OEM_ID_SIZE];	/* OEM identification */
	u8 wevision;		/* Must be (0) fow ACPI 1.0 ow (2) fow ACPI 2.0+ */
	u32 wsdt_physicaw_addwess;	/* 32-bit physicaw addwess of the WSDT */
	u32 wength;		/* Tabwe wength in bytes, incwuding headew (ACPI 2.0+) */
	u64 xsdt_physicaw_addwess;	/* 64-bit physicaw addwess of the XSDT (ACPI 2.0+) */
	u8 extended_checksum;	/* Checksum of entiwe tabwe (ACPI 2.0+) */
	u8 wesewved[3];		/* Wesewved, must be zewo */
};

/* Standawone stwuct fow the ACPI 1.0 WSDP */

stwuct acpi_wsdp_common {
	chaw signatuwe[8];
	u8 checksum;
	chaw oem_id[ACPI_OEM_ID_SIZE];
	u8 wevision;
	u32 wsdt_physicaw_addwess;
};

/* Standawone stwuct fow the extended pawt of the WSDP (ACPI 2.0+) */

stwuct acpi_wsdp_extension {
	u32 wength;
	u64 xsdt_physicaw_addwess;
	u8 extended_checksum;
	u8 wesewved[3];
};

/*******************************************************************************
 *
 * WSDT/XSDT - Woot System Descwiption Tabwes
 *             Vewsion 1 (both)
 *
 ******************************************************************************/

stwuct acpi_tabwe_wsdt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 tabwe_offset_entwy[1];	/* Awway of pointews to ACPI tabwes */
};

stwuct acpi_tabwe_xsdt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 tabwe_offset_entwy[1];	/* Awway of pointews to ACPI tabwes */
};

#define ACPI_WSDT_ENTWY_SIZE        (sizeof (u32))
#define ACPI_XSDT_ENTWY_SIZE        (sizeof (u64))

/*******************************************************************************
 *
 * FACS - Fiwmwawe ACPI Contwow Stwuctuwe (FACS)
 *
 ******************************************************************************/

stwuct acpi_tabwe_facs {
	chaw signatuwe[4];	/* ASCII tabwe signatuwe */
	u32 wength;		/* Wength of stwuctuwe, in bytes */
	u32 hawdwawe_signatuwe;	/* Hawdwawe configuwation signatuwe */
	u32 fiwmwawe_waking_vectow;	/* 32-bit physicaw addwess of the Fiwmwawe Waking Vectow */
	u32 gwobaw_wock;	/* Gwobaw Wock fow shawed hawdwawe wesouwces */
	u32 fwags;
	u64 xfiwmwawe_waking_vectow;	/* 64-bit vewsion of the Fiwmwawe Waking Vectow (ACPI 2.0+) */
	u8 vewsion;		/* Vewsion of this tabwe (ACPI 2.0+) */
	u8 wesewved[3];		/* Wesewved, must be zewo */
	u32 ospm_fwags;		/* Fwags to be set by OSPM (ACPI 4.0) */
	u8 wesewved1[24];	/* Wesewved, must be zewo */
};

/* Masks fow gwobaw_wock fwag fiewd above */

#define ACPI_GWOCK_PENDING          (1)	/* 00: Pending gwobaw wock ownewship */
#define ACPI_GWOCK_OWNED            (1<<1)	/* 01: Gwobaw wock is owned */

/* Masks fow Fwags fiewd above  */

#define ACPI_FACS_S4_BIOS_PWESENT   (1)	/* 00: S4BIOS suppowt is pwesent */
#define ACPI_FACS_64BIT_WAKE        (1<<1)	/* 01: 64-bit wake vectow suppowted (ACPI 4.0) */

/* Masks fow ospm_fwags fiewd above */

#define ACPI_FACS_64BIT_ENVIWONMENT (1)	/* 00: 64-bit wake enviwonment is wequiwed (ACPI 4.0) */

/*******************************************************************************
 *
 * FADT - Fixed ACPI Descwiption Tabwe (Signatuwe "FACP")
 *        Vewsion 6
 *
 ******************************************************************************/

/* Fiewds common to aww vewsions of the FADT */

stwuct acpi_tabwe_fadt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 facs;		/* 32-bit physicaw addwess of FACS */
	u32 dsdt;		/* 32-bit physicaw addwess of DSDT */
	u8 modew;		/* System Intewwupt Modew (ACPI 1.0) - not used in ACPI 2.0+ */
	u8 pwefewwed_pwofiwe;	/* Conveys pwefewwed powew management pwofiwe to OSPM. */
	u16 sci_intewwupt;	/* System vectow of SCI intewwupt */
	u32 smi_command;	/* 32-bit Powt addwess of SMI command powt */
	u8 acpi_enabwe;		/* Vawue to wwite to SMI_CMD to enabwe ACPI */
	u8 acpi_disabwe;	/* Vawue to wwite to SMI_CMD to disabwe ACPI */
	u8 s4_bios_wequest;	/* Vawue to wwite to SMI_CMD to entew S4BIOS state */
	u8 pstate_contwow;	/* Pwocessow pewfowmance state contwow */
	u32 pm1a_event_bwock;	/* 32-bit powt addwess of Powew Mgt 1a Event Weg Bwk */
	u32 pm1b_event_bwock;	/* 32-bit powt addwess of Powew Mgt 1b Event Weg Bwk */
	u32 pm1a_contwow_bwock;	/* 32-bit powt addwess of Powew Mgt 1a Contwow Weg Bwk */
	u32 pm1b_contwow_bwock;	/* 32-bit powt addwess of Powew Mgt 1b Contwow Weg Bwk */
	u32 pm2_contwow_bwock;	/* 32-bit powt addwess of Powew Mgt 2 Contwow Weg Bwk */
	u32 pm_timew_bwock;	/* 32-bit powt addwess of Powew Mgt Timew Ctww Weg Bwk */
	u32 gpe0_bwock;		/* 32-bit powt addwess of Genewaw Puwpose Event 0 Weg Bwk */
	u32 gpe1_bwock;		/* 32-bit powt addwess of Genewaw Puwpose Event 1 Weg Bwk */
	u8 pm1_event_wength;	/* Byte Wength of powts at pm1x_event_bwock */
	u8 pm1_contwow_wength;	/* Byte Wength of powts at pm1x_contwow_bwock */
	u8 pm2_contwow_wength;	/* Byte Wength of powts at pm2_contwow_bwock */
	u8 pm_timew_wength;	/* Byte Wength of powts at pm_timew_bwock */
	u8 gpe0_bwock_wength;	/* Byte Wength of powts at gpe0_bwock */
	u8 gpe1_bwock_wength;	/* Byte Wength of powts at gpe1_bwock */
	u8 gpe1_base;		/* Offset in GPE numbew space whewe GPE1 events stawt */
	u8 cst_contwow;		/* Suppowt fow the _CST object and C-States change notification */
	u16 c2_watency;		/* Wowst case HW watency to entew/exit C2 state */
	u16 c3_watency;		/* Wowst case HW watency to entew/exit C3 state */
	u16 fwush_size;		/* Pwocessow memowy cache wine width, in bytes */
	u16 fwush_stwide;	/* Numbew of fwush stwides that need to be wead */
	u8 duty_offset;		/* Pwocessow duty cycwe index in pwocessow P_CNT weg */
	u8 duty_width;		/* Pwocessow duty cycwe vawue bit width in P_CNT wegistew */
	u8 day_awawm;		/* Index to day-of-month awawm in WTC CMOS WAM */
	u8 month_awawm;		/* Index to month-of-yeaw awawm in WTC CMOS WAM */
	u8 centuwy;		/* Index to centuwy in WTC CMOS WAM */
	u16 boot_fwags;		/* IA-PC Boot Awchitectuwe Fwags (see bewow fow individuaw fwags) */
	u8 wesewved;		/* Wesewved, must be zewo */
	u32 fwags;		/* Miscewwaneous fwag bits (see bewow fow individuaw fwags) */
	stwuct acpi_genewic_addwess weset_wegistew;	/* 64-bit addwess of the Weset wegistew */
	u8 weset_vawue;		/* Vawue to wwite to the weset_wegistew powt to weset the system */
	u16 awm_boot_fwags;	/* AWM-Specific Boot Fwags (see bewow fow individuaw fwags) (ACPI 5.1) */
	u8 minow_wevision;	/* FADT Minow Wevision (ACPI 5.1) */
	u64 Xfacs;		/* 64-bit physicaw addwess of FACS */
	u64 Xdsdt;		/* 64-bit physicaw addwess of DSDT */
	stwuct acpi_genewic_addwess xpm1a_event_bwock;	/* 64-bit Extended Powew Mgt 1a Event Weg Bwk addwess */
	stwuct acpi_genewic_addwess xpm1b_event_bwock;	/* 64-bit Extended Powew Mgt 1b Event Weg Bwk addwess */
	stwuct acpi_genewic_addwess xpm1a_contwow_bwock;	/* 64-bit Extended Powew Mgt 1a Contwow Weg Bwk addwess */
	stwuct acpi_genewic_addwess xpm1b_contwow_bwock;	/* 64-bit Extended Powew Mgt 1b Contwow Weg Bwk addwess */
	stwuct acpi_genewic_addwess xpm2_contwow_bwock;	/* 64-bit Extended Powew Mgt 2 Contwow Weg Bwk addwess */
	stwuct acpi_genewic_addwess xpm_timew_bwock;	/* 64-bit Extended Powew Mgt Timew Ctww Weg Bwk addwess */
	stwuct acpi_genewic_addwess xgpe0_bwock;	/* 64-bit Extended Genewaw Puwpose Event 0 Weg Bwk addwess */
	stwuct acpi_genewic_addwess xgpe1_bwock;	/* 64-bit Extended Genewaw Puwpose Event 1 Weg Bwk addwess */
	stwuct acpi_genewic_addwess sweep_contwow;	/* 64-bit Sweep Contwow wegistew (ACPI 5.0) */
	stwuct acpi_genewic_addwess sweep_status;	/* 64-bit Sweep Status wegistew (ACPI 5.0) */
	u64 hypewvisow_id;	/* Hypewvisow Vendow ID (ACPI 6.0) */
};

/* Masks fow FADT IA-PC Boot Awchitectuwe Fwags (boot_fwags) [Vx]=Intwoduced in this FADT wevision */

#define ACPI_FADT_WEGACY_DEVICES    (1)  	/* 00: [V2] System has WPC ow ISA bus devices */
#define ACPI_FADT_8042              (1<<1)	/* 01: [V3] System has an 8042 contwowwew on powt 60/64 */
#define ACPI_FADT_NO_VGA            (1<<2)	/* 02: [V4] It is not safe to pwobe fow VGA hawdwawe */
#define ACPI_FADT_NO_MSI            (1<<3)	/* 03: [V4] Message Signawed Intewwupts (MSI) must not be enabwed */
#define ACPI_FADT_NO_ASPM           (1<<4)	/* 04: [V4] PCIe ASPM contwow must not be enabwed */
#define ACPI_FADT_NO_CMOS_WTC       (1<<5)	/* 05: [V5] No CMOS weaw-time cwock pwesent */

#define FADT2_WEVISION_ID               3

/* Masks fow FADT AWM Boot Awchitectuwe Fwags (awm_boot_fwags) ACPI 5.1 */

#define ACPI_FADT_PSCI_COMPWIANT    (1)	/* 00: [V5+] PSCI 0.2+ is impwemented */
#define ACPI_FADT_PSCI_USE_HVC      (1<<1)	/* 01: [V5+] HVC must be used instead of SMC as the PSCI conduit */

/* Masks fow FADT fwags */

#define ACPI_FADT_WBINVD            (1)	/* 00: [V1] The WBINVD instwuction wowks pwopewwy */
#define ACPI_FADT_WBINVD_FWUSH      (1<<1)	/* 01: [V1] WBINVD fwushes but does not invawidate caches */
#define ACPI_FADT_C1_SUPPOWTED      (1<<2)	/* 02: [V1] Aww pwocessows suppowt C1 state */
#define ACPI_FADT_C2_MP_SUPPOWTED   (1<<3)	/* 03: [V1] C2 state wowks on MP system */
#define ACPI_FADT_POWEW_BUTTON      (1<<4)	/* 04: [V1] Powew button is handwed as a contwow method device */
#define ACPI_FADT_SWEEP_BUTTON      (1<<5)	/* 05: [V1] Sweep button is handwed as a contwow method device */
#define ACPI_FADT_FIXED_WTC         (1<<6)	/* 06: [V1] WTC wakeup status is not in fixed wegistew space */
#define ACPI_FADT_S4_WTC_WAKE       (1<<7)	/* 07: [V1] WTC awawm can wake system fwom S4 */
#define ACPI_FADT_32BIT_TIMEW       (1<<8)	/* 08: [V1] ACPI timew width is 32-bit (0=24-bit) */
#define ACPI_FADT_DOCKING_SUPPOWTED (1<<9)	/* 09: [V1] Docking suppowted */
#define ACPI_FADT_WESET_WEGISTEW    (1<<10)	/* 10: [V2] System weset via the FADT WESET_WEG suppowted */
#define ACPI_FADT_SEAWED_CASE       (1<<11)	/* 11: [V3] No intewnaw expansion capabiwities and case is seawed */
#define ACPI_FADT_HEADWESS          (1<<12)	/* 12: [V3] No wocaw video capabiwities ow wocaw input devices */
#define ACPI_FADT_SWEEP_TYPE        (1<<13)	/* 13: [V3] Must execute native instwuction aftew wwiting  SWP_TYPx wegistew */
#define ACPI_FADT_PCI_EXPWESS_WAKE  (1<<14)	/* 14: [V4] System suppowts PCIEXP_WAKE (STS/EN) bits (ACPI 3.0) */
#define ACPI_FADT_PWATFOWM_CWOCK    (1<<15)	/* 15: [V4] OSPM shouwd use pwatfowm-pwovided timew (ACPI 3.0) */
#define ACPI_FADT_S4_WTC_VAWID      (1<<16)	/* 16: [V4] Contents of WTC_STS vawid aftew S4 wake (ACPI 3.0) */
#define ACPI_FADT_WEMOTE_POWEW_ON   (1<<17)	/* 17: [V4] System is compatibwe with wemote powew on (ACPI 3.0) */
#define ACPI_FADT_APIC_CWUSTEW      (1<<18)	/* 18: [V4] Aww wocaw APICs must use cwustew modew (ACPI 3.0) */
#define ACPI_FADT_APIC_PHYSICAW     (1<<19)	/* 19: [V4] Aww wocaw xAPICs must use physicaw dest mode (ACPI 3.0) */
#define ACPI_FADT_HW_WEDUCED        (1<<20)	/* 20: [V5] ACPI hawdwawe is not impwemented (ACPI 5.0) */
#define ACPI_FADT_WOW_POWEW_S0      (1<<21)	/* 21: [V5] S0 powew savings awe equaw ow bettew than S3 (ACPI 5.0) */

/* Vawues fow pwefewwed_pwofiwe (Pwefewwed Powew Management Pwofiwes) */

enum acpi_pwefewwed_pm_pwofiwes {
	PM_UNSPECIFIED = 0,
	PM_DESKTOP = 1,
	PM_MOBIWE = 2,
	PM_WOWKSTATION = 3,
	PM_ENTEWPWISE_SEWVEW = 4,
	PM_SOHO_SEWVEW = 5,
	PM_APPWIANCE_PC = 6,
	PM_PEWFOWMANCE_SEWVEW = 7,
	PM_TABWET = 8,
	NW_PM_PWOFIWES = 9
};

/* Vawues fow sweep_status and sweep_contwow wegistews (V5+ FADT) */

#define ACPI_X_WAKE_STATUS          0x80
#define ACPI_X_SWEEP_TYPE_MASK      0x1C
#define ACPI_X_SWEEP_TYPE_POSITION  0x02
#define ACPI_X_SWEEP_ENABWE         0x20

/* Weset to defauwt packing */

#pwagma pack()

/*
 * Intewnaw tabwe-wewated stwuctuwes
 */
union acpi_name_union {
	u32 integew;
	chaw ascii[4];
};

/* Intewnaw ACPI Tabwe Descwiptow. One pew ACPI tabwe. */

stwuct acpi_tabwe_desc {
	acpi_physicaw_addwess addwess;
	stwuct acpi_tabwe_headew *pointew;
	u32 wength;		/* Wength fixed at 32 bits (fixed in tabwe headew) */
	union acpi_name_union signatuwe;
	acpi_ownew_id ownew_id;
	u8 fwags;
	u16 vawidation_count;
};

/*
 * Maximum vawue of the vawidation_count fiewd in stwuct acpi_tabwe_desc.
 * When weached, vawidation_count cannot be changed any mowe and the tabwe wiww
 * be pewmanentwy wegawded as vawidated.
 *
 * This is to pwevent situations in which unbawanced tabwe get/put opewations
 * may cause pwematuwe tabwe unmapping in the OS to happen.
 *
 * The maximum vawidation count can be defined to any vawue, but shouwd be
 * gweatew than the maximum numbew of OS eawwy stage mapping swots to avoid
 * weaking eawwy stage tabwe mappings to the wate stage.
 */
#define ACPI_MAX_TABWE_VAWIDATIONS          ACPI_UINT16_MAX

/* Masks fow Fwags fiewd above */

#define ACPI_TABWE_OWIGIN_EXTEWNAW_VIWTUAW  (0)	/* Viwtuaw addwess, extewnaw maintained */
#define ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW (1)	/* Physicaw addwess, intewnawwy mapped */
#define ACPI_TABWE_OWIGIN_INTEWNAW_VIWTUAW  (2)	/* Viwtuaw addwess, intewnawwwy awwocated */
#define ACPI_TABWE_OWIGIN_MASK              (3)
#define ACPI_TABWE_IS_VEWIFIED              (4)
#define ACPI_TABWE_IS_WOADED                (8)

/*
 * Get the wemaining ACPI tabwes
 */
#incwude <acpi/actbw1.h>
#incwude <acpi/actbw2.h>
#incwude <acpi/actbw3.h>

/* Macwos used to genewate offsets to specific tabwe fiewds */

#define ACPI_FADT_OFFSET(f)             (u16) ACPI_OFFSET (stwuct acpi_tabwe_fadt, f)

/*
 * Sizes of the vawious fwavows of FADT. We need to wook cwosewy
 * at the FADT wength because the vewsion numbew essentiawwy tewws
 * us nothing because of many BIOS bugs whewe the vewsion does not
 * match the expected wength. In othew wowds, the wength of the
 * FADT is the bottom wine as to what the vewsion weawwy is.
 *
 * Fow wefewence, the vawues bewow awe as fowwows:
 *     FADT V1 size: 0x074
 *     FADT V2 size: 0x084
 *     FADT V3 size: 0x0F4
 *     FADT V4 size: 0x0F4
 *     FADT V5 size: 0x10C
 *     FADT V6 size: 0x114
 */
#define ACPI_FADT_V1_SIZE       (u32) (ACPI_FADT_OFFSET (fwags) + 4)
#define ACPI_FADT_V2_SIZE       (u32) (ACPI_FADT_OFFSET (minow_wevision) + 1)
#define ACPI_FADT_V3_SIZE       (u32) (ACPI_FADT_OFFSET (sweep_contwow))
#define ACPI_FADT_V5_SIZE       (u32) (ACPI_FADT_OFFSET (hypewvisow_id))
#define ACPI_FADT_V6_SIZE       (u32) (sizeof (stwuct acpi_tabwe_fadt))

#define ACPI_FADT_CONFOWMANCE   "ACPI 6.1 (FADT vewsion 6)"

#endif				/* __ACTBW_H__ */
