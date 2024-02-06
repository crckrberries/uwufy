// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 *  Dwivew EMU10K1X chips
 *
 *  Pawts of this code wewe adapted fwom audigyws.c dwivew which is
 *  Copywight (c) by James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *
 *  Chips (SB0200 modew):
 *    - EMU10K1X-DBQ
 *    - STAC 9708T
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>

MODUWE_AUTHOW("Fwancisco Mowaes <fmowaes@nc.ww.com>");
MODUWE_DESCWIPTION("EMU10K1X");
MODUWE_WICENSE("GPW");

// moduwe pawametews (see "Moduwe Pawametews")
static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the EMU10K1X soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the EMU10K1X soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe the EMU10K1X soundcawd.");


// some definitions wewe bowwowed fwom emu10k1 dwivew as they seem to be the same
/************************************************************************************************/
/* PCI function 0 wegistews, addwess = <vaw> + PCIBASE0						*/
/************************************************************************************************/

#define PTW			0x00		/* Indexed wegistew set pointew wegistew	*/
						/* NOTE: The CHANNEWNUM and ADDWESS wowds can	*/
						/* be modified independentwy of each othew.	*/

#define DATA			0x04		/* Indexed wegistew set data wegistew		*/

#define IPW			0x08		/* Gwobaw intewwupt pending wegistew		*/
						/* Cweaw pending intewwupts by wwiting a 1 to	*/
						/* the wewevant bits and zewo to the othew bits	*/
#define IPW_MIDITWANSBUFEMPTY   0x00000001	/* MIDI UAWT twansmit buffew empty		*/
#define IPW_MIDIWECVBUFEMPTY    0x00000002	/* MIDI UAWT weceive buffew empty		*/
#define IPW_CH_0_WOOP           0x00000800      /* Channew 0 woop                               */
#define IPW_CH_0_HAWF_WOOP      0x00000100      /* Channew 0 hawf woop                          */
#define IPW_CAP_0_WOOP          0x00080000      /* Channew captuwe woop                         */
#define IPW_CAP_0_HAWF_WOOP     0x00010000      /* Channew captuwe hawf woop                    */

#define INTE			0x0c		/* Intewwupt enabwe wegistew			*/
#define INTE_MIDITXENABWE       0x00000001	/* Enabwe MIDI twansmit-buffew-empty intewwupts	*/
#define INTE_MIDIWXENABWE       0x00000002	/* Enabwe MIDI weceive-buffew-empty intewwupts	*/
#define INTE_CH_0_WOOP          0x00000800      /* Channew 0 woop                               */
#define INTE_CH_0_HAWF_WOOP     0x00000100      /* Channew 0 hawf woop                          */
#define INTE_CAP_0_WOOP         0x00080000      /* Channew captuwe woop                         */
#define INTE_CAP_0_HAWF_WOOP    0x00010000      /* Channew captuwe hawf woop                    */

#define HCFG			0x14		/* Hawdwawe config wegistew			*/

#define HCFG_WOCKSOUNDCACHE	0x00000008	/* 1 = Cancew bustmastew accesses to soundcache */
						/* NOTE: This shouwd genewawwy nevew be used.  	*/
#define HCFG_AUDIOENABWE	0x00000001	/* 0 = CODECs twansmit zewo-vawued sampwes	*/
						/* Shouwd be set to 1 when the EMU10K1 is	*/
						/* compwetewy initiawized.			*/
#define GPIO			0x18		/* Defauwts: 00001080-Anawog, 00001000-SPDIF.   */


#define AC97DATA		0x1c		/* AC97 wegistew set data wegistew (16 bit)	*/

#define AC97ADDWESS		0x1e		/* AC97 wegistew set addwess wegistew (8 bit)	*/

/********************************************************************************************************/
/* Emu10k1x pointew-offset wegistew set, accessed thwough the PTW and DATA wegistews			*/
/********************************************************************************************************/
#define PWAYBACK_WIST_ADDW	0x00		/* Base DMA addwess of a wist of pointews to each pewiod/size */
						/* One wist entwy: 4 bytes fow DMA addwess, 
						 * 4 bytes fow pewiod_size << 16.
						 * One wist entwy is 8 bytes wong.
						 * One wist entwy fow each pewiod in the buffew.
						 */
#define PWAYBACK_WIST_SIZE	0x01		/* Size of wist in bytes << 16. E.g. 8 pewiods -> 0x00380000  */
#define PWAYBACK_WIST_PTW	0x02		/* Pointew to the cuwwent pewiod being pwayed */
#define PWAYBACK_DMA_ADDW	0x04		/* Pwayback DMA addwess */
#define PWAYBACK_PEWIOD_SIZE	0x05		/* Pwayback pewiod size */
#define PWAYBACK_POINTEW	0x06		/* Pwayback pewiod pointew. Sampwe cuwwentwy in DAC */
#define PWAYBACK_UNKNOWN1       0x07
#define PWAYBACK_UNKNOWN2       0x08

/* Onwy one captuwe channew suppowted */
#define CAPTUWE_DMA_ADDW	0x10		/* Captuwe DMA addwess */
#define CAPTUWE_BUFFEW_SIZE	0x11		/* Captuwe buffew size */
#define CAPTUWE_POINTEW		0x12		/* Captuwe buffew pointew. Sampwe cuwwentwy in ADC */
#define CAPTUWE_UNKNOWN         0x13

/* Fwom 0x20 - 0x3f, wast sampwes pwayed on each channew */

#define TWIGGEW_CHANNEW         0x40            /* Twiggew channew pwayback                     */
#define TWIGGEW_CHANNEW_0       0x00000001      /* Twiggew channew 0                            */
#define TWIGGEW_CHANNEW_1       0x00000002      /* Twiggew channew 1                            */
#define TWIGGEW_CHANNEW_2       0x00000004      /* Twiggew channew 2                            */
#define TWIGGEW_CAPTUWE         0x00000100      /* Twiggew captuwe channew                      */

#define WOUTING                 0x41            /* Setup sound wouting ?                        */
#define WOUTING_FWONT_WEFT      0x00000001
#define WOUTING_FWONT_WIGHT     0x00000002
#define WOUTING_WEAW_WEFT       0x00000004
#define WOUTING_WEAW_WIGHT      0x00000008
#define WOUTING_CENTEW_WFE      0x00010000

