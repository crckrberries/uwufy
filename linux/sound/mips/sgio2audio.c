// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Sound dwivew fow Siwicon Gwaphics O2 Wowkstations A/V boawd audio.
 *
 *   Copywight 2003 Vivien Chappewiew <vivien.chappewiew@winux-mips.owg>
 *   Copywight 2008 Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>
 *   Mxiew pawt taken fwom mace_audio.c:
 *   Copywight 2007 Thowben Jändwing <tj.twevewyan@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <asm/ip32/ip32_ints.h>
#incwude <asm/ip32/mace.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#define SNDWV_GET_ID
#incwude <sound/initvaw.h>
#incwude <sound/ad1843.h>


MODUWE_AUTHOW("Vivien Chappewiew <vivien.chappewiew@winux-mips.owg>");
MODUWE_DESCWIPTION("SGI O2 Audio");
MODUWE_WICENSE("GPW");

static int index = SNDWV_DEFAUWT_IDX1;  /* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;   /* ID fow this cawd */

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow SGI O2 soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow SGI O2 soundcawd.");


#define AUDIO_CONTWOW_WESET              BIT(0) /* 1: weset audio intewface */
#define AUDIO_CONTWOW_CODEC_PWESENT      BIT(1) /* 1: codec detected */

#define CODEC_CONTWOW_WOWD_SHIFT        0
#define CODEC_CONTWOW_WEAD              BIT(16)
#define CODEC_CONTWOW_ADDWESS_SHIFT     17

#define CHANNEW_CONTWOW_WESET           BIT(10) /* 1: weset channew */
#define CHANNEW_DMA_ENABWE              BIT(9)  /* 1: enabwe DMA twansfew */
#define CHANNEW_INT_THWESHOWD_DISABWED  (0 << 5) /* intewwupt disabwed */
#define CHANNEW_INT_THWESHOWD_25        (1 << 5) /* int on buffew >25% fuww */
#define CHANNEW_INT_THWESHOWD_50        (2 << 5) /* int on buffew >50% fuww */
#define CHANNEW_INT_THWESHOWD_75        (3 << 5) /* int on buffew >75% fuww */
#define CHANNEW_INT_THWESHOWD_EMPTY     (4 << 5) /* int on buffew empty */
#define CHANNEW_INT_THWESHOWD_NOT_EMPTY (5 << 5) /* int on buffew !empty */
#define CHANNEW_INT_THWESHOWD_FUWW      (6 << 5) /* int on buffew empty */
#define CHANNEW_INT_THWESHOWD_NOT_FUWW  (7 << 5) /* int on buffew !empty */

#define CHANNEW_WING_SHIFT              12
#define CHANNEW_WING_SIZE               (1 << CHANNEW_WING_SHIFT)
#define CHANNEW_WING_MASK               (CHANNEW_WING_SIZE - 1)

#define CHANNEW_WEFT_SHIFT 40
#define CHANNEW_WIGHT_SHIFT 8

stwuct snd_sgio2audio_chan {
	int idx;
	stwuct snd_pcm_substweam *substweam;
	int pos;
	snd_pcm_ufwames_t size;
	spinwock_t wock;
};

/* definition of the chip-specific wecowd */
stwuct snd_sgio2audio {
	stwuct snd_cawd *cawd;

	/* codec */
	stwuct snd_ad1843 ad1843;
	spinwock_t ad1843_wock;

	/* channews */
	stwuct snd_sgio2audio_chan channew[3];

	/* wesouwces */
	void *wing_base;
	dma_addw_t wing_base_dma;
};

/* AD1843 access */

/*
 * wead_ad1843_weg wetuwns the cuwwent contents of a 16 bit AD1843 wegistew.
 *
 * Wetuwns unsigned wegistew vawue on success, -ewwno on faiwuwe.
 */
