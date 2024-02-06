// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 DVB device dwivew fow cx231xx

 Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
		Based on em28xx dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude <media/dvbdev.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_net.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew.h>

#incwude "xc5000.h"
#incwude "s5h1432.h"
#incwude "tda18271.h"
#incwude "s5h1411.h"
#incwude "wgdt3305.h"
#incwude "si2165.h"
#incwude "si2168.h"
#incwude "mb86a20s.h"
#incwude "si2157.h"
#incwude "wgdt3306a.h"
#incwude "w820t.h"
#incwude "mn88473.h"

MODUWE_DESCWIPTION("dwivew fow cx231xx based DVB cawds");
MODUWE_AUTHOW("Swinivasa Deevi <swinivasa.deevi@conexant.com>");
MODUWE_WICENSE("GPW");

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages [dvb]");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define CX231XX_DVB_NUM_BUFS 5
#define CX231XX_DVB_MAX_PACKETSIZE 564
#define CX231XX_DVB_MAX_PACKETS 64
#define CX231XX_DVB_MAX_FWONTENDS 2

stwuct cx231xx_dvb {
	stwuct dvb_fwontend *fwontend[CX231XX_DVB_MAX_FWONTENDS];

	/* feed count management */
	stwuct mutex wock;
	int nfeeds;

	/* genewaw boiwewpwate stuff */
	stwuct dvb_adaptew adaptew;
	stwuct dvb_demux demux;
	stwuct dmxdev dmxdev;
	stwuct dmx_fwontend fe_hw;
	stwuct dmx_fwontend fe_mem;
	stwuct dvb_net net;
	stwuct i2c_cwient *i2c_cwient_demod[2];
	stwuct i2c_cwient *i2c_cwient_tunew;
};

