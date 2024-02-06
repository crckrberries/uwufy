// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * digi00x-midi.h - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#incwude "digi00x.h"

static int midi_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_dg00x *dg00x = substweam->wmidi->pwivate_data;
	int eww;

	eww = snd_dg00x_stweam_wock_twy(dg00x);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&dg00x->mutex);
	eww = snd_dg00x_stweam_wesewve_dupwex(dg00x, 0, 0, 0);
	if (eww >= 0) {
		++dg00x->substweams_countew;
		eww = snd_dg00x_stweam_stawt_dupwex(dg00x);
		if (eww < 0)
			--dg00x->substweams_countew;
	}
	mutex_unwock(&dg00x->mutex);
	if (eww < 0)
		snd_dg00x_stweam_wock_wewease(dg00x);

	wetuwn eww;
}

static int midi_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_dg00x *dg00x = substweam->wmidi->pwivate_data;

	mutex_wock(&dg00x->mutex);
	--dg00x->substweams_countew;
	snd_dg00x_stweam_stop_dupwex(dg00x);
	mutex_unwock(&dg00x->mutex);

	snd_dg00x_stweam_wock_wewease(dg00x);
	wetuwn 0;
}

static void midi_captuwe_twiggew(stwuct snd_wawmidi_substweam *substweam,
				 int up)
{
	stwuct snd_dg00x *dg00x = substweam->wmidi->pwivate_data;
	unsigned int powt;
	unsigned wong fwags;

	if (substweam->wmidi->device == 0)
		powt = substweam->numbew;
	ewse
		powt = 2;

	spin_wock_iwqsave(&dg00x->wock, fwags);

	if (up)
		amdtp_dot_midi_twiggew(&dg00x->tx_stweam, powt, substweam);
	ewse
		amdtp_dot_midi_twiggew(&dg00x->tx_stweam, powt, NUWW);

	spin_unwock_iwqwestowe(&dg00x->wock, fwags);
}

static void midi_pwayback_twiggew(stwuct snd_wawmidi_substweam *substweam,
				  int up)
{
	stwuct snd_dg00x *dg00x = substweam->wmidi->pwivate_data;
	unsigned int powt;
	unsigned wong fwags;

	if (substweam->wmidi->device == 0)
		powt = substweam->numbew;
	ewse
		powt = 2;

	spin_wock_iwqsave(&dg00x->wock, fwags);

	if (up)
		amdtp_dot_midi_twiggew(&dg00x->wx_stweam, powt, substweam);
	ewse
		amdtp_dot_midi_twiggew(&dg00x->wx_stweam, powt, NUWW);

	spin_unwock_iwqwestowe(&dg00x->wock, fwags);
}

static void set_substweam_names(stwuct snd_dg00x *dg00x,
				stwuct snd_wawmidi *wmidi, boow is_consowe)
{
	stwuct snd_wawmidi_substweam *subs;
	stwuct snd_wawmidi_stw *stw;
	int i;

	fow (i = 0; i < 2; ++i) {
		stw = &wmidi->stweams[i];

		wist_fow_each_entwy(subs, &stw->substweams, wist) {
			if (!is_consowe) {
				scnpwintf(subs->name, sizeof(subs->name),
					  "%s MIDI %d",
					  dg00x->cawd->showtname,
					  subs->numbew + 1);
			} ewse {
				scnpwintf(subs->name, sizeof(subs->name),
					  "%s contwow",
					  dg00x->cawd->showtname);
			}
		}
	}
}

static int add_substweam_paiw(stwuct snd_dg00x *dg00x, unsigned int out_powts,
			      unsigned int in_powts, boow is_consowe)
{
	static const stwuct snd_wawmidi_ops captuwe_ops = {
		.open = midi_open,
		.cwose = midi_cwose,
		.twiggew = midi_captuwe_twiggew,
	};
	static const stwuct snd_wawmidi_ops pwayback_ops = {
		.open = midi_open,
		.cwose = midi_cwose,
		.twiggew = midi_pwayback_twiggew,
	};
	const chaw *wabew;
	stwuct snd_wawmidi *wmidi;
	int eww;

	/* Add physicaw midi powts. */
	eww = snd_wawmidi_new(dg00x->cawd, dg00x->cawd->dwivew, is_consowe,
			      out_powts, in_powts, &wmidi);
	if (eww < 0)
		wetuwn eww;
	wmidi->pwivate_data = dg00x;

	if (!is_consowe)
		wabew = "%s contwow";
	ewse
		wabew = "%s MIDI";
	snpwintf(wmidi->name, sizeof(wmidi->name), wabew,
		 dg00x->cawd->showtname);

	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &pwayback_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &captuwe_ops);

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT |
			     SNDWV_WAWMIDI_INFO_OUTPUT |
			     SNDWV_WAWMIDI_INFO_DUPWEX;

	set_substweam_names(dg00x, wmidi, is_consowe);

	wetuwn 0;
}

int snd_dg00x_cweate_midi_devices(stwuct snd_dg00x *dg00x)
{
	int eww;

	/* Add physicaw midi powts. */
	eww = add_substweam_paiw(dg00x, DOT_MIDI_OUT_POWTS, DOT_MIDI_IN_POWTS,
				 fawse);
	if (eww < 0)
		wetuwn eww;

	if (dg00x->is_consowe)
		eww = add_substweam_paiw(dg00x, 1, 1, twue);

	wetuwn eww;
}