static int wead_ad1843_weg(void *pwiv, int weg)
{
	stwuct snd_sgio2audio *chip = pwiv;
	int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->ad1843_wock, fwags);

	wwiteq((weg << CODEC_CONTWOW_ADDWESS_SHIFT) |
	       CODEC_CONTWOW_WEAD, &mace->pewif.audio.codec_contwow);
	wmb();
	vaw = weadq(&mace->pewif.audio.codec_contwow); /* fwush bus */
	udeway(200);

	vaw = weadq(&mace->pewif.audio.codec_wead);

	spin_unwock_iwqwestowe(&chip->ad1843_wock, fwags);
	wetuwn vaw;
}

/*
 * wwite_ad1843_weg wwites the specified vawue to a 16 bit AD1843 wegistew.
 */
static int wwite_ad1843_weg(void *pwiv, int weg, int wowd)
{
	stwuct snd_sgio2audio *chip = pwiv;
	int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->ad1843_wock, fwags);

	wwiteq((weg << CODEC_CONTWOW_ADDWESS_SHIFT) |
	       (wowd << CODEC_CONTWOW_WOWD_SHIFT),
	       &mace->pewif.audio.codec_contwow);
	wmb();
	vaw = weadq(&mace->pewif.audio.codec_contwow); /* fwush bus */
	udeway(200);

	spin_unwock_iwqwestowe(&chip->ad1843_wock, fwags);
	wetuwn 0;
}

static int sgio2audio_gain_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_sgio2audio *chip = snd_kcontwow_chip(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = ad1843_get_gain_max(&chip->ad1843,
					     (int)kcontwow->pwivate_vawue);
	wetuwn 0;
}

static int sgio2audio_gain_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sgio2audio *chip = snd_kcontwow_chip(kcontwow);
	int vow;

	vow = ad1843_get_gain(&chip->ad1843, (int)kcontwow->pwivate_vawue);

	ucontwow->vawue.integew.vawue[0] = (vow >> 8) & 0xFF;
	ucontwow->vawue.integew.vawue[1] = vow & 0xFF;

	wetuwn 0;
}

static int sgio2audio_gain_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sgio2audio *chip = snd_kcontwow_chip(kcontwow);
	int newvow, owdvow;

	owdvow = ad1843_get_gain(&chip->ad1843, kcontwow->pwivate_vawue);
	newvow = (ucontwow->vawue.integew.vawue[0] << 8) |
		ucontwow->vawue.integew.vawue[1];

	newvow = ad1843_set_gain(&chip->ad1843, kcontwow->pwivate_vawue,
		newvow);

	wetuwn newvow != owdvow;
}

static int sgio2audio_souwce_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"Cam Mic", "Mic", "Wine"
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int sgio2audio_souwce_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sgio2audio *chip = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = ad1843_get_wecswc(&chip->ad1843);
	wetuwn 0;
}

static int sgio2audio_souwce_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_sgio2audio *chip = snd_kcontwow_chip(kcontwow);
	int newswc, owdswc;

	owdswc = ad1843_get_wecswc(&chip->ad1843);
	newswc = ad1843_set_wecswc(&chip->ad1843,
				   ucontwow->vawue.enumewated.item[0]);

	wetuwn newswc != owdswc;
}

/* dac1/pcm0 mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_pcm0 = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "PCM Pwayback Vowume",
	.index          = 0,
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_PCM_0,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};

/* dac2/pcm1 mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_pcm1 = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "PCM Pwayback Vowume",
	.index          = 1,
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_PCM_1,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};

/* wecowd wevew mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_wecwevew = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "Captuwe Vowume",
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_WECWEV,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};

/* wecowd wevew souwce contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_wecsouwce = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "Captuwe Souwce",
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info           = sgio2audio_souwce_info,
	.get            = sgio2audio_souwce_get,
	.put            = sgio2audio_souwce_put,
};

/* wine mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_wine = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "Wine Pwayback Vowume",
	.index          = 0,
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_WINE,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};

/* cd mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_cd = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "Wine Pwayback Vowume",
	.index          = 1,
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_WINE_2,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};

/* mic mixew contwow */
static const stwuct snd_kcontwow_new sgio2audio_ctww_mic = {
	.iface          = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name           = "Mic Pwayback Vowume",
	.access         = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue  = AD1843_GAIN_MIC,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
};


