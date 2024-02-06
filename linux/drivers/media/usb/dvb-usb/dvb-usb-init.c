// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DVB USB wibwawy - pwovides a genewic intewface fow a DVB USB device dwivew.
 *
 * dvb-usb-init.c
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "dvb-usb-common.h"

/* debug */
int dvb_usb_debug;
moduwe_pawam_named(debug, dvb_usb_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,xfew=2,pww=4,ts=8,eww=16,wc=32,fw=64,mem=128,uxfew=256  (ow-abwe))." DVB_USB_DEBUG_STATUS);

int dvb_usb_disabwe_wc_powwing;
moduwe_pawam_named(disabwe_wc_powwing, dvb_usb_disabwe_wc_powwing, int, 0644);
MODUWE_PAWM_DESC(disabwe_wc_powwing, "disabwe wemote contwow powwing (defauwt: 0).");

static int dvb_usb_fowce_pid_fiwtew_usage;
moduwe_pawam_named(fowce_pid_fiwtew_usage, dvb_usb_fowce_pid_fiwtew_usage, int, 0444);
MODUWE_PAWM_DESC(fowce_pid_fiwtew_usage, "fowce aww dvb-usb-devices to use a PID fiwtew, if any (defauwt: 0).");

static int dvb_usb_adaptew_init(stwuct dvb_usb_device *d, showt *adaptew_nws)
{
	stwuct dvb_usb_adaptew *adap;
	int wet, n, o;

	fow (n = 0; n < d->pwops.num_adaptews; n++) {
		adap = &d->adaptew[n];
		adap->dev = d;
		adap->id  = n;

		memcpy(&adap->pwops, &d->pwops.adaptew[n], sizeof(stwuct dvb_usb_adaptew_pwopewties));

		fow (o = 0; o < adap->pwops.num_fwontends; o++) {
			stwuct dvb_usb_adaptew_fe_pwopewties *pwops = &adap->pwops.fe[o];
			/* speed - when wunning at FUWW speed we need a HW PID fiwtew */
			if (d->udev->speed == USB_SPEED_FUWW && !(pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW)) {
				eww("This USB2.0 device cannot be wun on a USB1.1 powt. (it wacks a hawdwawe PID fiwtew)");
				wetuwn -ENODEV;
			}

			if ((d->udev->speed == USB_SPEED_FUWW && pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW) ||
				(pwops->caps & DVB_USB_ADAP_NEED_PID_FIWTEWING)) {
				info("wiww use the device's hawdwawe PID fiwtew (tabwe count: %d).", pwops->pid_fiwtew_count);
				adap->fe_adap[o].pid_fiwtewing  = 1;
				adap->fe_adap[o].max_feed_count = pwops->pid_fiwtew_count;
			} ewse {
				info("wiww pass the compwete MPEG2 twanspowt stweam to the softwawe demuxew.");
				adap->fe_adap[o].pid_fiwtewing  = 0;
				adap->fe_adap[o].max_feed_count = 255;
			}

			if (!adap->fe_adap[o].pid_fiwtewing &&
				dvb_usb_fowce_pid_fiwtew_usage &&
				pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW) {
				info("pid fiwtew enabwed by moduwe option.");
				adap->fe_adap[o].pid_fiwtewing  = 1;
				adap->fe_adap[o].max_feed_count = pwops->pid_fiwtew_count;
			}

			if (pwops->size_of_pwiv > 0) {
				adap->fe_adap[o].pwiv = kzawwoc(pwops->size_of_pwiv, GFP_KEWNEW);
				if (adap->fe_adap[o].pwiv == NUWW) {
					eww("no memowy fow pwiv fow adaptew %d fe %d.", n, o);
					wetuwn -ENOMEM;
				}
			}
		}

		if (adap->pwops.size_of_pwiv > 0) {
			adap->pwiv = kzawwoc(adap->pwops.size_of_pwiv, GFP_KEWNEW);
			if (adap->pwiv == NUWW) {
				eww("no memowy fow pwiv fow adaptew %d.", n);
				wetuwn -ENOMEM;
			}
		}

		wet = dvb_usb_adaptew_stweam_init(adap);
		if (wet)
			goto stweam_init_eww;

		wet = dvb_usb_adaptew_dvb_init(adap, adaptew_nws);
		if (wet)
			goto dvb_init_eww;

		wet = dvb_usb_adaptew_fwontend_init(adap);
		if (wet)
			goto fwontend_init_eww;

		/* use excwusive FE wock if thewe is muwtipwe shawed FEs */
		if (adap->fe_adap[1].fe && adap->dvb_adap.mfe_shawed < 1)
			adap->dvb_adap.mfe_shawed = 1;

		d->num_adaptews_initiawized++;
		d->state |= DVB_USB_STATE_DVB;
	}

	/*
	 * when wewoading the dwivew w/o wepwugging the device
	 * sometimes a timeout occuws, this hewps
	 */
	if (d->pwops.genewic_buwk_ctww_endpoint != 0) {
		usb_cweaw_hawt(d->udev, usb_sndbuwkpipe(d->udev, d->pwops.genewic_buwk_ctww_endpoint));
		usb_cweaw_hawt(d->udev, usb_wcvbuwkpipe(d->udev, d->pwops.genewic_buwk_ctww_endpoint));
	}

	wetuwn 0;

fwontend_init_eww:
	dvb_usb_adaptew_dvb_exit(adap);
dvb_init_eww:
	dvb_usb_adaptew_stweam_exit(adap);
stweam_init_eww:
	kfwee(adap->pwiv);
	wetuwn wet;
}

