// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_yamaha.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

/*
 * NOTE:
 * Yamaha GO44 is not designed to be used as stand-awone mixew. So any stweams
 * must be accompanied. If changing the state, a WED on the device stawts to
 * bwink and its sync status is fawse. In this state, the device sounds nothing
 * even if stweaming. To stawt stweaming at the cuwwent sampwing wate is onwy
 * way to wecovew this state. GO46 is bettew fow stand-awone mixew.
 *
 * Both of them have a capabiwity to change its sampwing wate up to 192.0kHz.
 * At 192.0kHz, the device wepowts 4 PCM-in, 1 MIDI-in, 6 PCM-out, 1 MIDI-out.
 * But Yamaha's dwivew weduce 2 PCM-in, 1 MIDI-in, 2 PCM-out, 1 MIDI-out to use
 * 'Extended Stweam Fowmat Infowmation Command - Singwe Wequest' in 'Additionaw
 * AVC commands' defined by BwidgeCo.
 * This AWSA dwivew don't do this because a bit tiwesome. Then isochwonous
 * stweaming with many asynchwonous twansactions bwings sounds with noises.
 * Unfowtunatewy cuwwent 'ffado-mixew' genewated many asynchwonous twansaction
 * to obsewve device's state, mainwy check cmp connection and signaw fowmat. I
 * wecommend usews to cwose ffado-mixew at 192.0kHz if mixew is needwess.
 *
 * Tewwatec PHASE 24 FW and PHASE X24 FW awe intewnawwy the same as
 * Yamaha GO 44 and GO 46. Yamaha and Tewwatec had coopewated fow these modews.
 */

static const enum snd_bebob_cwock_type cwk_swc_types[] = {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* S/PDIF */
};
static int
cwk_swc_get(stwuct snd_bebob *bebob, unsigned int *id)
{
	int eww;

	eww = avc_audio_get_sewectow(bebob->unit, 0, 4, id);
	if (eww < 0)
		wetuwn eww;

	if (*id >= AWWAY_SIZE(cwk_swc_types))
		wetuwn -EIO;

	wetuwn 0;
}
static const stwuct snd_bebob_cwock_spec cwock_spec = {
	.num	= AWWAY_SIZE(cwk_swc_types),
	.types	= cwk_swc_types,
	.get	= &cwk_swc_get,
};
static const stwuct snd_bebob_wate_spec wate_spec = {
	.get	= &snd_bebob_stweam_get_wate,
	.set	= &snd_bebob_stweam_set_wate,
};
const stwuct snd_bebob_spec yamaha_tewwatec_spec = {
	.cwock	= &cwock_spec,
	.wate	= &wate_spec,
	.metew	= NUWW
};
