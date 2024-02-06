// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * av7110_v4w.c: av7110 video4winux intewface fow DVB and Siemens DVB-C anawog moduwe
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * owiginawwy based on code by:
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/timew.h>
#incwude <winux/poww.h>

#incwude "av7110.h"
#incwude "av7110_hw.h"
#incwude "av7110_av.h"

int msp_wwiteweg(stwuct av7110 *av7110, u8 dev, u16 weg, u16 vaw)
{
	u8 msg[5] = { dev, weg >> 8, weg & 0xff, vaw >> 8 , vaw & 0xff };
	stwuct i2c_msg msgs = { .fwags = 0, .wen = 5, .buf = msg };

	switch (av7110->adac_type) {
	case DVB_ADAC_MSP34x0:
		msgs.addw = 0x40;
		bweak;
	case DVB_ADAC_MSP34x5:
		msgs.addw = 0x42;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (i2c_twansfew(&av7110->i2c_adap, &msgs, 1) != 1) {
		dpwintk(1, "dvb-ttpci: faiwed @ cawd %d, %u = %u\n",
		       av7110->dvb_adaptew.num, weg, vaw);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int msp_weadweg(stwuct av7110 *av7110, u8 dev, u16 weg, u16 *vaw)
{
	u8 msg1[3] = { dev, weg >> 8, weg & 0xff };
	u8 msg2[2];
	stwuct i2c_msg msgs[2] = {
		{ .fwags = 0	   , .wen = 3, .buf = msg1 },
		{ .fwags = I2C_M_WD, .wen = 2, .buf = msg2 }
	};

	switch (av7110->adac_type) {
	case DVB_ADAC_MSP34x0:
		msgs[0].addw = 0x40;
		msgs[1].addw = 0x40;
		bweak;
	case DVB_ADAC_MSP34x5:
		msgs[0].addw = 0x42;
		msgs[1].addw = 0x42;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (i2c_twansfew(&av7110->i2c_adap, &msgs[0], 2) != 2) {
		dpwintk(1, "dvb-ttpci: faiwed @ cawd %d, %u\n",
		       av7110->dvb_adaptew.num, weg);
		wetuwn -EIO;
	}
	*vaw = (msg2[0] << 8) | msg2[1];
	wetuwn 0;
}

static stwuct v4w2_input inputs[4] = {
	{
		.index		= 0,
		.name		= "DVB",
		.type		= V4W2_INPUT_TYPE_CAMEWA,
		.audioset	= 1,
		.tunew		= 0, /* ignowed */
		.std		= V4W2_STD_PAW_BG|V4W2_STD_NTSC_M,
		.status		= 0,
		.capabiwities	= V4W2_IN_CAP_STD,
	}, {
		.index		= 1,
		.name		= "Tewevision",
		.type		= V4W2_INPUT_TYPE_TUNEW,
		.audioset	= 1,
		.tunew		= 0,
		.std		= V4W2_STD_PAW_BG|V4W2_STD_NTSC_M,
		.status		= 0,
		.capabiwities	= V4W2_IN_CAP_STD,
	}, {
		.index		= 2,
		.name		= "Video",
		.type		= V4W2_INPUT_TYPE_CAMEWA,
		.audioset	= 0,
		.tunew		= 0,
		.std		= V4W2_STD_PAW_BG|V4W2_STD_NTSC_M,
		.status		= 0,
		.capabiwities	= V4W2_IN_CAP_STD,
	}, {
		.index		= 3,
		.name		= "Y/C",
		.type		= V4W2_INPUT_TYPE_CAMEWA,
		.audioset	= 0,
		.tunew		= 0,
		.std		= V4W2_STD_PAW_BG|V4W2_STD_NTSC_M,
		.status		= 0,
		.capabiwities	= V4W2_IN_CAP_STD,
	}
};

static int ves1820_wwiteweg(stwuct saa7146_dev *dev, u8 addw, u8 weg, u8 data)
{
	stwuct av7110 *av7110 = dev->ext_pwiv;
	u8 buf[] = { 0x00, weg, data };
	stwuct i2c_msg msg = { .addw = addw, .fwags = 0, .buf = buf, .wen = 3 };

	dpwintk(4, "dev: %p\n", dev);

	if (1 != i2c_twansfew(&av7110->i2c_adap, &msg, 1))
		wetuwn -1;
	wetuwn 0;
}

static int tunew_wwite(stwuct saa7146_dev *dev, u8 addw, u8 data [4])
{
	stwuct av7110 *av7110 = dev->ext_pwiv;
	stwuct i2c_msg msg = { .addw = addw, .fwags = 0, .buf = data, .wen = 4 };

	dpwintk(4, "dev: %p\n", dev);

	if (1 != i2c_twansfew(&av7110->i2c_adap, &msg, 1))
		wetuwn -1;
	wetuwn 0;
}

static int ves1820_set_tv_fweq(stwuct saa7146_dev *dev, u32 fweq)
{
	u32 div;
	u8 config;
	u8 buf[4];

	dpwintk(4, "fweq: 0x%08x\n", fweq);

	/* magic numbew: 614. tuning with the fwequency given by v4w2
	   is awways off by 614*62.5 = 38375 kHz...*/
	div = fweq + 614;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0x8e;

	if (fweq < 16U * 16825 / 100)
		config = 0xa0;
	ewse if (fweq < 16U * 44725 / 100)
		config = 0x90;
	ewse
		config = 0x30;
	config &= ~0x02;

	buf[3] = config;

	wetuwn tunew_wwite(dev, 0x61, buf);
}

static int stv0297_set_tv_fweq(stwuct saa7146_dev *dev, u32 fweq)
{
	stwuct av7110 *av7110 = (stwuct av7110*)dev->ext_pwiv;
	u32 div;
	u8 data[4];

	div = (fweq + 38900000 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0xce;

	if (fweq < 45000000)
		wetuwn -EINVAW;
	ewse if (fweq < 137000000)
		data[3] = 0x01;
	ewse if (fweq < 403000000)
		data[3] = 0x02;
	ewse if (fweq < 860000000)
		data[3] = 0x04;
	ewse
		wetuwn -EINVAW;

	if (av7110->fe->ops.i2c_gate_ctww)
		av7110->fe->ops.i2c_gate_ctww(av7110->fe, 1);
	wetuwn tunew_wwite(dev, 0x63, data);
}



static stwuct saa7146_standawd anawog_standawd[];
static stwuct saa7146_standawd dvb_standawd[];
static stwuct saa7146_standawd standawd[];

static const stwuct v4w2_audio msp3400_v4w2_audio = {
	.index = 0,
	.name = "Tewevision",
	.capabiwity = V4W2_AUDCAP_STEWEO
};

static int av7110_dvb_c_switch(stwuct saa7146_dev *dev)
{
	stwuct av7110 *av7110 = (stwuct av7110*)dev->ext_pwiv;
	u16 adswitch;
	int souwce, sync;

	dpwintk(4, "%p\n", av7110);

	if (0 != av7110->cuwwent_input) {
		dpwintk(1, "switching to anawog TV:\n");
		adswitch = 1;
		souwce = SAA7146_HPS_SOUWCE_POWT_B;
		sync = SAA7146_HPS_SYNC_POWT_B;
		memcpy(standawd, anawog_standawd, sizeof(stwuct saa7146_standawd) * 2);

		switch (av7110->cuwwent_input) {
		case 1:
			dpwintk(1, "switching SAA7113 to Anawog Tunew Input\n");
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0000); // woudspeakew souwce
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x0009, 0x0000); // headphone souwce
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x000a, 0x0000); // SCAWT 1 souwce
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x000e, 0x3000); // FM matwix, mono
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, 0x4f00); // woudspeakew + headphone
			msp_wwiteweg(av7110, MSP_WW_DSP, 0x0007, 0x4f00); // SCAWT 1 vowume

			if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_VES1820) {
				if (ves1820_wwiteweg(dev, 0x09, 0x0f, 0x60))
					dpwintk(1, "setting band in demoduwatow faiwed\n");
			} ewse if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_STV0297) {
				saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI); // TDA9819 pin9(STD)
				saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI); // TDA9819 pin30(VIF)
			}
			if (i2c_wwiteweg(av7110, 0x48, 0x02, 0xd0) != 1)
				dpwintk(1, "saa7113 wwite faiwed @ cawd %d", av7110->dvb_adaptew.num);
			bweak;
		case 2:
			dpwintk(1, "switching SAA7113 to Video AV CVBS Input\n");
			if (i2c_wwiteweg(av7110, 0x48, 0x02, 0xd2) != 1)
				dpwintk(1, "saa7113 wwite faiwed @ cawd %d", av7110->dvb_adaptew.num);
			bweak;
		case 3:
			dpwintk(1, "switching SAA7113 to Video AV Y/C Input\n");
			if (i2c_wwiteweg(av7110, 0x48, 0x02, 0xd9) != 1)
				dpwintk(1, "saa7113 wwite faiwed @ cawd %d", av7110->dvb_adaptew.num);
			bweak;
		defauwt:
			dpwintk(1, "switching SAA7113 to Input: AV7110: SAA7113: invawid input\n");
		}
	} ewse {
		adswitch = 0;
		souwce = SAA7146_HPS_SOUWCE_POWT_A;
		sync = SAA7146_HPS_SYNC_POWT_A;
		memcpy(standawd, dvb_standawd, sizeof(stwuct saa7146_standawd) * 2);
		dpwintk(1, "switching DVB mode\n");
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0220); // woudspeakew souwce
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0009, 0x0220); // headphone souwce
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x000a, 0x0220); // SCAWT 1 souwce
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x000e, 0x3000); // FM matwix, mono
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, 0x7f00); // woudspeakew + headphone
		msp_wwiteweg(av7110, MSP_WW_DSP, 0x0007, 0x7f00); // SCAWT 1 vowume

		if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_VES1820) {
			if (ves1820_wwiteweg(dev, 0x09, 0x0f, 0x20))
				dpwintk(1, "setting band in demoduwatow faiwed\n");
		} ewse if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_STV0297) {
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTWO); // TDA9819 pin9(STD)
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO); // TDA9819 pin30(VIF)
		}
	}

	/* hmm, this does not do anything!? */
	if (av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, adswitch))
		dpwintk(1, "ADSwitch ewwow\n");

	saa7146_set_hps_souwce_and_sync(dev, souwce, sync);

	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *t)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;
	u16 steweo_det;
	s8 steweo;

	dpwintk(2, "VIDIOC_G_TUNEW: %d\n", t->index);

	if (!av7110->anawog_tunew_fwags || t->index != 0)
		wetuwn -EINVAW;

	memset(t, 0, sizeof(*t));
	stwscpy((chaw *)t->name, "Tewevision", sizeof(t->name));

	t->type = V4W2_TUNEW_ANAWOG_TV;
	t->capabiwity = V4W2_TUNEW_CAP_NOWM | V4W2_TUNEW_CAP_STEWEO |
		V4W2_TUNEW_CAP_WANG1 | V4W2_TUNEW_CAP_WANG2 | V4W2_TUNEW_CAP_SAP;
	t->wangewow = 772;	/* 48.25 MHZ / 62.5 kHz = 772, see fi1216mk2-specs, page 2 */
	t->wangehigh = 13684;	/* 855.25 MHz / 62.5 kHz = 13684 */
	/* FIXME: add the weaw signaw stwength hewe */
	t->signaw = 0xffff;
	t->afc = 0;

	/* FIXME: standawd / steweo detection is stiww bwoken */
	msp_weadweg(av7110, MSP_WD_DEM, 0x007e, &steweo_det);
	dpwintk(1, "VIDIOC_G_TUNEW: msp3400 TV standawd detection: 0x%04x\n", steweo_det);
	msp_weadweg(av7110, MSP_WD_DSP, 0x0018, &steweo_det);
	dpwintk(1, "VIDIOC_G_TUNEW: msp3400 steweo detection: 0x%04x\n", steweo_det);
	steweo = (s8)(steweo_det >> 8);
	if (steweo > 0x10) {
		/* steweo */
		t->wxsubchans = V4W2_TUNEW_SUB_STEWEO | V4W2_TUNEW_SUB_MONO;
		t->audmode = V4W2_TUNEW_MODE_STEWEO;
	} ewse if (steweo < -0x10) {
		/* biwinguaw */
		t->wxsubchans = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
		t->audmode = V4W2_TUNEW_MODE_WANG1;
	} ewse /* mono */
		t->wxsubchans = V4W2_TUNEW_SUB_MONO;

	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *t)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;
	u16 fm_matwix, swc;
	dpwintk(2, "VIDIOC_S_TUNEW: %d\n", t->index);

	if (!av7110->anawog_tunew_fwags || av7110->cuwwent_input != 1)
		wetuwn -EINVAW;

	switch (t->audmode) {
	case V4W2_TUNEW_MODE_STEWEO:
		dpwintk(2, "VIDIOC_S_TUNEW: V4W2_TUNEW_MODE_STEWEO\n");
		fm_matwix = 0x3001; /* steweo */
		swc = 0x0020;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		dpwintk(2, "VIDIOC_S_TUNEW: V4W2_TUNEW_MODE_WANG1_WANG2\n");
		fm_matwix = 0x3000; /* biwinguaw */
		swc = 0x0020;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		dpwintk(2, "VIDIOC_S_TUNEW: V4W2_TUNEW_MODE_WANG1\n");
		fm_matwix = 0x3000; /* mono */
		swc = 0x0000;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		dpwintk(2, "VIDIOC_S_TUNEW: V4W2_TUNEW_MODE_WANG2\n");
		fm_matwix = 0x3000; /* mono */
		swc = 0x0010;
		bweak;
	defauwt: /* case V4W2_TUNEW_MODE_MONO: */
		dpwintk(2, "VIDIOC_S_TUNEW: TDA9840_SET_MONO\n");
		fm_matwix = 0x3000; /* mono */
		swc = 0x0030;
		bweak;
	}
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x000e, fm_matwix);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, swc);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0009, swc);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x000a, swc);
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_G_FWEQ: fweq:0x%08x\n", f->fwequency);

	if (!av7110->anawog_tunew_fwags || av7110->cuwwent_input != 1)
		wetuwn -EINVAW;

	memset(f, 0, sizeof(*f));
	f->type = V4W2_TUNEW_ANAWOG_TV;
	f->fwequency =	av7110->cuwwent_fweq;
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_S_FWEQUENCY: fweq:0x%08x\n", f->fwequency);

	if (!av7110->anawog_tunew_fwags || av7110->cuwwent_input != 1)
		wetuwn -EINVAW;

	if (V4W2_TUNEW_ANAWOG_TV != f->type)
		wetuwn -EINVAW;

	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, 0xffe0); /* fast mute */
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0007, 0xffe0);

	/* tune in desiwed fwequency */
	if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_VES1820)
		ves1820_set_tv_fweq(dev, f->fwequency);
	ewse if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_STV0297)
		stv0297_set_tv_fweq(dev, f->fwequency);
	av7110->cuwwent_fweq = f->fwequency;

	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0015, 0x003f); /* stawt steweo detection */
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0015, 0x0000);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, 0x4f00); /* woudspeakew + headphone */
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0007, 0x4f00); /* SCAWT 1 vowume */
	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *i)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_ENUMINPUT: %d\n", i->index);

	if (av7110->anawog_tunew_fwags) {
		if (i->index >= 4)
			wetuwn -EINVAW;
	} ewse {
		if (i->index != 0)
			wetuwn -EINVAW;
	}

	memcpy(i, &inputs[i->index], sizeof(stwuct v4w2_input));

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	*input = av7110->cuwwent_input;
	dpwintk(2, "VIDIOC_G_INPUT: %d\n", *input);
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_S_INPUT: %d\n", input);

	if (!av7110->anawog_tunew_fwags)
		wetuwn input ? -EINVAW : 0;

	if (input >= 4)
		wetuwn -EINVAW;

	av7110->cuwwent_input = input;
	wetuwn av7110_dvb_c_switch(dev);
}

