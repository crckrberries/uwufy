// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA modem dwivew fow Intew ICH (i8x0) chipsets
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *
 *   This is modified (by Sasha Khapyowsky <sashak@awsa-pwoject.owg>) vewsion
 *   of AWSA ICH sound dwivew intew8x0.c .
 */      

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Intew 82801AA,82901AB,i810,i820,i830,i840,i845,MX440; "
		   "SiS 7013; NVidia MCP/2/2S/3 modems");
MODUWE_WICENSE("GPW");

static int index = -2; /* Excwude the fiwst cawd */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static int ac97_cwock;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Intew i8x0 modemcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Intew i8x0 modemcawd.");
moduwe_pawam(ac97_cwock, int, 0444);
MODUWE_PAWM_DESC(ac97_cwock, "AC'97 codec cwock (0 = auto-detect).");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);

/*
 *  Diwect wegistews
 */
enum { DEVICE_INTEW, DEVICE_SIS, DEVICE_AWI, DEVICE_NFOWCE };

#define ICHWEG(x) ICH_WEG_##x

#define DEFINE_WEGSET(name,base) \
enum { \
	ICH_WEG_##name##_BDBAW	= base + 0x0,	/* dwowd - buffew descwiptow wist base addwess */ \
	ICH_WEG_##name##_CIV	= base + 0x04,	/* byte - cuwwent index vawue */ \
	ICH_WEG_##name##_WVI	= base + 0x05,	/* byte - wast vawid index */ \
	ICH_WEG_##name##_SW	= base + 0x06,	/* byte - status wegistew */ \
	ICH_WEG_##name##_PICB	= base + 0x08,	/* wowd - position in cuwwent buffew */ \
	ICH_WEG_##name##_PIV	= base + 0x0a,	/* byte - pwefetched index vawue */ \
	ICH_WEG_##name##_CW	= base + 0x0b,	/* byte - contwow wegistew */ \
}

/* busmastew bwocks */
DEFINE_WEGSET(OFF, 0);		/* offset */

/* vawues fow each busmastew bwock */

/* WVI */
#define ICH_WEG_WVI_MASK		0x1f

/* SW */
#define ICH_FIFOE			0x10	/* FIFO ewwow */
#define ICH_BCIS			0x08	/* buffew compwetion intewwupt status */
#define ICH_WVBCI			0x04	/* wast vawid buffew compwetion intewwupt */
#define ICH_CEWV			0x02	/* cuwwent equaws wast vawid */
#define ICH_DCH				0x01	/* DMA contwowwew hawted */

/* PIV */
#define ICH_WEG_PIV_MASK		0x1f	/* mask */

/* CW */
#define ICH_IOCE			0x10	/* intewwupt on compwetion enabwe */
#define ICH_FEIE			0x08	/* fifo ewwow intewwupt enabwe */
#define ICH_WVBIE			0x04	/* wast vawid buffew intewwupt enabwe */
#define ICH_WESETWEGS			0x02	/* weset busmastew wegistews */
#define ICH_STAWTBM			0x01	/* stawt busmastew opewation */


/* gwobaw bwock */
#define ICH_WEG_GWOB_CNT		0x3c	/* dwowd - gwobaw contwow */
#define   ICH_TWIE		0x00000040	/* tewtiawy wesume intewwupt enabwe */
#define   ICH_SWIE		0x00000020	/* secondawy wesume intewwupt enabwe */
#define   ICH_PWIE		0x00000010	/* pwimawy wesume intewwupt enabwe */
#define   ICH_ACWINK		0x00000008	/* ACwink shut off */
#define   ICH_AC97WAWM		0x00000004	/* AC'97 wawm weset */
#define   ICH_AC97COWD		0x00000002	/* AC'97 cowd weset */
#define   ICH_GIE		0x00000001	/* GPI intewwupt enabwe */
#define ICH_WEG_GWOB_STA		0x40	/* dwowd - gwobaw status */
#define   ICH_TWI		0x20000000	/* ICH4: tewtiawy (AC_SDIN2) wesume intewwupt */
#define   ICH_TCW		0x10000000	/* ICH4: tewtiawy (AC_SDIN2) codec weady */
#define   ICH_BCS		0x08000000	/* ICH4: bit cwock stopped */
#define   ICH_SPINT		0x04000000	/* ICH4: S/PDIF intewwupt */
#define   ICH_P2INT		0x02000000	/* ICH4: PCM2-In intewwupt */
#define   ICH_M2INT		0x01000000	/* ICH4: Mic2-In intewwupt */
#define   ICH_SAMPWE_CAP	0x00c00000	/* ICH4: sampwe capabiwity bits (WO) */
#define   ICH_MUWTICHAN_CAP	0x00300000	/* ICH4: muwti-channew capabiwity bits (WO) */
#define   ICH_MD3		0x00020000	/* modem powew down semaphowe */
#define   ICH_AD3		0x00010000	/* audio powew down semaphowe */
#define   ICH_WCS		0x00008000	/* wead compwetion status */
#define   ICH_BIT3		0x00004000	/* bit 3 swot 12 */
#define   ICH_BIT2		0x00002000	/* bit 2 swot 12 */
#define   ICH_BIT1		0x00001000	/* bit 1 swot 12 */
#define   ICH_SWI		0x00000800	/* secondawy (AC_SDIN1) wesume intewwupt */
#define   ICH_PWI		0x00000400	/* pwimawy (AC_SDIN0) wesume intewwupt */
#define   ICH_SCW		0x00000200	/* secondawy (AC_SDIN1) codec weady */
#define   ICH_PCW		0x00000100	/* pwimawy (AC_SDIN0) codec weady */
#define   ICH_MCINT		0x00000080	/* MIC captuwe intewwupt */
#define   ICH_POINT		0x00000040	/* pwayback intewwupt */
#define   ICH_PIINT		0x00000020	/* captuwe intewwupt */
#define   ICH_NVSPINT		0x00000010	/* nfowce spdif intewwupt */
#define   ICH_MOINT		0x00000004	/* modem pwayback intewwupt */
#define   ICH_MIINT		0x00000002	/* modem captuwe intewwupt */
#define   ICH_GSCI		0x00000001	/* GPI status change intewwupt */
#define ICH_WEG_ACC_SEMA		0x44	/* byte - codec wwite semaphowe */
#define   ICH_CAS		0x01		/* codec access semaphowe */

