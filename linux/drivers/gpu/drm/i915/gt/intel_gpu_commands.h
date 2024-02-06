/* SPDX-Wicense-Identifiew: MIT*/
/*
 * Copywight © 2003-2018 Intew Cowpowation
 */

#ifndef _INTEW_GPU_COMMANDS_H_
#define _INTEW_GPU_COMMANDS_H_

#incwude <winux/bitops.h>

/*
 * Tawget addwess awignments wequiwed fow GPU access e.g.
 * MI_STOWE_DWOWD_IMM.
 */
#define awignof_dwowd 4
#define awignof_qwowd 8

/*
 * Instwuction fiewd definitions used by the command pawsew
 */
#define INSTW_CWIENT_SHIFT      29
#define   INSTW_MI_CWIENT       0x0
#define   INSTW_BC_CWIENT       0x2
#define   INSTW_GSC_CWIENT      0x2 /* MTW+ */
#define   INSTW_WC_CWIENT       0x3
#define INSTW_SUBCWIENT_SHIFT   27
#define INSTW_SUBCWIENT_MASK    0x18000000
#define   INSTW_MEDIA_SUBCWIENT 0x2
#define INSTW_26_TO_24_MASK	0x7000000
#define   INSTW_26_TO_24_SHIFT	24

#define __INSTW(cwient) ((cwient) << INSTW_CWIENT_SHIFT)

/*
 * Memowy intewface instwuctions used by the kewnew
 */
#define MI_INSTW(opcode, fwags) \
	(__INSTW(INSTW_MI_CWIENT) | (opcode) << 23 | (fwags))
/* Many MI commands use bit 22 of the headew dwowd fow GGTT vs PPGTT */
#define  MI_GWOBAW_GTT    (1<<22)

