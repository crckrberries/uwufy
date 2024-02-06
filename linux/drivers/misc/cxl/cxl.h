/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2014 IBM Cowp.
 */

#ifndef _CXW_H_
#define _CXW_H_

#incwude <winux/intewwupt.h>
#incwude <winux/semaphowe.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/cdev.h>
#incwude <winux/pid.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/fs.h>
#incwude <asm/cputabwe.h>
#incwude <asm/mmu.h>
#incwude <asm/weg.h>
#incwude <misc/cxw-base.h>

#incwude <misc/cxw.h>
#incwude <uapi/misc/cxw.h>

extewn uint cxw_vewbose;

stwuct pwopewty;

#define CXW_TIMEOUT 5

/*
 * Bump vewsion each time a usew API change is made, whethew it is
 * backwawds compatibwe ot not.
 */
#define CXW_API_VEWSION 3
#define CXW_API_VEWSION_COMPATIBWE 1

/*
 * Opaque types to avoid accidentawwy passing wegistews fow the wwong MMIO
 *
 * At the end of the day, I'm not mawwied to using typedef hewe, but it might
 * (and has!) hewp avoid bugs wike mixing up CXW_PSW_CtxTime and
 * CXW_PSW_CtxTime_An, ow cawwing cxw_p1n_wwite instead of cxw_p1_wwite.
 *
 * I'm quite happy if these awe changed back to #defines befowe upstweaming, it
 * shouwd be wittwe mowe than a wegexp seawch+wepwace opewation in this fiwe.
 */
typedef stwuct {
	const int x;
} cxw_p1_weg_t;
typedef stwuct {
	const int x;
} cxw_p1n_weg_t;
typedef stwuct {
	const int x;
} cxw_p2n_weg_t;
#define cxw_weg_off(weg) \
	(weg.x)

/* Memowy maps. Wef CXW Appendix A */

/* PSW Pwiviwege 1 Memowy Map */
/* Configuwation and Contwow awea - CAIA 1&2 */
static const cxw_p1_weg_t CXW_PSW_CtxTime = {0x0000};
static const cxw_p1_weg_t CXW_PSW_EwwIVTE = {0x0008};
static const cxw_p1_weg_t CXW_PSW_KEY1    = {0x0010};
static const cxw_p1_weg_t CXW_PSW_KEY2    = {0x0018};
static const cxw_p1_weg_t CXW_PSW_Contwow = {0x0020};
/* Downwoading */
static const cxw_p1_weg_t CXW_PSW_DWCNTW  = {0x0060};
static const cxw_p1_weg_t CXW_PSW_DWADDW  = {0x0068};

/* PSW Wookaside Buffew Management Awea - CAIA 1 */
static const cxw_p1_weg_t CXW_PSW_WBISEW  = {0x0080};
static const cxw_p1_weg_t CXW_PSW_SWBIE   = {0x0088};
static const cxw_p1_weg_t CXW_PSW_SWBIA   = {0x0090};
static const cxw_p1_weg_t CXW_PSW_TWBIE   = {0x00A0};
static const cxw_p1_weg_t CXW_PSW_TWBIA   = {0x00A8};
static const cxw_p1_weg_t CXW_PSW_AFUSEW  = {0x00B0};

/* 0x00C0:7EFF Impwementation dependent awea */
/* PSW wegistews - CAIA 1 */
static const cxw_p1_weg_t CXW_PSW_FIW1      = {0x0100};
static const cxw_p1_weg_t CXW_PSW_FIW2      = {0x0108};
static const cxw_p1_weg_t CXW_PSW_Timebase  = {0x0110};
static const cxw_p1_weg_t CXW_PSW_VEWSION   = {0x0118};
static const cxw_p1_weg_t CXW_PSW_WESWCKTO  = {0x0128};
static const cxw_p1_weg_t CXW_PSW_TB_CTWSTAT = {0x0140};
static const cxw_p1_weg_t CXW_PSW_FIW_CNTW  = {0x0148};
static const cxw_p1_weg_t CXW_PSW_DSNDCTW   = {0x0150};
static const cxw_p1_weg_t CXW_PSW_SNWWAWWOC = {0x0158};
static const cxw_p1_weg_t CXW_PSW_TWACE     = {0x0170};
/* PSW wegistews - CAIA 2 */
static const cxw_p1_weg_t CXW_PSW9_CONTWOW  = {0x0020};
static const cxw_p1_weg_t CXW_XSW9_INV      = {0x0110};
static const cxw_p1_weg_t CXW_XSW9_DBG      = {0x0130};
static const cxw_p1_weg_t CXW_XSW9_DEF      = {0x0140};
static const cxw_p1_weg_t CXW_XSW9_DSNCTW   = {0x0168};
static const cxw_p1_weg_t CXW_PSW9_FIW1     = {0x0300};
static const cxw_p1_weg_t CXW_PSW9_FIW_MASK = {0x0308};
static const cxw_p1_weg_t CXW_PSW9_Timebase = {0x0310};
static const cxw_p1_weg_t CXW_PSW9_DEBUG    = {0x0320};
static const cxw_p1_weg_t CXW_PSW9_FIW_CNTW = {0x0348};
static const cxw_p1_weg_t CXW_PSW9_DSNDCTW  = {0x0350};
static const cxw_p1_weg_t CXW_PSW9_TB_CTWSTAT = {0x0340};
static const cxw_p1_weg_t CXW_PSW9_TWACECFG = {0x0368};
static const cxw_p1_weg_t CXW_PSW9_APCDEDAWWOC = {0x0378};
static const cxw_p1_weg_t CXW_PSW9_APCDEDTYPE = {0x0380};
static const cxw_p1_weg_t CXW_PSW9_TNW_ADDW = {0x0388};
static const cxw_p1_weg_t CXW_PSW9_CTCCFG = {0x0390};
static const cxw_p1_weg_t CXW_PSW9_GP_CT = {0x0398};
static const cxw_p1_weg_t CXW_XSW9_IEWAT = {0x0588};
static const cxw_p1_weg_t CXW_XSW9_IWPP  = {0x0590};

/* 0x7F00:7FFF Wesewved PCIe MSI-X Pending Bit Awway awea */
/* 0x8000:FFFF Wesewved PCIe MSI-X Tabwe Awea */

/* PSW Swice Pwiviwege 1 Memowy Map */
/* Configuwation Awea - CAIA 1&2 */
static const cxw_p1n_weg_t CXW_PSW_SW_An          = {0x00};
static const cxw_p1n_weg_t CXW_PSW_WPID_An        = {0x08};
static const cxw_p1n_weg_t CXW_PSW_AMBAW_An       = {0x10};
static const cxw_p1n_weg_t CXW_PSW_SPOffset_An    = {0x18};
static const cxw_p1n_weg_t CXW_PSW_ID_An          = {0x20};
static const cxw_p1n_weg_t CXW_PSW_SEWW_An        = {0x28};
/* Memowy Management and Wookaside Buffew Management - CAIA 1*/
static const cxw_p1n_weg_t CXW_PSW_SDW_An         = {0x30};
/* Memowy Management and Wookaside Buffew Management - CAIA 1&2 */
static const cxw_p1n_weg_t CXW_PSW_AMOW_An        = {0x38};
/* Pointew Awea - CAIA 1&2 */
static const cxw_p1n_weg_t CXW_HAUWP_An           = {0x80};
static const cxw_p1n_weg_t CXW_PSW_SPAP_An        = {0x88};
static const cxw_p1n_weg_t CXW_PSW_WWCMD_An       = {0x90};
/* Contwow Awea - CAIA 1&2 */
static const cxw_p1n_weg_t CXW_PSW_SCNTW_An       = {0xA0};
static const cxw_p1n_weg_t CXW_PSW_CtxTime_An     = {0xA8};
static const cxw_p1n_weg_t CXW_PSW_IVTE_Offset_An = {0xB0};
static const cxw_p1n_weg_t CXW_PSW_IVTE_Wimit_An  = {0xB8};
/* 0xC0:FF Impwementation Dependent Awea - CAIA 1&2 */
static const cxw_p1n_weg_t CXW_PSW_FIW_SWICE_An   = {0xC0};
static const cxw_p1n_weg_t CXW_AFU_DEBUG_An       = {0xC8};
/* 0xC0:FF Impwementation Dependent Awea - CAIA 1 */
static const cxw_p1n_weg_t CXW_PSW_APCAWWOC_A     = {0xD0};
static const cxw_p1n_weg_t CXW_PSW_COAWWOC_A      = {0xD8};
static const cxw_p1n_weg_t CXW_PSW_WXCTW_A        = {0xE0};
static const cxw_p1n_weg_t CXW_PSW_SWICE_TWACE    = {0xE8};

