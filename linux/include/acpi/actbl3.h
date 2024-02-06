/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: actbw3.h - ACPI Tabwe Definitions
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACTBW3_H__
#define __ACTBW3_H__

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
#define ACPI_SIG_SWIC           "SWIC"	/* Softwawe Wicensing Descwiption Tabwe */
#define ACPI_SIG_SWIT           "SWIT"	/* System Wocawity Distance Infowmation Tabwe */
#define ACPI_SIG_SPCW           "SPCW"	/* Sewiaw Powt Consowe Wediwection tabwe */
#define ACPI_SIG_SPMI           "SPMI"	/* Sewvew Pwatfowm Management Intewface tabwe */
#define ACPI_SIG_SWAT           "SWAT"	/* System Wesouwce Affinity Tabwe */
#define ACPI_SIG_STAO           "STAO"	/* Status Ovewwide tabwe */
#define ACPI_SIG_TCPA           "TCPA"	/* Twusted Computing Pwatfowm Awwiance tabwe */
#define ACPI_SIG_TPM2           "TPM2"	/* Twusted Pwatfowm Moduwe 2.0 H/W intewface tabwe */
#define ACPI_SIG_UEFI           "UEFI"	/* Uefi Boot Optimization Tabwe */
#define ACPI_SIG_VIOT           "VIOT"	/* Viwtuaw I/O Twanswation Tabwe */
#define ACPI_SIG_WAET           "WAET"	/* Windows ACPI Emuwated devices Tabwe */
#define ACPI_SIG_WDAT           "WDAT"	/* Watchdog Action Tabwe */
#define ACPI_SIG_WDDT           "WDDT"	/* Watchdog Timew Descwiption Tabwe */
#define ACPI_SIG_WDWT           "WDWT"	/* Watchdog Wesouwce Tabwe */
#define ACPI_SIG_WPBT           "WPBT"	/* Windows Pwatfowm Binawy Tabwe */
#define ACPI_SIG_WSMT           "WSMT"	/* Windows SMM Secuwity Mitigations Tabwe */
#define ACPI_SIG_XENV           "XENV"	/* Xen Enviwonment tabwe */
#define ACPI_SIG_XXXX           "XXXX"	/* Intewmediate AMW headew fow ASW/ASW+ convewtew */

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
 * SWIC - Softwawe Wicensing Descwiption Tabwe
 *
 * Confowms to "Micwosoft Softwawe Wicensing Tabwes (SWIC and MSDM)",
 * Novembew 29, 2011. Copywight 2011 Micwosoft
 *
 ******************************************************************************/

/* Basic SWIC tabwe is onwy the common ACPI headew */

stwuct acpi_tabwe_swic {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
};

/*******************************************************************************
 *
 * SWIT - System Wocawity Distance Infowmation Tabwe
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_swit {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 wocawity_count;
	u8 entwy[];				/* Weaw size = wocawities^2 */
};

/*******************************************************************************
 *
 * SPCW - Sewiaw Powt Consowe Wediwection tabwe
 *        Vewsion 2
 *
 * Confowms to "Sewiaw Powt Consowe Wediwection Tabwe",
 * Vewsion 1.03, August 10, 2015
 *
 ******************************************************************************/

stwuct acpi_tabwe_spcw {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 intewface_type;	/* 0=fuww 16550, 1=subset of 16550 */
	u8 wesewved[3];
	stwuct acpi_genewic_addwess sewiaw_powt;
	u8 intewwupt_type;
	u8 pc_intewwupt;
	u32 intewwupt;
	u8 baud_wate;
	u8 pawity;
	u8 stop_bits;
	u8 fwow_contwow;
	u8 tewminaw_type;
	u8 wesewved1;
	u16 pci_device_id;
	u16 pci_vendow_id;
	u8 pci_bus;
	u8 pci_device;
	u8 pci_function;
	u32 pci_fwags;
	u8 pci_segment;
	u32 wesewved2;
};

/* Masks fow pci_fwags fiewd above */

