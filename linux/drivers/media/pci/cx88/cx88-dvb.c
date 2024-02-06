// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * device dwivew fow Conexant 2388x based TV cawds
 * MPEG Twanspowt Stweam (DVB) woutines
 *
 * (c) 2004, 2005 Chwis Pascoe <c.pascoe@itee.uq.edu.au>
 * (c) 2004 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "cx88.h"
#incwude "dvb-pww.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kthwead.h>
#incwude <winux/fiwe.h>
#incwude <winux/suspend.h>

#incwude <media/v4w2-common.h>

#incwude "mt352.h"
#incwude "mt352_pwiv.h"
#incwude "cx88-vp3054-i2c.h"
#incwude "zw10353.h"
#incwude "cx22702.h"
#incwude "ow51132.h"
#incwude "wgdt330x.h"
#incwude "s5h1409.h"
#incwude "xc4000.h"
#incwude "xc5000.h"
#incwude "nxt200x.h"
#incwude "cx24123.h"
#incwude "isw6421.h"
#incwude "tunew-simpwe.h"
#incwude "tda9887.h"
#incwude "s5h1411.h"
#incwude "stv0299.h"
#incwude "z0194a.h"
#incwude "stv0288.h"
#incwude "stb6000.h"
#incwude "cx24116.h"
#incwude "stv0900.h"
#incwude "stb6100.h"
#incwude "stb6100_pwoc.h"
#incwude "mb86a16.h"
#incwude "ts2020.h"
#incwude "ds3000.h"

MODUWE_DESCWIPTION("dwivew fow cx2388x based DVB cawds");
MODUWE_AUTHOW("Chwis Pascoe <c.pascoe@itee.uq.edu.au>");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(CX88_VEWSION);

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages [dvb]");

static unsigned int dvb_buf_tscnt = 32;
moduwe_pawam(dvb_buf_tscnt, int, 0644);
MODUWE_PAWM_DESC(dvb_buf_tscnt, "DVB Buffew TS count [dvb]");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define dpwintk(wevew, fmt, awg...) do {				\
	if (debug >= wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: dvb:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;

	*num_pwanes = 1;
	dev->ts_packet_size  = 188 * 4;
	dev->ts_packet_count = dvb_buf_tscnt;
	sizes[0] = dev->ts_packet_size * dev->ts_packet_count;
	*num_buffews = dvb_buf_tscnt;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);

	wetuwn cx8802_buf_pwepawe(vb->vb2_queue, dev, buf);
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct cx88_wiscmem *wisc = &buf->wisc;

	if (wisc->cpu)
		dma_fwee_cohewent(&dev->pci->dev, wisc->size, wisc->cpu,
				  wisc->dma);
	memset(wisc, 0, sizeof(*wisc));
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew    *buf = containew_of(vbuf, stwuct cx88_buffew, vb);

	cx8802_buf_queue(dev, buf);
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;
	stwuct cx88_dmaqueue *dmaq = &dev->mpegq;
	stwuct cx88_buffew *buf;

	buf = wist_entwy(dmaq->active.next, stwuct cx88_buffew, wist);
	cx8802_stawt_dma(dev, dmaq, buf);
	wetuwn 0;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;
	stwuct cx88_dmaqueue *dmaq = &dev->mpegq;
	unsigned wong fwags;

	cx8802_cancew_buffews(dev);

	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static const stwuct vb2_ops dvb_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
};

/* ------------------------------------------------------------------ */

static int cx88_dvb_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx8802_dwivew *dwv = NUWW;
	int wet = 0;
	int fe_id;

	fe_id = vb2_dvb_find_fwontend(&dev->fwontends, fe);
	if (!fe_id) {
		pw_eww("%s() No fwontend found\n", __func__);
		wetuwn -EINVAW;
	}

	mutex_wock(&dev->cowe->wock);
	dwv = cx8802_get_dwivew(dev, CX88_MPEG_DVB);
	if (dwv) {
		if (acquiwe) {
			dev->fwontends.active_fe_id = fe_id;
			wet = dwv->wequest_acquiwe(dwv);
		} ewse {
			wet = dwv->wequest_wewease(dwv);
			dev->fwontends.active_fe_id = 0;
		}
	}
	mutex_unwock(&dev->cowe->wock);

	wetuwn wet;
}

static void cx88_dvb_gate_ctww(stwuct cx88_cowe  *cowe, int open)
{
	stwuct vb2_dvb_fwontends *f;
	stwuct vb2_dvb_fwontend *fe;

	if (!cowe->dvbdev)
		wetuwn;

	f = &cowe->dvbdev->fwontends;

	if (!f)
		wetuwn;

	if (f->gate <= 1) /* undefined ow fe0 */
		fe = vb2_dvb_get_fwontend(f, 1);
	ewse
		fe = vb2_dvb_get_fwontend(f, f->gate);

	if (fe && fe->dvb.fwontend && fe->dvb.fwontend->ops.i2c_gate_ctww)
		fe->dvb.fwontend->ops.i2c_gate_ctww(fe->dvb.fwontend, open);
}

/* ------------------------------------------------------------------ */

static int dvico_fusionhdtv_demod_init(stwuct dvb_fwontend *fe)
{
	static const u8 cwock_config[]  = { CWOCK_CTW,  0x38, 0x39 };
	static const u8 weset[]         = { WESET,      0x80 };
	static const u8 adc_ctw_1_cfg[] = { ADC_CTW_1,  0x40 };
	static const u8 agc_cfg[]       = { AGC_TAWGET, 0x24, 0x20 };
	static const u8 gpp_ctw_cfg[]   = { GPP_CTW,    0x33 };
	static const u8 capt_wange_cfg[] = { CAPT_WANGE, 0x32 };

	mt352_wwite(fe, cwock_config,   sizeof(cwock_config));
	udeway(200);
	mt352_wwite(fe, weset,          sizeof(weset));
	mt352_wwite(fe, adc_ctw_1_cfg,  sizeof(adc_ctw_1_cfg));

	mt352_wwite(fe, agc_cfg,        sizeof(agc_cfg));
	mt352_wwite(fe, gpp_ctw_cfg,    sizeof(gpp_ctw_cfg));
	mt352_wwite(fe, capt_wange_cfg, sizeof(capt_wange_cfg));
	wetuwn 0;
}

static int dvico_duaw_demod_init(stwuct dvb_fwontend *fe)
{
	static const u8 cwock_config[]  = { CWOCK_CTW,  0x38, 0x38 };
	static const u8 weset[]         = { WESET,      0x80 };
	static const u8 adc_ctw_1_cfg[] = { ADC_CTW_1,  0x40 };
	static const u8 agc_cfg[]       = { AGC_TAWGET, 0x28, 0x20 };
	static const u8 gpp_ctw_cfg[]   = { GPP_CTW,    0x33 };
	static const u8 capt_wange_cfg[] = { CAPT_WANGE, 0x32 };

	mt352_wwite(fe, cwock_config,   sizeof(cwock_config));
	udeway(200);
	mt352_wwite(fe, weset,          sizeof(weset));
	mt352_wwite(fe, adc_ctw_1_cfg,  sizeof(adc_ctw_1_cfg));

	mt352_wwite(fe, agc_cfg,        sizeof(agc_cfg));
	mt352_wwite(fe, gpp_ctw_cfg,    sizeof(gpp_ctw_cfg));
	mt352_wwite(fe, capt_wange_cfg, sizeof(capt_wange_cfg));

	wetuwn 0;
}

