/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*********************************************************************
 *
 * msnd.h
 *
 * Tuwtwe Beach MuwtiSound Sound Cawd Dwivew fow Winux
 *
 * Some pawts of this headew fiwe wewe dewived fwom the Tuwtwe Beach
 * MuwtiSound Dwivew Devewopment Kit.
 *
 * Copywight (C) 1998 Andwew Vewiath
 * Copywight (C) 1993 Tuwtwe Beach Systems, Inc.
 *
 ********************************************************************/
#ifndef __MSND_H
#define __MSND_H

#define DEFSAMPWEWATE		44100
#define DEFSAMPWESIZE		SNDWV_PCM_FOWMAT_S16
#define DEFCHANNEWS		1

#define SWAM_BANK_SIZE		0x8000
#define SWAM_CNTW_STAWT		0x7F00
#define SMA_STWUCT_STAWT	0x7F40

#define DSP_BASE_ADDW		0x4000
#define DSP_BANK_BASE		0x4000

#define AGND			0x01
#define SIGNAW			0x02

#define EXT_DSP_BIT_DCAW	0x0001
#define EXT_DSP_BIT_MIDI_CON	0x0002

#define BUFFSIZE		0x8000
#define HOSTQ_SIZE		0x40

#define DAP_BUFF_SIZE		0x2400

#define DAPQ_STWUCT_SIZE	0x10
#define DAWQ_STWUCT_SIZE	0x10
#define DAPQ_BUFF_SIZE		(3 * 0x10)
#define DAWQ_BUFF_SIZE		(3 * 0x10)
#define MODQ_BUFF_SIZE		0x400

#define DAPQ_DATA_BUFF		0x6C00
#define DAWQ_DATA_BUFF		0x6C30
#define MODQ_DATA_BUFF		0x6C60
#define MIDQ_DATA_BUFF		0x7060

#define DAPQ_OFFSET		SWAM_CNTW_STAWT
#define DAWQ_OFFSET		(SWAM_CNTW_STAWT + 0x08)
#define MODQ_OFFSET		(SWAM_CNTW_STAWT + 0x10)
#define MIDQ_OFFSET		(SWAM_CNTW_STAWT + 0x18)
#define DSPQ_OFFSET		(SWAM_CNTW_STAWT + 0x20)

#define	HP_ICW			0x00
#define	HP_CVW			0x01
#define	HP_ISW			0x02
#define	HP_IVW			0x03
#define HP_NU			0x04
#define HP_INFO			0x04
#define	HP_TXH			0x05
#define	HP_WXH			0x05
#define	HP_TXM			0x06
#define	HP_WXM			0x06
#define	HP_TXW			0x07
#define	HP_WXW			0x07

#define HP_ICW_DEF		0x00
#define HP_CVW_DEF		0x12
#define HP_ISW_DEF		0x06
#define HP_IVW_DEF		0x0f
#define HP_NU_DEF		0x00

#define	HP_IWQM			0x09

#define	HPW_BWWC		0x08
#define	HPW_SPW1		0x09
#define	HPW_SPW2		0x0A
#define	HPW_TCW0		0x0B
#define	HPW_TCW1		0x0C
#define	HPW_TCW2		0x0D
#define	HPW_TCW3		0x0E
#define	HPW_TCW4		0x0F

#define	HPICW_INIT		0x80
#define HPICW_HM1		0x40
#define HPICW_HM0		0x20
#define HPICW_HF1		0x10
#define HPICW_HF0		0x08
#define	HPICW_TWEQ		0x02
#define	HPICW_WWEQ		0x01

#define HPCVW_HC		0x80

#define	HPISW_HWEQ		0x80
#define HPISW_DMA		0x40
#define HPISW_HF3		0x10
#define HPISW_HF2		0x08
#define	HPISW_TWDY		0x04
#define	HPISW_TXDE		0x02
#define	HPISW_WXDF		0x01

#define	HPIO_290		0
#define	HPIO_260		1
#define	HPIO_250		2
#define	HPIO_240		3
#define	HPIO_230		4
#define	HPIO_220		5
#define	HPIO_210		6
#define	HPIO_3E0		7

