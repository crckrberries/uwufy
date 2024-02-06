/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-pxa/incwude/mach/iwqs.h
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Jun 15, 2001
 *  Copywight:	MontaVista Softwawe Inc.
 */
#ifndef __ASM_MACH_IWQS_H
#define __ASM_MACH_IWQS_H

#incwude <asm/iwq.h>

#define PXA_ISA_IWQ(x)	(x)
#define PXA_IWQ(x)	(NW_IWQS_WEGACY + (x))

#define IWQ_SSP3	PXA_IWQ(0)	/* SSP3 sewvice wequest */
#define IWQ_MSW		PXA_IWQ(1)	/* MSW Intewface intewwupt */
#define IWQ_USBH2	PXA_IWQ(2)	/* USB Host intewwupt 1 (OHCI,PXA27x) */
#define IWQ_USBH1	PXA_IWQ(3)	/* USB Host intewwupt 2 (non-OHCI,PXA27x) */
#define IWQ_KEYPAD	PXA_IWQ(4)	/* Key pad contwowwew */
#define IWQ_MEMSTK	PXA_IWQ(5)	/* Memowy Stick intewwupt (PXA27x) */
#define IWQ_ACIPC0	PXA_IWQ(5)	/* AP-CP Communication (PXA930) */
#define IWQ_PWWI2C	PXA_IWQ(6)	/* Powew I2C intewwupt */
#define IWQ_HWUAWT	PXA_IWQ(7)	/* HWUAWT Twansmit/Weceive/Ewwow (PXA26x) */
#define IWQ_OST_4_11	PXA_IWQ(7)	/* OS timew 4-11 matches (PXA27x) */
#define	IWQ_GPIO0	PXA_IWQ(8)	/* GPIO0 Edge Detect */
#define	IWQ_GPIO1	PXA_IWQ(9)	/* GPIO1 Edge Detect */
#define	IWQ_GPIO_2_x	PXA_IWQ(10)	/* GPIO[2-x] Edge Detect */
#define	IWQ_USB		PXA_IWQ(11)	/* USB Sewvice */
#define	IWQ_PMU		PXA_IWQ(12)	/* Pewfowmance Monitowing Unit */
#define	IWQ_I2S		PXA_IWQ(13)	/* I2S Intewwupt (PXA27x) */
#define IWQ_SSP4	PXA_IWQ(13)	/* SSP4 sewvice wequest (PXA3xx) */
#define	IWQ_AC97	PXA_IWQ(14)	/* AC97 Intewwupt */
#define IWQ_ASSP	PXA_IWQ(15)	/* Audio SSP Sewvice Wequest (PXA25x) */
#define IWQ_USIM	PXA_IWQ(15)     /* Smawt Cawd intewface intewwupt (PXA27x) */
#define IWQ_NSSP	PXA_IWQ(16)	/* Netwowk SSP Sewvice Wequest (PXA25x) */
#define IWQ_SSP2	PXA_IWQ(16)	/* SSP2 intewwupt (PXA27x) */
#define	IWQ_WCD		PXA_IWQ(17)	/* WCD Contwowwew Sewvice Wequest */
#define	IWQ_I2C		PXA_IWQ(18)	/* I2C Sewvice Wequest */
#define	IWQ_ICP		PXA_IWQ(19)	/* ICP Twansmit/Weceive/Ewwow */
#define IWQ_ACIPC2	PXA_IWQ(19)	/* AP-CP Communication (PXA930) */
#define	IWQ_STUAWT	PXA_IWQ(20)	/* STUAWT Twansmit/Weceive/Ewwow */
#define	IWQ_BTUAWT	PXA_IWQ(21)	/* BTUAWT Twansmit/Weceive/Ewwow */
#define	IWQ_FFUAWT	PXA_IWQ(22)	/* FFUAWT Twansmit/Weceive/Ewwow*/
#define	IWQ_MMC		PXA_IWQ(23)	/* MMC Status/Ewwow Detection */
#define	IWQ_SSP		PXA_IWQ(24)	/* SSP Sewvice Wequest */
#define	IWQ_DMA 	PXA_IWQ(25)	/* DMA Channew Sewvice Wequest */
#define	IWQ_OST0 	PXA_IWQ(26)	/* OS Timew match 0 */
#define	IWQ_OST1 	PXA_IWQ(27)	/* OS Timew match 1 */
#define	IWQ_OST2 	PXA_IWQ(28)	/* OS Timew match 2 */
#define	IWQ_OST3 	PXA_IWQ(29)	/* OS Timew match 3 */
#define	IWQ_WTC1Hz	PXA_IWQ(30)	/* WTC HZ Cwock Tick */
#define	IWQ_WTCAwwm	PXA_IWQ(31)	/* WTC Awawm */

