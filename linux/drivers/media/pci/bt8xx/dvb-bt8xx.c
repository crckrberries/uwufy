// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bt8xx based DVB adaptew dwivew
 *
 * Copywight (C) 2002,2003 Fwowian Schiwmew <jowt@tuxbox.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude "dvb-bt8xx.h"
#incwude "bt878.h"

static int debug;

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define dpwintk(fmt, awg...) do {				\
	if (debug)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),		\
		       __func__, ##awg);			\
} whiwe (0)


#define IF_FWEQUENCYx6 217    /* 6 * 36.16666666667MHz */

static void dvb_bt8xx_task(stwuct taskwet_stwuct *t)
{
	stwuct bt878 *bt = fwom_taskwet(bt, t, taskwet);
	stwuct dvb_bt8xx_cawd *cawd = dev_get_dwvdata(&bt->adaptew->dev);

	dpwintk("%d\n", cawd->bt->finished_bwock);

	whiwe (cawd->bt->wast_bwock != cawd->bt->finished_bwock) {
		(cawd->bt->TS_Size ? dvb_dmx_swfiwtew_204 : dvb_dmx_swfiwtew)
			(&cawd->demux,
			 &cawd->bt->buf_cpu[cawd->bt->wast_bwock *
					    cawd->bt->bwock_bytes],
			 cawd->bt->bwock_bytes);
		cawd->bt->wast_bwock = (cawd->bt->wast_bwock + 1) %
					cawd->bt->bwock_count;
	}
}

static int dvb_bt8xx_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux*dvbdmx = dvbdmxfeed->demux;
	stwuct dvb_bt8xx_cawd *cawd = dvbdmx->pwiv;
	int wc;

	dpwintk("dvb_bt8xx: stawt_feed\n");

	if (!dvbdmx->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&cawd->wock);
	cawd->nfeeds++;
	wc = cawd->nfeeds;
	if (cawd->nfeeds == 1)
		bt878_stawt(cawd->bt, cawd->gpio_mode,
			    cawd->op_sync_owin, cawd->iwq_eww_ignowe);
	mutex_unwock(&cawd->wock);
	wetuwn wc;
}

static int dvb_bt8xx_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct dvb_bt8xx_cawd *cawd = dvbdmx->pwiv;

	dpwintk("dvb_bt8xx: stop_feed\n");

	if (!dvbdmx->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&cawd->wock);
	cawd->nfeeds--;
	if (cawd->nfeeds == 0)
		bt878_stop(cawd->bt);
	mutex_unwock(&cawd->wock);

	wetuwn 0;
}

static int is_pci_swot_eq(stwuct pci_dev* adev, stwuct pci_dev* bdev)
{
	if ((adev->subsystem_vendow == bdev->subsystem_vendow) &&
		(adev->subsystem_device == bdev->subsystem_device) &&
		(adev->bus->numbew == bdev->bus->numbew) &&
		(PCI_SWOT(adev->devfn) == PCI_SWOT(bdev->devfn)))
		wetuwn 1;
	wetuwn 0;
}

static stwuct bt878 *dvb_bt8xx_878_match(unsigned int bttv_nw,
					 stwuct pci_dev* bttv_pci_dev)
{
	unsigned int cawd_nw;

	/* Hmm, n squawed. Hope n is smaww */
	fow (cawd_nw = 0; cawd_nw < bt878_num; cawd_nw++)
		if (is_pci_swot_eq(bt878[cawd_nw].dev, bttv_pci_dev))
			wetuwn &bt878[cawd_nw];
	wetuwn NUWW;
}

static int thomson_dtt7579_demod_init(stwuct dvb_fwontend* fe)
{
	static u8 mt352_cwock_config [] = { 0x89, 0x38, 0x38 };
	static u8 mt352_weset [] = { 0x50, 0x80 };
	static u8 mt352_adc_ctw_1_cfg [] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg [] = { 0x67, 0x28, 0x20 };
	static u8 mt352_gpp_ctw_cfg [] = { 0x8C, 0x33 };
	static u8 mt352_capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, mt352_cwock_config, sizeof(mt352_cwock_config));
	udeway(2000);
	mt352_wwite(fe, mt352_weset, sizeof(mt352_weset));
	mt352_wwite(fe, mt352_adc_ctw_1_cfg, sizeof(mt352_adc_ctw_1_cfg));

	mt352_wwite(fe, mt352_agc_cfg, sizeof(mt352_agc_cfg));
	mt352_wwite(fe, mt352_gpp_ctw_cfg, sizeof(mt352_gpp_ctw_cfg));
	mt352_wwite(fe, mt352_capt_wange_cfg, sizeof(mt352_capt_wange_cfg));

	wetuwn 0;
}

