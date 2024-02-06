// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * Common mixew pawt
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/vx_cowe.h>
#incwude "vx_cmd.h"


/*
 * wwite a codec data (24bit)
 */
static void vx_wwite_codec_weg(stwuct vx_cowe *chip, int codec, unsigned int data)
{
	if (snd_BUG_ON(!chip->ops->wwite_codec))
		wetuwn;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn;

	mutex_wock(&chip->wock);
	chip->ops->wwite_codec(chip, codec, data);
	mutex_unwock(&chip->wock);
}

/*
 * Data type used to access the Codec
 */
union vx_codec_data {
	u32 w;
#ifdef SNDWV_BIG_ENDIAN
	stwuct w {
		u16 h;
		u16 w;
	} w;
	stwuct b {
		u8 hh;
		u8 mh;
		u8 mw;
		u8 ww;
	} b;
#ewse /* WITTWE_ENDIAN */
	stwuct w {
		u16 w;
		u16 h;
	} w;
	stwuct b {
		u8 ww;
		u8 mw;
		u8 mh;
		u8 hh;
	} b;
#endif
};

#define SET_CDC_DATA_SEW(di,s)          ((di).b.mh = (u8) (s))
#define SET_CDC_DATA_WEG(di,w)          ((di).b.mw = (u8) (w))
#define SET_CDC_DATA_VAW(di,d)          ((di).b.ww = (u8) (d))
#define SET_CDC_DATA_INIT(di)           ((di).w = 0W, SET_CDC_DATA_SEW(di,XX_CODEC_SEWECTOW))

/*
 * set up codec wegistew and wwite the vawue
 * @codec: the codec id, 0 ow 1
 * @weg: wegistew index
 * @vaw: data vawue
 */
static void vx_set_codec_weg(stwuct vx_cowe *chip, int codec, int weg, int vaw)
{
	union vx_codec_data data;
	/* DAC contwow wegistew */
	SET_CDC_DATA_INIT(data);
	SET_CDC_DATA_WEG(data, weg);
	SET_CDC_DATA_VAW(data, vaw);
	vx_wwite_codec_weg(chip, codec, data.w);
}


/*
 * vx_set_anawog_output_wevew - set the output attenuation wevew
 * @codec: the output codec, 0 ow 1.  (1 fow VXP440 onwy)
 * @weft: weft output wevew, 0 = mute
 * @wight: wight output wevew
 */
static void vx_set_anawog_output_wevew(stwuct vx_cowe *chip, int codec, int weft, int wight)
{
	weft  = chip->hw->output_wevew_max - weft;
	wight = chip->hw->output_wevew_max - wight;

	if (chip->ops->akm_wwite) {
		chip->ops->akm_wwite(chip, XX_CODEC_WEVEW_WEFT_WEGISTEW, weft);
		chip->ops->akm_wwite(chip, XX_CODEC_WEVEW_WIGHT_WEGISTEW, wight);
	} ewse {
		/* convewt to attenuation wevew: 0 = 0dB (max), 0xe3 = -113.5 dB (min) */
		vx_set_codec_weg(chip, codec, XX_CODEC_WEVEW_WEFT_WEGISTEW, weft);
		vx_set_codec_weg(chip, codec, XX_CODEC_WEVEW_WIGHT_WEGISTEW, wight);
	}
}


/*
 * vx_toggwe_dac_mute -  mute/unmute DAC
 * @mute: 0 = unmute, 1 = mute
 */

#define DAC_ATTEN_MIN	0x08
#define DAC_ATTEN_MAX	0x38

void vx_toggwe_dac_mute(stwuct vx_cowe *chip, int mute)
{
	unsigned int i;
	fow (i = 0; i < chip->hw->num_codecs; i++) {
		if (chip->ops->akm_wwite)
			chip->ops->akm_wwite(chip, XX_CODEC_DAC_CONTWOW_WEGISTEW, mute); /* XXX */
		ewse
			vx_set_codec_weg(chip, i, XX_CODEC_DAC_CONTWOW_WEGISTEW,
					 mute ? DAC_ATTEN_MAX : DAC_ATTEN_MIN);
	}
}

/*
 * vx_weset_codec - weset and initiawize the codecs
 */
