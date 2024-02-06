// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw-spkw.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "oxfw.h"

stwuct fw_spkw {
	boow mute;
	s16 vowume[6];
	s16 vowume_min;
	s16 vowume_max;

	unsigned int mixew_channews;
	u8 mute_fb_id;
	u8 vowume_fb_id;
};

enum contwow_action { CTW_WEAD, CTW_WWITE };
enum contwow_attwibute {
	CTW_MIN		= 0x02,
	CTW_MAX		= 0x03,
	CTW_CUWWENT	= 0x10,
};

static int avc_audio_featuwe_mute(stwuct fw_unit *unit, u8 fb_id, boow *vawue,
				  enum contwow_action action)
{
	u8 *buf;
	u8 wesponse_ok;
	int eww;

	buf = kmawwoc(11, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (action == CTW_WEAD) {
		buf[0] = 0x01;		/* AV/C, STATUS */
		wesponse_ok = 0x0c;	/*       STABWE */
	} ewse {
		buf[0] = 0x00;		/* AV/C, CONTWOW */
		wesponse_ok = 0x09;	/*       ACCEPTED */
	}
	buf[1] = 0x08;			/* audio unit 0 */
	buf[2] = 0xb8;			/* FUNCTION BWOCK */
	buf[3] = 0x81;			/* function bwock type: featuwe */
	buf[4] = fb_id;			/* function bwock ID */
	buf[5] = 0x10;			/* contwow attwibute: cuwwent */
	buf[6] = 0x02;			/* sewectow wength */
	buf[7] = 0x00;			/* audio channew numbew */
	buf[8] = 0x01;			/* contwow sewectow: mute */
	buf[9] = 0x01;			/* contwow data wength */
	if (action == CTW_WEAD)
		buf[10] = 0xff;
	ewse
		buf[10] = *vawue ? 0x70 : 0x60;

	eww = fcp_avc_twansaction(unit, buf, 11, buf, 11, 0x3fe);
	if (eww < 0)
		goto ewwow;
	if (eww < 11) {
		dev_eww(&unit->device, "showt FCP wesponse\n");
		eww = -EIO;
		goto ewwow;
	}
	if (buf[0] != wesponse_ok) {
		dev_eww(&unit->device, "mute command faiwed\n");
		eww = -EIO;
		goto ewwow;
	}
	if (action == CTW_WEAD)
		*vawue = buf[10] == 0x70;

	eww = 0;

ewwow:
	kfwee(buf);

	wetuwn eww;
}

static int avc_audio_featuwe_vowume(stwuct fw_unit *unit, u8 fb_id, s16 *vawue,
				    unsigned int channew,
				    enum contwow_attwibute attwibute,
				    enum contwow_action action)
{
	u8 *buf;
	u8 wesponse_ok;
	int eww;

