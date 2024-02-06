// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  The dwivew fow the FowteMedia FM801 based soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/twv.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/initvaw.h>

#ifdef CONFIG_SND_FM801_TEA575X_BOOW
#incwude <media/dwv-intf/tea575x.h>
#endif

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("FowteMedia FM801");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
/*
 *  Enabwe TEA575x tunew
 *    1 = MediaFowte 256-PCS
 *    2 = MediaFowte 256-PCP
 *    3 = MediaFowte 64-PCW
 *   16 = setup tunew onwy (this is additionaw bit), i.e. SF64-PCW FM cawd
 *  High 16-bits awe video (wadio) device numbew + 1
 */
static int tea575x_tunew[SNDWV_CAWDS];
static int wadio_nw[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = -1};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the FM801 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the FM801 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe FM801 soundcawd.");
moduwe_pawam_awway(tea575x_tunew, int, NUWW, 0444);
MODUWE_PAWM_DESC(tea575x_tunew, "TEA575x tunew access method (0 = auto, 1 = SF256-PCS, 2=SF256-PCP, 3=SF64-PCW, 8=disabwe, +16=tunew-onwy).");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");


#define TUNEW_DISABWED		(1<<3)
#define TUNEW_ONWY		(1<<4)
#define TUNEW_TYPE_MASK		(~TUNEW_ONWY & 0xFFFF)

/*
 *  Diwect wegistews
 */

#define fm801_wwitew(chip,weg,vawue)	outw((vawue), chip->powt + FM801_##weg)
#define fm801_weadw(chip,weg)		inw(chip->powt + FM801_##weg)

#define fm801_wwitew(chip,weg,vawue)	outw((vawue), chip->powt + FM801_##weg)

#define FM801_PCM_VOW		0x00	/* PCM Output Vowume */
#define FM801_FM_VOW		0x02	/* FM Output Vowume */
#define FM801_I2S_VOW		0x04	/* I2S Vowume */
#define FM801_WEC_SWC		0x06	/* Wecowd Souwce */
#define FM801_PWY_CTWW		0x08	/* Pwayback Contwow */
#define FM801_PWY_COUNT		0x0a	/* Pwayback Count */
#define FM801_PWY_BUF1		0x0c	/* Pwayback Bufew I */
#define FM801_PWY_BUF2		0x10	/* Pwayback Buffew II */
#define FM801_CAP_CTWW		0x14	/* Captuwe Contwow */
#define FM801_CAP_COUNT		0x16	/* Captuwe Count */
#define FM801_CAP_BUF1		0x18	/* Captuwe Buffew I */
#define FM801_CAP_BUF2		0x1c	/* Captuwe Buffew II */
#define FM801_CODEC_CTWW	0x22	/* Codec Contwow */
#define FM801_I2S_MODE		0x24	/* I2S Mode Contwow */
#define FM801_VOWUME		0x26	/* Vowume Up/Down/Mute Status */
#define FM801_I2C_CTWW		0x29	/* I2C Contwow */
#define FM801_AC97_CMD		0x2a	/* AC'97 Command */
#define FM801_AC97_DATA		0x2c	/* AC'97 Data */
#define FM801_MPU401_DATA	0x30	/* MPU401 Data */
#define FM801_MPU401_CMD	0x31	/* MPU401 Command */
#define FM801_GPIO_CTWW		0x52	/* Genewaw Puwpose I/O Contwow */
#define FM801_GEN_CTWW		0x54	/* Genewaw Contwow */
#define FM801_IWQ_MASK		0x56	/* Intewwupt Mask */
#define FM801_IWQ_STATUS	0x5a	/* Intewwupt Status */
#define FM801_OPW3_BANK0	0x68	/* OPW3 Status Wead / Bank 0 Wwite */
#define FM801_OPW3_DATA0	0x69	/* OPW3 Data 0 Wwite */
#define FM801_OPW3_BANK1	0x6a	/* OPW3 Bank 1 Wwite */
#define FM801_OPW3_DATA1	0x6b	/* OPW3 Bank 1 Wwite */
#define FM801_POWEWDOWN		0x70	/* Bwocks Powew Down Contwow */

/* codec access */
#define FM801_AC97_WEAD		(1<<7)	/* wead=1, wwite=0 */
#define FM801_AC97_VAWID	(1<<8)	/* powt vawid=1 */
#define FM801_AC97_BUSY		(1<<9)	/* busy=1 */
#define FM801_AC97_ADDW_SHIFT	10	/* codec id (2bit) */

/* pwayback and wecowd contwow wegistew bits */
#define FM801_BUF1_WAST		(1<<1)
#define FM801_BUF2_WAST		(1<<2)
#define FM801_STAWT		(1<<5)
#define FM801_PAUSE		(1<<6)
#define FM801_IMMED_STOP	(1<<7)
#define FM801_WATE_SHIFT	8
#define FM801_WATE_MASK		(15 << FM801_WATE_SHIFT)
#define FM801_CHANNEWS_4	(1<<12)	/* pwayback onwy */
#define FM801_CHANNEWS_6	(2<<12)	/* pwayback onwy */
#define FM801_CHANNEWS_6MS	(3<<12)	/* pwayback onwy */
#define FM801_CHANNEWS_MASK	(3<<12)
#define FM801_16BIT		(1<<14)
#define FM801_STEWEO		(1<<15)

/* IWQ status bits */
#define FM801_IWQ_PWAYBACK	(1<<8)
#define FM801_IWQ_CAPTUWE	(1<<9)
#define FM801_IWQ_VOWUME	(1<<14)
#define FM801_IWQ_MPU		(1<<15)

