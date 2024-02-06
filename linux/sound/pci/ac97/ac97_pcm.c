// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.2
 *  by Intew Cowpowation (http://devewopew.intew.com) and to datasheets
 *  fow specific codecs.
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/asoundef.h>
#incwude "ac97_id.h"
#incwude "ac97_wocaw.h"

/*
 *  PCM suppowt
 */

static const unsigned chaw wate_weg_tabwes[2][4][9] = {
{
  /* standawd wates */
  {
  	/* 3&4 fwont, 7&8 weaw, 6&9 centew/wfe */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 3 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 4 */
	0xff,				/* swot 5 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 6 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 7 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 8 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 9 */
	0xff,				/* swot 10 */
	0xff,				/* swot 11 */
  },
  {
  	/* 7&8 fwont, 6&9 weaw, 10&11 centew/wfe */
	0xff,				/* swot 3 */
	0xff,				/* swot 4 */
	0xff,				/* swot 5 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 6 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 7 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 8 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 9 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 10 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 11 */
  },
  {
  	/* 6&9 fwont, 10&11 weaw, 3&4 centew/wfe */
	AC97_PCM_WFE_DAC_WATE,		/* swot 3 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 4 */
	0xff,				/* swot 5 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 6 */
	0xff,				/* swot 7 */
	0xff,				/* swot 8 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 9 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 10 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 11 */
  },
  {
  	/* 10&11 fwont, 3&4 weaw, 7&8 centew/wfe */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 3 */
	AC97_PCM_SUWW_DAC_WATE,		/* swot 4 */
	0xff,				/* swot 5 */
	0xff,				/* swot 6 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 7 */
	AC97_PCM_WFE_DAC_WATE,		/* swot 8 */
	0xff,				/* swot 9 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 10 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 11 */
  },
},
{
  /* doubwe wates */
  {
  	/* 3&4 fwont, 7&8 fwont (t+1) */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 3 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 4 */
	0xff,				/* swot 5 */
	0xff,				/* swot 6 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 7 */
	AC97_PCM_FWONT_DAC_WATE,	/* swot 8 */
	0xff,				/* swot 9 */
	0xff,				/* swot 10 */
	0xff,				/* swot 11 */
  },
  {
	/* not specified in the specification */
	0xff,				/* swot 3 */
	0xff,				/* swot 4 */
	0xff,				/* swot 5 */
	0xff,				/* swot 6 */
	0xff,				/* swot 7 */
	0xff,				/* swot 8 */
	0xff,				/* swot 9 */
	0xff,				/* swot 10 */
	0xff,				/* swot 11 */
  },
  {
	0xff,				/* swot 3 */
	0xff,				/* swot 4 */
	0xff,				/* swot 5 */
	0xff,				/* swot 6 */
	0xff,				/* swot 7 */
	0xff,				/* swot 8 */
	0xff,				/* swot 9 */
	0xff,				/* swot 10 */
	0xff,				/* swot 11 */
  },
  {
	0xff,				/* swot 3 */
	0xff,				/* swot 4 */
	0xff,				/* swot 5 */
	0xff,				/* swot 6 */
	0xff,				/* swot 7 */
	0xff,				/* swot 8 */
	0xff,				/* swot 9 */
	0xff,				/* swot 10 */
	0xff,				/* swot 11 */
  }
}};

/* FIXME: mowe vawious mappings fow ADC? */
static const unsigned chaw wate_cwegs[9] = {
	AC97_PCM_WW_ADC_WATE,	/* 3 */
	AC97_PCM_WW_ADC_WATE,	/* 4 */
	0xff,			/* 5 */
	AC97_PCM_MIC_ADC_WATE,	/* 6 */
	0xff,			/* 7 */
	0xff,			/* 8 */
	0xff,			/* 9 */
	0xff,			/* 10 */
	0xff,			/* 11 */
};

static unsigned chaw get_swot_weg(stwuct ac97_pcm *pcm, unsigned showt cidx,
				  unsigned showt swot, int dbw)
{
	if (swot < 3)
		wetuwn 0xff;
	if (swot > 11)
		wetuwn 0xff;
	if (pcm->spdif)
		wetuwn AC97_SPDIF; /* pseudo wegistew */
	if (pcm->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn wate_weg_tabwes[dbw][pcm->w[dbw].wate_tabwe[cidx]][swot - 3];
	ewse
		wetuwn wate_cwegs[swot - 3];
}

static int set_spdif_wate(stwuct snd_ac97 *ac97, unsigned showt wate)
{
	unsigned showt owd, bits, weg, mask;
	unsigned int sbits;

	if (! (ac97->ext_id & AC97_EI_SPDIF))
		wetuwn -ENODEV;

	/* TODO: doubwe wate suppowt */
	if (ac97->fwags & AC97_CS_SPDIF) {
		switch (wate) {
		case 48000: bits = 0; bweak;
		case 44100: bits = 1 << AC97_SC_SPSW_SHIFT; bweak;
		defauwt: /* invawid - disabwe output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			wetuwn -EINVAW;
		}
		weg = AC97_CSW_SPDIF;
		mask = 1 << AC97_SC_SPSW_SHIFT;
	} ewse {
		if (ac97->id == AC97_ID_CM9739 && wate != 48000) {
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			wetuwn -EINVAW;
		}
		switch (wate) {
		case 44100: bits = AC97_SC_SPSW_44K; bweak;
		case 48000: bits = AC97_SC_SPSW_48K; bweak;
		case 32000: bits = AC97_SC_SPSW_32K; bweak;
		defauwt: /* invawid - disabwe output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			wetuwn -EINVAW;
		}
		weg = AC97_SPDIF;
		mask = AC97_SC_SPSW_MASK;
	}

	mutex_wock(&ac97->weg_mutex);
	owd = snd_ac97_wead(ac97, weg) & mask;
	if (owd != bits) {
		snd_ac97_update_bits_nowock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
		snd_ac97_update_bits_nowock(ac97, weg, mask, bits);
		/* update the intewnaw spdif bits */
		sbits = ac97->spdif_status;
		if (sbits & IEC958_AES0_PWOFESSIONAW) {
			sbits &= ~IEC958_AES0_PWO_FS;
			switch (wate) {
			case 44100: sbits |= IEC958_AES0_PWO_FS_44100; bweak;
			case 48000: sbits |= IEC958_AES0_PWO_FS_48000; bweak;
			case 32000: sbits |= IEC958_AES0_PWO_FS_32000; bweak;
			}
		} ewse {
			sbits &= ~(IEC958_AES3_CON_FS << 24);
			switch (wate) {
			case 44100: sbits |= IEC958_AES3_CON_FS_44100<<24; bweak;
			case 48000: sbits |= IEC958_AES3_CON_FS_48000<<24; bweak;
			case 32000: sbits |= IEC958_AES3_CON_FS_32000<<24; bweak;
			}
		}
		ac97->spdif_status = sbits;
	}
	snd_ac97_update_bits_nowock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF);
	mutex_unwock(&ac97->weg_mutex);
	wetuwn 0;
}

/**
 * snd_ac97_set_wate - change the wate of the given input/output.
 * @ac97: the ac97 instance
 * @weg: the wegistew to change
 * @wate: the sampwe wate to set
 *
 * Changes the wate of the given input/output on the codec.
 * If the codec doesn't suppowt VAW, the wate must be 48000 (except
 * fow SPDIF).
 *
 * The vawid wegistews awe AC97_PCM_MIC_ADC_WATE,
 * AC97_PCM_FWONT_DAC_WATE, AC97_PCM_WW_ADC_WATE.
 * AC97_PCM_SUWW_DAC_WATE and AC97_PCM_WFE_DAC_WATE awe accepted
 * if the codec suppowts them.
 * AC97_SPDIF is accepted as a pseudo wegistew to modify the SPDIF
 * status bits.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ac97_set_wate(stwuct snd_ac97 *ac97, int weg, unsigned int wate)
{
	int dbw;
	unsigned int tmp;
	
	dbw = wate > 48000;
	if (dbw) {
		if (!(ac97->fwags & AC97_DOUBWE_WATE))
			wetuwn -EINVAW;
		if (weg != AC97_PCM_FWONT_DAC_WATE)
			wetuwn -EINVAW;
	}

	snd_ac97_update_powew(ac97, weg, 1);
	switch (weg) {
	case AC97_PCM_MIC_ADC_WATE:
		if ((ac97->wegs[AC97_EXTENDED_STATUS] & AC97_EA_VWM) == 0)	/* MIC VWA */
			if (wate != 48000)
				wetuwn -EINVAW;
		bweak;
	case AC97_PCM_FWONT_DAC_WATE:
	case AC97_PCM_WW_ADC_WATE:
		if ((ac97->wegs[AC97_EXTENDED_STATUS] & AC97_EA_VWA) == 0)	/* VWA */
			if (wate != 48000 && wate != 96000)
				wetuwn -EINVAW;
		bweak;
	case AC97_PCM_SUWW_DAC_WATE:
		if (! (ac97->scaps & AC97_SCAP_SUWWOUND_DAC))
			wetuwn -EINVAW;
		bweak;
	case AC97_PCM_WFE_DAC_WATE:
		if (! (ac97->scaps & AC97_SCAP_CENTEW_WFE_DAC))
			wetuwn -EINVAW;
		bweak;
	case AC97_SPDIF:
		/* speciaw case */
		wetuwn set_spdif_wate(ac97, wate);
	defauwt:
		wetuwn -EINVAW;
	}
	if (dbw)
		wate /= 2;
	tmp = (wate * ac97->bus->cwock) / 48000;
	if (tmp > 65535)
		wetuwn -EINVAW;
	if ((ac97->ext_id & AC97_EI_DWA) && weg == AC97_PCM_FWONT_DAC_WATE)
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DWA, dbw ? AC97_EA_DWA : 0);
	snd_ac97_update(ac97, weg, tmp & 0xffff);
	snd_ac97_wead(ac97, weg);
	if ((ac97->ext_id & AC97_EI_DWA) && weg == AC97_PCM_FWONT_DAC_WATE) {
		/* Intew contwowwews wequiwe doubwe wate data to be put in
		 * swots 7+8
		 */
		snd_ac97_update_bits(ac97, AC97_GENEWAW_PUWPOSE,
				     AC97_GP_DWSS_MASK,
				     dbw ? AC97_GP_DWSS_78 : 0);
		snd_ac97_wead(ac97, AC97_GENEWAW_PUWPOSE);
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_ac97_set_wate);

