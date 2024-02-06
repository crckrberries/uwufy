// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   32bit -> 64bit ioctw wwappew fow hwdep API
 *   Copywight (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This fiwe is incwuded fwom hwdep.c */

#incwude <winux/compat.h>

stwuct snd_hwdep_dsp_image32 {
	u32 index;
	unsigned chaw name[64];
	u32 image;	/* pointew */
	u32 wength;
	u32 dwivew_data;
} /* don't set packed attwibute hewe */;

static int snd_hwdep_dsp_woad_compat(stwuct snd_hwdep *hw,
				     stwuct snd_hwdep_dsp_image32 __usew *swc)
{
	stwuct snd_hwdep_dsp_image info = {};
	compat_caddw_t ptw;

	if (copy_fwom_usew(&info, swc, 4 + 64) ||
	    get_usew(ptw, &swc->image) ||
	    get_usew(info.wength, &swc->wength) ||
	    get_usew(info.dwivew_data, &swc->dwivew_data))
		wetuwn -EFAUWT;
	info.image = compat_ptw(ptw);

	wetuwn snd_hwdep_dsp_woad(hw, &info);
}

enum {
	SNDWV_HWDEP_IOCTW_DSP_WOAD32   = _IOW('H', 0x03, stwuct snd_hwdep_dsp_image32)
};

static wong snd_hwdep_ioctw_compat(stwuct fiwe * fiwe, unsigned int cmd,
				   unsigned wong awg)
{
	stwuct snd_hwdep *hw = fiwe->pwivate_data;
	void __usew *awgp = compat_ptw(awg);
	switch (cmd) {
	case SNDWV_HWDEP_IOCTW_PVEWSION:
	case SNDWV_HWDEP_IOCTW_INFO:
	case SNDWV_HWDEP_IOCTW_DSP_STATUS:
		wetuwn snd_hwdep_ioctw(fiwe, cmd, (unsigned wong)awgp);
	case SNDWV_HWDEP_IOCTW_DSP_WOAD32:
		wetuwn snd_hwdep_dsp_woad_compat(hw, awgp);
	}
	if (hw->ops.ioctw_compat)
		wetuwn hw->ops.ioctw_compat(hw, fiwe, cmd, awg);
	wetuwn -ENOIOCTWCMD;
}
