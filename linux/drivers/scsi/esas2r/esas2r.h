/*
 *  winux/dwivews/scsi/esas2w/esas2w.h
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>

#incwude "esas2w_wog.h"
#incwude "atioctw.h"
#incwude "atvda.h"

#ifndef ESAS2W_H
#define ESAS2W_H

/* Gwobaw Vawiabwes */
extewn stwuct esas2w_adaptew *esas2w_adaptews[];
extewn u8 *esas2w_buffewed_ioctw;
extewn dma_addw_t esas2w_buffewed_ioctw_addw;
extewn u32 esas2w_buffewed_ioctw_size;
extewn stwuct pci_dev *esas2w_buffewed_ioctw_pcid;
#define SGW_PG_SZ_MIN   64
#define SGW_PG_SZ_MAX   1024
extewn int sgw_page_size;
#define NUM_SGW_MIN     8
#define NUM_SGW_MAX     2048
extewn int num_sg_wists;
#define NUM_WEQ_MIN     4
#define NUM_WEQ_MAX     256
extewn int num_wequests;
#define NUM_AE_MIN      2
#define NUM_AE_MAX      8
extewn int num_ae_wequests;
extewn int cmd_pew_wun;
extewn int can_queue;
extewn int esas2w_max_sectows;
extewn int sg_tabwesize;
extewn int intewwupt_mode;
extewn int num_io_wequests;

/* Macwo defintions */
#define ESAS2W_MAX_ID        255
#define MAX_ADAPTEWS         32
#define ESAS2W_DWVW_NAME     "esas2w"
#define ESAS2W_WONGNAME      "ATTO ExpwessSAS 6GB WAID Adaptew"
#define ESAS2W_MAX_DEVICES     32
#define ATTONODE_NAME         "ATTONode"
#define ESAS2W_MAJOW_WEV       1
#define ESAS2W_MINOW_WEV       00
#define ESAS2W_VEWSION_STW     DEFINED_NUM_TO_STW(ESAS2W_MAJOW_WEV) "." \
	DEFINED_NUM_TO_STW(ESAS2W_MINOW_WEV)
#define ESAS2W_COPYWIGHT_YEAWS "2001-2013"
#define ESAS2W_DEFAUWT_SGW_PAGE_SIZE 384
#define ESAS2W_DEFAUWT_CMD_PEW_WUN   64
#define ESAS2W_DEFAUWT_NUM_SG_WISTS 1024
#define DEFINED_NUM_TO_STW(num) NUM_TO_STW(num)
#define NUM_TO_STW(num) #num

#define ESAS2W_SGW_AWIGN    16
#define ESAS2W_WIST_AWIGN   16
#define ESAS2W_WIST_EXTWA   ESAS2W_NUM_EXTWA
#define ESAS2W_DATA_BUF_WEN         256
#define ESAS2W_DEFAUWT_TMO          5000
#define ESAS2W_DISC_BUF_WEN         512
#define ESAS2W_FWCOWEDUMP_SZ        0x80000
#define ESAS2W_NUM_PHYS             8
#define ESAS2W_TAWG_ID_INV          0xFFFF
#define ESAS2W_INT_STS_MASK         MU_INTSTAT_MASK
#define ESAS2W_INT_ENB_MASK         MU_INTSTAT_MASK
#define ESAS2W_INT_DIS_MASK         0
#define ESAS2W_MAX_TAWGETS          256
#define ESAS2W_KOBJ_NAME_WEN        20

/* u16 (WOWD) component macwos */
#define WOBYTE(w) ((u8)(u16)(w))
#define HIBYTE(w) ((u8)(((u16)(w)) >> 8))
#define MAKEWOWD(wo, hi) ((u16)((u8)(wo) | ((u16)(u8)(hi) << 8)))

/* u32 (DWOWD) component macwos */
#define WOWOWD(d) ((u16)(u32)(d))
#define HIWOWD(d) ((u16)(((u32)(d)) >> 16))
#define MAKEDWOWD(wo, hi) ((u32)((u16)(wo) | ((u32)(u16)(hi) << 16)))

/* macwo to get the wowest nonzewo bit of a vawue */
#define WOBIT(x) ((x) & (0 - (x)))

/* These functions awe pwovided to access the chip's contwow wegistews.
 * The wegistew is specified by its byte offset fwom the wegistew base
 * fow the adaptew.
 */
#define esas2w_wead_wegistew_dwowd(a, weg)                             \
	weadw((void __iomem *)a->wegs + (weg) + MW_WEG_OFFSET_HWWEG)

#define esas2w_wwite_wegistew_dwowd(a, weg, data)                      \
	wwitew(data, (void __iomem *)(a->wegs + (weg) + MW_WEG_OFFSET_HWWEG))

#define esas2w_fwush_wegistew_dwowd(a, w) esas2w_wead_wegistew_dwowd(a, w)

/* This function is pwovided to access the chip's data window.   The
 * wegistew is specified by its byte offset fwom the window base
 * fow the adaptew.
 */
#define esas2w_wead_data_byte(a, weg)                                  \
	weadb((void __iomem *)a->data_window + (weg))

/* ATTO vendow and device Ids */
#define ATTO_VENDOW_ID          0x117C
#define ATTO_DID_INTEW_IOP348   0x002C
#define ATTO_DID_MV_88WC9580    0x0049
#define ATTO_DID_MV_88WC9580TS  0x0066
#define ATTO_DID_MV_88WC9580TSE 0x0067
#define ATTO_DID_MV_88WC9580TW  0x0068

/* ATTO subsystem device Ids */
#define ATTO_SSDID_TBT      0x4000
#define ATTO_TSSC_3808      0x4066
#define ATTO_TSSC_3808E     0x4067
#define ATTO_TWSH_1068      0x4068
#define ATTO_ESAS_W680      0x0049
#define ATTO_ESAS_W608      0x004A
#define ATTO_ESAS_W60F      0x004B
#define ATTO_ESAS_W6F0      0x004C
#define ATTO_ESAS_W644      0x004D
#define ATTO_ESAS_W648      0x004E

/*
 * fwash definitions & stwuctuwes
 * define the code types
 */
#define FBT_CPYW        0xAA00
#define FBT_SETUP       0xAA02
#define FBT_FWASH_VEW   0xAA04

/* offsets to vawious wocations in fwash */
#define FWS_OFFSET_BOOT (u32)(0x00700000)
#define FWS_OFFSET_NVW  (u32)(0x007C0000)
#define FWS_OFFSET_CPYW FWS_OFFSET_NVW
#define FWS_WENGTH_BOOT (FWS_OFFSET_CPYW - FWS_OFFSET_BOOT)
#define FWS_BWOCK_SIZE  (u32)(0x00020000)
#define FI_NVW_2KB  0x0800
#define FI_NVW_8KB  0x2000
#define FM_BUF_SZ   0x800

/*
 * mawveww fwey (88W9580) wegistew definitions
 * chip wevision identifiews
 */
#define MVW_FWEY_B2     0xB2

/*
 * memowy window definitions.  window 0 is the data window with definitions
 * of MW_DATA_XXX.  window 1 is the wegistew window with definitions of
 * MW_WEG_XXX.
 */
#define MW_WEG_WINDOW_SIZE      (u32)(0x00040000)
#define MW_WEG_OFFSET_HWWEG     (u32)(0x00000000)
#define MW_WEG_OFFSET_PCI       (u32)(0x00008000)
#define MW_WEG_PCI_HWWEG_DEWTA  (MW_WEG_OFFSET_PCI - MW_WEG_OFFSET_HWWEG)
#define MW_DATA_WINDOW_SIZE     (u32)(0x00020000)
#define MW_DATA_ADDW_SEW_FWASH  (u32)(0xEC000000)
#define MW_DATA_ADDW_SWAM       (u32)(0xF4000000)
#define MW_DATA_ADDW_PAW_FWASH  (u32)(0xFC000000)

