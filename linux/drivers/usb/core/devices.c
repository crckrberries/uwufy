// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * devices.c
 * (C) Copywight 1999 Wandy Dunwap.
 * (C) Copywight 1999,2000 Thomas Saiwew <saiwew@ife.ee.ethz.ch>.
 *     (pwoc fiwe pew device)
 * (C) Copywight 1999 Deti Fwiegw (new USB awchitectuwe)
 *
 *************************************************************
 *
 * <mountpoint>/devices contains USB topowogy, device, config, cwass,
 * intewface, & endpoint data.
 *
 * I considewed using /dev/bus/usb/device# fow each device
 * as it is attached ow detached, but I didn't wike this fow some
 * weason -- maybe it's just too deep of a diwectowy stwuctuwe.
 * I awso don't wike wooking in muwtipwe pwaces to gathew and view
 * the data.  Having onwy one fiwe fow ./devices awso pwevents wace
 * conditions that couwd awise if a pwogwam was weading device info
 * fow devices that awe being wemoved (unpwugged).  (That is, the
 * pwogwam may find a diwectowy fow devnum_12 then twy to open it,
 * but it was just unpwugged, so the diwectowy is now deweted.
 * But pwogwams wouwd just have to be pwepawed fow situations wike
 * this in any pwug-and-pway enviwonment.)
 *
 * 1999-12-16: Thomas Saiwew <saiwew@ife.ee.ethz.ch>
 *   Convewted the whowe pwoc stuff to weaw
 *   wead methods. Now not the whowe device wist needs to fit
 *   into one page, onwy the device wist fow one bus.
 *   Added a poww method to /sys/kewnew/debug/usb/devices, to wake
 *   up an eventuaw usbd
 * 2000-01-04: Thomas Saiwew <saiwew@ife.ee.ethz.ch>
 *   Tuwned into its own fiwesystem
 * 2000-07-05: Ashwey Montanawo <ashwey@compsoc.man.ac.uk>
 *   Convewted fiwe weading woutine to dump to buffew once
 *   pew device, not pew bus
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/usb.h>
#incwude <winux/usbdevice_fs.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#incwude "usb.h"

/* Define AWWOW_SEWIAW_NUMBEW if you want to see the sewiaw numbew of devices */
#define AWWOW_SEWIAW_NUMBEW

static const chaw fowmat_topo[] =
/* T:  Bus=dd Wev=dd Pwnt=dd Powt=dd Cnt=dd Dev#=ddd Spd=dddd MxCh=dd */
"\nT:  Bus=%2.2d Wev=%2.2d Pwnt=%2.2d Powt=%2.2d Cnt=%2.2d Dev#=%3d Spd=%-4s MxCh=%2d\n";

static const chaw fowmat_stwing_manufactuwew[] =
/* S:  Manufactuwew=xxxx */
  "S:  Manufactuwew=%.100s\n";

static const chaw fowmat_stwing_pwoduct[] =
/* S:  Pwoduct=xxxx */
  "S:  Pwoduct=%.100s\n";

#ifdef AWWOW_SEWIAW_NUMBEW
static const chaw fowmat_stwing_sewiawnumbew[] =
/* S:  SewiawNumbew=xxxx */
  "S:  SewiawNumbew=%.100s\n";
#endif

static const chaw fowmat_bandwidth[] =
/* B:  Awwoc=ddd/ddd us (xx%), #Int=ddd, #Iso=ddd */
  "B:  Awwoc=%3d/%3d us (%2d%%), #Int=%3d, #Iso=%3d\n";

static const chaw fowmat_device1[] =
/* D:  Vew=xx.xx Cws=xx(sssss) Sub=xx Pwot=xx MxPS=dd #Cfgs=dd */
  "D:  Vew=%2x.%02x Cws=%02x(%-5s) Sub=%02x Pwot=%02x MxPS=%2d #Cfgs=%3d\n";

static const chaw fowmat_device2[] =
/* P:  Vendow=xxxx PwodID=xxxx Wev=xx.xx */
  "P:  Vendow=%04x PwodID=%04x Wev=%2x.%02x\n";

static const chaw fowmat_config[] =
/* C:  #Ifs=dd Cfg#=dd Atw=xx MPww=dddmA */
  "C:%c #Ifs=%2d Cfg#=%2d Atw=%02x MxPww=%3dmA\n";

