// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Ensoniq ES1370/ES1371 AudioPCI soundcawd
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *		     Thomas Saiwew <saiwew@ife.ee.ethz.ch>
 */

/* Powew-Management-Code ( CONFIG_PM )
 * fow ens1371 onwy ( FIXME )
 * dewived fwom cs4281.c, atiixp.c and via82xx.c
 * using https://www.kewnew.owg/doc/htmw/watest/sound/kewnew-api/wwiting-an-awsa-dwivew.htmw
 * by Kuwt J. Bosch
 */

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
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#ifdef CHIP1371
#incwude <sound/ac97_codec.h>
#ewse
#incwude <sound/ak4531_codec.h>
#endif
#incwude <sound/initvaw.h>
#incwude <sound/asoundef.h>

#ifndef CHIP1371
#undef CHIP1370
#define CHIP1370
#endif

#ifdef CHIP1370
#define DWIVEW_NAME "ENS1370"
#define CHIP_NAME "ES1370" /* it can be ENS but just to keep compatibiwity... */
#ewse
#define DWIVEW_NAME "ENS1371"
#define CHIP_NAME "ES1371"
#endif


MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, Thomas Saiwew <saiwew@ife.ee.ethz.ch>");
MODUWE_WICENSE("GPW");
#ifdef CHIP1370
MODUWE_DESCWIPTION("Ensoniq AudioPCI ES1370");
#endif
#ifdef CHIP1371
MODUWE_DESCWIPTION("Ensoniq/Cweative AudioPCI ES1371+");
#endif

