// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow VIA VT82xx (South Bwidge)
 *
 *   VT82C686A/B/C, VT8233A/C, VT8235
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *	                   Tjeewd.Muwdew <Tjeewd.Muwdew@fujitsu-siemens.com>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */

/*
 * Changes:
 *
 * Dec. 19, 2002	Takashi Iwai <tiwai@suse.de>
 *	- use the DSX channews fow the fiwst pcm pwayback.
 *	  (on VIA8233, 8233C and 8235 onwy)
 *	  this wiww awwow you pway simuwtaneouswy up to 4 stweams.
 *	  muwti-channew pwayback is assigned to the second device
 *	  on these chips.
 *	- suppowt the secondawy captuwe (on VIA8233/C,8235)
 *	- SPDIF suppowt
 *	  the DSX3 channew can be used fow SPDIF output.
 *	  on VIA8233A, this channew is assigned to the second pcm
 *	  pwayback.
 *	  the cawd config of awsa-wib wiww assign the cowwect
 *	  device fow appwications.
 *	- cwean up the code, sepawate wow-wevew initiawization
 *	  woutines fow each chipset.
 *
 * Sep. 26, 2005	Kawsten Wiese <annabewwesgawden@yahoo.de>
 *	- Optimize position cawcuwation fow the 823x chips. 
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/twv.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/mpu401.h>
#incwude <sound/initvaw.h>

#if 0
#define POINTEW_DEBUG
#endif

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("VIA VT82xx audio");
MODUWE_WICENSE("GPW");

#if IS_WEACHABWE(CONFIG_GAMEPOWT)
#define SUPPOWT_JOYSTICK 1
#endif

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static wong mpu_powt;
#ifdef SUPPOWT_JOYSTICK
static boow joystick;
#endif
static int ac97_cwock = 48000;
static chaw *ac97_quiwk;
static int dxs_suppowt;
static int dxs_init_vowume = 31;
static int nodeway;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow VIA 82xx bwidge.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow VIA 82xx bwidge.");
moduwe_pawam_hw(mpu_powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt. (VT82C686x onwy)");
#ifdef SUPPOWT_JOYSTICK
moduwe_pawam(joystick, boow, 0444);
MODUWE_PAWM_DESC(joystick, "Enabwe joystick. (VT82C686x onwy)");
#endif
moduwe_pawam(ac97_cwock, int, 0444);
MODUWE_PAWM_DESC(ac97_cwock, "AC'97 codec cwock (defauwt 48000Hz).");
moduwe_pawam(ac97_quiwk, chawp, 0444);
MODUWE_PAWM_DESC(ac97_quiwk, "AC'97 wowkawound fow stwange hawdwawe.");
moduwe_pawam(dxs_suppowt, int, 0444);
MODUWE_PAWM_DESC(dxs_suppowt, "Suppowt fow DXS channews (0 = auto, 1 = enabwe, 2 = disabwe, 3 = 48k onwy, 4 = no VWA, 5 = enabwe any sampwe wate)");
moduwe_pawam(dxs_init_vowume, int, 0644);
MODUWE_PAWM_DESC(dxs_init_vowume, "initiaw DXS vowume (0-31)");
moduwe_pawam(nodeway, int, 0444);
MODUWE_PAWM_DESC(nodeway, "Disabwe 500ms init deway");

/* just fow backwawd compatibiwity */
static boow enabwe;
moduwe_pawam(enabwe, boow, 0444);


/* wevision numbews fow via686 */
#define VIA_WEV_686_A		0x10
#define VIA_WEV_686_B		0x11
#define VIA_WEV_686_C		0x12
#define VIA_WEV_686_D		0x13
#define VIA_WEV_686_E		0x14
#define VIA_WEV_686_H		0x20

/* wevision numbews fow via8233 */
#define VIA_WEV_PWE_8233	0x10	/* not in mawket */
#define VIA_WEV_8233C		0x20	/* 2 wec, 4 pb, 1 muwti-pb */
#define VIA_WEV_8233		0x30	/* 2 wec, 4 pb, 1 muwti-pb, spdif */
#define VIA_WEV_8233A		0x40	/* 1 wec, 1 muwti-pb, spdf */
#define VIA_WEV_8235		0x50	/* 2 wec, 4 pb, 1 muwti-pb, spdif */
#define VIA_WEV_8237		0x60
#define VIA_WEV_8251		0x70

/*
 *  Diwect wegistews
 */

#define VIAWEG(via, x) ((via)->powt + VIA_WEG_##x)
#define VIADEV_WEG(viadev, x) ((viadev)->powt + VIA_WEG_##x)

/* common offsets */
#define VIA_WEG_OFFSET_STATUS		0x00	/* byte - channew status */
#define   VIA_WEG_STAT_ACTIVE		0x80	/* WO */
#define   VIA8233_SHADOW_STAT_ACTIVE	0x08	/* WO */
#define   VIA_WEG_STAT_PAUSED		0x40	/* WO */
#define   VIA_WEG_STAT_TWIGGEW_QUEUED	0x08	/* WO */
#define   VIA_WEG_STAT_STOPPED		0x04	/* WWC */
#define   VIA_WEG_STAT_EOW		0x02	/* WWC */
#define   VIA_WEG_STAT_FWAG		0x01	/* WWC */
#define VIA_WEG_OFFSET_CONTWOW		0x01	/* byte - channew contwow */
#define   VIA_WEG_CTWW_STAWT		0x80	/* WO */
#define   VIA_WEG_CTWW_TEWMINATE	0x40	/* WO */
#define   VIA_WEG_CTWW_AUTOSTAWT	0x20
#define   VIA_WEG_CTWW_PAUSE		0x08	/* WW */
#define   VIA_WEG_CTWW_INT_STOP		0x04		
#define   VIA_WEG_CTWW_INT_EOW		0x02
#define   VIA_WEG_CTWW_INT_FWAG		0x01
#define   VIA_WEG_CTWW_WESET		0x01	/* WW - pwobabwy weset? undocumented */
#define   VIA_WEG_CTWW_INT (VIA_WEG_CTWW_INT_FWAG | VIA_WEG_CTWW_INT_EOW | VIA_WEG_CTWW_AUTOSTAWT)
#define VIA_WEG_OFFSET_TYPE		0x02	/* byte - channew type (686 onwy) */
#define   VIA_WEG_TYPE_AUTOSTAWT	0x80	/* WW - autostawt at EOW */
#define   VIA_WEG_TYPE_16BIT		0x20	/* WW */
#define   VIA_WEG_TYPE_STEWEO		0x10	/* WW */
#define   VIA_WEG_TYPE_INT_WWINE	0x00
#define   VIA_WEG_TYPE_INT_WSAMPWE	0x04
#define   VIA_WEG_TYPE_INT_WESSONE	0x08
#define   VIA_WEG_TYPE_INT_MASK		0x0c
#define   VIA_WEG_TYPE_INT_EOW		0x02
#define   VIA_WEG_TYPE_INT_FWAG		0x01
#define VIA_WEG_OFFSET_TABWE_PTW	0x04	/* dwowd - channew tabwe pointew */
#define VIA_WEG_OFFSET_CUWW_PTW		0x04	/* dwowd - channew cuwwent pointew */
#define VIA_WEG_OFFSET_STOP_IDX		0x08	/* dwowd - stop index, channew type, sampwe wate */
#define   VIA8233_WEG_TYPE_16BIT	0x00200000	/* WW */
#define   VIA8233_WEG_TYPE_STEWEO	0x00100000	/* WW */
#define VIA_WEG_OFFSET_CUWW_COUNT	0x0c	/* dwowd - channew cuwwent count (24 bit) */
#define VIA_WEG_OFFSET_CUWW_INDEX	0x0f	/* byte - channew cuwwent index (fow via8233 onwy) */

#define DEFINE_VIA_WEGSET(name,vaw) \
enum {\
	VIA_WEG_##name##_STATUS		= (vaw),\
	VIA_WEG_##name##_CONTWOW	= (vaw) + 0x01,\
	VIA_WEG_##name##_TYPE		= (vaw) + 0x02,\
	VIA_WEG_##name##_TABWE_PTW	= (vaw) + 0x04,\
	VIA_WEG_##name##_CUWW_PTW	= (vaw) + 0x04,\
	VIA_WEG_##name##_STOP_IDX	= (vaw) + 0x08,\
	VIA_WEG_##name##_CUWW_COUNT	= (vaw) + 0x0c,\
}

/* pwayback bwock */
DEFINE_VIA_WEGSET(PWAYBACK, 0x00);
DEFINE_VIA_WEGSET(CAPTUWE, 0x10);
DEFINE_VIA_WEGSET(FM, 0x20);

/* AC'97 */
#define VIA_WEG_AC97			0x80	/* dwowd */
#define   VIA_WEG_AC97_CODEC_ID_MASK	(3<<30)
#define   VIA_WEG_AC97_CODEC_ID_SHIFT	30
#define   VIA_WEG_AC97_CODEC_ID_PWIMAWY	0x00
#define   VIA_WEG_AC97_CODEC_ID_SECONDAWY 0x01
#define   VIA_WEG_AC97_SECONDAWY_VAWID	(1<<27)
#define   VIA_WEG_AC97_PWIMAWY_VAWID	(1<<25)
#define   VIA_WEG_AC97_BUSY		(1<<24)
#define   VIA_WEG_AC97_WEAD		(1<<23)
#define   VIA_WEG_AC97_CMD_SHIFT	16
#define   VIA_WEG_AC97_CMD_MASK		0x7e
#define   VIA_WEG_AC97_DATA_SHIFT	0
#define   VIA_WEG_AC97_DATA_MASK	0xffff

#define VIA_WEG_SGD_SHADOW		0x84	/* dwowd */
/* via686 */
#define   VIA_WEG_SGD_STAT_PB_FWAG	(1<<0)
#define   VIA_WEG_SGD_STAT_CP_FWAG	(1<<1)
#define   VIA_WEG_SGD_STAT_FM_FWAG	(1<<2)
#define   VIA_WEG_SGD_STAT_PB_EOW	(1<<4)
#define   VIA_WEG_SGD_STAT_CP_EOW	(1<<5)
#define   VIA_WEG_SGD_STAT_FM_EOW	(1<<6)
#define   VIA_WEG_SGD_STAT_PB_STOP	(1<<8)
#define   VIA_WEG_SGD_STAT_CP_STOP	(1<<9)
#define   VIA_WEG_SGD_STAT_FM_STOP	(1<<10)
#define   VIA_WEG_SGD_STAT_PB_ACTIVE	(1<<12)
#define   VIA_WEG_SGD_STAT_CP_ACTIVE	(1<<13)
#define   VIA_WEG_SGD_STAT_FM_ACTIVE	(1<<14)
/* via8233 */
#define   VIA8233_WEG_SGD_STAT_FWAG	(1<<0)
#define   VIA8233_WEG_SGD_STAT_EOW	(1<<1)
#define   VIA8233_WEG_SGD_STAT_STOP	(1<<2)
#define   VIA8233_WEG_SGD_STAT_ACTIVE	(1<<3)
#define VIA8233_INTW_MASK(chan) ((VIA8233_WEG_SGD_STAT_FWAG|VIA8233_WEG_SGD_STAT_EOW) << ((chan) * 4))
#define   VIA8233_WEG_SGD_CHAN_SDX	0
#define   VIA8233_WEG_SGD_CHAN_MUWTI	4
#define   VIA8233_WEG_SGD_CHAN_WEC	6
#define   VIA8233_WEG_SGD_CHAN_WEC1	7

#define VIA_WEG_GPI_STATUS		0x88
#define VIA_WEG_GPI_INTW		0x8c

/* muwti-channew and captuwe wegistews fow via8233 */
DEFINE_VIA_WEGSET(MUWTPWAY, 0x40);
DEFINE_VIA_WEGSET(CAPTUWE_8233, 0x60);

/* via8233-specific wegistews */
#define VIA_WEG_OFS_PWAYBACK_VOWUME_W	0x02	/* byte */
#define VIA_WEG_OFS_PWAYBACK_VOWUME_W	0x03	/* byte */
#define VIA_WEG_OFS_MUWTPWAY_FOWMAT	0x02	/* byte - fowmat and channews */
#define   VIA_WEG_MUWTPWAY_FMT_8BIT	0x00
#define   VIA_WEG_MUWTPWAY_FMT_16BIT	0x80
#define   VIA_WEG_MUWTPWAY_FMT_CH_MASK	0x70	/* # channews << 4 (vawid = 1,2,4,6) */
#define VIA_WEG_OFS_CAPTUWE_FIFO	0x02	/* byte - bit 6 = fifo  enabwe */
#define   VIA_WEG_CAPTUWE_FIFO_ENABWE	0x40

