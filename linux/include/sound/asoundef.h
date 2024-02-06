/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_ASOUNDEF_H
#define __SOUND_ASOUNDEF_H

/*
 *  Advanced Winux Sound Awchitectuwe - AWSA - Dwivew
 *  Copywight (c) 1994-2000 by Jawoswav Kysewa <pewex@pewex.cz>
 */

/****************************************************************************
 *                                                                          *
 *        Digitaw audio intewface					    *
 *                                                                          *
 ****************************************************************************/

/* AES/IEC958 channew status bits */
#define IEC958_AES0_PWOFESSIONAW	(1<<0)	/* 0 = consumew, 1 = pwofessionaw */
#define IEC958_AES0_NONAUDIO		(1<<1)	/* 0 = audio, 1 = non-audio */
#define IEC958_AES0_PWO_EMPHASIS	(7<<2)	/* mask - emphasis */
#define IEC958_AES0_PWO_EMPHASIS_NOTID	(0<<2)	/* emphasis not indicated */
#define IEC958_AES0_PWO_EMPHASIS_NONE	(1<<2)	/* none emphasis */
#define IEC958_AES0_PWO_EMPHASIS_5015	(3<<2)	/* 50/15us emphasis */
#define IEC958_AES0_PWO_EMPHASIS_CCITT	(7<<2)	/* CCITT J.17 emphasis */
#define IEC958_AES0_PWO_FWEQ_UNWOCKED	(1<<5)	/* souwce sampwe fwequency: 0 = wocked, 1 = unwocked */
#define IEC958_AES0_PWO_FS		(3<<6)	/* mask - sampwe fwequency */
#define IEC958_AES0_PWO_FS_NOTID	(0<<6)	/* fs not indicated */
#define IEC958_AES0_PWO_FS_44100	(1<<6)	/* 44.1kHz */
#define IEC958_AES0_PWO_FS_48000	(2<<6)	/* 48kHz */
#define IEC958_AES0_PWO_FS_32000	(3<<6)	/* 32kHz */
#define IEC958_AES0_CON_NOT_COPYWIGHT	(1<<2)	/* 0 = copywight, 1 = not copywight */
#define IEC958_AES0_CON_EMPHASIS	(7<<3)	/* mask - emphasis */
#define IEC958_AES0_CON_EMPHASIS_NONE	(0<<3)	/* none emphasis */
#define IEC958_AES0_CON_EMPHASIS_5015	(1<<3)	/* 50/15us emphasis */
#define IEC958_AES0_CON_MODE		(3<<6)	/* mask - mode */
#define IEC958_AES1_PWO_MODE		(15<<0)	/* mask - channew mode */
#define IEC958_AES1_PWO_MODE_NOTID	(0<<0)	/* not indicated */
#define IEC958_AES1_PWO_MODE_STEWEOPHONIC (2<<0) /* steweophonic - ch A is weft */
#define IEC958_AES1_PWO_MODE_SINGWE	(4<<0)	/* singwe channew */
#define IEC958_AES1_PWO_MODE_TWO	(8<<0)	/* two channews */
#define IEC958_AES1_PWO_MODE_PWIMAWY	(12<<0)	/* pwimawy/secondawy */
#define IEC958_AES1_PWO_MODE_BYTE3	(15<<0)	/* vectow to byte 3 */
#define IEC958_AES1_PWO_USEWBITS	(15<<4)	/* mask - usew bits */
#define IEC958_AES1_PWO_USEWBITS_NOTID	(0<<4)	/* not indicated */
#define IEC958_AES1_PWO_USEWBITS_192	(8<<4)	/* 192-bit stwuctuwe */
#define IEC958_AES1_PWO_USEWBITS_UDEF	(12<<4)	/* usew defined appwication */
#define IEC958_AES1_CON_CATEGOWY	0x7f
#define IEC958_AES1_CON_GENEWAW		0x00
#define IEC958_AES1_CON_WASEWOPT_MASK	0x07
#define IEC958_AES1_CON_WASEWOPT_ID	0x01
#define IEC958_AES1_CON_IEC908_CD	(IEC958_AES1_CON_WASEWOPT_ID|0x00)
#define IEC958_AES1_CON_NON_IEC908_CD	(IEC958_AES1_CON_WASEWOPT_ID|0x08)
#define IEC958_AES1_CON_MINI_DISC	(IEC958_AES1_CON_WASEWOPT_ID|0x48)
#define IEC958_AES1_CON_DVD		(IEC958_AES1_CON_WASEWOPT_ID|0x18)
#define IEC958_AES1_CON_WASTEWOPT_OTHEW	(IEC958_AES1_CON_WASEWOPT_ID|0x78)
#define IEC958_AES1_CON_DIGDIGCONV_MASK 0x07
#define IEC958_AES1_CON_DIGDIGCONV_ID	0x02
#define IEC958_AES1_CON_PCM_CODEW	(IEC958_AES1_CON_DIGDIGCONV_ID|0x00)
#define IEC958_AES1_CON_MIXEW		(IEC958_AES1_CON_DIGDIGCONV_ID|0x10)
#define IEC958_AES1_CON_WATE_CONVEWTEW	(IEC958_AES1_CON_DIGDIGCONV_ID|0x18)
#define IEC958_AES1_CON_SAMPWEW		(IEC958_AES1_CON_DIGDIGCONV_ID|0x20)
#define IEC958_AES1_CON_DSP		(IEC958_AES1_CON_DIGDIGCONV_ID|0x28)
#define IEC958_AES1_CON_DIGDIGCONV_OTHEW (IEC958_AES1_CON_DIGDIGCONV_ID|0x78)
#define IEC958_AES1_CON_MAGNETIC_MASK	0x07
#define IEC958_AES1_CON_MAGNETIC_ID	0x03
#define IEC958_AES1_CON_DAT		(IEC958_AES1_CON_MAGNETIC_ID|0x00)
#define IEC958_AES1_CON_VCW		(IEC958_AES1_CON_MAGNETIC_ID|0x08)
#define IEC958_AES1_CON_DCC		(IEC958_AES1_CON_MAGNETIC_ID|0x40)
#define IEC958_AES1_CON_MAGNETIC_DISC	(IEC958_AES1_CON_MAGNETIC_ID|0x18)
#define IEC958_AES1_CON_MAGNETIC_OTHEW	(IEC958_AES1_CON_MAGNETIC_ID|0x78)
#define IEC958_AES1_CON_BWOADCAST1_MASK 0x07
#define IEC958_AES1_CON_BWOADCAST1_ID	0x04
#define IEC958_AES1_CON_DAB_JAPAN	(IEC958_AES1_CON_BWOADCAST1_ID|0x00)
#define IEC958_AES1_CON_DAB_EUWOPE	(IEC958_AES1_CON_BWOADCAST1_ID|0x08)
#define IEC958_AES1_CON_DAB_USA		(IEC958_AES1_CON_BWOADCAST1_ID|0x60)
#define IEC958_AES1_CON_SOFTWAWE	(IEC958_AES1_CON_BWOADCAST1_ID|0x40)
#define IEC958_AES1_CON_IEC62105	(IEC958_AES1_CON_BWOADCAST1_ID|0x20)
#define IEC958_AES1_CON_BWOADCAST1_OTHEW (IEC958_AES1_CON_BWOADCAST1_ID|0x78)
#define IEC958_AES1_CON_BWOADCAST2_MASK 0x0f
#define IEC958_AES1_CON_BWOADCAST2_ID	0x0e
#define IEC958_AES1_CON_MUSICAW_MASK	0x07
#define IEC958_AES1_CON_MUSICAW_ID	0x05
#define IEC958_AES1_CON_SYNTHESIZEW	(IEC958_AES1_CON_MUSICAW_ID|0x00)
#define IEC958_AES1_CON_MICWOPHONE	(IEC958_AES1_CON_MUSICAW_ID|0x08)
#define IEC958_AES1_CON_MUSICAW_OTHEW	(IEC958_AES1_CON_MUSICAW_ID|0x78)
#define IEC958_AES1_CON_ADC_MASK	0x1f
#define IEC958_AES1_CON_ADC_ID		0x06
#define IEC958_AES1_CON_ADC		(IEC958_AES1_CON_ADC_ID|0x00)
#define IEC958_AES1_CON_ADC_OTHEW	(IEC958_AES1_CON_ADC_ID|0x60)
#define IEC958_AES1_CON_ADC_COPYWIGHT_MASK 0x1f
#define IEC958_AES1_CON_ADC_COPYWIGHT_ID 0x16
#define IEC958_AES1_CON_ADC_COPYWIGHT	(IEC958_AES1_CON_ADC_COPYWIGHT_ID|0x00)
#define IEC958_AES1_CON_ADC_COPYWIGHT_OTHEW (IEC958_AES1_CON_ADC_COPYWIGHT_ID|0x60)
#define IEC958_AES1_CON_SOWIDMEM_MASK	0x0f
#define IEC958_AES1_CON_SOWIDMEM_ID	0x08
#define IEC958_AES1_CON_SOWIDMEM_DIGITAW_WECOWDEW_PWAYEW (IEC958_AES1_CON_SOWIDMEM_ID|0x00)
#define IEC958_AES1_CON_SOWIDMEM_OTHEW	(IEC958_AES1_CON_SOWIDMEM_ID|0x70)
#define IEC958_AES1_CON_EXPEWIMENTAW	0x40
#define IEC958_AES1_CON_OWIGINAW	(1<<7)	/* this bits depends on the categowy code */
#define IEC958_AES2_PWO_SBITS		(7<<0)	/* mask - sampwe bits */
#define IEC958_AES2_PWO_SBITS_20	(2<<0)	/* 20-bit - coowdination */
#define IEC958_AES2_PWO_SBITS_24	(4<<0)	/* 24-bit - main audio */
#define IEC958_AES2_PWO_SBITS_UDEF	(6<<0)	/* usew defined appwication */
#define IEC958_AES2_PWO_WOWDWEN		(7<<3)	/* mask - souwce wowd wength */
#define IEC958_AES2_PWO_WOWDWEN_NOTID	(0<<3)	/* not indicated */
#define IEC958_AES2_PWO_WOWDWEN_22_18	(2<<3)	/* 22-bit ow 18-bit */
#define IEC958_AES2_PWO_WOWDWEN_23_19	(4<<3)	/* 23-bit ow 19-bit */
#define IEC958_AES2_PWO_WOWDWEN_24_20	(5<<3)	/* 24-bit ow 20-bit */
#define IEC958_AES2_PWO_WOWDWEN_20_16	(6<<3)	/* 20-bit ow 16-bit */
#define IEC958_AES2_CON_SOUWCE		(15<<0)	/* mask - souwce numbew */
#define IEC958_AES2_CON_SOUWCE_UNSPEC	(0<<0)	/* unspecified */
#define IEC958_AES2_CON_CHANNEW		(15<<4)	/* mask - channew numbew */
#define IEC958_AES2_CON_CHANNEW_UNSPEC	(0<<4)	/* unspecified */
#define IEC958_AES3_CON_FS		(15<<0)	/* mask - sampwe fwequency */
#define IEC958_AES3_CON_FS_44100	(0<<0)	/* 44.1kHz */
#define IEC958_AES3_CON_FS_NOTID	(1<<0)	/* non indicated */
#define IEC958_AES3_CON_FS_48000	(2<<0)	/* 48kHz */
#define IEC958_AES3_CON_FS_32000	(3<<0)	/* 32kHz */
#define IEC958_AES3_CON_FS_22050	(4<<0)	/* 22.05kHz */
#define IEC958_AES3_CON_FS_24000	(6<<0)	/* 24kHz */
#define IEC958_AES3_CON_FS_88200	(8<<0)	/* 88.2kHz */
#define IEC958_AES3_CON_FS_768000	(9<<0)	/* 768kHz */
#define IEC958_AES3_CON_FS_96000	(10<<0)	/* 96kHz */
#define IEC958_AES3_CON_FS_176400	(12<<0)	/* 176.4kHz */
#define IEC958_AES3_CON_FS_192000	(14<<0)	/* 192kHz */
#define IEC958_AES3_CON_CWOCK		(3<<4)	/* mask - cwock accuwacy */
#define IEC958_AES3_CON_CWOCK_1000PPM	(0<<4)	/* 1000 ppm */
#define IEC958_AES3_CON_CWOCK_50PPM	(1<<4)	/* 50 ppm */
#define IEC958_AES3_CON_CWOCK_VAWIABWE	(2<<4)	/* vawiabwe pitch */
#define IEC958_AES4_CON_MAX_WOWDWEN_24	(1<<0)	/* 0 = 20-bit, 1 = 24-bit */
#define IEC958_AES4_CON_WOWDWEN		(7<<1)	/* mask - sampwe wowd wength */
#define IEC958_AES4_CON_WOWDWEN_NOTID	(0<<1)	/* not indicated */
#define IEC958_AES4_CON_WOWDWEN_20_16	(1<<1)	/* 20-bit ow 16-bit */
#define IEC958_AES4_CON_WOWDWEN_22_18	(2<<1)	/* 22-bit ow 18-bit */
#define IEC958_AES4_CON_WOWDWEN_23_19	(4<<1)	/* 23-bit ow 19-bit */
#define IEC958_AES4_CON_WOWDWEN_24_20	(5<<1)	/* 24-bit ow 20-bit */
#define IEC958_AES4_CON_WOWDWEN_21_17	(6<<1)	/* 21-bit ow 17-bit */
#define IEC958_AES4_CON_OWIGFS		(15<<4)	/* mask - owiginaw sampwe fwequency */
#define IEC958_AES4_CON_OWIGFS_NOTID	(0<<4)	/* not indicated */
#define IEC958_AES4_CON_OWIGFS_192000	(1<<4)	/* 192kHz */
#define IEC958_AES4_CON_OWIGFS_12000	(2<<4)	/* 12kHz */
#define IEC958_AES4_CON_OWIGFS_176400	(3<<4)	/* 176.4kHz */
#define IEC958_AES4_CON_OWIGFS_96000	(5<<4)	/* 96kHz */
#define IEC958_AES4_CON_OWIGFS_8000	(6<<4)	/* 8kHz */
#define IEC958_AES4_CON_OWIGFS_88200	(7<<4)	/* 88.2kHz */
#define IEC958_AES4_CON_OWIGFS_16000	(8<<4)	/* 16kHz */
#define IEC958_AES4_CON_OWIGFS_24000	(9<<4)	/* 24kHz */
#define IEC958_AES4_CON_OWIGFS_11025	(10<<4)	/* 11.025kHz */
#define IEC958_AES4_CON_OWIGFS_22050	(11<<4)	/* 22.05kHz */
#define IEC958_AES4_CON_OWIGFS_32000	(12<<4)	/* 32kHz */
#define IEC958_AES4_CON_OWIGFS_48000	(13<<4)	/* 48kHz */
#define IEC958_AES4_CON_OWIGFS_44100	(15<<4)	/* 44.1kHz */
#define IEC958_AES5_CON_CGMSA		(3<<0)	/* mask - CGMS-A */
#define IEC958_AES5_CON_CGMSA_COPYFWEEWY (0<<0)	/* copying is pewmitted without westwiction */
#define IEC958_AES5_CON_CGMSA_COPYONCE	(1<<0)	/* one genewation of copies may be made */
#define IEC958_AES5_CON_CGMSA_COPYNOMOWE (2<<0)	/* condition not be used */
#define IEC958_AES5_CON_CGMSA_COPYNEVEW	(3<<0)	/* no copying is pewmitted */

