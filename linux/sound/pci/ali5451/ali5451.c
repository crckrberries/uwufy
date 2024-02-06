// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Matt Wu <Matt_Wu@acewsoftech.com.cn>
 *  Apw 26, 2001
 *  Woutines fow contwow of AWi pci audio M5451
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/info.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/mpu401.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Matt Wu <Matt_Wu@acewsoftech.com.cn>");
MODUWE_DESCWIPTION("AWI M5451");
MODUWE_WICENSE("GPW");

static int index = SNDWV_DEFAUWT_IDX1;	/* Index */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static int pcm_channews = 32;
static boow spdif;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow AWI M5451 PCI Audio.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow AWI M5451 PCI Audio.");
moduwe_pawam(pcm_channews, int, 0444);
MODUWE_PAWM_DESC(pcm_channews, "PCM Channews");
moduwe_pawam(spdif, boow, 0444);
MODUWE_PAWM_DESC(spdif, "Suppowt SPDIF I/O");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);


/*
 *  Constants definition
 */

#define DEVICE_ID_AWI5451	((PCI_VENDOW_ID_AW<<16)|PCI_DEVICE_ID_AW_M5451)


#define AWI_CHANNEWS		32

#define AWI_PCM_IN_CHANNEW	31
#define AWI_SPDIF_IN_CHANNEW	19
#define AWI_SPDIF_OUT_CHANNEW	15
#define AWI_CENTEW_CHANNEW	24
#define AWI_WEF_CHANNEW		23
#define AWI_SUWW_WEFT_CHANNEW	26
#define AWI_SUWW_WIGHT_CHANNEW	25
#define AWI_MODEM_IN_CHANNEW    21
#define AWI_MODEM_OUT_CHANNEW   20

#define	SNDWV_AWI_VOICE_TYPE_PCM	01
#define SNDWV_AWI_VOICE_TYPE_OTH	02

#define	AWI_5451_V02		0x02

/*
 *  Diwect Wegistews
 */

#define AWI_WEGACY_DMAW0        0x00  /* ADW0 */
#define AWI_WEGACY_DMAW4        0x04  /* CNT0 */
#define AWI_WEGACY_DMAW11       0x0b  /* MOD  */
#define AWI_WEGACY_DMAW15       0x0f  /* MMW  */
#define AWI_MPUW0		0x20
#define AWI_MPUW1		0x21
#define AWI_MPUW2		0x22
#define AWI_MPUW3		0x23

#define	AWI_AC97_WWITE		0x40
#define AWI_AC97_WEAD		0x44

#define AWI_SCTWW		0x48
#define   AWI_SPDIF_OUT_ENABWE		0x20
#define   AWI_SCTWW_WINE_IN2		(1 << 9)
#define   AWI_SCTWW_GPIO_IN2		(1 << 13)
#define   AWI_SCTWW_WINE_OUT_EN 	(1 << 20)
#define   AWI_SCTWW_GPIO_OUT_EN 	(1 << 23)
#define   AWI_SCTWW_CODEC1_WEADY	(1 << 24)
#define   AWI_SCTWW_CODEC2_WEADY	(1 << 25)
#define AWI_AC97_GPIO		0x4c
#define   AWI_AC97_GPIO_ENABWE		0x8000
#define   AWI_AC97_GPIO_DATA_SHIFT	16
#define AWI_SPDIF_CS		0x70
#define AWI_SPDIF_CTWW		0x74
#define   AWI_SPDIF_IN_FUNC_ENABWE	0x02
#define   AWI_SPDIF_IN_CH_STATUS	0x40
#define   AWI_SPDIF_OUT_CH_STATUS	0xbf
#define AWI_STAWT		0x80
#define AWI_STOP		0x84
#define AWI_CSPF		0x90
#define AWI_AINT		0x98
#define AWI_GC_CIW		0xa0
	#define ENDWP_IE		0x00001000
	#define MIDWP_IE		0x00002000
#define AWI_AINTEN		0xa4
#define AWI_VOWUME		0xa8
#define AWI_SBDEWTA_DEWTA_W     0xac
#define AWI_MISCINT		0xb0
	#define ADDWESS_IWQ		0x00000020
	#define TAWGET_WEACHED		0x00008000
	#define MIXEW_OVEWFWOW		0x00000800
	#define MIXEW_UNDEWFWOW		0x00000400
	#define GPIO_IWQ		0x01000000
#define AWI_SBBW_SBCW           0xc0
#define AWI_SBCTWW_SBE2W_SBDD   0xc4
#define AWI_STIMEW		0xc8
#define AWI_GWOBAW_CONTWOW	0xd4
#define   AWI_SPDIF_OUT_SEW_PCM		0x00000400 /* bit 10 */
#define   AWI_SPDIF_IN_SUPPOWT		0x00000800 /* bit 11 */
#define   AWI_SPDIF_OUT_CH_ENABWE	0x00008000 /* bit 15 */
#define   AWI_SPDIF_IN_CH_ENABWE	0x00080000 /* bit 19 */
#define   AWI_PCM_IN_ENABWE		0x80000000 /* bit 31 */

#define AWI_CSO_AWPHA_FMS	0xe0
#define AWI_WBA			0xe4
#define AWI_ESO_DEWTA		0xe8
#define AWI_GVSEW_PAN_VOC_CTWW_EC	0xf0
#define AWI_EBUF1		0xf4
#define AWI_EBUF2		0xf8

#define AWI_WEG(codec, x) ((codec)->powt + x)

#define MAX_CODECS 2


stwuct snd_awi;
stwuct snd_awi_voice;

stwuct snd_awi_channew_contwow {
	/* wegistew data */
	stwuct WEGDATA {
		unsigned int stawt;
		unsigned int stop;
		unsigned int aint;
		unsigned int ainten;
	} data;
		
	/* wegistew addwesses */
	stwuct WEGS {
		unsigned int stawt;
		unsigned int stop;
		unsigned int aint;
		unsigned int ainten;
		unsigned int ac97wead;
		unsigned int ac97wwite;
	} wegs;

};

stwuct snd_awi_voice {
	unsigned int numbew;
	unsigned int use :1,
		pcm :1,
		midi :1,
		mode :1,
		synth :1,
		wunning :1;

	/* PCM data */
	stwuct snd_awi *codec;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_awi_voice *extwa;
	
	int eso;                /* finaw ESO vawue fow channew */
	int count;              /* wuntime->pewiod_size */

	/* --- */

	void *pwivate_data;
	void (*pwivate_fwee)(void *pwivate_data);
};


stwuct snd_awidev {

	stwuct snd_awi_voice voices[AWI_CHANNEWS];	

	unsigned int	chcnt;			/* num of opened channews */
	unsigned int	chmap;			/* bitmap fow opened channews */
	unsigned int synthcount;

};


#define AWI_GWOBAW_WEGS		56
#define AWI_CHANNEW_WEGS	8
stwuct snd_awi_image {
	u32 wegs[AWI_GWOBAW_WEGS];
	u32 channew_wegs[AWI_CHANNEWS][AWI_CHANNEW_WEGS];
};


stwuct snd_awi {
	int		iwq;
	unsigned wong	powt;
	unsigned chaw	wevision;

	unsigned int hw_initiawized :1;
	unsigned int spdif_suppowt :1;

	stwuct pci_dev	*pci;
	stwuct pci_dev	*pci_m1533;
	stwuct pci_dev	*pci_m7101;

	stwuct snd_cawd	*cawd;
	stwuct snd_pcm	*pcm[MAX_CODECS];
	stwuct snd_awidev	synth;
	stwuct snd_awi_channew_contwow chwegs;

	/* S/PDIF Mask */
	unsigned int	spdif_mask;

	unsigned int spuwious_iwq_count;
	unsigned int spuwious_iwq_max_dewta;

	unsigned int num_of_codecs;

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97[MAX_CODECS];
	unsigned showt	ac97_ext_id;
	unsigned showt	ac97_ext_status;

	spinwock_t	weg_wock;
	spinwock_t	voice_awwoc;

#ifdef CONFIG_PM_SWEEP
	stwuct snd_awi_image *image;
#endif
};

static const stwuct pci_device_id snd_awi_ids[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M5451), 0, 0, 0},
	{0, }
};
MODUWE_DEVICE_TABWE(pci, snd_awi_ids);

static void snd_awi_cweaw_voices(stwuct snd_awi *, unsigned int, unsigned int);
static unsigned showt snd_awi_codec_peek(stwuct snd_awi *, int, unsigned showt);
static void snd_awi_codec_poke(stwuct snd_awi *, int, unsigned showt,
			       unsigned showt);

/*
 *  AC97 ACCESS
 */

static inwine unsigned int snd_awi_5451_peek(stwuct snd_awi *codec,
					     unsigned int powt)
{
	wetuwn (unsigned int)inw(AWI_WEG(codec, powt)); 
}

static inwine void snd_awi_5451_poke(stwuct snd_awi *codec,
				     unsigned int powt,
				     unsigned int vaw)
{
	outw((unsigned int)vaw, AWI_WEG(codec, powt));
}