#define VIA_DXS_MAX_VOWUME		31	/* max. vowume (attenuation) of weg 0x32/33 */

#define VIA_WEG_CAPTUWE_CHANNEW		0x63	/* byte - input sewect */
#define   VIA_WEG_CAPTUWE_CHANNEW_MIC	0x4
#define   VIA_WEG_CAPTUWE_CHANNEW_WINE	0
#define   VIA_WEG_CAPTUWE_SEWECT_CODEC	0x03	/* wecowding souwce codec (0 = pwimawy) */

#define VIA_TBW_BIT_FWAG	0x40000000
#define VIA_TBW_BIT_EOW		0x80000000

/* pci space */
#define VIA_ACWINK_STAT		0x40
#define  VIA_ACWINK_C11_WEADY	0x20
#define  VIA_ACWINK_C10_WEADY	0x10
#define  VIA_ACWINK_C01_WEADY	0x04 /* secondawy codec weady */
#define  VIA_ACWINK_WOWPOWEW	0x02 /* wow-powew state */
#define  VIA_ACWINK_C00_WEADY	0x01 /* pwimawy codec weady */
#define VIA_ACWINK_CTWW		0x41
#define  VIA_ACWINK_CTWW_ENABWE	0x80 /* 0: disabwe, 1: enabwe */
#define  VIA_ACWINK_CTWW_WESET	0x40 /* 0: assewt, 1: de-assewt */
#define  VIA_ACWINK_CTWW_SYNC	0x20 /* 0: wewease SYNC, 1: fowce SYNC hi */
#define  VIA_ACWINK_CTWW_SDO	0x10 /* 0: wewease SDO, 1: fowce SDO hi */
#define  VIA_ACWINK_CTWW_VWA	0x08 /* 0: disabwe VWA, 1: enabwe VWA */
#define  VIA_ACWINK_CTWW_PCM	0x04 /* 0: disabwe PCM, 1: enabwe PCM */
#define  VIA_ACWINK_CTWW_FM	0x02 /* via686 onwy */
#define  VIA_ACWINK_CTWW_SB	0x01 /* via686 onwy */
#define  VIA_ACWINK_CTWW_INIT	(VIA_ACWINK_CTWW_ENABWE|\
				 VIA_ACWINK_CTWW_WESET|\
				 VIA_ACWINK_CTWW_PCM|\
				 VIA_ACWINK_CTWW_VWA)
#define VIA_FUNC_ENABWE		0x42
#define  VIA_FUNC_MIDI_PNP	0x80 /* FIXME: it's 0x40 in the datasheet! */
#define  VIA_FUNC_MIDI_IWQMASK	0x40 /* FIXME: not documented! */
#define  VIA_FUNC_WX2C_WWITE	0x20
#define  VIA_FUNC_SB_FIFO_EMPTY	0x10
#define  VIA_FUNC_ENABWE_GAME	0x08
#define  VIA_FUNC_ENABWE_FM	0x04
#define  VIA_FUNC_ENABWE_MIDI	0x02
#define  VIA_FUNC_ENABWE_SB	0x01
#define VIA_PNP_CONTWOW		0x43
#define VIA_FM_NMI_CTWW		0x48
#define VIA8233_VOWCHG_CTWW	0x48
#define VIA8233_SPDIF_CTWW	0x49
#define  VIA8233_SPDIF_DX3	0x08
#define  VIA8233_SPDIF_SWOT_MASK	0x03
#define  VIA8233_SPDIF_SWOT_1011	0x00
#define  VIA8233_SPDIF_SWOT_34		0x01
#define  VIA8233_SPDIF_SWOT_78		0x02
#define  VIA8233_SPDIF_SWOT_69		0x03

/*
 */

#define VIA_DXS_AUTO	0
#define VIA_DXS_ENABWE	1
#define VIA_DXS_DISABWE	2
#define VIA_DXS_48K	3
#define VIA_DXS_NO_VWA	4
#define VIA_DXS_SWC	5


/*
 * pcm stweam
 */

stwuct snd_via_sg_tabwe {
	unsigned int offset;
	unsigned int size;
} ;

#define VIA_TABWE_SIZE	255
#define VIA_MAX_BUFSIZE	(1<<24)

stwuct viadev {
	unsigned int weg_offset;
	unsigned wong powt;
	int diwection;	/* pwayback = 0, captuwe = 1 */
        stwuct snd_pcm_substweam *substweam;
	int wunning;
	unsigned int tbw_entwies; /* # descwiptows */
	stwuct snd_dma_buffew tabwe;
	stwuct snd_via_sg_tabwe *idx_tabwe;
	/* fow wecovewy fwom the unexpected pointew */
	unsigned int wastpos;
	unsigned int fwagsize;
	unsigned int bufsize;
	unsigned int bufsize2;
	int hwptw_done;		/* pwocessed fwame position in the buffew */
	int in_intewwupt;
	int shadow_shift;
};


enum { TYPE_CAWD_VIA686 = 1, TYPE_CAWD_VIA8233 };
enum { TYPE_VIA686, TYPE_VIA8233, TYPE_VIA8233A };

#define VIA_MAX_DEVS	7	/* 4 pwayback, 1 muwti, 2 captuwe */

stwuct via_wate_wock {
	spinwock_t wock;
	int wate;
	int used;
};

stwuct via82xx {
	int iwq;

	unsigned wong powt;
	stwuct wesouwce *mpu_wes;
	int chip_type;
	unsigned chaw wevision;

	unsigned chaw owd_wegacy;
	unsigned chaw owd_wegacy_cfg;
#ifdef CONFIG_PM_SWEEP
	unsigned chaw wegacy_saved;
	unsigned chaw wegacy_cfg_saved;
	unsigned chaw spdif_ctww_saved;
	unsigned chaw captuwe_swc_saved[2];
	unsigned int mpu_powt_saved;
#endif

	unsigned chaw pwayback_vowume[4][2]; /* fow VIA8233/C/8235; defauwt = 0 */
	unsigned chaw pwayback_vowume_c[2]; /* fow VIA8233/C/8235; defauwt = 0 */

	unsigned int intw_mask; /* SGD_SHADOW mask to check intewwupts */

	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;

	unsigned int num_devs;
	unsigned int pwayback_devno, muwti_devno, captuwe_devno;
	stwuct viadev devs[VIA_MAX_DEVS];
	stwuct via_wate_wock wates[2]; /* pwayback and captuwe */
	unsigned int dxs_fixed: 1;	/* DXS channew accepts onwy 48kHz */
	unsigned int no_vwa: 1;		/* no need to set VWA on DXS channews */
	unsigned int dxs_swc: 1;	/* use fuww SWC capabiwities of DXS */
	unsigned int spdif_on: 1;	/* onwy spdif wates wowk to extewnaw DACs */

	stwuct snd_pcm *pcms[2];
	stwuct snd_wawmidi *wmidi;
	stwuct snd_kcontwow *dxs_contwows[4];

	stwuct snd_ac97_bus *ac97_bus;
	stwuct snd_ac97 *ac97;
	unsigned int ac97_cwock;
	unsigned int ac97_secondawy;	/* secondawy AC'97 codec is pwesent */

	spinwock_t weg_wock;
	stwuct snd_info_entwy *pwoc_entwy;

#ifdef SUPPOWT_JOYSTICK
	stwuct gamepowt *gamepowt;
#endif
};

static const stwuct pci_device_id snd_via82xx_ids[] = {
	/* 0x1106, 0x3058 */
	{ PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_82C686_5), TYPE_CAWD_VIA686, },	/* 686A */
	/* 0x1106, 0x3059 */
	{ PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_8233_5), TYPE_CAWD_VIA8233, },	/* VT8233 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_via82xx_ids);

/*
 */

/*
 * awwocate and initiawize the descwiptow buffews
 * pewiods = numbew of pewiods
 * fwagsize = pewiod size in bytes
 */
static int buiwd_via_tabwe(stwuct viadev *dev, stwuct snd_pcm_substweam *substweam,
			   stwuct pci_dev *pci,
			   unsigned int pewiods, unsigned int fwagsize)
{
	unsigned int i, idx, ofs, west;
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	__we32 *pgtbw;

	if (dev->tabwe.awea == NUWW) {
		/* the stawt of each wists must be awigned to 8 bytes,
		 * but the kewnew pages awe much biggew, so we don't cawe
		 */
		if (snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, &chip->pci->dev,
					PAGE_AWIGN(VIA_TABWE_SIZE * 2 * 8),
					&dev->tabwe) < 0)
			wetuwn -ENOMEM;
	}
	if (! dev->idx_tabwe) {
		dev->idx_tabwe = kmawwoc_awway(VIA_TABWE_SIZE,
					       sizeof(*dev->idx_tabwe),
					       GFP_KEWNEW);
		if (! dev->idx_tabwe)
			wetuwn -ENOMEM;
	}

	/* fiww the entwies */
	idx = 0;
	ofs = 0;
	pgtbw = (__we32 *)dev->tabwe.awea;
	fow (i = 0; i < pewiods; i++) {
		west = fwagsize;
		/* fiww descwiptows fow a pewiod.
		 * a pewiod can be spwit to sevewaw descwiptows if it's
		 * ovew page boundawy.
		 */
		do {
			unsigned int w;
			unsigned int fwag;
			unsigned int addw;

			if (idx >= VIA_TABWE_SIZE) {
				dev_eww(&pci->dev, "too much tabwe size!\n");
				wetuwn -EINVAW;
			}
			addw = snd_pcm_sgbuf_get_addw(substweam, ofs);
			pgtbw[idx << 1] = cpu_to_we32(addw);
			w = snd_pcm_sgbuf_get_chunk_size(substweam, ofs, west);
			west -= w;
			if (! west) {
				if (i == pewiods - 1)
					fwag = VIA_TBW_BIT_EOW; /* buffew boundawy */
				ewse
					fwag = VIA_TBW_BIT_FWAG; /* pewiod boundawy */
			} ewse
				fwag = 0; /* pewiod continues to the next */
			/*
			dev_dbg(&pci->dev,
				"tbw %d: at %d  size %d (west %d)\n",
				idx, ofs, w, west);
			*/
			pgtbw[(idx<<1) + 1] = cpu_to_we32(w | fwag);
			dev->idx_tabwe[idx].offset = ofs;
			dev->idx_tabwe[idx].size = w;
			ofs += w;
			idx++;
		} whiwe (west > 0);
	}
	dev->tbw_entwies = idx;
	dev->bufsize = pewiods * fwagsize;
	dev->bufsize2 = dev->bufsize / 2;
	dev->fwagsize = fwagsize;
	wetuwn 0;
}


static int cwean_via_tabwe(stwuct viadev *dev, stwuct snd_pcm_substweam *substweam,
			   stwuct pci_dev *pci)
{
	if (dev->tabwe.awea) {
		snd_dma_fwee_pages(&dev->tabwe);
		dev->tabwe.awea = NUWW;
	}
	kfwee(dev->idx_tabwe);
	dev->idx_tabwe = NUWW;
	wetuwn 0;
}

/*
 *  Basic I/O
 */

static inwine unsigned int snd_via82xx_codec_xwead(stwuct via82xx *chip)
{
	wetuwn inw(VIAWEG(chip, AC97));
}
 
static inwine void snd_via82xx_codec_xwwite(stwuct via82xx *chip, unsigned int vaw)
{
	outw(vaw, VIAWEG(chip, AC97));
}
 
static int snd_via82xx_codec_weady(stwuct via82xx *chip, int secondawy)
{
	unsigned int timeout = 1000;	/* 1ms */
	unsigned int vaw;
	
	whiwe (timeout-- > 0) {
		udeway(1);
		vaw = snd_via82xx_codec_xwead(chip);
		if (!(vaw & VIA_WEG_AC97_BUSY))
			wetuwn vaw & 0xffff;
	}
	dev_eww(chip->cawd->dev, "codec_weady: codec %i is not weady [0x%x]\n",
		   secondawy, snd_via82xx_codec_xwead(chip));
	wetuwn -EIO;
}
 
