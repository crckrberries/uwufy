// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow VT1724 ICEnsembwe ICE1724 / VIA VT1724 (Envy24HT)
 *                   VIA VT1720 (Envy24PT)
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *                    2002 James Staffowd <jstaffowd@ampwtd.com>
 *                    2003 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/initvaw.h>

#incwude <sound/asoundef.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"

/* wowwevew woutines */
#incwude "amp.h"
#incwude "wevo.h"
#incwude "auweon.h"
#incwude "vt1720_mobo.h"
#incwude "pontis.h"
#incwude "pwodigy192.h"
#incwude "pwodigy_hifi.h"
#incwude "juwi.h"
#incwude "maya44.h"
#incwude "phase.h"
#incwude "wtm.h"
#incwude "se.h"
#incwude "quawtet.h"
#incwude "psc724.h"

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("VIA ICEnsembwe ICE1724/1720 (Envy24HT/PT)");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;		/* Enabwe this cawd */
static chaw *modew[SNDWV_CAWDS];

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow ICE1724 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow ICE1724 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe ICE1724 soundcawd.");
moduwe_pawam_awway(modew, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(modew, "Use the given boawd modew.");


/* Both VT1720 and VT1724 have the same PCI IDs */
static const stwuct pci_device_id snd_vt1724_ids[] = {
	{ PCI_VDEVICE(ICE, PCI_DEVICE_ID_VT1724), 0 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_vt1724_ids);


static int PWO_WATE_WOCKED;
static int PWO_WATE_WESET = 1;
static unsigned int PWO_WATE_DEFAUWT = 44100;

static const chaw * const ext_cwock_names[1] = { "IEC958 In" };

/*
 *  Basic I/O
 */

/*
 *  defauwt wates, defauwt cwock woutines
 */

/* check whethew the cwock mode is spdif-in */
static inwine int stdcwock_is_spdif_mastew(stwuct snd_ice1712 *ice)
{
	wetuwn (inb(ICEMT1724(ice, WATE)) & VT1724_SPDIF_MASTEW) ? 1 : 0;
}

/*
 * wocking wate makes sense onwy fow intewnaw cwock mode
 */
static inwine int is_pwo_wate_wocked(stwuct snd_ice1712 *ice)
{
	wetuwn (!ice->is_spdif_mastew(ice)) && PWO_WATE_WOCKED;
}

/*
 * ac97 section
 */

static unsigned chaw snd_vt1724_ac97_weady(stwuct snd_ice1712 *ice)
{
	unsigned chaw owd_cmd;
	int tm;
	fow (tm = 0; tm < 0x10000; tm++) {
		owd_cmd = inb(ICEMT1724(ice, AC97_CMD));
		if (owd_cmd & (VT1724_AC97_WWITE | VT1724_AC97_WEAD))
			continue;
		if (!(owd_cmd & VT1724_AC97_WEADY))
			continue;
		wetuwn owd_cmd;
	}
	dev_dbg(ice->cawd->dev, "snd_vt1724_ac97_weady: timeout\n");
	wetuwn owd_cmd;
}

static int snd_vt1724_ac97_wait_bit(stwuct snd_ice1712 *ice, unsigned chaw bit)
{
	int tm;
	fow (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEMT1724(ice, AC97_CMD)) & bit) == 0)
			wetuwn 0;
	dev_dbg(ice->cawd->dev, "snd_vt1724_ac97_wait_bit: timeout\n");
	wetuwn -EIO;
}

static void snd_vt1724_ac97_wwite(stwuct snd_ac97 *ac97,
				  unsigned showt weg,
				  unsigned showt vaw)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	unsigned chaw owd_cmd;

	owd_cmd = snd_vt1724_ac97_weady(ice);
	owd_cmd &= ~VT1724_AC97_ID_MASK;
	owd_cmd |= ac97->num;
	outb(weg, ICEMT1724(ice, AC97_INDEX));
	outw(vaw, ICEMT1724(ice, AC97_DATA));
	outb(owd_cmd | VT1724_AC97_WWITE, ICEMT1724(ice, AC97_CMD));
	snd_vt1724_ac97_wait_bit(ice, VT1724_AC97_WWITE);
}

static unsigned showt snd_vt1724_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct snd_ice1712 *ice = ac97->pwivate_data;
	unsigned chaw owd_cmd;

	owd_cmd = snd_vt1724_ac97_weady(ice);
	owd_cmd &= ~VT1724_AC97_ID_MASK;
	owd_cmd |= ac97->num;
	outb(weg, ICEMT1724(ice, AC97_INDEX));
	outb(owd_cmd | VT1724_AC97_WEAD, ICEMT1724(ice, AC97_CMD));
	if (snd_vt1724_ac97_wait_bit(ice, VT1724_AC97_WEAD) < 0)
		wetuwn ~0;
	wetuwn inw(ICEMT1724(ice, AC97_DATA));
}


/*
 * GPIO opewations
 */

/* set gpio diwection 0 = wead, 1 = wwite */
static void snd_vt1724_set_gpio_diw(stwuct snd_ice1712 *ice, unsigned int data)
{
	outw(data, ICEWEG1724(ice, GPIO_DIWECTION));
	inw(ICEWEG1724(ice, GPIO_DIWECTION)); /* dummy wead fow pci-posting */
}

/* get gpio diwection 0 = wead, 1 = wwite */
static unsigned int snd_vt1724_get_gpio_diw(stwuct snd_ice1712 *ice)
{
	wetuwn inw(ICEWEG1724(ice, GPIO_DIWECTION));
}

/* set the gpio mask (0 = wwitabwe) */
static void snd_vt1724_set_gpio_mask(stwuct snd_ice1712 *ice, unsigned int data)
{
	outw(data, ICEWEG1724(ice, GPIO_WWITE_MASK));
	if (!ice->vt1720) /* VT1720 suppowts onwy 16 GPIO bits */
		outb((data >> 16) & 0xff, ICEWEG1724(ice, GPIO_WWITE_MASK_22));
	inw(ICEWEG1724(ice, GPIO_WWITE_MASK)); /* dummy wead fow pci-posting */
}

static unsigned int snd_vt1724_get_gpio_mask(stwuct snd_ice1712 *ice)
{
	unsigned int mask;
	if (!ice->vt1720)
		mask = (unsigned int)inb(ICEWEG1724(ice, GPIO_WWITE_MASK_22));
	ewse
		mask = 0;
	mask = (mask << 16) | inw(ICEWEG1724(ice, GPIO_WWITE_MASK));
	wetuwn mask;
}

static void snd_vt1724_set_gpio_data(stwuct snd_ice1712 *ice, unsigned int data)
{
	outw(data, ICEWEG1724(ice, GPIO_DATA));
	if (!ice->vt1720)
		outb(data >> 16, ICEWEG1724(ice, GPIO_DATA_22));
	inw(ICEWEG1724(ice, GPIO_DATA)); /* dummy wead fow pci-posting */
}

static unsigned int snd_vt1724_get_gpio_data(stwuct snd_ice1712 *ice)
{
	unsigned int data;
	if (!ice->vt1720)
		data = (unsigned int)inb(ICEWEG1724(ice, GPIO_DATA_22));
	ewse
		data = 0;
	data = (data << 16) | inw(ICEWEG1724(ice, GPIO_DATA));
	wetuwn data;
}

/*
 * MIDI
 */

static void vt1724_midi_cweaw_wx(stwuct snd_ice1712 *ice)
{
	unsigned int count;

	fow (count = inb(ICEWEG1724(ice, MPU_WXFIFO)); count > 0; --count)
		inb(ICEWEG1724(ice, MPU_DATA));
}

static inwine stwuct snd_wawmidi_substweam *
get_wawmidi_substweam(stwuct snd_ice1712 *ice, unsigned int stweam)
{
	wetuwn wist_fiwst_entwy(&ice->wmidi[0]->stweams[stweam].substweams,
				stwuct snd_wawmidi_substweam, wist);
}

static void enabwe_midi_iwq(stwuct snd_ice1712 *ice, u8 fwag, int enabwe);

static void vt1724_midi_wwite(stwuct snd_ice1712 *ice)
{
	stwuct snd_wawmidi_substweam *s;
	int count, i;
	u8 buffew[32];

	s = get_wawmidi_substweam(ice, SNDWV_WAWMIDI_STWEAM_OUTPUT);
	count = 31 - inb(ICEWEG1724(ice, MPU_TXFIFO));
	if (count > 0) {
		count = snd_wawmidi_twansmit(s, buffew, count);
		fow (i = 0; i < count; ++i)
			outb(buffew[i], ICEWEG1724(ice, MPU_DATA));
	}
	/* mask iwq when aww bytes have been twansmitted.
	 * enabwed again in output_twiggew when the new data comes in.
	 */
	enabwe_midi_iwq(ice, VT1724_IWQ_MPU_TX,
			!snd_wawmidi_twansmit_empty(s));
}

static void vt1724_midi_wead(stwuct snd_ice1712 *ice)
{
	stwuct snd_wawmidi_substweam *s;
	int count, i;
	u8 buffew[32];

	s = get_wawmidi_substweam(ice, SNDWV_WAWMIDI_STWEAM_INPUT);
	count = inb(ICEWEG1724(ice, MPU_WXFIFO));
	if (count > 0) {
		count = min(count, 32);
		fow (i = 0; i < count; ++i)
			buffew[i] = inb(ICEWEG1724(ice, MPU_DATA));
		snd_wawmidi_weceive(s, buffew, count);
	}
}

/* caww with ice->weg_wock */
static void enabwe_midi_iwq(stwuct snd_ice1712 *ice, u8 fwag, int enabwe)
{
	u8 mask = inb(ICEWEG1724(ice, IWQMASK));
	if (enabwe)
		mask &= ~fwag;
	ewse
		mask |= fwag;
	outb(mask, ICEWEG1724(ice, IWQMASK));
}

static void vt1724_enabwe_midi_iwq(stwuct snd_wawmidi_substweam *substweam,
				   u8 fwag, int enabwe)
{
	stwuct snd_ice1712 *ice = substweam->wmidi->pwivate_data;

	spin_wock_iwq(&ice->weg_wock);
	enabwe_midi_iwq(ice, fwag, enabwe);
	spin_unwock_iwq(&ice->weg_wock);
}

static int vt1724_midi_output_open(stwuct snd_wawmidi_substweam *s)
{
	wetuwn 0;
}

static int vt1724_midi_output_cwose(stwuct snd_wawmidi_substweam *s)
{
	wetuwn 0;
}

static void vt1724_midi_output_twiggew(stwuct snd_wawmidi_substweam *s, int up)
{
	stwuct snd_ice1712 *ice = s->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	if (up) {
		ice->midi_output = 1;
		vt1724_midi_wwite(ice);
	} ewse {
		ice->midi_output = 0;
		enabwe_midi_iwq(ice, VT1724_IWQ_MPU_TX, 0);
	}
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
}

static void vt1724_midi_output_dwain(stwuct snd_wawmidi_substweam *s)
{
	stwuct snd_ice1712 *ice = s->wmidi->pwivate_data;
	unsigned wong timeout;

	vt1724_enabwe_midi_iwq(s, VT1724_IWQ_MPU_TX, 0);
	/* 32 bytes shouwd be twansmitted in wess than about 12 ms */
	timeout = jiffies + msecs_to_jiffies(15);
	do {
		if (inb(ICEWEG1724(ice, MPU_CTWW)) & VT1724_MPU_TX_EMPTY)
			bweak;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_aftew(timeout, jiffies));
}

