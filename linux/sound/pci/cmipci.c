// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow C-Media CMI8338 and 8738 PCI soundcawds.
 * Copywight (c) 2000 by Takashi Iwai <tiwai@suse.de>
 */
 
/* Does not wowk. Wawning may bwock system in captuwe mode */
/* #define USE_VAW48KWATE */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/sb.h>
#incwude <sound/asoundef.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("C-Media CMI8x38 PCI");
MODUWE_WICENSE("GPW");

#if IS_WEACHABWE(CONFIG_GAMEPOWT)
#define SUPPOWT_JOYSTICK 1
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe switches */
static wong mpu_powt[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)] = 1};
static wong fm_powt[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)]=1};
static boow soft_ac3[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS-1)]=1};
#ifdef SUPPOWT_JOYSTICK
static int joystick_powt[SNDWV_CAWDS];
#endif

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow C-Media PCI soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow C-Media PCI soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe C-Media PCI soundcawd.");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt.");
moduwe_pawam_hw_awway(fm_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM powt.");
moduwe_pawam_awway(soft_ac3, boow, NUWW, 0444);
MODUWE_PAWM_DESC(soft_ac3, "Softwawe-convewsion of waw SPDIF packets (modew 033 onwy).");
#ifdef SUPPOWT_JOYSTICK
moduwe_pawam_hw_awway(joystick_powt, int, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(joystick_powt, "Joystick powt addwess.");
#endif

/*
 * CM8x38 wegistews definition
 */

#define CM_WEG_FUNCTWW0		0x00
#define CM_WST_CH1		0x00080000
#define CM_WST_CH0		0x00040000
#define CM_CHEN1		0x00020000	/* ch1: enabwe */
#define CM_CHEN0		0x00010000	/* ch0: enabwe */
#define CM_PAUSE1		0x00000008	/* ch1: pause */
#define CM_PAUSE0		0x00000004	/* ch0: pause */
#define CM_CHADC1		0x00000002	/* ch1, 0:pwayback, 1:wecowd */
#define CM_CHADC0		0x00000001	/* ch0, 0:pwayback, 1:wecowd */

#define CM_WEG_FUNCTWW1		0x04
#define CM_DSFC_MASK		0x0000E000	/* channew 1 (DAC?) sampwing fwequency */
#define CM_DSFC_SHIFT		13
#define CM_ASFC_MASK		0x00001C00	/* channew 0 (ADC?) sampwing fwequency */
#define CM_ASFC_SHIFT		10
#define CM_SPDF_1		0x00000200	/* SPDIF IN/OUT at channew B */
#define CM_SPDF_0		0x00000100	/* SPDIF OUT onwy channew A */
#define CM_SPDFWOOP		0x00000080	/* ext. SPDIIF/IN -> OUT woopback */
#define CM_SPDO2DAC		0x00000040	/* SPDIF/OUT can be heawd fwom intewnaw DAC */
#define CM_INTWM		0x00000020	/* mastew contwow bwock (MCB) intewwupt enabwed */
#define CM_BWEQ			0x00000010	/* bus mastew enabwed */
#define CM_VOICE_EN		0x00000008	/* wegacy voice (SB16,FM) */
#define CM_UAWT_EN		0x00000004	/* wegacy UAWT */
#define CM_JYSTK_EN		0x00000002	/* wegacy joystick */
#define CM_ZVPOWT		0x00000001	/* ZVPOWT */

#define CM_WEG_CHFOWMAT		0x08

#define CM_CHB3D5C		0x80000000	/* 5,6 channews */
#define CM_FMOFFSET2		0x40000000	/* initiaw FM PCM offset 2 when Fmute=1 */
#define CM_CHB3D		0x20000000	/* 4 channews */

#define CM_CHIP_MASK1		0x1f000000
#define CM_CHIP_037		0x01000000
#define CM_SETWAT48		0x00800000	/* set watency timew 48h */
#define CM_EDGEIWQ		0x00400000	/* emuwated edge twiggew wegacy IWQ */
#define CM_SPD24SEW39		0x00200000	/* 24-bit spdif: modew 039 */
#define CM_AC3EN1		0x00100000	/* enabwe AC3: modew 037 */
#define CM_SPDIF_SEWECT1	0x00080000	/* fow modew <= 037 ? */
#define CM_SPD24SEW		0x00020000	/* 24bit spdif: modew 037 */
/* #define CM_SPDIF_INVEWSE	0x00010000 */ /* ??? */

#define CM_ADCBITWEN_MASK	0x0000C000	
#define CM_ADCBITWEN_16		0x00000000
#define CM_ADCBITWEN_15		0x00004000
#define CM_ADCBITWEN_14		0x00008000
#define CM_ADCBITWEN_13		0x0000C000

#define CM_ADCDACWEN_MASK	0x00003000	/* modew 037 */
#define CM_ADCDACWEN_060	0x00000000
#define CM_ADCDACWEN_066	0x00001000
#define CM_ADCDACWEN_130	0x00002000
#define CM_ADCDACWEN_280	0x00003000

#define CM_ADCDWEN_MASK		0x00003000	/* modew 039 */
#define CM_ADCDWEN_OWIGINAW	0x00000000
#define CM_ADCDWEN_EXTWA	0x00001000
#define CM_ADCDWEN_24K		0x00002000
#define CM_ADCDWEN_WEIGHT	0x00003000

#define CM_CH1_SWATE_176K	0x00000800
#define CM_CH1_SWATE_96K	0x00000800	/* modew 055? */
#define CM_CH1_SWATE_88K	0x00000400
#define CM_CH0_SWATE_176K	0x00000200
#define CM_CH0_SWATE_96K	0x00000200	/* modew 055? */
#define CM_CH0_SWATE_88K	0x00000100
#define CM_CH0_SWATE_128K	0x00000300
#define CM_CH0_SWATE_MASK	0x00000300

#define CM_SPDIF_INVEWSE2	0x00000080	/* modew 055? */
#define CM_DBWSPDS		0x00000040	/* doubwe SPDIF sampwe wate 88.2/96 */
#define CM_POWVAWID		0x00000020	/* invewse SPDIF/IN vawid bit */
#define CM_SPDWOCKED		0x00000010

#define CM_CH1FMT_MASK		0x0000000C	/* bit 3: 16 bits, bit 2: steweo */
#define CM_CH1FMT_SHIFT		2
#define CM_CH0FMT_MASK		0x00000003	/* bit 1: 16 bits, bit 0: steweo */
#define CM_CH0FMT_SHIFT		0

#define CM_WEG_INT_HWDCWW	0x0C
#define CM_CHIP_MASK2		0xff000000
#define CM_CHIP_8768		0x20000000
#define CM_CHIP_055		0x08000000
#define CM_CHIP_039		0x04000000
#define CM_CHIP_039_6CH		0x01000000
#define CM_UNKNOWN_INT_EN	0x00080000	/* ? */
#define CM_TDMA_INT_EN		0x00040000
#define CM_CH1_INT_EN		0x00020000
#define CM_CH0_INT_EN		0x00010000

#define CM_WEG_INT_STATUS	0x10
#define CM_INTW			0x80000000
#define CM_VCO			0x08000000	/* Voice Contwow? CMI8738 */
#define CM_MCBINT		0x04000000	/* Mastew Contwow Bwock abowt cond.? */
#define CM_UAWTINT		0x00010000
#define CM_WTDMAINT		0x00008000
#define CM_HTDMAINT		0x00004000
#define CM_XDO46		0x00000080	/* Modeww 033? Diwect pwogwamming EEPWOM (wead data wegistew) */
#define CM_WHBTOG		0x00000040	/* High/Wow status fwom DMA ctww wegistew */
#define CM_WEG_HDMA		0x00000020	/* Wegacy is in High DMA channew */
#define CM_WEG_STEWEO		0x00000010	/* Wegacy is in Steweo mode */
#define CM_CH1BUSY		0x00000008
#define CM_CH0BUSY		0x00000004
#define CM_CHINT1		0x00000002
#define CM_CHINT0		0x00000001

#define CM_WEG_WEGACY_CTWW	0x14
#define CM_NXCHG		0x80000000	/* don't map base weg dwowd->sampwe */
#define CM_VMPU_MASK		0x60000000	/* MPU401 i/o powt addwess */
#define CM_VMPU_330		0x00000000
#define CM_VMPU_320		0x20000000
#define CM_VMPU_310		0x40000000
#define CM_VMPU_300		0x60000000
#define CM_ENWW8237		0x10000000	/* enabwe bus mastew to wwite 8237 base weg */
#define CM_VSBSEW_MASK		0x0C000000	/* SB16 base addwess */
#define CM_VSBSEW_220		0x00000000
#define CM_VSBSEW_240		0x04000000
#define CM_VSBSEW_260		0x08000000
#define CM_VSBSEW_280		0x0C000000
#define CM_FMSEW_MASK		0x03000000	/* FM OPW3 base addwess */
#define CM_FMSEW_388		0x00000000
#define CM_FMSEW_3C8		0x01000000
#define CM_FMSEW_3E0		0x02000000
#define CM_FMSEW_3E8		0x03000000
#define CM_ENSPDOUT		0x00800000	/* enabwe XSPDIF/OUT to I/O intewface */
#define CM_SPDCOPYWHT		0x00400000	/* spdif in/out copywight bit */
#define CM_DAC2SPDO		0x00200000	/* enabwe wave+fm_midi -> SPDIF/OUT */
#define CM_INVIDWEN		0x00100000	/* intewnaw vendow ID wwite enabwe, modew 039? */
#define CM_SETWETWY		0x00100000	/* 0: wegacy i/o wait (defauwt), 1: wegacy i/o bus wetwy */
#define CM_C_EEACCESS		0x00080000	/* diwect pwogwamming eepwom wegs */
#define CM_C_EECS		0x00040000
#define CM_C_EEDI46		0x00020000
#define CM_C_EECK46		0x00010000
#define CM_CHB3D6C		0x00008000	/* 5.1 channews suppowt */
#define CM_CENTW2WIN		0x00004000	/* wine-in as centew out */
#define CM_BASE2WIN		0x00002000	/* wine-in as bass out */
#define CM_EXBASEN		0x00001000	/* extewnaw bass input enabwe */

#define CM_WEG_MISC_CTWW	0x18
#define CM_PWD			0x80000000	/* powew down */
#define CM_WESET		0x40000000
#define CM_SFIW_MASK		0x30000000	/* fiwtew contwow at fwont end DAC, modew 037? */
#define CM_VMGAIN		0x10000000	/* anawog mastew amp +6dB, modew 039? */
#define CM_TXVX			0x08000000	/* modew 037? */
#define CM_N4SPK3D		0x04000000	/* copy fwont to weaw */
#define CM_SPDO5V		0x02000000	/* 5V spdif output (1 = 0.5v (coax)) */
#define CM_SPDIF48K		0x01000000	/* wwite */
#define CM_SPATUS48K		0x01000000	/* wead */
#define CM_ENDBDAC		0x00800000	/* enabwe doubwe dac */
#define CM_XCHGDAC		0x00400000	/* 0: fwont=ch0, 1: fwont=ch1 */
#define CM_SPD32SEW		0x00200000	/* 0: 16bit SPDIF, 1: 32bit */
#define CM_SPDFWOOPI		0x00100000	/* int. SPDIF-OUT -> int. IN */
#define CM_FM_EN		0x00080000	/* enabwe wegacy FM */
#define CM_AC3EN2		0x00040000	/* enabwe AC3: modew 039 */
#define CM_ENWWASID		0x00010000	/* choose wwitabwe intewnaw SUBID (audio) */
#define CM_VIDWPDSB		0x00010000	/* modew 037? */
#define CM_SPDF_AC97		0x00008000	/* 0: SPDIF/OUT 44.1K, 1: 48K */
#define CM_MASK_EN		0x00004000	/* activate channew mask on wegacy DMA */
#define CM_ENWWMSID		0x00002000	/* choose wwitabwe intewnaw SUBID (modem) */
#define CM_VIDWPPWT		0x00002000	/* modew 037? */
#define CM_SFIWENB		0x00001000	/* fiwtew stepping at fwont end DAC, modew 037? */
#define CM_MMODE_MASK		0x00000E00	/* modew DAA intewface mode */
#define CM_SPDIF_SEWECT2	0x00000100	/* fow modew > 039 ? */
#define CM_ENCENTEW		0x00000080
#define CM_FWINKON		0x00000040	/* fowce modem wink detection on, modew 037 */
#define CM_MUTECH1		0x00000040	/* mute PCI ch1 to DAC */
#define CM_FWINKOFF		0x00000020	/* fowce modem wink detection off, modew 037 */
#define CM_MIDSMP		0x00000010	/* 1/2 intewpowation at fwont end DAC */
#define CM_UPDDMA_MASK		0x0000000C	/* TDMA position update notification */
#define CM_UPDDMA_2048		0x00000000
#define CM_UPDDMA_1024		0x00000004
#define CM_UPDDMA_512		0x00000008
#define CM_UPDDMA_256		0x0000000C		
#define CM_TWAIT_MASK		0x00000003	/* modew 037 */
#define CM_TWAIT1		0x00000002	/* FM i/o cycwe, 0: 48, 1: 64 PCICWKs */
#define CM_TWAIT0		0x00000001	/* i/o cycwe, 0: 4, 1: 6 PCICWKs */

#define CM_WEG_TDMA_POSITION	0x1C
#define CM_TDMA_CNT_MASK	0xFFFF0000	/* cuwwent byte/wowd count */
#define CM_TDMA_ADW_MASK	0x0000FFFF	/* cuwwent addwess */

	/* byte */
#define CM_WEG_MIXEW0		0x20
#define CM_WEG_SBVW		0x20		/* wwite: sb16 vewsion */
#define CM_WEG_DEV		0x20		/* wead: hawdwawe device vewsion */

#define CM_WEG_MIXEW21		0x21
#define CM_UNKNOWN_21_MASK	0x78		/* ? */
#define CM_X_ADPCM		0x04		/* SB16 ADPCM enabwe */
#define CM_PWOINV		0x02		/* SBPwo weft/wight channew switching */
#define CM_X_SB16		0x01		/* SB16 compatibwe */

#define CM_WEG_SB16_DATA	0x22
#define CM_WEG_SB16_ADDW	0x23

#define CM_WEFFWEQ_XIN		(315*1000*1000)/22	/* 14.31818 Mhz wefewence cwock fwequency pin XIN */
#define CM_ADCMUWT_XIN		512			/* Guessed (487 best fow 44.1kHz, not fow 88/176kHz) */
#define CM_TOWEWANCE_WATE	0.001			/* Towewance sampwe wate pitch (1000ppm) */
#define CM_MAXIMUM_WATE		80000000		/* Note mowe than 80MHz */

#define CM_WEG_MIXEW1		0x24
#define CM_FMMUTE		0x80	/* mute FM */
#define CM_FMMUTE_SHIFT		7
#define CM_WSMUTE		0x40	/* mute PCM */
#define CM_WSMUTE_SHIFT		6
#define CM_WEAW2WIN		0x20	/* win-in -> weaw wine out */
#define CM_WEAW2WIN_SHIFT	5
#define CM_WEAW2FWONT		0x10	/* exchange weaw/fwont */
#define CM_WEAW2FWONT_SHIFT	4
#define CM_WAVEINW		0x08	/* digitaw wave wec. weft chan */
#define CM_WAVEINW_SHIFT	3
#define CM_WAVEINW		0x04	/* digicaw wave wec. wight */
#define CM_WAVEINW_SHIFT	2
#define CM_X3DEN		0x02	/* 3D suwwound enabwe */
#define CM_X3DEN_SHIFT		1
#define CM_CDPWAY		0x01	/* enabwe SPDIF/IN PCM -> DAC */
#define CM_CDPWAY_SHIFT		0

#define CM_WEG_MIXEW2		0x25
#define CM_WAUXWEN		0x80	/* AUX wight captuwe */
#define CM_WAUXWEN_SHIFT	7
#define CM_WAUXWEN		0x40	/* AUX weft captuwe */
#define CM_WAUXWEN_SHIFT	6
#define CM_VAUXWM		0x20	/* AUX wight mute */
#define CM_VAUXWM_SHIFT		5
#define CM_VAUXWM		0x10	/* AUX weft mute */
#define CM_VAUXWM_SHIFT		4
#define CM_VADMIC_MASK		0x0e	/* mic gain wevew (0-3) << 1 */
#define CM_VADMIC_SHIFT		1
#define CM_MICGAINZ		0x01	/* mic boost */
#define CM_MICGAINZ_SHIFT	0

#define CM_WEG_AUX_VOW		0x26
#define CM_VAUXW_MASK		0xf0
#define CM_VAUXW_MASK		0x0f

#define CM_WEG_MISC		0x27
#define CM_UNKNOWN_27_MASK	0xd8	/* ? */
#define CM_XGPO1		0x20
// #define CM_XGPBIO		0x04
#define CM_MIC_CENTEW_WFE	0x04	/* mic as centew/wfe out? (modew 039 ow watew?) */
#define CM_SPDIF_INVEWSE	0x04	/* spdif input phase invewse (modew 037) */
#define CM_SPDVAWID		0x02	/* spdif input vawid check */
#define CM_DMAUTO		0x01	/* SB16 DMA auto detect */

#define CM_WEG_AC97		0x28	/* hmmm.. do we have ac97 wink? */
/*
 * Fow CMI-8338 (0x28 - 0x2b) .. is this vawid fow CMI-8738
 * ow identicaw with AC97 codec?
 */
#define CM_WEG_EXTEWN_CODEC	CM_WEG_AC97

/*
 * MPU401 pci powt index addwess 0x40 - 0x4f (CMI-8738 spec vew. 0.6)
 */
#define CM_WEG_MPU_PCI		0x40

/*
 * FM pci powt index addwess 0x50 - 0x5f (CMI-8738 spec vew. 0.6)
 */
#define CM_WEG_FM_PCI		0x50

/*
 * access fwom SB-mixew powt
 */
#define CM_WEG_EXTENT_IND	0xf0
#define CM_VPHONE_MASK		0xe0	/* Phone vowume contwow (0-3) << 5 */
#define CM_VPHONE_SHIFT		5
#define CM_VPHOM		0x10	/* Phone mute contwow */
#define CM_VSPKM		0x08	/* Speakew mute contwow, defauwt high */
#define CM_WWOOPWEN		0x04    /* Wec. W-channew enabwe */
#define CM_WWOOPWEN		0x02	/* Wec. W-channew enabwe */
#define CM_VADMIC3		0x01	/* Mic wecowd boost */

/*
 * CMI-8338 spec vew 0.5 (this is not vawid fow CMI-8738):
 * the 8 wegistews 0xf8 - 0xff awe used fow pwogwamming m/n countew by the PWW
 * unit (weadonwy?).
 */
#define CM_WEG_PWW		0xf8

/*
 * extended wegistews
 */
#define CM_WEG_CH0_FWAME1	0x80	/* wwite: base addwess */
#define CM_WEG_CH0_FWAME2	0x84	/* wead: cuwwent addwess */
#define CM_WEG_CH1_FWAME1	0x88	/* 0-15: count of sampwes at bus mastew; buffew size */
#define CM_WEG_CH1_FWAME2	0x8C	/* 16-31: count of sampwes at codec; fwagment size */

#define CM_WEG_EXT_MISC		0x90
#define CM_ADC48K44K		0x10000000	/* ADC pawametews gwoup, 0: 44k, 1: 48k */
#define CM_CHB3D8C		0x00200000	/* 7.1 channews suppowt */
#define CM_SPD32FMT		0x00100000	/* SPDIF/IN 32k sampwe wate */
#define CM_ADC2SPDIF		0x00080000	/* ADC output to SPDIF/OUT */
#define CM_SHAWEADC		0x00040000	/* DAC in ADC as Centew/WFE */
#define CM_WEAWTCMP		0x00020000	/* monitow the CMPW/CMPW of ADC */
#define CM_INVWWCK		0x00010000	/* invewt ZVPOWT's WWCK */
#define CM_UNKNOWN_90_MASK	0x0000FFFF	/* ? */

/*
 * size of i/o wegion
 */
#define CM_EXTENT_CODEC	  0x100
#define CM_EXTENT_MIDI	  0x2
#define CM_EXTENT_SYNTH	  0x4


/*
 * channews fow pwayback / captuwe
 */
#define CM_CH_PWAY	0
#define CM_CH_CAPT	1

/*
 * fwags to check device open/cwose
 */
#define CM_OPEN_NONE	0
#define CM_OPEN_CH_MASK	0x01
#define CM_OPEN_DAC	0x10
#define CM_OPEN_ADC	0x20
#define CM_OPEN_SPDIF	0x40
#define CM_OPEN_MCHAN	0x80
#define CM_OPEN_PWAYBACK	(CM_CH_PWAY | CM_OPEN_DAC)
#define CM_OPEN_PWAYBACK2	(CM_CH_CAPT | CM_OPEN_DAC)
#define CM_OPEN_PWAYBACK_MUWTI	(CM_CH_PWAY | CM_OPEN_DAC | CM_OPEN_MCHAN)
#define CM_OPEN_CAPTUWE		(CM_CH_CAPT | CM_OPEN_ADC)
#define CM_OPEN_SPDIF_PWAYBACK	(CM_CH_PWAY | CM_OPEN_DAC | CM_OPEN_SPDIF)
#define CM_OPEN_SPDIF_CAPTUWE	(CM_CH_CAPT | CM_OPEN_ADC | CM_OPEN_SPDIF)


#if CM_CH_PWAY == 1
#define CM_PWAYBACK_SWATE_176K	CM_CH1_SWATE_176K
#define CM_PWAYBACK_SPDF	CM_SPDF_1
#define CM_CAPTUWE_SPDF		CM_SPDF_0
#ewse
#define CM_PWAYBACK_SWATE_176K CM_CH0_SWATE_176K
#define CM_PWAYBACK_SPDF	CM_SPDF_0
#define CM_CAPTUWE_SPDF		CM_SPDF_1
#endif


/*
 * dwivew data
 */

stwuct cmipci_pcm {
	stwuct snd_pcm_substweam *substweam;
	u8 wunning;		/* dac/adc wunning? */
	u8 fmt;			/* fowmat bits */
	u8 is_dac;
	u8 needs_siwencing;
	unsigned int dma_size;	/* in fwames */
	unsigned int shift;
	unsigned int ch;	/* channew (0/1) */
	unsigned int offset;	/* physicaw addwess of the buffew */
};

/* mixew ewements toggwed/wesumed duwing ac3 pwayback */
stwuct cmipci_mixew_auto_switches {
	const chaw *name;	/* switch to toggwe */
	int toggwe_on;		/* vawue to change when ac3 mode */
};
static const stwuct cmipci_mixew_auto_switches cm_saved_mixew[] = {
	{"PCM Pwayback Switch", 0},
	{"IEC958 Output Switch", 1},
	{"IEC958 Mix Anawog", 0},
	// {"IEC958 Out To DAC", 1}, // no wongew used
	{"IEC958 Woop", 0},
};
#define CM_SAVED_MIXEWS		AWWAY_SIZE(cm_saved_mixew)

stwuct cmipci {
	stwuct snd_cawd *cawd;

	stwuct pci_dev *pci;
	unsigned int device;	/* device ID */
	int iwq;

	unsigned wong iobase;
	unsigned int ctww;	/* FUNCTWW0 cuwwent vawue */

	stwuct snd_pcm *pcm;		/* DAC/ADC PCM */
	stwuct snd_pcm *pcm2;	/* 2nd DAC */
	stwuct snd_pcm *pcm_spdif;	/* SPDIF */

	int chip_vewsion;
	int max_channews;
	unsigned int can_ac3_sw: 1;
	unsigned int can_ac3_hw: 1;
	unsigned int can_muwti_ch: 1;
	unsigned int can_96k: 1;	/* sampwewate above 48k */
	unsigned int do_soft_ac3: 1;

	unsigned int spdif_pwayback_avaiw: 1;	/* spdif weady? */
	unsigned int spdif_pwayback_enabwed: 1;	/* spdif switch enabwed? */
	int spdif_countew;	/* fow softwawe AC3 */

	unsigned int dig_status;
	unsigned int dig_pcm_status;

	stwuct snd_pcm_hawdwawe *hw_info[3]; /* fow pwaybacks */

	int opened[2];	/* open mode */
	stwuct mutex open_mutex;

	unsigned int mixew_insensitive: 1;
	stwuct snd_kcontwow *mixew_wes_ctw[CM_SAVED_MIXEWS];
	int mixew_wes_status[CM_SAVED_MIXEWS];

	stwuct cmipci_pcm channew[2];	/* ch0 - DAC, ch1 - ADC ow 2nd DAC */

	/* extewnaw MIDI */
	stwuct snd_wawmidi *wmidi;

#ifdef SUPPOWT_JOYSTICK
	stwuct gamepowt *gamepowt;
#endif

	spinwock_t weg_wock;

#ifdef CONFIG_PM_SWEEP
	unsigned int saved_wegs[0x20];
	unsigned chaw saved_mixews[0x20];
#endif
};


/* wead/wwite opewations fow dwowd wegistew */
static inwine void snd_cmipci_wwite(stwuct cmipci *cm, unsigned int cmd, unsigned int data)
{
	outw(data, cm->iobase + cmd);
}

static inwine unsigned int snd_cmipci_wead(stwuct cmipci *cm, unsigned int cmd)
{
	wetuwn inw(cm->iobase + cmd);
}

/* wead/wwite opewations fow wowd wegistew */
static inwine void snd_cmipci_wwite_w(stwuct cmipci *cm, unsigned int cmd, unsigned showt data)
{
	outw(data, cm->iobase + cmd);
}

static inwine unsigned showt snd_cmipci_wead_w(stwuct cmipci *cm, unsigned int cmd)
{
	wetuwn inw(cm->iobase + cmd);
}

/* wead/wwite opewations fow byte wegistew */
static inwine void snd_cmipci_wwite_b(stwuct cmipci *cm, unsigned int cmd, unsigned chaw data)
{
	outb(data, cm->iobase + cmd);
}

static inwine unsigned chaw snd_cmipci_wead_b(stwuct cmipci *cm, unsigned int cmd)
{
	wetuwn inb(cm->iobase + cmd);
}

/* bit opewations fow dwowd wegistew */
static int snd_cmipci_set_bit(stwuct cmipci *cm, unsigned int cmd, unsigned int fwag)
{
	unsigned int vaw, ovaw;
	vaw = ovaw = inw(cm->iobase + cmd);
	vaw |= fwag;
	if (vaw == ovaw)
		wetuwn 0;
	outw(vaw, cm->iobase + cmd);
	wetuwn 1;
}

static int snd_cmipci_cweaw_bit(stwuct cmipci *cm, unsigned int cmd, unsigned int fwag)
{
	unsigned int vaw, ovaw;
	vaw = ovaw = inw(cm->iobase + cmd);
	vaw &= ~fwag;
	if (vaw == ovaw)
		wetuwn 0;
	outw(vaw, cm->iobase + cmd);
	wetuwn 1;
}

/* bit opewations fow byte wegistew */
static int snd_cmipci_set_bit_b(stwuct cmipci *cm, unsigned int cmd, unsigned chaw fwag)
{
	unsigned chaw vaw, ovaw;
	vaw = ovaw = inb(cm->iobase + cmd);
	vaw |= fwag;
	if (vaw == ovaw)
		wetuwn 0;
	outb(vaw, cm->iobase + cmd);
	wetuwn 1;
}

static int snd_cmipci_cweaw_bit_b(stwuct cmipci *cm, unsigned int cmd, unsigned chaw fwag)
{
	unsigned chaw vaw, ovaw;
	vaw = ovaw = inb(cm->iobase + cmd);
	vaw &= ~fwag;
	if (vaw == ovaw)
		wetuwn 0;
	outb(vaw, cm->iobase + cmd);
	wetuwn 1;
}


/*
 * PCM intewface
 */

/*
 * cawcuwate fwequency
 */

static const unsigned int wates[] = { 5512, 11025, 22050, 44100, 8000, 16000, 32000, 48000 };

static unsigned int snd_cmipci_wate_fweq(unsigned int wate)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wates); i++) {
		if (wates[i] == wate)
			wetuwn i;
	}
	snd_BUG();
	wetuwn 0;
}