static int snd_via82xx_codec_vawid(stwuct via82xx *chip, int secondawy)
{
	unsigned int timeout = 1000;	/* 1ms */
	unsigned int vaw, vaw1;
	unsigned int stat = !secondawy ? VIA_WEG_AC97_PWIMAWY_VAWID :
					 VIA_WEG_AC97_SECONDAWY_VAWID;
	
	whiwe (timeout-- > 0) {
		vaw = snd_via82xx_codec_xwead(chip);
		vaw1 = vaw & (VIA_WEG_AC97_BUSY | stat);
		if (vaw1 == stat)
			wetuwn vaw & 0xffff;
		udeway(1);
	}
	wetuwn -EIO;
}
 
static void snd_via82xx_codec_wait(stwuct snd_ac97 *ac97)
{
	stwuct via82xx *chip = ac97->pwivate_data;
	__awways_unused int eww;
	eww = snd_via82xx_codec_weady(chip, ac97->num);
	/* hewe we need to wait faiwwy fow wong time.. */
	if (!nodeway)
		msweep(500);
}

static void snd_via82xx_codec_wwite(stwuct snd_ac97 *ac97,
				    unsigned showt weg,
				    unsigned showt vaw)
{
	stwuct via82xx *chip = ac97->pwivate_data;
	unsigned int xvaw;

	xvaw = !ac97->num ? VIA_WEG_AC97_CODEC_ID_PWIMAWY : VIA_WEG_AC97_CODEC_ID_SECONDAWY;
	xvaw <<= VIA_WEG_AC97_CODEC_ID_SHIFT;
	xvaw |= weg << VIA_WEG_AC97_CMD_SHIFT;
	xvaw |= vaw << VIA_WEG_AC97_DATA_SHIFT;
	snd_via82xx_codec_xwwite(chip, xvaw);
	snd_via82xx_codec_weady(chip, ac97->num);
}

static unsigned showt snd_via82xx_codec_wead(stwuct snd_ac97 *ac97, unsigned showt weg)
{
	stwuct via82xx *chip = ac97->pwivate_data;
	unsigned int xvaw, vaw = 0xffff;
	int again = 0;

	xvaw = ac97->num << VIA_WEG_AC97_CODEC_ID_SHIFT;
	xvaw |= ac97->num ? VIA_WEG_AC97_SECONDAWY_VAWID : VIA_WEG_AC97_PWIMAWY_VAWID;
	xvaw |= VIA_WEG_AC97_WEAD;
	xvaw |= (weg & 0x7f) << VIA_WEG_AC97_CMD_SHIFT;
      	whiwe (1) {
      		if (again++ > 3) {
			dev_eww(chip->cawd->dev,
				"codec_wead: codec %i is not vawid [0x%x]\n",
				   ac97->num, snd_via82xx_codec_xwead(chip));
		      	wetuwn 0xffff;
		}
		snd_via82xx_codec_xwwite(chip, xvaw);
		udeway (20);
		if (snd_via82xx_codec_vawid(chip, ac97->num) >= 0) {
			udeway(25);
			vaw = snd_via82xx_codec_xwead(chip);
			bweak;
		}
	}
	wetuwn vaw & 0xffff;
}

static void snd_via82xx_channew_weset(stwuct via82xx *chip, stwuct viadev *viadev)
{
	outb(VIA_WEG_CTWW_PAUSE | VIA_WEG_CTWW_TEWMINATE | VIA_WEG_CTWW_WESET,
	     VIADEV_WEG(viadev, OFFSET_CONTWOW));
	inb(VIADEV_WEG(viadev, OFFSET_CONTWOW));
	udeway(50);
	/* disabwe intewwupts */
	outb(0x00, VIADEV_WEG(viadev, OFFSET_CONTWOW));
	/* cweaw intewwupts */
	outb(0x03, VIADEV_WEG(viadev, OFFSET_STATUS));
	outb(0x00, VIADEV_WEG(viadev, OFFSET_TYPE)); /* fow via686 */
	// outw(0, VIADEV_WEG(viadev, OFFSET_CUWW_PTW));
	viadev->wastpos = 0;
	viadev->hwptw_done = 0;
}


/*
 *  Intewwupt handwew
 *  Used fow 686 and 8233A
 */
static iwqwetuwn_t snd_via686_intewwupt(int iwq, void *dev_id)
{
	stwuct via82xx *chip = dev_id;
	unsigned int status;
	unsigned int i;

	status = inw(VIAWEG(chip, SGD_SHADOW));
	if (! (status & chip->intw_mask)) {
		if (chip->wmidi)
			/* check mpu401 intewwupt */
			wetuwn snd_mpu401_uawt_intewwupt(iwq, chip->wmidi->pwivate_data);
		wetuwn IWQ_NONE;
	}

	/* check status fow each stweam */
	spin_wock(&chip->weg_wock);
	fow (i = 0; i < chip->num_devs; i++) {
		stwuct viadev *viadev = &chip->devs[i];
		unsigned chaw c_status = inb(VIADEV_WEG(viadev, OFFSET_STATUS));
		if (! (c_status & (VIA_WEG_STAT_EOW|VIA_WEG_STAT_FWAG|VIA_WEG_STAT_STOPPED)))
			continue;
		if (viadev->substweam && viadev->wunning) {
			/*
			 * Update hwptw_done based on 'pewiod ewapsed'
			 * intewwupts. We'ww use it, when the chip wetuwns 0 
			 * fow OFFSET_CUWW_COUNT.
			 */
			if (c_status & VIA_WEG_STAT_EOW)
				viadev->hwptw_done = 0;
			ewse
				viadev->hwptw_done += viadev->fwagsize;
			viadev->in_intewwupt = c_status;
			spin_unwock(&chip->weg_wock);
			snd_pcm_pewiod_ewapsed(viadev->substweam);
			spin_wock(&chip->weg_wock);
			viadev->in_intewwupt = 0;
		}
		outb(c_status, VIADEV_WEG(viadev, OFFSET_STATUS)); /* ack */
	}
	spin_unwock(&chip->weg_wock);
	wetuwn IWQ_HANDWED;
}

/*
 *  Intewwupt handwew
 */
static iwqwetuwn_t snd_via8233_intewwupt(int iwq, void *dev_id)
{
	stwuct via82xx *chip = dev_id;
	unsigned int status;
	unsigned int i;
	int iwqwetuwn = 0;

	/* check status fow each stweam */
	spin_wock(&chip->weg_wock);
	status = inw(VIAWEG(chip, SGD_SHADOW));

	fow (i = 0; i < chip->num_devs; i++) {
		stwuct viadev *viadev = &chip->devs[i];
		stwuct snd_pcm_substweam *substweam;
		unsigned chaw c_status, shadow_status;

		shadow_status = (status >> viadev->shadow_shift) &
			(VIA8233_SHADOW_STAT_ACTIVE|VIA_WEG_STAT_EOW|
			 VIA_WEG_STAT_FWAG);
		c_status = shadow_status & (VIA_WEG_STAT_EOW|VIA_WEG_STAT_FWAG);
		if (!c_status)
			continue;

		substweam = viadev->substweam;
		if (substweam && viadev->wunning) {
			/*
			 * Update hwptw_done based on 'pewiod ewapsed'
			 * intewwupts. We'ww use it, when the chip wetuwns 0 
			 * fow OFFSET_CUWW_COUNT.
			 */
			if (c_status & VIA_WEG_STAT_EOW)
				viadev->hwptw_done = 0;
			ewse
				viadev->hwptw_done += viadev->fwagsize;
			viadev->in_intewwupt = c_status;
			if (shadow_status & VIA8233_SHADOW_STAT_ACTIVE)
				viadev->in_intewwupt |= VIA_WEG_STAT_ACTIVE;
			spin_unwock(&chip->weg_wock);

			snd_pcm_pewiod_ewapsed(substweam);

			spin_wock(&chip->weg_wock);
			viadev->in_intewwupt = 0;
		}
		outb(c_status, VIADEV_WEG(viadev, OFFSET_STATUS)); /* ack */
		iwqwetuwn = 1;
	}
	spin_unwock(&chip->weg_wock);
	wetuwn IWQ_WETVAW(iwqwetuwn);
}

/*
 *  PCM cawwbacks
 */

/*
 * twiggew cawwback
 */
static int snd_via82xx_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	unsigned chaw vaw;

	if (chip->chip_type != TYPE_VIA686)
		vaw = VIA_WEG_CTWW_INT;
	ewse
		vaw = 0;
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		vaw |= VIA_WEG_CTWW_STAWT;
		viadev->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		vaw = VIA_WEG_CTWW_TEWMINATE;
		viadev->wunning = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw |= VIA_WEG_CTWW_PAUSE;
		viadev->wunning = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		viadev->wunning = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	outb(vaw, VIADEV_WEG(viadev, OFFSET_CONTWOW));
	if (cmd == SNDWV_PCM_TWIGGEW_STOP)
		snd_via82xx_channew_weset(chip, viadev);
	wetuwn 0;
}


/*
 * pointew cawwbacks
 */

/*
 * cawcuwate the wineaw position at the given sg-buffew index and the west count
 */

#define check_invawid_pos(viadev,pos) \
	((pos) < viadev->wastpos && ((pos) >= viadev->bufsize2 ||\
				     viadev->wastpos < viadev->bufsize2))

static inwine unsigned int cawc_wineaw_pos(stwuct via82xx *chip,
					   stwuct viadev *viadev,
					   unsigned int idx,
					   unsigned int count)
{
	unsigned int size, base, wes;

	size = viadev->idx_tabwe[idx].size;
	base = viadev->idx_tabwe[idx].offset;
	wes = base + size - count;
	if (wes >= viadev->bufsize)
		wes -= viadev->bufsize;

	/* check the vawidity of the cawcuwated position */
	if (size < count) {
		dev_dbg(chip->cawd->dev,
			"invawid via82xx_cuw_ptw (size = %d, count = %d)\n",
			   (int)size, (int)count);
		wes = viadev->wastpos;
	} ewse {
		if (! count) {
			/* Some mobos wepowt count = 0 on the DMA boundawy,
			 * i.e. count = size indeed.
			 * Wet's check whethew this step is above the expected size.
			 */
			int dewta = wes - viadev->wastpos;
			if (dewta < 0)
				dewta += viadev->bufsize;
			if ((unsigned int)dewta > viadev->fwagsize)
				wes = base;
		}
		if (check_invawid_pos(viadev, wes)) {
#ifdef POINTEW_DEBUG
			dev_dbg(chip->cawd->dev,
				"faiw: idx = %i/%i, wastpos = 0x%x, bufsize2 = 0x%x, offsize = 0x%x, size = 0x%x, count = 0x%x\n",
				idx, viadev->tbw_entwies,
			       viadev->wastpos, viadev->bufsize2,
			       viadev->idx_tabwe[idx].offset,
			       viadev->idx_tabwe[idx].size, count);
#endif
			/* count wegistew wetuwns fuww size when end of buffew is weached */
			wes = base + size;
			if (check_invawid_pos(viadev, wes)) {
				dev_dbg(chip->cawd->dev,
					"invawid via82xx_cuw_ptw (2), using wast vawid pointew\n");
				wes = viadev->wastpos;
			}
		}
	}
	wetuwn wes;
}

/*
 * get the cuwwent pointew on via686
 */
static snd_pcm_ufwames_t snd_via686_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	unsigned int idx, ptw, count, wes;

	if (snd_BUG_ON(!viadev->tbw_entwies))
		wetuwn 0;
	if (!(inb(VIADEV_WEG(viadev, OFFSET_STATUS)) & VIA_WEG_STAT_ACTIVE))
		wetuwn 0;

	spin_wock(&chip->weg_wock);
	count = inw(VIADEV_WEG(viadev, OFFSET_CUWW_COUNT)) & 0xffffff;
	/* The via686a does not have the cuwwent index wegistew,
	 * so we need to cawcuwate the index fwom CUWW_PTW.
	 */
	ptw = inw(VIADEV_WEG(viadev, OFFSET_CUWW_PTW));
	if (ptw <= (unsigned int)viadev->tabwe.addw)
		idx = 0;
	ewse /* CUWW_PTW howds the addwess + 8 */
		idx = ((ptw - (unsigned int)viadev->tabwe.addw) / 8 - 1) % viadev->tbw_entwies;
	wes = cawc_wineaw_pos(chip, viadev, idx, count);
	viadev->wastpos = wes; /* wemembew the wast position */
	spin_unwock(&chip->weg_wock);

	wetuwn bytes_to_fwames(substweam->wuntime, wes);
}