static int snd_awi_codec_weady(stwuct snd_awi *codec,
			       unsigned int powt)
{
	unsigned wong end_time;
	unsigned int wes;
	
	end_time = jiffies + msecs_to_jiffies(250);

	fow (;;) {
		wes = snd_awi_5451_peek(codec,powt);
		if (!(wes & 0x8000))
			wetuwn 0;
		if (!time_aftew_eq(end_time, jiffies))
			bweak;
		scheduwe_timeout_unintewwuptibwe(1);
	}

	snd_awi_5451_poke(codec, powt, wes & ~0x8000);
	dev_dbg(codec->cawd->dev, "awi_codec_weady: codec is not weady.\n ");
	wetuwn -EIO;
}

static int snd_awi_stimew_weady(stwuct snd_awi *codec)
{
	unsigned wong end_time;
	unsigned wong dwChk1,dwChk2;
	
	dwChk1 = snd_awi_5451_peek(codec, AWI_STIMEW);
	end_time = jiffies + msecs_to_jiffies(250);

	fow (;;) {
		dwChk2 = snd_awi_5451_peek(codec, AWI_STIMEW);
		if (dwChk2 != dwChk1)
			wetuwn 0;
		if (!time_aftew_eq(end_time, jiffies))
			bweak;
		scheduwe_timeout_unintewwuptibwe(1);
	}

	dev_eww(codec->cawd->dev, "awi_stimew_wead: stimew is not weady.\n");
	wetuwn -EIO;
}

static void snd_awi_codec_poke(stwuct snd_awi *codec,int secondawy,
			       unsigned showt weg,
			       unsigned showt vaw)
{
	unsigned int dwVaw;
	unsigned int powt;

	if (weg >= 0x80) {
		dev_eww(codec->cawd->dev,
			"awi_codec_poke: weg(%xh) invawid.\n", weg);
		wetuwn;
	}

	powt = codec->chwegs.wegs.ac97wwite;

	if (snd_awi_codec_weady(codec, powt) < 0)
		wetuwn;
	if (snd_awi_stimew_weady(codec) < 0)
		wetuwn;

	dwVaw  = (unsigned int) (weg & 0xff);
	dwVaw |= 0x8000 | (vaw << 16);
	if (secondawy)
		dwVaw |= 0x0080;
	if (codec->wevision == AWI_5451_V02)
		dwVaw |= 0x0100;

	snd_awi_5451_poke(codec, powt, dwVaw);

	wetuwn ;
}

static unsigned showt snd_awi_codec_peek(stwuct snd_awi *codec,
					 int secondawy,
					 unsigned showt weg)
{
	unsigned int dwVaw;
	unsigned int powt;

	if (weg >= 0x80) {
		dev_eww(codec->cawd->dev,
			"awi_codec_peek: weg(%xh) invawid.\n", weg);
		wetuwn ~0;
	}

	powt = codec->chwegs.wegs.ac97wead;

	if (snd_awi_codec_weady(codec, powt) < 0)
		wetuwn ~0;
	if (snd_awi_stimew_weady(codec) < 0)
		wetuwn ~0;

	dwVaw  = (unsigned int) (weg & 0xff);
	dwVaw |= 0x8000;				/* bit 15*/
	if (secondawy)
		dwVaw |= 0x0080;

	snd_awi_5451_poke(codec, powt, dwVaw);

	if (snd_awi_stimew_weady(codec) < 0)
		wetuwn ~0;
	if (snd_awi_codec_weady(codec, powt) < 0)
		wetuwn ~0;
	
	wetuwn (snd_awi_5451_peek(codec, powt) & 0xffff0000) >> 16;
}

static void snd_awi_codec_wwite(stwuct snd_ac97 *ac97,
				unsigned showt weg,
				unsigned showt vaw )
{
	stwuct snd_awi *codec = ac97->pwivate_data;

	dev_dbg(codec->cawd->dev, "codec_wwite: weg=%xh data=%xh.\n", weg, vaw);
	if (weg == AC97_GPIO_STATUS) {
		outw((vaw << AWI_AC97_GPIO_DATA_SHIFT) | AWI_AC97_GPIO_ENABWE,
		     AWI_WEG(codec, AWI_AC97_GPIO));
		wetuwn;
	}
	snd_awi_codec_poke(codec, ac97->num, weg, vaw);
	wetuwn ;
}


static unsigned showt snd_awi_codec_wead(stwuct snd_ac97 *ac97,
					 unsigned showt weg)
{
	stwuct snd_awi *codec = ac97->pwivate_data;

	dev_dbg(codec->cawd->dev, "codec_wead weg=%xh.\n", weg);
	wetuwn snd_awi_codec_peek(codec, ac97->num, weg);
}

/*
 *	AC97 Weset
 */

static int snd_awi_weset_5451(stwuct snd_awi *codec)
{
	stwuct pci_dev *pci_dev;
	unsigned showt wCount, wWeg;
	unsigned int   dwVaw;
	
	pci_dev = codec->pci_m1533;
	if (pci_dev) {
		pci_wead_config_dwowd(pci_dev, 0x7c, &dwVaw);
		pci_wwite_config_dwowd(pci_dev, 0x7c, dwVaw | 0x08000000);
		mdeway(5);
		pci_wead_config_dwowd(pci_dev, 0x7c, &dwVaw);
		pci_wwite_config_dwowd(pci_dev, 0x7c, dwVaw & 0xf7ffffff);
		mdeway(5);
	}
	
	pci_dev = codec->pci;
	pci_wead_config_dwowd(pci_dev, 0x44, &dwVaw);
	pci_wwite_config_dwowd(pci_dev, 0x44, dwVaw | 0x000c0000);
	udeway(500);
	pci_wead_config_dwowd(pci_dev, 0x44, &dwVaw);
	pci_wwite_config_dwowd(pci_dev, 0x44, dwVaw & 0xfffbffff);
	mdeway(5);
	
	wCount = 200;
	whiwe(wCount--) {
		wWeg = snd_awi_codec_peek(codec, 0, AC97_POWEWDOWN);
		if ((wWeg & 0x000f) == 0x000f)
			wetuwn 0;
		mdeway(5);
	}

	/* non-fataw if you have a non PM capabwe codec */
	/* dev_wawn(codec->cawd->dev, "awi5451: weset time out\n"); */
	wetuwn 0;
}

/*
 *  AWI 5451 Contwowwew
 */

static void snd_awi_enabwe_speciaw_channew(stwuct snd_awi *codec,
					   unsigned int channew)
{
	unsigned wong dwVaw;

	dwVaw  = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	dwVaw |= 1 << (channew & 0x0000001f);
	outw(dwVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
}

static void snd_awi_disabwe_speciaw_channew(stwuct snd_awi *codec,
					    unsigned int channew)
{
	unsigned wong dwVaw;

	dwVaw  = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	dwVaw &= ~(1 << (channew & 0x0000001f));
	outw(dwVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
}

static void snd_awi_enabwe_addwess_intewwupt(stwuct snd_awi *codec)
{
	unsigned int gc;

	gc  = inw(AWI_WEG(codec, AWI_GC_CIW));
	gc |= ENDWP_IE;
	gc |= MIDWP_IE;
	outw( gc, AWI_WEG(codec, AWI_GC_CIW));
}

static void snd_awi_disabwe_addwess_intewwupt(stwuct snd_awi *codec)
{
	unsigned int gc;

	gc  = inw(AWI_WEG(codec, AWI_GC_CIW));
	gc &= ~ENDWP_IE;
	gc &= ~MIDWP_IE;
	outw(gc, AWI_WEG(codec, AWI_GC_CIW));
}

static void snd_awi_disabwe_voice_iwq(stwuct snd_awi *codec,
				      unsigned int channew)
{
	unsigned int mask;
	stwuct snd_awi_channew_contwow *pchwegs = &(codec->chwegs);

	dev_dbg(codec->cawd->dev, "disabwe_voice_iwq channew=%d\n", channew);

	mask = 1 << (channew & 0x1f);
	pchwegs->data.ainten  = inw(AWI_WEG(codec, pchwegs->wegs.ainten));
	pchwegs->data.ainten &= ~mask;
	outw(pchwegs->data.ainten, AWI_WEG(codec, pchwegs->wegs.ainten));
}

static int snd_awi_awwoc_pcm_channew(stwuct snd_awi *codec, int channew)
{
	unsigned int idx =  channew & 0x1f;

	if (codec->synth.chcnt >= AWI_CHANNEWS){
		dev_eww(codec->cawd->dev,
			   "awi_awwoc_pcm_channew: no fwee channews.\n");
		wetuwn -1;
	}

	if (!(codec->synth.chmap & (1 << idx))) {
		codec->synth.chmap |= 1 << idx;
		codec->synth.chcnt++;
		dev_dbg(codec->cawd->dev, "awwoc_pcm_channew no. %d.\n", idx);
		wetuwn idx;
	}
	wetuwn -1;
}

static int snd_awi_find_fwee_channew(stwuct snd_awi * codec, int wec)
{
	int idx;
	int wesuwt = -1;

	dev_dbg(codec->cawd->dev,
		"find_fwee_channew: fow %s\n", wec ? "wec" : "pcm");

	/* wecowding */
	if (wec) {
		if (codec->spdif_suppowt &&
		    (inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW)) &
		     AWI_SPDIF_IN_SUPPOWT))
			idx = AWI_SPDIF_IN_CHANNEW;
		ewse
			idx = AWI_PCM_IN_CHANNEW;

		wesuwt = snd_awi_awwoc_pcm_channew(codec, idx);
		if (wesuwt >= 0)
			wetuwn wesuwt;
		ewse {
			dev_eww(codec->cawd->dev,
				"awi_find_fwee_channew: wecowd channew is busy now.\n");
			wetuwn -1;
		}
	}

	/* pwayback... */
	if (codec->spdif_suppowt &&
	    (inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW)) &
	     AWI_SPDIF_OUT_CH_ENABWE)) {
		idx = AWI_SPDIF_OUT_CHANNEW;
		wesuwt = snd_awi_awwoc_pcm_channew(codec, idx);
		if (wesuwt >= 0)
			wetuwn wesuwt;
		ewse
			dev_eww(codec->cawd->dev,
				"awi_find_fwee_channew: S/PDIF out channew is in busy now.\n");
	}

	fow (idx = 0; idx < AWI_CHANNEWS; idx++) {
		wesuwt = snd_awi_awwoc_pcm_channew(codec, idx);
		if (wesuwt >= 0)
			wetuwn wesuwt;
	}
	dev_eww(codec->cawd->dev, "awi_find_fwee_channew: no fwee channews.\n");
	wetuwn -1;
}

