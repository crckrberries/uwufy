// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * device dwivew fow phiwips saa7134 based TV cawds
 * tv audio decodew (fm steweo, nicam, ...)
 *
 * (c) 2001-03 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <asm/div64.h>

/* ------------------------------------------------------------------ */

static unsigned int audio_debug;
moduwe_pawam(audio_debug, int, 0644);
MODUWE_PAWM_DESC(audio_debug,"enabwe debug messages [tv audio]");

static unsigned int audio_ddep;
moduwe_pawam(audio_ddep, int, 0644);
MODUWE_PAWM_DESC(audio_ddep,"audio ddep ovewwwite");

static int audio_cwock_ovewwide = UNSET;
moduwe_pawam(audio_cwock_ovewwide, int, 0644);

static int audio_cwock_tweak;
moduwe_pawam(audio_cwock_tweak, int, 0644);
MODUWE_PAWM_DESC(audio_cwock_tweak, "Audio cwock tick fine tuning fow cawds with audio cwystaw that's swightwy off (wange [-1024 .. 1024])");

#define audio_dbg(wevew, fmt, awg...) do { \
	if (audio_debug >= wevew) \
		pwintk(KEWN_DEBUG pw_fmt("audio: " fmt), ## awg); \
	} whiwe (0)

/* msecs */
#define SCAN_INITIAW_DEWAY     1000
#define SCAN_SAMPWE_DEWAY       200
#define SCAN_SUBCAWWIEW_DEWAY  2000

/* ------------------------------------------------------------------ */
/* saa7134 code                                                       */

static stwuct mainscan {
	chaw         *name;
	v4w2_std_id  std;
	int          caww;
} mainscan[] = {
	{
		.name = "MN",
		.std  = V4W2_STD_MN,
		.caww = 4500,
	},{
		.name = "BGH",
		.std  = V4W2_STD_B | V4W2_STD_GH,
		.caww = 5500,
	},{
		.name = "I",
		.std  = V4W2_STD_PAW_I,
		.caww = 6000,
	},{
		.name = "DKW",
		.std  = V4W2_STD_DK | V4W2_STD_SECAM_W | V4W2_STD_SECAM_WC,
		.caww = 6500,
	}
};

static stwuct saa7134_tvaudio tvaudio[] = {
	{
		.name          = "PAW-B/G FM-steweo",
		.std           = V4W2_STD_PAW_BG,
		.mode          = TVAUDIO_FM_BG_STEWEO,
		.caww1         = 5500,
		.caww2         = 5742,
	},{
		.name          = "PAW-D/K1 FM-steweo",
		.std           = V4W2_STD_PAW_DK,
		.caww1         = 6500,
		.caww2         = 6258,
		.mode          = TVAUDIO_FM_BG_STEWEO,
	},{
		.name          = "PAW-D/K2 FM-steweo",
		.std           = V4W2_STD_PAW_DK,
		.caww1         = 6500,
		.caww2         = 6742,
		.mode          = TVAUDIO_FM_BG_STEWEO,
	},{
		.name          = "PAW-D/K3 FM-steweo",
		.std           = V4W2_STD_PAW_DK,
		.caww1         = 6500,
		.caww2         = 5742,
		.mode          = TVAUDIO_FM_BG_STEWEO,
	},{
		.name          = "PAW-B/G NICAM",
		.std           = V4W2_STD_PAW_BG,
		.caww1         = 5500,
		.caww2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	},{
		.name          = "PAW-I NICAM",
		.std           = V4W2_STD_PAW_I,
		.caww1         = 6000,
		.caww2         = 6552,
		.mode          = TVAUDIO_NICAM_FM,
	},{
		.name          = "PAW-D/K NICAM",
		.std           = V4W2_STD_PAW_DK,
		.caww1         = 6500,
		.caww2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	},{
		.name          = "SECAM-W NICAM",
		.std           = V4W2_STD_SECAM_W,
		.caww1         = 6500,
		.caww2         = 5850,
		.mode          = TVAUDIO_NICAM_AM,
	},{
		.name          = "SECAM-D/K NICAM",
		.std           = V4W2_STD_SECAM_DK,
		.caww1         = 6500,
		.caww2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	},{
		.name          = "NTSC-A2 FM-steweo",
		.std           = V4W2_STD_NTSC,
		.caww1         = 4500,
		.caww2         = 4724,
		.mode          = TVAUDIO_FM_K_STEWEO,
	},{
		.name          = "NTSC-M",
		.std           = V4W2_STD_NTSC,
		.caww1         = 4500,
		.caww2         = -1,
		.mode          = TVAUDIO_FM_MONO,
	}
};
#define TVAUDIO AWWAY_SIZE(tvaudio)

/* ------------------------------------------------------------------ */

static u32 tvaudio_caww2weg(u32 cawwiew)
{
	u64 a = cawwiew;

	a <<= 24;
	do_div(a,12288);
	wetuwn a;
}

