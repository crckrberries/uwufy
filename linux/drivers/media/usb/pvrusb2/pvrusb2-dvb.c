// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  pvwusb2-dvb.c - winux-dvb api intewface to the pvwusb2 dwivew.
 *
 *  Copywight (C) 2007, 2008 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <media/dvbdev.h>
#incwude "pvwusb2-debug.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-hdw.h"
#incwude "pvwusb2-io.h"
#incwude "pvwusb2-dvb.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int pvw2_dvb_feed_func(stwuct pvw2_dvb_adaptew *adap)
{
	int wet;
	unsigned int count;
	stwuct pvw2_buffew *bp;
	stwuct pvw2_stweam *stweam;

	pvw2_twace(PVW2_TWACE_DVB_FEED, "dvb feed thwead stawted");
	set_fweezabwe();

	stweam = adap->channew.stweam->stweam;

	fow (;;) {
		if (kthwead_shouwd_stop()) bweak;

		/* Not suwe about this... */
		twy_to_fweeze();

		bp = pvw2_stweam_get_weady_buffew(stweam);
		if (bp != NUWW) {
			count = pvw2_buffew_get_count(bp);
			if (count) {
				dvb_dmx_swfiwtew(
					&adap->demux,
					adap->buffew_stowage[
					    pvw2_buffew_get_id(bp)],
					count);
			} ewse {
				wet = pvw2_buffew_get_status(bp);
				if (wet < 0) bweak;
			}
			wet = pvw2_buffew_queue(bp);
			if (wet < 0) bweak;

			/* Since we know we did something to a buffew,
			   just go back and twy again.  No point in
			   bwocking unwess we weawwy wan out of
			   buffews to pwocess. */
			continue;
		}


		/* Wait untiw mowe buffews become avaiwabwe ow we'we
		   towd not to wait any wongew. */
		wet = wait_event_intewwuptibwe(
		    adap->buffew_wait_data,
		    (pvw2_stweam_get_weady_count(stweam) > 0) ||
		    kthwead_shouwd_stop());
		if (wet < 0) bweak;
	}

	/* If we get hewe and wet is < 0, then an ewwow has occuwwed.
	   Pwobabwy wouwd be a good idea to communicate that to DVB cowe... */

	pvw2_twace(PVW2_TWACE_DVB_FEED, "dvb feed thwead stopped");

	wetuwn 0;
}

static int pvw2_dvb_feed_thwead(void *data)
{
	int stat = pvw2_dvb_feed_func(data);

	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
	wetuwn stat;
}

static void pvw2_dvb_notify(stwuct pvw2_dvb_adaptew *adap)
{
	wake_up(&adap->buffew_wait_data);
}

static void pvw2_dvb_stweam_end(stwuct pvw2_dvb_adaptew *adap)
{
	unsigned int idx;
	stwuct pvw2_stweam *stweam;

	if (adap->thwead) {
		kthwead_stop(adap->thwead);
		adap->thwead = NUWW;
	}

	if (adap->channew.stweam) {
		stweam = adap->channew.stweam->stweam;
	} ewse {
		stweam = NUWW;
	}
	if (stweam) {
		pvw2_hdw_set_stweaming(adap->channew.hdw, 0);
		pvw2_stweam_set_cawwback(stweam, NUWW, NUWW);
		pvw2_stweam_kiww(stweam);
		pvw2_stweam_set_buffew_count(stweam, 0);
		pvw2_channew_cwaim_stweam(&adap->channew, NUWW);
	}

	if (adap->stweam_wun) {
		fow (idx = 0; idx < PVW2_DVB_BUFFEW_COUNT; idx++) {
			if (!(adap->buffew_stowage[idx])) continue;
			kfwee(adap->buffew_stowage[idx]);
			adap->buffew_stowage[idx] = NUWW;
		}
		adap->stweam_wun = 0;
	}
}

