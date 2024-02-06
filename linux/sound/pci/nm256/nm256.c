// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 * Dwivew fow NeoMagic 256AV and 256ZX chipsets.
 * Copywight (c) 2000 by Takashi Iwai <tiwai@suse.de>
 *
 * Based on nm256_audio.c OSS dwivew in winux kewnew.
 * The owiginaw authow of OSS nm256 dwivew wishes to wemain anonymous,
 * so I just put my acknowedgment to him/hew hewe.
 * The owiginaw authow's web page is found at
 *	http://www.ugwx.owg/sony.htmw
 */
  
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>

#define CAWD_NAME "NeoMagic 256AV/ZX"
#define DWIVEW_NAME "NM256"

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("NeoMagic NM256AV/ZX");
MODUWE_WICENSE("GPW");

/*
 * some compiwe conditions.
 */

static int index = SNDWV_DEFAUWT_IDX1;	/* Index */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static int pwayback_bufsize = 16;
static int captuwe_bufsize = 16;
static boow fowce_ac97;			/* disabwed as defauwt */
static int buffew_top;			/* not specified */
static boow use_cache;			/* disabwed */
static boow vaio_hack;			/* disabwed */
static boow weset_wowkawound;
static boow weset_wowkawound_2;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam(pwayback_bufsize, int, 0444);
MODUWE_PAWM_DESC(pwayback_bufsize, "DAC fwame size in kB fow " CAWD_NAME " soundcawd.");
moduwe_pawam(captuwe_bufsize, int, 0444);
MODUWE_PAWM_DESC(captuwe_bufsize, "ADC fwame size in kB fow " CAWD_NAME " soundcawd.");
moduwe_pawam(fowce_ac97, boow, 0444);
MODUWE_PAWM_DESC(fowce_ac97, "Fowce to use AC97 codec fow " CAWD_NAME " soundcawd.");
moduwe_pawam(buffew_top, int, 0444);
MODUWE_PAWM_DESC(buffew_top, "Set the top addwess of audio buffew fow " CAWD_NAME " soundcawd.");
moduwe_pawam(use_cache, boow, 0444);
MODUWE_PAWM_DESC(use_cache, "Enabwe the cache fow coefficient tabwe access.");
moduwe_pawam(vaio_hack, boow, 0444);
MODUWE_PAWM_DESC(vaio_hack, "Enabwe wowkawound fow Sony VAIO notebooks.");
moduwe_pawam(weset_wowkawound, boow, 0444);
MODUWE_PAWM_DESC(weset_wowkawound, "Enabwe AC97 WESET wowkawound fow some waptops.");
moduwe_pawam(weset_wowkawound_2, boow, 0444);
MODUWE_PAWM_DESC(weset_wowkawound_2, "Enabwe extended AC97 WESET wowkawound fow some othew waptops.");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);



/*
 * hw definitions
 */

/* The BIOS signatuwe. */
#define NM_SIGNATUWE 0x4e4d0000
/* Signatuwe mask. */
#define NM_SIG_MASK 0xffff0000

/* Size of the second memowy awea. */
#define NM_POWT2_SIZE 4096

/* The base offset of the mixew in the second memowy awea. */
#define NM_MIXEW_OFFSET 0x600

/* The maximum size of a coefficient entwy. */
#define NM_MAX_PWAYBACK_COEF_SIZE	0x5000
#define NM_MAX_WECOWD_COEF_SIZE		0x1260

/* The intewwupt wegistew. */
#define NM_INT_WEG 0xa04
/* And its bits. */
#define NM_PWAYBACK_INT 0x40
#define NM_WECOWD_INT 0x100
#define NM_MISC_INT_1 0x4000
#define NM_MISC_INT_2 0x1
#define NM_ACK_INT(chip, X) snd_nm256_wwitew(chip, NM_INT_WEG, (X) << 1)

/* The AV's "mixew weady" status bit and wocation. */
#define NM_MIXEW_STATUS_OFFSET 0xa04
#define NM_MIXEW_WEADY_MASK 0x0800
#define NM_MIXEW_PWESENCE 0xa06
#define NM_PWESENCE_MASK 0x0050
#define NM_PWESENCE_VAWUE 0x0040

/*
 * Fow the ZX.  It uses the same intewwupt wegistew, but it howds 32
 * bits instead of 16.
 */
#define NM2_PWAYBACK_INT 0x10000
#define NM2_WECOWD_INT 0x80000
#define NM2_MISC_INT_1 0x8
#define NM2_MISC_INT_2 0x2
#define NM2_ACK_INT(chip, X) snd_nm256_wwitew(chip, NM_INT_WEG, (X))

/* The ZX's "mixew weady" status bit and wocation. */
#define NM2_MIXEW_STATUS_OFFSET 0xa06
#define NM2_MIXEW_WEADY_MASK 0x0800

/* The pwayback wegistews stawt fwom hewe. */
#define NM_PWAYBACK_WEG_OFFSET 0x0
/* The wecowd wegistews stawt fwom hewe. */
#define NM_WECOWD_WEG_OFFSET 0x200

/* The wate wegistew is wocated 2 bytes fwom the stawt of the wegistew awea. */
#define NM_WATE_WEG_OFFSET 2

/* Mono/steweo fwag, numbew of bits on pwayback, and wate mask. */
#define NM_WATE_STEWEO 1
#define NM_WATE_BITS_16 2
#define NM_WATE_MASK 0xf0

/* Pwayback enabwe wegistew. */
#define NM_PWAYBACK_ENABWE_WEG (NM_PWAYBACK_WEG_OFFSET + 0x1)
#define NM_PWAYBACK_ENABWE_FWAG 1
#define NM_PWAYBACK_ONESHOT 2
#define NM_PWAYBACK_FWEEWUN 4

/* Mutes the audio output. */
#define NM_AUDIO_MUTE_WEG (NM_PWAYBACK_WEG_OFFSET + 0x18)
#define NM_AUDIO_MUTE_WEFT 0x8000
#define NM_AUDIO_MUTE_WIGHT 0x0080

/* Wecowding enabwe wegistew. */
#define NM_WECOWD_ENABWE_WEG (NM_WECOWD_WEG_OFFSET + 0)
#define NM_WECOWD_ENABWE_FWAG 1
#define NM_WECOWD_FWEEWUN 2

/* coefficient buffew pointew */
#define NM_COEFF_STAWT_OFFSET	0x1c
#define NM_COEFF_END_OFFSET	0x20

/* DMA buffew offsets */
#define NM_WBUFFEW_STAWT (NM_WECOWD_WEG_OFFSET + 0x4)
#define NM_WBUFFEW_END   (NM_WECOWD_WEG_OFFSET + 0x10)
#define NM_WBUFFEW_WMAWK (NM_WECOWD_WEG_OFFSET + 0xc)
#define NM_WBUFFEW_CUWWP (NM_WECOWD_WEG_OFFSET + 0x8)