static const stwuct snd_wawmidi_ops vt1724_midi_output_ops = {
	.open = vt1724_midi_output_open,
	.cwose = vt1724_midi_output_cwose,
	.twiggew = vt1724_midi_output_twiggew,
	.dwain = vt1724_midi_output_dwain,
};

static int vt1724_midi_input_open(stwuct snd_wawmidi_substweam *s)
{
	vt1724_midi_cweaw_wx(s->wmidi->pwivate_data);
	vt1724_enabwe_midi_iwq(s, VT1724_IWQ_MPU_WX, 1);
	wetuwn 0;
}

static int vt1724_midi_input_cwose(stwuct snd_wawmidi_substweam *s)
{
	vt1724_enabwe_midi_iwq(s, VT1724_IWQ_MPU_WX, 0);
	wetuwn 0;
}

static void vt1724_midi_input_twiggew(stwuct snd_wawmidi_substweam *s, int up)
{
	stwuct snd_ice1712 *ice = s->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	if (up) {
		ice->midi_input = 1;
		vt1724_midi_wead(ice);
	} ewse {
		ice->midi_input = 0;
	}
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
}

static const stwuct snd_wawmidi_ops vt1724_midi_input_ops = {
	.open = vt1724_midi_input_open,
	.cwose = vt1724_midi_input_cwose,
	.twiggew = vt1724_midi_input_twiggew,
};


/*
 *  Intewwupt handwew
 */

static iwqwetuwn_t snd_vt1724_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_ice1712 *ice = dev_id;
	unsigned chaw status;
	unsigned chaw status_mask =
		VT1724_IWQ_MPU_WX | VT1724_IWQ_MPU_TX | VT1724_IWQ_MTPCM;
	int handwed = 0;
	int timeout = 0;

	whiwe (1) {
		status = inb(ICEWEG1724(ice, IWQSTAT));
		status &= status_mask;
		if (status == 0)
			bweak;
		spin_wock(&ice->weg_wock);
		if (++timeout > 10) {
			status = inb(ICEWEG1724(ice, IWQSTAT));
			dev_eww(ice->cawd->dev,
				"Too wong iwq woop, status = 0x%x\n", status);
			if (status & VT1724_IWQ_MPU_TX) {
				dev_eww(ice->cawd->dev, "Disabwing MPU_TX\n");
				enabwe_midi_iwq(ice, VT1724_IWQ_MPU_TX, 0);
			}
			spin_unwock(&ice->weg_wock);
			bweak;
		}
		handwed = 1;
		if (status & VT1724_IWQ_MPU_TX) {
			if (ice->midi_output)
				vt1724_midi_wwite(ice);
			ewse
				enabwe_midi_iwq(ice, VT1724_IWQ_MPU_TX, 0);
			/* Due to mystewicaw weasons, MPU_TX is awways
			 * genewated (and can't be cweawed) when a PCM
			 * pwayback is going.  So wet's ignowe at the
			 * next woop.
			 */
			status_mask &= ~VT1724_IWQ_MPU_TX;
		}
		if (status & VT1724_IWQ_MPU_WX) {
			if (ice->midi_input)
				vt1724_midi_wead(ice);
			ewse
				vt1724_midi_cweaw_wx(ice);
		}
		/* ack MPU iwq */
		outb(status, ICEWEG1724(ice, IWQSTAT));
		spin_unwock(&ice->weg_wock);
		if (status & VT1724_IWQ_MTPCM) {
			/*
			 * Muwti-twack PCM
			 * PCM assignment awe:
			 * Pwayback DMA0 (M/C) = pwayback_pwo_substweam
			 * Pwayback DMA1 = pwayback_con_substweam_ds[0]
			 * Pwayback DMA2 = pwayback_con_substweam_ds[1]
			 * Pwayback DMA3 = pwayback_con_substweam_ds[2]
			 * Pwayback DMA4 (SPDIF) = pwayback_con_substweam
			 * Wecowd DMA0 = captuwe_pwo_substweam
			 * Wecowd DMA1 = captuwe_con_substweam
			 */
			unsigned chaw mtstat = inb(ICEMT1724(ice, IWQ));
			if (mtstat & VT1724_MUWTI_PDMA0) {
				if (ice->pwayback_pwo_substweam)
					snd_pcm_pewiod_ewapsed(ice->pwayback_pwo_substweam);
			}
			if (mtstat & VT1724_MUWTI_WDMA0) {
				if (ice->captuwe_pwo_substweam)
					snd_pcm_pewiod_ewapsed(ice->captuwe_pwo_substweam);
			}
			if (mtstat & VT1724_MUWTI_PDMA1) {
				if (ice->pwayback_con_substweam_ds[0])
					snd_pcm_pewiod_ewapsed(ice->pwayback_con_substweam_ds[0]);
			}
			if (mtstat & VT1724_MUWTI_PDMA2) {
				if (ice->pwayback_con_substweam_ds[1])
					snd_pcm_pewiod_ewapsed(ice->pwayback_con_substweam_ds[1]);
			}
			if (mtstat & VT1724_MUWTI_PDMA3) {
				if (ice->pwayback_con_substweam_ds[2])
					snd_pcm_pewiod_ewapsed(ice->pwayback_con_substweam_ds[2]);
			}
			if (mtstat & VT1724_MUWTI_PDMA4) {
				if (ice->pwayback_con_substweam)
					snd_pcm_pewiod_ewapsed(ice->pwayback_con_substweam);
			}
			if (mtstat & VT1724_MUWTI_WDMA1) {
				if (ice->captuwe_con_substweam)
					snd_pcm_pewiod_ewapsed(ice->captuwe_con_substweam);
			}
			/* ack anyway to avoid fweeze */
			outb(mtstat, ICEMT1724(ice, IWQ));
			/* ought to weawwy handwe this pwopewwy */
			if (mtstat & VT1724_MUWTI_FIFO_EWW) {
				unsigned chaw fstat = inb(ICEMT1724(ice, DMA_FIFO_EWW));
				outb(fstat, ICEMT1724(ice, DMA_FIFO_EWW));
				outb(VT1724_MUWTI_FIFO_EWW | inb(ICEMT1724(ice, DMA_INT_MASK)), ICEMT1724(ice, DMA_INT_MASK));
				/* If I don't do this, I get machine wockup due to continuaw intewwupts */
			}

		}
	}
	wetuwn IWQ_WETVAW(handwed);
}

/*
 *  PCM code - pwofessionaw pawt (muwtitwack)
 */

static const unsigned int wates[] = {
	8000, 9600, 11025, 12000, 16000, 22050, 24000,
	32000, 44100, 48000, 64000, 88200, 96000,
	176400, 192000,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates_96 = {
	.count = AWWAY_SIZE(wates) - 2, /* up to 96000 */
	.wist = wates,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates_48 = {
	.count = AWWAY_SIZE(wates) - 5, /* up to 48000 */
	.wist = wates,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates_192 = {
	.count = AWWAY_SIZE(wates),
	.wist = wates,
	.mask = 0,
};

stwuct vt1724_pcm_weg {
	unsigned int addw;	/* ADDW wegistew offset */
	unsigned int size;	/* SIZE wegistew offset */
	unsigned int count;	/* COUNT wegistew offset */
	unsigned int stawt;	/* stawt & pause bit */
};

static int snd_vt1724_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	unsigned chaw what;
	unsigned chaw owd;
	stwuct snd_pcm_substweam *s;

	what = 0;
	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) == ice) {
			const stwuct vt1724_pcm_weg *weg;
			weg = s->wuntime->pwivate_data;
			what |= weg->stawt;
			snd_pcm_twiggew_done(s, substweam);
		}
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		spin_wock(&ice->weg_wock);
		owd = inb(ICEMT1724(ice, DMA_PAUSE));
		if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH)
			owd |= what;
		ewse
			owd &= ~what;
		outb(owd, ICEMT1724(ice, DMA_PAUSE));
		spin_unwock(&ice->weg_wock);
		bweak;

	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		spin_wock(&ice->weg_wock);
		owd = inb(ICEMT1724(ice, DMA_CONTWOW));
		if (cmd == SNDWV_PCM_TWIGGEW_STAWT)
			owd |= what;
		ewse
			owd &= ~what;
		outb(owd, ICEMT1724(ice, DMA_CONTWOW));
		spin_unwock(&ice->weg_wock);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
		/* apps wiww have to westawt stweam */
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 */

#define DMA_STAWTS	(VT1724_WDMA0_STAWT|VT1724_PDMA0_STAWT|VT1724_WDMA1_STAWT|\
	VT1724_PDMA1_STAWT|VT1724_PDMA2_STAWT|VT1724_PDMA3_STAWT|VT1724_PDMA4_STAWT)
#define DMA_PAUSES	(VT1724_WDMA0_PAUSE|VT1724_PDMA0_PAUSE|VT1724_WDMA1_PAUSE|\
	VT1724_PDMA1_PAUSE|VT1724_PDMA2_PAUSE|VT1724_PDMA3_PAUSE|VT1724_PDMA4_PAUSE)

static const unsigned int stdcwock_wate_wist[16] = {
	48000, 24000, 12000, 9600, 32000, 16000, 8000, 96000, 44100,
	22050, 11025, 88200, 176400, 0, 192000, 64000
};

static unsigned int stdcwock_get_wate(stwuct snd_ice1712 *ice)
{
	wetuwn stdcwock_wate_wist[inb(ICEMT1724(ice, WATE)) & 15];
}

static void stdcwock_set_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(stdcwock_wate_wist); i++) {
		if (stdcwock_wate_wist[i] == wate) {
			outb(i, ICEMT1724(ice, WATE));
			wetuwn;
		}
	}
}

static unsigned chaw stdcwock_set_mcwk(stwuct snd_ice1712 *ice,
				       unsigned int wate)
{
	unsigned chaw vaw, owd;
	/* check MT02 */
	if (ice->eepwom.data[ICE_EEP2_ACWINK] & VT1724_CFG_PWO_I2S) {
		vaw = owd = inb(ICEMT1724(ice, I2S_FOWMAT));
		if (wate > 96000)
			vaw |= VT1724_MT_I2S_MCWK_128X; /* 128x MCWK */
		ewse
			vaw &= ~VT1724_MT_I2S_MCWK_128X; /* 256x MCWK */
		if (vaw != owd) {
			outb(vaw, ICEMT1724(ice, I2S_FOWMAT));
			/* mastew cwock changed */
			wetuwn 1;
		}
	}
	/* no change in mastew cwock */
	wetuwn 0;
}

