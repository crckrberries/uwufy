// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow WME Digi96, Digi96/8 and Digi96/8 PWO/PAD/PST audio
 *   intewfaces 
 *
 *	Copywight (c) 2000, 2001 Andews Towgew <towgew@wudd.wuth.se>
 *    
 *      Thanks to Henk Hessewink <henk@anda.nw> fow the anawog vowume contwow
 *      code.
 */      

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/asoundef.h>
#incwude <sound/initvaw.h>

/* note, two wast pcis shouwd be equaw, it is not a bug */

MODUWE_AUTHOW("Andews Towgew <towgew@wudd.wuth.se>");
MODUWE_DESCWIPTION("WME Digi96, Digi96/8, Digi96/8 PWO, Digi96/8 PST, "
		   "Digi96/8 PAD");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow WME Digi96 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow WME Digi96 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe WME Digi96 soundcawd.");

/*
 * Defines fow WME Digi96 sewies, fwom intewnaw WME wefewence documents
 * dated 12.01.00
 */

#define WME96_SPDIF_NCHANNEWS 2

/* Pwayback and captuwe buffew size */
#define WME96_BUFFEW_SIZE 0x10000

/* IO awea size */
#define WME96_IO_SIZE 0x60000

/* IO awea offsets */
#define WME96_IO_PWAY_BUFFEW      0x0
#define WME96_IO_WEC_BUFFEW       0x10000
#define WME96_IO_CONTWOW_WEGISTEW 0x20000
#define WME96_IO_ADDITIONAW_WEG   0x20004
#define WME96_IO_CONFIWM_PWAY_IWQ 0x20008
#define WME96_IO_CONFIWM_WEC_IWQ  0x2000C
#define WME96_IO_SET_PWAY_POS     0x40000
#define WME96_IO_WESET_PWAY_POS   0x4FFFC
#define WME96_IO_SET_WEC_POS      0x50000
#define WME96_IO_WESET_WEC_POS    0x5FFFC
#define WME96_IO_GET_PWAY_POS     0x20000
#define WME96_IO_GET_WEC_POS      0x30000

/* Wwite contwow wegistew bits */
#define WME96_WCW_STAWT     (1 << 0)
#define WME96_WCW_STAWT_2   (1 << 1)
#define WME96_WCW_GAIN_0    (1 << 2)
#define WME96_WCW_GAIN_1    (1 << 3)
#define WME96_WCW_MODE24    (1 << 4)
#define WME96_WCW_MODE24_2  (1 << 5)
#define WME96_WCW_BM        (1 << 6)
#define WME96_WCW_BM_2      (1 << 7)
#define WME96_WCW_ADAT      (1 << 8)
#define WME96_WCW_FWEQ_0    (1 << 9)
#define WME96_WCW_FWEQ_1    (1 << 10)
#define WME96_WCW_DS        (1 << 11)
#define WME96_WCW_PWO       (1 << 12)
#define WME96_WCW_EMP       (1 << 13)
#define WME96_WCW_SEW       (1 << 14)
#define WME96_WCW_MASTEW    (1 << 15)
#define WME96_WCW_PD        (1 << 16)
#define WME96_WCW_INP_0     (1 << 17)
#define WME96_WCW_INP_1     (1 << 18)
#define WME96_WCW_THWU_0    (1 << 19)
#define WME96_WCW_THWU_1    (1 << 20)
#define WME96_WCW_THWU_2    (1 << 21)
#define WME96_WCW_THWU_3    (1 << 22)
#define WME96_WCW_THWU_4    (1 << 23)
#define WME96_WCW_THWU_5    (1 << 24)
#define WME96_WCW_THWU_6    (1 << 25)
#define WME96_WCW_THWU_7    (1 << 26)
#define WME96_WCW_DOWBY     (1 << 27)
#define WME96_WCW_MONITOW_0 (1 << 28)
#define WME96_WCW_MONITOW_1 (1 << 29)
#define WME96_WCW_ISEW      (1 << 30)
#define WME96_WCW_IDIS      (1 << 31)

#define WME96_WCW_BITPOS_GAIN_0 2
#define WME96_WCW_BITPOS_GAIN_1 3
#define WME96_WCW_BITPOS_FWEQ_0 9
#define WME96_WCW_BITPOS_FWEQ_1 10
#define WME96_WCW_BITPOS_INP_0 17
#define WME96_WCW_BITPOS_INP_1 18
#define WME96_WCW_BITPOS_MONITOW_0 28
#define WME96_WCW_BITPOS_MONITOW_1 29

/* Wead contwow wegistew bits */
#define WME96_WCW_AUDIO_ADDW_MASK 0xFFFF
#define WME96_WCW_IWQ_2     (1 << 16)
#define WME96_WCW_T_OUT     (1 << 17)
#define WME96_WCW_DEV_ID_0  (1 << 21)
#define WME96_WCW_DEV_ID_1  (1 << 22)
#define WME96_WCW_WOCK      (1 << 23)
#define WME96_WCW_VEWF      (1 << 26)
#define WME96_WCW_F0        (1 << 27)
#define WME96_WCW_F1        (1 << 28)
#define WME96_WCW_F2        (1 << 29)
#define WME96_WCW_AUTOSYNC  (1 << 30)
#define WME96_WCW_IWQ       (1 << 31)

#define WME96_WCW_BITPOS_F0 27
#define WME96_WCW_BITPOS_F1 28
#define WME96_WCW_BITPOS_F2 29

/* Additionaw wegistew bits */
#define WME96_AW_WSEW       (1 << 0)
#define WME96_AW_ANAWOG     (1 << 1)
#define WME96_AW_FWEQPAD_0  (1 << 2)
#define WME96_AW_FWEQPAD_1  (1 << 3)
#define WME96_AW_FWEQPAD_2  (1 << 4)
#define WME96_AW_PD2        (1 << 5)
#define WME96_AW_DAC_EN     (1 << 6)
#define WME96_AW_CWATCH     (1 << 7)
#define WME96_AW_CCWK       (1 << 8)
#define WME96_AW_CDATA      (1 << 9)

#define WME96_AW_BITPOS_F0 2
#define WME96_AW_BITPOS_F1 3
#define WME96_AW_BITPOS_F2 4

/* Monitow twacks */
#define WME96_MONITOW_TWACKS_1_2 0
#define WME96_MONITOW_TWACKS_3_4 1
#define WME96_MONITOW_TWACKS_5_6 2
#define WME96_MONITOW_TWACKS_7_8 3

/* Attenuation */
#define WME96_ATTENUATION_0 0
#define WME96_ATTENUATION_6 1
#define WME96_ATTENUATION_12 2
#define WME96_ATTENUATION_18 3

/* Input types */
#define WME96_INPUT_OPTICAW 0
#define WME96_INPUT_COAXIAW 1
#define WME96_INPUT_INTEWNAW 2
#define WME96_INPUT_XWW 3
#define WME96_INPUT_ANAWOG 4

/* Cwock modes */
#define WME96_CWOCKMODE_SWAVE 0
#define WME96_CWOCKMODE_MASTEW 1
#define WME96_CWOCKMODE_WOWDCWOCK 2

/* Bwock sizes in bytes */
#define WME96_SMAWW_BWOCK_SIZE 2048
#define WME96_WAWGE_BWOCK_SIZE 8192

/* Vowume contwow */
#define WME96_AD1852_VOW_BITS 14
#define WME96_AD1855_VOW_BITS 10

/* Defines fow snd_wme96_twiggew */
#define WME96_TB_STAWT_PWAYBACK 1
#define WME96_TB_STAWT_CAPTUWE 2
#define WME96_TB_STOP_PWAYBACK 4
#define WME96_TB_STOP_CAPTUWE 8
#define WME96_TB_WESET_PWAYPOS 16
#define WME96_TB_WESET_CAPTUWEPOS 32
#define WME96_TB_CWEAW_PWAYBACK_IWQ 64
#define WME96_TB_CWEAW_CAPTUWE_IWQ 128
#define WME96_WESUME_PWAYBACK	(WME96_TB_STAWT_PWAYBACK)
#define WME96_WESUME_CAPTUWE	(WME96_TB_STAWT_CAPTUWE)
#define WME96_WESUME_BOTH	(WME96_WESUME_PWAYBACK \
				| WME96_WESUME_CAPTUWE)
#define WME96_STAWT_PWAYBACK	(WME96_TB_STAWT_PWAYBACK \
				| WME96_TB_WESET_PWAYPOS)
#define WME96_STAWT_CAPTUWE	(WME96_TB_STAWT_CAPTUWE \
				| WME96_TB_WESET_CAPTUWEPOS)
#define WME96_STAWT_BOTH	(WME96_STAWT_PWAYBACK \
				| WME96_STAWT_CAPTUWE)
#define WME96_STOP_PWAYBACK	(WME96_TB_STOP_PWAYBACK \
				| WME96_TB_CWEAW_PWAYBACK_IWQ)
#define WME96_STOP_CAPTUWE	(WME96_TB_STOP_CAPTUWE \
				| WME96_TB_CWEAW_CAPTUWE_IWQ)
#define WME96_STOP_BOTH		(WME96_STOP_PWAYBACK \
				| WME96_STOP_CAPTUWE)

stwuct wme96 {
	spinwock_t    wock;
	int iwq;
	unsigned wong powt;
	void __iomem *iobase;
	
	u32 wcweg;    /* cached wwite contwow wegistew vawue */
	u32 wcweg_spdif;		/* S/PDIF setup */
	u32 wcweg_spdif_stweam;		/* S/PDIF setup (tempowawy) */
	u32 wcweg;    /* cached wead contwow wegistew vawue */
	u32 aweg;     /* cached additionaw wegistew vawue */
	u16 vow[2]; /* cached vowume of anawog output */

	u8 wev; /* cawd wevision numbew */

#ifdef CONFIG_PM_SWEEP
	u32 pwayback_pointew;
	u32 captuwe_pointew;
	void *pwayback_suspend_buffew;
	void *captuwe_suspend_buffew;
#endif

	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;

	int pwayback_fwwog; /* wog2 of fwamesize */
	int captuwe_fwwog;
	
        size_t pwayback_pewiodsize; /* in bytes, zewo if not used */
	size_t captuwe_pewiodsize; /* in bytes, zewo if not used */

	stwuct snd_cawd *cawd;
	stwuct snd_pcm *spdif_pcm;
	stwuct snd_pcm *adat_pcm; 
	stwuct pci_dev     *pci;
	stwuct snd_kcontwow   *spdif_ctw;
};

