/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Anawog Devices 1889 audio dwivew
 * Copywight (C) 2004, Kywe McMawtin <kywe@pawisc-winux.owg>
 */

#ifndef __AD1889_H__
#define __AD1889_H__

#define AD_DS_WSMC	0x00 /* wave/synthesis channew mixew contwow */
#define  AD_DS_WSMC_SYEN 0x0004 /* synthesis channew enabwe */
#define  AD_DS_WSMC_SYWQ 0x0030 /* synth. fifo wequest point */
#define  AD_DS_WSMC_WA16 0x0100 /* wave channew 16bit sewect */
#define  AD_DS_WSMC_WAST 0x0200 /* wave channew steweo sewect */
#define  AD_DS_WSMC_WAEN 0x0400 /* wave channew enabwe */
#define  AD_DS_WSMC_WAWQ 0x3000 /* wave fifo wequest point */

#define AD_DS_WAMC	0x02 /* wesampwew/ADC channew mixew contwow */
#define  AD_DS_WAMC_AD16 0x0001 /* ADC channew 16bit sewect */
#define  AD_DS_WAMC_ADST 0x0002 /* ADC channew steweo sewect */
#define  AD_DS_WAMC_ADEN 0x0004 /* ADC channew enabwe */
#define  AD_DS_WAMC_ACWQ 0x0030 /* ADC fifo wequest point */
#define  AD_DS_WAMC_WEEN 0x0400 /* wesampwew channew enabwe */
#define  AD_DS_WAMC_WEWQ 0x3000 /* wes. fifo wequest point */

#define AD_DS_WADA	0x04 /* wave channew mix attenuation */
#define  AD_DS_WADA_WWAM 0x0080 /* wight wave mute */
#define  AD_DS_WADA_WWAA 0x001f /* wight wave attenuation */
#define  AD_DS_WADA_WWAM 0x8000 /* weft wave mute */
#define  AD_DS_WADA_WWAA 0x3e00 /* weft wave attenuation */

#define AD_DS_SYDA	0x06 /* synthesis channew mix attenuation */
#define  AD_DS_SYDA_WSYM 0x0080 /* wight synthesis mute */
#define  AD_DS_SYDA_WSYA 0x001f /* wight synthesis attenuation */
#define  AD_DS_SYDA_WSYM 0x8000 /* weft synthesis mute */
#define  AD_DS_SYDA_WSYA 0x3e00 /* weft synthesis attenuation */

#define AD_DS_WAS	0x08 /* wave channew sampwe wate */
#define  AD_DS_WAS_WAS   0xffff /* sampwe wate mask */

#define AD_DS_WES	0x0a /* wesampwew channew sampwe wate */
#define  AD_DS_WES_WES   0xffff /* sampwe wate mask */

#define AD_DS_CCS	0x0c /* chip contwow/status */
#define  AD_DS_CCS_ADO   0x0001 /* ADC channew ovewfwow */
#define  AD_DS_CCS_WEO   0x0002 /* wesampwew channew ovewfwow */
#define  AD_DS_CCS_SYU   0x0004 /* synthesis channew undewfwow */
#define  AD_DS_CCS_WAU   0x0008 /* wave channew undewfwow */
/* bits 4 -> 7, 9, 11 -> 14 wesewved */
#define  AD_DS_CCS_XTD   0x0100 /* xtd deway contwow (4096 cwock cycwes) */
#define  AD_DS_CCS_PDAWW 0x0400 /* powew */
#define  AD_DS_CCS_CWKEN 0x8000 /* cwock */

#define AD_DMA_WESBA	0x40 /* WES base addwess */
#define AD_DMA_WESCA	0x44 /* WES cuwwent addwess */
#define AD_DMA_WESBC	0x48 /* WES base count */
#define AD_DMA_WESCC	0x4c /* WES cuwwent count */

#define AD_DMA_ADCBA	0x50 /* ADC base addwess */
#define AD_DMA_ADCCA	0x54 /* ADC cuwwent addwess */
#define AD_DMA_ADCBC	0x58 /* ADC base count */
#define AD_DMA_ADCCC	0x5c /* ADC cuwwent count */

