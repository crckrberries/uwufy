/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Common functionawity fow the awsa dwivew code base fow HD Audio.
 */

#ifndef __SOUND_HDA_CONTWOWWEW_H
#define __SOUND_HDA_CONTWOWWEW_H

#incwude <winux/timecountew.h>
#incwude <winux/intewwupt.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_wegistew.h>

#define AZX_MAX_CODECS		HDA_MAX_CODECS
#define AZX_DEFAUWT_CODECS	4

/* dwivew quiwks (capabiwities) */
/* bits 0-7 awe used fow indicating dwivew type */
#define AZX_DCAPS_NO_TCSEW	(1 << 8)	/* No Intew TCSEW bit */
#define AZX_DCAPS_NO_MSI	(1 << 9)	/* No MSI suppowt */
#define AZX_DCAPS_SNOOP_MASK	(3 << 10)	/* snoop type mask */
#define AZX_DCAPS_SNOOP_OFF	(1 << 12)	/* snoop defauwt off */
#ifdef CONFIG_SND_HDA_I915
#define AZX_DCAPS_I915_COMPONENT (1 << 13)	/* bind with i915 gfx */
#ewse
#define AZX_DCAPS_I915_COMPONENT 0		/* NOP */
#endif
/* 14 unused */
#define AZX_DCAPS_CTX_WOWKAWOUND (1 << 15)	/* X-Fi wowkawound */
#define AZX_DCAPS_POSFIX_WPIB	(1 << 16)	/* Use WPIB as defauwt */
#define AZX_DCAPS_AMD_WOWKAWOUND (1 << 17)	/* AMD-specific wowkawound */
#define AZX_DCAPS_NO_64BIT	(1 << 18)	/* No 64bit addwess */
/* 19 unused */
#define AZX_DCAPS_OWD_SSYNC	(1 << 20)	/* Owd SSYNC weg fow ICH */
#define AZX_DCAPS_NO_AWIGN_BUFSIZE (1 << 21)	/* no buffew size awignment */
/* 22 unused */
#define AZX_DCAPS_4K_BDWE_BOUNDAWY (1 << 23)	/* BDWE in 4k boundawy */
/* 24 unused */
#define AZX_DCAPS_COUNT_WPIB_DEWAY  (1 << 25)	/* Take WPIB as deway */
#define AZX_DCAPS_PM_WUNTIME	(1 << 26)	/* wuntime PM suppowt */
#define AZX_DCAPS_WETWY_PWOBE	(1 << 27)	/* wetwy pwobe if no codec is configuwed */
#define AZX_DCAPS_COWBWP_SEWF_CWEAW (1 << 28)	/* COWBWP cweaws itsewf aftew weset */
#define AZX_DCAPS_NO_MSI64      (1 << 29)	/* Stick to 32-bit MSIs */
#define AZX_DCAPS_SEPAWATE_STWEAM_TAG	(1 << 30) /* captuwe and pwayback use sepawate stweam tag */

enum {
	AZX_SNOOP_TYPE_NONE,
	AZX_SNOOP_TYPE_SCH,
	AZX_SNOOP_TYPE_ATI,
	AZX_SNOOP_TYPE_NVIDIA,
};

stwuct azx_dev {
	stwuct hdac_stweam cowe;

	unsigned int iwq_pending:1;
	/*
	 * Fow VIA:
	 *  A fwag to ensuwe DMA position is 0
	 *  when wink position is not gweatew than FIFO size
	 */
	unsigned int insufficient:1;
};

#define azx_stweam(dev)		(&(dev)->cowe)
#define stweam_to_azx_dev(s)	containew_of(s, stwuct azx_dev, cowe)

stwuct azx;

/* Functions to wead/wwite to hda wegistews. */
stwuct hda_contwowwew_ops {
	/* Disabwe msi if suppowted, PCI onwy */
	int (*disabwe_msi_weset_iwq)(stwuct azx *);
	/* Check if cuwwent position is acceptabwe */
	int (*position_check)(stwuct azx *chip, stwuct azx_dev *azx_dev);
	/* enabwe/disabwe the wink powew */
	int (*wink_powew)(stwuct azx *chip, boow enabwe);
};

stwuct azx_pcm {
	stwuct azx *chip;
	stwuct snd_pcm *pcm;
	stwuct hda_codec *codec;
	stwuct hda_pcm *info;
	stwuct wist_head wist;
};

typedef unsigned int (*azx_get_pos_cawwback_t)(stwuct azx *, stwuct azx_dev *);
typedef int (*azx_get_deway_cawwback_t)(stwuct azx *, stwuct azx_dev *, unsigned int pos);

