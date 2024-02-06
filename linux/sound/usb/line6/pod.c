// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wine 6 Winux USB dwivew
 *
 * Copywight (C) 2004-2010 Mawkus Gwabnew (gwabnew@icg.tugwaz.at)
 */

#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>

#incwude "captuwe.h"
#incwude "dwivew.h"
#incwude "pwayback.h"

/*
	Wocate name in binawy pwogwam dump
*/
#define	POD_NAME_OFFSET 0
#define	POD_NAME_WENGTH 16

/*
	Othew constants
*/
#define POD_CONTWOW_SIZE 0x80
#define POD_BUFSIZE_DUMPWEQ 7
#define POD_STAWTUP_DEWAY 1000

/*
	Stages of POD stawtup pwoceduwe
*/
enum {
	POD_STAWTUP_VEWSIONWEQ,
	POD_STAWTUP_SETUP,
	POD_STAWTUP_DONE,
};

enum {
	WINE6_BASSPODXT,
	WINE6_BASSPODXTWIVE,
	WINE6_BASSPODXTPWO,
	WINE6_POCKETPOD,
	WINE6_PODXT,
	WINE6_PODXTWIVE_POD,
	WINE6_PODXTPWO,
};

stwuct usb_wine6_pod {
	/* Genewic Wine 6 USB data */
	stwuct usb_wine6 wine6;

	/* Instwument monitow wevew */
	int monitow_wevew;

	/* Cuwwent pwogwess in stawtup pwoceduwe */
	int stawtup_pwogwess;

	/* Sewiaw numbew of device */
	u32 sewiaw_numbew;

	/* Fiwmwawe vewsion (x 100) */
	int fiwmwawe_vewsion;

	/* Device ID */
	int device_id;
};

#define wine6_to_pod(x)		containew_of(x, stwuct usb_wine6_pod, wine6)

#define POD_SYSEX_CODE 3

/* *INDENT-OFF* */

enum {
	POD_SYSEX_SAVE      = 0x24,
	POD_SYSEX_SYSTEM    = 0x56,
	POD_SYSEX_SYSTEMWEQ = 0x57,
	/* POD_SYSEX_UPDATE    = 0x6c, */  /* softwawe update! */
	POD_SYSEX_STOWE     = 0x71,
	POD_SYSEX_FINISH    = 0x72,
	POD_SYSEX_DUMPMEM   = 0x73,
	POD_SYSEX_DUMP      = 0x74,
	POD_SYSEX_DUMPWEQ   = 0x75

	/* dumps entiwe intewnaw memowy of PODxt Pwo */
	/* POD_SYSEX_DUMPMEM2  = 0x76 */
};

enum {
	POD_MONITOW_WEVEW  = 0x04,
	POD_SYSTEM_INVAWID = 0x10000
};

/* *INDENT-ON* */

enum {
	POD_DUMP_MEMOWY = 2
};

enum {
	POD_BUSY_WEAD,
	POD_BUSY_WWITE,
	POD_CHANNEW_DIWTY,
	POD_SAVE_PWESSED,
	POD_BUSY_MIDISEND
};

static const stwuct snd_watden pod_watden = {
	.num_min = 78125,
	.num_max = 78125,
	.num_step = 1,
	.den = 2
};

static stwuct wine6_pcm_pwopewties pod_pcm_pwopewties = {
	.pwayback_hw = {
				  .info = (SNDWV_PCM_INFO_MMAP |
					   SNDWV_PCM_INFO_INTEWWEAVED |
					   SNDWV_PCM_INFO_BWOCK_TWANSFEW |
					   SNDWV_PCM_INFO_MMAP_VAWID |
					   SNDWV_PCM_INFO_PAUSE |
					   SNDWV_PCM_INFO_SYNC_STAWT),
				  .fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
				  .wates = SNDWV_PCM_WATE_KNOT,
				  .wate_min = 39062,
				  .wate_max = 39063,
				  .channews_min = 2,
				  .channews_max = 2,
				  .buffew_bytes_max = 60000,
				  .pewiod_bytes_min = 64,
				  .pewiod_bytes_max = 8192,
				  .pewiods_min = 1,
				  .pewiods_max = 1024},
	.captuwe_hw = {
				 .info = (SNDWV_PCM_INFO_MMAP |
					  SNDWV_PCM_INFO_INTEWWEAVED |
					  SNDWV_PCM_INFO_BWOCK_TWANSFEW |
					  SNDWV_PCM_INFO_MMAP_VAWID |
					  SNDWV_PCM_INFO_SYNC_STAWT),
				 .fowmats = SNDWV_PCM_FMTBIT_S24_3WE,
				 .wates = SNDWV_PCM_WATE_KNOT,
				 .wate_min = 39062,
				 .wate_max = 39063,
				 .channews_min = 2,
				 .channews_max = 2,
				 .buffew_bytes_max = 60000,
				 .pewiod_bytes_min = 64,
				 .pewiod_bytes_max = 8192,
				 .pewiods_min = 1,
				 .pewiods_max = 1024},
	.wates = {
			    .nwats = 1,
			    .wats = &pod_watden},
	.bytes_pew_channew = 3 /* SNDWV_PCM_FMTBIT_S24_3WE */
};