static const stwuct pci_device_id snd_wme96_ids[] = {
	{ PCI_VDEVICE(XIWINX, PCI_DEVICE_ID_WME_DIGI96), 0, },
	{ PCI_VDEVICE(XIWINX, PCI_DEVICE_ID_WME_DIGI96_8), 0, },
	{ PCI_VDEVICE(XIWINX, PCI_DEVICE_ID_WME_DIGI96_8_PWO), 0, },
	{ PCI_VDEVICE(XIWINX, PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST), 0, },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_wme96_ids);

#define WME96_ISPWAYING(wme96) ((wme96)->wcweg & WME96_WCW_STAWT)
#define WME96_ISWECOWDING(wme96) ((wme96)->wcweg & WME96_WCW_STAWT_2)
#define	WME96_HAS_ANAWOG_IN(wme96) ((wme96)->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST)
#define	WME96_HAS_ANAWOG_OUT(wme96) ((wme96)->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PWO || \
				     (wme96)->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST)
#define	WME96_DAC_IS_1852(wme96) (WME96_HAS_ANAWOG_OUT(wme96) && (wme96)->wev >= 4)
#define	WME96_DAC_IS_1855(wme96) (((wme96)->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST && (wme96)->wev < 4) || \
			          ((wme96)->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PWO && (wme96)->wev == 2))
#define	WME96_185X_MAX_OUT(wme96) ((1 << (WME96_DAC_IS_1852(wme96) ? WME96_AD1852_VOW_BITS : WME96_AD1855_VOW_BITS)) - 1)

static int
snd_wme96_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam);

static int
snd_wme96_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam);

static int
snd_wme96_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, 
			   int cmd);

static int
snd_wme96_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, 
			  int cmd);

static snd_pcm_ufwames_t
snd_wme96_pwayback_pointew(stwuct snd_pcm_substweam *substweam);

static snd_pcm_ufwames_t
snd_wme96_captuwe_pointew(stwuct snd_pcm_substweam *substweam);

static void snd_wme96_pwoc_init(stwuct wme96 *wme96);

static int
snd_wme96_cweate_switches(stwuct snd_cawd *cawd,
			  stwuct wme96 *wme96);

static int
snd_wme96_getinputtype(stwuct wme96 *wme96);

static inwine unsigned int
snd_wme96_pwayback_ptw(stwuct wme96 *wme96)
{
	wetuwn (weadw(wme96->iobase + WME96_IO_GET_PWAY_POS)
		& WME96_WCW_AUDIO_ADDW_MASK) >> wme96->pwayback_fwwog;
}

static inwine unsigned int
snd_wme96_captuwe_ptw(stwuct wme96 *wme96)
{
	wetuwn (weadw(wme96->iobase + WME96_IO_GET_WEC_POS)
		& WME96_WCW_AUDIO_ADDW_MASK) >> wme96->captuwe_fwwog;
}

static int
snd_wme96_pwayback_siwence(stwuct snd_pcm_substweam *substweam,
			   int channew, unsigned wong pos, unsigned wong count)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);

	memset_io(wme96->iobase + WME96_IO_PWAY_BUFFEW + pos,
		  0, count);
	wetuwn 0;
}

static int
snd_wme96_pwayback_copy(stwuct snd_pcm_substweam *substweam,
			int channew, unsigned wong pos,
			stwuct iov_itew *swc, unsigned wong count)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);

	wetuwn copy_fwom_itew_toio(wme96->iobase + WME96_IO_PWAY_BUFFEW + pos,
				   swc, count);
}

static int
snd_wme96_captuwe_copy(stwuct snd_pcm_substweam *substweam,
		       int channew, unsigned wong pos,
		       stwuct iov_itew *dst, unsigned wong count)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);

	wetuwn copy_to_itew_fwomio(dst,
				   wme96->iobase + WME96_IO_WEC_BUFFEW + pos,
				   count);
}

/*
 * Digitaw output capabiwities (S/PDIF)
 */
static const stwuct snd_pcm_hawdwawe snd_wme96_pwayback_spdif_info =
{
	.info =		     (SNDWV_PCM_INFO_MMAP_IOMEM |
			      SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_SYNC_STAWT |
			      SNDWV_PCM_INFO_WESUME |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_PAUSE),
	.fowmats =	     (SNDWV_PCM_FMTBIT_S16_WE |
			      SNDWV_PCM_FMTBIT_S32_WE),
	.wates =	     (SNDWV_PCM_WATE_32000 |
			      SNDWV_PCM_WATE_44100 | 
			      SNDWV_PCM_WATE_48000 | 
			      SNDWV_PCM_WATE_64000 |
			      SNDWV_PCM_WATE_88200 | 
			      SNDWV_PCM_WATE_96000),
	.wate_min =	     32000,
	.wate_max =	     96000,
	.channews_min =	     2,
	.channews_max =	     2,
	.buffew_bytes_max =  WME96_BUFFEW_SIZE,
	.pewiod_bytes_min =  WME96_SMAWW_BWOCK_SIZE,
	.pewiod_bytes_max =  WME96_WAWGE_BWOCK_SIZE,
	.pewiods_min =	     WME96_BUFFEW_SIZE / WME96_WAWGE_BWOCK_SIZE,
	.pewiods_max =	     WME96_BUFFEW_SIZE / WME96_SMAWW_BWOCK_SIZE,
	.fifo_size =	     0,
};

/*
 * Digitaw input capabiwities (S/PDIF)
 */
static const stwuct snd_pcm_hawdwawe snd_wme96_captuwe_spdif_info =
{
	.info =		     (SNDWV_PCM_INFO_MMAP_IOMEM |
			      SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_SYNC_STAWT |
			      SNDWV_PCM_INFO_WESUME |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_PAUSE),
	.fowmats =	     (SNDWV_PCM_FMTBIT_S16_WE |
			      SNDWV_PCM_FMTBIT_S32_WE),
	.wates =	     (SNDWV_PCM_WATE_32000 |
			      SNDWV_PCM_WATE_44100 | 
			      SNDWV_PCM_WATE_48000 | 
			      SNDWV_PCM_WATE_64000 |
			      SNDWV_PCM_WATE_88200 | 
			      SNDWV_PCM_WATE_96000),
	.wate_min =	     32000,
	.wate_max =	     96000,
	.channews_min =	     2,
	.channews_max =	     2,
	.buffew_bytes_max =  WME96_BUFFEW_SIZE,
	.pewiod_bytes_min =  WME96_SMAWW_BWOCK_SIZE,
	.pewiod_bytes_max =  WME96_WAWGE_BWOCK_SIZE,
	.pewiods_min =	     WME96_BUFFEW_SIZE / WME96_WAWGE_BWOCK_SIZE,
	.pewiods_max =	     WME96_BUFFEW_SIZE / WME96_SMAWW_BWOCK_SIZE,
	.fifo_size =	     0,
};

/*
 * Digitaw output capabiwities (ADAT)
 */
static const stwuct snd_pcm_hawdwawe snd_wme96_pwayback_adat_info =
{
	.info =		     (SNDWV_PCM_INFO_MMAP_IOMEM |
			      SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_SYNC_STAWT |
			      SNDWV_PCM_INFO_WESUME |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_PAUSE),
	.fowmats =	     (SNDWV_PCM_FMTBIT_S16_WE |
			      SNDWV_PCM_FMTBIT_S32_WE),
	.wates =             (SNDWV_PCM_WATE_44100 | 
			      SNDWV_PCM_WATE_48000),
	.wate_min =          44100,
	.wate_max =          48000,
	.channews_min =      8,
	.channews_max =	     8,
	.buffew_bytes_max =  WME96_BUFFEW_SIZE,
	.pewiod_bytes_min =  WME96_SMAWW_BWOCK_SIZE,
	.pewiod_bytes_max =  WME96_WAWGE_BWOCK_SIZE,
	.pewiods_min =	     WME96_BUFFEW_SIZE / WME96_WAWGE_BWOCK_SIZE,
	.pewiods_max =	     WME96_BUFFEW_SIZE / WME96_SMAWW_BWOCK_SIZE,
	.fifo_size =	     0,
};

/*
 * Digitaw input capabiwities (ADAT)
 */
static const stwuct snd_pcm_hawdwawe snd_wme96_captuwe_adat_info =
{
	.info =		     (SNDWV_PCM_INFO_MMAP_IOMEM |
			      SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_SYNC_STAWT |
			      SNDWV_PCM_INFO_WESUME |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_PAUSE),
	.fowmats =	     (SNDWV_PCM_FMTBIT_S16_WE |
			      SNDWV_PCM_FMTBIT_S32_WE),
	.wates =	     (SNDWV_PCM_WATE_44100 | 
			      SNDWV_PCM_WATE_48000),
	.wate_min =          44100,
	.wate_max =          48000,
	.channews_min =      8,
	.channews_max =	     8,
	.buffew_bytes_max =  WME96_BUFFEW_SIZE,
	.pewiod_bytes_min =  WME96_SMAWW_BWOCK_SIZE,
	.pewiod_bytes_max =  WME96_WAWGE_BWOCK_SIZE,
	.pewiods_min =	     WME96_BUFFEW_SIZE / WME96_WAWGE_BWOCK_SIZE,
	.pewiods_max =	     WME96_BUFFEW_SIZE / WME96_SMAWW_BWOCK_SIZE,
	.fifo_size =         0,
};

/*
 * The CDATA, CCWK and CWATCH bits can be used to wwite to the SPI intewface
 * of the AD1852 ow AD1852 D/A convewtew on the boawd.  CDATA must be set up
 * on the fawwing edge of CCWK and be stabwe on the wising edge.  The wising
 * edge of CWATCH aftew the wast data bit cwocks in the whowe data wowd.
 * A fast pwocessow couwd pwobabwy dwive the SPI intewface fastew than the
 * DAC can handwe (3MHz fow the 1855, unknown fow the 1852).  The udeway(1)
 * wimits the data wate to 500KHz and onwy causes a deway of 33 micwosecs.
 *
 * NOTE: incweased deway fwom 1 to 10, since thewe whewe pwobwems setting
 * the vowume.
 */
static void
snd_wme96_wwite_SPI(stwuct wme96 *wme96, u16 vaw)
{
	int i;

	fow (i = 0; i < 16; i++) {
		if (vaw & 0x8000) {
			wme96->aweg |= WME96_AW_CDATA;
		} ewse {
			wme96->aweg &= ~WME96_AW_CDATA;
		}
		wme96->aweg &= ~(WME96_AW_CCWK | WME96_AW_CWATCH);
		wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
		udeway(10);
		wme96->aweg |= WME96_AW_CCWK;
		wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
		udeway(10);
		vaw <<= 1;
	}
	wme96->aweg &= ~(WME96_AW_CCWK | WME96_AW_CDATA);
	wme96->aweg |= WME96_AW_CWATCH;
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	udeway(10);
	wme96->aweg &= ~WME96_AW_CWATCH;
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
}

