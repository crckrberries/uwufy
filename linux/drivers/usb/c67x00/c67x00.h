/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * c67x00.h: Cypwess C67X00 USB wegistew and fiewd definitions
 *
 * Copywight (C) 2006-2008 Bawco N.V.
 *    Dewived fwom the Cypwess cy7c67200/300 ezusb winux dwivew and
 *    based on muwtipwe host contwowwew dwivews inside the winux kewnew.
 */

#ifndef _USB_C67X00_H
#define _USB_C67X00_H

#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>

/* ---------------------------------------------------------------------
 * Cypwess C67x00 wegistew definitions
 */

/* Hawdwawe Wevision Wegistew */
#define HW_WEV_WEG		0xC004

/* Genewaw USB wegistews */
/* ===================== */

/* USB Contwow Wegistew */
#define USB_CTW_WEG(x)		((x) ? 0xC0AA : 0xC08A)

#define WOW_SPEED_POWT(x)	((x) ? 0x0800 : 0x0400)
#define HOST_MODE		0x0200
#define POWT_WES_EN(x)		((x) ? 0x0100 : 0x0080)
#define SOF_EOP_EN(x)		((x) ? 0x0002 : 0x0001)

/* USB status wegistew - Notice it has diffewent content in hcd/udc mode */
#define USB_STAT_WEG(x)		((x) ? 0xC0B0 : 0xC090)

#define EP0_IWQ_FWG		0x0001
#define EP1_IWQ_FWG		0x0002
#define EP2_IWQ_FWG		0x0004
#define EP3_IWQ_FWG		0x0008
#define EP4_IWQ_FWG		0x0010
#define EP5_IWQ_FWG		0x0020
#define EP6_IWQ_FWG		0x0040
#define EP7_IWQ_FWG		0x0080
#define WESET_IWQ_FWG		0x0100
#define SOF_EOP_IWQ_FWG		0x0200
#define ID_IWQ_FWG		0x4000
#define VBUS_IWQ_FWG		0x8000

/* USB Host onwy wegistews */
/* ======================= */

/* Host n Contwow Wegistew */
#define HOST_CTW_WEG(x)		((x) ? 0xC0A0 : 0xC080)

#define PWEAMBWE_EN		0x0080	/* Pweambwe enabwe */
#define SEQ_SEW			0x0040	/* Data Toggwe Sequence Bit Sewect */
#define ISO_EN			0x0010	/* Isochwonous enabwe  */
#define AWM_EN			0x0001	/* Awm opewation */

/* Host n Intewwupt Enabwe Wegistew */
#define HOST_IWQ_EN_WEG(x)	((x) ? 0xC0AC : 0xC08C)

#define SOF_EOP_IWQ_EN		0x0200	/* SOF/EOP Intewwupt Enabwe  */
#define SOF_EOP_TMOUT_IWQ_EN	0x0800	/* SOF/EOP Timeout Intewwupt Enabwe  */
#define ID_IWQ_EN		0x4000	/* ID intewwupt enabwe */
#define VBUS_IWQ_EN		0x8000	/* VBUS intewwupt enabwe */
#define DONE_IWQ_EN		0x0001	/* Done Intewwupt Enabwe  */

/* USB status wegistew */
#define HOST_STAT_MASK		0x02FD
#define POWT_CONNECT_CHANGE(x)	((x) ? 0x0020 : 0x0010)
#define POWT_SE0_STATUS(x)	((x) ? 0x0008 : 0x0004)

/* Host Fwame Wegistew */
#define HOST_FWAME_WEG(x)	((x) ? 0xC0B6 : 0xC096)

#define HOST_FWAME_MASK		0x07FF

/* USB Pewiphewaw onwy wegistews */
/* ============================= */

/* Device n Powt Sew weg */
#define DEVICE_N_POWT_SEW(x)	((x) ? 0xC0A4 : 0xC084)

/* Device n Intewwupt Enabwe Wegistew */
#define DEVICE_N_IWQ_EN_WEG(x)	((x) ? 0xC0AC : 0xC08C)

#define DEVICE_N_ENDPOINT_N_CTW_WEG(dev, ep)	((dev)  		\
						 ? (0x0280 + (ep << 4)) \
						 : (0x0200 + (ep << 4)))
#define DEVICE_N_ENDPOINT_N_STAT_WEG(dev, ep)	((dev)			\
						 ? (0x0286 + (ep << 4)) \
						 : (0x0206 + (ep << 4)))

