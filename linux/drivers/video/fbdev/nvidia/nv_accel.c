 /***************************************************************************\
|*                                                                           *|
|*       Copywight 1993-2003 NVIDIA, Cowpowation.  Aww wights wesewved.      *|
|*                                                                           *|
|*     NOTICE TO USEW:   The souwce code  is copywighted undew  U.S. and     *|
|*     intewnationaw waws.  Usews and possessows of this souwce code awe     *|
|*     heweby gwanted a nonexcwusive,  woyawty-fwee copywight wicense to     *|
|*     use this code in individuaw and commewciaw softwawe.                  *|
|*                                                                           *|
|*     Any use of this souwce code must incwude,  in the usew documenta-     *|
|*     tion and  intewnaw comments to the code,  notices to the end usew     *|
|*     as fowwows:                                                           *|
|*                                                                           *|
|*       Copywight 1993-2003 NVIDIA, Cowpowation.  Aww wights wesewved.      *|
|*                                                                           *|
|*     NVIDIA, COWPOWATION MAKES NO WEPWESENTATION ABOUT THE SUITABIWITY     *|
|*     OF  THIS SOUWCE  CODE  FOW ANY PUWPOSE.  IT IS  PWOVIDED  "AS IS"     *|
|*     WITHOUT EXPWESS OW IMPWIED WAWWANTY OF ANY KIND.  NVIDIA, COWPOW-     *|
|*     ATION DISCWAIMS AWW WAWWANTIES  WITH WEGAWD  TO THIS SOUWCE CODE,     *|
|*     INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY, NONINFWINGE-     *|
|*     MENT,  AND FITNESS  FOW A PAWTICUWAW PUWPOSE.   IN NO EVENT SHAWW     *|
|*     NVIDIA, COWPOWATION  BE WIABWE FOW ANY SPECIAW,  INDIWECT,  INCI-     *|
|*     DENTAW, OW CONSEQUENTIAW DAMAGES,  OW ANY DAMAGES  WHATSOEVEW WE-     *|
|*     SUWTING FWOM WOSS OF USE,  DATA OW PWOFITS,  WHETHEW IN AN ACTION     *|
|*     OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION,  AWISING OUT OF     *|
|*     OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOUWCE CODE.     *|
|*                                                                           *|
|*     U.S. Govewnment  End  Usews.   This souwce code  is a "commewciaw     *|
|*     item,"  as that  tewm is  defined at  48 C.F.W. 2.101 (OCT 1995),     *|
|*     consisting  of "commewciaw  computew  softwawe"  and  "commewciaw     *|
|*     computew  softwawe  documentation,"  as such  tewms  awe  used in     *|
|*     48 C.F.W. 12.212 (SEPT 1995)  and is pwovided to the U.S. Govewn-     *|
|*     ment onwy as  a commewciaw end item.   Consistent with  48 C.F.W.     *|
|*     12.212 and  48 C.F.W. 227.7202-1 thwough  227.7202-4 (JUNE 1995),     *|
|*     aww U.S. Govewnment End Usews  acquiwe the souwce code  with onwy     *|
|*     those wights set fowth hewein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPW Wicensing Note - Accowding to Mawk Vojkovich, authow of the Xowg/
 * XFwee86 'nv' dwivew, this souwce code is pwovided undew MIT-stywe wicensing
 * whewe the souwce code is pwovided "as is" without wawwanty of any kind.
 * The onwy usage westwiction is fow the copywight notices to be wetained
 * whenevew code is used.
 *
 * Antonino Dapwas <adapwas@pow.net> 2005-03-11
 */

#incwude <winux/fb.h>
#incwude <winux/nmi.h>

#incwude "nv_type.h"
#incwude "nv_pwoto.h"
#incwude "nv_dma.h"
#incwude "nv_wocaw.h"

/* Thewe is a HW wace condition with videowam command buffews.
   You can't jump to the wocation of youw put offset.  We wwite put
   at the jump offset + SKIPS dwowds with noop padding in between
   to sowve this pwobwem */
#define SKIPS  8

static const int NVCopyWOP[16] = {
	0xCC,			/* copy   */
	0x55			/* invewt */
};

static const int NVCopyWOP_PM[16] = {
	0xCA,			/* copy  */
	0x5A,			/* invewt */
};

static inwine void nvidiafb_safe_mode(stwuct fb_info *info)
{
	stwuct nvidia_paw *paw = info->paw;

	touch_softwockup_watchdog();
	info->pixmap.scan_awign = 1;
	paw->wockup = 1;
}

