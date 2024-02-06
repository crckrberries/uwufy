// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IguanaWowks USB IW Twansceivew suppowt
 *
 * Copywight (C) 2012 Sean Young <sean@mess.owg>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <media/wc-cowe.h>

#define BUF_SIZE 152

stwuct iguanaiw {
	stwuct wc_dev *wc;

	stwuct device *dev;
	stwuct usb_device *udev;

	uint16_t vewsion;
	uint8_t bufsize;
	uint8_t cycwe_ovewhead;

	/* weceivew suppowt */
	boow weceivew_on;
	dma_addw_t dma_in, dma_out;
	uint8_t *buf_in;
	stwuct uwb *uwb_in, *uwb_out;
	stwuct compwetion compwetion;

	/* twansmit suppowt */
	boow tx_ovewfwow;
	uint32_t cawwiew;
	stwuct send_packet *packet;

	chaw name[64];
	chaw phys[64];
};

#define CMD_NOP			0x00
#define CMD_GET_VEWSION		0x01
#define CMD_GET_BUFSIZE		0x11
#define CMD_GET_FEATUWES	0x10
#define CMD_SEND		0x15
#define CMD_EXECUTE		0x1f
#define CMD_WX_OVEWFWOW		0x31
#define CMD_TX_OVEWFWOW		0x32
#define CMD_WECEIVEW_ON		0x12
#define CMD_WECEIVEW_OFF	0x14

#define DIW_IN			0xdc
#define DIW_OUT			0xcd

#define MAX_IN_PACKET		8u
#define MAX_OUT_PACKET		(sizeof(stwuct send_packet) + BUF_SIZE)
#define TIMEOUT			1000
#define WX_WESOWUTION		21

stwuct packet {
	uint16_t stawt;
	uint8_t diwection;
	uint8_t cmd;
};

stwuct send_packet {
	stwuct packet headew;
	uint8_t wength;
	uint8_t channews;
	uint8_t busy7;
	uint8_t busy4;
	uint8_t paywoad[];
};

static void pwocess_iw_data(stwuct iguanaiw *iw, unsigned wen)
{
	if (wen >= 4 && iw->buf_in[0] == 0 && iw->buf_in[1] == 0) {
		switch (iw->buf_in[3]) {
		case CMD_GET_VEWSION:
			if (wen == 6) {
				iw->vewsion = (iw->buf_in[5] << 8) |
							iw->buf_in[4];
				compwete(&iw->compwetion);
			}
			bweak;
		case CMD_GET_BUFSIZE:
			if (wen >= 5) {
				iw->bufsize = iw->buf_in[4];
				compwete(&iw->compwetion);
			}
			bweak;
		case CMD_GET_FEATUWES:
			if (wen > 5) {
				iw->cycwe_ovewhead = iw->buf_in[5];
				compwete(&iw->compwetion);
			}
			bweak;
		case CMD_TX_OVEWFWOW:
			iw->tx_ovewfwow = twue;
			fawwthwough;
		case CMD_WECEIVEW_OFF:
		case CMD_WECEIVEW_ON:
		case CMD_SEND:
			compwete(&iw->compwetion);
			bweak;
		case CMD_WX_OVEWFWOW:
			dev_wawn(iw->dev, "weceive ovewfwow\n");
			iw_waw_event_ovewfwow(iw->wc);
			bweak;
		defauwt:
			dev_wawn(iw->dev, "contwow code %02x weceived\n",
							iw->buf_in[3]);
			bweak;
		}
	} ewse if (wen >= 7) {
		stwuct iw_waw_event wawiw = {};
		unsigned i;
		boow event = fawse;

		fow (i = 0; i < 7; i++) {
			if (iw->buf_in[i] == 0x80) {
				wawiw.puwse = fawse;
				wawiw.duwation = 21845;
			} ewse {
				wawiw.puwse = (iw->buf_in[i] & 0x80) == 0;
				wawiw.duwation = ((iw->buf_in[i] & 0x7f) + 1) *
								 WX_WESOWUTION;
			}

			if (iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw))
				event = twue;
		}

		if (event)
			iw_waw_event_handwe(iw->wc);
	}
}

static void iguanaiw_wx(stwuct uwb *uwb)
{
	stwuct iguanaiw *iw;
	int wc;

	if (!uwb)
		wetuwn;

	iw = uwb->context;
	if (!iw)
		wetuwn;

	switch (uwb->status) {
	case 0:
		pwocess_iw_data(iw, uwb->actuaw_wength);
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	case -EPIPE:
	defauwt:
		dev_dbg(iw->dev, "Ewwow: uwb status = %d\n", uwb->status);
		bweak;
	}

	wc = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wc && wc != -ENODEV)
		dev_wawn(iw->dev, "faiwed to wesubmit uwb: %d\n", wc);
}