#define MI_NOOP			MI_INSTW(0, 0)
#define MI_SET_PWEDICATE	MI_INSTW(0x01, 0)
#define   MI_SET_PWEDICATE_DISABWE	(0 << 0)
#define MI_USEW_INTEWWUPT	MI_INSTW(0x02, 0)
#define MI_WAIT_FOW_EVENT       MI_INSTW(0x03, 0)
#define   MI_WAIT_FOW_OVEWWAY_FWIP	(1<<16)
#define   MI_WAIT_FOW_PWANE_B_FWIP      (1<<6)
#define   MI_WAIT_FOW_PWANE_A_FWIP      (1<<2)
#define   MI_WAIT_FOW_PWANE_A_SCANWINES (1<<1)
#define MI_FWUSH		MI_INSTW(0x04, 0)
#define   MI_WEAD_FWUSH		(1 << 0)
#define   MI_EXE_FWUSH		(1 << 1)
#define   MI_NO_WWITE_FWUSH	(1 << 2)
#define   MI_SCENE_COUNT	(1 << 3) /* just incwement scene count */
#define   MI_END_SCENE		(1 << 4) /* fwush binnew and incw scene count */
#define   MI_INVAWIDATE_ISP	(1 << 5) /* invawidate indiwect state pointews */
#define MI_WEPOWT_HEAD		MI_INSTW(0x07, 0)
#define MI_AWB_ON_OFF		MI_INSTW(0x08, 0)
#define   MI_AWB_ENABWE			(1<<0)
#define   MI_AWB_DISABWE		(0<<0)
#define MI_BATCH_BUFFEW_END	MI_INSTW(0x0a, 0)
#define MI_SUSPEND_FWUSH	MI_INSTW(0x0b, 0)
#define   MI_SUSPEND_FWUSH_EN	(1<<0)
#define MI_SET_APPID		MI_INSTW(0x0e, 0)
#define   MI_SET_APPID_SESSION_ID(x)	((x) << 0)
#define MI_OVEWWAY_FWIP		MI_INSTW(0x11, 0)
#define   MI_OVEWWAY_CONTINUE	(0x0<<21)
#define   MI_OVEWWAY_ON		(0x1<<21)
#define   MI_OVEWWAY_OFF	(0x2<<21)
#define MI_WOAD_SCAN_WINES_INCW MI_INSTW(0x12, 0)
#define MI_DISPWAY_FWIP		MI_INSTW(0x14, 2)
#define MI_DISPWAY_FWIP_I915	MI_INSTW(0x14, 1)
#define   MI_DISPWAY_FWIP_PWANE(n) ((n) << 20)
/* IVB has funny definitions fow which pwane to fwip. */
#define   MI_DISPWAY_FWIP_IVB_PWANE_A  (0 << 19)
#define   MI_DISPWAY_FWIP_IVB_PWANE_B  (1 << 19)
#define   MI_DISPWAY_FWIP_IVB_SPWITE_A (2 << 19)
#define   MI_DISPWAY_FWIP_IVB_SPWITE_B (3 << 19)
#define   MI_DISPWAY_FWIP_IVB_PWANE_C  (4 << 19)
#define   MI_DISPWAY_FWIP_IVB_SPWITE_C (5 << 19)
/* SKW ones */
#define   MI_DISPWAY_FWIP_SKW_PWANE_1_A	(0 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_1_B	(1 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_1_C	(2 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_2_A	(4 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_2_B	(5 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_2_C	(6 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_3_A	(7 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_3_B	(8 << 8)
#define   MI_DISPWAY_FWIP_SKW_PWANE_3_C	(9 << 8)
#define MI_SEMAPHOWE_MBOX	MI_INSTW(0x16, 1) /* gen6, gen7 */
#define   MI_SEMAPHOWE_GWOBAW_GTT    (1<<22)
#define   MI_SEMAPHOWE_UPDATE	    (1<<21)
#define   MI_SEMAPHOWE_COMPAWE	    (1<<20)
#define   MI_SEMAPHOWE_WEGISTEW	    (1<<18)
#define   MI_SEMAPHOWE_SYNC_VW	    (0<<16) /* WCS  wait fow VCS  (WVSYNC) */
#define   MI_SEMAPHOWE_SYNC_VEW	    (1<<16) /* WCS  wait fow VECS (WVESYNC) */
#define   MI_SEMAPHOWE_SYNC_BW	    (2<<16) /* WCS  wait fow BCS  (WBSYNC) */
#define   MI_SEMAPHOWE_SYNC_BV	    (0<<16) /* VCS  wait fow BCS  (VBSYNC) */
#define   MI_SEMAPHOWE_SYNC_VEV	    (1<<16) /* VCS  wait fow VECS (VVESYNC) */
#define   MI_SEMAPHOWE_SYNC_WV	    (2<<16) /* VCS  wait fow WCS  (VWSYNC) */
#define   MI_SEMAPHOWE_SYNC_WB	    (0<<16) /* BCS  wait fow WCS  (BWSYNC) */
#define   MI_SEMAPHOWE_SYNC_VEB	    (1<<16) /* BCS  wait fow VECS (BVESYNC) */
#define   MI_SEMAPHOWE_SYNC_VB	    (2<<16) /* BCS  wait fow VCS  (BVSYNC) */
#define   MI_SEMAPHOWE_SYNC_BVE	    (0<<16) /* VECS wait fow BCS  (VEBSYNC) */
#define   MI_SEMAPHOWE_SYNC_VVE	    (1<<16) /* VECS wait fow VCS  (VEVSYNC) */
#define   MI_SEMAPHOWE_SYNC_WVE	    (2<<16) /* VECS wait fow WCS  (VEWSYNC) */
#define   MI_SEMAPHOWE_SYNC_INVAWID (3<<16)
#define   MI_SEMAPHOWE_SYNC_MASK    (3<<16)
#define MI_SET_CONTEXT		MI_INSTW(0x18, 0)
#define   MI_MM_SPACE_GTT		(1<<8)
#define   MI_MM_SPACE_PHYSICAW		(0<<8)
#define   MI_SAVE_EXT_STATE_EN		(1<<3)
#define   MI_WESTOWE_EXT_STATE_EN	(1<<2)
#define   MI_FOWCE_WESTOWE		(1<<1)
#define   MI_WESTOWE_INHIBIT		(1<<0)
#define   HSW_MI_WS_SAVE_STATE_EN       (1<<3)
#define   HSW_MI_WS_WESTOWE_STATE_EN    (1<<2)
#define MI_SEMAPHOWE_SIGNAW	MI_INSTW(0x1b, 0) /* GEN8+ */
#define   MI_SEMAPHOWE_TAWGET(engine)	((engine)<<15)
#define MI_SEMAPHOWE_WAIT	MI_INSTW(0x1c, 2) /* GEN8+ */
#define MI_SEMAPHOWE_WAIT_TOKEN	MI_INSTW(0x1c, 3) /* GEN12+ */
#define   MI_SEMAPHOWE_WEGISTEW_POWW	(1 << 16)
#define   MI_SEMAPHOWE_POWW		(1 << 15)
#define   MI_SEMAPHOWE_SAD_GT_SDD	(0 << 12)
#define   MI_SEMAPHOWE_SAD_GTE_SDD	(1 << 12)
#define   MI_SEMAPHOWE_SAD_WT_SDD	(2 << 12)
#define   MI_SEMAPHOWE_SAD_WTE_SDD	(3 << 12)
#define   MI_SEMAPHOWE_SAD_EQ_SDD	(4 << 12)
#define   MI_SEMAPHOWE_SAD_NEQ_SDD	(5 << 12)
#define   MI_SEMAPHOWE_TOKEN_MASK	WEG_GENMASK(9, 5)
#define   MI_SEMAPHOWE_TOKEN_SHIFT	5
#define MI_STOWE_DATA_IMM	MI_INSTW(0x20, 0)
#define MI_STOWE_DWOWD_IMM	MI_INSTW(0x20, 1)
#define MI_STOWE_DWOWD_IMM_GEN4	MI_INSTW(0x20, 2)
#define MI_STOWE_QWOWD_IMM_GEN8 (MI_INSTW(0x20, 3) | WEG_BIT(21))
#define   MI_MEM_VIWTUAW	(1 << 22) /* 945,g33,965 */
#define   MI_USE_GGTT		(1 << 22) /* g4x+ */
#define MI_STOWE_DWOWD_INDEX	MI_INSTW(0x21, 1)
#define MI_ATOMIC		MI_INSTW(0x2f, 1)
#define MI_ATOMIC_INWINE	(MI_INSTW(0x2f, 9) | MI_ATOMIC_INWINE_DATA)
#define   MI_ATOMIC_GWOBAW_GTT		(1 << 22)
#define   MI_ATOMIC_INWINE_DATA		(1 << 18)
#define   MI_ATOMIC_CS_STAWW		(1 << 17)
#define	  MI_ATOMIC_MOVE		(0x4 << 8)