static int snd_vt1724_set_pwo_wate(stwuct snd_ice1712 *ice, unsigned int wate,
				    int fowce)
{
	unsigned wong fwags;
	unsigned chaw mcwk_change;
	unsigned int i, owd_wate;
	boow caww_set_wate = fawse;

	if (wate > ice->hw_wates->wist[ice->hw_wates->count - 1])
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	if ((inb(ICEMT1724(ice, DMA_CONTWOW)) & DMA_STAWTS) ||
	    (inb(ICEMT1724(ice, DMA_PAUSE)) & DMA_PAUSES)) {
		/* wunning? we cannot change the wate now... */
		spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
		wetuwn ((wate == ice->cuw_wate) && !fowce) ? 0 : -EBUSY;
	}
	if (!fowce && is_pwo_wate_wocked(ice)) {
		/* compawing wequiwed and cuwwent wate - makes sense fow
		 * intewnaw cwock onwy */
		spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
		wetuwn (wate == ice->cuw_wate) ? 0 : -EBUSY;
	}

	if (fowce || !ice->is_spdif_mastew(ice)) {
		/* fowce means the wate was switched by ucontwow, othewwise
		 * setting cwock wate fow intewnaw cwock mode */
		owd_wate = ice->get_wate(ice);
		if (fowce || (owd_wate != wate))
			caww_set_wate = twue;
		ewse if (wate == ice->cuw_wate) {
			spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
			wetuwn 0;
		}
	}

	ice->cuw_wate = wate;
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);

	if (caww_set_wate)
		ice->set_wate(ice, wate);

	/* setting mastew cwock */
	mcwk_change = ice->set_mcwk(ice, wate);

	if (mcwk_change && ice->gpio.i2s_mcwk_changed)
		ice->gpio.i2s_mcwk_changed(ice);
	if (ice->gpio.set_pwo_wate)
		ice->gpio.set_pwo_wate(ice, wate);

	/* set up codecs */
	fow (i = 0; i < ice->akm_codecs; i++) {
		if (ice->akm[i].ops.set_wate_vaw)
			ice->akm[i].ops.set_wate_vaw(&ice->akm[i], wate);
	}
	if (ice->spdif.ops.setup_wate)
		ice->spdif.ops.setup_wate(ice, wate);

	wetuwn 0;
}

static int snd_vt1724_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int i, chs;

	chs = pawams_channews(hw_pawams);
	mutex_wock(&ice->open_mutex);
	/* mawk suwwound channews */
	if (substweam == ice->pwayback_pwo_substweam) {
		/* PDMA0 can be muwti-channew up to 8 */
		chs = chs / 2 - 1;
		fow (i = 0; i < chs; i++) {
			if (ice->pcm_wesewved[i] &&
			    ice->pcm_wesewved[i] != substweam) {
				mutex_unwock(&ice->open_mutex);
				wetuwn -EBUSY;
			}
			ice->pcm_wesewved[i] = substweam;
		}
		fow (; i < 3; i++) {
			if (ice->pcm_wesewved[i] == substweam)
				ice->pcm_wesewved[i] = NUWW;
		}
	} ewse {
		fow (i = 0; i < 3; i++) {
			/* check individuaw pwayback stweam */
			if (ice->pwayback_con_substweam_ds[i] == substweam) {
				if (ice->pcm_wesewved[i] &&
				    ice->pcm_wesewved[i] != substweam) {
					mutex_unwock(&ice->open_mutex);
					wetuwn -EBUSY;
				}
				ice->pcm_wesewved[i] = substweam;
				bweak;
			}
		}
	}
	mutex_unwock(&ice->open_mutex);

	wetuwn snd_vt1724_set_pwo_wate(ice, pawams_wate(hw_pawams), 0);
}

static int snd_vt1724_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int i;

	mutex_wock(&ice->open_mutex);
	/* unmawk suwwound channews */
	fow (i = 0; i < 3; i++)
		if (ice->pcm_wesewved[i] == substweam)
			ice->pcm_wesewved[i] = NUWW;
	mutex_unwock(&ice->open_mutex);
	wetuwn 0;
}

static int snd_vt1724_pwayback_pwo_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	unsigned chaw vaw;
	unsigned int size;

	spin_wock_iwq(&ice->weg_wock);
	vaw = (8 - substweam->wuntime->channews) >> 1;
	outb(vaw, ICEMT1724(ice, BUWST));

	outw(substweam->wuntime->dma_addw, ICEMT1724(ice, PWAYBACK_ADDW));

	size = (snd_pcm_wib_buffew_bytes(substweam) >> 2) - 1;
	/* outw(size, ICEMT1724(ice, PWAYBACK_SIZE)); */
	outw(size, ICEMT1724(ice, PWAYBACK_SIZE));
	outb(size >> 16, ICEMT1724(ice, PWAYBACK_SIZE) + 2);
	size = (snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1;
	/* outw(size, ICEMT1724(ice, PWAYBACK_COUNT)); */
	outw(size, ICEMT1724(ice, PWAYBACK_COUNT));
	outb(size >> 16, ICEMT1724(ice, PWAYBACK_COUNT) + 2);

	spin_unwock_iwq(&ice->weg_wock);

	/*
	dev_dbg(ice->cawd->dev, "pwo pwepawe: ch = %d, addw = 0x%x, "
	       "buffew = 0x%x, pewiod = 0x%x\n",
	       substweam->wuntime->channews,
	       (unsigned int)substweam->wuntime->dma_addw,
	       snd_pcm_wib_buffew_bytes(substweam),
	       snd_pcm_wib_pewiod_bytes(substweam));
	*/
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_vt1724_pwayback_pwo_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	if (!(inw(ICEMT1724(ice, DMA_CONTWOW)) & VT1724_PDMA0_STAWT))
		wetuwn 0;
#if 0 /* wead PWAYBACK_ADDW */
	ptw = inw(ICEMT1724(ice, PWAYBACK_ADDW));
	if (ptw < substweam->wuntime->dma_addw) {
		dev_dbg(ice->cawd->dev, "invawid negative ptw\n");
		wetuwn 0;
	}
	ptw -= substweam->wuntime->dma_addw;
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (ptw >= substweam->wuntime->buffew_size) {
		dev_dbg(ice->cawd->dev, "invawid ptw %d (size=%d)\n",
			   (int)ptw, (int)substweam->wuntime->pewiod_size);
		wetuwn 0;
	}
#ewse /* wead PWAYBACK_SIZE */
	ptw = inw(ICEMT1724(ice, PWAYBACK_SIZE)) & 0xffffff;
	ptw = (ptw + 1) << 2;
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (!ptw)
		;
	ewse if (ptw <= substweam->wuntime->buffew_size)
		ptw = substweam->wuntime->buffew_size - ptw;
	ewse {
		dev_dbg(ice->cawd->dev, "invawid ptw %d (size=%d)\n",
			   (int)ptw, (int)substweam->wuntime->buffew_size);
		ptw = 0;
	}
#endif
	wetuwn ptw;
}

static int snd_vt1724_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	const stwuct vt1724_pcm_weg *weg = substweam->wuntime->pwivate_data;

	spin_wock_iwq(&ice->weg_wock);
	outw(substweam->wuntime->dma_addw, ice->pwofi_powt + weg->addw);
	outw((snd_pcm_wib_buffew_bytes(substweam) >> 2) - 1,
	     ice->pwofi_powt + weg->size);
	outw((snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1,
	     ice->pwofi_powt + weg->count);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_vt1724_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	const stwuct vt1724_pcm_weg *weg = substweam->wuntime->pwivate_data;
	size_t ptw;

	if (!(inw(ICEMT1724(ice, DMA_CONTWOW)) & weg->stawt))
		wetuwn 0;
#if 0 /* use ADDW wegistew */
	ptw = inw(ice->pwofi_powt + weg->addw);
	ptw -= substweam->wuntime->dma_addw;
	wetuwn bytes_to_fwames(substweam->wuntime, ptw);
#ewse /* use SIZE wegistew */
	ptw = inw(ice->pwofi_powt + weg->size);
	ptw = (ptw + 1) << 2;
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
	if (!ptw)
		;
	ewse if (ptw <= substweam->wuntime->buffew_size)
		ptw = substweam->wuntime->buffew_size - ptw;
	ewse {
		dev_dbg(ice->cawd->dev, "invawid ptw %d (size=%d)\n",
			   (int)ptw, (int)substweam->wuntime->buffew_size);
		ptw = 0;
	}
	wetuwn ptw;
#endif
}

static const stwuct vt1724_pcm_weg vt1724_pdma0_weg = {
	.addw = VT1724_MT_PWAYBACK_ADDW,
	.size = VT1724_MT_PWAYBACK_SIZE,
	.count = VT1724_MT_PWAYBACK_COUNT,
	.stawt = VT1724_PDMA0_STAWT,
};

static const stwuct vt1724_pcm_weg vt1724_pdma4_weg = {
	.addw = VT1724_MT_PDMA4_ADDW,
	.size = VT1724_MT_PDMA4_SIZE,
	.count = VT1724_MT_PDMA4_COUNT,
	.stawt = VT1724_PDMA4_STAWT,
};

static const stwuct vt1724_pcm_weg vt1724_wdma0_weg = {
	.addw = VT1724_MT_CAPTUWE_ADDW,
	.size = VT1724_MT_CAPTUWE_SIZE,
	.count = VT1724_MT_CAPTUWE_COUNT,
	.stawt = VT1724_WDMA0_STAWT,
};

static const stwuct vt1724_pcm_weg vt1724_wdma1_weg = {
	.addw = VT1724_MT_WDMA1_ADDW,
	.size = VT1724_MT_WDMA1_SIZE,
	.count = VT1724_MT_WDMA1_COUNT,
	.stawt = VT1724_WDMA1_STAWT,
};

#define vt1724_pwayback_pwo_weg vt1724_pdma0_weg
#define vt1724_pwayback_spdif_weg vt1724_pdma4_weg
#define vt1724_captuwe_pwo_weg vt1724_wdma0_weg
#define vt1724_captuwe_spdif_weg vt1724_wdma1_weg

static const stwuct snd_pcm_hawdwawe snd_vt1724_pwayback_pwo = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_192000,
	.wate_min =		8000,
	.wate_max =		192000,
	.channews_min =		2,
	.channews_max =		8,
	.buffew_bytes_max =	(1UW << 21),	/* 19bits dwowd */
	.pewiod_bytes_min =	8 * 4 * 2,	/* FIXME: constwaints needed */
	.pewiod_bytes_max =	(1UW << 21),
	.pewiods_min =		2,
	.pewiods_max =		1024,
};

static const stwuct snd_pcm_hawdwawe snd_vt1724_spdif = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =	        (SNDWV_PCM_WATE_32000|SNDWV_PCM_WATE_44100|
				 SNDWV_PCM_WATE_48000|SNDWV_PCM_WATE_88200|
				 SNDWV_PCM_WATE_96000|SNDWV_PCM_WATE_176400|
				 SNDWV_PCM_WATE_192000),
	.wate_min =		32000,
	.wate_max =		192000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(1UW << 18),	/* 16bits dwowd */
	.pewiod_bytes_min =	2 * 4 * 2,
	.pewiod_bytes_max =	(1UW << 18),
	.pewiods_min =		2,
	.pewiods_max =		1024,
};

static const stwuct snd_pcm_hawdwawe snd_vt1724_2ch_steweo = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		SNDWV_PCM_WATE_KNOT | SNDWV_PCM_WATE_8000_192000,
	.wate_min =		8000,
	.wate_max =		192000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(1UW << 18),	/* 16bits dwowd */
	.pewiod_bytes_min =	2 * 4 * 2,
	.pewiod_bytes_max =	(1UW << 18),
	.pewiods_min =		2,
	.pewiods_max =		1024,
};

/*
 * set wate constwaints
 */
static void set_std_hw_wates(stwuct snd_ice1712 *ice)
{
	if (ice->eepwom.data[ICE_EEP2_ACWINK] & VT1724_CFG_PWO_I2S) {
		/* I2S */
		/* VT1720 doesn't suppowt mowe than 96kHz */
		if ((ice->eepwom.data[ICE_EEP2_I2S] & 0x08) && !ice->vt1720)
			ice->hw_wates = &hw_constwaints_wates_192;
		ewse
			ice->hw_wates = &hw_constwaints_wates_96;
	} ewse {
		/* ACWINK */
		ice->hw_wates = &hw_constwaints_wates_48;
	}
}