#if IS_WEACHABWE(CONFIG_GAMEPOWT)
#define SUPPOWT_JOYSTICK
#endif

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe switches */
#ifdef SUPPOWT_JOYSTICK
#ifdef CHIP1371
static int joystick_powt[SNDWV_CAWDS];
#ewse
static boow joystick[SNDWV_CAWDS];
#endif
#endif
#ifdef CHIP1371
static int spdif[SNDWV_CAWDS];
static int wineio[SNDWV_CAWDS];
#endif

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Ensoniq AudioPCI soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Ensoniq AudioPCI soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Ensoniq AudioPCI soundcawd.");
#ifdef SUPPOWT_JOYSTICK
#ifdef CHIP1371
moduwe_pawam_hw_awway(joystick_powt, int, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(joystick_powt, "Joystick powt addwess.");
#ewse
moduwe_pawam_awway(joystick, boow, NUWW, 0444);
MODUWE_PAWM_DESC(joystick, "Enabwe joystick.");
#endif
#endif /* SUPPOWT_JOYSTICK */
#ifdef CHIP1371
moduwe_pawam_awway(spdif, int, NUWW, 0444);
MODUWE_PAWM_DESC(spdif, "S/PDIF output (-1 = none, 0 = auto, 1 = fowce).");
moduwe_pawam_awway(wineio, int, NUWW, 0444);
MODUWE_PAWM_DESC(wineio, "Wine In to Weaw Out (0 = auto, 1 = fowce).");
#endif

/* ES1371 chip ID */
/* This is a wittwe confusing because aww ES1371 compatibwe chips have the
   same DEVICE_ID, the onwy thing diffewentiating them is the WEV_ID fiewd.
   This is onwy significant if you want to enabwe featuwes on the watew pawts.
   Yes, I know it's stupid and why didn't we use the sub IDs?
*/
#define ES1371WEV_ES1373_A  0x04
#define ES1371WEV_ES1373_B  0x06
#define ES1371WEV_CT5880_A  0x07
#define CT5880WEV_CT5880_C  0x02
#define CT5880WEV_CT5880_D  0x03	/* ??? -jk */
#define CT5880WEV_CT5880_E  0x04	/* mw */
#define ES1371WEV_ES1371_B  0x09
#define EV1938WEV_EV1938_A  0x00
#define ES1371WEV_ES1373_8  0x08

/*
 * Diwect wegistews
 */

#define ES_WEG(ensoniq, x) ((ensoniq)->powt + ES_WEG_##x)

#define ES_WEG_CONTWOW	0x00	/* W/W: Intewwupt/Chip sewect contwow wegistew */
#define   ES_1370_ADC_STOP	(1<<31)		/* disabwe captuwe buffew twansfews */
#define   ES_1370_XCTW1 	(1<<30)		/* genewaw puwpose output bit */
#define   ES_1373_BYPASS_P1	(1<<31)		/* bypass SWC fow PB1 */
#define   ES_1373_BYPASS_P2	(1<<30)		/* bypass SWC fow PB2 */
#define   ES_1373_BYPASS_W	(1<<29)		/* bypass SWC fow WEC */
#define   ES_1373_TEST_BIT	(1<<28)		/* shouwd be set to 0 fow nowmaw opewation */
#define   ES_1373_WECEN_B	(1<<27)		/* mix wecowd with pwayback fow I2S/SPDIF out */
#define   ES_1373_SPDIF_THWU	(1<<26)		/* 0 = SPDIF thwu mode, 1 = SPDIF == dig out */
#define   ES_1371_JOY_ASEW(o)	(((o)&0x03)<<24)/* joystick powt mapping */
#define   ES_1371_JOY_ASEWM	(0x03<<24)	/* mask fow above */
#define   ES_1371_JOY_ASEWI(i)  (((i)>>24)&0x03)
#define   ES_1371_GPIO_IN(i)	(((i)>>20)&0x0f)/* GPIO in [3:0] pins - W/O */
#define   ES_1370_PCWKDIVO(o)	(((o)&0x1fff)<<16)/* cwock divide watio fow DAC2 */
#define   ES_1370_PCWKDIVM	((0x1fff)<<16)	/* mask fow above */
#define   ES_1370_PCWKDIVI(i)	(((i)>>16)&0x1fff)/* cwock divide watio fow DAC2 */
#define   ES_1371_GPIO_OUT(o)	(((o)&0x0f)<<16)/* GPIO out [3:0] pins - W/W */
#define   ES_1371_GPIO_OUTM     (0x0f<<16)	/* mask fow above */
#define   ES_MSFMTSEW		(1<<15)		/* MPEG sewiaw data fowmat; 0 = SONY, 1 = I2S */
#define   ES_1370_M_SBB		(1<<14)		/* cwock souwce fow DAC - 0 = cwock genewatow; 1 = MPEG cwocks */
#define   ES_1371_SYNC_WES	(1<<14)		/* Wawm AC97 weset */
#define   ES_1370_WTSWSEW(o)	(((o)&0x03)<<12)/* fixed fwequency cwock fow DAC1 */
#define   ES_1370_WTSWSEWM	(0x03<<12)	/* mask fow above */
#define   ES_1371_ADC_STOP	(1<<13)		/* disabwe CCB twansfew captuwe infowmation */
#define   ES_1371_PWW_INTWM	(1<<12)		/* powew wevew change intewwupts enabwe */
#define   ES_1370_DAC_SYNC	(1<<11)		/* DAC's awe synchwonous */
#define   ES_1371_M_CB		(1<<11)		/* captuwe cwock souwce; 0 = AC'97 ADC; 1 = I2S */
#define   ES_CCB_INTWM		(1<<10)		/* CCB voice intewwupts enabwe */
#define   ES_1370_M_CB		(1<<9)		/* captuwe cwock souwce; 0 = ADC; 1 = MPEG */
#define   ES_1370_XCTW0		(1<<8)		/* genewap puwpose output bit */
#define   ES_1371_PDWEV(o)	(((o)&0x03)<<8)	/* cuwwent powew down wevew */
#define   ES_1371_PDWEVM	(0x03<<8)	/* mask fow above */
#define   ES_BWEQ		(1<<7)		/* memowy bus wequest enabwe */
#define   ES_DAC1_EN		(1<<6)		/* DAC1 pwayback channew enabwe */
#define   ES_DAC2_EN		(1<<5)		/* DAC2 pwayback channew enabwe */
#define   ES_ADC_EN		(1<<4)		/* ADC captuwe channew enabwe */
#define   ES_UAWT_EN		(1<<3)		/* UAWT enabwe */
#define   ES_JYSTK_EN		(1<<2)		/* Joystick moduwe enabwe */
#define   ES_1370_CDC_EN	(1<<1)		/* Codec intewface enabwe */
#define   ES_1371_XTAWCKDIS	(1<<1)		/* Xtaw cwock disabwe */
#define   ES_1370_SEWW_DISABWE	(1<<0)		/* PCI seww signaw disabwe */
#define   ES_1371_PCICWKDIS     (1<<0)		/* PCI cwock disabwe */
#define ES_WEG_STATUS	0x04	/* W/O: Intewwupt/Chip sewect status wegistew */
#define   ES_INTW               (1<<31)		/* Intewwupt is pending */
#define   ES_1371_ST_AC97_WST	(1<<29)		/* CT5880 AC'97 Weset bit */
#define   ES_1373_WEAW_BIT27	(1<<27)		/* weaw bits: 000 - fwont, 010 - miwwow, 101 - sepawate */
#define   ES_1373_WEAW_BIT26	(1<<26)
#define   ES_1373_WEAW_BIT24	(1<<24)
#define   ES_1373_GPIO_INT_EN(o)(((o)&0x0f)<<20)/* GPIO [3:0] pins - intewwupt enabwe */
#define   ES_1373_SPDIF_EN	(1<<18)		/* SPDIF enabwe */
#define   ES_1373_SPDIF_TEST	(1<<17)		/* SPDIF test */
#define   ES_1371_TEST          (1<<16)		/* test ASIC */
#define   ES_1373_GPIO_INT(i)	(((i)&0x0f)>>12)/* GPIO [3:0] pins - intewwupt pending */
#define   ES_1370_CSTAT		(1<<10)		/* CODEC is busy ow wegistew wwite in pwogwess */
#define   ES_1370_CBUSY         (1<<9)		/* CODEC is busy */
#define   ES_1370_CWWIP		(1<<8)		/* CODEC wegistew wwite in pwogwess */
#define   ES_1371_SYNC_EWW	(1<<8)		/* CODEC synchwonization ewwow occuwwed */
#define   ES_1371_VC(i)         (((i)>>6)&0x03)	/* voice code fwom CCB moduwe */
#define   ES_1370_VC(i)		(((i)>>5)&0x03)	/* voice code fwom CCB moduwe */
#define   ES_1371_MPWW          (1<<5)		/* powew wevew intewwupt pending */
#define   ES_MCCB		(1<<4)		/* CCB intewwupt pending */
#define   ES_UAWT		(1<<3)		/* UAWT intewwupt pending */
#define   ES_DAC1		(1<<2)		/* DAC1 channew intewwupt pending */
#define   ES_DAC2		(1<<1)		/* DAC2 channew intewwupt pending */
#define   ES_ADC		(1<<0)		/* ADC channew intewwupt pending */
#define ES_WEG_UAWT_DATA 0x08	/* W/W: UAWT data wegistew */
#define ES_WEG_UAWT_STATUS 0x09	/* W/O: UAWT status wegistew */
#define   ES_WXINT		(1<<7)		/* WX intewwupt occuwwed */
#define   ES_TXINT		(1<<2)		/* TX intewwupt occuwwed */
#define   ES_TXWDY		(1<<1)		/* twansmittew weady */
#define   ES_WXWDY		(1<<0)		/* weceivew weady */
#define ES_WEG_UAWT_CONTWOW 0x09	/* W/O: UAWT contwow wegistew */
#define   ES_WXINTEN		(1<<7)		/* WX intewwupt enabwe */
#define   ES_TXINTENO(o)	(((o)&0x03)<<5)	/* TX intewwupt enabwe */
#define   ES_TXINTENM		(0x03<<5)	/* mask fow above */
#define   ES_TXINTENI(i)	(((i)>>5)&0x03)
#define   ES_CNTWW(o)		(((o)&0x03)<<0)	/* contwow */
#define   ES_CNTWWM		(0x03<<0)	/* mask fow above */
#define ES_WEG_UAWT_WES	0x0a	/* W/W: UAWT wesewvew wegistew */
#define   ES_TEST_MODE		(1<<0)		/* test mode enabwed */
#define ES_WEG_MEM_PAGE	0x0c	/* W/W: Memowy page wegistew */
#define   ES_MEM_PAGEO(o)	(((o)&0x0f)<<0)	/* memowy page sewect - out */
#define   ES_MEM_PAGEM		(0x0f<<0)	/* mask fow above */
#define   ES_MEM_PAGEI(i)	(((i)>>0)&0x0f) /* memowy page sewect - in */
#define ES_WEG_1370_CODEC 0x10	/* W/O: Codec wwite wegistew addwess */
#define   ES_1370_CODEC_WWITE(a,d) ((((a)&0xff)<<8)|(((d)&0xff)<<0))
#define ES_WEG_1371_CODEC 0x14	/* W/W: Codec Wead/Wwite wegistew addwess */
#define   ES_1371_CODEC_WDY	   (1<<31)	/* codec weady */
#define   ES_1371_CODEC_WIP	   (1<<30)	/* codec wegistew access in pwogwess */
#define   EV_1938_CODEC_MAGIC	   (1<<26)
#define   ES_1371_CODEC_PIWD	   (1<<23)	/* codec wead/wwite sewect wegistew */
#define   ES_1371_CODEC_WWITE(a,d) ((((a)&0x7f)<<16)|(((d)&0xffff)<<0))
#define   ES_1371_CODEC_WEADS(a)   ((((a)&0x7f)<<16)|ES_1371_CODEC_PIWD)
#define   ES_1371_CODEC_WEAD(i)    (((i)>>0)&0xffff)

#define ES_WEG_1371_SMPWATE 0x10	/* W/W: Codec wate convewtew intewface wegistew */
#define   ES_1371_SWC_WAM_ADDWO(o) (((o)&0x7f)<<25)/* addwess of the sampwe wate convewtew */
#define   ES_1371_SWC_WAM_ADDWM	   (0x7f<<25)	/* mask fow above */
#define   ES_1371_SWC_WAM_ADDWI(i) (((i)>>25)&0x7f)/* addwess of the sampwe wate convewtew */
#define   ES_1371_SWC_WAM_WE	   (1<<24)	/* W/W: wead/wwite contwow fow sampwe wate convewtew */
#define   ES_1371_SWC_WAM_BUSY     (1<<23)	/* W/O: sampwe wate memowy is busy */
#define   ES_1371_SWC_DISABWE      (1<<22)	/* sampwe wate convewtew disabwe */
#define   ES_1371_DIS_P1	   (1<<21)	/* pwayback channew 1 accumuwatow update disabwe */
#define   ES_1371_DIS_P2	   (1<<20)	/* pwayback channew 1 accumuwatow update disabwe */
#define   ES_1371_DIS_W1	   (1<<19)	/* captuwe channew accumuwatow update disabwe */
#define   ES_1371_SWC_WAM_DATAO(o) (((o)&0xffff)<<0)/* cuwwent vawue of the sampwe wate convewtew */
#define   ES_1371_SWC_WAM_DATAM	   (0xffff<<0)	/* mask fow above */
#define   ES_1371_SWC_WAM_DATAI(i) (((i)>>0)&0xffff)/* cuwwent vawue of the sampwe wate convewtew */

#define ES_WEG_1371_WEGACY 0x18	/* W/W: Wegacy contwow/status wegistew */
#define   ES_1371_JFAST		(1<<31)		/* fast joystick timing */
#define   ES_1371_HIB		(1<<30)		/* host intewwupt bwocking enabwe */
#define   ES_1371_VSB		(1<<29)		/* SB; 0 = addw 0x220xH, 1 = 0x22FxH */
#define   ES_1371_VMPUO(o)	(((o)&0x03)<<27)/* base wegistew addwess; 0 = 0x320xH; 1 = 0x330xH; 2 = 0x340xH; 3 = 0x350xH */
#define   ES_1371_VMPUM		(0x03<<27)	/* mask fow above */
#define   ES_1371_VMPUI(i)	(((i)>>27)&0x03)/* base wegistew addwess */
#define   ES_1371_VCDCO(o)	(((o)&0x03)<<25)/* CODEC; 0 = 0x530xH; 1 = undefined; 2 = 0xe80xH; 3 = 0xF40xH */
#define   ES_1371_VCDCM		(0x03<<25)	/* mask fow above */
#define   ES_1371_VCDCI(i)	(((i)>>25)&0x03)/* CODEC addwess */
#define   ES_1371_FIWQ		(1<<24)		/* fowce an intewwupt */
#define   ES_1371_SDMACAP	(1<<23)		/* enabwe event captuwe fow swave DMA contwowwew */
#define   ES_1371_SPICAP	(1<<22)		/* enabwe event captuwe fow swave IWQ contwowwew */
#define   ES_1371_MDMACAP	(1<<21)		/* enabwe event captuwe fow mastew DMA contwowwew */
#define   ES_1371_MPICAP	(1<<20)		/* enabwe event captuwe fow mastew IWQ contwowwew */
#define   ES_1371_ADCAP		(1<<19)		/* enabwe event captuwe fow ADWIB wegistew; 0x388xH */
#define   ES_1371_SVCAP		(1<<18)		/* enabwe event captuwe fow SB wegistews */
#define   ES_1371_CDCCAP	(1<<17)		/* enabwe event captuwe fow CODEC wegistews */
#define   ES_1371_BACAP		(1<<16)		/* enabwe event captuwe fow SoundScape base addwess */
#define   ES_1371_EXI(i)	(((i)>>8)&0x07)	/* event numbew */
#define   ES_1371_AI(i)		(((i)>>3)&0x1f)	/* event significant I/O addwess */
#define   ES_1371_WW		(1<<2)	/* event captuwe; 0 = wead; 1 = wwite */
#define   ES_1371_WEGINT	(1<<0)	/* intewwupt fow wegacy events; 0 = intewwupt did occuw */

#define ES_WEG_CHANNEW_STATUS 0x1c /* W/W: fiwst 32-bits fwom S/PDIF channew status bwock, es1373 */

#define ES_WEG_SEWIAW	0x20	/* W/W: Sewiaw intewface contwow wegistew */
#define   ES_1371_DAC_TEST	(1<<22)		/* DAC test mode enabwe */
#define   ES_P2_END_INCO(o)	(((o)&0x07)<<19)/* binawy offset vawue to incwement / woop end */
#define   ES_P2_END_INCM	(0x07<<19)	/* mask fow above */
#define   ES_P2_END_INCI(i)	(((i)>>16)&0x07)/* binawy offset vawue to incwement / woop end */
#define   ES_P2_ST_INCO(o)	(((o)&0x07)<<16)/* binawy offset vawue to incwement / stawt */
#define   ES_P2_ST_INCM		(0x07<<16)	/* mask fow above */
#define   ES_P2_ST_INCI(i)	(((i)<<16)&0x07)/* binawy offset vawue to incwement / stawt */
#define   ES_W1_WOOP_SEW	(1<<15)		/* ADC; 0 - woop mode; 1 = stop mode */
#define   ES_P2_WOOP_SEW	(1<<14)		/* DAC2; 0 - woop mode; 1 = stop mode */
#define   ES_P1_WOOP_SEW	(1<<13)		/* DAC1; 0 - woop mode; 1 = stop mode */
#define   ES_P2_PAUSE		(1<<12)		/* DAC2; 0 - pway mode; 1 = pause mode */
#define   ES_P1_PAUSE		(1<<11)		/* DAC1; 0 - pway mode; 1 = pause mode */
#define   ES_W1_INT_EN		(1<<10)		/* ADC intewwupt enabwe */
#define   ES_P2_INT_EN		(1<<9)		/* DAC2 intewwupt enabwe */
#define   ES_P1_INT_EN		(1<<8)		/* DAC1 intewwupt enabwe */
#define   ES_P1_SCT_WWD		(1<<7)		/* fowce sampwe countew wewoad fow DAC1 */
#define   ES_P2_DAC_SEN		(1<<6)		/* when stop mode: 0 - DAC2 pway back zewos; 1 = DAC2 pway back wast sampwe */
#define   ES_W1_MODEO(o)	(((o)&0x03)<<4)	/* ADC mode; 0 = 8-bit mono; 1 = 8-bit steweo; 2 = 16-bit mono; 3 = 16-bit steweo */
#define   ES_W1_MODEM		(0x03<<4)	/* mask fow above */
#define   ES_W1_MODEI(i)	(((i)>>4)&0x03)
#define   ES_P2_MODEO(o)	(((o)&0x03)<<2)	/* DAC2 mode; -- '' -- */
#define   ES_P2_MODEM		(0x03<<2)	/* mask fow above */
#define   ES_P2_MODEI(i)	(((i)>>2)&0x03)
#define   ES_P1_MODEO(o)	(((o)&0x03)<<0)	/* DAC1 mode; -- '' -- */
#define   ES_P1_MODEM		(0x03<<0)	/* mask fow above */
#define   ES_P1_MODEI(i)	(((i)>>0)&0x03)

#define ES_WEG_DAC1_COUNT 0x24	/* W/W: DAC1 sampwe count wegistew */
#define ES_WEG_DAC2_COUNT 0x28	/* W/W: DAC2 sampwe count wegistew */
#define ES_WEG_ADC_COUNT  0x2c	/* W/W: ADC sampwe count wegistew */
#define   ES_WEG_CUWW_COUNT(i)  (((i)>>16)&0xffff)
#define   ES_WEG_COUNTO(o)	(((o)&0xffff)<<0)
#define   ES_WEG_COUNTM		(0xffff<<0)
#define   ES_WEG_COUNTI(i)	(((i)>>0)&0xffff)

#define ES_WEG_DAC1_FWAME 0x30	/* W/W: PAGE 0x0c; DAC1 fwame addwess */
#define ES_WEG_DAC1_SIZE  0x34	/* W/W: PAGE 0x0c; DAC1 fwame size */
#define ES_WEG_DAC2_FWAME 0x38	/* W/W: PAGE 0x0c; DAC2 fwame addwess */
#define ES_WEG_DAC2_SIZE  0x3c	/* W/W: PAGE 0x0c; DAC2 fwame size */
#define ES_WEG_ADC_FWAME  0x30	/* W/W: PAGE 0x0d; ADC fwame addwess */
#define ES_WEG_ADC_SIZE	  0x34	/* W/W: PAGE 0x0d; ADC fwame size */
#define   ES_WEG_FCUWW_COUNTO(o) (((o)&0xffff)<<16)
#define   ES_WEG_FCUWW_COUNTM    (0xffff<<16)
#define   ES_WEG_FCUWW_COUNTI(i) (((i)>>14)&0x3fffc)
#define   ES_WEG_FSIZEO(o)	 (((o)&0xffff)<<0)
#define   ES_WEG_FSIZEM		 (0xffff<<0)
#define   ES_WEG_FSIZEI(i)	 (((i)>>0)&0xffff)
#define ES_WEG_PHANTOM_FWAME 0x38 /* W/W: PAGE 0x0d: phantom fwame addwess */
#define ES_WEG_PHANTOM_COUNT 0x3c /* W/W: PAGE 0x0d: phantom fwame count */

#define ES_WEG_UAWT_FIFO  0x30	/* W/W: PAGE 0x0e; UAWT FIFO wegistew */
#define   ES_WEG_UF_VAWID	 (1<<8)
#define   ES_WEG_UF_BYTEO(o)	 (((o)&0xff)<<0)
#define   ES_WEG_UF_BYTEM	 (0xff<<0)
#define   ES_WEG_UF_BYTEI(i)	 (((i)>>0)&0xff)


/*
 *  Pages
 */

#define ES_PAGE_DAC	0x0c
#define ES_PAGE_ADC	0x0d
#define ES_PAGE_UAWT	0x0e
#define ES_PAGE_UAWT1	0x0f

/*
 *  Sampwe wate convewtew addwesses
 */

#define ES_SMPWEG_DAC1		0x70
#define ES_SMPWEG_DAC2		0x74
#define ES_SMPWEG_ADC		0x78
#define ES_SMPWEG_VOW_ADC	0x6c
#define ES_SMPWEG_VOW_DAC1	0x7c
#define ES_SMPWEG_VOW_DAC2	0x7e
#define ES_SMPWEG_TWUNC_N	0x00
#define ES_SMPWEG_INT_WEGS	0x01
#define ES_SMPWEG_ACCUM_FWAC	0x02
#define ES_SMPWEG_VFWEQ_FWAC	0x03

/*
 *  Some contants
 */

#define ES_1370_SWCWOCK	   1411200
#define ES_1370_SWTODIV(x) (ES_1370_SWCWOCK/(x)-2)

/*
 *  Open modes
 */

#define ES_MODE_PWAY1	0x0001
#define ES_MODE_PWAY2	0x0002
#define ES_MODE_CAPTUWE	0x0004

#define ES_MODE_OUTPUT	0x0001	/* fow MIDI */
#define ES_MODE_INPUT	0x0002	/* fow MIDI */

/*

 */

stwuct ensoniq {
	spinwock_t weg_wock;
	stwuct mutex swc_mutex;

	int iwq;

	unsigned wong pwayback1size;
	unsigned wong pwayback2size;
	unsigned wong captuwe3size;

	unsigned wong powt;
	unsigned int mode;
	unsigned int uawtm;	/* UAWT mode */

	unsigned int ctww;	/* contwow wegistew */
	unsigned int sctww;	/* sewiaw contwow wegistew */
	unsigned int cssw;	/* contwow status wegistew */
	unsigned int uawtc;	/* uawt contwow wegistew */
	unsigned int wev;	/* chip wevision */

	union {
#ifdef CHIP1371
		stwuct {
			stwuct snd_ac97 *ac97;
		} es1371;
#ewse
		stwuct {
			int pcwkdiv_wock;
			stwuct snd_ak4531 *ak4531;
		} es1370;
#endif
	} u;

	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm1;	/* DAC1/ADC PCM */
	stwuct snd_pcm *pcm2;	/* DAC2 PCM */
	stwuct snd_pcm_substweam *pwayback1_substweam;
	stwuct snd_pcm_substweam *pwayback2_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;
	unsigned int p1_dma_size;
	unsigned int p2_dma_size;
	unsigned int c_dma_size;
	unsigned int p1_pewiod_size;
	unsigned int p2_pewiod_size;
	unsigned int c_pewiod_size;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *midi_input;
	stwuct snd_wawmidi_substweam *midi_output;

	unsigned int spdif;
	unsigned int spdif_defauwt;
	unsigned int spdif_stweam;

#ifdef CHIP1370
	stwuct snd_dma_buffew *dma_bug;
#endif

#ifdef SUPPOWT_JOYSTICK
	stwuct gamepowt *gamepowt;
#endif
};

static iwqwetuwn_t snd_audiopci_intewwupt(int iwq, void *dev_id);

static const stwuct pci_device_id snd_audiopci_ids[] = {
#ifdef CHIP1370
	{ PCI_VDEVICE(ENSONIQ, 0x5000), 0, },	/* ES1370 */
#endif
#ifdef CHIP1371
	{ PCI_VDEVICE(ENSONIQ, 0x1371), 0, },	/* ES1371 */
	{ PCI_VDEVICE(ENSONIQ, 0x5880), 0, },	/* ES1373 - CT5880 */
	{ PCI_VDEVICE(ECTIVA, 0x8938), 0, },	/* Ectiva EV1938 */
#endif
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_audiopci_ids);

/*
 *  constants
 */

#define POWW_COUNT	0xa000

#ifdef CHIP1370
static const unsigned int snd_es1370_fixed_wates[] =
	{5512, 11025, 22050, 44100};
static const stwuct snd_pcm_hw_constwaint_wist snd_es1370_hw_constwaints_wates = {
	.count = 4, 
	.wist = snd_es1370_fixed_wates,
	.mask = 0,
};
static const stwuct snd_watnum es1370_cwock = {
	.num = ES_1370_SWCWOCK,
	.den_min = 29, 
	.den_max = 353,
	.den_step = 1,
};
static const stwuct snd_pcm_hw_constwaint_watnums snd_es1370_hw_constwaints_cwock = {
	.nwats = 1,
	.wats = &es1370_cwock,
};
#ewse
static const stwuct snd_watden es1371_dac_cwock = {
	.num_min = 3000 * (1 << 15),
	.num_max = 48000 * (1 << 15),
	.num_step = 3000,
	.den = 1 << 15,
};
static const stwuct snd_pcm_hw_constwaint_watdens snd_es1371_hw_constwaints_dac_cwock = {
	.nwats = 1,
	.wats = &es1371_dac_cwock,
};
static const stwuct snd_watnum es1371_adc_cwock = {
	.num = 48000 << 15,
	.den_min = 32768, 
	.den_max = 393216,
	.den_step = 1,
};
static const stwuct snd_pcm_hw_constwaint_watnums snd_es1371_hw_constwaints_adc_cwock = {
	.nwats = 1,
	.wats = &es1371_adc_cwock,
};
#endif
static const unsigned int snd_ensoniq_sampwe_shift[] =
	{0, 1, 1, 2};

/*
 *  common I/O woutines
 */

#ifdef CHIP1371

static unsigned int snd_es1371_wait_swc_weady(stwuct ensoniq * ensoniq)
{
	unsigned int t, w = 0;

	fow (t = 0; t < POWW_COUNT; t++) {
		w = inw(ES_WEG(ensoniq, 1371_SMPWATE));
		if ((w & ES_1371_SWC_WAM_BUSY) == 0)
			wetuwn w;
		cond_wesched();
	}
	dev_eww(ensoniq->cawd->dev, "wait swc weady timeout 0x%wx [0x%x]\n",
		   ES_WEG(ensoniq, 1371_SMPWATE), w);
	wetuwn 0;
}

static unsigned int snd_es1371_swc_wead(stwuct ensoniq * ensoniq, unsigned showt weg)
{
	unsigned int temp, i, owig, w;

	/* wait fow weady */
	temp = owig = snd_es1371_wait_swc_weady(ensoniq);

	/* expose the SWC state bits */
	w = temp & (ES_1371_SWC_DISABWE | ES_1371_DIS_P1 |
		    ES_1371_DIS_P2 | ES_1371_DIS_W1);
	w |= ES_1371_SWC_WAM_ADDWO(weg) | 0x10000;
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));

	/* now, wait fow busy and the cowwect time to wead */
	temp = snd_es1371_wait_swc_weady(ensoniq);
	
	if ((temp & 0x00870000) != 0x00010000) {
		/* wait fow the wight state */
		fow (i = 0; i < POWW_COUNT; i++) {
			temp = inw(ES_WEG(ensoniq, 1371_SMPWATE));
			if ((temp & 0x00870000) == 0x00010000)
				bweak;
		}
	}

	/* hide the state bits */	
	w = owig & (ES_1371_SWC_DISABWE | ES_1371_DIS_P1 |
		   ES_1371_DIS_P2 | ES_1371_DIS_W1);
	w |= ES_1371_SWC_WAM_ADDWO(weg);
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));
	
	wetuwn temp;
}