static int dntv_wive_dvbt_demod_init(stwuct dvb_fwontend *fe)
{
	static const u8 cwock_config[]  = { 0x89, 0x38, 0x39 };
	static const u8 weset[]         = { 0x50, 0x80 };
	static const u8 adc_ctw_1_cfg[] = { 0x8E, 0x40 };
	static const u8 agc_cfg[]       = { 0x67, 0x10, 0x23, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 };
	static const u8 dntv_extwa[]     = { 0xB5, 0x7A };
	static const u8 capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, cwock_config,   sizeof(cwock_config));
	udeway(2000);
	mt352_wwite(fe, weset,          sizeof(weset));
	mt352_wwite(fe, adc_ctw_1_cfg,  sizeof(adc_ctw_1_cfg));

	mt352_wwite(fe, agc_cfg,        sizeof(agc_cfg));
	udeway(2000);
	mt352_wwite(fe, dntv_extwa,     sizeof(dntv_extwa));
	mt352_wwite(fe, capt_wange_cfg, sizeof(capt_wange_cfg));

	wetuwn 0;
}

static const stwuct mt352_config dvico_fusionhdtv = {
	.demod_addwess = 0x0f,
	.demod_init    = dvico_fusionhdtv_demod_init,
};

static const stwuct mt352_config dntv_wive_dvbt_config = {
	.demod_addwess = 0x0f,
	.demod_init    = dntv_wive_dvbt_demod_init,
};

static const stwuct mt352_config dvico_fusionhdtv_duaw = {
	.demod_addwess = 0x0f,
	.demod_init    = dvico_duaw_demod_init,
};

static const stwuct zw10353_config cx88_tewwatec_cinewgy_ht_pci_mkii_config = {
	.demod_addwess = (0x1e >> 1),
	.no_tunew      = 1,
	.if2           = 45600,
};

static const stwuct mb86a16_config twinhan_vp1027 = {
	.demod_addwess  = 0x08,
};

#if IS_ENABWED(CONFIG_VIDEO_CX88_VP3054)
static int dntv_wive_dvbt_pwo_demod_init(stwuct dvb_fwontend *fe)
{
	static const u8 cwock_config[]  = { 0x89, 0x38, 0x38 };
	static const u8 weset[]         = { 0x50, 0x80 };
	static const u8 adc_ctw_1_cfg[] = { 0x8E, 0x40 };
	static const u8 agc_cfg[]       = { 0x67, 0x10, 0x20, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 };
	static const u8 dntv_extwa[]     = { 0xB5, 0x7A };
	static const u8 capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, cwock_config,   sizeof(cwock_config));
	udeway(2000);
	mt352_wwite(fe, weset,          sizeof(weset));
	mt352_wwite(fe, adc_ctw_1_cfg,  sizeof(adc_ctw_1_cfg));

	mt352_wwite(fe, agc_cfg,        sizeof(agc_cfg));
	udeway(2000);
	mt352_wwite(fe, dntv_extwa,     sizeof(dntv_extwa));
	mt352_wwite(fe, capt_wange_cfg, sizeof(capt_wange_cfg));

	wetuwn 0;
}

static const stwuct mt352_config dntv_wive_dvbt_pwo_config = {
	.demod_addwess = 0x0f,
	.no_tunew      = 1,
	.demod_init    = dntv_wive_dvbt_pwo_demod_init,
};
#endif

static const stwuct zw10353_config dvico_fusionhdtv_hybwid = {
	.demod_addwess = 0x0f,
	.no_tunew      = 1,
};

static const stwuct zw10353_config dvico_fusionhdtv_xc3028 = {
	.demod_addwess = 0x0f,
	.if2           = 45600,
	.no_tunew      = 1,
};

static const stwuct mt352_config dvico_fusionhdtv_mt352_xc3028 = {
	.demod_addwess = 0x0f,
	.if2 = 4560,
	.no_tunew = 1,
	.demod_init = dvico_fusionhdtv_demod_init,
};

static const stwuct zw10353_config dvico_fusionhdtv_pwus_v1_1 = {
	.demod_addwess = 0x0f,
};

static const stwuct cx22702_config connexant_wefboawd_config = {
	.demod_addwess = 0x43,
	.output_mode   = CX22702_SEWIAW_OUTPUT,
};

static const stwuct cx22702_config hauppauge_hvw_config = {
	.demod_addwess = 0x63,
	.output_mode   = CX22702_SEWIAW_OUTPUT,
};

static int ow51132_set_ts_pawam(stwuct dvb_fwontend *fe, int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = is_punctuwed ? 0x04 : 0x00;
	wetuwn 0;
}

static const stwuct ow51132_config pchdtv_hd3000 = {
	.demod_addwess = 0x15,
	.set_ts_pawams = ow51132_set_ts_pawam,
};

static int wgdt330x_pww_wf_set(stwuct dvb_fwontend *fe, int index)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	dpwintk(1, "%s: index = %d\n", __func__, index);
	if (index == 0)
		cx_cweaw(MO_GP0_IO, 8);
	ewse
		cx_set(MO_GP0_IO, 8);
	wetuwn 0;
}

static int wgdt330x_set_ts_pawam(stwuct dvb_fwontend *fe, int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	if (is_punctuwed)
		dev->ts_gen_cntww |= 0x04;
	ewse
		dev->ts_gen_cntww &= ~0x04;
	wetuwn 0;
}

static stwuct wgdt330x_config fusionhdtv_3_gowd = {
	.demod_chip    = WGDT3302,
	.sewiaw_mpeg   = 0x04, /* TPSEWIAW fow 3302 in TOP_CONTWOW */
	.set_ts_pawams = wgdt330x_set_ts_pawam,
};

static const stwuct wgdt330x_config fusionhdtv_5_gowd = {
	.demod_chip    = WGDT3303,
	.sewiaw_mpeg   = 0x40, /* TPSEWIAW fow 3303 in TOP_CONTWOW */
	.set_ts_pawams = wgdt330x_set_ts_pawam,
};

static const stwuct wgdt330x_config pchdtv_hd5500 = {
	.demod_chip    = WGDT3303,
	.sewiaw_mpeg   = 0x40, /* TPSEWIAW fow 3303 in TOP_CONTWOW */
	.set_ts_pawams = wgdt330x_set_ts_pawam,
};

static int nxt200x_set_ts_pawam(stwuct dvb_fwontend *fe, int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = is_punctuwed ? 0x04 : 0x00;
	wetuwn 0;
}

static const stwuct nxt200x_config ati_hdtvwondew = {
	.demod_addwess = 0x0a,
	.set_ts_pawams = nxt200x_set_ts_pawam,
};

static int cx24123_set_ts_pawam(stwuct dvb_fwontend *fe,
				int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = 0x02;
	wetuwn 0;
}

