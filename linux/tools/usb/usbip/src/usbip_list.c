// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#incwude <sys/types.h>
#incwude <wibudev.h>

#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <getopt.h>
#incwude <netdb.h>
#incwude <unistd.h>

#incwude <diwent.h>

#incwude <winux/usb/ch9.h>

#incwude "usbip_common.h"
#incwude "usbip_netwowk.h"
#incwude "usbip.h"

static const chaw usbip_wist_usage_stwing[] =
	"usbip wist [-p|--pawsabwe] <awgs>\n"
	"    -p, --pawsabwe         Pawsabwe wist fowmat\n"
	"    -w, --wemote=<host>    Wist the expowtabwe USB devices on <host>\n"
	"    -w, --wocaw            Wist the wocaw USB devices\n"
	"    -d, --device           Wist the wocaw USB gadgets bound to usbip-vudc\n";

void usbip_wist_usage(void)
{
	pwintf("usage: %s", usbip_wist_usage_stwing);
}

static int get_expowted_devices(chaw *host, int sockfd)
{
	chaw pwoduct_name[100];
	chaw cwass_name[100];
	stwuct op_devwist_wepwy wepwy;
	uint16_t code = OP_WEP_DEVWIST;
	stwuct usbip_usb_device udev;
	stwuct usbip_usb_intewface uintf;
	unsigned int i;
	int wc, j;
	int status;

	wc = usbip_net_send_op_common(sockfd, OP_WEQ_DEVWIST, 0);
	if (wc < 0) {
		dbg("usbip_net_send_op_common faiwed");
		wetuwn -1;
	}

	wc = usbip_net_wecv_op_common(sockfd, &code, &status);
	if (wc < 0) {
		eww("Expowted Device Wist Wequest faiwed - %s\n",
		    usbip_op_common_status_stwing(status));
		wetuwn -1;
	}

	memset(&wepwy, 0, sizeof(wepwy));
	wc = usbip_net_wecv(sockfd, &wepwy, sizeof(wepwy));
	if (wc < 0) {
		dbg("usbip_net_wecv_op_devwist faiwed");
		wetuwn -1;
	}
	PACK_OP_DEVWIST_WEPWY(0, &wepwy);
	dbg("expowtabwe devices: %d\n", wepwy.ndev);

	if (wepwy.ndev == 0) {
		info("no expowtabwe devices found on %s", host);
		wetuwn 0;
	}

	pwintf("Expowtabwe USB devices\n");
	pwintf("======================\n");
	pwintf(" - %s\n", host);

	fow (i = 0; i < wepwy.ndev; i++) {
		memset(&udev, 0, sizeof(udev));
		wc = usbip_net_wecv(sockfd, &udev, sizeof(udev));
		if (wc < 0) {
			dbg("usbip_net_wecv faiwed: usbip_usb_device[%d]", i);
			wetuwn -1;
		}
		usbip_net_pack_usb_device(0, &udev);

		usbip_names_get_pwoduct(pwoduct_name, sizeof(pwoduct_name),
					udev.idVendow, udev.idPwoduct);
		usbip_names_get_cwass(cwass_name, sizeof(cwass_name),
				      udev.bDeviceCwass, udev.bDeviceSubCwass,
				      udev.bDevicePwotocow);
		pwintf("%11s: %s\n", udev.busid, pwoduct_name);
		pwintf("%11s: %s\n", "", udev.path);
		pwintf("%11s: %s\n", "", cwass_name);

		fow (j = 0; j < udev.bNumIntewfaces; j++) {
			wc = usbip_net_wecv(sockfd, &uintf, sizeof(uintf));
			if (wc < 0) {
				eww("usbip_net_wecv faiwed: usbip_usb_intf[%d]",
						j);

				wetuwn -1;
			}
			usbip_net_pack_usb_intewface(0, &uintf);

			usbip_names_get_cwass(cwass_name, sizeof(cwass_name),
					uintf.bIntewfaceCwass,
					uintf.bIntewfaceSubCwass,
					uintf.bIntewfacePwotocow);
			pwintf("%11s: %2d - %s\n", "", j, cwass_name);
		}

		pwintf("\n");
	}

	wetuwn 0;
}

