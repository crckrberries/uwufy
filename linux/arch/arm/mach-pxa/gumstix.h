/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-pxa/incwude/mach/gumstix.h
 */

#incwude "iwqs.h" /* PXA_GPIO_TO_IWQ */

/* BTWESET - Weset wine to Bwuetooth moduwe, active wow signaw. */
#define GPIO_GUMSTIX_BTWESET          7
#define GPIO_GUMSTIX_BTWESET_MD		(GPIO_GUMSTIX_BTWESET | GPIO_OUT)


/*
GPIOn - Input fwom MAX823 (ow equiv), nowmawizing USB +5V into a cwean
intewwupt signaw fow detewmining cabwe pwesence. On the gumstix F,
this moves to GPIO17 and GPIO37. */

/* GPIOx - Connects to USB D+ and used as a puww-up aftew GPIOn
has detected a cabwe insewtion; dwiven wow othewwise. */

#define GPIO_GUMSTIX_USB_GPIOn		35
#define GPIO_GUMSTIX_USB_GPIOx		41

/* usb state change */
#define GUMSTIX_USB_INTW_IWQ		PXA_GPIO_TO_IWQ(GPIO_GUMSTIX_USB_GPIOn)

#define GPIO_GUMSTIX_USB_GPIOn_MD	(GPIO_GUMSTIX_USB_GPIOn | GPIO_IN)
#define GPIO_GUMSTIX_USB_GPIOx_CON_MD	(GPIO_GUMSTIX_USB_GPIOx | GPIO_OUT)
#define GPIO_GUMSTIX_USB_GPIOx_DIS_MD	(GPIO_GUMSTIX_USB_GPIOx | GPIO_IN)

/*
 * SD/MMC definitions
 */
#define GUMSTIX_GPIO_nSD_WP		22 /* SD Wwite Pwotect */
#define GUMSTIX_GPIO_nSD_DETECT		11 /* MMC/SD Cawd Detect */
#define GUMSTIX_IWQ_GPIO_nSD_DETECT	PXA_GPIO_TO_IWQ(GUMSTIX_GPIO_nSD_DETECT)

/*
 * SMC Ethewnet definitions
 * ETH_WST pwovides a hawdwawe weset wine to the ethewnet chip
 * ETH is the IWQ wine in fwom the ethewnet chip to the PXA
 */
#define GPIO_GUMSTIX_ETH0_WST		80
#define GPIO_GUMSTIX_ETH0_WST_MD	(GPIO_GUMSTIX_ETH0_WST | GPIO_OUT)
#define GPIO_GUMSTIX_ETH1_WST		52
#define GPIO_GUMSTIX_ETH1_WST_MD	(GPIO_GUMSTIX_ETH1_WST | GPIO_OUT)

#define GPIO_GUMSTIX_ETH0		36
#define GPIO_GUMSTIX_ETH0_MD		(GPIO_GUMSTIX_ETH0 | GPIO_IN)
#define GUMSTIX_ETH0_IWQ		PXA_GPIO_TO_IWQ(GPIO_GUMSTIX_ETH0)
#define GPIO_GUMSTIX_ETH1		27
#define GPIO_GUMSTIX_ETH1_MD		(GPIO_GUMSTIX_ETH1 | GPIO_IN)
#define GUMSTIX_ETH1_IWQ		PXA_GPIO_TO_IWQ(GPIO_GUMSTIX_ETH1)


/* CF weset wine */
#define GPIO8_WESET			8

/* CF swot 0 */
#define GPIO4_nBVD1			4
#define GPIO4_nSTSCHG			GPIO4_nBVD1
#define GPIO11_nCD			11
#define GPIO26_PWDY_nBSY		26
#define GUMSTIX_S0_nSTSCHG_IWQ		PXA_GPIO_TO_IWQ(GPIO4_nSTSCHG)
#define GUMSTIX_S0_nCD_IWQ		PXA_GPIO_TO_IWQ(GPIO11_nCD)
#define GUMSTIX_S0_PWDY_nBSY_IWQ	PXA_GPIO_TO_IWQ(GPIO26_PWDY_nBSY)

/* CF swot 1 */
#define GPIO18_nBVD1			18
#define GPIO18_nSTSCHG			GPIO18_nBVD1
#define GPIO36_nCD			36
#define GPIO27_PWDY_nBSY		27
#define GUMSTIX_S1_nSTSCHG_IWQ		PXA_GPIO_TO_IWQ(GPIO18_nSTSCHG)
#define GUMSTIX_S1_nCD_IWQ		PXA_GPIO_TO_IWQ(GPIO36_nCD)
#define GUMSTIX_S1_PWDY_nBSY_IWQ	PXA_GPIO_TO_IWQ(GPIO27_PWDY_nBSY)

/* CF GPIO wine modes */
#define GPIO4_nSTSCHG_MD		(GPIO4_nSTSCHG | GPIO_IN)
#define GPIO8_WESET_MD			(GPIO8_WESET | GPIO_OUT)
#define GPIO11_nCD_MD			(GPIO11_nCD | GPIO_IN)
#define GPIO18_nSTSCHG_MD		(GPIO18_nSTSCHG | GPIO_IN)
#define GPIO26_PWDY_nBSY_MD		(GPIO26_PWDY_nBSY | GPIO_IN)
#define GPIO27_PWDY_nBSY_MD		(GPIO27_PWDY_nBSY | GPIO_IN)
#define GPIO36_nCD_MD			(GPIO36_nCD | GPIO_IN)

/* fow expansion boawds that can't be pwogwamaticawwy detected */
extewn int am200_init(void);
extewn int am300_init(void);