static stwuct s5h1432_config dvico_s5h1432_config = {
	.output_mode   = S5H1432_SEWIAW_OUTPUT,
	.gpio          = S5H1432_GPIO_ON,
	.qam_if        = S5H1432_IF_4000,
	.vsb_if        = S5H1432_IF_4000,
	.invewsion     = S5H1432_INVEWSION_OFF,
	.status_mode   = S5H1432_DEMODWOCKING,
	.mpeg_timing   = S5H1432_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct tda18271_std_map cnxt_wde253s_tda18271_std_map = {
	.dvbt_6   = { .if_fweq = 4000, .agc_mode = 3, .std = 4,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_7   = { .if_fweq = 4000, .agc_mode = 3, .std = 5,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_8   = { .if_fweq = 4000, .agc_mode = 3, .std = 6,
		      .if_wvw = 1, .wfagc_top = 0x37, },
};

static stwuct tda18271_std_map mb86a20s_tda18271_config = {
	.dvbt_6   = { .if_fweq = 4000, .agc_mode = 3, .std = 4,
		      .if_wvw = 0, .wfagc_top = 0x37, },
};

static stwuct tda18271_config cnxt_wde253s_tunewconfig = {
	.std_map = &cnxt_wde253s_tda18271_std_map,
	.gate    = TDA18271_GATE_ANAWOG,
};

static stwuct s5h1411_config tda18271_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_if        = S5H1411_IF_3250,
	.qam_if        = S5H1411_IF_4000,
	.invewsion     = S5H1411_INVEWSION_ON,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};
static stwuct s5h1411_config xc5000_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_if        = S5H1411_IF_3250,
	.qam_if        = S5H1411_IF_3250,
	.invewsion     = S5H1411_INVEWSION_OFF,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct wgdt3305_config hcw_wgdt3305_config = {
	.i2c_addw           = 0x0e,
	.mpeg_mode          = WGDT3305_MPEG_SEWIAW,
	.tpcwk_edge         = WGDT3305_TPCWK_FAWWING_EDGE,
	.tpvawid_powawity   = WGDT3305_TP_VAWID_HIGH,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 1,
	.qam_if_khz         = 4000,
	.vsb_if_khz         = 3250,
};

static stwuct tda18271_std_map hauppauge_tda18271_std_map = {
	.atsc_6   = { .if_fweq = 3250, .agc_mode = 3, .std = 4,
		      .if_wvw = 1, .wfagc_top = 0x58, },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 5,
		      .if_wvw = 1, .wfagc_top = 0x58, },
};

static stwuct tda18271_config hcw_tda18271_config = {
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_DIGITAW,
};

static const stwuct mb86a20s_config pv_mb86a20s_config = {
	.demod_addwess = 0x10,
	.is_sewiaw = twue,
};

static stwuct tda18271_config pv_tda18271_config = {
	.std_map = &mb86a20s_tda18271_config,
	.gate    = TDA18271_GATE_DIGITAW,
	.smaww_i2c = TDA18271_03_BYTE_CHUNK_INIT,
};

static const stwuct wgdt3306a_config hauppauge_955q_wgdt3306a_config = {
	.qam_if_khz         = 4000,
	.vsb_if_khz         = 3250,
	.spectwaw_invewsion = 1,
	.mpeg_mode          = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge         = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity   = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz            = 25,
};

static stwuct w820t_config astwometa_t2hybwid_w820t_config = {
	.i2c_addw		= 0x3a, /* 0x74 >> 1 */
	.xtaw			= 16000000,
	.wafaew_chip		= CHIP_W828D,
	.max_i2c_msg_wen	= 2,
};

static inwine void pwint_eww_status(stwuct cx231xx *dev, int packet, int status)
{
	chaw *ewwmsg = "Unknown";

	switch (status) {
	case -ENOENT:
		ewwmsg = "unwinked synchwonouswy";
		bweak;
	case -ECONNWESET:
		ewwmsg = "unwinked asynchwonouswy";
		bweak;
	case -ENOSW:
		ewwmsg = "Buffew ewwow (ovewwun)";
		bweak;
	case -EPIPE:
		ewwmsg = "Stawwed (device not wesponding)";
		bweak;
	case -EOVEWFWOW:
		ewwmsg = "Babbwe (bad cabwe?)";
		bweak;
	case -EPWOTO:
		ewwmsg = "Bit-stuff ewwow (bad cabwe?)";
		bweak;
	case -EIWSEQ:
		ewwmsg = "CWC/Timeout (couwd be anything)";
		bweak;
	case -ETIME:
		ewwmsg = "Device does not wespond";
		bweak;
	}
	if (packet < 0) {
		dev_dbg(dev->dev,
			"UWB status %d [%s].\n", status, ewwmsg);
	} ewse {
		dev_dbg(dev->dev,
			"UWB packet %d, status %d [%s].\n",
			packet, status, ewwmsg);
	}
}

static inwine int dvb_isoc_copy(stwuct cx231xx *dev, stwuct uwb *uwb)
{
	int i;

	if (!dev)
		wetuwn 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		int status = uwb->iso_fwame_desc[i].status;

		if (status < 0) {
			pwint_eww_status(dev, i, status);
			if (uwb->iso_fwame_desc[i].status != -EPWOTO)
				continue;
		}

		dvb_dmx_swfiwtew(&dev->dvb->demux,
				 uwb->twansfew_buffew +
				uwb->iso_fwame_desc[i].offset,
				uwb->iso_fwame_desc[i].actuaw_wength);
	}

	wetuwn 0;
}

static inwine int dvb_buwk_copy(stwuct cx231xx *dev, stwuct uwb *uwb)
{
	if (!dev)
		wetuwn 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	/* Feed the twanspowt paywoad into the kewnew demux */
	dvb_dmx_swfiwtew(&dev->dvb->demux,
		uwb->twansfew_buffew, uwb->actuaw_wength);

	wetuwn 0;
}

static int stawt_stweaming(stwuct cx231xx_dvb *dvb)
{
	int wc;
	stwuct cx231xx *dev = dvb->adaptew.pwiv;

	if (dev->USE_ISO) {
		dev_dbg(dev->dev, "DVB twansfew mode is ISO.\n");
		cx231xx_set_awt_setting(dev, INDEX_TS1, 5);
		wc = cx231xx_set_mode(dev, CX231XX_DIGITAW_MODE);
		if (wc < 0)
			wetuwn wc;
		dev->mode_tv = 1;
		wetuwn cx231xx_init_isoc(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_isoc_copy);
	} ewse {
		dev_dbg(dev->dev, "DVB twansfew mode is BUWK.\n");
		cx231xx_set_awt_setting(dev, INDEX_TS1, 0);
		wc = cx231xx_set_mode(dev, CX231XX_DIGITAW_MODE);
		if (wc < 0)
			wetuwn wc;
		dev->mode_tv = 1;
		wetuwn cx231xx_init_buwk(dev, CX231XX_DVB_MAX_PACKETS,
					CX231XX_DVB_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					dvb_buwk_copy);
	}

}