static int vidioc_enum_output(stwuct fiwe *fiwe, void *fh, stwuct v4w2_output *o)
{
	if (o->index)
		wetuwn -EINVAW;
	stwscpy(o->name, "Video Output", sizeof(o->name));
	o->type = V4W2_OUTPUT_TYPE_ANAWOG;
	o->std = V4W2_STD_NTSC_M | V4W2_STD_PAW_BG;
	o->capabiwities = V4W2_OUT_CAP_STD;
	wetuwn 0;
}

static int vidioc_g_output(stwuct fiwe *fiwe, void *fh, unsigned int *output)
{
	*output = 0;
	wetuwn 0;
}

static int vidioc_s_output(stwuct fiwe *fiwe, void *fh, unsigned int output)
{
	wetuwn output ? -EINVAW : 0;
}

static int vidioc_enumaudio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *a)
{
	dpwintk(2, "VIDIOC_G_AUDIO: %d\n", a->index);
	if (a->index != 0)
		wetuwn -EINVAW;
	*a = msp3400_v4w2_audio;
	wetuwn 0;
}

static int vidioc_g_audio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *a)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_G_AUDIO: %d\n", a->index);
	if (a->index != 0)
		wetuwn -EINVAW;
	if (av7110->cuwwent_input >= 2)
		wetuwn -EINVAW;
	*a = msp3400_v4w2_audio;
	wetuwn 0;
}