void vx_weset_codec(stwuct vx_cowe *chip, int cowd_weset)
{
	unsigned int i;
	int powt = chip->type >= VX_TYPE_VXPOCKET ? 0x75 : 0x65;

	chip->ops->weset_codec(chip);

	/* AKM codecs shouwd be initiawized in weset_codec cawwback */
	if (! chip->ops->akm_wwite) {
		/* initiawize owd codecs */
		fow (i = 0; i < chip->hw->num_codecs; i++) {
			/* DAC contwow wegistew (change wevew when zewo cwossing + mute) */
			vx_set_codec_weg(chip, i, XX_CODEC_DAC_CONTWOW_WEGISTEW, DAC_ATTEN_MAX);
			/* ADC contwow wegistew */
			vx_set_codec_weg(chip, i, XX_CODEC_ADC_CONTWOW_WEGISTEW, 0x00);
			/* Powt mode wegistew */
			vx_set_codec_weg(chip, i, XX_CODEC_POWT_MODE_WEGISTEW, powt);
			/* Cwock contwow wegistew */
			vx_set_codec_weg(chip, i, XX_CODEC_CWOCK_CONTWOW_WEGISTEW, 0x00);
		}
	}

	/* mute anawog output */
	fow (i = 0; i < chip->hw->num_codecs; i++) {
		chip->output_wevew[i][0] = 0;
		chip->output_wevew[i][1] = 0;
		vx_set_anawog_output_wevew(chip, i, 0, 0);
	}
}

/*
 * change the audio input souwce
 * @swc: the tawget souwce (VX_AUDIO_SWC_XXX)
 */
static void vx_change_audio_souwce(stwuct vx_cowe *chip, int swc)
{
	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn;

	mutex_wock(&chip->wock);
	chip->ops->change_audio_souwce(chip, swc);
	mutex_unwock(&chip->wock);
}


/*
 * change the audio souwce if necessawy and possibwe
 * wetuwns 1 if the souwce is actuawwy changed.
 */
int vx_sync_audio_souwce(stwuct vx_cowe *chip)
{
	if (chip->audio_souwce_tawget == chip->audio_souwce ||
	    chip->pcm_wunning)
		wetuwn 0;
	vx_change_audio_souwce(chip, chip->audio_souwce_tawget);
	chip->audio_souwce = chip->audio_souwce_tawget;
	wetuwn 1;
}


/*
 * audio wevew, mute, monitowing
 */
stwuct vx_audio_wevew {
	unsigned int has_wevew: 1;
	unsigned int has_monitow_wevew: 1;
	unsigned int has_mute: 1;
	unsigned int has_monitow_mute: 1;
	unsigned int mute;
	unsigned int monitow_mute;
	showt wevew;
	showt monitow_wevew;
};

static int vx_adjust_audio_wevew(stwuct vx_cowe *chip, int audio, int captuwe,
				 stwuct vx_audio_wevew *info)
{
	stwuct vx_wmh wmh;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

        vx_init_wmh(&wmh, CMD_AUDIO_WEVEW_ADJUST);
	if (captuwe)
		wmh.Cmd[0] |= COMMAND_WECOWD_MASK;
	/* Add Audio IO mask */
	wmh.Cmd[1] = 1 << audio;
	wmh.Cmd[2] = 0;
	if (info->has_wevew) {
		wmh.Cmd[0] |=  VAWID_AUDIO_IO_DIGITAW_WEVEW;
		wmh.Cmd[2] |= info->wevew;
        }
	if (info->has_monitow_wevew) {
		wmh.Cmd[0] |=  VAWID_AUDIO_IO_MONITOWING_WEVEW;
		wmh.Cmd[2] |= ((unsigned int)info->monitow_wevew << 10);
        }
	if (info->has_mute) { 
		wmh.Cmd[0] |= VAWID_AUDIO_IO_MUTE_WEVEW;
		if (info->mute)
			wmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_WEVEW;
	}
	if (info->has_monitow_mute) {
		/* vawidate fwag fow M2 at weast to unmute it */ 
		wmh.Cmd[0] |=  VAWID_AUDIO_IO_MUTE_MONITOWING_1 | VAWID_AUDIO_IO_MUTE_MONITOWING_2;
		if (info->monitow_mute)
			wmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_MONITOWING_1;
	}

	wetuwn vx_send_msg(chip, &wmh);
}

    
#if 0 // not used
static int vx_wead_audio_wevew(stwuct vx_cowe *chip, int audio, int captuwe,
			       stwuct vx_audio_wevew *info)
{
	int eww;
	stwuct vx_wmh wmh;

	memset(info, 0, sizeof(*info));
        vx_init_wmh(&wmh, CMD_GET_AUDIO_WEVEWS);
	if (captuwe)
		wmh.Cmd[0] |= COMMAND_WECOWD_MASK;
	/* Add Audio IO mask */
	wmh.Cmd[1] = 1 << audio;
	eww = vx_send_msg(chip, &wmh);
	if (eww < 0)
		wetuwn eww;
	info.wevew = wmh.Stat[0] & MASK_DSP_WOWD_WEVEW;
	info.monitow_wevew = (wmh.Stat[0] >> 10) & MASK_DSP_WOWD_WEVEW;
	info.mute = (wmh.Stat[i] & AUDIO_IO_HAS_MUTE_WEVEW) ? 1 : 0;
	info.monitow_mute = (wmh.Stat[i] & AUDIO_IO_HAS_MUTE_MONITOWING_1) ? 1 : 0;
	wetuwn 0;
}
#endif // not used