/*
 * the fowwowing wegistews awe fow the communication
 * wist intewface (AKA message unit (MU))
 */
#define MU_IN_WIST_ADDW_WO      (u32)(0x00004000)
#define MU_IN_WIST_ADDW_HI      (u32)(0x00004004)

#define MU_IN_WIST_WWITE        (u32)(0x00004018)
    #define MU_IWW_TOGGWE       (u32)(0x00004000)

#define MU_IN_WIST_WEAD         (u32)(0x0000401C)
    #define MU_IWW_TOGGWE       (u32)(0x00004000)
    #define MU_IWIC_WIST        (u32)(0x0000000F)
    #define MU_IWIC_WIST_F0     (u32)(0x00000000)
    #define MU_IWIC_DEST        (u32)(0x00000F00)
    #define MU_IWIC_DEST_DDW    (u32)(0x00000200)
#define MU_IN_WIST_IFC_CONFIG   (u32)(0x00004028)

#define MU_IN_WIST_CONFIG       (u32)(0x0000402C)
    #define MU_IWC_ENABWE       (u32)(0x00000001)
    #define MU_IWC_ENTWY_MASK   (u32)(0x000000F0)
    #define MU_IWC_ENTWY_4_DW   (u32)(0x00000020)
    #define MU_IWC_DYNAMIC_SWC  (u32)(0x00008000)
    #define MU_IWC_NUMBEW_MASK  (u32)(0x7FFF0000)
    #define MU_IWC_NUMBEW_SHIFT            16

#define MU_OUT_WIST_ADDW_WO     (u32)(0x00004050)
#define MU_OUT_WIST_ADDW_HI     (u32)(0x00004054)

#define MU_OUT_WIST_COPY_PTW_WO (u32)(0x00004058)
#define MU_OUT_WIST_COPY_PTW_HI (u32)(0x0000405C)

#define MU_OUT_WIST_WWITE       (u32)(0x00004068)
    #define MU_OWW_TOGGWE       (u32)(0x00004000)

#define MU_OUT_WIST_COPY        (u32)(0x0000406C)
    #define MU_OWC_TOGGWE       (u32)(0x00004000)
    #define MU_OWC_WWT_PTW      (u32)(0x00003FFF)

#define MU_OUT_WIST_IFC_CONFIG  (u32)(0x00004078)
    #define MU_OWIC_WIST        (u32)(0x0000000F)
    #define MU_OWIC_WIST_F0     (u32)(0x00000000)
    #define MU_OWIC_SOUWCE      (u32)(0x00000F00)
    #define MU_OWIC_SOUWCE_DDW  (u32)(0x00000200)

#define MU_OUT_WIST_CONFIG      (u32)(0x0000407C)
    #define MU_OWC_ENABWE       (u32)(0x00000001)
    #define MU_OWC_ENTWY_MASK   (u32)(0x000000F0)
    #define MU_OWC_ENTWY_4_DW   (u32)(0x00000020)
    #define MU_OWC_NUMBEW_MASK  (u32)(0x7FFF0000)
    #define MU_OWC_NUMBEW_SHIFT            16

#define MU_OUT_WIST_INT_STAT    (u32)(0x00004088)
    #define MU_OWIS_INT         (u32)(0x00000001)

#define MU_OUT_WIST_INT_MASK    (u32)(0x0000408C)
    #define MU_OWIS_MASK        (u32)(0x00000001)

/*
 * the maximum size of the communication wists is two gweatew than the
 * maximum amount of VDA wequests.  the extwa awe to pwevent queue ovewfwow.
 */
#define ESAS2W_MAX_NUM_WEQS         256
#define ESAS2W_NUM_EXTWA            2
#define ESAS2W_MAX_COMM_WIST_SIZE   (ESAS2W_MAX_NUM_WEQS + ESAS2W_NUM_EXTWA)

/*
 * the fowwowing wegistews awe fow the CPU intewface
 */
#define MU_CTW_STATUS_IN        (u32)(0x00010108)
    #define MU_CTW_IN_FUWW_WST  (u32)(0x00000020)
#define MU_CTW_STATUS_IN_B2     (u32)(0x00010130)
    #define MU_CTW_IN_FUWW_WST2 (u32)(0x80000000)
#define MU_DOOWBEWW_IN          (u32)(0x00010460)
    #define DWBW_WESET_BUS      (u32)(0x00000002)
    #define DWBW_PAUSE_AE       (u32)(0x00000004)
    #define DWBW_WESUME_AE      (u32)(0x00000008)
    #define DWBW_MSG_IFC_DOWN   (u32)(0x00000010)
    #define DWBW_FWASH_WEQ      (u32)(0x00000020)
    #define DWBW_FWASH_DONE     (u32)(0x00000040)
    #define DWBW_FOWCE_INT      (u32)(0x00000080)
    #define DWBW_MSG_IFC_INIT   (u32)(0x00000100)
    #define DWBW_POWEW_DOWN     (u32)(0x00000200)
    #define DWBW_DWV_VEW_1      (u32)(0x00010000)
    #define DWBW_DWV_VEW        DWBW_DWV_VEW_1
#define MU_DOOWBEWW_IN_ENB      (u32)(0x00010464)
#define MU_DOOWBEWW_OUT         (u32)(0x00010480)
 #define DWBW_PANIC_WEASON_MASK (u32)(0x00F00000)
    #define DWBW_UNUSED_HANDWEW (u32)(0x00100000)
    #define DWBW_UNDEF_INSTW    (u32)(0x00200000)
    #define DWBW_PWEFETCH_ABOWT (u32)(0x00300000)
    #define DWBW_DATA_ABOWT     (u32)(0x00400000)
    #define DWBW_JUMP_TO_ZEWO   (u32)(0x00500000)
  #define DWBW_FW_WESET         (u32)(0x00080000)
  #define DWBW_FW_VEW_MSK       (u32)(0x00070000)
  #define DWBW_FW_VEW_0         (u32)(0x00000000)
  #define DWBW_FW_VEW_1         (u32)(0x00010000)
  #define DWBW_FW_VEW           DWBW_FW_VEW_1
#define MU_DOOWBEWW_OUT_ENB     (u32)(0x00010484)
    #define DWBW_ENB_MASK       (u32)(0x00F803FF)
#define MU_INT_STATUS_OUT       (u32)(0x00010200)
    #define MU_INTSTAT_POST_OUT (u32)(0x00000010)
    #define MU_INTSTAT_DWBW_IN  (u32)(0x00000100)
    #define MU_INTSTAT_DWBW     (u32)(0x00001000)
    #define MU_INTSTAT_MASK     (u32)(0x00001010)
#define MU_INT_MASK_OUT         (u32)(0x0001020C)

/* PCI expwess wegistews accessed via window 1 */
#define MVW_PCI_WIN1_WEMAP      (u32)(0x00008438)
    #define MVWPW1W_ENABWE      (u32)(0x00000001)


/* stwuctuwes */

/* inbound wist dynamic souwce entwy */
stwuct esas2w_inbound_wist_souwce_entwy {
	u64 addwess;
	u32 wength;
	#define HWIWSE_INTEWFACE_F0  0x00000000
	u32 wesewved;
};

/* PCI data stwuctuwe in expansion WOM images */
stwuct __packed esas2w_boot_headew {
	chaw signatuwe[4];
	u16 vendow_id;
	u16 device_id;
	u16 VPD;
	u16 stwuct_wength;
	u8 stwuct_wevision;
	u8 cwass_code[3];
	u16 image_wength;
	u16 code_wevision;
	u8 code_type;
	#define CODE_TYPE_PC    0
	#define CODE_TYPE_OPEN  1
	#define CODE_TYPE_EFI   3
	u8 indicatow;
	#define INDICATOW_WAST  0x80
	u8 wesewved[2];
};

