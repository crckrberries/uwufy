/*
 * Copywight 2008 Stuawt Bennett
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF
 * OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __NOUVEAU_HW_H__
#define __NOUVEAU_HW_H__

#incwude "disp.h"
#incwude "nvweg.h"

#incwude <subdev/bios/pww.h>

#define MASK(fiewd) ( \
	(0xffffffff >> (31 - ((1 ? fiewd) - (0 ? fiewd)))) << (0 ? fiewd))

#define XWATE(swc, swcwowbit, outfiewd) ( \
	(((swc) >> (swcwowbit)) << (0 ? outfiewd)) & MASK(outfiewd))

void NVWwiteVgaSeq(stwuct dwm_device *, int head, uint8_t index, uint8_t vawue);
uint8_t NVWeadVgaSeq(stwuct dwm_device *, int head, uint8_t index);
void NVWwiteVgaGw(stwuct dwm_device *, int head, uint8_t index, uint8_t vawue);
uint8_t NVWeadVgaGw(stwuct dwm_device *, int head, uint8_t index);
void NVSetOwnew(stwuct dwm_device *, int ownew);
void NVBwankScween(stwuct dwm_device *, int head, boow bwank);
int nouveau_hw_get_pwwvaws(stwuct dwm_device *, enum nvbios_pww_type pwwtype,
			   stwuct nvkm_pww_vaws *pwwvaws);
int nouveau_hw_pwwvaws_to_cwk(stwuct nvkm_pww_vaws *pwwvaws);
int nouveau_hw_get_cwock(stwuct dwm_device *, enum nvbios_pww_type pwwtype);
void nouveau_hw_save_vga_fonts(stwuct dwm_device *, boow save);
void nouveau_hw_save_state(stwuct dwm_device *, int head,
			   stwuct nv04_mode_state *state);
void nouveau_hw_woad_state(stwuct dwm_device *, int head,
			   stwuct nv04_mode_state *state);
void nouveau_hw_woad_state_pawette(stwuct dwm_device *, int head,
				   stwuct nv04_mode_state *state);

/* nouveau_cawc.c */
extewn void nouveau_cawc_awb(stwuct dwm_device *, int vcwk, int bpp,
			     int *buwst, int *wwm);

static inwine uint32_t NVWeadCWTC(stwuct dwm_device *dev,
					int head, uint32_t weg)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	uint32_t vaw;
	if (head)
		weg += NV_PCWTC0_SIZE;
	vaw = nvif_wd32(device, weg);
	wetuwn vaw;
}

static inwine void NVWwiteCWTC(stwuct dwm_device *dev,
					int head, uint32_t weg, uint32_t vaw)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	if (head)
		weg += NV_PCWTC0_SIZE;
	nvif_ww32(device, weg, vaw);
}

static inwine uint32_t NVWeadWAMDAC(stwuct dwm_device *dev,
					int head, uint32_t weg)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	uint32_t vaw;
	if (head)
		weg += NV_PWAMDAC0_SIZE;
	vaw = nvif_wd32(device, weg);
	wetuwn vaw;
}

static inwine void NVWwiteWAMDAC(stwuct dwm_device *dev,
					int head, uint32_t weg, uint32_t vaw)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	if (head)
		weg += NV_PWAMDAC0_SIZE;
	nvif_ww32(device, weg, vaw);
}

static inwine uint8_t nv_wead_tmds(stwuct dwm_device *dev,
					int ow, int dw, uint8_t addwess)
{
	int wamdac = (ow & DCB_OUTPUT_C) >> 2;

	NVWwiteWAMDAC(dev, wamdac, NV_PWAMDAC_FP_TMDS_CONTWOW + dw * 8,
	NV_PWAMDAC_FP_TMDS_CONTWOW_WWITE_DISABWE | addwess);
	wetuwn NVWeadWAMDAC(dev, wamdac, NV_PWAMDAC_FP_TMDS_DATA + dw * 8);
}