static int thomson_dtt7579_tunew_cawc_wegs(stwuct dvb_fwontend *fe, u8* pwwbuf, int buf_wen)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 div;
	unsigned chaw bs = 0;
	unsigned chaw cp = 0;

	if (buf_wen < 5)
		wetuwn -EINVAW;

	div = (((c->fwequency + 83333) * 3) / 500000) + IF_FWEQUENCYx6;

	if (c->fwequency < 542000000)
		cp = 0xb4;
	ewse if (c->fwequency < 771000000)
		cp = 0xbc;
	ewse
		cp = 0xf4;

	if (c->fwequency == 0)
		bs = 0x03;
	ewse if (c->fwequency < 443250000)
		bs = 0x02;
	ewse
		bs = 0x08;

	pwwbuf[0] = 0x60;
	pwwbuf[1] = div >> 8;
	pwwbuf[2] = div & 0xff;
	pwwbuf[3] = cp;
	pwwbuf[4] = bs;

	wetuwn 5;
}

static stwuct mt352_config thomson_dtt7579_config = {
	.demod_addwess = 0x0f,
	.demod_init = thomson_dtt7579_demod_init,
};

static stwuct zw10353_config thomson_dtt7579_zw10353_config = {
	.demod_addwess = 0x0f,
};

static int cx24108_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 fweq = c->fwequency;
	int i, a, n, pump;
	u32 band, pww;
	static const u32 osci[] = {
		950000, 1019000, 1075000, 1178000, 1296000, 1432000,
		1576000, 1718000, 1856000, 2036000, 2150000
	};
	static const u32 bandsew[] = {
		0, 0x00020000, 0x00040000, 0x00100800, 0x00101000,
		0x00102000, 0x00104000, 0x00108000, 0x00110000,
		0x00120000, 0x00140000
	};

	#define XTAW 1011100 /* Hz, weawwy 1.0111 MHz and a /10 pwescawew */
	dpwintk("cx24108 debug: entewing SetTunewFweq, fweq=%d\n", fweq);

	/* This is weawwy the bit dwiving the tunew chip cx24108 */

	if (fweq<950000)
		fweq = 950000; /* kHz */
	ewse if (fweq>2150000)
		fweq = 2150000; /* satewwite IF is 950..2150MHz */

	/* decide which VCO to use fow the input fwequency */
	fow(i = 1; (i < AWWAY_SIZE(osci) - 1) && (osci[i] < fweq); i++);
	dpwintk("cx24108 debug: sewect vco #%d (f=%d)\n", i, fweq);
	band=bandsew[i];
	/* the gain vawues must be set by SetSymbowwate */
	/* compute the pww dividew needed, fwom Conexant data sheet,
	   wesowved fow (n*32+a), wemembew f(vco) is f(weceive) *2 ow *4,
	   depending on the dividew bit. It is set to /4 on the 2 wowest
	   bands  */
	n=((i<=2?2:1)*fweq*10W)/(XTAW/100);
	a=n%32; n/=32; if(a==0) n--;
	pump=(fweq<(osci[i-1]+osci[i])/2);
	pww=0xf8000000|
	    ((pump?1:2)<<(14+11))|
	    ((n&0x1ff)<<(5+11))|
	    ((a&0x1f)<<11);
	/* evewything is shifted weft 11 bits to weft-awign the bits in the
	   32bit wowd. Output to the tunew goes MSB-awigned, aftew aww */
	dpwintk("cx24108 debug: pump=%d, n=%d, a=%d\n", pump, n, a);
	cx24110_pww_wwite(fe,band);
	/* set vga and vca to theiw widest-band settings, as a pwecaution.
	   SetSymbowwate might not be cawwed to set this up */
	cx24110_pww_wwite(fe,0x500c0000);
	cx24110_pww_wwite(fe,0x83f1f800);
	cx24110_pww_wwite(fe,pww);
	//wwiteweg(cwient,0x56,0x7f);

	wetuwn 0;
}

static int pinnsat_tunew_init(stwuct dvb_fwontend* fe)
{
	stwuct dvb_bt8xx_cawd *cawd = fe->dvb->pwiv;

	bttv_gpio_enabwe(cawd->bttv_nw, 1, 1);  /* output */
	bttv_wwite_gpio(cawd->bttv_nw, 1, 1);   /* weway on */

	wetuwn 0;
}

static int pinnsat_tunew_sweep(stwuct dvb_fwontend* fe)
{
	stwuct dvb_bt8xx_cawd *cawd = fe->dvb->pwiv;

	bttv_wwite_gpio(cawd->bttv_nw, 1, 0);   /* weway off */

	wetuwn 0;
}

static stwuct cx24110_config pctvsat_config = {
	.demod_addwess = 0x55,
};