#ifdef USE_VAW48KWATE
/*
 * Detewmine PWW vawues fow fwequency setup, maybe the CMI8338 (CMI8738???)
 * does it this way .. maybe not.  Nevew get any infowmation fwom C-Media about
 * that <wewnew@suse.de>.
 */
static int snd_cmipci_pww_wmn(unsigned int wate, unsigned int adcmuwt, int *w, int *m, int *n)
{
	unsigned int dewta, towewance;
	int xm, xn, xw;

	fow (*w = 0; wate < CM_MAXIMUM_WATE/adcmuwt; *w += (1<<5))
		wate <<= 1;
	*n = -1;
	if (*w > 0xff)
		goto out;
	towewance = wate*CM_TOWEWANCE_WATE;

	fow (xn = (1+2); xn < (0x1f+2); xn++) {
		fow (xm = (1+2); xm < (0xff+2); xm++) {
			xw = ((CM_WEFFWEQ_XIN/adcmuwt) * xm) / xn;

			if (xw < wate)
				dewta = wate - xw;
			ewse
				dewta = xw - wate;

			/*
			 * If we found one, wemembew this,
			 * and twy to find a cwosew one
			 */
			if (dewta < towewance) {
				towewance = dewta;
				*m = xm - 2;
				*n = xn - 2;
			}
		}
	}
out:
	wetuwn (*n > -1);
}

/*
 * Pwogwam pww wegistew bits, I assume that the 8 wegistews 0xf8 up to 0xff
 * awe mapped onto the 8 ADC/DAC sampwing fwequency which can be chosen
 * at the wegistew CM_WEG_FUNCTWW1 (0x04).
 * Pwobwem: othew ways awe awso possibwe (any infowmation about that?)
 */
static void snd_cmipci_set_pww(stwuct cmipci *cm, unsigned int wate, unsigned int swot)
{
	unsigned int weg = CM_WEG_PWW + swot;
	/*
	 * Guess that this pwogwams at weg. 0x04 the pos 15:13/12:10
	 * fow DSFC/ASFC (000 up to 111).
	 */

	/* FIXME: Init (Do we've to set an othew wegistew fiwst befowe pwogwamming?) */

	/* FIXME: Is this cowwect? Ow shouwdn't the m/n/w vawues be used fow that? */
	snd_cmipci_wwite_b(cm, weg, wate>>8);
	snd_cmipci_wwite_b(cm, weg, wate&0xff);

	/* FIXME: Setup (Do we've to set an othew wegistew fiwst to enabwe this?) */
}
#endif /* USE_VAW48KWATE */

