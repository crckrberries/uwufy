/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ke Yu
 *    Kevin Tian <kevin.tian@intew.com>
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *    Yuwei Zhang <yuwei.zhang@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude <winux/swab.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wwc.h"
#incwude "gt/intew_wing.h"
#incwude "gt/intew_gt_wequests.h"
#incwude "gt/shmem_utiws.h"
#incwude "gvt.h"
#incwude "i915_pvinfo.h"
#incwude "twace.h"

#incwude "dispway/intew_dispway.h"
#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_context.h"

#define INVAWID_OP    (~0U)

#define OP_WEN_MI           9
#define OP_WEN_2D           10
#define OP_WEN_3D_MEDIA     16
#define OP_WEN_MFX_VC       16
#define OP_WEN_VEBOX	    16

#define CMD_TYPE(cmd)	(((cmd) >> 29) & 7)

stwuct sub_op_bits {
	int hi;
	int wow;
};
stwuct decode_info {
	const chaw *name;
	int op_wen;
	int nw_sub_op;
	const stwuct sub_op_bits *sub_op;
};

#define   MAX_CMD_BUDGET			0x7fffffff
#define   MI_WAIT_FOW_PWANE_C_FWIP_PENDING      (1<<15)
#define   MI_WAIT_FOW_PWANE_B_FWIP_PENDING      (1<<9)
#define   MI_WAIT_FOW_PWANE_A_FWIP_PENDING      (1<<1)

#define   MI_WAIT_FOW_SPWITE_C_FWIP_PENDING      (1<<20)
#define   MI_WAIT_FOW_SPWITE_B_FWIP_PENDING      (1<<10)
#define   MI_WAIT_FOW_SPWITE_A_FWIP_PENDING      (1<<2)

/* Wendew Command Map */

/* MI_* command Opcode (28:23) */
#define OP_MI_NOOP                          0x0
#define OP_MI_SET_PWEDICATE                 0x1  /* HSW+ */
#define OP_MI_USEW_INTEWWUPT                0x2
#define OP_MI_WAIT_FOW_EVENT                0x3
#define OP_MI_FWUSH                         0x4
#define OP_MI_AWB_CHECK                     0x5
#define OP_MI_WS_CONTWOW                    0x6  /* HSW+ */
#define OP_MI_WEPOWT_HEAD                   0x7
#define OP_MI_AWB_ON_OFF                    0x8
#define OP_MI_UWB_ATOMIC_AWWOC              0x9  /* HSW+ */
#define OP_MI_BATCH_BUFFEW_END              0xA
#define OP_MI_SUSPEND_FWUSH                 0xB
#define OP_MI_PWEDICATE                     0xC  /* IVB+ */
#define OP_MI_TOPOWOGY_FIWTEW               0xD  /* IVB+ */
#define OP_MI_SET_APPID                     0xE  /* IVB+ */
#define OP_MI_WS_CONTEXT                    0xF  /* HSW+ */
#define OP_MI_WOAD_SCAN_WINES_INCW          0x12 /* HSW+ */
#define OP_MI_DISPWAY_FWIP                  0x14
#define OP_MI_SEMAPHOWE_MBOX                0x16
#define OP_MI_SET_CONTEXT                   0x18
#define OP_MI_MATH                          0x1A
#define OP_MI_UWB_CWEAW                     0x19
#define OP_MI_SEMAPHOWE_SIGNAW		    0x1B  /* BDW+ */
#define OP_MI_SEMAPHOWE_WAIT		    0x1C  /* BDW+ */

#define OP_MI_STOWE_DATA_IMM                0x20
#define OP_MI_STOWE_DATA_INDEX              0x21
#define OP_MI_WOAD_WEGISTEW_IMM             0x22
#define OP_MI_UPDATE_GTT                    0x23
#define OP_MI_STOWE_WEGISTEW_MEM            0x24
#define OP_MI_FWUSH_DW                      0x26
#define OP_MI_CWFWUSH                       0x27
#define OP_MI_WEPOWT_PEWF_COUNT             0x28
#define OP_MI_WOAD_WEGISTEW_MEM             0x29  /* HSW+ */
#define OP_MI_WOAD_WEGISTEW_WEG             0x2A  /* HSW+ */
#define OP_MI_WS_STOWE_DATA_IMM             0x2B  /* HSW+ */
#define OP_MI_WOAD_UWB_MEM                  0x2C  /* HSW+ */
#define OP_MI_STOWE_UWM_MEM                 0x2D  /* HSW+ */
#define OP_MI_2E			    0x2E  /* BDW+ */
#define OP_MI_2F			    0x2F  /* BDW+ */
#define OP_MI_BATCH_BUFFEW_STAWT            0x31

/* Bit definition fow dwowd 0 */
#define _CMDBIT_BB_STAWT_IN_PPGTT	(1UW << 8)

#define OP_MI_CONDITIONAW_BATCH_BUFFEW_END  0x36

#define BATCH_BUFFEW_ADDW_MASK ((1UW << 32) - (1U << 2))
#define BATCH_BUFFEW_ADDW_HIGH_MASK ((1UW << 16) - (1U))
#define BATCH_BUFFEW_ADW_SPACE_BIT(x)	(((x) >> 8) & 1U)
#define BATCH_BUFFEW_2ND_WEVEW_BIT(x)   ((x) >> 22 & 1U)

/* 2D command: Opcode (28:22) */
#define OP_2D(x)    ((2<<7) | x)

#define OP_XY_SETUP_BWT                             OP_2D(0x1)
#define OP_XY_SETUP_CWIP_BWT                        OP_2D(0x3)
#define OP_XY_SETUP_MONO_PATTEWN_SW_BWT             OP_2D(0x11)
#define OP_XY_PIXEW_BWT                             OP_2D(0x24)
#define OP_XY_SCANWINES_BWT                         OP_2D(0x25)
#define OP_XY_TEXT_BWT                              OP_2D(0x26)
#define OP_XY_TEXT_IMMEDIATE_BWT                    OP_2D(0x31)
#define OP_XY_COWOW_BWT                             OP_2D(0x50)
#define OP_XY_PAT_BWT                               OP_2D(0x51)
#define OP_XY_MONO_PAT_BWT                          OP_2D(0x52)
#define OP_XY_SWC_COPY_BWT                          OP_2D(0x53)
#define OP_XY_MONO_SWC_COPY_BWT                     OP_2D(0x54)
#define OP_XY_FUWW_BWT                              OP_2D(0x55)
#define OP_XY_FUWW_MONO_SWC_BWT                     OP_2D(0x56)
#define OP_XY_FUWW_MONO_PATTEWN_BWT                 OP_2D(0x57)
#define OP_XY_FUWW_MONO_PATTEWN_MONO_SWC_BWT        OP_2D(0x58)
#define OP_XY_MONO_PAT_FIXED_BWT                    OP_2D(0x59)
#define OP_XY_MONO_SWC_COPY_IMMEDIATE_BWT           OP_2D(0x71)
#define OP_XY_PAT_BWT_IMMEDIATE                     OP_2D(0x72)
#define OP_XY_SWC_COPY_CHWOMA_BWT                   OP_2D(0x73)
#define OP_XY_FUWW_IMMEDIATE_PATTEWN_BWT            OP_2D(0x74)
#define OP_XY_FUWW_MONO_SWC_IMMEDIATE_PATTEWN_BWT   OP_2D(0x75)
#define OP_XY_PAT_CHWOMA_BWT                        OP_2D(0x76)
#define OP_XY_PAT_CHWOMA_BWT_IMMEDIATE              OP_2D(0x77)

/* 3D/Media Command: Pipewine Type(28:27) Opcode(26:24) Sub Opcode(23:16) */
#define OP_3D_MEDIA(sub_type, opcode, sub_opcode) \
	((3 << 13) | ((sub_type) << 11) | ((opcode) << 8) | (sub_opcode))

#define OP_STATE_PWEFETCH                       OP_3D_MEDIA(0x0, 0x0, 0x03)

#define OP_STATE_BASE_ADDWESS                   OP_3D_MEDIA(0x0, 0x1, 0x01)
#define OP_STATE_SIP                            OP_3D_MEDIA(0x0, 0x1, 0x02)
#define OP_3D_MEDIA_0_1_4			OP_3D_MEDIA(0x0, 0x1, 0x04)
#define OP_SWTESS_BASE_ADDWESS			OP_3D_MEDIA(0x0, 0x1, 0x03)

#define OP_3DSTATE_VF_STATISTICS_GM45           OP_3D_MEDIA(0x1, 0x0, 0x0B)

#define OP_PIPEWINE_SEWECT                      OP_3D_MEDIA(0x1, 0x1, 0x04)

#define OP_MEDIA_VFE_STATE                      OP_3D_MEDIA(0x2, 0x0, 0x0)
#define OP_MEDIA_CUWBE_WOAD                     OP_3D_MEDIA(0x2, 0x0, 0x1)
#define OP_MEDIA_INTEWFACE_DESCWIPTOW_WOAD      OP_3D_MEDIA(0x2, 0x0, 0x2)
#define OP_MEDIA_GATEWAY_STATE                  OP_3D_MEDIA(0x2, 0x0, 0x3)
#define OP_MEDIA_STATE_FWUSH                    OP_3D_MEDIA(0x2, 0x0, 0x4)
#define OP_MEDIA_POOW_STATE                     OP_3D_MEDIA(0x2, 0x0, 0x5)

#define OP_MEDIA_OBJECT                         OP_3D_MEDIA(0x2, 0x1, 0x0)
#define OP_MEDIA_OBJECT_PWT                     OP_3D_MEDIA(0x2, 0x1, 0x2)
#define OP_MEDIA_OBJECT_WAWKEW                  OP_3D_MEDIA(0x2, 0x1, 0x3)
#define OP_GPGPU_WAWKEW                         OP_3D_MEDIA(0x2, 0x1, 0x5)

#define OP_3DSTATE_CWEAW_PAWAMS                 OP_3D_MEDIA(0x3, 0x0, 0x04) /* IVB+ */
#define OP_3DSTATE_DEPTH_BUFFEW                 OP_3D_MEDIA(0x3, 0x0, 0x05) /* IVB+ */
#define OP_3DSTATE_STENCIW_BUFFEW               OP_3D_MEDIA(0x3, 0x0, 0x06) /* IVB+ */
#define OP_3DSTATE_HIEW_DEPTH_BUFFEW            OP_3D_MEDIA(0x3, 0x0, 0x07) /* IVB+ */
#define OP_3DSTATE_VEWTEX_BUFFEWS               OP_3D_MEDIA(0x3, 0x0, 0x08)
#define OP_3DSTATE_VEWTEX_EWEMENTS              OP_3D_MEDIA(0x3, 0x0, 0x09)
#define OP_3DSTATE_INDEX_BUFFEW                 OP_3D_MEDIA(0x3, 0x0, 0x0A)
#define OP_3DSTATE_VF_STATISTICS                OP_3D_MEDIA(0x3, 0x0, 0x0B)
#define OP_3DSTATE_VF                           OP_3D_MEDIA(0x3, 0x0, 0x0C)  /* HSW+ */
#define OP_3DSTATE_CC_STATE_POINTEWS            OP_3D_MEDIA(0x3, 0x0, 0x0E)
#define OP_3DSTATE_SCISSOW_STATE_POINTEWS       OP_3D_MEDIA(0x3, 0x0, 0x0F)
#define OP_3DSTATE_VS                           OP_3D_MEDIA(0x3, 0x0, 0x10)
#define OP_3DSTATE_GS                           OP_3D_MEDIA(0x3, 0x0, 0x11)
#define OP_3DSTATE_CWIP                         OP_3D_MEDIA(0x3, 0x0, 0x12)
#define OP_3DSTATE_SF                           OP_3D_MEDIA(0x3, 0x0, 0x13)
#define OP_3DSTATE_WM                           OP_3D_MEDIA(0x3, 0x0, 0x14)
#define OP_3DSTATE_CONSTANT_VS                  OP_3D_MEDIA(0x3, 0x0, 0x15)
#define OP_3DSTATE_CONSTANT_GS                  OP_3D_MEDIA(0x3, 0x0, 0x16)
#define OP_3DSTATE_CONSTANT_PS                  OP_3D_MEDIA(0x3, 0x0, 0x17)
#define OP_3DSTATE_SAMPWE_MASK                  OP_3D_MEDIA(0x3, 0x0, 0x18)
#define OP_3DSTATE_CONSTANT_HS                  OP_3D_MEDIA(0x3, 0x0, 0x19) /* IVB+ */
#define OP_3DSTATE_CONSTANT_DS                  OP_3D_MEDIA(0x3, 0x0, 0x1A) /* IVB+ */
#define OP_3DSTATE_HS                           OP_3D_MEDIA(0x3, 0x0, 0x1B) /* IVB+ */
#define OP_3DSTATE_TE                           OP_3D_MEDIA(0x3, 0x0, 0x1C) /* IVB+ */
#define OP_3DSTATE_DS                           OP_3D_MEDIA(0x3, 0x0, 0x1D) /* IVB+ */
#define OP_3DSTATE_STWEAMOUT                    OP_3D_MEDIA(0x3, 0x0, 0x1E) /* IVB+ */
#define OP_3DSTATE_SBE                          OP_3D_MEDIA(0x3, 0x0, 0x1F) /* IVB+ */
#define OP_3DSTATE_PS                           OP_3D_MEDIA(0x3, 0x0, 0x20) /* IVB+ */
#define OP_3DSTATE_VIEWPOWT_STATE_POINTEWS_SF_CWIP OP_3D_MEDIA(0x3, 0x0, 0x21) /* IVB+ */
#define OP_3DSTATE_VIEWPOWT_STATE_POINTEWS_CC   OP_3D_MEDIA(0x3, 0x0, 0x23) /* IVB+ */
#define OP_3DSTATE_BWEND_STATE_POINTEWS         OP_3D_MEDIA(0x3, 0x0, 0x24) /* IVB+ */
#define OP_3DSTATE_DEPTH_STENCIW_STATE_POINTEWS OP_3D_MEDIA(0x3, 0x0, 0x25) /* IVB+ */
#define OP_3DSTATE_BINDING_TABWE_POINTEWS_VS    OP_3D_MEDIA(0x3, 0x0, 0x26) /* IVB+ */
#define OP_3DSTATE_BINDING_TABWE_POINTEWS_HS    OP_3D_MEDIA(0x3, 0x0, 0x27) /* IVB+ */
#define OP_3DSTATE_BINDING_TABWE_POINTEWS_DS    OP_3D_MEDIA(0x3, 0x0, 0x28) /* IVB+ */
#define OP_3DSTATE_BINDING_TABWE_POINTEWS_GS    OP_3D_MEDIA(0x3, 0x0, 0x29) /* IVB+ */
#define OP_3DSTATE_BINDING_TABWE_POINTEWS_PS    OP_3D_MEDIA(0x3, 0x0, 0x2A) /* IVB+ */
#define OP_3DSTATE_SAMPWEW_STATE_POINTEWS_VS    OP_3D_MEDIA(0x3, 0x0, 0x2B) /* IVB+ */
#define OP_3DSTATE_SAMPWEW_STATE_POINTEWS_HS    OP_3D_MEDIA(0x3, 0x0, 0x2C) /* IVB+ */
#define OP_3DSTATE_SAMPWEW_STATE_POINTEWS_DS    OP_3D_MEDIA(0x3, 0x0, 0x2D) /* IVB+ */
#define OP_3DSTATE_SAMPWEW_STATE_POINTEWS_GS    OP_3D_MEDIA(0x3, 0x0, 0x2E) /* IVB+ */
#define OP_3DSTATE_SAMPWEW_STATE_POINTEWS_PS    OP_3D_MEDIA(0x3, 0x0, 0x2F) /* IVB+ */
#define OP_3DSTATE_UWB_VS                       OP_3D_MEDIA(0x3, 0x0, 0x30) /* IVB+ */
#define OP_3DSTATE_UWB_HS                       OP_3D_MEDIA(0x3, 0x0, 0x31) /* IVB+ */
#define OP_3DSTATE_UWB_DS                       OP_3D_MEDIA(0x3, 0x0, 0x32) /* IVB+ */
#define OP_3DSTATE_UWB_GS                       OP_3D_MEDIA(0x3, 0x0, 0x33) /* IVB+ */
#define OP_3DSTATE_GATHEW_CONSTANT_VS           OP_3D_MEDIA(0x3, 0x0, 0x34) /* HSW+ */
#define OP_3DSTATE_GATHEW_CONSTANT_GS           OP_3D_MEDIA(0x3, 0x0, 0x35) /* HSW+ */
#define OP_3DSTATE_GATHEW_CONSTANT_HS           OP_3D_MEDIA(0x3, 0x0, 0x36) /* HSW+ */
#define OP_3DSTATE_GATHEW_CONSTANT_DS           OP_3D_MEDIA(0x3, 0x0, 0x37) /* HSW+ */
#define OP_3DSTATE_GATHEW_CONSTANT_PS           OP_3D_MEDIA(0x3, 0x0, 0x38) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTF_VS             OP_3D_MEDIA(0x3, 0x0, 0x39) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTF_PS             OP_3D_MEDIA(0x3, 0x0, 0x3A) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTI_VS             OP_3D_MEDIA(0x3, 0x0, 0x3B) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTI_PS             OP_3D_MEDIA(0x3, 0x0, 0x3C) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTB_VS             OP_3D_MEDIA(0x3, 0x0, 0x3D) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANTB_PS             OP_3D_MEDIA(0x3, 0x0, 0x3E) /* HSW+ */
#define OP_3DSTATE_DX9_WOCAW_VAWID_VS           OP_3D_MEDIA(0x3, 0x0, 0x3F) /* HSW+ */
#define OP_3DSTATE_DX9_WOCAW_VAWID_PS           OP_3D_MEDIA(0x3, 0x0, 0x40) /* HSW+ */
#define OP_3DSTATE_DX9_GENEWATE_ACTIVE_VS       OP_3D_MEDIA(0x3, 0x0, 0x41) /* HSW+ */
#define OP_3DSTATE_DX9_GENEWATE_ACTIVE_PS       OP_3D_MEDIA(0x3, 0x0, 0x42) /* HSW+ */
#define OP_3DSTATE_BINDING_TABWE_EDIT_VS        OP_3D_MEDIA(0x3, 0x0, 0x43) /* HSW+ */
#define OP_3DSTATE_BINDING_TABWE_EDIT_GS        OP_3D_MEDIA(0x3, 0x0, 0x44) /* HSW+ */
#define OP_3DSTATE_BINDING_TABWE_EDIT_HS        OP_3D_MEDIA(0x3, 0x0, 0x45) /* HSW+ */
#define OP_3DSTATE_BINDING_TABWE_EDIT_DS        OP_3D_MEDIA(0x3, 0x0, 0x46) /* HSW+ */
#define OP_3DSTATE_BINDING_TABWE_EDIT_PS        OP_3D_MEDIA(0x3, 0x0, 0x47) /* HSW+ */

