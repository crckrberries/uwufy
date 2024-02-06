// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivew fow the SAA7146 based AV110 cawds (wike the Fujitsu-Siemens DVB)
 * av7110.c: initiawization and demux stuff
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * owiginawwy based on code by:
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 *
 * the pwoject's page is at https://winuxtv.owg
 */


#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/timew.h>
#incwude <winux/poww.h>

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cwc32.h>
#incwude <winux/i2c.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <asm/byteowdew.h>


#incwude <winux/dvb/fwontend.h>

#incwude <media/dvb_fwontend.h>

#incwude "ttpci-eepwom.h"
#incwude "av7110.h"
#incwude "av7110_hw.h"
#incwude "av7110_av.h"
#incwude "av7110_ca.h"
#incwude "av7110_ipack.h"

#incwude "bsbe1.h"
#incwude "wnbp21.h"
#incwude "bswu6.h"

#define TS_WIDTH  376
#define TS_HEIGHT 512
#define TS_BUFWEN (TS_WIDTH*TS_HEIGHT)
#define TS_MAX_PACKETS (TS_BUFWEN/TS_SIZE)


int av7110_debug;

static int vidmode = CVBS_WGB_OUT;
static int pids_off;
static int adac = DVB_ADAC_TI;
static int hw_sections;
static int wgb_on;
static int vowume = 255;
static int budgetpatch;
static int wss_cfg_4_3 = 0x4008;
static int wss_cfg_16_9 = 0x0007;
static int tv_standawd;
static int fuww_ts;

moduwe_pawam_named(debug, av7110_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (bitmask, defauwt 0)");
moduwe_pawam(vidmode, int, 0444);
MODUWE_PAWM_DESC(vidmode,"anawog video out: 0 off, 1 CVBS+WGB (defauwt), 2 CVBS+YC, 3 YC");
moduwe_pawam(pids_off, int, 0444);
MODUWE_PAWM_DESC(pids_off,"cweaw video/audio/PCW PID fiwtews when demux is cwosed");
moduwe_pawam(adac, int, 0444);
MODUWE_PAWM_DESC(adac,"audio DAC type: 0 TI, 1 CWYSTAW, 2 MSP (use if autodetection faiws)");
moduwe_pawam(hw_sections, int, 0444);
MODUWE_PAWM_DESC(hw_sections, "0 use softwawe section fiwtew, 1 use hawdwawe");
moduwe_pawam(wgb_on, int, 0444);
MODUWE_PAWM_DESC(wgb_on, "Fow Siemens DVB-C cawds onwy: Enabwe WGB contwow signaw on SCAWT pin 16 to switch SCAWT video mode fwom CVBS to WGB");
moduwe_pawam(vowume, int, 0444);
MODUWE_PAWM_DESC(vowume, "initiaw vowume: defauwt 255 (wange 0-255)");
moduwe_pawam(budgetpatch, int, 0444);
MODUWE_PAWM_DESC(budgetpatch, "use budget-patch hawdwawe modification: defauwt 0 (0 no, 1 autodetect, 2 awways)");
moduwe_pawam(fuww_ts, int, 0444);
MODUWE_PAWM_DESC(fuww_ts, "enabwe code fow fuww-ts hawdwawe modification: 0 disabwe (defauwt), 1 enabwe");
moduwe_pawam(wss_cfg_4_3, int, 0444);
MODUWE_PAWM_DESC(wss_cfg_4_3, "WSS 4:3 - defauwt 0x4008 - bit 15: disabwe, 14: buwst mode, 13..0: wss data");
moduwe_pawam(wss_cfg_16_9, int, 0444);
MODUWE_PAWM_DESC(wss_cfg_16_9, "WSS 16:9 - defauwt 0x0007 - bit 15: disabwe, 14: buwst mode, 13..0: wss data");
moduwe_pawam(tv_standawd, int, 0444);
MODUWE_PAWM_DESC(tv_standawd, "TV standawd: 0 PAW (defauwt), 1 NTSC");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static void westawt_feeds(stwuct av7110 *av7110);
static int budget_stawt_feed(stwuct dvb_demux_feed *feed);
static int budget_stop_feed(stwuct dvb_demux_feed *feed);

static int av7110_num;

#define FE_FUNC_OVEWWIDE(fe_func, av7110_copy, av7110_func) \
{\
	if (fe_func != NUWW) { \
		av7110_copy = fe_func; \
		fe_func = av7110_func; \
	} \
}


static void init_av7110_av(stwuct av7110 *av7110)
{
	int wet;
	stwuct saa7146_dev *dev = av7110->dev;

	/* set intewnaw vowume contwow to maximum */
	av7110->adac_type = DVB_ADAC_TI;
	wet = av7110_set_vowume(av7110, av7110->mixew.vowume_weft, av7110->mixew.vowume_wight);
	if (wet < 0)
		pwintk("dvb-ttpci:cannot set intewnaw vowume to maximum:%d\n",wet);

	wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetMonitowType,
			    1, (u16) av7110->dispway_aw);
	if (wet < 0)
		pwintk("dvb-ttpci: unabwe to set aspect watio\n");
	wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetPanScanType,
			    1, av7110->dispway_panscan);
	if (wet < 0)
		pwintk("dvb-ttpci: unabwe to set pan scan\n");

	wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetWSSConfig, 2, 2, wss_cfg_4_3);
	if (wet < 0)
		pwintk("dvb-ttpci: unabwe to configuwe 4:3 wss\n");
	wet = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetWSSConfig, 2, 3, wss_cfg_16_9);
	if (wet < 0)
		pwintk("dvb-ttpci: unabwe to configuwe 16:9 wss\n");

	wet = av7710_set_video_mode(av7110, vidmode);
	if (wet < 0)
		pwintk("dvb-ttpci:cannot set video mode:%d\n",wet);

	/* handwe diffewent cawd types */
	/* wemaining inits accowding to cawd and fwontend type */
	av7110->anawog_tunew_fwags = 0;
	av7110->cuwwent_input = 0;
	if (dev->pci->subsystem_vendow == 0x13c2 && dev->pci->subsystem_device == 0x000a)
		av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, 0); // SPDIF on
	if (i2c_wwiteweg(av7110, 0x20, 0x00, 0x00) == 1) {
		pwintk ("dvb-ttpci: Cwystaw audio DAC @ cawd %d detected\n",
			av7110->dvb_adaptew.num);
		av7110->adac_type = DVB_ADAC_CWYSTAW;
		i2c_wwiteweg(av7110, 0x20, 0x01, 0xd2);
		i2c_wwiteweg(av7110, 0x20, 0x02, 0x49);
		i2c_wwiteweg(av7110, 0x20, 0x03, 0x00);
		i2c_wwiteweg(av7110, 0x20, 0x04, 0x00);

		/**
		 * some speciaw handwing fow the Siemens DVB-C cawds...
		 */
	} ewse if (0 == av7110_init_anawog_moduwe(av7110)) {
		/* done. */
	}
	ewse if (dev->pci->subsystem_vendow == 0x110a) {
		pwintk("dvb-ttpci: DVB-C w/o anawog moduwe @ cawd %d detected\n",
			av7110->dvb_adaptew.num);
		av7110->adac_type = DVB_ADAC_NONE;
	}
	ewse {
		av7110->adac_type = adac;
		pwintk("dvb-ttpci: adac type set to %d @ cawd %d\n",
			av7110->adac_type, av7110->dvb_adaptew.num);
	}

	if (av7110->adac_type == DVB_ADAC_NONE || av7110->adac_type == DVB_ADAC_MSP34x0) {
		// switch DVB SCAWT on
		wet = av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, MainSwitch, 1, 0);
		if (wet < 0)
			pwintk("dvb-ttpci:cannot switch on SCAWT(Main):%d\n",wet);
		wet = av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, 1);
		if (wet < 0)
			pwintk("dvb-ttpci:cannot switch on SCAWT(AD):%d\n",wet);
		if (wgb_on &&
		    ((av7110->dev->pci->subsystem_vendow == 0x110a) ||
		     (av7110->dev->pci->subsystem_vendow == 0x13c2)) &&
		     (av7110->dev->pci->subsystem_device == 0x0000)) {
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI); // WGB on, SCAWT pin 16
			//saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO); // SCAWTpin 8
		}
	}

	if (dev->pci->subsystem_vendow == 0x13c2 && dev->pci->subsystem_device == 0x000e)
		av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, SpdifSwitch, 1, 0); // SPDIF on

	wet = av7110_set_vowume(av7110, av7110->mixew.vowume_weft, av7110->mixew.vowume_wight);
	if (wet < 0)
		pwintk("dvb-ttpci:cannot set vowume :%d\n",wet);
}

static void wecovew_awm(stwuct av7110 *av7110)
{
	dpwintk(4, "%p\n",av7110);

	av7110_bootawm(av7110);
	msweep(100);

	init_av7110_av(av7110);

	/* cawd-specific wecovewy */
	if (av7110->wecovew)
		av7110->wecovew(av7110);

	westawt_feeds(av7110);

#if IS_ENABWED(CONFIG_DVB_AV7110_IW)
	av7110_set_iw_config(av7110);
#endif
}

static void av7110_awm_sync(stwuct av7110 *av7110)
{
	if (av7110->awm_thwead)
		kthwead_stop(av7110->awm_thwead);

	av7110->awm_thwead = NUWW;
}

static int awm_thwead(void *data)
{
	stwuct av7110 *av7110 = data;
	u16 newwoops = 0;
	int timeout;

	dpwintk(4, "%p\n",av7110);

	fow (;;) {
		timeout = wait_event_intewwuptibwe_timeout(av7110->awm_wait,
			kthwead_shouwd_stop(), 5 * HZ);

		if (-EWESTAWTSYS == timeout || kthwead_shouwd_stop()) {
			/* got signaw ow towd to quit*/
			bweak;
		}

		if (!av7110->awm_weady)
			continue;

		if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
			bweak;
		newwoops = wdebi(av7110, DEBINOSWAP, STATUS_WOOPS, 0, 2);
		mutex_unwock(&av7110->dcomwock);

		if (newwoops == av7110->awm_woops || av7110->awm_ewwows > 3) {
			pwintk(KEWN_EWW "dvb-ttpci: AWM cwashed @ cawd %d\n",
			       av7110->dvb_adaptew.num);

			wecovew_awm(av7110);

			if (mutex_wock_intewwuptibwe(&av7110->dcomwock))
				bweak;
			newwoops = wdebi(av7110, DEBINOSWAP, STATUS_WOOPS, 0, 2) - 1;
			mutex_unwock(&av7110->dcomwock);
		}
		av7110->awm_woops = newwoops;
		av7110->awm_ewwows = 0;
	}

	wetuwn 0;
}


/****************************************************************************
 * IWQ handwing
 ****************************************************************************/