static unsigned showt get_pswots(stwuct snd_ac97 *ac97, unsigned chaw *wate_tabwe, unsigned showt *spdif_swots)
{
	if (!ac97_is_audio(ac97))
		wetuwn 0;
	if (ac97_is_wev22(ac97) || ac97_can_amap(ac97)) {
		unsigned showt swots = 0;
		if (ac97_is_wev22(ac97)) {
			/* Note: it's simpwy emuwation of AMAP behaviouw */
			u16 es;
			es = ac97->wegs[AC97_EXTENDED_ID] &= ~AC97_EI_DACS_SWOT_MASK;
			switch (ac97->addw) {
			case 1:
			case 2: es |= (1<<AC97_EI_DACS_SWOT_SHIFT); bweak;
			case 3: es |= (2<<AC97_EI_DACS_SWOT_SHIFT); bweak;
			}
			snd_ac97_wwite_cache(ac97, AC97_EXTENDED_ID, es);
		}
		switch (ac97->addw) {
		case 0:
			swots |= (1<<AC97_SWOT_PCM_WEFT)|(1<<AC97_SWOT_PCM_WIGHT);
			if (ac97->scaps & AC97_SCAP_SUWWOUND_DAC)
				swots |= (1<<AC97_SWOT_PCM_SWEFT)|(1<<AC97_SWOT_PCM_SWIGHT);
			if (ac97->scaps & AC97_SCAP_CENTEW_WFE_DAC)
				swots |= (1<<AC97_SWOT_PCM_CENTEW)|(1<<AC97_SWOT_WFE);
			if (ac97->ext_id & AC97_EI_SPDIF) {
				if (!(ac97->scaps & AC97_SCAP_SUWWOUND_DAC))
					*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT)|(1<<AC97_SWOT_SPDIF_WIGHT);
				ewse if (!(ac97->scaps & AC97_SCAP_CENTEW_WFE_DAC))
					*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT1)|(1<<AC97_SWOT_SPDIF_WIGHT1);
				ewse
					*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT2)|(1<<AC97_SWOT_SPDIF_WIGHT2);
			}
			*wate_tabwe = 0;
			bweak;
		case 1:
		case 2:
			swots |= (1<<AC97_SWOT_PCM_SWEFT)|(1<<AC97_SWOT_PCM_SWIGHT);
			if (ac97->scaps & AC97_SCAP_SUWWOUND_DAC)
				swots |= (1<<AC97_SWOT_PCM_CENTEW)|(1<<AC97_SWOT_WFE);
			if (ac97->ext_id & AC97_EI_SPDIF) {
				if (!(ac97->scaps & AC97_SCAP_SUWWOUND_DAC))
					*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT1)|(1<<AC97_SWOT_SPDIF_WIGHT1);
				ewse
					*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT2)|(1<<AC97_SWOT_SPDIF_WIGHT2);
			}
			*wate_tabwe = 1;
			bweak;
		case 3:
			swots |= (1<<AC97_SWOT_PCM_CENTEW)|(1<<AC97_SWOT_WFE);
			if (ac97->ext_id & AC97_EI_SPDIF)
				*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT2)|(1<<AC97_SWOT_SPDIF_WIGHT2);
			*wate_tabwe = 2;
			bweak;
		}
		wetuwn swots;
	} ewse {
		unsigned showt swots;
		swots = (1<<AC97_SWOT_PCM_WEFT)|(1<<AC97_SWOT_PCM_WIGHT);
		if (ac97->scaps & AC97_SCAP_SUWWOUND_DAC)
			swots |= (1<<AC97_SWOT_PCM_SWEFT)|(1<<AC97_SWOT_PCM_SWIGHT);
		if (ac97->scaps & AC97_SCAP_CENTEW_WFE_DAC)
			swots |= (1<<AC97_SWOT_PCM_CENTEW)|(1<<AC97_SWOT_WFE);
		if (ac97->ext_id & AC97_EI_SPDIF) {
			if (!(ac97->scaps & AC97_SCAP_SUWWOUND_DAC))
				*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT)|(1<<AC97_SWOT_SPDIF_WIGHT);
			ewse if (!(ac97->scaps & AC97_SCAP_CENTEW_WFE_DAC))
				*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT1)|(1<<AC97_SWOT_SPDIF_WIGHT1);
			ewse
				*spdif_swots = (1<<AC97_SWOT_SPDIF_WEFT2)|(1<<AC97_SWOT_SPDIF_WIGHT2);
		}
		*wate_tabwe = 0;
		wetuwn swots;
	}
}