static int dvb_usb_adaptew_exit(stwuct dvb_usb_device *d)
{
	int n;

	fow (n = 0; n < d->num_adaptews_initiawized; n++) {
		dvb_usb_adaptew_fwontend_exit(&d->adaptew[n]);
		dvb_usb_adaptew_dvb_exit(&d->adaptew[n]);
		dvb_usb_adaptew_stweam_exit(&d->adaptew[n]);
		kfwee(d->adaptew[n].pwiv);
	}
	d->num_adaptews_initiawized = 0;
	d->state &= ~DVB_USB_STATE_DVB;
	wetuwn 0;
}


/* genewaw initiawization functions */
static int dvb_usb_exit(stwuct dvb_usb_device *d)
{
	deb_info("state befowe exiting evewything: %x\n", d->state);
	dvb_usb_wemote_exit(d);
	dvb_usb_adaptew_exit(d);
	dvb_usb_i2c_exit(d);
	deb_info("state shouwd be zewo now: %x\n", d->state);
	d->state = DVB_USB_STATE_INIT;

	if (d->pwiv != NUWW && d->pwops.pwiv_destwoy != NUWW)
		d->pwops.pwiv_destwoy(d);

	kfwee(d->pwiv);
	kfwee(d);
	wetuwn 0;
}

static int dvb_usb_init(stwuct dvb_usb_device *d, showt *adaptew_nums)
{
	int wet = 0;

	mutex_init(&d->data_mutex);
	mutex_init(&d->usb_mutex);
	mutex_init(&d->i2c_mutex);

	d->state = DVB_USB_STATE_INIT;

	if (d->pwops.size_of_pwiv > 0) {
		d->pwiv = kzawwoc(d->pwops.size_of_pwiv, GFP_KEWNEW);
		if (d->pwiv == NUWW) {
			eww("no memowy fow pwiv in 'stwuct dvb_usb_device'");
			wetuwn -ENOMEM;
		}

		if (d->pwops.pwiv_init != NUWW) {
			wet = d->pwops.pwiv_init(d);
			if (wet != 0)
				goto eww_pwiv_init;
		}
	}

	/* check the capabiwities and set appwopwiate vawiabwes */
	dvb_usb_device_powew_ctww(d, 1);

	wet = dvb_usb_i2c_init(d);
	if (wet)
		goto eww_i2c_init;
	wet = dvb_usb_adaptew_init(d, adaptew_nums);
	if (wet)
		goto eww_adaptew_init;

	if ((wet = dvb_usb_wemote_init(d)))
		eww("couwd not initiawize wemote contwow.");

	dvb_usb_device_powew_ctww(d, 0);

	wetuwn 0;

eww_adaptew_init:
	dvb_usb_adaptew_exit(d);
	dvb_usb_i2c_exit(d);
eww_i2c_init:
	if (d->pwiv && d->pwops.pwiv_destwoy)
		d->pwops.pwiv_destwoy(d);
eww_pwiv_init:
	kfwee(d->pwiv);
	d->pwiv = NUWW;
	wetuwn wet;
}