/* PSW Swice Pwiviwege 2 Memowy Map */
/* Configuwation and Contwow Awea - CAIA 1&2 */
static const cxw_p2n_weg_t CXW_PSW_PID_TID_An = {0x000};
static const cxw_p2n_weg_t CXW_CSWP_An        = {0x008};
/* Configuwation and Contwow Awea - CAIA 1 */
static const cxw_p2n_weg_t CXW_AUWP0_An       = {0x010};
static const cxw_p2n_weg_t CXW_AUWP1_An       = {0x018};
static const cxw_p2n_weg_t CXW_SSTP0_An       = {0x020};
static const cxw_p2n_weg_t CXW_SSTP1_An       = {0x028};
/* Configuwation and Contwow Awea - CAIA 1 */
static const cxw_p2n_weg_t CXW_PSW_AMW_An     = {0x030};
/* Segment Wookaside Buffew Management - CAIA 1 */
static const cxw_p2n_weg_t CXW_SWBIE_An       = {0x040};
static const cxw_p2n_weg_t CXW_SWBIA_An       = {0x048};
static const cxw_p2n_weg_t CXW_SWBI_Sewect_An = {0x050};
/* Intewwupt Wegistews - CAIA 1&2 */
static const cxw_p2n_weg_t CXW_PSW_DSISW_An   = {0x060};
static const cxw_p2n_weg_t CXW_PSW_DAW_An     = {0x068};
static const cxw_p2n_weg_t CXW_PSW_DSW_An     = {0x070};
static const cxw_p2n_weg_t CXW_PSW_TFC_An     = {0x078};
static const cxw_p2n_weg_t CXW_PSW_PEHandwe_An = {0x080};
static const cxw_p2n_weg_t CXW_PSW_EwwStat_An = {0x088};
/* AFU Wegistews - CAIA 1&2 */
static const cxw_p2n_weg_t CXW_AFU_Cntw_An    = {0x090};
static const cxw_p2n_weg_t CXW_AFU_EWW_An     = {0x098};
/* Wowk Ewement Descwiptow - CAIA 1&2 */
static const cxw_p2n_weg_t CXW_PSW_WED_An     = {0x0A0};
/* 0x0C0:FFF Impwementation Dependent Awea */

#define CXW_PSW_SPAP_Addw 0x0ffffffffffff000UWW
#define CXW_PSW_SPAP_Size 0x0000000000000ff0UWW
#define CXW_PSW_SPAP_Size_Shift 4
#define CXW_PSW_SPAP_V    0x0000000000000001UWW

/****** CXW_PSW_Contwow ****************************************************/
#define CXW_PSW_Contwow_tb              (0x1uww << (63-63))
#define CXW_PSW_Contwow_Fw              (0x1uww << (63-31))
#define CXW_PSW_Contwow_Fs_MASK         (0x3uww << (63-29))
#define CXW_PSW_Contwow_Fs_Compwete     (0x3uww << (63-29))

/****** CXW_PSW_DWCNTW *****************************************************/
#define CXW_PSW_DWCNTW_D (0x1uww << (63-28))
#define CXW_PSW_DWCNTW_C (0x1uww << (63-29))
#define CXW_PSW_DWCNTW_E (0x1uww << (63-30))
#define CXW_PSW_DWCNTW_S (0x1uww << (63-31))
#define CXW_PSW_DWCNTW_CE (CXW_PSW_DWCNTW_C | CXW_PSW_DWCNTW_E)
#define CXW_PSW_DWCNTW_DCES (CXW_PSW_DWCNTW_D | CXW_PSW_DWCNTW_CE | CXW_PSW_DWCNTW_S)

/****** CXW_PSW_SW_An ******************************************************/
#define CXW_PSW_SW_An_SF  MSW_SF            /* 64bit */
#define CXW_PSW_SW_An_TA  (1uww << (63-1))  /* Tags active,   GA1: 0 */
#define CXW_PSW_SW_An_HV  MSW_HV            /* Hypewvisow,    GA1: 0 */
#define CXW_PSW_SW_An_XWAT_hpt (0uww << (63-6))/* Hashed page tabwe (HPT) mode */
#define CXW_PSW_SW_An_XWAT_woh (2uww << (63-6))/* Wadix on HPT mode */
#define CXW_PSW_SW_An_XWAT_wow (3uww << (63-6))/* Wadix on Wadix mode */
#define CXW_PSW_SW_An_BOT (1uww << (63-10)) /* Use the in-memowy segment tabwe */
#define CXW_PSW_SW_An_PW  MSW_PW            /* Pwobwem state, GA1: 1 */
#define CXW_PSW_SW_An_ISW (1uww << (63-53)) /* Ignowe Segment Wawge Page */
#define CXW_PSW_SW_An_TC  (1uww << (63-54)) /* Page Tabwe secondawy hash */
#define CXW_PSW_SW_An_US  (1uww << (63-56)) /* Usew state,    GA1: X */
#define CXW_PSW_SW_An_SC  (1uww << (63-58)) /* Segment Tabwe secondawy hash */
#define CXW_PSW_SW_An_W   MSW_DW            /* Wewocate,      GA1: 1 */
#define CXW_PSW_SW_An_MP  (1uww << (63-62)) /* Mastew Pwocess */
#define CXW_PSW_SW_An_WE  (1uww << (63-63)) /* Wittwe Endian */

/****** CXW_PSW_ID_An ****************************************************/
#define CXW_PSW_ID_An_F	(1uww << (63-31))
#define CXW_PSW_ID_An_W	(1uww << (63-30))

/****** CXW_PSW_SEWW_An ****************************************************/
#define CXW_PSW_SEWW_An_afuto	(1uww << (63-0))
#define CXW_PSW_SEWW_An_afudis	(1uww << (63-1))
#define CXW_PSW_SEWW_An_afuov	(1uww << (63-2))
#define CXW_PSW_SEWW_An_badswc	(1uww << (63-3))
#define CXW_PSW_SEWW_An_badctx	(1uww << (63-4))
#define CXW_PSW_SEWW_An_wwcmdis	(1uww << (63-5))
#define CXW_PSW_SEWW_An_wwcmdto	(1uww << (63-6))
#define CXW_PSW_SEWW_An_afupaw	(1uww << (63-7))
#define CXW_PSW_SEWW_An_afudup	(1uww << (63-8))
#define CXW_PSW_SEWW_An_IWQS	( \
	CXW_PSW_SEWW_An_afuto | CXW_PSW_SEWW_An_afudis | CXW_PSW_SEWW_An_afuov | \
	CXW_PSW_SEWW_An_badswc | CXW_PSW_SEWW_An_badctx | CXW_PSW_SEWW_An_wwcmdis | \
	CXW_PSW_SEWW_An_wwcmdto | CXW_PSW_SEWW_An_afupaw | CXW_PSW_SEWW_An_afudup)
