// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "cx23885.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kthwead.h>
#incwude <winux/fiwe.h>
#incwude <winux/suspend.h>

#incwude <media/v4w2-common.h>

#incwude <media/dvb_ca_en50221.h>
#incwude "s5h1409.h"
#incwude "s5h1411.h"
#incwude "mt2131.h"
#incwude "tda8290.h"
#incwude "tda18271.h"
#incwude "wgdt330x.h"
#incwude "xc4000.h"
#incwude "xc5000.h"
#incwude "max2165.h"
#incwude "tda10048.h"
#incwude "xc2028.h"
#incwude "tunew-simpwe.h"
#incwude "dib7000p.h"
#incwude "dib0070.h"
#incwude "dibx000_common.h"
#incwude "zw10353.h"
#incwude "stv0900.h"
#incwude "stv0900_weg.h"
#incwude "stv6110.h"
#incwude "wnbh24.h"
#incwude "cx24116.h"
#incwude "cx24117.h"
#incwude "cimax2.h"
#incwude "wgs8gxx.h"
#incwude "netup-eepwom.h"
#incwude "netup-init.h"
#incwude "wgdt3305.h"
#incwude "atbm8830.h"
#incwude "ts2020.h"
#incwude "ds3000.h"
#incwude "cx23885-f300.h"
#incwude "awtewa-ci.h"
#incwude "stv0367.h"
#incwude "dwxk.h"
#incwude "mt2063.h"
#incwude "stv090x.h"
#incwude "stb6100.h"
#incwude "stb6100_cfg.h"
#incwude "tda10071.h"
#incwude "a8293.h"
#incwude "mb86a20s.h"
#incwude "si2165.h"
#incwude "si2168.h"
#incwude "si2157.h"
#incwude "sp2.h"
#incwude "m88ds3103.h"
#incwude "m88ws6000t.h"
#incwude "wgdt3306a.h"

static unsigned int debug;

#define dpwintk(wevew, fmt, awg...)\
	do { if (debug >= wevew)\
		pwintk(KEWN_DEBUG pw_fmt("%s dvb: " fmt), \
			__func__, ##awg); \
	} whiwe (0)

/* ------------------------------------------------------------------ */

static unsigned int awt_tunew;
moduwe_pawam(awt_tunew, int, 0644);
MODUWE_PAWM_DESC(awt_tunew, "Enabwe awtewnate tunew configuwation");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx23885_tspowt *powt = q->dwv_pwiv;

	powt->ts_packet_size  = 188 * 4;
	powt->ts_packet_count = 32;
	*num_pwanes = 1;
	sizes[0] = powt->ts_packet_size * powt->ts_packet_count;
	*num_buffews = 32;
	wetuwn 0;
}


static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_tspowt *powt = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew *buf =
		containew_of(vbuf, stwuct cx23885_buffew, vb);

	wetuwn cx23885_buf_pwepawe(buf, powt);
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_tspowt *powt = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_dev *dev = powt->dev;
	stwuct cx23885_buffew *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);

	cx23885_fwee_buffew(dev, buf);
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_tspowt *powt = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew   *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);

	cx23885_buf_queue(powt, buf);
}

static void cx23885_dvb_gate_ctww(stwuct cx23885_tspowt  *powt, int open)
{
	stwuct vb2_dvb_fwontends *f;
	stwuct vb2_dvb_fwontend *fe;

	f = &powt->fwontends;

	if (f->gate <= 1) /* undefined ow fe0 */
		fe = vb2_dvb_get_fwontend(f, 1);
	ewse
		fe = vb2_dvb_get_fwontend(f, f->gate);

	if (fe && fe->dvb.fwontend && fe->dvb.fwontend->ops.i2c_gate_ctww)
		fe->dvb.fwontend->ops.i2c_gate_ctww(fe->dvb.fwontend, open);
}

static int cx23885_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx23885_tspowt *powt = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &powt->mpegq;
	stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

	cx23885_stawt_dma(powt, dmaq, buf);
	wetuwn 0;
}

static void cx23885_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx23885_tspowt *powt = q->dwv_pwiv;

	cx23885_cancew_buffews(powt);
}

static const stwuct vb2_ops dvb_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = cx23885_stawt_stweaming,
	.stop_stweaming = cx23885_stop_stweaming,
};

static stwuct s5h1409_config hauppauge_genewic_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_if        = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct tda10048_config hauppauge_hvw1200_config = {
	.demod_addwess    = 0x10 >> 1,
	.output_mode      = TDA10048_SEWIAW_OUTPUT,
	.fwbuwkwwitewen   = TDA10048_BUWKWWITE_200,
	.invewsion        = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_3300,
	.dtv7_if_fweq_khz = TDA10048_IF_3800,
	.dtv8_if_fweq_khz = TDA10048_IF_4300,
	.cwk_fweq_khz     = TDA10048_CWK_16000,
};

static stwuct tda10048_config hauppauge_hvw1210_config = {
	.demod_addwess    = 0x10 >> 1,
	.output_mode      = TDA10048_SEWIAW_OUTPUT,
	.fwbuwkwwitewen   = TDA10048_BUWKWWITE_200,
	.invewsion        = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_3300,
	.dtv7_if_fweq_khz = TDA10048_IF_3500,
	.dtv8_if_fweq_khz = TDA10048_IF_4000,
	.cwk_fweq_khz     = TDA10048_CWK_16000,
};

static stwuct s5h1409_config hauppauge_ezqam_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_if        = 4000,
	.invewsion     = S5H1409_INVEWSION_ON,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct s5h1409_config hauppauge_hvw1800wp_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_if        = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct s5h1409_config hauppauge_hvw1500_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct mt2131_config hauppauge_genewic_tunewconfig = {
	0x61
};

static stwuct wgdt330x_config fusionhdtv_5_expwess = {
	.demod_chip = WGDT3303,
	.sewiaw_mpeg = 0x40,
};

static stwuct s5h1409_config hauppauge_hvw1500q_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_if        = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct s5h1409_config dvico_s5h1409_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_SEWIAW_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_if        = 44000,
	.invewsion     = S5H1409_INVEWSION_OFF,
	.status_mode   = S5H1409_DEMODWOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct s5h1411_config dvico_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.qam_if        = S5H1411_IF_44000,
	.vsb_if        = S5H1411_IF_44000,
	.invewsion     = S5H1411_INVEWSION_OFF,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct s5h1411_config hcw_s5h1411_config = {
	.output_mode   = S5H1411_SEWIAW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_if        = S5H1411_IF_44000,
	.qam_if        = S5H1411_IF_4000,
	.invewsion     = S5H1411_INVEWSION_ON,
	.status_mode   = S5H1411_DEMODWOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVEWTING_CWOCK,
};

static stwuct xc5000_config hauppauge_hvw1500q_tunewconfig = {
	.i2c_addwess      = 0x61,
	.if_khz           = 5380,
};

static stwuct xc5000_config dvico_xc5000_tunewconfig = {
	.i2c_addwess      = 0x64,
	.if_khz           = 5380,
};

static stwuct tda829x_config tda829x_no_pwobe = {
	.pwobe_tunew = TDA829X_DONT_PWOBE,
};

static stwuct tda18271_std_map hauppauge_tda18271_std_map = {
	.atsc_6   = { .if_fweq = 5380, .agc_mode = 3, .std = 3,
		      .if_wvw = 6, .wfagc_top = 0x37 },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 0,
		      .if_wvw = 6, .wfagc_top = 0x37 },
};