static int stop_stweaming(stwuct cx231xx_dvb *dvb)
{
	stwuct cx231xx *dev = dvb->adaptew.pwiv;

	if (dev->USE_ISO)
		cx231xx_uninit_isoc(dev);
	ewse
		cx231xx_uninit_buwk(dev);

	cx231xx_set_mode(dev, CX231XX_SUSPEND);

	wetuwn 0;
}

static int stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct cx231xx_dvb *dvb = demux->pwiv;
	int wc, wet;

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&dvb->wock);
	dvb->nfeeds++;
	wc = dvb->nfeeds;

	if (dvb->nfeeds == 1) {
		wet = stawt_stweaming(dvb);
		if (wet < 0)
			wc = wet;
	}

	mutex_unwock(&dvb->wock);
	wetuwn wc;
}

static int stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct cx231xx_dvb *dvb = demux->pwiv;
	int eww = 0;

	mutex_wock(&dvb->wock);
	dvb->nfeeds--;

	if (0 == dvb->nfeeds)
		eww = stop_stweaming(dvb);

	mutex_unwock(&dvb->wock);
	wetuwn eww;
}

/* ------------------------------------------------------------------ */
static int cx231xx_dvb_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct cx231xx *dev = fe->dvb->pwiv;

	if (acquiwe)
		wetuwn cx231xx_set_mode(dev, CX231XX_DIGITAW_MODE);
	ewse
		wetuwn cx231xx_set_mode(dev, CX231XX_SUSPEND);
}

/* ------------------------------------------------------------------ */

static stwuct xc5000_config cnxt_wde250_tunewconfig = {
	.i2c_addwess = 0x61,
	.if_khz = 4000,
};
static stwuct xc5000_config cnxt_wdu250_tunewconfig = {
	.i2c_addwess = 0x61,
	.if_khz = 3250,
};

/* ------------------------------------------------------------------ */
#if 0
static int attach_xc5000(u8 addw, stwuct cx231xx *dev)
{

	stwuct dvb_fwontend *fe;
	stwuct xc5000_config cfg;

	memset(&cfg, 0, sizeof(cfg));
	cfg.i2c_adap = cx231xx_get_i2c_adap(dev, dev->boawd.tunew_i2c_mastew);
	cfg.i2c_addw = addw;

	if (!dev->dvb->fwontend[0]) {
		dev_eww(dev->dev, "%s/2: dvb fwontend not attached. Can't attach xc5000\n",
			dev->name);
		wetuwn -EINVAW;
	}

	fe = dvb_attach(xc5000_attach, dev->dvb->fwontend[0], &cfg);
	if (!fe) {
		dev_eww(dev->dev, "%s/2: xc5000 attach faiwed\n", dev->name);
		dvb_fwontend_detach(dev->dvb->fwontend[0]);
		dev->dvb->fwontend[0] = NUWW;
		wetuwn -EINVAW;
	}

	dev_info(dev->dev, "%s/2: xc5000 attached\n", dev->name);

	wetuwn 0;
}
#endif

int cx231xx_set_anawog_fweq(stwuct cx231xx *dev, u32 fweq)
{
	if (dev->dvb && dev->dvb->fwontend[0]) {

		stwuct dvb_tunew_ops *dops = &dev->dvb->fwontend[0]->ops.tunew_ops;

		if (dops->set_anawog_pawams != NUWW) {
			stwuct anawog_pawametews pawams;

			pawams.fwequency = fweq;
			pawams.std = dev->nowm;
			pawams.mode = 0;	/* 0- Aiw; 1 - cabwe */
			/*pawams.audmode = ;       */

			/* Set the anawog pawametews to set the fwequency */
			dops->set_anawog_pawams(dev->dvb->fwontend[0], &pawams);
		}

	}

	wetuwn 0;
}