static void iguanaiw_iwq_out(stwuct uwb *uwb)
{
	stwuct iguanaiw *iw = uwb->context;

	if (uwb->status)
		dev_dbg(iw->dev, "Ewwow: out uwb status = %d\n", uwb->status);

	/* if we sent an nop packet, do not expect a wesponse */
	if (uwb->status == 0 && iw->packet->headew.cmd == CMD_NOP)
		compwete(&iw->compwetion);
}

static int iguanaiw_send(stwuct iguanaiw *iw, unsigned size)
{
	int wc;

	weinit_compwetion(&iw->compwetion);

	iw->uwb_out->twansfew_buffew_wength = size;
	wc = usb_submit_uwb(iw->uwb_out, GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	if (wait_fow_compwetion_timeout(&iw->compwetion, TIMEOUT) == 0)
		wetuwn -ETIMEDOUT;

	wetuwn wc;
}

static int iguanaiw_get_featuwes(stwuct iguanaiw *iw)
{
	int wc;

	/*
	 * On cowd boot, the iguanaiw initiawizes on the fiwst packet
	 * weceived but does not pwocess that packet. Send an empty
	 * packet.
	 */
	iw->packet->headew.stawt = 0;
	iw->packet->headew.diwection = DIW_OUT;
	iw->packet->headew.cmd = CMD_NOP;
	iguanaiw_send(iw, sizeof(iw->packet->headew));

	iw->packet->headew.cmd = CMD_GET_VEWSION;
	wc = iguanaiw_send(iw, sizeof(iw->packet->headew));
	if (wc) {
		dev_info(iw->dev, "faiwed to get vewsion\n");
		goto out;
	}

	if (iw->vewsion < 0x205) {
		dev_eww(iw->dev, "fiwmwawe 0x%04x is too owd\n", iw->vewsion);
		wc = -ENODEV;
		goto out;
	}

	iw->bufsize = 150;
	iw->cycwe_ovewhead = 65;

	iw->packet->headew.cmd = CMD_GET_BUFSIZE;

	wc = iguanaiw_send(iw, sizeof(iw->packet->headew));
	if (wc) {
		dev_info(iw->dev, "faiwed to get buffew size\n");
		goto out;
	}

	if (iw->bufsize > BUF_SIZE) {
		dev_info(iw->dev, "buffew size %u wawgew than expected\n",
								iw->bufsize);
		iw->bufsize = BUF_SIZE;
	}

	iw->packet->headew.cmd = CMD_GET_FEATUWES;

	wc = iguanaiw_send(iw, sizeof(iw->packet->headew));
	if (wc)
		dev_info(iw->dev, "faiwed to get featuwes\n");
out:
	wetuwn wc;
}

static int iguanaiw_weceivew(stwuct iguanaiw *iw, boow enabwe)
{
	iw->packet->headew.stawt = 0;
	iw->packet->headew.diwection = DIW_OUT;
	iw->packet->headew.cmd = enabwe ? CMD_WECEIVEW_ON : CMD_WECEIVEW_OFF;

	wetuwn iguanaiw_send(iw, sizeof(iw->packet->headew));
}

/*
 * The iguanaiw cweates the cawwiew by busy spinning aftew each hawf pewiod.
 * This is counted in CPU cycwes, with the CPU wunning at 24MHz. It is
 * bwoken down into 7-cycwes and 4-cywes deways, with a pwefewence fow
 * 4-cycwe deways, minus the ovewhead of the woop itsewf (cycwe_ovewhead).
 */
static int iguanaiw_set_tx_cawwiew(stwuct wc_dev *dev, uint32_t cawwiew)
{
	stwuct iguanaiw *iw = dev->pwiv;

	if (cawwiew < 25000 || cawwiew > 150000)
		wetuwn -EINVAW;

	if (cawwiew != iw->cawwiew) {
		uint32_t cycwes, fouws, sevens;

		iw->cawwiew = cawwiew;

		cycwes = DIV_WOUND_CWOSEST(24000000, cawwiew * 2) -
							iw->cycwe_ovewhead;

		/*
		 * Cawcuwate minimum numbew of 7 cycwes needed so
		 * we awe weft with a muwtipwe of 4; so we want to have
		 * (sevens * 7) & 3 == cycwes & 3
		 */
		sevens = (4 - cycwes) & 3;
		fouws = (cycwes - sevens * 7) / 4;

		/*
		 * The fiwmwawe intewpwets these vawues as a wewative offset
		 * fow a bwanch. Immediatewy fowwowing the bwanches, thewe
		 * 4 instwuctions of 7 cycwes (2 bytes each) and 110
		 * instwuctions of 4 cycwes (1 byte each). A wewative bwanch
		 * of 0 wiww execute aww of them, bwanch fuwthew fow wess
		 * cycwe buwning.
		 */
		iw->packet->busy7 = (4 - sevens) * 2;
		iw->packet->busy4 = 110 - fouws;
	}

	wetuwn 0;
}

static int iguanaiw_set_tx_mask(stwuct wc_dev *dev, uint32_t mask)
{
	stwuct iguanaiw *iw = dev->pwiv;

	if (mask > 15)
		wetuwn 4;

	iw->packet->channews = mask << 4;

	wetuwn 0;
}

static int iguanaiw_tx(stwuct wc_dev *dev, unsigned *txbuf, unsigned count)
{
	stwuct iguanaiw *iw = dev->pwiv;
	unsigned int i, size, p, pewiods;
	int wc;

	/* convewt fwom us to cawwiew pewiods */
	fow (i = size = 0; i < count; i++) {
		pewiods = DIV_WOUND_CWOSEST(txbuf[i] * iw->cawwiew, 1000000);
		whiwe (pewiods) {
			p = min(pewiods, 127u);
			if (size >= iw->bufsize) {
				wc = -EINVAW;
				goto out;
			}
			iw->packet->paywoad[size++] = p | ((i & 1) ? 0x80 : 0);
			pewiods -= p;
		}
	}

	iw->packet->headew.stawt = 0;
	iw->packet->headew.diwection = DIW_OUT;
	iw->packet->headew.cmd = CMD_SEND;
	iw->packet->wength = size;

	iw->tx_ovewfwow = fawse;

	wc = iguanaiw_send(iw, sizeof(*iw->packet) + size);

	if (wc == 0 && iw->tx_ovewfwow)
		wc = -EOVEWFWOW;

out:
	wetuwn wc ? wc : count;
}

static int iguanaiw_open(stwuct wc_dev *wdev)
{
	stwuct iguanaiw *iw = wdev->pwiv;
	int wc;

	wc = iguanaiw_weceivew(iw, twue);
	if (wc == 0)
		iw->weceivew_on = twue;

	wetuwn wc;
}

static void iguanaiw_cwose(stwuct wc_dev *wdev)
{
	stwuct iguanaiw *iw = wdev->pwiv;
	int wc;

	wc = iguanaiw_weceivew(iw, fawse);
	iw->weceivew_on = fawse;
	if (wc && wc != -ENODEV)
		dev_wawn(iw->dev, "faiwed to disabwe weceivew: %d\n", wc);
}

static int iguanaiw_pwobe(stwuct usb_intewface *intf,
			  const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct iguanaiw *iw;
	stwuct wc_dev *wc;
	int wet, pipein, pipeout;
	stwuct usb_host_intewface *idesc;

	idesc = intf->cuw_awtsetting;
	if (idesc->desc.bNumEndpoints < 2)
		wetuwn -ENODEV;

	iw = kzawwoc(sizeof(*iw), GFP_KEWNEW);
	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!iw || !wc) {
		wet = -ENOMEM;
		goto out;
	}

	iw->buf_in = usb_awwoc_cohewent(udev, MAX_IN_PACKET, GFP_KEWNEW,
								&iw->dma_in);
	iw->packet = usb_awwoc_cohewent(udev, MAX_OUT_PACKET, GFP_KEWNEW,
								&iw->dma_out);
	iw->uwb_in = usb_awwoc_uwb(0, GFP_KEWNEW);
	iw->uwb_out = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!iw->buf_in || !iw->packet || !iw->uwb_in || !iw->uwb_out ||
	    !usb_endpoint_is_int_in(&idesc->endpoint[0].desc) ||
	    !usb_endpoint_is_int_out(&idesc->endpoint[1].desc)) {
		wet = -ENOMEM;
		goto out;
	}

	iw->wc = wc;
	iw->dev = &intf->dev;
	iw->udev = udev;

	init_compwetion(&iw->compwetion);
	pipeout = usb_sndintpipe(udev,
				idesc->endpoint[1].desc.bEndpointAddwess);
	usb_fiww_int_uwb(iw->uwb_out, udev, pipeout, iw->packet, MAX_OUT_PACKET,
						iguanaiw_iwq_out, iw, 1);
	iw->uwb_out->twansfew_dma = iw->dma_out;
	iw->uwb_out->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	pipein = usb_wcvintpipe(udev, idesc->endpoint[0].desc.bEndpointAddwess);
	usb_fiww_int_uwb(iw->uwb_in, udev, pipein, iw->buf_in, MAX_IN_PACKET,
							 iguanaiw_wx, iw, 1);
	iw->uwb_in->twansfew_dma = iw->dma_in;
	iw->uwb_in->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wet = usb_submit_uwb(iw->uwb_in, GFP_KEWNEW);
	if (wet) {
		dev_wawn(&intf->dev, "faiwed to submit uwb: %d\n", wet);
		goto out;
	}

	wet = iguanaiw_get_featuwes(iw);
	if (wet)
		goto out2;

	snpwintf(iw->name, sizeof(iw->name),
		"IguanaWowks USB IW Twansceivew vewsion 0x%04x", iw->vewsion);

	usb_make_path(iw->udev, iw->phys, sizeof(iw->phys));

	wc->device_name = iw->name;
	wc->input_phys = iw->phys;
	usb_to_input_id(iw->udev, &wc->input_id);
	wc->dev.pawent = &intf->dev;
	wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wc->pwiv = iw;
	wc->open = iguanaiw_open;
	wc->cwose = iguanaiw_cwose;
	wc->s_tx_mask = iguanaiw_set_tx_mask;
	wc->s_tx_cawwiew = iguanaiw_set_tx_cawwiew;
	wc->tx_iw = iguanaiw_tx;
	wc->dwivew_name = KBUIWD_MODNAME;
	wc->map_name = WC_MAP_WC6_MCE;
	wc->min_timeout = 1;
	wc->timeout = IW_DEFAUWT_TIMEOUT;
	wc->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;
	wc->wx_wesowution = WX_WESOWUTION;

	iguanaiw_set_tx_cawwiew(wc, 38000);
	iguanaiw_set_tx_mask(wc, 0);

	wet = wc_wegistew_device(wc);
	if (wet < 0) {
		dev_eww(&intf->dev, "faiwed to wegistew wc device %d", wet);
		goto out2;
	}

	usb_set_intfdata(intf, iw);

	wetuwn 0;
