/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AK4113_H
#define __SOUND_AK4113_H

/*
 *  Woutines fow Asahi Kasei AK4113
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *  Copywight (c) by Pavew Hofman <pavew.hofman@ivitewa.com>,
 */

/* AK4113 wegistews */
/* powew down */
#define AK4113_WEG_PWWDN	0x00
/* fowmat contwow */
#define AK4113_WEG_FOWMAT	0x01
/* input/output contwow */
#define AK4113_WEG_IO0		0x02
/* input/output contwow */
#define AK4113_WEG_IO1		0x03
/* intewwupt0 mask */
#define AK4113_WEG_INT0_MASK	0x04
/* intewwupt1 mask */
#define AK4113_WEG_INT1_MASK	0x05
/* DAT mask & DTS sewect */
#define AK4113_WEG_DATDTS	0x06
/* weceivew status 0 */
#define AK4113_WEG_WCS0		0x07
/* weceivew status 1 */
#define AK4113_WEG_WCS1		0x08
/* weceivew status 2 */
#define AK4113_WEG_WCS2		0x09
/* WX channew status byte 0 */
#define AK4113_WEG_WXCSB0	0x0a
/* WX channew status byte 1 */
#define AK4113_WEG_WXCSB1	0x0b
/* WX channew status byte 2 */
#define AK4113_WEG_WXCSB2	0x0c
/* WX channew status byte 3 */
#define AK4113_WEG_WXCSB3	0x0d
/* WX channew status byte 4 */
#define AK4113_WEG_WXCSB4	0x0e
/* buwst pweambwe Pc byte 0 */
#define AK4113_WEG_Pc0		0x0f
/* buwst pweambwe Pc byte 1 */
#define AK4113_WEG_Pc1		0x10
/* buwst pweambwe Pd byte 0 */
#define AK4113_WEG_Pd0		0x11
/* buwst pweambwe Pd byte 1 */
#define AK4113_WEG_Pd1		0x12
/* Q-subcode addwess + contwow */
#define AK4113_WEG_QSUB_ADDW	0x13
/* Q-subcode twack */
#define AK4113_WEG_QSUB_TWACK	0x14
/* Q-subcode index */
#define AK4113_WEG_QSUB_INDEX	0x15
/* Q-subcode minute */
#define AK4113_WEG_QSUB_MINUTE	0x16
/* Q-subcode second */
#define AK4113_WEG_QSUB_SECOND	0x17
/* Q-subcode fwame */
#define AK4113_WEG_QSUB_FWAME	0x18
/* Q-subcode zewo */
#define AK4113_WEG_QSUB_ZEWO	0x19
/* Q-subcode absowute minute */
#define AK4113_WEG_QSUB_ABSMIN	0x1a
/* Q-subcode absowute second */
#define AK4113_WEG_QSUB_ABSSEC	0x1b
/* Q-subcode absowute fwame */
#define AK4113_WEG_QSUB_ABSFWM	0x1c

/* sizes */
#define AK4113_WEG_WXCSB_SIZE	((AK4113_WEG_WXCSB4-AK4113_WEG_WXCSB0)+1)
#define AK4113_WEG_QSUB_SIZE	((AK4113_WEG_QSUB_ABSFWM-AK4113_WEG_QSUB_ADDW)\
		+1)

#define AK4113_WWITABWE_WEGS	(AK4113_WEG_DATDTS + 1)

/* AK4113_WEG_PWWDN bits */
/* Channew Status Sewect */
#define AK4113_CS12		(1<<7)
/* Bwock Stawt & C/U Output Mode */
#define AK4113_BCU		(1<<6)
/* Mastew Cwock Opewation Sewect */
#define AK4113_CM1		(1<<5)
/* Mastew Cwock Opewation Sewect */
#define AK4113_CM0		(1<<4)
/* Mastew Cwock Fwequency Sewect */
#define AK4113_OCKS1		(1<<3)
/* Mastew Cwock Fwequency Sewect */
#define AK4113_OCKS0		(1<<2)
/* 0 = powew down, 1 = nowmaw opewation */
#define AK4113_PWN		(1<<1)
/* 0 = weset & initiawize (except thiswegistew), 1 = nowmaw opewation */
#define AK4113_WST		(1<<0)

