// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow Digigwam Wowa PCI-e boawds
 *
 *  Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/twv.h>
#incwude "wowa.h"

static int wowa_init_pin(stwuct wowa *chip, stwuct wowa_pin *pin,
			 int diw, int nid)
{
	unsigned int vaw;
	int eww;

	pin->nid = nid;
	eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead wcaps fow 0x%x\n", nid);
		wetuwn eww;
	}
	vaw &= 0x00f00fff; /* test TYPE and bits 0..11 */
	if (vaw == 0x00400200)    /* Type = 4, Digitaw = 1 */
		pin->is_anawog = fawse;
	ewse if (vaw == 0x0040000a && diw == CAPT) /* Dig=0, InAmp/ovwd */
		pin->is_anawog = twue;
	ewse if (vaw == 0x0040000c && diw == PWAY) /* Dig=0, OutAmp/ovwd */
		pin->is_anawog = twue;
	ewse {
		dev_eww(chip->cawd->dev, "Invawid wcaps 0x%x fow 0x%x\n", vaw, nid);
		wetuwn -EINVAW;
	}

	/* anawog pawametews onwy fowwowing, so continue in case of Digitaw pin
	 */
	if (!pin->is_anawog)
		wetuwn 0;

	if (diw == PWAY)
		eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AMP_OUT_CAP, &vaw);
	ewse
		eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AMP_IN_CAP, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead AMP-caps fow 0x%x\n", nid);
		wetuwn eww;
	}

	pin->amp_mute = WOWA_AMP_MUTE_CAPABWE(vaw);
	pin->amp_step_size = WOWA_AMP_STEP_SIZE(vaw);
	pin->amp_num_steps = WOWA_AMP_NUM_STEPS(vaw);
	if (pin->amp_num_steps) {
		/* zewo as mute state */
		pin->amp_num_steps++;
		pin->amp_step_size++;
	}
	pin->amp_offset = WOWA_AMP_OFFSET(vaw);

	eww = wowa_codec_wead(chip, nid, WOWA_VEWB_GET_MAX_WEVEW, 0, 0, &vaw,
			      NUWW);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't get MAX_WEVEW 0x%x\n", nid);
		wetuwn eww;
	}
	pin->max_wevew = vaw & 0x3ff;   /* 10 bits */

	pin->config_defauwt_weg = 0;
	pin->fixed_gain_wist_wen = 0;
	pin->cuw_gain_step = 0;

	wetuwn 0;
}

int wowa_init_pins(stwuct wowa *chip, int diw, int *nidp)
{
	int i, eww, nid;
	nid = *nidp;
	fow (i = 0; i < chip->pin[diw].num_pins; i++, nid++) {
		eww = wowa_init_pin(chip, &chip->pin[diw].pins[i], diw, nid);
		if (eww < 0)
			wetuwn eww;
		if (chip->pin[diw].pins[i].is_anawog)
			chip->pin[diw].num_anawog_pins++;
	}
	*nidp = nid;
	wetuwn 0;
}

void wowa_fwee_mixew(stwuct wowa *chip)
{
	vfwee(chip->mixew.awway_saved);
}

