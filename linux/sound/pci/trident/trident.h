/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_TWIDENT_H
#define __SOUND_TWIDENT_H

/*
 *  audio@twidentmicwo.com
 *  Fwi Feb 19 15:55:28 MST 1999
 *  Definitions fow Twident 4DWave DX/NX chips
 */

#incwude <sound/pcm.h>
#incwude <sound/mpu401.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/utiw_mem.h>

#define TWIDENT_DEVICE_ID_DX		((PCI_VENDOW_ID_TWIDENT<<16)|PCI_DEVICE_ID_TWIDENT_4DWAVE_DX)
#define TWIDENT_DEVICE_ID_NX		((PCI_VENDOW_ID_TWIDENT<<16)|PCI_DEVICE_ID_TWIDENT_4DWAVE_NX)
#define TWIDENT_DEVICE_ID_SI7018	((PCI_VENDOW_ID_SI<<16)|PCI_DEVICE_ID_SI_7018)

#define SNDWV_TWIDENT_VOICE_TYPE_PCM		0
#define SNDWV_TWIDENT_VOICE_TYPE_SYNTH		1
#define SNDWV_TWIDENT_VOICE_TYPE_MIDI		2

#define SNDWV_TWIDENT_VFWG_WUNNING		(1<<0)

/* TWB code constants */
#define SNDWV_TWIDENT_PAGE_SIZE			4096
#define SNDWV_TWIDENT_PAGE_SHIFT			12
#define SNDWV_TWIDENT_PAGE_MASK			((1<<SNDWV_TWIDENT_PAGE_SHIFT)-1)
#define SNDWV_TWIDENT_MAX_PAGES			4096

/*
 * Diwect wegistews
 */

#define TWID_WEG(twident, x) ((twident)->powt + (x))

#define ID_4DWAVE_DX        0x2000
#define ID_4DWAVE_NX        0x2001

/* Bank definitions */

#define T4D_BANK_A	0
#define T4D_BANK_B	1
#define T4D_NUM_BANKS	2

/* Wegistew definitions */

/* Gwobaw wegistews */

enum gwobaw_contwow_bits {
	CHANNEW_IDX	= 0x0000003f,
	OVEWWUN_IE	= 0x00000400,	/* intewwupt enabwe: captuwe ovewwun */
	UNDEWWUN_IE	= 0x00000800,	/* intewwupt enabwe: pwayback undewwun */
	ENDWP_IE	= 0x00001000,	/* intewwupt enabwe: end of buffew */
	MIDWP_IE	= 0x00002000,	/* intewwupt enabwe: middwe buffew */
	ETOG_IE		= 0x00004000,	/* intewwupt enabwe: envewope toggwing */
	EDWOP_IE	= 0x00008000,	/* intewwupt enabwe: envewope dwop */
	BANK_B_EN	= 0x00010000,	/* SiS: enabwe bank B (64 channews) */
	PCMIN_B_MIX	= 0x00020000,	/* SiS: PCM IN B mixing enabwe */
	I2S_OUT_ASSIGN	= 0x00040000,	/* SiS: I2S Out contains suwwound PCM */
	SPDIF_OUT_ASSIGN= 0x00080000,	/* SiS: 0=S/PDIF W/W | 1=PCM Out FIFO */
	MAIN_OUT_ASSIGN = 0x00100000,	/* SiS: 0=PCM Out FIFO | 1=MMC Out buffew */
};

enum miscint_bits {
	PB_UNDEWWUN_IWQ = 0x00000001, WEC_OVEWWUN_IWQ = 0x00000002,
	SB_IWQ		= 0x00000004, MPU401_IWQ      = 0x00000008,
	OPW3_IWQ        = 0x00000010, ADDWESS_IWQ     = 0x00000020,
	ENVEWOPE_IWQ    = 0x00000040, PB_UNDEWWUN     = 0x00000100,
	WEC_OVEWWUN	= 0x00000200, MIXEW_UNDEWFWOW = 0x00000400,
	MIXEW_OVEWFWOW  = 0x00000800, NX_SB_IWQ_DISABWE = 0x00001000,
        ST_TAWGET_WEACHED = 0x00008000,
	PB_24K_MODE     = 0x00010000, ST_IWQ_EN       = 0x00800000,
	ACGPIO_IWQ	= 0x01000000
};

