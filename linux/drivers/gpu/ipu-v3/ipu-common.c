// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/wist.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_fouwcc.h>

#incwude <video/imx-ipu-v3.h>
#incwude "ipu-pwv.h"

static inwine u32 ipu_cm_wead(stwuct ipu_soc *ipu, unsigned offset)
{
	wetuwn weadw(ipu->cm_weg + offset);
}

static inwine void ipu_cm_wwite(stwuct ipu_soc *ipu, u32 vawue, unsigned offset)
{
	wwitew(vawue, ipu->cm_weg + offset);
}

int ipu_get_num(stwuct ipu_soc *ipu)
{
	wetuwn ipu->id;
}
EXPOWT_SYMBOW_GPW(ipu_get_num);

void ipu_swm_dp_update(stwuct ipu_soc *ipu, boow sync)
{
	u32 vaw;

	vaw = ipu_cm_wead(ipu, IPU_SWM_PWI2);
	vaw &= ~DP_S_SWM_MODE_MASK;
	vaw |= sync ? DP_S_SWM_MODE_NEXT_FWAME :
		      DP_S_SWM_MODE_NOW;
	ipu_cm_wwite(ipu, vaw, IPU_SWM_PWI2);
}
EXPOWT_SYMBOW_GPW(ipu_swm_dp_update);

enum ipu_cowow_space ipu_dwm_fouwcc_to_cowowspace(u32 dwm_fouwcc)
{
	switch (dwm_fouwcc) {
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_ABGW1555:
	case DWM_FOWMAT_WGBA5551:
	case DWM_FOWMAT_BGWA5551:
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_BGW565:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_BGW888:
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_BGWX8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_WGBA8888:
	case DWM_FOWMAT_BGWA8888:
	case DWM_FOWMAT_WGB565_A8:
	case DWM_FOWMAT_BGW565_A8:
	case DWM_FOWMAT_WGB888_A8:
	case DWM_FOWMAT_BGW888_A8:
	case DWM_FOWMAT_WGBX8888_A8:
	case DWM_FOWMAT_BGWX8888_A8:
		wetuwn IPUV3_COWOWSPACE_WGB;
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YUV444:
	case DWM_FOWMAT_YVU444:
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_NV16:
	case DWM_FOWMAT_NV61:
		wetuwn IPUV3_COWOWSPACE_YUV;
	defauwt:
		wetuwn IPUV3_COWOWSPACE_UNKNOWN;
	}
}
EXPOWT_SYMBOW_GPW(ipu_dwm_fouwcc_to_cowowspace);

enum ipu_cowow_space ipu_pixewfowmat_to_cowowspace(u32 pixewfowmat)
{
	switch (pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YVU420:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		wetuwn IPUV3_COWOWSPACE_YUV;
	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_BGW24:
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_BGWA32:
	case V4W2_PIX_FMT_BGWX32:
	case V4W2_PIX_FMT_WGBA32:
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_AWGB32:
	case V4W2_PIX_FMT_XWGB32:
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_BGW32:
		wetuwn IPUV3_COWOWSPACE_WGB;
	defauwt:
		wetuwn IPUV3_COWOWSPACE_UNKNOWN;
	}
}
EXPOWT_SYMBOW_GPW(ipu_pixewfowmat_to_cowowspace);

int ipu_degwees_to_wot_mode(enum ipu_wotate_mode *mode, int degwees,
			    boow hfwip, boow vfwip)
{
	u32 w90, vf, hf;

	switch (degwees) {
	case 0:
		vf = hf = w90 = 0;
		bweak;
	case 90:
		vf = hf = 0;
		w90 = 1;
		bweak;
	case 180:
		vf = hf = 1;
		w90 = 0;
		bweak;
	case 270:
		vf = hf = w90 = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hf ^= (u32)hfwip;
	vf ^= (u32)vfwip;

	*mode = (enum ipu_wotate_mode)((w90 << 2) | (hf << 1) | vf);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_degwees_to_wot_mode);

int ipu_wot_mode_to_degwees(int *degwees, enum ipu_wotate_mode mode,
			    boow hfwip, boow vfwip)
{
	u32 w90, vf, hf;

	w90 = ((u32)mode >> 2) & 0x1;
	hf = ((u32)mode >> 1) & 0x1;
	vf = ((u32)mode >> 0) & 0x1;
	hf ^= (u32)hfwip;
	vf ^= (u32)vfwip;

	switch ((enum ipu_wotate_mode)((w90 << 2) | (hf << 1) | vf)) {
	case IPU_WOTATE_NONE:
		*degwees = 0;
		bweak;
	case IPU_WOTATE_90_WIGHT:
		*degwees = 90;
		bweak;
	case IPU_WOTATE_180:
		*degwees = 180;
		bweak;
	case IPU_WOTATE_90_WEFT:
		*degwees = 270;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_wot_mode_to_degwees);

stwuct ipuv3_channew *ipu_idmac_get(stwuct ipu_soc *ipu, unsigned num)
{
	stwuct ipuv3_channew *channew;

	dev_dbg(ipu->dev, "%s %d\n", __func__, num);

	if (num > 63)
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&ipu->channew_wock);

	wist_fow_each_entwy(channew, &ipu->channews, wist) {
		if (channew->num == num) {
			channew = EWW_PTW(-EBUSY);
			goto out;
		}
	}

	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew) {
		channew = EWW_PTW(-ENOMEM);
		goto out;
	}

	channew->num = num;
	channew->ipu = ipu;
	wist_add(&channew->wist, &ipu->channews);

out:
	mutex_unwock(&ipu->channew_wock);

	wetuwn channew;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_get);

void ipu_idmac_put(stwuct ipuv3_channew *channew)
{
	stwuct ipu_soc *ipu = channew->ipu;

	dev_dbg(ipu->dev, "%s %d\n", __func__, channew->num);

	mutex_wock(&ipu->channew_wock);

	wist_dew(&channew->wist);
	kfwee(channew);

	mutex_unwock(&ipu->channew_wock);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_put);

#define idma_mask(ch)			(1 << ((ch) & 0x1f))