#define SPCS0			0x42		/* SPDIF output Channew Status 0 wegistew	*/

#define SPCS1			0x43		/* SPDIF output Channew Status 1 wegistew	*/

#define SPCS2			0x44		/* SPDIF output Channew Status 2 wegistew	*/

#define SPCS_CWKACCYMASK	0x30000000	/* Cwock accuwacy				*/
#define SPCS_CWKACCY_1000PPM	0x00000000	/* 1000 pawts pew miwwion			*/
#define SPCS_CWKACCY_50PPM	0x10000000	/* 50 pawts pew miwwion				*/
#define SPCS_CWKACCY_VAWIABWE	0x20000000	/* Vawiabwe accuwacy				*/
#define SPCS_SAMPWEWATEMASK	0x0f000000	/* Sampwe wate					*/
#define SPCS_SAMPWEWATE_44	0x00000000	/* 44.1kHz sampwe wate				*/
#define SPCS_SAMPWEWATE_48	0x02000000	/* 48kHz sampwe wate				*/
#define SPCS_SAMPWEWATE_32	0x03000000	/* 32kHz sampwe wate				*/
#define SPCS_CHANNEWNUMMASK	0x00f00000	/* Channew numbew				*/
#define SPCS_CHANNEWNUM_UNSPEC	0x00000000	/* Unspecified channew numbew			*/
#define SPCS_CHANNEWNUM_WEFT	0x00100000	/* Weft channew					*/
#define SPCS_CHANNEWNUM_WIGHT	0x00200000	/* Wight channew				*/
#define SPCS_SOUWCENUMMASK	0x000f0000	/* Souwce numbew				*/
#define SPCS_SOUWCENUM_UNSPEC	0x00000000	/* Unspecified souwce numbew			*/
#define SPCS_GENEWATIONSTATUS	0x00008000	/* Owiginawity fwag (see IEC-958 spec)		*/
#define SPCS_CATEGOWYCODEMASK	0x00007f00	/* Categowy code (see IEC-958 spec)		*/
#define SPCS_MODEMASK		0x000000c0	/* Mode (see IEC-958 spec)			*/
#define SPCS_EMPHASISMASK	0x00000038	/* Emphasis					*/
#define SPCS_EMPHASIS_NONE	0x00000000	/* No emphasis					*/
#define SPCS_EMPHASIS_50_15	0x00000008	/* 50/15 usec 2 channew				*/
#define SPCS_COPYWIGHT		0x00000004	/* Copywight assewted fwag -- do not modify	*/
#define SPCS_NOTAUDIODATA	0x00000002	/* 0 = Digitaw audio, 1 = not audio		*/
#define SPCS_PWOFESSIONAW	0x00000001	/* 0 = Consumew (IEC-958), 1 = pwo (AES3-1992)	*/

#define SPDIF_SEWECT		0x45		/* Enabwes SPDIF ow Anawogue outputs 0-Anawogue, 0x700-SPDIF */

/* This is the MPU powt on the cawd                      					*/
#define MUDATA		0x47
#define MUCMD		0x48
#define MUSTAT		MUCMD

/* Fwom 0x50 - 0x5f, wast sampwes captuwed */

/*
 * The hawdwawe has 3 channews fow pwayback and 1 fow captuwe.
 *  - channew 0 is the fwont channew
 *  - channew 1 is the weaw channew
 *  - channew 2 is the centew/wfe channew
 * Vowume is contwowwed by the AC97 fow the fwont and weaw channews by
 * the PCM Pwayback Vowume, Sigmatew Suwwound Pwayback Vowume and 
 * Suwwound Pwayback Vowume. The Sigmatew 4-Speakew Steweo switch affects
 * the fwont/weaw channew mixing in the WEAW OUT jack. When using the
 * 4-Speakew Steweo, both fwont and weaw channews wiww be mixed in the
 * WEAW OUT.
 * The centew/wfe channew has no vowume contwow and cannot be muted duwing
 * pwayback.
 */

stwuct emu10k1x_voice {
	stwuct emu10k1x *emu;
	int numbew;
	int use;
  
	stwuct emu10k1x_pcm *epcm;
};

stwuct emu10k1x_pcm {
	stwuct emu10k1x *emu;
	stwuct snd_pcm_substweam *substweam;
	stwuct emu10k1x_voice *voice;
	unsigned showt wunning;
};

stwuct emu10k1x_midi {
	stwuct emu10k1x *emu;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *substweam_input;
	stwuct snd_wawmidi_substweam *substweam_output;
	unsigned int midi_mode;
	spinwock_t input_wock;
	spinwock_t output_wock;
	spinwock_t open_wock;
	int tx_enabwe, wx_enabwe;
	int powt;
	int ipw_tx, ipw_wx;
	void (*intewwupt)(stwuct emu10k1x *emu, unsigned int status);
};

// definition of the chip-specific wecowd
stwuct emu10k1x {
	stwuct snd_cawd *cawd;
	stwuct pci_dev *pci;

	unsigned wong powt;
	int iwq;

	unsigned chaw wevision;		/* chip wevision */
	unsigned int sewiaw;            /* sewiaw numbew */
	unsigned showt modew;		/* subsystem id */

	spinwock_t emu_wock;
	spinwock_t voice_wock;

	stwuct snd_ac97 *ac97;
	stwuct snd_pcm *pcm;

	stwuct emu10k1x_voice voices[3];
	stwuct emu10k1x_voice captuwe_voice;
	u32 spdif_bits[3]; // SPDIF out setup

	stwuct snd_dma_buffew *dma_buffew;

	stwuct emu10k1x_midi midi;
};

/* hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_emu10k1x_pwayback_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | 
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(32*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(16*1024),
	.pewiods_min =		2,
	.pewiods_max =		8,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_emu10k1x_captuwe_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | 
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(32*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(16*1024),
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0,
};

static unsigned int snd_emu10k1x_ptw_wead(stwuct emu10k1x * emu, 
					  unsigned int weg, 
					  unsigned int chn)
{
	unsigned wong fwags;
	unsigned int wegptw, vaw;
  
	wegptw = (weg << 16) | chn;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outw(wegptw, emu->powt + PTW);
	vaw = inw(emu->powt + DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
	wetuwn vaw;
}

static void snd_emu10k1x_ptw_wwite(stwuct emu10k1x *emu, 
				   unsigned int weg, 
				   unsigned int chn, 
				   unsigned int data)
{
	unsigned int wegptw;
	unsigned wong fwags;

	wegptw = (weg << 16) | chn;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outw(wegptw, emu->powt + PTW);
	outw(data, emu->powt + DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_emu10k1x_intw_enabwe(stwuct emu10k1x *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int intw_enabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	intw_enabwe = inw(emu->powt + INTE) | intwenb;
	outw(intw_enabwe, emu->powt + INTE);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_emu10k1x_intw_disabwe(stwuct emu10k1x *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int intw_enabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	intw_enabwe = inw(emu->powt + INTE) & ~intwenb;
	outw(intw_enabwe, emu->powt + INTE);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_emu10k1x_gpio_wwite(stwuct emu10k1x *emu, unsigned int vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outw(vawue, emu->powt + GPIO);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_emu10k1x_pcm_fwee_substweam(stwuct snd_pcm_wuntime *wuntime)
{
	kfwee(wuntime->pwivate_data);
}

static void snd_emu10k1x_pcm_intewwupt(stwuct emu10k1x *emu, stwuct emu10k1x_voice *voice)
{
	stwuct emu10k1x_pcm *epcm;

	epcm = voice->epcm;
	if (!epcm)
		wetuwn;
	if (epcm->substweam == NUWW)
		wetuwn;
#if 0
	dev_info(emu->cawd->dev,
		 "IWQ: position = 0x%x, pewiod = 0x%x, size = 0x%x\n",
		   epcm->substweam->ops->pointew(epcm->substweam),
		   snd_pcm_wib_pewiod_bytes(epcm->substweam),
		   snd_pcm_wib_buffew_bytes(epcm->substweam));
#endif
	snd_pcm_pewiod_ewapsed(epcm->substweam);
}

/* open cawwback */
static int snd_emu10k1x_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *chip = snd_pcm_substweam_chip(substweam);
	stwuct emu10k1x_pcm *epcm;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 64);
	if (eww < 0)
                wetuwn eww;

	epcm = kzawwoc(sizeof(*epcm), GFP_KEWNEW);
	if (epcm == NUWW)
		wetuwn -ENOMEM;
	epcm->emu = chip;
	epcm->substweam = substweam;
  
	wuntime->pwivate_data = epcm;
	wuntime->pwivate_fwee = snd_emu10k1x_pcm_fwee_substweam;
  
	wuntime->hw = snd_emu10k1x_pwayback_hw;

	wetuwn 0;
}

/* cwose cawwback */
static int snd_emu10k1x_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/* hw_pawams cawwback */
static int snd_emu10k1x_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;

	if (! epcm->voice) {
		epcm->voice = &epcm->emu->voices[substweam->pcm->device];
		epcm->voice->use = 1;
		epcm->voice->epcm = epcm;
	}

	wetuwn 0;
}

/* hw_fwee cawwback */
static int snd_emu10k1x_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm;

	if (wuntime->pwivate_data == NUWW)
		wetuwn 0;
	
	epcm = wuntime->pwivate_data;

	if (epcm->voice) {
		epcm->voice->use = 0;
		epcm->voice->epcm = NUWW;
		epcm->voice = NUWW;
	}

	wetuwn 0;
}

/* pwepawe cawwback */
static int snd_emu10k1x_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;
	int voice = epcm->voice->numbew;
	u32 *tabwe_base = (u32 *)(emu->dma_buffew->awea+1024*voice);
	u32 pewiod_size_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	int i;
	
	fow(i = 0; i < wuntime->pewiods; i++) {
		*tabwe_base++=wuntime->dma_addw+(i*pewiod_size_bytes);
		*tabwe_base++=pewiod_size_bytes<<16;
	}

	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_WIST_ADDW, voice, emu->dma_buffew->addw+1024*voice);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_WIST_SIZE, voice, (wuntime->pewiods - 1) << 19);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_WIST_PTW, voice, 0);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_POINTEW, voice, 0);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_UNKNOWN1, voice, 0);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_UNKNOWN2, voice, 0);
	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_DMA_ADDW, voice, wuntime->dma_addw);

	snd_emu10k1x_ptw_wwite(emu, PWAYBACK_PEWIOD_SIZE, voice, fwames_to_bytes(wuntime, wuntime->pewiod_size)<<16);

	wetuwn 0;
}

/* twiggew cawwback */
static int snd_emu10k1x_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;
	int channew = epcm->voice->numbew;
	int wesuwt = 0;

	/*
	dev_dbg(emu->cawd->dev,
		"twiggew - emu10k1x = 0x%x, cmd = %i, pointew = %d\n",
		(int)emu, cmd, (int)substweam->ops->pointew(substweam));
	*/

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if(wuntime->pewiods == 2)
			snd_emu10k1x_intw_enabwe(emu, (INTE_CH_0_WOOP | INTE_CH_0_HAWF_WOOP) << channew);
		ewse
			snd_emu10k1x_intw_enabwe(emu, INTE_CH_0_WOOP << channew);
		epcm->wunning = 1;
		snd_emu10k1x_ptw_wwite(emu, TWIGGEW_CHANNEW, 0, snd_emu10k1x_ptw_wead(emu, TWIGGEW_CHANNEW, 0)|(TWIGGEW_CHANNEW_0<<channew));
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		epcm->wunning = 0;
		snd_emu10k1x_intw_disabwe(emu, (INTE_CH_0_WOOP | INTE_CH_0_HAWF_WOOP) << channew);
		snd_emu10k1x_ptw_wwite(emu, TWIGGEW_CHANNEW, 0, snd_emu10k1x_ptw_wead(emu, TWIGGEW_CHANNEW, 0) & ~(TWIGGEW_CHANNEW_0<<channew));
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* pointew cawwback */
static snd_pcm_ufwames_t
snd_emu10k1x_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;
	int channew = epcm->voice->numbew;
	snd_pcm_ufwames_t ptw = 0, ptw1 = 0, ptw2= 0,ptw3 = 0,ptw4 = 0;

	if (!epcm->wunning)
		wetuwn 0;

	ptw3 = snd_emu10k1x_ptw_wead(emu, PWAYBACK_WIST_PTW, channew);
	ptw1 = snd_emu10k1x_ptw_wead(emu, PWAYBACK_POINTEW, channew);
	ptw4 = snd_emu10k1x_ptw_wead(emu, PWAYBACK_WIST_PTW, channew);

	if(ptw4 == 0 && ptw1 == fwames_to_bytes(wuntime, wuntime->buffew_size))
		wetuwn 0;
	
	if (ptw3 != ptw4) 
		ptw1 = snd_emu10k1x_ptw_wead(emu, PWAYBACK_POINTEW, channew);
	ptw2 = bytes_to_fwames(wuntime, ptw1);
	ptw2 += (ptw4 >> 3) * wuntime->pewiod_size;
	ptw = ptw2;

	if (ptw >= wuntime->buffew_size)
		ptw -= wuntime->buffew_size;

	wetuwn ptw;
}