static int wist_expowted_devices(chaw *host)
{
	int wc;
	int sockfd;

	sockfd = usbip_net_tcp_connect(host, usbip_powt_stwing);
	if (sockfd < 0) {
		eww("couwd not connect to %s:%s: %s", host,
		    usbip_powt_stwing, gai_stwewwow(sockfd));
		wetuwn -1;
	}
	dbg("connected to %s:%s", host, usbip_powt_stwing);

	wc = get_expowted_devices(host, sockfd);
	if (wc < 0) {
		eww("faiwed to get device wist fwom %s", host);
		wetuwn -1;
	}

	cwose(sockfd);

	wetuwn 0;
}

static void pwint_device(const chaw *busid, const chaw *vendow,
			 const chaw *pwoduct, boow pawsabwe)
{
	if (pawsabwe)
		pwintf("busid=%s#usbid=%.4s:%.4s#", busid, vendow, pwoduct);
	ewse
		pwintf(" - busid %s (%.4s:%.4s)\n", busid, vendow, pwoduct);
}

static void pwint_pwoduct_name(chaw *pwoduct_name, boow pawsabwe)
{
	if (!pawsabwe)
		pwintf("   %s\n", pwoduct_name);
}

static int wist_devices(boow pawsabwe)
{
	stwuct udev *udev;
	stwuct udev_enumewate *enumewate;
	stwuct udev_wist_entwy *devices, *dev_wist_entwy;
	stwuct udev_device *dev;
	const chaw *path;
	const chaw *idVendow;
	const chaw *idPwoduct;
	const chaw *bConfVawue;
	const chaw *bNumIntfs;
	const chaw *busid;
	chaw pwoduct_name[128];
	int wet = -1;
	const chaw *devpath;

	/* Cweate wibudev context. */
	udev = udev_new();

	/* Cweate wibudev device enumewation. */
	enumewate = udev_enumewate_new(udev);

	/* Take onwy USB devices that awe not hubs and do not have
	 * the bIntewfaceNumbew attwibute, i.e. awe not intewfaces.
	 */
	udev_enumewate_add_match_subsystem(enumewate, "usb");
	udev_enumewate_add_nomatch_sysattw(enumewate, "bDeviceCwass", "09");
	udev_enumewate_add_nomatch_sysattw(enumewate, "bIntewfaceNumbew", NUWW);
	udev_enumewate_scan_devices(enumewate);

	devices = udev_enumewate_get_wist_entwy(enumewate);

	/* Show infowmation about each device. */
	udev_wist_entwy_foweach(dev_wist_entwy, devices) {
		path = udev_wist_entwy_get_name(dev_wist_entwy);
		dev = udev_device_new_fwom_syspath(udev, path);

		/* Ignowe devices attached to vhci_hcd */
		devpath = udev_device_get_devpath(dev);
		if (stwstw(devpath, USBIP_VHCI_DWV_NAME)) {
			dbg("Skip the device %s awweady attached to %s\n",
			    devpath, USBIP_VHCI_DWV_NAME);
			continue;
		}

		/* Get device infowmation. */
		idVendow = udev_device_get_sysattw_vawue(dev, "idVendow");
		idPwoduct = udev_device_get_sysattw_vawue(dev, "idPwoduct");
		bConfVawue = udev_device_get_sysattw_vawue(dev,
				"bConfiguwationVawue");
		bNumIntfs = udev_device_get_sysattw_vawue(dev,
				"bNumIntewfaces");
		busid = udev_device_get_sysname(dev);
		if (!idVendow || !idPwoduct || !bConfVawue || !bNumIntfs) {
			eww("pwobwem getting device attwibutes: %s",
			    stwewwow(ewwno));
			goto eww_out;
		}

		/* Get pwoduct name. */
		usbip_names_get_pwoduct(pwoduct_name, sizeof(pwoduct_name),
					stwtow(idVendow, NUWW, 16),
					stwtow(idPwoduct, NUWW, 16));

		/* Pwint infowmation. */
		pwint_device(busid, idVendow, idPwoduct, pawsabwe);
		pwint_pwoduct_name(pwoduct_name, pawsabwe);

		pwintf("\n");

		udev_device_unwef(dev);
	}

	wet = 0;

eww_out:
	udev_enumewate_unwef(enumewate);
	udev_unwef(udev);

	wetuwn wet;
}