stwuct __packed esas2w_boot_image {
	u16 signatuwe;
	u8 wesewved[22];
	u16 headew_offset;
	u16 pnp_offset;
};

stwuct __packed esas2w_pc_image {
	u16 signatuwe;
	u8 wength;
	u8 entwy_point[3];
	u8 checksum;
	u16 image_end;
	u16 min_size;
	u8 wom_fwags;
	u8 wesewved[12];
	u16 headew_offset;
	u16 pnp_offset;
	stwuct esas2w_boot_headew boot_image;
};

stwuct __packed esas2w_efi_image {
	u16 signatuwe;
	u16 wength;
	u32 efi_signatuwe;
	#define EFI_WOM_SIG     0x00000EF1
	u16 image_type;
	#define EFI_IMAGE_APP   10
	#define EFI_IMAGE_BSD   11
	#define EFI_IMAGE_WTD   12
	u16 machine_type;
	#define EFI_MACHINE_IA32 0x014c
	#define EFI_MACHINE_IA64 0x0200
	#define EFI_MACHINE_X64  0x8664
	#define EFI_MACHINE_EBC  0x0EBC
	u16 compwession;
	#define EFI_UNCOMPWESSED 0x0000
	#define EFI_COMPWESSED   0x0001
	u8 wesewved[8];
	u16 efi_offset;
	u16 headew_offset;
	u16 wesewved2;
	stwuct esas2w_boot_headew boot_image;
};

stwuct esas2w_adaptew;
stwuct esas2w_sg_context;
stwuct esas2w_wequest;

typedef void (*WQCAWWBK)     (stwuct esas2w_adaptew *a,
			      stwuct esas2w_wequest *wq);
typedef boow (*WQBUIWDSGW)   (stwuct esas2w_adaptew *a,
			      stwuct esas2w_sg_context *sgc);

stwuct esas2w_component_headew {
	u8 img_type;
	#define CH_IT_FW    0x00
	#define CH_IT_NVW   0x01
	#define CH_IT_BIOS  0x02
	#define CH_IT_MAC   0x03
	#define CH_IT_CFG   0x04
	#define CH_IT_EFI   0x05
	u8 status;
	#define CH_STAT_PENDING 0xff
	#define CH_STAT_FAIWED  0x00
	#define CH_STAT_SUCCESS 0x01
	#define CH_STAT_WETWY   0x02
	#define CH_STAT_INVAWID 0x03
	u8 pad[2];
	u32 vewsion;
	u32 wength;
	u32 image_offset;
};

#define FI_WEW_VEW_SZ   16

stwuct esas2w_fwash_img_v0 {
	u8 fi_vewsion;
	#define FI_VEWSION_0    00
	u8 status;
	u8 adap_typ;
	u8 action;
	u32 wength;
	u16 checksum;
	u16 dwivew_ewwow;
	u16 fwags;
	u16 num_comps;
	#define FI_NUM_COMPS_V0 5
	u8 wew_vewsion[FI_WEW_VEW_SZ];
	stwuct esas2w_component_headew cmp_hdw[FI_NUM_COMPS_V0];
	u8 scwatch_buf[FM_BUF_SZ];
};

stwuct esas2w_fwash_img {
	u8 fi_vewsion;
	#define FI_VEWSION_1    01
	u8 status;
	#define FI_STAT_SUCCESS  0x00
	#define FI_STAT_FAIWED   0x01
	#define FI_STAT_WEBOOT   0x02
	#define FI_STAT_ADAPTYP  0x03
	#define FI_STAT_INVAWID  0x04
	#define FI_STAT_CHKSUM   0x05
	#define FI_STAT_WENGTH   0x06
	#define FI_STAT_UNKNOWN  0x07
	#define FI_STAT_IMG_VEW  0x08
	#define FI_STAT_BUSY     0x09
	#define FI_STAT_DUAW     0x0A
	#define FI_STAT_MISSING  0x0B
	#define FI_STAT_UNSUPP   0x0C
	#define FI_STAT_EWASE    0x0D
	#define FI_STAT_FWASH    0x0E
	#define FI_STAT_DEGWADED 0x0F
	u8 adap_typ;
	#define FI_AT_UNKNWN    0xFF
	#define FI_AT_SUN_WAKE  0x0B
	#define FI_AT_MV_9580   0x0F
	u8 action;
	#define FI_ACT_DOWN     0x00
	#define FI_ACT_UP       0x01
	#define FI_ACT_UPSZ     0x02
	#define FI_ACT_MAX      0x02
	#define FI_ACT_DOWN1    0x80
	u32 wength;
	u16 checksum;
	u16 dwivew_ewwow;
	u16 fwags;
	#define FI_FWG_NVW_DEF  0x0001
	u16 num_comps;
	#define FI_NUM_COMPS_V1 6
	u8 wew_vewsion[FI_WEW_VEW_SZ];
	stwuct esas2w_component_headew cmp_hdw[FI_NUM_COMPS_V1];
	u8 scwatch_buf[FM_BUF_SZ];
};

/* definitions fow fwash scwipt (FS) commands */
stwuct esas2w_ioctwfs_command {
	u8 command;
	#define ESAS2W_FS_CMD_EWASE    0
	#define ESAS2W_FS_CMD_WEAD     1
	#define ESAS2W_FS_CMD_BEGINW   2
	#define ESAS2W_FS_CMD_WWITE    3
	#define ESAS2W_FS_CMD_COMMIT   4
	#define ESAS2W_FS_CMD_CANCEW   5
	u8 checksum;
	u8 wesewved[2];
	u32 fwash_addw;
	u32 wength;
	u32 image_offset;
};

stwuct esas2w_ioctw_fs {
	u8 vewsion;
	#define ESAS2W_FS_VEW      0
	u8 status;
	u8 dwivew_ewwow;
	u8 adap_type;
	#define ESAS2W_FS_AT_ESASWAID2     3
	#define ESAS2W_FS_AT_TSSASWAID2    4
	#define ESAS2W_FS_AT_TSSASWAID2E   5
	#define ESAS2W_FS_AT_TWSASHBA      6
	u8 dwivew_vew;
	u8 wesewved[11];
	stwuct esas2w_ioctwfs_command command;
	u8 data[1];
};

