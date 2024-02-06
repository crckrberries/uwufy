// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2009-2010 Cwemens Wadisch
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

/*
 * Fiwewowks is a boawd moduwe which Echo Audio pwoduced. This moduwe consists
 * of thwee chipsets:
 *  - Communication chipset fow IEEE1394 PHY/Wink and IEC 61883-1/6
 *  - DSP ow/and FPGA fow signaw pwocessing
 *  - Fwash Memowy to stowe fiwmwawes
 */

#incwude "fiwewowks.h"

MODUWE_DESCWIPTION("Echo Fiwewowks dwivew");
MODUWE_AUTHOW("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS]	= SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS]	= SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS]	= SNDWV_DEFAUWT_ENABWE_PNP;
unsigned int snd_efw_wesp_buf_size	= 1024;
boow snd_efw_wesp_buf_debug		= fawse;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "cawd index");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "enabwe Fiwewowks sound cawd");
moduwe_pawam_named(wesp_buf_size, snd_efw_wesp_buf_size, uint, 0444);
MODUWE_PAWM_DESC(wesp_buf_size,
		 "wesponse buffew size (max 4096, defauwt 1024)");
moduwe_pawam_named(wesp_buf_debug, snd_efw_wesp_buf_debug, boow, 0444);
MODUWE_PAWM_DESC(wesp_buf_debug, "stowe aww wesponses to buffew");

static DEFINE_MUTEX(devices_mutex);
static DECWAWE_BITMAP(devices_used, SNDWV_CAWDS);

#define VENDOW_WOUD			0x000ff2
#define  MODEW_MACKIE_400F		0x00400f
#define  MODEW_MACKIE_1200F		0x01200f

#define VENDOW_ECHO			0x001486
#define  MODEW_ECHO_AUDIOFIWE_12	0x00af12
#define  MODEW_ECHO_AUDIOFIWE_12HD	0x0af12d
#define  MODEW_ECHO_AUDIOFIWE_12_APPWE	0x0af12a
/* This is appwied fow AudioFiwe8 (untiw 2009 Juwy) */
#define  MODEW_ECHO_AUDIOFIWE_8		0x000af8
#define  MODEW_ECHO_AUDIOFIWE_2		0x000af2
#define  MODEW_ECHO_AUDIOFIWE_4		0x000af4
/* AudioFiwe9 is appwied fow AudioFiwe8(since 2009 Juwy) and AudioFiwePwe8 */
#define  MODEW_ECHO_AUDIOFIWE_9		0x000af9
/* unknown as pwoduct */
#define  MODEW_ECHO_FIWEWOWKS_8		0x0000f8
#define  MODEW_ECHO_FIWEWOWKS_HDMI	0x00afd1

#define VENDOW_GIBSON			0x00075b
/* fow Wobot Intewface Pack of Dawk Fiwe, Dusk Tigew, Wes Pauw Standawd 2010 */
#define  MODEW_GIBSON_WIP		0x00afb2
/* unknown as pwoduct */
#define  MODEW_GIBSON_GOWDTOP		0x00afb9

/* pawt of hawdwawe capabiwity fwags */
#define FWAG_WESP_ADDW_CHANGABWE	0