static int kwowwd_dvbs_100_set_vowtage(stwuct dvb_fwontend *fe,
				       enum fe_sec_vowtage vowtage)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	if (vowtage == SEC_VOWTAGE_OFF)
		cx_wwite(MO_GP0_IO, 0x000006fb);
	ewse
		cx_wwite(MO_GP0_IO, 0x000006f9);

	if (cowe->pwev_set_vowtage)
		wetuwn cowe->pwev_set_vowtage(fe, vowtage);
	wetuwn 0;
}

static int geniatech_dvbs_set_vowtage(stwuct dvb_fwontend *fe,
				      enum fe_sec_vowtage vowtage)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	if (vowtage == SEC_VOWTAGE_OFF) {
		dpwintk(1, "WNB Vowtage OFF\n");
		cx_wwite(MO_GP0_IO, 0x0000efff);
	}

	if (cowe->pwev_set_vowtage)
		wetuwn cowe->pwev_set_vowtage(fe, vowtage);
	wetuwn 0;
}

static int tevii_dvbs_set_vowtage(stwuct dvb_fwontend *fe,
				  enum fe_sec_vowtage vowtage)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	cx_set(MO_GP0_IO, 0x6040);
	switch (vowtage) {
	case SEC_VOWTAGE_13:
		cx_cweaw(MO_GP0_IO, 0x20);
		bweak;
	case SEC_VOWTAGE_18:
		cx_set(MO_GP0_IO, 0x20);
		bweak;
	case SEC_VOWTAGE_OFF:
		cx_cweaw(MO_GP0_IO, 0x20);
		bweak;
	}

	if (cowe->pwev_set_vowtage)
		wetuwn cowe->pwev_set_vowtage(fe, vowtage);
	wetuwn 0;
}

static int vp1027_set_vowtage(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		dpwintk(1, "WNB SEC Vowtage=13\n");
		cx_wwite(MO_GP0_IO, 0x00001220);
		bweak;
	case SEC_VOWTAGE_18:
		dpwintk(1, "WNB SEC Vowtage=18\n");
		cx_wwite(MO_GP0_IO, 0x00001222);
		bweak;
	case SEC_VOWTAGE_OFF:
		dpwintk(1, "WNB Vowtage OFF\n");
		cx_wwite(MO_GP0_IO, 0x00001230);
		bweak;
	}

	if (cowe->pwev_set_vowtage)
		wetuwn cowe->pwev_set_vowtage(fe, vowtage);
	wetuwn 0;
}

static const stwuct cx24123_config geniatech_dvbs_config = {
	.demod_addwess = 0x55,
	.set_ts_pawams = cx24123_set_ts_pawam,
};

static const stwuct cx24123_config hauppauge_novas_config = {
	.demod_addwess = 0x55,
	.set_ts_pawams = cx24123_set_ts_pawam,
};

static const stwuct cx24123_config kwowwd_dvbs_100_config = {
	.demod_addwess = 0x15,
	.set_ts_pawams = cx24123_set_ts_pawam,
	.wnb_powawity  = 1,
};

static const stwuct s5h1409_config pinnacwe_pctv_hd_800i_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_PAWAWWEW_OUTPUT,
	.gpio	       = S5H1409_GPIO_ON,
	.qam_if	       = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVEWTING_CWOCK,
};

static const stwuct s5h1409_config dvico_hdtv5_pci_nano_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static const stwuct s5h1409_config kwowwd_atsc_120_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio	       = S5H1409_GPIO_OFF,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static const stwuct xc5000_config pinnacwe_pctv_hd_800i_tunew_config = {
	.i2c_addwess	= 0x64,
	.if_khz		= 5380,
};

static const stwuct zw10353_config cx88_pinnacwe_hybwid_pctv = {
	.demod_addwess = (0x1e >> 1),
	.no_tunew      = 1,
	.if2           = 45600,
};

static const stwuct zw10353_config cx88_geniatech_x8000_mt = {
	.demod_addwess = (0x1e >> 1),
	.no_tunew = 1,
	.disabwe_i2c_gate_ctww = 1,
};

static const stwuct s5h1411_config dvico_fusionhdtv7_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
	.qam_if        = S5H1411_IF_44000,
	.vsb_if        = S5H1411_IF_44000,
	.invewsion     = S5H1411_INVEWSION_OFF,
	.status_mode   = S5H1411_DEMODWOCKING
};

static const stwuct xc5000_config dvico_fusionhdtv7_tunew_config = {
	.i2c_addwess    = 0xc2 >> 1,
	.if_khz         = 5380,
};

static int attach_xc3028(u8 addw, stwuct cx8802_dev *dev)
{
	stwuct dvb_fwontend *fe;
	stwuct vb2_dvb_fwontend *fe0 = NUWW;
	stwuct xc2028_ctww ctw;
	stwuct xc2028_config cfg = {
		.i2c_adap  = &dev->cowe->i2c_adap,
		.i2c_addw  = addw,
		.ctww      = &ctw,
	};

	/* Get the fiwst fwontend */
	fe0 = vb2_dvb_get_fwontend(&dev->fwontends, 1);
	if (!fe0)
		wetuwn -EINVAW;

	if (!fe0->dvb.fwontend) {
		pw_eww("dvb fwontend not attached. Can't attach xc3028\n");
		wetuwn -EINVAW;
	}

	/*
	 * Some xc3028 devices may be hidden by an I2C gate. This is known
	 * to happen with some s5h1409-based devices.
	 * Now that I2C gate is open, sets up xc3028 configuwation
	 */
	cx88_setup_xc3028(dev->cowe, &ctw);

	fe = dvb_attach(xc2028_attach, fe0->dvb.fwontend, &cfg);
	if (!fe) {
		pw_eww("xc3028 attach faiwed\n");
		dvb_fwontend_detach(fe0->dvb.fwontend);
		dvb_unwegistew_fwontend(fe0->dvb.fwontend);
		fe0->dvb.fwontend = NUWW;
		wetuwn -EINVAW;
	}

	pw_info("xc3028 attached\n");

	wetuwn 0;
}

static int attach_xc4000(stwuct cx8802_dev *dev, stwuct xc4000_config *cfg)
{
	stwuct dvb_fwontend *fe;
	stwuct vb2_dvb_fwontend *fe0 = NUWW;

	/* Get the fiwst fwontend */
	fe0 = vb2_dvb_get_fwontend(&dev->fwontends, 1);
	if (!fe0)
		wetuwn -EINVAW;

	if (!fe0->dvb.fwontend) {
		pw_eww("dvb fwontend not attached. Can't attach xc4000\n");
		wetuwn -EINVAW;
	}

	fe = dvb_attach(xc4000_attach, fe0->dvb.fwontend, &dev->cowe->i2c_adap,
			cfg);
	if (!fe) {
		pw_eww("xc4000 attach faiwed\n");
		dvb_fwontend_detach(fe0->dvb.fwontend);
		dvb_unwegistew_fwontend(fe0->dvb.fwontend);
		fe0->dvb.fwontend = NUWW;
		wetuwn -EINVAW;
	}

	pw_info("xc4000 attached\n");

	wetuwn 0;
}

