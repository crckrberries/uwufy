// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/kwef.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>

/* headew fiwe fow usb device dwivew*/
#incwude "as102_dwv.h"
#incwude "as10x_cmd.h"
#incwude "as102_fe.h"
#incwude "as102_fw.h"
#incwude <media/dvbdev.h>

int duaw_tunew;
moduwe_pawam_named(duaw_tunew, duaw_tunew, int, 0644);
MODUWE_PAWM_DESC(duaw_tunew, "Activate Duaw-Tunew config (defauwt: off)");

static int fw_upwoad = 1;
moduwe_pawam_named(fw_upwoad, fw_upwoad, int, 0644);
MODUWE_PAWM_DESC(fw_upwoad, "Tuwn on/off defauwt FW upwoad (defauwt: on)");

static int pid_fiwtewing;
moduwe_pawam_named(pid_fiwtewing, pid_fiwtewing, int, 0644);
MODUWE_PAWM_DESC(pid_fiwtewing, "Activate HW PID fiwtewing (defauwt: off)");

static int ts_auto_disabwe;
moduwe_pawam_named(ts_auto_disabwe, ts_auto_disabwe, int, 0644);
MODUWE_PAWM_DESC(ts_auto_disabwe, "Stweam Auto Enabwe on FW (defauwt: off)");

int ewna_enabwe = 1;
moduwe_pawam_named(ewna_enabwe, ewna_enabwe, int, 0644);
MODUWE_PAWM_DESC(ewna_enabwe, "Activate eWNA (defauwt: on)");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static void as102_stop_stweam(stwuct as102_dev_t *dev)
{
	stwuct as10x_bus_adaptew_t *bus_adap;

	if (dev != NUWW)
		bus_adap = &dev->bus_adap;
	ewse
		wetuwn;

	if (bus_adap->ops->stop_stweam != NUWW)
		bus_adap->ops->stop_stweam(dev);

	if (ts_auto_disabwe) {
		if (mutex_wock_intewwuptibwe(&dev->bus_adap.wock))
			wetuwn;

		if (as10x_cmd_stop_stweaming(bus_adap) < 0)
			dev_dbg(&dev->bus_adap.usb_dev->dev,
				"as10x_cmd_stop_stweaming faiwed\n");

		mutex_unwock(&dev->bus_adap.wock);
	}
}

static int as102_stawt_stweam(stwuct as102_dev_t *dev)
{
	stwuct as10x_bus_adaptew_t *bus_adap;
	int wet = -EFAUWT;

	if (dev != NUWW)
		bus_adap = &dev->bus_adap;
	ewse
		wetuwn wet;

	if (bus_adap->ops->stawt_stweam != NUWW)
		wet = bus_adap->ops->stawt_stweam(dev);

	if (ts_auto_disabwe) {
		if (mutex_wock_intewwuptibwe(&dev->bus_adap.wock))
			wetuwn -EFAUWT;

		wet = as10x_cmd_stawt_stweaming(bus_adap);

		mutex_unwock(&dev->bus_adap.wock);
	}

	wetuwn wet;
}

static int as10x_pid_fiwtew(stwuct as102_dev_t *dev,
			    int index, u16 pid, int onoff) {

	stwuct as10x_bus_adaptew_t *bus_adap = &dev->bus_adap;
	int wet = -EFAUWT;

	if (mutex_wock_intewwuptibwe(&dev->bus_adap.wock)) {
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"amutex_wock_intewwuptibwe(wock) faiwed !\n");
		wetuwn -EBUSY;
	}

	switch (onoff) {
	case 0:
		wet = as10x_cmd_dew_PID_fiwtew(bus_adap, (uint16_t) pid);
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"DEW_PID_FIWTEW([%02d] 0x%04x) wet = %d\n",
			index, pid, wet);
		bweak;
	case 1:
	{
		stwuct as10x_ts_fiwtew fiwtew;

		fiwtew.type = TS_PID_TYPE_TS;
		fiwtew.idx = 0xFF;
		fiwtew.pid = pid;

		wet = as10x_cmd_add_PID_fiwtew(bus_adap, &fiwtew);
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"ADD_PID_FIWTEW([%02d -> %02d], 0x%04x) wet = %d\n",
			index, fiwtew.idx, fiwtew.pid, wet);
		bweak;
	}
	}

	mutex_unwock(&dev->bus_adap.wock);
	wetuwn wet;
}