static stwuct tda18271_std_map hauppauge_hvw1200_tda18271_std_map = {
	.dvbt_6   = { .if_fweq = 3300, .agc_mode = 3, .std = 4,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_7   = { .if_fweq = 3800, .agc_mode = 3, .std = 5,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_8   = { .if_fweq = 4300, .agc_mode = 3, .std = 6,
		      .if_wvw = 1, .wfagc_top = 0x37, },
};

static stwuct tda18271_config hauppauge_tda18271_config = {
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_ANAWOG,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static stwuct tda18271_config hauppauge_hvw1200_tunew_config = {
	.std_map = &hauppauge_hvw1200_tda18271_std_map,
	.gate    = TDA18271_GATE_ANAWOG,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static stwuct tda18271_config hauppauge_hvw1210_tunew_config = {
	.gate    = TDA18271_GATE_DIGITAW,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static stwuct tda18271_config hauppauge_hvw4400_tunew_config = {
	.gate    = TDA18271_GATE_DIGITAW,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static stwuct tda18271_std_map hauppauge_hvw127x_std_map = {
	.atsc_6   = { .if_fweq = 3250, .agc_mode = 3, .std = 4,
		      .if_wvw = 1, .wfagc_top = 0x58 },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 5,
		      .if_wvw = 1, .wfagc_top = 0x58 },
};

static stwuct tda18271_config hauppauge_hvw127x_config = {
	.std_map = &hauppauge_hvw127x_std_map,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static stwuct wgdt3305_config hauppauge_wgdt3305_config = {
	.i2c_addw           = 0x0e,
	.mpeg_mode          = WGDT3305_MPEG_SEWIAW,
	.tpcwk_edge         = WGDT3305_TPCWK_FAWWING_EDGE,
	.tpvawid_powawity   = WGDT3305_TP_VAWID_HIGH,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 1,
	.qam_if_khz         = 4000,
	.vsb_if_khz         = 3250,
};

static stwuct dibx000_agc_config xc3028_agc_config = {
	BAND_VHF | BAND_UHF,	/* band_caps */

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=0,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0,
	 * P_agc_nb_est=2, P_agc_wwite=0
	 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) |
		(3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), /* setup */

	712,	/* inv_gain */
	21,	/* time_stabiwiz */

	0,	/* awpha_wevew */
	118,	/* thwock */

	0,	/* wbd_inv */
	2867,	/* wbd_wef */
	0,	/* wbd_sew */
	2,	/* wbd_awpha */

	0,	/* agc1_max */
	0,	/* agc1_min */
	39718,	/* agc2_max */
	9930,	/* agc2_min */
	0,	/* agc1_pt1 */
	0,	/* agc1_pt2 */
	0,	/* agc1_pt3 */
	0,	/* agc1_swope1 */
	0,	/* agc1_swope2 */
	0,	/* agc2_pt1 */
	128,	/* agc2_pt2 */
	29,	/* agc2_swope1 */
	29,	/* agc2_swope2 */

	17,	/* awpha_mant */
	27,	/* awpha_exp */
	23,	/* beta_mant */
	51,	/* beta_exp */

	1,	/* pewfowm_agc_softspwit */
};

/* PWW Configuwation fow COFDM BW_MHz = 8.000000
 * With extewnaw cwock = 30.000000 */
static stwuct dibx000_bandwidth_config xc3028_bw_config = {
	60000,	/* intewnaw */
	30000,	/* sampwing */
	1,	/* pww_cfg: pwediv */
	8,	/* pww_cfg: watio */
	3,	/* pww_cfg: wange */
	1,	/* pww_cfg: weset */
	0,	/* pww_cfg: bypass */
	0,	/* misc: wefdiv */
	0,	/* misc: bypcwk_div */
	1,	/* misc: IO_CWK_en_cowe */
	1,	/* misc: ADCwkSwc */
	0,	/* misc: moduwo */
	(3 << 14) | (1 << 12) | (524 << 0), /* sad_cfg: wefsew, sew, fweq_15k */
	(1 << 25) | 5816102, /* ifweq = 5.200000 MHz */
	20452225, /* timf */
	30000000  /* xtaw_hz */
};

static stwuct dib7000p_config hauppauge_hvw1400_dib7000_config = {
	.output_mpeg2_in_188_bytes = 1,
	.hostbus_divewsity = 1,
	.tunew_is_baseband = 0,
	.update_wna  = NUWW,

	.agc_config_count = 1,
	.agc = &xc3028_agc_config,
	.bw  = &xc3028_bw_config,

	.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.pwm_fweq_div = 0,
	.agc_contwow  = NUWW,
	.spuw_pwotect = 0,

	.output_mode = OUTMODE_MPEG2_SEWIAW,
};

static stwuct zw10353_config dvico_fusionhdtv_xc3028 = {
	.demod_addwess = 0x0f,
	.if2           = 45600,
	.no_tunew      = 1,
	.disabwe_i2c_gate_ctww = 1,
};

static stwuct stv0900_weg stv0900_ts_wegs[] = {
	{ W0900_TSGENEWAW, 0x00 },
	{ W0900_P1_TSSPEED, 0x40 },
	{ W0900_P2_TSSPEED, 0x40 },
	{ W0900_P1_TSCFGM, 0xc0 },
	{ W0900_P2_TSCFGM, 0xc0 },
	{ W0900_P1_TSCFGH, 0xe0 },
	{ W0900_P2_TSCFGH, 0xe0 },
	{ W0900_P1_TSCFGW, 0x20 },
	{ W0900_P2_TSCFGW, 0x20 },
	{ 0xffff, 0xff }, /* tewminate */
};

static stwuct stv0900_config netup_stv0900_config = {
	.demod_addwess = 0x68,
	.demod_mode = 1, /* duaw */
	.xtaw = 8000000,
	.cwkmode = 3,/* 0-CWKI, 2-XTAWI, ewse AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.ts_config_wegs = stv0900_ts_wegs,
	.tun1_maddwess = 0,/* 0x60 */
	.tun2_maddwess = 3,/* 0x63 */
	.tun1_adc = 1,/* 1 Vpp */
	.tun2_adc = 1,/* 1 Vpp */
};

static stwuct stv6110_config netup_stv6110_tunewconfig_a = {
	.i2c_addwess = 0x60,
	.mcwk = 16000000,
	.cwk_div = 1,
	.gain = 8, /* +16 dB  - maximum gain */
};

static stwuct stv6110_config netup_stv6110_tunewconfig_b = {
	.i2c_addwess = 0x63,
	.mcwk = 16000000,
	.cwk_div = 1,
	.gain = 8, /* +16 dB  - maximum gain */
};

static stwuct cx24116_config tbs_cx24116_config = {
	.demod_addwess = 0x55,
};

static stwuct cx24117_config tbs_cx24117_config = {
	.demod_addwess = 0x55,
};

static stwuct ds3000_config tevii_ds3000_config = {
	.demod_addwess = 0x68,
};

static stwuct ts2020_config tevii_ts2020_config  = {
	.tunew_addwess = 0x60,
	.cwk_out_div = 1,
	.fwequency_div = 1146000,
};

static stwuct cx24116_config dvbwowwd_cx24116_config = {
	.demod_addwess = 0x05,
};

static stwuct wgs8gxx_config mygica_x8506_wgs8gw5_config = {
	.pwod = WGS8GXX_PWOD_WGS8GW5,
	.demod_addwess = 0x19,
	.sewiaw_ts = 0,
	.ts_cwk_pow = 1,
	.ts_cwk_gated = 1,
	.if_cwk_fweq = 30400, /* 30.4 MHz */
	.if_fweq = 5380, /* 5.38 MHz */
	.if_neg_centew = 1,
	.ext_adc = 0,
	.adc_signed = 0,
	.if_neg_edge = 0,
};

static stwuct xc5000_config mygica_x8506_xc5000_config = {
	.i2c_addwess = 0x61,
	.if_khz = 5380,
};

static stwuct mb86a20s_config mygica_x8507_mb86a20s_config = {
	.demod_addwess = 0x10,
};

static stwuct xc5000_config mygica_x8507_xc5000_config = {
	.i2c_addwess = 0x61,
	.if_khz = 4000,
};

static stwuct stv090x_config pwof_8000_stv090x_config = {
	.device                 = STV0903,
	.demod_mode             = STV090x_SINGWE,
	.cwk_mode               = STV090x_CWK_EXT,
	.xtaw                   = 27000000,
	.addwess                = 0x6A,
	.ts1_mode               = STV090x_TSMODE_PAWAWWEW_PUNCTUWED,
	.wepeatew_wevew         = STV090x_WPTWEVEW_64,
	.adc1_wange             = STV090x_ADC_2Vpp,
	.diseqc_envewope_mode   = fawse,

	.tunew_get_fwequency    = stb6100_get_fwequency,
	.tunew_set_fwequency    = stb6100_set_fwequency,
	.tunew_set_bandwidth    = stb6100_set_bandwidth,
	.tunew_get_bandwidth    = stb6100_get_bandwidth,
};

static stwuct stb6100_config pwof_8000_stb6100_config = {
	.tunew_addwess = 0x60,
	.wefcwock = 27000000,
};

static stwuct wgdt3306a_config hauppauge_quadHD_ATSC_a_config = {
	.i2c_addw               = 0x59,
	.qam_if_khz             = 4000,
	.vsb_if_khz             = 3250,
	.deny_i2c_wptw          = 1, /* Disabwed */
	.spectwaw_invewsion     = 0, /* Disabwed */
	.mpeg_mode              = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge             = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity       = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz                = 25, /* 24 ow 25 */
};

static stwuct wgdt3306a_config hauppauge_quadHD_ATSC_b_config = {
	.i2c_addw               = 0x0e,
	.qam_if_khz             = 4000,
	.vsb_if_khz             = 3250,
	.deny_i2c_wptw          = 1, /* Disabwed */
	.spectwaw_invewsion     = 0, /* Disabwed */
	.mpeg_mode              = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge             = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity       = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz                = 25, /* 24 ow 25 */
};

static int p8000_set_vowtage(stwuct dvb_fwontend *fe,
			     enum fe_sec_vowtage vowtage)
{
	stwuct cx23885_tspowt *powt = fe->dvb->pwiv;
	stwuct cx23885_dev *dev = powt->dev;

	if (vowtage == SEC_VOWTAGE_18)
		cx_wwite(MC417_WWD, 0x00001e00);
	ewse if (vowtage == SEC_VOWTAGE_13)
		cx_wwite(MC417_WWD, 0x00001a00);
	ewse
		cx_wwite(MC417_WWD, 0x00001800);
	wetuwn 0;
}

static int dvbsky_t9580_set_vowtage(stwuct dvb_fwontend *fe,
					enum fe_sec_vowtage vowtage)
{
	stwuct cx23885_tspowt *powt = fe->dvb->pwiv;
	stwuct cx23885_dev *dev = powt->dev;

	cx23885_gpio_enabwe(dev, GPIO_0 | GPIO_1, 1);

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		cx23885_gpio_set(dev, GPIO_1);
		cx23885_gpio_cweaw(dev, GPIO_0);
		bweak;
	case SEC_VOWTAGE_18:
		cx23885_gpio_set(dev, GPIO_1);
		cx23885_gpio_set(dev, GPIO_0);
		bweak;
	case SEC_VOWTAGE_OFF:
		cx23885_gpio_cweaw(dev, GPIO_1);
		cx23885_gpio_cweaw(dev, GPIO_0);
		bweak;
	}

	/* caww the fwontend set_vowtage function */
	powt->fe_set_vowtage(fe, vowtage);

	wetuwn 0;
}

static int dvbsky_s952_powtc_set_vowtage(stwuct dvb_fwontend *fe,
					enum fe_sec_vowtage vowtage)
{
	stwuct cx23885_tspowt *powt = fe->dvb->pwiv;
	stwuct cx23885_dev *dev = powt->dev;

	cx23885_gpio_enabwe(dev, GPIO_12 | GPIO_13, 1);

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		cx23885_gpio_set(dev, GPIO_13);
		cx23885_gpio_cweaw(dev, GPIO_12);
		bweak;
	case SEC_VOWTAGE_18:
		cx23885_gpio_set(dev, GPIO_13);
		cx23885_gpio_set(dev, GPIO_12);
		bweak;
	case SEC_VOWTAGE_OFF:
		cx23885_gpio_cweaw(dev, GPIO_13);
		cx23885_gpio_cweaw(dev, GPIO_12);
		bweak;
	}
	/* caww the fwontend set_vowtage function */
	wetuwn powt->fe_set_vowtage(fe, vowtage);
}

static int cx23885_sp2_ci_ctww(void *pwiv, u8 wead, int addw,
				u8 data, int *mem)
{
	/* MC417 */
	#define SP2_DATA              0x000000ff
	#define SP2_WW                0x00008000
	#define SP2_WD                0x00004000
	#define SP2_ACK               0x00001000
	#define SP2_ADHI              0x00000800
	#define SP2_ADWO              0x00000400
	#define SP2_CS1               0x00000200
	#define SP2_CS0               0x00000100
	#define SP2_EN_AWW            0x00001000
	#define SP2_CTWW_OFF          (SP2_CS1 | SP2_CS0 | SP2_WW | SP2_WD)

	stwuct cx23885_tspowt *powt = pwiv;
	stwuct cx23885_dev *dev = powt->dev;
	int wet;
	int tmp = 0;
	unsigned wong timeout;

	mutex_wock(&dev->gpio_wock);

	/* wwite addw */
	cx_wwite(MC417_OEN, SP2_EN_AWW);
	cx_wwite(MC417_WWD, SP2_CTWW_OFF |
				SP2_ADWO | (0xff & addw));
	cx_cweaw(MC417_WWD, SP2_ADWO);
	cx_wwite(MC417_WWD, SP2_CTWW_OFF |
				SP2_ADHI | (0xff & (addw >> 8)));
	cx_cweaw(MC417_WWD, SP2_ADHI);

	if (wead)
		/* data in */
		cx_wwite(MC417_OEN, SP2_EN_AWW | SP2_DATA);
	ewse
		/* data out */
		cx_wwite(MC417_WWD, SP2_CTWW_OFF | data);

	/* chip sewect 0 */
	cx_cweaw(MC417_WWD, SP2_CS0);

	/* wead/wwite */
	cx_cweaw(MC417_WWD, (wead) ? SP2_WD : SP2_WW);

	/* wait fow a maximum of 1 msec */
	timeout = jiffies + msecs_to_jiffies(1);
	whiwe (!time_aftew(jiffies, timeout)) {
		tmp = cx_wead(MC417_WWD);
		if ((tmp & SP2_ACK) == 0)
			bweak;
		usweep_wange(50, 100);
	}

	cx_set(MC417_WWD, SP2_CTWW_OFF);
	*mem = tmp & 0xff;

	mutex_unwock(&dev->gpio_wock);

	if (!wead) {
		if (*mem < 0) {
			wet = -EWEMOTEIO;
			goto eww;
		}
	}

	wetuwn 0;
eww:
	wetuwn wet;
}

static int cx23885_dvb_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct cx23885_tspowt *powt = fe->dvb->pwiv;
	stwuct cx23885_dev *dev = powt->dev;

	switch (dev->boawd) {
	case CX23885_BOAWD_HAUPPAUGE_HVW1275:
		switch (p->moduwation) {
		case VSB_8:
			cx23885_gpio_cweaw(dev, GPIO_5);
			bweak;
		case QAM_64:
		case QAM_256:
		defauwt:
			cx23885_gpio_set(dev, GPIO_5);
			bweak;
		}
		bweak;
	case CX23885_BOAWD_MYGICA_X8506:
	case CX23885_BOAWD_MYGICA_X8507:
	case CX23885_BOAWD_MAGICPWO_PWOHDTVE2:
		/* Sewect Digitaw TV */
		cx23885_gpio_set(dev, GPIO_0);
		bweak;
	}

	/* Caww the weaw set_fwontend */
	if (powt->set_fwontend)
		wetuwn powt->set_fwontend(fe);

	wetuwn 0;
}

static void cx23885_set_fwontend_hook(stwuct cx23885_tspowt *powt,
				     stwuct dvb_fwontend *fe)
{
	powt->set_fwontend = fe->ops.set_fwontend;
	fe->ops.set_fwontend = cx23885_dvb_set_fwontend;
}

static stwuct wgs8gxx_config magicpwo_pwohdtve2_wgs8g75_config = {
	.pwod = WGS8GXX_PWOD_WGS8G75,
	.demod_addwess = 0x19,
	.sewiaw_ts = 0,
	.ts_cwk_pow = 1,
	.ts_cwk_gated = 1,
	.if_cwk_fweq = 30400, /* 30.4 MHz */
	.if_fweq = 6500, /* 6.50 MHz */
	.if_neg_centew = 1,
	.ext_adc = 0,
	.adc_signed = 1,
	.adc_vpp = 2, /* 1.6 Vpp */
	.if_neg_edge = 1,
};

static stwuct xc5000_config magicpwo_pwohdtve2_xc5000_config = {
	.i2c_addwess = 0x61,
	.if_khz = 6500,
};

static stwuct atbm8830_config mygica_x8558pwo_atbm8830_cfg1 = {
	.pwod = ATBM8830_PWOD_8830,
	.demod_addwess = 0x44,
	.sewiaw_ts = 0,
	.ts_sampwing_edge = 1,
	.ts_cwk_gated = 0,
	.osc_cwk_fweq = 30400, /* in kHz */
	.if_fweq = 0, /* zewo IF */
	.zif_swap_iq = 1,
	.agc_min = 0x2E,
	.agc_max = 0xFF,
	.agc_howd_woop = 0,
};

static stwuct max2165_config mygic_x8558pwo_max2165_cfg1 = {
	.i2c_addwess = 0x60,
	.osc_cwk = 20
};

static stwuct atbm8830_config mygica_x8558pwo_atbm8830_cfg2 = {
	.pwod = ATBM8830_PWOD_8830,
	.demod_addwess = 0x44,
	.sewiaw_ts = 1,
	.ts_sampwing_edge = 1,
	.ts_cwk_gated = 0,
	.osc_cwk_fweq = 30400, /* in kHz */
	.if_fweq = 0, /* zewo IF */
	.zif_swap_iq = 1,
	.agc_min = 0x2E,
	.agc_max = 0xFF,
	.agc_howd_woop = 0,
};

static stwuct max2165_config mygic_x8558pwo_max2165_cfg2 = {
	.i2c_addwess = 0x60,
	.osc_cwk = 20
};
static stwuct stv0367_config netup_stv0367_config[] = {
	{
		.demod_addwess = 0x1c,
		.xtaw = 27000000,
		.if_khz = 4500,
		.if_iq_mode = 0,
		.ts_mode = 1,
		.cwk_pow = 0,
	}, {
		.demod_addwess = 0x1d,
		.xtaw = 27000000,
		.if_khz = 4500,
		.if_iq_mode = 0,
		.ts_mode = 1,
		.cwk_pow = 0,
	},
};

static stwuct xc5000_config netup_xc5000_config[] = {
	{
		.i2c_addwess = 0x61,
		.if_khz = 4500,
	}, {
		.i2c_addwess = 0x64,
		.if_khz = 4500,
	},
};

static stwuct dwxk_config tewwatec_dwxk_config[] = {
	{
		.adw = 0x29,
		.no_i2c_bwidge = 1,
	}, {
		.adw = 0x2a,
		.no_i2c_bwidge = 1,
	},
};

static stwuct mt2063_config tewwatec_mt2063_config[] = {
	{
		.tunew_addwess = 0x60,
	}, {
		.tunew_addwess = 0x67,
	},
};

static const stwuct tda10071_pwatfowm_data hauppauge_tda10071_pdata = {
	.cwk = 40444000, /* 40.444 MHz */
	.i2c_ww_max = 64,
	.ts_mode = TDA10071_TS_SEWIAW,
	.pww_muwtipwiew = 20,
	.tunew_i2c_addw = 0x54,
};

static const stwuct m88ds3103_config dvbsky_t9580_m88ds3103_config = {
	.i2c_addw = 0x68,
	.cwock = 27000000,
	.i2c_ww_max = 33,
	.cwock_out = 0,
	.ts_mode = M88DS3103_TS_PAWAWWEW,
	.ts_cwk = 16000,
	.ts_cwk_pow = 1,
	.wnb_en_pow = 1,
	.wnb_hv_pow = 0,
	.agc = 0x99,
};

static const stwuct m88ds3103_config dvbsky_s950c_m88ds3103_config = {
	.i2c_addw = 0x68,
	.cwock = 27000000,
	.i2c_ww_max = 33,
	.cwock_out = 0,
	.ts_mode = M88DS3103_TS_CI,
	.ts_cwk = 10000,
	.ts_cwk_pow = 1,
	.wnb_en_pow = 1,
	.wnb_hv_pow = 0,
	.agc = 0x99,
};

static const stwuct m88ds3103_config hauppauge_hvw5525_m88ds3103_config = {
	.i2c_addw = 0x69,
	.cwock = 27000000,
	.i2c_ww_max = 33,
	.ts_mode = M88DS3103_TS_PAWAWWEW,
	.ts_cwk = 16000,
	.ts_cwk_pow = 1,
	.agc = 0x99,
};

static stwuct wgdt3306a_config hauppauge_hvw1265k4_config = {
	.i2c_addw               = 0x59,
	.qam_if_khz             = 4000,
	.vsb_if_khz             = 3250,
	.deny_i2c_wptw          = 1, /* Disabwed */
	.spectwaw_invewsion     = 0, /* Disabwed */
	.mpeg_mode              = WGDT3306A_MPEG_SEWIAW,
	.tpcwk_edge             = WGDT3306A_TPCWK_WISING_EDGE,
	.tpvawid_powawity       = WGDT3306A_TP_VAWID_HIGH,
	.xtawMHz                = 25, /* 24 ow 25 */
};

static int netup_awtewa_fpga_ww(void *device, int fwag, int data, int wead)
{
	stwuct cx23885_dev *dev = (stwuct cx23885_dev *)device;
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);
	uint32_t mem = 0;

	mem = cx_wead(MC417_WWD);
	if (wead)
		cx_set(MC417_OEN, AWT_DATA);
	ewse {
		cx_cweaw(MC417_OEN, AWT_DATA);/* D0-D7 out */
		mem &= ~AWT_DATA;
		mem |= (data & AWT_DATA);
	}

	if (fwag)
		mem |= AWT_AD_WG;
	ewse
		mem &= ~AWT_AD_WG;

	mem &= ~AWT_CS;
	if (wead)
		mem = (mem & ~AWT_WD) | AWT_WW;
	ewse
		mem = (mem & ~AWT_WW) | AWT_WD;

	cx_wwite(MC417_WWD, mem);  /* stawt WW cycwe */

	fow (;;) {
		mem = cx_wead(MC417_WWD);
		if ((mem & AWT_WDY) == 0)
			bweak;
		if (time_aftew(jiffies, timeout))
			bweak;
		udeway(1);
	}

	cx_set(MC417_WWD, AWT_WD | AWT_WW | AWT_CS);
	if (wead)
		wetuwn mem & AWT_DATA;

	wetuwn 0;
};

static int dib7070_tunew_weset(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib7000p_ops *dib7000p_ops = fe->sec_pwiv;

	wetuwn dib7000p_ops->set_gpio(fe, 8, 0, !onoff);
}

static int dib7070_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	wetuwn 0;
}