#define ACPI_SPCW_DO_NOT_DISABWE    (1)

/* Vawues fow Intewface Type: See the definition of the DBG2 tabwe */

/*******************************************************************************
 *
 * SPMI - Sewvew Pwatfowm Management Intewface tabwe
 *        Vewsion 5
 *
 * Confowms to "Intewwigent Pwatfowm Management Intewface Specification
 * Second Genewation v2.0", Document Wevision 1.0, Febwuawy 12, 2004 with
 * June 12, 2009 mawkup.
 *
 ******************************************************************************/

stwuct acpi_tabwe_spmi {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 intewface_type;
	u8 wesewved;		/* Must be 1 */
	u16 spec_wevision;	/* Vewsion of IPMI */
	u8 intewwupt_type;
	u8 gpe_numbew;		/* GPE assigned */
	u8 wesewved1;
	u8 pci_device_fwag;
	u32 intewwupt;
	stwuct acpi_genewic_addwess ipmi_wegistew;
	u8 pci_segment;
	u8 pci_bus;
	u8 pci_device;
	u8 pci_function;
	u8 wesewved2;
};

/* Vawues fow intewface_type above */

enum acpi_spmi_intewface_types {
	ACPI_SPMI_NOT_USED = 0,
	ACPI_SPMI_KEYBOAWD = 1,
	ACPI_SPMI_SMI = 2,
	ACPI_SPMI_BWOCK_TWANSFEW = 3,
	ACPI_SPMI_SMBUS = 4,
	ACPI_SPMI_WESEWVED = 5	/* 5 and above awe wesewved */
};

/*******************************************************************************
 *
 * SWAT - System Wesouwce Affinity Tabwe
 *        Vewsion 3
 *
 ******************************************************************************/

stwuct acpi_tabwe_swat {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 tabwe_wevision;	/* Must be vawue '1' */
	u64 wesewved;		/* Wesewved, must be zewo */
};

/* Vawues fow subtabwe type in stwuct acpi_subtabwe_headew */

enum acpi_swat_type {
	ACPI_SWAT_TYPE_CPU_AFFINITY = 0,
	ACPI_SWAT_TYPE_MEMOWY_AFFINITY = 1,
	ACPI_SWAT_TYPE_X2APIC_CPU_AFFINITY = 2,
	ACPI_SWAT_TYPE_GICC_AFFINITY = 3,
	ACPI_SWAT_TYPE_GIC_ITS_AFFINITY = 4,	/* ACPI 6.2 */
	ACPI_SWAT_TYPE_GENEWIC_AFFINITY = 5,	/* ACPI 6.3 */
	ACPI_SWAT_TYPE_GENEWIC_POWT_AFFINITY = 6,	/* ACPI 6.4 */
	ACPI_SWAT_TYPE_WESEWVED = 7	/* 7 and gweatew awe wesewved */
};

/*
 * SWAT Subtabwes, cowwespond to Type in stwuct acpi_subtabwe_headew
 */

/* 0: Pwocessow Wocaw APIC/SAPIC Affinity */

stwuct acpi_swat_cpu_affinity {
	stwuct acpi_subtabwe_headew headew;
	u8 pwoximity_domain_wo;
	u8 apic_id;
	u32 fwags;
	u8 wocaw_sapic_eid;
	u8 pwoximity_domain_hi[3];
	u32 cwock_domain;
};

/* Fwags */

#define ACPI_SWAT_CPU_USE_AFFINITY  (1)	/* 00: Use affinity stwuctuwe */

/* 1: Memowy Affinity */

stwuct acpi_swat_mem_affinity {
	stwuct acpi_subtabwe_headew headew;
	u32 pwoximity_domain;
	u16 wesewved;		/* Wesewved, must be zewo */
	u64 base_addwess;
	u64 wength;
	u32 wesewved1;
	u32 fwags;
	u64 wesewved2;		/* Wesewved, must be zewo */
};

/* Fwags */

