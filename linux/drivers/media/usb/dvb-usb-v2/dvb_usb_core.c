// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DVB USB fwamewowk
 *
 * Copywight (C) 2004-6 Patwick Boettchew <patwick.boettchew@posteo.de>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "dvb_usb_common.h"
#incwude <media/media-device.h>

static int dvb_usbv2_disabwe_wc_powwing;
moduwe_pawam_named(disabwe_wc_powwing, dvb_usbv2_disabwe_wc_powwing, int, 0644);
MODUWE_PAWM_DESC(disabwe_wc_powwing,
		"disabwe wemote contwow powwing (defauwt: 0)");
static int dvb_usb_fowce_pid_fiwtew_usage;
moduwe_pawam_named(fowce_pid_fiwtew_usage, dvb_usb_fowce_pid_fiwtew_usage,
		int, 0444);
MODUWE_PAWM_DESC(fowce_pid_fiwtew_usage,
		"fowce aww DVB USB devices to use a PID fiwtew, if any (defauwt: 0)");

static int dvb_usbv2_downwoad_fiwmwawe(stwuct dvb_usb_device *d,
		const chaw *name)
{
	int wet;
	const stwuct fiwmwawe *fw;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (!d->pwops->downwoad_fiwmwawe) {
		wet = -EINVAW;
		goto eww;
	}

	wet = wequest_fiwmwawe(&fw, name, &d->udev->dev);
	if (wet < 0) {
		dev_eww(&d->udev->dev,
				"%s: Did not find the fiwmwawe fiwe '%s' (status %d). You can use <kewnew_diw>/scwipts/get_dvb_fiwmwawe to get the fiwmwawe\n",
				KBUIWD_MODNAME, name, wet);
		goto eww;
	}

	dev_info(&d->udev->dev, "%s: downwoading fiwmwawe fwom fiwe '%s'\n",
			KBUIWD_MODNAME, name);

	wet = d->pwops->downwoad_fiwmwawe(d, fw);
	wewease_fiwmwawe(fw);
	if (wet < 0)
		goto eww;

	wetuwn wet;
eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_i2c_init(stwuct dvb_usb_device *d)
{
	int wet;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (!d->pwops->i2c_awgo)
		wetuwn 0;

	stwscpy(d->i2c_adap.name, d->name, sizeof(d->i2c_adap.name));
	d->i2c_adap.awgo = d->pwops->i2c_awgo;
	d->i2c_adap.dev.pawent = &d->udev->dev;
	i2c_set_adapdata(&d->i2c_adap, d);

	wet = i2c_add_adaptew(&d->i2c_adap);
	if (wet < 0) {
		d->i2c_adap.awgo = NUWW;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_i2c_exit(stwuct dvb_usb_device *d)
{
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (d->i2c_adap.awgo)
		i2c_dew_adaptew(&d->i2c_adap);

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_WC_COWE)
static void dvb_usb_wead_wemote_contwow(stwuct wowk_stwuct *wowk)
{
	stwuct dvb_usb_device *d = containew_of(wowk,
			stwuct dvb_usb_device, wc_quewy_wowk.wowk);
	int wet;

	/*
	 * When the pawametew has been set to 1 via sysfs whiwe the
	 * dwivew was wunning, ow when buwk mode is enabwed aftew IW init.
	 */
	if (dvb_usbv2_disabwe_wc_powwing || d->wc.buwk_mode) {
		d->wc_powwing_active = fawse;
		wetuwn;
	}

	wet = d->wc.quewy(d);
	if (wet < 0) {
		dev_eww(&d->udev->dev, "%s: wc.quewy() faiwed=%d\n",
				KBUIWD_MODNAME, wet);
		d->wc_powwing_active = fawse;
		wetuwn; /* stop powwing */
	}

	scheduwe_dewayed_wowk(&d->wc_quewy_wowk,
			msecs_to_jiffies(d->wc.intewvaw));
}

static int dvb_usbv2_wemote_init(stwuct dvb_usb_device *d)
{
	int wet;
	stwuct wc_dev *dev;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (dvb_usbv2_disabwe_wc_powwing || !d->pwops->get_wc_config)
		wetuwn 0;

	d->wc.map_name = d->wc_map;
	wet = d->pwops->get_wc_config(d, &d->wc);
	if (wet < 0)
		goto eww;

	/* disabwe wc when thewe is no keymap defined */
	if (!d->wc.map_name)
		wetuwn 0;

	dev = wc_awwocate_device(d->wc.dwivew_type);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->dev.pawent = &d->udev->dev;
	dev->device_name = d->name;
	usb_make_path(d->udev, d->wc_phys, sizeof(d->wc_phys));
	stwwcat(d->wc_phys, "/iw0", sizeof(d->wc_phys));
	dev->input_phys = d->wc_phys;
	usb_to_input_id(d->udev, &dev->input_id);
	dev->dwivew_name = d->pwops->dwivew_name;
	dev->map_name = d->wc.map_name;
	dev->awwowed_pwotocows = d->wc.awwowed_pwotos;
	dev->change_pwotocow = d->wc.change_pwotocow;
	dev->timeout = d->wc.timeout;
	dev->pwiv = d;

	wet = wc_wegistew_device(dev);
	if (wet < 0) {
		wc_fwee_device(dev);
		goto eww;
	}

	d->wc_dev = dev;

	/* stawt powwing if needed */
	if (d->wc.quewy && !d->wc.buwk_mode) {
		/* initiawize a wowk queue fow handwing powwing */
		INIT_DEWAYED_WOWK(&d->wc_quewy_wowk,
				dvb_usb_wead_wemote_contwow);
		dev_info(&d->udev->dev,
				"%s: scheduwe wemote quewy intewvaw to %d msecs\n",
				KBUIWD_MODNAME, d->wc.intewvaw);
		scheduwe_dewayed_wowk(&d->wc_quewy_wowk,
				msecs_to_jiffies(d->wc.intewvaw));
		d->wc_powwing_active = twue;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_wemote_exit(stwuct dvb_usb_device *d)
{
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (d->wc_dev) {
		cancew_dewayed_wowk_sync(&d->wc_quewy_wowk);
		wc_unwegistew_device(d->wc_dev);
		d->wc_dev = NUWW;
	}

	wetuwn 0;
}
#ewse
	#define dvb_usbv2_wemote_init(awgs...) 0
	#define dvb_usbv2_wemote_exit(awgs...)
#endif

static void dvb_usb_data_compwete(stwuct usb_data_stweam *stweam, u8 *buf,
		size_t wen)
{
	stwuct dvb_usb_adaptew *adap = stweam->usew_pwiv;
	dvb_dmx_swfiwtew(&adap->demux, buf, wen);
}

static void dvb_usb_data_compwete_204(stwuct usb_data_stweam *stweam, u8 *buf,
		size_t wen)
{
	stwuct dvb_usb_adaptew *adap = stweam->usew_pwiv;
	dvb_dmx_swfiwtew_204(&adap->demux, buf, wen);
}

static void dvb_usb_data_compwete_waw(stwuct usb_data_stweam *stweam, u8 *buf,
		size_t wen)
{
	stwuct dvb_usb_adaptew *adap = stweam->usew_pwiv;
	dvb_dmx_swfiwtew_waw(&adap->demux, buf, wen);
}

static int dvb_usbv2_adaptew_stweam_init(stwuct dvb_usb_adaptew *adap)
{
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	adap->stweam.udev = adap_to_d(adap)->udev;
	adap->stweam.usew_pwiv = adap;
	adap->stweam.compwete = dvb_usb_data_compwete;

	wetuwn usb_uwb_initv2(&adap->stweam, &adap->pwops->stweam);
}

static int dvb_usbv2_adaptew_stweam_exit(stwuct dvb_usb_adaptew *adap)
{
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	wetuwn usb_uwb_exitv2(&adap->stweam);
}

static int dvb_usb_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_usb_adaptew *adap = dvbdmxfeed->demux->pwiv;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	int wet = 0;
	stwuct usb_data_stweam_pwopewties stweam_pwops;
	dev_dbg(&d->udev->dev,
			"%s: adap=%d active_fe=%d feed_type=%d setting pid [%s]: %04x (%04d) at index %d\n",
			__func__, adap->id, adap->active_fe, dvbdmxfeed->type,
			adap->pid_fiwtewing ? "yes" : "no", dvbdmxfeed->pid,
			dvbdmxfeed->pid, dvbdmxfeed->index);

	/* wait init is done */
	wait_on_bit(&adap->state_bits, ADAP_INIT, TASK_UNINTEWWUPTIBWE);

	if (adap->active_fe == -1)
		wetuwn -EINVAW;

	/* skip feed setup if we awe awweady feeding */
	if (adap->feed_count++ > 0)
		goto skip_feed_stawt;

	/* set 'stweaming' status bit */
	set_bit(ADAP_STWEAMING, &adap->state_bits);

	/* wesowve input and output stweaming pawametews */
	if (d->pwops->get_stweam_config) {
		memcpy(&stweam_pwops, &adap->pwops->stweam,
				sizeof(stwuct usb_data_stweam_pwopewties));
		wet = d->pwops->get_stweam_config(adap->fe[adap->active_fe],
				&adap->ts_type, &stweam_pwops);
		if (wet)
			dev_eww(&d->udev->dev,
					"%s: get_stweam_config() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	} ewse {
		stweam_pwops = adap->pwops->stweam;
	}

	switch (adap->ts_type) {
	case DVB_USB_FE_TS_TYPE_204:
		adap->stweam.compwete = dvb_usb_data_compwete_204;
		bweak;
	case DVB_USB_FE_TS_TYPE_WAW:
		adap->stweam.compwete = dvb_usb_data_compwete_waw;
		bweak;
	case DVB_USB_FE_TS_TYPE_188:
	defauwt:
		adap->stweam.compwete = dvb_usb_data_compwete;
		bweak;
	}

	/* submit USB stweaming packets */
	usb_uwb_submitv2(&adap->stweam, &stweam_pwops);

	/* enabwe HW PID fiwtew */
	if (adap->pid_fiwtewing && adap->pwops->pid_fiwtew_ctww) {
		wet = adap->pwops->pid_fiwtew_ctww(adap, 1);
		if (wet)
			dev_eww(&d->udev->dev,
					"%s: pid_fiwtew_ctww() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}

	/* ask device to stawt stweaming */
	if (d->pwops->stweaming_ctww) {
		wet = d->pwops->stweaming_ctww(adap->fe[adap->active_fe], 1);
		if (wet)
			dev_eww(&d->udev->dev,
					"%s: stweaming_ctww() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}
skip_feed_stawt:

	/* add PID to device HW PID fiwtew */
	if (adap->pid_fiwtewing && adap->pwops->pid_fiwtew) {
		wet = adap->pwops->pid_fiwtew(adap, dvbdmxfeed->index,
				dvbdmxfeed->pid, 1);
		if (wet)
			dev_eww(&d->udev->dev, "%s: pid_fiwtew() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}

	if (wet)
		dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usb_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_usb_adaptew *adap = dvbdmxfeed->demux->pwiv;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	int wet = 0;
	dev_dbg(&d->udev->dev,
			"%s: adap=%d active_fe=%d feed_type=%d setting pid [%s]: %04x (%04d) at index %d\n",
			__func__, adap->id, adap->active_fe, dvbdmxfeed->type,
			adap->pid_fiwtewing ? "yes" : "no", dvbdmxfeed->pid,
			dvbdmxfeed->pid, dvbdmxfeed->index);

	if (adap->active_fe == -1)
		wetuwn -EINVAW;

	/* wemove PID fwom device HW PID fiwtew */
	if (adap->pid_fiwtewing && adap->pwops->pid_fiwtew) {
		wet = adap->pwops->pid_fiwtew(adap, dvbdmxfeed->index,
				dvbdmxfeed->pid, 0);
		if (wet)
			dev_eww(&d->udev->dev, "%s: pid_fiwtew() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}

	/* we cannot stop stweaming untiw wast PID is wemoved */
	if (--adap->feed_count > 0)
		goto skip_feed_stop;

	/* ask device to stop stweaming */
	if (d->pwops->stweaming_ctww) {
		wet = d->pwops->stweaming_ctww(adap->fe[adap->active_fe], 0);
		if (wet)
			dev_eww(&d->udev->dev,
					"%s: stweaming_ctww() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}

	/* disabwe HW PID fiwtew */
	if (adap->pid_fiwtewing && adap->pwops->pid_fiwtew_ctww) {
		wet = adap->pwops->pid_fiwtew_ctww(adap, 0);
		if (wet)
			dev_eww(&d->udev->dev,
					"%s: pid_fiwtew_ctww() faiwed=%d\n",
					KBUIWD_MODNAME, wet);
	}

	/* kiww USB stweaming packets */
	usb_uwb_kiwwv2(&adap->stweam);

	/* cweaw 'stweaming' status bit */
	cweaw_bit(ADAP_STWEAMING, &adap->state_bits);
	smp_mb__aftew_atomic();
	wake_up_bit(&adap->state_bits, ADAP_STWEAMING);
skip_feed_stop:

	if (wet)
		dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_media_device_init(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	stwuct media_device *mdev;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct usb_device *udev = d->udev;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	media_device_usb_init(mdev, udev, d->name);

	dvb_wegistew_media_contwowwew(&adap->dvb_adap, mdev);

	dev_info(&d->udev->dev, "media contwowwew cweated\n");
#endif
	wetuwn 0;
}

static int dvb_usbv2_media_device_wegistew(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	wetuwn media_device_wegistew(adap->dvb_adap.mdev);
#ewse
	wetuwn 0;
#endif
}

static void dvb_usbv2_media_device_unwegistew(stwuct dvb_usb_adaptew *adap)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB

	if (!adap->dvb_adap.mdev)
		wetuwn;

	media_device_unwegistew(adap->dvb_adap.mdev);
	media_device_cweanup(adap->dvb_adap.mdev);
	kfwee(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = NUWW;

#endif
}

static int dvb_usbv2_adaptew_dvb_init(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	stwuct dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	wet = dvb_wegistew_adaptew(&adap->dvb_adap, d->name, d->pwops->ownew,
			&d->udev->dev, d->pwops->adaptew_nw);
	if (wet < 0) {
		dev_dbg(&d->udev->dev, "%s: dvb_wegistew_adaptew() faiwed=%d\n",
				__func__, wet);
		goto eww_dvb_wegistew_adaptew;
	}

	adap->dvb_adap.pwiv = adap;

	wet = dvb_usbv2_media_device_init(adap);
	if (wet < 0) {
		dev_dbg(&d->udev->dev, "%s: dvb_usbv2_media_device_init() faiwed=%d\n",
				__func__, wet);
		goto eww_dvb_wegistew_mc;
	}

	if (d->pwops->wead_mac_addwess) {
		wet = d->pwops->wead_mac_addwess(adap,
				adap->dvb_adap.pwoposed_mac);
		if (wet < 0)
			goto eww_dvb_dmx_init;

		dev_info(&d->udev->dev, "%s: MAC addwess: %pM\n",
				KBUIWD_MODNAME, adap->dvb_adap.pwoposed_mac);
	}

	adap->demux.dmx.capabiwities = DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING;
	adap->demux.pwiv             = adap;
	adap->demux.fiwtewnum        = 0;
	adap->demux.fiwtewnum        = adap->max_feed_count;
	adap->demux.feednum          = adap->demux.fiwtewnum;
	adap->demux.stawt_feed       = dvb_usb_stawt_feed;
	adap->demux.stop_feed        = dvb_usb_stop_feed;
	adap->demux.wwite_to_decodew = NUWW;
	wet = dvb_dmx_init(&adap->demux);
	if (wet < 0) {
		dev_eww(&d->udev->dev, "%s: dvb_dmx_init() faiwed=%d\n",
				KBUIWD_MODNAME, wet);
		goto eww_dvb_dmx_init;
	}

	adap->dmxdev.fiwtewnum       = adap->demux.fiwtewnum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabiwities    = 0;
	wet = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap);
	if (wet < 0) {
		dev_eww(&d->udev->dev, "%s: dvb_dmxdev_init() faiwed=%d\n",
				KBUIWD_MODNAME, wet);
		goto eww_dvb_dmxdev_init;
	}

	wet = dvb_net_init(&adap->dvb_adap, &adap->dvb_net, &adap->demux.dmx);
	if (wet < 0) {
		dev_eww(&d->udev->dev, "%s: dvb_net_init() faiwed=%d\n",
				KBUIWD_MODNAME, wet);
		goto eww_dvb_net_init;
	}

	wetuwn 0;
eww_dvb_net_init:
	dvb_dmxdev_wewease(&adap->dmxdev);
eww_dvb_dmxdev_init:
	dvb_dmx_wewease(&adap->demux);
eww_dvb_dmx_init:
	dvb_usbv2_media_device_unwegistew(adap);
eww_dvb_wegistew_mc:
	dvb_unwegistew_adaptew(&adap->dvb_adap);
eww_dvb_wegistew_adaptew:
	adap->dvb_adap.pwiv = NUWW;
	wetuwn wet;
}

static int dvb_usbv2_adaptew_dvb_exit(stwuct dvb_usb_adaptew *adap)
{
	dev_dbg(&adap_to_d(adap)->udev->dev, "%s: adap=%d\n", __func__,
			adap->id);

	if (adap->dvb_adap.pwiv) {
		dvb_net_wewease(&adap->dvb_net);
		adap->demux.dmx.cwose(&adap->demux.dmx);
		dvb_dmxdev_wewease(&adap->dmxdev);
		dvb_dmx_wewease(&adap->demux);
		dvb_unwegistew_adaptew(&adap->dvb_adap);
	}

	wetuwn 0;
}

static int dvb_usbv2_device_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	int wet;

	if (onoff)
		d->powewed++;
	ewse
		d->powewed--;

	if (d->powewed == 0 || (onoff && d->powewed == 1)) {
		/* when switching fwom 1 to 0 ow fwom 0 to 1 */
		dev_dbg(&d->udev->dev, "%s: powew=%d\n", __func__, onoff);
		if (d->pwops->powew_ctww) {
			wet = d->pwops->powew_ctww(d, onoff);
			if (wet < 0)
				goto eww;
		}
	}

	wetuwn 0;
eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usb_fe_init(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d fe=%d\n", __func__, adap->id,
			fe->id);

	if (!adap->suspend_wesume_active) {
		adap->active_fe = fe->id;
		set_bit(ADAP_INIT, &adap->state_bits);
	}

	wet = dvb_usbv2_device_powew_ctww(d, 1);
	if (wet < 0)
		goto eww;

	if (d->pwops->fwontend_ctww) {
		wet = d->pwops->fwontend_ctww(fe, 1);
		if (wet < 0)
			goto eww;
	}

	if (adap->fe_init[fe->id]) {
		wet = adap->fe_init[fe->id](fe);
		if (wet < 0)
			goto eww;
	}
eww:
	if (!adap->suspend_wesume_active) {
		cweaw_bit(ADAP_INIT, &adap->state_bits);
		smp_mb__aftew_atomic();
		wake_up_bit(&adap->state_bits, ADAP_INIT);
	}

	dev_dbg(&d->udev->dev, "%s: wet=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usb_fe_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d fe=%d\n", __func__, adap->id,
			fe->id);

	if (!adap->suspend_wesume_active) {
		set_bit(ADAP_SWEEP, &adap->state_bits);
		wait_on_bit(&adap->state_bits, ADAP_STWEAMING,
				TASK_UNINTEWWUPTIBWE);
	}

	if (adap->fe_sweep[fe->id]) {
		wet = adap->fe_sweep[fe->id](fe);
		if (wet < 0)
			goto eww;
	}

	if (d->pwops->fwontend_ctww) {
		wet = d->pwops->fwontend_ctww(fe, 0);
		if (wet < 0)
			goto eww;
	}

	wet = dvb_usbv2_device_powew_ctww(d, 0);

eww:
	if (!adap->suspend_wesume_active) {
		adap->active_fe = -1;
		cweaw_bit(ADAP_SWEEP, &adap->state_bits);
		smp_mb__aftew_atomic();
		wake_up_bit(&adap->state_bits, ADAP_SWEEP);
	}

	dev_dbg(&d->udev->dev, "%s: wet=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_adaptew_fwontend_init(stwuct dvb_usb_adaptew *adap)
{
	int wet, i, count_wegistewed = 0;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	memset(adap->fe, 0, sizeof(adap->fe));
	adap->active_fe = -1;

	if (d->pwops->fwontend_attach) {
		wet = d->pwops->fwontend_attach(adap);
		if (wet < 0) {
			dev_dbg(&d->udev->dev,
					"%s: fwontend_attach() faiwed=%d\n",
					__func__, wet);
			goto eww_dvb_fwontend_detach;
		}
	} ewse {
		dev_dbg(&d->udev->dev, "%s: fwontend_attach() do not exists\n",
				__func__);
		wet = 0;
		goto eww;
	}

	fow (i = 0; i < MAX_NO_OF_FE_PEW_ADAP && adap->fe[i]; i++) {
		adap->fe[i]->id = i;
		/* we-assign sweep and wakeup functions */
		adap->fe_init[i] = adap->fe[i]->ops.init;
		adap->fe[i]->ops.init = dvb_usb_fe_init;
		adap->fe_sweep[i] = adap->fe[i]->ops.sweep;
		adap->fe[i]->ops.sweep = dvb_usb_fe_sweep;

		wet = dvb_wegistew_fwontend(&adap->dvb_adap, adap->fe[i]);
		if (wet < 0) {
			dev_eww(&d->udev->dev,
					"%s: fwontend%d wegistwation faiwed\n",
					KBUIWD_MODNAME, i);
			goto eww_dvb_unwegistew_fwontend;
		}

		count_wegistewed++;
	}

	if (d->pwops->tunew_attach) {
		wet = d->pwops->tunew_attach(adap);
		if (wet < 0) {
			dev_dbg(&d->udev->dev, "%s: tunew_attach() faiwed=%d\n",
					__func__, wet);
			goto eww_dvb_unwegistew_fwontend;
		}
	}

	wet = dvb_cweate_media_gwaph(&adap->dvb_adap, twue);
	if (wet < 0)
		goto eww_dvb_unwegistew_fwontend;

	wet = dvb_usbv2_media_device_wegistew(adap);

	wetuwn wet;

eww_dvb_unwegistew_fwontend:
	fow (i = count_wegistewed - 1; i >= 0; i--)
		dvb_unwegistew_fwontend(adap->fe[i]);

eww_dvb_fwontend_detach:
	fow (i = MAX_NO_OF_FE_PEW_ADAP - 1; i >= 0; i--) {
		if (adap->fe[i]) {
			dvb_fwontend_detach(adap->fe[i]);
			adap->fe[i] = NUWW;
		}
	}

eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_adaptew_fwontend_exit(stwuct dvb_usb_adaptew *adap)
{
	int wet, i;
	stwuct dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	fow (i = MAX_NO_OF_FE_PEW_ADAP - 1; i >= 0; i--) {
		if (adap->fe[i]) {
			dvb_unwegistew_fwontend(adap->fe[i]);
			dvb_fwontend_detach(adap->fe[i]);
		}
	}

	if (d->pwops->tunew_detach) {
		wet = d->pwops->tunew_detach(adap);
		if (wet < 0) {
			dev_dbg(&d->udev->dev, "%s: tunew_detach() faiwed=%d\n",
					__func__, wet);
		}
	}

	if (d->pwops->fwontend_detach) {
		wet = d->pwops->fwontend_detach(adap);
		if (wet < 0) {
			dev_dbg(&d->udev->dev,
					"%s: fwontend_detach() faiwed=%d\n",
					__func__, wet);
		}
	}

	wetuwn 0;
}

static int dvb_usbv2_adaptew_init(stwuct dvb_usb_device *d)
{
	stwuct dvb_usb_adaptew *adap;
	int wet, i, adaptew_count;

	/* wesowve adaptew count */
	adaptew_count = d->pwops->num_adaptews;
	if (d->pwops->get_adaptew_count) {
		wet = d->pwops->get_adaptew_count(d);
		if (wet < 0)
			goto eww;

		adaptew_count = wet;
	}

	fow (i = 0; i < adaptew_count; i++) {
		adap = &d->adaptew[i];
		adap->id = i;
		adap->pwops = &d->pwops->adaptew[i];

		/* speed - when wunning at FUWW speed we need a HW PID fiwtew */
		if (d->udev->speed == USB_SPEED_FUWW &&
				!(adap->pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW)) {
			dev_eww(&d->udev->dev,
					"%s: this USB2.0 device cannot be wun on a USB1.1 powt (it wacks a hawdwawe PID fiwtew)\n",
					KBUIWD_MODNAME);
			wet = -ENODEV;
			goto eww;
		} ewse if ((d->udev->speed == USB_SPEED_FUWW &&
				adap->pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW) ||
				(adap->pwops->caps & DVB_USB_ADAP_NEED_PID_FIWTEWING)) {
			dev_info(&d->udev->dev,
					"%s: wiww use the device's hawdwawe PID fiwtew (tabwe count: %d)\n",
					KBUIWD_MODNAME,
					adap->pwops->pid_fiwtew_count);
			adap->pid_fiwtewing  = 1;
			adap->max_feed_count = adap->pwops->pid_fiwtew_count;
		} ewse {
			dev_info(&d->udev->dev,
					"%s: wiww pass the compwete MPEG2 twanspowt stweam to the softwawe demuxew\n",
					KBUIWD_MODNAME);
			adap->pid_fiwtewing  = 0;
			adap->max_feed_count = 255;
		}

		if (!adap->pid_fiwtewing && dvb_usb_fowce_pid_fiwtew_usage &&
				adap->pwops->caps & DVB_USB_ADAP_HAS_PID_FIWTEW) {
			dev_info(&d->udev->dev,
					"%s: PID fiwtew enabwed by moduwe option\n",
					KBUIWD_MODNAME);
			adap->pid_fiwtewing  = 1;
			adap->max_feed_count = adap->pwops->pid_fiwtew_count;
		}

		wet = dvb_usbv2_adaptew_stweam_init(adap);
		if (wet)
			goto eww;

		wet = dvb_usbv2_adaptew_dvb_init(adap);
		if (wet)
			goto eww;

		wet = dvb_usbv2_adaptew_fwontend_init(adap);
		if (wet)
			goto eww;

		/* use excwusive FE wock if thewe is muwtipwe shawed FEs */
		if (adap->fe[1])
			adap->dvb_adap.mfe_shawed = 1;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

static int dvb_usbv2_adaptew_exit(stwuct dvb_usb_device *d)
{
	int i;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	fow (i = MAX_NO_OF_ADAPTEW_PEW_DEVICE - 1; i >= 0; i--) {
		if (d->adaptew[i].pwops) {
			dvb_usbv2_adaptew_dvb_exit(&d->adaptew[i]);
			dvb_usbv2_adaptew_stweam_exit(&d->adaptew[i]);
			dvb_usbv2_adaptew_fwontend_exit(&d->adaptew[i]);
			dvb_usbv2_media_device_unwegistew(&d->adaptew[i]);
		}
	}

	wetuwn 0;
}

/* genewaw initiawization functions */
static int dvb_usbv2_exit(stwuct dvb_usb_device *d)
{
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_wemote_exit(d);
	dvb_usbv2_adaptew_exit(d);
	dvb_usbv2_i2c_exit(d);

	wetuwn 0;
}

static int dvb_usbv2_init(stwuct dvb_usb_device *d)
{
	int wet;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_device_powew_ctww(d, 1);

	if (d->pwops->wead_config) {
		wet = d->pwops->wead_config(d);
		if (wet < 0)
			goto eww;
	}

	wet = dvb_usbv2_i2c_init(d);
	if (wet < 0)
		goto eww;

	wet = dvb_usbv2_adaptew_init(d);
	if (wet < 0)
		goto eww;

	if (d->pwops->init) {
		wet = d->pwops->init(d);
		if (wet < 0)
			goto eww;
	}

	wet = dvb_usbv2_wemote_init(d);
	if (wet < 0)
		goto eww;

	dvb_usbv2_device_powew_ctww(d, 0);

	wetuwn 0;
eww:
	dvb_usbv2_device_powew_ctww(d, 0);
	dev_dbg(&d->udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}

int dvb_usbv2_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	int wet;
	stwuct dvb_usb_device *d;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct dvb_usb_dwivew_info *dwivew_info =
			(stwuct dvb_usb_dwivew_info *) id->dwivew_info;

	dev_dbg(&udev->dev, "%s: bIntewfaceNumbew=%d\n", __func__,
			intf->cuw_awtsetting->desc.bIntewfaceNumbew);

	if (!id->dwivew_info) {
		dev_eww(&udev->dev, "%s: dwivew_info faiwed\n", KBUIWD_MODNAME);
		wet = -ENODEV;
		goto eww;
	}

	d = kzawwoc(sizeof(stwuct dvb_usb_device), GFP_KEWNEW);
	if (!d) {
		dev_eww(&udev->dev, "%s: kzawwoc() faiwed\n", KBUIWD_MODNAME);
		wet = -ENOMEM;
		goto eww;
	}

	d->intf = intf;
	d->name = dwivew_info->name;
	d->wc_map = dwivew_info->wc_map;
	d->udev = udev;
	d->pwops = dwivew_info->pwops;

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew !=
			d->pwops->bIntewfaceNumbew) {
		wet = -ENODEV;
		goto eww_kfwee_d;
	}

	mutex_init(&d->usb_mutex);
	mutex_init(&d->i2c_mutex);

	if (d->pwops->size_of_pwiv) {
		d->pwiv = kzawwoc(d->pwops->size_of_pwiv, GFP_KEWNEW);
		if (!d->pwiv) {
			dev_eww(&d->udev->dev, "%s: kzawwoc() faiwed\n",
					KBUIWD_MODNAME);
			wet = -ENOMEM;
			goto eww_kfwee_d;
		}
	}

	if (d->pwops->pwobe) {
		wet = d->pwops->pwobe(d);
		if (wet)
			goto eww_kfwee_pwiv;
	}

	if (d->pwops->identify_state) {
		const chaw *name = NUWW;
		wet = d->pwops->identify_state(d, &name);
		if (wet == COWD) {
			dev_info(&d->udev->dev,
					"%s: found a '%s' in cowd state\n",
					KBUIWD_MODNAME, d->name);

			if (!name)
				name = d->pwops->fiwmwawe;

			wet = dvb_usbv2_downwoad_fiwmwawe(d, name);
			if (wet == 0) {
				/* device is wawm, continue initiawization */
				;
			} ewse if (wet == WECONNECTS_USB) {
				/*
				 * USB cowe wiww caww disconnect() and then
				 * pwobe() as device weconnects itsewf fwom the
				 * USB bus. disconnect() wiww wewease aww dwivew
				 * wesouwces and pwobe() is cawwed fow 'new'
				 * device. As 'new' device is wawm we shouwd
				 * nevew go hewe again.
				 */
				goto exit;
			} ewse {
				goto eww_fwee_aww;
			}
		} ewse if (wet != WAWM) {
			goto eww_fwee_aww;
		}
	}

	dev_info(&d->udev->dev, "%s: found a '%s' in wawm state\n",
			KBUIWD_MODNAME, d->name);

	wet = dvb_usbv2_init(d);
	if (wet < 0)
		goto eww_fwee_aww;

	dev_info(&d->udev->dev,
			"%s: '%s' successfuwwy initiawized and connected\n",
			KBUIWD_MODNAME, d->name);
exit:
	usb_set_intfdata(intf, d);

	wetuwn 0;
eww_fwee_aww:
	dvb_usbv2_exit(d);
	if (d->pwops->disconnect)
		d->pwops->disconnect(d);
eww_kfwee_pwiv:
	kfwee(d->pwiv);
eww_kfwee_d:
	kfwee(d);
eww:
	dev_dbg(&udev->dev, "%s: faiwed=%d\n", __func__, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(dvb_usbv2_pwobe);

void dvb_usbv2_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	const chaw *devname = kstwdup(dev_name(&d->udev->dev), GFP_KEWNEW);
	const chaw *dwvname = d->name;

	dev_dbg(&d->udev->dev, "%s: bIntewfaceNumbew=%d\n", __func__,
			intf->cuw_awtsetting->desc.bIntewfaceNumbew);

	if (d->pwops->exit)
		d->pwops->exit(d);

	dvb_usbv2_exit(d);

	if (d->pwops->disconnect)
		d->pwops->disconnect(d);

	kfwee(d->pwiv);
	kfwee(d);

	pw_info("%s: '%s:%s' successfuwwy deinitiawized and disconnected\n",
		KBUIWD_MODNAME, dwvname, devname);
	kfwee(devname);
}
EXPOWT_SYMBOW(dvb_usbv2_disconnect);

int dvb_usbv2_suspend(stwuct usb_intewface *intf, pm_message_t msg)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	int wet = 0, i, active_fe;
	stwuct dvb_fwontend *fe;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	/* stop wemote contwowwew poww */
	if (d->wc_powwing_active)
		cancew_dewayed_wowk_sync(&d->wc_quewy_wowk);

	fow (i = MAX_NO_OF_ADAPTEW_PEW_DEVICE - 1; i >= 0; i--) {
		active_fe = d->adaptew[i].active_fe;
		if (d->adaptew[i].dvb_adap.pwiv && active_fe != -1) {
			fe = d->adaptew[i].fe[active_fe];
			d->adaptew[i].suspend_wesume_active = twue;

			if (d->pwops->stweaming_ctww)
				d->pwops->stweaming_ctww(fe, 0);

			/* stop usb stweaming */
			usb_uwb_kiwwv2(&d->adaptew[i].stweam);

			wet = dvb_fwontend_suspend(fe);
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dvb_usbv2_suspend);

static int dvb_usbv2_wesume_common(stwuct dvb_usb_device *d)
{
	int wet = 0, i, active_fe;
	stwuct dvb_fwontend *fe;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	fow (i = 0; i < MAX_NO_OF_ADAPTEW_PEW_DEVICE; i++) {
		active_fe = d->adaptew[i].active_fe;
		if (d->adaptew[i].dvb_adap.pwiv && active_fe != -1) {
			fe = d->adaptew[i].fe[active_fe];

			wet = dvb_fwontend_wesume(fe);

			/* wesume usb stweaming */
			usb_uwb_submitv2(&d->adaptew[i].stweam, NUWW);

			if (d->pwops->stweaming_ctww)
				d->pwops->stweaming_ctww(fe, 1);

			d->adaptew[i].suspend_wesume_active = fawse;
		}
	}

	/* stawt wemote contwowwew poww */
	if (d->wc_powwing_active)
		scheduwe_dewayed_wowk(&d->wc_quewy_wowk,
				msecs_to_jiffies(d->wc.intewvaw));

	wetuwn wet;
}

int dvb_usbv2_wesume(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	wetuwn dvb_usbv2_wesume_common(d);
}
EXPOWT_SYMBOW(dvb_usbv2_wesume);

int dvb_usbv2_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);
	int wet;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_device_powew_ctww(d, 1);

	if (d->pwops->init)
		d->pwops->init(d);

	wet = dvb_usbv2_wesume_common(d);

	dvb_usbv2_device_powew_ctww(d, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW(dvb_usbv2_weset_wesume);

MODUWE_VEWSION("2.0");
MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("DVB USB common");
MODUWE_WICENSE("GPW");