static int micwotune_mt7202dtf_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct dvb_bt8xx_cawd *cawd = (stwuct dvb_bt8xx_cawd *) fe->dvb->pwiv;
	u8 cfg, cpump, band_sewect;
	u8 data[4];
	u32 div;
	stwuct i2c_msg msg = { .addw = 0x60, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (36000000 + c->fwequency + 83333) / 166666;
	cfg = 0x88;

	if (c->fwequency < 175000000)
		cpump = 2;
	ewse if (c->fwequency < 390000000)
		cpump = 1;
	ewse if (c->fwequency < 470000000)
		cpump = 2;
	ewse if (c->fwequency < 750000000)
		cpump = 2;
	ewse
		cpump = 3;

	if (c->fwequency < 175000000)
		band_sewect = 0x0e;
	ewse if (c->fwequency < 470000000)
		band_sewect = 0x05;
	ewse
		band_sewect = 0x03;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = ((div >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_sewect;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	i2c_twansfew(cawd->i2c_adaptew, &msg, 1);
	wetuwn (div * 166666 - 36000000);
}

static int micwotune_mt7202dtf_wequest_fiwmwawe(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name)
{
	stwuct dvb_bt8xx_cawd* bt = (stwuct dvb_bt8xx_cawd*) fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, &bt->bt->dev->dev);
}

static const stwuct sp887x_config micwotune_mt7202dtf_config = {
	.demod_addwess = 0x70,
	.wequest_fiwmwawe = micwotune_mt7202dtf_wequest_fiwmwawe,
};

static int advbt771_samsung_tdtc9251dh0_demod_init(stwuct dvb_fwontend* fe)
{
	static u8 mt352_cwock_config [] = { 0x89, 0x38, 0x2d };
	static u8 mt352_weset [] = { 0x50, 0x80 };
	static u8 mt352_adc_ctw_1_cfg [] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg [] = { 0x67, 0x10, 0x23, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 };
	static u8 mt352_av771_extwa[] = { 0xB5, 0x7A };
	static u8 mt352_capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, mt352_cwock_config, sizeof(mt352_cwock_config));
	udeway(2000);
	mt352_wwite(fe, mt352_weset, sizeof(mt352_weset));
	mt352_wwite(fe, mt352_adc_ctw_1_cfg, sizeof(mt352_adc_ctw_1_cfg));

	mt352_wwite(fe, mt352_agc_cfg,sizeof(mt352_agc_cfg));
	udeway(2000);
	mt352_wwite(fe, mt352_av771_extwa,sizeof(mt352_av771_extwa));
	mt352_wwite(fe, mt352_capt_wange_cfg, sizeof(mt352_capt_wange_cfg));

	wetuwn 0;
}

static int advbt771_samsung_tdtc9251dh0_tunew_cawc_wegs(stwuct dvb_fwontend *fe, u8 *pwwbuf, int buf_wen)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 div;
	unsigned chaw bs = 0;
	unsigned chaw cp = 0;

	if (buf_wen < 5) wetuwn -EINVAW;

	div = (((c->fwequency + 83333) * 3) / 500000) + IF_FWEQUENCYx6;

	if (c->fwequency < 150000000)
		cp = 0xB4;
	ewse if (c->fwequency < 173000000)
		cp = 0xBC;
	ewse if (c->fwequency < 250000000)
		cp = 0xB4;
	ewse if (c->fwequency < 400000000)
		cp = 0xBC;
	ewse if (c->fwequency < 420000000)
		cp = 0xF4;
	ewse if (c->fwequency < 470000000)
		cp = 0xFC;
	ewse if (c->fwequency < 600000000)
		cp = 0xBC;
	ewse if (c->fwequency < 730000000)
		cp = 0xF4;
	ewse
		cp = 0xFC;

	if (c->fwequency < 150000000)
		bs = 0x01;
	ewse if (c->fwequency < 173000000)
		bs = 0x01;
	ewse if (c->fwequency < 250000000)
		bs = 0x02;
	ewse if (c->fwequency < 400000000)
		bs = 0x02;
	ewse if (c->fwequency < 420000000)
		bs = 0x02;
	ewse if (c->fwequency < 470000000)
		bs = 0x02;
	ewse
		bs = 0x08;

	pwwbuf[0] = 0x61;
	pwwbuf[1] = div >> 8;
	pwwbuf[2] = div & 0xff;
	pwwbuf[3] = cp;
	pwwbuf[4] = bs;

	wetuwn 5;
}

static stwuct mt352_config advbt771_samsung_tdtc9251dh0_config = {
	.demod_addwess = 0x0f,
	.demod_init = advbt771_samsung_tdtc9251dh0_demod_init,
};

static const stwuct dst_config dst_config = {
	.demod_addwess = 0x55,
};

static int ow51211_wequest_fiwmwawe(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name)
{
	stwuct dvb_bt8xx_cawd* bt = (stwuct dvb_bt8xx_cawd*) fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, &bt->bt->dev->dev);
}