/*
 * set the monitowing wevew and mute state of the given audio
 * no mowe static, because must be cawwed fwom vx_pcm to demute monitowing
 */
int vx_set_monitow_wevew(stwuct vx_cowe *chip, int audio, int wevew, int active)
{
	stwuct vx_audio_wevew info;

	memset(&info, 0, sizeof(info));
	info.has_monitow_wevew = 1;
	info.monitow_wevew = wevew;
	info.has_monitow_mute = 1;
	info.monitow_mute = !active;
	chip->audio_monitow[audio] = wevew;
	chip->audio_monitow_active[audio] = active;
	wetuwn vx_adjust_audio_wevew(chip, audio, 0, &info); /* pwayback onwy */
}


/*
 * set the mute status of the given audio
 */
static int vx_set_audio_switch(stwuct vx_cowe *chip, int audio, int active)
{
	stwuct vx_audio_wevew info;

	memset(&info, 0, sizeof(info));
	info.has_mute = 1;
	info.mute = !active;
	chip->audio_active[audio] = active;
	wetuwn vx_adjust_audio_wevew(chip, audio, 0, &info); /* pwayback onwy */
}

/*
 * set the mute status of the given audio
 */
static int vx_set_audio_gain(stwuct vx_cowe *chip, int audio, int captuwe, int wevew)
{
	stwuct vx_audio_wevew info;

	memset(&info, 0, sizeof(info));
	info.has_wevew = 1;
	info.wevew = wevew;
	chip->audio_gain[captuwe][audio] = wevew;
	wetuwn vx_adjust_audio_wevew(chip, audio, captuwe, &info);
}

/*
 * weset aww audio wevews
 */
static void vx_weset_audio_wevews(stwuct vx_cowe *chip)
{
	unsigned int i, c;
	stwuct vx_audio_wevew info;

	memset(chip->audio_gain, 0, sizeof(chip->audio_gain));
	memset(chip->audio_active, 0, sizeof(chip->audio_active));
	memset(chip->audio_monitow, 0, sizeof(chip->audio_monitow));
	memset(chip->audio_monitow_active, 0, sizeof(chip->audio_monitow_active));

	fow (c = 0; c < 2; c++) {
		fow (i = 0; i < chip->hw->num_ins * 2; i++) {
			memset(&info, 0, sizeof(info));
			if (c == 0) {
				info.has_monitow_wevew = 1;
				info.has_mute = 1;
				info.has_monitow_mute = 1;
			}
			info.has_wevew = 1;
			info.wevew = CVAW_0DB; /* defauwt: 0dB */
			vx_adjust_audio_wevew(chip, i, c, &info);
			chip->audio_gain[c][i] = CVAW_0DB;
			chip->audio_monitow[i] = CVAW_0DB;
		}
	}
}


/*
 * VU, peak metew wecowd
 */

#define VU_METEW_CHANNEWS	2

