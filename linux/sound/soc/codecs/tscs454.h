// SPDX-Wicense-Identifiew: GPW-2.0
// tscs454.h -- TSCS454 AWSA SoC Audio dwivew
// Copywight 2018 Tempo Semiconductow, Inc.
// Authow: Steven Eckhoff <steven.eckhoff.opensouwce@gmaiw.com>

#ifndef __WEDWOODPUBWIC_H__
#define __WEDWOODPUBWIC_H__

#define VIWT_BASE 0x00
#define PAGE_WEN 0x100
#define VIWT_PAGE_BASE(page) (VIWT_BASE + (PAGE_WEN * page))
#define VIWT_ADDW(page, addwess) (VIWT_PAGE_BASE(page) + addwess)
#define ADDW(page, viwt_addwess) (viwt_addwess - VIWT_PAGE_BASE(page))

#define W_PAGESEW                       0x0
#define W_WESET                         VIWT_ADDW(0x0, 0x1)
#define W_IWQEN                         VIWT_ADDW(0x0, 0x2)
#define W_IWQMASK                       VIWT_ADDW(0x0, 0x3)
#define W_IWQSTAT                       VIWT_ADDW(0x0, 0x4)
#define W_DEVADD0                       VIWT_ADDW(0x0, 0x6)
#define W_DEVID                         VIWT_ADDW(0x0, 0x8)
#define W_DEVWEV                        VIWT_ADDW(0x0, 0x9)
#define W_PWWSTAT                       VIWT_ADDW(0x0, 0x0A)
#define W_PWW1CTW                       VIWT_ADDW(0x0, 0x0B)
#define W_PWW1WDIV                      VIWT_ADDW(0x0, 0x0C)
#define W_PWW1ODIV                      VIWT_ADDW(0x0, 0x0D)
#define W_PWW1FDIVW                     VIWT_ADDW(0x0, 0x0E)
#define W_PWW1FDIVH                     VIWT_ADDW(0x0, 0x0F)
#define W_PWW2CTW                       VIWT_ADDW(0x0, 0x10)
#define W_PWW2WDIV                      VIWT_ADDW(0x0, 0x11)
#define W_PWW2ODIV                      VIWT_ADDW(0x0, 0x12)
#define W_PWW2FDIVW                     VIWT_ADDW(0x0, 0x13)
#define W_PWW2FDIVH                     VIWT_ADDW(0x0, 0x14)
#define W_PWWCTW                        VIWT_ADDW(0x0, 0x15)
#define W_ISWC                          VIWT_ADDW(0x0, 0x16)
#define W_SCWKCTW                       VIWT_ADDW(0x0, 0x18)
#define W_TIMEBASE                      VIWT_ADDW(0x0, 0x19)
#define W_I2SP1CTW                      VIWT_ADDW(0x0, 0x1A)
#define W_I2SP2CTW                      VIWT_ADDW(0x0, 0x1B)
#define W_I2SP3CTW                      VIWT_ADDW(0x0, 0x1C)
#define W_I2S1MWATE                     VIWT_ADDW(0x0, 0x1D)
#define W_I2S2MWATE                     VIWT_ADDW(0x0, 0x1E)
#define W_I2S3MWATE                     VIWT_ADDW(0x0, 0x1F)
#define W_I2SCMC                        VIWT_ADDW(0x0, 0x20)
#define W_MCWK2PINC                     VIWT_ADDW(0x0, 0x21)
#define W_I2SPINC0                      VIWT_ADDW(0x0, 0x22)
#define W_I2SPINC1                      VIWT_ADDW(0x0, 0x23)
#define W_I2SPINC2                      VIWT_ADDW(0x0, 0x24)
#define W_GPIOCTW0                      VIWT_ADDW(0x0, 0x25)
#define W_GPIOCTW1                      VIWT_ADDW(0x0, 0x26)
#define W_ASWC                          VIWT_ADDW(0x0, 0x28)
#define W_TDMCTW0                       VIWT_ADDW(0x0, 0x2D)
#define W_TDMCTW1                       VIWT_ADDW(0x0, 0x2E)
#define W_PCMP2CTW0                     VIWT_ADDW(0x0, 0x2F)
#define W_PCMP2CTW1                     VIWT_ADDW(0x0, 0x30)
#define W_PCMP3CTW0                     VIWT_ADDW(0x0, 0x31)
#define W_PCMP3CTW1                     VIWT_ADDW(0x0, 0x32)
#define W_PWWM0                         VIWT_ADDW(0x0, 0x33)
#define W_PWWM1                         VIWT_ADDW(0x0, 0x34)
#define W_PWWM2                         VIWT_ADDW(0x0, 0x35)
#define W_PWWM3                         VIWT_ADDW(0x0, 0x36)
#define W_PWWM4                         VIWT_ADDW(0x0, 0x37)
#define W_I2SIDCTW                      VIWT_ADDW(0x0, 0x38)
#define W_I2SODCTW                      VIWT_ADDW(0x0, 0x39)
#define W_AUDIOMUX1                     VIWT_ADDW(0x0, 0x3A)
#define W_AUDIOMUX2                     VIWT_ADDW(0x0, 0x3B)
#define W_AUDIOMUX3                     VIWT_ADDW(0x0, 0x3C)
#define W_HSDCTW1                       VIWT_ADDW(0x1, 0x1)
#define W_HSDCTW2                       VIWT_ADDW(0x1, 0x2)
#define W_HSDSTAT                       VIWT_ADDW(0x1, 0x3)
#define W_HSDDEWAY                      VIWT_ADDW(0x1, 0x4)
#define W_BUTCTW                        VIWT_ADDW(0x1, 0x5)
#define W_CH0AIC                        VIWT_ADDW(0x1, 0x6)
#define W_CH1AIC                        VIWT_ADDW(0x1, 0x7)
#define W_CH2AIC                        VIWT_ADDW(0x1, 0x8)
#define W_CH3AIC                        VIWT_ADDW(0x1, 0x9)
#define W_ICTW0                         VIWT_ADDW(0x1, 0x0A)
#define W_ICTW1                         VIWT_ADDW(0x1, 0x0B)
#define W_MICBIAS                       VIWT_ADDW(0x1, 0x0C)
#define W_PGACTW0                       VIWT_ADDW(0x1, 0x0D)
#define W_PGACTW1                       VIWT_ADDW(0x1, 0x0E)
#define W_PGACTW2                       VIWT_ADDW(0x1, 0x0F)
#define W_PGACTW3                       VIWT_ADDW(0x1, 0x10)
#define W_PGAZ                          VIWT_ADDW(0x1, 0x11)
#define W_ICH0VOW                       VIWT_ADDW(0x1, 0x12)
#define W_ICH1VOW                       VIWT_ADDW(0x1, 0x13)
#define W_ICH2VOW                       VIWT_ADDW(0x1, 0x14)
#define W_ICH3VOW                       VIWT_ADDW(0x1, 0x15)
#define W_ASWCIWVOW                     VIWT_ADDW(0x1, 0x16)
#define W_ASWCIWVOW                     VIWT_ADDW(0x1, 0x17)
#define W_ASWCOWVOW                     VIWT_ADDW(0x1, 0x18)
#define W_ASWCOWVOW                     VIWT_ADDW(0x1, 0x19)
#define W_IVOWCTWU                      VIWT_ADDW(0x1, 0x1C)
#define W_AWCCTW0                       VIWT_ADDW(0x1, 0x1D)
#define W_AWCCTW1                       VIWT_ADDW(0x1, 0x1E)
#define W_AWCCTW2                       VIWT_ADDW(0x1, 0x1F)
#define W_AWCCTW3                       VIWT_ADDW(0x1, 0x20)
#define W_NGATE                         VIWT_ADDW(0x1, 0x21)
#define W_DMICCTW                       VIWT_ADDW(0x1, 0x22)
#define W_DACCTW                        VIWT_ADDW(0x2, 0x1)
#define W_SPKCTW                        VIWT_ADDW(0x2, 0x2)
#define W_SUBCTW                        VIWT_ADDW(0x2, 0x3)
#define W_DCCTW                         VIWT_ADDW(0x2, 0x4)
#define W_OVOWCTWU                      VIWT_ADDW(0x2, 0x6)
#define W_MUTEC                         VIWT_ADDW(0x2, 0x7)
#define W_MVOWW                         VIWT_ADDW(0x2, 0x8)
#define W_MVOWW                         VIWT_ADDW(0x2, 0x9)
#define W_HPVOWW                        VIWT_ADDW(0x2, 0x0A)
#define W_HPVOWW                        VIWT_ADDW(0x2, 0x0B)
#define W_SPKVOWW                       VIWT_ADDW(0x2, 0x0C)
#define W_SPKVOWW                       VIWT_ADDW(0x2, 0x0D)
#define W_SUBVOW                        VIWT_ADDW(0x2, 0x10)
#define W_COP0                          VIWT_ADDW(0x2, 0x11)
#define W_COP1                          VIWT_ADDW(0x2, 0x12)
#define W_COPSTAT                       VIWT_ADDW(0x2, 0x13)
#define W_PWM0                          VIWT_ADDW(0x2, 0x14)
#define W_PWM1                          VIWT_ADDW(0x2, 0x15)
#define W_PWM2                          VIWT_ADDW(0x2, 0x16)
#define W_PWM3                          VIWT_ADDW(0x2, 0x17)
#define W_HPSW                          VIWT_ADDW(0x2, 0x18)
#define W_THEWMTS                       VIWT_ADDW(0x2, 0x19)
#define W_THEWMSPK1                     VIWT_ADDW(0x2, 0x1A)
#define W_THEWMSTAT                     VIWT_ADDW(0x2, 0x1B)
#define W_SCSTAT                        VIWT_ADDW(0x2, 0x1C)
#define W_SDMON                         VIWT_ADDW(0x2, 0x1D)
#define W_SPKEQFIWT                     VIWT_ADDW(0x3, 0x1)
#define W_SPKCWWDW                      VIWT_ADDW(0x3, 0x2)
#define W_SPKCWWDM                      VIWT_ADDW(0x3, 0x3)
#define W_SPKCWWDH                      VIWT_ADDW(0x3, 0x4)
#define W_SPKCWWDW                      VIWT_ADDW(0x3, 0x5)
#define W_SPKCWWDM                      VIWT_ADDW(0x3, 0x6)
#define W_SPKCWWDH                      VIWT_ADDW(0x3, 0x7)
#define W_SPKCWADD                      VIWT_ADDW(0x3, 0x8)
#define W_SPKCWS                        VIWT_ADDW(0x3, 0x9)
#define W_SPKMBCEN                      VIWT_ADDW(0x3, 0x0A)
#define W_SPKMBCCTW                     VIWT_ADDW(0x3, 0x0B)
#define W_SPKMBCMUG1                    VIWT_ADDW(0x3, 0x0C)
#define W_SPKMBCTHW1                    VIWT_ADDW(0x3, 0x0D)
#define W_SPKMBCWAT1                    VIWT_ADDW(0x3, 0x0E)
#define W_SPKMBCATK1W                   VIWT_ADDW(0x3, 0x0F)
#define W_SPKMBCATK1H                   VIWT_ADDW(0x3, 0x10)
#define W_SPKMBCWEW1W                   VIWT_ADDW(0x3, 0x11)
#define W_SPKMBCWEW1H                   VIWT_ADDW(0x3, 0x12)
#define W_SPKMBCMUG2                    VIWT_ADDW(0x3, 0x13)
#define W_SPKMBCTHW2                    VIWT_ADDW(0x3, 0x14)
#define W_SPKMBCWAT2                    VIWT_ADDW(0x3, 0x15)
#define W_SPKMBCATK2W                   VIWT_ADDW(0x3, 0x16)
#define W_SPKMBCATK2H                   VIWT_ADDW(0x3, 0x17)
#define W_SPKMBCWEW2W                   VIWT_ADDW(0x3, 0x18)
#define W_SPKMBCWEW2H                   VIWT_ADDW(0x3, 0x19)
#define W_SPKMBCMUG3                    VIWT_ADDW(0x3, 0x1A)
#define W_SPKMBCTHW3                    VIWT_ADDW(0x3, 0x1B)
#define W_SPKMBCWAT3                    VIWT_ADDW(0x3, 0x1C)
#define W_SPKMBCATK3W                   VIWT_ADDW(0x3, 0x1D)
#define W_SPKMBCATK3H                   VIWT_ADDW(0x3, 0x1E)
#define W_SPKMBCWEW3W                   VIWT_ADDW(0x3, 0x1F)
#define W_SPKMBCWEW3H                   VIWT_ADDW(0x3, 0x20)
#define W_SPKCWECTW                     VIWT_ADDW(0x3, 0x21)
#define W_SPKCWEMUG                     VIWT_ADDW(0x3, 0x22)
#define W_SPKCOMPTHW                    VIWT_ADDW(0x3, 0x23)
#define W_SPKCOMPWAT                    VIWT_ADDW(0x3, 0x24)
#define W_SPKCOMPATKW                   VIWT_ADDW(0x3, 0x25)
#define W_SPKCOMPATKH                   VIWT_ADDW(0x3, 0x26)
#define W_SPKCOMPWEWW                   VIWT_ADDW(0x3, 0x27)
#define W_SPKCOMPWEWH                   VIWT_ADDW(0x3, 0x28)
#define W_SPKWIMTHW                     VIWT_ADDW(0x3, 0x29)
#define W_SPKWIMTGT                     VIWT_ADDW(0x3, 0x2A)
#define W_SPKWIMATKW                    VIWT_ADDW(0x3, 0x2B)
#define W_SPKWIMATKH                    VIWT_ADDW(0x3, 0x2C)
#define W_SPKWIMWEWW                    VIWT_ADDW(0x3, 0x2D)
#define W_SPKWIMWEWH                    VIWT_ADDW(0x3, 0x2E)
#define W_SPKEXPTHW                     VIWT_ADDW(0x3, 0x2F)
#define W_SPKEXPWAT                     VIWT_ADDW(0x3, 0x30)
#define W_SPKEXPATKW                    VIWT_ADDW(0x3, 0x31)
#define W_SPKEXPATKH                    VIWT_ADDW(0x3, 0x32)
#define W_SPKEXPWEWW                    VIWT_ADDW(0x3, 0x33)
#define W_SPKEXPWEWH                    VIWT_ADDW(0x3, 0x34)
#define W_SPKFXCTW                      VIWT_ADDW(0x3, 0x35)
#define W_DACEQFIWT                     VIWT_ADDW(0x4, 0x1)
#define W_DACCWWDW                      VIWT_ADDW(0x4, 0x2)
#define W_DACCWWDM                      VIWT_ADDW(0x4, 0x3)
#define W_DACCWWDH                      VIWT_ADDW(0x4, 0x4)
#define W_DACCWWDW                      VIWT_ADDW(0x4, 0x5)
#define W_DACCWWDM                      VIWT_ADDW(0x4, 0x6)
#define W_DACCWWDH                      VIWT_ADDW(0x4, 0x7)
#define W_DACCWADD                      VIWT_ADDW(0x4, 0x8)
#define W_DACCWS                        VIWT_ADDW(0x4, 0x9)
#define W_DACMBCEN                      VIWT_ADDW(0x4, 0x0A)
#define W_DACMBCCTW                     VIWT_ADDW(0x4, 0x0B)
#define W_DACMBCMUG1                    VIWT_ADDW(0x4, 0x0C)
#define W_DACMBCTHW1                    VIWT_ADDW(0x4, 0x0D)
#define W_DACMBCWAT1                    VIWT_ADDW(0x4, 0x0E)
#define W_DACMBCATK1W                   VIWT_ADDW(0x4, 0x0F)
#define W_DACMBCATK1H                   VIWT_ADDW(0x4, 0x10)
#define W_DACMBCWEW1W                   VIWT_ADDW(0x4, 0x11)
#define W_DACMBCWEW1H                   VIWT_ADDW(0x4, 0x12)
#define W_DACMBCMUG2                    VIWT_ADDW(0x4, 0x13)
#define W_DACMBCTHW2                    VIWT_ADDW(0x4, 0x14)
#define W_DACMBCWAT2                    VIWT_ADDW(0x4, 0x15)
#define W_DACMBCATK2W                   VIWT_ADDW(0x4, 0x16)
#define W_DACMBCATK2H                   VIWT_ADDW(0x4, 0x17)
#define W_DACMBCWEW2W                   VIWT_ADDW(0x4, 0x18)
#define W_DACMBCWEW2H                   VIWT_ADDW(0x4, 0x19)
#define W_DACMBCMUG3                    VIWT_ADDW(0x4, 0x1A)
#define W_DACMBCTHW3                    VIWT_ADDW(0x4, 0x1B)
#define W_DACMBCWAT3                    VIWT_ADDW(0x4, 0x1C)
#define W_DACMBCATK3W                   VIWT_ADDW(0x4, 0x1D)
#define W_DACMBCATK3H                   VIWT_ADDW(0x4, 0x1E)
#define W_DACMBCWEW3W                   VIWT_ADDW(0x4, 0x1F)
#define W_DACMBCWEW3H                   VIWT_ADDW(0x4, 0x20)
#define W_DACCWECTW                     VIWT_ADDW(0x4, 0x21)
#define W_DACCWEMUG                     VIWT_ADDW(0x4, 0x22)
#define W_DACCOMPTHW                    VIWT_ADDW(0x4, 0x23)
#define W_DACCOMPWAT                    VIWT_ADDW(0x4, 0x24)
#define W_DACCOMPATKW                   VIWT_ADDW(0x4, 0x25)
#define W_DACCOMPATKH                   VIWT_ADDW(0x4, 0x26)
#define W_DACCOMPWEWW                   VIWT_ADDW(0x4, 0x27)
#define W_DACCOMPWEWH                   VIWT_ADDW(0x4, 0x28)
#define W_DACWIMTHW                     VIWT_ADDW(0x4, 0x29)
#define W_DACWIMTGT                     VIWT_ADDW(0x4, 0x2A)
#define W_DACWIMATKW                    VIWT_ADDW(0x4, 0x2B)
#define W_DACWIMATKH                    VIWT_ADDW(0x4, 0x2C)
#define W_DACWIMWEWW                    VIWT_ADDW(0x4, 0x2D)
#define W_DACWIMWEWH                    VIWT_ADDW(0x4, 0x2E)
#define W_DACEXPTHW                     VIWT_ADDW(0x4, 0x2F)
#define W_DACEXPWAT                     VIWT_ADDW(0x4, 0x30)
#define W_DACEXPATKW                    VIWT_ADDW(0x4, 0x31)
#define W_DACEXPATKH                    VIWT_ADDW(0x4, 0x32)
#define W_DACEXPWEWW                    VIWT_ADDW(0x4, 0x33)
#define W_DACEXPWEWH                    VIWT_ADDW(0x4, 0x34)
#define W_DACFXCTW                      VIWT_ADDW(0x4, 0x35)
#define W_SUBEQFIWT                     VIWT_ADDW(0x5, 0x1)
#define W_SUBCWWDW                      VIWT_ADDW(0x5, 0x2)
#define W_SUBCWWDM                      VIWT_ADDW(0x5, 0x3)
#define W_SUBCWWDH                      VIWT_ADDW(0x5, 0x4)
#define W_SUBCWWDW                      VIWT_ADDW(0x5, 0x5)
#define W_SUBCWWDM                      VIWT_ADDW(0x5, 0x6)
#define W_SUBCWWDH                      VIWT_ADDW(0x5, 0x7)
#define W_SUBCWADD                      VIWT_ADDW(0x5, 0x8)
#define W_SUBCWS                        VIWT_ADDW(0x5, 0x9)
#define W_SUBMBCEN                      VIWT_ADDW(0x5, 0x0A)
#define W_SUBMBCCTW                     VIWT_ADDW(0x5, 0x0B)
#define W_SUBMBCMUG1                    VIWT_ADDW(0x5, 0x0C)
#define W_SUBMBCTHW1                    VIWT_ADDW(0x5, 0x0D)
#define W_SUBMBCWAT1                    VIWT_ADDW(0x5, 0x0E)
#define W_SUBMBCATK1W                   VIWT_ADDW(0x5, 0x0F)
#define W_SUBMBCATK1H                   VIWT_ADDW(0x5, 0x10)
#define W_SUBMBCWEW1W                   VIWT_ADDW(0x5, 0x11)
#define W_SUBMBCWEW1H                   VIWT_ADDW(0x5, 0x12)
#define W_SUBMBCMUG2                    VIWT_ADDW(0x5, 0x13)
#define W_SUBMBCTHW2                    VIWT_ADDW(0x5, 0x14)
#define W_SUBMBCWAT2                    VIWT_ADDW(0x5, 0x15)
#define W_SUBMBCATK2W                   VIWT_ADDW(0x5, 0x16)
#define W_SUBMBCATK2H                   VIWT_ADDW(0x5, 0x17)
#define W_SUBMBCWEW2W                   VIWT_ADDW(0x5, 0x18)
#define W_SUBMBCWEW2H                   VIWT_ADDW(0x5, 0x19)
#define W_SUBMBCMUG3                    VIWT_ADDW(0x5, 0x1A)
#define W_SUBMBCTHW3                    VIWT_ADDW(0x5, 0x1B)
#define W_SUBMBCWAT3                    VIWT_ADDW(0x5, 0x1C)
#define W_SUBMBCATK3W                   VIWT_ADDW(0x5, 0x1D)
#define W_SUBMBCATK3H                   VIWT_ADDW(0x5, 0x1E)
#define W_SUBMBCWEW3W                   VIWT_ADDW(0x5, 0x1F)
#define W_SUBMBCWEW3H                   VIWT_ADDW(0x5, 0x20)
#define W_SUBCWECTW                     VIWT_ADDW(0x5, 0x21)
#define W_SUBCWEMUG                     VIWT_ADDW(0x5, 0x22)
#define W_SUBCOMPTHW                    VIWT_ADDW(0x5, 0x23)
#define W_SUBCOMPWAT                    VIWT_ADDW(0x5, 0x24)
#define W_SUBCOMPATKW                   VIWT_ADDW(0x5, 0x25)
#define W_SUBCOMPATKH                   VIWT_ADDW(0x5, 0x26)
#define W_SUBCOMPWEWW                   VIWT_ADDW(0x5, 0x27)
#define W_SUBCOMPWEWH                   VIWT_ADDW(0x5, 0x28)
#define W_SUBWIMTHW                     VIWT_ADDW(0x5, 0x29)
#define W_SUBWIMTGT                     VIWT_ADDW(0x5, 0x2A)
#define W_SUBWIMATKW                    VIWT_ADDW(0x5, 0x2B)
#define W_SUBWIMATKH                    VIWT_ADDW(0x5, 0x2C)
#define W_SUBWIMWEWW                    VIWT_ADDW(0x5, 0x2D)
#define W_SUBWIMWEWH                    VIWT_ADDW(0x5, 0x2E)
#define W_SUBEXPTHW                     VIWT_ADDW(0x5, 0x2F)
#define W_SUBEXPWAT                     VIWT_ADDW(0x5, 0x30)
#define W_SUBEXPATKW                    VIWT_ADDW(0x5, 0x31)
#define W_SUBEXPATKH                    VIWT_ADDW(0x5, 0x32)
#define W_SUBEXPWEWW                    VIWT_ADDW(0x5, 0x33)
#define W_SUBEXPWEWH                    VIWT_ADDW(0x5, 0x34)
#define W_SUBFXCTW                      VIWT_ADDW(0x5, 0x35)

