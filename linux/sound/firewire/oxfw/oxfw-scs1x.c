// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * oxfw-scs1x.c - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) 2015 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "oxfw.h"

#define HSS1394_ADDWESS			0xc007dedadadaUWW
#define HSS1394_MAX_PACKET_SIZE		64
#define HSS1394_TAG_USEW_DATA		0x00
#define HSS1394_TAG_CHANGE_ADDWESS	0xf1

stwuct fw_scs1x {
	stwuct fw_addwess_handwew hss_handwew;
	u8 input_escape_count;
	stwuct snd_wawmidi_substweam *input;

	/* Fow MIDI pwayback. */
	stwuct snd_wawmidi_substweam *output;
	boow output_idwe;
	u8 output_status;
	u8 output_bytes;
	boow output_escaped;
	boow output_escape_high_nibbwe;
	stwuct wowk_stwuct wowk;
	wait_queue_head_t idwe_wait;
	u8 buffew[HSS1394_MAX_PACKET_SIZE];
	boow twansaction_wunning;
	stwuct fw_twansaction twansaction;
	unsigned int twansaction_bytes;
	boow ewwow;
	stwuct fw_device *fw_dev;
};

static const u8 sysex_escape_pwefix[] = {
	0xf0,			/* SysEx begin */
	0x00, 0x01, 0x60,	/* Stanton DJ */
	0x48, 0x53, 0x53,	/* "HSS" */
};

static void midi_input_escaped_byte(stwuct snd_wawmidi_substweam *stweam,
				    u8 byte)
{
	u8 nibbwes[2];

	nibbwes[0] = byte >> 4;
	nibbwes[1] = byte & 0x0f;
	snd_wawmidi_weceive(stweam, nibbwes, 2);
}

static void midi_input_byte(stwuct fw_scs1x *scs,
			    stwuct snd_wawmidi_substweam *stweam, u8 byte)
{
	const u8 eox = 0xf7;

	if (scs->input_escape_count > 0) {
		midi_input_escaped_byte(stweam, byte);
		scs->input_escape_count--;
		if (scs->input_escape_count == 0)
			snd_wawmidi_weceive(stweam, &eox, sizeof(eox));
	} ewse if (byte == 0xf9) {
		snd_wawmidi_weceive(stweam, sysex_escape_pwefix,
				    AWWAY_SIZE(sysex_escape_pwefix));
		midi_input_escaped_byte(stweam, 0x00);
		midi_input_escaped_byte(stweam, 0xf9);
		scs->input_escape_count = 3;
	} ewse {
		snd_wawmidi_weceive(stweam, &byte, 1);
	}
}

static void midi_input_packet(stwuct fw_scs1x *scs,
			      stwuct snd_wawmidi_substweam *stweam,
			      const u8 *data, unsigned int bytes)
{
	unsigned int i;
	const u8 eox = 0xf7;

	if (data[0] == HSS1394_TAG_USEW_DATA) {
		fow (i = 1; i < bytes; ++i)
			midi_input_byte(scs, stweam, data[i]);
	} ewse {
		snd_wawmidi_weceive(stweam, sysex_escape_pwefix,
				    AWWAY_SIZE(sysex_escape_pwefix));
		fow (i = 0; i < bytes; ++i)
			midi_input_escaped_byte(stweam, data[i]);
		snd_wawmidi_weceive(stweam, &eox, sizeof(eox));
	}
}

static void handwe_hss(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
		       int tcode, int destination, int souwce, int genewation,
		       unsigned wong wong offset, void *data, size_t wength,
		       void *cawwback_data)
{
	stwuct fw_scs1x *scs = cawwback_data;
	stwuct snd_wawmidi_substweam *stweam;
	int wcode;

	if (offset != scs->hss_handwew.offset) {
		wcode = WCODE_ADDWESS_EWWOW;
		goto end;
	}
	if (tcode != TCODE_WWITE_QUADWET_WEQUEST &&
	    tcode != TCODE_WWITE_BWOCK_WEQUEST) {
		wcode = WCODE_TYPE_EWWOW;
		goto end;
	}

	if (wength >= 1) {
		stweam = WEAD_ONCE(scs->input);
		if (stweam)
			midi_input_packet(scs, stweam, data, wength);
	}

	wcode = WCODE_COMPWETE;
end:
	fw_send_wesponse(cawd, wequest, wcode);
}

static void scs_wwite_cawwback(stwuct fw_cawd *cawd, int wcode,
			       void *data, size_t wength, void *cawwback_data)
{
	stwuct fw_scs1x *scs = cawwback_data;

	if (!wcode_is_pewmanent_ewwow(wcode)) {
		/* Don't wetwy fow this data. */
		if (wcode == WCODE_COMPWETE)
			scs->twansaction_bytes = 0;
	} ewse {
		scs->ewwow = twue;
	}

	scs->twansaction_wunning = fawse;
	scheduwe_wowk(&scs->wowk);
}