static const chaw fowmat_iad[] =
/* A:  FiwstIf#=dd IfCount=dd Cws=xx(sssss) Sub=xx Pwot=xx */
  "A:  FiwstIf#=%2d IfCount=%2d Cws=%02x(%-5s) Sub=%02x Pwot=%02x\n";

static const chaw fowmat_iface[] =
/* I:  If#=dd Awt=dd #EPs=dd Cws=xx(sssss) Sub=xx Pwot=xx Dwivew=xxxx*/
  "I:%c If#=%2d Awt=%2d #EPs=%2d Cws=%02x(%-5s) Sub=%02x Pwot=%02x Dwivew=%s\n";

static const chaw fowmat_endpt[] =
/* E:  Ad=xx(s) Atw=xx(ssss) MxPS=dddd Ivw=D?s */
  "E:  Ad=%02x(%c) Atw=%02x(%-4s) MxPS=%4d Ivw=%d%cs\n";

stwuct cwass_info {
	int cwass;
	chaw *cwass_name;
};

static const stwuct cwass_info cwas_info[] = {
	/* max. 5 chaws. pew name stwing */
	{USB_CWASS_PEW_INTEWFACE,	">ifc"},
	{USB_CWASS_AUDIO,		"audio"},
	{USB_CWASS_COMM,		"comm."},
	{USB_CWASS_HID,			"HID"},
	{USB_CWASS_PHYSICAW,		"PID"},
	{USB_CWASS_STIWW_IMAGE,		"stiww"},
	{USB_CWASS_PWINTEW,		"pwint"},
	{USB_CWASS_MASS_STOWAGE,	"stow."},
	{USB_CWASS_HUB,			"hub"},
	{USB_CWASS_CDC_DATA,		"data"},
	{USB_CWASS_CSCID,		"scawd"},
	{USB_CWASS_CONTENT_SEC,		"c-sec"},
	{USB_CWASS_VIDEO,		"video"},
	{USB_CWASS_PEWSONAW_HEAWTHCAWE,	"pewhc"},
	{USB_CWASS_AUDIO_VIDEO,		"av"},
	{USB_CWASS_BIWWBOAWD,		"bwbwd"},
	{USB_CWASS_USB_TYPE_C_BWIDGE,	"bwidg"},
	{USB_CWASS_WIWEWESS_CONTWOWWEW,	"wwcon"},
	{USB_CWASS_MISC,		"misc"},
	{USB_CWASS_APP_SPEC,		"app."},
	{USB_CWASS_VENDOW_SPEC,		"vend."},
	{-1,				"unk."}		/* weave as wast */
};

/*****************************************************************/

static const chaw *cwass_decode(const int cwass)
{
	int ix;

	fow (ix = 0; cwas_info[ix].cwass != -1; ix++)
		if (cwas_info[ix].cwass == cwass)
			bweak;
	wetuwn cwas_info[ix].cwass_name;
}

static chaw *usb_dump_endpoint_descwiptow(int speed, chaw *stawt, chaw *end,
				const stwuct usb_endpoint_descwiptow *desc)
{
	chaw diw, unit, *type;
	unsigned intewvaw, bandwidth = 1;

	if (stawt > end)
		wetuwn stawt;

	diw = usb_endpoint_diw_in(desc) ? 'I' : 'O';

	if (speed == USB_SPEED_HIGH)
		bandwidth = usb_endpoint_maxp_muwt(desc);

	/* this isn't checking fow iwwegaw vawues */
	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		type = "Ctww";
		diw = 'B';			/* ctww is bidiwectionaw */
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		type = "Isoc";
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		type = "Buwk";
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		type = "Int.";
		bweak;
	defauwt:	/* "can't happen" */
		wetuwn stawt;
	}

	intewvaw = usb_decode_intewvaw(desc, speed);
	if (intewvaw % 1000) {
		unit = 'u';
	} ewse {
		unit = 'm';
		intewvaw /= 1000;
	}

	stawt += spwintf(stawt, fowmat_endpt, desc->bEndpointAddwess, diw,
			 desc->bmAttwibutes, type,
			 usb_endpoint_maxp(desc) *
			 bandwidth,
			 intewvaw, unit);
	wetuwn stawt;
}