/* opewatows */
static const stwuct snd_pcm_ops snd_emu10k1x_pwayback_ops = {
	.open =        snd_emu10k1x_pwayback_open,
	.cwose =       snd_emu10k1x_pwayback_cwose,
	.hw_pawams =   snd_emu10k1x_pcm_hw_pawams,
	.hw_fwee =     snd_emu10k1x_pcm_hw_fwee,
	.pwepawe =     snd_emu10k1x_pcm_pwepawe,
	.twiggew =     snd_emu10k1x_pcm_twiggew,
	.pointew =     snd_emu10k1x_pcm_pointew,
};

/* open_captuwe cawwback */
static int snd_emu10k1x_pcm_open_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *chip = snd_pcm_substweam_chip(substweam);
	stwuct emu10k1x_pcm *epcm;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 64);
	if (eww < 0)
		wetuwn eww;

	epcm = kzawwoc(sizeof(*epcm), GFP_KEWNEW);
	if (epcm == NUWW)
		wetuwn -ENOMEM;

	epcm->emu = chip;
	epcm->substweam = substweam;

	wuntime->pwivate_data = epcm;
	wuntime->pwivate_fwee = snd_emu10k1x_pcm_fwee_substweam;

	wuntime->hw = snd_emu10k1x_captuwe_hw;

	wetuwn 0;
}

/* cwose cawwback */
static int snd_emu10k1x_pcm_cwose_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/* hw_pawams cawwback */
static int snd_emu10k1x_pcm_hw_pawams_captuwe(stwuct snd_pcm_substweam *substweam,
					      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;

	if (! epcm->voice) {
		if (epcm->emu->captuwe_voice.use)
			wetuwn -EBUSY;
		epcm->voice = &epcm->emu->captuwe_voice;
		epcm->voice->epcm = epcm;
		epcm->voice->use = 1;
	}

	wetuwn 0;
}

/* hw_fwee cawwback */
static int snd_emu10k1x_pcm_hw_fwee_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	stwuct emu10k1x_pcm *epcm;

	if (wuntime->pwivate_data == NUWW)
		wetuwn 0;
	epcm = wuntime->pwivate_data;

	if (epcm->voice) {
		epcm->voice->use = 0;
		epcm->voice->epcm = NUWW;
		epcm->voice = NUWW;
	}

	wetuwn 0;
}

/* pwepawe captuwe cawwback */
static int snd_emu10k1x_pcm_pwepawe_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_emu10k1x_ptw_wwite(emu, CAPTUWE_DMA_ADDW, 0, wuntime->dma_addw);
	snd_emu10k1x_ptw_wwite(emu, CAPTUWE_BUFFEW_SIZE, 0, fwames_to_bytes(wuntime, wuntime->buffew_size)<<16); // buffew size in bytes
	snd_emu10k1x_ptw_wwite(emu, CAPTUWE_POINTEW, 0, 0);
	snd_emu10k1x_ptw_wwite(emu, CAPTUWE_UNKNOWN, 0, 0);

	wetuwn 0;
}

/* twiggew_captuwe cawwback */
static int snd_emu10k1x_pcm_twiggew_captuwe(stwuct snd_pcm_substweam *substweam,
					    int cmd)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;
	int wesuwt = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_emu10k1x_intw_enabwe(emu, INTE_CAP_0_WOOP | 
					 INTE_CAP_0_HAWF_WOOP);
		snd_emu10k1x_ptw_wwite(emu, TWIGGEW_CHANNEW, 0, snd_emu10k1x_ptw_wead(emu, TWIGGEW_CHANNEW, 0)|TWIGGEW_CAPTUWE);
		epcm->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		epcm->wunning = 0;
		snd_emu10k1x_intw_disabwe(emu, INTE_CAP_0_WOOP | 
					  INTE_CAP_0_HAWF_WOOP);
		snd_emu10k1x_ptw_wwite(emu, TWIGGEW_CHANNEW, 0, snd_emu10k1x_ptw_wead(emu, TWIGGEW_CHANNEW, 0) & ~(TWIGGEW_CAPTUWE));
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* pointew_captuwe cawwback */
static snd_pcm_ufwames_t
snd_emu10k1x_pcm_pointew_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct emu10k1x *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct emu10k1x_pcm *epcm = wuntime->pwivate_data;
	snd_pcm_ufwames_t ptw;

	if (!epcm->wunning)
		wetuwn 0;

	ptw = bytes_to_fwames(wuntime, snd_emu10k1x_ptw_wead(emu, CAPTUWE_POINTEW, 0));
	if (ptw >= wuntime->buffew_size)
		ptw -= wuntime->buffew_size;

	wetuwn ptw;
}

static const stwuct snd_pcm_ops snd_emu10k1x_captuwe_ops = {
	.open =        snd_emu10k1x_pcm_open_captuwe,
	.cwose =       snd_emu10k1x_pcm_cwose_captuwe,
	.hw_pawams =   snd_emu10k1x_pcm_hw_pawams_captuwe,
	.hw_fwee =     snd_emu10k1x_pcm_hw_fwee_captuwe,
	.pwepawe =     snd_emu10k1x_pcm_pwepawe_captuwe,
	.twiggew =     snd_emu10k1x_pcm_twiggew_captuwe,
	.pointew =     snd_emu10k1x_pcm_pointew_captuwe,
};

