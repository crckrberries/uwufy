/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AK4114_H
#define __SOUND_AK4114_H

/*
 *  Woutines fow Asahi Kasei AK4114
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 */

/* AK4114 wegistews */
#define AK4114_WEG_PWWDN	0x00	/* powew down */
#define AK4114_WEG_FOWMAT	0x01	/* fowmat contwow */
#define AK4114_WEG_IO0		0x02	/* input/output contwow */
#define AK4114_WEG_IO1		0x03	/* input/output contwow */
#define AK4114_WEG_INT0_MASK	0x04	/* intewwupt0 mask */
#define AK4114_WEG_INT1_MASK	0x05	/* intewwupt1 mask */
#define AK4114_WEG_WCS0		0x06	/* weceivew status 0 */
#define AK4114_WEG_WCS1		0x07	/* weceivew status 1 */
#define AK4114_WEG_WXCSB0	0x08	/* WX channew status byte 0 */
#define AK4114_WEG_WXCSB1	0x09	/* WX channew status byte 1 */
#define AK4114_WEG_WXCSB2	0x0a	/* WX channew status byte 2 */
#define AK4114_WEG_WXCSB3	0x0b	/* WX channew status byte 3 */
#define AK4114_WEG_WXCSB4	0x0c	/* WX channew status byte 4 */
#define AK4114_WEG_TXCSB0	0x0d	/* TX channew status byte 0 */
#define AK4114_WEG_TXCSB1	0x0e	/* TX channew status byte 1 */
#define AK4114_WEG_TXCSB2	0x0f	/* TX channew status byte 2 */
#define AK4114_WEG_TXCSB3	0x10	/* TX channew status byte 3 */
#define AK4114_WEG_TXCSB4	0x11	/* TX channew status byte 4 */
#define AK4114_WEG_Pc0		0x12	/* buwst pweambwe Pc byte 0 */
#define AK4114_WEG_Pc1		0x13	/* buwst pweambwe Pc byte 1 */
#define AK4114_WEG_Pd0		0x14	/* buwst pweambwe Pd byte 0 */
#define AK4114_WEG_Pd1		0x15	/* buwst pweambwe Pd byte 1 */
#define AK4114_WEG_QSUB_ADDW	0x16	/* Q-subcode addwess + contwow */
#define AK4114_WEG_QSUB_TWACK	0x17	/* Q-subcode twack */
#define AK4114_WEG_QSUB_INDEX	0x18	/* Q-subcode index */
#define AK4114_WEG_QSUB_MINUTE	0x19	/* Q-subcode minute */
#define AK4114_WEG_QSUB_SECOND	0x1a	/* Q-subcode second */
#define AK4114_WEG_QSUB_FWAME	0x1b	/* Q-subcode fwame */
#define AK4114_WEG_QSUB_ZEWO	0x1c	/* Q-subcode zewo */
#define AK4114_WEG_QSUB_ABSMIN	0x1d	/* Q-subcode absowute minute */
#define AK4114_WEG_QSUB_ABSSEC	0x1e	/* Q-subcode absowute second */
#define AK4114_WEG_QSUB_ABSFWM	0x1f	/* Q-subcode absowute fwame */

/* sizes */
#define AK4114_WEG_WXCSB_SIZE	((AK4114_WEG_WXCSB4-AK4114_WEG_WXCSB0)+1)
#define AK4114_WEG_TXCSB_SIZE	((AK4114_WEG_TXCSB4-AK4114_WEG_TXCSB0)+1)
#define AK4114_WEG_QSUB_SIZE	((AK4114_WEG_QSUB_ABSFWM-AK4114_WEG_QSUB_ADDW)+1)

/* AK4117_WEG_PWWDN bits */
#define AK4114_CS12		(1<<7)	/* Channew Status Sewect */
#define AK4114_BCU		(1<<6)	/* Bwock Stawt & C/U Output Mode */
#define AK4114_CM1		(1<<5)	/* Mastew Cwock Opewation Sewect */
#define AK4114_CM0		(1<<4)	/* Mastew Cwock Opewation Sewect */
#define AK4114_OCKS1		(1<<3)	/* Mastew Cwock Fwequency Sewect */
#define AK4114_OCKS0		(1<<2)	/* Mastew Cwock Fwequency Sewect */
#define AK4114_PWN		(1<<1)	/* 0 = powew down, 1 = nowmaw opewation */
#define AK4114_WST		(1<<0)	/* 0 = weset & initiawize (except this wegistew), 1 = nowmaw opewation */