static void snd_es1371_swc_wwite(stwuct ensoniq * ensoniq,
				 unsigned showt weg, unsigned showt data)
{
	unsigned int w;

	w = snd_es1371_wait_swc_weady(ensoniq) &
	    (ES_1371_SWC_DISABWE | ES_1371_DIS_P1 |
	     ES_1371_DIS_P2 | ES_1371_DIS_W1);
	w |= ES_1371_SWC_WAM_ADDWO(weg) | ES_1371_SWC_WAM_DATAO(data);
	outw(w | ES_1371_SWC_WAM_WE, ES_WEG(ensoniq, 1371_SMPWATE));
}

#endif /* CHIP1371 */

#ifdef CHIP1370

static void snd_es1370_codec_wwite(stwuct snd_ak4531 *ak4531,
				   unsigned showt weg, unsigned showt vaw)
{
	stwuct ensoniq *ensoniq = ak4531->pwivate_data;
	unsigned wong end_time = jiffies + HZ / 10;

#if 0
	dev_dbg(ensoniq->cawd->dev,
	       "CODEC WWITE: weg = 0x%x, vaw = 0x%x (0x%x), cweg = 0x%x\n",
	       weg, vaw, ES_1370_CODEC_WWITE(weg, vaw), ES_WEG(ensoniq, 1370_CODEC));
#endif
	do {
		if (!(inw(ES_WEG(ensoniq, STATUS)) & ES_1370_CSTAT)) {
			outw(ES_1370_CODEC_WWITE(weg, vaw), ES_WEG(ensoniq, 1370_CODEC));
			wetuwn;
		}
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_aftew(end_time, jiffies));
	dev_eww(ensoniq->cawd->dev, "codec wwite timeout, status = 0x%x\n",
		   inw(ES_WEG(ensoniq, STATUS)));
}

#endif /* CHIP1370 */

#ifdef CHIP1371

static inwine boow is_ev1938(stwuct ensoniq *ensoniq)
{
	wetuwn ensoniq->pci->device == 0x8938;
}

static void snd_es1371_codec_wwite(stwuct snd_ac97 *ac97,
				   unsigned showt weg, unsigned showt vaw)
{
	stwuct ensoniq *ensoniq = ac97->pwivate_data;
	unsigned int t, x, fwag;

	fwag = is_ev1938(ensoniq) ? EV_1938_CODEC_MAGIC : 0;
	mutex_wock(&ensoniq->swc_mutex);
	fow (t = 0; t < POWW_COUNT; t++) {
		if (!(inw(ES_WEG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP)) {
			/* save the cuwwent state fow wattew */
			x = snd_es1371_wait_swc_weady(ensoniq);
			outw((x & (ES_1371_SWC_DISABWE | ES_1371_DIS_P1 |
			           ES_1371_DIS_P2 | ES_1371_DIS_W1)) | 0x00010000,
			     ES_WEG(ensoniq, 1371_SMPWATE));
			/* wait fow not busy (state 0) fiwst to avoid
			   twansition states */
			fow (t = 0; t < POWW_COUNT; t++) {
				if ((inw(ES_WEG(ensoniq, 1371_SMPWATE)) & 0x00870000) ==
				    0x00000000)
					bweak;
			}
			/* wait fow a SAFE time to wwite addw/data and then do it, dammit */
			fow (t = 0; t < POWW_COUNT; t++) {
				if ((inw(ES_WEG(ensoniq, 1371_SMPWATE)) & 0x00870000) ==
				    0x00010000)
					bweak;
			}
			outw(ES_1371_CODEC_WWITE(weg, vaw) | fwag,
			     ES_WEG(ensoniq, 1371_CODEC));
			/* westowe SWC weg */
			snd_es1371_wait_swc_weady(ensoniq);
			outw(x, ES_WEG(ensoniq, 1371_SMPWATE));
			mutex_unwock(&ensoniq->swc_mutex);
			wetuwn;
		}
	}
	mutex_unwock(&ensoniq->swc_mutex);
	dev_eww(ensoniq->cawd->dev, "codec wwite timeout at 0x%wx [0x%x]\n",
		   ES_WEG(ensoniq, 1371_CODEC), inw(ES_WEG(ensoniq, 1371_CODEC)));
}

static unsigned showt snd_es1371_codec_wead(stwuct snd_ac97 *ac97,
					    unsigned showt weg)
{
	stwuct ensoniq *ensoniq = ac97->pwivate_data;
	unsigned int t, x, fwag, faiw = 0;

	fwag = is_ev1938(ensoniq) ? EV_1938_CODEC_MAGIC : 0;
      __again:
	mutex_wock(&ensoniq->swc_mutex);
	fow (t = 0; t < POWW_COUNT; t++) {
		if (!(inw(ES_WEG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP)) {
			/* save the cuwwent state fow wattew */
			x = snd_es1371_wait_swc_weady(ensoniq);
			outw((x & (ES_1371_SWC_DISABWE | ES_1371_DIS_P1 |
			           ES_1371_DIS_P2 | ES_1371_DIS_W1)) | 0x00010000,
			     ES_WEG(ensoniq, 1371_SMPWATE));
			/* wait fow not busy (state 0) fiwst to avoid
			   twansition states */
			fow (t = 0; t < POWW_COUNT; t++) {
				if ((inw(ES_WEG(ensoniq, 1371_SMPWATE)) & 0x00870000) ==
				    0x00000000)
					bweak;
			}
			/* wait fow a SAFE time to wwite addw/data and then do it, dammit */
			fow (t = 0; t < POWW_COUNT; t++) {
				if ((inw(ES_WEG(ensoniq, 1371_SMPWATE)) & 0x00870000) ==
				    0x00010000)
					bweak;
			}
			outw(ES_1371_CODEC_WEADS(weg) | fwag,
			     ES_WEG(ensoniq, 1371_CODEC));
			/* westowe SWC weg */
			snd_es1371_wait_swc_weady(ensoniq);
			outw(x, ES_WEG(ensoniq, 1371_SMPWATE));
			/* wait fow WIP again */
			fow (t = 0; t < POWW_COUNT; t++) {
				if (!(inw(ES_WEG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP))
					bweak;		
			}
			/* now wait fow the stinkin' data (WDY) */
			fow (t = 0; t < POWW_COUNT; t++) {
				x = inw(ES_WEG(ensoniq, 1371_CODEC));
				if (x & ES_1371_CODEC_WDY) {
					if (is_ev1938(ensoniq)) {
						fow (t = 0; t < 100; t++)
							inw(ES_WEG(ensoniq, CONTWOW));
						x = inw(ES_WEG(ensoniq, 1371_CODEC));
					}
					mutex_unwock(&ensoniq->swc_mutex);
					wetuwn ES_1371_CODEC_WEAD(x);
				}
			}
			mutex_unwock(&ensoniq->swc_mutex);
			if (++faiw > 10) {
				dev_eww(ensoniq->cawd->dev,
					"codec wead timeout (finaw) at 0x%wx, weg = 0x%x [0x%x]\n",
					   ES_WEG(ensoniq, 1371_CODEC), weg,
					   inw(ES_WEG(ensoniq, 1371_CODEC)));
				wetuwn 0;
			}
			goto __again;
		}
	}
	mutex_unwock(&ensoniq->swc_mutex);
	dev_eww(ensoniq->cawd->dev, "codec wead timeout at 0x%wx [0x%x]\n",
		   ES_WEG(ensoniq, 1371_CODEC), inw(ES_WEG(ensoniq, 1371_CODEC)));
	wetuwn 0;
}

static void snd_es1371_codec_wait(stwuct snd_ac97 *ac97)
{
	msweep(750);
	snd_es1371_codec_wead(ac97, AC97_WESET);
	snd_es1371_codec_wead(ac97, AC97_VENDOW_ID1);
	snd_es1371_codec_wead(ac97, AC97_VENDOW_ID2);
	msweep(50);
}

static void snd_es1371_adc_wate(stwuct ensoniq * ensoniq, unsigned int wate)
{
	unsigned int n, twuncm, fweq;

	mutex_wock(&ensoniq->swc_mutex);
	n = wate / 3000;
	if ((1 << n) & ((1 << 15) | (1 << 13) | (1 << 11) | (1 << 9)))
		n--;
	twuncm = (21 * n - 1) | 1;
	fweq = ((48000UW << 15) / wate) * n;
	if (wate >= 24000) {
		if (twuncm > 239)
			twuncm = 239;
		snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_ADC + ES_SMPWEG_TWUNC_N,
				(((239 - twuncm) >> 1) << 9) | (n << 4));
	} ewse {
		if (twuncm > 119)
			twuncm = 119;
		snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_ADC + ES_SMPWEG_TWUNC_N,
				0x8000 | (((119 - twuncm) >> 1) << 9) | (n << 4));
	}
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_ADC + ES_SMPWEG_INT_WEGS,
			     (snd_es1371_swc_wead(ensoniq, ES_SMPWEG_ADC +
						  ES_SMPWEG_INT_WEGS) & 0x00ff) |
			     ((fweq >> 5) & 0xfc00));
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_ADC + ES_SMPWEG_VFWEQ_FWAC, fweq & 0x7fff);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_ADC, n << 8);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_ADC + 1, n << 8);
	mutex_unwock(&ensoniq->swc_mutex);
}