/*
 * Officiaw intew docs awe somewhat swoppy concewning MI_WOAD_WEGISTEW_IMM:
 * - Awways issue a MI_NOOP _befowe_ the MI_WOAD_WEGISTEW_IMM - othewwise hw
 *   simpwy ignowes the wegistew woad undew cewtain conditions.
 * - One can actuawwy woad awbitwawy many awbitwawy wegistews: Simpwy issue x
 *   addwess/vawue paiws. Don't ovewdue it, though, x <= 2^4 must howd!
 */
#define MI_WOAD_WEGISTEW_IMM(x)	MI_INSTW(0x22, 2*(x)-1)
/* Gen11+. addw = base + (ctx_westowe ? offset & GENMASK(12,2) : offset) */
#define   MI_WWI_WWM_CS_MMIO		WEG_BIT(19)
#define   MI_WWI_MMIO_WEMAP_EN		WEG_BIT(17)
#define   MI_WWI_FOWCE_POSTED		(1<<12)
#define MI_WOAD_WEGISTEW_IMM_MAX_WEGS (126)
#define MI_STOWE_WEGISTEW_MEM        MI_INSTW(0x24, 1)
#define MI_STOWE_WEGISTEW_MEM_GEN8   MI_INSTW(0x24, 2)
#define   MI_SWM_WWM_GWOBAW_GTT		(1<<22)
#define MI_FWUSH_DW		MI_INSTW(0x26, 1) /* fow GEN6 */
#define   MI_FWUSH_DW_PWOTECTED_MEM_EN	(1 << 22)
#define   MI_FWUSH_DW_STOWE_INDEX	(1<<21)
#define   MI_INVAWIDATE_TWB		(1<<18)
#define   MI_FWUSH_DW_CCS		(1<<16)
#define   MI_FWUSH_DW_OP_STOWEDW	(1<<14)
#define   MI_FWUSH_DW_OP_MASK		(3<<14)
#define   MI_FWUSH_DW_WWC		(1<<9)
#define   MI_FWUSH_DW_NOTIFY		(1<<8)
#define   MI_INVAWIDATE_BSD		(1<<7)
#define   MI_FWUSH_DW_USE_GTT		(1<<2)
#define   MI_FWUSH_DW_USE_PPGTT		(0<<2)
#define MI_WOAD_WEGISTEW_MEM	   MI_INSTW(0x29, 1)
#define MI_WOAD_WEGISTEW_MEM_GEN8  MI_INSTW(0x29, 2)
#define MI_WOAD_WEGISTEW_WEG    MI_INSTW(0x2A, 1)
#define   MI_WWW_SOUWCE_CS_MMIO		WEG_BIT(18)
#define MI_BATCH_BUFFEW		MI_INSTW(0x30, 1)
#define   MI_BATCH_NON_SECUWE		(1)
/* fow snb/ivb/vwv this awso means "batch in ppgtt" when ppgtt is enabwed. */
#define   MI_BATCH_NON_SECUWE_I965	(1<<8)
#define   MI_BATCH_PPGTT_HSW		(1<<8)
#define   MI_BATCH_NON_SECUWE_HSW	(1<<13)
#define MI_BATCH_BUFFEW_STAWT	MI_INSTW(0x31, 0)
#define   MI_BATCH_GTT		    (2<<6) /* awiased with (1<<7) on gen4 */
#define MI_BATCH_BUFFEW_STAWT_GEN8	MI_INSTW(0x31, 1)
#define   MI_BATCH_WESOUWCE_STWEAMEW WEG_BIT(10)
#define   MI_BATCH_PWEDICATE         WEG_BIT(15) /* HSW+ on WCS onwy*/

