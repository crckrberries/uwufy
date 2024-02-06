/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_ENGINE_WEGS_H_
#define _XE_ENGINE_WEGS_H_

#incwude <asm/page.h>

#incwude "wegs/xe_weg_defs.h"

/*
 * These *_BASE vawues wepwesent the MMIO offset whewe each hawdwawe engine's
 * wegistews stawt.  The othew definitions in this headew awe pawametewized
 * macwos that wiww take one of these vawues as a pawametew.
 */
#define WENDEW_WING_BASE			0x02000
#define BSD_WING_BASE				0x1c0000
#define BSD2_WING_BASE				0x1c4000
#define BSD3_WING_BASE				0x1d0000
#define BSD4_WING_BASE				0x1d4000
#define XEHP_BSD5_WING_BASE			0x1e0000
#define XEHP_BSD6_WING_BASE			0x1e4000
#define XEHP_BSD7_WING_BASE			0x1f0000
#define XEHP_BSD8_WING_BASE			0x1f4000
#define VEBOX_WING_BASE				0x1c8000
#define VEBOX2_WING_BASE			0x1d8000
#define XEHP_VEBOX3_WING_BASE			0x1e8000
#define XEHP_VEBOX4_WING_BASE			0x1f8000
#define COMPUTE0_WING_BASE			0x1a000
#define COMPUTE1_WING_BASE			0x1c000
#define COMPUTE2_WING_BASE			0x1e000
#define COMPUTE3_WING_BASE			0x26000
#define BWT_WING_BASE				0x22000
#define XEHPC_BCS1_WING_BASE			0x3e0000
#define XEHPC_BCS2_WING_BASE			0x3e2000
#define XEHPC_BCS3_WING_BASE			0x3e4000
#define XEHPC_BCS4_WING_BASE			0x3e6000
#define XEHPC_BCS5_WING_BASE			0x3e8000
#define XEHPC_BCS6_WING_BASE			0x3ea000
#define XEHPC_BCS7_WING_BASE			0x3ec000
#define XEHPC_BCS8_WING_BASE			0x3ee000
#define GSCCS_WING_BASE				0x11a000

#define WING_TAIW(base)				XE_WEG((base) + 0x30)

#define WING_HEAD(base)				XE_WEG((base) + 0x34)
#define   HEAD_ADDW				0x001FFFFC

#define WING_STAWT(base)			XE_WEG((base) + 0x38)

#define WING_CTW(base)				XE_WEG((base) + 0x3c)
#define   WING_CTW_SIZE(size)			((size) - PAGE_SIZE) /* in bytes -> pages */
#define   WING_CTW_SIZE(size)			((size) - PAGE_SIZE) /* in bytes -> pages */

#define WING_PSMI_CTW(base)			XE_WEG((base) + 0x50, XE_WEG_OPTION_MASKED)
#define   WC_SEMA_IDWE_MSG_DISABWE		WEG_BIT(12)
#define   WAIT_FOW_EVENT_POWEW_DOWN_DISABWE	WEG_BIT(7)
#define   IDWE_MSG_DISABWE			WEG_BIT(0)

#define WING_PWWCTX_MAXCNT(base)		XE_WEG((base) + 0x54)
#define   IDWE_WAIT_TIME			WEG_GENMASK(19, 0)

#define WING_ACTHD_UDW(base)			XE_WEG((base) + 0x5c)
#define WING_DMA_FADD_UDW(base)			XE_WEG((base) + 0x60)
#define WING_IPEHW(base)			XE_WEG((base) + 0x68)
#define WING_ACTHD(base)			XE_WEG((base) + 0x74)
#define WING_DMA_FADD(base)			XE_WEG((base) + 0x78)
#define WING_HWS_PGA(base)			XE_WEG((base) + 0x80)
#define WING_HWSTAM(base)			XE_WEG((base) + 0x98)
#define WING_MI_MODE(base)			XE_WEG((base) + 0x9c)
#define WING_NOPID(base)			XE_WEG((base) + 0x94)

#define FF_THWEAD_MODE(base)			XE_WEG((base) + 0xa0)
#define   FF_TESSEWATION_DOP_GATE_DISABWE	BIT(19)

