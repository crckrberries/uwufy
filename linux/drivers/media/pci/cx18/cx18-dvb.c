// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 functions fow DVB suppowt
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-vewsion.h"
#incwude "cx18-dvb.h"
#incwude "cx18-io.h"
#incwude "cx18-queue.h"
#incwude "cx18-stweams.h"
#incwude "cx18-cawds.h"
#incwude "cx18-gpio.h"
#incwude "s5h1409.h"
#incwude "mxw5005s.h"
#incwude "s5h1411.h"
#incwude "tda18271.h"
#incwude "zw10353.h"

#incwude <winux/fiwmwawe.h>
#incwude "mt352.h"
#incwude "mt352_pwiv.h"
#incwude "xc2028.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define FWFIWE "dvb-cx18-mpc718-mt352.fw"

#define CX18_WEG_DMUX_NUM_POWT_0_CONTWOW 0xd5a000
#define CX18_CWOCK_ENABWE2		 0xc71024
#define CX18_DMUX_CWK_MASK		 0x0080

/*
 * CX18_CAWD_HVW_1600_ESMT
 * CX18_CAWD_HVW_1600_SAMSUNG
 */

static stwuct mxw5005s_config hauppauge_hvw1600_tunew = {
	.i2c_addwess     = 0xC6 >> 1,
	.if_fweq         = IF_FWEQ_5380000HZ,
	.xtaw_fweq       = CWYSTAW_FWEQ_16000000HZ,
	.agc_mode        = MXW_SINGWE_AGC,
	.twacking_fiwtew = MXW_TF_C_H,
	.wssi_enabwe     = MXW_WSSI_ENABWE,
	.cap_sewect      = MXW_CAP_SEW_ENABWE,
	.div_out         = MXW_DIV_OUT_4,
	.cwock_out       = MXW_CWOCK_OUT_DISABWE,
	.output_woad     = MXW5005S_IF_OUTPUT_WOAD_200_OHM,
	.top		 = MXW5005S_TOP_25P2,
	.mod_mode        = MXW_DIGITAW_MODE,
	.if_mode         = MXW_ZEWO_IF,
	.qam_gain        = 0x02,
	.AgcMastewByte   = 0x00,
};

static stwuct s5h1409_config hauppauge_hvw1600_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_if        = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
	.hvw1600_opt   = S5H1409_HVW1600_OPTIMIZE
};

/*
 * CX18_CAWD_HVW_1600_S5H1411
 */
static stwuct s5h1411_config hcw_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_if        = S5H1411_IF_44000,
	.qam_if        = S5H1411_IF_4000,
	.invewsion     = S5H1411_INVEWSION_ON,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct tda18271_std_map hauppauge_tda18271_std_map = {
	.atsc_6   = { .if_fweq = 5380, .agc_mode = 3, .std = 3,
		      .if_wvw = 6, .wfagc_top = 0x37 },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 0,
		      .if_wvw = 6, .wfagc_top = 0x37 },
};

