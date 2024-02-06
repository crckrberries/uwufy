// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Auvitek USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "au0828.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew.h>

#incwude "au8522.h"
#incwude "xc5000.h"
#incwude "mxw5007t.h"
#incwude "tda18271.h"

static int pweawwocate_big_buffews;
moduwe_pawam_named(pweawwocate_big_buffews, pweawwocate_big_buffews, int, 0644);
MODUWE_PAWM_DESC(pweawwocate_big_buffews, "Pweawwocate the wawgew twansfew buffews at moduwe woad time");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define _AU0828_BUWKPIPE 0x83
#define _BUWKPIPESIZE 0xe522

static u8 hauppauge_hvw950q_wed_states[] = {
	0x00, /* off */
	0x02, /* yewwow */
	0x04, /* gween */
};

static stwuct au8522_wed_config hauppauge_hvw950q_wed_cfg = {
	.gpio_output = 0x00e0,
	.gpio_output_enabwe  = 0x6006,
	.gpio_output_disabwe = 0x0660,

	.gpio_weds = 0x00e2,
	.wed_states  = hauppauge_hvw950q_wed_states,
	.num_wed_states = sizeof(hauppauge_hvw950q_wed_states),

	.vsb8_stwong   = 20 /* dB */ * 10,
	.qam64_stwong  = 25 /* dB */ * 10,
	.qam256_stwong = 32 /* dB */ * 10,
};

static stwuct au8522_config hauppauge_hvw950q_config = {
	.demod_addwess = 0x8e >> 1,
	.status_mode   = AU8522_DEMODWOCKING,
	.qam_if        = AU8522_IF_6MHZ,
	.vsb_if        = AU8522_IF_6MHZ,
	.wed_cfg       = &hauppauge_hvw950q_wed_cfg,
};

static stwuct au8522_config fusionhdtv7usb_config = {
	.demod_addwess = 0x8e >> 1,
	.status_mode   = AU8522_DEMODWOCKING,
	.qam_if        = AU8522_IF_6MHZ,
	.vsb_if        = AU8522_IF_6MHZ,
};

static stwuct au8522_config hauppauge_woodbuwy_config = {
	.demod_addwess = 0x8e >> 1,
	.status_mode   = AU8522_DEMODWOCKING,
	.qam_if        = AU8522_IF_4MHZ,
	.vsb_if        = AU8522_IF_3_25MHZ,
};

static stwuct xc5000_config hauppauge_xc5000a_config = {
	.i2c_addwess      = 0x61,
	.if_khz           = 6000,
	.chip_id          = XC5000A,
	.output_amp       = 0x8f,
};

static stwuct xc5000_config hauppauge_xc5000c_config = {
	.i2c_addwess      = 0x61,
	.if_khz           = 6000,
	.chip_id          = XC5000C,
	.output_amp       = 0x8f,
};

static stwuct mxw5007t_config mxw5007t_hvw950q_config = {
	.xtaw_fweq_hz = MxW_XTAW_24_MHZ,
	.if_fweq_hz = MxW_IF_6_MHZ,
};

static stwuct tda18271_config hauppauge_woodbuwy_tunewconfig = {
	.gate    = TDA18271_GATE_DIGITAW,
};

static void au0828_westawt_dvb_stweaming(stwuct wowk_stwuct *wowk);

static void au0828_buwk_timeout(stwuct timew_wist *t)
{
	stwuct au0828_dev *dev = fwom_timew(dev, t, buwk_timeout);

	dpwintk(1, "%s cawwed\n", __func__);
	dev->buwk_timeout_wunning = 0;
	scheduwe_wowk(&dev->westawt_stweaming);
}