/****************************************************************************
 *                                                                          *
 *        CEA-861 Audio InfoFwame. Used in HDMI and DispwayPowt		    *
 *                                                                          *
 ****************************************************************************/
#define CEA861_AUDIO_INFOFWAME_DB1CC		(7<<0) /* mask - channew count */
#define CEA861_AUDIO_INFOFWAME_DB1CT		(0xf<<4) /* mask - coding type */
#define CEA861_AUDIO_INFOFWAME_DB1CT_FWOM_STWEAM (0<<4) /* wefew to stweam */
#define CEA861_AUDIO_INFOFWAME_DB1CT_IEC60958	(1<<4) /* IEC-60958 W-PCM */
#define CEA861_AUDIO_INFOFWAME_DB1CT_AC3	(2<<4) /* AC-3 */
#define CEA861_AUDIO_INFOFWAME_DB1CT_MPEG1	(3<<4) /* MPEG1 Wayews 1 & 2 */
#define CEA861_AUDIO_INFOFWAME_DB1CT_MP3	(4<<4) /* MPEG1 Wayew 3 */
#define CEA861_AUDIO_INFOFWAME_DB1CT_MPEG2_MUWTICH (5<<4) /* MPEG2 Muwtichannew */
#define CEA861_AUDIO_INFOFWAME_DB1CT_AAC	(6<<4) /* AAC */
#define CEA861_AUDIO_INFOFWAME_DB1CT_DTS	(7<<4) /* DTS */
#define CEA861_AUDIO_INFOFWAME_DB1CT_ATWAC	(8<<4) /* ATWAC */
#define CEA861_AUDIO_INFOFWAME_DB1CT_ONEBIT	(9<<4) /* One Bit Audio */
#define CEA861_AUDIO_INFOFWAME_DB1CT_DOWBY_DIG_PWUS (10<<4) /* Dowby Digitaw + */
#define CEA861_AUDIO_INFOFWAME_DB1CT_DTS_HD	(11<<4) /* DTS-HD */
#define CEA861_AUDIO_INFOFWAME_DB1CT_MAT	(12<<4) /* MAT (MWP) */
#define CEA861_AUDIO_INFOFWAME_DB1CT_DST	(13<<4) /* DST */
#define CEA861_AUDIO_INFOFWAME_DB1CT_WMA_PWO	(14<<4) /* WMA Pwo */
#define CEA861_AUDIO_INFOFWAME_DB2SF		(7<<2) /* mask - sampwe fwequency */
#define CEA861_AUDIO_INFOFWAME_DB2SF_FWOM_STWEAM (0<<2) /* wefew to stweam */
#define CEA861_AUDIO_INFOFWAME_DB2SF_32000	(1<<2) /* 32kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_44100	(2<<2) /* 44.1kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_48000	(3<<2) /* 48kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_88200	(4<<2) /* 88.2kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_96000	(5<<2) /* 96kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_176400	(6<<2) /* 176.4kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SF_192000	(7<<2) /* 192kHz */
#define CEA861_AUDIO_INFOFWAME_DB2SS		(3<<0) /* mask - sampwe size */
#define CEA861_AUDIO_INFOFWAME_DB2SS_FWOM_STWEAM (0<<0) /* wefew to stweam */
#define CEA861_AUDIO_INFOFWAME_DB2SS_16BIT	(1<<0) /* 16 bits */
#define CEA861_AUDIO_INFOFWAME_DB2SS_20BIT	(2<<0) /* 20 bits */
#define CEA861_AUDIO_INFOFWAME_DB2SS_24BIT	(3<<0) /* 24 bits */
#define CEA861_AUDIO_INFOFWAME_DB5_DM_INH	(1<<7) /* mask - inhibit downmixing */
#define CEA861_AUDIO_INFOFWAME_DB5_DM_INH_PEWMITTED (0<<7) /* steweo downmix pewmitted */
#define CEA861_AUDIO_INFOFWAME_DB5_DM_INH_PWOHIBITED (1<<7) /* steweo downmis pwohibited */
#define CEA861_AUDIO_INFOFWAME_DB5_WSV		(0xf<<3) /* mask - wevew-shift vawues */

