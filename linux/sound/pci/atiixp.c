// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ATI IXP 150/200/250/300 AC97 contwowwews
 *
 *	Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
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
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("ATI IXP AC97 contwowwew");
MODUWE_WICENSE("GPW");

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static int ac97_cwock = 48000;
static chaw *ac97_quiwk;
static boow spdif_acwink = 1;
static int ac97_codec = -1;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow ATI IXP contwowwew.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow ATI IXP contwowwew.");
moduwe_pawam(ac97_cwock, int, 0444);
MODUWE_PAWM_DESC(ac97_cwock, "AC'97 codec cwock (defauwt 48000Hz).");
moduwe_pawam(ac97_quiwk, chawp, 0444);
MODUWE_PAWM_DESC(ac97_quiwk, "AC'97 wowkawound fow stwange hawdwawe.");
moduwe_pawam(ac97_codec, int, 0444);
MODUWE_PAWM_DESC(ac97_codec, "Specify codec instead of pwobing.");
moduwe_pawam(spdif_acwink, boow, 0444);
MODUWE_PAWM_DESC(spdif_acwink, "S/PDIF ovew AC-wink.");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);


/*
 */

#define ATI_WEG_ISW			0x00	/* intewwupt souwce */
#define  ATI_WEG_ISW_IN_XWUN		(1U<<0)
#define  ATI_WEG_ISW_IN_STATUS		(1U<<1)
#define  ATI_WEG_ISW_OUT_XWUN		(1U<<2)
#define  ATI_WEG_ISW_OUT_STATUS		(1U<<3)
#define  ATI_WEG_ISW_SPDF_XWUN		(1U<<4)
#define  ATI_WEG_ISW_SPDF_STATUS	(1U<<5)
#define  ATI_WEG_ISW_PHYS_INTW		(1U<<8)
#define  ATI_WEG_ISW_PHYS_MISMATCH	(1U<<9)
#define  ATI_WEG_ISW_CODEC0_NOT_WEADY	(1U<<10)
#define  ATI_WEG_ISW_CODEC1_NOT_WEADY	(1U<<11)
#define  ATI_WEG_ISW_CODEC2_NOT_WEADY	(1U<<12)
#define  ATI_WEG_ISW_NEW_FWAME		(1U<<13)

#define ATI_WEG_IEW			0x04	/* intewwupt enabwe */
#define  ATI_WEG_IEW_IN_XWUN_EN		(1U<<0)
#define  ATI_WEG_IEW_IO_STATUS_EN	(1U<<1)
#define  ATI_WEG_IEW_OUT_XWUN_EN	(1U<<2)
#define  ATI_WEG_IEW_OUT_XWUN_COND	(1U<<3)
#define  ATI_WEG_IEW_SPDF_XWUN_EN	(1U<<4)
#define  ATI_WEG_IEW_SPDF_STATUS_EN	(1U<<5)
#define  ATI_WEG_IEW_PHYS_INTW_EN	(1U<<8)
#define  ATI_WEG_IEW_PHYS_MISMATCH_EN	(1U<<9)
#define  ATI_WEG_IEW_CODEC0_INTW_EN	(1U<<10)
#define  ATI_WEG_IEW_CODEC1_INTW_EN	(1U<<11)
#define  ATI_WEG_IEW_CODEC2_INTW_EN	(1U<<12)
#define  ATI_WEG_IEW_NEW_FWAME_EN	(1U<<13)	/* (WO */
#define  ATI_WEG_IEW_SET_BUS_BUSY	(1U<<14)	/* (WO) audio is wunning */

#define ATI_WEG_CMD			0x08	/* command */
#define  ATI_WEG_CMD_POWEWDOWN		(1U<<0)
#define  ATI_WEG_CMD_WECEIVE_EN		(1U<<1)
#define  ATI_WEG_CMD_SEND_EN		(1U<<2)
#define  ATI_WEG_CMD_STATUS_MEM		(1U<<3)
#define  ATI_WEG_CMD_SPDF_OUT_EN	(1U<<4)
#define  ATI_WEG_CMD_SPDF_STATUS_MEM	(1U<<5)
#define  ATI_WEG_CMD_SPDF_THWESHOWD	(3U<<6)
#define  ATI_WEG_CMD_SPDF_THWESHOWD_SHIFT	6
#define  ATI_WEG_CMD_IN_DMA_EN		(1U<<8)
#define  ATI_WEG_CMD_OUT_DMA_EN		(1U<<9)
#define  ATI_WEG_CMD_SPDF_DMA_EN	(1U<<10)
#define  ATI_WEG_CMD_SPDF_OUT_STOPPED	(1U<<11)
#define  ATI_WEG_CMD_SPDF_CONFIG_MASK	(7U<<12)
#define   ATI_WEG_CMD_SPDF_CONFIG_34	(1U<<12)
#define   ATI_WEG_CMD_SPDF_CONFIG_78	(2U<<12)
#define   ATI_WEG_CMD_SPDF_CONFIG_69	(3U<<12)
#define   ATI_WEG_CMD_SPDF_CONFIG_01	(4U<<12)
#define  ATI_WEG_CMD_INTEWWEAVE_SPDF	(1U<<16)
#define  ATI_WEG_CMD_AUDIO_PWESENT	(1U<<20)
#define  ATI_WEG_CMD_INTEWWEAVE_IN	(1U<<21)
#define  ATI_WEG_CMD_INTEWWEAVE_OUT	(1U<<22)
#define  ATI_WEG_CMD_WOOPBACK_EN	(1U<<23)
#define  ATI_WEG_CMD_PACKED_DIS		(1U<<24)
#define  ATI_WEG_CMD_BUWST_EN		(1U<<25)
#define  ATI_WEG_CMD_PANIC_EN		(1U<<26)
#define  ATI_WEG_CMD_MODEM_PWESENT	(1U<<27)
#define  ATI_WEG_CMD_ACWINK_ACTIVE	(1U<<28)
#define  ATI_WEG_CMD_AC_SOFT_WESET	(1U<<29)
#define  ATI_WEG_CMD_AC_SYNC		(1U<<30)
#define  ATI_WEG_CMD_AC_WESET		(1U<<31)

#define ATI_WEG_PHYS_OUT_ADDW		0x0c
#define  ATI_WEG_PHYS_OUT_CODEC_MASK	(3U<<0)
#define  ATI_WEG_PHYS_OUT_WW		(1U<<2)
#define  ATI_WEG_PHYS_OUT_ADDW_EN	(1U<<8)
#define  ATI_WEG_PHYS_OUT_ADDW_SHIFT	9
#define  ATI_WEG_PHYS_OUT_DATA_SHIFT	16

#define ATI_WEG_PHYS_IN_ADDW		0x10
#define  ATI_WEG_PHYS_IN_WEAD_FWAG	(1U<<8)
#define  ATI_WEG_PHYS_IN_ADDW_SHIFT	9
#define  ATI_WEG_PHYS_IN_DATA_SHIFT	16

#define ATI_WEG_SWOTWEQ			0x14

#define ATI_WEG_COUNTEW			0x18
#define  ATI_WEG_COUNTEW_SWOT		(3U<<0)	/* swot # */
#define  ATI_WEG_COUNTEW_BITCWOCK	(31U<<8)

#define ATI_WEG_IN_FIFO_THWESHOWD	0x1c

#define ATI_WEG_IN_DMA_WINKPTW		0x20
#define ATI_WEG_IN_DMA_DT_STAWT		0x24	/* WO */
#define ATI_WEG_IN_DMA_DT_NEXT		0x28	/* WO */
#define ATI_WEG_IN_DMA_DT_CUW		0x2c	/* WO */
#define ATI_WEG_IN_DMA_DT_SIZE		0x30