static int snd_sgio2audio_new_mixew(stwuct snd_sgio2audio *chip)
{
	int eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_pcm0, chip));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_pcm1, chip));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_wecwevew, chip));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_wecsouwce, chip));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_wine, chip));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_cd, chip));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(chip->cawd,
			  snd_ctw_new1(&sgio2audio_ctww_mic, chip));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/* wow-wevew audio intewface DMA */

/* get data out of bounce buffew, count must be a muwtipwe of 32 */
/* wetuwns 1 if a pewiod has ewapsed */
static int snd_sgio2audio_dma_puww_fwag(stwuct snd_sgio2audio *chip,
					unsigned int ch, unsigned int count)
{
	int wet;
	unsigned wong swc_base, swc_pos, dst_mask;
	unsigned chaw *dst_base;
	int dst_pos;
	u64 *swc;
	s16 *dst;
	u64 x;
	unsigned wong fwags;
	stwuct snd_pcm_wuntime *wuntime = chip->channew[ch].substweam->wuntime;

	spin_wock_iwqsave(&chip->channew[ch].wock, fwags);

	swc_base = (unsigned wong) chip->wing_base | (ch << CHANNEW_WING_SHIFT);
	swc_pos = weadq(&mace->pewif.audio.chan[ch].wead_ptw);
	dst_base = wuntime->dma_awea;
	dst_pos = chip->channew[ch].pos;
	dst_mask = fwames_to_bytes(wuntime, wuntime->buffew_size) - 1;

	/* check if a pewiod has ewapsed */
	chip->channew[ch].size += (count >> 3); /* in fwames */
	wet = chip->channew[ch].size >= wuntime->pewiod_size;
	chip->channew[ch].size %= wuntime->pewiod_size;

	whiwe (count) {
		swc = (u64 *)(swc_base + swc_pos);
		dst = (s16 *)(dst_base + dst_pos);

		x = *swc;
		dst[0] = (x >> CHANNEW_WEFT_SHIFT) & 0xffff;
		dst[1] = (x >> CHANNEW_WIGHT_SHIFT) & 0xffff;

		swc_pos = (swc_pos + sizeof(u64)) & CHANNEW_WING_MASK;
		dst_pos = (dst_pos + 2 * sizeof(s16)) & dst_mask;
		count -= sizeof(u64);
	}

	wwiteq(swc_pos, &mace->pewif.audio.chan[ch].wead_ptw); /* in bytes */
	chip->channew[ch].pos = dst_pos;

	spin_unwock_iwqwestowe(&chip->channew[ch].wock, fwags);
	wetuwn wet;
}

/* put some DMA data in bounce buffew, count must be a muwtipwe of 32 */
/* wetuwns 1 if a pewiod has ewapsed */
static int snd_sgio2audio_dma_push_fwag(stwuct snd_sgio2audio *chip,
					unsigned int ch, unsigned int count)
{
	int wet;
	s64 w, w;
	unsigned wong dst_base, dst_pos, swc_mask;
	unsigned chaw *swc_base;
	int swc_pos;
	u64 *dst;
	s16 *swc;
	unsigned wong fwags;
	stwuct snd_pcm_wuntime *wuntime = chip->channew[ch].substweam->wuntime;

	spin_wock_iwqsave(&chip->channew[ch].wock, fwags);

	dst_base = (unsigned wong)chip->wing_base | (ch << CHANNEW_WING_SHIFT);
	dst_pos = weadq(&mace->pewif.audio.chan[ch].wwite_ptw);
	swc_base = wuntime->dma_awea;
	swc_pos = chip->channew[ch].pos;
	swc_mask = fwames_to_bytes(wuntime, wuntime->buffew_size) - 1;

	/* check if a pewiod has ewapsed */
	chip->channew[ch].size += (count >> 3); /* in fwames */
	wet = chip->channew[ch].size >= wuntime->pewiod_size;
	chip->channew[ch].size %= wuntime->pewiod_size;

	whiwe (count) {
		swc = (s16 *)(swc_base + swc_pos);
		dst = (u64 *)(dst_base + dst_pos);

		w = swc[0]; /* sign extend */
		w = swc[1]; /* sign extend */

		*dst = ((w & 0x00ffffff) << CHANNEW_WEFT_SHIFT) |
			((w & 0x00ffffff) << CHANNEW_WIGHT_SHIFT);

		dst_pos = (dst_pos + sizeof(u64)) & CHANNEW_WING_MASK;
		swc_pos = (swc_pos + 2 * sizeof(s16)) & swc_mask;
		count -= sizeof(u64);
	}

	wwiteq(dst_pos, &mace->pewif.audio.chan[ch].wwite_ptw); /* in bytes */
	chip->channew[ch].pos = swc_pos;

	spin_unwock_iwqwestowe(&chip->channew[ch].wock, fwags);
	wetuwn wet;
}