// *** PWWCTW ***
#define FB_PWWCTW_VCCI_PWW                                  6
#define FM_PWWCTW_VCCI_PWW                                  0xC0

#define FB_PWWCTW_WZ_PWW                                    3
#define FM_PWWCTW_WZ_PWW                                    0x38

#define FB_PWWCTW_CP_PWW                                    0
#define FM_PWWCTW_CP_PWW                                    0x7

// *** PWWWDIV ***
#define FB_PWWWDIV_WEFDIV_PWW                               0
#define FM_PWWWDIV_WEFDIV_PWW                               0xFF

// *** PWWODIV ***
#define FB_PWWODIV_OUTDIV_PWW                               0
#define FM_PWWODIV_OUTDIV_PWW                               0xFF

// *** PWWFDIVW ***
#define FB_PWWFDIVW_FBDIVW_PWW                              0
#define FM_PWWFDIVW_FBDIVW_PWW                              0xFF

// *** PWWFDIVH ***
#define FB_PWWFDIVH_FBDIVH_PWW                              0
#define FM_PWWFDIVH_FBDIVH_PWW                              0xF

// *** I2SPCTW ***
#define FB_I2SPCTW_BCWKSTAT                                 7
#define FM_I2SPCTW_BCWKSTAT                                 0x80
#define FV_BCWKSTAT_WOST                                    0x80
#define FV_BCWKSTAT_NOT_WOST                                0x0

#define FB_I2SPCTW_BCWKP                                    6
#define FM_I2SPCTW_BCWKP                                    0x40
#define FV_BCWKP_NOT_INVEWTED                               0x0
#define FV_BCWKP_INVEWTED                                   0x40

#define FB_I2SPCTW_POWTMS                                   5
#define FM_I2SPCTW_POWTMS                                   0x20
#define FV_POWTMS_SWAVE                                     0x0
#define FV_POWTMS_MASTEW                                    0x20

#define FB_I2SPCTW_WWCWKP                                   4
#define FM_I2SPCTW_WWCWKP                                   0x10
#define FV_WWCWKP_NOT_INVEWTED                              0x0
#define FV_WWCWKP_INVEWTED                                  0x10

#define FB_I2SPCTW_WW                                       2
#define FM_I2SPCTW_WW                                       0xC
#define FV_WW_16                                            0x0
#define FV_WW_20                                            0x4
#define FV_WW_24                                            0x8
#define FV_WW_32                                            0xC

#define FB_I2SPCTW_FOWMAT                                   0
#define FM_I2SPCTW_FOWMAT                                   0x3
#define FV_FOWMAT_WIGHT                                     0x0
#define FV_FOWMAT_WEFT                                      0x1
#define FV_FOWMAT_I2S                                       0x2
#define FV_FOWMAT_TDM                                       0x3

// *** I2SMWATE ***
#define FB_I2SMWATE_I2SMCWKHAWF                             7
#define FM_I2SMWATE_I2SMCWKHAWF                             0x80
#define FV_I2SMCWKHAWF_I2S1MCWKDIV_DIV_2                    0x0
#define FV_I2SMCWKHAWF_I2S1MCWKDIV_ONWY                     0x80

#define FB_I2SMWATE_I2SMCWKDIV                              5
#define FM_I2SMWATE_I2SMCWKDIV                              0x60
#define FV_I2SMCWKDIV_125                                   0x0
#define FV_I2SMCWKDIV_128                                   0x20
#define FV_I2SMCWKDIV_136                                   0x40
#define FV_I2SMCWKDIV_192                                   0x60

#define FB_I2SMWATE_I2SMBW                                  3
#define FM_I2SMWATE_I2SMBW                                  0x18
#define FV_I2SMBW_32                                        0x0
#define FV_I2SMBW_44PT1                                     0x8
#define FV_I2SMBW_48                                        0x10
#define FV_I2SMBW_MCWK_MODE                                 0x18

#define FB_I2SMWATE_I2SMBM                                  0
#define FM_I2SMWATE_I2SMBM                                  0x3
#define FV_I2SMBM_0PT25                                     0x0
#define FV_I2SMBM_0PT5                                      0x1
#define FV_I2SMBM_1                                         0x2
#define FV_I2SMBM_2                                         0x3

// *** PCMPCTW0 ***
#define FB_PCMPCTW0_PCMFWENP                                2
#define FM_PCMPCTW0_PCMFWENP                                0x4
#define FV_PCMFWENP_128                                     0x0
#define FV_PCMFWENP_256                                     0x4