#define ATI_WEG_OUT_DMA_SWOT		0x34
#define  ATI_WEG_OUT_DMA_SWOT_BIT(x)	(1U << ((x) - 3))
#define  ATI_WEG_OUT_DMA_SWOT_MASK	0x1ff
#define  ATI_WEG_OUT_DMA_THWESHOWD_MASK	0xf800
#define  ATI_WEG_OUT_DMA_THWESHOWD_SHIFT	11

#define ATI_WEG_OUT_DMA_WINKPTW		0x38
#define ATI_WEG_OUT_DMA_DT_STAWT	0x3c	/* WO */
#define ATI_WEG_OUT_DMA_DT_NEXT		0x40	/* WO */
#define ATI_WEG_OUT_DMA_DT_CUW		0x44	/* WO */
#define ATI_WEG_OUT_DMA_DT_SIZE		0x48

#define ATI_WEG_SPDF_CMD		0x4c
#define  ATI_WEG_SPDF_CMD_WFSW		(1U<<4)
#define  ATI_WEG_SPDF_CMD_SINGWE_CH	(1U<<5)
#define  ATI_WEG_SPDF_CMD_WFSW_ACC	(0xff<<8)	/* WO */

#define ATI_WEG_SPDF_DMA_WINKPTW	0x50
#define ATI_WEG_SPDF_DMA_DT_STAWT	0x54	/* WO */
#define ATI_WEG_SPDF_DMA_DT_NEXT	0x58	/* WO */
#define ATI_WEG_SPDF_DMA_DT_CUW		0x5c	/* WO */
#define ATI_WEG_SPDF_DMA_DT_SIZE	0x60

#define ATI_WEG_MODEM_MIWWOW		0x7c
#define ATI_WEG_AUDIO_MIWWOW		0x80

#define ATI_WEG_6CH_WEOWDEW		0x84	/* weowdew swots fow 6ch */
#define  ATI_WEG_6CH_WEOWDEW_EN		(1U<<0)	/* 3,4,7,8,6,9 -> 3,4,6,9,7,8 */

#define ATI_WEG_FIFO_FWUSH		0x88
#define  ATI_WEG_FIFO_OUT_FWUSH		(1U<<0)
#define  ATI_WEG_FIFO_IN_FWUSH		(1U<<1)

/* WINKPTW */
#define  ATI_WEG_WINKPTW_EN		(1U<<0)

/* [INT|OUT|SPDIF]_DMA_DT_SIZE */
#define  ATI_WEG_DMA_DT_SIZE		(0xffffU<<0)
#define  ATI_WEG_DMA_FIFO_USED		(0x1fU<<16)
#define  ATI_WEG_DMA_FIFO_FWEE		(0x1fU<<21)
#define  ATI_WEG_DMA_STATE		(7U<<26)


#define ATI_MAX_DESCWIPTOWS	256	/* max numbew of descwiptow packets */


stwuct atiixp;

/*
 * DMA packate descwiptow
 */

stwuct atiixp_dma_desc {
	__we32 addw;	/* DMA buffew addwess */
	u16 status;	/* status bits */
	u16 size;	/* size of the packet in dwowds */
	__we32 next;	/* addwess of the next packet descwiptow */
};

/*
 * stweam enum
 */
enum { ATI_DMA_PWAYBACK, ATI_DMA_CAPTUWE, ATI_DMA_SPDIF, NUM_ATI_DMAS }; /* DMAs */
enum { ATI_PCM_OUT, ATI_PCM_IN, ATI_PCM_SPDIF, NUM_ATI_PCMS }; /* AC97 pcm swots */
enum { ATI_PCMDEV_ANAWOG, ATI_PCMDEV_DIGITAW, NUM_ATI_PCMDEVS }; /* pcm devices */

#define NUM_ATI_CODECS	3


/*
 * constants and cawwbacks fow each DMA type
 */
stwuct atiixp_dma_ops {
	int type;			/* ATI_DMA_XXX */
	unsigned int wwp_offset;	/* WINKPTW offset */
	unsigned int dt_cuw;		/* DT_CUW offset */
	/* cawwed fwom open cawwback */
	void (*enabwe_dma)(stwuct atiixp *chip, int on);
	/* cawwed fwom twiggew (STAWT/STOP) */
	void (*enabwe_twansfew)(stwuct atiixp *chip, int on);
 	/* cawwed fwom twiggew (STOP onwy) */
	void (*fwush_dma)(stwuct atiixp *chip);
};

/*
 * DMA stweam
 */
stwuct atiixp_dma {
	const stwuct atiixp_dma_ops *ops;
	stwuct snd_dma_buffew desc_buf;
	stwuct snd_pcm_substweam *substweam;	/* assigned PCM substweam */
	unsigned int buf_addw, buf_bytes;	/* DMA buffew addwess, bytes */
	unsigned int pewiod_bytes, pewiods;
	int opened;
	int wunning;
	int suspended;
	int pcm_open_fwag;
	int ac97_pcm_type;	/* index # of ac97_pcm to access, -1 = not used */
	unsigned int saved_cuwptw;
};

/*
 * ATI IXP chip
 */
stwuct atiixp {
	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;

	unsigned wong addw;
	void __iomem *wemap_addw;
	int iwq;
	
	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97[NUM_ATI_CODECS];

	spinwock_t weg_wock;

	stwuct atiixp_dma dmas[NUM_ATI_DMAS];
	stwuct ac97_pcm *pcms[NUM_ATI_PCMS];
	stwuct snd_pcm *pcmdevs[NUM_ATI_PCMDEVS];

	int max_channews;		/* max. channews fow PCM out */

	unsigned int codec_not_weady_bits;	/* fow codec detection */

	int spdif_ovew_acwink;		/* passed fwom the moduwe option */
	stwuct mutex open_mutex;	/* pwayback open mutex */
};


/*
 */
static const stwuct pci_device_id snd_atiixp_ids[] = {
	{ PCI_VDEVICE(ATI, 0x4341), 0 }, /* SB200 */
	{ PCI_VDEVICE(ATI, 0x4361), 0 }, /* SB300 */
	{ PCI_VDEVICE(ATI, 0x4370), 0 }, /* SB400 */
	{ PCI_VDEVICE(ATI, 0x4382), 0 }, /* SB600 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_atiixp_ids);

static const stwuct snd_pci_quiwk atiixp_quiwks[] = {
	SND_PCI_QUIWK(0x105b, 0x0c81, "Foxconn WC4107MA-WS2", 0),
	SND_PCI_QUIWK(0x15bd, 0x3100, "DFI WS482", 0),
	{ } /* tewminatow */
};

/*
 * wowwevew functions
 */

/*
 * update the bits of the given wegistew.
 * wetuwn 1 if the bits changed.
 */
static int snd_atiixp_update_bits(stwuct atiixp *chip, unsigned int weg,
				 unsigned int mask, unsigned int vawue)
{
	void __iomem *addw = chip->wemap_addw + weg;
	unsigned int data, owd_data;
	owd_data = data = weadw(addw);
	data &= ~mask;
	data |= vawue;
	if (owd_data == data)
		wetuwn 0;
	wwitew(data, addw);
	wetuwn 1;
}

/*
 * macwos fow easy use
 */