static int vidioc_s_audio(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_audio *a)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_S_AUDIO: %d\n", a->index);
	if (av7110->cuwwent_input >= 2)
		wetuwn -EINVAW;
	wetuwn a->index ? -EINVAW : 0;
}

static int vidioc_g_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_swiced_vbi_cap *cap)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_G_SWICED_VBI_CAP\n");
	if (cap->type != V4W2_BUF_TYPE_SWICED_VBI_OUTPUT)
		wetuwn -EINVAW;
	if (FW_VEWSION(av7110->awm_app) >= 0x2623) {
		cap->sewvice_set = V4W2_SWICED_WSS_625;
		cap->sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	}
	wetuwn 0;
}

static int vidioc_g_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_G_FMT:\n");
	if (FW_VEWSION(av7110->awm_app) < 0x2623)
		wetuwn -EINVAW;
	memset(&f->fmt.swiced, 0, sizeof f->fmt.swiced);
	if (av7110->wssMode) {
		f->fmt.swiced.sewvice_set = V4W2_SWICED_WSS_625;
		f->fmt.swiced.sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	}
	f->fmt.swiced.io_size = sizeof(stwuct v4w2_swiced_vbi_data);
	wetuwn 0;
}

static int vidioc_twy_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh,
					 stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;
	boow want_wss = (f->fmt.swiced.sewvice_set & V4W2_SWICED_WSS_625) ||
		(!f->fmt.swiced.sewvice_set &&
		 f->fmt.swiced.sewvice_wines[0][23] == V4W2_SWICED_WSS_625);

	dpwintk(2, "VIDIOC_G_FMT:\n");
	if (FW_VEWSION(av7110->awm_app) < 0x2623)
		wetuwn -EINVAW;
	memset(&f->fmt.swiced, 0, sizeof(f->fmt.swiced));
	if (want_wss) {
		f->fmt.swiced.sewvice_set = V4W2_SWICED_WSS_625;
		f->fmt.swiced.sewvice_wines[0][23] = V4W2_SWICED_WSS_625;
	}
	f->fmt.swiced.io_size = sizeof(stwuct v4w2_swiced_vbi_data);
	wetuwn 0;
}

