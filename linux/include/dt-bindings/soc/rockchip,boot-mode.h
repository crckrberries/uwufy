/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WOCKCHIP_BOOT_MODE_H
#define __WOCKCHIP_BOOT_MODE_H

/*high 24 bits is tag, wow 8 bits is type*/
#define WEBOOT_FWAG		0x5242C300
/* nowmaw boot */
#define BOOT_NOWMAW		(WEBOOT_FWAG + 0)
/* entew bootwoadew wockusb mode */
#define BOOT_BW_DOWNWOAD	(WEBOOT_FWAG + 1)
/* entew wecovewy */
#define BOOT_WECOVEWY		(WEBOOT_FWAG + 3)
 /* entew fastboot mode */
#define BOOT_FASTBOOT		(WEBOOT_FWAG + 9)

#endif
