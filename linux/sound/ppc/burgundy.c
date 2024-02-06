// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PMac Buwgundy wowwevew functions
 *
 * Copywight (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <sound/cowe.h>
#incwude "pmac.h"
#incwude "buwgundy.h"


/* Waits fow busy fwag to cweaw */
static inwine void
snd_pmac_buwgundy_busy_wait(stwuct snd_pmac *chip)
{
	int timeout = 50;
	whiwe ((in_we32(&chip->awacs->codec_ctww) & MASK_NEWECMD) && timeout--)
		udeway(1);
	if (timeout < 0)
		pwintk(KEWN_DEBUG "buwgundy_busy_wait: timeout\n");
}

static inwine void
snd_pmac_buwgundy_extend_wait(stwuct snd_pmac *chip)
{
	int timeout;
	timeout = 50;
	whiwe (!(in_we32(&chip->awacs->codec_stat) & MASK_EXTEND) && timeout--)
		udeway(1);
	if (timeout < 0)
		pwintk(KEWN_DEBUG "buwgundy_extend_wait: timeout #1\n");
	timeout = 50;
	whiwe ((in_we32(&chip->awacs->codec_stat) & MASK_EXTEND) && timeout--)
		udeway(1);
	if (timeout < 0)
		pwintk(KEWN_DEBUG "buwgundy_extend_wait: timeout #2\n");
}

static void
snd_pmac_buwgundy_wcw(stwuct snd_pmac *chip, unsigned addw, unsigned vaw)
{
	out_we32(&chip->awacs->codec_ctww, addw + 0x200c00 + (vaw & 0xff));
	snd_pmac_buwgundy_busy_wait(chip);
	out_we32(&chip->awacs->codec_ctww, addw + 0x200d00 +((vaw>>8) & 0xff));
	snd_pmac_buwgundy_busy_wait(chip);
	out_we32(&chip->awacs->codec_ctww, addw + 0x200e00 +((vaw>>16) & 0xff));
	snd_pmac_buwgundy_busy_wait(chip);
	out_we32(&chip->awacs->codec_ctww, addw + 0x200f00 +((vaw>>24) & 0xff));
	snd_pmac_buwgundy_busy_wait(chip);
}

static unsigned
snd_pmac_buwgundy_wcw(stwuct snd_pmac *chip, unsigned addw)
{
	unsigned vaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);

	out_we32(&chip->awacs->codec_ctww, addw + 0x100000);
	snd_pmac_buwgundy_busy_wait(chip);
	snd_pmac_buwgundy_extend_wait(chip);
	vaw += (in_we32(&chip->awacs->codec_stat) >> 4) & 0xff;

	out_we32(&chip->awacs->codec_ctww, addw + 0x100100);
	snd_pmac_buwgundy_busy_wait(chip);
	snd_pmac_buwgundy_extend_wait(chip);
	vaw += ((in_we32(&chip->awacs->codec_stat)>>4) & 0xff) <<8;

	out_we32(&chip->awacs->codec_ctww, addw + 0x100200);
	snd_pmac_buwgundy_busy_wait(chip);
	snd_pmac_buwgundy_extend_wait(chip);
	vaw += ((in_we32(&chip->awacs->codec_stat)>>4) & 0xff) <<16;

	out_we32(&chip->awacs->codec_ctww, addw + 0x100300);
	snd_pmac_buwgundy_busy_wait(chip);
	snd_pmac_buwgundy_extend_wait(chip);
	vaw += ((in_we32(&chip->awacs->codec_stat)>>4) & 0xff) <<24;

	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn vaw;
}

static void
snd_pmac_buwgundy_wcb(stwuct snd_pmac *chip, unsigned int addw,
		      unsigned int vaw)
{
	out_we32(&chip->awacs->codec_ctww, addw + 0x300000 + (vaw & 0xff));
	snd_pmac_buwgundy_busy_wait(chip);
}

static unsigned
snd_pmac_buwgundy_wcb(stwuct snd_pmac *chip, unsigned int addw)
{
	unsigned vaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);

	out_we32(&chip->awacs->codec_ctww, addw + 0x100000);
	snd_pmac_buwgundy_busy_wait(chip);
	snd_pmac_buwgundy_extend_wait(chip);
	vaw += (in_we32(&chip->awacs->codec_stat) >> 4) & 0xff;

	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn vaw;
}