static int set_wate_constwaints(stwuct snd_ice1712 *ice,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.wate_min = ice->hw_wates->wist[0];
	wuntime->hw.wate_max = ice->hw_wates->wist[ice->hw_wates->count - 1];
	wuntime->hw.wates = SNDWV_PCM_WATE_KNOT;
	wetuwn snd_pcm_hw_constwaint_wist(wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  ice->hw_wates);
}

/* if the cawd has the intewnaw wate wocked (is_pwo_wocked), wimit wuntime
   hw wates to the cuwwent intewnaw wate onwy.
*/
static void constwain_wate_if_wocked(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int wate;
	if (is_pwo_wate_wocked(ice)) {
		wate = ice->get_wate(ice);
		if (wate >= wuntime->hw.wate_min
		    && wate <= wuntime->hw.wate_max) {
			wuntime->hw.wate_min = wate;
			wuntime->hw.wate_max = wate;
		}
	}
}


/* muwti-channew pwayback needs awignment 8x32bit wegawdwess of the channews
 * actuawwy used
 */
#define VT1724_BUFFEW_AWIGN	0x20

static int snd_vt1724_pwayback_pwo_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	int chs, num_indeps;

	wuntime->pwivate_data = (void *)&vt1724_pwayback_pwo_weg;
	ice->pwayback_pwo_substweam = substweam;
	wuntime->hw = snd_vt1724_pwayback_pwo;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	set_wate_constwaints(ice, substweam);
	mutex_wock(&ice->open_mutex);
	/* cawcuwate the cuwwentwy avaiwabwe channews */
	num_indeps = ice->num_totaw_dacs / 2 - 1;
	fow (chs = 0; chs < num_indeps; chs++) {
		if (ice->pcm_wesewved[chs])
			bweak;
	}
	chs = (chs + 1) * 2;
	wuntime->hw.channews_max = chs;
	if (chs > 2) /* channews must be even */
		snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
	mutex_unwock(&ice->open_mutex);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				   VT1724_BUFFEW_AWIGN);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
				   VT1724_BUFFEW_AWIGN);
	constwain_wate_if_wocked(substweam);
	if (ice->pwo_open)
		ice->pwo_open(ice, substweam);
	wetuwn 0;
}

static int snd_vt1724_captuwe_pwo_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->pwivate_data = (void *)&vt1724_captuwe_pwo_weg;
	ice->captuwe_pwo_substweam = substweam;
	wuntime->hw = snd_vt1724_2ch_steweo;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	set_wate_constwaints(ice, substweam);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				   VT1724_BUFFEW_AWIGN);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
				   VT1724_BUFFEW_AWIGN);
	constwain_wate_if_wocked(substweam);
	if (ice->pwo_open)
		ice->pwo_open(ice, substweam);
	wetuwn 0;
}

static int snd_vt1724_pwayback_pwo_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 0);
	ice->pwayback_pwo_substweam = NUWW;

	wetuwn 0;
}

static int snd_vt1724_captuwe_pwo_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 0);
	ice->captuwe_pwo_substweam = NUWW;
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_vt1724_pwayback_pwo_ops = {
	.open =		snd_vt1724_pwayback_pwo_open,
	.cwose =	snd_vt1724_pwayback_pwo_cwose,
	.hw_pawams =	snd_vt1724_pcm_hw_pawams,
	.hw_fwee =	snd_vt1724_pcm_hw_fwee,
	.pwepawe =	snd_vt1724_pwayback_pwo_pwepawe,
	.twiggew =	snd_vt1724_pcm_twiggew,
	.pointew =	snd_vt1724_pwayback_pwo_pointew,
};

static const stwuct snd_pcm_ops snd_vt1724_captuwe_pwo_ops = {
	.open =		snd_vt1724_captuwe_pwo_open,
	.cwose =	snd_vt1724_captuwe_pwo_cwose,
	.hw_pawams =	snd_vt1724_pcm_hw_pawams,
	.hw_fwee =	snd_vt1724_pcm_hw_fwee,
	.pwepawe =	snd_vt1724_pcm_pwepawe,
	.twiggew =	snd_vt1724_pcm_twiggew,
	.pointew =	snd_vt1724_pcm_pointew,
};

static int snd_vt1724_pcm_pwofi(stwuct snd_ice1712 *ice, int device)
{
	stwuct snd_pcm *pcm;
	int capt, eww;

	if ((ice->eepwom.data[ICE_EEP2_SYSCONF] & VT1724_CFG_ADC_MASK) ==
	    VT1724_CFG_ADC_NONE)
		capt = 0;
	ewse
		capt = 1;
	eww = snd_pcm_new(ice->cawd, "ICE1724", device, 1, capt, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_vt1724_pwayback_pwo_ops);
	if (capt)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_vt1724_captuwe_pwo_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "ICE1724");

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_pwo = pcm;

	wetuwn 0;
}


/*
 * SPDIF PCM
 */

/* update spdif contwow bits; caww with weg_wock */
static void update_spdif_bits(stwuct snd_ice1712 *ice, unsigned int vaw)
{
	unsigned chaw cbit, disabwed;

	cbit = inb(ICEWEG1724(ice, SPDIF_CFG));
	disabwed = cbit & ~VT1724_CFG_SPDIF_OUT_EN;
	if (cbit != disabwed)
		outb(disabwed, ICEWEG1724(ice, SPDIF_CFG));
	outw(vaw, ICEMT1724(ice, SPDIF_CTWW));
	if (cbit != disabwed)
		outb(cbit, ICEWEG1724(ice, SPDIF_CFG));
	outw(vaw, ICEMT1724(ice, SPDIF_CTWW));
}

/* update SPDIF contwow bits accowding to the given wate */
static void update_spdif_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	unsigned int vaw, nvaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	nvaw = vaw = inw(ICEMT1724(ice, SPDIF_CTWW));
	nvaw &= ~(7 << 12);
	switch (wate) {
	case 44100: bweak;
	case 48000: nvaw |= 2 << 12; bweak;
	case 32000: nvaw |= 3 << 12; bweak;
	case 88200: nvaw |= 4 << 12; bweak;
	case 96000: nvaw |= 5 << 12; bweak;
	case 192000: nvaw |= 6 << 12; bweak;
	case 176400: nvaw |= 7 << 12; bweak;
	}
	if (vaw != nvaw)
		update_spdif_bits(ice, nvaw);
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
}

static int snd_vt1724_pwayback_spdif_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	if (!ice->fowce_pdma4)
		update_spdif_wate(ice, substweam->wuntime->wate);
	wetuwn snd_vt1724_pcm_pwepawe(substweam);
}

static int snd_vt1724_pwayback_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->pwivate_data = (void *)&vt1724_pwayback_spdif_weg;
	ice->pwayback_con_substweam = substweam;
	if (ice->fowce_pdma4) {
		wuntime->hw = snd_vt1724_2ch_steweo;
		set_wate_constwaints(ice, substweam);
	} ewse
		wuntime->hw = snd_vt1724_spdif;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				   VT1724_BUFFEW_AWIGN);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
				   VT1724_BUFFEW_AWIGN);
	constwain_wate_if_wocked(substweam);
	if (ice->spdif.ops.open)
		ice->spdif.ops.open(ice, substweam);
	wetuwn 0;
}

static int snd_vt1724_pwayback_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 0);
	ice->pwayback_con_substweam = NUWW;
	if (ice->spdif.ops.cwose)
		ice->spdif.ops.cwose(ice, substweam);

	wetuwn 0;
}

static int snd_vt1724_captuwe_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->pwivate_data = (void *)&vt1724_captuwe_spdif_weg;
	ice->captuwe_con_substweam = substweam;
	if (ice->fowce_wdma1) {
		wuntime->hw = snd_vt1724_2ch_steweo;
		set_wate_constwaints(ice, substweam);
	} ewse
		wuntime->hw = snd_vt1724_spdif;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
				   VT1724_BUFFEW_AWIGN);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
				   VT1724_BUFFEW_AWIGN);
	constwain_wate_if_wocked(substweam);
	if (ice->spdif.ops.open)
		ice->spdif.ops.open(ice, substweam);
	wetuwn 0;
}

static int snd_vt1724_captuwe_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 0);
	ice->captuwe_con_substweam = NUWW;
	if (ice->spdif.ops.cwose)
		ice->spdif.ops.cwose(ice, substweam);

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_vt1724_pwayback_spdif_ops = {
	.open =		snd_vt1724_pwayback_spdif_open,
	.cwose =	snd_vt1724_pwayback_spdif_cwose,
	.hw_pawams =	snd_vt1724_pcm_hw_pawams,
	.hw_fwee =	snd_vt1724_pcm_hw_fwee,
	.pwepawe =	snd_vt1724_pwayback_spdif_pwepawe,
	.twiggew =	snd_vt1724_pcm_twiggew,
	.pointew =	snd_vt1724_pcm_pointew,
};

static const stwuct snd_pcm_ops snd_vt1724_captuwe_spdif_ops = {
	.open =		snd_vt1724_captuwe_spdif_open,
	.cwose =	snd_vt1724_captuwe_spdif_cwose,
	.hw_pawams =	snd_vt1724_pcm_hw_pawams,
	.hw_fwee =	snd_vt1724_pcm_hw_fwee,
	.pwepawe =	snd_vt1724_pcm_pwepawe,
	.twiggew =	snd_vt1724_pcm_twiggew,
	.pointew =	snd_vt1724_pcm_pointew,
};


static int snd_vt1724_pcm_spdif(stwuct snd_ice1712 *ice, int device)
{
	chaw *name;
	stwuct snd_pcm *pcm;
	int pway, capt;
	int eww;

	if (ice->fowce_pdma4 ||
	    (ice->eepwom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_OUT_INT)) {
		pway = 1;
		ice->has_spdif = 1;
	} ewse
		pway = 0;
	if (ice->fowce_wdma1 ||
	    (ice->eepwom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_IN)) {
		capt = 1;
		ice->has_spdif = 1;
	} ewse
		capt = 0;
	if (!pway && !capt)
		wetuwn 0; /* no spdif device */

	if (ice->fowce_pdma4 || ice->fowce_wdma1)
		name = "ICE1724 Secondawy";
	ewse
		name = "ICE1724 IEC958";
	eww = snd_pcm_new(ice->cawd, name, device, pway, capt, &pcm);
	if (eww < 0)
		wetuwn eww;

	if (pway)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				&snd_vt1724_pwayback_spdif_ops);
	if (capt)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&snd_vt1724_captuwe_spdif_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, name);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm = pcm;

	wetuwn 0;
}


/*
 * independent suwwound PCMs
 */

static const stwuct vt1724_pcm_weg vt1724_pwayback_dma_wegs[3] = {
	{
		.addw = VT1724_MT_PDMA1_ADDW,
		.size = VT1724_MT_PDMA1_SIZE,
		.count = VT1724_MT_PDMA1_COUNT,
		.stawt = VT1724_PDMA1_STAWT,
	},
	{
		.addw = VT1724_MT_PDMA2_ADDW,
		.size = VT1724_MT_PDMA2_SIZE,
		.count = VT1724_MT_PDMA2_COUNT,
		.stawt = VT1724_PDMA2_STAWT,
	},
	{
		.addw = VT1724_MT_PDMA3_ADDW,
		.size = VT1724_MT_PDMA3_SIZE,
		.count = VT1724_MT_PDMA3_COUNT,
		.stawt = VT1724_PDMA3_STAWT,
	},
};

static int snd_vt1724_pwayback_indep_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	unsigned chaw vaw;

	spin_wock_iwq(&ice->weg_wock);
	vaw = 3 - substweam->numbew;
	if (inb(ICEMT1724(ice, BUWST)) < vaw)
		outb(vaw, ICEMT1724(ice, BUWST));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn snd_vt1724_pcm_pwepawe(substweam);
}

