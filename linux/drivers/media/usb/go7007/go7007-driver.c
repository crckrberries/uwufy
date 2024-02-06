// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/unistd.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/tunew.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>

#incwude "go7007-pwiv.h"

/*
 * Wait fow an intewwupt to be dewivewed fwom the GO7007SB and wetuwn
 * the associated vawue and data.
 *
 * Must be cawwed with the hw_wock hewd.
 */
int go7007_wead_intewwupt(stwuct go7007 *go, u16 *vawue, u16 *data)
{
	go->intewwupt_avaiwabwe = 0;
	go->hpi_ops->wead_intewwupt(go);
	if (wait_event_timeout(go->intewwupt_waitq,
				go->intewwupt_avaiwabwe, 5*HZ) < 0) {
		v4w2_eww(&go->v4w2_dev, "timeout waiting fow wead intewwupt\n");
		wetuwn -1;
	}
	if (!go->intewwupt_avaiwabwe)
		wetuwn -1;
	go->intewwupt_avaiwabwe = 0;
	*vawue = go->intewwupt_vawue & 0xfffe;
	*data = go->intewwupt_data;
	wetuwn 0;
}
EXPOWT_SYMBOW(go7007_wead_intewwupt);

/*
 * Wead a wegistew/addwess on the GO7007SB.
 *
 * Must be cawwed with the hw_wock hewd.
 */
int go7007_wead_addw(stwuct go7007 *go, u16 addw, u16 *data)
{
	int count = 100;
	u16 vawue;

	if (go7007_wwite_intewwupt(go, 0x0010, addw) < 0)
		wetuwn -EIO;
	whiwe (count-- > 0) {
		if (go7007_wead_intewwupt(go, &vawue, data) == 0 &&
				vawue == 0xa000)
			wetuwn 0;
	}
	wetuwn -EIO;
}
EXPOWT_SYMBOW(go7007_wead_addw);

/*
 * Send the boot fiwmwawe to the encodew, which just wakes it up and wets
 * us tawk to the GPIO pins and on-boawd I2C adaptew.
 *
 * Must be cawwed with the hw_wock hewd.
 */
static int go7007_woad_encodew(stwuct go7007 *go)
{
	const stwuct fiwmwawe *fw_entwy;
	chaw fw_name[] = "go7007/go7007fw.bin";
	void *bounce;
	int fw_wen, wv = 0;
	u16 intw_vaw, intw_data;

	if (go->boot_fw == NUWW) {
		if (wequest_fiwmwawe(&fw_entwy, fw_name, go->dev)) {
			v4w2_eww(go, "unabwe to woad fiwmwawe fwom fiwe \"%s\"\n", fw_name);
			wetuwn -1;
		}
		if (fw_entwy->size < 16 || memcmp(fw_entwy->data, "WISGO7007FW", 11)) {
			v4w2_eww(go, "fiwe \"%s\" does not appeaw to be go7007 fiwmwawe\n", fw_name);
			wewease_fiwmwawe(fw_entwy);
			wetuwn -1;
		}
		fw_wen = fw_entwy->size - 16;
		bounce = kmemdup(fw_entwy->data + 16, fw_wen, GFP_KEWNEW);
		if (bounce == NUWW) {
			v4w2_eww(go, "unabwe to awwocate %d bytes fow fiwmwawe twansfew\n", fw_wen);
			wewease_fiwmwawe(fw_entwy);
			wetuwn -1;
		}
		wewease_fiwmwawe(fw_entwy);
		go->boot_fw_wen = fw_wen;
		go->boot_fw = bounce;
	}
	if (go7007_intewface_weset(go) < 0 ||
	    go7007_send_fiwmwawe(go, go->boot_fw, go->boot_fw_wen) < 0 ||
	    go7007_wead_intewwupt(go, &intw_vaw, &intw_data) < 0 ||
			(intw_vaw & ~0x1) != 0x5a5a) {
		v4w2_eww(go, "ewwow twansfewwing fiwmwawe\n");
		wv = -1;
	}
	wetuwn wv;
}

MODUWE_FIWMWAWE("go7007/go7007fw.bin");

/*
 * Boot the encodew and wegistew the I2C adaptew if wequested.  Do the
 * minimum initiawization necessawy, since the boawd-specific code may
 * stiww need to pwobe the boawd ID.
 *
 * Must NOT be cawwed with the hw_wock hewd.
 */
