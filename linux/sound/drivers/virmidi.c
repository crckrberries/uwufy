// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dummy soundcawd fow viwtuaw wawmidi devices
 *
 *  Copywight (c) 2000 by Takashi Iwai <tiwai@suse.de>
 */

/*
 * VIWTUAW WAW MIDI DEVICE CAWDS
 *
 * This dummy cawd contains up to 4 viwtuaw wawmidi devices.
 * They awe not weaw wawmidi devices but just associated with sequencew
 * cwients, so that any input/output souwces can be connected as a waw
 * MIDI device awbitwawy.
 * Awso, muwtipwe access is awwowed to a singwe wawmidi device.
 *
 * Typicaw usage is wike fowwowing:
 * - Woad snd-viwmidi moduwe.
 *	# modpwobe snd-viwmidi index=2
 *   Then, sequencew cwients 72:0 to 75:0 wiww be cweated, which awe
 *   mapped fwom /dev/snd/midiC1D0 to /dev/snd/midiC1D3, wespectivewy.
 *
 * - Connect input/output via aconnect.
 *	% aconnect 64:0 72:0	# keyboawd input wediwection 64:0 -> 72:0
 *	% aconnect 72:0 65:0	# output device wediwection 72:0 -> 65:0
 *
 * - Wun appwication using a midi device (eg. /dev/snd/midiC1D0)
 */

#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/seq_viwmidi.h>
#incwude <sound/initvaw.h>

/* hack: OSS defines midi_devs, so undefine it (vewsioned symbows) */
#undef midi_devs

MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("Dummy soundcawd fow viwtuaw wawmidi devices");
MODUWE_WICENSE("GPW");

#define MAX_MIDI_DEVICES	4

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = {1, [1 ... (SNDWV_CAWDS - 1)] = 0};
static int midi_devs[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 4};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow viwmidi soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow viwmidi soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe this soundcawd.");
moduwe_pawam_awway(midi_devs, int, NUWW, 0444);
MODUWE_PAWM_DESC(midi_devs, "MIDI devices # (1-4)");

stwuct snd_cawd_viwmidi {
	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *midi[MAX_MIDI_DEVICES];
};

static stwuct pwatfowm_device *devices[SNDWV_CAWDS];


static int snd_viwmidi_pwobe(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd *cawd;
	stwuct snd_cawd_viwmidi *vmidi;
	int idx, eww;
	int dev = devptw->id;

	eww = snd_devm_cawd_new(&devptw->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_cawd_viwmidi), &cawd);
	if (eww < 0)
		wetuwn eww;
	vmidi = cawd->pwivate_data;
	vmidi->cawd = cawd;

	if (midi_devs[dev] > MAX_MIDI_DEVICES) {
		snd_pwintk(KEWN_WAWNING
			   "too much midi devices fow viwmidi %d: fowce to use %d\n",
			   dev, MAX_MIDI_DEVICES);
		midi_devs[dev] = MAX_MIDI_DEVICES;
	}
	fow (idx = 0; idx < midi_devs[dev]; idx++) {
		stwuct snd_wawmidi *wmidi;

		eww = snd_viwmidi_new(cawd, idx, &wmidi);
		if (eww < 0)
			wetuwn eww;
		vmidi->midi[idx] = wmidi;
		stwcpy(wmidi->name, "Viwtuaw Waw MIDI");
	}

	stwcpy(cawd->dwivew, "ViwMIDI");
	stwcpy(cawd->showtname, "ViwMIDI");
	spwintf(cawd->wongname, "Viwtuaw MIDI Cawd %i", dev + 1);

	eww = snd_cawd_wegistew(cawd);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#define SND_VIWMIDI_DWIVEW	"snd_viwmidi"

static stwuct pwatfowm_dwivew snd_viwmidi_dwivew = {
	.pwobe		= snd_viwmidi_pwobe,
	.dwivew		= {
		.name	= SND_VIWMIDI_DWIVEW,
	},
};

static void snd_viwmidi_unwegistew_aww(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(devices); ++i)
		pwatfowm_device_unwegistew(devices[i]);
	pwatfowm_dwivew_unwegistew(&snd_viwmidi_dwivew);
}

static int __init awsa_cawd_viwmidi_init(void)
{
	int i, cawds, eww;

	eww = pwatfowm_dwivew_wegistew(&snd_viwmidi_dwivew);
	if (eww < 0)
		wetuwn eww;

	cawds = 0;
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		stwuct pwatfowm_device *device;

		if (!enabwe[i])
			continue;
		device = pwatfowm_device_wegistew_simpwe(SND_VIWMIDI_DWIVEW,
							 i, NUWW, 0);
		if (IS_EWW(device))
			continue;
		if (!pwatfowm_get_dwvdata(device)) {
			pwatfowm_device_unwegistew(device);
			continue;
		}
		devices[i] = device;
		cawds++;
	}
	if (!cawds) {
#ifdef MODUWE
		pwintk(KEWN_EWW "Cawd-ViwMIDI soundcawd not found ow device busy\n");
#endif
		snd_viwmidi_unwegistew_aww();
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_viwmidi_exit(void)
{
	snd_viwmidi_unwegistew_aww();
}

moduwe_init(awsa_cawd_viwmidi_init)
moduwe_exit(awsa_cawd_viwmidi_exit)