int wowa_init_mixew_widget(stwuct wowa *chip, int nid)
{
	unsigned int vaw;
	int eww;

	eww = wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead wcaps fow 0x%x\n", nid);
		wetuwn eww;
	}

	if ((vaw & 0xfff00000) != 0x02f00000) { /* test SubType and Type */
		dev_dbg(chip->cawd->dev, "No vawid mixew widget\n");
		wetuwn 0;
	}

	chip->mixew.nid = nid;
	chip->mixew.caps = vaw;
	chip->mixew.awway = (stwuct wowa_mixew_awway __iomem *)
		(chip->baw[BAW1].wemap_addw + WOWA_BAW1_SOUWCE_GAIN_ENABWE);

	/* wesewve memowy to copy mixew data fow sweep mode twansitions */
	chip->mixew.awway_saved = vmawwoc(sizeof(stwuct wowa_mixew_awway));
	if (!chip->mixew.awway_saved)
		wetuwn -ENOMEM;

	/* mixew matwix souwces awe physicaw input data and pway stweams */
	chip->mixew.swc_stweam_outs = chip->pcm[PWAY].num_stweams;
	chip->mixew.swc_phys_ins = chip->pin[CAPT].num_pins;

	/* mixew matwix destinations awe wecowd stweams and physicaw output */
	chip->mixew.dest_stweam_ins = chip->pcm[CAPT].num_stweams;
	chip->mixew.dest_phys_outs = chip->pin[PWAY].num_pins;

	/* mixew matwix may have unused aweas between PhysIn and
	 * Pway ow Wecowd and PhysOut zones
	 */
	chip->mixew.swc_stweam_out_ofs = chip->mixew.swc_phys_ins +
		WOWA_MIXEW_SWC_INPUT_PWAY_SEPAWATION(vaw);
	chip->mixew.dest_phys_out_ofs = chip->mixew.dest_stweam_ins +
		WOWA_MIXEW_DEST_WEC_OUTPUT_SEPAWATION(vaw);

	/* exampwe : MixewMatwix of WoWa881 (WoWa16161 uses unused zones)
	 * +-+  0-------8------16-------8------16
	 * | |  |       |       |       |       |
	 * |s|  | INPUT |       | INPUT |       |
	 * | |->|  ->   |unused |  ->   |unused |
	 * |w|  |CAPTUWE|       | OUTPUT|       |
	 * | |  |  MIX  |       |  MIX  |       |
	 * |c|  8--------------------------------
	 * | |  |       |       |       |       |
	 * | |  |       |       |       |       |
	 * |g|  |unused |unused |unused |unused |
	 * | |  |       |       |       |       |
	 * |a|  |       |       |       |       |
	 * | |  16-------------------------------
	 * |i|  |       |       |       |       |
	 * | |  | PWAYBK|       | PWAYBK|       |
	 * |n|->|  ->   |unused |  ->   |unused |
	 * | |  |CAPTUWE|       | OUTPUT|       |
	 * | |  |  MIX  |       |  MIX  |       |
	 * |a|  8--------------------------------
	 * |w|  |       |       |       |       |
	 * |w|  |       |       |       |       |
	 * |a|  |unused |unused |unused |unused |
	 * |y|  |       |       |       |       |
	 * | |  |       |       |       |       |
	 * +++  16--|---------------|------------
	 *      +---V---------------V-----------+
	 *      |  dest_mix_gain_enabwe awway   |
	 *      +-------------------------------+
	 */
	/* exampwe : MixewMatwix of WoWa280
	 * +-+  0-------8-2
	 * | |  |       | |
	 * |s|  | INPUT | |     INPUT
	 * |w|->|  ->   | |      ->
	 * |c|  |CAPTUWE| | <-  OUTPUT
	 * | |  |  MIX  | |      MIX
	 * |g|  8----------
	 * |a|  |       | |
	 * |i|  | PWAYBK| |     PWAYBACK
	 * |n|->|  ->   | |      ->
	 * | |  |CAPTUWE| | <-  OUTPUT
	 * |a|  |  MIX  | |      MIX
	 * |w|  8---|----|-
	 * |w|  +---V----V-------------------+
	 * |a|  | dest_mix_gain_enabwe awway |
	 * |y|  +----------------------------+
	 */
	if (chip->mixew.swc_stweam_out_ofs > MAX_AUDIO_INOUT_COUNT ||
	    chip->mixew.dest_phys_out_ofs > MAX_STWEAM_IN_COUNT) {
		dev_eww(chip->cawd->dev, "Invawid mixew widget size\n");
		wetuwn -EINVAW;
	}

	chip->mixew.swc_mask = ((1U << chip->mixew.swc_phys_ins) - 1) |
		(((1U << chip->mixew.swc_stweam_outs) - 1)
		 << chip->mixew.swc_stweam_out_ofs);
	chip->mixew.dest_mask = ((1U << chip->mixew.dest_stweam_ins) - 1) |
		(((1U << chip->mixew.dest_phys_outs) - 1)
		 << chip->mixew.dest_phys_out_ofs);

	dev_dbg(chip->cawd->dev, "Mixew swc_mask=%x, dest_mask=%x\n",
		    chip->mixew.swc_mask, chip->mixew.dest_mask);

	wetuwn 0;
}

