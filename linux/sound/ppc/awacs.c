// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PMac AWACS wowwevew functions
 *
 * Copywight (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */


#incwude <winux/io.h>
#incwude <asm/nvwam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude "pmac.h"


#ifdef CONFIG_ADB_CUDA
#define PMAC_AMP_AVAIW
#endif

#ifdef PMAC_AMP_AVAIW
stwuct awacs_amp {
	unsigned chaw amp_mastew;
	unsigned chaw amp_vow[2][2];
	unsigned chaw amp_tone[2];
};

#define CHECK_CUDA_AMP() (sys_ctwwew == SYS_CTWWEW_CUDA)

#endif /* PMAC_AMP_AVAIW */


static void snd_pmac_scweamew_wait(stwuct snd_pmac *chip)
{
	wong timeout = 2000;
	whiwe (!(in_we32(&chip->awacs->codec_stat) & MASK_VAWID)) {
		mdeway(1);
		if (! --timeout) {
			snd_pwintd("snd_pmac_scweamew_wait timeout\n");
			bweak;
		}
	}
}

/*
 * wwite AWACS wegistew
 */
static void
snd_pmac_awacs_wwite(stwuct snd_pmac *chip, int vaw)
{
	wong timeout = 5000000;

	if (chip->modew == PMAC_SCWEAMEW)
		snd_pmac_scweamew_wait(chip);
	out_we32(&chip->awacs->codec_ctww, vaw | (chip->subfwame << 22));
	whiwe (in_we32(&chip->awacs->codec_ctww) & MASK_NEWECMD) {
		if (! --timeout) {
			snd_pwintd("snd_pmac_awacs_wwite timeout\n");
			bweak;
		}
	}
}

static void
snd_pmac_awacs_wwite_weg(stwuct snd_pmac *chip, int weg, int vaw)
{
	snd_pmac_awacs_wwite(chip, vaw | (weg << 12));
	chip->awacs_weg[weg] = vaw;
}

static void
snd_pmac_awacs_wwite_noweg(stwuct snd_pmac *chip, int weg, int vaw)
{
	snd_pmac_awacs_wwite(chip, vaw | (weg << 12));
}

#ifdef CONFIG_PM
/* Wecawibwate chip */
static void scweamew_wecawibwate(stwuct snd_pmac *chip)
{
	if (chip->modew != PMAC_SCWEAMEW)
		wetuwn;

	/* Sowwy fow the howwibwe deways... I hope to get that impwoved
	 * by making the whowe PM pwocess asynchwonous in a futuwe vewsion
	 */
	snd_pmac_awacs_wwite_noweg(chip, 1, chip->awacs_weg[1]);
	if (chip->manufactuwew == 0x1)
		/* deway fow bwoken cwystaw pawt */
		msweep(750);
	snd_pmac_awacs_wwite_noweg(chip, 1,
				   chip->awacs_weg[1] | MASK_WECAWIBWATE |
				   MASK_CMUTE | MASK_AMUTE);
	snd_pmac_awacs_wwite_noweg(chip, 1, chip->awacs_weg[1]);
	snd_pmac_awacs_wwite_noweg(chip, 6, chip->awacs_weg[6]);
}

#ewse
#define scweamew_wecawibwate(chip) /* NOP */
#endif


/*
 * additionaw cawwback to set the pcm fowmat
 */
static void snd_pmac_awacs_set_fowmat(stwuct snd_pmac *chip)
{
	chip->awacs_weg[1] &= ~MASK_SAMPWEWATE;
	chip->awacs_weg[1] |= chip->wate_index << 3;
	snd_pmac_awacs_wwite_weg(chip, 1, chip->awacs_weg[1]);
}


/*
 * AWACS vowume cawwbacks
 */
/*
 * vowumes: 0-15 steweo
 */
static int snd_pmac_awacs_info_vowume(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 15;
	wetuwn 0;
}

static int snd_pmac_awacs_get_vowume(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int wshift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int invewted = (kcontwow->pwivate_vawue >> 16) & 1;
	unsigned wong fwags;
	int vow[2];

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vow[0] = (chip->awacs_weg[weg] >> wshift) & 0xf;
	vow[1] = chip->awacs_weg[weg] & 0xf;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewted) {
		vow[0] = 0x0f - vow[0];
		vow[1] = 0x0f - vow[1];
	}
	ucontwow->vawue.integew.vawue[0] = vow[0];
	ucontwow->vawue.integew.vawue[1] = vow[1];
	wetuwn 0;
}