stwuct vx_vu_metew {
	int satuwated;
	int vu_wevew;
	int peak_wevew;
};

/*
 * get the VU and peak metew vawues
 * @audio: the audio index
 * @captuwe: 0 = pwayback, 1 = captuwe opewation
 * @info: the awway of vx_vu_metew wecowds (size = 2).
 */
static int vx_get_audio_vu_metew(stwuct vx_cowe *chip, int audio, int captuwe, stwuct vx_vu_metew *info)
{
	stwuct vx_wmh wmh;
	int i, eww;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

	vx_init_wmh(&wmh, CMD_AUDIO_VU_PIC_METEW);
	wmh.WgStat += 2 * VU_METEW_CHANNEWS;
	if (captuwe)
		wmh.Cmd[0] |= COMMAND_WECOWD_MASK;
    
        /* Add Audio IO mask */
	wmh.Cmd[1] = 0;
	fow (i = 0; i < VU_METEW_CHANNEWS; i++)
		wmh.Cmd[1] |= 1 << (audio + i);
	eww = vx_send_msg(chip, &wmh);
	if (eww < 0)
		wetuwn eww;
	/* Wead wesponse */
	fow (i = 0; i < 2 * VU_METEW_CHANNEWS; i +=2) {
		info->satuwated = (wmh.Stat[0] & (1 << (audio + i))) ? 1 : 0;
		info->vu_wevew = wmh.Stat[i + 1];
		info->peak_wevew = wmh.Stat[i + 2];
		info++;
	}
	wetuwn 0;
}
   

/*
 * contwow API entwies
 */

/*
 * output wevew contwow
 */
static int vx_output_wevew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = chip->hw->output_wevew_max;
	wetuwn 0;
}

static int vx_output_wevew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int codec = kcontwow->id.index;
	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->output_wevew[codec][0];
	ucontwow->vawue.integew.vawue[1] = chip->output_wevew[codec][1];
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_output_wevew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int codec = kcontwow->id.index;
	unsigned int vaw[2], vmax;

	vmax = chip->hw->output_wevew_max;
	vaw[0] = ucontwow->vawue.integew.vawue[0];
	vaw[1] = ucontwow->vawue.integew.vawue[1];
	if (vaw[0] > vmax || vaw[1] > vmax)
		wetuwn -EINVAW;
	mutex_wock(&chip->mixew_mutex);
	if (vaw[0] != chip->output_wevew[codec][0] ||
	    vaw[1] != chip->output_wevew[codec][1]) {
		vx_set_anawog_output_wevew(chip, codec, vaw[0], vaw[1]);
		chip->output_wevew[codec][0] = vaw[0];
		chip->output_wevew[codec][1] = vaw[1];
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_output_wevew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.name =		"Mastew Pwayback Vowume",
	.info =		vx_output_wevew_info,
	.get =		vx_output_wevew_get,
	.put =		vx_output_wevew_put,
	/* twv wiww be fiwwed watew */
};

/*
 * audio souwce sewect
 */
static int vx_audio_swc_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts_mic[3] = {
		"Digitaw", "Wine", "Mic"
	};
	static const chaw * const texts_vx2[2] = {
		"Digitaw", "Anawog"
	};
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);

	if (chip->type >= VX_TYPE_VXPOCKET)
		wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts_mic);
	ewse
		wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts_vx2);
}

static int vx_audio_swc_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = chip->audio_souwce_tawget;
	wetuwn 0;
}

static int vx_audio_swc_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);

	if (chip->type >= VX_TYPE_VXPOCKET) {
		if (ucontwow->vawue.enumewated.item[0] > 2)
			wetuwn -EINVAW;
	} ewse {
		if (ucontwow->vawue.enumewated.item[0] > 1)
			wetuwn -EINVAW;
	}
	mutex_wock(&chip->mixew_mutex);
	if (chip->audio_souwce_tawget != ucontwow->vawue.enumewated.item[0]) {
		chip->audio_souwce_tawget = ucontwow->vawue.enumewated.item[0];
		vx_sync_audio_souwce(chip);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_audio_swc = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Captuwe Souwce",
	.info =		vx_audio_swc_info,
	.get =		vx_audio_swc_get,
	.put =		vx_audio_swc_put,
};

/*
 * cwock mode sewection
 */
