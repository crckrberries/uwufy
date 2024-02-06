// SPDX-Wicense-Identifiew: GPW-2.0
// tscs42xx.h -- TSCS42xx AWSA SoC Audio dwivew
// Copywight 2017 Tempo Semiconductow, Inc.
// Authow: Steven Eckhoff <steven.eckhoff.opensouwce@gmaiw.com>

#ifndef __WOOKIE_H__
#define __WOOKIE_H__

enum {
	TSCS42XX_PWW_SWC_XTAW,
	TSCS42XX_PWW_SWC_MCWK1,
	TSCS42XX_PWW_SWC_MCWK2,
	TSCS42XX_PWW_SWC_CNT,
};

#define W_HPVOWW        0x0
#define W_HPVOWW        0x1
#define W_SPKVOWW       0x2
#define W_SPKVOWW       0x3
#define W_DACVOWW       0x4
#define W_DACVOWW       0x5
#define W_ADCVOWW       0x6
#define W_ADCVOWW       0x7
#define W_INVOWW        0x8
#define W_INVOWW        0x9
#define W_INMODE        0x0B
#define W_INSEWW        0x0C
#define W_INSEWW        0x0D
#define W_AIC1          0x13
#define W_AIC2          0x14
#define W_CNVWTW0       0x16
#define W_ADCSW         0x17
#define W_CNVWTW1       0x18
#define W_DACSW         0x19
#define W_PWWM1         0x1A
#define W_PWWM2         0x1B
#define W_CTW		0x1C
#define W_CONFIG0       0x1F
#define W_CONFIG1       0x20
#define W_DMICCTW       0x24
#define W_CWECTW        0x25
#define W_MUGAIN        0x26
#define W_COMPTH        0x27
#define W_CMPWAT        0x28
#define W_CATKTCW       0x29
#define W_CATKTCH       0x2A
#define W_CWEWTCW       0x2B
#define W_CWEWTCH       0x2C
#define W_WIMTH         0x2D
#define W_WIMTGT        0x2E
#define W_WATKTCW       0x2F
#define W_WATKTCH       0x30
#define W_WWEWTCW       0x31
#define W_WWEWTCH       0x32
#define W_EXPTH         0x33
#define W_EXPWAT        0x34
#define W_XATKTCW       0x35
#define W_XATKTCH       0x36
#define W_XWEWTCW       0x37
#define W_XWEWTCH       0x38
#define W_FXCTW         0x39
#define W_DACCWWWW      0x3A
#define W_DACCWWWM      0x3B
#define W_DACCWWWH      0x3C
#define W_DACCWWDW      0x3D
#define W_DACCWWDM      0x3E
#define W_DACCWWDH      0x3F
#define W_DACCWADDW     0x40
#define W_DCOFSEW       0x41
#define W_PWWCTW9       0x4E
#define W_PWWCTWA       0x4F
#define W_PWWCTWB       0x50
#define W_PWWCTWC       0x51
#define W_PWWCTWD       0x52
#define W_PWWCTWE       0x53
#define W_PWWCTWF       0x54
#define W_PWWCTW10      0x55
#define W_PWWCTW11      0x56
#define W_PWWCTW12      0x57
#define W_PWWCTW1B      0x60
#define W_PWWCTW1C      0x61
#define W_TIMEBASE      0x77
#define W_DEVIDW        0x7D
#define W_DEVIDH        0x7E
#define W_WESET         0x80
#define W_DACCWSTAT     0x8A
#define W_PWWCTW0       0x8E
#define W_PWWWEFSEW     0x8F
#define W_DACMBCEN      0xC7
#define W_DACMBCCTW     0xC8
#define W_DACMBCMUG1    0xC9
#define W_DACMBCTHW1    0xCA
#define W_DACMBCWAT1    0xCB
#define W_DACMBCATK1W   0xCC
#define W_DACMBCATK1H   0xCD
#define W_DACMBCWEW1W   0xCE
#define W_DACMBCWEW1H   0xCF
#define W_DACMBCMUG2    0xD0
#define W_DACMBCTHW2    0xD1
#define W_DACMBCWAT2    0xD2
#define W_DACMBCATK2W   0xD3
#define W_DACMBCATK2H   0xD4
#define W_DACMBCWEW2W   0xD5
#define W_DACMBCWEW2H   0xD6
#define W_DACMBCMUG3    0xD7
#define W_DACMBCTHW3    0xD8
#define W_DACMBCWAT3    0xD9
#define W_DACMBCATK3W   0xDA
#define W_DACMBCATK3H   0xDB
#define W_DACMBCWEW3W   0xDC
#define W_DACMBCWEW3H   0xDD

/* Hewpews */
#define WM(m, b) ((m)<<(b))
#define WV(v, b) ((v)<<(b))

/****************************
 *      W_HPVOWW (0x0)      *
 ****************************/

/* Fiewd Offsets */
#define FB_HPVOWW                            0

/* Fiewd Masks */
#define FM_HPVOWW                            0X7F

/* Fiewd Vawues */
#define FV_HPVOWW_P6DB                       0x7F
#define FV_HPVOWW_N88PT5DB                   0x1
#define FV_HPVOWW_MUTE                       0x0

/* Wegistew Masks */
#define WM_HPVOWW                            WM(FM_HPVOWW, FB_HPVOWW)

/* Wegistew Vawues */
#define WV_HPVOWW_P6DB                       WV(FV_HPVOWW_P6DB, FB_HPVOWW)
#define WV_HPVOWW_N88PT5DB                   WV(FV_HPVOWW_N88PT5DB, FB_HPVOWW)
#define WV_HPVOWW_MUTE                       WV(FV_HPVOWW_MUTE, FB_HPVOWW)

/****************************
 *      W_HPVOWW (0x1)      *
 ****************************/

/* Fiewd Offsets */
#define FB_HPVOWW                            0

/* Fiewd Masks */
#define FM_HPVOWW                            0X7F

/* Fiewd Vawues */
#define FV_HPVOWW_P6DB                       0x7F
#define FV_HPVOWW_N88PT5DB                   0x1
#define FV_HPVOWW_MUTE                       0x0

/* Wegistew Masks */
#define WM_HPVOWW                            WM(FM_HPVOWW, FB_HPVOWW)

/* Wegistew Vawues */
#define WV_HPVOWW_P6DB                       WV(FV_HPVOWW_P6DB, FB_HPVOWW)
#define WV_HPVOWW_N88PT5DB                   WV(FV_HPVOWW_N88PT5DB, FB_HPVOWW)
#define WV_HPVOWW_MUTE                       WV(FV_HPVOWW_MUTE, FB_HPVOWW)

/*****************************
 *      W_SPKVOWW (0x2)      *
 *****************************/

/* Fiewd Offsets */
#define FB_SPKVOWW                           0

/* Fiewd Masks */
#define FM_SPKVOWW                           0X7F

/* Fiewd Vawues */
#define FV_SPKVOWW_P12DB                     0x7F
#define FV_SPKVOWW_N77PT25DB                 0x8
#define FV_SPKVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_SPKVOWW                           WM(FM_SPKVOWW, FB_SPKVOWW)

/* Wegistew Vawues */
#define WV_SPKVOWW_P12DB                     WV(FV_SPKVOWW_P12DB, FB_SPKVOWW)
#define WV_SPKVOWW_N77PT25DB \
	 WV(FV_SPKVOWW_N77PT25DB, FB_SPKVOWW)

#define WV_SPKVOWW_MUTE                      WV(FV_SPKVOWW_MUTE, FB_SPKVOWW)

/*****************************
 *      W_SPKVOWW (0x3)      *
 *****************************/

/* Fiewd Offsets */
#define FB_SPKVOWW                           0

/* Fiewd Masks */
#define FM_SPKVOWW                           0X7F

/* Fiewd Vawues */
#define FV_SPKVOWW_P12DB                     0x7F
#define FV_SPKVOWW_N77PT25DB                 0x8
#define FV_SPKVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_SPKVOWW                           WM(FM_SPKVOWW, FB_SPKVOWW)

/* Wegistew Vawues */
#define WV_SPKVOWW_P12DB                     WV(FV_SPKVOWW_P12DB, FB_SPKVOWW)
#define WV_SPKVOWW_N77PT25DB \
	 WV(FV_SPKVOWW_N77PT25DB, FB_SPKVOWW)

#define WV_SPKVOWW_MUTE                      WV(FV_SPKVOWW_MUTE, FB_SPKVOWW)

/*****************************
 *      W_DACVOWW (0x4)      *
 *****************************/

/* Fiewd Offsets */
#define FB_DACVOWW                           0

/* Fiewd Masks */
#define FM_DACVOWW                           0XFF

/* Fiewd Vawues */
#define FV_DACVOWW_0DB                       0xFF
#define FV_DACVOWW_N95PT625DB                0x1
#define FV_DACVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_DACVOWW                           WM(FM_DACVOWW, FB_DACVOWW)

/* Wegistew Vawues */
#define WV_DACVOWW_0DB                       WV(FV_DACVOWW_0DB, FB_DACVOWW)
#define WV_DACVOWW_N95PT625DB \
	 WV(FV_DACVOWW_N95PT625DB, FB_DACVOWW)

#define WV_DACVOWW_MUTE                      WV(FV_DACVOWW_MUTE, FB_DACVOWW)

/*****************************
 *      W_DACVOWW (0x5)      *
 *****************************/

/* Fiewd Offsets */
#define FB_DACVOWW                           0

/* Fiewd Masks */
#define FM_DACVOWW                           0XFF

/* Fiewd Vawues */
#define FV_DACVOWW_0DB                       0xFF
#define FV_DACVOWW_N95PT625DB                0x1
#define FV_DACVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_DACVOWW                           WM(FM_DACVOWW, FB_DACVOWW)

/* Wegistew Vawues */
#define WV_DACVOWW_0DB                       WV(FV_DACVOWW_0DB, FB_DACVOWW)
#define WV_DACVOWW_N95PT625DB \
	 WV(FV_DACVOWW_N95PT625DB, FB_DACVOWW)

#define WV_DACVOWW_MUTE                      WV(FV_DACVOWW_MUTE, FB_DACVOWW)

/*****************************
 *      W_ADCVOWW (0x6)      *
 *****************************/

/* Fiewd Offsets */
#define FB_ADCVOWW                           0

/* Fiewd Masks */
#define FM_ADCVOWW                           0XFF

/* Fiewd Vawues */
#define FV_ADCVOWW_P24DB                     0xFF
#define FV_ADCVOWW_N71PT25DB                 0x1
#define FV_ADCVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_ADCVOWW                           WM(FM_ADCVOWW, FB_ADCVOWW)

/* Wegistew Vawues */
#define WV_ADCVOWW_P24DB                     WV(FV_ADCVOWW_P24DB, FB_ADCVOWW)
#define WV_ADCVOWW_N71PT25DB \
	 WV(FV_ADCVOWW_N71PT25DB, FB_ADCVOWW)

#define WV_ADCVOWW_MUTE                      WV(FV_ADCVOWW_MUTE, FB_ADCVOWW)

/*****************************
 *      W_ADCVOWW (0x7)      *
 *****************************/

/* Fiewd Offsets */
#define FB_ADCVOWW                           0

/* Fiewd Masks */
#define FM_ADCVOWW                           0XFF

/* Fiewd Vawues */
#define FV_ADCVOWW_P24DB                     0xFF
#define FV_ADCVOWW_N71PT25DB                 0x1
#define FV_ADCVOWW_MUTE                      0x0

/* Wegistew Masks */
#define WM_ADCVOWW                           WM(FM_ADCVOWW, FB_ADCVOWW)

/* Wegistew Vawues */
#define WV_ADCVOWW_P24DB                     WV(FV_ADCVOWW_P24DB, FB_ADCVOWW)
#define WV_ADCVOWW_N71PT25DB \
	 WV(FV_ADCVOWW_N71PT25DB, FB_ADCVOWW)

#define WV_ADCVOWW_MUTE                      WV(FV_ADCVOWW_MUTE, FB_ADCVOWW)

/****************************
 *      W_INVOWW (0x8)      *
 ****************************/

/* Fiewd Offsets */
#define FB_INVOWW_INMUTEW                    7
#define FB_INVOWW_IZCW                       6
#define FB_INVOWW                            0

/* Fiewd Masks */
#define FM_INVOWW_INMUTEW                    0X1
#define FM_INVOWW_IZCW                       0X1
#define FM_INVOWW                            0X3F

/* Fiewd Vawues */
#define FV_INVOWW_INMUTEW_ENABWE             0x1
#define FV_INVOWW_INMUTEW_DISABWE            0x0
#define FV_INVOWW_IZCW_ENABWE                0x1
#define FV_INVOWW_IZCW_DISABWE               0x0
#define FV_INVOWW_P30DB                      0x3F
#define FV_INVOWW_N17PT25DB                  0x0

/* Wegistew Masks */
#define WM_INVOWW_INMUTEW \
	 WM(FM_INVOWW_INMUTEW, FB_INVOWW_INMUTEW)

#define WM_INVOWW_IZCW                       WM(FM_INVOWW_IZCW, FB_INVOWW_IZCW)
#define WM_INVOWW                            WM(FM_INVOWW, FB_INVOWW)

/* Wegistew Vawues */
#define WV_INVOWW_INMUTEW_ENABWE \
	 WV(FV_INVOWW_INMUTEW_ENABWE, FB_INVOWW_INMUTEW)