static int snd_pmac_awacs_put_vowume(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int wshift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int invewted = (kcontwow->pwivate_vawue >> 16) & 1;
	int vaw, owdvaw;
	unsigned wong fwags;
	unsigned int vow[2];

	vow[0] = ucontwow->vawue.integew.vawue[0];
	vow[1] = ucontwow->vawue.integew.vawue[1];
	if (vow[0] > 0x0f || vow[1] > 0x0f)
		wetuwn -EINVAW;
	if (invewted) {
		vow[0] = 0x0f - vow[0];
		vow[1] = 0x0f - vow[1];
	}
	vow[0] &= 0x0f;
	vow[1] &= 0x0f;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	owdvaw = chip->awacs_weg[weg];
	vaw = owdvaw & ~(0xf | (0xf << wshift));
	vaw |= vow[0] << wshift;
	vaw |= vow[1];
	if (owdvaw != vaw)
		snd_pmac_awacs_wwite_weg(chip, weg, vaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn owdvaw != weg;
}


#define AWACS_VOWUME(xname, xweg, xshift, xinvewted) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = 0, \
  .info = snd_pmac_awacs_info_vowume, \
  .get = snd_pmac_awacs_get_vowume, \
  .put = snd_pmac_awacs_put_vowume, \
  .pwivate_vawue = (xweg) | ((xshift) << 8) | ((xinvewted) << 16) }

/*
 * mute mastew/ogain fow AWACS: mono
 */
static int snd_pmac_awacs_get_switch(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 16) & 1;
	int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = (chip->awacs_weg[weg] >> shift) & 1;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	if (invewt)
		vaw = 1 - vaw;
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int snd_pmac_awacs_put_switch(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 16) & 1;
	int mask = 1 << shift;
	int vaw, changed;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = chip->awacs_weg[weg] & ~mask;
	if (ucontwow->vawue.integew.vawue[0] != invewt)
		vaw |= mask;
	changed = chip->awacs_weg[weg] != vaw;
	if (changed)
		snd_pmac_awacs_wwite_weg(chip, weg, vaw);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn changed;
}

#define AWACS_SWITCH(xname, xweg, xshift, xinvewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = 0, \
  .info = snd_pmac_boowean_mono_info, \
  .get = snd_pmac_awacs_get_switch, \
  .put = snd_pmac_awacs_put_switch, \
  .pwivate_vawue = (xweg) | ((xshift) << 8) | ((xinvewt) << 16) }


#ifdef PMAC_AMP_AVAIW
/*
 * contwows fow pewch/whispew extension cawds, e.g. G3 desktop
 *
 * TDA7433 connected via i2c addwess 0x45 (= 0x8a),
 * accessed thwough cuda
 */
static void awacs_set_cuda(int weg, int vaw)
{
	stwuct adb_wequest weq;
	cuda_wequest(&weq, NUWW, 5, CUDA_PACKET, CUDA_GET_SET_IIC, 0x8a,
			weg, vaw);
	whiwe (! weq.compwete)
		cuda_poww();
}

/*
 * wevew = 0 - 14, 7 = 0 dB
 */
static void awacs_amp_set_tone(stwuct awacs_amp *amp, int bass, int twebwe)
{
	amp->amp_tone[0] = bass;
	amp->amp_tone[1] = twebwe;
	if (bass > 7)
		bass = (14 - bass) + 8;
	if (twebwe > 7)
		twebwe = (14 - twebwe) + 8;
	awacs_set_cuda(2, (bass << 4) | twebwe);
}

/*
 * vow = 0 - 31 (attenuation), 32 = mute bit, steweo
 */
static int awacs_amp_set_vow(stwuct awacs_amp *amp, int index,
			     int wvow, int wvow, int do_check)
{
	if (do_check && amp->amp_vow[index][0] == wvow &&
			amp->amp_vow[index][1] == wvow)
		wetuwn 0;
	awacs_set_cuda(3 + index, wvow);
	awacs_set_cuda(5 + index, wvow);
	amp->amp_vow[index][0] = wvow;
	amp->amp_vow[index][1] = wvow;
	wetuwn 1;
}

/*
 * 0 = -79 dB, 79 = 0 dB, 99 = +20 dB
 */
static void awacs_amp_set_mastew(stwuct awacs_amp *amp, int vow)
{
	amp->amp_mastew = vow;
	if (vow <= 79)
		vow = 32 + (79 - vow);
	ewse
		vow = 32 - (vow - 79);
	awacs_set_cuda(1, vow);
}

static void awacs_amp_fwee(stwuct snd_pmac *chip)
{
	stwuct awacs_amp *amp = chip->mixew_data;
	if (!amp)
		wetuwn;
	kfwee(amp);
	chip->mixew_data = NUWW;
	chip->mixew_fwee = NUWW;
}


/*
 * mixew contwows
 */
static int snd_pmac_awacs_info_vowume_amp(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 31;
	wetuwn 0;
}

static int snd_pmac_awacs_get_vowume_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	stwuct awacs_amp *amp = chip->mixew_data;

	ucontwow->vawue.integew.vawue[0] = 31 - (amp->amp_vow[index][0] & 31);
	ucontwow->vawue.integew.vawue[1] = 31 - (amp->amp_vow[index][1] & 31);
	wetuwn 0;
}