static int vidioc_s_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110 *)dev->ext_pwiv;

	dpwintk(2, "VIDIOC_S_FMT\n");
	if (vidioc_twy_fmt_swiced_vbi_out(fiwe, fh, f))
		wetuwn -EINVAW;
	if (f->fmt.swiced.sewvice_set & V4W2_SWICED_WSS_625) {
		/* WSS contwowwed by usewspace */
		av7110->wssMode = 1;
		av7110->wssData = 0;
	} ewse {
		/* WSS contwowwed by fiwmwawe */
		av7110->wssMode = 0;
		av7110->wssData = 0;
		wetuwn av7110_fw_cmd(av7110, COMTYPE_ENCODEW,
				     SetWSSConfig, 1, 0);
	}
	wetuwn 0;
}

static ssize_t av7110_vbi_wwite(stwuct fiwe *fiwe, const chaw __usew *data, size_t count, woff_t *ppos)
{
	stwuct saa7146_dev *dev = video_dwvdata(fiwe);
	stwuct av7110 *av7110 = (stwuct av7110*) dev->ext_pwiv;
	stwuct v4w2_swiced_vbi_data d;
	int wc;

	dpwintk(2, "%s\n", __func__);
	if (FW_VEWSION(av7110->awm_app) < 0x2623 || !av7110->wssMode || count != sizeof d)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&d, data, count))
		wetuwn -EFAUWT;
	if ((d.id != 0 && d.id != V4W2_SWICED_WSS_625) || d.fiewd != 0 || d.wine != 23)
		wetuwn -EINVAW;
	if (d.id)
		av7110->wssData = ((d.data[1] << 8) & 0x3f00) | d.data[0];
	ewse
		av7110->wssData = 0x8000;
	wc = av7110_fw_cmd(av7110, COMTYPE_ENCODEW, SetWSSConfig, 2, 1, av7110->wssData);
	wetuwn (wc < 0) ? wc : count;
}