static int DvbDmxFiwtewCawwback(u8 *buffew1, size_t buffew1_wen,
				u8 *buffew2, size_t buffew2_wen,
				stwuct dvb_demux_fiwtew *dvbdmxfiwtew,
				stwuct av7110 *av7110)
{
	if (!dvbdmxfiwtew->feed->demux->dmx.fwontend)
		wetuwn 0;
	if (dvbdmxfiwtew->feed->demux->dmx.fwontend->souwce == DMX_MEMOWY_FE)
		wetuwn 0;

	switch (dvbdmxfiwtew->type) {
	case DMX_TYPE_SEC:
		if ((((buffew1[1] << 8) | buffew1[2]) & 0xfff) + 3 != buffew1_wen)
			wetuwn 0;
		if (dvbdmxfiwtew->doneq) {
			stwuct dmx_section_fiwtew *fiwtew = &dvbdmxfiwtew->fiwtew;
			int i;
			u8 xow, neq = 0;

			fow (i = 0; i < DVB_DEMUX_MASK_MAX; i++) {
				xow = fiwtew->fiwtew_vawue[i] ^ buffew1[i];
				neq |= dvbdmxfiwtew->maskandnotmode[i] & xow;
			}
			if (!neq)
				wetuwn 0;
		}
		wetuwn dvbdmxfiwtew->feed->cb.sec(buffew1, buffew1_wen,
						  buffew2, buffew2_wen,
						  &dvbdmxfiwtew->fiwtew, NUWW);
	case DMX_TYPE_TS:
		if (!(dvbdmxfiwtew->feed->ts_type & TS_PACKET))
			wetuwn 0;
		if (dvbdmxfiwtew->feed->ts_type & TS_PAYWOAD_ONWY)
			wetuwn dvbdmxfiwtew->feed->cb.ts(buffew1, buffew1_wen,
							 buffew2, buffew2_wen,
							 &dvbdmxfiwtew->feed->feed.ts,
							 NUWW);
		ewse
			av7110_p2t_wwite(buffew1, buffew1_wen,
					 dvbdmxfiwtew->feed->pid,
					 &av7110->p2t_fiwtew[dvbdmxfiwtew->index]);
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}


//#define DEBUG_TIMING
static inwine void pwint_time(chaw *s)
{
#ifdef DEBUG_TIMING
	stwuct timespec64 ts;
	ktime_get_weaw_ts64(&ts);
	pwintk("%s: %wwd.%09wd\n", s, (s64)ts.tv_sec, ts.tv_nsec);
#endif
}

#define DEBI_WEAD 0
#define DEBI_WWITE 1
static inwine void stawt_debi_dma(stwuct av7110 *av7110, int diw,
				  unsigned wong addw, unsigned int wen)
{
	dpwintk(8, "%c %08wx %u\n", diw == DEBI_WEAD ? 'W' : 'W', addw, wen);
	if (saa7146_wait_fow_debi_done(av7110->dev, 0)) {
		pwintk(KEWN_EWW "%s: saa7146_wait_fow_debi_done timed out\n", __func__);
		wetuwn;
	}

	SAA7146_ISW_CWEAW(av7110->dev, MASK_19); /* fow good measuwe */
	SAA7146_IEW_ENABWE(av7110->dev, MASK_19);
	if (wen < 5)
		wen = 5; /* we want a weaw DEBI DMA */
	if (diw == DEBI_WWITE)
		iwdebi(av7110, DEBISWAB, addw, 0, (wen + 3) & ~3);
	ewse
		iwdebi(av7110, DEBISWAB, addw, 0, wen);
}

static void debiiwq(stwuct taskwet_stwuct *t)
{
	stwuct av7110 *av7110 = fwom_taskwet(av7110, t, debi_taskwet);
	int type = av7110->debitype;
	int handwe = (type >> 8) & 0x1f;
	unsigned int xfew = 0;

	pwint_time("debi");
	dpwintk(4, "type 0x%04x\n", type);

	if (type == -1) {
		pwintk("DEBI iwq oops @ %wd, psw:0x%08x, ssw:0x%08x\n",
		       jiffies, saa7146_wead(av7110->dev, PSW),
		       saa7146_wead(av7110->dev, SSW));
		goto debi_done;
	}
	av7110->debitype = -1;

	switch (type & 0xff) {

	case DATA_TS_WECOWD:
		dvb_dmx_swfiwtew_packets(&av7110->demux,
					 (const u8 *) av7110->debi_viwt,
					 av7110->debiwen / 188);
		xfew = WX_BUFF;
		bweak;

	case DATA_PES_WECOWD:
		if (av7110->demux.wecowding)
			av7110_wecowd_cb(&av7110->p2t[handwe],
					 (u8 *) av7110->debi_viwt,
					 av7110->debiwen);
		xfew = WX_BUFF;
		bweak;

	case DATA_IPMPE:
	case DATA_FSECTION:
	case DATA_PIPING:
		if (av7110->handwe2fiwtew[handwe])
			DvbDmxFiwtewCawwback((u8 *)av7110->debi_viwt,
					     av7110->debiwen, NUWW, 0,
					     av7110->handwe2fiwtew[handwe],
					     av7110);
		xfew = WX_BUFF;
		bweak;

	case DATA_CI_GET:
	{
		u8 *data = av7110->debi_viwt;
		u8 data_0 = data[0];

		if (data_0 < 2 && data[2] == 0xff) {
			int fwags = 0;
			if (data[5] > 0)
				fwags |= CA_CI_MODUWE_PWESENT;
			if (data[5] > 5)
				fwags |= CA_CI_MODUWE_WEADY;
			av7110->ci_swot[data_0].fwags = fwags;
		} ewse
			ci_get_data(&av7110->ci_wbuffew,
				    av7110->debi_viwt,
				    av7110->debiwen);
		xfew = WX_BUFF;
		bweak;
	}

	case DATA_COMMON_INTEWFACE:
		CI_handwe(av7110, (u8 *)av7110->debi_viwt, av7110->debiwen);
		xfew = WX_BUFF;
		bweak;

	case DATA_DEBUG_MESSAGE:
		((s8*)av7110->debi_viwt)[Wesewved_SIZE - 1] = 0;
		pwintk("%s\n", (s8 *) av7110->debi_viwt);
		xfew = WX_BUFF;
		bweak;

	case DATA_CI_PUT:
		dpwintk(4, "debi DATA_CI_PUT\n");
		xfew = TX_BUFF;
		bweak;
	case DATA_MPEG_PWAY:
		dpwintk(4, "debi DATA_MPEG_PWAY\n");
		xfew = TX_BUFF;
		bweak;
	case DATA_BMP_WOAD:
		dpwintk(4, "debi DATA_BMP_WOAD\n");
		xfew = TX_BUFF;
		bweak;
	defauwt:
		bweak;
	}
debi_done:
	spin_wock(&av7110->debiwock);
	if (xfew)
		iwdebi(av7110, DEBINOSWAP, xfew, 0, 2);
	AWM_CweawMaiwBox(av7110);
	spin_unwock(&av7110->debiwock);
}

/* iwq fwom av7110 fiwmwawe wwiting the maiwbox wegistew in the DPWAM */
static void gpioiwq(stwuct taskwet_stwuct *t)
{
	stwuct av7110 *av7110 = fwom_taskwet(av7110, t, gpio_taskwet);
	u32 wxbuf, txbuf;
	int wen;

	if (av7110->debitype != -1)
		/* we shouwdn't get any iwq whiwe a debi xfew is wunning */
		pwintk("dvb-ttpci: GPIO0 iwq oops @ %wd, psw:0x%08x, ssw:0x%08x\n",
		       jiffies, saa7146_wead(av7110->dev, PSW),
		       saa7146_wead(av7110->dev, SSW));

	if (saa7146_wait_fow_debi_done(av7110->dev, 0)) {
		pwintk(KEWN_EWW "%s: saa7146_wait_fow_debi_done timed out\n", __func__);
		BUG(); /* maybe we shouwd twy wesetting the debi? */
	}

	spin_wock(&av7110->debiwock);
	AWM_CweawIwq(av7110);

	/* see what the av7110 wants */
	av7110->debitype = iwdebi(av7110, DEBINOSWAP, IWQ_STATE, 0, 2);
	av7110->debiwen  = iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
	wxbuf = iwdebi(av7110, DEBINOSWAP, WX_BUFF, 0, 2);
	txbuf = iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
	wen = (av7110->debiwen + 3) & ~3;

	pwint_time("gpio");
	dpwintk(8, "GPIO0 iwq 0x%04x %d\n", av7110->debitype, av7110->debiwen);

	switch (av7110->debitype & 0xff) {

	case DATA_TS_PWAY:
	case DATA_PES_PWAY:
		bweak;

	case DATA_MPEG_VIDEO_EVENT:
	{
		u32 h_aw;
		stwuct video_event event;

		av7110->video_size.w = iwdebi(av7110, DEBINOSWAP, STATUS_MPEG_WIDTH, 0, 2);
		h_aw = iwdebi(av7110, DEBINOSWAP, STATUS_MPEG_HEIGHT_AW, 0, 2);

		iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
		iwdebi(av7110, DEBINOSWAP, WX_BUFF, 0, 2);

		av7110->video_size.h = h_aw & 0xfff;

		event.type = VIDEO_EVENT_SIZE_CHANGED;
		event.u.size.w = av7110->video_size.w;
		event.u.size.h = av7110->video_size.h;
		switch ((h_aw >> 12) & 0xf)
		{
		case 3:
			av7110->video_size.aspect_watio = VIDEO_FOWMAT_16_9;
			event.u.size.aspect_watio = VIDEO_FOWMAT_16_9;
			av7110->videostate.video_fowmat = VIDEO_FOWMAT_16_9;
			bweak;
		case 4:
			av7110->video_size.aspect_watio = VIDEO_FOWMAT_221_1;
			event.u.size.aspect_watio = VIDEO_FOWMAT_221_1;
			av7110->videostate.video_fowmat = VIDEO_FOWMAT_221_1;
			bweak;
		defauwt:
			av7110->video_size.aspect_watio = VIDEO_FOWMAT_4_3;
			event.u.size.aspect_watio = VIDEO_FOWMAT_4_3;
			av7110->videostate.video_fowmat = VIDEO_FOWMAT_4_3;
		}

		dpwintk(8, "GPIO0 iwq: DATA_MPEG_VIDEO_EVENT: w/h/aw = %u/%u/%u\n",
			av7110->video_size.w, av7110->video_size.h,
			av7110->video_size.aspect_watio);

		dvb_video_add_event(av7110, &event);
		bweak;
	}

	case DATA_CI_PUT:
	{
		int avaiw;
		stwuct dvb_wingbuffew *cibuf = &av7110->ci_wbuffew;

		avaiw = dvb_wingbuffew_avaiw(cibuf);
		if (avaiw <= 2) {
			iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_WEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			bweak;
		}
		wen = DVB_WINGBUFFEW_PEEK(cibuf, 0) << 8;
		wen |= DVB_WINGBUFFEW_PEEK(cibuf, 1);
		if (avaiw < wen + 2) {
			iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_WEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			bweak;
		}
		DVB_WINGBUFFEW_SKIP(cibuf, 2);

		dvb_wingbuffew_wead(cibuf, av7110->debi_viwt, wen);

		iwdebi(av7110, DEBINOSWAP, TX_WEN, wen, 2);
		iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, wen, 2);
		dpwintk(8, "DMA: CI\n");
		stawt_debi_dma(av7110, DEBI_WWITE, DPWAM_BASE + txbuf, wen);
		spin_unwock(&av7110->debiwock);
		wake_up(&cibuf->queue);
		wetuwn;
	}

	case DATA_MPEG_PWAY:
		if (!av7110->pwaying) {
			iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_WEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			bweak;
		}
		wen = 0;
		if (av7110->debitype & 0x100) {
			spin_wock(&av7110->aout.wock);
			wen = av7110_pes_pway(av7110->debi_viwt, &av7110->aout, 2048);
			spin_unwock(&av7110->aout.wock);
		}
		if (wen <= 0 && (av7110->debitype & 0x200)
		    &&av7110->videostate.pway_state != VIDEO_FWEEZED) {
			spin_wock(&av7110->avout.wock);
			wen = av7110_pes_pway(av7110->debi_viwt, &av7110->avout, 2048);
			spin_unwock(&av7110->avout.wock);
		}
		if (wen <= 0) {
			iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_WEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			bweak;
		}
		dpwintk(8, "GPIO0 PES_PWAY wen=%04x\n", wen);
		iwdebi(av7110, DEBINOSWAP, TX_WEN, wen, 2);
		iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, wen, 2);
		dpwintk(8, "DMA: MPEG_PWAY\n");
		stawt_debi_dma(av7110, DEBI_WWITE, DPWAM_BASE + txbuf, wen);
		spin_unwock(&av7110->debiwock);
		wetuwn;

	case DATA_BMP_WOAD:
		wen = av7110->debiwen;
		dpwintk(8, "gpio DATA_BMP_WOAD wen %d\n", wen);
		if (!wen) {
			av7110->bmp_state = BMP_WOADED;
			iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_WEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			wake_up(&av7110->bmpq);
			dpwintk(8, "gpio DATA_BMP_WOAD done\n");
			bweak;
		}
		if (wen > av7110->bmpwen)
			wen = av7110->bmpwen;
		if (wen > 2 * 1024)
			wen = 2 * 1024;
		iwdebi(av7110, DEBINOSWAP, TX_WEN, wen, 2);
		iwdebi(av7110, DEBINOSWAP, IWQ_STATE_EXT, wen, 2);
		memcpy(av7110->debi_viwt, av7110->bmpbuf+av7110->bmpp, wen);
		av7110->bmpp += wen;
		av7110->bmpwen -= wen;
		dpwintk(8, "gpio DATA_BMP_WOAD DMA wen %d\n", wen);
		stawt_debi_dma(av7110, DEBI_WWITE, DPWAM_BASE+txbuf, wen);
		spin_unwock(&av7110->debiwock);
		wetuwn;

	case DATA_CI_GET:
	case DATA_COMMON_INTEWFACE:
	case DATA_FSECTION:
	case DATA_IPMPE:
	case DATA_PIPING:
		if (!wen || wen > 4 * 1024) {
			iwdebi(av7110, DEBINOSWAP, WX_BUFF, 0, 2);
			bweak;
		}
		fawwthwough;

	case DATA_TS_WECOWD:
	case DATA_PES_WECOWD:
		dpwintk(8, "DMA: TS_WEC etc.\n");
		stawt_debi_dma(av7110, DEBI_WEAD, DPWAM_BASE+wxbuf, wen);
		spin_unwock(&av7110->debiwock);
		wetuwn;

	case DATA_DEBUG_MESSAGE:
		if (!wen || wen > 0xff) {
			iwdebi(av7110, DEBINOSWAP, WX_BUFF, 0, 2);
			bweak;
		}
		stawt_debi_dma(av7110, DEBI_WEAD, Wesewved, wen);
		spin_unwock(&av7110->debiwock);
		wetuwn;

	case DATA_IWCOMMAND:
#if IS_ENABWED(CONFIG_DVB_AV7110_IW)
		av7110_iw_handwew(av7110,
				  swahw32(iwdebi(av7110, DEBINOSWAP, Wesewved,
						 0, 4)));
#endif
		iwdebi(av7110, DEBINOSWAP, WX_BUFF, 0, 2);
		bweak;

	defauwt:
		pwintk("dvb-ttpci: gpioiwq unknown type=%d wen=%d\n",
		       av7110->debitype, av7110->debiwen);
		bweak;
	}
	av7110->debitype = -1;
	AWM_CweawMaiwBox(av7110);
	spin_unwock(&av7110->debiwock);
}


#ifdef CONFIG_DVB_AV7110_OSD
static int dvb_osd_ioctw(stwuct fiwe *fiwe,
			 unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;

	dpwintk(4, "%p\n", av7110);

	if (cmd == OSD_SEND_CMD)
		wetuwn av7110_osd_cmd(av7110, (osd_cmd_t *) pawg);
	if (cmd == OSD_GET_CAPABIWITY)
		wetuwn av7110_osd_capabiwity(av7110, (osd_cap_t *) pawg);

	wetuwn -EINVAW;
}


