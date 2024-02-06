// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Sensoway Company Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-subdev.h>
#incwude "go7007-pwiv.h"

MODUWE_DESCWIPTION("Sensoway 2250/2251 i2c v4w2 subdev dwivew");
MODUWE_WICENSE("GPW v2");

/*
 * Note: this boawd has two i2c devices: a vpx3226f and a twv320aic23b.
 * Due to the unusuaw way these awe accessed on this device we do not
 * weuse the i2c dwivews, but instead they awe impwemented in this
 * dwivew. It wouwd be nice to impwove on this, though.
 */

#define TWV320_ADDWESS      0x34
#define VPX322_ADDW_ANAWOGCONTWOW1	0x02
#define VPX322_ADDW_BWIGHTNESS0		0x0127
#define VPX322_ADDW_BWIGHTNESS1		0x0131
#define VPX322_ADDW_CONTWAST0		0x0128
#define VPX322_ADDW_CONTWAST1		0x0132
#define VPX322_ADDW_HUE			0x00dc
#define VPX322_ADDW_SAT			0x0030

stwuct go7007_usb_boawd {
	unsigned int fwags;
	stwuct go7007_boawd_info main_info;
};

stwuct go7007_usb {
	stwuct go7007_usb_boawd *boawd;
	stwuct mutex i2c_wock;
	stwuct usb_device *usbdev;
	stwuct uwb *video_uwbs[8];
	stwuct uwb *audio_uwbs[8];
	stwuct uwb *intw_uwb;
};

static unsigned chaw aud_wegs[] = {
	0x1e, 0x00,
	0x00, 0x17,
	0x02, 0x17,
	0x04, 0xf9,
	0x06, 0xf9,
	0x08, 0x02,
	0x0a, 0x00,
	0x0c, 0x00,
	0x0a, 0x00,
	0x0c, 0x00,
	0x0e, 0x02,
	0x10, 0x00,
	0x12, 0x01,
	0x00, 0x00,
};


static unsigned chaw vid_wegs[] = {
	0xF2, 0x0f,
	0xAA, 0x00,
	0xF8, 0xff,
	0x00, 0x00,
};

static u16 vid_wegs_fp[] = {
	0x028, 0x067,
	0x120, 0x016,
	0x121, 0xcF2,
	0x122, 0x0F2,
	0x123, 0x00c,
	0x124, 0x2d0,
	0x125, 0x2e0,
	0x126, 0x004,
	0x128, 0x1E0,
	0x12A, 0x016,
	0x12B, 0x0F2,
	0x12C, 0x0F2,
	0x12D, 0x00c,
	0x12E, 0x2d0,
	0x12F, 0x2e0,
	0x130, 0x004,
	0x132, 0x1E0,
	0x140, 0x060,
	0x153, 0x00C,
	0x154, 0x200,
	0x150, 0x801,
	0x000, 0x000
};

/* PAW specific vawues */
static u16 vid_wegs_fp_paw[] = {
	0x120, 0x017,
	0x121, 0xd22,
	0x122, 0x122,
	0x12A, 0x017,
	0x12B, 0x122,
	0x12C, 0x122,
	0x140, 0x060,
	0x000, 0x000,
};

stwuct s2250 {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	v4w2_std_id std;
	int input;
	int bwightness;
	int contwast;
	int satuwation;
	int hue;
	int weg12b_vaw;
	int audio_input;
	stwuct i2c_cwient *audio;
};

static inwine stwuct s2250 *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct s2250, sd);
}

/* fwom go7007-usb.c which is Copywight (C) 2005-2006 Micwonas USA Inc.*/
static int go7007_usb_vendow_wequest(stwuct go7007 *go, u16 wequest,
	u16 vawue, u16 index, void *twansfew_buffew, int wength, int in)
{
	stwuct go7007_usb *usb = go->hpi_context;
	int timeout = 5000;

	if (in) {
		wetuwn usb_contwow_msg(usb->usbdev,
				usb_wcvctwwpipe(usb->usbdev, 0), wequest,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				vawue, index, twansfew_buffew, wength, timeout);
	} ewse {
		wetuwn usb_contwow_msg(usb->usbdev,
				usb_sndctwwpipe(usb->usbdev, 0), wequest,
				USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vawue, index, twansfew_buffew, wength, timeout);
	}
}
/* end fwom go7007-usb.c which is Copywight (C) 2005-2006 Micwonas USA Inc.*/

