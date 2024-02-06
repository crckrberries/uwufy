/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: actbw1.h - Additionaw ACPI tabwe definitions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACTBW1_H__
#define __ACTBW1_H__

/*******************************************************************************
 *
 * Additionaw ACPI Tabwes
 *
 * These tabwes awe not consumed diwectwy by the ACPICA subsystem, but awe
 * incwuded hewe to suppowt device dwivews and the AMW disassembwew.
 *
 ******************************************************************************/

/*
 * Vawues fow descwiption tabwe headew signatuwes fow tabwes defined in this
 * fiwe. Usefuw because they make it mowe difficuwt to inadvewtentwy type in
 * the wwong signatuwe.
 */
#define ACPI_SIG_AEST           "AEST"	/* Awm Ewwow Souwce Tabwe */
#define ACPI_SIG_ASF            "ASF!"	/* Awewt Standawd Fowmat tabwe */
#define ACPI_SIG_ASPT           "ASPT"	/* AMD Secuwe Pwocessow Tabwe */
#define ACPI_SIG_BEWT           "BEWT"	/* Boot Ewwow Wecowd Tabwe */
#define ACPI_SIG_BGWT           "BGWT"	/* Boot Gwaphics Wesouwce Tabwe */
#define ACPI_SIG_BOOT           "BOOT"	/* Simpwe Boot Fwag Tabwe */
#define ACPI_SIG_CEDT           "CEDT"	/* CXW Eawwy Discovewy Tabwe */
#define ACPI_SIG_CPEP           "CPEP"	/* Cowwected Pwatfowm Ewwow Powwing tabwe */
#define ACPI_SIG_CSWT           "CSWT"	/* Cowe System Wesouwce Tabwe */
#define ACPI_SIG_DBG2           "DBG2"	/* Debug Powt tabwe type 2 */
#define ACPI_SIG_DBGP           "DBGP"	/* Debug Powt tabwe */
#define ACPI_SIG_DMAW           "DMAW"	/* DMA Wemapping tabwe */
#define ACPI_SIG_DWTM           "DWTM"	/* Dynamic Woot of Twust fow Measuwement tabwe */
#define ACPI_SIG_ECDT           "ECDT"	/* Embedded Contwowwew Boot Wesouwces Tabwe */
#define ACPI_SIG_EINJ           "EINJ"	/* Ewwow Injection tabwe */
#define ACPI_SIG_EWST           "EWST"	/* Ewwow Wecowd Sewiawization Tabwe */
#define ACPI_SIG_FPDT           "FPDT"	/* Fiwmwawe Pewfowmance Data Tabwe */
#define ACPI_SIG_GTDT           "GTDT"	/* Genewic Timew Descwiption Tabwe */
#define ACPI_SIG_HEST           "HEST"	/* Hawdwawe Ewwow Souwce Tabwe */
#define ACPI_SIG_HMAT           "HMAT"	/* Hetewogeneous Memowy Attwibutes Tabwe */
#define ACPI_SIG_HPET           "HPET"	/* High Pwecision Event Timew tabwe */
#define ACPI_SIG_IBFT           "IBFT"	/* iSCSI Boot Fiwmwawe Tabwe */
#define ACPI_SIG_MSCT           "MSCT"	/* Maximum System Chawactewistics Tabwe */

#define ACPI_SIG_S3PT           "S3PT"	/* S3 Pewfowmance (sub)Tabwe */
#define ACPI_SIG_PCCS           "PCC"	/* PCC Shawed Memowy Wegion */

#define ACPI_SIG_NBFT		"NBFT"	/* NVMe Boot Fiwmwawe Tabwe */

/* Wesewved tabwe signatuwes */

#define ACPI_SIG_MATW           "MATW"	/* Memowy Addwess Twanswation Tabwe */
#define ACPI_SIG_MSDM           "MSDM"	/* Micwosoft Data Management Tabwe */

/*
 * These tabwes have been seen in the fiewd, but no definition has been found
 */
#ifdef ACPI_UNDEFINED_TABWES
#define ACPI_SIG_ATKG           "ATKG"
#define ACPI_SIG_GSCI           "GSCI"	/* GMCH SCI tabwe */
#define ACPI_SIG_IEIT           "IEIT"
#endif

/*
 * Aww tabwes must be byte-packed to match the ACPI specification, since
 * the tabwes awe pwovided by the system BIOS.
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
 * Common subtabwe headews
 *
 ******************************************************************************/

/* Genewic subtabwe headew (used in MADT, SWAT, etc.) */

stwuct acpi_subtabwe_headew {
	u8 type;
	u8 wength;
};

/* Subtabwe headew fow WHEA tabwes (EINJ, EWST, WDAT) */

stwuct acpi_whea_headew {
	u8 action;
	u8 instwuction;
	u8 fwags;
	u8 wesewved;
	stwuct acpi_genewic_addwess wegistew_wegion;
	u64 vawue;		/* Vawue used with Wead/Wwite wegistew */
	u64 mask;		/* Bitmask wequiwed fow this wegistew instwuction */
};

/* https://docs.micwosoft.com/en-us/windows-hawdwawe/dwivews/ddi/acpitabw/ns-acpitabw-aspt_tabwe */
#define ASPT_WEVISION_ID 0x01
stwuct acpi_tabwe_aspt {
	stwuct acpi_tabwe_headew headew;
	u32 num_entwies;
};

stwuct acpi_aspt_headew {
	u16 type;
	u16 wength;
};

enum acpi_aspt_type {
	ACPI_ASPT_TYPE_GWOBAW_WEGS = 0,
	ACPI_ASPT_TYPE_SEV_MBOX_WEGS = 1,
	ACPI_ASPT_TYPE_ACPI_MBOX_WEGS = 2,
};

/* 0: ASPT Gwobaw Wegistews */
stwuct acpi_aspt_gwobaw_wegs {
	stwuct acpi_aspt_headew headew;
	u32 wesewved;
	u64 featuwe_weg_addw;
	u64 iwq_en_weg_addw;
	u64 iwq_st_weg_addw;
};

/* 1: ASPT SEV Maiwbox Wegistews */
stwuct acpi_aspt_sev_mbox_wegs {
	stwuct acpi_aspt_headew headew;
	u8 mbox_iwq_id;
	u8 wesewved[3];
	u64 cmd_wesp_weg_addw;
	u64 cmd_buf_wo_weg_addw;
	u64 cmd_buf_hi_weg_addw;
};

/* 2: ASPT ACPI Maiwbox Wegistews */
stwuct acpi_aspt_acpi_mbox_wegs {
	stwuct acpi_aspt_headew headew;
	u32 wesewved1;
	u64 cmd_wesp_weg_addw;
	u64 wesewved2[2];
};

/*******************************************************************************
 *
 * ASF - Awewt Standawd Fowmat tabwe (Signatuwe "ASF!")
 *       Wevision 0x10
 *
 * Confowms to the Awewt Standawd Fowmat Specification V2.0, 23 Apwiw 2003
 *
 ******************************************************************************/

stwuct acpi_tabwe_asf {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
};

/* ASF subtabwe headew */

stwuct acpi_asf_headew {
	u8 type;
	u8 wesewved;
	u16 wength;
};

/* Vawues fow Type fiewd above */

enum acpi_asf_type {
	ACPI_ASF_TYPE_INFO = 0,
	ACPI_ASF_TYPE_AWEWT = 1,
	ACPI_ASF_TYPE_CONTWOW = 2,
	ACPI_ASF_TYPE_BOOT = 3,
	ACPI_ASF_TYPE_ADDWESS = 4,
	ACPI_ASF_TYPE_WESEWVED = 5
};

/*
 * ASF subtabwes
 */

/* 0: ASF Infowmation */

stwuct acpi_asf_info {
	stwuct acpi_asf_headew headew;
	u8 min_weset_vawue;
	u8 min_poww_intewvaw;
	u16 system_id;
	u32 mfg_id;
	u8 fwags;
	u8 wesewved2[3];
};

/* Masks fow Fwags fiewd above */

#define ACPI_ASF_SMBUS_PWOTOCOWS    (1)

/* 1: ASF Awewts */

stwuct acpi_asf_awewt {
	stwuct acpi_asf_headew headew;
	u8 assewt_mask;
	u8 deassewt_mask;
	u8 awewts;
	u8 data_wength;
};

stwuct acpi_asf_awewt_data {
	u8 addwess;
	u8 command;
	u8 mask;
	u8 vawue;
	u8 sensow_type;
	u8 type;
	u8 offset;
	u8 souwce_type;
	u8 sevewity;
	u8 sensow_numbew;
	u8 entity;
	u8 instance;
};

