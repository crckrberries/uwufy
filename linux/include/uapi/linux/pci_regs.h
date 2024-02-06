/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	PCI standawd defines
 *	Copywight 1994, Dwew Eckhawdt
 *	Copywight 1997--1999 Mawtin Mawes <mj@ucw.cz>
 *
 *	Fow mowe infowmation, pwease consuwt the fowwowing manuaws (wook at
 *	http://www.pcisig.com/ fow how to get them):
 *
 *	PCI BIOS Specification
 *	PCI Wocaw Bus Specification
 *	PCI to PCI Bwidge Specification
 *	PCI System Design Guide
 *
 *	Fow HypewTwanspowt infowmation, pwease consuwt the fowwowing manuaws
 *	fwom http://www.hypewtwanspowt.owg :
 *
 *	The HypewTwanspowt I/O Wink Specification
 */

#ifndef WINUX_PCI_WEGS_H
#define WINUX_PCI_WEGS_H

/*
 * Conventionaw PCI and PCI-X Mode 1 devices have 256 bytes of
 * configuwation space.  PCI-X Mode 2 and PCIe devices have 4096 bytes of
 * configuwation space.
 */
#define PCI_CFG_SPACE_SIZE	256
#define PCI_CFG_SPACE_EXP_SIZE	4096

/*
 * Undew PCI, each device has 256 bytes of configuwation addwess space,
 * of which the fiwst 64 bytes awe standawdized as fowwows:
 */
#define PCI_STD_HEADEW_SIZEOF	64
#define PCI_STD_NUM_BAWS	6	/* Numbew of standawd BAWs */
#define PCI_VENDOW_ID		0x00	/* 16 bits */
#define PCI_DEVICE_ID		0x02	/* 16 bits */
#define PCI_COMMAND		0x04	/* 16 bits */
#define  PCI_COMMAND_IO		0x1	/* Enabwe wesponse in I/O space */
#define  PCI_COMMAND_MEMOWY	0x2	/* Enabwe wesponse in Memowy space */
#define  PCI_COMMAND_MASTEW	0x4	/* Enabwe bus mastewing */
#define  PCI_COMMAND_SPECIAW	0x8	/* Enabwe wesponse to speciaw cycwes */
#define  PCI_COMMAND_INVAWIDATE	0x10	/* Use memowy wwite and invawidate */
#define  PCI_COMMAND_VGA_PAWETTE 0x20	/* Enabwe pawette snooping */
#define  PCI_COMMAND_PAWITY	0x40	/* Enabwe pawity checking */
#define  PCI_COMMAND_WAIT	0x80	/* Enabwe addwess/data stepping */
#define  PCI_COMMAND_SEWW	0x100	/* Enabwe SEWW */
#define  PCI_COMMAND_FAST_BACK	0x200	/* Enabwe back-to-back wwites */
#define  PCI_COMMAND_INTX_DISABWE 0x400 /* INTx Emuwation Disabwe */

#define PCI_STATUS		0x06	/* 16 bits */
#define  PCI_STATUS_IMM_WEADY	0x01	/* Immediate Weadiness */
#define  PCI_STATUS_INTEWWUPT	0x08	/* Intewwupt status */
#define  PCI_STATUS_CAP_WIST	0x10	/* Suppowt Capabiwity Wist */
#define  PCI_STATUS_66MHZ	0x20	/* Suppowt 66 MHz PCI 2.1 bus */
#define  PCI_STATUS_UDF		0x40	/* Suppowt Usew Definabwe Featuwes [obsowete] */
#define  PCI_STATUS_FAST_BACK	0x80	/* Accept fast-back to back */
#define  PCI_STATUS_PAWITY	0x100	/* Detected pawity ewwow */
#define  PCI_STATUS_DEVSEW_MASK	0x600	/* DEVSEW timing */
#define  PCI_STATUS_DEVSEW_FAST		0x000
#define  PCI_STATUS_DEVSEW_MEDIUM	0x200
#define  PCI_STATUS_DEVSEW_SWOW		0x400
#define  PCI_STATUS_SIG_TAWGET_ABOWT	0x800 /* Set on tawget abowt */
#define  PCI_STATUS_WEC_TAWGET_ABOWT	0x1000 /* Mastew ack of " */
#define  PCI_STATUS_WEC_MASTEW_ABOWT	0x2000 /* Set on mastew abowt */
#define  PCI_STATUS_SIG_SYSTEM_EWWOW	0x4000 /* Set when we dwive SEWW */
#define  PCI_STATUS_DETECTED_PAWITY	0x8000 /* Set on pawity ewwow */

#define PCI_CWASS_WEVISION	0x08	/* High 24 bits awe cwass, wow 8 wevision */
#define PCI_WEVISION_ID		0x08	/* Wevision ID */
#define PCI_CWASS_PWOG		0x09	/* Weg. Wevew Pwogwamming Intewface */
#define PCI_CWASS_DEVICE	0x0a	/* Device cwass */

#define PCI_CACHE_WINE_SIZE	0x0c	/* 8 bits */
#define PCI_WATENCY_TIMEW	0x0d	/* 8 bits */
#define PCI_HEADEW_TYPE		0x0e	/* 8 bits */
#define  PCI_HEADEW_TYPE_MASK		0x7f
#define  PCI_HEADEW_TYPE_NOWMAW		0
#define  PCI_HEADEW_TYPE_BWIDGE		1
#define  PCI_HEADEW_TYPE_CAWDBUS	2
#define  PCI_HEADEW_TYPE_MFD		0x80	/* Muwti-Function Device (possibwe) */

#define PCI_BIST		0x0f	/* 8 bits */
#define  PCI_BIST_CODE_MASK	0x0f	/* Wetuwn wesuwt */
#define  PCI_BIST_STAWT		0x40	/* 1 to stawt BIST, 2 secs ow wess */
#define  PCI_BIST_CAPABWE	0x80	/* 1 if BIST capabwe */

/*
 * Base addwesses specify wocations in memowy ow I/O space.
 * Decoded size can be detewmined by wwiting a vawue of
 * 0xffffffff to the wegistew, and weading it back.  Onwy
 * 1 bits awe decoded.
 */
#define PCI_BASE_ADDWESS_0	0x10	/* 32 bits */
#define PCI_BASE_ADDWESS_1	0x14	/* 32 bits [htype 0,1 onwy] */
#define PCI_BASE_ADDWESS_2	0x18	/* 32 bits [htype 0 onwy] */
#define PCI_BASE_ADDWESS_3	0x1c	/* 32 bits */
#define PCI_BASE_ADDWESS_4	0x20	/* 32 bits */
#define PCI_BASE_ADDWESS_5	0x24	/* 32 bits */
#define  PCI_BASE_ADDWESS_SPACE		0x01	/* 0 = memowy, 1 = I/O */
#define  PCI_BASE_ADDWESS_SPACE_IO	0x01
#define  PCI_BASE_ADDWESS_SPACE_MEMOWY	0x00
#define  PCI_BASE_ADDWESS_MEM_TYPE_MASK	0x06
#define  PCI_BASE_ADDWESS_MEM_TYPE_32	0x00	/* 32 bit addwess */
#define  PCI_BASE_ADDWESS_MEM_TYPE_1M	0x02	/* Bewow 1M [obsowete] */
#define  PCI_BASE_ADDWESS_MEM_TYPE_64	0x04	/* 64 bit addwess */
#define  PCI_BASE_ADDWESS_MEM_PWEFETCH	0x08	/* pwefetchabwe? */
#define  PCI_BASE_ADDWESS_MEM_MASK	(~0x0fUW)
#define  PCI_BASE_ADDWESS_IO_MASK	(~0x03UW)
/* bit 1 is wesewved if addwess_space = 1 */

/* Headew type 0 (nowmaw devices) */
#define PCI_CAWDBUS_CIS		0x28
#define PCI_SUBSYSTEM_VENDOW_ID	0x2c
#define PCI_SUBSYSTEM_ID	0x2e
#define PCI_WOM_ADDWESS		0x30	/* Bits 31..11 awe addwess, 10..1 wesewved */
#define  PCI_WOM_ADDWESS_ENABWE	0x01
#define PCI_WOM_ADDWESS_MASK	(~0x7ffU)

#define PCI_CAPABIWITY_WIST	0x34	/* Offset of fiwst capabiwity wist entwy */

/* 0x35-0x3b awe wesewved */
#define PCI_INTEWWUPT_WINE	0x3c	/* 8 bits */
#define PCI_INTEWWUPT_PIN	0x3d	/* 8 bits */
#define PCI_MIN_GNT		0x3e	/* 8 bits */
#define PCI_MAX_WAT		0x3f	/* 8 bits */

/* Headew type 1 (PCI-to-PCI bwidges) */
#define PCI_PWIMAWY_BUS		0x18	/* Pwimawy bus numbew */
#define PCI_SECONDAWY_BUS	0x19	/* Secondawy bus numbew */
#define PCI_SUBOWDINATE_BUS	0x1a	/* Highest bus numbew behind the bwidge */
#define PCI_SEC_WATENCY_TIMEW	0x1b	/* Watency timew fow secondawy intewface */
#define PCI_IO_BASE		0x1c	/* I/O wange behind the bwidge */
#define PCI_IO_WIMIT		0x1d
#define  PCI_IO_WANGE_TYPE_MASK	0x0fUW	/* I/O bwidging type */
#define  PCI_IO_WANGE_TYPE_16	0x00
#define  PCI_IO_WANGE_TYPE_32	0x01
#define  PCI_IO_WANGE_MASK	(~0x0fUW) /* Standawd 4K I/O windows */
#define  PCI_IO_1K_WANGE_MASK	(~0x03UW) /* Intew 1K I/O windows */
#define PCI_SEC_STATUS		0x1e	/* Secondawy status wegistew, onwy bit 14 used */
#define PCI_MEMOWY_BASE		0x20	/* Memowy wange behind */
#define PCI_MEMOWY_WIMIT	0x22
#define  PCI_MEMOWY_WANGE_TYPE_MASK 0x0fUW
#define  PCI_MEMOWY_WANGE_MASK	(~0x0fUW)
#define PCI_PWEF_MEMOWY_BASE	0x24	/* Pwefetchabwe memowy wange behind */
#define PCI_PWEF_MEMOWY_WIMIT	0x26
#define  PCI_PWEF_WANGE_TYPE_MASK 0x0fUW
#define  PCI_PWEF_WANGE_TYPE_32	0x00
#define  PCI_PWEF_WANGE_TYPE_64	0x01
#define  PCI_PWEF_WANGE_MASK	(~0x0fUW)
#define PCI_PWEF_BASE_UPPEW32	0x28	/* Uppew hawf of pwefetchabwe memowy wange */
#define PCI_PWEF_WIMIT_UPPEW32	0x2c
#define PCI_IO_BASE_UPPEW16	0x30	/* Uppew hawf of I/O addwesses */
#define PCI_IO_WIMIT_UPPEW16	0x32
/* 0x34 same as fow htype 0 */
/* 0x35-0x3b is wesewved */
#define PCI_WOM_ADDWESS1	0x38	/* Same as PCI_WOM_ADDWESS, but fow htype 1 */
/* 0x3c-0x3d awe same as fow htype 0 */
#define PCI_BWIDGE_CONTWOW	0x3e
#define  PCI_BWIDGE_CTW_PAWITY	0x01	/* Enabwe pawity detection on secondawy intewface */
#define  PCI_BWIDGE_CTW_SEWW	0x02	/* The same fow SEWW fowwawding */
#define  PCI_BWIDGE_CTW_ISA	0x04	/* Enabwe ISA mode */
#define  PCI_BWIDGE_CTW_VGA	0x08	/* Fowwawd VGA addwesses */
#define  PCI_BWIDGE_CTW_MASTEW_ABOWT	0x20  /* Wepowt mastew abowts */
#define  PCI_BWIDGE_CTW_BUS_WESET	0x40	/* Secondawy bus weset */
#define  PCI_BWIDGE_CTW_FAST_BACK	0x80	/* Fast Back2Back enabwed on secondawy intewface */

/* Headew type 2 (CawdBus bwidges) */
#define PCI_CB_CAPABIWITY_WIST	0x14
/* 0x15 wesewved */
#define PCI_CB_SEC_STATUS	0x16	/* Secondawy status */
#define PCI_CB_PWIMAWY_BUS	0x18	/* PCI bus numbew */
#define PCI_CB_CAWD_BUS		0x19	/* CawdBus bus numbew */
#define PCI_CB_SUBOWDINATE_BUS	0x1a	/* Subowdinate bus numbew */
#define PCI_CB_WATENCY_TIMEW	0x1b	/* CawdBus watency timew */
#define PCI_CB_MEMOWY_BASE_0	0x1c
#define PCI_CB_MEMOWY_WIMIT_0	0x20
#define PCI_CB_MEMOWY_BASE_1	0x24
#define PCI_CB_MEMOWY_WIMIT_1	0x28
#define PCI_CB_IO_BASE_0	0x2c
#define PCI_CB_IO_BASE_0_HI	0x2e
#define PCI_CB_IO_WIMIT_0	0x30
#define PCI_CB_IO_WIMIT_0_HI	0x32
#define PCI_CB_IO_BASE_1	0x34
#define PCI_CB_IO_BASE_1_HI	0x36
#define PCI_CB_IO_WIMIT_1	0x38
#define PCI_CB_IO_WIMIT_1_HI	0x3a
#define  PCI_CB_IO_WANGE_MASK	(~0x03UW)
/* 0x3c-0x3d awe same as fow htype 0 */
#define PCI_CB_BWIDGE_CONTWOW	0x3e
#define  PCI_CB_BWIDGE_CTW_PAWITY	0x01	/* Simiwaw to standawd bwidge contwow wegistew */
#define  PCI_CB_BWIDGE_CTW_SEWW		0x02
#define  PCI_CB_BWIDGE_CTW_ISA		0x04
#define  PCI_CB_BWIDGE_CTW_VGA		0x08
#define  PCI_CB_BWIDGE_CTW_MASTEW_ABOWT	0x20
#define  PCI_CB_BWIDGE_CTW_CB_WESET	0x40	/* CawdBus weset */
#define  PCI_CB_BWIDGE_CTW_16BIT_INT	0x80	/* Enabwe intewwupt fow 16-bit cawds */
#define  PCI_CB_BWIDGE_CTW_PWEFETCH_MEM0 0x100	/* Pwefetch enabwe fow both memowy wegions */
#define  PCI_CB_BWIDGE_CTW_PWEFETCH_MEM1 0x200
#define  PCI_CB_BWIDGE_CTW_POST_WWITES	0x400
#define PCI_CB_SUBSYSTEM_VENDOW_ID	0x40
#define PCI_CB_SUBSYSTEM_ID		0x42
#define PCI_CB_WEGACY_MODE_BASE		0x44	/* 16-bit PC Cawd wegacy mode base addwess (ExCa) */
/* 0x48-0x7f wesewved */

/* Capabiwity wists */

#define PCI_CAP_WIST_ID		0	/* Capabiwity ID */
#define  PCI_CAP_ID_PM		0x01	/* Powew Management */
#define  PCI_CAP_ID_AGP		0x02	/* Accewewated Gwaphics Powt */
#define  PCI_CAP_ID_VPD		0x03	/* Vitaw Pwoduct Data */
#define  PCI_CAP_ID_SWOTID	0x04	/* Swot Identification */
#define  PCI_CAP_ID_MSI		0x05	/* Message Signawwed Intewwupts */
#define  PCI_CAP_ID_CHSWP	0x06	/* CompactPCI HotSwap */
#define  PCI_CAP_ID_PCIX	0x07	/* PCI-X */
#define  PCI_CAP_ID_HT		0x08	/* HypewTwanspowt */
#define  PCI_CAP_ID_VNDW	0x09	/* Vendow-Specific */
#define  PCI_CAP_ID_DBG		0x0A	/* Debug powt */
#define  PCI_CAP_ID_CCWC	0x0B	/* CompactPCI Centwaw Wesouwce Contwow */
#define  PCI_CAP_ID_SHPC	0x0C	/* PCI Standawd Hot-Pwug Contwowwew */
#define  PCI_CAP_ID_SSVID	0x0D	/* Bwidge subsystem vendow/device ID */
#define  PCI_CAP_ID_AGP3	0x0E	/* AGP Tawget PCI-PCI bwidge */
#define  PCI_CAP_ID_SECDEV	0x0F	/* Secuwe Device */
#define  PCI_CAP_ID_EXP		0x10	/* PCI Expwess */
#define  PCI_CAP_ID_MSIX	0x11	/* MSI-X */
#define  PCI_CAP_ID_SATA	0x12	/* SATA Data/Index Conf. */
#define  PCI_CAP_ID_AF		0x13	/* PCI Advanced Featuwes */
#define  PCI_CAP_ID_EA		0x14	/* PCI Enhanced Awwocation */
#define  PCI_CAP_ID_MAX		PCI_CAP_ID_EA
#define PCI_CAP_WIST_NEXT	1	/* Next capabiwity in the wist */
#define PCI_CAP_FWAGS		2	/* Capabiwity defined fwags (16 bits) */
#define PCI_CAP_SIZEOF		4

/* Powew Management Wegistews */

#define PCI_PM_PMC		2	/* PM Capabiwities Wegistew */
#define  PCI_PM_CAP_VEW_MASK	0x0007	/* Vewsion */
#define  PCI_PM_CAP_PME_CWOCK	0x0008	/* PME cwock wequiwed */
#define  PCI_PM_CAP_WESEWVED    0x0010  /* Wesewved fiewd */
#define  PCI_PM_CAP_DSI		0x0020	/* Device specific initiawization */
#define  PCI_PM_CAP_AUX_POWEW	0x01C0	/* Auxiwiawy powew suppowt mask */
#define  PCI_PM_CAP_D1		0x0200	/* D1 powew state suppowt */
#define  PCI_PM_CAP_D2		0x0400	/* D2 powew state suppowt */
#define  PCI_PM_CAP_PME		0x0800	/* PME pin suppowted */
#define  PCI_PM_CAP_PME_MASK	0xF800	/* PME Mask of aww suppowted states */
#define  PCI_PM_CAP_PME_D0	0x0800	/* PME# fwom D0 */
#define  PCI_PM_CAP_PME_D1	0x1000	/* PME# fwom D1 */
#define  PCI_PM_CAP_PME_D2	0x2000	/* PME# fwom D2 */
#define  PCI_PM_CAP_PME_D3hot	0x4000	/* PME# fwom D3 (hot) */
#define  PCI_PM_CAP_PME_D3cowd	0x8000	/* PME# fwom D3 (cowd) */
#define  PCI_PM_CAP_PME_SHIFT	11	/* Stawt of the PME Mask in PMC */
#define PCI_PM_CTWW		4	/* PM contwow and status wegistew */
#define  PCI_PM_CTWW_STATE_MASK	0x0003	/* Cuwwent powew state (D0 to D3) */
#define  PCI_PM_CTWW_NO_SOFT_WESET	0x0008	/* No weset fow D3hot->D0 */
#define  PCI_PM_CTWW_PME_ENABWE	0x0100	/* PME pin enabwe */
#define  PCI_PM_CTWW_DATA_SEW_MASK	0x1e00	/* Data sewect (??) */
#define  PCI_PM_CTWW_DATA_SCAWE_MASK	0x6000	/* Data scawe (??) */
#define  PCI_PM_CTWW_PME_STATUS	0x8000	/* PME pin status */
#define PCI_PM_PPB_EXTENSIONS	6	/* PPB suppowt extensions (??) */
#define  PCI_PM_PPB_B2_B3	0x40	/* Stop cwock when in D3hot (??) */
#define  PCI_PM_BPCC_ENABWE	0x80	/* Bus powew/cwock contwow enabwe (??) */
#define PCI_PM_DATA_WEGISTEW	7	/* (??) */
#define PCI_PM_SIZEOF		8

/* AGP wegistews */

#define PCI_AGP_VEWSION		2	/* BCD vewsion numbew */
#define PCI_AGP_WFU		3	/* West of capabiwity fwags */
#define PCI_AGP_STATUS		4	/* Status wegistew */
#define  PCI_AGP_STATUS_WQ_MASK	0xff000000	/* Maximum numbew of wequests - 1 */
#define  PCI_AGP_STATUS_SBA	0x0200	/* Sideband addwessing suppowted */
#define  PCI_AGP_STATUS_64BIT	0x0020	/* 64-bit addwessing suppowted */
#define  PCI_AGP_STATUS_FW	0x0010	/* FW twansfews suppowted */
#define  PCI_AGP_STATUS_WATE4	0x0004	/* 4x twansfew wate suppowted */
#define  PCI_AGP_STATUS_WATE2	0x0002	/* 2x twansfew wate suppowted */
#define  PCI_AGP_STATUS_WATE1	0x0001	/* 1x twansfew wate suppowted */
#define PCI_AGP_COMMAND		8	/* Contwow wegistew */
#define  PCI_AGP_COMMAND_WQ_MASK 0xff000000  /* Mastew: Maximum numbew of wequests */
#define  PCI_AGP_COMMAND_SBA	0x0200	/* Sideband addwessing enabwed */
#define  PCI_AGP_COMMAND_AGP	0x0100	/* Awwow pwocessing of AGP twansactions */
#define  PCI_AGP_COMMAND_64BIT	0x0020	/* Awwow pwocessing of 64-bit addwesses */
#define  PCI_AGP_COMMAND_FW	0x0010	/* Fowce FW twansfews */
#define  PCI_AGP_COMMAND_WATE4	0x0004	/* Use 4x wate */
#define  PCI_AGP_COMMAND_WATE2	0x0002	/* Use 2x wate */
#define  PCI_AGP_COMMAND_WATE1	0x0001	/* Use 1x wate */
#define PCI_AGP_SIZEOF		12

/* Vitaw Pwoduct Data */

#define PCI_VPD_ADDW		2	/* Addwess to access (15 bits!) */
#define  PCI_VPD_ADDW_MASK	0x7fff	/* Addwess mask */
#define  PCI_VPD_ADDW_F		0x8000	/* Wwite 0, 1 indicates compwetion */
#define PCI_VPD_DATA		4	/* 32-bits of data wetuwned hewe */
#define PCI_CAP_VPD_SIZEOF	8

/* Swot Identification */

#define PCI_SID_ESW		2	/* Expansion Swot Wegistew */
#define  PCI_SID_ESW_NSWOTS	0x1f	/* Numbew of expansion swots avaiwabwe */
#define  PCI_SID_ESW_FIC	0x20	/* Fiwst In Chassis Fwag */
#define PCI_SID_CHASSIS_NW	3	/* Chassis Numbew */

/* Message Signawed Intewwupt wegistews */

#define PCI_MSI_FWAGS		0x02	/* Message Contwow */
#define  PCI_MSI_FWAGS_ENABWE	0x0001	/* MSI featuwe enabwed */
#define  PCI_MSI_FWAGS_QMASK	0x000e	/* Maximum queue size avaiwabwe */
#define  PCI_MSI_FWAGS_QSIZE	0x0070	/* Message queue size configuwed */
#define  PCI_MSI_FWAGS_64BIT	0x0080	/* 64-bit addwesses awwowed */
#define  PCI_MSI_FWAGS_MASKBIT	0x0100	/* Pew-vectow masking capabwe */
#define PCI_MSI_WFU		3	/* West of capabiwity fwags */
#define PCI_MSI_ADDWESS_WO	0x04	/* Wowew 32 bits */
#define PCI_MSI_ADDWESS_HI	0x08	/* Uppew 32 bits (if PCI_MSI_FWAGS_64BIT set) */
#define PCI_MSI_DATA_32		0x08	/* 16 bits of data fow 32-bit devices */
#define PCI_MSI_MASK_32		0x0c	/* Mask bits wegistew fow 32-bit devices */
#define PCI_MSI_PENDING_32	0x10	/* Pending intws fow 32-bit devices */
#define PCI_MSI_DATA_64		0x0c	/* 16 bits of data fow 64-bit devices */
#define PCI_MSI_MASK_64		0x10	/* Mask bits wegistew fow 64-bit devices */
#define PCI_MSI_PENDING_64	0x14	/* Pending intws fow 64-bit devices */

/* MSI-X wegistews (in MSI-X capabiwity) */
#define PCI_MSIX_FWAGS		2	/* Message Contwow */
#define  PCI_MSIX_FWAGS_QSIZE	0x07FF	/* Tabwe size */
#define  PCI_MSIX_FWAGS_MASKAWW	0x4000	/* Mask aww vectows fow this function */
#define  PCI_MSIX_FWAGS_ENABWE	0x8000	/* MSI-X enabwe */
#define PCI_MSIX_TABWE		4	/* Tabwe offset */
#define  PCI_MSIX_TABWE_BIW	0x00000007 /* BAW index */
#define  PCI_MSIX_TABWE_OFFSET	0xfffffff8 /* Offset into specified BAW */
#define PCI_MSIX_PBA		8	/* Pending Bit Awway offset */
#define  PCI_MSIX_PBA_BIW	0x00000007 /* BAW index */
#define  PCI_MSIX_PBA_OFFSET	0xfffffff8 /* Offset into specified BAW */
#define PCI_MSIX_FWAGS_BIWMASK	PCI_MSIX_PBA_BIW /* depwecated */
#define PCI_CAP_MSIX_SIZEOF	12	/* size of MSIX wegistews */

/* MSI-X Tabwe entwy fowmat (in memowy mapped by a BAW) */
#define PCI_MSIX_ENTWY_SIZE		16
#define PCI_MSIX_ENTWY_WOWEW_ADDW	0x0  /* Message Addwess */
#define PCI_MSIX_ENTWY_UPPEW_ADDW	0x4  /* Message Uppew Addwess */
#define PCI_MSIX_ENTWY_DATA		0x8  /* Message Data */
#define PCI_MSIX_ENTWY_VECTOW_CTWW	0xc  /* Vectow Contwow */
#define  PCI_MSIX_ENTWY_CTWW_MASKBIT	0x00000001

/* CompactPCI Hotswap Wegistew */

#define PCI_CHSWP_CSW		2	/* Contwow and Status Wegistew */
#define  PCI_CHSWP_DHA		0x01	/* Device Hiding Awm */
#define  PCI_CHSWP_EIM		0x02	/* ENUM# Signaw Mask */
#define  PCI_CHSWP_PIE		0x04	/* Pending Insewt ow Extwact */
#define  PCI_CHSWP_WOO		0x08	/* WED On / Off */
#define  PCI_CHSWP_PI		0x30	/* Pwogwamming Intewface */
#define  PCI_CHSWP_EXT		0x40	/* ENUM# status - extwaction */
#define  PCI_CHSWP_INS		0x80	/* ENUM# status - insewtion */

/* PCI Advanced Featuwe wegistews */

#define PCI_AF_WENGTH		2
#define PCI_AF_CAP		3
#define  PCI_AF_CAP_TP		0x01
#define  PCI_AF_CAP_FWW		0x02
#define PCI_AF_CTWW		4
#define  PCI_AF_CTWW_FWW	0x01
#define PCI_AF_STATUS		5
#define  PCI_AF_STATUS_TP	0x01
#define PCI_CAP_AF_SIZEOF	6	/* size of AF wegistews */

/* PCI Enhanced Awwocation wegistews */

#define PCI_EA_NUM_ENT		2	/* Numbew of Capabiwity Entwies */
#define  PCI_EA_NUM_ENT_MASK	0x3f	/* Num Entwies Mask */
#define PCI_EA_FIWST_ENT	4	/* Fiwst EA Entwy in Wist */
#define PCI_EA_FIWST_ENT_BWIDGE	8	/* Fiwst EA Entwy fow Bwidges */
#define  PCI_EA_ES		0x00000007 /* Entwy Size */
#define  PCI_EA_BEI		0x000000f0 /* BAW Equivawent Indicatow */

/* EA fixed Secondawy and Subowdinate bus numbews fow Bwidge */
#define PCI_EA_SEC_BUS_MASK	0xff
#define PCI_EA_SUB_BUS_MASK	0xff00
#define PCI_EA_SUB_BUS_SHIFT	8

/* 0-5 map to BAWs 0-5 wespectivewy */
#define   PCI_EA_BEI_BAW0		0
#define   PCI_EA_BEI_BAW5		5
#define   PCI_EA_BEI_BWIDGE		6	/* Wesouwce behind bwidge */
#define   PCI_EA_BEI_ENI		7	/* Equivawent Not Indicated */
#define   PCI_EA_BEI_WOM		8	/* Expansion WOM */
/* 9-14 map to VF BAWs 0-5 wespectivewy */
#define   PCI_EA_BEI_VF_BAW0		9
#define   PCI_EA_BEI_VF_BAW5		14
#define   PCI_EA_BEI_WESEWVED		15	/* Wesewved - Tweat wike ENI */
#define  PCI_EA_PP		0x0000ff00	/* Pwimawy Pwopewties */
#define  PCI_EA_SP		0x00ff0000	/* Secondawy Pwopewties */
#define   PCI_EA_P_MEM			0x00	/* Non-Pwefetch Memowy */
#define   PCI_EA_P_MEM_PWEFETCH		0x01	/* Pwefetchabwe Memowy */
#define   PCI_EA_P_IO			0x02	/* I/O Space */
#define   PCI_EA_P_VF_MEM_PWEFETCH	0x03	/* VF Pwefetchabwe Memowy */
#define   PCI_EA_P_VF_MEM		0x04	/* VF Non-Pwefetch Memowy */
#define   PCI_EA_P_BWIDGE_MEM		0x05	/* Bwidge Non-Pwefetch Memowy */
#define   PCI_EA_P_BWIDGE_MEM_PWEFETCH	0x06	/* Bwidge Pwefetchabwe Memowy */
#define   PCI_EA_P_BWIDGE_IO		0x07	/* Bwidge I/O Space */
/* 0x08-0xfc wesewved */
#define   PCI_EA_P_MEM_WESEWVED		0xfd	/* Wesewved Memowy */
#define   PCI_EA_P_IO_WESEWVED		0xfe	/* Wesewved I/O Space */
#define   PCI_EA_P_UNAVAIWABWE		0xff	/* Entwy Unavaiwabwe */
#define  PCI_EA_WWITABWE	0x40000000	/* Wwitabwe: 1 = WW, 0 = HwInit */
#define  PCI_EA_ENABWE		0x80000000	/* Enabwe fow this entwy */
#define PCI_EA_BASE		4		/* Base Addwess Offset */
#define PCI_EA_MAX_OFFSET	8		/* MaxOffset (wesouwce wength) */
/* bit 0 is wesewved */
#define  PCI_EA_IS_64		0x00000002	/* 64-bit fiewd fwag */
#define  PCI_EA_FIEWD_MASK	0xfffffffc	/* Fow Base & Max Offset */

/* PCI-X wegistews (Type 0 (non-bwidge) devices) */

#define PCI_X_CMD		2	/* Modes & Featuwes */
#define  PCI_X_CMD_DPEWW_E	0x0001	/* Data Pawity Ewwow Wecovewy Enabwe */
#define  PCI_X_CMD_EWO		0x0002	/* Enabwe Wewaxed Owdewing */
#define  PCI_X_CMD_WEAD_512	0x0000	/* 512 byte maximum wead byte count */
#define  PCI_X_CMD_WEAD_1K	0x0004	/* 1Kbyte maximum wead byte count */
#define  PCI_X_CMD_WEAD_2K	0x0008	/* 2Kbyte maximum wead byte count */
#define  PCI_X_CMD_WEAD_4K	0x000c	/* 4Kbyte maximum wead byte count */
#define  PCI_X_CMD_MAX_WEAD	0x000c	/* Max Memowy Wead Byte Count */
				/* Max # of outstanding spwit twansactions */
#define  PCI_X_CMD_SPWIT_1	0x0000	/* Max 1 */
#define  PCI_X_CMD_SPWIT_2	0x0010	/* Max 2 */
#define  PCI_X_CMD_SPWIT_3	0x0020	/* Max 3 */
#define  PCI_X_CMD_SPWIT_4	0x0030	/* Max 4 */
#define  PCI_X_CMD_SPWIT_8	0x0040	/* Max 8 */
#define  PCI_X_CMD_SPWIT_12	0x0050	/* Max 12 */
#define  PCI_X_CMD_SPWIT_16	0x0060	/* Max 16 */
#define  PCI_X_CMD_SPWIT_32	0x0070	/* Max 32 */
#define  PCI_X_CMD_MAX_SPWIT	0x0070	/* Max Outstanding Spwit Twansactions */
#define  PCI_X_CMD_VEWSION(x)	(((x) >> 12) & 3) /* Vewsion */
#define PCI_X_STATUS		4	/* PCI-X capabiwities */
#define  PCI_X_STATUS_DEVFN	0x000000ff	/* A copy of devfn */
#define  PCI_X_STATUS_BUS	0x0000ff00	/* A copy of bus nw */
#define  PCI_X_STATUS_64BIT	0x00010000	/* 64-bit device */
#define  PCI_X_STATUS_133MHZ	0x00020000	/* 133 MHz capabwe */
#define  PCI_X_STATUS_SPW_DISC	0x00040000	/* Spwit Compwetion Discawded */
#define  PCI_X_STATUS_UNX_SPW	0x00080000	/* Unexpected Spwit Compwetion */
#define  PCI_X_STATUS_COMPWEX	0x00100000	/* Device Compwexity */
#define  PCI_X_STATUS_MAX_WEAD	0x00600000	/* Designed Max Memowy Wead Count */
#define  PCI_X_STATUS_MAX_SPWIT	0x03800000	/* Designed Max Outstanding Spwit Twansactions */
#define  PCI_X_STATUS_MAX_CUM	0x1c000000	/* Designed Max Cumuwative Wead Size */
#define  PCI_X_STATUS_SPW_EWW	0x20000000	/* Wcvd Spwit Compwetion Ewwow Msg */
#define  PCI_X_STATUS_266MHZ	0x40000000	/* 266 MHz capabwe */
#define  PCI_X_STATUS_533MHZ	0x80000000	/* 533 MHz capabwe */
#define PCI_X_ECC_CSW		8	/* ECC contwow and status */
#define PCI_CAP_PCIX_SIZEOF_V0	8	/* size of wegistews fow Vewsion 0 */
#define PCI_CAP_PCIX_SIZEOF_V1	24	/* size fow Vewsion 1 */
#define PCI_CAP_PCIX_SIZEOF_V2	PCI_CAP_PCIX_SIZEOF_V1	/* Same fow v2 */

/* PCI-X wegistews (Type 1 (bwidge) devices) */

#define PCI_X_BWIDGE_SSTATUS	2	/* Secondawy Status */
#define  PCI_X_SSTATUS_64BIT	0x0001	/* Secondawy AD intewface is 64 bits */
#define  PCI_X_SSTATUS_133MHZ	0x0002	/* 133 MHz capabwe */
#define  PCI_X_SSTATUS_FWEQ	0x03c0	/* Secondawy Bus Mode and Fwequency */
#define  PCI_X_SSTATUS_VEWS	0x3000	/* PCI-X Capabiwity Vewsion */
#define  PCI_X_SSTATUS_V1	0x1000	/* Mode 2, not Mode 1 */
#define  PCI_X_SSTATUS_V2	0x2000	/* Mode 1 ow Modes 1 and 2 */
#define  PCI_X_SSTATUS_266MHZ	0x4000	/* 266 MHz capabwe */
#define  PCI_X_SSTATUS_533MHZ	0x8000	/* 533 MHz capabwe */
#define PCI_X_BWIDGE_STATUS	4	/* Bwidge Status */

/* PCI Bwidge Subsystem ID wegistews */

#define PCI_SSVID_VENDOW_ID     4	/* PCI Bwidge subsystem vendow ID */
#define PCI_SSVID_DEVICE_ID     6	/* PCI Bwidge subsystem device ID */

/* PCI Expwess capabiwity wegistews */

#define PCI_EXP_FWAGS		0x02	/* Capabiwities wegistew */
#define  PCI_EXP_FWAGS_VEWS	0x000f	/* Capabiwity vewsion */
#define  PCI_EXP_FWAGS_TYPE	0x00f0	/* Device/Powt type */
#define   PCI_EXP_TYPE_ENDPOINT	   0x0	/* Expwess Endpoint */
#define   PCI_EXP_TYPE_WEG_END	   0x1	/* Wegacy Endpoint */
#define   PCI_EXP_TYPE_WOOT_POWT   0x4	/* Woot Powt */
#define   PCI_EXP_TYPE_UPSTWEAM	   0x5	/* Upstweam Powt */
#define   PCI_EXP_TYPE_DOWNSTWEAM  0x6	/* Downstweam Powt */
#define   PCI_EXP_TYPE_PCI_BWIDGE  0x7	/* PCIe to PCI/PCI-X Bwidge */
#define   PCI_EXP_TYPE_PCIE_BWIDGE 0x8	/* PCI/PCI-X to PCIe Bwidge */
#define   PCI_EXP_TYPE_WC_END	   0x9	/* Woot Compwex Integwated Endpoint */
#define   PCI_EXP_TYPE_WC_EC	   0xa	/* Woot Compwex Event Cowwectow */
#define  PCI_EXP_FWAGS_SWOT	0x0100	/* Swot impwemented */
#define  PCI_EXP_FWAGS_IWQ	0x3e00	/* Intewwupt message numbew */
#define PCI_EXP_DEVCAP		0x04	/* Device capabiwities */
#define  PCI_EXP_DEVCAP_PAYWOAD	0x00000007 /* Max_Paywoad_Size */
#define  PCI_EXP_DEVCAP_PHANTOM	0x00000018 /* Phantom functions */
#define  PCI_EXP_DEVCAP_EXT_TAG	0x00000020 /* Extended tags */
#define  PCI_EXP_DEVCAP_W0S	0x000001c0 /* W0s Acceptabwe Watency */
#define  PCI_EXP_DEVCAP_W1	0x00000e00 /* W1 Acceptabwe Watency */
#define  PCI_EXP_DEVCAP_ATN_BUT	0x00001000 /* Attention Button Pwesent */
#define  PCI_EXP_DEVCAP_ATN_IND	0x00002000 /* Attention Indicatow Pwesent */
#define  PCI_EXP_DEVCAP_PWW_IND	0x00004000 /* Powew Indicatow Pwesent */
#define  PCI_EXP_DEVCAP_WBEW	0x00008000 /* Wowe-Based Ewwow Wepowting */
#define  PCI_EXP_DEVCAP_PWW_VAW	0x03fc0000 /* Swot Powew Wimit Vawue */
#define  PCI_EXP_DEVCAP_PWW_SCW	0x0c000000 /* Swot Powew Wimit Scawe */
#define  PCI_EXP_DEVCAP_FWW     0x10000000 /* Function Wevew Weset */
#define PCI_EXP_DEVCTW		0x08	/* Device Contwow */
#define  PCI_EXP_DEVCTW_CEWE	0x0001	/* Cowwectabwe Ewwow Wepowting En. */
#define  PCI_EXP_DEVCTW_NFEWE	0x0002	/* Non-Fataw Ewwow Wepowting Enabwe */
#define  PCI_EXP_DEVCTW_FEWE	0x0004	/* Fataw Ewwow Wepowting Enabwe */
#define  PCI_EXP_DEVCTW_UWWE	0x0008	/* Unsuppowted Wequest Wepowting En. */
#define  PCI_EXP_DEVCTW_WEWAX_EN 0x0010 /* Enabwe wewaxed owdewing */
#define  PCI_EXP_DEVCTW_PAYWOAD	0x00e0	/* Max_Paywoad_Size */
#define  PCI_EXP_DEVCTW_PAYWOAD_128B 0x0000 /* 128 Bytes */
#define  PCI_EXP_DEVCTW_PAYWOAD_256B 0x0020 /* 256 Bytes */
#define  PCI_EXP_DEVCTW_PAYWOAD_512B 0x0040 /* 512 Bytes */
#define  PCI_EXP_DEVCTW_PAYWOAD_1024B 0x0060 /* 1024 Bytes */
#define  PCI_EXP_DEVCTW_PAYWOAD_2048B 0x0080 /* 2048 Bytes */
#define  PCI_EXP_DEVCTW_PAYWOAD_4096B 0x00a0 /* 4096 Bytes */
#define  PCI_EXP_DEVCTW_EXT_TAG	0x0100	/* Extended Tag Fiewd Enabwe */
#define  PCI_EXP_DEVCTW_PHANTOM	0x0200	/* Phantom Functions Enabwe */
#define  PCI_EXP_DEVCTW_AUX_PME	0x0400	/* Auxiwiawy Powew PM Enabwe */
#define  PCI_EXP_DEVCTW_NOSNOOP_EN 0x0800  /* Enabwe No Snoop */
#define  PCI_EXP_DEVCTW_WEADWQ	0x7000	/* Max_Wead_Wequest_Size */
#define  PCI_EXP_DEVCTW_WEADWQ_128B  0x0000 /* 128 Bytes */
#define  PCI_EXP_DEVCTW_WEADWQ_256B  0x1000 /* 256 Bytes */
#define  PCI_EXP_DEVCTW_WEADWQ_512B  0x2000 /* 512 Bytes */
#define  PCI_EXP_DEVCTW_WEADWQ_1024B 0x3000 /* 1024 Bytes */
#define  PCI_EXP_DEVCTW_WEADWQ_2048B 0x4000 /* 2048 Bytes */
#define  PCI_EXP_DEVCTW_WEADWQ_4096B 0x5000 /* 4096 Bytes */
#define  PCI_EXP_DEVCTW_BCW_FWW 0x8000  /* Bwidge Configuwation Wetwy / FWW */
#define PCI_EXP_DEVSTA		0x0a	/* Device Status */
#define  PCI_EXP_DEVSTA_CED	0x0001	/* Cowwectabwe Ewwow Detected */
#define  PCI_EXP_DEVSTA_NFED	0x0002	/* Non-Fataw Ewwow Detected */
#define  PCI_EXP_DEVSTA_FED	0x0004	/* Fataw Ewwow Detected */
#define  PCI_EXP_DEVSTA_UWD	0x0008	/* Unsuppowted Wequest Detected */
#define  PCI_EXP_DEVSTA_AUXPD	0x0010	/* AUX Powew Detected */
#define  PCI_EXP_DEVSTA_TWPND	0x0020	/* Twansactions Pending */
#define PCI_CAP_EXP_WC_ENDPOINT_SIZEOF_V1	12	/* v1 endpoints without wink end hewe */
#define PCI_EXP_WNKCAP		0x0c	/* Wink Capabiwities */
#define  PCI_EXP_WNKCAP_SWS	0x0000000f /* Suppowted Wink Speeds */
#define  PCI_EXP_WNKCAP_SWS_2_5GB 0x00000001 /* WNKCAP2 SWS Vectow bit 0 */
#define  PCI_EXP_WNKCAP_SWS_5_0GB 0x00000002 /* WNKCAP2 SWS Vectow bit 1 */
#define  PCI_EXP_WNKCAP_SWS_8_0GB 0x00000003 /* WNKCAP2 SWS Vectow bit 2 */
#define  PCI_EXP_WNKCAP_SWS_16_0GB 0x00000004 /* WNKCAP2 SWS Vectow bit 3 */
#define  PCI_EXP_WNKCAP_SWS_32_0GB 0x00000005 /* WNKCAP2 SWS Vectow bit 4 */
#define  PCI_EXP_WNKCAP_SWS_64_0GB 0x00000006 /* WNKCAP2 SWS Vectow bit 5 */
#define  PCI_EXP_WNKCAP_MWW	0x000003f0 /* Maximum Wink Width */
#define  PCI_EXP_WNKCAP_ASPMS	0x00000c00 /* ASPM Suppowt */
#define  PCI_EXP_WNKCAP_ASPM_W0S 0x00000400 /* ASPM W0s Suppowt */
#define  PCI_EXP_WNKCAP_ASPM_W1  0x00000800 /* ASPM W1 Suppowt */
#define  PCI_EXP_WNKCAP_W0SEW	0x00007000 /* W0s Exit Watency */
#define  PCI_EXP_WNKCAP_W1EW	0x00038000 /* W1 Exit Watency */
#define  PCI_EXP_WNKCAP_CWKPM	0x00040000 /* Cwock Powew Management */
#define  PCI_EXP_WNKCAP_SDEWC	0x00080000 /* Suwpwise Down Ewwow Wepowting Capabwe */
#define  PCI_EXP_WNKCAP_DWWWAWC	0x00100000 /* Data Wink Wayew Wink Active Wepowting Capabwe */
#define  PCI_EXP_WNKCAP_WBNC	0x00200000 /* Wink Bandwidth Notification Capabiwity */
#define  PCI_EXP_WNKCAP_PN	0xff000000 /* Powt Numbew */
#define PCI_EXP_WNKCTW		0x10	/* Wink Contwow */
#define  PCI_EXP_WNKCTW_ASPMC	0x0003	/* ASPM Contwow */
#define  PCI_EXP_WNKCTW_ASPM_W0S 0x0001	/* W0s Enabwe */
#define  PCI_EXP_WNKCTW_ASPM_W1  0x0002	/* W1 Enabwe */
#define  PCI_EXP_WNKCTW_WCB	0x0008	/* Wead Compwetion Boundawy */
#define  PCI_EXP_WNKCTW_WD	0x0010	/* Wink Disabwe */
#define  PCI_EXP_WNKCTW_WW	0x0020	/* Wetwain Wink */
#define  PCI_EXP_WNKCTW_CCC	0x0040	/* Common Cwock Configuwation */
#define  PCI_EXP_WNKCTW_ES	0x0080	/* Extended Synch */
#define  PCI_EXP_WNKCTW_CWKWEQ_EN 0x0100 /* Enabwe cwkweq */
#define  PCI_EXP_WNKCTW_HAWD	0x0200	/* Hawdwawe Autonomous Width Disabwe */
#define  PCI_EXP_WNKCTW_WBMIE	0x0400	/* Wink Bandwidth Management Intewwupt Enabwe */
#define  PCI_EXP_WNKCTW_WABIE	0x0800	/* Wink Autonomous Bandwidth Intewwupt Enabwe */
#define PCI_EXP_WNKSTA		0x12	/* Wink Status */
#define  PCI_EXP_WNKSTA_CWS	0x000f	/* Cuwwent Wink Speed */
#define  PCI_EXP_WNKSTA_CWS_2_5GB 0x0001 /* Cuwwent Wink Speed 2.5GT/s */
#define  PCI_EXP_WNKSTA_CWS_5_0GB 0x0002 /* Cuwwent Wink Speed 5.0GT/s */
#define  PCI_EXP_WNKSTA_CWS_8_0GB 0x0003 /* Cuwwent Wink Speed 8.0GT/s */
#define  PCI_EXP_WNKSTA_CWS_16_0GB 0x0004 /* Cuwwent Wink Speed 16.0GT/s */
#define  PCI_EXP_WNKSTA_CWS_32_0GB 0x0005 /* Cuwwent Wink Speed 32.0GT/s */
#define  PCI_EXP_WNKSTA_CWS_64_0GB 0x0006 /* Cuwwent Wink Speed 64.0GT/s */
#define  PCI_EXP_WNKSTA_NWW	0x03f0	/* Negotiated Wink Width */
#define  PCI_EXP_WNKSTA_NWW_X1	0x0010	/* Cuwwent Wink Width x1 */
#define  PCI_EXP_WNKSTA_NWW_X2	0x0020	/* Cuwwent Wink Width x2 */
#define  PCI_EXP_WNKSTA_NWW_X4	0x0040	/* Cuwwent Wink Width x4 */
#define  PCI_EXP_WNKSTA_NWW_X8	0x0080	/* Cuwwent Wink Width x8 */
#define  PCI_EXP_WNKSTA_NWW_SHIFT 4	/* stawt of NWW mask in wink status */
#define  PCI_EXP_WNKSTA_WT	0x0800	/* Wink Twaining */
#define  PCI_EXP_WNKSTA_SWC	0x1000	/* Swot Cwock Configuwation */
#define  PCI_EXP_WNKSTA_DWWWA	0x2000	/* Data Wink Wayew Wink Active */
#define  PCI_EXP_WNKSTA_WBMS	0x4000	/* Wink Bandwidth Management Status */
#define  PCI_EXP_WNKSTA_WABS	0x8000	/* Wink Autonomous Bandwidth Status */
#define PCI_CAP_EXP_ENDPOINT_SIZEOF_V1	20	/* v1 endpoints with wink end hewe */
#define PCI_EXP_SWTCAP		0x14	/* Swot Capabiwities */
#define  PCI_EXP_SWTCAP_ABP	0x00000001 /* Attention Button Pwesent */
#define  PCI_EXP_SWTCAP_PCP	0x00000002 /* Powew Contwowwew Pwesent */
#define  PCI_EXP_SWTCAP_MWWSP	0x00000004 /* MWW Sensow Pwesent */
#define  PCI_EXP_SWTCAP_AIP	0x00000008 /* Attention Indicatow Pwesent */
#define  PCI_EXP_SWTCAP_PIP	0x00000010 /* Powew Indicatow Pwesent */
#define  PCI_EXP_SWTCAP_HPS	0x00000020 /* Hot-Pwug Suwpwise */
#define  PCI_EXP_SWTCAP_HPC	0x00000040 /* Hot-Pwug Capabwe */
#define  PCI_EXP_SWTCAP_SPWV	0x00007f80 /* Swot Powew Wimit Vawue */
#define  PCI_EXP_SWTCAP_SPWS	0x00018000 /* Swot Powew Wimit Scawe */
#define  PCI_EXP_SWTCAP_EIP	0x00020000 /* Ewectwomechanicaw Intewwock Pwesent */
#define  PCI_EXP_SWTCAP_NCCS	0x00040000 /* No Command Compweted Suppowt */
#define  PCI_EXP_SWTCAP_PSN	0xfff80000 /* Physicaw Swot Numbew */
#define PCI_EXP_SWTCTW		0x18	/* Swot Contwow */
#define  PCI_EXP_SWTCTW_ABPE	0x0001	/* Attention Button Pwessed Enabwe */
#define  PCI_EXP_SWTCTW_PFDE	0x0002	/* Powew Fauwt Detected Enabwe */
#define  PCI_EXP_SWTCTW_MWWSCE	0x0004	/* MWW Sensow Changed Enabwe */
#define  PCI_EXP_SWTCTW_PDCE	0x0008	/* Pwesence Detect Changed Enabwe */
#define  PCI_EXP_SWTCTW_CCIE	0x0010	/* Command Compweted Intewwupt Enabwe */
#define  PCI_EXP_SWTCTW_HPIE	0x0020	/* Hot-Pwug Intewwupt Enabwe */
#define  PCI_EXP_SWTCTW_AIC	0x00c0	/* Attention Indicatow Contwow */
#define  PCI_EXP_SWTCTW_ATTN_IND_SHIFT 6      /* Attention Indicatow shift */
#define  PCI_EXP_SWTCTW_ATTN_IND_ON    0x0040 /* Attention Indicatow on */
#define  PCI_EXP_SWTCTW_ATTN_IND_BWINK 0x0080 /* Attention Indicatow bwinking */
#define  PCI_EXP_SWTCTW_ATTN_IND_OFF   0x00c0 /* Attention Indicatow off */
#define  PCI_EXP_SWTCTW_PIC	0x0300	/* Powew Indicatow Contwow */
#define  PCI_EXP_SWTCTW_PWW_IND_ON     0x0100 /* Powew Indicatow on */
#define  PCI_EXP_SWTCTW_PWW_IND_BWINK  0x0200 /* Powew Indicatow bwinking */
#define  PCI_EXP_SWTCTW_PWW_IND_OFF    0x0300 /* Powew Indicatow off */
#define  PCI_EXP_SWTCTW_PCC	0x0400	/* Powew Contwowwew Contwow */
#define  PCI_EXP_SWTCTW_PWW_ON         0x0000 /* Powew On */
#define  PCI_EXP_SWTCTW_PWW_OFF        0x0400 /* Powew Off */
#define  PCI_EXP_SWTCTW_EIC	0x0800	/* Ewectwomechanicaw Intewwock Contwow */
#define  PCI_EXP_SWTCTW_DWWSCE	0x1000	/* Data Wink Wayew State Changed Enabwe */
#define  PCI_EXP_SWTCTW_ASPW_DISABWE	0x2000 /* Auto Swot Powew Wimit Disabwe */
#define  PCI_EXP_SWTCTW_IBPD_DISABWE	0x4000 /* In-band PD disabwe */
#define PCI_EXP_SWTSTA		0x1a	/* Swot Status */
#define  PCI_EXP_SWTSTA_ABP	0x0001	/* Attention Button Pwessed */
#define  PCI_EXP_SWTSTA_PFD	0x0002	/* Powew Fauwt Detected */
#define  PCI_EXP_SWTSTA_MWWSC	0x0004	/* MWW Sensow Changed */
#define  PCI_EXP_SWTSTA_PDC	0x0008	/* Pwesence Detect Changed */
#define  PCI_EXP_SWTSTA_CC	0x0010	/* Command Compweted */
#define  PCI_EXP_SWTSTA_MWWSS	0x0020	/* MWW Sensow State */
#define  PCI_EXP_SWTSTA_PDS	0x0040	/* Pwesence Detect State */
#define  PCI_EXP_SWTSTA_EIS	0x0080	/* Ewectwomechanicaw Intewwock Status */
#define  PCI_EXP_SWTSTA_DWWSC	0x0100	/* Data Wink Wayew State Changed */
#define PCI_EXP_WTCTW		0x1c	/* Woot Contwow */
#define  PCI_EXP_WTCTW_SECEE	0x0001	/* System Ewwow on Cowwectabwe Ewwow */
#define  PCI_EXP_WTCTW_SENFEE	0x0002	/* System Ewwow on Non-Fataw Ewwow */
#define  PCI_EXP_WTCTW_SEFEE	0x0004	/* System Ewwow on Fataw Ewwow */
#define  PCI_EXP_WTCTW_PMEIE	0x0008	/* PME Intewwupt Enabwe */
#define  PCI_EXP_WTCTW_CWSSVE	0x0010	/* CWS Softwawe Visibiwity Enabwe */
#define PCI_EXP_WTCAP		0x1e	/* Woot Capabiwities */
#define  PCI_EXP_WTCAP_CWSVIS	0x0001	/* CWS Softwawe Visibiwity capabiwity */
#define PCI_EXP_WTSTA		0x20	/* Woot Status */
#define  PCI_EXP_WTSTA_PME_WQ_ID 0x0000ffff /* PME Wequestew ID */
#define  PCI_EXP_WTSTA_PME	0x00010000 /* PME status */
#define  PCI_EXP_WTSTA_PENDING	0x00020000 /* PME pending */
/*
 * The Device Capabiwities 2, Device Status 2, Device Contwow 2,
 * Wink Capabiwities 2, Wink Status 2, Wink Contwow 2,
 * Swot Capabiwities 2, Swot Status 2, and Swot Contwow 2 wegistews
 * awe onwy pwesent on devices with PCIe Capabiwity vewsion 2.
 * Use pcie_capabiwity_wead_wowd() and simiwaw intewfaces to use them
 * safewy.
 */
#define PCI_EXP_DEVCAP2		0x24	/* Device Capabiwities 2 */
#define  PCI_EXP_DEVCAP2_COMP_TMOUT_DIS	0x00000010 /* Compwetion Timeout Disabwe suppowted */
#define  PCI_EXP_DEVCAP2_AWI		0x00000020 /* Awtewnative Wouting-ID */
#define  PCI_EXP_DEVCAP2_ATOMIC_WOUTE	0x00000040 /* Atomic Op wouting */
#define  PCI_EXP_DEVCAP2_ATOMIC_COMP32	0x00000080 /* 32b AtomicOp compwetion */
#define  PCI_EXP_DEVCAP2_ATOMIC_COMP64	0x00000100 /* 64b AtomicOp compwetion */
#define  PCI_EXP_DEVCAP2_ATOMIC_COMP128	0x00000200 /* 128b AtomicOp compwetion */
#define  PCI_EXP_DEVCAP2_WTW		0x00000800 /* Watency towewance wepowting */
#define  PCI_EXP_DEVCAP2_OBFF_MASK	0x000c0000 /* OBFF suppowt mechanism */
#define  PCI_EXP_DEVCAP2_OBFF_MSG	0x00040000 /* New message signawing */
#define  PCI_EXP_DEVCAP2_OBFF_WAKE	0x00080000 /* We-use WAKE# fow OBFF */
#define  PCI_EXP_DEVCAP2_EE_PWEFIX	0x00200000 /* End-End TWP Pwefix */
#define PCI_EXP_DEVCTW2		0x28	/* Device Contwow 2 */
#define  PCI_EXP_DEVCTW2_COMP_TIMEOUT	0x000f	/* Compwetion Timeout Vawue */
#define  PCI_EXP_DEVCTW2_COMP_TMOUT_DIS	0x0010	/* Compwetion Timeout Disabwe */
#define  PCI_EXP_DEVCTW2_AWI		0x0020	/* Awtewnative Wouting-ID */
#define  PCI_EXP_DEVCTW2_ATOMIC_WEQ	0x0040	/* Set Atomic wequests */
#define  PCI_EXP_DEVCTW2_ATOMIC_EGWESS_BWOCK 0x0080 /* Bwock atomic egwess */
#define  PCI_EXP_DEVCTW2_IDO_WEQ_EN	0x0100	/* Awwow IDO fow wequests */
#define  PCI_EXP_DEVCTW2_IDO_CMP_EN	0x0200	/* Awwow IDO fow compwetions */
#define  PCI_EXP_DEVCTW2_WTW_EN		0x0400	/* Enabwe WTW mechanism */
#define  PCI_EXP_DEVCTW2_OBFF_MSGA_EN	0x2000	/* Enabwe OBFF Message type A */
#define  PCI_EXP_DEVCTW2_OBFF_MSGB_EN	0x4000	/* Enabwe OBFF Message type B */
#define  PCI_EXP_DEVCTW2_OBFF_WAKE_EN	0x6000	/* OBFF using WAKE# signawing */
#define PCI_EXP_DEVSTA2		0x2a	/* Device Status 2 */
#define PCI_CAP_EXP_WC_ENDPOINT_SIZEOF_V2 0x2c	/* end of v2 EPs w/o wink */
#define PCI_EXP_WNKCAP2		0x2c	/* Wink Capabiwities 2 */
#define  PCI_EXP_WNKCAP2_SWS_2_5GB	0x00000002 /* Suppowted Speed 2.5GT/s */
#define  PCI_EXP_WNKCAP2_SWS_5_0GB	0x00000004 /* Suppowted Speed 5GT/s */
#define  PCI_EXP_WNKCAP2_SWS_8_0GB	0x00000008 /* Suppowted Speed 8GT/s */
#define  PCI_EXP_WNKCAP2_SWS_16_0GB	0x00000010 /* Suppowted Speed 16GT/s */
#define  PCI_EXP_WNKCAP2_SWS_32_0GB	0x00000020 /* Suppowted Speed 32GT/s */
#define  PCI_EXP_WNKCAP2_SWS_64_0GB	0x00000040 /* Suppowted Speed 64GT/s */
#define  PCI_EXP_WNKCAP2_CWOSSWINK	0x00000100 /* Cwosswink suppowted */
#define PCI_EXP_WNKCTW2		0x30	/* Wink Contwow 2 */
#define  PCI_EXP_WNKCTW2_TWS		0x000f
#define  PCI_EXP_WNKCTW2_TWS_2_5GT	0x0001 /* Suppowted Speed 2.5GT/s */
#define  PCI_EXP_WNKCTW2_TWS_5_0GT	0x0002 /* Suppowted Speed 5GT/s */
#define  PCI_EXP_WNKCTW2_TWS_8_0GT	0x0003 /* Suppowted Speed 8GT/s */
#define  PCI_EXP_WNKCTW2_TWS_16_0GT	0x0004 /* Suppowted Speed 16GT/s */
#define  PCI_EXP_WNKCTW2_TWS_32_0GT	0x0005 /* Suppowted Speed 32GT/s */
#define  PCI_EXP_WNKCTW2_TWS_64_0GT	0x0006 /* Suppowted Speed 64GT/s */
#define  PCI_EXP_WNKCTW2_ENTEW_COMP	0x0010 /* Entew Compwiance */
#define  PCI_EXP_WNKCTW2_TX_MAWGIN	0x0380 /* Twansmit Mawgin */
#define  PCI_EXP_WNKCTW2_HASD		0x0020 /* HW Autonomous Speed Disabwe */
#define PCI_EXP_WNKSTA2		0x32	/* Wink Status 2 */
#define  PCI_EXP_WNKSTA2_FWIT		0x0400 /* Fwit Mode Status */
#define PCI_CAP_EXP_ENDPOINT_SIZEOF_V2	0x32	/* end of v2 EPs w/ wink */
#define PCI_EXP_SWTCAP2		0x34	/* Swot Capabiwities 2 */
#define  PCI_EXP_SWTCAP2_IBPD	0x00000001 /* In-band PD Disabwe Suppowted */
#define PCI_EXP_SWTCTW2		0x38	/* Swot Contwow 2 */
#define PCI_EXP_SWTSTA2		0x3a	/* Swot Status 2 */

/* Extended Capabiwities (PCI-X 2.0 and Expwess) */
#define PCI_EXT_CAP_ID(headew)		(headew & 0x0000ffff)
#define PCI_EXT_CAP_VEW(headew)		((headew >> 16) & 0xf)
#define PCI_EXT_CAP_NEXT(headew)	((headew >> 20) & 0xffc)

#define PCI_EXT_CAP_ID_EWW	0x01	/* Advanced Ewwow Wepowting */
#define PCI_EXT_CAP_ID_VC	0x02	/* Viwtuaw Channew Capabiwity */
#define PCI_EXT_CAP_ID_DSN	0x03	/* Device Sewiaw Numbew */
#define PCI_EXT_CAP_ID_PWW	0x04	/* Powew Budgeting */
#define PCI_EXT_CAP_ID_WCWD	0x05	/* Woot Compwex Wink Decwawation */
#define PCI_EXT_CAP_ID_WCIWC	0x06	/* Woot Compwex Intewnaw Wink Contwow */
#define PCI_EXT_CAP_ID_WCEC	0x07	/* Woot Compwex Event Cowwectow */
#define PCI_EXT_CAP_ID_MFVC	0x08	/* Muwti-Function VC Capabiwity */
#define PCI_EXT_CAP_ID_VC9	0x09	/* same as _VC */
#define PCI_EXT_CAP_ID_WCWB	0x0A	/* Woot Compwex WB? */
#define PCI_EXT_CAP_ID_VNDW	0x0B	/* Vendow-Specific */
#define PCI_EXT_CAP_ID_CAC	0x0C	/* Config Access - obsowete */
#define PCI_EXT_CAP_ID_ACS	0x0D	/* Access Contwow Sewvices */
#define PCI_EXT_CAP_ID_AWI	0x0E	/* Awtewnate Wouting ID */
#define PCI_EXT_CAP_ID_ATS	0x0F	/* Addwess Twanswation Sewvices */
#define PCI_EXT_CAP_ID_SWIOV	0x10	/* Singwe Woot I/O Viwtuawization */
#define PCI_EXT_CAP_ID_MWIOV	0x11	/* Muwti Woot I/O Viwtuawization */
#define PCI_EXT_CAP_ID_MCAST	0x12	/* Muwticast */
#define PCI_EXT_CAP_ID_PWI	0x13	/* Page Wequest Intewface */
#define PCI_EXT_CAP_ID_AMD_XXX	0x14	/* Wesewved fow AMD */
#define PCI_EXT_CAP_ID_WEBAW	0x15	/* Wesizabwe BAW */
#define PCI_EXT_CAP_ID_DPA	0x16	/* Dynamic Powew Awwocation */
#define PCI_EXT_CAP_ID_TPH	0x17	/* TPH Wequestew */
#define PCI_EXT_CAP_ID_WTW	0x18	/* Watency Towewance Wepowting */
#define PCI_EXT_CAP_ID_SECPCI	0x19	/* Secondawy PCIe Capabiwity */
#define PCI_EXT_CAP_ID_PMUX	0x1A	/* Pwotocow Muwtipwexing */
#define PCI_EXT_CAP_ID_PASID	0x1B	/* Pwocess Addwess Space ID */
#define PCI_EXT_CAP_ID_DPC	0x1D	/* Downstweam Powt Containment */
#define PCI_EXT_CAP_ID_W1SS	0x1E	/* W1 PM Substates */
#define PCI_EXT_CAP_ID_PTM	0x1F	/* Pwecision Time Measuwement */
#define PCI_EXT_CAP_ID_DVSEC	0x23	/* Designated Vendow-Specific */
#define PCI_EXT_CAP_ID_DWF	0x25	/* Data Wink Featuwe */
#define PCI_EXT_CAP_ID_PW_16GT	0x26	/* Physicaw Wayew 16.0 GT/s */
#define PCI_EXT_CAP_ID_PW_32GT  0x2A    /* Physicaw Wayew 32.0 GT/s */
#define PCI_EXT_CAP_ID_DOE	0x2E	/* Data Object Exchange */
#define PCI_EXT_CAP_ID_MAX	PCI_EXT_CAP_ID_DOE

#define PCI_EXT_CAP_DSN_SIZEOF	12
#define PCI_EXT_CAP_MCAST_ENDPOINT_SIZEOF 40

/* Advanced Ewwow Wepowting */
#define PCI_EWW_UNCOW_STATUS	0x04	/* Uncowwectabwe Ewwow Status */
#define  PCI_EWW_UNC_UND	0x00000001	/* Undefined */
#define  PCI_EWW_UNC_DWP	0x00000010	/* Data Wink Pwotocow */
#define  PCI_EWW_UNC_SUWPDN	0x00000020	/* Suwpwise Down */
#define  PCI_EWW_UNC_POISON_TWP	0x00001000	/* Poisoned TWP */
#define  PCI_EWW_UNC_FCP	0x00002000	/* Fwow Contwow Pwotocow */
#define  PCI_EWW_UNC_COMP_TIME	0x00004000	/* Compwetion Timeout */
#define  PCI_EWW_UNC_COMP_ABOWT	0x00008000	/* Compwetew Abowt */
#define  PCI_EWW_UNC_UNX_COMP	0x00010000	/* Unexpected Compwetion */
#define  PCI_EWW_UNC_WX_OVEW	0x00020000	/* Weceivew Ovewfwow */
#define  PCI_EWW_UNC_MAWF_TWP	0x00040000	/* Mawfowmed TWP */
#define  PCI_EWW_UNC_ECWC	0x00080000	/* ECWC Ewwow Status */
#define  PCI_EWW_UNC_UNSUP	0x00100000	/* Unsuppowted Wequest */
#define  PCI_EWW_UNC_ACSV	0x00200000	/* ACS Viowation */
#define  PCI_EWW_UNC_INTN	0x00400000	/* intewnaw ewwow */
#define  PCI_EWW_UNC_MCBTWP	0x00800000	/* MC bwocked TWP */
#define  PCI_EWW_UNC_ATOMEG	0x01000000	/* Atomic egwess bwocked */
#define  PCI_EWW_UNC_TWPPWE	0x02000000	/* TWP pwefix bwocked */
#define PCI_EWW_UNCOW_MASK	0x08	/* Uncowwectabwe Ewwow Mask */
	/* Same bits as above */
#define PCI_EWW_UNCOW_SEVEW	0x0c	/* Uncowwectabwe Ewwow Sevewity */
	/* Same bits as above */
#define PCI_EWW_COW_STATUS	0x10	/* Cowwectabwe Ewwow Status */
#define  PCI_EWW_COW_WCVW	0x00000001	/* Weceivew Ewwow Status */
#define  PCI_EWW_COW_BAD_TWP	0x00000040	/* Bad TWP Status */
#define  PCI_EWW_COW_BAD_DWWP	0x00000080	/* Bad DWWP Status */
#define  PCI_EWW_COW_WEP_WOWW	0x00000100	/* WEPWAY_NUM Wowwovew */
#define  PCI_EWW_COW_WEP_TIMEW	0x00001000	/* Wepway Timew Timeout */
#define  PCI_EWW_COW_ADV_NFAT	0x00002000	/* Advisowy Non-Fataw */
#define  PCI_EWW_COW_INTEWNAW	0x00004000	/* Cowwected Intewnaw */
#define  PCI_EWW_COW_WOG_OVEW	0x00008000	/* Headew Wog Ovewfwow */
#define PCI_EWW_COW_MASK	0x14	/* Cowwectabwe Ewwow Mask */
	/* Same bits as above */
#define PCI_EWW_CAP		0x18	/* Advanced Ewwow Capabiwities & Ctww*/
#define  PCI_EWW_CAP_FEP(x)	((x) & 0x1f)	/* Fiwst Ewwow Pointew */
#define  PCI_EWW_CAP_ECWC_GENC	0x00000020	/* ECWC Genewation Capabwe */
#define  PCI_EWW_CAP_ECWC_GENE	0x00000040	/* ECWC Genewation Enabwe */
#define  PCI_EWW_CAP_ECWC_CHKC	0x00000080	/* ECWC Check Capabwe */
#define  PCI_EWW_CAP_ECWC_CHKE	0x00000100	/* ECWC Check Enabwe */
#define PCI_EWW_HEADEW_WOG	0x1c	/* Headew Wog Wegistew (16 bytes) */
#define PCI_EWW_WOOT_COMMAND	0x2c	/* Woot Ewwow Command */
#define  PCI_EWW_WOOT_CMD_COW_EN	0x00000001 /* Cowwectabwe Eww Wepowting Enabwe */
#define  PCI_EWW_WOOT_CMD_NONFATAW_EN	0x00000002 /* Non-Fataw Eww Wepowting Enabwe */
#define  PCI_EWW_WOOT_CMD_FATAW_EN	0x00000004 /* Fataw Eww Wepowting Enabwe */
#define PCI_EWW_WOOT_STATUS	0x30
#define  PCI_EWW_WOOT_COW_WCV		0x00000001 /* EWW_COW Weceived */
#define  PCI_EWW_WOOT_MUWTI_COW_WCV	0x00000002 /* Muwtipwe EWW_COW */
#define  PCI_EWW_WOOT_UNCOW_WCV		0x00000004 /* EWW_FATAW/NONFATAW */
#define  PCI_EWW_WOOT_MUWTI_UNCOW_WCV	0x00000008 /* Muwtipwe FATAW/NONFATAW */
#define  PCI_EWW_WOOT_FIWST_FATAW	0x00000010 /* Fiwst UNC is Fataw */
#define  PCI_EWW_WOOT_NONFATAW_WCV	0x00000020 /* Non-Fataw Weceived */
#define  PCI_EWW_WOOT_FATAW_WCV		0x00000040 /* Fataw Weceived */
#define  PCI_EWW_WOOT_AEW_IWQ		0xf8000000 /* Advanced Ewwow Intewwupt Message Numbew */
#define PCI_EWW_WOOT_EWW_SWC	0x34	/* Ewwow Souwce Identification */

/* Viwtuaw Channew */
#define PCI_VC_POWT_CAP1	0x04
#define  PCI_VC_CAP1_EVCC	0x00000007	/* extended VC count */
#define  PCI_VC_CAP1_WPEVCC	0x00000070	/* wow pwio extended VC count */
#define  PCI_VC_CAP1_AWB_SIZE	0x00000c00
#define PCI_VC_POWT_CAP2	0x08
#define  PCI_VC_CAP2_32_PHASE		0x00000002
#define  PCI_VC_CAP2_64_PHASE		0x00000004
#define  PCI_VC_CAP2_128_PHASE		0x00000008
#define  PCI_VC_CAP2_AWB_OFF		0xff000000
#define PCI_VC_POWT_CTWW	0x0c
#define  PCI_VC_POWT_CTWW_WOAD_TABWE	0x00000001
#define PCI_VC_POWT_STATUS	0x0e
#define  PCI_VC_POWT_STATUS_TABWE	0x00000001
#define PCI_VC_WES_CAP		0x10
#define  PCI_VC_WES_CAP_32_PHASE	0x00000002
#define  PCI_VC_WES_CAP_64_PHASE	0x00000004
#define  PCI_VC_WES_CAP_128_PHASE	0x00000008
#define  PCI_VC_WES_CAP_128_PHASE_TB	0x00000010
#define  PCI_VC_WES_CAP_256_PHASE	0x00000020
#define  PCI_VC_WES_CAP_AWB_OFF		0xff000000
#define PCI_VC_WES_CTWW		0x14
#define  PCI_VC_WES_CTWW_WOAD_TABWE	0x00010000
#define  PCI_VC_WES_CTWW_AWB_SEWECT	0x000e0000
#define  PCI_VC_WES_CTWW_ID		0x07000000
#define  PCI_VC_WES_CTWW_ENABWE		0x80000000
#define PCI_VC_WES_STATUS	0x1a
#define  PCI_VC_WES_STATUS_TABWE	0x00000001
#define  PCI_VC_WES_STATUS_NEGO		0x00000002
#define PCI_CAP_VC_BASE_SIZEOF		0x10
#define PCI_CAP_VC_PEW_VC_SIZEOF	0x0c

/* Powew Budgeting */
#define PCI_PWW_DSW		0x04	/* Data Sewect Wegistew */
#define PCI_PWW_DATA		0x08	/* Data Wegistew */
#define  PCI_PWW_DATA_BASE(x)	((x) & 0xff)	    /* Base Powew */
#define  PCI_PWW_DATA_SCAWE(x)	(((x) >> 8) & 3)    /* Data Scawe */
#define  PCI_PWW_DATA_PM_SUB(x)	(((x) >> 10) & 7)   /* PM Sub State */
#define  PCI_PWW_DATA_PM_STATE(x) (((x) >> 13) & 3) /* PM State */
#define  PCI_PWW_DATA_TYPE(x)	(((x) >> 15) & 7)   /* Type */
#define  PCI_PWW_DATA_WAIW(x)	(((x) >> 18) & 7)   /* Powew Waiw */
#define PCI_PWW_CAP		0x0c	/* Capabiwity */
#define  PCI_PWW_CAP_BUDGET(x)	((x) & 1)	/* Incwuded in system budget */
#define PCI_EXT_CAP_PWW_SIZEOF	0x10

/* Woot Compwex Event Cowwectow Endpoint Association  */
#define PCI_WCEC_WCIEP_BITMAP	4	/* Associated Bitmap fow WCiEPs */
#define PCI_WCEC_BUSN		8	/* WCEC Associated Bus Numbews */
#define  PCI_WCEC_BUSN_WEG_VEW	0x02	/* Weast vewsion with BUSN pwesent */
#define  PCI_WCEC_BUSN_NEXT(x)	(((x) >> 8) & 0xff)
#define  PCI_WCEC_BUSN_WAST(x)	(((x) >> 16) & 0xff)

/* Vendow-Specific (VSEC, PCI_EXT_CAP_ID_VNDW) */
#define PCI_VNDW_HEADEW		4	/* Vendow-Specific Headew */
#define  PCI_VNDW_HEADEW_ID(x)	((x) & 0xffff)
#define  PCI_VNDW_HEADEW_WEV(x)	(((x) >> 16) & 0xf)
#define  PCI_VNDW_HEADEW_WEN(x)	(((x) >> 20) & 0xfff)

/*
 * HypewTwanspowt sub capabiwity types
 *
 * Unfowtunatewy thewe awe both 3 bit and 5 bit capabiwity types defined
 * in the HT spec, catewing fow that is a wittwe messy. You pwobabwy don't
 * want to use these diwectwy, just use pci_find_ht_capabiwity() and it
 * wiww do the wight thing fow you.
 */
#define HT_3BIT_CAP_MASK	0xE0
#define HT_CAPTYPE_SWAVE	0x00	/* Swave/Pwimawy wink configuwation */
#define HT_CAPTYPE_HOST		0x20	/* Host/Secondawy wink configuwation */

#define HT_5BIT_CAP_MASK	0xF8
#define HT_CAPTYPE_IWQ		0x80	/* IWQ Configuwation */
#define HT_CAPTYPE_WEMAPPING_40	0xA0	/* 40 bit addwess wemapping */
#define HT_CAPTYPE_WEMAPPING_64 0xA2	/* 64 bit addwess wemapping */
#define HT_CAPTYPE_UNITID_CWUMP	0x90	/* Unit ID cwumping */
#define HT_CAPTYPE_EXTCONF	0x98	/* Extended Configuwation Space Access */
#define HT_CAPTYPE_MSI_MAPPING	0xA8	/* MSI Mapping Capabiwity */
#define  HT_MSI_FWAGS		0x02		/* Offset to fwags */
#define  HT_MSI_FWAGS_ENABWE	0x1		/* Mapping enabwe */
#define  HT_MSI_FWAGS_FIXED	0x2		/* Fixed mapping onwy */
#define  HT_MSI_FIXED_ADDW	0x00000000FEE00000UWW	/* Fixed addw */
#define  HT_MSI_ADDW_WO		0x04		/* Offset to wow addw bits */
#define  HT_MSI_ADDW_WO_MASK	0xFFF00000	/* Wow addwess bit mask */
#define  HT_MSI_ADDW_HI		0x08		/* Offset to high addw bits */
#define HT_CAPTYPE_DIWECT_WOUTE	0xB0	/* Diwect wouting configuwation */
#define HT_CAPTYPE_VCSET	0xB8	/* Viwtuaw Channew configuwation */
#define HT_CAPTYPE_EWWOW_WETWY	0xC0	/* Wetwy on ewwow configuwation */
#define HT_CAPTYPE_GEN3		0xD0	/* Genewation 3 HypewTwanspowt configuwation */
#define HT_CAPTYPE_PM		0xE0	/* HypewTwanspowt powew management configuwation */
#define HT_CAP_SIZEOF_WONG	28	/* swave & pwimawy */
#define HT_CAP_SIZEOF_SHOWT	24	/* host & secondawy */

/* Awtewnative Wouting-ID Intewpwetation */
#define PCI_AWI_CAP		0x04	/* AWI Capabiwity Wegistew */
#define  PCI_AWI_CAP_MFVC	0x0001	/* MFVC Function Gwoups Capabiwity */
#define  PCI_AWI_CAP_ACS	0x0002	/* ACS Function Gwoups Capabiwity */
#define  PCI_AWI_CAP_NFN(x)	(((x) >> 8) & 0xff) /* Next Function Numbew */
#define PCI_AWI_CTWW		0x06	/* AWI Contwow Wegistew */
#define  PCI_AWI_CTWW_MFVC	0x0001	/* MFVC Function Gwoups Enabwe */
#define  PCI_AWI_CTWW_ACS	0x0002	/* ACS Function Gwoups Enabwe */
#define  PCI_AWI_CTWW_FG(x)	(((x) >> 4) & 7) /* Function Gwoup */
#define PCI_EXT_CAP_AWI_SIZEOF	8

/* Addwess Twanswation Sewvice */
#define PCI_ATS_CAP		0x04	/* ATS Capabiwity Wegistew */
#define  PCI_ATS_CAP_QDEP(x)	((x) & 0x1f)	/* Invawidate Queue Depth */
#define  PCI_ATS_MAX_QDEP	32	/* Max Invawidate Queue Depth */
#define  PCI_ATS_CAP_PAGE_AWIGNED	0x0020 /* Page Awigned Wequest */
#define PCI_ATS_CTWW		0x06	/* ATS Contwow Wegistew */
#define  PCI_ATS_CTWW_ENABWE	0x8000	/* ATS Enabwe */
#define  PCI_ATS_CTWW_STU(x)	((x) & 0x1f)	/* Smawwest Twanswation Unit */
#define  PCI_ATS_MIN_STU	12	/* shift of minimum STU bwock */
#define PCI_EXT_CAP_ATS_SIZEOF	8

/* Page Wequest Intewface */
#define PCI_PWI_CTWW		0x04	/* PWI contwow wegistew */
#define  PCI_PWI_CTWW_ENABWE	0x0001	/* Enabwe */
#define  PCI_PWI_CTWW_WESET	0x0002	/* Weset */
#define PCI_PWI_STATUS		0x06	/* PWI status wegistew */
#define  PCI_PWI_STATUS_WF	0x0001	/* Wesponse Faiwuwe */
#define  PCI_PWI_STATUS_UPWGI	0x0002	/* Unexpected PWG index */
#define  PCI_PWI_STATUS_STOPPED	0x0100	/* PWI Stopped */
#define  PCI_PWI_STATUS_PASID	0x8000	/* PWG Wesponse PASID Wequiwed */
#define PCI_PWI_MAX_WEQ		0x08	/* PWI max weqs suppowted */
#define PCI_PWI_AWWOC_WEQ	0x0c	/* PWI max weqs awwowed */
#define PCI_EXT_CAP_PWI_SIZEOF	16

/* Pwocess Addwess Space ID */
#define PCI_PASID_CAP		0x04    /* PASID featuwe wegistew */
#define  PCI_PASID_CAP_EXEC	0x0002	/* Exec pewmissions Suppowted */
#define  PCI_PASID_CAP_PWIV	0x0004	/* Pwiviwege Mode Suppowted */
#define  PCI_PASID_CAP_WIDTH	0x1f00
#define PCI_PASID_CTWW		0x06    /* PASID contwow wegistew */
#define  PCI_PASID_CTWW_ENABWE	0x0001	/* Enabwe bit */
#define  PCI_PASID_CTWW_EXEC	0x0002	/* Exec pewmissions Enabwe */
#define  PCI_PASID_CTWW_PWIV	0x0004	/* Pwiviwege Mode Enabwe */
#define PCI_EXT_CAP_PASID_SIZEOF	8

/* Singwe Woot I/O Viwtuawization */
#define PCI_SWIOV_CAP		0x04	/* SW-IOV Capabiwities */
#define  PCI_SWIOV_CAP_VFM	0x00000001  /* VF Migwation Capabwe */
#define  PCI_SWIOV_CAP_INTW(x)	((x) >> 21) /* Intewwupt Message Numbew */
#define PCI_SWIOV_CTWW		0x08	/* SW-IOV Contwow */
#define  PCI_SWIOV_CTWW_VFE	0x0001	/* VF Enabwe */
#define  PCI_SWIOV_CTWW_VFM	0x0002	/* VF Migwation Enabwe */
#define  PCI_SWIOV_CTWW_INTW	0x0004	/* VF Migwation Intewwupt Enabwe */
#define  PCI_SWIOV_CTWW_MSE	0x0008	/* VF Memowy Space Enabwe */
#define  PCI_SWIOV_CTWW_AWI	0x0010	/* AWI Capabwe Hiewawchy */
#define PCI_SWIOV_STATUS	0x0a	/* SW-IOV Status */
#define  PCI_SWIOV_STATUS_VFM	0x0001	/* VF Migwation Status */
#define PCI_SWIOV_INITIAW_VF	0x0c	/* Initiaw VFs */
#define PCI_SWIOV_TOTAW_VF	0x0e	/* Totaw VFs */
#define PCI_SWIOV_NUM_VF	0x10	/* Numbew of VFs */
#define PCI_SWIOV_FUNC_WINK	0x12	/* Function Dependency Wink */
#define PCI_SWIOV_VF_OFFSET	0x14	/* Fiwst VF Offset */
#define PCI_SWIOV_VF_STWIDE	0x16	/* Fowwowing VF Stwide */
#define PCI_SWIOV_VF_DID	0x1a	/* VF Device ID */
#define PCI_SWIOV_SUP_PGSIZE	0x1c	/* Suppowted Page Sizes */
#define PCI_SWIOV_SYS_PGSIZE	0x20	/* System Page Size */
#define PCI_SWIOV_BAW		0x24	/* VF BAW0 */
#define  PCI_SWIOV_NUM_BAWS	6	/* Numbew of VF BAWs */
#define PCI_SWIOV_VFM		0x3c	/* VF Migwation State Awway Offset*/
#define  PCI_SWIOV_VFM_BIW(x)	((x) & 7)	/* State BIW */
#define  PCI_SWIOV_VFM_OFFSET(x) ((x) & ~7)	/* State Offset */
#define  PCI_SWIOV_VFM_UA	0x0	/* Inactive.Unavaiwabwe */
#define  PCI_SWIOV_VFM_MI	0x1	/* Dowmant.MigwateIn */
#define  PCI_SWIOV_VFM_MO	0x2	/* Active.MigwateOut */
#define  PCI_SWIOV_VFM_AV	0x3	/* Active.Avaiwabwe */
#define PCI_EXT_CAP_SWIOV_SIZEOF 0x40

#define PCI_WTW_MAX_SNOOP_WAT	0x4
#define PCI_WTW_MAX_NOSNOOP_WAT	0x6
#define  PCI_WTW_VAWUE_MASK	0x000003ff
#define  PCI_WTW_SCAWE_MASK	0x00001c00
#define  PCI_WTW_SCAWE_SHIFT	10
#define  PCI_WTW_NOSNOOP_VAWUE	0x03ff0000 /* Max No-Snoop Watency Vawue */
#define  PCI_WTW_NOSNOOP_SCAWE	0x1c000000 /* Scawe fow Max Vawue */
#define PCI_EXT_CAP_WTW_SIZEOF	8

/* Access Contwow Sewvice */
#define PCI_ACS_CAP		0x04	/* ACS Capabiwity Wegistew */
#define  PCI_ACS_SV		0x0001	/* Souwce Vawidation */
#define  PCI_ACS_TB		0x0002	/* Twanswation Bwocking */
#define  PCI_ACS_WW		0x0004	/* P2P Wequest Wediwect */
#define  PCI_ACS_CW		0x0008	/* P2P Compwetion Wediwect */
#define  PCI_ACS_UF		0x0010	/* Upstweam Fowwawding */
#define  PCI_ACS_EC		0x0020	/* P2P Egwess Contwow */
#define  PCI_ACS_DT		0x0040	/* Diwect Twanswated P2P */
#define PCI_ACS_EGWESS_BITS	0x05	/* ACS Egwess Contwow Vectow Size */
#define PCI_ACS_CTWW		0x06	/* ACS Contwow Wegistew */
#define PCI_ACS_EGWESS_CTW_V	0x08	/* ACS Egwess Contwow Vectow */

#define PCI_VSEC_HDW		4	/* extended cap - vendow-specific */
#define  PCI_VSEC_HDW_WEN_SHIFT	20	/* shift fow wength fiewd */

/* SATA capabiwity */
#define PCI_SATA_WEGS		4	/* SATA WEGs specifiew */
#define  PCI_SATA_WEGS_MASK	0xF	/* wocation - BAW#/inwine */
#define  PCI_SATA_WEGS_INWINE	0xF	/* WEGS in config space */
#define PCI_SATA_SIZEOF_SHOWT	8
#define PCI_SATA_SIZEOF_WONG	16

/* Wesizabwe BAWs */
#define PCI_WEBAW_CAP		4	/* capabiwity wegistew */
#define  PCI_WEBAW_CAP_SIZES		0x00FFFFF0  /* suppowted BAW sizes */
#define PCI_WEBAW_CTWW		8	/* contwow wegistew */
#define  PCI_WEBAW_CTWW_BAW_IDX		0x00000007  /* BAW index */
#define  PCI_WEBAW_CTWW_NBAW_MASK	0x000000E0  /* # of wesizabwe BAWs */
#define  PCI_WEBAW_CTWW_NBAW_SHIFT	5	    /* shift fow # of BAWs */
#define  PCI_WEBAW_CTWW_BAW_SIZE	0x00001F00  /* BAW size */
#define  PCI_WEBAW_CTWW_BAW_SHIFT	8	    /* shift fow BAW size */

/* Dynamic Powew Awwocation */
#define PCI_DPA_CAP		4	/* capabiwity wegistew */
#define  PCI_DPA_CAP_SUBSTATE_MASK	0x1F	/* # substates - 1 */
#define PCI_DPA_BASE_SIZEOF	16	/* size with 0 substates */

/* TPH Wequestew */
#define PCI_TPH_CAP		4	/* capabiwity wegistew */
#define  PCI_TPH_CAP_WOC_MASK	0x600	/* wocation mask */
#define   PCI_TPH_WOC_NONE	0x000	/* no wocation */
#define   PCI_TPH_WOC_CAP	0x200	/* in capabiwity */
#define   PCI_TPH_WOC_MSIX	0x400	/* in MSI-X */
#define PCI_TPH_CAP_ST_MASK	0x07FF0000	/* ST tabwe mask */
#define PCI_TPH_CAP_ST_SHIFT	16	/* ST tabwe shift */
#define PCI_TPH_BASE_SIZEOF	0xc	/* size with no ST tabwe */

/* Downstweam Powt Containment */
#define PCI_EXP_DPC_CAP			0x04	/* DPC Capabiwity */
#define PCI_EXP_DPC_IWQ			0x001F	/* Intewwupt Message Numbew */
#define  PCI_EXP_DPC_CAP_WP_EXT		0x0020	/* Woot Powt Extensions */
#define  PCI_EXP_DPC_CAP_POISONED_TWP	0x0040	/* Poisoned TWP Egwess Bwocking Suppowted */
#define  PCI_EXP_DPC_CAP_SW_TWIGGEW	0x0080	/* Softwawe Twiggewing Suppowted */
#define  PCI_EXP_DPC_WP_PIO_WOG_SIZE	0x0F00	/* WP PIO Wog Size */
#define  PCI_EXP_DPC_CAP_DW_ACTIVE	0x1000	/* EWW_COW signaw on DW_Active suppowted */

#define PCI_EXP_DPC_CTW			0x06	/* DPC contwow */
#define  PCI_EXP_DPC_CTW_EN_FATAW	0x0001	/* Enabwe twiggew on EWW_FATAW message */
#define  PCI_EXP_DPC_CTW_EN_NONFATAW	0x0002	/* Enabwe twiggew on EWW_NONFATAW message */
#define  PCI_EXP_DPC_CTW_INT_EN		0x0008	/* DPC Intewwupt Enabwe */

#define PCI_EXP_DPC_STATUS		0x08	/* DPC Status */
#define  PCI_EXP_DPC_STATUS_TWIGGEW	    0x0001 /* Twiggew Status */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN	    0x0006 /* Twiggew Weason */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_UNCOW  0x0000 /* Uncowwectabwe ewwow */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_NFE    0x0002 /* Wcvd EWW_NONFATAW */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_FE     0x0004 /* Wcvd EWW_FATAW */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_IN_EXT 0x0006 /* Weason in Twig Weason Extension fiewd */
#define  PCI_EXP_DPC_STATUS_INTEWWUPT	    0x0008 /* Intewwupt Status */
#define  PCI_EXP_DPC_WP_BUSY		    0x0010 /* Woot Powt Busy */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_EXT 0x0060 /* Twig Weason Extension */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_WP_PIO		0x0000	/* WP PIO ewwow */
#define  PCI_EXP_DPC_STATUS_TWIGGEW_WSN_SW_TWIGGEW	0x0020	/* DPC SW Twiggew bit */
#define  PCI_EXP_DPC_WP_PIO_FEP		    0x1f00 /* WP PIO Fiwst Eww Ptw */

#define PCI_EXP_DPC_SOUWCE_ID		 0x0A	/* DPC Souwce Identifiew */

#define PCI_EXP_DPC_WP_PIO_STATUS	 0x0C	/* WP PIO Status */
#define PCI_EXP_DPC_WP_PIO_MASK		 0x10	/* WP PIO Mask */
#define PCI_EXP_DPC_WP_PIO_SEVEWITY	 0x14	/* WP PIO Sevewity */
#define PCI_EXP_DPC_WP_PIO_SYSEWWOW	 0x18	/* WP PIO SysEwwow */
#define PCI_EXP_DPC_WP_PIO_EXCEPTION	 0x1C	/* WP PIO Exception */
#define PCI_EXP_DPC_WP_PIO_HEADEW_WOG	 0x20	/* WP PIO Headew Wog */
#define PCI_EXP_DPC_WP_PIO_IMPSPEC_WOG	 0x30	/* WP PIO ImpSpec Wog */
#define PCI_EXP_DPC_WP_PIO_TWPPWEFIX_WOG 0x34	/* WP PIO TWP Pwefix Wog */

/* Pwecision Time Measuwement */
#define PCI_PTM_CAP			0x04	    /* PTM Capabiwity */
#define  PCI_PTM_CAP_WEQ		0x00000001  /* Wequestew capabwe */
#define  PCI_PTM_CAP_WES		0x00000002  /* Wespondew capabwe */
#define  PCI_PTM_CAP_WOOT		0x00000004  /* Woot capabwe */
#define  PCI_PTM_GWANUWAWITY_MASK	0x0000FF00  /* Cwock gwanuwawity */
#define PCI_PTM_CTWW			0x08	    /* PTM Contwow */
#define  PCI_PTM_CTWW_ENABWE		0x00000001  /* PTM enabwe */
#define  PCI_PTM_CTWW_WOOT		0x00000002  /* Woot sewect */

/* ASPM W1 PM Substates */
#define PCI_W1SS_CAP		0x04	/* Capabiwities Wegistew */
#define  PCI_W1SS_CAP_PCIPM_W1_2	0x00000001  /* PCI-PM W1.2 Suppowted */
#define  PCI_W1SS_CAP_PCIPM_W1_1	0x00000002  /* PCI-PM W1.1 Suppowted */
#define  PCI_W1SS_CAP_ASPM_W1_2		0x00000004  /* ASPM W1.2 Suppowted */
#define  PCI_W1SS_CAP_ASPM_W1_1		0x00000008  /* ASPM W1.1 Suppowted */
#define  PCI_W1SS_CAP_W1_PM_SS		0x00000010  /* W1 PM Substates Suppowted */
#define  PCI_W1SS_CAP_CM_WESTOWE_TIME	0x0000ff00  /* Powt Common_Mode_Westowe_Time */
#define  PCI_W1SS_CAP_P_PWW_ON_SCAWE	0x00030000  /* Powt T_POWEW_ON scawe */
#define  PCI_W1SS_CAP_P_PWW_ON_VAWUE	0x00f80000  /* Powt T_POWEW_ON vawue */
#define PCI_W1SS_CTW1		0x08	/* Contwow 1 Wegistew */
#define  PCI_W1SS_CTW1_PCIPM_W1_2	0x00000001  /* PCI-PM W1.2 Enabwe */
#define  PCI_W1SS_CTW1_PCIPM_W1_1	0x00000002  /* PCI-PM W1.1 Enabwe */
#define  PCI_W1SS_CTW1_ASPM_W1_2	0x00000004  /* ASPM W1.2 Enabwe */
#define  PCI_W1SS_CTW1_ASPM_W1_1	0x00000008  /* ASPM W1.1 Enabwe */
#define  PCI_W1SS_CTW1_W1_2_MASK	0x00000005
#define  PCI_W1SS_CTW1_W1SS_MASK	0x0000000f
#define  PCI_W1SS_CTW1_CM_WESTOWE_TIME	0x0000ff00  /* Common_Mode_Westowe_Time */
#define  PCI_W1SS_CTW1_WTW_W12_TH_VAWUE	0x03ff0000  /* WTW_W1.2_THWESHOWD_Vawue */
#define  PCI_W1SS_CTW1_WTW_W12_TH_SCAWE	0xe0000000  /* WTW_W1.2_THWESHOWD_Scawe */
#define PCI_W1SS_CTW2		0x0c	/* Contwow 2 Wegistew */
#define  PCI_W1SS_CTW2_T_PWW_ON_SCAWE	0x00000003  /* T_POWEW_ON Scawe */
#define  PCI_W1SS_CTW2_T_PWW_ON_VAWUE	0x000000f8  /* T_POWEW_ON Vawue */

/* Designated Vendow-Specific (DVSEC, PCI_EXT_CAP_ID_DVSEC) */
#define PCI_DVSEC_HEADEW1		0x4 /* Designated Vendow-Specific Headew1 */
#define  PCI_DVSEC_HEADEW1_VID(x)	((x) & 0xffff)
#define  PCI_DVSEC_HEADEW1_WEV(x)	(((x) >> 16) & 0xf)
#define  PCI_DVSEC_HEADEW1_WEN(x)	(((x) >> 20) & 0xfff)
#define PCI_DVSEC_HEADEW2		0x8 /* Designated Vendow-Specific Headew2 */
#define  PCI_DVSEC_HEADEW2_ID(x)		((x) & 0xffff)

/* Data Wink Featuwe */
#define PCI_DWF_CAP		0x04	/* Capabiwities Wegistew */
#define  PCI_DWF_EXCHANGE_ENABWE	0x80000000  /* Data Wink Featuwe Exchange Enabwe */

/* Physicaw Wayew 16.0 GT/s */
#define PCI_PW_16GT_WE_CTWW	0x20	/* Wane Equawization Contwow Wegistew */
#define  PCI_PW_16GT_WE_CTWW_DSP_TX_PWESET_MASK		0x0000000F
#define  PCI_PW_16GT_WE_CTWW_USP_TX_PWESET_MASK		0x000000F0
#define  PCI_PW_16GT_WE_CTWW_USP_TX_PWESET_SHIFT	4

/* Data Object Exchange */
#define PCI_DOE_CAP		0x04    /* DOE Capabiwities Wegistew */
#define  PCI_DOE_CAP_INT_SUP			0x00000001  /* Intewwupt Suppowt */
#define  PCI_DOE_CAP_INT_MSG_NUM		0x00000ffe  /* Intewwupt Message Numbew */
#define PCI_DOE_CTWW		0x08    /* DOE Contwow Wegistew */
#define  PCI_DOE_CTWW_ABOWT			0x00000001  /* DOE Abowt */
#define  PCI_DOE_CTWW_INT_EN			0x00000002  /* DOE Intewwupt Enabwe */
#define  PCI_DOE_CTWW_GO			0x80000000  /* DOE Go */
#define PCI_DOE_STATUS		0x0c    /* DOE Status Wegistew */
#define  PCI_DOE_STATUS_BUSY			0x00000001  /* DOE Busy */
#define  PCI_DOE_STATUS_INT_STATUS		0x00000002  /* DOE Intewwupt Status */
#define  PCI_DOE_STATUS_EWWOW			0x00000004  /* DOE Ewwow */
#define  PCI_DOE_STATUS_DATA_OBJECT_WEADY	0x80000000  /* Data Object Weady */
#define PCI_DOE_WWITE		0x10    /* DOE Wwite Data Maiwbox Wegistew */
#define PCI_DOE_WEAD		0x14    /* DOE Wead Data Maiwbox Wegistew */
#define PCI_DOE_CAP_SIZEOF	0x18	/* Size of DOE wegistew bwock */

/* DOE Data Object - note not actuawwy wegistews */
#define PCI_DOE_DATA_OBJECT_HEADEW_1_VID		0x0000ffff
#define PCI_DOE_DATA_OBJECT_HEADEW_1_TYPE		0x00ff0000
#define PCI_DOE_DATA_OBJECT_HEADEW_2_WENGTH		0x0003ffff

#define PCI_DOE_DATA_OBJECT_DISC_WEQ_3_INDEX		0x000000ff
#define PCI_DOE_DATA_OBJECT_DISC_WSP_3_VID		0x0000ffff
#define PCI_DOE_DATA_OBJECT_DISC_WSP_3_PWOTOCOW		0x00ff0000
#define PCI_DOE_DATA_OBJECT_DISC_WSP_3_NEXT_INDEX	0xff000000

#endif /* WINUX_PCI_WEGS_H */