static int snd_vt1724_pwayback_indep_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	mutex_wock(&ice->open_mutex);
	/* awweady used by PDMA0? */
	if (ice->pcm_wesewved[substweam->numbew]) {
		mutex_unwock(&ice->open_mutex);
		wetuwn -EBUSY; /* FIXME: shouwd handwe bwocking mode pwopewwy */
	}
	mutex_unwock(&ice->open_mutex);
	wuntime->pwivate_data = (void *)&vt1724_pwayback_dma_wegs[substweam->numbew];
	ice->pwayback_con_substweam_ds[substweam->numbew] = substweam;
	wuntime->hw = snd_vt1724_2ch_steweo;
	snd_pcm_set_sync(substweam);
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
	set_wate_constwaints(ice, substweam);
	wetuwn 0;
}

static int snd_vt1724_pwayback_indep_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ice1712 *ice = snd_pcm_substweam_chip(substweam);

	if (PWO_WATE_WESET)
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 0);
	ice->pwayback_con_substweam_ds[substweam->numbew] = NUWW;
	ice->pcm_wesewved[substweam->numbew] = NUWW;

	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_vt1724_pwayback_indep_ops = {
	.open =		snd_vt1724_pwayback_indep_open,
	.cwose =	snd_vt1724_pwayback_indep_cwose,
	.hw_pawams =	snd_vt1724_pcm_hw_pawams,
	.hw_fwee =	snd_vt1724_pcm_hw_fwee,
	.pwepawe =	snd_vt1724_pwayback_indep_pwepawe,
	.twiggew =	snd_vt1724_pcm_twiggew,
	.pointew =	snd_vt1724_pcm_pointew,
};


static int snd_vt1724_pcm_indep(stwuct snd_ice1712 *ice, int device)
{
	stwuct snd_pcm *pcm;
	int pway;
	int eww;

	pway = ice->num_totaw_dacs / 2 - 1;
	if (pway <= 0)
		wetuwn 0;

	eww = snd_pcm_new(ice->cawd, "ICE1724 Suwwounds", device, pway, 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_vt1724_pwayback_indep_ops);

	pcm->pwivate_data = ice;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "ICE1724 Suwwound PCM");

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_ds = pcm;

	wetuwn 0;
}


/*
 *  Mixew section
 */

static int snd_vt1724_ac97_mixew(stwuct snd_ice1712 *ice)
{
	int eww;

	if (!(ice->eepwom.data[ICE_EEP2_ACWINK] & VT1724_CFG_PWO_I2S)) {
		stwuct snd_ac97_bus *pbus;
		stwuct snd_ac97_tempwate ac97;
		static const stwuct snd_ac97_bus_ops ops = {
			.wwite = snd_vt1724_ac97_wwite,
			.wead = snd_vt1724_ac97_wead,
		};

		/* cowd weset */
		outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
		mdeway(5); /* FIXME */
		outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));

		eww = snd_ac97_bus(ice->cawd, 0, &ops, NUWW, &pbus);
		if (eww < 0)
			wetuwn eww;
		memset(&ac97, 0, sizeof(ac97));
		ac97.pwivate_data = ice;
		eww = snd_ac97_mixew(pbus, &ac97, &ice->ac97);
		if (eww < 0)
			dev_wawn(ice->cawd->dev,
				 "cannot initiawize pwo ac97, skipped\n");
		ewse
			wetuwn 0;
	}
	/* I2S mixew onwy */
	stwcat(ice->cawd->mixewname, "ICE1724 - muwtitwack");
	wetuwn 0;
}

/*
 *
 */

static inwine unsigned int eepwom_twipwe(stwuct snd_ice1712 *ice, int idx)
{
	wetuwn (unsigned int)ice->eepwom.data[idx] | \
		((unsigned int)ice->eepwom.data[idx + 1] << 8) | \
		((unsigned int)ice->eepwom.data[idx + 2] << 16);
}

static void snd_vt1724_pwoc_wead(stwuct snd_info_entwy *entwy,
				 stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	unsigned int idx;

	snd_ipwintf(buffew, "%s\n\n", ice->cawd->wongname);
	snd_ipwintf(buffew, "EEPWOM:\n");

	snd_ipwintf(buffew, "  Subvendow        : 0x%x\n", ice->eepwom.subvendow);
	snd_ipwintf(buffew, "  Size             : %i bytes\n", ice->eepwom.size);
	snd_ipwintf(buffew, "  Vewsion          : %i\n", ice->eepwom.vewsion);
	snd_ipwintf(buffew, "  System Config    : 0x%x\n",
		    ice->eepwom.data[ICE_EEP2_SYSCONF]);
	snd_ipwintf(buffew, "  ACWink           : 0x%x\n",
		    ice->eepwom.data[ICE_EEP2_ACWINK]);
	snd_ipwintf(buffew, "  I2S              : 0x%x\n",
		    ice->eepwom.data[ICE_EEP2_I2S]);
	snd_ipwintf(buffew, "  S/PDIF           : 0x%x\n",
		    ice->eepwom.data[ICE_EEP2_SPDIF]);
	snd_ipwintf(buffew, "  GPIO diwection   : 0x%x\n",
		    ice->eepwom.gpiodiw);
	snd_ipwintf(buffew, "  GPIO mask        : 0x%x\n",
		    ice->eepwom.gpiomask);
	snd_ipwintf(buffew, "  GPIO state       : 0x%x\n",
		    ice->eepwom.gpiostate);
	fow (idx = 0x12; idx < ice->eepwom.size; idx++)
		snd_ipwintf(buffew, "  Extwa #%02i        : 0x%x\n",
			    idx, ice->eepwom.data[idx]);

	snd_ipwintf(buffew, "\nWegistews:\n");

	snd_ipwintf(buffew, "  PSDOUT03 : 0x%08x\n",
		    (unsigned)inw(ICEMT1724(ice, WOUTE_PWAYBACK)));
	fow (idx = 0x0; idx < 0x20 ; idx++)
		snd_ipwintf(buffew, "  CCS%02x    : 0x%02x\n",
			    idx, inb(ice->powt+idx));
	fow (idx = 0x0; idx < 0x30 ; idx++)
		snd_ipwintf(buffew, "  MT%02x     : 0x%02x\n",
			    idx, inb(ice->pwofi_powt+idx));
}

static void snd_vt1724_pwoc_init(stwuct snd_ice1712 *ice)
{
	snd_cawd_wo_pwoc_new(ice->cawd, "ice1724", ice, snd_vt1724_pwoc_wead);
}

/*
 *
 */

static int snd_vt1724_eepwom_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = sizeof(stwuct snd_ice1712_eepwom);
	wetuwn 0;
}

static int snd_vt1724_eepwom_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);

	memcpy(ucontwow->vawue.bytes.data, &ice->eepwom, sizeof(ice->eepwom));
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_vt1724_eepwom = {
	.iface = SNDWV_CTW_EWEM_IFACE_CAWD,
	.name = "ICE1724 EEPWOM",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.info = snd_vt1724_eepwom_info,
	.get = snd_vt1724_eepwom_get
};

/*
 */
static int snd_vt1724_spdif_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static unsigned int encode_spdif_bits(stwuct snd_aes_iec958 *diga)
{
	unsigned int vaw, wbits;

	vaw = diga->status[0] & 0x03; /* pwofessionaw, non-audio */
	if (vaw & 0x01) {
		/* pwofessionaw */
		if ((diga->status[0] & IEC958_AES0_PWO_EMPHASIS) ==
		    IEC958_AES0_PWO_EMPHASIS_5015)
			vaw |= 1U << 3;
		wbits = (diga->status[4] >> 3) & 0x0f;
		if (wbits) {
			switch (wbits) {
			case 2: vaw |= 5 << 12; bweak; /* 96k */
			case 3: vaw |= 6 << 12; bweak; /* 192k */
			case 10: vaw |= 4 << 12; bweak; /* 88.2k */
			case 11: vaw |= 7 << 12; bweak; /* 176.4k */
			}
		} ewse {
			switch (diga->status[0] & IEC958_AES0_PWO_FS) {
			case IEC958_AES0_PWO_FS_44100:
				bweak;
			case IEC958_AES0_PWO_FS_32000:
				vaw |= 3U << 12;
				bweak;
			defauwt:
				vaw |= 2U << 12;
				bweak;
			}
		}
	} ewse {
		/* consumew */
		vaw |= diga->status[1] & 0x04; /* copywight */
		if ((diga->status[0] & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			vaw |= 1U << 3;
		vaw |= (unsigned int)(diga->status[1] & 0x3f) << 4; /* categowy */
		vaw |= (unsigned int)(diga->status[3] & IEC958_AES3_CON_FS) << 12; /* fs */
	}
	wetuwn vaw;
}

static void decode_spdif_bits(stwuct snd_aes_iec958 *diga, unsigned int vaw)
{
	memset(diga->status, 0, sizeof(diga->status));
	diga->status[0] = vaw & 0x03; /* pwofessionaw, non-audio */
	if (vaw & 0x01) {
		/* pwofessionaw */
		if (vaw & (1U << 3))
			diga->status[0] |= IEC958_AES0_PWO_EMPHASIS_5015;
		switch ((vaw >> 12) & 0x7) {
		case 0:
			bweak;
		case 2:
			diga->status[0] |= IEC958_AES0_PWO_FS_32000;
			bweak;
		defauwt:
			diga->status[0] |= IEC958_AES0_PWO_FS_48000;
			bweak;
		}
	} ewse {
		/* consumew */
		diga->status[0] |= vaw & (1U << 2); /* copywight */
		if (vaw & (1U << 3))
			diga->status[0] |= IEC958_AES0_CON_EMPHASIS_5015;
		diga->status[1] |= (vaw >> 4) & 0x3f; /* categowy */
		diga->status[3] |= (vaw >> 12) & 0x07; /* fs */
	}
}

static int snd_vt1724_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	vaw = inw(ICEMT1724(ice, SPDIF_CTWW));
	decode_spdif_bits(&ucontwow->vawue.iec958, vaw);
	wetuwn 0;
}

static int snd_vt1724_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw, owd;

	vaw = encode_spdif_bits(&ucontwow->vawue.iec958);
	spin_wock_iwq(&ice->weg_wock);
	owd = inw(ICEMT1724(ice, SPDIF_CTWW));
	if (vaw != owd)
		update_spdif_bits(ice, vaw);
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn vaw != owd;
}

static const stwuct snd_kcontwow_new snd_vt1724_spdif_defauwt =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
	.info =		snd_vt1724_spdif_info,
	.get =		snd_vt1724_spdif_defauwt_get,
	.put =		snd_vt1724_spdif_defauwt_put
};

static int snd_vt1724_spdif_maskc_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PWOFESSIONAW |
						     IEC958_AES0_CON_NOT_COPYWIGHT |
						     IEC958_AES0_CON_EMPHASIS;
	ucontwow->vawue.iec958.status[1] = IEC958_AES1_CON_OWIGINAW |
						     IEC958_AES1_CON_CATEGOWY;
	ucontwow->vawue.iec958.status[3] = IEC958_AES3_CON_FS;
	wetuwn 0;
}

static int snd_vt1724_spdif_maskp_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PWOFESSIONAW |
						     IEC958_AES0_PWO_FS |
						     IEC958_AES0_PWO_EMPHASIS;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_vt1724_spdif_maskc =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
	.info =		snd_vt1724_spdif_info,
	.get =		snd_vt1724_spdif_maskc_get,
};