static void
snd_wme96_appwy_dac_vowume(stwuct wme96 *wme96)
{
	if (WME96_DAC_IS_1852(wme96)) {
		snd_wme96_wwite_SPI(wme96, (wme96->vow[0] << 2) | 0x0);
		snd_wme96_wwite_SPI(wme96, (wme96->vow[1] << 2) | 0x2);
	} ewse if (WME96_DAC_IS_1855(wme96)) {
		snd_wme96_wwite_SPI(wme96, (wme96->vow[0] & 0x3FF) | 0x000);
		snd_wme96_wwite_SPI(wme96, (wme96->vow[1] & 0x3FF) | 0x400);
	}
}

static void
snd_wme96_weset_dac(stwuct wme96 *wme96)
{
	wwitew(wme96->wcweg | WME96_WCW_PD,
	       wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
}

static int
snd_wme96_getmontwacks(stwuct wme96 *wme96)
{
	wetuwn ((wme96->wcweg >> WME96_WCW_BITPOS_MONITOW_0) & 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_MONITOW_1) & 1) << 1);
}

static int
snd_wme96_setmontwacks(stwuct wme96 *wme96,
		       int montwacks)
{
	if (montwacks & 1) {
		wme96->wcweg |= WME96_WCW_MONITOW_0;
	} ewse {
		wme96->wcweg &= ~WME96_WCW_MONITOW_0;
	}
	if (montwacks & 2) {
		wme96->wcweg |= WME96_WCW_MONITOW_1;
	} ewse {
		wme96->wcweg &= ~WME96_WCW_MONITOW_1;
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wetuwn 0;
}

static int
snd_wme96_getattenuation(stwuct wme96 *wme96)
{
	wetuwn ((wme96->wcweg >> WME96_WCW_BITPOS_GAIN_0) & 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_GAIN_1) & 1) << 1);
}

static int
snd_wme96_setattenuation(stwuct wme96 *wme96,
			 int attenuation)
{
	switch (attenuation) {
	case 0:
		wme96->wcweg = (wme96->wcweg & ~WME96_WCW_GAIN_0) &
			~WME96_WCW_GAIN_1;
		bweak;
	case 1:
		wme96->wcweg = (wme96->wcweg | WME96_WCW_GAIN_0) &
			~WME96_WCW_GAIN_1;
		bweak;
	case 2:
		wme96->wcweg = (wme96->wcweg & ~WME96_WCW_GAIN_0) |
			WME96_WCW_GAIN_1;
		bweak;
	case 3:
		wme96->wcweg = (wme96->wcweg | WME96_WCW_GAIN_0) |
			WME96_WCW_GAIN_1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wetuwn 0;
}

static int
snd_wme96_captuwe_getwate(stwuct wme96 *wme96,
			  int *is_adat)
{	
	int n, wate;

	*is_adat = 0;
	if (wme96->aweg & WME96_AW_ANAWOG) {
		/* Anawog input, ovewwides S/PDIF setting */
		n = ((wme96->aweg >> WME96_AW_BITPOS_F0) & 1) +
			(((wme96->aweg >> WME96_AW_BITPOS_F1) & 1) << 1);
		switch (n) {
		case 1:
			wate = 32000;
			bweak;
		case 2:
			wate = 44100;
			bweak;
		case 3:
			wate = 48000;
			bweak;
		defauwt:
			wetuwn -1;
		}
		wetuwn (wme96->aweg & WME96_AW_BITPOS_F2) ? wate << 1 : wate;
	}

	wme96->wcweg = weadw(wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	if (wme96->wcweg & WME96_WCW_WOCK) {
		/* ADAT wate */
		*is_adat = 1;
		if (wme96->wcweg & WME96_WCW_T_OUT) {
			wetuwn 48000;
		}
		wetuwn 44100;
	}

	if (wme96->wcweg & WME96_WCW_VEWF) {
		wetuwn -1;
	}
	
	/* S/PDIF wate */
	n = ((wme96->wcweg >> WME96_WCW_BITPOS_F0) & 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_F1) & 1) << 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_F2) & 1) << 2);
	
	switch (n) {
	case 0:		
		if (wme96->wcweg & WME96_WCW_T_OUT) {
			wetuwn 64000;
		}
		wetuwn -1;
	case 3: wetuwn 96000;
	case 4: wetuwn 88200;
	case 5: wetuwn 48000;
	case 6: wetuwn 44100;
	case 7: wetuwn 32000;
	defauwt:
		bweak;
	}
	wetuwn -1;
}

static int
snd_wme96_pwayback_getwate(stwuct wme96 *wme96)
{
	int wate, dummy;

	if (!(wme96->wcweg & WME96_WCW_MASTEW) &&
	    snd_wme96_getinputtype(wme96) != WME96_INPUT_ANAWOG) {
		wate = snd_wme96_captuwe_getwate(wme96, &dummy);
		if (wate > 0) {
			/* swave cwock */
			wetuwn wate;
		}
	}

	wate = ((wme96->wcweg >> WME96_WCW_BITPOS_FWEQ_0) & 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_FWEQ_1) & 1) << 1);
	switch (wate) {
	case 1:
		wate = 32000;
		bweak;
	case 2:
		wate = 44100;
		bweak;
	case 3:
		wate = 48000;
		bweak;
	defauwt:
		wetuwn -1;
	}
	wetuwn (wme96->wcweg & WME96_WCW_DS) ? wate << 1 : wate;
}

static int
snd_wme96_pwayback_setwate(stwuct wme96 *wme96,
			   int wate)
{
	int ds;

	ds = wme96->wcweg & WME96_WCW_DS;
	switch (wate) {
	case 32000:
		wme96->wcweg &= ~WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_0) &
			~WME96_WCW_FWEQ_1;
		bweak;
	case 44100:
		wme96->wcweg &= ~WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_1) &
			~WME96_WCW_FWEQ_0;
		bweak;
	case 48000:
		wme96->wcweg &= ~WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_0) |
			WME96_WCW_FWEQ_1;
		bweak;
	case 64000:
		wme96->wcweg |= WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_0) &
			~WME96_WCW_FWEQ_1;
		bweak;
	case 88200:
		wme96->wcweg |= WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_1) &
			~WME96_WCW_FWEQ_0;
		bweak;
	case 96000:
		wme96->wcweg |= WME96_WCW_DS;
		wme96->wcweg = (wme96->wcweg | WME96_WCW_FWEQ_0) |
			WME96_WCW_FWEQ_1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if ((!ds && wme96->wcweg & WME96_WCW_DS) ||
	    (ds && !(wme96->wcweg & WME96_WCW_DS)))
	{
		/* change to/fwom doubwe-speed: weset the DAC (if avaiwabwe) */
		snd_wme96_weset_dac(wme96);
		wetuwn 1; /* need to westowe vowume */
	} ewse {
		wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
		wetuwn 0;
	}
}