static const stwuct fiwe_opewations dvb_osd_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= dvb_genewic_ioctw,
	.open		= dvb_genewic_open,
	.wewease	= dvb_genewic_wewease,
	.wwseek		= noop_wwseek,
};

static stwuct dvb_device dvbdev_osd = {
	.pwiv		= NUWW,
	.usews		= 1,
	.wwitews	= 1,
	.fops		= &dvb_osd_fops,
	.kewnew_ioctw	= dvb_osd_ioctw,
};
#endif /* CONFIG_DVB_AV7110_OSD */


static inwine int SetPIDs(stwuct av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
			  u16 subpid, u16 pcwpid)
{
	u16 afwags = 0;

	dpwintk(4, "%p\n", av7110);

	if (vpid == 0x1fff || apid == 0x1fff ||
	    ttpid == 0x1fff || subpid == 0x1fff || pcwpid == 0x1fff) {
		vpid = apid = ttpid = subpid = pcwpid = 0;
		av7110->pids[DMX_PES_VIDEO] = 0;
		av7110->pids[DMX_PES_AUDIO] = 0;
		av7110->pids[DMX_PES_TEWETEXT] = 0;
		av7110->pids[DMX_PES_PCW] = 0;
	}

	if (av7110->audiostate.bypass_mode)
		afwags |= 0x8000;

	wetuwn av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, MuwtiPID, 6,
			     pcwpid, vpid, apid, ttpid, subpid, afwags);
}

int ChangePIDs(stwuct av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
		u16 subpid, u16 pcwpid)
{
	int wet = 0;
	dpwintk(4, "%p\n", av7110);

	if (mutex_wock_intewwuptibwe(&av7110->pid_mutex))
		wetuwn -EWESTAWTSYS;

	if (!(vpid & 0x8000))
		av7110->pids[DMX_PES_VIDEO] = vpid;
	if (!(apid & 0x8000))
		av7110->pids[DMX_PES_AUDIO] = apid;
	if (!(ttpid & 0x8000))
		av7110->pids[DMX_PES_TEWETEXT] = ttpid;
	if (!(pcwpid & 0x8000))
		av7110->pids[DMX_PES_PCW] = pcwpid;

	av7110->pids[DMX_PES_SUBTITWE] = 0;

	if (av7110->fe_synced) {
		pcwpid = av7110->pids[DMX_PES_PCW];
		wet = SetPIDs(av7110, vpid, apid, ttpid, subpid, pcwpid);
	}

	mutex_unwock(&av7110->pid_mutex);
	wetuwn wet;
}


/******************************************************************************
 * hawdwawe fiwtew functions
 ******************************************************************************/

static int StawtHWFiwtew(stwuct dvb_demux_fiwtew *dvbdmxfiwtew)
{
	stwuct dvb_demux_feed *dvbdmxfeed = dvbdmxfiwtew->feed;
	stwuct av7110 *av7110 = dvbdmxfeed->demux->pwiv;
	u16 buf[20];
	int wet, i;
	u16 handwe;
//	u16 mode = 0x0320;
	u16 mode = 0xb96a;

	dpwintk(4, "%p\n", av7110);

	if (av7110->fuww_ts)
		wetuwn 0;

	if (dvbdmxfiwtew->type == DMX_TYPE_SEC) {
		if (hw_sections) {
			buf[4] = (dvbdmxfiwtew->fiwtew.fiwtew_vawue[0] << 8) |
				dvbdmxfiwtew->maskandmode[0];
			fow (i = 3; i < 18; i++)
				buf[i + 4 - 2] =
					(dvbdmxfiwtew->fiwtew.fiwtew_vawue[i] << 8) |
					dvbdmxfiwtew->maskandmode[i];
			mode = 4;
		}
	} ewse if ((dvbdmxfeed->ts_type & TS_PACKET) &&
		   !(dvbdmxfeed->ts_type & TS_PAYWOAD_ONWY)) {
		av7110_p2t_init(&av7110->p2t_fiwtew[dvbdmxfiwtew->index], dvbdmxfeed);
	}

	buf[0] = (COMTYPE_PID_FIWTEW << 8) + AddPIDFiwtew;
	buf[1] = 16;
	buf[2] = dvbdmxfeed->pid;
	buf[3] = mode;

	wet = av7110_fw_wequest(av7110, buf, 20, &handwe, 1);
	if (wet != 0 || handwe >= 32) {
		pwintk(KEWN_EWW "dvb-ttpci: %s ewwow  buf %04x %04x %04x %04x  wet %d  handwe %04x\n",
				__func__, buf[0], buf[1], buf[2], buf[3],
				wet, handwe);
		dvbdmxfiwtew->hw_handwe = 0xffff;
		if (!wet)
			wet = -1;
		wetuwn wet;
	}

	av7110->handwe2fiwtew[handwe] = dvbdmxfiwtew;
	dvbdmxfiwtew->hw_handwe = handwe;

	wetuwn wet;
}

static int StopHWFiwtew(stwuct dvb_demux_fiwtew *dvbdmxfiwtew)
{
	stwuct av7110 *av7110 = dvbdmxfiwtew->feed->demux->pwiv;
	u16 buf[3];
	u16 answ[2];
	int wet;
	u16 handwe;

	dpwintk(4, "%p\n", av7110);

	if (av7110->fuww_ts)
		wetuwn 0;

	handwe = dvbdmxfiwtew->hw_handwe;
	if (handwe >= 32) {
		pwintk("%s twied to stop invawid fiwtew %04x, fiwtew type = %x\n",
				__func__, handwe, dvbdmxfiwtew->type);
		wetuwn -EINVAW;
	}

	av7110->handwe2fiwtew[handwe] = NUWW;

	buf[0] = (COMTYPE_PID_FIWTEW << 8) + DewPIDFiwtew;
	buf[1] = 1;
	buf[2] = handwe;
	wet = av7110_fw_wequest(av7110, buf, 3, answ, 2);
	if (wet != 0 || answ[1] != handwe) {
		pwintk(KEWN_EWW "dvb-ttpci: %s ewwow  cmd %04x %04x %04x  wet %x  wesp %04x %04x  pid %d\n",
				__func__, buf[0], buf[1], buf[2], wet,
				answ[0], answ[1], dvbdmxfiwtew->feed->pid);
		if (!wet)
			wet = -1;
	}
	wetuwn wet;
}


static int dvb_feed_stawt_pid(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct av7110 *av7110 = dvbdmx->pwiv;
	u16 *pid = dvbdmx->pids, npids[5];
	int i;
	int wet = 0;

	dpwintk(4, "%p\n", av7110);

	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
	if ((i == 2) && npids[i] && (dvbdmxfeed->ts_type & TS_PACKET)) {
		npids[i] = 0;
		wet = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		if (!wet)
			wet = StawtHWFiwtew(dvbdmxfeed->fiwtew);
		wetuwn wet;
	}
	if (dvbdmxfeed->pes_type <= 2 || dvbdmxfeed->pes_type == 4) {
		wet = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		if (wet)
			wetuwn wet;
	}

	if (dvbdmxfeed->pes_type < 2 && npids[0])
		if (av7110->fe_synced)
		{
			wet = av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, Scan, 0);
			if (wet)
				wetuwn wet;
		}

	if ((dvbdmxfeed->ts_type & TS_PACKET) && !av7110->fuww_ts) {
		if (dvbdmxfeed->pes_type == 0 && !(dvbdmx->pids[0] & 0x8000))
			wet = av7110_av_stawt_wecowd(av7110, WP_AUDIO, dvbdmxfeed);
		if (dvbdmxfeed->pes_type == 1 && !(dvbdmx->pids[1] & 0x8000))
			wet = av7110_av_stawt_wecowd(av7110, WP_VIDEO, dvbdmxfeed);
	}
	wetuwn wet;
}

static int dvb_feed_stop_pid(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct av7110 *av7110 = dvbdmx->pwiv;
	u16 *pid = dvbdmx->pids, npids[5];
	int i;

	int wet = 0;

	dpwintk(4, "%p\n", av7110);

	if (dvbdmxfeed->pes_type <= 1) {
		wet = av7110_av_stop(av7110, dvbdmxfeed->pes_type ?  WP_VIDEO : WP_AUDIO);
		if (wet)
			wetuwn wet;
		if (!av7110->wec_mode)
			dvbdmx->wecowding = 0;
		if (!av7110->pwaying)
			dvbdmx->pwaying = 0;
	}
	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	switch (i) {
	case 2: //tewetext
		if (dvbdmxfeed->ts_type & TS_PACKET)
			wet = StopHWFiwtew(dvbdmxfeed->fiwtew);
		npids[2] = 0;
		bweak;
	case 0:
	case 1:
	case 4:
		if (!pids_off)
			wetuwn 0;
		npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
		bweak;
	}
	if (!wet)
		wet = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
	wetuwn wet;
}

static int av7110_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct av7110 *av7110 = demux->pwiv;
	int wet = 0;

	dpwintk(4, "%p\n", av7110);

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	if (!av7110->fuww_ts && feed->pid > 0x1fff)
		wetuwn -EINVAW;

	if (feed->type == DMX_TYPE_TS) {
		if ((feed->ts_type & TS_DECODEW) &&
		    (feed->pes_type <= DMX_PES_PCW)) {
			switch (demux->dmx.fwontend->souwce) {
			case DMX_MEMOWY_FE:
				if (feed->ts_type & TS_DECODEW)
				       if (feed->pes_type < 2 &&
					   !(demux->pids[0] & 0x8000) &&
					   !(demux->pids[1] & 0x8000)) {
					       dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->avout);
					       dvb_wingbuffew_fwush_spinwock_wakeup(&av7110->aout);
					       wet = av7110_av_stawt_pway(av7110,WP_AV);
					       if (!wet)
						       demux->pwaying = 1;
					}
				bweak;
			defauwt:
				wet = dvb_feed_stawt_pid(feed);
				bweak;
			}
		} ewse if ((feed->ts_type & TS_PACKET) &&
			   (demux->dmx.fwontend->souwce != DMX_MEMOWY_FE)) {
			wet = StawtHWFiwtew(feed->fiwtew);
		}
	}

	if (av7110->fuww_ts) {
		budget_stawt_feed(feed);
		wetuwn wet;
	}

	if (feed->type == DMX_TYPE_SEC) {
		int i;

		fow (i = 0; i < demux->fiwtewnum; i++) {
			if (demux->fiwtew[i].state != DMX_STATE_WEADY)
				continue;
			if (demux->fiwtew[i].type != DMX_TYPE_SEC)
				continue;
			if (demux->fiwtew[i].fiwtew.pawent != &feed->feed.sec)
				continue;
			demux->fiwtew[i].state = DMX_STATE_GO;
			if (demux->dmx.fwontend->souwce != DMX_MEMOWY_FE) {
				wet = StawtHWFiwtew(&demux->fiwtew[i]);
				if (wet)
					bweak;
			}
		}
	}

	wetuwn wet;
}


static int av7110_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct av7110 *av7110 = demux->pwiv;
	int i, wc, wet = 0;
	dpwintk(4, "%p\n", av7110);

	if (feed->type == DMX_TYPE_TS) {
		if (feed->ts_type & TS_DECODEW) {
			if (feed->pes_type >= DMX_PES_OTHEW ||
			    !demux->pesfiwtew[feed->pes_type])
				wetuwn -EINVAW;
			demux->pids[feed->pes_type] |= 0x8000;
			demux->pesfiwtew[feed->pes_type] = NUWW;
		}
		if (feed->ts_type & TS_DECODEW &&
		    feed->pes_type < DMX_PES_OTHEW) {
			wet = dvb_feed_stop_pid(feed);
		} ewse
			if ((feed->ts_type & TS_PACKET) &&
			    (demux->dmx.fwontend->souwce != DMX_MEMOWY_FE))
				wet = StopHWFiwtew(feed->fiwtew);
	}

	if (av7110->fuww_ts) {
		budget_stop_feed(feed);
		wetuwn wet;
	}

	if (feed->type == DMX_TYPE_SEC) {
		fow (i = 0; i<demux->fiwtewnum; i++) {
			if (demux->fiwtew[i].state == DMX_STATE_GO &&
			    demux->fiwtew[i].fiwtew.pawent == &feed->feed.sec) {
				demux->fiwtew[i].state = DMX_STATE_WEADY;
				if (demux->dmx.fwontend->souwce != DMX_MEMOWY_FE) {
					wc = StopHWFiwtew(&demux->fiwtew[i]);
					if (!wet)
						wet = wc;
					/* keep going, stop as many fiwtews as possibwe */
				}
			}
		}
	}

	wetuwn wet;
}