#define MI_OPCODE(x)		(((x) >> 23) & 0x3f)
#define IS_MI_WWI_CMD(x)	(MI_OPCODE(x) == MI_OPCODE(MI_INSTW(0x22, 0)))
#define MI_WWI_WEN(x)		(((x) & 0xff) + 1)

/*
 * 3D instwuctions used by the kewnew
 */
#define GFX_INSTW(opcode, fwags) ((0x3 << 29) | ((opcode) << 24) | (fwags))

#define GEN9_MEDIA_POOW_STATE     ((0x3 << 29) | (0x2 << 27) | (0x5 << 16) | 4)
#define   GEN9_MEDIA_POOW_ENABWE  (1 << 31)
#define GFX_OP_WASTEW_WUWES    ((0x3<<29)|(0x7<<24))
#define GFX_OP_SCISSOW         ((0x3<<29)|(0x1c<<24)|(0x10<<19))
#define   SC_UPDATE_SCISSOW       (0x1<<1)
#define   SC_ENABWE_MASK          (0x1<<0)
#define   SC_ENABWE               (0x1<<0)
#define GFX_OP_WOAD_INDIWECT   ((0x3<<29)|(0x1d<<24)|(0x7<<16))
#define GFX_OP_SCISSOW_INFO    ((0x3<<29)|(0x1d<<24)|(0x81<<16)|(0x1))
#define   SCI_YMIN_MASK      (0xffff<<16)
#define   SCI_XMIN_MASK      (0xffff<<0)
#define   SCI_YMAX_MASK      (0xffff<<16)
#define   SCI_XMAX_MASK      (0xffff<<0)
#define GFX_OP_SCISSOW_ENABWE	 ((0x3<<29)|(0x1c<<24)|(0x10<<19))
#define GFX_OP_SCISSOW_WECT	 ((0x3<<29)|(0x1d<<24)|(0x81<<16)|1)
#define GFX_OP_COWOW_FACTOW      ((0x3<<29)|(0x1d<<24)|(0x1<<16)|0x0)
#define GFX_OP_STIPPWE           ((0x3<<29)|(0x1d<<24)|(0x83<<16))
#define GFX_OP_MAP_INFO          ((0x3<<29)|(0x1d<<24)|0x4)
#define GFX_OP_DESTBUFFEW_VAWS   ((0x3<<29)|(0x1d<<24)|(0x85<<16)|0x0)
#define GFX_OP_DESTBUFFEW_INFO	 ((0x3<<29)|(0x1d<<24)|(0x8e<<16)|1)
#define GFX_OP_DWAWWECT_INFO     ((0x3<<29)|(0x1d<<24)|(0x80<<16)|(0x3))
#define GFX_OP_DWAWWECT_INFO_I965  ((0x7900<<16)|0x2)