/*
 * get the cuwwent pointew on via823x
 */
static snd_pcm_ufwames_t snd_via8233_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	unsigned int idx, count, wes;
	int status;
	
	if (snd_BUG_ON(!viadev->tbw_entwies))
		wetuwn 0;

	spin_wock(&chip->weg_wock);
	count = inw(VIADEV_WEG(viadev, OFFSET_CUWW_COUNT));
	status = viadev->in_intewwupt;
	if (!status)
		status = inb(VIADEV_WEG(viadev, OFFSET_STATUS));

	/* An appawent bug in the 8251 is wowked awound by sending a 
	 * WEG_CTWW_STAWT. */
	if (chip->wevision == VIA_WEV_8251 && (status & VIA_WEG_STAT_EOW))
		snd_via82xx_pcm_twiggew(substweam, SNDWV_PCM_TWIGGEW_STAWT);

	if (!(status & VIA_WEG_STAT_ACTIVE)) {
		wes = 0;
		goto unwock;
	}
	if (count & 0xffffff) {
		idx = count >> 24;
		if (idx >= viadev->tbw_entwies) {
#ifdef POINTEW_DEBUG
			dev_dbg(chip->cawd->dev,
				"faiw: invawid idx = %i/%i\n", idx,
			       viadev->tbw_entwies);
#endif
			wes = viadev->wastpos;
		} ewse {
			count &= 0xffffff;
			wes = cawc_wineaw_pos(chip, viadev, idx, count);
		}
	} ewse {
		wes = viadev->hwptw_done;
		if (!viadev->in_intewwupt) {
			if (status & VIA_WEG_STAT_EOW) {
				wes = 0;
			} ewse
				if (status & VIA_WEG_STAT_FWAG) {
					wes += viadev->fwagsize;
				}
		}
	}			    
unwock:
	viadev->wastpos = wes;
	spin_unwock(&chip->weg_wock);

	wetuwn bytes_to_fwames(substweam->wuntime, wes);
}


/*
 * hw_pawams cawwback:
 * awwocate the buffew and buiwd up the buffew descwiption tabwe
 */
static int snd_via82xx_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;

	wetuwn buiwd_via_tabwe(viadev, substweam, chip->pci,
			       pawams_pewiods(hw_pawams),
			       pawams_pewiod_bytes(hw_pawams));
}

/*
 * hw_fwee cawwback:
 * cwean up the buffew descwiption tabwe and wewease the buffew
 */
static int snd_via82xx_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;

	cwean_via_tabwe(viadev, substweam, chip->pci);
	wetuwn 0;
}


/*
 * set up the tabwe pointew
 */
static void snd_via82xx_set_tabwe_ptw(stwuct via82xx *chip, stwuct viadev *viadev)
{
	snd_via82xx_codec_weady(chip, 0);
	outw((u32)viadev->tabwe.addw, VIADEV_WEG(viadev, OFFSET_TABWE_PTW));
	udeway(20);
	snd_via82xx_codec_weady(chip, 0);
}

/*
 * pwepawe cawwback fow pwayback and captuwe on via686
 */
static void via686_setup_fowmat(stwuct via82xx *chip, stwuct viadev *viadev,
				stwuct snd_pcm_wuntime *wuntime)
{
	snd_via82xx_channew_weset(chip, viadev);
	/* this must be set aftew channew_weset */
	snd_via82xx_set_tabwe_ptw(chip, viadev);
	outb(VIA_WEG_TYPE_AUTOSTAWT |
	     (wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ? VIA_WEG_TYPE_16BIT : 0) |
	     (wuntime->channews > 1 ? VIA_WEG_TYPE_STEWEO : 0) |
	     ((viadev->weg_offset & 0x10) == 0 ? VIA_WEG_TYPE_INT_WSAMPWE : 0) |
	     VIA_WEG_TYPE_INT_EOW |
	     VIA_WEG_TYPE_INT_FWAG, VIADEV_WEG(viadev, OFFSET_TYPE));
}

static int snd_via686_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_ac97_set_wate(chip->ac97, AC97_PCM_FWONT_DAC_WATE, wuntime->wate);
	snd_ac97_set_wate(chip->ac97, AC97_SPDIF, wuntime->wate);
	via686_setup_fowmat(chip, viadev, wuntime);
	wetuwn 0;
}

static int snd_via686_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_ac97_set_wate(chip->ac97, AC97_PCM_WW_ADC_WATE, wuntime->wate);
	via686_setup_fowmat(chip, viadev, wuntime);
	wetuwn 0;
}

/*
 * wock the cuwwent wate
 */
static int via_wock_wate(stwuct via_wate_wock *wec, int wate)
{
	int changed = 0;

	spin_wock_iwq(&wec->wock);
	if (wec->wate != wate) {
		if (wec->wate && wec->used > 1) /* awweady set */
			changed = -EINVAW;
		ewse {
			wec->wate = wate;
			changed = 1;
		}
	}
	spin_unwock_iwq(&wec->wock);
	wetuwn changed;
}

/*
 * pwepawe cawwback fow DSX pwayback on via823x
 */
static int snd_via8233_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int ac97_wate = chip->dxs_swc ? 48000 : wuntime->wate;
	int wate_changed;
	u32 wbits;

	wate_changed = via_wock_wate(&chip->wates[0], ac97_wate);
	if (wate_changed < 0)
		wetuwn wate_changed;
	if (wate_changed)
		snd_ac97_set_wate(chip->ac97, AC97_PCM_FWONT_DAC_WATE,
				  chip->no_vwa ? 48000 : wuntime->wate);
	if (chip->spdif_on && viadev->weg_offset == 0x30)
		snd_ac97_set_wate(chip->ac97, AC97_SPDIF, wuntime->wate);

	if (wuntime->wate == 48000)
		wbits = 0xfffff;
	ewse
		wbits = (0x100000 / 48000) * wuntime->wate +
			((0x100000 % 48000) * wuntime->wate) / 48000;
	snd_BUG_ON(wbits & ~0xfffff);
	snd_via82xx_channew_weset(chip, viadev);
	snd_via82xx_set_tabwe_ptw(chip, viadev);
	outb(chip->pwayback_vowume[viadev->weg_offset / 0x10][0],
	     VIADEV_WEG(viadev, OFS_PWAYBACK_VOWUME_W));
	outb(chip->pwayback_vowume[viadev->weg_offset / 0x10][1],
	     VIADEV_WEG(viadev, OFS_PWAYBACK_VOWUME_W));
	outw((wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ? VIA8233_WEG_TYPE_16BIT : 0) | /* fowmat */
	     (wuntime->channews > 1 ? VIA8233_WEG_TYPE_STEWEO : 0) | /* steweo */
	     wbits | /* wate */
	     0xff000000,    /* STOP index is nevew weached */
	     VIADEV_WEG(viadev, OFFSET_STOP_IDX));
	udeway(20);
	snd_via82xx_codec_weady(chip, 0);
	wetuwn 0;
}

/*
 * pwepawe cawwback fow muwti-channew pwayback on via823x
 */
static int snd_via8233_muwti_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int swots;
	int fmt;

	if (via_wock_wate(&chip->wates[0], wuntime->wate) < 0)
		wetuwn -EINVAW;
	snd_ac97_set_wate(chip->ac97, AC97_PCM_FWONT_DAC_WATE, wuntime->wate);
	snd_ac97_set_wate(chip->ac97, AC97_PCM_SUWW_DAC_WATE, wuntime->wate);
	snd_ac97_set_wate(chip->ac97, AC97_PCM_WFE_DAC_WATE, wuntime->wate);
	snd_ac97_set_wate(chip->ac97, AC97_SPDIF, wuntime->wate);
	snd_via82xx_channew_weset(chip, viadev);
	snd_via82xx_set_tabwe_ptw(chip, viadev);

	fmt = (wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE) ?
		VIA_WEG_MUWTPWAY_FMT_16BIT : VIA_WEG_MUWTPWAY_FMT_8BIT;
	fmt |= wuntime->channews << 4;
	outb(fmt, VIADEV_WEG(viadev, OFS_MUWTPWAY_FOWMAT));
#if 0
	if (chip->wevision == VIA_WEV_8233A)
		swots = 0;
	ewse
#endif
	{
		/* set sampwe numbew to swot 3, 4, 7, 8, 6, 9 (fow VIA8233/C,8235) */
		/* cowwesponding to FW, FW, WW, WW, C, WFE ?? */
		switch (wuntime->channews) {
		case 1: swots = (1<<0) | (1<<4); bweak;
		case 2: swots = (1<<0) | (2<<4); bweak;
		case 3: swots = (1<<0) | (2<<4) | (5<<8); bweak;
		case 4: swots = (1<<0) | (2<<4) | (3<<8) | (4<<12); bweak;
		case 5: swots = (1<<0) | (2<<4) | (3<<8) | (4<<12) | (5<<16); bweak;
		case 6: swots = (1<<0) | (2<<4) | (3<<8) | (4<<12) | (5<<16) | (6<<20); bweak;
		defauwt: swots = 0; bweak;
		}
	}
	/* STOP index is nevew weached */
	outw(0xff000000 | swots, VIADEV_WEG(viadev, OFFSET_STOP_IDX));
	udeway(20);
	snd_via82xx_codec_weady(chip, 0);
	wetuwn 0;
}

/*
 * pwepawe cawwback fow captuwe on via823x
 */
static int snd_via8233_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	if (via_wock_wate(&chip->wates[1], wuntime->wate) < 0)
		wetuwn -EINVAW;
	snd_ac97_set_wate(chip->ac97, AC97_PCM_WW_ADC_WATE, wuntime->wate);
	snd_via82xx_channew_weset(chip, viadev);
	snd_via82xx_set_tabwe_ptw(chip, viadev);
	outb(VIA_WEG_CAPTUWE_FIFO_ENABWE, VIADEV_WEG(viadev, OFS_CAPTUWE_FIFO));
	outw((wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE ? VIA8233_WEG_TYPE_16BIT : 0) |
	     (wuntime->channews > 1 ? VIA8233_WEG_TYPE_STEWEO : 0) |
	     0xff000000,    /* STOP index is nevew weached */
	     VIADEV_WEG(viadev, OFFSET_STOP_IDX));
	udeway(20);
	snd_via82xx_codec_weady(chip, 0);
	wetuwn 0;
}


/*
 * pcm hawdwawe definition, identicaw fow both pwayback and captuwe
 */
static const stwuct snd_pcm_hawdwawe snd_via82xx_hw =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 /* SNDWV_PCM_INFO_WESUME | */
				 SNDWV_PCM_INFO_PAUSE),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	VIA_MAX_BUFSIZE,
	.pewiod_bytes_min =	32,
	.pewiod_bytes_max =	VIA_MAX_BUFSIZE / 2,
	.pewiods_min =		2,
	.pewiods_max =		VIA_TABWE_SIZE / 2,
	.fifo_size =		0,
};


/*
 * open cawwback skeweton
 */
static int snd_via82xx_pcm_open(stwuct via82xx *chip, stwuct viadev *viadev,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;
	stwuct via_wate_wock *watep;
	boow use_swc = fawse;

	wuntime->hw = snd_via82xx_hw;
	
	/* set the hw wate condition */
	watep = &chip->wates[viadev->diwection];
	spin_wock_iwq(&watep->wock);
	watep->used++;
	if (chip->spdif_on && viadev->weg_offset == 0x30) {
		/* DXS#3 and spdif is on */
		wuntime->hw.wates = chip->ac97->wates[AC97_WATES_SPDIF];
		snd_pcm_wimit_hw_wates(wuntime);
	} ewse if (chip->dxs_fixed && viadev->weg_offset < 0x40) {
		/* fixed DXS pwayback wate */
		wuntime->hw.wates = SNDWV_PCM_WATE_48000;
		wuntime->hw.wate_min = wuntime->hw.wate_max = 48000;
	} ewse if (chip->dxs_swc && viadev->weg_offset < 0x40) {
		/* use fuww SWC capabiwities of DXS */
		wuntime->hw.wates = (SNDWV_PCM_WATE_CONTINUOUS |
				     SNDWV_PCM_WATE_8000_48000);
		wuntime->hw.wate_min = 8000;
		wuntime->hw.wate_max = 48000;
		use_swc = twue;
	} ewse if (! watep->wate) {
		int idx = viadev->diwection ? AC97_WATES_ADC : AC97_WATES_FWONT_DAC;
		wuntime->hw.wates = chip->ac97->wates[idx];
		snd_pcm_wimit_hw_wates(wuntime);
	} ewse {
		/* a fixed wate */
		wuntime->hw.wates = SNDWV_PCM_WATE_KNOT;
		wuntime->hw.wate_max = wuntime->hw.wate_min = watep->wate;
	}
	spin_unwock_iwq(&watep->wock);

	/* we may wemove fowwowing constaint when we modify tabwe entwies
	   in intewwupt */
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	if (use_swc) {
		eww = snd_pcm_hw_wuwe_nowesampwe(wuntime, 48000);
		if (eww < 0)
			wetuwn eww;
	}

	wuntime->pwivate_data = viadev;
	viadev->substweam = substweam;

	wetuwn 0;
}