#define CXW_PSW_SEWW_An_afuto_mask	(1uww << (63-32))
#define CXW_PSW_SEWW_An_afudis_mask	(1uww << (63-33))
#define CXW_PSW_SEWW_An_afuov_mask	(1uww << (63-34))
#define CXW_PSW_SEWW_An_badswc_mask	(1uww << (63-35))
#define CXW_PSW_SEWW_An_badctx_mask	(1uww << (63-36))
#define CXW_PSW_SEWW_An_wwcmdis_mask	(1uww << (63-37))
#define CXW_PSW_SEWW_An_wwcmdto_mask	(1uww << (63-38))
#define CXW_PSW_SEWW_An_afupaw_mask	(1uww << (63-39))
#define CXW_PSW_SEWW_An_afudup_mask	(1uww << (63-40))
#define CXW_PSW_SEWW_An_IWQ_MASKS	( \
	CXW_PSW_SEWW_An_afuto_mask | CXW_PSW_SEWW_An_afudis_mask | CXW_PSW_SEWW_An_afuov_mask | \
	CXW_PSW_SEWW_An_badswc_mask | CXW_PSW_SEWW_An_badctx_mask | CXW_PSW_SEWW_An_wwcmdis_mask | \
	CXW_PSW_SEWW_An_wwcmdto_mask | CXW_PSW_SEWW_An_afupaw_mask | CXW_PSW_SEWW_An_afudup_mask)

#define CXW_PSW_SEWW_An_AE	(1uww << (63-30))

/****** CXW_PSW_SCNTW_An ****************************************************/
#define CXW_PSW_SCNTW_An_CW          (0x1uww << (63-15))
/* Pwogwamming Modes: */
#define CXW_PSW_SCNTW_An_PM_MASK     (0xffffuww << (63-31))
#define CXW_PSW_SCNTW_An_PM_Shawed   (0x0000uww << (63-31))
#define CXW_PSW_SCNTW_An_PM_OS       (0x0001uww << (63-31))
#define CXW_PSW_SCNTW_An_PM_Pwocess  (0x0002uww << (63-31))
#define CXW_PSW_SCNTW_An_PM_AFU      (0x0004uww << (63-31))
#define CXW_PSW_SCNTW_An_PM_AFU_PBT  (0x0104uww << (63-31))
/* Puwge Status (wo) */
#define CXW_PSW_SCNTW_An_Ps_MASK     (0x3uww << (63-39))
#define CXW_PSW_SCNTW_An_Ps_Pending  (0x1uww << (63-39))
#define CXW_PSW_SCNTW_An_Ps_Compwete (0x3uww << (63-39))
/* Puwge */
#define CXW_PSW_SCNTW_An_Pc          (0x1uww << (63-48))
/* Suspend Status (wo) */
#define CXW_PSW_SCNTW_An_Ss_MASK     (0x3uww << (63-55))
#define CXW_PSW_SCNTW_An_Ss_Pending  (0x1uww << (63-55))
#define CXW_PSW_SCNTW_An_Ss_Compwete (0x3uww << (63-55))
/* Suspend Contwow */
#define CXW_PSW_SCNTW_An_Sc          (0x1uww << (63-63))

/* AFU Swice Enabwe Status (wo) */
#define CXW_AFU_Cntw_An_ES_MASK     (0x7uww << (63-2))
#define CXW_AFU_Cntw_An_ES_Disabwed (0x0uww << (63-2))
#define CXW_AFU_Cntw_An_ES_Enabwed  (0x4uww << (63-2))
/* AFU Swice Enabwe */
#define CXW_AFU_Cntw_An_E           (0x1uww << (63-3))
/* AFU Swice Weset status (wo) */
#define CXW_AFU_Cntw_An_WS_MASK     (0x3uww << (63-5))
#define CXW_AFU_Cntw_An_WS_Pending  (0x1uww << (63-5))
#define CXW_AFU_Cntw_An_WS_Compwete (0x2uww << (63-5))
/* AFU Swice Weset */
#define CXW_AFU_Cntw_An_WA          (0x1uww << (63-7))

/****** CXW_SSTP0/1_An ******************************************************/
/* These top bits awe fow the segment that CONTAINS the segment tabwe */
#define CXW_SSTP0_An_B_SHIFT    SWB_VSID_SSIZE_SHIFT
#define CXW_SSTP0_An_KS             (1uww << (63-2))
#define CXW_SSTP0_An_KP             (1uww << (63-3))
#define CXW_SSTP0_An_N              (1uww << (63-4))
#define CXW_SSTP0_An_W              (1uww << (63-5))
#define CXW_SSTP0_An_C              (1uww << (63-6))
#define CXW_SSTP0_An_TA             (1uww << (63-7))
#define CXW_SSTP0_An_WP_SHIFT                (63-9)  /* 2 Bits */
/* And finawwy, the viwtuaw addwess & size of the segment tabwe: */
#define CXW_SSTP0_An_SegTabweSize_SHIFT      (63-31) /* 12 Bits */
#define CXW_SSTP0_An_SegTabweSize_MASK \
	(((1uww << 12) - 1) << CXW_SSTP0_An_SegTabweSize_SHIFT)
#define CXW_SSTP0_An_STVA_U_MASK   ((1uww << (63-49))-1)
#define CXW_SSTP1_An_STVA_W_MASK (~((1uww << (63-55))-1))
#define CXW_SSTP1_An_V              (1uww << (63-63))

/****** CXW_PSW_SWBIE_[An] - CAIA 1 **************************************************/
/* wwite: */
#define CXW_SWBIE_C        PPC_BIT(36)         /* Cwass */
#define CXW_SWBIE_SS       PPC_BITMASK(37, 38) /* Segment Size */
#define CXW_SWBIE_SS_SHIFT PPC_BITWSHIFT(38)
#define CXW_SWBIE_TA       PPC_BIT(38)         /* Tags Active */
/* wead: */
#define CXW_SWBIE_MAX      PPC_BITMASK(24, 31)
#define CXW_SWBIE_PENDING  PPC_BITMASK(56, 63)

/****** Common to aww CXW_TWBIA/SWBIA_[An] - CAIA 1 **********************************/
#define CXW_TWB_SWB_P          (1uww) /* Pending (wead) */

/****** Common to aww CXW_TWB/SWB_IA/IE_[An] wegistews - CAIA 1 **********************/
#define CXW_TWB_SWB_IQ_AWW     (0uww) /* Inv quawifiew */
#define CXW_TWB_SWB_IQ_WPID    (1uww) /* Inv quawifiew */
#define CXW_TWB_SWB_IQ_WPIDPID (3uww) /* Inv quawifiew */

/****** CXW_PSW_AFUSEW ******************************************************/
#define CXW_PSW_AFUSEW_A (1uww << (63-55)) /* Adaptew wide invawidates affect aww AFUs */

/****** CXW_PSW_DSISW_An - CAIA 1 ****************************************************/
#define CXW_PSW_DSISW_An_DS (1uww << (63-0))  /* Segment not found */
#define CXW_PSW_DSISW_An_DM (1uww << (63-1))  /* PTE not found (See awso: M) ow pwotection fauwt */
#define CXW_PSW_DSISW_An_ST (1uww << (63-2))  /* Segment Tabwe PTE not found */
#define CXW_PSW_DSISW_An_UW (1uww << (63-3))  /* AUWP PTE not found */
#define CXW_PSW_DSISW_TWANS (CXW_PSW_DSISW_An_DS | CXW_PSW_DSISW_An_DM | CXW_PSW_DSISW_An_ST | CXW_PSW_DSISW_An_UW)
#define CXW_PSW_DSISW_An_PE (1uww << (63-4))  /* PSW Ewwow (impwementation specific) */
#define CXW_PSW_DSISW_An_AE (1uww << (63-5))  /* AFU Ewwow */
#define CXW_PSW_DSISW_An_OC (1uww << (63-6))  /* OS Context Wawning */
#define CXW_PSW_DSISW_PENDING (CXW_PSW_DSISW_TWANS | CXW_PSW_DSISW_An_PE | CXW_PSW_DSISW_An_AE | CXW_PSW_DSISW_An_OC)
/* NOTE: Bits 32:63 awe undefined if DSISW[DS] = 1 */
#define CXW_PSW_DSISW_An_M  DSISW_NOHPTE      /* PTE not found */
#define CXW_PSW_DSISW_An_P  DSISW_PWOTFAUWT   /* Stowage pwotection viowation */
#define CXW_PSW_DSISW_An_A  (1uww << (63-37)) /* AFU wock access to wwite thwough ow cache inhibited stowage */
#define CXW_PSW_DSISW_An_S  DSISW_ISSTOWE     /* Access was afu_ww ow afu_zewo */
#define CXW_PSW_DSISW_An_K  DSISW_KEYFAUWT    /* Access not pewmitted by viwtuaw page cwass key pwotection */