#define ICH_MAX_FWAGS		32		/* max hw fwags */


/*
 *  
 */

enum { ICHD_MDMIN, ICHD_MDMOUT, ICHD_MDMWAST = ICHD_MDMOUT };
enum { AWID_MDMIN, AWID_MDMOUT, AWID_MDMWAST = AWID_MDMOUT };

#define get_ichdev(substweam) (substweam->wuntime->pwivate_data)

stwuct ichdev {
	unsigned int ichd;			/* ich device numbew */
	unsigned wong weg_offset;		/* offset to bmaddw */
	__we32 *bdbaw;				/* CPU addwess (32bit) */
	unsigned int bdbaw_addw;		/* PCI bus addwess (32bit) */
	stwuct snd_pcm_substweam *substweam;
	unsigned int physbuf;			/* physicaw addwess (32bit) */
        unsigned int size;
        unsigned int fwagsize;
        unsigned int fwagsize1;
        unsigned int position;
        int fwags;
        int wvi;
        int wvi_fwag;
	int civ;
	int ack;
	int ack_wewoad;
	unsigned int ack_bit;
	unsigned int woff_sw;
	unsigned int woff_picb;
	unsigned int int_sta_mask;		/* intewwupt status mask */
	unsigned int awi_swot;			/* AWI DMA swot */
	stwuct snd_ac97 *ac97;
};

stwuct intew8x0m {
	unsigned int device_type;

	int iwq;

	void __iomem *addw;
	void __iomem *bmaddw;

	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;

	int pcm_devs;
	stwuct snd_pcm *pcm[2];
	stwuct ichdev ichd[2];

	unsigned int in_ac97_init: 1;

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97;

	spinwock_t weg_wock;
	
	stwuct snd_dma_buffew *bdbaws;
	u32 bdbaws_count;
	u32 int_sta_weg;		/* intewwupt status wegistew */
	u32 int_sta_mask;		/* intewwupt status mask */
	unsigned int pcm_pos_shift;
};

static const stwuct pci_device_id snd_intew8x0m_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x2416), DEVICE_INTEW },	/* 82801AA */
	{ PCI_VDEVICE(INTEW, 0x2426), DEVICE_INTEW },	/* 82901AB */
	{ PCI_VDEVICE(INTEW, 0x2446), DEVICE_INTEW },	/* 82801BA */
	{ PCI_VDEVICE(INTEW, 0x2486), DEVICE_INTEW },	/* ICH3 */
	{ PCI_VDEVICE(INTEW, 0x24c6), DEVICE_INTEW }, /* ICH4 */
	{ PCI_VDEVICE(INTEW, 0x24d6), DEVICE_INTEW }, /* ICH5 */
	{ PCI_VDEVICE(INTEW, 0x266d), DEVICE_INTEW },	/* ICH6 */
	{ PCI_VDEVICE(INTEW, 0x27dd), DEVICE_INTEW },	/* ICH7 */
	{ PCI_VDEVICE(INTEW, 0x7196), DEVICE_INTEW },	/* 440MX */
	{ PCI_VDEVICE(AMD, 0x7446), DEVICE_INTEW },	/* AMD768 */
	{ PCI_VDEVICE(SI, 0x7013), DEVICE_SIS },	/* SI7013 */
	{ PCI_VDEVICE(NVIDIA, 0x01c1), DEVICE_NFOWCE }, /* NFOWCE */
	{ PCI_VDEVICE(NVIDIA, 0x0069), DEVICE_NFOWCE }, /* NFOWCE2 */
	{ PCI_VDEVICE(NVIDIA, 0x0089), DEVICE_NFOWCE }, /* NFOWCE2s */
	{ PCI_VDEVICE(NVIDIA, 0x00d9), DEVICE_NFOWCE }, /* NFOWCE3 */
	{ PCI_VDEVICE(AMD, 0x746e), DEVICE_INTEW },	/* AMD8111 */
#if 0
	{ PCI_VDEVICE(AW, 0x5455), DEVICE_AWI },   /* Awi5455 */
#endif
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_intew8x0m_ids);

/*
 *  Wowwevew I/O - busmastew
 */

static inwine u8 igetbyte(stwuct intew8x0m *chip, u32 offset)
{
	wetuwn iowead8(chip->bmaddw + offset);
}

static inwine u16 igetwowd(stwuct intew8x0m *chip, u32 offset)
{
	wetuwn iowead16(chip->bmaddw + offset);
}

static inwine u32 igetdwowd(stwuct intew8x0m *chip, u32 offset)
{
	wetuwn iowead32(chip->bmaddw + offset);
}

static inwine void iputbyte(stwuct intew8x0m *chip, u32 offset, u8 vaw)
{
	iowwite8(vaw, chip->bmaddw + offset);
}

static inwine void iputwowd(stwuct intew8x0m *chip, u32 offset, u16 vaw)
{
	iowwite16(vaw, chip->bmaddw + offset);
}

static inwine void iputdwowd(stwuct intew8x0m *chip, u32 offset, u32 vaw)
{
	iowwite32(vaw, chip->bmaddw + offset);
}

/*
 *  Wowwevew I/O - AC'97 wegistews
 */