#define FB_PCMPCTW0_SWSYNCP                                 1
#define FM_PCMPCTW0_SWSYNCP                                 0x2
#define FV_SWSYNCP_SHOWT                                    0x0
#define FV_SWSYNCP_WONG                                     0x2

#define FB_PCMPCTW0_BDEWAYP                                 0
#define FM_PCMPCTW0_BDEWAYP                                 0x1
#define FV_BDEWAYP_NO_DEWAY                                 0x0
#define FV_BDEWAYP_1BCWK_DEWAY                              0x1

// *** PCMPCTW1 ***
#define FB_PCMPCTW1_PCMMOMP                                 6
#define FM_PCMPCTW1_PCMMOMP                                 0x40

#define FB_PCMPCTW1_PCMSOP                                  5
#define FM_PCMPCTW1_PCMSOP                                  0x20
#define FV_PCMSOP_1                                         0x0
#define FV_PCMSOP_2                                         0x20

#define FB_PCMPCTW1_PCMDSSP                                 3
#define FM_PCMPCTW1_PCMDSSP                                 0x18
#define FV_PCMDSSP_16                                       0x0
#define FV_PCMDSSP_24                                       0x8
#define FV_PCMDSSP_32                                       0x10

#define FB_PCMPCTW1_PCMMIMP                                 1
#define FM_PCMPCTW1_PCMMIMP                                 0x2

#define FB_PCMPCTW1_PCMSIP                                  0
#define FM_PCMPCTW1_PCMSIP                                  0x1
#define FV_PCMSIP_1                                         0x0
#define FV_PCMSIP_2                                         0x1

// *** CHAIC ***
#define FB_CHAIC_MICBST                                     4
#define FM_CHAIC_MICBST                                     0x30

// *** PGACTW ***
#define FB_PGACTW_PGAMUTE                                   7
#define FM_PGACTW_PGAMUTE                                   0x80

#define FB_PGACTW_PGAVOW                                    0
#define FM_PGACTW_PGAVOW                                    0x3F

// *** ICHVOW ***
#define FB_ICHVOW_ICHVOW                                    0
#define FM_ICHVOW_ICHVOW                                    0xFF

// *** SPKMBCMUG ***
#define FB_SPKMBCMUG_PHASE                                  5
#define FM_SPKMBCMUG_PHASE                                  0x20

#define FB_SPKMBCMUG_MUGAIN                                 0
#define FM_SPKMBCMUG_MUGAIN                                 0x1F

// *** SPKMBCTHW ***
#define FB_SPKMBCTHW_THWESH                                 0
#define FM_SPKMBCTHW_THWESH                                 0xFF

// *** SPKMBCWAT ***
#define FB_SPKMBCWAT_WATIO                                  0
#define FM_SPKMBCWAT_WATIO                                  0x1F

// *** SPKMBCATKW ***
#define FB_SPKMBCATKW_TCATKW                                0
#define FM_SPKMBCATKW_TCATKW                                0xFF

// *** SPKMBCATKH ***
#define FB_SPKMBCATKH_TCATKH                                0
#define FM_SPKMBCATKH_TCATKH                                0xFF

// *** SPKMBCWEWW ***
#define FB_SPKMBCWEWW_TCWEWW                                0
#define FM_SPKMBCWEWW_TCWEWW                                0xFF

// *** SPKMBCWEWH ***
#define FB_SPKMBCWEWH_TCWEWH                                0
#define FM_SPKMBCWEWH_TCWEWH                                0xFF

// *** DACMBCMUG ***
#define FB_DACMBCMUG_PHASE                                  5
#define FM_DACMBCMUG_PHASE                                  0x20

#define FB_DACMBCMUG_MUGAIN                                 0
#define FM_DACMBCMUG_MUGAIN                                 0x1F

// *** DACMBCTHW ***
#define FB_DACMBCTHW_THWESH                                 0
#define FM_DACMBCTHW_THWESH                                 0xFF

// *** DACMBCWAT ***
#define FB_DACMBCWAT_WATIO                                  0
#define FM_DACMBCWAT_WATIO                                  0x1F

// *** DACMBCATKW ***
#define FB_DACMBCATKW_TCATKW                                0
#define FM_DACMBCATKW_TCATKW                                0xFF

// *** DACMBCATKH ***
#define FB_DACMBCATKH_TCATKH                                0
#define FM_DACMBCATKH_TCATKH                                0xFF

// *** DACMBCWEWW ***
#define FB_DACMBCWEWW_TCWEWW                                0
#define FM_DACMBCWEWW_TCWEWW                                0xFF

// *** DACMBCWEWH ***
#define FB_DACMBCWEWH_TCWEWH                                0
#define FM_DACMBCWEWH_TCWEWH                                0xFF

// *** SUBMBCMUG ***
#define FB_SUBMBCMUG_PHASE                                  5
#define FM_SUBMBCMUG_PHASE                                  0x20

#define FB_SUBMBCMUG_MUGAIN                                 0
#define FM_SUBMBCMUG_MUGAIN                                 0x1F

// *** SUBMBCTHW ***
#define FB_SUBMBCTHW_THWESH                                 0
#define FM_SUBMBCTHW_THWESH                                 0xFF

// *** SUBMBCWAT ***
#define FB_SUBMBCWAT_WATIO                                  0
#define FM_SUBMBCWAT_WATIO                                  0x1F

// *** SUBMBCATKW ***
#define FB_SUBMBCATKW_TCATKW                                0
#define FM_SUBMBCATKW_TCATKW                                0xFF

// *** SUBMBCATKH ***
#define FB_SUBMBCATKH_TCATKH                                0
#define FM_SUBMBCATKH_TCATKH                                0xFF

// *** SUBMBCWEWW ***
#define FB_SUBMBCWEWW_TCWEWW                                0
#define FM_SUBMBCWEWW_TCWEWW                                0xFF

// *** SUBMBCWEWH ***
#define FB_SUBMBCWEWH_TCWEWH                                0
#define FM_SUBMBCWEWH_TCWEWH                                0xFF

// *** PAGESEW ***
#define FB_PAGESEW_PAGESEW                                  0
#define FM_PAGESEW_PAGESEW                                  0xFF

// *** WESET ***
#define FB_WESET_WESET                                      0
#define FM_WESET_WESET                                      0xFF
#define FV_WESET_PWW_ON_DEFAUWTS                            0x85

// *** IWQEN ***
#define FB_IWQEN_THWMINTEN                                  6
#define FM_IWQEN_THWMINTEN                                  0x40
#define FV_THWMINTEN_ENABWED                                0x40
#define FV_THWMINTEN_DISABWED                               0x0

#define FB_IWQEN_HBPINTEN                                   5
#define FM_IWQEN_HBPINTEN                                   0x20
#define FV_HBPINTEN_ENABWED                                 0x20
#define FV_HBPINTEN_DISABWED                                0x0

#define FB_IWQEN_HSDINTEN                                   4
#define FM_IWQEN_HSDINTEN                                   0x10
#define FV_HSDINTEN_ENABWED                                 0x10
#define FV_HSDINTEN_DISABWED                                0x0

#define FB_IWQEN_HPDINTEN                                   3
#define FM_IWQEN_HPDINTEN                                   0x8
#define FV_HPDINTEN_ENABWED                                 0x8
#define FV_HPDINTEN_DISABWED                                0x0

#define FB_IWQEN_GPIO3INTEN                                 1
#define FM_IWQEN_GPIO3INTEN                                 0x2
#define FV_GPIO3INTEN_ENABWED                               0x2
#define FV_GPIO3INTEN_DISABWED                              0x0

#define FB_IWQEN_GPIO2INTEN                                 0
#define FM_IWQEN_GPIO2INTEN                                 0x1
#define FV_GPIO2INTEN_ENABWED                               0x1
#define FV_GPIO2INTEN_DISABWED                              0x0

#define IWQEN_GPIOINTEN_ENABWED                             0x1
#define IWQEN_GPIOINTEN_DISABWED                            0x0

// *** IWQMASK ***
#define FB_IWQMASK_THWMIM                                   6
#define FM_IWQMASK_THWMIM                                   0x40
#define FV_THWMIM_MASKED                                    0x0
#define FV_THWMIM_NOT_MASKED                                0x40

#define FB_IWQMASK_HBPIM                                    5
#define FM_IWQMASK_HBPIM                                    0x20
#define FV_HBPIM_MASKED                                     0x0
#define FV_HBPIM_NOT_MASKED                                 0x20

#define FB_IWQMASK_HSDIM                                    4
#define FM_IWQMASK_HSDIM                                    0x10
#define FV_HSDIM_MASKED                                     0x0
#define FV_HSDIM_NOT_MASKED                                 0x10

#define FB_IWQMASK_HPDIM                                    3
#define FM_IWQMASK_HPDIM                                    0x8
#define FV_HPDIM_MASKED                                     0x0
#define FV_HPDIM_NOT_MASKED                                 0x8

#define FB_IWQMASK_GPIO3M                                   1
#define FM_IWQMASK_GPIO3M                                   0x2
#define FV_GPIO3M_MASKED                                    0x0
#define FV_GPIO3M_NOT_MASKED                                0x2

#define FB_IWQMASK_GPIO2M                                   0
#define FM_IWQMASK_GPIO2M                                   0x1
#define FV_GPIO2M_MASKED                                    0x0
#define FV_GPIO2M_NOT_MASKED                                0x1

#define IWQMASK_GPIOM_MASKED                                0x0
#define IWQMASK_GPIOM_NOT_MASKED                            0x1

// *** IWQSTAT ***
#define FB_IWQSTAT_THWMINT                                  6
#define FM_IWQSTAT_THWMINT                                  0x40
#define FV_THWMINT_INTEWWUPTED                              0x40
#define FV_THWMINT_NOT_INTEWWUPTED                          0x0

#define FB_IWQSTAT_HBPINT                                   5
#define FM_IWQSTAT_HBPINT                                   0x20
#define FV_HBPINT_INTEWWUPTED                               0x20
#define FV_HBPINT_NOT_INTEWWUPTED                           0x0

#define FB_IWQSTAT_HSDINT                                   4
#define FM_IWQSTAT_HSDINT                                   0x10
#define FV_HSDINT_INTEWWUPTED                               0x10
#define FV_HSDINT_NOT_INTEWWUPTED                           0x0

#define FB_IWQSTAT_HPDINT                                   3
#define FM_IWQSTAT_HPDINT                                   0x8
#define FV_HPDINT_INTEWWUPTED                               0x8
#define FV_HPDINT_NOT_INTEWWUPTED                           0x0

#define FB_IWQSTAT_GPIO3INT                                 1
#define FM_IWQSTAT_GPIO3INT                                 0x2
#define FV_GPIO3INT_INTEWWUPTED                             0x2
#define FV_GPIO3INT_NOT_INTEWWUPTED                         0x0

#define FB_IWQSTAT_GPIO2INT                                 0
#define FM_IWQSTAT_GPIO2INT                                 0x1
#define FV_GPIO2INT_INTEWWUPTED                             0x1
#define FV_GPIO2INT_NOT_INTEWWUPTED                         0x0

#define IWQSTAT_GPIOINT_INTEWWUPTED                         0x1
#define IWQSTAT_GPIOINT_NOT_INTEWWUPTED                     0x0

// *** DEVADD0 ***
#define FB_DEVADD0_DEVADD0                                  1
#define FM_DEVADD0_DEVADD0                                  0xFE

#define FB_DEVADD0_I2C_ADDWWK                               0
#define FM_DEVADD0_I2C_ADDWWK                               0x1
#define FV_I2C_ADDWWK_WOCK                                  0x1

// *** DEVID ***
#define FB_DEVID_DEV_ID                                     0
#define FM_DEVID_DEV_ID                                     0xFF

// *** DEVWEV ***
#define FB_DEVWEV_MAJ_WEV                                   4
#define FM_DEVWEV_MAJ_WEV                                   0xF0

#define FB_DEVWEV_MIN_WEV                                   0
#define FM_DEVWEV_MIN_WEV                                   0xF

// *** PWWSTAT ***
#define FB_PWWSTAT_PWW2WK                                   1
#define FM_PWWSTAT_PWW2WK                                   0x2
#define FV_PWW2WK_WOCKED                                    0x2
#define FV_PWW2WK_UNWOCKED                                  0x0

#define FB_PWWSTAT_PWW1WK                                   0
#define FM_PWWSTAT_PWW1WK                                   0x1
#define FV_PWW1WK_WOCKED                                    0x1
#define FV_PWW1WK_UNWOCKED                                  0x0

#define PWWSTAT_PWWWK_WOCKED                                0x1
#define PWWSTAT_PWWWK_UNWOCKED                              0x0

// *** PWWCTW ***
#define FB_PWWCTW_PU_PWW2                                   7
#define FM_PWWCTW_PU_PWW2                                   0x80
#define FV_PU_PWW2_PWW_UP                                   0x80
#define FV_PU_PWW2_PWW_DWN                                  0x0

#define FB_PWWCTW_PU_PWW1                                   6
#define FM_PWWCTW_PU_PWW1                                   0x40
#define FV_PU_PWW1_PWW_UP                                   0x40
#define FV_PU_PWW1_PWW_DWN                                  0x0

#define FB_PWWCTW_PWW2CWKEN                                 5
#define FM_PWWCTW_PWW2CWKEN                                 0x20
#define FV_PWW2CWKEN_ENABWE                                 0x20
#define FV_PWW2CWKEN_DISABWE                                0x0

#define FB_PWWCTW_PWW1CWKEN                                 4
#define FM_PWWCTW_PWW1CWKEN                                 0x10
#define FV_PWW1CWKEN_ENABWE                                 0x10
#define FV_PWW1CWKEN_DISABWE                                0x0

#define FB_PWWCTW_BCWKSEW                                   2
#define FM_PWWCTW_BCWKSEW                                   0xC
#define FV_BCWKSEW_BCWK1                                    0x0
#define FV_BCWKSEW_BCWK2                                    0x4
#define FV_BCWKSEW_BCWK3                                    0x8