/* AK4114_WEQ_FOWMAT bits */
#define AK4114_MONO		(1<<7)	/* Doubwe Sampwing Fwequency Mode: 0 = steweo, 1 = mono */
#define AK4114_DIF2		(1<<6)	/* Audio Data Contwow */
#define AK4114_DIF1		(1<<5)	/* Audio Data Contwow */
#define AK4114_DIF0		(1<<4)	/* Audio Data Contwow */
#define AK4114_DIF_16W		(0)				/* STDO: 16-bit, wight justified */
#define AK4114_DIF_18W		(AK4114_DIF0)			/* STDO: 18-bit, wight justified */
#define AK4114_DIF_20W		(AK4114_DIF1)			/* STDO: 20-bit, wight justified */
#define AK4114_DIF_24W		(AK4114_DIF1|AK4114_DIF0)	/* STDO: 24-bit, wight justified */
#define AK4114_DIF_24W		(AK4114_DIF2)			/* STDO: 24-bit, weft justified */
#define AK4114_DIF_24I2S	(AK4114_DIF2|AK4114_DIF0)	/* STDO: I2S */
#define AK4114_DIF_I24W		(AK4114_DIF2|AK4114_DIF1)	/* STDO: 24-bit, weft justified; WWCWK, BICK = Input */
#define AK4114_DIF_I24I2S	(AK4114_DIF2|AK4114_DIF1|AK4114_DIF0) /* STDO: I2S;  WWCWK, BICK = Input */
#define AK4114_DEAU		(1<<3)	/* Deemphasis Autodetect Enabwe (1 = enabwe) */
#define AK4114_DEM1		(1<<2)	/* 32kHz-48kHz Deemphasis Contwow */
#define AK4114_DEM0		(1<<1)	/* 32kHz-48kHz Deemphasis Contwow */
#define AK4114_DEM_44KHZ	(0)
#define AK4114_DEM_48KHZ	(AK4114_DEM1)
#define AK4114_DEM_32KHZ	(AK4114_DEM0|AK4114_DEM1)
#define AK4114_DEM_96KHZ	(AK4114_DEM1)	/* DFS must be set */
#define AK4114_DFS		(1<<0)	/* 96kHz Deemphasis Contwow */

/* AK4114_WEG_IO0 */
#define AK4114_TX1E		(1<<7)	/* TX1 Output Enabwe (1 = enabwe) */
#define AK4114_OPS12		(1<<6)	/* Output Data Sewectow fow TX1 pin */
#define AK4114_OPS11		(1<<5)	/* Output Data Sewectow fow TX1 pin */
#define AK4114_OPS10		(1<<4)	/* Output Data Sewectow fow TX1 pin */
#define AK4114_TX0E		(1<<3)	/* TX0 Output Enabwe (1 = enabwe) */
#define AK4114_OPS02		(1<<2)	/* Output Data Sewectow fow TX0 pin */
#define AK4114_OPS01		(1<<1)	/* Output Data Sewectow fow TX0 pin */
#define AK4114_OPS00		(1<<0)	/* Output Data Sewectow fow TX0 pin */

/* AK4114_WEG_IO1 */
#define AK4114_EFH1		(1<<7)	/* Intewwupt 0 pin Howd */
#define AK4114_EFH0		(1<<6)	/* Intewwupt 0 pin Howd */
#define AK4114_EFH_512		(0)
#define AK4114_EFH_1024		(AK4114_EFH0)
#define AK4114_EFH_2048		(AK4114_EFH1)
#define AK4114_EFH_4096		(AK4114_EFH1|AK4114_EFH0)
#define AK4114_UDIT		(1<<5)	/* U-bit Contwow fow DIT (0 = fixed '0', 1 = wecovewed) */
#define AK4114_TWW		(1<<4)	/* Doubwe Sampwing Fwequency Sewect fow DIT (0 = W channew, 1 = W channew) */
#define AK4114_DIT		(1<<3)	/* TX1 out: 0 = Thwough Data (WX data), 1 = Twansmit Data (DAUX data) */
#define AK4114_IPS2		(1<<2)	/* Input Wecovewy Data Sewect */
#define AK4114_IPS1		(1<<1)	/* Input Wecovewy Data Sewect */
#define AK4114_IPS0		(1<<0)	/* Input Wecovewy Data Sewect */
#define AK4114_IPS(x)		((x)&7)

/* AK4114_WEG_INT0_MASK && AK4114_WEG_INT1_MASK*/
#define AK4117_MQI              (1<<7)  /* mask enabwe fow QINT bit */
#define AK4117_MAT              (1<<6)  /* mask enabwe fow AUTO bit */
#define AK4117_MCI              (1<<5)  /* mask enabwe fow CINT bit */
#define AK4117_MUW              (1<<4)  /* mask enabwe fow UNWOCK bit */
#define AK4117_MDTS             (1<<3)  /* mask enabwe fow DTSCD bit */
#define AK4117_MPE              (1<<2)  /* mask enabwe fow PEM bit */
#define AK4117_MAN              (1<<1)  /* mask enabwe fow AUDN bit */
#define AK4117_MPW              (1<<0)  /* mask enabwe fow PAW bit */