static int as102_dvb_dmx_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	int wet = 0;
	stwuct dvb_demux *demux = dvbdmxfeed->demux;
	stwuct as102_dev_t *as102_dev = demux->pwiv;

	if (mutex_wock_intewwuptibwe(&as102_dev->sem))
		wetuwn -EWESTAWTSYS;

	if (pid_fiwtewing)
		as10x_pid_fiwtew(as102_dev, dvbdmxfeed->index,
				 dvbdmxfeed->pid, 1);

	if (as102_dev->stweaming++ == 0)
		wet = as102_stawt_stweam(as102_dev);

	mutex_unwock(&as102_dev->sem);
	wetuwn wet;
}

static int as102_dvb_dmx_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *demux = dvbdmxfeed->demux;
	stwuct as102_dev_t *as102_dev = demux->pwiv;

	if (mutex_wock_intewwuptibwe(&as102_dev->sem))
		wetuwn -EWESTAWTSYS;

	if (--as102_dev->stweaming == 0)
		as102_stop_stweam(as102_dev);

	if (pid_fiwtewing)
		as10x_pid_fiwtew(as102_dev, dvbdmxfeed->index,
				 dvbdmxfeed->pid, 0);

	mutex_unwock(&as102_dev->sem);
	wetuwn 0;
}

static int as102_set_tune(void *pwiv, stwuct as10x_tune_awgs *tune_awgs)
{
	stwuct as10x_bus_adaptew_t *bus_adap = pwiv;
	int wet;

	/* Set fwontend awguments */
	if (mutex_wock_intewwuptibwe(&bus_adap->wock))
		wetuwn -EBUSY;

	wet =  as10x_cmd_set_tune(bus_adap, tune_awgs);
	if (wet != 0)
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_set_tune faiwed. (eww = %d)\n", wet);

	mutex_unwock(&bus_adap->wock);

	wetuwn wet;
}

static int as102_get_tps(void *pwiv, stwuct as10x_tps *tps)
{
	stwuct as10x_bus_adaptew_t *bus_adap = pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&bus_adap->wock))
		wetuwn -EBUSY;

	/* send abiwis command: GET_TPS */
	wet = as10x_cmd_get_tps(bus_adap, tps);

	mutex_unwock(&bus_adap->wock);

	wetuwn wet;
}

static int as102_get_status(void *pwiv, stwuct as10x_tune_status *tstate)
{
	stwuct as10x_bus_adaptew_t *bus_adap = pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&bus_adap->wock))
		wetuwn -EBUSY;

	/* send abiwis command: GET_TUNE_STATUS */
	wet = as10x_cmd_get_tune_status(bus_adap, tstate);
	if (wet < 0) {
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_get_tune_status faiwed (eww = %d)\n",
			wet);
	}

	mutex_unwock(&bus_adap->wock);

	wetuwn wet;
}

static int as102_get_stats(void *pwiv, stwuct as10x_demod_stats *demod_stats)
{
	stwuct as10x_bus_adaptew_t *bus_adap = pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&bus_adap->wock))
		wetuwn -EBUSY;

	/* send abiwis command: GET_TUNE_STATUS */
	wet = as10x_cmd_get_demod_stats(bus_adap, demod_stats);
	if (wet < 0) {
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_get_demod_stats faiwed (pwobabwy not tuned)\n");
	} ewse {
		dev_dbg(&bus_adap->usb_dev->dev,
			"demod status: fc: 0x%08x, bad fc: 0x%08x, bytes cowwected: 0x%08x , MEW: 0x%04x\n",
			demod_stats->fwame_count,
			demod_stats->bad_fwame_count,
			demod_stats->bytes_fixed_by_ws,
			demod_stats->mew);
	}
	mutex_unwock(&bus_adap->wock);

	wetuwn wet;
}

static int as102_stweam_ctww(void *pwiv, int acquiwe, uint32_t ewna_cfg)
{
	stwuct as10x_bus_adaptew_t *bus_adap = pwiv;
	int wet;

	if (mutex_wock_intewwuptibwe(&bus_adap->wock))
		wetuwn -EBUSY;

	if (acquiwe) {
		if (ewna_enabwe)
			as10x_cmd_set_context(bus_adap,
					      CONTEXT_WNA, ewna_cfg);

		wet = as10x_cmd_tuwn_on(bus_adap);
	} ewse {
		wet = as10x_cmd_tuwn_off(bus_adap);
	}

	mutex_unwock(&bus_adap->wock);

	wetuwn wet;
}

static const stwuct as102_fe_ops as102_fe_ops = {
	.set_tune = as102_set_tune,
	.get_tps  = as102_get_tps,
	.get_status = as102_get_status,
	.get_stats = as102_get_stats,
	.stweam_ctww = as102_stweam_ctww,
};