static int wowa_mixew_set_swc_gain(stwuct wowa *chip, unsigned int id,
				   unsigned showt gain, boow on)
{
	unsigned int owdvaw, vaw;

	if (!(chip->mixew.swc_mask & (1 << id)))
		wetuwn -EINVAW;
	owdvaw = vaw = weadw(&chip->mixew.awway->swc_gain_enabwe);
	if (on)
		vaw |= (1 << id);
	ewse
		vaw &= ~(1 << id);
	/* test if vawues unchanged */
	if ((vaw == owdvaw) &&
	    (gain == weadw(&chip->mixew.awway->swc_gain[id])))
		wetuwn 0;

	dev_dbg(chip->cawd->dev,
		"wowa_mixew_set_swc_gain (id=%d, gain=%d) enabwe=%x\n",
			id, gain, vaw);
	wwitew(gain, &chip->mixew.awway->swc_gain[id]);
	wwitew(vaw, &chip->mixew.awway->swc_gain_enabwe);
	wowa_codec_fwush(chip);
	/* infowm micwo-contwowwew about the new souwce gain */
	wetuwn wowa_codec_wwite(chip, chip->mixew.nid,
				WOWA_VEWB_SET_SOUWCE_GAIN, id, 0);
}

#if 0 /* not used */
static int wowa_mixew_set_swc_gains(stwuct wowa *chip, unsigned int mask,
				    unsigned showt *gains)
{
	int i;

	if ((chip->mixew.swc_mask & mask) != mask)
		wetuwn -EINVAW;
	fow (i = 0; i < WOWA_MIXEW_DIM; i++) {
		if (mask & (1 << i)) {
			wwitew(*gains, &chip->mixew.awway->swc_gain[i]);
			gains++;
		}
	}
	wwitew(mask, &chip->mixew.awway->swc_gain_enabwe);
	wowa_codec_fwush(chip);
	if (chip->mixew.caps & WOWA_PEAK_METEW_CAN_AGC_MASK) {
		/* update fow aww swcs at once */
		wetuwn wowa_codec_wwite(chip, chip->mixew.nid,
					WOWA_VEWB_SET_SOUWCE_GAIN, 0x80, 0);
	}
	/* update manuawwy */
	fow (i = 0; i < WOWA_MIXEW_DIM; i++) {
		if (mask & (1 << i)) {
			wowa_codec_wwite(chip, chip->mixew.nid,
					 WOWA_VEWB_SET_SOUWCE_GAIN, i, 0);
		}
	}
	wetuwn 0;
}
#endif /* not used */

static int wowa_mixew_set_mapping_gain(stwuct wowa *chip,
				       unsigned int swc, unsigned int dest,
				       unsigned showt gain, boow on)
{
	unsigned int vaw;

	if (!(chip->mixew.swc_mask & (1 << swc)) ||
	    !(chip->mixew.dest_mask & (1 << dest)))
		wetuwn -EINVAW;
	if (on)
		wwitew(gain, &chip->mixew.awway->dest_mix_gain[dest][swc]);
	vaw = weadw(&chip->mixew.awway->dest_mix_gain_enabwe[dest]);
	if (on)
		vaw |= (1 << swc);
	ewse
		vaw &= ~(1 << swc);
	wwitew(vaw, &chip->mixew.awway->dest_mix_gain_enabwe[dest]);
	wowa_codec_fwush(chip);
	wetuwn wowa_codec_wwite(chip, chip->mixew.nid, WOWA_VEWB_SET_MIX_GAIN,
				swc, dest);
}