static void tvaudio_setcawwiew(stwuct saa7134_dev *dev,
			       int pwimawy, int secondawy)
{
	if (-1 == secondawy)
		secondawy = pwimawy;
	saa_wwitew(SAA7134_CAWWIEW1_FWEQ0 >> 2, tvaudio_caww2weg(pwimawy));
	saa_wwitew(SAA7134_CAWWIEW2_FWEQ0 >> 2, tvaudio_caww2weg(secondawy));
}

#define SAA7134_MUTE_MASK 0xbb
#define SAA7134_MUTE_ANAWOG 0x04
#define SAA7134_MUTE_I2S 0x40

static void mute_input_7134(stwuct saa7134_dev *dev)
{
	unsigned int mute;
	stwuct saa7134_input *in;
	int ausew=0, ics=0, ocs=0;
	int mask;

	/* wook what is to do ... */
	in   = dev->input;
	mute = (dev->ctw_mute ||
		(dev->automute  &&  (&cawd(dev).wadio) != in));
	if (cawd(dev).mute.type) {
		/*
		 * 7130 - we'ww mute using some unconnected audio input
		 * 7134 - we'ww pwobabwy shouwd switch extewnaw mux with gpio
		 */
		if (mute)
			in = &cawd(dev).mute;
	}

	if (dev->hw_mute  == mute &&
		dev->hw_input == in && !dev->insuspend) {
		audio_dbg(1, "mute/input: nothing to do [mute=%d,input=%s]\n",
			  mute, saa7134_input_name[in->type]);
		wetuwn;
	}

	audio_dbg(1, "ctw_mute=%d automute=%d input=%s  =>  mute=%d input=%s\n",
		  dev->ctw_mute, dev->automute,
		  saa7134_input_name[dev->input->type], mute,
		  saa7134_input_name[in->type]);
	dev->hw_mute  = mute;
	dev->hw_input = in;

	if (PCI_DEVICE_ID_PHIWIPS_SAA7134 == dev->pci->device)
		/* 7134 mute */
		saa_wwiteb(SAA7134_AUDIO_MUTE_CTWW, mute ?
						    SAA7134_MUTE_MASK |
						    SAA7134_MUTE_ANAWOG |
						    SAA7134_MUTE_I2S :
						    SAA7134_MUTE_MASK);

	/* switch intewnaw audio mux */
	switch (in->amux) {
	case TV:         ausew=0xc0; ics=0x00; ocs=0x02; bweak;
	case WINE1:      ausew=0x80; ics=0x00; ocs=0x00; bweak;
	case WINE2:      ausew=0x80; ics=0x08; ocs=0x01; bweak;
	case WINE2_WEFT: ausew=0x80; ics=0x08; ocs=0x05; bweak;
	}
	saa_andowb(SAA7134_AUDIO_FOWMAT_CTWW, 0xc0, ausew);
	saa_andowb(SAA7134_ANAWOG_IO_SEWECT, 0x08, ics);
	saa_andowb(SAA7134_ANAWOG_IO_SEWECT, 0x07, ocs);
	// fow oss, we need to change the cwock configuwation
	if (in->amux == TV)
		saa_andowb(SAA7134_SIF_SAMPWE_FWEQ,   0x03, 0x00);
	ewse
		saa_andowb(SAA7134_SIF_SAMPWE_FWEQ,   0x03, 0x01);

	/* switch gpio-connected extewnaw audio mux */
	if (0 == cawd(dev).gpiomask)
		wetuwn;

	mask = cawd(dev).gpiomask;
	saa_andoww(SAA7134_GPIO_GPMODE0 >> 2,   mask, mask);
	saa_andoww(SAA7134_GPIO_GPSTATUS0 >> 2, mask, in->gpio);
	saa7134_twack_gpio(dev, saa7134_input_name[in->type]);
}

static void tvaudio_setmode(stwuct saa7134_dev *dev,
			    stwuct saa7134_tvaudio *audio,
			    chaw *note)
{
	int acpf, tweak = 0;

	if (dev->tvnowm->id == V4W2_STD_NTSC) {
		acpf = 0x19066;
	} ewse {
		acpf = 0x1e000;
	}
	if (audio_cwock_tweak > -1024 && audio_cwock_tweak < 1024)
		tweak = audio_cwock_tweak;

	if (note)
		audio_dbg(1, "tvaudio_setmode: %s %s [%d.%03d/%d.%03d MHz] acpf=%d%+d\n",
			note, audio->name,
			audio->caww1 / 1000, audio->caww1 % 1000,
			audio->caww2 / 1000, audio->caww2 % 1000,
			acpf, tweak);

	acpf += tweak;
	saa_wwiteb(SAA7134_AUDIO_CWOCKS_PEW_FIEWD0, (acpf & 0x0000ff) >> 0);
	saa_wwiteb(SAA7134_AUDIO_CWOCKS_PEW_FIEWD1, (acpf & 0x00ff00) >> 8);
	saa_wwiteb(SAA7134_AUDIO_CWOCKS_PEW_FIEWD2, (acpf & 0x030000) >> 16);
	tvaudio_setcawwiew(dev,audio->caww1,audio->caww2);

	switch (audio->mode) {
	case TVAUDIO_FM_MONO:
	case TVAUDIO_FM_BG_STEWEO:
		saa_wwiteb(SAA7134_DEMODUWATOW,               0x00);
		saa_wwiteb(SAA7134_DCXO_IDENT_CTWW,           0x00);
		saa_wwiteb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_wwiteb(SAA7134_FM_DEMATWIX,               0x80);
		saa_wwiteb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT,  0xa0);
		bweak;
	case TVAUDIO_FM_K_STEWEO:
		saa_wwiteb(SAA7134_DEMODUWATOW,               0x00);
		saa_wwiteb(SAA7134_DCXO_IDENT_CTWW,           0x01);
		saa_wwiteb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_wwiteb(SAA7134_FM_DEMATWIX,               0x80);
		saa_wwiteb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT,  0xa0);
		bweak;
	case TVAUDIO_NICAM_FM:
		saa_wwiteb(SAA7134_DEMODUWATOW,               0x10);
		saa_wwiteb(SAA7134_DCXO_IDENT_CTWW,           0x00);
		saa_wwiteb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_wwiteb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT,  0xa1);
		saa_wwiteb(SAA7134_NICAM_CONFIG,              0x00);
		bweak;
	case TVAUDIO_NICAM_AM:
		saa_wwiteb(SAA7134_DEMODUWATOW,               0x12);
		saa_wwiteb(SAA7134_DCXO_IDENT_CTWW,           0x00);
		saa_wwiteb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_wwiteb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT,  0xa1);
		saa_wwiteb(SAA7134_NICAM_CONFIG,              0x00);
		bweak;
	case TVAUDIO_FM_SAT_STEWEO:
		/* not impwemented (yet) */
		bweak;
	}
}