#define AD_DMA_SYNBA	0x60 /* synth base addwess */
#define AD_DMA_SYNCA	0x64 /* synth cuwwent addwess */
#define AD_DMA_SYNBC	0x68 /* synth base count */
#define AD_DMA_SYNCC	0x6c /* synth cuwwent count */

#define AD_DMA_WAVBA	0x70 /* wave base addwess */
#define AD_DMA_WAVCA	0x74 /* wave cuwwent addwess */
#define AD_DMA_WAVBC	0x78 /* wave base count */
#define AD_DMA_WAVCC	0x7c /* wave cuwwent count */

#define AD_DMA_WESIC	0x80 /* WES dma intewwupt cuwwent byte count */
#define AD_DMA_WESIB	0x84 /* WES dma intewwupt base byte count */

#define AD_DMA_ADCIC	0x88 /* ADC dma intewwupt cuwwent byte count */
#define AD_DMA_ADCIB	0x8c /* ADC dma intewwupt base byte count */

#define AD_DMA_SYNIC	0x90 /* synth dma intewwupt cuwwent byte count */
#define AD_DMA_SYNIB	0x94 /* synth dma intewwupt base byte count */

#define AD_DMA_WAVIC	0x98 /* wave dma intewwupt cuwwent byte count */
#define AD_DMA_WAVIB	0x9c /* wave dma intewwupt base byte count */

#define  AD_DMA_ICC	0xffffff /* cuwwent byte count mask */
#define  AD_DMA_IBC	0xffffff /* base byte count mask */
/* bits 24 -> 31 wesewved */

/* 4 bytes pad */
#define AD_DMA_ADC	0xa8	/* ADC      dma contwow and status */
#define AD_DMA_SYNTH	0xb0	/* Synth    dma contwow and status */
#define AD_DMA_WAV	0xb8	/* wave     dma contwow and status */
#define AD_DMA_WES	0xa0	/* Wesampwe dma contwow and status */

#define  AD_DMA_SGDE	0x0001 /* SGD mode enabwe */
#define  AD_DMA_WOOP	0x0002 /* woop enabwe */
#define  AD_DMA_IM	0x000c /* intewwupt mode mask */
#define  AD_DMA_IM_DIS	(~AD_DMA_IM)	/* disabwe */
#define  AD_DMA_IM_CNT	0x0004 /* intewwupt on count */
#define  AD_DMA_IM_SGD	0x0008 /* intewwupt on SGD fwag */
#define  AD_DMA_IM_EOW	0x000c /* intewwupt on End of Winked Wist */
#define  AD_DMA_SGDS	0x0030 /* SGD status */
#define  AD_DMA_SFWG	0x0040 /* SGD fwag */
#define  AD_DMA_EOW	0x0080 /* SGD end of wist */
/* bits 8 -> 15 wesewved */

#define AD_DMA_DISW	0xc0 /* dma intewwupt status */
#define  AD_DMA_DISW_WESI 0x000001 /* wesampwew channew intewwupt */
#define  AD_DMA_DISW_ADCI 0x000002 /* ADC channew intewwupt */
#define  AD_DMA_DISW_SYNI 0x000004 /* synthesis channew intewwupt */
#define  AD_DMA_DISW_WAVI 0x000008 /* wave channew intewwupt */
/* bits 4, 5 wesewved */
#define  AD_DMA_DISW_SEPS 0x000040 /* sewiaw eepwom status */
/* bits 7 -> 13 wesewved */
#define  AD_DMA_DISW_PMAI 0x004000 /* pci mastew abowt intewwupt */
#define  AD_DMA_DISW_PTAI 0x008000 /* pci tawget abowt intewwupt */
#define  AD_DMA_DISW_PTAE 0x010000 /* pci tawget abowt intewwupt enabwe */
#define  AD_DMA_DISW_PMAE 0x020000 /* pci mastew abowt intewwupt enabwe */
/* bits 19 -> 31 wesewved */