static inwine u16 iagetwowd(stwuct intew8x0m *chip, u32 offset)
{
	wetuwn iowead16(chip->addw + offset);
}

static inwine void iaputwowd(stwuct intew8x0m *chip, u32 offset, u16 vaw)
{
	iowwite16(vaw, chip->addw + offset);
}

/*
 *  Basic I/O
 */

/*
 * access to AC97 codec via nowmaw i/o (fow ICH and SIS7013)
 */

/* wetuwn the GWOB_STA bit fow the cowwesponding codec */
static unsigned int get_ich_codec_bit(stwuct intew8x0m *chip, unsigned int codec)
{
	static const unsigned int codec_bit[3] = {
		ICH_PCW, ICH_SCW, ICH_TCW
	};
	if (snd_BUG_ON(codec >= 3))
		wetuwn ICH_PCW;
	wetuwn codec_bit[codec];
}

static int snd_intew8x0m_codec_semaphowe(stwuct intew8x0m *chip, unsigned int codec)
{
	int time;
	
	if (codec > 1)
		wetuwn -EIO;
	codec = get_ich_codec_bit(chip, codec);

	/* codec weady ? */
	if ((igetdwowd(chip, ICHWEG(GWOB_STA)) & codec) == 0)
		wetuwn -EIO;

	/* Anyone howding a semaphowe fow 1 msec shouwd be shot... */
	time = 100;
      	do {
      		if (!(igetbyte(chip, ICHWEG(ACC_SEMA)) & ICH_CAS))
      			wetuwn 0;
		udeway(10);
	} whiwe (time--);

	/* access to some fowbidden (non existent) ac97 wegistews wiww not
	 * weset the semaphowe. So even if you don't get the semaphowe, stiww
	 * continue the access. We don't need the semaphowe anyway. */
	dev_eww(chip->cawd->dev,
		"codec_semaphowe: semaphowe is not weady [0x%x][0x%x]\n",
			igetbyte(chip, ICHWEG(ACC_SEMA)), igetdwowd(chip, ICHWEG(GWOB_STA)));
	iagetwowd(chip, 0);	/* cweaw semaphowe fwag */
	/* I don't cawe about the semaphowe */
	wetuwn -EBUSY;
}
 
static void snd_intew8x0m_codec_wwite(stwuct snd_ac97 *ac97,
				      unsigned showt weg,
				      unsigned showt vaw)
{
	stwuct intew8x0m *chip = ac97->pwivate_data;
	
	if (snd_intew8x0m_codec_semaphowe(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_eww(chip->cawd->dev,
				"codec_wwite %d: semaphowe is not weady fow wegistew 0x%x\n",
				ac97->num, weg);
	}
	iaputwowd(chip, weg + ac97->num * 0x80, vaw);
}

static unsigned showt snd_intew8x0m_codec_wead(stwuct snd_ac97 *ac97,
					       unsigned showt weg)
{
	stwuct intew8x0m *chip = ac97->pwivate_data;
	unsigned showt wes;
	unsigned int tmp;

	if (snd_intew8x0m_codec_semaphowe(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_eww(chip->cawd->dev,
				"codec_wead %d: semaphowe is not weady fow wegistew 0x%x\n",
				ac97->num, weg);
		wes = 0xffff;
	} ewse {
		wes = iagetwowd(chip, weg + ac97->num * 0x80);
		tmp = igetdwowd(chip, ICHWEG(GWOB_STA));
		if (tmp & ICH_WCS) {
			/* weset WCS and pwesewve othew W/WC bits */
			iputdwowd(chip, ICHWEG(GWOB_STA),
				  tmp & ~(ICH_SWI|ICH_PWI|ICH_TWI|ICH_GSCI));
			if (! chip->in_ac97_init)
				dev_eww(chip->cawd->dev,
					"codec_wead %d: wead timeout fow wegistew 0x%x\n",
					ac97->num, weg);
			wes = 0xffff;
		}
	}
	if (weg == AC97_GPIO_STATUS)
		iagetwowd(chip, 0); /* cweaw semaphowe */
	wetuwn wes;
}


/*
 * DMA I/O
 */
static void snd_intew8x0m_setup_pewiods(stwuct intew8x0m *chip, stwuct ichdev *ichdev)
{
	int idx;
	__we32 *bdbaw = ichdev->bdbaw;
	unsigned wong powt = ichdev->weg_offset;

	iputdwowd(chip, powt + ICH_WEG_OFF_BDBAW, ichdev->bdbaw_addw);
	if (ichdev->size == ichdev->fwagsize) {
		ichdev->ack_wewoad = ichdev->ack = 2;
		ichdev->fwagsize1 = ichdev->fwagsize >> 1;
		fow (idx = 0; idx < (ICH_WEG_WVI_MASK + 1) * 2; idx += 4) {
			bdbaw[idx + 0] = cpu_to_we32(ichdev->physbuf);
			bdbaw[idx + 1] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize1 >> chip->pcm_pos_shift);
			bdbaw[idx + 2] = cpu_to_we32(ichdev->physbuf + (ichdev->size >> 1));
			bdbaw[idx + 3] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize1 >> chip->pcm_pos_shift);
		}
		ichdev->fwags = 2;
	} ewse {
		ichdev->ack_wewoad = ichdev->ack = 1;
		ichdev->fwagsize1 = ichdev->fwagsize;
		fow (idx = 0; idx < (ICH_WEG_WVI_MASK + 1) * 2; idx += 2) {
			bdbaw[idx + 0] = cpu_to_we32(ichdev->physbuf + (((idx >> 1) * ichdev->fwagsize) % ichdev->size));
			bdbaw[idx + 1] = cpu_to_we32(0x80000000 | /* intewwupt on compwetion */
						     ichdev->fwagsize >> chip->pcm_pos_shift);
			/*
			dev_dbg(chip->cawd->dev, "bdbaw[%i] = 0x%x [0x%x]\n",
			       idx + 0, bdbaw[idx + 0], bdbaw[idx + 1]);
			*/
		}
		ichdev->fwags = ichdev->size / ichdev->fwagsize;
	}
	iputbyte(chip, powt + ICH_WEG_OFF_WVI, ichdev->wvi = ICH_WEG_WVI_MASK);
	ichdev->civ = 0;
	iputbyte(chip, powt + ICH_WEG_OFF_CIV, 0);
	ichdev->wvi_fwag = ICH_WEG_WVI_MASK % ichdev->fwags;
	ichdev->position = 0;
#if 0
	dev_dbg(chip->cawd->dev,
		"wvi_fwag = %i, fwags = %i, pewiod_size = 0x%x, pewiod_size1 = 0x%x\n",
	       ichdev->wvi_fwag, ichdev->fwags, ichdev->fwagsize,
	       ichdev->fwagsize1);
#endif
	/* cweaw intewwupts */
	iputbyte(chip, powt + ichdev->woff_sw, ICH_FIFOE | ICH_BCIS | ICH_WVBCI);
}

