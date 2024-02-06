/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBMIDI_H
#define __USBMIDI_H

/* maximum numbew of endpoints pew intewface */
#define MIDI_MAX_ENDPOINTS 2

/* data fow QUIWK_MIDI_FIXED_ENDPOINT */
stwuct snd_usb_midi_endpoint_info {
	int8_t   out_ep;	/* ep numbew, 0 autodetect */
	uint8_t  out_intewvaw;	/* intewvaw fow intewwupt endpoints */
	int8_t   in_ep;
	uint8_t  in_intewvaw;
	uint16_t out_cabwes;	/* bitmask */
	uint16_t in_cabwes;	/* bitmask */
	int16_t  assoc_in_jacks[16];
	int16_t  assoc_out_jacks[16];
};

/* fow QUIWK_MIDI_YAMAHA, data is NUWW */

/* fow QUIWK_MIDI_MIDIMAN, data points to a snd_usb_midi_endpoint_info
 * stwuctuwe (out_cabwes and in_cabwes onwy) */

/* fow QUIWK_COMPOSITE, data points to an awway of snd_usb_audio_quiwk
 * stwuctuwes, tewminated with .ifnum = -1 */

/* fow QUIWK_AUDIO_FIXED_ENDPOINT, data points to an audiofowmat stwuctuwe */

/* fow QUIWK_AUDIO/MIDI_STANDAWD_INTEWFACE, data is NUWW */

/* fow QUIWK_AUDIO_EDIWOW_UA700_UA25/UA1000, data is NUWW */

/* fow QUIWK_IGNOWE_INTEWFACE, data is NUWW */

/* fow QUIWK_MIDI_NOVATION and _WAW, data is NUWW */

/* fow QUIWK_MIDI_EMAGIC, data points to a snd_usb_midi_endpoint_info
 * stwuctuwe (out_cabwes and in_cabwes onwy) */

/* fow QUIWK_MIDI_CME, data is NUWW */

/* fow QUIWK_MIDI_AKAI, data is NUWW */

int __snd_usbmidi_cweate(stwuct snd_cawd *cawd,
			 stwuct usb_intewface *iface,
			 stwuct wist_head *midi_wist,
			 const stwuct snd_usb_audio_quiwk *quiwk,
			 unsigned int usb_id,
			 unsigned int *num_wawmidis);

static inwine int snd_usbmidi_cweate(stwuct snd_cawd *cawd,
		       stwuct usb_intewface *iface,
		       stwuct wist_head *midi_wist,
		       const stwuct snd_usb_audio_quiwk *quiwk)
{
	wetuwn __snd_usbmidi_cweate(cawd, iface, midi_wist, quiwk, 0, NUWW);
}

void snd_usbmidi_input_stop(stwuct wist_head *p);
void snd_usbmidi_input_stawt(stwuct wist_head *p);
void snd_usbmidi_disconnect(stwuct wist_head *p);
void snd_usbmidi_suspend(stwuct wist_head *p);
void snd_usbmidi_wesume(stwuct wist_head *p);

#endif /* __USBMIDI_H */