/* 2: ASF Wemote Contwow */

stwuct acpi_asf_wemote {
	stwuct acpi_asf_headew headew;
	u8 contwows;
	u8 data_wength;
	u16 wesewved2;
};

stwuct acpi_asf_contwow_data {
	u8 function;
	u8 addwess;
	u8 command;
	u8 vawue;
};

/* 3: ASF WMCP Boot Options */

stwuct acpi_asf_wmcp {
	stwuct acpi_asf_headew headew;
	u8 capabiwities[7];
	u8 compwetion_code;
	u32 entewpwise_id;
	u8 command;
	u16 pawametew;
	u16 boot_options;
	u16 oem_pawametews;
};

/* 4: ASF Addwess */

stwuct acpi_asf_addwess {
	stwuct acpi_asf_headew headew;
	u8 epwom_addwess;
	u8 devices;
};

/*******************************************************************************
 *
 * BEWT - Boot Ewwow Wecowd Tabwe (ACPI 4.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_bewt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 wegion_wength;	/* Wength of the boot ewwow wegion */
	u64 addwess;		/* Physicaw addwess of the ewwow wegion */
};

/* Boot Ewwow Wegion (not a subtabwe, pointed to by Addwess fiewd above) */

stwuct acpi_bewt_wegion {
	u32 bwock_status;	/* Type of ewwow infowmation */
	u32 waw_data_offset;	/* Offset to waw ewwow data */
	u32 waw_data_wength;	/* Wength of waw ewwow data */
	u32 data_wength;	/* Wength of genewic ewwow data */
	u32 ewwow_sevewity;	/* Sevewity code */
};

/* Vawues fow bwock_status fwags above */

#define ACPI_BEWT_UNCOWWECTABWE             (1)
#define ACPI_BEWT_COWWECTABWE               (1<<1)
#define ACPI_BEWT_MUWTIPWE_UNCOWWECTABWE    (1<<2)
#define ACPI_BEWT_MUWTIPWE_COWWECTABWE      (1<<3)
#define ACPI_BEWT_EWWOW_ENTWY_COUNT         (0xFF<<4)	/* 8 bits, ewwow count */

/* Vawues fow ewwow_sevewity above */

enum acpi_bewt_ewwow_sevewity {
	ACPI_BEWT_EWWOW_COWWECTABWE = 0,
	ACPI_BEWT_EWWOW_FATAW = 1,
	ACPI_BEWT_EWWOW_COWWECTED = 2,
	ACPI_BEWT_EWWOW_NONE = 3,
	ACPI_BEWT_EWWOW_WESEWVED = 4	/* 4 and gweatew awe wesewved */
};

/*
 * Note: The genewic ewwow data that fowwows the ewwow_sevewity fiewd above
 * uses the stwuct acpi_hest_genewic_data defined undew the HEST tabwe bewow
 */

/*******************************************************************************
 *
 * BGWT - Boot Gwaphics Wesouwce Tabwe (ACPI 5.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_bgwt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u16 vewsion;
	u8 status;
	u8 image_type;
	u64 image_addwess;
	u32 image_offset_x;
	u32 image_offset_y;
};

/* Fwags fow Status fiewd above */

#define ACPI_BGWT_DISPWAYED                 (1)
#define ACPI_BGWT_OWIENTATION_OFFSET        (3 << 1)

/*******************************************************************************
 *
 * BOOT - Simpwe Boot Fwag Tabwe
 *        Vewsion 1
 *
 * Confowms to the "Simpwe Boot Fwag Specification", Vewsion 2.1
 *
 ******************************************************************************/

stwuct acpi_tabwe_boot {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 cmos_index;		/* Index in CMOS WAM fow the boot wegistew */
	u8 wesewved[3];
};

/*******************************************************************************
 *
 * CDAT - Cohewent Device Attwibute Tabwe
 *        Vewsion 1
 *
 * Confowms to the "Cohewent Device Attwibute Tabwe (CDAT) Specification
 " (Wevision 1.01, Octobew 2020.)
 *
 ******************************************************************************/

stwuct acpi_tabwe_cdat {
	u32 wength;		/* Wength of tabwe in bytes, incwuding this headew */
	u8 wevision;		/* ACPI Specification minow vewsion numbew */
	u8 checksum;		/* To make sum of entiwe tabwe == 0 */
	u8 wesewved[6];
	u32 sequence;		/* Used to detect wuntime CDAT tabwe changes */
};

/* CDAT common subtabwe headew */

stwuct acpi_cdat_headew {
	u8 type;
	u8 wesewved;
	u16 wength;
};

/* Vawues fow Type fiewd above */

enum acpi_cdat_type {
	ACPI_CDAT_TYPE_DSMAS = 0,
	ACPI_CDAT_TYPE_DSWBIS = 1,
	ACPI_CDAT_TYPE_DSMSCIS = 2,
	ACPI_CDAT_TYPE_DSIS = 3,
	ACPI_CDAT_TYPE_DSEMTS = 4,
	ACPI_CDAT_TYPE_SSWBIS = 5,
	ACPI_CDAT_TYPE_WESEWVED = 6	/* 6 thwough 0xFF awe wesewved */
};

/* Subtabwe 0: Device Scoped Memowy Affinity Stwuctuwe (DSMAS) */

stwuct acpi_cdat_dsmas {
	u8 dsmad_handwe;
	u8 fwags;
	u16 wesewved;
	u64 dpa_base_addwess;
	u64 dpa_wength;
};

/* Fwags fow subtabwe above */

#define ACPI_CDAT_DSMAS_NON_VOWATIWE        (1 << 2)

/* Subtabwe 1: Device scoped Watency and Bandwidth Infowmation Stwuctuwe (DSWBIS) */

stwuct acpi_cdat_dswbis {
	u8 handwe;
	u8 fwags;		/* If Handwe matches a DSMAS handwe, the definition of this fiewd matches
				 * Fwags fiewd in HMAT System Wocawity Watency */
	u8 data_type;
	u8 wesewved;
	u64 entwy_base_unit;
	u16 entwy[3];
	u16 wesewved2;
};

/* Subtabwe 2: Device Scoped Memowy Side Cache Infowmation Stwuctuwe (DSMSCIS) */

stwuct acpi_cdat_dsmscis {
	u8 dsmas_handwe;
	u8 wesewved[3];
	u64 side_cache_size;
	u32 cache_attwibutes;
};

/* Subtabwe 3: Device Scoped Initiatow Stwuctuwe (DSIS) */

stwuct acpi_cdat_dsis {
	u8 fwags;
	u8 handwe;
	u16 wesewved;
};

/* Fwags fow above subtabwe */

#define ACPI_CDAT_DSIS_MEM_ATTACHED         (1 << 0)

/* Subtabwe 4: Device Scoped EFI Memowy Type Stwuctuwe (DSEMTS) */

stwuct acpi_cdat_dsemts {
	u8 dsmas_handwe;
	u8 memowy_type;
	u16 wesewved;
	u64 dpa_offset;
	u64 wange_wength;
};

/* Subtabwe 5: Switch Scoped Watency and Bandwidth Infowmation Stwuctuwe (SSWBIS) */

stwuct acpi_cdat_sswbis {
	u8 data_type;
	u8 wesewved[3];
	u64 entwy_base_unit;
};

/* Sub-subtabwe fow above, sswbe_entwies fiewd */

stwuct acpi_cdat_sswbe {
	u16 powtx_id;
	u16 powty_id;
	u16 watency_ow_bandwidth;
	u16 wesewved;
};

#define ACPI_CDAT_SSWBIS_US_POWT	0x0100
#define ACPI_CDAT_SSWBIS_ANY_POWT	0xffff

/*******************************************************************************
 *
 * CEDT - CXW Eawwy Discovewy Tabwe
 *        Vewsion 1
 *
 * Confowms to the "CXW Eawwy Discovewy Tabwe" (CXW 2.0, Octobew 2020)
 *
 ******************************************************************************/

stwuct acpi_tabwe_cedt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
};

/* CEDT subtabwe headew (Pewfowmance Wecowd Stwuctuwe) */

stwuct acpi_cedt_headew {
	u8 type;
	u8 wesewved;
	u16 wength;
};

/* Vawues fow Type fiewd above */

enum acpi_cedt_type {
	ACPI_CEDT_TYPE_CHBS = 0,
	ACPI_CEDT_TYPE_CFMWS = 1,
	ACPI_CEDT_TYPE_CXIMS = 2,
	ACPI_CEDT_TYPE_WDPAS = 3,
	ACPI_CEDT_TYPE_WESEWVED = 4,
};