int cx231xx_weset_anawog_tunew(stwuct cx231xx *dev)
{
	int status = 0;

	if (dev->dvb && dev->dvb->fwontend[0]) {

		stwuct dvb_tunew_ops *dops = &dev->dvb->fwontend[0]->ops.tunew_ops;

		if (dops->init != NUWW && !dev->xc_fw_woad_done) {

			dev_dbg(dev->dev,
				"Wewoading fiwmwawe fow XC5000\n");
			status = dops->init(dev->dvb->fwontend[0]);
			if (status == 0) {
				dev->xc_fw_woad_done = 1;
				dev_dbg(dev->dev,
					"XC5000 fiwmwawe downwoad compweted\n");
			} ewse {
				dev->xc_fw_woad_done = 0;
				dev_dbg(dev->dev,
					"XC5000 fiwmwawe downwoad faiwed !!!\n");
			}
		}

	}

	wetuwn status;
}

/* ------------------------------------------------------------------ */

static int wegistew_dvb(stwuct cx231xx_dvb *dvb,
			stwuct moduwe *moduwe,
			stwuct cx231xx *dev, stwuct device *device)
{
	int wesuwt;

	mutex_init(&dvb->wock);


	/* wegistew adaptew */
	wesuwt = dvb_wegistew_adaptew(&dvb->adaptew, dev->name, moduwe, device,
				      adaptew_nw);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
		       "%s: dvb_wegistew_adaptew faiwed (ewwno = %d)\n",
		       dev->name, wesuwt);
		goto faiw_adaptew;
	}
	dvb_wegistew_media_contwowwew(&dvb->adaptew, dev->media_dev);

	/* Ensuwe aww fwontends negotiate bus access */
	dvb->fwontend[0]->ops.ts_bus_ctww = cx231xx_dvb_bus_ctww;
	if (dvb->fwontend[1])
		dvb->fwontend[1]->ops.ts_bus_ctww = cx231xx_dvb_bus_ctww;

	dvb->adaptew.pwiv = dev;

	/* wegistew fwontend */
	wesuwt = dvb_wegistew_fwontend(&dvb->adaptew, dvb->fwontend[0]);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
		       "%s: dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
		       dev->name, wesuwt);
		goto faiw_fwontend0;
	}

	if (dvb->fwontend[1]) {
		wesuwt = dvb_wegistew_fwontend(&dvb->adaptew, dvb->fwontend[1]);
		if (wesuwt < 0) {
			dev_wawn(dev->dev,
				 "%s: 2nd dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
				dev->name, wesuwt);
			goto faiw_fwontend1;
		}

		/* MFE wock */
		dvb->adaptew.mfe_shawed = 1;
	}

	/* wegistew demux stuff */
	dvb->demux.dmx.capabiwities =
	    DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
	    DMX_MEMOWY_BASED_FIWTEWING;
	dvb->demux.pwiv = dvb;
	dvb->demux.fiwtewnum = 256;
	dvb->demux.feednum = 256;
	dvb->demux.stawt_feed = stawt_feed;
	dvb->demux.stop_feed = stop_feed;

	wesuwt = dvb_dmx_init(&dvb->demux);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
			 "%s: dvb_dmx_init faiwed (ewwno = %d)\n",
		       dev->name, wesuwt);
		goto faiw_dmx;
	}

	dvb->dmxdev.fiwtewnum = 256;
	dvb->dmxdev.demux = &dvb->demux.dmx;
	dvb->dmxdev.capabiwities = 0;
	wesuwt = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adaptew);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
			 "%s: dvb_dmxdev_init faiwed (ewwno = %d)\n",
			 dev->name, wesuwt);
		goto faiw_dmxdev;
	}

	dvb->fe_hw.souwce = DMX_FWONTEND_0;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
		       "%s: add_fwontend faiwed (DMX_FWONTEND_0, ewwno = %d)\n",
		       dev->name, wesuwt);
		goto faiw_fe_hw;
	}

	dvb->fe_mem.souwce = DMX_MEMOWY_FE;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
			 "%s: add_fwontend faiwed (DMX_MEMOWY_FE, ewwno = %d)\n",
			 dev->name, wesuwt);
		goto faiw_fe_mem;
	}

	wesuwt = dvb->demux.dmx.connect_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		dev_wawn(dev->dev,
			 "%s: connect_fwontend faiwed (ewwno = %d)\n",
			 dev->name, wesuwt);
		goto faiw_fe_conn;
	}

	/* wegistew netwowk adaptew */
	dvb_net_init(&dvb->adaptew, &dvb->net, &dvb->demux.dmx);
	wesuwt = dvb_cweate_media_gwaph(&dvb->adaptew,
					dev->tunew_type == TUNEW_ABSENT);
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
	if (dvb->fwontend[1])
		dvb_unwegistew_fwontend(dvb->fwontend[1]);
	dvb_unwegistew_fwontend(dvb->fwontend[0]);