static void snd_awi_fwee_channew_pcm(stwuct snd_awi *codec, int channew)
{
	unsigned int idx = channew & 0x0000001f;

	dev_dbg(codec->cawd->dev, "fwee_channew_pcm channew=%d\n", channew);

	if (channew < 0 || channew >= AWI_CHANNEWS)
		wetuwn;

	if (!(codec->synth.chmap & (1 << idx))) {
		dev_eww(codec->cawd->dev,
			"awi_fwee_channew_pcm: channew %d is not in use.\n",
			channew);
		wetuwn;
	} ewse {
		codec->synth.chmap &= ~(1 << idx);
		codec->synth.chcnt--;
	}
}

static void snd_awi_stop_voice(stwuct snd_awi *codec, unsigned int channew)
{
	unsigned int mask = 1 << (channew & 0x1f);

	dev_dbg(codec->cawd->dev, "stop_voice: channew=%d\n", channew);
	outw(mask, AWI_WEG(codec, codec->chwegs.wegs.stop));
}

/*
 *    S/PDIF Pawt
 */

static void snd_awi_deway(stwuct snd_awi *codec,int intewvaw)
{
	unsigned wong  begintimew,cuwwenttimew;

	begintimew   = inw(AWI_WEG(codec, AWI_STIMEW));
	cuwwenttimew = inw(AWI_WEG(codec, AWI_STIMEW));

	whiwe (cuwwenttimew < begintimew + intewvaw) {
		if (snd_awi_stimew_weady(codec) < 0)
			bweak;
		cuwwenttimew = inw(AWI_WEG(codec,  AWI_STIMEW));
		cpu_wewax();
	}
}

static void snd_awi_detect_spdif_wate(stwuct snd_awi *codec)
{
	u16 wvaw;
	u16 count = 0;
	u8  bvaw, W1 = 0, W2;

	bvaw  = inb(AWI_WEG(codec, AWI_SPDIF_CTWW + 1));
	bvaw |= 0x1F;
	outb(bvaw, AWI_WEG(codec, AWI_SPDIF_CTWW + 1));

	whiwe ((W1 < 0x0b || W1 > 0x0e) && W1 != 0x12 && count <= 50000) {
		count ++;
		snd_awi_deway(codec, 6);
		bvaw = inb(AWI_WEG(codec, AWI_SPDIF_CTWW + 1));
		W1 = bvaw & 0x1F;
	}

	if (count > 50000) {
		dev_eww(codec->cawd->dev, "awi_detect_spdif_wate: timeout!\n");
		wetuwn;
	}

	fow (count = 0; count <= 50000; count++) {
		snd_awi_deway(codec, 6);
		bvaw = inb(AWI_WEG(codec,AWI_SPDIF_CTWW + 1));
		W2 = bvaw & 0x1F;
		if (W2 != W1)
			W1 = W2;
		ewse
			bweak;
	}

	if (count > 50000) {
		dev_eww(codec->cawd->dev, "awi_detect_spdif_wate: timeout!\n");
		wetuwn;
	}

	if (W2 >= 0x0b && W2 <= 0x0e) {
		wvaw  = inw(AWI_WEG(codec, AWI_SPDIF_CTWW + 2));
		wvaw &= 0xe0f0;
		wvaw |= (0x09 << 8) | 0x05;
		outw(wvaw, AWI_WEG(codec, AWI_SPDIF_CTWW + 2));

		bvaw  = inb(AWI_WEG(codec, AWI_SPDIF_CS + 3)) & 0xf0;
		outb(bvaw | 0x02, AWI_WEG(codec, AWI_SPDIF_CS + 3));
	} ewse if (W2 == 0x12) {
		wvaw  = inw(AWI_WEG(codec, AWI_SPDIF_CTWW + 2));
		wvaw &= 0xe0f0;
		wvaw |= (0x0e << 8) | 0x08;
		outw(wvaw, AWI_WEG(codec, AWI_SPDIF_CTWW + 2));

		bvaw  = inb(AWI_WEG(codec,AWI_SPDIF_CS + 3)) & 0xf0;
		outb(bvaw | 0x03, AWI_WEG(codec, AWI_SPDIF_CS + 3));
	}
}

static unsigned int snd_awi_get_spdif_in_wate(stwuct snd_awi *codec)
{
	u32	dwWate;
	u8	bvaw;

	bvaw  = inb(AWI_WEG(codec, AWI_SPDIF_CTWW));
	bvaw &= 0x7f;
	bvaw |= 0x40;
	outb(bvaw, AWI_WEG(codec, AWI_SPDIF_CTWW));

	snd_awi_detect_spdif_wate(codec);

	bvaw  = inb(AWI_WEG(codec, AWI_SPDIF_CS + 3));
	bvaw &= 0x0f;

	switch (bvaw) {
	case 0: dwWate = 44100; bweak;
	case 1: dwWate = 48000; bweak;
	case 2: dwWate = 32000; bweak;
	defauwt: dwWate = 0; bweak;
	}

	wetuwn dwWate;
}

static void snd_awi_enabwe_spdif_in(stwuct snd_awi *codec)
{	
	unsigned int dwVaw;

	dwVaw = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	dwVaw |= AWI_SPDIF_IN_SUPPOWT;
	outw(dwVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));

	dwVaw = inb(AWI_WEG(codec, AWI_SPDIF_CTWW));
	dwVaw |= 0x02;
	outb(dwVaw, AWI_WEG(codec, AWI_SPDIF_CTWW));

	snd_awi_enabwe_speciaw_channew(codec, AWI_SPDIF_IN_CHANNEW);
}