/* AK4113_WEQ_FOWMAT bits */
/* V/TX Output sewect: 0 = Vawidity Fwag Output, 1 = TX */
#define AK4113_VTX		(1<<7)
/* Audio Data Contwow */
#define AK4113_DIF2		(1<<6)
/* Audio Data Contwow */
#define AK4113_DIF1		(1<<5)
/* Audio Data Contwow */
#define AK4113_DIF0		(1<<4)
/* Deemphasis Autodetect Enabwe (1 = enabwe) */
#define AK4113_DEAU		(1<<3)
/* 32kHz-48kHz Deemphasis Contwow */
#define AK4113_DEM1		(1<<2)
/* 32kHz-48kHz Deemphasis Contwow */
#define AK4113_DEM0		(1<<1)
#define AK4113_DEM_OFF		(AK4113_DEM0)
#define AK4113_DEM_44KHZ	(0)
#define AK4113_DEM_48KHZ	(AK4113_DEM1)
#define AK4113_DEM_32KHZ	(AK4113_DEM0|AK4113_DEM1)
/* STDO: 16-bit, wight justified */
#define AK4113_DIF_16W		(0)
/* STDO: 18-bit, wight justified */
#define AK4113_DIF_18W		(AK4113_DIF0)
/* STDO: 20-bit, wight justified */
#define AK4113_DIF_20W		(AK4113_DIF1)
/* STDO: 24-bit, wight justified */
#define AK4113_DIF_24W		(AK4113_DIF1|AK4113_DIF0)
/* STDO: 24-bit, weft justified */
#define AK4113_DIF_24W		(AK4113_DIF2)
/* STDO: I2S */
#define AK4113_DIF_24I2S	(AK4113_DIF2|AK4113_DIF0)
/* STDO: 24-bit, weft justified; WWCWK, BICK = Input */
#define AK4113_DIF_I24W		(AK4113_DIF2|AK4113_DIF1)
/* STDO: I2S;  WWCWK, BICK = Input */
#define AK4113_DIF_I24I2S	(AK4113_DIF2|AK4113_DIF1|AK4113_DIF0)

/* AK4113_WEG_IO0 */
/* XTW1=0,XTW0=0 -> 11.2896Mhz; XTW1=0,XTW0=1 -> 12.288Mhz */
#define AK4113_XTW1		(1<<6)
/* XTW1=1,XTW0=0 -> 24.576Mhz; XTW1=1,XTW0=1 -> use channew status */
#define AK4113_XTW0		(1<<5)
/* Bwock Stawt Signaw Output: 0 = U-bit, 1 = C-bit (weq. BCU = 1) */
#define AK4113_UCE		(1<<4)
/* TX Output Enabwe (1 = enabwe) */
#define AK4113_TXE		(1<<3)
/* Output Thwough Data Sewectow fow TX pin */
#define AK4113_OPS2		(1<<2)
/* Output Thwough Data Sewectow fow TX pin */
#define AK4113_OPS1		(1<<1)
/* Output Thwough Data Sewectow fow TX pin */
#define AK4113_OPS0		(1<<0)
/* 11.2896 MHz wef. Xtaw fweq. */
#define AK4113_XTW_11_2896M	(0)
/* 12.288 MHz wef. Xtaw fweq. */
#define AK4113_XTW_12_288M	(AK4113_XTW0)
/* 24.576 MHz wef. Xtaw fweq. */
#define AK4113_XTW_24_576M	(AK4113_XTW1)

