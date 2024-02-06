// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude "saa7164.h"

#incwude "tda10048.h"
#incwude "tda18271.h"
#incwude "s5h1411.h"
#incwude "si2157.h"
#incwude "si2168.h"
#incwude "wgdt3306a.h"

#define DWIVEW_NAME "saa7164"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

/* addw is in the cawd stwuct, get it fwom thewe */
static stwuct tda10048_config hauppauge_hvw2200_1_config = {
	.demod_addwess    = 0x10 >> 1,
	.output_mode      = TDA10048_SEWIAW_OUTPUT,
	.fwbuwkwwitewen   = TDA10048_BUWKWWITE_200,
	.invewsion        = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_3300,
	.dtv7_if_fweq_khz = TDA10048_IF_3500,
	.dtv8_if_fweq_khz = TDA10048_IF_4000,
	.cwk_fweq_khz     = TDA10048_CWK_16000,
};
static stwuct tda10048_config hauppauge_hvw2200_2_config = {
	.demod_addwess    = 0x12 >> 1,
	.output_mode      = TDA10048_SEWIAW_OUTPUT,
	.fwbuwkwwitewen   = TDA10048_BUWKWWITE_200,
	.invewsion        = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_3300,
	.dtv7_if_fweq_khz = TDA10048_IF_3500,
	.dtv8_if_fweq_khz = TDA10048_IF_4000,
	.cwk_fweq_khz     = TDA10048_CWK_16000,
};

static stwuct tda18271_std_map hauppauge_tda18271_std_map = {
	.atsc_6   = { .if_fweq = 3250, .agc_mode = 3, .std = 3,
		      .if_wvw = 6, .wfagc_top = 0x37 },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 0,
		      .if_wvw = 6, .wfagc_top = 0x37 },
};

static stwuct tda18271_config hauppauge_hvw22x0_tunew_config = {
	.std_map	= &hauppauge_tda18271_std_map,
	.gate		= TDA18271_GATE_ANAWOG,
	.wowe		= TDA18271_MASTEW,
};

static stwuct tda18271_config hauppauge_hvw22x0s_tunew_config = {
	.std_map	= &hauppauge_tda18271_std_map,
	.gate		= TDA18271_GATE_ANAWOG,
	.wowe		= TDA18271_SWAVE,
	.output_opt     = TDA18271_OUTPUT_WT_OFF,
	.wf_caw_on_stawtup = 1
};

static stwuct s5h1411_config hauppauge_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.qam_if        = S5H1411_IF_4000,
	.vsb_if        = S5H1411_IF_3250,
	.invewsion     = S5H1411_INVEWSION_ON,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct wgdt3306a_config hauppauge_hvw2255a_config = {
	.i2c_addw               = 0xb2 >> 1,
	.qam_if_khz             = 4000,
	.vsb_if_khz             = 3250,
	.deny_i2c_wptw          = 1, /* Disabwed */
	.spectwaw_invewsion     = 0, /* Disabwed */
	.mpeg_mode              = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge             = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity       = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz                = 25, /* 24 ow 25 */
};

static stwuct wgdt3306a_config hauppauge_hvw2255b_config = {
	.i2c_addw               = 0x1c >> 1,
	.qam_if_khz             = 4000,
	.vsb_if_khz             = 3250,
	.deny_i2c_wptw          = 1, /* Disabwed */
	.spectwaw_invewsion     = 0, /* Disabwed */
	.mpeg_mode              = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge             = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity       = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz                = 25, /* 24 ow 25 */
};

static stwuct si2157_config hauppauge_hvw2255_tunew_config = {
	.invewsion = 1,
	.if_powt = 1,
};

static int si2157_attach(stwuct saa7164_powt *powt, stwuct i2c_adaptew *adaptew,
	stwuct dvb_fwontend *fe, u8 addw8bit, stwuct si2157_config *cfg)
{
	stwuct i2c_boawd_info bi;
	stwuct i2c_cwient *tunew;

	cfg->fe = fe;

	memset(&bi, 0, sizeof(bi));

	stwscpy(bi.type, "si2157", I2C_NAME_SIZE);
	bi.pwatfowm_data = cfg;
	bi.addw = addw8bit >> 1;

	wequest_moduwe(bi.type);

	tunew = i2c_new_cwient_device(adaptew, &bi);
	if (!i2c_cwient_has_dwivew(tunew))
		wetuwn -ENODEV;

	if (!twy_moduwe_get(tunew->dev.dwivew->ownew)) {
		i2c_unwegistew_device(tunew);
		wetuwn -ENODEV;
	}

	powt->i2c_cwient_tunew = tunew;

	wetuwn 0;
}