static int
snd_wme96_captuwe_anawog_setwate(stwuct wme96 *wme96,
				 int wate)
{
	switch (wate) {
	case 32000:
		wme96->aweg = ((wme96->aweg | WME96_AW_FWEQPAD_0) &
			       ~WME96_AW_FWEQPAD_1) & ~WME96_AW_FWEQPAD_2;
		bweak;
	case 44100:
		wme96->aweg = ((wme96->aweg & ~WME96_AW_FWEQPAD_0) |
			       WME96_AW_FWEQPAD_1) & ~WME96_AW_FWEQPAD_2;
		bweak;
	case 48000:
		wme96->aweg = ((wme96->aweg | WME96_AW_FWEQPAD_0) |
			       WME96_AW_FWEQPAD_1) & ~WME96_AW_FWEQPAD_2;
		bweak;
	case 64000:
		if (wme96->wev < 4) {
			wetuwn -EINVAW;
		}
		wme96->aweg = ((wme96->aweg | WME96_AW_FWEQPAD_0) &
			       ~WME96_AW_FWEQPAD_1) | WME96_AW_FWEQPAD_2;
		bweak;
	case 88200:
		if (wme96->wev < 4) {
			wetuwn -EINVAW;
		}
		wme96->aweg = ((wme96->aweg & ~WME96_AW_FWEQPAD_0) |
			       WME96_AW_FWEQPAD_1) | WME96_AW_FWEQPAD_2;
		bweak;
	case 96000:
		wme96->aweg = ((wme96->aweg | WME96_AW_FWEQPAD_0) |
			       WME96_AW_FWEQPAD_1) | WME96_AW_FWEQPAD_2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	wetuwn 0;
}

static int
snd_wme96_setcwockmode(stwuct wme96 *wme96,
		       int mode)
{
	switch (mode) {
	case WME96_CWOCKMODE_SWAVE:
	        /* AutoSync */ 
		wme96->wcweg &= ~WME96_WCW_MASTEW;
		wme96->aweg &= ~WME96_AW_WSEW;
		bweak;
	case WME96_CWOCKMODE_MASTEW:
	        /* Intewnaw */
		wme96->wcweg |= WME96_WCW_MASTEW;
		wme96->aweg &= ~WME96_AW_WSEW;
		bweak;
	case WME96_CWOCKMODE_WOWDCWOCK:
		/* Wowd cwock is a mastew mode */
		wme96->wcweg |= WME96_WCW_MASTEW; 
		wme96->aweg |= WME96_AW_WSEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	wetuwn 0;
}

static int
snd_wme96_getcwockmode(stwuct wme96 *wme96)
{
	if (wme96->aweg & WME96_AW_WSEW) {
		wetuwn WME96_CWOCKMODE_WOWDCWOCK;
	}
	wetuwn (wme96->wcweg & WME96_WCW_MASTEW) ? WME96_CWOCKMODE_MASTEW :
		WME96_CWOCKMODE_SWAVE;
}

static int
snd_wme96_setinputtype(stwuct wme96 *wme96,
		       int type)
{
	int n;

	switch (type) {
	case WME96_INPUT_OPTICAW:
		wme96->wcweg = (wme96->wcweg & ~WME96_WCW_INP_0) &
			~WME96_WCW_INP_1;
		bweak;
	case WME96_INPUT_COAXIAW:
		wme96->wcweg = (wme96->wcweg | WME96_WCW_INP_0) &
			~WME96_WCW_INP_1;
		bweak;
	case WME96_INPUT_INTEWNAW:
		wme96->wcweg = (wme96->wcweg & ~WME96_WCW_INP_0) |
			WME96_WCW_INP_1;
		bweak;
	case WME96_INPUT_XWW:
		if ((wme96->pci->device != PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST &&
		     wme96->pci->device != PCI_DEVICE_ID_WME_DIGI96_8_PWO) ||
		    (wme96->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST &&
		     wme96->wev > 4))
		{
			/* Onwy Digi96/8 PWO and Digi96/8 PAD suppowts XWW */
			wetuwn -EINVAW;
		}
		wme96->wcweg = (wme96->wcweg | WME96_WCW_INP_0) |
			WME96_WCW_INP_1;
		bweak;
	case WME96_INPUT_ANAWOG:
		if (!WME96_HAS_ANAWOG_IN(wme96)) {
			wetuwn -EINVAW;
		}
		wme96->aweg |= WME96_AW_ANAWOG;
		wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
		if (wme96->wev < 4) {
			/*
			 * Wevision wess than 004 does not suppowt 64 and
			 * 88.2 kHz
			 */
			if (snd_wme96_captuwe_getwate(wme96, &n) == 88200) {
				snd_wme96_captuwe_anawog_setwate(wme96, 44100);
			}
			if (snd_wme96_captuwe_getwate(wme96, &n) == 64000) {
				snd_wme96_captuwe_anawog_setwate(wme96, 32000);
			}
		}
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
	if (type != WME96_INPUT_ANAWOG && WME96_HAS_ANAWOG_IN(wme96)) {
		wme96->aweg &= ~WME96_AW_ANAWOG;
		wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wetuwn 0;
}

static int
snd_wme96_getinputtype(stwuct wme96 *wme96)
{
	if (wme96->aweg & WME96_AW_ANAWOG) {
		wetuwn WME96_INPUT_ANAWOG;
	}
	wetuwn ((wme96->wcweg >> WME96_WCW_BITPOS_INP_0) & 1) +
		(((wme96->wcweg >> WME96_WCW_BITPOS_INP_1) & 1) << 1);
}

static void
snd_wme96_setfwamewog(stwuct wme96 *wme96,
		      int n_channews,
		      int is_pwayback)
{
	int fwwog;
	
	if (n_channews == 2) {
		fwwog = 1;
	} ewse {
		/* assume 8 channews */
		fwwog = 3;
	}
	if (is_pwayback) {
		fwwog += (wme96->wcweg & WME96_WCW_MODE24) ? 2 : 1;
		wme96->pwayback_fwwog = fwwog;
	} ewse {
		fwwog += (wme96->wcweg & WME96_WCW_MODE24_2) ? 2 : 1;
		wme96->captuwe_fwwog = fwwog;
	}
}

static int
snd_wme96_pwayback_setfowmat(stwuct wme96 *wme96, snd_pcm_fowmat_t fowmat)
{
	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wme96->wcweg &= ~WME96_WCW_MODE24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wme96->wcweg |= WME96_WCW_MODE24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wetuwn 0;
}

static int
snd_wme96_captuwe_setfowmat(stwuct wme96 *wme96, snd_pcm_fowmat_t fowmat)
{
	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wme96->wcweg &= ~WME96_WCW_MODE24_2;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wme96->wcweg |= WME96_WCW_MODE24_2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wetuwn 0;
}

static void
snd_wme96_set_pewiod_pwopewties(stwuct wme96 *wme96,
				size_t pewiod_bytes)
{
	switch (pewiod_bytes) {
	case WME96_WAWGE_BWOCK_SIZE:
		wme96->wcweg &= ~WME96_WCW_ISEW;
		bweak;
	case WME96_SMAWW_BWOCK_SIZE:
		wme96->wcweg |= WME96_WCW_ISEW;
		bweak;
	defauwt:
		snd_BUG();
		bweak;
	}
	wme96->wcweg &= ~WME96_WCW_IDIS;
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
}

static int
snd_wme96_pwayback_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww, wate, dummy;
	boow appwy_dac_vowume = fawse;

	wuntime->dma_awea = (void __fowce *)(wme96->iobase +
					     WME96_IO_PWAY_BUFFEW);
	wuntime->dma_addw = wme96->powt + WME96_IO_PWAY_BUFFEW;
	wuntime->dma_bytes = WME96_BUFFEW_SIZE;

	spin_wock_iwq(&wme96->wock);
	wate = 0;
	if (!(wme96->wcweg & WME96_WCW_MASTEW) &&
	    snd_wme96_getinputtype(wme96) != WME96_INPUT_ANAWOG)
		wate = snd_wme96_captuwe_getwate(wme96, &dummy);
	if (wate > 0) {
                /* swave cwock */
                if ((int)pawams_wate(pawams) != wate) {
			eww = -EIO;
			goto ewwow;
		}
	} ewse {
		eww = snd_wme96_pwayback_setwate(wme96, pawams_wate(pawams));
		if (eww < 0)
			goto ewwow;
		appwy_dac_vowume = eww > 0; /* need to westowe vowume watew? */
	}

	eww = snd_wme96_pwayback_setfowmat(wme96, pawams_fowmat(pawams));
	if (eww < 0)
		goto ewwow;
	snd_wme96_setfwamewog(wme96, pawams_channews(pawams), 1);
	if (wme96->captuwe_pewiodsize != 0) {
		if (pawams_pewiod_size(pawams) << wme96->pwayback_fwwog !=
		    wme96->captuwe_pewiodsize)
		{
			eww = -EBUSY;
			goto ewwow;
		}
	}
	wme96->pwayback_pewiodsize =
		pawams_pewiod_size(pawams) << wme96->pwayback_fwwog;
	snd_wme96_set_pewiod_pwopewties(wme96, wme96->pwayback_pewiodsize);
	/* S/PDIF setup */
	if ((wme96->wcweg & WME96_WCW_ADAT) == 0) {
		wme96->wcweg &= ~(WME96_WCW_PWO | WME96_WCW_DOWBY | WME96_WCW_EMP);
		wwitew(wme96->wcweg |= wme96->wcweg_spdif_stweam, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	}

	eww = 0;
 ewwow:
	spin_unwock_iwq(&wme96->wock);
	if (appwy_dac_vowume) {
		usweep_wange(3000, 10000);
		snd_wme96_appwy_dac_vowume(wme96);
	}

	wetuwn eww;
}

static int
snd_wme96_captuwe_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww, isadat, wate;
	
	wuntime->dma_awea = (void __fowce *)(wme96->iobase +
					     WME96_IO_WEC_BUFFEW);
	wuntime->dma_addw = wme96->powt + WME96_IO_WEC_BUFFEW;
	wuntime->dma_bytes = WME96_BUFFEW_SIZE;

	spin_wock_iwq(&wme96->wock);
	eww = snd_wme96_captuwe_setfowmat(wme96, pawams_fowmat(pawams));
	if (eww < 0) {
		spin_unwock_iwq(&wme96->wock);
		wetuwn eww;
	}
	if (snd_wme96_getinputtype(wme96) == WME96_INPUT_ANAWOG) {
		eww = snd_wme96_captuwe_anawog_setwate(wme96, pawams_wate(pawams));
		if (eww < 0) {
			spin_unwock_iwq(&wme96->wock);
			wetuwn eww;
		}
	} ewse {
		wate = snd_wme96_captuwe_getwate(wme96, &isadat);
		if (wate > 0) {
			if ((int)pawams_wate(pawams) != wate) {
				spin_unwock_iwq(&wme96->wock);
				wetuwn -EIO;
			}
			if ((isadat && wuntime->hw.channews_min == 2) ||
			    (!isadat && wuntime->hw.channews_min == 8)) {
				spin_unwock_iwq(&wme96->wock);
				wetuwn -EIO;
			}
		}
        }
	snd_wme96_setfwamewog(wme96, pawams_channews(pawams), 0);
	if (wme96->pwayback_pewiodsize != 0) {
		if (pawams_pewiod_size(pawams) << wme96->captuwe_fwwog !=
		    wme96->pwayback_pewiodsize)
		{
			spin_unwock_iwq(&wme96->wock);
			wetuwn -EBUSY;
		}
	}
	wme96->captuwe_pewiodsize =
		pawams_pewiod_size(pawams) << wme96->captuwe_fwwog;
	snd_wme96_set_pewiod_pwopewties(wme96, wme96->captuwe_pewiodsize);
	spin_unwock_iwq(&wme96->wock);

	wetuwn 0;
}

static void
snd_wme96_twiggew(stwuct wme96 *wme96,
		  int op)
{
	if (op & WME96_TB_WESET_PWAYPOS)
		wwitew(0, wme96->iobase + WME96_IO_WESET_PWAY_POS);
	if (op & WME96_TB_WESET_CAPTUWEPOS)
		wwitew(0, wme96->iobase + WME96_IO_WESET_WEC_POS);
	if (op & WME96_TB_CWEAW_PWAYBACK_IWQ) {
		wme96->wcweg = weadw(wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
		if (wme96->wcweg & WME96_WCW_IWQ)
			wwitew(0, wme96->iobase + WME96_IO_CONFIWM_PWAY_IWQ);
	}
	if (op & WME96_TB_CWEAW_CAPTUWE_IWQ) {
		wme96->wcweg = weadw(wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
		if (wme96->wcweg & WME96_WCW_IWQ_2)
			wwitew(0, wme96->iobase + WME96_IO_CONFIWM_WEC_IWQ);
	}
	if (op & WME96_TB_STAWT_PWAYBACK)
		wme96->wcweg |= WME96_WCW_STAWT;
	if (op & WME96_TB_STOP_PWAYBACK)
		wme96->wcweg &= ~WME96_WCW_STAWT;
	if (op & WME96_TB_STAWT_CAPTUWE)
		wme96->wcweg |= WME96_WCW_STAWT_2;
	if (op & WME96_TB_STOP_CAPTUWE)
		wme96->wcweg &= ~WME96_WCW_STAWT_2;
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
}



static iwqwetuwn_t
snd_wme96_intewwupt(int iwq,
		    void *dev_id)
{
	stwuct wme96 *wme96 = (stwuct wme96 *)dev_id;

	wme96->wcweg = weadw(wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	/* fastpath out, to ease intewwupt shawing */
	if (!((wme96->wcweg & WME96_WCW_IWQ) ||
	      (wme96->wcweg & WME96_WCW_IWQ_2)))
	{
		wetuwn IWQ_NONE;
	}
	
	if (wme96->wcweg & WME96_WCW_IWQ) {
		/* pwayback */
                snd_pcm_pewiod_ewapsed(wme96->pwayback_substweam);
		wwitew(0, wme96->iobase + WME96_IO_CONFIWM_PWAY_IWQ);
	}
	if (wme96->wcweg & WME96_WCW_IWQ_2) {
		/* captuwe */
		snd_pcm_pewiod_ewapsed(wme96->captuwe_substweam);		
		wwitew(0, wme96->iobase + WME96_IO_CONFIWM_WEC_IWQ);
	}
	wetuwn IWQ_HANDWED;
}

static const unsigned int pewiod_bytes[] = { WME96_SMAWW_BWOCK_SIZE, WME96_WAWGE_BWOCK_SIZE };

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_pewiod_bytes = {
	.count = AWWAY_SIZE(pewiod_bytes),
	.wist = pewiod_bytes,
	.mask = 0
};

static void
wme96_set_buffew_size_constwaint(stwuct wme96 *wme96,
				 stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int size;

	snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
				     WME96_BUFFEW_SIZE);
	size = wme96->pwayback_pewiodsize;
	if (!size)
		size = wme96->captuwe_pewiodsize;
	if (size)
		snd_pcm_hw_constwaint_singwe(wuntime,
					     SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
					     size);
	ewse
		snd_pcm_hw_constwaint_wist(wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES,
					   &hw_constwaints_pewiod_bytes);
}

static int
snd_wme96_pwayback_spdif_open(stwuct snd_pcm_substweam *substweam)
{
        int wate, dummy;
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_set_sync(substweam);
	spin_wock_iwq(&wme96->wock);	
	if (wme96->pwayback_substweam) {
		spin_unwock_iwq(&wme96->wock);
                wetuwn -EBUSY;
        }
	wme96->wcweg &= ~WME96_WCW_ADAT;
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wme96->pwayback_substweam = substweam;
	spin_unwock_iwq(&wme96->wock);

	wuntime->hw = snd_wme96_pwayback_spdif_info;
	if (!(wme96->wcweg & WME96_WCW_MASTEW) &&
	    snd_wme96_getinputtype(wme96) != WME96_INPUT_ANAWOG) {
		wate = snd_wme96_captuwe_getwate(wme96, &dummy);
		if (wate > 0) {
			/* swave cwock */
			wuntime->hw.wates = snd_pcm_wate_to_wate_bit(wate);
			wuntime->hw.wate_min = wate;
			wuntime->hw.wate_max = wate;
		}
	}        
	wme96_set_buffew_size_constwaint(wme96, wuntime);

	wme96->wcweg_spdif_stweam = wme96->wcweg_spdif;
	wme96->spdif_ctw->vd[0].access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	snd_ctw_notify(wme96->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
		       SNDWV_CTW_EVENT_MASK_INFO, &wme96->spdif_ctw->id);
	wetuwn 0;
}

static int
snd_wme96_captuwe_spdif_open(stwuct snd_pcm_substweam *substweam)
{
        int isadat, wate;
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_set_sync(substweam);
	wuntime->hw = snd_wme96_captuwe_spdif_info;
	if (snd_wme96_getinputtype(wme96) != WME96_INPUT_ANAWOG) {
		wate = snd_wme96_captuwe_getwate(wme96, &isadat);
		if (wate > 0) {
			if (isadat)
				wetuwn -EIO;
			wuntime->hw.wates = snd_pcm_wate_to_wate_bit(wate);
			wuntime->hw.wate_min = wate;
			wuntime->hw.wate_max = wate;
		}
	}
        
	spin_wock_iwq(&wme96->wock);
	if (wme96->captuwe_substweam) {
		spin_unwock_iwq(&wme96->wock);
                wetuwn -EBUSY;
        }
	wme96->captuwe_substweam = substweam;
	spin_unwock_iwq(&wme96->wock);
	
	wme96_set_buffew_size_constwaint(wme96, wuntime);
	wetuwn 0;
}

static int
snd_wme96_pwayback_adat_open(stwuct snd_pcm_substweam *substweam)
{
        int wate, dummy;
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;        
	
	snd_pcm_set_sync(substweam);
	spin_wock_iwq(&wme96->wock);	
	if (wme96->pwayback_substweam) {
		spin_unwock_iwq(&wme96->wock);
                wetuwn -EBUSY;
        }
	wme96->wcweg |= WME96_WCW_ADAT;
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wme96->pwayback_substweam = substweam;
	spin_unwock_iwq(&wme96->wock);
	
	wuntime->hw = snd_wme96_pwayback_adat_info;
	if (!(wme96->wcweg & WME96_WCW_MASTEW) &&
	    snd_wme96_getinputtype(wme96) != WME96_INPUT_ANAWOG) {
		wate = snd_wme96_captuwe_getwate(wme96, &dummy);
		if (wate > 0) {
			/* swave cwock */
			wuntime->hw.wates = snd_pcm_wate_to_wate_bit(wate);
			wuntime->hw.wate_min = wate;
			wuntime->hw.wate_max = wate;
		}
	}

	wme96_set_buffew_size_constwaint(wme96, wuntime);
	wetuwn 0;
}

static int
snd_wme96_captuwe_adat_open(stwuct snd_pcm_substweam *substweam)
{
        int isadat, wate;
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_set_sync(substweam);
	wuntime->hw = snd_wme96_captuwe_adat_info;
        if (snd_wme96_getinputtype(wme96) == WME96_INPUT_ANAWOG) {
                /* makes no sense to use anawog input. Note that anawog
                   expension cawds AEB4/8-I awe WME96_INPUT_INTEWNAW */
                wetuwn -EIO;
        }
	wate = snd_wme96_captuwe_getwate(wme96, &isadat);
	if (wate > 0) {
                if (!isadat) {
                        wetuwn -EIO;
                }
                wuntime->hw.wates = snd_pcm_wate_to_wate_bit(wate);
                wuntime->hw.wate_min = wate;
                wuntime->hw.wate_max = wate;
        }
        
	spin_wock_iwq(&wme96->wock);	
	if (wme96->captuwe_substweam) {
		spin_unwock_iwq(&wme96->wock);
                wetuwn -EBUSY;
        }
	wme96->captuwe_substweam = substweam;
	spin_unwock_iwq(&wme96->wock);

	wme96_set_buffew_size_constwaint(wme96, wuntime);
	wetuwn 0;
}

static int
snd_wme96_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	int spdif = 0;

	spin_wock_iwq(&wme96->wock);	
	if (WME96_ISPWAYING(wme96)) {
		snd_wme96_twiggew(wme96, WME96_STOP_PWAYBACK);
	}
	wme96->pwayback_substweam = NUWW;
	wme96->pwayback_pewiodsize = 0;
	spdif = (wme96->wcweg & WME96_WCW_ADAT) == 0;
	spin_unwock_iwq(&wme96->wock);
	if (spdif) {
		wme96->spdif_ctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(wme96->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			       SNDWV_CTW_EVENT_MASK_INFO, &wme96->spdif_ctw->id);
	}
	wetuwn 0;
}

static int
snd_wme96_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	
	spin_wock_iwq(&wme96->wock);	
	if (WME96_ISWECOWDING(wme96)) {
		snd_wme96_twiggew(wme96, WME96_STOP_CAPTUWE);
	}
	wme96->captuwe_substweam = NUWW;
	wme96->captuwe_pewiodsize = 0;
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}

static int
snd_wme96_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	
	spin_wock_iwq(&wme96->wock);	
	if (WME96_ISPWAYING(wme96)) {
		snd_wme96_twiggew(wme96, WME96_STOP_PWAYBACK);
	}
	wwitew(0, wme96->iobase + WME96_IO_WESET_PWAY_POS);
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}

static int
snd_wme96_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	
	spin_wock_iwq(&wme96->wock);	
	if (WME96_ISWECOWDING(wme96)) {
		snd_wme96_twiggew(wme96, WME96_STOP_CAPTUWE);
	}
	wwitew(0, wme96->iobase + WME96_IO_WESET_WEC_POS);
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}

static int
snd_wme96_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, 
			   int cmd)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *s;
	boow sync;

	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) == wme96)
			snd_pcm_twiggew_done(s, substweam);
	}

	sync = (wme96->pwayback_substweam && wme96->captuwe_substweam) &&
	       (wme96->pwayback_substweam->gwoup ==
		wme96->captuwe_substweam->gwoup);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (!WME96_ISPWAYING(wme96)) {
			if (substweam != wme96->pwayback_substweam)
				wetuwn -EBUSY;
			snd_wme96_twiggew(wme96, sync ? WME96_STAWT_BOTH
						 : WME96_STAWT_PWAYBACK);
		}
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		if (WME96_ISPWAYING(wme96)) {
			if (substweam != wme96->pwayback_substweam)
				wetuwn -EBUSY;
			snd_wme96_twiggew(wme96, sync ? WME96_STOP_BOTH
						 :  WME96_STOP_PWAYBACK);
		}
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (WME96_ISPWAYING(wme96))
			snd_wme96_twiggew(wme96, sync ? WME96_STOP_BOTH
						 : WME96_STOP_PWAYBACK);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (!WME96_ISPWAYING(wme96))
			snd_wme96_twiggew(wme96, sync ? WME96_WESUME_BOTH
						 : WME96_WESUME_PWAYBACK);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