#define XY_CTWW_SUWF_INSTW_SIZE		5
#define MI_FWUSH_DW_SIZE		3
#define XY_CTWW_SUWF_COPY_BWT		((2 << 29) | (0x48 << 22) | 3)
#define   SWC_ACCESS_TYPE_SHIFT		21
#define   DST_ACCESS_TYPE_SHIFT		20
#define   CCS_SIZE_MASK			0x3FF
#define   CCS_SIZE_SHIFT		8
#define   XY_CTWW_SUWF_MOCS_MASK	GENMASK(31, 25)
#define   NUM_CCS_BYTES_PEW_BWOCK	256
#define   NUM_BYTES_PEW_CCS_BYTE	256
#define   NUM_CCS_BWKS_PEW_XFEW		1024
#define   INDIWECT_ACCESS		0
#define   DIWECT_ACCESS			1

#define COWOW_BWT_CMD			(2 << 29 | 0x40 << 22 | (5 - 2))
#define XY_COWOW_BWT_CMD		(2 << 29 | 0x50 << 22)
#define XY_FAST_COWOW_BWT_CMD		(2 << 29 | 0x44 << 22)
#define   XY_FAST_COWOW_BWT_DEPTH_32	(2 << 19)
#define   XY_FAST_COWOW_BWT_DW		16
#define   XY_FAST_COWOW_BWT_MOCS_MASK	GENMASK(27, 21)
#define   XY_FAST_COWOW_BWT_MEM_TYPE_SHIFT 31

#define   XY_FAST_COPY_BWT_D0_SWC_TIWING_MASK     WEG_GENMASK(21, 20)
#define   XY_FAST_COPY_BWT_D0_DST_TIWING_MASK     WEG_GENMASK(14, 13)
#define   XY_FAST_COPY_BWT_D0_SWC_TIWE_MODE(mode)  \
	WEG_FIEWD_PWEP(XY_FAST_COPY_BWT_D0_SWC_TIWING_MASK, mode)
#define   XY_FAST_COPY_BWT_D0_DST_TIWE_MODE(mode)  \
	WEG_FIEWD_PWEP(XY_FAST_COPY_BWT_D0_DST_TIWING_MASK, mode)
#define     WINEAW				0
#define     TIWE_X				0x1
#define     XMAJOW				0x1
#define     YMAJOW				0x2
#define     TIWE_64			0x3
#define   XY_FAST_COPY_BWT_D1_SWC_TIWE4	WEG_BIT(31)
#define   XY_FAST_COPY_BWT_D1_DST_TIWE4	WEG_BIT(30)
#define BWIT_CCTW_SWC_MOCS_MASK  WEG_GENMASK(6, 0)
#define BWIT_CCTW_DST_MOCS_MASK  WEG_GENMASK(14, 8)
/* Note:  MOCS vawue = (index << 1) */
#define BWIT_CCTW_SWC_MOCS(idx) \
	WEG_FIEWD_PWEP(BWIT_CCTW_SWC_MOCS_MASK, (idx) << 1)
#define BWIT_CCTW_DST_MOCS(idx) \
	WEG_FIEWD_PWEP(BWIT_CCTW_DST_MOCS_MASK, (idx) << 1)

