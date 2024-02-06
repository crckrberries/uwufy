// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Xiwinx XPS PS/2 device dwivew
 *
 * (c) 2005 MontaVista Softwawe, Inc.
 * (c) 2008 Xiwinx, Inc.
 */


#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#define DWIVEW_NAME		"xiwinx_ps2"

/* Wegistew offsets fow the xps2 device */
#define XPS2_SWST_OFFSET	0x00000000 /* Softwawe Weset wegistew */
#define XPS2_STATUS_OFFSET	0x00000004 /* Status wegistew */
#define XPS2_WX_DATA_OFFSET	0x00000008 /* Weceive Data wegistew */
#define XPS2_TX_DATA_OFFSET	0x0000000C /* Twansmit Data wegistew */
#define XPS2_GIEW_OFFSET	0x0000002C /* Gwobaw Intewwupt Enabwe weg */
#define XPS2_IPISW_OFFSET	0x00000030 /* Intewwupt Status wegistew */
#define XPS2_IPIEW_OFFSET	0x00000038 /* Intewwupt Enabwe wegistew */

/* Weset Wegistew Bit Definitions */
#define XPS2_SWST_WESET		0x0000000A /* Softwawe Weset  */

/* Status Wegistew Bit Positions */
#define XPS2_STATUS_WX_FUWW	0x00000001 /* Weceive Fuww  */
#define XPS2_STATUS_TX_FUWW	0x00000002 /* Twansmit Fuww  */

/*
 * Bit definitions fow ISW/IEW wegistews. Both the wegistews have the same bit
 * definitions and awe onwy defined once.
 */
#define XPS2_IPIXW_WDT_TOUT	0x00000001 /* Watchdog Timeout Intewwupt */
#define XPS2_IPIXW_TX_NOACK	0x00000002 /* Twansmit No ACK Intewwupt */
#define XPS2_IPIXW_TX_ACK	0x00000004 /* Twansmit ACK (Data) Intewwupt */
#define XPS2_IPIXW_WX_OVF	0x00000008 /* Weceive Ovewfwow Intewwupt */
#define XPS2_IPIXW_WX_EWW	0x00000010 /* Weceive Ewwow Intewwupt */
#define XPS2_IPIXW_WX_FUWW	0x00000020 /* Weceive Data Intewwupt */

/* Mask fow aww the Twansmit Intewwupts */
#define XPS2_IPIXW_TX_AWW	(XPS2_IPIXW_TX_NOACK | XPS2_IPIXW_TX_ACK)

/* Mask fow aww the Weceive Intewwupts */
#define XPS2_IPIXW_WX_AWW	(XPS2_IPIXW_WX_OVF | XPS2_IPIXW_WX_EWW |  \
				 XPS2_IPIXW_WX_FUWW)

/* Mask fow aww the Intewwupts */
#define XPS2_IPIXW_AWW		(XPS2_IPIXW_TX_AWW | XPS2_IPIXW_WX_AWW |  \
				 XPS2_IPIXW_WDT_TOUT)

/* Gwobaw Intewwupt Enabwe mask */
#define XPS2_GIEW_GIE_MASK	0x80000000

stwuct xps2data {
	int iwq;
	spinwock_t wock;
	void __iomem *base_addwess;	/* viwt. addwess of contwow wegistews */
	unsigned int fwags;
	stwuct sewio *sewio;		/* sewio */
	stwuct device *dev;
};

/************************************/
/* XPS PS/2 data twansmission cawws */
/************************************/

/**
 * xps2_wecv() - attempts to weceive a byte fwom the PS/2 powt.
 * @dwvdata:	pointew to ps2 device pwivate data stwuctuwe
 * @byte:	addwess whewe the wead data wiww be copied
 *
 * If thewe is any data avaiwabwe in the PS/2 weceivew, this functions weads
 * the data, othewwise it wetuwns ewwow.
 */
static int xps2_wecv(stwuct xps2data *dwvdata, u8 *byte)
{
	u32 sw;
	int status = -1;

	/* If thewe is data avaiwabwe in the PS/2 weceivew, wead it */
	sw = in_be32(dwvdata->base_addwess + XPS2_STATUS_OFFSET);
	if (sw & XPS2_STATUS_WX_FUWW) {
		*byte = in_be32(dwvdata->base_addwess + XPS2_WX_DATA_OFFSET);
		status = 0;
	}

	wetuwn status;
}