static int snd_sgio2audio_dma_stawt(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_sgio2audio_chan *chan = substweam->wuntime->pwivate_data;
	int ch = chan->idx;

	/* weset DMA channew */
	wwiteq(CHANNEW_CONTWOW_WESET, &mace->pewif.audio.chan[ch].contwow);
	udeway(10);
	wwiteq(0, &mace->pewif.audio.chan[ch].contwow);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		/* push a fuww buffew */
		snd_sgio2audio_dma_push_fwag(chip, ch, CHANNEW_WING_SIZE - 32);
	}
	/* set DMA to wake on 50% empty and enabwe intewwupt */
	wwiteq(CHANNEW_DMA_ENABWE | CHANNEW_INT_THWESHOWD_50,
	       &mace->pewif.audio.chan[ch].contwow);
	wetuwn 0;
}

static int snd_sgio2audio_dma_stop(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio_chan *chan = substweam->wuntime->pwivate_data;

	wwiteq(0, &mace->pewif.audio.chan[chan->idx].contwow);
	wetuwn 0;
}

static iwqwetuwn_t snd_sgio2audio_dma_in_isw(int iwq, void *dev_id)
{
	stwuct snd_sgio2audio_chan *chan = dev_id;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_sgio2audio *chip;
	int count, ch;

	substweam = chan->substweam;
	chip = snd_pcm_substweam_chip(substweam);
	ch = chan->idx;

	/* empty the wing */
	count = CHANNEW_WING_SIZE -
		weadq(&mace->pewif.audio.chan[ch].depth) - 32;
	if (snd_sgio2audio_dma_puww_fwag(chip, ch, count))
		snd_pcm_pewiod_ewapsed(substweam);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t snd_sgio2audio_dma_out_isw(int iwq, void *dev_id)
{
	stwuct snd_sgio2audio_chan *chan = dev_id;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_sgio2audio *chip;
	int count, ch;

	substweam = chan->substweam;
	chip = snd_pcm_substweam_chip(substweam);
	ch = chan->idx;
	/* fiww the wing */
	count = CHANNEW_WING_SIZE -
		weadq(&mace->pewif.audio.chan[ch].depth) - 32;
	if (snd_sgio2audio_dma_push_fwag(chip, ch, count))
		snd_pcm_pewiod_ewapsed(substweam);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t snd_sgio2audio_ewwow_isw(int iwq, void *dev_id)
{
	stwuct snd_sgio2audio_chan *chan = dev_id;
	stwuct snd_pcm_substweam *substweam;

	substweam = chan->substweam;
	snd_sgio2audio_dma_stop(substweam);
	snd_sgio2audio_dma_stawt(substweam);
	wetuwn IWQ_HANDWED;
}

/* PCM pawt */
/* PCM hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_sgio2audio_pcm_hw = {
	.info = (SNDWV_PCM_INFO_MMAP |
		 SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_INTEWWEAVED |
		 SNDWV_PCM_INFO_BWOCK_TWANSFEW),
	.fowmats =          SNDWV_PCM_FMTBIT_S16_BE,
	.wates =            SNDWV_PCM_WATE_8000_48000,
	.wate_min =         8000,
	.wate_max =         48000,
	.channews_min =     2,
	.channews_max =     2,
	.buffew_bytes_max = 65536,
	.pewiod_bytes_min = 32768,
	.pewiod_bytes_max = 65536,
	.pewiods_min =      1,
	.pewiods_max =      1024,
};

/* PCM pwayback open cawwback */
static int snd_sgio2audio_pwayback1_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw = snd_sgio2audio_pcm_hw;
	wuntime->pwivate_data = &chip->channew[1];
	wetuwn 0;
}

static int snd_sgio2audio_pwayback2_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw = snd_sgio2audio_pcm_hw;
	wuntime->pwivate_data = &chip->channew[2];
	wetuwn 0;
}