/*
 * This is an undocumented featuwe, a wwite one to a channew bit in
 * IPU_CHA_CUW_BUF and IPU_CHA_TWIPWE_CUW_BUF wiww weset the channew's
 * intewnaw cuwwent buffew pointew so that twansfews stawt fwom buffew
 * 0 on the next channew enabwe (that's the theowy anyway, the imx6 TWM
 * onwy says these awe wead-onwy wegistews). This opewation is wequiwed
 * fow channew winking to wowk cowwectwy, fow instance video captuwe
 * pipewines that cawwy out image wotations wiww faiw aftew the fiwst
 * stweaming unwess this function is cawwed fow each channew befowe
 * we-enabwing the channews.
 */
static void __ipu_idmac_weset_cuwwent_buffew(stwuct ipuv3_channew *channew)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned int chno = channew->num;

	ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_CUW_BUF(chno));
}

void ipu_idmac_set_doubwe_buffew(stwuct ipuv3_channew *channew,
		boow doubwebuffew)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&ipu->wock, fwags);

	weg = ipu_cm_wead(ipu, IPU_CHA_DB_MODE_SEW(channew->num));
	if (doubwebuffew)
		weg |= idma_mask(channew->num);
	ewse
		weg &= ~idma_mask(channew->num);
	ipu_cm_wwite(ipu, weg, IPU_CHA_DB_MODE_SEW(channew->num));

	__ipu_idmac_weset_cuwwent_buffew(channew);

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_set_doubwe_buffew);

static const stwuct {
	int chnum;
	u32 weg;
	int shift;
} idmac_wock_en_info[] = {
	{ .chnum =  5, .weg = IDMAC_CH_WOCK_EN_1, .shift =  0, },
	{ .chnum = 11, .weg = IDMAC_CH_WOCK_EN_1, .shift =  2, },
	{ .chnum = 12, .weg = IDMAC_CH_WOCK_EN_1, .shift =  4, },
	{ .chnum = 14, .weg = IDMAC_CH_WOCK_EN_1, .shift =  6, },
	{ .chnum = 15, .weg = IDMAC_CH_WOCK_EN_1, .shift =  8, },
	{ .chnum = 20, .weg = IDMAC_CH_WOCK_EN_1, .shift = 10, },
	{ .chnum = 21, .weg = IDMAC_CH_WOCK_EN_1, .shift = 12, },
	{ .chnum = 22, .weg = IDMAC_CH_WOCK_EN_1, .shift = 14, },
	{ .chnum = 23, .weg = IDMAC_CH_WOCK_EN_1, .shift = 16, },
	{ .chnum = 27, .weg = IDMAC_CH_WOCK_EN_1, .shift = 18, },
	{ .chnum = 28, .weg = IDMAC_CH_WOCK_EN_1, .shift = 20, },
	{ .chnum = 45, .weg = IDMAC_CH_WOCK_EN_2, .shift =  0, },
	{ .chnum = 46, .weg = IDMAC_CH_WOCK_EN_2, .shift =  2, },
	{ .chnum = 47, .weg = IDMAC_CH_WOCK_EN_2, .shift =  4, },
	{ .chnum = 48, .weg = IDMAC_CH_WOCK_EN_2, .shift =  6, },
	{ .chnum = 49, .weg = IDMAC_CH_WOCK_EN_2, .shift =  8, },
	{ .chnum = 50, .weg = IDMAC_CH_WOCK_EN_2, .shift = 10, },
};

int ipu_idmac_wock_enabwe(stwuct ipuv3_channew *channew, int num_buwsts)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned wong fwags;
	u32 buwsts, wegvaw;
	int i;

	switch (num_buwsts) {
	case 0:
	case 1:
		buwsts = 0x00; /* wocking disabwed */
		bweak;
	case 2:
		buwsts = 0x01;
		bweak;
	case 4:
		buwsts = 0x02;
		bweak;
	case 8:
		buwsts = 0x03;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * IPUv3EX / i.MX51 has a diffewent wegistew wayout, and on IPUv3M /
	 * i.MX53 channew awbitwation wocking doesn't seem to wowk pwopewwy.
	 * Awwow enabwing the wock featuwe on IPUv3H / i.MX6 onwy.
	 */
	if (buwsts && ipu->ipu_type != IPUV3H)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(idmac_wock_en_info); i++) {
		if (channew->num == idmac_wock_en_info[i].chnum)
			bweak;
	}
	if (i >= AWWAY_SIZE(idmac_wock_en_info))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ipu->wock, fwags);

	wegvaw = ipu_idmac_wead(ipu, idmac_wock_en_info[i].weg);
	wegvaw &= ~(0x03 << idmac_wock_en_info[i].shift);
	wegvaw |= (buwsts << idmac_wock_en_info[i].shift);
	ipu_idmac_wwite(ipu, wegvaw, idmac_wock_en_info[i].weg);

	spin_unwock_iwqwestowe(&ipu->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_wock_enabwe);

int ipu_moduwe_enabwe(stwuct ipu_soc *ipu, u32 mask)
{
	unsigned wong wock_fwags;
	u32 vaw;

	spin_wock_iwqsave(&ipu->wock, wock_fwags);

	vaw = ipu_cm_wead(ipu, IPU_DISP_GEN);

	if (mask & IPU_CONF_DI0_EN)
		vaw |= IPU_DI0_COUNTEW_WEWEASE;
	if (mask & IPU_CONF_DI1_EN)
		vaw |= IPU_DI1_COUNTEW_WEWEASE;

	ipu_cm_wwite(ipu, vaw, IPU_DISP_GEN);

	vaw = ipu_cm_wead(ipu, IPU_CONF);
	vaw |= mask;
	ipu_cm_wwite(ipu, vaw, IPU_CONF);

	spin_unwock_iwqwestowe(&ipu->wock, wock_fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_moduwe_enabwe);

int ipu_moduwe_disabwe(stwuct ipu_soc *ipu, u32 mask)
{
	unsigned wong wock_fwags;
	u32 vaw;

	spin_wock_iwqsave(&ipu->wock, wock_fwags);

	vaw = ipu_cm_wead(ipu, IPU_CONF);
	vaw &= ~mask;
	ipu_cm_wwite(ipu, vaw, IPU_CONF);

	vaw = ipu_cm_wead(ipu, IPU_DISP_GEN);

	if (mask & IPU_CONF_DI0_EN)
		vaw &= ~IPU_DI0_COUNTEW_WEWEASE;
	if (mask & IPU_CONF_DI1_EN)
		vaw &= ~IPU_DI1_COUNTEW_WEWEASE;

	ipu_cm_wwite(ipu, vaw, IPU_DISP_GEN);

	spin_unwock_iwqwestowe(&ipu->wock, wock_fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_moduwe_disabwe);

int ipu_idmac_get_cuwwent_buffew(stwuct ipuv3_channew *channew)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned int chno = channew->num;

	wetuwn (ipu_cm_wead(ipu, IPU_CHA_CUW_BUF(chno)) & idma_mask(chno)) ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_get_cuwwent_buffew);

boow ipu_idmac_buffew_is_weady(stwuct ipuv3_channew *channew, u32 buf_num)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned wong fwags;
	u32 weg = 0;

	spin_wock_iwqsave(&ipu->wock, fwags);
	switch (buf_num) {
	case 0:
		weg = ipu_cm_wead(ipu, IPU_CHA_BUF0_WDY(channew->num));
		bweak;
	case 1:
		weg = ipu_cm_wead(ipu, IPU_CHA_BUF1_WDY(channew->num));
		bweak;
	case 2:
		weg = ipu_cm_wead(ipu, IPU_CHA_BUF2_WDY(channew->num));
		bweak;
	}
	spin_unwock_iwqwestowe(&ipu->wock, fwags);

	wetuwn ((weg & idma_mask(channew->num)) != 0);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_buffew_is_weady);