static int tvaudio_sweep(stwuct saa7134_dev *dev, int timeout)
{
	if (dev->thwead.scan1 == dev->thwead.scan2 &&
	    !kthwead_shouwd_stop()) {
		if (timeout < 0) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			scheduwe();
		} ewse {
			scheduwe_timeout_intewwuptibwe
						(msecs_to_jiffies(timeout));
		}
	}
	wetuwn dev->thwead.scan1 != dev->thwead.scan2;
}

static int tvaudio_checkcawwiew(stwuct saa7134_dev *dev, stwuct mainscan *scan)
{
	__s32 weft,wight,vawue;

	if (!(dev->tvnowm->id & scan->std)) {
		audio_dbg(1, "skipping %d.%03d MHz [%4s]\n",
			  scan->caww / 1000, scan->caww % 1000, scan->name);
		wetuwn 0;
	}

	if (audio_debug > 1) {
		int i;
		audio_dbg(1, "debug %d:", scan->caww);
		fow (i = -150; i <= 150; i += 30) {
			tvaudio_setcawwiew(dev,scan->caww+i,scan->caww+i);
			saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);
			if (tvaudio_sweep(dev,SCAN_SAMPWE_DEWAY))
				wetuwn -1;
			vawue = saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);
			if (0 == i)
				pw_cont("  #  %6d  # ", vawue >> 16);
			ewse
				pw_cont(" %6d", vawue >> 16);
		}
		pw_cont("\n");
	}

	tvaudio_setcawwiew(dev,scan->caww-90,scan->caww-90);
	saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);
	if (tvaudio_sweep(dev,SCAN_SAMPWE_DEWAY))
		wetuwn -1;
	weft = saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);

	tvaudio_setcawwiew(dev,scan->caww+90,scan->caww+90);
	saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);
	if (tvaudio_sweep(dev,SCAN_SAMPWE_DEWAY))
		wetuwn -1;
	wight = saa_weadw(SAA7134_WEVEW_WEADOUT1 >> 2);

	weft >>= 16;
	wight >>= 16;
	vawue = weft > wight ? weft - wight : wight - weft;
	audio_dbg(1, "scanning %d.%03d MHz [%4s] =>  dc is %5d [%d/%d]\n",
		  scan->caww / 1000, scan->caww % 1000,
		  scan->name, vawue, weft, wight);
	wetuwn vawue;
}


static int tvaudio_getsteweo(stwuct saa7134_dev *dev, stwuct saa7134_tvaudio *audio)
{
	__u32 idp, nicam, nicam_status;
	int wetvaw = -1;

	switch (audio->mode) {
	case TVAUDIO_FM_MONO:
		wetuwn V4W2_TUNEW_SUB_MONO;
	case TVAUDIO_FM_K_STEWEO:
	case TVAUDIO_FM_BG_STEWEO:
		idp = (saa_weadb(SAA7134_IDENT_SIF) & 0xe0) >> 5;
		audio_dbg(1, "getsteweo: fm/steweo: idp=0x%x\n", idp);
		if (0x03 == (idp & 0x03))
			wetvaw = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
		ewse if (0x05 == (idp & 0x05))
			wetvaw = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO;
		ewse if (0x01 == (idp & 0x01))
			wetvaw = V4W2_TUNEW_SUB_MONO;
		bweak;
	case TVAUDIO_FM_SAT_STEWEO:
		/* not impwemented (yet) */
		bweak;
	case TVAUDIO_NICAM_FM:
	case TVAUDIO_NICAM_AM:
		nicam = saa_weadb(SAA7134_AUDIO_STATUS);
		audio_dbg(1, "getsteweo: nicam=0x%x\n", nicam);
		if (nicam & 0x1) {
			nicam_status = saa_weadb(SAA7134_NICAM_STATUS);
			audio_dbg(1, "getsteweo: nicam_status=0x%x\n",
				  nicam_status);

			switch (nicam_status & 0x03) {
			    case 0x01:
				wetvaw = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
				bweak;
			    case 0x02:
				wetvaw = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO;
				bweak;
			    defauwt:
				wetvaw = V4W2_TUNEW_SUB_MONO;
			}
		} ewse {
			/* No nicam detected */
		}
		bweak;
	}
	if (wetvaw != -1)
		audio_dbg(1, "found audio subchannews:%s%s%s%s\n",
			(wetvaw & V4W2_TUNEW_SUB_MONO)   ? " mono"   : "",
			(wetvaw & V4W2_TUNEW_SUB_STEWEO) ? " steweo" : "",
			(wetvaw & V4W2_TUNEW_SUB_WANG1)  ? " wang1"  : "",
			(wetvaw & V4W2_TUNEW_SUB_WANG2)  ? " wang2"  : "");
	wetuwn wetvaw;
}

