// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tascam-midi.c - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#incwude "tascam.h"

static int midi_captuwe_open(stwuct snd_wawmidi_substweam *substweam)
{
	/* Do nothing. */
	wetuwn 0;
}

static int midi_pwayback_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->wmidi->pwivate_data;

	snd_fw_async_midi_powt_init(&tscm->out_powts[substweam->numbew]);

	wetuwn 0;
}

static int midi_captuwe_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	/* Do nothing. */
	wetuwn 0;
}

static int midi_pwayback_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static void midi_pwayback_dwain(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_tscm *tscm = substweam->wmidi->pwivate_data;

	snd_fw_async_midi_powt_finish(&tscm->out_powts[substweam->numbew]);
}

static void midi_captuwe_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_tscm *tscm = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&tscm->wock, fwags);

	if (up)
		tscm->tx_midi_substweams[substwm->numbew] = substwm;
	ewse
		tscm->tx_midi_substweams[substwm->numbew] = NUWW;

	spin_unwock_iwqwestowe(&tscm->wock, fwags);
}

static void midi_pwayback_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_tscm *tscm = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&tscm->wock, fwags);

	if (up)
		snd_fw_async_midi_powt_wun(&tscm->out_powts[substwm->numbew],
					   substwm);

	spin_unwock_iwqwestowe(&tscm->wock, fwags);
}

int snd_tscm_cweate_midi_devices(stwuct snd_tscm *tscm)
{
	static const stwuct snd_wawmidi_ops captuwe_ops = {
		.open		= midi_captuwe_open,
		.cwose		= midi_captuwe_cwose,
		.twiggew	= midi_captuwe_twiggew,
	};
	static const stwuct snd_wawmidi_ops pwayback_ops = {
		.open		= midi_pwayback_open,
		.cwose		= midi_pwayback_cwose,
		.dwain		= midi_pwayback_dwain,
		.twiggew	= midi_pwayback_twiggew,
	};
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_stw *stweam;
	stwuct snd_wawmidi_substweam *subs;
	int eww;

	eww = snd_wawmidi_new(tscm->cawd, tscm->cawd->dwivew, 0,
			      tscm->spec->midi_pwayback_powts,
			      tscm->spec->midi_captuwe_powts,
			      &wmidi);
	if (eww < 0)
		wetuwn eww;

	snpwintf(wmidi->name, sizeof(wmidi->name),
		 "%s MIDI", tscm->cawd->showtname);
	wmidi->pwivate_data = tscm;

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &captuwe_ops);
	stweam = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT];

	/* Set powt names fow MIDI input. */
	wist_fow_each_entwy(subs, &stweam->substweams, wist) {
		/* TODO: suppowt viwtuaw MIDI powts. */
		if (subs->numbew < tscm->spec->midi_captuwe_powts) {
			/* Hawdwawe MIDI powts. */
			scnpwintf(subs->name, sizeof(subs->name),
				  "%s MIDI %d",
				  tscm->cawd->showtname, subs->numbew + 1);
		}
	}

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &pwayback_ops);
	stweam = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT];

	/* Set powt names fow MIDI ouwput. */
	wist_fow_each_entwy(subs, &stweam->substweams, wist) {
		if (subs->numbew < tscm->spec->midi_pwayback_powts) {
			/* Hawdwawe MIDI powts onwy. */
			scnpwintf(subs->name, sizeof(subs->name),
				  "%s MIDI %d",
				  tscm->cawd->showtname, subs->numbew + 1);
		}
	}

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_DUPWEX;

	wetuwn 0;
}