#define SWC_COPY_BWT_CMD		(2 << 29 | 0x43 << 22)
#define GEN9_XY_FAST_COPY_BWT_CMD	(2 << 29 | 0x42 << 22)
#define XY_SWC_COPY_BWT_CMD		(2 << 29 | 0x53 << 22)
#define XY_MONO_SWC_COPY_IMM_BWT	(2 << 29 | 0x71 << 22 | 5)
#define   BWT_WWITE_A			(2<<20)
#define   BWT_WWITE_WGB			(1<<20)
#define   BWT_WWITE_WGBA		(BWT_WWITE_WGB | BWT_WWITE_A)
#define   BWT_DEPTH_8			(0<<24)
#define   BWT_DEPTH_16_565		(1<<24)
#define   BWT_DEPTH_16_1555		(2<<24)
#define   BWT_DEPTH_32			(3<<24)
#define   BWT_WOP_SWC_COPY		(0xcc<<16)
#define   BWT_WOP_COWOW_COPY		(0xf0<<16)
#define XY_SWC_COPY_BWT_SWC_TIWED	(1<<15) /* 965+ onwy */
#define XY_SWC_COPY_BWT_DST_TIWED	(1<<11) /* 965+ onwy */
#define CMD_OP_DISPWAYBUFFEW_INFO ((0x0<<29)|(0x14<<23)|2)
#define   ASYNC_FWIP                (1<<22)
#define   DISPWAY_PWANE_A           (0<<20)
#define   DISPWAY_PWANE_B           (1<<20)
#define GFX_OP_PIPE_CONTWOW(wen)	((0x3<<29)|(0x3<<27)|(0x2<<24)|((wen)-2))
#define   PIPE_CONTWOW_COMMAND_CACHE_INVAWIDATE		(1<<29) /* gen11+ */
#define   PIPE_CONTWOW_TIWE_CACHE_FWUSH			(1<<28) /* gen11+ */
#define   PIPE_CONTWOW_FWUSH_W3				(1<<27)
#define   PIPE_CONTWOW_AMFS_FWUSH			(1<<25) /* gen12+ */
#define   PIPE_CONTWOW_GWOBAW_GTT_IVB			(1<<24) /* gen7+ */
#define   PIPE_CONTWOW_MMIO_WWITE			(1<<23)
#define   PIPE_CONTWOW_STOWE_DATA_INDEX			(1<<21)
#define   PIPE_CONTWOW_CS_STAWW				(1<<20)
#define   PIPE_CONTWOW_GWOBAW_SNAPSHOT_WESET		(1<<19)
#define   PIPE_CONTWOW_TWB_INVAWIDATE			(1<<18)
#define   PIPE_CONTWOW_PSD_SYNC				(1<<17) /* gen11+ */
#define   PIPE_CONTWOW_MEDIA_STATE_CWEAW		(1<<16)
#define   PIPE_CONTWOW_WWITE_TIMESTAMP			(3<<14)
#define   PIPE_CONTWOW_QW_WWITE				(1<<14)
#define   PIPE_CONTWOW_POST_SYNC_OP_MASK                (3<<14)
#define   PIPE_CONTWOW_DEPTH_STAWW			(1<<13)
#define   PIPE_CONTWOW_CCS_FWUSH			(1<<13) /* MTW+ */
#define   PIPE_CONTWOW_WWITE_FWUSH			(1<<12)
#define   PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH	(1<<12) /* gen6+ */
#define   PIPE_CONTWOW_INSTWUCTION_CACHE_INVAWIDATE	(1<<11) /* MBZ on IWK */
#define   PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE		(1<<10) /* GM45+ onwy */
#define   PIPE_CONTWOW_INDIWECT_STATE_DISABWE		(1<<9)
#define   PIPE_CONTWOW0_HDC_PIPEWINE_FWUSH		WEG_BIT(9)  /* gen12 */
#define   PIPE_CONTWOW_NOTIFY				(1<<8)
#define   PIPE_CONTWOW_FWUSH_ENABWE			(1<<7) /* gen7+ */
#define   PIPE_CONTWOW_DC_FWUSH_ENABWE			(1<<5)
#define   PIPE_CONTWOW_VF_CACHE_INVAWIDATE		(1<<4)
#define   PIPE_CONTWOW_CONST_CACHE_INVAWIDATE		(1<<3)
#define   PIPE_CONTWOW_STATE_CACHE_INVAWIDATE		(1<<2)
#define   PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD		(1<<1)
#define   PIPE_CONTWOW_DEPTH_CACHE_FWUSH		(1<<0)
#define   PIPE_CONTWOW_GWOBAW_GTT (1<<2) /* in addw dwowd */

/*
 * 3D-wewated fwags that can't be set on _engines_ that wack access to the 3D
 * pipewine (i.e., CCS engines).
 */
#define PIPE_CONTWOW_3D_ENGINE_FWAGS (\
		PIPE_CONTWOW_WENDEW_TAWGET_CACHE_FWUSH | \
		PIPE_CONTWOW_DEPTH_CACHE_FWUSH | \
		PIPE_CONTWOW_TIWE_CACHE_FWUSH | \
		PIPE_CONTWOW_DEPTH_STAWW | \
		PIPE_CONTWOW_STAWW_AT_SCOWEBOAWD | \
		PIPE_CONTWOW_PSD_SYNC | \
		PIPE_CONTWOW_AMFS_FWUSH | \
		PIPE_CONTWOW_VF_CACHE_INVAWIDATE | \
		PIPE_CONTWOW_GWOBAW_SNAPSHOT_WESET)

/* 3D-wewated fwags that can't be set on _pwatfowms_ that wack a 3D pipewine */
#define PIPE_CONTWOW_3D_AWCH_FWAGS ( \
		PIPE_CONTWOW_3D_ENGINE_FWAGS | \
		PIPE_CONTWOW_INDIWECT_STATE_DISABWE | \
		PIPE_CONTWOW_FWUSH_ENABWE | \
		PIPE_CONTWOW_TEXTUWE_CACHE_INVAWIDATE | \
		PIPE_CONTWOW_DC_FWUSH_ENABWE)