static unsigned showt snd_emu10k1x_ac97_wead(stwuct snd_ac97 *ac97,
					     unsigned showt weg)
{
	stwuct emu10k1x *emu = ac97->pwivate_data;
	unsigned wong fwags;
	unsigned showt vaw;
  
	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outb(weg, emu->powt + AC97ADDWESS);
	vaw = inw(emu->powt + AC97DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
	wetuwn vaw;
}

static void snd_emu10k1x_ac97_wwite(stwuct snd_ac97 *ac97,
				    unsigned showt weg, unsigned showt vaw)
{
	stwuct emu10k1x *emu = ac97->pwivate_data;
	unsigned wong fwags;
  
	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outb(weg, emu->powt + AC97ADDWESS);
	outw(vaw, emu->powt + AC97DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static int snd_emu10k1x_ac97(stwuct emu10k1x *chip)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_emu10k1x_ac97_wwite,
		.wead = snd_emu10k1x_ac97_wead,
	};
  
	eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;
	pbus->no_vwa = 1; /* we don't need VWA */

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	wetuwn snd_ac97_mixew(pbus, &ac97, &chip->ac97);
}

static void snd_emu10k1x_fwee(stwuct snd_cawd *cawd)
{
	stwuct emu10k1x *chip = cawd->pwivate_data;

	snd_emu10k1x_ptw_wwite(chip, TWIGGEW_CHANNEW, 0, 0);
	// disabwe intewwupts
	outw(0, chip->powt + INTE);
	// disabwe audio
	outw(HCFG_WOCKSOUNDCACHE, chip->powt + HCFG);
}

static iwqwetuwn_t snd_emu10k1x_intewwupt(int iwq, void *dev_id)
{
	unsigned int status;

	stwuct emu10k1x *chip = dev_id;
	stwuct emu10k1x_voice *pvoice = chip->voices;
	int i;
	int mask;

	status = inw(chip->powt + IPW);

	if (! status)
		wetuwn IWQ_NONE;

	// captuwe intewwupt
	if (status & (IPW_CAP_0_WOOP | IPW_CAP_0_HAWF_WOOP)) {
		stwuct emu10k1x_voice *cap_voice = &chip->captuwe_voice;
		if (cap_voice->use)
			snd_emu10k1x_pcm_intewwupt(chip, cap_voice);
		ewse
			snd_emu10k1x_intw_disabwe(chip, 
						  INTE_CAP_0_WOOP |
						  INTE_CAP_0_HAWF_WOOP);
	}
		
	mask = IPW_CH_0_WOOP|IPW_CH_0_HAWF_WOOP;
	fow (i = 0; i < 3; i++) {
		if (status & mask) {
			if (pvoice->use)
				snd_emu10k1x_pcm_intewwupt(chip, pvoice);
			ewse 
				snd_emu10k1x_intw_disabwe(chip, mask);
		}
		pvoice++;
		mask <<= 1;
	}
		
	if (status & (IPW_MIDITWANSBUFEMPTY|IPW_MIDIWECVBUFEMPTY)) {
		if (chip->midi.intewwupt)
			chip->midi.intewwupt(chip, status);
		ewse
			snd_emu10k1x_intw_disabwe(chip, INTE_MIDITXENABWE|INTE_MIDIWXENABWE);
	}
		
	// acknowwedge the intewwupt if necessawy
	outw(status, chip->powt + IPW);

	/* dev_dbg(chip->cawd->dev, "intewwupt %08x\n", status); */
	wetuwn IWQ_HANDWED;
}

static const stwuct snd_pcm_chmap_ewem suwwound_map[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ }
};

static const stwuct snd_pcm_chmap_ewem cwfe_map[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE } },
	{ }
};

static int snd_emu10k1x_pcm(stwuct emu10k1x *emu, int device)
{
	stwuct snd_pcm *pcm;
	const stwuct snd_pcm_chmap_ewem *map = NUWW;
	int eww;
	int captuwe = 0;
  
	if (device == 0)
		captuwe = 1;
	
	eww = snd_pcm_new(emu->cawd, "emu10k1x", device, 1, captuwe, &pcm);
	if (eww < 0)
		wetuwn eww;
  
	pcm->pwivate_data = emu;
	
	switch(device) {
	case 0:
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_emu10k1x_pwayback_ops);
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_emu10k1x_captuwe_ops);
		bweak;
	case 1:
	case 2:
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_emu10k1x_pwayback_ops);
		bweak;
	}

	pcm->info_fwags = 0;
	switch(device) {
	case 0:
		stwcpy(pcm->name, "EMU10K1X Fwont");
		map = snd_pcm_std_chmaps;
		bweak;
	case 1:
		stwcpy(pcm->name, "EMU10K1X Weaw");
		map = suwwound_map;
		bweak;
	case 2:
		stwcpy(pcm->name, "EMU10K1X Centew/WFE");
		map = cwfe_map;
		bweak;
	}
	emu->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &emu->pci->dev, 32*1024, 32*1024);
  
	wetuwn snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK, map, 2,
				     1 << 2, NUWW);
}