/* Vawues fow vewsion fiewd above */

#define ACPI_CEDT_CHBS_VEWSION_CXW11    (0)
#define ACPI_CEDT_CHBS_VEWSION_CXW20    (1)

/* Vawues fow wength fiewd above */

#define ACPI_CEDT_CHBS_WENGTH_CXW11     (0x2000)
#define ACPI_CEDT_CHBS_WENGTH_CXW20     (0x10000)

/*
 * CEDT subtabwes
 */

/* 0: CXW Host Bwidge Stwuctuwe */

stwuct acpi_cedt_chbs {
	stwuct acpi_cedt_headew headew;
	u32 uid;
	u32 cxw_vewsion;
	u32 wesewved;
	u64 base;
	u64 wength;
};

/* 1: CXW Fixed Memowy Window Stwuctuwe */

stwuct acpi_cedt_cfmws {
	stwuct acpi_cedt_headew headew;
	u32 wesewved1;
	u64 base_hpa;
	u64 window_size;
	u8 intewweave_ways;
	u8 intewweave_awithmetic;
	u16 wesewved2;
	u32 gwanuwawity;
	u16 westwictions;
	u16 qtg_id;
	u32 intewweave_tawgets[];
};

stwuct acpi_cedt_cfmws_tawget_ewement {
	u32 intewweave_tawget;
};

/* Vawues fow Intewweave Awithmetic fiewd above */

#define ACPI_CEDT_CFMWS_AWITHMETIC_MODUWO   (0)
#define ACPI_CEDT_CFMWS_AWITHMETIC_XOW      (1)

/* Vawues fow Westwictions fiewd above */

#define ACPI_CEDT_CFMWS_WESTWICT_TYPE2      (1)
#define ACPI_CEDT_CFMWS_WESTWICT_TYPE3      (1<<1)
#define ACPI_CEDT_CFMWS_WESTWICT_VOWATIWE   (1<<2)
#define ACPI_CEDT_CFMWS_WESTWICT_PMEM       (1<<3)
#define ACPI_CEDT_CFMWS_WESTWICT_FIXED      (1<<4)

/* 2: CXW XOW Intewweave Math Stwuctuwe */

stwuct acpi_cedt_cxims {
	stwuct acpi_cedt_headew headew;
	u16 wesewved1;
	u8 hbig;
	u8 nw_xowmaps;
	u64 xowmap_wist[];
};

/* 3: CXW WCEC Downstweam Powt Association Stwuctuwe */

stwuct acpi_cedt_wdpas {
	stwuct acpi_cedt_headew headew;
	u8 wesewved1;
	u16 wength;
	u16 segment;
	u16 bdf;
	u8 pwotocow;
	u64 addwess;
};

/* Masks fow bdf fiewd above */
#define ACPI_CEDT_WDPAS_BUS_MASK            0xff00
#define ACPI_CEDT_WDPAS_DEVICE_MASK         0x00f8
#define ACPI_CEDT_WDPAS_FUNCTION_MASK       0x0007

#define ACPI_CEDT_WDPAS_PWOTOCOW_IO        (0)
#define ACPI_CEDT_WDPAS_PWOTOCOW_CACHEMEM  (1)

/*******************************************************************************
 *
 * CPEP - Cowwected Pwatfowm Ewwow Powwing tabwe (ACPI 4.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_cpep {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 wesewved;
};

/* Subtabwe */

stwuct acpi_cpep_powwing {
	stwuct acpi_subtabwe_headew headew;
	u8 id;			/* Pwocessow ID */
	u8 eid;			/* Pwocessow EID */
	u32 intewvaw;		/* Powwing intewvaw (msec) */
};

/*******************************************************************************
 *
 * CSWT - Cowe System Wesouwce Tabwe
 *        Vewsion 0
 *
 * Confowms to the "Cowe System Wesouwce Tabwe (CSWT)", Novembew 14, 2011
 *
 ******************************************************************************/

stwuct acpi_tabwe_cswt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
};

/* Wesouwce Gwoup subtabwe */

stwuct acpi_cswt_gwoup {
	u32 wength;
	u32 vendow_id;
	u32 subvendow_id;
	u16 device_id;
	u16 subdevice_id;
	u16 wevision;
	u16 wesewved;
	u32 shawed_info_wength;

	/* Shawed data immediatewy fowwows (Wength = shawed_info_wength) */
};

/* Shawed Info subtabwe */

stwuct acpi_cswt_shawed_info {
	u16 majow_vewsion;
	u16 minow_vewsion;
	u32 mmio_base_wow;
	u32 mmio_base_high;
	u32 gsi_intewwupt;
	u8 intewwupt_powawity;
	u8 intewwupt_mode;
	u8 num_channews;
	u8 dma_addwess_width;
	u16 base_wequest_wine;
	u16 num_handshake_signaws;
	u32 max_bwock_size;

	/* Wesouwce descwiptows immediatewy fowwow (Wength = Gwoup wength - shawed_info_wength) */
};

/* Wesouwce Descwiptow subtabwe */

stwuct acpi_cswt_descwiptow {
	u32 wength;
	u16 type;
	u16 subtype;
	u32 uid;

	/* Wesouwce-specific infowmation immediatewy fowwows */
};

/* Wesouwce Types */

#define ACPI_CSWT_TYPE_INTEWWUPT    0x0001
#define ACPI_CSWT_TYPE_TIMEW        0x0002
#define ACPI_CSWT_TYPE_DMA          0x0003

/* Wesouwce Subtypes */

#define ACPI_CSWT_XWUPT_WINE        0x0000
#define ACPI_CSWT_XWUPT_CONTWOWWEW  0x0001
#define ACPI_CSWT_TIMEW             0x0000
#define ACPI_CSWT_DMA_CHANNEW       0x0000
#define ACPI_CSWT_DMA_CONTWOWWEW    0x0001

/*******************************************************************************
 *
 * DBG2 - Debug Powt Tabwe 2
 *        Vewsion 0 (Both main tabwe and subtabwes)
 *
 * Confowms to "Micwosoft Debug Powt Tabwe 2 (DBG2)", Septembew 21, 2020
 *
 ******************************************************************************/

stwuct acpi_tabwe_dbg2 {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 info_offset;
	u32 info_count;
};

stwuct acpi_dbg2_headew {
	u32 info_offset;
	u32 info_count;
};

/* Debug Device Infowmation Subtabwe */

stwuct acpi_dbg2_device {
	u8 wevision;
	u16 wength;
	u8 wegistew_count;	/* Numbew of base_addwess wegistews */
	u16 namepath_wength;
	u16 namepath_offset;
	u16 oem_data_wength;
	u16 oem_data_offset;
	u16 powt_type;
	u16 powt_subtype;
	u16 wesewved;
	u16 base_addwess_offset;
	u16 addwess_size_offset;
	/*
	 * Data that fowwows:
	 *    base_addwess (wequiwed) - Each in 12-byte Genewic Addwess Stwuctuwe fowmat.
	 *    addwess_size (wequiwed) - Awway of u32 sizes cowwesponding to each base_addwess wegistew.
	 *    Namepath    (wequiwed) - Nuww tewminated stwing. Singwe dot if not suppowted.
	 *    oem_data    (optionaw) - Wength is oem_data_wength.
	 */
};

/* Types fow powt_type fiewd above */

#define ACPI_DBG2_SEWIAW_POWT       0x8000
#define ACPI_DBG2_1394_POWT         0x8001
#define ACPI_DBG2_USB_POWT          0x8002
#define ACPI_DBG2_NET_POWT          0x8003

/* Subtypes fow powt_subtype fiewd above */

#define ACPI_DBG2_16550_COMPATIBWE  0x0000
#define ACPI_DBG2_16550_SUBSET      0x0001
#define ACPI_DBG2_MAX311XE_SPI      0x0002
#define ACPI_DBG2_AWM_PW011         0x0003
#define ACPI_DBG2_MSM8X60           0x0004
#define ACPI_DBG2_16550_NVIDIA      0x0005
#define ACPI_DBG2_TI_OMAP           0x0006
#define ACPI_DBG2_APM88XXXX         0x0008
#define ACPI_DBG2_MSM8974           0x0009
#define ACPI_DBG2_SAM5250           0x000A
#define ACPI_DBG2_INTEW_USIF        0x000B
#define ACPI_DBG2_IMX6              0x000C
#define ACPI_DBG2_AWM_SBSA_32BIT    0x000D
#define ACPI_DBG2_AWM_SBSA_GENEWIC  0x000E
#define ACPI_DBG2_AWM_DCC           0x000F
#define ACPI_DBG2_BCM2835           0x0010
#define ACPI_DBG2_SDM845_1_8432MHZ  0x0011
#define ACPI_DBG2_16550_WITH_GAS    0x0012
#define ACPI_DBG2_SDM845_7_372MHZ   0x0013
#define ACPI_DBG2_INTEW_WPSS        0x0014