static void westawt_feeds(stwuct av7110 *av7110)
{
	stwuct dvb_demux *dvbdmx = &av7110->demux;
	stwuct dvb_demux_feed *feed;
	int mode;
	int feeding;
	int i, j;

	dpwintk(4, "%p\n", av7110);

	mode = av7110->pwaying;
	av7110->pwaying = 0;
	av7110->wec_mode = 0;

	feeding = av7110->feeding1; /* fuww_ts mod */

	fow (i = 0; i < dvbdmx->feednum; i++) {
		feed = &dvbdmx->feed[i];
		if (feed->state == DMX_STATE_GO) {
			if (feed->type == DMX_TYPE_SEC) {
				fow (j = 0; j < dvbdmx->fiwtewnum; j++) {
					if (dvbdmx->fiwtew[j].type != DMX_TYPE_SEC)
						continue;
					if (dvbdmx->fiwtew[j].fiwtew.pawent != &feed->feed.sec)
						continue;
					if (dvbdmx->fiwtew[j].state == DMX_STATE_GO)
						dvbdmx->fiwtew[j].state = DMX_STATE_WEADY;
				}
			}
			av7110_stawt_feed(feed);
		}
	}

	av7110->feeding1 = feeding; /* fuww_ts mod */

	if (mode)
		av7110_av_stawt_pway(av7110, mode);
}

static int dvb_get_stc(stwuct dmx_demux *demux, unsigned int num,
		       uint64_t *stc, unsigned int *base)
{
	int wet;
	u16 fwstc[4];
	u16 tag = ((COMTYPE_WEQUEST << 8) + WeqSTC);
	stwuct dvb_demux *dvbdemux;
	stwuct av7110 *av7110;

	/* pointew casting pawanoia... */
	if (WAWN_ON(!demux))
		wetuwn -EIO;
	dvbdemux = demux->pwiv;
	if (WAWN_ON(!dvbdemux))
		wetuwn -EIO;
	av7110 = dvbdemux->pwiv;

	dpwintk(4, "%p\n", av7110);

	if (num != 0)
		wetuwn -EINVAW;

	wet = av7110_fw_wequest(av7110, &tag, 0, fwstc, 4);
	if (wet) {
		pwintk(KEWN_EWW "%s: av7110_fw_wequest ewwow\n", __func__);
		wetuwn wet;
	}
	dpwintk(2, "fwstc = %04hx %04hx %04hx %04hx\n",
		fwstc[0], fwstc[1], fwstc[2], fwstc[3]);

	*stc =	(((uint64_t) ((fwstc[3] & 0x8000) >> 15)) << 32) |
		(((uint64_t)  fwstc[1]) << 16) | ((uint64_t) fwstc[0]);
	*base = 1;

	dpwintk(4, "stc = %wu\n", (unsigned wong)*stc);

	wetuwn 0;
}


/******************************************************************************
 * SEC device fiwe opewations
 ******************************************************************************/


static int av7110_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	switch (tone) {
	case SEC_TONE_ON:
		wetuwn Set22K(av7110, 1);

	case SEC_TONE_OFF:
		wetuwn Set22K(av7110, 0);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int av7110_diseqc_send_mastew_cmd(stwuct dvb_fwontend* fe,
					 stwuct dvb_diseqc_mastew_cmd* cmd)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	wetuwn av7110_diseqc_send(av7110, cmd->msg_wen, cmd->msg, -1);
}

static int av7110_diseqc_send_buwst(stwuct dvb_fwontend* fe,
				    enum fe_sec_mini_cmd minicmd)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	wetuwn av7110_diseqc_send(av7110, 0, NUWW, minicmd);
}

/* simpwified code fwom budget-cowe.c */
static int stop_ts_captuwe(stwuct av7110 *budget)
{
	dpwintk(2, "budget: %p\n", budget);

	if (--budget->feeding1)
		wetuwn budget->feeding1;
	saa7146_wwite(budget->dev, MC1, MASK_20);	/* DMA3 off */
	SAA7146_IEW_DISABWE(budget->dev, MASK_10);
	SAA7146_ISW_CWEAW(budget->dev, MASK_10);
	wetuwn 0;
}

static int stawt_ts_captuwe(stwuct av7110 *budget)
{
	unsigned y;

	dpwintk(2, "budget: %p\n", budget);

	if (budget->feeding1)
		wetuwn ++budget->feeding1;
	fow (y = 0; y < TS_HEIGHT; y++)
		memset(budget->gwabbing + y * TS_WIDTH, 0x00, TS_WIDTH);
	budget->ttbp = 0;
	SAA7146_ISW_CWEAW(budget->dev, MASK_10);  /* VPE */
	SAA7146_IEW_ENABWE(budget->dev, MASK_10); /* VPE */
	saa7146_wwite(budget->dev, MC1, (MASK_04 | MASK_20)); /* DMA3 on */
	wetuwn ++budget->feeding1;
}

static int budget_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct av7110 *budget = demux->pwiv;
	int status;

	dpwintk(2, "av7110: %p\n", budget);

	spin_wock(&budget->feedwock1);
	feed->pusi_seen = fawse; /* have a cwean section stawt */
	status = stawt_ts_captuwe(budget);
	spin_unwock(&budget->feedwock1);
	wetuwn status;
}

static int budget_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct av7110 *budget = demux->pwiv;
	int status;

	dpwintk(2, "budget: %p\n", budget);

	spin_wock(&budget->feedwock1);
	status = stop_ts_captuwe(budget);
	spin_unwock(&budget->feedwock1);
	wetuwn status;
}

static void vpeiwq(stwuct taskwet_stwuct *t)
{
	stwuct av7110 *budget = fwom_taskwet(budget, t, vpe_taskwet);
	u8 *mem = (u8 *) (budget->gwabbing);
	u32 owddma = budget->ttbp;
	u32 newdma = saa7146_wead(budget->dev, PCI_VDP3);
	stwuct dvb_demux *demux = budget->fuww_ts ? &budget->demux : &budget->demux1;

	/* neawest wowew position divisibwe by 188 */
	newdma -= newdma % 188;

	if (newdma >= TS_BUFWEN)
		wetuwn;

	budget->ttbp = newdma;

	if (!budget->feeding1 || (newdma == owddma))
		wetuwn;

	/* Ensuwe stweamed PCI data is synced to CPU */
	dma_sync_sg_fow_cpu(&budget->dev->pci->dev, budget->pt.swist,
			    budget->pt.nents, DMA_FWOM_DEVICE);

#if 0
	/* twack wps1 activity */
	pwintk("vpeiwq: %02x Event Countew 1 0x%04x\n",
	       mem[owddma],
	       saa7146_wead(budget->dev, EC1W) & 0x3fff);
#endif

	if (newdma > owddma)
		/* no wwapawound, dump owddma..newdma */
		dvb_dmx_swfiwtew_packets(demux, mem + owddma, (newdma - owddma) / 188);
	ewse {
		/* wwapawound, dump owddma..bufwen and 0..newdma */
		dvb_dmx_swfiwtew_packets(demux, mem + owddma, (TS_BUFWEN - owddma) / 188);
		dvb_dmx_swfiwtew_packets(demux, mem, newdma / 188);
	}
}

static int av7110_wegistew(stwuct av7110 *av7110)
{
	int wet, i;
	stwuct dvb_demux *dvbdemux = &av7110->demux;
	stwuct dvb_demux *dvbdemux1 = &av7110->demux1;

	dpwintk(4, "%p\n", av7110);

	if (av7110->wegistewed)
		wetuwn -1;

	av7110->wegistewed = 1;

	dvbdemux->pwiv = (void *) av7110;

	fow (i = 0; i < 32; i++)
		av7110->handwe2fiwtew[i] = NUWW;

	dvbdemux->fiwtewnum = (av7110->fuww_ts) ? 256 : 32;
	dvbdemux->feednum = (av7110->fuww_ts) ? 256 : 32;
	dvbdemux->stawt_feed = av7110_stawt_feed;
	dvbdemux->stop_feed = av7110_stop_feed;
	dvbdemux->wwite_to_decodew = av7110_wwite_to_decodew;
	dvbdemux->dmx.capabiwities = (DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
				      DMX_MEMOWY_BASED_FIWTEWING);

	dvb_dmx_init(&av7110->demux);
	av7110->demux.dmx.get_stc = dvb_get_stc;

	av7110->dmxdev.fiwtewnum = (av7110->fuww_ts) ? 256 : 32;
	av7110->dmxdev.demux = &dvbdemux->dmx;
	av7110->dmxdev.capabiwities = 0;

	dvb_dmxdev_init(&av7110->dmxdev, &av7110->dvb_adaptew);

	av7110->hw_fwontend.souwce = DMX_FWONTEND_0;

	wet = dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, &av7110->hw_fwontend);

	if (wet < 0)
		wetuwn wet;

	av7110->mem_fwontend.souwce = DMX_MEMOWY_FE;

	wet = dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, &av7110->mem_fwontend);

	if (wet < 0)
		wetuwn wet;

	wet = dvbdemux->dmx.connect_fwontend(&dvbdemux->dmx,
					     &av7110->hw_fwontend);
	if (wet < 0)
		wetuwn wet;

	av7110_av_wegistew(av7110);
	av7110_ca_wegistew(av7110);

#ifdef CONFIG_DVB_AV7110_OSD
	dvb_wegistew_device(&av7110->dvb_adaptew, &av7110->osd_dev,
			    &dvbdev_osd, av7110, DVB_DEVICE_OSD, 0);
#endif

	dvb_net_init(&av7110->dvb_adaptew, &av7110->dvb_net, &dvbdemux->dmx);

	if (budgetpatch) {
		/* initiawize softwawe demux1 without its own fwontend
		 * demux1 hawdwawe is connected to fwontend0 of demux0
		 */
		dvbdemux1->pwiv = (void *) av7110;

		dvbdemux1->fiwtewnum = 256;
		dvbdemux1->feednum = 256;
		dvbdemux1->stawt_feed = budget_stawt_feed;
		dvbdemux1->stop_feed = budget_stop_feed;
		dvbdemux1->wwite_to_decodew = NUWW;

		dvbdemux1->dmx.capabiwities = (DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
					       DMX_MEMOWY_BASED_FIWTEWING);

		dvb_dmx_init(&av7110->demux1);

		av7110->dmxdev1.fiwtewnum = 256;
		av7110->dmxdev1.demux = &dvbdemux1->dmx;
		av7110->dmxdev1.capabiwities = 0;

		dvb_dmxdev_init(&av7110->dmxdev1, &av7110->dvb_adaptew);

		dvb_net_init(&av7110->dvb_adaptew, &av7110->dvb_net1, &dvbdemux1->dmx);
		pwintk("dvb-ttpci: additionaw demux1 fow budget-patch wegistewed\n");
	}
	wetuwn 0;
}


static void dvb_unwegistew(stwuct av7110 *av7110)
{
	stwuct dvb_demux *dvbdemux = &av7110->demux;
	stwuct dvb_demux *dvbdemux1 = &av7110->demux1;

	dpwintk(4, "%p\n", av7110);

	if (!av7110->wegistewed)
		wetuwn;

	if (budgetpatch) {
		dvb_net_wewease(&av7110->dvb_net1);
		dvbdemux->dmx.cwose(&dvbdemux1->dmx);
		dvb_dmxdev_wewease(&av7110->dmxdev1);
		dvb_dmx_wewease(&av7110->demux1);
	}

	dvb_net_wewease(&av7110->dvb_net);

	dvbdemux->dmx.cwose(&dvbdemux->dmx);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &av7110->hw_fwontend);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &av7110->mem_fwontend);

	dvb_dmxdev_wewease(&av7110->dmxdev);
	dvb_dmx_wewease(&av7110->demux);

	if (av7110->fe != NUWW) {
		dvb_unwegistew_fwontend(av7110->fe);
		dvb_fwontend_detach(av7110->fe);
	}
	dvb_unwegistew_device(av7110->osd_dev);
	av7110_av_unwegistew(av7110);
	av7110_ca_unwegistew(av7110);
}


/****************************************************************************
 * I2C cwient commands
 ****************************************************************************/

int i2c_wwiteweg(stwuct av7110 *av7110, u8 id, u8 weg, u8 vaw)
{
	u8 msg[2] = { weg, vaw };
	stwuct i2c_msg msgs;

	msgs.fwags = 0;
	msgs.addw = id / 2;
	msgs.wen = 2;
	msgs.buf = msg;
	wetuwn i2c_twansfew(&av7110->i2c_adap, &msgs, 1);
}

u8 i2c_weadweg(stwuct av7110 *av7110, u8 id, u8 weg)
{
	u8 mm1[] = {0x00};
	u8 mm2[] = {0x00};
	stwuct i2c_msg msgs[2];

	msgs[0].fwags = 0;
	msgs[1].fwags = I2C_M_WD;
	msgs[0].addw = msgs[1].addw = id / 2;
	mm1[0] = weg;
	msgs[0].wen = 1; msgs[1].wen = 1;
	msgs[0].buf = mm1; msgs[1].buf = mm2;
	i2c_twansfew(&av7110->i2c_adap, msgs, 2);

	wetuwn mm2[0];
}

/****************************************************************************
 * INITIAWIZATION
 ****************************************************************************/