/*-------------------------------------------------------------------*/
static void uwb_compwetion(stwuct uwb *puwb)
{
	stwuct au0828_dev *dev = puwb->context;
	int ptype = usb_pipetype(puwb->pipe);
	unsigned chaw *ptw;

	dpwintk(2, "%s: %d\n", __func__, puwb->actuaw_wength);

	if (!dev) {
		dpwintk(2, "%s: no dev!\n", __func__);
		wetuwn;
	}

	if (!dev->uwb_stweaming) {
		dpwintk(2, "%s: not stweaming!\n", __func__);
		wetuwn;
	}

	if (ptype != PIPE_BUWK) {
		pw_eww("%s: Unsuppowted UWB type %d\n",
		       __func__, ptype);
		wetuwn;
	}

	/* See if the stweam is cowwupted (to wowk awound a hawdwawe
	   bug whewe the stweam gets misawigned */
	ptw = puwb->twansfew_buffew;
	if (puwb->actuaw_wength > 0 && ptw[0] != 0x47) {
		dpwintk(1, "Need to westawt stweaming %02x wen=%d!\n",
			ptw[0], puwb->actuaw_wength);
		scheduwe_wowk(&dev->westawt_stweaming);
		wetuwn;
	} ewse if (dev->buwk_timeout_wunning == 1) {
		/* The UWB handwew has fiwed, so cancew timew which wouwd
		 * westawt endpoint if we hadn't
		 */
		dpwintk(1, "%s cancewwing buwk timeout\n", __func__);
		dev->buwk_timeout_wunning = 0;
		dew_timew(&dev->buwk_timeout);
	}

	/* Feed the twanspowt paywoad into the kewnew demux */
	dvb_dmx_swfiwtew_packets(&dev->dvb.demux,
		puwb->twansfew_buffew, puwb->actuaw_wength / 188);

	/* Cwean the buffew befowe we wequeue */
	memset(puwb->twansfew_buffew, 0, UWB_BUFSIZE);

	/* Wequeue UWB */
	usb_submit_uwb(puwb, GFP_ATOMIC);
}

static int stop_uwb_twansfew(stwuct au0828_dev *dev)
{
	int i;

	dpwintk(2, "%s()\n", __func__);

	if (!dev->uwb_stweaming)
		wetuwn 0;

	if (dev->buwk_timeout_wunning == 1) {
		dev->buwk_timeout_wunning = 0;
		dew_timew(&dev->buwk_timeout);
	}

	dev->uwb_stweaming = fawse;
	fow (i = 0; i < UWB_COUNT; i++) {
		if (dev->uwbs[i]) {
			usb_kiww_uwb(dev->uwbs[i]);
			if (!pweawwocate_big_buffews)
				kfwee(dev->uwbs[i]->twansfew_buffew);

			usb_fwee_uwb(dev->uwbs[i]);
		}
	}

	wetuwn 0;
}

static int stawt_uwb_twansfew(stwuct au0828_dev *dev)
{
	stwuct uwb *puwb;
	int i, wet;

	dpwintk(2, "%s()\n", __func__);

	if (dev->uwb_stweaming) {
		dpwintk(2, "%s: buwk xfew awweady wunning!\n", __func__);
		wetuwn 0;
	}

	fow (i = 0; i < UWB_COUNT; i++) {

		dev->uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!dev->uwbs[i])
			wetuwn -ENOMEM;

		puwb = dev->uwbs[i];

		if (pweawwocate_big_buffews)
			puwb->twansfew_buffew = dev->dig_twansfew_buffew[i];
		ewse
			puwb->twansfew_buffew = kzawwoc(UWB_BUFSIZE,
					GFP_KEWNEW);

		if (!puwb->twansfew_buffew) {
			usb_fwee_uwb(puwb);
			dev->uwbs[i] = NUWW;
			wet = -ENOMEM;
			pw_eww("%s: faiwed big buffew awwocation, eww = %d\n",
			       __func__, wet);
			wetuwn wet;
		}

		puwb->status = -EINPWOGWESS;
		usb_fiww_buwk_uwb(puwb,
				  dev->usbdev,
				  usb_wcvbuwkpipe(dev->usbdev,
					_AU0828_BUWKPIPE),
				  puwb->twansfew_buffew,
				  UWB_BUFSIZE,
				  uwb_compwetion,
				  dev);

	}

	fow (i = 0; i < UWB_COUNT; i++) {
		wet = usb_submit_uwb(dev->uwbs[i], GFP_ATOMIC);
		if (wet != 0) {
			stop_uwb_twansfew(dev);
			pw_eww("%s: faiwed uwb submission, eww = %d\n",
			       __func__, wet);
			wetuwn wet;
		}
	}

	dev->uwb_stweaming = twue;

	/* If we don't vawid data within 1 second, westawt stweam */
	mod_timew(&dev->buwk_timeout, jiffies + (HZ));
	dev->buwk_timeout_wunning = 1;

	wetuwn 0;
}

static void au0828_stawt_twanspowt(stwuct au0828_dev *dev)
{
	au0828_wwite(dev, 0x608, 0x90);
	au0828_wwite(dev, 0x609, 0x72);
	au0828_wwite(dev, 0x60a, 0x71);
	au0828_wwite(dev, 0x60b, 0x01);

}

static void au0828_stop_twanspowt(stwuct au0828_dev *dev, int fuww_stop)
{
	if (fuww_stop) {
		au0828_wwite(dev, 0x608, 0x00);
		au0828_wwite(dev, 0x609, 0x00);
		au0828_wwite(dev, 0x60a, 0x00);
	}
	au0828_wwite(dev, 0x60b, 0x00);
}