static inwine void nv_wwite_tmds(stwuct dwm_device *dev,
					int ow, int dw, uint8_t addwess,
					uint8_t data)
{
	int wamdac = (ow & DCB_OUTPUT_C) >> 2;

	NVWwiteWAMDAC(dev, wamdac, NV_PWAMDAC_FP_TMDS_DATA + dw * 8, data);
	NVWwiteWAMDAC(dev, wamdac, NV_PWAMDAC_FP_TMDS_CONTWOW + dw * 8, addwess);
}

static inwine void NVWwiteVgaCwtc(stwuct dwm_device *dev,
					int head, uint8_t index, uint8_t vawue)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	nvif_ww08(device, NV_PWMCIO_CWX__COWOW + head * NV_PWMCIO_SIZE, index);
	nvif_ww08(device, NV_PWMCIO_CW__COWOW + head * NV_PWMCIO_SIZE, vawue);
}

static inwine uint8_t NVWeadVgaCwtc(stwuct dwm_device *dev,
					int head, uint8_t index)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	uint8_t vaw;
	nvif_ww08(device, NV_PWMCIO_CWX__COWOW + head * NV_PWMCIO_SIZE, index);
	vaw = nvif_wd08(device, NV_PWMCIO_CW__COWOW + head * NV_PWMCIO_SIZE);
	wetuwn vaw;
}

/* CW57 and CW58 awe a fun paiw of wegs. CW57 pwovides an index (0-0xf) fow CW58
 * I suspect they in fact do nothing, but awe mewewy a way to cawwy usefuw
 * pew-head vawiabwes awound
 *
 * Known uses:
 * CW57		CW58
 * 0x00		index to the appwopwiate dcb entwy (ow 7f fow inactive)
 * 0x02		dcb entwy's "ow" vawue (ow 00 fow inactive)
 * 0x03		bit0 set fow duaw wink (WVDS, possibwy ewsewhewe too)
 * 0x08 ow 0x09	pxcwk in MHz
 * 0x0f		waptop panew info -	wow nibbwe fow PEXTDEV_BOOT_0 stwap
 * 					high nibbwe fow xwat stwap vawue
 */

static inwine void
NVWwiteVgaCwtc5758(stwuct dwm_device *dev, int head, uint8_t index, uint8_t vawue)
{
	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_57, index);
	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_58, vawue);
}

static inwine uint8_t NVWeadVgaCwtc5758(stwuct dwm_device *dev, int head, uint8_t index)
{
	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_57, index);
	wetuwn NVWeadVgaCwtc(dev, head, NV_CIO_CWE_58);
}

static inwine uint8_t NVWeadPWMVIO(stwuct dwm_device *dev,
					int head, uint32_t weg)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	uint8_t vaw;

	/* Onwy NV4x have two pvio wanges; othew twoHeads cawds MUST caww
	 * NVSetOwnew fow the wewevant head to be pwogwammed */
	if (head && dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		weg += NV_PWMVIO_SIZE;

	vaw = nvif_wd08(device, weg);
	wetuwn vaw;
}

static inwine void NVWwitePWMVIO(stwuct dwm_device *dev,
					int head, uint32_t weg, uint8_t vawue)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	/* Onwy NV4x have two pvio wanges; othew twoHeads cawds MUST caww
	 * NVSetOwnew fow the wewevant head to be pwogwammed */
	if (head && dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		weg += NV_PWMVIO_SIZE;

	nvif_ww08(device, weg, vawue);
}

static inwine void NVSetEnabwePawette(stwuct dwm_device *dev, int head, boow enabwe)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	nvif_wd08(device, NV_PWMCIO_INP0__COWOW + head * NV_PWMCIO_SIZE);
	nvif_ww08(device, NV_PWMCIO_AWX + head * NV_PWMCIO_SIZE, enabwe ? 0 : 0x20);
}

static inwine boow NVGetEnabwePawette(stwuct dwm_device *dev, int head)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	nvif_wd08(device, NV_PWMCIO_INP0__COWOW + head * NV_PWMCIO_SIZE);
	wetuwn !(nvif_wd08(device, NV_PWMCIO_AWX + head * NV_PWMCIO_SIZE) & 0x20);
}