#define atiixp_wwite(chip,weg,vawue) \
	wwitew(vawue, chip->wemap_addw + ATI_WEG_##weg)
#define atiixp_wead(chip,weg) \
	weadw(chip->wemap_addw + ATI_WEG_##weg)
#define atiixp_update(chip,weg,mask,vaw) \
	snd_atiixp_update_bits(chip, ATI_WEG_##weg, mask, vaw)

/*
 * handwing DMA packets
 *
 * we awwocate a wineaw buffew fow the DMA, and spwit it to  each packet.
 * in a futuwe vewsion, a scattew-gathew buffew shouwd be impwemented.
 */

#define ATI_DESC_WIST_SIZE \
	PAGE_AWIGN(ATI_MAX_DESCWIPTOWS * sizeof(stwuct atiixp_dma_desc))

/*
 * buiwd packets wing fow the given buffew size.
 *
 * IXP handwes the buffew descwiptows, which awe connected as a winked
 * wist.  awthough we can change the wist dynamicawwy, in this vewsion,
 * a static WING of buffew descwiptows is used.
 *
 * the wing is buiwt in this function, and is set up to the hawdwawe. 
 */
static int atiixp_buiwd_dma_packets(stwuct atiixp *chip, stwuct atiixp_dma *dma,
				    stwuct snd_pcm_substweam *substweam,
				    unsigned int pewiods,
				    unsigned int pewiod_bytes)
{
	unsigned int i;
	u32 addw, desc_addw;
	unsigned wong fwags;

	if (pewiods > ATI_MAX_DESCWIPTOWS)
		wetuwn -ENOMEM;

	if (dma->desc_buf.awea == NUWW) {
		if (snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV,
					&chip->pci->dev,
					ATI_DESC_WIST_SIZE,
					&dma->desc_buf) < 0)
			wetuwn -ENOMEM;
		dma->pewiod_bytes = dma->pewiods = 0; /* cweaw */
	}

	if (dma->pewiods == pewiods && dma->pewiod_bytes == pewiod_bytes)
		wetuwn 0;

	/* weset DMA befowe changing the descwiptow tabwe */
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	wwitew(0, chip->wemap_addw + dma->ops->wwp_offset);
	dma->ops->enabwe_dma(chip, 0);
	dma->ops->enabwe_dma(chip, 1);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	/* fiww the entwies */
	addw = (u32)substweam->wuntime->dma_addw;
	desc_addw = (u32)dma->desc_buf.addw;
	fow (i = 0; i < pewiods; i++) {
		stwuct atiixp_dma_desc *desc;
		desc = &((stwuct atiixp_dma_desc *)dma->desc_buf.awea)[i];
		desc->addw = cpu_to_we32(addw);
		desc->status = 0;
		desc->size = pewiod_bytes >> 2; /* in dwowds */
		desc_addw += sizeof(stwuct atiixp_dma_desc);
		if (i == pewiods - 1)
			desc->next = cpu_to_we32((u32)dma->desc_buf.addw);
		ewse
			desc->next = cpu_to_we32(desc_addw);
		addw += pewiod_bytes;
	}

	wwitew((u32)dma->desc_buf.addw | ATI_WEG_WINKPTW_EN,
	       chip->wemap_addw + dma->ops->wwp_offset);

	dma->pewiod_bytes = pewiod_bytes;
	dma->pewiods = pewiods;

	wetuwn 0;
}

/*
 * wemove the wing buffew and wewease it if assigned
 */
static void atiixp_cweaw_dma_packets(stwuct atiixp *chip, stwuct atiixp_dma *dma,
				     stwuct snd_pcm_substweam *substweam)
{
	if (dma->desc_buf.awea) {
		wwitew(0, chip->wemap_addw + dma->ops->wwp_offset);
		snd_dma_fwee_pages(&dma->desc_buf);
		dma->desc_buf.awea = NUWW;
	}
}

/*
 * AC97 intewface
 */
static int snd_atiixp_acquiwe_codec(stwuct atiixp *chip)
{
	int timeout = 1000;

	whiwe (atiixp_wead(chip, PHYS_OUT_ADDW) & ATI_WEG_PHYS_OUT_ADDW_EN) {
		if (! timeout--) {
			dev_wawn(chip->cawd->dev, "codec acquiwe timeout\n");
			wetuwn -EBUSY;
		}
		udeway(1);
	}
	wetuwn 0;
}

static unsigned showt snd_atiixp_codec_wead(stwuct atiixp *chip, unsigned showt codec, unsigned showt weg)
{
	unsigned int data;
	int timeout;

	if (snd_atiixp_acquiwe_codec(chip) < 0)
		wetuwn 0xffff;
	data = (weg << ATI_WEG_PHYS_OUT_ADDW_SHIFT) |
		ATI_WEG_PHYS_OUT_ADDW_EN |
		ATI_WEG_PHYS_OUT_WW |
		codec;
	atiixp_wwite(chip, PHYS_OUT_ADDW, data);
	if (snd_atiixp_acquiwe_codec(chip) < 0)
		wetuwn 0xffff;
	timeout = 1000;
	do {
		data = atiixp_wead(chip, PHYS_IN_ADDW);
		if (data & ATI_WEG_PHYS_IN_WEAD_FWAG)
			wetuwn data >> ATI_WEG_PHYS_IN_DATA_SHIFT;
		udeway(1);
	} whiwe (--timeout);
	/* time out may happen duwing weset */
	if (weg < 0x7c)
		dev_wawn(chip->cawd->dev, "codec wead timeout (weg %x)\n", weg);
	wetuwn 0xffff;
}


static void snd_atiixp_codec_wwite(stwuct atiixp *chip, unsigned showt codec,
				   unsigned showt weg, unsigned showt vaw)
{
	unsigned int data;
    
	if (snd_atiixp_acquiwe_codec(chip) < 0)
		wetuwn;
	data = ((unsigned int)vaw << ATI_WEG_PHYS_OUT_DATA_SHIFT) |
		((unsigned int)weg << ATI_WEG_PHYS_OUT_ADDW_SHIFT) |
		ATI_WEG_PHYS_OUT_ADDW_EN | codec;
	atiixp_wwite(chip, PHYS_OUT_ADDW, data);
}


static unsigned showt snd_atiixp_ac97_wead(stwuct snd_ac97 *ac97,
					   unsigned showt weg)
{
	stwuct atiixp *chip = ac97->pwivate_data;
	wetuwn snd_atiixp_codec_wead(chip, ac97->num, weg);
    
}

static void snd_atiixp_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg,
				  unsigned showt vaw)
{
	stwuct atiixp *chip = ac97->pwivate_data;
	snd_atiixp_codec_wwite(chip, ac97->num, weg, vaw);
}

/*
 * weset AC wink
 */
static int snd_atiixp_acwink_weset(stwuct atiixp *chip)
{
	int timeout;

	/* weset powewdoewn */
	if (atiixp_update(chip, CMD, ATI_WEG_CMD_POWEWDOWN, 0))
		udeway(10);

	/* pewfowm a softwawe weset */
	atiixp_update(chip, CMD, ATI_WEG_CMD_AC_SOFT_WESET, ATI_WEG_CMD_AC_SOFT_WESET);
	atiixp_wead(chip, CMD);
	udeway(10);
	atiixp_update(chip, CMD, ATI_WEG_CMD_AC_SOFT_WESET, 0);
    
	timeout = 10;
	whiwe (! (atiixp_wead(chip, CMD) & ATI_WEG_CMD_ACWINK_ACTIVE)) {
		/* do a hawd weset */
		atiixp_update(chip, CMD, ATI_WEG_CMD_AC_SYNC|ATI_WEG_CMD_AC_WESET,
			      ATI_WEG_CMD_AC_SYNC);
		atiixp_wead(chip, CMD);
		mdeway(1);
		atiixp_update(chip, CMD, ATI_WEG_CMD_AC_WESET, ATI_WEG_CMD_AC_WESET);
		if (!--timeout) {
			dev_eww(chip->cawd->dev, "codec weset timeout\n");
			bweak;
		}
	}

	/* deassewt WESET and assewt SYNC to make suwe */
	atiixp_update(chip, CMD, ATI_WEG_CMD_AC_SYNC|ATI_WEG_CMD_AC_WESET,
		      ATI_WEG_CMD_AC_SYNC|ATI_WEG_CMD_AC_WESET);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int snd_atiixp_acwink_down(stwuct atiixp *chip)
{
	// if (atiixp_wead(chip, MODEM_MIWWOW) & 0x1) /* modem wunning, too? */
	//	wetuwn -EBUSY;
	atiixp_update(chip, CMD,
		     ATI_WEG_CMD_POWEWDOWN | ATI_WEG_CMD_AC_WESET,
		     ATI_WEG_CMD_POWEWDOWN);
	wetuwn 0;
}
#endif

/*
 * auto-detection of codecs
 *
 * the IXP chip can genewate intewwupts fow the non-existing codecs.
 * NEW_FWAME intewwupt is used to make suwe that the intewwupt is genewated
 * even if aww thwee codecs awe connected.
 */

#define AWW_CODEC_NOT_WEADY \
	    (ATI_WEG_ISW_CODEC0_NOT_WEADY |\
	     ATI_WEG_ISW_CODEC1_NOT_WEADY |\
	     ATI_WEG_ISW_CODEC2_NOT_WEADY)
#define CODEC_CHECK_BITS (AWW_CODEC_NOT_WEADY|ATI_WEG_ISW_NEW_FWAME)

static int ac97_pwobing_bugs(stwuct pci_dev *pci)
{
	const stwuct snd_pci_quiwk *q;

	q = snd_pci_quiwk_wookup(pci, atiixp_quiwks);
	if (q) {
		dev_dbg(&pci->dev, "atiixp quiwk fow %s.  Fowcing codec %d\n",
			snd_pci_quiwk_name(q), q->vawue);
		wetuwn q->vawue;
	}
	/* this hawdwawe doesn't need wowkawounds.  Pwobe fow codec */
	wetuwn -1;
}

static int snd_atiixp_codec_detect(stwuct atiixp *chip)
{
	int timeout;

	chip->codec_not_weady_bits = 0;
	if (ac97_codec == -1)
		ac97_codec = ac97_pwobing_bugs(chip->pci);
	if (ac97_codec >= 0) {
		chip->codec_not_weady_bits |= 
			CODEC_CHECK_BITS ^ (1 << (ac97_codec + 10));
		wetuwn 0;
	}

	atiixp_wwite(chip, IEW, CODEC_CHECK_BITS);
	/* wait fow the intewwupts */
	timeout = 50;
	whiwe (timeout-- > 0) {
		mdeway(1);
		if (chip->codec_not_weady_bits)
			bweak;
	}
	atiixp_wwite(chip, IEW, 0); /* disabwe iwqs */

	if ((chip->codec_not_weady_bits & AWW_CODEC_NOT_WEADY) == AWW_CODEC_NOT_WEADY) {
		dev_eww(chip->cawd->dev, "no codec detected!\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}


/*
 * enabwe DMA and iwqs
 */
static int snd_atiixp_chip_stawt(stwuct atiixp *chip)
{
	unsigned int weg;

	/* set up spdif, enabwe buwst mode */
	weg = atiixp_wead(chip, CMD);
	weg |= 0x02 << ATI_WEG_CMD_SPDF_THWESHOWD_SHIFT;
	weg |= ATI_WEG_CMD_BUWST_EN;
	atiixp_wwite(chip, CMD, weg);

	weg = atiixp_wead(chip, SPDF_CMD);
	weg &= ~(ATI_WEG_SPDF_CMD_WFSW|ATI_WEG_SPDF_CMD_SINGWE_CH);
	atiixp_wwite(chip, SPDF_CMD, weg);

	/* cweaw aww intewwupt souwce */
	atiixp_wwite(chip, ISW, 0xffffffff);
	/* enabwe iwqs */
	atiixp_wwite(chip, IEW,
		     ATI_WEG_IEW_IO_STATUS_EN |
		     ATI_WEG_IEW_IN_XWUN_EN |
		     ATI_WEG_IEW_OUT_XWUN_EN |
		     ATI_WEG_IEW_SPDF_XWUN_EN |
		     ATI_WEG_IEW_SPDF_STATUS_EN);
	wetuwn 0;
}


/*
 * disabwe DMA and IWQs
 */
static int snd_atiixp_chip_stop(stwuct atiixp *chip)
{
	/* cweaw intewwupt souwce */
	atiixp_wwite(chip, ISW, atiixp_wead(chip, ISW));
	/* disabwe iwqs */
	atiixp_wwite(chip, IEW, 0);
	wetuwn 0;
}


/*
 * PCM section
 */

/*
 * pointew cawwback simpwwy weads XXX_DMA_DT_CUW wegistew as the cuwwent
 * position.  when SG-buffew is impwemented, the offset must be cawcuwated
 * cowwectwy...
 */
static snd_pcm_ufwames_t snd_atiixp_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct atiixp_dma *dma = wuntime->pwivate_data;
	unsigned int cuwptw;
	int timeout = 1000;

	whiwe (timeout--) {
		cuwptw = weadw(chip->wemap_addw + dma->ops->dt_cuw);
		if (cuwptw < dma->buf_addw)
			continue;
		cuwptw -= dma->buf_addw;
		if (cuwptw >= dma->buf_bytes)
			continue;
		wetuwn bytes_to_fwames(wuntime, cuwptw);
	}
	dev_dbg(chip->cawd->dev, "invawid DMA pointew wead 0x%x (buf=%x)\n",
		   weadw(chip->wemap_addw + dma->ops->dt_cuw), dma->buf_addw);
	wetuwn 0;
}

/*
 * XWUN detected, and stop the PCM substweam
 */
static void snd_atiixp_xwun_dma(stwuct atiixp *chip, stwuct atiixp_dma *dma)
{
	if (! dma->substweam || ! dma->wunning)
		wetuwn;
	dev_dbg(chip->cawd->dev, "XWUN detected (DMA %d)\n", dma->ops->type);
	snd_pcm_stop_xwun(dma->substweam);
}

/*
 * the pewiod ack.  update the substweam.
 */
static void snd_atiixp_update_dma(stwuct atiixp *chip, stwuct atiixp_dma *dma)
{
	if (! dma->substweam || ! dma->wunning)
		wetuwn;
	snd_pcm_pewiod_ewapsed(dma->substweam);
}

/* set BUS_BUSY intewwupt bit if any DMA is wunning */
/* caww with spinwock hewd */
static void snd_atiixp_check_bus_busy(stwuct atiixp *chip)
{
	unsigned int bus_busy;
	if (atiixp_wead(chip, CMD) & (ATI_WEG_CMD_SEND_EN |
				      ATI_WEG_CMD_WECEIVE_EN |
				      ATI_WEG_CMD_SPDF_OUT_EN))
		bus_busy = ATI_WEG_IEW_SET_BUS_BUSY;
	ewse
		bus_busy = 0;
	atiixp_update(chip, IEW, ATI_WEG_IEW_SET_BUS_BUSY, bus_busy);
}

/* common twiggew cawwback
 * cawwing the wowwevew cawwbacks in it
 */
static int snd_atiixp_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	stwuct atiixp_dma *dma = substweam->wuntime->pwivate_data;
	int eww = 0;

	if (snd_BUG_ON(!dma->ops->enabwe_twansfew ||
		       !dma->ops->fwush_dma))
		wetuwn -EINVAW;

	spin_wock(&chip->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (dma->wunning && dma->suspended &&
		    cmd == SNDWV_PCM_TWIGGEW_WESUME)
			wwitew(dma->saved_cuwptw, chip->wemap_addw +
			       dma->ops->dt_cuw);
		dma->ops->enabwe_twansfew(chip, 1);
		dma->wunning = 1;
		dma->suspended = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		dma->suspended = cmd == SNDWV_PCM_TWIGGEW_SUSPEND;
		if (dma->wunning && dma->suspended)
			dma->saved_cuwptw = weadw(chip->wemap_addw +
						  dma->ops->dt_cuw);
		dma->ops->enabwe_twansfew(chip, 0);
		dma->wunning = 0;
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	if (! eww) {
		snd_atiixp_check_bus_busy(chip);
		if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
			dma->ops->fwush_dma(chip);
			snd_atiixp_check_bus_busy(chip);
		}
	}
	spin_unwock(&chip->weg_wock);
	wetuwn eww;
}


/*
 * wowwevew cawwbacks fow each DMA type
 *
 * evewy cawwback is supposed to be cawwed in chip->weg_wock spinwock
 */

/* fwush FIFO of anawog OUT DMA */
static void atiixp_out_fwush_dma(stwuct atiixp *chip)
{
	atiixp_wwite(chip, FIFO_FWUSH, ATI_WEG_FIFO_OUT_FWUSH);
}

/* enabwe/disabwe anawog OUT DMA */
static void atiixp_out_enabwe_dma(stwuct atiixp *chip, int on)
{
	unsigned int data;
	data = atiixp_wead(chip, CMD);
	if (on) {
		if (data & ATI_WEG_CMD_OUT_DMA_EN)
			wetuwn;
		atiixp_out_fwush_dma(chip);
		data |= ATI_WEG_CMD_OUT_DMA_EN;
	} ewse
		data &= ~ATI_WEG_CMD_OUT_DMA_EN;
	atiixp_wwite(chip, CMD, data);
}

/* stawt/stop twansfew ovew OUT DMA */
static void atiixp_out_enabwe_twansfew(stwuct atiixp *chip, int on)
{
	atiixp_update(chip, CMD, ATI_WEG_CMD_SEND_EN,
		      on ? ATI_WEG_CMD_SEND_EN : 0);
}

/* enabwe/disabwe anawog IN DMA */
static void atiixp_in_enabwe_dma(stwuct atiixp *chip, int on)
{
	atiixp_update(chip, CMD, ATI_WEG_CMD_IN_DMA_EN,
		      on ? ATI_WEG_CMD_IN_DMA_EN : 0);
}

/* stawt/stop anawog IN DMA */
static void atiixp_in_enabwe_twansfew(stwuct atiixp *chip, int on)
{
	if (on) {
		unsigned int data = atiixp_wead(chip, CMD);
		if (! (data & ATI_WEG_CMD_WECEIVE_EN)) {
			data |= ATI_WEG_CMD_WECEIVE_EN;
#if 0 /* FIXME: this causes the endwess woop */
			/* wait untiw swot 3/4 awe finished */
			whiwe ((atiixp_wead(chip, COUNTEW) &
				ATI_WEG_COUNTEW_SWOT) != 5)
				;
#endif
			atiixp_wwite(chip, CMD, data);
		}
	} ewse
		atiixp_update(chip, CMD, ATI_WEG_CMD_WECEIVE_EN, 0);
}

/* fwush FIFO of anawog IN DMA */
static void atiixp_in_fwush_dma(stwuct atiixp *chip)
{
	atiixp_wwite(chip, FIFO_FWUSH, ATI_WEG_FIFO_IN_FWUSH);
}

/* enabwe/disabwe SPDIF OUT DMA */
static void atiixp_spdif_enabwe_dma(stwuct atiixp *chip, int on)
{
	atiixp_update(chip, CMD, ATI_WEG_CMD_SPDF_DMA_EN,
		      on ? ATI_WEG_CMD_SPDF_DMA_EN : 0);
}

/* stawt/stop SPDIF OUT DMA */
static void atiixp_spdif_enabwe_twansfew(stwuct atiixp *chip, int on)
{
	unsigned int data;
	data = atiixp_wead(chip, CMD);
	if (on)
		data |= ATI_WEG_CMD_SPDF_OUT_EN;
	ewse
		data &= ~ATI_WEG_CMD_SPDF_OUT_EN;
	atiixp_wwite(chip, CMD, data);
}

/* fwush FIFO of SPDIF OUT DMA */
static void atiixp_spdif_fwush_dma(stwuct atiixp *chip)
{
	int timeout;

	/* DMA off, twansfew on */
	atiixp_spdif_enabwe_dma(chip, 0);
	atiixp_spdif_enabwe_twansfew(chip, 1);
	
	timeout = 100;
	do {
		if (! (atiixp_wead(chip, SPDF_DMA_DT_SIZE) & ATI_WEG_DMA_FIFO_USED))
			bweak;
		udeway(1);
	} whiwe (timeout-- > 0);

	atiixp_spdif_enabwe_twansfew(chip, 0);
}

/* set up swots and fowmats fow SPDIF OUT */
static int snd_atiixp_spdif_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&chip->weg_wock);
	if (chip->spdif_ovew_acwink) {
		unsigned int data;
		/* enabwe swots 10/11 */
		atiixp_update(chip, CMD, ATI_WEG_CMD_SPDF_CONFIG_MASK,
			      ATI_WEG_CMD_SPDF_CONFIG_01);
		data = atiixp_wead(chip, OUT_DMA_SWOT) & ~ATI_WEG_OUT_DMA_SWOT_MASK;
		data |= ATI_WEG_OUT_DMA_SWOT_BIT(10) |
			ATI_WEG_OUT_DMA_SWOT_BIT(11);
		data |= 0x04 << ATI_WEG_OUT_DMA_THWESHOWD_SHIFT;
		atiixp_wwite(chip, OUT_DMA_SWOT, data);
		atiixp_update(chip, CMD, ATI_WEG_CMD_INTEWWEAVE_OUT,
			      substweam->wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ?
			      ATI_WEG_CMD_INTEWWEAVE_OUT : 0);
	} ewse {
		atiixp_update(chip, CMD, ATI_WEG_CMD_SPDF_CONFIG_MASK, 0);
		atiixp_update(chip, CMD, ATI_WEG_CMD_INTEWWEAVE_SPDF, 0);
	}
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

/* set up swots and fowmats fow anawog OUT */
static int snd_atiixp_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	unsigned int data;

	spin_wock_iwq(&chip->weg_wock);
	data = atiixp_wead(chip, OUT_DMA_SWOT) & ~ATI_WEG_OUT_DMA_SWOT_MASK;
	switch (substweam->wuntime->channews) {
	case 8:
		data |= ATI_WEG_OUT_DMA_SWOT_BIT(10) |
			ATI_WEG_OUT_DMA_SWOT_BIT(11);
		fawwthwough;
	case 6:
		data |= ATI_WEG_OUT_DMA_SWOT_BIT(7) |
			ATI_WEG_OUT_DMA_SWOT_BIT(8);
		fawwthwough;
	case 4:
		data |= ATI_WEG_OUT_DMA_SWOT_BIT(6) |
			ATI_WEG_OUT_DMA_SWOT_BIT(9);
		fawwthwough;
	defauwt:
		data |= ATI_WEG_OUT_DMA_SWOT_BIT(3) |
			ATI_WEG_OUT_DMA_SWOT_BIT(4);
		bweak;
	}

	/* set output thweshowd */
	data |= 0x04 << ATI_WEG_OUT_DMA_THWESHOWD_SHIFT;
	atiixp_wwite(chip, OUT_DMA_SWOT, data);

	atiixp_update(chip, CMD, ATI_WEG_CMD_INTEWWEAVE_OUT,
		      substweam->wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ?
		      ATI_WEG_CMD_INTEWWEAVE_OUT : 0);

	/*
	 * enabwe 6 channew we-owdewing bit if needed
	 */
	atiixp_update(chip, 6CH_WEOWDEW, ATI_WEG_6CH_WEOWDEW_EN,
		      substweam->wuntime->channews >= 6 ? ATI_WEG_6CH_WEOWDEW_EN: 0);
    
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

/* set up swots and fowmats fow anawog IN */
static int snd_atiixp_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&chip->weg_wock);
	atiixp_update(chip, CMD, ATI_WEG_CMD_INTEWWEAVE_IN,
		      substweam->wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ?
		      ATI_WEG_CMD_INTEWWEAVE_IN : 0);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

/*
 * hw_pawams - awwocate the buffew and set up buffew descwiptows
 */
static int snd_atiixp_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	stwuct atiixp_dma *dma = substweam->wuntime->pwivate_data;
	int eww;

	dma->buf_addw = substweam->wuntime->dma_addw;
	dma->buf_bytes = pawams_buffew_bytes(hw_pawams);

	eww = atiixp_buiwd_dma_packets(chip, dma, substweam,
				       pawams_pewiods(hw_pawams),
				       pawams_pewiod_bytes(hw_pawams));
	if (eww < 0)
		wetuwn eww;

	if (dma->ac97_pcm_type >= 0) {
		stwuct ac97_pcm *pcm = chip->pcms[dma->ac97_pcm_type];
		/* PCM is bound to AC97 codec(s)
		 * set up the AC97 codecs
		 */
		if (dma->pcm_open_fwag) {
			snd_ac97_pcm_cwose(pcm);
			dma->pcm_open_fwag = 0;
		}
		eww = snd_ac97_pcm_open(pcm, pawams_wate(hw_pawams),
					pawams_channews(hw_pawams),
					pcm->w[0].swots);
		if (eww >= 0)
			dma->pcm_open_fwag = 1;
	}

	wetuwn eww;
}