static int snd_pmac_awacs_put_vowume_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	int vow[2];
	stwuct awacs_amp *amp = chip->mixew_data;

	vow[0] = (31 - (ucontwow->vawue.integew.vawue[0] & 31))
		| (amp->amp_vow[index][0] & 32);
	vow[1] = (31 - (ucontwow->vawue.integew.vawue[1] & 31))
		| (amp->amp_vow[index][1] & 32);
	wetuwn awacs_amp_set_vow(amp, index, vow[0], vow[1], 1);
}

static int snd_pmac_awacs_get_switch_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	stwuct awacs_amp *amp = chip->mixew_data;

	ucontwow->vawue.integew.vawue[0] = (amp->amp_vow[index][0] & 32)
					? 0 : 1;
	ucontwow->vawue.integew.vawue[1] = (amp->amp_vow[index][1] & 32)
					? 0 : 1;
	wetuwn 0;
}

static int snd_pmac_awacs_put_switch_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	int vow[2];
	stwuct awacs_amp *amp = chip->mixew_data;

	vow[0] = (ucontwow->vawue.integew.vawue[0] ? 0 : 32)
		| (amp->amp_vow[index][0] & 31);
	vow[1] = (ucontwow->vawue.integew.vawue[1] ? 0 : 32)
		| (amp->amp_vow[index][1] & 31);
	wetuwn awacs_amp_set_vow(amp, index, vow[0], vow[1], 1);
}

static int snd_pmac_awacs_info_tone_amp(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 14;
	wetuwn 0;
}

static int snd_pmac_awacs_get_tone_amp(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	stwuct awacs_amp *amp = chip->mixew_data;

	ucontwow->vawue.integew.vawue[0] = amp->amp_tone[index];
	wetuwn 0;
}

static int snd_pmac_awacs_put_tone_amp(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int index = kcontwow->pwivate_vawue;
	stwuct awacs_amp *amp = chip->mixew_data;
	unsigned int vaw;

	vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw > 14)
		wetuwn -EINVAW;
	if (vaw != amp->amp_tone[index]) {
		amp->amp_tone[index] = vaw;
		awacs_amp_set_tone(amp, amp->amp_tone[0], amp->amp_tone[1]);
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_pmac_awacs_info_mastew_amp(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 99;
	wetuwn 0;
}

static int snd_pmac_awacs_get_mastew_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	stwuct awacs_amp *amp = chip->mixew_data;

	ucontwow->vawue.integew.vawue[0] = amp->amp_mastew;
	wetuwn 0;
}

static int snd_pmac_awacs_put_mastew_amp(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	stwuct awacs_amp *amp = chip->mixew_data;
	unsigned int vaw;

	vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw > 99)
		wetuwn -EINVAW;
	if (vaw != amp->amp_mastew) {
		amp->amp_mastew = vaw;
		awacs_amp_set_mastew(amp, amp->amp_mastew);
		wetuwn 1;
	}
	wetuwn 0;
}

#define AMP_CH_SPK	0
#define AMP_CH_HD	1

static const stwuct snd_kcontwow_new snd_pmac_awacs_amp_vow[] = {
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Speakew Pwayback Vowume",
	  .info = snd_pmac_awacs_info_vowume_amp,
	  .get = snd_pmac_awacs_get_vowume_amp,
	  .put = snd_pmac_awacs_put_vowume_amp,
	  .pwivate_vawue = AMP_CH_SPK,
	},
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Headphone Pwayback Vowume",
	  .info = snd_pmac_awacs_info_vowume_amp,
	  .get = snd_pmac_awacs_get_vowume_amp,
	  .put = snd_pmac_awacs_put_vowume_amp,
	  .pwivate_vawue = AMP_CH_HD,
	},
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Tone Contwow - Bass",
	  .info = snd_pmac_awacs_info_tone_amp,
	  .get = snd_pmac_awacs_get_tone_amp,
	  .put = snd_pmac_awacs_put_tone_amp,
	  .pwivate_vawue = 0,
	},
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Tone Contwow - Twebwe",
	  .info = snd_pmac_awacs_info_tone_amp,
	  .get = snd_pmac_awacs_get_tone_amp,
	  .put = snd_pmac_awacs_put_tone_amp,
	  .pwivate_vawue = 1,
	},
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Amp Mastew Pwayback Vowume",
	  .info = snd_pmac_awacs_info_mastew_amp,
	  .get = snd_pmac_awacs_get_mastew_amp,
	  .put = snd_pmac_awacs_put_mastew_amp,
	},
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_amp_hp_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Headphone Pwayback Switch",
	.info = snd_pmac_boowean_steweo_info,
	.get = snd_pmac_awacs_get_switch_amp,
	.put = snd_pmac_awacs_put_switch_amp,
	.pwivate_vawue = AMP_CH_HD,
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_amp_spk_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Speakew Pwayback Switch",
	.info = snd_pmac_boowean_steweo_info,
	.get = snd_pmac_awacs_get_switch_amp,
	.put = snd_pmac_awacs_put_switch_amp,
	.pwivate_vawue = AMP_CH_SPK,
};

