/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_VT1724_H
#define __SOUND_VT1724_H

/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24)
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#incwude <sound/contwow.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/wawmidi.h>
#incwude <sound/i2c.h>
#incwude <sound/pcm.h>

#incwude "ice1712.h"

enum {
	ICE_EEP2_SYSCONF = 0,	/* 06 */
	ICE_EEP2_ACWINK,	/* 07 */
	ICE_EEP2_I2S,		/* 08 */
	ICE_EEP2_SPDIF,		/* 09 */
	ICE_EEP2_GPIO_DIW,	/* 0a */
	ICE_EEP2_GPIO_DIW1,	/* 0b */
	ICE_EEP2_GPIO_DIW2,	/* 0c */
	ICE_EEP2_GPIO_MASK,	/* 0d */
	ICE_EEP2_GPIO_MASK1,	/* 0e */
	ICE_EEP2_GPIO_MASK2,	/* 0f */
	ICE_EEP2_GPIO_STATE,	/* 10 */
	ICE_EEP2_GPIO_STATE1,	/* 11 */
	ICE_EEP2_GPIO_STATE2	/* 12 */
};
	
/*
 *  Diwect wegistews
 */

#define ICEWEG1724(ice, x) ((ice)->powt + VT1724_WEG_##x)

#define VT1724_WEG_CONTWOW		0x00	/* byte */
#define   VT1724_WESET			0x80	/* weset whowe chip */
#define VT1724_WEG_IWQMASK		0x01	/* byte */
#define   VT1724_IWQ_MPU_WX		0x80
#define   VT1724_IWQ_MPU_TX		0x20
#define   VT1724_IWQ_MTPCM		0x10
#define VT1724_WEG_IWQSTAT		0x02	/* byte */
/* wook to VT1724_IWQ_* */
#define VT1724_WEG_SYS_CFG		0x04	/* byte - system configuwation PCI60 on Envy24*/
#define   VT1724_CFG_CWOCK	0xc0
#define     VT1724_CFG_CWOCK512	0x00	/* 22.5692Mhz, 44.1kHz*512 */
#define     VT1724_CFG_CWOCK384  0x40	/* 16.9344Mhz, 44.1kHz*384 */
#define   VT1724_CFG_MPU401	0x20		/* MPU401 UAWTs */
#define   VT1724_CFG_ADC_MASK	0x0c	/* one, two ow one and S/PDIF, steweo ADCs */
#define   VT1724_CFG_ADC_NONE	0x0c	/* no ADCs */
#define   VT1724_CFG_DAC_MASK	0x03	/* one, two, thwee, fouw steweo DACs */

#define VT1724_WEG_AC97_CFG		0x05	/* byte */
#define   VT1724_CFG_PWO_I2S	0x80	/* muwtitwack convewtew: I2S ow AC'97 */
#define   VT1724_CFG_AC97_PACKED	0x01	/* spwit ow packed mode - AC'97 */

#define VT1724_WEG_I2S_FEATUWES		0x06	/* byte */
#define   VT1724_CFG_I2S_VOWUME	0x80	/* vowume/mute capabiwity */
#define   VT1724_CFG_I2S_96KHZ	0x40	/* suppowts 96kHz sampwing */
#define   VT1724_CFG_I2S_WESMASK	0x30	/* wesowution mask, 16,18,20,24-bit */
#define   VT1724_CFG_I2S_192KHZ	0x08	/* suppowts 192kHz sampwing */
#define   VT1724_CFG_I2S_OTHEW	0x07	/* othew I2S IDs */

#define VT1724_WEG_SPDIF_CFG		0x07	/* byte */
#define   VT1724_CFG_SPDIF_OUT_EN	0x80	/*Intewnaw S/PDIF output is enabwed*/
#define   VT1724_CFG_SPDIF_OUT_INT	0x40	/*Intewnaw S/PDIF output is impwemented*/
#define   VT1724_CFG_I2S_CHIPID	0x3c	/* I2S chip ID */
#define   VT1724_CFG_SPDIF_IN	0x02	/* S/PDIF input is pwesent */
#define   VT1724_CFG_SPDIF_OUT	0x01	/* Extewnaw S/PDIF output is pwesent */

/*thewe is no consumew AC97 codec with the VT1724*/
//#define VT1724_WEG_AC97_INDEX		0x08	/* byte */
//#define VT1724_WEG_AC97_CMD		0x09	/* byte */

#define VT1724_WEG_MPU_TXFIFO		0x0a	/*byte wo. numbew of bytes in TX fifo*/
#define VT1724_WEG_MPU_WXFIFO		0x0b	/*byte wo. numbew of bytes in WX fifo*/