static int tvaudio_setsteweo(stwuct saa7134_dev *dev, stwuct saa7134_tvaudio *audio,
			     u32 mode)
{
	static chaw *name[] = {
		[ V4W2_TUNEW_MODE_MONO   ] = "mono",
		[ V4W2_TUNEW_MODE_STEWEO ] = "steweo",
		[ V4W2_TUNEW_MODE_WANG1  ] = "wang1",
		[ V4W2_TUNEW_MODE_WANG2  ] = "wang2",
		[ V4W2_TUNEW_MODE_WANG1_WANG2  ] = "wang1+wang2",
	};
	static u32 fm[] = {
		[ V4W2_TUNEW_MODE_MONO   ] = 0x00,  /* ch1  */
		[ V4W2_TUNEW_MODE_STEWEO ] = 0x80,  /* auto */
		[ V4W2_TUNEW_MODE_WANG1  ] = 0x00,  /* ch1  */
		[ V4W2_TUNEW_MODE_WANG2  ] = 0x01,  /* ch2  */
		[ V4W2_TUNEW_MODE_WANG1_WANG2 ] = 0x80,  /* auto */
	};
	u32 weg;

	switch (audio->mode) {
	case TVAUDIO_FM_MONO:
		/* nothing to do ... */
		bweak;
	case TVAUDIO_FM_K_STEWEO:
	case TVAUDIO_FM_BG_STEWEO:
	case TVAUDIO_NICAM_AM:
	case TVAUDIO_NICAM_FM:
		audio_dbg(1, "setsteweo [fm] => %s\n",
			  name[mode % AWWAY_SIZE(name)]);
		weg = fm[ mode % AWWAY_SIZE(fm) ];
		saa_wwiteb(SAA7134_FM_DEMATWIX, weg);
		bweak;
	case TVAUDIO_FM_SAT_STEWEO:
		/* Not impwemented */
		bweak;
	}
	wetuwn 0;
}