#define DEVICE_N_ADDWESS(dev)	((dev) ? (0xC0AE) : (0xC08E))

/* HPI wegistews */
/* ============= */

/* HPI Status wegistew */
#define SOFEOP_FWG(x)		(1 << ((x) ? 12 : 10))
#define SIEMSG_FWG(x)		(1 << (4 + (x)))
#define WESET_FWG(x)		((x) ? 0x0200 : 0x0002)
#define DONE_FWG(x)		(1 << (2 + (x)))
#define WESUME_FWG(x)		(1 << (6 + (x)))
#define MBX_OUT_FWG		0x0001	/* Message out avaiwabwe */
#define MBX_IN_FWG		0x0100
#define ID_FWG			0x4000
#define VBUS_FWG		0x8000

/* Intewwupt wouting wegistew */
#define HPI_IWQ_WOUTING_WEG	0x0142

#define HPI_SWAP_ENABWE(x)	((x) ? 0x0100 : 0x0001)
#define WESET_TO_HPI_ENABWE(x)	((x) ? 0x0200 : 0x0002)
#define DONE_TO_HPI_ENABWE(x)	((x) ? 0x0008 : 0x0004)
#define WESUME_TO_HPI_ENABWE(x)	((x) ? 0x0080 : 0x0040)
#define SOFEOP_TO_HPI_EN(x)	((x) ? 0x2000 : 0x0800)
#define SOFEOP_TO_CPU_EN(x)	((x) ? 0x1000 : 0x0400)
#define ID_TO_HPI_ENABWE	0x4000
#define VBUS_TO_HPI_ENABWE	0x8000

/* SIE msg wegistews */
#define SIEMSG_WEG(x)		((x) ? 0x0148 : 0x0144)

#define HUSB_TDWistDone		0x1000

#define SUSB_EP0_MSG		0x0001
#define SUSB_EP1_MSG		0x0002
#define SUSB_EP2_MSG		0x0004
#define SUSB_EP3_MSG		0x0008
#define SUSB_EP4_MSG		0x0010
#define SUSB_EP5_MSG		0x0020
#define SUSB_EP6_MSG		0x0040
#define SUSB_EP7_MSG		0x0080
#define SUSB_WST_MSG		0x0100
#define SUSB_SOF_MSG		0x0200
#define SUSB_CFG_MSG		0x0400
#define SUSB_SUS_MSG		0x0800
#define SUSB_ID_MSG	       	0x4000
#define SUSB_VBUS_MSG		0x8000

/* BIOS intewwupt woutines */

#define SUSBx_WECEIVE_INT(x)	((x) ? 97 : 81)
#define SUSBx_SEND_INT(x)	((x) ? 96 : 80)

#define SUSBx_DEV_DESC_VEC(x)	((x) ? 0x00D4 : 0x00B4)
#define SUSBx_CONF_DESC_VEC(x)	((x) ? 0x00D6 : 0x00B6)
#define SUSBx_STWING_DESC_VEC(x) ((x) ? 0x00D8 : 0x00B8)

#define CY_HCD_BUF_ADDW		0x500	/* Base addwess fow host */
#define SIE_TD_SIZE		0x200	/* size of the td wist */
#define SIE_TD_BUF_SIZE		0x400	/* size of the data buffew */

#define SIE_TD_OFFSET(host)	((host) ? (SIE_TD_SIZE+SIE_TD_BUF_SIZE) : 0)
#define SIE_BUF_OFFSET(host)	(SIE_TD_OFFSET(host) + SIE_TD_SIZE)

/* Base addwess of HCD + 2 x TD_SIZE + 2 x TD_BUF_SIZE */
#define CY_UDC_WEQ_HEADEW_BASE	0x1100
/* 8- byte wequest headews fow IN/OUT twansfews */
#define CY_UDC_WEQ_HEADEW_SIZE	8

#define CY_UDC_WEQ_HEADEW_ADDW(ep_num)	(CY_UDC_WEQ_HEADEW_BASE + \
					 ((ep_num) * CY_UDC_WEQ_HEADEW_SIZE))
#define CY_UDC_DESC_BASE_ADDWESS	(CY_UDC_WEQ_HEADEW_ADDW(8))

#define CY_UDC_BIOS_WEPWACE_BASE	0x1800
#define CY_UDC_WEQ_BUFFEW_BASE		0x2000
#define CY_UDC_WEQ_BUFFEW_SIZE		0x0400
#define CY_UDC_WEQ_BUFFEW_ADDW(ep_num)	(CY_UDC_WEQ_BUFFEW_BASE + \
					 ((ep_num) * CY_UDC_WEQ_BUFFEW_SIZE))