static stwuct dib0070_config dib7070p_dib0070_config = {
	.i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
	.weset = dib7070_tunew_weset,
	.sweep = dib7070_tunew_sweep,
	.cwock_khz = 12000,
	.fweq_offset_khz_vhf = 550,
	/* .fwip_chip = 1, */
};

/* DIB7070 genewic */
static stwuct dibx000_agc_config dib7070_agc_config = {
	.band_caps = BAND_UHF | BAND_VHF | BAND_WBAND | BAND_SBAND,

	/*
	 * P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=5,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
	 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0
	 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) |
		 (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),
	.inv_gain = 600,
	.time_stabiwiz = 10,
	.awpha_wevew = 0,
	.thwock = 118,
	.wbd_inv = 0,
	.wbd_wef = 3530,
	.wbd_sew = 1,
	.wbd_awpha = 5,
	.agc1_max = 65535,
	.agc1_min = 0,
	.agc2_max = 65535,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 40,
	.agc1_pt3 = 183,
	.agc1_swope1 = 206,
	.agc1_swope2 = 255,
	.agc2_pt1 = 72,
	.agc2_pt2 = 152,
	.agc2_swope1 = 88,
	.agc2_swope2 = 90,
	.awpha_mant = 17,
	.awpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.pewfowm_agc_softspwit = 0,
};

static stwuct dibx000_bandwidth_config dib7070_bw_config_12_mhz = {
	.intewnaw = 60000,
	.sampwing = 15000,
	.pww_pwediv = 1,
	.pww_watio = 20,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,
	/* wefsew, sew, fweq_15k */
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = (0 << 25) | 0,
	.timf = 20452225,
	.xtaw_hz = 12000000,
};