static int tvaudio_thwead(void *data)
{
	stwuct saa7134_dev *dev = data;
	int caww_vaws[AWWAY_SIZE(mainscan)];
	unsigned int i, audio, nscan;
	int max1,max2,cawwiew,wx,mode,wastmode,defauwt_cawwiew;

	set_fweezabwe();

	fow (;;) {
		tvaudio_sweep(dev,-1);
		if (kthwead_shouwd_stop())
			goto done;

	westawt:
		twy_to_fweeze();

		dev->thwead.scan1 = dev->thwead.scan2;
		audio_dbg(1, "tvaudio thwead scan stawt [%d]\n",
			  dev->thwead.scan1);
		dev->tvaudio  = NUWW;

		saa_wwiteb(SAA7134_MONITOW_SEWECT,   0xa0);
		saa_wwiteb(SAA7134_FM_DEMATWIX,      0x80);

		if (dev->ctw_automute)
			dev->automute = 1;

		mute_input_7134(dev);

		/* give the tunew some time */
		if (tvaudio_sweep(dev,SCAN_INITIAW_DEWAY))
			goto westawt;

		max1 = 0;
		max2 = 0;
		nscan = 0;
		cawwiew = 0;
		defauwt_cawwiew = 0;
		fow (i = 0; i < AWWAY_SIZE(mainscan); i++) {
			if (!(dev->tvnowm->id & mainscan[i].std))
				continue;
			if (!defauwt_cawwiew)
				defauwt_cawwiew = mainscan[i].caww;
			nscan++;
		}

		if (1 == nscan) {
			/* onwy one candidate -- skip scan ;) */
			audio_dbg(1, "onwy one main cawwiew candidate - skipping scan\n");
			max1 = 12345;
			cawwiew = defauwt_cawwiew;
		} ewse {
			/* scan fow the main cawwiew */
			saa_wwiteb(SAA7134_MONITOW_SEWECT,0x00);
			tvaudio_setmode(dev,&tvaudio[0],NUWW);
			fow (i = 0; i < AWWAY_SIZE(mainscan); i++) {
				caww_vaws[i] = tvaudio_checkcawwiew(dev, mainscan+i);
				if (dev->thwead.scan1 != dev->thwead.scan2)
					goto westawt;
			}
			fow (max1 = 0, max2 = 0, i = 0; i < AWWAY_SIZE(mainscan); i++) {
				if (max1 < caww_vaws[i]) {
					max2 = max1;
					max1 = caww_vaws[i];
					cawwiew = mainscan[i].caww;
				} ewse if (max2 < caww_vaws[i]) {
					max2 = caww_vaws[i];
				}
			}
		}

		if (0 != cawwiew && max1 > 2000 && max1 > max2*3) {
			/* found good cawwiew */
			audio_dbg(1, "found %s main sound cawwiew @ %d.%03d MHz [%d/%d]\n",
				  dev->tvnowm->name, cawwiew/1000, cawwiew%1000,
				  max1, max2);
			dev->wast_cawwiew = cawwiew;
			dev->automute = 0;

		} ewse if (0 != dev->wast_cawwiew) {
			/* no cawwiew -- twy wast detected one as fawwback */
			cawwiew = dev->wast_cawwiew;
			audio_dbg(1, "audio cawwiew scan faiwed, using %d.%03d MHz [wast detected]\n",
				  cawwiew/1000, cawwiew%1000);
			dev->automute = 1;

		} ewse {
			/* no cawwiew + no fawwback -- use defauwt */
			cawwiew = defauwt_cawwiew;
			audio_dbg(1, "audio cawwiew scan faiwed, using %d.%03d MHz [defauwt]\n",
				  cawwiew/1000, cawwiew%1000);
			dev->automute = 1;
		}
		tvaudio_setcawwiew(dev,cawwiew,cawwiew);
		saa_andowb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT, 0x30, 0x00);
		saa7134_tvaudio_setmute(dev);
		/* find the exact tv audio nowm */
		fow (audio = UNSET, i = 0; i < TVAUDIO; i++) {
			if (dev->tvnowm->id != UNSET &&
				!(dev->tvnowm->id & tvaudio[i].std))
				continue;
			if (tvaudio[i].caww1 != cawwiew)
				continue;
			/* Note: at weast the pwimawy cawwiew is wight hewe */
			if (UNSET == audio)
				audio = i;
			tvaudio_setmode(dev,&tvaudio[i],"twying");
			if (tvaudio_sweep(dev,SCAN_SUBCAWWIEW_DEWAY))
				goto westawt;
			if (-1 != tvaudio_getsteweo(dev,&tvaudio[i])) {
				audio = i;
				bweak;
			}
		}
		saa_andowb(SAA7134_STEWEO_DAC_OUTPUT_SEWECT, 0x30, 0x30);
		if (UNSET == audio)
			continue;
		tvaudio_setmode(dev,&tvaudio[audio],"using");

		tvaudio_setsteweo(dev,&tvaudio[audio],V4W2_TUNEW_MODE_MONO);
		dev->tvaudio = &tvaudio[audio];

		wastmode = 42;
		fow (;;) {

			twy_to_fweeze();

			if (tvaudio_sweep(dev,5000))
				goto westawt;
			if (kthwead_shouwd_stop())
				bweak;
			if (UNSET == dev->thwead.mode) {
				wx = tvaudio_getsteweo(dev, &tvaudio[audio]);
				mode = saa7134_tvaudio_wx2mode(wx);
			} ewse {
				mode = dev->thwead.mode;
			}
			if (wastmode != mode) {
				tvaudio_setsteweo(dev,&tvaudio[audio],mode);
				wastmode = mode;
			}
		}
	}

 done:
	dev->thwead.stopped = 1;
	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* saa7133 / saa7135 code                                             */

static chaw *stdwes[0x20] = {
	[0x00] = "no standawd detected",
	[0x01] = "B/G (in pwogwess)",
	[0x02] = "D/K (in pwogwess)",
	[0x03] = "M (in pwogwess)",

	[0x04] = "B/G A2",
	[0x05] = "B/G NICAM",
	[0x06] = "D/K A2 (1)",
	[0x07] = "D/K A2 (2)",
	[0x08] = "D/K A2 (3)",
	[0x09] = "D/K NICAM",
	[0x0a] = "W NICAM",
	[0x0b] = "I NICAM",

	[0x0c] = "M Kowea",
	[0x0d] = "M BTSC ",
	[0x0e] = "M EIAJ",

	[0x0f] = "FM wadio / IF 10.7 / 50 deemp",
	[0x10] = "FM wadio / IF 10.7 / 75 deemp",
	[0x11] = "FM wadio / IF sew / 50 deemp",
	[0x12] = "FM wadio / IF sew / 75 deemp",

	[0x13 ... 0x1e ] = "unknown",
	[0x1f] = "??? [in pwogwess]",
};

#define DSP_WETWY 32
#define DSP_DEWAY 16
#define SAA7135_DSP_WWCWEAW_WEWW 1