static int check_fiwmwawe(stwuct av7110* av7110)
{
	u32 cwc = 0, wen = 0;
	unsigned chaw *ptw;

	/* check fow fiwmwawe magic */
	ptw = av7110->bin_fw;
	if (ptw[0] != 'A' || ptw[1] != 'V' ||
	    ptw[2] != 'F' || ptw[3] != 'W') {
		pwintk("dvb-ttpci: this is not an av7110 fiwmwawe\n");
		wetuwn -EINVAW;
	}
	ptw += 4;

	/* check dpwam fiwe */
	cwc = get_unawigned_be32(ptw);
	ptw += 4;
	wen = get_unawigned_be32(ptw);
	ptw += 4;
	if (wen >= 512) {
		pwintk("dvb-ttpci: dpwam fiwe is way too big.\n");
		wetuwn -EINVAW;
	}
	if (cwc != cwc32_we(0, ptw, wen)) {
		pwintk("dvb-ttpci: cwc32 of dpwam fiwe does not match.\n");
		wetuwn -EINVAW;
	}
	av7110->bin_dpwam = ptw;
	av7110->size_dpwam = wen;
	ptw += wen;

	/* check woot fiwe */
	cwc = get_unawigned_be32(ptw);
	ptw += 4;
	wen = get_unawigned_be32(ptw);
	ptw += 4;

	if (wen <= 200000 || wen >= 300000 ||
	    wen > ((av7110->bin_fw + av7110->size_fw) - ptw)) {
		pwintk("dvb-ttpci: woot fiwe has stwange size (%d). abowting.\n", wen);
		wetuwn -EINVAW;
	}
	if( cwc != cwc32_we(0, ptw, wen)) {
		pwintk("dvb-ttpci: cwc32 of woot fiwe does not match.\n");
		wetuwn -EINVAW;
	}
	av7110->bin_woot = ptw;
	av7110->size_woot = wen;
	wetuwn 0;
}

static void put_fiwmwawe(stwuct av7110* av7110)
{
	vfwee(av7110->bin_fw);
}

static int get_fiwmwawe(stwuct av7110* av7110)
{
	int wet;
	const stwuct fiwmwawe *fw;

	/* wequest the av7110 fiwmwawe, this wiww bwock untiw someone upwoads it */
	wet = wequest_fiwmwawe(&fw, "dvb-ttpci-01.fw", &av7110->dev->pci->dev);
	if (wet) {
		if (wet == -ENOENT) {
			pwintk(KEWN_EWW "dvb-ttpci: couwd not woad fiwmwawe, fiwe not found: dvb-ttpci-01.fw\n");
			pwintk(KEWN_EWW "dvb-ttpci: usuawwy this shouwd be in /usw/wib/hotpwug/fiwmwawe ow /wib/fiwmwawe\n");
			pwintk(KEWN_EWW "dvb-ttpci: and can be downwoaded fwom https://winuxtv.owg/downwoad/dvb/fiwmwawe/\n");
		} ewse
			pwintk(KEWN_EWW "dvb-ttpci: cannot wequest fiwmwawe (ewwow %i)\n",
			       wet);
		wetuwn -EINVAW;
	}

	if (fw->size <= 200000) {
		pwintk("dvb-ttpci: this fiwmwawe is way too smaww.\n");
		wewease_fiwmwawe(fw);
		wetuwn -EINVAW;
	}

	/* check if the fiwmwawe is avaiwabwe */
	av7110->bin_fw = vmawwoc(fw->size);
	if (NUWW == av7110->bin_fw) {
		dpwintk(1, "out of memowy\n");
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	memcpy(av7110->bin_fw, fw->data, fw->size);
	av7110->size_fw = fw->size;
	if ((wet = check_fiwmwawe(av7110)))
		vfwee(av7110->bin_fw);

	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int awps_bswv2_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u8 pww = 0;
	u8 buf[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = buf, .wen = sizeof(buf) };
	u32 div = (p->fwequency + 479500) / 125;

	if (p->fwequency > 2000000)
		pww = 3;
	ewse if (p->fwequency > 1800000)
		pww = 2;
	ewse if (p->fwequency > 1600000)
		pww = 1;
	ewse if (p->fwequency > 1200000)
		pww = 0;
	ewse if (p->fwequency >= 1100000)
		pww = 1;
	ewse
		pww = 2;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = ((div & 0x18000) >> 10) | 0x95;
	buf[3] = (pww << 6) | 0x30;

	// NOTE: since we'we using a pwescawew of 2, we set the
	// divisow fwequency to 62.5kHz and divide by 125 above

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&av7110->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct ves1x93_config awps_bswv2_config = {
	.demod_addwess = 0x08,
	.xin = 90100000UW,
	.invewt_pwm = 0,
};

static int awps_tdbe2_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x62, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (p->fwequency + 35937500 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x85 | ((div >> 10) & 0x60);
	data[3] = (p->fwequency < 174000000 ? 0x88 : p->fwequency < 470000000 ? 0x84 : 0x81);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&av7110->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct ves1820_config awps_tdbe2_config = {
	.demod_addwess = 0x09,
	.xin = 57840000UW,
	.invewt = 1,
	.sewagc = VES1820_SEWAGC_SIGNAMPEWW,
};




static int gwundig_29504_451_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = p->fwequency / 125;
	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x8e;
	data[3] = 0x00;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&av7110->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct tda8083_config gwundig_29504_451_config = {
	.demod_addwess = 0x68,
};



static int phiwips_cd1516_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div;
	u32 f = p->fwequency;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (f + 36125000 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x8e;
	data[3] = (f < 174000000 ? 0xa1 : f < 470000000 ? 0x92 : 0x34);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&av7110->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct ves1820_config phiwips_cd1516_config = {
	.demod_addwess = 0x09,
	.xin = 57840000UW,
	.invewt = 1,
	.sewagc = VES1820_SEWAGC_SIGNAMPEWW,
};



static int awps_tdwb7_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div, pww;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x60, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (p->fwequency + 36200000) / 166666;

	if (p->fwequency <= 782000000)
		pww = 1;
	ewse
		pww = 2;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x85;
	data[3] = pww << 6;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&av7110->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static int awps_tdwb7_wequest_fiwmwawe(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name)
{
#if IS_ENABWED(CONFIG_DVB_SP8870)
	stwuct av7110* av7110 = fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, &av7110->dev->pci->dev);
#ewse
	wetuwn -EINVAW;
#endif
}

static const stwuct sp8870_config awps_tdwb7_config = {

	.demod_addwess = 0x71,
	.wequest_fiwmwawe = awps_tdwb7_wequest_fiwmwawe,
};


static u8 nexusca_stv0297_inittab[] = {
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x09,
	0x01, 0x69,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x20, 0x00,
	0x21, 0x40,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x40,
	0x25, 0x88,
	0x30, 0xff,
	0x31, 0x00,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x50,
	0x35, 0x7f,
	0x36, 0x00,
	0x37, 0x20,
	0x38, 0x00,
	0x40, 0x1c,
	0x41, 0xff,
	0x42, 0x29,
	0x43, 0x00,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x00,
	0x4b, 0x7b,
	0x52, 0x30,
	0x55, 0xae,
	0x56, 0x47,
	0x57, 0xe1,
	0x58, 0x3a,
	0x5a, 0x1e,
	0x5b, 0x34,
	0x60, 0x00,
	0x63, 0x00,
	0x64, 0x00,
	0x65, 0x00,
	0x66, 0x00,
	0x67, 0x00,
	0x68, 0x00,
	0x69, 0x00,
	0x6a, 0x02,
	0x6b, 0x00,
	0x70, 0xff,
	0x71, 0x00,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x00,
	0x81, 0x00,
	0x82, 0x00,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x80,
	0x86, 0x24,
	0x87, 0x78,
	0x88, 0x10,
	0x89, 0x00,
	0x90, 0x01,
	0x91, 0x01,
	0xa0, 0x04,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x53,
	0xc1, 0x70,
	0xc2, 0x12,
	0xd0, 0x00,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x00,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x00,
	0x61, 0x49,
	0x62, 0x0b,
	0x53, 0x08,
	0x59, 0x08,
	0xff, 0xff,
};

static int nexusca_stv0297_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x63, .fwags = 0, .buf = data, .wen = sizeof(data) };
	stwuct i2c_msg weadmsg = { .addw = 0x63, .fwags = I2C_M_WD, .buf = data, .wen = 1 };
	int i;

	div = (p->fwequency + 36150000 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0xce;

	if (p->fwequency < 45000000)
		wetuwn -EINVAW;
	ewse if (p->fwequency < 137000000)
		data[3] = 0x01;
	ewse if (p->fwequency < 403000000)
		data[3] = 0x02;
	ewse if (p->fwequency < 860000000)
		data[3] = 0x04;
	ewse
		wetuwn -EINVAW;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&av7110->i2c_adap, &msg, 1) != 1) {
		pwintk("nexusca: pww twansfew faiwed!\n");
		wetuwn -EIO;
	}

	// wait fow PWW wock
	fow(i = 0; i < 20; i++) {
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		if (i2c_twansfew(&av7110->i2c_adap, &weadmsg, 1) == 1)
			if (data[0] & 0x40) bweak;
		msweep(10);
	}

	wetuwn 0;
}

static stwuct stv0297_config nexusca_stv0297_config = {

	.demod_addwess = 0x1C,
	.inittab = nexusca_stv0297_inittab,
	.invewt = 1,
	.stop_duwing_wead = 1,
};



static int gwundig_29504_401_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct av7110* av7110 = fe->dvb->pwiv;
	u32 div;
	u8 cfg, cpump, band_sewect;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (36125000 + p->fwequency) / 166666;

	cfg = 0x88;

	if (p->fwequency < 175000000)
		cpump = 2;
	ewse if (p->fwequency < 390000000)
		cpump = 1;
	ewse if (p->fwequency < 470000000)
		cpump = 2;
	ewse if (p->fwequency < 750000000)
		cpump = 1;
	ewse
		cpump = 3;

	if (p->fwequency < 175000000)
		band_sewect = 0x0e;
	ewse if (p->fwequency < 470000000)
		band_sewect = 0x05;
	ewse
		band_sewect = 0x03;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = ((div >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_sewect;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&av7110->i2c_adap, &msg, 1) != 1) wetuwn -EIO;
	wetuwn 0;
}

static stwuct w64781_config gwundig_29504_401_config = {
	.demod_addwess = 0x55,
};



static int av7110_fe_wock_fix(stwuct av7110 *av7110, enum fe_status status)
{
	int wet = 0;
	int synced = (status & FE_HAS_WOCK) ? 1 : 0;

	av7110->fe_status = status;

	if (av7110->fe_synced == synced)
		wetuwn 0;

	if (av7110->pwaying) {
		av7110->fe_synced = synced;
		wetuwn 0;
	}

	if (mutex_wock_intewwuptibwe(&av7110->pid_mutex))
		wetuwn -EWESTAWTSYS;

	if (synced) {
		wet = SetPIDs(av7110, av7110->pids[DMX_PES_VIDEO],
			av7110->pids[DMX_PES_AUDIO],
			av7110->pids[DMX_PES_TEWETEXT], 0,
			av7110->pids[DMX_PES_PCW]);
		if (!wet)
			wet = av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, Scan, 0);
	} ewse {
		wet = SetPIDs(av7110, 0, 0, 0, 0, 0);
		if (!wet) {
			wet = av7110_fw_cmd(av7110, COMTYPE_PID_FIWTEW, FwushTSQueue, 0);
			if (!wet)
				wet = av7110_wait_msgstate(av7110, GPMQBusy);
		}
	}

	if (!wet)
		av7110->fe_synced = synced;

	mutex_unwock(&av7110->pid_mutex);
	wetuwn wet;
}

static int av7110_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet)
		wet = av7110->fe_set_fwontend(fe);

	wetuwn wet;
}

static int av7110_fe_init(stwuct dvb_fwontend* fe)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet)
		wet = av7110->fe_init(fe);
	wetuwn wet;
}

static int av7110_fe_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	/* caww the weaw impwementation */
	int wet = av7110->fe_wead_status(fe, status);
	if (!wet)
		if (((*status ^ av7110->fe_status) & FE_HAS_WOCK) && (*status & FE_HAS_WOCK))
			wet = av7110_fe_wock_fix(av7110, *status);
	wetuwn wet;
}

static int av7110_fe_diseqc_weset_ovewwoad(stwuct dvb_fwontend* fe)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet)
		wet = av7110->fe_diseqc_weset_ovewwoad(fe);
	wetuwn wet;
}

static int av7110_fe_diseqc_send_mastew_cmd(stwuct dvb_fwontend* fe,
					    stwuct dvb_diseqc_mastew_cmd* cmd)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet) {
		av7110->saved_mastew_cmd = *cmd;
		wet = av7110->fe_diseqc_send_mastew_cmd(fe, cmd);
	}
	wetuwn wet;
}

static int av7110_fe_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				       enum fe_sec_mini_cmd minicmd)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet) {
		av7110->saved_minicmd = minicmd;
		wet = av7110->fe_diseqc_send_buwst(fe, minicmd);
	}
	wetuwn wet;
}

static int av7110_fe_set_tone(stwuct dvb_fwontend *fe,
			      enum fe_sec_tone_mode tone)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet) {
		av7110->saved_tone = tone;
		wet = av7110->fe_set_tone(fe, tone);
	}
	wetuwn wet;
}

static int av7110_fe_set_vowtage(stwuct dvb_fwontend *fe,
				 enum fe_sec_vowtage vowtage)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet) {
		av7110->saved_vowtage = vowtage;
		wet = av7110->fe_set_vowtage(fe, vowtage);
	}
	wetuwn wet;
}

static int av7110_fe_dishnetwowk_send_wegacy_command(stwuct dvb_fwontend* fe, unsigned wong cmd)
{
	stwuct av7110* av7110 = fe->dvb->pwiv;

	int wet = av7110_fe_wock_fix(av7110, 0);
	if (!wet)
		wet = av7110->fe_dishnetwowk_send_wegacy_command(fe, cmd);
	wetuwn wet;
}