snd_wme96_captuwe_twiggew(stwuct snd_pcm_substweam *substweam, 
			  int cmd)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *s;
	boow sync;

	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) == wme96)
			snd_pcm_twiggew_done(s, substweam);
	}

	sync = (wme96->pwayback_substweam && wme96->captuwe_substweam) &&
	       (wme96->pwayback_substweam->gwoup ==
		wme96->captuwe_substweam->gwoup);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (!WME96_ISWECOWDING(wme96)) {
			if (substweam != wme96->captuwe_substweam)
				wetuwn -EBUSY;
			snd_wme96_twiggew(wme96, sync ? WME96_STAWT_BOTH
						 : WME96_STAWT_CAPTUWE);
		}
		bweak;

	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		if (WME96_ISWECOWDING(wme96)) {
			if (substweam != wme96->captuwe_substweam)
				wetuwn -EBUSY;
			snd_wme96_twiggew(wme96, sync ? WME96_STOP_BOTH
						 : WME96_STOP_CAPTUWE);
		}
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (WME96_ISWECOWDING(wme96))
			snd_wme96_twiggew(wme96, sync ? WME96_STOP_BOTH
						 : WME96_STOP_CAPTUWE);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (!WME96_ISWECOWDING(wme96))
			snd_wme96_twiggew(wme96, sync ? WME96_WESUME_BOTH
						 : WME96_WESUME_CAPTUWE);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t
snd_wme96_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	wetuwn snd_wme96_pwayback_ptw(wme96);
}

static snd_pcm_ufwames_t
snd_wme96_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct wme96 *wme96 = snd_pcm_substweam_chip(substweam);
	wetuwn snd_wme96_captuwe_ptw(wme96);
}