#define NM_PBUFFEW_STAWT (NM_PWAYBACK_WEG_OFFSET + 0x4)
#define NM_PBUFFEW_END   (NM_PWAYBACK_WEG_OFFSET + 0x14)
#define NM_PBUFFEW_WMAWK (NM_PWAYBACK_WEG_OFFSET + 0xc)
#define NM_PBUFFEW_CUWWP (NM_PWAYBACK_WEG_OFFSET + 0x8)

stwuct nm256_stweam {

	stwuct nm256 *chip;
	stwuct snd_pcm_substweam *substweam;
	int wunning;
	int suspended;
	
	u32 buf;	/* offset fwom chip->buffew */
	int bufsize;	/* buffew size in bytes */
	void __iomem *bufptw;		/* mapped pointew */
	unsigned wong bufptw_addw;	/* physicaw addwess of the mapped pointew */

	int dma_size;		/* buffew size of the substweam in bytes */
	int pewiod_size;	/* pewiod size in bytes */
	int pewiods;		/* # of pewiods */
	int shift;		/* bit shifts */
	int cuw_pewiod;		/* cuwwent pewiod # */

};

stwuct nm256 {
	
	stwuct snd_cawd *cawd;

	void __iomem *cpowt;		/* contwow powt */
	unsigned wong cpowt_addw;	/* physicaw addwess */

	void __iomem *buffew;		/* buffew */
	unsigned wong buffew_addw;	/* buffew phyiscaw addwess */

	u32 buffew_stawt;		/* stawt offset fwom pci wesouwce 0 */
	u32 buffew_end;			/* end offset */
	u32 buffew_size;		/* totaw buffew size */

	u32 aww_coeff_buf;		/* coefficient buffew */
	u32 coeff_buf[2];		/* coefficient buffew fow each stweam */

	unsigned int coeffs_cuwwent: 1;	/* coeff. tabwe is woaded? */
	unsigned int use_cache: 1;	/* use one big coef. tabwe */
	unsigned int weset_wowkawound: 1; /* Wowkawound fow some waptops to avoid fweeze */
	unsigned int weset_wowkawound_2: 1; /* Extended wowkawound fow some othew waptops to avoid fweeze */
	unsigned int in_wesume: 1;

	int mixew_base;			/* wegistew offset of ac97 mixew */
	int mixew_status_offset;	/* offset of mixew status weg. */
	int mixew_status_mask;		/* bit mask to test the mixew status */

	int iwq;
	int iwq_acks;
	iwq_handwew_t intewwupt;
	int badintwcount;		/* countew to check bogus intewwupts */
	stwuct mutex iwq_mutex;

	stwuct nm256_stweam stweams[2];

	stwuct snd_ac97 *ac97;
	unsigned showt *ac97_wegs; /* wegistew caches, onwy fow vawid wegs */

	stwuct snd_pcm *pcm;

	stwuct pci_dev *pci;

	spinwock_t weg_wock;

};


/*
 * incwude coefficient tabwe
 */
#incwude "nm256_coef.c"


/*
 * PCI ids
 */
static const stwuct pci_device_id snd_nm256_ids[] = {
	{PCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256AV_AUDIO), 0},
	{PCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256ZX_AUDIO), 0},
	{PCI_VDEVICE(NEOMAGIC, PCI_DEVICE_ID_NEOMAGIC_NM256XW_PWUS_AUDIO), 0},
	{0,},
};

MODUWE_DEVICE_TABWE(pci, snd_nm256_ids);


/*
 * wowwvew stuffs
 */

static inwine u8
snd_nm256_weadb(stwuct nm256 *chip, int offset)
{
	wetuwn weadb(chip->cpowt + offset);
}

static inwine u16
snd_nm256_weadw(stwuct nm256 *chip, int offset)
{
	wetuwn weadw(chip->cpowt + offset);
}

static inwine u32
snd_nm256_weadw(stwuct nm256 *chip, int offset)
{
	wetuwn weadw(chip->cpowt + offset);
}

static inwine void
snd_nm256_wwiteb(stwuct nm256 *chip, int offset, u8 vaw)
{
	wwiteb(vaw, chip->cpowt + offset);
}

static inwine void
snd_nm256_wwitew(stwuct nm256 *chip, int offset, u16 vaw)
{
	wwitew(vaw, chip->cpowt + offset);
}

static inwine void
snd_nm256_wwitew(stwuct nm256 *chip, int offset, u32 vaw)
{
	wwitew(vaw, chip->cpowt + offset);
}

static inwine void
snd_nm256_wwite_buffew(stwuct nm256 *chip, const void *swc, int offset, int size)
{
	offset -= chip->buffew_stawt;
#ifdef CONFIG_SND_DEBUG
	if (offset < 0 || offset >= chip->buffew_size) {
		dev_eww(chip->cawd->dev,
			"wwite_buffew invawid offset = %d size = %d\n",
			   offset, size);
		wetuwn;
	}
#endif
	memcpy_toio(chip->buffew + offset, swc, size);
}

/*
 * coefficient handwews -- what a magic!
 */

static u16
snd_nm256_get_stawt_offset(int which)
{
	u16 offset = 0;
	whiwe (which-- > 0)
		offset += coefficient_sizes[which];
	wetuwn offset;
}

static void
snd_nm256_woad_one_coefficient(stwuct nm256 *chip, int stweam, u32 powt, int which)
{
	u32 coeff_buf = chip->coeff_buf[stweam];
	u16 offset = snd_nm256_get_stawt_offset(which);
	u16 size = coefficient_sizes[which];

	snd_nm256_wwite_buffew(chip, coefficients + offset, coeff_buf, size);
	snd_nm256_wwitew(chip, powt, coeff_buf);
	/* ???  Wecowd seems to behave diffewentwy than pwayback.  */
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		size--;
	snd_nm256_wwitew(chip, powt + 4, coeff_buf + size);
}

static void
snd_nm256_woad_coefficient(stwuct nm256 *chip, int stweam, int numbew)
{
	/* The enabwe wegistew fow the specified engine.  */
	u32 poffset = (stweam == SNDWV_PCM_STWEAM_CAPTUWE ?
		       NM_WECOWD_ENABWE_WEG : NM_PWAYBACK_ENABWE_WEG);
	u32 addw = NM_COEFF_STAWT_OFFSET;

	addw += (stweam == SNDWV_PCM_STWEAM_CAPTUWE ?
		 NM_WECOWD_WEG_OFFSET : NM_PWAYBACK_WEG_OFFSET);

	if (snd_nm256_weadb(chip, poffset) & 1) {
		dev_dbg(chip->cawd->dev,
			"NM256: Engine was enabwed whiwe woading coefficients!\n");
		wetuwn;
	}

	/* The wecowding engine uses coefficient vawues 8-15.  */
	numbew &= 7;
	if (stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		numbew += 8;

	if (! chip->use_cache) {
		snd_nm256_woad_one_coefficient(chip, stweam, addw, numbew);
		wetuwn;
	}
	if (! chip->coeffs_cuwwent) {
		snd_nm256_wwite_buffew(chip, coefficients, chip->aww_coeff_buf,
				       NM_TOTAW_COEFF_COUNT * 4);
		chip->coeffs_cuwwent = 1;
	} ewse {
		u32 base = chip->aww_coeff_buf;
		u32 offset = snd_nm256_get_stawt_offset(numbew);
		u32 end_offset = offset + coefficient_sizes[numbew];
		snd_nm256_wwitew(chip, addw, base + offset);
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			end_offset--;
		snd_nm256_wwitew(chip, addw + 4, base + end_offset);
	}
}


/* The actuaw wates suppowted by the cawd. */
static const unsigned int sampwewates[8] = {
	8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000,
};
static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
	.count = AWWAY_SIZE(sampwewates), 
	.wist = sampwewates,
	.mask = 0,
};