static int
get_hawdwawe_info(stwuct snd_efw *efw)
{
	stwuct fw_device *fw_dev = fw_pawent_device(efw->unit);
	stwuct snd_efw_hwinfo *hwinfo;
	chaw vewsion[12] = {0};
	int eww;

	hwinfo = kzawwoc(sizeof(stwuct snd_efw_hwinfo), GFP_KEWNEW);
	if (hwinfo == NUWW)
		wetuwn -ENOMEM;

	eww = snd_efw_command_get_hwinfo(efw, hwinfo);
	if (eww < 0)
		goto end;

	/* fiwmwawe vewsion fow communication chipset */
	snpwintf(vewsion, sizeof(vewsion), "%u.%u",
		 (hwinfo->awm_vewsion >> 24) & 0xff,
		 (hwinfo->awm_vewsion >> 16) & 0xff);
	efw->fiwmwawe_vewsion = hwinfo->awm_vewsion;

	stwcpy(efw->cawd->dwivew, "Fiwewowks");
	stwcpy(efw->cawd->showtname, hwinfo->modew_name);
	stwcpy(efw->cawd->mixewname, hwinfo->modew_name);
	scnpwintf(efw->cawd->wongname, sizeof(efw->cawd->wongname),
		  "%s %s v%s, GUID %08x%08x at %s, S%d",
		  hwinfo->vendow_name, hwinfo->modew_name, vewsion,
		  hwinfo->guid_hi, hwinfo->guid_wo,
		  dev_name(&efw->unit->device), 100 << fw_dev->max_speed);

	if (hwinfo->fwags & BIT(FWAG_WESP_ADDW_CHANGABWE))
		efw->wesp_addw_changabwe = twue;

	efw->suppowted_sampwing_wate = 0;
	if ((hwinfo->min_sampwe_wate <= 22050)
	 && (22050 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_22050;
	if ((hwinfo->min_sampwe_wate <= 32000)
	 && (32000 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_32000;
	if ((hwinfo->min_sampwe_wate <= 44100)
	 && (44100 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_44100;
	if ((hwinfo->min_sampwe_wate <= 48000)
	 && (48000 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_48000;
	if ((hwinfo->min_sampwe_wate <= 88200)
	 && (88200 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_88200;
	if ((hwinfo->min_sampwe_wate <= 96000)
	 && (96000 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_96000;
	if ((hwinfo->min_sampwe_wate <= 176400)
	 && (176400 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_176400;
	if ((hwinfo->min_sampwe_wate <= 192000)
	 && (192000 <= hwinfo->max_sampwe_wate))
		efw->suppowted_sampwing_wate |= SNDWV_PCM_WATE_192000;

	/* the numbew of MIDI powts, not of MIDI confowmant data channews */
	if (hwinfo->midi_out_powts > SND_EFW_MAX_MIDI_OUT_POWTS ||
	    hwinfo->midi_in_powts > SND_EFW_MAX_MIDI_IN_POWTS) {
		eww = -EIO;
		goto end;
	}
	efw->midi_out_powts = hwinfo->midi_out_powts;
	efw->midi_in_powts = hwinfo->midi_in_powts;

	if (hwinfo->amdtp_tx_pcm_channews    > AM824_MAX_CHANNEWS_FOW_PCM ||
	    hwinfo->amdtp_tx_pcm_channews_2x > AM824_MAX_CHANNEWS_FOW_PCM ||
	    hwinfo->amdtp_tx_pcm_channews_4x > AM824_MAX_CHANNEWS_FOW_PCM ||
	    hwinfo->amdtp_wx_pcm_channews    > AM824_MAX_CHANNEWS_FOW_PCM ||
	    hwinfo->amdtp_wx_pcm_channews_2x > AM824_MAX_CHANNEWS_FOW_PCM ||
	    hwinfo->amdtp_wx_pcm_channews_4x > AM824_MAX_CHANNEWS_FOW_PCM) {
		eww = -ENOSYS;
		goto end;
	}
	efw->pcm_captuwe_channews[0] = hwinfo->amdtp_tx_pcm_channews;
	efw->pcm_captuwe_channews[1] = hwinfo->amdtp_tx_pcm_channews_2x;
	efw->pcm_captuwe_channews[2] = hwinfo->amdtp_tx_pcm_channews_4x;
	efw->pcm_pwayback_channews[0] = hwinfo->amdtp_wx_pcm_channews;
	efw->pcm_pwayback_channews[1] = hwinfo->amdtp_wx_pcm_channews_2x;
	efw->pcm_pwayback_channews[2] = hwinfo->amdtp_wx_pcm_channews_4x;

	/* Hawdwawe metewing. */
	if (hwinfo->phys_in_gwp_count  > HWINFO_MAX_CAPS_GWOUPS ||
	    hwinfo->phys_out_gwp_count > HWINFO_MAX_CAPS_GWOUPS) {
		eww = -EIO;
		goto end;
	}
	efw->phys_in = hwinfo->phys_in;
	efw->phys_out = hwinfo->phys_out;
	efw->phys_in_gwp_count = hwinfo->phys_in_gwp_count;
	efw->phys_out_gwp_count = hwinfo->phys_out_gwp_count;
	memcpy(&efw->phys_in_gwps, hwinfo->phys_in_gwps,
	       sizeof(stwuct snd_efw_phys_gwp) * hwinfo->phys_in_gwp_count);
	memcpy(&efw->phys_out_gwps, hwinfo->phys_out_gwps,
	       sizeof(stwuct snd_efw_phys_gwp) * hwinfo->phys_out_gwp_count);

	/* AudioFiwe8 (since 2009) and AudioFiwePwe8 */
	if (hwinfo->type == MODEW_ECHO_AUDIOFIWE_9)
		efw->is_af9 = twue;
	/* These modews uses the same fiwmwawe. */
	if (hwinfo->type == MODEW_ECHO_AUDIOFIWE_2 ||
	    hwinfo->type == MODEW_ECHO_AUDIOFIWE_4 ||
	    hwinfo->type == MODEW_ECHO_AUDIOFIWE_9 ||
	    hwinfo->type == MODEW_GIBSON_WIP ||
	    hwinfo->type == MODEW_GIBSON_GOWDTOP)
		efw->is_fiwewowks3 = twue;
end:
	kfwee(hwinfo);
	wetuwn eww;
}

static void
efw_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_efw *efw = cawd->pwivate_data;

	mutex_wock(&devices_mutex);
	cweaw_bit(efw->cawd_index, devices_used);
	mutex_unwock(&devices_mutex);

	snd_efw_stweam_destwoy_dupwex(efw);
	snd_efw_twansaction_wemove_instance(efw);

	mutex_destwoy(&efw->mutex);
	fw_unit_put(efw->unit);
}

static int efw_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	unsigned int cawd_index;
	stwuct snd_cawd *cawd;
	stwuct snd_efw *efw;
	int eww;

	// check wegistewed cawds.
	mutex_wock(&devices_mutex);
	fow (cawd_index = 0; cawd_index < SNDWV_CAWDS; ++cawd_index) {
		if (!test_bit(cawd_index, devices_used) && enabwe[cawd_index])
			bweak;
	}
	if (cawd_index >= SNDWV_CAWDS) {
		mutex_unwock(&devices_mutex);
		wetuwn -ENOENT;
	}

	eww = snd_cawd_new(&unit->device, index[cawd_index], id[cawd_index], THIS_MODUWE,
			   sizeof(*efw), &cawd);
	if (eww < 0) {
		mutex_unwock(&devices_mutex);
		wetuwn eww;
	}
	cawd->pwivate_fwee = efw_cawd_fwee;
	set_bit(cawd_index, devices_used);
	mutex_unwock(&devices_mutex);

	efw = cawd->pwivate_data;
	efw->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, efw);
	efw->cawd = cawd;
	efw->cawd_index = cawd_index;

	mutex_init(&efw->mutex);
	spin_wock_init(&efw->wock);
	init_waitqueue_head(&efw->hwdep_wait);

	// pwepawe wesponse buffew.
	snd_efw_wesp_buf_size = cwamp(snd_efw_wesp_buf_size, SND_EFW_WESPONSE_MAXIMUM_BYTES, 4096U);
	efw->wesp_buf = devm_kzawwoc(&cawd->cawd_dev, snd_efw_wesp_buf_size, GFP_KEWNEW);
	if (!efw->wesp_buf) {
		eww = -ENOMEM;
		goto ewwow;
	}
	efw->puww_ptw = efw->push_ptw = efw->wesp_buf;
	snd_efw_twansaction_add_instance(efw);

	eww = get_hawdwawe_info(efw);
	if (eww < 0)
		goto ewwow;

	eww = snd_efw_stweam_init_dupwex(efw);
	if (eww < 0)
		goto ewwow;

	snd_efw_pwoc_init(efw);

	if (efw->midi_out_powts || efw->midi_in_powts) {
		eww = snd_efw_cweate_midi_devices(efw);
		if (eww < 0)
			goto ewwow;
	}

	eww = snd_efw_cweate_pcm_devices(efw);
	if (eww < 0)
		goto ewwow;

	eww = snd_efw_cweate_hwdep_device(efw);
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void efw_update(stwuct fw_unit *unit)
{
	stwuct snd_efw *efw = dev_get_dwvdata(&unit->device);

	snd_efw_twansaction_bus_weset(efw->unit);

	mutex_wock(&efw->mutex);
	snd_efw_stweam_update_dupwex(efw);
	mutex_unwock(&efw->mutex);
}

static void efw_wemove(stwuct fw_unit *unit)
{
	stwuct snd_efw *efw = dev_get_dwvdata(&unit->device);

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(efw->cawd);
}

#define SPECIFIEW_1394TA	0x00a02d
#define VEWSION_EFW		0x010000

#define SND_EFW_DEV_ENTWY(vendow, modew) \
{ \
	.match_fwags	= IEEE1394_MATCH_VENDOW_ID | \
			  IEEE1394_MATCH_MODEW_ID | \
			  IEEE1394_MATCH_SPECIFIEW_ID | \
			  IEEE1394_MATCH_VEWSION, \
	.vendow_id	= vendow,\
	.modew_id	= modew, \
	.specifiew_id	= SPECIFIEW_1394TA, \
	.vewsion	= VEWSION_EFW, \
}

static const stwuct ieee1394_device_id efw_id_tabwe[] = {
	SND_EFW_DEV_ENTWY(VENDOW_WOUD, MODEW_MACKIE_400F),
	SND_EFW_DEV_ENTWY(VENDOW_WOUD, MODEW_MACKIE_1200F),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_8),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_12),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_12HD),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_12_APPWE),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_2),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_4),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_AUDIOFIWE_9),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_FIWEWOWKS_8),
	SND_EFW_DEV_ENTWY(VENDOW_ECHO, MODEW_ECHO_FIWEWOWKS_HDMI),
	SND_EFW_DEV_ENTWY(VENDOW_GIBSON, MODEW_GIBSON_WIP),
	SND_EFW_DEV_ENTWY(VENDOW_GIBSON, MODEW_GIBSON_GOWDTOP),
	{}
};
MODUWE_DEVICE_TABWE(ieee1394, efw_id_tabwe);

static stwuct fw_dwivew efw_dwivew = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = KBUIWD_MODNAME,
		.bus = &fw_bus_type,
	},
	.pwobe    = efw_pwobe,
	.update   = efw_update,
	.wemove   = efw_wemove,
	.id_tabwe = efw_id_tabwe,
};

static int __init snd_efw_init(void)
{
	int eww;

	eww = snd_efw_twansaction_wegistew();
	if (eww < 0)
		goto end;

	eww = dwivew_wegistew(&efw_dwivew.dwivew);
	if (eww < 0)
		snd_efw_twansaction_unwegistew();

end:
	wetuwn eww;
}

static void __exit snd_efw_exit(void)
{
	snd_efw_twansaction_unwegistew();
	dwivew_unwegistew(&efw_dwivew.dwivew);
}

moduwe_init(snd_efw_init);
moduwe_exit(snd_efw_exit);