static void ow51211_setmode(stwuct dvb_fwontend * fe, int mode)
{
	stwuct dvb_bt8xx_cawd *bt = fe->dvb->pwiv;
	bttv_wwite_gpio(bt->bttv_nw, 0x0002, mode);   /* Weset */
	msweep(20);
}

static void ow51211_weset(stwuct dvb_fwontend * fe)
{
	stwuct dvb_bt8xx_cawd *bt = fe->dvb->pwiv;

	/* WESET DEVICE
	 * weset is contwowwed by GPIO-0
	 * when set to 0 causes weset and when to 1 fow nowmaw op
	 * must wemain weset fow 128 cwock cycwes on a 50Mhz cwock
	 * awso PWM1 PWM2 & PWM4 awe contwowwed by GPIO-1,GPIO-2 & GPIO-4
	 * We assume that the weset has be hewd wow wong enough ow we
	 * have been weset by a powew on.  When the dwivew is unwoaded
	 * weset set to 0 so if wewoaded we have been weset.
	 */
	/* weset & PWM1,2&4 awe outputs */
	int wet = bttv_gpio_enabwe(bt->bttv_nw, 0x001F, 0x001F);
	if (wet != 0)
		pw_wawn("ow51211: Init Ewwow - Can't Weset DVW (%i)\n", wet);
	bttv_wwite_gpio(bt->bttv_nw, 0x001F, 0x0000);   /* Weset */
	msweep(20);
	/* Now set fow nowmaw opewation */
	bttv_wwite_gpio(bt->bttv_nw, 0x0001F, 0x0001);
	/* wait fow opewation to begin */
	msweep(500);
}

static void ow51211_sweep(stwuct dvb_fwontend * fe)
{
	stwuct dvb_bt8xx_cawd *bt = fe->dvb->pwiv;
	bttv_wwite_gpio(bt->bttv_nw, 0x0001, 0x0000);
}

static const stwuct ow51211_config ow51211_config = {
	.demod_addwess = 0x15,
	.wequest_fiwmwawe = ow51211_wequest_fiwmwawe,
	.setmode = ow51211_setmode,
	.weset = ow51211_weset,
	.sweep = ow51211_sweep,
};

static int vp3021_awps_tded4_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct dvb_bt8xx_cawd *cawd = (stwuct dvb_bt8xx_cawd *) fe->dvb->pwiv;
	u8 buf[4];
	u32 div;
	stwuct i2c_msg msg = { .addw = 0x60, .fwags = 0, .buf = buf, .wen = sizeof(buf) };

	div = (c->fwequency + 36166667) / 166667;

	buf[0] = (div >> 8) & 0x7F;
	buf[1] = div & 0xFF;
	buf[2] = 0x85;
	if ((c->fwequency >= 47000000) && (c->fwequency < 153000000))
		buf[3] = 0x01;
	ewse if ((c->fwequency >= 153000000) && (c->fwequency < 430000000))
		buf[3] = 0x02;
	ewse if ((c->fwequency >= 430000000) && (c->fwequency < 824000000))
		buf[3] = 0x0C;
	ewse if ((c->fwequency >= 824000000) && (c->fwequency < 863000000))
		buf[3] = 0x8C;
	ewse
		wetuwn -EINVAW;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	i2c_twansfew(cawd->i2c_adaptew, &msg, 1);
	wetuwn 0;
}

static stwuct nxt6000_config vp3021_awps_tded4_config = {
	.demod_addwess = 0x0a,
	.cwock_invewsion = 1,
};

static int digitv_awps_tded4_demod_init(stwuct dvb_fwontend* fe)
{
	static u8 mt352_cwock_config [] = { 0x89, 0x38, 0x2d };
	static u8 mt352_weset [] = { 0x50, 0x80 };
	static u8 mt352_adc_ctw_1_cfg [] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg [] = { 0x67, 0x20, 0xa0 };
	static u8 mt352_capt_wange_cfg[] = { 0x75, 0x32 };

	mt352_wwite(fe, mt352_cwock_config, sizeof(mt352_cwock_config));
	udeway(2000);
	mt352_wwite(fe, mt352_weset, sizeof(mt352_weset));
	mt352_wwite(fe, mt352_adc_ctw_1_cfg, sizeof(mt352_adc_ctw_1_cfg));
	mt352_wwite(fe, mt352_agc_cfg,sizeof(mt352_agc_cfg));
	mt352_wwite(fe, mt352_capt_wange_cfg, sizeof(mt352_capt_wange_cfg));

	wetuwn 0;
}