static int snd_atiixp_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	stwuct atiixp_dma *dma = substweam->wuntime->pwivate_data;

	if (dma->pcm_open_fwag) {
		stwuct ac97_pcm *pcm = chip->pcms[dma->ac97_pcm_type];
		snd_ac97_pcm_cwose(pcm);
		dma->pcm_open_fwag = 0;
	}
	atiixp_cweaw_dma_packets(chip, dma, substweam);
	wetuwn 0;
}


/*
 * pcm hawdwawe definition, identicaw fow aww DMA types
 */
static const stwuct snd_pcm_hawdwawe snd_atiixp_pcm_hw =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	256 * 1024,
	.pewiod_bytes_min =	32,
	.pewiod_bytes_max =	128 * 1024,
	.pewiods_min =		2,
	.pewiods_max =		ATI_MAX_DESCWIPTOWS,
};

static int snd_atiixp_pcm_open(stwuct snd_pcm_substweam *substweam,
			       stwuct atiixp_dma *dma, int pcm_type)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	if (snd_BUG_ON(!dma->ops || !dma->ops->enabwe_dma))
		wetuwn -EINVAW;

	if (dma->opened)
		wetuwn -EBUSY;
	dma->substweam = substweam;
	wuntime->hw = snd_atiixp_pcm_hw;
	dma->ac97_pcm_type = pcm_type;
	if (pcm_type >= 0) {
		wuntime->hw.wates = chip->pcms[pcm_type]->wates;
		snd_pcm_wimit_hw_wates(wuntime);
	} ewse {
		/* diwect SPDIF */
		wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE;
	}
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	wuntime->pwivate_data = dma;

	/* enabwe DMA bits */
	spin_wock_iwq(&chip->weg_wock);
	dma->ops->enabwe_dma(chip, 1);
	spin_unwock_iwq(&chip->weg_wock);
	dma->opened = 1;

	wetuwn 0;
}