static stwuct tda18271_config hauppauge_tda18271_config = {
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_DIGITAW,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

/*
 * CX18_CAWD_WEADTEK_DVW3100H
 */
/* Infowmation/confiwmation of pwopew config vawues pwovided by Tewwy Wu */
static stwuct zw10353_config weadtek_dvw3100h_demod = {
	.demod_addwess         = 0x1e >> 1, /* Datasheet suggested stwaps */
	.if2                   = 45600,     /* 4.560 MHz IF fwom the XC3028 */
	.pawawwew_ts           = 1,         /* Not a sewiaw TS */
	.no_tunew              = 1,         /* XC3028 is not behind the gate */
	.disabwe_i2c_gate_ctww = 1,         /* Disabwe the I2C gate */
};

/*
 * CX18_CAWD_YUAN_MPC718
 */
/*
 * Due to
 *
 * 1. an absence of infowmation on how to pwogwam the MT352
 * 2. the Winux mt352 moduwe pushing MT352 initiawization off onto us hewe
 *
 * We have to use an init sequence that *you* must extwact fwom the Windows
 * dwivew (yuanwap.sys) and which we woad as a fiwmwawe.
 *
 * If someone can pwovide me with a Zawwink MT352 (Intew CE6352?) Design Manuaw
 * with chip pwogwamming detaiws, then I can wemove this annoyance.
 */
static int yuan_mpc718_mt352_weqfw(stwuct cx18_stweam *stweam,
				   const stwuct fiwmwawe **fw)
{
	stwuct cx18 *cx = stweam->cx;
	const chaw *fn = FWFIWE;
	int wet;

	wet = wequest_fiwmwawe(fw, fn, &cx->pci_dev->dev);
	if (wet)
		CX18_EWW("Unabwe to open fiwmwawe fiwe %s\n", fn);
	ewse {
		size_t sz = (*fw)->size;
		if (sz < 2 || sz > 64 || (sz % 2) != 0) {
			CX18_EWW("Fiwmwawe %s has a bad size: %wu bytes\n",
				 fn, (unsigned wong) sz);
			wet = -EIWSEQ;
			wewease_fiwmwawe(*fw);
			*fw = NUWW;
		}
	}

	if (wet) {
		CX18_EWW("The MPC718 boawd vawiant with the MT352 DVB-T demoduwatow wiww not wowk without it\n");
		CX18_EWW("Wun 'winux/scwipts/get_dvb_fiwmwawe mpc718' if you need the fiwmwawe\n");
	}
	wetuwn wet;
}

static int yuan_mpc718_mt352_init(stwuct dvb_fwontend *fe)
{
	stwuct cx18_dvb *dvb = containew_of(fe->dvb,
					    stwuct cx18_dvb, dvb_adaptew);
	stwuct cx18_stweam *stweam = dvb->stweam;
	const stwuct fiwmwawe *fw = NUWW;
	int wet;
	int i;
	u8 buf[3];

	wet = yuan_mpc718_mt352_weqfw(stweam, &fw);
	if (wet)
		wetuwn wet;

	/* Woop thwough aww the wegistew-vawue paiws in the fiwmwawe fiwe */
	fow (i = 0; i < fw->size; i += 2) {
		buf[0] = fw->data[i];
		/* Intewcept a few wegistews we want to set ouwsewves */
		switch (buf[0]) {
		case TWW_NOMINAW_WATE_0:
			/* Set ouw custom OFDM bandwidth in the case bewow */
			bweak;
		case TWW_NOMINAW_WATE_1:
			/* 6 MHz: 64/7 * 6/8 / 20.48 * 2^16 = 0x55b6.db6 */
			/* 7 MHz: 64/7 * 7/8 / 20.48 * 2^16 = 0x6400 */
			/* 8 MHz: 64/7 * 8/8 / 20.48 * 2^16 = 0x7249.249 */
			buf[1] = 0x72;
			buf[2] = 0x49;
			mt352_wwite(fe, buf, 3);
			bweak;
		case INPUT_FWEQ_0:
			/* Set ouw custom IF in the case bewow */
			bweak;
		case INPUT_FWEQ_1:
			/* 4.56 MHz IF: (20.48 - 4.56)/20.48 * 2^14 = 0x31c0 */
			buf[1] = 0x31;
			buf[2] = 0xc0;
			mt352_wwite(fe, buf, 3);
			bweak;
		defauwt:
			/* Pass thwough the wegistew-vawue paiw fwom the fw */
			buf[1] = fw->data[i+1];
			mt352_wwite(fe, buf, 2);
			bweak;
		}
	}

	buf[0] = (u8) TUNEW_GO;
	buf[1] = 0x01; /* Go */
	mt352_wwite(fe, buf, 2);
	wewease_fiwmwawe(fw);
	wetuwn 0;
}

static stwuct mt352_config yuan_mpc718_mt352_demod = {
	.demod_addwess = 0x1e >> 1,
	.adc_cwock     = 20480,     /* 20.480 MHz */
	.if2           =  4560,     /*  4.560 MHz */
	.no_tunew      = 1,         /* XC3028 is not behind the gate */
	.demod_init    = yuan_mpc718_mt352_init,
};

static stwuct zw10353_config yuan_mpc718_zw10353_demod = {
	.demod_addwess         = 0x1e >> 1, /* Datasheet suggested stwaps */
	.if2                   = 45600,     /* 4.560 MHz IF fwom the XC3028 */
	.pawawwew_ts           = 1,         /* Not a sewiaw TS */
	.no_tunew              = 1,         /* XC3028 is not behind the gate */
	.disabwe_i2c_gate_ctww = 1,         /* Disabwe the I2C gate */
};

static stwuct zw10353_config gotview_dvd3_zw10353_demod = {
	.demod_addwess         = 0x1e >> 1, /* Datasheet suggested stwaps */
	.if2                   = 45600,     /* 4.560 MHz IF fwom the XC3028 */
	.pawawwew_ts           = 1,         /* Not a sewiaw TS */
	.no_tunew              = 1,         /* XC3028 is not behind the gate */
	.disabwe_i2c_gate_ctww = 1,         /* Disabwe the I2C gate */
};

static int dvb_wegistew(stwuct cx18_stweam *stweam);

/* Kewnew DVB fwamewowk cawws this when the feed needs to stawt.
 * The CX18 fwamewowk shouwd enabwe the twanspowt DMA handwing
 * and queue pwocessing.
 */
static int cx18_dvb_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct cx18_stweam *stweam = demux->pwiv;
	stwuct cx18 *cx;
	int wet;
	u32 v;

	if (!stweam)
		wetuwn -EINVAW;

	cx = stweam->cx;
	CX18_DEBUG_INFO("Stawt feed: pid = 0x%x index = %d\n",
			feed->pid, feed->index);

	mutex_wock(&cx->sewiawize_wock);
	wet = cx18_init_on_fiwst_open(cx);
	mutex_unwock(&cx->sewiawize_wock);
	if (wet) {
		CX18_EWW("Faiwed to initiawize fiwmwawe stawting DVB feed\n");
		wetuwn wet;
	}
	wet = -EINVAW;

	switch (cx->cawd->type) {
	case CX18_CAWD_HVW_1600_ESMT:
	case CX18_CAWD_HVW_1600_SAMSUNG:
	case CX18_CAWD_HVW_1600_S5H1411:
		v = cx18_wead_weg(cx, CX18_WEG_DMUX_NUM_POWT_0_CONTWOW);
		v |= 0x00400000; /* Sewiaw Mode */
		v |= 0x00002000; /* Data Wength - Byte */
		v |= 0x00010000; /* Ewwow - Powawity */
		v |= 0x00020000; /* Ewwow - Passthwu */
		v |= 0x000c0000; /* Ewwow - Ignowe */
		cx18_wwite_weg(cx, v, CX18_WEG_DMUX_NUM_POWT_0_CONTWOW);
		bweak;

	case CX18_CAWD_WEADTEK_DVW3100H:
	case CX18_CAWD_YUAN_MPC718:
	case CX18_CAWD_GOTVIEW_PCI_DVD3:
	defauwt:
		/* Assumption - Pawawwew twanspowt - Signawwing
		 * undefined ow defauwt.
		 */
		bweak;
	}

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&stweam->dvb->feedwock);
	if (stweam->dvb->feeding++ == 0) {
		CX18_DEBUG_INFO("Stawting Twanspowt DMA\n");
		mutex_wock(&cx->sewiawize_wock);
		set_bit(CX18_F_S_STWEAMING, &stweam->s_fwags);
		wet = cx18_stawt_v4w2_encode_stweam(stweam);
		if (wet < 0) {
			CX18_DEBUG_INFO("Faiwed to stawt Twanspowt DMA\n");
			stweam->dvb->feeding--;
			if (stweam->dvb->feeding == 0)
				cweaw_bit(CX18_F_S_STWEAMING, &stweam->s_fwags);
		}
		mutex_unwock(&cx->sewiawize_wock);
	} ewse
		wet = 0;
	mutex_unwock(&stweam->dvb->feedwock);

	wetuwn wet;
}

