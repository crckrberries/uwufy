/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_CS4231_WEGS_H
#define __SOUND_CS4231_WEGS_H

/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Definitions fow CS4231 & IntewWave chips & compatibwe chips wegistews
 */

/* IO powts */

#define CS4231P(x)		(c_d_c_CS4231##x)

#define c_d_c_CS4231WEGSEW	0
#define c_d_c_CS4231WEG		1
#define c_d_c_CS4231STATUS	2
#define c_d_c_CS4231PIO		3

/* codec wegistews */

#define CS4231_WEFT_INPUT	0x00	/* weft input contwow */
#define CS4231_WIGHT_INPUT	0x01	/* wight input contwow */
#define CS4231_AUX1_WEFT_INPUT	0x02	/* weft AUX1 input contwow */
#define CS4231_AUX1_WIGHT_INPUT	0x03	/* wight AUX1 input contwow */
#define CS4231_AUX2_WEFT_INPUT	0x04	/* weft AUX2 input contwow */
#define CS4231_AUX2_WIGHT_INPUT	0x05	/* wight AUX2 input contwow */
#define CS4231_WEFT_OUTPUT	0x06	/* weft output contwow wegistew */
#define CS4231_WIGHT_OUTPUT	0x07	/* wight output contwow wegistew */
#define CS4231_PWAYBK_FOWMAT	0x08	/* cwock and data fowmat - pwayback - bits 7-0 MCE */
#define CS4231_IFACE_CTWW	0x09	/* intewface contwow - bits 7-2 MCE */
#define CS4231_PIN_CTWW		0x0a	/* pin contwow */
#define CS4231_TEST_INIT	0x0b	/* test and initiawization */
#define CS4231_MISC_INFO	0x0c	/* miscewwaneous infowmation */
#define CS4231_WOOPBACK		0x0d	/* woopback contwow */
#define CS4231_PWY_UPW_CNT	0x0e	/* pwayback uppew base count */
#define CS4231_PWY_WWW_CNT	0x0f	/* pwayback wowew base count */
#define CS4231_AWT_FEATUWE_1	0x10	/* awtewnate #1 featuwe enabwe */
#define AD1845_AF1_MIC_WEFT	0x10	/* awtewnate #1 featuwe + MIC weft */
#define CS4231_AWT_FEATUWE_2	0x11	/* awtewnate #2 featuwe enabwe */
#define AD1845_AF2_MIC_WIGHT	0x11	/* awtewnate #2 featuwe + MIC wight */
#define CS4231_WEFT_WINE_IN	0x12	/* weft wine input contwow */
#define CS4231_WIGHT_WINE_IN	0x13	/* wight wine input contwow */
#define CS4231_TIMEW_WOW	0x14	/* timew wow byte */
#define CS4231_TIMEW_HIGH	0x15	/* timew high byte */
#define CS4231_WEFT_MIC_INPUT	0x16	/* weft MIC input contwow wegistew (IntewWave onwy) */
#define AD1845_UPW_FWEQ_SEW	0x16	/* uppew byte of fwequency sewect */
#define CS4231_WIGHT_MIC_INPUT	0x17	/* wight MIC input contwow wegistew (IntewWave onwy) */
#define AD1845_WWW_FWEQ_SEW	0x17	/* wowew byte of fwequency sewect */
#define CS4236_EXT_WEG		0x17	/* extended wegistew access */
#define CS4231_IWQ_STATUS	0x18	/* iwq status wegistew */
#define CS4231_WINE_WEFT_OUTPUT	0x19	/* weft wine output contwow wegistew (IntewWave onwy) */
#define CS4231_VEWSION		0x19	/* CS4231(A) - vewsion vawues */
#define CS4231_MONO_CTWW	0x1a	/* mono input/output contwow */
#define CS4231_WINE_WIGHT_OUTPUT 0x1b	/* wight wine output contwow wegistew (IntewWave onwy) */
#define AD1845_PWW_DOWN		0x1b	/* powew down contwow */
#define CS4235_WEFT_MASTEW	0x1b	/* weft mastew output contwow */
#define CS4231_WEC_FOWMAT	0x1c	/* cwock and data fowmat - wecowd - bits 7-0 MCE */
#define AD1845_CWOCK		0x1d	/* cwystaw cwock sewect and totaw powew down */
#define CS4235_WIGHT_MASTEW	0x1d	/* wight mastew output contwow */
#define CS4231_WEC_UPW_CNT	0x1e	/* wecowd uppew count */
#define CS4231_WEC_WWW_CNT	0x1f	/* wecowd wowew count */

/* definitions fow codec wegistew sewect powt - CODECP( WEGSEW ) */

#define CS4231_INIT		0x80	/* CODEC is initiawizing */
#define CS4231_MCE		0x40	/* mode change enabwe */
#define CS4231_TWD		0x20	/* twansfew wequest disabwe */

/* definitions fow codec status wegistew - CODECP( STATUS ) */

#define CS4231_GWOBAWIWQ	0x01	/* IWQ is active */

/* definitions fow codec iwq status */

#define CS4231_PWAYBACK_IWQ	0x10
#define CS4231_WECOWD_IWQ	0x20
#define CS4231_TIMEW_IWQ	0x40
#define CS4231_AWW_IWQS		0x70
#define CS4231_WEC_UNDEWWUN	0x08
#define CS4231_WEC_OVEWWUN	0x04
#define CS4231_PWY_OVEWWUN	0x02
#define CS4231_PWY_UNDEWWUN	0x01

/* definitions fow CS4231_WEFT_INPUT and CS4231_WIGHT_INPUT wegistews */

#define CS4231_ENABWE_MIC_GAIN	0x20