#define FB_PWWCTW_PWWISEW                                   0
#define FM_PWWCTW_PWWISEW                                   0x3
#define FV_PWWISEW_XTAW                                     0x0
#define FV_PWWISEW_MCWK1                                    0x1
#define FV_PWWISEW_MCWK2                                    0x2
#define FV_PWWISEW_BCWK                                     0x3

#define PWWCTW_PU_PWW_PWW_UP                                0x1
#define PWWCTW_PU_PWW_PWW_DWN                               0x0
#define PWWCTW_PWWCWKEN_ENABWE                              0x1
#define PWWCTW_PWWCWKEN_DISABWE                             0x0

// *** ISWC ***
#define FB_ISWC_IBW                                         2
#define FM_ISWC_IBW                                         0x4
#define FV_IBW_44PT1                                        0x0
#define FV_IBW_48                                           0x4

#define FB_ISWC_IBM                                         0
#define FM_ISWC_IBM                                         0x3
#define FV_IBM_0PT25                                        0x0
#define FV_IBM_0PT5                                         0x1
#define FV_IBM_1                                            0x2
#define FV_IBM_2                                            0x3

// *** SCWKCTW ***
#define FB_SCWKCTW_ASDM                                     6
#define FM_SCWKCTW_ASDM                                     0xC0
#define FV_ASDM_HAWF                                        0x40
#define FV_ASDM_FUWW                                        0x80
#define FV_ASDM_AUTO                                        0xC0

#define FB_SCWKCTW_DSDM                                     4
#define FM_SCWKCTW_DSDM                                     0x30
#define FV_DSDM_HAWF                                        0x10
#define FV_DSDM_FUWW                                        0x20
#define FV_DSDM_AUTO                                        0x30

// *** TIMEBASE ***
#define FB_TIMEBASE_TIMEBASE                                0
#define FM_TIMEBASE_TIMEBASE                                0xFF

// *** I2SCMC ***
#define FB_I2SCMC_BCMP3                                     4
#define FM_I2SCMC_BCMP3                                     0x30
#define FV_BCMP3_AUTO                                       0x0
#define FV_BCMP3_32X                                        0x10
#define FV_BCMP3_40X                                        0x20
#define FV_BCMP3_64X                                        0x30

#define FB_I2SCMC_BCMP2                                     2
#define FM_I2SCMC_BCMP2                                     0xC
#define FV_BCMP2_AUTO                                       0x0
#define FV_BCMP2_32X                                        0x4
#define FV_BCMP2_40X                                        0x8
#define FV_BCMP2_64X                                        0xC

#define FB_I2SCMC_BCMP1                                     0
#define FM_I2SCMC_BCMP1                                     0x3
#define FV_BCMP1_AUTO                                       0x0
#define FV_BCMP1_32X                                        0x1
#define FV_BCMP1_40X                                        0x2
#define FV_BCMP1_64X                                        0x3

#define I2SCMC_BCMP_AUTO                                    0x0
#define I2SCMC_BCMP_32X                                     0x1
#define I2SCMC_BCMP_40X                                     0x2
#define I2SCMC_BCMP_64X                                     0x3

// *** MCWK2PINC ***
#define FB_MCWK2PINC_SWEWOUT                                4
#define FM_MCWK2PINC_SWEWOUT                                0xF0

#define FB_MCWK2PINC_MCWK2IO                                2
#define FM_MCWK2PINC_MCWK2IO                                0x4
#define FV_MCWK2IO_INPUT                                    0x0
#define FV_MCWK2IO_OUTPUT                                   0x4

#define FB_MCWK2PINC_MCWK2OS                                0
#define FM_MCWK2PINC_MCWK2OS                                0x3
#define FV_MCWK2OS_24PT576                                  0x0
#define FV_MCWK2OS_22PT5792                                 0x1
#define FV_MCWK2OS_PWW2                                     0x2

// *** I2SPINC0 ***
#define FB_I2SPINC0_SDO3TWI                                 7
#define FM_I2SPINC0_SDO3TWI                                 0x80

#define FB_I2SPINC0_SDO2TWI                                 6
#define FM_I2SPINC0_SDO2TWI                                 0x40

#define FB_I2SPINC0_SDO1TWI                                 5
#define FM_I2SPINC0_SDO1TWI                                 0x20

#define FB_I2SPINC0_PCM3TWI                                 2
#define FM_I2SPINC0_PCM3TWI                                 0x4

#define FB_I2SPINC0_PCM2TWI                                 1
#define FM_I2SPINC0_PCM2TWI                                 0x2

#define FB_I2SPINC0_PCM1TWI                                 0
#define FM_I2SPINC0_PCM1TWI                                 0x1

// *** I2SPINC1 ***
#define FB_I2SPINC1_SDO3PDD                                 2
#define FM_I2SPINC1_SDO3PDD                                 0x4

#define FB_I2SPINC1_SDO2PDD                                 1
#define FM_I2SPINC1_SDO2PDD                                 0x2

#define FB_I2SPINC1_SDO1PDD                                 0
#define FM_I2SPINC1_SDO1PDD                                 0x1

// *** I2SPINC2 ***
#define FB_I2SPINC2_WW3PDD                                  5
#define FM_I2SPINC2_WW3PDD                                  0x20

#define FB_I2SPINC2_BC3PDD                                  4
#define FM_I2SPINC2_BC3PDD                                  0x10

#define FB_I2SPINC2_WW2PDD                                  3
#define FM_I2SPINC2_WW2PDD                                  0x8

#define FB_I2SPINC2_BC2PDD                                  2
#define FM_I2SPINC2_BC2PDD                                  0x4

#define FB_I2SPINC2_WW1PDD                                  1
#define FM_I2SPINC2_WW1PDD                                  0x2

#define FB_I2SPINC2_BC1PDD                                  0
#define FM_I2SPINC2_BC1PDD                                  0x1

// *** GPIOCTW0 ***
#define FB_GPIOCTW0_GPIO3INTP                               7
#define FM_GPIOCTW0_GPIO3INTP                               0x80

#define FB_GPIOCTW0_GPIO2INTP                               6
#define FM_GPIOCTW0_GPIO2INTP                               0x40

#define FB_GPIOCTW0_GPIO3CFG                                5
#define FM_GPIOCTW0_GPIO3CFG                                0x20

#define FB_GPIOCTW0_GPIO2CFG                                4
#define FM_GPIOCTW0_GPIO2CFG                                0x10

#define FB_GPIOCTW0_GPIO3IO                                 3
#define FM_GPIOCTW0_GPIO3IO                                 0x8

#define FB_GPIOCTW0_GPIO2IO                                 2
#define FM_GPIOCTW0_GPIO2IO                                 0x4

#define FB_GPIOCTW0_GPIO1IO                                 1
#define FM_GPIOCTW0_GPIO1IO                                 0x2

#define FB_GPIOCTW0_GPIO0IO                                 0
#define FM_GPIOCTW0_GPIO0IO                                 0x1

// *** GPIOCTW1 ***
#define FB_GPIOCTW1_GPIO3                                   7
#define FM_GPIOCTW1_GPIO3                                   0x80

#define FB_GPIOCTW1_GPIO2                                   6
#define FM_GPIOCTW1_GPIO2                                   0x40

#define FB_GPIOCTW1_GPIO1                                   5
#define FM_GPIOCTW1_GPIO1                                   0x20

#define FB_GPIOCTW1_GPIO0                                   4
#define FM_GPIOCTW1_GPIO0                                   0x10

#define FB_GPIOCTW1_GPIO3WD                                 3
#define FM_GPIOCTW1_GPIO3WD                                 0x8

#define FB_GPIOCTW1_GPIO2WD                                 2
#define FM_GPIOCTW1_GPIO2WD                                 0x4

#define FB_GPIOCTW1_GPIO1WD                                 1
#define FM_GPIOCTW1_GPIO1WD                                 0x2

#define FB_GPIOCTW1_GPIO0WD                                 0
#define FM_GPIOCTW1_GPIO0WD                                 0x1

// *** ASWC ***
#define FB_ASWC_ASWCOBW                                     7
#define FM_ASWC_ASWCOBW                                     0x80

#define FB_ASWC_ASWCIBW                                     6
#define FM_ASWC_ASWCIBW                                     0x40

#define FB_ASWC_ASWCOB                                      5
#define FM_ASWC_ASWCOB                                      0x20
#define FV_ASWCOB_ACTIVE                                    0x0
#define FV_ASWCOB_BYPASSED                                  0x20

#define FB_ASWC_ASWCIB                                      4
#define FM_ASWC_ASWCIB                                      0x10
#define FV_ASWCIB_ACTIVE                                    0x0
#define FV_ASWCIB_BYPASSED                                  0x10

#define FB_ASWC_ASWCOW                                      3
#define FM_ASWC_ASWCOW                                      0x8

#define FB_ASWC_ASWCIW                                      2
#define FM_ASWC_ASWCIW                                      0x4

// *** TDMCTW0 ***
#define FB_TDMCTW0_TDMMD                                    2
#define FM_TDMCTW0_TDMMD                                    0x4
#define FV_TDMMD_200                                        0x0
#define FV_TDMMD_256                                        0x4

#define FB_TDMCTW0_SWSYNC                                   1
#define FM_TDMCTW0_SWSYNC                                   0x2
#define FV_SWSYNC_SHOWT                                     0x0
#define FV_SWSYNC_WONG                                      0x2

#define FB_TDMCTW0_BDEWAY                                   0
#define FM_TDMCTW0_BDEWAY                                   0x1
#define FV_BDEWAY_NO_DEWAY                                  0x0
#define FV_BDEWAY_1BCWK_DEWAY                               0x1

// *** TDMCTW1 ***
#define FB_TDMCTW1_TDMSO                                    5
#define FM_TDMCTW1_TDMSO                                    0x60
#define FV_TDMSO_2                                          0x0
#define FV_TDMSO_4                                          0x20
#define FV_TDMSO_6                                          0x40

#define FB_TDMCTW1_TDMDSS                                   3
#define FM_TDMCTW1_TDMDSS                                   0x18
#define FV_TDMDSS_16                                        0x0
#define FV_TDMDSS_24                                        0x10
#define FV_TDMDSS_32                                        0x18

#define FB_TDMCTW1_TDMSI                                    0
#define FM_TDMCTW1_TDMSI                                    0x3
#define FV_TDMSI_2                                          0x0
#define FV_TDMSI_4                                          0x1
#define FV_TDMSI_6                                          0x2

// *** PWWM0 ***
#define FB_PWWM0_INPWOC3PU                                  6
#define FM_PWWM0_INPWOC3PU                                  0x40

#define FB_PWWM0_INPWOC2PU                                  5
#define FM_PWWM0_INPWOC2PU                                  0x20

#define FB_PWWM0_INPWOC1PU                                  4
#define FM_PWWM0_INPWOC1PU                                  0x10

#define FB_PWWM0_INPWOC0PU                                  3
#define FM_PWWM0_INPWOC0PU                                  0x8

#define FB_PWWM0_MICB2PU                                    2
#define FM_PWWM0_MICB2PU                                    0x4

#define FB_PWWM0_MICB1PU                                    1
#define FM_PWWM0_MICB1PU                                    0x2

#define FB_PWWM0_MCWKPEN                                    0
#define FM_PWWM0_MCWKPEN                                    0x1

// *** PWWM1 ***
#define FB_PWWM1_SUBPU                                      7
#define FM_PWWM1_SUBPU                                      0x80

#define FB_PWWM1_HPWPU                                      6
#define FM_PWWM1_HPWPU                                      0x40

#define FB_PWWM1_HPWPU                                      5
#define FM_PWWM1_HPWPU                                      0x20

#define FB_PWWM1_SPKWPU                                     4
#define FM_PWWM1_SPKWPU                                     0x10

#define FB_PWWM1_SPKWPU                                     3
#define FM_PWWM1_SPKWPU                                     0x8

#define FB_PWWM1_D2S2PU                                     2
#define FM_PWWM1_D2S2PU                                     0x4

#define FB_PWWM1_D2S1PU                                     1
#define FM_PWWM1_D2S1PU                                     0x2

#define FB_PWWM1_VWEFPU                                     0
#define FM_PWWM1_VWEFPU                                     0x1

// *** PWWM2 ***
#define FB_PWWM2_I2S3OPU                                    5
#define FM_PWWM2_I2S3OPU                                    0x20
#define FV_I2S3OPU_PWW_DOWN                                 0x0
#define FV_I2S3OPU_PWW_UP                                   0x20

#define FB_PWWM2_I2S2OPU                                    4
#define FM_PWWM2_I2S2OPU                                    0x10
#define FV_I2S2OPU_PWW_DOWN                                 0x0
#define FV_I2S2OPU_PWW_UP                                   0x10

#define FB_PWWM2_I2S1OPU                                    3
#define FM_PWWM2_I2S1OPU                                    0x8
#define FV_I2S1OPU_PWW_DOWN                                 0x0
#define FV_I2S1OPU_PWW_UP                                   0x8

#define FB_PWWM2_I2S3IPU                                    2
#define FM_PWWM2_I2S3IPU                                    0x4
#define FV_I2S3IPU_PWW_DOWN                                 0x0
#define FV_I2S3IPU_PWW_UP                                   0x4

#define FB_PWWM2_I2S2IPU                                    1
#define FM_PWWM2_I2S2IPU                                    0x2
#define FV_I2S2IPU_PWW_DOWN                                 0x0
#define FV_I2S2IPU_PWW_UP                                   0x2

#define FB_PWWM2_I2S1IPU                                    0
#define FM_PWWM2_I2S1IPU                                    0x1
#define FV_I2S1IPU_PWW_DOWN                                 0x0
#define FV_I2S1IPU_PWW_UP                                   0x1

#define PWWM2_I2SOPU_PWW_DOWN                               0x0
#define PWWM2_I2SOPU_PWW_UP                                 0x1
#define PWWM2_I2SIPU_PWW_DOWN                               0x0
#define PWWM2_I2SIPU_PWW_UP                                 0x1