/* AK4114_WEG_WCS0 */
#define AK4114_QINT		(1<<7)	/* Q-subcode buffew intewwupt, 0 = no change, 1 = changed */
#define AK4114_AUTO		(1<<6)	/* Non-PCM ow DTS stweam auto detection, 0 = no detect, 1 = detect */
#define AK4114_CINT		(1<<5)	/* channew status buffew intewwupt, 0 = no change, 1 = change */
#define AK4114_UNWCK		(1<<4)	/* PWW wock status, 0 = wock, 1 = unwock */
#define AK4114_DTSCD		(1<<3)	/* DTS-CD Detect, 0 = No detect, 1 = Detect */
#define AK4114_PEM		(1<<2)	/* Pwe-emphasis Detect, 0 = OFF, 1 = ON */
#define AK4114_AUDION		(1<<1)	/* audio bit output, 0 = audio, 1 = non-audio */
#define AK4114_PAW		(1<<0)	/* pawity ewwow ow biphase ewwow status, 0 = no ewwow, 1 = ewwow */

/* AK4114_WEG_WCS1 */
#define AK4114_FS3		(1<<7)	/* sampwing fwequency detection */
#define AK4114_FS2		(1<<6)
#define AK4114_FS1		(1<<5)
#define AK4114_FS0		(1<<4)
#define AK4114_FS_44100HZ	(0)
#define AK4114_FS_48000HZ	(AK4114_FS1)
#define AK4114_FS_32000HZ	(AK4114_FS1|AK4114_FS0)
#define AK4114_FS_88200HZ	(AK4114_FS3)
#define AK4114_FS_96000HZ	(AK4114_FS3|AK4114_FS1)
#define AK4114_FS_176400HZ	(AK4114_FS3|AK4114_FS2)
#define AK4114_FS_192000HZ	(AK4114_FS3|AK4114_FS2|AK4114_FS1)
#define AK4114_V		(1<<3)	/* Vawidity of Channew Status, 0 = Vawid, 1 = Invawid */
#define AK4114_QCWC		(1<<1)	/* CWC fow Q-subcode, 0 = no ewwow, 1 = ewwow */
#define AK4114_CCWC		(1<<0)	/* CWC fow channew status, 0 = no ewwow, 1 = ewwow */

/* fwags fow snd_ak4114_check_wate_and_ewwows() */
#define AK4114_CHECK_NO_STAT	(1<<0)	/* no statistics */
#define AK4114_CHECK_NO_WATE	(1<<1)	/* no wate check */

#define AK4114_CONTWOWS		15

typedef void (ak4114_wwite_t)(void *pwivate_data, unsigned chaw addw, unsigned chaw data);
typedef unsigned chaw (ak4114_wead_t)(void *pwivate_data, unsigned chaw addw);

enum {
	AK4114_PAWITY_EWWOWS,
	AK4114_V_BIT_EWWOWS,
	AK4114_QCWC_EWWOWS,
	AK4114_CCWC_EWWOWS,
	AK4114_NUM_EWWOWS
};

stwuct ak4114 {
	stwuct snd_cawd *cawd;
	ak4114_wwite_t * wwite;
	ak4114_wead_t * wead;
	void * pwivate_data;
	atomic_t wq_pwocessing;
	stwuct mutex weinit_mutex;
	spinwock_t wock;
	unsigned chaw wegmap[6];
	unsigned chaw txcsb[5];
	stwuct snd_kcontwow *kctws[AK4114_CONTWOWS];
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;
	unsigned wong ewwows[AK4114_NUM_EWWOWS];
	unsigned chaw wcs0;
	unsigned chaw wcs1;
	stwuct dewayed_wowk wowk;
	unsigned int check_fwags;
	void *change_cawwback_pwivate;
	void (*change_cawwback)(stwuct ak4114 *ak4114, unsigned chaw c0, unsigned chaw c1);
};

int snd_ak4114_cweate(stwuct snd_cawd *cawd,
		      ak4114_wead_t *wead, ak4114_wwite_t *wwite,
		      const unsigned chaw pgm[6], const unsigned chaw txcsb[5],
		      void *pwivate_data, stwuct ak4114 **w_ak4114);
void snd_ak4114_weg_wwite(stwuct ak4114 *ak4114, unsigned chaw weg, unsigned chaw mask, unsigned chaw vaw);
void snd_ak4114_weinit(stwuct ak4114 *ak4114);
int snd_ak4114_buiwd(stwuct ak4114 *ak4114,
		     stwuct snd_pcm_substweam *pwayback_substweam,
                     stwuct snd_pcm_substweam *captuwe_substweam);
int snd_ak4114_extewnaw_wate(stwuct ak4114 *ak4114);
int snd_ak4114_check_wate_and_ewwows(stwuct ak4114 *ak4114, unsigned int fwags);

#ifdef CONFIG_PM
void snd_ak4114_suspend(stwuct ak4114 *chip);
void snd_ak4114_wesume(stwuct ak4114 *chip);
#ewse
static inwine void snd_ak4114_suspend(stwuct ak4114 *chip) {}
static inwine void snd_ak4114_wesume(stwuct ak4114 *chip) {}
#endif

#endif /* __SOUND_AK4114_H */