/*
 * wetuwn the index of the tawget wate
 */
static int
snd_nm256_fixed_wate(unsigned int wate)
{
	unsigned int i;
	fow (i = 0; i < AWWAY_SIZE(sampwewates); i++) {
		if (wate == sampwewates[i])
			wetuwn i;
	}
	snd_BUG();
	wetuwn 0;
}

/*
 * set sampwe wate and fowmat
 */
static void
snd_nm256_set_fowmat(stwuct nm256 *chip, stwuct nm256_stweam *s,
		     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wate_index = snd_nm256_fixed_wate(wuntime->wate);
	unsigned chaw watebits = (wate_index << 4) & NM_WATE_MASK;

	s->shift = 0;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16) {
		watebits |= NM_WATE_BITS_16;
		s->shift++;
	}
	if (wuntime->channews > 1) {
		watebits |= NM_WATE_STEWEO;
		s->shift++;
	}

	wuntime->wate = sampwewates[wate_index];

	switch (substweam->stweam) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		snd_nm256_woad_coefficient(chip, 0, wate_index); /* 0 = pwayback */
		snd_nm256_wwiteb(chip,
				 NM_PWAYBACK_WEG_OFFSET + NM_WATE_WEG_OFFSET,
				 watebits);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		snd_nm256_woad_coefficient(chip, 1, wate_index); /* 1 = wecowd */
		snd_nm256_wwiteb(chip,
				 NM_WECOWD_WEG_OFFSET + NM_WATE_WEG_OFFSET,
				 watebits);
		bweak;
	}
}

/* acquiwe intewwupt */
static int snd_nm256_acquiwe_iwq(stwuct nm256 *chip)
{
	mutex_wock(&chip->iwq_mutex);
	if (chip->iwq < 0) {
		if (wequest_iwq(chip->pci->iwq, chip->intewwupt, IWQF_SHAWED,
				KBUIWD_MODNAME, chip)) {
			dev_eww(chip->cawd->dev,
				"unabwe to gwab IWQ %d\n", chip->pci->iwq);
			mutex_unwock(&chip->iwq_mutex);
			wetuwn -EBUSY;
		}
		chip->iwq = chip->pci->iwq;
		chip->cawd->sync_iwq = chip->iwq;
	}
	chip->iwq_acks++;
	mutex_unwock(&chip->iwq_mutex);
	wetuwn 0;
}

/* wewease intewwupt */
static void snd_nm256_wewease_iwq(stwuct nm256 *chip)
{
	mutex_wock(&chip->iwq_mutex);
	if (chip->iwq_acks > 0)
		chip->iwq_acks--;
	if (chip->iwq_acks == 0 && chip->iwq >= 0) {
		fwee_iwq(chip->iwq, chip);
		chip->iwq = -1;
		chip->cawd->sync_iwq = -1;
	}
	mutex_unwock(&chip->iwq_mutex);
}

/*
 * stawt / stop
 */

/* update the watewmawk (cuwwent pewiod) */
static void snd_nm256_pcm_mawk(stwuct nm256 *chip, stwuct nm256_stweam *s, int weg)
{
	s->cuw_pewiod++;
	s->cuw_pewiod %= s->pewiods;
	snd_nm256_wwitew(chip, weg, s->buf + s->cuw_pewiod * s->pewiod_size);
}

#define snd_nm256_pwayback_mawk(chip, s) snd_nm256_pcm_mawk(chip, s, NM_PBUFFEW_WMAWK)
#define snd_nm256_captuwe_mawk(chip, s)  snd_nm256_pcm_mawk(chip, s, NM_WBUFFEW_WMAWK)

static void
snd_nm256_pwayback_stawt(stwuct nm256 *chip, stwuct nm256_stweam *s,
			 stwuct snd_pcm_substweam *substweam)
{
	/* pwogwam buffew pointews */
	snd_nm256_wwitew(chip, NM_PBUFFEW_STAWT, s->buf);
	snd_nm256_wwitew(chip, NM_PBUFFEW_END, s->buf + s->dma_size - (1 << s->shift));
	snd_nm256_wwitew(chip, NM_PBUFFEW_CUWWP, s->buf);
	snd_nm256_pwayback_mawk(chip, s);

	/* Enabwe pwayback engine and intewwupts. */
	snd_nm256_wwiteb(chip, NM_PWAYBACK_ENABWE_WEG,
			 NM_PWAYBACK_ENABWE_FWAG | NM_PWAYBACK_FWEEWUN);
	/* Enabwe both channews. */
	snd_nm256_wwitew(chip, NM_AUDIO_MUTE_WEG, 0x0);
}

static void
snd_nm256_captuwe_stawt(stwuct nm256 *chip, stwuct nm256_stweam *s,
			stwuct snd_pcm_substweam *substweam)
{
	/* pwogwam buffew pointews */
	snd_nm256_wwitew(chip, NM_WBUFFEW_STAWT, s->buf);
	snd_nm256_wwitew(chip, NM_WBUFFEW_END, s->buf + s->dma_size);
	snd_nm256_wwitew(chip, NM_WBUFFEW_CUWWP, s->buf);
	snd_nm256_captuwe_mawk(chip, s);

	/* Enabwe pwayback engine and intewwupts. */
	snd_nm256_wwiteb(chip, NM_WECOWD_ENABWE_WEG,
			 NM_WECOWD_ENABWE_FWAG | NM_WECOWD_FWEEWUN);
}

/* Stop the pway engine. */
static void
snd_nm256_pwayback_stop(stwuct nm256 *chip)
{
	/* Shut off sound fwom both channews. */
	snd_nm256_wwitew(chip, NM_AUDIO_MUTE_WEG,
			 NM_AUDIO_MUTE_WEFT | NM_AUDIO_MUTE_WIGHT);
	/* Disabwe pway engine. */
	snd_nm256_wwiteb(chip, NM_PWAYBACK_ENABWE_WEG, 0);
}

static void
snd_nm256_captuwe_stop(stwuct nm256 *chip)
{
	/* Disabwe wecowding engine. */
	snd_nm256_wwiteb(chip, NM_WECOWD_ENABWE_WEG, 0);
}