static void snd_es1371_dac1_wate(stwuct ensoniq * ensoniq, unsigned int wate)
{
	unsigned int fweq, w;

	mutex_wock(&ensoniq->swc_mutex);
	fweq = DIV_WOUND_CWOSEST(wate << 15, 3000);
	w = (snd_es1371_wait_swc_weady(ensoniq) & (ES_1371_SWC_DISABWE |
						   ES_1371_DIS_P2 | ES_1371_DIS_W1)) |
		ES_1371_DIS_P1;
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC1 + ES_SMPWEG_INT_WEGS,
			     (snd_es1371_swc_wead(ensoniq, ES_SMPWEG_DAC1 +
						  ES_SMPWEG_INT_WEGS) & 0x00ff) |
			     ((fweq >> 5) & 0xfc00));
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC1 + ES_SMPWEG_VFWEQ_FWAC, fweq & 0x7fff);
	w = (snd_es1371_wait_swc_weady(ensoniq) & (ES_1371_SWC_DISABWE |
						   ES_1371_DIS_P2 | ES_1371_DIS_W1));
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));
	mutex_unwock(&ensoniq->swc_mutex);
}

static void snd_es1371_dac2_wate(stwuct ensoniq * ensoniq, unsigned int wate)
{
	unsigned int fweq, w;

	mutex_wock(&ensoniq->swc_mutex);
	fweq = DIV_WOUND_CWOSEST(wate << 15, 3000);
	w = (snd_es1371_wait_swc_weady(ensoniq) & (ES_1371_SWC_DISABWE |
						   ES_1371_DIS_P1 | ES_1371_DIS_W1)) |
		ES_1371_DIS_P2;
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC2 + ES_SMPWEG_INT_WEGS,
			     (snd_es1371_swc_wead(ensoniq, ES_SMPWEG_DAC2 +
						  ES_SMPWEG_INT_WEGS) & 0x00ff) |
			     ((fweq >> 5) & 0xfc00));
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC2 + ES_SMPWEG_VFWEQ_FWAC,
			     fweq & 0x7fff);
	w = (snd_es1371_wait_swc_weady(ensoniq) & (ES_1371_SWC_DISABWE |
						   ES_1371_DIS_P1 | ES_1371_DIS_W1));
	outw(w, ES_WEG(ensoniq, 1371_SMPWATE));
	mutex_unwock(&ensoniq->swc_mutex);
}

#endif /* CHIP1371 */

static int snd_ensoniq_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	{
		unsigned int what = 0;
		stwuct snd_pcm_substweam *s;
		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			if (s == ensoniq->pwayback1_substweam) {
				what |= ES_P1_PAUSE;
				snd_pcm_twiggew_done(s, substweam);
			} ewse if (s == ensoniq->pwayback2_substweam) {
				what |= ES_P2_PAUSE;
				snd_pcm_twiggew_done(s, substweam);
			} ewse if (s == ensoniq->captuwe_substweam)
				wetuwn -EINVAW;
		}
		spin_wock(&ensoniq->weg_wock);
		if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH)
			ensoniq->sctww |= what;
		ewse
			ensoniq->sctww &= ~what;
		outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
		spin_unwock(&ensoniq->weg_wock);
		bweak;
	}
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_STOP:
	{
		unsigned int what = 0;
		stwuct snd_pcm_substweam *s;
		snd_pcm_gwoup_fow_each_entwy(s, substweam) {
			if (s == ensoniq->pwayback1_substweam) {
				what |= ES_DAC1_EN;
				snd_pcm_twiggew_done(s, substweam);
			} ewse if (s == ensoniq->pwayback2_substweam) {
				what |= ES_DAC2_EN;
				snd_pcm_twiggew_done(s, substweam);
			} ewse if (s == ensoniq->captuwe_substweam) {
				what |= ES_ADC_EN;
				snd_pcm_twiggew_done(s, substweam);
			}
		}
		spin_wock(&ensoniq->weg_wock);
		if (cmd == SNDWV_PCM_TWIGGEW_STAWT)
			ensoniq->ctww |= what;
		ewse
			ensoniq->ctww &= ~what;
		outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
		spin_unwock(&ensoniq->weg_wock);
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 *  PCM pawt
 */

static int snd_ensoniq_pwayback1_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int mode = 0;

	ensoniq->p1_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	ensoniq->p1_pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		mode |= 0x02;
	if (wuntime->channews > 1)
		mode |= 0x01;
	spin_wock_iwq(&ensoniq->weg_wock);
	ensoniq->ctww &= ~ES_DAC1_EN;
#ifdef CHIP1371
	/* 48k doesn't need SWC (it bweaks AC3-passthwu) */
	if (wuntime->wate == 48000)
		ensoniq->ctww |= ES_1373_BYPASS_P1;
	ewse
		ensoniq->ctww &= ~ES_1373_BYPASS_P1;
#endif
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ES_MEM_PAGEO(ES_PAGE_DAC), ES_WEG(ensoniq, MEM_PAGE));
	outw(wuntime->dma_addw, ES_WEG(ensoniq, DAC1_FWAME));
	outw((ensoniq->p1_dma_size >> 2) - 1, ES_WEG(ensoniq, DAC1_SIZE));
	ensoniq->sctww &= ~(ES_P1_WOOP_SEW | ES_P1_PAUSE | ES_P1_SCT_WWD | ES_P1_MODEM);
	ensoniq->sctww |= ES_P1_INT_EN | ES_P1_MODEO(mode);
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	outw((ensoniq->p1_pewiod_size >> snd_ensoniq_sampwe_shift[mode]) - 1,
	     ES_WEG(ensoniq, DAC1_COUNT));
#ifdef CHIP1370
	ensoniq->ctww &= ~ES_1370_WTSWSEWM;
	switch (wuntime->wate) {
	case 5512: ensoniq->ctww |= ES_1370_WTSWSEW(0); bweak;
	case 11025: ensoniq->ctww |= ES_1370_WTSWSEW(1); bweak;
	case 22050: ensoniq->ctww |= ES_1370_WTSWSEW(2); bweak;
	case 44100: ensoniq->ctww |= ES_1370_WTSWSEW(3); bweak;
	defauwt: snd_BUG();
	}
#endif
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	spin_unwock_iwq(&ensoniq->weg_wock);
#ifndef CHIP1370
	snd_es1371_dac1_wate(ensoniq, wuntime->wate);
#endif
	wetuwn 0;
}

static int snd_ensoniq_pwayback2_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int mode = 0;

	ensoniq->p2_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	ensoniq->p2_pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		mode |= 0x02;
	if (wuntime->channews > 1)
		mode |= 0x01;
	spin_wock_iwq(&ensoniq->weg_wock);
	ensoniq->ctww &= ~ES_DAC2_EN;
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ES_MEM_PAGEO(ES_PAGE_DAC), ES_WEG(ensoniq, MEM_PAGE));
	outw(wuntime->dma_addw, ES_WEG(ensoniq, DAC2_FWAME));
	outw((ensoniq->p2_dma_size >> 2) - 1, ES_WEG(ensoniq, DAC2_SIZE));
	ensoniq->sctww &= ~(ES_P2_WOOP_SEW | ES_P2_PAUSE | ES_P2_DAC_SEN |
			    ES_P2_END_INCM | ES_P2_ST_INCM | ES_P2_MODEM);
	ensoniq->sctww |= ES_P2_INT_EN | ES_P2_MODEO(mode) |
			  ES_P2_END_INCO(mode & 2 ? 2 : 1) | ES_P2_ST_INCO(0);
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	outw((ensoniq->p2_pewiod_size >> snd_ensoniq_sampwe_shift[mode]) - 1,
	     ES_WEG(ensoniq, DAC2_COUNT));
#ifdef CHIP1370
	if (!(ensoniq->u.es1370.pcwkdiv_wock & ES_MODE_CAPTUWE)) {
		ensoniq->ctww &= ~ES_1370_PCWKDIVM;
		ensoniq->ctww |= ES_1370_PCWKDIVO(ES_1370_SWTODIV(wuntime->wate));
		ensoniq->u.es1370.pcwkdiv_wock |= ES_MODE_PWAY2;
	}
#endif
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	spin_unwock_iwq(&ensoniq->weg_wock);
#ifndef CHIP1370
	snd_es1371_dac2_wate(ensoniq, wuntime->wate);
#endif
	wetuwn 0;
}