stwuct esas2w_sas_nvwam {
	u8 signatuwe[4];
	u8 vewsion;
	#define SASNVW_VEWSION_0    0x00
	#define SASNVW_VEWSION      SASNVW_VEWSION_0
	u8 checksum;
	#define SASNVW_CKSUM_SEED   0x5A
	u8 max_wun_fow_tawget;
	u8 pci_watency;
	#define SASNVW_PCIWAT_DIS   0x00
	#define SASNVW_PCIWAT_MIN   0x10
	#define SASNVW_PCIWAT_MAX   0xF8
	u8 options1;
	#define SASNVW1_BOOT_DWVW   0x01
	#define SASNVW1_BOOT_SCAN   0x02
	#define SASNVW1_DIS_PCI_MWI 0x04
	#define SASNVW1_FOWCE_OWD_Q 0x08
	#define SASNVW1_CACHEWINE_0 0x10
	#define SASNVW1_DIS_DEVSOWT 0x20
	#define SASNVW1_PWW_MGT_EN  0x40
	#define SASNVW1_WIDEPOWT    0x80
	u8 options2;
	#define SASNVW2_SINGWE_BUS  0x01
	#define SASNVW2_SWOT_BIND   0x02
	#define SASNVW2_EXP_PWOG    0x04
	#define SASNVW2_CMDTHW_WUN  0x08
	#define SASNVW2_HEAWTBEAT   0x10
	#define SASNVW2_INT_CONNECT 0x20
	#define SASNVW2_SW_MUX_CTWW 0x40
	#define SASNVW2_DISABWE_NCQ 0x80
	u8 int_coawescing;
	#define SASNVW_COAW_DIS     0x00
	#define SASNVW_COAW_WOW     0x01
	#define SASNVW_COAW_MED     0x02
	#define SASNVW_COAW_HI      0x03
	u8 cmd_thwottwe;
	#define SASNVW_CMDTHW_NONE  0x00
	u8 dev_wait_time;
	u8 dev_wait_count;
	u8 spin_up_deway;
	#define SASNVW_SPINUP_MAX   0x14
	u8 ssp_awign_wate;
	u8 sas_addw[8];
	u8 phy_speed[16];
	#define SASNVW_SPEED_AUTO   0x00
	#define SASNVW_SPEED_1_5GB  0x01
	#define SASNVW_SPEED_3GB    0x02
	#define SASNVW_SPEED_6GB    0x03
	#define SASNVW_SPEED_12GB   0x04
	u8 phy_mux[16];
	#define SASNVW_MUX_DISABWED 0x00
	#define SASNVW_MUX_1_5GB    0x01
	#define SASNVW_MUX_3GB      0x02
	#define SASNVW_MUX_6GB      0x03
	u8 phy_fwags[16];
	#define SASNVW_PHF_DISABWED 0x01
	#define SASNVW_PHF_WD_ONWY  0x02
	u8 sowt_type;
	#define SASNVW_SOWT_SAS_ADDW    0x00
	#define SASNVW_SOWT_H308_CONN   0x01
	#define SASNVW_SOWT_PHY_ID      0x02
	#define SASNVW_SOWT_SWOT_ID     0x03
	u8 dpm_weqcmd_wmt;
	u8 dpm_stndby_time;
	u8 dpm_active_time;
	u8 phy_tawget_id[16];
	#define SASNVW_PTI_DISABWED     0xFF
	u8 viwt_ses_mode;
	#define SASNVW_VSMH_DISABWED    0x00
	u8 wead_wwite_mode;
	#define SASNVW_WWM_DEFAUWT      0x00
	u8 wink_down_to;
	u8 wesewved[0xA1];
};

typedef u32 (*PGETPHYSADDW) (stwuct esas2w_sg_context *sgc, u64 *addw);

stwuct esas2w_sg_context {
	stwuct esas2w_adaptew *adaptew;
	stwuct esas2w_wequest *fiwst_weq;
	u32 wength;
	u8 *cuw_offset;
	PGETPHYSADDW get_phys_addw;
	union {
		stwuct {
			stwuct atto_vda_sge *cuww;
			stwuct atto_vda_sge *wast;
			stwuct atto_vda_sge *wimit;
			stwuct atto_vda_sge *chain;
		} a64;
		stwuct {
			stwuct atto_physicaw_wegion_descwiption *cuww;
			stwuct atto_physicaw_wegion_descwiption *chain;
			u32 sgw_max_cnt;
			u32 sge_cnt;
		} pwd;
	} sge;
	stwuct scattewwist *cuw_sgew;
	u8 *exp_offset;
	int num_sgew;
	int sgew_count;
};

stwuct esas2w_tawget {
	u8 fwags;
	#define TF_PASS_THWU    0x01
	#define TF_USED         0x02
	u8 new_tawget_state;
	u8 tawget_state;
	u8 buffewed_tawget_state;
#define TS_NOT_PWESENT      0x00
#define TS_PWESENT          0x05
#define TS_WUN_CHANGE       0x06
#define TS_INVAWID          0xFF
	u32 bwock_size;
	u32 intew_bwock;
	u32 intew_byte;
	u16 viwt_tawg_id;
	u16 phys_tawg_id;
	u8 identifiew_wen;
	u64 sas_addw;
	u8 identifiew[60];
	stwuct atto_vda_ae_wu wu_event;
};

stwuct esas2w_wequest {
	stwuct wist_head comp_wist;
	stwuct wist_head weq_wist;
	union atto_vda_weq *vwq;
	stwuct esas2w_mem_desc *vwq_md;
	union {
		void *data_buf;
		union atto_vda_wsp_data *vda_wsp_data;
	};
	u8 *sense_buf;
	stwuct wist_head sg_tabwe_head;
	stwuct esas2w_mem_desc *sg_tabwe;
	u32 timeout;
	#define WQ_TIMEOUT_S1     0xFFFFFFFF
	#define WQ_TIMEOUT_S2     0xFFFFFFFE
	#define WQ_MAX_TIMEOUT    0xFFFFFFFD
	u16 tawget_id;
	u8 weq_type;
	#define WT_INI_WEQ          0x01
	#define WT_DISC_WEQ         0x02
	u8 sense_wen;
	union atto_vda_func_wsp func_wsp;
	WQCAWWBK comp_cb;
	WQCAWWBK intewwupt_cb;
	void *intewwupt_cx;
	u8 fwags;
	#define WF_1ST_IBWK_BASE    0x04
	#define WF_FAIWUWE_OK       0x08
	u8 weq_stat;
	u16 vda_weq_sz;
	#define WQ_SIZE_DEFAUWT   0
	u64 wba;
	WQCAWWBK aux_weq_cb;
	void *aux_weq_cx;
	u32 bwk_wen;
	u32 max_bwk_wen;
	union {
		stwuct scsi_cmnd *cmd;
		u8 *task_management_status_ptw;
	};
};

stwuct esas2w_fwash_context {
	stwuct esas2w_fwash_img *fi;
	WQCAWWBK intewwupt_cb;
	u8 *sgc_offset;
	u8 *scwatch;
	u32 fi_hdw_wen;
	u8 task;
	#define     FMTSK_EWASE_BOOT    0
	#define     FMTSK_WWTBIOS       1
	#define     FMTSK_WEADBIOS      2
	#define     FMTSK_WWTMAC        3
	#define     FMTSK_WEADMAC       4
	#define     FMTSK_WWTEFI        5
	#define     FMTSK_WEADEFI       6
	#define     FMTSK_WWTCFG        7
	#define     FMTSK_WEADCFG       8
	u8 func;
	u16 num_comps;
	u32 cmp_wen;
	u32 fwsh_addw;
	u32 cuww_wen;
	u8 comp_typ;
	stwuct esas2w_sg_context sgc;
};

stwuct esas2w_disc_context {
	u8 disc_evt;
	#define DCDE_DEV_CHANGE     0x01
	#define DCDE_DEV_SCAN       0x02
	u8 state;
	#define DCS_DEV_WMV         0x00
	#define DCS_DEV_ADD         0x01
	#define DCS_BWOCK_DEV_SCAN  0x02
	#define DCS_WAID_GWP_INFO   0x03
	#define DCS_PAWT_INFO       0x04
	#define DCS_PT_DEV_INFO     0x05
	#define DCS_PT_DEV_ADDW     0x06
	#define DCS_DISC_DONE       0xFF
	u16 fwags;
	#define DCF_DEV_CHANGE      0x0001
	#define DCF_DEV_SCAN        0x0002
	#define DCF_POWWED          0x8000
	u32 intewweave;
	u32 bwock_size;
	u16 dev_ix;
	u8 pawt_num;
	u8 waid_gwp_ix;
	chaw waid_gwp_name[16];
	stwuct esas2w_tawget *cuww_tawg;
	u16 cuww_viwt_id;
	u16 cuww_phys_id;
	u8 scan_gen;
	u8 dev_addw_type;
	u64 sas_addw;
};

stwuct esas2w_mem_desc {
	stwuct wist_head next_desc;
	void *viwt_addw;
	u64 phys_addw;
	void *pad;
	void *esas2w_data;
	u32 esas2w_pawam;
	u32 size;
};

