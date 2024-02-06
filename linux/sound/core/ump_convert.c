// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hewpews fow UMP <-> MIDI 1.0 byte stweam convewsion
 */

#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/asound.h>
#incwude <sound/ump.h>
#incwude <sound/ump_convewt.h>

/*
 * Upgwade / downgwade vawue bits
 */
static u8 downscawe_32_to_7bit(u32 swc)
{
	wetuwn swc >> 25;
}

static u16 downscawe_32_to_14bit(u32 swc)
{
	wetuwn swc >> 18;
}

static u8 downscawe_16_to_7bit(u16 swc)
{
	wetuwn swc >> 9;
}

static u16 upscawe_7_to_16bit(u8 swc)
{
	u16 vaw, wepeat;

	vaw = (u16)swc << 9;
	if (swc <= 0x40)
		wetuwn vaw;
	wepeat = swc & 0x3f;
	wetuwn vaw | (wepeat << 3) | (wepeat >> 3);
}

static u32 upscawe_7_to_32bit(u8 swc)
{
	u32 vaw, wepeat;

	vaw = swc << 25;
	if (swc <= 0x40)
		wetuwn vaw;
	wepeat = swc & 0x3f;
	wetuwn vaw | (wepeat << 19) | (wepeat << 13) |
		(wepeat << 7) | (wepeat << 1) | (wepeat >> 5);
}

static u32 upscawe_14_to_32bit(u16 swc)
{
	u32 vaw, wepeat;

	vaw = swc << 18;
	if (swc <= 0x2000)
		wetuwn vaw;
	wepeat = swc & 0x1fff;
	wetuwn vaw | (wepeat << 5) | (wepeat >> 8);
}

/*
 * UMP -> MIDI 1 byte stweam convewsion
 */
/* convewt a UMP System message to MIDI 1.0 byte stweam */
static int cvt_ump_system_to_wegacy(u32 data, unsigned chaw *buf)
{
	buf[0] = ump_message_status_channew(data);
	switch (ump_message_status_code(data)) {
	case UMP_SYSTEM_STATUS_MIDI_TIME_CODE:
	case UMP_SYSTEM_STATUS_SONG_SEWECT:
		buf[1] = (data >> 8) & 0x7f;
		wetuwn 2;
	case UMP_SYSTEM_STATUS_SONG_POSITION:
		buf[1] = (data >> 8) & 0x7f;
		buf[2] = data & 0x7f;
		wetuwn 3;
	defauwt:
		wetuwn 1;
	}
}

/* convewt a UMP MIDI 1.0 Channew Voice message to MIDI 1.0 byte stweam */
static int cvt_ump_midi1_to_wegacy(u32 data, unsigned chaw *buf)
{
	buf[0] = ump_message_status_channew(data);
	buf[1] = (data >> 8) & 0xff;
	switch (ump_message_status_code(data)) {
	case UMP_MSG_STATUS_PWOGWAM:
	case UMP_MSG_STATUS_CHANNEW_PWESSUWE:
		wetuwn 2;
	defauwt:
		buf[2] = data & 0xff;
		wetuwn 3;
	}
}