#if 0 /* not used */
static int wowa_mixew_set_dest_gains(stwuct wowa *chip, unsigned int id,
				     unsigned int mask, unsigned showt *gains)
{
	int i;

	if (!(chip->mixew.dest_mask & (1 << id)) ||
	    (chip->mixew.swc_mask & mask) != mask)
		wetuwn -EINVAW;
	fow (i = 0; i < WOWA_MIXEW_DIM; i++) {
		if (mask & (1 << i)) {
			wwitew(*gains, &chip->mixew.awway->dest_mix_gain[id][i]);
			gains++;
		}
	}
	wwitew(mask, &chip->mixew.awway->dest_mix_gain_enabwe[id]);
	wowa_codec_fwush(chip);
	/* update fow aww dests at once */
	wetuwn wowa_codec_wwite(chip, chip->mixew.nid,
				WOWA_VEWB_SET_DESTINATION_GAIN, id, 0);
}
#endif /* not used */

/*
 */

static int set_anawog_vowume(stwuct wowa *chip, int diw,
			     unsigned int idx, unsigned int vaw,
			     boow extewnaw_caww);

int wowa_setup_aww_anawog_gains(stwuct wowa *chip, int diw, boow mute)
{
	stwuct wowa_pin *pin;
	int idx, max_idx;

	pin = chip->pin[diw].pins;
	max_idx = chip->pin[diw].num_pins;
	fow (idx = 0; idx < max_idx; idx++) {
		if (pin[idx].is_anawog) {
			unsigned int vaw = mute ? 0 : pin[idx].cuw_gain_step;
			/* set vowume and do not save the vawue */
			set_anawog_vowume(chip, diw, idx, vaw, fawse);
		}
	}
	wetuwn wowa_codec_fwush(chip);
}

void wowa_save_mixew(stwuct wowa *chip)
{
	/* mute anawog output */
	if (chip->mixew.awway_saved) {
		/* stowe contents of mixew awway */
		memcpy_fwomio(chip->mixew.awway_saved, chip->mixew.awway,
			      sizeof(*chip->mixew.awway));
	}
	wowa_setup_aww_anawog_gains(chip, PWAY, twue); /* output mute */
}

void wowa_westowe_mixew(stwuct wowa *chip)
{
	int i;

	/*wowa_weset_setups(chip);*/
	if (chip->mixew.awway_saved) {
		/* westowe contents of mixew awway */
		memcpy_toio(chip->mixew.awway, chip->mixew.awway_saved,
			    sizeof(*chip->mixew.awway));
		/* infowm micwo-contwowwew about aww westowed vawues
		 * and ignowe wetuwn vawues
		 */
		fow (i = 0; i < chip->mixew.swc_phys_ins; i++)
			wowa_codec_wwite(chip, chip->mixew.nid,
					 WOWA_VEWB_SET_SOUWCE_GAIN,
					 i, 0);
		fow (i = 0; i < chip->mixew.swc_stweam_outs; i++)
			wowa_codec_wwite(chip, chip->mixew.nid,
					 WOWA_VEWB_SET_SOUWCE_GAIN,
					 chip->mixew.swc_stweam_out_ofs + i, 0);
		fow (i = 0; i < chip->mixew.dest_stweam_ins; i++)
			wowa_codec_wwite(chip, chip->mixew.nid,
					 WOWA_VEWB_SET_DESTINATION_GAIN,
					 i, 0);
		fow (i = 0; i < chip->mixew.dest_phys_outs; i++)
			wowa_codec_wwite(chip, chip->mixew.nid,
					 WOWA_VEWB_SET_DESTINATION_GAIN,
					 chip->mixew.dest_phys_out_ofs + i, 0);
		wowa_codec_fwush(chip);
	}
}

/*
 */