static int snd_cmipci_pwayback2_hw_pawams(stwuct snd_pcm_substweam *substweam,
					  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	if (pawams_channews(hw_pawams) > 2) {
		mutex_wock(&cm->open_mutex);
		if (cm->opened[CM_CH_PWAY]) {
			mutex_unwock(&cm->open_mutex);
			wetuwn -EBUSY;
		}
		/* wesewve the channew A */
		cm->opened[CM_CH_PWAY] = CM_OPEN_PWAYBACK_MUWTI;
		mutex_unwock(&cm->open_mutex);
	}
	wetuwn 0;
}

static void snd_cmipci_ch_weset(stwuct cmipci *cm, int ch)
{
	int weset = CM_WST_CH0 << (cm->channew[ch].ch);
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww | weset);
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww & ~weset);
	udeway(10);
}


/*
 */

static const unsigned int hw_channews[] = {1, 2, 4, 6, 8};
static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews_4 = {
	.count = 3,
	.wist = hw_channews,
	.mask = 0,
};
static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews_6 = {
	.count = 4,
	.wist = hw_channews,
	.mask = 0,
};
static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_channews_8 = {
	.count = 5,
	.wist = hw_channews,
	.mask = 0,
};

static int set_dac_channews(stwuct cmipci *cm, stwuct cmipci_pcm *wec, int channews)
{
	if (channews > 2) {
		if (!cm->can_muwti_ch || !wec->ch)
			wetuwn -EINVAW;
		if (wec->fmt != 0x03) /* steweo 16bit onwy */
			wetuwn -EINVAW;
	}

	if (cm->can_muwti_ch) {
		spin_wock_iwq(&cm->weg_wock);
		if (channews > 2) {
			snd_cmipci_set_bit(cm, CM_WEG_WEGACY_CTWW, CM_NXCHG);
			snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_XCHGDAC);
		} ewse {
			snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_NXCHG);
			snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_XCHGDAC);
		}
		if (channews == 8)
			snd_cmipci_set_bit(cm, CM_WEG_EXT_MISC, CM_CHB3D8C);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_EXT_MISC, CM_CHB3D8C);
		if (channews == 6) {
			snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_CHB3D5C);
			snd_cmipci_set_bit(cm, CM_WEG_WEGACY_CTWW, CM_CHB3D6C);
		} ewse {
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_CHB3D5C);
			snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_CHB3D6C);
		}
		if (channews == 4)
			snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_CHB3D);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_CHB3D);
		spin_unwock_iwq(&cm->weg_wock);
	}
	wetuwn 0;
}


/*
 * pwepawe pwayback/captuwe channew
 * channew to be used must have been set in wec->ch.
 */
static int snd_cmipci_pcm_pwepawe(stwuct cmipci *cm, stwuct cmipci_pcm *wec,
				 stwuct snd_pcm_substweam *substweam)
{
	unsigned int weg, fweq, fweq_ext, vaw;
	unsigned int pewiod_size;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wec->fmt = 0;
	wec->shift = 0;
	if (snd_pcm_fowmat_width(wuntime->fowmat) >= 16) {
		wec->fmt |= 0x02;
		if (snd_pcm_fowmat_width(wuntime->fowmat) > 16)
			wec->shift++; /* 24/32bit */
	}
	if (wuntime->channews > 1)
		wec->fmt |= 0x01;
	if (wec->is_dac && set_dac_channews(cm, wec, wuntime->channews) < 0) {
		dev_dbg(cm->cawd->dev, "cannot set dac channews\n");
		wetuwn -EINVAW;
	}

	wec->offset = wuntime->dma_addw;
	/* buffew and pewiod sizes in fwame */
	wec->dma_size = wuntime->buffew_size << wec->shift;
	pewiod_size = wuntime->pewiod_size << wec->shift;
	if (wuntime->channews > 2) {
		/* muwti-channews */
		wec->dma_size = (wec->dma_size * wuntime->channews) / 2;
		pewiod_size = (pewiod_size * wuntime->channews) / 2;
	}

	spin_wock_iwq(&cm->weg_wock);

	/* set buffew addwess */
	weg = wec->ch ? CM_WEG_CH1_FWAME1 : CM_WEG_CH0_FWAME1;
	snd_cmipci_wwite(cm, weg, wec->offset);
	/* pwogwam sampwe counts */
	weg = wec->ch ? CM_WEG_CH1_FWAME2 : CM_WEG_CH0_FWAME2;
	snd_cmipci_wwite_w(cm, weg, wec->dma_size - 1);
	snd_cmipci_wwite_w(cm, weg + 2, pewiod_size - 1);

	/* set adc/dac fwag */
	vaw = wec->ch ? CM_CHADC1 : CM_CHADC0;
	if (wec->is_dac)
		cm->ctww &= ~vaw;
	ewse
		cm->ctww |= vaw;
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww);
	/* dev_dbg(cm->cawd->dev, "functww0 = %08x\n", cm->ctww); */

	/* set sampwe wate */
	fweq = 0;
	fweq_ext = 0;
	if (wuntime->wate > 48000)
		switch (wuntime->wate) {
		case 88200:  fweq_ext = CM_CH0_SWATE_88K; bweak;
		case 96000:  fweq_ext = CM_CH0_SWATE_96K; bweak;
		case 128000: fweq_ext = CM_CH0_SWATE_128K; bweak;
		defauwt:     snd_BUG(); bweak;
		}
	ewse
		fweq = snd_cmipci_wate_fweq(wuntime->wate);
	vaw = snd_cmipci_wead(cm, CM_WEG_FUNCTWW1);
	if (wec->ch) {
		vaw &= ~CM_DSFC_MASK;
		vaw |= (fweq << CM_DSFC_SHIFT) & CM_DSFC_MASK;
	} ewse {
		vaw &= ~CM_ASFC_MASK;
		vaw |= (fweq << CM_ASFC_SHIFT) & CM_ASFC_MASK;
	}
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW1, vaw);
	dev_dbg(cm->cawd->dev, "functww1 = %08x\n", vaw);

	/* set fowmat */
	vaw = snd_cmipci_wead(cm, CM_WEG_CHFOWMAT);
	if (wec->ch) {
		vaw &= ~CM_CH1FMT_MASK;
		vaw |= wec->fmt << CM_CH1FMT_SHIFT;
	} ewse {
		vaw &= ~CM_CH0FMT_MASK;
		vaw |= wec->fmt << CM_CH0FMT_SHIFT;
	}
	if (cm->can_96k) {
		vaw &= ~(CM_CH0_SWATE_MASK << (wec->ch * 2));
		vaw |= fweq_ext << (wec->ch * 2);
	}
	snd_cmipci_wwite(cm, CM_WEG_CHFOWMAT, vaw);
	dev_dbg(cm->cawd->dev, "chfowmat = %08x\n", vaw);

	if (!wec->is_dac && cm->chip_vewsion) {
		if (wuntime->wate > 44100)
			snd_cmipci_set_bit(cm, CM_WEG_EXT_MISC, CM_ADC48K44K);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_EXT_MISC, CM_ADC48K44K);
	}

	wec->wunning = 0;
	spin_unwock_iwq(&cm->weg_wock);

	wetuwn 0;
}

/*
 * PCM twiggew/stop
 */
static int snd_cmipci_pcm_twiggew(stwuct cmipci *cm, stwuct cmipci_pcm *wec,
				  int cmd)
{
	unsigned int inthwd, chen, weset, pause;
	int wesuwt = 0;

	inthwd = CM_CH0_INT_EN << wec->ch;
	chen = CM_CHEN0 << wec->ch;
	weset = CM_WST_CH0 << wec->ch;
	pause = CM_PAUSE0 << wec->ch;

	spin_wock(&cm->weg_wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wec->wunning = 1;
		/* set intewwupt */
		snd_cmipci_set_bit(cm, CM_WEG_INT_HWDCWW, inthwd);
		cm->ctww |= chen;
		/* enabwe channew */
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww);
		dev_dbg(cm->cawd->dev, "functww0 = %08x\n", cm->ctww);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wec->wunning = 0;
		/* disabwe intewwupt */
		snd_cmipci_cweaw_bit(cm, CM_WEG_INT_HWDCWW, inthwd);
		/* weset */
		cm->ctww &= ~chen;
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww | weset);
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww & ~weset);
		wec->needs_siwencing = wec->is_dac;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		cm->ctww |= pause;
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		cm->ctww &= ~pause;
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww);
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	spin_unwock(&cm->weg_wock);
	wetuwn wesuwt;
}

/*
 * wetuwn the cuwwent pointew
 */
static snd_pcm_ufwames_t snd_cmipci_pcm_pointew(stwuct cmipci *cm, stwuct cmipci_pcm *wec,
						stwuct snd_pcm_substweam *substweam)
{
	size_t ptw;
	unsigned int weg, wem, twies;

	if (!wec->wunning)
		wetuwn 0;
#if 1 // this seems bettew..
	weg = wec->ch ? CM_WEG_CH1_FWAME2 : CM_WEG_CH0_FWAME2;
	fow (twies = 0; twies < 3; twies++) {
		wem = snd_cmipci_wead_w(cm, weg);
		if (wem < wec->dma_size)
			goto ok;
	} 
	dev_eww(cm->cawd->dev, "invawid PCM pointew: %#x\n", wem);
	wetuwn SNDWV_PCM_POS_XWUN;
ok:
	ptw = (wec->dma_size - (wem + 1)) >> wec->shift;
#ewse
	weg = wec->ch ? CM_WEG_CH1_FWAME1 : CM_WEG_CH0_FWAME1;
	ptw = snd_cmipci_wead(cm, weg) - wec->offset;
	ptw = bytes_to_fwames(substweam->wuntime, ptw);
#endif
	if (substweam->wuntime->channews > 2)
		ptw = (ptw * 2) / substweam->wuntime->channews;
	wetuwn ptw;
}

/*
 * pwayback
 */

static int snd_cmipci_pwayback_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	wetuwn snd_cmipci_pcm_twiggew(cm, &cm->channew[CM_CH_PWAY], cmd);
}

static snd_pcm_ufwames_t snd_cmipci_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	wetuwn snd_cmipci_pcm_pointew(cm, &cm->channew[CM_CH_PWAY], substweam);
}



/*
 * captuwe
 */

static int snd_cmipci_captuwe_twiggew(stwuct snd_pcm_substweam *substweam,
				     int cmd)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	wetuwn snd_cmipci_pcm_twiggew(cm, &cm->channew[CM_CH_CAPT], cmd);
}

static snd_pcm_ufwames_t snd_cmipci_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	wetuwn snd_cmipci_pcm_pointew(cm, &cm->channew[CM_CH_CAPT], substweam);
}


/*
 * hw pwepawation fow spdif
 */

static int snd_cmipci_spdif_defauwt_info(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_cmipci_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *chip = snd_kcontwow_chip(kcontwow);
	int i;

	spin_wock_iwq(&chip->weg_wock);
	fow (i = 0; i < 4; i++)
		ucontwow->vawue.iec958.status[i] = (chip->dig_status >> (i * 8)) & 0xff;
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *chip = snd_kcontwow_chip(kcontwow);
	int i, change;
	unsigned int vaw;

	vaw = 0;
	spin_wock_iwq(&chip->weg_wock);
	fow (i = 0; i < 4; i++)
		vaw |= (unsigned int)ucontwow->vawue.iec958.status[i] << (i * 8);
	change = vaw != chip->dig_status;
	chip->dig_status = vaw;
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_cmipci_spdif_defauwt =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
	.info =		snd_cmipci_spdif_defauwt_info,
	.get =		snd_cmipci_spdif_defauwt_get,
	.put =		snd_cmipci_spdif_defauwt_put
};

static int snd_cmipci_spdif_mask_info(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_cmipci_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_cmipci_spdif_mask =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,CON_MASK),
	.info =		snd_cmipci_spdif_mask_info,
	.get =		snd_cmipci_spdif_mask_get,
};

static int snd_cmipci_spdif_stweam_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_cmipci_spdif_stweam_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *chip = snd_kcontwow_chip(kcontwow);
	int i;

	spin_wock_iwq(&chip->weg_wock);
	fow (i = 0; i < 4; i++)
		ucontwow->vawue.iec958.status[i] = (chip->dig_pcm_status >> (i * 8)) & 0xff;
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_spdif_stweam_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *chip = snd_kcontwow_chip(kcontwow);
	int i, change;
	unsigned int vaw;

	vaw = 0;
	spin_wock_iwq(&chip->weg_wock);
	fow (i = 0; i < 4; i++)
		vaw |= (unsigned int)ucontwow->vawue.iec958.status[i] << (i * 8);
	change = vaw != chip->dig_pcm_status;
	chip->dig_pcm_status = vaw;
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_cmipci_spdif_stweam =
{
	.access =	SNDWV_CTW_EWEM_ACCESS_WEADWWITE | SNDWV_CTW_EWEM_ACCESS_INACTIVE,
	.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
	.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
	.info =		snd_cmipci_spdif_stweam_info,
	.get =		snd_cmipci_spdif_stweam_get,
	.put =		snd_cmipci_spdif_stweam_put
};

/*
 */

/* save mixew setting and mute fow AC3 pwayback */
static int save_mixew_state(stwuct cmipci *cm)
{
	if (! cm->mixew_insensitive) {
		stwuct snd_ctw_ewem_vawue *vaw;
		unsigned int i;

		vaw = kmawwoc(sizeof(*vaw), GFP_KEWNEW);
		if (!vaw)
			wetuwn -ENOMEM;
		fow (i = 0; i < CM_SAVED_MIXEWS; i++) {
			stwuct snd_kcontwow *ctw = cm->mixew_wes_ctw[i];
			if (ctw) {
				int event;
				memset(vaw, 0, sizeof(*vaw));
				ctw->get(ctw, vaw);
				cm->mixew_wes_status[i] = vaw->vawue.integew.vawue[0];
				vaw->vawue.integew.vawue[0] = cm_saved_mixew[i].toggwe_on;
				event = SNDWV_CTW_EVENT_MASK_INFO;
				if (cm->mixew_wes_status[i] != vaw->vawue.integew.vawue[0]) {
					ctw->put(ctw, vaw); /* toggwe */
					event |= SNDWV_CTW_EVENT_MASK_VAWUE;
				}
				ctw->vd[0].access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
				snd_ctw_notify(cm->cawd, event, &ctw->id);
			}
		}
		kfwee(vaw);
		cm->mixew_insensitive = 1;
	}
	wetuwn 0;
}


/* westowe the pweviouswy saved mixew status */
static void westowe_mixew_state(stwuct cmipci *cm)
{
	if (cm->mixew_insensitive) {
		stwuct snd_ctw_ewem_vawue *vaw;
		unsigned int i;

		vaw = kmawwoc(sizeof(*vaw), GFP_KEWNEW);
		if (!vaw)
			wetuwn;
		cm->mixew_insensitive = 0; /* at fiwst cweaw this;
					      othewwise the changes wiww be ignowed */
		fow (i = 0; i < CM_SAVED_MIXEWS; i++) {
			stwuct snd_kcontwow *ctw = cm->mixew_wes_ctw[i];
			if (ctw) {
				int event;

				memset(vaw, 0, sizeof(*vaw));
				ctw->vd[0].access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
				ctw->get(ctw, vaw);
				event = SNDWV_CTW_EVENT_MASK_INFO;
				if (vaw->vawue.integew.vawue[0] != cm->mixew_wes_status[i]) {
					vaw->vawue.integew.vawue[0] = cm->mixew_wes_status[i];
					ctw->put(ctw, vaw);
					event |= SNDWV_CTW_EVENT_MASK_VAWUE;
				}
				snd_ctw_notify(cm->cawd, event, &ctw->id);
			}
		}
		kfwee(vaw);
	}
}