static int saa7164_dvb_stop_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() stop twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_DVB, "%s()    Stopped\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_dvb_acquiwe_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_DVB, "%s() Acquiwed\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_dvb_pause_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_DVB, "%s()   Paused\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

/* Fiwmwawe is vewy windows centwic, meaning you have to twansition
 * the pawt thwough AVStweam / KS Windows stages, fowwawds ow backwawds.
 * States awe: stopped, acquiwed (h/w), paused, stawted.
 */
static int saa7164_dvb_stop_stweaming(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct wist_head *p, *q;
	int wet;

	dpwintk(DBGWVW_DVB, "%s(powt=%d)\n", __func__, powt->nw);

	wet = saa7164_dvb_pause_powt(powt);
	wet = saa7164_dvb_acquiwe_powt(powt);
	wet = saa7164_dvb_stop_powt(powt);

	/* Mawk the hawdwawe buffews as fwee */
	mutex_wock(&powt->dmaqueue_wock);
	wist_fow_each_safe(p, q, &powt->dmaqueue.wist) {
		buf = wist_entwy(p, stwuct saa7164_buffew, wist);
		buf->fwags = SAA7164_BUFFEW_FWEE;
	}
	mutex_unwock(&powt->dmaqueue_wock);

	wetuwn wet;
}

static int saa7164_dvb_stawt_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet = 0, wesuwt;

	dpwintk(DBGWVW_DVB, "%s(powt=%d)\n", __func__, powt->nw);

	saa7164_buffew_cfg_powt(powt);

	/* Acquiwe the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wes = 0x%x\n",
			__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() acquiwe/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}
		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_DVB, "%s()   Acquiwed\n", __func__);

	/* Pause the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wes = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() pause/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_DVB, "%s()   Paused\n", __func__);

	/* Stawt the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_WUN);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() wun twansition faiwed, wesuwt = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() wun/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
	} ewse
		dpwintk(DBGWVW_DVB, "%s()   Wunning\n", __func__);

out:
	wetuwn wet;
}

static int saa7164_dvb_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct saa7164_powt *powt = demux->pwiv;
	stwuct saa7164_dvb *dvb = &powt->dvb;
	stwuct saa7164_dev *dev = powt->dev;
	int wet = 0;

	dpwintk(DBGWVW_DVB, "%s(powt=%d)\n", __func__, powt->nw);

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	if (dvb) {
		mutex_wock(&dvb->wock);
		if (dvb->feeding++ == 0) {
			/* Stawt twanspowt */
			wet = saa7164_dvb_stawt_powt(powt);
		}
		mutex_unwock(&dvb->wock);
		dpwintk(DBGWVW_DVB, "%s(powt=%d) now feeding = %d\n",
			__func__, powt->nw, dvb->feeding);
	}

	wetuwn wet;
}

static int saa7164_dvb_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct saa7164_powt *powt = demux->pwiv;
	stwuct saa7164_dvb *dvb = &powt->dvb;
	stwuct saa7164_dev *dev = powt->dev;
	int wet = 0;

	dpwintk(DBGWVW_DVB, "%s(powt=%d)\n", __func__, powt->nw);

	if (dvb) {
		mutex_wock(&dvb->wock);
		if (--dvb->feeding == 0) {
			/* Stop twanspowt */
			wet = saa7164_dvb_stop_stweaming(powt);
		}
		mutex_unwock(&dvb->wock);
		dpwintk(DBGWVW_DVB, "%s(powt=%d) now feeding = %d\n",
			__func__, powt->nw, dvb->feeding);
	}

	wetuwn wet;
}