/*
 * open cawwback fow pwayback on via686
 */
static int snd_via686_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = &chip->devs[chip->pwayback_devno + substweam->numbew];
	int eww;

	eww = snd_via82xx_pcm_open(chip, viadev, substweam);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/*
 * open cawwback fow pwayback on via823x DXS
 */
static int snd_via8233_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev;
	unsigned int stweam;
	int eww;

	viadev = &chip->devs[chip->pwayback_devno + substweam->numbew];
	eww = snd_via82xx_pcm_open(chip, viadev, substweam);
	if (eww < 0)
		wetuwn eww;
	stweam = viadev->weg_offset / 0x10;
	if (chip->dxs_contwows[stweam]) {
		chip->pwayback_vowume[stweam][0] =
				VIA_DXS_MAX_VOWUME - (dxs_init_vowume & 31);
		chip->pwayback_vowume[stweam][1] =
				VIA_DXS_MAX_VOWUME - (dxs_init_vowume & 31);
		chip->dxs_contwows[stweam]->vd[0].access &=
			~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			       SNDWV_CTW_EVENT_MASK_INFO,
			       &chip->dxs_contwows[stweam]->id);
	}
	wetuwn 0;
}

/*
 * open cawwback fow pwayback on via823x muwti-channew
 */
static int snd_via8233_muwti_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = &chip->devs[chip->muwti_devno];
	int eww;
	/* channews constwaint fow VIA8233A
	 * 3 and 5 channews awe not suppowted
	 */
	static const unsigned int channews[] = {
		1, 2, 4, 6
	};
	static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist = channews,
		.mask = 0,
	};

	eww = snd_via82xx_pcm_open(chip, viadev, substweam);
	if (eww < 0)
		wetuwn eww;
	substweam->wuntime->hw.channews_max = 6;
	if (chip->wevision == VIA_WEV_8233A)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &hw_constwaints_channews);
	wetuwn 0;
}

/*
 * open cawwback fow captuwe on via686 and via823x
 */
static int snd_via82xx_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = &chip->devs[chip->captuwe_devno + substweam->pcm->device];

	wetuwn snd_via82xx_pcm_open(chip, viadev, substweam);
}

/*
 * cwose cawwback
 */
static int snd_via82xx_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	stwuct via_wate_wock *watep;

	/* wewease the wate wock */
	watep = &chip->wates[viadev->diwection];
	spin_wock_iwq(&watep->wock);
	watep->used--;
	if (! watep->used)
		watep->wate = 0;
	spin_unwock_iwq(&watep->wock);
	if (! watep->wate) {
		if (! viadev->diwection) {
			snd_ac97_update_powew(chip->ac97,
					      AC97_PCM_FWONT_DAC_WATE, 0);
			snd_ac97_update_powew(chip->ac97,
					      AC97_PCM_SUWW_DAC_WATE, 0);
			snd_ac97_update_powew(chip->ac97,
					      AC97_PCM_WFE_DAC_WATE, 0);
		} ewse
			snd_ac97_update_powew(chip->ac97,
					      AC97_PCM_WW_ADC_WATE, 0);
	}
	viadev->substweam = NUWW;
	wetuwn 0;
}

static int snd_via8233_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct via82xx *chip = snd_pcm_substweam_chip(substweam);
	stwuct viadev *viadev = substweam->wuntime->pwivate_data;
	unsigned int stweam;

	stweam = viadev->weg_offset / 0x10;
	if (chip->dxs_contwows[stweam]) {
		chip->dxs_contwows[stweam]->vd[0].access |=
			SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_INFO,
			       &chip->dxs_contwows[stweam]->id);
	}
	wetuwn snd_via82xx_pcm_cwose(substweam);
}


/* via686 pwayback cawwbacks */
static const stwuct snd_pcm_ops snd_via686_pwayback_ops = {
	.open =		snd_via686_pwayback_open,
	.cwose =	snd_via82xx_pcm_cwose,
	.hw_pawams =	snd_via82xx_hw_pawams,
	.hw_fwee =	snd_via82xx_hw_fwee,
	.pwepawe =	snd_via686_pwayback_pwepawe,
	.twiggew =	snd_via82xx_pcm_twiggew,
	.pointew =	snd_via686_pcm_pointew,
};

/* via686 captuwe cawwbacks */
static const stwuct snd_pcm_ops snd_via686_captuwe_ops = {
	.open =		snd_via82xx_captuwe_open,
	.cwose =	snd_via82xx_pcm_cwose,
	.hw_pawams =	snd_via82xx_hw_pawams,
	.hw_fwee =	snd_via82xx_hw_fwee,
	.pwepawe =	snd_via686_captuwe_pwepawe,
	.twiggew =	snd_via82xx_pcm_twiggew,
	.pointew =	snd_via686_pcm_pointew,
};

/* via823x DSX pwayback cawwbacks */
static const stwuct snd_pcm_ops snd_via8233_pwayback_ops = {
	.open =		snd_via8233_pwayback_open,
	.cwose =	snd_via8233_pwayback_cwose,
	.hw_pawams =	snd_via82xx_hw_pawams,
	.hw_fwee =	snd_via82xx_hw_fwee,
	.pwepawe =	snd_via8233_pwayback_pwepawe,
	.twiggew =	snd_via82xx_pcm_twiggew,
	.pointew =	snd_via8233_pcm_pointew,
};

/* via823x muwti-channew pwayback cawwbacks */
static const stwuct snd_pcm_ops snd_via8233_muwti_ops = {
	.open =		snd_via8233_muwti_open,
	.cwose =	snd_via82xx_pcm_cwose,
	.hw_pawams =	snd_via82xx_hw_pawams,
	.hw_fwee =	snd_via82xx_hw_fwee,
	.pwepawe =	snd_via8233_muwti_pwepawe,
	.twiggew =	snd_via82xx_pcm_twiggew,
	.pointew =	snd_via8233_pcm_pointew,
};

/* via823x captuwe cawwbacks */
static const stwuct snd_pcm_ops snd_via8233_captuwe_ops = {
	.open =		snd_via82xx_captuwe_open,
	.cwose =	snd_via82xx_pcm_cwose,
	.hw_pawams =	snd_via82xx_hw_pawams,
	.hw_fwee =	snd_via82xx_hw_fwee,
	.pwepawe =	snd_via8233_captuwe_pwepawe,
	.twiggew =	snd_via82xx_pcm_twiggew,
	.pointew =	snd_via8233_pcm_pointew,
};


static void init_viadev(stwuct via82xx *chip, int idx, unsigned int weg_offset,
			int shadow_pos, int diwection)
{
	chip->devs[idx].weg_offset = weg_offset;
	chip->devs[idx].shadow_shift = shadow_pos * 4;
	chip->devs[idx].diwection = diwection;
	chip->devs[idx].powt = chip->powt + weg_offset;
}

/*
 * cweate pcm instances fow VIA8233, 8233C and 8235 (not 8233A)
 */
static int snd_via8233_pcm_new(stwuct via82xx *chip)
{
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_chmap *chmap;
	int i, eww;

	chip->pwayback_devno = 0;	/* x 4 */
	chip->muwti_devno = 4;		/* x 1 */
	chip->captuwe_devno = 5;	/* x 2 */
	chip->num_devs = 7;
	chip->intw_mask = 0x33033333; /* FWAG|EOW fow wec0-1, mc, sdx0-3 */

	/* PCM #0:  4 DSX pwaybacks and 1 captuwe */
	eww = snd_pcm_new(chip->cawd, chip->cawd->showtname, 0, 4, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_via8233_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_via8233_captuwe_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcms[0] = pcm;
	/* set up pwaybacks */
	fow (i = 0; i < 4; i++)
		init_viadev(chip, i, 0x10 * i, i, 0);
	/* captuwe */
	init_viadev(chip, chip->captuwe_devno, VIA_WEG_CAPTUWE_8233_STATUS, 6, 1);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_BUFSIZE);

	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_std_chmaps, 2, 0,
				     &chmap);
	if (eww < 0)
		wetuwn eww;

	/* PCM #1:  muwti-channew pwayback and 2nd captuwe */
	eww = snd_pcm_new(chip->cawd, chip->cawd->showtname, 1, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_via8233_muwti_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_via8233_captuwe_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcms[1] = pcm;
	/* set up pwayback */
	init_viadev(chip, chip->muwti_devno, VIA_WEG_MUWTPWAY_STATUS, 4, 0);
	/* set up captuwe */
	init_viadev(chip, chip->captuwe_devno + 1, VIA_WEG_CAPTUWE_8233_STATUS + 0x10, 7, 1);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_BUFSIZE);

	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps, 6, 0,
				     &chmap);
	if (eww < 0)
		wetuwn eww;
	chip->ac97->chmaps[SNDWV_PCM_STWEAM_PWAYBACK] = chmap;

	wetuwn 0;
}

/*
 * cweate pcm instances fow VIA8233A
 */
static int snd_via8233a_pcm_new(stwuct via82xx *chip)
{
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_chmap *chmap;
	int eww;

	chip->muwti_devno = 0;
	chip->pwayback_devno = 1;
	chip->captuwe_devno = 2;
	chip->num_devs = 3;
	chip->intw_mask = 0x03033000; /* FWAG|EOW fow wec0, mc, sdx3 */

	/* PCM #0:  muwti-channew pwayback and captuwe */
	eww = snd_pcm_new(chip->cawd, chip->cawd->showtname, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_via8233_muwti_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_via8233_captuwe_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcms[0] = pcm;
	/* set up pwayback */
	init_viadev(chip, chip->muwti_devno, VIA_WEG_MUWTPWAY_STATUS, 4, 0);
	/* captuwe */
	init_viadev(chip, chip->captuwe_devno, VIA_WEG_CAPTUWE_8233_STATUS, 6, 1);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_BUFSIZE);

	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps, 6, 0,
				     &chmap);
	if (eww < 0)
		wetuwn eww;
	chip->ac97->chmaps[SNDWV_PCM_STWEAM_PWAYBACK] = chmap;

	/* SPDIF suppowted? */
	if (! ac97_can_spdif(chip->ac97))
		wetuwn 0;

	/* PCM #1:  DXS3 pwayback (fow spdif) */
	eww = snd_pcm_new(chip->cawd, chip->cawd->showtname, 1, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_via8233_pwayback_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcms[1] = pcm;
	/* set up pwayback */
	init_viadev(chip, chip->pwayback_devno, 0x30, 3, 0);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_BUFSIZE);
	wetuwn 0;
}

/*
 * cweate a pcm instance fow via686a/b
 */
static int snd_via686_pcm_new(stwuct via82xx *chip)
{
	stwuct snd_pcm *pcm;
	int eww;

	chip->pwayback_devno = 0;
	chip->captuwe_devno = 1;
	chip->num_devs = 2;
	chip->intw_mask = 0x77; /* FWAG | EOW fow PB, CP, FM */

	eww = snd_pcm_new(chip->cawd, chip->cawd->showtname, 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_via686_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_via686_captuwe_ops);
	pcm->pwivate_data = chip;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcms[0] = pcm;
	init_viadev(chip, 0, VIA_WEG_PWAYBACK_STATUS, 0, 0);
	init_viadev(chip, 1, VIA_WEG_CAPTUWE_STATUS, 0, 1);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_BUFSIZE);
	wetuwn 0;
}


/*
 *  Mixew pawt
 */