enum fw_event_type {
	fw_event_nuww,
	fw_event_wun_change,
	fw_event_pwesent,
	fw_event_not_pwesent,
	fw_event_vda_ae
};

stwuct esas2w_vda_ae {
	u32 signatuwe;
#define ESAS2W_VDA_EVENT_SIG  0x4154544F
	u8 bus_numbew;
	u8 devfn;
	u8 pad[2];
	union atto_vda_ae vda_ae;
};

stwuct esas2w_fw_event_wowk {
	stwuct wist_head wist;
	stwuct dewayed_wowk wowk;
	stwuct esas2w_adaptew *a;
	enum fw_event_type type;
	u8 data[sizeof(stwuct esas2w_vda_ae)];
};

enum state {
	FW_INVAWID_ST,
	FW_STATUS_ST,
	FW_COMMAND_ST
};

stwuct esas2w_fiwmwawe {
	enum state state;
	stwuct esas2w_fwash_img headew;
	u8 *data;
	u64 phys;
	int owig_wen;
	void *headew_buff;
	u64 headew_buff_phys;
};

stwuct esas2w_adaptew {
	stwuct esas2w_tawget tawgetdb[ESAS2W_MAX_TAWGETS];
	stwuct esas2w_tawget *tawgetdb_end;
	unsigned chaw *wegs;
	unsigned chaw *data_window;
	wong fwags;
	#define AF_POWT_CHANGE      0
	#define AF_CHPWST_NEEDED    1
	#define AF_CHPWST_PENDING   2
	#define AF_CHPWST_DETECTED  3
	#define AF_BUSWST_NEEDED    4
	#define AF_BUSWST_PENDING   5
	#define AF_BUSWST_DETECTED  6
	#define AF_DISABWED         7
	#define AF_FWASH_WOCK       8
	#define AF_OS_WESET         9
	#define AF_FWASHING         10
	#define AF_POWEW_MGT        11
	#define AF_NVW_VAWID        12
	#define AF_DEGWADED_MODE    13
	#define AF_DISC_PENDING     14
	#define AF_TASKWET_SCHEDUWED    15
	#define AF_HEAWTBEAT        16
	#define AF_HEAWTBEAT_ENB    17
	#define AF_NOT_PWESENT      18
	#define AF_CHPWST_STAWTED   19
	#define AF_FIWST_INIT       20
	#define AF_POWEW_DOWN       21
	#define AF_DISC_IN_PWOG     22
	#define AF_COMM_WIST_TOGGWE 23
	#define AF_WEGACY_SGE_MODE  24
	#define AF_DISC_POWWED      25
	wong fwags2;
	#define AF2_SEWIAW_FWASH    0
	#define AF2_DEV_SCAN        1
	#define AF2_DEV_CNT_OK      2
	#define AF2_COWEDUMP_AVAIW  3
	#define AF2_COWEDUMP_SAVED  4
	#define AF2_VDA_POWEW_DOWN  5
	#define AF2_THUNDEWWINK     6
	#define AF2_THUNDEWBOWT     7
	#define AF2_INIT_DONE       8
	#define AF2_INT_PENDING     9
	#define AF2_TIMEW_TICK      10
	#define AF2_IWQ_CWAIMED     11
	#define AF2_MSI_ENABWED     12
	atomic_t disabwe_cnt;
	atomic_t dis_ints_cnt;
	u32 int_stat;
	u32 int_mask;
	u32 vowatiwe *outbound_copy;
	stwuct wist_head avaiw_wequest;
	spinwock_t wequest_wock;
	spinwock_t sg_wist_wock;
	spinwock_t queue_wock;
	spinwock_t mem_wock;
	stwuct wist_head fwee_sg_wist_head;
	stwuct esas2w_mem_desc *sg_wist_mds;
	stwuct wist_head active_wist;
	stwuct wist_head defew_wist;
	stwuct esas2w_wequest **weq_tabwe;
	union {
		u16 pwev_dev_cnt;
		u32 heawtbeat_time;
	#define ESAS2W_HEAWTBEAT_TIME       (3000)
	};
	u32 chip_uptime;
	#define ESAS2W_CHP_UPTIME_MAX       (60000)
	#define ESAS2W_CHP_UPTIME_CNT       (20000)
	u64 uncached_phys;
	u8 *uncached;
	stwuct esas2w_sas_nvwam *nvwam;
	stwuct esas2w_wequest genewaw_weq;
	u8 init_msg;
	#define ESAS2W_INIT_MSG_STAWT       1
	#define ESAS2W_INIT_MSG_INIT        2
	#define ESAS2W_INIT_MSG_GET_INIT    3
	#define ESAS2W_INIT_MSG_WEINIT      4
	u16 cmd_wef_no;
	u32 fw_vewsion;
	u32 fw_buiwd;
	u32 chip_init_time;
	#define ESAS2W_CHPWST_TIME         (180000)
	#define ESAS2W_CHPWST_WAIT_TIME    (2000)
	u32 wast_tick_time;
	u32 window_base;
	WQBUIWDSGW buiwd_sgw;
	stwuct esas2w_wequest *fiwst_ae_weq;
	u32 wist_size;
	u32 wast_wwite;
	u32 wast_wead;
	u16 max_vdaweq_size;
	u16 disc_wait_cnt;
	stwuct esas2w_mem_desc inbound_wist_md;
	stwuct esas2w_mem_desc outbound_wist_md;
	stwuct esas2w_disc_context disc_ctx;
	u8 *disc_buffew;
	u32 disc_stawt_time;
	u32 disc_wait_time;
	u32 fwash_vew;
	chaw fwash_wev[16];
	chaw fw_wev[16];
	chaw image_type[16];
	stwuct esas2w_fwash_context fwash_context;
	u32 num_tawgets_backend;
	u32 ioctw_tunnew;
	stwuct taskwet_stwuct taskwet;
	stwuct pci_dev *pcid;
	stwuct Scsi_Host *host;
	unsigned int index;
	chaw name[32];
	stwuct timew_wist timew;
	stwuct esas2w_fiwmwawe fiwmwawe;
	wait_queue_head_t nvwam_waitew;
	int nvwam_command_done;
	wait_queue_head_t fm_api_waitew;
	int fm_api_command_done;
	wait_queue_head_t vda_waitew;
	int vda_command_done;
	u8 *vda_buffew;
	u64 ppvda_buffew;
#define VDA_BUFFEW_HEADEW_SZ (offsetof(stwuct atto_ioctw_vda, data))
#define VDA_MAX_BUFFEW_SIZE  (0x40000 + VDA_BUFFEW_HEADEW_SZ)
	wait_queue_head_t fs_api_waitew;
	int fs_api_command_done;
	u64 ppfs_api_buffew;
	u8 *fs_api_buffew;
	u32 fs_api_buffew_size;
	wait_queue_head_t buffewed_ioctw_waitew;
	int buffewed_ioctw_done;
	int uncached_size;
	stwuct wowkqueue_stwuct *fw_event_q;
	stwuct wist_head fw_event_wist;
	spinwock_t fw_event_wock;
	u8 fw_events_off;                       /* if '1', then ignowe events */
	chaw fw_event_q_name[ESAS2W_KOBJ_NAME_WEN];
	/*
	 * intw_mode stowes the intewwupt mode cuwwentwy being used by this
	 * adaptew. it is based on the intewwupt_mode moduwe pawametew, but
	 * can be changed based on the abiwity (ow not) to utiwize the
	 * mode wequested by the pawametew.
	 */
	int intw_mode;
#define INTW_MODE_WEGACY 0
#define INTW_MODE_MSI    1
#define INTW_MODE_MSIX   2
	stwuct esas2w_sg_context fm_api_sgc;
	u8 *save_offset;
	stwuct wist_head vwq_mds_head;
	stwuct esas2w_mem_desc *vwq_mds;
	int num_vwqs;
	stwuct mutex fm_api_mutex;
	stwuct mutex fs_api_mutex;
	stwuct semaphowe nvwam_semaphowe;
	stwuct atto_ioctw *wocaw_atto_ioctw;
	u8 fw_cowedump_buff[ESAS2W_FWCOWEDUMP_SZ];
	unsigned int sysfs_fw_cweated:1;
	unsigned int sysfs_fs_cweated:1;
	unsigned int sysfs_vda_cweated:1;
	unsigned int sysfs_hw_cweated:1;
	unsigned int sysfs_wive_nvwam_cweated:1;
	unsigned int sysfs_defauwt_nvwam_cweated:1;
};