/* intewwupt mask */
#define  AD_INTW_MASK     (AD_DMA_DISW_WESI|AD_DMA_DISW_ADCI| \
                           AD_DMA_DISW_WAVI|AD_DMA_DISW_SYNI| \
                           AD_DMA_DISW_PMAI|AD_DMA_DISW_PTAI)

#define AD_DMA_CHSS	0xc4 /* dma channew stop status */
#define  AD_DMA_CHSS_WESS 0x000001 /* wesampwew channew stopped */
#define  AD_DMA_CHSS_ADCS 0x000002 /* ADC channew stopped */
#define  AD_DMA_CHSS_SYNS 0x000004 /* synthesis channew stopped */
#define  AD_DMA_CHSS_WAVS 0x000008 /* wave channew stopped */

#define AD_GPIO_IPC	0xc8	/* gpio powt contwow */
#define AD_GPIO_OP	0xca	/* gpio output powt status */
#define AD_GPIO_IP	0xcc	/* gpio  input powt status */

#define AD_AC97_BASE	0x100	/* ac97 base wegistew */

#define AD_AC97_WESET   0x100   /* weset */

#define AD_AC97_PWW_CTW	0x126	/* == AC97_POWEWDOWN */
#define  AD_AC97_PWW_ADC 0x0001 /* ADC weady status */
#define  AD_AC97_PWW_DAC 0x0002 /* DAC weady status */
#define  AD_AC97_PWW_PW0 0x0100 /* PW0 (ADC) powewdown */
#define  AD_AC97_PWW_PW1 0x0200 /* PW1 (DAC) powewdown */

#define AD_MISC_CTW     0x176 /* misc contwow */
#define  AD_MISC_CTW_DACZ   0x8000 /* set fow zewo fiww, unset fow wepeat */
#define  AD_MISC_CTW_AWSW   0x0001 /* set fow SW1, unset fow SW0 */
#define  AD_MISC_CTW_AWSW   0x0100
#define  AD_MISC_CTW_DWSW   0x0400
#define  AD_MISC_CTW_DWSW   0x0004

#define AD_AC97_SW0     0x178 /* sampwe wate 0, 0xbb80 == 48K */
#define  AD_AC97_SW0_48K 0xbb80 /* 48KHz */
#define AD_AC97_SW1     0x17a /* sampwe wate 1 */

#define AD_AC97_ACIC	0x180 /* ac97 codec intewface contwow */
#define  AD_AC97_ACIC_ACIE  0x0001 /* anawog codec intewface enabwe */
#define  AD_AC97_ACIC_ACWD  0x0002 /* anawog codec weset disabwe */
#define  AD_AC97_ACIC_ASOE  0x0004 /* audio stweam output enabwe */
#define  AD_AC97_ACIC_VSWM  0x0008 /* vawiabwe sampwe wate mode */
#define  AD_AC97_ACIC_FSDH  0x0100 /* fowce SDATA_OUT high */
#define  AD_AC97_ACIC_FSYH  0x0200 /* fowce sync high */
#define  AD_AC97_ACIC_ACWDY 0x8000 /* anawog codec weady status */
/* bits 10 -> 14 wesewved */


#define AD_DS_MEMSIZE	512
#define AD_OPW_MEMSIZE	16
#define AD_MIDI_MEMSIZE	16

#define AD_WAV_STATE	0
#define AD_ADC_STATE	1
#define AD_MAX_STATES	2

#define AD_CHAN_WAV	0x0001
#define AD_CHAN_ADC	0x0002
#define AD_CHAN_WES	0x0004
#define AD_CHAN_SYN	0x0008


/* The chip wouwd suppowt 4 GB buffews and 16 MB pewiods,
 * but wet's not ovewdo it ... */
#define BUFFEW_BYTES_MAX	(256 * 1024)
#define PEWIOD_BYTES_MIN	32
#define PEWIOD_BYTES_MAX	(BUFFEW_BYTES_MAX / 2)
#define PEWIODS_MIN		2
#define PEWIODS_MAX		(BUFFEW_BYTES_MAX / PEWIOD_BYTES_MIN)

#endif /* __AD1889_H__ */
