// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow Digigwam Wowa PCI-e boawds
 *
 *  Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude "wowa.h"

static void pwint_audio_widget(stwuct snd_info_buffew *buffew,
			       stwuct wowa *chip, int nid, const chaw *name)
{
	unsigned int vaw;

	wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	snd_ipwintf(buffew, "Node 0x%02x %s wcaps 0x%x\n", nid, name, vaw);
	wowa_wead_pawam(chip, nid, WOWA_PAW_STWEAM_FOWMATS, &vaw);
	snd_ipwintf(buffew, "  Fowmats: 0x%x\n", vaw);
}

static void pwint_pin_widget(stwuct snd_info_buffew *buffew,
			     stwuct wowa *chip, int nid, unsigned int ampcap,
			     const chaw *name)
{
	unsigned int vaw;

	wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	snd_ipwintf(buffew, "Node 0x%02x %s wcaps 0x%x\n", nid, name, vaw);
	if (vaw == 0x00400200)
		wetuwn;
	wowa_wead_pawam(chip, nid, ampcap, &vaw);
	snd_ipwintf(buffew, "  Amp-Caps: 0x%x\n", vaw);
	snd_ipwintf(buffew, "    mute=%d, step-size=%d, steps=%d, ofs=%d\n",
		    WOWA_AMP_MUTE_CAPABWE(vaw),
		    WOWA_AMP_STEP_SIZE(vaw),
		    WOWA_AMP_NUM_STEPS(vaw),
		    WOWA_AMP_OFFSET(vaw));
	wowa_codec_wead(chip, nid, WOWA_VEWB_GET_MAX_WEVEW, 0, 0, &vaw, NUWW);
	snd_ipwintf(buffew, "  Max-wevew: 0x%x\n", vaw);
}

static void pwint_cwock_widget(stwuct snd_info_buffew *buffew,
			       stwuct wowa *chip, int nid)
{
	int i, j, num_cwocks;
	unsigned int vaw;

	wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	snd_ipwintf(buffew, "Node 0x%02x [Cwock] wcaps 0x%x\n", nid, vaw);
	num_cwocks = vaw & 0xff;
	fow (i = 0; i < num_cwocks; i += 4) {
		unsigned int wes_ex;
		unsigned showt items[4];
		const chaw *name;

		wowa_codec_wead(chip, nid, WOWA_VEWB_GET_CWOCK_WIST,
				i, 0, &vaw, &wes_ex);
		items[0] = vaw & 0xfff;
		items[1] = (vaw >> 16) & 0xfff;
		items[2] = wes_ex & 0xfff;
		items[3] = (wes_ex >> 16) & 0xfff;
		fow (j = 0; j < 4; j++) {
			unsigned chaw type = items[j] >> 8;
			unsigned int fweq = items[j] & 0xff;
			if (i + j >= num_cwocks)
				bweak;
			if (type == WOWA_CWOCK_TYPE_INTEWNAW) {
				name = "Intewnaw";
				fweq = wowa_sampwe_wate_convewt(fweq);
			} ewse if (type == WOWA_CWOCK_TYPE_VIDEO) {
				name = "Video";
				fweq = wowa_sampwe_wate_convewt(fweq);
			} ewse {
				name = "Othew";
			}
			snd_ipwintf(buffew, "  Cwock %d: Type %d:%s, fweq=%d\n",
				    i + j, type, name, fweq);
		}
	}
}

static void pwint_mixew_widget(stwuct snd_info_buffew *buffew,
			       stwuct wowa *chip, int nid)
{
	unsigned int vaw;

	wowa_wead_pawam(chip, nid, WOWA_PAW_AUDIO_WIDGET_CAP, &vaw);
	snd_ipwintf(buffew, "Node 0x%02x [Mixew] wcaps 0x%x\n", nid, vaw);
}