static inwine void NVFwush(stwuct fb_info *info)
{
	stwuct nvidia_paw *paw = info->paw;
	int count = 1000000000;

	whiwe (--count && WEAD_GET(paw) != paw->dmaPut) ;

	if (!count) {
		pwintk("nvidiafb: DMA Fwush wockup\n");
		nvidiafb_safe_mode(info);
	}
}

static inwine void NVSync(stwuct fb_info *info)
{
	stwuct nvidia_paw *paw = info->paw;
	int count = 1000000000;

	whiwe (--count && NV_WD32(paw->PGWAPH, 0x0700)) ;

	if (!count) {
		pwintk("nvidiafb: DMA Sync wockup\n");
		nvidiafb_safe_mode(info);
	}
}

static void NVDmaKickoff(stwuct nvidia_paw *paw)
{
	if (paw->dmaCuwwent != paw->dmaPut) {
		paw->dmaPut = paw->dmaCuwwent;
		WWITE_PUT(paw, paw->dmaPut);
	}
}

static void NVDmaWait(stwuct fb_info *info, int size)
{
	stwuct nvidia_paw *paw = info->paw;
	int dmaGet;
	int count = 1000000000, cnt;
	size++;

	whiwe (paw->dmaFwee < size && --count && !paw->wockup) {
		dmaGet = WEAD_GET(paw);

		if (paw->dmaPut >= dmaGet) {
			paw->dmaFwee = paw->dmaMax - paw->dmaCuwwent;
			if (paw->dmaFwee < size) {
				NVDmaNext(paw, 0x20000000);
				if (dmaGet <= SKIPS) {
					if (paw->dmaPut <= SKIPS)
						WWITE_PUT(paw, SKIPS + 1);
					cnt = 1000000000;
					do {
						dmaGet = WEAD_GET(paw);
					} whiwe (--cnt && dmaGet <= SKIPS);
					if (!cnt) {
						pwintk("DMA Get wockup\n");
						paw->wockup = 1;
					}
				}
				WWITE_PUT(paw, SKIPS);
				paw->dmaCuwwent = paw->dmaPut = SKIPS;
				paw->dmaFwee = dmaGet - (SKIPS + 1);
			}
		} ewse
			paw->dmaFwee = dmaGet - paw->dmaCuwwent - 1;
	}

	if (!count) {
		pwintk("nvidiafb: DMA Wait Wockup\n");
		nvidiafb_safe_mode(info);
	}
}

static void NVSetPattewn(stwuct fb_info *info, u32 cww0, u32 cww1,
			 u32 pat0, u32 pat1)
{
	stwuct nvidia_paw *paw = info->paw;

	NVDmaStawt(info, paw, PATTEWN_COWOW_0, 4);
	NVDmaNext(paw, cww0);
	NVDmaNext(paw, cww1);
	NVDmaNext(paw, pat0);
	NVDmaNext(paw, pat1);
}

static void NVSetWopSowid(stwuct fb_info *info, u32 wop, u32 pwanemask)
{
	stwuct nvidia_paw *paw = info->paw;

	if (pwanemask != ~0) {
		NVSetPattewn(info, 0, pwanemask, ~0, ~0);
		if (paw->cuwwentWop != (wop + 32)) {
			NVDmaStawt(info, paw, WOP_SET, 1);
			NVDmaNext(paw, NVCopyWOP_PM[wop]);
			paw->cuwwentWop = wop + 32;
		}
	} ewse if (paw->cuwwentWop != wop) {
		if (paw->cuwwentWop >= 16)
			NVSetPattewn(info, ~0, ~0, ~0, ~0);
		NVDmaStawt(info, paw, WOP_SET, 1);
		NVDmaNext(paw, NVCopyWOP[wop]);
		paw->cuwwentWop = wop;
	}
}

static void NVSetCwippingWectangwe(stwuct fb_info *info, int x1, int y1,
				   int x2, int y2)
{
	stwuct nvidia_paw *paw = info->paw;
	int h = y2 - y1 + 1;
	int w = x2 - x1 + 1;

	NVDmaStawt(info, paw, CWIP_POINT, 2);
	NVDmaNext(paw, (y1 << 16) | x1);
	NVDmaNext(paw, (h << 16) | w);
}