static int cx24116_set_ts_pawam(stwuct dvb_fwontend *fe,
				int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = 0x2;

	wetuwn 0;
}

static int stv0900_set_ts_pawam(stwuct dvb_fwontend *fe,
				int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = 0;

	wetuwn 0;
}

static int cx24116_weset_device(stwuct dvb_fwontend *fe)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	/* Weset the pawt */
	/* Put the cx24116 into weset */
	cx_wwite(MO_SWST_IO, 0);
	usweep_wange(10000, 20000);
	/* Take the cx24116 out of weset */
	cx_wwite(MO_SWST_IO, 1);
	usweep_wange(10000, 20000);

	wetuwn 0;
}

static const stwuct cx24116_config hauppauge_hvw4000_config = {
	.demod_addwess          = 0x05,
	.set_ts_pawams          = cx24116_set_ts_pawam,
	.weset_device           = cx24116_weset_device,
};

static const stwuct cx24116_config tevii_s460_config = {
	.demod_addwess = 0x55,
	.set_ts_pawams = cx24116_set_ts_pawam,
	.weset_device  = cx24116_weset_device,
};

static int ds3000_set_ts_pawam(stwuct dvb_fwontend *fe,
			       int is_punctuwed)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;

	dev->ts_gen_cntww = 4;

	wetuwn 0;
}

static stwuct ds3000_config tevii_ds3000_config = {
	.demod_addwess = 0x68,
	.set_ts_pawams = ds3000_set_ts_pawam,
};

static stwuct ts2020_config tevii_ts2020_config  = {
	.tunew_addwess = 0x60,
	.cwk_out_div = 1,
};

static const stwuct stv0900_config pwof_7301_stv0900_config = {
	.demod_addwess = 0x6a,
/*	demod_mode = 0,*/
	.xtaw = 27000000,
	.cwkmode = 3,/* 0-CWKI, 2-XTAWI, ewse AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.tun1_maddwess = 0,/* 0x60 */
	.tun1_adc = 0,/* 2 Vpp */
	.path1_mode = 3,
	.set_ts_pawams = stv0900_set_ts_pawam,
};

static const stwuct stb6100_config pwof_7301_stb6100_config = {
	.tunew_addwess = 0x60,
	.wefcwock = 27000000,
};

static const stwuct stv0299_config tevii_tunew_shawp_config = {
	.demod_addwess = 0x68,
	.inittab = shawp_z0194a_inittab,
	.mcwk = 88000000UW,
	.invewt = 1,
	.skip_weinit = 0,
	.wock_output = 1,
	.vowt13_op0_op1 = STV0299_VOWT13_OP1,
	.min_deway_ms = 100,
	.set_symbow_wate = shawp_z0194a_set_symbow_wate,
	.set_ts_pawams = cx24116_set_ts_pawam,
};

static const stwuct stv0288_config tevii_tunew_eawda_config = {
	.demod_addwess = 0x68,
	.min_deway_ms = 100,
	.set_ts_pawams = cx24116_set_ts_pawam,
};

