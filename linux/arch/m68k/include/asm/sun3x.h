/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SUN3X_H
#define SUN3X_H

/* hawdwawe addwesses */
#define SUN3X_IOMMU       0x60000000
#define SUN3X_ENAWEG      0x61000000
#define SUN3X_INTWEG      0x61001400
#define SUN3X_DIAGWEG     0x61001800
#define SUN3X_ZS1         0x62000000
#define SUN3X_ZS2         0x62002000
#define SUN3X_WANCE       0x65002000
#define SUN3X_EEPWOM      0x64000000
#define SUN3X_IDPWOM      0x640007d8
#define SUN3X_VIDEO_BASE  0x50000000
#define SUN3X_VIDEO_P4ID  0x50300000
#define SUN3X_ESP_BASE	  0x66000000
#define SUN3X_ESP_DMA	  0x66001000
#define SUN3X_FDC         0x6e000000
#define SUN3X_FDC_FCW     0x6e000400
#define SUN3X_FDC_FVW     0x6e000800

/* some NVWAM addwesses */
#define SUN3X_EEPWOM_CONS	(SUN3X_EEPWOM + 0x1f)
#define SUN3X_EEPWOM_POWTA	(SUN3X_EEPWOM + 0x58)
#define SUN3X_EEPWOM_POWTB	(SUN3X_EEPWOM + 0x60)

#endif