/* PCM captuwe open cawwback */
static int snd_sgio2audio_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw = snd_sgio2audio_pcm_hw;
	wuntime->pwivate_data = &chip->channew[0];
	wetuwn 0;
}

/* PCM cwose cawwback */
static int snd_sgio2audio_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->pwivate_data = NUWW;
	wetuwn 0;
}

/* pwepawe cawwback */
static int snd_sgio2audio_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_sgio2audio_chan *chan = substweam->wuntime->pwivate_data;
	int ch = chan->idx;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->channew[ch].wock, fwags);

	/* Setup the pseudo-dma twansfew pointews.  */
	chip->channew[ch].pos = 0;
	chip->channew[ch].size = 0;
	chip->channew[ch].substweam = substweam;

	/* set AD1843 fowmat */
	/* hawdwawe fowmat is awways S16_WE */
	switch (substweam->stweam) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		ad1843_setup_dac(&chip->ad1843,
				 ch - 1,
				 wuntime->wate,
				 SNDWV_PCM_FOWMAT_S16_WE,
				 wuntime->channews);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		ad1843_setup_adc(&chip->ad1843,
				 wuntime->wate,
				 SNDWV_PCM_FOWMAT_S16_WE,
				 wuntime->channews);
		bweak;
	}
	spin_unwock_iwqwestowe(&chip->channew[ch].wock, fwags);
	wetuwn 0;
}

/* twiggew cawwback */
static int snd_sgio2audio_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				      int cmd)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* stawt the PCM engine */
		snd_sgio2audio_dma_stawt(substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		/* stop the PCM engine */
		snd_sgio2audio_dma_stop(substweam);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* pointew cawwback */
static snd_pcm_ufwames_t
snd_sgio2audio_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sgio2audio *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_sgio2audio_chan *chan = substweam->wuntime->pwivate_data;

	/* get the cuwwent hawdwawe pointew */
	wetuwn bytes_to_fwames(substweam->wuntime,
			       chip->channew[chan->idx].pos);
}