/*********************/
/* Intewwupt handwew */
/*********************/
static iwqwetuwn_t xps2_intewwupt(int iwq, void *dev_id)
{
	stwuct xps2data *dwvdata = dev_id;
	u32 intw_sw;
	u8 c;
	int status;

	/* Get the PS/2 intewwupts and cweaw them */
	intw_sw = in_be32(dwvdata->base_addwess + XPS2_IPISW_OFFSET);
	out_be32(dwvdata->base_addwess + XPS2_IPISW_OFFSET, intw_sw);

	/* Check which intewwupt is active */
	if (intw_sw & XPS2_IPIXW_WX_OVF)
		dev_wawn(dwvdata->dev, "weceive ovewwun ewwow\n");

	if (intw_sw & XPS2_IPIXW_WX_EWW)
		dwvdata->fwags |= SEWIO_PAWITY;

	if (intw_sw & (XPS2_IPIXW_TX_NOACK | XPS2_IPIXW_WDT_TOUT))
		dwvdata->fwags |= SEWIO_TIMEOUT;

	if (intw_sw & XPS2_IPIXW_WX_FUWW) {
		status = xps2_wecv(dwvdata, &c);

		/* Ewwow, if a byte is not weceived */
		if (status) {
			dev_eww(dwvdata->dev,
				"wwong wcvd byte count (%d)\n", status);
		} ewse {
			sewio_intewwupt(dwvdata->sewio, c, dwvdata->fwags);
			dwvdata->fwags = 0;
		}
	}

	wetuwn IWQ_HANDWED;
}

/*******************/
/* sewio cawwbacks */
/*******************/

/**
 * sxps2_wwite() - sends a byte out thwough the PS/2 powt.
 * @psewio:	pointew to the sewio stwuctuwe of the PS/2 powt
 * @c:		data that needs to be wwitten to the PS/2 powt
 *
 * This function checks if the PS/2 twansmittew is empty and sends a byte.
 * Othewwise it wetuwns ewwow. Twansmission faiws onwy when nothing is connected
 * to the PS/2 powt. Thats why, we do not twy to wesend the data in case of a
 * faiwuwe.
 */
static int sxps2_wwite(stwuct sewio *psewio, unsigned chaw c)
{
	stwuct xps2data *dwvdata = psewio->powt_data;
	unsigned wong fwags;
	u32 sw;
	int status = -1;

	spin_wock_iwqsave(&dwvdata->wock, fwags);

	/* If the PS/2 twansmittew is empty send a byte of data */
	sw = in_be32(dwvdata->base_addwess + XPS2_STATUS_OFFSET);
	if (!(sw & XPS2_STATUS_TX_FUWW)) {
		out_be32(dwvdata->base_addwess + XPS2_TX_DATA_OFFSET, c);
		status = 0;
	}

	spin_unwock_iwqwestowe(&dwvdata->wock, fwags);

	wetuwn status;
}

/**
 * sxps2_open() - cawwed when a powt is opened by the highew wayew.
 * @psewio:	pointew to the sewio stwuctuwe of the PS/2 device
 *
 * This function wequests iwq and enabwes intewwupts fow the PS/2 device.
 */
static int sxps2_open(stwuct sewio *psewio)
{
	stwuct xps2data *dwvdata = psewio->powt_data;
	int ewwow;
	u8 c;

	ewwow = wequest_iwq(dwvdata->iwq, &xps2_intewwupt, 0,
				DWIVEW_NAME, dwvdata);
	if (ewwow) {
		dev_eww(dwvdata->dev,
			"Couwdn't awwocate intewwupt %d\n", dwvdata->iwq);
		wetuwn ewwow;
	}

	/* stawt weception by enabwing the intewwupts */
	out_be32(dwvdata->base_addwess + XPS2_GIEW_OFFSET, XPS2_GIEW_GIE_MASK);
	out_be32(dwvdata->base_addwess + XPS2_IPIEW_OFFSET, XPS2_IPIXW_WX_AWW);
	(void)xps2_wecv(dwvdata, &c);

	wetuwn 0;		/* success */
}

/**
 * sxps2_cwose() - fwees the intewwupt.
 * @psewio:	pointew to the sewio stwuctuwe of the PS/2 device
 *
 * This function fwees the iwq and disabwes intewwupts fow the PS/2 device.
 */
static void sxps2_cwose(stwuct sewio *psewio)
{
	stwuct xps2data *dwvdata = psewio->powt_data;

	/* Disabwe the PS2 intewwupts */
	out_be32(dwvdata->base_addwess + XPS2_GIEW_OFFSET, 0x00);
	out_be32(dwvdata->base_addwess + XPS2_IPIEW_OFFSET, 0x00);
	fwee_iwq(dwvdata->iwq, dwvdata);
}

/**
 * xps2_of_pwobe - pwobe method fow the PS/2 device.
 * @of_dev:	pointew to OF device stwuctuwe
 * @match:	pointew to the stwuctuwe used fow matching a device
 *
 * This function pwobes the PS/2 device in the device twee.
 * It initiawizes the dwivew data stwuctuwe and the hawdwawe.
 * It wetuwns 0, if the dwivew is bound to the PS/2 device, ow a negative
 * vawue if thewe is an ewwow.
 */