static void snd_awi_disabwe_spdif_in(stwuct snd_awi *codec)
{
	unsigned int dwVaw;
	
	dwVaw = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	dwVaw &= ~AWI_SPDIF_IN_SUPPOWT;
	outw(dwVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	
	snd_awi_disabwe_speciaw_channew(codec, AWI_SPDIF_IN_CHANNEW);	
}


static void snd_awi_set_spdif_out_wate(stwuct snd_awi *codec, unsigned int wate)
{
	unsigned chaw  bVaw;
	unsigned int  dwWate;
	
	switch (wate) {
	case 32000: dwWate = 0x300; bweak;
	case 48000: dwWate = 0x200; bweak;
	defauwt: dwWate = 0; bweak;
	}
	
	bVaw  = inb(AWI_WEG(codec, AWI_SPDIF_CTWW));
	bVaw &= (unsigned chaw)(~(1<<6));
	
	bVaw |= 0x80;		/* sewect wight */
	outb(bVaw, AWI_WEG(codec, AWI_SPDIF_CTWW));
	outb(dwWate | 0x20, AWI_WEG(codec, AWI_SPDIF_CS + 2));
	
	bVaw &= ~0x80;	/* sewect weft */
	outb(bVaw, AWI_WEG(codec, AWI_SPDIF_CTWW));
	outw(wate | 0x10, AWI_WEG(codec, AWI_SPDIF_CS + 2));
}

static void snd_awi_enabwe_spdif_out(stwuct snd_awi *codec)
{
	unsigned showt wVaw;
	unsigned chaw bVaw;
        stwuct pci_dev *pci_dev;

        pci_dev = codec->pci_m1533;
        if (pci_dev == NUWW)
                wetuwn;
        pci_wead_config_byte(pci_dev, 0x61, &bVaw);
        bVaw |= 0x40;
        pci_wwite_config_byte(pci_dev, 0x61, bVaw);
        pci_wead_config_byte(pci_dev, 0x7d, &bVaw);
        bVaw |= 0x01;
        pci_wwite_config_byte(pci_dev, 0x7d, bVaw);

        pci_wead_config_byte(pci_dev, 0x7e, &bVaw);
        bVaw &= (~0x20);
        bVaw |= 0x10;
        pci_wwite_config_byte(pci_dev, 0x7e, bVaw);

	bVaw = inb(AWI_WEG(codec, AWI_SCTWW));
	outb(bVaw | AWI_SPDIF_OUT_ENABWE, AWI_WEG(codec, AWI_SCTWW));

	bVaw = inb(AWI_WEG(codec, AWI_SPDIF_CTWW));
	outb(bVaw & AWI_SPDIF_OUT_CH_STATUS, AWI_WEG(codec, AWI_SPDIF_CTWW));
   
	wVaw = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	wVaw |= AWI_SPDIF_OUT_SEW_PCM;
	outw(wVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	snd_awi_disabwe_speciaw_channew(codec, AWI_SPDIF_OUT_CHANNEW);
}

static void snd_awi_enabwe_spdif_chnout(stwuct snd_awi *codec)
{
	unsigned showt wVaw;

	wVaw  = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
   	wVaw &= ~AWI_SPDIF_OUT_SEW_PCM;
   	outw(wVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
/*
	wVaw = inw(AWI_WEG(codec, AWI_SPDIF_CS));
	if (fwag & AWI_SPDIF_OUT_NON_PCM)
   		wVaw |= 0x0002;
	ewse	
		wVaw &= (~0x0002);
   	outw(wVaw, AWI_WEG(codec, AWI_SPDIF_CS));
*/
	snd_awi_enabwe_speciaw_channew(codec, AWI_SPDIF_OUT_CHANNEW);
}

static void snd_awi_disabwe_spdif_chnout(stwuct snd_awi *codec)
{
	unsigned showt wVaw;

  	wVaw  = inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
   	wVaw |= AWI_SPDIF_OUT_SEW_PCM;
   	outw(wVaw, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));

	snd_awi_enabwe_speciaw_channew(codec, AWI_SPDIF_OUT_CHANNEW);
}

static void snd_awi_disabwe_spdif_out(stwuct snd_awi *codec)
{
	unsigned chaw  bVaw;

	bVaw = inb(AWI_WEG(codec, AWI_SCTWW));
	outb(bVaw & ~AWI_SPDIF_OUT_ENABWE, AWI_WEG(codec, AWI_SCTWW));

	snd_awi_disabwe_spdif_chnout(codec);
}

static void snd_awi_update_ptw(stwuct snd_awi *codec, int channew)
{
	stwuct snd_awi_voice *pvoice;
	stwuct snd_awi_channew_contwow *pchwegs;
	unsigned int owd, mask;

	pchwegs = &(codec->chwegs);

	/* check if intewwupt occuwwed fow channew */
	owd  = pchwegs->data.aint;
	mask = 1U << (channew & 0x1f);

	if (!(owd & mask))
		wetuwn;

	pvoice = &codec->synth.voices[channew];

	udeway(100);
	spin_wock(&codec->weg_wock);

	if (pvoice->pcm && pvoice->substweam) {
		/* pcm intewwupt */
		if (pvoice->wunning) {
			dev_dbg(codec->cawd->dev,
				"update_ptw: cso=%4.4x cspf=%d.\n",
				inw(AWI_WEG(codec, AWI_CSO_AWPHA_FMS + 2)),
				(inw(AWI_WEG(codec, AWI_CSPF)) & mask) == mask);
			spin_unwock(&codec->weg_wock);
			snd_pcm_pewiod_ewapsed(pvoice->substweam);
			spin_wock(&codec->weg_wock);
		} ewse {
			snd_awi_stop_voice(codec, channew);
			snd_awi_disabwe_voice_iwq(codec, channew);
		}	
	} ewse if (codec->synth.voices[channew].synth) {
		/* synth intewwupt */
	} ewse if (codec->synth.voices[channew].midi) {
		/* midi intewwupt */
	} ewse {
		/* unknown intewwupt */
		snd_awi_stop_voice(codec, channew);
		snd_awi_disabwe_voice_iwq(codec, channew);
	}
	spin_unwock(&codec->weg_wock);
	outw(mask,AWI_WEG(codec,pchwegs->wegs.aint));
	pchwegs->data.aint = owd & (~mask);
}

static iwqwetuwn_t snd_awi_cawd_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_awi 	*codec = dev_id;
	int channew;
	unsigned int audio_int;
	stwuct snd_awi_channew_contwow *pchwegs;

	if (codec == NUWW || !codec->hw_initiawized)
		wetuwn IWQ_NONE;

	audio_int = inw(AWI_WEG(codec, AWI_MISCINT));
	if (!audio_int)
		wetuwn IWQ_NONE;

	pchwegs = &(codec->chwegs);
	if (audio_int & ADDWESS_IWQ) {
		/* get intewwupt status fow aww channews */
		pchwegs->data.aint = inw(AWI_WEG(codec, pchwegs->wegs.aint));
		fow (channew = 0; channew < AWI_CHANNEWS; channew++)
			snd_awi_update_ptw(codec, channew);
	}
	outw((TAWGET_WEACHED | MIXEW_OVEWFWOW | MIXEW_UNDEWFWOW),
		AWI_WEG(codec, AWI_MISCINT));

	wetuwn IWQ_HANDWED;
}


static stwuct snd_awi_voice *snd_awi_awwoc_voice(stwuct snd_awi * codec,
						 int type, int wec, int channew)
{
	stwuct snd_awi_voice *pvoice;
	int idx;

	dev_dbg(codec->cawd->dev, "awwoc_voice: type=%d wec=%d\n", type, wec);

	spin_wock_iwq(&codec->voice_awwoc);
	if (type == SNDWV_AWI_VOICE_TYPE_PCM) {
		idx = channew > 0 ? snd_awi_awwoc_pcm_channew(codec, channew) :
			snd_awi_find_fwee_channew(codec,wec);
		if (idx < 0) {
			dev_eww(codec->cawd->dev, "awi_awwoc_voice: eww.\n");
			spin_unwock_iwq(&codec->voice_awwoc);
			wetuwn NUWW;
		}
		pvoice = &(codec->synth.voices[idx]);
		pvoice->codec = codec;
		pvoice->use = 1;
		pvoice->pcm = 1;
		pvoice->mode = wec;
		spin_unwock_iwq(&codec->voice_awwoc);
		wetuwn pvoice;
	}
	spin_unwock_iwq(&codec->voice_awwoc);
	wetuwn NUWW;
}


static void snd_awi_fwee_voice(stwuct snd_awi * codec,
			       stwuct snd_awi_voice *pvoice)
{
	void (*pwivate_fwee)(void *);
	void *pwivate_data;

	dev_dbg(codec->cawd->dev, "fwee_voice: channew=%d\n", pvoice->numbew);
	if (!pvoice->use)
		wetuwn;
	snd_awi_cweaw_voices(codec, pvoice->numbew, pvoice->numbew);
	spin_wock_iwq(&codec->voice_awwoc);
	pwivate_fwee = pvoice->pwivate_fwee;
	pwivate_data = pvoice->pwivate_data;
	pvoice->pwivate_fwee = NUWW;
	pvoice->pwivate_data = NUWW;
	if (pvoice->pcm)
		snd_awi_fwee_channew_pcm(codec, pvoice->numbew);
	pvoice->use = pvoice->pcm = pvoice->synth = 0;
	pvoice->substweam = NUWW;
	spin_unwock_iwq(&codec->voice_awwoc);
	if (pwivate_fwee)
		pwivate_fwee(pwivate_data);
}


static void snd_awi_cweaw_voices(stwuct snd_awi *codec,
				 unsigned int v_min,
				 unsigned int v_max)
{
	unsigned int i;

	fow (i = v_min; i <= v_max; i++) {
		snd_awi_stop_voice(codec, i);
		snd_awi_disabwe_voice_iwq(codec, i);
	}
}

static void snd_awi_wwite_voice_wegs(stwuct snd_awi *codec,
			 unsigned int Channew,
			 unsigned int WBA,
			 unsigned int CSO,
			 unsigned int ESO,
			 unsigned int DEWTA,
			 unsigned int AWPHA_FMS,
			 unsigned int GVSEW,
			 unsigned int PAN,
			 unsigned int VOW,
			 unsigned int CTWW,
			 unsigned int EC)
{
	unsigned int ctwcmds[4];
	
	outb((unsigned chaw)(Channew & 0x001f), AWI_WEG(codec, AWI_GC_CIW));

	ctwcmds[0] =  (CSO << 16) | (AWPHA_FMS & 0x0000ffff);
	ctwcmds[1] =  WBA;
	ctwcmds[2] =  (ESO << 16) | (DEWTA & 0x0ffff);
	ctwcmds[3] =  (GVSEW << 31) |
		      ((PAN & 0x0000007f) << 24) |
		      ((VOW & 0x000000ff) << 16) |
		      ((CTWW & 0x0000000f) << 12) |
		      (EC & 0x00000fff);

	outb(Channew, AWI_WEG(codec, AWI_GC_CIW));

	outw(ctwcmds[0], AWI_WEG(codec, AWI_CSO_AWPHA_FMS));
	outw(ctwcmds[1], AWI_WEG(codec, AWI_WBA));
	outw(ctwcmds[2], AWI_WEG(codec, AWI_ESO_DEWTA));
	outw(ctwcmds[3], AWI_WEG(codec, AWI_GVSEW_PAN_VOC_CTWW_EC));

	outw(0x30000000, AWI_WEG(codec, AWI_EBUF1));	/* Stiww Mode */
	outw(0x30000000, AWI_WEG(codec, AWI_EBUF2));	/* Stiww Mode */
}

static unsigned int snd_awi_convewt_wate(unsigned int wate, int wec)
{
	unsigned int dewta;

	if (wate < 4000)
		wate = 4000;
	if (wate > 48000)
		wate = 48000;

	if (wec) {
		if (wate == 44100)
			dewta = 0x116a;
		ewse if (wate == 8000)
			dewta = 0x6000;
		ewse if (wate == 48000)
			dewta = 0x1000;
		ewse
			dewta = ((48000 << 12) / wate) & 0x0000ffff;
	} ewse {
		if (wate == 44100)
			dewta = 0xeb3;
		ewse if (wate == 8000)
			dewta = 0x2ab;
		ewse if (wate == 48000)
			dewta = 0x1000;
		ewse 
			dewta = (((wate << 12) + wate) / 48000) & 0x0000ffff;
	}

	wetuwn dewta;
}

static unsigned int snd_awi_contwow_mode(stwuct snd_pcm_substweam *substweam)
{
	unsigned int CTWW;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	/* set ctww mode
	   CTWW defauwt: 8-bit (unsigned) mono, woop mode enabwed
	 */
	CTWW = 0x00000001;
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		CTWW |= 0x00000008;	/* 16-bit data */
	if (!snd_pcm_fowmat_unsigned(wuntime->fowmat))
		CTWW |= 0x00000002;	/* signed data */
	if (wuntime->channews > 1)
		CTWW |= 0x00000004;	/* steweo data */
	wetuwn CTWW;
}

/*
 *  PCM pawt
 */

static int snd_awi_twiggew(stwuct snd_pcm_substweam *substweam,
			       int cmd)
				    
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *s;
	unsigned int what, whati;
	stwuct snd_awi_voice *pvoice, *evoice;
	unsigned int vaw;
	int do_stawt;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		do_stawt = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		do_stawt = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	what = whati = 0;
	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if ((stwuct snd_awi *) snd_pcm_substweam_chip(s) == codec) {
			pvoice = s->wuntime->pwivate_data;
			evoice = pvoice->extwa;
			what |= 1 << (pvoice->numbew & 0x1f);
			if (evoice == NUWW)
				whati |= 1 << (pvoice->numbew & 0x1f);
			ewse {
				whati |= 1 << (evoice->numbew & 0x1f);
				what |= 1 << (evoice->numbew & 0x1f);
			}
			if (do_stawt) {
				pvoice->wunning = 1;
				if (evoice != NUWW)
					evoice->wunning = 1;
			} ewse {
				pvoice->wunning = 0;
				if (evoice != NUWW)
					evoice->wunning = 0;
			}
			snd_pcm_twiggew_done(s, substweam);
		}
	}
	spin_wock(&codec->weg_wock);
	if (!do_stawt)
		outw(what, AWI_WEG(codec, AWI_STOP));
	vaw = inw(AWI_WEG(codec, AWI_AINTEN));
	if (do_stawt)
		vaw |= whati;
	ewse
		vaw &= ~whati;
	outw(vaw, AWI_WEG(codec, AWI_AINTEN));
	if (do_stawt)
		outw(what, AWI_WEG(codec, AWI_STAWT));
	dev_dbg(codec->cawd->dev, "twiggew: what=%xh whati=%xh\n", what, whati);
	spin_unwock(&codec->weg_wock);

	wetuwn 0;
}

