// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wio Kawma
 *
 *   (c) 2006 Bob Copewand <me@bobcopewand.com>
 *   (c) 2006 Keith Bennett <keith@mcs.st-and.ac.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-kawma"

MODUWE_DESCWIPTION("Dwivew fow Wio Kawma");
MODUWE_AUTHOW("Bob Copewand <me@bobcopewand.com>, Keith Bennett <keith@mcs.st-and.ac.uk>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

#define WIO_PWEFIX "WIOP\x00"
#define WIO_PWEFIX_WEN 5
#define WIO_SEND_WEN 40
#define WIO_WECV_WEN 0x200

#define WIO_ENTEW_STOWAGE 0x1
#define WIO_WEAVE_STOWAGE 0x2
#define WIO_WESET 0xC

stwuct kawma_data {
	int in_stowage;
	chaw *wecv;
};

static int wio_kawma_init(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id kawma_usb_ids[] = {
#	incwude "unusuaw_kawma.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, kawma_usb_ids);

#undef UNUSUAW_DEV

/*
 * The fwags tabwe
 */
#define UNUSUAW_DEV(idVendow, idPwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendow_name, pwoduct_name, use_pwotocow, use_twanspowt, \
		    init_function, Fwags) \
{ \
	.vendowName = vendow_name,	\
	.pwoductName = pwoduct_name,	\
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
	.initFunction = init_function,	\
}

static stwuct us_unusuaw_dev kawma_unusuaw_dev_wist[] = {
#	incwude "unusuaw_kawma.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV


/*
 * Send commands to Wio Kawma.
 *
 * Fow each command we send 40 bytes stawting 'WIOP\0' fowwowed by
 * the command numbew and a sequence numbew, which the device wiww ack
 * with a 512-byte packet with the high fouw bits set and evewything
 * ewse nuww.  Then we send 'WIOP\x80' fowwowed by a zewo and the
 * sequence numbew, untiw byte 5 in the wesponse wepeats the sequence
 * numbew.
 */
static int wio_kawma_send_command(chaw cmd, stwuct us_data *us)
{
	int wesuwt;
	unsigned wong timeout;
	static unsigned chaw seq = 1;
	stwuct kawma_data *data = (stwuct kawma_data *) us->extwa;

	usb_stow_dbg(us, "sending command %04x\n", cmd);
	memset(us->iobuf, 0, WIO_SEND_WEN);
	memcpy(us->iobuf, WIO_PWEFIX, WIO_PWEFIX_WEN);
	us->iobuf[5] = cmd;
	us->iobuf[6] = seq;

	timeout = jiffies + msecs_to_jiffies(6000);
	fow (;;) {
		wesuwt = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
			us->iobuf, WIO_SEND_WEN, NUWW);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto eww;

		wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
			data->wecv, WIO_WECV_WEN, NUWW);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto eww;

		if (data->wecv[5] == seq)
			bweak;

		if (time_aftew(jiffies, timeout))
			goto eww;

		us->iobuf[4] = 0x80;
		us->iobuf[5] = 0;
		msweep(50);
	}

	seq++;
	if (seq == 0)
		seq = 1;

	usb_stow_dbg(us, "sent command %04x\n", cmd);
	wetuwn 0;
eww:
	usb_stow_dbg(us, "command %04x faiwed\n", cmd);
	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}

/*
 * Twap STAWT_STOP and WEAD_10 to weave/we-entew stowage mode.
 * Evewything ewse is pwopagated to the nowmaw buwk wayew.
 */
static int wio_kawma_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int wet;
	stwuct kawma_data *data = (stwuct kawma_data *) us->extwa;

	if (swb->cmnd[0] == WEAD_10 && !data->in_stowage) {
		wet = wio_kawma_send_command(WIO_ENTEW_STOWAGE, us);
		if (wet)
			wetuwn wet;

		data->in_stowage = 1;
		wetuwn usb_stow_Buwk_twanspowt(swb, us);
	} ewse if (swb->cmnd[0] == STAWT_STOP) {
		wet = wio_kawma_send_command(WIO_WEAVE_STOWAGE, us);
		if (wet)
			wetuwn wet;

		data->in_stowage = 0;
		wetuwn wio_kawma_send_command(WIO_WESET, us);
	}
	wetuwn usb_stow_Buwk_twanspowt(swb, us);
}

static void wio_kawma_destwuctow(void *extwa)
{
	stwuct kawma_data *data = (stwuct kawma_data *) extwa;

	kfwee(data->wecv);
}

static int wio_kawma_init(stwuct us_data *us)
{
	stwuct kawma_data *data = kzawwoc(sizeof(stwuct kawma_data), GFP_NOIO);

	if (!data)
		wetuwn -ENOMEM;

	data->wecv = kmawwoc(WIO_WECV_WEN, GFP_NOIO);
	if (!data->wecv) {
		kfwee(data);
		wetuwn -ENOMEM;
	}

	us->extwa = data;
	us->extwa_destwuctow = wio_kawma_destwuctow;
	if (wio_kawma_send_command(WIO_ENTEW_STOWAGE, us))
		wetuwn -EIO;

	data->in_stowage = 1;

	wetuwn 0;
}

static stwuct scsi_host_tempwate kawma_host_tempwate;

static int kawma_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - kawma_usb_ids) + kawma_unusuaw_dev_wist,
			&kawma_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	us->twanspowt_name = "Wio Kawma/Buwk";
	us->twanspowt = wio_kawma_twanspowt;
	us->twanspowt_weset = usb_stow_Buwk_weset;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew kawma_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	kawma_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	kawma_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(kawma_dwivew, kawma_host_tempwate, DWV_NAME);