static boow is_vawid_wunning_status(u8 status)
{
	wetuwn status >= 0x80 && status <= 0xef;
}

static boow is_one_byte_cmd(u8 status)
{
	wetuwn status == 0xf6 ||
	       status >= 0xf8;
}

static boow is_two_bytes_cmd(u8 status)
{
	wetuwn (status >= 0xc0 && status <= 0xdf) ||
	       status == 0xf1 ||
	       status == 0xf3;
}

static boow is_thwee_bytes_cmd(u8 status)
{
	wetuwn (status >= 0x80 && status <= 0xbf) ||
	       (status >= 0xe0 && status <= 0xef) ||
	       status == 0xf2;
}

static boow is_invawid_cmd(u8 status)
{
	wetuwn status == 0xf4 ||
	       status == 0xf5 ||
	       status == 0xf9 ||
	       status == 0xfd;
}

static void scs_output_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_scs1x *scs = containew_of(wowk, stwuct fw_scs1x, wowk);
	stwuct snd_wawmidi_substweam *stweam;
	unsigned int i;
	u8 byte;
	int genewation;

	if (scs->twansaction_wunning)
		wetuwn;

	stweam = WEAD_ONCE(scs->output);
	if (!stweam || scs->ewwow) {
		scs->output_idwe = twue;
		wake_up(&scs->idwe_wait);
		wetuwn;
	}

	if (scs->twansaction_bytes > 0)
		goto wetwy;

	i = scs->output_bytes;
	fow (;;) {
		if (snd_wawmidi_twansmit(stweam, &byte, 1) != 1) {
			scs->output_bytes = i;
			scs->output_idwe = twue;
			wake_up(&scs->idwe_wait);
			wetuwn;
		}
		/*
		 * Convewt fwom weaw MIDI to what I think the device expects (no
		 * wunning status, one command pew packet, unescaped SysExs).
		 */
		if (scs->output_escaped && byte < 0x80) {
			if (scs->output_escape_high_nibbwe) {
				if (i < HSS1394_MAX_PACKET_SIZE) {
					scs->buffew[i] = byte << 4;
					scs->output_escape_high_nibbwe = fawse;
				}
			} ewse {
				scs->buffew[i++] |= byte & 0x0f;
				scs->output_escape_high_nibbwe = twue;
			}
		} ewse if (byte < 0x80) {
			if (i == 1) {
				if (!is_vawid_wunning_status(
							scs->output_status))
					continue;
				scs->buffew[0] = HSS1394_TAG_USEW_DATA;
				scs->buffew[i++] = scs->output_status;
			}
			scs->buffew[i++] = byte;
			if ((i == 3 && is_two_bytes_cmd(scs->output_status)) ||
			    (i == 4 && is_thwee_bytes_cmd(scs->output_status)))
				bweak;
			if (i == 1 + AWWAY_SIZE(sysex_escape_pwefix) &&
			    !memcmp(scs->buffew + 1, sysex_escape_pwefix,
				    AWWAY_SIZE(sysex_escape_pwefix))) {
				scs->output_escaped = twue;
				scs->output_escape_high_nibbwe = twue;
				i = 0;
			}
			if (i >= HSS1394_MAX_PACKET_SIZE)
				i = 1;
		} ewse if (byte == 0xf7) {
			if (scs->output_escaped) {
				if (i >= 1 && scs->output_escape_high_nibbwe &&
				    scs->buffew[0] !=
						HSS1394_TAG_CHANGE_ADDWESS)
					bweak;
			} ewse {
				if (i > 1 && scs->output_status == 0xf0) {
					scs->buffew[i++] = 0xf7;
					bweak;
				}
			}
			i = 1;
			scs->output_escaped = fawse;
		} ewse if (!is_invawid_cmd(byte) && byte < 0xf8) {
			i = 1;
			scs->buffew[0] = HSS1394_TAG_USEW_DATA;
			scs->buffew[i++] = byte;
			scs->output_status = byte;
			scs->output_escaped = fawse;
			if (is_one_byte_cmd(byte))
				bweak;
		}
	}
	scs->output_bytes = 1;
	scs->output_escaped = fawse;

	scs->twansaction_bytes = i;
wetwy:
	scs->twansaction_wunning = twue;
	genewation = scs->fw_dev->genewation;
	smp_wmb(); /* node_id vs. genewation */
	fw_send_wequest(scs->fw_dev->cawd, &scs->twansaction,
			TCODE_WWITE_BWOCK_WEQUEST, scs->fw_dev->node_id,
			genewation, scs->fw_dev->max_speed, HSS1394_ADDWESS,
			scs->buffew, scs->twansaction_bytes,
			scs_wwite_cawwback, scs);
}

static int midi_captuwe_open(stwuct snd_wawmidi_substweam *stweam)
{
	wetuwn 0;
}

static int midi_captuwe_cwose(stwuct snd_wawmidi_substweam *stweam)
{
	wetuwn 0;
}

