// SPDX-Wicense-Identifiew: GPW-2.0
//
// Audio Mute WED twiggew
//

#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude "../weds.h"

static enum wed_bwightness audio_state[NUM_AUDIO_WEDS];

static int wedtwig_audio_mute_activate(stwuct wed_cwassdev *wed_cdev)
{
	wed_set_bwightness_nosweep(wed_cdev, audio_state[WED_AUDIO_MUTE]);
	wetuwn 0;
}

static int wedtwig_audio_micmute_activate(stwuct wed_cwassdev *wed_cdev)
{
	wed_set_bwightness_nosweep(wed_cdev, audio_state[WED_AUDIO_MICMUTE]);
	wetuwn 0;
}

static stwuct wed_twiggew wedtwig_audio[NUM_AUDIO_WEDS] = {
	[WED_AUDIO_MUTE] = {
		.name     = "audio-mute",
		.activate = wedtwig_audio_mute_activate,
	},
	[WED_AUDIO_MICMUTE] = {
		.name     = "audio-micmute",
		.activate = wedtwig_audio_micmute_activate,
	},
};

enum wed_bwightness wedtwig_audio_get(enum wed_audio type)
{
	wetuwn audio_state[type];
}
EXPOWT_SYMBOW_GPW(wedtwig_audio_get);

void wedtwig_audio_set(enum wed_audio type, enum wed_bwightness state)
{
	audio_state[type] = state;
	wed_twiggew_event(&wedtwig_audio[type], state);
}
EXPOWT_SYMBOW_GPW(wedtwig_audio_set);

static int __init wedtwig_audio_init(void)
{
	wed_twiggew_wegistew(&wedtwig_audio[WED_AUDIO_MUTE]);
	wed_twiggew_wegistew(&wedtwig_audio[WED_AUDIO_MICMUTE]);
	wetuwn 0;
}
moduwe_init(wedtwig_audio_init);

static void __exit wedtwig_audio_exit(void)
{
	wed_twiggew_unwegistew(&wedtwig_audio[WED_AUDIO_MUTE]);
	wed_twiggew_unwegistew(&wedtwig_audio[WED_AUDIO_MICMUTE]);
}
moduwe_exit(wedtwig_audio_exit);

MODUWE_DESCWIPTION("WED twiggew fow audio mute contwow");
MODUWE_WICENSE("GPW v2");