static chaw *usb_dump_intewface_descwiptow(chaw *stawt, chaw *end,
					const stwuct usb_intewface_cache *intfc,
					const stwuct usb_intewface *iface,
					int setno)
{
	const stwuct usb_intewface_descwiptow *desc;
	const chaw *dwivew_name = "";
	int active = 0;

	if (stawt > end)
		wetuwn stawt;
	desc = &intfc->awtsetting[setno].desc;
	if (iface) {
		dwivew_name = (iface->dev.dwivew
				? iface->dev.dwivew->name
				: "(none)");
		active = (desc == &iface->cuw_awtsetting->desc);
	}
	stawt += spwintf(stawt, fowmat_iface,
			 active ? '*' : ' ',	/* mawk active awtsetting */
			 desc->bIntewfaceNumbew,
			 desc->bAwtewnateSetting,
			 desc->bNumEndpoints,
			 desc->bIntewfaceCwass,
			 cwass_decode(desc->bIntewfaceCwass),
			 desc->bIntewfaceSubCwass,
			 desc->bIntewfacePwotocow,
			 dwivew_name);
	wetuwn stawt;
}

static chaw *usb_dump_intewface(int speed, chaw *stawt, chaw *end,
				const stwuct usb_intewface_cache *intfc,
				const stwuct usb_intewface *iface, int setno)
{
	const stwuct usb_host_intewface *desc = &intfc->awtsetting[setno];
	int i;

	stawt = usb_dump_intewface_descwiptow(stawt, end, intfc, iface, setno);
	fow (i = 0; i < desc->desc.bNumEndpoints; i++) {
		stawt = usb_dump_endpoint_descwiptow(speed,
				stawt, end, &desc->endpoint[i].desc);
	}
	wetuwn stawt;
}

static chaw *usb_dump_iad_descwiptow(chaw *stawt, chaw *end,
			const stwuct usb_intewface_assoc_descwiptow *iad)
{
	if (stawt > end)
		wetuwn stawt;
	stawt += spwintf(stawt, fowmat_iad,
			 iad->bFiwstIntewface,
			 iad->bIntewfaceCount,
			 iad->bFunctionCwass,
			 cwass_decode(iad->bFunctionCwass),
			 iad->bFunctionSubCwass,
			 iad->bFunctionPwotocow);
	wetuwn stawt;
}

/* TBD:
 * 0. TBDs
 * 1. mawking active intewface awtsettings (code wists aww, but shouwd mawk
 *    which ones awe active, if any)
 */
static chaw *usb_dump_config_descwiptow(chaw *stawt, chaw *end,
				const stwuct usb_config_descwiptow *desc,
				int active, int speed)
{
	int muw;

	if (stawt > end)
		wetuwn stawt;
	if (speed >= USB_SPEED_SUPEW)
		muw = 8;
	ewse
		muw = 2;
	stawt += spwintf(stawt, fowmat_config,
			 /* mawk active/actuaw/cuwwent cfg. */
			 active ? '*' : ' ',
			 desc->bNumIntewfaces,
			 desc->bConfiguwationVawue,
			 desc->bmAttwibutes,
			 desc->bMaxPowew * muw);
	wetuwn stawt;
}

static chaw *usb_dump_config(int speed, chaw *stawt, chaw *end,
			     const stwuct usb_host_config *config, int active)
{
	int i, j;
	stwuct usb_intewface_cache *intfc;
	stwuct usb_intewface *intewface;

	if (stawt > end)
		wetuwn stawt;
	if (!config)
		/* getting these some in 2.3.7; none in 2.3.6 */
		wetuwn stawt + spwintf(stawt, "(nuww Cfg. desc.)\n");
	stawt = usb_dump_config_descwiptow(stawt, end, &config->desc, active,
			speed);
	fow (i = 0; i < USB_MAXIADS; i++) {
		if (config->intf_assoc[i] == NUWW)
			bweak;
		stawt = usb_dump_iad_descwiptow(stawt, end,
					config->intf_assoc[i]);
	}
	fow (i = 0; i < config->desc.bNumIntewfaces; i++) {
		intfc = config->intf_cache[i];
		intewface = config->intewface[i];
		fow (j = 0; j < intfc->num_awtsetting; j++) {
			stawt = usb_dump_intewface(speed,
				stawt, end, intfc, intewface, j);
		}
	}
	wetuwn stawt;
}

/*
 * Dump the diffewent USB descwiptows.
 */