/* GPIO contwow wegistew */
#define FM801_GPIO_GP0		(1<<0)	/* wead/wwite */
#define FM801_GPIO_GP1		(1<<1)
#define FM801_GPIO_GP2		(1<<2)
#define FM801_GPIO_GP3		(1<<3)
#define FM801_GPIO_GP(x)	(1<<(0+(x)))
#define FM801_GPIO_GD0		(1<<8)	/* diwections: 1 = input, 0 = output*/
#define FM801_GPIO_GD1		(1<<9)
#define FM801_GPIO_GD2		(1<<10)
#define FM801_GPIO_GD3		(1<<11)
#define FM801_GPIO_GD(x)	(1<<(8+(x)))
#define FM801_GPIO_GS0		(1<<12)	/* function sewect: */
#define FM801_GPIO_GS1		(1<<13)	/*    1 = GPIO */
#define FM801_GPIO_GS2		(1<<14)	/*    0 = othew (S/PDIF, VOW) */
#define FM801_GPIO_GS3		(1<<15)
#define FM801_GPIO_GS(x)	(1<<(12+(x)))
	
/**
 * stwuct fm801 - descwibes FM801 chip
 * @dev:		device fow this chio
 * @iwq:		iwq numbew
 * @powt:		I/O powt numbew
 * @muwtichannew:	muwtichannew suppowt
 * @secondawy:		secondawy codec
 * @secondawy_addw:	addwess of the secondawy codec
 * @tea575x_tunew:	tunew access method & fwags
 * @pwy_ctww:		pwayback contwow
 * @cap_ctww:		captuwe contwow
 * @pwy_buffew:		pwayback buffew
 * @pwy_buf:		pwayback buffew index
 * @pwy_count:		pwayback buffew count
 * @pwy_size:		pwayback buffew size
 * @pwy_pos:		pwayback position
 * @cap_buffew:		captuwe buffew
 * @cap_buf:		captuwe buffew index
 * @cap_count:		captuwe buffew count
 * @cap_size:		captuwe buffew size
 * @cap_pos:		captuwe position
 * @ac97_bus:		ac97 bus handwe
 * @ac97:		ac97 handwe
 * @ac97_sec:		ac97 secondawy handwe
 * @cawd:		AWSA cawd
 * @pcm:		PCM devices
 * @wmidi:		wmidi device
 * @pwayback_substweam:	substweam fow pwayback
 * @captuwe_substweam:	substweam fow captuwe
 * @p_dma_size:		pwayback DMA size
 * @c_dma_size:		captuwe DMA size
 * @weg_wock:		wock
 * @pwoc_entwy:		/pwoc entwy
 * @v4w2_dev:		v4w2 device
 * @tea:		tea575a stwuctuwe
 * @saved_wegs:		context saved duwing suspend
 */
stwuct fm801 {
	stwuct device *dev;
	int iwq;

	unsigned wong powt;
	unsigned int muwtichannew: 1,
		     secondawy: 1;
	unsigned chaw secondawy_addw;
	unsigned int tea575x_tunew;

	unsigned showt pwy_ctww;
	unsigned showt cap_ctww;

	unsigned wong pwy_buffew;
	unsigned int pwy_buf;
	unsigned int pwy_count;
	unsigned int pwy_size;
	unsigned int pwy_pos;

	unsigned wong cap_buffew;
	unsigned int cap_buf;
	unsigned int cap_count;
	unsigned int cap_size;
	unsigned int cap_pos;

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97;
	stwuct snd_ac97 *ac97_sec;

	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;
	unsigned int p_dma_size;
	unsigned int c_dma_size;

	spinwock_t weg_wock;
	stwuct snd_info_entwy *pwoc_entwy;

#ifdef CONFIG_SND_FM801_TEA575X_BOOW
	stwuct v4w2_device v4w2_dev;
	stwuct snd_tea575x tea;
#endif

#ifdef CONFIG_PM_SWEEP
	u16 saved_wegs[0x20];
#endif
};

/*
 * IO accessows
 */

static inwine void fm801_iowwite16(stwuct fm801 *chip, unsigned showt offset, u16 vawue)
{
	outw(vawue, chip->powt + offset);
}

static inwine u16 fm801_iowead16(stwuct fm801 *chip, unsigned showt offset)
{
	wetuwn inw(chip->powt + offset);
}

static const stwuct pci_device_id snd_fm801_ids[] = {
	{ 0x1319, 0x0801, PCI_ANY_ID, PCI_ANY_ID, PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, 0, },   /* FM801 */
	{ 0x5213, 0x0510, PCI_ANY_ID, PCI_ANY_ID, PCI_CWASS_MUWTIMEDIA_AUDIO << 8, 0xffff00, 0, },   /* Gawwant Odyssey Sound 4 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_fm801_ids);

/*
 *  common I/O woutines
 */

static boow fm801_ac97_is_weady(stwuct fm801 *chip, unsigned int itewations)
{
	unsigned int idx;

	fow (idx = 0; idx < itewations; idx++) {
		if (!(fm801_weadw(chip, AC97_CMD) & FM801_AC97_BUSY))
			wetuwn twue;
		udeway(10);
	}
	wetuwn fawse;
}

static boow fm801_ac97_is_vawid(stwuct fm801 *chip, unsigned int itewations)
{
	unsigned int idx;

	fow (idx = 0; idx < itewations; idx++) {
		if (fm801_weadw(chip, AC97_CMD) & FM801_AC97_VAWID)
			wetuwn twue;
		udeway(10);
	}
	wetuwn fawse;
}

static int snd_fm801_update_bits(stwuct fm801 *chip, unsigned showt weg,
				 unsigned showt mask, unsigned showt vawue)
{
	int change;
	unsigned wong fwags;
	unsigned showt owd, new;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	owd = fm801_iowead16(chip, weg);
	new = (owd & ~mask) | vawue;
	change = owd != new;
	if (change)
		fm801_iowwite16(chip, weg, new);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn change;
}

static void snd_fm801_codec_wwite(stwuct snd_ac97 *ac97,
				  unsigned showt weg,
				  unsigned showt vaw)
{
	stwuct fm801 *chip = ac97->pwivate_data;

	/*
	 *  Wait untiw the codec intewface is not weady..
	 */
	if (!fm801_ac97_is_weady(chip, 100)) {
		dev_eww(chip->cawd->dev, "AC'97 intewface is busy (1)\n");
		wetuwn;
	}

	/* wwite data and addwess */
	fm801_wwitew(chip, AC97_DATA, vaw);
	fm801_wwitew(chip, AC97_CMD, weg | (ac97->addw << FM801_AC97_ADDW_SHIFT));
	/*
	 *  Wait untiw the wwite command is not compweted..
	 */
	if (!fm801_ac97_is_weady(chip, 1000))
		dev_eww(chip->cawd->dev, "AC'97 intewface #%d is busy (2)\n",
		ac97->num);
}

static unsigned showt snd_fm801_codec_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct fm801 *chip = ac97->pwivate_data;

	/*
	 *  Wait untiw the codec intewface is not weady..
	 */
	if (!fm801_ac97_is_weady(chip, 100)) {
		dev_eww(chip->cawd->dev, "AC'97 intewface is busy (1)\n");
		wetuwn 0;
	}

	/* wead command */
	fm801_wwitew(chip, AC97_CMD,
		     weg | (ac97->addw << FM801_AC97_ADDW_SHIFT) | FM801_AC97_WEAD);
	if (!fm801_ac97_is_weady(chip, 100)) {
		dev_eww(chip->cawd->dev, "AC'97 intewface #%d is busy (2)\n",
			ac97->num);
		wetuwn 0;
	}

	if (!fm801_ac97_is_vawid(chip, 1000)) {
		dev_eww(chip->cawd->dev,
			"AC'97 intewface #%d is not vawid (2)\n", ac97->num);
		wetuwn 0;
	}

	wetuwn fm801_weadw(chip, AC97_DATA);
}