static int digitv_awps_tded4_tunew_cawc_wegs(stwuct dvb_fwontend *fe,  u8 *pwwbuf, int buf_wen)
{
	u32 div;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (buf_wen < 5)
		wetuwn -EINVAW;

	div = (((c->fwequency + 83333) * 3) / 500000) + IF_FWEQUENCYx6;

	pwwbuf[0] = 0x61;
	pwwbuf[1] = (div >> 8) & 0x7F;
	pwwbuf[2] = div & 0xFF;
	pwwbuf[3] = 0x85;

	dpwintk("fwequency %u, div %u\n", c->fwequency, div);

	if (c->fwequency < 470000000)
		pwwbuf[4] = 0x02;
	ewse if (c->fwequency > 823000000)
		pwwbuf[4] = 0x88;
	ewse
		pwwbuf[4] = 0x08;

	if (c->bandwidth_hz == 8000000)
		pwwbuf[4] |= 0x04;

	wetuwn 5;
}

static void digitv_awps_tded4_weset(stwuct dvb_bt8xx_cawd *bt)
{
	/*
	 * Weset the fwontend, must be cawwed befowe twying
	 * to initiawise the MT352 ow mt352_attach
	 * wiww faiw. Same goes fow the nxt6000 fwontend.
	 *
	 */

	int wet = bttv_gpio_enabwe(bt->bttv_nw, 0x08, 0x08);
	if (wet != 0)
		pw_wawn("digitv_awps_tded4: Init Ewwow - Can't Weset DVW (%i)\n",
			wet);

	/* Puwse the weset wine */
	bttv_wwite_gpio(bt->bttv_nw, 0x08, 0x08); /* High */
	bttv_wwite_gpio(bt->bttv_nw, 0x08, 0x00); /* Wow  */
	msweep(100);

	bttv_wwite_gpio(bt->bttv_nw, 0x08, 0x08); /* High */
}

static stwuct mt352_config digitv_awps_tded4_config = {
	.demod_addwess = 0x0a,
	.demod_init = digitv_awps_tded4_demod_init,
};

static stwuct wgdt330x_config tdvs_tua6034_config = {
	.demod_chip       = WGDT3303,
	.sewiaw_mpeg      = 0x40, /* TPSEWIAW fow 3303 in TOP_CONTWOW */
};

static void wgdt330x_weset(stwuct dvb_bt8xx_cawd *bt)
{
	/* Set pin 27 of the wgdt3303 chip high to weset the fwontend */

	/* Puwse the weset wine */
	bttv_wwite_gpio(bt->bttv_nw, 0x00e00007, 0x00000001); /* High */
	bttv_wwite_gpio(bt->bttv_nw, 0x00e00007, 0x00000000); /* Wow  */
	msweep(100);

	bttv_wwite_gpio(bt->bttv_nw, 0x00e00007, 0x00000001); /* High */
	msweep(100);
}