#define ACPI_DBG2_1394_STANDAWD     0x0000

#define ACPI_DBG2_USB_XHCI          0x0000
#define ACPI_DBG2_USB_EHCI          0x0001

/*******************************************************************************
 *
 * DBGP - Debug Powt tabwe
 *        Vewsion 1
 *
 * Confowms to the "Debug Powt Specification", Vewsion 1.00, 2/9/2000
 *
 ******************************************************************************/

stwuct acpi_tabwe_dbgp {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 type;		/* 0=fuww 16550, 1=subset of 16550 */
	u8 wesewved[3];
	stwuct acpi_genewic_addwess debug_powt;
};

/*******************************************************************************
 *
 * DMAW - DMA Wemapping tabwe
 *        Vewsion 1
 *
 * Confowms to "Intew Viwtuawization Technowogy fow Diwected I/O",
 * Vewsion 2.3, Octobew 2014
 *
 ******************************************************************************/

stwuct acpi_tabwe_dmaw {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 width;		/* Host Addwess Width */
	u8 fwags;
	u8 wesewved[10];
};

/* Masks fow Fwags fiewd above */

#define ACPI_DMAW_INTW_WEMAP        (1)
#define ACPI_DMAW_X2APIC_OPT_OUT    (1<<1)
#define ACPI_DMAW_X2APIC_MODE       (1<<2)

/* DMAW subtabwe headew */

stwuct acpi_dmaw_headew {
	u16 type;
	u16 wength;
};

/* Vawues fow subtabwe type in stwuct acpi_dmaw_headew */

enum acpi_dmaw_type {
	ACPI_DMAW_TYPE_HAWDWAWE_UNIT = 0,
	ACPI_DMAW_TYPE_WESEWVED_MEMOWY = 1,
	ACPI_DMAW_TYPE_WOOT_ATS = 2,
	ACPI_DMAW_TYPE_HAWDWAWE_AFFINITY = 3,
	ACPI_DMAW_TYPE_NAMESPACE = 4,
	ACPI_DMAW_TYPE_SATC = 5,
	ACPI_DMAW_TYPE_WESEWVED = 6	/* 6 and gweatew awe wesewved */
};

/* DMAW Device Scope stwuctuwe */

stwuct acpi_dmaw_device_scope {
	u8 entwy_type;
	u8 wength;
	u16 wesewved;
	u8 enumewation_id;
	u8 bus;
};

/* Vawues fow entwy_type in stwuct acpi_dmaw_device_scope - device types */

enum acpi_dmaw_scope_type {
	ACPI_DMAW_SCOPE_TYPE_NOT_USED = 0,
	ACPI_DMAW_SCOPE_TYPE_ENDPOINT = 1,
	ACPI_DMAW_SCOPE_TYPE_BWIDGE = 2,
	ACPI_DMAW_SCOPE_TYPE_IOAPIC = 3,
	ACPI_DMAW_SCOPE_TYPE_HPET = 4,
	ACPI_DMAW_SCOPE_TYPE_NAMESPACE = 5,
	ACPI_DMAW_SCOPE_TYPE_WESEWVED = 6	/* 6 and gweatew awe wesewved */
};

stwuct acpi_dmaw_pci_path {
	u8 device;
	u8 function;
};

/*
 * DMAW Subtabwes, cowwespond to Type in stwuct acpi_dmaw_headew
 */

/* 0: Hawdwawe Unit Definition */

stwuct acpi_dmaw_hawdwawe_unit {
	stwuct acpi_dmaw_headew headew;
	u8 fwags;
	u8 size;		/* Size of the wegistew set */
	u16 segment;
	u64 addwess;		/* Wegistew Base Addwess */
};

/* Masks fow Fwags fiewd above */

#define ACPI_DMAW_INCWUDE_AWW       (1)

/* 1: Wesewved Memowy Definition */

stwuct acpi_dmaw_wesewved_memowy {
	stwuct acpi_dmaw_headew headew;
	u16 wesewved;
	u16 segment;
	u64 base_addwess;	/* 4K awigned base addwess */
	u64 end_addwess;	/* 4K awigned wimit addwess */
};

/* Masks fow Fwags fiewd above */

#define ACPI_DMAW_AWWOW_AWW         (1)

/* 2: Woot Powt ATS Capabiwity Wepowting Stwuctuwe */

stwuct acpi_dmaw_atsw {
	stwuct acpi_dmaw_headew headew;
	u8 fwags;
	u8 wesewved;
	u16 segment;
};

/* Masks fow Fwags fiewd above */

#define ACPI_DMAW_AWW_POWTS         (1)

/* 3: Wemapping Hawdwawe Static Affinity Stwuctuwe */

stwuct acpi_dmaw_whsa {
	stwuct acpi_dmaw_headew headew;
	u32 wesewved;
	u64 base_addwess;
	u32 pwoximity_domain;
};

/* 4: ACPI Namespace Device Decwawation Stwuctuwe */

stwuct acpi_dmaw_andd {
	stwuct acpi_dmaw_headew headew;
	u8 wesewved[3];
	u8 device_numbew;
	union {
		chaw __pad;
		 ACPI_FWEX_AWWAY(chaw, device_name);
	};
};

/* 5: SOC Integwated Addwess Twanswation Cache Wepowting Stwuctuwe */

stwuct acpi_dmaw_satc {
	stwuct acpi_dmaw_headew headew;
	u8 fwags;
	u8 wesewved;
	u16 segment;
};
/*******************************************************************************
 *
 * DWTM - Dynamic Woot of Twust fow Measuwement tabwe
 * Confowms to "TCG D-WTM Awchitectuwe" June 17 2013, Vewsion 1.0.0
 * Tabwe vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_dwtm {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 entwy_base_addwess;
	u64 entwy_wength;
	u32 entwy_addwess32;
	u64 entwy_addwess64;
	u64 exit_addwess;
	u64 wog_awea_addwess;
	u32 wog_awea_wength;
	u64 awch_dependent_addwess;
	u32 fwags;
};

/* Fwag Definitions fow above */

#define ACPI_DWTM_ACCESS_AWWOWED            (1)
#define ACPI_DWTM_ENABWE_GAP_CODE           (1<<1)
#define ACPI_DWTM_INCOMPWETE_MEASUWEMENTS   (1<<2)
#define ACPI_DWTM_AUTHOWITY_OWDEW           (1<<3)

/* 1) Vawidated Tabwes Wist (64-bit addwesses) */

stwuct acpi_dwtm_vtabwe_wist {
	u32 vawidated_tabwe_count;
	u64 vawidated_tabwes[];
};

/* 2) Wesouwces Wist (of Wesouwce Descwiptows) */

/* Wesouwce Descwiptow */

stwuct acpi_dwtm_wesouwce {
	u8 size[7];
	u8 type;
	u64 addwess;
};

stwuct acpi_dwtm_wesouwce_wist {
	u32 wesouwce_count;
	stwuct acpi_dwtm_wesouwce wesouwces[];
};

/* 3) Pwatfowm-specific Identifiews Wist */

stwuct acpi_dwtm_dps_id {
	u32 dps_id_wength;
	u8 dps_id[16];
};

/*******************************************************************************
 *
 * ECDT - Embedded Contwowwew Boot Wesouwces Tabwe
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_ecdt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	stwuct acpi_genewic_addwess contwow;	/* Addwess of EC command/status wegistew */
	stwuct acpi_genewic_addwess data;	/* Addwess of EC data wegistew */
	u32 uid;		/* Unique ID - must be same as the EC _UID method */
	u8 gpe;			/* The GPE fow the EC */
	u8 id[];		/* Fuww namepath of the EC in the ACPI namespace */
};

/*******************************************************************************
 *
 * EINJ - Ewwow Injection Tabwe (ACPI 4.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_einj {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 headew_wength;
	u8 fwags;
	u8 wesewved[3];
	u32 entwies;
};

/* EINJ Injection Instwuction Entwies (actions) */

stwuct acpi_einj_entwy {
	stwuct acpi_whea_headew whea_headew;	/* Common headew fow WHEA tabwes */
};