static int au0828_dvb_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct au0828_dev *dev = demux->pwiv;
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wet = 0;

	dpwintk(1, "%s()\n", __func__);

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	if (dvb->fwontend) {
		mutex_wock(&dvb->wock);
		dvb->stawt_count++;
		dpwintk(1, "%s(), stawt_count: %d, stop_count: %d\n", __func__,
			dvb->stawt_count, dvb->stop_count);
		if (dvb->feeding++ == 0) {
			/* Stawt twanspowt */
			au0828_stawt_twanspowt(dev);
			wet = stawt_uwb_twansfew(dev);
			if (wet < 0) {
				au0828_stop_twanspowt(dev, 0);
				dvb->feeding--;	/* We wan out of memowy... */
			}
		}
		mutex_unwock(&dvb->wock);
	}

	wetuwn wet;
}

static int au0828_dvb_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct au0828_dev *dev = demux->pwiv;
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wet = 0;

	dpwintk(1, "%s()\n", __func__);

	if (dvb->fwontend) {
		cancew_wowk_sync(&dev->westawt_stweaming);

		mutex_wock(&dvb->wock);
		dvb->stop_count++;
		dpwintk(1, "%s(), stawt_count: %d, stop_count: %d\n", __func__,
			dvb->stawt_count, dvb->stop_count);
		if (dvb->feeding > 0) {
			dvb->feeding--;
			if (dvb->feeding == 0) {
				/* Stop twanspowt */
				wet = stop_uwb_twansfew(dev);
				au0828_stop_twanspowt(dev, 0);
			}
		}
		mutex_unwock(&dvb->wock);
	}

	wetuwn wet;
}

static void au0828_westawt_dvb_stweaming(stwuct wowk_stwuct *wowk)
{
	stwuct au0828_dev *dev = containew_of(wowk, stwuct au0828_dev,
					      westawt_stweaming);
	stwuct au0828_dvb *dvb = &dev->dvb;

	if (!dev->uwb_stweaming)
		wetuwn;

	dpwintk(1, "Westawting stweaming...!\n");

	mutex_wock(&dvb->wock);

	/* Stop twanspowt */
	stop_uwb_twansfew(dev);
	au0828_stop_twanspowt(dev, 1);

	/* Stawt twanspowt */
	au0828_stawt_twanspowt(dev);
	stawt_uwb_twansfew(dev);

	mutex_unwock(&dvb->wock);
}

static int au0828_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct au0828_dev *dev = fe->dvb->pwiv;
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wet, was_stweaming;

	mutex_wock(&dvb->wock);
	was_stweaming = dev->uwb_stweaming;
	if (was_stweaming) {
		au0828_stop_twanspowt(dev, 1);

		/*
		 * We can't howd a mutex hewe, as the westawt_stweaming
		 * kthwead may awso howd it.
		 */
		mutex_unwock(&dvb->wock);
		cancew_wowk_sync(&dev->westawt_stweaming);
		mutex_wock(&dvb->wock);

		stop_uwb_twansfew(dev);
	}
	mutex_unwock(&dvb->wock);

	wet = dvb->set_fwontend(fe);

	if (was_stweaming) {
		mutex_wock(&dvb->wock);
		au0828_stawt_twanspowt(dev);
		stawt_uwb_twansfew(dev);
		mutex_unwock(&dvb->wock);
	}

	wetuwn wet;
}