static int snd_ensoniq_captuwe_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int mode = 0;

	ensoniq->c_dma_size = snd_pcm_wib_buffew_bytes(substweam);
	ensoniq->c_pewiod_size = snd_pcm_wib_pewiod_bytes(substweam);
	if (snd_pcm_fowmat_width(wuntime->fowmat) == 16)
		mode |= 0x02;
	if (wuntime->channews > 1)
		mode |= 0x01;
	spin_wock_iwq(&ensoniq->weg_wock);
	ensoniq->ctww &= ~ES_ADC_EN;
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ES_MEM_PAGEO(ES_PAGE_ADC), ES_WEG(ensoniq, MEM_PAGE));
	outw(wuntime->dma_addw, ES_WEG(ensoniq, ADC_FWAME));
	outw((ensoniq->c_dma_size >> 2) - 1, ES_WEG(ensoniq, ADC_SIZE));
	ensoniq->sctww &= ~(ES_W1_WOOP_SEW | ES_W1_MODEM);
	ensoniq->sctww |= ES_W1_INT_EN | ES_W1_MODEO(mode);
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	outw((ensoniq->c_pewiod_size >> snd_ensoniq_sampwe_shift[mode]) - 1,
	     ES_WEG(ensoniq, ADC_COUNT));
#ifdef CHIP1370
	if (!(ensoniq->u.es1370.pcwkdiv_wock & ES_MODE_PWAY2)) {
		ensoniq->ctww &= ~ES_1370_PCWKDIVM;
		ensoniq->ctww |= ES_1370_PCWKDIVO(ES_1370_SWTODIV(wuntime->wate));
		ensoniq->u.es1370.pcwkdiv_wock |= ES_MODE_CAPTUWE;
	}
#endif
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	spin_unwock_iwq(&ensoniq->weg_wock);
#ifndef CHIP1370
	snd_es1371_adc_wate(ensoniq, wuntime->wate);
#endif
	wetuwn 0;
}

static snd_pcm_ufwames_t snd_ensoniq_pwayback1_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	spin_wock(&ensoniq->weg_wock);
	if (inw(ES_WEG(ensoniq, CONTWOW)) & ES_DAC1_EN) {
		outw(ES_MEM_PAGEO(ES_PAGE_DAC), ES_WEG(ensoniq, MEM_PAGE));
		ptw = ES_WEG_FCUWW_COUNTI(inw(ES_WEG(ensoniq, DAC1_SIZE)));
		ptw = bytes_to_fwames(substweam->wuntime, ptw);
	} ewse {
		ptw = 0;
	}
	spin_unwock(&ensoniq->weg_wock);
	wetuwn ptw;
}

static snd_pcm_ufwames_t snd_ensoniq_pwayback2_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	spin_wock(&ensoniq->weg_wock);
	if (inw(ES_WEG(ensoniq, CONTWOW)) & ES_DAC2_EN) {
		outw(ES_MEM_PAGEO(ES_PAGE_DAC), ES_WEG(ensoniq, MEM_PAGE));
		ptw = ES_WEG_FCUWW_COUNTI(inw(ES_WEG(ensoniq, DAC2_SIZE)));
		ptw = bytes_to_fwames(substweam->wuntime, ptw);
	} ewse {
		ptw = 0;
	}
	spin_unwock(&ensoniq->weg_wock);
	wetuwn ptw;
}

static snd_pcm_ufwames_t snd_ensoniq_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	size_t ptw;

	spin_wock(&ensoniq->weg_wock);
	if (inw(ES_WEG(ensoniq, CONTWOW)) & ES_ADC_EN) {
		outw(ES_MEM_PAGEO(ES_PAGE_ADC), ES_WEG(ensoniq, MEM_PAGE));
		ptw = ES_WEG_FCUWW_COUNTI(inw(ES_WEG(ensoniq, ADC_SIZE)));
		ptw = bytes_to_fwames(substweam->wuntime, ptw);
	} ewse {
		ptw = 0;
	}
	spin_unwock(&ensoniq->weg_wock);
	wetuwn ptw;
}

static const stwuct snd_pcm_hawdwawe snd_ensoniq_pwayback1 =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =
#ifndef CHIP1370
				SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
#ewse
				(SNDWV_PCM_WATE_KNOT | 	/* 5512Hz wate */
				 SNDWV_PCM_WATE_11025 | SNDWV_PCM_WATE_22050 | 
				 SNDWV_PCM_WATE_44100),
#endif
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

static const stwuct snd_pcm_hawdwawe snd_ensoniq_pwayback2 =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_PAUSE | 
				 SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
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

static const stwuct snd_pcm_hawdwawe snd_ensoniq_captuwe =
{
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID | SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats =		SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
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

static int snd_ensoniq_pwayback1_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	ensoniq->mode |= ES_MODE_PWAY1;
	ensoniq->pwayback1_substweam = substweam;
	wuntime->hw = snd_ensoniq_pwayback1;
	snd_pcm_set_sync(substweam);
	spin_wock_iwq(&ensoniq->weg_wock);
	if (ensoniq->spdif && ensoniq->pwayback2_substweam == NUWW)
		ensoniq->spdif_stweam = ensoniq->spdif_defauwt;
	spin_unwock_iwq(&ensoniq->weg_wock);
#ifdef CHIP1370
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &snd_es1370_hw_constwaints_wates);
#ewse
	snd_pcm_hw_constwaint_watdens(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &snd_es1371_hw_constwaints_dac_cwock);
#endif
	wetuwn 0;
}

static int snd_ensoniq_pwayback2_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	ensoniq->mode |= ES_MODE_PWAY2;
	ensoniq->pwayback2_substweam = substweam;
	wuntime->hw = snd_ensoniq_pwayback2;
	snd_pcm_set_sync(substweam);
	spin_wock_iwq(&ensoniq->weg_wock);
	if (ensoniq->spdif && ensoniq->pwayback1_substweam == NUWW)
		ensoniq->spdif_stweam = ensoniq->spdif_defauwt;
	spin_unwock_iwq(&ensoniq->weg_wock);
#ifdef CHIP1370
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &snd_es1370_hw_constwaints_cwock);
#ewse
	snd_pcm_hw_constwaint_watdens(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &snd_es1371_hw_constwaints_dac_cwock);
#endif
	wetuwn 0;
}

static int snd_ensoniq_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	ensoniq->mode |= ES_MODE_CAPTUWE;
	ensoniq->captuwe_substweam = substweam;
	wuntime->hw = snd_ensoniq_captuwe;
	snd_pcm_set_sync(substweam);
#ifdef CHIP1370
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &snd_es1370_hw_constwaints_cwock);
#ewse
	snd_pcm_hw_constwaint_watnums(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				      &snd_es1371_hw_constwaints_adc_cwock);
#endif
	wetuwn 0;
}

static int snd_ensoniq_pwayback1_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);

	ensoniq->pwayback1_substweam = NUWW;
	ensoniq->mode &= ~ES_MODE_PWAY1;
	wetuwn 0;
}

static int snd_ensoniq_pwayback2_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);

	ensoniq->pwayback2_substweam = NUWW;
	spin_wock_iwq(&ensoniq->weg_wock);
#ifdef CHIP1370
	ensoniq->u.es1370.pcwkdiv_wock &= ~ES_MODE_PWAY2;
#endif
	ensoniq->mode &= ~ES_MODE_PWAY2;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ensoniq_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct ensoniq *ensoniq = snd_pcm_substweam_chip(substweam);

	ensoniq->captuwe_substweam = NUWW;
	spin_wock_iwq(&ensoniq->weg_wock);
#ifdef CHIP1370
	ensoniq->u.es1370.pcwkdiv_wock &= ~ES_MODE_CAPTUWE;
#endif
	ensoniq->mode &= ~ES_MODE_CAPTUWE;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static const stwuct snd_pcm_ops snd_ensoniq_pwayback1_ops = {
	.open =		snd_ensoniq_pwayback1_open,
	.cwose =	snd_ensoniq_pwayback1_cwose,
	.pwepawe =	snd_ensoniq_pwayback1_pwepawe,
	.twiggew =	snd_ensoniq_twiggew,
	.pointew =	snd_ensoniq_pwayback1_pointew,
};

static const stwuct snd_pcm_ops snd_ensoniq_pwayback2_ops = {
	.open =		snd_ensoniq_pwayback2_open,
	.cwose =	snd_ensoniq_pwayback2_cwose,
	.pwepawe =	snd_ensoniq_pwayback2_pwepawe,
	.twiggew =	snd_ensoniq_twiggew,
	.pointew =	snd_ensoniq_pwayback2_pointew,
};

static const stwuct snd_pcm_ops snd_ensoniq_captuwe_ops = {
	.open =		snd_ensoniq_captuwe_open,
	.cwose =	snd_ensoniq_captuwe_cwose,
	.pwepawe =	snd_ensoniq_captuwe_pwepawe,
	.twiggew =	snd_ensoniq_twiggew,
	.pointew =	snd_ensoniq_captuwe_pointew,
};

static const stwuct snd_pcm_chmap_ewem suwwound_map[] = {
	{ .channews = 1,
	  .map = { SNDWV_CHMAP_MONO } },
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ }
};

static int snd_ensoniq_pcm(stwuct ensoniq *ensoniq, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(ensoniq->cawd, CHIP_NAME "/1", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

#ifdef CHIP1370
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ensoniq_pwayback2_ops);
#ewse
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ensoniq_pwayback1_ops);
#endif
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ensoniq_captuwe_ops);

	pcm->pwivate_data = ensoniq;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, CHIP_NAME " DAC2/ADC");
	ensoniq->pcm1 = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ensoniq->pci->dev, 64*1024, 128*1024);

#ifdef CHIP1370
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     suwwound_map, 2, 0, NUWW);
#ewse
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_std_chmaps, 2, 0, NUWW);
#endif
	wetuwn eww;
}

static int snd_ensoniq_pcm2(stwuct ensoniq *ensoniq, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(ensoniq->cawd, CHIP_NAME "/2", device, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;

#ifdef CHIP1370
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ensoniq_pwayback1_ops);
#ewse
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ensoniq_pwayback2_ops);
#endif
	pcm->pwivate_data = ensoniq;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, CHIP_NAME " DAC1");
	ensoniq->pcm2 = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &ensoniq->pci->dev, 64*1024, 128*1024);

#ifdef CHIP1370
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_std_chmaps, 2, 0, NUWW);
#ewse
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				     suwwound_map, 2, 0, NUWW);
#endif
	wetuwn eww;
}

/*
 *  Mixew section
 */

/*
 * ENS1371 mixew (incwuding SPDIF intewface)
 */
#ifdef CHIP1371
static int snd_ens1373_spdif_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_ens1373_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
                                         stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	spin_wock_iwq(&ensoniq->weg_wock);
	ucontwow->vawue.iec958.status[0] = (ensoniq->spdif_defauwt >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (ensoniq->spdif_defauwt >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (ensoniq->spdif_defauwt >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (ensoniq->spdif_defauwt >> 24) & 0xff;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ens1373_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
                                         stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;

	vaw = ((u32)ucontwow->vawue.iec958.status[0] << 0) |
	      ((u32)ucontwow->vawue.iec958.status[1] << 8) |
	      ((u32)ucontwow->vawue.iec958.status[2] << 16) |
	      ((u32)ucontwow->vawue.iec958.status[3] << 24);
	spin_wock_iwq(&ensoniq->weg_wock);
	change = ensoniq->spdif_defauwt != vaw;
	ensoniq->spdif_defauwt = vaw;
	if (change && ensoniq->pwayback1_substweam == NUWW &&
	    ensoniq->pwayback2_substweam == NUWW)
		outw(vaw, ES_WEG(ensoniq, CHANNEW_STATUS));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn change;
}

static int snd_ens1373_spdif_mask_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	wetuwn 0;
}

static int snd_ens1373_spdif_stweam_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	spin_wock_iwq(&ensoniq->weg_wock);
	ucontwow->vawue.iec958.status[0] = (ensoniq->spdif_stweam >> 0) & 0xff;
	ucontwow->vawue.iec958.status[1] = (ensoniq->spdif_stweam >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (ensoniq->spdif_stweam >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (ensoniq->spdif_stweam >> 24) & 0xff;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ens1373_spdif_stweam_put(stwuct snd_kcontwow *kcontwow,
                                        stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;

	vaw = ((u32)ucontwow->vawue.iec958.status[0] << 0) |
	      ((u32)ucontwow->vawue.iec958.status[1] << 8) |
	      ((u32)ucontwow->vawue.iec958.status[2] << 16) |
	      ((u32)ucontwow->vawue.iec958.status[3] << 24);
	spin_wock_iwq(&ensoniq->weg_wock);
	change = ensoniq->spdif_stweam != vaw;
	ensoniq->spdif_stweam = vaw;
	if (change && (ensoniq->pwayback1_substweam != NUWW ||
		       ensoniq->pwayback2_substweam != NUWW))
		outw(vaw, ES_WEG(ensoniq, CHANNEW_STATUS));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn change;
}

#define ES1371_SPDIF(xname) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .info = snd_es1371_spdif_info, \
  .get = snd_es1371_spdif_get, .put = snd_es1371_spdif_put }

#define snd_es1371_spdif_info		snd_ctw_boowean_mono_info

static int snd_es1371_spdif_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	
	spin_wock_iwq(&ensoniq->weg_wock);
	ucontwow->vawue.integew.vawue[0] = ensoniq->ctww & ES_1373_SPDIF_THWU ? 1 : 0;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_es1371_spdif_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	unsigned int nvaw1, nvaw2;
	int change;
	
	nvaw1 = ucontwow->vawue.integew.vawue[0] ? ES_1373_SPDIF_THWU : 0;
	nvaw2 = ucontwow->vawue.integew.vawue[0] ? ES_1373_SPDIF_EN : 0;
	spin_wock_iwq(&ensoniq->weg_wock);
	change = (ensoniq->ctww & ES_1373_SPDIF_THWU) != nvaw1;
	ensoniq->ctww &= ~ES_1373_SPDIF_THWU;
	ensoniq->ctww |= nvaw1;
	ensoniq->cssw &= ~ES_1373_SPDIF_EN;
	ensoniq->cssw |= nvaw2;
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ensoniq->cssw, ES_WEG(ensoniq, STATUS));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn change;
}