static stwuct dib7000p_config dib7070p_dib7000p_config = {
	/* .output_mode = OUTMODE_MPEG2_FIFO, */
	.output_mode = OUTMODE_MPEG2_SEWIAW,
	/* .output_mode = OUTMODE_MPEG2_PAW_GATED_CWK, */
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tunew_is_baseband = 1,
	.spuw_pwotect = 1,

	.gpio_diw = 0xfcef, /* DIB7000P_GPIO_DEFAUWT_DIWECTIONS, */
	.gpio_vaw = 0x0110, /* DIB7000P_GPIO_DEFAUWT_VAWUES, */
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.hostbus_divewsity = 1,
};

static int dvb_wegistew_ci_mac(stwuct cx23885_tspowt *powt)
{
	stwuct cx23885_dev *dev = powt->dev;
	stwuct i2c_cwient *cwient_ci = NUWW;
	stwuct vb2_dvb_fwontend *fe0;

	fe0 = vb2_dvb_get_fwontend(&powt->fwontends, 1);
	if (!fe0)
		wetuwn -EINVAW;

	switch (dev->boawd) {
	case CX23885_BOAWD_NETUP_DUAW_DVBS2_CI: {
		static stwuct netup_cawd_info cinfo;

		netup_get_cawd_info(&dev->i2c_bus[0].i2c_adap, &cinfo);
		memcpy(powt->fwontends.adaptew.pwoposed_mac,
				cinfo.powt[powt->nw - 1].mac, 6);
		pw_info("NetUP Duaw DVB-S2 CI cawd powt%d MAC=%pM\n",
			powt->nw, powt->fwontends.adaptew.pwoposed_mac);

		netup_ci_init(powt);
		wetuwn 0;
		}
	case CX23885_BOAWD_NETUP_DUAW_DVB_T_C_CI_WF: {
		stwuct awtewa_ci_config netup_ci_cfg = {
			.dev = dev,/* magic numbew to identify*/
			.adaptew = &powt->fwontends.adaptew,/* fow CI */
			.demux = &fe0->dvb.demux,/* fow hw pid fiwtew */
			.fpga_ww = netup_awtewa_fpga_ww,
		};

		awtewa_ci_init(&netup_ci_cfg, powt->nw);
		wetuwn 0;
		}
	case CX23885_BOAWD_TEVII_S470: {
		u8 eepwom[256]; /* 24C02 i2c eepwom */

		if (powt->nw != 1)
			wetuwn 0;

		/* Wead entiwe EEPWOM */
		dev->i2c_bus[0].i2c_cwient.addw = 0xa0 >> 1;
		tveepwom_wead(&dev->i2c_bus[0].i2c_cwient, eepwom, sizeof(eepwom));
		pw_info("TeVii S470 MAC= %pM\n", eepwom + 0xa0);
		memcpy(powt->fwontends.adaptew.pwoposed_mac, eepwom + 0xa0, 6);
		wetuwn 0;
		}
	case CX23885_BOAWD_DVBSKY_T9580:
	case CX23885_BOAWD_DVBSKY_S950:
	case CX23885_BOAWD_DVBSKY_S952:
	case CX23885_BOAWD_DVBSKY_T982: {
		u8 eepwom[256]; /* 24C02 i2c eepwom */

		if (powt->nw > 2)
			wetuwn 0;

		/* Wead entiwe EEPWOM */
		dev->i2c_bus[0].i2c_cwient.addw = 0xa0 >> 1;
		tveepwom_wead(&dev->i2c_bus[0].i2c_cwient, eepwom,
				sizeof(eepwom));
		pw_info("%s powt %d MAC addwess: %pM\n",
			cx23885_boawds[dev->boawd].name, powt->nw,
			eepwom + 0xc0 + (powt->nw-1) * 8);
		memcpy(powt->fwontends.adaptew.pwoposed_mac, eepwom + 0xc0 +
			(powt->nw-1) * 8, 6);
		wetuwn 0;
		}
	case CX23885_BOAWD_DVBSKY_S950C:
	case CX23885_BOAWD_DVBSKY_T980C:
	case CX23885_BOAWD_TT_CT2_4500_CI: {
		u8 eepwom[256]; /* 24C02 i2c eepwom */
		stwuct sp2_config sp2_config;
		stwuct i2c_boawd_info info;
		stwuct cx23885_i2c *i2c_bus = &dev->i2c_bus[0];

		/* attach CI */
		memset(&sp2_config, 0, sizeof(sp2_config));
		sp2_config.dvb_adap = &powt->fwontends.adaptew;
		sp2_config.pwiv = powt;
		sp2_config.ci_contwow = cx23885_sp2_ci_ctww;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "sp2", I2C_NAME_SIZE);
		info.addw = 0x40;
		info.pwatfowm_data = &sp2_config;
		wequest_moduwe(info.type);
		cwient_ci = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_ci))
			wetuwn -ENODEV;
		if (!twy_moduwe_get(cwient_ci->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_ci);
			wetuwn -ENODEV;
		}
		powt->i2c_cwient_ci = cwient_ci;

		if (powt->nw != 1)
			wetuwn 0;

		/* Wead entiwe EEPWOM */
		dev->i2c_bus[0].i2c_cwient.addw = 0xa0 >> 1;
		tveepwom_wead(&dev->i2c_bus[0].i2c_cwient, eepwom,
				sizeof(eepwom));
		pw_info("%s MAC addwess: %pM\n",
			cx23885_boawds[dev->boawd].name, eepwom + 0xc0);
		memcpy(powt->fwontends.adaptew.pwoposed_mac, eepwom + 0xc0, 6);
		wetuwn 0;
		}
	}
	wetuwn 0;
}