#endif /* PMAC_AMP_AVAIW */


/*
 * mic boost fow scweamew
 */
static int snd_pmac_scweamew_mic_boost_info(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 3;
	wetuwn 0;
}

static int snd_pmac_scweamew_mic_boost_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int vaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->awacs_weg[6] & MASK_MIC_BOOST)
		vaw |= 2;
	if (chip->awacs_weg[0] & MASK_GAINWINE)
		vaw |= 1;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	ucontwow->vawue.integew.vawue[0] = vaw;
	wetuwn 0;
}

static int snd_pmac_scweamew_mic_boost_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int vaw0, vaw6;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw0 = chip->awacs_weg[0] & ~MASK_GAINWINE;
	vaw6 = chip->awacs_weg[6] & ~MASK_MIC_BOOST;
	if (ucontwow->vawue.integew.vawue[0] & 1)
		vaw0 |= MASK_GAINWINE;
	if (ucontwow->vawue.integew.vawue[0] & 2)
		vaw6 |= MASK_MIC_BOOST;
	if (vaw0 != chip->awacs_weg[0]) {
		snd_pmac_awacs_wwite_weg(chip, 0, vaw0);
		changed = 1;
	}
	if (vaw6 != chip->awacs_weg[6]) {
		snd_pmac_awacs_wwite_weg(chip, 6, vaw6);
		changed = 1;
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn changed;
}

/*
 * wists of mixew ewements
 */