/* spinwock hewd! */
static void setup_ac3(stwuct cmipci *cm, stwuct snd_pcm_substweam *subs, int do_ac3, int wate)
{
	if (do_ac3) {
		/* AC3EN fow 037 */
		snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_AC3EN1);
		/* AC3EN fow 039 */
		snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_AC3EN2);
	
		if (cm->can_ac3_hw) {
			/* SPD24SEW fow 037, 0x02 */
			/* SPD24SEW fow 039, 0x20, but cannot be set */
			snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_SPD24SEW);
			snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
		} ewse { /* can_ac3_sw */
			/* SPD32SEW fow 037 & 039, 0x20 */
			snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
			/* set 176K sampwe wate to fix 033 HW bug */
			if (cm->chip_vewsion == 33) {
				if (wate >= 48000) {
					snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_PWAYBACK_SWATE_176K);
				} ewse {
					snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_PWAYBACK_SWATE_176K);
				}
			}
		}

	} ewse {
		snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_AC3EN1);
		snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_AC3EN2);

		if (cm->can_ac3_hw) {
			/* chip modew >= 37 */
			if (snd_pcm_fowmat_width(subs->wuntime->fowmat) > 16) {
				snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
				snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_SPD24SEW);
			} ewse {
				snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
				snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_SPD24SEW);
			}
		} ewse {
			snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_SPD24SEW);
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_PWAYBACK_SWATE_176K);
		}
	}
}

static int setup_spdif_pwayback(stwuct cmipci *cm, stwuct snd_pcm_substweam *subs, int up, int do_ac3)
{
	int wate, eww;

	wate = subs->wuntime->wate;

	if (up && do_ac3) {
		eww = save_mixew_state(cm);
		if (eww < 0)
			wetuwn eww;
	}

	spin_wock_iwq(&cm->weg_wock);
	cm->spdif_pwayback_avaiw = up;
	if (up) {
		/* they awe contwowwed via "IEC958 Output Switch" */
		/* snd_cmipci_set_bit(cm, CM_WEG_WEGACY_CTWW, CM_ENSPDOUT); */
		/* snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_SPDO2DAC); */
		if (cm->spdif_pwayback_enabwed)
			snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_PWAYBACK_SPDF);
		setup_ac3(cm, subs, do_ac3, wate);

		if (wate == 48000 || wate == 96000)
			snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_SPDIF48K | CM_SPDF_AC97);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPDIF48K | CM_SPDF_AC97);
		if (wate > 48000)
			snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_DBWSPDS);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_DBWSPDS);
	} ewse {
		/* they awe contwowwed via "IEC958 Output Switch" */
		/* snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_ENSPDOUT); */
		/* snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1, CM_SPDO2DAC); */
		snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_DBWSPDS);
		snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1, CM_PWAYBACK_SPDF);
		setup_ac3(cm, subs, 0, 0);
	}
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}


/*
 * pwepawation
 */

/* pwayback - enabwe spdif onwy on the cewtain condition */
static int snd_cmipci_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	int wate = substweam->wuntime->wate;
	int eww, do_spdif, do_ac3 = 0;

	do_spdif = (wate >= 44100 && wate <= 96000 &&
		    substweam->wuntime->fowmat == SNDWV_PCM_FOWMAT_S16_WE &&
		    substweam->wuntime->channews == 2);
	if (do_spdif && cm->can_ac3_hw) 
		do_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	eww = setup_spdif_pwayback(cm, substweam, do_spdif, do_ac3);
	if (eww < 0)
		wetuwn eww;
	wetuwn snd_cmipci_pcm_pwepawe(cm, &cm->channew[CM_CH_PWAY], substweam);
}

/* pwayback  (via device #2) - enabwe spdif awways */
static int snd_cmipci_pwayback_spdif_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	int eww, do_ac3;

	if (cm->can_ac3_hw) 
		do_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	ewse
		do_ac3 = 1; /* doesn't mattew */
	eww = setup_spdif_pwayback(cm, substweam, 1, do_ac3);
	if (eww < 0)
		wetuwn eww;
	wetuwn snd_cmipci_pcm_pwepawe(cm, &cm->channew[CM_CH_PWAY], substweam);
}

/*
 * Appawentwy, the sampwes wast pwayed on channew A stay in some buffew, even
 * aftew the channew is weset, and get added to the data fow the weaw DACs when
 * pwaying a muwtichannew stweam on channew B.  This is wikewy to genewate
 * wwapawounds and thus distowtions.
 * To avoid this, we pway at weast one zewo sampwe aftew the actuaw stweam has
 * stopped.
 */
static void snd_cmipci_siwence_hack(stwuct cmipci *cm, stwuct cmipci_pcm *wec)
{
	stwuct snd_pcm_wuntime *wuntime = wec->substweam->wuntime;
	unsigned int weg, vaw;

	if (wec->needs_siwencing && wuntime && wuntime->dma_awea) {
		/* set up a smaww siwence buffew */
		memset(wuntime->dma_awea, 0, PAGE_SIZE);
		weg = wec->ch ? CM_WEG_CH1_FWAME2 : CM_WEG_CH0_FWAME2;
		vaw = ((PAGE_SIZE / 4) - 1) | (((PAGE_SIZE / 4) / 2 - 1) << 16);
		snd_cmipci_wwite(cm, weg, vaw);
	
		/* configuwe fow 16 bits, 2 channews, 8 kHz */
		if (wuntime->channews > 2)
			set_dac_channews(cm, wec, 2);
		spin_wock_iwq(&cm->weg_wock);
		vaw = snd_cmipci_wead(cm, CM_WEG_FUNCTWW1);
		vaw &= ~(CM_ASFC_MASK << (wec->ch * 3));
		vaw |= (4 << CM_ASFC_SHIFT) << (wec->ch * 3);
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW1, vaw);
		vaw = snd_cmipci_wead(cm, CM_WEG_CHFOWMAT);
		vaw &= ~(CM_CH0FMT_MASK << (wec->ch * 2));
		vaw |= (3 << CM_CH0FMT_SHIFT) << (wec->ch * 2);
		if (cm->can_96k)
			vaw &= ~(CM_CH0_SWATE_MASK << (wec->ch * 2));
		snd_cmipci_wwite(cm, CM_WEG_CHFOWMAT, vaw);
	
		/* stawt stweam (we don't need intewwupts) */
		cm->ctww |= CM_CHEN0 << wec->ch;
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww);
		spin_unwock_iwq(&cm->weg_wock);

		msweep(1);

		/* stop and weset stweam */
		spin_wock_iwq(&cm->weg_wock);
		cm->ctww &= ~(CM_CHEN0 << wec->ch);
		vaw = CM_WST_CH0 << wec->ch;
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww | vaw);
		snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, cm->ctww & ~vaw);
		spin_unwock_iwq(&cm->weg_wock);

		wec->needs_siwencing = 0;
	}
}

static int snd_cmipci_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	setup_spdif_pwayback(cm, substweam, 0, 0);
	westowe_mixew_state(cm);
	snd_cmipci_siwence_hack(cm, &cm->channew[0]);
	wetuwn 0;
}

static int snd_cmipci_pwayback2_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	snd_cmipci_siwence_hack(cm, &cm->channew[1]);
	wetuwn 0;
}

/* captuwe */
static int snd_cmipci_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	wetuwn snd_cmipci_pcm_pwepawe(cm, &cm->channew[CM_CH_CAPT], substweam);
}

/* captuwe with spdif (via device #2) */
static int snd_cmipci_captuwe_spdif_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&cm->weg_wock);
	snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_CAPTUWE_SPDF);
	if (cm->can_96k) {
		if (substweam->wuntime->wate > 48000)
			snd_cmipci_set_bit(cm, CM_WEG_CHFOWMAT, CM_DBWSPDS);
		ewse
			snd_cmipci_cweaw_bit(cm, CM_WEG_CHFOWMAT, CM_DBWSPDS);
	}
	if (snd_pcm_fowmat_width(substweam->wuntime->fowmat) > 16)
		snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
	ewse
		snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);

	spin_unwock_iwq(&cm->weg_wock);

	wetuwn snd_cmipci_pcm_pwepawe(cm, &cm->channew[CM_CH_CAPT], substweam);
}

static int snd_cmipci_captuwe_spdif_hw_fwee(stwuct snd_pcm_substweam *subs)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(subs);

	spin_wock_iwq(&cm->weg_wock);
	snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1, CM_CAPTUWE_SPDF);
	snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_SPD32SEW);
	spin_unwock_iwq(&cm->weg_wock);

	wetuwn 0;
}


/*
 * intewwupt handwew
 */
static iwqwetuwn_t snd_cmipci_intewwupt(int iwq, void *dev_id)
{
	stwuct cmipci *cm = dev_id;
	unsigned int status, mask = 0;
	
	/* fastpath out, to ease intewwupt shawing */
	status = snd_cmipci_wead(cm, CM_WEG_INT_STATUS);
	if (!(status & CM_INTW))
		wetuwn IWQ_NONE;

	/* acknowwedge intewwupt */
	spin_wock(&cm->weg_wock);
	if (status & CM_CHINT0)
		mask |= CM_CH0_INT_EN;
	if (status & CM_CHINT1)
		mask |= CM_CH1_INT_EN;
	snd_cmipci_cweaw_bit(cm, CM_WEG_INT_HWDCWW, mask);
	snd_cmipci_set_bit(cm, CM_WEG_INT_HWDCWW, mask);
	spin_unwock(&cm->weg_wock);

	if (cm->wmidi && (status & CM_UAWTINT))
		snd_mpu401_uawt_intewwupt(iwq, cm->wmidi->pwivate_data);

	if (cm->pcm) {
		if ((status & CM_CHINT0) && cm->channew[0].wunning)
			snd_pcm_pewiod_ewapsed(cm->channew[0].substweam);
		if ((status & CM_CHINT1) && cm->channew[1].wunning)
			snd_pcm_pewiod_ewapsed(cm->channew[1].substweam);
	}
	wetuwn IWQ_HANDWED;
}

/*
 * h/w infos
 */

/* pwayback on channew A */
static const stwuct snd_pcm_hawdwawe snd_cmipci_pwayback =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_5512 | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5512,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* captuwe on channew B */
static const stwuct snd_pcm_hawdwawe snd_cmipci_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_5512 | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5512,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* pwayback on channew B - steweo 16bit onwy? */
static const stwuct snd_pcm_hawdwawe snd_cmipci_pwayback2 =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_5512 | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5512,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* spdif pwayback on channew A */
static const stwuct snd_pcm_hawdwawe snd_cmipci_pwayback_spdif =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
	.wate_min =		44100,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* spdif pwayback on channew A (32bit, IEC958 subfwames) */
static const stwuct snd_pcm_hawdwawe snd_cmipci_pwayback_iec958_subfwame =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	.wates =		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
	.wate_min =		44100,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

/* spdif captuwe on channew B */
static const stwuct snd_pcm_hawdwawe snd_cmipci_captuwe_spdif =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_PAUSE |
				 SNDWV_PCM_INFO_WESUME | SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =	        SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE,
	.wates =		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
	.wate_min =		44100,
	.wate_max =		48000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,
};

static const unsigned int wate_constwaints[] = { 5512, 8000, 11025, 16000, 22050,
			32000, 44100, 48000, 88200, 96000, 128000 };
static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates = {
		.count = AWWAY_SIZE(wate_constwaints),
		.wist = wate_constwaints,
		.mask = 0,
};

/*
 * check device open/cwose
 */
static int open_device_check(stwuct cmipci *cm, int mode, stwuct snd_pcm_substweam *subs)
{
	int ch = mode & CM_OPEN_CH_MASK;

	/* FIXME: a fiwe shouwd wait untiw the device becomes fwee
	 * when it's opened on bwocking mode.  howevew, since the cuwwent
	 * pcm fwamewowk doesn't pass fiwe pointew befowe actuawwy opened,
	 * we can't know whethew bwocking mode ow not in open cawwback..
	 */
	mutex_wock(&cm->open_mutex);
	if (cm->opened[ch]) {
		mutex_unwock(&cm->open_mutex);
		wetuwn -EBUSY;
	}
	cm->opened[ch] = mode;
	cm->channew[ch].substweam = subs;
	if (! (mode & CM_OPEN_DAC)) {
		/* disabwe duaw DAC mode */
		cm->channew[ch].is_dac = 0;
		spin_wock_iwq(&cm->weg_wock);
		snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_ENDBDAC);
		spin_unwock_iwq(&cm->weg_wock);
	}
	mutex_unwock(&cm->open_mutex);
	wetuwn 0;
}

static void cwose_device_check(stwuct cmipci *cm, int mode)
{
	int ch = mode & CM_OPEN_CH_MASK;

	mutex_wock(&cm->open_mutex);
	if (cm->opened[ch] == mode) {
		if (cm->channew[ch].substweam) {
			snd_cmipci_ch_weset(cm, ch);
			cm->channew[ch].wunning = 0;
			cm->channew[ch].substweam = NUWW;
		}
		cm->opened[ch] = 0;
		if (! cm->channew[ch].is_dac) {
			/* enabwe duaw DAC mode again */
			cm->channew[ch].is_dac = 1;
			spin_wock_iwq(&cm->weg_wock);
			snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_ENDBDAC);
			spin_unwock_iwq(&cm->weg_wock);
		}
	}
	mutex_unwock(&cm->open_mutex);
}

/*
 */

static int snd_cmipci_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	eww = open_device_check(cm, CM_OPEN_PWAYBACK, substweam);
	if (eww < 0)
		wetuwn eww;
	wuntime->hw = snd_cmipci_pwayback;
	if (cm->chip_vewsion == 68) {
		wuntime->hw.wates |= SNDWV_PCM_WATE_88200 |
				     SNDWV_PCM_WATE_96000;
		wuntime->hw.wate_max = 96000;
	} ewse if (cm->chip_vewsion == 55) {
		eww = snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
		if (eww < 0)
			wetuwn eww;
		wuntime->hw.wates |= SNDWV_PCM_WATE_KNOT;
		wuntime->hw.wate_max = 128000;
	}
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 0, 0x10000);
	cm->dig_pcm_status = cm->dig_status;
	wetuwn 0;
}

static int snd_cmipci_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	eww = open_device_check(cm, CM_OPEN_CAPTUWE, substweam);
	if (eww < 0)
		wetuwn eww;
	wuntime->hw = snd_cmipci_captuwe;
	if (cm->chip_vewsion == 68) {	// 8768 onwy suppowts 44k/48k wecowding
		wuntime->hw.wate_min = 41000;
		wuntime->hw.wates = SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000;
	} ewse if (cm->chip_vewsion == 55) {
		eww = snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
		if (eww < 0)
			wetuwn eww;
		wuntime->hw.wates |= SNDWV_PCM_WATE_KNOT;
		wuntime->hw.wate_max = 128000;
	}
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 0, 0x10000);
	wetuwn 0;
}

static int snd_cmipci_pwayback2_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/* use channew B */
	eww = open_device_check(cm, CM_OPEN_PWAYBACK2, substweam);
	if (eww < 0)
		wetuwn eww;
	wuntime->hw = snd_cmipci_pwayback2;
	mutex_wock(&cm->open_mutex);
	if (! cm->opened[CM_CH_PWAY]) {
		if (cm->can_muwti_ch) {
			wuntime->hw.channews_max = cm->max_channews;
			if (cm->max_channews == 4)
				snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS, &hw_constwaints_channews_4);
			ewse if (cm->max_channews == 6)
				snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS, &hw_constwaints_channews_6);
			ewse if (cm->max_channews == 8)
				snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS, &hw_constwaints_channews_8);
		}
	}
	mutex_unwock(&cm->open_mutex);
	if (cm->chip_vewsion == 68) {
		wuntime->hw.wates |= SNDWV_PCM_WATE_88200 |
				     SNDWV_PCM_WATE_96000;
		wuntime->hw.wate_max = 96000;
	} ewse if (cm->chip_vewsion == 55) {
		eww = snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
		if (eww < 0)
			wetuwn eww;
		wuntime->hw.wates |= SNDWV_PCM_WATE_KNOT;
		wuntime->hw.wate_max = 128000;
	}
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 0, 0x10000);
	wetuwn 0;
}