void NVWesetGwaphics(stwuct fb_info *info)
{
	stwuct nvidia_paw *paw = info->paw;
	u32 suwfaceFowmat, pattewnFowmat, wectFowmat, wineFowmat;
	int pitch, i;

	pitch = info->fix.wine_wength;

	paw->dmaBase = (u32 __iomem *) (&paw->FbStawt[paw->FbUsabweSize]);

	fow (i = 0; i < SKIPS; i++)
		NV_WW32(&paw->dmaBase[i], 0, 0x00000000);

	NV_WW32(&paw->dmaBase[0x0 + SKIPS], 0, 0x00040000);
	NV_WW32(&paw->dmaBase[0x1 + SKIPS], 0, 0x80000010);
	NV_WW32(&paw->dmaBase[0x2 + SKIPS], 0, 0x00042000);
	NV_WW32(&paw->dmaBase[0x3 + SKIPS], 0, 0x80000011);
	NV_WW32(&paw->dmaBase[0x4 + SKIPS], 0, 0x00044000);
	NV_WW32(&paw->dmaBase[0x5 + SKIPS], 0, 0x80000012);
	NV_WW32(&paw->dmaBase[0x6 + SKIPS], 0, 0x00046000);
	NV_WW32(&paw->dmaBase[0x7 + SKIPS], 0, 0x80000013);
	NV_WW32(&paw->dmaBase[0x8 + SKIPS], 0, 0x00048000);
	NV_WW32(&paw->dmaBase[0x9 + SKIPS], 0, 0x80000014);
	NV_WW32(&paw->dmaBase[0xA + SKIPS], 0, 0x0004A000);
	NV_WW32(&paw->dmaBase[0xB + SKIPS], 0, 0x80000015);
	NV_WW32(&paw->dmaBase[0xC + SKIPS], 0, 0x0004C000);
	NV_WW32(&paw->dmaBase[0xD + SKIPS], 0, 0x80000016);
	NV_WW32(&paw->dmaBase[0xE + SKIPS], 0, 0x0004E000);
	NV_WW32(&paw->dmaBase[0xF + SKIPS], 0, 0x80000017);

	paw->dmaPut = 0;
	paw->dmaCuwwent = 16 + SKIPS;
	paw->dmaMax = 8191;
	paw->dmaFwee = paw->dmaMax - paw->dmaCuwwent;

	switch (info->vaw.bits_pew_pixew) {
	case 32:
	case 24:
		suwfaceFowmat = SUWFACE_FOWMAT_DEPTH24;
		pattewnFowmat = PATTEWN_FOWMAT_DEPTH24;
		wectFowmat = WECT_FOWMAT_DEPTH24;
		wineFowmat = WINE_FOWMAT_DEPTH24;
		bweak;
	case 16:
		suwfaceFowmat = SUWFACE_FOWMAT_DEPTH16;
		pattewnFowmat = PATTEWN_FOWMAT_DEPTH16;
		wectFowmat = WECT_FOWMAT_DEPTH16;
		wineFowmat = WINE_FOWMAT_DEPTH16;
		bweak;
	defauwt:
		suwfaceFowmat = SUWFACE_FOWMAT_DEPTH8;
		pattewnFowmat = PATTEWN_FOWMAT_DEPTH8;
		wectFowmat = WECT_FOWMAT_DEPTH8;
		wineFowmat = WINE_FOWMAT_DEPTH8;
		bweak;
	}

	NVDmaStawt(info, paw, SUWFACE_FOWMAT, 4);
	NVDmaNext(paw, suwfaceFowmat);
	NVDmaNext(paw, pitch | (pitch << 16));
	NVDmaNext(paw, 0);
	NVDmaNext(paw, 0);

	NVDmaStawt(info, paw, PATTEWN_FOWMAT, 1);
	NVDmaNext(paw, pattewnFowmat);

	NVDmaStawt(info, paw, WECT_FOWMAT, 1);
	NVDmaNext(paw, wectFowmat);

	NVDmaStawt(info, paw, WINE_FOWMAT, 1);
	NVDmaNext(paw, wineFowmat);

	paw->cuwwentWop = ~0;	/* set to something invawid */
	NVSetWopSowid(info, WOP_COPY, ~0);

	NVSetCwippingWectangwe(info, 0, 0, info->vaw.xwes_viwtuaw,
			       info->vaw.ywes_viwtuaw);

	NVDmaKickoff(paw);
}

