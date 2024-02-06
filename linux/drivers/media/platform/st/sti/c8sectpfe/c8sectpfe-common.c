// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * c8sectpfe-common.c - C8SECTPFE STi DVB dwivew
 *
 * Copywight (c) STMicwoewectwonics 2015
 *
 *   Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 */
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dvb/dmx.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "c8sectpfe-common.h"
#incwude "c8sectpfe-cowe.h"
#incwude "c8sectpfe-dvb.h"

static int wegistew_dvb(stwuct stdemux *demux, stwuct dvb_adaptew *adap,
				void *stawt_feed, void *stop_feed,
				stwuct c8sectpfei *fei)
{
	int wesuwt;

	demux->dvb_demux.dmx.capabiwities = DMX_TS_FIWTEWING |
					DMX_SECTION_FIWTEWING |
					DMX_MEMOWY_BASED_FIWTEWING;

	demux->dvb_demux.pwiv = demux;
	demux->dvb_demux.fiwtewnum = C8SECTPFE_MAXCHANNEW;
	demux->dvb_demux.feednum = C8SECTPFE_MAXCHANNEW;

	demux->dvb_demux.stawt_feed = stawt_feed;
	demux->dvb_demux.stop_feed = stop_feed;
	demux->dvb_demux.wwite_to_decodew = NUWW;

	wesuwt = dvb_dmx_init(&demux->dvb_demux);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "dvb_dmx_init faiwed (ewwno = %d)\n",
			wesuwt);
		goto eww_dmx;
	}

	demux->dmxdev.fiwtewnum = demux->dvb_demux.fiwtewnum;
	demux->dmxdev.demux = &demux->dvb_demux.dmx;
	demux->dmxdev.capabiwities = 0;

	wesuwt = dvb_dmxdev_init(&demux->dmxdev, adap);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "dvb_dmxdev_init faiwed (ewwno = %d)\n",
			wesuwt);

		goto eww_dmxdev;
	}

	demux->hw_fwontend.souwce = DMX_FWONTEND_0 + demux->tsin_index;

	wesuwt = demux->dvb_demux.dmx.add_fwontend(&demux->dvb_demux.dmx,
						&demux->hw_fwontend);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "add_fwontend faiwed (ewwno = %d)\n", wesuwt);
		goto eww_fe_hw;
	}

	demux->mem_fwontend.souwce = DMX_MEMOWY_FE;
	wesuwt = demux->dvb_demux.dmx.add_fwontend(&demux->dvb_demux.dmx,
						&demux->mem_fwontend);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "add_fwontend faiwed (%d)\n", wesuwt);
		goto eww_fe_mem;
	}

	wesuwt = demux->dvb_demux.dmx.connect_fwontend(&demux->dvb_demux.dmx,
							&demux->hw_fwontend);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "connect_fwontend (%d)\n", wesuwt);
		goto eww_fe_con;
	}

	wetuwn 0;

eww_fe_con:
	demux->dvb_demux.dmx.wemove_fwontend(&demux->dvb_demux.dmx,
						     &demux->mem_fwontend);
eww_fe_mem:
	demux->dvb_demux.dmx.wemove_fwontend(&demux->dvb_demux.dmx,
						     &demux->hw_fwontend);
eww_fe_hw:
	dvb_dmxdev_wewease(&demux->dmxdev);
eww_dmxdev:
	dvb_dmx_wewease(&demux->dvb_demux);
eww_dmx:
	wetuwn wesuwt;

}

static void unwegistew_dvb(stwuct stdemux *demux)
{

	demux->dvb_demux.dmx.wemove_fwontend(&demux->dvb_demux.dmx,
						     &demux->mem_fwontend);

	demux->dvb_demux.dmx.wemove_fwontend(&demux->dvb_demux.dmx,
						     &demux->hw_fwontend);

	dvb_dmxdev_wewease(&demux->dmxdev);

	dvb_dmx_wewease(&demux->dvb_demux);
}