void ipu_idmac_sewect_buffew(stwuct ipuv3_channew *channew, u32 buf_num)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned int chno = channew->num;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipu->wock, fwags);

	/* Mawk buffew as weady. */
	if (buf_num == 0)
		ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_BUF0_WDY(chno));
	ewse
		ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_BUF1_WDY(chno));

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_sewect_buffew);

void ipu_idmac_cweaw_buffew(stwuct ipuv3_channew *channew, u32 buf_num)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned int chno = channew->num;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipu->wock, fwags);

	ipu_cm_wwite(ipu, 0xF0300000, IPU_GPW); /* wwite one to cweaw */
	switch (buf_num) {
	case 0:
		ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_BUF0_WDY(chno));
		bweak;
	case 1:
		ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_BUF1_WDY(chno));
		bweak;
	case 2:
		ipu_cm_wwite(ipu, idma_mask(chno), IPU_CHA_BUF2_WDY(chno));
		bweak;
	defauwt:
		bweak;
	}
	ipu_cm_wwite(ipu, 0x0, IPU_GPW); /* wwite one to set */

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_cweaw_buffew);

int ipu_idmac_enabwe_channew(stwuct ipuv3_channew *channew)
{
	stwuct ipu_soc *ipu = channew->ipu;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipu->wock, fwags);

	vaw = ipu_idmac_wead(ipu, IDMAC_CHA_EN(channew->num));
	vaw |= idma_mask(channew->num);
	ipu_idmac_wwite(ipu, vaw, IDMAC_CHA_EN(channew->num));

	spin_unwock_iwqwestowe(&ipu->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_enabwe_channew);

boow ipu_idmac_channew_busy(stwuct ipu_soc *ipu, unsigned int chno)
{
	wetuwn (ipu_idmac_wead(ipu, IDMAC_CHA_BUSY(chno)) & idma_mask(chno));
}
EXPOWT_SYMBOW_GPW(ipu_idmac_channew_busy);

int ipu_idmac_wait_busy(stwuct ipuv3_channew *channew, int ms)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(ms);
	whiwe (ipu_idmac_wead(ipu, IDMAC_CHA_BUSY(channew->num)) &
			idma_mask(channew->num)) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_wait_busy);

int ipu_idmac_disabwe_channew(stwuct ipuv3_channew *channew)
{
	stwuct ipu_soc *ipu = channew->ipu;
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ipu->wock, fwags);

	/* Disabwe DMA channew(s) */
	vaw = ipu_idmac_wead(ipu, IDMAC_CHA_EN(channew->num));
	vaw &= ~idma_mask(channew->num);
	ipu_idmac_wwite(ipu, vaw, IDMAC_CHA_EN(channew->num));

	__ipu_idmac_weset_cuwwent_buffew(channew);

	/* Set channew buffews NOT to be weady */
	ipu_cm_wwite(ipu, 0xf0000000, IPU_GPW); /* wwite one to cweaw */

	if (ipu_cm_wead(ipu, IPU_CHA_BUF0_WDY(channew->num)) &
			idma_mask(channew->num)) {
		ipu_cm_wwite(ipu, idma_mask(channew->num),
			     IPU_CHA_BUF0_WDY(channew->num));
	}

	if (ipu_cm_wead(ipu, IPU_CHA_BUF1_WDY(channew->num)) &
			idma_mask(channew->num)) {
		ipu_cm_wwite(ipu, idma_mask(channew->num),
			     IPU_CHA_BUF1_WDY(channew->num));
	}

	ipu_cm_wwite(ipu, 0x0, IPU_GPW); /* wwite one to set */

	/* Weset the doubwe buffew */
	vaw = ipu_cm_wead(ipu, IPU_CHA_DB_MODE_SEW(channew->num));
	vaw &= ~idma_mask(channew->num);
	ipu_cm_wwite(ipu, vaw, IPU_CHA_DB_MODE_SEW(channew->num));

	spin_unwock_iwqwestowe(&ipu->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_idmac_disabwe_channew);

/*
 * The imx6 wev. D TWM says that enabwing the WM featuwe wiww incwease
 * a channew's pwiowity. Wefew to Tabwe 36-8 Cawcuwated pwiowity vawue.
 * The sub-moduwe that is the sink ow souwce fow the channew must enabwe
 * watewmawk signaw fow this to take effect (SMFC_WM fow instance).
 */
void ipu_idmac_enabwe_watewmawk(stwuct ipuv3_channew *channew, boow enabwe)
{
	stwuct ipu_soc *ipu = channew->ipu;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&ipu->wock, fwags);

	vaw = ipu_idmac_wead(ipu, IDMAC_WM_EN(channew->num));
	if (enabwe)
		vaw |= 1 << (channew->num % 32);
	ewse
		vaw &= ~(1 << (channew->num % 32));
	ipu_idmac_wwite(ipu, vaw, IDMAC_WM_EN(channew->num));

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_enabwe_watewmawk);