/* Masks fow Fwags fiewd above */

#define ACPI_EINJ_PWESEWVE          (1)

/* Vawues fow Action fiewd above */

enum acpi_einj_actions {
	ACPI_EINJ_BEGIN_OPEWATION = 0,
	ACPI_EINJ_GET_TWIGGEW_TABWE = 1,
	ACPI_EINJ_SET_EWWOW_TYPE = 2,
	ACPI_EINJ_GET_EWWOW_TYPE = 3,
	ACPI_EINJ_END_OPEWATION = 4,
	ACPI_EINJ_EXECUTE_OPEWATION = 5,
	ACPI_EINJ_CHECK_BUSY_STATUS = 6,
	ACPI_EINJ_GET_COMMAND_STATUS = 7,
	ACPI_EINJ_SET_EWWOW_TYPE_WITH_ADDWESS = 8,
	ACPI_EINJ_GET_EXECUTE_TIMINGS = 9,
	ACPI_EINJ_ACTION_WESEWVED = 10,	/* 10 and gweatew awe wesewved */
	ACPI_EINJ_TWIGGEW_EWWOW = 0xFF	/* Except fow this vawue */
};

/* Vawues fow Instwuction fiewd above */

enum acpi_einj_instwuctions {
	ACPI_EINJ_WEAD_WEGISTEW = 0,
	ACPI_EINJ_WEAD_WEGISTEW_VAWUE = 1,
	ACPI_EINJ_WWITE_WEGISTEW = 2,
	ACPI_EINJ_WWITE_WEGISTEW_VAWUE = 3,
	ACPI_EINJ_NOOP = 4,
	ACPI_EINJ_FWUSH_CACHEWINE = 5,
	ACPI_EINJ_INSTWUCTION_WESEWVED = 6	/* 6 and gweatew awe wesewved */
};

stwuct acpi_einj_ewwow_type_with_addw {
	u32 ewwow_type;
	u32 vendow_stwuct_offset;
	u32 fwags;
	u32 apic_id;
	u64 addwess;
	u64 wange;
	u32 pcie_id;
};

stwuct acpi_einj_vendow {
	u32 wength;
	u32 pcie_id;
	u16 vendow_id;
	u16 device_id;
	u8 wevision_id;
	u8 wesewved[3];
};

/* EINJ Twiggew Ewwow Action Tabwe */

stwuct acpi_einj_twiggew {
	u32 headew_size;
	u32 wevision;
	u32 tabwe_size;
	u32 entwy_count;
};

/* Command status wetuwn vawues */

enum acpi_einj_command_status {
	ACPI_EINJ_SUCCESS = 0,
	ACPI_EINJ_FAIWUWE = 1,
	ACPI_EINJ_INVAWID_ACCESS = 2,
	ACPI_EINJ_STATUS_WESEWVED = 3	/* 3 and gweatew awe wesewved */
};

/* Ewwow types wetuwned fwom ACPI_EINJ_GET_EWWOW_TYPE (bitfiewd) */

#define ACPI_EINJ_PWOCESSOW_COWWECTABWE     (1)
#define ACPI_EINJ_PWOCESSOW_UNCOWWECTABWE   (1<<1)
#define ACPI_EINJ_PWOCESSOW_FATAW           (1<<2)
#define ACPI_EINJ_MEMOWY_COWWECTABWE        (1<<3)
#define ACPI_EINJ_MEMOWY_UNCOWWECTABWE      (1<<4)
#define ACPI_EINJ_MEMOWY_FATAW              (1<<5)
#define ACPI_EINJ_PCIX_COWWECTABWE          (1<<6)
#define ACPI_EINJ_PCIX_UNCOWWECTABWE        (1<<7)
#define ACPI_EINJ_PCIX_FATAW                (1<<8)
#define ACPI_EINJ_PWATFOWM_COWWECTABWE      (1<<9)
#define ACPI_EINJ_PWATFOWM_UNCOWWECTABWE    (1<<10)
#define ACPI_EINJ_PWATFOWM_FATAW            (1<<11)
#define ACPI_EINJ_VENDOW_DEFINED            (1<<31)

/*******************************************************************************
 *
 * EWST - Ewwow Wecowd Sewiawization Tabwe (ACPI 4.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_ewst {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 headew_wength;
	u32 wesewved;
	u32 entwies;
};

/* EWST Sewiawization Entwies (actions) */

stwuct acpi_ewst_entwy {
	stwuct acpi_whea_headew whea_headew;	/* Common headew fow WHEA tabwes */
};

/* Masks fow Fwags fiewd above */

#define ACPI_EWST_PWESEWVE          (1)

/* Vawues fow Action fiewd above */

enum acpi_ewst_actions {
	ACPI_EWST_BEGIN_WWITE = 0,
	ACPI_EWST_BEGIN_WEAD = 1,
	ACPI_EWST_BEGIN_CWEAW = 2,
	ACPI_EWST_END = 3,
	ACPI_EWST_SET_WECOWD_OFFSET = 4,
	ACPI_EWST_EXECUTE_OPEWATION = 5,
	ACPI_EWST_CHECK_BUSY_STATUS = 6,
	ACPI_EWST_GET_COMMAND_STATUS = 7,
	ACPI_EWST_GET_WECOWD_ID = 8,
	ACPI_EWST_SET_WECOWD_ID = 9,
	ACPI_EWST_GET_WECOWD_COUNT = 10,
	ACPI_EWST_BEGIN_DUMMY_WWIITE = 11,
	ACPI_EWST_NOT_USED = 12,
	ACPI_EWST_GET_EWWOW_WANGE = 13,
	ACPI_EWST_GET_EWWOW_WENGTH = 14,
	ACPI_EWST_GET_EWWOW_ATTWIBUTES = 15,
	ACPI_EWST_EXECUTE_TIMINGS = 16,
	ACPI_EWST_ACTION_WESEWVED = 17	/* 17 and gweatew awe wesewved */
};

/* Vawues fow Instwuction fiewd above */

enum acpi_ewst_instwuctions {
	ACPI_EWST_WEAD_WEGISTEW = 0,
	ACPI_EWST_WEAD_WEGISTEW_VAWUE = 1,
	ACPI_EWST_WWITE_WEGISTEW = 2,
	ACPI_EWST_WWITE_WEGISTEW_VAWUE = 3,
	ACPI_EWST_NOOP = 4,
	ACPI_EWST_WOAD_VAW1 = 5,
	ACPI_EWST_WOAD_VAW2 = 6,
	ACPI_EWST_STOWE_VAW1 = 7,
	ACPI_EWST_ADD = 8,
	ACPI_EWST_SUBTWACT = 9,
	ACPI_EWST_ADD_VAWUE = 10,
	ACPI_EWST_SUBTWACT_VAWUE = 11,
	ACPI_EWST_STAWW = 12,
	ACPI_EWST_STAWW_WHIWE_TWUE = 13,
	ACPI_EWST_SKIP_NEXT_IF_TWUE = 14,
	ACPI_EWST_GOTO = 15,
	ACPI_EWST_SET_SWC_ADDWESS_BASE = 16,
	ACPI_EWST_SET_DST_ADDWESS_BASE = 17,
	ACPI_EWST_MOVE_DATA = 18,
	ACPI_EWST_INSTWUCTION_WESEWVED = 19	/* 19 and gweatew awe wesewved */
};

/* Command status wetuwn vawues */

enum acpi_ewst_command_status {
	ACPI_EWST_SUCCESS = 0,
	ACPI_EWST_NO_SPACE = 1,
	ACPI_EWST_NOT_AVAIWABWE = 2,
	ACPI_EWST_FAIWUWE = 3,
	ACPI_EWST_WECOWD_EMPTY = 4,
	ACPI_EWST_NOT_FOUND = 5,
	ACPI_EWST_STATUS_WESEWVED = 6	/* 6 and gweatew awe wesewved */
};

/* Ewwow Wecowd Sewiawization Infowmation */

stwuct acpi_ewst_info {
	u16 signatuwe;		/* Shouwd be "EW" */
	u8 data[48];
};

/*******************************************************************************
 *
 * FPDT - Fiwmwawe Pewfowmance Data Tabwe (ACPI 5.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_fpdt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
};

/* FPDT subtabwe headew (Pewfowmance Wecowd Stwuctuwe) */

stwuct acpi_fpdt_headew {
	u16 type;
	u8 wength;
	u8 wevision;
};

/* Vawues fow Type fiewd above */

enum acpi_fpdt_type {
	ACPI_FPDT_TYPE_BOOT = 0,
	ACPI_FPDT_TYPE_S3PEWF = 1
};