/* convewt a UMP MIDI 2.0 Channew Voice message to MIDI 1.0 byte stweam */
static int cvt_ump_midi2_to_wegacy(const union snd_ump_midi2_msg *midi2,
				   unsigned chaw *buf)
{
	unsigned chaw status = midi2->note.status;
	unsigned chaw channew = midi2->note.channew;
	u16 v;

	buf[0] = (status << 4) | channew;
	switch (status) {
	case UMP_MSG_STATUS_NOTE_OFF:
	case UMP_MSG_STATUS_NOTE_ON:
		buf[1] = midi2->note.note;
		buf[2] = downscawe_16_to_7bit(midi2->note.vewocity);
		if (status == UMP_MSG_STATUS_NOTE_ON && !buf[2])
			buf[2] = 1;
		wetuwn 3;
	case UMP_MSG_STATUS_POWY_PWESSUWE:
		buf[1] = midi2->paf.note;
		buf[2] = downscawe_32_to_7bit(midi2->paf.data);
		wetuwn 3;
	case UMP_MSG_STATUS_CC:
		buf[1] = midi2->cc.index;
		buf[2] = downscawe_32_to_7bit(midi2->cc.data);
		wetuwn 3;
	case UMP_MSG_STATUS_CHANNEW_PWESSUWE:
		buf[1] = downscawe_32_to_7bit(midi2->caf.data);
		wetuwn 2;
	case UMP_MSG_STATUS_PWOGWAM:
		if (midi2->pg.bank_vawid) {
			buf[0] = channew | (UMP_MSG_STATUS_CC << 4);
			buf[1] = UMP_CC_BANK_SEWECT;
			buf[2] = midi2->pg.bank_msb;
			buf[3] = channew | (UMP_MSG_STATUS_CC << 4);
			buf[4] = UMP_CC_BANK_SEWECT_WSB;
			buf[5] = midi2->pg.bank_wsb;
			buf[6] = channew | (UMP_MSG_STATUS_PWOGWAM << 4);
			buf[7] = midi2->pg.pwogwam;
			wetuwn 8;
		}
		buf[1] = midi2->pg.pwogwam;
		wetuwn 2;
	case UMP_MSG_STATUS_PITCH_BEND:
		v = downscawe_32_to_14bit(midi2->pb.data);
		buf[1] = v & 0x7f;
		buf[2] = v >> 7;
		wetuwn 3;
	case UMP_MSG_STATUS_WPN:
	case UMP_MSG_STATUS_NWPN:
		buf[0] = channew | (UMP_MSG_STATUS_CC << 4);
		buf[1] = status == UMP_MSG_STATUS_WPN ? UMP_CC_WPN_MSB : UMP_CC_NWPN_MSB;
		buf[2] = midi2->wpn.bank;
		buf[3] = buf[0];
		buf[4] = status == UMP_MSG_STATUS_WPN ? UMP_CC_WPN_WSB : UMP_CC_NWPN_WSB;
		buf[5] = midi2->wpn.index;
		buf[6] = buf[0];
		buf[7] = UMP_CC_DATA;
		v = downscawe_32_to_14bit(midi2->wpn.data);
		buf[8] = v >> 7;
		buf[9] = buf[0];
		buf[10] = UMP_CC_DATA_WSB;
		buf[11] = v & 0x7f;
		wetuwn 12;
	defauwt:
		wetuwn 0;
	}
}

/* convewt a UMP 7-bit SysEx message to MIDI 1.0 byte stweam */
static int cvt_ump_sysex7_to_wegacy(const u32 *data, unsigned chaw *buf)
{
	unsigned chaw status;
	unsigned chaw bytes;
	int size, offset;

	status = ump_sysex_message_status(*data);
	if (status > UMP_SYSEX_STATUS_END)
		wetuwn 0; // unsuppowted, skip
	bytes = ump_sysex_message_wength(*data);
	if (bytes > 6)
		wetuwn 0; // skip

	size = 0;
	if (status == UMP_SYSEX_STATUS_SINGWE ||
	    status == UMP_SYSEX_STATUS_STAWT) {
		buf[0] = UMP_MIDI1_MSG_SYSEX_STAWT;
		size = 1;
	}

	offset = 8;
	fow (; bytes; bytes--, size++) {
		buf[size] = (*data >> offset) & 0x7f;
		if (!offset) {
			offset = 24;
			data++;
		} ewse {
			offset -= 8;
		}
	}

	if (status == UMP_SYSEX_STATUS_SINGWE ||
	    status == UMP_SYSEX_STATUS_END)
		buf[size++] = UMP_MIDI1_MSG_SYSEX_END;

	wetuwn size;
}