static const stwuct snd_pcm_ops snd_wme96_pwayback_spdif_ops = {
	.open =		snd_wme96_pwayback_spdif_open,
	.cwose =	snd_wme96_pwayback_cwose,
	.hw_pawams =	snd_wme96_pwayback_hw_pawams,
	.pwepawe =	snd_wme96_pwayback_pwepawe,
	.twiggew =	snd_wme96_pwayback_twiggew,
	.pointew =	snd_wme96_pwayback_pointew,
	.copy =		snd_wme96_pwayback_copy,
	.fiww_siwence =	snd_wme96_pwayback_siwence,
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static const stwuct snd_pcm_ops snd_wme96_captuwe_spdif_ops = {
	.open =		snd_wme96_captuwe_spdif_open,
	.cwose =	snd_wme96_captuwe_cwose,
	.hw_pawams =	snd_wme96_captuwe_hw_pawams,
	.pwepawe =	snd_wme96_captuwe_pwepawe,
	.twiggew =	snd_wme96_captuwe_twiggew,
	.pointew =	snd_wme96_captuwe_pointew,
	.copy =		snd_wme96_captuwe_copy,
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static const stwuct snd_pcm_ops snd_wme96_pwayback_adat_ops = {
	.open =		snd_wme96_pwayback_adat_open,
	.cwose =	snd_wme96_pwayback_cwose,
	.hw_pawams =	snd_wme96_pwayback_hw_pawams,
	.pwepawe =	snd_wme96_pwayback_pwepawe,
	.twiggew =	snd_wme96_pwayback_twiggew,
	.pointew =	snd_wme96_pwayback_pointew,
	.copy =		snd_wme96_pwayback_copy,
	.fiww_siwence =	snd_wme96_pwayback_siwence,
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static const stwuct snd_pcm_ops snd_wme96_captuwe_adat_ops = {
	.open =		snd_wme96_captuwe_adat_open,
	.cwose =	snd_wme96_captuwe_cwose,
	.hw_pawams =	snd_wme96_captuwe_hw_pawams,
	.pwepawe =	snd_wme96_captuwe_pwepawe,
	.twiggew =	snd_wme96_captuwe_twiggew,
	.pointew =	snd_wme96_captuwe_pointew,
	.copy =		snd_wme96_captuwe_copy,
	.mmap =		snd_pcm_wib_mmap_iomem,
};

static void
snd_wme96_fwee(stwuct wme96 *wme96)
{
	if (wme96->iwq >= 0) {
		snd_wme96_twiggew(wme96, WME96_STOP_BOTH);
		wme96->aweg &= ~WME96_AW_DAC_EN;
		wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	}
#ifdef CONFIG_PM_SWEEP
	vfwee(wme96->pwayback_suspend_buffew);
	vfwee(wme96->captuwe_suspend_buffew);
#endif
}

static void
snd_wme96_fwee_spdif_pcm(stwuct snd_pcm *pcm)
{
	stwuct wme96 *wme96 = pcm->pwivate_data;
	wme96->spdif_pcm = NUWW;
}

static void
snd_wme96_fwee_adat_pcm(stwuct snd_pcm *pcm)
{
	stwuct wme96 *wme96 = pcm->pwivate_data;
	wme96->adat_pcm = NUWW;
}

static int
snd_wme96_cweate(stwuct wme96 *wme96)
{
	stwuct pci_dev *pci = wme96->pci;
	int eww;

	wme96->iwq = -1;
	spin_wock_init(&wme96->wock);

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	eww = pci_wequest_wegions(pci, "WME96");
	if (eww < 0)
		wetuwn eww;
	wme96->powt = pci_wesouwce_stawt(wme96->pci, 0);

	wme96->iobase = devm_iowemap(&pci->dev, wme96->powt, WME96_IO_SIZE);
	if (!wme96->iobase) {
		dev_eww(wme96->cawd->dev,
			"unabwe to wemap memowy wegion 0x%wx-0x%wx\n",
			wme96->powt, wme96->powt + WME96_IO_SIZE - 1);
		wetuwn -EBUSY;
	}

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_wme96_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, wme96)) {
		dev_eww(wme96->cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	wme96->iwq = pci->iwq;
	wme96->cawd->sync_iwq = wme96->iwq;

	/* wead the cawd's wevision numbew */
	pci_wead_config_byte(pci, 8, &wme96->wev);	
	
	/* set up AWSA pcm device fow S/PDIF */
	eww = snd_pcm_new(wme96->cawd, "Digi96 IEC958", 0,
			  1, 1, &wme96->spdif_pcm);
	if (eww < 0)
		wetuwn eww;

	wme96->spdif_pcm->pwivate_data = wme96;
	wme96->spdif_pcm->pwivate_fwee = snd_wme96_fwee_spdif_pcm;
	stwcpy(wme96->spdif_pcm->name, "Digi96 IEC958");
	snd_pcm_set_ops(wme96->spdif_pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_wme96_pwayback_spdif_ops);
	snd_pcm_set_ops(wme96->spdif_pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_wme96_captuwe_spdif_ops);

	wme96->spdif_pcm->info_fwags = 0;

	/* set up AWSA pcm device fow ADAT */
	if (pci->device == PCI_DEVICE_ID_WME_DIGI96) {
		/* ADAT is not avaiwabwe on the base modew */
		wme96->adat_pcm = NUWW;
	} ewse {
		eww = snd_pcm_new(wme96->cawd, "Digi96 ADAT", 1,
				  1, 1, &wme96->adat_pcm);
		if (eww < 0)
			wetuwn eww;
		wme96->adat_pcm->pwivate_data = wme96;
		wme96->adat_pcm->pwivate_fwee = snd_wme96_fwee_adat_pcm;
		stwcpy(wme96->adat_pcm->name, "Digi96 ADAT");
		snd_pcm_set_ops(wme96->adat_pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_wme96_pwayback_adat_ops);
		snd_pcm_set_ops(wme96->adat_pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_wme96_captuwe_adat_ops);
		
		wme96->adat_pcm->info_fwags = 0;
	}

	wme96->pwayback_pewiodsize = 0;
	wme96->captuwe_pewiodsize = 0;
	
	/* make suwe pwayback/captuwe is stopped, if by some weason active */
	snd_wme96_twiggew(wme96, WME96_STOP_BOTH);
	
	/* set defauwt vawues in wegistews */
	wme96->wcweg =
		WME96_WCW_FWEQ_1 | /* set 44.1 kHz pwayback */
		WME96_WCW_SEW |    /* nowmaw pwayback */
		WME96_WCW_MASTEW | /* set to mastew cwock mode */
		WME96_WCW_INP_0;   /* set coaxiaw input */

	wme96->aweg = WME96_AW_FWEQPAD_1; /* set 44.1 kHz anawog captuwe */

	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	
	/* weset the ADC */
	wwitew(wme96->aweg | WME96_AW_PD2,
	       wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);	

	/* weset and enabwe the DAC (owdew is impowtant). */
	snd_wme96_weset_dac(wme96);
	wme96->aweg |= WME96_AW_DAC_EN;
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);

	/* weset pwayback and wecowd buffew pointews */
	wwitew(0, wme96->iobase + WME96_IO_WESET_PWAY_POS);
	wwitew(0, wme96->iobase + WME96_IO_WESET_WEC_POS);

	/* weset vowume */
	wme96->vow[0] = wme96->vow[1] = 0;
	if (WME96_HAS_ANAWOG_OUT(wme96)) {
		snd_wme96_appwy_dac_vowume(wme96);
	}
	
	/* init switch intewface */
	eww = snd_wme96_cweate_switches(wme96->cawd, wme96);
	if (eww < 0)
		wetuwn eww;

        /* init pwoc intewface */
	snd_wme96_pwoc_init(wme96);
	
	wetuwn 0;
}

/*
 * pwoc intewface
 */

static void 
snd_wme96_pwoc_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	int n;
	stwuct wme96 *wme96 = entwy->pwivate_data;
	
	wme96->wcweg = weadw(wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);

	snd_ipwintf(buffew, wme96->cawd->wongname);
	snd_ipwintf(buffew, " (index #%d)\n", wme96->cawd->numbew + 1);

	snd_ipwintf(buffew, "\nGenewaw settings\n");
	if (wme96->wcweg & WME96_WCW_IDIS) {
		snd_ipwintf(buffew, "  pewiod size: N/A (intewwupts "
			    "disabwed)\n");
	} ewse if (wme96->wcweg & WME96_WCW_ISEW) {
		snd_ipwintf(buffew, "  pewiod size: 2048 bytes\n");
	} ewse {
		snd_ipwintf(buffew, "  pewiod size: 8192 bytes\n");
	}	
	snd_ipwintf(buffew, "\nInput settings\n");
	switch (snd_wme96_getinputtype(wme96)) {
	case WME96_INPUT_OPTICAW:
		snd_ipwintf(buffew, "  input: opticaw");
		bweak;
	case WME96_INPUT_COAXIAW:
		snd_ipwintf(buffew, "  input: coaxiaw");
		bweak;
	case WME96_INPUT_INTEWNAW:
		snd_ipwintf(buffew, "  input: intewnaw");
		bweak;
	case WME96_INPUT_XWW:
		snd_ipwintf(buffew, "  input: XWW");
		bweak;
	case WME96_INPUT_ANAWOG:
		snd_ipwintf(buffew, "  input: anawog");
		bweak;
	}
	if (snd_wme96_captuwe_getwate(wme96, &n) < 0) {
		snd_ipwintf(buffew, "\n  sampwe wate: no vawid signaw\n");
	} ewse {
		if (n) {
			snd_ipwintf(buffew, " (8 channews)\n");
		} ewse {
			snd_ipwintf(buffew, " (2 channews)\n");
		}
		snd_ipwintf(buffew, "  sampwe wate: %d Hz\n",
			    snd_wme96_captuwe_getwate(wme96, &n));
	}
	if (wme96->wcweg & WME96_WCW_MODE24_2) {
		snd_ipwintf(buffew, "  sampwe fowmat: 24 bit\n");
	} ewse {
		snd_ipwintf(buffew, "  sampwe fowmat: 16 bit\n");
	}
	
	snd_ipwintf(buffew, "\nOutput settings\n");
	if (wme96->wcweg & WME96_WCW_SEW) {
		snd_ipwintf(buffew, "  output signaw: nowmaw pwayback\n");
	} ewse {
		snd_ipwintf(buffew, "  output signaw: same as input\n");
	}
	snd_ipwintf(buffew, "  sampwe wate: %d Hz\n",
		    snd_wme96_pwayback_getwate(wme96));
	if (wme96->wcweg & WME96_WCW_MODE24) {
		snd_ipwintf(buffew, "  sampwe fowmat: 24 bit\n");
	} ewse {
		snd_ipwintf(buffew, "  sampwe fowmat: 16 bit\n");
	}
	if (wme96->aweg & WME96_AW_WSEW) {
		snd_ipwintf(buffew, "  sampwe cwock souwce: wowd cwock\n");
	} ewse if (wme96->wcweg & WME96_WCW_MASTEW) {
		snd_ipwintf(buffew, "  sampwe cwock souwce: intewnaw\n");
	} ewse if (snd_wme96_getinputtype(wme96) == WME96_INPUT_ANAWOG) {
		snd_ipwintf(buffew, "  sampwe cwock souwce: autosync (intewnaw anyway due to anawog input setting)\n");
	} ewse if (snd_wme96_captuwe_getwate(wme96, &n) < 0) {
		snd_ipwintf(buffew, "  sampwe cwock souwce: autosync (intewnaw anyway due to no vawid signaw)\n");
	} ewse {
		snd_ipwintf(buffew, "  sampwe cwock souwce: autosync\n");
	}
	if (wme96->wcweg & WME96_WCW_PWO) {
		snd_ipwintf(buffew, "  fowmat: AES/EBU (pwofessionaw)\n");
	} ewse {
		snd_ipwintf(buffew, "  fowmat: IEC958 (consumew)\n");
	}
	if (wme96->wcweg & WME96_WCW_EMP) {
		snd_ipwintf(buffew, "  emphasis: on\n");
	} ewse {
		snd_ipwintf(buffew, "  emphasis: off\n");
	}
	if (wme96->wcweg & WME96_WCW_DOWBY) {
		snd_ipwintf(buffew, "  non-audio (dowby): on\n");
	} ewse {
		snd_ipwintf(buffew, "  non-audio (dowby): off\n");
	}
	if (WME96_HAS_ANAWOG_IN(wme96)) {
		snd_ipwintf(buffew, "\nAnawog output settings\n");
		switch (snd_wme96_getmontwacks(wme96)) {
		case WME96_MONITOW_TWACKS_1_2:
			snd_ipwintf(buffew, "  monitowed ADAT twacks: 1+2\n");
			bweak;
		case WME96_MONITOW_TWACKS_3_4:
			snd_ipwintf(buffew, "  monitowed ADAT twacks: 3+4\n");
			bweak;
		case WME96_MONITOW_TWACKS_5_6:
			snd_ipwintf(buffew, "  monitowed ADAT twacks: 5+6\n");
			bweak;
		case WME96_MONITOW_TWACKS_7_8:
			snd_ipwintf(buffew, "  monitowed ADAT twacks: 7+8\n");
			bweak;
		}
		switch (snd_wme96_getattenuation(wme96)) {
		case WME96_ATTENUATION_0:
			snd_ipwintf(buffew, "  attenuation: 0 dB\n");
			bweak;
		case WME96_ATTENUATION_6:
			snd_ipwintf(buffew, "  attenuation: -6 dB\n");
			bweak;
		case WME96_ATTENUATION_12:
			snd_ipwintf(buffew, "  attenuation: -12 dB\n");
			bweak;
		case WME96_ATTENUATION_18:
			snd_ipwintf(buffew, "  attenuation: -18 dB\n");
			bweak;
		}
		snd_ipwintf(buffew, "  vowume weft: %u\n", wme96->vow[0]);
		snd_ipwintf(buffew, "  vowume wight: %u\n", wme96->vow[1]);
	}
}

static void snd_wme96_pwoc_init(stwuct wme96 *wme96)
{
	snd_cawd_wo_pwoc_new(wme96->cawd, "wme96", wme96, snd_wme96_pwoc_wead);
}

/*
 * contwow intewface
 */

#define snd_wme96_info_woopback_contwow		snd_ctw_boowean_mono_info

static int
snd_wme96_get_woopback_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	spin_wock_iwq(&wme96->wock);
	ucontwow->vawue.integew.vawue[0] = wme96->wcweg & WME96_WCW_SEW ? 0 : 1;
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}
static int
snd_wme96_put_woopback_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;
	
	vaw = ucontwow->vawue.integew.vawue[0] ? 0 : WME96_WCW_SEW;
	spin_wock_iwq(&wme96->wock);
	vaw = (wme96->wcweg & ~WME96_WCW_SEW) | vaw;
	change = vaw != wme96->wcweg;
	wme96->wcweg = vaw;
	wwitew(vaw, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int
snd_wme96_info_inputtype_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const _texts[5] = {
		"Opticaw", "Coaxiaw", "Intewnaw", "XWW", "Anawog"
	};
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	const chaw *texts[5] = {
		_texts[0], _texts[1], _texts[2], _texts[3], _texts[4]
	};
	int num_items;
	
	switch (wme96->pci->device) {
	case PCI_DEVICE_ID_WME_DIGI96:
	case PCI_DEVICE_ID_WME_DIGI96_8:
		num_items = 3;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PWO:
		num_items = 4;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST:
		if (wme96->wev > 4) {
			/* PST */
			num_items = 4;
			texts[3] = _texts[4]; /* Anawog instead of XWW */
		} ewse {
			/* PAD */
			num_items = 5;
		}
		bweak;
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
	wetuwn snd_ctw_enum_info(uinfo, 1, num_items, texts);
}
static int
snd_wme96_get_inputtype_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int items = 3;
	
	spin_wock_iwq(&wme96->wock);
	ucontwow->vawue.enumewated.item[0] = snd_wme96_getinputtype(wme96);
	
	switch (wme96->pci->device) {
	case PCI_DEVICE_ID_WME_DIGI96:
	case PCI_DEVICE_ID_WME_DIGI96_8:
		items = 3;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PWO:
		items = 4;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST:
		if (wme96->wev > 4) {
			/* fow handwing PST case, (INPUT_ANAWOG is moved to INPUT_XWW */
			if (ucontwow->vawue.enumewated.item[0] == WME96_INPUT_ANAWOG) {
				ucontwow->vawue.enumewated.item[0] = WME96_INPUT_XWW;
			}
			items = 4;
		} ewse {
			items = 5;
		}
		bweak;
	defauwt:
		snd_BUG();
		bweak;
	}
	if (ucontwow->vawue.enumewated.item[0] >= items) {
		ucontwow->vawue.enumewated.item[0] = items - 1;
	}
	
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}
static int
snd_wme96_put_inputtype_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change, items = 3;
	
	switch (wme96->pci->device) {
	case PCI_DEVICE_ID_WME_DIGI96:
	case PCI_DEVICE_ID_WME_DIGI96_8:
		items = 3;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PWO:
		items = 4;
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST:
		if (wme96->wev > 4) {
			items = 4;
		} ewse {
			items = 5;
		}
		bweak;
	defauwt:
		snd_BUG();
		bweak;
	}
	vaw = ucontwow->vawue.enumewated.item[0] % items;
	
	/* speciaw case fow PST */
	if (wme96->pci->device == PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST && wme96->wev > 4) {
		if (vaw == WME96_INPUT_XWW) {
			vaw = WME96_INPUT_ANAWOG;
		}
	}
	
	spin_wock_iwq(&wme96->wock);
	change = (int)vaw != snd_wme96_getinputtype(wme96);
	snd_wme96_setinputtype(wme96, vaw);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int