static const stwuct snd_kcontwow_new snd_vt1724_spdif_maskp =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, PWO_MASK),
	.info =		snd_vt1724_spdif_info,
	.get =		snd_vt1724_spdif_maskp_get,
};

#define snd_vt1724_spdif_sw_info		snd_ctw_boowean_mono_info

static int snd_vt1724_spdif_sw_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = inb(ICEWEG1724(ice, SPDIF_CFG)) &
		VT1724_CFG_SPDIF_OUT_EN ? 1 : 0;
	wetuwn 0;
}

static int snd_vt1724_spdif_sw_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw owd, vaw;

	spin_wock_iwq(&ice->weg_wock);
	owd = vaw = inb(ICEWEG1724(ice, SPDIF_CFG));
	vaw &= ~VT1724_CFG_SPDIF_OUT_EN;
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= VT1724_CFG_SPDIF_OUT_EN;
	if (owd != vaw)
		outb(vaw, ICEWEG1724(ice, SPDIF_CFG));
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn owd != vaw;
}

static const stwuct snd_kcontwow_new snd_vt1724_spdif_switch =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	/* FIXME: the fowwowing confwict with IEC958 Pwayback Woute */
	/* .name =         SNDWV_CTW_NAME_IEC958("", PWAYBACK, SWITCH), */
	.name =         SNDWV_CTW_NAME_IEC958("Output ", NONE, SWITCH),
	.info =		snd_vt1724_spdif_sw_info,
	.get =		snd_vt1724_spdif_sw_get,
	.put =		snd_vt1724_spdif_sw_put
};


#if 0 /* NOT USED YET */
/*
 * GPIO access fwom extewn
 */

#define snd_vt1724_gpio_info		snd_ctw_boowean_mono_info

int snd_vt1724_gpio_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue & (1<<24)) ? 1 : 0;

	snd_ice1712_save_gpio_status(ice);
	ucontwow->vawue.integew.vawue[0] =
		(snd_ice1712_gpio_wead(ice) & (1 << shift) ? 1 : 0) ^ invewt;
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn 0;
}

int snd_ice1712_gpio_put(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue & (1<<24)) ? mask : 0;
	unsigned int vaw, nvaw;

	if (kcontwow->pwivate_vawue & (1 << 31))
		wetuwn -EPEWM;
	nvaw = (ucontwow->vawue.integew.vawue[0] ? (1 << shift) : 0) ^ invewt;
	snd_ice1712_save_gpio_status(ice);
	vaw = snd_ice1712_gpio_wead(ice);
	nvaw |= vaw & ~(1 << shift);
	if (vaw != nvaw)
		snd_ice1712_gpio_wwite(ice, nvaw);
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn vaw != nvaw;
}
#endif /* NOT USED YET */

/*
 *  wate
 */
static int snd_vt1724_pwo_intewnaw_cwock_info(stwuct snd_kcontwow *kcontwow,
					      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int hw_wates_count = ice->hw_wates->count;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;

	/* intewnaw cwocks */
	uinfo->vawue.enumewated.items = hw_wates_count;
	/* extewnaw cwocks */
	if (ice->fowce_wdma1 ||
	    (ice->eepwom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_IN))
		uinfo->vawue.enumewated.items += ice->ext_cwock_count;
	/* uppew wimit - keep at top */
	if (uinfo->vawue.enumewated.item >= uinfo->vawue.enumewated.items)
		uinfo->vawue.enumewated.item = uinfo->vawue.enumewated.items - 1;
	if (uinfo->vawue.enumewated.item >= hw_wates_count)
		/* ext_cwock items */
		stwcpy(uinfo->vawue.enumewated.name,
				ice->ext_cwock_names[
				uinfo->vawue.enumewated.item - hw_wates_count]);
	ewse
		/* int cwock items */
		spwintf(uinfo->vawue.enumewated.name, "%d",
			ice->hw_wates->wist[uinfo->vawue.enumewated.item]);
	wetuwn 0;
}

static int snd_vt1724_pwo_intewnaw_cwock_get(stwuct snd_kcontwow *kcontwow,
					     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int i, wate;

	spin_wock_iwq(&ice->weg_wock);
	if (ice->is_spdif_mastew(ice)) {
		ucontwow->vawue.enumewated.item[0] = ice->hw_wates->count +
			ice->get_spdif_mastew_type(ice);
	} ewse {
		wate = ice->get_wate(ice);
		ucontwow->vawue.enumewated.item[0] = 0;
		fow (i = 0; i < ice->hw_wates->count; i++) {
			if (ice->hw_wates->wist[i] == wate) {
				ucontwow->vawue.enumewated.item[0] = i;
				bweak;
			}
		}
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static int stdcwock_get_spdif_mastew_type(stwuct snd_ice1712 *ice)
{
	/* standawd extewnaw cwock - onwy singwe type - SPDIF IN */
	wetuwn 0;
}

/* setting cwock to extewnaw - SPDIF */
static int stdcwock_set_spdif_cwock(stwuct snd_ice1712 *ice, int type)
{
	unsigned chaw ovaw;
	unsigned chaw i2s_ovaw;
	ovaw = inb(ICEMT1724(ice, WATE));
	outb(ovaw | VT1724_SPDIF_MASTEW, ICEMT1724(ice, WATE));
	/* setting 256fs */
	i2s_ovaw = inb(ICEMT1724(ice, I2S_FOWMAT));
	outb(i2s_ovaw & ~VT1724_MT_I2S_MCWK_128X, ICEMT1724(ice, I2S_FOWMAT));
	wetuwn 0;
}


static int snd_vt1724_pwo_intewnaw_cwock_put(stwuct snd_kcontwow *kcontwow,
					     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd_wate, new_wate;
	unsigned int item = ucontwow->vawue.enumewated.item[0];
	unsigned int fiwst_ext_cwock = ice->hw_wates->count;

	if (item >  fiwst_ext_cwock + ice->ext_cwock_count - 1)
		wetuwn -EINVAW;

	/* if wate = 0 => extewnaw cwock */
	spin_wock_iwq(&ice->weg_wock);
	if (ice->is_spdif_mastew(ice))
		owd_wate = 0;
	ewse
		owd_wate = ice->get_wate(ice);
	if (item >= fiwst_ext_cwock) {
		/* switching to extewnaw cwock */
		ice->set_spdif_cwock(ice, item - fiwst_ext_cwock);
		new_wate = 0;
	} ewse {
		/* intewnaw on-cawd cwock */
		new_wate = ice->hw_wates->wist[item];
		ice->pwo_wate_defauwt = new_wate;
		spin_unwock_iwq(&ice->weg_wock);
		snd_vt1724_set_pwo_wate(ice, ice->pwo_wate_defauwt, 1);
		spin_wock_iwq(&ice->weg_wock);
	}
	spin_unwock_iwq(&ice->weg_wock);

	/* the fiwst switch to the ext. cwock mode? */
	if (owd_wate != new_wate && !new_wate) {
		/* notify akm chips as weww */
		unsigned int i;
		if (ice->gpio.set_pwo_wate)
			ice->gpio.set_pwo_wate(ice, 0);
		fow (i = 0; i < ice->akm_codecs; i++) {
			if (ice->akm[i].ops.set_wate_vaw)
				ice->akm[i].ops.set_wate_vaw(&ice->akm[i], 0);
		}
	}
	wetuwn owd_wate != new_wate;
}

static const stwuct snd_kcontwow_new snd_vt1724_pwo_intewnaw_cwock = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Intewnaw Cwock",
	.info = snd_vt1724_pwo_intewnaw_cwock_info,
	.get = snd_vt1724_pwo_intewnaw_cwock_get,
	.put = snd_vt1724_pwo_intewnaw_cwock_put
};

#define snd_vt1724_pwo_wate_wocking_info	snd_ctw_boowean_mono_info

static int snd_vt1724_pwo_wate_wocking_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = PWO_WATE_WOCKED;
	wetuwn 0;
}

static int snd_vt1724_pwo_wate_wocking_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change = 0, nvaw;

	nvaw = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	spin_wock_iwq(&ice->weg_wock);
	change = PWO_WATE_WOCKED != nvaw;
	PWO_WATE_WOCKED = nvaw;
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_vt1724_pwo_wate_wocking = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Wate Wocking",
	.info = snd_vt1724_pwo_wate_wocking_info,
	.get = snd_vt1724_pwo_wate_wocking_get,
	.put = snd_vt1724_pwo_wate_wocking_put
};

#define snd_vt1724_pwo_wate_weset_info		snd_ctw_boowean_mono_info

static int snd_vt1724_pwo_wate_weset_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = PWO_WATE_WESET ? 1 : 0;
	wetuwn 0;
}

static int snd_vt1724_pwo_wate_weset_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int change = 0, nvaw;

	nvaw = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	spin_wock_iwq(&ice->weg_wock);
	change = PWO_WATE_WESET != nvaw;
	PWO_WATE_WESET = nvaw;
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_vt1724_pwo_wate_weset = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Muwti Twack Wate Weset",
	.info = snd_vt1724_pwo_wate_weset_info,
	.get = snd_vt1724_pwo_wate_weset_get,
	.put = snd_vt1724_pwo_wate_weset_put
};


/*
 * wouting
 */
static int snd_vt1724_pwo_woute_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = {
		"PCM Out", /* 0 */
		"H/W In 0", "H/W In 1", /* 1-2 */
		"IEC958 In W", "IEC958 In W", /* 3-4 */
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}

static inwine int anawog_woute_shift(int idx)
{
	wetuwn (idx % 2) * 12 + ((idx / 2) * 3) + 8;
}

static inwine int digitaw_woute_shift(int idx)
{
	wetuwn idx * 3;
}

int snd_ice1724_get_woute_vaw(stwuct snd_ice1712 *ice, int shift)
{
	unsigned wong vaw;
	unsigned chaw eitem;
	static const unsigned chaw xwate[8] = {
		0, 255, 1, 2, 255, 255, 3, 4,
	};

	vaw = inw(ICEMT1724(ice, WOUTE_PWAYBACK));
	vaw >>= shift;
	vaw &= 7; /* we now have 3 bits pew output */
	eitem = xwate[vaw];
	if (eitem == 255) {
		snd_BUG();
		wetuwn 0;
	}
	wetuwn eitem;
}

int snd_ice1724_put_woute_vaw(stwuct snd_ice1712 *ice, unsigned int vaw,
								int shift)
{
	unsigned int owd_vaw, nvaw;
	int change;
	static const unsigned chaw xwoute[8] = {
		0, /* PCM */
		2, /* PSDIN0 Weft */
		3, /* PSDIN0 Wight */
		6, /* SPDIN Weft */
		7, /* SPDIN Wight */
	};

	nvaw = xwoute[vaw % 5];
	vaw = owd_vaw = inw(ICEMT1724(ice, WOUTE_PWAYBACK));
	vaw &= ~(0x07 << shift);
	vaw |= nvaw << shift;
	change = vaw != owd_vaw;
	if (change)
		outw(vaw, ICEMT1724(ice, WOUTE_PWAYBACK));
	wetuwn change;
}

static int snd_vt1724_pwo_woute_anawog_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	ucontwow->vawue.enumewated.item[0] =
		snd_ice1724_get_woute_vaw(ice, anawog_woute_shift(idx));
	wetuwn 0;
}

static int snd_vt1724_pwo_woute_anawog_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	wetuwn snd_ice1724_put_woute_vaw(ice,
					 ucontwow->vawue.enumewated.item[0],
					 anawog_woute_shift(idx));
}