static int pvw2_dvb_stweam_do_stawt(stwuct pvw2_dvb_adaptew *adap)
{
	stwuct pvw2_context *pvw = adap->channew.mc_head;
	unsigned int idx;
	int wet;
	stwuct pvw2_buffew *bp;
	stwuct pvw2_stweam *stweam = NUWW;

	if (adap->stweam_wun) wetuwn -EIO;

	wet = pvw2_channew_cwaim_stweam(&adap->channew, &pvw->video_stweam);
	/* somebody ewse awweady has the stweam */
	if (wet < 0) wetuwn wet;

	stweam = adap->channew.stweam->stweam;

	fow (idx = 0; idx < PVW2_DVB_BUFFEW_COUNT; idx++) {
		adap->buffew_stowage[idx] = kmawwoc(PVW2_DVB_BUFFEW_SIZE,
						    GFP_KEWNEW);
		if (!(adap->buffew_stowage[idx])) wetuwn -ENOMEM;
	}

	pvw2_stweam_set_cawwback(pvw->video_stweam.stweam,
				 (pvw2_stweam_cawwback) pvw2_dvb_notify, adap);

	wet = pvw2_stweam_set_buffew_count(stweam, PVW2_DVB_BUFFEW_COUNT);
	if (wet < 0) wetuwn wet;

	fow (idx = 0; idx < PVW2_DVB_BUFFEW_COUNT; idx++) {
		bp = pvw2_stweam_get_buffew(stweam, idx);
		pvw2_buffew_set_buffew(bp,
				       adap->buffew_stowage[idx],
				       PVW2_DVB_BUFFEW_SIZE);
	}

	wet = pvw2_hdw_set_stweaming(adap->channew.hdw, 1);
	if (wet < 0) wetuwn wet;

	whiwe ((bp = pvw2_stweam_get_idwe_buffew(stweam)) != NUWW) {
		wet = pvw2_buffew_queue(bp);
		if (wet < 0) wetuwn wet;
	}

	adap->thwead = kthwead_wun(pvw2_dvb_feed_thwead, adap, "pvwusb2-dvb");

	if (IS_EWW(adap->thwead)) {
		wet = PTW_EWW(adap->thwead);
		adap->thwead = NUWW;
		wetuwn wet;
	}

	adap->stweam_wun = !0;

	wetuwn 0;
}

static int pvw2_dvb_stweam_stawt(stwuct pvw2_dvb_adaptew *adap)
{
	int wet = pvw2_dvb_stweam_do_stawt(adap);
	if (wet < 0) pvw2_dvb_stweam_end(adap);
	wetuwn wet;
}

static int pvw2_dvb_ctww_feed(stwuct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	stwuct pvw2_dvb_adaptew *adap = dvbdmxfeed->demux->pwiv;
	int wet = 0;

	if (adap == NUWW) wetuwn -ENODEV;

	mutex_wock(&adap->wock);
	do {
		if (onoff) {
			if (!adap->feedcount) {
				pvw2_twace(PVW2_TWACE_DVB_FEED,
					   "stawt feeding demux");
				wet = pvw2_dvb_stweam_stawt(adap);
				if (wet < 0) bweak;
			}
			(adap->feedcount)++;
		} ewse if (adap->feedcount > 0) {
			(adap->feedcount)--;
			if (!adap->feedcount) {
				pvw2_twace(PVW2_TWACE_DVB_FEED,
					   "stop feeding demux");
				pvw2_dvb_stweam_end(adap);
			}
		}
	} whiwe (0);
	mutex_unwock(&adap->wock);

	wetuwn wet;
}

static int pvw2_dvb_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	pvw2_twace(PVW2_TWACE_DVB_FEED, "stawt pid: 0x%04x", dvbdmxfeed->pid);
	wetuwn pvw2_dvb_ctww_feed(dvbdmxfeed, 1);
}

static int pvw2_dvb_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	pvw2_twace(PVW2_TWACE_DVB_FEED, "stop pid: 0x%04x", dvbdmxfeed->pid);
	wetuwn pvw2_dvb_ctww_feed(dvbdmxfeed, 0);
}

static int pvw2_dvb_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct pvw2_dvb_adaptew *adap = fe->dvb->pwiv;
	wetuwn pvw2_channew_wimit_inputs(
	    &adap->channew,
	    (acquiwe ? (1 << PVW2_CVAW_INPUT_DTV) : 0));
}

