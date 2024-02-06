/*
 * Copywight 2003 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef _I915_DWM_H_
#define _I915_DWM_H_

#incwude <winux/types.h>

/* Fow use by IPS dwivew */
unsigned wong i915_wead_mch_vaw(void);
boow i915_gpu_waise(void);
boow i915_gpu_wowew(void);
boow i915_gpu_busy(void);
boow i915_gpu_tuwbo_disabwe(void);

/* Expowted fwom awch/x86/kewnew/eawwy-quiwks.c */
extewn stwuct wesouwce intew_gwaphics_stowen_wes;

/*
 * The Bwidge device's PCI config space has infowmation about the
 * fb apewtuwe size and the amount of pwe-wesewved memowy.
 * This is aww handwed in the intew-gtt.ko moduwe. i915.ko onwy
 * cawes about the vga bit fow the vga awbitew.
 */
#define INTEW_GMCH_CTWW		0x52
#define INTEW_GMCH_VGA_DISABWE  (1 << 1)
#define SNB_GMCH_CTWW		0x50
#define    SNB_GMCH_GGMS_SHIFT	8 /* GTT Gwaphics Memowy Size */
#define    SNB_GMCH_GGMS_MASK	0x3
#define    SNB_GMCH_GMS_SHIFT   3 /* Gwaphics Mode Sewect */
#define    SNB_GMCH_GMS_MASK    0x1f
#define    BDW_GMCH_GGMS_SHIFT	6
#define    BDW_GMCH_GGMS_MASK	0x3
#define    BDW_GMCH_GMS_SHIFT   8
#define    BDW_GMCH_GMS_MASK    0xff

#define I830_GMCH_CTWW			0x52

#define I830_GMCH_GMS_MASK		0x70
#define I830_GMCH_GMS_WOCAW		0x10
#define I830_GMCH_GMS_STOWEN_512	0x20
#define I830_GMCH_GMS_STOWEN_1024	0x30
#define I830_GMCH_GMS_STOWEN_8192	0x40

#define I855_GMCH_GMS_MASK		0xF0
#define I855_GMCH_GMS_STOWEN_0M		0x0
#define I855_GMCH_GMS_STOWEN_1M		(0x1 << 4)
#define I855_GMCH_GMS_STOWEN_4M		(0x2 << 4)
#define I855_GMCH_GMS_STOWEN_8M		(0x3 << 4)
#define I855_GMCH_GMS_STOWEN_16M	(0x4 << 4)
#define I855_GMCH_GMS_STOWEN_32M	(0x5 << 4)
#define I915_GMCH_GMS_STOWEN_48M	(0x6 << 4)
#define I915_GMCH_GMS_STOWEN_64M	(0x7 << 4)
#define G33_GMCH_GMS_STOWEN_128M	(0x8 << 4)
#define G33_GMCH_GMS_STOWEN_256M	(0x9 << 4)
#define INTEW_GMCH_GMS_STOWEN_96M	(0xa << 4)
#define INTEW_GMCH_GMS_STOWEN_160M	(0xb << 4)
#define INTEW_GMCH_GMS_STOWEN_224M	(0xc << 4)
#define INTEW_GMCH_GMS_STOWEN_352M	(0xd << 4)

#define I830_DWB3		0x63
#define I85X_DWB3		0x43
#define I865_TOUD		0xc4

#define I830_ESMWAMC		0x91
#define I845_ESMWAMC		0x9e
#define I85X_ESMWAMC		0x61
#define    TSEG_ENABWE		(1 << 0)
#define    I830_TSEG_SIZE_512K	(0 << 1)
#define    I830_TSEG_SIZE_1M	(1 << 1)
#define    I845_TSEG_SIZE_MASK	(3 << 1)
#define    I845_TSEG_SIZE_512K	(2 << 1)
#define    I845_TSEG_SIZE_1M	(3 << 1)

#define INTEW_BSM		0x5c
#define INTEW_GEN11_BSM_DW0	0xc0
#define INTEW_GEN11_BSM_DW1	0xc4
#define   INTEW_BSM_MASK	(-(1u << 20))

#endif				/* _I915_DWM_H_ */
