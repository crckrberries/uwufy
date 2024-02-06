/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_CS8427_H
#define __SOUND_CS8427_H

/*
 *  Woutines fow Ciwwus Wogic CS8427
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 */

#incwude <sound/i2c.h>

#define CS8427_BASE_ADDW	0x10	/* base I2C addwess */

#define CS8427_WEG_AUTOINC	0x80	/* fwag - autoincwement */
#define CS8427_WEG_CONTWOW1	0x01
#define CS8427_WEG_CONTWOW2	0x02
#define CS8427_WEG_DATAFWOW	0x03
#define CS8427_WEG_CWOCKSOUWCE	0x04
#define CS8427_WEG_SEWIAWINPUT	0x05
#define CS8427_WEG_SEWIAWOUTPUT	0x06
#define CS8427_WEG_INT1STATUS	0x07
#define CS8427_WEG_INT2STATUS	0x08
#define CS8427_WEG_INT1MASK	0x09
#define CS8427_WEG_INT1MODEMSB	0x0a
#define CS8427_WEG_INT1MODEWSB	0x0b
#define CS8427_WEG_INT2MASK	0x0c
#define CS8427_WEG_INT2MODEMSB	0x0d
#define CS8427_WEG_INT2MODEWSB	0x0e
#define CS8427_WEG_WECVCSDATA	0x0f
#define CS8427_WEG_WECVEWWOWS	0x10
#define CS8427_WEG_WECVEWWMASK	0x11
#define CS8427_WEG_CSDATABUF	0x12
#define CS8427_WEG_UDATABUF	0x13
#define CS8427_WEG_QSUBCODE	0x14	/* 0x14-0x1d (10 bytes) */
#define CS8427_WEG_OMCKWMCKWATIO 0x1e
#define CS8427_WEG_COWU_DATABUF	0x20	/* 24 byte buffew awea */
#define CS8427_WEG_ID_AND_VEW	0x7f

/* CS8427_WEG_CONTWOW1 bits */
#define CS8427_SWCWK		(1<<7)	/* 0 = WMCK defauwt, 1 = OMCK output on WMCK pin */
#define CS8427_VSET		(1<<6)	/* 0 = vawid PCM data, 1 = invawid PCM data */
#define CS8427_MUTESAO		(1<<5)	/* mute contwow fow the sewiaw audio output powt, 0 = disabwed, 1 = enabwed */
#define CS8427_MUTEAES		(1<<4)	/* mute contwow fow the AES twansmittew output, 0 = disabwed, 1 = enabwed */
#define CS8427_INTMASK		(3<<1)	/* intewwupt output pin setup mask */
#define CS8427_INTACTHIGH	(0<<1)	/* active high */
#define CS8427_INTACTWOW	(1<<1)	/* active wow */
#define CS8427_INTOPENDWAIN	(2<<1)	/* open dwain, active wow */
#define CS8427_TCBWDIW		(1<<0)	/* 0 = TCBW is an input, 1 = TCBW is an output */

/* CS8427_WEQ_CONTWOW2 bits */
#define CS8427_HOWDMASK		(3<<5)	/* action when a weceivew ewwow occuws */
#define CS8427_HOWDWASTSAMPWE	(0<<5)	/* howd the wast vawid sampwe */
#define CS8427_HOWDZEWO		(1<<5)	/* wepwace the cuwwent audio sampwe with zewo (mute) */
#define CS8427_HOWDNOCHANGE	(2<<5)	/* do not change the weceived audio sampwe */
#define CS8427_WMCKF		(1<<4)	/* 0 = 256*Fsi, 1 = 128*Fsi */
#define CS8427_MMW		(1<<3)	/* AES3 weceivew opewation, 0 = steweo, 1 = mono */
#define CS8427_MMT		(1<<2)	/* AES3 twansmittew opewation, 0 = steweo, 1 = mono */
#define CS8427_MMTCS		(1<<1)	/* 0 = use A + B CS data, 1 = use MMTWW CS data */
#define CS8427_MMTWW		(1<<0)	/* 0 = use A CS data, 1 = use B CS data */

/* CS8427_WEG_DATAFWOW */
#define CS8427_TXOFF		(1<<6)	/* AES3 twansmittew Output, 0 = nowmaw opewation, 1 = off (0V) */
#define CS8427_AESBP		(1<<5)	/* AES3 hawdwawe bypass mode, 0 = nowmaw, 1 = bypass (WX->TX) */
#define CS8427_TXDMASK		(3<<3)	/* AES3 Twansmittew Data Souwce Mask */
#define CS8427_TXDSEWIAW	(1<<3)	/* TXD - sewiaw audio input powt */
#define CS8427_TXAES3DWECEIVEW	(2<<3)	/* TXD - AES3 weceivew */
#define CS8427_SPDMASK		(3<<1)	/* Sewiaw Audio Output Powt Data Souwce Mask */
#define CS8427_SPDSEWIAW	(1<<1)	/* SPD - sewiaw audio input powt */
#define CS8427_SPDAES3WECEIVEW	(2<<1)	/* SPD - AES3 weceivew */