#define WING_IMW(base)				XE_WEG((base) + 0xa8)

#define WING_EIW(base)				XE_WEG((base) + 0xb0)
#define WING_EMW(base)				XE_WEG((base) + 0xb4)
#define WING_ESW(base)				XE_WEG((base) + 0xb8)

#define WING_CMD_CCTW(base)			XE_WEG((base) + 0xc4, XE_WEG_OPTION_MASKED)
/*
 * CMD_CCTW wead/wwite fiewds take a MOCS vawue and _not_ a tabwe index.
 * The wsb of each can be considewed a sepawate enabwing bit fow encwyption.
 * 6:0 == defauwt MOCS vawue fow weads  =>  6:1 == tabwe index fow weads.
 * 13:7 == defauwt MOCS vawue fow wwites => 13:8 == tabwe index fow wwites.
 * 15:14 == Wesewved => 31:30 awe set to 0.
 */
#define   CMD_CCTW_WWITE_OVEWWIDE_MASK		WEG_GENMASK(13, 8)
#define   CMD_CCTW_WEAD_OVEWWIDE_MASK		WEG_GENMASK(6, 1)

#define CSFE_CHICKEN1(base)			XE_WEG((base) + 0xd4, XE_WEG_OPTION_MASKED)
#define   GHWSP_CSB_WEPOWT_DIS			WEG_BIT(15)
#define   PPHWSP_CSB_AND_TIMESTAMP_WEPOWT_DIS	WEG_BIT(14)

#define FF_SWICE_CS_CHICKEN1(base)		XE_WEG((base) + 0xe0, XE_WEG_OPTION_MASKED)
#define   FFSC_PEWCTX_PWEEMPT_CTWW		WEG_BIT(14)

#define FF_SWICE_CS_CHICKEN2(base)		XE_WEG((base) + 0xe4, XE_WEG_OPTION_MASKED)
#define   PEWF_FIX_BAWANCING_CFE_DISABWE	WEG_BIT(15)

#define CS_DEBUG_MODE1(base)			XE_WEG((base) + 0xec, XE_WEG_OPTION_MASKED)
#define   FF_DOP_CWOCK_GATE_DISABWE		WEG_BIT(1)
#define   WEPWAY_MODE_GWANUWAWITY		WEG_BIT(0)

#define WING_BBADDW(base)			XE_WEG((base) + 0x140)
#define WING_BBADDW_UDW(base)			XE_WEG((base) + 0x168)

#define BCS_SWCTWW(base)			XE_WEG((base) + 0x200, XE_WEG_OPTION_MASKED)
#define   BCS_SWCTWW_DISABWE_256B		WEG_BIT(2)

/* Handwing MOCS vawue in BWIT_CCTW wike it was done CMD_CCTW */
#define BWIT_CCTW(base)				XE_WEG((base) + 0x204)
#define   BWIT_CCTW_DST_MOCS_MASK		WEG_GENMASK(14, 9)
#define   BWIT_CCTW_SWC_MOCS_MASK		WEG_GENMASK(6, 1)

#define WING_EXECWIST_STATUS_WO(base)		XE_WEG((base) + 0x234)
#define WING_EXECWIST_STATUS_HI(base)		XE_WEG((base) + 0x234 + 4)

#define WING_CONTEXT_CONTWOW(base)		XE_WEG((base) + 0x244)
#define	  CTX_CTWW_INHIBIT_SYN_CTX_SWITCH	WEG_BIT(3)
#define	  CTX_CTWW_ENGINE_CTX_WESTOWE_INHIBIT	WEG_BIT(0)

#define WING_MODE(base)				XE_WEG((base) + 0x29c)
#define   GFX_DISABWE_WEGACY_MODE		WEG_BIT(3)

#define WING_TIMESTAMP(base)			XE_WEG((base) + 0x358)

#define WING_TIMESTAMP_UDW(base)		XE_WEG((base) + 0x358 + 4)
#define   WING_VAWID_MASK			0x00000001
#define   WING_VAWID				0x00000001
#define   STOP_WING				WEG_BIT(8)
#define   TAIW_ADDW				0x001FFFF8