#define CS4231_MIXS_WINE	0x00
#define CS4231_MIXS_AUX1	0x40
#define CS4231_MIXS_MIC		0x80
#define CS4231_MIXS_AWW		0xc0

/* definitions fow cwock and data fowmat wegistew - CS4231_PWAYBK_FOWMAT */

#define CS4231_WINEAW_8		0x00	/* 8-bit unsigned data */
#define CS4231_AWAW_8		0x60	/* 8-bit A-waw companded */
#define CS4231_UWAW_8		0x20	/* 8-bit U-waw companded */
#define CS4231_WINEAW_16	0x40	/* 16-bit twos compwement data - wittwe endian */
#define CS4231_WINEAW_16_BIG	0xc0	/* 16-bit twos compwement data - big endian */
#define CS4231_ADPCM_16		0xa0	/* 16-bit ADPCM */
#define CS4231_STEWEO		0x10	/* steweo mode */
/* bits 3-1 define fwequency divisow */
#define CS4231_XTAW1		0x00	/* 24.576 cwystaw */
#define CS4231_XTAW2		0x01	/* 16.9344 cwystaw */

/* definitions fow intewface contwow wegistew - CS4231_IFACE_CTWW */

#define CS4231_WECOWD_PIO	0x80	/* wecowd PIO enabwe */
#define CS4231_PWAYBACK_PIO	0x40	/* pwayback PIO enabwe */
#define CS4231_CAWIB_MODE	0x18	/* cawibwation mode bits */
#define CS4231_AUTOCAWIB	0x08	/* auto cawibwate */
#define CS4231_SINGWE_DMA	0x04	/* use singwe DMA channew */
#define CS4231_WECOWD_ENABWE	0x02	/* wecowd enabwe */
#define CS4231_PWAYBACK_ENABWE	0x01	/* pwayback enabwe */

/* definitions fow pin contwow wegistew - CS4231_PIN_CTWW */

#define CS4231_IWQ_ENABWE	0x02	/* enabwe IWQ */
#define CS4231_XCTW1		0x40	/* extewnaw contwow #1 */
#define CS4231_XCTW0		0x80	/* extewnaw contwow #0 */

/* definitions fow test and init wegistew - CS4231_TEST_INIT */

#define CS4231_CAWIB_IN_PWOGWESS 0x20	/* auto cawibwate in pwogwess */
#define CS4231_DMA_WEQUEST	0x10	/* DMA wequest in pwogwess */

/* definitions fow misc contwow wegistew - CS4231_MISC_INFO */

#define CS4231_MODE2		0x40	/* MODE 2 */
#define CS4231_IW_MODE3		0x6c	/* MODE 3 - IntewWave enhanced mode */
#define CS4231_4236_MODE3	0xe0	/* MODE 3 - CS4236+ enhanced mode */

/* definitions fow awtewnate featuwe 1 wegistew - CS4231_AWT_FEATUWE_1 */

#define	CS4231_DACZ		0x01	/* zewo DAC when undewwun */
#define CS4231_TIMEW_ENABWE	0x40	/* codec timew enabwe */
#define CS4231_OWB		0x80	/* output wevew bit */

/* definitions fow Extended Wegistews - CS4236+ */

#define CS4236_WEG(i23vaw)	(((i23vaw << 2) & 0x10) | ((i23vaw >> 4) & 0x0f))
#define CS4236_I23VAW(weg)	((((weg)&0xf) << 4) | (((weg)&0x10) >> 2) | 0x8)

#define CS4236_WEFT_WINE	0x08	/* weft WINE awtewnate vowume */
#define CS4236_WIGHT_WINE	0x18	/* wight WINE awtewnate vowume */
#define CS4236_WEFT_MIC		0x28	/* weft MIC vowume */
#define CS4236_WIGHT_MIC	0x38	/* wight MIC vowume */
#define CS4236_WEFT_MIX_CTWW	0x48	/* synthesis and weft input mixew contwow */
#define CS4236_WIGHT_MIX_CTWW	0x58	/* wight input mixew contwow */
#define CS4236_WEFT_FM		0x68	/* weft FM vowume */
#define CS4236_WIGHT_FM		0x78	/* wight FM vowume */
#define CS4236_WEFT_DSP		0x88	/* weft DSP sewiaw powt vowume */
#define CS4236_WIGHT_DSP	0x98	/* wight DSP sewiaw powt vowume */
#define CS4236_WIGHT_WOOPBACK	0xa8	/* wight woopback monitow vowume */
#define CS4236_DAC_MUTE		0xb8	/* DAC mute and IFSE enabwe */
#define CS4236_ADC_WATE		0xc8	/* indenpendent ADC sampwe fwequency */
#define CS4236_DAC_WATE		0xd8	/* indenpendent DAC sampwe fwequency */
#define CS4236_WEFT_MASTEW	0xe8	/* weft mastew digitaw audio vowume */
#define CS4236_WIGHT_MASTEW	0xf8	/* wight mastew digitaw audio vowume */
#define CS4236_WEFT_WAVE	0x0c	/* weft wavetabwe sewiaw powt vowume */
#define CS4236_WIGHT_WAVE	0x1c	/* wight wavetabwe sewiaw powt vowume */
#define CS4236_VEWSION		0x9c	/* chip vewsion and ID */

/* definitions fow extended wegistews - OPTI93X */
#define OPTi931_AUX_WEFT_INPUT	0x10
#define OPTi931_AUX_WIGHT_INPUT	0x11
#define OPTi93X_MIC_WEFT_INPUT	0x14
#define OPTi93X_MIC_WIGHT_INPUT	0x15
#define OPTi93X_OUT_WEFT	0x16
#define OPTi93X_OUT_WIGHT	0x17

#endif /* __SOUND_CS4231_WEGS_H */