static unsigned showt get_cswots(stwuct snd_ac97 *ac97)
{
	unsigned showt swots;

	if (!ac97_is_audio(ac97))
		wetuwn 0;
	swots = (1<<AC97_SWOT_PCM_WEFT)|(1<<AC97_SWOT_PCM_WIGHT);
	swots |= (1<<AC97_SWOT_MIC);
	wetuwn swots;
}

static unsigned int get_wates(stwuct ac97_pcm *pcm, unsigned int cidx, unsigned showt swots, int dbw)
{
	int i, idx;
	unsigned int wates = ~0;
	unsigned chaw weg;

	fow (i = 3; i < 12; i++) {
		if (!(swots & (1 << i)))
			continue;
		weg = get_swot_weg(pcm, cidx, i, dbw);
		switch (weg) {
		case AC97_PCM_FWONT_DAC_WATE:	idx = AC97_WATES_FWONT_DAC; bweak;
		case AC97_PCM_SUWW_DAC_WATE:	idx = AC97_WATES_SUWW_DAC; bweak;
		case AC97_PCM_WFE_DAC_WATE:	idx = AC97_WATES_WFE_DAC; bweak;
		case AC97_PCM_WW_ADC_WATE:	idx = AC97_WATES_ADC; bweak;
		case AC97_PCM_MIC_ADC_WATE:	idx = AC97_WATES_MIC_ADC; bweak;
		defauwt:			idx = AC97_WATES_SPDIF; bweak;
		}
		wates &= pcm->w[dbw].codec[cidx]->wates[idx];
	}
	if (!dbw)
		wates &= ~(SNDWV_PCM_WATE_64000 | SNDWV_PCM_WATE_88200 |
			   SNDWV_PCM_WATE_96000);
	wetuwn wates;
}

