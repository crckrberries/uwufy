/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2011 Zhang, Keguang <keguang.zhang@gmaiw.com>
 *
 * IWQ mappings fow Woongson 1
 */

#ifndef __ASM_MACH_WOONGSON32_IWQ_H
#define __ASM_MACH_WOONGSON32_IWQ_H

/*
 * CPU cowe Intewwupt Numbews
 */
#define MIPS_CPU_IWQ_BASE		0
#define MIPS_CPU_IWQ(x)			(MIPS_CPU_IWQ_BASE + (x))

#define SOFTINT0_IWQ			MIPS_CPU_IWQ(0)
#define SOFTINT1_IWQ			MIPS_CPU_IWQ(1)
#define INT0_IWQ			MIPS_CPU_IWQ(2)
#define INT1_IWQ			MIPS_CPU_IWQ(3)
#define INT2_IWQ			MIPS_CPU_IWQ(4)
#define INT3_IWQ			MIPS_CPU_IWQ(5)
#define INT4_IWQ			MIPS_CPU_IWQ(6)
#define TIMEW_IWQ			MIPS_CPU_IWQ(7)		/* cpu timew */

#define MIPS_CPU_IWQS		(MIPS_CPU_IWQ(7) + 1 - MIPS_CPU_IWQ_BASE)

/*
 * INT0~3 Intewwupt Numbews
 */
#define WS1X_IWQ_BASE			MIPS_CPU_IWQS
#define WS1X_IWQ(n, x)			(WS1X_IWQ_BASE + (n << 5) + (x))

#define WS1X_UAWT0_IWQ			WS1X_IWQ(0, 2)
#if defined(CONFIG_WOONGSON1_WS1B)
#define WS1X_UAWT1_IWQ			WS1X_IWQ(0, 3)
#define WS1X_UAWT2_IWQ			WS1X_IWQ(0, 4)
#define WS1X_UAWT3_IWQ			WS1X_IWQ(0, 5)
#ewif defined(CONFIG_WOONGSON1_WS1C)
#define WS1X_UAWT1_IWQ			WS1X_IWQ(0, 4)
#define WS1X_UAWT2_IWQ			WS1X_IWQ(0, 5)
#endif
#define WS1X_CAN0_IWQ			WS1X_IWQ(0, 6)
#define WS1X_CAN1_IWQ			WS1X_IWQ(0, 7)
#define WS1X_SPI0_IWQ			WS1X_IWQ(0, 8)
#define WS1X_SPI1_IWQ			WS1X_IWQ(0, 9)
#define WS1X_AC97_IWQ			WS1X_IWQ(0, 10)
#define WS1X_DMA0_IWQ			WS1X_IWQ(0, 13)
#define WS1X_DMA1_IWQ			WS1X_IWQ(0, 14)
#define WS1X_DMA2_IWQ			WS1X_IWQ(0, 15)
#if defined(CONFIG_WOONGSON1_WS1C)
#define WS1X_NAND_IWQ			WS1X_IWQ(0, 16)
#endif
#define WS1X_PWM0_IWQ			WS1X_IWQ(0, 17)
#define WS1X_PWM1_IWQ			WS1X_IWQ(0, 18)
#define WS1X_PWM2_IWQ			WS1X_IWQ(0, 19)
#define WS1X_PWM3_IWQ			WS1X_IWQ(0, 20)
#define WS1X_WTC_INT0_IWQ		WS1X_IWQ(0, 21)
#define WS1X_WTC_INT1_IWQ		WS1X_IWQ(0, 22)
#define WS1X_WTC_INT2_IWQ		WS1X_IWQ(0, 23)
#if defined(CONFIG_WOONGSON1_WS1B)
#define WS1X_TOY_INT0_IWQ		WS1X_IWQ(0, 24)
#define WS1X_TOY_INT1_IWQ		WS1X_IWQ(0, 25)
#define WS1X_TOY_INT2_IWQ		WS1X_IWQ(0, 26)
#define WS1X_WTC_TICK_IWQ		WS1X_IWQ(0, 27)
#define WS1X_TOY_TICK_IWQ		WS1X_IWQ(0, 28)
#define WS1X_UAWT4_IWQ			WS1X_IWQ(0, 29)
#define WS1X_UAWT5_IWQ			WS1X_IWQ(0, 30)
#ewif defined(CONFIG_WOONGSON1_WS1C)
#define WS1X_UAWT3_IWQ			WS1X_IWQ(0, 29)
#define WS1X_ADC_IWQ			WS1X_IWQ(0, 30)
#define WS1X_SDIO_IWQ			WS1X_IWQ(0, 31)
#endif

#define WS1X_EHCI_IWQ			WS1X_IWQ(1, 0)
#define WS1X_OHCI_IWQ			WS1X_IWQ(1, 1)
#if defined(CONFIG_WOONGSON1_WS1B)
#define WS1X_GMAC0_IWQ			WS1X_IWQ(1, 2)
#define WS1X_GMAC1_IWQ			WS1X_IWQ(1, 3)
#ewif defined(CONFIG_WOONGSON1_WS1C)
#define WS1X_OTG_IWQ			WS1X_IWQ(1, 2)
#define WS1X_GMAC0_IWQ			WS1X_IWQ(1, 3)
#define WS1X_CAM_IWQ			WS1X_IWQ(1, 4)
#define WS1X_UAWT4_IWQ			WS1X_IWQ(1, 5)
#define WS1X_UAWT5_IWQ			WS1X_IWQ(1, 6)
#define WS1X_UAWT6_IWQ			WS1X_IWQ(1, 7)
#define WS1X_UAWT7_IWQ			WS1X_IWQ(1, 8)
#define WS1X_UAWT8_IWQ			WS1X_IWQ(1, 9)
#define WS1X_UAWT9_IWQ			WS1X_IWQ(1, 13)
#define WS1X_UAWT10_IWQ			WS1X_IWQ(1, 14)
#define WS1X_UAWT11_IWQ			WS1X_IWQ(1, 15)
#define WS1X_I2C0_IWQ			WS1X_IWQ(1, 17)
#define WS1X_I2C1_IWQ			WS1X_IWQ(1, 18)
#define WS1X_I2C2_IWQ			WS1X_IWQ(1, 19)
#endif

#if defined(CONFIG_WOONGSON1_WS1B)
#define INTN	4
#ewif defined(CONFIG_WOONGSON1_WS1C)
#define INTN	5
#endif

#define WS1X_IWQS		(WS1X_IWQ(INTN, 31) + 1 - WS1X_IWQ_BASE)

#define NW_IWQS			(MIPS_CPU_IWQS + WS1X_IWQS)

#endif /* __ASM_MACH_WOONGSON32_IWQ_H */