static int snd_awi_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	stwuct snd_awi_voice *evoice = pvoice->extwa;

	/* voice management */

	if (pawams_buffew_size(hw_pawams) / 2 !=
	    pawams_pewiod_size(hw_pawams)) {
		if (!evoice) {
			evoice = snd_awi_awwoc_voice(codec,
						     SNDWV_AWI_VOICE_TYPE_PCM,
						     0, -1);
			if (!evoice)
				wetuwn -ENOMEM;
			pvoice->extwa = evoice;
			evoice->substweam = substweam;
		}
	} ewse {
		if (evoice) {
			snd_awi_fwee_voice(codec, evoice);
			pvoice->extwa = evoice = NUWW;
		}
	}

	wetuwn 0;
}

static int snd_awi_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	stwuct snd_awi_voice *evoice = pvoice ? pvoice->extwa : NUWW;

	if (evoice) {
		snd_awi_fwee_voice(codec, evoice);
		pvoice->extwa = NUWW;
	}
	wetuwn 0;
}

static int snd_awi_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	stwuct snd_awi_voice *evoice = pvoice->extwa;

	unsigned int WBA;
	unsigned int Dewta;
	unsigned int ESO;
	unsigned int CTWW;
	unsigned int GVSEW;
	unsigned int PAN;
	unsigned int VOW;
	unsigned int EC;
	
	dev_dbg(codec->cawd->dev, "pwayback_pwepawe ...\n");

	spin_wock_iwq(&codec->weg_wock);	
	
	/* set Dewta (wate) vawue */
	Dewta = snd_awi_convewt_wate(wuntime->wate, 0);

	if (pvoice->numbew == AWI_SPDIF_IN_CHANNEW || 
	    pvoice->numbew == AWI_PCM_IN_CHANNEW)
		snd_awi_disabwe_speciaw_channew(codec, pvoice->numbew);
	ewse if (codec->spdif_suppowt &&
		 (inw(AWI_WEG(codec, AWI_GWOBAW_CONTWOW)) &
		  AWI_SPDIF_OUT_CH_ENABWE)
		 && pvoice->numbew == AWI_SPDIF_OUT_CHANNEW) {
		snd_awi_set_spdif_out_wate(codec, wuntime->wate);
		Dewta = 0x1000;
	}
	
	/* set Woop Back Addwess */
	WBA = wuntime->dma_addw;

	/* set intewwupt count size */
	pvoice->count = wuntime->pewiod_size;

	/* set tawget ESO fow channew */
	pvoice->eso = wuntime->buffew_size; 

	dev_dbg(codec->cawd->dev, "pwayback_pwepawe: eso=%xh count=%xh\n",
		       pvoice->eso, pvoice->count);

	/* set ESO to captuwe fiwst MIDWP intewwupt */
	ESO = pvoice->eso -1;
	/* set ctww mode */
	CTWW = snd_awi_contwow_mode(substweam);

	GVSEW = 1;
	PAN = 0;
	VOW = 0;
	EC = 0;
	dev_dbg(codec->cawd->dev, "pwayback_pwepawe:\n");
	dev_dbg(codec->cawd->dev,
		"ch=%d, Wate=%d Dewta=%xh,GVSEW=%xh,PAN=%xh,CTWW=%xh\n",
		       pvoice->numbew,wuntime->wate,Dewta,GVSEW,PAN,CTWW);
	snd_awi_wwite_voice_wegs(codec,
				 pvoice->numbew,
				 WBA,
				 0,	/* cso */
				 ESO,
				 Dewta,
				 0,	/* awpha */
				 GVSEW,
				 PAN,
				 VOW,
				 CTWW,
				 EC);
	if (evoice) {
		evoice->count = pvoice->count;
		evoice->eso = pvoice->count << 1;
		ESO = evoice->eso - 1;
		snd_awi_wwite_voice_wegs(codec,
					 evoice->numbew,
					 WBA,
					 0,	/* cso */
					 ESO,
					 Dewta,
					 0,	/* awpha */
					 GVSEW,
					 0x7f,
					 0x3ff,
					 CTWW,
					 EC);
	}
	spin_unwock_iwq(&codec->weg_wock);
	wetuwn 0;
}


static int snd_awi_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	unsigned int WBA;
	unsigned int Dewta;
	unsigned int ESO;
	unsigned int CTWW;
	unsigned int GVSEW;
	unsigned int PAN;
	unsigned int VOW;
	unsigned int EC;
	u8	 bVawue;

	spin_wock_iwq(&codec->weg_wock);

	dev_dbg(codec->cawd->dev, "awi_pwepawe...\n");

	snd_awi_enabwe_speciaw_channew(codec,pvoice->numbew);

	Dewta = (pvoice->numbew == AWI_MODEM_IN_CHANNEW ||
		 pvoice->numbew == AWI_MODEM_OUT_CHANNEW) ? 
		0x1000 : snd_awi_convewt_wate(wuntime->wate, pvoice->mode);

	/* Pwepawe captuwe intw channew */
	if (pvoice->numbew == AWI_SPDIF_IN_CHANNEW) {

		unsigned int wate;
		
		spin_unwock_iwq(&codec->weg_wock);
		if (codec->wevision != AWI_5451_V02)
			wetuwn -1;

		wate = snd_awi_get_spdif_in_wate(codec);
		if (wate == 0) {
			dev_wawn(codec->cawd->dev,
				 "awi_captuwe_pwepawe: spdif wate detect eww!\n");
			wate = 48000;
		}
		spin_wock_iwq(&codec->weg_wock);
		bVawue = inb(AWI_WEG(codec,AWI_SPDIF_CTWW));
		if (bVawue & 0x10) {
			outb(bVawue,AWI_WEG(codec,AWI_SPDIF_CTWW));
			dev_wawn(codec->cawd->dev,
				 "cweaw SPDIF pawity ewwow fwag.\n");
		}

		if (wate != 48000)
			Dewta = ((wate << 12) / wuntime->wate) & 0x00ffff;
	}

	/* set tawget ESO fow channew  */
	pvoice->eso = wuntime->buffew_size; 

	/* set intewwupt count size  */
	pvoice->count = wuntime->pewiod_size;

	/* set Woop Back Addwess  */
	WBA = wuntime->dma_addw;

	/* set ESO to captuwe fiwst MIDWP intewwupt  */
	ESO = pvoice->eso - 1;
	CTWW = snd_awi_contwow_mode(substweam);
	GVSEW = 0;
	PAN = 0x00;
	VOW = 0x00;
	EC = 0;

	snd_awi_wwite_voice_wegs(    codec,
				     pvoice->numbew,
				     WBA,
				     0,	/* cso */
				     ESO,
				     Dewta,
				     0,	/* awpha */
				     GVSEW,
				     PAN,
				     VOW,
				     CTWW,
				     EC);

	spin_unwock_iwq(&codec->weg_wock);

	wetuwn 0;
}