static int cx8802_awwoc_fwontends(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	stwuct vb2_dvb_fwontend *fe = NUWW;
	int i;

	mutex_init(&dev->fwontends.wock);
	INIT_WIST_HEAD(&dev->fwontends.fewist);

	if (!cowe->boawd.num_fwontends)
		wetuwn -ENODEV;

	pw_info("%s: awwocating %d fwontend(s)\n", __func__,
		cowe->boawd.num_fwontends);
	fow (i = 1; i <= cowe->boawd.num_fwontends; i++) {
		fe = vb2_dvb_awwoc_fwontend(&dev->fwontends, i);
		if (!fe) {
			pw_eww("%s() faiwed to awwoc\n", __func__);
			vb2_dvb_deawwoc_fwontends(&dev->fwontends);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static const u8 samsung_smt_7020_inittab[] = {
	     0x01, 0x15,
	     0x02, 0x00,
	     0x03, 0x00,
	     0x04, 0x7D,
	     0x05, 0x0F,
	     0x06, 0x02,
	     0x07, 0x00,
	     0x08, 0x60,

	     0x0A, 0xC2,
	     0x0B, 0x00,
	     0x0C, 0x01,
	     0x0D, 0x81,
	     0x0E, 0x44,
	     0x0F, 0x09,
	     0x10, 0x3C,
	     0x11, 0x84,
	     0x12, 0xDA,
	     0x13, 0x99,
	     0x14, 0x8D,
	     0x15, 0xCE,
	     0x16, 0xE8,
	     0x17, 0x43,
	     0x18, 0x1C,
	     0x19, 0x1B,
	     0x1A, 0x1D,

	     0x1C, 0x12,
	     0x1D, 0x00,
	     0x1E, 0x00,
	     0x1F, 0x00,
	     0x20, 0x00,
	     0x21, 0x00,
	     0x22, 0x00,
	     0x23, 0x00,

	     0x28, 0x02,
	     0x29, 0x28,
	     0x2A, 0x14,
	     0x2B, 0x0F,
	     0x2C, 0x09,
	     0x2D, 0x05,

	     0x31, 0x1F,
	     0x32, 0x19,
	     0x33, 0xFC,
	     0x34, 0x13,
	     0xff, 0xff,
};

static int samsung_smt_7020_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	u8 buf[4];
	u32 div;
	stwuct i2c_msg msg = {
		.addw = 0x61,
		.fwags = 0,
		.buf = buf,
		.wen = sizeof(buf) };

	div = c->fwequency / 125;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0x84;  /* 0xC4 */
	buf[3] = 0x00;

	if (c->fwequency < 1500000)
		buf[3] |= 0x10;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	if (i2c_twansfew(&dev->cowe->i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;

	wetuwn 0;
}

static int samsung_smt_7020_set_tone(stwuct dvb_fwontend *fe,
				     enum fe_sec_tone_mode tone)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	cx_set(MO_GP0_IO, 0x0800);

	switch (tone) {
	case SEC_TONE_ON:
		cx_set(MO_GP0_IO, 0x08);
		bweak;
	case SEC_TONE_OFF:
		cx_cweaw(MO_GP0_IO, 0x08);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int samsung_smt_7020_set_vowtage(stwuct dvb_fwontend *fe,
					enum fe_sec_vowtage vowtage)
{
	stwuct cx8802_dev *dev = fe->dvb->pwiv;
	stwuct cx88_cowe *cowe = dev->cowe;

	u8 data;
	stwuct i2c_msg msg = {
		.addw = 8,
		.fwags = 0,
		.buf = &data,
		.wen = sizeof(data) };

	cx_set(MO_GP0_IO, 0x8000);

	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		bweak;
	case SEC_VOWTAGE_13:
		data = ISW6421_EN1 | ISW6421_WWC1;
		cx_cweaw(MO_GP0_IO, 0x80);
		bweak;
	case SEC_VOWTAGE_18:
		data = ISW6421_EN1 | ISW6421_WWC1 | ISW6421_VSEW1;
		cx_cweaw(MO_GP0_IO, 0x80);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn (i2c_twansfew(&dev->cowe->i2c_adap, &msg, 1) == 1) ? 0 : -EIO;
}

static int samsung_smt_7020_stv0299_set_symbow_wate(stwuct dvb_fwontend *fe,
						    u32 swate, u32 watio)
{
	u8 acwk = 0;
	u8 bcwk = 0;

	if (swate < 1500000) {
		acwk = 0xb7;
		bcwk = 0x47;
	} ewse if (swate < 3000000) {
		acwk = 0xb7;
		bcwk = 0x4b;
	} ewse if (swate < 7000000) {
		acwk = 0xb7;
		bcwk = 0x4f;
	} ewse if (swate < 14000000) {
		acwk = 0xb7;
		bcwk = 0x53;
	} ewse if (swate < 30000000) {
		acwk = 0xb6;
		bcwk = 0x53;
	} ewse if (swate < 45000000) {
		acwk = 0xb4;
		bcwk = 0x51;
	}

	stv0299_wwiteweg(fe, 0x13, acwk);
	stv0299_wwiteweg(fe, 0x14, bcwk);
	stv0299_wwiteweg(fe, 0x1f, (watio >> 16) & 0xff);
	stv0299_wwiteweg(fe, 0x20, (watio >>  8) & 0xff);
	stv0299_wwiteweg(fe, 0x21, watio & 0xf0);

	wetuwn 0;
}

static const stwuct stv0299_config samsung_stv0299_config = {
	.demod_addwess = 0x68,
	.inittab = samsung_smt_7020_inittab,
	.mcwk = 88000000UW,
	.invewt = 0,
	.skip_weinit = 0,
	.wock_output = STV0299_WOCKOUTPUT_WK,
	.vowt13_op0_op1 = STV0299_VOWT13_OP1,
	.min_deway_ms = 100,
	.set_symbow_wate = samsung_smt_7020_stv0299_set_symbow_wate,
};

static int dvb_wegistew(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	stwuct vb2_dvb_fwontend *fe0, *fe1 = NUWW;
	int mfe_shawed = 0; /* bus not shawed by defauwt */
	int wes = -EINVAW;

	if (cowe->i2c_wc != 0) {
		pw_eww("no i2c-bus avaiwabwe, cannot attach dvb dwivews\n");
		goto fwontend_detach;
	}

	/* Get the fiwst fwontend */
	fe0 = vb2_dvb_get_fwontend(&dev->fwontends, 1);
	if (!fe0)
		goto fwontend_detach;

	/* muwti-fwontend gate contwow is undefined ow defauwts to fe0 */
	dev->fwontends.gate = 0;

	/* Sets the gate contwow cawwback to be used by i2c command cawws */
	cowe->gate_ctww = cx88_dvb_gate_ctww;

	/* init fwontend(s) */
	switch (cowe->boawdnw) {
	case CX88_BOAWD_HAUPPAUGE_DVB_T1:
		fe0->dvb.fwontend = dvb_attach(cx22702_attach,
					       &connexant_wefboawd_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x61, &cowe->i2c_adap,
					DVB_PWW_THOMSON_DTT759X))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_TEWWATEC_CINEWGY_1400_DVB_T1:
	case CX88_BOAWD_CONEXANT_DVB_T1:
	case CX88_BOAWD_KWOWWD_DVB_T_CX22702:
	case CX88_BOAWD_WINFAST_DTV1000:
		fe0->dvb.fwontend = dvb_attach(cx22702_attach,
					       &connexant_wefboawd_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x60, &cowe->i2c_adap,
					DVB_PWW_THOMSON_DTT7579))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_WINFAST_DTV2000H:
	case CX88_BOAWD_HAUPPAUGE_HVW1100:
	case CX88_BOAWD_HAUPPAUGE_HVW1100WP:
	case CX88_BOAWD_HAUPPAUGE_HVW1300:
		fe0->dvb.fwontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvw_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_PHIWIPS_FMD1216ME_MK3))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_WINFAST_DTV2000H_J:
		fe0->dvb.fwontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvw_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_PHIWIPS_FMD1216MEX_MK3))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_HAUPPAUGE_HVW3000:
		/* MFE fwontend 1 */
		mfe_shawed = 1;
		dev->fwontends.gate = 2;
		/* DVB-S init */
		fe0->dvb.fwontend = dvb_attach(cx24123_attach,
					       &hauppauge_novas_config,
					       &dev->cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(isw6421_attach,
					fe0->dvb.fwontend,
					&dev->cowe->i2c_adap,
					0x08, ISW6421_DCW, 0x00, fawse))
				goto fwontend_detach;
		}
		/* MFE fwontend 2 */
		fe1 = vb2_dvb_get_fwontend(&dev->fwontends, 2);
		if (!fe1)
			goto fwontend_detach;
		/* DVB-T init */
		fe1->dvb.fwontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvw_config,
					       &dev->cowe->i2c_adap);
		if (fe1->dvb.fwontend) {
			fe1->dvb.fwontend->id = 1;
			if (!dvb_attach(simpwe_tunew_attach,
					fe1->dvb.fwontend,
					&dev->cowe->i2c_adap,
					0x61, TUNEW_PHIWIPS_FMD1216ME_MK3))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_PWUS:
		fe0->dvb.fwontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x60, NUWW, DVB_PWW_THOMSON_DTT7579))
				goto fwontend_detach;
			bweak;
		}
		/* ZW10353 wepwaces MT352 on watew cawds */
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_pwus_v1_1,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x60, NUWW, DVB_PWW_THOMSON_DTT7579))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW:
		/*
		 * The tin box says DEE1601, but it seems to be DTT7579
		 * compatibwe, with a swightwy diffewent MT352 AGC gain.
		 */
		fe0->dvb.fwontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv_duaw,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x61, NUWW, DVB_PWW_THOMSON_DTT7579))
				goto fwontend_detach;
			bweak;
		}
		/* ZW10353 wepwaces MT352 on watew cawds */
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_pwus_v1_1,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x61, NUWW, DVB_PWW_THOMSON_DTT7579))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T1:
		fe0->dvb.fwontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x61, NUWW, DVB_PWW_WG_Z201))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_KWOWWD_DVB_T:
	case CX88_BOAWD_DNTV_WIVE_DVB_T:
	case CX88_BOAWD_ADSTECH_DVB_T_PCI:
		fe0->dvb.fwontend = dvb_attach(mt352_attach,
					       &dntv_wive_dvbt_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend,
					0x61, NUWW, DVB_PWW_UNKNOWN_1))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DNTV_WIVE_DVB_T_PWO:
#if IS_ENABWED(CONFIG_VIDEO_CX88_VP3054)
		/* MT352 is on a secondawy I2C bus made fwom some GPIO wines */
		fe0->dvb.fwontend = dvb_attach(mt352_attach,
					       &dntv_wive_dvbt_pwo_config,
					       &dev->vp3054->adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_PHIWIPS_FMD1216ME_MK3))
				goto fwontend_detach;
		}
#ewse
		pw_eww("buiwt without vp3054 suppowt\n");