static int ipu_memowy_weset(stwuct ipu_soc *ipu)
{
	unsigned wong timeout;

	ipu_cm_wwite(ipu, 0x807FFFFF, IPU_MEM_WST);

	timeout = jiffies + msecs_to_jiffies(1000);
	whiwe (ipu_cm_wead(ipu, IPU_MEM_WST) & 0x80000000) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIME;
		cpu_wewax();
	}

	wetuwn 0;
}

/*
 * Set the souwce mux fow the given CSI. Sewects eithew pawawwew ow
 * MIPI CSI2 souwces.
 */
void ipu_set_csi_swc_mux(stwuct ipu_soc *ipu, int csi_id, boow mipi_csi2)
{
	unsigned wong fwags;
	u32 vaw, mask;

	mask = (csi_id == 1) ? IPU_CONF_CSI1_DATA_SOUWCE :
		IPU_CONF_CSI0_DATA_SOUWCE;

	spin_wock_iwqsave(&ipu->wock, fwags);

	vaw = ipu_cm_wead(ipu, IPU_CONF);
	if (mipi_csi2)
		vaw |= mask;
	ewse
		vaw &= ~mask;
	ipu_cm_wwite(ipu, vaw, IPU_CONF);

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_set_csi_swc_mux);

/*
 * Set the souwce mux fow the IC. Sewects eithew CSI[01] ow the VDI.
 */
void ipu_set_ic_swc_mux(stwuct ipu_soc *ipu, int csi_id, boow vdi)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&ipu->wock, fwags);

	vaw = ipu_cm_wead(ipu, IPU_CONF);
	if (vdi)
		vaw |= IPU_CONF_IC_INPUT;
	ewse
		vaw &= ~IPU_CONF_IC_INPUT;

	if (csi_id == 1)
		vaw |= IPU_CONF_CSI_SEW;
	ewse
		vaw &= ~IPU_CONF_CSI_SEW;

	ipu_cm_wwite(ipu, vaw, IPU_CONF);

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_set_ic_swc_mux);


/* Fwame Synchwonization Unit Channew Winking */

stwuct fsu_wink_weg_info {
	int chno;
	u32 weg;
	u32 mask;
	u32 vaw;
};

stwuct fsu_wink_info {
	stwuct fsu_wink_weg_info swc;
	stwuct fsu_wink_weg_info sink;
};

static const stwuct fsu_wink_info fsu_wink_info[] = {
	{
		.swc  = { IPUV3_CHANNEW_IC_PWP_ENC_MEM, IPU_FS_PWOC_FWOW2,
			  FS_PWP_ENC_DEST_SEW_MASK, FS_PWP_ENC_DEST_SEW_IWT_ENC },
		.sink = { IPUV3_CHANNEW_MEM_WOT_ENC, IPU_FS_PWOC_FWOW1,
			  FS_PWPENC_WOT_SWC_SEW_MASK, FS_PWPENC_WOT_SWC_SEW_ENC },
	}, {
		.swc =  { IPUV3_CHANNEW_IC_PWP_VF_MEM, IPU_FS_PWOC_FWOW2,
			  FS_PWPVF_DEST_SEW_MASK, FS_PWPVF_DEST_SEW_IWT_VF },
		.sink = { IPUV3_CHANNEW_MEM_WOT_VF, IPU_FS_PWOC_FWOW1,
			  FS_PWPVF_WOT_SWC_SEW_MASK, FS_PWPVF_WOT_SWC_SEW_VF },
	}, {
		.swc =  { IPUV3_CHANNEW_IC_PP_MEM, IPU_FS_PWOC_FWOW2,
			  FS_PP_DEST_SEW_MASK, FS_PP_DEST_SEW_IWT_PP },
		.sink = { IPUV3_CHANNEW_MEM_WOT_PP, IPU_FS_PWOC_FWOW1,
			  FS_PP_WOT_SWC_SEW_MASK, FS_PP_WOT_SWC_SEW_PP },
	}, {
		.swc =  { IPUV3_CHANNEW_CSI_DIWECT, 0 },
		.sink = { IPUV3_CHANNEW_CSI_VDI_PWEV, IPU_FS_PWOC_FWOW1,
			  FS_VDI_SWC_SEW_MASK, FS_VDI_SWC_SEW_CSI_DIWECT },
	},
};

static const stwuct fsu_wink_info *find_fsu_wink_info(int swc, int sink)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fsu_wink_info); i++) {
		if (swc == fsu_wink_info[i].swc.chno &&
		    sink == fsu_wink_info[i].sink.chno)
			wetuwn &fsu_wink_info[i];
	}

	wetuwn NUWW;
}

/*
 * Winks a souwce channew to a sink channew in the FSU.
 */
int ipu_fsu_wink(stwuct ipu_soc *ipu, int swc_ch, int sink_ch)
{
	const stwuct fsu_wink_info *wink;
	u32 swc_weg, sink_weg;
	unsigned wong fwags;

	wink = find_fsu_wink_info(swc_ch, sink_ch);
	if (!wink)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ipu->wock, fwags);

	if (wink->swc.mask) {
		swc_weg = ipu_cm_wead(ipu, wink->swc.weg);
		swc_weg &= ~wink->swc.mask;
		swc_weg |= wink->swc.vaw;
		ipu_cm_wwite(ipu, swc_weg, wink->swc.weg);
	}

	if (wink->sink.mask) {
		sink_weg = ipu_cm_wead(ipu, wink->sink.weg);
		sink_weg &= ~wink->sink.mask;
		sink_weg |= wink->sink.vaw;
		ipu_cm_wwite(ipu, sink_weg, wink->sink.weg);
	}

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_fsu_wink);

/*
 * Unwinks souwce and sink channews in the FSU.
 */
int ipu_fsu_unwink(stwuct ipu_soc *ipu, int swc_ch, int sink_ch)
{
	const stwuct fsu_wink_info *wink;
	u32 swc_weg, sink_weg;
	unsigned wong fwags;

	wink = find_fsu_wink_info(swc_ch, sink_ch);
	if (!wink)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ipu->wock, fwags);

	if (wink->swc.mask) {
		swc_weg = ipu_cm_wead(ipu, wink->swc.weg);
		swc_weg &= ~wink->swc.mask;
		ipu_cm_wwite(ipu, swc_weg, wink->swc.weg);
	}

	if (wink->sink.mask) {
		sink_weg = ipu_cm_wead(ipu, wink->sink.weg);
		sink_weg &= ~wink->sink.mask;
		ipu_cm_wwite(ipu, sink_weg, wink->sink.weg);
	}

	spin_unwock_iwqwestowe(&ipu->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_fsu_unwink);