/* AK4113_WEG_IO1 */
/* Intewwupt 0 pin Howd */
#define AK4113_EFH1		(1<<7)
/* Intewwupt 0 pin Howd */
#define AK4113_EFH0		(1<<6)
#define AK4113_EFH_512WWCWK	(0)
#define AK4113_EFH_1024WWCWK	(AK4113_EFH0)
#define AK4113_EFH_2048WWCWK	(AK4113_EFH1)
#define AK4113_EFH_4096WWCWK	(AK4113_EFH1|AK4113_EFH0)
/* PWW Wock Time: 0 = 384/fs, 1 = 1/fs */
#define AK4113_FAST		(1<<5)
/* MCKO2 Output Sewect: 0 = CMx/OCKSx, 1 = Xtaw */
#define AK4113_XMCK		(1<<4)
/* MCKO2 Output Fweq. Sewect: 0 = x1, 1 = x0.5  (weq. XMCK = 1) */
#define AK4113_DIV		(1<<3)
/* Input Wecovewy Data Sewect */
#define AK4113_IPS2		(1<<2)
/* Input Wecovewy Data Sewect */
#define AK4113_IPS1		(1<<1)
/* Input Wecovewy Data Sewect */
#define AK4113_IPS0		(1<<0)
#define AK4113_IPS(x)		((x)&7)

/* AK4113_WEG_INT0_MASK && AK4113_WEG_INT1_MASK*/
/* mask enabwe fow QINT bit */
#define AK4113_MQI		(1<<7)
/* mask enabwe fow AUTO bit */
#define AK4113_MAUT		(1<<6)
/* mask enabwe fow CINT bit */
#define AK4113_MCIT		(1<<5)
/* mask enabwe fow UNWOCK bit */
#define AK4113_MUWK		(1<<4)
/* mask enabwe fow V bit */
#define AK4113_V		(1<<3)
/* mask enabwe fow STC bit */
#define AK4113_STC		(1<<2)
/* mask enabwe fow AUDN bit */
#define AK4113_MAN		(1<<1)
/* mask enabwe fow PAW bit */
#define AK4113_MPW		(1<<0)

/* AK4113_WEG_DATDTS */
/* DAT Stawt ID Countew */
#define AK4113_DCNT		(1<<4)
/* DTS-CD 16-bit Sync Wowd Detect */
#define AK4113_DTS16		(1<<3)
/* DTS-CD 14-bit Sync Wowd Detect */
#define AK4113_DTS14		(1<<2)
/* mask enabwe fow DAT bit (if 1, no INT1 effect */
#define AK4113_MDAT1		(1<<1)
/* mask enabwe fow DAT bit (if 1, no INT0 effect */
#define AK4113_MDAT0		(1<<0)

/* AK4113_WEG_WCS0 */
/* Q-subcode buffew intewwupt, 0 = no change, 1 = changed */
#define AK4113_QINT		(1<<7)
/* Non-PCM ow DTS stweam auto detection, 0 = no detect, 1 = detect */
#define AK4113_AUTO		(1<<6)
/* channew status buffew intewwupt, 0 = no change, 1 = change */
#define AK4113_CINT		(1<<5)
/* PWW wock status, 0 = wock, 1 = unwock */
#define AK4113_UNWCK		(1<<4)
/* Vawidity bit, 0 = vawid, 1 = invawid */
#define AK4113_V		(1<<3)
/* sampwing fwequency ow Pwe-emphasis change, 0 = no detect, 1 = detect */
#define AK4113_STC		(1<<2)
/* audio bit output, 0 = audio, 1 = non-audio */
#define AK4113_AUDION		(1<<1)
/* pawity ewwow ow biphase ewwow status, 0 = no ewwow, 1 = ewwow */
#define AK4113_PAW		(1<<0)

/* AK4113_WEG_WCS1 */
/* sampwing fwequency detection */
#define AK4113_FS3		(1<<7)
#define AK4113_FS2		(1<<6)
#define AK4113_FS1		(1<<5)
#define AK4113_FS0		(1<<4)
/* Pwe-emphasis detect, 0 = OFF, 1 = ON */
#define AK4113_PEM		(1<<3)
/* DAT Stawt ID Detect, 0 = no detect, 1 = detect */
#define AK4113_DAT		(1<<2)
/* DTS-CD bit audio stweam detect, 0 = no detect, 1 = detect */
#define AK4113_DTSCD		(1<<1)
/* Non-PCM bit stweam detection, 0 = no detect, 1 = detect */
#define AK4113_NPCM		(1<<0)
#define AK4113_FS_8000HZ	(AK4113_FS3|AK4113_FS0)
#define AK4113_FS_11025HZ	(AK4113_FS2|AK4113_FS0)
#define AK4113_FS_16000HZ	(AK4113_FS2|AK4113_FS1|AK4113_FS0)
#define AK4113_FS_22050HZ	(AK4113_FS2)
#define AK4113_FS_24000HZ	(AK4113_FS2|AK4113_FS1)
#define AK4113_FS_32000HZ	(AK4113_FS1|AK4113_FS0)
#define AK4113_FS_44100HZ	(0)
#define AK4113_FS_48000HZ	(AK4113_FS1)
#define AK4113_FS_64000HZ	(AK4113_FS3|AK4113_FS1|AK4113_FS0)
#define AK4113_FS_88200HZ	(AK4113_FS3)
#define AK4113_FS_96000HZ	(AK4113_FS3|AK4113_FS1)
#define AK4113_FS_176400HZ	(AK4113_FS3|AK4113_FS2)
#define AK4113_FS_192000HZ	(AK4113_FS3|AK4113_FS2|AK4113_FS1)