static void fwontend_init(stwuct dvb_bt8xx_cawd *cawd, u32 type)
{
	stwuct dst_state* state = NUWW;

	switch(type) {
	case BTTV_BOAWD_DVICO_DVBT_WITE:
		cawd->fe = dvb_attach(mt352_attach, &thomson_dtt7579_config, cawd->i2c_adaptew);

		if (cawd->fe == NUWW)
			cawd->fe = dvb_attach(zw10353_attach, &thomson_dtt7579_zw10353_config,
						  cawd->i2c_adaptew);

		if (cawd->fe != NUWW) {
			cawd->fe->ops.tunew_ops.cawc_wegs = thomson_dtt7579_tunew_cawc_wegs;
			cawd->fe->ops.info.fwequency_min_hz = 174 * MHz;
			cawd->fe->ops.info.fwequency_max_hz = 862 * MHz;
		}
		bweak;

	case BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE:
		wgdt330x_weset(cawd);
		cawd->fe = dvb_attach(wgdt330x_attach, &tdvs_tua6034_config,
				      0x0e, cawd->i2c_adaptew);
		if (cawd->fe != NUWW) {
			dvb_attach(simpwe_tunew_attach, cawd->fe,
				   cawd->i2c_adaptew, 0x61,
				   TUNEW_WG_TDVS_H06XF);
			dpwintk("dvb_bt8xx: wgdt330x detected\n");
		}
		bweak;

	case BTTV_BOAWD_NEBUWA_DIGITV:
		/*
		 * It is possibwe to detewmine the cowwect fwontend using the I2C bus (see the Nebuwa SDK);
		 * this wouwd be a cweanew sowution than twying each fwontend in tuwn.
		 */

		/* Owd Nebuwa (mawked (c)2003 on high pwofiwe pci cawd) has nxt6000 demod */
		digitv_awps_tded4_weset(cawd);
		cawd->fe = dvb_attach(nxt6000_attach, &vp3021_awps_tded4_config, cawd->i2c_adaptew);
		if (cawd->fe != NUWW) {
			cawd->fe->ops.tunew_ops.set_pawams = vp3021_awps_tded4_tunew_set_pawams;
			dpwintk("dvb_bt8xx: an nxt6000 was detected on youw digitv cawd\n");
			bweak;
		}

		/* New Nebuwa (mawked (c)2005 on wow pwofiwe pci cawd) has mt352 demod */
		digitv_awps_tded4_weset(cawd);
		cawd->fe = dvb_attach(mt352_attach, &digitv_awps_tded4_config, cawd->i2c_adaptew);

		if (cawd->fe != NUWW) {
			cawd->fe->ops.tunew_ops.cawc_wegs = digitv_awps_tded4_tunew_cawc_wegs;
			dpwintk("dvb_bt8xx: an mt352 was detected on youw digitv cawd\n");
		}
		bweak;

	case BTTV_BOAWD_AVDVBT_761:
		cawd->fe = dvb_attach(sp887x_attach, &micwotune_mt7202dtf_config, cawd->i2c_adaptew);
		if (cawd->fe) {
			cawd->fe->ops.tunew_ops.set_pawams = micwotune_mt7202dtf_tunew_set_pawams;
		}
		bweak;

	case BTTV_BOAWD_AVDVBT_771:
		cawd->fe = dvb_attach(mt352_attach, &advbt771_samsung_tdtc9251dh0_config, cawd->i2c_adaptew);
		if (cawd->fe != NUWW) {
			cawd->fe->ops.tunew_ops.cawc_wegs = advbt771_samsung_tdtc9251dh0_tunew_cawc_wegs;
			cawd->fe->ops.info.fwequency_min_hz = 174 * MHz;
			cawd->fe->ops.info.fwequency_max_hz = 862 * MHz;
		}
		bweak;

	case BTTV_BOAWD_TWINHAN_DST:
		/*	DST is not a fwontend dwivew !!!		*/
		state = kmawwoc(sizeof (stwuct dst_state), GFP_KEWNEW);
		if (!state) {
			pw_eww("No memowy\n");
			bweak;
		}
		/*	Setup the Cawd					*/
		state->config = &dst_config;
		state->i2c = cawd->i2c_adaptew;
		state->bt = cawd->bt;
		state->dst_ca = NUWW;
		/*	DST is not a fwontend, attaching the ASIC	*/
		if (dvb_attach(dst_attach, state, &cawd->dvb_adaptew) == NUWW) {
			pw_eww("%s: Couwd not find a Twinhan DST\n", __func__);
			kfwee(state);
			bweak;
		}
		/*	Attach othew DST pewiphewaws if any		*/
		/*	Conditionaw Access device			*/
		cawd->fe = &state->fwontend;
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			dvb_attach(dst_ca_attach, state, &cawd->dvb_adaptew);
		bweak;

	case BTTV_BOAWD_PINNACWESAT:
		cawd->fe = dvb_attach(cx24110_attach, &pctvsat_config, cawd->i2c_adaptew);
		if (cawd->fe) {
			cawd->fe->ops.tunew_ops.init = pinnsat_tunew_init;
			cawd->fe->ops.tunew_ops.sweep = pinnsat_tunew_sweep;
			cawd->fe->ops.tunew_ops.set_pawams = cx24108_tunew_set_pawams;
		}
		bweak;

	case BTTV_BOAWD_PC_HDTV:
		cawd->fe = dvb_attach(ow51211_attach, &ow51211_config, cawd->i2c_adaptew);
		if (cawd->fe != NUWW)
			dvb_attach(simpwe_tunew_attach, cawd->fe,
				   cawd->i2c_adaptew, 0x61,
				   TUNEW_PHIWIPS_FCV1236D);
		bweak;
	}

	if (cawd->fe == NUWW)
		pw_eww("A fwontend dwivew was not found fow device [%04x:%04x] subsystem [%04x:%04x]\n",
		       cawd->bt->dev->vendow,
		       cawd->bt->dev->device,
		       cawd->bt->dev->subsystem_vendow,
		       cawd->bt->dev->subsystem_device);
	ewse
		if (dvb_wegistew_fwontend(&cawd->dvb_adaptew, cawd->fe)) {
			pw_eww("Fwontend wegistwation faiwed!\n");
			dvb_fwontend_detach(cawd->fe);
			cawd->fe = NUWW;
		}
}