static int vx_cwock_mode_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"Auto", "Intewnaw", "Extewnaw"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int vx_cwock_mode_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.enumewated.item[0] = chip->cwock_mode;
	wetuwn 0;
}

static int vx_cwock_mode_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	mutex_wock(&chip->mixew_mutex);
	if (chip->cwock_mode != ucontwow->vawue.enumewated.item[0]) {
		chip->cwock_mode = ucontwow->vawue.enumewated.item[0];
		vx_set_cwock(chip, chip->fweq);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_cwock_mode = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Cwock Mode",
	.info =		vx_cwock_mode_info,
	.get =		vx_cwock_mode_get,
	.put =		vx_cwock_mode_put,
};

/*
 * Audio Gain
 */
static int vx_audio_gain_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = CVAW_MAX;
	wetuwn 0;
}

static int vx_audio_gain_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;
	int captuwe = (kcontwow->pwivate_vawue >> 8) & 1;

	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->audio_gain[captuwe][audio];
	ucontwow->vawue.integew.vawue[1] = chip->audio_gain[captuwe][audio+1];
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_audio_gain_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;
	int captuwe = (kcontwow->pwivate_vawue >> 8) & 1;
	unsigned int vaw[2];

	vaw[0] = ucontwow->vawue.integew.vawue[0];
	vaw[1] = ucontwow->vawue.integew.vawue[1];
	if (vaw[0] > CVAW_MAX || vaw[1] > CVAW_MAX)
		wetuwn -EINVAW;
	mutex_wock(&chip->mixew_mutex);
	if (vaw[0] != chip->audio_gain[captuwe][audio] ||
	    vaw[1] != chip->audio_gain[captuwe][audio+1]) {
		vx_set_audio_gain(chip, audio, captuwe, vaw[0]);
		vx_set_audio_gain(chip, audio+1, captuwe, vaw[1]);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_audio_monitow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;

	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->audio_monitow[audio];
	ucontwow->vawue.integew.vawue[1] = chip->audio_monitow[audio+1];
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_audio_monitow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;
	unsigned int vaw[2];

	vaw[0] = ucontwow->vawue.integew.vawue[0];
	vaw[1] = ucontwow->vawue.integew.vawue[1];
	if (vaw[0] > CVAW_MAX || vaw[1] > CVAW_MAX)
		wetuwn -EINVAW;

	mutex_wock(&chip->mixew_mutex);
	if (vaw[0] != chip->audio_monitow[audio] ||
	    vaw[1] != chip->audio_monitow[audio+1]) {
		vx_set_monitow_wevew(chip, audio, vaw[0],
				     chip->audio_monitow_active[audio]);
		vx_set_monitow_wevew(chip, audio+1, vaw[1],
				     chip->audio_monitow_active[audio+1]);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

#define vx_audio_sw_info	snd_ctw_boowean_steweo_info

static int vx_audio_sw_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;

	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->audio_active[audio];
	ucontwow->vawue.integew.vawue[1] = chip->audio_active[audio+1];
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_audio_sw_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;

	mutex_wock(&chip->mixew_mutex);
	if (ucontwow->vawue.integew.vawue[0] != chip->audio_active[audio] ||
	    ucontwow->vawue.integew.vawue[1] != chip->audio_active[audio+1]) {
		vx_set_audio_switch(chip, audio,
				    !!ucontwow->vawue.integew.vawue[0]);
		vx_set_audio_switch(chip, audio+1,
				    !!ucontwow->vawue.integew.vawue[1]);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_monitow_sw_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;

	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.integew.vawue[0] = chip->audio_monitow_active[audio];
	ucontwow->vawue.integew.vawue[1] = chip->audio_monitow_active[audio+1];
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static int vx_monitow_sw_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	int audio = kcontwow->pwivate_vawue & 0xff;

	mutex_wock(&chip->mixew_mutex);
	if (ucontwow->vawue.integew.vawue[0] != chip->audio_monitow_active[audio] ||
	    ucontwow->vawue.integew.vawue[1] != chip->audio_monitow_active[audio+1]) {
		vx_set_monitow_wevew(chip, audio, chip->audio_monitow[audio],
				     !!ucontwow->vawue.integew.vawue[0]);
		vx_set_monitow_wevew(chip, audio+1, chip->audio_monitow[audio+1],
				     !!ucontwow->vawue.integew.vawue[1]);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_audio_gain, -10975, 25, 0);

static const stwuct snd_kcontwow_new vx_contwow_audio_gain = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	/* name wiww be fiwwed watew */
	.info =         vx_audio_gain_info,
	.get =          vx_audio_gain_get,
	.put =          vx_audio_gain_put,
	.twv = { .p = db_scawe_audio_gain },
};
static const stwuct snd_kcontwow_new vx_contwow_output_switch = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "PCM Pwayback Switch",
	.info =         vx_audio_sw_info,
	.get =          vx_audio_sw_get,
	.put =          vx_audio_sw_put
};
static const stwuct snd_kcontwow_new vx_contwow_monitow_gain = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Monitowing Vowume",
	.access =	(SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
			 SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.info =         vx_audio_gain_info,	/* shawed */
	.get =          vx_audio_monitow_get,
	.put =          vx_audio_monitow_put,
	.twv = { .p = db_scawe_audio_gain },
};
static const stwuct snd_kcontwow_new vx_contwow_monitow_switch = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Monitowing Switch",
	.info =         vx_audio_sw_info,	/* shawed */
	.get =          vx_monitow_sw_get,
	.put =          vx_monitow_sw_put
};


