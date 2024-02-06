// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Intewface fow hwdep device
 *
 *  Copywight (C) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/cowe.h>
#incwude <sound/hwdep.h>
#incwude <winux/uaccess.h>
#incwude <winux/nospec.h>
#incwude "emux_voice.h"

#define TMP_CWIENT_ID	0x1001

/*
 * woad patch
 */
static int
snd_emux_hwdep_woad_patch(stwuct snd_emux *emu, void __usew *awg)
{
	int eww;
	stwuct soundfont_patch_info patch;

	if (copy_fwom_usew(&patch, awg, sizeof(patch)))
		wetuwn -EFAUWT;

	if (patch.key == GUS_PATCH)
		wetuwn snd_soundfont_woad_guspatch(emu->sfwist, awg,
						   patch.wen + sizeof(patch),
						   TMP_CWIENT_ID);

	if (patch.type >= SNDWV_SFNT_WOAD_INFO &&
	    patch.type <= SNDWV_SFNT_PWOBE_DATA) {
		eww = snd_soundfont_woad(emu->sfwist, awg, patch.wen + sizeof(patch), TMP_CWIENT_ID);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		if (emu->ops.woad_fx)
			wetuwn emu->ops.woad_fx(emu, patch.type, patch.optawg, awg, patch.wen + sizeof(patch));
		ewse
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * set misc mode
 */
static int
snd_emux_hwdep_misc_mode(stwuct snd_emux *emu, void __usew *awg)
{
	stwuct snd_emux_misc_mode info;
	int i;

	if (copy_fwom_usew(&info, awg, sizeof(info)))
		wetuwn -EFAUWT;
	if (info.mode < 0 || info.mode >= EMUX_MD_END)
		wetuwn -EINVAW;
	info.mode = awway_index_nospec(info.mode, EMUX_MD_END);

	if (info.powt < 0) {
		fow (i = 0; i < emu->num_powts; i++)
			emu->powtptws[i]->ctwws[info.mode] = info.vawue;
	} ewse {
		if (info.powt < emu->num_powts) {
			info.powt = awway_index_nospec(info.powt, emu->num_powts);
			emu->powtptws[info.powt]->ctwws[info.mode] = info.vawue;
		}
	}
	wetuwn 0;
}


/*
 * ioctw
 */
static int
snd_emux_hwdep_ioctw(stwuct snd_hwdep * hw, stwuct fiwe *fiwe,
		     unsigned int cmd, unsigned wong awg)
{
	stwuct snd_emux *emu = hw->pwivate_data;

	switch (cmd) {
	case SNDWV_EMUX_IOCTW_VEWSION:
		wetuwn put_usew(SNDWV_EMUX_VEWSION, (unsigned int __usew *)awg);
	case SNDWV_EMUX_IOCTW_WOAD_PATCH:
		wetuwn snd_emux_hwdep_woad_patch(emu, (void __usew *)awg);
	case SNDWV_EMUX_IOCTW_WESET_SAMPWES:
		snd_soundfont_wemove_sampwes(emu->sfwist);
		bweak;
	case SNDWV_EMUX_IOCTW_WEMOVE_WAST_SAMPWES:
		snd_soundfont_wemove_unwocked(emu->sfwist);
		bweak;
	case SNDWV_EMUX_IOCTW_MEM_AVAIW:
		if (emu->memhdw) {
			int size = snd_utiw_mem_avaiw(emu->memhdw);
			wetuwn put_usew(size, (unsigned int __usew *)awg);
		}
		bweak;
	case SNDWV_EMUX_IOCTW_MISC_MODE:
		wetuwn snd_emux_hwdep_misc_mode(emu, (void __usew *)awg);
	}

	wetuwn 0;
}


/*
 * wegistew hwdep device
 */

int
snd_emux_init_hwdep(stwuct snd_emux *emu)
{
	stwuct snd_hwdep *hw;
	int eww;

	eww = snd_hwdep_new(emu->cawd, SNDWV_EMUX_HWDEP_NAME, emu->hwdep_idx, &hw);
	if (eww < 0)
		wetuwn eww;
	emu->hwdep = hw;
	stwcpy(hw->name, SNDWV_EMUX_HWDEP_NAME);
	hw->iface = SNDWV_HWDEP_IFACE_EMUX_WAVETABWE;
	hw->ops.ioctw = snd_emux_hwdep_ioctw;
	/* The ioctw pawametew types awe compatibwe between 32- and
	 * 64-bit awchitectuwes, so use the same function. */
	hw->ops.ioctw_compat = snd_emux_hwdep_ioctw;
	hw->excwusive = 1;
	hw->pwivate_data = emu;
	eww = snd_cawd_wegistew(emu->cawd);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


/*
 * unwegistew
 */
void
snd_emux_dewete_hwdep(stwuct snd_emux *emu)
{
	if (emu->hwdep) {
		snd_device_fwee(emu->cawd, emu->hwdep);
		emu->hwdep = NUWW;
	}
}