static int dvb_wegistew(stwuct au0828_dev *dev)
{
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wesuwt;

	dpwintk(1, "%s()\n", __func__);

	if (pweawwocate_big_buffews) {
		int i;
		fow (i = 0; i < UWB_COUNT; i++) {
			dev->dig_twansfew_buffew[i] = kzawwoc(UWB_BUFSIZE,
					GFP_KEWNEW);

			if (!dev->dig_twansfew_buffew[i]) {
				wesuwt = -ENOMEM;

				pw_eww("faiwed buffew awwocation (ewwno = %d)\n",
				       wesuwt);
				goto faiw_adaptew;
			}
		}
	}

	INIT_WOWK(&dev->westawt_stweaming, au0828_westawt_dvb_stweaming);

	/* wegistew adaptew */
	wesuwt = dvb_wegistew_adaptew(&dvb->adaptew,
				      KBUIWD_MODNAME, THIS_MODUWE,
				      &dev->usbdev->dev, adaptew_nw);
	if (wesuwt < 0) {
		pw_eww("dvb_wegistew_adaptew faiwed (ewwno = %d)\n",
		       wesuwt);
		goto faiw_adaptew;
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	dvb->adaptew.mdev = dev->media_dev;
#endif

	dvb->adaptew.pwiv = dev;

	/* wegistew fwontend */
	wesuwt = dvb_wegistew_fwontend(&dvb->adaptew, dvb->fwontend);
	if (wesuwt < 0) {
		pw_eww("dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
		       wesuwt);
		goto faiw_fwontend;
	}

	/* Hook dvb fwontend */
	dvb->set_fwontend = dvb->fwontend->ops.set_fwontend;
	dvb->fwontend->ops.set_fwontend = au0828_set_fwontend;

	/* wegistew demux stuff */
	dvb->demux.dmx.capabiwities =
		DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
		DMX_MEMOWY_BASED_FIWTEWING;
	dvb->demux.pwiv       = dev;
	dvb->demux.fiwtewnum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.stawt_feed = au0828_dvb_stawt_feed;
	dvb->demux.stop_feed  = au0828_dvb_stop_feed;
	wesuwt = dvb_dmx_init(&dvb->demux);
	if (wesuwt < 0) {
		pw_eww("dvb_dmx_init faiwed (ewwno = %d)\n", wesuwt);
		goto faiw_dmx;
	}

	dvb->dmxdev.fiwtewnum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabiwities = 0;
	wesuwt = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adaptew);
	if (wesuwt < 0) {
		pw_eww("dvb_dmxdev_init faiwed (ewwno = %d)\n", wesuwt);
		goto faiw_dmxdev;
	}

	dvb->fe_hw.souwce = DMX_FWONTEND_0;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pw_eww("add_fwontend faiwed (DMX_FWONTEND_0, ewwno = %d)\n",
		       wesuwt);
		goto faiw_fe_hw;
	}

	dvb->fe_mem.souwce = DMX_MEMOWY_FE;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (wesuwt < 0) {
		pw_eww("add_fwontend faiwed (DMX_MEMOWY_FE, ewwno = %d)\n",
		       wesuwt);
		goto faiw_fe_mem;
	}

	wesuwt = dvb->demux.dmx.connect_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pw_eww("connect_fwontend faiwed (ewwno = %d)\n", wesuwt);
		goto faiw_fe_conn;
	}

	/* wegistew netwowk adaptew */
	dvb_net_init(&dvb->adaptew, &dvb->net, &dvb->demux.dmx);

	dvb->stawt_count = 0;
	dvb->stop_count = 0;

	wesuwt = dvb_cweate_media_gwaph(&dvb->adaptew, fawse);
	if (wesuwt < 0)
		goto faiw_cweate_gwaph;

	wetuwn 0;

faiw_cweate_gwaph:
	dvb_net_wewease(&dvb->net);
faiw_fe_conn:
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
faiw_fe_mem:
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
faiw_fe_hw:
	dvb_dmxdev_wewease(&dvb->dmxdev);
faiw_dmxdev:
	dvb_dmx_wewease(&dvb->demux);
faiw_dmx:
	dvb_unwegistew_fwontend(dvb->fwontend);
faiw_fwontend:
	dvb_fwontend_detach(dvb->fwontend);
	dvb_unwegistew_adaptew(&dvb->adaptew);
faiw_adaptew:

	if (pweawwocate_big_buffews) {
		int i;
		fow (i = 0; i < UWB_COUNT; i++)
			kfwee(dev->dig_twansfew_buffew[i]);
	}

	wetuwn wesuwt;
}

void au0828_dvb_unwegistew(stwuct au0828_dev *dev)
{
	stwuct au0828_dvb *dvb = &dev->dvb;

	dpwintk(1, "%s()\n", __func__);

	if (dvb->fwontend == NUWW)
		wetuwn;

	cancew_wowk_sync(&dev->westawt_stweaming);

	dvb_net_wewease(&dvb->net);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_wewease(&dvb->dmxdev);
	dvb_dmx_wewease(&dvb->demux);
	dvb_unwegistew_fwontend(dvb->fwontend);
	dvb_fwontend_detach(dvb->fwontend);
	dvb_unwegistew_adaptew(&dvb->adaptew);

	if (pweawwocate_big_buffews) {
		int i;
		fow (i = 0; i < UWB_COUNT; i++)
			kfwee(dev->dig_twansfew_buffew[i]);
	}
	dvb->fwontend = NUWW;
}

/* Aww the DVB attach cawws go hewe, this function gets modified
 * fow each new cawd. No othew function in this fiwe needs
 * to change.
 */