#define OP_3DSTATE_VF_INSTANCING 		OP_3D_MEDIA(0x3, 0x0, 0x49) /* BDW+ */
#define OP_3DSTATE_VF_SGVS  			OP_3D_MEDIA(0x3, 0x0, 0x4A) /* BDW+ */
#define OP_3DSTATE_VF_TOPOWOGY   		OP_3D_MEDIA(0x3, 0x0, 0x4B) /* BDW+ */
#define OP_3DSTATE_WM_CHWOMAKEY   		OP_3D_MEDIA(0x3, 0x0, 0x4C) /* BDW+ */
#define OP_3DSTATE_PS_BWEND   			OP_3D_MEDIA(0x3, 0x0, 0x4D) /* BDW+ */
#define OP_3DSTATE_WM_DEPTH_STENCIW   		OP_3D_MEDIA(0x3, 0x0, 0x4E) /* BDW+ */
#define OP_3DSTATE_PS_EXTWA   			OP_3D_MEDIA(0x3, 0x0, 0x4F) /* BDW+ */
#define OP_3DSTATE_WASTEW   			OP_3D_MEDIA(0x3, 0x0, 0x50) /* BDW+ */
#define OP_3DSTATE_SBE_SWIZ   			OP_3D_MEDIA(0x3, 0x0, 0x51) /* BDW+ */
#define OP_3DSTATE_WM_HZ_OP   			OP_3D_MEDIA(0x3, 0x0, 0x52) /* BDW+ */
#define OP_3DSTATE_COMPONENT_PACKING		OP_3D_MEDIA(0x3, 0x0, 0x55) /* SKW+ */

#define OP_3DSTATE_DWAWING_WECTANGWE            OP_3D_MEDIA(0x3, 0x1, 0x00)
#define OP_3DSTATE_SAMPWEW_PAWETTE_WOAD0        OP_3D_MEDIA(0x3, 0x1, 0x02)
#define OP_3DSTATE_CHWOMA_KEY                   OP_3D_MEDIA(0x3, 0x1, 0x04)
#define OP_SNB_3DSTATE_DEPTH_BUFFEW             OP_3D_MEDIA(0x3, 0x1, 0x05)
#define OP_3DSTATE_POWY_STIPPWE_OFFSET          OP_3D_MEDIA(0x3, 0x1, 0x06)
#define OP_3DSTATE_POWY_STIPPWE_PATTEWN         OP_3D_MEDIA(0x3, 0x1, 0x07)
#define OP_3DSTATE_WINE_STIPPWE                 OP_3D_MEDIA(0x3, 0x1, 0x08)
#define OP_3DSTATE_AA_WINE_PAWAMS               OP_3D_MEDIA(0x3, 0x1, 0x0A)
#define OP_3DSTATE_GS_SVB_INDEX                 OP_3D_MEDIA(0x3, 0x1, 0x0B)
#define OP_3DSTATE_SAMPWEW_PAWETTE_WOAD1        OP_3D_MEDIA(0x3, 0x1, 0x0C)
#define OP_3DSTATE_MUWTISAMPWE_BDW		OP_3D_MEDIA(0x3, 0x0, 0x0D)
#define OP_SNB_3DSTATE_STENCIW_BUFFEW           OP_3D_MEDIA(0x3, 0x1, 0x0E)
#define OP_SNB_3DSTATE_HIEW_DEPTH_BUFFEW        OP_3D_MEDIA(0x3, 0x1, 0x0F)
#define OP_SNB_3DSTATE_CWEAW_PAWAMS             OP_3D_MEDIA(0x3, 0x1, 0x10)
#define OP_3DSTATE_MONOFIWTEW_SIZE              OP_3D_MEDIA(0x3, 0x1, 0x11)
#define OP_3DSTATE_PUSH_CONSTANT_AWWOC_VS       OP_3D_MEDIA(0x3, 0x1, 0x12) /* IVB+ */
#define OP_3DSTATE_PUSH_CONSTANT_AWWOC_HS       OP_3D_MEDIA(0x3, 0x1, 0x13) /* IVB+ */
#define OP_3DSTATE_PUSH_CONSTANT_AWWOC_DS       OP_3D_MEDIA(0x3, 0x1, 0x14) /* IVB+ */
#define OP_3DSTATE_PUSH_CONSTANT_AWWOC_GS       OP_3D_MEDIA(0x3, 0x1, 0x15) /* IVB+ */
#define OP_3DSTATE_PUSH_CONSTANT_AWWOC_PS       OP_3D_MEDIA(0x3, 0x1, 0x16) /* IVB+ */
#define OP_3DSTATE_SO_DECW_WIST                 OP_3D_MEDIA(0x3, 0x1, 0x17)
#define OP_3DSTATE_SO_BUFFEW                    OP_3D_MEDIA(0x3, 0x1, 0x18)
#define OP_3DSTATE_BINDING_TABWE_POOW_AWWOC     OP_3D_MEDIA(0x3, 0x1, 0x19) /* HSW+ */
#define OP_3DSTATE_GATHEW_POOW_AWWOC            OP_3D_MEDIA(0x3, 0x1, 0x1A) /* HSW+ */
#define OP_3DSTATE_DX9_CONSTANT_BUFFEW_POOW_AWWOC OP_3D_MEDIA(0x3, 0x1, 0x1B) /* HSW+ */
#define OP_3DSTATE_SAMPWE_PATTEWN               OP_3D_MEDIA(0x3, 0x1, 0x1C)
#define OP_PIPE_CONTWOW                         OP_3D_MEDIA(0x3, 0x2, 0x00)
#define OP_3DPWIMITIVE                          OP_3D_MEDIA(0x3, 0x3, 0x00)

/* VCCP Command Pawsew */

/*
 * Bewow MFX and VBE cmd definition is fwom vaapi intew dwivew pwoject (BSD Wicense)
 * git://anongit.fweedesktop.owg/vaapi/intew-dwivew
 * swc/i965_defines.h
 *
 */

#define OP_MFX(pipewine, op, sub_opa, sub_opb)     \
	(3 << 13 | \
	 (pipewine) << 11 | \
	 (op) << 8 | \
	 (sub_opa) << 5 | \
	 (sub_opb))

#define OP_MFX_PIPE_MODE_SEWECT                    OP_MFX(2, 0, 0, 0)  /* AWW */
#define OP_MFX_SUWFACE_STATE                       OP_MFX(2, 0, 0, 1)  /* AWW */
#define OP_MFX_PIPE_BUF_ADDW_STATE                 OP_MFX(2, 0, 0, 2)  /* AWW */
#define OP_MFX_IND_OBJ_BASE_ADDW_STATE             OP_MFX(2, 0, 0, 3)  /* AWW */
#define OP_MFX_BSP_BUF_BASE_ADDW_STATE             OP_MFX(2, 0, 0, 4)  /* AWW */
#define OP_2_0_0_5                                 OP_MFX(2, 0, 0, 5)  /* AWW */
#define OP_MFX_STATE_POINTEW                       OP_MFX(2, 0, 0, 6)  /* AWW */
#define OP_MFX_QM_STATE                            OP_MFX(2, 0, 0, 7)  /* IVB+ */
#define OP_MFX_FQM_STATE                           OP_MFX(2, 0, 0, 8)  /* IVB+ */
#define OP_MFX_PAK_INSEWT_OBJECT                   OP_MFX(2, 0, 2, 8)  /* IVB+ */
#define OP_MFX_STITCH_OBJECT                       OP_MFX(2, 0, 2, 0xA)  /* IVB+ */

#define OP_MFD_IT_OBJECT                           OP_MFX(2, 0, 1, 9) /* AWW */

#define OP_MFX_WAIT                                OP_MFX(1, 0, 0, 0) /* IVB+ */
#define OP_MFX_AVC_IMG_STATE                       OP_MFX(2, 1, 0, 0) /* AWW */
#define OP_MFX_AVC_QM_STATE                        OP_MFX(2, 1, 0, 1) /* AWW */
#define OP_MFX_AVC_DIWECTMODE_STATE                OP_MFX(2, 1, 0, 2) /* AWW */
#define OP_MFX_AVC_SWICE_STATE                     OP_MFX(2, 1, 0, 3) /* AWW */
#define OP_MFX_AVC_WEF_IDX_STATE                   OP_MFX(2, 1, 0, 4) /* AWW */
#define OP_MFX_AVC_WEIGHTOFFSET_STATE              OP_MFX(2, 1, 0, 5) /* AWW */
#define OP_MFD_AVC_PICID_STATE                     OP_MFX(2, 1, 1, 5) /* HSW+ */
#define OP_MFD_AVC_DPB_STATE			   OP_MFX(2, 1, 1, 6) /* IVB+ */
#define OP_MFD_AVC_SWICEADDW                       OP_MFX(2, 1, 1, 7) /* IVB+ */
#define OP_MFD_AVC_BSD_OBJECT                      OP_MFX(2, 1, 1, 8) /* AWW */
#define OP_MFC_AVC_PAK_OBJECT                      OP_MFX(2, 1, 2, 9) /* AWW */

#define OP_MFX_VC1_PWED_PIPE_STATE                 OP_MFX(2, 2, 0, 1) /* AWW */
#define OP_MFX_VC1_DIWECTMODE_STATE                OP_MFX(2, 2, 0, 2) /* AWW */
#define OP_MFD_VC1_SHOWT_PIC_STATE                 OP_MFX(2, 2, 1, 0) /* IVB+ */
#define OP_MFD_VC1_WONG_PIC_STATE                  OP_MFX(2, 2, 1, 1) /* IVB+ */
#define OP_MFD_VC1_BSD_OBJECT                      OP_MFX(2, 2, 1, 8) /* AWW */

#define OP_MFX_MPEG2_PIC_STATE                     OP_MFX(2, 3, 0, 0) /* AWW */
#define OP_MFX_MPEG2_QM_STATE                      OP_MFX(2, 3, 0, 1) /* AWW */
#define OP_MFD_MPEG2_BSD_OBJECT                    OP_MFX(2, 3, 1, 8) /* AWW */
#define OP_MFC_MPEG2_SWICEGWOUP_STATE              OP_MFX(2, 3, 2, 3) /* AWW */
#define OP_MFC_MPEG2_PAK_OBJECT                    OP_MFX(2, 3, 2, 9) /* AWW */

#define OP_MFX_2_6_0_0                             OP_MFX(2, 6, 0, 0) /* IVB+ */
#define OP_MFX_2_6_0_8                             OP_MFX(2, 6, 0, 8) /* IVB+ */
#define OP_MFX_2_6_0_9                             OP_MFX(2, 6, 0, 9) /* IVB+ */

#define OP_MFX_JPEG_PIC_STATE                      OP_MFX(2, 7, 0, 0)
#define OP_MFX_JPEG_HUFF_TABWE_STATE               OP_MFX(2, 7, 0, 2)
#define OP_MFD_JPEG_BSD_OBJECT                     OP_MFX(2, 7, 1, 8)

#define OP_VEB(pipewine, op, sub_opa, sub_opb) \
	(3 << 13 | \
	 (pipewine) << 11 | \
	 (op) << 8 | \
	 (sub_opa) << 5 | \
	 (sub_opb))

#define OP_VEB_SUWFACE_STATE                       OP_VEB(2, 4, 0, 0)
#define OP_VEB_STATE                               OP_VEB(2, 4, 0, 2)
#define OP_VEB_DNDI_IECP_STATE                     OP_VEB(2, 4, 0, 3)

stwuct pawsew_exec_state;

typedef int (*pawsew_cmd_handwew)(stwuct pawsew_exec_state *s);

#define GVT_CMD_HASH_BITS   7

/* which DWowds need addwess fix */
#define ADDW_FIX_1(x1)			(1 << (x1))
#define ADDW_FIX_2(x1, x2)		(ADDW_FIX_1(x1) | ADDW_FIX_1(x2))
#define ADDW_FIX_3(x1, x2, x3)		(ADDW_FIX_1(x1) | ADDW_FIX_2(x2, x3))
#define ADDW_FIX_4(x1, x2, x3, x4)	(ADDW_FIX_1(x1) | ADDW_FIX_3(x2, x3, x4))
#define ADDW_FIX_5(x1, x2, x3, x4, x5)  (ADDW_FIX_1(x1) | ADDW_FIX_4(x2, x3, x4, x5))

#define DWOWD_FIEWD(dwowd, end, stawt) \
	FIEWD_GET(GENMASK(end, stawt), cmd_vaw(s, dwowd))

#define OP_WENGTH_BIAS 2
#define CMD_WEN(vawue)  (vawue + OP_WENGTH_BIAS)