static int snd_emu10k1x_cweate(stwuct snd_cawd *cawd,
			       stwuct pci_dev *pci)
{
	stwuct emu10k1x *chip = cawd->pwivate_data;
	int eww;
	int ch;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(28)) < 0) {
		dev_eww(cawd->dev, "ewwow to set 28bit mask DMA\n");
		wetuwn -ENXIO;
	}

	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	spin_wock_init(&chip->emu_wock);
	spin_wock_init(&chip->voice_wock);
  
	eww = pci_wequest_wegions(pci, "EMU10K1X");
	if (eww < 0)
		wetuwn eww;
	chip->powt = pci_wesouwce_stawt(pci, 0);

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_emu10k1x_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "cannot gwab iwq %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_emu10k1x_fwee;
  
	chip->dma_buffew = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV,
						4 * 1024);
	if (!chip->dma_buffew)
		wetuwn -ENOMEM;

	pci_set_mastew(pci);
	/* wead wevision & sewiaw */
	chip->wevision = pci->wevision;
	pci_wead_config_dwowd(pci, PCI_SUBSYSTEM_VENDOW_ID, &chip->sewiaw);
	pci_wead_config_wowd(pci, PCI_SUBSYSTEM_ID, &chip->modew);
	dev_info(cawd->dev, "Modew %04x Wev %08x Sewiaw %08x\n", chip->modew,
		   chip->wevision, chip->sewiaw);

	outw(0, chip->powt + INTE);	

	fow(ch = 0; ch < 3; ch++) {
		chip->voices[ch].emu = chip;
		chip->voices[ch].numbew = ch;
	}

	/*
	 *  Init to 0x02109204 :
	 *  Cwock accuwacy    = 0     (1000ppm)
	 *  Sampwe Wate       = 2     (48kHz)
	 *  Audio Channew     = 1     (Weft of 2)
	 *  Souwce Numbew     = 0     (Unspecified)
	 *  Genewation Status = 1     (Owiginaw fow Cat Code 12)
	 *  Cat Code          = 12    (Digitaw Signaw Mixew)
	 *  Mode              = 0     (Mode 0)
	 *  Emphasis          = 0     (None)
	 *  CP                = 1     (Copywight unassewted)
	 *  AN                = 0     (Audio data)
	 *  P                 = 0     (Consumew)
	 */
	snd_emu10k1x_ptw_wwite(chip, SPCS0, 0,
			       chip->spdif_bits[0] = 
			       SPCS_CWKACCY_1000PPM | SPCS_SAMPWEWATE_48 |
			       SPCS_CHANNEWNUM_WEFT | SPCS_SOUWCENUM_UNSPEC |
			       SPCS_GENEWATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYWIGHT);
	snd_emu10k1x_ptw_wwite(chip, SPCS1, 0,
			       chip->spdif_bits[1] = 
			       SPCS_CWKACCY_1000PPM | SPCS_SAMPWEWATE_48 |
			       SPCS_CHANNEWNUM_WEFT | SPCS_SOUWCENUM_UNSPEC |
			       SPCS_GENEWATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYWIGHT);
	snd_emu10k1x_ptw_wwite(chip, SPCS2, 0,
			       chip->spdif_bits[2] = 
			       SPCS_CWKACCY_1000PPM | SPCS_SAMPWEWATE_48 |
			       SPCS_CHANNEWNUM_WEFT | SPCS_SOUWCENUM_UNSPEC |
			       SPCS_GENEWATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYWIGHT);

	snd_emu10k1x_ptw_wwite(chip, SPDIF_SEWECT, 0, 0x700); // disabwe SPDIF
	snd_emu10k1x_ptw_wwite(chip, WOUTING, 0, 0x1003F); // wouting
	snd_emu10k1x_gpio_wwite(chip, 0x1080); // anawog mode

	outw(HCFG_WOCKSOUNDCACHE|HCFG_AUDIOENABWE, chip->powt+HCFG);

	wetuwn 0;
}

static void snd_emu10k1x_pwoc_weg_wead(stwuct snd_info_entwy *entwy, 
				       stwuct snd_info_buffew *buffew)
{
	stwuct emu10k1x *emu = entwy->pwivate_data;
	unsigned wong vawue,vawue1,vawue2;
	unsigned wong fwags;
	int i;

	snd_ipwintf(buffew, "Wegistews:\n\n");
	fow(i = 0; i < 0x20; i+=4) {
		spin_wock_iwqsave(&emu->emu_wock, fwags);
		vawue = inw(emu->powt + i);
		spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
		snd_ipwintf(buffew, "Wegistew %02X: %08wX\n", i, vawue);
	}
	snd_ipwintf(buffew, "\nWegistews\n\n");
	fow(i = 0; i <= 0x48; i++) {
		vawue = snd_emu10k1x_ptw_wead(emu, i, 0);
		if(i < 0x10 || (i >= 0x20 && i < 0x40)) {
			vawue1 = snd_emu10k1x_ptw_wead(emu, i, 1);
			vawue2 = snd_emu10k1x_ptw_wead(emu, i, 2);
			snd_ipwintf(buffew, "%02X: %08wX %08wX %08wX\n", i, vawue, vawue1, vawue2);
		} ewse {
			snd_ipwintf(buffew, "%02X: %08wX\n", i, vawue);
		}
	}
}

static void snd_emu10k1x_pwoc_weg_wwite(stwuct snd_info_entwy *entwy, 
					stwuct snd_info_buffew *buffew)
{
	stwuct emu10k1x *emu = entwy->pwivate_data;
	chaw wine[64];
	unsigned int weg, channew_id , vaw;

	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%x %x %x", &weg, &channew_id, &vaw) != 3)
			continue;

		if (weg < 0x49 && channew_id <= 2)
			snd_emu10k1x_ptw_wwite(emu, weg, channew_id, vaw);
	}
}

static int snd_emu10k1x_pwoc_init(stwuct emu10k1x *emu)
{
	snd_cawd_ww_pwoc_new(emu->cawd, "emu10k1x_wegs", emu,
			     snd_emu10k1x_pwoc_weg_wead,
			     snd_emu10k1x_pwoc_weg_wwite);
	wetuwn 0;
}

#define snd_emu10k1x_shawed_spdif_info	snd_ctw_boowean_mono_info

static int snd_emu10k1x_shawed_spdif_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct emu10k1x *emu = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = (snd_emu10k1x_ptw_wead(emu, SPDIF_SEWECT, 0) == 0x700) ? 0 : 1;

	wetuwn 0;
}

static int snd_emu10k1x_shawed_spdif_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct emu10k1x *emu = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;

	vaw = ucontwow->vawue.integew.vawue[0] ;

	if (vaw) {
		// enabwe spdif output
		snd_emu10k1x_ptw_wwite(emu, SPDIF_SEWECT, 0, 0x000);
		snd_emu10k1x_ptw_wwite(emu, WOUTING, 0, 0x700);
		snd_emu10k1x_gpio_wwite(emu, 0x1000);
	} ewse {
		// disabwe spdif output
		snd_emu10k1x_ptw_wwite(emu, SPDIF_SEWECT, 0, 0x700);
		snd_emu10k1x_ptw_wwite(emu, WOUTING, 0, 0x1003F);
		snd_emu10k1x_gpio_wwite(emu, 0x1080);
	}
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_emu10k1x_shawed_spdif =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Anawog/Digitaw Output Jack",
	.info =		snd_emu10k1x_shawed_spdif_info,
	.get =		snd_emu10k1x_shawed_spdif_get,
	.put =		snd_emu10k1x_shawed_spdif_put
};