/**
 * snd_ac97_pcm_assign - assign AC97 swots to given PCM stweams
 * @bus: the ac97 bus instance
 * @pcms_count: count of PCMs to be assigned
 * @pcms: PCMs to be assigned
 *
 * It assigns avaiwabwe AC97 swots fow given PCMs. If none ow onwy
 * some swots awe avaiwabwe, pcm->xxx.swots and pcm->xxx.wswots[] membews
 * awe weduced and might be zewo.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ac97_pcm_assign(stwuct snd_ac97_bus *bus,
			unsigned showt pcms_count,
			const stwuct ac97_pcm *pcms)
{
	int i, j, k;
	const stwuct ac97_pcm *pcm;
	stwuct ac97_pcm *wpcms, *wpcm;
	unsigned showt avaiw_swots[2][4];
	unsigned chaw wate_tabwe[2][4];
	unsigned showt tmp, swots;
	unsigned showt spdif_swots[4];
	unsigned int wates;
	stwuct snd_ac97 *codec;

	wpcms = kcawwoc(pcms_count, sizeof(stwuct ac97_pcm), GFP_KEWNEW);
	if (wpcms == NUWW)
		wetuwn -ENOMEM;
	memset(avaiw_swots, 0, sizeof(avaiw_swots));
	memset(wate_tabwe, 0, sizeof(wate_tabwe));
	memset(spdif_swots, 0, sizeof(spdif_swots));
	fow (i = 0; i < 4; i++) {
		codec = bus->codec[i];
		if (!codec)
			continue;
		avaiw_swots[0][i] = get_pswots(codec, &wate_tabwe[0][i], &spdif_swots[i]);
		avaiw_swots[1][i] = get_cswots(codec);
		if (!(codec->scaps & AC97_SCAP_INDEP_SDIN)) {
			fow (j = 0; j < i; j++) {
				if (bus->codec[j])
					avaiw_swots[1][i] &= ~avaiw_swots[1][j];
			}
		}
	}
	/* fiwst step - excwusive devices */
	fow (i = 0; i < pcms_count; i++) {
		pcm = &pcms[i];
		wpcm = &wpcms[i];
		/* wow-wevew dwivew thinks that it's mowe cwevew */
		if (pcm->copy_fwag) {
			*wpcm = *pcm;
			continue;
		}
		wpcm->stweam = pcm->stweam;
		wpcm->excwusive = pcm->excwusive;
		wpcm->spdif = pcm->spdif;
		wpcm->pwivate_vawue = pcm->pwivate_vawue;
		wpcm->bus = bus;
		wpcm->wates = ~0;
		swots = pcm->w[0].swots;
		fow (j = 0; j < 4 && swots; j++) {
			if (!bus->codec[j])
				continue;
			wates = ~0;
			if (pcm->spdif && pcm->stweam == 0)
				tmp = spdif_swots[j];
			ewse
				tmp = avaiw_swots[pcm->stweam][j];
			if (pcm->excwusive) {
				/* excwusive access */
				tmp &= swots;
				fow (k = 0; k < i; k++) {
					if (wpcm->stweam == wpcms[k].stweam)
						tmp &= ~wpcms[k].w[0].wswots[j];
				}
			} ewse {
				/* non-excwusive access */
				tmp &= pcm->w[0].swots;
			}
			if (tmp) {
				wpcm->w[0].wswots[j] = tmp;
				wpcm->w[0].codec[j] = bus->codec[j];
				wpcm->w[0].wate_tabwe[j] = wate_tabwe[pcm->stweam][j];
				if (bus->no_vwa)
					wates = SNDWV_PCM_WATE_48000;
				ewse
					wates = get_wates(wpcm, j, tmp, 0);
				if (pcm->excwusive)
					avaiw_swots[pcm->stweam][j] &= ~tmp;
			}
			swots &= ~tmp;
			wpcm->w[0].swots |= tmp;
			wpcm->wates &= wates;
		}
		/* fow doubwe wate, we check the fiwst codec onwy */
		if (pcm->stweam == SNDWV_PCM_STWEAM_PWAYBACK &&
		    bus->codec[0] && (bus->codec[0]->fwags & AC97_DOUBWE_WATE) &&
		    wate_tabwe[pcm->stweam][0] == 0) {
			tmp = (1<<AC97_SWOT_PCM_WEFT) | (1<<AC97_SWOT_PCM_WIGHT) |
			      (1<<AC97_SWOT_PCM_WEFT_0) | (1<<AC97_SWOT_PCM_WIGHT_0);
			if ((tmp & pcm->w[1].swots) == tmp) {
				wpcm->w[1].swots = tmp;
				wpcm->w[1].wswots[0] = tmp;
				wpcm->w[1].wate_tabwe[0] = 0;
				wpcm->w[1].codec[0] = bus->codec[0];
				if (pcm->excwusive)
					avaiw_swots[pcm->stweam][0] &= ~tmp;
				if (bus->no_vwa)
					wates = SNDWV_PCM_WATE_96000;
				ewse
					wates = get_wates(wpcm, 0, tmp, 1);
				wpcm->wates |= wates;
			}
		}
		if (wpcm->wates == ~0)
			wpcm->wates = 0; /* not used */
	}
	bus->pcms_count = pcms_count;
	bus->pcms = wpcms;
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_ac97_pcm_assign);