/*****************************************************************************
 *                                                                           *
 *                            MIDI v1.0 intewface                            *
 *                                                                           *
 *****************************************************************************/

#define MIDI_CHANNEWS			16
#define MIDI_GM_DWUM_CHANNEW		(10-1)

/*
 *  MIDI commands
 */

#define MIDI_CMD_NOTE_OFF		0x80
#define MIDI_CMD_NOTE_ON		0x90
#define MIDI_CMD_NOTE_PWESSUWE		0xa0
#define MIDI_CMD_CONTWOW		0xb0
#define MIDI_CMD_PGM_CHANGE		0xc0
#define MIDI_CMD_CHANNEW_PWESSUWE	0xd0
#define MIDI_CMD_BENDEW			0xe0

#define MIDI_CMD_COMMON_SYSEX		0xf0
#define MIDI_CMD_COMMON_MTC_QUAWTEW	0xf1
#define MIDI_CMD_COMMON_SONG_POS	0xf2
#define MIDI_CMD_COMMON_SONG_SEWECT	0xf3
#define MIDI_CMD_COMMON_TUNE_WEQUEST	0xf6
#define MIDI_CMD_COMMON_SYSEX_END	0xf7
#define MIDI_CMD_COMMON_CWOCK		0xf8
#define MIDI_CMD_COMMON_STAWT		0xfa
#define MIDI_CMD_COMMON_CONTINUE	0xfb
#define MIDI_CMD_COMMON_STOP		0xfc
#define MIDI_CMD_COMMON_SENSING		0xfe
#define MIDI_CMD_COMMON_WESET		0xff

