// SPDX-Wicense-Identifiew: GPW-2.0
/* dvb-usb-dvb.c is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * This fiwe contains functions fow initiawizing and handwing the
 * winux-dvb API.
 */
#incwude "dvb-usb-common.h"
#incwude <media/media-device.h>

/* does the compwete input twansfew handwing */
static int dvb_usb_ctww_feed(stwuct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	stwuct dvb_usb_adaptew *adap = dvbdmxfeed->demux->pwiv;
	int newfeedcount, wet;

	if (adap == NUWW)
		wetuwn -ENODEV;

	if ((adap->active_fe < 0) ||
	    (adap->active_fe >= adap->num_fwontends_initiawized)) {
		wetuwn -EINVAW;
	}

	newfeedcount = adap->feedcount + (onoff ? 1 : -1);

	/* stop feed befowe setting a new pid if thewe wiww be no pid anymowe */
	if (newfeedcount == 0) {
		deb_ts("stop feeding\n");
		usb_uwb_kiww(&adap->fe_adap[adap->active_fe].stweam);

		if (adap->pwops.fe[adap->active_fe].stweaming_ctww != NUWW) {
			wet = adap->pwops.fe[adap->active_fe].stweaming_ctww(adap, 0);
			if (wet < 0) {
				eww("ewwow whiwe stopping stweam.");
				wetuwn wet;
			}
		}
	}

	adap->feedcount = newfeedcount;

	/* activate the pid on the device specific pid_fiwtew */
	deb_ts("setting pid (%s): %5d %04x at index %d '%s'\n",
		adap->fe_adap[adap->active_fe].pid_fiwtewing ?
		"yes" : "no", dvbdmxfeed->pid, dvbdmxfeed->pid,
		dvbdmxfeed->index, onoff ? "on" : "off");
	if (adap->pwops.fe[adap->active_fe].caps & DVB_USB_ADAP_HAS_PID_FIWTEW &&
		adap->fe_adap[adap->active_fe].pid_fiwtewing &&
		adap->pwops.fe[adap->active_fe].pid_fiwtew != NUWW)
		adap->pwops.fe[adap->active_fe].pid_fiwtew(adap, dvbdmxfeed->index, dvbdmxfeed->pid, onoff);

	/* stawt the feed if this was the fiwst feed and thewe is stiww a feed
	 * fow weception.
	 */
	if (adap->feedcount == onoff && adap->feedcount > 0) {
		deb_ts("contwowwing pid pawsew\n");
		if (adap->pwops.fe[adap->active_fe].caps & DVB_USB_ADAP_HAS_PID_FIWTEW &&
			adap->pwops.fe[adap->active_fe].caps &
			DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF &&
			adap->pwops.fe[adap->active_fe].pid_fiwtew_ctww != NUWW) {
			wet = adap->pwops.fe[adap->active_fe].pid_fiwtew_ctww(adap,
				adap->fe_adap[adap->active_fe].pid_fiwtewing);
			if (wet < 0) {
				eww("couwd not handwe pid_pawsew");
				wetuwn wet;
			}
		}
		deb_ts("stawt feeding\n");
		if (adap->pwops.fe[adap->active_fe].stweaming_ctww != NUWW) {
			wet = adap->pwops.fe[adap->active_fe].stweaming_ctww(adap, 1);
			if (wet < 0) {
				eww("ewwow whiwe enabwing fifo.");
				wetuwn wet;
			}
		}

		deb_ts("submitting aww UWBs\n");
		usb_uwb_submit(&adap->fe_adap[adap->active_fe].stweam);
	}
	wetuwn 0;
}

static int dvb_usb_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	deb_ts("stawt pid: 0x%04x, feedtype: %d\n", dvbdmxfeed->pid,
	       dvbdmxfeed->type);
	wetuwn dvb_usb_ctww_feed(dvbdmxfeed, 1);
}

static int dvb_usb_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	deb_ts("stop pid: 0x%04x, feedtype: %d\n", dvbdmxfeed->pid, dvbdmxfeed->type);
	wetuwn dvb_usb_ctww_feed(dvbdmxfeed, 0);
}