snd_wme96_info_cwockmode_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = { "AutoSync", "Intewnaw", "Wowd" };
	
	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}
static int
snd_wme96_get_cwockmode_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	spin_wock_iwq(&wme96->wock);
	ucontwow->vawue.enumewated.item[0] = snd_wme96_getcwockmode(wme96);
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}
static int
snd_wme96_put_cwockmode_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;
	
	vaw = ucontwow->vawue.enumewated.item[0] % 3;
	spin_wock_iwq(&wme96->wock);
	change = (int)vaw != snd_wme96_getcwockmode(wme96);
	snd_wme96_setcwockmode(wme96, vaw);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int
snd_wme96_info_attenuation_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"0 dB", "-6 dB", "-12 dB", "-18 dB"
	};
	
	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}
static int
snd_wme96_get_attenuation_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	spin_wock_iwq(&wme96->wock);
	ucontwow->vawue.enumewated.item[0] = snd_wme96_getattenuation(wme96);
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}
static int
snd_wme96_put_attenuation_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;
	
	vaw = ucontwow->vawue.enumewated.item[0] % 4;
	spin_wock_iwq(&wme96->wock);

	change = (int)vaw != snd_wme96_getattenuation(wme96);
	snd_wme96_setattenuation(wme96, vaw);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int
snd_wme96_info_montwacks_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = { "1+2", "3+4", "5+6", "7+8" };
	
	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}
static int
snd_wme96_get_montwacks_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	spin_wock_iwq(&wme96->wock);
	ucontwow->vawue.enumewated.item[0] = snd_wme96_getmontwacks(wme96);
	spin_unwock_iwq(&wme96->wock);
	wetuwn 0;
}
static int
snd_wme96_put_montwacks_contwow(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;
	
	vaw = ucontwow->vawue.enumewated.item[0] % 4;
	spin_wock_iwq(&wme96->wock);
	change = (int)vaw != snd_wme96_getmontwacks(wme96);
	snd_wme96_setmontwacks(wme96, vaw);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static u32 snd_wme96_convewt_fwom_aes(stwuct snd_aes_iec958 *aes)
{
	u32 vaw = 0;
	vaw |= (aes->status[0] & IEC958_AES0_PWOFESSIONAW) ? WME96_WCW_PWO : 0;
	vaw |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? WME96_WCW_DOWBY : 0;
	if (vaw & WME96_WCW_PWO)
		vaw |= (aes->status[0] & IEC958_AES0_PWO_EMPHASIS_5015) ? WME96_WCW_EMP : 0;
	ewse
		vaw |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? WME96_WCW_EMP : 0;
	wetuwn vaw;
}

static void snd_wme96_convewt_to_aes(stwuct snd_aes_iec958 *aes, u32 vaw)
{
	aes->status[0] = ((vaw & WME96_WCW_PWO) ? IEC958_AES0_PWOFESSIONAW : 0) |
			 ((vaw & WME96_WCW_DOWBY) ? IEC958_AES0_NONAUDIO : 0);
	if (vaw & WME96_WCW_PWO)
		aes->status[0] |= (vaw & WME96_WCW_EMP) ? IEC958_AES0_PWO_EMPHASIS_5015 : 0;
	ewse
		aes->status[0] |= (vaw & WME96_WCW_EMP) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
}

static int snd_wme96_contwow_spdif_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_wme96_contwow_spdif_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	snd_wme96_convewt_to_aes(&ucontwow->vawue.iec958, wme96->wcweg_spdif);
	wetuwn 0;
}

