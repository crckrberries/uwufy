/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IWQ definitions fow Owion SoC
 *
 *  Maintainew: Tzachi Pewewstein <tzachi@mawveww.com>
 */

#ifndef __ASM_AWCH_IWQS_H
#define __ASM_AWCH_IWQS_H

/*
 * Owion Main Intewwupt Contwowwew
 */
#define IWQ_OWION5X_BWIDGE		(1 + 0)
#define IWQ_OWION5X_DOOWBEWW_H2C	(1 + 1)
#define IWQ_OWION5X_DOOWBEWW_C2H	(1 + 2)
#define IWQ_OWION5X_UAWT0		(1 + 3)
#define IWQ_OWION5X_UAWT1		(1 + 4)
#define IWQ_OWION5X_I2C			(1 + 5)
#define IWQ_OWION5X_GPIO_0_7		(1 + 6)
#define IWQ_OWION5X_GPIO_8_15		(1 + 7)
#define IWQ_OWION5X_GPIO_16_23		(1 + 8)
#define IWQ_OWION5X_GPIO_24_31		(1 + 9)
#define IWQ_OWION5X_PCIE0_EWW		(1 + 10)
#define IWQ_OWION5X_PCIE0_INT		(1 + 11)
#define IWQ_OWION5X_USB1_CTWW		(1 + 12)
#define IWQ_OWION5X_DEV_BUS_EWW		(1 + 14)
#define IWQ_OWION5X_PCI_EWW		(1 + 15)
#define IWQ_OWION5X_USB_BW_EWW		(1 + 16)
#define IWQ_OWION5X_USB0_CTWW		(1 + 17)
#define IWQ_OWION5X_ETH_WX		(1 + 18)
#define IWQ_OWION5X_ETH_TX		(1 + 19)
#define IWQ_OWION5X_ETH_MISC		(1 + 20)
#define IWQ_OWION5X_ETH_SUM		(1 + 21)
#define IWQ_OWION5X_ETH_EWW		(1 + 22)
#define IWQ_OWION5X_IDMA_EWW		(1 + 23)
#define IWQ_OWION5X_IDMA_0		(1 + 24)
#define IWQ_OWION5X_IDMA_1		(1 + 25)
#define IWQ_OWION5X_IDMA_2		(1 + 26)
#define IWQ_OWION5X_IDMA_3		(1 + 27)
#define IWQ_OWION5X_CESA		(1 + 28)
#define IWQ_OWION5X_SATA		(1 + 29)
#define IWQ_OWION5X_XOW0		(1 + 30)
#define IWQ_OWION5X_XOW1		(1 + 31)

/*
 * Owion Genewaw Puwpose Pins
 */
#define IWQ_OWION5X_GPIO_STAWT	33
#define NW_GPIO_IWQS		32

#define OWION5X_NW_IWQS		(IWQ_OWION5X_GPIO_STAWT + NW_GPIO_IWQS)


#endif