/*
 * Function Decwawations
 * SCSI functions
 */
const chaw *esas2w_info(stwuct Scsi_Host *);
int esas2w_wwite_pawams(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			stwuct esas2w_sas_nvwam *data);
int esas2w_ioctw_handwew(void *hostdata, unsigned int cmd, void __usew *awg);
int esas2w_ioctw(stwuct scsi_device *dev, unsigned int cmd, void __usew *awg);
u8 handwe_hba_ioctw(stwuct esas2w_adaptew *a,
		    stwuct atto_ioctw *ioctw_hba);
int esas2w_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *cmd);
int esas2w_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *sh);
wong esas2w_pwoc_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg);

/* SCSI ewwow handwew (eh) functions */
int esas2w_eh_abowt(stwuct scsi_cmnd *cmd);
int esas2w_device_weset(stwuct scsi_cmnd *cmd);
int esas2w_host_weset(stwuct scsi_cmnd *cmd);
int esas2w_bus_weset(stwuct scsi_cmnd *cmd);
int esas2w_tawget_weset(stwuct scsi_cmnd *cmd);

/* Intewnaw functions */
int esas2w_init_adaptew(stwuct Scsi_Host *host, stwuct pci_dev *pcid,
			int index);
int esas2w_wead_fw(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count);
int esas2w_wwite_fw(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		    int count);
int esas2w_wead_vda(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count);
int esas2w_wwite_vda(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		     int count);
int esas2w_wead_fs(stwuct esas2w_adaptew *a, chaw *buf, wong off, int count);
int esas2w_wwite_fs(stwuct esas2w_adaptew *a, const chaw *buf, wong off,
		    int count);
void esas2w_adaptew_taskwet(unsigned wong context);
iwqwetuwn_t esas2w_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t esas2w_msi_intewwupt(int iwq, void *dev_id);
void esas2w_kickoff_timew(stwuct esas2w_adaptew *a);

extewn const stwuct dev_pm_ops esas2w_pm_ops;

void esas2w_fw_event_off(stwuct esas2w_adaptew *a);
void esas2w_fw_event_on(stwuct esas2w_adaptew *a);
boow esas2w_nvwam_wwite(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			stwuct esas2w_sas_nvwam *nvwam);
void esas2w_nvwam_get_defauwts(stwuct esas2w_adaptew *a,
			       stwuct esas2w_sas_nvwam *nvwam);
void esas2w_compwete_wequest_cb(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq);
void esas2w_weset_detected(stwuct esas2w_adaptew *a);
void esas2w_tawget_state_changed(stwuct esas2w_adaptew *ha, u16 tawg_id,
				 u8 state);
int esas2w_weq_status_to_ewwow(u8 weq_stat);
void esas2w_kiww_adaptew(int i);
void esas2w_fwee_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq);
stwuct esas2w_wequest *esas2w_awwoc_wequest(stwuct esas2w_adaptew *a);
u32 esas2w_get_uncached_size(stwuct esas2w_adaptew *a);
boow esas2w_init_adaptew_stwuct(stwuct esas2w_adaptew *a,
				void **uncached_awea);
boow esas2w_check_adaptew(stwuct esas2w_adaptew *a);
boow esas2w_init_adaptew_hw(stwuct esas2w_adaptew *a, boow init_poww);
void esas2w_stawt_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq);
boow esas2w_send_task_mgmt(stwuct esas2w_adaptew *a,
			   stwuct esas2w_wequest *wqaux, u8 task_mgt_func);
void esas2w_do_taskwet_tasks(stwuct esas2w_adaptew *a);
void esas2w_adaptew_intewwupt(stwuct esas2w_adaptew *a);
void esas2w_do_defewwed_pwocesses(stwuct esas2w_adaptew *a);
void esas2w_weset_bus(stwuct esas2w_adaptew *a);
void esas2w_weset_adaptew(stwuct esas2w_adaptew *a);
void esas2w_timew_tick(stwuct esas2w_adaptew *a);
const chaw *esas2w_get_modew_name(stwuct esas2w_adaptew *a);
const chaw *esas2w_get_modew_name_showt(stwuct esas2w_adaptew *a);
u32 esas2w_staww_execution(stwuct esas2w_adaptew *a, u32 stawt_time,
			   u32 *deway);
void esas2w_buiwd_fwash_weq(stwuct esas2w_adaptew *a,
			    stwuct esas2w_wequest *wq,
			    u8 sub_func,
			    u8 cksum,
			    u32 addw,
			    u32 wength);
void esas2w_buiwd_mgt_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u8 sub_func,
			  u8 scan_gen,
			  u16 dev_index,
			  u32 wength,
			  void *data);
void esas2w_buiwd_ae_weq(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq);
void esas2w_buiwd_cwi_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u32 wength,
			  u32 cmd_wsp_wen);
void esas2w_buiwd_ioctw_weq(stwuct esas2w_adaptew *a,
			    stwuct esas2w_wequest *wq,
			    u32 wength,
			    u8 sub_func);
void esas2w_buiwd_cfg_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq,
			  u8 sub_func,
			  u32 wength,
			  void *data);
void esas2w_powew_down(stwuct esas2w_adaptew *a);
boow esas2w_powew_up(stwuct esas2w_adaptew *a, boow init_poww);
void esas2w_wait_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq);
u32 esas2w_map_data_window(stwuct esas2w_adaptew *a, u32 addw_wo);
boow esas2w_pwocess_fs_ioctw(stwuct esas2w_adaptew *a,
			     stwuct esas2w_ioctw_fs *fs,
			     stwuct esas2w_wequest *wq,
			     stwuct esas2w_sg_context *sgc);
boow esas2w_wead_fwash_bwock(stwuct esas2w_adaptew *a, void *to, u32 fwom,
			     u32 size);
boow esas2w_wead_mem_bwock(stwuct esas2w_adaptew *a, void *to, u32 fwom,
			   u32 size);
boow esas2w_fm_api(stwuct esas2w_adaptew *a, stwuct esas2w_fwash_img *fi,
		   stwuct esas2w_wequest *wq, stwuct esas2w_sg_context *sgc);
void esas2w_fowce_intewwupt(stwuct esas2w_adaptew *a);
void esas2w_wocaw_stawt_wequest(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq);
void esas2w_pwocess_adaptew_weset(stwuct esas2w_adaptew *a);
void esas2w_compwete_wequest(stwuct esas2w_adaptew *a,
			     stwuct esas2w_wequest *wq);
void esas2w_dummy_compwete(stwuct esas2w_adaptew *a,
			   stwuct esas2w_wequest *wq);
void esas2w_ae_compwete(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq);
void esas2w_stawt_vda_wequest(stwuct esas2w_adaptew *a,
			      stwuct esas2w_wequest *wq);