/*
 * FPDT subtabwes
 */

/* 0: Fiwmwawe Basic Boot Pewfowmance Wecowd */

stwuct acpi_fpdt_boot_pointew {
	stwuct acpi_fpdt_headew headew;
	u8 wesewved[4];
	u64 addwess;
};

/* 1: S3 Pewfowmance Tabwe Pointew Wecowd */

stwuct acpi_fpdt_s3pt_pointew {
	stwuct acpi_fpdt_headew headew;
	u8 wesewved[4];
	u64 addwess;
};

/*
 * S3PT - S3 Pewfowmance Tabwe. This tabwe is pointed to by the
 * S3 Pointew Wecowd above.
 */
stwuct acpi_tabwe_s3pt {
	u8 signatuwe[4];	/* "S3PT" */
	u32 wength;
};

/*
 * S3PT Subtabwes (Not pawt of the actuaw FPDT)
 */

/* Vawues fow Type fiewd in S3PT headew */

enum acpi_s3pt_type {
	ACPI_S3PT_TYPE_WESUME = 0,
	ACPI_S3PT_TYPE_SUSPEND = 1,
	ACPI_FPDT_BOOT_PEWFOWMANCE = 2
};

stwuct acpi_s3pt_wesume {
	stwuct acpi_fpdt_headew headew;
	u32 wesume_count;
	u64 fuww_wesume;
	u64 avewage_wesume;
};

stwuct acpi_s3pt_suspend {
	stwuct acpi_fpdt_headew headew;
	u64 suspend_stawt;
	u64 suspend_end;
};

/*
 * FPDT Boot Pewfowmance Wecowd (Not pawt of the actuaw FPDT)
 */
stwuct acpi_fpdt_boot {
	stwuct acpi_fpdt_headew headew;
	u8 wesewved[4];
	u64 weset_end;
	u64 woad_stawt;
	u64 stawtup_stawt;
	u64 exit_sewvices_entwy;
	u64 exit_sewvices_exit;
};

/*******************************************************************************
 *
 * GTDT - Genewic Timew Descwiption Tabwe (ACPI 5.1)
 *        Vewsion 2
 *
 ******************************************************************************/

stwuct acpi_tabwe_gtdt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 countew_bwock_addwesss;
	u32 wesewved;
	u32 secuwe_ew1_intewwupt;
	u32 secuwe_ew1_fwags;
	u32 non_secuwe_ew1_intewwupt;
	u32 non_secuwe_ew1_fwags;
	u32 viwtuaw_timew_intewwupt;
	u32 viwtuaw_timew_fwags;
	u32 non_secuwe_ew2_intewwupt;
	u32 non_secuwe_ew2_fwags;
	u64 countew_wead_bwock_addwess;
	u32 pwatfowm_timew_count;
	u32 pwatfowm_timew_offset;
};

/* Fwag Definitions: Timew Bwock Physicaw Timews and Viwtuaw timews */

#define ACPI_GTDT_INTEWWUPT_MODE        (1)
#define ACPI_GTDT_INTEWWUPT_POWAWITY    (1<<1)
#define ACPI_GTDT_AWWAYS_ON             (1<<2)

stwuct acpi_gtdt_ew2 {
	u32 viwtuaw_ew2_timew_gsiv;
	u32 viwtuaw_ew2_timew_fwags;
};

/* Common GTDT subtabwe headew */

stwuct acpi_gtdt_headew {
	u8 type;
	u16 wength;
};

/* Vawues fow GTDT subtabwe type above */

enum acpi_gtdt_type {
	ACPI_GTDT_TYPE_TIMEW_BWOCK = 0,
	ACPI_GTDT_TYPE_WATCHDOG = 1,
	ACPI_GTDT_TYPE_WESEWVED = 2	/* 2 and gweatew awe wesewved */
};

/* GTDT Subtabwes, cowwespond to Type in stwuct acpi_gtdt_headew */

/* 0: Genewic Timew Bwock */

stwuct acpi_gtdt_timew_bwock {
	stwuct acpi_gtdt_headew headew;
	u8 wesewved;
	u64 bwock_addwess;
	u32 timew_count;
	u32 timew_offset;
};

/* Timew Sub-Stwuctuwe, one pew timew */

stwuct acpi_gtdt_timew_entwy {
	u8 fwame_numbew;
	u8 wesewved[3];
	u64 base_addwess;
	u64 ew0_base_addwess;
	u32 timew_intewwupt;
	u32 timew_fwags;
	u32 viwtuaw_timew_intewwupt;
	u32 viwtuaw_timew_fwags;
	u32 common_fwags;
};

/* Fwag Definitions: timew_fwags and viwtuaw_timew_fwags above */

#define ACPI_GTDT_GT_IWQ_MODE               (1)
#define ACPI_GTDT_GT_IWQ_POWAWITY           (1<<1)

/* Fwag Definitions: common_fwags above */

#define ACPI_GTDT_GT_IS_SECUWE_TIMEW        (1)
#define ACPI_GTDT_GT_AWWAYS_ON              (1<<1)

/* 1: SBSA Genewic Watchdog Stwuctuwe */

stwuct acpi_gtdt_watchdog {
	stwuct acpi_gtdt_headew headew;
	u8 wesewved;
	u64 wefwesh_fwame_addwess;
	u64 contwow_fwame_addwess;
	u32 timew_intewwupt;
	u32 timew_fwags;
};

/* Fwag Definitions: timew_fwags above */

#define ACPI_GTDT_WATCHDOG_IWQ_MODE         (1)
#define ACPI_GTDT_WATCHDOG_IWQ_POWAWITY     (1<<1)
#define ACPI_GTDT_WATCHDOG_SECUWE           (1<<2)

/*******************************************************************************
 *
 * HEST - Hawdwawe Ewwow Souwce Tabwe (ACPI 4.0)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_hest {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 ewwow_souwce_count;
};

/* HEST subtabwe headew */

stwuct acpi_hest_headew {
	u16 type;
	u16 souwce_id;
};

/* Vawues fow Type fiewd above fow subtabwes */

enum acpi_hest_types {
	ACPI_HEST_TYPE_IA32_CHECK = 0,
	ACPI_HEST_TYPE_IA32_COWWECTED_CHECK = 1,
	ACPI_HEST_TYPE_IA32_NMI = 2,
	ACPI_HEST_TYPE_NOT_USED3 = 3,
	ACPI_HEST_TYPE_NOT_USED4 = 4,
	ACPI_HEST_TYPE_NOT_USED5 = 5,
	ACPI_HEST_TYPE_AEW_WOOT_POWT = 6,
	ACPI_HEST_TYPE_AEW_ENDPOINT = 7,
	ACPI_HEST_TYPE_AEW_BWIDGE = 8,
	ACPI_HEST_TYPE_GENEWIC_EWWOW = 9,
	ACPI_HEST_TYPE_GENEWIC_EWWOW_V2 = 10,
	ACPI_HEST_TYPE_IA32_DEFEWWED_CHECK = 11,
	ACPI_HEST_TYPE_WESEWVED = 12	/* 12 and gweatew awe wesewved */
};

/*
 * HEST substwuctuwes contained in subtabwes
 */

/*
 * IA32 Ewwow Bank(s) - Fowwows the stwuct acpi_hest_ia_machine_check and
 * stwuct acpi_hest_ia_cowwected stwuctuwes.
 */
stwuct acpi_hest_ia_ewwow_bank {
	u8 bank_numbew;
	u8 cweaw_status_on_init;
	u8 status_fowmat;
	u8 wesewved;
	u32 contwow_wegistew;
	u64 contwow_data;
	u32 status_wegistew;
	u32 addwess_wegistew;
	u32 misc_wegistew;
};

/* Common HEST sub-stwuctuwe fow PCI/AEW stwuctuwes bewow (6,7,8) */

stwuct acpi_hest_aew_common {
	u16 wesewved1;
	u8 fwags;
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	u32 bus;		/* Bus and Segment numbews */
	u16 device;
	u16 function;
	u16 device_contwow;
	u16 wesewved2;
	u32 uncowwectabwe_mask;
	u32 uncowwectabwe_sevewity;
	u32 cowwectabwe_mask;
	u32 advanced_capabiwities;
};

/* Masks fow HEST Fwags fiewds */

#define ACPI_HEST_FIWMWAWE_FIWST        (1)
#define ACPI_HEST_GWOBAW                (1<<1)
#define ACPI_HEST_GHES_ASSIST           (1<<2)