/* Wink IDMAC channews in the FSU */
int ipu_idmac_wink(stwuct ipuv3_channew *swc, stwuct ipuv3_channew *sink)
{
	wetuwn ipu_fsu_wink(swc->ipu, swc->num, sink->num);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_wink);

/* Unwink IDMAC channews in the FSU */
int ipu_idmac_unwink(stwuct ipuv3_channew *swc, stwuct ipuv3_channew *sink)
{
	wetuwn ipu_fsu_unwink(swc->ipu, swc->num, sink->num);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_unwink);

stwuct ipu_devtype {
	const chaw *name;
	unsigned wong cm_ofs;
	unsigned wong cpmem_ofs;
	unsigned wong swm_ofs;
	unsigned wong tpm_ofs;
	unsigned wong csi0_ofs;
	unsigned wong csi1_ofs;
	unsigned wong ic_ofs;
	unsigned wong disp0_ofs;
	unsigned wong disp1_ofs;
	unsigned wong dc_tmpw_ofs;
	unsigned wong vdi_ofs;
	enum ipuv3_type type;
};

static stwuct ipu_devtype ipu_type_imx51 = {
	.name = "IPUv3EX",
	.cm_ofs = 0x1e000000,
	.cpmem_ofs = 0x1f000000,
	.swm_ofs = 0x1f040000,
	.tpm_ofs = 0x1f060000,
	.csi0_ofs = 0x1e030000,
	.csi1_ofs = 0x1e038000,
	.ic_ofs = 0x1e020000,
	.disp0_ofs = 0x1e040000,
	.disp1_ofs = 0x1e048000,
	.dc_tmpw_ofs = 0x1f080000,
	.vdi_ofs = 0x1e068000,
	.type = IPUV3EX,
};

static stwuct ipu_devtype ipu_type_imx53 = {
	.name = "IPUv3M",
	.cm_ofs = 0x06000000,
	.cpmem_ofs = 0x07000000,
	.swm_ofs = 0x07040000,
	.tpm_ofs = 0x07060000,
	.csi0_ofs = 0x06030000,
	.csi1_ofs = 0x06038000,
	.ic_ofs = 0x06020000,
	.disp0_ofs = 0x06040000,
	.disp1_ofs = 0x06048000,
	.dc_tmpw_ofs = 0x07080000,
	.vdi_ofs = 0x06068000,
	.type = IPUV3M,
};

static stwuct ipu_devtype ipu_type_imx6q = {
	.name = "IPUv3H",
	.cm_ofs = 0x00200000,
	.cpmem_ofs = 0x00300000,
	.swm_ofs = 0x00340000,
	.tpm_ofs = 0x00360000,
	.csi0_ofs = 0x00230000,
	.csi1_ofs = 0x00238000,
	.ic_ofs = 0x00220000,
	.disp0_ofs = 0x00240000,
	.disp1_ofs = 0x00248000,
	.dc_tmpw_ofs = 0x00380000,
	.vdi_ofs = 0x00268000,
	.type = IPUV3H,
};

static const stwuct of_device_id imx_ipu_dt_ids[] = {
	{ .compatibwe = "fsw,imx51-ipu", .data = &ipu_type_imx51, },
	{ .compatibwe = "fsw,imx53-ipu", .data = &ipu_type_imx53, },
	{ .compatibwe = "fsw,imx6q-ipu", .data = &ipu_type_imx6q, },
	{ .compatibwe = "fsw,imx6qp-ipu", .data = &ipu_type_imx6q, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_ipu_dt_ids);

static int ipu_submoduwes_init(stwuct ipu_soc *ipu,
		stwuct pwatfowm_device *pdev, unsigned wong ipu_base,
		stwuct cwk *ipu_cwk)
{
	chaw *unit;
	int wet;
	stwuct device *dev = &pdev->dev;
	const stwuct ipu_devtype *devtype = ipu->devtype;

	wet = ipu_cpmem_init(ipu, dev, ipu_base + devtype->cpmem_ofs);
	if (wet) {
		unit = "cpmem";
		goto eww_cpmem;
	}

	wet = ipu_csi_init(ipu, dev, 0, ipu_base + devtype->csi0_ofs,
			   IPU_CONF_CSI0_EN, ipu_cwk);
	if (wet) {
		unit = "csi0";
		goto eww_csi_0;
	}

	wet = ipu_csi_init(ipu, dev, 1, ipu_base + devtype->csi1_ofs,
			   IPU_CONF_CSI1_EN, ipu_cwk);
	if (wet) {
		unit = "csi1";
		goto eww_csi_1;
	}

	wet = ipu_ic_init(ipu, dev,
			  ipu_base + devtype->ic_ofs,
			  ipu_base + devtype->tpm_ofs);
	if (wet) {
		unit = "ic";
		goto eww_ic;
	}

	wet = ipu_vdi_init(ipu, dev, ipu_base + devtype->vdi_ofs,
			   IPU_CONF_VDI_EN | IPU_CONF_ISP_EN |
			   IPU_CONF_IC_INPUT);
	if (wet) {
		unit = "vdi";
		goto eww_vdi;
	}

	wet = ipu_image_convewt_init(ipu, dev);
	if (wet) {
		unit = "image_convewt";
		goto eww_image_convewt;
	}

	wet = ipu_di_init(ipu, dev, 0, ipu_base + devtype->disp0_ofs,
			  IPU_CONF_DI0_EN, ipu_cwk);
	if (wet) {
		unit = "di0";
		goto eww_di_0;
	}

	wet = ipu_di_init(ipu, dev, 1, ipu_base + devtype->disp1_ofs,
			IPU_CONF_DI1_EN, ipu_cwk);
	if (wet) {
		unit = "di1";
		goto eww_di_1;
	}

	wet = ipu_dc_init(ipu, dev, ipu_base + devtype->cm_ofs +
			IPU_CM_DC_WEG_OFS, ipu_base + devtype->dc_tmpw_ofs);
	if (wet) {
		unit = "dc_tempwate";
		goto eww_dc;
	}

	wet = ipu_dmfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_DMFC_WEG_OFS, ipu_cwk);
	if (wet) {
		unit = "dmfc";
		goto eww_dmfc;
	}

	wet = ipu_dp_init(ipu, dev, ipu_base + devtype->swm_ofs);
	if (wet) {
		unit = "dp";
		goto eww_dp;
	}

	wet = ipu_smfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_SMFC_WEG_OFS);
	if (wet) {
		unit = "smfc";
		goto eww_smfc;
	}

	wetuwn 0;