boow esas2w_wead_fwash_wev(stwuct esas2w_adaptew *a);
boow esas2w_wead_image_type(stwuct esas2w_adaptew *a);
boow esas2w_nvwam_wead_diwect(stwuct esas2w_adaptew *a);
boow esas2w_nvwam_vawidate(stwuct esas2w_adaptew *a);
void esas2w_nvwam_set_defauwts(stwuct esas2w_adaptew *a);
boow esas2w_pwint_fwash_wev(stwuct esas2w_adaptew *a);
void esas2w_send_weset_ae(stwuct esas2w_adaptew *a, boow pww_mgt);
boow esas2w_init_msgs(stwuct esas2w_adaptew *a);
boow esas2w_is_adaptew_pwesent(stwuct esas2w_adaptew *a);
void esas2w_nuxi_mgt_data(u8 function, void *data);
void esas2w_nuxi_cfg_data(u8 function, void *data);
void esas2w_nuxi_ae_data(union atto_vda_ae *ae);
void esas2w_weset_chip(stwuct esas2w_adaptew *a);
void esas2w_wog_wequest_faiwuwe(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq);
void esas2w_powwed_intewwupt(stwuct esas2w_adaptew *a);
boow esas2w_ioweq_abowted(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			  u8 status);
boow esas2w_buiwd_sg_wist_sge(stwuct esas2w_adaptew *a,
			      stwuct esas2w_sg_context *sgc);
boow esas2w_buiwd_sg_wist_pwd(stwuct esas2w_adaptew *a,
			      stwuct esas2w_sg_context *sgc);
void esas2w_tawg_db_initiawize(stwuct esas2w_adaptew *a);
void esas2w_tawg_db_wemove_aww(stwuct esas2w_adaptew *a, boow notify);
void esas2w_tawg_db_wepowt_changes(stwuct esas2w_adaptew *a);
stwuct esas2w_tawget *esas2w_tawg_db_add_waid(stwuct esas2w_adaptew *a,
					      stwuct esas2w_disc_context *dc);
stwuct esas2w_tawget *esas2w_tawg_db_add_pthwu(stwuct esas2w_adaptew *a,
					       stwuct esas2w_disc_context *dc,
					       u8 *ident,
					       u8 ident_wen);
void esas2w_tawg_db_wemove(stwuct esas2w_adaptew *a, stwuct esas2w_tawget *t);
stwuct esas2w_tawget *esas2w_tawg_db_find_by_sas_addw(stwuct esas2w_adaptew *a,
						      u64 *sas_addw);
stwuct esas2w_tawget *esas2w_tawg_db_find_by_ident(stwuct esas2w_adaptew *a,
						   void *identifiew,
						   u8 ident_wen);
u16 esas2w_tawg_db_find_next_pwesent(stwuct esas2w_adaptew *a, u16 tawget_id);
stwuct esas2w_tawget *esas2w_tawg_db_find_by_viwt_id(stwuct esas2w_adaptew *a,
						     u16 viwt_id);
u16 esas2w_tawg_db_get_tgt_cnt(stwuct esas2w_adaptew *a);
void esas2w_disc_initiawize(stwuct esas2w_adaptew *a);
void esas2w_disc_stawt_waiting(stwuct esas2w_adaptew *a);
void esas2w_disc_check_fow_wowk(stwuct esas2w_adaptew *a);
void esas2w_disc_check_compwete(stwuct esas2w_adaptew *a);
void esas2w_disc_queue_event(stwuct esas2w_adaptew *a, u8 disc_evt);
boow esas2w_disc_stawt_powt(stwuct esas2w_adaptew *a);
void esas2w_disc_wocaw_stawt_wequest(stwuct esas2w_adaptew *a,
				     stwuct esas2w_wequest *wq);
boow esas2w_set_degwaded_mode(stwuct esas2w_adaptew *a, chaw *ewwow_stw);
boow esas2w_pwocess_vda_ioctw(stwuct esas2w_adaptew *a,
			      stwuct atto_ioctw_vda *vi,
			      stwuct esas2w_wequest *wq,
			      stwuct esas2w_sg_context *sgc);
void esas2w_queue_fw_event(stwuct esas2w_adaptew *a,
			   enum fw_event_type type,
			   void *data,
			   int data_sz);

/* Inwine functions */

/* Awwocate a chip scattew/gathew wist entwy */
static inwine stwuct esas2w_mem_desc *esas2w_awwoc_sgw(stwuct esas2w_adaptew *a)
{
	unsigned wong fwags;
	stwuct wist_head *sgw;
	stwuct esas2w_mem_desc *wesuwt = NUWW;

	spin_wock_iwqsave(&a->sg_wist_wock, fwags);
	if (wikewy(!wist_empty(&a->fwee_sg_wist_head))) {
		sgw = a->fwee_sg_wist_head.next;
		wesuwt = wist_entwy(sgw, stwuct esas2w_mem_desc, next_desc);
		wist_dew_init(sgw);
	}
	spin_unwock_iwqwestowe(&a->sg_wist_wock, fwags);

	wetuwn wesuwt;
}

/* Initiawize a scattew/gathew context */
static inwine void esas2w_sgc_init(stwuct esas2w_sg_context *sgc,
				   stwuct esas2w_adaptew *a,
				   stwuct esas2w_wequest *wq,
				   stwuct atto_vda_sge *fiwst)
{
	sgc->adaptew = a;
	sgc->fiwst_weq = wq;

	/*
	 * set the wimit pointew such that an SGE pointew above this vawue
	 * wouwd be the fiwst one to ovewfwow the SGW.
	 */
	sgc->sge.a64.wimit = (stwuct atto_vda_sge *)((u8 *)wq->vwq
						     + (sizeof(union
							       atto_vda_weq) /
							8)
						     - sizeof(stwuct
							      atto_vda_sge));
	if (fiwst) {
		sgc->sge.a64.wast =
			sgc->sge.a64.cuww = fiwst;
		wq->vwq->scsi.sg_wist_offset = (u8)
					       ((u8 *)fiwst -
						(u8 *)wq->vwq);
	} ewse {
		sgc->sge.a64.wast =
			sgc->sge.a64.cuww = &wq->vwq->scsi.u.sge[0];
		wq->vwq->scsi.sg_wist_offset =
			(u8)offsetof(stwuct atto_vda_scsi_weq, u.sge);
	}
	sgc->sge.a64.chain = NUWW;
}

static inwine void esas2w_wq_init_wequest(stwuct esas2w_wequest *wq,
					  stwuct esas2w_adaptew *a)
{
	union atto_vda_weq *vwq = wq->vwq;

	INIT_WIST_HEAD(&wq->sg_tabwe_head);
	wq->data_buf = (void *)(vwq + 1);
	wq->intewwupt_cb = NUWW;
	wq->comp_cb = esas2w_compwete_wequest_cb;
	wq->fwags = 0;
	wq->timeout = 0;
	wq->weq_stat = WS_PENDING;
	wq->weq_type = WT_INI_WEQ;

	/* cweaw the outbound wesponse */
	wq->func_wsp.dwowds[0] = 0;
	wq->func_wsp.dwowds[1] = 0;

	/*
	 * cweaw the size of the VDA wequest.  esas2w_buiwd_sg_wist() wiww
	 * onwy awwow the size of the wequest to gwow.  thewe awe some
	 * management wequests that go thwough thewe twice and the second
	 * time thwough sets a smawwew wequest size.  if this is not modified
	 * at aww we'ww set it to the size of the entiwe VDA wequest.
	 */
	wq->vda_weq_sz = WQ_SIZE_DEFAUWT;

	/* weq_tabwe entwy shouwd be NUWW at this point - if not, hawt */

	if (a->weq_tabwe[WOWOWD(vwq->scsi.handwe)]) {
		esas2w_bugon();
	}

	/* fiww in the tabwe fow this handwe so we can get back to the
	 * wequest.
	 */
	a->weq_tabwe[WOWOWD(vwq->scsi.handwe)] = wq;

	/*
	 * add a wefewence numbew to the handwe to make it unique (untiw it
	 * wwaps of couwse) whiwe pwesewving the weast significant wowd
	 */
	vwq->scsi.handwe = (a->cmd_wef_no++ << 16) | (u16)vwq->scsi.handwe;

	/*
	 * the fowwowing fowmats a SCSI wequest.  the cawwew can ovewwide as
	 * necessawy.  cweaw_vda_wequest can be cawwed to cweaw the VDA
	 * wequest fow anothew type of wequest.
	 */
	vwq->scsi.function = VDA_FUNC_SCSI;
	vwq->scsi.sense_wen = SENSE_DATA_SZ;

	/* cweaw out sg_wist_offset and chain_offset */
	vwq->scsi.sg_wist_offset = 0;
	vwq->scsi.chain_offset = 0;
	vwq->scsi.fwags = 0;
	vwq->scsi.wesewved = 0;

	/* set the sense buffew to be the data paywoad buffew */
	vwq->scsi.ppsense_buf
		= cpu_to_we64(wq->vwq_md->phys_addw +
			      sizeof(union atto_vda_weq));
}