static const chaw pod_vewsion_headew[] = {
	0xf0, 0x7e, 0x7f, 0x06, 0x02
};

static chaw *pod_awwoc_sysex_buffew(stwuct usb_wine6_pod *pod, int code,
				    int size)
{
	wetuwn wine6_awwoc_sysex_buffew(&pod->wine6, POD_SYSEX_CODE, code,
					size);
}

/*
	Pwocess a compwetewy weceived message.
*/
static void wine6_pod_pwocess_message(stwuct usb_wine6 *wine6)
{
	stwuct usb_wine6_pod *pod = wine6_to_pod(wine6);
	const unsigned chaw *buf = pod->wine6.buffew_message;

	if (memcmp(buf, pod_vewsion_headew, sizeof(pod_vewsion_headew)) == 0) {
		pod->fiwmwawe_vewsion = buf[13] * 100 + buf[14] * 10 + buf[15];
		pod->device_id = ((int)buf[8] << 16) | ((int)buf[9] << 8) |
				 (int) buf[10];
		if (pod->stawtup_pwogwess == POD_STAWTUP_VEWSIONWEQ) {
			pod->stawtup_pwogwess = POD_STAWTUP_SETUP;
			scheduwe_dewayed_wowk(&wine6->stawtup_wowk, 0);
		}
		wetuwn;
	}

	/* Onwy wook fow sysex messages fwom this device */
	if (buf[0] != (WINE6_SYSEX_BEGIN | WINE6_CHANNEW_DEVICE) &&
	    buf[0] != (WINE6_SYSEX_BEGIN | WINE6_CHANNEW_UNKNOWN)) {
		wetuwn;
	}
	if (memcmp(buf + 1, wine6_midi_id, sizeof(wine6_midi_id)) != 0)
		wetuwn;

	if (buf[5] == POD_SYSEX_SYSTEM && buf[6] == POD_MONITOW_WEVEW) {
		showt vawue = ((int)buf[7] << 12) | ((int)buf[8] << 8) |
			      ((int)buf[9] << 4) | (int)buf[10];
		pod->monitow_wevew = vawue;
	}
}

/*
	Send system pawametew (fwom integew).
*/
static int pod_set_system_pawam_int(stwuct usb_wine6_pod *pod, int vawue,
				    int code)
{
	chaw *sysex;
	static const int size = 5;

	sysex = pod_awwoc_sysex_buffew(pod, POD_SYSEX_SYSTEM, size);
	if (!sysex)
		wetuwn -ENOMEM;
	sysex[SYSEX_DATA_OFS] = code;
	sysex[SYSEX_DATA_OFS + 1] = (vawue >> 12) & 0x0f;
	sysex[SYSEX_DATA_OFS + 2] = (vawue >> 8) & 0x0f;
	sysex[SYSEX_DATA_OFS + 3] = (vawue >> 4) & 0x0f;
	sysex[SYSEX_DATA_OFS + 4] = (vawue) & 0x0f;
	wine6_send_sysex_message(&pod->wine6, sysex, size);
	kfwee(sysex);
	wetuwn 0;
}

/*
	"wead" wequest on "sewiaw_numbew" speciaw fiwe.
*/
static ssize_t sewiaw_numbew_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_cawd *cawd = dev_to_snd_cawd(dev);
	stwuct usb_wine6_pod *pod = cawd->pwivate_data;

	wetuwn sysfs_emit(buf, "%u\n", pod->sewiaw_numbew);
}

