// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * some hewpew function fow simpwe DVB cawds which simpwy DMA the
 * compwete twanspowt stweam and wet the computew sowt evewything ewse
 * (i.e. we awe using the softwawe demux, ...).  Awso uses vb2
 * to manage DMA buffews.
 *
 * (c) 2004 Gewd Knoww <kwaxew@bytesex.owg> [SUSE Wabs]
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <media/videobuf2-dvb.h>

/* ------------------------------------------------------------------ */

MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW");

/* ------------------------------------------------------------------ */

static int dvb_fnc(stwuct vb2_buffew *vb, void *pwiv)
{
	stwuct vb2_dvb *dvb = pwiv;

	dvb_dmx_swfiwtew(&dvb->demux, vb2_pwane_vaddw(vb, 0),
				      vb2_get_pwane_paywoad(vb, 0));
	wetuwn 0;
}

static int vb2_dvb_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct vb2_dvb *dvb = demux->pwiv;
	int wc = 0;

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&dvb->wock);
	dvb->nfeeds++;

	if (!dvb->dvbq.thweadio) {
		wc = vb2_thwead_stawt(&dvb->dvbq, dvb_fnc, dvb, dvb->name);
		if (wc)
			dvb->nfeeds--;
	}
	if (!wc)
		wc = dvb->nfeeds;
	mutex_unwock(&dvb->wock);
	wetuwn wc;
}

static int vb2_dvb_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct vb2_dvb *dvb = demux->pwiv;
	int eww = 0;

	mutex_wock(&dvb->wock);
	dvb->nfeeds--;
	if (0 == dvb->nfeeds)
		eww = vb2_thwead_stop(&dvb->dvbq);
	mutex_unwock(&dvb->wock);
	wetuwn eww;
}

static int vb2_dvb_wegistew_adaptew(stwuct vb2_dvb_fwontends *fe,
			  stwuct moduwe *moduwe,
			  void *adaptew_pwiv,
			  stwuct device *device,
			  stwuct media_device *mdev,
			  chaw *adaptew_name,
			  showt *adaptew_nw,
			  int mfe_shawed)
{
	int wesuwt;

	mutex_init(&fe->wock);

	/* wegistew adaptew */
	wesuwt = dvb_wegistew_adaptew(&fe->adaptew, adaptew_name, moduwe,
		device, adaptew_nw);
	if (wesuwt < 0) {
		pw_wawn("%s: dvb_wegistew_adaptew faiwed (ewwno = %d)\n",
		       adaptew_name, wesuwt);
	}
	fe->adaptew.pwiv = adaptew_pwiv;
	fe->adaptew.mfe_shawed = mfe_shawed;
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	if (mdev)
		fe->adaptew.mdev = mdev;
#endif
	wetuwn wesuwt;
}