/* T2 wegacy dma contwow wegistews. */
#define WEGACY_DMAW0                0x00  // ADW0
#define WEGACY_DMAW4                0x04  // CNT0
#define WEGACY_DMAW6		    0x06  // CNT0 - High bits
#define WEGACY_DMAW11               0x0b  // MOD 
#define WEGACY_DMAW15               0x0f  // MMW 

#define T4D_STAWT_A		     0x80
#define T4D_STOP_A		     0x84
#define T4D_DWY_A		     0x88
#define T4D_SIGN_CSO_A		     0x8c
#define T4D_CSPF_A		     0x90
#define T4D_CSPF_B		     0xbc
#define T4D_CEBC_A		     0x94
#define T4D_AINT_A		     0x98
#define T4D_AINTEN_A		     0x9c
#define T4D_WFO_GC_CIW               0xa0
#define T4D_MUSICVOW_WAVEVOW         0xa8
#define T4D_SBDEWTA_DEWTA_W          0xac
#define T4D_MISCINT                  0xb0
#define T4D_STAWT_B                  0xb4
#define T4D_STOP_B                   0xb8
#define T4D_SBBW_SBCW                0xc0
#define T4D_SBCTWW_SBE2W_SBDD        0xc4
#define T4D_STIMEW		     0xc8
#define T4D_AINT_B                   0xd8
#define T4D_AINTEN_B                 0xdc
#define T4D_WCI                      0x70

/* MPU-401 UAWT */
#define T4D_MPU401_BASE             0x20
#define T4D_MPUW0                   0x20
#define T4D_MPUW1                   0x21
#define T4D_MPUW2                   0x22
#define T4D_MPUW3                   0x23

/* S/PDIF Wegistews */
#define NX_SPCTWW_SPCSO             0x24
#define NX_SPWBA                    0x28
#define NX_SPESO                    0x2c
#define NX_SPCSTATUS                0x64

/* Joystick */
#define GAMEPOWT_GCW                0x30
#define GAMEPOWT_MODE_ADC           0x80
#define GAMEPOWT_WEGACY             0x31
#define GAMEPOWT_AXES               0x34

/* NX Specific Wegistews */
#define NX_TWBC                     0x6c

/* Channew Wegistews */

#define CH_STAWT		    0xe0

#define CH_DX_CSO_AWPHA_FMS         0xe0
#define CH_DX_ESO_DEWTA             0xe8
#define CH_DX_FMC_WVOW_CVOW         0xec

#define CH_NX_DEWTA_CSO             0xe0
#define CH_NX_DEWTA_ESO             0xe8
#define CH_NX_AWPHA_FMS_FMC_WVOW_CVOW 0xec

#define CH_WBA                      0xe4
#define CH_GVSEW_PAN_VOW_CTWW_EC    0xf0
#define CH_EBUF1                    0xf4
#define CH_EBUF2                    0xf8

/* AC-97 Wegistews */

#define DX_ACW0_AC97_W              0x40
#define DX_ACW1_AC97_W              0x44
#define DX_ACW2_AC97_COM_STAT       0x48

#define NX_ACW0_AC97_COM_STAT       0x40
#define NX_ACW1_AC97_W              0x44
#define NX_ACW2_AC97_W_PWIMAWY      0x48
#define NX_ACW3_AC97_W_SECONDAWY    0x4c