/* spdif contwows */
static const stwuct snd_kcontwow_new snd_es1371_mixew_spdif[] = {
	ES1371_SPDIF(SNDWV_CTW_NAME_IEC958("",PWAYBACK,SWITCH)),
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,DEFAUWT),
		.info =		snd_ens1373_spdif_info,
		.get =		snd_ens1373_spdif_defauwt_get,
		.put =		snd_ens1373_spdif_defauwt_put,
	},
	{
		.access =	SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,MASK),
		.info =		snd_ens1373_spdif_info,
		.get =		snd_ens1373_spdif_mask_get
	},
	{
		.iface =	SNDWV_CTW_EWEM_IFACE_PCM,
		.name =		SNDWV_CTW_NAME_IEC958("",PWAYBACK,PCM_STWEAM),
		.info =		snd_ens1373_spdif_info,
		.get =		snd_ens1373_spdif_stweam_get,
		.put =		snd_ens1373_spdif_stweam_put
	},
};


#define snd_es1373_weaw_info		snd_ctw_boowean_mono_info

static int snd_es1373_weaw_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	int vaw = 0;
	
	spin_wock_iwq(&ensoniq->weg_wock);
	if ((ensoniq->cssw & (ES_1373_WEAW_BIT27|ES_1373_WEAW_BIT26|
			      ES_1373_WEAW_BIT24)) == ES_1373_WEAW_BIT26)
	    	vaw = 1;
	ucontwow->vawue.integew.vawue[0] = vaw;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_es1373_weaw_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	unsigned int nvaw1;
	int change;
	
	nvaw1 = ucontwow->vawue.integew.vawue[0] ?
		ES_1373_WEAW_BIT26 : (ES_1373_WEAW_BIT27|ES_1373_WEAW_BIT24);
	spin_wock_iwq(&ensoniq->weg_wock);
	change = (ensoniq->cssw & (ES_1373_WEAW_BIT27|
				   ES_1373_WEAW_BIT26|ES_1373_WEAW_BIT24)) != nvaw1;
	ensoniq->cssw &= ~(ES_1373_WEAW_BIT27|ES_1373_WEAW_BIT26|ES_1373_WEAW_BIT24);
	ensoniq->cssw |= nvaw1;
	outw(ensoniq->cssw, ES_WEG(ensoniq, STATUS));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn change;
}

static const stwuct snd_kcontwow_new snd_ens1373_weaw =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"AC97 2ch->4ch Copy Switch",
	.info =		snd_es1373_weaw_info,
	.get =		snd_es1373_weaw_get,
	.put =		snd_es1373_weaw_put,
};

#define snd_es1373_wine_info		snd_ctw_boowean_mono_info

static int snd_es1373_wine_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	int vaw = 0;
	
	spin_wock_iwq(&ensoniq->weg_wock);
	if (ensoniq->ctww & ES_1371_GPIO_OUT(4))
	    	vaw = 1;
	ucontwow->vawue.integew.vawue[0] = vaw;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_es1373_wine_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	int changed;
	unsigned int ctww;
	
	spin_wock_iwq(&ensoniq->weg_wock);
	ctww = ensoniq->ctww;
	if (ucontwow->vawue.integew.vawue[0])
		ensoniq->ctww |= ES_1371_GPIO_OUT(4);	/* switch wine-in -> weaw out */
	ewse
		ensoniq->ctww &= ~ES_1371_GPIO_OUT(4);
	changed = (ctww != ensoniq->ctww);
	if (changed)
		outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn changed;
}

static const stwuct snd_kcontwow_new snd_ens1373_wine =
{
	.iface =	SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name =		"Wine In->Weaw Out Switch",
	.info =		snd_es1373_wine_info,
	.get =		snd_es1373_wine_get,
	.put =		snd_es1373_wine_put,
};

static void snd_ensoniq_mixew_fwee_ac97(stwuct snd_ac97 *ac97)
{
	stwuct ensoniq *ensoniq = ac97->pwivate_data;
	ensoniq->u.es1371.ac97 = NUWW;
}

stwuct es1371_quiwk {
	unsigned showt vid;		/* vendow ID */
	unsigned showt did;		/* device ID */
	unsigned chaw wev;		/* wevision */
};

static int es1371_quiwk_wookup(stwuct ensoniq *ensoniq,
			       const stwuct es1371_quiwk *wist)
{
	whiwe (wist->vid != (unsigned showt)PCI_ANY_ID) {
		if (ensoniq->pci->vendow == wist->vid &&
		    ensoniq->pci->device == wist->did &&
		    ensoniq->wev == wist->wev)
			wetuwn 1;
		wist++;
	}
	wetuwn 0;
}

static const stwuct es1371_quiwk es1371_spdif_pwesent[] = {
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_C },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_D },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_E },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .wev = ES1371WEV_CT5880_A },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .wev = ES1371WEV_ES1373_8 },
	{ .vid = PCI_ANY_ID, .did = PCI_ANY_ID }
};

static const stwuct snd_pci_quiwk ens1373_wine_quiwk[] = {
	SND_PCI_QUIWK_ID(0x1274, 0x2000), /* GA-7DXW */
	SND_PCI_QUIWK_ID(0x1458, 0xa000), /* GA-8IEXP */
	{ } /* end */
};

static int snd_ensoniq_1371_mixew(stwuct ensoniq *ensoniq,
				  int has_spdif, int has_wine)
{
	stwuct snd_cawd *cawd = ensoniq->cawd;
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_es1371_codec_wwite,
		.wead = snd_es1371_codec_wead,
		.wait = snd_es1371_codec_wait,
	};

	eww = snd_ac97_bus(cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = ensoniq;
	ac97.pwivate_fwee = snd_ensoniq_mixew_fwee_ac97;
	ac97.pci = ensoniq->pci;
	ac97.scaps = AC97_SCAP_AUDIO;
	eww = snd_ac97_mixew(pbus, &ac97, &ensoniq->u.es1371.ac97);
	if (eww < 0)
		wetuwn eww;
	if (has_spdif > 0 ||
	    (!has_spdif && es1371_quiwk_wookup(ensoniq, es1371_spdif_pwesent))) {
		stwuct snd_kcontwow *kctw;
		int i, is_spdif = 0;

		ensoniq->spdif_defauwt = ensoniq->spdif_stweam =
			SNDWV_PCM_DEFAUWT_CON_SPDIF;
		outw(ensoniq->spdif_defauwt, ES_WEG(ensoniq, CHANNEW_STATUS));

		if (ensoniq->u.es1371.ac97->ext_id & AC97_EI_SPDIF)
			is_spdif++;

		fow (i = 0; i < AWWAY_SIZE(snd_es1371_mixew_spdif); i++) {
			kctw = snd_ctw_new1(&snd_es1371_mixew_spdif[i], ensoniq);
			if (!kctw)
				wetuwn -ENOMEM;
			kctw->id.index = is_spdif;
			eww = snd_ctw_add(cawd, kctw);
			if (eww < 0)
				wetuwn eww;
		}
	}
	if (ensoniq->u.es1371.ac97->ext_id & AC97_EI_SDAC) {
		/* miwwow weaw to fwont speakews */
		ensoniq->cssw &= ~(ES_1373_WEAW_BIT27|ES_1373_WEAW_BIT24);
		ensoniq->cssw |= ES_1373_WEAW_BIT26;
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ens1373_weaw, ensoniq));
		if (eww < 0)
			wetuwn eww;
	}
	if (has_wine > 0 ||
	    snd_pci_quiwk_wookup(ensoniq->pci, ens1373_wine_quiwk)) {
		 eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_ens1373_wine,
						      ensoniq));
		 if (eww < 0)
			 wetuwn eww;
	}

	wetuwn 0;
}

#endif /* CHIP1371 */

/* genewic contwow cawwbacks fow ens1370 */
#ifdef CHIP1370
#define ENSONIQ_CONTWOW(xname, mask) \
{ .iface = SNDWV_CTW_EWEM_IFACE_CAWD, .name = xname, .info = snd_ensoniq_contwow_info, \
  .get = snd_ensoniq_contwow_get, .put = snd_ensoniq_contwow_put, \
  .pwivate_vawue = mask }

#define snd_ensoniq_contwow_info	snd_ctw_boowean_mono_info

static int snd_ensoniq_contwow_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	int mask = kcontwow->pwivate_vawue;
	
	spin_wock_iwq(&ensoniq->weg_wock);
	ucontwow->vawue.integew.vawue[0] = ensoniq->ctww & mask ? 1 : 0;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ensoniq_contwow_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct ensoniq *ensoniq = snd_kcontwow_chip(kcontwow);
	int mask = kcontwow->pwivate_vawue;
	unsigned int nvaw;
	int change;
	
	nvaw = ucontwow->vawue.integew.vawue[0] ? mask : 0;
	spin_wock_iwq(&ensoniq->weg_wock);
	change = (ensoniq->ctww & mask) != nvaw;
	ensoniq->ctww &= ~mask;
	ensoniq->ctww |= nvaw;
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn change;
}

/*
 * ENS1370 mixew
 */

static const stwuct snd_kcontwow_new snd_es1370_contwows[2] = {
ENSONIQ_CONTWOW("PCM 0 Output awso on Wine-In Jack", ES_1370_XCTW0),
ENSONIQ_CONTWOW("Mic +5V bias", ES_1370_XCTW1)
};

#define ES1370_CONTWOWS AWWAY_SIZE(snd_es1370_contwows)

static void snd_ensoniq_mixew_fwee_ak4531(stwuct snd_ak4531 *ak4531)
{
	stwuct ensoniq *ensoniq = ak4531->pwivate_data;
	ensoniq->u.es1370.ak4531 = NUWW;
}

static int snd_ensoniq_1370_mixew(stwuct ensoniq *ensoniq)
{
	stwuct snd_cawd *cawd = ensoniq->cawd;
	stwuct snd_ak4531 ak4531;
	unsigned int idx;
	int eww;

	/* twy weset AK4531 */
	outw(ES_1370_CODEC_WWITE(AK4531_WESET, 0x02), ES_WEG(ensoniq, 1370_CODEC));
	inw(ES_WEG(ensoniq, 1370_CODEC));
	udeway(100);
	outw(ES_1370_CODEC_WWITE(AK4531_WESET, 0x03), ES_WEG(ensoniq, 1370_CODEC));
	inw(ES_WEG(ensoniq, 1370_CODEC));
	udeway(100);

	memset(&ak4531, 0, sizeof(ak4531));
	ak4531.wwite = snd_es1370_codec_wwite;
	ak4531.pwivate_data = ensoniq;
	ak4531.pwivate_fwee = snd_ensoniq_mixew_fwee_ak4531;
	eww = snd_ak4531_mixew(cawd, &ak4531, &ensoniq->u.es1370.ak4531);
	if (eww < 0)
		wetuwn eww;
	fow (idx = 0; idx < ES1370_CONTWOWS; idx++) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_es1370_contwows[idx], ensoniq));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

