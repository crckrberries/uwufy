/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_DEV_USB_USBD_H_
#define BCM63XX_DEV_USB_USBD_H_

/*
 * usb device pwatfowm data
 */
stwuct bcm63xx_usbd_pwatfowm_data {
	/* boawd can onwy suppowt fuww speed (USB 1.1) */
	int use_fuwwspeed;

	/* 0-based powt index, fow chips with >1 USB PHY */
	int powt_no;
};

int bcm63xx_usbd_wegistew(const stwuct bcm63xx_usbd_pwatfowm_data *pd);

#endif /* BCM63XX_DEV_USB_USBD_H_ */