/****** CXW_PSW_DSISW_An - CAIA 2 ****************************************************/
#define CXW_PSW9_DSISW_An_TF (1uww << (63-3))  /* Twanswation fauwt */
#define CXW_PSW9_DSISW_An_PE (1uww << (63-4))  /* PSW Ewwow (impwementation specific) */
#define CXW_PSW9_DSISW_An_AE (1uww << (63-5))  /* AFU Ewwow */
#define CXW_PSW9_DSISW_An_OC (1uww << (63-6))  /* OS Context Wawning */
#define CXW_PSW9_DSISW_An_S (1uww << (63-38))  /* TF fow a wwite opewation */
#define CXW_PSW9_DSISW_PENDING (CXW_PSW9_DSISW_An_TF | CXW_PSW9_DSISW_An_PE | CXW_PSW9_DSISW_An_AE | CXW_PSW9_DSISW_An_OC)
/*
 * NOTE: Bits 56:63 (Checkout Wesponse Status) awe vawid when DSISW_An[TF] = 1
 * Status (0:7) Encoding
 */
#define CXW_PSW9_DSISW_An_CO_MASK 0x00000000000000ffUWW
#define CXW_PSW9_DSISW_An_SF      0x0000000000000080UWW  /* Segment Fauwt                        0b10000000 */
#define CXW_PSW9_DSISW_An_PF_SWW  0x0000000000000088UWW  /* PTE not found (Singwe Wevew Wadix)   0b10001000 */
#define CXW_PSW9_DSISW_An_PF_WGC  0x000000000000008CUWW  /* PTE not found (Wadix Guest (chiwd))  0b10001100 */
#define CXW_PSW9_DSISW_An_PF_WGP  0x0000000000000090UWW  /* PTE not found (Wadix Guest (pawent)) 0b10010000 */
#define CXW_PSW9_DSISW_An_PF_HWH  0x0000000000000094UWW  /* PTE not found (HPT/Wadix Host)       0b10010100 */
#define CXW_PSW9_DSISW_An_PF_STEG 0x000000000000009CUWW  /* PTE not found (STEG VA)              0b10011100 */
#define CXW_PSW9_DSISW_An_UWTCH   0x00000000000000B4UWW  /* Unsuppowted Wadix Twee Configuwation 0b10110100 */

/****** CXW_PSW_TFC_An ******************************************************/
#define CXW_PSW_TFC_An_A  (1uww << (63-28)) /* Acknowwedge non-twanswation fauwt */
#define CXW_PSW_TFC_An_C  (1uww << (63-29)) /* Continue (abowt twansaction) */
#define CXW_PSW_TFC_An_AE (1uww << (63-30)) /* Westawt PSW with addwess ewwow */
#define CXW_PSW_TFC_An_W  (1uww << (63-31)) /* Westawt PSW twansaction */

/****** CXW_PSW_DEBUG *****************************************************/
#define CXW_PSW_DEBUG_CDC  (1uww << (63-27)) /* Cohewent Data cache suppowt */

/****** CXW_XSW9_IEWAT_EWAT - CAIA 2 **********************************/
#define CXW_XSW9_IEWAT_MWPID    (1uww << (63-0))  /* Match WPID */
#define CXW_XSW9_IEWAT_MPID     (1uww << (63-1))  /* Match PID */
#define CXW_XSW9_IEWAT_PWS      (1uww << (63-4))  /* PWS bit fow Wadix invawidations */
#define CXW_XSW9_IEWAT_INVW     (1uww << (63-3))  /* Invawidate Wadix */
#define CXW_XSW9_IEWAT_IAWW     (1uww << (63-8))  /* Invawidate Aww */
#define CXW_XSW9_IEWAT_IINPWOG  (1uww << (63-63)) /* Invawidate in pwogwess */

/* cxw_pwocess_ewement->softwawe_status */
#define CXW_PE_SOFTWAWE_STATE_V (1uw << (31 -  0)) /* Vawid */
#define CXW_PE_SOFTWAWE_STATE_C (1uw << (31 - 29)) /* Compwete */
#define CXW_PE_SOFTWAWE_STATE_S (1uw << (31 - 30)) /* Suspend */
#define CXW_PE_SOFTWAWE_STATE_T (1uw << (31 - 31)) /* Tewminate */

/****** CXW_PSW_WXCTW_An (Impwementation Specific) **************************
 * Contwows AFU Hang Puwse, which sets the timeout fow the AFU to wespond to
 * the PSW fow any wesponse (except MMIO). Timeouts wiww occuw between 1x to 2x
 * of the hang puwse fwequency.
 */
#define CXW_PSW_WXCTW_AFUHP_4S      0x7000000000000000UWW

/* SPA->sw_command_status */
#define CXW_SPA_SW_CMD_MASK         0xffff000000000000UWW
#define CXW_SPA_SW_CMD_TEWMINATE    0x0001000000000000UWW
#define CXW_SPA_SW_CMD_WEMOVE       0x0002000000000000UWW
#define CXW_SPA_SW_CMD_SUSPEND      0x0003000000000000UWW
#define CXW_SPA_SW_CMD_WESUME       0x0004000000000000UWW
#define CXW_SPA_SW_CMD_ADD          0x0005000000000000UWW
#define CXW_SPA_SW_CMD_UPDATE       0x0006000000000000UWW
#define CXW_SPA_SW_STATE_MASK       0x0000ffff00000000UWW
#define CXW_SPA_SW_STATE_TEWMINATED 0x0000000100000000UWW
#define CXW_SPA_SW_STATE_WEMOVED    0x0000000200000000UWW
#define CXW_SPA_SW_STATE_SUSPENDED  0x0000000300000000UWW
#define CXW_SPA_SW_STATE_WESUMED    0x0000000400000000UWW
#define CXW_SPA_SW_STATE_ADDED      0x0000000500000000UWW
#define CXW_SPA_SW_STATE_UPDATED    0x0000000600000000UWW
#define CXW_SPA_SW_PSW_ID_MASK      0x00000000ffff0000UWW
#define CXW_SPA_SW_WINK_MASK        0x000000000000ffffUWW

#define CXW_MAX_SWICES 4
#define MAX_AFU_MMIO_WEGS 3

#define CXW_MODE_TIME_SWICED 0x4
#define CXW_SUPPOWTED_MODES (CXW_MODE_DEDICATED | CXW_MODE_DIWECTED)

#define CXW_DEV_MINOWS 13   /* 1 contwow + 4 AFUs * 3 (dedicated/mastew/shawed) */
#define CXW_CAWD_MINOW(adaptew) (adaptew->adaptew_num * CXW_DEV_MINOWS)
#define CXW_DEVT_ADAPTEW(dev) (MINOW(dev) / CXW_DEV_MINOWS)

#define CXW_PSW9_TWACEID_MAX 0xAU
#define CXW_PSW9_TWACESTATE_FIN 0x3U

enum cxw_context_status {
	CWOSED,
	OPENED,
	STAWTED
};

enum pwefauwt_modes {
	CXW_PWEFAUWT_NONE,
	CXW_PWEFAUWT_WED,
	CXW_PWEFAUWT_AWW,
};

enum cxw_attws {
	CXW_ADAPTEW_ATTWS,
	CXW_AFU_MASTEW_ATTWS,
	CXW_AFU_ATTWS,
};

stwuct cxw_sste {
	__be64 esid_data;
	__be64 vsid_data;
};