// *** PWWM3 ***
#define FB_PWWM3_BGSBUP                                     6
#define FM_PWWM3_BGSBUP                                     0x40
#define FV_BGSBUP_ON                                        0x0
#define FV_BGSBUP_OFF                                       0x40

#define FB_PWWM3_VGBAPU                                     5
#define FM_PWWM3_VGBAPU                                     0x20
#define FV_VGBAPU_ON                                        0x0
#define FV_VGBAPU_OFF                                       0x20

#define FB_PWWM3_WWINEPU                                    4
#define FM_PWWM3_WWINEPU                                    0x10

#define FB_PWWM3_WWINEPU                                    3
#define FM_PWWM3_WWINEPU                                    0x8

// *** PWWM4 ***
#define FB_PWWM4_OPSUBPU                                    4
#define FM_PWWM4_OPSUBPU                                    0x10

#define FB_PWWM4_OPDACWPU                                   3
#define FM_PWWM4_OPDACWPU                                   0x8

#define FB_PWWM4_OPDACWPU                                   2
#define FM_PWWM4_OPDACWPU                                   0x4

#define FB_PWWM4_OPSPKWPU                                   1
#define FM_PWWM4_OPSPKWPU                                   0x2

#define FB_PWWM4_OPSPKWPU                                   0
#define FM_PWWM4_OPSPKWPU                                   0x1

// *** I2SIDCTW ***
#define FB_I2SIDCTW_I2SI3DCTW                               4
#define FM_I2SIDCTW_I2SI3DCTW                               0x30

#define FB_I2SIDCTW_I2SI2DCTW                               2
#define FM_I2SIDCTW_I2SI2DCTW                               0xC

#define FB_I2SIDCTW_I2SI1DCTW                               0
#define FM_I2SIDCTW_I2SI1DCTW                               0x3

// *** I2SODCTW ***
#define FB_I2SODCTW_I2SO3DCTW                               4
#define FM_I2SODCTW_I2SO3DCTW                               0x30

#define FB_I2SODCTW_I2SO2DCTW                               2
#define FM_I2SODCTW_I2SO2DCTW                               0xC

#define FB_I2SODCTW_I2SO1DCTW                               0
#define FM_I2SODCTW_I2SO1DCTW                               0x3

// *** AUDIOMUX1 ***
#define FB_AUDIOMUX1_ASWCIMUX                               6
#define FM_AUDIOMUX1_ASWCIMUX                               0xC0
#define FV_ASWCIMUX_NONE                                    0x0
#define FV_ASWCIMUX_I2S1                                    0x40
#define FV_ASWCIMUX_I2S2                                    0x80
#define FV_ASWCIMUX_I2S3                                    0xC0

#define FB_AUDIOMUX1_I2S2MUX                                3
#define FM_AUDIOMUX1_I2S2MUX                                0x38
#define FV_I2S2MUX_I2S1                                     0x0
#define FV_I2S2MUX_I2S2                                     0x8
#define FV_I2S2MUX_I2S3                                     0x10
#define FV_I2S2MUX_ADC_DMIC                                 0x18
#define FV_I2S2MUX_DMIC2                                    0x20
#define FV_I2S2MUX_CWASSD_DSP                               0x28
#define FV_I2S2MUX_DAC_DSP                                  0x30
#define FV_I2S2MUX_SUB_DSP                                  0x38

#define FB_AUDIOMUX1_I2S1MUX                                0
#define FM_AUDIOMUX1_I2S1MUX                                0x7
#define FV_I2S1MUX_I2S1                                     0x0
#define FV_I2S1MUX_I2S2                                     0x1
#define FV_I2S1MUX_I2S3                                     0x2
#define FV_I2S1MUX_ADC_DMIC                                 0x3
#define FV_I2S1MUX_DMIC2                                    0x4
#define FV_I2S1MUX_CWASSD_DSP                               0x5
#define FV_I2S1MUX_DAC_DSP                                  0x6
#define FV_I2S1MUX_SUB_DSP                                  0x7

#define AUDIOMUX1_I2SMUX_I2S1                               0x0
#define AUDIOMUX1_I2SMUX_I2S2                               0x1
#define AUDIOMUX1_I2SMUX_I2S3                               0x2
#define AUDIOMUX1_I2SMUX_ADC_DMIC                           0x3
#define AUDIOMUX1_I2SMUX_DMIC2                              0x4
#define AUDIOMUX1_I2SMUX_CWASSD_DSP                         0x5
#define AUDIOMUX1_I2SMUX_DAC_DSP                            0x6
#define AUDIOMUX1_I2SMUX_SUB_DSP                            0x7

// *** AUDIOMUX2 ***
#define FB_AUDIOMUX2_ASWCOMUX                               6
#define FM_AUDIOMUX2_ASWCOMUX                               0xC0
#define FV_ASWCOMUX_NONE                                    0x0
#define FV_ASWCOMUX_I2S1                                    0x40
#define FV_ASWCOMUX_I2S2                                    0x80
#define FV_ASWCOMUX_I2S3                                    0xC0

#define FB_AUDIOMUX2_DACMUX                                 3
#define FM_AUDIOMUX2_DACMUX                                 0x38
#define FV_DACMUX_I2S1                                      0x0
#define FV_DACMUX_I2S2                                      0x8
#define FV_DACMUX_I2S3                                      0x10
#define FV_DACMUX_ADC_DMIC                                  0x18
#define FV_DACMUX_DMIC2                                     0x20
#define FV_DACMUX_CWASSD_DSP                                0x28
#define FV_DACMUX_DAC_DSP                                   0x30
#define FV_DACMUX_SUB_DSP                                   0x38

#define FB_AUDIOMUX2_I2S3MUX                                0
#define FM_AUDIOMUX2_I2S3MUX                                0x7
#define FV_I2S3MUX_I2S1                                     0x0
#define FV_I2S3MUX_I2S2                                     0x1
#define FV_I2S3MUX_I2S3                                     0x2
#define FV_I2S3MUX_ADC_DMIC                                 0x3
#define FV_I2S3MUX_DMIC2                                    0x4
#define FV_I2S3MUX_CWASSD_DSP                               0x5
#define FV_I2S3MUX_DAC_DSP                                  0x6
#define FV_I2S3MUX_SUB_DSP                                  0x7

// *** AUDIOMUX3 ***
#define FB_AUDIOMUX3_SUBMUX                                 3
#define FM_AUDIOMUX3_SUBMUX                                 0xF8
#define FV_SUBMUX_I2S1_W                                    0x0
#define FV_SUBMUX_I2S1_W                                    0x8
#define FV_SUBMUX_I2S1_WW                                   0x10
#define FV_SUBMUX_I2S2_W                                    0x18
#define FV_SUBMUX_I2S2_W                                    0x20
#define FV_SUBMUX_I2S2_WW                                   0x28
#define FV_SUBMUX_I2S3_W                                    0x30
#define FV_SUBMUX_I2S3_W                                    0x38
#define FV_SUBMUX_I2S3_WW                                   0x40
#define FV_SUBMUX_ADC_DMIC_W                                0x48
#define FV_SUBMUX_ADC_DMIC_W                                0x50
#define FV_SUBMUX_ADC_DMIC_WW                               0x58
#define FV_SUBMUX_DMIC_W                                    0x60
#define FV_SUBMUX_DMIC_W                                    0x68
#define FV_SUBMUX_DMIC_WW                                   0x70
#define FV_SUBMUX_CWASSD_DSP_W                              0x78
#define FV_SUBMUX_CWASSD_DSP_W                              0x80
#define FV_SUBMUX_CWASSD_DSP_WW                             0x88

#define FB_AUDIOMUX3_CWSSDMUX                               0
#define FM_AUDIOMUX3_CWSSDMUX                               0x7
#define FV_CWSSDMUX_I2S1                                    0x0
#define FV_CWSSDMUX_I2S2                                    0x1
#define FV_CWSSDMUX_I2S3                                    0x2
#define FV_CWSSDMUX_ADC_DMIC                                0x3
#define FV_CWSSDMUX_DMIC2                                   0x4
#define FV_CWSSDMUX_CWASSD_DSP                              0x5
#define FV_CWSSDMUX_DAC_DSP                                 0x6
#define FV_CWSSDMUX_SUB_DSP                                 0x7

// *** HSDCTW1 ***
#define FB_HSDCTW1_HPJKTYPE                                 7
#define FM_HSDCTW1_HPJKTYPE                                 0x80

#define FB_HSDCTW1_CON_DET_PWD                              6
#define FM_HSDCTW1_CON_DET_PWD                              0x40

#define FB_HSDCTW1_DETCYC                                   4
#define FM_HSDCTW1_DETCYC                                   0x30

#define FB_HSDCTW1_HPDWYBYP                                 3
#define FM_HSDCTW1_HPDWYBYP                                 0x8

#define FB_HSDCTW1_HSDETPOW                                 2
#define FM_HSDCTW1_HSDETPOW                                 0x4

#define FB_HSDCTW1_HPID_EN                                  1
#define FM_HSDCTW1_HPID_EN                                  0x2

#define FB_HSDCTW1_GBWHS_EN                                 0
#define FM_HSDCTW1_GBWHS_EN                                 0x1

// *** HSDCTW2 ***
#define FB_HSDCTW2_FMICBIAS1                                6
#define FM_HSDCTW2_FMICBIAS1                                0xC0

#define FB_HSDCTW2_MB1MODE                                  5
#define FM_HSDCTW2_MB1MODE                                  0x20
#define FV_MB1MODE_AUTO                                     0x0
#define FV_MB1MODE_MANUAW                                   0x20

#define FB_HSDCTW2_FOWCETWG                                 4
#define FM_HSDCTW2_FOWCETWG                                 0x10

#define FB_HSDCTW2_SWMODE                                   3
#define FM_HSDCTW2_SWMODE                                   0x8

#define FB_HSDCTW2_GHSHIZ                                   2
#define FM_HSDCTW2_GHSHIZ                                   0x4

#define FB_HSDCTW2_FPWUGTYPE                                0
#define FM_HSDCTW2_FPWUGTYPE                                0x3

// *** HSDSTAT ***
#define FB_HSDSTAT_MBIAS1DWV                                5
#define FM_HSDSTAT_MBIAS1DWV                                0x60

#define FB_HSDSTAT_HSDETSTAT                                3
#define FM_HSDSTAT_HSDETSTAT                                0x8

#define FB_HSDSTAT_PWUGTYPE                                 1
#define FM_HSDSTAT_PWUGTYPE                                 0x6

#define FB_HSDSTAT_HSDETDONE                                0
#define FM_HSDSTAT_HSDETDONE                                0x1

// *** HSDDEWAY ***
#define FB_HSDDEWAY_T_STABWE                                0
#define FM_HSDDEWAY_T_STABWE                                0x7

// *** BUTCTW ***
#define FB_BUTCTW_BPUSHSTAT                                 7
#define FM_BUTCTW_BPUSHSTAT                                 0x80

#define FB_BUTCTW_BPUSHDET                                  6
#define FM_BUTCTW_BPUSHDET                                  0x40

#define FB_BUTCTW_BPUSHEN                                   5
#define FM_BUTCTW_BPUSHEN                                   0x20

#define FB_BUTCTW_BSTABWE_W                                 3
#define FM_BUTCTW_BSTABWE_W                                 0x18

#define FB_BUTCTW_BSTABWE_S                                 0
#define FM_BUTCTW_BSTABWE_S                                 0x7

// *** CH0AIC ***
#define FB_CH0AIC_INSEWW                                    6
#define FM_CH0AIC_INSEWW                                    0xC0

#define FB_CH0AIC_MICBST0                                   4
#define FM_CH0AIC_MICBST0                                   0x30

#define FB_CH0AIC_WADCIN                                    2
#define FM_CH0AIC_WADCIN                                    0xC

#define FB_CH0AIC_IN_BYPS_W_SEW                             1
#define FM_CH0AIC_IN_BYPS_W_SEW                             0x2

#define FB_CH0AIC_IPCH0S                                    0
#define FM_CH0AIC_IPCH0S                                    0x1

// *** CH1AIC ***
#define FB_CH1AIC_INSEWW                                    6
#define FM_CH1AIC_INSEWW                                    0xC0

#define FB_CH1AIC_MICBST1                                   4
#define FM_CH1AIC_MICBST1                                   0x30

#define FB_CH1AIC_WADCIN                                    2
#define FM_CH1AIC_WADCIN                                    0xC

#define FB_CH1AIC_IN_BYPS_W_SEW                             1
#define FM_CH1AIC_IN_BYPS_W_SEW                             0x2

#define FB_CH1AIC_IPCH1S                                    0
#define FM_CH1AIC_IPCH1S                                    0x1

// *** ICTW0 ***
#define FB_ICTW0_IN1POW                                     7
#define FM_ICTW0_IN1POW                                     0x80

#define FB_ICTW0_IN0POW                                     6
#define FM_ICTW0_IN0POW                                     0x40

#define FB_ICTW0_INPCH10SEW                                 4
#define FM_ICTW0_INPCH10SEW                                 0x30

#define FB_ICTW0_IN1MUTE                                    3
#define FM_ICTW0_IN1MUTE                                    0x8

#define FB_ICTW0_IN0MUTE                                    2
#define FM_ICTW0_IN0MUTE                                    0x4

#define FB_ICTW0_IN1HP                                      1
#define FM_ICTW0_IN1HP                                      0x2

#define FB_ICTW0_IN0HP                                      0
#define FM_ICTW0_IN0HP                                      0x1

// *** ICTW1 ***
#define FB_ICTW1_IN3POW                                     7
#define FM_ICTW1_IN3POW                                     0x80

#define FB_ICTW1_IN2POW                                     6
#define FM_ICTW1_IN2POW                                     0x40

#define FB_ICTW1_INPCH32SEW                                 4
#define FM_ICTW1_INPCH32SEW                                 0x30