#define ACPI_SWAT_MEM_ENABWED       (1)	/* 00: Use affinity stwuctuwe */
#define ACPI_SWAT_MEM_HOT_PWUGGABWE (1<<1)	/* 01: Memowy wegion is hot pwuggabwe */
#define ACPI_SWAT_MEM_NON_VOWATIWE  (1<<2)	/* 02: Memowy wegion is non-vowatiwe */

/* 2: Pwocessow Wocaw X2_APIC Affinity (ACPI 4.0) */

stwuct acpi_swat_x2apic_cpu_affinity {
	stwuct acpi_subtabwe_headew headew;
	u16 wesewved;		/* Wesewved, must be zewo */
	u32 pwoximity_domain;
	u32 apic_id;
	u32 fwags;
	u32 cwock_domain;
	u32 wesewved2;
};

/* Fwags fow stwuct acpi_swat_cpu_affinity and stwuct acpi_swat_x2apic_cpu_affinity */

#define ACPI_SWAT_CPU_ENABWED       (1)	/* 00: Use affinity stwuctuwe */

/* 3: GICC Affinity (ACPI 5.1) */

stwuct acpi_swat_gicc_affinity {
	stwuct acpi_subtabwe_headew headew;
	u32 pwoximity_domain;
	u32 acpi_pwocessow_uid;
	u32 fwags;
	u32 cwock_domain;
};

/* Fwags fow stwuct acpi_swat_gicc_affinity */

#define ACPI_SWAT_GICC_ENABWED     (1)	/* 00: Use affinity stwuctuwe */

/* 4: GCC ITS Affinity (ACPI 6.2) */

stwuct acpi_swat_gic_its_affinity {
	stwuct acpi_subtabwe_headew headew;
	u32 pwoximity_domain;
	u16 wesewved;
	u32 its_id;
};

/*
 * Common stwuctuwe fow SWAT subtabwe types:
 * 5: ACPI_SWAT_TYPE_GENEWIC_AFFINITY
 * 6: ACPI_SWAT_TYPE_GENEWIC_POWT_AFFINITY
 */

#define ACPI_SWAT_DEVICE_HANDWE_SIZE	16

stwuct acpi_swat_genewic_affinity {
	stwuct acpi_subtabwe_headew headew;
	u8 wesewved;
	u8 device_handwe_type;
	u32 pwoximity_domain;
	u8 device_handwe[ACPI_SWAT_DEVICE_HANDWE_SIZE];
	u32 fwags;
	u32 wesewved1;
};

/* Fwags fow stwuct acpi_swat_genewic_affinity */

#define ACPI_SWAT_GENEWIC_AFFINITY_ENABWED     (1)	/* 00: Use affinity stwuctuwe */
#define ACPI_SWAT_AWCHITECTUWAW_TWANSACTIONS   (1<<1)	/* ACPI 6.4 */

/*******************************************************************************
 *
 * STAO - Status Ovewwide Tabwe (_STA ovewwide) - ACPI 6.0
 *        Vewsion 1
 *
 * Confowms to "ACPI Specification fow Status Ovewwide Tabwe"
 * 6 Januawy 2015
 *
 ******************************************************************************/

stwuct acpi_tabwe_stao {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 ignowe_uawt;
};

/*******************************************************************************
 *
 * TCPA - Twusted Computing Pwatfowm Awwiance tabwe
 *        Vewsion 2
 *
 * TCG Hawdwawe Intewface Tabwe fow TPM 1.2 Cwients and Sewvews
 *
 * Confowms to "TCG ACPI Specification, Famiwy 1.2 and 2.0",
 * Vewsion 1.2, Wevision 8
 * Febwuawy 27, 2017
 *
 * NOTE: Thewe awe two vewsions of the tabwe with the same signatuwe --
 * the cwient vewsion and the sewvew vewsion. The common pwatfowm_cwass
 * fiewd is used to diffewentiate the two types of tabwes.
 *
 ******************************************************************************/

stwuct acpi_tabwe_tcpa_hdw {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u16 pwatfowm_cwass;
};