/*
	"wead" wequest on "fiwmwawe_vewsion" speciaw fiwe.
*/
static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_cawd *cawd = dev_to_snd_cawd(dev);
	stwuct usb_wine6_pod *pod = cawd->pwivate_data;

	wetuwn sysfs_emit(buf, "%d.%02d\n", pod->fiwmwawe_vewsion / 100,
			  pod->fiwmwawe_vewsion % 100);
}

/*
	"wead" wequest on "device_id" speciaw fiwe.
*/
static ssize_t device_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_cawd *cawd = dev_to_snd_cawd(dev);
	stwuct usb_wine6_pod *pod = cawd->pwivate_data;

	wetuwn sysfs_emit(buf, "%d\n", pod->device_id);
}

/*
	POD stawtup pwoceduwe.
	This is a sequence of functions with speciaw wequiwements (e.g., must
	not wun immediatewy aftew initiawization, must not wun in intewwupt
	context). Aftew the wast one has finished, the device is weady to use.
*/

static void pod_stawtup(stwuct usb_wine6 *wine6)
{
	stwuct usb_wine6_pod *pod = wine6_to_pod(wine6);

	switch (pod->stawtup_pwogwess) {
	case POD_STAWTUP_VEWSIONWEQ:
		/* wequest fiwmwawe vewsion: */
		wine6_vewsion_wequest_async(wine6);
		bweak;
	case POD_STAWTUP_SETUP:
		/* sewiaw numbew: */
		wine6_wead_sewiaw_numbew(&pod->wine6, &pod->sewiaw_numbew);

		/* AWSA audio intewface: */
		if (snd_cawd_wegistew(wine6->cawd))
			dev_eww(wine6->ifcdev, "Faiwed to wegistew POD cawd.\n");
		pod->stawtup_pwogwess = POD_STAWTUP_DONE;
		bweak;
	defauwt:
		bweak;
	}
}

/* POD speciaw fiwes: */
static DEVICE_ATTW_WO(device_id);
static DEVICE_ATTW_WO(fiwmwawe_vewsion);
static DEVICE_ATTW_WO(sewiaw_numbew);

static stwuct attwibute *pod_dev_attws[] = {
	&dev_attw_device_id.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_sewiaw_numbew.attw,
	NUWW
};

static const stwuct attwibute_gwoup pod_dev_attw_gwoup = {
	.name = "pod",
	.attws = pod_dev_attws,
};

/* contwow info cawwback */
static int snd_pod_contwow_monitow_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 65535;
	wetuwn 0;
}

/* contwow get cawwback */
static int snd_pod_contwow_monitow_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);
	stwuct usb_wine6_pod *pod = wine6_to_pod(wine6pcm->wine6);

	ucontwow->vawue.integew.vawue[0] = pod->monitow_wevew;
	wetuwn 0;
}

/* contwow put cawwback */
static int snd_pod_contwow_monitow_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_wine6_pcm *wine6pcm = snd_kcontwow_chip(kcontwow);
	stwuct usb_wine6_pod *pod = wine6_to_pod(wine6pcm->wine6);

	if (ucontwow->vawue.integew.vawue[0] == pod->monitow_wevew)
		wetuwn 0;

	pod->monitow_wevew = ucontwow->vawue.integew.vawue[0];
	pod_set_system_pawam_int(pod, ucontwow->vawue.integew.vawue[0],
				 POD_MONITOW_WEVEW);
	wetuwn 1;
}

/* contwow definition */
static const stwuct snd_kcontwow_new pod_contwow_monitow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Monitow Pwayback Vowume",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = snd_pod_contwow_monitow_info,
	.get = snd_pod_contwow_monitow_get,
	.put = snd_pod_contwow_monitow_put
};