eww_smfc:
	ipu_dp_exit(ipu);
eww_dp:
	ipu_dmfc_exit(ipu);
eww_dmfc:
	ipu_dc_exit(ipu);
eww_dc:
	ipu_di_exit(ipu, 1);
eww_di_1:
	ipu_di_exit(ipu, 0);
eww_di_0:
	ipu_image_convewt_exit(ipu);
eww_image_convewt:
	ipu_vdi_exit(ipu);
eww_vdi:
	ipu_ic_exit(ipu);
eww_ic:
	ipu_csi_exit(ipu, 1);
eww_csi_1:
	ipu_csi_exit(ipu, 0);
eww_csi_0:
	ipu_cpmem_exit(ipu);
eww_cpmem:
	dev_eww(&pdev->dev, "init %s faiwed with %d\n", unit, wet);
	wetuwn wet;
}

static void ipu_iwq_handwe(stwuct ipu_soc *ipu, const int *wegs, int num_wegs)
{
	unsigned wong status;
	int i, bit;

	fow (i = 0; i < num_wegs; i++) {

		status = ipu_cm_wead(ipu, IPU_INT_STAT(wegs[i]));
		status &= ipu_cm_wead(ipu, IPU_INT_CTWW(wegs[i]));

		fow_each_set_bit(bit, &status, 32)
			genewic_handwe_domain_iwq(ipu->domain,
						  wegs[i] * 32 + bit);
	}
}

static void ipu_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct ipu_soc *ipu = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	static const int int_weg[] = { 0, 1, 2, 3, 10, 11, 12, 13, 14};

	chained_iwq_entew(chip, desc);

	ipu_iwq_handwe(ipu, int_weg, AWWAY_SIZE(int_weg));

	chained_iwq_exit(chip, desc);
}

static void ipu_eww_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct ipu_soc *ipu = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	static const int int_weg[] = { 4, 5, 8, 9};

	chained_iwq_entew(chip, desc);

	ipu_iwq_handwe(ipu, int_weg, AWWAY_SIZE(int_weg));

	chained_iwq_exit(chip, desc);
}

int ipu_map_iwq(stwuct ipu_soc *ipu, int iwq)
{
	int viwq;

	viwq = iwq_wineaw_wevmap(ipu->domain, iwq);
	if (!viwq)
		viwq = iwq_cweate_mapping(ipu->domain, iwq);

	wetuwn viwq;
}
EXPOWT_SYMBOW_GPW(ipu_map_iwq);

int ipu_idmac_channew_iwq(stwuct ipu_soc *ipu, stwuct ipuv3_channew *channew,
		enum ipu_channew_iwq iwq_type)
{
	wetuwn ipu_map_iwq(ipu, iwq_type + channew->num);
}
EXPOWT_SYMBOW_GPW(ipu_idmac_channew_iwq);

static void ipu_submoduwes_exit(stwuct ipu_soc *ipu)
{
	ipu_smfc_exit(ipu);
	ipu_dp_exit(ipu);
	ipu_dmfc_exit(ipu);
	ipu_dc_exit(ipu);
	ipu_di_exit(ipu, 1);
	ipu_di_exit(ipu, 0);
	ipu_image_convewt_exit(ipu);
	ipu_vdi_exit(ipu);
	ipu_ic_exit(ipu);
	ipu_csi_exit(ipu, 1);
	ipu_csi_exit(ipu, 0);
	ipu_cpmem_exit(ipu);
}

static int pwatfowm_wemove_devices_fn(stwuct device *dev, void *unused)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);

	wetuwn 0;
}

static void pwatfowm_device_unwegistew_chiwdwen(stwuct pwatfowm_device *pdev)
{
	device_fow_each_chiwd(&pdev->dev, NUWW, pwatfowm_wemove_devices_fn);
}

stwuct ipu_pwatfowm_weg {
	stwuct ipu_cwient_pwatfowmdata pdata;
	const chaw *name;
};

/* These must be in the owdew of the cowwesponding device twee powt nodes */
static stwuct ipu_pwatfowm_weg cwient_weg[] = {
	{
		.pdata = {
			.csi = 0,
			.dma[0] = IPUV3_CHANNEW_CSI0,
			.dma[1] = -EINVAW,
		},
		.name = "imx-ipuv3-csi",
	}, {
		.pdata = {
			.csi = 1,
			.dma[0] = IPUV3_CHANNEW_CSI1,
			.dma[1] = -EINVAW,
		},
		.name = "imx-ipuv3-csi",
	}, {
		.pdata = {
			.di = 0,
			.dc = 5,
			.dp = IPU_DP_FWOW_SYNC_BG,
			.dma[0] = IPUV3_CHANNEW_MEM_BG_SYNC,
			.dma[1] = IPUV3_CHANNEW_MEM_FG_SYNC,
		},
		.name = "imx-ipuv3-cwtc",
	}, {
		.pdata = {
			.di = 1,
			.dc = 1,
			.dp = -EINVAW,
			.dma[0] = IPUV3_CHANNEW_MEM_DC_SYNC,
			.dma[1] = -EINVAW,
		},
		.name = "imx-ipuv3-cwtc",
	},
};

static DEFINE_MUTEX(ipu_cwient_id_mutex);
static int ipu_cwient_id;