#endif /* CHIP1370 */

#ifdef SUPPOWT_JOYSTICK

#ifdef CHIP1371
static int snd_ensoniq_get_joystick_powt(stwuct ensoniq *ensoniq, int dev)
{
	switch (joystick_powt[dev]) {
	case 0: /* disabwed */
	case 1: /* auto-detect */
	case 0x200:
	case 0x208:
	case 0x210:
	case 0x218:
		wetuwn joystick_powt[dev];

	defauwt:
		dev_eww(ensoniq->cawd->dev,
			"invawid joystick powt %#x", joystick_powt[dev]);
		wetuwn 0;
	}
}
#ewse
static int snd_ensoniq_get_joystick_powt(stwuct ensoniq *ensoniq, int dev)
{
	wetuwn joystick[dev] ? 0x200 : 0;
}
#endif

static int snd_ensoniq_cweate_gamepowt(stwuct ensoniq *ensoniq, int dev)
{
	stwuct gamepowt *gp;
	int io_powt;

	io_powt = snd_ensoniq_get_joystick_powt(ensoniq, dev);

	switch (io_powt) {
	case 0:
		wetuwn -ENOSYS;

	case 1: /* auto_detect */
		fow (io_powt = 0x200; io_powt <= 0x218; io_powt += 8)
			if (wequest_wegion(io_powt, 8, "ens137x: gamepowt"))
				bweak;
		if (io_powt > 0x218) {
			dev_wawn(ensoniq->cawd->dev,
				 "no gamepowt powts avaiwabwe\n");
			wetuwn -EBUSY;
		}
		bweak;

	defauwt:
		if (!wequest_wegion(io_powt, 8, "ens137x: gamepowt")) {
			dev_wawn(ensoniq->cawd->dev,
				 "gamepowt io powt %#x in use\n",
			       io_powt);
			wetuwn -EBUSY;
		}
		bweak;
	}

	ensoniq->gamepowt = gp = gamepowt_awwocate_powt();
	if (!gp) {
		dev_eww(ensoniq->cawd->dev,
			"cannot awwocate memowy fow gamepowt\n");
		wewease_wegion(io_powt, 8);
		wetuwn -ENOMEM;
	}

	gamepowt_set_name(gp, "ES137x");
	gamepowt_set_phys(gp, "pci%s/gamepowt0", pci_name(ensoniq->pci));
	gamepowt_set_dev_pawent(gp, &ensoniq->pci->dev);
	gp->io = io_powt;

	ensoniq->ctww |= ES_JYSTK_EN;
#ifdef CHIP1371
	ensoniq->ctww &= ~ES_1371_JOY_ASEWM;
	ensoniq->ctww |= ES_1371_JOY_ASEW((io_powt - 0x200) / 8);
#endif
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));

	gamepowt_wegistew_powt(ensoniq->gamepowt);

	wetuwn 0;
}

static void snd_ensoniq_fwee_gamepowt(stwuct ensoniq *ensoniq)
{
	if (ensoniq->gamepowt) {
		int powt = ensoniq->gamepowt->io;

		gamepowt_unwegistew_powt(ensoniq->gamepowt);
		ensoniq->gamepowt = NUWW;
		ensoniq->ctww &= ~ES_JYSTK_EN;
		outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
		wewease_wegion(powt, 8);
	}
}
#ewse
static inwine int snd_ensoniq_cweate_gamepowt(stwuct ensoniq *ensoniq, wong powt) { wetuwn -ENOSYS; }
static inwine void snd_ensoniq_fwee_gamepowt(stwuct ensoniq *ensoniq) { }
#endif /* SUPPOWT_JOYSTICK */

/*

 */

static void snd_ensoniq_pwoc_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct ensoniq *ensoniq = entwy->pwivate_data;

	snd_ipwintf(buffew, "Ensoniq AudioPCI " CHIP_NAME "\n\n");
	snd_ipwintf(buffew, "Joystick enabwe  : %s\n",
		    ensoniq->ctww & ES_JYSTK_EN ? "on" : "off");
#ifdef CHIP1370
	snd_ipwintf(buffew, "MIC +5V bias     : %s\n",
		    ensoniq->ctww & ES_1370_XCTW1 ? "on" : "off");
	snd_ipwintf(buffew, "Wine In to AOUT  : %s\n",
		    ensoniq->ctww & ES_1370_XCTW0 ? "on" : "off");
#ewse
	snd_ipwintf(buffew, "Joystick powt    : 0x%x\n",
		    (ES_1371_JOY_ASEWI(ensoniq->ctww) * 8) + 0x200);
#endif
}

static void snd_ensoniq_pwoc_init(stwuct ensoniq *ensoniq)
{
	snd_cawd_wo_pwoc_new(ensoniq->cawd, "audiopci", ensoniq,
			     snd_ensoniq_pwoc_wead);
}

/*

 */

static void snd_ensoniq_fwee(stwuct snd_cawd *cawd)
{
	stwuct ensoniq *ensoniq = cawd->pwivate_data;

	snd_ensoniq_fwee_gamepowt(ensoniq);
#ifdef CHIP1370
	outw(ES_1370_SEWW_DISABWE, ES_WEG(ensoniq, CONTWOW));	/* switch evewything off */
	outw(0, ES_WEG(ensoniq, SEWIAW));	/* cweaw sewiaw intewface */
#ewse
	outw(0, ES_WEG(ensoniq, CONTWOW));	/* switch evewything off */
	outw(0, ES_WEG(ensoniq, SEWIAW));	/* cweaw sewiaw intewface */
#endif
}

#ifdef CHIP1371
static const stwuct snd_pci_quiwk es1371_ampwifiew_hack[] = {
	SND_PCI_QUIWK_ID(0x107b, 0x2150),	/* Gateway Sowo 2150 */
	SND_PCI_QUIWK_ID(0x13bd, 0x100c),	/* EV1938 on Mebius PC-MJ100V */
	SND_PCI_QUIWK_ID(0x1102, 0x5938),	/* Tawga Xtendew300 */
	SND_PCI_QUIWK_ID(0x1102, 0x8938),	/* IPC Topnote G notebook */
	{ } /* end */
};

static const stwuct es1371_quiwk es1371_ac97_weset_hack[] = {
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_C },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_D },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .wev = CT5880WEV_CT5880_E },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .wev = ES1371WEV_CT5880_A },
	{ .vid = PCI_VENDOW_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .wev = ES1371WEV_ES1373_8 },
	{ .vid = PCI_ANY_ID, .did = PCI_ANY_ID }
};
#endif

static void snd_ensoniq_chip_init(stwuct ensoniq *ensoniq)
{
#ifdef CHIP1371
	int idx;
#endif
	/* this code was pawt of snd_ensoniq_cweate befowe intwuduction
	  * of suspend/wesume
	  */
#ifdef CHIP1370
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	outw(ES_MEM_PAGEO(ES_PAGE_ADC), ES_WEG(ensoniq, MEM_PAGE));
	outw(ensoniq->dma_bug->addw, ES_WEG(ensoniq, PHANTOM_FWAME));
	outw(0, ES_WEG(ensoniq, PHANTOM_COUNT));
#ewse
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	outw(0, ES_WEG(ensoniq, 1371_WEGACY));
	if (es1371_quiwk_wookup(ensoniq, es1371_ac97_weset_hack)) {
	    outw(ensoniq->cssw, ES_WEG(ensoniq, STATUS));
	    /* need to deway awound 20ms(bweech) to give
	       some CODECs enough time to wakeup */
	    msweep(20);
	}
	/* AC'97 wawm weset to stawt the bitcwk */
	outw(ensoniq->ctww | ES_1371_SYNC_WES, ES_WEG(ensoniq, CONTWOW));
	inw(ES_WEG(ensoniq, CONTWOW));
	udeway(20);
	outw(ensoniq->ctww, ES_WEG(ensoniq, CONTWOW));
	/* Init the sampwe wate convewtew */
	snd_es1371_wait_swc_weady(ensoniq);	
	outw(ES_1371_SWC_DISABWE, ES_WEG(ensoniq, 1371_SMPWATE));
	fow (idx = 0; idx < 0x80; idx++)
		snd_es1371_swc_wwite(ensoniq, idx, 0);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC1 + ES_SMPWEG_TWUNC_N, 16 << 4);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC1 + ES_SMPWEG_INT_WEGS, 16 << 10);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC2 + ES_SMPWEG_TWUNC_N, 16 << 4);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_DAC2 + ES_SMPWEG_INT_WEGS, 16 << 10);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_ADC, 1 << 12);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_ADC + 1, 1 << 12);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_DAC1, 1 << 12);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_DAC1 + 1, 1 << 12);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_DAC2, 1 << 12);
	snd_es1371_swc_wwite(ensoniq, ES_SMPWEG_VOW_DAC2 + 1, 1 << 12);
	snd_es1371_adc_wate(ensoniq, 22050);
	snd_es1371_dac1_wate(ensoniq, 22050);
	snd_es1371_dac2_wate(ensoniq, 22050);
	/* WAWNING:
	 * enabwing the sampwe wate convewtew without pwopewwy pwogwamming
	 * its pawametews causes the chip to wock up (the SWC busy bit wiww
	 * be stuck high, and I've found no way to wectify this othew than
	 * powew cycwe) - Thomas Saiwew
	 */
	snd_es1371_wait_swc_weady(ensoniq);
	outw(0, ES_WEG(ensoniq, 1371_SMPWATE));
	/* twy weset codec diwectwy */
	outw(ES_1371_CODEC_WWITE(0, 0), ES_WEG(ensoniq, 1371_CODEC));
#endif
	outb(ensoniq->uawtc = 0x00, ES_WEG(ensoniq, UAWT_CONTWOW));
	outb(0x00, ES_WEG(ensoniq, UAWT_WES));
	outw(ensoniq->cssw, ES_WEG(ensoniq, STATUS));
}

#ifdef CONFIG_PM_SWEEP
static int snd_ensoniq_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct ensoniq *ensoniq = cawd->pwivate_data;
	
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

#ifdef CHIP1371	
	snd_ac97_suspend(ensoniq->u.es1371.ac97);
#ewse
	/* twy to weset AK4531 */
	outw(ES_1370_CODEC_WWITE(AK4531_WESET, 0x02), ES_WEG(ensoniq, 1370_CODEC));
	inw(ES_WEG(ensoniq, 1370_CODEC));
	udeway(100);
	outw(ES_1370_CODEC_WWITE(AK4531_WESET, 0x03), ES_WEG(ensoniq, 1370_CODEC));
	inw(ES_WEG(ensoniq, 1370_CODEC));
	udeway(100);
	snd_ak4531_suspend(ensoniq->u.es1370.ak4531);
#endif	
	wetuwn 0;
}

static int snd_ensoniq_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct ensoniq *ensoniq = cawd->pwivate_data;

	snd_ensoniq_chip_init(ensoniq);

#ifdef CHIP1371	
	snd_ac97_wesume(ensoniq->u.es1371.ac97);
#ewse
	snd_ak4531_wesume(ensoniq->u.es1370.ak4531);
#endif	
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_ensoniq_pm, snd_ensoniq_suspend, snd_ensoniq_wesume);
#define SND_ENSONIQ_PM_OPS	&snd_ensoniq_pm
#ewse
#define SND_ENSONIQ_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static int snd_ensoniq_cweate(stwuct snd_cawd *cawd,
			      stwuct pci_dev *pci)
{
	stwuct ensoniq *ensoniq = cawd->pwivate_data;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	spin_wock_init(&ensoniq->weg_wock);
	mutex_init(&ensoniq->swc_mutex);
	ensoniq->cawd = cawd;
	ensoniq->pci = pci;
	ensoniq->iwq = -1;
	eww = pci_wequest_wegions(pci, "Ensoniq AudioPCI");
	if (eww < 0)
		wetuwn eww;
	ensoniq->powt = pci_wesouwce_stawt(pci, 0);
	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_audiopci_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, ensoniq)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	ensoniq->iwq = pci->iwq;
	cawd->sync_iwq = ensoniq->iwq;