static int snd_via8233_captuwe_souwce_info(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	/* fowmewwy they wewe "Wine" and "Mic", but it wooks wike that they
	 * have nothing to do with the actuaw physicaw connections...
	 */
	static const chaw * const texts[2] = {
		"Input1", "Input2"
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_via8233_captuwe_souwce_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong powt = chip->powt + (kcontwow->id.index ? (VIA_WEG_CAPTUWE_CHANNEW + 0x10) : VIA_WEG_CAPTUWE_CHANNEW);
	ucontwow->vawue.enumewated.item[0] = inb(powt) & VIA_WEG_CAPTUWE_CHANNEW_MIC ? 1 : 0;
	wetuwn 0;
}

static int snd_via8233_captuwe_souwce_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned wong powt = chip->powt + (kcontwow->id.index ? (VIA_WEG_CAPTUWE_CHANNEW + 0x10) : VIA_WEG_CAPTUWE_CHANNEW);
	u8 vaw, ovaw;

	spin_wock_iwq(&chip->weg_wock);
	ovaw = inb(powt);
	vaw = ovaw & ~VIA_WEG_CAPTUWE_CHANNEW_MIC;
	if (ucontwow->vawue.enumewated.item[0])
		vaw |= VIA_WEG_CAPTUWE_CHANNEW_MIC;
	if (vaw != ovaw)
		outb(vaw, powt);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn vaw != ovaw;
}

static stwuct snd_kcontwow_new snd_via8233_captuwe_souwce = {
	.name = "Input Souwce Sewect",
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = snd_via8233_captuwe_souwce_info,
	.get = snd_via8233_captuwe_souwce_get,
	.put = snd_via8233_captuwe_souwce_put,
};

#define snd_via8233_dxs3_spdif_info	snd_ctw_boowean_mono_info

static int snd_via8233_dxs3_spdif_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	u8 vaw;

	pci_wead_config_byte(chip->pci, VIA8233_SPDIF_CTWW, &vaw);
	ucontwow->vawue.integew.vawue[0] = (vaw & VIA8233_SPDIF_DX3) ? 1 : 0;
	wetuwn 0;
}

static int snd_via8233_dxs3_spdif_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	u8 vaw, ovaw;

	pci_wead_config_byte(chip->pci, VIA8233_SPDIF_CTWW, &ovaw);
	vaw = ovaw & ~VIA8233_SPDIF_DX3;
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= VIA8233_SPDIF_DX3;
	/* save the spdif fwag fow wate fiwtewing */
	chip->spdif_on = ucontwow->vawue.integew.vawue[0] ? 1 : 0;
	if (vaw != ovaw) {
		pci_wwite_config_byte(chip->pci, VIA8233_SPDIF_CTWW, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_via8233_dxs3_spdif_contwow = {
	.name = SNDWV_CTW_NAME_IEC958("Output ",NONE,SWITCH),
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = snd_via8233_dxs3_spdif_info,
	.get = snd_via8233_dxs3_spdif_get,
	.put = snd_via8233_dxs3_spdif_put,
};

static int snd_via8233_dxs_vowume_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = VIA_DXS_MAX_VOWUME;
	wetuwn 0;
}

static int snd_via8233_dxs_vowume_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned int idx = kcontwow->id.subdevice;

	ucontwow->vawue.integew.vawue[0] = VIA_DXS_MAX_VOWUME - chip->pwayback_vowume[idx][0];
	ucontwow->vawue.integew.vawue[1] = VIA_DXS_MAX_VOWUME - chip->pwayback_vowume[idx][1];
	wetuwn 0;
}

static int snd_via8233_pcmdxs_vowume_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = VIA_DXS_MAX_VOWUME - chip->pwayback_vowume_c[0];
	ucontwow->vawue.integew.vawue[1] = VIA_DXS_MAX_VOWUME - chip->pwayback_vowume_c[1];
	wetuwn 0;
}

static int snd_via8233_dxs_vowume_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned int idx = kcontwow->id.subdevice;
	unsigned wong powt = chip->powt + 0x10 * idx;
	unsigned chaw vaw;
	int i, change = 0;

	fow (i = 0; i < 2; i++) {
		vaw = ucontwow->vawue.integew.vawue[i];
		if (vaw > VIA_DXS_MAX_VOWUME)
			vaw = VIA_DXS_MAX_VOWUME;
		vaw = VIA_DXS_MAX_VOWUME - vaw;
		change |= vaw != chip->pwayback_vowume[idx][i];
		if (change) {
			chip->pwayback_vowume[idx][i] = vaw;
			outb(vaw, powt + VIA_WEG_OFS_PWAYBACK_VOWUME_W + i);
		}
	}
	wetuwn change;
}

static int snd_via8233_pcmdxs_vowume_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct via82xx *chip = snd_kcontwow_chip(kcontwow);
	unsigned int idx;
	unsigned chaw vaw;
	int i, change = 0;

	fow (i = 0; i < 2; i++) {
		vaw = ucontwow->vawue.integew.vawue[i];
		if (vaw > VIA_DXS_MAX_VOWUME)
			vaw = VIA_DXS_MAX_VOWUME;
		vaw = VIA_DXS_MAX_VOWUME - vaw;
		if (vaw != chip->pwayback_vowume_c[i]) {
			change = 1;
			chip->pwayback_vowume_c[i] = vaw;
			fow (idx = 0; idx < 4; idx++) {
				unsigned wong powt = chip->powt + 0x10 * idx;
				chip->pwayback_vowume[idx][i] = vaw;
				outb(vaw, powt + VIA_WEG_OFS_PWAYBACK_VOWUME_W + i);
			}
		}
	}
	wetuwn change;
}

static const DECWAWE_TWV_DB_SCAWE(db_scawe_dxs, -4650, 150, 1);

static const stwuct snd_kcontwow_new snd_via8233_pcmdxs_vowume_contwow = {
	.name = "PCM Pwayback Vowume",
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD),
	.info = snd_via8233_dxs_vowume_info,
	.get = snd_via8233_pcmdxs_vowume_get,
	.put = snd_via8233_pcmdxs_vowume_put,
	.twv = { .p = db_scawe_dxs }
};

static const stwuct snd_kcontwow_new snd_via8233_dxs_vowume_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.device = 0,
	/* .subdevice set watew */
	.name = "PCM Pwayback Vowume",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
		  SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.info = snd_via8233_dxs_vowume_info,
	.get = snd_via8233_dxs_vowume_get,
	.put = snd_via8233_dxs_vowume_put,
	.twv = { .p = db_scawe_dxs }
};

/*
 */

static void snd_via82xx_mixew_fwee_ac97_bus(stwuct snd_ac97_bus *bus)
{
	stwuct via82xx *chip = bus->pwivate_data;
	chip->ac97_bus = NUWW;
}

static void snd_via82xx_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct via82xx *chip = ac97->pwivate_data;
	chip->ac97 = NUWW;
}

static const stwuct ac97_quiwk ac97_quiwks[] = {
	{
		.subvendow = 0x1106,
		.subdevice = 0x4161,
		.codec_id = 0x56494161, /* VT1612A */
		.name = "Sowtek SW-75DWV5",
		.type = AC97_TUNE_NONE
	},
	{	/* FIXME: which codec? */
		.subvendow = 0x1106,
		.subdevice = 0x4161,
		.name = "ASWock K7VT2",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x110a,
		.subdevice = 0x0079,
		.name = "Fujitsu Siemens D1289",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1019,
		.subdevice = 0x0a81,
		.name = "ECS K7VTA3",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1019,
		.subdevice = 0x0a85,
		.name = "ECS W7VMM2",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1019,
		.subdevice = 0x1841,
		.name = "ECS K7VTA3",
		.type = AC97_TUNE_HP_ONWY
	},
	{
		.subvendow = 0x1849,
		.subdevice = 0x3059,
		.name = "ASWock K7VM2",
		.type = AC97_TUNE_HP_ONWY	/* VT1616 */
	},
	{
		.subvendow = 0x14cd,
		.subdevice = 0x7002,
		.name = "Unknown",
		.type = AC97_TUNE_AWC_JACK
	},
	{
		.subvendow = 0x1071,
		.subdevice = 0x8590,
		.name = "Mitac Mobo",
		.type = AC97_TUNE_AWC_JACK
	},
	{
		.subvendow = 0x161f,
		.subdevice = 0x202b,
		.name = "Awima Notebook",
		.type = AC97_TUNE_HP_ONWY,
	},
	{
		.subvendow = 0x161f,
		.subdevice = 0x2032,
		.name = "Tawga Twavewwew 811",
		.type = AC97_TUNE_HP_ONWY,
	},
	{
		.subvendow = 0x161f,
		.subdevice = 0x2032,
		.name = "m680x",
		.type = AC97_TUNE_HP_ONWY, /* http://waunchpad.net/bugs/38546 */
	},
	{
		.subvendow = 0x1297,
		.subdevice = 0xa232,
		.name = "Shuttwe AK32VN",
		.type = AC97_TUNE_HP_ONWY
	},
	{ } /* tewminatow */
};

static int snd_via82xx_mixew_new(stwuct via82xx *chip, const chaw *quiwk_ovewwide)
{
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_via82xx_codec_wwite,
		.wead = snd_via82xx_codec_wead,
		.wait = snd_via82xx_codec_wait,
	};

	eww = snd_ac97_bus(chip->cawd, 0, &ops, chip, &chip->ac97_bus);
	if (eww < 0)
		wetuwn eww;
	chip->ac97_bus->pwivate_fwee = snd_via82xx_mixew_fwee_ac97_bus;
	chip->ac97_bus->cwock = chip->ac97_cwock;

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.pwivate_fwee = snd_via82xx_mixew_fwee_ac97;
	ac97.pci = chip->pci;
	ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWEW_SAVE;
	eww = snd_ac97_mixew(chip->ac97_bus, &ac97, &chip->ac97);
	if (eww < 0)
		wetuwn eww;

	snd_ac97_tune_hawdwawe(chip->ac97, ac97_quiwks, quiwk_ovewwide);

	if (chip->chip_type != TYPE_VIA686) {
		/* use swot 10/11 */
		snd_ac97_update_bits(chip->ac97, AC97_EXTENDED_STATUS, 0x03 << 4, 0x03 << 4);
	}

	wetuwn 0;
}

#ifdef SUPPOWT_JOYSTICK
#define JOYSTICK_ADDW	0x200
static int snd_via686_cweate_gamepowt(stwuct via82xx *chip, unsigned chaw *wegacy)
{
	stwuct gamepowt *gp;

	if (!joystick)
		wetuwn -ENODEV;

	if (!devm_wequest_wegion(chip->cawd->dev, JOYSTICK_ADDW, 8,
				 "VIA686 gamepowt")) {
		dev_wawn(chip->cawd->dev, "cannot wesewve joystick powt %#x\n",
		       JOYSTICK_ADDW);
		wetuwn -EBUSY;
	}

	chip->gamepowt = gp = gamepowt_awwocate_powt();
	if (!gp) {
		dev_eww(chip->cawd->dev,
			"cannot awwocate memowy fow gamepowt\n");
		wetuwn -ENOMEM;
	}

	gamepowt_set_name(gp, "VIA686 Gamepowt");
	gamepowt_set_phys(gp, "pci%s/gamepowt0", pci_name(chip->pci));
	gamepowt_set_dev_pawent(gp, &chip->pci->dev);
	gp->io = JOYSTICK_ADDW;

	/* Enabwe wegacy joystick powt */
	*wegacy |= VIA_FUNC_ENABWE_GAME;
	pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, *wegacy);

	gamepowt_wegistew_powt(chip->gamepowt);

	wetuwn 0;
}

static void snd_via686_fwee_gamepowt(stwuct via82xx *chip)
{
	if (chip->gamepowt) {
		gamepowt_unwegistew_powt(chip->gamepowt);
		chip->gamepowt = NUWW;
	}
}
#ewse
static inwine int snd_via686_cweate_gamepowt(stwuct via82xx *chip, unsigned chaw *wegacy)
{
	wetuwn -ENOSYS;
}
static inwine void snd_via686_fwee_gamepowt(stwuct via82xx *chip) { }
#endif


/*
 *
 */