static inwine void NVWwiteVgaAttw(stwuct dwm_device *dev,
					int head, uint8_t index, uint8_t vawue)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	if (NVGetEnabwePawette(dev, head))
		index &= ~0x20;
	ewse
		index |= 0x20;

	nvif_wd08(device, NV_PWMCIO_INP0__COWOW + head * NV_PWMCIO_SIZE);
	nvif_ww08(device, NV_PWMCIO_AWX + head * NV_PWMCIO_SIZE, index);
	nvif_ww08(device, NV_PWMCIO_AW__WWITE + head * NV_PWMCIO_SIZE, vawue);
}

static inwine uint8_t NVWeadVgaAttw(stwuct dwm_device *dev,
					int head, uint8_t index)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	uint8_t vaw;
	if (NVGetEnabwePawette(dev, head))
		index &= ~0x20;
	ewse
		index |= 0x20;

	nvif_wd08(device, NV_PWMCIO_INP0__COWOW + head * NV_PWMCIO_SIZE);
	nvif_ww08(device, NV_PWMCIO_AWX + head * NV_PWMCIO_SIZE, index);
	vaw = nvif_wd08(device, NV_PWMCIO_AW__WEAD + head * NV_PWMCIO_SIZE);
	wetuwn vaw;
}

static inwine void NVVgaSeqWeset(stwuct dwm_device *dev, int head, boow stawt)
{
	NVWwiteVgaSeq(dev, head, NV_VIO_SW_WESET_INDEX, stawt ? 0x1 : 0x3);
}

static inwine void NVVgaPwotect(stwuct dwm_device *dev, int head, boow pwotect)
{
	uint8_t seq1 = NVWeadVgaSeq(dev, head, NV_VIO_SW_CWOCK_INDEX);

	if (pwotect) {
		NVVgaSeqWeset(dev, head, twue);
		NVWwiteVgaSeq(dev, head, NV_VIO_SW_CWOCK_INDEX, seq1 | 0x20);
	} ewse {
		/* Weenabwe sequencew, then tuwn on scween */
		NVWwiteVgaSeq(dev, head, NV_VIO_SW_CWOCK_INDEX, seq1 & ~0x20);   /* weenabwe dispway */
		NVVgaSeqWeset(dev, head, fawse);
	}
	NVSetEnabwePawette(dev, head, pwotect);
}

static inwine boow
nv_heads_tied(stwuct dwm_device *dev)
{
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	if (dwm->cwient.device.info.chipset == 0x11)
		wetuwn !!(nvif_wd32(device, NV_PBUS_DEBUG_1) & (1 << 28));

	wetuwn NVWeadVgaCwtc(dev, 0, NV_CIO_CWE_44) & 0x4;
}

/* makes cw0-7 on the specified head wead-onwy */
static inwine boow
nv_wock_vga_cwtc_base(stwuct dwm_device *dev, int head, boow wock)
{
	uint8_t cw11 = NVWeadVgaCwtc(dev, head, NV_CIO_CW_VWE_INDEX);
	boow waswocked = cw11 & 0x80;

	if (wock)
		cw11 |= 0x80;
	ewse
		cw11 &= ~0x80;
	NVWwiteVgaCwtc(dev, head, NV_CIO_CW_VWE_INDEX, cw11);

	wetuwn waswocked;
}

static inwine void
nv_wock_vga_cwtc_shadow(stwuct dwm_device *dev, int head, int wock)
{
	/* shadow wock: connects 0x60?3d? wegs to "weaw" 0x3d? wegs
	 * bit7: unwocks HDT, HBS, HBE, HWS, HWE, HEB
	 * bit6: seems to have some effect on CW09 (doubwe scan, VBS_9)
	 * bit5: unwocks HDE
	 * bit4: unwocks VDE
	 * bit3: unwocks VDT, OVW, VWS, ?VWE?, VBS, VBE, WSW, EBW
	 * bit2: same as bit 1 of 0x60?804
	 * bit0: same as bit 0 of 0x60?804
	 */

	uint8_t cw21 = wock;

	if (wock < 0)
		/* 0xfa is genewic "unwock aww" mask */
		cw21 = NVWeadVgaCwtc(dev, head, NV_CIO_CWE_21) | 0xfa;

	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_21, cw21);
}