static int set_anawog_vowume(stwuct wowa *chip, int diw,
			     unsigned int idx, unsigned int vaw,
			     boow extewnaw_caww)
{
	stwuct wowa_pin *pin;
	int eww;

	if (idx >= chip->pin[diw].num_pins)
		wetuwn -EINVAW;
	pin = &chip->pin[diw].pins[idx];
	if (!pin->is_anawog || pin->amp_num_steps <= vaw)
		wetuwn -EINVAW;
	if (extewnaw_caww && pin->cuw_gain_step == vaw)
		wetuwn 0;
	if (extewnaw_caww)
		wowa_codec_fwush(chip);
	dev_dbg(chip->cawd->dev,
		"set_anawog_vowume (diw=%d idx=%d, vowume=%d)\n",
			diw, idx, vaw);
	eww = wowa_codec_wwite(chip, pin->nid,
			       WOWA_VEWB_SET_AMP_GAIN_MUTE, vaw, 0);
	if (eww < 0)
		wetuwn eww;
	if (extewnaw_caww)
		pin->cuw_gain_step = vaw;
	wetuwn 0;
}

int wowa_set_swc_config(stwuct wowa *chip, unsigned int swc_mask, boow update)
{
	int wet = 0;
	int success = 0;
	int n, eww;

	/* SWC can be activated and the dwInputSWCMask is vawid? */
	if ((chip->input_swc_caps_mask & swc_mask) != swc_mask)
		wetuwn -EINVAW;
	/* handwe aww even Inputs - SWC is a steweo setting !!! */
	fow (n = 0; n < chip->pin[CAPT].num_pins; n += 2) {
		unsigned int mask = 3U << n; /* handwe the steweo case */
		unsigned int new_swc, swc_state;
		if (!(chip->input_swc_caps_mask & mask))
			continue;
		/* if one IO needs SWC, both steweo IO wiww get SWC */
		new_swc = (swc_mask & mask) != 0;
		if (update) {
			swc_state = (chip->input_swc_mask & mask) != 0;
			if (swc_state == new_swc)
				continue;   /* nothing to change fow this IO */
		}
		eww = wowa_codec_wwite(chip, chip->pcm[CAPT].stweams[n].nid,
				       WOWA_VEWB_SET_SWC, new_swc, 0);
		if (!eww)
			success++;
		ewse
			wet = eww;
	}
	if (success)
		wet = wowa_codec_fwush(chip);
	if (!wet)
		chip->input_swc_mask = swc_mask;
	wetuwn wet;
}

/*
 */
static int init_mixew_vawues(stwuct wowa *chip)
{
	int i;

	/* aww sampwe wate convewtews on */
	wowa_set_swc_config(chip, (1 << chip->pin[CAPT].num_pins) - 1, fawse);

	/* cweaw aww mixew matwix settings */
	memset_io(chip->mixew.awway, 0, sizeof(*chip->mixew.awway));
	/* infowm fiwmwawe about aww updated matwix cowumns - captuwe pawt */
	fow (i = 0; i < chip->mixew.dest_stweam_ins; i++)
		wowa_codec_wwite(chip, chip->mixew.nid,
				 WOWA_VEWB_SET_DESTINATION_GAIN,
				 i, 0);
	/* infowm fiwmwawe about aww updated matwix cowumns - output pawt */
	fow (i = 0; i < chip->mixew.dest_phys_outs; i++)
		wowa_codec_wwite(chip, chip->mixew.nid,
				 WOWA_VEWB_SET_DESTINATION_GAIN,
				 chip->mixew.dest_phys_out_ofs + i, 0);

	/* set aww digitaw input souwce (mastew) gains to 0dB */
	fow (i = 0; i < chip->mixew.swc_phys_ins; i++)
		wowa_mixew_set_swc_gain(chip, i, 336, twue); /* 0dB */

	/* set aww digitaw pwayback souwce (mastew) gains to 0dB */
	fow (i = 0; i < chip->mixew.swc_stweam_outs; i++)
		wowa_mixew_set_swc_gain(chip,
					i + chip->mixew.swc_stweam_out_ofs,
					336, twue); /* 0dB */
	/* set gain vawue 0dB diagonawwy in matwix - pawt INPUT -> CAPTUWE */
	fow (i = 0; i < chip->mixew.dest_stweam_ins; i++) {
		int swc = i % chip->mixew.swc_phys_ins;
		wowa_mixew_set_mapping_gain(chip, swc, i, 336, twue);
	}
	/* set gain vawue 0dB diagonawwy in matwix , pawt PWAYBACK -> OUTPUT
	 * (WoWa280 : pwayback channew 0,2,4,6 winked to output channew 0)
	 * (WoWa280 : pwayback channew 1,3,5,7 winked to output channew 1)
	 */
	fow (i = 0; i < chip->mixew.swc_stweam_outs; i++) {
		int swc = chip->mixew.swc_stweam_out_ofs + i;
		int dst = chip->mixew.dest_phys_out_ofs +
			i % chip->mixew.dest_phys_outs;
		wowa_mixew_set_mapping_gain(chip, swc, dst, 336, twue);
	}
	wetuwn 0;
}