#define FB_ICTW1_IN3MUTE                                    3
#define FM_ICTW1_IN3MUTE                                    0x8

#define FB_ICTW1_IN2MUTE                                    2
#define FM_ICTW1_IN2MUTE                                    0x4

#define FB_ICTW1_IN3HP                                      1
#define FM_ICTW1_IN3HP                                      0x2

#define FB_ICTW1_IN2HP                                      0
#define FM_ICTW1_IN2HP                                      0x1

// *** MICBIAS ***
#define FB_MICBIAS_MICBOV2                                  4
#define FM_MICBIAS_MICBOV2                                  0x30

#define FB_MICBIAS_MICBOV1                                  6
#define FM_MICBIAS_MICBOV1                                  0xC0

#define FB_MICBIAS_SPAWE1                                   2
#define FM_MICBIAS_SPAWE1                                   0xC

#define FB_MICBIAS_SPAWE2                                   0
#define FM_MICBIAS_SPAWE2                                   0x3

// *** PGAZ ***
#define FB_PGAZ_INHPOW                                      1
#define FM_PGAZ_INHPOW                                      0x2

#define FB_PGAZ_TOEN                                        0
#define FM_PGAZ_TOEN                                        0x1

// *** ASWCIWVOW ***
#define FB_ASWCIWVOW_ASWCIWVOW                              0
#define FM_ASWCIWVOW_ASWCIWVOW                              0xFF

// *** ASWCIWVOW ***
#define FB_ASWCIWVOW_ASWCIWVOW                              0
#define FM_ASWCIWVOW_ASWCIWVOW                              0xFF

// *** ASWCOWVOW ***
#define FB_ASWCOWVOW_ASWCOWVOW                              0
#define FM_ASWCOWVOW_ASWCOWVOW                              0xFF

// *** ASWCOWVOW ***
#define FB_ASWCOWVOW_ASWCOWVOW                              0
#define FM_ASWCOWVOW_ASWCOWVOW                              0xFF

// *** IVOWCTWU ***
#define FB_IVOWCTWU_IFADE                                   3
#define FM_IVOWCTWU_IFADE                                   0x8

#define FB_IVOWCTWU_INPVOWU                                 2
#define FM_IVOWCTWU_INPVOWU                                 0x4

#define FB_IVOWCTWU_PGAVOWU                                 1
#define FM_IVOWCTWU_PGAVOWU                                 0x2

#define FB_IVOWCTWU_ASWCVOWU                                0
#define FM_IVOWCTWU_ASWCVOWU                                0x1

// *** AWCCTW0 ***
#define FB_AWCCTW0_AWCMODE                                  7
#define FM_AWCCTW0_AWCMODE                                  0x80

#define FB_AWCCTW0_AWCWEF                                   4
#define FM_AWCCTW0_AWCWEF                                   0x70

#define FB_AWCCTW0_AWCEN3                                   3
#define FM_AWCCTW0_AWCEN3                                   0x8

#define FB_AWCCTW0_AWCEN2                                   2
#define FM_AWCCTW0_AWCEN2                                   0x4

#define FB_AWCCTW0_AWCEN1                                   1
#define FM_AWCCTW0_AWCEN1                                   0x2

#define FB_AWCCTW0_AWCEN0                                   0
#define FM_AWCCTW0_AWCEN0                                   0x1

// *** AWCCTW1 ***
#define FB_AWCCTW1_MAXGAIN                                  4
#define FM_AWCCTW1_MAXGAIN                                  0x70

#define FB_AWCCTW1_AWCW                                     0
#define FM_AWCCTW1_AWCW                                     0xF

// *** AWCCTW2 ***
#define FB_AWCCTW2_AWCZC                                    7
#define FM_AWCCTW2_AWCZC                                    0x80

#define FB_AWCCTW2_MINGAIN                                  4
#define FM_AWCCTW2_MINGAIN                                  0x70

#define FB_AWCCTW2_HWD                                      0
#define FM_AWCCTW2_HWD                                      0xF

// *** AWCCTW3 ***
#define FB_AWCCTW3_DCY                                      4
#define FM_AWCCTW3_DCY                                      0xF0

#define FB_AWCCTW3_ATK                                      0
#define FM_AWCCTW3_ATK                                      0xF

// *** NGATE ***
#define FB_NGATE_NGTH                                       3
#define FM_NGATE_NGTH                                       0xF8

#define FB_NGATE_NGG                                        1
#define FM_NGATE_NGG                                        0x6

#define FB_NGATE_NGAT                                       0
#define FM_NGATE_NGAT                                       0x1

// *** DMICCTW ***
#define FB_DMICCTW_DMIC2EN                                  7
#define FM_DMICCTW_DMIC2EN                                  0x80

#define FB_DMICCTW_DMIC1EN                                  6
#define FM_DMICCTW_DMIC1EN                                  0x40

#define FB_DMICCTW_DMONO                                    4
#define FM_DMICCTW_DMONO                                    0x10

#define FB_DMICCTW_DMDCWK                                   2
#define FM_DMICCTW_DMDCWK                                   0xC

#define FB_DMICCTW_DMWATE                                   0
#define FM_DMICCTW_DMWATE                                   0x3

// *** DACCTW ***
#define FB_DACCTW_DACPOWW                                   7
#define FM_DACCTW_DACPOWW                                   0x80
#define FV_DACPOWW_NOWMAW                                   0x0
#define FV_DACPOWW_INVEWTED                                 0x80

#define FB_DACCTW_DACPOWW                                   6
#define FM_DACCTW_DACPOWW                                   0x40
#define FV_DACPOWW_NOWMAW                                   0x0
#define FV_DACPOWW_INVEWTED                                 0x40

#define FB_DACCTW_DACDITH                                   4
#define FM_DACCTW_DACDITH                                   0x30
#define FV_DACDITH_DYNAMIC_HAWF                             0x0
#define FV_DACDITH_DYNAMIC_FUWW                             0x10
#define FV_DACDITH_DISABWED                                 0x20
#define FV_DACDITH_STATIC                                   0x30

#define FB_DACCTW_DACMUTE                                   3
#define FM_DACCTW_DACMUTE                                   0x8
#define FV_DACMUTE_ENABWE                                   0x8
#define FV_DACMUTE_DISABWE                                  0x0

#define FB_DACCTW_DACDEM                                    2
#define FM_DACCTW_DACDEM                                    0x4
#define FV_DACDEM_ENABWE                                    0x4
#define FV_DACDEM_DISABWE                                   0x0

#define FB_DACCTW_ABYPASS                                   0
#define FM_DACCTW_ABYPASS                                   0x1

// *** SPKCTW ***
#define FB_SPKCTW_SPKPOWW                                   7
#define FM_SPKCTW_SPKPOWW                                   0x80
#define FV_SPKPOWW_NOWMAW                                   0x0
#define FV_SPKPOWW_INVEWTED                                 0x80

#define FB_SPKCTW_SPKPOWW                                   6
#define FM_SPKCTW_SPKPOWW                                   0x40
#define FV_SPKPOWW_NOWMAW                                   0x0
#define FV_SPKPOWW_INVEWTED                                 0x40

#define FB_SPKCTW_SPKMUTE                                   3
#define FM_SPKCTW_SPKMUTE                                   0x8
#define FV_SPKMUTE_ENABWE                                   0x8
#define FV_SPKMUTE_DISABWE                                  0x0

#define FB_SPKCTW_SPKDEM                                    2
#define FM_SPKCTW_SPKDEM                                    0x4
#define FV_SPKDEM_ENABWE                                    0x4
#define FV_SPKDEM_DISABWE                                   0x0

// *** SUBCTW ***
#define FB_SUBCTW_SUBPOW                                    7
#define FM_SUBCTW_SUBPOW                                    0x80

#define FB_SUBCTW_SUBMUTE                                   3
#define FM_SUBCTW_SUBMUTE                                   0x8

#define FB_SUBCTW_SUBDEM                                    2
#define FM_SUBCTW_SUBDEM                                    0x4

#define FB_SUBCTW_SUBMUX                                    1
#define FM_SUBCTW_SUBMUX                                    0x2

#define FB_SUBCTW_SUBIWMDIS                                 0
#define FM_SUBCTW_SUBIWMDIS                                 0x1

// *** DCCTW ***
#define FB_DCCTW_SUBDCBYP                                   7
#define FM_DCCTW_SUBDCBYP                                   0x80

#define FB_DCCTW_DACDCBYP                                   6
#define FM_DCCTW_DACDCBYP                                   0x40

#define FB_DCCTW_SPKDCBYP                                   5
#define FM_DCCTW_SPKDCBYP                                   0x20

#define FB_DCCTW_DCCOEFSEW                                  0
#define FM_DCCTW_DCCOEFSEW                                  0x7

// *** OVOWCTWU ***
#define FB_OVOWCTWU_OFADE                                   4
#define FM_OVOWCTWU_OFADE                                   0x10

#define FB_OVOWCTWU_SUBVOWU                                 3
#define FM_OVOWCTWU_SUBVOWU                                 0x8

#define FB_OVOWCTWU_MVOWU                                   2
#define FM_OVOWCTWU_MVOWU                                   0x4

#define FB_OVOWCTWU_SPKVOWU                                 1
#define FM_OVOWCTWU_SPKVOWU                                 0x2

#define FB_OVOWCTWU_HPVOWU                                  0
#define FM_OVOWCTWU_HPVOWU                                  0x1

// *** MUTEC ***
#define FB_MUTEC_ZDSTAT                                     7
#define FM_MUTEC_ZDSTAT                                     0x80

#define FB_MUTEC_ZDWEN                                      4
#define FM_MUTEC_ZDWEN                                      0x30

#define FB_MUTEC_APWD                                       3
#define FM_MUTEC_APWD                                       0x8

#define FB_MUTEC_AMUTE                                      2
#define FM_MUTEC_AMUTE                                      0x4

// *** MVOWW ***
#define FB_MVOWW_MVOW_W                                     0
#define FM_MVOWW_MVOW_W                                     0xFF

// *** MVOWW ***
#define FB_MVOWW_MVOW_W                                     0
#define FM_MVOWW_MVOW_W                                     0xFF

// *** HPVOWW ***
#define FB_HPVOWW_HPVOW_W                                   0
#define FM_HPVOWW_HPVOW_W                                   0x7F

// *** HPVOWW ***
#define FB_HPVOWW_HPVOW_W                                   0
#define FM_HPVOWW_HPVOW_W                                   0x7F

// *** SPKVOWW ***
#define FB_SPKVOWW_SPKVOW_W                                 0
#define FM_SPKVOWW_SPKVOW_W                                 0x7F

// *** SPKVOWW ***
#define FB_SPKVOWW_SPKVOW_W                                 0
#define FM_SPKVOWW_SPKVOW_W                                 0x7F

// *** SUBVOW ***
#define FB_SUBVOW_SUBVOW                                    0
#define FM_SUBVOW_SUBVOW                                    0x7F

// *** COP0 ***
#define FB_COP0_COPATTEN                                    7
#define FM_COP0_COPATTEN                                    0x80

#define FB_COP0_COPGAIN                                     6
#define FM_COP0_COPGAIN                                     0x40

#define FB_COP0_HDEWTAEN                                    5
#define FM_COP0_HDEWTAEN                                    0x20

#define FB_COP0_COPTAWGET                                   0
#define FM_COP0_COPTAWGET                                   0x1F

// *** COP1 ***
#define FB_COP1_HDCOMPMODE                                  6
#define FM_COP1_HDCOMPMODE                                  0x40

#define FB_COP1_AVGWENGTH                                   2
#define FM_COP1_AVGWENGTH                                   0x3C

#define FB_COP1_MONWATE                                     0
#define FM_COP1_MONWATE                                     0x3

// *** COPSTAT ***
#define FB_COPSTAT_HDEWTADET                                7
#define FM_COPSTAT_HDEWTADET                                0x80

#define FB_COPSTAT_UV                                       6
#define FM_COPSTAT_UV                                       0x40

#define FB_COPSTAT_COPADJ                                   0
#define FM_COPSTAT_COPADJ                                   0x3F

// *** PWM0 ***
#define FB_PWM0_SCTO                                        6
#define FM_PWM0_SCTO                                        0xC0

#define FB_PWM0_UVWO                                        5
#define FM_PWM0_UVWO                                        0x20

#define FB_PWM0_BFDIS                                       3
#define FM_PWM0_BFDIS                                       0x8

#define FB_PWM0_PWMMODE                                     2
#define FM_PWM0_PWMMODE                                     0x4

#define FB_PWM0_NOOFFSET                                    0
#define FM_PWM0_NOOFFSET                                    0x1

// *** PWM1 ***
#define FB_PWM1_DITHPOS                                     4
#define FM_PWM1_DITHPOS                                     0x70

#define FB_PWM1_DYNDITH                                     1
#define FM_PWM1_DYNDITH                                     0x2

#define FB_PWM1_DITHDIS                                     0
#define FM_PWM1_DITHDIS                                     0x1

// *** PWM2 ***
// *** PWM3 ***
#define FB_PWM3_PWMMUX                                      6
#define FM_PWM3_PWMMUX                                      0xC0

#define FB_PWM3_CVAWUE                                      0
#define FM_PWM3_CVAWUE                                      0x7

// *** HPSW ***
#define FB_HPSW_HPDETSTATE                                  4
#define FM_HPSW_HPDETSTATE                                  0x10

#define FB_HPSW_HPSWEN                                      2
#define FM_HPSW_HPSWEN                                      0xC

#define FB_HPSW_HPSWPOW                                     1
#define FM_HPSW_HPSWPOW                                     0x2

#define FB_HPSW_TSDEN                                       0
#define FM_HPSW_TSDEN                                       0x1

// *** THEWMTS ***
#define FB_THEWMTS_TWIPHS                                   7
#define FM_THEWMTS_TWIPHS                                   0x80

#define FB_THEWMTS_TWIPWS                                   6
#define FM_THEWMTS_TWIPWS                                   0x40