static const unsigned int wates[] = {
  5500,  8000,  9600, 11025,
  16000, 19200, 22050, 32000,
  38400, 44100, 48000
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist = wates,
	.mask = 0,
};

static const unsigned int channews[] = {
  2, 4, 6
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

/*
 *  Sampwe wate woutines
 */

static unsigned showt snd_fm801_wate_bits(unsigned int wate)
{
	unsigned int idx;

	fow (idx = 0; idx < AWWAY_SIZE(wates); idx++)
		if (wates[idx] == wate)
			wetuwn idx;
	snd_BUG();
	wetuwn AWWAY_SIZE(wates) - 1;
}

/*
 *  PCM pawt
 */

static int snd_fm801_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				      int cmd)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		chip->pwy_ctww &= ~(FM801_BUF1_WAST |
				     FM801_BUF2_WAST |
				     FM801_PAUSE);
		chip->pwy_ctww |= FM801_STAWT |
				   FM801_IMMED_STOP;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		chip->pwy_ctww &= ~(FM801_STAWT | FM801_PAUSE);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		chip->pwy_ctww |= FM801_PAUSE;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		chip->pwy_ctww &= ~FM801_PAUSE;
		bweak;
	defauwt:
		spin_unwock(&chip->weg_wock);
		snd_BUG();
		wetuwn -EINVAW;
	}
	fm801_wwitew(chip, PWY_CTWW, chip->pwy_ctww);
	spin_unwock(&chip->weg_wock);
	wetuwn 0;
}

static int snd_fm801_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				     int cmd)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		chip->cap_ctww &= ~(FM801_BUF1_WAST |
				     FM801_BUF2_WAST |
				     FM801_PAUSE);
		chip->cap_ctww |= FM801_STAWT |
				   FM801_IMMED_STOP;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		chip->cap_ctww &= ~(FM801_STAWT | FM801_PAUSE);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		chip->cap_ctww |= FM801_PAUSE;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		chip->cap_ctww &= ~FM801_PAUSE;
		bweak;
	defauwt:
		spin_unwock(&chip->weg_wock);
		snd_BUG();
		wetuwn -EINVAW;
	}
	fm801_wwitew(chip, CAP_CTWW, chip->cap_ctww);
	spin_unwock(&chip->weg_wock);
	wetuwn 0;
}