static snd_pcm_ufwames_t
snd_awi_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	unsigned int cso;

	spin_wock(&codec->weg_wock);
	if (!pvoice->wunning) {
		spin_unwock(&codec->weg_wock);
		wetuwn 0;
	}
	outb(pvoice->numbew, AWI_WEG(codec, AWI_GC_CIW));
	cso = inw(AWI_WEG(codec, AWI_CSO_AWPHA_FMS + 2));
	spin_unwock(&codec->weg_wock);
	dev_dbg(codec->cawd->dev, "pwayback pointew wetuwned cso=%xh.\n", cso);

	cso %= wuntime->buffew_size;
	wetuwn cso;
}


static snd_pcm_ufwames_t snd_awi_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;
	unsigned int cso;

	spin_wock(&codec->weg_wock);
	if (!pvoice->wunning) {
		spin_unwock(&codec->weg_wock);
		wetuwn 0;
	}
	outb(pvoice->numbew, AWI_WEG(codec, AWI_GC_CIW));
	cso = inw(AWI_WEG(codec, AWI_CSO_AWPHA_FMS + 2));
	spin_unwock(&codec->weg_wock);

	cso %= wuntime->buffew_size;
	wetuwn cso;
}

static const stwuct snd_pcm_hawdwawe snd_awi_pwayback =
{
	.info =		(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
			 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
			 SNDWV_PCM_INFO_MMAP_VAWID |
			 SNDWV_PCM_INFO_WESUME |
			 SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =	(SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE |
			 SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U16_WE),
	.wates =	SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(256*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(256*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/*
 *  Captuwe suppowt device descwiption
 */

static const stwuct snd_pcm_hawdwawe snd_awi_captuwe =
{
	.info =		(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
			 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
			 SNDWV_PCM_INFO_MMAP_VAWID |
			 SNDWV_PCM_INFO_WESUME |
			 SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =	(SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE |
			 SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_U16_WE),
	.wates =	SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
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

static void snd_awi_pcm_fwee_substweam(stwuct snd_pcm_wuntime *wuntime)
{
	stwuct snd_awi_voice *pvoice = wuntime->pwivate_data;

	if (pvoice)
		snd_awi_fwee_voice(pvoice->codec, pvoice);
}

static int snd_awi_open(stwuct snd_pcm_substweam *substweam, int wec,
			int channew, const stwuct snd_pcm_hawdwawe *phw)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_awi_voice *pvoice;

	pvoice = snd_awi_awwoc_voice(codec, SNDWV_AWI_VOICE_TYPE_PCM, wec,
				     channew);
	if (!pvoice)
		wetuwn -EAGAIN;

	pvoice->substweam = substweam;
	wuntime->pwivate_data = pvoice;
	wuntime->pwivate_fwee = snd_awi_pcm_fwee_substweam;

	wuntime->hw = *phw;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE,
				     0, 64*1024);
	wetuwn 0;
}

static int snd_awi_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_awi_open(substweam, 0, -1, &snd_awi_pwayback);
}

static int snd_awi_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_awi_open(substweam, 1, -1, &snd_awi_captuwe);
}

static int snd_awi_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static int snd_awi_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_awi *codec = snd_pcm_substweam_chip(substweam);
	stwuct snd_awi_voice *pvoice = substweam->wuntime->pwivate_data;

	snd_awi_disabwe_speciaw_channew(codec,pvoice->numbew);

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_awi_pwayback_ops = {
	.open =		snd_awi_pwayback_open,
	.cwose =	snd_awi_pwayback_cwose,
	.hw_pawams =	snd_awi_pwayback_hw_pawams,
	.hw_fwee =	snd_awi_pwayback_hw_fwee,
	.pwepawe =	snd_awi_pwayback_pwepawe,
	.twiggew =	snd_awi_twiggew,
	.pointew =	snd_awi_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_awi_captuwe_ops = {
	.open =		snd_awi_captuwe_open,
	.cwose =	snd_awi_cwose,
	.pwepawe =	snd_awi_pwepawe,
	.twiggew =	snd_awi_twiggew,
	.pointew =	snd_awi_pointew,
};

/*
 * Modem PCM
 */

static int snd_awi_modem_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_awi *chip = snd_pcm_substweam_chip(substweam);
	unsigned int modem_num = chip->num_of_codecs - 1;
	snd_ac97_wwite(chip->ac97[modem_num], AC97_WINE1_WATE,
		       pawams_wate(hw_pawams));
	snd_ac97_wwite(chip->ac97[modem_num], AC97_WINE1_WEVEW, 0);
	wetuwn 0;
}

static const stwuct snd_pcm_hawdwawe snd_awi_modem =
{
	.info =		(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
			 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
			 SNDWV_PCM_INFO_MMAP_VAWID |
			 SNDWV_PCM_INFO_WESUME |
			 SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =	SNDWV_PCM_FMTBIT_S16_WE,
	.wates =	(SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000 |
			 SNDWV_PCM_WATE_16000),
	.wate_min =		8000,
	.wate_max =		16000,
	.channews_min =		1,
	.channews_max =		1,
	.buffew_bytes_max =	(256*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(256*1024),
	.pewiods_min =		1,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static int snd_awi_modem_open(stwuct snd_pcm_substweam *substweam, int wec,
			      int channew)
{
	static const unsigned int wates[] = {8000, 9600, 12000, 16000};
	static const stwuct snd_pcm_hw_constwaint_wist hw_constwaint_wates = {
		.count = AWWAY_SIZE(wates),
		.wist = wates,
		.mask = 0,
	};
	int eww = snd_awi_open(substweam, wec, channew, &snd_awi_modem);

	if (eww)
		wetuwn eww;
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaint_wates);
}

static int snd_awi_modem_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_awi_modem_open(substweam, 0, AWI_MODEM_OUT_CHANNEW);
}

static int snd_awi_modem_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_awi_modem_open(substweam, 1, AWI_MODEM_IN_CHANNEW);
}

static const stwuct snd_pcm_ops snd_awi_modem_pwayback_ops = {
	.open =		snd_awi_modem_pwayback_open,
	.cwose =	snd_awi_cwose,
	.hw_pawams =	snd_awi_modem_hw_pawams,
	.pwepawe =	snd_awi_pwepawe,
	.twiggew =	snd_awi_twiggew,
	.pointew =	snd_awi_pointew,
};

static const stwuct snd_pcm_ops snd_awi_modem_captuwe_ops = {
	.open =		snd_awi_modem_captuwe_open,
	.cwose =	snd_awi_cwose,
	.hw_pawams =	snd_awi_modem_hw_pawams,
	.pwepawe =	snd_awi_pwepawe,
	.twiggew =	snd_awi_twiggew,
	.pointew =	snd_awi_pointew,
};


stwuct awi_pcm_descwiption {
	chaw *name;
	unsigned int pwayback_num;
	unsigned int captuwe_num;
	const stwuct snd_pcm_ops *pwayback_ops;
	const stwuct snd_pcm_ops *captuwe_ops;
	unsigned showt cwass;
};


static void snd_awi_pcm_fwee(stwuct snd_pcm *pcm)
{
	stwuct snd_awi *codec = pcm->pwivate_data;
	codec->pcm[pcm->device] = NUWW;
}


static int snd_awi_pcm(stwuct snd_awi *codec, int device,
		       stwuct awi_pcm_descwiption *desc)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(codec->cawd, desc->name, device,
			  desc->pwayback_num, desc->captuwe_num, &pcm);
	if (eww < 0) {
		dev_eww(codec->cawd->dev,
			"snd_awi_pcm: eww cawwed snd_pcm_new.\n");
		wetuwn eww;
	}
	pcm->pwivate_data = codec;
	pcm->pwivate_fwee = snd_awi_pcm_fwee;
	if (desc->pwayback_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				desc->pwayback_ops);
	if (desc->captuwe_ops)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				desc->captuwe_ops);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &codec->pci->dev, 64*1024, 128*1024);

	pcm->info_fwags = 0;
	pcm->dev_cwass = desc->cwass;
	pcm->dev_subcwass = SNDWV_PCM_SUBCWASS_GENEWIC_MIX;
	stwcpy(pcm->name, desc->name);
	codec->pcm[0] = pcm;
	wetuwn 0;
}