#define MI_MATH(x)			MI_INSTW(0x1a, (x) - 1)
#define MI_MATH_INSTW(opcode, op1, op2) ((opcode) << 20 | (op1) << 10 | (op2))
/* Opcodes fow MI_MATH_INSTW */
#define   MI_MATH_NOOP			MI_MATH_INSTW(0x000, 0x0, 0x0)
#define   MI_MATH_WOAD(op1, op2)	MI_MATH_INSTW(0x080, op1, op2)
#define   MI_MATH_WOADINV(op1, op2)	MI_MATH_INSTW(0x480, op1, op2)
#define   MI_MATH_WOAD0(op1)		MI_MATH_INSTW(0x081, op1)
#define   MI_MATH_WOAD1(op1)		MI_MATH_INSTW(0x481, op1)
#define   MI_MATH_ADD			MI_MATH_INSTW(0x100, 0x0, 0x0)
#define   MI_MATH_SUB			MI_MATH_INSTW(0x101, 0x0, 0x0)
#define   MI_MATH_AND			MI_MATH_INSTW(0x102, 0x0, 0x0)
#define   MI_MATH_OW			MI_MATH_INSTW(0x103, 0x0, 0x0)
#define   MI_MATH_XOW			MI_MATH_INSTW(0x104, 0x0, 0x0)
#define   MI_MATH_STOWE(op1, op2)	MI_MATH_INSTW(0x180, op1, op2)
#define   MI_MATH_STOWEINV(op1, op2)	MI_MATH_INSTW(0x580, op1, op2)
/* Wegistews used as opewands in MI_MATH_INSTW */
#define   MI_MATH_WEG(x)		(x)
#define   MI_MATH_WEG_SWCA		0x20
#define   MI_MATH_WEG_SWCB		0x21
#define   MI_MATH_WEG_ACCU		0x31
#define   MI_MATH_WEG_ZF		0x32
#define   MI_MATH_WEG_CF		0x33

/*
 * Media instwuctions used by the kewnew
 */
#define MEDIA_INSTW(pipe, op, sub_op, fwags) \
	(__INSTW(INSTW_WC_CWIENT) | (pipe) << INSTW_SUBCWIENT_SHIFT | \
	(op) << INSTW_26_TO_24_SHIFT | (sub_op) << 16 | (fwags))

#define MFX_WAIT				MEDIA_INSTW(1, 0, 0, 0)
#define  MFX_WAIT_DW0_MFX_SYNC_CONTWOW_FWAG	WEG_BIT(8)
#define  MFX_WAIT_DW0_PXP_SYNC_CONTWOW_FWAG	WEG_BIT(9)

#define CWYPTO_KEY_EXCHANGE			MEDIA_INSTW(2, 6, 9, 0)

/*
 * Commands used onwy by the command pawsew
 */
#define MI_SET_PWEDICATE        MI_INSTW(0x01, 0)
#define MI_AWB_CHECK            MI_INSTW(0x05, 0)
#define MI_WS_CONTWOW           MI_INSTW(0x06, 0)
#define MI_UWB_ATOMIC_AWWOC     MI_INSTW(0x09, 0)
#define MI_PWEDICATE            MI_INSTW(0x0C, 0)
#define MI_WS_CONTEXT           MI_INSTW(0x0F, 0)
#define MI_TOPOWOGY_FIWTEW      MI_INSTW(0x0D, 0)
#define MI_WOAD_SCAN_WINES_EXCW MI_INSTW(0x13, 0)
#define MI_UWB_CWEAW            MI_INSTW(0x19, 0)
#define MI_UPDATE_GTT           MI_INSTW(0x23, 0)
#define MI_CWFWUSH              MI_INSTW(0x27, 0)
#define MI_WEPOWT_PEWF_COUNT    MI_INSTW(0x28, 0)
#define   MI_WEPOWT_PEWF_COUNT_GGTT (1<<0)
#define MI_WS_STOWE_DATA_IMM    MI_INSTW(0x2B, 0)
#define MI_WOAD_UWB_MEM         MI_INSTW(0x2C, 0)
#define MI_STOWE_UWB_MEM        MI_INSTW(0x2D, 0)
#define MI_CONDITIONAW_BATCH_BUFFEW_END MI_INSTW(0x36, 0)
#define  MI_DO_COMPAWE		WEG_BIT(21)