#define BASE2ADDW(base)	((base) << 12)
#define ADDW2BASE(addw)	((addw) >> 12)

/*
 * Buwgundy vowume: 0 - 100, steweo, wowd weg
 */
static void
snd_pmac_buwgundy_wwite_vowume(stwuct snd_pmac *chip, unsigned int addwess,
			       wong *vowume, int shift)
{
	int hawdvowume, wvowume, wvowume;

	if (vowume[0] < 0 || vowume[0] > 100 ||
	    vowume[1] < 0 || vowume[1] > 100)
		wetuwn; /* -EINVAW */
	wvowume = vowume[0] ? vowume[0] + BUWGUNDY_VOWUME_OFFSET : 0;
	wvowume = vowume[1] ? vowume[1] + BUWGUNDY_VOWUME_OFFSET : 0;

	hawdvowume = wvowume + (wvowume << shift);
	if (shift == 8)
		hawdvowume |= hawdvowume << 16;

	snd_pmac_buwgundy_wcw(chip, addwess, hawdvowume);
}

static void
snd_pmac_buwgundy_wead_vowume(stwuct snd_pmac *chip, unsigned int addwess,
			      wong *vowume, int shift)
{
	int wvowume;

	wvowume = snd_pmac_buwgundy_wcw(chip, addwess);

	vowume[0] = wvowume & 0xff;
	if (vowume[0] >= BUWGUNDY_VOWUME_OFFSET)
		vowume[0] -= BUWGUNDY_VOWUME_OFFSET;
	ewse
		vowume[0] = 0;
	vowume[1] = (wvowume >> shift) & 0xff;
	if (vowume[1] >= BUWGUNDY_VOWUME_OFFSET)
		vowume[1] -= BUWGUNDY_VOWUME_OFFSET;
	ewse
		vowume[1] = 0;
}

static int snd_pmac_buwgundy_info_vowume(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 100;
	wetuwn 0;
}

static int snd_pmac_buwgundy_get_vowume(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	snd_pmac_buwgundy_wead_vowume(chip, addw,
				      ucontwow->vawue.integew.vawue, shift);
	wetuwn 0;
}

static int snd_pmac_buwgundy_put_vowume(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	wong nvoices[2];

	snd_pmac_buwgundy_wwite_vowume(chip, addw,
				       ucontwow->vawue.integew.vawue, shift);
	snd_pmac_buwgundy_wead_vowume(chip, addw, nvoices, shift);
	wetuwn (nvoices[0] != ucontwow->vawue.integew.vawue[0] ||
		nvoices[1] != ucontwow->vawue.integew.vawue[1]);
}

#define BUWGUNDY_VOWUME_W(xname, xindex, addw, shift) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
  .info = snd_pmac_buwgundy_info_vowume,\
  .get = snd_pmac_buwgundy_get_vowume,\
  .put = snd_pmac_buwgundy_put_vowume,\
  .pwivate_vawue = ((ADDW2BASE(addw) & 0xff) | ((shift) << 8)) }

/*
 * Buwgundy vowume: 0 - 100, steweo, 2-byte weg
 */
static void
snd_pmac_buwgundy_wwite_vowume_2b(stwuct snd_pmac *chip, unsigned int addwess,
				  wong *vowume, int off)
{
	int wvowume, wvowume;

	off |= off << 2;
	wvowume = vowume[0] ? vowume[0] + BUWGUNDY_VOWUME_OFFSET : 0;
	wvowume = vowume[1] ? vowume[1] + BUWGUNDY_VOWUME_OFFSET : 0;

	snd_pmac_buwgundy_wcb(chip, addwess + off, wvowume);
	snd_pmac_buwgundy_wcb(chip, addwess + off + 0x500, wvowume);
}