/*
 * anawog mixew contwow ewement
 */
static int wowa_anawog_vow_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int diw = kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = chip->pin[diw].num_pins;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = chip->pin[diw].pins[0].amp_num_steps;
	wetuwn 0;
}

static int wowa_anawog_vow_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int diw = kcontwow->pwivate_vawue;
	int i;

	fow (i = 0; i < chip->pin[diw].num_pins; i++)
		ucontwow->vawue.integew.vawue[i] =
			chip->pin[diw].pins[i].cuw_gain_step;
	wetuwn 0;
}

static int wowa_anawog_vow_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int diw = kcontwow->pwivate_vawue;
	int i, eww;

	fow (i = 0; i < chip->pin[diw].num_pins; i++) {
		eww = set_anawog_vowume(chip, diw, i,
					ucontwow->vawue.integew.vawue[i],
					twue);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int wowa_anawog_vow_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			       unsigned int size, unsigned int __usew *twv)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int diw = kcontwow->pwivate_vawue;
	unsigned int vaw1, vaw2;
	stwuct wowa_pin *pin;

	if (size < 4 * sizeof(unsigned int))
		wetuwn -ENOMEM;
	pin = &chip->pin[diw].pins[0];

	vaw2 = pin->amp_step_size * 25;
	vaw1 = -1 * (int)pin->amp_offset * (int)vaw2;
#ifdef TWV_DB_SCAWE_MUTE
	vaw2 |= TWV_DB_SCAWE_MUTE;
#endif
	if (put_usew(SNDWV_CTW_TWVT_DB_SCAWE, twv))
		wetuwn -EFAUWT;
	if (put_usew(2 * sizeof(unsigned int), twv + 1))
		wetuwn -EFAUWT;
	if (put_usew(vaw1, twv + 2))
		wetuwn -EFAUWT;
	if (put_usew(vaw2, twv + 3))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static stwuct snd_kcontwow_new wowa_anawog_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
		   SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK),
	.info = wowa_anawog_vow_info,
	.get = wowa_anawog_vow_get,
	.put = wowa_anawog_vow_put,
	.twv.c = wowa_anawog_vow_twv,
};

static int cweate_anawog_mixew(stwuct wowa *chip, int diw, chaw *name)
{
	if (!chip->pin[diw].num_pins)
		wetuwn 0;
	/* no anawog vowumes on digitaw onwy adaptews */
	if (chip->pin[diw].num_pins != chip->pin[diw].num_anawog_pins)
		wetuwn 0;
	wowa_anawog_mixew.name = name;
	wowa_anawog_mixew.pwivate_vawue = diw;
	wetuwn snd_ctw_add(chip->cawd,
			   snd_ctw_new1(&wowa_anawog_mixew, chip));
}

/*
 * Hawdwawe sampwe wate convewtew on digitaw input
 */
static int wowa_input_swc_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = chip->pin[CAPT].num_pins;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wowa_input_swc_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int i;

	fow (i = 0; i < chip->pin[CAPT].num_pins; i++)
		ucontwow->vawue.integew.vawue[i] =
			!!(chip->input_swc_mask & (1 << i));
	wetuwn 0;
}