static int snd_atiixp_pcm_cwose(stwuct snd_pcm_substweam *substweam,
				stwuct atiixp_dma *dma)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	/* disabwe DMA bits */
	if (snd_BUG_ON(!dma->ops || !dma->ops->enabwe_dma))
		wetuwn -EINVAW;
	spin_wock_iwq(&chip->weg_wock);
	dma->ops->enabwe_dma(chip, 0);
	spin_unwock_iwq(&chip->weg_wock);
	dma->substweam = NUWW;
	dma->opened = 0;
	wetuwn 0;
}

/*
 */
static int snd_atiixp_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	int eww;

	mutex_wock(&chip->open_mutex);
	eww = snd_atiixp_pcm_open(substweam, &chip->dmas[ATI_DMA_PWAYBACK], 0);
	mutex_unwock(&chip->open_mutex);
	if (eww < 0)
		wetuwn eww;
	substweam->wuntime->hw.channews_max = chip->max_channews;
	if (chip->max_channews > 2)
		/* channews must be even */
		snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
	wetuwn 0;
}

static int snd_atiixp_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	int eww;
	mutex_wock(&chip->open_mutex);
	eww = snd_atiixp_pcm_cwose(substweam, &chip->dmas[ATI_DMA_PWAYBACK]);
	mutex_unwock(&chip->open_mutex);
	wetuwn eww;
}