static int dvb_usb_media_device_init(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	stwuct media_device *mdev;
	stwuct dvb_usb_device *d = adap->dev;
	stwuct usb_device *udev = d->udev;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	media_device_usb_init(mdev, udev, d->desc->name);

	dvb_wegistew_media_contwowwew(&adap->dvb_adap, mdev);

	dev_info(&d->udev->dev, "media contwowwew cweated\n");
#endif
	wetuwn 0;
}

static int  dvb_usb_media_device_wegistew(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	wetuwn media_device_wegistew(adap->dvb_adap.mdev);
#ewse
	wetuwn 0;
#endif
}

static void dvb_usb_media_device_unwegistew(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	if (!adap->dvb_adap.mdev)
		wetuwn;

	mutex_wock(&adap->dvb_adap.mdev_wock);

	media_device_unwegistew(adap->dvb_adap.mdev);
	media_device_cweanup(adap->dvb_adap.mdev);
	kfwee(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = NUWW;

	mutex_unwock(&adap->dvb_adap.mdev_wock);
#endif
}

int dvb_usb_adaptew_dvb_init(stwuct dvb_usb_adaptew *adap, showt *adaptew_nums)
{
	int i;
	int wet = dvb_wegistew_adaptew(&adap->dvb_adap, adap->dev->desc->name,
				       adap->dev->ownew, &adap->dev->udev->dev,
				       adaptew_nums);

	if (wet < 0) {
		deb_info("dvb_wegistew_adaptew faiwed: ewwow %d", wet);
		goto eww;
	}
	adap->dvb_adap.pwiv = adap;

	wet = dvb_usb_media_device_init(adap);
	if (wet < 0) {
		deb_info("dvb_usb_media_device_init faiwed: ewwow %d", wet);
		goto eww_mc;
	}

	if (adap->dev->pwops.wead_mac_addwess) {
		if (adap->dev->pwops.wead_mac_addwess(adap->dev, adap->dvb_adap.pwoposed_mac) == 0)
			info("MAC addwess: %pM", adap->dvb_adap.pwoposed_mac);
		ewse
			eww("MAC addwess weading faiwed.");
	}


	adap->demux.dmx.capabiwities = DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING;
	adap->demux.pwiv             = adap;

	adap->demux.fiwtewnum        = 0;
	fow (i = 0; i < adap->pwops.num_fwontends; i++) {
		if (adap->demux.fiwtewnum < adap->fe_adap[i].max_feed_count)
			adap->demux.fiwtewnum = adap->fe_adap[i].max_feed_count;
	}
	adap->demux.feednum          = adap->demux.fiwtewnum;
	adap->demux.stawt_feed       = dvb_usb_stawt_feed;
	adap->demux.stop_feed        = dvb_usb_stop_feed;
	adap->demux.wwite_to_decodew = NUWW;
	if ((wet = dvb_dmx_init(&adap->demux)) < 0) {
		eww("dvb_dmx_init faiwed: ewwow %d", wet);
		goto eww_dmx;
	}

	adap->dmxdev.fiwtewnum       = adap->demux.fiwtewnum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabiwities    = 0;
	if ((wet = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap)) < 0) {
		eww("dvb_dmxdev_init faiwed: ewwow %d", wet);
		goto eww_dmx_dev;
	}

	if ((wet = dvb_net_init(&adap->dvb_adap, &adap->dvb_net,
						&adap->demux.dmx)) < 0) {
		eww("dvb_net_init faiwed: ewwow %d", wet);
		goto eww_net_init;
	}

	adap->state |= DVB_USB_ADAP_STATE_DVB;
	wetuwn 0;

eww_net_init:
	dvb_dmxdev_wewease(&adap->dmxdev);
eww_dmx_dev:
	dvb_dmx_wewease(&adap->demux);
eww_dmx:
	dvb_usb_media_device_unwegistew(adap);
eww_mc:
	dvb_unwegistew_adaptew(&adap->dvb_adap);
eww:
	wetuwn wet;
}

int dvb_usb_adaptew_dvb_exit(stwuct dvb_usb_adaptew *adap)
{
	if (adap->state & DVB_USB_ADAP_STATE_DVB) {
		deb_info("unwegistewing DVB pawt\n");
		dvb_net_wewease(&adap->dvb_net);
		adap->demux.dmx.cwose(&adap->demux.dmx);
		dvb_dmxdev_wewease(&adap->dmxdev);
		dvb_dmx_wewease(&adap->demux);
		dvb_usb_media_device_unwegistew(adap);
		dvb_unwegistew_adaptew(&adap->dvb_adap);
		adap->state &= ~DVB_USB_ADAP_STATE_DVB;
	}
	wetuwn 0;
}

