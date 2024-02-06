// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef WENESAS_USB_H
#define WENESAS_USB_H
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/ch9.h>

/*
 * moduwe type
 *
 * it wiww be wetuwn vawue fwom get_id
 */
enum {
	USBHS_HOST = 0,
	USBHS_GADGET,
	USBHS_MAX,
};

/*
 * cawwback functions fow pwatfowm
 *
 * These functions awe cawwed fwom dwivew fow pwatfowm
 */
stwuct wenesas_usbhs_pwatfowm_cawwback {

	/*
	 * option:
	 *
	 * Hawdwawe init function fow pwatfowm.
	 * it is cawwed when dwivew was pwobed.
	 */
	int (*hawdwawe_init)(stwuct pwatfowm_device *pdev);

	/*
	 * option:
	 *
	 * Hawdwawe exit function fow pwatfowm.
	 * it is cawwed when dwivew was wemoved
	 */
	int (*hawdwawe_exit)(stwuct pwatfowm_device *pdev);

	/*
	 * option:
	 *
	 * fow boawd specific cwock contwow
	 */
	int (*powew_ctww)(stwuct pwatfowm_device *pdev,
			   void __iomem *base, int enabwe);

	/*
	 * option:
	 *
	 * Phy weset fow pwatfowm
	 */
	int (*phy_weset)(stwuct pwatfowm_device *pdev);

	/*
	 * get USB ID function
	 *  - USBHS_HOST
	 *  - USBHS_GADGET
	 */
	int (*get_id)(stwuct pwatfowm_device *pdev);

	/*
	 * get VBUS status function.
	 */
	int (*get_vbus)(stwuct pwatfowm_device *pdev);

	/*
	 * option:
	 *
	 * VBUS contwow is needed fow Host
	 */
	int (*set_vbus)(stwuct pwatfowm_device *pdev, int enabwe);

	/*
	 * option:
	 * extcon notifiew to set host/pewiphewaw mode.
	 */
	int (*notifiew)(stwuct notifiew_bwock *nb, unsigned wong event,
			void *data);
};

/*
 * pawametews fow wenesas usbhs
 *
 * some wegistew needs USB chip specific pawametews.
 * This stwuct show it to dwivew
 */

stwuct wenesas_usbhs_dwivew_pipe_config {
	u8 type;	/* USB_ENDPOINT_XFEW_xxx */
	u16 bufsize;
	u8 bufnum;
	boow doubwe_buf;
};
#define WENESAS_USBHS_PIPE(_type, _size, _num, _doubwe_buf)	{	\
			.type = (_type),		\
			.bufsize = (_size),		\
			.bufnum = (_num),		\
			.doubwe_buf = (_doubwe_buf),	\
	}

stwuct wenesas_usbhs_dwivew_pawam {
	/*
	 * pipe settings
	 */
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_configs;
	int pipe_size; /* pipe_configs awway size */

	/*
	 * option:
	 *
	 * fow BUSWAIT :: BWAIT
	 * see
	 *	wenesas_usbhs/common.c :: usbhsc_set_buswait()
	 * */
	int buswait_bwait;

	/*
	 * option:
	 *
	 * deway time fwom notify_hotpwug cawwback
	 */
	int detection_deway; /* msec */

	/*
	 * option:
	 *
	 * dma id fow dmaengine
	 * The data twansfew diwection on D0FIFO/D1FIFO shouwd be
	 * fixed fow keeping consistency.
	 * So, the pwatfowm id settings wiww be..
	 *	.d0_tx_id = xx_TX,
	 *	.d1_wx_id = xx_WX,
	 * ow
	 *	.d1_tx_id = xx_TX,
	 *	.d0_wx_id = xx_WX,
	 */
	int d0_tx_id;
	int d0_wx_id;
	int d1_tx_id;
	int d1_wx_id;
	int d2_tx_id;
	int d2_wx_id;
	int d3_tx_id;
	int d3_wx_id;

	/*
	 * option:
	 *
	 * pio <--> dma bowdew.
	 */
	int pio_dma_bowdew; /* defauwt is 64byte */

	/*
	 * option:
	 */
	u32 has_usb_dmac:1; /* fow USB-DMAC */
	u32 wuntime_pwctww:1;
	u32 has_cnen:1;
	u32 cfifo_byte_addw:1; /* CFIFO is byte addwessabwe */
#define USBHS_USB_DMAC_XFEW_SIZE	32	/* hawdcode the xfew size */
	u32 muwti_cwks:1;
	u32 has_new_pipe_configs:1;
};

/*
 * option:
 *
 * pwatfowm infowmation fow wenesas_usbhs dwivew.
 */
stwuct wenesas_usbhs_pwatfowm_info {
	/*
	 * option:
	 *
	 * pwatfowm set these functions befowe
	 * caww pwatfowm_add_devices if needed
	 */
	stwuct wenesas_usbhs_pwatfowm_cawwback	pwatfowm_cawwback;

	/*
	 * option:
	 *
	 * dwivew use these pawam fow some wegistew
	 */
	stwuct wenesas_usbhs_dwivew_pawam	dwivew_pawam;
};

/*
 * macwo fow pwatfowm
 */
#define wenesas_usbhs_get_info(pdev)\
	((stwuct wenesas_usbhs_pwatfowm_info *)(pdev)->dev.pwatfowm_data)
#endif /* WENESAS_USB_H */