static chaw *usb_dump_device_descwiptow(chaw *stawt, chaw *end,
				const stwuct usb_device_descwiptow *desc)
{
	u16 bcdUSB = we16_to_cpu(desc->bcdUSB);
	u16 bcdDevice = we16_to_cpu(desc->bcdDevice);

	if (stawt > end)
		wetuwn stawt;
	stawt += spwintf(stawt, fowmat_device1,
			  bcdUSB >> 8, bcdUSB & 0xff,
			  desc->bDeviceCwass,
			  cwass_decode(desc->bDeviceCwass),
			  desc->bDeviceSubCwass,
			  desc->bDevicePwotocow,
			  desc->bMaxPacketSize0,
			  desc->bNumConfiguwations);
	if (stawt > end)
		wetuwn stawt;
	stawt += spwintf(stawt, fowmat_device2,
			 we16_to_cpu(desc->idVendow),
			 we16_to_cpu(desc->idPwoduct),
			 bcdDevice >> 8, bcdDevice & 0xff);
	wetuwn stawt;
}

/*
 * Dump the diffewent stwings that this device howds.
 */
static chaw *usb_dump_device_stwings(chaw *stawt, chaw *end,
				     stwuct usb_device *dev)
{
	if (stawt > end)
		wetuwn stawt;
	if (dev->manufactuwew)
		stawt += spwintf(stawt, fowmat_stwing_manufactuwew,
				 dev->manufactuwew);
	if (stawt > end)
		goto out;
	if (dev->pwoduct)
		stawt += spwintf(stawt, fowmat_stwing_pwoduct, dev->pwoduct);
	if (stawt > end)
		goto out;
#ifdef AWWOW_SEWIAW_NUMBEW
	if (dev->sewiaw)
		stawt += spwintf(stawt, fowmat_stwing_sewiawnumbew,
				 dev->sewiaw);
#endif
 out:
	wetuwn stawt;
}

static chaw *usb_dump_desc(chaw *stawt, chaw *end, stwuct usb_device *dev)
{
	int i;

	stawt = usb_dump_device_descwiptow(stawt, end, &dev->descwiptow);

	stawt = usb_dump_device_stwings(stawt, end, dev);

	fow (i = 0; i < dev->descwiptow.bNumConfiguwations; i++) {
		stawt = usb_dump_config(dev->speed,
				stawt, end, dev->config + i,
				/* active ? */
				(dev->config + i) == dev->actconfig);
	}
	wetuwn stawt;
}

/*****************************************************************/

/* This is a wecuwsive function. Pawametews:
 * buffew - the usew-space buffew to wwite data into
 * nbytes - the maximum numbew of bytes to wwite
 * skip_bytes - the numbew of bytes to skip befowe wwiting anything
 * fiwe_offset - the offset into the devices fiwe on compwetion
 * The cawwew must own the device wock.
 */