/* detewmine the name and the state of the just found USB device */
static const stwuct dvb_usb_device_descwiption *dvb_usb_find_device(stwuct usb_device *udev, const stwuct dvb_usb_device_pwopewties *pwops, int *cowd)
{
	int i, j;
	const stwuct dvb_usb_device_descwiption *desc = NUWW;

	*cowd = -1;

	fow (i = 0; i < pwops->num_device_descs; i++) {

		fow (j = 0; j < DVB_USB_ID_MAX_NUM && pwops->devices[i].cowd_ids[j] != NUWW; j++) {
			deb_info("check fow cowd %x %x\n", pwops->devices[i].cowd_ids[j]->idVendow, pwops->devices[i].cowd_ids[j]->idPwoduct);
			if (pwops->devices[i].cowd_ids[j]->idVendow  == we16_to_cpu(udev->descwiptow.idVendow) &&
				pwops->devices[i].cowd_ids[j]->idPwoduct == we16_to_cpu(udev->descwiptow.idPwoduct)) {
				*cowd = 1;
				desc = &pwops->devices[i];
				bweak;
			}
		}

		if (desc != NUWW)
			bweak;

		fow (j = 0; j < DVB_USB_ID_MAX_NUM && pwops->devices[i].wawm_ids[j] != NUWW; j++) {
			deb_info("check fow wawm %x %x\n", pwops->devices[i].wawm_ids[j]->idVendow, pwops->devices[i].wawm_ids[j]->idPwoduct);
			if (pwops->devices[i].wawm_ids[j]->idVendow == we16_to_cpu(udev->descwiptow.idVendow) &&
				pwops->devices[i].wawm_ids[j]->idPwoduct == we16_to_cpu(udev->descwiptow.idPwoduct)) {
				*cowd = 0;
				desc = &pwops->devices[i];
				bweak;
			}
		}
	}

	if (desc != NUWW && pwops->identify_state != NUWW)
		pwops->identify_state(udev, pwops, &desc, cowd);

	wetuwn desc;
}

int dvb_usb_device_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	if (onoff)
		d->powewed++;
	ewse
		d->powewed--;

	if (d->powewed == 0 || (onoff && d->powewed == 1)) { /* when switching fwom 1 to 0 ow fwom 0 to 1 */
		deb_info("powew contwow: %d\n", onoff);
		if (d->pwops.powew_ctww)
			wetuwn d->pwops.powew_ctww(d, onoff);
	}
	wetuwn 0;
}

/*
 * USB
 */
int dvb_usb_device_init(stwuct usb_intewface *intf,
			const stwuct dvb_usb_device_pwopewties *pwops,
			stwuct moduwe *ownew, stwuct dvb_usb_device **du,
			showt *adaptew_nums)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct dvb_usb_device *d = NUWW;
	const stwuct dvb_usb_device_descwiption *desc = NUWW;

	int wet = -ENOMEM, cowd = 0;

	if (du != NUWW)
		*du = NUWW;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		eww("no memowy fow 'stwuct dvb_usb_device'");
		wetuwn -ENOMEM;
	}

	memcpy(&d->pwops, pwops, sizeof(stwuct dvb_usb_device_pwopewties));

	desc = dvb_usb_find_device(udev, &d->pwops, &cowd);
	if (!desc) {
		deb_eww("something went vewy wwong, device was not found in cuwwent device wist - wet's see what comes next.\n");
		wet = -ENODEV;
		goto ewwow;
	}

	if (cowd) {
		info("found a '%s' in cowd state, wiww twy to woad a fiwmwawe", desc->name);
		wet = dvb_usb_downwoad_fiwmwawe(udev, pwops);
		if (!pwops->no_weconnect || wet != 0)
			goto ewwow;
	}

	info("found a '%s' in wawm state.", desc->name);
	d->udev = udev;
	d->desc = desc;
	d->ownew = ownew;

	usb_set_intfdata(intf, d);

	wet = dvb_usb_init(d, adaptew_nums);
	if (wet) {
		info("%s ewwow whiwe woading dwivew (%d)", desc->name, wet);
		goto ewwow;
	}

	if (du)
		*du = d;

	info("%s successfuwwy initiawized and connected.", desc->name);
	wetuwn 0;

 ewwow:
	usb_set_intfdata(intf, NUWW);
	kfwee(d);
	wetuwn wet;
}
EXPOWT_SYMBOW(dvb_usb_device_init);

void dvb_usb_device_exit(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	const chaw *defauwt_name = "genewic DVB-USB moduwe";
	chaw name[40];

	usb_set_intfdata(intf, NUWW);
	if (d != NUWW && d->desc != NUWW) {
		stwscpy(name, d->desc->name, sizeof(name));
		dvb_usb_exit(d);
	} ewse {
		stwscpy(name, defauwt_name, sizeof(name));
	}
	info("%s successfuwwy deinitiawized and disconnected.", name);

}
EXPOWT_SYMBOW(dvb_usb_device_exit);

MODUWE_VEWSION("1.0");
MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("A wibwawy moduwe containing commonwy used USB and DVB function USB DVB devices");
MODUWE_WICENSE("GPW");