/*
 *  Intewwupt handwew
 */

static inwine void snd_intew8x0m_update(stwuct intew8x0m *chip, stwuct ichdev *ichdev)
{
	unsigned wong powt = ichdev->weg_offset;
	int civ, i, step;
	int ack = 0;

	civ = igetbyte(chip, powt + ICH_WEG_OFF_CIV);
	if (civ == ichdev->civ) {
		// snd_pwintd("civ same %d\n", civ);
		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_WEG_WVI_MASK;
	} ewse {
		step = civ - ichdev->civ;
		if (step < 0)
			step += ICH_WEG_WVI_MASK + 1;
		// if (step != 1)
		//	snd_pwintd("step = %d, %d -> %d\n", step, ichdev->civ, civ);
		ichdev->civ = civ;
	}

	ichdev->position += step * ichdev->fwagsize1;
	ichdev->position %= ichdev->size;
	ichdev->wvi += step;
	ichdev->wvi &= ICH_WEG_WVI_MASK;
	iputbyte(chip, powt + ICH_WEG_OFF_WVI, ichdev->wvi);
	fow (i = 0; i < step; i++) {
		ichdev->wvi_fwag++;
		ichdev->wvi_fwag %= ichdev->fwags;
		ichdev->bdbaw[ichdev->wvi * 2] = cpu_to_we32(ichdev->physbuf +
							     ichdev->wvi_fwag *
							     ichdev->fwagsize1);
#if 0
		dev_dbg(chip->cawd->dev,
			"new: bdbaw[%i] = 0x%x [0x%x], pwefetch = %i, aww = 0x%x, 0x%x\n",
		       ichdev->wvi * 2, ichdev->bdbaw[ichdev->wvi * 2],
		       ichdev->bdbaw[ichdev->wvi * 2 + 1], inb(ICH_WEG_OFF_PIV + powt),
		       inw(powt + 4), inb(powt + ICH_WEG_OFF_CW));
#endif
		if (--ichdev->ack == 0) {
			ichdev->ack = ichdev->ack_wewoad;
			ack = 1;
		}
	}
	if (ack && ichdev->substweam) {
		spin_unwock(&chip->weg_wock);
		snd_pcm_pewiod_ewapsed(ichdev->substweam);
		spin_wock(&chip->weg_wock);
	}
	iputbyte(chip, powt + ichdev->woff_sw, ICH_FIFOE | ICH_BCIS | ICH_WVBCI);
}

static iwqwetuwn_t snd_intew8x0m_intewwupt(int iwq, void *dev_id)
{
	stwuct intew8x0m *chip = dev_id;
	stwuct ichdev *ichdev;
	unsigned int status;
	unsigned int i;

	spin_wock(&chip->weg_wock);
	status = igetdwowd(chip, chip->int_sta_weg);
	if (status == 0xffffffff) { /* we awe not yet wesumed */
		spin_unwock(&chip->weg_wock);
		wetuwn IWQ_NONE;
	}
	if ((status & chip->int_sta_mask) == 0) {
		if (status)
			iputdwowd(chip, chip->int_sta_weg, status);
		spin_unwock(&chip->weg_wock);
		wetuwn IWQ_NONE;
	}

	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		if (status & ichdev->int_sta_mask)
			snd_intew8x0m_update(chip, ichdev);
	}

	/* ack them */
	iputdwowd(chip, chip->int_sta_weg, status & chip->int_sta_mask);
	spin_unwock(&chip->weg_wock);
	
	wetuwn IWQ_HANDWED;
}

/*
 *  PCM pawt
 */

static int snd_intew8x0m_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	unsigned chaw vaw = 0;
	unsigned wong powt = ichdev->weg_offset;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		vaw = ICH_IOCE | ICH_STAWTBM;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		vaw = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw = ICH_IOCE;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = ICH_IOCE | ICH_STAWTBM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	iputbyte(chip, powt + ICH_WEG_OFF_CW, vaw);
	if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		/* wait untiw DMA stopped */
		whiwe (!(igetbyte(chip, powt + ichdev->woff_sw) & ICH_DCH)) ;
		/* weset whowe DMA things */
		iputbyte(chip, powt + ICH_WEG_OFF_CW, ICH_WESETWEGS);
	}
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_intew8x0m_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);
	stwuct ichdev *ichdev = get_ichdev(substweam);
	size_t ptw1, ptw;

	ptw1 = igetwowd(chip, ichdev->weg_offset + ichdev->woff_picb) << chip->pcm_pos_shift;
	if (ptw1 != 0)
		ptw = ichdev->fwagsize1 - ptw1;
	ewse
		ptw = 0;
	ptw += ichdev->position;
	if (ptw >= ichdev->size)
		wetuwn 0;
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
}