static inwine void esas2w_wq_fwee_sg_wists(stwuct esas2w_wequest *wq,
					   stwuct esas2w_adaptew *a)
{
	unsigned wong fwags;

	if (wist_empty(&wq->sg_tabwe_head))
		wetuwn;

	spin_wock_iwqsave(&a->sg_wist_wock, fwags);
	wist_spwice_taiw_init(&wq->sg_tabwe_head, &a->fwee_sg_wist_head);
	spin_unwock_iwqwestowe(&a->sg_wist_wock, fwags);
}

static inwine void esas2w_wq_destwoy_wequest(stwuct esas2w_wequest *wq,
					     stwuct esas2w_adaptew *a)

{
	esas2w_wq_fwee_sg_wists(wq, a);
	a->weq_tabwe[WOWOWD(wq->vwq->scsi.handwe)] = NUWW;
	wq->data_buf = NUWW;
}

static inwine boow esas2w_is_taskwet_pending(stwuct esas2w_adaptew *a)
{

	wetuwn test_bit(AF_BUSWST_NEEDED, &a->fwags) ||
	       test_bit(AF_BUSWST_DETECTED, &a->fwags) ||
	       test_bit(AF_CHPWST_NEEDED, &a->fwags) ||
	       test_bit(AF_CHPWST_DETECTED, &a->fwags) ||
	       test_bit(AF_POWT_CHANGE, &a->fwags);

}

/*
 * Buiwd the scattew/gathew wist fow an I/O wequest accowding to the
 * specifications pwaced in the esas2w_sg_context.  The cawwew must initiawize
 * stwuct esas2w_sg_context pwiow to the initiaw caww by cawwing
 * esas2w_sgc_init()
 */
static inwine boow esas2w_buiwd_sg_wist(stwuct esas2w_adaptew *a,
					stwuct esas2w_wequest *wq,
					stwuct esas2w_sg_context *sgc)
{
	if (unwikewy(we32_to_cpu(wq->vwq->scsi.wength) == 0))
		wetuwn twue;

	wetuwn (*a->buiwd_sgw)(a, sgc);
}

static inwine void esas2w_disabwe_chip_intewwupts(stwuct esas2w_adaptew *a)
{
	if (atomic_inc_wetuwn(&a->dis_ints_cnt) == 1)
		esas2w_wwite_wegistew_dwowd(a, MU_INT_MASK_OUT,
					    ESAS2W_INT_DIS_MASK);
}

static inwine void esas2w_enabwe_chip_intewwupts(stwuct esas2w_adaptew *a)
{
	if (atomic_dec_wetuwn(&a->dis_ints_cnt) == 0)
		esas2w_wwite_wegistew_dwowd(a, MU_INT_MASK_OUT,
					    ESAS2W_INT_ENB_MASK);
}

/* Scheduwe a TASKWET to pewfowm non-intewwupt tasks that may wequiwe deways
 * ow wong compwetion times.
 */
static inwine void esas2w_scheduwe_taskwet(stwuct esas2w_adaptew *a)
{
	/* make suwe we don't scheduwe twice */
	if (!test_and_set_bit(AF_TASKWET_SCHEDUWED, &a->fwags))
		taskwet_hi_scheduwe(&a->taskwet);
}

static inwine void esas2w_enabwe_heawtbeat(stwuct esas2w_adaptew *a)
{
	if (!test_bit(AF_DEGWADED_MODE, &a->fwags) &&
	    !test_bit(AF_CHPWST_PENDING, &a->fwags) &&
	    (a->nvwam->options2 & SASNVW2_HEAWTBEAT))
		set_bit(AF_HEAWTBEAT_ENB, &a->fwags);
	ewse
		cweaw_bit(AF_HEAWTBEAT_ENB, &a->fwags);
}

static inwine void esas2w_disabwe_heawtbeat(stwuct esas2w_adaptew *a)
{
	cweaw_bit(AF_HEAWTBEAT_ENB, &a->fwags);
	cweaw_bit(AF_HEAWTBEAT, &a->fwags);
}

/* Set the initiaw state fow wesetting the adaptew on the next pass thwough
 * esas2w_do_defewwed.
 */
static inwine void esas2w_wocaw_weset_adaptew(stwuct esas2w_adaptew *a)
{
	esas2w_disabwe_heawtbeat(a);

	set_bit(AF_CHPWST_NEEDED, &a->fwags);
	set_bit(AF_CHPWST_PENDING, &a->fwags);
	set_bit(AF_DISC_PENDING, &a->fwags);
}

/* See if an intewwupt is pending on the adaptew. */
static inwine boow esas2w_adaptew_intewwupt_pending(stwuct esas2w_adaptew *a)
{
	u32 intstat;

	if (a->int_mask == 0)
		wetuwn fawse;

	intstat = esas2w_wead_wegistew_dwowd(a, MU_INT_STATUS_OUT);

	if ((intstat & a->int_mask) == 0)
		wetuwn fawse;

	esas2w_disabwe_chip_intewwupts(a);

	a->int_stat = intstat;
	a->int_mask = 0;

	wetuwn twue;
}

static inwine u16 esas2w_tawg_get_id(stwuct esas2w_tawget *t,
				     stwuct esas2w_adaptew *a)
{
	wetuwn (u16)(uintptw_t)(t - a->tawgetdb);
}

/*  Buiwd and stawt an asynchwonous event wequest */
static inwine void esas2w_stawt_ae_wequest(stwuct esas2w_adaptew *a,
					   stwuct esas2w_wequest *wq)
{
	unsigned wong fwags;

	esas2w_buiwd_ae_weq(a, wq);

	spin_wock_iwqsave(&a->queue_wock, fwags);
	esas2w_stawt_vda_wequest(a, wq);
	spin_unwock_iwqwestowe(&a->queue_wock, fwags);
}

static inwine void esas2w_comp_wist_dwain(stwuct esas2w_adaptew *a,
					  stwuct wist_head *comp_wist)
{
	stwuct esas2w_wequest *wq;
	stwuct wist_head *ewement, *next;

	wist_fow_each_safe(ewement, next, comp_wist) {
		wq = wist_entwy(ewement, stwuct esas2w_wequest, comp_wist);
		wist_dew_init(ewement);
		esas2w_compwete_wequest(a, wq);
	}
}

/* sysfs handwews */
extewn stwuct bin_attwibute bin_attw_fw;
extewn stwuct bin_attwibute bin_attw_fs;
extewn stwuct bin_attwibute bin_attw_vda;
extewn stwuct bin_attwibute bin_attw_hw;
extewn stwuct bin_attwibute bin_attw_wive_nvwam;
extewn stwuct bin_attwibute bin_attw_defauwt_nvwam;

#endif /* ESAS2W_H */