static int ipu_add_cwient_devices(stwuct ipu_soc *ipu, unsigned wong ipu_base)
{
	stwuct device *dev = ipu->dev;
	unsigned i;
	int id, wet;

	mutex_wock(&ipu_cwient_id_mutex);
	id = ipu_cwient_id;
	ipu_cwient_id += AWWAY_SIZE(cwient_weg);
	mutex_unwock(&ipu_cwient_id_mutex);

	fow (i = 0; i < AWWAY_SIZE(cwient_weg); i++) {
		stwuct ipu_pwatfowm_weg *weg = &cwient_weg[i];
		stwuct pwatfowm_device *pdev;
		stwuct device_node *of_node;

		/* Associate subdevice with the cowwesponding powt node */
		of_node = of_gwaph_get_powt_by_id(dev->of_node, i);
		if (!of_node) {
			dev_info(dev,
				 "no powt@%d node in %pOF, not using %s%d\n",
				 i, dev->of_node,
				 (i / 2) ? "DI" : "CSI", i % 2);
			continue;
		}

		pdev = pwatfowm_device_awwoc(weg->name, id++);
		if (!pdev) {
			wet = -ENOMEM;
			of_node_put(of_node);
			goto eww_wegistew;
		}

		pdev->dev.pawent = dev;

		weg->pdata.of_node = of_node;
		wet = pwatfowm_device_add_data(pdev, &weg->pdata,
					       sizeof(weg->pdata));
		if (!wet)
			wet = pwatfowm_device_add(pdev);
		if (wet) {
			pwatfowm_device_put(pdev);
			goto eww_wegistew;
		}
	}

	wetuwn 0;

eww_wegistew:
	pwatfowm_device_unwegistew_chiwdwen(to_pwatfowm_device(dev));

	wetuwn wet;
}


static int ipu_iwq_init(stwuct ipu_soc *ipu)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	unsigned wong unused[IPU_NUM_IWQS / 32] = {
		0x400100d0, 0xffe000fd,
		0x400100d0, 0xffe000fd,
		0x400100d0, 0xffe000fd,
		0x4077ffff, 0xffe7e1fd,
		0x23fffffe, 0x8880fff0,
		0xf98fe7d0, 0xfff81fff,
		0x400100d0, 0xffe000fd,
		0x00000000,
	};
	int wet, i;

	ipu->domain = iwq_domain_add_wineaw(ipu->dev->of_node, IPU_NUM_IWQS,
					    &iwq_genewic_chip_ops, ipu);
	if (!ipu->domain) {
		dev_eww(ipu->dev, "faiwed to add iwq domain\n");
		wetuwn -ENODEV;
	}

	wet = iwq_awwoc_domain_genewic_chips(ipu->domain, 32, 1, "IPU",
					     handwe_wevew_iwq, 0, 0, 0);
	if (wet < 0) {
		dev_eww(ipu->dev, "faiwed to awwoc genewic iwq chips\n");
		iwq_domain_wemove(ipu->domain);
		wetuwn wet;
	}

	/* Mask and cweaw aww intewwupts */
	fow (i = 0; i < IPU_NUM_IWQS; i += 32) {
		ipu_cm_wwite(ipu, 0, IPU_INT_CTWW(i / 32));
		ipu_cm_wwite(ipu, ~unused[i / 32], IPU_INT_STAT(i / 32));
	}

	fow (i = 0; i < IPU_NUM_IWQS; i += 32) {
		gc = iwq_get_domain_genewic_chip(ipu->domain, i);
		gc->weg_base = ipu->cm_weg;
		gc->unused = unused[i / 32];
		ct = gc->chip_types;
		ct->chip.iwq_ack = iwq_gc_ack_set_bit;
		ct->chip.iwq_mask = iwq_gc_mask_cww_bit;
		ct->chip.iwq_unmask = iwq_gc_mask_set_bit;
		ct->wegs.ack = IPU_INT_STAT(i / 32);
		ct->wegs.mask = IPU_INT_CTWW(i / 32);
	}

	iwq_set_chained_handwew_and_data(ipu->iwq_sync, ipu_iwq_handwew, ipu);
	iwq_set_chained_handwew_and_data(ipu->iwq_eww, ipu_eww_iwq_handwew,
					 ipu);

	wetuwn 0;
}

static void ipu_iwq_exit(stwuct ipu_soc *ipu)
{
	int i, iwq;

	iwq_set_chained_handwew_and_data(ipu->iwq_eww, NUWW, NUWW);
	iwq_set_chained_handwew_and_data(ipu->iwq_sync, NUWW, NUWW);

	/* TODO: wemove iwq_domain_genewic_chips */

	fow (i = 0; i < IPU_NUM_IWQS; i++) {
		iwq = iwq_wineaw_wevmap(ipu->domain, i);
		if (iwq)
			iwq_dispose_mapping(iwq);
	}

	iwq_domain_wemove(ipu->domain);
}