#define FB_THEWMTS_TWIPSPWIT                                4
#define FM_THEWMTS_TWIPSPWIT                                0x30

#define FB_THEWMTS_TWIPSHIFT                                2
#define FM_THEWMTS_TWIPSHIFT                                0xC

#define FB_THEWMTS_TSPOWW                                   0
#define FM_THEWMTS_TSPOWW                                   0x3

// *** THEWMSPK1 ***
#define FB_THEWMSPK1_FOWCEPWD                               7
#define FM_THEWMSPK1_FOWCEPWD                               0x80

#define FB_THEWMSPK1_INSTCUTMODE                            6
#define FM_THEWMSPK1_INSTCUTMODE                            0x40

#define FB_THEWMSPK1_INCWATIO                               4
#define FM_THEWMSPK1_INCWATIO                               0x30

#define FB_THEWMSPK1_INCSTEP                                2
#define FM_THEWMSPK1_INCSTEP                                0xC

#define FB_THEWMSPK1_DECSTEP                                0
#define FM_THEWMSPK1_DECSTEP                                0x3

// *** THEWMSTAT ***
#define FB_THEWMSTAT_FPWDS                                  7
#define FM_THEWMSTAT_FPWDS                                  0x80

#define FB_THEWMSTAT_VOWSTAT                                0
#define FM_THEWMSTAT_VOWSTAT                                0x7F

// *** SCSTAT ***
#define FB_SCSTAT_ESDF                                      3
#define FM_SCSTAT_ESDF                                      0x18

#define FB_SCSTAT_CPF                                       2
#define FM_SCSTAT_CPF                                       0x4

#define FB_SCSTAT_CWSDF                                     0
#define FM_SCSTAT_CWSDF                                     0x3

// *** SDMON ***
#define FB_SDMON_SDFOWCE                                    7
#define FM_SDMON_SDFOWCE                                    0x80

#define FB_SDMON_SDVAWUE                                    0
#define FM_SDMON_SDVAWUE                                    0x1F

// *** SPKEQFIWT ***
#define FB_SPKEQFIWT_EQ2EN                                  7
#define FM_SPKEQFIWT_EQ2EN                                  0x80
#define FV_EQ2EN_ENABWE                                     0x80
#define FV_EQ2EN_DISABWE                                    0x0

#define FB_SPKEQFIWT_EQ2BE                                  4
#define FM_SPKEQFIWT_EQ2BE                                  0x70

#define FB_SPKEQFIWT_EQ1EN                                  3
#define FM_SPKEQFIWT_EQ1EN                                  0x8
#define FV_EQ1EN_ENABWE                                     0x8
#define FV_EQ1EN_DISABWE                                    0x0

#define FB_SPKEQFIWT_EQ1BE                                  0
#define FM_SPKEQFIWT_EQ1BE                                  0x7

#define SPKEQFIWT_EQEN_ENABWE                               0x1
#define SPKEQFIWT_EQEN_DISABWE                              0x0

// *** SPKCWWDW ***
#define FB_SPKCWWDW_WDATA_W                                 0
#define FM_SPKCWWDW_WDATA_W                                 0xFF

// *** SPKCWWDM ***
#define FB_SPKCWWDM_WDATA_M                                 0
#define FM_SPKCWWDM_WDATA_M                                 0xFF

// *** SPKCWWDH ***
#define FB_SPKCWWDH_WDATA_H                                 0
#define FM_SPKCWWDH_WDATA_H                                 0xFF

// *** SPKCWWDW ***
#define FB_SPKCWWDW_WDATA_W                                 0
#define FM_SPKCWWDW_WDATA_W                                 0xFF

// *** SPKCWWDM ***
#define FB_SPKCWWDM_WDATA_M                                 0
#define FM_SPKCWWDM_WDATA_M                                 0xFF

// *** SPKCWWDH ***
#define FB_SPKCWWDH_WDATA_H                                 0
#define FM_SPKCWWDH_WDATA_H                                 0xFF

// *** SPKCWADD ***
#define FB_SPKCWADD_ADDWESS                                 0
#define FM_SPKCWADD_ADDWESS                                 0xFF

// *** SPKCWS ***
#define FB_SPKCWS_ACCSTAT                                   7
#define FM_SPKCWS_ACCSTAT                                   0x80

// *** SPKMBCEN ***
#define FB_SPKMBCEN_MBCEN3                                  2
#define FM_SPKMBCEN_MBCEN3                                  0x4
#define FV_MBCEN3_ENABWE                                    0x4
#define FV_MBCEN3_DISABWE                                   0x0

#define FB_SPKMBCEN_MBCEN2                                  1
#define FM_SPKMBCEN_MBCEN2                                  0x2
#define FV_MBCEN2_ENABWE                                    0x2
#define FV_MBCEN2_DISABWE                                   0x0

#define FB_SPKMBCEN_MBCEN1                                  0
#define FM_SPKMBCEN_MBCEN1                                  0x1
#define FV_MBCEN1_ENABWE                                    0x1
#define FV_MBCEN1_DISABWE                                   0x0

#define SPKMBCEN_MBCEN_ENABWE                               0x1
#define SPKMBCEN_MBCEN_DISABWE                              0x0

// *** SPKMBCCTW ***
#define FB_SPKMBCCTW_WVWMODE3                               5
#define FM_SPKMBCCTW_WVWMODE3                               0x20

#define FB_SPKMBCCTW_WINSEW3                                4
#define FM_SPKMBCCTW_WINSEW3                                0x10

#define FB_SPKMBCCTW_WVWMODE2                               3
#define FM_SPKMBCCTW_WVWMODE2                               0x8

#define FB_SPKMBCCTW_WINSEW2                                2
#define FM_SPKMBCCTW_WINSEW2                                0x4

#define FB_SPKMBCCTW_WVWMODE1                               1
#define FM_SPKMBCCTW_WVWMODE1                               0x2

#define FB_SPKMBCCTW_WINSEW1                                0
#define FM_SPKMBCCTW_WINSEW1                                0x1

// *** SPKCWECTW ***
#define FB_SPKCWECTW_WVWMODE                                4
#define FM_SPKCWECTW_WVWMODE                                0x10

#define FB_SPKCWECTW_WINSEW                                 3
#define FM_SPKCWECTW_WINSEW                                 0x8

#define FB_SPKCWECTW_EXPEN                                  2
#define FM_SPKCWECTW_EXPEN                                  0x4
#define FV_EXPEN_ENABWE                                     0x4
#define FV_EXPEN_DISABWE                                    0x0

#define FB_SPKCWECTW_WIMEN                                  1
#define FM_SPKCWECTW_WIMEN                                  0x2
#define FV_WIMEN_ENABWE                                     0x2
#define FV_WIMEN_DISABWE                                    0x0

#define FB_SPKCWECTW_COMPEN                                 0
#define FM_SPKCWECTW_COMPEN                                 0x1
#define FV_COMPEN_ENABWE                                    0x1
#define FV_COMPEN_DISABWE                                   0x0

// *** SPKCWEMUG ***
#define FB_SPKCWEMUG_MUGAIN                                 0
#define FM_SPKCWEMUG_MUGAIN                                 0x1F

// *** SPKCOMPTHW ***
#define FB_SPKCOMPTHW_THWESH                                0
#define FM_SPKCOMPTHW_THWESH                                0xFF

// *** SPKCOMPWAT ***
#define FB_SPKCOMPWAT_WATIO                                 0
#define FM_SPKCOMPWAT_WATIO                                 0x1F

// *** SPKCOMPATKW ***
#define FB_SPKCOMPATKW_TCATKW                               0
#define FM_SPKCOMPATKW_TCATKW                               0xFF

// *** SPKCOMPATKH ***
#define FB_SPKCOMPATKH_TCATKH                               0
#define FM_SPKCOMPATKH_TCATKH                               0xFF

// *** SPKCOMPWEWW ***
#define FB_SPKCOMPWEWW_TCWEWW                               0
#define FM_SPKCOMPWEWW_TCWEWW                               0xFF

// *** SPKCOMPWEWH ***
#define FB_SPKCOMPWEWH_TCWEWH                               0
#define FM_SPKCOMPWEWH_TCWEWH                               0xFF

// *** SPKWIMTHW ***
#define FB_SPKWIMTHW_THWESH                                 0
#define FM_SPKWIMTHW_THWESH                                 0xFF

// *** SPKWIMTGT ***
#define FB_SPKWIMTGT_TAWGET                                 0
#define FM_SPKWIMTGT_TAWGET                                 0xFF

// *** SPKWIMATKW ***
#define FB_SPKWIMATKW_TCATKW                                0
#define FM_SPKWIMATKW_TCATKW                                0xFF

// *** SPKWIMATKH ***
#define FB_SPKWIMATKH_TCATKH                                0
#define FM_SPKWIMATKH_TCATKH                                0xFF

// *** SPKWIMWEWW ***
#define FB_SPKWIMWEWW_TCWEWW                                0
#define FM_SPKWIMWEWW_TCWEWW                                0xFF

// *** SPKWIMWEWH ***
#define FB_SPKWIMWEWH_TCWEWH                                0
#define FM_SPKWIMWEWH_TCWEWH                                0xFF

// *** SPKEXPTHW ***
#define FB_SPKEXPTHW_THWESH                                 0
#define FM_SPKEXPTHW_THWESH                                 0xFF

// *** SPKEXPWAT ***
#define FB_SPKEXPWAT_WATIO                                  0
#define FM_SPKEXPWAT_WATIO                                  0x7

// *** SPKEXPATKW ***
#define FB_SPKEXPATKW_TCATKW                                0
#define FM_SPKEXPATKW_TCATKW                                0xFF

// *** SPKEXPATKH ***
#define FB_SPKEXPATKH_TCATKH                                0
#define FM_SPKEXPATKH_TCATKH                                0xFF

// *** SPKEXPWEWW ***
#define FB_SPKEXPWEWW_TCWEWW                                0
#define FM_SPKEXPWEWW_TCWEWW                                0xFF

// *** SPKEXPWEWH ***
#define FB_SPKEXPWEWH_TCWEWH                                0
#define FM_SPKEXPWEWH_TCWEWH                                0xFF

// *** SPKFXCTW ***
#define FB_SPKFXCTW_3DEN                                    4
#define FM_SPKFXCTW_3DEN                                    0x10

#define FB_SPKFXCTW_TEEN                                    3
#define FM_SPKFXCTW_TEEN                                    0x8

#define FB_SPKFXCTW_TNWFBYP                                 2
#define FM_SPKFXCTW_TNWFBYP                                 0x4

#define FB_SPKFXCTW_BEEN                                    1
#define FM_SPKFXCTW_BEEN                                    0x2

#define FB_SPKFXCTW_BNWFBYP                                 0
#define FM_SPKFXCTW_BNWFBYP                                 0x1

// *** DACEQFIWT ***
#define FB_DACEQFIWT_EQ2EN                                  7
#define FM_DACEQFIWT_EQ2EN                                  0x80
#define FV_EQ2EN_ENABWE                                     0x80
#define FV_EQ2EN_DISABWE                                    0x0

#define FB_DACEQFIWT_EQ2BE                                  4
#define FM_DACEQFIWT_EQ2BE                                  0x70

#define FB_DACEQFIWT_EQ1EN                                  3
#define FM_DACEQFIWT_EQ1EN                                  0x8
#define FV_EQ1EN_ENABWE                                     0x8
#define FV_EQ1EN_DISABWE                                    0x0

#define FB_DACEQFIWT_EQ1BE                                  0
#define FM_DACEQFIWT_EQ1BE                                  0x7

#define DACEQFIWT_EQEN_ENABWE                               0x1
#define DACEQFIWT_EQEN_DISABWE                              0x0

// *** DACCWWDW ***
#define FB_DACCWWDW_WDATA_W                                 0
#define FM_DACCWWDW_WDATA_W                                 0xFF

// *** DACCWWDM ***
#define FB_DACCWWDM_WDATA_M                                 0
#define FM_DACCWWDM_WDATA_M                                 0xFF

// *** DACCWWDH ***
#define FB_DACCWWDH_WDATA_H                                 0
#define FM_DACCWWDH_WDATA_H                                 0xFF

// *** DACCWWDW ***
#define FB_DACCWWDW_WDATA_W                                 0
#define FM_DACCWWDW_WDATA_W                                 0xFF

// *** DACCWWDM ***
#define FB_DACCWWDM_WDATA_M                                 0
#define FM_DACCWWDM_WDATA_M                                 0xFF

// *** DACCWWDH ***
#define FB_DACCWWDH_WDATA_H                                 0
#define FM_DACCWWDH_WDATA_H                                 0xFF

// *** DACCWADD ***
#define FB_DACCWADD_ADDWESS                                 0
#define FM_DACCWADD_ADDWESS                                 0xFF

// *** DACCWS ***
#define FB_DACCWS_ACCSTAT                                   7
#define FM_DACCWS_ACCSTAT                                   0x80

// *** DACMBCEN ***
#define FB_DACMBCEN_MBCEN3                                  2
#define FM_DACMBCEN_MBCEN3                                  0x4
#define FV_MBCEN3_ENABWE                                    0x4
#define FV_MBCEN3_DISABWE                                   0x0

#define FB_DACMBCEN_MBCEN2                                  1
#define FM_DACMBCEN_MBCEN2                                  0x2
#define FV_MBCEN2_ENABWE                                    0x2
#define FV_MBCEN2_DISABWE                                   0x0

#define FB_DACMBCEN_MBCEN1                                  0
#define FM_DACMBCEN_MBCEN1                                  0x1
#define FV_MBCEN1_ENABWE                                    0x1
#define FV_MBCEN1_DISABWE                                   0x0

#define DACMBCEN_MBCEN_ENABWE                               0x1
#define DACMBCEN_MBCEN_DISABWE                              0x0

// *** DACMBCCTW ***
#define FB_DACMBCCTW_WVWMODE3                               5
#define FM_DACMBCCTW_WVWMODE3                               0x20