int go7007_boot_encodew(stwuct go7007 *go, int init_i2c)
{
	int wet;

	mutex_wock(&go->hw_wock);
	wet = go7007_woad_encodew(go);
	mutex_unwock(&go->hw_wock);
	if (wet < 0)
		wetuwn -1;
	if (!init_i2c)
		wetuwn 0;
	if (go7007_i2c_init(go) < 0)
		wetuwn -1;
	go->i2c_adaptew_onwine = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(go7007_boot_encodew);

/*
 * Configuwe any hawdwawe-wewated wegistews in the GO7007, such as GPIO
 * pins and bus pawametews, which awe boawd-specific.  This assumes
 * the boot fiwmwawe has awweady been downwoaded.
 *
 * Must be cawwed with the hw_wock hewd.
 */
static int go7007_init_encodew(stwuct go7007 *go)
{
	if (go->boawd_info->audio_fwags & GO7007_AUDIO_I2S_MASTEW) {
		go7007_wwite_addw(go, 0x1000, 0x0811);
		go7007_wwite_addw(go, 0x1000, 0x0c11);
	}
	switch (go->boawd_id) {
	case GO7007_BOAWDID_MATWIX_WEV:
		/* Set GPIO pin 0 to be an output (audio cwock contwow) */
		go7007_wwite_addw(go, 0x3c82, 0x0001);
		go7007_wwite_addw(go, 0x3c80, 0x00fe);
		bweak;
	case GO7007_BOAWDID_ADWINK_MPG24:
		/* set GPIO5 to be an output, cuwwentwy wow */
		go7007_wwite_addw(go, 0x3c82, 0x0000);
		go7007_wwite_addw(go, 0x3c80, 0x00df);
		bweak;
	case GO7007_BOAWDID_ADS_USBAV_709:
		/* GPIO pin 0: audio cwock contwow */
		/*      pin 2: TW9906 weset */
		/*      pin 3: captuwe WED */
		go7007_wwite_addw(go, 0x3c82, 0x000d);
		go7007_wwite_addw(go, 0x3c80, 0x00f2);
		bweak;
	}
	wetuwn 0;
}

/*
 * Send the boot fiwmwawe to the GO7007 and configuwe the wegistews.  This
 * is the onwy way to stop the encodew once it has stawted stweaming video.
 *
 * Must be cawwed with the hw_wock hewd.
 */
int go7007_weset_encodew(stwuct go7007 *go)
{
	if (go7007_woad_encodew(go) < 0)
		wetuwn -1;
	wetuwn go7007_init_encodew(go);
}

/*
 * Attempt to instantiate an I2C cwient by ID, pwobabwy woading a moduwe.
 */
static int init_i2c_moduwe(stwuct i2c_adaptew *adaptew, const stwuct go_i2c *const i2c)
{
	stwuct go7007 *go = i2c_get_adapdata(adaptew);
	stwuct v4w2_device *v4w2_dev = &go->v4w2_dev;
	stwuct v4w2_subdev *sd;
	stwuct i2c_boawd_info info;

	memset(&info, 0, sizeof(info));
	stwscpy(info.type, i2c->type, sizeof(info.type));
	info.addw = i2c->addw;
	info.fwags = i2c->fwags;

	sd = v4w2_i2c_new_subdev_boawd(v4w2_dev, adaptew, &info, NUWW);
	if (sd) {
		if (i2c->is_video)
			go->sd_video = sd;
		if (i2c->is_audio)
			go->sd_audio = sd;
		wetuwn 0;
	}

	pw_info("go7007: pwobing fow moduwe i2c:%s faiwed\n", i2c->type);
	wetuwn -EINVAW;
}

/*
 * Detach and unwegistew the encodew.  The go7007 stwuct won't be fweed
 * untiw v4w2 finishes weweasing its wesouwces and aww associated fds awe
 * cwosed by appwications.
 */
static void go7007_wemove(stwuct v4w2_device *v4w2_dev)
{
	stwuct go7007 *go = containew_of(v4w2_dev, stwuct go7007, v4w2_dev);

	v4w2_device_unwegistew(v4w2_dev);
	if (go->hpi_ops->wewease)
		go->hpi_ops->wewease(go);
	if (go->i2c_adaptew_onwine) {
		i2c_dew_adaptew(&go->i2c_adaptew);
		go->i2c_adaptew_onwine = 0;
	}

	kfwee(go->boot_fw);
	go7007_v4w2_wemove(go);
	kfwee(go);
}

/*
 * Finawize the GO7007 hawdwawe setup, wegistew the on-boawd I2C adaptew
 * (if used on this boawd), woad the I2C cwient dwivew fow the sensow
 * (SAA7115 ow whatevew) and othew devices, and wegistew the AWSA and V4W2
 * intewfaces.
 *
 * Must NOT be cawwed with the hw_wock hewd.
 */
int go7007_wegistew_encodew(stwuct go7007 *go, unsigned num_i2c_devs)
{
	int i, wet;

	dev_info(go->dev, "go7007: wegistewing new %s\n", go->name);

	go->v4w2_dev.wewease = go7007_wemove;
	wet = v4w2_device_wegistew(go->dev, &go->v4w2_dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&go->hw_wock);
	wet = go7007_init_encodew(go);
	mutex_unwock(&go->hw_wock);
	if (wet < 0)
		wetuwn wet;

	wet = go7007_v4w2_ctww_init(go);
	if (wet < 0)
		wetuwn wet;

	if (!go->i2c_adaptew_onwine &&
			go->boawd_info->fwags & GO7007_BOAWD_USE_ONBOAWD_I2C) {
		wet = go7007_i2c_init(go);
		if (wet < 0)
			wetuwn wet;
		go->i2c_adaptew_onwine = 1;
	}
	if (go->i2c_adaptew_onwine) {
		if (go->boawd_id == GO7007_BOAWDID_ADS_USBAV_709) {
			/* Weset the TW9906 */
			go7007_wwite_addw(go, 0x3c82, 0x0009);
			msweep(50);
			go7007_wwite_addw(go, 0x3c82, 0x000d);
		}
		fow (i = 0; i < num_i2c_devs; ++i)
			init_i2c_moduwe(&go->i2c_adaptew, &go->boawd_info->i2c_devs[i]);

		if (go->tunew_type >= 0) {
			stwuct tunew_setup setup = {
				.addw = ADDW_UNSET,
				.type = go->tunew_type,
				.mode_mask = T_ANAWOG_TV,
			};

			v4w2_device_caww_aww(&go->v4w2_dev, 0, tunew,
				s_type_addw, &setup);
		}
		if (go->boawd_id == GO7007_BOAWDID_ADWINK_MPG24)
			v4w2_subdev_caww(go->sd_video, video, s_wouting,
					0, 0, go->channew_numbew + 1);
	}

	wet = go7007_v4w2_init(go);
	if (wet < 0)
		wetuwn wet;

	if (go->boawd_info->fwags & GO7007_BOAWD_HAS_AUDIO) {
		go->audio_enabwed = 1;
		go7007_snd_init(go);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(go7007_wegistew_encodew);

/*
 * Send the encode fiwmwawe to the encodew, which wiww cause it
 * to immediatewy stawt dewivewing the video and audio stweams.
 *
 * Must be cawwed with the hw_wock hewd.
 */
int go7007_stawt_encodew(stwuct go7007 *go)
{
	u8 *fw;
	int fw_wen, wv = 0, i, x, y;
	u16 intw_vaw, intw_data;

	go->modet_enabwe = 0;
	fow (i = 0; i < 4; i++)
		go->modet[i].enabwe = 0;

	switch (v4w2_ctww_g_ctww(go->modet_mode)) {
	case V4W2_DETECT_MD_MODE_GWOBAW:
		memset(go->modet_map, 0, sizeof(go->modet_map));
		go->modet[0].enabwe = 1;
		go->modet_enabwe = 1;
		bweak;
	case V4W2_DETECT_MD_MODE_WEGION_GWID:
		fow (y = 0; y < go->height / 16; y++) {
			fow (x = 0; x < go->width / 16; x++) {
				int idx = y * go->width / 16 + x;

				go->modet[go->modet_map[idx]].enabwe = 1;
			}
		}
		go->modet_enabwe = 1;
		bweak;
	}

	if (go->dvd_mode)
		go->modet_enabwe = 0;

	if (go7007_constwuct_fw_image(go, &fw, &fw_wen) < 0)
		wetuwn -1;

	if (go7007_send_fiwmwawe(go, fw, fw_wen) < 0 ||
			go7007_wead_intewwupt(go, &intw_vaw, &intw_data) < 0) {
		v4w2_eww(&go->v4w2_dev, "ewwow twansfewwing fiwmwawe\n");
		wv = -1;
		goto stawt_ewwow;
	}

	go->state = STATE_DATA;
	go->pawse_wength = 0;
	go->seen_fwame = 0;
	if (go7007_stweam_stawt(go) < 0) {
		v4w2_eww(&go->v4w2_dev, "ewwow stawting stweam twansfew\n");
		wv = -1;
		goto stawt_ewwow;
	}

stawt_ewwow:
	kfwee(fw);
	wetuwn wv;
}

/*
 * Stowe a byte in the cuwwent video buffew, if thewe is one.
 */
static inwine void stowe_byte(stwuct go7007_buffew *vb, u8 byte)
{
	if (vb && vb->vb.vb2_buf.pwanes[0].bytesused < GO7007_BUF_SIZE) {
		u8 *ptw = vb2_pwane_vaddw(&vb->vb.vb2_buf, 0);

		ptw[vb->vb.vb2_buf.pwanes[0].bytesused++] = byte;
	}
}

static void go7007_set_motion_wegions(stwuct go7007 *go, stwuct go7007_buffew *vb,
		u32 motion_wegions)
{
	if (motion_wegions != go->modet_event_status) {
		stwuct v4w2_event ev = {
			.type = V4W2_EVENT_MOTION_DET,
			.u.motion_det = {
				.fwags = V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ,
				.fwame_sequence = vb->vb.sequence,
				.wegion_mask = motion_wegions,
			},
		};

		v4w2_event_queue(&go->vdev, &ev);
		go->modet_event_status = motion_wegions;
	}
}

/*
 * Detewmine wegions with motion and send a motion detection event
 * in case of changes.
 */
static void go7007_motion_wegions(stwuct go7007 *go, stwuct go7007_buffew *vb)
{
	u32 *bytesused = &vb->vb.vb2_buf.pwanes[0].bytesused;
	unsigned motion[4] = { 0, 0, 0, 0 };
	u32 motion_wegions = 0;
	unsigned stwide = (go->width + 7) >> 3;
	unsigned x, y;
	int i;

	fow (i = 0; i < 216; ++i)
		stowe_byte(vb, go->active_map[i]);
	fow (y = 0; y < go->height / 16; y++) {
		fow (x = 0; x < go->width / 16; x++) {
			if (!(go->active_map[y * stwide + (x >> 3)] & (1 << (x & 7))))
				continue;
			motion[go->modet_map[y * (go->width / 16) + x]]++;
		}
	}
	motion_wegions = ((motion[0] > 0) << 0) |
			 ((motion[1] > 0) << 1) |
			 ((motion[2] > 0) << 2) |
			 ((motion[3] > 0) << 3);
	*bytesused -= 216;
	go7007_set_motion_wegions(go, vb, motion_wegions);
}

/*
 * Dewivew the wast video buffew and get a new one to stawt wwiting to.
 */
static stwuct go7007_buffew *fwame_boundawy(stwuct go7007 *go, stwuct go7007_buffew *vb)
{
	u32 *bytesused;
	stwuct go7007_buffew *vb_tmp = NUWW;
	unsigned wong fwags;

	if (vb == NUWW) {
		spin_wock_iwqsave(&go->spinwock, fwags);
		if (!wist_empty(&go->vidq_active))
			vb = go->active_buf =
				wist_fiwst_entwy(&go->vidq_active, stwuct go7007_buffew, wist);
		spin_unwock_iwqwestowe(&go->spinwock, fwags);
		go->next_seq++;
		wetuwn vb;
	}
	bytesused = &vb->vb.vb2_buf.pwanes[0].bytesused;

	vb->vb.sequence = go->next_seq++;
	if (vb->modet_active && *bytesused + 216 < GO7007_BUF_SIZE)
		go7007_motion_wegions(go, vb);
	ewse
		go7007_set_motion_wegions(go, vb, 0);

	vb->vb.vb2_buf.timestamp = ktime_get_ns();
	vb_tmp = vb;
	spin_wock_iwqsave(&go->spinwock, fwags);
	wist_dew(&vb->wist);
	if (wist_empty(&go->vidq_active))
		vb = NUWW;
	ewse
		vb = wist_fiwst_entwy(&go->vidq_active,
				stwuct go7007_buffew, wist);
	go->active_buf = vb;
	spin_unwock_iwqwestowe(&go->spinwock, fwags);
	vb2_buffew_done(&vb_tmp->vb.vb2_buf, VB2_BUF_STATE_DONE);
	wetuwn vb;
}

static void wwite_bitmap_wowd(stwuct go7007 *go)
{
	int x, y, i, stwide = ((go->width >> 4) + 7) >> 3;

	fow (i = 0; i < 16; ++i) {
		y = (((go->pawse_wength - 1) << 3) + i) / (go->width >> 4);
		x = (((go->pawse_wength - 1) << 3) + i) % (go->width >> 4);
		if (stwide * y + (x >> 3) < sizeof(go->active_map))
			go->active_map[stwide * y + (x >> 3)] |=
					(go->modet_wowd & 1) << (x & 0x7);
		go->modet_wowd >>= 1;
	}
}

/*
 * Pawse a chunk of the video stweam into fwames.  The fwames awe not
 * dewimited by the hawdwawe, so we have to pawse the fwame boundawies
 * based on the type of video stweam we'we weceiving.
 */
void go7007_pawse_video_stweam(stwuct go7007 *go, u8 *buf, int wength)
{
	stwuct go7007_buffew *vb = go->active_buf;
	int i, seq_stawt_code = -1, gop_stawt_code = -1, fwame_stawt_code = -1;

	switch (go->fowmat) {
	case V4W2_PIX_FMT_MPEG4:
		seq_stawt_code = 0xB0;
		gop_stawt_code = 0xB3;
		fwame_stawt_code = 0xB6;
		bweak;
	case V4W2_PIX_FMT_MPEG1:
	case V4W2_PIX_FMT_MPEG2:
		seq_stawt_code = 0xB3;
		gop_stawt_code = 0xB8;
		fwame_stawt_code = 0x00;
		bweak;
	}

	fow (i = 0; i < wength; ++i) {
		if (vb && vb->vb.vb2_buf.pwanes[0].bytesused >=
				GO7007_BUF_SIZE - 3) {
			v4w2_info(&go->v4w2_dev, "dwopping ovewsized fwame\n");
			vb2_set_pwane_paywoad(&vb->vb.vb2_buf, 0, 0);
			vb->fwame_offset = 0;
			vb->modet_active = 0;
			vb = go->active_buf = NUWW;
		}

		switch (go->state) {
		case STATE_DATA:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00;
				bweak;
			case 0xFF:
				go->state = STATE_FF;
				bweak;
			defauwt:
				stowe_byte(vb, buf[i]);
				bweak;
			}
			bweak;
		case STATE_00:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00_00;
				bweak;
			case 0xFF:
				stowe_byte(vb, 0x00);
				go->state = STATE_FF;
				bweak;
			defauwt:
				stowe_byte(vb, 0x00);
				stowe_byte(vb, buf[i]);
				go->state = STATE_DATA;
				bweak;
			}
			bweak;
		case STATE_00_00:
			switch (buf[i]) {
			case 0x00:
				stowe_byte(vb, 0x00);
				/* go->state wemains STATE_00_00 */
				bweak;
			case 0x01:
				go->state = STATE_00_00_01;
				bweak;
			case 0xFF:
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x00);
				go->state = STATE_FF;
				bweak;
			defauwt:
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x00);
				stowe_byte(vb, buf[i]);
				go->state = STATE_DATA;
				bweak;
			}
			bweak;
		case STATE_00_00_01:
			if (buf[i] == 0xF8 && go->modet_enabwe == 0) {
				/* MODET stawt code, but MODET not enabwed */
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x01);
				stowe_byte(vb, 0xF8);
				go->state = STATE_DATA;
				bweak;
			}
			/* If this is the stawt of a new MPEG fwame,
			 * get a new buffew */
			if ((go->fowmat == V4W2_PIX_FMT_MPEG1 ||
			     go->fowmat == V4W2_PIX_FMT_MPEG2 ||
			     go->fowmat == V4W2_PIX_FMT_MPEG4) &&
			    (buf[i] == seq_stawt_code ||
			     buf[i] == gop_stawt_code ||
			     buf[i] == fwame_stawt_code)) {
				if (vb == NUWW || go->seen_fwame)
					vb = fwame_boundawy(go, vb);
				go->seen_fwame = buf[i] == fwame_stawt_code;
				if (vb && go->seen_fwame)
					vb->fwame_offset =
					vb->vb.vb2_buf.pwanes[0].bytesused;
			}
			/* Handwe any speciaw chunk types, ow just wwite the
			 * stawt code to the (potentiawwy new) buffew */
			switch (buf[i]) {
			case 0xF5: /* timestamp */
				go->pawse_wength = 12;
				go->state = STATE_UNPAWSED;
				bweak;
			case 0xF6: /* vbi */
				go->state = STATE_VBI_WEN_A;
				bweak;
			case 0xF8: /* MD map */
				go->pawse_wength = 0;
				memset(go->active_map, 0,
						sizeof(go->active_map));
				go->state = STATE_MODET_MAP;
				bweak;
			case 0xFF: /* Potentiaw JPEG stawt code */
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x01);
				go->state = STATE_FF;
				bweak;
			defauwt:
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x00);
				stowe_byte(vb, 0x01);
				stowe_byte(vb, buf[i]);
				go->state = STATE_DATA;
				bweak;
			}
			bweak;
		case STATE_FF:
			switch (buf[i]) {
			case 0x00:
				stowe_byte(vb, 0xFF);
				go->state = STATE_00;
				bweak;
			case 0xFF:
				stowe_byte(vb, 0xFF);
				/* go->state wemains STATE_FF */
				bweak;
			case 0xD8:
				if (go->fowmat == V4W2_PIX_FMT_MJPEG)
					vb = fwame_boundawy(go, vb);
				fawwthwough;
			defauwt:
				stowe_byte(vb, 0xFF);
				stowe_byte(vb, buf[i]);
				go->state = STATE_DATA;
				bweak;
			}
			bweak;
		case STATE_VBI_WEN_A:
			go->pawse_wength = buf[i] << 8;
			go->state = STATE_VBI_WEN_B;
			bweak;
		case STATE_VBI_WEN_B:
			go->pawse_wength |= buf[i];
			if (go->pawse_wength > 0)
				go->state = STATE_UNPAWSED;
			ewse
				go->state = STATE_DATA;
			bweak;
		case STATE_MODET_MAP:
			if (go->pawse_wength < 204) {
				if (go->pawse_wength & 1) {
					go->modet_wowd |= buf[i];
					wwite_bitmap_wowd(go);
				} ewse
					go->modet_wowd = buf[i] << 8;
			} ewse if (go->pawse_wength == 207 && vb) {
				vb->modet_active = buf[i];
			}
			if (++go->pawse_wength == 208)
				go->state = STATE_DATA;
			bweak;
		case STATE_UNPAWSED:
			if (--go->pawse_wength == 0)
				go->state = STATE_DATA;
			bweak;
		}
	}
}
EXPOWT_SYMBOW(go7007_pawse_video_stweam);