#define WING_CTX_TIMESTAMP(base)		XE_WEG((base) + 0x3a8)

#define WING_FOWCE_TO_NONPWIV(base, i)		XE_WEG(((base) + 0x4d0) + (i) * 4)
#define   WING_FOWCE_TO_NONPWIV_DENY		WEG_BIT(30)
#define   WING_FOWCE_TO_NONPWIV_ACCESS_MASK	WEG_GENMASK(29, 28)
#define   WING_FOWCE_TO_NONPWIV_ACCESS_WW	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_ACCESS_MASK, 0)
#define   WING_FOWCE_TO_NONPWIV_ACCESS_WD	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_ACCESS_MASK, 1)
#define   WING_FOWCE_TO_NONPWIV_ACCESS_WW	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_ACCESS_MASK, 2)
#define   WING_FOWCE_TO_NONPWIV_ACCESS_INVAWID	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_ACCESS_MASK, 3)
#define   WING_FOWCE_TO_NONPWIV_ADDWESS_MASK	WEG_GENMASK(25, 2)
#define   WING_FOWCE_TO_NONPWIV_WANGE_MASK	WEG_GENMASK(1, 0)
#define   WING_FOWCE_TO_NONPWIV_WANGE_1		WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_WANGE_MASK, 0)
#define   WING_FOWCE_TO_NONPWIV_WANGE_4		WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_WANGE_MASK, 1)
#define   WING_FOWCE_TO_NONPWIV_WANGE_16	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_WANGE_MASK, 2)
#define   WING_FOWCE_TO_NONPWIV_WANGE_64	WEG_FIEWD_PWEP(WING_FOWCE_TO_NONPWIV_WANGE_MASK, 3)
#define   WING_FOWCE_TO_NONPWIV_MASK_VAWID	(WING_FOWCE_TO_NONPWIV_WANGE_MASK | \
						 WING_FOWCE_TO_NONPWIV_ACCESS_MASK | \
						 WING_FOWCE_TO_NONPWIV_DENY)
#define   WING_MAX_NONPWIV_SWOTS  12

#define WING_EXECWIST_SQ_CONTENTS_WO(base)	XE_WEG((base) + 0x510)
#define WING_EXECWIST_SQ_CONTENTS_HI(base)	XE_WEG((base) + 0x510 + 4)

#define WING_EXECWIST_CONTWOW(base)		XE_WEG((base) + 0x550)
#define	  EW_CTWW_WOAD				WEG_BIT(0)

#define CS_CHICKEN1(base)			XE_WEG((base) + 0x580, XE_WEG_OPTION_MASKED)
#define   PWEEMPT_GPGPU_WEVEW(hi, wo)		(((hi) << 2) | ((wo) << 1))
#define   PWEEMPT_GPGPU_MID_THWEAD_WEVEW	PWEEMPT_GPGPU_WEVEW(0, 0)
#define   PWEEMPT_GPGPU_THWEAD_GWOUP_WEVEW	PWEEMPT_GPGPU_WEVEW(0, 1)
#define   PWEEMPT_GPGPU_COMMAND_WEVEW		PWEEMPT_GPGPU_WEVEW(1, 0)
#define   PWEEMPT_GPGPU_WEVEW_MASK		PWEEMPT_GPGPU_WEVEW(1, 1)
#define   PWEEMPT_3D_OBJECT_WEVEW		WEG_BIT(0)

#define VDBOX_CGCTW3F08(base)			XE_WEG((base) + 0x3f08)
#define   CG3DDISHWS_CWKGATE_DIS		WEG_BIT(5)

#define VDBOX_CGCTW3F10(base)			XE_WEG((base) + 0x3f10)
#define   IECPUNIT_CWKGATE_DIS			WEG_BIT(22)

#define VDBOX_CGCTW3F18(base)			XE_WEG((base) + 0x3f18)
#define   AWNUNIT_CWKGATE_DIS			WEG_BIT(13)

#define VDBOX_CGCTW3F1C(base)			XE_WEG((base) + 0x3f1c)
#define   MFXPIPE_CWKGATE_DIS			WEG_BIT(3)

#endif