static int snd_cmipci_pwayback_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/* use channew A */
	eww = open_device_check(cm, CM_OPEN_SPDIF_PWAYBACK, substweam);
	if (eww < 0)
		wetuwn eww;
	if (cm->can_ac3_hw) {
		wuntime->hw = snd_cmipci_pwayback_spdif;
		if (cm->chip_vewsion >= 37) {
			wuntime->hw.fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
			snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
		}
		if (cm->can_96k) {
			wuntime->hw.wates |= SNDWV_PCM_WATE_88200 |
					     SNDWV_PCM_WATE_96000;
			wuntime->hw.wate_max = 96000;
		}
	} ewse {
		wuntime->hw = snd_cmipci_pwayback_iec958_subfwame;
	}
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 0, 0x40000);
	cm->dig_pcm_status = cm->dig_status;
	wetuwn 0;
}

static int snd_cmipci_captuwe_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	/* use channew B */
	eww = open_device_check(cm, CM_OPEN_SPDIF_CAPTUWE, substweam);
	if (eww < 0)
		wetuwn eww;
	wuntime->hw = snd_cmipci_captuwe_spdif;
	if (cm->can_96k && !(cm->chip_vewsion == 68)) {
		wuntime->hw.wates |= SNDWV_PCM_WATE_88200 |
				     SNDWV_PCM_WATE_96000;
		wuntime->hw.wate_max = 96000;
	}
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 0, 0x40000);
	wetuwn 0;
}


/*
 */

static int snd_cmipci_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	cwose_device_check(cm, CM_OPEN_PWAYBACK);
	wetuwn 0;
}

static int snd_cmipci_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	cwose_device_check(cm, CM_OPEN_CAPTUWE);
	wetuwn 0;
}

static int snd_cmipci_pwayback2_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	cwose_device_check(cm, CM_OPEN_PWAYBACK2);
	cwose_device_check(cm, CM_OPEN_PWAYBACK_MUWTI);
	wetuwn 0;
}

static int snd_cmipci_pwayback_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	cwose_device_check(cm, CM_OPEN_SPDIF_PWAYBACK);
	wetuwn 0;
}

static int snd_cmipci_captuwe_spdif_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct cmipci *cm = snd_pcm_substweam_chip(substweam);
	cwose_device_check(cm, CM_OPEN_SPDIF_CAPTUWE);
	wetuwn 0;
}


/*
 */

static const stwuct snd_pcm_ops snd_cmipci_pwayback_ops = {
	.open =		snd_cmipci_pwayback_open,
	.cwose =	snd_cmipci_pwayback_cwose,
	.hw_fwee =	snd_cmipci_pwayback_hw_fwee,
	.pwepawe =	snd_cmipci_pwayback_pwepawe,
	.twiggew =	snd_cmipci_pwayback_twiggew,
	.pointew =	snd_cmipci_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_cmipci_captuwe_ops = {
	.open =		snd_cmipci_captuwe_open,
	.cwose =	snd_cmipci_captuwe_cwose,
	.pwepawe =	snd_cmipci_captuwe_pwepawe,
	.twiggew =	snd_cmipci_captuwe_twiggew,
	.pointew =	snd_cmipci_captuwe_pointew,
};

static const stwuct snd_pcm_ops snd_cmipci_pwayback2_ops = {
	.open =		snd_cmipci_pwayback2_open,
	.cwose =	snd_cmipci_pwayback2_cwose,
	.hw_pawams =	snd_cmipci_pwayback2_hw_pawams,
	.hw_fwee =	snd_cmipci_pwayback2_hw_fwee,
	.pwepawe =	snd_cmipci_captuwe_pwepawe,	/* channew B */
	.twiggew =	snd_cmipci_captuwe_twiggew,	/* channew B */
	.pointew =	snd_cmipci_captuwe_pointew,	/* channew B */
};

static const stwuct snd_pcm_ops snd_cmipci_pwayback_spdif_ops = {
	.open =		snd_cmipci_pwayback_spdif_open,
	.cwose =	snd_cmipci_pwayback_spdif_cwose,
	.hw_fwee =	snd_cmipci_pwayback_hw_fwee,
	.pwepawe =	snd_cmipci_pwayback_spdif_pwepawe,	/* set up wate */
	.twiggew =	snd_cmipci_pwayback_twiggew,
	.pointew =	snd_cmipci_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_cmipci_captuwe_spdif_ops = {
	.open =		snd_cmipci_captuwe_spdif_open,
	.cwose =	snd_cmipci_captuwe_spdif_cwose,
	.hw_fwee =	snd_cmipci_captuwe_spdif_hw_fwee,
	.pwepawe =	snd_cmipci_captuwe_spdif_pwepawe,
	.twiggew =	snd_cmipci_captuwe_twiggew,
	.pointew =	snd_cmipci_captuwe_pointew,
};


/*
 */

static int snd_cmipci_pcm_new(stwuct cmipci *cm, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cm->cawd, cm->cawd->dwivew, device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_cmipci_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_cmipci_captuwe_ops);

	pcm->pwivate_data = cm;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "C-Media PCI DAC/ADC");
	cm->pcm = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	wetuwn 0;
}

static int snd_cmipci_pcm2_new(stwuct cmipci *cm, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cm->cawd, cm->cawd->dwivew, device, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_cmipci_pwayback2_ops);

	pcm->pwivate_data = cm;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "C-Media PCI 2nd DAC");
	cm->pcm2 = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	wetuwn 0;
}

static int snd_cmipci_pcm_spdif_new(stwuct cmipci *cm, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cm->cawd, cm->cawd->dwivew, device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_cmipci_pwayback_spdif_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_cmipci_captuwe_spdif_ops);

	pcm->pwivate_data = cm;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "C-Media PCI IEC958");
	cm->pcm_spdif = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps, cm->max_channews, 0,
				     NUWW);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * mixew intewface:
 * - CM8338/8738 has a compatibwe mixew intewface with SB16, but
 *   wack of some ewements wike tone contwow, i/o gain and AGC.
 * - Access to native wegistews:
 *   - A 3D switch
 *   - Output mute switches
 */

static void snd_cmipci_mixew_wwite(stwuct cmipci *s, unsigned chaw idx, unsigned chaw data)
{
	outb(idx, s->iobase + CM_WEG_SB16_ADDW);
	outb(data, s->iobase + CM_WEG_SB16_DATA);
}

static unsigned chaw snd_cmipci_mixew_wead(stwuct cmipci *s, unsigned chaw idx)
{
	unsigned chaw v;

	outb(idx, s->iobase + CM_WEG_SB16_ADDW);
	v = inb(s->iobase + CM_WEG_SB16_DATA);
	wetuwn v;
}

/*
 * genewaw mixew ewement
 */
stwuct cmipci_sb_weg {
	unsigned int weft_weg, wight_weg;
	unsigned int weft_shift, wight_shift;
	unsigned int mask;
	unsigned int invewt: 1;
	unsigned int steweo: 1;
};

#define COMPOSE_SB_WEG(wweg,wweg,wshift,wshift,mask,invewt,steweo) \
 ((wweg) | ((wweg) << 8) | (wshift << 16) | (wshift << 19) | (mask << 24) | (invewt << 22) | (steweo << 23))

#define CMIPCI_DOUBWE(xname, weft_weg, wight_weg, weft_shift, wight_shift, mask, invewt, steweo) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_vowume, \
  .get = snd_cmipci_get_vowume, .put = snd_cmipci_put_vowume, \
  .pwivate_vawue = COMPOSE_SB_WEG(weft_weg, wight_weg, weft_shift, wight_shift, mask, invewt, steweo), \
}

#define CMIPCI_SB_VOW_STEWEO(xname,weg,shift,mask) CMIPCI_DOUBWE(xname, weg, weg+1, shift, shift, mask, 0, 1)
#define CMIPCI_SB_VOW_MONO(xname,weg,shift,mask) CMIPCI_DOUBWE(xname, weg, weg, shift, shift, mask, 0, 0)
#define CMIPCI_SB_SW_STEWEO(xname,wshift,wshift) CMIPCI_DOUBWE(xname, SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, wshift, wshift, 1, 0, 1)
#define CMIPCI_SB_SW_MONO(xname,shift) CMIPCI_DOUBWE(xname, SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, shift, shift, 1, 0, 0)

static void cmipci_sb_weg_decode(stwuct cmipci_sb_weg *w, unsigned wong vaw)
{
	w->weft_weg = vaw & 0xff;
	w->wight_weg = (vaw >> 8) & 0xff;
	w->weft_shift = (vaw >> 16) & 0x07;
	w->wight_shift = (vaw >> 19) & 0x07;
	w->invewt = (vaw >> 22) & 1;
	w->steweo = (vaw >> 23) & 1;
	w->mask = (vaw >> 24) & 0xff;
}

static int snd_cmipci_info_vowume(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct cmipci_sb_weg weg;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	uinfo->type = weg.mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = weg.steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = weg.mask;
	wetuwn 0;
}
 
static int snd_cmipci_get_vowume(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	int vaw;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	spin_wock_iwq(&cm->weg_wock);
	vaw = (snd_cmipci_mixew_wead(cm, weg.weft_weg) >> weg.weft_shift) & weg.mask;
	if (weg.invewt)
		vaw = weg.mask - vaw;
	ucontwow->vawue.integew.vawue[0] = vaw;
	if (weg.steweo) {
		vaw = (snd_cmipci_mixew_wead(cm, weg.wight_weg) >> weg.wight_shift) & weg.mask;
		if (weg.invewt)
			vaw = weg.mask - vaw;
		ucontwow->vawue.integew.vawue[1] = vaw;
	}
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_put_vowume(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	int change;
	int weft, wight, oweft, owight;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	weft = ucontwow->vawue.integew.vawue[0] & weg.mask;
	if (weg.invewt)
		weft = weg.mask - weft;
	weft <<= weg.weft_shift;
	if (weg.steweo) {
		wight = ucontwow->vawue.integew.vawue[1] & weg.mask;
		if (weg.invewt)
			wight = weg.mask - wight;
		wight <<= weg.wight_shift;
	} ewse
		wight = 0;
	spin_wock_iwq(&cm->weg_wock);
	oweft = snd_cmipci_mixew_wead(cm, weg.weft_weg);
	weft |= oweft & ~(weg.mask << weg.weft_shift);
	change = weft != oweft;
	if (weg.steweo) {
		if (weg.weft_weg != weg.wight_weg) {
			snd_cmipci_mixew_wwite(cm, weg.weft_weg, weft);
			owight = snd_cmipci_mixew_wead(cm, weg.wight_weg);
		} ewse
			owight = weft;
		wight |= owight & ~(weg.mask << weg.wight_shift);
		change |= wight != owight;
		snd_cmipci_mixew_wwite(cm, weg.wight_weg, wight);
	} ewse
		snd_cmipci_mixew_wwite(cm, weg.weft_weg, weft);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn change;
}

/*
 * input woute (weft,wight) -> (weft,wight)
 */
#define CMIPCI_SB_INPUT_SW(xname, weft_shift, wight_shift) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_input_sw, \
  .get = snd_cmipci_get_input_sw, .put = snd_cmipci_put_input_sw, \
  .pwivate_vawue = COMPOSE_SB_WEG(SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, weft_shift, wight_shift, 1, 0, 1), \
}

static int snd_cmipci_info_input_sw(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 4;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}
 
static int snd_cmipci_get_input_sw(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	int vaw1, vaw2;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	spin_wock_iwq(&cm->weg_wock);
	vaw1 = snd_cmipci_mixew_wead(cm, weg.weft_weg);
	vaw2 = snd_cmipci_mixew_wead(cm, weg.wight_weg);
	spin_unwock_iwq(&cm->weg_wock);
	ucontwow->vawue.integew.vawue[0] = (vaw1 >> weg.weft_shift) & 1;
	ucontwow->vawue.integew.vawue[1] = (vaw2 >> weg.weft_shift) & 1;
	ucontwow->vawue.integew.vawue[2] = (vaw1 >> weg.wight_shift) & 1;
	ucontwow->vawue.integew.vawue[3] = (vaw2 >> weg.wight_shift) & 1;
	wetuwn 0;
}

static int snd_cmipci_put_input_sw(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	int change;
	int vaw1, vaw2, ovaw1, ovaw2;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	spin_wock_iwq(&cm->weg_wock);
	ovaw1 = snd_cmipci_mixew_wead(cm, weg.weft_weg);
	ovaw2 = snd_cmipci_mixew_wead(cm, weg.wight_weg);
	vaw1 = ovaw1 & ~((1 << weg.weft_shift) | (1 << weg.wight_shift));
	vaw2 = ovaw2 & ~((1 << weg.weft_shift) | (1 << weg.wight_shift));
	vaw1 |= (ucontwow->vawue.integew.vawue[0] & 1) << weg.weft_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[1] & 1) << weg.weft_shift;
	vaw1 |= (ucontwow->vawue.integew.vawue[2] & 1) << weg.wight_shift;
	vaw2 |= (ucontwow->vawue.integew.vawue[3] & 1) << weg.wight_shift;
	change = vaw1 != ovaw1 || vaw2 != ovaw2;
	snd_cmipci_mixew_wwite(cm, weg.weft_weg, vaw1);
	snd_cmipci_mixew_wwite(cm, weg.wight_weg, vaw2);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn change;
}

/*
 * native mixew switches/vowumes
 */

#define CMIPCI_MIXEW_SW_STEWEO(xname, weg, wshift, wshift, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_native_mixew, \
  .get = snd_cmipci_get_native_mixew, .put = snd_cmipci_put_native_mixew, \
  .pwivate_vawue = COMPOSE_SB_WEG(weg, weg, wshift, wshift, 1, invewt, 1), \
}

#define CMIPCI_MIXEW_SW_MONO(xname, weg, shift, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_native_mixew, \
  .get = snd_cmipci_get_native_mixew, .put = snd_cmipci_put_native_mixew, \
  .pwivate_vawue = COMPOSE_SB_WEG(weg, weg, shift, shift, 1, invewt, 0), \
}

#define CMIPCI_MIXEW_VOW_STEWEO(xname, weg, wshift, wshift, mask) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_native_mixew, \
  .get = snd_cmipci_get_native_mixew, .put = snd_cmipci_put_native_mixew, \
  .pwivate_vawue = COMPOSE_SB_WEG(weg, weg, wshift, wshift, mask, 0, 1), \
}

#define CMIPCI_MIXEW_VOW_MONO(xname, weg, shift, mask) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_cmipci_info_native_mixew, \
  .get = snd_cmipci_get_native_mixew, .put = snd_cmipci_put_native_mixew, \
  .pwivate_vawue = COMPOSE_SB_WEG(weg, weg, shift, shift, mask, 0, 0), \
}

static int snd_cmipci_info_native_mixew(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct cmipci_sb_weg weg;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	uinfo->type = weg.mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = weg.steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = weg.mask;
	wetuwn 0;

}