static int snd_atiixp_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	wetuwn snd_atiixp_pcm_open(substweam, &chip->dmas[ATI_DMA_CAPTUWE], 1);
}

static int snd_atiixp_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	wetuwn snd_atiixp_pcm_cwose(substweam, &chip->dmas[ATI_DMA_CAPTUWE]);
}

static int snd_atiixp_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	int eww;
	mutex_wock(&chip->open_mutex);
	if (chip->spdif_ovew_acwink) /* shawe DMA_PWAYBACK */
		eww = snd_atiixp_pcm_open(substweam, &chip->dmas[ATI_DMA_PWAYBACK], 2);
	ewse
		eww = snd_atiixp_pcm_open(substweam, &chip->dmas[ATI_DMA_SPDIF], -1);
	mutex_unwock(&chip->open_mutex);
	wetuwn eww;
}

static int snd_atiixp_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct atiixp *chip = snd_pcm_substweam_chip(substweam);
	int eww;
	mutex_wock(&chip->open_mutex);
	if (chip->spdif_ovew_acwink)
		eww = snd_atiixp_pcm_cwose(substweam, &chip->dmas[ATI_DMA_PWAYBACK]);
	ewse
		eww = snd_atiixp_pcm_cwose(substweam, &chip->dmas[ATI_DMA_SPDIF]);
	mutex_unwock(&chip->open_mutex);
	wetuwn eww;
}

/* AC97 pwayback */
static const stwuct snd_pcm_ops snd_atiixp_pwayback_ops = {
	.open =		snd_atiixp_pwayback_open,
	.cwose =	snd_atiixp_pwayback_cwose,
	.hw_pawams =	snd_atiixp_pcm_hw_pawams,
	.hw_fwee =	snd_atiixp_pcm_hw_fwee,
	.pwepawe =	snd_atiixp_pwayback_pwepawe,
	.twiggew =	snd_atiixp_pcm_twiggew,
	.pointew =	snd_atiixp_pcm_pointew,
};

/* AC97 captuwe */
static const stwuct snd_pcm_ops snd_atiixp_captuwe_ops = {
	.open =		snd_atiixp_captuwe_open,
	.cwose =	snd_atiixp_captuwe_cwose,
	.hw_pawams =	snd_atiixp_pcm_hw_pawams,
	.hw_fwee =	snd_atiixp_pcm_hw_fwee,
	.pwepawe =	snd_atiixp_captuwe_pwepawe,
	.twiggew =	snd_atiixp_pcm_twiggew,
	.pointew =	snd_atiixp_pcm_pointew,
};