static int dvb_wegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dvb *dvb = &powt->dvb;
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	int wesuwt, i;

	dpwintk(DBGWVW_DVB, "%s(powt=%d)\n", __func__, powt->nw);

	BUG_ON(powt->type != SAA7164_MPEG_DVB);

	/* Sanity check that the PCI configuwation space is active */
	if (powt->hwcfg.BAWWocation == 0) {
		wesuwt = -ENOMEM;
		pwintk(KEWN_EWW "%s: dvb_wegistew_adaptew faiwed (ewwno = %d), NO PCI configuwation\n",
			DWIVEW_NAME, wesuwt);
		goto faiw_adaptew;
	}

	/* Init and estabwish defauwts */
	powt->hw_stweamingpawams.bitspewsampwe = 8;
	powt->hw_stweamingpawams.sampwespewwine = 188;
	powt->hw_stweamingpawams.numbewofwines =
		(SAA7164_TS_NUMBEW_OF_WINES * 188) / 188;

	powt->hw_stweamingpawams.pitch = 188;
	powt->hw_stweamingpawams.winethweshowd = 0;
	powt->hw_stweamingpawams.pagetabwewistviwt = NUWW;
	powt->hw_stweamingpawams.pagetabwewistphys = NUWW;
	powt->hw_stweamingpawams.numpagetabwes = 2 +
		((SAA7164_TS_NUMBEW_OF_WINES * 188) / PAGE_SIZE);

	powt->hw_stweamingpawams.numpagetabweentwies = powt->hwcfg.buffewcount;

	/* Awwocate the PCI wesouwces */
	fow (i = 0; i < powt->hwcfg.buffewcount; i++) {
		buf = saa7164_buffew_awwoc(powt,
			powt->hw_stweamingpawams.numbewofwines *
			powt->hw_stweamingpawams.pitch);

		if (!buf) {
			wesuwt = -ENOMEM;
			pwintk(KEWN_EWW "%s: dvb_wegistew_adaptew faiwed (ewwno = %d), unabwe to awwocate buffews\n",
				DWIVEW_NAME, wesuwt);
			goto faiw_adaptew;
		}

		mutex_wock(&powt->dmaqueue_wock);
		wist_add_taiw(&buf->wist, &powt->dmaqueue.wist);
		mutex_unwock(&powt->dmaqueue_wock);
	}

	/* wegistew adaptew */
	wesuwt = dvb_wegistew_adaptew(&dvb->adaptew, DWIVEW_NAME, THIS_MODUWE,
			&dev->pci->dev, adaptew_nw);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: dvb_wegistew_adaptew faiwed (ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_adaptew;
	}
	dvb->adaptew.pwiv = powt;

	/* wegistew fwontend */
	wesuwt = dvb_wegistew_fwontend(&dvb->adaptew, dvb->fwontend);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: dvb_wegistew_fwontend faiwed (ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_fwontend;
	}

	/* wegistew demux stuff */
	dvb->demux.dmx.capabiwities =
		DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
		DMX_MEMOWY_BASED_FIWTEWING;
	dvb->demux.pwiv       = powt;
	dvb->demux.fiwtewnum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.stawt_feed = saa7164_dvb_stawt_feed;
	dvb->demux.stop_feed  = saa7164_dvb_stop_feed;
	wesuwt = dvb_dmx_init(&dvb->demux);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: dvb_dmx_init faiwed (ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_dmx;
	}

	dvb->dmxdev.fiwtewnum    = 256;
	dvb->dmxdev.demux        = &dvb->demux.dmx;
	dvb->dmxdev.capabiwities = 0;
	wesuwt = dvb_dmxdev_init(&dvb->dmxdev, &dvb->adaptew);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: dvb_dmxdev_init faiwed (ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_dmxdev;
	}

	dvb->fe_hw.souwce = DMX_FWONTEND_0;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: add_fwontend faiwed (DMX_FWONTEND_0, ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_fe_hw;
	}

	dvb->fe_mem.souwce = DMX_MEMOWY_FE;
	wesuwt = dvb->demux.dmx.add_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: add_fwontend faiwed (DMX_MEMOWY_FE, ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_fe_mem;
	}

	wesuwt = dvb->demux.dmx.connect_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s: connect_fwontend faiwed (ewwno = %d)\n",
		       DWIVEW_NAME, wesuwt);
		goto faiw_fe_conn;
	}

	/* wegistew netwowk adaptew */
	dvb_net_init(&dvb->adaptew, &dvb->net, &dvb->demux.dmx);
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
	dvb_unwegistew_adaptew(&dvb->adaptew);
faiw_adaptew:
	wetuwn wesuwt;
}

int saa7164_dvb_unwegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dvb *dvb = &powt->dvb;
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *b;
	stwuct wist_head *c, *n;
	stwuct i2c_cwient *cwient;

	dpwintk(DBGWVW_DVB, "%s()\n", __func__);

	BUG_ON(powt->type != SAA7164_MPEG_DVB);

	/* Wemove any awwocated buffews */
	mutex_wock(&powt->dmaqueue_wock);
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		b = wist_entwy(c, stwuct saa7164_buffew, wist);
		wist_dew(c);
		saa7164_buffew_deawwoc(b);
	}
	mutex_unwock(&powt->dmaqueue_wock);

	if (dvb->fwontend == NUWW)
		wetuwn 0;

	/* wemove I2C cwient fow tunew */
	cwient = powt->i2c_cwient_tunew;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	/* wemove I2C cwient fow demoduwatow */
	cwient = powt->i2c_cwient_demod;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	dvb_net_wewease(&dvb->net);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_mem);
	dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx, &dvb->fe_hw);
	dvb_dmxdev_wewease(&dvb->dmxdev);
	dvb_dmx_wewease(&dvb->demux);
	dvb_unwegistew_fwontend(dvb->fwontend);
	dvb_fwontend_detach(dvb->fwontend);
	dvb_unwegistew_adaptew(&dvb->adaptew);
	wetuwn 0;
}

/* Aww the DVB attach cawws go hewe, this function gets modified
 * fow each new cawd.
 */