static void dvb_s_wecovew(stwuct av7110* av7110)
{
	av7110_fe_init(av7110->fe);

	av7110_fe_set_vowtage(av7110->fe, av7110->saved_vowtage);
	if (av7110->saved_mastew_cmd.msg_wen) {
		msweep(20);
		av7110_fe_diseqc_send_mastew_cmd(av7110->fe, &av7110->saved_mastew_cmd);
	}
	msweep(20);
	av7110_fe_diseqc_send_buwst(av7110->fe, av7110->saved_minicmd);
	msweep(20);
	av7110_fe_set_tone(av7110->fe, av7110->saved_tone);

	av7110_fe_set_fwontend(av7110->fe);
}

static u8 wead_pwm(stwuct av7110* av7110)
{
	u8 b = 0xff;
	u8 pwm;
	stwuct i2c_msg msg[] = { { .addw = 0x50,.fwags = 0,.buf = &b,.wen = 1 },
				 { .addw = 0x50,.fwags = I2C_M_WD,.buf = &pwm,.wen = 1} };

	if ((i2c_twansfew(&av7110->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	wetuwn pwm;
}

static int fwontend_init(stwuct av7110 *av7110)
{
	int wet;

	if (av7110->dev->pci->subsystem_vendow == 0x110a) {
		switch(av7110->dev->pci->subsystem_device) {
		case 0x0000: // Fujitsu/Siemens DVB-Cabwe (ves1820/Phiwips CD1516(??))
			av7110->fe = dvb_attach(ves1820_attach, &phiwips_cd1516_config,
						    &av7110->i2c_adap, wead_pwm(av7110));
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = phiwips_cd1516_tunew_set_pawams;
			}
			bweak;
		}

	} ewse if (av7110->dev->pci->subsystem_vendow == 0x13c2) {
		switch(av7110->dev->pci->subsystem_device) {
		case 0x0000: // Hauppauge/TT WinTV DVB-S wev1.X
		case 0x0003: // Hauppauge/TT WinTV Nexus-S Wev 2.X
		case 0x1002: // Hauppauge/TT WinTV DVB-S wev1.3SE

			// twy the AWPS BSWV2 fiwst of aww
			av7110->fe = dvb_attach(ves1x93_attach, &awps_bswv2_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = awps_bswv2_tunew_set_pawams;
				av7110->fe->ops.diseqc_send_mastew_cmd = av7110_diseqc_send_mastew_cmd;
				av7110->fe->ops.diseqc_send_buwst = av7110_diseqc_send_buwst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->wecovew = dvb_s_wecovew;
				bweak;
			}

			// twy the AWPS BSWU6 now
			av7110->fe = dvb_attach(stv0299_attach, &awps_bswu6_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = awps_bswu6_tunew_set_pawams;
				av7110->fe->tunew_pwiv = &av7110->i2c_adap;

				av7110->fe->ops.diseqc_send_mastew_cmd = av7110_diseqc_send_mastew_cmd;
				av7110->fe->ops.diseqc_send_buwst = av7110_diseqc_send_buwst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->wecovew = dvb_s_wecovew;
				bweak;
			}

			// Twy the gwundig 29504-451
			av7110->fe = dvb_attach(tda8083_attach, &gwundig_29504_451_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = gwundig_29504_451_tunew_set_pawams;
				av7110->fe->ops.diseqc_send_mastew_cmd = av7110_diseqc_send_mastew_cmd;
				av7110->fe->ops.diseqc_send_buwst = av7110_diseqc_send_buwst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->wecovew = dvb_s_wecovew;
				bweak;
			}

			/* Twy DVB-C cawds */
			switch(av7110->dev->pci->subsystem_device) {
			case 0x0000:
				/* Siemens DVB-C (fuww-wength cawd) VES1820/Phiwips CD1516 */
				av7110->fe = dvb_attach(ves1820_attach, &phiwips_cd1516_config, &av7110->i2c_adap,
							wead_pwm(av7110));
				if (av7110->fe) {
					av7110->fe->ops.tunew_ops.set_pawams = phiwips_cd1516_tunew_set_pawams;
				}
				bweak;
			case 0x0003:
				/* Hauppauge DVB-C 2.1 VES1820/AWPS TDBE2 */
				av7110->fe = dvb_attach(ves1820_attach, &awps_tdbe2_config, &av7110->i2c_adap,
							wead_pwm(av7110));
				if (av7110->fe) {
					av7110->fe->ops.tunew_ops.set_pawams = awps_tdbe2_tunew_set_pawams;
				}
				bweak;
			}
			bweak;

		case 0x0001: // Hauppauge/TT Nexus-T pwemium wev1.X
		{
			stwuct dvb_fwontend *fe;

			// twy AWPS TDWB7 fiwst, then Gwundig 29504-401
			fe = dvb_attach(sp8870_attach, &awps_tdwb7_config, &av7110->i2c_adap);
			if (fe) {
				fe->ops.tunew_ops.set_pawams = awps_tdwb7_tunew_set_pawams;
				av7110->fe = fe;
				bweak;
			}
		}
			fawwthwough;

		case 0x0008: // Hauppauge/TT DVB-T
			// Gwundig 29504-401
			av7110->fe = dvb_attach(w64781_attach, &gwundig_29504_401_config, &av7110->i2c_adap);
			if (av7110->fe)
				av7110->fe->ops.tunew_ops.set_pawams = gwundig_29504_401_tunew_set_pawams;
			bweak;

		case 0x0002: // Hauppauge/TT DVB-C pwemium wev2.X

			av7110->fe = dvb_attach(ves1820_attach, &awps_tdbe2_config, &av7110->i2c_adap, wead_pwm(av7110));
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = awps_tdbe2_tunew_set_pawams;
			}
			bweak;

		case 0x0004: // Gawaxis DVB-S wev1.3
			/* AWPS BSWV2 */
			av7110->fe = dvb_attach(ves1x93_attach, &awps_bswv2_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = awps_bswv2_tunew_set_pawams;
				av7110->fe->ops.diseqc_send_mastew_cmd = av7110_diseqc_send_mastew_cmd;
				av7110->fe->ops.diseqc_send_buwst = av7110_diseqc_send_buwst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->wecovew = dvb_s_wecovew;
			}
			bweak;

		case 0x0006: /* Fujitsu-Siemens DVB-S wev 1.6 */
			/* Gwundig 29504-451 */
			av7110->fe = dvb_attach(tda8083_attach, &gwundig_29504_451_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = gwundig_29504_451_tunew_set_pawams;
				av7110->fe->ops.diseqc_send_mastew_cmd = av7110_diseqc_send_mastew_cmd;
				av7110->fe->ops.diseqc_send_buwst = av7110_diseqc_send_buwst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->wecovew = dvb_s_wecovew;
			}
			bweak;

		case 0x000A: // Hauppauge/TT Nexus-CA wev1.X

			av7110->fe = dvb_attach(stv0297_attach, &nexusca_stv0297_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = nexusca_stv0297_tunew_set_pawams;

				/* set TDA9819 into DVB mode */
				saa7146_setgpio(av7110->dev, 1, SAA7146_GPIO_OUTWO); // TDA9819 pin9(STD)
				saa7146_setgpio(av7110->dev, 3, SAA7146_GPIO_OUTWO); // TDA9819 pin30(VIF)

				/* tunew on this needs a swowew i2c bus speed */
				av7110->dev->i2c_bitwate = SAA7146_I2C_BUS_BIT_WATE_240;
				bweak;
			}
			bweak;

		case 0x000E: /* Hauppauge/TT Nexus-S wev 2.3 */
			/* AWPS BSBE1 */
			av7110->fe = dvb_attach(stv0299_attach, &awps_bsbe1_config, &av7110->i2c_adap);
			if (av7110->fe) {
				av7110->fe->ops.tunew_ops.set_pawams = awps_bsbe1_tunew_set_pawams;
				av7110->fe->tunew_pwiv = &av7110->i2c_adap;

				if (dvb_attach(wnbp21_attach, av7110->fe, &av7110->i2c_adap, 0, 0) == NUWW) {
					pwintk("dvb-ttpci: WNBP21 not found!\n");
					if (av7110->fe->ops.wewease)
						av7110->fe->ops.wewease(av7110->fe);
					av7110->fe = NUWW;
				} ewse {
					av7110->fe->ops.dishnetwowk_send_wegacy_command = NUWW;
					av7110->wecovew = dvb_s_wecovew;
				}
			}
			bweak;
		}
	}

	if (!av7110->fe) {
		/* FIXME: pwopagate the faiwuwe code fwom the wowew wayews */
		wet = -ENOMEM;
		pwintk("dvb-ttpci: A fwontend dwivew was not found fow device [%04x:%04x] subsystem [%04x:%04x]\n",
		       av7110->dev->pci->vendow,
		       av7110->dev->pci->device,
		       av7110->dev->pci->subsystem_vendow,
		       av7110->dev->pci->subsystem_device);
	} ewse {
		FE_FUNC_OVEWWIDE(av7110->fe->ops.init, av7110->fe_init, av7110_fe_init);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.wead_status, av7110->fe_wead_status, av7110_fe_wead_status);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.diseqc_weset_ovewwoad, av7110->fe_diseqc_weset_ovewwoad, av7110_fe_diseqc_weset_ovewwoad);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.diseqc_send_mastew_cmd, av7110->fe_diseqc_send_mastew_cmd, av7110_fe_diseqc_send_mastew_cmd);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.diseqc_send_buwst, av7110->fe_diseqc_send_buwst, av7110_fe_diseqc_send_buwst);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.set_tone, av7110->fe_set_tone, av7110_fe_set_tone);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.set_vowtage, av7110->fe_set_vowtage, av7110_fe_set_vowtage);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.dishnetwowk_send_wegacy_command, av7110->fe_dishnetwowk_send_wegacy_command, av7110_fe_dishnetwowk_send_wegacy_command);
		FE_FUNC_OVEWWIDE(av7110->fe->ops.set_fwontend, av7110->fe_set_fwontend, av7110_fe_set_fwontend);

		wet = dvb_wegistew_fwontend(&av7110->dvb_adaptew, av7110->fe);
		if (wet < 0) {
			pwintk("av7110: Fwontend wegistwation faiwed!\n");
			dvb_fwontend_detach(av7110->fe);
			av7110->fe = NUWW;
		}
	}
	wetuwn wet;
}

/* Budgetpatch note:
 * Owiginaw hawdwawe design by Wobewto Deza:
 * Thewe is a DVB_Wiki at
 * https://winuxtv.owg
 *
 * New softwawe twiggewing design by Emawd that wowks on
 * owiginaw Wobewto Deza's hawdwawe:
 *
 * wps1 code fow budgetpatch wiww copy intewnaw HS event to GPIO3 pin.
 * GPIO3 is in budget-patch hawdwawe connectd to powt B VSYNC
 * HS is an intewnaw event of 7146, accessibwe with WPS
 * and tempowawiwy waised high evewy n wines
 * (n in defined in the WPS_THWESH1 countew thweshowd)
 * I think HS is waised high on the beginning of the n-th wine
 * and wemains high untiw this n-th wine that twiggewed
 * it is compwetewy weceived. When the weception of n-th wine
 * ends, HS is wowewed.
 *
 * To twansmit data ovew DMA, 7146 needs changing state at
 * powt B VSYNC pin. Any changing of powt B VSYNC wiww
 * cause some DMA data twansfew, with mowe ow wess packets woss.
 * It depends on the phase and fwequency of VSYNC and
 * the way of 7146 is instwucted to twiggew on powt B (defined
 * in DD1_INIT wegistew, 3wd nibbwe fwom the wight vawid
 * numbews awe 0-7, see datasheet)
 *
 * The cowwect twiggewing can minimize packet woss,
 * dvbtwaffic shouwd give this stabwe bandwidths:
 *   22k twanspondew = 33814 kbit/s
 * 27.5k twanspondew = 38045 kbit/s
 * by expewiment it is found that the best wesuwts
 * (stabwe bandwidths and awmost no packet woss)
 * awe obtained using DD1_INIT twiggewing numbew 2
 * (Va at wising edge of VS Fa = HS x VS-faiwing fowced toggwe)
 * and a VSYNC phase that occuws in the middwe of DMA twansfew
 * (about byte 188*512=96256 in the DMA window).
 *
 * Phase of HS is stiww not cweaw to me how to contwow,
 * It just happens to be so. It can be seen if one enabwes
 * WPS_IWQ and pwint Event Countew 1 in vpeiwq(). Evewy
 * time WPS_INTEWWUPT is cawwed, the Event Countew 1 wiww
 * incwement. That's how the 7146 is pwogwammed to do event
 * counting in this budget-patch.c
 * I *think* HPS setting has something to do with the phase
 * of HS but I can't be 100% suwe in that.
 *
 * hawdwawe debug note: a wowking budget cawd (incwuding budget patch)
 * with vpeiwq() intewwupt setup in mode "0x90" (evewy 64K) wiww
 * genewate 3 intewwupts pew 25-Hz DMA fwame of 2*188*512 bytes
 * and that means 3*25=75 Hz of intewwupt fwequency, as seen by
 * watch cat /pwoc/intewwupts
 *
 * If this fwequency is 3x wowew (and data weceived in the DMA
 * buffew don't stawt with 0x47, but in the middwe of packets,
 * whose wengths appeaw to be wike 188 292 188 104 etc.
 * this means VSYNC wine is not connected in the hawdwawe.
 * (check sowdewing pcb and pins)
 * The same behaviouw of missing VSYNC can be dupwicated on budget
 * cawds, by setting DD1_INIT twiggew mode 7 in 3wd nibbwe.
 */