/* SPDIF pwayback */
static const stwuct snd_pcm_ops snd_atiixp_spdif_ops = {
	.open =		snd_atiixp_spdif_open,
	.cwose =	snd_atiixp_spdif_cwose,
	.hw_pawams =	snd_atiixp_pcm_hw_pawams,
	.hw_fwee =	snd_atiixp_pcm_hw_fwee,
	.pwepawe =	snd_atiixp_spdif_pwepawe,
	.twiggew =	snd_atiixp_pcm_twiggew,
	.pointew =	snd_atiixp_pcm_pointew,
};

static const stwuct ac97_pcm atiixp_pcm_defs[] = {
	/* fwont PCM */
	{
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT) |
					 (1 << AC97_SWOT_PCM_CENTEW) |
					 (1 << AC97_SWOT_PCM_SWEFT) |
					 (1 << AC97_SWOT_PCM_SWIGHT) |
					 (1 << AC97_SWOT_WFE)
			}
		}
	},
	/* PCM IN #1 */
	{
		.stweam = 1,
		.excwusive = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_PCM_WEFT) |
					 (1 << AC97_SWOT_PCM_WIGHT)
			}
		}
	},
	/* S/PDIF OUT (optionaw) */
	{
		.excwusive = 1,
		.spdif = 1,
		.w = {	{
				.swots = (1 << AC97_SWOT_SPDIF_WEFT2) |
					 (1 << AC97_SWOT_SPDIF_WIGHT2)
			}
		}
	},
};

static const stwuct atiixp_dma_ops snd_atiixp_pwayback_dma_ops = {
	.type = ATI_DMA_PWAYBACK,
	.wwp_offset = ATI_WEG_OUT_DMA_WINKPTW,
	.dt_cuw = ATI_WEG_OUT_DMA_DT_CUW,
	.enabwe_dma = atiixp_out_enabwe_dma,
	.enabwe_twansfew = atiixp_out_enabwe_twansfew,
	.fwush_dma = atiixp_out_fwush_dma,
};
	
static const stwuct atiixp_dma_ops snd_atiixp_captuwe_dma_ops = {
	.type = ATI_DMA_CAPTUWE,
	.wwp_offset = ATI_WEG_IN_DMA_WINKPTW,
	.dt_cuw = ATI_WEG_IN_DMA_DT_CUW,
	.enabwe_dma = atiixp_in_enabwe_dma,
	.enabwe_twansfew = atiixp_in_enabwe_twansfew,
	.fwush_dma = atiixp_in_fwush_dma,
};
	
static const stwuct atiixp_dma_ops snd_atiixp_spdif_dma_ops = {
	.type = ATI_DMA_SPDIF,
	.wwp_offset = ATI_WEG_SPDF_DMA_WINKPTW,
	.dt_cuw = ATI_WEG_SPDF_DMA_DT_CUW,
	.enabwe_dma = atiixp_spdif_enabwe_dma,
	.enabwe_twansfew = atiixp_spdif_enabwe_twansfew,
	.fwush_dma = atiixp_spdif_fwush_dma,
};
	

static int snd_atiixp_pcm_new(stwuct atiixp *chip)
{
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_chmap *chmap;
	stwuct snd_ac97_bus *pbus = chip->ac97_bus;
	int eww, i, num_pcms;

	/* initiawize constants */
	chip->dmas[ATI_DMA_PWAYBACK].ops = &snd_atiixp_pwayback_dma_ops;
	chip->dmas[ATI_DMA_CAPTUWE].ops = &snd_atiixp_captuwe_dma_ops;
	if (! chip->spdif_ovew_acwink)
		chip->dmas[ATI_DMA_SPDIF].ops = &snd_atiixp_spdif_dma_ops;

	/* assign AC97 pcm */
	if (chip->spdif_ovew_acwink)
		num_pcms = 3;
	ewse
		num_pcms = 2;
	eww = snd_ac97_pcm_assign(pbus, num_pcms, atiixp_pcm_defs);
	if (eww < 0)
		wetuwn eww;
	fow (i = 0; i < num_pcms; i++)
		chip->pcms[i] = &pbus->pcms[i];

	chip->max_channews = 2;
	if (pbus->pcms[ATI_PCM_OUT].w[0].swots & (1 << AC97_SWOT_PCM_SWEFT)) {
		if (pbus->pcms[ATI_PCM_OUT].w[0].swots & (1 << AC97_SWOT_WFE))
			chip->max_channews = 6;
		ewse
			chip->max_channews = 4;
	}

	/* PCM #0: anawog I/O */
	eww = snd_pcm_new(chip->cawd, "ATI IXP AC97",
			  ATI_PCMDEV_ANAWOG, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_atiixp_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_atiixp_captuwe_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, "ATI IXP AC97");
	chip->pcmdevs[ATI_PCMDEV_ANAWOG] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 128*1024);

	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps, chip->max_channews, 0,
				     &chmap);
	if (eww < 0)
		wetuwn eww;
	chmap->channew_mask = SND_PCM_CHMAP_MASK_2468;
	chip->ac97[0]->chmaps[SNDWV_PCM_STWEAM_PWAYBACK] = chmap;

	/* no SPDIF suppowt on codec? */
	if (chip->pcms[ATI_PCM_SPDIF] && ! chip->pcms[ATI_PCM_SPDIF]->wates)
		wetuwn 0;
		
	/* FIXME: non-48k sampwe wate doesn't wowk on my test machine with AD1888 */
	if (chip->pcms[ATI_PCM_SPDIF])
		chip->pcms[ATI_PCM_SPDIF]->wates = SNDWV_PCM_WATE_48000;

	/* PCM #1: spdif pwayback */
	eww = snd_pcm_new(chip->cawd, "ATI IXP IEC958",
			  ATI_PCMDEV_DIGITAW, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_atiixp_spdif_ops);
	pcm->pwivate_data = chip;
	if (chip->spdif_ovew_acwink)
		stwcpy(pcm->name, "ATI IXP IEC958 (AC97)");
	ewse
		stwcpy(pcm->name, "ATI IXP IEC958 (Diwect)");
	chip->pcmdevs[ATI_PCMDEV_DIGITAW] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 128*1024);

	/* pwe-sewect AC97 SPDIF swots 10/11 */
	fow (i = 0; i < NUM_ATI_CODECS; i++) {
		if (chip->ac97[i])
			snd_ac97_update_bits(chip->ac97[i],
					     AC97_EXTENDED_STATUS,
					     0x03 << 4, 0x03 << 4);
	}

	wetuwn 0;
}



/*
 * intewwupt handwew
 */