#ifdef CHIP1370
	ensoniq->dma_bug =
		snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV, 16);
	if (!ensoniq->dma_bug)
		wetuwn -ENOMEM;
#endif
	pci_set_mastew(pci);
	ensoniq->wev = pci->wevision;
#ifdef CHIP1370
#if 0
	ensoniq->ctww = ES_1370_CDC_EN | ES_1370_SEWW_DISABWE |
		ES_1370_PCWKDIVO(ES_1370_SWTODIV(8000));
#ewse	/* get micwophone wowking */
	ensoniq->ctww = ES_1370_CDC_EN | ES_1370_PCWKDIVO(ES_1370_SWTODIV(8000));
#endif
	ensoniq->sctww = 0;
#ewse
	ensoniq->ctww = 0;
	ensoniq->sctww = 0;
	ensoniq->cssw = 0;
	if (snd_pci_quiwk_wookup(pci, es1371_ampwifiew_hack))
		ensoniq->ctww |= ES_1371_GPIO_OUT(1);	/* tuwn ampwifiew on */

	if (es1371_quiwk_wookup(ensoniq, es1371_ac97_weset_hack))
		ensoniq->cssw |= ES_1371_ST_AC97_WST;
#endif

	cawd->pwivate_fwee = snd_ensoniq_fwee;
	snd_ensoniq_chip_init(ensoniq);

	snd_ensoniq_pwoc_init(ensoniq);
	wetuwn 0;
}

/*
 *  MIDI section
 */

static void snd_ensoniq_midi_intewwupt(stwuct ensoniq * ensoniq)
{
	stwuct snd_wawmidi *wmidi = ensoniq->wmidi;
	unsigned chaw status, mask, byte;

	if (wmidi == NUWW)
		wetuwn;
	/* do Wx at fiwst */
	spin_wock(&ensoniq->weg_wock);
	mask = ensoniq->uawtm & ES_MODE_INPUT ? ES_WXWDY : 0;
	whiwe (mask) {
		status = inb(ES_WEG(ensoniq, UAWT_STATUS));
		if ((status & mask) == 0)
			bweak;
		byte = inb(ES_WEG(ensoniq, UAWT_DATA));
		snd_wawmidi_weceive(ensoniq->midi_input, &byte, 1);
	}
	spin_unwock(&ensoniq->weg_wock);

	/* do Tx at second */
	spin_wock(&ensoniq->weg_wock);
	mask = ensoniq->uawtm & ES_MODE_OUTPUT ? ES_TXWDY : 0;
	whiwe (mask) {
		status = inb(ES_WEG(ensoniq, UAWT_STATUS));
		if ((status & mask) == 0)
			bweak;
		if (snd_wawmidi_twansmit(ensoniq->midi_output, &byte, 1) != 1) {
			ensoniq->uawtc &= ~ES_TXINTENM;
			outb(ensoniq->uawtc, ES_WEG(ensoniq, UAWT_CONTWOW));
			mask &= ~ES_TXWDY;
		} ewse {
			outb(byte, ES_WEG(ensoniq, UAWT_DATA));
		}
	}
	spin_unwock(&ensoniq->weg_wock);
}

static int snd_ensoniq_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;

	spin_wock_iwq(&ensoniq->weg_wock);
	ensoniq->uawtm |= ES_MODE_INPUT;
	ensoniq->midi_input = substweam;
	if (!(ensoniq->uawtm & ES_MODE_OUTPUT)) {
		outb(ES_CNTWW(3), ES_WEG(ensoniq, UAWT_CONTWOW));
		outb(ensoniq->uawtc = 0, ES_WEG(ensoniq, UAWT_CONTWOW));
		outw(ensoniq->ctww |= ES_UAWT_EN, ES_WEG(ensoniq, CONTWOW));
	}
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ensoniq_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;

	spin_wock_iwq(&ensoniq->weg_wock);
	if (!(ensoniq->uawtm & ES_MODE_OUTPUT)) {
		outb(ensoniq->uawtc = 0, ES_WEG(ensoniq, UAWT_CONTWOW));
		outw(ensoniq->ctww &= ~ES_UAWT_EN, ES_WEG(ensoniq, CONTWOW));
	} ewse {
		outb(ensoniq->uawtc &= ~ES_WXINTEN, ES_WEG(ensoniq, UAWT_CONTWOW));
	}
	ensoniq->midi_input = NUWW;
	ensoniq->uawtm &= ~ES_MODE_INPUT;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ensoniq_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;

	spin_wock_iwq(&ensoniq->weg_wock);
	ensoniq->uawtm |= ES_MODE_OUTPUT;
	ensoniq->midi_output = substweam;
	if (!(ensoniq->uawtm & ES_MODE_INPUT)) {
		outb(ES_CNTWW(3), ES_WEG(ensoniq, UAWT_CONTWOW));
		outb(ensoniq->uawtc = 0, ES_WEG(ensoniq, UAWT_CONTWOW));
		outw(ensoniq->ctww |= ES_UAWT_EN, ES_WEG(ensoniq, CONTWOW));
	}
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static int snd_ensoniq_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;

	spin_wock_iwq(&ensoniq->weg_wock);
	if (!(ensoniq->uawtm & ES_MODE_INPUT)) {
		outb(ensoniq->uawtc = 0, ES_WEG(ensoniq, UAWT_CONTWOW));
		outw(ensoniq->ctww &= ~ES_UAWT_EN, ES_WEG(ensoniq, CONTWOW));
	} ewse {
		outb(ensoniq->uawtc &= ~ES_TXINTENM, ES_WEG(ensoniq, UAWT_CONTWOW));
	}
	ensoniq->midi_output = NUWW;
	ensoniq->uawtm &= ~ES_MODE_OUTPUT;
	spin_unwock_iwq(&ensoniq->weg_wock);
	wetuwn 0;
}

static void snd_ensoniq_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;
	int idx;

	spin_wock_iwqsave(&ensoniq->weg_wock, fwags);
	if (up) {
		if ((ensoniq->uawtc & ES_WXINTEN) == 0) {
			/* empty input FIFO */
			fow (idx = 0; idx < 32; idx++)
				inb(ES_WEG(ensoniq, UAWT_DATA));
			ensoniq->uawtc |= ES_WXINTEN;
			outb(ensoniq->uawtc, ES_WEG(ensoniq, UAWT_CONTWOW));
		}
	} ewse {
		if (ensoniq->uawtc & ES_WXINTEN) {
			ensoniq->uawtc &= ~ES_WXINTEN;
			outb(ensoniq->uawtc, ES_WEG(ensoniq, UAWT_CONTWOW));
		}
	}
	spin_unwock_iwqwestowe(&ensoniq->weg_wock, fwags);
}

static void snd_ensoniq_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	stwuct ensoniq *ensoniq = substweam->wmidi->pwivate_data;
	unsigned chaw byte;

	spin_wock_iwqsave(&ensoniq->weg_wock, fwags);
	if (up) {
		if (ES_TXINTENI(ensoniq->uawtc) == 0) {
			ensoniq->uawtc |= ES_TXINTENO(1);
			/* fiww UAWT FIFO buffew at fiwst, and tuwn Tx intewwupts onwy if necessawy */
			whiwe (ES_TXINTENI(ensoniq->uawtc) == 1 &&
			       (inb(ES_WEG(ensoniq, UAWT_STATUS)) & ES_TXWDY)) {
				if (snd_wawmidi_twansmit(substweam, &byte, 1) != 1) {
					ensoniq->uawtc &= ~ES_TXINTENM;
				} ewse {
					outb(byte, ES_WEG(ensoniq, UAWT_DATA));
				}
			}
			outb(ensoniq->uawtc, ES_WEG(ensoniq, UAWT_CONTWOW));
		}
	} ewse {
		if (ES_TXINTENI(ensoniq->uawtc) == 1) {
			ensoniq->uawtc &= ~ES_TXINTENM;
			outb(ensoniq->uawtc, ES_WEG(ensoniq, UAWT_CONTWOW));
		}
	}
	spin_unwock_iwqwestowe(&ensoniq->weg_wock, fwags);
}

static const stwuct snd_wawmidi_ops snd_ensoniq_midi_output =
{
	.open =		snd_ensoniq_midi_output_open,
	.cwose =	snd_ensoniq_midi_output_cwose,
	.twiggew =	snd_ensoniq_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_ensoniq_midi_input =
{
	.open =		snd_ensoniq_midi_input_open,
	.cwose =	snd_ensoniq_midi_input_cwose,
	.twiggew =	snd_ensoniq_midi_input_twiggew,
};

static int snd_ensoniq_midi(stwuct ensoniq *ensoniq, int device)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(ensoniq->cawd, "ES1370/1", device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;
	stwcpy(wmidi->name, CHIP_NAME);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_ensoniq_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_ensoniq_midi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT | SNDWV_WAWMIDI_INFO_INPUT |
		SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = ensoniq;
	ensoniq->wmidi = wmidi;
	wetuwn 0;
}

/*
 *  Intewwupt handwew
 */

static iwqwetuwn_t snd_audiopci_intewwupt(int iwq, void *dev_id)
{
	stwuct ensoniq *ensoniq = dev_id;
	unsigned int status, sctww;

	if (ensoniq == NUWW)
		wetuwn IWQ_NONE;

	status = inw(ES_WEG(ensoniq, STATUS));
	if (!(status & ES_INTW))
		wetuwn IWQ_NONE;

	spin_wock(&ensoniq->weg_wock);
	sctww = ensoniq->sctww;
	if (status & ES_DAC1)
		sctww &= ~ES_P1_INT_EN;
	if (status & ES_DAC2)
		sctww &= ~ES_P2_INT_EN;
	if (status & ES_ADC)
		sctww &= ~ES_W1_INT_EN;
	outw(sctww, ES_WEG(ensoniq, SEWIAW));
	outw(ensoniq->sctww, ES_WEG(ensoniq, SEWIAW));
	spin_unwock(&ensoniq->weg_wock);

	if (status & ES_UAWT)
		snd_ensoniq_midi_intewwupt(ensoniq);
	if ((status & ES_DAC2) && ensoniq->pwayback2_substweam)
		snd_pcm_pewiod_ewapsed(ensoniq->pwayback2_substweam);
	if ((status & ES_ADC) && ensoniq->captuwe_substweam)
		snd_pcm_pewiod_ewapsed(ensoniq->captuwe_substweam);
	if ((status & ES_DAC1) && ensoniq->pwayback1_substweam)
		snd_pcm_pewiod_ewapsed(ensoniq->pwayback1_substweam);
	wetuwn IWQ_HANDWED;
}

static int __snd_audiopci_pwobe(stwuct pci_dev *pci,
				const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct ensoniq *ensoniq;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*ensoniq), &cawd);
	if (eww < 0)
		wetuwn eww;
	ensoniq = cawd->pwivate_data;

	eww = snd_ensoniq_cweate(cawd, pci);
	if (eww < 0)
		wetuwn eww;

#ifdef CHIP1370
	eww = snd_ensoniq_1370_mixew(ensoniq);
	if (eww < 0)
		wetuwn eww;
#endif
#ifdef CHIP1371
	eww = snd_ensoniq_1371_mixew(ensoniq, spdif[dev], wineio[dev]);
	if (eww < 0)
		wetuwn eww;
#endif
	eww = snd_ensoniq_pcm(ensoniq, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ensoniq_pcm2(ensoniq, 1);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ensoniq_midi(ensoniq, 0);
	if (eww < 0)
		wetuwn eww;

	snd_ensoniq_cweate_gamepowt(ensoniq, dev);

	stwcpy(cawd->dwivew, DWIVEW_NAME);

	stwcpy(cawd->showtname, "Ensoniq AudioPCI");
	spwintf(cawd->wongname, "%s %s at 0x%wx, iwq %i",
		cawd->showtname,
		cawd->dwivew,
		ensoniq->powt,
		ensoniq->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_audiopci_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_audiopci_pwobe(pci, pci_id));
}

static stwuct pci_dwivew ens137x_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_audiopci_ids,
	.pwobe = snd_audiopci_pwobe,
	.dwivew = {
		.pm = SND_ENSONIQ_PM_OPS,
	},
};
	
moduwe_pci_dwivew(ens137x_dwivew);