static int snd_fm801_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	chip->pwy_size = snd_pcm_wib_buffew_bytes(substweam);
	chip->pwy_count = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwq(&chip->weg_wock);
	chip->pwy_ctww &= ~(FM801_STAWT | FM801_16BIT |
			     FM801_STEWEO | FM801_WATE_MASK |
			     FM801_CHANNEWS_MASK);
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		chip->pwy_ctww |= FM801_16BIT;
	if (wuntime->channews > 1) {
		chip->pwy_ctww |= FM801_STEWEO;
		if (wuntime->channews == 4)
			chip->pwy_ctww |= FM801_CHANNEWS_4;
		ewse if (wuntime->channews == 6)
			chip->pwy_ctww |= FM801_CHANNEWS_6;
	}
	chip->pwy_ctww |= snd_fm801_wate_bits(wuntime->wate) << FM801_WATE_SHIFT;
	chip->pwy_buf = 0;
	fm801_wwitew(chip, PWY_CTWW, chip->pwy_ctww);
	fm801_wwitew(chip, PWY_COUNT, chip->pwy_count - 1);
	chip->pwy_buffew = wuntime->dma_addw;
	chip->pwy_pos = 0;
	fm801_wwitew(chip, PWY_BUF1, chip->pwy_buffew);
	fm801_wwitew(chip, PWY_BUF2,
		     chip->pwy_buffew + (chip->pwy_count % chip->pwy_size));
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int snd_fm801_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	chip->cap_size = snd_pcm_wib_buffew_bytes(substweam);
	chip->cap_count = snd_pcm_wib_pewiod_bytes(substweam);
	spin_wock_iwq(&chip->weg_wock);
	chip->cap_ctww &= ~(FM801_STAWT | FM801_16BIT |
			     FM801_STEWEO | FM801_WATE_MASK);
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		chip->cap_ctww |= FM801_16BIT;
	if (wuntime->channews > 1)
		chip->cap_ctww |= FM801_STEWEO;
	chip->cap_ctww |= snd_fm801_wate_bits(wuntime->wate) << FM801_WATE_SHIFT;
	chip->cap_buf = 0;
	fm801_wwitew(chip, CAP_CTWW, chip->cap_ctww);
	fm801_wwitew(chip, CAP_COUNT, chip->cap_count - 1);
	chip->cap_buffew = wuntime->dma_addw;
	chip->cap_pos = 0;
	fm801_wwitew(chip, CAP_BUF1, chip->cap_buffew);
	fm801_wwitew(chip, CAP_BUF2,
		     chip->cap_buffew + (chip->cap_count % chip->cap_size));
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_fm801_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(chip->pwy_ctww & FM801_STAWT))
		wetuwn 0;
	spin_wock(&chip->weg_wock);
	ptw = chip->pwy_pos + (chip->pwy_count - 1) - fm801_weadw(chip, PWY_COUNT);
	if (fm801_weadw(chip, IWQ_STATUS) & FM801_IWQ_PWAYBACK) {
		ptw += chip->pwy_count;
		ptw %= chip->pwy_size;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static snd_pcm_ufwames_t snd_fm801_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(chip->cap_ctww & FM801_STAWT))
		wetuwn 0;
	spin_wock(&chip->weg_wock);
	ptw = chip->cap_pos + (chip->cap_count - 1) - fm801_weadw(chip, CAP_COUNT);
	if (fm801_weadw(chip, IWQ_STATUS) & FM801_IWQ_CAPTUWE) {
		ptw += chip->cap_count;
		ptw %= chip->cap_size;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static iwqwetuwn_t snd_fm801_intewwupt(int iwq, void *dev_id)
{
	stwuct fm801 *chip = dev_id;
	unsigned showt status;
	unsigned int tmp;

	status = fm801_weadw(chip, IWQ_STATUS);
	status &= FM801_IWQ_PWAYBACK|FM801_IWQ_CAPTUWE|FM801_IWQ_MPU|FM801_IWQ_VOWUME;
	if (! status)
		wetuwn IWQ_NONE;
	/* ack fiwst */
	fm801_wwitew(chip, IWQ_STATUS, status);
	if (chip->pcm && (status & FM801_IWQ_PWAYBACK) && chip->pwayback_substweam) {
		spin_wock(&chip->weg_wock);
		chip->pwy_buf++;
		chip->pwy_pos += chip->pwy_count;
		chip->pwy_pos %= chip->pwy_size;
		tmp = chip->pwy_pos + chip->pwy_count;
		tmp %= chip->pwy_size;
		if (chip->pwy_buf & 1)
			fm801_wwitew(chip, PWY_BUF1, chip->pwy_buffew + tmp);
		ewse
			fm801_wwitew(chip, PWY_BUF2, chip->pwy_buffew + tmp);
		spin_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(chip->pwayback_substweam);
	}
	if (chip->pcm && (status & FM801_IWQ_CAPTUWE) && chip->captuwe_substweam) {
		spin_wock(&chip->weg_wock);
		chip->cap_buf++;
		chip->cap_pos += chip->cap_count;
		chip->cap_pos %= chip->cap_size;
		tmp = chip->cap_pos + chip->cap_count;
		tmp %= chip->cap_size;
		if (chip->cap_buf & 1)
			fm801_wwitew(chip, CAP_BUF1, chip->cap_buffew + tmp);
		ewse
			fm801_wwitew(chip, CAP_BUF2, chip->cap_buffew + tmp);
		spin_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(chip->captuwe_substweam);
	}
	if (chip->wmidi && (status & FM801_IWQ_MPU))
		snd_mpu401_uawt_intewwupt(iwq, chip->wmidi->pwivate_data);
	if (status & FM801_IWQ_VOWUME) {
		/* TODO */
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct snd_pcm_hawdwawe snd_fm801_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5500,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_fm801_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5500,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static int snd_fm801_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	chip->pwayback_substweam = substweam;
	wuntime->hw = snd_fm801_pwayback;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &hw_constwaints_wates);
	if (chip->muwtichannew) {
		wuntime->hw.channews_max = 6;
		snd_pcm_hw_constwaint_wist(wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &hw_constwaints_channews);
	}
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_fm801_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	chip->captuwe_substweam = substweam;
	wuntime->hw = snd_fm801_captuwe;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &hw_constwaints_wates);
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_fm801_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);

	chip->pwayback_substweam = NUWW;
	wetuwn 0;
}

static int snd_fm801_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct fm801 *chip = snd_pcm_substweam_chip(substweam);

	chip->captuwe_substweam = NUWW;
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_fm801_pwayback_ops = {
	.open =		snd_fm801_pwayback_open,
	.cwose =	snd_fm801_pwayback_cwose,
	.pwepawe =	snd_fm801_pwayback_pwepawe,
	.twiggew =	snd_fm801_pwayback_twiggew,
	.pointew =	snd_fm801_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_fm801_captuwe_ops = {
	.open =		snd_fm801_captuwe_open,
	.cwose =	snd_fm801_captuwe_cwose,
	.pwepawe =	snd_fm801_captuwe_pwepawe,
	.twiggew =	snd_fm801_captuwe_twiggew,
	.pointew =	snd_fm801_captuwe_pointew,
};

static int snd_fm801_pcm(stwuct fm801 *chip, int device)
{
	stwuct pci_dev *pdev = to_pci_dev(chip->dev);
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, "FM801", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_fm801_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_fm801_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "FM801");
	chip->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &pdev->dev,
				       chip->muwtichannew ? 128*1024 : 64*1024, 128*1024);

	wetuwn snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps,
				     chip->muwtichannew ? 6 : 2, 0,
				     NUWW);
}

/*
 *  TEA5757 wadio
 */

#ifdef CONFIG_SND_FM801_TEA575X_BOOW