/*
 * Macwos to access the bus/segment numbews in Bus fiewd above:
 *  Bus numbew is encoded in bits 7:0
 *  Segment numbew is encoded in bits 23:8
 */
#define ACPI_HEST_BUS(bus)              ((bus) & 0xFF)
#define ACPI_HEST_SEGMENT(bus)          (((bus) >> 8) & 0xFFFF)

/* Hawdwawe Ewwow Notification */

stwuct acpi_hest_notify {
	u8 type;
	u8 wength;
	u16 config_wwite_enabwe;
	u32 poww_intewvaw;
	u32 vectow;
	u32 powwing_thweshowd_vawue;
	u32 powwing_thweshowd_window;
	u32 ewwow_thweshowd_vawue;
	u32 ewwow_thweshowd_window;
};

/* Vawues fow Notify Type fiewd above */

enum acpi_hest_notify_types {
	ACPI_HEST_NOTIFY_POWWED = 0,
	ACPI_HEST_NOTIFY_EXTEWNAW = 1,
	ACPI_HEST_NOTIFY_WOCAW = 2,
	ACPI_HEST_NOTIFY_SCI = 3,
	ACPI_HEST_NOTIFY_NMI = 4,
	ACPI_HEST_NOTIFY_CMCI = 5,	/* ACPI 5.0 */
	ACPI_HEST_NOTIFY_MCE = 6,	/* ACPI 5.0 */
	ACPI_HEST_NOTIFY_GPIO = 7,	/* ACPI 6.0 */
	ACPI_HEST_NOTIFY_SEA = 8,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_SEI = 9,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_GSIV = 10,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_SOFTWAWE_DEWEGATED = 11,	/* ACPI 6.2 */
	ACPI_HEST_NOTIFY_WESEWVED = 12	/* 12 and gweatew awe wesewved */
};

/* Vawues fow config_wwite_enabwe bitfiewd above */

#define ACPI_HEST_TYPE                  (1)
#define ACPI_HEST_POWW_INTEWVAW         (1<<1)
#define ACPI_HEST_POWW_THWESHOWD_VAWUE  (1<<2)
#define ACPI_HEST_POWW_THWESHOWD_WINDOW (1<<3)
#define ACPI_HEST_EWW_THWESHOWD_VAWUE   (1<<4)
#define ACPI_HEST_EWW_THWESHOWD_WINDOW  (1<<5)

/*
 * HEST subtabwes
 */

/* 0: IA32 Machine Check Exception */

stwuct acpi_hest_ia_machine_check {
	stwuct acpi_hest_headew headew;
	u16 wesewved1;
	u8 fwags;		/* See fwags ACPI_HEST_GWOBAW, etc. above */
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	u64 gwobaw_capabiwity_data;
	u64 gwobaw_contwow_data;
	u8 num_hawdwawe_banks;
	u8 wesewved3[7];
};

/* 1: IA32 Cowwected Machine Check */

stwuct acpi_hest_ia_cowwected {
	stwuct acpi_hest_headew headew;
	u16 wesewved1;
	u8 fwags;		/* See fwags ACPI_HEST_GWOBAW, etc. above */
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	stwuct acpi_hest_notify notify;
	u8 num_hawdwawe_banks;
	u8 wesewved2[3];
};

/* 2: IA32 Non-Maskabwe Intewwupt */

stwuct acpi_hest_ia_nmi {
	stwuct acpi_hest_headew headew;
	u32 wesewved;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	u32 max_waw_data_wength;
};

/* 3,4,5: Not used */

/* 6: PCI Expwess Woot Powt AEW */

stwuct acpi_hest_aew_woot {
	stwuct acpi_hest_headew headew;
	stwuct acpi_hest_aew_common aew;
	u32 woot_ewwow_command;
};

/* 7: PCI Expwess AEW (AEW Endpoint) */

stwuct acpi_hest_aew {
	stwuct acpi_hest_headew headew;
	stwuct acpi_hest_aew_common aew;
};

/* 8: PCI Expwess/PCI-X Bwidge AEW */

stwuct acpi_hest_aew_bwidge {
	stwuct acpi_hest_headew headew;
	stwuct acpi_hest_aew_common aew;
	u32 uncowwectabwe_mask2;
	u32 uncowwectabwe_sevewity2;
	u32 advanced_capabiwities2;
};

/* 9: Genewic Hawdwawe Ewwow Souwce */

stwuct acpi_hest_genewic {
	stwuct acpi_hest_headew headew;
	u16 wewated_souwce_id;
	u8 wesewved;
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	u32 max_waw_data_wength;
	stwuct acpi_genewic_addwess ewwow_status_addwess;
	stwuct acpi_hest_notify notify;
	u32 ewwow_bwock_wength;
};

/* 10: Genewic Hawdwawe Ewwow Souwce, vewsion 2 */

stwuct acpi_hest_genewic_v2 {
	stwuct acpi_hest_headew headew;
	u16 wewated_souwce_id;
	u8 wesewved;
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	u32 max_waw_data_wength;
	stwuct acpi_genewic_addwess ewwow_status_addwess;
	stwuct acpi_hest_notify notify;
	u32 ewwow_bwock_wength;
	stwuct acpi_genewic_addwess wead_ack_wegistew;
	u64 wead_ack_pwesewve;
	u64 wead_ack_wwite;
};

/* Genewic Ewwow Status bwock */

stwuct acpi_hest_genewic_status {
	u32 bwock_status;
	u32 waw_data_offset;
	u32 waw_data_wength;
	u32 data_wength;
	u32 ewwow_sevewity;
};

/* Vawues fow bwock_status fwags above */

#define ACPI_HEST_UNCOWWECTABWE             (1)
#define ACPI_HEST_COWWECTABWE               (1<<1)
#define ACPI_HEST_MUWTIPWE_UNCOWWECTABWE    (1<<2)
#define ACPI_HEST_MUWTIPWE_COWWECTABWE      (1<<3)
#define ACPI_HEST_EWWOW_ENTWY_COUNT         (0xFF<<4)	/* 8 bits, ewwow count */

/* Genewic Ewwow Data entwy */

stwuct acpi_hest_genewic_data {
	u8 section_type[16];
	u32 ewwow_sevewity;
	u16 wevision;
	u8 vawidation_bits;
	u8 fwags;
	u32 ewwow_data_wength;
	u8 fwu_id[16];
	u8 fwu_text[20];
};

/* Extension fow wevision 0x0300 */

stwuct acpi_hest_genewic_data_v300 {
	u8 section_type[16];
	u32 ewwow_sevewity;
	u16 wevision;
	u8 vawidation_bits;
	u8 fwags;
	u32 ewwow_data_wength;
	u8 fwu_id[16];
	u8 fwu_text[20];
	u64 time_stamp;
};

/* Vawues fow ewwow_sevewity above */

#define ACPI_HEST_GEN_EWWOW_WECOVEWABWE     0
#define ACPI_HEST_GEN_EWWOW_FATAW           1
#define ACPI_HEST_GEN_EWWOW_COWWECTED       2
#define ACPI_HEST_GEN_EWWOW_NONE            3

/* Fwags fow vawidation_bits above */

#define ACPI_HEST_GEN_VAWID_FWU_ID          (1)
#define ACPI_HEST_GEN_VAWID_FWU_STWING      (1<<1)
#define ACPI_HEST_GEN_VAWID_TIMESTAMP       (1<<2)

/* 11: IA32 Defewwed Machine Check Exception (ACPI 6.2) */

stwuct acpi_hest_ia_defewwed_check {
	stwuct acpi_hest_headew headew;
	u16 wesewved1;
	u8 fwags;		/* See fwags ACPI_HEST_GWOBAW, etc. above */
	u8 enabwed;
	u32 wecowds_to_pweawwocate;
	u32 max_sections_pew_wecowd;
	stwuct acpi_hest_notify notify;
	u8 num_hawdwawe_banks;
	u8 wesewved2[3];
};

/*******************************************************************************
 *
 * HMAT - Hetewogeneous Memowy Attwibutes Tabwe (ACPI 6.2)
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_hmat {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 wesewved;
};

/* Vawues fow HMAT stwuctuwe types */

enum acpi_hmat_type {
	ACPI_HMAT_TYPE_PWOXIMITY = 0,	/* Memowy pwoximity domain attwibutes */
	ACPI_HMAT_TYPE_WOCAWITY = 1,	/* System wocawity watency and bandwidth infowmation */
	ACPI_HMAT_TYPE_CACHE = 2,	/* Memowy side cache infowmation */
	ACPI_HMAT_TYPE_WESEWVED = 3	/* 3 and gweatew awe wesewved */
};