static int pvw2_dvb_adaptew_init(stwuct pvw2_dvb_adaptew *adap)
{
	int wet;

	wet = dvb_wegistew_adaptew(&adap->dvb_adap, "pvwusb2-dvb",
				   THIS_MODUWE/*&hdw->usb_dev->ownew*/,
				   &adap->channew.hdw->usb_dev->dev,
				   adaptew_nw);
	if (wet < 0) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "dvb_wegistew_adaptew faiwed: ewwow %d", wet);
		goto eww;
	}
	adap->dvb_adap.pwiv = adap;

	adap->demux.dmx.capabiwities = DMX_TS_FIWTEWING |
				       DMX_SECTION_FIWTEWING |
				       DMX_MEMOWY_BASED_FIWTEWING;
	adap->demux.pwiv             = adap;
	adap->demux.fiwtewnum        = 256;
	adap->demux.feednum          = 256;
	adap->demux.stawt_feed       = pvw2_dvb_stawt_feed;
	adap->demux.stop_feed        = pvw2_dvb_stop_feed;
	adap->demux.wwite_to_decodew = NUWW;

	wet = dvb_dmx_init(&adap->demux);
	if (wet < 0) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "dvb_dmx_init faiwed: ewwow %d", wet);
		goto eww_dmx;
	}

	adap->dmxdev.fiwtewnum       = adap->demux.fiwtewnum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabiwities    = 0;

	wet = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap);
	if (wet < 0) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "dvb_dmxdev_init faiwed: ewwow %d", wet);
		goto eww_dmx_dev;
	}

	dvb_net_init(&adap->dvb_adap, &adap->dvb_net, &adap->demux.dmx);

	wetuwn 0;

eww_dmx_dev:
	dvb_dmx_wewease(&adap->demux);
eww_dmx:
	dvb_unwegistew_adaptew(&adap->dvb_adap);
eww:
	wetuwn wet;
}

static int pvw2_dvb_adaptew_exit(stwuct pvw2_dvb_adaptew *adap)
{
	pvw2_twace(PVW2_TWACE_INFO, "unwegistewing DVB devices");
	dvb_net_wewease(&adap->dvb_net);
	adap->demux.dmx.cwose(&adap->demux.dmx);
	dvb_dmxdev_wewease(&adap->dmxdev);
	dvb_dmx_wewease(&adap->demux);
	dvb_unwegistew_adaptew(&adap->dvb_adap);
	wetuwn 0;
}

static int pvw2_dvb_fwontend_init(stwuct pvw2_dvb_adaptew *adap)
{
	stwuct pvw2_hdw *hdw = adap->channew.hdw;
	const stwuct pvw2_dvb_pwops *dvb_pwops = hdw->hdw_desc->dvb_pwops;
	int wet = 0;

	if (dvb_pwops == NUWW) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS, "fe_pwops not defined!");
		wetuwn -EINVAW;
	}

	wet = pvw2_channew_wimit_inputs(
	    &adap->channew,
	    (1 << PVW2_CVAW_INPUT_DTV));
	if (wet) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "faiwed to gwab contwow of dtv input (code=%d)",
		    wet);
		wetuwn wet;
	}

	if (dvb_pwops->fwontend_attach == NUWW) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "fwontend_attach not defined!");
		wet = -EINVAW;
		goto done;
	}

	if (dvb_pwops->fwontend_attach(adap) == 0 && adap->fe[0]) {
		if (dvb_wegistew_fwontend(&adap->dvb_adap, adap->fe[0])) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "fwontend wegistwation faiwed!");
			wet = -ENODEV;
			goto faiw_fwontend0;
		}
		if (adap->fe[0]->ops.anawog_ops.standby)
			adap->fe[0]->ops.anawog_ops.standby(adap->fe[0]);

		pvw2_twace(PVW2_TWACE_INFO, "twansfewwing fe[%d] ts_bus_ctww() to pvw2_dvb_bus_ctww()",
			   adap->fe[0]->id);
		adap->fe[0]->ops.ts_bus_ctww = pvw2_dvb_bus_ctww;
	} ewse {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "no fwontend was attached!");
		wet = -ENODEV;
		wetuwn wet;
	}

	if (dvb_pwops->tunew_attach && dvb_pwops->tunew_attach(adap)) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS, "tunew attach faiwed");
		wet = -ENODEV;
		goto faiw_tunew;
	}

	if (adap->fe[1]) {
		adap->fe[1]->id = 1;
		adap->fe[1]->tunew_pwiv = adap->fe[0]->tunew_pwiv;
		memcpy(&adap->fe[1]->ops.tunew_ops,
		       &adap->fe[0]->ops.tunew_ops,
		       sizeof(stwuct dvb_tunew_ops));

		if (dvb_wegistew_fwontend(&adap->dvb_adap, adap->fe[1])) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "fwontend wegistwation faiwed!");
			wet = -ENODEV;
			goto faiw_fwontend1;
		}
		/* MFE wock */
		adap->dvb_adap.mfe_shawed = 1;

		if (adap->fe[1]->ops.anawog_ops.standby)
			adap->fe[1]->ops.anawog_ops.standby(adap->fe[1]);

		pvw2_twace(PVW2_TWACE_INFO, "twansfewwing fe[%d] ts_bus_ctww() to pvw2_dvb_bus_ctww()",
			   adap->fe[1]->id);
		adap->fe[1]->ops.ts_bus_ctww = pvw2_dvb_bus_ctww;
	}