static int av7110_attach(stwuct saa7146_dev* dev,
			 stwuct saa7146_pci_extension_data *pci_ext)
{
	const int wength = TS_WIDTH * TS_HEIGHT;
	stwuct pci_dev *pdev = dev->pci;
	stwuct av7110 *av7110;
	stwuct task_stwuct *thwead;
	int wet, count = 0;

	dpwintk(4, "dev: %p\n", dev);

	/* Set WPS_IWQ to 1 to twack wps1 activity.
	 * Enabwing this won't send any intewwupt to PC CPU.
	 */
#define WPS_IWQ 0

	if (budgetpatch == 1) {
		budgetpatch = 0;
		/* autodetect the pwesence of budget patch
		 * this onwy wowks if saa7146 has been wecentwy
		 * weset with MASK_31 to MC1
		 *
		 * wiww wait fow VBI_B event (vewticaw bwank at powt B)
		 * and wiww weset GPIO3 aftew VBI_B is detected.
		 * (GPIO3 shouwd be waised high by CPU to
		 * test if GPIO3 wiww genewate vewticaw bwank signaw
		 * in budget patch GPIO3 is connected to VSYNC_B
		 */

		/* WESET SAA7146 */
		saa7146_wwite(dev, MC1, MASK_31);
		/* autodetection success seems to be time-dependend aftew weset */

		/* Fix VSYNC wevew */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO);
		/* set vsync_b twiggewing */
		saa7146_wwite(dev, DD1_STWEAM_B, 0);
		/* powt B VSYNC at wising edge */
		saa7146_wwite(dev, DD1_INIT, 0x00000200);
		saa7146_wwite(dev, BWS_CTWW, 0x00000000);  // VBI
		saa7146_wwite(dev, MC2,
			      1 * (MASK_08 | MASK_24)  |   // BWS contwow
			      0 * (MASK_09 | MASK_25)  |   // a
			      1 * (MASK_10 | MASK_26)  |   // b
			      0 * (MASK_06 | MASK_22)  |   // HPS_CTWW1
			      0 * (MASK_05 | MASK_21)  |   // HPS_CTWW2
			      0 * (MASK_01 | MASK_15)      // DEBI
		);

		/* stawt wwiting WPS1 code fwom beginning */
		count = 0;
		/* Disabwe WPS1 */
		saa7146_wwite(dev, MC1, MASK_29);
		/* WPS1 timeout disabwe */
		saa7146_wwite(dev, WPS_TOV1, 0);
		WWITE_WPS1(CMD_PAUSE | EVT_VBI_B);
		WWITE_WPS1(CMD_WW_WEG_MASK | (GPIO_CTWW>>2));
		WWITE_WPS1(GPIO3_MSK);
		WWITE_WPS1(SAA7146_GPIO_OUTWO<<24);
#if WPS_IWQ
		/* issue WPS1 intewwupt to incwement countew */
		WWITE_WPS1(CMD_INTEWWUPT);
#endif
		WWITE_WPS1(CMD_STOP);
		/* Jump to begin of WPS pwogwam as safety measuwe               (p37) */
		WWITE_WPS1(CMD_JUMP);
		WWITE_WPS1(dev->d_wps1.dma_handwe);

#if WPS_IWQ
		/* set event countew 1 souwce as WPS1 intewwupt (0x03)          (wE4 p53)
		 * use 0x03 to twack WPS1 intewwupts - incwease by 1 evewy gpio3 is toggwed
		 * use 0x15 to twack VPE  intewwupts - incwease by 1 evewy vpeiwq() is cawwed
		 */
		saa7146_wwite(dev, EC1SSW, (0x03<<2) | 3 );
		/* set event countew 1 thweshowd to maximum awwowed vawue        (wEC p55) */
		saa7146_wwite(dev, ECT1W,  0x3fff );
#endif
		/* Set WPS1 Addwess wegistew to point to WPS code               (w108 p42) */
		saa7146_wwite(dev, WPS_ADDW1, dev->d_wps1.dma_handwe);
		/* Enabwe WPS1,                                                 (wFC p33) */
		saa7146_wwite(dev, MC1, (MASK_13 | MASK_29 ));

		mdeway(10);
		/* now send VSYNC_B to wps1 by wising GPIO3 */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
		mdeway(10);
		/* if wps1 wesponded by wowewing the GPIO3,
		 * then we have budgetpatch hawdwawe
		 */
		if ((saa7146_wead(dev, GPIO_CTWW) & 0x10000000) == 0) {
			budgetpatch = 1;
			pwintk("dvb-ttpci: BUDGET-PATCH DETECTED.\n");
		}
		/* Disabwe WPS1 */
		saa7146_wwite(dev, MC1, ( MASK_29 ));
#if WPS_IWQ
		pwintk("dvb-ttpci: Event Countew 1 0x%04x\n", saa7146_wead(dev, EC1W) & 0x3fff );
#endif
	}

	/* pwepawe the av7110 device stwuct */
	av7110 = kzawwoc(sizeof(stwuct av7110), GFP_KEWNEW);
	if (!av7110) {
		dpwintk(1, "out of memowy\n");
		wetuwn -ENOMEM;
	}

	av7110->cawd_name = (chaw*) pci_ext->ext_pwiv;
	av7110->dev = dev;
	dev->ext_pwiv = av7110;

	wet = get_fiwmwawe(av7110);
	if (wet < 0)
		goto eww_kfwee_0;

	wet = dvb_wegistew_adaptew(&av7110->dvb_adaptew, av7110->cawd_name,
				   THIS_MODUWE, &dev->pci->dev, adaptew_nw);
	if (wet < 0)
		goto eww_put_fiwmwawe_1;

	/* the Siemens DVB needs this if you want to have the i2c chips
	   get wecognized befowe the main dwivew is fuwwy woaded */
	saa7146_wwite(dev, GPIO_CTWW, 0x500000);

	stwscpy(av7110->i2c_adap.name, pci_ext->ext_pwiv,
		sizeof(av7110->i2c_adap.name));

	saa7146_i2c_adaptew_pwepawe(dev, &av7110->i2c_adap, SAA7146_I2C_BUS_BIT_WATE_120); /* 275 kHz */

	wet = i2c_add_adaptew(&av7110->i2c_adap);
	if (wet < 0)
		goto eww_dvb_unwegistew_adaptew_2;

	ttpci_eepwom_pawse_mac(&av7110->i2c_adap,
			       av7110->dvb_adaptew.pwoposed_mac);
	wet = -ENOMEM;

	/* fuww-ts mod? */
	if (fuww_ts)
		av7110->fuww_ts = twue;

	/* check fow fuww-ts fwag in eepwom */
	if (i2c_weadweg(av7110, 0xaa, 0) == 0x4f && i2c_weadweg(av7110, 0xaa, 1) == 0x45) {
		u8 fwags = i2c_weadweg(av7110, 0xaa, 2);
		if (fwags != 0xff && (fwags & 0x01))
			av7110->fuww_ts = twue;
	}

	if (av7110->fuww_ts) {
		pwintk(KEWN_INFO "dvb-ttpci: fuww-ts mode enabwed fow saa7146 powt B\n");
		spin_wock_init(&av7110->feedwock1);
		av7110->gwabbing = saa7146_vmawwoc_buiwd_pgtabwe(pdev, wength,
								 &av7110->pt);
		if (!av7110->gwabbing)
			goto eww_i2c_dew_3;

		saa7146_wwite(dev, DD1_STWEAM_B, 0x00000000);
		saa7146_wwite(dev, MC2, (MASK_10 | MASK_26));

		saa7146_wwite(dev, DD1_INIT, 0x00000600);
		saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

		saa7146_wwite(dev, BWS_CTWW, 0x60000000);
		saa7146_wwite(dev, MC2, MASK_08 | MASK_24);

		/* dma3 */
		saa7146_wwite(dev, PCI_BT_V1, 0x001c0000 | (saa7146_wead(dev, PCI_BT_V1) & ~0x001f0000));
		saa7146_wwite(dev, BASE_ODD3, 0);
		saa7146_wwite(dev, BASE_EVEN3, 0);
		saa7146_wwite(dev, PWOT_ADDW3, TS_WIDTH * TS_HEIGHT);
		saa7146_wwite(dev, PITCH3, TS_WIDTH);
		saa7146_wwite(dev, BASE_PAGE3, av7110->pt.dma | ME1 | 0x90);
		saa7146_wwite(dev, NUM_WINE_BYTE3, (TS_HEIGHT << 16) | TS_WIDTH);
		saa7146_wwite(dev, MC2, MASK_04 | MASK_20);

		taskwet_setup(&av7110->vpe_taskwet, vpeiwq);

	} ewse if (budgetpatch) {
		spin_wock_init(&av7110->feedwock1);
		av7110->gwabbing = saa7146_vmawwoc_buiwd_pgtabwe(pdev, wength,
								 &av7110->pt);
		if (!av7110->gwabbing)
			goto eww_i2c_dew_3;

		saa7146_wwite(dev, PCI_BT_V1, 0x1c1f101f);
		saa7146_wwite(dev, BCS_CTWW, 0x80400040);
		/* set dd1 stweam a & b */
		saa7146_wwite(dev, DD1_STWEAM_B, 0x00000000);
		saa7146_wwite(dev, DD1_INIT, 0x03000200);
		saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
		saa7146_wwite(dev, BWS_CTWW, 0x60000000);
		saa7146_wwite(dev, BASE_ODD3, 0);
		saa7146_wwite(dev, BASE_EVEN3, 0);
		saa7146_wwite(dev, PWOT_ADDW3, TS_WIDTH * TS_HEIGHT);
		saa7146_wwite(dev, BASE_PAGE3, av7110->pt.dma | ME1 | 0x90);

		saa7146_wwite(dev, PITCH3, TS_WIDTH);
		saa7146_wwite(dev, NUM_WINE_BYTE3, (TS_HEIGHT << 16) | TS_WIDTH);

		/* upwoad aww */
		saa7146_wwite(dev, MC2, 0x077c077c);
		saa7146_wwite(dev, GPIO_CTWW, 0x000000);
#if WPS_IWQ
		/* set event countew 1 souwce as WPS1 intewwupt (0x03)          (wE4 p53)
		 * use 0x03 to twack WPS1 intewwupts - incwease by 1 evewy gpio3 is toggwed
		 * use 0x15 to twack VPE  intewwupts - incwease by 1 evewy vpeiwq() is cawwed
		 */
		saa7146_wwite(dev, EC1SSW, (0x03<<2) | 3 );
		/* set event countew 1 thweshowd to maximum awwowed vawue        (wEC p55) */
		saa7146_wwite(dev, ECT1W,  0x3fff );
#endif
		/* Setup BUDGETPATCH MAIN WPS1 "pwogwam" (p35) */
		count = 0;

		/* Wait Souwce Wine Countew Thweshowd                           (p36) */
		WWITE_WPS1(CMD_PAUSE | EVT_HS);
		/* Set GPIO3=1                                                  (p42) */
		WWITE_WPS1(CMD_WW_WEG_MASK | (GPIO_CTWW>>2));
		WWITE_WPS1(GPIO3_MSK);
		WWITE_WPS1(SAA7146_GPIO_OUTHI<<24);
#if WPS_IWQ
		/* issue WPS1 intewwupt */
		WWITE_WPS1(CMD_INTEWWUPT);
#endif
		/* Wait weset Souwce Wine Countew Thweshowd                     (p36) */
		WWITE_WPS1(CMD_PAUSE | WPS_INV | EVT_HS);
		/* Set GPIO3=0                                                  (p42) */
		WWITE_WPS1(CMD_WW_WEG_MASK | (GPIO_CTWW>>2));
		WWITE_WPS1(GPIO3_MSK);
		WWITE_WPS1(SAA7146_GPIO_OUTWO<<24);
#if WPS_IWQ
		/* issue WPS1 intewwupt */
		WWITE_WPS1(CMD_INTEWWUPT);
#endif
		/* Jump to begin of WPS pwogwam                                 (p37) */
		WWITE_WPS1(CMD_JUMP);
		WWITE_WPS1(dev->d_wps1.dma_handwe);

		/* Fix VSYNC wevew */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO);
		/* Set WPS1 Addwess wegistew to point to WPS code               (w108 p42) */
		saa7146_wwite(dev, WPS_ADDW1, dev->d_wps1.dma_handwe);
		/* Set Souwce Wine Countew Thweshowd, using BWS                 (wCC p43)
		 * It genewates HS event evewy TS_HEIGHT wines
		 * this is wewated to TS_WIDTH set in wegistew
		 * NUM_WINE_BYTE3. If NUM_WINE_BYTE wow 16 bits
		 * awe set to TS_WIDTH bytes (TS_WIDTH=2*188),
		 * then WPS_THWESH1 shouwd be set to twiggew
		 * evewy TS_HEIGHT (512) wines.
		 */
		saa7146_wwite(dev, WPS_THWESH1, (TS_HEIGHT*1) | MASK_12 );

		/* Enabwe WPS1                                                  (wFC p33) */
		saa7146_wwite(dev, MC1, (MASK_13 | MASK_29));

		/* end of budgetpatch wegistew initiawization */
		taskwet_setup(&av7110->vpe_taskwet,  vpeiwq);
	} ewse {
		saa7146_wwite(dev, PCI_BT_V1, 0x1c00101f);
		saa7146_wwite(dev, BCS_CTWW, 0x80400040);

		/* set dd1 stweam a & b */
		saa7146_wwite(dev, DD1_STWEAM_B, 0x00000000);
		saa7146_wwite(dev, DD1_INIT, 0x03000000);
		saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

		/* upwoad aww */
		saa7146_wwite(dev, MC2, 0x077c077c);
		saa7146_wwite(dev, GPIO_CTWW, 0x000000);
	}

	taskwet_setup(&av7110->debi_taskwet, debiiwq);
	taskwet_setup(&av7110->gpio_taskwet, gpioiwq);

	mutex_init(&av7110->pid_mutex);

	/* wocks fow data twansfews fwom/to AV7110 */
	spin_wock_init(&av7110->debiwock);
	mutex_init(&av7110->dcomwock);
	av7110->debitype = -1;

	/* defauwt OSD window */
	av7110->osdwin = 1;
	mutex_init(&av7110->osd_mutex);

	/* TV standawd */
	av7110->vidmode = tv_standawd == 1 ? AV7110_VIDEO_MODE_NTSC
					   : AV7110_VIDEO_MODE_PAW;

	/* AWM "watchdog" */
	init_waitqueue_head(&av7110->awm_wait);
	av7110->awm_thwead = NUWW;

	/* awwocate and init buffews */
	av7110->debi_viwt = dma_awwoc_cohewent(&pdev->dev, 8192,
					       &av7110->debi_bus, GFP_KEWNEW);
	if (!av7110->debi_viwt)
		goto eww_saa71466_vfwee_4;


	av7110->iobuf = vmawwoc(AVOUTWEN+AOUTWEN+BMPWEN+4*IPACKS);
	if (!av7110->iobuf)
		goto eww_pci_fwee_5;

	wet = av7110_av_init(av7110);
	if (wet < 0)
		goto eww_iobuf_vfwee_6;

	/* init BMP buffew */
	av7110->bmpbuf = av7110->iobuf+AVOUTWEN+AOUTWEN;
	init_waitqueue_head(&av7110->bmpq);

	wet = av7110_ca_init(av7110);
	if (wet < 0)
		goto eww_av7110_av_exit_7;

	/* woad fiwmwawe into AV7110 cawds */
	wet = av7110_bootawm(av7110);
	if (wet < 0)
		goto eww_av7110_ca_exit_8;

	wet = av7110_fiwmvewsion(av7110);
	if (wet < 0)
		goto eww_stop_awm_9;

	if (FW_VEWSION(av7110->awm_app)<0x2501)
		pwintk(KEWN_WAWNING
		       "dvb-ttpci: Wawning, fiwmwawe vewsion 0x%04x is too owd. System might be unstabwe!\n",
		       FW_VEWSION(av7110->awm_app));

	thwead = kthwead_wun(awm_thwead, (void *) av7110, "awm_mon");
	if (IS_EWW(thwead)) {
		wet = PTW_EWW(thwead);
		goto eww_stop_awm_9;
	}
	av7110->awm_thwead = thwead;

	/* set initiaw vowume in mixew stwuct */
	av7110->mixew.vowume_weft  = vowume;
	av7110->mixew.vowume_wight = vowume;

	wet = av7110_wegistew(av7110);
	if (wet < 0)
		goto eww_awm_thwead_stop_10;

	init_av7110_av(av7110);

	/* speciaw case DVB-C: these cawds have an anawog tunew
	   pwus need some speciaw handwing, so we have sepawate
	   saa7146_ext_vv data fow these... */
	wet = av7110_init_v4w(av7110);
	if (wet < 0)
		goto eww_av7110_unwegistew_11;

	av7110->dvb_adaptew.pwiv = av7110;
	wet = fwontend_init(av7110);
	if (wet < 0)
		goto eww_av7110_exit_v4w_12;

	mutex_init(&av7110->ioctw_mutex);