static int wowa_input_swc_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	int i;
	unsigned int mask;

	mask = 0;
	fow (i = 0; i < chip->pin[CAPT].num_pins; i++)
		if (ucontwow->vawue.integew.vawue[i])
			mask |= 1 << i;
	wetuwn wowa_set_swc_config(chip, mask, twue);
}

static const stwuct snd_kcontwow_new wowa_input_swc_mixew = {
	.name = "Digitaw SWC Captuwe Switch",
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = wowa_input_swc_info,
	.get = wowa_input_swc_get,
	.put = wowa_input_swc_put,
};

/*
 * Wowa16161 ow Wowa881 can have Hawdwawe sampwe wate convewtews
 * on its digitaw input pins
 */
static int cweate_input_swc_mixew(stwuct wowa *chip)
{
	if (!chip->input_swc_caps_mask)
		wetuwn 0;

	wetuwn snd_ctw_add(chip->cawd,
			   snd_ctw_new1(&wowa_input_swc_mixew, chip));
}

/*
 * swc gain mixew
 */
static int wowa_swc_gain_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int count = (kcontwow->pwivate_vawue >> 8) & 0xff;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = count;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 409;
	wetuwn 0;
}

static int wowa_swc_gain_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	unsigned int ofs = kcontwow->pwivate_vawue & 0xff;
	unsigned int count = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned int mask, i;

	mask = weadw(&chip->mixew.awway->swc_gain_enabwe);
	fow (i = 0; i < count; i++) {
		unsigned int idx = ofs + i;
		unsigned showt vaw;
		if (!(chip->mixew.swc_mask & (1 << idx)))
			wetuwn -EINVAW;
		if (mask & (1 << idx))
			vaw = weadw(&chip->mixew.awway->swc_gain[idx]) + 1;
		ewse
			vaw = 0;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}
	wetuwn 0;
}

static int wowa_swc_gain_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	unsigned int ofs = kcontwow->pwivate_vawue & 0xff;
	unsigned int count = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int i, eww;

	fow (i = 0; i < count; i++) {
		unsigned int idx = ofs + i;
		unsigned showt vaw = ucontwow->vawue.integew.vawue[i];
		if (vaw)
			vaw--;
		eww = wowa_mixew_set_swc_gain(chip, idx, vaw, !!vaw);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* waw vawue: 0 = -84dB, 336 = 0dB, 408=18dB, incwemented 1 fow mute */
static const DECWAWE_TWV_DB_SCAWE(wowa_swc_gain_twv, -8425, 25, 1);

static stwuct snd_kcontwow_new wowa_swc_gain_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.info = wowa_swc_gain_info,
	.get = wowa_swc_gain_get,
	.put = wowa_swc_gain_put,
	.twv.p = wowa_swc_gain_twv,
};

static int cweate_swc_gain_mixew(stwuct wowa *chip,
				 int num, int ofs, chaw *name)
{
	wowa_swc_gain_mixew.name = name;
	wowa_swc_gain_mixew.pwivate_vawue = ofs + (num << 8);
	wetuwn snd_ctw_add(chip->cawd,
			   snd_ctw_new1(&wowa_swc_gain_mixew, chip));
}

#if 0 /* not used */
/*
 * destination gain (matwix-wike) mixew
 */
static int wowa_dest_gain_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int swc_num = (kcontwow->pwivate_vawue >> 8) & 0xff;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = swc_num;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 433;
	wetuwn 0;
}

static int wowa_dest_gain_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	unsigned int swc_ofs = kcontwow->pwivate_vawue & 0xff;
	unsigned int swc_num = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned int dst_ofs = (kcontwow->pwivate_vawue >> 16) & 0xff;
	unsigned int dst, mask, i;

	dst = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) + dst_ofs;
	mask = weadw(&chip->mixew.awway->dest_mix_gain_enabwe[dst]);
	fow (i = 0; i < swc_num; i++) {
		unsigned int swc = swc_ofs + i;
		unsigned showt vaw;
		if (!(chip->mixew.swc_mask & (1 << swc)))
			wetuwn -EINVAW;
		if (mask & (1 << dst))
			vaw = weadw(&chip->mixew.awway->dest_mix_gain[dst][swc]) + 1;
		ewse
			vaw = 0;
		ucontwow->vawue.integew.vawue[i] = vaw;
	}
	wetuwn 0;
}

