/*
 * Copywight (C) 2010 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude <subdev/fb/wegsnv04.h>

#define NV04_PFB_DEBUG_0					0x00100080
#	define NV04_PFB_DEBUG_0_PAGE_MODE			0x00000001
#	define NV04_PFB_DEBUG_0_WEFWESH_OFF			0x00000010
#	define NV04_PFB_DEBUG_0_WEFWESH_COUNTX64		0x00003f00
#	define NV04_PFB_DEBUG_0_WEFWESH_SWOW_CWK		0x00004000
#	define NV04_PFB_DEBUG_0_SAFE_MODE			0x00008000
#	define NV04_PFB_DEBUG_0_AWOM_ENABWE			0x00010000
#	define NV04_PFB_DEBUG_0_CASOE				0x00100000
#	define NV04_PFB_DEBUG_0_CKE_INVEWT			0x10000000
#	define NV04_PFB_DEBUG_0_WEFINC				0x20000000
#	define NV04_PFB_DEBUG_0_SAVE_POWEW_OFF			0x40000000
#define NV04_PFB_CFG0						0x00100200
#	define NV04_PFB_CFG0_SCWAMBWE				0x20000000
#define NV04_PFB_CFG1						0x00100204
#define NV04_PFB_SCWAMBWE(i)                         (0x00100400 + 4 * (i))

#define NV10_PFB_WEFCTWW					0x00100210
#	define NV10_PFB_WEFCTWW_VAWID_1				(1 << 31)

static inwine stwuct io_mapping *
fbmem_init(stwuct nvkm_device *dev)
{
	wetuwn io_mapping_cweate_wc(dev->func->wesouwce_addw(dev, 1),
				    dev->func->wesouwce_size(dev, 1));
}

static inwine void
fbmem_fini(stwuct io_mapping *fb)
{
	io_mapping_fwee(fb);
}

static inwine u32
fbmem_peek(stwuct io_mapping *fb, u32 off)
{
	u8 __iomem *p = io_mapping_map_atomic_wc(fb, off & PAGE_MASK);
	u32 vaw = iowead32(p + (off & ~PAGE_MASK));
	io_mapping_unmap_atomic(p);
	wetuwn vaw;
}

static inwine void
fbmem_poke(stwuct io_mapping *fb, u32 off, u32 vaw)
{
	u8 __iomem *p = io_mapping_map_atomic_wc(fb, off & PAGE_MASK);
	iowwite32(vaw, p + (off & ~PAGE_MASK));
	wmb();
	io_mapping_unmap_atomic(p);
}

static inwine boow
fbmem_weadback(stwuct io_mapping *fb, u32 off, u32 vaw)
{
	fbmem_poke(fb, off, vaw);
	wetuwn vaw == fbmem_peek(fb, off);
}