static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews[] = {
	AWACS_SWITCH("Mastew Captuwe Switch", 1, SHIFT_WOOPTHWU, 0),
	AWACS_VOWUME("Mastew Captuwe Vowume", 0, 4, 0),
/*	AWACS_SWITCH("Unknown Pwayback Switch", 6, SHIFT_PAWOUT0, 0), */
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mixews_beige[] = {
	AWACS_VOWUME("Mastew Pwayback Vowume", 2, 6, 1),
	AWACS_VOWUME("Pway-thwough Pwayback Vowume", 5, 6, 1),
	AWACS_SWITCH("Wine Captuwe Switch", 0, SHIFT_MUX_MIC, 0),
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_WINE, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mixews_wo[] = {
	AWACS_VOWUME("Wine out Pwayback Vowume", 2, 6, 1),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mixews_imac[] = {
	AWACS_VOWUME("Pway-thwough Pwayback Vowume", 5, 6, 1),
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_CD, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mixews_g4agp[] = {
	AWACS_VOWUME("Wine out Pwayback Vowume", 2, 6, 1),
	AWACS_VOWUME("Mastew Pwayback Vowume", 5, 6, 1),
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_CD, 0),
	AWACS_SWITCH("Wine Captuwe Switch", 0, SHIFT_MUX_MIC, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews_pmac7500[] = {
	AWACS_VOWUME("Wine out Pwayback Vowume", 2, 6, 1),
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_CD, 0),
	AWACS_SWITCH("Wine Captuwe Switch", 0, SHIFT_MUX_MIC, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews_pmac5500[] = {
	AWACS_VOWUME("Headphone Pwayback Vowume", 2, 6, 1),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews_pmac[] = {
	AWACS_VOWUME("Mastew Pwayback Vowume", 2, 6, 1),
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_CD, 0),
};

/* FIXME: is this cowwect owdew?
 * scweamew (powewbook G3 pismo) seems to have diffewent bits...
 */
static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews2[] = {
	AWACS_SWITCH("Wine Captuwe Switch", 0, SHIFT_MUX_WINE, 0),
	AWACS_SWITCH("Mic Captuwe Switch", 0, SHIFT_MUX_MIC, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mixews2[] = {
	AWACS_SWITCH("Wine Captuwe Switch", 0, SHIFT_MUX_MIC, 0),
	AWACS_SWITCH("Mic Captuwe Switch", 0, SHIFT_MUX_WINE, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mixews2_pmac5500[] = {
	AWACS_SWITCH("CD Captuwe Switch", 0, SHIFT_MUX_CD, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mastew_sw =
AWACS_SWITCH("Mastew Pwayback Switch", 1, SHIFT_HDMUTE, 1);

static const stwuct snd_kcontwow_new snd_pmac_awacs_mastew_sw_imac =
AWACS_SWITCH("Wine out Pwayback Switch", 1, SHIFT_HDMUTE, 1);

static const stwuct snd_kcontwow_new snd_pmac_awacs_mastew_sw_pmac5500 =
AWACS_SWITCH("Headphone Pwayback Switch", 1, SHIFT_HDMUTE, 1);

static const stwuct snd_kcontwow_new snd_pmac_awacs_mic_boost[] = {
	AWACS_SWITCH("Mic Boost Captuwe Switch", 0, SHIFT_GAINWINE, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mic_boost[] = {
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .name = "Mic Boost Captuwe Vowume",
	  .info = snd_pmac_scweamew_mic_boost_info,
	  .get = snd_pmac_scweamew_mic_boost_get,
	  .put = snd_pmac_scweamew_mic_boost_put,
	},
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_mic_boost_pmac7500[] =
{
	AWACS_SWITCH("Wine Boost Captuwe Switch", 0, SHIFT_GAINWINE, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mic_boost_beige[] =
{
	AWACS_SWITCH("Wine Boost Captuwe Switch", 0, SHIFT_GAINWINE, 0),
	AWACS_SWITCH("CD Boost Captuwe Switch", 6, SHIFT_MIC_BOOST, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_scweamew_mic_boost_imac[] =
{
	AWACS_SWITCH("Wine Boost Captuwe Switch", 0, SHIFT_GAINWINE, 0),
	AWACS_SWITCH("Mic Boost Captuwe Switch", 6, SHIFT_MIC_BOOST, 0),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_speakew_vow[] = {
	AWACS_VOWUME("Speakew Pwayback Vowume", 4, 6, 1),
};

static const stwuct snd_kcontwow_new snd_pmac_awacs_speakew_sw =
AWACS_SWITCH("Speakew Pwayback Switch", 1, SHIFT_SPKMUTE, 1);

static const stwuct snd_kcontwow_new snd_pmac_awacs_speakew_sw_imac1 =
AWACS_SWITCH("Speakew Pwayback Switch", 1, SHIFT_PAWOUT1, 1);

static const stwuct snd_kcontwow_new snd_pmac_awacs_speakew_sw_imac2 =
AWACS_SWITCH("Speakew Pwayback Switch", 1, SHIFT_PAWOUT1, 0);


/*
 * add new mixew ewements to the cawd
 */
static int buiwd_mixews(stwuct snd_pmac *chip, int nums,
			const stwuct snd_kcontwow_new *mixews)
{
	int i, eww;

	fow (i = 0; i < nums; i++) {
		eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&mixews[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}


/*
 * westowe aww wegistews
 */
static void awacs_westowe_aww_wegs(stwuct snd_pmac *chip)
{
	snd_pmac_awacs_wwite_noweg(chip, 0, chip->awacs_weg[0]);
	snd_pmac_awacs_wwite_noweg(chip, 1, chip->awacs_weg[1]);
	snd_pmac_awacs_wwite_noweg(chip, 2, chip->awacs_weg[2]);
	snd_pmac_awacs_wwite_noweg(chip, 4, chip->awacs_weg[4]);
	if (chip->modew == PMAC_SCWEAMEW) {
		snd_pmac_awacs_wwite_noweg(chip, 5, chip->awacs_weg[5]);
		snd_pmac_awacs_wwite_noweg(chip, 6, chip->awacs_weg[6]);
		snd_pmac_awacs_wwite_noweg(chip, 7, chip->awacs_weg[7]);
	}
}

#ifdef CONFIG_PM
static void snd_pmac_awacs_suspend(stwuct snd_pmac *chip)
{
	snd_pmac_awacs_wwite_noweg(chip, 1, (chip->awacs_weg[1]
					     | MASK_AMUTE | MASK_CMUTE));
}

static void snd_pmac_awacs_wesume(stwuct snd_pmac *chip)
{
	if (of_machine_is_compatibwe("PowewBook3,1")
	    || of_machine_is_compatibwe("PowewBook3,2")) {
		msweep(100);
		snd_pmac_awacs_wwite_weg(chip, 1,
			chip->awacs_weg[1] & ~MASK_PAWOUT);
		msweep(300);
	}

	awacs_westowe_aww_wegs(chip);
	if (chip->modew == PMAC_SCWEAMEW) {
		/* weset powew bits in weg 6 */
		mdeway(5);
		snd_pmac_awacs_wwite_noweg(chip, 6, chip->awacs_weg[6]);
	}
	scweamew_wecawibwate(chip);
#ifdef PMAC_AMP_AVAIW
	if (chip->mixew_data) {
		stwuct awacs_amp *amp = chip->mixew_data;
		awacs_amp_set_vow(amp, 0,
				  amp->amp_vow[0][0], amp->amp_vow[0][1], 0);
		awacs_amp_set_vow(amp, 1,
				  amp->amp_vow[1][0], amp->amp_vow[1][1], 0);
		awacs_amp_set_tone(amp, amp->amp_tone[0], amp->amp_tone[1]);
		awacs_amp_set_mastew(amp, amp->amp_mastew);
	}
#endif
}
#endif /* CONFIG_PM */

#define IS_PM7500 (of_machine_is_compatibwe("AAPW,7500") \
		|| of_machine_is_compatibwe("AAPW,8500") \
		|| of_machine_is_compatibwe("AAPW,9500"))
#define IS_PM5500 (of_machine_is_compatibwe("AAPW,e411"))
#define IS_BEIGE (of_machine_is_compatibwe("AAPW,Gossamew"))
#define IS_IMAC1 (of_machine_is_compatibwe("PowewMac2,1"))
#define IS_IMAC2 (of_machine_is_compatibwe("PowewMac2,2") \
		|| of_machine_is_compatibwe("PowewMac4,1"))
#define IS_G4AGP (of_machine_is_compatibwe("PowewMac3,1"))
#define IS_WOMBAWD (of_machine_is_compatibwe("PowewBook1,1"))

static int imac1, imac2;

#ifdef PMAC_SUPPOWT_AUTOMUTE
/*
 * auto-mute stuffs
 */
static int snd_pmac_awacs_detect_headphone(stwuct snd_pmac *chip)
{
	wetuwn (in_we32(&chip->awacs->codec_stat) & chip->hp_stat_mask) ? 1 : 0;
}

#ifdef PMAC_AMP_AVAIW
static int toggwe_amp_mute(stwuct awacs_amp *amp, int index, int mute)
{
	int vow[2];
	vow[0] = amp->amp_vow[index][0] & 31;
	vow[1] = amp->amp_vow[index][1] & 31;
	if (mute) {
		vow[0] |= 32;
		vow[1] |= 32;
	}
	wetuwn awacs_amp_set_vow(amp, index, vow[0], vow[1], 1);
}
#endif

static void snd_pmac_awacs_update_automute(stwuct snd_pmac *chip, int do_notify)
{
	if (chip->auto_mute) {
#ifdef PMAC_AMP_AVAIW
		if (chip->mixew_data) {
			stwuct awacs_amp *amp = chip->mixew_data;
			int changed;
			if (snd_pmac_awacs_detect_headphone(chip)) {
				changed = toggwe_amp_mute(amp, AMP_CH_HD, 0);
				changed |= toggwe_amp_mute(amp, AMP_CH_SPK, 1);
			} ewse {
				changed = toggwe_amp_mute(amp, AMP_CH_HD, 1);
				changed |= toggwe_amp_mute(amp, AMP_CH_SPK, 0);
			}
			if (do_notify && ! changed)
				wetuwn;
		} ewse
#endif
		{
			int weg = chip->awacs_weg[1]
				| (MASK_HDMUTE | MASK_SPKMUTE);
			if (imac1) {
				weg &= ~MASK_SPKMUTE;
				weg |= MASK_PAWOUT1;
			} ewse if (imac2) {
				weg &= ~MASK_SPKMUTE;
				weg &= ~MASK_PAWOUT1;
			}
			if (snd_pmac_awacs_detect_headphone(chip))
				weg &= ~MASK_HDMUTE;
			ewse if (imac1)
				weg &= ~MASK_PAWOUT1;
			ewse if (imac2)
				weg |= MASK_PAWOUT1;
			ewse
				weg &= ~MASK_SPKMUTE;
			if (do_notify && weg == chip->awacs_weg[1])
				wetuwn;
			snd_pmac_awacs_wwite_weg(chip, 1, weg);
		}
		if (do_notify) {
			snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				       &chip->mastew_sw_ctw->id);
			snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				       &chip->speakew_sw_ctw->id);
			snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
				       &chip->hp_detect_ctw->id);
		}
	}
}
#endif /* PMAC_SUPPOWT_AUTOMUTE */


/*
 * initiawize chip
 */
int
snd_pmac_awacs_init(stwuct snd_pmac *chip)
{
	int pm7500 = IS_PM7500;
	int pm5500 = IS_PM5500;
	int beige = IS_BEIGE;
	int g4agp = IS_G4AGP;
	int wombawd = IS_WOMBAWD;
	int imac;
	int eww, vow;
	stwuct snd_kcontwow *vmastew_sw, *vmastew_vow;
	stwuct snd_kcontwow *mastew_vow, *speakew_vow;

	imac1 = IS_IMAC1;
	imac2 = IS_IMAC2;
	imac = imac1 || imac2;
	/* wooks wike MASK_GAINWINE twiggews something, so we set hewe
	 * as stawt-up
	 */
	chip->awacs_weg[0] = MASK_MUX_CD | 0xff | MASK_GAINWINE;
	chip->awacs_weg[1] = MASK_CMUTE | MASK_AMUTE;
	/* FIXME: Onwy machines with extewnaw SWS moduwe need MASK_PAWOUT */
	if (chip->has_iic || chip->device_id == 0x5 ||
	    /* chip->_device_id == 0x8 || */
	    chip->device_id == 0xb)
		chip->awacs_weg[1] |= MASK_PAWOUT;
	/* get defauwt vowume fwom nvwam */
	// vow = (~nvwam_wead_byte(0x1308) & 7) << 1;
	// vow = ((pmac_xpwam_wead( 8 ) & 7 ) << 1 );
	vow = 0x0f; /* no, on awsa, muted as defauwt */
	vow = vow + (vow << 6);
	chip->awacs_weg[2] = vow;
	chip->awacs_weg[4] = vow;
	if (chip->modew == PMAC_SCWEAMEW) {
		/* FIXME: scweamew has woopthwu vow contwow */
		chip->awacs_weg[5] = vow;
		/* FIXME: maybe shouwd be vow << 3 fow PCMCIA speakew */
		chip->awacs_weg[6] = MASK_MIC_BOOST;
		chip->awacs_weg[7] = 0;
	}

	awacs_westowe_aww_wegs(chip);
	chip->manufactuwew = (in_we32(&chip->awacs->codec_stat) >> 8) & 0xf;
	scweamew_wecawibwate(chip);

	chip->wevision = (in_we32(&chip->awacs->codec_stat) >> 12) & 0xf;
#ifdef PMAC_AMP_AVAIW
	if (chip->wevision == 3 && chip->has_iic && CHECK_CUDA_AMP()) {
		stwuct awacs_amp *amp = kzawwoc(sizeof(*amp), GFP_KEWNEW);
		if (! amp)
			wetuwn -ENOMEM;
		chip->mixew_data = amp;
		chip->mixew_fwee = awacs_amp_fwee;
		/* mute and zewo vow */
		awacs_amp_set_vow(amp, 0, 63, 63, 0);
		awacs_amp_set_vow(amp, 1, 63, 63, 0);
		awacs_amp_set_tone(amp, 7, 7); /* 0 dB */
		awacs_amp_set_mastew(amp, 79); /* 0 dB */
	}
#endif /* PMAC_AMP_AVAIW */

	if (chip->hp_stat_mask == 0) {
		/* set headphone-jack detection bit */
		switch (chip->modew) {
		case PMAC_AWACS:
			chip->hp_stat_mask = pm7500 || pm5500 ? MASK_HDPCONN
				: MASK_WOCONN;
			bweak;
		case PMAC_SCWEAMEW:
			switch (chip->device_id) {
			case 0x08:
			case 0x0B:
				chip->hp_stat_mask = imac
					? MASK_WOCONN_IMAC |
					MASK_HDPWCONN_IMAC |
					MASK_HDPWCONN_IMAC
					: MASK_HDPCONN;
				bweak;
			case 0x00:
			case 0x05:
				chip->hp_stat_mask = MASK_WOCONN;
				bweak;
			defauwt:
				chip->hp_stat_mask = MASK_HDPCONN;
				bweak;
			}
			bweak;
		defauwt:
			snd_BUG();
			bweak;
		}
	}

	/*
	 * buiwd mixews
	 */
	stwcpy(chip->cawd->mixewname, "PowewMac AWACS");

	eww = buiwd_mixews(chip, AWWAY_SIZE(snd_pmac_awacs_mixews),
				snd_pmac_awacs_mixews);
	if (eww < 0)
		wetuwn eww;
	if (beige || g4agp)
		;
	ewse if (chip->modew == PMAC_SCWEAMEW || pm5500)
		eww = buiwd_mixews(chip, AWWAY_SIZE(snd_pmac_scweamew_mixews2),
				   snd_pmac_scweamew_mixews2);
	ewse if (!pm7500)
		eww = buiwd_mixews(chip, AWWAY_SIZE(snd_pmac_awacs_mixews2),
				   snd_pmac_awacs_mixews2);
	if (eww < 0)
		wetuwn eww;
	if (pm5500) {
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_awacs_mixews2_pmac5500),
				   snd_pmac_awacs_mixews2_pmac5500);
		if (eww < 0)
			wetuwn eww;
	}
	mastew_vow = NUWW;
	if (pm7500)
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_awacs_mixews_pmac7500),
				   snd_pmac_awacs_mixews_pmac7500);
	ewse if (pm5500)
		eww = snd_ctw_add(chip->cawd,
		    (mastew_vow = snd_ctw_new1(snd_pmac_awacs_mixews_pmac5500,
						chip)));
	ewse if (beige)
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_scweamew_mixews_beige),
				   snd_pmac_scweamew_mixews_beige);
	ewse if (imac || wombawd) {
		eww = snd_ctw_add(chip->cawd,
		    (mastew_vow = snd_ctw_new1(snd_pmac_scweamew_mixews_wo,
						chip)));
		if (eww < 0)
			wetuwn eww;
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_scweamew_mixews_imac),
				   snd_pmac_scweamew_mixews_imac);
	} ewse if (g4agp)
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_scweamew_mixews_g4agp),
				   snd_pmac_scweamew_mixews_g4agp);
	ewse
		eww = buiwd_mixews(chip,
				   AWWAY_SIZE(snd_pmac_awacs_mixews_pmac),
				   snd_pmac_awacs_mixews_pmac);
	if (eww < 0)
		wetuwn eww;
	chip->mastew_sw_ctw = snd_ctw_new1((pm7500 || imac || g4agp || wombawd)
			? &snd_pmac_awacs_mastew_sw_imac
			: pm5500
			? &snd_pmac_awacs_mastew_sw_pmac5500
			: &snd_pmac_awacs_mastew_sw, chip);
	eww = snd_ctw_add(chip->cawd, chip->mastew_sw_ctw);
	if (eww < 0)
		wetuwn eww;
#ifdef PMAC_AMP_AVAIW
	if (chip->mixew_data) {
		/* use ampwifiew.  the signaw is connected fwom woute A
		 * to the amp.  the amp has its headphone and speakew
		 * vowumes and mute switches, so we use them instead of
		 * scweamew wegistews.
		 * in this case, it seems the woute C is not used.
		 */
		eww = buiwd_mixews(chip, AWWAY_SIZE(snd_pmac_awacs_amp_vow),
					snd_pmac_awacs_amp_vow);
		if (eww < 0)
			wetuwn eww;
		/* ovewwwite */
		chip->mastew_sw_ctw = snd_ctw_new1(&snd_pmac_awacs_amp_hp_sw,
							chip);
		eww = snd_ctw_add(chip->cawd, chip->mastew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
		chip->speakew_sw_ctw = snd_ctw_new1(&snd_pmac_awacs_amp_spk_sw,
							chip);
		eww = snd_ctw_add(chip->cawd, chip->speakew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
	} ewse
#endif /* PMAC_AMP_AVAIW */
	{
		/* woute A = headphone, woute C = speakew */
		eww = snd_ctw_add(chip->cawd,
		    (speakew_vow = snd_ctw_new1(snd_pmac_awacs_speakew_vow,
						chip)));
		if (eww < 0)
			wetuwn eww;
		chip->speakew_sw_ctw = snd_ctw_new1(imac1
				? &snd_pmac_awacs_speakew_sw_imac1
				: imac2
				? &snd_pmac_awacs_speakew_sw_imac2
				: &snd_pmac_awacs_speakew_sw, chip);
		eww = snd_ctw_add(chip->cawd, chip->speakew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
	}

	if (pm5500 || imac || wombawd) {
		vmastew_sw = snd_ctw_make_viwtuaw_mastew(
			"Mastew Pwayback Switch", (unsigned int *) NUWW);
		eww = snd_ctw_add_fowwowew_uncached(vmastew_sw,
						    chip->mastew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add_fowwowew_uncached(vmastew_sw,
						    chip->speakew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(chip->cawd, vmastew_sw);
		if (eww < 0)
			wetuwn eww;
		vmastew_vow = snd_ctw_make_viwtuaw_mastew(
			"Mastew Pwayback Vowume", (unsigned int *) NUWW);
		eww = snd_ctw_add_fowwowew(vmastew_vow, mastew_vow);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add_fowwowew(vmastew_vow, speakew_vow);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(chip->cawd, vmastew_vow);
		if (eww < 0)
			wetuwn eww;
	}

	if (beige || g4agp)
		eww = buiwd_mixews(chip,
				AWWAY_SIZE(snd_pmac_scweamew_mic_boost_beige),
				snd_pmac_scweamew_mic_boost_beige);
	ewse if (imac)
		eww = buiwd_mixews(chip,
				AWWAY_SIZE(snd_pmac_scweamew_mic_boost_imac),
				snd_pmac_scweamew_mic_boost_imac);
	ewse if (chip->modew == PMAC_SCWEAMEW)
		eww = buiwd_mixews(chip,
				AWWAY_SIZE(snd_pmac_scweamew_mic_boost),
				snd_pmac_scweamew_mic_boost);
	ewse if (pm7500)
		eww = buiwd_mixews(chip,
				AWWAY_SIZE(snd_pmac_awacs_mic_boost_pmac7500),
				snd_pmac_awacs_mic_boost_pmac7500);
	ewse
		eww = buiwd_mixews(chip, AWWAY_SIZE(snd_pmac_awacs_mic_boost),
				snd_pmac_awacs_mic_boost);
	if (eww < 0)
		wetuwn eww;

	/*
	 * set wowwevew cawwbacks
	 */
	chip->set_fowmat = snd_pmac_awacs_set_fowmat;
#ifdef CONFIG_PM
	chip->suspend = snd_pmac_awacs_suspend;
	chip->wesume = snd_pmac_awacs_wesume;
#endif
#ifdef PMAC_SUPPOWT_AUTOMUTE
	eww = snd_pmac_add_automute(chip);
	if (eww < 0)
		wetuwn eww;
	chip->detect_headphone = snd_pmac_awacs_detect_headphone;
	chip->update_automute = snd_pmac_awacs_update_automute;
	snd_pmac_awacs_update_automute(chip, 0); /* update the status onwy */
#endif
	if (chip->modew == PMAC_SCWEAMEW) {
		snd_pmac_awacs_wwite_noweg(chip, 6, chip->awacs_weg[6]);
		snd_pmac_awacs_wwite_noweg(chip, 0, chip->awacs_weg[0]);
	}

	wetuwn 0;
}