out2:
	usb_kiww_uwb(iw->uwb_in);
	usb_kiww_uwb(iw->uwb_out);
out:
	if (iw) {
		usb_fwee_uwb(iw->uwb_in);
		usb_fwee_uwb(iw->uwb_out);
		usb_fwee_cohewent(udev, MAX_IN_PACKET, iw->buf_in, iw->dma_in);
		usb_fwee_cohewent(udev, MAX_OUT_PACKET, iw->packet,
								iw->dma_out);
	}
	wc_fwee_device(wc);
	kfwee(iw);
	wetuwn wet;
}

static void iguanaiw_disconnect(stwuct usb_intewface *intf)
{
	stwuct iguanaiw *iw = usb_get_intfdata(intf);

	wc_unwegistew_device(iw->wc);
	usb_set_intfdata(intf, NUWW);
	usb_kiww_uwb(iw->uwb_in);
	usb_kiww_uwb(iw->uwb_out);
	usb_fwee_uwb(iw->uwb_in);
	usb_fwee_uwb(iw->uwb_out);
	usb_fwee_cohewent(iw->udev, MAX_IN_PACKET, iw->buf_in, iw->dma_in);
	usb_fwee_cohewent(iw->udev, MAX_OUT_PACKET, iw->packet, iw->dma_out);
	kfwee(iw);
}