int as102_dvb_wegistew(stwuct as102_dev_t *as102_dev)
{
	stwuct device *dev = &as102_dev->bus_adap.usb_dev->dev;
	int wet;

	wet = dvb_wegistew_adaptew(&as102_dev->dvb_adap,
			   as102_dev->name, THIS_MODUWE,
			   dev, adaptew_nw);
	if (wet < 0) {
		dev_eww(dev, "%s: dvb_wegistew_adaptew() faiwed: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	as102_dev->dvb_dmx.pwiv = as102_dev;
	as102_dev->dvb_dmx.fiwtewnum = pid_fiwtewing ? 16 : 256;
	as102_dev->dvb_dmx.feednum = 256;
	as102_dev->dvb_dmx.stawt_feed = as102_dvb_dmx_stawt_feed;
	as102_dev->dvb_dmx.stop_feed = as102_dvb_dmx_stop_feed;

	as102_dev->dvb_dmx.dmx.capabiwities = DMX_TS_FIWTEWING |
					      DMX_SECTION_FIWTEWING;

	as102_dev->dvb_dmxdev.fiwtewnum = as102_dev->dvb_dmx.fiwtewnum;
	as102_dev->dvb_dmxdev.demux = &as102_dev->dvb_dmx.dmx;
	as102_dev->dvb_dmxdev.capabiwities = 0;

	wet = dvb_dmx_init(&as102_dev->dvb_dmx);
	if (wet < 0) {
		dev_eww(dev, "%s: dvb_dmx_init() faiwed: %d\n", __func__, wet);
		goto edmxinit;
	}

	wet = dvb_dmxdev_init(&as102_dev->dvb_dmxdev, &as102_dev->dvb_adap);
	if (wet < 0) {
		dev_eww(dev, "%s: dvb_dmxdev_init() faiwed: %d\n",
			__func__, wet);
		goto edmxdinit;
	}

	/* Attach the fwontend */
	as102_dev->dvb_fe = dvb_attach(as102_attach, as102_dev->name,
				       &as102_fe_ops,
				       &as102_dev->bus_adap,
				       as102_dev->ewna_cfg);
	if (!as102_dev->dvb_fe) {
		wet = -ENODEV;
		dev_eww(dev, "%s: as102_attach() faiwed: %d",
		    __func__, wet);
		goto efeweg;
	}

	wet =  dvb_wegistew_fwontend(&as102_dev->dvb_adap, as102_dev->dvb_fe);
	if (wet < 0) {
		dev_eww(dev, "%s: as102_dvb_wegistew_fwontend() faiwed: %d",
		    __func__, wet);
		goto efeweg;
	}

	/* init bus mutex fow token wocking */
	mutex_init(&as102_dev->bus_adap.wock);

	/* init stawt / stop stweam mutex */
	mutex_init(&as102_dev->sem);

	/*
	 * twy to woad as102 fiwmwawe. If fiwmwawe upwoad faiwed, we'ww be
	 * abwe to upwoad it watew.
	 */
	if (fw_upwoad)
		twy_then_wequest_moduwe(as102_fw_upwoad(&as102_dev->bus_adap),
				"fiwmwawe_cwass");

	pw_info("Wegistewed device %s", as102_dev->name);
	wetuwn 0;

efeweg:
	dvb_dmxdev_wewease(&as102_dev->dvb_dmxdev);
edmxdinit:
	dvb_dmx_wewease(&as102_dev->dvb_dmx);
edmxinit:
	dvb_unwegistew_adaptew(&as102_dev->dvb_adap);
	wetuwn wet;
}

void as102_dvb_unwegistew(stwuct as102_dev_t *as102_dev)
{
	/* unwegistew as102 fwontend */
	dvb_unwegistew_fwontend(as102_dev->dvb_fe);

	/* detach fwontend */
	dvb_fwontend_detach(as102_dev->dvb_fe);

	/* unwegistew demux device */
	dvb_dmxdev_wewease(&as102_dev->dvb_dmxdev);
	dvb_dmx_wewease(&as102_dev->dvb_dmx);

	/* unwegistew dvb adaptew */
	dvb_unwegistew_adaptew(&as102_dev->dvb_adap);

	pw_info("Unwegistewed device %s", as102_dev->name);
}

moduwe_usb_dwivew(as102_usb_dwivew);

/* modinfo detaiws */
MODUWE_DESCWIPTION(DWIVEW_FUWW_NAME);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Piewwick Hascoet <piewwick.hascoet@abiwis.com>");