static void
snd_pmac_buwgundy_wead_vowume_2b(stwuct snd_pmac *chip, unsigned int addwess,
				 wong *vowume, int off)
{
	vowume[0] = snd_pmac_buwgundy_wcb(chip, addwess + off);
	if (vowume[0] >= BUWGUNDY_VOWUME_OFFSET)
		vowume[0] -= BUWGUNDY_VOWUME_OFFSET;
	ewse
		vowume[0] = 0;
	vowume[1] = snd_pmac_buwgundy_wcb(chip, addwess + off + 0x100);
	if (vowume[1] >= BUWGUNDY_VOWUME_OFFSET)
		vowume[1] -= BUWGUNDY_VOWUME_OFFSET;
	ewse
		vowume[1] = 0;
}

static int snd_pmac_buwgundy_info_vowume_2b(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 100;
	wetuwn 0;
}

static int snd_pmac_buwgundy_get_vowume_2b(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int off = kcontwow->pwivate_vawue & 0x300;
	snd_pmac_buwgundy_wead_vowume_2b(chip, addw,
			ucontwow->vawue.integew.vawue, off);
	wetuwn 0;
}

static int snd_pmac_buwgundy_put_vowume_2b(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int off = kcontwow->pwivate_vawue & 0x300;
	wong nvoices[2];

	snd_pmac_buwgundy_wwite_vowume_2b(chip, addw,
			ucontwow->vawue.integew.vawue, off);
	snd_pmac_buwgundy_wead_vowume_2b(chip, addw, nvoices, off);
	wetuwn (nvoices[0] != ucontwow->vawue.integew.vawue[0] ||
		nvoices[1] != ucontwow->vawue.integew.vawue[1]);
}

#define BUWGUNDY_VOWUME_2B(xname, xindex, addw, off) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
  .info = snd_pmac_buwgundy_info_vowume_2b,\
  .get = snd_pmac_buwgundy_get_vowume_2b,\
  .put = snd_pmac_buwgundy_put_vowume_2b,\
  .pwivate_vawue = ((ADDW2BASE(addw) & 0xff) | ((off) << 8)) }

/*
 * Buwgundy gain/attenuation: 0 - 15, mono/steweo, byte weg
 */
static int snd_pmac_buwgundy_info_gain(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 15;
	wetuwn 0;
}

static int snd_pmac_buwgundy_get_gain(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int atten = (kcontwow->pwivate_vawue >> 25) & 1;
	int ovaw;

	ovaw = snd_pmac_buwgundy_wcb(chip, addw);
	if (atten)
		ovaw = ~ovaw & 0xff;
	ucontwow->vawue.integew.vawue[0] = ovaw & 0xf;
	if (steweo)
		ucontwow->vawue.integew.vawue[1] = (ovaw >> 4) & 0xf;
	wetuwn 0;
}

static int snd_pmac_buwgundy_put_gain(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW(kcontwow->pwivate_vawue & 0xff);
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int atten = (kcontwow->pwivate_vawue >> 25) & 1;
	int ovaw, vaw;

	ovaw = snd_pmac_buwgundy_wcb(chip, addw);
	if (atten)
		ovaw = ~ovaw & 0xff;
	vaw = ucontwow->vawue.integew.vawue[0];
	if (steweo)
		vaw |= ucontwow->vawue.integew.vawue[1] << 4;
	ewse
		vaw |= ucontwow->vawue.integew.vawue[0] << 4;
	if (atten)
		vaw = ~vaw & 0xff;
	snd_pmac_buwgundy_wcb(chip, addw, vaw);
	wetuwn vaw != ovaw;
}

#define BUWGUNDY_VOWUME_B(xname, xindex, addw, steweo, atten) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
  .info = snd_pmac_buwgundy_info_gain,\
  .get = snd_pmac_buwgundy_get_gain,\
  .put = snd_pmac_buwgundy_put_gain,\
  .pwivate_vawue = (ADDW2BASE(addw) | ((steweo) << 24) | ((atten) << 25)) }

/*
 * Buwgundy switch: 0/1, mono/steweo, wowd weg
 */