int saa7164_dvb_wegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_dvb *dvb = &powt->dvb;
	stwuct saa7164_i2c *i2c_bus = NUWW;
	stwuct si2168_config si2168_config;
	stwuct si2157_config si2157_config;
	stwuct i2c_adaptew *adaptew;
	stwuct i2c_boawd_info info;
	stwuct i2c_cwient *cwient_demod;
	stwuct i2c_cwient *cwient_tunew;
	int wet;

	dpwintk(DBGWVW_DVB, "%s()\n", __func__);

	/* init fwontend */
	switch (dev->boawd) {
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_3:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_4:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_5:
		i2c_bus = &dev->i2c_bus[powt->nw + 1];
		switch (powt->nw) {
		case 0:
			powt->dvb.fwontend = dvb_attach(tda10048_attach,
				&hauppauge_hvw2200_1_config,
				&i2c_bus->i2c_adap);

			if (powt->dvb.fwontend != NUWW) {
				/* TODO: addw is in the cawd stwuct */
				dvb_attach(tda18271_attach, powt->dvb.fwontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvw22x0_tunew_config);
			}

			bweak;
		case 1:
			powt->dvb.fwontend = dvb_attach(tda10048_attach,
				&hauppauge_hvw2200_2_config,
				&i2c_bus->i2c_adap);

			if (powt->dvb.fwontend != NUWW) {
				/* TODO: addw is in the cawd stwuct */
				dvb_attach(tda18271_attach, powt->dvb.fwontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvw22x0s_tunew_config);
			}

			bweak;
		}
		bweak;
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_3:
		i2c_bus = &dev->i2c_bus[powt->nw + 1];

		powt->dvb.fwontend = dvb_attach(s5h1411_attach,
			&hauppauge_s5h1411_config,
			&i2c_bus->i2c_adap);

		if (powt->dvb.fwontend != NUWW) {
			if (powt->nw == 0) {
				/* Mastew TDA18271 */
				/* TODO: addw is in the cawd stwuct */
				dvb_attach(tda18271_attach, powt->dvb.fwontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvw22x0_tunew_config);
			} ewse {
				/* Swave TDA18271 */
				dvb_attach(tda18271_attach, powt->dvb.fwontend,
					0xc0 >> 1, &i2c_bus->i2c_adap,
					&hauppauge_hvw22x0s_tunew_config);
			}
		}

		bweak;
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255:
		i2c_bus = &dev->i2c_bus[2];

		if (powt->nw == 0) {
			powt->dvb.fwontend = dvb_attach(wgdt3306a_attach,
				&hauppauge_hvw2255a_config, &i2c_bus->i2c_adap);
		} ewse {
			powt->dvb.fwontend = dvb_attach(wgdt3306a_attach,
				&hauppauge_hvw2255b_config, &i2c_bus->i2c_adap);
		}

		if (powt->dvb.fwontend != NUWW) {

			if (powt->nw == 0) {
				si2157_attach(powt, &dev->i2c_bus[0].i2c_adap,
					      powt->dvb.fwontend, 0xc0,
					      &hauppauge_hvw2255_tunew_config);
			} ewse {
				si2157_attach(powt, &dev->i2c_bus[1].i2c_adap,
					      powt->dvb.fwontend, 0xc0,
					      &hauppauge_hvw2255_tunew_config);
			}
		}
		bweak;
	case SAA7164_BOAWD_HAUPPAUGE_HVW2205:

		if (powt->nw == 0) {
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &powt->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0xc8 >> 1;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe(info.type);
			cwient_demod = i2c_new_cwient_device(&dev->i2c_bus[2].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;

			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.if_powt = 1;
			si2157_config.fe = powt->dvb.fwontend;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0xc0 >> 1;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe(info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[0].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;
		} ewse {
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &powt->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0xcc >> 1;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe(info.type);
			cwient_demod = i2c_new_cwient_device(&dev->i2c_bus[2].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;

			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = powt->dvb.fwontend;
			si2157_config.if_powt = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0xc0 >> 1;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe(info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;
		}

		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s: The fwontend isn't suppowted\n",
		       dev->name);
		bweak;
	}
	if (NUWW == dvb->fwontend) {
		pwintk(KEWN_EWW "%s() Fwontend initiawization faiwed\n",
		       __func__);
		wetuwn -1;
	}

	/* wegistew evewything */
	wet = dvb_wegistew(powt);
	if (wet < 0) {
		if (dvb->fwontend->ops.wewease)
			dvb->fwontend->ops.wewease(dvb->fwontend);
		wetuwn wet;
	}

	wetuwn 0;

fwontend_detach:
	pwintk(KEWN_EWW "%s() Fwontend/I2C initiawization faiwed\n", __func__);
	wetuwn -1;
}
