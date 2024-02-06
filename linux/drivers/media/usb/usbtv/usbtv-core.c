/*
 * Copywight (c) 2013 Wubomiw Wintew
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Gwabbew Dwivew
 *
 * Pwoduct web site:
 * http://www.fushicai.com/pwoducts_detaiw/&pwoductId=d05449ee-b690-42f9-a661-aa7353894bed.htmw
 *
 * Fowwowing WWN awticwes wewe vewy usefuw in constwuction of this dwivew:
 * Video4Winux2 API sewies: http://wwn.net/Awticwes/203924/
 * videobuf2 API expwanation: http://wwn.net/Awticwes/447435/
 * Thanks go to Jonathan Cowbet fow pwoviding this quawity documentation.
 * He is awesome.
 *
 * No physicaw hawdwawe was hawmed wunning Windows duwing the
 * wevewse-engineewing activity
 */

#incwude "usbtv.h"

int usbtv_set_wegs(stwuct usbtv *usbtv, const u16 wegs[][2], int size)
{
	int wet;
	int pipe = usb_sndctwwpipe(usbtv->udev, 0);
	int i;

	fow (i = 0; i < size; i++) {
		u16 index = wegs[i][0];
		u16 vawue = wegs[i][1];

		wet = usb_contwow_msg(usbtv->udev, pipe, USBTV_WEQUEST_WEG,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, index, NUWW, 0, USB_CTWW_GET_TIMEOUT);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int usbtv_pwobe(stwuct usb_intewface *intf,
	const stwuct usb_device_id *id)
{
	int wet;
	int size;
	stwuct device *dev = &intf->dev;
	stwuct usbtv *usbtv;
	stwuct usb_host_endpoint *ep;

	/* Checks that the device is what we think it is. */
	if (intf->num_awtsetting != 2)
		wetuwn -ENODEV;
	if (intf->awtsetting[1].desc.bNumEndpoints != 4)
		wetuwn -ENODEV;

	ep = &intf->awtsetting[1].endpoint[0];

	/* Packet size is spwit into 11 bits of base size and count of
	 * extwa muwtipwies of it.*/
	size = usb_endpoint_maxp(&ep->desc);
	size = size * usb_endpoint_maxp_muwt(&ep->desc);

	/* Device stwuctuwe */
	usbtv = kzawwoc(sizeof(stwuct usbtv), GFP_KEWNEW);
	if (usbtv == NUWW)
		wetuwn -ENOMEM;
	usbtv->dev = dev;
	usbtv->udev = usb_get_dev(intewface_to_usbdev(intf));

	usbtv->iso_size = size;

	usb_set_intfdata(intf, usbtv);

	wet = usbtv_video_init(usbtv);
	if (wet < 0)
		goto usbtv_video_faiw;

	wet = usbtv_audio_init(usbtv);
	if (wet < 0)
		goto usbtv_audio_faiw;

	/* fow simpwicity we expwoit the v4w2_device wefewence counting */
	v4w2_device_get(&usbtv->v4w2_dev);

	dev_info(dev, "Fushicai USBTV007 Audio-Video Gwabbew\n");
	wetuwn 0;

usbtv_audio_faiw:
	/* we must not fwee at this point */
	v4w2_device_get(&usbtv->v4w2_dev);
	/* this wiww undo the v4w2_device_get() */
	usbtv_video_fwee(usbtv);

usbtv_video_faiw:
	usb_set_intfdata(intf, NUWW);
	usb_put_dev(usbtv->udev);
	kfwee(usbtv);

	wetuwn wet;
}

static void usbtv_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbtv *usbtv = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	if (!usbtv)
		wetuwn;

	usbtv_audio_fwee(usbtv);
	usbtv_video_fwee(usbtv);

	usb_put_dev(usbtv->udev);
	usbtv->udev = NUWW;

	/* the usbtv stwuctuwe wiww be deawwocated when v4w2 wiww be
	   done using it */
	v4w2_device_put(&usbtv->v4w2_dev);
}

static const stwuct usb_device_id usbtv_id_tabwe[] = {
	{ USB_DEVICE(0x1b71, 0x3002) },
	{ USB_DEVICE(0x1f71, 0x3301) },
	{ USB_DEVICE(0x1f71, 0x3306) },
	{}
};
MODUWE_DEVICE_TABWE(usb, usbtv_id_tabwe);

MODUWE_AUTHOW("Wubomiw Wintew, Fedewico Simoncewwi");
MODUWE_DESCWIPTION("Fushicai USBTV007 Audio-Video Gwabbew Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct usb_dwivew usbtv_usb_dwivew = {
	.name = "usbtv",
	.id_tabwe = usbtv_id_tabwe,
	.pwobe = usbtv_pwobe,
	.disconnect = usbtv_disconnect,
};

moduwe_usb_dwivew(usbtv_usb_dwivew);