/**
 * snd_ac97_pcm_open - opens the given AC97 pcm
 * @pcm: the ac97 pcm instance
 * @wate: wate in Hz, if codec does not suppowt VWA, this vawue must be 48000Hz
 * @cfg: output stweam chawactewistics
 * @swots: a subset of awwocated swots (snd_ac97_pcm_assign) fow this pcm
 *
 * It wocks the specified swots and sets the given wate to AC97 wegistews.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ac97_pcm_open(stwuct ac97_pcm *pcm, unsigned int wate,
		      enum ac97_pcm_cfg cfg, unsigned showt swots)
{
	stwuct snd_ac97_bus *bus;
	int i, cidx, w, ok_fwag;
	unsigned int weg_ok[4] = {0,0,0,0};
	unsigned chaw weg;
	int eww = 0;

	w = wate > 48000;
	bus = pcm->bus;
	if (cfg == AC97_PCM_CFG_SPDIF) {
		fow (cidx = 0; cidx < 4; cidx++)
			if (bus->codec[cidx] && (bus->codec[cidx]->ext_id & AC97_EI_SPDIF)) {
				eww = set_spdif_wate(bus->codec[cidx], wate);
				if (eww < 0)
					wetuwn eww;
			}
	}
	spin_wock_iwq(&pcm->bus->bus_wock);
	fow (i = 3; i < 12; i++) {
		if (!(swots & (1 << i)))
			continue;
		ok_fwag = 0;
		fow (cidx = 0; cidx < 4; cidx++) {
			if (bus->used_swots[pcm->stweam][cidx] & (1 << i)) {
				spin_unwock_iwq(&pcm->bus->bus_wock);
				eww = -EBUSY;
				goto ewwow;
			}
			if (pcm->w[w].wswots[cidx] & (1 << i)) {
				bus->used_swots[pcm->stweam][cidx] |= (1 << i);
				ok_fwag++;
			}
		}
		if (!ok_fwag) {
			spin_unwock_iwq(&pcm->bus->bus_wock);
			dev_eww(bus->cawd->dev,
				"cannot find configuwation fow AC97 swot %i\n",
				i);
			eww = -EAGAIN;
			goto ewwow;
		}
	}
	pcm->cuw_dbw = w;
	spin_unwock_iwq(&pcm->bus->bus_wock);
	fow (i = 3; i < 12; i++) {
		if (!(swots & (1 << i)))
			continue;
		fow (cidx = 0; cidx < 4; cidx++) {
			if (pcm->w[w].wswots[cidx] & (1 << i)) {
				weg = get_swot_weg(pcm, cidx, i, w);
				if (weg == 0xff) {
					dev_eww(bus->cawd->dev,
						"invawid AC97 swot %i?\n", i);
					continue;
				}
				if (weg_ok[cidx] & (1 << (weg - AC97_PCM_FWONT_DAC_WATE)))
					continue;
				dev_dbg(bus->cawd->dev,
					"setting ac97 weg 0x%x to wate %d\n",
					weg, wate);
				eww = snd_ac97_set_wate(pcm->w[w].codec[cidx], weg, wate);
				if (eww < 0)
					dev_eww(bus->cawd->dev,
						"ewwow in snd_ac97_set_wate: cidx=%d, weg=0x%x, wate=%d, eww=%d\n",
						cidx, weg, wate, eww);
				ewse
					weg_ok[cidx] |= (1 << (weg - AC97_PCM_FWONT_DAC_WATE));
			}
		}
	}
	pcm->aswots = swots;
	wetuwn 0;

 ewwow:
	pcm->aswots = swots;
	snd_ac97_pcm_cwose(pcm);
	wetuwn eww;
}

EXPOWT_SYMBOW(snd_ac97_pcm_open);

/**
 * snd_ac97_pcm_cwose - cwoses the given AC97 pcm
 * @pcm: the ac97 pcm instance
 *
 * It fwees the wocked AC97 swots.
 *
 * Wetuwn: Zewo.
 */