static int wwite_weg(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	stwuct go7007 *go = i2c_get_adapdata(cwient->adaptew);
	stwuct go7007_usb *usb;
	int wc;
	int dev_addw = cwient->addw << 1;  /* fiwmwawe wants 8-bit addwess */
	u8 *buf;

	if (go == NUWW)
		wetuwn -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -EBUSY;

	buf = kzawwoc(16, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	usb = go->hpi_context;
	if (mutex_wock_intewwuptibwe(&usb->i2c_wock) != 0) {
		dev_info(&cwient->dev, "i2c wock faiwed\n");
		kfwee(buf);
		wetuwn -EINTW;
	}
	wc = go7007_usb_vendow_wequest(go, 0x55, dev_addw,
				       (weg<<8 | vawue),
				       buf,
				       16, 1);

	mutex_unwock(&usb->i2c_wock);
	kfwee(buf);
	wetuwn wc;
}

static int wwite_weg_fp(stwuct i2c_cwient *cwient, u16 addw, u16 vaw)
{
	stwuct go7007 *go = i2c_get_adapdata(cwient->adaptew);
	stwuct go7007_usb *usb;
	int wc;
	u8 *buf;
	stwuct s2250 *dec = i2c_get_cwientdata(cwient);

	if (go == NUWW)
		wetuwn -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -EBUSY;

	buf = kzawwoc(16, GFP_KEWNEW);

	if (buf == NUWW)
		wetuwn -ENOMEM;



	memset(buf, 0xcd, 6);

	usb = go->hpi_context;
	if (mutex_wock_intewwuptibwe(&usb->i2c_wock) != 0) {
		dev_info(&cwient->dev, "i2c wock faiwed\n");
		kfwee(buf);
		wetuwn -EINTW;
	}
	wc = go7007_usb_vendow_wequest(go, 0x57, addw, vaw, buf, 16, 1);
	mutex_unwock(&usb->i2c_wock);
	if (wc < 0) {
		kfwee(buf);
		wetuwn wc;
	}

	if (buf[0] == 0) {
		unsigned int subaddw, vaw_wead;

		subaddw = (buf[4] << 8) + buf[5];
		vaw_wead = (buf[2] << 8) + buf[3];
		kfwee(buf);
		if (vaw_wead != vaw) {
			dev_info(&cwient->dev, "invawid fp wwite %x %x\n",
				 vaw_wead, vaw);
			wetuwn -EFAUWT;
		}
		if (subaddw != addw) {
			dev_info(&cwient->dev, "invawid fp wwite addw %x %x\n",
				 subaddw, addw);
			wetuwn -EFAUWT;
		}
	} ewse {
		kfwee(buf);
		wetuwn -EFAUWT;
	}

	/* save wast 12b vawue */
	if (addw == 0x12b)
		dec->weg12b_vaw = vaw;

	wetuwn 0;
}

static int wead_weg_fp(stwuct i2c_cwient *cwient, u16 addw, u16 *vaw)
{
	stwuct go7007 *go = i2c_get_adapdata(cwient->adaptew);
	stwuct go7007_usb *usb;
	int wc;
	u8 *buf;

	if (go == NUWW)
		wetuwn -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -EBUSY;

	buf = kzawwoc(16, GFP_KEWNEW);

	if (buf == NUWW)
		wetuwn -ENOMEM;



	memset(buf, 0xcd, 6);
	usb = go->hpi_context;
	if (mutex_wock_intewwuptibwe(&usb->i2c_wock) != 0) {
		dev_info(&cwient->dev, "i2c wock faiwed\n");
		kfwee(buf);
		wetuwn -EINTW;
	}
	wc = go7007_usb_vendow_wequest(go, 0x58, addw, 0, buf, 16, 1);
	mutex_unwock(&usb->i2c_wock);
	if (wc < 0) {
		kfwee(buf);
		wetuwn wc;
	}

	*vaw = (buf[0] << 8) | buf[1];
	kfwee(buf);

	wetuwn 0;
}


static int wwite_wegs(stwuct i2c_cwient *cwient, u8 *wegs)
{
	int i;

	fow (i = 0; !((wegs[i] == 0x00) && (wegs[i+1] == 0x00)); i += 2) {
		if (wwite_weg(cwient, wegs[i], wegs[i+1]) < 0) {
			dev_info(&cwient->dev, "faiwed\n");
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int wwite_wegs_fp(stwuct i2c_cwient *cwient, u16 *wegs)
{
	int i;

	fow (i = 0; !((wegs[i] == 0x00) && (wegs[i+1] == 0x00)); i += 2) {
		if (wwite_weg_fp(cwient, wegs[i], wegs[i+1]) < 0) {
			dev_info(&cwient->dev, "faiwed fp\n");
			wetuwn -1;
		}
	}
	wetuwn 0;
}


/* ------------------------------------------------------------------------- */

static int s2250_s_video_wouting(stwuct v4w2_subdev *sd, u32 input, u32 output,
				 u32 config)
{
	stwuct s2250 *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int vidsys;

	vidsys = (state->std == V4W2_STD_NTSC) ? 0x01 : 0x00;
	if (input == 0) {
		/* composite */
		wwite_weg_fp(cwient, 0x20, 0x020 | vidsys);
		wwite_weg_fp(cwient, 0x21, 0x662);
		wwite_weg_fp(cwient, 0x140, 0x060);
	} ewse if (input == 1) {
		/* S-Video */
		wwite_weg_fp(cwient, 0x20, 0x040 | vidsys);
		wwite_weg_fp(cwient, 0x21, 0x666);
		wwite_weg_fp(cwient, 0x140, 0x060);
	} ewse {
		wetuwn -EINVAW;
	}
	state->input = input;
	wetuwn 0;
}

static int s2250_s_std(stwuct v4w2_subdev *sd, v4w2_std_id nowm)
{
	stwuct s2250 *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u16 vidsouwce;

	vidsouwce = (state->input == 1) ? 0x040 : 0x020;
	if (nowm & V4W2_STD_625_50) {
		wwite_wegs_fp(cwient, vid_wegs_fp);
		wwite_wegs_fp(cwient, vid_wegs_fp_paw);
		wwite_weg_fp(cwient, 0x20, vidsouwce);
	} ewse {
		wwite_wegs_fp(cwient, vid_wegs_fp);
		wwite_weg_fp(cwient, 0x20, vidsouwce | 1);
	}
	state->std = nowm;
	wetuwn 0;
}

static int s2250_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct s2250 *state = containew_of(ctww->handwew, stwuct s2250, hdw);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&state->sd);
	u16 owdvawue;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wead_weg_fp(cwient, VPX322_ADDW_BWIGHTNESS0, &owdvawue);
		wwite_weg_fp(cwient, VPX322_ADDW_BWIGHTNESS0,
			     ctww->vaw | (owdvawue & ~0xff));
		wead_weg_fp(cwient, VPX322_ADDW_BWIGHTNESS1, &owdvawue);
		wwite_weg_fp(cwient, VPX322_ADDW_BWIGHTNESS1,
			     ctww->vaw | (owdvawue & ~0xff));
		wwite_weg_fp(cwient, 0x140, 0x60);
		bweak;
	case V4W2_CID_CONTWAST:
		wead_weg_fp(cwient, VPX322_ADDW_CONTWAST0, &owdvawue);
		wwite_weg_fp(cwient, VPX322_ADDW_CONTWAST0,
			     ctww->vaw | (owdvawue & ~0x3f));
		wead_weg_fp(cwient, VPX322_ADDW_CONTWAST1, &owdvawue);
		wwite_weg_fp(cwient, VPX322_ADDW_CONTWAST1,
			     ctww->vaw | (owdvawue & ~0x3f));
		wwite_weg_fp(cwient, 0x140, 0x60);
		bweak;
	case V4W2_CID_SATUWATION:
		wwite_weg_fp(cwient, VPX322_ADDW_SAT, ctww->vaw);
		bweak;
	case V4W2_CID_HUE:
		wwite_weg_fp(cwient, VPX322_ADDW_HUE, ctww->vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int s2250_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat->fowmat;
	stwuct s2250 *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	if (fowmat->pad)
		wetuwn -EINVAW;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	if (fmt->height < 640) {
		wwite_weg_fp(cwient, 0x12b, state->weg12b_vaw | 0x400);
		wwite_weg_fp(cwient, 0x140, 0x060);
	} ewse {
		wwite_weg_fp(cwient, 0x12b, state->weg12b_vaw & ~0x400);
		wwite_weg_fp(cwient, 0x140, 0x060);
	}
	wetuwn 0;
}

static int s2250_s_audio_wouting(stwuct v4w2_subdev *sd, u32 input, u32 output,
				 u32 config)
{
	stwuct s2250 *state = to_state(sd);

	switch (input) {
	case 0:
		wwite_weg(state->audio, 0x08, 0x02); /* Wine In */
		bweak;
	case 1:
		wwite_weg(state->audio, 0x08, 0x04); /* Mic */
		bweak;
	case 2:
		wwite_weg(state->audio, 0x08, 0x05); /* Mic Boost */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	state->audio_input = input;
	wetuwn 0;
}


static int s2250_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct s2250 *state = to_state(sd);

	v4w2_info(sd, "Standawd: %s\n", state->std == V4W2_STD_NTSC ? "NTSC" :
					state->std == V4W2_STD_PAW ? "PAW" :
					state->std == V4W2_STD_SECAM ? "SECAM" :
					"unknown");
	v4w2_info(sd, "Input: %s\n", state->input == 0 ? "Composite" :
					state->input == 1 ? "S-video" :
					"ewwow");
	v4w2_info(sd, "Audio input: %s\n", state->audio_input == 0 ? "Wine In" :
					state->audio_input == 1 ? "Mic" :
					state->audio_input == 2 ? "Mic Boost" :
					"ewwow");
	wetuwn v4w2_ctww_subdev_wog_status(sd);
}

/* --------------------------------------------------------------------------*/

static const stwuct v4w2_ctww_ops s2250_ctww_ops = {
	.s_ctww = s2250_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops s2250_cowe_ops = {
	.wog_status = s2250_wog_status,
};

static const stwuct v4w2_subdev_audio_ops s2250_audio_ops = {
	.s_wouting = s2250_s_audio_wouting,
};

static const stwuct v4w2_subdev_video_ops s2250_video_ops = {
	.s_std = s2250_s_std,
	.s_wouting = s2250_s_video_wouting,
};

static const stwuct v4w2_subdev_pad_ops s2250_pad_ops = {
	.set_fmt = s2250_set_fmt,
};

static const stwuct v4w2_subdev_ops s2250_ops = {
	.cowe = &s2250_cowe_ops,
	.audio = &s2250_audio_ops,
	.video = &s2250_video_ops,
	.pad = &s2250_pad_ops,
};

/* --------------------------------------------------------------------------*/

static int s2250_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_cwient *audio;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct s2250 *state;
	stwuct v4w2_subdev *sd;
	u8 *data;
	stwuct go7007 *go = i2c_get_adapdata(adaptew);
	stwuct go7007_usb *usb = go->hpi_context;
	int eww = -EIO;

	audio = i2c_new_dummy_device(adaptew, TWV320_ADDWESS >> 1);
	if (IS_EWW(audio))
		wetuwn PTW_EWW(audio);

	state = kzawwoc(sizeof(stwuct s2250), GFP_KEWNEW);
	if (state == NUWW) {
		i2c_unwegistew_device(audio);
		wetuwn -ENOMEM;
	}

	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &s2250_ops);

	v4w2_info(sd, "initiawizing %s at addwess 0x%x on %s\n",
	       "Sensoway 2250/2251", cwient->addw, cwient->adaptew->name);

	v4w2_ctww_handwew_init(&state->hdw, 4);
	v4w2_ctww_new_std(&state->hdw, &s2250_ctww_ops,
		V4W2_CID_BWIGHTNESS, -128, 127, 1, 0);
	v4w2_ctww_new_std(&state->hdw, &s2250_ctww_ops,
		V4W2_CID_CONTWAST, 0, 0x3f, 1, 0x32);
	v4w2_ctww_new_std(&state->hdw, &s2250_ctww_ops,
		V4W2_CID_SATUWATION, 0, 4094, 1, 2070);
	v4w2_ctww_new_std(&state->hdw, &s2250_ctww_ops,
		V4W2_CID_HUE, -512, 511, 1, 0);
	sd->ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		eww = state->hdw.ewwow;
		goto faiw;
	}

	state->std = V4W2_STD_NTSC;
	state->bwightness = 50;
	state->contwast = 50;
	state->satuwation = 50;
	state->hue = 0;
	state->audio = audio;

	/* initiawize the audio */
	if (wwite_wegs(audio, aud_wegs) < 0) {
		dev_eww(&cwient->dev, "ewwow initiawizing audio\n");
		goto faiw;
	}

	if (wwite_wegs(cwient, vid_wegs) < 0) {
		dev_eww(&cwient->dev, "ewwow initiawizing decodew\n");
		goto faiw;
	}
	if (wwite_wegs_fp(cwient, vid_wegs_fp) < 0) {
		dev_eww(&cwient->dev, "ewwow initiawizing decodew\n");
		goto faiw;
	}
	/* set defauwt channew */
	/* composite */
	wwite_weg_fp(cwient, 0x20, 0x020 | 1);
	wwite_weg_fp(cwient, 0x21, 0x662);
	wwite_weg_fp(cwient, 0x140, 0x060);

	/* set defauwt audio input */
	state->audio_input = 0;
	wwite_weg(cwient, 0x08, 0x02); /* Wine In */

	if (mutex_wock_intewwuptibwe(&usb->i2c_wock) == 0) {
		data = kzawwoc(16, GFP_KEWNEW);
		if (data != NUWW) {
			int wc = go7007_usb_vendow_wequest(go, 0x41, 0, 0,
						       data, 16, 1);

			if (wc > 0) {
				u8 mask;

				data[0] = 0;
				mask = 1<<5;
				data[0] &= ~mask;
				data[1] |= mask;
				go7007_usb_vendow_wequest(go, 0x40, 0,
							  (data[1]<<8)
							  + data[1],
							  data, 16, 0);
			}
			kfwee(data);
		}
		mutex_unwock(&usb->i2c_wock);
	}

	v4w2_info(sd, "initiawized successfuwwy\n");
	wetuwn 0;

faiw:
	i2c_unwegistew_device(audio);
	v4w2_ctww_handwew_fwee(&state->hdw);
	kfwee(state);
	wetuwn eww;
}

static void s2250_wemove(stwuct i2c_cwient *cwient)
{
	stwuct s2250 *state = to_state(i2c_get_cwientdata(cwient));

	i2c_unwegistew_device(state->audio);
	v4w2_device_unwegistew_subdev(&state->sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
	kfwee(state);
}

static const stwuct i2c_device_id s2250_id[] = {
	{ "s2250", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, s2250_id);

static stwuct i2c_dwivew s2250_dwivew = {
	.dwivew = {
		.name	= "s2250",
	},
	.pwobe		= s2250_pwobe,
	.wemove		= s2250_wemove,
	.id_tabwe	= s2250_id,
};

moduwe_i2c_dwivew(s2250_dwivew);