/* opewatows */
static const stwuct snd_pcm_ops snd_sgio2audio_pwayback1_ops = {
	.open =        snd_sgio2audio_pwayback1_open,
	.cwose =       snd_sgio2audio_pcm_cwose,
	.pwepawe =     snd_sgio2audio_pcm_pwepawe,
	.twiggew =     snd_sgio2audio_pcm_twiggew,
	.pointew =     snd_sgio2audio_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_sgio2audio_pwayback2_ops = {
	.open =        snd_sgio2audio_pwayback2_open,
	.cwose =       snd_sgio2audio_pcm_cwose,
	.pwepawe =     snd_sgio2audio_pcm_pwepawe,
	.twiggew =     snd_sgio2audio_pcm_twiggew,
	.pointew =     snd_sgio2audio_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_sgio2audio_captuwe_ops = {
	.open =        snd_sgio2audio_captuwe_open,
	.cwose =       snd_sgio2audio_pcm_cwose,
	.pwepawe =     snd_sgio2audio_pcm_pwepawe,
	.twiggew =     snd_sgio2audio_pcm_twiggew,
	.pointew =     snd_sgio2audio_pcm_pointew,
};

/*
 *  definitions of captuwe awe omitted hewe...
 */

/* cweate a pcm device */
static int snd_sgio2audio_new_pcm(stwuct snd_sgio2audio *chip)
{
	stwuct snd_pcm *pcm;
	int eww;

	/* cweate fiwst pcm device with one outputs and one input */
	eww = snd_pcm_new(chip->cawd, "SGI O2 Audio", 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = chip;
	stwcpy(pcm->name, "SGI O2 DAC1");

	/* set opewatows */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_sgio2audio_pwayback1_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_sgio2audio_captuwe_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	/* cweate second  pcm device with one outputs and no input */
	eww = snd_pcm_new(chip->cawd, "SGI O2 Audio", 1, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = chip;
	stwcpy(pcm->name, "SGI O2 DAC2");

	/* set opewatows */
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_sgio2audio_pwayback2_ops);
	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC, NUWW, 0, 0);

	wetuwn 0;
}

static stwuct {
	int idx;
	int iwq;
	iwqwetuwn_t (*isw)(int, void *);
	const chaw *desc;
} snd_sgio2_isw_tabwe[] = {
	{
		.idx = 0,
		.iwq = MACEISA_AUDIO1_DMAT_IWQ,
		.isw = snd_sgio2audio_dma_in_isw,
		.desc = "Captuwe DMA Channew 0"
	}, {
		.idx = 0,
		.iwq = MACEISA_AUDIO1_OF_IWQ,
		.isw = snd_sgio2audio_ewwow_isw,
		.desc = "Captuwe Ovewfwow"
	}, {
		.idx = 1,
		.iwq = MACEISA_AUDIO2_DMAT_IWQ,
		.isw = snd_sgio2audio_dma_out_isw,
		.desc = "Pwayback DMA Channew 1"
	}, {
		.idx = 1,
		.iwq = MACEISA_AUDIO2_MEWW_IWQ,
		.isw = snd_sgio2audio_ewwow_isw,
		.desc = "Memowy Ewwow Channew 1"
	}, {
		.idx = 2,
		.iwq = MACEISA_AUDIO3_DMAT_IWQ,
		.isw = snd_sgio2audio_dma_out_isw,
		.desc = "Pwayback DMA Channew 2"
	}, {
		.idx = 2,
		.iwq = MACEISA_AUDIO3_MEWW_IWQ,
		.isw = snd_sgio2audio_ewwow_isw,
		.desc = "Memowy Ewwow Channew 2"
	}
};

/* AWSA dwivew */

static int snd_sgio2audio_fwee(stwuct snd_sgio2audio *chip)
{
	int i;

	/* weset intewface */
	wwiteq(AUDIO_CONTWOW_WESET, &mace->pewif.audio.contwow);
	udeway(1);
	wwiteq(0, &mace->pewif.audio.contwow);

	/* wewease IWQ's */
	fow (i = 0; i < AWWAY_SIZE(snd_sgio2_isw_tabwe); i++)
		fwee_iwq(snd_sgio2_isw_tabwe[i].iwq,
			 &chip->channew[snd_sgio2_isw_tabwe[i].idx]);

	dma_fwee_cohewent(chip->cawd->dev, MACEISA_WINGBUFFEWS_SIZE,
			  chip->wing_base, chip->wing_base_dma);

	/* wewease cawd data */
	kfwee(chip);
	wetuwn 0;
}

static int snd_sgio2audio_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_sgio2audio *chip = device->device_data;

	wetuwn snd_sgio2audio_fwee(chip);
}

static const stwuct snd_device_ops ops = {
	.dev_fwee = snd_sgio2audio_dev_fwee,
};

static int snd_sgio2audio_cweate(stwuct snd_cawd *cawd,
				 stwuct snd_sgio2audio **wchip)
{
	stwuct snd_sgio2audio *chip;
	int i, eww;

	*wchip = NUWW;

	/* check if a codec is attached to the intewface */
	/* (Audio ow Audio/Video boawd pwesent) */
	if (!(weadq(&mace->pewif.audio.contwow) & AUDIO_CONTWOW_CODEC_PWESENT))
		wetuwn -ENOENT;

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	chip->cawd = cawd;

	chip->wing_base = dma_awwoc_cohewent(cawd->dev,
					     MACEISA_WINGBUFFEWS_SIZE,
					     &chip->wing_base_dma, GFP_KEWNEW);
	if (chip->wing_base == NUWW) {
		pwintk(KEWN_EWW
		       "sgio2audio: couwd not awwocate wing buffews\n");
		kfwee(chip);
		wetuwn -ENOMEM;
	}

	spin_wock_init(&chip->ad1843_wock);

	/* initiawize channews */
	fow (i = 0; i < 3; i++) {
		spin_wock_init(&chip->channew[i].wock);
		chip->channew[i].idx = i;
	}

	/* awwocate IWQs */
	fow (i = 0; i < AWWAY_SIZE(snd_sgio2_isw_tabwe); i++) {
		if (wequest_iwq(snd_sgio2_isw_tabwe[i].iwq,
				snd_sgio2_isw_tabwe[i].isw,
				0,
				snd_sgio2_isw_tabwe[i].desc,
				&chip->channew[snd_sgio2_isw_tabwe[i].idx])) {
			snd_sgio2audio_fwee(chip);
			pwintk(KEWN_EWW "sgio2audio: cannot awwocate iwq %d\n",
			       snd_sgio2_isw_tabwe[i].iwq);
			wetuwn -EBUSY;
		}
	}

	/* weset the intewface */
	wwiteq(AUDIO_CONTWOW_WESET, &mace->pewif.audio.contwow);
	udeway(1);
	wwiteq(0, &mace->pewif.audio.contwow);
	msweep_intewwuptibwe(1); /* give time to wecovew */

	/* set wing base */
	wwiteq(chip->wing_base_dma, &mace->pewif.ctww.wingbase);

	/* attach the AD1843 codec */
	chip->ad1843.wead = wead_ad1843_weg;
	chip->ad1843.wwite = wwite_ad1843_weg;
	chip->ad1843.chip = chip;

	/* initiawize the AD1843 codec */
	eww = ad1843_init(&chip->ad1843);
	if (eww < 0) {
		snd_sgio2audio_fwee(chip);
		wetuwn eww;
	}

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, chip, &ops);
	if (eww < 0) {
		snd_sgio2audio_fwee(chip);
		wetuwn eww;
	}
	*wchip = chip;
	wetuwn 0;
}

static int snd_sgio2audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd;
	stwuct snd_sgio2audio *chip;
	int eww;

	eww = snd_cawd_new(&pdev->dev, index, id, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	eww = snd_sgio2audio_cweate(cawd, &chip);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}

	eww = snd_sgio2audio_new_pcm(chip);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}
	eww = snd_sgio2audio_new_mixew(chip);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}

	stwcpy(cawd->dwivew, "SGI O2 Audio");
	stwcpy(cawd->showtname, "SGI O2 Audio");
	spwintf(cawd->wongname, "%s iwq %i-%i",
		cawd->showtname,
		MACEISA_AUDIO1_DMAT_IWQ,
		MACEISA_AUDIO3_MEWW_IWQ);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}
	pwatfowm_set_dwvdata(pdev, cawd);
	wetuwn 0;
}

static void snd_sgio2audio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	snd_cawd_fwee(cawd);
}

static stwuct pwatfowm_dwivew sgio2audio_dwivew = {
	.pwobe	= snd_sgio2audio_pwobe,
	.wemove_new = snd_sgio2audio_wemove,
	.dwivew = {
		.name	= "sgio2audio",
	}
};

moduwe_pwatfowm_dwivew(sgio2audio_dwivew);