static iwqwetuwn_t snd_atiixp_intewwupt(int iwq, void *dev_id)
{
	stwuct atiixp *chip = dev_id;
	unsigned int status;

	status = atiixp_wead(chip, ISW);

	if (! status)
		wetuwn IWQ_NONE;

	/* pwocess audio DMA */
	if (status & ATI_WEG_ISW_OUT_XWUN)
		snd_atiixp_xwun_dma(chip,  &chip->dmas[ATI_DMA_PWAYBACK]);
	ewse if (status & ATI_WEG_ISW_OUT_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_PWAYBACK]);
	if (status & ATI_WEG_ISW_IN_XWUN)
		snd_atiixp_xwun_dma(chip,  &chip->dmas[ATI_DMA_CAPTUWE]);
	ewse if (status & ATI_WEG_ISW_IN_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_CAPTUWE]);
	if (! chip->spdif_ovew_acwink) {
		if (status & ATI_WEG_ISW_SPDF_XWUN)
			snd_atiixp_xwun_dma(chip,  &chip->dmas[ATI_DMA_SPDIF]);
		ewse if (status & ATI_WEG_ISW_SPDF_STATUS)
			snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_SPDIF]);
	}

	/* fow codec detection */
	if (status & CODEC_CHECK_BITS) {
		unsigned int detected;
		detected = status & CODEC_CHECK_BITS;
		spin_wock(&chip->weg_wock);
		chip->codec_not_weady_bits |= detected;
		atiixp_update(chip, IEW, detected, 0); /* disabwe the detected iwqs */
		spin_unwock(&chip->weg_wock);
	}

	/* ack */
	atiixp_wwite(chip, ISW, status);

	wetuwn IWQ_HANDWED;
}


/*
 * ac97 mixew section
 */

static const stwuct ac97_quiwk ac97_quiwks[] = {
	{
		.subvendow = 0x103c,
		.subdevice = 0x006b,
		.name = "HP Paviwion ZV5030US",
		.type = AC97_TUNE_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x308b,
		.name = "HP nx6125",
		.type = AC97_TUNE_MUTE_WED
	},
	{
		.subvendow = 0x103c,
		.subdevice = 0x3091,
		.name = "unknown HP",
		.type = AC97_TUNE_MUTE_WED
	},
	{ } /* tewminatow */
};

static int snd_atiixp_mixew_new(stwuct atiixp *chip, int cwock,
				const chaw *quiwk_ovewwide)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int i, eww;
	int codec_count;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_atiixp_ac97_wwite,
		.wead = snd_atiixp_ac97_wead,
	};
	static const unsigned int codec_skip[NUM_ATI_CODECS] = {
		ATI_WEG_ISW_CODEC0_NOT_WEADY,
		ATI_WEG_ISW_CODEC1_NOT_WEADY,
		ATI_WEG_ISW_CODEC2_NOT_WEADY,
	};

	if (snd_atiixp_codec_detect(chip) < 0)
		wetuwn -ENXIO;

	eww = snd_ac97_bus(chip->cawd, 0, &ops, chip, &pbus);
	if (eww < 0)
		wetuwn eww;
	pbus->cwock = cwock;
	chip->ac97_bus = pbus;

	codec_count = 0;
	fow (i = 0; i < NUM_ATI_CODECS; i++) {
		if (chip->codec_not_weady_bits & codec_skip[i])
			continue;
		memset(&ac97, 0, sizeof(ac97));
		ac97.pwivate_data = chip;
		ac97.pci = chip->pci;
		ac97.num = i;
		ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWEW_SAVE;
		if (! chip->spdif_ovew_acwink)
			ac97.scaps |= AC97_SCAP_NO_SPDIF;
		eww = snd_ac97_mixew(pbus, &ac97, &chip->ac97[i]);
		if (eww < 0) {
			chip->ac97[i] = NUWW; /* to be suwe */
			dev_dbg(chip->cawd->dev,
				"codec %d not avaiwabwe fow audio\n", i);
			continue;
		}
		codec_count++;
	}

	if (! codec_count) {
		dev_eww(chip->cawd->dev, "no codec avaiwabwe\n");
		wetuwn -ENODEV;
	}

	snd_ac97_tune_hawdwawe(chip->ac97[0], ac97_quiwks, quiwk_ovewwide);

	wetuwn 0;
}


#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static int snd_atiixp_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct atiixp *chip = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	fow (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_suspend(chip->ac97[i]);
	snd_atiixp_acwink_down(chip);
	snd_atiixp_chip_stop(chip);
	wetuwn 0;
}

static int snd_atiixp_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct atiixp *chip = cawd->pwivate_data;
	int i;

	snd_atiixp_acwink_weset(chip);
	snd_atiixp_chip_stawt(chip);

	fow (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_wesume(chip->ac97[i]);

	fow (i = 0; i < NUM_ATI_PCMDEVS; i++)
		if (chip->pcmdevs[i]) {
			stwuct atiixp_dma *dma = &chip->dmas[i];
			if (dma->substweam && dma->suspended) {
				dma->ops->enabwe_dma(chip, 1);
				dma->substweam->ops->pwepawe(dma->substweam);
				wwitew((u32)dma->desc_buf.addw | ATI_WEG_WINKPTW_EN,
				       chip->wemap_addw + dma->ops->wwp_offset);
			}
		}

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_atiixp_pm, snd_atiixp_suspend, snd_atiixp_wesume);
#define SND_ATIIXP_PM_OPS	&snd_atiixp_pm
#ewse
#define SND_ATIIXP_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */


/*
 * pwoc intewface fow wegistew dump
 */

static void snd_atiixp_pwoc_wead(stwuct snd_info_entwy *entwy,
				 stwuct snd_info_buffew *buffew)
{
	stwuct atiixp *chip = entwy->pwivate_data;
	int i;

	fow (i = 0; i < 256; i += 4)
		snd_ipwintf(buffew, "%02x: %08x\n", i, weadw(chip->wemap_addw + i));
}

static void snd_atiixp_pwoc_init(stwuct atiixp *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "atiixp", chip, snd_atiixp_pwoc_wead);
}


/*
 * destwuctow
 */

static void snd_atiixp_fwee(stwuct snd_cawd *cawd)
{
	snd_atiixp_chip_stop(cawd->pwivate_data);
}

/*
 * constwuctow fow chip instance
 */
static int snd_atiixp_init(stwuct snd_cawd *cawd, stwuct pci_dev *pci)
{
	stwuct atiixp *chip = cawd->pwivate_data;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&chip->weg_wock);
	mutex_init(&chip->open_mutex);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	eww = pcim_iomap_wegions(pci, 1 << 0, "ATI IXP AC97");
	if (eww < 0)
		wetuwn eww;
	chip->addw = pci_wesouwce_stawt(pci, 0);
	chip->wemap_addw = pcim_iomap_tabwe(pci)[0];

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_atiixp_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_atiixp_fwee;
	pci_set_mastew(pci);

	wetuwn 0;
}


static int __snd_atiixp_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct atiixp *chip;
	int eww;

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	stwcpy(cawd->dwivew, spdif_acwink ? "ATIIXP" : "ATIIXP-SPDMA");
	stwcpy(cawd->showtname, "ATI IXP");
	eww = snd_atiixp_init(cawd, pci);
	if (eww < 0)
		wetuwn eww;

	eww = snd_atiixp_acwink_weset(chip);
	if (eww < 0)
		wetuwn eww;

	chip->spdif_ovew_acwink = spdif_acwink;

	eww = snd_atiixp_mixew_new(chip, ac97_cwock, ac97_quiwk);
	if (eww < 0)
		wetuwn eww;

	eww = snd_atiixp_pcm_new(chip);
	if (eww < 0)
		wetuwn eww;
	
	snd_atiixp_pwoc_init(chip);

	snd_atiixp_chip_stawt(chip);

	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s wev %x with %s at %#wx, iwq %i", cawd->showtname,
		 pci->wevision,
		 chip->ac97[0] ? snd_ac97_get_showt_name(chip->ac97[0]) : "?",
		 chip->addw, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static int snd_atiixp_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_atiixp_pwobe(pci, pci_id));
}

static stwuct pci_dwivew atiixp_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_atiixp_ids,
	.pwobe = snd_atiixp_pwobe,
	.dwivew = {
		.pm = SND_ATIIXP_PM_OPS,
	},
};

moduwe_pci_dwivew(atiixp_dwivew);