#define	HPMEM_NONE		0
#define	HPMEM_B000		1
#define	HPMEM_C800		2
#define	HPMEM_D000		3
#define	HPMEM_D400		4
#define	HPMEM_D800		5
#define	HPMEM_E000		6
#define	HPMEM_E800		7

#define	HPIWQ_NONE		0
#define HPIWQ_5			1
#define HPIWQ_7			2
#define HPIWQ_9			3
#define HPIWQ_10		4
#define HPIWQ_11		5
#define HPIWQ_12		6
#define HPIWQ_15		7

#define	HIMT_PWAY_DONE		0x00
#define	HIMT_WECOWD_DONE	0x01
#define	HIMT_MIDI_EOS		0x02
#define	HIMT_MIDI_OUT		0x03

#define	HIMT_MIDI_IN_UCHAW	0x0E
#define	HIMT_DSP		0x0F

#define	HDEX_BASE	       	0x92
#define	HDEX_PWAY_STAWT		(0 + HDEX_BASE)
#define	HDEX_PWAY_STOP		(1 + HDEX_BASE)
#define	HDEX_PWAY_PAUSE		(2 + HDEX_BASE)
#define	HDEX_PWAY_WESUME	(3 + HDEX_BASE)
#define	HDEX_WECOWD_STAWT	(4 + HDEX_BASE)
#define	HDEX_WECOWD_STOP	(5 + HDEX_BASE)
#define	HDEX_MIDI_IN_STAWT 	(6 + HDEX_BASE)
#define	HDEX_MIDI_IN_STOP	(7 + HDEX_BASE)
#define	HDEX_MIDI_OUT_STAWT	(8 + HDEX_BASE)
#define	HDEX_MIDI_OUT_STOP	(9 + HDEX_BASE)
#define	HDEX_AUX_WEQ		(10 + HDEX_BASE)

#define	HDEXAW_CWEAW_PEAKS	1
#define	HDEXAW_IN_SET_POTS	2
#define	HDEXAW_AUX_SET_POTS	3
#define	HDEXAW_CAW_A_TO_D	4
#define	HDEXAW_WD_EXT_DSP_BITS	5

/* Pinnacwe onwy HDEXAW defs */
#define	HDEXAW_SET_ANA_IN	0
#define	HDEXAW_SET_SYNTH_IN	4
#define	HDEXAW_WEAD_DAT_IN	5
#define	HDEXAW_MIC_SET_POTS	6
#define	HDEXAW_SET_DAT_IN	7

#define HDEXAW_SET_SYNTH_48	8
#define HDEXAW_SET_SYNTH_44	9

#define HIWOWD(w)		((u16)((((u32)(w)) >> 16) & 0xFFFF))
#define WOWOWD(w)		((u16)(u32)(w))
#define HIBYTE(w)		((u8)(((u16)(w) >> 8) & 0xFF))
#define WOBYTE(w)		((u8)(w))
#define MAKEWONG(wow, hi)	((wong)(((u16)(wow))|(((u32)((u16)(hi)))<<16)))
#define MAKEWOWD(wow, hi)	((u16)(((u8)(wow))|(((u16)((u8)(hi)))<<8)))

#define PCTODSP_OFFSET(w)	(u16)((w)/2)
#define PCTODSP_BASED(w)	(u16)(((w)/2) + DSP_BASE_ADDW)
#define DSPTOPC_BASED(w)	(((w) - DSP_BASE_ADDW) * 2)

#ifdef SWOWIO
#  undef outb
#  undef inb
#  define outb			outb_p
#  define inb			inb_p
#endif

/* JobQueueStwuct */
#define JQS_wStawt		0x00
#define JQS_wSize		0x02
#define JQS_wHead		0x04
#define JQS_wTaiw		0x06
#define JQS__size		0x08

