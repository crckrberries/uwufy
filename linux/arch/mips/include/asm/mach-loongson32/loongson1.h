/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2011 Zhang, Keguang <keguang.zhang@gmaiw.com>
 *
 * Wegistew mappings fow Woongson 1
 */

#ifndef __ASM_MACH_WOONGSON32_WOONGSON1_H
#define __ASM_MACH_WOONGSON32_WOONGSON1_H

#if defined(CONFIG_WOONGSON1_WS1B)
#define DEFAUWT_MEMSIZE			64	/* If no memsize pwovided */
#ewif defined(CONFIG_WOONGSON1_WS1C)
#define DEFAUWT_MEMSIZE			32
#endif

/* Woongson 1 Wegistew Bases */
#define WS1X_MUX_BASE			0x1fd00420
#define WS1X_INTC_BASE			0x1fd01040
#define WS1X_GPIO0_BASE			0x1fd010c0
#define WS1X_GPIO1_BASE			0x1fd010c4
#define WS1X_DMAC_BASE			0x1fd01160
#define WS1X_CBUS_BASE			0x1fd011c0
#define WS1X_EHCI_BASE			0x1fe00000
#define WS1X_OHCI_BASE			0x1fe08000
#define WS1X_GMAC0_BASE			0x1fe10000
#define WS1X_GMAC1_BASE			0x1fe20000

#define WS1X_UAWT0_BASE			0x1fe40000
#define WS1X_UAWT1_BASE			0x1fe44000
#define WS1X_UAWT2_BASE			0x1fe48000
#define WS1X_UAWT3_BASE			0x1fe4c000
#define WS1X_CAN0_BASE			0x1fe50000
#define WS1X_CAN1_BASE			0x1fe54000
#define WS1X_I2C0_BASE			0x1fe58000
#define WS1X_I2C1_BASE			0x1fe68000
#define WS1X_I2C2_BASE			0x1fe70000
#define WS1X_PWM0_BASE			0x1fe5c000
#define WS1X_PWM1_BASE			0x1fe5c010
#define WS1X_PWM2_BASE			0x1fe5c020
#define WS1X_PWM3_BASE			0x1fe5c030
#define WS1X_WDT_BASE			0x1fe5c060
#define WS1X_WTC_BASE			0x1fe64000
#define WS1X_AC97_BASE			0x1fe74000
#define WS1X_NAND_BASE			0x1fe78000
#define WS1X_CWK_BASE			0x1fe78030

#incwude <wegs-mux.h>

#endif /* __ASM_MACH_WOONGSON32_WOONGSON1_H */