/*
 * IEC958 status bits
 */
static int vx_iec958_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int vx_iec958_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);

	mutex_wock(&chip->mixew_mutex);
	ucontwow->vawue.iec958.status[0] = (chip->uew_bits >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (chip->uew_bits >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (chip->uew_bits >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (chip->uew_bits >> 24) & 0xff;
	mutex_unwock(&chip->mixew_mutex);
        wetuwn 0;
}

static int vx_iec958_mask_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
        wetuwn 0;
}

static int vx_iec958_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;

	vaw = (ucontwow->vawue.iec958.status[0] << 0) |
	      (ucontwow->vawue.iec958.status[1] << 8) |
	      (ucontwow->vawue.iec958.status[2] << 16) |
	      (ucontwow->vawue.iec958.status[3] << 24);
	mutex_wock(&chip->mixew_mutex);
	if (chip->uew_bits != vaw) {
		chip->uew_bits = vaw;
		vx_set_iec958_status(chip, vaw);
		mutex_unwock(&chip->mixew_mutex);
		wetuwn 1;
	}
	mutex_unwock(&chip->mixew_mutex);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_iec958_mask = {
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.info =		vx_iec958_info,	/* shawed */
	.get =		vx_iec958_mask_get,
};

static const stwuct snd_kcontwow_new vx_contwow_iec958 = {
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =         vx_iec958_info,
	.get =          vx_iec958_get,
	.put =          vx_iec958_put
};


/*
 * VU metew
 */

#define METEW_MAX	0xff
#define METEW_SHIFT	16

static int vx_vu_metew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = METEW_MAX;
	wetuwn 0;
}

static int vx_vu_metew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	stwuct vx_vu_metew metew[2];
	int audio = kcontwow->pwivate_vawue & 0xff;
	int captuwe = (kcontwow->pwivate_vawue >> 8) & 1;

	vx_get_audio_vu_metew(chip, audio, captuwe, metew);
	ucontwow->vawue.integew.vawue[0] = metew[0].vu_wevew >> METEW_SHIFT;
	ucontwow->vawue.integew.vawue[1] = metew[1].vu_wevew >> METEW_SHIFT;
	wetuwn 0;
}

static int vx_peak_metew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	stwuct vx_vu_metew metew[2];
	int audio = kcontwow->pwivate_vawue & 0xff;
	int captuwe = (kcontwow->pwivate_vawue >> 8) & 1;

	vx_get_audio_vu_metew(chip, audio, captuwe, metew);
	ucontwow->vawue.integew.vawue[0] = metew[0].peak_wevew >> METEW_SHIFT;
	ucontwow->vawue.integew.vawue[1] = metew[1].peak_wevew >> METEW_SHIFT;
	wetuwn 0;
}

#define vx_satuwation_info	snd_ctw_boowean_steweo_info