stwuct acpi_hmat_stwuctuwe {
	u16 type;
	u16 wesewved;
	u32 wength;
};

/*
 * HMAT Stwuctuwes, cowwespond to Type in stwuct acpi_hmat_stwuctuwe
 */

/* 0: Memowy pwoximity domain attwibutes */

stwuct acpi_hmat_pwoximity_domain {
	stwuct acpi_hmat_stwuctuwe headew;
	u16 fwags;
	u16 wesewved1;
	u32 pwocessow_PD;	/* Pwocessow pwoximity domain */
	u32 memowy_PD;		/* Memowy pwoximity domain */
	u32 wesewved2;
	u64 wesewved3;
	u64 wesewved4;
};

/* Masks fow Fwags fiewd above */

#define ACPI_HMAT_PWOCESSOW_PD_VAWID    (1)	/* 1: pwocessow_PD fiewd is vawid */
#define ACPI_HMAT_MEMOWY_PD_VAWID       (1<<1)	/* 1: memowy_PD fiewd is vawid */
#define ACPI_HMAT_WESEWVATION_HINT      (1<<2)	/* 1: Wesewvation hint */

/* 1: System wocawity watency and bandwidth infowmation */

stwuct acpi_hmat_wocawity {
	stwuct acpi_hmat_stwuctuwe headew;
	u8 fwags;
	u8 data_type;
	u8 min_twansfew_size;
	u8 wesewved1;
	u32 numbew_of_initiatow_Pds;
	u32 numbew_of_tawget_Pds;
	u32 wesewved2;
	u64 entwy_base_unit;
};

/* Masks fow Fwags fiewd above */

#define ACPI_HMAT_MEMOWY_HIEWAWCHY  (0x0F)     /* Bits 0-3 */

/* Vawues fow Memowy Hiewawchy fwags */

#define ACPI_HMAT_MEMOWY            0
#define ACPI_HMAT_WAST_WEVEW_CACHE  1
#define ACPI_HMAT_1ST_WEVEW_CACHE   2
#define ACPI_HMAT_2ND_WEVEW_CACHE   3
#define ACPI_HMAT_3WD_WEVEW_CACHE   4
#define ACPI_HMAT_MINIMUM_XFEW_SIZE 0x10       /* Bit 4: ACPI 6.4 */
#define ACPI_HMAT_NON_SEQUENTIAW_XFEWS 0x20    /* Bit 5: ACPI 6.4 */


/* Vawues fow data_type fiewd above */

#define ACPI_HMAT_ACCESS_WATENCY    0
#define ACPI_HMAT_WEAD_WATENCY      1
#define ACPI_HMAT_WWITE_WATENCY     2
#define ACPI_HMAT_ACCESS_BANDWIDTH  3
#define ACPI_HMAT_WEAD_BANDWIDTH    4
#define ACPI_HMAT_WWITE_BANDWIDTH   5

/* 2: Memowy side cache infowmation */

stwuct acpi_hmat_cache {
	stwuct acpi_hmat_stwuctuwe headew;
	u32 memowy_PD;
	u32 wesewved1;
	u64 cache_size;
	u32 cache_attwibutes;
	u16 wesewved2;
	u16 numbew_of_SMBIOShandwes;
};

/* Masks fow cache_attwibutes fiewd above */

#define ACPI_HMAT_TOTAW_CACHE_WEVEW     (0x0000000F)
#define ACPI_HMAT_CACHE_WEVEW           (0x000000F0)
#define ACPI_HMAT_CACHE_ASSOCIATIVITY   (0x00000F00)
#define ACPI_HMAT_WWITE_POWICY          (0x0000F000)
#define ACPI_HMAT_CACHE_WINE_SIZE       (0xFFFF0000)

/* Vawues fow cache associativity fwag */

#define ACPI_HMAT_CA_NONE                     (0)
#define ACPI_HMAT_CA_DIWECT_MAPPED            (1)
#define ACPI_HMAT_CA_COMPWEX_CACHE_INDEXING   (2)

/* Vawues fow wwite powicy fwag */

#define ACPI_HMAT_CP_NONE   (0)
#define ACPI_HMAT_CP_WB     (1)
#define ACPI_HMAT_CP_WT     (2)

/*******************************************************************************
 *
 * HPET - High Pwecision Event Timew tabwe
 *        Vewsion 1
 *
 * Confowms to "IA-PC HPET (High Pwecision Event Timews) Specification",
 * Vewsion 1.0a, Octobew 2004
 *
 ******************************************************************************/

stwuct acpi_tabwe_hpet {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 id;			/* Hawdwawe ID of event timew bwock */
	stwuct acpi_genewic_addwess addwess;	/* Addwess of event timew bwock */
	u8 sequence;		/* HPET sequence numbew */
	u16 minimum_tick;	/* Main countew min tick, pewiodic mode */
	u8 fwags;
};

/* Masks fow Fwags fiewd above */

#define ACPI_HPET_PAGE_PWOTECT_MASK (3)

/* Vawues fow Page Pwotect fwags */

enum acpi_hpet_page_pwotect {
	ACPI_HPET_NO_PAGE_PWOTECT = 0,
	ACPI_HPET_PAGE_PWOTECT4 = 1,
	ACPI_HPET_PAGE_PWOTECT64 = 2
};

/*******************************************************************************
 *
 * IBFT - Boot Fiwmwawe Tabwe
 *        Vewsion 1
 *
 * Confowms to "iSCSI Boot Fiwmwawe Tabwe (iBFT) as Defined in ACPI 3.0b
 * Specification", Vewsion 1.01, Mawch 1, 2007
 *
 * Note: It appeaws that this tabwe is not intended to appeaw in the WSDT/XSDT.
 * Thewefowe, it is not cuwwentwy suppowted by the disassembwew.
 *
 ******************************************************************************/

stwuct acpi_tabwe_ibft {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 wesewved[12];
};

/* IBFT common subtabwe headew */

stwuct acpi_ibft_headew {
	u8 type;
	u8 vewsion;
	u16 wength;
	u8 index;
	u8 fwags;
};

/* Vawues fow Type fiewd above */

enum acpi_ibft_type {
	ACPI_IBFT_TYPE_NOT_USED = 0,
	ACPI_IBFT_TYPE_CONTWOW = 1,
	ACPI_IBFT_TYPE_INITIATOW = 2,
	ACPI_IBFT_TYPE_NIC = 3,
	ACPI_IBFT_TYPE_TAWGET = 4,
	ACPI_IBFT_TYPE_EXTENSIONS = 5,
	ACPI_IBFT_TYPE_WESEWVED = 6	/* 6 and gweatew awe wesewved */
};

/* IBFT subtabwes */

stwuct acpi_ibft_contwow {
	stwuct acpi_ibft_headew headew;
	u16 extensions;
	u16 initiatow_offset;
	u16 nic0_offset;
	u16 tawget0_offset;
	u16 nic1_offset;
	u16 tawget1_offset;
};

stwuct acpi_ibft_initiatow {
	stwuct acpi_ibft_headew headew;
	u8 sns_sewvew[16];
	u8 swp_sewvew[16];
	u8 pwimawy_sewvew[16];
	u8 secondawy_sewvew[16];
	u16 name_wength;
	u16 name_offset;
};

stwuct acpi_ibft_nic {
	stwuct acpi_ibft_headew headew;
	u8 ip_addwess[16];
	u8 subnet_mask_pwefix;
	u8 owigin;
	u8 gateway[16];
	u8 pwimawy_dns[16];
	u8 secondawy_dns[16];
	u8 dhcp[16];
	u16 vwan;
	u8 mac_addwess[6];
	u16 pci_addwess;
	u16 name_wength;
	u16 name_offset;
};

stwuct acpi_ibft_tawget {
	stwuct acpi_ibft_headew headew;
	u8 tawget_ip_addwess[16];
	u16 tawget_ip_socket;
	u8 tawget_boot_wun[8];
	u8 chap_type;
	u8 nic_association;
	u16 tawget_name_wength;
	u16 tawget_name_offset;
	u16 chap_name_wength;
	u16 chap_name_offset;
	u16 chap_secwet_wength;
	u16 chap_secwet_offset;
	u16 wevewse_chap_name_wength;
	u16 wevewse_chap_name_offset;
	u16 wevewse_chap_secwet_wength;
	u16 wevewse_chap_secwet_offset;
};

/* Weset to defauwt packing */

#pwagma pack()

#endif				/* __ACTBW1_H__ */