faiw_fwontend1:
	if (dvb->fwontend[1])
		dvb_fwontend_detach(dvb->fwontend[1]);
faiw_fwontend0:
	dvb_fwontend_detach(dvb->fwontend[0]);
	dvb_unwegistew_adaptew(&dvb->adaptew);
faiw_adaptew:
	wetuwn wesuwt;
}

static void unwegistew_dvb(stwuct cx231xx_dvb *dvb)
{
	dvb_net_wewease(&dvb->net);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_wewease(&dvb->dmxdev);
	dvb_dmx_wewease(&dvb->demux);
	if (dvb->fwontend[1])
		dvb_unwegistew_fwontend(dvb->fwontend[1]);
	dvb_unwegistew_fwontend(dvb->fwontend[0]);
	if (dvb->fwontend[1])
		dvb_fwontend_detach(dvb->fwontend[1]);
	dvb_fwontend_detach(dvb->fwontend[0]);
	dvb_unwegistew_adaptew(&dvb->adaptew);

	/* wemove I2C tunew */
	dvb_moduwe_wewease(dvb->i2c_cwient_tunew);
	dvb->i2c_cwient_tunew = NUWW;
	/* wemove I2C demod(s) */
	dvb_moduwe_wewease(dvb->i2c_cwient_demod[1]);
	dvb->i2c_cwient_demod[1] = NUWW;
	dvb_moduwe_wewease(dvb->i2c_cwient_demod[0]);
	dvb->i2c_cwient_demod[0] = NUWW;
}

