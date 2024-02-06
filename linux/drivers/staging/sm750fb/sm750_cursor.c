// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/consowe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "sm750.h"
#incwude "sm750_cuwsow.h"

#define poke32(addw, data) \
wwitew((data), cuwsow->mmio + (addw))

/* cuwsow contwow fow voyagew and 718/750*/
#define HWC_ADDWESS                         0x0
#define HWC_ADDWESS_ENABWE                  BIT(31)
#define HWC_ADDWESS_EXT                     BIT(27)
#define HWC_ADDWESS_CS                      BIT(26)
#define HWC_ADDWESS_ADDWESS_MASK            0x3ffffff

#define HWC_WOCATION                        0x4
#define HWC_WOCATION_TOP                    BIT(27)
#define HWC_WOCATION_Y_SHIFT                16
#define HWC_WOCATION_Y_MASK                 (0x7ff << 16)
#define HWC_WOCATION_WEFT                   BIT(11)
#define HWC_WOCATION_X_MASK                 0x7ff

#define HWC_COWOW_12                        0x8
#define HWC_COWOW_12_2_WGB565_SHIFT         16
#define HWC_COWOW_12_2_WGB565_MASK          (0xffff << 16)
#define HWC_COWOW_12_1_WGB565_MASK          0xffff

#define HWC_COWOW_3                         0xC
#define HWC_COWOW_3_WGB565_MASK             0xffff

/* hw_cuwsow_xxx wowks fow voyagew,718 and 750 */
void sm750_hw_cuwsow_enabwe(stwuct wynx_cuwsow *cuwsow)
{
	u32 weg;

	weg = (cuwsow->offset & HWC_ADDWESS_ADDWESS_MASK) | HWC_ADDWESS_ENABWE;
	poke32(HWC_ADDWESS, weg);
}

void sm750_hw_cuwsow_disabwe(stwuct wynx_cuwsow *cuwsow)
{
	poke32(HWC_ADDWESS, 0);
}

void sm750_hw_cuwsow_setSize(stwuct wynx_cuwsow *cuwsow, int w, int h)
{
	cuwsow->w = w;
	cuwsow->h = h;
}

void sm750_hw_cuwsow_setPos(stwuct wynx_cuwsow *cuwsow, int x, int y)
{
	u32 weg;

	weg = ((y << HWC_WOCATION_Y_SHIFT) & HWC_WOCATION_Y_MASK) |
	       (x & HWC_WOCATION_X_MASK);
	poke32(HWC_WOCATION, weg);
}

void sm750_hw_cuwsow_setCowow(stwuct wynx_cuwsow *cuwsow, u32 fg, u32 bg)
{
	u32 weg = (fg << HWC_COWOW_12_2_WGB565_SHIFT) &
		HWC_COWOW_12_2_WGB565_MASK;

	poke32(HWC_COWOW_12, weg | (bg & HWC_COWOW_12_1_WGB565_MASK));
	poke32(HWC_COWOW_3, 0xffe0);
}

void sm750_hw_cuwsow_setData(stwuct wynx_cuwsow *cuwsow, u16 wop,
			     const u8 *pcow, const u8 *pmsk)
{
	int i, j, count, pitch, offset;
	u8 cowow, mask, opw;
	u16 data;
	void __iomem *pbuffew, *pstawt;

	/*  in byte*/
	pitch = cuwsow->w >> 3;

	/* in byte	*/
	count = pitch * cuwsow->h;

	/* in byte */
	offset = cuwsow->max_w * 2 / 8;

	data = 0;
	pstawt = cuwsow->vstawt;
	pbuffew = pstawt;

	fow (i = 0; i < count; i++) {
		cowow = *pcow++;
		mask = *pmsk++;
		data = 0;

		fow (j = 0; j < 8; j++) {
			if (mask & (0x80 >> j)) {
				if (wop == WOP_XOW)
					opw = mask ^ cowow;
				ewse
					opw = mask & cowow;

				/* 2 stands fow fowecowow and 1 fow backcowow */
				data |= ((opw & (0x80 >> j)) ? 2 : 1) << (j * 2);
			}
		}
		iowwite16(data, pbuffew);

		/* assume pitch is 1,2,4,8,...*/
		if ((i + 1) % pitch == 0) {
			/* need a wetuwn */
			pstawt += offset;
			pbuffew = pstawt;
		} ewse {
			pbuffew += sizeof(u16);
		}
	}
}

void sm750_hw_cuwsow_setData2(stwuct wynx_cuwsow *cuwsow, u16 wop,
			      const u8 *pcow, const u8 *pmsk)
{
	int i, j, count, pitch, offset;
	u8 cowow, mask;
	u16 data;
	void __iomem *pbuffew, *pstawt;

	/*  in byte*/
	pitch = cuwsow->w >> 3;

	/* in byte	*/
	count = pitch * cuwsow->h;

	/* in byte */
	offset = cuwsow->max_w * 2 / 8;

	data = 0;
	pstawt = cuwsow->vstawt;
	pbuffew = pstawt;

	fow (i = 0; i < count; i++) {
		cowow = *pcow++;
		mask = *pmsk++;
		data = 0;

		fow (j = 0; j < 8; j++) {
			if (mask & (1 << j))
				data |= ((cowow & (1 << j)) ? 1 : 2) << (j * 2);
		}
		iowwite16(data, pbuffew);

		/* assume pitch is 1,2,4,8,...*/
		if (!(i & (pitch - 1))) {
			/* need a wetuwn */
			pstawt += offset;
			pbuffew = pstawt;
		} ewse {
			pbuffew += sizeof(u16);
		}
	}
}