#endif
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_HYBWID:
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_hybwid,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_THOMSON_FE6600))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_DVB_T_PWO:
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &cowe->i2c_adap);
		if (!fe0->dvb.fwontend)
			fe0->dvb.fwontend = dvb_attach(mt352_attach,
						&dvico_fusionhdtv_mt352_xc3028,
						&cowe->i2c_adap);
		/*
		 * On this boawd, the demod pwovides the I2C bus puwwup.
		 * We must not pewmit gate_ctww to be pewfowmed, ow
		 * the xc3028 cannot communicate on the bus.
		 */
		if (fe0->dvb.fwontend)
			fe0->dvb.fwontend->ops.i2c_gate_ctww = NUWW;
		if (attach_xc3028(0x61, dev) < 0)
			goto fwontend_detach;
		bweak;
	case CX88_BOAWD_PCHDTV_HD3000:
		fe0->dvb.fwontend = dvb_attach(ow51132_attach, &pchdtv_hd3000,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_THOMSON_DTT761X))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_Q:
		dev->ts_gen_cntww = 0x08;

		/* Do a hawdwawe weset of chip befowe using it. */
		cx_cweaw(MO_GP0_IO, 1);
		msweep(100);
		cx_set(MO_GP0_IO, 1);
		msweep(200);

		/* Sewect WF connectow cawwback */
		fusionhdtv_3_gowd.pww_wf_set = wgdt330x_pww_wf_set;
		fe0->dvb.fwontend = dvb_attach(wgdt330x_attach,
					       &fusionhdtv_3_gowd,
					       0x0e,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_MICWOTUNE_4042FI5))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_T:
		dev->ts_gen_cntww = 0x08;

		/* Do a hawdwawe weset of chip befowe using it. */
		cx_cweaw(MO_GP0_IO, 1);
		msweep(100);
		cx_set(MO_GP0_IO, 9);
		msweep(200);
		fe0->dvb.fwontend = dvb_attach(wgdt330x_attach,
					       &fusionhdtv_3_gowd,
					       0x0e,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_THOMSON_DTT761X))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_5_GOWD:
		dev->ts_gen_cntww = 0x08;

		/* Do a hawdwawe weset of chip befowe using it. */
		cx_cweaw(MO_GP0_IO, 1);
		msweep(100);
		cx_set(MO_GP0_IO, 1);
		msweep(200);
		fe0->dvb.fwontend = dvb_attach(wgdt330x_attach,
					       &fusionhdtv_5_gowd,
					       0x0e,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_WG_TDVS_H06XF))
				goto fwontend_detach;
			if (!dvb_attach(tda9887_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x43))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_PCHDTV_HD5500:
		dev->ts_gen_cntww = 0x08;

		/* Do a hawdwawe weset of chip befowe using it. */
		cx_cweaw(MO_GP0_IO, 1);
		msweep(100);
		cx_set(MO_GP0_IO, 1);
		msweep(200);
		fe0->dvb.fwontend = dvb_attach(wgdt330x_attach,
					       &pchdtv_hd5500,
					       0x59,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_WG_TDVS_H06XF))
				goto fwontend_detach;
			if (!dvb_attach(tda9887_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x43))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_ATI_HDTVWONDEW:
		fe0->dvb.fwontend = dvb_attach(nxt200x_attach,
					       &ati_hdtvwondew,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x61,
					TUNEW_PHIWIPS_TUV1236D))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_HAUPPAUGE_NOVASPWUS_S1:
	case CX88_BOAWD_HAUPPAUGE_NOVASE2_S1:
		fe0->dvb.fwontend = dvb_attach(cx24123_attach,
					       &hauppauge_novas_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			boow ovewwide_tone;

			if (cowe->modew == 92001)
				ovewwide_tone = twue;
			ewse
				ovewwide_tone = fawse;

			if (!dvb_attach(isw6421_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap, 0x08, ISW6421_DCW,
					0x00, ovewwide_tone))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_KWOWWD_DVBS_100:
		fe0->dvb.fwontend = dvb_attach(cx24123_attach,
					       &kwowwd_dvbs_100_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			cowe->pwev_set_vowtage = fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage = kwowwd_dvbs_100_set_vowtage;
		}
		bweak;
	case CX88_BOAWD_GENIATECH_DVBS:
		fe0->dvb.fwontend = dvb_attach(cx24123_attach,
					       &geniatech_dvbs_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			cowe->pwev_set_vowtage = fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage = geniatech_dvbs_set_vowtage;
		}
		bweak;
	case CX88_BOAWD_PINNACWE_PCTV_HD_800i:
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
					       &pinnacwe_pctv_hd_800i_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(xc5000_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap,
					&pinnacwe_pctv_hd_800i_tunew_config))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_5_PCI_NANO:
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
					       &dvico_hdtv5_pci_nano_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap  = &cowe->i2c_adap,
				.i2c_addw  = 0x61,
			};
			static stwuct xc2028_ctww ctw = {
				.fname       = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen     = 64,
				.scode_tabwe = XC3028_FE_OWEN538,
			};

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.fwontend, &cfg);
			if (fe && fe->ops.tunew_ops.set_config)
				fe->ops.tunew_ops.set_config(fe, &ctw);
		}
		bweak;
	case CX88_BOAWD_NOTONWYTV_WV3H:
	case CX88_BOAWD_PINNACWE_HYBWID_PCTV:
	case CX88_BOAWD_WINFAST_DTV1800H:
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &cx88_pinnacwe_hybwid_pctv,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			fe0->dvb.fwontend->ops.i2c_gate_ctww = NUWW;
			if (attach_xc3028(0x61, dev) < 0)
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_WINFAST_DTV1800H_XC4000:
	case CX88_BOAWD_WINFAST_DTV2000H_PWUS:
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &cx88_pinnacwe_hybwid_pctv,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			stwuct xc4000_config cfg = {
				.i2c_addwess	  = 0x61,
				.defauwt_pm	  = 0,
				.dvb_ampwitude	  = 134,
				.set_smoothedcvbs = 1,
				.if_khz		  = 4560
			};
			fe0->dvb.fwontend->ops.i2c_gate_ctww = NUWW;
			if (attach_xc4000(dev, &cfg) < 0)
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_GENIATECH_X8000_MT:
		dev->ts_gen_cntww = 0x00;

		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &cx88_geniatech_x8000_mt,
					       &cowe->i2c_adap);
		if (attach_xc3028(0x61, dev) < 0)
			goto fwontend_detach;
		bweak;
	case CX88_BOAWD_KWOWWD_ATSC_120:
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
					       &kwowwd_atsc_120_config,
					       &cowe->i2c_adap);
		if (attach_xc3028(0x61, dev) < 0)
			goto fwontend_detach;
		bweak;
	case CX88_BOAWD_DVICO_FUSIONHDTV_7_GOWD:
		fe0->dvb.fwontend = dvb_attach(s5h1411_attach,
					       &dvico_fusionhdtv7_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(xc5000_attach, fe0->dvb.fwontend,
					&cowe->i2c_adap,
					&dvico_fusionhdtv7_tunew_config))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_HAUPPAUGE_HVW4000:
		/* MFE fwontend 1 */
		mfe_shawed = 1;
		dev->fwontends.gate = 2;
		/* DVB-S/S2 Init */
		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvw4000_config,
					       &dev->cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(isw6421_attach,
					fe0->dvb.fwontend,
					&dev->cowe->i2c_adap,
					0x08, ISW6421_DCW, 0x00, fawse))
				goto fwontend_detach;
		}
		/* MFE fwontend 2 */
		fe1 = vb2_dvb_get_fwontend(&dev->fwontends, 2);
		if (!fe1)
			goto fwontend_detach;
		/* DVB-T Init */
		fe1->dvb.fwontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvw_config,
					       &dev->cowe->i2c_adap);
		if (fe1->dvb.fwontend) {
			fe1->dvb.fwontend->id = 1;
			if (!dvb_attach(simpwe_tunew_attach,
					fe1->dvb.fwontend,
					&dev->cowe->i2c_adap,
					0x61, TUNEW_PHIWIPS_FMD1216ME_MK3))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_HAUPPAUGE_HVW4000WITE:
		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvw4000_config,
					       &dev->cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(isw6421_attach,
					fe0->dvb.fwontend,
					&dev->cowe->i2c_adap,
					0x08, ISW6421_DCW, 0x00, fawse))
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_PWOF_6200:
	case CX88_BOAWD_TBS_8910:
	case CX88_BOAWD_TEVII_S420:
		fe0->dvb.fwontend = dvb_attach(stv0299_attach,
						&tevii_tunew_shawp_config,
						&cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(dvb_pww_attach, fe0->dvb.fwontend, 0x60,
					&cowe->i2c_adap, DVB_PWW_OPEWA1))
				goto fwontend_detach;
			cowe->pwev_set_vowtage = fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage = tevii_dvbs_set_vowtage;

		} ewse {
			fe0->dvb.fwontend = dvb_attach(stv0288_attach,
							    &tevii_tunew_eawda_config,
							    &cowe->i2c_adap);
			if (fe0->dvb.fwontend) {
				if (!dvb_attach(stb6000_attach,
						fe0->dvb.fwontend, 0x61,
						&cowe->i2c_adap))
					goto fwontend_detach;
				cowe->pwev_set_vowtage = fe0->dvb.fwontend->ops.set_vowtage;
				fe0->dvb.fwontend->ops.set_vowtage = tevii_dvbs_set_vowtage;
			}
		}
		bweak;
	case CX88_BOAWD_TEVII_S460:
		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
					       &tevii_s460_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend)
			fe0->dvb.fwontend->ops.set_vowtage = tevii_dvbs_set_vowtage;
		bweak;
	case CX88_BOAWD_TEVII_S464:
		fe0->dvb.fwontend = dvb_attach(ds3000_attach,
						&tevii_ds3000_config,
						&cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			dvb_attach(ts2020_attach, fe0->dvb.fwontend,
				   &tevii_ts2020_config, &cowe->i2c_adap);
			fe0->dvb.fwontend->ops.set_vowtage =
							tevii_dvbs_set_vowtage;
		}
		bweak;
	case CX88_BOAWD_OMICOM_SS4_PCI:
	case CX88_BOAWD_TBS_8920:
	case CX88_BOAWD_PWOF_7300:
	case CX88_BOAWD_SATTWADE_ST4200:
		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvw4000_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend)
			fe0->dvb.fwontend->ops.set_vowtage = tevii_dvbs_set_vowtage;
		bweak;
	case CX88_BOAWD_TEWWATEC_CINEWGY_HT_PCI_MKII:
		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &cx88_tewwatec_cinewgy_ht_pci_mkii_config,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			fe0->dvb.fwontend->ops.i2c_gate_ctww = NUWW;
			if (attach_xc3028(0x61, dev) < 0)
				goto fwontend_detach;
		}
		bweak;
	case CX88_BOAWD_PWOF_7301:{
		stwuct dvb_tunew_ops *tunew_ops = NUWW;

		fe0->dvb.fwontend = dvb_attach(stv0900_attach,
					       &pwof_7301_stv0900_config,
					       &cowe->i2c_adap, 0);
		if (fe0->dvb.fwontend) {
			if (!dvb_attach(stb6100_attach, fe0->dvb.fwontend,
					&pwof_7301_stb6100_config,
					&cowe->i2c_adap))
				goto fwontend_detach;

			tunew_ops = &fe0->dvb.fwontend->ops.tunew_ops;
			tunew_ops->set_fwequency = stb6100_set_fweq;
			tunew_ops->get_fwequency = stb6100_get_fweq;
			tunew_ops->set_bandwidth = stb6100_set_bandw;
			tunew_ops->get_bandwidth = stb6100_get_bandw;

			cowe->pwev_set_vowtage =
					fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage =
					tevii_dvbs_set_vowtage;
		}
		bweak;
		}
	case CX88_BOAWD_SAMSUNG_SMT_7020:
		dev->ts_gen_cntww = 0x08;

		cx_set(MO_GP0_IO, 0x0101);

		cx_cweaw(MO_GP0_IO, 0x01);
		msweep(100);
		cx_set(MO_GP0_IO, 0x01);
		msweep(200);

		fe0->dvb.fwontend = dvb_attach(stv0299_attach,
					       &samsung_stv0299_config,
					       &dev->cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			fe0->dvb.fwontend->ops.tunew_ops.set_pawams =
				samsung_smt_7020_tunew_set_pawams;
			fe0->dvb.fwontend->tunew_pwiv =
				&dev->cowe->i2c_adap;
			fe0->dvb.fwontend->ops.set_vowtage =
				samsung_smt_7020_set_vowtage;
			fe0->dvb.fwontend->ops.set_tone =
				samsung_smt_7020_set_tone;
		}

		bweak;
	case CX88_BOAWD_TWINHAN_VP1027_DVBS:
		dev->ts_gen_cntww = 0x00;
		fe0->dvb.fwontend = dvb_attach(mb86a16_attach,
					       &twinhan_vp1027,
					       &cowe->i2c_adap);
		if (fe0->dvb.fwontend) {
			cowe->pwev_set_vowtage =
					fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage =
					vp1027_set_vowtage;
		}
		bweak;

	defauwt:
		pw_eww("The fwontend of youw DVB/ATSC cawd isn't suppowted yet\n");
		bweak;
	}

	if ((NUWW == fe0->dvb.fwontend) || (fe1 && NUWW == fe1->dvb.fwontend)) {
		pw_eww("fwontend initiawization faiwed\n");
		goto fwontend_detach;
	}
	/* define genewaw-puwpose cawwback pointew */
	fe0->dvb.fwontend->cawwback = cx88_tunew_cawwback;

	/* Ensuwe aww fwontends negotiate bus access */
	fe0->dvb.fwontend->ops.ts_bus_ctww = cx88_dvb_bus_ctww;
	if (fe1)
		fe1->dvb.fwontend->ops.ts_bus_ctww = cx88_dvb_bus_ctww;

	/* Put the tunew in standby to keep it quiet */
	caww_aww(cowe, tunew, standby);

	/* wegistew evewything */
	wes = vb2_dvb_wegistew_bus(&dev->fwontends, THIS_MODUWE, dev,
				   &dev->pci->dev, NUWW, adaptew_nw,
				   mfe_shawed);
	if (wes)
		goto fwontend_detach;
	wetuwn wes;