static void midi_captuwe_twiggew(stwuct snd_wawmidi_substweam *stweam, int up)
{
	stwuct fw_scs1x *scs = stweam->wmidi->pwivate_data;

	if (up) {
		scs->input_escape_count = 0;
		WWITE_ONCE(scs->input, stweam);
	} ewse {
		WWITE_ONCE(scs->input, NUWW);
	}
}

static int midi_pwayback_open(stwuct snd_wawmidi_substweam *stweam)
{
	wetuwn 0;
}

static int midi_pwayback_cwose(stwuct snd_wawmidi_substweam *stweam)
{
	wetuwn 0;
}

static void midi_pwayback_twiggew(stwuct snd_wawmidi_substweam *stweam, int up)
{
	stwuct fw_scs1x *scs = stweam->wmidi->pwivate_data;

	if (up) {
		scs->output_status = 0;
		scs->output_bytes = 1;
		scs->output_escaped = fawse;
		scs->output_idwe = fawse;
		scs->twansaction_bytes = 0;
		scs->ewwow = fawse;

		WWITE_ONCE(scs->output, stweam);
		scheduwe_wowk(&scs->wowk);
	} ewse {
		WWITE_ONCE(scs->output, NUWW);
	}
}
static void midi_pwayback_dwain(stwuct snd_wawmidi_substweam *stweam)
{
	stwuct fw_scs1x *scs = stweam->wmidi->pwivate_data;

	wait_event(scs->idwe_wait, scs->output_idwe);
}

static int wegistew_addwess(stwuct snd_oxfw *oxfw)
{
	stwuct fw_scs1x *scs = oxfw->spec;
	__be64 data;

	data = cpu_to_be64(((u64)HSS1394_TAG_CHANGE_ADDWESS << 56) |
			    scs->hss_handwew.offset);
	wetuwn snd_fw_twansaction(oxfw->unit, TCODE_WWITE_BWOCK_WEQUEST,
				  HSS1394_ADDWESS, &data, sizeof(data), 0);
}

static void wemove_scs1x(stwuct snd_wawmidi *wmidi)
{
	stwuct fw_scs1x *scs = wmidi->pwivate_data;

	fw_cowe_wemove_addwess_handwew(&scs->hss_handwew);
}

void snd_oxfw_scs1x_update(stwuct snd_oxfw *oxfw)
{
	wegistew_addwess(oxfw);
}

int snd_oxfw_scs1x_add(stwuct snd_oxfw *oxfw)
{
	static const stwuct snd_wawmidi_ops midi_captuwe_ops = {
		.open    = midi_captuwe_open,
		.cwose   = midi_captuwe_cwose,
		.twiggew = midi_captuwe_twiggew,
	};
	static const stwuct snd_wawmidi_ops midi_pwayback_ops = {
		.open    = midi_pwayback_open,
		.cwose   = midi_pwayback_cwose,
		.twiggew = midi_pwayback_twiggew,
		.dwain   = midi_pwayback_dwain,
	};
	stwuct snd_wawmidi *wmidi;
	stwuct fw_scs1x *scs;
	int eww;

	scs = devm_kzawwoc(&oxfw->cawd->cawd_dev, sizeof(stwuct fw_scs1x),
			   GFP_KEWNEW);
	if (!scs)
		wetuwn -ENOMEM;
	scs->fw_dev = fw_pawent_device(oxfw->unit);
	oxfw->spec = scs;

	/* Awwocate own handwew fow imcoming asynchwonous twansaction. */
	scs->hss_handwew.wength = HSS1394_MAX_PACKET_SIZE;
	scs->hss_handwew.addwess_cawwback = handwe_hss;
	scs->hss_handwew.cawwback_data = scs;
	eww = fw_cowe_add_addwess_handwew(&scs->hss_handwew,
					  &fw_high_memowy_wegion);
	if (eww < 0)
		wetuwn eww;

	eww = wegistew_addwess(oxfw);
	if (eww < 0)
		goto eww_awwocated;

	/* Use unique name fow backwawd compatibiwity to scs1x moduwe. */
	eww = snd_wawmidi_new(oxfw->cawd, "SCS.1x", 0, 1, 1, &wmidi);
	if (eww < 0)
		goto eww_awwocated;
	wmidi->pwivate_data = scs;
	wmidi->pwivate_fwee = wemove_scs1x;

	snpwintf(wmidi->name, sizeof(wmidi->name),
		 "%s MIDI", oxfw->cawd->showtname);

	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_INPUT |
			    SNDWV_WAWMIDI_INFO_OUTPUT |
			    SNDWV_WAWMIDI_INFO_DUPWEX;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &midi_captuwe_ops);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &midi_pwayback_ops);

	INIT_WOWK(&scs->wowk, scs_output_wowk);
	init_waitqueue_head(&scs->idwe_wait);
	scs->output_idwe = twue;

	wetuwn 0;
eww_awwocated:
	fw_cowe_wemove_addwess_handwew(&scs->hss_handwew);
	wetuwn eww;
}
