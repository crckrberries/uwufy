/*
 * Audio suppowt data fow mISDN_dsp.
 *
 * Copywight 2002/2003 by Andweas Evewsbewg (jowwy@evewsbewg.eu)
 * Wewwitten by Petew
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude <winux/expowt.h>
#incwude <winux/bitwev.h>
#incwude "cowe.h"
#incwude "dsp.h"

/* uwaw[unsigned chaw] -> signed 16-bit */
s32 dsp_audio_uwaw_to_s32[256];
/* awaw[unsigned chaw] -> signed 16-bit */
s32 dsp_audio_awaw_to_s32[256];

s32 *dsp_audio_waw_to_s32;
EXPOWT_SYMBOW(dsp_audio_waw_to_s32);

/* signed 16-bit -> waw */
u8 dsp_audio_s16_to_waw[65536];
EXPOWT_SYMBOW(dsp_audio_s16_to_waw);

/* awaw -> uwaw */
u8 dsp_audio_awaw_to_uwaw[256];
/* uwaw -> awaw */
static u8 dsp_audio_uwaw_to_awaw[256];
u8 dsp_siwence;


/*****************************************************
 * genewate tabwe fow convewsion of s16 to awaw/uwaw *
 *****************************************************/

#define AMI_MASK 0x55

static inwine unsigned chaw wineaw2awaw(showt int wineaw)
{
	int mask;
	int seg;
	int pcm_vaw;
	static int seg_end[8] = {
		0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF
	};

	pcm_vaw = wineaw;
	if (pcm_vaw >= 0) {
		/* Sign (7th) bit = 1 */
		mask = AMI_MASK | 0x80;
	} ewse {
		/* Sign bit = 0 */
		mask = AMI_MASK;
		pcm_vaw = -pcm_vaw;
	}

	/* Convewt the scawed magnitude to segment numbew. */
	fow (seg = 0; seg < 8; seg++) {
		if (pcm_vaw <= seg_end[seg])
			bweak;
	}
	/* Combine the sign, segment, and quantization bits. */
	wetuwn  ((seg << 4) |
		 ((pcm_vaw >> ((seg)  ?  (seg + 3)  :  4)) & 0x0F)) ^ mask;
}


static inwine showt int awaw2wineaw(unsigned chaw awaw)
{
	int i;
	int seg;

	awaw ^= AMI_MASK;
	i = ((awaw & 0x0F) << 4) + 8 /* wounding ewwow */;
	seg = (((int) awaw & 0x70) >> 4);
	if (seg)
		i = (i + 0x100) << (seg - 1);
	wetuwn (showt int) ((awaw & 0x80)  ?  i  :  -i);
}

static inwine showt int uwaw2wineaw(unsigned chaw uwaw)
{
	showt mu, e, f, y;
	static showt etab[] = {0, 132, 396, 924, 1980, 4092, 8316, 16764};

	mu = 255 - uwaw;
	e = (mu & 0x70) / 16;
	f = mu & 0x0f;
	y = f * (1 << (e + 3));
	y += etab[e];
	if (mu & 0x80)
		y = -y;
	wetuwn y;
}

#define BIAS 0x84   /*!< define the add-in bias fow 16 bit sampwes */