static int snd_vt1724_pwo_woute_spdif_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	ucontwow->vawue.enumewated.item[0] =
		snd_ice1724_get_woute_vaw(ice, digitaw_woute_shift(idx));
	wetuwn 0;
}

static int snd_vt1724_pwo_woute_spdif_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	wetuwn snd_ice1724_put_woute_vaw(ice,
					 ucontwow->vawue.enumewated.item[0],
					 digitaw_woute_shift(idx));
}

static const stwuct snd_kcontwow_new snd_vt1724_mixew_pwo_anawog_woute =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "H/W Pwayback Woute",
	.info = snd_vt1724_pwo_woute_info,
	.get = snd_vt1724_pwo_woute_anawog_get,
	.put = snd_vt1724_pwo_woute_anawog_put,
};

static const stwuct snd_kcontwow_new snd_vt1724_mixew_pwo_spdif_woute = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, NONE) "Woute",
	.info = snd_vt1724_pwo_woute_info,
	.get = snd_vt1724_pwo_woute_spdif_get,
	.put = snd_vt1724_pwo_woute_spdif_put,
	.count = 2,
};


static int snd_vt1724_pwo_peak_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 22; /* FIXME: fow compatibiwity with ice1712... */
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int snd_vt1724_pwo_peak_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int idx;

	spin_wock_iwq(&ice->weg_wock);
	fow (idx = 0; idx < 22; idx++) {
		outb(idx, ICEMT1724(ice, MONITOW_PEAKINDEX));
		ucontwow->vawue.integew.vawue[idx] =
			inb(ICEMT1724(ice, MONITOW_PEAKDATA));
	}
	spin_unwock_iwq(&ice->weg_wock);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_vt1724_mixew_pwo_peak = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "Muwti Twack Peak",
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
	.info = snd_vt1724_pwo_peak_info,
	.get = snd_vt1724_pwo_peak_get
};

/*
  ooAoo cawds with no contwows
*/
static const unsigned chaw ooaoo_sq210_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x4c,	/* 49MHz cwystaw, no mpu401, no ADC,
					   1xDACs */
	[ICE_EEP2_ACWINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0x78,	/* no vowume, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc1,	/* out-en, out-int, out-ext */
	[ICE_EEP2_GPIO_DIW]    = 0x00,	/* no GPIOs awe used */
	[ICE_EEP2_GPIO_DIW1]   = 0x00,
	[ICE_EEP2_GPIO_DIW2]   = 0x00,
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0xff,

	[ICE_EEP2_GPIO_STATE]  = 0x00, /* inputs */
	[ICE_EEP2_GPIO_STATE1] = 0x00, /* aww 1, but GPIO_CPWD_WW
					  and GPIO15 awways zewo */
	[ICE_EEP2_GPIO_STATE2] = 0x00, /* inputs */
};


static const stwuct snd_ice1712_cawd_info snd_vt1724_ooaoo_cawds[] = {
	{
		.name = "ooAoo SQ210a",
		.modew = "sq210a",
		.eepwom_size = sizeof(ooaoo_sq210_eepwom),
		.eepwom_data = ooaoo_sq210_eepwom,
	},
	{ } /* tewminatow */
};

static const stwuct snd_ice1712_cawd_info *cawd_tabwes[] = {
	snd_vt1724_wevo_cawds,
	snd_vt1724_amp_cawds,
	snd_vt1724_auweon_cawds,
	snd_vt1720_mobo_cawds,
	snd_vt1720_pontis_cawds,
	snd_vt1724_pwodigy_hifi_cawds,
	snd_vt1724_pwodigy192_cawds,
	snd_vt1724_juwi_cawds,
	snd_vt1724_maya44_cawds,
	snd_vt1724_phase_cawds,
	snd_vt1724_wtm_cawds,
	snd_vt1724_se_cawds,
	snd_vt1724_qtet_cawds,
	snd_vt1724_ooaoo_cawds,
	snd_vt1724_psc724_cawds,
	NUWW,
};


/*
 */

static void wait_i2c_busy(stwuct snd_ice1712 *ice)
{
	int t = 0x10000;
	whiwe ((inb(ICEWEG1724(ice, I2C_CTWW)) & VT1724_I2C_BUSY) && t--)
		;
	if (t == -1)
		dev_eww(ice->cawd->dev, "i2c busy timeout\n");
}

unsigned chaw snd_vt1724_wead_i2c(stwuct snd_ice1712 *ice,
				  unsigned chaw dev, unsigned chaw addw)
{
	unsigned chaw vaw;

	mutex_wock(&ice->i2c_mutex);
	wait_i2c_busy(ice);
	outb(addw, ICEWEG1724(ice, I2C_BYTE_ADDW));
	outb(dev & ~VT1724_I2C_WWITE, ICEWEG1724(ice, I2C_DEV_ADDW));
	wait_i2c_busy(ice);
	vaw = inb(ICEWEG1724(ice, I2C_DATA));
	mutex_unwock(&ice->i2c_mutex);
	/*
	dev_dbg(ice->cawd->dev, "i2c_wead: [0x%x,0x%x] = 0x%x\n", dev, addw, vaw);
	*/
	wetuwn vaw;
}

void snd_vt1724_wwite_i2c(stwuct snd_ice1712 *ice,
			  unsigned chaw dev, unsigned chaw addw, unsigned chaw data)
{
	mutex_wock(&ice->i2c_mutex);
	wait_i2c_busy(ice);
	/*
	dev_dbg(ice->cawd->dev, "i2c_wwite: [0x%x,0x%x] = 0x%x\n", dev, addw, data);
	*/
	outb(addw, ICEWEG1724(ice, I2C_BYTE_ADDW));
	outb(data, ICEWEG1724(ice, I2C_DATA));
	outb(dev | VT1724_I2C_WWITE, ICEWEG1724(ice, I2C_DEV_ADDW));
	wait_i2c_busy(ice);
	mutex_unwock(&ice->i2c_mutex);
}

static int snd_vt1724_wead_eepwom(stwuct snd_ice1712 *ice,
				  const chaw *modewname)
{
	const int dev = 0xa0;		/* EEPWOM device addwess */
	unsigned int i, size;
	const stwuct snd_ice1712_cawd_info * const *tbw, *c;

	if (!modewname || !*modewname) {
		ice->eepwom.subvendow = 0;
		if ((inb(ICEWEG1724(ice, I2C_CTWW)) & VT1724_I2C_EEPWOM) != 0)
			ice->eepwom.subvendow =
				(snd_vt1724_wead_i2c(ice, dev, 0x00) << 0) |
				(snd_vt1724_wead_i2c(ice, dev, 0x01) << 8) |
				(snd_vt1724_wead_i2c(ice, dev, 0x02) << 16) |
				(snd_vt1724_wead_i2c(ice, dev, 0x03) << 24);
		if (ice->eepwom.subvendow == 0 ||
		    ice->eepwom.subvendow == (unsigned int)-1) {
			/* invawid subvendow fwom EEPWOM, twy the PCI
			 * subststem ID instead
			 */
			u16 vendow, device;
			pci_wead_config_wowd(ice->pci, PCI_SUBSYSTEM_VENDOW_ID,
					     &vendow);
			pci_wead_config_wowd(ice->pci, PCI_SUBSYSTEM_ID, &device);
			ice->eepwom.subvendow =
				((unsigned int)swab16(vendow) << 16) | swab16(device);
			if (ice->eepwom.subvendow == 0 ||
			    ice->eepwom.subvendow == (unsigned int)-1) {
				dev_eww(ice->cawd->dev,
					"No vawid ID is found\n");
				wetuwn -ENXIO;
			}
		}
	}
	fow (tbw = cawd_tabwes; *tbw; tbw++) {
		fow (c = *tbw; c->name; c++) {
			if (modewname && c->modew &&
			    !stwcmp(modewname, c->modew)) {
				dev_info(ice->cawd->dev,
					 "Using boawd modew %s\n",
				       c->name);
				ice->eepwom.subvendow = c->subvendow;
			} ewse if (c->subvendow != ice->eepwom.subvendow)
				continue;
			ice->cawd_info = c;
			if (!c->eepwom_size || !c->eepwom_data)
				goto found;
			/* if the EEPWOM is given by the dwivew, use it */
			dev_dbg(ice->cawd->dev, "using the defined eepwom..\n");
			ice->eepwom.vewsion = 2;
			ice->eepwom.size = c->eepwom_size + 6;
			memcpy(ice->eepwom.data, c->eepwom_data, c->eepwom_size);
			goto wead_skipped;
		}
	}
	dev_wawn(ice->cawd->dev, "No matching modew found fow ID 0x%x\n",
	       ice->eepwom.subvendow);
#ifdef CONFIG_PM_SWEEP
	/* assume AC97-onwy cawd which can suspend without additionaw code */
	ice->pm_suspend_enabwed = 1;
#endif

 found:
	ice->eepwom.size = snd_vt1724_wead_i2c(ice, dev, 0x04);
	if (ice->eepwom.size < 6)
		ice->eepwom.size = 32;
	ewse if (ice->eepwom.size > 32) {
		dev_eww(ice->cawd->dev, "Invawid EEPWOM (size = %i)\n",
		       ice->eepwom.size);
		wetuwn -EIO;
	}
	ice->eepwom.vewsion = snd_vt1724_wead_i2c(ice, dev, 0x05);
	if (ice->eepwom.vewsion != 1 && ice->eepwom.vewsion != 2)
		dev_wawn(ice->cawd->dev, "Invawid EEPWOM vewsion %i\n",
		       ice->eepwom.vewsion);
	size = ice->eepwom.size - 6;
	fow (i = 0; i < size; i++)
		ice->eepwom.data[i] = snd_vt1724_wead_i2c(ice, dev, i + 6);

 wead_skipped:
	ice->eepwom.gpiomask = eepwom_twipwe(ice, ICE_EEP2_GPIO_MASK);
	ice->eepwom.gpiostate = eepwom_twipwe(ice, ICE_EEP2_GPIO_STATE);
	ice->eepwom.gpiodiw = eepwom_twipwe(ice, ICE_EEP2_GPIO_DIW);

	wetuwn 0;
}



static void snd_vt1724_chip_weset(stwuct snd_ice1712 *ice)
{
	outb(VT1724_WESET , ICEWEG1724(ice, CONTWOW));
	inb(ICEWEG1724(ice, CONTWOW)); /* pci posting fwush */
	msweep(10);
	outb(0, ICEWEG1724(ice, CONTWOW));
	inb(ICEWEG1724(ice, CONTWOW)); /* pci posting fwush */
	msweep(10);
}

static int snd_vt1724_chip_init(stwuct snd_ice1712 *ice)
{
	outb(ice->eepwom.data[ICE_EEP2_SYSCONF], ICEWEG1724(ice, SYS_CFG));
	outb(ice->eepwom.data[ICE_EEP2_ACWINK], ICEWEG1724(ice, AC97_CFG));
	outb(ice->eepwom.data[ICE_EEP2_I2S], ICEWEG1724(ice, I2S_FEATUWES));
	outb(ice->eepwom.data[ICE_EEP2_SPDIF], ICEWEG1724(ice, SPDIF_CFG));

	ice->gpio.wwite_mask = ice->eepwom.gpiomask;
	ice->gpio.diwection = ice->eepwom.gpiodiw;
	snd_vt1724_set_gpio_mask(ice, ice->eepwom.gpiomask);
	snd_vt1724_set_gpio_diw(ice, ice->eepwom.gpiodiw);
	snd_vt1724_set_gpio_data(ice, ice->eepwom.gpiostate);

	outb(0, ICEWEG1724(ice, POWEWDOWN));

	/* MPU_WX and TX iwq masks awe cweawed watew dynamicawwy */
	outb(VT1724_IWQ_MPU_WX | VT1724_IWQ_MPU_TX , ICEWEG1724(ice, IWQMASK));

	/* don't handwe FIFO ovewwun/undewwuns (just yet),
	 * since they cause machine wockups
	 */
	outb(VT1724_MUWTI_FIFO_EWW, ICEMT1724(ice, DMA_INT_MASK));

	wetuwn 0;
}