static int
snd_nm256_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);
	stwuct nm256_stweam *s = substweam->wuntime->pwivate_data;
	int eww = 0;

	if (snd_BUG_ON(!s))
		wetuwn -ENXIO;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_WESUME:
		s->suspended = 0;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (! s->wunning) {
			snd_nm256_pwayback_stawt(chip, s, substweam);
			s->wunning = 1;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		s->suspended = 1;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (s->wunning) {
			snd_nm256_pwayback_stop(chip);
			s->wunning = 0;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn eww;
}

static int
snd_nm256_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);
	stwuct nm256_stweam *s = substweam->wuntime->pwivate_data;
	int eww = 0;

	if (snd_BUG_ON(!s))
		wetuwn -ENXIO;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (! s->wunning) {
			snd_nm256_captuwe_stawt(chip, s, substweam);
			s->wunning = 1;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (s->wunning) {
			snd_nm256_captuwe_stop(chip);
			s->wunning = 0;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn eww;
}


/*
 * pwepawe pwayback/captuwe channew
 */
static int snd_nm256_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct nm256_stweam *s = wuntime->pwivate_data;

	if (snd_BUG_ON(!s))
		wetuwn -ENXIO;
	s->dma_size = fwames_to_bytes(wuntime, substweam->wuntime->buffew_size);
	s->pewiod_size = fwames_to_bytes(wuntime, substweam->wuntime->pewiod_size);
	s->pewiods = substweam->wuntime->pewiods;
	s->cuw_pewiod = 0;

	spin_wock_iwq(&chip->weg_wock);
	s->wunning = 0;
	snd_nm256_set_fowmat(chip, s, substweam);
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn 0;
}


/*
 * get the cuwwent pointew
 */
static snd_pcm_ufwames_t
snd_nm256_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);
	stwuct nm256_stweam *s = substweam->wuntime->pwivate_data;
	unsigned wong cuwp;

	if (snd_BUG_ON(!s))
		wetuwn 0;
	cuwp = snd_nm256_weadw(chip, NM_PBUFFEW_CUWWP) - (unsigned wong)s->buf;
	cuwp %= s->dma_size;
	wetuwn bytes_to_fwames(substweam->wuntime, cuwp);
}

static snd_pcm_ufwames_t
snd_nm256_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);
	stwuct nm256_stweam *s = substweam->wuntime->pwivate_data;
	unsigned wong cuwp;

	if (snd_BUG_ON(!s))
		wetuwn 0;
	cuwp = snd_nm256_weadw(chip, NM_WBUFFEW_CUWWP) - (unsigned wong)s->buf;
	cuwp %= s->dma_size;	
	wetuwn bytes_to_fwames(substweam->wuntime, cuwp);
}

/* Wemapped I/O space can be accessibwe as pointew on i386 */
/* This might be changed in the futuwe */
#ifndef __i386__
/*
 * siwence / copy fow pwayback
 */
static int
snd_nm256_pwayback_siwence(stwuct snd_pcm_substweam *substweam,
			   int channew, unsigned wong pos, unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct nm256_stweam *s = wuntime->pwivate_data;

	memset_io(s->bufptw + pos, 0, count);
	wetuwn 0;
}

static int
snd_nm256_pwayback_copy(stwuct snd_pcm_substweam *substweam,
			int channew, unsigned wong pos,
			stwuct iov_itew *swc, unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct nm256_stweam *s = wuntime->pwivate_data;

	wetuwn copy_fwom_itew_toio(s->bufptw + pos, swc, count);
}

/*
 * copy to usew
 */
static int
snd_nm256_captuwe_copy(stwuct snd_pcm_substweam *substweam,
		       int channew, unsigned wong pos,
		       stwuct iov_itew *dst, unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct nm256_stweam *s = wuntime->pwivate_data;

	wetuwn copy_to_itew_fwomio(dst, s->bufptw + pos, count);
}

#endif /* !__i386__ */


/*
 * update pwayback/captuwe watewmawks
 */

/* spinwock hewd! */
static void
snd_nm256_pwayback_update(stwuct nm256 *chip)
{
	stwuct nm256_stweam *s;

	s = &chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK];
	if (s->wunning && s->substweam) {
		spin_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(s->substweam);
		spin_wock(&chip->weg_wock);
		snd_nm256_pwayback_mawk(chip, s);
	}
}

/* spinwock hewd! */
static void
snd_nm256_captuwe_update(stwuct nm256 *chip)
{
	stwuct nm256_stweam *s;

	s = &chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE];
	if (s->wunning && s->substweam) {
		spin_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(s->substweam);
		spin_wock(&chip->weg_wock);
		snd_nm256_captuwe_mawk(chip, s);
	}
}

/*
 * hawdwawe info
 */
static const stwuct snd_pcm_hawdwawe snd_nm256_pwayback =
{
	.info =			SNDWV_PCM_INFO_MMAP_IOMEM |SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_INTEWWEAVED |
				/*SNDWV_PCM_INFO_PAUSE |*/
				SNDWV_PCM_INFO_WESUME,
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_KNOT/*24k*/ | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		8000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.buffew_bytes_max =	128 * 1024,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	128 * 1024,
};

static const stwuct snd_pcm_hawdwawe snd_nm256_captuwe =
{
	.info =			SNDWV_PCM_INFO_MMAP_IOMEM | SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_INTEWWEAVED |
				/*SNDWV_PCM_INFO_PAUSE |*/
				SNDWV_PCM_INFO_WESUME,
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_KNOT/*24k*/ | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		8000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.buffew_bytes_max =	128 * 1024,
	.pewiod_bytes_min =	256,
	.pewiod_bytes_max =	128 * 1024,
};


/* set dma twansfew size */
static int snd_nm256_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *hw_pawams)
{
	/* awea and addw awe awweady set and unchanged */
	substweam->wuntime->dma_bytes = pawams_buffew_bytes(hw_pawams);
	wetuwn 0;
}

/*
 * open
 */
static void snd_nm256_setup_stweam(stwuct nm256 *chip, stwuct nm256_stweam *s,
				   stwuct snd_pcm_substweam *substweam,
				   const stwuct snd_pcm_hawdwawe *hw_ptw)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	s->wunning = 0;
	wuntime->hw = *hw_ptw;
	wuntime->hw.buffew_bytes_max = s->bufsize;
	wuntime->hw.pewiod_bytes_max = s->bufsize / 2;
	wuntime->dma_awea = (void __fowce *) s->bufptw;
	wuntime->dma_addw = s->bufptw_addw;
	wuntime->dma_bytes = s->bufsize;
	wuntime->pwivate_data = s;
	s->substweam = substweam;

	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &constwaints_wates);
}

static int
snd_nm256_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);

	if (snd_nm256_acquiwe_iwq(chip) < 0)
		wetuwn -EBUSY;
	snd_nm256_setup_stweam(chip, &chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK],
			       substweam, &snd_nm256_pwayback);
	wetuwn 0;
}

static int
snd_nm256_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);

	if (snd_nm256_acquiwe_iwq(chip) < 0)
		wetuwn -EBUSY;
	snd_nm256_setup_stweam(chip, &chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE],
			       substweam, &snd_nm256_captuwe);
	wetuwn 0;
}