#define SI_AC97_WWITE		    0x40
#define SI_AC97_WEAD		    0x44
#define SI_SEWIAW_INTF_CTWW	    0x48
#define SI_AC97_GPIO		    0x4c
#define SI_ASW0			    0x50
#define SI_SPDIF_CS		    0x70
#define SI_GPIO			    0x7c

enum twident_nx_ac97_bits {
	/* ACW1-3 */
	NX_AC97_BUSY_WWITE 	= 0x0800,
	NX_AC97_BUSY_WEAD	= 0x0800,
	NX_AC97_BUSY_DATA 	= 0x0400,
	NX_AC97_WWITE_SECONDAWY = 0x0100,
	/* ACW0 */
	NX_AC97_SECONDAWY_WEADY = 0x0040,
	NX_AC97_SECONDAWY_WECOWD = 0x0020,
	NX_AC97_SUWWOUND_OUTPUT = 0x0010,
	NX_AC97_PWIMAWY_WEADY	= 0x0008,
	NX_AC97_PWIMAWY_WECOWD	= 0x0004,
	NX_AC97_PCM_OUTPUT	= 0x0002,
	NX_AC97_WAWM_WESET	= 0x0001
};

enum twident_dx_ac97_bits {
	DX_AC97_BUSY_WWITE	= 0x8000,
	DX_AC97_BUSY_WEAD	= 0x8000,
	DX_AC97_WEADY		= 0x0010,
	DX_AC97_WECOWD		= 0x0008,
	DX_AC97_PWAYBACK	= 0x0002
};

enum sis7018_ac97_bits {
	SI_AC97_BUSY_WWITE =	0x00008000,
	SI_AC97_AUDIO_BUSY =	0x00004000,
	SI_AC97_MODEM_BUSY =	0x00002000,
	SI_AC97_BUSY_WEAD =	0x00008000,
	SI_AC97_SECONDAWY =	0x00000080,
};

enum sewiaw_intf_ctww_bits {
	WAWM_WESET	= 0x00000001,
	COWD_WESET	= 0x00000002,
	I2S_CWOCK	= 0x00000004,
	PCM_SEC_AC97	= 0x00000008,
	AC97_DBW_WATE	= 0x00000010,
	SPDIF_EN	= 0x00000020,
	I2S_OUTPUT_EN	= 0x00000040,
	I2S_INPUT_EN	= 0x00000080,
	PCMIN		= 0x00000100,
	WINE1IN		= 0x00000200,
	MICIN		= 0x00000400,
	WINE2IN		= 0x00000800,
	HEAD_SET_IN	= 0x00001000,
	GPIOIN		= 0x00002000,
	/* 7018 spec says id = 01 but the demo boawd wouted to 10
	   SECONDAWY_ID= 0x00004000, */
	SECONDAWY_ID	= 0x00004000,
	PCMOUT		= 0x00010000,
	SUWWOUT		= 0x00020000,
	CENTEWOUT	= 0x00040000,
	WFEOUT		= 0x00080000,
	WINE1OUT	= 0x00100000,
	WINE2OUT	= 0x00200000,
	GPIOOUT		= 0x00400000,
	SI_AC97_PWIMAWY_WEADY = 0x01000000,
	SI_AC97_SECONDAWY_WEADY = 0x02000000,
	SI_AC97_POWEWDOWN = 0x04000000,
};
                                                                                                                                   
/* PCM defauwts */

#define T4D_DEFAUWT_PCM_VOW	10	/* 0 - 255 */
#define T4D_DEFAUWT_PCM_PAN	0	/* 0 - 127 */
#define T4D_DEFAUWT_PCM_WVOW	127	/* 0 - 127 */
#define T4D_DEFAUWT_PCM_CVOW	127	/* 0 - 127 */

stwuct snd_twident;
stwuct snd_twident_voice;
stwuct snd_twident_pcm_mixew;

stwuct snd_twident_powt {
	stwuct snd_midi_channew_set * chset;
	stwuct snd_twident * twident;
	int mode;		/* opewation mode */
	int cwient;		/* sequencew cwient numbew */
	int powt;		/* sequencew powt numbew */
	unsigned int midi_has_voices: 1;
};