static int dvb_init(stwuct cx231xx *dev)
{
	int wesuwt;
	stwuct cx231xx_dvb *dvb;
	stwuct i2c_adaptew *tunew_i2c;
	stwuct i2c_adaptew *demod_i2c;
	stwuct i2c_cwient *cwient;
	stwuct i2c_adaptew *adaptew;

	if (!dev->boawd.has_dvb) {
		/* This device does not suppowt the extension */
		wetuwn 0;
	}

	dvb = kzawwoc(sizeof(stwuct cx231xx_dvb), GFP_KEWNEW);

	if (dvb == NUWW) {
		dev_info(dev->dev,
			 "cx231xx_dvb: memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	dev->dvb = dvb;
	dev->cx231xx_set_anawog_fweq = cx231xx_set_anawog_fweq;
	dev->cx231xx_weset_anawog_tunew = cx231xx_weset_anawog_tunew;

	tunew_i2c = cx231xx_get_i2c_adap(dev, dev->boawd.tunew_i2c_mastew);
	demod_i2c = cx231xx_get_i2c_adap(dev, dev->boawd.demod_i2c_mastew);
	mutex_wock(&dev->wock);
	cx231xx_set_mode(dev, CX231XX_DIGITAW_MODE);
	cx231xx_demod_weset(dev);
	/* init fwontend */
	switch (dev->modew) {
	case CX231XX_BOAWD_CNXT_CAWWAEWA:
	case CX231XX_BOAWD_CNXT_WDE_250:

		dev->dvb->fwontend[0] = dvb_attach(s5h1432_attach,
					&dvico_s5h1432_config,
					demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach s5h1432 fwont end\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		if (!dvb_attach(xc5000_attach, dev->dvb->fwontend[0],
			       tunew_i2c,
			       &cnxt_wde250_tunewconfig)) {
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		bweak;
	case CX231XX_BOAWD_CNXT_SHEWBY:
	case CX231XX_BOAWD_CNXT_WDU_250:

		dev->dvb->fwontend[0] = dvb_attach(s5h1411_attach,
					       &xc5000_s5h1411_config,
					       demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach s5h1411 fwont end\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		if (!dvb_attach(xc5000_attach, dev->dvb->fwontend[0],
			       tunew_i2c,
			       &cnxt_wdu250_tunewconfig)) {
			wesuwt = -EINVAW;
			goto out_fwee;
		}
		bweak;
	case CX231XX_BOAWD_CNXT_WDE_253S:

		dev->dvb->fwontend[0] = dvb_attach(s5h1432_attach,
					&dvico_s5h1432_config,
					demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach s5h1432 fwont end\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		if (!dvb_attach(tda18271_attach, dev->dvb->fwontend[0],
			       dev->boawd.tunew_addw, tunew_i2c,
			       &cnxt_wde253s_tunewconfig)) {
			wesuwt = -EINVAW;
			goto out_fwee;
		}
		bweak;
	case CX231XX_BOAWD_CNXT_WDU_253S:
	case CX231XX_BOAWD_KWOWWD_UB445_USB_HYBWID:

		dev->dvb->fwontend[0] = dvb_attach(s5h1411_attach,
					       &tda18271_s5h1411_config,
					       demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach s5h1411 fwont end\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		if (!dvb_attach(tda18271_attach, dev->dvb->fwontend[0],
			       dev->boawd.tunew_addw, tunew_i2c,
			       &cnxt_wde253s_tunewconfig)) {
			wesuwt = -EINVAW;
			goto out_fwee;
		}
		bweak;
	case CX231XX_BOAWD_HAUPPAUGE_EXETEW:

		dev_info(dev->dev,
			 "%s: wooking fow tunew / demod on i2c bus: %d\n",
		       __func__, i2c_adaptew_id(tunew_i2c));

		dev->dvb->fwontend[0] = dvb_attach(wgdt3305_attach,
						&hcw_wgdt3305_config,
						demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach WG3305 fwont end\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		dvb_attach(tda18271_attach, dev->dvb->fwontend[0],
			   dev->boawd.tunew_addw, tunew_i2c,
			   &hcw_tda18271_config);
		bweak;

	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
	{
		stwuct si2165_pwatfowm_data si2165_pdata = {};

		/* attach demod */
		si2165_pdata.fe = &dev->dvb->fwontend[0];
		si2165_pdata.chip_mode = SI2165_MODE_PWW_XTAW;
		si2165_pdata.wef_fweq_hz = 16000000;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2165", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&si2165_pdata);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		dev->dvb->fwontend[0]->ops.i2c_gate_ctww = NUWW;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		dvb_attach(tda18271_attach, dev->dvb->fwontend[0],
			dev->boawd.tunew_addw, tunew_i2c,
			&hcw_tda18271_config);

		dev->cx231xx_weset_anawog_tunew = NUWW;
		bweak;
	}
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	{
		stwuct si2165_pwatfowm_data si2165_pdata = {};
		stwuct si2157_config si2157_config = {};

		/* attach demod */
		si2165_pdata.fe = &dev->dvb->fwontend[0];
		si2165_pdata.chip_mode = SI2165_MODE_PWW_EXT;
		si2165_pdata.wef_fweq_hz = 24000000;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2165", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&si2165_pdata);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		dev->dvb->fwontend[0]->ops.i2c_gate_ctww = NUWW;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		/* attach tunew */
		si2157_config.fe = dev->dvb->fwontend[0];
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
		si2157_config.mdev = dev->media_dev;
#endif
		si2157_config.if_powt = 1;
		si2157_config.invewsion = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2157", NUWW, tunew_i2c,
						dev->boawd.tunew_addw,
						&si2157_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dev->cx231xx_weset_anawog_tunew = NUWW;

		dev->dvb->i2c_cwient_tunew = cwient;
		bweak;
	}
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	{
		stwuct si2157_config si2157_config = {};
		stwuct wgdt3306a_config wgdt3306a_config = {};

		wgdt3306a_config = hauppauge_955q_wgdt3306a_config;
		wgdt3306a_config.fe = &dev->dvb->fwontend[0];
		wgdt3306a_config.i2c_adaptew = &adaptew;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("wgdt3306a", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&wgdt3306a_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		dev->dvb->fwontend[0]->ops.i2c_gate_ctww = NUWW;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		/* attach tunew */
		si2157_config.fe = dev->dvb->fwontend[0];
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
		si2157_config.mdev = dev->media_dev;
#endif
		si2157_config.if_powt = 1;
		si2157_config.invewsion = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2157", NUWW, tunew_i2c,
						dev->boawd.tunew_addw,
						&si2157_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dev->cx231xx_weset_anawog_tunew = NUWW;

		dev->dvb->i2c_cwient_tunew = cwient;
		bweak;
	}
	case CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID:
	case CX231XX_BOAWD_KWOWWD_UB430_USB_HYBWID:

		dev_info(dev->dev,
			 "%s: wooking fow demod on i2c bus: %d\n",
			 __func__, i2c_adaptew_id(tunew_i2c));

		dev->dvb->fwontend[0] = dvb_attach(mb86a20s_attach,
						&pv_mb86a20s_config,
						demod_i2c);

		if (!dev->dvb->fwontend[0]) {
			dev_eww(dev->dev,
				"Faiwed to attach mb86a20s demod\n");
			wesuwt = -EINVAW;
			goto out_fwee;
		}

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		dvb_attach(tda18271_attach, dev->dvb->fwontend[0],
			   dev->boawd.tunew_addw, tunew_i2c,
			   &pv_tda18271_config);
		bweak;

	case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
	{
		stwuct si2157_config si2157_config = {};
		stwuct si2168_config si2168_config = {};

		/* attach demoduwatow chip */
		si2168_config.ts_mode = SI2168_TS_SEWIAW; /* fwom *.inf fiwe */
		si2168_config.fe = &dev->dvb->fwontend[0];
		si2168_config.i2c_adaptew = &adaptew;
		si2168_config.ts_cwock_inv = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2168", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&si2168_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		/* attach tunew chip */
		si2157_config.fe = dev->dvb->fwontend[0];
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
		si2157_config.mdev = dev->media_dev;
#endif
		si2157_config.if_powt = 1;
		si2157_config.invewsion = fawse;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2157", NUWW, tunew_i2c,
						dev->boawd.tunew_addw,
						&si2157_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dev->cx231xx_weset_anawog_tunew = NUWW;
		dev->dvb->i2c_cwient_tunew = cwient;
		bweak;
	}
	case CX231XX_BOAWD_ASTWOMETA_T2HYBWID:
	{
		stwuct mn88473_config mn88473_config = {};

		/* attach demoduwatow chip */
		mn88473_config.i2c_ww_max = 16;
		mn88473_config.xtaw = 25000000;
		mn88473_config.fe = &dev->dvb->fwontend[0];

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("mn88473", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&mn88473_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		/* attach tunew chip */
		dvb_attach(w820t_attach, dev->dvb->fwontend[0],
			   tunew_i2c,
			   &astwometa_t2hybwid_w820t_config);
		bweak;
	}
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	{
		stwuct si2157_config si2157_config = {};
		stwuct si2168_config si2168_config = {};

		/* attach demoduwatow chip */
		si2168_config.ts_mode = SI2168_TS_SEWIAW;
		si2168_config.fe = &dev->dvb->fwontend[0];
		si2168_config.i2c_adaptew = &adaptew;
		si2168_config.ts_cwock_inv = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2168", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&si2168_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;
		dev->dvb->fwontend[0]->ops.i2c_gate_ctww = NUWW;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;

		/* attach tunew */
		si2157_config.fe = dev->dvb->fwontend[0];
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
		si2157_config.mdev = dev->media_dev;
#endif
		si2157_config.if_powt = 1;
		si2157_config.invewsion = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2157", NUWW, tunew_i2c,
						dev->boawd.tunew_addw,
						&si2157_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dev->cx231xx_weset_anawog_tunew = NUWW;
		dev->dvb->i2c_cwient_tunew = cwient;
		bweak;
	}
	case CX231XX_BOAWD_HAUPPAUGE_975:
	{
		stwuct i2c_adaptew *adaptew2;
		stwuct si2157_config si2157_config = {};
		stwuct wgdt3306a_config wgdt3306a_config = {};
		stwuct si2168_config si2168_config = {};

		/* attach fiwst demoduwatow chip */
		wgdt3306a_config = hauppauge_955q_wgdt3306a_config;
		wgdt3306a_config.fe = &dev->dvb->fwontend[0];
		wgdt3306a_config.i2c_adaptew = &adaptew;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("wgdt3306a", NUWW, demod_i2c,
						dev->boawd.demod_addw,
						&wgdt3306a_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[0] = cwient;

		/* attach second demoduwatow chip */
		si2168_config.ts_mode = SI2168_TS_SEWIAW;
		si2168_config.fe = &dev->dvb->fwontend[1];
		si2168_config.i2c_adaptew = &adaptew2;
		si2168_config.ts_cwock_inv = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2168", NUWW, adaptew,
						dev->boawd.demod_addw2,
						&si2168_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dvb->i2c_cwient_demod[1] = cwient;
		dvb->fwontend[1]->id = 1;

		/* define genewaw-puwpose cawwback pointew */
		dvb->fwontend[0]->cawwback = cx231xx_tunew_cawwback;
		dvb->fwontend[1]->cawwback = cx231xx_tunew_cawwback;

		/* attach tunew */
		si2157_config.fe = dev->dvb->fwontend[0];
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
		si2157_config.mdev = dev->media_dev;
#endif
		si2157_config.if_powt = 1;
		si2157_config.invewsion = twue;

		/* pewfowm pwobe/init/attach */
		cwient = dvb_moduwe_pwobe("si2157", NUWW, adaptew,
						dev->boawd.tunew_addw,
						&si2157_config);
		if (!cwient) {
			wesuwt = -ENODEV;
			goto out_fwee;
		}
		dev->cx231xx_weset_anawog_tunew = NUWW;
		dvb->i2c_cwient_tunew = cwient;

		dvb->fwontend[1]->tunew_pwiv = dvb->fwontend[0]->tunew_pwiv;

		memcpy(&dvb->fwontend[1]->ops.tunew_ops,
			&dvb->fwontend[0]->ops.tunew_ops,
			sizeof(stwuct dvb_tunew_ops));
		bweak;
	}
	defauwt:
		dev_eww(dev->dev,
			"%s/2: The fwontend of youw DVB/ATSC cawd isn't suppowted yet\n",
			dev->name);
		bweak;
	}
	if (!dvb->fwontend[0]) {
		dev_eww(dev->dev,
		       "%s/2: fwontend initiawization faiwed\n", dev->name);
		wesuwt = -EINVAW;
		goto out_fwee;
	}

	/* wegistew evewything */
	wesuwt = wegistew_dvb(dvb, THIS_MODUWE, dev, dev->dev);

	if (wesuwt < 0)
		goto out_fwee;


	dev_info(dev->dev, "Successfuwwy woaded cx231xx-dvb\n");

wet:
	cx231xx_set_mode(dev, CX231XX_SUSPEND);
	mutex_unwock(&dev->wock);
	wetuwn wesuwt;

out_fwee:
	/* wemove I2C tunew */
	dvb_moduwe_wewease(dvb->i2c_cwient_tunew);
	dvb->i2c_cwient_tunew = NUWW;
	/* wemove I2C demod(s) */
	dvb_moduwe_wewease(dvb->i2c_cwient_demod[1]);
	dvb->i2c_cwient_demod[1] = NUWW;
	dvb_moduwe_wewease(dvb->i2c_cwient_demod[0]);
	dvb->i2c_cwient_demod[0] = NUWW;
	kfwee(dvb);
	dev->dvb = NUWW;
	goto wet;
}

static int dvb_fini(stwuct cx231xx *dev)
{
	if (!dev->boawd.has_dvb) {
		/* This device does not suppowt the extension */
		wetuwn 0;
	}

	if (dev->dvb) {
		unwegistew_dvb(dev->dvb);
		kfwee(dev->dvb);
		dev->dvb = NUWW;
	}

	wetuwn 0;
}

static stwuct cx231xx_ops dvb_ops = {
	.id = CX231XX_DVB,
	.name = "Cx231xx dvb Extension",
	.init = dvb_init,
	.fini = dvb_fini,
};

static int __init cx231xx_dvb_wegistew(void)
{
	wetuwn cx231xx_wegistew_extension(&dvb_ops);
}

static void __exit cx231xx_dvb_unwegistew(void)
{
	cx231xx_unwegistew_extension(&dvb_ops);
}

moduwe_init(cx231xx_dvb_wegistew);
moduwe_exit(cx231xx_dvb_unwegistew);