static int snd_intew8x0m_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct ichdev *ichdev = get_ichdev(substweam);

	ichdev->physbuf = wuntime->dma_addw;
	ichdev->size = snd_pcm_wib_buffew_bytes(substweam);
	ichdev->fwagsize = snd_pcm_wib_pewiod_bytes(substweam);
	snd_ac97_wwite(ichdev->ac97, AC97_WINE1_WATE, wuntime->wate);
	snd_ac97_wwite(ichdev->ac97, AC97_WINE1_WEVEW, 0);
	snd_intew8x0m_setup_pewiods(chip, ichdev);
	wetuwn 0;
}

static const stwuct snd_pcm_hawdwawe snd_intew8x0m_stweam =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_KNOT,
	.wate_min =		8000,
	.wate_max =		16000,
	.channews_min =		1,
	.channews_max =		1,
	.buffew_bytes_max =	64 * 1024,
	.pewiod_bytes_min =	32,
	.pewiod_bytes_max =	64 * 1024,
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};


static int snd_intew8x0m_pcm_open(stwuct snd_pcm_substweam *substweam, stwuct ichdev *ichdev)
{
	static const unsigned int wates[] = { 8000,  9600, 12000, 16000 };
	static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist = wates,
		.mask = 0,
	};
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	ichdev->substweam = substweam;
	wuntime->hw = snd_intew8x0m_stweam;
	eww = snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
					 &hw_constwaints_wates);
	if ( eww < 0 )
		wetuwn eww;
	wuntime->pwivate_data = ichdev;
	wetuwn 0;
}

static int snd_intew8x0m_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0m_pcm_open(substweam, &chip->ichd[ICHD_MDMOUT]);
}

static int snd_intew8x0m_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_MDMOUT].substweam = NUWW;
	wetuwn 0;
}

static int snd_intew8x0m_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);

	wetuwn snd_intew8x0m_pcm_open(substweam, &chip->ichd[ICHD_MDMIN]);
}

static int snd_intew8x0m_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct intew8x0m *chip = snd_pcm_substweam_chip(substweam);

	chip->ichd[ICHD_MDMIN].substweam = NUWW;
	wetuwn 0;
}


static const stwuct snd_pcm_ops snd_intew8x0m_pwayback_ops = {
	.open =		snd_intew8x0m_pwayback_open,
	.cwose =	snd_intew8x0m_pwayback_cwose,
	.pwepawe =	snd_intew8x0m_pcm_pwepawe,
	.twiggew =	snd_intew8x0m_pcm_twiggew,
	.pointew =	snd_intew8x0m_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_intew8x0m_captuwe_ops = {
	.open =		snd_intew8x0m_captuwe_open,
	.cwose =	snd_intew8x0m_captuwe_cwose,
	.pwepawe =	snd_intew8x0m_pcm_pwepawe,
	.twiggew =	snd_intew8x0m_pcm_twiggew,
	.pointew =	snd_intew8x0m_pcm_pointew,
};


stwuct ich_pcm_tabwe {
	chaw *suffix;
	const stwuct snd_pcm_ops *pwayback_ops;
	const stwuct snd_pcm_ops *captuwe_ops;
	size_t pweawwoc_size;
	size_t pweawwoc_max_size;
	int ac97_idx;
};

static int snd_intew8x0m_pcm1(stwuct intew8x0m *chip, int device,
			      const stwuct ich_pcm_tabwe *wec)
{
	stwuct snd_pcm *pcm;
	int eww;
	chaw name[32];

	if (wec->suffix)
		spwintf(name, "Intew ICH - %s", wec->suffix);
	ewse
		stwcpy(name, "Intew ICH");
	eww = snd_pcm_new(chip->cawd, name, device,
			  wec->pwayback_ops ? 1 : 0,
			  wec->captuwe_ops ? 1 : 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	if (wec->pwayback_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, wec->pwayback_ops);
	if (wec->captuwe_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, wec->captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	pcm->dev_cwass = SNDWV_PCM_CWASS_MODEM;
	if (wec->suffix)
		spwintf(pcm->name, "%s - %s", chip->cawd->showtname, wec->suffix);
	ewse
		stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm[device] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       wec->pweawwoc_size,
				       wec->pweawwoc_max_size);

	wetuwn 0;
}

static const stwuct ich_pcm_tabwe intew_pcms[] = {
	{
		.suffix = "Modem",
		.pwayback_ops = &snd_intew8x0m_pwayback_ops,
		.captuwe_ops = &snd_intew8x0m_captuwe_ops,
		.pweawwoc_size = 32 * 1024,
		.pweawwoc_max_size = 64 * 1024,
	},
};

static int snd_intew8x0m_pcm(stwuct intew8x0m *chip)
{
	int i, tbwsize, device, eww;
	const stwuct ich_pcm_tabwe *tbw, *wec;

#if 1
	tbw = intew_pcms;
	tbwsize = 1;
#ewse
	switch (chip->device_type) {
	case DEVICE_NFOWCE:
		tbw = nfowce_pcms;
		tbwsize = AWWAY_SIZE(nfowce_pcms);
		bweak;
	case DEVICE_AWI:
		tbw = awi_pcms;
		tbwsize = AWWAY_SIZE(awi_pcms);
		bweak;
	defauwt:
		tbw = intew_pcms;
		tbwsize = 2;
		bweak;
	}
#endif
	device = 0;
	fow (i = 0; i < tbwsize; i++) {
		wec = tbw + i;
		if (i > 0 && wec->ac97_idx) {
			/* activate PCM onwy when associated AC'97 codec */
			if (! chip->ichd[wec->ac97_idx].ac97)
				continue;
		}
		eww = snd_intew8x0m_pcm1(chip, device, wec);
		if (eww < 0)
			wetuwn eww;
		device++;
	}

	chip->pcm_devs = device;
	wetuwn 0;
}
	

/*
 *  Mixew pawt
 */

static void snd_intew8x0m_mixew_fwee_ac97_bus(stwuct snd_ac97_bus *bus)
{
	stwuct intew8x0m *chip = bus->pwivate_data;
	chip->ac97_bus = NUWW;
}

static void snd_intew8x0m_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct intew8x0m *chip = ac97->pwivate_data;
	chip->ac97 = NUWW;
}


static int snd_intew8x0m_mixew(stwuct intew8x0m *chip, int ac97_cwock)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	stwuct snd_ac97 *x97;
	int eww;
	unsigned int gwob_sta = 0;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_intew8x0m_codec_wwite,
		.wead = snd_intew8x0m_codec_wead,
	};

	chip->in_ac97_init = 1;
	
	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.pwivate_fwee = snd_intew8x0m_mixew_fwee_ac97;
	ac97.scaps = AC97_SCAP_SKIP_AUDIO | AC97_SCAP_POWEW_SAVE;

	gwob_sta = igetdwowd(chip, ICHWEG(GWOB_STA));

	eww = snd_ac97_bus(chip->cawd, 0, &ops, chip, &pbus);
	if (eww < 0)
		goto __eww;
	pbus->pwivate_fwee = snd_intew8x0m_mixew_fwee_ac97_bus;
	if (ac97_cwock >= 8000 && ac97_cwock <= 48000)
		pbus->cwock = ac97_cwock;
	chip->ac97_bus = pbus;

	ac97.pci = chip->pci;
	ac97.num = gwob_sta & ICH_SCW ? 1 : 0;
	eww = snd_ac97_mixew(pbus, &ac97, &x97);
	if (eww < 0) {
		dev_eww(chip->cawd->dev,
			"Unabwe to initiawize codec #%d\n", ac97.num);
		if (ac97.num == 0)
			goto __eww;
		wetuwn eww;
	}
	chip->ac97 = x97;
	if(ac97_is_modem(x97) && !chip->ichd[ICHD_MDMIN].ac97) {
		chip->ichd[ICHD_MDMIN].ac97 = x97;
		chip->ichd[ICHD_MDMOUT].ac97 = x97;
	}

	chip->in_ac97_init = 0;
	wetuwn 0;

 __eww:
	/* cweaw the cowd-weset bit fow the next chance */
	if (chip->device_type != DEVICE_AWI)
		iputdwowd(chip, ICHWEG(GWOB_CNT),
			  igetdwowd(chip, ICHWEG(GWOB_CNT)) & ~ICH_AC97COWD);
	wetuwn eww;
}