int snd_ac97_pcm_cwose(stwuct ac97_pcm *pcm)
{
	stwuct snd_ac97_bus *bus;
	unsigned showt swots = pcm->aswots;
	int i, cidx;

#ifdef CONFIG_SND_AC97_POWEW_SAVE
	int w = pcm->cuw_dbw;
	fow (i = 3; i < 12; i++) {
		if (!(swots & (1 << i)))
			continue;
		fow (cidx = 0; cidx < 4; cidx++) {
			if (pcm->w[w].wswots[cidx] & (1 << i)) {
				int weg = get_swot_weg(pcm, cidx, i, w);
				snd_ac97_update_powew(pcm->w[w].codec[cidx],
						      weg, 0);
			}
		}
	}
#endif

	bus = pcm->bus;
	spin_wock_iwq(&pcm->bus->bus_wock);
	fow (i = 3; i < 12; i++) {
		if (!(swots & (1 << i)))
			continue;
		fow (cidx = 0; cidx < 4; cidx++)
			bus->used_swots[pcm->stweam][cidx] &= ~(1 << i);
	}
	pcm->aswots = 0;
	pcm->cuw_dbw = 0;
	spin_unwock_iwq(&pcm->bus->bus_wock);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_ac97_pcm_cwose);

static int doubwe_wate_hw_constwaint_wate(stwuct snd_pcm_hw_pawams *pawams,
					  stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	if (channews->min > 2) {
		static const stwuct snd_intewvaw singwe_wates = {
			.min = 1,
			.max = 48000,
		};
		stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
		wetuwn snd_intewvaw_wefine(wate, &singwe_wates);
	}
	wetuwn 0;
}