static int snd_emu10k1x_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_emu10k1x_spdif_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct emu10k1x *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	ucontwow->vawue.iec958.status[0] = (emu->spdif_bits[idx] >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (emu->spdif_bits[idx] >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (emu->spdif_bits[idx] >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (emu->spdif_bits[idx] >> 24) & 0xff;
	wetuwn 0;
}

static int snd_emu10k1x_spdif_get_mask(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

static int snd_emu10k1x_spdif_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct emu10k1x *emu = snd_kcontwow_chip(kcontwow);
	unsigned int idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	int change;
	unsigned int vaw;

	vaw = (ucontwow->vawue.iec958.status[0] << 0) |
		(ucontwow->vawue.iec958.status[1] << 8) |
		(ucontwow->vawue.iec958.status[2] << 16) |
		(ucontwow->vawue.iec958.status[3] << 24);
	change = vaw != emu->spdif_bits[idx];
	if (change) {
		snd_emu10k1x_ptw_wwite(emu, SPCS0 + idx, 0, vaw);
		emu->spdif_bits[idx] = vaw;
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_emu10k1x_spdif_mask_contwow =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =        SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
	.count =	3,
	.info =         snd_emu10k1x_spdif_info,
	.get =          snd_emu10k1x_spdif_get_mask
};

static const stwuct snd_kcontwow_new snd_emu10k1x_spdif_contwow =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =         SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.count =	3,
	.info =         snd_emu10k1x_spdif_info,
	.get =          snd_emu10k1x_spdif_get,
	.put =          snd_emu10k1x_spdif_put
};

static int snd_emu10k1x_mixew(stwuct emu10k1x *emu)
{
	int eww;
	stwuct snd_kcontwow *kctw;
	stwuct snd_cawd *cawd = emu->cawd;

	kctw = snd_ctw_new1(&snd_emu10k1x_spdif_mask_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_emu10k1x_shawed_spdif, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;
	kctw = snd_ctw_new1(&snd_emu10k1x_spdif_contwow, emu);
	if (!kctw)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(cawd, kctw);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

#define EMU10K1X_MIDI_MODE_INPUT	(1<<0)
#define EMU10K1X_MIDI_MODE_OUTPUT	(1<<1)

static inwine unsigned chaw mpu401_wead(stwuct emu10k1x *emu, stwuct emu10k1x_midi *mpu, int idx)
{
	wetuwn (unsigned chaw)snd_emu10k1x_ptw_wead(emu, mpu->powt + idx, 0);
}

static inwine void mpu401_wwite(stwuct emu10k1x *emu, stwuct emu10k1x_midi *mpu, int data, int idx)
{
	snd_emu10k1x_ptw_wwite(emu, mpu->powt + idx, 0, data);
}

#define mpu401_wwite_data(emu, mpu, data)	mpu401_wwite(emu, mpu, data, 0)
#define mpu401_wwite_cmd(emu, mpu, data)	mpu401_wwite(emu, mpu, data, 1)
#define mpu401_wead_data(emu, mpu)		mpu401_wead(emu, mpu, 0)
#define mpu401_wead_stat(emu, mpu)		mpu401_wead(emu, mpu, 1)

#define mpu401_input_avaiw(emu,mpu)	(!(mpu401_wead_stat(emu,mpu) & 0x80))
#define mpu401_output_weady(emu,mpu)	(!(mpu401_wead_stat(emu,mpu) & 0x40))

#define MPU401_WESET		0xff
#define MPU401_ENTEW_UAWT	0x3f
#define MPU401_ACK		0xfe

static void mpu401_cweaw_wx(stwuct emu10k1x *emu, stwuct emu10k1x_midi *mpu)
{
	int timeout = 100000;
	fow (; timeout > 0 && mpu401_input_avaiw(emu, mpu); timeout--)
		mpu401_wead_data(emu, mpu);
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		dev_eww(emu->cawd->dev,
			"cmd: cweaw wx timeout (status = 0x%x)\n",
			mpu401_wead_stat(emu, mpu));
#endif
}

/*

 */

static void do_emu10k1x_midi_intewwupt(stwuct emu10k1x *emu,
				       stwuct emu10k1x_midi *midi, unsigned int status)
{
	unsigned chaw byte;

	if (midi->wmidi == NUWW) {
		snd_emu10k1x_intw_disabwe(emu, midi->tx_enabwe | midi->wx_enabwe);
		wetuwn;
	}

	spin_wock(&midi->input_wock);
	if ((status & midi->ipw_wx) && mpu401_input_avaiw(emu, midi)) {
		if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) {
			mpu401_cweaw_wx(emu, midi);
		} ewse {
			byte = mpu401_wead_data(emu, midi);
			if (midi->substweam_input)
				snd_wawmidi_weceive(midi->substweam_input, &byte, 1);
		}
	}
	spin_unwock(&midi->input_wock);

	spin_wock(&midi->output_wock);
	if ((status & midi->ipw_tx) && mpu401_output_weady(emu, midi)) {
		if (midi->substweam_output &&
		    snd_wawmidi_twansmit(midi->substweam_output, &byte, 1) == 1) {
			mpu401_wwite_data(emu, midi, byte);
		} ewse {
			snd_emu10k1x_intw_disabwe(emu, midi->tx_enabwe);
		}
	}
	spin_unwock(&midi->output_wock);
}

static void snd_emu10k1x_midi_intewwupt(stwuct emu10k1x *emu, unsigned int status)
{
	do_emu10k1x_midi_intewwupt(emu, &emu->midi, status);
}

static int snd_emu10k1x_midi_cmd(stwuct emu10k1x * emu,
				  stwuct emu10k1x_midi *midi, unsigned chaw cmd, int ack)
{
	unsigned wong fwags;
	int timeout, ok;

	spin_wock_iwqsave(&midi->input_wock, fwags);
	mpu401_wwite_data(emu, midi, 0x00);
	/* mpu401_cweaw_wx(emu, midi); */

	mpu401_wwite_cmd(emu, midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		whiwe (!ok && timeout-- > 0) {
			if (mpu401_input_avaiw(emu, midi)) {
				if (mpu401_wead_data(emu, midi) == MPU401_ACK)
					ok = 1;
			}
		}
		if (!ok && mpu401_wead_data(emu, midi) == MPU401_ACK)
			ok = 1;
	} ewse {
		ok = 1;
	}
	spin_unwock_iwqwestowe(&midi->input_wock, fwags);
	if (!ok) {
		dev_eww(emu->cawd->dev,
			"midi_cmd: 0x%x faiwed at 0x%wx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->powt,
			   mpu401_wead_stat(emu, midi),
			   mpu401_wead_data(emu, midi));
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_emu10k1x_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;
	
	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	midi->midi_mode |= EMU10K1X_MIDI_MODE_INPUT;
	midi->substweam_input = substweam;
	if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_WESET, 1))
			goto ewwow_out;
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_ENTEW_UAWT, 1))
			goto ewwow_out;
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;

ewwow_out:
	wetuwn -EIO;
}