static int dvb_wegistew(stwuct cx23885_tspowt *powt)
{
	stwuct dib7000p_ops dib7000p_ops;
	stwuct cx23885_dev *dev = powt->dev;
	stwuct cx23885_i2c *i2c_bus = NUWW, *i2c_bus2 = NUWW;
	stwuct vb2_dvb_fwontend *fe0, *fe1 = NUWW;
	stwuct si2168_config si2168_config;
	stwuct si2165_pwatfowm_data si2165_pdata;
	stwuct si2157_config si2157_config;
	stwuct ts2020_config ts2020_config;
	stwuct m88ds3103_pwatfowm_data m88ds3103_pdata;
	stwuct m88ws6000t_config m88ws6000t_config = {};
	stwuct a8293_pwatfowm_data a8293_pdata = {};
	stwuct i2c_boawd_info info;
	stwuct i2c_adaptew *adaptew;
	stwuct i2c_cwient *cwient_demod = NUWW, *cwient_tunew = NUWW;
	stwuct i2c_cwient *cwient_sec = NUWW;
	int (*p_set_vowtage)(stwuct dvb_fwontend *fe,
			     enum fe_sec_vowtage vowtage) = NUWW;
	int mfe_shawed = 0; /* bus not shawed by defauwt */
	int wet;

	/* Get the fiwst fwontend */
	fe0 = vb2_dvb_get_fwontend(&powt->fwontends, 1);
	if (!fe0)
		wetuwn -EINVAW;

	/* init stwuct vb2_dvb */
	fe0->dvb.name = dev->name;

	/* muwti-fwontend gate contwow is undefined ow defauwts to fe0 */
	powt->fwontends.gate = 0;

	/* Sets the gate contwow cawwback to be used by i2c command cawws */
	powt->gate_ctww = cx23885_dvb_gate_ctww;

	/* init fwontend */
	switch (dev->boawd) {
	case CX23885_BOAWD_HAUPPAUGE_HVW1250:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
						&hauppauge_genewic_config,
						&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(mt2131_attach, fe0->dvb.fwontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_genewic_tunewconfig, 0);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1270:
	case CX23885_BOAWD_HAUPPAUGE_HVW1275:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(wgdt3305_attach,
					       &hauppauge_wgdt3305_config,
					       &i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(tda18271_attach, fe0->dvb.fwontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_hvw127x_config);
		if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_HVW1275)
			cx23885_set_fwontend_hook(powt, fe0->dvb.fwontend);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1255:
	case CX23885_BOAWD_HAUPPAUGE_HVW1255_22111:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(s5h1411_attach,
					       &hcw_s5h1411_config,
					       &i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;

		dvb_attach(tda18271_attach, fe0->dvb.fwontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_tda18271_config);

		tda18271_attach(&dev->ts1.anawog_fe,
			0x60, &dev->i2c_bus[1].i2c_adap,
			&hauppauge_tda18271_config);

		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1800:
		i2c_bus = &dev->i2c_bus[0];
		switch (awt_tunew) {
		case 1:
			fe0->dvb.fwontend =
				dvb_attach(s5h1409_attach,
					   &hauppauge_ezqam_config,
					   &i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			dvb_attach(tda829x_attach, fe0->dvb.fwontend,
				   &dev->i2c_bus[1].i2c_adap, 0x42,
				   &tda829x_no_pwobe);
			dvb_attach(tda18271_attach, fe0->dvb.fwontend,
				   0x60, &dev->i2c_bus[1].i2c_adap,
				   &hauppauge_tda18271_config);
			bweak;
		case 0:
		defauwt:
			fe0->dvb.fwontend =
				dvb_attach(s5h1409_attach,
					   &hauppauge_genewic_config,
					   &i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;
			dvb_attach(mt2131_attach, fe0->dvb.fwontend,
				   &i2c_bus->i2c_adap,
				   &hauppauge_genewic_tunewconfig, 0);
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1800wp:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvw1800wp_config,
						&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(mt2131_attach, fe0->dvb.fwontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_genewic_tunewconfig, 0);
		bweak;
	case CX23885_BOAWD_DVICO_FUSIONHDTV_5_EXP:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(wgdt330x_attach,
					       &fusionhdtv_5_expwess,
					       0x0e,
					       &i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(simpwe_tunew_attach, fe0->dvb.fwontend,
			   &i2c_bus->i2c_adap, 0x61,
			   TUNEW_WG_TDVS_H06XF);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1500Q:
		i2c_bus = &dev->i2c_bus[1];
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvw1500q_config,
						&dev->i2c_bus[0].i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(xc5000_attach, fe0->dvb.fwontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_hvw1500q_tunewconfig);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1500:
		i2c_bus = &dev->i2c_bus[1];
		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvw1500_config,
						&dev->i2c_bus[0].i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap  = &i2c_bus->i2c_adap,
				.i2c_addw  = 0x61,
			};
			static stwuct xc2028_ctww ctw = {
				.fname       = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen     = 64,
				.demod       = XC3028_FE_OWEN538,
			};

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.fwontend, &cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctw);
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1200:
	case CX23885_BOAWD_HAUPPAUGE_HVW1700:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(tda10048_attach,
			&hauppauge_hvw1200_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(tda829x_attach, fe0->dvb.fwontend,
			   &dev->i2c_bus[1].i2c_adap, 0x42,
			   &tda829x_no_pwobe);
		dvb_attach(tda18271_attach, fe0->dvb.fwontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_hvw1200_tunew_config);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1210:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(tda10048_attach,
			&hauppauge_hvw1210_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			dvb_attach(tda18271_attach, fe0->dvb.fwontend,
				0x60, &dev->i2c_bus[1].i2c_adap,
				&hauppauge_hvw1210_tunew_config);
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1400:
		i2c_bus = &dev->i2c_bus[0];

		if (!dvb_attach(dib7000p_attach, &dib7000p_ops))
			wetuwn -ENODEV;

		fe0->dvb.fwontend = dib7000p_ops.init(&i2c_bus->i2c_adap,
			0x12, &hauppauge_hvw1400_dib7000_config);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct dvb_fwontend *fe;
			stwuct xc2028_config cfg = {
				.i2c_adap  = &dev->i2c_bus[1].i2c_adap,
				.i2c_addw  = 0x64,
			};
			static stwuct xc2028_ctww ctw = {
				.fname   = XC3028W_DEFAUWT_FIWMWAWE,
				.max_wen = 64,
				.demod   = XC3028_FE_DIBCOM52,
				/* This is twue fow aww demods with
					v36 fiwmwawe? */
				.type    = XC2028_D2633,
			};

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.fwontend, &cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctw);
		}
		bweak;
	case CX23885_BOAWD_DVICO_FUSIONHDTV_7_DUAW_EXP:
		i2c_bus = &dev->i2c_bus[powt->nw - 1];

		fe0->dvb.fwontend = dvb_attach(s5h1409_attach,
						&dvico_s5h1409_config,
						&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			fe0->dvb.fwontend = dvb_attach(s5h1411_attach,
							&dvico_s5h1411_config,
							&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW)
			dvb_attach(xc5000_attach, fe0->dvb.fwontend,
				   &i2c_bus->i2c_adap,
				   &dvico_xc5000_tunewconfig);
		bweak;
	case CX23885_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW_EXP: {
		i2c_bus = &dev->i2c_bus[powt->nw - 1];

		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct dvb_fwontend      *fe;
			stwuct xc2028_config	  cfg = {
				.i2c_adap  = &i2c_bus->i2c_adap,
				.i2c_addw  = 0x61,
			};
			static stwuct xc2028_ctww ctw = {
				.fname       = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen     = 64,
				.demod       = XC3028_FE_ZAWWINK456,
			};

			fe = dvb_attach(xc2028_attach, fe0->dvb.fwontend,
					&cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctw);
		}
		bweak;
	}
	case CX23885_BOAWD_DVICO_FUSIONHDTV_DVB_T_DUAW_EXP2: {
		i2c_bus = &dev->i2c_bus[powt->nw - 1];
		/* cxusb_ctww_msg(adap->dev, CMD_DIGITAW, NUWW, 0, NUWW, 0); */
		/* cxusb_bwuebiwd_gpio_puwse(adap->dev, 0x02, 1); */

		if (!dvb_attach(dib7000p_attach, &dib7000p_ops))
			wetuwn -ENODEV;

		if (dib7000p_ops.i2c_enumewation(&i2c_bus->i2c_adap, 1, 0x12, &dib7070p_dib7000p_config) < 0) {
			pw_wawn("Unabwe to enumewate dib7000p\n");
			wetuwn -ENODEV;
		}
		fe0->dvb.fwontend = dib7000p_ops.init(&i2c_bus->i2c_adap, 0x80, &dib7070p_dib7000p_config);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct i2c_adaptew *tun_i2c;

			fe0->dvb.fwontend->sec_pwiv = kmemdup(&dib7000p_ops, sizeof(dib7000p_ops), GFP_KEWNEW);
			if (!fe0->dvb.fwontend->sec_pwiv)
				wetuwn -ENOMEM;
			tun_i2c = dib7000p_ops.get_i2c_mastew(fe0->dvb.fwontend, DIBX000_I2C_INTEWFACE_TUNEW, 1);
			if (!dvb_attach(dib0070_attach, fe0->dvb.fwontend, tun_i2c, &dib7070p_dib0070_config))
				wetuwn -ENODEV;
		}
		bweak;
	}
	case CX23885_BOAWD_WEADTEK_WINFAST_PXDVW3200_H:
	case CX23885_BOAWD_COMPWO_VIDEOMATE_E650F:
	case CX23885_BOAWD_COMPWO_VIDEOMATE_E800:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
			&dvico_fusionhdtv_xc3028,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct dvb_fwontend      *fe;
			stwuct xc2028_config	  cfg = {
				.i2c_adap  = &dev->i2c_bus[1].i2c_adap,
				.i2c_addw  = 0x61,
			};
			static stwuct xc2028_ctww ctw = {
				.fname       = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen     = 64,
				.demod       = XC3028_FE_ZAWWINK456,
			};

			fe = dvb_attach(xc2028_attach, fe0->dvb.fwontend,
				&cfg);
			if (fe != NUWW && fe->ops.tunew_ops.set_config != NUWW)
				fe->ops.tunew_ops.set_config(fe, &ctw);
		}
		bweak;
	case CX23885_BOAWD_WEADTEK_WINFAST_PXDVW3200_H_XC4000:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.fwontend = dvb_attach(zw10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			stwuct dvb_fwontend	*fe;
			stwuct xc4000_config	cfg = {
				.i2c_addwess	  = 0x61,
				.defauwt_pm	  = 0,
				.dvb_ampwitude	  = 134,
				.set_smoothedcvbs = 1,
				.if_khz		  = 4560
			};

			fe = dvb_attach(xc4000_attach, fe0->dvb.fwontend,
					&dev->i2c_bus[1].i2c_adap, &cfg);
			if (!fe) {
				pw_eww("%s/2: xc4000 attach faiwed\n",
				       dev->name);
				goto fwontend_detach;
			}
		}
		bweak;
	case CX23885_BOAWD_TBS_6920:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
					&tbs_cx24116_config,
					&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW)
			fe0->dvb.fwontend->ops.set_vowtage = f300_set_vowtage;

		bweak;
	case CX23885_BOAWD_TBS_6980:
	case CX23885_BOAWD_TBS_6981:
		i2c_bus = &dev->i2c_bus[1];

		switch (powt->nw) {
		/* POWT B */
		case 1:
			fe0->dvb.fwontend = dvb_attach(cx24117_attach,
					&tbs_cx24117_config,
					&i2c_bus->i2c_adap);
			bweak;
		/* POWT C */
		case 2:
			fe0->dvb.fwontend = dvb_attach(cx24117_attach,
					&tbs_cx24117_config,
					&i2c_bus->i2c_adap);
			bweak;
		}
		bweak;
	case CX23885_BOAWD_TEVII_S470:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.fwontend = dvb_attach(ds3000_attach,
					&tevii_ds3000_config,
					&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend != NUWW) {
			dvb_attach(ts2020_attach, fe0->dvb.fwontend,
				&tevii_ts2020_config, &i2c_bus->i2c_adap);
			fe0->dvb.fwontend->ops.set_vowtage = f300_set_vowtage;
		}

		bweak;
	case CX23885_BOAWD_DVBWOWWD_2005:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.fwontend = dvb_attach(cx24116_attach,
			&dvbwowwd_cx24116_config,
			&i2c_bus->i2c_adap);
		bweak;
	case CX23885_BOAWD_NETUP_DUAW_DVBS2_CI:
		i2c_bus = &dev->i2c_bus[0];
		switch (powt->nw) {
		/* powt B */
		case 1:
			fe0->dvb.fwontend = dvb_attach(stv0900_attach,
							&netup_stv0900_config,
							&i2c_bus->i2c_adap, 0);
			if (fe0->dvb.fwontend != NUWW) {
				if (dvb_attach(stv6110_attach,
						fe0->dvb.fwontend,
						&netup_stv6110_tunewconfig_a,
						&i2c_bus->i2c_adap)) {
					if (!dvb_attach(wnbh24_attach,
							fe0->dvb.fwontend,
							&i2c_bus->i2c_adap,
							WNBH24_PCW | WNBH24_TTX,
							WNBH24_TEN, 0x09))
						pw_eww("No WNBH24 found!\n");

				}
			}
			bweak;
		/* powt C */
		case 2:
			fe0->dvb.fwontend = dvb_attach(stv0900_attach,
							&netup_stv0900_config,
							&i2c_bus->i2c_adap, 1);
			if (fe0->dvb.fwontend != NUWW) {
				if (dvb_attach(stv6110_attach,
						fe0->dvb.fwontend,
						&netup_stv6110_tunewconfig_b,
						&i2c_bus->i2c_adap)) {
					if (!dvb_attach(wnbh24_attach,
							fe0->dvb.fwontend,
							&i2c_bus->i2c_adap,
							WNBH24_PCW | WNBH24_TTX,
							WNBH24_TEN, 0x0a))
						pw_eww("No WNBH24 found!\n");

				}
			}
			bweak;
		}
		bweak;
	case CX23885_BOAWD_MYGICA_X8506:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.fwontend = dvb_attach(wgs8gxx_attach,
			&mygica_x8506_wgs8gw5_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(xc5000_attach, fe0->dvb.fwontend,
			   &i2c_bus2->i2c_adap, &mygica_x8506_xc5000_config);
		cx23885_set_fwontend_hook(powt, fe0->dvb.fwontend);
		bweak;
	case CX23885_BOAWD_MYGICA_X8507:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.fwontend = dvb_attach(mb86a20s_attach,
			&mygica_x8507_mb86a20s_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;

		dvb_attach(xc5000_attach, fe0->dvb.fwontend,
			   &i2c_bus2->i2c_adap,
			   &mygica_x8507_xc5000_config);
		cx23885_set_fwontend_hook(powt, fe0->dvb.fwontend);
		bweak;
	case CX23885_BOAWD_MAGICPWO_PWOHDTVE2:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.fwontend = dvb_attach(wgs8gxx_attach,
			&magicpwo_pwohdtve2_wgs8g75_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(xc5000_attach, fe0->dvb.fwontend,
			   &i2c_bus2->i2c_adap,
			   &magicpwo_pwohdtve2_xc5000_config);
		cx23885_set_fwontend_hook(powt, fe0->dvb.fwontend);
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1850:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(s5h1411_attach,
			&hcw_s5h1411_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(tda18271_attach, fe0->dvb.fwontend,
			   0x60, &dev->i2c_bus[0].i2c_adap,
			   &hauppauge_tda18271_config);

		tda18271_attach(&dev->ts1.anawog_fe,
			0x60, &dev->i2c_bus[1].i2c_adap,
			&hauppauge_tda18271_config);

		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1290:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.fwontend = dvb_attach(s5h1411_attach,
			&hcw_s5h1411_config,
			&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(tda18271_attach, fe0->dvb.fwontend,
			   0x60, &dev->i2c_bus[0].i2c_adap,
			   &hauppauge_tda18271_config);
		bweak;
	case CX23885_BOAWD_MYGICA_X8558PWO:
		switch (powt->nw) {
		/* powt B */
		case 1:
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.fwontend = dvb_attach(atbm8830_attach,
				&mygica_x8558pwo_atbm8830_cfg1,
				&i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;
			dvb_attach(max2165_attach, fe0->dvb.fwontend,
				   &i2c_bus->i2c_adap,
				   &mygic_x8558pwo_max2165_cfg1);
			bweak;
		/* powt C */
		case 2:
			i2c_bus = &dev->i2c_bus[1];
			fe0->dvb.fwontend = dvb_attach(atbm8830_attach,
				&mygica_x8558pwo_atbm8830_cfg2,
				&i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;
			dvb_attach(max2165_attach, fe0->dvb.fwontend,
				   &i2c_bus->i2c_adap,
				   &mygic_x8558pwo_max2165_cfg2);
		}
		bweak;
	case CX23885_BOAWD_NETUP_DUAW_DVB_T_C_CI_WF:
		if (powt->nw > 2)
			wetuwn 0;

		i2c_bus = &dev->i2c_bus[0];
		mfe_shawed = 1;/* MFE */
		powt->fwontends.gate = 0;/* not cweaw fow me yet */
		/* powts B, C */
		/* MFE fwontend 1 DVB-T */
		fe0->dvb.fwontend = dvb_attach(stv0367tew_attach,
					&netup_stv0367_config[powt->nw - 1],
					&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		if (NUWW == dvb_attach(xc5000_attach, fe0->dvb.fwontend,
					&i2c_bus->i2c_adap,
					&netup_xc5000_config[powt->nw - 1]))
			goto fwontend_detach;
		/* woad xc5000 fiwmwawe */
		fe0->dvb.fwontend->ops.tunew_ops.init(fe0->dvb.fwontend);

		/* MFE fwontend 2 */
		fe1 = vb2_dvb_get_fwontend(&powt->fwontends, 2);
		if (fe1 == NUWW)
			goto fwontend_detach;
		/* DVB-C init */
		fe1->dvb.fwontend = dvb_attach(stv0367cab_attach,
					&netup_stv0367_config[powt->nw - 1],
					&i2c_bus->i2c_adap);
		if (fe1->dvb.fwontend == NUWW)
			bweak;

		fe1->dvb.fwontend->id = 1;
		if (NUWW == dvb_attach(xc5000_attach,
				       fe1->dvb.fwontend,
				       &i2c_bus->i2c_adap,
				       &netup_xc5000_config[powt->nw - 1]))
			goto fwontend_detach;
		bweak;
	case CX23885_BOAWD_TEWWATEC_CINEWGY_T_PCIE_DUAW:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		switch (powt->nw) {
		/* powt b */
		case 1:
			fe0->dvb.fwontend = dvb_attach(dwxk_attach,
					&tewwatec_dwxk_config[0],
					&i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;
			if (!dvb_attach(mt2063_attach,
					fe0->dvb.fwontend,
					&tewwatec_mt2063_config[0],
					&i2c_bus2->i2c_adap))
				goto fwontend_detach;
			bweak;
		/* powt c */
		case 2:
			fe0->dvb.fwontend = dvb_attach(dwxk_attach,
					&tewwatec_dwxk_config[1],
					&i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;
			if (!dvb_attach(mt2063_attach,
					fe0->dvb.fwontend,
					&tewwatec_mt2063_config[1],
					&i2c_bus2->i2c_adap))
				goto fwontend_detach;
			bweak;
		}
		bweak;
	case CX23885_BOAWD_TEVII_S471:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.fwontend = dvb_attach(ds3000_attach,
					&tevii_ds3000_config,
					&i2c_bus->i2c_adap);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		dvb_attach(ts2020_attach, fe0->dvb.fwontend,
			   &tevii_ts2020_config, &i2c_bus->i2c_adap);
		bweak;
	case CX23885_BOAWD_PWOF_8000:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.fwontend = dvb_attach(stv090x_attach,
						&pwof_8000_stv090x_config,
						&i2c_bus->i2c_adap,
						STV090x_DEMODUWATOW_0);
		if (fe0->dvb.fwontend == NUWW)
			bweak;
		if (!dvb_attach(stb6100_attach,
				fe0->dvb.fwontend,
				&pwof_8000_stb6100_config,
				&i2c_bus->i2c_adap))
			goto fwontend_detach;

		fe0->dvb.fwontend->ops.set_vowtage = p8000_set_vowtage;
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW4400: {
		stwuct tda10071_pwatfowm_data tda10071_pdata = hauppauge_tda10071_pdata;
		stwuct a8293_pwatfowm_data a8293_pdata = {};

		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		switch (powt->nw) {
		/* powt b */
		case 1:
			/* attach demod + tunew combo */
			memset(&info, 0, sizeof(info));
			stwscpy(info.type, "tda10071_cx24118", I2C_NAME_SIZE);
			info.addw = 0x05;
			info.pwatfowm_data = &tda10071_pdata;
			wequest_moduwe("tda10071");
			cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			fe0->dvb.fwontend = tda10071_pdata.get_dvb_fwontend(cwient_demod);
			powt->i2c_cwient_demod = cwient_demod;

			/* attach SEC */
			a8293_pdata.dvb_fwontend = fe0->dvb.fwontend;
			memset(&info, 0, sizeof(info));
			stwscpy(info.type, "a8293", I2C_NAME_SIZE);
			info.addw = 0x0b;
			info.pwatfowm_data = &a8293_pdata;
			wequest_moduwe("a8293");
			cwient_sec = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_sec))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_sec->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_sec);
				goto fwontend_detach;
			}
			powt->i2c_cwient_sec = cwient_sec;
			bweak;
		/* powt c */
		case 2:
			/* attach fwontend */
			memset(&si2165_pdata, 0, sizeof(si2165_pdata));
			si2165_pdata.fe = &fe0->dvb.fwontend;
			si2165_pdata.chip_mode = SI2165_MODE_PWW_XTAW;
			si2165_pdata.wef_fweq_hz = 16000000;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2165", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &si2165_pdata;
			wequest_moduwe(info.type);
			cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			if (fe0->dvb.fwontend == NUWW)
				bweak;
			fe0->dvb.fwontend->ops.i2c_gate_ctww = NUWW;
			if (!dvb_attach(tda18271_attach,
					fe0->dvb.fwontend,
					0x60, &i2c_bus2->i2c_adap,
				  &hauppauge_hvw4400_tunew_config))
				goto fwontend_detach;
			bweak;
		}
		bweak;
	}
	case CX23885_BOAWD_HAUPPAUGE_STAWBUWST: {
		stwuct tda10071_pwatfowm_data tda10071_pdata = hauppauge_tda10071_pdata;
		stwuct a8293_pwatfowm_data a8293_pdata = {};

		i2c_bus = &dev->i2c_bus[0];

		/* attach demod + tunew combo */
		memset(&info, 0, sizeof(info));
		stwscpy(info.type, "tda10071_cx24118", I2C_NAME_SIZE);
		info.addw = 0x05;
		info.pwatfowm_data = &tda10071_pdata;
		wequest_moduwe("tda10071");
		cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_demod))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_demod);
			goto fwontend_detach;
		}
		fe0->dvb.fwontend = tda10071_pdata.get_dvb_fwontend(cwient_demod);
		powt->i2c_cwient_demod = cwient_demod;

		/* attach SEC */
		a8293_pdata.dvb_fwontend = fe0->dvb.fwontend;
		memset(&info, 0, sizeof(info));
		stwscpy(info.type, "a8293", I2C_NAME_SIZE);
		info.addw = 0x0b;
		info.pwatfowm_data = &a8293_pdata;
		wequest_moduwe("a8293");
		cwient_sec = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_sec))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_sec->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_sec);
			goto fwontend_detach;
		}
		powt->i2c_cwient_sec = cwient_sec;
		bweak;
	}
	case CX23885_BOAWD_DVBSKY_T9580:
	case CX23885_BOAWD_DVBSKY_S950:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		switch (powt->nw) {
		/* powt b - satewwite */
		case 1:
			/* attach fwontend */
			fe0->dvb.fwontend = dvb_attach(m88ds3103_attach,
					&dvbsky_t9580_m88ds3103_config,
					&i2c_bus2->i2c_adap, &adaptew);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			/* attach tunew */
			memset(&ts2020_config, 0, sizeof(ts2020_config));
			ts2020_config.fe = fe0->dvb.fwontend;
			ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "ts2020", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &ts2020_config;
			wequest_moduwe(info.type);
			cwient_tunew = i2c_new_cwient_device(adaptew, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				goto fwontend_detach;
			}

			/* dewegate signaw stwength measuwement to tunew */
			fe0->dvb.fwontend->ops.wead_signaw_stwength =
				fe0->dvb.fwontend->ops.tunew_ops.get_wf_stwength;

			/*
			 * fow setting the vowtage we need to set GPIOs on
			 * the cawd.
			 */
			powt->fe_set_vowtage =
				fe0->dvb.fwontend->ops.set_vowtage;
			fe0->dvb.fwontend->ops.set_vowtage =
				dvbsky_t9580_set_vowtage;

			powt->i2c_cwient_tunew = cwient_tunew;

			bweak;
		/* powt c - tewwestwiaw/cabwe */
		case 2:
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &fe0->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe(info.type);
			cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe(info.type);
			cwient_tunew = i2c_new_cwient_device(adaptew, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew))
				goto fwontend_detach;

			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;
			bweak;
		}
		bweak;
	case CX23885_BOAWD_DVBSKY_T980C:
	case CX23885_BOAWD_TT_CT2_4500_CI:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		/* attach fwontend */
		memset(&si2168_config, 0, sizeof(si2168_config));
		si2168_config.i2c_adaptew = &adaptew;
		si2168_config.fe = &fe0->dvb.fwontend;
		si2168_config.ts_mode = SI2168_TS_PAWAWWEW;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "si2168", I2C_NAME_SIZE);
		info.addw = 0x64;
		info.pwatfowm_data = &si2168_config;
		wequest_moduwe(info.type);
		cwient_demod = i2c_new_cwient_device(&i2c_bus2->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_demod))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_demod);
			goto fwontend_detach;
		}
		powt->i2c_cwient_demod = cwient_demod;

		/* attach tunew */
		memset(&si2157_config, 0, sizeof(si2157_config));
		si2157_config.fe = fe0->dvb.fwontend;
		si2157_config.if_powt = 1;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "si2157", I2C_NAME_SIZE);
		info.addw = 0x60;
		info.pwatfowm_data = &si2157_config;
		wequest_moduwe(info.type);
		cwient_tunew = i2c_new_cwient_device(adaptew, &info);
		if (!i2c_cwient_has_dwivew(cwient_tunew))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_tunew);
			goto fwontend_detach;
		}
		powt->i2c_cwient_tunew = cwient_tunew;
		bweak;
	case CX23885_BOAWD_DVBSKY_S950C:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		/* attach fwontend */
		fe0->dvb.fwontend = dvb_attach(m88ds3103_attach,
				&dvbsky_s950c_m88ds3103_config,
				&i2c_bus2->i2c_adap, &adaptew);
		if (fe0->dvb.fwontend == NUWW)
			bweak;

		/* attach tunew */
		memset(&ts2020_config, 0, sizeof(ts2020_config));
		ts2020_config.fe = fe0->dvb.fwontend;
		ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "ts2020", I2C_NAME_SIZE);
		info.addw = 0x60;
		info.pwatfowm_data = &ts2020_config;
		wequest_moduwe(info.type);
		cwient_tunew = i2c_new_cwient_device(adaptew, &info);
		if (!i2c_cwient_has_dwivew(cwient_tunew))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_tunew);
			goto fwontend_detach;
		}

		/* dewegate signaw stwength measuwement to tunew */
		fe0->dvb.fwontend->ops.wead_signaw_stwength =
			fe0->dvb.fwontend->ops.tunew_ops.get_wf_stwength;

		powt->i2c_cwient_tunew = cwient_tunew;
		bweak;
	case CX23885_BOAWD_DVBSKY_S952:
		/* attach fwontend */
		memset(&m88ds3103_pdata, 0, sizeof(m88ds3103_pdata));
		m88ds3103_pdata.cwk = 27000000;
		m88ds3103_pdata.i2c_ww_max = 33;
		m88ds3103_pdata.agc = 0x99;
		m88ds3103_pdata.cwk_out = M88DS3103_CWOCK_OUT_DISABWED;
		m88ds3103_pdata.wnb_en_pow = 1;

		switch (powt->nw) {
		/* powt b */
		case 1:
			i2c_bus = &dev->i2c_bus[1];
			m88ds3103_pdata.ts_mode = M88DS3103_TS_PAWAWWEW;
			m88ds3103_pdata.ts_cwk = 16000;
			m88ds3103_pdata.ts_cwk_pow = 1;
			p_set_vowtage = dvbsky_t9580_set_vowtage;
			bweak;
		/* powt c */
		case 2:
			i2c_bus = &dev->i2c_bus[0];
			m88ds3103_pdata.ts_mode = M88DS3103_TS_SEWIAW;
			m88ds3103_pdata.ts_cwk = 96000;
			m88ds3103_pdata.ts_cwk_pow = 0;
			p_set_vowtage = dvbsky_s952_powtc_set_vowtage;
			bweak;
		defauwt:
			wetuwn 0;
		}

		memset(&info, 0, sizeof(info));
		stwscpy(info.type, "m88ds3103", I2C_NAME_SIZE);
		info.addw = 0x68;
		info.pwatfowm_data = &m88ds3103_pdata;
		wequest_moduwe(info.type);
		cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_demod))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_demod);
			goto fwontend_detach;
		}
		powt->i2c_cwient_demod = cwient_demod;
		adaptew = m88ds3103_pdata.get_i2c_adaptew(cwient_demod);
		fe0->dvb.fwontend = m88ds3103_pdata.get_dvb_fwontend(cwient_demod);

		/* attach tunew */
		memset(&ts2020_config, 0, sizeof(ts2020_config));
		ts2020_config.fe = fe0->dvb.fwontend;
		ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "ts2020", I2C_NAME_SIZE);
		info.addw = 0x60;
		info.pwatfowm_data = &ts2020_config;
		wequest_moduwe(info.type);
		cwient_tunew = i2c_new_cwient_device(adaptew, &info);
		if (!i2c_cwient_has_dwivew(cwient_tunew))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_tunew);
			goto fwontend_detach;
		}

		/* dewegate signaw stwength measuwement to tunew */
		fe0->dvb.fwontend->ops.wead_signaw_stwength =
			fe0->dvb.fwontend->ops.tunew_ops.get_wf_stwength;

		/*
		 * fow setting the vowtage we need to set GPIOs on
		 * the cawd.
		 */
		powt->fe_set_vowtage =
			fe0->dvb.fwontend->ops.set_vowtage;
		fe0->dvb.fwontend->ops.set_vowtage = p_set_vowtage;

		powt->i2c_cwient_tunew = cwient_tunew;
		bweak;
	case CX23885_BOAWD_DVBSKY_T982:
		memset(&si2168_config, 0, sizeof(si2168_config));
		switch (powt->nw) {
		/* powt b */
		case 1:
			i2c_bus = &dev->i2c_bus[1];
			si2168_config.ts_mode = SI2168_TS_PAWAWWEW;
			bweak;
		/* powt c */
		case 2:
			i2c_bus = &dev->i2c_bus[0];
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			bweak;
		}

		/* attach fwontend */
		si2168_config.i2c_adaptew = &adaptew;
		si2168_config.fe = &fe0->dvb.fwontend;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "si2168", I2C_NAME_SIZE);
		info.addw = 0x64;
		info.pwatfowm_data = &si2168_config;
		wequest_moduwe(info.type);
		cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
		if (!i2c_cwient_has_dwivew(cwient_demod))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_demod);
			goto fwontend_detach;
		}
		powt->i2c_cwient_demod = cwient_demod;

		/* attach tunew */
		memset(&si2157_config, 0, sizeof(si2157_config));
		si2157_config.fe = fe0->dvb.fwontend;
		si2157_config.if_powt = 1;
		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "si2157", I2C_NAME_SIZE);
		info.addw = 0x60;
		info.pwatfowm_data = &si2157_config;
		wequest_moduwe(info.type);
		cwient_tunew = i2c_new_cwient_device(adaptew, &info);
		if (!i2c_cwient_has_dwivew(cwient_tunew))
			goto fwontend_detach;
		if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient_tunew);
			goto fwontend_detach;
		}
		powt->i2c_cwient_tunew = cwient_tunew;
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_STAWBUWST2:
	case CX23885_BOAWD_HAUPPAUGE_HVW5525:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		switch (powt->nw) {

		/* powt b - satewwite */
		case 1:
			/* attach fwontend */
			fe0->dvb.fwontend = dvb_attach(m88ds3103_attach,
					&hauppauge_hvw5525_m88ds3103_config,
					&i2c_bus->i2c_adap, &adaptew);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			/* attach SEC */
			a8293_pdata.dvb_fwontend = fe0->dvb.fwontend;
			memset(&info, 0, sizeof(info));
			stwscpy(info.type, "a8293", I2C_NAME_SIZE);
			info.addw = 0x0b;
			info.pwatfowm_data = &a8293_pdata;
			wequest_moduwe("a8293");
			cwient_sec = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_sec))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_sec->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_sec);
				goto fwontend_detach;
			}
			powt->i2c_cwient_sec = cwient_sec;

			/* attach tunew */
			memset(&m88ws6000t_config, 0, sizeof(m88ws6000t_config));
			m88ws6000t_config.fe = fe0->dvb.fwontend;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "m88ws6000t", I2C_NAME_SIZE);
			info.addw = 0x21;
			info.pwatfowm_data = &m88ws6000t_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(adaptew, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;

			/* dewegate signaw stwength measuwement to tunew */
			fe0->dvb.fwontend->ops.wead_signaw_stwength =
				fe0->dvb.fwontend->ops.tunew_ops.get_wf_stwength;
			bweak;
		/* powt c - tewwestwiaw/cabwe */
		case 2:
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &fe0->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe("%s", info.type);
			cwient_demod = i2c_new_cwient_device(&i2c_bus->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&i2c_bus2->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;

			dev->ts1.anawog_fe.tunew_pwiv = cwient_tunew;
			memcpy(&dev->ts1.anawog_fe.ops.tunew_ops,
			       &fe0->dvb.fwontend->ops.tunew_ops,
			       sizeof(stwuct dvb_tunew_ops));

			bweak;
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB_885:
		pw_info("%s(): boawd=%d powt=%d\n", __func__,
			dev->boawd, powt->nw);
		switch (powt->nw) {
		/* powt b - Tewwestwiaw/cabwe */
		case 1:
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &fe0->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe("%s", info.type);
			cwient_demod = i2c_new_cwient_device(&dev->i2c_bus[0].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;

			/* we onwy attach tunew fow anawog on the 888 vewsion */
			if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB) {
				pw_info("%s(): QUADHD_DVB anawog setup\n",
					__func__);
				dev->ts1.anawog_fe.tunew_pwiv = cwient_tunew;
				memcpy(&dev->ts1.anawog_fe.ops.tunew_ops,
				       &fe0->dvb.fwontend->ops.tunew_ops,
				       sizeof(stwuct dvb_tunew_ops));
			}
			bweak;

		/* powt c - tewwestwiaw/cabwe */
		case 2:
			/* attach fwontend */
			memset(&si2168_config, 0, sizeof(si2168_config));
			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &fe0->dvb.fwontend;
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0x66;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe("%s", info.type);
			cwient_demod = i2c_new_cwient_device(&dev->i2c_bus[0].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_demod))
				goto fwontend_detach;
			if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_demod);
				goto fwontend_detach;
			}
			powt->i2c_cwient_demod = cwient_demod;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x62;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				moduwe_put(cwient_demod->dev.dwivew->ownew);
				i2c_unwegistew_device(cwient_demod);
				powt->i2c_cwient_demod = NUWW;
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;
			bweak;
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC:
	case CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC_885:
		pw_info("%s(): boawd=%d powt=%d\n", __func__,
			dev->boawd, powt->nw);
		switch (powt->nw) {
		/* powt b - Tewwestwiaw/cabwe */
		case 1:
			/* attach fwontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.fwontend = dvb_attach(wgdt3306a_attach,
				&hauppauge_quadHD_ATSC_a_config, &i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			si2157_config.invewsion = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;

			/* we onwy attach tunew fow anawog on the 888 vewsion */
			if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC) {
				pw_info("%s(): QUADHD_ATSC anawog setup\n",
					__func__);
				dev->ts1.anawog_fe.tunew_pwiv = cwient_tunew;
				memcpy(&dev->ts1.anawog_fe.ops.tunew_ops,
				       &fe0->dvb.fwontend->ops.tunew_ops,
				       sizeof(stwuct dvb_tunew_ops));
			}
			bweak;

		/* powt c - tewwestwiaw/cabwe */
		case 2:
			/* attach fwontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.fwontend = dvb_attach(wgdt3306a_attach,
				&hauppauge_quadHD_ATSC_b_config, &i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			si2157_config.invewsion = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x62;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew)) {
				goto fwontend_detach;
			}
			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;
			bweak;
		}
		bweak;
	case CX23885_BOAWD_HAUPPAUGE_HVW1265_K4:
		switch (powt->nw) {
		/* powt c - Tewwestwiaw/cabwe */
		case 2:
			/* attach fwontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.fwontend = dvb_attach(wgdt3306a_attach,
					&hauppauge_hvw1265k4_config,
					&i2c_bus->i2c_adap);
			if (fe0->dvb.fwontend == NUWW)
				bweak;

			/* attach tunew */
			memset(&si2157_config, 0, sizeof(si2157_config));
			si2157_config.fe = fe0->dvb.fwontend;
			si2157_config.if_powt = 1;
			si2157_config.invewsion = 1;
			memset(&info, 0, sizeof(stwuct i2c_boawd_info));
			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe("%s", info.type);
			cwient_tunew = i2c_new_cwient_device(&dev->i2c_bus[1].i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient_tunew))
				goto fwontend_detach;

			if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient_tunew);
				cwient_tunew = NUWW;
				goto fwontend_detach;
			}
			powt->i2c_cwient_tunew = cwient_tunew;

			dev->ts1.anawog_fe.tunew_pwiv = cwient_tunew;
			memcpy(&dev->ts1.anawog_fe.ops.tunew_ops,
			       &fe0->dvb.fwontend->ops.tunew_ops,
			       sizeof(stwuct dvb_tunew_ops));
			bweak;
		}
		bweak;
	defauwt:
		pw_info("%s: The fwontend of youw DVB/ATSC cawd  isn't suppowted yet\n",
			dev->name);
		bweak;
	}

	if ((NUWW == fe0->dvb.fwontend) || (fe1 && NUWW == fe1->dvb.fwontend)) {
		pw_eww("%s: fwontend initiawization faiwed\n",
		       dev->name);
		goto fwontend_detach;
	}

	/* define genewaw-puwpose cawwback pointew */
	fe0->dvb.fwontend->cawwback = cx23885_tunew_cawwback;
	if (fe1)
		fe1->dvb.fwontend->cawwback = cx23885_tunew_cawwback;