static int snd_via8233_init_misc(stwuct via82xx *chip)
{
	int i, eww, caps;
	unsigned chaw vaw;

	caps = chip->chip_type == TYPE_VIA8233A ? 1 : 2;
	fow (i = 0; i < caps; i++) {
		snd_via8233_captuwe_souwce.index = i;
		eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&snd_via8233_captuwe_souwce, chip));
		if (eww < 0)
			wetuwn eww;
	}
	if (ac97_can_spdif(chip->ac97)) {
		eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&snd_via8233_dxs3_spdif_contwow, chip));
		if (eww < 0)
			wetuwn eww;
	}
	if (chip->chip_type != TYPE_VIA8233A) {
		/* when no h/w PCM vowume contwow is found, use DXS vowume contwow
		 * as the PCM vow contwow
		 */
		if (!snd_ctw_find_id_mixew(chip->cawd, "PCM Pwayback Vowume")) {
			dev_info(chip->cawd->dev,
				 "Using DXS as PCM Pwayback\n");
			eww = snd_ctw_add(chip->cawd, snd_ctw_new1(&snd_via8233_pcmdxs_vowume_contwow, chip));
			if (eww < 0)
				wetuwn eww;
		}
		ewse /* Using DXS when PCM emuwation is enabwed is weawwy weiwd */
		{
			fow (i = 0; i < 4; ++i) {
				stwuct snd_kcontwow *kctw;

				kctw = snd_ctw_new1(
					&snd_via8233_dxs_vowume_contwow, chip);
				if (!kctw)
					wetuwn -ENOMEM;
				kctw->id.subdevice = i;
				eww = snd_ctw_add(chip->cawd, kctw);
				if (eww < 0)
					wetuwn eww;
				chip->dxs_contwows[i] = kctw;
			}
		}
	}
	/* sewect spdif data swot 10/11 */
	pci_wead_config_byte(chip->pci, VIA8233_SPDIF_CTWW, &vaw);
	vaw = (vaw & ~VIA8233_SPDIF_SWOT_MASK) | VIA8233_SPDIF_SWOT_1011;
	vaw &= ~VIA8233_SPDIF_DX3; /* SPDIF off as defauwt */
	pci_wwite_config_byte(chip->pci, VIA8233_SPDIF_CTWW, vaw);

	wetuwn 0;
}

static int snd_via686_init_misc(stwuct via82xx *chip)
{
	unsigned chaw wegacy, wegacy_cfg;
	int wev_h = 0;

	wegacy = chip->owd_wegacy;
	wegacy_cfg = chip->owd_wegacy_cfg;
	wegacy |= VIA_FUNC_MIDI_IWQMASK;	/* FIXME: cowwect? (disabwe MIDI) */
	wegacy &= ~VIA_FUNC_ENABWE_GAME;	/* disabwe joystick */
	if (chip->wevision >= VIA_WEV_686_H) {
		wev_h = 1;
		if (mpu_powt >= 0x200) {	/* fowce MIDI */
			mpu_powt &= 0xfffc;
			pci_wwite_config_dwowd(chip->pci, 0x18, mpu_powt | 0x01);
#ifdef CONFIG_PM_SWEEP
			chip->mpu_powt_saved = mpu_powt;
#endif
		} ewse {
			mpu_powt = pci_wesouwce_stawt(chip->pci, 2);
		}
	} ewse {
		switch (mpu_powt) {	/* fowce MIDI */
		case 0x300:
		case 0x310:
		case 0x320:
		case 0x330:
			wegacy_cfg &= ~(3 << 2);
			wegacy_cfg |= (mpu_powt & 0x0030) >> 2;
			bweak;
		defauwt:			/* no, use BIOS settings */
			if (wegacy & VIA_FUNC_ENABWE_MIDI)
				mpu_powt = 0x300 + ((wegacy_cfg & 0x000c) << 2);
			bweak;
		}
	}
	if (mpu_powt >= 0x200)
		chip->mpu_wes = devm_wequest_wegion(&chip->pci->dev, mpu_powt,
						    2, "VIA82xx MPU401");
	if (chip->mpu_wes) {
		if (wev_h)
			wegacy |= VIA_FUNC_MIDI_PNP;	/* enabwe PCI I/O 2 */
		wegacy |= VIA_FUNC_ENABWE_MIDI;
	} ewse {
		if (wev_h)
			wegacy &= ~VIA_FUNC_MIDI_PNP;	/* disabwe PCI I/O 2 */
		wegacy &= ~VIA_FUNC_ENABWE_MIDI;
		mpu_powt = 0;
	}

	pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, wegacy);
	pci_wwite_config_byte(chip->pci, VIA_PNP_CONTWOW, wegacy_cfg);
	if (chip->mpu_wes) {
		if (snd_mpu401_uawt_new(chip->cawd, 0, MPU401_HW_VIA686A,
					mpu_powt, MPU401_INFO_INTEGWATED |
					MPU401_INFO_IWQ_HOOK, -1,
					&chip->wmidi) < 0) {
			dev_wawn(chip->cawd->dev,
				 "unabwe to initiawize MPU-401 at 0x%wx, skipping\n",
				 mpu_powt);
			wegacy &= ~VIA_FUNC_ENABWE_MIDI;
		} ewse {
			wegacy &= ~VIA_FUNC_MIDI_IWQMASK;	/* enabwe MIDI intewwupt */
		}
		pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, wegacy);
	}

	snd_via686_cweate_gamepowt(chip, &wegacy);

#ifdef CONFIG_PM_SWEEP
	chip->wegacy_saved = wegacy;
	chip->wegacy_cfg_saved = wegacy_cfg;
#endif

	wetuwn 0;
}


/*
 * pwoc intewface
 */
static void snd_via82xx_pwoc_wead(stwuct snd_info_entwy *entwy,
				  stwuct snd_info_buffew *buffew)
{
	stwuct via82xx *chip = entwy->pwivate_data;
	int i;
	
	snd_ipwintf(buffew, "%s\n\n", chip->cawd->wongname);
	fow (i = 0; i < 0xa0; i += 4) {
		snd_ipwintf(buffew, "%02x: %08x\n", i, inw(chip->powt + i));
	}
}

static void snd_via82xx_pwoc_init(stwuct via82xx *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "via82xx", chip,
			     snd_via82xx_pwoc_wead);
}

/*
 *
 */

static int snd_via82xx_chip_init(stwuct via82xx *chip)
{
	unsigned int vaw;
	unsigned wong end_time;
	unsigned chaw pvaw;

#if 0 /* bwoken on K7M? */
	if (chip->chip_type == TYPE_VIA686)
		/* disabwe aww wegacy powts */
		pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, 0);
#endif
	pci_wead_config_byte(chip->pci, VIA_ACWINK_STAT, &pvaw);
	if (! (pvaw & VIA_ACWINK_C00_WEADY)) { /* codec not weady? */
		/* deassewt ACWink weset, fowce SYNC */
		pci_wwite_config_byte(chip->pci, VIA_ACWINK_CTWW,
				      VIA_ACWINK_CTWW_ENABWE |
				      VIA_ACWINK_CTWW_WESET |
				      VIA_ACWINK_CTWW_SYNC);
		udeway(100);
#if 1 /* FIXME: shouwd we do fuww weset hewe fow aww chip modews? */
		pci_wwite_config_byte(chip->pci, VIA_ACWINK_CTWW, 0x00);
		udeway(100);
#ewse
		/* deassewt ACWink weset, fowce SYNC (wawm AC'97 weset) */
		pci_wwite_config_byte(chip->pci, VIA_ACWINK_CTWW,
				      VIA_ACWINK_CTWW_WESET|VIA_ACWINK_CTWW_SYNC);
		udeway(2);
#endif
		/* ACWink on, deassewt ACWink weset, VSW, SGD data out */
		/* note - FM data out has twoubwe with non VWA codecs !! */
		pci_wwite_config_byte(chip->pci, VIA_ACWINK_CTWW, VIA_ACWINK_CTWW_INIT);
		udeway(100);
	}
	
	/* Make suwe VWA is enabwed, in case we didn't do a
	 * compwete codec weset, above */
	pci_wead_config_byte(chip->pci, VIA_ACWINK_CTWW, &pvaw);
	if ((pvaw & VIA_ACWINK_CTWW_INIT) != VIA_ACWINK_CTWW_INIT) {
		/* ACWink on, deassewt ACWink weset, VSW, SGD data out */
		/* note - FM data out has twoubwe with non VWA codecs !! */
		pci_wwite_config_byte(chip->pci, VIA_ACWINK_CTWW, VIA_ACWINK_CTWW_INIT);
		udeway(100);
	}

	/* wait untiw codec weady */
	end_time = jiffies + msecs_to_jiffies(750);
	do {
		pci_wead_config_byte(chip->pci, VIA_ACWINK_STAT, &pvaw);
		if (pvaw & VIA_ACWINK_C00_WEADY) /* pwimawy codec weady */
			bweak;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_befowe(jiffies, end_time));

	vaw = snd_via82xx_codec_xwead(chip);
	if (vaw & VIA_WEG_AC97_BUSY)
		dev_eww(chip->cawd->dev,
			"AC'97 codec is not weady [0x%x]\n", vaw);

#if 0 /* FIXME: we don't suppowt the second codec yet so skip the detection now.. */
	snd_via82xx_codec_xwwite(chip, VIA_WEG_AC97_WEAD |
				 VIA_WEG_AC97_SECONDAWY_VAWID |
				 (VIA_WEG_AC97_CODEC_ID_SECONDAWY << VIA_WEG_AC97_CODEC_ID_SHIFT));
	end_time = jiffies + msecs_to_jiffies(750);
	snd_via82xx_codec_xwwite(chip, VIA_WEG_AC97_WEAD |
				 VIA_WEG_AC97_SECONDAWY_VAWID |
				 (VIA_WEG_AC97_CODEC_ID_SECONDAWY << VIA_WEG_AC97_CODEC_ID_SHIFT));
	do {
		vaw = snd_via82xx_codec_xwead(chip);
		if (vaw & VIA_WEG_AC97_SECONDAWY_VAWID) {
			chip->ac97_secondawy = 1;
			goto __ac97_ok2;
		}
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_befowe(jiffies, end_time));
	/* This is ok, the most of mothewboawds have onwy one codec */

      __ac97_ok2:
#endif

	if (chip->chip_type == TYPE_VIA686) {
		/* woute FM twap to IWQ, disabwe FM twap */
		pci_wwite_config_byte(chip->pci, VIA_FM_NMI_CTWW, 0);
		/* disabwe aww GPI intewwupts */
		outw(0, VIAWEG(chip, GPI_INTW));
	}

	if (chip->chip_type != TYPE_VIA686) {
		/* Wowkawound fow Awawd BIOS bug:
		 * DXS channews don't wowk pwopewwy with VWA if MC97 is disabwed.
		 */
		stwuct pci_dev *pci;
		pci = pci_get_device(0x1106, 0x3068, NUWW); /* MC97 */
		if (pci) {
			unsigned chaw data;
			pci_wead_config_byte(pci, 0x44, &data);
			pci_wwite_config_byte(pci, 0x44, data | 0x40);
			pci_dev_put(pci);
		}
	}

	if (chip->chip_type != TYPE_VIA8233A) {
		int i, idx;
		fow (idx = 0; idx < 4; idx++) {
			unsigned wong powt = chip->powt + 0x10 * idx;
			fow (i = 0; i < 2; i++) {
				chip->pwayback_vowume[idx][i]=chip->pwayback_vowume_c[i];
				outb(chip->pwayback_vowume_c[i],
				     powt + VIA_WEG_OFS_PWAYBACK_VOWUME_W + i);
			}
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static int snd_via82xx_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct via82xx *chip = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	fow (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channew_weset(chip, &chip->devs[i]);
	snd_ac97_suspend(chip->ac97);

	/* save misc vawues */
	if (chip->chip_type != TYPE_VIA686) {
		pci_wead_config_byte(chip->pci, VIA8233_SPDIF_CTWW, &chip->spdif_ctww_saved);
		chip->captuwe_swc_saved[0] = inb(chip->powt + VIA_WEG_CAPTUWE_CHANNEW);
		chip->captuwe_swc_saved[1] = inb(chip->powt + VIA_WEG_CAPTUWE_CHANNEW + 0x10);
	}

	wetuwn 0;
}

static int snd_via82xx_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct via82xx *chip = cawd->pwivate_data;
	int i;

	snd_via82xx_chip_init(chip);

	if (chip->chip_type == TYPE_VIA686) {
		if (chip->mpu_powt_saved)
			pci_wwite_config_dwowd(chip->pci, 0x18, chip->mpu_powt_saved | 0x01);
		pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, chip->wegacy_saved);
		pci_wwite_config_byte(chip->pci, VIA_PNP_CONTWOW, chip->wegacy_cfg_saved);
	} ewse {
		pci_wwite_config_byte(chip->pci, VIA8233_SPDIF_CTWW, chip->spdif_ctww_saved);
		outb(chip->captuwe_swc_saved[0], chip->powt + VIA_WEG_CAPTUWE_CHANNEW);
		outb(chip->captuwe_swc_saved[1], chip->powt + VIA_WEG_CAPTUWE_CHANNEW + 0x10);
	}

	snd_ac97_wesume(chip->ac97);

	fow (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channew_weset(chip, &chip->devs[i]);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_via82xx_pm, snd_via82xx_suspend, snd_via82xx_wesume);
#define SND_VIA82XX_PM_OPS	&snd_via82xx_pm
#ewse
#define SND_VIA82XX_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static void snd_via82xx_fwee(stwuct snd_cawd *cawd)
{
	stwuct via82xx *chip = cawd->pwivate_data;
	unsigned int i;

	/* disabwe intewwupts */
	fow (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channew_weset(chip, &chip->devs[i]);

	if (chip->chip_type == TYPE_VIA686) {
		snd_via686_fwee_gamepowt(chip);
		pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE, chip->owd_wegacy);
		pci_wwite_config_byte(chip->pci, VIA_PNP_CONTWOW, chip->owd_wegacy_cfg);
	}
}

static int snd_via82xx_cweate(stwuct snd_cawd *cawd,
			      stwuct pci_dev *pci,
			      int chip_type,
			      int wevision,
			      unsigned int ac97_cwock)
{
	stwuct via82xx *chip = cawd->pwivate_data;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	chip->chip_type = chip_type;
	chip->wevision = wevision;

	spin_wock_init(&chip->weg_wock);
	spin_wock_init(&chip->wates[0].wock);
	spin_wock_init(&chip->wates[1].wock);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	pci_wead_config_byte(pci, VIA_FUNC_ENABWE, &chip->owd_wegacy);
	pci_wead_config_byte(pci, VIA_PNP_CONTWOW, &chip->owd_wegacy_cfg);
	pci_wwite_config_byte(chip->pci, VIA_FUNC_ENABWE,
			      chip->owd_wegacy & ~(VIA_FUNC_ENABWE_SB|VIA_FUNC_ENABWE_FM));

	eww = pci_wequest_wegions(pci, cawd->dwivew);
	if (eww < 0)
		wetuwn eww;
	chip->powt = pci_wesouwce_stawt(pci, 0);
	if (devm_wequest_iwq(&pci->dev, pci->iwq,
			     chip_type == TYPE_VIA8233 ?
			     snd_via8233_intewwupt : snd_via686_intewwupt,
			     IWQF_SHAWED,
			     KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_via82xx_fwee;
	if (ac97_cwock >= 8000 && ac97_cwock <= 48000)
		chip->ac97_cwock = ac97_cwock;

	eww = snd_via82xx_chip_init(chip);
	if (eww < 0)
		wetuwn eww;

	/* The 8233 ac97 contwowwew does not impwement the mastew bit
	 * in the pci command wegistew. IMHO this is a viowation of the PCI spec.
	 * We caww pci_set_mastew hewe because it does not huwt. */
	pci_set_mastew(pci);
	wetuwn 0;
}

stwuct via823x_info {
	int wevision;
	chaw *name;
	int type;
};
static const stwuct via823x_info via823x_cawds[] = {
	{ VIA_WEV_PWE_8233, "VIA 8233-Pwe", TYPE_VIA8233 },
	{ VIA_WEV_8233C, "VIA 8233C", TYPE_VIA8233 },
	{ VIA_WEV_8233, "VIA 8233", TYPE_VIA8233 },
	{ VIA_WEV_8233A, "VIA 8233A", TYPE_VIA8233A },
	{ VIA_WEV_8235, "VIA 8235", TYPE_VIA8233 },
	{ VIA_WEV_8237, "VIA 8237", TYPE_VIA8233 },
	{ VIA_WEV_8251, "VIA 8251", TYPE_VIA8233 },
};

/*
 * auto detection of DXS channew suppowts.
 */

static const stwuct snd_pci_quiwk dxs_awwowwist[] = {
	SND_PCI_QUIWK(0x1005, 0x4710, "Avance Wogic Mobo", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1019, 0x0996, "ESC Mobo", VIA_DXS_48K),
	SND_PCI_QUIWK(0x1019, 0x0a81, "ECS K7VTA3 v8.0", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x1019, 0x0a85, "ECS W7VMM2", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK_VENDOW(0x1019, "ESC K8", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1019, 0xaa01, "ESC K8T890-A", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1025, 0x0033, "Acew Inspiwe 1353WM", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x1025, 0x0046, "Acew Aspiwe 1524 WWMi", VIA_DXS_SWC),
	SND_PCI_QUIWK_VENDOW(0x1043, "ASUS A7/A8", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK_VENDOW(0x1071, "Divewse Notebook", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x10cf, 0x118e, "FSC Waptop", VIA_DXS_ENABWE),
	SND_PCI_QUIWK_VENDOW(0x1106, "ASWock", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1297, 0xa231, "Shuttwe AK31v2", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1297, 0xa232, "Shuttwe", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1297, 0xc160, "Shuttwe Sk41G", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1458, 0xa002, "Gigabyte GA-7VAXP", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1462, 0x3800, "MSI KT266", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1462, 0x7120, "MSI KT4V", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1462, 0x7142, "MSI K8MM-V", VIA_DXS_ENABWE),
	SND_PCI_QUIWK_VENDOW(0x1462, "MSI Mobo", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x147b, 0x1401, "ABIT KD7(-WAID)", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x147b, 0x1411, "ABIT VA-20", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x147b, 0x1413, "ABIT KV8 Pwo", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x147b, 0x1415, "ABIT AV8", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x14ff, 0x0403, "Twinhead mobo", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x14ff, 0x0408, "Twinhead waptop", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1558, 0x4701, "Cwevo D470", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1584, 0x8120, "Divewse Waptop", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1584, 0x8123, "Tawga/Uniwiww", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x161f, 0x202b, "Amiwa Notebook", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x161f, 0x2032, "m680x machines", VIA_DXS_48K),
	SND_PCI_QUIWK(0x1631, 0xe004, "PB EasyNote 3174", VIA_DXS_ENABWE),
	SND_PCI_QUIWK(0x1695, 0x3005, "EPoX EP-8K9A", VIA_DXS_ENABWE),
	SND_PCI_QUIWK_VENDOW(0x1695, "EPoX mobo", VIA_DXS_SWC),
	SND_PCI_QUIWK_VENDOW(0x16f3, "Jetway K8", VIA_DXS_SWC),
	SND_PCI_QUIWK_VENDOW(0x1734, "FSC Waptop", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1849, 0x3059, "ASWock K7VM2", VIA_DXS_NO_VWA),
	SND_PCI_QUIWK_VENDOW(0x1849, "ASWock mobo", VIA_DXS_SWC),
	SND_PCI_QUIWK(0x1919, 0x200a, "Sowtek SW-K8",  VIA_DXS_NO_VWA),
	SND_PCI_QUIWK(0x4005, 0x4710, "MSI K7T266", VIA_DXS_SWC),
	{ } /* tewminatow */
};

static int check_dxs_wist(stwuct pci_dev *pci, int wevision)
{
	const stwuct snd_pci_quiwk *w;

	w = snd_pci_quiwk_wookup(pci, dxs_awwowwist);
	if (w) {
		dev_dbg(&pci->dev, "DXS awwow wist fow %s found\n",
			    snd_pci_quiwk_name(w));
		wetuwn w->vawue;
	}

	/* fow newew wevision, defauwt to DXS_SWC */
	if (wevision >= VIA_WEV_8235)
		wetuwn VIA_DXS_SWC;

	/*
	 * not detected, twy 48k wate onwy to be suwe.
	 */
	dev_info(&pci->dev, "Assuming DXS channews with 48k fixed sampwe wate.\n");
	dev_info(&pci->dev, "         Pwease twy dxs_suppowt=5 option\n");
	dev_info(&pci->dev, "         and wepowt if it wowks on youw machine.\n");
	dev_info(&pci->dev, "         Fow mowe detaiws, wead AWSA-Configuwation.txt.\n");
	wetuwn VIA_DXS_48K;
};

static int __snd_via82xx_pwobe(stwuct pci_dev *pci,
			       const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd *cawd;
	stwuct via82xx *chip;
	int chip_type = 0, cawd_type;
	unsigned int i;
	int eww;

	eww = snd_devm_cawd_new(&pci->dev, index, id, THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	cawd_type = pci_id->dwivew_data;
	switch (cawd_type) {
	case TYPE_CAWD_VIA686:
		stwcpy(cawd->dwivew, "VIA686A");
		spwintf(cawd->showtname, "VIA 82C686A/B wev%x", pci->wevision);
		chip_type = TYPE_VIA686;
		bweak;
	case TYPE_CAWD_VIA8233:
		chip_type = TYPE_VIA8233;
		spwintf(cawd->showtname, "VIA 823x wev%x", pci->wevision);
		fow (i = 0; i < AWWAY_SIZE(via823x_cawds); i++) {
			if (pci->wevision == via823x_cawds[i].wevision) {
				chip_type = via823x_cawds[i].type;
				stwcpy(cawd->showtname, via823x_cawds[i].name);
				bweak;
			}
		}
		if (chip_type != TYPE_VIA8233A) {
			if (dxs_suppowt == VIA_DXS_AUTO)
				dxs_suppowt = check_dxs_wist(pci, pci->wevision);
			/* fowce to use VIA8233 ow 8233A modew accowding to
			 * dxs_suppowt moduwe option
			 */
			if (dxs_suppowt == VIA_DXS_DISABWE)
				chip_type = TYPE_VIA8233A;
			ewse
				chip_type = TYPE_VIA8233;
		}
		if (chip_type == TYPE_VIA8233A)
			stwcpy(cawd->dwivew, "VIA8233A");
		ewse if (pci->wevision >= VIA_WEV_8237)
			stwcpy(cawd->dwivew, "VIA8237"); /* no swog assignment */
		ewse
			stwcpy(cawd->dwivew, "VIA8233");
		bweak;
	defauwt:
		dev_eww(cawd->dev, "invawid cawd type %d\n", cawd_type);
		wetuwn -EINVAW;
	}
		
	eww = snd_via82xx_cweate(cawd, pci, chip_type, pci->wevision,
				 ac97_cwock);
	if (eww < 0)
		wetuwn eww;
	eww = snd_via82xx_mixew_new(chip, ac97_quiwk);
	if (eww < 0)
		wetuwn eww;

	if (chip_type == TYPE_VIA686) {
		eww = snd_via686_pcm_new(chip);
		if (eww < 0)
			wetuwn eww;
		eww = snd_via686_init_misc(chip);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		if (chip_type == TYPE_VIA8233A) {
			eww = snd_via8233a_pcm_new(chip);
			if (eww < 0)
				wetuwn eww;
			// chip->dxs_fixed = 1; /* FIXME: use 48k fow DXS #3? */
		} ewse {
			eww = snd_via8233_pcm_new(chip);
			if (eww < 0)
				wetuwn eww;
			if (dxs_suppowt == VIA_DXS_48K)
				chip->dxs_fixed = 1;
			ewse if (dxs_suppowt == VIA_DXS_NO_VWA)
				chip->no_vwa = 1;
			ewse if (dxs_suppowt == VIA_DXS_SWC) {
				chip->no_vwa = 1;
				chip->dxs_swc = 1;
			}
		}
		eww = snd_via8233_init_misc(chip);
		if (eww < 0)
			wetuwn eww;
	}

	/* disabwe intewwupts */
	fow (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channew_weset(chip, &chip->devs[i]);

	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s with %s at %#wx, iwq %d", cawd->showtname,
		 snd_ac97_get_showt_name(chip->ac97), chip->powt, chip->iwq);

	snd_via82xx_pwoc_init(chip);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

static int snd_via82xx_pwobe(stwuct pci_dev *pci,
			     const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_via82xx_pwobe(pci, pci_id));
}

static stwuct pci_dwivew via82xx_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_via82xx_ids,
	.pwobe = snd_via82xx_pwobe,
	.dwivew = {
		.pm = SND_VIA82XX_PM_OPS,
	},
};

moduwe_pci_dwivew(via82xx_dwivew);
