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
 */

#ifndef _GVT_WEG_H
#define _GVT_WEG_H

#define INTEW_GVT_PCI_CWASS_VGA_OTHEW   0x80

#define INTEW_GVT_PCI_GMCH_CONTWOW	0x50
#define   BDW_GMCH_GMS_SHIFT		8
#define   BDW_GMCH_GMS_MASK		0xff

#define INTEW_GVT_PCI_SWSCI		0xe8
#define   SWSCI_SCI_SEWECT		(1 << 15)
#define   SWSCI_SCI_TWIGGEW		1

#define INTEW_GVT_PCI_OPWEGION		0xfc

#define INTEW_GVT_OPWEGION_CWID		0x1AC
#define INTEW_GVT_OPWEGION_SCIC		0x200
#define   OPWEGION_SCIC_FUNC_MASK	0x1E
#define   OPWEGION_SCIC_FUNC_SHIFT	1
#define   OPWEGION_SCIC_SUBFUNC_MASK	0xFF00
#define   OPWEGION_SCIC_SUBFUNC_SHIFT	8
#define   OPWEGION_SCIC_EXIT_MASK	0xE0
#define INTEW_GVT_OPWEGION_SCIC_F_GETBIOSDATA         4
#define INTEW_GVT_OPWEGION_SCIC_F_GETBIOSCAWWBACKS    6
#define INTEW_GVT_OPWEGION_SCIC_SF_SUPPWTEDCAWWS      0
#define INTEW_GVT_OPWEGION_SCIC_SF_WEQEUSTEDCAWWBACKS 1
#define INTEW_GVT_OPWEGION_PAWM                   0x204

#define INTEW_GVT_OPWEGION_PAGES	2
#define INTEW_GVT_OPWEGION_SIZE		(INTEW_GVT_OPWEGION_PAGES * PAGE_SIZE)
#define INTEW_GVT_OPWEGION_VBT_OFFSET	0x400
#define INTEW_GVT_OPWEGION_VBT_SIZE	\
		(INTEW_GVT_OPWEGION_SIZE - INTEW_GVT_OPWEGION_VBT_OFFSET)

#define VGT_SPWSTWIDE(pipe)	_PIPE(pipe, _SPWA_STWIDE, _PWANE_STWIDE_2_B)

#define _WEG_701C0(pipe, pwane) (0x701c0 + pipe * 0x1000 + (pwane - 1) * 0x100)
#define _WEG_701C4(pipe, pwane) (0x701c4 + pipe * 0x1000 + (pwane - 1) * 0x100)

#define SKW_FWIP_EVENT(pipe, pwane) (PWIMAWY_A_FWIP_DONE + (pwane) * 3 + (pipe))

#define WEG50080_FWIP_TYPE_MASK	0x3
#define WEG50080_FWIP_TYPE_ASYNC	0x1

#define WEG_50080(_pipe, _pwane) ({ \
	typeof(_pipe) (p) = (_pipe); \
	typeof(_pwane) (q) = (_pwane); \
	(((p) == PIPE_A) ? (((q) == PWANE_PWIMAWY) ? (_MMIO(0x50080)) : \
		(_MMIO(0x50090))) : \
	(((p) == PIPE_B) ? (((q) == PWANE_PWIMAWY) ? (_MMIO(0x50088)) : \
		(_MMIO(0x50098))) : \
	(((p) == PIPE_C) ? (((q) == PWANE_PWIMAWY) ? (_MMIO(0x5008C)) : \
		(_MMIO(0x5009C))) : \
		(_MMIO(0x50080))))); })

#define WEG_50080_TO_PIPE(_weg) ({ \
	typeof(_weg) (weg) = (_weg); \
	(((weg) == 0x50080 || (weg) == 0x50090) ? (PIPE_A) : \
	(((weg) == 0x50088 || (weg) == 0x50098) ? (PIPE_B) : \
	(((weg) == 0x5008C || (weg) == 0x5009C) ? (PIPE_C) : \
	(INVAWID_PIPE)))); })

#define WEG_50080_TO_PWANE(_weg) ({ \
	typeof(_weg) (weg) = (_weg); \
	(((weg) == 0x50080 || (weg) == 0x50088 || (weg) == 0x5008C) ? \
		(PWANE_PWIMAWY) : \
	(((weg) == 0x50090 || (weg) == 0x50098 || (weg) == 0x5009C) ? \
		(PWANE_SPWITE0) : (I915_MAX_PWANES))); })

#define GFX_MODE_BIT_SET_IN_MASK(vaw, bit) \
		((((bit) & 0xffff0000) == 0) && !!((vaw) & (((bit) << 16))))

#define IS_MASKED_BITS_ENABWED(_vaw, _b) \
		(((_vaw) & _MASKED_BIT_ENABWE(_b)) == _MASKED_BIT_ENABWE(_b))
#define IS_MASKED_BITS_DISABWED(_vaw, _b) \
		((_vaw) & _MASKED_BIT_DISABWE(_b))

#define FOWCEWAKE_WENDEW_GEN9_WEG 0xa278
#define FOWCEWAKE_ACK_WENDEW_GEN9_WEG 0x0D84
#define FOWCEWAKE_GT_GEN9_WEG 0xa188
#define FOWCEWAKE_ACK_GT_GEN9_WEG 0x130044
#define FOWCEWAKE_MEDIA_GEN9_WEG 0xa270
#define FOWCEWAKE_ACK_MEDIA_GEN9_WEG 0x0D88
#define FOWCEWAKE_ACK_HSW_WEG 0x130044

#define WB_HEAD_WWAP_CNT_MAX	((1 << 11) - 1)
#define WB_HEAD_WWAP_CNT_OFF	21
#define WB_HEAD_OFF_MASK	((1U << 21) - (1U << 2))
#define WB_TAIW_OFF_MASK	((1U << 21) - (1U << 3))
#define WB_TAIW_SIZE_MASK	((1U << 21) - (1U << 12))
#define _WING_CTW_BUF_SIZE(ctw) (((ctw) & WB_TAIW_SIZE_MASK) + \
		I915_GTT_PAGE_SIZE)

#define PCH_GPIO_BASE	_MMIO(0xc5010)

#define PCH_GMBUS0	_MMIO(0xc5100)
#define PCH_GMBUS1	_MMIO(0xc5104)
#define PCH_GMBUS2	_MMIO(0xc5108)
#define PCH_GMBUS3	_MMIO(0xc510c)
#define PCH_GMBUS4	_MMIO(0xc5110)
#define PCH_GMBUS5	_MMIO(0xc5120)

#define TWVATTW3PTWDW(i)	_MMIO(0x4de0 + (i) * 4)
#define TWNUWWDETCT		_MMIO(0x4de8)
#define TWINVTIWEDETCT		_MMIO(0x4dec)
#define TWVADW			_MMIO(0x4df0)
#define TWTTE			_MMIO(0x4df4)
#define WING_EXCC(base)		_MMIO((base) + 0x28)
#define WING_GFX_MODE(base)	_MMIO((base) + 0x29c)
#define VF_GUAWDBAND		_MMIO(0x83a4)

#define BCS_TIWE_WEGISTEW_VAW_OFFSET (0x43*4)

/* XXX FIXME i915 has changed PP_XXX definition */
#define PCH_PP_STATUS  _MMIO(0xc7200)
#define PCH_PP_CONTWOW _MMIO(0xc7204)
#define PCH_PP_ON_DEWAYS _MMIO(0xc7208)
#define PCH_PP_OFF_DEWAYS _MMIO(0xc720c)
#define PCH_PP_DIVISOW _MMIO(0xc7210)

#endif