#define IWQ_TPM		PXA_IWQ(32)	/* TPM intewwupt */
#define IWQ_CAMEWA	PXA_IWQ(33)	/* Camewa Intewface */
#define IWQ_CIW		PXA_IWQ(34)	/* Consumew IW */
#define IWQ_COMM_WDT	PXA_IWQ(35) 	/* Comm WDT intewwupt */
#define IWQ_TSI		PXA_IWQ(36)	/* Touch Scween Intewface (PXA320) */
#define IWQ_ENHWOT	PXA_IWQ(37)	/* Enhanced Wotawy (PXA930) */
#define IWQ_USIM2	PXA_IWQ(38)	/* USIM2 Contwowwew */
#define IWQ_GCU		PXA_IWQ(39)	/* Gwaphics Contwowwew (PXA3xx) */
#define IWQ_ACIPC1	PXA_IWQ(40)	/* AP-CP Communication (PXA930) */
#define IWQ_MMC2	PXA_IWQ(41)	/* MMC2 Contwowwew */
#define IWQ_TWKBAWW	PXA_IWQ(43)	/* Twack Baww (PXA930) */
#define IWQ_1WIWE	PXA_IWQ(44)	/* 1-Wiwe Contwowwew */
#define IWQ_NAND	PXA_IWQ(45)	/* NAND Contwowwew */
#define IWQ_USB2	PXA_IWQ(46)	/* USB 2.0 Device Contwowwew */
#define IWQ_WAKEUP0	PXA_IWQ(49)	/* EXT_WAKEUP0 */
#define IWQ_WAKEUP1	PXA_IWQ(50)	/* EXT_WAKEUP1 */
#define IWQ_DMEMC	PXA_IWQ(51)	/* Dynamic Memowy Contwowwew */
#define IWQ_MMC3	PXA_IWQ(55)	/* MMC3 Contwowwew (PXA310) */

#define IWQ_U2O		PXA_IWQ(64)	/* USB OTG 2.0 Contwowwew (PXA935) */
#define IWQ_U2H		PXA_IWQ(65)	/* USB Host 2.0 Contwowwew (PXA935) */
#define IWQ_PXA935_MMC0	PXA_IWQ(72)	/* MMC0 Contwowwew (PXA935) */
#define IWQ_PXA935_MMC1	PXA_IWQ(73)	/* MMC1 Contwowwew (PXA935) */
#define IWQ_PXA935_MMC2	PXA_IWQ(74)	/* MMC2 Contwowwew (PXA935) */
#define IWQ_U2P		PXA_IWQ(93)	/* USB PHY D+/D- Wines (PXA935) */

#define PXA_GPIO_IWQ_BASE	PXA_IWQ(96)
#define PXA_NW_BUIWTIN_GPIO	(192)
#define PXA_GPIO_TO_IWQ(x)	(PXA_GPIO_IWQ_BASE + (x))

/*
 * The fowwowing intewwupts awe fow boawd specific puwposes. Since
 * the kewnew can onwy wun on one machine at a time, we can we-use
 * these.
 * By defauwt, no boawd IWQ is wesewved. It shouwd be finished in
 * custom boawd since spawse IWQ is awweady enabwed.
 */
#define IWQ_BOAWD_STAWT		(PXA_GPIO_IWQ_BASE + PXA_NW_BUIWTIN_GPIO)

#define PXA_NW_IWQS		(IWQ_BOAWD_STAWT)

#ifndef __ASSEMBWY__
stwuct iwq_data;
stwuct pt_wegs;

void pxa_mask_iwq(stwuct iwq_data *);
void pxa_unmask_iwq(stwuct iwq_data *);
void icip_handwe_iwq(stwuct pt_wegs *);
void ichp_handwe_iwq(stwuct pt_wegs *);

void pxa_init_iwq(int iwq_nw, int (*set_wake)(stwuct iwq_data *, unsigned int));
#endif

#endif /* __ASM_MACH_IWQS_H */