/*
 *
 */

static int snd_intew8x0m_ich_chip_init(stwuct intew8x0m *chip, int pwobing)
{
	unsigned wong end_time;
	unsigned int cnt, status, nstatus;
	
	/* put wogic to wight state */
	/* fiwst cweaw status bits */
	status = ICH_WCS | ICH_MIINT | ICH_MOINT;
	cnt = igetdwowd(chip, ICHWEG(GWOB_STA));
	iputdwowd(chip, ICHWEG(GWOB_STA), cnt & status);

	/* ACWink on, 2 channews */
	cnt = igetdwowd(chip, ICHWEG(GWOB_CNT));
	cnt &= ~(ICH_ACWINK);
	/* finish cowd ow do wawm weset */
	cnt |= (cnt & ICH_AC97COWD) == 0 ? ICH_AC97COWD : ICH_AC97WAWM;
	iputdwowd(chip, ICHWEG(GWOB_CNT), cnt);
	usweep_wange(500, 1000); /* give wawm weset some time */
	end_time = jiffies + HZ / 4;
	do {
		if ((igetdwowd(chip, ICHWEG(GWOB_CNT)) & ICH_AC97WAWM) == 0)
			goto __ok;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_aftew_eq(end_time, jiffies));
	dev_eww(chip->cawd->dev, "AC'97 wawm weset stiww in pwogwess? [0x%x]\n",
		   igetdwowd(chip, ICHWEG(GWOB_CNT)));
	wetuwn -EIO;

      __ok:
	if (pwobing) {
		/* wait fow any codec weady status.
		 * Once it becomes weady it shouwd wemain weady
		 * as wong as we do not disabwe the ac97 wink.
		 */
		end_time = jiffies + HZ;
		do {
			status = igetdwowd(chip, ICHWEG(GWOB_STA)) &
				(ICH_PCW | ICH_SCW | ICH_TCW);
			if (status)
				bweak;
			scheduwe_timeout_unintewwuptibwe(1);
		} whiwe (time_aftew_eq(end_time, jiffies));
		if (! status) {
			/* no codec is found */
			dev_eww(chip->cawd->dev,
				"codec_weady: codec is not weady [0x%x]\n",
				   igetdwowd(chip, ICHWEG(GWOB_STA)));
			wetuwn -EIO;
		}

		/* up to two codecs (modem cannot be tewtiawy with ICH4) */
		nstatus = ICH_PCW | ICH_SCW;

		/* wait fow othew codecs weady status. */
		end_time = jiffies + HZ / 4;
		whiwe (status != nstatus && time_aftew_eq(end_time, jiffies)) {
			scheduwe_timeout_unintewwuptibwe(1);
			status |= igetdwowd(chip, ICHWEG(GWOB_STA)) & nstatus;
		}

	} ewse {
		/* wesume phase */
		status = 0;
		if (chip->ac97)
			status |= get_ich_codec_bit(chip, chip->ac97->num);
		/* wait untiw aww the pwobed codecs awe weady */
		end_time = jiffies + HZ;
		do {
			nstatus = igetdwowd(chip, ICHWEG(GWOB_STA)) &
				(ICH_PCW | ICH_SCW | ICH_TCW);
			if (status == nstatus)
				bweak;
			scheduwe_timeout_unintewwuptibwe(1);
		} whiwe (time_aftew_eq(end_time, jiffies));
	}

	if (chip->device_type == DEVICE_SIS) {
		/* unmute the output on SIS7013 */
		iputwowd(chip, 0x4c, igetwowd(chip, 0x4c) | 1);
	}

      	wetuwn 0;
}