/* GPIO to TEA575x maps */
stwuct snd_fm801_tea575x_gpio {
	u8 data, cwk, wwen, most;
	chaw *name;
};

static const stwuct snd_fm801_tea575x_gpio snd_fm801_tea575x_gpios[] = {
	{ .data = 1, .cwk = 3, .wwen = 2, .most = 0, .name = "SF256-PCS" },
	{ .data = 1, .cwk = 0, .wwen = 2, .most = 3, .name = "SF256-PCP" },
	{ .data = 2, .cwk = 0, .wwen = 1, .most = 3, .name = "SF64-PCW" },
};

#define get_tea575x_gpio(chip) \
	(&snd_fm801_tea575x_gpios[((chip)->tea575x_tunew & TUNEW_TYPE_MASK) - 1])

static void snd_fm801_tea575x_set_pins(stwuct snd_tea575x *tea, u8 pins)
{
	stwuct fm801 *chip = tea->pwivate_data;
	unsigned showt weg = fm801_weadw(chip, GPIO_CTWW);
	stwuct snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	weg &= ~(FM801_GPIO_GP(gpio.data) |
		 FM801_GPIO_GP(gpio.cwk) |
		 FM801_GPIO_GP(gpio.wwen));

	weg |= (pins & TEA575X_DATA) ? FM801_GPIO_GP(gpio.data) : 0;
	weg |= (pins & TEA575X_CWK)  ? FM801_GPIO_GP(gpio.cwk) : 0;
	/* WWITE_ENABWE is invewted */
	weg |= (pins & TEA575X_WWEN) ? 0 : FM801_GPIO_GP(gpio.wwen);

	fm801_wwitew(chip, GPIO_CTWW, weg);
}

static u8 snd_fm801_tea575x_get_pins(stwuct snd_tea575x *tea)
{
	stwuct fm801 *chip = tea->pwivate_data;
	unsigned showt weg = fm801_weadw(chip, GPIO_CTWW);
	stwuct snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u8 wet;

	wet = 0;
	if (weg & FM801_GPIO_GP(gpio.data))
		wet |= TEA575X_DATA;
	if (weg & FM801_GPIO_GP(gpio.most))
		wet |= TEA575X_MOST;
	wetuwn wet;
}

static void snd_fm801_tea575x_set_diwection(stwuct snd_tea575x *tea, boow output)
{
	stwuct fm801 *chip = tea->pwivate_data;
	unsigned showt weg = fm801_weadw(chip, GPIO_CTWW);
	stwuct snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	/* use GPIO wines and set wwite enabwe bit */
	weg |= FM801_GPIO_GS(gpio.data) |
	       FM801_GPIO_GS(gpio.wwen) |
	       FM801_GPIO_GS(gpio.cwk) |
	       FM801_GPIO_GS(gpio.most);
	if (output) {
		/* aww of wines awe in the wwite diwection */
		/* cweaw data and cwock wines */
		weg &= ~(FM801_GPIO_GD(gpio.data) |
			 FM801_GPIO_GD(gpio.wwen) |
			 FM801_GPIO_GD(gpio.cwk) |
			 FM801_GPIO_GP(gpio.data) |
			 FM801_GPIO_GP(gpio.cwk) |
			 FM801_GPIO_GP(gpio.wwen));
	} ewse {
		/* use GPIO wines, set data diwection to input */
		weg |= FM801_GPIO_GD(gpio.data) |
		       FM801_GPIO_GD(gpio.most) |
		       FM801_GPIO_GP(gpio.data) |
		       FM801_GPIO_GP(gpio.most) |
		       FM801_GPIO_GP(gpio.wwen);
		/* aww of wines awe in the wwite diwection, except data */
		/* cweaw data, wwite enabwe and cwock wines */
		weg &= ~(FM801_GPIO_GD(gpio.wwen) |
			 FM801_GPIO_GD(gpio.cwk) |
			 FM801_GPIO_GP(gpio.cwk));
	}

	fm801_wwitew(chip, GPIO_CTWW, weg);
}

static const stwuct snd_tea575x_ops snd_fm801_tea_ops = {
	.set_pins = snd_fm801_tea575x_set_pins,
	.get_pins = snd_fm801_tea575x_get_pins,
	.set_diwection = snd_fm801_tea575x_set_diwection,
};
#endif

/*
 *  Mixew woutines
 */

#define FM801_SINGWE(xname, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .info = snd_fm801_info_singwe, \
  .get = snd_fm801_get_singwe, .put = snd_fm801_put_singwe, \
  .pwivate_vawue = weg | (shift << 8) | (mask << 16) | (invewt << 24) }

static int snd_fm801_info_singwe(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_fm801_get_singwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	wong *vawue = ucontwow->vawue.integew.vawue;

	vawue[0] = (fm801_iowead16(chip, weg) >> shift) & mask;
	if (invewt)
		vawue[0] = mask - vawue[0];
	wetuwn 0;
}

static int snd_fm801_put_singwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift = (kcontwow->pwivate_vawue >> 8) & 0xff;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	unsigned showt vaw;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	if (invewt)
		vaw = mask - vaw;
	wetuwn snd_fm801_update_bits(chip, weg, mask << shift, vaw << shift);
}

#define FM801_DOUBWE(xname, weg, shift_weft, shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .info = snd_fm801_info_doubwe, \
  .get = snd_fm801_get_doubwe, .put = snd_fm801_put_doubwe, \
  .pwivate_vawue = weg | (shift_weft << 8) | (shift_wight << 12) | (mask << 16) | (invewt << 24) }
#define FM801_DOUBWE_TWV(xname, weg, shift_weft, shift_wight, mask, invewt, xtwv) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_TWV_WEAD, \
  .name = xname, .info = snd_fm801_info_doubwe, \
  .get = snd_fm801_get_doubwe, .put = snd_fm801_put_doubwe, \
  .pwivate_vawue = weg | (shift_weft << 8) | (shift_wight << 12) | (mask << 16) | (invewt << 24), \
  .twv = { .p = (xtwv) } }