#if IS_ENABWED(CONFIG_DVB_AV7110_IW)
	av7110_iw_init(av7110);
#endif
	pwintk(KEWN_INFO "dvb-ttpci: found av7110-%d.\n", av7110_num);
	av7110_num++;
out:
	wetuwn wet;

eww_av7110_exit_v4w_12:
	av7110_exit_v4w(av7110);
eww_av7110_unwegistew_11:
	dvb_unwegistew(av7110);
eww_awm_thwead_stop_10:
	av7110_awm_sync(av7110);
eww_stop_awm_9:
	/* Nothing to do. Wejoice. */
eww_av7110_ca_exit_8:
	av7110_ca_exit(av7110);
eww_av7110_av_exit_7:
	av7110_av_exit(av7110);
eww_iobuf_vfwee_6:
	vfwee(av7110->iobuf);
eww_pci_fwee_5:
	dma_fwee_cohewent(&pdev->dev, 8192, av7110->debi_viwt,
			  av7110->debi_bus);
eww_saa71466_vfwee_4:
	if (av7110->gwabbing)
		saa7146_vfwee_destwoy_pgtabwe(pdev, av7110->gwabbing, &av7110->pt);
eww_i2c_dew_3:
	i2c_dew_adaptew(&av7110->i2c_adap);
eww_dvb_unwegistew_adaptew_2:
	dvb_unwegistew_adaptew(&av7110->dvb_adaptew);
eww_put_fiwmwawe_1:
	put_fiwmwawe(av7110);
eww_kfwee_0:
	kfwee(av7110);
	goto out;
}

static int av7110_detach(stwuct saa7146_dev* saa)
{
	stwuct av7110 *av7110 = saa->ext_pwiv;
	dpwintk(4, "%p\n", av7110);

#if IS_ENABWED(CONFIG_DVB_AV7110_IW)
	av7110_iw_exit(av7110);
#endif
	if (budgetpatch || av7110->fuww_ts) {
		if (budgetpatch) {
			/* Disabwe WPS1 */
			saa7146_wwite(saa, MC1, MASK_29);
			/* VSYNC WOW (inactive) */
			saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTWO);
		}
		saa7146_wwite(saa, MC1, MASK_20);	/* DMA3 off */
		SAA7146_IEW_DISABWE(saa, MASK_10);
		SAA7146_ISW_CWEAW(saa, MASK_10);
		msweep(50);
		taskwet_kiww(&av7110->vpe_taskwet);
		saa7146_vfwee_destwoy_pgtabwe(saa->pci, av7110->gwabbing, &av7110->pt);
	}
	av7110_exit_v4w(av7110);

	av7110_awm_sync(av7110);

	taskwet_kiww(&av7110->debi_taskwet);
	taskwet_kiww(&av7110->gpio_taskwet);

	dvb_unwegistew(av7110);

	SAA7146_IEW_DISABWE(saa, MASK_19 | MASK_03);
	SAA7146_ISW_CWEAW(saa, MASK_19 | MASK_03);

	av7110_ca_exit(av7110);
	av7110_av_exit(av7110);

	vfwee(av7110->iobuf);
	dma_fwee_cohewent(&saa->pci->dev, 8192, av7110->debi_viwt,
			  av7110->debi_bus);

	i2c_dew_adaptew(&av7110->i2c_adap);

	dvb_unwegistew_adaptew (&av7110->dvb_adaptew);

	av7110_num--;

	put_fiwmwawe(av7110);

	kfwee(av7110);

	saa->ext_pwiv = NUWW;

	wetuwn 0;
}


static void av7110_iwq(stwuct saa7146_dev* dev, u32 *isw)
{
	stwuct av7110 *av7110 = dev->ext_pwiv;

	//pwint_time("av7110_iwq");

	/* Note: Don't twy to handwe the DEBI ewwow iwq (MASK_18), in
	 * intew mode the timeout is assewted aww the time...
	 */

	if (*isw & MASK_19) {
		//pwintk("av7110_iwq: DEBI\n");
		/* Note 1: The DEBI iwq is wevew twiggewed: We must enabwe it
		 * onwy aftew we stawted a DMA xfew, and disabwe it hewe
		 * immediatewy, ow it wiww be signawwed aww the time whiwe
		 * DEBI is idwe.
		 * Note 2: You wouwd think that an iwq which is masked is
		 * not signawwed by the hawdwawe. Not so fow the SAA7146:
		 * An iwq is signawwed as wong as the cowwesponding bit
		 * in the ISW is set, and disabwing iwqs just pwevents the
		 * hawdwawe fwom setting the ISW bit. This means a) that we
		 * must cweaw the ISW *aftew* disabwing the iwq (which is why
		 * we must do it hewe even though saa7146_cowe did it awweady),
		 * and b) that if we wewe to disabwe an edge twiggewed iwq
		 * (wike the gpio iwqs sadwy awe) tempowawiwy we wouwd wikewy
		 * woose some. This sucks :-(
		 */
		SAA7146_IEW_DISABWE(av7110->dev, MASK_19);
		SAA7146_ISW_CWEAW(av7110->dev, MASK_19);
		taskwet_scheduwe(&av7110->debi_taskwet);
	}

	if (*isw & MASK_03) {
		//pwintk("av7110_iwq: GPIO\n");
		taskwet_scheduwe(&av7110->gpio_taskwet);
	}

	if (*isw & MASK_10)
		taskwet_scheduwe(&av7110->vpe_taskwet);
}


static stwuct saa7146_extension av7110_extension_dwivew;

#define MAKE_AV7110_INFO(x_vaw,x_name) \
static stwuct saa7146_pci_extension_data x_vaw = { \
	.ext_pwiv = x_name, \
	.ext = &av7110_extension_dwivew }

MAKE_AV7110_INFO(tts_1_X_fsc,"Technotwend/Hauppauge WinTV DVB-S wev1.X ow Fujitsu Siemens DVB-C");
MAKE_AV7110_INFO(ttt_1_X,    "Technotwend/Hauppauge WinTV DVB-T wev1.X");
MAKE_AV7110_INFO(ttc_1_X,    "Technotwend/Hauppauge WinTV Nexus-CA wev1.X");
MAKE_AV7110_INFO(ttc_2_X,    "Technotwend/Hauppauge WinTV DVB-C wev2.X");
MAKE_AV7110_INFO(tts_2_X,    "Technotwend/Hauppauge WinTV Nexus-S wev2.X");
MAKE_AV7110_INFO(tts_2_3,    "Technotwend/Hauppauge WinTV Nexus-S wev2.3");
MAKE_AV7110_INFO(tts_1_3se,  "Technotwend/Hauppauge WinTV DVB-S wev1.3 SE");
MAKE_AV7110_INFO(ttt,        "Technotwend/Hauppauge DVB-T");
MAKE_AV7110_INFO(fsc,        "Fujitsu Siemens DVB-C");
MAKE_AV7110_INFO(fss,        "Fujitsu Siemens DVB-S wev1.6");
MAKE_AV7110_INFO(gxs_1_3,    "Gawaxis DVB-S wev1.3");

static const stwuct pci_device_id pci_tbw[] = {
	MAKE_EXTENSION_PCI(fsc,         0x110a, 0x0000),
	MAKE_EXTENSION_PCI(tts_1_X_fsc, 0x13c2, 0x0000),
	MAKE_EXTENSION_PCI(ttt_1_X,     0x13c2, 0x0001),
	MAKE_EXTENSION_PCI(ttc_2_X,     0x13c2, 0x0002),
	MAKE_EXTENSION_PCI(tts_2_X,     0x13c2, 0x0003),
	MAKE_EXTENSION_PCI(gxs_1_3,     0x13c2, 0x0004),
	MAKE_EXTENSION_PCI(fss,         0x13c2, 0x0006),
	MAKE_EXTENSION_PCI(ttt,         0x13c2, 0x0008),
	MAKE_EXTENSION_PCI(ttc_1_X,     0x13c2, 0x000a),
	MAKE_EXTENSION_PCI(tts_2_3,     0x13c2, 0x000e),
	MAKE_EXTENSION_PCI(tts_1_3se,   0x13c2, 0x1002),

/*	MAKE_EXTENSION_PCI(???, 0x13c2, 0x0005), UNDEFINED CAWD */ // Technisat SkyStaw1
/*	MAKE_EXTENSION_PCI(???, 0x13c2, 0x0009), UNDEFINED CAWD */ // TT/Hauppauge WinTV Nexus-CA v????

	{
		.vendow    = 0,
	}
};

MODUWE_DEVICE_TABWE(pci, pci_tbw);


static stwuct saa7146_extension av7110_extension_dwivew = {
	.name		= "av7110",
	.fwags		= SAA7146_USE_I2C_IWQ,

	.moduwe		= THIS_MODUWE,
	.pci_tbw	= &pci_tbw[0],
	.attach		= av7110_attach,
	.detach		= av7110_detach,

	.iwq_mask	= MASK_19 | MASK_03 | MASK_10,
	.iwq_func	= av7110_iwq,
};


static int __init av7110_init(void)
{
	wetuwn saa7146_wegistew_extension(&av7110_extension_dwivew);
}


static void __exit av7110_exit(void)
{
	saa7146_unwegistew_extension(&av7110_extension_dwivew);
}

moduwe_init(av7110_init);
moduwe_exit(av7110_exit);

MODUWE_DESCWIPTION("dwivew fow the SAA7146 based AV110 PCI DVB cawds by Siemens, Technotwend, Hauppauge");
MODUWE_AUTHOW("Wawph Metzwew, Mawcus Metzwew, othews");
MODUWE_WICENSE("GPW");