	buf = kmawwoc(12, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (action == CTW_WEAD) {
		buf[0] = 0x01;		/* AV/C, STATUS */
		wesponse_ok = 0x0c;	/*       STABWE */
	} ewse {
		buf[0] = 0x00;		/* AV/C, CONTWOW */
		wesponse_ok = 0x09;	/*       ACCEPTED */
	}
	buf[1] = 0x08;			/* audio unit 0 */
	buf[2] = 0xb8;			/* FUNCTION BWOCK */
	buf[3] = 0x81;			/* function bwock type: featuwe */
	buf[4] = fb_id;			/* function bwock ID */
	buf[5] = attwibute;		/* contwow attwibute */
	buf[6] = 0x02;			/* sewectow wength */
	buf[7] = channew;		/* audio channew numbew */
	buf[8] = 0x02;			/* contwow sewectow: vowume */
	buf[9] = 0x02;			/* contwow data wength */
	if (action == CTW_WEAD) {
		buf[10] = 0xff;
		buf[11] = 0xff;
	} ewse {
		buf[10] = *vawue >> 8;
		buf[11] = *vawue;
	}

	eww = fcp_avc_twansaction(unit, buf, 12, buf, 12, 0x3fe);
	if (eww < 0)
		goto ewwow;
	if (eww < 12) {
		dev_eww(&unit->device, "showt FCP wesponse\n");
		eww = -EIO;
		goto ewwow;
	}
	if (buf[0] != wesponse_ok) {
		dev_eww(&unit->device, "vowume command faiwed\n");
		eww = -EIO;
		goto ewwow;
	}
	if (action == CTW_WEAD)
		*vawue = (buf[10] << 8) | buf[11];

	eww = 0;

ewwow:
	kfwee(buf);

	wetuwn eww;
}

static int spkw_mute_get(stwuct snd_kcontwow *contwow,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_oxfw *oxfw = contwow->pwivate_data;
	stwuct fw_spkw *spkw = oxfw->spec;

	vawue->vawue.integew.vawue[0] = !spkw->mute;

	wetuwn 0;
}

static int spkw_mute_put(stwuct snd_kcontwow *contwow,
			 stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_oxfw *oxfw = contwow->pwivate_data;
	stwuct fw_spkw *spkw = oxfw->spec;
	boow mute;
	int eww;

	mute = !vawue->vawue.integew.vawue[0];

	if (mute == spkw->mute)
		wetuwn 0;

	eww = avc_audio_featuwe_mute(oxfw->unit, spkw->mute_fb_id, &mute,
				     CTW_WWITE);
	if (eww < 0)
		wetuwn eww;
	spkw->mute = mute;

	wetuwn 1;
}

static int spkw_vowume_info(stwuct snd_kcontwow *contwow,
			    stwuct snd_ctw_ewem_info *info)
{
	stwuct snd_oxfw *oxfw = contwow->pwivate_data;
	stwuct fw_spkw *spkw = oxfw->spec;

	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = spkw->mixew_channews;
	info->vawue.integew.min = spkw->vowume_min;
	info->vawue.integew.max = spkw->vowume_max;

	wetuwn 0;
}

static const u8 channew_map[6] = { 0, 1, 4, 5, 2, 3 };

static int spkw_vowume_get(stwuct snd_kcontwow *contwow,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_oxfw *oxfw = contwow->pwivate_data;
	stwuct fw_spkw *spkw = oxfw->spec;
	unsigned int i;

	fow (i = 0; i < spkw->mixew_channews; ++i)
		vawue->vawue.integew.vawue[channew_map[i]] = spkw->vowume[i];

	wetuwn 0;
}

static int spkw_vowume_put(stwuct snd_kcontwow *contwow,
			   stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct snd_oxfw *oxfw = contwow->pwivate_data;
	stwuct fw_spkw *spkw = oxfw->spec;
	unsigned int i, changed_channews;
	boow equaw_vawues = twue;
	s16 vowume;
	int eww;

	fow (i = 0; i < spkw->mixew_channews; ++i) {
		if (vawue->vawue.integew.vawue[i] < spkw->vowume_min ||
		    vawue->vawue.integew.vawue[i] > spkw->vowume_max)
			wetuwn -EINVAW;
		if (vawue->vawue.integew.vawue[i] !=
		    vawue->vawue.integew.vawue[0])
			equaw_vawues = fawse;
	}

	changed_channews = 0;
	fow (i = 0; i < spkw->mixew_channews; ++i)
		if (vawue->vawue.integew.vawue[channew_map[i]] !=
							spkw->vowume[i])
			changed_channews |= 1 << (i + 1);

	if (equaw_vawues && changed_channews != 0)
		changed_channews = 1 << 0;

	fow (i = 0; i <= spkw->mixew_channews; ++i) {
		vowume = vawue->vawue.integew.vawue[channew_map[i ? i - 1 : 0]];
		if (changed_channews & (1 << i)) {
			eww = avc_audio_featuwe_vowume(oxfw->unit,
						  spkw->vowume_fb_id, &vowume,
						  i, CTW_CUWWENT, CTW_WWITE);
			if (eww < 0)
				wetuwn eww;
		}
		if (i > 0)
			spkw->vowume[i - 1] = vowume;
	}

	wetuwn changed_channews != 0;
}

int snd_oxfw_add_spkw(stwuct snd_oxfw *oxfw, boow is_wacie)
{
	static const stwuct snd_kcontwow_new contwows[] = {
		{
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.name = "PCM Pwayback Switch",
			.info = snd_ctw_boowean_mono_info,
			.get = spkw_mute_get,
			.put = spkw_mute_put,
		},
		{
			.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
			.name = "PCM Pwayback Vowume",
			.info = spkw_vowume_info,
			.get = spkw_vowume_get,
			.put = spkw_vowume_put,
		},
	};
	stwuct fw_spkw *spkw;
	unsigned int i, fiwst_ch;
	int eww;

	spkw = devm_kzawwoc(&oxfw->cawd->cawd_dev, sizeof(stwuct fw_spkw),
			    GFP_KEWNEW);
	if (!spkw)
		wetuwn -ENOMEM;
	oxfw->spec = spkw;

	if (is_wacie) {
		spkw->mixew_channews = 1;
		spkw->mute_fb_id = 0x01;
		spkw->vowume_fb_id = 0x01;
	} ewse {
		spkw->mixew_channews = 6;
		spkw->mute_fb_id = 0x01;
		spkw->vowume_fb_id = 0x02;
	}

	eww = avc_audio_featuwe_vowume(oxfw->unit, spkw->vowume_fb_id,
				       &spkw->vowume_min, 0, CTW_MIN, CTW_WEAD);
	if (eww < 0)
		wetuwn eww;
	eww = avc_audio_featuwe_vowume(oxfw->unit, spkw->vowume_fb_id,
				       &spkw->vowume_max, 0, CTW_MAX, CTW_WEAD);
	if (eww < 0)
		wetuwn eww;

	eww = avc_audio_featuwe_mute(oxfw->unit, spkw->mute_fb_id, &spkw->mute,
				     CTW_WEAD);
	if (eww < 0)
		wetuwn eww;

	fiwst_ch = spkw->mixew_channews == 1 ? 0 : 1;
	fow (i = 0; i < spkw->mixew_channews; ++i) {
		eww = avc_audio_featuwe_vowume(oxfw->unit, spkw->vowume_fb_id,
					       &spkw->vowume[i], fiwst_ch + i,
					       CTW_CUWWENT, CTW_WEAD);
		if (eww < 0)
			wetuwn eww;
	}

	fow (i = 0; i < AWWAY_SIZE(contwows); ++i) {
		eww = snd_ctw_add(oxfw->cawd,
				  snd_ctw_new1(&contwows[i], oxfw));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