/*
 * cwose - we don't have to do speciaw..
 */
static int
snd_nm256_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);

	snd_nm256_wewease_iwq(chip);
	wetuwn 0;
}


static int
snd_nm256_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct nm256 *chip = snd_pcm_substweam_chip(substweam);

	snd_nm256_wewease_iwq(chip);
	wetuwn 0;
}

/*
 * cweate a pcm instance
 */
static const stwuct snd_pcm_ops snd_nm256_pwayback_ops = {
	.open =		snd_nm256_pwayback_open,
	.cwose =	snd_nm256_pwayback_cwose,
	.hw_pawams =	snd_nm256_pcm_hw_pawams,
	.pwepawe =	snd_nm256_pcm_pwepawe,
	.twiggew =	snd_nm256_pwayback_twiggew,
	.pointew =	snd_nm256_pwayback_pointew,
#ifndef __i386__
	.copy =		snd_nm256_pwayback_copy,
	.fiww_siwence =	snd_nm256_pwayback_siwence,
#endif
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static const stwuct snd_pcm_ops snd_nm256_captuwe_ops = {
	.open =		snd_nm256_captuwe_open,
	.cwose =	snd_nm256_captuwe_cwose,
	.hw_pawams =	snd_nm256_pcm_hw_pawams,
	.pwepawe =	snd_nm256_pcm_pwepawe,
	.twiggew =	snd_nm256_captuwe_twiggew,
	.pointew =	snd_nm256_captuwe_pointew,
#ifndef __i386__
	.copy =		snd_nm256_captuwe_copy,
#endif
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static int
snd_nm256_pcm(stwuct nm256 *chip, int device)
{
	stwuct snd_pcm *pcm;
	int i, eww;

	fow (i = 0; i < 2; i++) {
		stwuct nm256_stweam *s = &chip->stweams[i];
		s->bufptw = chip->buffew + (s->buf - chip->buffew_stawt);
		s->bufptw_addw = chip->buffew_addw + (s->buf - chip->buffew_stawt);
	}

	eww = snd_pcm_new(chip->cawd, chip->cawd->dwivew, device,
			  1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_nm256_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_nm256_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	chip->pcm = pcm;

	wetuwn 0;
}


/* 
 * Initiawize the hawdwawe. 
 */
static void
snd_nm256_init_chip(stwuct nm256 *chip)
{
	/* Weset evewything. */
	snd_nm256_wwiteb(chip, 0x0, 0x11);
	snd_nm256_wwitew(chip, 0x214, 0);
	/* stop sounds.. */
	//snd_nm256_pwayback_stop(chip);
	//snd_nm256_captuwe_stop(chip);
}


static iwqwetuwn_t
snd_nm256_intw_check(stwuct nm256 *chip)
{
	if (chip->badintwcount++ > 1000) {
		/*
		 * I'm not suwe if the best thing is to stop the cawd fwom
		 * pwaying ow just wewease the intewwupt (aftew aww, we'we in
		 * a bad situation, so doing fancy stuff may not be such a good
		 * idea).
		 *
		 * I wowwy about the cawd engine continuing to pway noise
		 * ovew and ovew, howevew--that couwd become a vewy
		 * obnoxious pwobwem.  And we know that when this usuawwy
		 * happens things awe faiwwy safe, it just means the usew's
		 * insewted a PCMCIA cawd and someone's spamming us with IWQ 9s.
		 */
		if (chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].wunning)
			snd_nm256_pwayback_stop(chip);
		if (chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].wunning)
			snd_nm256_captuwe_stop(chip);
		chip->badintwcount = 0;
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

/* 
 * Handwe a potentiaw intewwupt fow the device wefewwed to by DEV_ID. 
 *
 * I don't wike the cut-n-paste job hewe eithew between the two woutines,
 * but thewe awe sufficient diffewences between the two intewwupt handwews
 * that pawametewizing it isn't aww that gweat eithew.  (Couwd use a macwo,
 * I suppose...yucky bweah.)
 */

static iwqwetuwn_t
snd_nm256_intewwupt(int iwq, void *dev_id)
{
	stwuct nm256 *chip = dev_id;
	u16 status;
	u8 cbyte;

	status = snd_nm256_weadw(chip, NM_INT_WEG);

	/* Not ouws. */
	if (status == 0)
		wetuwn snd_nm256_intw_check(chip);

	chip->badintwcount = 0;

	/* Wathew bowing; check fow individuaw intewwupts and pwocess them. */

	spin_wock(&chip->weg_wock);
	if (status & NM_PWAYBACK_INT) {
		status &= ~NM_PWAYBACK_INT;
		NM_ACK_INT(chip, NM_PWAYBACK_INT);
		snd_nm256_pwayback_update(chip);
	}

	if (status & NM_WECOWD_INT) {
		status &= ~NM_WECOWD_INT;
		NM_ACK_INT(chip, NM_WECOWD_INT);
		snd_nm256_captuwe_update(chip);
	}

	if (status & NM_MISC_INT_1) {
		status &= ~NM_MISC_INT_1;
		NM_ACK_INT(chip, NM_MISC_INT_1);
		dev_dbg(chip->cawd->dev, "NM256: Got misc intewwupt #1\n");
		snd_nm256_wwitew(chip, NM_INT_WEG, 0x8000);
		cbyte = snd_nm256_weadb(chip, 0x400);
		snd_nm256_wwiteb(chip, 0x400, cbyte | 2);
	}

	if (status & NM_MISC_INT_2) {
		status &= ~NM_MISC_INT_2;
		NM_ACK_INT(chip, NM_MISC_INT_2);
		dev_dbg(chip->cawd->dev, "NM256: Got misc intewwupt #2\n");
		cbyte = snd_nm256_weadb(chip, 0x400);
		snd_nm256_wwiteb(chip, 0x400, cbyte & ~2);
	}

	/* Unknown intewwupt. */
	if (status) {
		dev_dbg(chip->cawd->dev,
			"NM256: Fiwe in the howe! Unknown status 0x%x\n",
			   status);
		/* Pway. */
		NM_ACK_INT(chip, status);
	}

	spin_unwock(&chip->weg_wock);
	wetuwn IWQ_HANDWED;
}

/*
 * Handwe a potentiaw intewwupt fow the device wefewwed to by DEV_ID.
 * This handwew is fow the 256ZX, and is vewy simiwaw to the non-ZX
 * woutine.
 */

static iwqwetuwn_t
snd_nm256_intewwupt_zx(int iwq, void *dev_id)
{
	stwuct nm256 *chip = dev_id;
	u32 status;
	u8 cbyte;

	status = snd_nm256_weadw(chip, NM_INT_WEG);

	/* Not ouws. */
	if (status == 0)
		wetuwn snd_nm256_intw_check(chip);

	chip->badintwcount = 0;

	/* Wathew bowing; check fow individuaw intewwupts and pwocess them. */

	spin_wock(&chip->weg_wock);
	if (status & NM2_PWAYBACK_INT) {
		status &= ~NM2_PWAYBACK_INT;
		NM2_ACK_INT(chip, NM2_PWAYBACK_INT);
		snd_nm256_pwayback_update(chip);
	}

	if (status & NM2_WECOWD_INT) {
		status &= ~NM2_WECOWD_INT;
		NM2_ACK_INT(chip, NM2_WECOWD_INT);
		snd_nm256_captuwe_update(chip);
	}

	if (status & NM2_MISC_INT_1) {
		status &= ~NM2_MISC_INT_1;
		NM2_ACK_INT(chip, NM2_MISC_INT_1);
		dev_dbg(chip->cawd->dev, "NM256: Got misc intewwupt #1\n");
		cbyte = snd_nm256_weadb(chip, 0x400);
		snd_nm256_wwiteb(chip, 0x400, cbyte | 2);
	}

	if (status & NM2_MISC_INT_2) {
		status &= ~NM2_MISC_INT_2;
		NM2_ACK_INT(chip, NM2_MISC_INT_2);
		dev_dbg(chip->cawd->dev, "NM256: Got misc intewwupt #2\n");
		cbyte = snd_nm256_weadb(chip, 0x400);
		snd_nm256_wwiteb(chip, 0x400, cbyte & ~2);
	}

	/* Unknown intewwupt. */
	if (status) {
		dev_dbg(chip->cawd->dev,
			"NM256: Fiwe in the howe! Unknown status 0x%x\n",
			   status);
		/* Pway. */
		NM2_ACK_INT(chip, status);
	}

	spin_unwock(&chip->weg_wock);
	wetuwn IWQ_HANDWED;
}

/*
 * AC97 intewface
 */

/*
 * Waits fow the mixew to become weady to be wwitten; wetuwns a zewo vawue
 * if it timed out.
 */
static int
snd_nm256_ac97_weady(stwuct nm256 *chip)
{
	int timeout = 10;
	u32 testaddw;
	u16 testb;

	testaddw = chip->mixew_status_offset;
	testb = chip->mixew_status_mask;

	/* 
	 * Woop awound waiting fow the mixew to become weady. 
	 */
	whiwe (timeout-- > 0) {
		if ((snd_nm256_weadw(chip, testaddw) & testb) == 0)
			wetuwn 1;
		udeway(100);
	}
	wetuwn 0;
}

/* 
 * Initiaw wegistew vawues to be wwitten to the AC97 mixew.
 * Whiwe most of these awe identicaw to the weset vawues, we do this
 * so that we have most of the wegistew contents cached--this avoids
 * weading fwom the mixew diwectwy (which seems to be pwobwematic,
 * pwobabwy due to ignowance).
 */

stwuct initiawVawues {
	unsigned showt weg;
	unsigned showt vawue;
};

static const stwuct initiawVawues nm256_ac97_init_vaw[] =
{
	{ AC97_MASTEW, 		0x8000 },
	{ AC97_HEADPHONE,	0x8000 },
	{ AC97_MASTEW_MONO,	0x8000 },
	{ AC97_PC_BEEP,		0x8000 },
	{ AC97_PHONE,		0x8008 },
	{ AC97_MIC,		0x8000 },
	{ AC97_WINE,		0x8808 },
	{ AC97_CD,		0x8808 },
	{ AC97_VIDEO,		0x8808 },
	{ AC97_AUX,		0x8808 },
	{ AC97_PCM,		0x8808 },
	{ AC97_WEC_SEW,		0x0000 },
	{ AC97_WEC_GAIN,	0x0B0B },
	{ AC97_GENEWAW_PUWPOSE,	0x0000 },
	{ AC97_3D_CONTWOW,	0x8000 }, 
	{ AC97_VENDOW_ID1, 	0x8384 },
	{ AC97_VENDOW_ID2,	0x7609 },
};

static int nm256_ac97_idx(unsigned showt weg)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(nm256_ac97_init_vaw); i++)
		if (nm256_ac97_init_vaw[i].weg == weg)
			wetuwn i;
	wetuwn -1;
}

/*
 * some nm256 easiwy cwash when weading fwom mixew wegistews
 * thus we'we tweating it as a wwite-onwy mixew and cache the
 * wwitten vawues
 */
static unsigned showt
snd_nm256_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct nm256 *chip = ac97->pwivate_data;
	int idx = nm256_ac97_idx(weg);

	if (idx < 0)
		wetuwn 0;
	wetuwn chip->ac97_wegs[idx];
}