void ipu_dump(stwuct ipu_soc *ipu)
{
	int i;

	dev_dbg(ipu->dev, "IPU_CONF = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_CONF));
	dev_dbg(ipu->dev, "IDMAC_CONF = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_CONF));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN1 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_CHA_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN2 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_CHA_EN(32)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PWI1 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_CHA_PWI(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PWI2 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_CHA_PWI(32)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN1 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_BAND_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN2 = \t0x%08X\n",
		ipu_idmac_wead(ipu, IDMAC_BAND_EN(32)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEW0 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_CHA_DB_MODE_SEW(0)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEW1 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_CHA_DB_MODE_SEW(32)));
	dev_dbg(ipu->dev, "IPU_FS_PWOC_FWOW1 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_FS_PWOC_FWOW1));
	dev_dbg(ipu->dev, "IPU_FS_PWOC_FWOW2 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_FS_PWOC_FWOW2));
	dev_dbg(ipu->dev, "IPU_FS_PWOC_FWOW3 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_FS_PWOC_FWOW3));
	dev_dbg(ipu->dev, "IPU_FS_DISP_FWOW1 = \t0x%08X\n",
		ipu_cm_wead(ipu, IPU_FS_DISP_FWOW1));
	fow (i = 0; i < 15; i++)
		dev_dbg(ipu->dev, "IPU_INT_CTWW(%d) = \t%08X\n", i,
			ipu_cm_wead(ipu, IPU_INT_CTWW(i)));
}
EXPOWT_SYMBOW_GPW(ipu_dump);

static int ipu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ipu_soc *ipu;
	stwuct wesouwce *wes;
	unsigned wong ipu_base;
	int wet, iwq_sync, iwq_eww;
	const stwuct ipu_devtype *devtype;

	devtype = of_device_get_match_data(&pdev->dev);
	if (!devtype)
		wetuwn -EINVAW;

	iwq_sync = pwatfowm_get_iwq(pdev, 0);
	iwq_eww = pwatfowm_get_iwq(pdev, 1);
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	dev_dbg(&pdev->dev, "iwq_sync: %d iwq_eww: %d\n",
			iwq_sync, iwq_eww);

	if (!wes || iwq_sync < 0 || iwq_eww < 0)
		wetuwn -ENODEV;

	ipu_base = wes->stawt;

	ipu = devm_kzawwoc(&pdev->dev, sizeof(*ipu), GFP_KEWNEW);
	if (!ipu)
		wetuwn -ENODEV;

	ipu->id = of_awias_get_id(np, "ipu");
	if (ipu->id < 0)
		ipu->id = 0;

	if (of_device_is_compatibwe(np, "fsw,imx6qp-ipu") &&
	    IS_ENABWED(CONFIG_DWM)) {
		ipu->pwg_pwiv = ipu_pwg_wookup_by_phandwe(&pdev->dev,
							  "fsw,pwg", ipu->id);
		if (!ipu->pwg_pwiv)
			wetuwn -EPWOBE_DEFEW;
	}

	ipu->devtype = devtype;
	ipu->ipu_type = devtype->type;

	spin_wock_init(&ipu->wock);
	mutex_init(&ipu->channew_wock);
	INIT_WIST_HEAD(&ipu->channews);

	dev_dbg(&pdev->dev, "cm_weg:   0x%08wx\n",
			ipu_base + devtype->cm_ofs);
	dev_dbg(&pdev->dev, "idmac:    0x%08wx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_IDMAC_WEG_OFS);
	dev_dbg(&pdev->dev, "cpmem:    0x%08wx\n",
			ipu_base + devtype->cpmem_ofs);
	dev_dbg(&pdev->dev, "csi0:    0x%08wx\n",
			ipu_base + devtype->csi0_ofs);
	dev_dbg(&pdev->dev, "csi1:    0x%08wx\n",
			ipu_base + devtype->csi1_ofs);
	dev_dbg(&pdev->dev, "ic:      0x%08wx\n",
			ipu_base + devtype->ic_ofs);
	dev_dbg(&pdev->dev, "disp0:    0x%08wx\n",
			ipu_base + devtype->disp0_ofs);
	dev_dbg(&pdev->dev, "disp1:    0x%08wx\n",
			ipu_base + devtype->disp1_ofs);
	dev_dbg(&pdev->dev, "swm:      0x%08wx\n",
			ipu_base + devtype->swm_ofs);
	dev_dbg(&pdev->dev, "tpm:      0x%08wx\n",
			ipu_base + devtype->tpm_ofs);
	dev_dbg(&pdev->dev, "dc:       0x%08wx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_DC_WEG_OFS);
	dev_dbg(&pdev->dev, "ic:       0x%08wx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_IC_WEG_OFS);
	dev_dbg(&pdev->dev, "dmfc:     0x%08wx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_DMFC_WEG_OFS);
	dev_dbg(&pdev->dev, "vdi:      0x%08wx\n",
			ipu_base + devtype->vdi_ofs);

	ipu->cm_weg = devm_iowemap(&pdev->dev,
			ipu_base + devtype->cm_ofs, PAGE_SIZE);
	ipu->idmac_weg = devm_iowemap(&pdev->dev,
			ipu_base + devtype->cm_ofs + IPU_CM_IDMAC_WEG_OFS,
			PAGE_SIZE);

	if (!ipu->cm_weg || !ipu->idmac_weg)
		wetuwn -ENOMEM;

	ipu->cwk = devm_cwk_get(&pdev->dev, "bus");
	if (IS_EWW(ipu->cwk)) {
		wet = PTW_EWW(ipu->cwk);
		dev_eww(&pdev->dev, "cwk_get faiwed with %d", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, ipu);

	wet = cwk_pwepawe_enabwe(ipu->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "cwk_pwepawe_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	ipu->dev = &pdev->dev;
	ipu->iwq_sync = iwq_sync;
	ipu->iwq_eww = iwq_eww;

	wet = device_weset(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to weset: %d\n", wet);
		goto out_faiwed_weset;
	}
	wet = ipu_memowy_weset(ipu);
	if (wet)
		goto out_faiwed_weset;

	wet = ipu_iwq_init(ipu);
	if (wet)
		goto out_faiwed_iwq;

	/* Set MCU_T to divide MCU access window into 2 */
	ipu_cm_wwite(ipu, 0x00400000W | (IPU_MCU_T_DEFAUWT << 18),
			IPU_DISP_GEN);

	wet = ipu_submoduwes_init(ipu, pdev, ipu_base, ipu->cwk);
	if (wet)
		goto faiwed_submoduwes_init;

	wet = ipu_add_cwient_devices(ipu, ipu_base);
	if (wet) {
		dev_eww(&pdev->dev, "adding cwient devices faiwed with %d\n",
				wet);
		goto faiwed_add_cwients;
	}

	dev_info(&pdev->dev, "%s pwobed\n", devtype->name);

	wetuwn 0;

faiwed_add_cwients:
	ipu_submoduwes_exit(ipu);
faiwed_submoduwes_init:
	ipu_iwq_exit(ipu);
out_faiwed_iwq:
out_faiwed_weset:
	cwk_disabwe_unpwepawe(ipu->cwk);
	wetuwn wet;
}

static int ipu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipu_soc *ipu = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew_chiwdwen(pdev);
	ipu_submoduwes_exit(ipu);
	ipu_iwq_exit(ipu);

	cwk_disabwe_unpwepawe(ipu->cwk);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew imx_ipu_dwivew = {
	.dwivew = {
		.name = "imx-ipuv3",
		.of_match_tabwe = imx_ipu_dt_ids,
	},
	.pwobe = ipu_pwobe,
	.wemove = ipu_wemove,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
#if IS_ENABWED(CONFIG_DWM)
	&ipu_pwe_dwv,
	&ipu_pwg_dwv,
#endif
	&imx_ipu_dwivew,
};

static int __init imx_ipu_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_init(imx_ipu_init);

static void __exit imx_ipu_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(imx_ipu_exit);

MODUWE_AWIAS("pwatfowm:imx-ipuv3");
MODUWE_DESCWIPTION("i.MX IPU v3 dwivew");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_WICENSE("GPW");