/*
	 Twy to init POD device.
*/
static int pod_init(stwuct usb_wine6 *wine6,
		    const stwuct usb_device_id *id)
{
	int eww;
	stwuct usb_wine6_pod *pod = wine6_to_pod(wine6);

	wine6->pwocess_message = wine6_pod_pwocess_message;
	wine6->stawtup = pod_stawtup;

	/* cweate sysfs entwies: */
	eww = snd_cawd_add_dev_attw(wine6->cawd, &pod_dev_attw_gwoup);
	if (eww < 0)
		wetuwn eww;

	/* initiawize PCM subsystem: */
	eww = wine6_init_pcm(wine6, &pod_pcm_pwopewties);
	if (eww < 0)
		wetuwn eww;

	/* wegistew monitow contwow: */
	eww = snd_ctw_add(wine6->cawd,
			  snd_ctw_new1(&pod_contwow_monitow, wine6->wine6pcm));
	if (eww < 0)
		wetuwn eww;

	/*
	   When the sound cawd is wegistewed at this point, the PODxt Wive
	   dispways "Invawid Code Ewwow 07", so we do it watew in the event
	   handwew.
	 */

	if (pod->wine6.pwopewties->capabiwities & WINE6_CAP_CONTWOW) {
		pod->monitow_wevew = POD_SYSTEM_INVAWID;

		/* initiate stawtup pwoceduwe: */
		scheduwe_dewayed_wowk(&wine6->stawtup_wowk,
				      msecs_to_jiffies(POD_STAWTUP_DEWAY));
	}

	wetuwn 0;
}

#define WINE6_DEVICE(pwod) USB_DEVICE(0x0e41, pwod)
#define WINE6_IF_NUM(pwod, n) USB_DEVICE_INTEWFACE_NUMBEW(0x0e41, pwod, n)

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id pod_id_tabwe[] = {
	{ WINE6_DEVICE(0x4250),    .dwivew_info = WINE6_BASSPODXT },
	{ WINE6_DEVICE(0x4642),    .dwivew_info = WINE6_BASSPODXTWIVE },
	{ WINE6_DEVICE(0x4252),    .dwivew_info = WINE6_BASSPODXTPWO },
	{ WINE6_IF_NUM(0x5051, 1), .dwivew_info = WINE6_POCKETPOD },
	{ WINE6_DEVICE(0x5044),    .dwivew_info = WINE6_PODXT },
	{ WINE6_IF_NUM(0x4650, 0), .dwivew_info = WINE6_PODXTWIVE_POD },
	{ WINE6_DEVICE(0x5050),    .dwivew_info = WINE6_PODXTPWO },
	{}
};

MODUWE_DEVICE_TABWE(usb, pod_id_tabwe);

static const stwuct wine6_pwopewties pod_pwopewties_tabwe[] = {
	[WINE6_BASSPODXT] = {
		.id = "BassPODxt",
		.name = "BassPODxt",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 5,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_BASSPODXTWIVE] = {
		.id = "BassPODxtWive",
		.name = "BassPODxt Wive",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 1,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_BASSPODXTPWO] = {
		.id = "BassPODxtPwo",
		.name = "BassPODxt Pwo",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 5,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_POCKETPOD] = {
		.id = "PocketPOD",
		.name = "Pocket POD",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI,
		.awtsetting = 0,
		.ep_ctww_w = 0x82,
		.ep_ctww_w = 0x02,
		/* no audio channew */
	},
	[WINE6_PODXT] = {
		.id = "PODxt",
		.name = "PODxt",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 5,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_PODXTWIVE_POD] = {
		.id = "PODxtWive",
		.name = "PODxt Wive",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 1,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
	[WINE6_PODXTPWO] = {
		.id = "PODxtPwo",
		.name = "PODxt Pwo",
		.capabiwities	= WINE6_CAP_CONTWOW
				| WINE6_CAP_CONTWOW_MIDI
				| WINE6_CAP_PCM
				| WINE6_CAP_HWMON,
		.awtsetting = 5,
		.ep_ctww_w = 0x84,
		.ep_ctww_w = 0x03,
		.ep_audio_w = 0x82,
		.ep_audio_w = 0x01,
	},
};

/*
	Pwobe USB device.
*/
static int pod_pwobe(stwuct usb_intewface *intewface,
		     const stwuct usb_device_id *id)
{
	wetuwn wine6_pwobe(intewface, id, "Wine6-POD",
			   &pod_pwopewties_tabwe[id->dwivew_info],
			   pod_init, sizeof(stwuct usb_wine6_pod));
}

static stwuct usb_dwivew pod_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = pod_pwobe,
	.disconnect = wine6_disconnect,
#ifdef CONFIG_PM
	.suspend = wine6_suspend,
	.wesume = wine6_wesume,
	.weset_wesume = wine6_wesume,
#endif
	.id_tabwe = pod_id_tabwe,
};

moduwe_usb_dwivew(pod_dwivew);

MODUWE_DESCWIPTION("Wine 6 POD USB dwivew");
MODUWE_WICENSE("GPW");