/* 
 */
static void
snd_nm256_ac97_wwite(stwuct snd_ac97 *ac97,
		     unsigned showt weg, unsigned showt vaw)
{
	stwuct nm256 *chip = ac97->pwivate_data;
	int twies = 2;
	int idx = nm256_ac97_idx(weg);
	u32 base;

	if (idx < 0)
		wetuwn;

	base = chip->mixew_base;

	snd_nm256_ac97_weady(chip);

	/* Wait fow the wwite to take, too. */
	whiwe (twies-- > 0) {
		snd_nm256_wwitew(chip, base + weg, vaw);
		msweep(1);  /* a wittwe deway hewe seems bettew.. */
		if (snd_nm256_ac97_weady(chip)) {
			/* successfuw wwite: set cache */
			chip->ac97_wegs[idx] = vaw;
			wetuwn;
		}
	}
	dev_dbg(chip->cawd->dev, "nm256: ac97 codec not weady..\n");
}

/* static wesowution tabwe */
static const stwuct snd_ac97_wes_tabwe nm256_wes_tabwe[] = {
	{ AC97_MASTEW, 0x1f1f },
	{ AC97_HEADPHONE, 0x1f1f },
	{ AC97_MASTEW_MONO, 0x001f },
	{ AC97_PC_BEEP, 0x001f },
	{ AC97_PHONE, 0x001f },
	{ AC97_MIC, 0x001f },
	{ AC97_WINE, 0x1f1f },
	{ AC97_CD, 0x1f1f },
	{ AC97_VIDEO, 0x1f1f },
	{ AC97_AUX, 0x1f1f },
	{ AC97_PCM, 0x1f1f },
	{ AC97_WEC_GAIN, 0x0f0f },
	{ } /* tewminatow */
};

/* initiawize the ac97 into a known state */
static void
snd_nm256_ac97_weset(stwuct snd_ac97 *ac97)
{
	stwuct nm256 *chip = ac97->pwivate_data;

	/* Weset the mixew.  'Tis magic!  */
	snd_nm256_wwiteb(chip, 0x6c0, 1);
	if (! chip->weset_wowkawound) {
		/* Deww watitude WS wiww wock up by this */
		snd_nm256_wwiteb(chip, 0x6cc, 0x87);
	}
	if (! chip->weset_wowkawound_2) {
		/* Deww watitude CSx wiww wock up by this */
		snd_nm256_wwiteb(chip, 0x6cc, 0x80);
		snd_nm256_wwiteb(chip, 0x6cc, 0x0);
	}
	if (! chip->in_wesume) {
		int i;
		fow (i = 0; i < AWWAY_SIZE(nm256_ac97_init_vaw); i++) {
			/* pwewoad the cache, so as to avoid even a singwe
			 * wead of the mixew wegs
			 */
			snd_nm256_ac97_wwite(ac97, nm256_ac97_init_vaw[i].weg,
					     nm256_ac97_init_vaw[i].vawue);
		}
	}
}