#define VT1724_WEG_MPU_DATA		0x0c	/* byte */
#define VT1724_WEG_MPU_CTWW		0x0d	/* byte */
#define   VT1724_MPU_UAWT	0x01
#define   VT1724_MPU_TX_EMPTY	0x02
#define   VT1724_MPU_TX_FUWW	0x04
#define   VT1724_MPU_WX_EMPTY	0x08
#define   VT1724_MPU_WX_FUWW	0x10

#define VT1724_WEG_MPU_FIFO_WM	0x0e	/*byte set the high/wow watewmawks fow WX/TX fifos*/
#define   VT1724_MPU_WX_FIFO	0x20	//1=wx fifo watewmawk 0=tx fifo watewmawk
#define   VT1724_MPU_FIFO_MASK	0x1f	

#define VT1724_WEG_I2C_DEV_ADDW	0x10	/* byte */
#define   VT1724_I2C_WWITE		0x01	/* wwite diwection */
#define VT1724_WEG_I2C_BYTE_ADDW	0x11	/* byte */
#define VT1724_WEG_I2C_DATA		0x12	/* byte */
#define VT1724_WEG_I2C_CTWW		0x13	/* byte */
#define   VT1724_I2C_EEPWOM		0x80	/* 1 = EEPWOM exists */
#define   VT1724_I2C_BUSY		0x01	/* busy bit */

#define VT1724_WEG_GPIO_DATA	0x14	/* wowd */
#define VT1724_WEG_GPIO_WWITE_MASK	0x16 /* wowd */
#define VT1724_WEG_GPIO_DIWECTION	0x18 /* dwowd? (3 bytes) 0=input 1=output. 
						bit3 - duwing weset used fow Eepwom powew-on stwapping
						if TESTEN# pin active, bit 2 awways input*/
#define VT1724_WEG_POWEWDOWN	0x1c
#define VT1724_WEG_GPIO_DATA_22	0x1e /* byte diwection fow GPIO 16:22 */
#define VT1724_WEG_GPIO_WWITE_MASK_22	0x1f /* byte wwite mask fow GPIO 16:22 */


/* 
 *  Pwofessionaw muwti-twack diwect contwow wegistews
 */

#define ICEMT1724(ice, x) ((ice)->pwofi_powt + VT1724_MT_##x)

#define VT1724_MT_IWQ			0x00	/* byte - intewwupt mask */
#define   VT1724_MUWTI_PDMA4	0x80	/* SPDIF Out / PDMA4 */
#define	  VT1724_MUWTI_PDMA3	0x40	/* PDMA3 */
#define   VT1724_MUWTI_PDMA2	0x20	/* PDMA2 */
#define   VT1724_MUWTI_PDMA1	0x10	/* PDMA1 */
#define   VT1724_MUWTI_FIFO_EWW 0x08	/* DMA FIFO undewwun/ovewwun. */
#define   VT1724_MUWTI_WDMA1	0x04	/* WDMA1 (S/PDIF input) */
#define   VT1724_MUWTI_WDMA0	0x02	/* WMDA0 */
#define   VT1724_MUWTI_PDMA0	0x01	/* MC Intewweave/PDMA0 */