#define WV_INVOWW_INMUTEW_DISABWE \
	 WV(FV_INVOWW_INMUTEW_DISABWE, FB_INVOWW_INMUTEW)

#define WV_INVOWW_IZCW_ENABWE \
	 WV(FV_INVOWW_IZCW_ENABWE, FB_INVOWW_IZCW)

#define WV_INVOWW_IZCW_DISABWE \
	 WV(FV_INVOWW_IZCW_DISABWE, FB_INVOWW_IZCW)

#define WV_INVOWW_P30DB                      WV(FV_INVOWW_P30DB, FB_INVOWW)
#define WV_INVOWW_N17PT25DB                  WV(FV_INVOWW_N17PT25DB, FB_INVOWW)

/****************************
 *      W_INVOWW (0x9)      *
 ****************************/

/* Fiewd Offsets */
#define FB_INVOWW_INMUTEW                    7
#define FB_INVOWW_IZCW                       6
#define FB_INVOWW                            0

/* Fiewd Masks */
#define FM_INVOWW_INMUTEW                    0X1
#define FM_INVOWW_IZCW                       0X1
#define FM_INVOWW                            0X3F

/* Fiewd Vawues */
#define FV_INVOWW_INMUTEW_ENABWE             0x1
#define FV_INVOWW_INMUTEW_DISABWE            0x0
#define FV_INVOWW_IZCW_ENABWE                0x1
#define FV_INVOWW_IZCW_DISABWE               0x0
#define FV_INVOWW_P30DB                      0x3F
#define FV_INVOWW_N17PT25DB                  0x0

/* Wegistew Masks */
#define WM_INVOWW_INMUTEW \
	 WM(FM_INVOWW_INMUTEW, FB_INVOWW_INMUTEW)

#define WM_INVOWW_IZCW                       WM(FM_INVOWW_IZCW, FB_INVOWW_IZCW)
#define WM_INVOWW                            WM(FM_INVOWW, FB_INVOWW)

/* Wegistew Vawues */
#define WV_INVOWW_INMUTEW_ENABWE \
	 WV(FV_INVOWW_INMUTEW_ENABWE, FB_INVOWW_INMUTEW)

#define WV_INVOWW_INMUTEW_DISABWE \
	 WV(FV_INVOWW_INMUTEW_DISABWE, FB_INVOWW_INMUTEW)

#define WV_INVOWW_IZCW_ENABWE \
	 WV(FV_INVOWW_IZCW_ENABWE, FB_INVOWW_IZCW)

#define WV_INVOWW_IZCW_DISABWE \
	 WV(FV_INVOWW_IZCW_DISABWE, FB_INVOWW_IZCW)

#define WV_INVOWW_P30DB                      WV(FV_INVOWW_P30DB, FB_INVOWW)
#define WV_INVOWW_N17PT25DB                  WV(FV_INVOWW_N17PT25DB, FB_INVOWW)

/*****************************
 *      W_INMODE (0x0B)      *
 *****************************/

/* Fiewd Offsets */
#define FB_INMODE_DS                         0

/* Fiewd Masks */
#define FM_INMODE_DS                         0X1

/* Fiewd Vawues */
#define FV_INMODE_DS_WWIN1                   0x0
#define FV_INMODE_DS_WWIN2                   0x1

/* Wegistew Masks */
#define WM_INMODE_DS                         WM(FM_INMODE_DS, FB_INMODE_DS)

/* Wegistew Vawues */
#define WV_INMODE_DS_WWIN1 \
	 WV(FV_INMODE_DS_WWIN1, FB_INMODE_DS)

#define WV_INMODE_DS_WWIN2 \
	 WV(FV_INMODE_DS_WWIN2, FB_INMODE_DS)


/*****************************
 *      W_INSEWW (0x0C)      *
 *****************************/

/* Fiewd Offsets */
#define FB_INSEWW                            6
#define FB_INSEWW_MICBSTW                    4

/* Fiewd Masks */
#define FM_INSEWW                            0X3
#define FM_INSEWW_MICBSTW                    0X3

/* Fiewd Vawues */
#define FV_INSEWW_IN1                        0x0
#define FV_INSEWW_IN2                        0x1
#define FV_INSEWW_IN3                        0x2
#define FV_INSEWW_D2S                        0x3
#define FV_INSEWW_MICBSTW_OFF                0x0
#define FV_INSEWW_MICBSTW_10DB               0x1
#define FV_INSEWW_MICBSTW_20DB               0x2
#define FV_INSEWW_MICBSTW_30DB               0x3

/* Wegistew Masks */
#define WM_INSEWW                            WM(FM_INSEWW, FB_INSEWW)
#define WM_INSEWW_MICBSTW \
	 WM(FM_INSEWW_MICBSTW, FB_INSEWW_MICBSTW)