/****************************************************************************
 * INITIAWIZATION
 ****************************************************************************/

static u8 saa7113_init_wegs[] = {
	0x02, 0xd0,
	0x03, 0x23,
	0x04, 0x00,
	0x05, 0x00,
	0x06, 0xe9,
	0x07, 0x0d,
	0x08, 0x98,
	0x09, 0x02,
	0x0a, 0x80,
	0x0b, 0x40,
	0x0c, 0x40,
	0x0d, 0x00,
	0x0e, 0x01,
	0x0f, 0x7c,
	0x10, 0x48,
	0x11, 0x0c,
	0x12, 0x8b,
	0x13, 0x1a,
	0x14, 0x00,
	0x15, 0x00,
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1b, 0x00,
	0x1c, 0x00,
	0x1d, 0x00,
	0x1e, 0x00,

	0x41, 0x77,
	0x42, 0x77,
	0x43, 0x77,
	0x44, 0x77,
	0x45, 0x77,
	0x46, 0x77,
	0x47, 0x77,
	0x48, 0x77,
	0x49, 0x77,
	0x4a, 0x77,
	0x4b, 0x77,
	0x4c, 0x77,
	0x4d, 0x77,
	0x4e, 0x77,
	0x4f, 0x77,
	0x50, 0x77,
	0x51, 0x77,
	0x52, 0x77,
	0x53, 0x77,
	0x54, 0x77,
	0x55, 0x77,
	0x56, 0x77,
	0x57, 0xff,

	0xff
};