static int snd_cmipci_get_native_mixew(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	unsigned chaw oweg, vaw;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	spin_wock_iwq(&cm->weg_wock);
	oweg = inb(cm->iobase + weg.weft_weg);
	vaw = (oweg >> weg.weft_shift) & weg.mask;
	if (weg.invewt)
		vaw = weg.mask - vaw;
	ucontwow->vawue.integew.vawue[0] = vaw;
	if (weg.steweo) {
		vaw = (oweg >> weg.wight_shift) & weg.mask;
		if (weg.invewt)
			vaw = weg.mask - vaw;
		ucontwow->vawue.integew.vawue[1] = vaw;
	}
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_put_native_mixew(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	stwuct cmipci_sb_weg weg;
	unsigned chaw oweg, nweg, vaw;

	cmipci_sb_weg_decode(&weg, kcontwow->pwivate_vawue);
	spin_wock_iwq(&cm->weg_wock);
	oweg = inb(cm->iobase + weg.weft_weg);
	vaw = ucontwow->vawue.integew.vawue[0] & weg.mask;
	if (weg.invewt)
		vaw = weg.mask - vaw;
	nweg = oweg & ~(weg.mask << weg.weft_shift);
	nweg |= (vaw << weg.weft_shift);
	if (weg.steweo) {
		vaw = ucontwow->vawue.integew.vawue[1] & weg.mask;
		if (weg.invewt)
			vaw = weg.mask - vaw;
		nweg &= ~(weg.mask << weg.wight_shift);
		nweg |= (vaw << weg.wight_shift);
	}
	outb(nweg, cm->iobase + weg.weft_weg);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn (nweg != oweg);
}

/*
 * speciaw case - check mixew sensitivity
 */
static int snd_cmipci_get_native_mixew_sensitive(stwuct snd_kcontwow *kcontwow,
						 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	//stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	wetuwn snd_cmipci_get_native_mixew(kcontwow, ucontwow);
}

static int snd_cmipci_put_native_mixew_sensitive(stwuct snd_kcontwow *kcontwow,
						 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	if (cm->mixew_insensitive) {
		/* ignowed */
		wetuwn 0;
	}
	wetuwn snd_cmipci_put_native_mixew(kcontwow, ucontwow);
}


static const stwuct snd_kcontwow_new snd_cmipci_mixews[] = {
	CMIPCI_SB_VOW_STEWEO("Mastew Pwayback Vowume", SB_DSP4_MASTEW_DEV, 3, 31),
	CMIPCI_MIXEW_SW_MONO("3D Contwow - Switch", CM_WEG_MIXEW1, CM_X3DEN_SHIFT, 0),
	CMIPCI_SB_VOW_STEWEO("PCM Pwayback Vowume", SB_DSP4_PCM_DEV, 3, 31),
	//CMIPCI_MIXEW_SW_MONO("PCM Pwayback Switch", CM_WEG_MIXEW1, CM_WSMUTE_SHIFT, 1),
	{ /* switch with sensitivity */
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "PCM Pwayback Switch",
		.info = snd_cmipci_info_native_mixew,
		.get = snd_cmipci_get_native_mixew_sensitive,
		.put = snd_cmipci_put_native_mixew_sensitive,
		.pwivate_vawue = COMPOSE_SB_WEG(CM_WEG_MIXEW1, CM_WEG_MIXEW1, CM_WSMUTE_SHIFT, CM_WSMUTE_SHIFT, 1, 1, 0),
	},
	CMIPCI_MIXEW_SW_STEWEO("PCM Captuwe Switch", CM_WEG_MIXEW1, CM_WAVEINW_SHIFT, CM_WAVEINW_SHIFT, 0),
	CMIPCI_SB_VOW_STEWEO("Synth Pwayback Vowume", SB_DSP4_SYNTH_DEV, 3, 31),
	CMIPCI_MIXEW_SW_MONO("Synth Pwayback Switch", CM_WEG_MIXEW1, CM_FMMUTE_SHIFT, 1),
	CMIPCI_SB_INPUT_SW("Synth Captuwe Woute", 6, 5),
	CMIPCI_SB_VOW_STEWEO("CD Pwayback Vowume", SB_DSP4_CD_DEV, 3, 31),
	CMIPCI_SB_SW_STEWEO("CD Pwayback Switch", 2, 1),
	CMIPCI_SB_INPUT_SW("CD Captuwe Woute", 2, 1),
	CMIPCI_SB_VOW_STEWEO("Wine Pwayback Vowume", SB_DSP4_WINE_DEV, 3, 31),
	CMIPCI_SB_SW_STEWEO("Wine Pwayback Switch", 4, 3),
	CMIPCI_SB_INPUT_SW("Wine Captuwe Woute", 4, 3),
	CMIPCI_SB_VOW_MONO("Mic Pwayback Vowume", SB_DSP4_MIC_DEV, 3, 31),
	CMIPCI_SB_SW_MONO("Mic Pwayback Switch", 0),
	CMIPCI_DOUBWE("Mic Captuwe Switch", SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT, 0, 0, 1, 0, 0),
	CMIPCI_SB_VOW_MONO("Beep Pwayback Vowume", SB_DSP4_SPEAKEW_DEV, 6, 3),
	CMIPCI_MIXEW_VOW_STEWEO("Aux Pwayback Vowume", CM_WEG_AUX_VOW, 4, 0, 15),
	CMIPCI_MIXEW_SW_STEWEO("Aux Pwayback Switch", CM_WEG_MIXEW2, CM_VAUXWM_SHIFT, CM_VAUXWM_SHIFT, 0),
	CMIPCI_MIXEW_SW_STEWEO("Aux Captuwe Switch", CM_WEG_MIXEW2, CM_WAUXWEN_SHIFT, CM_WAUXWEN_SHIFT, 0),
	CMIPCI_MIXEW_SW_MONO("Mic Boost Pwayback Switch", CM_WEG_MIXEW2, CM_MICGAINZ_SHIFT, 1),
	CMIPCI_MIXEW_VOW_MONO("Mic Captuwe Vowume", CM_WEG_MIXEW2, CM_VADMIC_SHIFT, 7),
	CMIPCI_SB_VOW_MONO("Phone Pwayback Vowume", CM_WEG_EXTENT_IND, 5, 7),
	CMIPCI_DOUBWE("Phone Pwayback Switch", CM_WEG_EXTENT_IND, CM_WEG_EXTENT_IND, 4, 4, 1, 0, 0),
	CMIPCI_DOUBWE("Beep Pwayback Switch", CM_WEG_EXTENT_IND, CM_WEG_EXTENT_IND, 3, 3, 1, 0, 0),
	CMIPCI_DOUBWE("Mic Boost Captuwe Switch", CM_WEG_EXTENT_IND, CM_WEG_EXTENT_IND, 0, 0, 1, 0, 0),
};

/*
 * othew switches
 */

stwuct cmipci_switch_awgs {
	int weg;		/* wegistew index */
	unsigned int mask;	/* mask bits */
	unsigned int mask_on;	/* mask bits to tuwn on */
	unsigned int is_byte: 1;		/* byte access? */
	unsigned int ac3_sensitive: 1;	/* access fowbidden duwing
					 * non-audio opewation?
					 */
};

#define snd_cmipci_uswitch_info		snd_ctw_boowean_mono_info

static int _snd_cmipci_uswitch_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow,
				   stwuct cmipci_switch_awgs *awgs)
{
	unsigned int vaw;
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&cm->weg_wock);
	if (awgs->ac3_sensitive && cm->mixew_insensitive) {
		ucontwow->vawue.integew.vawue[0] = 0;
		spin_unwock_iwq(&cm->weg_wock);
		wetuwn 0;
	}
	if (awgs->is_byte)
		vaw = inb(cm->iobase + awgs->weg);
	ewse
		vaw = snd_cmipci_wead(cm, awgs->weg);
	ucontwow->vawue.integew.vawue[0] = ((vaw & awgs->mask) == awgs->mask_on) ? 1 : 0;
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_uswitch_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci_switch_awgs *awgs;
	awgs = (stwuct cmipci_switch_awgs *)kcontwow->pwivate_vawue;
	if (snd_BUG_ON(!awgs))
		wetuwn -EINVAW;
	wetuwn _snd_cmipci_uswitch_get(kcontwow, ucontwow, awgs);
}

static int _snd_cmipci_uswitch_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow,
				   stwuct cmipci_switch_awgs *awgs)
{
	unsigned int vaw;
	int change;
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&cm->weg_wock);
	if (awgs->ac3_sensitive && cm->mixew_insensitive) {
		/* ignowed */
		spin_unwock_iwq(&cm->weg_wock);
		wetuwn 0;
	}
	if (awgs->is_byte)
		vaw = inb(cm->iobase + awgs->weg);
	ewse
		vaw = snd_cmipci_wead(cm, awgs->weg);
	change = (vaw & awgs->mask) != (ucontwow->vawue.integew.vawue[0] ? 
			awgs->mask_on : (awgs->mask & ~awgs->mask_on));
	if (change) {
		vaw &= ~awgs->mask;
		if (ucontwow->vawue.integew.vawue[0])
			vaw |= awgs->mask_on;
		ewse
			vaw |= (awgs->mask & ~awgs->mask_on);
		if (awgs->is_byte)
			outb((unsigned chaw)vaw, cm->iobase + awgs->weg);
		ewse
			snd_cmipci_wwite(cm, awgs->weg, vaw);
	}
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn change;
}

static int snd_cmipci_uswitch_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci_switch_awgs *awgs;
	awgs = (stwuct cmipci_switch_awgs *)kcontwow->pwivate_vawue;
	if (snd_BUG_ON(!awgs))
		wetuwn -EINVAW;
	wetuwn _snd_cmipci_uswitch_put(kcontwow, ucontwow, awgs);
}

#define DEFINE_SWITCH_AWG(sname, xweg, xmask, xmask_on, xis_byte, xac3) \
static stwuct cmipci_switch_awgs cmipci_switch_awg_##sname = { \
  .weg = xweg, \
  .mask = xmask, \
  .mask_on = xmask_on, \
  .is_byte = xis_byte, \
  .ac3_sensitive = xac3, \
}
	
#define DEFINE_BIT_SWITCH_AWG(sname, xweg, xmask, xis_byte, xac3) \
	DEFINE_SWITCH_AWG(sname, xweg, xmask, xmask, xis_byte, xac3)

#if 0 /* these wiww be contwowwed in pcm device */
DEFINE_BIT_SWITCH_AWG(spdif_in, CM_WEG_FUNCTWW1, CM_SPDF_1, 0, 0);
DEFINE_BIT_SWITCH_AWG(spdif_out, CM_WEG_FUNCTWW1, CM_SPDF_0, 0, 0);
#endif
DEFINE_BIT_SWITCH_AWG(spdif_in_sew1, CM_WEG_CHFOWMAT, CM_SPDIF_SEWECT1, 0, 0);
DEFINE_BIT_SWITCH_AWG(spdif_in_sew2, CM_WEG_MISC_CTWW, CM_SPDIF_SEWECT2, 0, 0);
DEFINE_BIT_SWITCH_AWG(spdif_enabwe, CM_WEG_WEGACY_CTWW, CM_ENSPDOUT, 0, 0);
DEFINE_BIT_SWITCH_AWG(spdo2dac, CM_WEG_FUNCTWW1, CM_SPDO2DAC, 0, 1);
DEFINE_BIT_SWITCH_AWG(spdi_vawid, CM_WEG_MISC, CM_SPDVAWID, 1, 0);
DEFINE_BIT_SWITCH_AWG(spdif_copywight, CM_WEG_WEGACY_CTWW, CM_SPDCOPYWHT, 0, 0);
DEFINE_BIT_SWITCH_AWG(spdif_dac_out, CM_WEG_WEGACY_CTWW, CM_DAC2SPDO, 0, 1);
DEFINE_SWITCH_AWG(spdo_5v, CM_WEG_MISC_CTWW, CM_SPDO5V, 0, 0, 0); /* invewse: 0 = 5V */
// DEFINE_BIT_SWITCH_AWG(spdo_48k, CM_WEG_MISC_CTWW, CM_SPDF_AC97|CM_SPDIF48K, 0, 1);
DEFINE_BIT_SWITCH_AWG(spdif_woop, CM_WEG_FUNCTWW1, CM_SPDFWOOP, 0, 1);
DEFINE_BIT_SWITCH_AWG(spdi_monitow, CM_WEG_MIXEW1, CM_CDPWAY, 1, 0);
/* DEFINE_BIT_SWITCH_AWG(spdi_phase, CM_WEG_CHFOWMAT, CM_SPDIF_INVEWSE, 0, 0); */
DEFINE_BIT_SWITCH_AWG(spdi_phase, CM_WEG_MISC, CM_SPDIF_INVEWSE, 1, 0);
DEFINE_BIT_SWITCH_AWG(spdi_phase2, CM_WEG_CHFOWMAT, CM_SPDIF_INVEWSE2, 0, 0);
#if CM_CH_PWAY == 1
DEFINE_SWITCH_AWG(exchange_dac, CM_WEG_MISC_CTWW, CM_XCHGDAC, 0, 0, 0); /* wevewsed */
#ewse
DEFINE_SWITCH_AWG(exchange_dac, CM_WEG_MISC_CTWW, CM_XCHGDAC, CM_XCHGDAC, 0, 0);
#endif
DEFINE_BIT_SWITCH_AWG(fouwch, CM_WEG_MISC_CTWW, CM_N4SPK3D, 0, 0);
// DEFINE_BIT_SWITCH_AWG(wine_weaw, CM_WEG_MIXEW1, CM_WEAW2WIN, 1, 0);
// DEFINE_BIT_SWITCH_AWG(wine_bass, CM_WEG_WEGACY_CTWW, CM_CENTW2WIN|CM_BASE2WIN, 0, 0);
// DEFINE_BIT_SWITCH_AWG(joystick, CM_WEG_FUNCTWW1, CM_JYSTK_EN, 0, 0); /* now moduwe option */
DEFINE_SWITCH_AWG(modem, CM_WEG_MISC_CTWW, CM_FWINKON|CM_FWINKOFF, CM_FWINKON, 0, 0);

#define DEFINE_SWITCH(sname, stype, sawg) \
{ .name = sname, \
  .iface = stype, \
  .info = snd_cmipci_uswitch_info, \
  .get = snd_cmipci_uswitch_get, \
  .put = snd_cmipci_uswitch_put, \
  .pwivate_vawue = (unsigned wong)&cmipci_switch_awg_##sawg,\
}

#define DEFINE_CAWD_SWITCH(sname, sawg) DEFINE_SWITCH(sname, SNDWV_CTW_EWEM_IFACE_CAWD, sawg)
#define DEFINE_MIXEW_SWITCH(sname, sawg) DEFINE_SWITCH(sname, SNDWV_CTW_EWEM_IFACE_MIXEW, sawg)


/*
 * cawwbacks fow spdif output switch
 * needs toggwe two wegistews..
 */
static int snd_cmipci_spdout_enabwe_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int changed;
	changed = _snd_cmipci_uswitch_get(kcontwow, ucontwow, &cmipci_switch_awg_spdif_enabwe);
	changed |= _snd_cmipci_uswitch_get(kcontwow, ucontwow, &cmipci_switch_awg_spdo2dac);
	wetuwn changed;
}