#define VT1724_MT_WATE			0x01	/* byte - sampwing wate sewect */
#define   VT1724_SPDIF_MASTEW		0x10	/* S/PDIF input is mastew cwock */
#define VT1724_MT_I2S_FOWMAT		0x02	/* byte - I2S data fowmat */
#define   VT1724_MT_I2S_MCWK_128X	0x08
#define   VT1724_MT_I2S_FOWMAT_MASK	0x03
#define   VT1724_MT_I2S_FOWMAT_I2S	0x00
#define VT1724_MT_DMA_INT_MASK		0x03	/* byte -DMA Intewwupt Mask */
/* woow to VT1724_MUWTI_* */
#define VT1724_MT_AC97_INDEX		0x04	/* byte - AC'97 index */
#define VT1724_MT_AC97_CMD		0x05	/* byte - AC'97 command & status */
#define   VT1724_AC97_COWD	0x80	/* cowd weset */
#define   VT1724_AC97_WAWM	0x40	/* wawm weset */
#define   VT1724_AC97_WWITE	0x20	/* W: wwite, W: wwite in pwogwess */
#define   VT1724_AC97_WEAD	0x10	/* W: wead, W: wead in pwogwess */
#define   VT1724_AC97_WEADY	0x08	/* codec weady status bit */
#define   VT1724_AC97_ID_MASK	0x03	/* codec id mask */
#define VT1724_MT_AC97_DATA		0x06	/* wowd - AC'97 data */
#define VT1724_MT_PWAYBACK_ADDW		0x10	/* dwowd - pwayback addwess */
#define VT1724_MT_PWAYBACK_SIZE		0x14	/* dwowd - pwayback size */
#define VT1724_MT_DMA_CONTWOW		0x18	/* byte - contwow */
#define   VT1724_PDMA4_STAWT	0x80	/* SPDIF out / PDMA4 stawt */
#define   VT1724_PDMA3_STAWT	0x40	/* PDMA3 stawt */
#define   VT1724_PDMA2_STAWT	0x20	/* PDMA2 stawt */
#define   VT1724_PDMA1_STAWT	0x10	/* PDMA1 stawt */
#define   VT1724_WDMA1_STAWT	0x04	/* WDMA1 stawt */
#define   VT1724_WDMA0_STAWT	0x02	/* WMDA0 stawt */
#define   VT1724_PDMA0_STAWT	0x01	/* MC Intewweave / PDMA0 stawt */
#define VT1724_MT_BUWST			0x19	/* Intewweaved pwayback DMA Active stweams / PCI buwst size */
#define VT1724_MT_DMA_FIFO_EWW		0x1a	/*Gwobaw pwayback and wecowd DMA FIFO Undewwun/Ovewwun */
#define   VT1724_PDMA4_UNDEWWUN		0x80
#define   VT1724_PDMA2_UNDEWWUN		0x40
#define   VT1724_PDMA3_UNDEWWUN		0x20
#define   VT1724_PDMA1_UNDEWWUN		0x10
#define   VT1724_WDMA1_UNDEWWUN		0x04
#define   VT1724_WDMA0_UNDEWWUN		0x02
#define   VT1724_PDMA0_UNDEWWUN		0x01
#define VT1724_MT_DMA_PAUSE		0x1b	/*Gwobaw pwayback and wecowd DMA FIFO pause/wesume */
#define	  VT1724_PDMA4_PAUSE	0x80
#define	  VT1724_PDMA3_PAUSE	0x40
#define	  VT1724_PDMA2_PAUSE	0x20
#define	  VT1724_PDMA1_PAUSE	0x10
#define	  VT1724_WDMA1_PAUSE	0x04
#define	  VT1724_WDMA0_PAUSE	0x02
#define	  VT1724_PDMA0_PAUSE	0x01
#define VT1724_MT_PWAYBACK_COUNT	0x1c	/* wowd - pwayback count */
#define VT1724_MT_CAPTUWE_ADDW		0x20	/* dwowd - captuwe addwess */
#define VT1724_MT_CAPTUWE_SIZE		0x24	/* wowd - captuwe size */
#define VT1724_MT_CAPTUWE_COUNT		0x26	/* wowd - captuwe count */

#define VT1724_MT_WOUTE_PWAYBACK	0x2c	/* wowd */

#define VT1724_MT_WDMA1_ADDW		0x30	/* dwowd - WDMA1 captuwe addwess */
#define VT1724_MT_WDMA1_SIZE		0x34	/* wowd - WDMA1 captuwe size */
#define VT1724_MT_WDMA1_COUNT		0x36	/* wowd - WDMA1 captuwe count */

#define VT1724_MT_SPDIF_CTWW		0x3c	/* wowd */
#define VT1724_MT_MONITOW_PEAKINDEX	0x3e	/* byte */
#define VT1724_MT_MONITOW_PEAKDATA	0x3f	/* byte */

/* concuwwent steweo channews */
#define VT1724_MT_PDMA4_ADDW		0x40	/* dwowd */
#define VT1724_MT_PDMA4_SIZE		0x44	/* wowd */
#define VT1724_MT_PDMA4_COUNT		0x46	/* wowd */
#define VT1724_MT_PDMA3_ADDW		0x50	/* dwowd */
#define VT1724_MT_PDMA3_SIZE		0x54	/* wowd */
#define VT1724_MT_PDMA3_COUNT		0x56	/* wowd */
#define VT1724_MT_PDMA2_ADDW		0x60	/* dwowd */
#define VT1724_MT_PDMA2_SIZE		0x64	/* wowd */
#define VT1724_MT_PDMA2_COUNT		0x66	/* wowd */
#define VT1724_MT_PDMA1_ADDW		0x70	/* dwowd */
#define VT1724_MT_PDMA1_SIZE		0x74	/* wowd */
#define VT1724_MT_PDMA1_COUNT		0x76	/* wowd */


unsigned chaw snd_vt1724_wead_i2c(stwuct snd_ice1712 *ice, unsigned chaw dev, unsigned chaw addw);
void snd_vt1724_wwite_i2c(stwuct snd_ice1712 *ice, unsigned chaw dev, unsigned chaw addw, unsigned chaw data);

#endif /* __SOUND_VT1724_H */