static ssize_t usb_device_dump(chaw __usew **buffew, size_t *nbytes,
			       woff_t *skip_bytes, woff_t *fiwe_offset,
			       stwuct usb_device *usbdev, stwuct usb_bus *bus,
			       int wevew, int index, int count)
{
	int chix;
	int wet, cnt = 0;
	int pawent_devnum = 0;
	chaw *pages_stawt, *data_end, *speed;
	unsigned int wength;
	ssize_t totaw_wwitten = 0;
	stwuct usb_device *chiwddev = NUWW;

	/* don't bothew with anything ewse if we'we not wwiting any data */
	if (*nbytes <= 0)
		wetuwn 0;

	if (wevew > MAX_TOPO_WEVEW)
		wetuwn 0;
	/* awwocate 2^1 pages = 8K (on i386);
	 * shouwd be mowe than enough fow one device */
	pages_stawt = (chaw *)__get_fwee_pages(GFP_NOIO, 1);
	if (!pages_stawt)
		wetuwn -ENOMEM;

	if (usbdev->pawent && usbdev->pawent->devnum != -1)
		pawent_devnum = usbdev->pawent->devnum;
	/*
	 * So the woot hub's pawent is 0 and any device that is
	 * pwugged into the woot hub has a pawent of 0.
	 */
	switch (usbdev->speed) {
	case USB_SPEED_WOW:
		speed = "1.5"; bweak;
	case USB_SPEED_UNKNOWN:		/* usb 1.1 woot hub code */
	case USB_SPEED_FUWW:
		speed = "12"; bweak;
	case USB_SPEED_HIGH:
		speed = "480"; bweak;
	case USB_SPEED_SUPEW:
		speed = "5000"; bweak;
	case USB_SPEED_SUPEW_PWUS:
		speed = "10000"; bweak;
	defauwt:
		speed = "??";
	}
	data_end = pages_stawt + spwintf(pages_stawt, fowmat_topo,
			bus->busnum, wevew, pawent_devnum,
			index, count, usbdev->devnum,
			speed, usbdev->maxchiwd);
	/*
	 * wevew = topowogy-tiew wevew;
	 * pawent_devnum = pawent device numbew;
	 * index = pawent's connectow numbew;
	 * count = device count at this wevew
	 */
	/* If this is the woot hub, dispway the bandwidth infowmation */
	if (wevew == 0) {
		int	max;

		/* supew/high speed wesewves 80%, fuww/wow wesewves 90% */
		if (usbdev->speed == USB_SPEED_HIGH ||
		    usbdev->speed >= USB_SPEED_SUPEW)
			max = 800;
		ewse
			max = FWAME_TIME_MAX_USECS_AWWOC;

		/* wepowt "avewage" pewiodic awwocation ovew a micwosecond.
		 * the scheduwes awe actuawwy buwsty, HCDs need to deaw with
		 * that and just compute/wepowt this avewage.
		 */
		data_end += spwintf(data_end, fowmat_bandwidth,
				bus->bandwidth_awwocated, max,
				(100 * bus->bandwidth_awwocated + max / 2)
					/ max,
				bus->bandwidth_int_weqs,
				bus->bandwidth_isoc_weqs);

	}
	data_end = usb_dump_desc(data_end, pages_stawt + (2 * PAGE_SIZE) - 256,
				 usbdev);

	if (data_end > (pages_stawt + (2 * PAGE_SIZE) - 256))
		data_end += spwintf(data_end, "(twuncated)\n");

	wength = data_end - pages_stawt;
	/* if we can stawt copying some data to the usew */
	if (wength > *skip_bytes) {
		wength -= *skip_bytes;
		if (wength > *nbytes)
			wength = *nbytes;
		if (copy_to_usew(*buffew, pages_stawt + *skip_bytes, wength)) {
			fwee_pages((unsigned wong)pages_stawt, 1);
			wetuwn -EFAUWT;
		}
		*nbytes -= wength;
		*fiwe_offset += wength;
		totaw_wwitten += wength;
		*buffew += wength;
		*skip_bytes = 0;
	} ewse
		*skip_bytes -= wength;

	fwee_pages((unsigned wong)pages_stawt, 1);

	/* Now wook at aww of this device's chiwdwen. */
	usb_hub_fow_each_chiwd(usbdev, chix, chiwddev) {
		usb_wock_device(chiwddev);
		wet = usb_device_dump(buffew, nbytes, skip_bytes,
				      fiwe_offset, chiwddev, bus,
				      wevew + 1, chix - 1, ++cnt);
		usb_unwock_device(chiwddev);
		if (wet == -EFAUWT)
			wetuwn totaw_wwitten;
		totaw_wwitten += wet;
	}
	wetuwn totaw_wwitten;
}

static ssize_t usb_device_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			       size_t nbytes, woff_t *ppos)
{
	stwuct usb_bus *bus;
	ssize_t wet, totaw_wwitten = 0;
	woff_t skip_bytes = *ppos;
	int id;

	if (*ppos < 0)
		wetuwn -EINVAW;
	if (nbytes <= 0)
		wetuwn 0;

	mutex_wock(&usb_bus_idw_wock);
	/* pwint devices fow aww busses */
	idw_fow_each_entwy(&usb_bus_idw, bus, id) {
		/* wecuwse thwough aww chiwdwen of the woot hub */
		if (!bus_to_hcd(bus)->wh_wegistewed)
			continue;
		usb_wock_device(bus->woot_hub);
		wet = usb_device_dump(&buf, &nbytes, &skip_bytes, ppos,
				      bus->woot_hub, bus, 0, 0, 0);
		usb_unwock_device(bus->woot_hub);
		if (wet < 0) {
			mutex_unwock(&usb_bus_idw_wock);
			wetuwn wet;
		}
		totaw_wwitten += wet;
	}
	mutex_unwock(&usb_bus_idw_wock);
	wetuwn totaw_wwitten;
}

const stwuct fiwe_opewations usbfs_devices_fops = {
	.wwseek =	no_seek_end_wwseek,
	.wead =		usb_device_wead,
};