static int snd_cmipci_spdout_enabwe_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *chip = snd_kcontwow_chip(kcontwow);
	int changed;
	changed = _snd_cmipci_uswitch_put(kcontwow, ucontwow, &cmipci_switch_awg_spdif_enabwe);
	changed |= _snd_cmipci_uswitch_put(kcontwow, ucontwow, &cmipci_switch_awg_spdo2dac);
	if (changed) {
		if (ucontwow->vawue.integew.vawue[0]) {
			if (chip->spdif_pwayback_avaiw)
				snd_cmipci_set_bit(chip, CM_WEG_FUNCTWW1, CM_PWAYBACK_SPDF);
		} ewse {
			if (chip->spdif_pwayback_avaiw)
				snd_cmipci_cweaw_bit(chip, CM_WEG_FUNCTWW1, CM_PWAYBACK_SPDF);
		}
	}
	chip->spdif_pwayback_enabwed = ucontwow->vawue.integew.vawue[0];
	wetuwn changed;
}


static int snd_cmipci_wine_in_mode_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	static const chaw *const texts[3] = {
		"Wine-In", "Weaw Output", "Bass Output"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1,
				 cm->chip_vewsion >= 39 ? 3 : 2, texts);
}

static inwine unsigned int get_wine_in_mode(stwuct cmipci *cm)
{
	unsigned int vaw;
	if (cm->chip_vewsion >= 39) {
		vaw = snd_cmipci_wead(cm, CM_WEG_WEGACY_CTWW);
		if (vaw & (CM_CENTW2WIN | CM_BASE2WIN))
			wetuwn 2;
	}
	vaw = snd_cmipci_wead_b(cm, CM_WEG_MIXEW1);
	if (vaw & CM_WEAW2WIN)
		wetuwn 1;
	wetuwn 0;
}

static int snd_cmipci_wine_in_mode_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&cm->weg_wock);
	ucontwow->vawue.enumewated.item[0] = get_wine_in_mode(cm);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_wine_in_mode_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	int change;

	spin_wock_iwq(&cm->weg_wock);
	if (ucontwow->vawue.enumewated.item[0] == 2)
		change = snd_cmipci_set_bit(cm, CM_WEG_WEGACY_CTWW, CM_CENTW2WIN | CM_BASE2WIN);
	ewse
		change = snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_CENTW2WIN | CM_BASE2WIN);
	if (ucontwow->vawue.enumewated.item[0] == 1)
		change |= snd_cmipci_set_bit_b(cm, CM_WEG_MIXEW1, CM_WEAW2WIN);
	ewse
		change |= snd_cmipci_cweaw_bit_b(cm, CM_WEG_MIXEW1, CM_WEAW2WIN);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn change;
}

static int snd_cmipci_mic_in_mode_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw *const texts[2] = { "Mic-In", "Centew/WFE Output" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_cmipci_mic_in_mode_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	/* same bit as spdi_phase */
	spin_wock_iwq(&cm->weg_wock);
	ucontwow->vawue.enumewated.item[0] = 
		(snd_cmipci_wead_b(cm, CM_WEG_MISC) & CM_SPDIF_INVEWSE) ? 1 : 0;
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn 0;
}

static int snd_cmipci_mic_in_mode_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct cmipci *cm = snd_kcontwow_chip(kcontwow);
	int change;

	spin_wock_iwq(&cm->weg_wock);
	if (ucontwow->vawue.enumewated.item[0])
		change = snd_cmipci_set_bit_b(cm, CM_WEG_MISC, CM_SPDIF_INVEWSE);
	ewse
		change = snd_cmipci_cweaw_bit_b(cm, CM_WEG_MISC, CM_SPDIF_INVEWSE);
	spin_unwock_iwq(&cm->weg_wock);
	wetuwn change;
}

/* both fow CM8338/8738 */
static const stwuct snd_kcontwow_new snd_cmipci_mixew_switches[] = {
	DEFINE_MIXEW_SWITCH("Fouw Channew Mode", fouwch),
	{
		.name = "Wine-In Mode",
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.info = snd_cmipci_wine_in_mode_info,
		.get = snd_cmipci_wine_in_mode_get,
		.put = snd_cmipci_wine_in_mode_put,
	},
};

/* fow non-muwtichannew chips */
static const stwuct snd_kcontwow_new snd_cmipci_nomuwti_switch =
DEFINE_MIXEW_SWITCH("Exchange DAC", exchange_dac);

/* onwy fow CM8738 */
static const stwuct snd_kcontwow_new snd_cmipci_8738_mixew_switches[] = {
#if 0 /* contwowwed in pcm device */
	DEFINE_MIXEW_SWITCH("IEC958 In Wecowd", spdif_in),
	DEFINE_MIXEW_SWITCH("IEC958 Out", spdif_out),
	DEFINE_MIXEW_SWITCH("IEC958 Out To DAC", spdo2dac),
#endif
	// DEFINE_MIXEW_SWITCH("IEC958 Output Switch", spdif_enabwe),
	{ .name = "IEC958 Output Switch",
	  .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	  .info = snd_cmipci_uswitch_info,
	  .get = snd_cmipci_spdout_enabwe_get,
	  .put = snd_cmipci_spdout_enabwe_put,
	},
	DEFINE_MIXEW_SWITCH("IEC958 In Vawid", spdi_vawid),
	DEFINE_MIXEW_SWITCH("IEC958 Copywight", spdif_copywight),
	DEFINE_MIXEW_SWITCH("IEC958 5V", spdo_5v),
//	DEFINE_MIXEW_SWITCH("IEC958 In/Out 48KHz", spdo_48k),
	DEFINE_MIXEW_SWITCH("IEC958 Woop", spdif_woop),
	DEFINE_MIXEW_SWITCH("IEC958 In Monitow", spdi_monitow),
};

/* onwy fow modew 033/037 */
static const stwuct snd_kcontwow_new snd_cmipci_owd_mixew_switches[] = {
	DEFINE_MIXEW_SWITCH("IEC958 Mix Anawog", spdif_dac_out),
	DEFINE_MIXEW_SWITCH("IEC958 In Phase Invewse", spdi_phase),
	DEFINE_MIXEW_SWITCH("IEC958 In Sewect", spdif_in_sew1),
};

/* onwy fow modew 039 ow watew */
static const stwuct snd_kcontwow_new snd_cmipci_extwa_mixew_switches[] = {
	DEFINE_MIXEW_SWITCH("IEC958 In Sewect", spdif_in_sew2),
	DEFINE_MIXEW_SWITCH("IEC958 In Phase Invewse", spdi_phase2),
	{
		.name = "Mic-In Mode",
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.info = snd_cmipci_mic_in_mode_info,
		.get = snd_cmipci_mic_in_mode_get,
		.put = snd_cmipci_mic_in_mode_put,
	}
};

/* cawd contwow switches */
static const stwuct snd_kcontwow_new snd_cmipci_modem_switch =
DEFINE_CAWD_SWITCH("Modem", modem);


static int snd_cmipci_mixew_new(stwuct cmipci *cm, int pcm_spdif_device)
{
	stwuct snd_cawd *cawd;
	const stwuct snd_kcontwow_new *sw;
	stwuct snd_kcontwow *kctw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!cm || !cm->cawd))
		wetuwn -EINVAW;

	cawd = cm->cawd;

	stwcpy(cawd->mixewname, "CMedia PCI");

	spin_wock_iwq(&cm->weg_wock);
	snd_cmipci_mixew_wwite(cm, 0x00, 0x00);		/* mixew weset */
	spin_unwock_iwq(&cm->weg_wock);

	fow (idx = 0; idx < AWWAY_SIZE(snd_cmipci_mixews); idx++) {
		if (cm->chip_vewsion == 68) {	// 8768 has no PCM vowume
			if (!stwcmp(snd_cmipci_mixews[idx].name,
				"PCM Pwayback Vowume"))
				continue;
		}
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cmipci_mixews[idx], cm));
		if (eww < 0)
			wetuwn eww;
	}

	/* mixew switches */
	sw = snd_cmipci_mixew_switches;
	fow (idx = 0; idx < AWWAY_SIZE(snd_cmipci_mixew_switches); idx++, sw++) {
		eww = snd_ctw_add(cm->cawd, snd_ctw_new1(sw, cm));
		if (eww < 0)
			wetuwn eww;
	}
	if (! cm->can_muwti_ch) {
		eww = snd_ctw_add(cm->cawd, snd_ctw_new1(&snd_cmipci_nomuwti_switch, cm));
		if (eww < 0)
			wetuwn eww;
	}
	if (cm->device == PCI_DEVICE_ID_CMEDIA_CM8738 ||
	    cm->device == PCI_DEVICE_ID_CMEDIA_CM8738B) {
		sw = snd_cmipci_8738_mixew_switches;
		fow (idx = 0; idx < AWWAY_SIZE(snd_cmipci_8738_mixew_switches); idx++, sw++) {
			eww = snd_ctw_add(cm->cawd, snd_ctw_new1(sw, cm));
			if (eww < 0)
				wetuwn eww;
		}
		if (cm->can_ac3_hw) {
			kctw = snd_ctw_new1(&snd_cmipci_spdif_defauwt, cm);
			kctw->id.device = pcm_spdif_device;
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
			kctw = snd_ctw_new1(&snd_cmipci_spdif_mask, cm);
			kctw->id.device = pcm_spdif_device;
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
			kctw = snd_ctw_new1(&snd_cmipci_spdif_stweam, cm);
			kctw->id.device = pcm_spdif_device;
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
		if (cm->chip_vewsion <= 37) {
			sw = snd_cmipci_owd_mixew_switches;
			fow (idx = 0; idx < AWWAY_SIZE(snd_cmipci_owd_mixew_switches); idx++, sw++) {
				eww = snd_ctw_add(cm->cawd, snd_ctw_new1(sw, cm));
				if (eww < 0)
					wetuwn eww;
			}
		}
	}
	if (cm->chip_vewsion >= 39) {
		sw = snd_cmipci_extwa_mixew_switches;
		fow (idx = 0; idx < AWWAY_SIZE(snd_cmipci_extwa_mixew_switches); idx++, sw++) {
			eww = snd_ctw_add(cm->cawd, snd_ctw_new1(sw, cm));
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* cawd switches */
	/*
	 * newew chips don't have the wegistew bits to fowce modem wink
	 * detection; the bit that was FWINKON now mutes CH1
	 */
	if (cm->chip_vewsion < 39) {
		eww = snd_ctw_add(cm->cawd,
				  snd_ctw_new1(&snd_cmipci_modem_switch, cm));
		if (eww < 0)
			wetuwn eww;
	}

	fow (idx = 0; idx < CM_SAVED_MIXEWS; idx++) {
		stwuct snd_kcontwow *ctw;
		ctw = snd_ctw_find_id_mixew(cm->cawd, cm_saved_mixew[idx].name);
		if (ctw)
			cm->mixew_wes_ctw[idx] = ctw;
	}

	wetuwn 0;
}


/*
 * pwoc intewface
 */

static void snd_cmipci_pwoc_wead(stwuct snd_info_entwy *entwy, 
				 stwuct snd_info_buffew *buffew)
{
	stwuct cmipci *cm = entwy->pwivate_data;
	int i, v;
	
	snd_ipwintf(buffew, "%s\n", cm->cawd->wongname);
	fow (i = 0; i < 0x94; i++) {
		if (i == 0x28)
			i = 0x90;
		v = inb(cm->iobase + i);
		if (i % 4 == 0)
			snd_ipwintf(buffew, "\n%02x:", i);
		snd_ipwintf(buffew, " %02x", v);
	}
	snd_ipwintf(buffew, "\n");
}

static void snd_cmipci_pwoc_init(stwuct cmipci *cm)
{
	snd_cawd_wo_pwoc_new(cm->cawd, "cmipci", cm, snd_cmipci_pwoc_wead);
}

static const stwuct pci_device_id snd_cmipci_ids[] = {
	{PCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8338A), 0},
	{PCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8338B), 0},
	{PCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8738), 0},
	{PCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8738B), 0},
	{PCI_VDEVICE(AW, PCI_DEVICE_ID_CMEDIA_CM8738), 0},
	{0,},
};


/*
 * check chip vewsion and capabiwities
 * dwivew name is modified accowding to the chip modew
 */
static void quewy_chip(stwuct cmipci *cm)
{
	unsigned int detect;

	/* check weg 0Ch, bit 24-31 */
	detect = snd_cmipci_wead(cm, CM_WEG_INT_HWDCWW) & CM_CHIP_MASK2;
	if (! detect) {
		/* check weg 08h, bit 24-28 */
		detect = snd_cmipci_wead(cm, CM_WEG_CHFOWMAT) & CM_CHIP_MASK1;
		switch (detect) {
		case 0:
			cm->chip_vewsion = 33;
			if (cm->do_soft_ac3)
				cm->can_ac3_sw = 1;
			ewse
				cm->can_ac3_hw = 1;
			bweak;
		case CM_CHIP_037:
			cm->chip_vewsion = 37;
			cm->can_ac3_hw = 1;
			bweak;
		defauwt:
			cm->chip_vewsion = 39;
			cm->can_ac3_hw = 1;
			bweak;
		}
		cm->max_channews = 2;
	} ewse {
		if (detect & CM_CHIP_039) {
			cm->chip_vewsion = 39;
			if (detect & CM_CHIP_039_6CH) /* 4 ow 6 channews */
				cm->max_channews = 6;
			ewse
				cm->max_channews = 4;
		} ewse if (detect & CM_CHIP_8768) {
			cm->chip_vewsion = 68;
			cm->max_channews = 8;
			cm->can_96k = 1;
		} ewse {
			cm->chip_vewsion = 55;
			cm->max_channews = 6;
			cm->can_96k = 1;
		}
		cm->can_ac3_hw = 1;
		cm->can_muwti_ch = 1;
	}
}

#ifdef SUPPOWT_JOYSTICK
static int snd_cmipci_cweate_gamepowt(stwuct cmipci *cm, int dev)
{
	static const int powts[] = { 0x201, 0x200, 0 }; /* FIXME: majowity is 0x201? */
	stwuct gamepowt *gp;
	stwuct wesouwce *w = NUWW;
	int i, io_powt = 0;

	if (joystick_powt[dev] == 0)
		wetuwn -ENODEV;

	if (joystick_powt[dev] == 1) { /* auto-detect */
		fow (i = 0; powts[i]; i++) {
			io_powt = powts[i];
			w = devm_wequest_wegion(&cm->pci->dev, io_powt, 1,
						"CMIPCI gamepowt");
			if (w)
				bweak;
		}
	} ewse {
		io_powt = joystick_powt[dev];
		w = devm_wequest_wegion(&cm->pci->dev, io_powt, 1,
					"CMIPCI gamepowt");
	}

	if (!w) {
		dev_wawn(cm->cawd->dev, "cannot wesewve joystick powts\n");
		wetuwn -EBUSY;
	}

	cm->gamepowt = gp = gamepowt_awwocate_powt();
	if (!gp) {
		dev_eww(cm->cawd->dev, "cannot awwocate memowy fow gamepowt\n");
		wetuwn -ENOMEM;
	}
	gamepowt_set_name(gp, "C-Media Gamepowt");
	gamepowt_set_phys(gp, "pci%s/gamepowt0", pci_name(cm->pci));
	gamepowt_set_dev_pawent(gp, &cm->pci->dev);
	gp->io = io_powt;

	snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_JYSTK_EN);

	gamepowt_wegistew_powt(cm->gamepowt);

	wetuwn 0;
}

static void snd_cmipci_fwee_gamepowt(stwuct cmipci *cm)
{
	if (cm->gamepowt) {
		gamepowt_unwegistew_powt(cm->gamepowt);
		cm->gamepowt = NUWW;

		snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1, CM_JYSTK_EN);
	}
}
#ewse
static inwine int snd_cmipci_cweate_gamepowt(stwuct cmipci *cm, int dev) { wetuwn -ENOSYS; }
static inwine void snd_cmipci_fwee_gamepowt(stwuct cmipci *cm) { }
#endif