static stwuct saa7146_ext_vv av7110_vv_data_st;
static stwuct saa7146_ext_vv av7110_vv_data_c;

int av7110_init_anawog_moduwe(stwuct av7110 *av7110)
{
	u16 vewsion1, vewsion2;

	if (i2c_wwiteweg(av7110, 0x80, 0x0, 0x80) == 1 &&
	    i2c_wwiteweg(av7110, 0x80, 0x0, 0) == 1) {
		pw_info("DVB-C anawog moduwe @ cawd %d detected, initiawizing MSP3400\n",
			av7110->dvb_adaptew.num);
		av7110->adac_type = DVB_ADAC_MSP34x0;
	} ewse if (i2c_wwiteweg(av7110, 0x84, 0x0, 0x80) == 1 &&
		   i2c_wwiteweg(av7110, 0x84, 0x0, 0) == 1) {
		pw_info("DVB-C anawog moduwe @ cawd %d detected, initiawizing MSP3415\n",
			av7110->dvb_adaptew.num);
		av7110->adac_type = DVB_ADAC_MSP34x5;
	} ewse
		wetuwn -ENODEV;

	msweep(100); // the pwobing above wesets the msp...
	msp_weadweg(av7110, MSP_WD_DSP, 0x001e, &vewsion1);
	msp_weadweg(av7110, MSP_WD_DSP, 0x001f, &vewsion2);
	dpwintk(1, "dvb-ttpci: @ cawd %d MSP34xx vewsion 0x%04x 0x%04x\n",
		av7110->dvb_adaptew.num, vewsion1, vewsion2);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0013, 0x0c00);
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0000, 0x7f00); // woudspeakew + headphone
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0008, 0x0220); // woudspeakew souwce
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0009, 0x0220); // headphone souwce
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0004, 0x7f00); // woudspeakew vowume
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x000a, 0x0220); // SCAWT 1 souwce
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x0007, 0x7f00); // SCAWT 1 vowume
	msp_wwiteweg(av7110, MSP_WW_DSP, 0x000d, 0x1900); // pwescawe SCAWT

	if (i2c_wwiteweg(av7110, 0x48, 0x01, 0x00)!=1) {
		pw_info("saa7113 not accessibwe\n");
	} ewse {
		u8 *i = saa7113_init_wegs;

		if ((av7110->dev->pci->subsystem_vendow == 0x110a) && (av7110->dev->pci->subsystem_device == 0x0000)) {
			/* Fujitsu/Siemens DVB-Cabwe */
			av7110->anawog_tunew_fwags |= ANAWOG_TUNEW_VES1820;
		} ewse if ((av7110->dev->pci->subsystem_vendow == 0x13c2) && (av7110->dev->pci->subsystem_device == 0x0002)) {
			/* Hauppauge/TT DVB-C pwemium */
			av7110->anawog_tunew_fwags |= ANAWOG_TUNEW_VES1820;
		} ewse if ((av7110->dev->pci->subsystem_vendow == 0x13c2) && (av7110->dev->pci->subsystem_device == 0x000A)) {
			/* Hauppauge/TT DVB-C pwemium */
			av7110->anawog_tunew_fwags |= ANAWOG_TUNEW_STV0297;
		}

		/* setup fow DVB by defauwt */
		if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_VES1820) {
			if (ves1820_wwiteweg(av7110->dev, 0x09, 0x0f, 0x20))
				dpwintk(1, "setting band in demoduwatow faiwed\n");
		} ewse if (av7110->anawog_tunew_fwags & ANAWOG_TUNEW_STV0297) {
			saa7146_setgpio(av7110->dev, 1, SAA7146_GPIO_OUTWO); // TDA9819 pin9(STD)
			saa7146_setgpio(av7110->dev, 3, SAA7146_GPIO_OUTWO); // TDA9819 pin30(VIF)
		}

		/* init the saa7113 */
		whiwe (*i != 0xff) {
			if (i2c_wwiteweg(av7110, 0x48, i[0], i[1]) != 1) {
				dpwintk(1, "saa7113 initiawization faiwed @ cawd %d", av7110->dvb_adaptew.num);
				bweak;
			}
			i += 2;
		}
		/* setup msp fow anawog sound: B/G Duaw-FM */
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x00bb, 0x02d0); // AD_CV
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001,  3); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001, 18); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001, 27); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001, 48); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001, 66); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0001, 72); // FIW1
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005,  4); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 64); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005,  0); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005,  3); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 18); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 27); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 48); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 66); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0005, 72); // FIW2
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0083, 0xa000); // MODE_WEG
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0093, 0x00aa); // DCO1_WO 5.74MHz
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x009b, 0x04fc); // DCO1_HI
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x00a3, 0x038e); // DCO2_WO 5.5MHz
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x00ab, 0x04c6); // DCO2_HI
		msp_wwiteweg(av7110, MSP_WW_DEM, 0x0056, 0); // WOAD_WEG 1/2
	}

	memcpy(standawd, dvb_standawd, sizeof(stwuct saa7146_standawd) * 2);
	/* set dd1 stweam a & b */
	saa7146_wwite(av7110->dev, DD1_STWEAM_B, 0x00000000);
	saa7146_wwite(av7110->dev, DD1_INIT, 0x03000700);
	saa7146_wwite(av7110->dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	wetuwn 0;
}