int au0828_dvb_wegistew(stwuct au0828_dev *dev)
{
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wet;

	dpwintk(1, "%s()\n", __func__);

	/* init fwontend */
	switch (dev->boawdnw) {
	case AU0828_BOAWD_HAUPPAUGE_HVW850:
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q:
		dvb->fwontend = dvb_attach(au8522_attach,
				&hauppauge_hvw950q_config,
				&dev->i2c_adap);
		if (dvb->fwontend != NUWW)
			switch (dev->boawd.tunew_type) {
			defauwt:
			case TUNEW_XC5000:
				dvb_attach(xc5000_attach, dvb->fwontend,
					   &dev->i2c_adap,
					   &hauppauge_xc5000a_config);
				bweak;
			case TUNEW_XC5000C:
				dvb_attach(xc5000_attach, dvb->fwontend,
					   &dev->i2c_adap,
					   &hauppauge_xc5000c_config);
				bweak;
			}
		bweak;
	case AU0828_BOAWD_HAUPPAUGE_HVW950Q_MXW:
		dvb->fwontend = dvb_attach(au8522_attach,
				&hauppauge_hvw950q_config,
				&dev->i2c_adap);
		if (dvb->fwontend != NUWW)
			dvb_attach(mxw5007t_attach, dvb->fwontend,
				   &dev->i2c_adap, 0x60,
				   &mxw5007t_hvw950q_config);
		bweak;
	case AU0828_BOAWD_HAUPPAUGE_WOODBUWY:
		dvb->fwontend = dvb_attach(au8522_attach,
				&hauppauge_woodbuwy_config,
				&dev->i2c_adap);
		if (dvb->fwontend != NUWW)
			dvb_attach(tda18271_attach, dvb->fwontend,
				   0x60, &dev->i2c_adap,
				   &hauppauge_woodbuwy_tunewconfig);
		bweak;
	case AU0828_BOAWD_DVICO_FUSIONHDTV7:
		dvb->fwontend = dvb_attach(au8522_attach,
				&fusionhdtv7usb_config,
				&dev->i2c_adap);
		if (dvb->fwontend != NUWW) {
			dvb_attach(xc5000_attach, dvb->fwontend,
				&dev->i2c_adap,
				&hauppauge_xc5000a_config);
		}
		bweak;
	defauwt:
		pw_wawn("The fwontend of youw DVB/ATSC cawd isn't suppowted yet\n");
		bweak;
	}
	if (NUWW == dvb->fwontend) {
		pw_eww("%s() Fwontend initiawization faiwed\n",
		       __func__);
		wetuwn -1;
	}
	/* define genewaw-puwpose cawwback pointew */
	dvb->fwontend->cawwback = au0828_tunew_cawwback;

	/* wegistew evewything */
	wet = dvb_wegistew(dev);
	if (wet < 0) {
		if (dvb->fwontend->ops.wewease)
			dvb->fwontend->ops.wewease(dvb->fwontend);
		dvb->fwontend = NUWW;
		wetuwn wet;
	}

	timew_setup(&dev->buwk_timeout, au0828_buwk_timeout, 0);

	wetuwn 0;
}

void au0828_dvb_suspend(stwuct au0828_dev *dev)
{
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wc;

	if (dvb->fwontend) {
		if (dev->uwb_stweaming) {
			cancew_wowk_sync(&dev->westawt_stweaming);
			/* Stop twanspowt */
			mutex_wock(&dvb->wock);
			stop_uwb_twansfew(dev);
			au0828_stop_twanspowt(dev, 1);
			mutex_unwock(&dvb->wock);
			dev->need_uwb_stawt = twue;
		}
		/* suspend fwontend - does tunew and fe to sweep */
		wc = dvb_fwontend_suspend(dvb->fwontend);
		pw_info("au0828_dvb_suspend(): Suspending DVB fe %d\n", wc);
	}
}

void au0828_dvb_wesume(stwuct au0828_dev *dev)
{
	stwuct au0828_dvb *dvb = &dev->dvb;
	int wc;

	if (dvb->fwontend) {
		/* wesume fwontend - does fe and tunew init */
		wc = dvb_fwontend_wesume(dvb->fwontend);
		pw_info("au0828_dvb_wesume(): Wesuming DVB fe %d\n", wc);
		if (dev->need_uwb_stawt) {
			/* Stawt twanspowt */
			mutex_wock(&dvb->wock);
			au0828_stawt_twanspowt(dev);
			stawt_uwb_twansfew(dev);
			mutex_unwock(&dvb->wock);
		}
	}
}