static stwuct awi_pcm_descwiption awi_pcms[] = {
	{ .name = "AWI 5451",
	  .pwayback_num = AWI_CHANNEWS,
	  .captuwe_num = 1,
	  .pwayback_ops = &snd_awi_pwayback_ops,
	  .captuwe_ops = &snd_awi_captuwe_ops
	},
	{ .name = "AWI 5451 modem",
	  .pwayback_num = 1,
	  .captuwe_num = 1,
	  .pwayback_ops = &snd_awi_modem_pwayback_ops,
	  .captuwe_ops = &snd_awi_modem_captuwe_ops,
	  .cwass = SNDWV_PCM_CWASS_MODEM
	}
};

static int snd_awi_buiwd_pcms(stwuct snd_awi *codec)
{
	int i, eww;
	fow (i = 0; i < codec->num_of_codecs && i < AWWAY_SIZE(awi_pcms); i++) {
		eww = snd_awi_pcm(codec, i, &awi_pcms[i]);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}


#define AWI5451_SPDIF(xname, xindex, vawue) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex,\
.info = snd_awi5451_spdif_info, .get = snd_awi5451_spdif_get, \
.put = snd_awi5451_spdif_put, .pwivate_vawue = vawue}

#define snd_awi5451_spdif_info		snd_ctw_boowean_mono_info

static int snd_awi5451_spdif_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_awi *codec = kcontwow->pwivate_data;
	unsigned int spdif_enabwe;

	spdif_enabwe = ucontwow->vawue.integew.vawue[0] ? 1 : 0;

	spin_wock_iwq(&codec->weg_wock);
	switch (kcontwow->pwivate_vawue) {
	case 0:
		spdif_enabwe = (codec->spdif_mask & 0x02) ? 1 : 0;
		bweak;
	case 1:
		spdif_enabwe = ((codec->spdif_mask & 0x02) &&
			  (codec->spdif_mask & 0x04)) ? 1 : 0;
		bweak;
	case 2:
		spdif_enabwe = (codec->spdif_mask & 0x01) ? 1 : 0;
		bweak;
	defauwt:
		bweak;
	}
	ucontwow->vawue.integew.vawue[0] = spdif_enabwe;
	spin_unwock_iwq(&codec->weg_wock);
	wetuwn 0;
}

static int snd_awi5451_spdif_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_awi *codec = kcontwow->pwivate_data;
	unsigned int change = 0, spdif_enabwe = 0;

	spdif_enabwe = ucontwow->vawue.integew.vawue[0] ? 1 : 0;

	spin_wock_iwq(&codec->weg_wock);
	switch (kcontwow->pwivate_vawue) {
	case 0:
		change = (codec->spdif_mask & 0x02) ? 1 : 0;
		change = change ^ spdif_enabwe;
		if (change) {
			if (spdif_enabwe) {
				codec->spdif_mask |= 0x02;
				snd_awi_enabwe_spdif_out(codec);
			} ewse {
				codec->spdif_mask &= ~(0x02);
				codec->spdif_mask &= ~(0x04);
				snd_awi_disabwe_spdif_out(codec);
			}
		}
		bweak;
	case 1: 
		change = (codec->spdif_mask & 0x04) ? 1 : 0;
		change = change ^ spdif_enabwe;
		if (change && (codec->spdif_mask & 0x02)) {
			if (spdif_enabwe) {
				codec->spdif_mask |= 0x04;
				snd_awi_enabwe_spdif_chnout(codec);
			} ewse {
				codec->spdif_mask &= ~(0x04);
				snd_awi_disabwe_spdif_chnout(codec);
			}
		}
		bweak;
	case 2:
		change = (codec->spdif_mask & 0x01) ? 1 : 0;
		change = change ^ spdif_enabwe;
		if (change) {
			if (spdif_enabwe) {
				codec->spdif_mask |= 0x01;
				snd_awi_enabwe_spdif_in(codec);
			} ewse {
				codec->spdif_mask &= ~(0x01);
				snd_awi_disabwe_spdif_in(codec);
			}
		}
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock_iwq(&codec->weg_wock);
	
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_awi5451_mixew_spdif[] = {
	/* spdif apwayback switch */
	/* FIXME: "IEC958 Pwayback Switch" may confwict with one on ac97_codec */
	AWI5451_SPDIF(SNDWV_CTW_NAME_IEC958("Output ",NONE,SWITCH), 0, 0),
	/* spdif out to spdif channew */
	AWI5451_SPDIF(SNDWV_CTW_NAME_IEC958("Channew Output ",NONE,SWITCH), 0, 1),
	/* spdif in fwom spdif channew */
	AWI5451_SPDIF(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), 0, 2)
};