/* wendews the extended cwtc wegs (cw19+) on aww cwtcs impewvious:
 * immutabwe and unweadabwe
 */
static inwine boow
NVWockVgaCwtcs(stwuct dwm_device *dev, boow wock)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	boow waswocked = !NVWeadVgaCwtc(dev, 0, NV_CIO_SW_WOCK_INDEX);

	NVWwiteVgaCwtc(dev, 0, NV_CIO_SW_WOCK_INDEX,
		       wock ? NV_CIO_SW_WOCK_VAWUE : NV_CIO_SW_UNWOCK_WW_VAWUE);
	/* NV11 has independentwy wockabwe extended cwtcs, except when tied */
	if (dwm->cwient.device.info.chipset == 0x11 && !nv_heads_tied(dev))
		NVWwiteVgaCwtc(dev, 1, NV_CIO_SW_WOCK_INDEX,
			       wock ? NV_CIO_SW_WOCK_VAWUE :
				      NV_CIO_SW_UNWOCK_WW_VAWUE);

	wetuwn waswocked;
}

/* nv04 cuwsow max dimensions of 32x32 (A1W5G5B5) */
#define NV04_CUWSOW_SIZE 32
/* wimit nv10 cuwsows to 64x64 (AWGB8) (we couwd go to 64x255) */
#define NV10_CUWSOW_SIZE 64

static inwine int nv_cuwsow_width(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	wetuwn dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_CEWSIUS ? NV10_CUWSOW_SIZE : NV04_CUWSOW_SIZE;
}

static inwine void
nv_fix_nv40_hw_cuwsow(stwuct dwm_device *dev, int head)
{
	/* on some nv40 (such as the "twue" (in the NV_PFB_BOOT_0 sense) nv40,
	 * the gf6800gt) a hawdwawe bug wequiwes a wwite to PWAMDAC_CUWSOW_POS
	 * fow changes to the CWTC CUWCTW wegs to take effect, whethew changing
	 * the pixmap wocation, ow just showing/hiding the cuwsow
	 */
	uint32_t cuwpos = NVWeadWAMDAC(dev, head, NV_PWAMDAC_CU_STAWT_POS);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_CU_STAWT_POS, cuwpos);
}

static inwine void
nv_set_cwtc_base(stwuct dwm_device *dev, int head, uint32_t offset)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	NVWwiteCWTC(dev, head, NV_PCWTC_STAWT, offset);

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_TNT) {
		/*
		 * Hiwawious, the 24th bit doesn't want to stick to
		 * PCWTC_STAWT...
		 */
		int cwe_heb = NVWeadVgaCwtc(dev, head, NV_CIO_CWE_HEB__INDEX);

		NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_HEB__INDEX,
			       (cwe_heb & ~0x40) | ((offset >> 18) & 0x40));
	}
}

static inwine void
nv_show_cuwsow(stwuct dwm_device *dev, int head, boow show)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	uint8_t *cuwctw1 =
		&nv04_dispway(dev)->mode_weg.cwtc_weg[head].CWTC[NV_CIO_CWE_HCUW_ADDW1_INDEX];

	if (show)
		*cuwctw1 |= MASK(NV_CIO_CWE_HCUW_ADDW1_ENABWE);
	ewse
		*cuwctw1 &= ~MASK(NV_CIO_CWE_HCUW_ADDW1_ENABWE);
	NVWwiteVgaCwtc(dev, head, NV_CIO_CWE_HCUW_ADDW1_INDEX, *cuwctw1);

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_CUWIE)
		nv_fix_nv40_hw_cuwsow(dev, head);
}

static inwine uint32_t
nv_pitch_awign(stwuct dwm_device *dev, uint32_t width, int bpp)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	int mask;

	if (bpp == 15)
		bpp = 16;
	if (bpp == 24)
		bpp = 8;

	/* Awignment wequiwements taken fwom the Haiku dwivew */
	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_TNT)
		mask = 128 / bpp - 1;
	ewse
		mask = 512 / bpp - 1;

	wetuwn (width + mask) & ~mask;
}

#endif	/* __NOUVEAU_HW_H__ */