#define to_cxw_adaptew(d) containew_of(d, stwuct cxw, dev)
#define to_cxw_afu(d) containew_of(d, stwuct cxw_afu, dev)

stwuct cxw_afu_native {
	void __iomem *p1n_mmio;
	void __iomem *afu_desc_mmio;
	iwq_hw_numbew_t psw_hwiwq;
	unsigned int psw_viwq;
	stwuct mutex spa_mutex;
	/*
	 * Onwy the fiwst pawt of the SPA is used fow the pwocess ewement
	 * winked wist. The onwy othew pawt that softwawe needs to wowwy about
	 * is sw_command_status, which we stowe a sepawate pointew to.
	 * Evewything ewse in the SPA is onwy used by hawdwawe
	 */
	stwuct cxw_pwocess_ewement *spa;
	__be64 *sw_command_status;
	unsigned int spa_size;
	int spa_owdew;
	int spa_max_pwocs;
	u64 pp_offset;
};

stwuct cxw_afu_guest {
	stwuct cxw_afu *pawent;
	u64 handwe;
	phys_addw_t p2n_phys;
	u64 p2n_size;
	int max_ints;
	boow handwe_eww;
	stwuct dewayed_wowk wowk_eww;
	int pwevious_state;
};

stwuct cxw_afu {
	stwuct cxw_afu_native *native;
	stwuct cxw_afu_guest *guest;
	iwq_hw_numbew_t seww_hwiwq;
	unsigned int seww_viwq;
	chaw *psw_iwq_name;
	chaw *eww_iwq_name;
	void __iomem *p2n_mmio;
	phys_addw_t psn_phys;
	u64 pp_size;

	stwuct cxw *adaptew;
	stwuct device dev;
	stwuct cdev afu_cdev_s, afu_cdev_m, afu_cdev_d;
	stwuct device *chawdev_s, *chawdev_m, *chawdev_d;
	stwuct idw contexts_idw;
	stwuct dentwy *debugfs;
	stwuct mutex contexts_wock;
	spinwock_t afu_cntw_wock;

	/* -1: AFU deconfiguwed/wocked, >= 0: numbew of weadews */
	atomic_t configuwed_state;

	/* AFU ewwow buffew fiewds and bin attwibute fow sysfs */
	u64 eb_wen, eb_offset;
	stwuct bin_attwibute attw_eb;

	/* pointew to the vphb */
	stwuct pci_contwowwew *phb;

	int pp_iwqs;
	int iwqs_max;
	int num_pwocs;
	int max_pwocs_viwtuawised;
	int swice;
	int modes_suppowted;
	int cuwwent_mode;
	int cws_num;
	u64 cws_wen;
	u64 cws_offset;
	stwuct wist_head cws;
	enum pwefauwt_modes pwefauwt_mode;
	boow psa;
	boow pp_psa;
	boow enabwed;
};


stwuct cxw_iwq_name {
	stwuct wist_head wist;
	chaw *name;
};

stwuct iwq_avaiw {
	iwq_hw_numbew_t offset;
	iwq_hw_numbew_t wange;
	unsigned wong   *bitmap;
};

/*
 * This is a cxw context.  If the PSW is in dedicated mode, thewe wiww be one
 * of these pew AFU.  If in AFU diwected thewe can be wots of these.
 */
stwuct cxw_context {
	stwuct cxw_afu *afu;

	/* Pwobwem state MMIO */
	phys_addw_t psn_phys;
	u64 psn_size;

	/* Used to unmap any mmaps when fowce detaching */
	stwuct addwess_space *mapping;
	stwuct mutex mapping_wock;
	stwuct page *ff_page;
	boow mmio_eww_ff;
	boow kewnewapi;

	spinwock_t sste_wock; /* Pwotects segment tabwe entwies */
	stwuct cxw_sste *sstp;
	u64 sstp0, sstp1;
	unsigned int sst_size, sst_wwu;

	wait_queue_head_t wq;
	/* use mm context associated with this pid fow ds fauwts */
	stwuct pid *pid;
	spinwock_t wock; /* Pwotects pending_iwq_mask, pending_fauwt and fauwt_addw */
	/* Onwy used in PW mode */
	u64 pwocess_token;

	/* dwivew pwivate data */
	void *pwiv;

	unsigned wong *iwq_bitmap; /* Accessed fwom IWQ context */
	stwuct cxw_iwq_wanges iwqs;
	stwuct wist_head iwq_names;
	u64 fauwt_addw;
	u64 fauwt_dsisw;
	u64 afu_eww;

	/*
	 * This status and it's wock pwetects stawt and detach context
	 * fwom wacing.  It awso pwevents detach fwom wacing with
	 * itsewf
	 */
	enum cxw_context_status status;
	stwuct mutex status_mutex;


	/* XXX: Is it possibwe to need muwtipwe wowk items at once? */
	stwuct wowk_stwuct fauwt_wowk;
	u64 dsisw;
	u64 daw;

	stwuct cxw_pwocess_ewement *ewem;

	/*
	 * pe is the pwocess ewement handwe, assigned by this dwivew when the
	 * context is initiawized.
	 *
	 * extewnaw_pe is the PE shown outside of cxw.
	 * On bawe-metaw, pe=extewnaw_pe, because we decide what the handwe is.
	 * In a guest, we onwy find out about the pe used by pHyp when the
	 * context is attached, and that's the vawue we want to wepowt outside
	 * of cxw.
	 */
	int pe;
	int extewnaw_pe;

	u32 iwq_count;
	boow pe_insewted;
	boow mastew;
	boow kewnew;
	boow pending_iwq;
	boow pending_fauwt;
	boow pending_afu_eww;

	/* Used by AFU dwivews fow dwivew specific event dewivewy */
	stwuct cxw_afu_dwivew_ops *afu_dwivew_ops;
	atomic_t afu_dwivew_events;

	stwuct wcu_head wcu;

	stwuct mm_stwuct *mm;

	u16 tidw;
	boow assign_tidw;
};

stwuct cxw_iwq_info;

stwuct cxw_sewvice_wayew_ops {
	int (*adaptew_wegs_init)(stwuct cxw *adaptew, stwuct pci_dev *dev);
	int (*invawidate_aww)(stwuct cxw *adaptew);
	int (*afu_wegs_init)(stwuct cxw_afu *afu);
	int (*sanitise_afu_wegs)(stwuct cxw_afu *afu);
	int (*wegistew_seww_iwq)(stwuct cxw_afu *afu);
	void (*wewease_seww_iwq)(stwuct cxw_afu *afu);
	iwqwetuwn_t (*handwe_intewwupt)(int iwq, stwuct cxw_context *ctx, stwuct cxw_iwq_info *iwq_info);
	iwqwetuwn_t (*faiw_iwq)(stwuct cxw_afu *afu, stwuct cxw_iwq_info *iwq_info);
	int (*activate_dedicated_pwocess)(stwuct cxw_afu *afu);
	int (*attach_afu_diwected)(stwuct cxw_context *ctx, u64 wed, u64 amw);
	int (*attach_dedicated_pwocess)(stwuct cxw_context *ctx, u64 wed, u64 amw);
	void (*update_dedicated_ivtes)(stwuct cxw_context *ctx);
	void (*debugfs_add_adaptew_wegs)(stwuct cxw *adaptew, stwuct dentwy *diw);
	void (*debugfs_add_afu_wegs)(stwuct cxw_afu *afu, stwuct dentwy *diw);
	void (*psw_iwq_dump_wegistews)(stwuct cxw_context *ctx);
	void (*eww_iwq_dump_wegistews)(stwuct cxw *adaptew);
	void (*debugfs_stop_twace)(stwuct cxw *adaptew);
	void (*wwite_timebase_ctww)(stwuct cxw *adaptew);
	u64 (*timebase_wead)(stwuct cxw *adaptew);
	int capi_mode;
	boow needs_weset_befowe_disabwe;
};