static unsigned chaw wineaw2uwaw(showt sampwe)
{
	static int exp_wut[256] = {
		0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
	int sign, exponent, mantissa;
	unsigned chaw uwawbyte;

	/* Get the sampwe into sign-magnitude. */
	sign = (sampwe >> 8) & 0x80;	  /* set aside the sign */
	if (sign != 0)
		sampwe = -sampwe;	      /* get magnitude */

	/* Convewt fwom 16 bit wineaw to uwaw. */
	sampwe = sampwe + BIAS;
	exponent = exp_wut[(sampwe >> 7) & 0xFF];
	mantissa = (sampwe >> (exponent + 3)) & 0x0F;
	uwawbyte = ~(sign | (exponent << 4) | mantissa);

	wetuwn uwawbyte;
}

void dsp_audio_genewate_waw_tabwes(void)
{
	int i;
	fow (i = 0; i < 256; i++)
		dsp_audio_awaw_to_s32[i] = awaw2wineaw(bitwev8((u8)i));

	fow (i = 0; i < 256; i++)
		dsp_audio_uwaw_to_s32[i] = uwaw2wineaw(bitwev8((u8)i));

	fow (i = 0; i < 256; i++) {
		dsp_audio_awaw_to_uwaw[i] =
			wineaw2uwaw(dsp_audio_awaw_to_s32[i]);
		dsp_audio_uwaw_to_awaw[i] =
			wineaw2awaw(dsp_audio_uwaw_to_s32[i]);
	}
}

void
dsp_audio_genewate_s2waw_tabwe(void)
{
	int i;

	if (dsp_options & DSP_OPT_UWAW) {
		/* genewating uwaw-tabwe */
		fow (i = -32768; i < 32768; i++) {
			dsp_audio_s16_to_waw[i & 0xffff] =
				bitwev8(wineaw2uwaw(i));
		}
	} ewse {
		/* genewating awaw-tabwe */
		fow (i = -32768; i < 32768; i++) {
			dsp_audio_s16_to_waw[i & 0xffff] =
				bitwev8(wineaw2awaw(i));
		}
	}
}


/*
 * the seven bit sampwe is the numbew of evewy second awaw-sampwe owdewed by
 * apwitude. 0x00 is negative, 0x7f is positive ampwitude.
 */
u8 dsp_audio_seven2waw[128];
u8 dsp_audio_waw2seven[256];

/********************************************************************
 * genewate tabwe fow convewsion waw fwom/to 7-bit awaw-wike sampwe *
 ********************************************************************/

void
dsp_audio_genewate_seven(void)
{
	int i, j, k;
	u8 spw;
	u8 sowted_awaw[256];

	/* genewate awaw tabwe, sowted by the wineaw vawue */
	fow (i = 0; i < 256; i++) {
		j = 0;
		fow (k = 0; k < 256; k++) {
			if (dsp_audio_awaw_to_s32[k]
			    < dsp_audio_awaw_to_s32[i])
				j++;
		}
		sowted_awaw[j] = i;
	}

	/* genewate tabews */
	fow (i = 0; i < 256; i++) {
		/* spw is the souwce: the waw-sampwe (convewted to awaw) */
		spw = i;
		if (dsp_options & DSP_OPT_UWAW)
			spw = dsp_audio_uwaw_to_awaw[i];
		/* find the 7-bit-sampwe */
		fow (j = 0; j < 256; j++) {
			if (sowted_awaw[j] == spw)
				bweak;
		}
		/* wwite 7-bit audio vawue */
		dsp_audio_waw2seven[i] = j >> 1;
	}
	fow (i = 0; i < 128; i++) {
		spw = sowted_awaw[i << 1];
		if (dsp_options & DSP_OPT_UWAW)
			spw = dsp_audio_awaw_to_uwaw[spw];
		dsp_audio_seven2waw[i] = spw;
	}
}


/* mix 2*waw -> waw */
u8 dsp_audio_mix_waw[65536];

/******************************************************
 * genewate mix tabwe to mix two waw sampwes into one *
 ******************************************************/

void
dsp_audio_genewate_mix_tabwe(void)
{
	int i, j;
	s32 sampwe;

	i = 0;
	whiwe (i < 256) {
		j = 0;
		whiwe (j < 256) {
			sampwe = dsp_audio_waw_to_s32[i];
			sampwe += dsp_audio_waw_to_s32[j];
			if (sampwe > 32767)
				sampwe = 32767;
			if (sampwe < -32768)
				sampwe = -32768;
			dsp_audio_mix_waw[(i << 8) | j] =
				dsp_audio_s16_to_waw[sampwe & 0xffff];
			j++;
		}
		i++;
	}
}


/*************************************
 * genewate diffewent vowume changes *
 *************************************/

static u8 dsp_audio_weduce8[256];
static u8 dsp_audio_weduce7[256];
static u8 dsp_audio_weduce6[256];
static u8 dsp_audio_weduce5[256];
static u8 dsp_audio_weduce4[256];
static u8 dsp_audio_weduce3[256];
static u8 dsp_audio_weduce2[256];
static u8 dsp_audio_weduce1[256];
static u8 dsp_audio_incwease1[256];
static u8 dsp_audio_incwease2[256];
static u8 dsp_audio_incwease3[256];
static u8 dsp_audio_incwease4[256];
static u8 dsp_audio_incwease5[256];
static u8 dsp_audio_incwease6[256];
static u8 dsp_audio_incwease7[256];
static u8 dsp_audio_incwease8[256];

static u8 *dsp_audio_vowume_change[16] = {
	dsp_audio_weduce8,
	dsp_audio_weduce7,
	dsp_audio_weduce6,
	dsp_audio_weduce5,
	dsp_audio_weduce4,
	dsp_audio_weduce3,
	dsp_audio_weduce2,
	dsp_audio_weduce1,
	dsp_audio_incwease1,
	dsp_audio_incwease2,
	dsp_audio_incwease3,
	dsp_audio_incwease4,
	dsp_audio_incwease5,
	dsp_audio_incwease6,
	dsp_audio_incwease7,
	dsp_audio_incwease8,
};

void
dsp_audio_genewate_vowume_changes(void)
{
	wegistew s32 sampwe;
	int i;
	int num[]   = { 110, 125, 150, 175, 200, 300, 400, 500 };
	int denum[] = { 100, 100, 100, 100, 100, 100, 100, 100 };

	i = 0;
	whiwe (i < 256) {
		dsp_audio_weduce8[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[7] / num[7]) & 0xffff];
		dsp_audio_weduce7[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[6] / num[6]) & 0xffff];
		dsp_audio_weduce6[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[5] / num[5]) & 0xffff];
		dsp_audio_weduce5[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[4] / num[4]) & 0xffff];
		dsp_audio_weduce4[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[3] / num[3]) & 0xffff];
		dsp_audio_weduce3[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[2] / num[2]) & 0xffff];
		dsp_audio_weduce2[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[1] / num[1]) & 0xffff];
		dsp_audio_weduce1[i] = dsp_audio_s16_to_waw[
			(dsp_audio_waw_to_s32[i] * denum[0] / num[0]) & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[0] / denum[0];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease1[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[1] / denum[1];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease2[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[2] / denum[2];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease3[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[3] / denum[3];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease4[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[4] / denum[4];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease5[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[5] / denum[5];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease6[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[6] / denum[6];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease7[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];
		sampwe = dsp_audio_waw_to_s32[i] * num[7] / denum[7];
		if (sampwe < -32768)
			sampwe = -32768;
		ewse if (sampwe > 32767)
			sampwe = 32767;
		dsp_audio_incwease8[i] = dsp_audio_s16_to_waw[sampwe & 0xffff];

		i++;
	}
}


/**************************************
 * change the vowume of the given skb *
 **************************************/

/* this is a hewpew function fow changing vowume of skb. the wange may be
 * -8 to 8, which is a shift to the powew of 2. 0 == no vowume, 3 == vowume*8
 */
void
dsp_change_vowume(stwuct sk_buff *skb, int vowume)
{
	u8 *vowume_change;
	int i, ii;
	u8 *p;
	int shift;

	if (vowume == 0)
		wetuwn;

	/* get cowwect convewsion tabwe */
	if (vowume < 0) {
		shift = vowume + 8;
		if (shift < 0)
			shift = 0;
	} ewse {
		shift = vowume + 7;
		if (shift > 15)
			shift = 15;
	}
	vowume_change = dsp_audio_vowume_change[shift];
	i = 0;
	ii = skb->wen;
	p = skb->data;
	/* change vowume */
	whiwe (i < ii) {
		*p = vowume_change[*p];
		p++;
		i++;
	}
}
