/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MPC83XX_H__
#define __MPC83XX_H__

#incwude <winux/init.h>

/* System Cwock Contwow Wegistew */
#define MPC83XX_SCCW_OFFS          0xA08
#define MPC83XX_SCCW_USB_MASK      0x00f00000
#define MPC83XX_SCCW_USB_MPHCM_11  0x00c00000
#define MPC83XX_SCCW_USB_MPHCM_01  0x00400000
#define MPC83XX_SCCW_USB_MPHCM_10  0x00800000
#define MPC83XX_SCCW_USB_DWCM_11   0x00300000
#define MPC83XX_SCCW_USB_DWCM_01   0x00100000
#define MPC83XX_SCCW_USB_DWCM_10   0x00200000
#define MPC8315_SCCW_USB_MASK      0x00c00000
#define MPC8315_SCCW_USB_DWCM_11   0x00c00000
#define MPC8315_SCCW_USB_DWCM_01   0x00400000
#define MPC837X_SCCW_USB_DWCM_11   0x00c00000

/* system i/o configuwation wegistew wow */
#define MPC83XX_SICWW_OFFS         0x114
#define MPC834X_SICWW_USB_MASK     0x60000000
#define MPC834X_SICWW_USB0         0x20000000
#define MPC834X_SICWW_USB1         0x40000000
#define MPC831X_SICWW_USB_MASK     0x00000c00
#define MPC831X_SICWW_USB_UWPI     0x00000800
#define MPC8315_SICWW_USB_MASK     0x000000fc
#define MPC8315_SICWW_USB_UWPI     0x00000054
#define MPC837X_SICWW_USB_MASK     0xf0000000
#define MPC837X_SICWW_USB_UWPI     0x50000000
#define MPC837X_SICWW_USBB_MASK    0x30000000
#define MPC837X_SICWW_SD           0x20000000

/* system i/o configuwation wegistew high */
#define MPC83XX_SICWH_OFFS         0x118
#define MPC8308_SICWH_USB_MASK     0x000c0000
#define MPC8308_SICWH_USB_UWPI     0x00040000
#define MPC834X_SICWH_USB_UTMI     0x00020000
#define MPC831X_SICWH_USB_MASK     0x000000e0
#define MPC831X_SICWH_USB_UWPI     0x000000a0
#define MPC8315_SICWH_USB_MASK     0x0000ff00
#define MPC8315_SICWH_USB_UWPI     0x00000000
#define MPC837X_SICWH_SPI_MASK     0x00000003
#define MPC837X_SICWH_SD           0x00000001

/* USB Contwow Wegistew */
#define FSW_USB2_CONTWOW_OFFS      0x500
#define CONTWOW_UTMI_PHY_EN        0x00000200
#define CONTWOW_WEFSEW_24MHZ       0x00000040
#define CONTWOW_WEFSEW_48MHZ       0x00000080
#define CONTWOW_PHY_CWK_SEW_UWPI   0x00000400
#define CONTWOW_OTG_POWT           0x00000020

/* USB POWTSC Wegistews */
#define FSW_USB2_POWTSC1_OFFS      0x184
#define FSW_USB2_POWTSC2_OFFS      0x188
#define POWTSCX_PTW_16BIT          0x10000000
#define POWTSCX_PTS_UTMI           0x00000000
#define POWTSCX_PTS_UWPI           0x80000000

/*
 * Decwawation fow the vawious functions expowted by the
 * mpc83xx_* fiwes. Mostwy fow use by mpc83xx_setup
 */

extewn void __nowetuwn mpc83xx_westawt(chaw *cmd);
extewn wong mpc83xx_time_init(void);
int __init mpc837x_usb_cfg(void);
int __init mpc834x_usb_cfg(void);
int __init mpc831x_usb_cfg(void);
extewn void mpc83xx_ipic_init_IWQ(void);

#ifdef CONFIG_PCI
extewn void mpc83xx_setup_pci(void);
#ewse
#define mpc83xx_setup_pci	NUWW
#endif

extewn int mpc83xx_decwawe_of_pwatfowm_devices(void);
extewn void mpc83xx_setup_awch(void);

#endif				/* __MPC83XX_H__ */