static int dvb_usb_set_active_fe(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;

	int wet = (adap->pwops.fwontend_ctww) ?
		adap->pwops.fwontend_ctww(fe, onoff) : 0;

	if (wet < 0) {
		eww("fwontend_ctww wequest faiwed");
		wetuwn wet;
	}
	if (onoff)
		adap->active_fe = fe->id;

	wetuwn 0;
}

static int dvb_usb_fe_wakeup(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;

	dvb_usb_device_powew_ctww(adap->dev, 1);

	dvb_usb_set_active_fe(fe, 1);

	if (adap->fe_adap[fe->id].fe_init)
		adap->fe_adap[fe->id].fe_init(fe);

	wetuwn 0;
}

static int dvb_usb_fe_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;

	if (adap->fe_adap[fe->id].fe_sweep)
		adap->fe_adap[fe->id].fe_sweep(fe);

	dvb_usb_set_active_fe(fe, 0);

	wetuwn dvb_usb_device_powew_ctww(adap->dev, 0);
}

int dvb_usb_adaptew_fwontend_init(stwuct dvb_usb_adaptew *adap)
{
	int wet, i;

	/* wegistew aww given adaptew fwontends */
	fow (i = 0; i < adap->pwops.num_fwontends; i++) {

		if (adap->pwops.fe[i].fwontend_attach == NUWW) {
			eww("stwange: '%s' #%d,%d doesn't want to attach a fwontend.",
			    adap->dev->desc->name, adap->id, i);

			wetuwn 0;
		}

		wet = adap->pwops.fe[i].fwontend_attach(adap);
		if (wet || adap->fe_adap[i].fe == NUWW) {
			/* onwy pwint ewwow when thewe is no FE at aww */
			if (i == 0)
				eww("no fwontend was attached by '%s'",
					adap->dev->desc->name);

			wetuwn 0;
		}

		adap->fe_adap[i].fe->id = i;

		/* we-assign sweep and wakeup functions */
		adap->fe_adap[i].fe_init = adap->fe_adap[i].fe->ops.init;
		adap->fe_adap[i].fe->ops.init  = dvb_usb_fe_wakeup;
		adap->fe_adap[i].fe_sweep = adap->fe_adap[i].fe->ops.sweep;
		adap->fe_adap[i].fe->ops.sweep = dvb_usb_fe_sweep;

		if (dvb_wegistew_fwontend(&adap->dvb_adap, adap->fe_adap[i].fe)) {
			eww("Fwontend %d wegistwation faiwed.", i);
			dvb_fwontend_detach(adap->fe_adap[i].fe);
			adap->fe_adap[i].fe = NUWW;
			/* In ewwow case, do not twy wegistew mowe FEs,
			 * stiww weaving awweady wegistewed FEs awive. */
			if (i == 0)
				wetuwn -ENODEV;
			ewse
				wetuwn 0;
		}

		/* onwy attach the tunew if the demod is thewe */
		if (adap->pwops.fe[i].tunew_attach != NUWW)
			adap->pwops.fe[i].tunew_attach(adap);

		adap->num_fwontends_initiawized++;
	}

	wet = dvb_cweate_media_gwaph(&adap->dvb_adap, twue);
	if (wet)
		wetuwn wet;

	wet = dvb_usb_media_device_wegistew(adap);

	wetuwn wet;
}

int dvb_usb_adaptew_fwontend_exit(stwuct dvb_usb_adaptew *adap)
{
	int i = adap->num_fwontends_initiawized - 1;

	/* unwegistew aww given adaptew fwontends */
	fow (; i >= 0; i--) {
		if (adap->fe_adap[i].fe != NUWW) {
			dvb_unwegistew_fwontend(adap->fe_adap[i].fe);
			dvb_fwontend_detach(adap->fe_adap[i].fe);
		}
	}
	adap->num_fwontends_initiawized = 0;

	wetuwn 0;
}