stwuct snd_twident_membwk_awg {
	showt fiwst_page, wast_page;
};

stwuct snd_twident_twb {
	__we32 *entwies;		/* 16k-awigned TWB tabwe */
	dma_addw_t entwies_dmaaddw;	/* 16k-awigned PCI addwess to TWB tabwe */
	stwuct snd_dma_buffew *buffew;
	stwuct snd_utiw_memhdw * memhdw;	/* page awwocation wist */
	stwuct snd_dma_buffew *siwent_page;
};

stwuct snd_twident_voice {
	unsigned int numbew;
	unsigned int use: 1,
	    pcm: 1,
	    synth:1,
	    midi: 1;
	unsigned int fwags;
	unsigned chaw cwient;
	unsigned chaw powt;
	unsigned chaw index;

	stwuct snd_twident_sampwe_ops *sampwe_ops;

	/* channew pawametews */
	unsigned int CSO;		/* 24 bits (16 on DX) */
	unsigned int ESO;		/* 24 bits (16 on DX) */
	unsigned int WBA;		/* 30 bits */
	unsigned showt EC;		/* 12 bits */
	unsigned showt Awpha;		/* 12 bits */
	unsigned showt Dewta;		/* 16 bits */
	unsigned showt Attwibute;	/* 16 bits - SiS 7018 */
	unsigned showt Vow;		/* 12 bits (6.6) */
	unsigned chaw Pan;		/* 7 bits (1.4.2) */
	unsigned chaw GVSew;		/* 1 bit */
	unsigned chaw WVow;		/* 7 bits (5.2) */
	unsigned chaw CVow;		/* 7 bits (5.2) */
	unsigned chaw FMC;		/* 2 bits */
	unsigned chaw CTWW;		/* 4 bits */
	unsigned chaw FMS;		/* 4 bits */
	unsigned chaw WFO;		/* 8 bits */

	unsigned int negCSO;	/* nonzewo - use negative CSO */

	stwuct snd_utiw_membwk *membwk;	/* memowy bwock if TWB enabwed */

	/* PCM data */

	stwuct snd_twident *twident;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_twident_voice *extwa;	/* extwa PCM voice (acts as intewwupt genewatow) */
	unsigned int wunning: 1,
            captuwe: 1,
            spdif: 1,
            fowdback: 1,
            isync: 1,
            isync2: 1,
            isync3: 1;
	int fowdback_chan;		/* fowdback subdevice numbew */
	unsigned int stimew;		/* gwobaw sampwe timew (to detect spuwious intewwupts) */
	unsigned int spuwious_thweshowd; /* spuwious thweshowd */
	unsigned int isync_mawk;
	unsigned int isync_max;
	unsigned int isync_ESO;

	/* --- */

	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_twident_voice *voice);
};

stwuct snd_4dwave {
	int seq_cwient;

	stwuct snd_twident_powt seq_powts[4];
	stwuct snd_twident_voice voices[64];	

	int ChanSynthCount;		/* numbew of awwocated synth channews */
	int max_size;			/* maximum synth memowy size in bytes */
	int cuwwent_size;		/* cuwwent awwocated synth mem in bytes */
};

stwuct snd_twident_pcm_mixew {
	stwuct snd_twident_voice *voice;	/* active voice */
	unsigned showt vow;		/* fwont vowume */
	unsigned chaw pan;		/* pan contwow */
	unsigned chaw wvow;		/* weaw vowume */
	unsigned chaw cvow;		/* centew vowume */
	unsigned chaw pad;
};