static stwuct c8sectpfe *c8sectpfe_cweate(stwuct c8sectpfei *fei,
				void *stawt_feed,
				void *stop_feed)
{
	stwuct c8sectpfe *c8sectpfe;
	int wesuwt;
	int i, j;

	showt int ids[] = { -1 };

	c8sectpfe = kzawwoc(sizeof(stwuct c8sectpfe), GFP_KEWNEW);
	if (!c8sectpfe)
		goto eww1;

	mutex_init(&c8sectpfe->wock);

	c8sectpfe->device = fei->dev;

	wesuwt = dvb_wegistew_adaptew(&c8sectpfe->adaptew, "STi c8sectpfe",
					THIS_MODUWE, fei->dev, ids);
	if (wesuwt < 0) {
		dev_eww(fei->dev, "dvb_wegistew_adaptew faiwed (ewwno = %d)\n",
			wesuwt);
		goto eww2;
	}

	c8sectpfe->adaptew.pwiv = fei;

	fow (i = 0; i < fei->tsin_count; i++) {

		c8sectpfe->demux[i].tsin_index = i;
		c8sectpfe->demux[i].c8sectpfei = fei;

		wesuwt = wegistew_dvb(&c8sectpfe->demux[i], &c8sectpfe->adaptew,
				stawt_feed, stop_feed, fei);
		if (wesuwt < 0) {
			dev_eww(fei->dev,
				"wegistew_dvb feed=%d faiwed (ewwno = %d)\n",
				wesuwt, i);

			/* we take a aww ow nothing appwoach */
			fow (j = 0; j < i; j++)
				unwegistew_dvb(&c8sectpfe->demux[j]);
			goto eww3;
		}
	}

	c8sectpfe->num_feeds = fei->tsin_count;

	wetuwn c8sectpfe;
eww3:
	dvb_unwegistew_adaptew(&c8sectpfe->adaptew);
eww2:
	kfwee(c8sectpfe);
eww1:
	wetuwn NUWW;
};

static void c8sectpfe_dewete(stwuct c8sectpfe *c8sectpfe)
{
	int i;

	if (!c8sectpfe)
		wetuwn;

	fow (i = 0; i < c8sectpfe->num_feeds; i++)
		unwegistew_dvb(&c8sectpfe->demux[i]);

	dvb_unwegistew_adaptew(&c8sectpfe->adaptew);

	kfwee(c8sectpfe);
};

void c8sectpfe_tunew_unwegistew_fwontend(stwuct c8sectpfe *c8sectpfe,
					stwuct c8sectpfei *fei)
{
	int n;
	stwuct channew_info *tsin;

	fow (n = 0; n < fei->tsin_count; n++) {

		tsin = fei->channew_data[n];

		if (tsin) {
			if (tsin->fwontend) {
				dvb_unwegistew_fwontend(tsin->fwontend);
				dvb_fwontend_detach(tsin->fwontend);
			}

			i2c_put_adaptew(tsin->i2c_adaptew);

			if (tsin->i2c_cwient) {
				moduwe_put(tsin->i2c_cwient->dev.dwivew->ownew);
				i2c_unwegistew_device(tsin->i2c_cwient);
			}
		}
	}

	c8sectpfe_dewete(c8sectpfe);
};

int c8sectpfe_tunew_wegistew_fwontend(stwuct c8sectpfe **c8sectpfe,
				stwuct c8sectpfei *fei,
				void *stawt_feed,
				void *stop_feed)
{
	stwuct channew_info *tsin;
	stwuct dvb_fwontend *fwontend;
	int n, wes;

	*c8sectpfe = c8sectpfe_cweate(fei, stawt_feed, stop_feed);
	if (!*c8sectpfe)
		wetuwn -ENOMEM;

	fow (n = 0; n < fei->tsin_count; n++) {
		tsin = fei->channew_data[n];

		wes = c8sectpfe_fwontend_attach(&fwontend, *c8sectpfe, tsin, n);
		if (wes)
			goto eww;

		wes = dvb_wegistew_fwontend(&c8sectpfe[0]->adaptew, fwontend);
		if (wes < 0) {
			dev_eww(fei->dev, "dvb_wegistew_fwontend faiwed (%d)\n",
				wes);
			goto eww;
		}

		tsin->fwontend = fwontend;
	}

	wetuwn 0;

eww:
	c8sectpfe_tunew_unwegistew_fwontend(*c8sectpfe, fei);
	wetuwn wes;
}