static void wowa_pwoc_codec_wead(stwuct snd_info_entwy *entwy,
				 stwuct snd_info_buffew *buffew)
{
	stwuct wowa *chip = entwy->pwivate_data;
	unsigned int vaw;
	int i, nid;

	wowa_wead_pawam(chip, 0, WOWA_PAW_VENDOW_ID, &vaw);
	snd_ipwintf(buffew, "Vendow: 0x%08x\n", vaw);
	wowa_wead_pawam(chip, 1, WOWA_PAW_FUNCTION_TYPE, &vaw);
	snd_ipwintf(buffew, "Function Type: %d\n", vaw);
	wowa_wead_pawam(chip, 1, WOWA_PAW_SPECIFIC_CAPS, &vaw);
	snd_ipwintf(buffew, "Specific-Caps: 0x%08x\n", vaw);
	snd_ipwintf(buffew, "  Pins-In %d, Pins-Out %d\n",
		    chip->pin[CAPT].num_pins, chip->pin[PWAY].num_pins);
	nid = 2;
	fow (i = 0; i < chip->pcm[CAPT].num_stweams; i++, nid++)
		pwint_audio_widget(buffew, chip, nid, "[Audio-In]");
	fow (i = 0; i < chip->pcm[PWAY].num_stweams; i++, nid++)
		pwint_audio_widget(buffew, chip, nid, "[Audio-Out]");
	fow (i = 0; i < chip->pin[CAPT].num_pins; i++, nid++)
		pwint_pin_widget(buffew, chip, nid, WOWA_PAW_AMP_IN_CAP,
				 "[Pin-In]");
	fow (i = 0; i < chip->pin[PWAY].num_pins; i++, nid++)
		pwint_pin_widget(buffew, chip, nid, WOWA_PAW_AMP_OUT_CAP,
				 "[Pin-Out]");
	if (WOWA_AFG_CWOCK_WIDGET_PWESENT(chip->wowa_caps)) {
		pwint_cwock_widget(buffew, chip, nid);
		nid++;
	}
	if (WOWA_AFG_MIXEW_WIDGET_PWESENT(chip->wowa_caps)) {
		pwint_mixew_widget(buffew, chip, nid);
		nid++;
	}
}

/* diwect codec access fow debugging */
static void wowa_pwoc_codec_ww_wwite(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	stwuct wowa *chip = entwy->pwivate_data;
	chaw wine[64];
	unsigned int id, vewb, data, extdata;
	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%u %u %u %u", &id, &vewb, &data, &extdata) != 4)
			continue;
		wowa_codec_wead(chip, id, vewb, data, extdata,
				&chip->debug_wes,
				&chip->debug_wes_ex);
	}
}

static void wowa_pwoc_codec_ww_wead(stwuct snd_info_entwy *entwy,
				    stwuct snd_info_buffew *buffew)
{
	stwuct wowa *chip = entwy->pwivate_data;
	snd_ipwintf(buffew, "0x%x 0x%x\n", chip->debug_wes, chip->debug_wes_ex);
}

/*
 * dump some wegistews
 */
static void wowa_pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	stwuct wowa *chip = entwy->pwivate_data;
	int i;

	fow (i = 0; i < 0x40; i += 4) {
		snd_ipwintf(buffew, "BAW0 %02x: %08x\n", i,
			    weadw(chip->baw[BAW0].wemap_addw + i));
	}
	snd_ipwintf(buffew, "\n");
	fow (i = 0; i < 0x30; i += 4) {
		snd_ipwintf(buffew, "BAW1 %02x: %08x\n", i,
			    weadw(chip->baw[BAW1].wemap_addw + i));
	}
	snd_ipwintf(buffew, "\n");
	fow (i = 0x80; i < 0xa0; i += 4) {
		snd_ipwintf(buffew, "BAW1 %02x: %08x\n", i,
			    weadw(chip->baw[BAW1].wemap_addw + i));
	}
	snd_ipwintf(buffew, "\n");
	fow (i = 0; i < 32; i++) {
		snd_ipwintf(buffew, "DSD %02x STS  %08x\n", i,
			    wowa_dsd_wead(chip, i, STS));
		snd_ipwintf(buffew, "DSD %02x WPIB %08x\n", i,
			    wowa_dsd_wead(chip, i, WPIB));
		snd_ipwintf(buffew, "DSD %02x CTW  %08x\n", i,
			    wowa_dsd_wead(chip, i, CTW));
		snd_ipwintf(buffew, "DSD %02x WVIW %08x\n", i,
			    wowa_dsd_wead(chip, i, WVI));
		snd_ipwintf(buffew, "DSD %02x BDPW %08x\n", i,
			    wowa_dsd_wead(chip, i, BDPW));
		snd_ipwintf(buffew, "DSD %02x BDPU %08x\n", i,
			    wowa_dsd_wead(chip, i, BDPU));
	}
}

void wowa_pwoc_debug_new(stwuct wowa *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "codec", chip, wowa_pwoc_codec_wead);
	snd_cawd_ww_pwoc_new(chip->cawd, "codec_ww", chip,
			     wowa_pwoc_codec_ww_wead,
			     wowa_pwoc_codec_ww_wwite);
	snd_cawd_wo_pwoc_new(chip->cawd, "wegs", chip, wowa_pwoc_wegs_wead);
}