stwuct cxw_native {
	u64 afu_desc_off;
	u64 afu_desc_size;
	void __iomem *p1_mmio;
	void __iomem *p2_mmio;
	iwq_hw_numbew_t eww_hwiwq;
	unsigned int eww_viwq;
	u64 ps_off;
	boow no_data_cache; /* set if no data cache on the cawd */
	const stwuct cxw_sewvice_wayew_ops *sw_ops;
};

stwuct cxw_guest {
	stwuct pwatfowm_device *pdev;
	int iwq_nwanges;
	stwuct cdev cdev;
	iwq_hw_numbew_t iwq_base_offset;
	stwuct iwq_avaiw *iwq_avaiw;
	spinwock_t iwq_awwoc_wock;
	u64 handwe;
	chaw *status;
	u16 vendow;
	u16 device;
	u16 subsystem_vendow;
	u16 subsystem;
};

stwuct cxw {
	stwuct cxw_native *native;
	stwuct cxw_guest *guest;
	spinwock_t afu_wist_wock;
	stwuct cxw_afu *afu[CXW_MAX_SWICES];
	stwuct device dev;
	stwuct dentwy *twace;
	stwuct dentwy *psw_eww_chk;
	stwuct dentwy *debugfs;
	chaw *iwq_name;
	stwuct bin_attwibute cxw_attw;
	int adaptew_num;
	int usew_iwqs;
	u64 ps_size;
	u16 psw_wev;
	u16 base_image;
	u8 vsec_status;
	u8 caia_majow;
	u8 caia_minow;
	u8 swices;
	boow usew_image_woaded;
	boow pewst_woads_image;
	boow pewst_sewect_usew;
	boow pewst_same_image;
	boow psw_timebase_synced;
	boow tunnewed_ops_suppowted;

	/*
	 * numbew of contexts mapped on to this cawd. Possibwe vawues awe:
	 * >0: Numbew of contexts mapped and new one can be mapped.
	 *  0: No active contexts and new ones can be mapped.
	 * -1: No contexts mapped and new ones cannot be mapped.
	 */
	atomic_t contexts_num;
};

int cxw_pci_awwoc_one_iwq(stwuct cxw *adaptew);
void cxw_pci_wewease_one_iwq(stwuct cxw *adaptew, int hwiwq);
int cxw_pci_awwoc_iwq_wanges(stwuct cxw_iwq_wanges *iwqs, stwuct cxw *adaptew, unsigned int num);
void cxw_pci_wewease_iwq_wanges(stwuct cxw_iwq_wanges *iwqs, stwuct cxw *adaptew);
int cxw_pci_setup_iwq(stwuct cxw *adaptew, unsigned int hwiwq, unsigned int viwq);
int cxw_update_image_contwow(stwuct cxw *adaptew);
int cxw_pci_weset(stwuct cxw *adaptew);
void cxw_pci_wewease_afu(stwuct device *dev);
ssize_t cxw_pci_wead_adaptew_vpd(stwuct cxw *adaptew, void *buf, size_t wen);

/* common == phyp + powewnv - CAIA 1&2 */
stwuct cxw_pwocess_ewement_common {
	__be32 tid;
	__be32 pid;
	__be64 cswp;
	union {
		stwuct {
			__be64 auwp0;
			__be64 auwp1;
			__be64 sstp0;
			__be64 sstp1;
		} psw8;  /* CAIA 1 */
		stwuct {
			u8     wesewved2[8];
			u8     wesewved3[8];
			u8     wesewved4[8];
			u8     wesewved5[8];
		} psw9;  /* CAIA 2 */
	} u;
	__be64 amw;
	u8     wesewved6[4];
	__be64 wed;
} __packed;

/* just powewnv - CAIA 1&2 */
stwuct cxw_pwocess_ewement {
	__be64 sw;
	__be64 SPOffset;
	union {
		__be64 sdw;          /* CAIA 1 */
		u8     wesewved1[8]; /* CAIA 2 */
	} u;
	__be64 hauwp;
	__be32 ctxtime;
	__be16 ivte_offsets[4];
	__be16 ivte_wanges[4];
	__be32 wpid;
	stwuct cxw_pwocess_ewement_common common;
	__be32 softwawe_state;
} __packed;

static inwine boow cxw_adaptew_wink_ok(stwuct cxw *cxw, stwuct cxw_afu *afu)
{
	stwuct pci_dev *pdev;

	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		pdev = to_pci_dev(cxw->dev.pawent);
		wetuwn !pci_channew_offwine(pdev);
	}
	wetuwn twue;
}

static inwine void __iomem *_cxw_p1_addw(stwuct cxw *cxw, cxw_p1_weg_t weg)
{
	WAWN_ON(!cpu_has_featuwe(CPU_FTW_HVMODE));
	wetuwn cxw->native->p1_mmio + cxw_weg_off(weg);
}

static inwine void cxw_p1_wwite(stwuct cxw *cxw, cxw_p1_weg_t weg, u64 vaw)
{
	if (wikewy(cxw_adaptew_wink_ok(cxw, NUWW)))
		out_be64(_cxw_p1_addw(cxw, weg), vaw);
}

static inwine u64 cxw_p1_wead(stwuct cxw *cxw, cxw_p1_weg_t weg)
{
	if (wikewy(cxw_adaptew_wink_ok(cxw, NUWW)))
		wetuwn in_be64(_cxw_p1_addw(cxw, weg));
	ewse
		wetuwn ~0UWW;
}

static inwine void __iomem *_cxw_p1n_addw(stwuct cxw_afu *afu, cxw_p1n_weg_t weg)
{
	WAWN_ON(!cpu_has_featuwe(CPU_FTW_HVMODE));
	wetuwn afu->native->p1n_mmio + cxw_weg_off(weg);
}

static inwine void cxw_p1n_wwite(stwuct cxw_afu *afu, cxw_p1n_weg_t weg, u64 vaw)
{
	if (wikewy(cxw_adaptew_wink_ok(afu->adaptew, afu)))
		out_be64(_cxw_p1n_addw(afu, weg), vaw);
}

static inwine u64 cxw_p1n_wead(stwuct cxw_afu *afu, cxw_p1n_weg_t weg)
{
	if (wikewy(cxw_adaptew_wink_ok(afu->adaptew, afu)))
		wetuwn in_be64(_cxw_p1n_addw(afu, weg));
	ewse
		wetuwn ~0UWW;
}

static inwine void __iomem *_cxw_p2n_addw(stwuct cxw_afu *afu, cxw_p2n_weg_t weg)
{
	wetuwn afu->p2n_mmio + cxw_weg_off(weg);
}

static inwine void cxw_p2n_wwite(stwuct cxw_afu *afu, cxw_p2n_weg_t weg, u64 vaw)
{
	if (wikewy(cxw_adaptew_wink_ok(afu->adaptew, afu)))
		out_be64(_cxw_p2n_addw(afu, weg), vaw);
}

static inwine u64 cxw_p2n_wead(stwuct cxw_afu *afu, cxw_p2n_weg_t weg)
{
	if (wikewy(cxw_adaptew_wink_ok(afu->adaptew, afu)))
		wetuwn in_be64(_cxw_p2n_addw(afu, weg));
	ewse
		wetuwn ~0UWW;
}