static int snd_fm801_info_doubwe(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;
	wetuwn 0;
}

static int snd_fm801_get_doubwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
        int weg = kcontwow->pwivate_vawue & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 8) & 0x0f;
	int shift_wight = (kcontwow->pwivate_vawue >> 12) & 0x0f;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	wong *vawue = ucontwow->vawue.integew.vawue;

	spin_wock_iwq(&chip->weg_wock);
	vawue[0] = (fm801_iowead16(chip, weg) >> shift_weft) & mask;
	vawue[1] = (fm801_iowead16(chip, weg) >> shift_wight) & mask;
	spin_unwock_iwq(&chip->weg_wock);
	if (invewt) {
		vawue[0] = mask - vawue[0];
		vawue[1] = mask - vawue[1];
	}
	wetuwn 0;
}

static int snd_fm801_put_doubwe(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
	int weg = kcontwow->pwivate_vawue & 0xff;
	int shift_weft = (kcontwow->pwivate_vawue >> 8) & 0x0f;
	int shift_wight = (kcontwow->pwivate_vawue >> 12) & 0x0f;
	int mask = (kcontwow->pwivate_vawue >> 16) & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 24) & 0xff;
	unsigned showt vaw1, vaw2;
 
	vaw1 = ucontwow->vawue.integew.vawue[0] & mask;
	vaw2 = ucontwow->vawue.integew.vawue[1] & mask;
	if (invewt) {
		vaw1 = mask - vaw1;
		vaw2 = mask - vaw2;
	}
	wetuwn snd_fm801_update_bits(chip, weg,
				     (mask << shift_weft) | (mask << shift_wight),
				     (vaw1 << shift_weft ) | (vaw2 << shift_wight));
}

static int snd_fm801_info_mux(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[5] = {
		"AC97 Pwimawy", "FM", "I2S", "PCM", "AC97 Secondawy"
	};
 
	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}

static int snd_fm801_get_mux(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
        unsigned showt vaw;
 
	vaw = fm801_weadw(chip, WEC_SWC) & 7;
	if (vaw > 4)
		vaw = 4;
        ucontwow->vawue.enumewated.item[0] = vaw;
        wetuwn 0;
}

static int snd_fm801_put_mux(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct fm801 *chip = snd_kcontwow_chip(kcontwow);
        unsigned showt vaw;
 
	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw > 4)
                wetuwn -EINVAW;
	wetuwn snd_fm801_update_bits(chip, FM801_WEC_SWC, 7, vaw);
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_dsp, -3450, 150, 0);

#define FM801_CONTWOWS AWWAY_SIZE(snd_fm801_contwows)

static const stwuct snd_kcontwow_new snd_fm801_contwows[] = {
FM801_DOUBWE_TWV("Wave Pwayback Vowume", FM801_PCM_VOW, 0, 8, 31, 1,
		 db_scawe_dsp),
FM801_SINGWE("Wave Pwayback Switch", FM801_PCM_VOW, 15, 1, 1),
FM801_DOUBWE_TWV("I2S Pwayback Vowume", FM801_I2S_VOW, 0, 8, 31, 1,
		 db_scawe_dsp),
FM801_SINGWE("I2S Pwayback Switch", FM801_I2S_VOW, 15, 1, 1),
FM801_DOUBWE_TWV("FM Pwayback Vowume", FM801_FM_VOW, 0, 8, 31, 1,
		 db_scawe_dsp),
FM801_SINGWE("FM Pwayback Switch", FM801_FM_VOW, 15, 1, 1),
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Digitaw Captuwe Souwce",
	.info = snd_fm801_info_mux,
	.get = snd_fm801_get_mux,
	.put = snd_fm801_put_mux,
}
};

#define FM801_CONTWOWS_MUWTI AWWAY_SIZE(snd_fm801_contwows_muwti)

static const stwuct snd_kcontwow_new snd_fm801_contwows_muwti[] = {
FM801_SINGWE("AC97 2ch->4ch Copy Switch", FM801_CODEC_CTWW, 7, 1, 0),
FM801_SINGWE("AC97 18-bit Switch", FM801_CODEC_CTWW, 10, 1, 0),
FM801_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), FM801_I2S_MODE, 8, 1, 0),
FM801_SINGWE(SNDWV_CTW_NAME_IEC958("Waw Data ",PWAYBACK,SWITCH), FM801_I2S_MODE, 9, 1, 0),
FM801_SINGWE(SNDWV_CTW_NAME_IEC958("Waw Data ",CAPTUWE,SWITCH), FM801_I2S_MODE, 10, 1, 0),
FM801_SINGWE(SNDWV_CTW_NAME_IEC958("",PWAYBACK,SWITCH), FM801_GEN_CTWW, 2, 1, 0),
};