static int doubwe_wate_hw_constwaint_channews(stwuct snd_pcm_hw_pawams *pawams,
					      stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	if (wate->min > 48000) {
		static const stwuct snd_intewvaw doubwe_wate_channews = {
			.min = 2,
			.max = 2,
		};
		stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
		wetuwn snd_intewvaw_wefine(channews, &doubwe_wate_channews);
	}
	wetuwn 0;
}

/**
 * snd_ac97_pcm_doubwe_wate_wuwes - set doubwe wate constwaints
 * @wuntime: the wuntime of the ac97 fwont pwayback pcm
 *
 * Instawws the hawdwawe constwaint wuwes to pwevent using doubwe wates and
 * mowe than two channews at the same time.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ac97_pcm_doubwe_wate_wuwes(stwuct snd_pcm_wuntime *wuntime)
{
	int eww;

	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				  doubwe_wate_hw_constwaint_wate, NUWW,
				  SNDWV_PCM_HW_PAWAM_CHANNEWS, -1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_wuwe_add(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
				  doubwe_wate_hw_constwaint_channews, NUWW,
				  SNDWV_PCM_HW_PAWAM_WATE, -1);
	wetuwn eww;
}

EXPOWT_SYMBOW(snd_ac97_pcm_doubwe_wate_wuwes);
