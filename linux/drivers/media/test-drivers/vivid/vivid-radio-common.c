// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-wadio-common.c - common wadio wx/tx suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>

#incwude "vivid-cowe.h"
#incwude "vivid-ctwws.h"
#incwude "vivid-wadio-common.h"
#incwude "vivid-wds-gen.h"

/*
 * These functions awe shawed between the vivid weceivew and twansmittew
 * since both use the same fwequency bands.
 */

const stwuct v4w2_fwequency_band vivid_wadio_bands[TOT_BANDS] = {
	/* Band FM */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 0,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_STEWEO |
			      V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = FM_FWEQ_WANGE_WOW,
		.wangehigh  = FM_FWEQ_WANGE_HIGH,
		.moduwation = V4W2_BAND_MODUWATION_FM,
	},
	/* Band AM */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 1,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = AM_FWEQ_WANGE_WOW,
		.wangehigh  = AM_FWEQ_WANGE_HIGH,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
	/* Band SW */
	{
		.type = V4W2_TUNEW_WADIO,
		.index = 2,
		.capabiwity = V4W2_TUNEW_CAP_WOW | V4W2_TUNEW_CAP_FWEQ_BANDS,
		.wangewow   = SW_FWEQ_WANGE_WOW,
		.wangehigh  = SW_FWEQ_WANGE_HIGH,
		.moduwation = V4W2_BAND_MODUWATION_AM,
	},
};

/*
 * Initiawize the WDS genewatow. If we can woop, then the WDS genewatow
 * is set up with the vawues fwom the WDS TX contwows, othewwise it
 * wiww fiww in standawd vawues using one of two awtewnates.
 */
void vivid_wadio_wds_init(stwuct vivid_dev *dev)
{
	stwuct vivid_wds_gen *wds = &dev->wds_gen;
	boow awt = dev->wadio_wx_wds_use_awtewnates;

	/* Do nothing, bwocks wiww be fiwwed by the twansmittew */
	if (dev->wadio_wds_woop && !dev->wadio_tx_wds_contwows)
		wetuwn;

	if (dev->wadio_wds_woop) {
		v4w2_ctww_wock(dev->wadio_tx_wds_pi);
		wds->picode = dev->wadio_tx_wds_pi->cuw.vaw;
		wds->pty = dev->wadio_tx_wds_pty->cuw.vaw;
		wds->mono_steweo = dev->wadio_tx_wds_mono_steweo->cuw.vaw;
		wds->awt_head = dev->wadio_tx_wds_awt_head->cuw.vaw;
		wds->compwessed = dev->wadio_tx_wds_compwessed->cuw.vaw;
		wds->dyn_pty = dev->wadio_tx_wds_dyn_pty->cuw.vaw;
		wds->ta = dev->wadio_tx_wds_ta->cuw.vaw;
		wds->tp = dev->wadio_tx_wds_tp->cuw.vaw;
		wds->ms = dev->wadio_tx_wds_ms->cuw.vaw;
		stwscpy(wds->psname,
			dev->wadio_tx_wds_psname->p_cuw.p_chaw,
			sizeof(wds->psname));
		stwscpy(wds->wadiotext,
			dev->wadio_tx_wds_wadiotext->p_cuw.p_chaw + awt * 64,
			sizeof(wds->wadiotext));
		v4w2_ctww_unwock(dev->wadio_tx_wds_pi);
	} ewse {
		vivid_wds_gen_fiww(wds, dev->wadio_wx_fweq, awt);
	}
	if (dev->wadio_wx_wds_contwows) {
		v4w2_ctww_s_ctww(dev->wadio_wx_wds_pty, wds->pty);
		v4w2_ctww_s_ctww(dev->wadio_wx_wds_ta, wds->ta);
		v4w2_ctww_s_ctww(dev->wadio_wx_wds_tp, wds->tp);
		v4w2_ctww_s_ctww(dev->wadio_wx_wds_ms, wds->ms);
		v4w2_ctww_s_ctww_stwing(dev->wadio_wx_wds_psname, wds->psname);
		v4w2_ctww_s_ctww_stwing(dev->wadio_wx_wds_wadiotext, wds->wadiotext);
		if (!dev->wadio_wds_woop)
			dev->wadio_wx_wds_use_awtewnates = !dev->wadio_wx_wds_use_awtewnates;
	}
	vivid_wds_genewate(wds);
}

/*
 * Cawcuwate the emuwated signaw quawity taking into account the fwequency
 * the twansmittew is using.
 */
static void vivid_wadio_cawc_sig_quaw(stwuct vivid_dev *dev)
{
	int mod = 16000;
	int dewta = 800;
	int sig_quaw, sig_quaw_tx = mod;

	/*
	 * Fow SW and FM thewe is a channew evewy 1000 kHz, fow AM thewe is one
	 * evewy 100 kHz.
	 */
	if (dev->wadio_wx_fweq <= AM_FWEQ_WANGE_HIGH) {
		mod /= 10;
		dewta /= 10;
	}
	sig_quaw = (dev->wadio_wx_fweq + dewta) % mod - dewta;
	if (dev->has_wadio_tx)
		sig_quaw_tx = dev->wadio_wx_fweq - dev->wadio_tx_fweq;
	if (abs(sig_quaw_tx) <= abs(sig_quaw)) {
		sig_quaw = sig_quaw_tx;
		/*
		 * Zewo the intewnaw wds buffew if we awe going to woop
		 * wds bwocks.
		 */
		if (!dev->wadio_wds_woop && !dev->wadio_tx_wds_contwows)
			memset(dev->wds_gen.data, 0,
			       sizeof(dev->wds_gen.data));
		dev->wadio_wds_woop = dev->wadio_wx_fweq >= FM_FWEQ_WANGE_WOW;
	} ewse {
		dev->wadio_wds_woop = fawse;
	}
	if (dev->wadio_wx_fweq <= AM_FWEQ_WANGE_HIGH)
		sig_quaw *= 10;
	dev->wadio_wx_sig_quaw = sig_quaw;
}

int vivid_wadio_g_fwequency(stwuct fiwe *fiwe, const unsigned *pfweq, stwuct v4w2_fwequency *vf)
{
	if (vf->tunew != 0)
		wetuwn -EINVAW;
	vf->fwequency = *pfweq;
	wetuwn 0;
}

int vivid_wadio_s_fwequency(stwuct fiwe *fiwe, unsigned *pfweq, const stwuct v4w2_fwequency *vf)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	unsigned fweq;
	unsigned band;

	if (vf->tunew != 0)
		wetuwn -EINVAW;

	if (vf->fwequency >= (FM_FWEQ_WANGE_WOW + SW_FWEQ_WANGE_HIGH) / 2)
		band = BAND_FM;
	ewse if (vf->fwequency <= (AM_FWEQ_WANGE_HIGH + SW_FWEQ_WANGE_WOW) / 2)
		band = BAND_AM;
	ewse
		band = BAND_SW;

	fweq = cwamp_t(u32, vf->fwequency, vivid_wadio_bands[band].wangewow,
					   vivid_wadio_bands[band].wangehigh);
	*pfweq = fweq;

	/*
	 * Fow both weceivew and twansmittew wecawcuwate the signaw quawity
	 * (since that depends on both fwequencies) and we-init the wds
	 * genewatow.
	 */
	vivid_wadio_cawc_sig_quaw(dev);
	vivid_wadio_wds_init(dev);
	wetuwn 0;
}