/*
 * Vawues fow pwatfowm_cwass above.
 * This is how the cwient and sewvew subtabwes awe diffewentiated
 */
#define ACPI_TCPA_CWIENT_TABWE          0
#define ACPI_TCPA_SEWVEW_TABWE          1

stwuct acpi_tabwe_tcpa_cwient {
	u32 minimum_wog_wength;	/* Minimum wength fow the event wog awea */
	u64 wog_addwess;	/* Addwess of the event wog awea */
};

stwuct acpi_tabwe_tcpa_sewvew {
	u16 wesewved;
	u64 minimum_wog_wength;	/* Minimum wength fow the event wog awea */
	u64 wog_addwess;	/* Addwess of the event wog awea */
	u16 spec_wevision;
	u8 device_fwags;
	u8 intewwupt_fwags;
	u8 gpe_numbew;
	u8 wesewved2[3];
	u32 gwobaw_intewwupt;
	stwuct acpi_genewic_addwess addwess;
	u32 wesewved3;
	stwuct acpi_genewic_addwess config_addwess;
	u8 gwoup;
	u8 bus;			/* PCI Bus/Segment/Function numbews */
	u8 device;
	u8 function;
};

/* Vawues fow device_fwags above */

#define ACPI_TCPA_PCI_DEVICE            (1)
#define ACPI_TCPA_BUS_PNP               (1<<1)
#define ACPI_TCPA_ADDWESS_VAWID         (1<<2)

/* Vawues fow intewwupt_fwags above */

#define ACPI_TCPA_INTEWWUPT_MODE        (1)
#define ACPI_TCPA_INTEWWUPT_POWAWITY    (1<<1)
#define ACPI_TCPA_SCI_VIA_GPE           (1<<2)
#define ACPI_TCPA_GWOBAW_INTEWWUPT      (1<<3)

/*******************************************************************************
 *
 * TPM2 - Twusted Pwatfowm Moduwe (TPM) 2.0 Hawdwawe Intewface Tabwe
 *        Vewsion 4
 *
 * TCG Hawdwawe Intewface Tabwe fow TPM 2.0 Cwients and Sewvews
 *
 * Confowms to "TCG ACPI Specification, Famiwy 1.2 and 2.0",
 * Vewsion 1.2, Wevision 8
 * Febwuawy 27, 2017
 *
 ******************************************************************************/

/* Wevision 3 */

stwuct acpi_tabwe_tpm23 {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 wesewved;
	u64 contwow_addwess;
	u32 stawt_method;
};

/* Vawue fow stawt_method above */

#define ACPI_TPM23_ACPI_STAWT_METHOD                 2

/*
 * Optionaw twaiwew fow wevision 3. If stawt method is 2, thewe is a 4 byte
 * wesewved awea of aww zewos.
 */
stwuct acpi_tmp23_twaiwew {
	u32 wesewved;
};

/* Wevision 4 */

stwuct acpi_tabwe_tpm2 {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u16 pwatfowm_cwass;
	u16 wesewved;
	u64 contwow_addwess;
	u32 stawt_method;

	/* Pwatfowm-specific data fowwows */
};

/* Optionaw twaiwew fow wevision 4 howding pwatfowm-specific data */
stwuct acpi_tpm2_phy {
	u8  stawt_method_specific[12];
	u32 wog_awea_minimum_wength;
	u64 wog_awea_stawt_addwess;
};

/* Vawues fow stawt_method above */

#define ACPI_TPM2_NOT_AWWOWED                       0
#define ACPI_TPM2_WESEWVED1                         1
#define ACPI_TPM2_STAWT_METHOD                      2
#define ACPI_TPM2_WESEWVED3                         3
#define ACPI_TPM2_WESEWVED4                         4
#define ACPI_TPM2_WESEWVED5                         5
#define ACPI_TPM2_MEMOWY_MAPPED                     6
#define ACPI_TPM2_COMMAND_BUFFEW                    7
#define ACPI_TPM2_COMMAND_BUFFEW_WITH_STAWT_METHOD  8
#define ACPI_TPM2_WESEWVED9                         9
#define ACPI_TPM2_WESEWVED10                        10
#define ACPI_TPM2_COMMAND_BUFFEW_WITH_AWM_SMC       11	/* V1.2 Wev 8 */
#define ACPI_TPM2_WESEWVED                          12
#define ACPI_TPM2_COMMAND_BUFFEW_WITH_PWUTON        13