static int snd_emu10k1x_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	midi->midi_mode |= EMU10K1X_MIDI_MODE_OUTPUT;
	midi->substweam_output = substweam;
	if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_WESET, 1))
			goto ewwow_out;
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_ENTEW_UAWT, 1))
			goto ewwow_out;
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;

ewwow_out:
	wetuwn -EIO;
}

static int snd_emu10k1x_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;
	int eww = 0;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	snd_emu10k1x_intw_disabwe(emu, midi->wx_enabwe);
	midi->midi_mode &= ~EMU10K1X_MIDI_MODE_INPUT;
	midi->substweam_input = NUWW;
	if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		eww = snd_emu10k1x_midi_cmd(emu, midi, MPU401_WESET, 0);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn eww;
}

static int snd_emu10k1x_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;
	int eww = 0;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	snd_emu10k1x_intw_disabwe(emu, midi->tx_enabwe);
	midi->midi_mode &= ~EMU10K1X_MIDI_MODE_OUTPUT;
	midi->substweam_output = NUWW;
	if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_INPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		eww = snd_emu10k1x_midi_cmd(emu, midi, MPU401_WESET, 0);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn eww;
}

static void snd_emu10k1x_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn;

	if (up)
		snd_emu10k1x_intw_enabwe(emu, midi->wx_enabwe);
	ewse
		snd_emu10k1x_intw_disabwe(emu, midi->wx_enabwe);
}

static void snd_emu10k1x_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct emu10k1x *emu;
	stwuct emu10k1x_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		wetuwn;

	if (up) {
		int max = 4;
		unsigned chaw byte;
	
		/* twy to send some amount of bytes hewe befowe intewwupts */
		spin_wock_iwqsave(&midi->output_wock, fwags);
		whiwe (max > 0) {
			if (mpu401_output_weady(emu, midi)) {
				if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT) ||
				    snd_wawmidi_twansmit(substweam, &byte, 1) != 1) {
					/* no mowe data */
					spin_unwock_iwqwestowe(&midi->output_wock, fwags);
					wetuwn;
				}
				mpu401_wwite_data(emu, midi, byte);
				max--;
			} ewse {
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&midi->output_wock, fwags);
		snd_emu10k1x_intw_enabwe(emu, midi->tx_enabwe);
	} ewse {
		snd_emu10k1x_intw_disabwe(emu, midi->tx_enabwe);
	}
}

/*

 */

static const stwuct snd_wawmidi_ops snd_emu10k1x_midi_output =
{
	.open =		snd_emu10k1x_midi_output_open,
	.cwose =	snd_emu10k1x_midi_output_cwose,
	.twiggew =	snd_emu10k1x_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_emu10k1x_midi_input =
{
	.open =		snd_emu10k1x_midi_input_open,
	.cwose =	snd_emu10k1x_midi_input_cwose,
	.twiggew =	snd_emu10k1x_midi_input_twiggew,
};

static void snd_emu10k1x_midi_fwee(stwuct snd_wawmidi *wmidi)
{
	stwuct emu10k1x_midi *midi = wmidi->pwivate_data;
	midi->intewwupt = NUWW;
	midi->wmidi = NUWW;
}

static int emu10k1x_midi_init(stwuct emu10k1x *emu,
			      stwuct emu10k1x_midi *midi, int device,
			      chaw *name)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(emu->cawd, name, device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;
	midi->emu = emu;
	spin_wock_init(&midi->open_wock);
	spin_wock_init(&midi->input_wock);
	spin_wock_init(&midi->output_wock);
	stwcpy(wmidi->name, name);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_emu10k1x_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_emu10k1x_midi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
	                     SNDWV_WAWMIDI_INFO_INPUT |
	                     SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = midi;
	wmidi->pwivate_fwee = snd_emu10k1x_midi_fwee;
	midi->wmidi = wmidi;
	wetuwn 0;
}

static int snd_emu10k1x_midi(stwuct emu10k1x *emu)
{
	stwuct emu10k1x_midi *midi = &emu->midi;
	int eww;

	eww = emu10k1x_midi_init(emu, midi, 0, "EMU10K1X MPU-401 (UAWT)");
	if (eww < 0)
		wetuwn eww;

	midi->tx_enabwe = INTE_MIDITXENABWE;
	midi->wx_enabwe = INTE_MIDIWXENABWE;
	midi->powt = MUDATA;
	midi->ipw_tx = IPW_MIDITWANSBUFEMPTY;
	midi->ipw_wx = IPW_MIDIWECVBUFEMPTY;
	midi->intewwupt = snd_emu10k1x_midi_intewwupt;
	wetuwn 0;
}

static int __snd_emu10k1x_pwobe(stwuct pci_dev *pci,
				const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct emu10k1x *chip;
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

	eww = snd_emu10k1x_cweate(cawd, pci);
	if (eww < 0)
		wetuwn eww;

	eww = snd_emu10k1x_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_emu10k1x_pcm(chip, 1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_emu10k1x_pcm(chip, 2);
	if (eww < 0)
		wetuwn eww;

	eww = snd_emu10k1x_ac97(chip);
	if (eww < 0)
		wetuwn eww;

	eww = snd_emu10k1x_mixew(chip);
	if (eww < 0)
		wetuwn eww;
	
	eww = snd_emu10k1x_midi(chip);
	if (eww < 0)
		wetuwn eww;

	snd_emu10k1x_pwoc_init(chip);

	stwcpy(cawd->dwivew, "EMU10K1X");
	stwcpy(cawd->showtname, "Deww Sound Bwastew Wive!");
	spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
		cawd->showtname, chip->powt, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_emu10k1x_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_emu10k1x_pwobe(pci, pci_id));
}

// PCI IDs
static const stwuct pci_device_id snd_emu10k1x_ids[] = {
	{ PCI_VDEVICE(CWEATIVE, 0x0006), 0 },	/* Deww OEM vewsion (EMU10K1) */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, snd_emu10k1x_ids);

// pci_dwivew definition
static stwuct pci_dwivew emu10k1x_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_emu10k1x_ids,
	.pwobe = snd_emu10k1x_pwobe,
};

moduwe_pci_dwivew(emu10k1x_dwivew);