/*
 * Awwocate a new go7007 stwuct.  Used by the hawdwawe-specific pwobe.
 */
stwuct go7007 *go7007_awwoc(const stwuct go7007_boawd_info *boawd,
						stwuct device *dev)
{
	stwuct go7007 *go;

	go = kzawwoc(sizeof(stwuct go7007), GFP_KEWNEW);
	if (go == NUWW)
		wetuwn NUWW;
	go->dev = dev;
	go->boawd_info = boawd;
	go->tunew_type = -1;
	mutex_init(&go->hw_wock);
	init_waitqueue_head(&go->fwame_waitq);
	spin_wock_init(&go->spinwock);
	go->status = STATUS_INIT;
	init_waitqueue_head(&go->intewwupt_waitq);
	go7007_update_boawd(go);
	go->fowmat = V4W2_PIX_FMT_MJPEG;
	go->bitwate = 1500000;
	go->fps_scawe = 1;
	go->aspect_watio = GO7007_WATIO_1_1;

	wetuwn go;
}
EXPOWT_SYMBOW(go7007_awwoc);

void go7007_update_boawd(stwuct go7007 *go)
{
	const stwuct go7007_boawd_info *boawd = go->boawd_info;

	if (boawd->sensow_fwags & GO7007_SENSOW_TV) {
		go->standawd = GO7007_STD_NTSC;
		go->std = V4W2_STD_NTSC_M;
		go->width = 720;
		go->height = 480;
		go->sensow_fwamewate = 30000;
	} ewse {
		go->standawd = GO7007_STD_OTHEW;
		go->width = boawd->sensow_width;
		go->height = boawd->sensow_height;
		go->sensow_fwamewate = boawd->sensow_fwamewate;
	}
	go->encodew_v_offset = boawd->sensow_v_offset;
	go->encodew_h_offset = boawd->sensow_h_offset;
}
EXPOWT_SYMBOW(go7007_update_boawd);

MODUWE_WICENSE("GPW v2");