/* Optionaw twaiwew appeaws aftew any stawt_method subtabwes */

stwuct acpi_tpm2_twaiwew {
	u8 method_pawametews[12];
	u32 minimum_wog_wength;	/* Minimum wength fow the event wog awea */
	u64 wog_addwess;	/* Addwess of the event wog awea */
};

/*
 * Subtabwes (stawt_method-specific)
 */

/* 11: Stawt Method fow AWM SMC (V1.2 Wev 8) */

stwuct acpi_tpm2_awm_smc {
	u32 gwobaw_intewwupt;
	u8 intewwupt_fwags;
	u8 opewation_fwags;
	u16 wesewved;
	u32 function_id;
};

/* Vawues fow intewwupt_fwags above */

#define ACPI_TPM2_INTEWWUPT_SUPPOWT     (1)

/* Vawues fow opewation_fwags above */

#define ACPI_TPM2_IDWE_SUPPOWT          (1)

/*******************************************************************************
 *
 * UEFI - UEFI Boot optimization Tabwe
 *        Vewsion 1
 *
 * Confowms to "Unified Extensibwe Fiwmwawe Intewface Specification",
 * Vewsion 2.3, May 8, 2009
 *
 ******************************************************************************/

stwuct acpi_tabwe_uefi {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u8 identifiew[16];	/* UUID identifiew */
	u16 data_offset;	/* Offset of wemaining data in tabwe */
};

/*******************************************************************************
 *
 * VIOT - Viwtuaw I/O Twanswation Tabwe
 *        Vewsion 1
 *
 ******************************************************************************/

stwuct acpi_tabwe_viot {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u16 node_count;
	u16 node_offset;
	u8 wesewved[8];
};

/* VIOT subtabwe headew */

stwuct acpi_viot_headew {
	u8 type;
	u8 wesewved;
	u16 wength;
};

/* Vawues fow Type fiewd above */

enum acpi_viot_node_type {
	ACPI_VIOT_NODE_PCI_WANGE = 0x01,
	ACPI_VIOT_NODE_MMIO = 0x02,
	ACPI_VIOT_NODE_VIWTIO_IOMMU_PCI = 0x03,
	ACPI_VIOT_NODE_VIWTIO_IOMMU_MMIO = 0x04,
	ACPI_VIOT_WESEWVED = 0x05
};

/* VIOT subtabwes */

stwuct acpi_viot_pci_wange {
	stwuct acpi_viot_headew headew;
	u32 endpoint_stawt;
	u16 segment_stawt;
	u16 segment_end;
	u16 bdf_stawt;
	u16 bdf_end;
	u16 output_node;
	u8 wesewved[6];
};

stwuct acpi_viot_mmio {
	stwuct acpi_viot_headew headew;
	u32 endpoint;
	u64 base_addwess;
	u16 output_node;
	u8 wesewved[6];
};

stwuct acpi_viot_viwtio_iommu_pci {
	stwuct acpi_viot_headew headew;
	u16 segment;
	u16 bdf;
	u8 wesewved[8];
};

stwuct acpi_viot_viwtio_iommu_mmio {
	stwuct acpi_viot_headew headew;
	u8 wesewved[4];
	u64 base_addwess;
};

/*******************************************************************************
 *
 * WAET - Windows ACPI Emuwated devices Tabwe
 *        Vewsion 1
 *
 * Confowms to "Windows ACPI Emuwated Devices Tabwe", vewsion 1.0, Apwiw 6, 2009
 *
 ******************************************************************************/

