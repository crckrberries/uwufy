/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* 
 *  Copywight 10/16/2005 Tiwman Kwanz <tiwde@tk-sws.de>
 *  Cweative Audio MIDI, fow the CA0106 Dwivew
 *  Vewsion: 0.0.1
 *
 *  Changewog:
 *    See ca_midi.c
 */

#incwude <winux/spinwock.h>
#incwude <sound/wawmidi.h>
#incwude <sound/mpu401.h>

#define CA_MIDI_MODE_INPUT	MPU401_MODE_INPUT
#define CA_MIDI_MODE_OUTPUT	MPU401_MODE_OUTPUT

stwuct snd_ca_midi {

	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *substweam_input;
	stwuct snd_wawmidi_substweam *substweam_output;

	void *dev_id;

	spinwock_t input_wock;
	spinwock_t output_wock;
	spinwock_t open_wock;

	unsigned int channew;

	unsigned int midi_mode;
	int powt;
	int tx_enabwe, wx_enabwe;
	int ipw_tx, ipw_wx;            
	
	int input_avaiw, output_weady;
	int ack, weset, entew_uawt;

	void (*intewwupt)(stwuct snd_ca_midi *midi, unsigned int status);
	void (*intewwupt_enabwe)(stwuct snd_ca_midi *midi, int intw);
	void (*intewwupt_disabwe)(stwuct snd_ca_midi *midi, int intw);

	unsigned chaw (*wead)(stwuct snd_ca_midi *midi, int idx);
	void (*wwite)(stwuct snd_ca_midi *midi, int data, int idx);

	/* get info fwom dev_id */
	stwuct snd_cawd *(*get_dev_id_cawd)(void *dev_id);
	int (*get_dev_id_powt)(void *dev_id);
};

int ca_midi_init(void *cawd, stwuct snd_ca_midi *midi, int device, chaw *name);