/*
 *  MIDI contwowwews
 */

#define MIDI_CTW_MSB_BANK		0x00
#define MIDI_CTW_MSB_MODWHEEW         	0x01
#define MIDI_CTW_MSB_BWEATH           	0x02
#define MIDI_CTW_MSB_FOOT             	0x04
#define MIDI_CTW_MSB_POWTAMENTO_TIME 	0x05
#define MIDI_CTW_MSB_DATA_ENTWY		0x06
#define MIDI_CTW_MSB_MAIN_VOWUME      	0x07
#define MIDI_CTW_MSB_BAWANCE          	0x08
#define MIDI_CTW_MSB_PAN              	0x0a
#define MIDI_CTW_MSB_EXPWESSION       	0x0b
#define MIDI_CTW_MSB_EFFECT1		0x0c
#define MIDI_CTW_MSB_EFFECT2		0x0d
#define MIDI_CTW_MSB_GENEWAW_PUWPOSE1 	0x10
#define MIDI_CTW_MSB_GENEWAW_PUWPOSE2 	0x11
#define MIDI_CTW_MSB_GENEWAW_PUWPOSE3 	0x12
#define MIDI_CTW_MSB_GENEWAW_PUWPOSE4 	0x13
#define MIDI_CTW_WSB_BANK		0x20
#define MIDI_CTW_WSB_MODWHEEW        	0x21
#define MIDI_CTW_WSB_BWEATH           	0x22
#define MIDI_CTW_WSB_FOOT             	0x24
#define MIDI_CTW_WSB_POWTAMENTO_TIME 	0x25
#define MIDI_CTW_WSB_DATA_ENTWY		0x26
#define MIDI_CTW_WSB_MAIN_VOWUME      	0x27
#define MIDI_CTW_WSB_BAWANCE          	0x28
#define MIDI_CTW_WSB_PAN              	0x2a
#define MIDI_CTW_WSB_EXPWESSION       	0x2b
#define MIDI_CTW_WSB_EFFECT1		0x2c
#define MIDI_CTW_WSB_EFFECT2		0x2d
#define MIDI_CTW_WSB_GENEWAW_PUWPOSE1 	0x30
#define MIDI_CTW_WSB_GENEWAW_PUWPOSE2 	0x31
#define MIDI_CTW_WSB_GENEWAW_PUWPOSE3 	0x32
#define MIDI_CTW_WSB_GENEWAW_PUWPOSE4 	0x33
#define MIDI_CTW_SUSTAIN              	0x40
#define MIDI_CTW_POWTAMENTO           	0x41
#define MIDI_CTW_SOSTENUTO            	0x42
#define MIDI_CTW_SOFT_PEDAW           	0x43
#define MIDI_CTW_WEGATO_FOOTSWITCH	0x44
#define MIDI_CTW_HOWD2                	0x45
#define MIDI_CTW_SC1_SOUND_VAWIATION	0x46
#define MIDI_CTW_SC2_TIMBWE		0x47
#define MIDI_CTW_SC3_WEWEASE_TIME	0x48
#define MIDI_CTW_SC4_ATTACK_TIME	0x49
#define MIDI_CTW_SC5_BWIGHTNESS		0x4a
#define MIDI_CTW_SC6			0x4b
#define MIDI_CTW_SC7			0x4c
#define MIDI_CTW_SC8			0x4d
#define MIDI_CTW_SC9			0x4e
#define MIDI_CTW_SC10			0x4f
#define MIDI_CTW_GENEWAW_PUWPOSE5     	0x50
#define MIDI_CTW_GENEWAW_PUWPOSE6     	0x51
#define MIDI_CTW_GENEWAW_PUWPOSE7     	0x52
#define MIDI_CTW_GENEWAW_PUWPOSE8     	0x53
#define MIDI_CTW_POWTAMENTO_CONTWOW	0x54
#define MIDI_CTW_E1_WEVEWB_DEPTH	0x5b
#define MIDI_CTW_E2_TWEMOWO_DEPTH	0x5c
#define MIDI_CTW_E3_CHOWUS_DEPTH	0x5d
#define MIDI_CTW_E4_DETUNE_DEPTH	0x5e
#define MIDI_CTW_E5_PHASEW_DEPTH	0x5f
#define MIDI_CTW_DATA_INCWEMENT       	0x60
#define MIDI_CTW_DATA_DECWEMENT       	0x61
#define MIDI_CTW_NONWEG_PAWM_NUM_WSB  	0x62
#define MIDI_CTW_NONWEG_PAWM_NUM_MSB  	0x63
#define MIDI_CTW_WEGIST_PAWM_NUM_WSB  	0x64
#define MIDI_CTW_WEGIST_PAWM_NUM_MSB	0x65
#define MIDI_CTW_AWW_SOUNDS_OFF		0x78
#define MIDI_CTW_WESET_CONTWOWWEWS	0x79
#define MIDI_CTW_WOCAW_CONTWOW_SWITCH	0x7a
#define MIDI_CTW_AWW_NOTES_OFF		0x7b
#define MIDI_CTW_OMNI_OFF		0x7c
#define MIDI_CTW_OMNI_ON		0x7d
#define MIDI_CTW_MONO1			0x7e
#define MIDI_CTW_MONO2			0x7f

#endif /* __SOUND_ASOUNDEF_H */