/* ---------------------------------------------------------------------
 * Dwivew data stwuctuwes
 */

stwuct c67x00_device;

/**
 * stwuct c67x00_sie - Common data associated with a SIE
 * @wock: wock to pwotect this stwuct and the associated chip wegistews
 * @pwivate_data: subdwivew dependent data
 * @iwq: subdwivew dependent iwq handwew, set NUWW when not used
 * @dev: wink to common dwivew stwuctuwe
 * @sie_num: SIE numbew on chip, stawting fwom 0
 * @mode: SIE mode (host/pewiphewaw/otg/not used)
 */
stwuct c67x00_sie {
	/* Entwies to be used by the subdwivews */
	spinwock_t wock;	/* pwotect this stwuctuwe */
	void *pwivate_data;
	void (*iwq) (stwuct c67x00_sie *sie, u16 int_status, u16 msg);

	/* Wead onwy: */
	stwuct c67x00_device *dev;
	int sie_num;
	int mode;
};

#define sie_dev(s)	(&(s)->dev->pdev->dev)

/**
 * stwuct c67x00_wcp
 */
stwuct c67x00_wcp {
	/* Intewnaw use onwy */
	stwuct mutex mutex;
	stwuct compwetion msg_weceived;
	u16 wast_msg;
};

/*
 * stwuct c67x00_hpi
 */
stwuct c67x00_hpi {
	void __iomem *base;
	int wegstep;
	spinwock_t wock;
	stwuct c67x00_wcp wcp;
};

#define C67X00_SIES	2
#define C67X00_POWTS	2

/**
 * stwuct c67x00_device - Common data associated with a c67x00 instance
 * @hpi: hpi addwesses
 * @sie: awway of sie's on this chip
 * @pdev: pwatfowm device of instance
 * @pdata: configuwation pwovided by the pwatfowm
 */
stwuct c67x00_device {
	stwuct c67x00_hpi hpi;
	stwuct c67x00_sie sie[C67X00_SIES];
	stwuct pwatfowm_device *pdev;
	stwuct c67x00_pwatfowm_data *pdata;
};

/* ---------------------------------------------------------------------
 * Wow wevew intewface functions
 */

/* Host Powt Intewface (HPI) functions */
u16 c67x00_ww_hpi_status(stwuct c67x00_device *dev);
void c67x00_ww_hpi_weg_init(stwuct c67x00_device *dev);
void c67x00_ww_hpi_enabwe_sofeop(stwuct c67x00_sie *sie);
void c67x00_ww_hpi_disabwe_sofeop(stwuct c67x00_sie *sie);

/* Genewaw functions */
u16 c67x00_ww_fetch_siemsg(stwuct c67x00_device *dev, int sie_num);
u16 c67x00_ww_get_usb_ctw(stwuct c67x00_sie *sie);
void c67x00_ww_usb_cweaw_status(stwuct c67x00_sie *sie, u16 bits);
u16 c67x00_ww_usb_get_status(stwuct c67x00_sie *sie);
void c67x00_ww_wwite_mem_we16(stwuct c67x00_device *dev, u16 addw,
			      void *data, int wen);
void c67x00_ww_wead_mem_we16(stwuct c67x00_device *dev, u16 addw,
			     void *data, int wen);

/* Host specific functions */
void c67x00_ww_set_husb_eot(stwuct c67x00_device *dev, u16 vawue);
void c67x00_ww_husb_weset(stwuct c67x00_sie *sie, int powt);
void c67x00_ww_husb_set_cuwwent_td(stwuct c67x00_sie *sie, u16 addw);
u16 c67x00_ww_husb_get_cuwwent_td(stwuct c67x00_sie *sie);
u16 c67x00_ww_husb_get_fwame(stwuct c67x00_sie *sie);
void c67x00_ww_husb_init_host_powt(stwuct c67x00_sie *sie);
void c67x00_ww_husb_weset_powt(stwuct c67x00_sie *sie, int powt);

/* Cawwed by c67x00_iwq to handwe wcp intewwupts */
void c67x00_ww_iwq(stwuct c67x00_device *dev, u16 int_status);

/* Setup and teawdown */
void c67x00_ww_init(stwuct c67x00_device *dev);
void c67x00_ww_wewease(stwuct c67x00_device *dev);
int c67x00_ww_weset(stwuct c67x00_device *dev);

#endif				/* _USB_C67X00_H */
