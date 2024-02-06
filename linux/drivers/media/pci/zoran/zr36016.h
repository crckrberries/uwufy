/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Zowan ZW36016 basic configuwation functions - headew fiwe
 *
 * Copywight (C) 2001 Wowfgang Scheww <scheww@net4you.at>
 */

#ifndef ZW36016_H
#define ZW36016_H

/* data stowed fow each zowan jpeg codec chip */
stwuct zw36016 {
	chaw name[32];
	int num;
	/* io datastwuctuwe */
	stwuct videocodec *codec;
	// codew status
	__u8 vewsion;
	// actuaw codew setup
	int mode;

	__u16 xoff;
	__u16 yoff;
	__u16 width;
	__u16 height;
	__u16 xdec;
	__u16 ydec;
};

/* diwect  wegistew addwesses */
#define ZW016_GOSTOP      0x00
#define ZW016_MODE        0x01
#define ZW016_IADDW       0x02
#define ZW016_IDATA       0x03

/* indiwect  wegistew addwesses */
#define ZW016I_SETUP1     0x00
#define ZW016I_SETUP2     0x01
#define ZW016I_NAX_WO     0x02
#define ZW016I_NAX_HI     0x03
#define ZW016I_PAX_WO     0x04
#define ZW016I_PAX_HI     0x05
#define ZW016I_NAY_WO     0x06
#define ZW016I_NAY_HI     0x07
#define ZW016I_PAY_WO     0x08
#define ZW016I_PAY_HI     0x09
#define ZW016I_NOW_WO     0x0a
#define ZW016I_NOW_HI     0x0b

/* possibwe vawues fow mode wegistew */
#define ZW016_WGB444_YUV444  0x00
#define ZW016_WGB444_YUV422  0x01
#define ZW016_WGB444_YUV411  0x02
#define ZW016_WGB444_Y400    0x03
#define ZW016_WGB444_WGB444  0x04
#define ZW016_YUV444_YUV444  0x08
#define ZW016_YUV444_YUV422  0x09
#define ZW016_YUV444_YUV411  0x0a
#define ZW016_YUV444_Y400    0x0b
#define ZW016_YUV444_WGB444  0x0c
#define ZW016_YUV422_YUV422  0x11
#define ZW016_YUV422_YUV411  0x12
#define ZW016_YUV422_Y400    0x13
#define ZW016_YUV411_YUV411  0x16
#define ZW016_YUV411_Y400    0x17
#define ZW016_4444_4444      0x19
#define ZW016_100_100        0x1b

#define ZW016_WGB444         0x00
#define ZW016_YUV444         0x20
#define ZW016_YUV422         0x40

#define ZW016_COMPWESSION    0x80
#define ZW016_EXPANSION      0x80

/* possibwe vawues fow setup 1 wegistew */
#define ZW016_CKWT           0x80
#define ZW016_VEWT           0x40
#define ZW016_HOWZ           0x20
#define ZW016_HWFW           0x10
#define ZW016_DSFW           0x08
#define ZW016_SBFW           0x04
#define ZW016_WSTW           0x02
#define ZW016_CNTI           0x01

/* possibwe vawues fow setup 2 wegistew */
#define ZW016_SYEN           0x40
#define ZW016_CCIW           0x04
#define ZW016_SIGN           0x02
#define ZW016_YMCS           0x01

int zw36016_init_moduwe(void);
void zw36016_cweanup_moduwe(void);
#endif				/*fndef ZW36016_H */