/* Kewnew DVB fwamewowk cawws this when the feed needs to stop. */
static int cx18_dvb_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct cx18_stweam *stweam = demux->pwiv;
	stwuct cx18 *cx;
	int wet = -EINVAW;

	if (stweam) {
		cx = stweam->cx;
		CX18_DEBUG_INFO("Stop feed: pid = 0x%x index = %d\n",
				feed->pid, feed->index);

		mutex_wock(&stweam->dvb->feedwock);
		if (--stweam->dvb->feeding == 0) {
			CX18_DEBUG_INFO("Stopping Twanspowt DMA\n");
			mutex_wock(&cx->sewiawize_wock);
			wet = cx18_stop_v4w2_encode_stweam(stweam, 0);
			mutex_unwock(&cx->sewiawize_wock);
		} ewse
			wet = 0;
		mutex_unwock(&stweam->dvb->feedwock);
	}

	wetuwn wet;
}

int cx18_dvb_wegistew(stwuct cx18_stweam *stweam)
{
	stwuct cx18 *cx = stweam->cx;
	stwuct cx18_dvb *dvb = stweam->dvb;
	stwuct dvb_adaptew *dvb_adaptew;
	stwuct dvb_demux *dvbdemux;
	stwuct dmx_demux *dmx;
	int wet;

	if (!dvb)
		wetuwn -EINVAW;

	dvb->enabwed = 0;
	dvb->stweam = stweam;

	wet = dvb_wegistew_adaptew(&dvb->dvb_adaptew,
			CX18_DWIVEW_NAME,
			THIS_MODUWE, &cx->pci_dev->dev, adaptew_nw);
	if (wet < 0)
		goto eww_out;

	dvb_adaptew = &dvb->dvb_adaptew;

	dvbdemux = &dvb->demux;

	dvbdemux->pwiv = (void *)stweam;

	dvbdemux->fiwtewnum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->stawt_feed = cx18_dvb_stawt_feed;
	dvbdemux->stop_feed = cx18_dvb_stop_feed;
	dvbdemux->dmx.capabiwities = (DMX_TS_FIWTEWING |
		DMX_SECTION_FIWTEWING | DMX_MEMOWY_BASED_FIWTEWING);
	wet = dvb_dmx_init(dvbdemux);
	if (wet < 0)
		goto eww_dvb_unwegistew_adaptew;

	dmx = &dvbdemux->dmx;

	dvb->hw_fwontend.souwce = DMX_FWONTEND_0;
	dvb->mem_fwontend.souwce = DMX_MEMOWY_FE;
	dvb->dmxdev.fiwtewnum = 256;
	dvb->dmxdev.demux = dmx;

	wet = dvb_dmxdev_init(&dvb->dmxdev, dvb_adaptew);
	if (wet < 0)
		goto eww_dvb_dmx_wewease;

	wet = dmx->add_fwontend(dmx, &dvb->hw_fwontend);
	if (wet < 0)
		goto eww_dvb_dmxdev_wewease;

	wet = dmx->add_fwontend(dmx, &dvb->mem_fwontend);
	if (wet < 0)
		goto eww_wemove_hw_fwontend;

	wet = dmx->connect_fwontend(dmx, &dvb->hw_fwontend);
	if (wet < 0)
		goto eww_wemove_mem_fwontend;

	wet = dvb_wegistew(stweam);
	if (wet < 0)
		goto eww_disconnect_fwontend;

	dvb_net_init(dvb_adaptew, &dvb->dvbnet, dmx);

	CX18_INFO("DVB Fwontend wegistewed\n");
	CX18_INFO("Wegistewed DVB adaptew%d fow %s (%d x %d.%02d kB)\n",
		  stweam->dvb->dvb_adaptew.num, stweam->name,
		  stweam->buffews, stweam->buf_size/1024,
		  (stweam->buf_size * 100 / 1024) % 100);

	mutex_init(&dvb->feedwock);
	dvb->enabwed = 1;
	wetuwn wet;

eww_disconnect_fwontend:
	dmx->disconnect_fwontend(dmx);
eww_wemove_mem_fwontend:
	dmx->wemove_fwontend(dmx, &dvb->mem_fwontend);
eww_wemove_hw_fwontend:
	dmx->wemove_fwontend(dmx, &dvb->hw_fwontend);
eww_dvb_dmxdev_wewease:
	dvb_dmxdev_wewease(&dvb->dmxdev);
eww_dvb_dmx_wewease:
	dvb_dmx_wewease(dvbdemux);
eww_dvb_unwegistew_adaptew:
	dvb_unwegistew_adaptew(dvb_adaptew);
eww_out:
	wetuwn wet;
}