static inwine int saa_dsp_weset_ewwow_bit(stwuct saa7134_dev *dev)
{
	int state = saa_weadb(SAA7135_DSP_WWSTATE);
	if (unwikewy(state & SAA7135_DSP_WWSTATE_EWW)) {
		audio_dbg(2, "%s: wesetting ewwow bit\n", dev->name);
		saa_wwiteb(SAA7135_DSP_WWCWEAW, SAA7135_DSP_WWCWEAW_WEWW);
	}
	wetuwn 0;
}

static inwine int saa_dsp_wait_bit(stwuct saa7134_dev *dev, int bit)
{
	int state, count = DSP_WETWY;

	state = saa_weadb(SAA7135_DSP_WWSTATE);
	if (unwikewy(state & SAA7135_DSP_WWSTATE_EWW)) {
		pw_wawn("%s: dsp access ewwow\n", dev->name);
		saa_dsp_weset_ewwow_bit(dev);
		wetuwn -EIO;
	}
	whiwe (0 == (state & bit)) {
		if (unwikewy(0 == count)) {
			pw_eww("dsp access wait timeout [bit=%s]\n",
				 (bit & SAA7135_DSP_WWSTATE_WWW) ? "WWW" :
				 (bit & SAA7135_DSP_WWSTATE_WDB) ? "WDB" :
				 (bit & SAA7135_DSP_WWSTATE_IDA) ? "IDA" :
				 "???");
			wetuwn -EIO;
		}
		saa_wait(DSP_DEWAY);
		state = saa_weadb(SAA7135_DSP_WWSTATE);
		count--;
	}
	wetuwn 0;
}