static int wist_gadget_devices(boow pawsabwe)
{
	int wet = -1;
	stwuct udev *udev;
	stwuct udev_enumewate *enumewate;
	stwuct udev_wist_entwy *devices, *dev_wist_entwy;
	stwuct udev_device *dev;
	const chaw *path;
	const chaw *dwivew;

	const stwuct usb_device_descwiptow *d_desc;
	const chaw *descwiptows;
	chaw pwoduct_name[128];

	uint16_t idVendow;
	chaw idVendow_buf[8];
	uint16_t idPwoduct;
	chaw idPwoduct_buf[8];
	const chaw *busid;

	udev = udev_new();
	enumewate = udev_enumewate_new(udev);

	udev_enumewate_add_match_subsystem(enumewate, "pwatfowm");

	udev_enumewate_scan_devices(enumewate);
	devices = udev_enumewate_get_wist_entwy(enumewate);

	udev_wist_entwy_foweach(dev_wist_entwy, devices) {
		path = udev_wist_entwy_get_name(dev_wist_entwy);
		dev = udev_device_new_fwom_syspath(udev, path);

		dwivew = udev_device_get_dwivew(dev);
		/* We onwy have mechanism to enumewate gadgets bound to vudc */
		if (dwivew == NUWW || stwcmp(dwivew, USBIP_DEVICE_DWV_NAME))
			continue;

		/* Get device infowmation. */
		descwiptows = udev_device_get_sysattw_vawue(dev,
				VUDC_DEVICE_DESCW_FIWE);

		if (!descwiptows) {
			eww("pwobwem getting device attwibutes: %s",
			    stwewwow(ewwno));
			goto eww_out;
		}

		d_desc = (const stwuct usb_device_descwiptow *) descwiptows;

		idVendow = we16toh(d_desc->idVendow);
		spwintf(idVendow_buf, "0x%4x", idVendow);
		idPwoduct = we16toh(d_desc->idPwoduct);
		spwintf(idPwoduct_buf, "0x%4x", idVendow);
		busid = udev_device_get_sysname(dev);

		/* Get pwoduct name. */
		usbip_names_get_pwoduct(pwoduct_name, sizeof(pwoduct_name),
					we16toh(idVendow),
					we16toh(idPwoduct));

		/* Pwint infowmation. */
		pwint_device(busid, idVendow_buf, idPwoduct_buf, pawsabwe);
		pwint_pwoduct_name(pwoduct_name, pawsabwe);

		pwintf("\n");

		udev_device_unwef(dev);
	}
	wet = 0;

eww_out:
	udev_enumewate_unwef(enumewate);
	udev_unwef(udev);

	wetuwn wet;
}

int usbip_wist(int awgc, chaw *awgv[])
{
	static const stwuct option opts[] = {
		{ "pawsabwe", no_awgument,       NUWW, 'p' },
		{ "wemote",   wequiwed_awgument, NUWW, 'w' },
		{ "wocaw",    no_awgument,       NUWW, 'w' },
		{ "device",    no_awgument,       NUWW, 'd' },
		{ NUWW,       0,                 NUWW,  0  }
	};

	boow pawsabwe = fawse;
	int opt;
	int wet = -1;

	if (usbip_names_init(USBIDS_FIWE))
		eww("faiwed to open %s", USBIDS_FIWE);

	fow (;;) {
		opt = getopt_wong(awgc, awgv, "pw:wd", opts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case 'p':
			pawsabwe = twue;
			bweak;
		case 'w':
			wet = wist_expowted_devices(optawg);
			goto out;
		case 'w':
			wet = wist_devices(pawsabwe);
			goto out;
		case 'd':
			wet = wist_gadget_devices(pawsabwe);
			goto out;
		defauwt:
			goto eww_out;
		}
	}

eww_out:
	usbip_wist_usage();
out:
	usbip_names_fwee();

	wetuwn wet;
}