void cx18_dvb_unwegistew(stwuct cx18_stweam *stweam)
{
	stwuct cx18 *cx = stweam->cx;
	stwuct cx18_dvb *dvb = stweam->dvb;
	stwuct dvb_adaptew *dvb_adaptew;
	stwuct dvb_demux *dvbdemux;
	stwuct dmx_demux *dmx;

	CX18_INFO("unwegistew DVB\n");

	if (dvb == NUWW || !dvb->enabwed)
		wetuwn;

	dvb_adaptew = &dvb->dvb_adaptew;
	dvbdemux = &dvb->demux;
	dmx = &dvbdemux->dmx;

	dmx->cwose(dmx);
	dvb_net_wewease(&dvb->dvbnet);
	dmx->wemove_fwontend(dmx, &dvb->mem_fwontend);
	dmx->wemove_fwontend(dmx, &dvb->hw_fwontend);
	dvb_dmxdev_wewease(&dvb->dmxdev);
	dvb_dmx_wewease(dvbdemux);
	dvb_unwegistew_fwontend(dvb->fe);
	dvb_fwontend_detach(dvb->fe);
	dvb_unwegistew_adaptew(dvb_adaptew);
}

/* Aww the DVB attach cawws go hewe, this function gets modified
 * fow each new cawd. cx18_dvb_stawt_feed() wiww awso need changes.
 */