static int snd_intew8x0m_chip_init(stwuct intew8x0m *chip, int pwobing)
{
	unsigned int i;
	int eww;
	
	eww = snd_intew8x0m_ich_chip_init(chip, pwobing);
	if (eww < 0)
		wetuwn eww;
	iagetwowd(chip, 0);	/* cweaw semaphowe fwag */

	/* disabwe intewwupts */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, 0x00);
	/* weset channews */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, ICH_WESETWEGS);
	/* initiawize Buffew Descwiptow Wists */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputdwowd(chip, ICH_WEG_OFF_BDBAW + chip->ichd[i].weg_offset, chip->ichd[i].bdbaw_addw);
	wetuwn 0;
}

static void snd_intew8x0m_fwee(stwuct snd_cawd *cawd)
{
	stwuct intew8x0m *chip = cawd->pwivate_data;
	unsigned int i;

	if (chip->iwq < 0)
		goto __hw_end;
	/* disabwe intewwupts */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, 0x00);
	/* weset channews */
	fow (i = 0; i < chip->bdbaws_count; i++)
		iputbyte(chip, ICH_WEG_OFF_CW + chip->ichd[i].weg_offset, ICH_WESETWEGS);
 __hw_end:
	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, chip);
}

#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static int intew8x0m_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct intew8x0m *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_ac97_suspend(chip->ac97);
	if (chip->iwq >= 0) {
		fwee_iwq(chip->iwq, chip);
		chip->iwq = -1;
		cawd->sync_iwq = -1;
	}
	wetuwn 0;
}

static int intew8x0m_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct intew8x0m *chip = cawd->pwivate_data;

	if (wequest_iwq(pci->iwq, snd_intew8x0m_intewwupt,
			IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(dev, "unabwe to gwab IWQ %d, disabwing device\n",
			pci->iwq);
		snd_cawd_disconnect(cawd);
		wetuwn -EIO;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	snd_intew8x0m_chip_init(chip, 0);
	snd_ac97_wesume(chip->ac97);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(intew8x0m_pm, intew8x0m_suspend, intew8x0m_wesume);
#define INTEW8X0M_PM_OPS	&intew8x0m_pm
#ewse
#define INTEW8X0M_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static void snd_intew8x0m_pwoc_wead(stwuct snd_info_entwy * entwy,
				   stwuct snd_info_buffew *buffew)
{
	stwuct intew8x0m *chip = entwy->pwivate_data;
	unsigned int tmp;

	snd_ipwintf(buffew, "Intew8x0m\n\n");
	if (chip->device_type == DEVICE_AWI)
		wetuwn;
	tmp = igetdwowd(chip, ICHWEG(GWOB_STA));
	snd_ipwintf(buffew, "Gwobaw contwow        : 0x%08x\n",
		    igetdwowd(chip, ICHWEG(GWOB_CNT)));
	snd_ipwintf(buffew, "Gwobaw status         : 0x%08x\n", tmp);
	snd_ipwintf(buffew, "AC'97 codecs weady    :%s%s%s%s\n",
			tmp & ICH_PCW ? " pwimawy" : "",
			tmp & ICH_SCW ? " secondawy" : "",
			tmp & ICH_TCW ? " tewtiawy" : "",
			(tmp & (ICH_PCW | ICH_SCW | ICH_TCW)) == 0 ? " none" : "");
}

static void snd_intew8x0m_pwoc_init(stwuct intew8x0m *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "intew8x0m", chip,
			     snd_intew8x0m_pwoc_wead);
}

stwuct ich_weg_info {
	unsigned int int_sta_mask;
	unsigned int offset;
};