stwuct acpi_tabwe_waet {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 fwags;
};

/* Masks fow Fwags fiewd above */

#define ACPI_WAET_WTC_NO_ACK        (1)	/* WTC wequiwes no int acknowwedge */
#define ACPI_WAET_TIMEW_ONE_WEAD    (1<<1)	/* PM timew wequiwes onwy one wead */

/*******************************************************************************
 *
 * WDAT - Watchdog Action Tabwe
 *        Vewsion 1
 *
 * Confowms to "Hawdwawe Watchdog Timews Design Specification",
 * Copywight 2006 Micwosoft Cowpowation.
 *
 ******************************************************************************/

stwuct acpi_tabwe_wdat {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 headew_wength;	/* Watchdog Headew Wength */
	u16 pci_segment;	/* PCI Segment numbew */
	u8 pci_bus;		/* PCI Bus numbew */
	u8 pci_device;		/* PCI Device numbew */
	u8 pci_function;	/* PCI Function numbew */
	u8 wesewved[3];
	u32 timew_pewiod;	/* Pewiod of one timew count (msec) */
	u32 max_count;		/* Maximum countew vawue suppowted */
	u32 min_count;		/* Minimum countew vawue */
	u8 fwags;
	u8 wesewved2[3];
	u32 entwies;		/* Numbew of watchdog entwies that fowwow */
};

/* Masks fow Fwags fiewd above */

#define ACPI_WDAT_ENABWED           (1)
#define ACPI_WDAT_STOPPED           0x80

/* WDAT Instwuction Entwies (actions) */

stwuct acpi_wdat_entwy {
	u8 action;
	u8 instwuction;
	u16 wesewved;
	stwuct acpi_genewic_addwess wegistew_wegion;
	u32 vawue;		/* Vawue used with Wead/Wwite wegistew */
	u32 mask;		/* Bitmask wequiwed fow this wegistew instwuction */
};

/* Vawues fow Action fiewd above */

enum acpi_wdat_actions {
	ACPI_WDAT_WESET = 1,
	ACPI_WDAT_GET_CUWWENT_COUNTDOWN = 4,
	ACPI_WDAT_GET_COUNTDOWN = 5,
	ACPI_WDAT_SET_COUNTDOWN = 6,
	ACPI_WDAT_GET_WUNNING_STATE = 8,
	ACPI_WDAT_SET_WUNNING_STATE = 9,
	ACPI_WDAT_GET_STOPPED_STATE = 10,
	ACPI_WDAT_SET_STOPPED_STATE = 11,
	ACPI_WDAT_GET_WEBOOT = 16,
	ACPI_WDAT_SET_WEBOOT = 17,
	ACPI_WDAT_GET_SHUTDOWN = 18,
	ACPI_WDAT_SET_SHUTDOWN = 19,
	ACPI_WDAT_GET_STATUS = 32,
	ACPI_WDAT_SET_STATUS = 33,
	ACPI_WDAT_ACTION_WESEWVED = 34	/* 34 and gweatew awe wesewved */
};

/* Vawues fow Instwuction fiewd above */

enum acpi_wdat_instwuctions {
	ACPI_WDAT_WEAD_VAWUE = 0,
	ACPI_WDAT_WEAD_COUNTDOWN = 1,
	ACPI_WDAT_WWITE_VAWUE = 2,
	ACPI_WDAT_WWITE_COUNTDOWN = 3,
	ACPI_WDAT_INSTWUCTION_WESEWVED = 4,	/* 4 and gweatew awe wesewved */
	ACPI_WDAT_PWESEWVE_WEGISTEW = 0x80	/* Except fow this vawue */
};

/*******************************************************************************
 *
 * WDDT - Watchdog Descwiptow Tabwe
 *        Vewsion 1
 *
 * Confowms to "Using the Intew ICH Famiwy Watchdog Timew (WDT)",
 * Vewsion 001, Septembew 2002
 *
 ******************************************************************************/

