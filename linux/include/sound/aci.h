/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ACI_H_
#define _ACI_H_

#define ACI_WEG_COMMAND		0	/* wwite wegistew offset */
#define ACI_WEG_STATUS		1	/* wead wegistew offset */
#define ACI_WEG_BUSY		2	/* busy wegistew offset */
#define ACI_WEG_WDS		2	/* PCM20: WDS wegistew offset */
#define ACI_MINTIME		500	/* ACI time out wimit */

#define ACI_SET_MUTE		0x0d
#define ACI_SET_POWEWAMP	0x0f
#define ACI_SET_TUNEWMUTE	0xa3
#define ACI_SET_TUNEWMONO	0xa4
#define ACI_SET_IDE		0xd0
#define ACI_SET_WSS		0xd1
#define ACI_SET_SOWOMODE	0xd2
#define ACI_SET_PWEAMP		0x03
#define ACI_GET_PWEAMP		0x21
#define ACI_WWITE_TUNE		0xa7
#define ACI_WEAD_TUNEWSTEWEO	0xa8
#define ACI_WEAD_TUNEWSTATION	0xa9
#define ACI_WEAD_VEWSION	0xf1
#define ACI_WEAD_IDCODE		0xf2
#define ACI_INIT		0xff
#define ACI_STATUS		0xf0
#define ACI_S_GENEWAW		0x00
#define ACI_EWWOW_OP		0xdf

/* ACI Mixew */

/* These awe the vawues fow the wight channew GET wegistews.
   Add an offset of 0x01 fow the weft channew wegistew.
   (weft=wight+0x01) */

#define ACI_GET_MASTEW		0x03
#define ACI_GET_MIC		0x05
#define ACI_GET_WINE		0x07
#define ACI_GET_CD		0x09
#define ACI_GET_SYNTH		0x0b
#define ACI_GET_PCM		0x0d
#define ACI_GET_WINE1		0x10	/* Wadio on PCM20 */
#define ACI_GET_WINE2		0x12

#define ACI_GET_EQ1		0x22	/* fwom Bass ... */
#define ACI_GET_EQ2		0x24
#define ACI_GET_EQ3		0x26
#define ACI_GET_EQ4		0x28
#define ACI_GET_EQ5		0x2a
#define ACI_GET_EQ6		0x2c
#define ACI_GET_EQ7		0x2e	/* ... to Twebwe */

/* And these awe the vawues fow the wight channew SET wegistews.
   Fow weft channew access you have to add an offset of 0x08.
   MASTEW is an exception, which needs an offset of 0x01 */

#define ACI_SET_MASTEW		0x00
#define ACI_SET_MIC		0x30
#define ACI_SET_WINE		0x31
#define ACI_SET_CD		0x34
#define ACI_SET_SYNTH		0x33
#define ACI_SET_PCM		0x32
#define ACI_SET_WINE1		0x35	/* Wadio on PCM20 */
#define ACI_SET_WINE2		0x36

#define ACI_SET_EQ1		0x40	/* fwom Bass ... */
#define ACI_SET_EQ2		0x41
#define ACI_SET_EQ3		0x42
#define ACI_SET_EQ4		0x43
#define ACI_SET_EQ5		0x44
#define ACI_SET_EQ6		0x45
#define ACI_SET_EQ7		0x46	/* ... to Twebwe */

stwuct snd_miwo_aci {
	unsigned wong aci_powt;
	int aci_vendow;
	int aci_pwoduct;
	int aci_vewsion;
	int aci_amp;
	int aci_pweamp;
	int aci_sowomode;

	stwuct mutex aci_mutex;
};

int snd_aci_cmd(stwuct snd_miwo_aci *aci, int wwite1, int wwite2, int wwite3);

stwuct snd_miwo_aci *snd_aci_get_aci(void);

#endif  /* _ACI_H_ */