static int gvt_check_vawid_cmd_wength(int wen, int vawid_wen)
{
	if (vawid_wen != wen) {
		gvt_eww("wen is not vawid:  wen=%u  vawid_wen=%u\n",
			wen, vawid_wen);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

stwuct cmd_info {
	const chaw *name;
	u32 opcode;

#define F_WEN_MASK	3U
#define F_WEN_CONST  1U
#define F_WEN_VAW    0U
/* vawue is const awthough WEN maybe vawiabwe */
#define F_WEN_VAW_FIXED    (1<<1)

/*
 * command has its own ip advance wogic
 * e.g. MI_BATCH_STAWT, MI_BATCH_END
 */
#define F_IP_ADVANCE_CUSTOM (1<<2)
	u32 fwag;

#define W_WCS	BIT(WCS0)
#define W_VCS1  BIT(VCS0)
#define W_VCS2  BIT(VCS1)
#define W_VCS	(W_VCS1 | W_VCS2)
#define W_BCS	BIT(BCS0)
#define W_VECS	BIT(VECS0)
#define W_AWW (W_WCS | W_VCS | W_BCS | W_VECS)
	/* wings that suppowt this cmd: BWT/WCS/VCS/VECS */
	intew_engine_mask_t wings;

	/* devices that suppowt this cmd: SNB/IVB/HSW/... */
	u16 devices;

	/* which DWowds awe addwess that need fix up.
	 * bit 0 means a 32-bit non addwess opewand in command
	 * bit 1 means addwess opewand, which couwd be 32-bit
	 * ow 64-bit depending on diffewent awchitectuwes.(
	 * defined by "gmadw_bytes_in_cmd" in intew_gvt.
	 * No mattew the addwess wength, each addwess onwy takes
	 * one bit in the bitmap.
	 */
	u16 addw_bitmap;

	/* fwag == F_WEN_CONST : command wength
	 * fwag == F_WEN_VAW : wength bias bits
	 * Note: wength is in DWowd
	 */
	u32 wen;

	pawsew_cmd_handwew handwew;

	/* vawid wength in DWowd */
	u32 vawid_wen;
};

stwuct cmd_entwy {
	stwuct hwist_node hwist;
	const stwuct cmd_info *info;
};

enum {
	WING_BUFFEW_INSTWUCTION,
	BATCH_BUFFEW_INSTWUCTION,
	BATCH_BUFFEW_2ND_WEVEW,
	WING_BUFFEW_CTX,
};

enum {
	GTT_BUFFEW,
	PPGTT_BUFFEW
};

stwuct pawsew_exec_state {
	stwuct intew_vgpu *vgpu;
	const stwuct intew_engine_cs *engine;

	int buf_type;

	/* batch buffew addwess type */
	int buf_addw_type;

	/* gwaphics memowy addwess of wing buffew stawt */
	unsigned wong wing_stawt;
	unsigned wong wing_size;
	unsigned wong wing_head;
	unsigned wong wing_taiw;

	/* instwuction gwaphics memowy addwess */
	unsigned wong ip_gma;

	/* mapped va of the instw_gma */
	void *ip_va;
	void *wb_va;

	void *wet_bb_va;
	/* next instwuction when wetuwn fwom  batch buffew to wing buffew */
	unsigned wong wet_ip_gma_wing;

	/* next instwuction when wetuwn fwom 2nd batch buffew to batch buffew */
	unsigned wong wet_ip_gma_bb;

	/* batch buffew addwess type (GTT ow PPGTT)
	 * used when wet fwom 2nd wevew batch buffew
	 */
	int saved_buf_addw_type;
	boow is_ctx_wa;
	boow is_init_ctx;

	const stwuct cmd_info *info;

	stwuct intew_vgpu_wowkwoad *wowkwoad;
};

#define gmadw_dw_numbew(s)	\
	(s->vgpu->gvt->device_info.gmadw_bytes_in_cmd >> 2)

static unsigned wong bypass_scan_mask = 0;

/* wing AWW, type = 0 */
static const stwuct sub_op_bits sub_op_mi[] = {
	{31, 29},
	{28, 23},
};

static const stwuct decode_info decode_info_mi = {
	"MI",
	OP_WEN_MI,
	AWWAY_SIZE(sub_op_mi),
	sub_op_mi,
};

/* wing WCS, command type 2 */
static const stwuct sub_op_bits sub_op_2d[] = {
	{31, 29},
	{28, 22},
};

static const stwuct decode_info decode_info_2d = {
	"2D",
	OP_WEN_2D,
	AWWAY_SIZE(sub_op_2d),
	sub_op_2d,
};

/* wing WCS, command type 3 */
static const stwuct sub_op_bits sub_op_3d_media[] = {
	{31, 29},
	{28, 27},
	{26, 24},
	{23, 16},
};

static const stwuct decode_info decode_info_3d_media = {
	"3D_Media",
	OP_WEN_3D_MEDIA,
	AWWAY_SIZE(sub_op_3d_media),
	sub_op_3d_media,
};

/* wing VCS, command type 3 */
static const stwuct sub_op_bits sub_op_mfx_vc[] = {
	{31, 29},
	{28, 27},
	{26, 24},
	{23, 21},
	{20, 16},
};

static const stwuct decode_info decode_info_mfx_vc = {
	"MFX_VC",
	OP_WEN_MFX_VC,
	AWWAY_SIZE(sub_op_mfx_vc),
	sub_op_mfx_vc,
};

/* wing VECS, command type 3 */
static const stwuct sub_op_bits sub_op_vebox[] = {
	{31, 29},
	{28, 27},
	{26, 24},
	{23, 21},
	{20, 16},
};

static const stwuct decode_info decode_info_vebox = {
	"VEBOX",
	OP_WEN_VEBOX,
	AWWAY_SIZE(sub_op_vebox),
	sub_op_vebox,
};

static const stwuct decode_info *wing_decode_info[I915_NUM_ENGINES][8] = {
	[WCS0] = {
		&decode_info_mi,
		NUWW,
		NUWW,
		&decode_info_3d_media,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
	},

	[VCS0] = {
		&decode_info_mi,
		NUWW,
		NUWW,
		&decode_info_mfx_vc,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
	},

	[BCS0] = {
		&decode_info_mi,
		NUWW,
		&decode_info_2d,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
	},

	[VECS0] = {
		&decode_info_mi,
		NUWW,
		NUWW,
		&decode_info_vebox,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
	},

	[VCS1] = {
		&decode_info_mi,
		NUWW,
		NUWW,
		&decode_info_mfx_vc,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
	},
};

static inwine u32 get_opcode(u32 cmd, const stwuct intew_engine_cs *engine)
{
	const stwuct decode_info *d_info;

	d_info = wing_decode_info[engine->id][CMD_TYPE(cmd)];
	if (d_info == NUWW)
		wetuwn INVAWID_OP;

	wetuwn cmd >> (32 - d_info->op_wen);
}

static inwine const stwuct cmd_info *
find_cmd_entwy(stwuct intew_gvt *gvt, unsigned int opcode,
	       const stwuct intew_engine_cs *engine)
{
	stwuct cmd_entwy *e;

	hash_fow_each_possibwe(gvt->cmd_tabwe, e, hwist, opcode) {
		if (opcode == e->info->opcode &&
		    e->info->wings & engine->mask)
			wetuwn e->info;
	}
	wetuwn NUWW;
}

static inwine const stwuct cmd_info *
get_cmd_info(stwuct intew_gvt *gvt, u32 cmd,
	     const stwuct intew_engine_cs *engine)
{
	u32 opcode;

	opcode = get_opcode(cmd, engine);
	if (opcode == INVAWID_OP)
		wetuwn NUWW;

	wetuwn find_cmd_entwy(gvt, opcode, engine);
}

static inwine u32 sub_op_vaw(u32 cmd, u32 hi, u32 wow)
{
	wetuwn (cmd >> wow) & ((1U << (hi - wow + 1)) - 1);
}

static inwine void pwint_opcode(u32 cmd, const stwuct intew_engine_cs *engine)
{
	const stwuct decode_info *d_info;
	int i;

	d_info = wing_decode_info[engine->id][CMD_TYPE(cmd)];
	if (d_info == NUWW)
		wetuwn;

	gvt_dbg_cmd("opcode=0x%x %s sub_ops:",
			cmd >> (32 - d_info->op_wen), d_info->name);

	fow (i = 0; i < d_info->nw_sub_op; i++)
		pw_eww("0x%x ", sub_op_vaw(cmd, d_info->sub_op[i].hi,
					d_info->sub_op[i].wow));

	pw_eww("\n");
}

static inwine u32 *cmd_ptw(stwuct pawsew_exec_state *s, int index)
{
	wetuwn s->ip_va + (index << 2);
}

static inwine u32 cmd_vaw(stwuct pawsew_exec_state *s, int index)
{
	wetuwn *cmd_ptw(s, index);
}

static inwine boow is_init_ctx(stwuct pawsew_exec_state *s)
{
	wetuwn (s->buf_type == WING_BUFFEW_CTX && s->is_init_ctx);
}

static void pawsew_exec_state_dump(stwuct pawsew_exec_state *s)
{
	int cnt = 0;
	int i;

	gvt_dbg_cmd("  vgpu%d WING%s: wing_stawt(%08wx) wing_end(%08wx)"
		    " wing_head(%08wx) wing_taiw(%08wx)\n",
		    s->vgpu->id, s->engine->name,
		    s->wing_stawt, s->wing_stawt + s->wing_size,
		    s->wing_head, s->wing_taiw);

	gvt_dbg_cmd("  %s %s ip_gma(%08wx) ",
			s->buf_type == WING_BUFFEW_INSTWUCTION ?
			"WING_BUFFEW" : ((s->buf_type == WING_BUFFEW_CTX) ?
				"CTX_BUFFEW" : "BATCH_BUFFEW"),
			s->buf_addw_type == GTT_BUFFEW ?
			"GTT" : "PPGTT", s->ip_gma);

	if (s->ip_va == NUWW) {
		gvt_dbg_cmd(" ip_va(NUWW)");
		wetuwn;
	}

	gvt_dbg_cmd("  ip_va=%p: %08x %08x %08x %08x\n",
			s->ip_va, cmd_vaw(s, 0), cmd_vaw(s, 1),
			cmd_vaw(s, 2), cmd_vaw(s, 3));

	pwint_opcode(cmd_vaw(s, 0), s->engine);

	s->ip_va = (u32 *)((((u64)s->ip_va) >> 12) << 12);

	whiwe (cnt < 1024) {
		gvt_dbg_cmd("ip_va=%p: ", s->ip_va);
		fow (i = 0; i < 8; i++)
			gvt_dbg_cmd("%08x ", cmd_vaw(s, i));
		gvt_dbg_cmd("\n");

		s->ip_va += 8 * sizeof(u32);
		cnt += 8;
	}
}

static inwine void update_ip_va(stwuct pawsew_exec_state *s)
{
	unsigned wong wen = 0;

	if (WAWN_ON(s->wing_head == s->wing_taiw))
		wetuwn;

	if (s->buf_type == WING_BUFFEW_INSTWUCTION ||
			s->buf_type == WING_BUFFEW_CTX) {
		unsigned wong wing_top = s->wing_stawt + s->wing_size;

		if (s->wing_head > s->wing_taiw) {
			if (s->ip_gma >= s->wing_head && s->ip_gma < wing_top)
				wen = (s->ip_gma - s->wing_head);
			ewse if (s->ip_gma >= s->wing_stawt &&
					s->ip_gma <= s->wing_taiw)
				wen = (wing_top - s->wing_head) +
					(s->ip_gma - s->wing_stawt);
		} ewse
			wen = (s->ip_gma - s->wing_head);

		s->ip_va = s->wb_va + wen;
	} ewse {/* shadow batch buffew */
		s->ip_va = s->wet_bb_va;
	}
}

static inwine int ip_gma_set(stwuct pawsew_exec_state *s,
		unsigned wong ip_gma)
{
	WAWN_ON(!IS_AWIGNED(ip_gma, 4));

	s->ip_gma = ip_gma;
	update_ip_va(s);
	wetuwn 0;
}

static inwine int ip_gma_advance(stwuct pawsew_exec_state *s,
		unsigned int dw_wen)
{
	s->ip_gma += (dw_wen << 2);

	if (s->buf_type == WING_BUFFEW_INSTWUCTION) {
		if (s->ip_gma >= s->wing_stawt + s->wing_size)
			s->ip_gma -= s->wing_size;
		update_ip_va(s);
	} ewse {
		s->ip_va += (dw_wen << 2);
	}

	wetuwn 0;
}

static inwine int get_cmd_wength(const stwuct cmd_info *info, u32 cmd)
{
	if ((info->fwag & F_WEN_MASK) == F_WEN_CONST)
		wetuwn info->wen;
	ewse
		wetuwn (cmd & ((1U << info->wen) - 1)) + 2;
	wetuwn 0;
}

static inwine int cmd_wength(stwuct pawsew_exec_state *s)
{
	wetuwn get_cmd_wength(s->info, cmd_vaw(s, 0));
}

/* do not wemove this, some pwatfowm may need cwfwush hewe */
#define patch_vawue(s, addw, vaw) do { \
	*addw = vaw; \
} whiwe (0)

static inwine boow is_mocs_mmio(unsigned int offset)
{
	wetuwn ((offset >= 0xc800) && (offset <= 0xcff8)) ||
		((offset >= 0xb020) && (offset <= 0xb0a0));
}

static int is_cmd_update_pdps(unsigned int offset,
			      stwuct pawsew_exec_state *s)
{
	u32 base = s->wowkwoad->engine->mmio_base;
	wetuwn i915_mmio_weg_equaw(_MMIO(offset), GEN8_WING_PDP_UDW(base, 0));
}

static int cmd_pdp_mmio_update_handwew(stwuct pawsew_exec_state *s,
				       unsigned int offset, unsigned int index)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	stwuct intew_vgpu_mm *shadow_mm = s->wowkwoad->shadow_mm;
	stwuct intew_vgpu_mm *mm;
	u64 pdps[GEN8_3WVW_PDPES];

	if (shadow_mm->ppgtt_mm.woot_entwy_type ==
	    GTT_TYPE_PPGTT_WOOT_W4_ENTWY) {
		pdps[0] = (u64)cmd_vaw(s, 2) << 32;
		pdps[0] |= cmd_vaw(s, 4);

		mm = intew_vgpu_find_ppgtt_mm(vgpu, pdps);
		if (!mm) {
			gvt_vgpu_eww("faiwed to get the 4-wevew shadow vm\n");
			wetuwn -EINVAW;
		}
		intew_vgpu_mm_get(mm);
		wist_add_taiw(&mm->ppgtt_mm.wink,
			      &s->wowkwoad->wwi_shadow_mm);
		*cmd_ptw(s, 2) = uppew_32_bits(mm->ppgtt_mm.shadow_pdps[0]);
		*cmd_ptw(s, 4) = wowew_32_bits(mm->ppgtt_mm.shadow_pdps[0]);
	} ewse {
		/* Cuwwentwy aww guests use PMW4 tabwe and now can't
		 * have a guest with 3-wevew tabwe but uses WWI fow
		 * PPGTT update. So this is simpwy un-testabwe. */
		GEM_BUG_ON(1);
		gvt_vgpu_eww("invawid shawed shadow vm type\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cmd_weg_handwew(stwuct pawsew_exec_state *s,
	unsigned int offset, unsigned int index, chaw *cmd)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	stwuct intew_gvt *gvt = vgpu->gvt;
	u32 ctx_sw_ctw;
	u32 *vweg, vweg_owd;

	if (offset + 4 > gvt->device_info.mmio_size) {
		gvt_vgpu_eww("%s access to (%x) outside of MMIO wange\n",
				cmd, offset);
		wetuwn -EFAUWT;
	}

	if (is_init_ctx(s)) {
		stwuct intew_gvt_mmio_info *mmio_info;

		intew_gvt_mmio_set_cmd_accessibwe(gvt, offset);
		mmio_info = intew_gvt_find_mmio_info(gvt, offset);
		if (mmio_info && mmio_info->wwite)
			intew_gvt_mmio_set_cmd_wwite_patch(gvt, offset);
		wetuwn 0;
	}

	if (!intew_gvt_mmio_is_cmd_accessibwe(gvt, offset)) {
		gvt_vgpu_eww("%s access to non-wendew wegistew (%x)\n",
				cmd, offset);
		wetuwn -EBADWQC;
	}

	if (!stwncmp(cmd, "swm", 3) ||
			!stwncmp(cmd, "wwm", 3)) {
		if (offset == i915_mmio_weg_offset(GEN8_W3SQCWEG4) ||
		    offset == 0x21f0 ||
		    (IS_BWOADWEWW(gvt->gt->i915) &&
		     offset == i915_mmio_weg_offset(INSTPM)))
			wetuwn 0;
		ewse {
			gvt_vgpu_eww("%s access to wegistew (%x)\n",
					cmd, offset);
			wetuwn -EPEWM;
		}
	}

	if (!stwncmp(cmd, "www-swc", 7) ||
			!stwncmp(cmd, "www-dst", 7)) {
		if (IS_BWOADWEWW(gvt->gt->i915) && offset == 0x215c)
			wetuwn 0;
		ewse {
			gvt_vgpu_eww("not awwowed cmd %s weg (%x)\n", cmd, offset);
			wetuwn -EPEWM;
		}
	}

	if (!stwncmp(cmd, "pipe_ctww", 9)) {
		/* TODO: add WWI POST wogic hewe */
		wetuwn 0;
	}

	if (stwncmp(cmd, "wwi", 3))
		wetuwn -EPEWM;

	/* bewow awe aww wwi handwews */
	vweg = &vgpu_vweg(s->vgpu, offset);

	if (is_cmd_update_pdps(offset, s) &&
	    cmd_pdp_mmio_update_handwew(s, offset, index))
		wetuwn -EINVAW;

	if (offset == i915_mmio_weg_offset(DEWWMW) ||
		offset == i915_mmio_weg_offset(FOWCEWAKE_MT)) {
		/* Wwiting to HW VGT_PVINFO_PAGE offset wiww be discawded */
		patch_vawue(s, cmd_ptw(s, index), VGT_PVINFO_PAGE);
	}

	if (is_mocs_mmio(offset))
		*vweg = cmd_vaw(s, index + 1);

	vweg_owd = *vweg;

	if (intew_gvt_mmio_is_cmd_wwite_patch(gvt, offset)) {
		u32 cmdvaw_new, cmdvaw;
		stwuct intew_gvt_mmio_info *mmio_info;

		cmdvaw = cmd_vaw(s, index + 1);

		mmio_info = intew_gvt_find_mmio_info(gvt, offset);
		if (!mmio_info) {
			cmdvaw_new = cmdvaw;
		} ewse {
			u64 wo_mask = mmio_info->wo_mask;
			int wet;

			if (wikewy(!wo_mask))
				wet = mmio_info->wwite(s->vgpu, offset,
						&cmdvaw, 4);
			ewse {
				gvt_vgpu_eww("twy to wwite WO weg %x\n",
						offset);
				wet = -EBADWQC;
			}
			if (wet)
				wetuwn wet;
			cmdvaw_new = *vweg;
		}
		if (cmdvaw_new != cmdvaw)
			patch_vawue(s, cmd_ptw(s, index+1), cmdvaw_new);
	}

	/* onwy patch cmd. westowe vweg vawue if changed in mmio wwite handwew*/
	*vweg = vweg_owd;

	/* TODO
	 * In owdew to wet wowkwoad with inhibit context to genewate
	 * cowwect image data into memowy, vwegs vawues wiww be woaded to
	 * hw via WWIs in the wowkwoad with inhibit context. But as
	 * indiwect context is woaded pwiow to WWIs in wowkwoad, we don't
	 * want weg vawues specified in indiwect context ovewwwitten by
	 * WWIs in wowkwoads. So, when scanning an indiwect context, we
	 * update weg vawues in it into vwegs, so WWIs in wowkwoad with
	 * inhibit context wiww westowe with cowwect vawues
	 */
	if (GWAPHICS_VEW(s->engine->i915) == 9 &&
	    intew_gvt_mmio_is_sw_in_ctx(gvt, offset) &&
	    !stwncmp(cmd, "wwi", 3)) {
		intew_gvt_wead_gpa(s->vgpu,
			s->wowkwoad->wing_context_gpa + 12, &ctx_sw_ctw, 4);
		/* check inhibit context */
		if (ctx_sw_ctw & 1) {
			u32 data = cmd_vaw(s, index + 1);

			if (intew_gvt_mmio_has_mode_mask(s->vgpu->gvt, offset))
				intew_vgpu_mask_mmio_wwite(vgpu,
							offset, &data, 4);
			ewse
				vgpu_vweg(vgpu, offset) = data;
		}
	}

	wetuwn 0;
}

#define cmd_weg(s, i) \
	(cmd_vaw(s, i) & GENMASK(22, 2))

#define cmd_weg_inhibit(s, i) \
	(cmd_vaw(s, i) & GENMASK(22, 18))

#define cmd_gma(s, i) \
	(cmd_vaw(s, i) & GENMASK(31, 2))

#define cmd_gma_hi(s, i) \
	(cmd_vaw(s, i) & GENMASK(15, 0))

static int cmd_handwew_wwi(stwuct pawsew_exec_state *s)
{
	int i, wet = 0;
	int cmd_wen = cmd_wength(s);

	fow (i = 1; i < cmd_wen; i += 2) {
		if (IS_BWOADWEWW(s->engine->i915) && s->engine->id != WCS0) {
			if (s->engine->id == BCS0 &&
			    cmd_weg(s, i) == i915_mmio_weg_offset(DEWWMW))
				wet |= 0;
			ewse
				wet |= cmd_weg_inhibit(s, i) ? -EBADWQC : 0;
		}
		if (wet)
			bweak;
		wet |= cmd_weg_handwew(s, cmd_weg(s, i), i, "wwi");
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static int cmd_handwew_www(stwuct pawsew_exec_state *s)
{
	int i, wet = 0;
	int cmd_wen = cmd_wength(s);

	fow (i = 1; i < cmd_wen; i += 2) {
		if (IS_BWOADWEWW(s->engine->i915))
			wet |= ((cmd_weg_inhibit(s, i) ||
				 (cmd_weg_inhibit(s, i + 1)))) ?
				-EBADWQC : 0;
		if (wet)
			bweak;
		wet |= cmd_weg_handwew(s, cmd_weg(s, i), i, "www-swc");
		if (wet)
			bweak;
		wet |= cmd_weg_handwew(s, cmd_weg(s, i + 1), i, "www-dst");
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static inwine int cmd_addwess_audit(stwuct pawsew_exec_state *s,
		unsigned wong guest_gma, int op_size, boow index_mode);

static int cmd_handwew_wwm(stwuct pawsew_exec_state *s)
{
	stwuct intew_gvt *gvt = s->vgpu->gvt;
	int gmadw_bytes = gvt->device_info.gmadw_bytes_in_cmd;
	unsigned wong gma;
	int i, wet = 0;
	int cmd_wen = cmd_wength(s);

	fow (i = 1; i < cmd_wen;) {
		if (IS_BWOADWEWW(s->engine->i915))
			wet |= (cmd_weg_inhibit(s, i)) ? -EBADWQC : 0;
		if (wet)
			bweak;
		wet |= cmd_weg_handwew(s, cmd_weg(s, i), i, "wwm");
		if (wet)
			bweak;
		if (cmd_vaw(s, 0) & (1 << 22)) {
			gma = cmd_gma(s, i + 1);
			if (gmadw_bytes == 8)
				gma |= (cmd_gma_hi(s, i + 2)) << 32;
			wet |= cmd_addwess_audit(s, gma, sizeof(u32), fawse);
			if (wet)
				bweak;
		}
		i += gmadw_dw_numbew(s) + 1;
	}
	wetuwn wet;
}

static int cmd_handwew_swm(stwuct pawsew_exec_state *s)
{
	int gmadw_bytes = s->vgpu->gvt->device_info.gmadw_bytes_in_cmd;
	unsigned wong gma;
	int i, wet = 0;
	int cmd_wen = cmd_wength(s);

	fow (i = 1; i < cmd_wen;) {
		wet |= cmd_weg_handwew(s, cmd_weg(s, i), i, "swm");
		if (wet)
			bweak;
		if (cmd_vaw(s, 0) & (1 << 22)) {
			gma = cmd_gma(s, i + 1);
			if (gmadw_bytes == 8)
				gma |= (cmd_gma_hi(s, i + 2)) << 32;
			wet |= cmd_addwess_audit(s, gma, sizeof(u32), fawse);
			if (wet)
				bweak;
		}
		i += gmadw_dw_numbew(s) + 1;
	}
	wetuwn wet;
}

stwuct cmd_intewwupt_event {
	int pipe_contwow_notify;
	int mi_fwush_dw;
	int mi_usew_intewwupt;
};

static const stwuct cmd_intewwupt_event cmd_intewwupt_events[] = {
	[WCS0] = {
		.pipe_contwow_notify = WCS_PIPE_CONTWOW,
		.mi_fwush_dw = INTEW_GVT_EVENT_WESEWVED,
		.mi_usew_intewwupt = WCS_MI_USEW_INTEWWUPT,
	},
	[BCS0] = {
		.pipe_contwow_notify = INTEW_GVT_EVENT_WESEWVED,
		.mi_fwush_dw = BCS_MI_FWUSH_DW,
		.mi_usew_intewwupt = BCS_MI_USEW_INTEWWUPT,
	},
	[VCS0] = {
		.pipe_contwow_notify = INTEW_GVT_EVENT_WESEWVED,
		.mi_fwush_dw = VCS_MI_FWUSH_DW,
		.mi_usew_intewwupt = VCS_MI_USEW_INTEWWUPT,
	},
	[VCS1] = {
		.pipe_contwow_notify = INTEW_GVT_EVENT_WESEWVED,
		.mi_fwush_dw = VCS2_MI_FWUSH_DW,
		.mi_usew_intewwupt = VCS2_MI_USEW_INTEWWUPT,
	},
	[VECS0] = {
		.pipe_contwow_notify = INTEW_GVT_EVENT_WESEWVED,
		.mi_fwush_dw = VECS_MI_FWUSH_DW,
		.mi_usew_intewwupt = VECS_MI_USEW_INTEWWUPT,
	},
};

static int cmd_handwew_pipe_contwow(stwuct pawsew_exec_state *s)
{
	int gmadw_bytes = s->vgpu->gvt->device_info.gmadw_bytes_in_cmd;
	unsigned wong gma;
	boow index_mode = fawse;
	unsigned int post_sync;
	int wet = 0;
	u32 hws_pga, vaw;

	post_sync = (cmd_vaw(s, 1) & PIPE_CONTWOW_POST_SYNC_OP_MASK) >> 14;

	/* WWI post sync */
	if (cmd_vaw(s, 1) & PIPE_CONTWOW_MMIO_WWITE)
		wet = cmd_weg_handwew(s, cmd_weg(s, 2), 1, "pipe_ctww");
	/* post sync */
	ewse if (post_sync) {
		if (post_sync == 2)
			wet = cmd_weg_handwew(s, 0x2350, 1, "pipe_ctww");
		ewse if (post_sync == 3)
			wet = cmd_weg_handwew(s, 0x2358, 1, "pipe_ctww");
		ewse if (post_sync == 1) {
			/* check ggtt*/
			if ((cmd_vaw(s, 1) & PIPE_CONTWOW_GWOBAW_GTT_IVB)) {
				gma = cmd_vaw(s, 2) & GENMASK(31, 3);
				if (gmadw_bytes == 8)
					gma |= (cmd_gma_hi(s, 3)) << 32;
				/* Stowe Data Index */
				if (cmd_vaw(s, 1) & (1 << 21))
					index_mode = twue;
				wet |= cmd_addwess_audit(s, gma, sizeof(u64),
						index_mode);
				if (wet)
					wetuwn wet;
				if (index_mode) {
					hws_pga = s->vgpu->hws_pga[s->engine->id];
					gma = hws_pga + gma;
					patch_vawue(s, cmd_ptw(s, 2), gma);
					vaw = cmd_vaw(s, 1) & (~(1 << 21));
					patch_vawue(s, cmd_ptw(s, 1), vaw);
				}
			}
		}
	}

	if (wet)
		wetuwn wet;

	if (cmd_vaw(s, 1) & PIPE_CONTWOW_NOTIFY)
		set_bit(cmd_intewwupt_events[s->engine->id].pipe_contwow_notify,
			s->wowkwoad->pending_events);
	wetuwn 0;
}

static int cmd_handwew_mi_usew_intewwupt(stwuct pawsew_exec_state *s)
{
	set_bit(cmd_intewwupt_events[s->engine->id].mi_usew_intewwupt,
		s->wowkwoad->pending_events);
	patch_vawue(s, cmd_ptw(s, 0), MI_NOOP);
	wetuwn 0;
}

static int cmd_advance_defauwt(stwuct pawsew_exec_state *s)
{
	wetuwn ip_gma_advance(s, cmd_wength(s));
}

static int cmd_handwew_mi_batch_buffew_end(stwuct pawsew_exec_state *s)
{
	int wet;

	if (s->buf_type == BATCH_BUFFEW_2ND_WEVEW) {
		s->buf_type = BATCH_BUFFEW_INSTWUCTION;
		wet = ip_gma_set(s, s->wet_ip_gma_bb);
		s->buf_addw_type = s->saved_buf_addw_type;
	} ewse if (s->buf_type == WING_BUFFEW_CTX) {
		wet = ip_gma_set(s, s->wing_taiw);
	} ewse {
		s->buf_type = WING_BUFFEW_INSTWUCTION;
		s->buf_addw_type = GTT_BUFFEW;
		if (s->wet_ip_gma_wing >= s->wing_stawt + s->wing_size)
			s->wet_ip_gma_wing -= s->wing_size;
		wet = ip_gma_set(s, s->wet_ip_gma_wing);
	}
	wetuwn wet;
}

stwuct mi_dispway_fwip_command_info {
	int pipe;
	int pwane;
	int event;
	i915_weg_t stwide_weg;
	i915_weg_t ctww_weg;
	i915_weg_t suwf_weg;
	u64 stwide_vaw;
	u64 tiwe_vaw;
	u64 suwf_vaw;
	boow async_fwip;
};

stwuct pwane_code_mapping {
	int pipe;
	int pwane;
	int event;
};

static int gen8_decode_mi_dispway_fwip(stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	stwuct dwm_i915_pwivate *dev_pwiv = s->engine->i915;
	stwuct pwane_code_mapping gen8_pwane_code[] = {
		[0] = {PIPE_A, PWANE_A, PWIMAWY_A_FWIP_DONE},
		[1] = {PIPE_B, PWANE_A, PWIMAWY_B_FWIP_DONE},
		[2] = {PIPE_A, PWANE_B, SPWITE_A_FWIP_DONE},
		[3] = {PIPE_B, PWANE_B, SPWITE_B_FWIP_DONE},
		[4] = {PIPE_C, PWANE_A, PWIMAWY_C_FWIP_DONE},
		[5] = {PIPE_C, PWANE_B, SPWITE_C_FWIP_DONE},
	};
	u32 dwowd0, dwowd1, dwowd2;
	u32 v;

	dwowd0 = cmd_vaw(s, 0);
	dwowd1 = cmd_vaw(s, 1);
	dwowd2 = cmd_vaw(s, 2);

	v = (dwowd0 & GENMASK(21, 19)) >> 19;
	if (dwm_WAWN_ON(&dev_pwiv->dwm, v >= AWWAY_SIZE(gen8_pwane_code)))
		wetuwn -EBADWQC;

	info->pipe = gen8_pwane_code[v].pipe;
	info->pwane = gen8_pwane_code[v].pwane;
	info->event = gen8_pwane_code[v].event;
	info->stwide_vaw = (dwowd1 & GENMASK(15, 6)) >> 6;
	info->tiwe_vaw = (dwowd1 & 0x1);
	info->suwf_vaw = (dwowd2 & GENMASK(31, 12)) >> 12;
	info->async_fwip = ((dwowd2 & GENMASK(1, 0)) == 0x1);

	if (info->pwane == PWANE_A) {
		info->ctww_weg = DSPCNTW(info->pipe);
		info->stwide_weg = DSPSTWIDE(info->pipe);
		info->suwf_weg = DSPSUWF(info->pipe);
	} ewse if (info->pwane == PWANE_B) {
		info->ctww_weg = SPWCTW(info->pipe);
		info->stwide_weg = SPWSTWIDE(info->pipe);
		info->suwf_weg = SPWSUWF(info->pipe);
	} ewse {
		dwm_WAWN_ON(&dev_pwiv->dwm, 1);
		wetuwn -EBADWQC;
	}
	wetuwn 0;
}

static int skw_decode_mi_dispway_fwip(stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	stwuct dwm_i915_pwivate *dev_pwiv = s->engine->i915;
	stwuct intew_vgpu *vgpu = s->vgpu;
	u32 dwowd0 = cmd_vaw(s, 0);
	u32 dwowd1 = cmd_vaw(s, 1);
	u32 dwowd2 = cmd_vaw(s, 2);
	u32 pwane = (dwowd0 & GENMASK(12, 8)) >> 8;

	info->pwane = PWIMAWY_PWANE;

	switch (pwane) {
	case MI_DISPWAY_FWIP_SKW_PWANE_1_A:
		info->pipe = PIPE_A;
		info->event = PWIMAWY_A_FWIP_DONE;
		bweak;
	case MI_DISPWAY_FWIP_SKW_PWANE_1_B:
		info->pipe = PIPE_B;
		info->event = PWIMAWY_B_FWIP_DONE;
		bweak;
	case MI_DISPWAY_FWIP_SKW_PWANE_1_C:
		info->pipe = PIPE_C;
		info->event = PWIMAWY_C_FWIP_DONE;
		bweak;

	case MI_DISPWAY_FWIP_SKW_PWANE_2_A:
		info->pipe = PIPE_A;
		info->event = SPWITE_A_FWIP_DONE;
		info->pwane = SPWITE_PWANE;
		bweak;
	case MI_DISPWAY_FWIP_SKW_PWANE_2_B:
		info->pipe = PIPE_B;
		info->event = SPWITE_B_FWIP_DONE;
		info->pwane = SPWITE_PWANE;
		bweak;
	case MI_DISPWAY_FWIP_SKW_PWANE_2_C:
		info->pipe = PIPE_C;
		info->event = SPWITE_C_FWIP_DONE;
		info->pwane = SPWITE_PWANE;
		bweak;

	defauwt:
		gvt_vgpu_eww("unknown pwane code %d\n", pwane);
		wetuwn -EBADWQC;
	}

	info->stwide_vaw = (dwowd1 & GENMASK(15, 6)) >> 6;
	info->tiwe_vaw = (dwowd1 & GENMASK(2, 0));
	info->suwf_vaw = (dwowd2 & GENMASK(31, 12)) >> 12;
	info->async_fwip = ((dwowd2 & GENMASK(1, 0)) == 0x1);

	info->ctww_weg = DSPCNTW(info->pipe);
	info->stwide_weg = DSPSTWIDE(info->pipe);
	info->suwf_weg = DSPSUWF(info->pipe);

	wetuwn 0;
}

static int gen8_check_mi_dispway_fwip(stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	u32 stwide, tiwe;

	if (!info->async_fwip)
		wetuwn 0;

	if (GWAPHICS_VEW(s->engine->i915) >= 9) {
		stwide = vgpu_vweg_t(s->vgpu, info->stwide_weg) & GENMASK(9, 0);
		tiwe = (vgpu_vweg_t(s->vgpu, info->ctww_weg) &
				GENMASK(12, 10)) >> 10;
	} ewse {
		stwide = (vgpu_vweg_t(s->vgpu, info->stwide_weg) &
				GENMASK(15, 6)) >> 6;
		tiwe = (vgpu_vweg_t(s->vgpu, info->ctww_weg) & (1 << 10)) >> 10;
	}

	if (stwide != info->stwide_vaw)
		gvt_dbg_cmd("cannot change stwide duwing async fwip\n");

	if (tiwe != info->tiwe_vaw)
		gvt_dbg_cmd("cannot change tiwe duwing async fwip\n");

	wetuwn 0;
}

static int gen8_update_pwane_mmio_fwom_mi_dispway_fwip(
		stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	stwuct dwm_i915_pwivate *dev_pwiv = s->engine->i915;
	stwuct intew_vgpu *vgpu = s->vgpu;

	set_mask_bits(&vgpu_vweg_t(vgpu, info->suwf_weg), GENMASK(31, 12),
		      info->suwf_vaw << 12);
	if (GWAPHICS_VEW(dev_pwiv) >= 9) {
		set_mask_bits(&vgpu_vweg_t(vgpu, info->stwide_weg), GENMASK(9, 0),
			      info->stwide_vaw);
		set_mask_bits(&vgpu_vweg_t(vgpu, info->ctww_weg), GENMASK(12, 10),
			      info->tiwe_vaw << 10);
	} ewse {
		set_mask_bits(&vgpu_vweg_t(vgpu, info->stwide_weg), GENMASK(15, 6),
			      info->stwide_vaw << 6);
		set_mask_bits(&vgpu_vweg_t(vgpu, info->ctww_weg), GENMASK(10, 10),
			      info->tiwe_vaw << 10);
	}

	if (info->pwane == PWANE_PWIMAWY)
		vgpu_vweg_t(vgpu, PIPE_FWIPCOUNT_G4X(info->pipe))++;

	if (info->async_fwip)
		intew_vgpu_twiggew_viwtuaw_event(vgpu, info->event);
	ewse
		set_bit(info->event, vgpu->iwq.fwip_done_event[info->pipe]);

	wetuwn 0;
}

static int decode_mi_dispway_fwip(stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	if (IS_BWOADWEWW(s->engine->i915))
		wetuwn gen8_decode_mi_dispway_fwip(s, info);
	if (GWAPHICS_VEW(s->engine->i915) >= 9)
		wetuwn skw_decode_mi_dispway_fwip(s, info);

	wetuwn -ENODEV;
}

static int check_mi_dispway_fwip(stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	wetuwn gen8_check_mi_dispway_fwip(s, info);
}

static int update_pwane_mmio_fwom_mi_dispway_fwip(
		stwuct pawsew_exec_state *s,
		stwuct mi_dispway_fwip_command_info *info)
{
	wetuwn gen8_update_pwane_mmio_fwom_mi_dispway_fwip(s, info);
}

static int cmd_handwew_mi_dispway_fwip(stwuct pawsew_exec_state *s)
{
	stwuct mi_dispway_fwip_command_info info;
	stwuct intew_vgpu *vgpu = s->vgpu;
	int wet;
	int i;
	int wen = cmd_wength(s);
	u32 vawid_wen = CMD_WEN(1);

	/* Fwip Type == Steweo 3D Fwip */
	if (DWOWD_FIEWD(2, 1, 0) == 2)
		vawid_wen++;
	wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
			vawid_wen);
	if (wet)
		wetuwn wet;

	wet = decode_mi_dispway_fwip(s, &info);
	if (wet) {
		gvt_vgpu_eww("faiw to decode MI dispway fwip command\n");
		wetuwn wet;
	}

	wet = check_mi_dispway_fwip(s, &info);
	if (wet) {
		gvt_vgpu_eww("invawid MI dispway fwip command\n");
		wetuwn wet;
	}

	wet = update_pwane_mmio_fwom_mi_dispway_fwip(s, &info);
	if (wet) {
		gvt_vgpu_eww("faiw to update pwane mmio\n");
		wetuwn wet;
	}

	fow (i = 0; i < wen; i++)
		patch_vawue(s, cmd_ptw(s, i), MI_NOOP);
	wetuwn 0;
}

static boow is_wait_fow_fwip_pending(u32 cmd)
{
	wetuwn cmd & (MI_WAIT_FOW_PWANE_A_FWIP_PENDING |
			MI_WAIT_FOW_PWANE_B_FWIP_PENDING |
			MI_WAIT_FOW_PWANE_C_FWIP_PENDING |
			MI_WAIT_FOW_SPWITE_A_FWIP_PENDING |
			MI_WAIT_FOW_SPWITE_B_FWIP_PENDING |
			MI_WAIT_FOW_SPWITE_C_FWIP_PENDING);
}

static int cmd_handwew_mi_wait_fow_event(stwuct pawsew_exec_state *s)
{
	u32 cmd = cmd_vaw(s, 0);

	if (!is_wait_fow_fwip_pending(cmd))
		wetuwn 0;

	patch_vawue(s, cmd_ptw(s, 0), MI_NOOP);
	wetuwn 0;
}

static unsigned wong get_gma_bb_fwom_cmd(stwuct pawsew_exec_state *s, int index)
{
	unsigned wong addw;
	unsigned wong gma_high, gma_wow;
	stwuct intew_vgpu *vgpu = s->vgpu;
	int gmadw_bytes = vgpu->gvt->device_info.gmadw_bytes_in_cmd;

	if (WAWN_ON(gmadw_bytes != 4 && gmadw_bytes != 8)) {
		gvt_vgpu_eww("invawid gma bytes %d\n", gmadw_bytes);
		wetuwn INTEW_GVT_INVAWID_ADDW;
	}

	gma_wow = cmd_vaw(s, index) & BATCH_BUFFEW_ADDW_MASK;
	if (gmadw_bytes == 4) {
		addw = gma_wow;
	} ewse {
		gma_high = cmd_vaw(s, index + 1) & BATCH_BUFFEW_ADDW_HIGH_MASK;
		addw = (((unsigned wong)gma_high) << 32) | gma_wow;
	}
	wetuwn addw;
}

static inwine int cmd_addwess_audit(stwuct pawsew_exec_state *s,
		unsigned wong guest_gma, int op_size, boow index_mode)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	u32 max_suwface_size = vgpu->gvt->device_info.max_suwface_size;
	int i;
	int wet;

	if (op_size > max_suwface_size) {
		gvt_vgpu_eww("command addwess audit faiw name %s\n",
			s->info->name);
		wetuwn -EFAUWT;
	}

	if (index_mode)	{
		if (guest_gma >= I915_GTT_PAGE_SIZE) {
			wet = -EFAUWT;
			goto eww;
		}
	} ewse if (!intew_gvt_ggtt_vawidate_wange(vgpu, guest_gma, op_size)) {
		wet = -EFAUWT;
		goto eww;
	}

	wetuwn 0;

eww:
	gvt_vgpu_eww("cmd_pawsew: Mawicious %s detected, addw=0x%wx, wen=%d!\n",
			s->info->name, guest_gma, op_size);

	pw_eww("cmd dump: ");
	fow (i = 0; i < cmd_wength(s); i++) {
		if (!(i % 4))
			pw_eww("\n%08x ", cmd_vaw(s, i));
		ewse
			pw_eww("%08x ", cmd_vaw(s, i));
	}
	pw_eww("\nvgpu%d: apewtuwe 0x%wwx - 0x%wwx, hidden 0x%wwx - 0x%wwx\n",
			vgpu->id,
			vgpu_apewtuwe_gmadw_base(vgpu),
			vgpu_apewtuwe_gmadw_end(vgpu),
			vgpu_hidden_gmadw_base(vgpu),
			vgpu_hidden_gmadw_end(vgpu));
	wetuwn wet;
}

static int cmd_handwew_mi_stowe_data_imm(stwuct pawsew_exec_state *s)
{
	int gmadw_bytes = s->vgpu->gvt->device_info.gmadw_bytes_in_cmd;
	int op_size = (cmd_wength(s) - 3) * sizeof(u32);
	int cowe_id = (cmd_vaw(s, 2) & (1 << 0)) ? 1 : 0;
	unsigned wong gma, gma_wow, gma_high;
	u32 vawid_wen = CMD_WEN(2);
	int wet = 0;

	/* check ppggt */
	if (!(cmd_vaw(s, 0) & (1 << 22)))
		wetuwn 0;

	/* check if QWOWD */
	if (DWOWD_FIEWD(0, 21, 21))
		vawid_wen++;
	wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
			vawid_wen);
	if (wet)
		wetuwn wet;

	gma = cmd_vaw(s, 2) & GENMASK(31, 2);

	if (gmadw_bytes == 8) {
		gma_wow = cmd_vaw(s, 1) & GENMASK(31, 2);
		gma_high = cmd_vaw(s, 2) & GENMASK(15, 0);
		gma = (gma_high << 32) | gma_wow;
		cowe_id = (cmd_vaw(s, 1) & (1 << 0)) ? 1 : 0;
	}
	wet = cmd_addwess_audit(s, gma + op_size * cowe_id, op_size, fawse);
	wetuwn wet;
}

static inwine int unexpected_cmd(stwuct pawsew_exec_state *s)
{
	stwuct intew_vgpu *vgpu = s->vgpu;

	gvt_vgpu_eww("Unexpected %s in command buffew!\n", s->info->name);

	wetuwn -EBADWQC;
}

static int cmd_handwew_mi_semaphowe_wait(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_wepowt_pewf_count(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_op_2e(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_op_2f(stwuct pawsew_exec_state *s)
{
	int gmadw_bytes = s->vgpu->gvt->device_info.gmadw_bytes_in_cmd;
	int op_size = (1 << ((cmd_vaw(s, 0) & GENMASK(20, 19)) >> 19)) *
			sizeof(u32);
	unsigned wong gma, gma_high;
	u32 vawid_wen = CMD_WEN(1);
	int wet = 0;

	if (!(cmd_vaw(s, 0) & (1 << 22)))
		wetuwn wet;

	/* check inwine data */
	if (cmd_vaw(s, 0) & BIT(18))
		vawid_wen = CMD_WEN(9);
	wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
			vawid_wen);
	if (wet)
		wetuwn wet;

	gma = cmd_vaw(s, 1) & GENMASK(31, 2);
	if (gmadw_bytes == 8) {
		gma_high = cmd_vaw(s, 2) & GENMASK(15, 0);
		gma = (gma_high << 32) | gma;
	}
	wet = cmd_addwess_audit(s, gma, op_size, fawse);
	wetuwn wet;
}

static int cmd_handwew_mi_stowe_data_index(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_cwfwush(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_conditionaw_batch_buffew_end(
		stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_update_gtt(stwuct pawsew_exec_state *s)
{
	wetuwn unexpected_cmd(s);
}

static int cmd_handwew_mi_fwush_dw(stwuct pawsew_exec_state *s)
{
	int gmadw_bytes = s->vgpu->gvt->device_info.gmadw_bytes_in_cmd;
	unsigned wong gma;
	boow index_mode = fawse;
	int wet = 0;
	u32 hws_pga, vaw;
	u32 vawid_wen = CMD_WEN(2);

	wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
			vawid_wen);
	if (wet) {
		/* Check again fow Qwowd */
		wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
			++vawid_wen);
		wetuwn wet;
	}

	/* Check post-sync and ppgtt bit */
	if (((cmd_vaw(s, 0) >> 14) & 0x3) && (cmd_vaw(s, 1) & (1 << 2))) {
		gma = cmd_vaw(s, 1) & GENMASK(31, 3);
		if (gmadw_bytes == 8)
			gma |= (cmd_vaw(s, 2) & GENMASK(15, 0)) << 32;
		/* Stowe Data Index */
		if (cmd_vaw(s, 0) & (1 << 21))
			index_mode = twue;
		wet = cmd_addwess_audit(s, gma, sizeof(u64), index_mode);
		if (wet)
			wetuwn wet;
		if (index_mode) {
			hws_pga = s->vgpu->hws_pga[s->engine->id];
			gma = hws_pga + gma;
			patch_vawue(s, cmd_ptw(s, 1), gma);
			vaw = cmd_vaw(s, 0) & (~(1 << 21));
			patch_vawue(s, cmd_ptw(s, 0), vaw);
		}
	}
	/* Check notify bit */
	if ((cmd_vaw(s, 0) & (1 << 8)))
		set_bit(cmd_intewwupt_events[s->engine->id].mi_fwush_dw,
			s->wowkwoad->pending_events);
	wetuwn wet;
}

static void addw_type_update_snb(stwuct pawsew_exec_state *s)
{
	if ((s->buf_type == WING_BUFFEW_INSTWUCTION) &&
			(BATCH_BUFFEW_ADW_SPACE_BIT(cmd_vaw(s, 0)) == 1)) {
		s->buf_addw_type = PPGTT_BUFFEW;
	}
}


static int copy_gma_to_hva(stwuct intew_vgpu *vgpu, stwuct intew_vgpu_mm *mm,
		unsigned wong gma, unsigned wong end_gma, void *va)
{
	unsigned wong copy_wen, offset;
	unsigned wong wen = 0;
	unsigned wong gpa;

	whiwe (gma != end_gma) {
		gpa = intew_vgpu_gma_to_gpa(mm, gma);
		if (gpa == INTEW_GVT_INVAWID_ADDW) {
			gvt_vgpu_eww("invawid gma addwess: %wx\n", gma);
			wetuwn -EFAUWT;
		}

		offset = gma & (I915_GTT_PAGE_SIZE - 1);

		copy_wen = (end_gma - gma) >= (I915_GTT_PAGE_SIZE - offset) ?
			I915_GTT_PAGE_SIZE - offset : end_gma - gma;

		intew_gvt_wead_gpa(vgpu, gpa, va + wen, copy_wen);

		wen += copy_wen;
		gma += copy_wen;
	}
	wetuwn wen;
}


/*
 * Check whethew a batch buffew needs to be scanned. Cuwwentwy
 * the onwy cwitewia is based on pwiviwege.
 */
static int batch_buffew_needs_scan(stwuct pawsew_exec_state *s)
{
	/* Decide pwiviwege based on addwess space */
	if (cmd_vaw(s, 0) & BIT(8) &&
	    !(s->vgpu->scan_nonpwivbb & s->engine->mask))
		wetuwn 0;

	wetuwn 1;
}

static const chaw *wepw_addw_type(unsigned int type)
{
	wetuwn type == PPGTT_BUFFEW ? "ppgtt" : "ggtt";
}

static int find_bb_size(stwuct pawsew_exec_state *s,
			unsigned wong *bb_size,
			unsigned wong *bb_end_cmd_offset)
{
	unsigned wong gma = 0;
	const stwuct cmd_info *info;
	u32 cmd_wen = 0;
	boow bb_end = fawse;
	stwuct intew_vgpu *vgpu = s->vgpu;
	u32 cmd;
	stwuct intew_vgpu_mm *mm = (s->buf_addw_type == GTT_BUFFEW) ?
		s->vgpu->gtt.ggtt_mm : s->wowkwoad->shadow_mm;

	*bb_size = 0;
	*bb_end_cmd_offset = 0;

	/* get the stawt gm addwess of the batch buffew */
	gma = get_gma_bb_fwom_cmd(s, 1);
	if (gma == INTEW_GVT_INVAWID_ADDW)
		wetuwn -EFAUWT;

	cmd = cmd_vaw(s, 0);
	info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
	if (info == NUWW) {
		gvt_vgpu_eww("unknown cmd 0x%x, opcode=0x%x, addw_type=%s, wing %s, wowkwoad=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     wepw_addw_type(s->buf_addw_type),
			     s->engine->name, s->wowkwoad);
		wetuwn -EBADWQC;
	}
	do {
		if (copy_gma_to_hva(s->vgpu, mm,
				    gma, gma + 4, &cmd) < 0)
			wetuwn -EFAUWT;
		info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
		if (info == NUWW) {
			gvt_vgpu_eww("unknown cmd 0x%x, opcode=0x%x, addw_type=%s, wing %s, wowkwoad=%p\n",
				     cmd, get_opcode(cmd, s->engine),
				     wepw_addw_type(s->buf_addw_type),
				     s->engine->name, s->wowkwoad);
			wetuwn -EBADWQC;
		}

		if (info->opcode == OP_MI_BATCH_BUFFEW_END) {
			bb_end = twue;
		} ewse if (info->opcode == OP_MI_BATCH_BUFFEW_STAWT) {
			if (BATCH_BUFFEW_2ND_WEVEW_BIT(cmd) == 0)
				/* chained batch buffew */
				bb_end = twue;
		}

		if (bb_end)
			*bb_end_cmd_offset = *bb_size;

		cmd_wen = get_cmd_wength(info, cmd) << 2;
		*bb_size += cmd_wen;
		gma += cmd_wen;
	} whiwe (!bb_end);

	wetuwn 0;
}

static int audit_bb_end(stwuct pawsew_exec_state *s, void *va)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	u32 cmd = *(u32 *)va;
	const stwuct cmd_info *info;

	info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);
	if (info == NUWW) {
		gvt_vgpu_eww("unknown cmd 0x%x, opcode=0x%x, addw_type=%s, wing %s, wowkwoad=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     wepw_addw_type(s->buf_addw_type),
			     s->engine->name, s->wowkwoad);
		wetuwn -EBADWQC;
	}

	if ((info->opcode == OP_MI_BATCH_BUFFEW_END) ||
	    ((info->opcode == OP_MI_BATCH_BUFFEW_STAWT) &&
	     (BATCH_BUFFEW_2ND_WEVEW_BIT(cmd) == 0)))
		wetuwn 0;

	wetuwn -EBADWQC;
}

static int pewfowm_bb_shadow(stwuct pawsew_exec_state *s)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	stwuct intew_vgpu_shadow_bb *bb;
	unsigned wong gma = 0;
	unsigned wong bb_size;
	unsigned wong bb_end_cmd_offset;
	int wet = 0;
	stwuct intew_vgpu_mm *mm = (s->buf_addw_type == GTT_BUFFEW) ?
		s->vgpu->gtt.ggtt_mm : s->wowkwoad->shadow_mm;
	unsigned wong stawt_offset = 0;

	/* get the stawt gm addwess of the batch buffew */
	gma = get_gma_bb_fwom_cmd(s, 1);
	if (gma == INTEW_GVT_INVAWID_ADDW)
		wetuwn -EFAUWT;

	wet = find_bb_size(s, &bb_size, &bb_end_cmd_offset);
	if (wet)
		wetuwn wet;

	bb = kzawwoc(sizeof(*bb), GFP_KEWNEW);
	if (!bb)
		wetuwn -ENOMEM;

	bb->ppgtt = (s->buf_addw_type == GTT_BUFFEW) ? fawse : twue;

	/* the stawt_offset stowes the batch buffew's stawt gma's
	 * offset wewative to page boundawy. so fow non-pwiviweged batch
	 * buffew, the shadowed gem object howds exactwy the same page
	 * wayout as owiginaw gem object. This is fow the convience of
	 * wepwacing the whowe non-pwiviwged batch buffew page to this
	 * shadowed one in PPGTT at the same gma addwess. (this wepwacing
	 * action is not impwemented yet now, but may be necessawy in
	 * futuwe).
	 * fow pwiweged batch buffew, we just change stawt gma addwess to
	 * that of shadowed page.
	 */
	if (bb->ppgtt)
		stawt_offset = gma & ~I915_GTT_PAGE_MASK;

	bb->obj = i915_gem_object_cweate_shmem(s->engine->i915,
					       wound_up(bb_size + stawt_offset,
							PAGE_SIZE));
	if (IS_EWW(bb->obj)) {
		wet = PTW_EWW(bb->obj);
		goto eww_fwee_bb;
	}

	bb->va = i915_gem_object_pin_map(bb->obj, I915_MAP_WB);
	if (IS_EWW(bb->va)) {
		wet = PTW_EWW(bb->va);
		goto eww_fwee_obj;
	}

	wet = copy_gma_to_hva(s->vgpu, mm,
			      gma, gma + bb_size,
			      bb->va + stawt_offset);
	if (wet < 0) {
		gvt_vgpu_eww("faiw to copy guest wing buffew\n");
		wet = -EFAUWT;
		goto eww_unmap;
	}

	wet = audit_bb_end(s, bb->va + stawt_offset + bb_end_cmd_offset);
	if (wet)
		goto eww_unmap;

	i915_gem_object_unwock(bb->obj);
	INIT_WIST_HEAD(&bb->wist);
	wist_add(&bb->wist, &s->wowkwoad->shadow_bb);

	bb->bb_stawt_cmd_va = s->ip_va;

	if ((s->buf_type == BATCH_BUFFEW_INSTWUCTION) && (!s->is_ctx_wa))
		bb->bb_offset = s->ip_va - s->wb_va;
	ewse
		bb->bb_offset = 0;

	/*
	 * ip_va saves the viwtuaw addwess of the shadow batch buffew, whiwe
	 * ip_gma saves the gwaphics addwess of the owiginaw batch buffew.
	 * As the shadow batch buffew is just a copy fwom the owiginiaw one,
	 * it shouwd be wight to use shadow batch buffew'va and owiginaw batch
	 * buffew's gma in paiw. Aftew aww, we don't want to pin the shadow
	 * buffew hewe (too eawwy).
	 */
	s->ip_va = bb->va + stawt_offset;
	s->ip_gma = gma;
	wetuwn 0;
eww_unmap:
	i915_gem_object_unpin_map(bb->obj);
eww_fwee_obj:
	i915_gem_object_put(bb->obj);
eww_fwee_bb:
	kfwee(bb);
	wetuwn wet;
}

static int cmd_handwew_mi_batch_buffew_stawt(stwuct pawsew_exec_state *s)
{
	boow second_wevew;
	int wet = 0;
	stwuct intew_vgpu *vgpu = s->vgpu;

	if (s->buf_type == BATCH_BUFFEW_2ND_WEVEW) {
		gvt_vgpu_eww("Found MI_BATCH_BUFFEW_STAWT in 2nd wevew BB\n");
		wetuwn -EFAUWT;
	}

	second_wevew = BATCH_BUFFEW_2ND_WEVEW_BIT(cmd_vaw(s, 0)) == 1;
	if (second_wevew && (s->buf_type != BATCH_BUFFEW_INSTWUCTION)) {
		gvt_vgpu_eww("Jumping to 2nd wevew BB fwom WB is not awwowed\n");
		wetuwn -EFAUWT;
	}

	s->saved_buf_addw_type = s->buf_addw_type;
	addw_type_update_snb(s);
	if (s->buf_type == WING_BUFFEW_INSTWUCTION) {
		s->wet_ip_gma_wing = s->ip_gma + cmd_wength(s) * sizeof(u32);
		s->buf_type = BATCH_BUFFEW_INSTWUCTION;
	} ewse if (second_wevew) {
		s->buf_type = BATCH_BUFFEW_2ND_WEVEW;
		s->wet_ip_gma_bb = s->ip_gma + cmd_wength(s) * sizeof(u32);
		s->wet_bb_va = s->ip_va + cmd_wength(s) * sizeof(u32);
	}

	if (batch_buffew_needs_scan(s)) {
		wet = pewfowm_bb_shadow(s);
		if (wet < 0)
			gvt_vgpu_eww("invawid shadow batch buffew\n");
	} ewse {
		/* emuwate a batch buffew end to do wetuwn wight */
		wet = cmd_handwew_mi_batch_buffew_end(s);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn wet;
}

static int mi_noop_index;

static const stwuct cmd_info cmd_info[] = {
	{"MI_NOOP", OP_MI_NOOP, F_WEN_CONST, W_AWW, D_AWW, 0, 1, NUWW},

	{"MI_SET_PWEDICATE", OP_MI_SET_PWEDICATE, F_WEN_CONST, W_AWW, D_AWW,
		0, 1, NUWW},

	{"MI_USEW_INTEWWUPT", OP_MI_USEW_INTEWWUPT, F_WEN_CONST, W_AWW, D_AWW,
		0, 1, cmd_handwew_mi_usew_intewwupt},

	{"MI_WAIT_FOW_EVENT", OP_MI_WAIT_FOW_EVENT, F_WEN_CONST, W_WCS | W_BCS,
		D_AWW, 0, 1, cmd_handwew_mi_wait_fow_event},

	{"MI_FWUSH", OP_MI_FWUSH, F_WEN_CONST, W_AWW, D_AWW, 0, 1, NUWW},

	{"MI_AWB_CHECK", OP_MI_AWB_CHECK, F_WEN_CONST, W_AWW, D_AWW, 0, 1,
		NUWW},

	{"MI_WS_CONTWOW", OP_MI_WS_CONTWOW, F_WEN_CONST, W_WCS, D_AWW, 0, 1,
		NUWW},

	{"MI_WEPOWT_HEAD", OP_MI_WEPOWT_HEAD, F_WEN_CONST, W_AWW, D_AWW, 0, 1,
		NUWW},

	{"MI_AWB_ON_OFF", OP_MI_AWB_ON_OFF, F_WEN_CONST, W_AWW, D_AWW, 0, 1,
		NUWW},

	{"MI_UWB_ATOMIC_AWWOC", OP_MI_UWB_ATOMIC_AWWOC, F_WEN_CONST, W_WCS,
		D_AWW, 0, 1, NUWW},

	{"MI_BATCH_BUFFEW_END", OP_MI_BATCH_BUFFEW_END,
		F_IP_ADVANCE_CUSTOM | F_WEN_CONST, W_AWW, D_AWW, 0, 1,
		cmd_handwew_mi_batch_buffew_end},

	{"MI_SUSPEND_FWUSH", OP_MI_SUSPEND_FWUSH, F_WEN_CONST, W_AWW, D_AWW,
		0, 1, NUWW},

	{"MI_PWEDICATE", OP_MI_PWEDICATE, F_WEN_CONST, W_WCS, D_AWW, 0, 1,
		NUWW},

	{"MI_TOPOWOGY_FIWTEW", OP_MI_TOPOWOGY_FIWTEW, F_WEN_CONST, W_AWW,
		D_AWW, 0, 1, NUWW},

	{"MI_SET_APPID", OP_MI_SET_APPID, F_WEN_CONST, W_AWW, D_AWW, 0, 1,
		NUWW},

	{"MI_WS_CONTEXT", OP_MI_WS_CONTEXT, F_WEN_CONST, W_WCS, D_AWW, 0, 1,
		NUWW},

	{"MI_DISPWAY_FWIP", OP_MI_DISPWAY_FWIP, F_WEN_VAW,
		W_WCS | W_BCS, D_AWW, 0, 8, cmd_handwew_mi_dispway_fwip},

	{"MI_SEMAPHOWE_MBOX", OP_MI_SEMAPHOWE_MBOX, F_WEN_VAW | F_WEN_VAW_FIXED,
		W_AWW, D_AWW, 0, 8, NUWW, CMD_WEN(1)},

	{"MI_MATH", OP_MI_MATH, F_WEN_VAW, W_AWW, D_AWW, 0, 8, NUWW},

	{"MI_UWB_CWEAW", OP_MI_UWB_CWEAW, F_WEN_VAW | F_WEN_VAW_FIXED, W_WCS,
		D_AWW, 0, 8, NUWW, CMD_WEN(0)},

	{"MI_SEMAPHOWE_SIGNAW", OP_MI_SEMAPHOWE_SIGNAW,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_BDW_PWUS, 0, 8,
		NUWW, CMD_WEN(0)},

	{"MI_SEMAPHOWE_WAIT", OP_MI_SEMAPHOWE_WAIT,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_BDW_PWUS, ADDW_FIX_1(2),
		8, cmd_handwew_mi_semaphowe_wait, CMD_WEN(2)},

	{"MI_STOWE_DATA_IMM", OP_MI_STOWE_DATA_IMM, F_WEN_VAW, W_AWW, D_BDW_PWUS,
		ADDW_FIX_1(1), 10, cmd_handwew_mi_stowe_data_imm},

	{"MI_STOWE_DATA_INDEX", OP_MI_STOWE_DATA_INDEX, F_WEN_VAW, W_AWW, D_AWW,
		0, 8, cmd_handwew_mi_stowe_data_index},

	{"MI_WOAD_WEGISTEW_IMM", OP_MI_WOAD_WEGISTEW_IMM, F_WEN_VAW, W_AWW,
		D_AWW, 0, 8, cmd_handwew_wwi},

	{"MI_UPDATE_GTT", OP_MI_UPDATE_GTT, F_WEN_VAW, W_AWW, D_BDW_PWUS, 0, 10,
		cmd_handwew_mi_update_gtt},

	{"MI_STOWE_WEGISTEW_MEM", OP_MI_STOWE_WEGISTEW_MEM,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_AWW, ADDW_FIX_1(2), 8,
		cmd_handwew_swm, CMD_WEN(2)},

	{"MI_FWUSH_DW", OP_MI_FWUSH_DW, F_WEN_VAW, W_AWW, D_AWW, 0, 6,
		cmd_handwew_mi_fwush_dw},

	{"MI_CWFWUSH", OP_MI_CWFWUSH, F_WEN_VAW, W_AWW, D_AWW, ADDW_FIX_1(1),
		10, cmd_handwew_mi_cwfwush},

	{"MI_WEPOWT_PEWF_COUNT", OP_MI_WEPOWT_PEWF_COUNT,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_AWW, ADDW_FIX_1(1), 6,
		cmd_handwew_mi_wepowt_pewf_count, CMD_WEN(2)},

	{"MI_WOAD_WEGISTEW_MEM", OP_MI_WOAD_WEGISTEW_MEM,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_AWW, ADDW_FIX_1(2), 8,
		cmd_handwew_wwm, CMD_WEN(2)},

	{"MI_WOAD_WEGISTEW_WEG", OP_MI_WOAD_WEGISTEW_WEG,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_AWW, 0, 8,
		cmd_handwew_www, CMD_WEN(1)},

	{"MI_WS_STOWE_DATA_IMM", OP_MI_WS_STOWE_DATA_IMM,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_WCS, D_AWW, 0,
		8, NUWW, CMD_WEN(2)},

	{"MI_WOAD_UWB_MEM", OP_MI_WOAD_UWB_MEM, F_WEN_VAW | F_WEN_VAW_FIXED,
		W_WCS, D_AWW, ADDW_FIX_1(2), 8, NUWW, CMD_WEN(2)},

	{"MI_STOWE_UWM_MEM", OP_MI_STOWE_UWM_MEM, F_WEN_VAW, W_WCS, D_AWW,
		ADDW_FIX_1(2), 8, NUWW},

	{"MI_OP_2E", OP_MI_2E, F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_BDW_PWUS,
		ADDW_FIX_2(1, 2), 8, cmd_handwew_mi_op_2e, CMD_WEN(3)},

	{"MI_OP_2F", OP_MI_2F, F_WEN_VAW, W_AWW, D_BDW_PWUS, ADDW_FIX_1(1),
		8, cmd_handwew_mi_op_2f},

	{"MI_BATCH_BUFFEW_STAWT", OP_MI_BATCH_BUFFEW_STAWT,
		F_IP_ADVANCE_CUSTOM, W_AWW, D_AWW, 0, 8,
		cmd_handwew_mi_batch_buffew_stawt},

	{"MI_CONDITIONAW_BATCH_BUFFEW_END", OP_MI_CONDITIONAW_BATCH_BUFFEW_END,
		F_WEN_VAW | F_WEN_VAW_FIXED, W_AWW, D_AWW, ADDW_FIX_1(2), 8,
		cmd_handwew_mi_conditionaw_batch_buffew_end, CMD_WEN(2)},

	{"MI_WOAD_SCAN_WINES_INCW", OP_MI_WOAD_SCAN_WINES_INCW, F_WEN_CONST,
		W_WCS | W_BCS, D_AWW, 0, 2, NUWW},

	{"XY_SETUP_BWT", OP_XY_SETUP_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_2(4, 7), 8, NUWW},

	{"XY_SETUP_CWIP_BWT", OP_XY_SETUP_CWIP_BWT, F_WEN_VAW, W_BCS, D_AWW,
		0, 8, NUWW},

	{"XY_SETUP_MONO_PATTEWN_SW_BWT", OP_XY_SETUP_MONO_PATTEWN_SW_BWT,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_1(4), 8, NUWW},

	{"XY_PIXEW_BWT", OP_XY_PIXEW_BWT, F_WEN_VAW, W_BCS, D_AWW, 0, 8, NUWW},

	{"XY_SCANWINES_BWT", OP_XY_SCANWINES_BWT, F_WEN_VAW, W_BCS, D_AWW,
		0, 8, NUWW},

	{"XY_TEXT_BWT", OP_XY_TEXT_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_1(3), 8, NUWW},

	{"XY_TEXT_IMMEDIATE_BWT", OP_XY_TEXT_IMMEDIATE_BWT, F_WEN_VAW, W_BCS,
		D_AWW, 0, 8, NUWW},

	{"XY_COWOW_BWT", OP_XY_COWOW_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_1(4), 8, NUWW},

	{"XY_PAT_BWT", OP_XY_PAT_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_2(4, 5), 8, NUWW},

	{"XY_MONO_PAT_BWT", OP_XY_MONO_PAT_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_1(4), 8, NUWW},

	{"XY_SWC_COPY_BWT", OP_XY_SWC_COPY_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_2(4, 7), 8, NUWW},

	{"XY_MONO_SWC_COPY_BWT", OP_XY_MONO_SWC_COPY_BWT, F_WEN_VAW, W_BCS,
		D_AWW, ADDW_FIX_2(4, 5), 8, NUWW},

	{"XY_FUWW_BWT", OP_XY_FUWW_BWT, F_WEN_VAW, W_BCS, D_AWW, 0, 8, NUWW},

	{"XY_FUWW_MONO_SWC_BWT", OP_XY_FUWW_MONO_SWC_BWT, F_WEN_VAW, W_BCS,
		D_AWW, ADDW_FIX_3(4, 5, 8), 8, NUWW},

	{"XY_FUWW_MONO_PATTEWN_BWT", OP_XY_FUWW_MONO_PATTEWN_BWT, F_WEN_VAW,
		W_BCS, D_AWW, ADDW_FIX_2(4, 7), 8, NUWW},

	{"XY_FUWW_MONO_PATTEWN_MONO_SWC_BWT",
		OP_XY_FUWW_MONO_PATTEWN_MONO_SWC_BWT,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_2(4, 5), 8, NUWW},

	{"XY_MONO_PAT_FIXED_BWT", OP_XY_MONO_PAT_FIXED_BWT, F_WEN_VAW, W_BCS,
		D_AWW, ADDW_FIX_1(4), 8, NUWW},

	{"XY_MONO_SWC_COPY_IMMEDIATE_BWT", OP_XY_MONO_SWC_COPY_IMMEDIATE_BWT,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_1(4), 8, NUWW},

	{"XY_PAT_BWT_IMMEDIATE", OP_XY_PAT_BWT_IMMEDIATE, F_WEN_VAW, W_BCS,
		D_AWW, ADDW_FIX_1(4), 8, NUWW},

	{"XY_SWC_COPY_CHWOMA_BWT", OP_XY_SWC_COPY_CHWOMA_BWT, F_WEN_VAW, W_BCS,
		D_AWW, ADDW_FIX_2(4, 7), 8, NUWW},

	{"XY_FUWW_IMMEDIATE_PATTEWN_BWT", OP_XY_FUWW_IMMEDIATE_PATTEWN_BWT,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_2(4, 7), 8, NUWW},

	{"XY_FUWW_MONO_SWC_IMMEDIATE_PATTEWN_BWT",
		OP_XY_FUWW_MONO_SWC_IMMEDIATE_PATTEWN_BWT,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_2(4, 5), 8, NUWW},

	{"XY_PAT_CHWOMA_BWT", OP_XY_PAT_CHWOMA_BWT, F_WEN_VAW, W_BCS, D_AWW,
		ADDW_FIX_2(4, 5), 8, NUWW},

	{"XY_PAT_CHWOMA_BWT_IMMEDIATE", OP_XY_PAT_CHWOMA_BWT_IMMEDIATE,
		F_WEN_VAW, W_BCS, D_AWW, ADDW_FIX_1(4), 8, NUWW},

	{"3DSTATE_VIEWPOWT_STATE_POINTEWS_SF_CWIP",
		OP_3DSTATE_VIEWPOWT_STATE_POINTEWS_SF_CWIP,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_VIEWPOWT_STATE_POINTEWS_CC",
		OP_3DSTATE_VIEWPOWT_STATE_POINTEWS_CC,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BWEND_STATE_POINTEWS",
		OP_3DSTATE_BWEND_STATE_POINTEWS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DEPTH_STENCIW_STATE_POINTEWS",
		OP_3DSTATE_DEPTH_STENCIW_STATE_POINTEWS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POINTEWS_VS",
		OP_3DSTATE_BINDING_TABWE_POINTEWS_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POINTEWS_HS",
		OP_3DSTATE_BINDING_TABWE_POINTEWS_HS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POINTEWS_DS",
		OP_3DSTATE_BINDING_TABWE_POINTEWS_DS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POINTEWS_GS",
		OP_3DSTATE_BINDING_TABWE_POINTEWS_GS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POINTEWS_PS",
		OP_3DSTATE_BINDING_TABWE_POINTEWS_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_STATE_POINTEWS_VS",
		OP_3DSTATE_SAMPWEW_STATE_POINTEWS_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_STATE_POINTEWS_HS",
		OP_3DSTATE_SAMPWEW_STATE_POINTEWS_HS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_STATE_POINTEWS_DS",
		OP_3DSTATE_SAMPWEW_STATE_POINTEWS_DS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_STATE_POINTEWS_GS",
		OP_3DSTATE_SAMPWEW_STATE_POINTEWS_GS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_STATE_POINTEWS_PS",
		OP_3DSTATE_SAMPWEW_STATE_POINTEWS_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_UWB_VS", OP_3DSTATE_UWB_VS, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"3DSTATE_UWB_HS", OP_3DSTATE_UWB_HS, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"3DSTATE_UWB_DS", OP_3DSTATE_UWB_DS, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"3DSTATE_UWB_GS", OP_3DSTATE_UWB_GS, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"3DSTATE_GATHEW_CONSTANT_VS", OP_3DSTATE_GATHEW_CONSTANT_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_GATHEW_CONSTANT_GS", OP_3DSTATE_GATHEW_CONSTANT_GS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_GATHEW_CONSTANT_HS", OP_3DSTATE_GATHEW_CONSTANT_HS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_GATHEW_CONSTANT_DS", OP_3DSTATE_GATHEW_CONSTANT_DS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_GATHEW_CONSTANT_PS", OP_3DSTATE_GATHEW_CONSTANT_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_CONSTANTF_VS", OP_3DSTATE_DX9_CONSTANTF_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 11, NUWW},

	{"3DSTATE_DX9_CONSTANTF_PS", OP_3DSTATE_DX9_CONSTANTF_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 11, NUWW},

	{"3DSTATE_DX9_CONSTANTI_VS", OP_3DSTATE_DX9_CONSTANTI_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_CONSTANTI_PS", OP_3DSTATE_DX9_CONSTANTI_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_CONSTANTB_VS", OP_3DSTATE_DX9_CONSTANTB_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_CONSTANTB_PS", OP_3DSTATE_DX9_CONSTANTB_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_WOCAW_VAWID_VS", OP_3DSTATE_DX9_WOCAW_VAWID_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_WOCAW_VAWID_PS", OP_3DSTATE_DX9_WOCAW_VAWID_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_GENEWATE_ACTIVE_VS", OP_3DSTATE_DX9_GENEWATE_ACTIVE_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DX9_GENEWATE_ACTIVE_PS", OP_3DSTATE_DX9_GENEWATE_ACTIVE_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_BINDING_TABWE_EDIT_VS", OP_3DSTATE_BINDING_TABWE_EDIT_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 9, NUWW},

	{"3DSTATE_BINDING_TABWE_EDIT_GS", OP_3DSTATE_BINDING_TABWE_EDIT_GS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 9, NUWW},

	{"3DSTATE_BINDING_TABWE_EDIT_HS", OP_3DSTATE_BINDING_TABWE_EDIT_HS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 9, NUWW},

	{"3DSTATE_BINDING_TABWE_EDIT_DS", OP_3DSTATE_BINDING_TABWE_EDIT_DS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 9, NUWW},

	{"3DSTATE_BINDING_TABWE_EDIT_PS", OP_3DSTATE_BINDING_TABWE_EDIT_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 9, NUWW},

	{"3DSTATE_VF_INSTANCING", OP_3DSTATE_VF_INSTANCING, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_VF_SGVS", OP_3DSTATE_VF_SGVS, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0, 8,
		NUWW},

	{"3DSTATE_VF_TOPOWOGY", OP_3DSTATE_VF_TOPOWOGY, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_WM_CHWOMAKEY", OP_3DSTATE_WM_CHWOMAKEY, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_PS_BWEND", OP_3DSTATE_PS_BWEND, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0,
		8, NUWW},

	{"3DSTATE_WM_DEPTH_STENCIW", OP_3DSTATE_WM_DEPTH_STENCIW, F_WEN_VAW,
		W_WCS, D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_PS_EXTWA", OP_3DSTATE_PS_EXTWA, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0,
		8, NUWW},

	{"3DSTATE_WASTEW", OP_3DSTATE_WASTEW, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0, 8,
		NUWW},

	{"3DSTATE_SBE_SWIZ", OP_3DSTATE_SBE_SWIZ, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0, 8,
		NUWW},

	{"3DSTATE_WM_HZ_OP", OP_3DSTATE_WM_HZ_OP, F_WEN_VAW, W_WCS, D_BDW_PWUS, 0, 8,
		NUWW},

	{"3DSTATE_VEWTEX_BUFFEWS", OP_3DSTATE_VEWTEX_BUFFEWS, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_VEWTEX_EWEMENTS", OP_3DSTATE_VEWTEX_EWEMENTS, F_WEN_VAW,
		W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_INDEX_BUFFEW", OP_3DSTATE_INDEX_BUFFEW, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, ADDW_FIX_1(2), 8, NUWW},

	{"3DSTATE_VF_STATISTICS", OP_3DSTATE_VF_STATISTICS, F_WEN_CONST,
		W_WCS, D_AWW, 0, 1, NUWW},

	{"3DSTATE_VF", OP_3DSTATE_VF, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_CC_STATE_POINTEWS", OP_3DSTATE_CC_STATE_POINTEWS, F_WEN_VAW,
		W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SCISSOW_STATE_POINTEWS", OP_3DSTATE_SCISSOW_STATE_POINTEWS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_GS", OP_3DSTATE_GS, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_CWIP", OP_3DSTATE_CWIP, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_WM", OP_3DSTATE_WM, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_CONSTANT_GS", OP_3DSTATE_CONSTANT_GS, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_CONSTANT_PS", OP_3DSTATE_CONSTANT_PS, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_SAMPWE_MASK", OP_3DSTATE_SAMPWE_MASK, F_WEN_VAW, W_WCS,
		D_AWW, 0, 8, NUWW},

	{"3DSTATE_CONSTANT_HS", OP_3DSTATE_CONSTANT_HS, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_CONSTANT_DS", OP_3DSTATE_CONSTANT_DS, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_HS", OP_3DSTATE_HS, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_TE", OP_3DSTATE_TE, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DS", OP_3DSTATE_DS, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_STWEAMOUT", OP_3DSTATE_STWEAMOUT, F_WEN_VAW, W_WCS,
		D_AWW, 0, 8, NUWW},

	{"3DSTATE_SBE", OP_3DSTATE_SBE, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PS", OP_3DSTATE_PS, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_DWAWING_WECTANGWE", OP_3DSTATE_DWAWING_WECTANGWE, F_WEN_VAW,
		W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_PAWETTE_WOAD0", OP_3DSTATE_SAMPWEW_PAWETTE_WOAD0,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_CHWOMA_KEY", OP_3DSTATE_CHWOMA_KEY, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"3DSTATE_DEPTH_BUFFEW", OP_3DSTATE_DEPTH_BUFFEW, F_WEN_VAW, W_WCS,
		D_AWW, ADDW_FIX_1(2), 8, NUWW},

	{"3DSTATE_POWY_STIPPWE_OFFSET", OP_3DSTATE_POWY_STIPPWE_OFFSET,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_POWY_STIPPWE_PATTEWN", OP_3DSTATE_POWY_STIPPWE_PATTEWN,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_WINE_STIPPWE", OP_3DSTATE_WINE_STIPPWE, F_WEN_VAW, W_WCS,
		D_AWW, 0, 8, NUWW},

	{"3DSTATE_AA_WINE_PAWAMS", OP_3DSTATE_AA_WINE_PAWAMS, F_WEN_VAW, W_WCS,
		D_AWW, 0, 8, NUWW},

	{"3DSTATE_GS_SVB_INDEX", OP_3DSTATE_GS_SVB_INDEX, F_WEN_VAW, W_WCS,
		D_AWW, 0, 8, NUWW},

	{"3DSTATE_SAMPWEW_PAWETTE_WOAD1", OP_3DSTATE_SAMPWEW_PAWETTE_WOAD1,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_MUWTISAMPWE", OP_3DSTATE_MUWTISAMPWE_BDW, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"3DSTATE_STENCIW_BUFFEW", OP_3DSTATE_STENCIW_BUFFEW, F_WEN_VAW, W_WCS,
		D_AWW, ADDW_FIX_1(2), 8, NUWW},

	{"3DSTATE_HIEW_DEPTH_BUFFEW", OP_3DSTATE_HIEW_DEPTH_BUFFEW, F_WEN_VAW,
		W_WCS, D_AWW, ADDW_FIX_1(2), 8, NUWW},

	{"3DSTATE_CWEAW_PAWAMS", OP_3DSTATE_CWEAW_PAWAMS, F_WEN_VAW,
		W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PUSH_CONSTANT_AWWOC_VS", OP_3DSTATE_PUSH_CONSTANT_AWWOC_VS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PUSH_CONSTANT_AWWOC_HS", OP_3DSTATE_PUSH_CONSTANT_AWWOC_HS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PUSH_CONSTANT_AWWOC_DS", OP_3DSTATE_PUSH_CONSTANT_AWWOC_DS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PUSH_CONSTANT_AWWOC_GS", OP_3DSTATE_PUSH_CONSTANT_AWWOC_GS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_PUSH_CONSTANT_AWWOC_PS", OP_3DSTATE_PUSH_CONSTANT_AWWOC_PS,
		F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_MONOFIWTEW_SIZE", OP_3DSTATE_MONOFIWTEW_SIZE, F_WEN_VAW,
		W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SO_DECW_WIST", OP_3DSTATE_SO_DECW_WIST, F_WEN_VAW, W_WCS,
		D_AWW, 0, 9, NUWW},

	{"3DSTATE_SO_BUFFEW", OP_3DSTATE_SO_BUFFEW, F_WEN_VAW, W_WCS, D_BDW_PWUS,
		ADDW_FIX_2(2, 4), 8, NUWW},

	{"3DSTATE_BINDING_TABWE_POOW_AWWOC",
		OP_3DSTATE_BINDING_TABWE_POOW_AWWOC,
		F_WEN_VAW, W_WCS, D_BDW_PWUS, ADDW_FIX_1(1), 8, NUWW},

	{"3DSTATE_GATHEW_POOW_AWWOC", OP_3DSTATE_GATHEW_POOW_AWWOC,
		F_WEN_VAW, W_WCS, D_BDW_PWUS, ADDW_FIX_1(1), 8, NUWW},

	{"3DSTATE_DX9_CONSTANT_BUFFEW_POOW_AWWOC",
		OP_3DSTATE_DX9_CONSTANT_BUFFEW_POOW_AWWOC,
		F_WEN_VAW, W_WCS, D_BDW_PWUS, ADDW_FIX_1(1), 8, NUWW},

	{"3DSTATE_SAMPWE_PATTEWN", OP_3DSTATE_SAMPWE_PATTEWN, F_WEN_VAW, W_WCS,
		D_BDW_PWUS, 0, 8, NUWW},

	{"PIPE_CONTWOW", OP_PIPE_CONTWOW, F_WEN_VAW, W_WCS, D_AWW,
		ADDW_FIX_1(2), 8, cmd_handwew_pipe_contwow},

	{"3DPWIMITIVE", OP_3DPWIMITIVE, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"PIPEWINE_SEWECT", OP_PIPEWINE_SEWECT, F_WEN_CONST, W_WCS, D_AWW, 0,
		1, NUWW},

	{"STATE_PWEFETCH", OP_STATE_PWEFETCH, F_WEN_VAW, W_WCS, D_AWW,
		ADDW_FIX_1(1), 8, NUWW},

	{"STATE_SIP", OP_STATE_SIP, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"STATE_BASE_ADDWESS", OP_STATE_BASE_ADDWESS, F_WEN_VAW, W_WCS, D_BDW_PWUS,
		ADDW_FIX_5(1, 3, 4, 5, 6), 8, NUWW},

	{"OP_3D_MEDIA_0_1_4", OP_3D_MEDIA_0_1_4, F_WEN_VAW, W_WCS, D_AWW,
		ADDW_FIX_1(1), 8, NUWW},

	{"OP_SWTESS_BASE_ADDWESS", OP_SWTESS_BASE_ADDWESS,
		F_WEN_VAW, W_WCS, D_AWW, ADDW_FIX_2(1, 2), 3, NUWW},

	{"3DSTATE_VS", OP_3DSTATE_VS, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_SF", OP_3DSTATE_SF, F_WEN_VAW, W_WCS, D_AWW, 0, 8, NUWW},

	{"3DSTATE_CONSTANT_VS", OP_3DSTATE_CONSTANT_VS, F_WEN_VAW, W_WCS, D_BDW_PWUS,
		0, 8, NUWW},

	{"3DSTATE_COMPONENT_PACKING", OP_3DSTATE_COMPONENT_PACKING, F_WEN_VAW, W_WCS,
		D_SKW_PWUS, 0, 8, NUWW},

	{"MEDIA_INTEWFACE_DESCWIPTOW_WOAD", OP_MEDIA_INTEWFACE_DESCWIPTOW_WOAD,
		F_WEN_VAW, W_WCS, D_AWW, 0, 16, NUWW},

	{"MEDIA_GATEWAY_STATE", OP_MEDIA_GATEWAY_STATE, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"MEDIA_STATE_FWUSH", OP_MEDIA_STATE_FWUSH, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"MEDIA_POOW_STATE", OP_MEDIA_POOW_STATE, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"MEDIA_OBJECT", OP_MEDIA_OBJECT, F_WEN_VAW, W_WCS, D_AWW, 0, 16, NUWW},

	{"MEDIA_CUWBE_WOAD", OP_MEDIA_CUWBE_WOAD, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"MEDIA_OBJECT_PWT", OP_MEDIA_OBJECT_PWT, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"MEDIA_OBJECT_WAWKEW", OP_MEDIA_OBJECT_WAWKEW, F_WEN_VAW, W_WCS, D_AWW,
		0, 16, NUWW},

	{"GPGPU_WAWKEW", OP_GPGPU_WAWKEW, F_WEN_VAW, W_WCS, D_AWW,
		0, 8, NUWW},

	{"MEDIA_VFE_STATE", OP_MEDIA_VFE_STATE, F_WEN_VAW, W_WCS, D_AWW, 0, 16,
		NUWW},

	{"3DSTATE_VF_STATISTICS_GM45", OP_3DSTATE_VF_STATISTICS_GM45,
		F_WEN_CONST, W_AWW, D_AWW, 0, 1, NUWW},

	{"MFX_PIPE_MODE_SEWECT", OP_MFX_PIPE_MODE_SEWECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_SUWFACE_STATE", OP_MFX_SUWFACE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_PIPE_BUF_ADDW_STATE", OP_MFX_PIPE_BUF_ADDW_STATE, F_WEN_VAW,
		W_VCS, D_BDW_PWUS, 0, 12, NUWW},

	{"MFX_IND_OBJ_BASE_ADDW_STATE", OP_MFX_IND_OBJ_BASE_ADDW_STATE,
		F_WEN_VAW, W_VCS, D_BDW_PWUS, 0, 12, NUWW},

	{"MFX_BSP_BUF_BASE_ADDW_STATE", OP_MFX_BSP_BUF_BASE_ADDW_STATE,
		F_WEN_VAW, W_VCS, D_BDW_PWUS, ADDW_FIX_3(1, 3, 5), 12, NUWW},

	{"OP_2_0_0_5", OP_2_0_0_5, F_WEN_VAW, W_VCS, D_BDW_PWUS, 0, 12, NUWW},

	{"MFX_STATE_POINTEW", OP_MFX_STATE_POINTEW, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_QM_STATE", OP_MFX_QM_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_FQM_STATE", OP_MFX_FQM_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_PAK_INSEWT_OBJECT", OP_MFX_PAK_INSEWT_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_STITCH_OBJECT", OP_MFX_STITCH_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_IT_OBJECT", OP_MFD_IT_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_WAIT", OP_MFX_WAIT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 6, NUWW},

	{"MFX_AVC_IMG_STATE", OP_MFX_AVC_IMG_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_AVC_QM_STATE", OP_MFX_AVC_QM_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_AVC_DIWECTMODE_STATE", OP_MFX_AVC_DIWECTMODE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_AVC_SWICE_STATE", OP_MFX_AVC_SWICE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_AVC_WEF_IDX_STATE", OP_MFX_AVC_WEF_IDX_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_AVC_WEIGHTOFFSET_STATE", OP_MFX_AVC_WEIGHTOFFSET_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_AVC_PICID_STATE", OP_MFD_AVC_PICID_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},
	{"MFD_AVC_DPB_STATE", OP_MFD_AVC_DPB_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_AVC_BSD_OBJECT", OP_MFD_AVC_BSD_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_AVC_SWICEADDW", OP_MFD_AVC_SWICEADDW, F_WEN_VAW,
		W_VCS, D_AWW, ADDW_FIX_1(2), 12, NUWW},

	{"MFC_AVC_PAK_OBJECT", OP_MFC_AVC_PAK_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_VC1_PWED_PIPE_STATE", OP_MFX_VC1_PWED_PIPE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_VC1_DIWECTMODE_STATE", OP_MFX_VC1_DIWECTMODE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_VC1_SHOWT_PIC_STATE", OP_MFD_VC1_SHOWT_PIC_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_VC1_WONG_PIC_STATE", OP_MFD_VC1_WONG_PIC_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_VC1_BSD_OBJECT", OP_MFD_VC1_BSD_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFC_MPEG2_SWICEGWOUP_STATE", OP_MFC_MPEG2_SWICEGWOUP_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFC_MPEG2_PAK_OBJECT", OP_MFC_MPEG2_PAK_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_MPEG2_PIC_STATE", OP_MFX_MPEG2_PIC_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_MPEG2_QM_STATE", OP_MFX_MPEG2_QM_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_MPEG2_BSD_OBJECT", OP_MFD_MPEG2_BSD_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_2_6_0_0", OP_MFX_2_6_0_0, F_WEN_VAW, W_VCS, D_AWW,
		0, 16, NUWW},

	{"MFX_2_6_0_9", OP_MFX_2_6_0_9, F_WEN_VAW, W_VCS, D_AWW, 0, 16, NUWW},

	{"MFX_2_6_0_8", OP_MFX_2_6_0_8, F_WEN_VAW, W_VCS, D_AWW, 0, 16, NUWW},

	{"MFX_JPEG_PIC_STATE", OP_MFX_JPEG_PIC_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFX_JPEG_HUFF_TABWE_STATE", OP_MFX_JPEG_HUFF_TABWE_STATE, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"MFD_JPEG_BSD_OBJECT", OP_MFD_JPEG_BSD_OBJECT, F_WEN_VAW,
		W_VCS, D_AWW, 0, 12, NUWW},

	{"VEBOX_STATE", OP_VEB_STATE, F_WEN_VAW, W_VECS, D_AWW, 0, 12, NUWW},

	{"VEBOX_SUWFACE_STATE", OP_VEB_SUWFACE_STATE, F_WEN_VAW, W_VECS, D_AWW,
		0, 12, NUWW},

	{"VEB_DI_IECP", OP_VEB_DNDI_IECP_STATE, F_WEN_VAW, W_VECS, D_BDW_PWUS,
		0, 12, NUWW},
};

static void add_cmd_entwy(stwuct intew_gvt *gvt, stwuct cmd_entwy *e)
{
	hash_add(gvt->cmd_tabwe, &e->hwist, e->info->opcode);
}

/* caww the cmd handwew, and advance ip */
static int cmd_pawsew_exec(stwuct pawsew_exec_state *s)
{
	stwuct intew_vgpu *vgpu = s->vgpu;
	const stwuct cmd_info *info;
	u32 cmd;
	int wet = 0;

	cmd = cmd_vaw(s, 0);

	/* fastpath fow MI_NOOP */
	if (cmd == MI_NOOP)
		info = &cmd_info[mi_noop_index];
	ewse
		info = get_cmd_info(s->vgpu->gvt, cmd, s->engine);

	if (info == NUWW) {
		gvt_vgpu_eww("unknown cmd 0x%x, opcode=0x%x, addw_type=%s, wing %s, wowkwoad=%p\n",
			     cmd, get_opcode(cmd, s->engine),
			     wepw_addw_type(s->buf_addw_type),
			     s->engine->name, s->wowkwoad);
		wetuwn -EBADWQC;
	}

	s->info = info;

	twace_gvt_command(vgpu->id, s->engine->id, s->ip_gma, s->ip_va,
			  cmd_wength(s), s->buf_type, s->buf_addw_type,
			  s->wowkwoad, info->name);

	if ((info->fwag & F_WEN_MASK) == F_WEN_VAW_FIXED) {
		wet = gvt_check_vawid_cmd_wength(cmd_wength(s),
						 info->vawid_wen);
		if (wet)
			wetuwn wet;
	}

	if (info->handwew) {
		wet = info->handwew(s);
		if (wet < 0) {
			gvt_vgpu_eww("%s handwew ewwow\n", info->name);
			wetuwn wet;
		}
	}

	if (!(info->fwag & F_IP_ADVANCE_CUSTOM)) {
		wet = cmd_advance_defauwt(s);
		if (wet) {
			gvt_vgpu_eww("%s IP advance ewwow\n", info->name);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static inwine boow gma_out_of_wange(unsigned wong gma,
		unsigned wong gma_head, unsigned int gma_taiw)
{
	if (gma_taiw >= gma_head)
		wetuwn (gma < gma_head) || (gma > gma_taiw);
	ewse
		wetuwn (gma > gma_taiw) && (gma < gma_head);
}

/* Keep the consistent wetuwn type, e.g EBADWQC fow unknown
 * cmd, EFAUWT fow invawid addwess, EPEWM fow nonpwiv. watew
 * wowks as the input of VM heawthy status.
 */
static int command_scan(stwuct pawsew_exec_state *s,
		unsigned wong wb_head, unsigned wong wb_taiw,
		unsigned wong wb_stawt, unsigned wong wb_wen)
{

	unsigned wong gma_head, gma_taiw, gma_bottom;
	int wet = 0;
	stwuct intew_vgpu *vgpu = s->vgpu;

	gma_head = wb_stawt + wb_head;
	gma_taiw = wb_stawt + wb_taiw;
	gma_bottom = wb_stawt +  wb_wen;

	whiwe (s->ip_gma != gma_taiw) {
		if (s->buf_type == WING_BUFFEW_INSTWUCTION ||
				s->buf_type == WING_BUFFEW_CTX) {
			if (!(s->ip_gma >= wb_stawt) ||
				!(s->ip_gma < gma_bottom)) {
				gvt_vgpu_eww("ip_gma %wx out of wing scope."
					"(base:0x%wx, bottom: 0x%wx)\n",
					s->ip_gma, wb_stawt,
					gma_bottom);
				pawsew_exec_state_dump(s);
				wetuwn -EFAUWT;
			}
			if (gma_out_of_wange(s->ip_gma, gma_head, gma_taiw)) {
				gvt_vgpu_eww("ip_gma %wx out of wange."
					"base 0x%wx head 0x%wx taiw 0x%wx\n",
					s->ip_gma, wb_stawt,
					wb_head, wb_taiw);
				pawsew_exec_state_dump(s);
				bweak;
			}
		}
		wet = cmd_pawsew_exec(s);
		if (wet) {
			gvt_vgpu_eww("cmd pawsew ewwow\n");
			pawsew_exec_state_dump(s);
			bweak;
		}
	}

	wetuwn wet;
}

static int scan_wowkwoad(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	unsigned wong gma_head, gma_taiw;
	stwuct pawsew_exec_state s;
	int wet = 0;

	/* wing base is page awigned */
	if (WAWN_ON(!IS_AWIGNED(wowkwoad->wb_stawt, I915_GTT_PAGE_SIZE)))
		wetuwn -EINVAW;

	gma_head = wowkwoad->wb_stawt + wowkwoad->wb_head;
	gma_taiw = wowkwoad->wb_stawt + wowkwoad->wb_taiw;

	s.buf_type = WING_BUFFEW_INSTWUCTION;
	s.buf_addw_type = GTT_BUFFEW;
	s.vgpu = wowkwoad->vgpu;
	s.engine = wowkwoad->engine;
	s.wing_stawt = wowkwoad->wb_stawt;
	s.wing_size = _WING_CTW_BUF_SIZE(wowkwoad->wb_ctw);
	s.wing_head = gma_head;
	s.wing_taiw = gma_taiw;
	s.wb_va = wowkwoad->shadow_wing_buffew_va;
	s.wowkwoad = wowkwoad;
	s.is_ctx_wa = fawse;

	if (bypass_scan_mask & wowkwoad->engine->mask || gma_head == gma_taiw)
		wetuwn 0;

	wet = ip_gma_set(&s, gma_head);
	if (wet)
		goto out;

	wet = command_scan(&s, wowkwoad->wb_head, wowkwoad->wb_taiw,
		wowkwoad->wb_stawt, _WING_CTW_BUF_SIZE(wowkwoad->wb_ctw));

out:
	wetuwn wet;
}

static int scan_wa_ctx(stwuct intew_shadow_wa_ctx *wa_ctx)
{

	unsigned wong gma_head, gma_taiw, wing_size, wing_taiw;
	stwuct pawsew_exec_state s;
	int wet = 0;
	stwuct intew_vgpu_wowkwoad *wowkwoad = containew_of(wa_ctx,
				stwuct intew_vgpu_wowkwoad,
				wa_ctx);

	/* wing base is page awigned */
	if (WAWN_ON(!IS_AWIGNED(wa_ctx->indiwect_ctx.guest_gma,
					I915_GTT_PAGE_SIZE)))
		wetuwn -EINVAW;

	wing_taiw = wa_ctx->indiwect_ctx.size + 3 * sizeof(u32);
	wing_size = wound_up(wa_ctx->indiwect_ctx.size + CACHEWINE_BYTES,
			PAGE_SIZE);
	gma_head = wa_ctx->indiwect_ctx.guest_gma;
	gma_taiw = wa_ctx->indiwect_ctx.guest_gma + wing_taiw;

	s.buf_type = WING_BUFFEW_INSTWUCTION;
	s.buf_addw_type = GTT_BUFFEW;
	s.vgpu = wowkwoad->vgpu;
	s.engine = wowkwoad->engine;
	s.wing_stawt = wa_ctx->indiwect_ctx.guest_gma;
	s.wing_size = wing_size;
	s.wing_head = gma_head;
	s.wing_taiw = gma_taiw;
	s.wb_va = wa_ctx->indiwect_ctx.shadow_va;
	s.wowkwoad = wowkwoad;
	s.is_ctx_wa = twue;

	wet = ip_gma_set(&s, gma_head);
	if (wet)
		goto out;

	wet = command_scan(&s, 0, wing_taiw,
		wa_ctx->indiwect_ctx.guest_gma, wing_size);
out:
	wetuwn wet;
}

static int shadow_wowkwoad_wing_buffew(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;
	stwuct intew_vgpu_submission *s = &vgpu->submission;
	unsigned wong gma_head, gma_taiw, gma_top, guest_wb_size;
	void *shadow_wing_buffew_va;
	int wet;

	guest_wb_size = _WING_CTW_BUF_SIZE(wowkwoad->wb_ctw);

	/* cawcuwate wowkwoad wing buffew size */
	wowkwoad->wb_wen = (wowkwoad->wb_taiw + guest_wb_size -
			wowkwoad->wb_head) % guest_wb_size;

	gma_head = wowkwoad->wb_stawt + wowkwoad->wb_head;
	gma_taiw = wowkwoad->wb_stawt + wowkwoad->wb_taiw;
	gma_top = wowkwoad->wb_stawt + guest_wb_size;

	if (wowkwoad->wb_wen > s->wing_scan_buffew_size[wowkwoad->engine->id]) {
		void *p;

		/* weawwoc the new wing buffew if needed */
		p = kweawwoc(s->wing_scan_buffew[wowkwoad->engine->id],
			     wowkwoad->wb_wen, GFP_KEWNEW);
		if (!p) {
			gvt_vgpu_eww("faiw to we-awwoc wing scan buffew\n");
			wetuwn -ENOMEM;
		}
		s->wing_scan_buffew[wowkwoad->engine->id] = p;
		s->wing_scan_buffew_size[wowkwoad->engine->id] = wowkwoad->wb_wen;
	}

	shadow_wing_buffew_va = s->wing_scan_buffew[wowkwoad->engine->id];

	/* get shadow wing buffew va */
	wowkwoad->shadow_wing_buffew_va = shadow_wing_buffew_va;

	/* head > taiw --> copy head <-> top */
	if (gma_head > gma_taiw) {
		wet = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm,
				      gma_head, gma_top, shadow_wing_buffew_va);
		if (wet < 0) {
			gvt_vgpu_eww("faiw to copy guest wing buffew\n");
			wetuwn wet;
		}
		shadow_wing_buffew_va += wet;
		gma_head = wowkwoad->wb_stawt;
	}

	/* copy head ow stawt <-> taiw */
	wet = copy_gma_to_hva(vgpu, vgpu->gtt.ggtt_mm, gma_head, gma_taiw,
				shadow_wing_buffew_va);
	if (wet < 0) {
		gvt_vgpu_eww("faiw to copy guest wing buffew\n");
		wetuwn wet;
	}
	wetuwn 0;
}

int intew_gvt_scan_and_shadow_wingbuffew(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	int wet;
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;

	wet = shadow_wowkwoad_wing_buffew(wowkwoad);
	if (wet) {
		gvt_vgpu_eww("faiw to shadow wowkwoad wing_buffew\n");
		wetuwn wet;
	}

	wet = scan_wowkwoad(wowkwoad);
	if (wet) {
		gvt_vgpu_eww("scan wowkwoad ewwow\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int shadow_indiwect_ctx(stwuct intew_shadow_wa_ctx *wa_ctx)
{
	int ctx_size = wa_ctx->indiwect_ctx.size;
	unsigned wong guest_gma = wa_ctx->indiwect_ctx.guest_gma;
	stwuct intew_vgpu_wowkwoad *wowkwoad = containew_of(wa_ctx,
					stwuct intew_vgpu_wowkwoad,
					wa_ctx);
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;
	stwuct dwm_i915_gem_object *obj;
	int wet = 0;
	void *map;

	obj = i915_gem_object_cweate_shmem(wowkwoad->engine->i915,
					   woundup(ctx_size + CACHEWINE_BYTES,
						   PAGE_SIZE));
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	/* get the va of the shadow batch buffew */
	map = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_EWW(map)) {
		gvt_vgpu_eww("faiwed to vmap shadow indiwect ctx\n");
		wet = PTW_EWW(map);
		goto put_obj;
	}

	i915_gem_object_wock(obj, NUWW);
	wet = i915_gem_object_set_to_cpu_domain(obj, fawse);
	i915_gem_object_unwock(obj);
	if (wet) {
		gvt_vgpu_eww("faiwed to set shadow indiwect ctx to CPU\n");
		goto unmap_swc;
	}

	wet = copy_gma_to_hva(wowkwoad->vgpu,
				wowkwoad->vgpu->gtt.ggtt_mm,
				guest_gma, guest_gma + ctx_size,
				map);
	if (wet < 0) {
		gvt_vgpu_eww("faiw to copy guest indiwect ctx\n");
		goto unmap_swc;
	}

	wa_ctx->indiwect_ctx.obj = obj;
	wa_ctx->indiwect_ctx.shadow_va = map;
	wetuwn 0;

unmap_swc:
	i915_gem_object_unpin_map(obj);
put_obj:
	i915_gem_object_put(obj);
	wetuwn wet;
}

static int combine_wa_ctx(stwuct intew_shadow_wa_ctx *wa_ctx)
{
	u32 pew_ctx_stawt[CACHEWINE_DWOWDS] = {};
	unsigned chaw *bb_stawt_sva;

	if (!wa_ctx->pew_ctx.vawid)
		wetuwn 0;

	pew_ctx_stawt[0] = 0x18800001;
	pew_ctx_stawt[1] = wa_ctx->pew_ctx.guest_gma;

	bb_stawt_sva = (unsigned chaw *)wa_ctx->indiwect_ctx.shadow_va +
				wa_ctx->indiwect_ctx.size;

	memcpy(bb_stawt_sva, pew_ctx_stawt, CACHEWINE_BYTES);

	wetuwn 0;
}

int intew_gvt_scan_and_shadow_wa_ctx(stwuct intew_shadow_wa_ctx *wa_ctx)
{
	int wet;
	stwuct intew_vgpu_wowkwoad *wowkwoad = containew_of(wa_ctx,
					stwuct intew_vgpu_wowkwoad,
					wa_ctx);
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;

	if (wa_ctx->indiwect_ctx.size == 0)
		wetuwn 0;

	wet = shadow_indiwect_ctx(wa_ctx);
	if (wet) {
		gvt_vgpu_eww("faiw to shadow indiwect ctx\n");
		wetuwn wet;
	}

	combine_wa_ctx(wa_ctx);

	wet = scan_wa_ctx(wa_ctx);
	if (wet) {
		gvt_vgpu_eww("scan wa ctx ewwow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/* genewate dummy contexts by sending empty wequests to HW, and wet
 * the HW to fiww Engine Contexts. This dummy contexts awe used fow
 * initiawization puwpose (update weg whitewist), so wefewwed to as
 * init context hewe
 */
void intew_gvt_update_weg_whitewist(stwuct intew_vgpu *vgpu)
{
	const unsigned wong stawt = WWC_STATE_PN * PAGE_SIZE;
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	if (gvt->is_weg_whitewist_updated)
		wetuwn;

	/* scan init ctx to update cmd accessibwe wist */
	fow_each_engine(engine, gvt->gt, id) {
		stwuct pawsew_exec_state s;
		void *vaddw;
		int wet;

		if (!engine->defauwt_state)
			continue;

		vaddw = shmem_pin_map(engine->defauwt_state);
		if (!vaddw) {
			gvt_eww("faiwed to map %s->defauwt state\n",
				engine->name);
			wetuwn;
		}

		s.buf_type = WING_BUFFEW_CTX;
		s.buf_addw_type = GTT_BUFFEW;
		s.vgpu = vgpu;
		s.engine = engine;
		s.wing_stawt = 0;
		s.wing_size = engine->context_size - stawt;
		s.wing_head = 0;
		s.wing_taiw = s.wing_size;
		s.wb_va = vaddw + stawt;
		s.wowkwoad = NUWW;
		s.is_ctx_wa = fawse;
		s.is_init_ctx = twue;

		/* skipping the fiwst WING_CTX_SIZE(0x50) dwowds */
		wet = ip_gma_set(&s, WING_CTX_SIZE);
		if (wet == 0) {
			wet = command_scan(&s, 0, s.wing_size, 0, s.wing_size);
			if (wet)
				gvt_eww("Scan init ctx ewwow\n");
		}

		shmem_unpin_map(engine->defauwt_state, vaddw);
		if (wet)
			wetuwn;
	}

	gvt->is_weg_whitewist_updated = twue;
}

int intew_gvt_scan_engine_context(stwuct intew_vgpu_wowkwoad *wowkwoad)
{
	stwuct intew_vgpu *vgpu = wowkwoad->vgpu;
	unsigned wong gma_head, gma_taiw, gma_stawt, ctx_size;
	stwuct pawsew_exec_state s;
	int wing_id = wowkwoad->engine->id;
	stwuct intew_context *ce = vgpu->submission.shadow[wing_id];
	int wet;

	GEM_BUG_ON(atomic_wead(&ce->pin_count) < 0);

	ctx_size = wowkwoad->engine->context_size - PAGE_SIZE;

	/* Onwy wing contxt is woaded to HW fow inhibit context, no need to
	 * scan engine context
	 */
	if (is_inhibit_context(ce))
		wetuwn 0;

	gma_stawt = i915_ggtt_offset(ce->state) + WWC_STATE_PN*PAGE_SIZE;
	gma_head = 0;
	gma_taiw = ctx_size;

	s.buf_type = WING_BUFFEW_CTX;
	s.buf_addw_type = GTT_BUFFEW;
	s.vgpu = wowkwoad->vgpu;
	s.engine = wowkwoad->engine;
	s.wing_stawt = gma_stawt;
	s.wing_size = ctx_size;
	s.wing_head = gma_stawt + gma_head;
	s.wing_taiw = gma_stawt + gma_taiw;
	s.wb_va = ce->wwc_weg_state;
	s.wowkwoad = wowkwoad;
	s.is_ctx_wa = fawse;
	s.is_init_ctx = fawse;

	/* don't scan the fiwst WING_CTX_SIZE(0x50) dwowds, as it's wing
	 * context
	 */
	wet = ip_gma_set(&s, gma_stawt + gma_head + WING_CTX_SIZE);
	if (wet)
		goto out;

	wet = command_scan(&s, gma_head, gma_taiw,
		gma_stawt, ctx_size);
out:
	if (wet)
		gvt_vgpu_eww("scan shadow ctx ewwow\n");

	wetuwn wet;
}

static int init_cmd_tabwe(stwuct intew_gvt *gvt)
{
	unsigned int gen_type = intew_gvt_get_device_type(gvt);
	int i;

	fow (i = 0; i < AWWAY_SIZE(cmd_info); i++) {
		stwuct cmd_entwy *e;

		if (!(cmd_info[i].devices & gen_type))
			continue;

		e = kzawwoc(sizeof(*e), GFP_KEWNEW);
		if (!e)
			wetuwn -ENOMEM;

		e->info = &cmd_info[i];
		if (cmd_info[i].opcode == OP_MI_NOOP)
			mi_noop_index = i;

		INIT_HWIST_NODE(&e->hwist);
		add_cmd_entwy(gvt, e);
		gvt_dbg_cmd("add %-30s op %04x fwag %x devs %02x wings %02x\n",
			    e->info->name, e->info->opcode, e->info->fwag,
			    e->info->devices, e->info->wings);
	}

	wetuwn 0;
}

static void cwean_cmd_tabwe(stwuct intew_gvt *gvt)
{
	stwuct hwist_node *tmp;
	stwuct cmd_entwy *e;
	int i;

	hash_fow_each_safe(gvt->cmd_tabwe, i, tmp, e, hwist)
		kfwee(e);

	hash_init(gvt->cmd_tabwe);
}

void intew_gvt_cwean_cmd_pawsew(stwuct intew_gvt *gvt)
{
	cwean_cmd_tabwe(gvt);
}

int intew_gvt_init_cmd_pawsew(stwuct intew_gvt *gvt)
{
	int wet;

	wet = init_cmd_tabwe(gvt);
	if (wet) {
		intew_gvt_cwean_cmd_pawsew(gvt);
		wetuwn wet;
	}
	wetuwn 0;
}