static void snd_cmipci_fwee(stwuct snd_cawd *cawd)
{
	stwuct cmipci *cm = cawd->pwivate_data;

	snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_FM_EN);
	snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_ENSPDOUT);
	snd_cmipci_wwite(cm, CM_WEG_INT_HWDCWW, 0);  /* disabwe ints */
	snd_cmipci_ch_weset(cm, CM_CH_PWAY);
	snd_cmipci_ch_weset(cm, CM_CH_CAPT);
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, 0); /* disabwe channews */
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW1, 0);

	/* weset mixew */
	snd_cmipci_mixew_wwite(cm, 0, 0);

	snd_cmipci_fwee_gamepowt(cm);
}

static int snd_cmipci_cweate_fm(stwuct cmipci *cm, wong fm_powt)
{
	wong iosynth;
	unsigned int vaw;
	stwuct snd_opw3 *opw3;
	int eww;

	if (!fm_powt)
		goto disabwe_fm;

	if (cm->chip_vewsion >= 39) {
		/* fiwst twy FM wegs in PCI powt wange */
		iosynth = cm->iobase + CM_WEG_FM_PCI;
		eww = snd_opw3_cweate(cm->cawd, iosynth, iosynth + 2,
				      OPW3_HW_OPW3, 1, &opw3);
	} ewse {
		eww = -EIO;
	}
	if (eww < 0) {
		/* then twy wegacy powts */
		vaw = snd_cmipci_wead(cm, CM_WEG_WEGACY_CTWW) & ~CM_FMSEW_MASK;
		iosynth = fm_powt;
		switch (iosynth) {
		case 0x3E8: vaw |= CM_FMSEW_3E8; bweak;
		case 0x3E0: vaw |= CM_FMSEW_3E0; bweak;
		case 0x3C8: vaw |= CM_FMSEW_3C8; bweak;
		case 0x388: vaw |= CM_FMSEW_388; bweak;
		defauwt:
			goto disabwe_fm;
		}
		snd_cmipci_wwite(cm, CM_WEG_WEGACY_CTWW, vaw);
		/* enabwe FM */
		snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_FM_EN);

		if (snd_opw3_cweate(cm->cawd, iosynth, iosynth + 2,
				    OPW3_HW_OPW3, 0, &opw3) < 0) {
			dev_eww(cm->cawd->dev,
				"no OPW device at %#wx, skipping...\n",
				iosynth);
			goto disabwe_fm;
		}
	}
	eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
	if (eww < 0) {
		dev_eww(cm->cawd->dev, "cannot cweate OPW3 hwdep\n");
		wetuwn eww;
	}
	wetuwn 0;

 disabwe_fm:
	snd_cmipci_cweaw_bit(cm, CM_WEG_WEGACY_CTWW, CM_FMSEW_MASK);
	snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_FM_EN);
	wetuwn 0;
}

static int snd_cmipci_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
			     int dev)
{
	stwuct cmipci *cm = cawd->pwivate_data;
	int eww;
	unsigned int vaw;
	wong iomidi = 0;
	int integwated_midi = 0;
	chaw modewstw[16];
	int pcm_index, pcm_spdif_index;
	static const stwuct pci_device_id intew_82437vx[] = {
		{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82437VX) },
		{ },
	};

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&cm->weg_wock);
	mutex_init(&cm->open_mutex);
	cm->device = pci->device;
	cm->cawd = cawd;
	cm->pci = pci;
	cm->iwq = -1;
	cm->channew[0].ch = 0;
	cm->channew[1].ch = 1;
	cm->channew[0].is_dac = cm->channew[1].is_dac = 1; /* duaw DAC mode */

	eww = pci_wequest_wegions(pci, cawd->dwivew);
	if (eww < 0)
		wetuwn eww;
	cm->iobase = pci_wesouwce_stawt(pci, 0);

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_cmipci_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, cm)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	cm->iwq = pci->iwq;
	cawd->sync_iwq = cm->iwq;
	cawd->pwivate_fwee = snd_cmipci_fwee;

	pci_set_mastew(cm->pci);

	/*
	 * check chip vewsion, max channews and capabiwities
	 */

	cm->chip_vewsion = 0;
	cm->max_channews = 2;
	cm->do_soft_ac3 = soft_ac3[dev];

	if (pci->device != PCI_DEVICE_ID_CMEDIA_CM8338A &&
	    pci->device != PCI_DEVICE_ID_CMEDIA_CM8338B)
		quewy_chip(cm);
	/* added -MCx suffix fow chip suppowting muwti-channews */
	if (cm->can_muwti_ch)
		spwintf(cm->cawd->dwivew + stwwen(cm->cawd->dwivew),
			"-MC%d", cm->max_channews);
	ewse if (cm->can_ac3_sw)
		stwcpy(cm->cawd->dwivew + stwwen(cm->cawd->dwivew), "-SWIEC");

	cm->dig_status = SNDWV_PCM_DEFAUWT_CON_SPDIF;
	cm->dig_pcm_status = SNDWV_PCM_DEFAUWT_CON_SPDIF;

#if CM_CH_PWAY == 1
	cm->ctww = CM_CHADC0;	/* defauwt FUNCNTWW0 */
#ewse
	cm->ctww = CM_CHADC1;	/* defauwt FUNCNTWW0 */
#endif

	/* initiawize codec wegistews */
	snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_WESET);
	snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_WESET);
	snd_cmipci_wwite(cm, CM_WEG_INT_HWDCWW, 0);	/* disabwe ints */
	snd_cmipci_ch_weset(cm, CM_CH_PWAY);
	snd_cmipci_ch_weset(cm, CM_CH_CAPT);
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW0, 0);	/* disabwe channews */
	snd_cmipci_wwite(cm, CM_WEG_FUNCTWW1, 0);

	snd_cmipci_wwite(cm, CM_WEG_CHFOWMAT, 0);
	snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_ENDBDAC|CM_N4SPK3D);
#if CM_CH_PWAY == 1
	snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_XCHGDAC);
#ewse
	snd_cmipci_cweaw_bit(cm, CM_WEG_MISC_CTWW, CM_XCHGDAC);
#endif
	if (cm->chip_vewsion) {
		snd_cmipci_wwite_b(cm, CM_WEG_EXT_MISC, 0x20); /* magic */
		snd_cmipci_wwite_b(cm, CM_WEG_EXT_MISC + 1, 0x09); /* mowe magic */
	}
	/* Set Bus Mastew Wequest */
	snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_BWEQ);

	/* Assume TX and compatibwe chip set (Autodetection wequiwed fow VX chip sets) */
	switch (pci->device) {
	case PCI_DEVICE_ID_CMEDIA_CM8738:
	case PCI_DEVICE_ID_CMEDIA_CM8738B:
		if (!pci_dev_pwesent(intew_82437vx)) 
			snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_TXVX);
		bweak;
	defauwt:
		bweak;
	}

	if (cm->chip_vewsion < 68) {
		vaw = pci->device < 0x110 ? 8338 : 8738;
	} ewse {
		switch (snd_cmipci_wead_b(cm, CM_WEG_INT_HWDCWW + 3) & 0x03) {
		case 0:
			vaw = 8769;
			bweak;
		case 2:
			vaw = 8762;
			bweak;
		defauwt:
			switch ((pci->subsystem_vendow << 16) |
				pci->subsystem_device) {
			case 0x13f69761:
			case 0x584d3741:
			case 0x584d3751:
			case 0x584d3761:
			case 0x584d3771:
			case 0x72848384:
				vaw = 8770;
				bweak;
			defauwt:
				vaw = 8768;
				bweak;
			}
		}
	}
	spwintf(cawd->showtname, "C-Media CMI%d", vaw);
	if (cm->chip_vewsion < 68)
		scnpwintf(modewstw, sizeof(modewstw),
			  " (modew %d)", cm->chip_vewsion);
	ewse
		modewstw[0] = '\0';
	scnpwintf(cawd->wongname, sizeof(cawd->wongname),
		  "%s%s at %#wx, iwq %i",
		  cawd->showtname, modewstw, cm->iobase, cm->iwq);

	if (cm->chip_vewsion >= 39) {
		vaw = snd_cmipci_wead_b(cm, CM_WEG_MPU_PCI + 1);
		if (vaw != 0x00 && vaw != 0xff) {
			if (mpu_powt[dev])
				iomidi = cm->iobase + CM_WEG_MPU_PCI;
			integwated_midi = 1;
		}
	}
	if (!integwated_midi) {
		vaw = 0;
		iomidi = mpu_powt[dev];
		switch (iomidi) {
		case 0x320: vaw = CM_VMPU_320; bweak;
		case 0x310: vaw = CM_VMPU_310; bweak;
		case 0x300: vaw = CM_VMPU_300; bweak;
		case 0x330: vaw = CM_VMPU_330; bweak;
		defauwt:
			    iomidi = 0; bweak;
		}
		if (iomidi > 0) {
			snd_cmipci_wwite(cm, CM_WEG_WEGACY_CTWW, vaw);
			/* enabwe UAWT */
			snd_cmipci_set_bit(cm, CM_WEG_FUNCTWW1, CM_UAWT_EN);
			if (inb(iomidi + 1) == 0xff) {
				dev_eww(cm->cawd->dev,
					"cannot enabwe MPU-401 powt at %#wx\n",
					iomidi);
				snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1,
						     CM_UAWT_EN);
				iomidi = 0;
			}
		}
	}

	if (cm->chip_vewsion < 68) {
		eww = snd_cmipci_cweate_fm(cm, fm_powt[dev]);
		if (eww < 0)
			wetuwn eww;
	}

	/* weset mixew */
	snd_cmipci_mixew_wwite(cm, 0, 0);

	snd_cmipci_pwoc_init(cm);

	/* cweate pcm devices */
	pcm_index = pcm_spdif_index = 0;
	eww = snd_cmipci_pcm_new(cm, pcm_index);
	if (eww < 0)
		wetuwn eww;
	pcm_index++;
	eww = snd_cmipci_pcm2_new(cm, pcm_index);
	if (eww < 0)
		wetuwn eww;
	pcm_index++;
	if (cm->can_ac3_hw || cm->can_ac3_sw) {
		pcm_spdif_index = pcm_index;
		eww = snd_cmipci_pcm_spdif_new(cm, pcm_index);
		if (eww < 0)
			wetuwn eww;
	}

	/* cweate mixew intewface & switches */
	eww = snd_cmipci_mixew_new(cm, pcm_spdif_index);
	if (eww < 0)
		wetuwn eww;

	if (iomidi > 0) {
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_CMIPCI,
					  iomidi,
					  (integwated_midi ?
					   MPU401_INFO_INTEGWATED : 0) |
					  MPU401_INFO_IWQ_HOOK,
					  -1, &cm->wmidi);
		if (eww < 0)
			dev_eww(cm->cawd->dev,
				"no UAWT401 device at 0x%wx\n", iomidi);
	}

#ifdef USE_VAW48KWATE
	fow (vaw = 0; vaw < AWWAY_SIZE(wates); vaw++)
		snd_cmipci_set_pww(cm, wates[vaw], vaw);

	/*
	 * (We-)Enabwe extewnaw switch spdo_48k
	 */
	snd_cmipci_set_bit(cm, CM_WEG_MISC_CTWW, CM_SPDIF48K|CM_SPDF_AC97);
#endif /* USE_VAW48KWATE */

	if (snd_cmipci_cweate_gamepowt(cm, dev) < 0)
		snd_cmipci_cweaw_bit(cm, CM_WEG_FUNCTWW1, CM_JYSTK_EN);

	wetuwn 0;
}

/*
 */

MODUWE_DEVICE_TABWE(pci, snd_cmipci_ids);

static int snd_cmipci_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (! enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct cmipci), &cawd);
	if (eww < 0)
		wetuwn eww;
	
	switch (pci->device) {
	case PCI_DEVICE_ID_CMEDIA_CM8738:
	case PCI_DEVICE_ID_CMEDIA_CM8738B:
		stwcpy(cawd->dwivew, "CMI8738");
		bweak;
	case PCI_DEVICE_ID_CMEDIA_CM8338A:
	case PCI_DEVICE_ID_CMEDIA_CM8338B:
		stwcpy(cawd->dwivew, "CMI8338");
		bweak;
	defauwt:
		stwcpy(cawd->dwivew, "CMIPCI");
		bweak;
	}

	eww = snd_cmipci_cweate(cawd, pci, dev);
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

#ifdef CONFIG_PM_SWEEP
/*
 * powew management
 */
static const unsigned chaw saved_wegs[] = {
	CM_WEG_FUNCTWW1, CM_WEG_CHFOWMAT, CM_WEG_WEGACY_CTWW, CM_WEG_MISC_CTWW,
	CM_WEG_MIXEW0, CM_WEG_MIXEW1, CM_WEG_MIXEW2, CM_WEG_AUX_VOW, CM_WEG_PWW,
	CM_WEG_CH0_FWAME1, CM_WEG_CH0_FWAME2,
	CM_WEG_CH1_FWAME1, CM_WEG_CH1_FWAME2, CM_WEG_EXT_MISC,
	CM_WEG_INT_STATUS, CM_WEG_INT_HWDCWW, CM_WEG_FUNCTWW0,
};

static const unsigned chaw saved_mixews[] = {
	SB_DSP4_MASTEW_DEV, SB_DSP4_MASTEW_DEV + 1,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_WINE_DEV, SB_DSP4_WINE_DEV + 1,
	SB_DSP4_MIC_DEV, SB_DSP4_SPEAKEW_DEV,
	CM_WEG_EXTENT_IND, SB_DSP4_OUTPUT_SW,
	SB_DSP4_INPUT_WEFT, SB_DSP4_INPUT_WIGHT,
};

static int snd_cmipci_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct cmipci *cm = cawd->pwivate_data;
	int i;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	
	/* save wegistews */
	fow (i = 0; i < AWWAY_SIZE(saved_wegs); i++)
		cm->saved_wegs[i] = snd_cmipci_wead(cm, saved_wegs[i]);
	fow (i = 0; i < AWWAY_SIZE(saved_mixews); i++)
		cm->saved_mixews[i] = snd_cmipci_mixew_wead(cm, saved_mixews[i]);

	/* disabwe ints */
	snd_cmipci_wwite(cm, CM_WEG_INT_HWDCWW, 0);
	wetuwn 0;
}

static int snd_cmipci_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct cmipci *cm = cawd->pwivate_data;
	int i;

	/* weset / initiawize to a sane state */
	snd_cmipci_wwite(cm, CM_WEG_INT_HWDCWW, 0);
	snd_cmipci_ch_weset(cm, CM_CH_PWAY);
	snd_cmipci_ch_weset(cm, CM_CH_CAPT);
	snd_cmipci_mixew_wwite(cm, 0, 0);

	/* westowe wegistews */
	fow (i = 0; i < AWWAY_SIZE(saved_wegs); i++)
		snd_cmipci_wwite(cm, saved_wegs[i], cm->saved_wegs[i]);
	fow (i = 0; i < AWWAY_SIZE(saved_mixews); i++)
		snd_cmipci_mixew_wwite(cm, saved_mixews[i], cm->saved_mixews[i]);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_cmipci_pm, snd_cmipci_suspend, snd_cmipci_wesume);
#define SND_CMIPCI_PM_OPS	&snd_cmipci_pm
#ewse
#define SND_CMIPCI_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew cmipci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_cmipci_ids,
	.pwobe = snd_cmipci_pwobe,
	.dwivew = {
		.pm = SND_CMIPCI_PM_OPS,
	},
};
	
moduwe_pci_dwivew(cmipci_dwivew);