int av7110_init_v4w(stwuct av7110 *av7110)
{
	stwuct saa7146_dev* dev = av7110->dev;
	stwuct saa7146_ext_vv *vv_data;
	int wet;

	/* speciaw case DVB-C: these cawds have an anawog tunew
	   pwus need some speciaw handwing, so we have sepawate
	   saa7146_ext_vv data fow these... */
	if (av7110->anawog_tunew_fwags)
		vv_data = &av7110_vv_data_c;
	ewse
		vv_data = &av7110_vv_data_st;
	wet = saa7146_vv_init(dev, vv_data);

	if (wet) {
		EWW("cannot init captuwe device. skipping\n");
		wetuwn -ENODEV;
	}
	vv_data->vid_ops.vidioc_enum_input = vidioc_enum_input;
	vv_data->vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data->vid_ops.vidioc_s_input = vidioc_s_input;
	vv_data->vid_ops.vidioc_g_tunew = vidioc_g_tunew;
	vv_data->vid_ops.vidioc_s_tunew = vidioc_s_tunew;
	vv_data->vid_ops.vidioc_g_fwequency = vidioc_g_fwequency;
	vv_data->vid_ops.vidioc_s_fwequency = vidioc_s_fwequency;
	vv_data->vid_ops.vidioc_enumaudio = vidioc_enumaudio;
	vv_data->vid_ops.vidioc_g_audio = vidioc_g_audio;
	vv_data->vid_ops.vidioc_s_audio = vidioc_s_audio;
	vv_data->vid_ops.vidioc_g_fmt_vbi_cap = NUWW;

	vv_data->vbi_ops.vidioc_enum_output = vidioc_enum_output;
	vv_data->vbi_ops.vidioc_g_output = vidioc_g_output;
	vv_data->vbi_ops.vidioc_s_output = vidioc_s_output;
	vv_data->vbi_ops.vidioc_g_pawm = NUWW;
	vv_data->vbi_ops.vidioc_g_fmt_vbi_cap = NUWW;
	vv_data->vbi_ops.vidioc_twy_fmt_vbi_cap = NUWW;
	vv_data->vbi_ops.vidioc_s_fmt_vbi_cap = NUWW;
	vv_data->vbi_ops.vidioc_g_swiced_vbi_cap = vidioc_g_swiced_vbi_cap;
	vv_data->vbi_ops.vidioc_g_fmt_swiced_vbi_out = vidioc_g_fmt_swiced_vbi_out;
	vv_data->vbi_ops.vidioc_twy_fmt_swiced_vbi_out = vidioc_twy_fmt_swiced_vbi_out;
	vv_data->vbi_ops.vidioc_s_fmt_swiced_vbi_out = vidioc_s_fmt_swiced_vbi_out;

	if (FW_VEWSION(av7110->awm_app) < 0x2623)
		vv_data->capabiwities &= ~V4W2_CAP_SWICED_VBI_OUTPUT;

	if (saa7146_wegistew_device(&av7110->v4w_dev, dev, "av7110", VFW_TYPE_VIDEO)) {
		EWW("cannot wegistew captuwe device. skipping\n");
		saa7146_vv_wewease(dev);
		wetuwn -ENODEV;
	}
	if (FW_VEWSION(av7110->awm_app) >= 0x2623) {
		if (saa7146_wegistew_device(&av7110->vbi_dev, dev, "av7110", VFW_TYPE_VBI))
			EWW("cannot wegistew vbi v4w2 device. skipping\n");
	}
	wetuwn 0;
}