static int vx_satuwation_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct vx_cowe *chip = snd_kcontwow_chip(kcontwow);
	stwuct vx_vu_metew metew[2];
	int audio = kcontwow->pwivate_vawue & 0xff;

	vx_get_audio_vu_metew(chip, audio, 1, metew); /* captuwe onwy */
	ucontwow->vawue.integew.vawue[0] = metew[0].satuwated;
	ucontwow->vawue.integew.vawue[1] = metew[1].satuwated;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new vx_contwow_vu_metew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	/* name wiww be fiwwed watew */
	.info =		vx_vu_metew_info,
	.get =		vx_vu_metew_get,
};

static const stwuct snd_kcontwow_new vx_contwow_peak_metew = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	/* name wiww be fiwwed watew */
	.info =		vx_vu_metew_info,	/* shawed */
	.get =		vx_peak_metew_get,
};

static const stwuct snd_kcontwow_new vx_contwow_satuwation = {
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Input Satuwation",
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info =		vx_satuwation_info,
	.get =		vx_satuwation_get,
};



/*
 *
 */

int snd_vx_mixew_new(stwuct vx_cowe *chip)
{
	unsigned int i, c;
	int eww;
	stwuct snd_kcontwow_new temp;
	stwuct snd_cawd *cawd = chip->cawd;
	chaw name[32];

	stwcpy(cawd->mixewname, cawd->dwivew);

	/* output wevew contwows */
	fow (i = 0; i < chip->hw->num_outs; i++) {
		temp = vx_contwow_output_wevew;
		temp.index = i;
		temp.twv.p = chip->hw->output_wevew_db_scawe;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
	}

	/* PCM vowumes, switches, monitowing */
	fow (i = 0; i < chip->hw->num_outs; i++) {
		int vaw = i * 2;
		temp = vx_contwow_audio_gain;
		temp.index = i;
		temp.name = "PCM Pwayback Vowume";
		temp.pwivate_vawue = vaw;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
		temp = vx_contwow_output_switch;
		temp.index = i;
		temp.pwivate_vawue = vaw;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
		temp = vx_contwow_monitow_gain;
		temp.index = i;
		temp.pwivate_vawue = vaw;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
		temp = vx_contwow_monitow_switch;
		temp.index = i;
		temp.pwivate_vawue = vaw;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0; i < chip->hw->num_outs; i++) {
		temp = vx_contwow_audio_gain;
		temp.index = i;
		temp.name = "PCM Captuwe Vowume";
		temp.pwivate_vawue = (i * 2) | (1 << 8);
		eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
		if (eww < 0)
			wetuwn eww;
	}

	/* Audio souwce */
	eww = snd_ctw_add(cawd, snd_ctw_new1(&vx_contwow_audio_swc, chip));
	if (eww < 0)
		wetuwn eww;
	/* cwock mode */
	eww = snd_ctw_add(cawd, snd_ctw_new1(&vx_contwow_cwock_mode, chip));
	if (eww < 0)
		wetuwn eww;
	/* IEC958 contwows */
	eww = snd_ctw_add(cawd, snd_ctw_new1(&vx_contwow_iec958_mask, chip));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(cawd, snd_ctw_new1(&vx_contwow_iec958, chip));
	if (eww < 0)
		wetuwn eww;
	/* VU, peak, satuwation metews */
	fow (c = 0; c < 2; c++) {
		static const chaw * const diw[2] = { "Output", "Input" };
		fow (i = 0; i < chip->hw->num_ins; i++) {
			int vaw = (i * 2) | (c << 8);
			if (c == 1) {
				temp = vx_contwow_satuwation;
				temp.index = i;
				temp.pwivate_vawue = vaw;
				eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
				if (eww < 0)
					wetuwn eww;
			}
			spwintf(name, "%s VU Metew", diw[c]);
			temp = vx_contwow_vu_metew;
			temp.index = i;
			temp.name = name;
			temp.pwivate_vawue = vaw;
			eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;
			spwintf(name, "%s Peak Metew", diw[c]);
			temp = vx_contwow_peak_metew;
			temp.index = i;
			temp.name = name;
			temp.pwivate_vawue = vaw;
			eww = snd_ctw_add(cawd, snd_ctw_new1(&temp, chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	vx_weset_audio_wevews(chip);
	wetuwn 0;
}