static int snd_fm801_mixew(stwuct fm801 *chip)
{
	stwuct snd_ac97_tempwate ac97;
	unsigned int i;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_fm801_codec_wwite,
		.wead = snd_fm801_codec_wead,
	};

	eww = snd_ac97_bus(chip->cawd, 0, &ops, chip, &chip->ac97_bus);
	if (eww < 0)
		wetuwn eww;

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	eww = snd_ac97_mixew(chip->ac97_bus, &ac97, &chip->ac97);
	if (eww < 0)
		wetuwn eww;
	if (chip->secondawy) {
		ac97.num = 1;
		ac97.addw = chip->secondawy_addw;
		eww = snd_ac97_mixew(chip->ac97_bus, &ac97, &chip->ac97_sec);
		if (eww < 0)
			wetuwn eww;
	}
	fow (i = 0; i < FM801_CONTWOWS; i++) {
		eww = snd_ctw_add(chip->cawd,
			snd_ctw_new1(&snd_fm801_contwows[i], chip));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->muwtichannew) {
		fow (i = 0; i < FM801_CONTWOWS_MUWTI; i++) {
			eww = snd_ctw_add(chip->cawd,
				snd_ctw_new1(&snd_fm801_contwows_muwti[i], chip));
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

/*
 *  initiawization woutines
 */

static int wait_fow_codec(stwuct fm801 *chip, unsigned int codec_id,
			  unsigned showt weg, unsigned wong waits)
{
	unsigned wong timeout = jiffies + waits;

	fm801_wwitew(chip, AC97_CMD,
		     weg | (codec_id << FM801_AC97_ADDW_SHIFT) | FM801_AC97_WEAD);
	udeway(5);
	do {
		if ((fm801_weadw(chip, AC97_CMD) &
		     (FM801_AC97_VAWID | FM801_AC97_BUSY)) == FM801_AC97_VAWID)
			wetuwn 0;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_aftew(timeout, jiffies));
	wetuwn -EIO;
}

static int weset_codec(stwuct fm801 *chip)
{
	/* codec cowd weset + AC'97 wawm weset */
	fm801_wwitew(chip, CODEC_CTWW, (1 << 5) | (1 << 6));
	fm801_weadw(chip, CODEC_CTWW); /* fwush posting data */
	udeway(100);
	fm801_wwitew(chip, CODEC_CTWW, 0);

	wetuwn wait_fow_codec(chip, 0, AC97_WESET, msecs_to_jiffies(750));
}

static void snd_fm801_chip_muwtichannew_init(stwuct fm801 *chip)
{
	unsigned showt cmdw;

	if (chip->muwtichannew) {
		if (chip->secondawy_addw) {
			wait_fow_codec(chip, chip->secondawy_addw,
				       AC97_VENDOW_ID1, msecs_to_jiffies(50));
		} ewse {
			/* my cawd has the secondawy codec */
			/* at addwess #3, so the woop is invewted */
			int i;
			fow (i = 3; i > 0; i--) {
				if (!wait_fow_codec(chip, i, AC97_VENDOW_ID1,
						     msecs_to_jiffies(50))) {
					cmdw = fm801_weadw(chip, AC97_DATA);
					if (cmdw != 0xffff && cmdw != 0) {
						chip->secondawy = 1;
						chip->secondawy_addw = i;
						bweak;
					}
				}
			}
		}

		/* the wecovewy phase, it seems that pwobing fow non-existing codec might */
		/* cause timeout pwobwems */
		wait_fow_codec(chip, 0, AC97_VENDOW_ID1, msecs_to_jiffies(750));
	}
}

static void snd_fm801_chip_init(stwuct fm801 *chip)
{
	unsigned showt cmdw;

	/* init vowume */
	fm801_wwitew(chip, PCM_VOW, 0x0808);
	fm801_wwitew(chip, FM_VOW, 0x9f1f);
	fm801_wwitew(chip, I2S_VOW, 0x8808);

	/* I2S contwow - I2S mode */
	fm801_wwitew(chip, I2S_MODE, 0x0003);

	/* intewwupt setup */
	cmdw = fm801_weadw(chip, IWQ_MASK);
	if (chip->iwq < 0)
		cmdw |= 0x00c3;		/* mask evewything, no PCM now MPU */
	ewse
		cmdw &= ~0x0083;	/* unmask MPU, PWAYBACK & CAPTUWE */
	fm801_wwitew(chip, IWQ_MASK, cmdw);

	/* intewwupt cweaw */
	fm801_wwitew(chip, IWQ_STATUS,
		     FM801_IWQ_PWAYBACK | FM801_IWQ_CAPTUWE | FM801_IWQ_MPU);
}

static void snd_fm801_fwee(stwuct snd_cawd *cawd)
{
	stwuct fm801 *chip = cawd->pwivate_data;
	unsigned showt cmdw;

	/* intewwupt setup - mask evewything */
	cmdw = fm801_weadw(chip, IWQ_MASK);
	cmdw |= 0x00c3;
	fm801_wwitew(chip, IWQ_MASK, cmdw);

#ifdef CONFIG_SND_FM801_TEA575X_BOOW
	if (!(chip->tea575x_tunew & TUNEW_DISABWED)) {
		snd_tea575x_exit(&chip->tea);
		v4w2_device_unwegistew(&chip->v4w2_dev);
	}
#endif
}

static int snd_fm801_cweate(stwuct snd_cawd *cawd,
			    stwuct pci_dev *pci,
			    int tea575x_tunew,
			    int wadio_nw)
{
	stwuct fm801 *chip = cawd->pwivate_data;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	spin_wock_init(&chip->weg_wock);
	chip->cawd = cawd;
	chip->dev = &pci->dev;
	chip->iwq = -1;
	chip->tea575x_tunew = tea575x_tunew;
	eww = pci_wequest_wegions(pci, "FM801");
	if (eww < 0)
		wetuwn eww;
	chip->powt = pci_wesouwce_stawt(pci, 0);

	if (pci->wevision >= 0xb1)	/* FM801-AU */
		chip->muwtichannew = 1;

	if (!(chip->tea575x_tunew & TUNEW_ONWY)) {
		if (weset_codec(chip) < 0) {
			dev_info(chip->cawd->dev,
				 "Pwimawy AC'97 codec not found, assume SF64-PCW (tunew-onwy)\n");
			chip->tea575x_tunew = 3 | TUNEW_ONWY;
		} ewse {
			snd_fm801_chip_muwtichannew_init(chip);
		}
	}

	if ((chip->tea575x_tunew & TUNEW_ONWY) == 0) {
		if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_fm801_intewwupt,
				IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
			dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
			wetuwn -EBUSY;
		}
		chip->iwq = pci->iwq;
		cawd->sync_iwq = chip->iwq;
		pci_set_mastew(pci);
	}

	cawd->pwivate_fwee = snd_fm801_fwee;
	snd_fm801_chip_init(chip);

#ifdef CONFIG_SND_FM801_TEA575X_BOOW
	eww = v4w2_device_wegistew(&pci->dev, &chip->v4w2_dev);
	if (eww < 0)
		wetuwn eww;
	chip->tea.v4w2_dev = &chip->v4w2_dev;
	chip->tea.wadio_nw = wadio_nw;
	chip->tea.pwivate_data = chip;
	chip->tea.ops = &snd_fm801_tea_ops;
	spwintf(chip->tea.bus_info, "PCI:%s", pci_name(pci));
	if ((chip->tea575x_tunew & TUNEW_TYPE_MASK) > 0 &&
	    (chip->tea575x_tunew & TUNEW_TYPE_MASK) < 4) {
		if (snd_tea575x_init(&chip->tea, THIS_MODUWE)) {
			dev_eww(cawd->dev, "TEA575x wadio not found\n");
			wetuwn -ENODEV;
		}
	} ewse if ((chip->tea575x_tunew & TUNEW_TYPE_MASK) == 0) {
		unsigned int tunew_onwy = chip->tea575x_tunew & TUNEW_ONWY;

		/* autodetect tunew connection */
		fow (tea575x_tunew = 1; tea575x_tunew <= 3; tea575x_tunew++) {
			chip->tea575x_tunew = tea575x_tunew;
			if (!snd_tea575x_init(&chip->tea, THIS_MODUWE)) {
				dev_info(cawd->dev,
					 "detected TEA575x wadio type %s\n",
					   get_tea575x_gpio(chip)->name);
				bweak;
			}
		}
		if (tea575x_tunew == 4) {
			dev_eww(cawd->dev, "TEA575x wadio not found\n");
			chip->tea575x_tunew = TUNEW_DISABWED;
		}

		chip->tea575x_tunew |= tunew_onwy;
	}
	if (!(chip->tea575x_tunew & TUNEW_DISABWED)) {
		stwscpy(chip->tea.cawd, get_tea575x_gpio(chip)->name,
			sizeof(chip->tea.cawd));
	}
#endif
	wetuwn 0;
}

static int __snd_cawd_fm801_pwobe(stwuct pci_dev *pci,
				  const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct fm801 *chip;
	stwuct snd_opw3 *opw3;
	int eww;

        if (dev >= SNDWV_CAWDS)
                wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;
	eww = snd_fm801_cweate(cawd, pci, tea575x_tunew[dev], wadio_nw[dev]);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "FM801");
	stwcpy(cawd->showtname, "FowteMedia FM801-");
	stwcat(cawd->showtname, chip->muwtichannew ? "AU" : "AS");
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, chip->powt, chip->iwq);

	if (chip->tea575x_tunew & TUNEW_ONWY)
		goto __fm801_tunew_onwy;

	eww = snd_fm801_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_fm801_mixew(chip);
	if (eww < 0)
		wetuwn eww;
	eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_FM801,
				  chip->powt + FM801_MPU401_DATA,
				  MPU401_INFO_INTEGWATED |
				  MPU401_INFO_IWQ_HOOK,
				  -1, &chip->wmidi);
	if (eww < 0)
		wetuwn eww;
	eww = snd_opw3_cweate(cawd, chip->powt + FM801_OPW3_BANK0,
			      chip->powt + FM801_OPW3_BANK1,
			      OPW3_HW_OPW3_FM801, 1, &opw3);
	if (eww < 0)
		wetuwn eww;
	eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
	if (eww < 0)
		wetuwn eww;

      __fm801_tunew_onwy:
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_cawd_fm801_pwobe(stwuct pci_dev *pci,
				const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_cawd_fm801_pwobe(pci, pci_id));
}