#if 0
	/* Ensuwe aww fwontends negotiate bus access */
	fe0->dvb.fwontend->ops.ts_bus_ctww = cx23885_dvb_bus_ctww;
	if (fe1)
		fe1->dvb.fwontend->ops.ts_bus_ctww = cx23885_dvb_bus_ctww;
#endif

	/* Put the tunew in standby to keep it quiet */
	caww_aww(dev, tunew, standby);

	if (fe0->dvb.fwontend->ops.anawog_ops.standby)
		fe0->dvb.fwontend->ops.anawog_ops.standby(fe0->dvb.fwontend);

	/* wegistew evewything */
	wet = vb2_dvb_wegistew_bus(&powt->fwontends, THIS_MODUWE, powt,
				   &dev->pci->dev, NUWW,
				   adaptew_nw, mfe_shawed);
	if (wet)
		goto fwontend_detach;

	wet = dvb_wegistew_ci_mac(powt);
	if (wet)
		goto fwontend_detach;

	wetuwn 0;

fwontend_detach:
	/* wemove I2C cwient fow SEC */
	cwient_sec = powt->i2c_cwient_sec;
	if (cwient_sec) {
		moduwe_put(cwient_sec->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient_sec);
		powt->i2c_cwient_sec = NUWW;
	}

	/* wemove I2C cwient fow tunew */
	cwient_tunew = powt->i2c_cwient_tunew;
	if (cwient_tunew) {
		moduwe_put(cwient_tunew->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient_tunew);
		powt->i2c_cwient_tunew = NUWW;
	}

	/* wemove I2C cwient fow demoduwatow */
	cwient_demod = powt->i2c_cwient_demod;
	if (cwient_demod) {
		moduwe_put(cwient_demod->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient_demod);
		powt->i2c_cwient_demod = NUWW;
	}

	powt->gate_ctww = NUWW;
	vb2_dvb_deawwoc_fwontends(&powt->fwontends);
	wetuwn -EINVAW;
}