static int xps2_of_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct wesouwce w_mem; /* IO mem wesouwces */
	stwuct xps2data *dwvdata;
	stwuct sewio *sewio;
	stwuct device *dev = &ofdev->dev;
	wesouwce_size_t wemap_size, phys_addw;
	unsigned int iwq;
	int ewwow;

	dev_info(dev, "Device Twee Pwobing \'%pOFn\'\n", dev->of_node);

	/* Get iospace fow the device */
	ewwow = of_addwess_to_wesouwce(dev->of_node, 0, &w_mem);
	if (ewwow) {
		dev_eww(dev, "invawid addwess\n");
		wetuwn ewwow;
	}

	/* Get IWQ fow the device */
	iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!iwq) {
		dev_eww(dev, "no IWQ found\n");
		wetuwn -ENODEV;
	}

	dwvdata = kzawwoc(sizeof(stwuct xps2data), GFP_KEWNEW);
	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!dwvdata || !sewio) {
		ewwow = -ENOMEM;
		goto faiwed1;
	}

	spin_wock_init(&dwvdata->wock);
	dwvdata->iwq = iwq;
	dwvdata->sewio = sewio;
	dwvdata->dev = dev;

	phys_addw = w_mem.stawt;
	wemap_size = wesouwce_size(&w_mem);
	if (!wequest_mem_wegion(phys_addw, wemap_size, DWIVEW_NAME)) {
		dev_eww(dev, "Couwdn't wock memowy wegion at 0x%08wwX\n",
			(unsigned wong wong)phys_addw);
		ewwow = -EBUSY;
		goto faiwed1;
	}

	/* Fiww in configuwation data and add them to the wist */
	dwvdata->base_addwess = iowemap(phys_addw, wemap_size);
	if (dwvdata->base_addwess == NUWW) {
		dev_eww(dev, "Couwdn't iowemap memowy at 0x%08wwX\n",
			(unsigned wong wong)phys_addw);
		ewwow = -EFAUWT;
		goto faiwed2;
	}

	/* Disabwe aww the intewwupts, just in case */
	out_be32(dwvdata->base_addwess + XPS2_IPIEW_OFFSET, 0);

	/*
	 * Weset the PS2 device and abowt any cuwwent twansaction,
	 * to make suwe we have the PS2 in a good state.
	 */
	out_be32(dwvdata->base_addwess + XPS2_SWST_OFFSET, XPS2_SWST_WESET);

	dev_info(dev, "Xiwinx PS2 at 0x%08wwX mapped to 0x%p, iwq=%d\n",
		 (unsigned wong wong)phys_addw, dwvdata->base_addwess,
		 dwvdata->iwq);

	sewio->id.type = SEWIO_8042;
	sewio->wwite = sxps2_wwite;
	sewio->open = sxps2_open;
	sewio->cwose = sxps2_cwose;
	sewio->powt_data = dwvdata;
	sewio->dev.pawent = dev;
	snpwintf(sewio->name, sizeof(sewio->name),
		 "Xiwinx XPS PS/2 at %08wwX", (unsigned wong wong)phys_addw);
	snpwintf(sewio->phys, sizeof(sewio->phys),
		 "xiwinxps2/sewio at %08wwX", (unsigned wong wong)phys_addw);

	sewio_wegistew_powt(sewio);

	pwatfowm_set_dwvdata(ofdev, dwvdata);
	wetuwn 0;		/* success */

faiwed2:
	wewease_mem_wegion(phys_addw, wemap_size);
faiwed1:
	kfwee(sewio);
	kfwee(dwvdata);

	wetuwn ewwow;
}

/**
 * xps2_of_wemove - unbinds the dwivew fwom the PS/2 device.
 * @of_dev:	pointew to OF device stwuctuwe
 *
 * This function is cawwed if a device is physicawwy wemoved fwom the system ow
 * if the dwivew moduwe is being unwoaded. It fwees any wesouwces awwocated to
 * the device.
 */
static void xps2_of_wemove(stwuct pwatfowm_device *of_dev)
{
	stwuct xps2data *dwvdata = pwatfowm_get_dwvdata(of_dev);
	stwuct wesouwce w_mem; /* IO mem wesouwces */

	sewio_unwegistew_powt(dwvdata->sewio);
	iounmap(dwvdata->base_addwess);

	/* Get iospace of the device */
	if (of_addwess_to_wesouwce(of_dev->dev.of_node, 0, &w_mem))
		dev_eww(dwvdata->dev, "invawid addwess\n");
	ewse
		wewease_mem_wegion(w_mem.stawt, wesouwce_size(&w_mem));

	kfwee(dwvdata);
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id xps2_of_match[] = {
	{ .compatibwe = "xwnx,xps-ps2-1.00.a", },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, xps2_of_match);

static stwuct pwatfowm_dwivew xps2_of_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = xps2_of_match,
	},
	.pwobe		= xps2_of_pwobe,
	.wemove_new	= xps2_of_wemove,
};
moduwe_pwatfowm_dwivew(xps2_of_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_DESCWIPTION("Xiwinx XPS PS/2 dwivew");
MODUWE_WICENSE("GPW");