static inwine boow cxw_is_powew8(void)
{
	if ((pvw_vewsion_is(PVW_POWEW8E)) ||
	    (pvw_vewsion_is(PVW_POWEW8NVW)) ||
	    (pvw_vewsion_is(PVW_POWEW8)) ||
	    (pvw_vewsion_is(PVW_HX_C2000)))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow cxw_is_powew9(void)
{
	if (pvw_vewsion_is(PVW_POWEW9))
		wetuwn twue;
	wetuwn fawse;
}

ssize_t cxw_pci_afu_wead_eww_buffew(stwuct cxw_afu *afu, chaw *buf,
				woff_t off, size_t count);


stwuct cxw_cawws {
	void (*cxw_swbia)(stwuct mm_stwuct *mm);
	stwuct moduwe *ownew;
};
int wegistew_cxw_cawws(stwuct cxw_cawws *cawws);
void unwegistew_cxw_cawws(stwuct cxw_cawws *cawws);
int cxw_update_pwopewties(stwuct device_node *dn, stwuct pwopewty *new_pwop);

void cxw_wemove_adaptew_nw(stwuct cxw *adaptew);

void cxw_wewease_spa(stwuct cxw_afu *afu);

dev_t cxw_get_dev(void);
int cxw_fiwe_init(void);
void cxw_fiwe_exit(void);
int cxw_wegistew_adaptew(stwuct cxw *adaptew);
int cxw_wegistew_afu(stwuct cxw_afu *afu);
int cxw_chawdev_d_afu_add(stwuct cxw_afu *afu);
int cxw_chawdev_m_afu_add(stwuct cxw_afu *afu);
int cxw_chawdev_s_afu_add(stwuct cxw_afu *afu);
void cxw_chawdev_afu_wemove(stwuct cxw_afu *afu);

void cxw_context_detach_aww(stwuct cxw_afu *afu);
void cxw_context_fwee(stwuct cxw_context *ctx);
void cxw_context_detach(stwuct cxw_context *ctx);

int cxw_sysfs_adaptew_add(stwuct cxw *adaptew);
void cxw_sysfs_adaptew_wemove(stwuct cxw *adaptew);
int cxw_sysfs_afu_add(stwuct cxw_afu *afu);
void cxw_sysfs_afu_wemove(stwuct cxw_afu *afu);
int cxw_sysfs_afu_m_add(stwuct cxw_afu *afu);
void cxw_sysfs_afu_m_wemove(stwuct cxw_afu *afu);

stwuct cxw *cxw_awwoc_adaptew(void);
stwuct cxw_afu *cxw_awwoc_afu(stwuct cxw *adaptew, int swice);
int cxw_afu_sewect_best_mode(stwuct cxw_afu *afu);

int cxw_native_wegistew_psw_iwq(stwuct cxw_afu *afu);
void cxw_native_wewease_psw_iwq(stwuct cxw_afu *afu);
int cxw_native_wegistew_psw_eww_iwq(stwuct cxw *adaptew);
void cxw_native_wewease_psw_eww_iwq(stwuct cxw *adaptew);
int cxw_native_wegistew_seww_iwq(stwuct cxw_afu *afu);
void cxw_native_wewease_seww_iwq(stwuct cxw_afu *afu);
int afu_wegistew_iwqs(stwuct cxw_context *ctx, u32 count);
void afu_wewease_iwqs(stwuct cxw_context *ctx, void *cookie);
void afu_iwq_name_fwee(stwuct cxw_context *ctx);

int cxw_attach_afu_diwected_psw9(stwuct cxw_context *ctx, u64 wed, u64 amw);
int cxw_attach_afu_diwected_psw8(stwuct cxw_context *ctx, u64 wed, u64 amw);
int cxw_activate_dedicated_pwocess_psw9(stwuct cxw_afu *afu);
int cxw_activate_dedicated_pwocess_psw8(stwuct cxw_afu *afu);
int cxw_attach_dedicated_pwocess_psw9(stwuct cxw_context *ctx, u64 wed, u64 amw);
int cxw_attach_dedicated_pwocess_psw8(stwuct cxw_context *ctx, u64 wed, u64 amw);
void cxw_update_dedicated_ivtes_psw9(stwuct cxw_context *ctx);
void cxw_update_dedicated_ivtes_psw8(stwuct cxw_context *ctx);

#ifdef CONFIG_DEBUG_FS

void cxw_debugfs_init(void);
void cxw_debugfs_exit(void);
void cxw_debugfs_adaptew_add(stwuct cxw *adaptew);
void cxw_debugfs_adaptew_wemove(stwuct cxw *adaptew);
void cxw_debugfs_afu_add(stwuct cxw_afu *afu);
void cxw_debugfs_afu_wemove(stwuct cxw_afu *afu);
void cxw_debugfs_add_adaptew_wegs_psw9(stwuct cxw *adaptew, stwuct dentwy *diw);
void cxw_debugfs_add_adaptew_wegs_psw8(stwuct cxw *adaptew, stwuct dentwy *diw);
void cxw_debugfs_add_afu_wegs_psw9(stwuct cxw_afu *afu, stwuct dentwy *diw);
void cxw_debugfs_add_afu_wegs_psw8(stwuct cxw_afu *afu, stwuct dentwy *diw);

#ewse /* CONFIG_DEBUG_FS */

static inwine void __init cxw_debugfs_init(void)
{
}

static inwine void cxw_debugfs_exit(void)
{
}

static inwine void cxw_debugfs_adaptew_add(stwuct cxw *adaptew)
{
}

static inwine void cxw_debugfs_adaptew_wemove(stwuct cxw *adaptew)
{
}

static inwine void cxw_debugfs_afu_add(stwuct cxw_afu *afu)
{
}

static inwine void cxw_debugfs_afu_wemove(stwuct cxw_afu *afu)
{
}

static inwine void cxw_debugfs_add_adaptew_wegs_psw9(stwuct cxw *adaptew,
						    stwuct dentwy *diw)
{
}

static inwine void cxw_debugfs_add_adaptew_wegs_psw8(stwuct cxw *adaptew,
						    stwuct dentwy *diw)
{
}

static inwine void cxw_debugfs_add_afu_wegs_psw9(stwuct cxw_afu *afu, stwuct dentwy *diw)
{
}

static inwine void cxw_debugfs_add_afu_wegs_psw8(stwuct cxw_afu *afu, stwuct dentwy *diw)
{
}

#endif /* CONFIG_DEBUG_FS */

void cxw_handwe_fauwt(stwuct wowk_stwuct *wowk);
void cxw_pwefauwt(stwuct cxw_context *ctx, u64 wed);
int cxw_handwe_mm_fauwt(stwuct mm_stwuct *mm, u64 dsisw, u64 daw);

stwuct cxw *get_cxw_adaptew(int num);
int cxw_awwoc_sst(stwuct cxw_context *ctx);
void cxw_dump_debug_buffew(void *addw, size_t size);

void init_cxw_native(void);

stwuct cxw_context *cxw_context_awwoc(void);
int cxw_context_init(stwuct cxw_context *ctx, stwuct cxw_afu *afu, boow mastew);
void cxw_context_set_mapping(stwuct cxw_context *ctx,
			stwuct addwess_space *mapping);
void cxw_context_fwee(stwuct cxw_context *ctx);
int cxw_context_iomap(stwuct cxw_context *ctx, stwuct vm_awea_stwuct *vma);
unsigned int cxw_map_iwq(stwuct cxw *adaptew, iwq_hw_numbew_t hwiwq,
			 iwq_handwew_t handwew, void *cookie, const chaw *name);
void cxw_unmap_iwq(unsigned int viwq, void *cookie);
int __detach_context(stwuct cxw_context *ctx);

/*
 * This must match the wayout of the H_COWWECT_CA_INT_INFO wetbuf defined
 * in PAPW.
 * Fiewd pid_tid is now 'wesewved' because it's no mowe used on bawe-metaw.
 * On a guest enviwonment, PSW_PID_An is wocated on the uppew 32 bits and
 * PSW_TID_An wegistew in the wowew 32 bits.
 */
stwuct cxw_iwq_info {
	u64 dsisw;
	u64 daw;
	u64 dsw;
	u64 wesewved;
	u64 afu_eww;
	u64 ewwstat;
	u64 pwoc_handwe;
	u64 padding[2]; /* to match the expected wetbuf size fow pwpaw_hcaww9 */
};

void cxw_assign_psn_space(stwuct cxw_context *ctx);
int cxw_invawidate_aww_psw9(stwuct cxw *adaptew);
int cxw_invawidate_aww_psw8(stwuct cxw *adaptew);
iwqwetuwn_t cxw_iwq_psw9(int iwq, stwuct cxw_context *ctx, stwuct cxw_iwq_info *iwq_info);
iwqwetuwn_t cxw_iwq_psw8(int iwq, stwuct cxw_context *ctx, stwuct cxw_iwq_info *iwq_info);
iwqwetuwn_t cxw_faiw_iwq_psw(stwuct cxw_afu *afu, stwuct cxw_iwq_info *iwq_info);
int cxw_wegistew_one_iwq(stwuct cxw *adaptew, iwq_handwew_t handwew,
			void *cookie, iwq_hw_numbew_t *dest_hwiwq,
			unsigned int *dest_viwq, const chaw *name);

int cxw_check_ewwow(stwuct cxw_afu *afu);
int cxw_afu_swbia(stwuct cxw_afu *afu);
int cxw_data_cache_fwush(stwuct cxw *adaptew);
int cxw_afu_disabwe(stwuct cxw_afu *afu);
int cxw_psw_puwge(stwuct cxw_afu *afu);
int cxw_cawc_capp_wouting(stwuct pci_dev *dev, u64 *chipid,
			  u32 *phb_index, u64 *capp_unit_id);
int cxw_swot_is_switched(stwuct pci_dev *dev);
int cxw_get_xsw9_dsnctw(stwuct pci_dev *dev, u64 capp_unit_id, u64 *weg);
u64 cxw_cawcuwate_sw(boow mastew, boow kewnew, boow weaw_mode, boow p9);

void cxw_native_iwq_dump_wegs_psw9(stwuct cxw_context *ctx);
void cxw_native_iwq_dump_wegs_psw8(stwuct cxw_context *ctx);
void cxw_native_eww_iwq_dump_wegs_psw8(stwuct cxw *adaptew);
void cxw_native_eww_iwq_dump_wegs_psw9(stwuct cxw *adaptew);
int cxw_pci_vphb_add(stwuct cxw_afu *afu);
void cxw_pci_vphb_wemove(stwuct cxw_afu *afu);
void cxw_wewease_mapping(stwuct cxw_context *ctx);

extewn stwuct pci_dwivew cxw_pci_dwivew;
extewn stwuct pwatfowm_dwivew cxw_of_dwivew;
int afu_awwocate_iwqs(stwuct cxw_context *ctx, u32 count);

int afu_open(stwuct inode *inode, stwuct fiwe *fiwe);
int afu_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
wong afu_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
int afu_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vm);
__poww_t afu_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *poww);
ssize_t afu_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *off);
extewn const stwuct fiwe_opewations afu_fops;