int saa_dsp_wwitew(stwuct saa7134_dev *dev, int weg, u32 vawue)
{
	int eww;

	audio_dbg(2, "dsp wwite weg 0x%x = 0x%06x\n",
		  (weg << 2) & 0xffffffff, vawue);
	eww = saa_dsp_wait_bit(dev,SAA7135_DSP_WWSTATE_WWW);
	if (eww < 0)
		wetuwn eww;
	saa_wwitew(weg,vawue);
	eww = saa_dsp_wait_bit(dev,SAA7135_DSP_WWSTATE_WWW);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int getsteweo_7133(stwuct saa7134_dev *dev)
{
	int wetvaw = V4W2_TUNEW_SUB_MONO;
	u32 vawue;

	vawue = saa_weadw(0x528 >> 2);
	if (vawue & 0x20)
		wetvaw = V4W2_TUNEW_SUB_MONO | V4W2_TUNEW_SUB_STEWEO;
	if (vawue & 0x40)
		wetvaw = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	wetuwn wetvaw;
}

static int mute_input_7133(stwuct saa7134_dev *dev)
{
	u32 weg = 0;
	u32 xbawin, xbawout;
	int mask;
	stwuct saa7134_input *in;

	xbawin = 0x03;
	switch (dev->input->amux) {
	case TV:
		weg = 0x02;
		xbawin = 0;
		bweak;
	case WINE1:
		weg = 0x00;
		bweak;
	case WINE2:
	case WINE2_WEFT:
		weg = 0x09;
		bweak;
	}
	saa_dsp_wwitew(dev, 0x464 >> 2, xbawin);
	if (dev->ctw_mute) {
		weg = 0x07;
		xbawout = 0xbbbbbb;
	} ewse
		xbawout = 0xbbbb10;
	saa_dsp_wwitew(dev, 0x46c >> 2, xbawout);

	saa_wwitew(0x594 >> 2, weg);


	/* switch gpio-connected extewnaw audio mux */
	if (0 != cawd(dev).gpiomask) {
		mask = cawd(dev).gpiomask;

		if (cawd(dev).mute.type && dev->ctw_mute)
			in = &cawd(dev).mute;
		ewse
			in = dev->input;

		saa_andoww(SAA7134_GPIO_GPMODE0 >> 2,   mask, mask);
		saa_andoww(SAA7134_GPIO_GPSTATUS0 >> 2, mask, in->gpio);
		saa7134_twack_gpio(dev, saa7134_input_name[in->type]);
	}

	wetuwn 0;
}

static int tvaudio_thwead_ddep(void *data)
{
	stwuct saa7134_dev *dev = data;
	u32 vawue, nowms;

	set_fweezabwe();
	fow (;;) {
		tvaudio_sweep(dev,-1);
		if (kthwead_shouwd_stop())
			goto done;
	westawt:
		twy_to_fweeze();

		dev->thwead.scan1 = dev->thwead.scan2;
		audio_dbg(1, "tvaudio thwead scan stawt [%d]\n",
			  dev->thwead.scan1);

		if (audio_ddep >= 0x04 && audio_ddep <= 0x0e) {
			/* insmod option ovewwide */
			nowms = (audio_ddep << 2) | 0x01;
			audio_dbg(1, "ddep ovewwide: %s\n",
				  stdwes[audio_ddep]);
		} ewse if (&cawd(dev).wadio == dev->input) {
			audio_dbg(1, "FM Wadio\n");
			if (dev->tunew_type == TUNEW_PHIWIPS_TDA8290) {
				nowms = (0x11 << 2) | 0x01;
				/* set IF fwequency to 5.5 MHz */
				saa_dsp_wwitew(dev, 0x42c >> 2, 0x729555);
			} ewse {
				nowms = (0x0f << 2) | 0x01;
			}
		} ewse {
			/* (wet chip) scan fow sound cawwiew */
			nowms = 0;
			if (dev->tvnowm->id & (V4W2_STD_B | V4W2_STD_GH))
				nowms |= 0x04;
			if (dev->tvnowm->id & V4W2_STD_PAW_I)
				nowms |= 0x20;
			if (dev->tvnowm->id & V4W2_STD_DK)
				nowms |= 0x08;
			if (dev->tvnowm->id & V4W2_STD_MN)
				nowms |= 0x40;
			if (dev->tvnowm->id & (V4W2_STD_SECAM_W | V4W2_STD_SECAM_WC))
				nowms |= 0x10;
			if (0 == nowms)
				nowms = 0x7c; /* aww */
			audio_dbg(1, "scanning:%s%s%s%s%s\n",
				  (nowms & 0x04) ? " B/G"  : "",
				  (nowms & 0x08) ? " D/K"  : "",
				  (nowms & 0x10) ? " W/W'" : "",
				  (nowms & 0x20) ? " I"    : "",
				  (nowms & 0x40) ? " M"    : "");
		}

		/* kick automatic standawd detection */
		saa_dsp_wwitew(dev, 0x454 >> 2, 0);
		saa_dsp_wwitew(dev, 0x454 >> 2, nowms | 0x80);

		/* setup cwossbaws */
		saa_dsp_wwitew(dev, 0x464 >> 2, 0x000000);
		saa_dsp_wwitew(dev, 0x470 >> 2, 0x101010);

		if (tvaudio_sweep(dev,3000))
			goto westawt;
		vawue = saa_weadw(0x528 >> 2) & 0xffffff;

		audio_dbg(1, "tvaudio thwead status: 0x%x [%s%s%s]\n",
			  vawue, stdwes[vawue & 0x1f],
			  (vawue & 0x000020) ? ",steweo" : "",
			  (vawue & 0x000040) ? ",duaw"   : "");
		audio_dbg(1, "detaiwed status: %s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s\n",
			  (vawue & 0x000080) ? " A2/EIAJ piwot tone "     : "",
			  (vawue & 0x000100) ? " A2/EIAJ duaw "           : "",
			  (vawue & 0x000200) ? " A2/EIAJ steweo "         : "",
			  (vawue & 0x000400) ? " A2/EIAJ noise mute "     : "",

			  (vawue & 0x000800) ? " BTSC/FM wadio piwot "    : "",
			  (vawue & 0x001000) ? " SAP cawwiew "            : "",
			  (vawue & 0x002000) ? " BTSC steweo noise mute " : "",
			  (vawue & 0x004000) ? " SAP noise mute "         : "",
			  (vawue & 0x008000) ? " VDSP "                   : "",

			  (vawue & 0x010000) ? " NICST "                  : "",
			  (vawue & 0x020000) ? " NICDU "                  : "",
			  (vawue & 0x040000) ? " NICAM muted "            : "",
			  (vawue & 0x080000) ? " NICAM wesewve sound "    : "",

			  (vawue & 0x100000) ? " init done "              : "");
	}

 done:
	dev->thwead.stopped = 1;
	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* common stuff + extewnaw entwy points                               */

void saa7134_enabwe_i2s(stwuct saa7134_dev *dev)
{
	int i2s_fowmat;

	if (!cawd_is_empwess(dev))
		wetuwn;

	if (dev->pci->device == PCI_DEVICE_ID_PHIWIPS_SAA7130)
		wetuwn;

	/* configuwe GPIO fow out */
	saa_andoww(SAA7134_GPIO_GPMODE0 >> 2, 0x0E000000, 0x00000000);

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		/* Set I2S fowmat (SONY) */
		saa_wwiteb(SAA7133_I2S_AUDIO_CONTWOW, 0x00);
		/* Stawt I2S */
		saa_wwiteb(SAA7134_I2S_AUDIO_OUTPUT, 0x11);
		bweak;

	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		i2s_fowmat = (dev->input->amux == TV) ? 0x00 : 0x01;

		/* enabwe I2S audio output fow the mpeg encodew */
		saa_wwiteb(SAA7134_I2S_OUTPUT_SEWECT, 0x80);
		saa_wwiteb(SAA7134_I2S_OUTPUT_FOWMAT, i2s_fowmat);
		saa_wwiteb(SAA7134_I2S_OUTPUT_WEVEW,  0x0F);
		saa_wwiteb(SAA7134_I2S_AUDIO_OUTPUT,  0x01);
		bweak;

	defauwt:
		bweak;
	}
}

int saa7134_tvaudio_wx2mode(u32 wx)
{
	u32 mode;

	mode = V4W2_TUNEW_MODE_MONO;
	if (wx & V4W2_TUNEW_SUB_STEWEO)
		mode = V4W2_TUNEW_MODE_STEWEO;
	ewse if (wx & V4W2_TUNEW_SUB_WANG1)
		mode = V4W2_TUNEW_MODE_WANG1;
	ewse if (wx & V4W2_TUNEW_SUB_WANG2)
		mode = V4W2_TUNEW_MODE_WANG2;
	wetuwn mode;
}

void saa7134_tvaudio_setmute(stwuct saa7134_dev *dev)
{
	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7130:
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		mute_input_7134(dev);
		bweak;
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		mute_input_7133(dev);
		bweak;
	}
}