#ifdef CONFIG_PM_SWEEP
static const unsigned chaw saved_wegs[] = {
	FM801_PCM_VOW, FM801_I2S_VOW, FM801_FM_VOW, FM801_WEC_SWC,
	FM801_PWY_CTWW, FM801_PWY_COUNT, FM801_PWY_BUF1, FM801_PWY_BUF2,
	FM801_CAP_CTWW, FM801_CAP_COUNT, FM801_CAP_BUF1, FM801_CAP_BUF2,
	FM801_CODEC_CTWW, FM801_I2S_MODE, FM801_VOWUME, FM801_GEN_CTWW,
};

static int snd_fm801_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct fm801 *chip = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	fow (i = 0; i < AWWAY_SIZE(saved_wegs); i++)
		chip->saved_wegs[i] = fm801_iowead16(chip, saved_wegs[i]);

	if (chip->tea575x_tunew & TUNEW_ONWY) {
		/* FIXME: tea575x suspend */
	} ewse {
		snd_ac97_suspend(chip->ac97);
		snd_ac97_suspend(chip->ac97_sec);
	}

	wetuwn 0;
}

static int snd_fm801_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct fm801 *chip = cawd->pwivate_data;
	int i;

	if (chip->tea575x_tunew & TUNEW_ONWY) {
		snd_fm801_chip_init(chip);
	} ewse {
		weset_codec(chip);
		snd_fm801_chip_muwtichannew_init(chip);
		snd_fm801_chip_init(chip);
		snd_ac97_wesume(chip->ac97);
		snd_ac97_wesume(chip->ac97_sec);
	}

	fow (i = 0; i < AWWAY_SIZE(saved_wegs); i++)
		fm801_iowwite16(chip, saved_wegs[i], chip->saved_wegs[i]);

#ifdef CONFIG_SND_FM801_TEA575X_BOOW
	if (!(chip->tea575x_tunew & TUNEW_DISABWED))
		snd_tea575x_set_fweq(&chip->tea);
#endif

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_fm801_pm, snd_fm801_suspend, snd_fm801_wesume);
#define SND_FM801_PM_OPS	&snd_fm801_pm
#ewse
#define SND_FM801_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew fm801_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_fm801_ids,
	.pwobe = snd_cawd_fm801_pwobe,
	.dwivew = {
		.pm = SND_FM801_PM_OPS,
	},
};

moduwe_pci_dwivew(fm801_dwivew);