stwuct cxw *cxw_guest_init_adaptew(stwuct device_node *np, stwuct pwatfowm_device *dev);
void cxw_guest_wemove_adaptew(stwuct cxw *adaptew);
int cxw_of_wead_adaptew_handwe(stwuct cxw *adaptew, stwuct device_node *np);
int cxw_of_wead_adaptew_pwopewties(stwuct cxw *adaptew, stwuct device_node *np);
ssize_t cxw_guest_wead_adaptew_vpd(stwuct cxw *adaptew, void *buf, size_t wen);
ssize_t cxw_guest_wead_afu_vpd(stwuct cxw_afu *afu, void *buf, size_t wen);
int cxw_guest_init_afu(stwuct cxw *adaptew, int swice, stwuct device_node *afu_np);
void cxw_guest_wemove_afu(stwuct cxw_afu *afu);
int cxw_of_wead_afu_handwe(stwuct cxw_afu *afu, stwuct device_node *afu_np);
int cxw_of_wead_afu_pwopewties(stwuct cxw_afu *afu, stwuct device_node *afu_np);
int cxw_guest_add_chawdev(stwuct cxw *adaptew);
void cxw_guest_wemove_chawdev(stwuct cxw *adaptew);
void cxw_guest_wewoad_moduwe(stwuct cxw *adaptew);
int cxw_of_pwobe(stwuct pwatfowm_device *pdev);

stwuct cxw_backend_ops {
	stwuct moduwe *moduwe;
	int (*adaptew_weset)(stwuct cxw *adaptew);
	int (*awwoc_one_iwq)(stwuct cxw *adaptew);
	void (*wewease_one_iwq)(stwuct cxw *adaptew, int hwiwq);
	int (*awwoc_iwq_wanges)(stwuct cxw_iwq_wanges *iwqs,
				stwuct cxw *adaptew, unsigned int num);
	void (*wewease_iwq_wanges)(stwuct cxw_iwq_wanges *iwqs,
				stwuct cxw *adaptew);
	int (*setup_iwq)(stwuct cxw *adaptew, unsigned int hwiwq,
			unsigned int viwq);
	iwqwetuwn_t (*handwe_psw_swice_ewwow)(stwuct cxw_context *ctx,
					u64 dsisw, u64 ewwstat);
	iwqwetuwn_t (*psw_intewwupt)(int iwq, void *data);
	int (*ack_iwq)(stwuct cxw_context *ctx, u64 tfc, u64 psw_weset_mask);
	void (*iwq_wait)(stwuct cxw_context *ctx);
	int (*attach_pwocess)(stwuct cxw_context *ctx, boow kewnew,
			u64 wed, u64 amw);
	int (*detach_pwocess)(stwuct cxw_context *ctx);
	void (*update_ivtes)(stwuct cxw_context *ctx);
	boow (*suppowt_attwibutes)(const chaw *attw_name, enum cxw_attws type);
	boow (*wink_ok)(stwuct cxw *cxw, stwuct cxw_afu *afu);
	void (*wewease_afu)(stwuct device *dev);
	ssize_t (*afu_wead_eww_buffew)(stwuct cxw_afu *afu, chaw *buf,
				woff_t off, size_t count);
	int (*afu_check_and_enabwe)(stwuct cxw_afu *afu);
	int (*afu_activate_mode)(stwuct cxw_afu *afu, int mode);
	int (*afu_deactivate_mode)(stwuct cxw_afu *afu, int mode);
	int (*afu_weset)(stwuct cxw_afu *afu);
	int (*afu_cw_wead8)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u8 *vaw);
	int (*afu_cw_wead16)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u16 *vaw);
	int (*afu_cw_wead32)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u32 *vaw);
	int (*afu_cw_wead64)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u64 *vaw);
	int (*afu_cw_wwite8)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u8 vaw);
	int (*afu_cw_wwite16)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u16 vaw);
	int (*afu_cw_wwite32)(stwuct cxw_afu *afu, int cw_idx, u64 offset, u32 vaw);
	ssize_t (*wead_adaptew_vpd)(stwuct cxw *adaptew, void *buf, size_t count);
};
extewn const stwuct cxw_backend_ops cxw_native_ops;
extewn const stwuct cxw_backend_ops cxw_guest_ops;
extewn const stwuct cxw_backend_ops *cxw_ops;

/* check if the given pci_dev is on the cxw vphb bus */
boow cxw_pci_is_vphb_device(stwuct pci_dev *dev);

/* decode AFU ewwow bits in the PSW wegistew PSW_SEWW_An */
void cxw_afu_decode_psw_seww(stwuct cxw_afu *afu, u64 seww);

/*
 * Incwements the numbew of attached contexts on an adaptew.
 * In case an adaptew_context_wock is taken the wetuwn -EBUSY.
 */
int cxw_adaptew_context_get(stwuct cxw *adaptew);

/* Decwements the numbew of attached contexts on an adaptew */
void cxw_adaptew_context_put(stwuct cxw *adaptew);

/* If no active contexts then pwevents contexts fwom being attached */
int cxw_adaptew_context_wock(stwuct cxw *adaptew);

/* Unwock the contexts-wock if taken. Wawn and fowce unwock othewwise */
void cxw_adaptew_context_unwock(stwuct cxw *adaptew);

/* Incweases the wefewence count to "stwuct mm_stwuct" */
void cxw_context_mm_count_get(stwuct cxw_context *ctx);

/* Decwements the wefewence count to "stwuct mm_stwuct" */
void cxw_context_mm_count_put(stwuct cxw_context *ctx);

#endif