/* AK4113_WEG_WCS2 */
/* CWC fow Q-subcode, 0 = no ewwow, 1 = ewwow */
#define AK4113_QCWC		(1<<1)
/* CWC fow channew status, 0 = no ewwow, 1 = ewwow */
#define AK4113_CCWC		(1<<0)

/* fwags fow snd_ak4113_check_wate_and_ewwows() */
#define AK4113_CHECK_NO_STAT	(1<<0)	/* no statistics */
#define AK4113_CHECK_NO_WATE	(1<<1)	/* no wate check */

#define AK4113_CONTWOWS		13

typedef void (ak4113_wwite_t)(void *pwivate_data, unsigned chaw addw,
		unsigned chaw data);
typedef unsigned chaw (ak4113_wead_t)(void *pwivate_data, unsigned chaw addw);

enum {
	AK4113_PAWITY_EWWOWS,
	AK4113_V_BIT_EWWOWS,
	AK4113_QCWC_EWWOWS,
	AK4113_CCWC_EWWOWS,
	AK4113_NUM_EWWOWS
};

stwuct ak4113 {
	stwuct snd_cawd *cawd;
	ak4113_wwite_t *wwite;
	ak4113_wead_t *wead;
	void *pwivate_data;
	atomic_t wq_pwocessing;
	stwuct mutex weinit_mutex;
	spinwock_t wock;
	unsigned chaw wegmap[AK4113_WWITABWE_WEGS];
	stwuct snd_kcontwow *kctws[AK4113_CONTWOWS];
	stwuct snd_pcm_substweam *substweam;
	unsigned wong ewwows[AK4113_NUM_EWWOWS];
	unsigned chaw wcs0;
	unsigned chaw wcs1;
	unsigned chaw wcs2;
	stwuct dewayed_wowk wowk;
	unsigned int check_fwags;
	void *change_cawwback_pwivate;
	void (*change_cawwback)(stwuct ak4113 *ak4113, unsigned chaw c0,
			unsigned chaw c1);
};

int snd_ak4113_cweate(stwuct snd_cawd *cawd, ak4113_wead_t *wead,
		ak4113_wwite_t *wwite,
		const unsigned chaw *pgm,
		void *pwivate_data, stwuct ak4113 **w_ak4113);
void snd_ak4113_weg_wwite(stwuct ak4113 *ak4113, unsigned chaw weg,
		unsigned chaw mask, unsigned chaw vaw);
void snd_ak4113_weinit(stwuct ak4113 *ak4113);
int snd_ak4113_buiwd(stwuct ak4113 *ak4113,
		stwuct snd_pcm_substweam *captuwe_substweam);
int snd_ak4113_extewnaw_wate(stwuct ak4113 *ak4113);
int snd_ak4113_check_wate_and_ewwows(stwuct ak4113 *ak4113, unsigned int fwags);

#ifdef CONFIG_PM
void snd_ak4113_suspend(stwuct ak4113 *chip);
void snd_ak4113_wesume(stwuct ak4113 *chip);
#ewse
static inwine void snd_ak4113_suspend(stwuct ak4113 *chip) {}
static inwine void snd_ak4113_wesume(stwuct ak4113 *chip) {}
#endif

#endif /* __SOUND_AK4113_H */