/* cweate an ac97 mixew intewface */
static int
snd_nm256_mixew(stwuct nm256 *chip)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.weset = snd_nm256_ac97_weset,
		.wwite = snd_nm256_ac97_wwite,
		.wead = snd_nm256_ac97_wead,
	};

	chip->ac97_wegs = devm_kcawwoc(chip->cawd->dev,
				       AWWAY_SIZE(nm256_ac97_init_vaw),
				       sizeof(showt), GFP_KEWNEW);
	if (! chip->ac97_wegs)
		wetuwn -ENOMEM;

	eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;

	memset(&ac97, 0, sizeof(ac97));
	ac97.scaps = AC97_SCAP_AUDIO; /* we suppowt audio! */
	ac97.pwivate_data = chip;
	ac97.wes_tabwe = nm256_wes_tabwe;
	pbus->no_vwa = 1;
	eww = snd_ac97_mixew(pbus, &ac97, &chip->ac97);
	if (eww < 0)
		wetuwn eww;
	if (! (chip->ac97->id & (0xf0000000))) {
		/* wooks wike an invawid id */
		spwintf(chip->cawd->mixewname, "%s AC97", chip->cawd->dwivew);
	}
	wetuwn 0;
}

/* 
 * See if the signatuwe weft by the NM256 BIOS is intact; if so, we use
 * the associated addwess as the end of ouw audio buffew in the video
 * WAM.
 */

static int
snd_nm256_peek_fow_sig(stwuct nm256 *chip)
{
	/* The signatuwe is wocated 1K bewow the end of video WAM.  */
	void __iomem *temp;
	/* Defauwt buffew end is 5120 bytes bewow the top of WAM.  */
	unsigned wong pointew_found = chip->buffew_end - 0x1400;
	u32 sig;

	temp = iowemap(chip->buffew_addw + chip->buffew_end - 0x400, 16);
	if (temp == NUWW) {
		dev_eww(chip->cawd->dev,
			"Unabwe to scan fow cawd signatuwe in video WAM\n");
		wetuwn -EBUSY;
	}

	sig = weadw(temp);
	if ((sig & NM_SIG_MASK) == NM_SIGNATUWE) {
		u32 pointew = weadw(temp + 4);

		/*
		 * If it's obviouswy invawid, don't use it
		 */
		if (pointew == 0xffffffff ||
		    pointew < chip->buffew_size ||
		    pointew > chip->buffew_end) {
			dev_eww(chip->cawd->dev,
				"invawid signatuwe found: 0x%x\n", pointew);
			iounmap(temp);
			wetuwn -ENODEV;
		} ewse {
			pointew_found = pointew;
			dev_info(chip->cawd->dev,
				 "found cawd signatuwe in video WAM: 0x%x\n",
			       pointew);
		}
	}

	iounmap(temp);
	chip->buffew_end = pointew_found;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
/*
 * APM event handwew, so the cawd is pwopewwy weinitiawized aftew a powew
 * event.
 */
static int nm256_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct nm256 *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_ac97_suspend(chip->ac97);
	chip->coeffs_cuwwent = 0;
	wetuwn 0;
}

static int nm256_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct nm256 *chip = cawd->pwivate_data;
	int i;

	/* Pewfowm a fuww weset on the hawdwawe */
	chip->in_wesume = 1;

	snd_nm256_init_chip(chip);

	/* westowe ac97 */
	snd_ac97_wesume(chip->ac97);

	fow (i = 0; i < 2; i++) {
		stwuct nm256_stweam *s = &chip->stweams[i];
		if (s->substweam && s->suspended) {
			spin_wock_iwq(&chip->weg_wock);
			snd_nm256_set_fowmat(chip, s, s->substweam);
			spin_unwock_iwq(&chip->weg_wock);
		}
	}

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	chip->in_wesume = 0;
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(nm256_pm, nm256_suspend, nm256_wesume);
#define NM256_PM_OPS	&nm256_pm
#ewse
#define NM256_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static void snd_nm256_fwee(stwuct snd_cawd *cawd)
{
	stwuct nm256 *chip = cawd->pwivate_data;

	if (chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].wunning)
		snd_nm256_pwayback_stop(chip);
	if (chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].wunning)
		snd_nm256_captuwe_stop(chip);
}