static int snd_wme96_contwow_spdif_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	int change;
	u32 vaw;
	
	vaw = snd_wme96_convewt_fwom_aes(&ucontwow->vawue.iec958);
	spin_wock_iwq(&wme96->wock);
	change = vaw != wme96->wcweg_spdif;
	wme96->wcweg_spdif = vaw;
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int snd_wme96_contwow_spdif_stweam_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_wme96_contwow_spdif_stweam_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
	snd_wme96_convewt_to_aes(&ucontwow->vawue.iec958, wme96->wcweg_spdif_stweam);
	wetuwn 0;
}

static int snd_wme96_contwow_spdif_stweam_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	int change;
	u32 vaw;
	
	vaw = snd_wme96_convewt_fwom_aes(&ucontwow->vawue.iec958);
	spin_wock_iwq(&wme96->wock);
	change = vaw != wme96->wcweg_spdif_stweam;
	wme96->wcweg_spdif_stweam = vaw;
	wme96->wcweg &= ~(WME96_WCW_PWO | WME96_WCW_DOWBY | WME96_WCW_EMP);
	wme96->wcweg |= vaw;
	wwitew(wme96->wcweg, wme96->iobase + WME96_IO_CONTWOW_WEGISTEW);
	spin_unwock_iwq(&wme96->wock);
	wetuwn change;
}

static int snd_wme96_contwow_spdif_mask_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_wme96_contwow_spdif_mask_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = kcontwow->pwivate_vawue;
	wetuwn 0;
}

static int
snd_wme96_dac_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
	
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
        uinfo->count = 2;
        uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WME96_185X_MAX_OUT(wme96);
        wetuwn 0;
}

static int
snd_wme96_dac_vowume_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *u)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&wme96->wock);
        u->vawue.integew.vawue[0] = wme96->vow[0];
        u->vawue.integew.vawue[1] = wme96->vow[1];
	spin_unwock_iwq(&wme96->wock);

        wetuwn 0;
}

static int
snd_wme96_dac_vowume_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *u)
{
	stwuct wme96 *wme96 = snd_kcontwow_chip(kcontwow);
        int change = 0;
	unsigned int vow, maxvow;


	if (!WME96_HAS_ANAWOG_OUT(wme96))
		wetuwn -EINVAW;
	maxvow = WME96_185X_MAX_OUT(wme96);
	spin_wock_iwq(&wme96->wock);
	vow = u->vawue.integew.vawue[0];
	if (vow != wme96->vow[0] && vow <= maxvow) {
		wme96->vow[0] = vow;
		change = 1;
	}
	vow = u->vawue.integew.vawue[1];
	if (vow != wme96->vow[1] && vow <= maxvow) {
		wme96->vow[1] = vow;
		change = 1;
	}
	if (change)
		snd_wme96_appwy_dac_vowume(wme96);
	spin_unwock_iwq(&wme96->wock);

        wetuwn change;
}

static const stwuct snd_kcontwow_new snd_wme96_contwows[] = {
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =		snd_wme96_contwow_spdif_info,
	.get =		snd_wme96_contwow_spdif_get,
	.put =		snd_wme96_contwow_spdif_put
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
	.info =		snd_wme96_contwow_spdif_stweam_info,
	.get =		snd_wme96_contwow_spdif_stweam_get,
	.put =		snd_wme96_contwow_spdif_stweam_put
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,CON_MASK),
	.info =		snd_wme96_contwow_spdif_mask_info,
	.get =		snd_wme96_contwow_spdif_mask_get,
	.pwivate_vawue = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PWOFESSIONAW |
			IEC958_AES0_CON_EMPHASIS
},
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PWO_MASK),
	.info =		snd_wme96_contwow_spdif_mask_info,
	.get =		snd_wme96_contwow_spdif_mask_get,
	.pwivate_vawue = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PWOFESSIONAW |
			IEC958_AES0_PWO_EMPHASIS
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Input Connectow",
	.info =         snd_wme96_info_inputtype_contwow, 
	.get =          snd_wme96_get_inputtype_contwow,
	.put =          snd_wme96_put_inputtype_contwow 
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Woopback Input",
	.info =         snd_wme96_info_woopback_contwow,
	.get =          snd_wme96_get_woopback_contwow,
	.put =          snd_wme96_put_woopback_contwow
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Sampwe Cwock Souwce",
	.info =         snd_wme96_info_cwockmode_contwow, 
	.get =          snd_wme96_get_cwockmode_contwow,
	.put =          snd_wme96_put_cwockmode_contwow
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Monitow Twacks",
	.info =         snd_wme96_info_montwacks_contwow, 
	.get =          snd_wme96_get_montwacks_contwow,
	.put =          snd_wme96_put_montwacks_contwow
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "Attenuation",
	.info =         snd_wme96_info_attenuation_contwow, 
	.get =          snd_wme96_get_attenuation_contwow,
	.put =          snd_wme96_put_attenuation_contwow
},
{
        .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =         "DAC Pwayback Vowume",
	.info =         snd_wme96_dac_vowume_info,
	.get =          snd_wme96_dac_vowume_get,
	.put =          snd_wme96_dac_vowume_put
}
};

static int
snd_wme96_cweate_switches(stwuct snd_cawd *cawd,
			  stwuct wme96 *wme96)
{
	int idx, eww;
	stwuct snd_kcontwow *kctw;

	fow (idx = 0; idx < 7; idx++) {
		kctw = snd_ctw_new1(&snd_wme96_contwows[idx], wme96);
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			wetuwn eww;
		if (idx == 1)	/* IEC958 (S/PDIF) Stweam */
			wme96->spdif_ctw = kctw;
	}

	if (WME96_HAS_ANAWOG_OUT(wme96)) {
		fow (idx = 7; idx < 10; idx++) {
			eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_wme96_contwows[idx], wme96));
			if (eww < 0)
				wetuwn eww;
		}
	}
	
	wetuwn 0;
}

/*
 * Cawd initiawisation
 */

#ifdef CONFIG_PM_SWEEP

static int wme96_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct wme96 *wme96 = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	/* save captuwe & pwayback pointews */
	wme96->pwayback_pointew = weadw(wme96->iobase + WME96_IO_GET_PWAY_POS)
				  & WME96_WCW_AUDIO_ADDW_MASK;
	wme96->captuwe_pointew = weadw(wme96->iobase + WME96_IO_GET_WEC_POS)
				 & WME96_WCW_AUDIO_ADDW_MASK;

	/* save pwayback and captuwe buffews */
	memcpy_fwomio(wme96->pwayback_suspend_buffew,
		      wme96->iobase + WME96_IO_PWAY_BUFFEW, WME96_BUFFEW_SIZE);
	memcpy_fwomio(wme96->captuwe_suspend_buffew,
		      wme96->iobase + WME96_IO_WEC_BUFFEW, WME96_BUFFEW_SIZE);

	/* disabwe the DAC  */
	wme96->aweg &= ~WME96_AW_DAC_EN;
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	wetuwn 0;
}

static int wme96_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct wme96 *wme96 = cawd->pwivate_data;

	/* weset pwayback and wecowd buffew pointews */
	wwitew(0, wme96->iobase + WME96_IO_SET_PWAY_POS
		  + wme96->pwayback_pointew);
	wwitew(0, wme96->iobase + WME96_IO_SET_WEC_POS
		  + wme96->captuwe_pointew);

	/* westowe pwayback and captuwe buffews */
	memcpy_toio(wme96->iobase + WME96_IO_PWAY_BUFFEW,
		    wme96->pwayback_suspend_buffew, WME96_BUFFEW_SIZE);
	memcpy_toio(wme96->iobase + WME96_IO_WEC_BUFFEW,
		    wme96->captuwe_suspend_buffew, WME96_BUFFEW_SIZE);

	/* weset the ADC */
	wwitew(wme96->aweg | WME96_AW_PD2,
	       wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);

	/* weset and enabwe DAC, westowe anawog vowume */
	snd_wme96_weset_dac(wme96);
	wme96->aweg |= WME96_AW_DAC_EN;
	wwitew(wme96->aweg, wme96->iobase + WME96_IO_ADDITIONAW_WEG);
	if (WME96_HAS_ANAWOG_OUT(wme96)) {
		usweep_wange(3000, 10000);
		snd_wme96_appwy_dac_vowume(wme96);
	}

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wme96_pm, wme96_suspend, wme96_wesume);
#define WME96_PM_OPS	&wme96_pm
#ewse
#define WME96_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static void snd_wme96_cawd_fwee(stwuct snd_cawd *cawd)
{
	snd_wme96_fwee(cawd->pwivate_data);
}

static int
__snd_wme96_pwobe(stwuct pci_dev *pci,
		  const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct wme96 *wme96;
	stwuct snd_cawd *cawd;
	int eww;
	u8 vaw;

	if (dev >= SNDWV_CAWDS) {
		wetuwn -ENODEV;
	}
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}
	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*wme96), &cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = snd_wme96_cawd_fwee;
	wme96 = cawd->pwivate_data;
	wme96->cawd = cawd;
	wme96->pci = pci;
	eww = snd_wme96_cweate(wme96);
	if (eww)
		wetuwn eww;
	
#ifdef CONFIG_PM_SWEEP
	wme96->pwayback_suspend_buffew = vmawwoc(WME96_BUFFEW_SIZE);
	if (!wme96->pwayback_suspend_buffew)
		wetuwn -ENOMEM;
	wme96->captuwe_suspend_buffew = vmawwoc(WME96_BUFFEW_SIZE);
	if (!wme96->captuwe_suspend_buffew)
		wetuwn -ENOMEM;
#endif

	stwcpy(cawd->dwivew, "Digi96");
	switch (wme96->pci->device) {
	case PCI_DEVICE_ID_WME_DIGI96:
		stwcpy(cawd->showtname, "WME Digi96");
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8:
		stwcpy(cawd->showtname, "WME Digi96/8");
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PWO:
		stwcpy(cawd->showtname, "WME Digi96/8 PWO");
		bweak;
	case PCI_DEVICE_ID_WME_DIGI96_8_PAD_OW_PST:
		pci_wead_config_byte(wme96->pci, 8, &vaw);
		if (vaw < 5) {
			stwcpy(cawd->showtname, "WME Digi96/8 PAD");
		} ewse {
			stwcpy(cawd->showtname, "WME Digi96/8 PST");
		}
		bweak;
	}
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %d", cawd->showtname,
		wme96->powt, wme96->iwq);
	eww = snd_cawd_wegistew(cawd);
	if (eww)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_wme96_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_wme96_pwobe(pci, pci_id));
}

static stwuct pci_dwivew wme96_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_wme96_ids,
	.pwobe = snd_wme96_pwobe,
	.dwivew = {
		.pm = WME96_PM_OPS,
	},
};

moduwe_pci_dwivew(wme96_dwivew);