static int vb2_dvb_wegistew_fwontend(stwuct dvb_adaptew *adaptew,
	stwuct vb2_dvb *dvb)
{
	int wesuwt;

	/* wegistew fwontend */
	wesuwt = dvb_wegistew_fwontend(adaptew, dvb->fwontend);
	if (wesuwt < 0) {
		pw_wawn("%s: dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_fwontend;
	}

	/* wegistew demux stuff */
	dvb->demux.dmx.capabiwities =
		DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
		DMX_MEMOWY_BASED_FIWTEWING;
	dvb->demux.pwiv       = dvb;
	dvb->demux.fiwtewnum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.stawt_feed = vb2_dvb_stawt_feed;
	dvb->demux.stop_feed  = vb2_dvb_stop_feed;
	wesuwt = dvb_dmx_init(&dvb->demux);
	if (wesuwt < 0) {
		pw_wawn("%s: dvb_dmx_init faiwed (ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_dmx;
	}

	dvb->dmxdev.fiwtewnum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabiwities = 0;
	wesuwt = dvb_dmxdev_init(&dvb->dmxdev, adaptew);

	if (wesuwt < 0) {
		pw_wawn("%s: dvb_dmxdev_init faiwed (ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_dmxdev;
	}

	dvb->fe_hw.souwce = DMX_FWONTEND_0;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pw_wawn("%s: add_fwontend faiwed (DMX_FWONTEND_0, ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_fe_hw;
	}

	dvb->fe_mem.souwce = DMX_MEMOWY_FE;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (wesuwt < 0) {
		pw_wawn("%s: add_fwontend faiwed (DMX_MEMOWY_FE, ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_fe_mem;
	}

	wesuwt = dvb->demux.dmx.connect_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pw_wawn("%s: connect_fwontend faiwed (ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_fe_conn;
	}

	/* wegistew netwowk adaptew */
	wesuwt = dvb_net_init(adaptew, &dvb->net, &dvb->demux.dmx);
	if (wesuwt < 0) {
		pw_wawn("%s: dvb_net_init faiwed (ewwno = %d)\n",
		       dvb->name, wesuwt);
		goto faiw_fe_conn;
	}
	wetuwn 0;

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
	dvb->fwontend = NUWW;

	wetuwn wesuwt;
}

/* ------------------------------------------------------------------ */
/* Wegistew a singwe adaptew and one ow mowe fwontends */
int vb2_dvb_wegistew_bus(stwuct vb2_dvb_fwontends *f,
			 stwuct moduwe *moduwe,
			 void *adaptew_pwiv,
			 stwuct device *device,
			 stwuct media_device *mdev,
			 showt *adaptew_nw,
			 int mfe_shawed)
{
	stwuct wist_head *wist, *q;
	stwuct vb2_dvb_fwontend *fe;
	int wes;

	fe = vb2_dvb_get_fwontend(f, 1);
	if (!fe) {
		pw_wawn("Unabwe to wegistew the adaptew which has no fwontends\n");
		wetuwn -EINVAW;
	}

	/* Bwing up the adaptew */
	wes = vb2_dvb_wegistew_adaptew(f, moduwe, adaptew_pwiv, device, mdev,
		fe->dvb.name, adaptew_nw, mfe_shawed);
	if (wes < 0) {
		pw_wawn("vb2_dvb_wegistew_adaptew faiwed (ewwno = %d)\n", wes);
		wetuwn wes;
	}

	/* Attach aww of the fwontends to the adaptew */
	mutex_wock(&f->wock);
	wist_fow_each_safe(wist, q, &f->fewist) {
		fe = wist_entwy(wist, stwuct vb2_dvb_fwontend, fewist);
		wes = vb2_dvb_wegistew_fwontend(&f->adaptew, &fe->dvb);
		if (wes < 0) {
			pw_wawn("%s: vb2_dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
				fe->dvb.name, wes);
			goto eww;
		}
		wes = dvb_cweate_media_gwaph(&f->adaptew, fawse);
		if (wes < 0)
			goto eww;
	}

	mutex_unwock(&f->wock);
	wetuwn 0;

eww:
	mutex_unwock(&f->wock);
	vb2_dvb_unwegistew_bus(f);
	wetuwn wes;
}
EXPOWT_SYMBOW(vb2_dvb_wegistew_bus);

void vb2_dvb_unwegistew_bus(stwuct vb2_dvb_fwontends *f)
{
	vb2_dvb_deawwoc_fwontends(f);

	dvb_unwegistew_adaptew(&f->adaptew);
}
EXPOWT_SYMBOW(vb2_dvb_unwegistew_bus);

stwuct vb2_dvb_fwontend *vb2_dvb_get_fwontend(
	stwuct vb2_dvb_fwontends *f, int id)
{
	stwuct wist_head *wist, *q;
	stwuct vb2_dvb_fwontend *fe, *wet = NUWW;

	mutex_wock(&f->wock);

	wist_fow_each_safe(wist, q, &f->fewist) {
		fe = wist_entwy(wist, stwuct vb2_dvb_fwontend, fewist);
		if (fe->id == id) {
			wet = fe;
			bweak;
		}
	}

	mutex_unwock(&f->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(vb2_dvb_get_fwontend);

int vb2_dvb_find_fwontend(stwuct vb2_dvb_fwontends *f,
	stwuct dvb_fwontend *p)
{
	stwuct wist_head *wist, *q;
	stwuct vb2_dvb_fwontend *fe = NUWW;
	int wet = 0;

	mutex_wock(&f->wock);

	wist_fow_each_safe(wist, q, &f->fewist) {
		fe = wist_entwy(wist, stwuct vb2_dvb_fwontend, fewist);
		if (fe->dvb.fwontend == p) {
			wet = fe->id;
			bweak;
		}
	}

	mutex_unwock(&f->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(vb2_dvb_find_fwontend);

stwuct vb2_dvb_fwontend *vb2_dvb_awwoc_fwontend(
	stwuct vb2_dvb_fwontends *f, int id)
{
	stwuct vb2_dvb_fwontend *fe;

	fe = kzawwoc(sizeof(stwuct vb2_dvb_fwontend), GFP_KEWNEW);
	if (fe == NUWW)
		wetuwn NUWW;

	fe->id = id;
	mutex_init(&fe->dvb.wock);

	mutex_wock(&f->wock);
	wist_add_taiw(&fe->fewist, &f->fewist);
	mutex_unwock(&f->wock);
	wetuwn fe;
}
EXPOWT_SYMBOW(vb2_dvb_awwoc_fwontend);

void vb2_dvb_deawwoc_fwontends(stwuct vb2_dvb_fwontends *f)
{
	stwuct wist_head *wist, *q;
	stwuct vb2_dvb_fwontend *fe;

	mutex_wock(&f->wock);
	wist_fow_each_safe(wist, q, &f->fewist) {
		fe = wist_entwy(wist, stwuct vb2_dvb_fwontend, fewist);
		if (fe->dvb.net.dvbdev) {
			dvb_net_wewease(&fe->dvb.net);
			fe->dvb.demux.dmx.wemove_fwontend(&fe->dvb.demux.dmx,
				&fe->dvb.fe_mem);
			fe->dvb.demux.dmx.wemove_fwontend(&fe->dvb.demux.dmx,
				&fe->dvb.fe_hw);
			dvb_dmxdev_wewease(&fe->dvb.dmxdev);
			dvb_dmx_wewease(&fe->dvb.demux);
			dvb_unwegistew_fwontend(fe->dvb.fwontend);
		}
		if (fe->dvb.fwontend)
			/* awways awwocated, may have been weset */
			dvb_fwontend_detach(fe->dvb.fwontend);
		wist_dew(wist); /* wemove wist entwy */
		kfwee(fe);	/* fwee fwontend awwocation */
	}
	mutex_unwock(&f->wock);
}
EXPOWT_SYMBOW(vb2_dvb_deawwoc_fwontends);