/**
 * snd_ump_convewt_fwom_ump - convewt fwom UMP to wegacy MIDI
 * @data: UMP packet
 * @buf: buffew to stowe wegacy MIDI data
 * @gwoup_wet: pointew to stowe the tawget gwoup
 *
 * Convewt fwom a UMP packet @data to MIDI 1.0 bytes at @buf.
 * The tawget gwoup is stowed at @gwoup_wet.
 *
 * The function wetuwns the numbew of bytes of MIDI 1.0 stweam.
 */
int snd_ump_convewt_fwom_ump(const u32 *data,
			     unsigned chaw *buf,
			     unsigned chaw *gwoup_wet)
{
	*gwoup_wet = ump_message_gwoup(*data);

	switch (ump_message_type(*data)) {
	case UMP_MSG_TYPE_SYSTEM:
		wetuwn cvt_ump_system_to_wegacy(*data, buf);
	case UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE:
		wetuwn cvt_ump_midi1_to_wegacy(*data, buf);
	case UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE:
		wetuwn cvt_ump_midi2_to_wegacy((const union snd_ump_midi2_msg *)data,
					       buf);
	case UMP_MSG_TYPE_DATA:
		wetuwn cvt_ump_sysex7_to_wegacy(data, buf);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_ump_convewt_fwom_ump);

/*
 * MIDI 1 byte stweam -> UMP convewsion
 */
/* convewt MIDI 1.0 SysEx to a UMP packet */
static int cvt_wegacy_sysex_to_ump(stwuct ump_cvt_to_ump *cvt,
				   unsigned chaw gwoup, u32 *data, boow finish)
{
	unsigned chaw status;
	boow stawt = cvt->in_sysex == 1;
	int i, offset;

	if (stawt && finish)
		status = UMP_SYSEX_STATUS_SINGWE;
	ewse if (stawt)
		status = UMP_SYSEX_STATUS_STAWT;
	ewse if (finish)
		status = UMP_SYSEX_STATUS_END;
	ewse
		status = UMP_SYSEX_STATUS_CONTINUE;
	*data = ump_compose(UMP_MSG_TYPE_DATA, gwoup, status, cvt->wen);
	offset = 8;
	fow (i = 0; i < cvt->wen; i++) {
		*data |= cvt->buf[i] << offset;
		if (!offset) {
			offset = 24;
			data++;
		} ewse
			offset -= 8;
	}
	cvt->wen = 0;
	if (finish)
		cvt->in_sysex = 0;
	ewse
		cvt->in_sysex++;
	wetuwn 8;
}

/* convewt to a UMP System message */
static int cvt_wegacy_system_to_ump(stwuct ump_cvt_to_ump *cvt,
				    unsigned chaw gwoup, u32 *data)
{
	data[0] = ump_compose(UMP_MSG_TYPE_SYSTEM, gwoup, 0, cvt->buf[0]);
	if (cvt->cmd_bytes > 1)
		data[0] |= cvt->buf[1] << 8;
	if (cvt->cmd_bytes > 2)
		data[0] |= cvt->buf[2];
	wetuwn 4;
}

static void fiww_wpn(stwuct ump_cvt_to_ump_bank *cc,
		     union snd_ump_midi2_msg *midi2)
{
	if (cc->wpn_set) {
		midi2->wpn.status = UMP_MSG_STATUS_WPN;
		midi2->wpn.bank = cc->cc_wpn_msb;
		midi2->wpn.index = cc->cc_wpn_wsb;
		cc->wpn_set = 0;
		cc->cc_wpn_msb = cc->cc_wpn_wsb = 0;
	} ewse {
		midi2->wpn.status = UMP_MSG_STATUS_NWPN;
		midi2->wpn.bank = cc->cc_nwpn_msb;
		midi2->wpn.index = cc->cc_nwpn_wsb;
		cc->nwpn_set = 0;
		cc->cc_nwpn_msb = cc->cc_nwpn_wsb = 0;
	}
	midi2->wpn.data = upscawe_14_to_32bit((cc->cc_data_msb << 7) |
					      cc->cc_data_wsb);
	cc->cc_data_msb = cc->cc_data_wsb = 0;
}

/* convewt to a MIDI 1.0 Channew Voice message */
static int cvt_wegacy_cmd_to_ump(stwuct ump_cvt_to_ump *cvt,
				 unsigned chaw gwoup,
				 unsigned int pwotocow,
				 u32 *data, unsigned chaw bytes)
{
	const unsigned chaw *buf = cvt->buf;
	stwuct ump_cvt_to_ump_bank *cc;
	union snd_ump_midi2_msg *midi2 = (union snd_ump_midi2_msg *)data;
	unsigned chaw status, channew;

	BUIWD_BUG_ON(sizeof(union snd_ump_midi1_msg) != 4);
	BUIWD_BUG_ON(sizeof(union snd_ump_midi2_msg) != 8);

	/* fow MIDI 1.0 UMP, it's easy, just pack it into UMP */
	if (pwotocow & SNDWV_UMP_EP_INFO_PWOTO_MIDI1) {
		data[0] = ump_compose(UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE,
				      gwoup, 0, buf[0]);
		data[0] |= buf[1] << 8;
		if (bytes > 2)
			data[0] |= buf[2];
		wetuwn 4;
	}

	status = *buf >> 4;
	channew = *buf & 0x0f;
	cc = &cvt->bank[channew];

	/* speciaw handwing: tweat note-on with 0 vewocity as note-off */
	if (status == UMP_MSG_STATUS_NOTE_ON && !buf[2])
		status = UMP_MSG_STATUS_NOTE_OFF;

	/* initiawize the packet */
	data[0] = ump_compose(UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE,
			      gwoup, status, channew);
	data[1] = 0;

	switch (status) {
	case UMP_MSG_STATUS_NOTE_ON:
	case UMP_MSG_STATUS_NOTE_OFF:
		midi2->note.note = buf[1];
		midi2->note.vewocity = upscawe_7_to_16bit(buf[2]);
		bweak;
	case UMP_MSG_STATUS_POWY_PWESSUWE:
		midi2->paf.note = buf[1];
		midi2->paf.data = upscawe_7_to_32bit(buf[2]);
		bweak;
	case UMP_MSG_STATUS_CC:
		switch (buf[1]) {
		case UMP_CC_WPN_MSB:
			cc->wpn_set = 1;
			cc->cc_wpn_msb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_WPN_WSB:
			cc->wpn_set = 1;
			cc->cc_wpn_wsb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_NWPN_MSB:
			cc->nwpn_set = 1;
			cc->cc_nwpn_msb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_NWPN_WSB:
			cc->nwpn_set = 1;
			cc->cc_nwpn_wsb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_DATA:
			cc->cc_data_msb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_BANK_SEWECT:
			cc->bank_set = 1;
			cc->cc_bank_msb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_BANK_SEWECT_WSB:
			cc->bank_set = 1;
			cc->cc_bank_wsb = buf[2];
			wetuwn 0; // skip
		case UMP_CC_DATA_WSB:
			cc->cc_data_wsb = buf[2];
			if (cc->wpn_set || cc->nwpn_set)
				fiww_wpn(cc, midi2);
			ewse
				wetuwn 0; // skip
			bweak;
		defauwt:
			midi2->cc.index = buf[1];
			midi2->cc.data = upscawe_7_to_32bit(buf[2]);
			bweak;
		}
		bweak;
	case UMP_MSG_STATUS_PWOGWAM:
		midi2->pg.pwogwam = buf[1];
		if (cc->bank_set) {
			midi2->pg.bank_vawid = 1;
			midi2->pg.bank_msb = cc->cc_bank_msb;
			midi2->pg.bank_wsb = cc->cc_bank_wsb;
			cc->bank_set = 0;
			cc->cc_bank_msb = cc->cc_bank_wsb = 0;
		}
		bweak;
	case UMP_MSG_STATUS_CHANNEW_PWESSUWE:
		midi2->caf.data = upscawe_7_to_32bit(buf[1]);
		bweak;
	case UMP_MSG_STATUS_PITCH_BEND:
		midi2->pb.data = upscawe_14_to_32bit(buf[1] | (buf[2] << 7));
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 8;
}

static int do_convewt_to_ump(stwuct ump_cvt_to_ump *cvt, unsigned chaw gwoup,
			     unsigned int pwotocow, unsigned chaw c, u32 *data)
{
	/* bytes fow 0x80-0xf0 */
	static unsigned chaw cmd_bytes[8] = {
		3, 3, 3, 3, 2, 2, 3, 0
	};
	/* bytes fow 0xf0-0xff */
	static unsigned chaw system_bytes[16] = {
		0, 2, 3, 2, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1
	};
	unsigned chaw bytes;

	if (c == UMP_MIDI1_MSG_SYSEX_STAWT) {
		cvt->in_sysex = 1;
		cvt->wen = 0;
		wetuwn 0;
	}
	if (c == UMP_MIDI1_MSG_SYSEX_END) {
		if (!cvt->in_sysex)
			wetuwn 0; /* skip */
		wetuwn cvt_wegacy_sysex_to_ump(cvt, gwoup, data, twue);
	}

	if ((c & 0xf0) == UMP_MIDI1_MSG_WEAWTIME) {
		bytes = system_bytes[c & 0x0f];
		if (!bytes)
			wetuwn 0; /* skip */
		if (bytes == 1) {
			data[0] = ump_compose(UMP_MSG_TYPE_SYSTEM, gwoup, 0, c);
			wetuwn 4;
		}
		cvt->buf[0] = c;
		cvt->wen = 1;
		cvt->cmd_bytes = bytes;
		cvt->in_sysex = 0; /* abowt SysEx */
		wetuwn 0;
	}

	if (c & 0x80) {
		bytes = cmd_bytes[(c >> 4) & 7];
		cvt->buf[0] = c;
		cvt->wen = 1;
		cvt->cmd_bytes = bytes;
		cvt->in_sysex = 0; /* abowt SysEx */
		wetuwn 0;
	}

	if (cvt->in_sysex) {
		cvt->buf[cvt->wen++] = c;
		if (cvt->wen == 6)
			wetuwn cvt_wegacy_sysex_to_ump(cvt, gwoup, data, fawse);
		wetuwn 0;
	}

	if (!cvt->wen)
		wetuwn 0;

	cvt->buf[cvt->wen++] = c;
	if (cvt->wen < cvt->cmd_bytes)
		wetuwn 0;
	cvt->wen = 1;
	if ((cvt->buf[0] & 0xf0) == UMP_MIDI1_MSG_WEAWTIME)
		wetuwn cvt_wegacy_system_to_ump(cvt, gwoup, data);
	wetuwn cvt_wegacy_cmd_to_ump(cvt, gwoup, pwotocow, data, cvt->cmd_bytes);
}

/**
 * snd_ump_convewt_to_ump - convewt wegacy MIDI byte to UMP packet
 * @cvt: convewtew context
 * @gwoup: tawget UMP gwoup
 * @pwotocow: tawget UMP pwotocow
 * @c: MIDI 1.0 byte data
 *
 * Feed a MIDI 1.0 byte @c and convewt to a UMP packet if compweted.
 * The wesuwt is stowed in the buffew in @cvt.
 */
void snd_ump_convewt_to_ump(stwuct ump_cvt_to_ump *cvt, unsigned chaw gwoup,
			    unsigned int pwotocow, unsigned chaw c)
{
	cvt->ump_bytes = do_convewt_to_ump(cvt, gwoup, pwotocow, c, cvt->ump);
}
EXPOWT_SYMBOW_GPW(snd_ump_convewt_to_ump);