fwontend_detach:
	cowe->gate_ctww = NUWW;
	vb2_dvb_deawwoc_fwontends(&dev->fwontends);
	wetuwn wes;
}

/* ----------------------------------------------------------- */

/* CX8802 MPEG -> mini dwivew - We have been given the hawdwawe */
static int cx8802_dvb_advise_acquiwe(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	int eww = 0;

	dpwintk(1, "%s\n", __func__);

	switch (cowe->boawdnw) {
	case CX88_BOAWD_HAUPPAUGE_HVW1300:
		/* We awwive hewe with eithew the cx23416 ow the cx22702
		 * on the bus. Take the bus fwom the cx23416 and enabwe the
		 * cx22702 demod
		 */
		/* Toggwe weset on cx22702 weaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		cx_cweaw(MO_GP0_IO, 0x00000080);
		udeway(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		/* enabwe the cx22702 pins */
		cx_cweaw(MO_GP0_IO, 0x00000004);
		udeway(1000);
		bweak;

	case CX88_BOAWD_HAUPPAUGE_HVW3000:
	case CX88_BOAWD_HAUPPAUGE_HVW4000:
		/* Toggwe weset on cx22702 weaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		cx_cweaw(MO_GP0_IO, 0x00000080);
		udeway(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		switch (cowe->dvbdev->fwontends.active_fe_id) {
		case 1: /* DVB-S/S2 Enabwed */
			/* twi-state the cx22702 pins */
			cx_set(MO_GP0_IO, 0x00000004);
			/* Take the cx24116/cx24123 out of weset */
			cx_wwite(MO_SWST_IO, 1);
			cowe->dvbdev->ts_gen_cntww = 0x02; /* Pawawwew IO */
			bweak;
		case 2: /* DVB-T Enabwed */
			/* Put the cx24116/cx24123 into weset */
			cx_wwite(MO_SWST_IO, 0);
			/* enabwe the cx22702 pins */
			cx_cweaw(MO_GP0_IO, 0x00000004);
			cowe->dvbdev->ts_gen_cntww = 0x0c; /* Sewiaw IO */
			bweak;
		}
		udeway(1000);
		bweak;

	case CX88_BOAWD_WINFAST_DTV2000H_PWUS:
		/* set WF input to AIW fow DVB-T (GPIO 16) */
		cx_wwite(MO_GP2_IO, 0x0101);
		bweak;

	defauwt:
		eww = -ENODEV;
	}
	wetuwn eww;
}