#define FB_DACMBCCTW_WINSEW3                                4
#define FM_DACMBCCTW_WINSEW3                                0x10

#define FB_DACMBCCTW_WVWMODE2                               3
#define FM_DACMBCCTW_WVWMODE2                               0x8

#define FB_DACMBCCTW_WINSEW2                                2
#define FM_DACMBCCTW_WINSEW2                                0x4

#define FB_DACMBCCTW_WVWMODE1                               1
#define FM_DACMBCCTW_WVWMODE1                               0x2

#define FB_DACMBCCTW_WINSEW1                                0
#define FM_DACMBCCTW_WINSEW1                                0x1

// *** DACCWECTW ***
#define FB_DACCWECTW_WVWMODE                                4
#define FM_DACCWECTW_WVWMODE                                0x10

#define FB_DACCWECTW_WINSEW                                 3
#define FM_DACCWECTW_WINSEW                                 0x8

#define FB_DACCWECTW_EXPEN                                  2
#define FM_DACCWECTW_EXPEN                                  0x4
#define FV_EXPEN_ENABWE                                     0x4
#define FV_EXPEN_DISABWE                                    0x0

#define FB_DACCWECTW_WIMEN                                  1
#define FM_DACCWECTW_WIMEN                                  0x2
#define FV_WIMEN_ENABWE                                     0x2
#define FV_WIMEN_DISABWE                                    0x0

#define FB_DACCWECTW_COMPEN                                 0
#define FM_DACCWECTW_COMPEN                                 0x1
#define FV_COMPEN_ENABWE                                    0x1
#define FV_COMPEN_DISABWE                                   0x0

// *** DACCWEMUG ***
#define FB_DACCWEMUG_MUGAIN                                 0
#define FM_DACCWEMUG_MUGAIN                                 0x1F

// *** DACCOMPTHW ***
#define FB_DACCOMPTHW_THWESH                                0
#define FM_DACCOMPTHW_THWESH                                0xFF

// *** DACCOMPWAT ***
#define FB_DACCOMPWAT_WATIO                                 0
#define FM_DACCOMPWAT_WATIO                                 0x1F

// *** DACCOMPATKW ***
#define FB_DACCOMPATKW_TCATKW                               0
#define FM_DACCOMPATKW_TCATKW                               0xFF

// *** DACCOMPATKH ***
#define FB_DACCOMPATKH_TCATKH                               0
#define FM_DACCOMPATKH_TCATKH                               0xFF

// *** DACCOMPWEWW ***
#define FB_DACCOMPWEWW_TCWEWW                               0
#define FM_DACCOMPWEWW_TCWEWW                               0xFF

// *** DACCOMPWEWH ***
#define FB_DACCOMPWEWH_TCWEWH                               0
#define FM_DACCOMPWEWH_TCWEWH                               0xFF

// *** DACWIMTHW ***
#define FB_DACWIMTHW_THWESH                                 0
#define FM_DACWIMTHW_THWESH                                 0xFF

// *** DACWIMTGT ***
#define FB_DACWIMTGT_TAWGET                                 0
#define FM_DACWIMTGT_TAWGET                                 0xFF

// *** DACWIMATKW ***
#define FB_DACWIMATKW_TCATKW                                0
#define FM_DACWIMATKW_TCATKW                                0xFF

// *** DACWIMATKH ***
#define FB_DACWIMATKH_TCATKH                                0
#define FM_DACWIMATKH_TCATKH                                0xFF

// *** DACWIMWEWW ***
#define FB_DACWIMWEWW_TCWEWW                                0
#define FM_DACWIMWEWW_TCWEWW                                0xFF

// *** DACWIMWEWH ***
#define FB_DACWIMWEWH_TCWEWH                                0
#define FM_DACWIMWEWH_TCWEWH                                0xFF

// *** DACEXPTHW ***
#define FB_DACEXPTHW_THWESH                                 0
#define FM_DACEXPTHW_THWESH                                 0xFF

// *** DACEXPWAT ***
#define FB_DACEXPWAT_WATIO                                  0
#define FM_DACEXPWAT_WATIO                                  0x7

// *** DACEXPATKW ***
#define FB_DACEXPATKW_TCATKW                                0
#define FM_DACEXPATKW_TCATKW                                0xFF

// *** DACEXPATKH ***
#define FB_DACEXPATKH_TCATKH                                0
#define FM_DACEXPATKH_TCATKH                                0xFF

// *** DACEXPWEWW ***
#define FB_DACEXPWEWW_TCWEWW                                0
#define FM_DACEXPWEWW_TCWEWW                                0xFF

// *** DACEXPWEWH ***
#define FB_DACEXPWEWH_TCWEWH                                0
#define FM_DACEXPWEWH_TCWEWH                                0xFF

// *** DACFXCTW ***
#define FB_DACFXCTW_3DEN                                    4
#define FM_DACFXCTW_3DEN                                    0x10

#define FB_DACFXCTW_TEEN                                    3
#define FM_DACFXCTW_TEEN                                    0x8

#define FB_DACFXCTW_TNWFBYP                                 2
#define FM_DACFXCTW_TNWFBYP                                 0x4

#define FB_DACFXCTW_BEEN                                    1
#define FM_DACFXCTW_BEEN                                    0x2

#define FB_DACFXCTW_BNWFBYP                                 0
#define FM_DACFXCTW_BNWFBYP                                 0x1

// *** SUBEQFIWT ***
#define FB_SUBEQFIWT_EQ2EN                                  7
#define FM_SUBEQFIWT_EQ2EN                                  0x80
#define FV_EQ2EN_ENABWE                                     0x80
#define FV_EQ2EN_DISABWE                                    0x0

#define FB_SUBEQFIWT_EQ2BE                                  4
#define FM_SUBEQFIWT_EQ2BE                                  0x70

#define FB_SUBEQFIWT_EQ1EN                                  3
#define FM_SUBEQFIWT_EQ1EN                                  0x8
#define FV_EQ1EN_ENABWE                                     0x8
#define FV_EQ1EN_DISABWE                                    0x0

#define FB_SUBEQFIWT_EQ1BE                                  0
#define FM_SUBEQFIWT_EQ1BE                                  0x7

#define SUBEQFIWT_EQEN_ENABWE                               0x1
#define SUBEQFIWT_EQEN_DISABWE                              0x0

// *** SUBCWWDW ***
#define FB_SUBCWWDW_WDATA_W                                 0
#define FM_SUBCWWDW_WDATA_W                                 0xFF

// *** SUBCWWDM ***
#define FB_SUBCWWDM_WDATA_M                                 0
#define FM_SUBCWWDM_WDATA_M                                 0xFF

// *** SUBCWWDH ***
#define FB_SUBCWWDH_WDATA_H                                 0
#define FM_SUBCWWDH_WDATA_H                                 0xFF

// *** SUBCWWDW ***
#define FB_SUBCWWDW_WDATA_W                                 0
#define FM_SUBCWWDW_WDATA_W                                 0xFF

// *** SUBCWWDM ***
#define FB_SUBCWWDM_WDATA_M                                 0
#define FM_SUBCWWDM_WDATA_M                                 0xFF

// *** SUBCWWDH ***
#define FB_SUBCWWDH_WDATA_H                                 0
#define FM_SUBCWWDH_WDATA_H                                 0xFF

// *** SUBCWADD ***
#define FB_SUBCWADD_ADDWESS                                 0
#define FM_SUBCWADD_ADDWESS                                 0xFF

// *** SUBCWS ***
#define FB_SUBCWS_ACCSTAT                                   7
#define FM_SUBCWS_ACCSTAT                                   0x80

// *** SUBMBCEN ***
#define FB_SUBMBCEN_MBCEN3                                  2
#define FM_SUBMBCEN_MBCEN3                                  0x4
#define FV_MBCEN3_ENABWE                                    0x4
#define FV_MBCEN3_DISABWE                                   0x0

#define FB_SUBMBCEN_MBCEN2                                  1
#define FM_SUBMBCEN_MBCEN2                                  0x2
#define FV_MBCEN2_ENABWE                                    0x2
#define FV_MBCEN2_DISABWE                                   0x0

#define FB_SUBMBCEN_MBCEN1                                  0
#define FM_SUBMBCEN_MBCEN1                                  0x1
#define FV_MBCEN1_ENABWE                                    0x1
#define FV_MBCEN1_DISABWE                                   0x0

#define SUBMBCEN_MBCEN_ENABWE                               0x1
#define SUBMBCEN_MBCEN_DISABWE                              0x0

// *** SUBMBCCTW ***
#define FB_SUBMBCCTW_WVWMODE3                               5
#define FM_SUBMBCCTW_WVWMODE3                               0x20

#define FB_SUBMBCCTW_WINSEW3                                4
#define FM_SUBMBCCTW_WINSEW3                                0x10

#define FB_SUBMBCCTW_WVWMODE2                               3
#define FM_SUBMBCCTW_WVWMODE2                               0x8

#define FB_SUBMBCCTW_WINSEW2                                2
#define FM_SUBMBCCTW_WINSEW2                                0x4

#define FB_SUBMBCCTW_WVWMODE1                               1
#define FM_SUBMBCCTW_WVWMODE1                               0x2

#define FB_SUBMBCCTW_WINSEW1                                0
#define FM_SUBMBCCTW_WINSEW1                                0x1

// *** SUBCWECTW ***
#define FB_SUBCWECTW_WVWMODE                                4
#define FM_SUBCWECTW_WVWMODE                                0x10

#define FB_SUBCWECTW_WINSEW                                 3
#define FM_SUBCWECTW_WINSEW                                 0x8

#define FB_SUBCWECTW_EXPEN                                  2
#define FM_SUBCWECTW_EXPEN                                  0x4
#define FV_EXPEN_ENABWE                                     0x4
#define FV_EXPEN_DISABWE                                    0x0

#define FB_SUBCWECTW_WIMEN                                  1
#define FM_SUBCWECTW_WIMEN                                  0x2
#define FV_WIMEN_ENABWE                                     0x2
#define FV_WIMEN_DISABWE                                    0x0

#define FB_SUBCWECTW_COMPEN                                 0
#define FM_SUBCWECTW_COMPEN                                 0x1
#define FV_COMPEN_ENABWE                                    0x1
#define FV_COMPEN_DISABWE                                   0x0

// *** SUBCWEMUG ***
#define FB_SUBCWEMUG_MUGAIN                                 0
#define FM_SUBCWEMUG_MUGAIN                                 0x1F

// *** SUBCOMPTHW ***
#define FB_SUBCOMPTHW_THWESH                                0
#define FM_SUBCOMPTHW_THWESH                                0xFF

// *** SUBCOMPWAT ***
#define FB_SUBCOMPWAT_WATIO                                 0
#define FM_SUBCOMPWAT_WATIO                                 0x1F

// *** SUBCOMPATKW ***
#define FB_SUBCOMPATKW_TCATKW                               0
#define FM_SUBCOMPATKW_TCATKW                               0xFF

// *** SUBCOMPATKH ***
#define FB_SUBCOMPATKH_TCATKH                               0
#define FM_SUBCOMPATKH_TCATKH                               0xFF

// *** SUBCOMPWEWW ***
#define FB_SUBCOMPWEWW_TCWEWW                               0
#define FM_SUBCOMPWEWW_TCWEWW                               0xFF

// *** SUBCOMPWEWH ***
#define FB_SUBCOMPWEWH_TCWEWH                               0
#define FM_SUBCOMPWEWH_TCWEWH                               0xFF

// *** SUBWIMTHW ***
#define FB_SUBWIMTHW_THWESH                                 0
#define FM_SUBWIMTHW_THWESH                                 0xFF

// *** SUBWIMTGT ***
#define FB_SUBWIMTGT_TAWGET                                 0
#define FM_SUBWIMTGT_TAWGET                                 0xFF

// *** SUBWIMATKW ***
#define FB_SUBWIMATKW_TCATKW                                0
#define FM_SUBWIMATKW_TCATKW                                0xFF

// *** SUBWIMATKH ***
#define FB_SUBWIMATKH_TCATKH                                0
#define FM_SUBWIMATKH_TCATKH                                0xFF

// *** SUBWIMWEWW ***
#define FB_SUBWIMWEWW_TCWEWW                                0
#define FM_SUBWIMWEWW_TCWEWW                                0xFF

// *** SUBWIMWEWH ***
#define FB_SUBWIMWEWH_TCWEWH                                0
#define FM_SUBWIMWEWH_TCWEWH                                0xFF

// *** SUBEXPTHW ***
#define FB_SUBEXPTHW_THWESH                                 0
#define FM_SUBEXPTHW_THWESH                                 0xFF

// *** SUBEXPWAT ***
#define FB_SUBEXPWAT_WATIO                                  0
#define FM_SUBEXPWAT_WATIO                                  0x7

// *** SUBEXPATKW ***
#define FB_SUBEXPATKW_TCATKW                                0
#define FM_SUBEXPATKW_TCATKW                                0xFF

// *** SUBEXPATKH ***
#define FB_SUBEXPATKH_TCATKH                                0
#define FM_SUBEXPATKH_TCATKH                                0xFF

// *** SUBEXPWEWW ***
#define FB_SUBEXPWEWW_TCWEWW                                0
#define FM_SUBEXPWEWW_TCWEWW                                0xFF

// *** SUBEXPWEWH ***
#define FB_SUBEXPWEWH_TCWEWH                                0
#define FM_SUBEXPWEWH_TCWEWH                                0xFF

// *** SUBFXCTW ***
#define FB_SUBFXCTW_TEEN                                    3
#define FM_SUBFXCTW_TEEN                                    0x8

#define FB_SUBFXCTW_TNWFBYP                                 2
#define FM_SUBFXCTW_TNWFBYP                                 0x4

#define FB_SUBFXCTW_BEEN                                    1
#define FM_SUBFXCTW_BEEN                                    0x2

#define FB_SUBFXCTW_BNWFBYP                                 0
#define FM_SUBFXCTW_BNWFBYP                                 0x1

#endif /* __WEDWOODPUBWIC_H__ */