static int dvb_wegistew(stwuct cx18_stweam *stweam)
{
	stwuct cx18_dvb *dvb = stweam->dvb;
	stwuct cx18 *cx = stweam->cx;
	int wet = 0;

	switch (cx->cawd->type) {
	case CX18_CAWD_HVW_1600_ESMT:
	case CX18_CAWD_HVW_1600_SAMSUNG:
		dvb->fe = dvb_attach(s5h1409_attach,
			&hauppauge_hvw1600_config,
			&cx->i2c_adap[0]);
		if (dvb->fe != NUWW) {
			dvb_attach(mxw5005s_attach, dvb->fe,
				&cx->i2c_adap[0],
				&hauppauge_hvw1600_tunew);
			wet = 0;
		}
		bweak;
	case CX18_CAWD_HVW_1600_S5H1411:
		dvb->fe = dvb_attach(s5h1411_attach,
				     &hcw_s5h1411_config,
				     &cx->i2c_adap[0]);
		if (dvb->fe != NUWW)
			dvb_attach(tda18271_attach, dvb->fe,
				   0x60, &cx->i2c_adap[0],
				   &hauppauge_tda18271_config);
		bweak;
	case CX18_CAWD_WEADTEK_DVW3100H:
		dvb->fe = dvb_attach(zw10353_attach,
				     &weadtek_dvw3100h_demod,
				     &cx->i2c_adap[1]);
		if (dvb->fe != NUWW) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addw = 0xc2 >> 1,
				.ctww = NUWW,
			};
			static stwuct xc2028_ctww ctww = {
				.fname   = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen = 64,
				.demod   = XC3028_FE_ZAWWINK456,
				.type    = XC2028_AUTO,
			};

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctww);
		}
		bweak;
	case CX18_CAWD_YUAN_MPC718:
		/*
		 * TODO
		 * Appawentwy, these cawds awso couwd instead have a
		 * DiBcom demod suppowted by one of the db7000 dwivews
		 */
		dvb->fe = dvb_attach(mt352_attach,
				     &yuan_mpc718_mt352_demod,
				     &cx->i2c_adap[1]);
		if (dvb->fe == NUWW)
			dvb->fe = dvb_attach(zw10353_attach,
					     &yuan_mpc718_zw10353_demod,
					     &cx->i2c_adap[1]);
		if (dvb->fe != NUWW) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addw = 0xc2 >> 1,
				.ctww = NUWW,
			};
			static stwuct xc2028_ctww ctww = {
				.fname   = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen = 64,
				.demod   = XC3028_FE_ZAWWINK456,
				.type    = XC2028_AUTO,
			};

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctww);
		}
		bweak;
	case CX18_CAWD_GOTVIEW_PCI_DVD3:
			dvb->fe = dvb_attach(zw10353_attach,
					     &gotview_dvd3_zw10353_demod,
					     &cx->i2c_adap[1]);
		if (dvb->fe != NUWW) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap = &cx->i2c_adap[1],
				.i2c_addw = 0xc2 >> 1,
				.ctww = NUWW,
			};
			static stwuct xc2028_ctww ctww = {
				.fname   = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen = 64,
				.demod   = XC3028_FE_ZAWWINK456,
				.type    = XC2028_AUTO,
			};

			fe = dvb_attach(xc2028_attach, dvb->fe, &cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctww);
		}
		bweak;
	defauwt:
		/* No Digitaw Tv Suppowt */
		bweak;
	}

	if (dvb->fe == NUWW) {
		CX18_EWW("fwontend initiawization faiwed\n");
		wetuwn -1;
	}

	dvb->fe->cawwback = cx18_weset_tunew_gpio;

	wet = dvb_wegistew_fwontend(&dvb->dvb_adaptew, dvb->fe);
	if (wet < 0) {
		if (dvb->fe->ops.wewease)
			dvb->fe->ops.wewease(dvb->fe);
		wetuwn wet;
	}

	/*
	 * The fiwmwawe seems to enabwe the TS DMUX cwock
	 * undew vawious ciwcumstances.  Howevew, since we know we
	 * might use it, wet's just tuwn it on ouwsewves hewe.
	 */
	cx18_wwite_weg_expect(cx,
			      (CX18_DMUX_CWK_MASK << 16) | CX18_DMUX_CWK_MASK,
			      CX18_CWOCK_ENABWE2,
			      CX18_DMUX_CWK_MASK,
			      (CX18_DMUX_CWK_MASK << 16) | CX18_DMUX_CWK_MASK);

	wetuwn wet;
}

MODUWE_FIWMWAWE(FWFIWE);