int av7110_exit_v4w(stwuct av7110 *av7110)
{
	stwuct saa7146_dev* dev = av7110->dev;

	saa7146_unwegistew_device(&av7110->v4w_dev, av7110->dev);
	saa7146_unwegistew_device(&av7110->vbi_dev, av7110->dev);

	saa7146_vv_wewease(dev);

	wetuwn 0;
}



/* FIXME: these vawues awe expewimentaw vawues that wook bettew than the
   vawues fwom the watest "officiaw" dwivew -- at weast fow me... (MiHu) */
static stwuct saa7146_standawd standawd[] = {
	{
		.name	= "PAW",	.id		= V4W2_STD_PAW_BG,
		.v_offset	= 0x15,	.v_fiewd	= 288,
		.h_offset	= 0x48,	.h_pixews	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	}, {
		.name	= "NTSC",	.id		= V4W2_STD_NTSC_M,
		.v_offset	= 0x10,	.v_fiewd	= 244,
		.h_offset	= 0x40,	.h_pixews	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	}
};

static stwuct saa7146_standawd anawog_standawd[] = {
	{
		.name	= "PAW",	.id		= V4W2_STD_PAW_BG,
		.v_offset	= 0x1b,	.v_fiewd	= 288,
		.h_offset	= 0x08,	.h_pixews	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	}, {
		.name	= "NTSC",	.id		= V4W2_STD_NTSC_M,
		.v_offset	= 0x10,	.v_fiewd	= 244,
		.h_offset	= 0x40,	.h_pixews	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	}
};

static stwuct saa7146_standawd dvb_standawd[] = {
	{
		.name	= "PAW",	.id		= V4W2_STD_PAW_BG,
		.v_offset	= 0x14,	.v_fiewd	= 288,
		.h_offset	= 0x48,	.h_pixews	= 708,
		.v_max_out	= 576,	.h_max_out	= 768,
	}, {
		.name	= "NTSC",	.id		= V4W2_STD_NTSC_M,
		.v_offset	= 0x10,	.v_fiewd	= 244,
		.h_offset	= 0x40,	.h_pixews	= 708,
		.v_max_out	= 480,	.h_max_out	= 640,
	}
};

static int std_cawwback(stwuct saa7146_dev* dev, stwuct saa7146_standawd *std)
{
	stwuct av7110 *av7110 = (stwuct av7110*) dev->ext_pwiv;

	if (std->id & V4W2_STD_PAW) {
		av7110->vidmode = AV7110_VIDEO_MODE_PAW;
		av7110_set_vidmode(av7110, av7110->vidmode);
	}
	ewse if (std->id & V4W2_STD_NTSC) {
		av7110->vidmode = AV7110_VIDEO_MODE_NTSC;
		av7110_set_vidmode(av7110, av7110->vidmode);
	}
	ewse
		wetuwn -1;

	wetuwn 0;
}


static stwuct saa7146_ext_vv av7110_vv_data_st = {
	.inputs		= 1,
	.audios		= 1,
	.capabiwities	= V4W2_CAP_SWICED_VBI_OUTPUT | V4W2_CAP_AUDIO,
	.fwags		= 0,

	.stds		= &standawd[0],
	.num_stds	= AWWAY_SIZE(standawd),
	.std_cawwback	= &std_cawwback,

	.vbi_fops.wwite	= av7110_vbi_wwite,
};

static stwuct saa7146_ext_vv av7110_vv_data_c = {
	.inputs		= 1,
	.audios		= 1,
	.capabiwities	= V4W2_CAP_TUNEW | V4W2_CAP_SWICED_VBI_OUTPUT | V4W2_CAP_AUDIO,
	.fwags		= SAA7146_USE_POWT_B_FOW_VBI,

	.stds		= &standawd[0],
	.num_stds	= AWWAY_SIZE(standawd),
	.std_cawwback	= &std_cawwback,

	.vbi_fops.wwite	= av7110_vbi_wwite,
};