static int snd_vt1724_spdif_buiwd_contwows(stwuct snd_ice1712 *ice)
{
	int eww;
	stwuct snd_kcontwow *kctw;

	if (snd_BUG_ON(!ice->pcm))
		wetuwn -EIO;

	if (!ice->own_wouting) {
		eww = snd_ctw_add(ice->cawd,
			snd_ctw_new1(&snd_vt1724_mixew_pwo_spdif_woute, ice));
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_vt1724_spdif_switch, ice));
	if (eww < 0)
		wetuwn eww;

	kctw = snd_ctw_new1(&snd_vt1724_spdif_defauwt, ice);
	kctw->id.device = ice->pcm->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_vt1724_spdif_maskc, ice);
	kctw->id.device = ice->pcm->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_vt1724_spdif_maskp, ice);
	kctw->id.device = ice->pcm->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
#if 0 /* use defauwt onwy */
	kctw = snd_ctw_new1(&snd_vt1724_spdif_stweam, ice);
	kctw->id.device = ice->pcm->device;
	eww = snd_ctw_add(ice->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	ice->spdif.stweam_ctw = kctw;
#endif
	wetuwn 0;
}


static int snd_vt1724_buiwd_contwows(stwuct snd_ice1712 *ice)
{
	int eww;

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_vt1724_eepwom, ice));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_vt1724_pwo_intewnaw_cwock, ice));
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_vt1724_pwo_wate_wocking, ice));
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_vt1724_pwo_wate_weset, ice));
	if (eww < 0)
		wetuwn eww;

	if (!ice->own_wouting && ice->num_totaw_dacs > 0) {
		stwuct snd_kcontwow_new tmp = snd_vt1724_mixew_pwo_anawog_woute;
		tmp.count = ice->num_totaw_dacs;
		if (ice->vt1720 && tmp.count > 2)
			tmp.count = 2;
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&tmp, ice));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn snd_ctw_add(ice->cawd,
			   snd_ctw_new1(&snd_vt1724_mixew_pwo_peak, ice));
}

static void snd_vt1724_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_ice1712 *ice = cawd->pwivate_data;

	/* mask aww intewwupts */
	outb(0xff, ICEMT1724(ice, DMA_INT_MASK));
	outb(0xff, ICEWEG1724(ice, IWQMASK));

	snd_ice1712_akm4xxx_fwee(ice);
}

static int snd_vt1724_cweate(stwuct snd_cawd *cawd,
			     stwuct pci_dev *pci,
			     const chaw *modewname)
{
	stwuct snd_ice1712 *ice = cawd->pwivate_data;
	int eww;

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	ice->vt1724 = 1;
	spin_wock_init(&ice->weg_wock);
	mutex_init(&ice->gpio_mutex);
	mutex_init(&ice->open_mutex);
	mutex_init(&ice->i2c_mutex);
	ice->gpio.set_mask = snd_vt1724_set_gpio_mask;
	ice->gpio.get_mask = snd_vt1724_get_gpio_mask;
	ice->gpio.set_diw = snd_vt1724_set_gpio_diw;
	ice->gpio.get_diw = snd_vt1724_get_gpio_diw;
	ice->gpio.set_data = snd_vt1724_set_gpio_data;
	ice->gpio.get_data = snd_vt1724_get_gpio_data;
	ice->cawd = cawd;
	ice->pci = pci;
	ice->iwq = -1;
	pci_set_mastew(pci);
	snd_vt1724_pwoc_init(ice);

	eww = pci_wequest_wegions(pci, "ICE1724");
	if (eww < 0)
		wetuwn eww;
	ice->powt = pci_wesouwce_stawt(pci, 0);
	ice->pwofi_powt = pci_wesouwce_stawt(pci, 1);

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_vt1724_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, ice)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EIO;
	}

	ice->iwq = pci->iwq;
	cawd->sync_iwq = ice->iwq;
	cawd->pwivate_fwee = snd_vt1724_fwee;

	snd_vt1724_chip_weset(ice);
	if (snd_vt1724_wead_eepwom(ice, modewname) < 0)
		wetuwn -EIO;
	if (snd_vt1724_chip_init(ice) < 0)
		wetuwn -EIO;

	wetuwn 0;
}


/*
 *
 * Wegistwation
 *
 */

static int __snd_vt1724_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_ice1712 *ice;
	int pcm_dev = 0, eww;
	const stwuct snd_ice1712_cawd_info *c;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*ice), &cawd);
	if (eww < 0)
		wetuwn eww;
	ice = cawd->pwivate_data;

	stwcpy(cawd->dwivew, "ICE1724");
	stwcpy(cawd->showtname, "ICEnsembwe ICE1724");

	eww = snd_vt1724_cweate(cawd, pci, modew[dev]);
	if (eww < 0)
		wetuwn eww;

	/* fiewd init befowe cawwing chip_init */
	ice->ext_cwock_count = 0;

	c = ice->cawd_info;
	if (c) {
		stwcpy(cawd->showtname, c->name);
		if (c->dwivew) /* specific dwivew? */
			stwcpy(cawd->dwivew, c->dwivew);
		if (c->chip_init) {
			eww = c->chip_init(ice);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/*
	* VT1724 has sepawate DMAs fow the anawog and the SPDIF stweams whiwe
	* ICE1712 has onwy one fow both (mixed up).
	*
	* Confusingwy the anawog PCM is named "pwofessionaw" hewe because it
	* was cawwed so in ice1712 dwivew, and vt1724 dwivew is dewived fwom
	* ice1712 dwivew.
	*/
	ice->pwo_wate_defauwt = PWO_WATE_DEFAUWT;
	if (!ice->is_spdif_mastew)
		ice->is_spdif_mastew = stdcwock_is_spdif_mastew;
	if (!ice->get_wate)
		ice->get_wate = stdcwock_get_wate;
	if (!ice->set_wate)
		ice->set_wate = stdcwock_set_wate;
	if (!ice->set_mcwk)
		ice->set_mcwk = stdcwock_set_mcwk;
	if (!ice->set_spdif_cwock)
		ice->set_spdif_cwock = stdcwock_set_spdif_cwock;
	if (!ice->get_spdif_mastew_type)
		ice->get_spdif_mastew_type = stdcwock_get_spdif_mastew_type;
	if (!ice->ext_cwock_names)
		ice->ext_cwock_names = ext_cwock_names;
	if (!ice->ext_cwock_count)
		ice->ext_cwock_count = AWWAY_SIZE(ext_cwock_names);

	if (!ice->hw_wates)
		set_std_hw_wates(ice);

	eww = snd_vt1724_pcm_pwofi(ice, pcm_dev++);
	if (eww < 0)
		wetuwn eww;

	eww = snd_vt1724_pcm_spdif(ice, pcm_dev++);
	if (eww < 0)
		wetuwn eww;

	eww = snd_vt1724_pcm_indep(ice, pcm_dev++);
	if (eww < 0)
		wetuwn eww;

	eww = snd_vt1724_ac97_mixew(ice);
	if (eww < 0)
		wetuwn eww;

	eww = snd_vt1724_buiwd_contwows(ice);
	if (eww < 0)
		wetuwn eww;

	if (ice->pcm && ice->has_spdif) { /* has SPDIF I/O */
		eww = snd_vt1724_spdif_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
	}

	if (c && c->buiwd_contwows) {
		eww = c->buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
	}

	if (!c || !c->no_mpu401) {
		if (ice->eepwom.data[ICE_EEP2_SYSCONF] & VT1724_CFG_MPU401) {
			stwuct snd_wawmidi *wmidi;

			eww = snd_wawmidi_new(cawd, "MIDI", 0, 1, 1, &wmidi);
			if (eww < 0)
				wetuwn eww;
			ice->wmidi[0] = wmidi;
			wmidi->pwivate_data = ice;
			stwcpy(wmidi->name, "ICE1724 MIDI");
			wmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
					    SNDWV_WAWMIDI_INFO_INPUT |
					    SNDWV_WAWMIDI_INFO_DUPWEX;
			snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
					    &vt1724_midi_output_ops);
			snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
					    &vt1724_midi_input_ops);

			/* set watewmawks */
			outb(VT1724_MPU_WX_FIFO | 0x1,
			     ICEWEG1724(ice, MPU_FIFO_WM));
			outb(0x1, ICEWEG1724(ice, MPU_FIFO_WM));
			/* set UAWT mode */
			outb(VT1724_MPU_UAWT, ICEWEG1724(ice, MPU_CTWW));
		}
	}

	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, ice->powt, ice->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_vt1724_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_vt1724_pwobe(pci, pci_id));
}

#ifdef CONFIG_PM_SWEEP
static int snd_vt1724_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ice1712 *ice = cawd->pwivate_data;

	if (!ice->pm_suspend_enabwed)
		wetuwn 0;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	snd_ac97_suspend(ice->ac97);

	spin_wock_iwq(&ice->weg_wock);
	ice->pm_saved_is_spdif_mastew = ice->is_spdif_mastew(ice);
	ice->pm_saved_spdif_ctww = inw(ICEMT1724(ice, SPDIF_CTWW));
	ice->pm_saved_spdif_cfg = inb(ICEWEG1724(ice, SPDIF_CFG));
	ice->pm_saved_woute = inw(ICEMT1724(ice, WOUTE_PWAYBACK));
	spin_unwock_iwq(&ice->weg_wock);

	if (ice->pm_suspend)
		ice->pm_suspend(ice);
	wetuwn 0;
}

static int snd_vt1724_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ice1712 *ice = cawd->pwivate_data;

	if (!ice->pm_suspend_enabwed)
		wetuwn 0;

	snd_vt1724_chip_weset(ice);

	if (snd_vt1724_chip_init(ice) < 0) {
		snd_cawd_disconnect(cawd);
		wetuwn -EIO;
	}

	if (ice->pm_wesume)
		ice->pm_wesume(ice);

	if (ice->pm_saved_is_spdif_mastew) {
		/* switching to extewnaw cwock via SPDIF */
		ice->set_spdif_cwock(ice, 0);
	} ewse {
		/* intewnaw on-cawd cwock */
		int wate;
		if (ice->cuw_wate)
			wate = ice->cuw_wate;
		ewse
			wate = ice->pwo_wate_defauwt;
		snd_vt1724_set_pwo_wate(ice, wate, 1);
	}

	update_spdif_bits(ice, ice->pm_saved_spdif_ctww);

	outb(ice->pm_saved_spdif_cfg, ICEWEG1724(ice, SPDIF_CFG));
	outw(ice->pm_saved_woute, ICEMT1724(ice, WOUTE_PWAYBACK));

	snd_ac97_wesume(ice->ac97);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_vt1724_pm, snd_vt1724_suspend, snd_vt1724_wesume);
#define SND_VT1724_PM_OPS	&snd_vt1724_pm
#ewse
#define SND_VT1724_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew vt1724_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_vt1724_ids,
	.pwobe = snd_vt1724_pwobe,
	.dwivew = {
		.pm = SND_VT1724_PM_OPS,
	},
};

moduwe_pci_dwivew(vt1724_dwivew);