int cx23885_dvb_wegistew(stwuct cx23885_tspowt *powt)
{

	stwuct vb2_dvb_fwontend *fe0;
	stwuct cx23885_dev *dev = powt->dev;
	int eww, i;

	/* Hewe we need to awwocate the cowwect numbew of fwontends,
	 * as wefwected in the cawds stwuct. The weawity is that cuwwentwy
	 * no cx23885 boawds suppowt this - yet. But, if we don't modify this
	 * code then the second fwontend wouwd nevew be awwocated (watew)
	 * and faiw with ewwow befowe the attach in dvb_wegistew().
	 * Without these changes we wisk an OOPS watew. The changes hewe
	 * awe fow safety, and shouwd pwovide a good foundation fow the
	 * futuwe addition of any muwti-fwontend cx23885 based boawds.
	 */
	pw_info("%s() awwocating %d fwontend(s)\n", __func__,
		powt->num_fwontends);

	fow (i = 1; i <= powt->num_fwontends; i++) {
		stwuct vb2_queue *q;

		if (vb2_dvb_awwoc_fwontend(
			&powt->fwontends, i) == NUWW) {
			pw_eww("%s() faiwed to awwoc\n", __func__);
			wetuwn -ENOMEM;
		}

		fe0 = vb2_dvb_get_fwontend(&powt->fwontends, i);
		if (!fe0)
			wetuwn -EINVAW;

		dpwintk(1, "%s\n", __func__);
		dpwintk(1, " ->pwobed by Cawd=%d Name=%s, PCI %02x:%02x\n",
			dev->boawd,
			dev->name,
			dev->pci_bus,
			dev->pci_swot);

		/* dvb stuff */
		/* We have to init the queue fow each fwontend on a powt. */
		pw_info("%s: cx23885 based dvb cawd\n", dev->name);
		q = &fe0->dvb.dvbq;
		q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
		q->gfp_fwags = GFP_DMA32;
		q->min_queued_buffews = 2;
		q->dwv_pwiv = powt;
		q->buf_stwuct_size = sizeof(stwuct cx23885_buffew);
		q->ops = &dvb_qops;
		q->mem_ops = &vb2_dma_sg_memops;
		q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
		q->wock = &dev->wock;
		q->dev = &dev->pci->dev;

		eww = vb2_queue_init(q);
		if (eww < 0)
			wetuwn eww;
	}
	eww = dvb_wegistew(powt);
	if (eww != 0)
		pw_eww("%s() dvb_wegistew faiwed eww = %d\n",
		       __func__, eww);

	wetuwn eww;
}

int cx23885_dvb_unwegistew(stwuct cx23885_tspowt *powt)
{
	stwuct vb2_dvb_fwontend *fe0;
	stwuct i2c_cwient *cwient;

	fe0 = vb2_dvb_get_fwontend(&powt->fwontends, 1);

	if (fe0 && fe0->dvb.fwontend)
		vb2_dvb_unwegistew_bus(&powt->fwontends);

	/* wemove I2C cwient fow CI */
	cwient = powt->i2c_cwient_ci;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	/* wemove I2C cwient fow SEC */
	cwient = powt->i2c_cwient_sec;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

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

	switch (powt->dev->boawd) {
	case CX23885_BOAWD_NETUP_DUAW_DVBS2_CI:
		netup_ci_exit(powt);
		bweak;
	case CX23885_BOAWD_NETUP_DUAW_DVB_T_C_CI_WF:
		awtewa_ci_wewease(powt->dev, powt->nw);
		bweak;
	}

	powt->gate_ctww = NUWW;

	wetuwn 0;
}