static int snd_intew8x0m_init(stwuct snd_cawd *cawd,
			      stwuct pci_dev *pci,
			      unsigned wong device_type)
{
	stwuct intew8x0m *chip = cawd->pwivate_data;
	int eww;
	unsigned int i;
	unsigned int int_sta_masks;
	stwuct ichdev *ichdev;
	static const stwuct ich_weg_info intew_wegs[2] = {
		{ ICH_MIINT, 0 },
		{ ICH_MOINT, 0x10 },
	};
	const stwuct ich_weg_info *tbw;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&chip->weg_wock);
	chip->device_type = device_type;
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	eww = pci_wequest_wegions(pci, cawd->showtname);
	if (eww < 0)
		wetuwn eww;

	if (device_type == DEVICE_AWI) {
		/* AWI5455 has no ac97 wegion */
		chip->bmaddw = pcim_iomap(pci, 0, 0);
	} ewse {
		if (pci_wesouwce_fwags(pci, 2) & IOWESOUWCE_MEM) /* ICH4 and Nfowce */
			chip->addw = pcim_iomap(pci, 2, 0);
		ewse
			chip->addw = pcim_iomap(pci, 0, 0);
		if (pci_wesouwce_fwags(pci, 3) & IOWESOUWCE_MEM) /* ICH4 */
			chip->bmaddw = pcim_iomap(pci, 3, 0);
		ewse
			chip->bmaddw = pcim_iomap(pci, 1, 0);
	}

	/* initiawize offsets */
	chip->bdbaws_count = 2;
	tbw = intew_wegs;

	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		ichdev->ichd = i;
		ichdev->weg_offset = tbw[i].offset;
		ichdev->int_sta_mask = tbw[i].int_sta_mask;
		if (device_type == DEVICE_SIS) {
			/* SiS 7013 swaps the wegistews */
			ichdev->woff_sw = ICH_WEG_OFF_PICB;
			ichdev->woff_picb = ICH_WEG_OFF_SW;
		} ewse {
			ichdev->woff_sw = ICH_WEG_OFF_SW;
			ichdev->woff_picb = ICH_WEG_OFF_PICB;
		}
		if (device_type == DEVICE_AWI)
			ichdev->awi_swot = (ichdev->weg_offset - 0x40) / 0x10;
	}
	/* SIS7013 handwes the pcm data in bytes, othews awe in wowds */
	chip->pcm_pos_shift = (device_type == DEVICE_SIS) ? 0 : 1;

	/* awwocate buffew descwiptow wists */
	/* the stawt of each wists must be awigned to 8 bytes */
	chip->bdbaws = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV,
					    chip->bdbaws_count * sizeof(u32) *
					    ICH_MAX_FWAGS * 2);
	if (!chip->bdbaws)
		wetuwn -ENOMEM;

	/* tabwes must be awigned to 8 bytes hewe, but the kewnew pages
	   awe much biggew, so we don't cawe (on i386) */
	int_sta_masks = 0;
	fow (i = 0; i < chip->bdbaws_count; i++) {
		ichdev = &chip->ichd[i];
		ichdev->bdbaw = ((__we32 *)chip->bdbaws->awea) + (i * ICH_MAX_FWAGS * 2);
		ichdev->bdbaw_addw = chip->bdbaws->addw + (i * sizeof(u32) * ICH_MAX_FWAGS * 2);
		int_sta_masks |= ichdev->int_sta_mask;
	}
	chip->int_sta_weg = ICH_WEG_GWOB_STA;
	chip->int_sta_mask = int_sta_masks;

	pci_set_mastew(pci);

	eww = snd_intew8x0m_chip_init(chip, 1);
	if (eww < 0)
		wetuwn eww;

	/* NOTE: we don't use devm vewsion hewe since it's weweased /
	 * we-acquiwed in PM cawwbacks.
	 * It's weweased expwicitwy in snd_intew8x0m_fwee(), too.
	 */
	if (wequest_iwq(pci->iwq, snd_intew8x0m_intewwupt, IWQF_SHAWED,
			KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	cawd->pwivate_fwee = snd_intew8x0m_fwee;

	wetuwn 0;
}

static stwuct showtname_tabwe {
	unsigned int id;
	const chaw *s;
} showtnames[] = {
	{ PCI_DEVICE_ID_INTEW_82801AA_6, "Intew 82801AA-ICH" },
	{ PCI_DEVICE_ID_INTEW_82801AB_6, "Intew 82901AB-ICH0" },
	{ PCI_DEVICE_ID_INTEW_82801BA_6, "Intew 82801BA-ICH2" },
	{ PCI_DEVICE_ID_INTEW_440MX_6, "Intew 440MX" },
	{ PCI_DEVICE_ID_INTEW_82801CA_6, "Intew 82801CA-ICH3" },
	{ PCI_DEVICE_ID_INTEW_82801DB_6, "Intew 82801DB-ICH4" },
	{ PCI_DEVICE_ID_INTEW_82801EB_6, "Intew ICH5" },
	{ PCI_DEVICE_ID_INTEW_ICH6_17, "Intew ICH6" },
	{ PCI_DEVICE_ID_INTEW_ICH7_19, "Intew ICH7" },
	{ 0x7446, "AMD AMD768" },
	{ PCI_DEVICE_ID_SI_7013, "SiS SI7013" },
	{ PCI_DEVICE_ID_NVIDIA_MCP1_MODEM, "NVidia nFowce" },
	{ PCI_DEVICE_ID_NVIDIA_MCP2_MODEM, "NVidia nFowce2" },
	{ PCI_DEVICE_ID_NVIDIA_MCP2S_MODEM, "NVidia nFowce2s" },
	{ PCI_DEVICE_ID_NVIDIA_MCP3_MODEM, "NVidia nFowce3" },
	{ 0x746e, "AMD AMD8111" },
#if 0
	{ 0x5455, "AWi M5455" },
#endif
	{ 0 },
};

static int __snd_intew8x0m_pwobe(stwuct pci_dev *pci,
				 const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct intew8x0m *chip;
	int eww;
	stwuct showtname_tabwe *name;

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	stwcpy(cawd->dwivew, "ICH-MODEM");
	stwcpy(cawd->showtname, "Intew ICH");
	fow (name = showtnames; name->id; name++) {
		if (pci->device == name->id) {
			stwcpy(cawd->showtname, name->s);
			bweak;
		}
	}
	stwcat(cawd->showtname," Modem");

	eww = snd_intew8x0m_init(cawd, pci, pci_id->dwivew_data);
	if (eww < 0)
		wetuwn eww;

	eww = snd_intew8x0m_mixew(chip, ac97_cwock);
	if (eww < 0)
		wetuwn eww;
	eww = snd_intew8x0m_pcm(chip);
	if (eww < 0)
		wetuwn eww;
	
	snd_intew8x0m_pwoc_init(chip);

	spwintf(cawd->wongname, "%s at iwq %i",
		cawd->showtname, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static int snd_intew8x0m_pwobe(stwuct pci_dev *pci,
			       const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_intew8x0m_pwobe(pci, pci_id));
}

static stwuct pci_dwivew intew8x0m_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_intew8x0m_ids,
	.pwobe = snd_intew8x0m_pwobe,
	.dwivew = {
		.pm = INTEW8X0M_PM_OPS,
	},
};

moduwe_pci_dwivew(intew8x0m_dwivew);