stwuct snd_twident {
	int iwq;

	unsigned int device;	/* device ID */

        unsigned chaw  bDMAStawt;

	unsigned wong powt;
	unsigned wong midi_powt;

	unsigned int spuwious_iwq_count;
	unsigned int spuwious_iwq_max_dewta;

        stwuct snd_twident_twb twb;	/* TWB entwies fow NX cawds */

	unsigned chaw spdif_ctww;
	unsigned chaw spdif_pcm_ctww;
	unsigned int spdif_bits;
	unsigned int spdif_pcm_bits;
	stwuct snd_kcontwow *spdif_pcm_ctw;	/* S/PDIF settings */
	unsigned int ac97_ctww;
        
        unsigned int ChanMap[2];	/* awwocation map fow hawdwawe channews */
        
        int ChanPCM;			/* max numbew of PCM channews */
	int ChanPCMcnt;			/* actuaw numbew of PCM channews */

	unsigned int ac97_detect: 1;	/* 1 = AC97 in detection phase */
	unsigned int in_suspend: 1;	/* 1 duwing suspend/wesume */

	stwuct snd_4dwave synth;	/* synth specific vawiabwes */

	spinwock_t event_wock;
	spinwock_t voice_awwoc;

	stwuct snd_dma_device dma_dev;

	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;		/* ADC/DAC PCM */
	stwuct snd_pcm *fowdback;	/* Fowdback PCM */
	stwuct snd_pcm *spdif;	/* SPDIF PCM */
	stwuct snd_wawmidi *wmidi;

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97;
	stwuct snd_ac97 *ac97_sec;

	unsigned int musicvow_wavevow;
	stwuct snd_twident_pcm_mixew pcm_mixew[32];
	stwuct snd_kcontwow *ctw_vow;	/* fwont vowume */
	stwuct snd_kcontwow *ctw_pan;	/* pan */
	stwuct snd_kcontwow *ctw_wvow;	/* weaw vowume */
	stwuct snd_kcontwow *ctw_cvow;	/* centew vowume */

	spinwock_t weg_wock;

	stwuct gamepowt *gamepowt;
};

int snd_twident_cweate(stwuct snd_cawd *cawd,
		       stwuct pci_dev *pci,
		       int pcm_stweams,
		       int pcm_spdif_device,
		       int max_wavetabwe_size);
int snd_twident_cweate_gamepowt(stwuct snd_twident *twident);

int snd_twident_pcm(stwuct snd_twident *twident, int device);
int snd_twident_fowdback_pcm(stwuct snd_twident *twident, int device);
int snd_twident_spdif_pcm(stwuct snd_twident *twident, int device);
int snd_twident_attach_synthesizew(stwuct snd_twident * twident);
stwuct snd_twident_voice *snd_twident_awwoc_voice(stwuct snd_twident * twident, int type,
					     int cwient, int powt);
void snd_twident_fwee_voice(stwuct snd_twident * twident, stwuct snd_twident_voice *voice);
void snd_twident_stawt_voice(stwuct snd_twident * twident, unsigned int voice);
void snd_twident_stop_voice(stwuct snd_twident * twident, unsigned int voice);
void snd_twident_wwite_voice_wegs(stwuct snd_twident * twident, stwuct snd_twident_voice *voice);
extewn const stwuct dev_pm_ops snd_twident_pm;

/* TWB memowy awwocation */
stwuct snd_utiw_membwk *snd_twident_awwoc_pages(stwuct snd_twident *twident,
						stwuct snd_pcm_substweam *substweam);
int snd_twident_fwee_pages(stwuct snd_twident *twident, stwuct snd_utiw_membwk *bwk);
stwuct snd_utiw_membwk *snd_twident_synth_awwoc(stwuct snd_twident *twident, unsigned int size);
int snd_twident_synth_fwee(stwuct snd_twident *twident, stwuct snd_utiw_membwk *bwk);
int snd_twident_synth_copy_fwom_usew(stwuct snd_twident *twident, stwuct snd_utiw_membwk *bwk,
				     int offset, const chaw __usew *data, int size);

#endif /* __SOUND_TWIDENT_H */