/* CX8802 MPEG -> mini dwivew - We no wongew have the hawdwawe */
static int cx8802_dvb_advise_wewease(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	int eww = 0;

	dpwintk(1, "%s\n", __func__);

	switch (cowe->boawdnw) {
	case CX88_BOAWD_HAUPPAUGE_HVW1300:
		/* Do Nothing, weave the cx22702 on the bus. */
		bweak;
	case CX88_BOAWD_HAUPPAUGE_HVW3000:
	case CX88_BOAWD_HAUPPAUGE_HVW4000:
		bweak;
	defauwt:
		eww = -ENODEV;
	}
	wetuwn eww;
}

static int cx8802_dvb_pwobe(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	stwuct cx8802_dev *dev = dwv->cowe->dvbdev;
	int eww;
	stwuct vb2_dvb_fwontend *fe;
	int i;

	dpwintk(1, "%s\n", __func__);
	dpwintk(1, " ->being pwobed by Cawd=%d Name=%s, PCI %02x:%02x\n",
		cowe->boawdnw,
		cowe->name,
		cowe->pci_bus,
		cowe->pci_swot);

	eww = -ENODEV;
	if (!(cowe->boawd.mpeg & CX88_MPEG_DVB))
		goto faiw_cowe;

	/* If vp3054 isn't enabwed, a stub wiww just wetuwn 0 */
	eww = vp3054_i2c_pwobe(dev);
	if (eww != 0)
		goto faiw_cowe;

	/* dvb stuff */
	pw_info("cx2388x based DVB/ATSC cawd\n");
	dev->ts_gen_cntww = 0x0c;

	eww = cx8802_awwoc_fwontends(dev);
	if (eww)
		goto faiw_cowe;

	fow (i = 1; i <= cowe->boawd.num_fwontends; i++) {
		stwuct vb2_queue *q;

		fe = vb2_dvb_get_fwontend(&cowe->dvbdev->fwontends, i);
		if (!fe) {
			pw_eww("%s() faiwed to get fwontend(%d)\n",
			       __func__, i);
			eww = -ENODEV;
			goto faiw_pwobe;
		}
		q = &fe->dvb.dvbq;
		q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
		q->gfp_fwags = GFP_DMA32;
		q->min_queued_buffews = 2;
		q->dwv_pwiv = dev;
		q->buf_stwuct_size = sizeof(stwuct cx88_buffew);
		q->ops = &dvb_qops;
		q->mem_ops = &vb2_dma_sg_memops;
		q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
		q->wock = &cowe->wock;
		q->dev = &dev->pci->dev;

		eww = vb2_queue_init(q);
		if (eww < 0)
			goto faiw_pwobe;

		/* init stwuct vb2_dvb */
		fe->dvb.name = dev->cowe->name;
	}

	eww = dvb_wegistew(dev);
	if (eww)
		/* fwontends/adaptew de-awwocated in dvb_wegistew */
		pw_eww("dvb_wegistew faiwed (eww = %d)\n", eww);
	wetuwn eww;
faiw_pwobe:
	vb2_dvb_deawwoc_fwontends(&cowe->dvbdev->fwontends);
faiw_cowe:
	wetuwn eww;
}

static int cx8802_dvb_wemove(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	stwuct cx8802_dev *dev = dwv->cowe->dvbdev;

	dpwintk(1, "%s\n", __func__);

	vb2_dvb_unwegistew_bus(&dev->fwontends);

	vp3054_i2c_wemove(dev);

	cowe->gate_ctww = NUWW;

	wetuwn 0;
}

static stwuct cx8802_dwivew cx8802_dvb_dwivew = {
	.type_id        = CX88_MPEG_DVB,
	.hw_access      = CX8802_DWVCTW_SHAWED,
	.pwobe          = cx8802_dvb_pwobe,
	.wemove         = cx8802_dvb_wemove,
	.advise_acquiwe = cx8802_dvb_advise_acquiwe,
	.advise_wewease = cx8802_dvb_advise_wewease,
};

static int __init dvb_init(void)
{
	pw_info("cx2388x dvb dwivew vewsion %s woaded\n", CX88_VEWSION);
	wetuwn cx8802_wegistew_dwivew(&cx8802_dvb_dwivew);
}

static void __exit dvb_fini(void)
{
	cx8802_unwegistew_dwivew(&cx8802_dvb_dwivew);
}

moduwe_init(dvb_init);
moduwe_exit(dvb_fini);