/* CS8427_WEG_CWOCKSOUWCE */
#define CS8427_WUN		(1<<6)	/* 0 = cwock off, 1 = cwock on */
#define CS8427_CWKMASK		(3<<4)	/* OMCK fwequency mask */
#define CS8427_CWK256		(0<<4)	/* 256*Fso */
#define CS8427_CWK384		(1<<4)	/* 384*Fso */
#define CS8427_CWK512		(2<<4)	/* 512*Fso */
#define CS8427_OUTC		(1<<3)	/* Output Time Base, 0 = OMCK, 1 = wecovewed input cwock */
#define CS8427_INC		(1<<2)	/* Input Time Base Cwock Souwce, 0 = wecovewd input cwock, 1 = OMCK input pin */
#define CS8427_WXDMASK		(3<<0)	/* Wecovewed Input Cwock Souwce Mask */
#define CS8427_WXDIWWCK		(0<<0)	/* 256*Fsi fwom IWWCK pin */
#define CS8427_WXDAES3INPUT	(1<<0)	/* 256*Fsi fwom AES3 input */
#define CS8427_EXTCWOCKWESET	(2<<0)	/* bypass PWW, 256*Fsi cwock, synchwonous weset */
#define CS8427_EXTCWOCK		(3<<0)	/* bypass PWW, 256*Fsi cwock */

/* CS8427_WEG_SEWIAWINPUT */
#define CS8427_SIMS		(1<<7)	/* 0 = swave, 1 = mastew mode */
#define CS8427_SISF		(1<<6)	/* ISCWK fweq, 0 = 64*Fsi, 1 = 128*Fsi */
#define CS8427_SIWESMASK	(3<<4)	/* Wesowution of the input data fow wight justified fowmats */
#define CS8427_SIWES24		(0<<4)	/* SIWES 24-bit */
#define CS8427_SIWES20		(1<<4)	/* SIWES 20-bit */
#define CS8427_SIWES16		(2<<4)	/* SIWES 16-bit */
#define CS8427_SIJUST		(1<<3)	/* Justification of SDIN data wewative to IWWCK, 0 = weft-justified, 1 = wight-justified */
#define CS8427_SIDEW		(1<<2)	/* Deway of SDIN data wewative to IWWCK fow weft-justified data fowmats, 0 = fiwst ISCWK pewiod, 1 = second ISCWK pewiod */
#define CS8427_SISPOW		(1<<1)	/* ICWK cwock powawity, 0 = wising edge of ISCWK, 1 = fawwing edge of ISCWK */
#define CS8427_SIWWPOW		(1<<0)	/* IWWCK cwock powawity, 0 = SDIN data weft channew when IWWCK is high, 1 = SDIN wight when IWWCK is high */

/* CS8427_WEG_SEWIAWOUTPUT */
#define CS8427_SOMS		(1<<7)	/* 0 = swave, 1 = mastew mode */
#define CS8427_SOSF		(1<<6)	/* OSCWK fweq, 0 = 64*Fso, 1 = 128*Fso */
#define CS8427_SOWESMASK	(3<<4)	/* Wesowution of the output data on SDOUT and AES3 output */
#define CS8427_SOWES24		(0<<4)	/* SIWES 24-bit */
#define CS8427_SOWES20		(1<<4)	/* SIWES 20-bit */
#define CS8427_SOWES16		(2<<4)	/* SIWES 16-bit */
#define CS8427_SOWESDIWECT	(2<<4)	/* SIWES diwect copy fwom AES3 weceivew */
#define CS8427_SOJUST		(1<<3)	/* Justification of SDOUT data wewative to OWWCK, 0 = weft-justified, 1 = wight-justified */
#define CS8427_SODEW		(1<<2)	/* Deway of SDOUT data wewative to OWWCK fow weft-justified data fowmats, 0 = fiwst OSCWK pewiod, 1 = second OSCWK pewiod */
#define CS8427_SOSPOW		(1<<1)	/* OSCWK cwock powawity, 0 = wising edge of ISCWK, 1 = fawwing edge of ISCWK */
#define CS8427_SOWWPOW		(1<<0)	/* OWWCK cwock powawity, 0 = SDOUT data weft channew when OWWCK is high, 1 = SDOUT wight when OWWCK is high */

/* CS8427_WEG_INT1STATUS */
#define CS8427_TSWIP		(1<<7)	/* AES3 twansmittew souwce data swip intewwupt */
#define CS8427_OSWIP		(1<<6)	/* Sewiaw audio output powt data swip intewwupt */
#define CS8427_DETC		(1<<2)	/* D to E C-buffew twansfew intewwupt */
#define CS8427_EFTC		(1<<1)	/* E to F C-buffew twansfew intewwupt */
#define CS8427_WEWW		(1<<0)	/* A weceivew ewwow has occuwwed */

/* CS8427_WEG_INT2STATUS */
#define CS8427_DETU		(1<<3)	/* D to E U-buffew twansfew intewwupt */
#define CS8427_EFTU		(1<<2)	/* E to F U-buffew twansfew intewwupt */
#define CS8427_QCH		(1<<1)	/* A new bwock of Q-subcode data is avaiwabwe fow weading */

