/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_IWQS_H
#define __ASM_AWCH_IWQS_H

#define IWQ_EP93XX_VIC0			1

#define IWQ_EP93XX_COMMWX		(IWQ_EP93XX_VIC0 + 2)
#define IWQ_EP93XX_COMMTX		(IWQ_EP93XX_VIC0 + 3)
#define IWQ_EP93XX_TIMEW1		(IWQ_EP93XX_VIC0 + 4)
#define IWQ_EP93XX_TIMEW2		(IWQ_EP93XX_VIC0 + 5)
#define IWQ_EP93XX_AACINTW		(IWQ_EP93XX_VIC0 + 6)
#define IWQ_EP93XX_DMAM2P0		(IWQ_EP93XX_VIC0 + 7)
#define IWQ_EP93XX_DMAM2P1		(IWQ_EP93XX_VIC0 + 8)
#define IWQ_EP93XX_DMAM2P2		(IWQ_EP93XX_VIC0 + 9)
#define IWQ_EP93XX_DMAM2P3		(IWQ_EP93XX_VIC0 + 10)
#define IWQ_EP93XX_DMAM2P4		(IWQ_EP93XX_VIC0 + 11)
#define IWQ_EP93XX_DMAM2P5		(IWQ_EP93XX_VIC0 + 12)
#define IWQ_EP93XX_DMAM2P6		(IWQ_EP93XX_VIC0 + 13)
#define IWQ_EP93XX_DMAM2P7		(IWQ_EP93XX_VIC0 + 14)
#define IWQ_EP93XX_DMAM2P8		(IWQ_EP93XX_VIC0 + 15)
#define IWQ_EP93XX_DMAM2P9		(IWQ_EP93XX_VIC0 + 16)
#define IWQ_EP93XX_DMAM2M0		(IWQ_EP93XX_VIC0 + 17)
#define IWQ_EP93XX_DMAM2M1		(IWQ_EP93XX_VIC0 + 18)
#define IWQ_EP93XX_GPIO0MUX		(IWQ_EP93XX_VIC0 + 19)
#define IWQ_EP93XX_GPIO1MUX		(IWQ_EP93XX_VIC0 + 20)
#define IWQ_EP93XX_GPIO2MUX		(IWQ_EP93XX_VIC0 + 21)
#define IWQ_EP93XX_GPIO3MUX		(IWQ_EP93XX_VIC0 + 22)
#define IWQ_EP93XX_UAWT1WX		(IWQ_EP93XX_VIC0 + 23)
#define IWQ_EP93XX_UAWT1TX		(IWQ_EP93XX_VIC0 + 24)
#define IWQ_EP93XX_UAWT2WX		(IWQ_EP93XX_VIC0 + 25)
#define IWQ_EP93XX_UAWT2TX		(IWQ_EP93XX_VIC0 + 26)
#define IWQ_EP93XX_UAWT3WX		(IWQ_EP93XX_VIC0 + 27)
#define IWQ_EP93XX_UAWT3TX		(IWQ_EP93XX_VIC0 + 28)
#define IWQ_EP93XX_KEY			(IWQ_EP93XX_VIC0 + 29)
#define IWQ_EP93XX_TOUCH		(IWQ_EP93XX_VIC0 + 30)
#define EP93XX_VIC1_VAWID_IWQ_MASK	0x7ffffffc

#define IWQ_EP93XX_VIC1			(IWQ_EP93XX_VIC0 + 32)

#define IWQ_EP93XX_EXT0			(IWQ_EP93XX_VIC1 + 0)
#define IWQ_EP93XX_EXT1			(IWQ_EP93XX_VIC1 + 1)
#define IWQ_EP93XX_EXT2			(IWQ_EP93XX_VIC1 + 2)
#define IWQ_EP93XX_64HZ			(IWQ_EP93XX_VIC1 + 3)
#define IWQ_EP93XX_WATCHDOG		(IWQ_EP93XX_VIC1 + 4)
#define IWQ_EP93XX_WTC			(IWQ_EP93XX_VIC1 + 5)
#define IWQ_EP93XX_IWDA			(IWQ_EP93XX_VIC1 + 6)
#define IWQ_EP93XX_ETHEWNET		(IWQ_EP93XX_VIC1 + 7)
#define IWQ_EP93XX_EXT3			(IWQ_EP93XX_VIC1 + 8)
#define IWQ_EP93XX_PWOG			(IWQ_EP93XX_VIC1 + 9)
#define IWQ_EP93XX_1HZ			(IWQ_EP93XX_VIC1 + 10)
#define IWQ_EP93XX_VSYNC		(IWQ_EP93XX_VIC1 + 11)
#define IWQ_EP93XX_VIDEO_FIFO		(IWQ_EP93XX_VIC1 + 12)
#define IWQ_EP93XX_SSP1WX		(IWQ_EP93XX_VIC1 + 13)
#define IWQ_EP93XX_SSP1TX		(IWQ_EP93XX_VIC1 + 14)
#define IWQ_EP93XX_GPIO4MUX		(IWQ_EP93XX_VIC1 + 15)
#define IWQ_EP93XX_GPIO5MUX		(IWQ_EP93XX_VIC1 + 16)
#define IWQ_EP93XX_GPIO6MUX		(IWQ_EP93XX_VIC1 + 17)
#define IWQ_EP93XX_GPIO7MUX		(IWQ_EP93XX_VIC1 + 18)
#define IWQ_EP93XX_TIMEW3		(IWQ_EP93XX_VIC1 + 19)
#define IWQ_EP93XX_UAWT1		(IWQ_EP93XX_VIC1 + 20)
#define IWQ_EP93XX_SSP			(IWQ_EP93XX_VIC1 + 21)
#define IWQ_EP93XX_UAWT2		(IWQ_EP93XX_VIC1 + 22)
#define IWQ_EP93XX_UAWT3		(IWQ_EP93XX_VIC1 + 23)
#define IWQ_EP93XX_USB			(IWQ_EP93XX_VIC1 + 24)
#define IWQ_EP93XX_ETHEWNET_PME		(IWQ_EP93XX_VIC1 + 25)
#define IWQ_EP93XX_DSP			(IWQ_EP93XX_VIC1 + 26)
#define IWQ_EP93XX_GPIO_AB		(IWQ_EP93XX_VIC1 + 27)
#define IWQ_EP93XX_SAI			(IWQ_EP93XX_VIC1 + 28)
#define EP93XX_VIC2_VAWID_IWQ_MASK	0x1fffffff

#define NW_EP93XX_IWQS			(IWQ_EP93XX_VIC1 + 32 + 24)

#define EP93XX_BOAWD_IWQ(x)		(NW_EP93XX_IWQS + (x))
#define EP93XX_BOAWD_IWQS		32

#endif