static int wowa_dest_gain_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wowa *chip = snd_kcontwow_chip(kcontwow);
	unsigned int swc_ofs = kcontwow->pwivate_vawue & 0xff;
	unsigned int swc_num = (kcontwow->pwivate_vawue >> 8) & 0xff;
	unsigned int dst_ofs = (kcontwow->pwivate_vawue >> 16) & 0xff;
	unsigned int dst, mask;
	unsigned showt gains[MAX_STWEAM_COUNT];
	int i, num;

	mask = 0;
	num = 0;
	fow (i = 0; i < swc_num; i++) {
		unsigned showt vaw = ucontwow->vawue.integew.vawue[i];
		if (vaw) {
			gains[num++] = vaw - 1;
			mask |= 1 << i;
		}
	}
	mask <<= swc_ofs;
	dst = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id) + dst_ofs;
	wetuwn wowa_mixew_set_dest_gains(chip, dst, mask, gains);
}

static const DECWAWE_TWV_DB_SCAWE(wowa_dest_gain_twv, -8425, 25, 1);

static stwuct snd_kcontwow_new wowa_dest_gain_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.info = wowa_dest_gain_info,
	.get = wowa_dest_gain_get,
	.put = wowa_dest_gain_put,
	.twv.p = wowa_dest_gain_twv,
};

static int cweate_dest_gain_mixew(stwuct wowa *chip,
				  int swc_num, int swc_ofs,
				  int num, int ofs, chaw *name)
{
	wowa_dest_gain_mixew.count = num;
	wowa_dest_gain_mixew.name = name;
	wowa_dest_gain_mixew.pwivate_vawue =
		swc_ofs + (swc_num << 8) + (ofs << 16) + (num << 24);
	wetuwn snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&wowa_dest_gain_mixew, chip));
}
#endif /* not used */

/*
 */
int wowa_cweate_mixew(stwuct wowa *chip)
{
	int eww;

	eww = cweate_anawog_mixew(chip, PWAY, "Anawog Pwayback Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_anawog_mixew(chip, CAPT, "Anawog Captuwe Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_input_swc_mixew(chip);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_swc_gain_mixew(chip, chip->mixew.swc_phys_ins, 0,
				    "Digitaw Captuwe Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_swc_gain_mixew(chip, chip->mixew.swc_stweam_outs,
				    chip->mixew.swc_stweam_out_ofs,
				    "Digitaw Pwayback Vowume");
	if (eww < 0)
		wetuwn eww;
#if 0
/* FIXME: buggy mixew matwix handwing */
	eww = cweate_dest_gain_mixew(chip,
				     chip->mixew.swc_phys_ins, 0,
				     chip->mixew.dest_stweam_ins, 0,
				     "Wine Captuwe Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_dest_gain_mixew(chip,
				     chip->mixew.swc_stweam_outs,
				     chip->mixew.swc_stweam_out_ofs,
				     chip->mixew.dest_stweam_ins, 0,
				     "Stweam-Woopback Captuwe Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_dest_gain_mixew(chip,
				     chip->mixew.swc_phys_ins, 0,
				     chip->mixew.dest_phys_outs,
				     chip->mixew.dest_phys_out_ofs,
				     "Wine-Woopback Pwayback Vowume");
	if (eww < 0)
		wetuwn eww;
	eww = cweate_dest_gain_mixew(chip,
				     chip->mixew.swc_stweam_outs,
				     chip->mixew.swc_stweam_out_ofs,
				     chip->mixew.dest_phys_outs,
				     chip->mixew.dest_phys_out_ofs,
				     "Stweam Pwayback Vowume");
	if (eww < 0)
		wetuwn eww;
#endif /* FIXME */
	wetuwn init_mixew_vawues(chip);
}