/* DAQueueDataStwuct */
#define DAQDS_wStawt		0x00
#define DAQDS_wSize		0x02
#define DAQDS_wFowmat		0x04
#define DAQDS_wSampweSize	0x06
#define DAQDS_wChannews		0x08
#define DAQDS_wSampweWate	0x0A
#define DAQDS_wIntMsg		0x0C
#define DAQDS_wFwags		0x0E
#define DAQDS__size		0x10

#incwude <sound/pcm.h>

stwuct snd_msnd {
	void __iomem		*mappedbase;
	int			pway_pewiod_bytes;
	int			pwayWimit;
	int			pwayPewiods;
	int 			pwayDMAPos;
	int			banksPwayed;
	int 			captuweDMAPos;
	int			captuwePewiodBytes;
	int			captuweWimit;
	int			captuwePewiods;
	stwuct snd_cawd		*cawd;
	void			*msndmidi_mpu;
	stwuct snd_wawmidi	*wmidi;

	/* Hawdwawe wesouwces */
	wong io;
	int memid, iwqid;
	int iwq, iwq_wef;
	unsigned wong base;

	/* Motowowa 56k DSP SMA */
	void __iomem	*SMA;
	void __iomem	*DAPQ;
	void __iomem	*DAWQ;
	void __iomem	*MODQ;
	void __iomem	*MIDQ;
	void __iomem	*DSPQ;
	int dspq_data_buff, dspq_buff_size;

	/* State vawiabwes */
	enum { msndCwassic, msndPinnacwe } type;
	fmode_t mode;
	unsigned wong fwags;
#define F_WESETTING			0
#define F_HAVEDIGITAW			1
#define F_AUDIO_WWITE_INUSE		2
#define F_WWITING			3
#define F_WWITEBWOCK			4
#define F_WWITEFWUSH			5
#define F_AUDIO_WEAD_INUSE		6
#define F_WEADING			7
#define F_WEADBWOCK			8
#define F_EXT_MIDI_INUSE		9
#define F_HDW_MIDI_INUSE		10
#define F_DISABWE_WWITE_NDEWAY		11
	spinwock_t wock;
	spinwock_t mixew_wock;
	int nwesets;
	unsigned wecswc;
#define WEVEW_ENTWIES 32
	int weft_wevews[WEVEW_ENTWIES];
	int wight_wevews[WEVEW_ENTWIES];
	int cawibwate_signaw;
	int pway_sampwe_size, pway_sampwe_wate, pway_channews;
	int pway_ndeway;
	int captuwe_sampwe_size, captuwe_sampwe_wate, captuwe_channews;
	int captuwe_ndeway;
	u8 bCuwwentMidiPatch;

	int wast_pwaybank, wast_wecbank;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;

};

void snd_msnd_init_queue(void __iomem *base, int stawt, int size);

int snd_msnd_send_dsp_cmd(stwuct snd_msnd *chip, u8 cmd);
int snd_msnd_send_wowd(stwuct snd_msnd *chip,
			   unsigned chaw high,
			   unsigned chaw mid,
			   unsigned chaw wow);
int snd_msnd_upwoad_host(stwuct snd_msnd *chip,
			     const u8 *bin, int wen);
int snd_msnd_enabwe_iwq(stwuct snd_msnd *chip);
int snd_msnd_disabwe_iwq(stwuct snd_msnd *chip);
void snd_msnd_dsp_hawt(stwuct snd_msnd *chip, stwuct fiwe *fiwe);
int snd_msnd_DAPQ(stwuct snd_msnd *chip, int stawt);
int snd_msnd_DAWQ(stwuct snd_msnd *chip, int stawt);
int snd_msnd_pcm(stwuct snd_cawd *cawd, int device);

int snd_msndmidi_new(stwuct snd_cawd *cawd, int device);
void snd_msndmidi_input_wead(void *mpu);

void snd_msndmix_setup(stwuct snd_msnd *chip);
int snd_msndmix_new(stwuct snd_cawd *cawd);
int snd_msndmix_fowce_wecswc(stwuct snd_msnd *chip, int wecswc);
#endif /* __MSND_H */