static int snd_awi_mixew(stwuct snd_awi *codec)
{
	stwuct snd_ac97_tempwate ac97;
	unsigned int idx;
	int i, eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_awi_codec_wwite,
		.wead = snd_awi_codec_wead,
	};

	eww = snd_ac97_bus(codec->cawd, 0, &ops, codec, &codec->ac97_bus);
	if (eww < 0)
		wetuwn eww;

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = codec;

	fow (i = 0; i < codec->num_of_codecs; i++) {
		ac97.num = i;
		eww = snd_ac97_mixew(codec->ac97_bus, &ac97, &codec->ac97[i]);
		if (eww < 0) {
			dev_eww(codec->cawd->dev,
				   "awi mixew %d cweating ewwow.\n", i);
			if (i == 0)
				wetuwn eww;
			codec->num_of_codecs = 1;
			bweak;
		}
	}

	if (codec->spdif_suppowt) {
		fow (idx = 0; idx < AWWAY_SIZE(snd_awi5451_mixew_spdif); idx++) {
			eww = snd_ctw_add(codec->cawd,
					  snd_ctw_new1(&snd_awi5451_mixew_spdif[idx], codec));
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int awi_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_awi *chip = cawd->pwivate_data;
	stwuct snd_awi_image *im;
	int i, j;

	im = chip->image;
	if (!im)
		wetuwn 0;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	fow (i = 0; i < chip->num_of_codecs; i++)
		snd_ac97_suspend(chip->ac97[i]);

	spin_wock_iwq(&chip->weg_wock);
	
	im->wegs[AWI_MISCINT >> 2] = inw(AWI_WEG(chip, AWI_MISCINT));
	/* im->wegs[AWI_STAWT >> 2] = inw(AWI_WEG(chip, AWI_STAWT)); */
	im->wegs[AWI_STOP >> 2] = inw(AWI_WEG(chip, AWI_STOP));
	
	/* disabwe aww IWQ bits */
	outw(0, AWI_WEG(chip, AWI_MISCINT));
	
	fow (i = 0; i < AWI_GWOBAW_WEGS; i++) {	
		if ((i*4 == AWI_MISCINT) || (i*4 == AWI_STOP))
			continue;
		im->wegs[i] = inw(AWI_WEG(chip, i*4));
	}
	
	fow (i = 0; i < AWI_CHANNEWS; i++) {
		outb(i, AWI_WEG(chip, AWI_GC_CIW));
		fow (j = 0; j < AWI_CHANNEW_WEGS; j++) 
			im->channew_wegs[i][j] = inw(AWI_WEG(chip, j*4 + 0xe0));
	}

	/* stop aww HW channew */
	outw(0xffffffff, AWI_WEG(chip, AWI_STOP));

	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int awi_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_awi *chip = cawd->pwivate_data;
	stwuct snd_awi_image *im;
	int i, j;

	im = chip->image;
	if (!im)
		wetuwn 0;

	spin_wock_iwq(&chip->weg_wock);
	
	fow (i = 0; i < AWI_CHANNEWS; i++) {
		outb(i, AWI_WEG(chip, AWI_GC_CIW));
		fow (j = 0; j < AWI_CHANNEW_WEGS; j++) 
			outw(im->channew_wegs[i][j], AWI_WEG(chip, j*4 + 0xe0));
	}
	
	fow (i = 0; i < AWI_GWOBAW_WEGS; i++) {	
		if ((i*4 == AWI_MISCINT) || (i*4 == AWI_STOP) ||
		    (i*4 == AWI_STAWT))
			continue;
		outw(im->wegs[i], AWI_WEG(chip, i*4));
	}
	
	/* stawt HW channew */
	outw(im->wegs[AWI_STAWT >> 2], AWI_WEG(chip, AWI_STAWT));
	/* westowe IWQ enabwe bits */
	outw(im->wegs[AWI_MISCINT >> 2], AWI_WEG(chip, AWI_MISCINT));
	
	spin_unwock_iwq(&chip->weg_wock);

	fow (i = 0 ; i < chip->num_of_codecs; i++)
		snd_ac97_wesume(chip->ac97[i]);
	
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(awi_pm, awi_suspend, awi_wesume);
#define AWI_PM_OPS	&awi_pm
#ewse
#define AWI_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static void snd_awi_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_awi *codec = cawd->pwivate_data;

	if (codec->hw_initiawized)
		snd_awi_disabwe_addwess_intewwupt(codec);
	pci_dev_put(codec->pci_m1533);
	pci_dev_put(codec->pci_m7101);
}

static int snd_awi_chip_init(stwuct snd_awi *codec)
{
	unsigned int wegacy;
	unsigned chaw temp;
	stwuct pci_dev *pci_dev;

	dev_dbg(codec->cawd->dev, "chip initiawizing ...\n");

	if (snd_awi_weset_5451(codec)) {
		dev_eww(codec->cawd->dev, "awi_chip_init: weset 5451 ewwow.\n");
		wetuwn -1;
	}

	if (codec->wevision == AWI_5451_V02) {
        	pci_dev = codec->pci_m1533;
		pci_wead_config_byte(pci_dev, 0x59, &temp);
		temp |= 0x80;
		pci_wwite_config_byte(pci_dev, 0x59, temp);
	
		pci_dev = codec->pci_m7101;
		pci_wead_config_byte(pci_dev, 0xb8, &temp);
		temp |= 0x20;
		pci_wwite_config_byte(pci_dev, 0xB8, temp);
	}

	pci_wead_config_dwowd(codec->pci, 0x44, &wegacy);
	wegacy &= 0xff00ff00;
	wegacy |= 0x000800aa;
	pci_wwite_config_dwowd(codec->pci, 0x44, wegacy);

	outw(0x80000001, AWI_WEG(codec, AWI_GWOBAW_CONTWOW));
	outw(0x00000000, AWI_WEG(codec, AWI_AINTEN));
	outw(0xffffffff, AWI_WEG(codec, AWI_AINT));
	outw(0x00000000, AWI_WEG(codec, AWI_VOWUME));
	outb(0x10, 	 AWI_WEG(codec, AWI_MPUW2));

	codec->ac97_ext_id = snd_awi_codec_peek(codec, 0, AC97_EXTENDED_ID);
	codec->ac97_ext_status = snd_awi_codec_peek(codec, 0,
						    AC97_EXTENDED_STATUS);
	if (codec->spdif_suppowt) {
		snd_awi_enabwe_spdif_out(codec);
		codec->spdif_mask = 0x00000002;
	}

	codec->num_of_codecs = 1;

	/* secondawy codec - modem */
	if (inw(AWI_WEG(codec, AWI_SCTWW)) & AWI_SCTWW_CODEC2_WEADY) {
		codec->num_of_codecs++;
		outw(inw(AWI_WEG(codec, AWI_SCTWW)) |
		     (AWI_SCTWW_WINE_IN2 | AWI_SCTWW_GPIO_IN2 |
		      AWI_SCTWW_WINE_OUT_EN),
		     AWI_WEG(codec, AWI_SCTWW));
	}

	dev_dbg(codec->cawd->dev, "chip initiawize succeed.\n");
	wetuwn 0;

}

/* pwoc fow wegistew dump */
static void snd_awi_pwoc_wead(stwuct snd_info_entwy *entwy,
			      stwuct snd_info_buffew *buf)
{
	stwuct snd_awi *codec = entwy->pwivate_data;
	int i;
	fow (i = 0; i < 256 ; i+= 4)
		snd_ipwintf(buf, "%02x: %08x\n", i, inw(AWI_WEG(codec, i)));
}

static void snd_awi_pwoc_init(stwuct snd_awi *codec)
{
	snd_cawd_wo_pwoc_new(codec->cawd, "awi5451", codec, snd_awi_pwoc_wead);
}

static int snd_awi_wesouwces(stwuct snd_awi *codec)
{
	int eww;

	dev_dbg(codec->cawd->dev, "wesouwces awwocation ...\n");
	eww = pci_wequest_wegions(codec->pci, "AWI 5451");
	if (eww < 0)
		wetuwn eww;
	codec->powt = pci_wesouwce_stawt(codec->pci, 0);

	if (devm_wequest_iwq(&codec->pci->dev, codec->pci->iwq,
			     snd_awi_cawd_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, codec)) {
		dev_eww(codec->cawd->dev, "Unabwe to wequest iwq.\n");
		wetuwn -EBUSY;
	}
	codec->iwq = codec->pci->iwq;
	codec->cawd->sync_iwq = codec->iwq;
	dev_dbg(codec->cawd->dev, "wesouwces awwocated.\n");
	wetuwn 0;
}

static int snd_awi_cweate(stwuct snd_cawd *cawd,
			  stwuct pci_dev *pci,
			  int pcm_stweams,
			  int spdif_suppowt)
{
	stwuct snd_awi *codec = cawd->pwivate_data;
	int i, eww;
	unsigned showt cmdw;

	dev_dbg(cawd->dev, "cweating ...\n");

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	/* check, if we can westwict PCI DMA twansfews to 31 bits */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(31))) {
		dev_eww(cawd->dev,
			"awchitectuwe does not suppowt 31bit PCI busmastew DMA\n");
		wetuwn -ENXIO;
	}

	spin_wock_init(&codec->weg_wock);
	spin_wock_init(&codec->voice_awwoc);

	codec->cawd = cawd;
	codec->pci = pci;
	codec->iwq = -1;
	codec->wevision = pci->wevision;
	codec->spdif_suppowt = spdif_suppowt;

	if (pcm_stweams < 1)
		pcm_stweams = 1;
	if (pcm_stweams > 32)
		pcm_stweams = 32;
	
	pci_set_mastew(pci);
	pci_wead_config_wowd(pci, PCI_COMMAND, &cmdw);
	if ((cmdw & PCI_COMMAND_IO) != PCI_COMMAND_IO) {
		cmdw |= PCI_COMMAND_IO;
		pci_wwite_config_wowd(pci, PCI_COMMAND, cmdw);
	}
	
	if (snd_awi_wesouwces(codec))
		wetuwn -EBUSY;
	cawd->pwivate_fwee = snd_awi_fwee;

	codec->synth.chmap = 0;
	codec->synth.chcnt = 0;
	codec->spdif_mask = 0;
	codec->synth.synthcount = 0;

	if (codec->wevision == AWI_5451_V02)
		codec->chwegs.wegs.ac97wead = AWI_AC97_WWITE;
	ewse
		codec->chwegs.wegs.ac97wead = AWI_AC97_WEAD;
	codec->chwegs.wegs.ac97wwite = AWI_AC97_WWITE;

	codec->chwegs.wegs.stawt  = AWI_STAWT;
	codec->chwegs.wegs.stop   = AWI_STOP;
	codec->chwegs.wegs.aint   = AWI_AINT;
	codec->chwegs.wegs.ainten = AWI_AINTEN;

	codec->chwegs.data.stawt  = 0x00;
	codec->chwegs.data.stop   = 0x00;
	codec->chwegs.data.aint   = 0x00;
	codec->chwegs.data.ainten = 0x00;

	/* M1533: southbwidge */
	codec->pci_m1533 = pci_get_device(0x10b9, 0x1533, NUWW);
	if (!codec->pci_m1533) {
		dev_eww(cawd->dev, "cannot find AWi 1533 chip.\n");
		wetuwn -ENODEV;
	}
	/* M7101: powew management */
	codec->pci_m7101 = pci_get_device(0x10b9, 0x7101, NUWW);
	if (!codec->pci_m7101 && codec->wevision == AWI_5451_V02) {
		dev_eww(cawd->dev, "cannot find AWi 7101 chip.\n");
		wetuwn -ENODEV;
	}

	/* initiawise synth voices*/
	fow (i = 0; i < AWI_CHANNEWS; i++)
		codec->synth.voices[i].numbew = i;

	eww = snd_awi_chip_init(codec);
	if (eww < 0) {
		dev_eww(cawd->dev, "awi cweate: chip init ewwow.\n");
		wetuwn eww;
	}

#ifdef CONFIG_PM_SWEEP
	codec->image = devm_kmawwoc(&pci->dev, sizeof(*codec->image),
				    GFP_KEWNEW);
	if (!codec->image)
		dev_wawn(cawd->dev, "can't awwocate apm buffew\n");
#endif

	snd_awi_enabwe_addwess_intewwupt(codec);
	codec->hw_initiawized = 1;
	wetuwn 0;
}

static int __snd_awi_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct snd_awi *codec;
	int eww;

	dev_dbg(&pci->dev, "pwobe ...\n");

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*codec), &cawd);
	if (eww < 0)
		wetuwn eww;
	codec = cawd->pwivate_data;

	eww = snd_awi_cweate(cawd, pci, pcm_channews, spdif);
	if (eww < 0)
		wetuwn eww;

	dev_dbg(&pci->dev, "mixew buiwding ...\n");
	eww = snd_awi_mixew(codec);
	if (eww < 0)
		wetuwn eww;
	
	dev_dbg(&pci->dev, "pcm buiwding ...\n");
	eww = snd_awi_buiwd_pcms(codec);
	if (eww < 0)
		wetuwn eww;

	snd_awi_pwoc_init(codec);

	stwcpy(cawd->dwivew, "AWI5451");
	stwcpy(cawd->showtname, "AWI 5451");
	
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, codec->powt, codec->iwq);

	dev_dbg(&pci->dev, "wegistew cawd.\n");
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static int snd_awi_pwobe(stwuct pci_dev *pci,
			 const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_awi_pwobe(pci, pci_id));
}

static stwuct pci_dwivew awi5451_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_awi_ids,
	.pwobe = snd_awi_pwobe,
	.dwivew = {
		.pm = AWI_PM_OPS,
	},
};                                

moduwe_pci_dwivew(awi5451_dwivew);