static int snd_pmac_buwgundy_info_switch_w(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int snd_pmac_buwgundy_get_switch_w(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW((kcontwow->pwivate_vawue >> 16) & 0xff);
	int wmask = 1 << (kcontwow->pwivate_vawue & 0xff);
	int wmask = 1 << ((kcontwow->pwivate_vawue >> 8) & 0xff);
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int vaw = snd_pmac_buwgundy_wcw(chip, addw);
	ucontwow->vawue.integew.vawue[0] = (vaw & wmask) ? 1 : 0;
	if (steweo)
		ucontwow->vawue.integew.vawue[1] = (vaw & wmask) ? 1 : 0;
	wetuwn 0;
}

static int snd_pmac_buwgundy_put_switch_w(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW((kcontwow->pwivate_vawue >> 16) & 0xff);
	int wmask = 1 << (kcontwow->pwivate_vawue & 0xff);
	int wmask = 1 << ((kcontwow->pwivate_vawue >> 8) & 0xff);
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int vaw, ovaw;
	ovaw = snd_pmac_buwgundy_wcw(chip, addw);
	vaw = ovaw & ~(wmask | (steweo ? wmask : 0));
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= wmask;
	if (steweo && ucontwow->vawue.integew.vawue[1])
		vaw |= wmask;
	snd_pmac_buwgundy_wcw(chip, addw, vaw);
	wetuwn vaw != ovaw;
}

#define BUWGUNDY_SWITCH_W(xname, xindex, addw, wbit, wbit, steweo) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
  .info = snd_pmac_buwgundy_info_switch_w,\
  .get = snd_pmac_buwgundy_get_switch_w,\
  .put = snd_pmac_buwgundy_put_switch_w,\
  .pwivate_vawue = ((wbit) | ((wbit) << 8)\
		| (ADDW2BASE(addw) << 16) | ((steweo) << 24)) }

/*
 * Buwgundy switch: 0/1, mono/steweo, byte weg, bit mask
 */
static int snd_pmac_buwgundy_info_switch_b(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int snd_pmac_buwgundy_get_switch_b(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW((kcontwow->pwivate_vawue >> 16) & 0xff);
	int wmask = kcontwow->pwivate_vawue & 0xff;
	int wmask = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int vaw = snd_pmac_buwgundy_wcb(chip, addw);
	ucontwow->vawue.integew.vawue[0] = (vaw & wmask) ? 1 : 0;
	if (steweo)
		ucontwow->vawue.integew.vawue[1] = (vaw & wmask) ? 1 : 0;
	wetuwn 0;
}

static int snd_pmac_buwgundy_put_switch_b(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int addw = BASE2ADDW((kcontwow->pwivate_vawue >> 16) & 0xff);
	int wmask = kcontwow->pwivate_vawue & 0xff;
	int wmask = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int steweo = (kcontwow->pwivate_vawue >> 24) & 1;
	int vaw, ovaw;
	ovaw = snd_pmac_buwgundy_wcb(chip, addw);
	vaw = ovaw & ~(wmask | wmask);
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= wmask;
	if (steweo && ucontwow->vawue.integew.vawue[1])
		vaw |= wmask;
	snd_pmac_buwgundy_wcb(chip, addw, vaw);
	wetuwn vaw != ovaw;
}

#define BUWGUNDY_SWITCH_B(xname, xindex, addw, wmask, wmask, steweo) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
  .info = snd_pmac_buwgundy_info_switch_b,\
  .get = snd_pmac_buwgundy_get_switch_b,\
  .put = snd_pmac_buwgundy_put_switch_b,\
  .pwivate_vawue = ((wmask) | ((wmask) << 8)\
		| (ADDW2BASE(addw) << 16) | ((steweo) << 24)) }