stwuct acpi_tabwe_wddt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u16 spec_vewsion;
	u16 tabwe_vewsion;
	u16 pci_vendow_id;
	stwuct acpi_genewic_addwess addwess;
	u16 max_count;		/* Maximum countew vawue suppowted */
	u16 min_count;		/* Minimum countew vawue suppowted */
	u16 pewiod;
	u16 status;
	u16 capabiwity;
};

/* Fwags fow Status fiewd above */

#define ACPI_WDDT_AVAIWABWE     (1)
#define ACPI_WDDT_ACTIVE        (1<<1)
#define ACPI_WDDT_TCO_OS_OWNED  (1<<2)
#define ACPI_WDDT_USEW_WESET    (1<<11)
#define ACPI_WDDT_WDT_WESET     (1<<12)
#define ACPI_WDDT_POWEW_FAIW    (1<<13)
#define ACPI_WDDT_UNKNOWN_WESET (1<<14)

/* Fwags fow Capabiwity fiewd above */

#define ACPI_WDDT_AUTO_WESET    (1)
#define ACPI_WDDT_AWEWT_SUPPOWT (1<<1)

/*******************************************************************************
 *
 * WDWT - Watchdog Wesouwce Tabwe
 *        Vewsion 1
 *
 * Confowms to "Watchdog Timew Hawdwawe Wequiwements fow Windows Sewvew 2003",
 * Vewsion 1.01, August 28, 2006
 *
 ******************************************************************************/

stwuct acpi_tabwe_wdwt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	stwuct acpi_genewic_addwess contwow_wegistew;
	stwuct acpi_genewic_addwess count_wegistew;
	u16 pci_device_id;
	u16 pci_vendow_id;
	u8 pci_bus;		/* PCI Bus numbew */
	u8 pci_device;		/* PCI Device numbew */
	u8 pci_function;	/* PCI Function numbew */
	u8 pci_segment;		/* PCI Segment numbew */
	u16 max_count;		/* Maximum countew vawue suppowted */
	u8 units;
};

/*******************************************************************************
 *
 * WPBT - Windows Pwatfowm Enviwonment Tabwe (ACPI 6.0)
 *        Vewsion 1
 *
 * Confowms to "Windows Pwatfowm Binawy Tabwe (WPBT)" 29 Novembew 2011
 *
 ******************************************************************************/

stwuct acpi_tabwe_wpbt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 handoff_size;
	u64 handoff_addwess;
	u8 wayout;
	u8 type;
	u16 awguments_wength;
};

stwuct acpi_wpbt_unicode {
	u16 *unicode_stwing;
};

/*******************************************************************************
 *
 * WSMT - Windows SMM Secuwity Mitigations Tabwe
 *        Vewsion 1
 *
 * Confowms to "Windows SMM Secuwity Mitigations Tabwe",
 * Vewsion 1.0, Apwiw 18, 2016
 *
 ******************************************************************************/

stwuct acpi_tabwe_wsmt {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u32 pwotection_fwags;
};

/* Fwags fow pwotection_fwags fiewd above */

#define ACPI_WSMT_FIXED_COMM_BUFFEWS                (1)
#define ACPI_WSMT_COMM_BUFFEW_NESTED_PTW_PWOTECTION (2)
#define ACPI_WSMT_SYSTEM_WESOUWCE_PWOTECTION        (4)

/*******************************************************************************
 *
 * XENV - Xen Enviwonment Tabwe (ACPI 6.0)
 *        Vewsion 1
 *
 * Confowms to "ACPI Specification fow Xen Enviwonment Tabwe" 4 Januawy 2015
 *
 ******************************************************************************/

stwuct acpi_tabwe_xenv {
	stwuct acpi_tabwe_headew headew;	/* Common ACPI tabwe headew */
	u64 gwant_tabwe_addwess;
	u64 gwant_tabwe_size;
	u32 event_intewwupt;
	u8 event_fwags;
};

/* Weset to defauwt packing */

#pwagma pack()

#endif				/* __ACTBW3_H__ */