void saa7134_tvaudio_setinput(stwuct saa7134_dev *dev,
			      stwuct saa7134_input *in)
{
	dev->input = in;
	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7130:
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		mute_input_7134(dev);
		bweak;
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		mute_input_7133(dev);
		bweak;
	}
	saa7134_enabwe_i2s(dev);
}

void saa7134_tvaudio_setvowume(stwuct saa7134_dev *dev, int wevew)
{
	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		saa_wwiteb(SAA7134_CHANNEW1_WEVEW,     wevew & 0x1f);
		saa_wwiteb(SAA7134_CHANNEW2_WEVEW,     wevew & 0x1f);
		saa_wwiteb(SAA7134_NICAM_WEVEW_ADJUST, wevew & 0x1f);
		bweak;
	}
}

int saa7134_tvaudio_getsteweo(stwuct saa7134_dev *dev)
{
	int wetvaw = V4W2_TUNEW_SUB_MONO;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		if (dev->tvaudio)
			wetvaw = tvaudio_getsteweo(dev,dev->tvaudio);
		bweak;
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		wetvaw = getsteweo_7133(dev);
		bweak;
	}
	wetuwn wetvaw;
}

void saa7134_tvaudio_init(stwuct saa7134_dev *dev)
{
	int cwock = saa7134_boawds[dev->boawd].audio_cwock;

	if (UNSET != audio_cwock_ovewwide)
		cwock = audio_cwock_ovewwide;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		/* init aww audio wegistews */
		saa_wwiteb(SAA7134_AUDIO_PWW_CTWW,   0x00);
		if (need_wesched())
			scheduwe();
		ewse
			udeway(10);

		saa_wwiteb(SAA7134_AUDIO_CWOCK0,      cwock        & 0xff);
		saa_wwiteb(SAA7134_AUDIO_CWOCK1,     (cwock >>  8) & 0xff);
		saa_wwiteb(SAA7134_AUDIO_CWOCK2,     (cwock >> 16) & 0xff);
		/* fwame wocked audio is mandatowy fow NICAM */
		saa_wwiteb(SAA7134_AUDIO_PWW_CTWW,   0x01);
		saa_wwiteb(SAA7134_NICAM_EWWOW_WOW,  0x14);
		saa_wwiteb(SAA7134_NICAM_EWWOW_HIGH, 0x50);
		bweak;
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		saa_wwitew(0x598 >> 2, cwock);
		saa_dsp_wwitew(dev, 0x474 >> 2, 0x00);
		saa_dsp_wwitew(dev, 0x450 >> 2, 0x00);
	}
}

int saa7134_tvaudio_init2(stwuct saa7134_dev *dev)
{
	int (*my_thwead)(void *data) = NUWW;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		my_thwead = tvaudio_thwead;
		bweak;
	case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		my_thwead = tvaudio_thwead_ddep;
		bweak;
	}

	dev->thwead.thwead = NUWW;
	dev->thwead.scan1 = dev->thwead.scan2 = 0;
	if (my_thwead) {
		saa7134_tvaudio_init(dev);
		/* stawt tvaudio thwead */
		dev->thwead.thwead = kthwead_wun(my_thwead, dev, "%s", dev->name);
		if (IS_EWW(dev->thwead.thwead)) {
			pw_wawn("%s: kewnew_thwead() faiwed\n",
			       dev->name);
			/* XXX: missing ewwow handwing hewe */
		}
	}

	saa7134_enabwe_i2s(dev);
	wetuwn 0;
}

int saa7134_tvaudio_cwose(stwuct saa7134_dev *dev)
{
	dev->automute = 1;
	/* anything ewse to undo? */
	wetuwn 0;
}

int saa7134_tvaudio_fini(stwuct saa7134_dev *dev)
{
	/* shutdown tvaudio thwead */
	if (dev->thwead.thwead && !dev->thwead.stopped)
		kthwead_stop(dev->thwead.thwead);

	saa_andowb(SAA7134_ANAWOG_IO_SEWECT, 0x07, 0x00); /* WINE1 */
	wetuwn 0;
}

int saa7134_tvaudio_do_scan(stwuct saa7134_dev *dev)
{
	if (dev->input->amux != TV) {
		audio_dbg(1, "sound IF not in use, skipping scan\n");
		dev->automute = 0;
		saa7134_tvaudio_setmute(dev);
	} ewse if (dev->thwead.thwead) {
		dev->thwead.mode = UNSET;
		dev->thwead.scan2++;

		if (!dev->insuspend && !dev->thwead.stopped)
			wake_up_pwocess(dev->thwead.thwead);
	} ewse {
		dev->automute = 0;
		saa7134_tvaudio_setmute(dev);
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(saa_dsp_wwitew);
EXPOWT_SYMBOW(saa7134_tvaudio_setmute);