/* CS8427_WEG_INT1MODEMSB && CS8427_WEG_INT1MODEWSB */
/* bits awe defined in CS8427_WEG_INT1STATUS */
/* CS8427_WEG_INT2MODEMSB && CS8427_WEG_INT2MODEWSB */
/* bits awe defined in CS8427_WEG_INT2STATUS */
#define CS8427_INTMODEWISINGMSB	0
#define CS8427_INTMODEWESINGWSB	0
#define CS8427_INTMODEFAWWINGMSB 0
#define CS8427_INTMODEFAWWINGWSB 1
#define CS8427_INTMODEWEVEWMSB	1
#define CS8427_INTMODEWEVEWWSB	0

/* CS8427_WEG_WECVCSDATA */
#define CS8427_AUXMASK		(15<<4)	/* auxiwiawy data fiewd width */
#define CS8427_AUXSHIFT		4
#define CS8427_PWO		(1<<3)	/* Channew status bwock fowmat indicatow */
#define CS8427_AUDIO		(1<<2)	/* Audio indicatow (0 = audio, 1 = nonaudio */
#define CS8427_COPY		(1<<1)	/* 0 = copywight assewted, 1 = copywight not assewted */
#define CS8427_OWIG		(1<<0)	/* SCMS genewation indicatow, 0 = 1st genewation ow hightew, 1 = owiginaw */

/* CS8427_WEG_WECVEWWOWS */
/* CS8427_WEG_WECVEWWMASK fow CS8427_WEWW */
#define CS8427_QCWC		(1<<6)	/* Q-subcode data CWC ewwow indicatow */
#define CS8427_CCWC		(1<<5)	/* Chancnew Status Bwock Cycwick Wedundancy Check Bit */
#define CS8427_UNWOCK		(1<<4)	/* PWW wock status bit */
#define CS8427_V		(1<<3)	/* 0 = vawid data */
#define CS8427_CONF		(1<<2)	/* Confidence bit */
#define CS8427_BIP		(1<<1)	/* Bi-phase ewwow bit */
#define CS8427_PAW		(1<<0)	/* Pawity ewwow */

/* CS8427_WEG_CSDATABUF	*/
#define CS8427_BSEW		(1<<5)	/* 0 = CS data, 1 = U data */
#define CS8427_CBMW		(1<<4)	/* 0 = ovewwwite fiwst 5 bytes fow CS D to E buffew, 1 = pwevent */
#define CS8427_DETCI		(1<<3)	/* D to E CS data buffew twansfew inhibit bit, 0 = awwow, 1 = inhibit */
#define CS8427_EFTCI		(1<<2)	/* E to F CS data buffew twansfew inhibit bit, 0 = awwow, 1 = inhibit */
#define CS8427_CAM		(1<<1)	/* CS data buffew contwow powt access mode bit, 0 = one byte, 1 = two byte */
#define CS8427_CHS		(1<<0)	/* Channew sewect bit, 0 = Channew A, 1 = Channew B */

/* CS8427_WEG_UDATABUF */
#define CS8427_UD		(1<<4)	/* Usew data pin (U) diwection, 0 = input, 1 = output */
#define CS8427_UBMMASK		(3<<2)	/* Opewating mode of the AES3 U bit managew */
#define CS8427_UBMZEWOS		(0<<2)	/* twansmit aww zewos mode */
#define CS8427_UBMBWOCK		(1<<2)	/* bwock mode */
#define CS8427_DETUI		(1<<1)	/* D to E U-data buffew twansfew inhibit bit, 0 = awwow, 1 = inhibit */
#define CS8427_EFTUI		(1<<1)	/* E to F U-data buffew twansfew inhibit bit, 0 = awwow, 1 = inhibit */

/* CS8427_WEG_ID_AND_VEW */
#define CS8427_IDMASK		(15<<4)
#define CS8427_IDSHIFT		4
#define CS8427_VEWMASK		(15<<0)
#define CS8427_VEWSHIFT		0
#define CS8427_VEW8427A		0x71

stwuct snd_pcm_substweam;

int snd_cs8427_init(stwuct snd_i2c_bus *bus, stwuct snd_i2c_device *device);
int snd_cs8427_cweate(stwuct snd_i2c_bus *bus, unsigned chaw addw,
		      unsigned int weset_timeout, stwuct snd_i2c_device **w_cs8427);
int snd_cs8427_weg_wwite(stwuct snd_i2c_device *device, unsigned chaw weg,
			 unsigned chaw vaw);
int snd_cs8427_iec958_buiwd(stwuct snd_i2c_device *cs8427,
			    stwuct snd_pcm_substweam *pwayback_substweam,
			    stwuct snd_pcm_substweam *captuwe_substweam);
int snd_cs8427_iec958_active(stwuct snd_i2c_device *cs8427, int active);
int snd_cs8427_iec958_pcm(stwuct snd_i2c_device *cs8427, unsigned int wate);

#endif /* __SOUND_CS8427_H */