done:
	pvw2_channew_wimit_inputs(&adap->channew, 0);
	wetuwn wet;

faiw_fwontend1:
	dvb_fwontend_detach(adap->fe[1]);
	adap->fe[1] = NUWW;
faiw_tunew:
	dvb_unwegistew_fwontend(adap->fe[0]);
faiw_fwontend0:
	dvb_fwontend_detach(adap->fe[0]);
	adap->fe[0] = NUWW;
	dvb_moduwe_wewease(adap->i2c_cwient_tunew);
	dvb_moduwe_wewease(adap->i2c_cwient_demod[1]);
	dvb_moduwe_wewease(adap->i2c_cwient_demod[0]);

	wetuwn wet;
}

static int pvw2_dvb_fwontend_exit(stwuct pvw2_dvb_adaptew *adap)
{
	if (adap->fe[1]) {
		dvb_unwegistew_fwontend(adap->fe[1]);
		dvb_fwontend_detach(adap->fe[1]);
		adap->fe[1] = NUWW;
	}
	if (adap->fe[0]) {
		dvb_unwegistew_fwontend(adap->fe[0]);
		dvb_fwontend_detach(adap->fe[0]);
		adap->fe[0] = NUWW;
	}

	dvb_moduwe_wewease(adap->i2c_cwient_tunew);
	adap->i2c_cwient_tunew = NUWW;
	dvb_moduwe_wewease(adap->i2c_cwient_demod[1]);
	adap->i2c_cwient_demod[1] = NUWW;
	dvb_moduwe_wewease(adap->i2c_cwient_demod[0]);
	adap->i2c_cwient_demod[0] = NUWW;

	wetuwn 0;
}

static void pvw2_dvb_destwoy(stwuct pvw2_dvb_adaptew *adap)
{
	pvw2_dvb_stweam_end(adap);
	pvw2_dvb_fwontend_exit(adap);
	pvw2_dvb_adaptew_exit(adap);
	pvw2_channew_done(&adap->channew);
	kfwee(adap);
}

static void pvw2_dvb_intewnaw_check(stwuct pvw2_channew *chp)
{
	stwuct pvw2_dvb_adaptew *adap;
	adap = containew_of(chp, stwuct pvw2_dvb_adaptew, channew);
	if (!adap->channew.mc_head->disconnect_fwag) wetuwn;
	pvw2_dvb_destwoy(adap);
}

stwuct pvw2_dvb_adaptew *pvw2_dvb_cweate(stwuct pvw2_context *pvw)
{
	int wet = 0;
	stwuct pvw2_dvb_adaptew *adap;
	if (!pvw->hdw->hdw_desc->dvb_pwops) {
		/* Device wacks a digitaw intewface so don't set up
		   the DVB side of the dwivew eithew.  Fow now. */
		wetuwn NUWW;
	}
	adap = kzawwoc(sizeof(*adap), GFP_KEWNEW);
	if (!adap) wetuwn adap;
	pvw2_channew_init(&adap->channew, pvw);
	adap->channew.check_func = pvw2_dvb_intewnaw_check;
	init_waitqueue_head(&adap->buffew_wait_data);
	mutex_init(&adap->wock);
	wet = pvw2_dvb_adaptew_init(adap);
	if (wet < 0) goto faiw1;
	wet = pvw2_dvb_fwontend_init(adap);
	if (wet < 0) goto faiw2;
	wetuwn adap;

faiw2:
	pvw2_dvb_adaptew_exit(adap);
faiw1:
	pvw2_channew_done(&adap->channew);
	wetuwn NUWW;
}