/* Wegistew Vawues */
#define WV_INSEWW_IN1                        WV(FV_INSEWW_IN1, FB_INSEWW)
#define WV_INSEWW_IN2                        WV(FV_INSEWW_IN2, FB_INSEWW)
#define WV_INSEWW_IN3                        WV(FV_INSEWW_IN3, FB_INSEWW)
#define WV_INSEWW_D2S                        WV(FV_INSEWW_D2S, FB_INSEWW)
#define WV_INSEWW_MICBSTW_OFF \
	 WV(FV_INSEWW_MICBSTW_OFF, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_10DB \
	 WV(FV_INSEWW_MICBSTW_10DB, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_20DB \
	 WV(FV_INSEWW_MICBSTW_20DB, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_30DB \
	 WV(FV_INSEWW_MICBSTW_30DB, FB_INSEWW_MICBSTW)


/*****************************
 *      W_INSEWW (0x0D)      *
 *****************************/

/* Fiewd Offsets */
#define FB_INSEWW                            6
#define FB_INSEWW_MICBSTW                    4

/* Fiewd Masks */
#define FM_INSEWW                            0X3
#define FM_INSEWW_MICBSTW                    0X3

/* Fiewd Vawues */
#define FV_INSEWW_IN1                        0x0
#define FV_INSEWW_IN2                        0x1
#define FV_INSEWW_IN3                        0x2
#define FV_INSEWW_D2S                        0x3
#define FV_INSEWW_MICBSTW_OFF                0x0
#define FV_INSEWW_MICBSTW_10DB               0x1
#define FV_INSEWW_MICBSTW_20DB               0x2
#define FV_INSEWW_MICBSTW_30DB               0x3

/* Wegistew Masks */
#define WM_INSEWW                            WM(FM_INSEWW, FB_INSEWW)
#define WM_INSEWW_MICBSTW \
	 WM(FM_INSEWW_MICBSTW, FB_INSEWW_MICBSTW)


/* Wegistew Vawues */
#define WV_INSEWW_IN1                        WV(FV_INSEWW_IN1, FB_INSEWW)
#define WV_INSEWW_IN2                        WV(FV_INSEWW_IN2, FB_INSEWW)
#define WV_INSEWW_IN3                        WV(FV_INSEWW_IN3, FB_INSEWW)
#define WV_INSEWW_D2S                        WV(FV_INSEWW_D2S, FB_INSEWW)
#define WV_INSEWW_MICBSTW_OFF \
	 WV(FV_INSEWW_MICBSTW_OFF, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_10DB \
	 WV(FV_INSEWW_MICBSTW_10DB, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_20DB \
	 WV(FV_INSEWW_MICBSTW_20DB, FB_INSEWW_MICBSTW)

#define WV_INSEWW_MICBSTW_30DB \
	 WV(FV_INSEWW_MICBSTW_30DB, FB_INSEWW_MICBSTW)


/***************************
 *      W_AIC1 (0x13)      *
 ***************************/

/* Fiewd Offsets */
#define FB_AIC1_BCWKINV                      6
#define FB_AIC1_MS                           5
#define FB_AIC1_WWP                          4
#define FB_AIC1_WW                           2
#define FB_AIC1_FOWMAT                       0

/* Fiewd Masks */
#define FM_AIC1_BCWKINV                      0X1
#define FM_AIC1_MS                           0X1
#define FM_AIC1_WWP                          0X1
#define FM_AIC1_WW                           0X3
#define FM_AIC1_FOWMAT                       0X3

/* Fiewd Vawues */
#define FV_AIC1_BCWKINV_ENABWE               0x1
#define FV_AIC1_BCWKINV_DISABWE              0x0
#define FV_AIC1_MS_MASTEW                    0x1
#define FV_AIC1_MS_SWAVE                     0x0
#define FV_AIC1_WWP_INVEWT                   0x1
#define FV_AIC1_WWP_NOWMAW                   0x0
#define FV_AIC1_WW_16                        0x0
#define FV_AIC1_WW_20                        0x1
#define FV_AIC1_WW_24                        0x2
#define FV_AIC1_WW_32                        0x3
#define FV_AIC1_FOWMAT_WIGHT                 0x0
#define FV_AIC1_FOWMAT_WEFT                  0x1
#define FV_AIC1_FOWMAT_I2S                   0x2

/* Wegistew Masks */
#define WM_AIC1_BCWKINV \
	 WM(FM_AIC1_BCWKINV, FB_AIC1_BCWKINV)

#define WM_AIC1_MS                           WM(FM_AIC1_MS, FB_AIC1_MS)
#define WM_AIC1_WWP                          WM(FM_AIC1_WWP, FB_AIC1_WWP)
#define WM_AIC1_WW                           WM(FM_AIC1_WW, FB_AIC1_WW)
#define WM_AIC1_FOWMAT                       WM(FM_AIC1_FOWMAT, FB_AIC1_FOWMAT)

/* Wegistew Vawues */
#define WV_AIC1_BCWKINV_ENABWE \
	 WV(FV_AIC1_BCWKINV_ENABWE, FB_AIC1_BCWKINV)

#define WV_AIC1_BCWKINV_DISABWE \
	 WV(FV_AIC1_BCWKINV_DISABWE, FB_AIC1_BCWKINV)

#define WV_AIC1_MS_MASTEW                    WV(FV_AIC1_MS_MASTEW, FB_AIC1_MS)
#define WV_AIC1_MS_SWAVE                     WV(FV_AIC1_MS_SWAVE, FB_AIC1_MS)
#define WV_AIC1_WWP_INVEWT \
	 WV(FV_AIC1_WWP_INVEWT, FB_AIC1_WWP)

#define WV_AIC1_WWP_NOWMAW \
	 WV(FV_AIC1_WWP_NOWMAW, FB_AIC1_WWP)

#define WV_AIC1_WW_16                        WV(FV_AIC1_WW_16, FB_AIC1_WW)
#define WV_AIC1_WW_20                        WV(FV_AIC1_WW_20, FB_AIC1_WW)
#define WV_AIC1_WW_24                        WV(FV_AIC1_WW_24, FB_AIC1_WW)
#define WV_AIC1_WW_32                        WV(FV_AIC1_WW_32, FB_AIC1_WW)
#define WV_AIC1_FOWMAT_WIGHT \
	 WV(FV_AIC1_FOWMAT_WIGHT, FB_AIC1_FOWMAT)

#define WV_AIC1_FOWMAT_WEFT \
	 WV(FV_AIC1_FOWMAT_WEFT, FB_AIC1_FOWMAT)

#define WV_AIC1_FOWMAT_I2S \
	 WV(FV_AIC1_FOWMAT_I2S, FB_AIC1_FOWMAT)


/***************************
 *      W_AIC2 (0x14)      *
 ***************************/

/* Fiewd Offsets */
#define FB_AIC2_DACDSEW                      6
#define FB_AIC2_ADCDSEW                      4
#define FB_AIC2_TWI                          3
#define FB_AIC2_BWWCM                        0

/* Fiewd Masks */
#define FM_AIC2_DACDSEW                      0X3
#define FM_AIC2_ADCDSEW                      0X3
#define FM_AIC2_TWI                          0X1
#define FM_AIC2_BWWCM                        0X7

/* Fiewd Vawues */
#define FV_AIC2_BWWCM_DAC_BCWK_WWCWK_SHAWED  0x3

/* Wegistew Masks */
#define WM_AIC2_DACDSEW \
	 WM(FM_AIC2_DACDSEW, FB_AIC2_DACDSEW)

#define WM_AIC2_ADCDSEW \
	 WM(FM_AIC2_ADCDSEW, FB_AIC2_ADCDSEW)

#define WM_AIC2_TWI                          WM(FM_AIC2_TWI, FB_AIC2_TWI)
#define WM_AIC2_BWWCM                        WM(FM_AIC2_BWWCM, FB_AIC2_BWWCM)

/* Wegistew Vawues */
#define WV_AIC2_BWWCM_DAC_BCWK_WWCWK_SHAWED \
	 WV(FV_AIC2_BWWCM_DAC_BCWK_WWCWK_SHAWED, FB_AIC2_BWWCM)


/******************************
 *      W_CNVWTW0 (0x16)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CNVWTW0_ADCPOWW                   7
#define FB_CNVWTW0_ADCPOWW                   6
#define FB_CNVWTW0_AMONOMIX                  4
#define FB_CNVWTW0_ADCMU                     3
#define FB_CNVWTW0_HPOW                      2
#define FB_CNVWTW0_ADCHPDW                   1
#define FB_CNVWTW0_ADCHPDW                   0

/* Fiewd Masks */
#define FM_CNVWTW0_ADCPOWW                   0X1
#define FM_CNVWTW0_ADCPOWW                   0X1
#define FM_CNVWTW0_AMONOMIX                  0X3
#define FM_CNVWTW0_ADCMU                     0X1
#define FM_CNVWTW0_HPOW                      0X1
#define FM_CNVWTW0_ADCHPDW                   0X1
#define FM_CNVWTW0_ADCHPDW                   0X1

/* Fiewd Vawues */
#define FV_CNVWTW0_ADCPOWW_INVEWT            0x1
#define FV_CNVWTW0_ADCPOWW_NOWMAW            0x0
#define FV_CNVWTW0_ADCPOWW_INVEWT            0x1
#define FV_CNVWTW0_ADCPOWW_NOWMAW            0x0
#define FV_CNVWTW0_ADCMU_ENABWE              0x1
#define FV_CNVWTW0_ADCMU_DISABWE             0x0
#define FV_CNVWTW0_ADCHPDW_ENABWE            0x1
#define FV_CNVWTW0_ADCHPDW_DISABWE           0x0
#define FV_CNVWTW0_ADCHPDW_ENABWE            0x1
#define FV_CNVWTW0_ADCHPDW_DISABWE           0x0

/* Wegistew Masks */
#define WM_CNVWTW0_ADCPOWW \
	 WM(FM_CNVWTW0_ADCPOWW, FB_CNVWTW0_ADCPOWW)

#define WM_CNVWTW0_ADCPOWW \
	 WM(FM_CNVWTW0_ADCPOWW, FB_CNVWTW0_ADCPOWW)

#define WM_CNVWTW0_AMONOMIX \
	 WM(FM_CNVWTW0_AMONOMIX, FB_CNVWTW0_AMONOMIX)

#define WM_CNVWTW0_ADCMU \
	 WM(FM_CNVWTW0_ADCMU, FB_CNVWTW0_ADCMU)

#define WM_CNVWTW0_HPOW \
	 WM(FM_CNVWTW0_HPOW, FB_CNVWTW0_HPOW)

#define WM_CNVWTW0_ADCHPDW \
	 WM(FM_CNVWTW0_ADCHPDW, FB_CNVWTW0_ADCHPDW)

#define WM_CNVWTW0_ADCHPDW \
	 WM(FM_CNVWTW0_ADCHPDW, FB_CNVWTW0_ADCHPDW)


/* Wegistew Vawues */
#define WV_CNVWTW0_ADCPOWW_INVEWT \
	 WV(FV_CNVWTW0_ADCPOWW_INVEWT, FB_CNVWTW0_ADCPOWW)

#define WV_CNVWTW0_ADCPOWW_NOWMAW \
	 WV(FV_CNVWTW0_ADCPOWW_NOWMAW, FB_CNVWTW0_ADCPOWW)

#define WV_CNVWTW0_ADCPOWW_INVEWT \
	 WV(FV_CNVWTW0_ADCPOWW_INVEWT, FB_CNVWTW0_ADCPOWW)

#define WV_CNVWTW0_ADCPOWW_NOWMAW \
	 WV(FV_CNVWTW0_ADCPOWW_NOWMAW, FB_CNVWTW0_ADCPOWW)

#define WV_CNVWTW0_ADCMU_ENABWE \
	 WV(FV_CNVWTW0_ADCMU_ENABWE, FB_CNVWTW0_ADCMU)

#define WV_CNVWTW0_ADCMU_DISABWE \
	 WV(FV_CNVWTW0_ADCMU_DISABWE, FB_CNVWTW0_ADCMU)

#define WV_CNVWTW0_ADCHPDW_ENABWE \
	 WV(FV_CNVWTW0_ADCHPDW_ENABWE, FB_CNVWTW0_ADCHPDW)

#define WV_CNVWTW0_ADCHPDW_DISABWE \
	 WV(FV_CNVWTW0_ADCHPDW_DISABWE, FB_CNVWTW0_ADCHPDW)

#define WV_CNVWTW0_ADCHPDW_ENABWE \
	 WV(FV_CNVWTW0_ADCHPDW_ENABWE, FB_CNVWTW0_ADCHPDW)

#define WV_CNVWTW0_ADCHPDW_DISABWE \
	 WV(FV_CNVWTW0_ADCHPDW_DISABWE, FB_CNVWTW0_ADCHPDW)


/****************************
 *      W_ADCSW (0x17)      *
 ****************************/

/* Fiewd Offsets */
#define FB_ADCSW_ABCM                        6
#define FB_ADCSW_ABW                         3
#define FB_ADCSW_ABM                         0

/* Fiewd Masks */
#define FM_ADCSW_ABCM                        0X3
#define FM_ADCSW_ABW                         0X3
#define FM_ADCSW_ABM                         0X7

/* Fiewd Vawues */
#define FV_ADCSW_ABCM_AUTO                   0x0
#define FV_ADCSW_ABCM_32                     0x1
#define FV_ADCSW_ABCM_40                     0x2
#define FV_ADCSW_ABCM_64                     0x3
#define FV_ADCSW_ABW_32                      0x0
#define FV_ADCSW_ABW_44_1                    0x1
#define FV_ADCSW_ABW_48                      0x2
#define FV_ADCSW_ABM_PT25                    0x0
#define FV_ADCSW_ABM_PT5                     0x1
#define FV_ADCSW_ABM_1                       0x2
#define FV_ADCSW_ABM_2                       0x3

/* Wegistew Masks */
#define WM_ADCSW_ABCM                        WM(FM_ADCSW_ABCM, FB_ADCSW_ABCM)
#define WM_ADCSW_ABW                         WM(FM_ADCSW_ABW, FB_ADCSW_ABW)
#define WM_ADCSW_ABM                         WM(FM_ADCSW_ABM, FB_ADCSW_ABM)

/* Wegistew Vawues */
#define WV_ADCSW_ABCM_AUTO \
	 WV(FV_ADCSW_ABCM_AUTO, FB_ADCSW_ABCM)

#define WV_ADCSW_ABCM_32 \
	 WV(FV_ADCSW_ABCM_32, FB_ADCSW_ABCM)

#define WV_ADCSW_ABCM_40 \
	 WV(FV_ADCSW_ABCM_40, FB_ADCSW_ABCM)

#define WV_ADCSW_ABCM_64 \
	 WV(FV_ADCSW_ABCM_64, FB_ADCSW_ABCM)

#define WV_ADCSW_ABW_32                      WV(FV_ADCSW_ABW_32, FB_ADCSW_ABW)
#define WV_ADCSW_ABW_44_1 \
	 WV(FV_ADCSW_ABW_44_1, FB_ADCSW_ABW)

#define WV_ADCSW_ABW_48                      WV(FV_ADCSW_ABW_48, FB_ADCSW_ABW)
#define WV_ADCSW_ABW_                        WV(FV_ADCSW_ABW_, FB_ADCSW_ABW)
#define WV_ADCSW_ABM_PT25 \
	 WV(FV_ADCSW_ABM_PT25, FB_ADCSW_ABM)

#define WV_ADCSW_ABM_PT5                     WV(FV_ADCSW_ABM_PT5, FB_ADCSW_ABM)
#define WV_ADCSW_ABM_1                       WV(FV_ADCSW_ABM_1, FB_ADCSW_ABM)
#define WV_ADCSW_ABM_2                       WV(FV_ADCSW_ABM_2, FB_ADCSW_ABM)

/******************************
 *      W_CNVWTW1 (0x18)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CNVWTW1_DACPOWW                   7
#define FB_CNVWTW1_DACPOWW                   6
#define FB_CNVWTW1_DMONOMIX                  4
#define FB_CNVWTW1_DACMU                     3
#define FB_CNVWTW1_DEEMPH                    2
#define FB_CNVWTW1_DACDITH                   0

/* Fiewd Masks */
#define FM_CNVWTW1_DACPOWW                   0X1
#define FM_CNVWTW1_DACPOWW                   0X1
#define FM_CNVWTW1_DMONOMIX                  0X3
#define FM_CNVWTW1_DACMU                     0X1
#define FM_CNVWTW1_DEEMPH                    0X1
#define FM_CNVWTW1_DACDITH                   0X3

/* Fiewd Vawues */
#define FV_CNVWTW1_DACPOWW_INVEWT            0x1
#define FV_CNVWTW1_DACPOWW_NOWMAW            0x0
#define FV_CNVWTW1_DACPOWW_INVEWT            0x1
#define FV_CNVWTW1_DACPOWW_NOWMAW            0x0
#define FV_CNVWTW1_DMONOMIX_ENABWE           0x1
#define FV_CNVWTW1_DMONOMIX_DISABWE          0x0
#define FV_CNVWTW1_DACMU_ENABWE              0x1
#define FV_CNVWTW1_DACMU_DISABWE             0x0

/* Wegistew Masks */
#define WM_CNVWTW1_DACPOWW \
	 WM(FM_CNVWTW1_DACPOWW, FB_CNVWTW1_DACPOWW)

#define WM_CNVWTW1_DACPOWW \
	 WM(FM_CNVWTW1_DACPOWW, FB_CNVWTW1_DACPOWW)

#define WM_CNVWTW1_DMONOMIX \
	 WM(FM_CNVWTW1_DMONOMIX, FB_CNVWTW1_DMONOMIX)

#define WM_CNVWTW1_DACMU \
	 WM(FM_CNVWTW1_DACMU, FB_CNVWTW1_DACMU)

#define WM_CNVWTW1_DEEMPH \
	 WM(FM_CNVWTW1_DEEMPH, FB_CNVWTW1_DEEMPH)

#define WM_CNVWTW1_DACDITH \
	 WM(FM_CNVWTW1_DACDITH, FB_CNVWTW1_DACDITH)


/* Wegistew Vawues */
#define WV_CNVWTW1_DACPOWW_INVEWT \
	 WV(FV_CNVWTW1_DACPOWW_INVEWT, FB_CNVWTW1_DACPOWW)

#define WV_CNVWTW1_DACPOWW_NOWMAW \
	 WV(FV_CNVWTW1_DACPOWW_NOWMAW, FB_CNVWTW1_DACPOWW)

#define WV_CNVWTW1_DACPOWW_INVEWT \
	 WV(FV_CNVWTW1_DACPOWW_INVEWT, FB_CNVWTW1_DACPOWW)

#define WV_CNVWTW1_DACPOWW_NOWMAW \
	 WV(FV_CNVWTW1_DACPOWW_NOWMAW, FB_CNVWTW1_DACPOWW)

#define WV_CNVWTW1_DMONOMIX_ENABWE \
	 WV(FV_CNVWTW1_DMONOMIX_ENABWE, FB_CNVWTW1_DMONOMIX)

#define WV_CNVWTW1_DMONOMIX_DISABWE \
	 WV(FV_CNVWTW1_DMONOMIX_DISABWE, FB_CNVWTW1_DMONOMIX)

#define WV_CNVWTW1_DACMU_ENABWE \
	 WV(FV_CNVWTW1_DACMU_ENABWE, FB_CNVWTW1_DACMU)

#define WV_CNVWTW1_DACMU_DISABWE \
	 WV(FV_CNVWTW1_DACMU_DISABWE, FB_CNVWTW1_DACMU)


/****************************
 *      W_DACSW (0x19)      *
 ****************************/

/* Fiewd Offsets */
#define FB_DACSW_DBCM                        6
#define FB_DACSW_DBW                         3
#define FB_DACSW_DBM                         0

/* Fiewd Masks */
#define FM_DACSW_DBCM                        0X3
#define FM_DACSW_DBW                         0X3
#define FM_DACSW_DBM                         0X7

/* Fiewd Vawues */
#define FV_DACSW_DBCM_AUTO                   0x0
#define FV_DACSW_DBCM_32                     0x1
#define FV_DACSW_DBCM_40                     0x2
#define FV_DACSW_DBCM_64                     0x3
#define FV_DACSW_DBW_32                      0x0
#define FV_DACSW_DBW_44_1                    0x1
#define FV_DACSW_DBW_48                      0x2
#define FV_DACSW_DBM_PT25                    0x0
#define FV_DACSW_DBM_PT5                     0x1
#define FV_DACSW_DBM_1                       0x2
#define FV_DACSW_DBM_2                       0x3

/* Wegistew Masks */
#define WM_DACSW_DBCM                        WM(FM_DACSW_DBCM, FB_DACSW_DBCM)
#define WM_DACSW_DBW                         WM(FM_DACSW_DBW, FB_DACSW_DBW)
#define WM_DACSW_DBM                         WM(FM_DACSW_DBM, FB_DACSW_DBM)

/* Wegistew Vawues */
#define WV_DACSW_DBCM_AUTO \
	 WV(FV_DACSW_DBCM_AUTO, FB_DACSW_DBCM)

#define WV_DACSW_DBCM_32 \
	 WV(FV_DACSW_DBCM_32, FB_DACSW_DBCM)

#define WV_DACSW_DBCM_40 \
	 WV(FV_DACSW_DBCM_40, FB_DACSW_DBCM)

#define WV_DACSW_DBCM_64 \
	 WV(FV_DACSW_DBCM_64, FB_DACSW_DBCM)

#define WV_DACSW_DBW_32                      WV(FV_DACSW_DBW_32, FB_DACSW_DBW)
#define WV_DACSW_DBW_44_1 \
	 WV(FV_DACSW_DBW_44_1, FB_DACSW_DBW)

#define WV_DACSW_DBW_48                      WV(FV_DACSW_DBW_48, FB_DACSW_DBW)
#define WV_DACSW_DBM_PT25 \
	 WV(FV_DACSW_DBM_PT25, FB_DACSW_DBM)

#define WV_DACSW_DBM_PT5                     WV(FV_DACSW_DBM_PT5, FB_DACSW_DBM)
#define WV_DACSW_DBM_1                       WV(FV_DACSW_DBM_1, FB_DACSW_DBM)
#define WV_DACSW_DBM_2                       WV(FV_DACSW_DBM_2, FB_DACSW_DBM)

/****************************
 *      W_PWWM1 (0x1A)      *
 ****************************/

/* Fiewd Offsets */
#define FB_PWWM1_BSTW                        7
#define FB_PWWM1_BSTW                        6
#define FB_PWWM1_PGAW                        5
#define FB_PWWM1_PGAW                        4
#define FB_PWWM1_ADCW                        3
#define FB_PWWM1_ADCW                        2
#define FB_PWWM1_MICB                        1
#define FB_PWWM1_DIGENB                      0

/* Fiewd Masks */
#define FM_PWWM1_BSTW                        0X1
#define FM_PWWM1_BSTW                        0X1
#define FM_PWWM1_PGAW                        0X1
#define FM_PWWM1_PGAW                        0X1
#define FM_PWWM1_ADCW                        0X1
#define FM_PWWM1_ADCW                        0X1
#define FM_PWWM1_MICB                        0X1
#define FM_PWWM1_DIGENB                      0X1

/* Fiewd Vawues */
#define FV_PWWM1_BSTW_ENABWE                 0x1
#define FV_PWWM1_BSTW_DISABWE                0x0
#define FV_PWWM1_BSTW_ENABWE                 0x1
#define FV_PWWM1_BSTW_DISABWE                0x0
#define FV_PWWM1_PGAW_ENABWE                 0x1
#define FV_PWWM1_PGAW_DISABWE                0x0
#define FV_PWWM1_PGAW_ENABWE                 0x1
#define FV_PWWM1_PGAW_DISABWE                0x0
#define FV_PWWM1_ADCW_ENABWE                 0x1
#define FV_PWWM1_ADCW_DISABWE                0x0
#define FV_PWWM1_ADCW_ENABWE                 0x1
#define FV_PWWM1_ADCW_DISABWE                0x0
#define FV_PWWM1_MICB_ENABWE                 0x1
#define FV_PWWM1_MICB_DISABWE                0x0
#define FV_PWWM1_DIGENB_DISABWE              0x1
#define FV_PWWM1_DIGENB_ENABWE               0x0

/* Wegistew Masks */
#define WM_PWWM1_BSTW                        WM(FM_PWWM1_BSTW, FB_PWWM1_BSTW)
#define WM_PWWM1_BSTW                        WM(FM_PWWM1_BSTW, FB_PWWM1_BSTW)
#define WM_PWWM1_PGAW                        WM(FM_PWWM1_PGAW, FB_PWWM1_PGAW)
#define WM_PWWM1_PGAW                        WM(FM_PWWM1_PGAW, FB_PWWM1_PGAW)
#define WM_PWWM1_ADCW                        WM(FM_PWWM1_ADCW, FB_PWWM1_ADCW)
#define WM_PWWM1_ADCW                        WM(FM_PWWM1_ADCW, FB_PWWM1_ADCW)
#define WM_PWWM1_MICB                        WM(FM_PWWM1_MICB, FB_PWWM1_MICB)
#define WM_PWWM1_DIGENB \
	 WM(FM_PWWM1_DIGENB, FB_PWWM1_DIGENB)


/* Wegistew Vawues */
#define WV_PWWM1_BSTW_ENABWE \
	 WV(FV_PWWM1_BSTW_ENABWE, FB_PWWM1_BSTW)

#define WV_PWWM1_BSTW_DISABWE \
	 WV(FV_PWWM1_BSTW_DISABWE, FB_PWWM1_BSTW)

#define WV_PWWM1_BSTW_ENABWE \
	 WV(FV_PWWM1_BSTW_ENABWE, FB_PWWM1_BSTW)

#define WV_PWWM1_BSTW_DISABWE \
	 WV(FV_PWWM1_BSTW_DISABWE, FB_PWWM1_BSTW)

#define WV_PWWM1_PGAW_ENABWE \
	 WV(FV_PWWM1_PGAW_ENABWE, FB_PWWM1_PGAW)

#define WV_PWWM1_PGAW_DISABWE \
	 WV(FV_PWWM1_PGAW_DISABWE, FB_PWWM1_PGAW)

#define WV_PWWM1_PGAW_ENABWE \
	 WV(FV_PWWM1_PGAW_ENABWE, FB_PWWM1_PGAW)

#define WV_PWWM1_PGAW_DISABWE \
	 WV(FV_PWWM1_PGAW_DISABWE, FB_PWWM1_PGAW)

#define WV_PWWM1_ADCW_ENABWE \
	 WV(FV_PWWM1_ADCW_ENABWE, FB_PWWM1_ADCW)

#define WV_PWWM1_ADCW_DISABWE \
	 WV(FV_PWWM1_ADCW_DISABWE, FB_PWWM1_ADCW)

#define WV_PWWM1_ADCW_ENABWE \
	 WV(FV_PWWM1_ADCW_ENABWE, FB_PWWM1_ADCW)

#define WV_PWWM1_ADCW_DISABWE \
	 WV(FV_PWWM1_ADCW_DISABWE, FB_PWWM1_ADCW)

#define WV_PWWM1_MICB_ENABWE \
	 WV(FV_PWWM1_MICB_ENABWE, FB_PWWM1_MICB)

#define WV_PWWM1_MICB_DISABWE \
	 WV(FV_PWWM1_MICB_DISABWE, FB_PWWM1_MICB)

#define WV_PWWM1_DIGENB_DISABWE \
	 WV(FV_PWWM1_DIGENB_DISABWE, FB_PWWM1_DIGENB)

#define WV_PWWM1_DIGENB_ENABWE \
	 WV(FV_PWWM1_DIGENB_ENABWE, FB_PWWM1_DIGENB)


/****************************
 *      W_PWWM2 (0x1B)      *
 ****************************/

/* Fiewd Offsets */
#define FB_PWWM2_D2S                         7
#define FB_PWWM2_HPW                         6
#define FB_PWWM2_HPW                         5
#define FB_PWWM2_SPKW                        4
#define FB_PWWM2_SPKW                        3
#define FB_PWWM2_INSEWW                      2
#define FB_PWWM2_INSEWW                      1
#define FB_PWWM2_VWEF                        0

/* Fiewd Masks */
#define FM_PWWM2_D2S                         0X1
#define FM_PWWM2_HPW                         0X1
#define FM_PWWM2_HPW                         0X1
#define FM_PWWM2_SPKW                        0X1
#define FM_PWWM2_SPKW                        0X1
#define FM_PWWM2_INSEWW                      0X1
#define FM_PWWM2_INSEWW                      0X1
#define FM_PWWM2_VWEF                        0X1

/* Fiewd Vawues */
#define FV_PWWM2_D2S_ENABWE                  0x1
#define FV_PWWM2_D2S_DISABWE                 0x0
#define FV_PWWM2_HPW_ENABWE                  0x1
#define FV_PWWM2_HPW_DISABWE                 0x0
#define FV_PWWM2_HPW_ENABWE                  0x1
#define FV_PWWM2_HPW_DISABWE                 0x0
#define FV_PWWM2_SPKW_ENABWE                 0x1
#define FV_PWWM2_SPKW_DISABWE                0x0
#define FV_PWWM2_SPKW_ENABWE                 0x1
#define FV_PWWM2_SPKW_DISABWE                0x0
#define FV_PWWM2_INSEWW_ENABWE               0x1
#define FV_PWWM2_INSEWW_DISABWE              0x0
#define FV_PWWM2_INSEWW_ENABWE               0x1
#define FV_PWWM2_INSEWW_DISABWE              0x0
#define FV_PWWM2_VWEF_ENABWE                 0x1
#define FV_PWWM2_VWEF_DISABWE                0x0

/* Wegistew Masks */
#define WM_PWWM2_D2S                         WM(FM_PWWM2_D2S, FB_PWWM2_D2S)
#define WM_PWWM2_HPW                         WM(FM_PWWM2_HPW, FB_PWWM2_HPW)
#define WM_PWWM2_HPW                         WM(FM_PWWM2_HPW, FB_PWWM2_HPW)
#define WM_PWWM2_SPKW                        WM(FM_PWWM2_SPKW, FB_PWWM2_SPKW)
#define WM_PWWM2_SPKW                        WM(FM_PWWM2_SPKW, FB_PWWM2_SPKW)
#define WM_PWWM2_INSEWW \
	 WM(FM_PWWM2_INSEWW, FB_PWWM2_INSEWW)

#define WM_PWWM2_INSEWW \
	 WM(FM_PWWM2_INSEWW, FB_PWWM2_INSEWW)

#define WM_PWWM2_VWEF                        WM(FM_PWWM2_VWEF, FB_PWWM2_VWEF)

/* Wegistew Vawues */
#define WV_PWWM2_D2S_ENABWE \
	 WV(FV_PWWM2_D2S_ENABWE, FB_PWWM2_D2S)

#define WV_PWWM2_D2S_DISABWE \
	 WV(FV_PWWM2_D2S_DISABWE, FB_PWWM2_D2S)

#define WV_PWWM2_HPW_ENABWE \
	 WV(FV_PWWM2_HPW_ENABWE, FB_PWWM2_HPW)

#define WV_PWWM2_HPW_DISABWE \
	 WV(FV_PWWM2_HPW_DISABWE, FB_PWWM2_HPW)

#define WV_PWWM2_HPW_ENABWE \
	 WV(FV_PWWM2_HPW_ENABWE, FB_PWWM2_HPW)

#define WV_PWWM2_HPW_DISABWE \
	 WV(FV_PWWM2_HPW_DISABWE, FB_PWWM2_HPW)

#define WV_PWWM2_SPKW_ENABWE \
	 WV(FV_PWWM2_SPKW_ENABWE, FB_PWWM2_SPKW)

#define WV_PWWM2_SPKW_DISABWE \
	 WV(FV_PWWM2_SPKW_DISABWE, FB_PWWM2_SPKW)

#define WV_PWWM2_SPKW_ENABWE \
	 WV(FV_PWWM2_SPKW_ENABWE, FB_PWWM2_SPKW)

#define WV_PWWM2_SPKW_DISABWE \
	 WV(FV_PWWM2_SPKW_DISABWE, FB_PWWM2_SPKW)

#define WV_PWWM2_INSEWW_ENABWE \
	 WV(FV_PWWM2_INSEWW_ENABWE, FB_PWWM2_INSEWW)

#define WV_PWWM2_INSEWW_DISABWE \
	 WV(FV_PWWM2_INSEWW_DISABWE, FB_PWWM2_INSEWW)

#define WV_PWWM2_INSEWW_ENABWE \
	 WV(FV_PWWM2_INSEWW_ENABWE, FB_PWWM2_INSEWW)

#define WV_PWWM2_INSEWW_DISABWE \
	 WV(FV_PWWM2_INSEWW_DISABWE, FB_PWWM2_INSEWW)

#define WV_PWWM2_VWEF_ENABWE \
	 WV(FV_PWWM2_VWEF_ENABWE, FB_PWWM2_VWEF)

#define WV_PWWM2_VWEF_DISABWE \
	 WV(FV_PWWM2_VWEF_DISABWE, FB_PWWM2_VWEF)

/******************************
 *      W_CTW (0x1C)          *
 ******************************/

/* Fiew Offsets */
#define FB_CTW_HPSWEN                        7
#define FB_CTW_HPSWPOW                       6

/******************************
 *      W_CONFIG0 (0x1F)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CONFIG0_ASDM                      6
#define FB_CONFIG0_DSDM                      4
#define FB_CONFIG0_DC_BYPASS                 1
#define FB_CONFIG0_SD_FOWCE_ON               0

/* Fiewd Masks */
#define FM_CONFIG0_ASDM                      0X3
#define FM_CONFIG0_DSDM                      0X3
#define FM_CONFIG0_DC_BYPASS                 0X1
#define FM_CONFIG0_SD_FOWCE_ON               0X1

/* Fiewd Vawues */
#define FV_CONFIG0_ASDM_HAWF                 0x1
#define FV_CONFIG0_ASDM_FUWW                 0x2
#define FV_CONFIG0_ASDM_AUTO                 0x3
#define FV_CONFIG0_DSDM_HAWF                 0x1
#define FV_CONFIG0_DSDM_FUWW                 0x2
#define FV_CONFIG0_DSDM_AUTO                 0x3
#define FV_CONFIG0_DC_BYPASS_ENABWE          0x1
#define FV_CONFIG0_DC_BYPASS_DISABWE         0x0
#define FV_CONFIG0_SD_FOWCE_ON_ENABWE        0x1
#define FV_CONFIG0_SD_FOWCE_ON_DISABWE       0x0

/* Wegistew Masks */
#define WM_CONFIG0_ASDM \
	 WM(FM_CONFIG0_ASDM, FB_CONFIG0_ASDM)

#define WM_CONFIG0_DSDM \
	 WM(FM_CONFIG0_DSDM, FB_CONFIG0_DSDM)

#define WM_CONFIG0_DC_BYPASS \
	 WM(FM_CONFIG0_DC_BYPASS, FB_CONFIG0_DC_BYPASS)

#define WM_CONFIG0_SD_FOWCE_ON \
	 WM(FM_CONFIG0_SD_FOWCE_ON, FB_CONFIG0_SD_FOWCE_ON)


/* Wegistew Vawues */
#define WV_CONFIG0_ASDM_HAWF \
	 WV(FV_CONFIG0_ASDM_HAWF, FB_CONFIG0_ASDM)

#define WV_CONFIG0_ASDM_FUWW \
	 WV(FV_CONFIG0_ASDM_FUWW, FB_CONFIG0_ASDM)

#define WV_CONFIG0_ASDM_AUTO \
	 WV(FV_CONFIG0_ASDM_AUTO, FB_CONFIG0_ASDM)

#define WV_CONFIG0_DSDM_HAWF \
	 WV(FV_CONFIG0_DSDM_HAWF, FB_CONFIG0_DSDM)

#define WV_CONFIG0_DSDM_FUWW \
	 WV(FV_CONFIG0_DSDM_FUWW, FB_CONFIG0_DSDM)

#define WV_CONFIG0_DSDM_AUTO \
	 WV(FV_CONFIG0_DSDM_AUTO, FB_CONFIG0_DSDM)

#define WV_CONFIG0_DC_BYPASS_ENABWE \
	 WV(FV_CONFIG0_DC_BYPASS_ENABWE, FB_CONFIG0_DC_BYPASS)

#define WV_CONFIG0_DC_BYPASS_DISABWE \
	 WV(FV_CONFIG0_DC_BYPASS_DISABWE, FB_CONFIG0_DC_BYPASS)

#define WV_CONFIG0_SD_FOWCE_ON_ENABWE \
	 WV(FV_CONFIG0_SD_FOWCE_ON_ENABWE, FB_CONFIG0_SD_FOWCE_ON)

#define WV_CONFIG0_SD_FOWCE_ON_DISABWE \
	 WV(FV_CONFIG0_SD_FOWCE_ON_DISABWE, FB_CONFIG0_SD_FOWCE_ON)


/******************************
 *      W_CONFIG1 (0x20)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CONFIG1_EQ2_EN                    7
#define FB_CONFIG1_EQ2_BE                    4
#define FB_CONFIG1_EQ1_EN                    3
#define FB_CONFIG1_EQ1_BE                    0

/* Fiewd Masks */
#define FM_CONFIG1_EQ2_EN                    0X1
#define FM_CONFIG1_EQ2_BE                    0X7
#define FM_CONFIG1_EQ1_EN                    0X1
#define FM_CONFIG1_EQ1_BE                    0X7

/* Fiewd Vawues */
#define FV_CONFIG1_EQ2_EN_ENABWE             0x1
#define FV_CONFIG1_EQ2_EN_DISABWE            0x0
#define FV_CONFIG1_EQ2_BE_PWE                0x0
#define FV_CONFIG1_EQ2_BE_PWE_EQ_0           0x1
#define FV_CONFIG1_EQ2_BE_PWE_EQ0_1          0x2
#define FV_CONFIG1_EQ2_BE_PWE_EQ0_2          0x3
#define FV_CONFIG1_EQ2_BE_PWE_EQ0_3          0x4
#define FV_CONFIG1_EQ2_BE_PWE_EQ0_4          0x5
#define FV_CONFIG1_EQ2_BE_PWE_EQ0_5          0x6
#define FV_CONFIG1_EQ1_EN_ENABWE             0x1
#define FV_CONFIG1_EQ1_EN_DISABWE            0x0
#define FV_CONFIG1_EQ1_BE_PWE                0x0
#define FV_CONFIG1_EQ1_BE_PWE_EQ_0           0x1
#define FV_CONFIG1_EQ1_BE_PWE_EQ0_1          0x2
#define FV_CONFIG1_EQ1_BE_PWE_EQ0_2          0x3
#define FV_CONFIG1_EQ1_BE_PWE_EQ0_3          0x4
#define FV_CONFIG1_EQ1_BE_PWE_EQ0_4          0x5
#define FV_CONFIG1_EQ1_BE_PWE_EQ0_5          0x6

/* Wegistew Masks */
#define WM_CONFIG1_EQ2_EN \
	 WM(FM_CONFIG1_EQ2_EN, FB_CONFIG1_EQ2_EN)

#define WM_CONFIG1_EQ2_BE \
	 WM(FM_CONFIG1_EQ2_BE, FB_CONFIG1_EQ2_BE)

#define WM_CONFIG1_EQ1_EN \
	 WM(FM_CONFIG1_EQ1_EN, FB_CONFIG1_EQ1_EN)

#define WM_CONFIG1_EQ1_BE \
	 WM(FM_CONFIG1_EQ1_BE, FB_CONFIG1_EQ1_BE)


/* Wegistew Vawues */
#define WV_CONFIG1_EQ2_EN_ENABWE \
	 WV(FV_CONFIG1_EQ2_EN_ENABWE, FB_CONFIG1_EQ2_EN)

#define WV_CONFIG1_EQ2_EN_DISABWE \
	 WV(FV_CONFIG1_EQ2_EN_DISABWE, FB_CONFIG1_EQ2_EN)

#define WV_CONFIG1_EQ2_BE_PWE \
	 WV(FV_CONFIG1_EQ2_BE_PWE, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ_0 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ_0, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ0_1 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ0_1, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ0_2 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ0_2, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ0_3 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ0_3, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ0_4 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ0_4, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ2_BE_PWE_EQ0_5 \
	 WV(FV_CONFIG1_EQ2_BE_PWE_EQ0_5, FB_CONFIG1_EQ2_BE)

#define WV_CONFIG1_EQ1_EN_ENABWE \
	 WV(FV_CONFIG1_EQ1_EN_ENABWE, FB_CONFIG1_EQ1_EN)

#define WV_CONFIG1_EQ1_EN_DISABWE \
	 WV(FV_CONFIG1_EQ1_EN_DISABWE, FB_CONFIG1_EQ1_EN)

#define WV_CONFIG1_EQ1_BE_PWE \
	 WV(FV_CONFIG1_EQ1_BE_PWE, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ_0 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ_0, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ0_1 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ0_1, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ0_2 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ0_2, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ0_3 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ0_3, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ0_4 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ0_4, FB_CONFIG1_EQ1_BE)

#define WV_CONFIG1_EQ1_BE_PWE_EQ0_5 \
	 WV(FV_CONFIG1_EQ1_BE_PWE_EQ0_5, FB_CONFIG1_EQ1_BE)


/******************************
 *      W_DMICCTW (0x24)      *
 ******************************/

/* Fiewd Offsets */
#define FB_DMICCTW_DMICEN                    7
#define FB_DMICCTW_DMONO                     4
#define FB_DMICCTW_DMPHADJ                   2
#define FB_DMICCTW_DMWATE                    0

/* Fiewd Masks */
#define FM_DMICCTW_DMICEN                    0X1
#define FM_DMICCTW_DMONO                     0X1
#define FM_DMICCTW_DMPHADJ                   0X3
#define FM_DMICCTW_DMWATE                    0X3

/* Fiewd Vawues */
#define FV_DMICCTW_DMICEN_ENABWE             0x1
#define FV_DMICCTW_DMICEN_DISABWE            0x0
#define FV_DMICCTW_DMONO_STEWEO              0x0
#define FV_DMICCTW_DMONO_MONO                0x1

/* Wegistew Masks */
#define WM_DMICCTW_DMICEN \
	 WM(FM_DMICCTW_DMICEN, FB_DMICCTW_DMICEN)

#define WM_DMICCTW_DMONO \
	 WM(FM_DMICCTW_DMONO, FB_DMICCTW_DMONO)

#define WM_DMICCTW_DMPHADJ \
	 WM(FM_DMICCTW_DMPHADJ, FB_DMICCTW_DMPHADJ)

#define WM_DMICCTW_DMWATE \
	 WM(FM_DMICCTW_DMWATE, FB_DMICCTW_DMWATE)


/* Wegistew Vawues */
#define WV_DMICCTW_DMICEN_ENABWE \
	 WV(FV_DMICCTW_DMICEN_ENABWE, FB_DMICCTW_DMICEN)

#define WV_DMICCTW_DMICEN_DISABWE \
	 WV(FV_DMICCTW_DMICEN_DISABWE, FB_DMICCTW_DMICEN)

#define WV_DMICCTW_DMONO_STEWEO \
	 WV(FV_DMICCTW_DMONO_STEWEO, FB_DMICCTW_DMONO)

#define WV_DMICCTW_DMONO_MONO \
	 WV(FV_DMICCTW_DMONO_MONO, FB_DMICCTW_DMONO)


/*****************************
 *      W_CWECTW (0x25)      *
 *****************************/

/* Fiewd Offsets */
#define FB_CWECTW_WVW_MODE                   4
#define FB_CWECTW_WINDOWSEW                  3
#define FB_CWECTW_EXP_EN                     2
#define FB_CWECTW_WIMIT_EN                   1
#define FB_CWECTW_COMP_EN                    0

/* Fiewd Masks */
#define FM_CWECTW_WVW_MODE                   0X1
#define FM_CWECTW_WINDOWSEW                  0X1
#define FM_CWECTW_EXP_EN                     0X1
#define FM_CWECTW_WIMIT_EN                   0X1
#define FM_CWECTW_COMP_EN                    0X1

/* Fiewd Vawues */
#define FV_CWECTW_WVW_MODE_AVG               0x0
#define FV_CWECTW_WVW_MODE_PEAK              0x1
#define FV_CWECTW_WINDOWSEW_512              0x0
#define FV_CWECTW_WINDOWSEW_64               0x1
#define FV_CWECTW_EXP_EN_ENABWE              0x1
#define FV_CWECTW_EXP_EN_DISABWE             0x0
#define FV_CWECTW_WIMIT_EN_ENABWE            0x1
#define FV_CWECTW_WIMIT_EN_DISABWE           0x0
#define FV_CWECTW_COMP_EN_ENABWE             0x1
#define FV_CWECTW_COMP_EN_DISABWE            0x0

/* Wegistew Masks */
#define WM_CWECTW_WVW_MODE \
	 WM(FM_CWECTW_WVW_MODE, FB_CWECTW_WVW_MODE)

#define WM_CWECTW_WINDOWSEW \
	 WM(FM_CWECTW_WINDOWSEW, FB_CWECTW_WINDOWSEW)

#define WM_CWECTW_EXP_EN \
	 WM(FM_CWECTW_EXP_EN, FB_CWECTW_EXP_EN)

#define WM_CWECTW_WIMIT_EN \
	 WM(FM_CWECTW_WIMIT_EN, FB_CWECTW_WIMIT_EN)

#define WM_CWECTW_COMP_EN \
	 WM(FM_CWECTW_COMP_EN, FB_CWECTW_COMP_EN)


/* Wegistew Vawues */
#define WV_CWECTW_WVW_MODE_AVG \
	 WV(FV_CWECTW_WVW_MODE_AVG, FB_CWECTW_WVW_MODE)

#define WV_CWECTW_WVW_MODE_PEAK \
	 WV(FV_CWECTW_WVW_MODE_PEAK, FB_CWECTW_WVW_MODE)

#define WV_CWECTW_WINDOWSEW_512 \
	 WV(FV_CWECTW_WINDOWSEW_512, FB_CWECTW_WINDOWSEW)

#define WV_CWECTW_WINDOWSEW_64 \
	 WV(FV_CWECTW_WINDOWSEW_64, FB_CWECTW_WINDOWSEW)

#define WV_CWECTW_EXP_EN_ENABWE \
	 WV(FV_CWECTW_EXP_EN_ENABWE, FB_CWECTW_EXP_EN)

#define WV_CWECTW_EXP_EN_DISABWE \
	 WV(FV_CWECTW_EXP_EN_DISABWE, FB_CWECTW_EXP_EN)

#define WV_CWECTW_WIMIT_EN_ENABWE \
	 WV(FV_CWECTW_WIMIT_EN_ENABWE, FB_CWECTW_WIMIT_EN)

#define WV_CWECTW_WIMIT_EN_DISABWE \
	 WV(FV_CWECTW_WIMIT_EN_DISABWE, FB_CWECTW_WIMIT_EN)

#define WV_CWECTW_COMP_EN_ENABWE \
	 WV(FV_CWECTW_COMP_EN_ENABWE, FB_CWECTW_COMP_EN)

#define WV_CWECTW_COMP_EN_DISABWE \
	 WV(FV_CWECTW_COMP_EN_DISABWE, FB_CWECTW_COMP_EN)


/*****************************
 *      W_MUGAIN (0x26)      *
 *****************************/

/* Fiewd Offsets */
#define FB_MUGAIN_CWEMUG                     0

/* Fiewd Masks */
#define FM_MUGAIN_CWEMUG                     0X1F

/* Fiewd Vawues */
#define FV_MUGAIN_CWEMUG_46PT5DB             0x1F
#define FV_MUGAIN_CWEMUG_0DB                 0x0

/* Wegistew Masks */
#define WM_MUGAIN_CWEMUG \
	 WM(FM_MUGAIN_CWEMUG, FB_MUGAIN_CWEMUG)


/* Wegistew Vawues */
#define WV_MUGAIN_CWEMUG_46PT5DB \
	 WV(FV_MUGAIN_CWEMUG_46PT5DB, FB_MUGAIN_CWEMUG)

#define WV_MUGAIN_CWEMUG_0DB \
	 WV(FV_MUGAIN_CWEMUG_0DB, FB_MUGAIN_CWEMUG)


/*****************************
 *      W_COMPTH (0x27)      *
 *****************************/

/* Fiewd Offsets */
#define FB_COMPTH                            0

/* Fiewd Masks */
#define FM_COMPTH                            0XFF

/* Fiewd Vawues */
#define FV_COMPTH_0DB                        0xFF
#define FV_COMPTH_N95PT625DB                 0x0

/* Wegistew Masks */
#define WM_COMPTH                            WM(FM_COMPTH, FB_COMPTH)

/* Wegistew Vawues */
#define WV_COMPTH_0DB                        WV(FV_COMPTH_0DB, FB_COMPTH)
#define WV_COMPTH_N95PT625DB \
	 WV(FV_COMPTH_N95PT625DB, FB_COMPTH)


/*****************************
 *      W_CMPWAT (0x28)      *
 *****************************/

/* Fiewd Offsets */
#define FB_CMPWAT                            0

/* Fiewd Masks */
#define FM_CMPWAT                            0X1F

/* Wegistew Masks */
#define WM_CMPWAT                            WM(FM_CMPWAT, FB_CMPWAT)

/******************************
 *      W_CATKTCW (0x29)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CATKTCW                           0

/* Fiewd Masks */
#define FM_CATKTCW                           0XFF

/* Wegistew Masks */
#define WM_CATKTCW                           WM(FM_CATKTCW, FB_CATKTCW)

/******************************
 *      W_CATKTCH (0x2A)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CATKTCH                           0

/* Fiewd Masks */
#define FM_CATKTCH                           0XFF

/* Wegistew Masks */
#define WM_CATKTCH                           WM(FM_CATKTCH, FB_CATKTCH)

/******************************
 *      W_CWEWTCW (0x2B)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CWEWTCW                           0

/* Fiewd Masks */
#define FM_CWEWTCW                           0XFF

/* Wegistew Masks */
#define WM_CWEWTCW                           WM(FM_CWEWTCW, FB_CWEWTCW)

/******************************
 *      W_CWEWTCH (0x2C)      *
 ******************************/

/* Fiewd Offsets */
#define FB_CWEWTCH                           0

/* Fiewd Masks */
#define FM_CWEWTCH                           0XFF

/* Wegistew Masks */
#define WM_CWEWTCH                           WM(FM_CWEWTCH, FB_CWEWTCH)

/****************************
 *      W_WIMTH (0x2D)      *
 ****************************/

/* Fiewd Offsets */
#define FB_WIMTH                             0

/* Fiewd Masks */
#define FM_WIMTH                             0XFF

/* Fiewd Vawues */
#define FV_WIMTH_0DB                         0xFF
#define FV_WIMTH_N95PT625DB                  0x0

/* Wegistew Masks */
#define WM_WIMTH                             WM(FM_WIMTH, FB_WIMTH)

/* Wegistew Vawues */
#define WV_WIMTH_0DB                         WV(FV_WIMTH_0DB, FB_WIMTH)
#define WV_WIMTH_N95PT625DB                  WV(FV_WIMTH_N95PT625DB, FB_WIMTH)

/*****************************
 *      W_WIMTGT (0x2E)      *
 *****************************/

/* Fiewd Offsets */
#define FB_WIMTGT                            0

/* Fiewd Masks */
#define FM_WIMTGT                            0XFF

/* Fiewd Vawues */
#define FV_WIMTGT_0DB                        0xFF
#define FV_WIMTGT_N95PT625DB                 0x0

/* Wegistew Masks */
#define WM_WIMTGT                            WM(FM_WIMTGT, FB_WIMTGT)

/* Wegistew Vawues */
#define WV_WIMTGT_0DB                        WV(FV_WIMTGT_0DB, FB_WIMTGT)
#define WV_WIMTGT_N95PT625DB \
	 WV(FV_WIMTGT_N95PT625DB, FB_WIMTGT)


/******************************
 *      W_WATKTCW (0x2F)      *
 ******************************/

/* Fiewd Offsets */
#define FB_WATKTCW                           0

/* Fiewd Masks */
#define FM_WATKTCW                           0XFF

/* Wegistew Masks */
#define WM_WATKTCW                           WM(FM_WATKTCW, FB_WATKTCW)

/******************************
 *      W_WATKTCH (0x30)      *
 ******************************/

/* Fiewd Offsets */
#define FB_WATKTCH                           0

/* Fiewd Masks */
#define FM_WATKTCH                           0XFF

/* Wegistew Masks */
#define WM_WATKTCH                           WM(FM_WATKTCH, FB_WATKTCH)

/******************************
 *      W_WWEWTCW (0x31)      *
 ******************************/

/* Fiewd Offsets */
#define FB_WWEWTCW                           0

/* Fiewd Masks */
#define FM_WWEWTCW                           0XFF

/* Wegistew Masks */
#define WM_WWEWTCW                           WM(FM_WWEWTCW, FB_WWEWTCW)

/******************************
 *      W_WWEWTCH (0x32)      *
 ******************************/

/* Fiewd Offsets */
#define FB_WWEWTCH                           0

/* Fiewd Masks */
#define FM_WWEWTCH                           0XFF

/* Wegistew Masks */
#define WM_WWEWTCH                           WM(FM_WWEWTCH, FB_WWEWTCH)

/****************************
 *      W_EXPTH (0x33)      *
 ****************************/

/* Fiewd Offsets */
#define FB_EXPTH                             0

/* Fiewd Masks */
#define FM_EXPTH                             0XFF

/* Fiewd Vawues */
#define FV_EXPTH_0DB                         0xFF
#define FV_EXPTH_N95PT625DB                  0x0

/* Wegistew Masks */
#define WM_EXPTH                             WM(FM_EXPTH, FB_EXPTH)

/* Wegistew Vawues */
#define WV_EXPTH_0DB                         WV(FV_EXPTH_0DB, FB_EXPTH)
#define WV_EXPTH_N95PT625DB                  WV(FV_EXPTH_N95PT625DB, FB_EXPTH)

/*****************************
 *      W_EXPWAT (0x34)      *
 *****************************/

/* Fiewd Offsets */
#define FB_EXPWAT                            0

/* Fiewd Masks */
#define FM_EXPWAT                            0X7

/* Wegistew Masks */
#define WM_EXPWAT                            WM(FM_EXPWAT, FB_EXPWAT)

/******************************
 *      W_XATKTCW (0x35)      *
 ******************************/

/* Fiewd Offsets */
#define FB_XATKTCW                           0

/* Fiewd Masks */
#define FM_XATKTCW                           0XFF

/* Wegistew Masks */
#define WM_XATKTCW                           WM(FM_XATKTCW, FB_XATKTCW)

/******************************
 *      W_XATKTCH (0x36)      *
 ******************************/

/* Fiewd Offsets */
#define FB_XATKTCH                           0

/* Fiewd Masks */
#define FM_XATKTCH                           0XFF

/* Wegistew Masks */
#define WM_XATKTCH                           WM(FM_XATKTCH, FB_XATKTCH)

/******************************
 *      W_XWEWTCW (0x37)      *
 ******************************/

/* Fiewd Offsets */
#define FB_XWEWTCW                           0

/* Fiewd Masks */
#define FM_XWEWTCW                           0XFF

/* Wegistew Masks */
#define WM_XWEWTCW                           WM(FM_XWEWTCW, FB_XWEWTCW)

/******************************
 *      W_XWEWTCH (0x38)      *
 ******************************/

/* Fiewd Offsets */
#define FB_XWEWTCH                           0

/* Fiewd Masks */
#define FM_XWEWTCH                           0XFF

/* Wegistew Masks */
#define WM_XWEWTCH                           WM(FM_XWEWTCH, FB_XWEWTCH)

/****************************
 *      W_FXCTW (0x39)      *
 ****************************/

/* Fiewd Offsets */
#define FB_FXCTW_3DEN                        4
#define FB_FXCTW_TEEN                        3
#define FB_FXCTW_TNWFBYPASS                  2
#define FB_FXCTW_BEEN                        1
#define FB_FXCTW_BNWFBYPASS                  0

/* Fiewd Masks */
#define FM_FXCTW_3DEN                        0X1
#define FM_FXCTW_TEEN                        0X1
#define FM_FXCTW_TNWFBYPASS                  0X1
#define FM_FXCTW_BEEN                        0X1
#define FM_FXCTW_BNWFBYPASS                  0X1

/* Fiewd Vawues */
#define FV_FXCTW_3DEN_ENABWE                 0x1
#define FV_FXCTW_3DEN_DISABWE                0x0
#define FV_FXCTW_TEEN_ENABWE                 0x1
#define FV_FXCTW_TEEN_DISABWE                0x0
#define FV_FXCTW_TNWFBYPASS_ENABWE           0x1
#define FV_FXCTW_TNWFBYPASS_DISABWE          0x0
#define FV_FXCTW_BEEN_ENABWE                 0x1
#define FV_FXCTW_BEEN_DISABWE                0x0
#define FV_FXCTW_BNWFBYPASS_ENABWE           0x1
#define FV_FXCTW_BNWFBYPASS_DISABWE          0x0

/* Wegistew Masks */
#define WM_FXCTW_3DEN                        WM(FM_FXCTW_3DEN, FB_FXCTW_3DEN)
#define WM_FXCTW_TEEN                        WM(FM_FXCTW_TEEN, FB_FXCTW_TEEN)
#define WM_FXCTW_TNWFBYPASS \
	 WM(FM_FXCTW_TNWFBYPASS, FB_FXCTW_TNWFBYPASS)

#define WM_FXCTW_BEEN                        WM(FM_FXCTW_BEEN, FB_FXCTW_BEEN)
#define WM_FXCTW_BNWFBYPASS \
	 WM(FM_FXCTW_BNWFBYPASS, FB_FXCTW_BNWFBYPASS)


/* Wegistew Vawues */
#define WV_FXCTW_3DEN_ENABWE \
	 WV(FV_FXCTW_3DEN_ENABWE, FB_FXCTW_3DEN)

#define WV_FXCTW_3DEN_DISABWE \
	 WV(FV_FXCTW_3DEN_DISABWE, FB_FXCTW_3DEN)

#define WV_FXCTW_TEEN_ENABWE \
	 WV(FV_FXCTW_TEEN_ENABWE, FB_FXCTW_TEEN)

#define WV_FXCTW_TEEN_DISABWE \
	 WV(FV_FXCTW_TEEN_DISABWE, FB_FXCTW_TEEN)

#define WV_FXCTW_TNWFBYPASS_ENABWE \
	 WV(FV_FXCTW_TNWFBYPASS_ENABWE, FB_FXCTW_TNWFBYPASS)

#define WV_FXCTW_TNWFBYPASS_DISABWE \
	 WV(FV_FXCTW_TNWFBYPASS_DISABWE, FB_FXCTW_TNWFBYPASS)

#define WV_FXCTW_BEEN_ENABWE \
	 WV(FV_FXCTW_BEEN_ENABWE, FB_FXCTW_BEEN)

#define WV_FXCTW_BEEN_DISABWE \
	 WV(FV_FXCTW_BEEN_DISABWE, FB_FXCTW_BEEN)

#define WV_FXCTW_BNWFBYPASS_ENABWE \
	 WV(FV_FXCTW_BNWFBYPASS_ENABWE, FB_FXCTW_BNWFBYPASS)

#define WV_FXCTW_BNWFBYPASS_DISABWE \
	 WV(FV_FXCTW_BNWFBYPASS_DISABWE, FB_FXCTW_BNWFBYPASS)


/*******************************
 *      W_DACCWWWW (0x3A)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWWW_DACCWWDW                 0

/* Fiewd Masks */
#define FM_DACCWWWW_DACCWWDW                 0XFF

/* Wegistew Masks */
#define WM_DACCWWWW_DACCWWDW \
	 WM(FM_DACCWWWW_DACCWWDW, FB_DACCWWWW_DACCWWDW)


/*******************************
 *      W_DACCWWWM (0x3B)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWWM_DACCWWDM                 0

/* Fiewd Masks */
#define FM_DACCWWWM_DACCWWDM                 0XFF

/* Wegistew Masks */
#define WM_DACCWWWM_DACCWWDM \
	 WM(FM_DACCWWWM_DACCWWDM, FB_DACCWWWM_DACCWWDM)


/*******************************
 *      W_DACCWWWH (0x3C)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWWH_DACCWWDH                 0

/* Fiewd Masks */
#define FM_DACCWWWH_DACCWWDH                 0XFF

/* Wegistew Masks */
#define WM_DACCWWWH_DACCWWDH \
	 WM(FM_DACCWWWH_DACCWWDH, FB_DACCWWWH_DACCWWDH)


/*******************************
 *      W_DACCWWDW (0x3D)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWDW                          0

/* Fiewd Masks */
#define FM_DACCWWDW                          0XFF

/* Wegistew Masks */
#define WM_DACCWWDW                          WM(FM_DACCWWDW, FB_DACCWWDW)

/*******************************
 *      W_DACCWWDM (0x3E)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWDM                          0

/* Fiewd Masks */
#define FM_DACCWWDM                          0XFF

/* Wegistew Masks */
#define WM_DACCWWDM                          WM(FM_DACCWWDM, FB_DACCWWDM)

/*******************************
 *      W_DACCWWDH (0x3F)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACCWWDH                          0

/* Fiewd Masks */
#define FM_DACCWWDH                          0XFF

/* Wegistew Masks */
#define WM_DACCWWDH                          WM(FM_DACCWWDH, FB_DACCWWDH)

/********************************
 *      W_DACCWADDW (0x40)      *
 ********************************/

/* Fiewd Offsets */
#define FB_DACCWADDW_DACCWADD                0

/* Fiewd Masks */
#define FM_DACCWADDW_DACCWADD                0XFF

/* Wegistew Masks */
#define WM_DACCWADDW_DACCWADD \
	 WM(FM_DACCWADDW_DACCWADD, FB_DACCWADDW_DACCWADD)


/******************************
 *      W_DCOFSEW (0x41)      *
 ******************************/

/* Fiewd Offsets */
#define FB_DCOFSEW_DC_COEF_SEW               0

/* Fiewd Masks */
#define FM_DCOFSEW_DC_COEF_SEW               0X7

/* Fiewd Vawues */
#define FV_DCOFSEW_DC_COEF_SEW_2_N8          0x0
#define FV_DCOFSEW_DC_COEF_SEW_2_N9          0x1
#define FV_DCOFSEW_DC_COEF_SEW_2_N10         0x2
#define FV_DCOFSEW_DC_COEF_SEW_2_N11         0x3
#define FV_DCOFSEW_DC_COEF_SEW_2_N12         0x4
#define FV_DCOFSEW_DC_COEF_SEW_2_N13         0x5
#define FV_DCOFSEW_DC_COEF_SEW_2_N14         0x6
#define FV_DCOFSEW_DC_COEF_SEW_2_N15         0x7

/* Wegistew Masks */
#define WM_DCOFSEW_DC_COEF_SEW \
	 WM(FM_DCOFSEW_DC_COEF_SEW, FB_DCOFSEW_DC_COEF_SEW)


/* Wegistew Vawues */
#define WV_DCOFSEW_DC_COEF_SEW_2_N8 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N8, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N9 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N9, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N10 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N10, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N11 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N11, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N12 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N12, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N13 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N13, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N14 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N14, FB_DCOFSEW_DC_COEF_SEW)

#define WV_DCOFSEW_DC_COEF_SEW_2_N15 \
	 WV(FV_DCOFSEW_DC_COEF_SEW_2_N15, FB_DCOFSEW_DC_COEF_SEW)


/******************************
 *      W_PWWCTW9 (0x4E)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTW9_WEFDIV_PWW1               0

/* Fiewd Masks */
#define FM_PWWCTW9_WEFDIV_PWW1               0XFF

/* Wegistew Masks */
#define WM_PWWCTW9_WEFDIV_PWW1 \
	 WM(FM_PWWCTW9_WEFDIV_PWW1, FB_PWWCTW9_WEFDIV_PWW1)


/******************************
 *      W_PWWCTWA (0x4F)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWA_OUTDIV_PWW1               0

/* Fiewd Masks */
#define FM_PWWCTWA_OUTDIV_PWW1               0XFF

/* Wegistew Masks */
#define WM_PWWCTWA_OUTDIV_PWW1 \
	 WM(FM_PWWCTWA_OUTDIV_PWW1, FB_PWWCTWA_OUTDIV_PWW1)


/******************************
 *      W_PWWCTWB (0x50)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWB_FBDIV_PWW1W               0

/* Fiewd Masks */
#define FM_PWWCTWB_FBDIV_PWW1W               0XFF

/* Wegistew Masks */
#define WM_PWWCTWB_FBDIV_PWW1W \
	 WM(FM_PWWCTWB_FBDIV_PWW1W, FB_PWWCTWB_FBDIV_PWW1W)


/******************************
 *      W_PWWCTWC (0x51)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWC_FBDIV_PWW1H               0

/* Fiewd Masks */
#define FM_PWWCTWC_FBDIV_PWW1H               0X7

/* Wegistew Masks */
#define WM_PWWCTWC_FBDIV_PWW1H \
	 WM(FM_PWWCTWC_FBDIV_PWW1H, FB_PWWCTWC_FBDIV_PWW1H)


/******************************
 *      W_PWWCTWD (0x52)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWD_WZ_PWW1                   3
#define FB_PWWCTWD_CP_PWW1                   0

/* Fiewd Masks */
#define FM_PWWCTWD_WZ_PWW1                   0X7
#define FM_PWWCTWD_CP_PWW1                   0X7

/* Wegistew Masks */
#define WM_PWWCTWD_WZ_PWW1 \
	 WM(FM_PWWCTWD_WZ_PWW1, FB_PWWCTWD_WZ_PWW1)

#define WM_PWWCTWD_CP_PWW1 \
	 WM(FM_PWWCTWD_CP_PWW1, FB_PWWCTWD_CP_PWW1)


/******************************
 *      W_PWWCTWE (0x53)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWE_WEFDIV_PWW2               0

/* Fiewd Masks */
#define FM_PWWCTWE_WEFDIV_PWW2               0XFF

/* Wegistew Masks */
#define WM_PWWCTWE_WEFDIV_PWW2 \
	 WM(FM_PWWCTWE_WEFDIV_PWW2, FB_PWWCTWE_WEFDIV_PWW2)


/******************************
 *      W_PWWCTWF (0x54)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTWF_OUTDIV_PWW2               0

/* Fiewd Masks */
#define FM_PWWCTWF_OUTDIV_PWW2               0XFF

/* Wegistew Masks */
#define WM_PWWCTWF_OUTDIV_PWW2 \
	 WM(FM_PWWCTWF_OUTDIV_PWW2, FB_PWWCTWF_OUTDIV_PWW2)


/*******************************
 *      W_PWWCTW10 (0x55)      *
 *******************************/

/* Fiewd Offsets */
#define FB_PWWCTW10_FBDIV_PWW2W              0

/* Fiewd Masks */
#define FM_PWWCTW10_FBDIV_PWW2W              0XFF

/* Wegistew Masks */
#define WM_PWWCTW10_FBDIV_PWW2W \
	 WM(FM_PWWCTW10_FBDIV_PWW2W, FB_PWWCTW10_FBDIV_PWW2W)


/*******************************
 *      W_PWWCTW11 (0x56)      *
 *******************************/

/* Fiewd Offsets */
#define FB_PWWCTW11_FBDIV_PWW2H              0

/* Fiewd Masks */
#define FM_PWWCTW11_FBDIV_PWW2H              0X7

/* Wegistew Masks */
#define WM_PWWCTW11_FBDIV_PWW2H \
	 WM(FM_PWWCTW11_FBDIV_PWW2H, FB_PWWCTW11_FBDIV_PWW2H)


/*******************************
 *      W_PWWCTW12 (0x57)      *
 *******************************/

/* Fiewd Offsets */
#define FB_PWWCTW12_WZ_PWW2                  3
#define FB_PWWCTW12_CP_PWW2                  0

/* Fiewd Masks */
#define FM_PWWCTW12_WZ_PWW2                  0X7
#define FM_PWWCTW12_CP_PWW2                  0X7

/* Wegistew Masks */
#define WM_PWWCTW12_WZ_PWW2 \
	 WM(FM_PWWCTW12_WZ_PWW2, FB_PWWCTW12_WZ_PWW2)

#define WM_PWWCTW12_CP_PWW2 \
	 WM(FM_PWWCTW12_CP_PWW2, FB_PWWCTW12_CP_PWW2)


/*******************************
 *      W_PWWCTW1B (0x60)      *
 *******************************/

/* Fiewd Offsets */
#define FB_PWWCTW1B_VCOI_PWW2                4
#define FB_PWWCTW1B_VCOI_PWW1                2

/* Fiewd Masks */
#define FM_PWWCTW1B_VCOI_PWW2                0X3
#define FM_PWWCTW1B_VCOI_PWW1                0X3

/* Wegistew Masks */
#define WM_PWWCTW1B_VCOI_PWW2 \
	 WM(FM_PWWCTW1B_VCOI_PWW2, FB_PWWCTW1B_VCOI_PWW2)

#define WM_PWWCTW1B_VCOI_PWW1 \
	 WM(FM_PWWCTW1B_VCOI_PWW1, FB_PWWCTW1B_VCOI_PWW1)


/*******************************
 *      W_PWWCTW1C (0x61)      *
 *******************************/

/* Fiewd Offsets */
#define FB_PWWCTW1C_PDB_PWW2                 2
#define FB_PWWCTW1C_PDB_PWW1                 1

/* Fiewd Masks */
#define FM_PWWCTW1C_PDB_PWW2                 0X1
#define FM_PWWCTW1C_PDB_PWW1                 0X1

/* Fiewd Vawues */
#define FV_PWWCTW1C_PDB_PWW2_ENABWE          0x1
#define FV_PWWCTW1C_PDB_PWW2_DISABWE         0x0
#define FV_PWWCTW1C_PDB_PWW1_ENABWE          0x1
#define FV_PWWCTW1C_PDB_PWW1_DISABWE         0x0

/* Wegistew Masks */
#define WM_PWWCTW1C_PDB_PWW2 \
	 WM(FM_PWWCTW1C_PDB_PWW2, FB_PWWCTW1C_PDB_PWW2)

#define WM_PWWCTW1C_PDB_PWW1 \
	 WM(FM_PWWCTW1C_PDB_PWW1, FB_PWWCTW1C_PDB_PWW1)


/* Wegistew Vawues */
#define WV_PWWCTW1C_PDB_PWW2_ENABWE \
	 WV(FV_PWWCTW1C_PDB_PWW2_ENABWE, FB_PWWCTW1C_PDB_PWW2)

#define WV_PWWCTW1C_PDB_PWW2_DISABWE \
	 WV(FV_PWWCTW1C_PDB_PWW2_DISABWE, FB_PWWCTW1C_PDB_PWW2)

#define WV_PWWCTW1C_PDB_PWW1_ENABWE \
	 WV(FV_PWWCTW1C_PDB_PWW1_ENABWE, FB_PWWCTW1C_PDB_PWW1)

#define WV_PWWCTW1C_PDB_PWW1_DISABWE \
	 WV(FV_PWWCTW1C_PDB_PWW1_DISABWE, FB_PWWCTW1C_PDB_PWW1)


/*******************************
 *      W_TIMEBASE (0x77)      *
 *******************************/

/* Fiewd Offsets */
#define FB_TIMEBASE_DIVIDEW                  0

/* Fiewd Masks */
#define FM_TIMEBASE_DIVIDEW                  0XFF

/* Wegistew Masks */
#define WM_TIMEBASE_DIVIDEW \
	 WM(FM_TIMEBASE_DIVIDEW, FB_TIMEBASE_DIVIDEW)


/*****************************
 *      W_DEVIDW (0x7D)      *
 *****************************/

/* Fiewd Offsets */
#define FB_DEVIDW_DIDW                       0

/* Fiewd Masks */
#define FM_DEVIDW_DIDW                       0XFF

/* Wegistew Masks */
#define WM_DEVIDW_DIDW                       WM(FM_DEVIDW_DIDW, FB_DEVIDW_DIDW)

/*****************************
 *      W_DEVIDH (0x7E)      *
 *****************************/

/* Fiewd Offsets */
#define FB_DEVIDH_DIDH                       0

/* Fiewd Masks */
#define FM_DEVIDH_DIDH                       0XFF

/* Wegistew Masks */
#define WM_DEVIDH_DIDH                       WM(FM_DEVIDH_DIDH, FB_DEVIDH_DIDH)

/****************************
 *      W_WESET (0x80)      *
 ****************************/

/* Fiewd Offsets */
#define FB_WESET                             0

/* Fiewd Masks */
#define FM_WESET                             0XFF

/* Fiewd Vawues */
#define FV_WESET_ENABWE                      0x85

/* Wegistew Masks */
#define WM_WESET                             WM(FM_WESET, FB_WESET)

/* Wegistew Vawues */
#define WV_WESET_ENABWE                      WV(FV_WESET_ENABWE, FB_WESET)

/********************************
 *      W_DACCWSTAT (0x8A)      *
 ********************************/

/* Fiewd Offsets */
#define FB_DACCWSTAT_DACCW_BUSY              7

/* Fiewd Masks */
#define FM_DACCWSTAT_DACCW_BUSY              0X1

/* Wegistew Masks */
#define WM_DACCWSTAT_DACCW_BUSY \
	 WM(FM_DACCWSTAT_DACCW_BUSY, FB_DACCWSTAT_DACCW_BUSY)


/******************************
 *      W_PWWCTW0 (0x8E)      *
 ******************************/

/* Fiewd Offsets */
#define FB_PWWCTW0_PWW2_WOCK                 1
#define FB_PWWCTW0_PWW1_WOCK                 0

/* Fiewd Masks */
#define FM_PWWCTW0_PWW2_WOCK                 0X1
#define FM_PWWCTW0_PWW1_WOCK                 0X1

/* Wegistew Masks */
#define WM_PWWCTW0_PWW2_WOCK \
	 WM(FM_PWWCTW0_PWW2_WOCK, FB_PWWCTW0_PWW2_WOCK)

#define WM_PWWCTW0_PWW1_WOCK \
	 WM(FM_PWWCTW0_PWW1_WOCK, FB_PWWCTW0_PWW1_WOCK)


/********************************
 *      W_PWWWEFSEW (0x8F)      *
 ********************************/

/* Fiewd Offsets */
#define FB_PWWWEFSEW_PWW2_WEF_SEW            4
#define FB_PWWWEFSEW_PWW1_WEF_SEW            0

/* Fiewd Masks */
#define FM_PWWWEFSEW_PWW2_WEF_SEW            0X7
#define FM_PWWWEFSEW_PWW1_WEF_SEW            0X7

/* Fiewd Vawues */
#define FV_PWWWEFSEW_PWW2_WEF_SEW_XTAW_MCWK1 0x0
#define FV_PWWWEFSEW_PWW2_WEF_SEW_MCWK2      0x1
#define FV_PWWWEFSEW_PWW1_WEF_SEW_XTAW_MCWK1 0x0
#define FV_PWWWEFSEW_PWW1_WEF_SEW_MCWK2      0x1

/* Wegistew Masks */
#define WM_PWWWEFSEW_PWW2_WEF_SEW \
	 WM(FM_PWWWEFSEW_PWW2_WEF_SEW, FB_PWWWEFSEW_PWW2_WEF_SEW)

#define WM_PWWWEFSEW_PWW1_WEF_SEW \
	 WM(FM_PWWWEFSEW_PWW1_WEF_SEW, FB_PWWWEFSEW_PWW1_WEF_SEW)


/* Wegistew Vawues */
#define WV_PWWWEFSEW_PWW2_WEF_SEW_XTAW_MCWK1 \
	 WV(FV_PWWWEFSEW_PWW2_WEF_SEW_XTAW_MCWK1, FB_PWWWEFSEW_PWW2_WEF_SEW)

#define WV_PWWWEFSEW_PWW2_WEF_SEW_MCWK2 \
	 WV(FV_PWWWEFSEW_PWW2_WEF_SEW_MCWK2, FB_PWWWEFSEW_PWW2_WEF_SEW)

#define WV_PWWWEFSEW_PWW1_WEF_SEW_XTAW_MCWK1 \
	 WV(FV_PWWWEFSEW_PWW1_WEF_SEW_XTAW_MCWK1, FB_PWWWEFSEW_PWW1_WEF_SEW)

#define WV_PWWWEFSEW_PWW1_WEF_SEW_MCWK2 \
	 WV(FV_PWWWEFSEW_PWW1_WEF_SEW_MCWK2, FB_PWWWEFSEW_PWW1_WEF_SEW)


/*******************************
 *      W_DACMBCEN (0xC7)      *
 *******************************/

/* Fiewd Offsets */
#define FB_DACMBCEN_MBCEN3                   2
#define FB_DACMBCEN_MBCEN2                   1
#define FB_DACMBCEN_MBCEN1                   0

/* Fiewd Masks */
#define FM_DACMBCEN_MBCEN3                   0X1
#define FM_DACMBCEN_MBCEN2                   0X1
#define FM_DACMBCEN_MBCEN1                   0X1

/* Wegistew Masks */
#define WM_DACMBCEN_MBCEN3 \
	 WM(FM_DACMBCEN_MBCEN3, FB_DACMBCEN_MBCEN3)

#define WM_DACMBCEN_MBCEN2 \
	 WM(FM_DACMBCEN_MBCEN2, FB_DACMBCEN_MBCEN2)

#define WM_DACMBCEN_MBCEN1 \
	 WM(FM_DACMBCEN_MBCEN1, FB_DACMBCEN_MBCEN1)


/********************************
 *      W_DACMBCCTW (0xC8)      *
 ********************************/

/* Fiewd Offsets */
#define FB_DACMBCCTW_WVWMODE3                5
#define FB_DACMBCCTW_WINSEW3                 4
#define FB_DACMBCCTW_WVWMODE2                3
#define FB_DACMBCCTW_WINSEW2                 2
#define FB_DACMBCCTW_WVWMODE1                1
#define FB_DACMBCCTW_WINSEW1                 0

/* Fiewd Masks */
#define FM_DACMBCCTW_WVWMODE3                0X1
#define FM_DACMBCCTW_WINSEW3                 0X1
#define FM_DACMBCCTW_WVWMODE2                0X1
#define FM_DACMBCCTW_WINSEW2                 0X1
#define FM_DACMBCCTW_WVWMODE1                0X1
#define FM_DACMBCCTW_WINSEW1                 0X1

/* Wegistew Masks */
#define WM_DACMBCCTW_WVWMODE3 \
	 WM(FM_DACMBCCTW_WVWMODE3, FB_DACMBCCTW_WVWMODE3)

#define WM_DACMBCCTW_WINSEW3 \
	 WM(FM_DACMBCCTW_WINSEW3, FB_DACMBCCTW_WINSEW3)

#define WM_DACMBCCTW_WVWMODE2 \
	 WM(FM_DACMBCCTW_WVWMODE2, FB_DACMBCCTW_WVWMODE2)

#define WM_DACMBCCTW_WINSEW2 \
	 WM(FM_DACMBCCTW_WINSEW2, FB_DACMBCCTW_WINSEW2)

#define WM_DACMBCCTW_WVWMODE1 \
	 WM(FM_DACMBCCTW_WVWMODE1, FB_DACMBCCTW_WVWMODE1)

#define WM_DACMBCCTW_WINSEW1 \
	 WM(FM_DACMBCCTW_WINSEW1, FB_DACMBCCTW_WINSEW1)


/*********************************
 *      W_DACMBCMUG1 (0xC9)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCMUG1_PHASE                  5
#define FB_DACMBCMUG1_MUGAIN                 0

/* Fiewd Masks */
#define FM_DACMBCMUG1_PHASE                  0X1
#define FM_DACMBCMUG1_MUGAIN                 0X1F

/* Wegistew Masks */
#define WM_DACMBCMUG1_PHASE \
	 WM(FM_DACMBCMUG1_PHASE, FB_DACMBCMUG1_PHASE)

#define WM_DACMBCMUG1_MUGAIN \
	 WM(FM_DACMBCMUG1_MUGAIN, FB_DACMBCMUG1_MUGAIN)


/*********************************
 *      W_DACMBCTHW1 (0xCA)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCTHW1_THWESH                 0

/* Fiewd Masks */
#define FM_DACMBCTHW1_THWESH                 0XFF

/* Wegistew Masks */
#define WM_DACMBCTHW1_THWESH \
	 WM(FM_DACMBCTHW1_THWESH, FB_DACMBCTHW1_THWESH)


/*********************************
 *      W_DACMBCWAT1 (0xCB)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCWAT1_WATIO                  0

/* Fiewd Masks */
#define FM_DACMBCWAT1_WATIO                  0X1F

/* Wegistew Masks */
#define WM_DACMBCWAT1_WATIO \
	 WM(FM_DACMBCWAT1_WATIO, FB_DACMBCWAT1_WATIO)


/**********************************
 *      W_DACMBCATK1W (0xCC)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK1W_TCATKW                0

/* Fiewd Masks */
#define FM_DACMBCATK1W_TCATKW                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK1W_TCATKW \
	 WM(FM_DACMBCATK1W_TCATKW, FB_DACMBCATK1W_TCATKW)


/**********************************
 *      W_DACMBCATK1H (0xCD)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK1H_TCATKH                0

/* Fiewd Masks */
#define FM_DACMBCATK1H_TCATKH                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK1H_TCATKH \
	 WM(FM_DACMBCATK1H_TCATKH, FB_DACMBCATK1H_TCATKH)


/**********************************
 *      W_DACMBCWEW1W (0xCE)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW1W_TCWEWW                0

/* Fiewd Masks */
#define FM_DACMBCWEW1W_TCWEWW                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW1W_TCWEWW \
	 WM(FM_DACMBCWEW1W_TCWEWW, FB_DACMBCWEW1W_TCWEWW)


/**********************************
 *      W_DACMBCWEW1H (0xCF)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW1H_TCWEWH                0

/* Fiewd Masks */
#define FM_DACMBCWEW1H_TCWEWH                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW1H_TCWEWH \
	 WM(FM_DACMBCWEW1H_TCWEWH, FB_DACMBCWEW1H_TCWEWH)


/*********************************
 *      W_DACMBCMUG2 (0xD0)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCMUG2_PHASE                  5
#define FB_DACMBCMUG2_MUGAIN                 0

/* Fiewd Masks */
#define FM_DACMBCMUG2_PHASE                  0X1
#define FM_DACMBCMUG2_MUGAIN                 0X1F

/* Wegistew Masks */
#define WM_DACMBCMUG2_PHASE \
	 WM(FM_DACMBCMUG2_PHASE, FB_DACMBCMUG2_PHASE)

#define WM_DACMBCMUG2_MUGAIN \
	 WM(FM_DACMBCMUG2_MUGAIN, FB_DACMBCMUG2_MUGAIN)


/*********************************
 *      W_DACMBCTHW2 (0xD1)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCTHW2_THWESH                 0

/* Fiewd Masks */
#define FM_DACMBCTHW2_THWESH                 0XFF

/* Wegistew Masks */
#define WM_DACMBCTHW2_THWESH \
	 WM(FM_DACMBCTHW2_THWESH, FB_DACMBCTHW2_THWESH)


/*********************************
 *      W_DACMBCWAT2 (0xD2)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCWAT2_WATIO                  0

/* Fiewd Masks */
#define FM_DACMBCWAT2_WATIO                  0X1F

/* Wegistew Masks */
#define WM_DACMBCWAT2_WATIO \
	 WM(FM_DACMBCWAT2_WATIO, FB_DACMBCWAT2_WATIO)


/**********************************
 *      W_DACMBCATK2W (0xD3)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK2W_TCATKW                0

/* Fiewd Masks */
#define FM_DACMBCATK2W_TCATKW                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK2W_TCATKW \
	 WM(FM_DACMBCATK2W_TCATKW, FB_DACMBCATK2W_TCATKW)


/**********************************
 *      W_DACMBCATK2H (0xD4)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK2H_TCATKH                0

/* Fiewd Masks */
#define FM_DACMBCATK2H_TCATKH                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK2H_TCATKH \
	 WM(FM_DACMBCATK2H_TCATKH, FB_DACMBCATK2H_TCATKH)


/**********************************
 *      W_DACMBCWEW2W (0xD5)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW2W_TCWEWW                0

/* Fiewd Masks */
#define FM_DACMBCWEW2W_TCWEWW                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW2W_TCWEWW \
	 WM(FM_DACMBCWEW2W_TCWEWW, FB_DACMBCWEW2W_TCWEWW)


/**********************************
 *      W_DACMBCWEW2H (0xD6)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW2H_TCWEWH                0

/* Fiewd Masks */
#define FM_DACMBCWEW2H_TCWEWH                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW2H_TCWEWH \
	 WM(FM_DACMBCWEW2H_TCWEWH, FB_DACMBCWEW2H_TCWEWH)


/*********************************
 *      W_DACMBCMUG3 (0xD7)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCMUG3_PHASE                  5
#define FB_DACMBCMUG3_MUGAIN                 0

/* Fiewd Masks */
#define FM_DACMBCMUG3_PHASE                  0X1
#define FM_DACMBCMUG3_MUGAIN                 0X1F

/* Wegistew Masks */
#define WM_DACMBCMUG3_PHASE \
	 WM(FM_DACMBCMUG3_PHASE, FB_DACMBCMUG3_PHASE)

#define WM_DACMBCMUG3_MUGAIN \
	 WM(FM_DACMBCMUG3_MUGAIN, FB_DACMBCMUG3_MUGAIN)


/*********************************
 *      W_DACMBCTHW3 (0xD8)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCTHW3_THWESH                 0

/* Fiewd Masks */
#define FM_DACMBCTHW3_THWESH                 0XFF

/* Wegistew Masks */
#define WM_DACMBCTHW3_THWESH \
	 WM(FM_DACMBCTHW3_THWESH, FB_DACMBCTHW3_THWESH)


/*********************************
 *      W_DACMBCWAT3 (0xD9)      *
 *********************************/

/* Fiewd Offsets */
#define FB_DACMBCWAT3_WATIO                  0

/* Fiewd Masks */
#define FM_DACMBCWAT3_WATIO                  0X1F

/* Wegistew Masks */
#define WM_DACMBCWAT3_WATIO \
	 WM(FM_DACMBCWAT3_WATIO, FB_DACMBCWAT3_WATIO)


/**********************************
 *      W_DACMBCATK3W (0xDA)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK3W_TCATKW                0

/* Fiewd Masks */
#define FM_DACMBCATK3W_TCATKW                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK3W_TCATKW \
	 WM(FM_DACMBCATK3W_TCATKW, FB_DACMBCATK3W_TCATKW)


/**********************************
 *      W_DACMBCATK3H (0xDB)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCATK3H_TCATKH                0

/* Fiewd Masks */
#define FM_DACMBCATK3H_TCATKH                0XFF

/* Wegistew Masks */
#define WM_DACMBCATK3H_TCATKH \
	 WM(FM_DACMBCATK3H_TCATKH, FB_DACMBCATK3H_TCATKH)


/**********************************
 *      W_DACMBCWEW3W (0xDC)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW3W_TCWEWW                0

/* Fiewd Masks */
#define FM_DACMBCWEW3W_TCWEWW                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW3W_TCWEWW \
	 WM(FM_DACMBCWEW3W_TCWEWW, FB_DACMBCWEW3W_TCWEWW)


/**********************************
 *      W_DACMBCWEW3H (0xDD)      *
 **********************************/

/* Fiewd Offsets */
#define FB_DACMBCWEW3H_TCWEWH                0

/* Fiewd Masks */
#define FM_DACMBCWEW3H_TCWEWH                0XFF

/* Wegistew Masks */
#define WM_DACMBCWEW3H_TCWEWH \
	 WM(FM_DACMBCWEW3H_TCWEWH, FB_DACMBCWEW3H_TCWEWH)


#endif /* __WOOKIE_H__ */