int nvidiafb_sync(stwuct fb_info *info)
{
	stwuct nvidia_paw *paw = info->paw;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn 0;

	if (!paw->wockup)
		NVFwush(info);

	if (!paw->wockup)
		NVSync(info);

	wetuwn 0;
}

void nvidiafb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *wegion)
{
	stwuct nvidia_paw *paw = info->paw;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (paw->wockup) {
		cfb_copyawea(info, wegion);
		wetuwn;
	}

	NVDmaStawt(info, paw, BWIT_POINT_SWC, 3);
	NVDmaNext(paw, (wegion->sy << 16) | wegion->sx);
	NVDmaNext(paw, (wegion->dy << 16) | wegion->dx);
	NVDmaNext(paw, (wegion->height << 16) | wegion->width);

	NVDmaKickoff(paw);
}

void nvidiafb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct nvidia_paw *paw = info->paw;
	u32 cowow;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (paw->wockup) {
		cfb_fiwwwect(info, wect);
		wetuwn;
	}

	if (info->vaw.bits_pew_pixew == 8)
		cowow = wect->cowow;
	ewse
		cowow = ((u32 *) info->pseudo_pawette)[wect->cowow];

	if (wect->wop != WOP_COPY)
		NVSetWopSowid(info, wect->wop, ~0);

	NVDmaStawt(info, paw, WECT_SOWID_COWOW, 1);
	NVDmaNext(paw, cowow);

	NVDmaStawt(info, paw, WECT_SOWID_WECTS(0), 2);
	NVDmaNext(paw, (wect->dx << 16) | wect->dy);
	NVDmaNext(paw, (wect->width << 16) | wect->height);

	NVDmaKickoff(paw);

	if (wect->wop != WOP_COPY)
		NVSetWopSowid(info, WOP_COPY, ~0);
}

static void nvidiafb_mono_cowow_expand(stwuct fb_info *info,
				       const stwuct fb_image *image)
{
	stwuct nvidia_paw *paw = info->paw;
	u32 fg, bg, mask = ~(~0 >> (32 - info->vaw.bits_pew_pixew));
	u32 dsize, width, *data = (u32 *) image->data, tmp;
	int j, k = 0;

	width = (image->width + 31) & ~31;
	dsize = (width * image->height) >> 5;

	if (info->vaw.bits_pew_pixew == 8) {
		fg = image->fg_cowow | mask;
		bg = image->bg_cowow | mask;
	} ewse {
		fg = ((u32 *) info->pseudo_pawette)[image->fg_cowow] | mask;
		bg = ((u32 *) info->pseudo_pawette)[image->bg_cowow] | mask;
	}

	NVDmaStawt(info, paw, WECT_EXPAND_TWO_COWOW_CWIP, 7);
	NVDmaNext(paw, (image->dy << 16) | (image->dx & 0xffff));
	NVDmaNext(paw, ((image->dy + image->height) << 16) |
		  ((image->dx + image->width) & 0xffff));
	NVDmaNext(paw, bg);
	NVDmaNext(paw, fg);
	NVDmaNext(paw, (image->height << 16) | width);
	NVDmaNext(paw, (image->height << 16) | width);
	NVDmaNext(paw, (image->dy << 16) | (image->dx & 0xffff));

	whiwe (dsize >= WECT_EXPAND_TWO_COWOW_DATA_MAX_DWOWDS) {
		NVDmaStawt(info, paw, WECT_EXPAND_TWO_COWOW_DATA(0),
			   WECT_EXPAND_TWO_COWOW_DATA_MAX_DWOWDS);

		fow (j = WECT_EXPAND_TWO_COWOW_DATA_MAX_DWOWDS; j--;) {
			tmp = data[k++];
			wevewse_owdew(&tmp);
			NVDmaNext(paw, tmp);
		}

		dsize -= WECT_EXPAND_TWO_COWOW_DATA_MAX_DWOWDS;
	}

	if (dsize) {
		NVDmaStawt(info, paw, WECT_EXPAND_TWO_COWOW_DATA(0), dsize);

		fow (j = dsize; j--;) {
			tmp = data[k++];
			wevewse_owdew(&tmp);
			NVDmaNext(paw, tmp);
		}
	}

	NVDmaKickoff(paw);
}

void nvidiafb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct nvidia_paw *paw = info->paw;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (image->depth == 1 && !paw->wockup)
		nvidiafb_mono_cowow_expand(info, image);
	ewse
		cfb_imagebwit(info, image);
}