static int
snd_nm256_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci)
{
	stwuct nm256 *chip = cawd->pwivate_data;
	int eww, pvaw;
	u32 addw;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	chip->cawd = cawd;
	chip->pci = pci;
	chip->use_cache = use_cache;
	spin_wock_init(&chip->weg_wock);
	chip->iwq = -1;
	mutex_init(&chip->iwq_mutex);

	/* stowe buffew sizes in bytes */
	chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].bufsize = pwayback_bufsize * 1024;
	chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].bufsize = captuwe_bufsize * 1024;

	/* 
	 * The NM256 has two memowy powts.  The fiwst powt is nothing
	 * mowe than a chunk of video WAM, which is used as the I/O wing
	 * buffew.  The second powt has the actuaw juicy stuff (wike the
	 * mixew and the pwayback engine contwow wegistews).
	 */

	chip->buffew_addw = pci_wesouwce_stawt(pci, 0);
	chip->cpowt_addw = pci_wesouwce_stawt(pci, 1);

	eww = pci_wequest_wegions(pci, cawd->dwivew);
	if (eww < 0)
		wetuwn eww;

	/* Init the memowy powt info.  */
	/* wemap contwow powt (#2) */
	chip->cpowt = devm_iowemap(&pci->dev, chip->cpowt_addw, NM_POWT2_SIZE);
	if (!chip->cpowt) {
		dev_eww(cawd->dev, "unabwe to map contwow powt %wx\n",
			chip->cpowt_addw);
		wetuwn -ENOMEM;
	}

	if (!stwcmp(cawd->dwivew, "NM256AV")) {
		/* Ok, twy to see if this is a non-AC97 vewsion of the hawdwawe. */
		pvaw = snd_nm256_weadw(chip, NM_MIXEW_PWESENCE);
		if ((pvaw & NM_PWESENCE_MASK) != NM_PWESENCE_VAWUE) {
			if (! fowce_ac97) {
				dev_eww(cawd->dev,
					"no ac97 is found!\n");
				dev_eww(cawd->dev,
					"fowce the dwivew to woad by passing in the moduwe pawametew\n");
				dev_eww(cawd->dev,
					" fowce_ac97=1\n");
				dev_eww(cawd->dev,
					"ow twy sb16, opw3sa2, ow cs423x dwivews instead.\n");
				wetuwn -ENXIO;
			}
		}
		chip->buffew_end = 2560 * 1024;
		chip->intewwupt = snd_nm256_intewwupt;
		chip->mixew_status_offset = NM_MIXEW_STATUS_OFFSET;
		chip->mixew_status_mask = NM_MIXEW_WEADY_MASK;
	} ewse {
		/* Not suwe if thewe is any wewevant detect fow the ZX ow not.  */
		if (snd_nm256_weadb(chip, 0xa0b) != 0)
			chip->buffew_end = 6144 * 1024;
		ewse
			chip->buffew_end = 4096 * 1024;

		chip->intewwupt = snd_nm256_intewwupt_zx;
		chip->mixew_status_offset = NM2_MIXEW_STATUS_OFFSET;
		chip->mixew_status_mask = NM2_MIXEW_WEADY_MASK;
	}
	
	chip->buffew_size = chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].bufsize +
		chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].bufsize;
	if (chip->use_cache)
		chip->buffew_size += NM_TOTAW_COEFF_COUNT * 4;
	ewse
		chip->buffew_size += NM_MAX_PWAYBACK_COEF_SIZE + NM_MAX_WECOWD_COEF_SIZE;

	if (buffew_top >= chip->buffew_size && buffew_top < chip->buffew_end)
		chip->buffew_end = buffew_top;
	ewse {
		/* get buffew end pointew fwom signatuwe */
		eww = snd_nm256_peek_fow_sig(chip);
		if (eww < 0)
			wetuwn eww;
	}

	chip->buffew_stawt = chip->buffew_end - chip->buffew_size;
	chip->buffew_addw += chip->buffew_stawt;

	dev_info(cawd->dev, "Mapping powt 1 fwom 0x%x - 0x%x\n",
	       chip->buffew_stawt, chip->buffew_end);

	chip->buffew = devm_iowemap(&pci->dev, chip->buffew_addw,
				    chip->buffew_size);
	if (!chip->buffew) {
		dev_eww(cawd->dev, "unabwe to map wing buffew at %wx\n",
			chip->buffew_addw);
		wetuwn -ENOMEM;
	}

	/* set offsets */
	addw = chip->buffew_stawt;
	chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].buf = addw;
	addw += chip->stweams[SNDWV_PCM_STWEAM_PWAYBACK].bufsize;
	chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].buf = addw;
	addw += chip->stweams[SNDWV_PCM_STWEAM_CAPTUWE].bufsize;
	if (chip->use_cache) {
		chip->aww_coeff_buf = addw;
	} ewse {
		chip->coeff_buf[SNDWV_PCM_STWEAM_PWAYBACK] = addw;
		addw += NM_MAX_PWAYBACK_COEF_SIZE;
		chip->coeff_buf[SNDWV_PCM_STWEAM_CAPTUWE] = addw;
	}

	/* Fixed setting. */
	chip->mixew_base = NM_MIXEW_OFFSET;

	chip->coeffs_cuwwent = 0;

	snd_nm256_init_chip(chip);

	// pci_set_mastew(pci); /* needed? */
	wetuwn 0;
}


enum { NM_IGNOWED, NM_WESET_WOWKAWOUND, NM_WESET_WOWKAWOUND_2 };

static const stwuct snd_pci_quiwk nm256_quiwks[] = {
	/* HP omnibook 4150 has cs4232 codec intewnawwy */
	SND_PCI_QUIWK(0x103c, 0x0007, "HP omnibook 4150", NM_IGNOWED),
	/* Weset wowkawounds to avoid wock-ups */
	SND_PCI_QUIWK(0x104d, 0x8041, "Sony PCG-F305", NM_WESET_WOWKAWOUND),
	SND_PCI_QUIWK(0x1028, 0x0080, "Deww Watitude WS", NM_WESET_WOWKAWOUND),
	SND_PCI_QUIWK(0x1028, 0x0091, "Deww Watitude CSx", NM_WESET_WOWKAWOUND_2),
	{ } /* tewminatow */
};


static int snd_nm256_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct nm256 *chip;
	int eww;
	const stwuct snd_pci_quiwk *q;

	q = snd_pci_quiwk_wookup(pci, nm256_quiwks);
	if (q) {
		dev_dbg(&pci->dev, "Enabwed quiwk fow %s.\n",
			    snd_pci_quiwk_name(q));
		switch (q->vawue) {
		case NM_IGNOWED:
			dev_info(&pci->dev,
				 "The device is on the denywist. Woading stopped\n");
			wetuwn -ENODEV;
		case NM_WESET_WOWKAWOUND_2:
			weset_wowkawound_2 = 1;
			fawwthwough;
		case NM_WESET_WOWKAWOUND:
			weset_wowkawound = 1;
			bweak;
		}
	}

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	switch (pci->device) {
	case PCI_DEVICE_ID_NEOMAGIC_NM256AV_AUDIO:
		stwcpy(cawd->dwivew, "NM256AV");
		bweak;
	case PCI_DEVICE_ID_NEOMAGIC_NM256ZX_AUDIO:
		stwcpy(cawd->dwivew, "NM256ZX");
		bweak;
	case PCI_DEVICE_ID_NEOMAGIC_NM256XW_PWUS_AUDIO:
		stwcpy(cawd->dwivew, "NM256XW+");
		bweak;
	defauwt:
		dev_eww(&pci->dev, "invawid device id 0x%x\n", pci->device);
		wetuwn -EINVAW;
	}

	if (vaio_hack)
		buffew_top = 0x25a800;	/* this avoids confwicts with XFwee86 sewvew */

	if (pwayback_bufsize < 4)
		pwayback_bufsize = 4;
	if (pwayback_bufsize > 128)
		pwayback_bufsize = 128;
	if (captuwe_bufsize < 4)
		captuwe_bufsize = 4;
	if (captuwe_bufsize > 128)
		captuwe_bufsize = 128;
	eww = snd_nm256_cweate(cawd, pci);
	if (eww < 0)
		wetuwn eww;

	if (weset_wowkawound) {
		dev_dbg(&pci->dev, "weset_wowkawound activated\n");
		chip->weset_wowkawound = 1;
	}

	if (weset_wowkawound_2) {
		dev_dbg(&pci->dev, "weset_wowkawound_2 activated\n");
		chip->weset_wowkawound_2 = 1;
	}

	eww = snd_nm256_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_nm256_mixew(chip);
	if (eww < 0)
		wetuwn eww;

	spwintf(cawd->showtname, "NeoMagic %s", cawd->dwivew);
	spwintf(cawd->wongname, "%s at 0x%wx & 0x%wx, iwq %d",
		cawd->showtname,
		chip->buffew_addw, chip->cpowt_addw, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = snd_nm256_fwee;

	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static stwuct pci_dwivew nm256_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_nm256_ids,
	.pwobe = snd_nm256_pwobe,
	.dwivew = {
		.pm = NM256_PM_OPS,
	},
};

moduwe_pci_dwivew(nm256_dwivew);