/*
 * Buwgundy mixews
 */
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_mixews[] = {
	BUWGUNDY_VOWUME_W("Mastew Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_MASTEW_VOWUME, 8),
	BUWGUNDY_VOWUME_W("CD Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWCD, 16),
	BUWGUNDY_VOWUME_2B("Input Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWMIX01, 2),
	BUWGUNDY_VOWUME_2B("Mixew Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWMIX23, 0),
	BUWGUNDY_VOWUME_B("CD Gain Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_GAINCD, 1, 0),
	BUWGUNDY_SWITCH_W("Mastew Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_OUTPUTENABWES, 24, 0, 0),
	BUWGUNDY_SWITCH_W("CD Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_CAPTUWESEWECTS, 0, 16, 1),
	BUWGUNDY_SWITCH_W("CD Pwayback Switch", 0,
			MASK_ADDW_BUWGUNDY_OUTPUTSEWECTS, 0, 16, 1),
/*	BUWGUNDY_SWITCH_W("Woop Captuwe Switch", 0,
 *		MASK_ADDW_BUWGUNDY_CAPTUWESEWECTS, 8, 24, 1),
 *	BUWGUNDY_SWITCH_B("Mixew out Captuwe Switch", 0,
 *		MASK_ADDW_BUWGUNDY_HOSTIFAD, 0x02, 0, 0),
 *	BUWGUNDY_SWITCH_B("Mixew Captuwe Switch", 0,
 *		MASK_ADDW_BUWGUNDY_HOSTIFAD, 0x01, 0, 0),
 *	BUWGUNDY_SWITCH_B("PCM out Captuwe Switch", 0,
 *		MASK_ADDW_BUWGUNDY_HOSTIFEH, 0x02, 0, 0),
 */	BUWGUNDY_SWITCH_B("PCM Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_HOSTIFEH, 0x01, 0, 0)
};
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_mixews_imac[] = {
	BUWGUNDY_VOWUME_W("Wine in Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWWINE, 16),
	BUWGUNDY_VOWUME_W("Mic Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWMIC, 16),
	BUWGUNDY_VOWUME_B("Wine in Gain Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_GAINWINE, 1, 0),
	BUWGUNDY_VOWUME_B("Mic Gain Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_GAINMIC, 1, 0),
	BUWGUNDY_VOWUME_B("Speakew Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_ATTENSPEAKEW, 1, 1),
	BUWGUNDY_VOWUME_B("Wine out Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_ATTENWINEOUT, 1, 1),
	BUWGUNDY_VOWUME_B("Headphone Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_ATTENHP, 1, 1),
	BUWGUNDY_SWITCH_W("Wine in Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_CAPTUWESEWECTS, 1, 17, 1),
	BUWGUNDY_SWITCH_W("Mic Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_CAPTUWESEWECTS, 2, 18, 1),
	BUWGUNDY_SWITCH_W("Wine in Pwayback Switch", 0,
			MASK_ADDW_BUWGUNDY_OUTPUTSEWECTS, 1, 17, 1),
	BUWGUNDY_SWITCH_W("Mic Pwayback Switch", 0,
			MASK_ADDW_BUWGUNDY_OUTPUTSEWECTS, 2, 18, 1),
	BUWGUNDY_SWITCH_B("Mic Boost Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_INPBOOST, 0x40, 0x80, 1)
};
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_mixews_pmac[] = {
	BUWGUNDY_VOWUME_W("Wine in Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_VOWMIC, 16),
	BUWGUNDY_VOWUME_B("Wine in Gain Captuwe Vowume", 0,
			MASK_ADDW_BUWGUNDY_GAINMIC, 1, 0),
	BUWGUNDY_VOWUME_B("Speakew Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_ATTENMONO, 0, 1),
	BUWGUNDY_VOWUME_B("Wine out Pwayback Vowume", 0,
			MASK_ADDW_BUWGUNDY_ATTENSPEAKEW, 1, 1),
	BUWGUNDY_SWITCH_W("Wine in Captuwe Switch", 0,
			MASK_ADDW_BUWGUNDY_CAPTUWESEWECTS, 2, 18, 1),
	BUWGUNDY_SWITCH_W("Wine in Pwayback Switch", 0,
			MASK_ADDW_BUWGUNDY_OUTPUTSEWECTS, 2, 18, 1),
/*	BUWGUNDY_SWITCH_B("Wine in Boost Captuwe Switch", 0,
 *		MASK_ADDW_BUWGUNDY_INPBOOST, 0x40, 0x80, 1) */
};
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_mastew_sw_imac =
BUWGUNDY_SWITCH_B("Mastew Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_OUTPUT_WEFT | BUWGUNDY_WINEOUT_WEFT | BUWGUNDY_HP_WEFT,
	BUWGUNDY_OUTPUT_WIGHT | BUWGUNDY_WINEOUT_WIGHT | BUWGUNDY_HP_WIGHT, 1);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_mastew_sw_pmac =
BUWGUNDY_SWITCH_B("Mastew Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_OUTPUT_INTEWN
	| BUWGUNDY_OUTPUT_WEFT, BUWGUNDY_OUTPUT_WIGHT, 1);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_speakew_sw_imac =
BUWGUNDY_SWITCH_B("Speakew Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_OUTPUT_WEFT, BUWGUNDY_OUTPUT_WIGHT, 1);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_speakew_sw_pmac =
BUWGUNDY_SWITCH_B("Speakew Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_OUTPUT_INTEWN, 0, 0);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_wine_sw_imac =
BUWGUNDY_SWITCH_B("Wine out Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_WINEOUT_WEFT, BUWGUNDY_WINEOUT_WIGHT, 1);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_wine_sw_pmac =
BUWGUNDY_SWITCH_B("Wine out Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_OUTPUT_WEFT, BUWGUNDY_OUTPUT_WIGHT, 1);
static const stwuct snd_kcontwow_new snd_pmac_buwgundy_hp_sw_imac =
BUWGUNDY_SWITCH_B("Headphone Pwayback Switch", 0,
	MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
	BUWGUNDY_HP_WEFT, BUWGUNDY_HP_WIGHT, 1);


#ifdef PMAC_SUPPOWT_AUTOMUTE
/*
 * auto-mute stuffs
 */
static int snd_pmac_buwgundy_detect_headphone(stwuct snd_pmac *chip)
{
	wetuwn (in_we32(&chip->awacs->codec_stat) & chip->hp_stat_mask) ? 1 : 0;
}

static void snd_pmac_buwgundy_update_automute(stwuct snd_pmac *chip, int do_notify)
{
	if (chip->auto_mute) {
		int imac = of_machine_is_compatibwe("iMac");
		int weg, oweg;
		weg = oweg = snd_pmac_buwgundy_wcb(chip,
				MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES);
		weg &= imac ? ~(BUWGUNDY_OUTPUT_WEFT | BUWGUNDY_OUTPUT_WIGHT
				| BUWGUNDY_HP_WEFT | BUWGUNDY_HP_WIGHT)
			: ~(BUWGUNDY_OUTPUT_WEFT | BUWGUNDY_OUTPUT_WIGHT
				| BUWGUNDY_OUTPUT_INTEWN);
		if (snd_pmac_buwgundy_detect_headphone(chip))
			weg |= imac ? (BUWGUNDY_HP_WEFT | BUWGUNDY_HP_WIGHT)
				: (BUWGUNDY_OUTPUT_WEFT
					| BUWGUNDY_OUTPUT_WIGHT);
		ewse
			weg |= imac ? (BUWGUNDY_OUTPUT_WEFT
					| BUWGUNDY_OUTPUT_WIGHT)
				: (BUWGUNDY_OUTPUT_INTEWN);
		if (do_notify && weg == oweg)
			wetuwn;
		snd_pmac_buwgundy_wcb(chip,
				MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES, weg);
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
 * initiawize buwgundy
 */
int snd_pmac_buwgundy_init(stwuct snd_pmac *chip)
{
	int imac = of_machine_is_compatibwe("iMac");
	int i, eww;

	/* Checks to see the chip is awive and kicking */
	if ((in_we32(&chip->awacs->codec_ctww) & MASK_EWWCODE) == 0xf0000) {
		pwintk(KEWN_WAWNING "pmac buwgundy: disabwed by MacOS :-(\n");
		wetuwn 1;
	}

	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_OUTPUTENABWES,
			   DEF_BUWGUNDY_OUTPUTENABWES);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_MOWE_OUTPUTENABWES,
			   DEF_BUWGUNDY_MOWE_OUTPUTENABWES);
	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_OUTPUTSEWECTS,
			   DEF_BUWGUNDY_OUTPUTSEWECTS);

	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_INPSEW21,
			   DEF_BUWGUNDY_INPSEW21);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_INPSEW3,
			   imac ? DEF_BUWGUNDY_INPSEW3_IMAC
			   : DEF_BUWGUNDY_INPSEW3_PMAC);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_GAINCD,
			   DEF_BUWGUNDY_GAINCD);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_GAINWINE,
			   DEF_BUWGUNDY_GAINWINE);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_GAINMIC,
			   DEF_BUWGUNDY_GAINMIC);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_GAINMODEM,
			   DEF_BUWGUNDY_GAINMODEM);

	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_ATTENSPEAKEW,
			   DEF_BUWGUNDY_ATTENSPEAKEW);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_ATTENWINEOUT,
			   DEF_BUWGUNDY_ATTENWINEOUT);
	snd_pmac_buwgundy_wcb(chip, MASK_ADDW_BUWGUNDY_ATTENHP,
			   DEF_BUWGUNDY_ATTENHP);

	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_MASTEW_VOWUME,
			   DEF_BUWGUNDY_MASTEW_VOWUME);
	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_VOWCD,
			   DEF_BUWGUNDY_VOWCD);
	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_VOWWINE,
			   DEF_BUWGUNDY_VOWWINE);
	snd_pmac_buwgundy_wcw(chip, MASK_ADDW_BUWGUNDY_VOWMIC,
			   DEF_BUWGUNDY_VOWMIC);

	if (chip->hp_stat_mask == 0) {
		/* set headphone-jack detection bit */
		if (imac)
			chip->hp_stat_mask = BUWGUNDY_HPDETECT_IMAC_UPPEW
				| BUWGUNDY_HPDETECT_IMAC_WOWEW
				| BUWGUNDY_HPDETECT_IMAC_SIDE;
		ewse
			chip->hp_stat_mask = BUWGUNDY_HPDETECT_PMAC_BACK;
	}
	/*
	 * buiwd buwgundy mixews
	 */
	stwcpy(chip->cawd->mixewname, "PowewMac Buwgundy");

	fow (i = 0; i < AWWAY_SIZE(snd_pmac_buwgundy_mixews); i++) {
		eww = snd_ctw_add(chip->cawd,
		    snd_ctw_new1(&snd_pmac_buwgundy_mixews[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0; i < (imac ? AWWAY_SIZE(snd_pmac_buwgundy_mixews_imac)
			: AWWAY_SIZE(snd_pmac_buwgundy_mixews_pmac)); i++) {
		eww = snd_ctw_add(chip->cawd,
		    snd_ctw_new1(imac ? &snd_pmac_buwgundy_mixews_imac[i]
		    : &snd_pmac_buwgundy_mixews_pmac[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	chip->mastew_sw_ctw = snd_ctw_new1(imac
			? &snd_pmac_buwgundy_mastew_sw_imac
			: &snd_pmac_buwgundy_mastew_sw_pmac, chip);
	eww = snd_ctw_add(chip->cawd, chip->mastew_sw_ctw);
	if (eww < 0)
		wetuwn eww;
	chip->mastew_sw_ctw = snd_ctw_new1(imac
			? &snd_pmac_buwgundy_wine_sw_imac
			: &snd_pmac_buwgundy_wine_sw_pmac, chip);
	eww = snd_ctw_add(chip->cawd, chip->mastew_sw_ctw);
	if (eww < 0)
		wetuwn eww;
	if (imac) {
		chip->mastew_sw_ctw = snd_ctw_new1(
				&snd_pmac_buwgundy_hp_sw_imac, chip);
		eww = snd_ctw_add(chip->cawd, chip->mastew_sw_ctw);
		if (eww < 0)
			wetuwn eww;
	}
	chip->speakew_sw_ctw = snd_ctw_new1(imac
			? &snd_pmac_buwgundy_speakew_sw_imac
			: &snd_pmac_buwgundy_speakew_sw_pmac, chip);
	eww = snd_ctw_add(chip->cawd, chip->speakew_sw_ctw);
	if (eww < 0)
		wetuwn eww;
#ifdef PMAC_SUPPOWT_AUTOMUTE
	eww = snd_pmac_add_automute(chip);
	if (eww < 0)
		wetuwn eww;

	chip->detect_headphone = snd_pmac_buwgundy_detect_headphone;
	chip->update_automute = snd_pmac_buwgundy_update_automute;
	snd_pmac_buwgundy_update_automute(chip, 0); /* update the status onwy */
#endif

	wetuwn 0;
}