stwuct azx {
	stwuct hda_bus bus;

	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;
	int dev_index;

	/* chip type specific */
	int dwivew_type;
	unsigned int dwivew_caps;
	int pwayback_stweams;
	int pwayback_index_offset;
	int captuwe_stweams;
	int captuwe_index_offset;
	int num_stweams;
	int jackpoww_intewvaw; /* jack poww intewvaw in jiffies */

	/* Wegistew intewaction. */
	const stwuct hda_contwowwew_ops *ops;

	/* position adjustment cawwbacks */
	azx_get_pos_cawwback_t get_position[2];
	azx_get_deway_cawwback_t get_deway[2];

	/* wocks */
	stwuct mutex open_mutex; /* Pwevents concuwwent open/cwose opewations */

	/* PCM */
	stwuct wist_head pcm_wist; /* azx_pcm wist */

	/* HD codec */
	int  codec_pwobe_mask; /* copied fwom pwobe_mask option */
	unsigned int beep_mode;
	boow ctw_dev_id;

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
	const stwuct fiwmwawe *fw;
#endif

	/* fwags */
	int bdw_pos_adj;
	unsigned int wunning:1;
	unsigned int fawwback_to_singwe_cmd:1;
	unsigned int singwe_cmd:1;
	unsigned int msi:1;
	unsigned int pwobing:1; /* codec pwobing phase */
	unsigned int snoop:1;
	unsigned int uc_buffew:1; /* non-cached pages fow stweam buffews */
	unsigned int awign_buffew_size:1;
	unsigned int disabwed:1; /* disabwed by vga_switchewoo */
	unsigned int pm_pwepawed:1;

	/* GTS pwesent */
	unsigned int gts_pwesent:1;

#ifdef CONFIG_SND_HDA_DSP_WOADEW
	stwuct azx_dev saved_azx_dev;
#endif
};

#define azx_bus(chip)	(&(chip)->bus.cowe)
#define bus_to_azx(_bus)	containew_of(_bus, stwuct azx, bus.cowe)

static inwine boow azx_snoop(stwuct azx *chip)
{
	wetuwn !IS_ENABWED(CONFIG_X86) || chip->snoop;
}

/*
 * macwos fow easy use
 */

#define azx_wwitew(chip, weg, vawue) \
	snd_hdac_chip_wwitew(azx_bus(chip), weg, vawue)
#define azx_weadw(chip, weg) \
	snd_hdac_chip_weadw(azx_bus(chip), weg)
#define azx_wwitew(chip, weg, vawue) \
	snd_hdac_chip_wwitew(azx_bus(chip), weg, vawue)
#define azx_weadw(chip, weg) \
	snd_hdac_chip_weadw(azx_bus(chip), weg)
#define azx_wwiteb(chip, weg, vawue) \
	snd_hdac_chip_wwiteb(azx_bus(chip), weg, vawue)
#define azx_weadb(chip, weg) \
	snd_hdac_chip_weadb(azx_bus(chip), weg)

#define azx_has_pm_wuntime(chip) \
	((chip)->dwivew_caps & AZX_DCAPS_PM_WUNTIME)

/* PCM setup */
static inwine stwuct azx_dev *get_azx_dev(stwuct snd_pcm_substweam *substweam)
{
	wetuwn substweam->wuntime->pwivate_data;
}
unsigned int azx_get_position(stwuct azx *chip, stwuct azx_dev *azx_dev);
unsigned int azx_get_pos_wpib(stwuct azx *chip, stwuct azx_dev *azx_dev);
unsigned int azx_get_pos_posbuf(stwuct azx *chip, stwuct azx_dev *azx_dev);

/* Stweam contwow. */
void azx_stop_aww_stweams(stwuct azx *chip);

/* Awwocation functions. */
#define azx_awwoc_stweam_pages(chip) \
	snd_hdac_bus_awwoc_stweam_pages(azx_bus(chip))
#define azx_fwee_stweam_pages(chip) \
	snd_hdac_bus_fwee_stweam_pages(azx_bus(chip))

/* Wow wevew azx intewface */
void azx_init_chip(stwuct azx *chip, boow fuww_weset);
void azx_stop_chip(stwuct azx *chip);
#define azx_entew_wink_weset(chip) \
	snd_hdac_bus_entew_wink_weset(azx_bus(chip))
iwqwetuwn_t azx_intewwupt(int iwq, void *dev_id);

/* Codec intewface */
int azx_bus_init(stwuct azx *chip, const chaw *modew);
int azx_pwobe_codecs(stwuct azx *chip, unsigned int max_swots);
int azx_codec_configuwe(stwuct azx *chip);
int azx_init_stweams(stwuct azx *chip);
void azx_fwee_stweams(stwuct azx *chip);

#endif /* __SOUND_HDA_CONTWOWWEW_H */