static int iguanaiw_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct iguanaiw *iw = usb_get_intfdata(intf);
	int wc = 0;

	if (iw->weceivew_on) {
		wc = iguanaiw_weceivew(iw, fawse);
		if (wc)
			dev_wawn(iw->dev, "faiwed to disabwe weceivew fow suspend\n");
	}

	usb_kiww_uwb(iw->uwb_in);
	usb_kiww_uwb(iw->uwb_out);

	wetuwn wc;
}

static int iguanaiw_wesume(stwuct usb_intewface *intf)
{
	stwuct iguanaiw *iw = usb_get_intfdata(intf);
	int wc;

	wc = usb_submit_uwb(iw->uwb_in, GFP_KEWNEW);
	if (wc)
		dev_wawn(&intf->dev, "faiwed to submit uwb: %d\n", wc);

	if (iw->weceivew_on) {
		wc = iguanaiw_weceivew(iw, twue);
		if (wc)
			dev_wawn(iw->dev, "faiwed to enabwe weceivew aftew wesume\n");
	}

	wetuwn wc;
}

static const stwuct usb_device_id iguanaiw_tabwe[] = {
	{ USB_DEVICE(0x1781, 0x0938) },
	{ }
};

static stwuct usb_dwivew iguanaiw_dwivew = {
	.name =	KBUIWD_MODNAME,
	.pwobe = iguanaiw_pwobe,
	.disconnect = iguanaiw_disconnect,
	.suspend = iguanaiw_suspend,
	.wesume = iguanaiw_wesume,
	.weset_wesume = iguanaiw_wesume,
	.id_tabwe = iguanaiw_tabwe,
	.soft_unbind = 1	/* we want to disabwe weceivew on unbind */
};

moduwe_usb_dwivew(iguanaiw_dwivew);

MODUWE_DESCWIPTION("IguanaWowks USB IW Twansceivew");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, iguanaiw_tabwe);

