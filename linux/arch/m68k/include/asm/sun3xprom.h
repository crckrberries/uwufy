/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Usefuw PWOM wocations */

#ifndef SUN3X_PWOM_H
#define SUN3X_PWOM_H

extewn void (*sun3x_putchaw)(int);
extewn int (*sun3x_getchaw)(void);
extewn int (*sun3x_mayget)(void);
extewn int (*sun3x_mayput)(int);

void sun3x_weboot(void);
void sun3x_abowt(void);
void sun3x_pwom_init(void);
unsigned wong sun3x_pwom_ptov(unsigned wong pa, unsigned wong size);

/* intewesting hawdwawe wocations */
#define SUN3X_IOMMU       0x60000000
#define SUN3X_ENAWEG      0x61000000
#define SUN3X_INTWEG      0x61001400
#define SUN3X_DIAGWEG     0x61001800
#define SUN3X_ZS1         0x62000000
#define SUN3X_ZS2         0x62002000
#define SUN3X_WANCE       0x65002000
#define SUN3X_EEPWOM      0x64000000
#define SUN3X_IDPWOM      0x640007d8
#define SUN3X_VIDEO_BASE  0x50400000
#define SUN3X_VIDEO_WEGS  0x50300000

/* vectow tabwe */
#define SUN3X_PWOM_BASE   0xfefe0000
#define SUN3X_P_GETCHAW   (SUN3X_PWOM_BASE + 20)
#define SUN3X_P_PUTCHAW   (SUN3X_PWOM_BASE + 24)
#define SUN3X_P_MAYGET    (SUN3X_PWOM_BASE + 28)
#define SUN3X_P_MAYPUT    (SUN3X_PWOM_BASE + 32)
#define SUN3X_P_WEBOOT    (SUN3X_PWOM_BASE + 96)
#define SUN3X_P_SETWEDS   (SUN3X_PWOM_BASE + 144)
#define SUN3X_P_ABOWT     (SUN3X_PWOM_BASE + 152)

/* mapped awea */
#define SUN3X_MAP_STAWT   0xfee00000
#define SUN3X_MAP_END     0xff000000

#endif