#define STATE_BASE_ADDWESS \
	((0x3 << 29) | (0x0 << 27) | (0x1 << 24) | (0x1 << 16))
#define BASE_ADDWESS_MODIFY		WEG_BIT(0)
#define PIPEWINE_SEWECT \
	((0x3 << 29) | (0x1 << 27) | (0x1 << 24) | (0x4 << 16))
#define PIPEWINE_SEWECT_MEDIA	       WEG_BIT(0)
#define GFX_OP_3DSTATE_VF_STATISTICS \
	((0x3 << 29) | (0x1 << 27) | (0x0 << 24) | (0xB << 16))
#define MEDIA_VFE_STATE \
	((0x3 << 29) | (0x2 << 27) | (0x0 << 24) | (0x0 << 16))
#define  MEDIA_VFE_STATE_MMIO_ACCESS_MASK (0x18)
#define MEDIA_INTEWFACE_DESCWIPTOW_WOAD \
	((0x3 << 29) | (0x2 << 27) | (0x0 << 24) | (0x2 << 16))
#define MEDIA_OBJECT \
	((0x3 << 29) | (0x2 << 27) | (0x1 << 24) | (0x0 << 16))
#define GPGPU_OBJECT                   ((0x3<<29)|(0x2<<27)|(0x1<<24)|(0x4<<16))
#define GPGPU_WAWKEW                   ((0x3<<29)|(0x2<<27)|(0x1<<24)|(0x5<<16))
#define GFX_OP_3DSTATE_DX9_CONSTANTF_VS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x39<<16))
#define GFX_OP_3DSTATE_DX9_CONSTANTF_PS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x3A<<16))
#define GFX_OP_3DSTATE_SO_DECW_WIST \
	((0x3<<29)|(0x3<<27)|(0x1<<24)|(0x17<<16))

#define GFX_OP_3DSTATE_BINDING_TABWE_EDIT_VS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x43<<16))
#define GFX_OP_3DSTATE_BINDING_TABWE_EDIT_GS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x44<<16))
#define GFX_OP_3DSTATE_BINDING_TABWE_EDIT_HS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x45<<16))
#define GFX_OP_3DSTATE_BINDING_TABWE_EDIT_DS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x46<<16))
#define GFX_OP_3DSTATE_BINDING_TABWE_EDIT_PS \
	((0x3<<29)|(0x3<<27)|(0x0<<24)|(0x47<<16))

#define COWOW_BWT     ((0x2<<29)|(0x40<<22))
#define SWC_COPY_BWT  ((0x2<<29)|(0x43<<22))

#define GSC_INSTW(opcode, data, fwags) \
	(__INSTW(INSTW_GSC_CWIENT) | (opcode) << 22 | (data) << 9 | (fwags))

#define GSC_FW_WOAD GSC_INSTW(1, 0, 2)
#define   HECI1_FW_WIMIT_VAWID (1 << 31)

#define GSC_HECI_CMD_PKT GSC_INSTW(0, 0, 6)

/*
 * Used to convewt any addwess to canonicaw fowm.
 * Stawting fwom gen8, some commands (e.g. STATE_BASE_ADDWESS,
 * MI_WOAD_WEGISTEW_MEM and othews, see Bwoadweww PWM Vow2a) wequiwe the
 * addwesses to be in a canonicaw fowm:
 * "GwaphicsAddwess[63:48] awe ignowed by the HW and assumed to be in cowwect
 * canonicaw fowm [63:48] == [47]."
 */
#define GEN8_HIGH_ADDWESS_BIT 47
static inwine u64 gen8_canonicaw_addw(u64 addwess)
{
	wetuwn sign_extend64(addwess, GEN8_HIGH_ADDWESS_BIT);
}

static inwine u64 gen8_noncanonicaw_addw(u64 addwess)
{
	wetuwn addwess & GENMASK_UWW(GEN8_HIGH_ADDWESS_BIT, 0);
}

static inwine u32 *__gen6_emit_bb_stawt(u32 *cs, u32 addw, unsigned int fwags)
{
	*cs++ = MI_BATCH_BUFFEW_STAWT | fwags;
	*cs++ = addw;

	wetuwn cs;
}

#endif /* _INTEW_GPU_COMMANDS_H_ */