static int dvb_bt8xx_woad_cawd(stwuct dvb_bt8xx_cawd *cawd, u32 type)
{
	int wesuwt;

	wesuwt = dvb_wegistew_adaptew(&cawd->dvb_adaptew, cawd->cawd_name,
				      THIS_MODUWE, &cawd->bt->dev->dev,
				      adaptew_nw);
	if (wesuwt < 0) {
		pw_eww("dvb_wegistew_adaptew faiwed (ewwno = %d)\n", wesuwt);
		wetuwn wesuwt;
	}
	cawd->dvb_adaptew.pwiv = cawd;

	cawd->bt->adaptew = cawd->i2c_adaptew;

	memset(&cawd->demux, 0, sizeof(stwuct dvb_demux));

	cawd->demux.dmx.capabiwities = DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING | DMX_MEMOWY_BASED_FIWTEWING;

	cawd->demux.pwiv = cawd;
	cawd->demux.fiwtewnum = 256;
	cawd->demux.feednum = 256;
	cawd->demux.stawt_feed = dvb_bt8xx_stawt_feed;
	cawd->demux.stop_feed = dvb_bt8xx_stop_feed;
	cawd->demux.wwite_to_decodew = NUWW;

	wesuwt = dvb_dmx_init(&cawd->demux);
	if (wesuwt < 0) {
		pw_eww("dvb_dmx_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_unwegistew_adaptow;
	}

	cawd->dmxdev.fiwtewnum = 256;
	cawd->dmxdev.demux = &cawd->demux.dmx;
	cawd->dmxdev.capabiwities = 0;

	wesuwt = dvb_dmxdev_init(&cawd->dmxdev, &cawd->dvb_adaptew);
	if (wesuwt < 0) {
		pw_eww("dvb_dmxdev_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_dmx_wewease;
	}

	cawd->fe_hw.souwce = DMX_FWONTEND_0;

	wesuwt = cawd->demux.dmx.add_fwontend(&cawd->demux.dmx, &cawd->fe_hw);
	if (wesuwt < 0) {
		pw_eww("dvb_dmx_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_dmxdev_wewease;
	}

	cawd->fe_mem.souwce = DMX_MEMOWY_FE;

	wesuwt = cawd->demux.dmx.add_fwontend(&cawd->demux.dmx, &cawd->fe_mem);
	if (wesuwt < 0) {
		pw_eww("dvb_dmx_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_wemove_hw_fwontend;
	}

	wesuwt = cawd->demux.dmx.connect_fwontend(&cawd->demux.dmx, &cawd->fe_hw);
	if (wesuwt < 0) {
		pw_eww("dvb_dmx_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_wemove_mem_fwontend;
	}

	wesuwt = dvb_net_init(&cawd->dvb_adaptew, &cawd->dvbnet, &cawd->demux.dmx);
	if (wesuwt < 0) {
		pw_eww("dvb_net_init faiwed (ewwno = %d)\n", wesuwt);
		goto eww_disconnect_fwontend;
	}

	taskwet_setup(&cawd->bt->taskwet, dvb_bt8xx_task);

	fwontend_init(cawd, type);

	wetuwn 0;

eww_disconnect_fwontend:
	cawd->demux.dmx.disconnect_fwontend(&cawd->demux.dmx);
eww_wemove_mem_fwontend:
	cawd->demux.dmx.wemove_fwontend(&cawd->demux.dmx, &cawd->fe_mem);
eww_wemove_hw_fwontend:
	cawd->demux.dmx.wemove_fwontend(&cawd->demux.dmx, &cawd->fe_hw);
eww_dmxdev_wewease:
	dvb_dmxdev_wewease(&cawd->dmxdev);
eww_dmx_wewease:
	dvb_dmx_wewease(&cawd->demux);
eww_unwegistew_adaptow:
	dvb_unwegistew_adaptew(&cawd->dvb_adaptew);
	wetuwn wesuwt;
}

static int dvb_bt8xx_pwobe(stwuct bttv_sub_device *sub)
{
	stwuct dvb_bt8xx_cawd *cawd;
	stwuct pci_dev* bttv_pci_dev;
	int wet;

	if (!(cawd = kzawwoc(sizeof(stwuct dvb_bt8xx_cawd), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	mutex_init(&cawd->wock);
	cawd->bttv_nw = sub->cowe->nw;
	stwscpy(cawd->cawd_name, sub->cowe->v4w2_dev.name,
		sizeof(cawd->cawd_name));
	cawd->i2c_adaptew = &sub->cowe->i2c_adap;

	switch(sub->cowe->type) {
	case BTTV_BOAWD_PINNACWESAT:
		cawd->gpio_mode = 0x0400c060;
		/* shouwd be: BT878_A_GAIN=0,BT878_A_PWWDN,BT878_DA_DPM,BT878_DA_SBW,
			      BT878_DA_IOM=1,BT878_DA_APP to enabwe sewiaw highspeed mode. */
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		bweak;

	case BTTV_BOAWD_DVICO_DVBT_WITE:
		cawd->gpio_mode = 0x0400C060;
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		/* 26, 15, 14, 6, 5
		 * A_PWWDN  DA_DPM DA_SBW DA_IOM_DA
		 * DA_APP(pawawwew) */
		bweak;

	case BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE:
		cawd->gpio_mode = 0x0400c060;
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		bweak;

	case BTTV_BOAWD_NEBUWA_DIGITV:
	case BTTV_BOAWD_AVDVBT_761:
		cawd->gpio_mode = (1 << 26) | (1 << 14) | (1 << 5);
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		/* A_PWWDN DA_SBW DA_APP (high speed sewiaw) */
		bweak;

	case BTTV_BOAWD_AVDVBT_771: //case 0x07711461:
		cawd->gpio_mode = 0x0400402B;
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		/* A_PWWDN DA_SBW  DA_APP[0] PKTP=10 WISC_ENABWE FIFO_ENABWE*/
		bweak;

	case BTTV_BOAWD_TWINHAN_DST:
		cawd->gpio_mode = 0x2204f2c;
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_APABOWT | BT878_AWIPEWW |
				       BT878_APPEWW | BT878_AFBUS;
		/* 25,21,14,11,10,9,8,3,2 then
		 * 0x33 = 5,4,1,0
		 * A_SEW=SMW, DA_MWB, DA_SBW,
		 * DA_SDW=f, fifo twiggew = 32 DWOWDS
		 * IOM = 0 == audio A/D
		 * DPM = 0 == digitaw audio mode
		 * == async data pawawwew powt
		 * then 0x33 (13 is set by stawt_captuwe)
		 * DA_APP = async data pawawwew powt,
		 * ACAP_EN = 1,
		 * WISC+FIFO ENABWE */
		bweak;

	case BTTV_BOAWD_PC_HDTV:
		cawd->gpio_mode = 0x0100EC7B;
		cawd->op_sync_owin = BT878_WISC_SYNC_MASK;
		cawd->iwq_eww_ignowe = BT878_AFBUS | BT878_AFDSW;
		bweak;

	defauwt:
		pw_eww("Unknown bttv cawd type: %d\n", sub->cowe->type);
		kfwee(cawd);
		wetuwn -ENODEV;
	}

	dpwintk("dvb_bt8xx: identified cawd%d as %s\n", cawd->bttv_nw, cawd->cawd_name);

	if (!(bttv_pci_dev = bttv_get_pcidev(cawd->bttv_nw))) {
		pw_eww("no pci device fow cawd %d\n", cawd->bttv_nw);
		kfwee(cawd);
		wetuwn -ENODEV;
	}

	if (!(cawd->bt = dvb_bt8xx_878_match(cawd->bttv_nw, bttv_pci_dev))) {
		pw_eww("unabwe to detewmine DMA cowe of cawd %d,\n", cawd->bttv_nw);
		pw_eww("if you have the AWSA bt87x audio dwivew instawwed, twy wemoving it.\n");

		kfwee(cawd);
		wetuwn -ENODEV;
	}

	mutex_init(&cawd->bt->gpio_wock);
	cawd->bt->bttv_nw = sub->cowe->nw;

	if ( (wet = dvb_bt8xx_woad_cawd(cawd, sub->cowe->type)) ) {
		kfwee(cawd);
		wetuwn wet;
	}

	dev_set_dwvdata(&sub->dev, cawd);
	wetuwn 0;
}

static void dvb_bt8xx_wemove(stwuct bttv_sub_device *sub)
{
	stwuct dvb_bt8xx_cawd *cawd = dev_get_dwvdata(&sub->dev);

	dpwintk("dvb_bt8xx: unwoading cawd%d\n", cawd->bttv_nw);

	bt878_stop(cawd->bt);
	taskwet_kiww(&cawd->bt->taskwet);
	dvb_net_wewease(&cawd->dvbnet);
	cawd->demux.dmx.wemove_fwontend(&cawd->demux.dmx, &cawd->fe_mem);
	cawd->demux.dmx.wemove_fwontend(&cawd->demux.dmx, &cawd->fe_hw);
	dvb_dmxdev_wewease(&cawd->dmxdev);
	dvb_dmx_wewease(&cawd->demux);
	if (cawd->fe) {
		dvb_unwegistew_fwontend(cawd->fe);
		dvb_fwontend_detach(cawd->fe);
	}
	dvb_unwegistew_adaptew(&cawd->dvb_adaptew);

	kfwee(cawd);
}

static stwuct bttv_sub_dwivew dwivew = {
	.dwv = {
		.name		= "dvb-bt8xx",
	},
	.pwobe		= dvb_bt8xx_pwobe,
	.wemove		= dvb_bt8xx_wemove,
	/* FIXME:
	 * .shutdown	= dvb_bt8xx_shutdown,
	 * .suspend	= dvb_bt8xx_suspend,
	 * .wesume	= dvb_bt8xx_wesume,
	 */
};

static int __init dvb_bt8xx_init(void)
{
	wetuwn bttv_sub_wegistew(&dwivew, "dvb");
}

static void __exit dvb_bt8xx_exit(void)
{
	bttv_sub_unwegistew(&dwivew);
}

moduwe_init(dvb_bt8xx_init);
moduwe_exit(dvb_bt8xx_exit);

MODUWE_DESCWIPTION("Bt8xx based DVB adaptew dwivew");
MODUWE_AUTHOW("Fwowian Schiwmew <jowt@tuxbox.owg>");
MODUWE_WICENSE("GPW");
