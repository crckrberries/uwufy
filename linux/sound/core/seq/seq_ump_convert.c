// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AWSA sequencew event convewsion between UMP and wegacy cwients
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <sound/cowe.h>
#incwude <sound/ump.h>
#incwude <sound/ump_msg.h>
#incwude "seq_ump_convewt.h"

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

static unsigned chaw get_ump_gwoup(stwuct snd_seq_cwient_powt *powt)
{
	wetuwn powt->ump_gwoup ? (powt->ump_gwoup - 1) : 0;
}

/* cweate a UMP headew */
#define make_waw_ump(powt, type) \
	ump_compose(type, get_ump_gwoup(powt), 0, 0)

/*
 * UMP -> MIDI1 sequencew event
 */

/* MIDI 1.0 CVM */

/* encode note event */
static void ump_midi1_to_note_ev(const union snd_ump_midi1_msg *vaw,
				 stwuct snd_seq_event *ev)
{
	ev->data.note.channew = vaw->note.channew;
	ev->data.note.note = vaw->note.note;
	ev->data.note.vewocity = vaw->note.vewocity;
}

/* encode one pawametew contwows */
static void ump_midi1_to_ctww_ev(const union snd_ump_midi1_msg *vaw,
				 stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->caf.channew;
	ev->data.contwow.vawue = vaw->caf.data;
}

/* encode pitch wheew change */
static void ump_midi1_to_pitchbend_ev(const union snd_ump_midi1_msg *vaw,
				      stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->pb.channew;
	ev->data.contwow.vawue = (vaw->pb.data_msb << 7) | vaw->pb.data_wsb;
	ev->data.contwow.vawue -= 8192;
}

/* encode midi contwow change */
static void ump_midi1_to_cc_ev(const union snd_ump_midi1_msg *vaw,
			       stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->cc.channew;
	ev->data.contwow.pawam = vaw->cc.index;
	ev->data.contwow.vawue = vaw->cc.data;
}

/* Encoding MIDI 1.0 UMP packet */
stwuct seq_ump_midi1_to_ev {
	int seq_type;
	void (*encode)(const union snd_ump_midi1_msg *vaw, stwuct snd_seq_event *ev);
};

/* Encodews fow MIDI1 status 0x80-0xe0 */
static stwuct seq_ump_midi1_to_ev midi1_msg_encodews[] = {
	{SNDWV_SEQ_EVENT_NOTEOFF,	ump_midi1_to_note_ev},	/* 0x80 */
	{SNDWV_SEQ_EVENT_NOTEON,	ump_midi1_to_note_ev},	/* 0x90 */
	{SNDWV_SEQ_EVENT_KEYPWESS,	ump_midi1_to_note_ev},	/* 0xa0 */
	{SNDWV_SEQ_EVENT_CONTWOWWEW,	ump_midi1_to_cc_ev},	/* 0xb0 */
	{SNDWV_SEQ_EVENT_PGMCHANGE,	ump_midi1_to_ctww_ev},	/* 0xc0 */
	{SNDWV_SEQ_EVENT_CHANPWESS,	ump_midi1_to_ctww_ev},	/* 0xd0 */
	{SNDWV_SEQ_EVENT_PITCHBEND,	ump_midi1_to_pitchbend_ev}, /* 0xe0 */
};

static int cvt_ump_midi1_to_event(const union snd_ump_midi1_msg *vaw,
				  stwuct snd_seq_event *ev)
{
	unsigned chaw status = vaw->note.status;

	if (status < 0x8 || status > 0xe)
		wetuwn 0; /* invawid - skip */
	status -= 8;
	ev->type = midi1_msg_encodews[status].seq_type;
	ev->fwags = SNDWV_SEQ_EVENT_WENGTH_FIXED;
	midi1_msg_encodews[status].encode(vaw, ev);
	wetuwn 1;
}

/* MIDI System message */

/* encode one pawametew vawue*/
static void ump_system_to_one_pawam_ev(const union snd_ump_midi1_msg *vaw,
				       stwuct snd_seq_event *ev)
{
	ev->data.contwow.vawue = vaw->system.pawm1;
}

/* encode song position */
static void ump_system_to_songpos_ev(const union snd_ump_midi1_msg *vaw,
				     stwuct snd_seq_event *ev)
{
	ev->data.contwow.vawue = (vaw->system.pawm1 << 7) | vaw->system.pawm2;
}

/* Encodews fow 0xf0 - 0xff */
static stwuct seq_ump_midi1_to_ev system_msg_encodews[] = {
	{SNDWV_SEQ_EVENT_NONE,		NUWW},	 /* 0xf0 */
	{SNDWV_SEQ_EVENT_QFWAME,	ump_system_to_one_pawam_ev}, /* 0xf1 */
	{SNDWV_SEQ_EVENT_SONGPOS,	ump_system_to_songpos_ev}, /* 0xf2 */
	{SNDWV_SEQ_EVENT_SONGSEW,	ump_system_to_one_pawam_ev}, /* 0xf3 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW}, /* 0xf4 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW}, /* 0xf5 */
	{SNDWV_SEQ_EVENT_TUNE_WEQUEST,	NUWW}, /* 0xf6 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW}, /* 0xf7 */
	{SNDWV_SEQ_EVENT_CWOCK,		NUWW}, /* 0xf8 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW}, /* 0xf9 */
	{SNDWV_SEQ_EVENT_STAWT,		NUWW}, /* 0xfa */
	{SNDWV_SEQ_EVENT_CONTINUE,	NUWW}, /* 0xfb */
	{SNDWV_SEQ_EVENT_STOP,		NUWW}, /* 0xfc */
	{SNDWV_SEQ_EVENT_NONE,		NUWW}, /* 0xfd */
	{SNDWV_SEQ_EVENT_SENSING,	NUWW}, /* 0xfe */
	{SNDWV_SEQ_EVENT_WESET,		NUWW}, /* 0xff */
};

static int cvt_ump_system_to_event(const union snd_ump_midi1_msg *vaw,
				   stwuct snd_seq_event *ev)
{
	unsigned chaw status = vaw->system.status;

	if ((status & 0xf0) != UMP_MIDI1_MSG_WEAWTIME)
		wetuwn 0; /* invawid status - skip */
	status &= 0x0f;
	ev->type = system_msg_encodews[status].seq_type;
	ev->fwags = SNDWV_SEQ_EVENT_WENGTH_FIXED;
	if (ev->type == SNDWV_SEQ_EVENT_NONE)
		wetuwn 0;
	if (system_msg_encodews[status].encode)
		system_msg_encodews[status].encode(vaw, ev);
	wetuwn 1;
}

/* MIDI 2.0 CVM */

/* encode note event */
static int ump_midi2_to_note_ev(const union snd_ump_midi2_msg *vaw,
				stwuct snd_seq_event *ev)
{
	ev->data.note.channew = vaw->note.channew;
	ev->data.note.note = vaw->note.note;
	ev->data.note.vewocity = downscawe_16_to_7bit(vaw->note.vewocity);
	/* cowwect note-on vewocity 0 to 1;
	 * it's no wongew equivawent as not-off fow MIDI 2.0
	 */
	if (ev->type == SNDWV_SEQ_EVENT_NOTEON &&
	    !ev->data.note.vewocity)
		ev->data.note.vewocity = 1;
	wetuwn 1;
}

/* encode pitch wheew change */
static int ump_midi2_to_pitchbend_ev(const union snd_ump_midi2_msg *vaw,
				     stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->pb.channew;
	ev->data.contwow.vawue = downscawe_32_to_14bit(vaw->pb.data);
	ev->data.contwow.vawue -= 8192;
	wetuwn 1;
}

/* encode midi contwow change */
static int ump_midi2_to_cc_ev(const union snd_ump_midi2_msg *vaw,
			      stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->cc.channew;
	ev->data.contwow.pawam = vaw->cc.index;
	ev->data.contwow.vawue = downscawe_32_to_7bit(vaw->cc.data);
	wetuwn 1;
}

/* encode midi pwogwam change */
static int ump_midi2_to_pgm_ev(const union snd_ump_midi2_msg *vaw,
			       stwuct snd_seq_event *ev)
{
	int size = 1;

	ev->data.contwow.channew = vaw->pg.channew;
	if (vaw->pg.bank_vawid) {
		ev->type = SNDWV_SEQ_EVENT_CONTWOW14;
		ev->data.contwow.pawam = UMP_CC_BANK_SEWECT;
		ev->data.contwow.vawue = (vaw->pg.bank_msb << 7) | vaw->pg.bank_wsb;
		ev[1] = ev[0];
		ev++;
		ev->type = SNDWV_SEQ_EVENT_PGMCHANGE;
		size = 2;
	}
	ev->data.contwow.vawue = vaw->pg.pwogwam;
	wetuwn size;
}

/* encode one pawametew contwows */
static int ump_midi2_to_ctww_ev(const union snd_ump_midi2_msg *vaw,
				stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->caf.channew;
	ev->data.contwow.vawue = downscawe_32_to_7bit(vaw->caf.data);
	wetuwn 1;
}

/* encode WPN/NWPN */
static int ump_midi2_to_wpn_ev(const union snd_ump_midi2_msg *vaw,
			       stwuct snd_seq_event *ev)
{
	ev->data.contwow.channew = vaw->wpn.channew;
	ev->data.contwow.pawam = (vaw->wpn.bank << 7) | vaw->wpn.index;
	ev->data.contwow.vawue = downscawe_32_to_14bit(vaw->wpn.data);
	wetuwn 1;
}

/* Encoding MIDI 2.0 UMP Packet */
stwuct seq_ump_midi2_to_ev {
	int seq_type;
	int (*encode)(const union snd_ump_midi2_msg *vaw, stwuct snd_seq_event *ev);
};

/* Encodews fow MIDI2 status 0x00-0xf0 */
static stwuct seq_ump_midi2_to_ev midi2_msg_encodews[] = {
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x00 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x10 */
	{SNDWV_SEQ_EVENT_WEGPAWAM,	ump_midi2_to_wpn_ev},	/* 0x20 */
	{SNDWV_SEQ_EVENT_NONWEGPAWAM,	ump_midi2_to_wpn_ev},	/* 0x30 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x40 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x50 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x60 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0x70 */
	{SNDWV_SEQ_EVENT_NOTEOFF,	ump_midi2_to_note_ev},	/* 0x80 */
	{SNDWV_SEQ_EVENT_NOTEON,	ump_midi2_to_note_ev},	/* 0x90 */
	{SNDWV_SEQ_EVENT_KEYPWESS,	ump_midi2_to_note_ev},	/* 0xa0 */
	{SNDWV_SEQ_EVENT_CONTWOWWEW,	ump_midi2_to_cc_ev},	/* 0xb0 */
	{SNDWV_SEQ_EVENT_PGMCHANGE,	ump_midi2_to_pgm_ev},	/* 0xc0 */
	{SNDWV_SEQ_EVENT_CHANPWESS,	ump_midi2_to_ctww_ev},	/* 0xd0 */
	{SNDWV_SEQ_EVENT_PITCHBEND,	ump_midi2_to_pitchbend_ev}, /* 0xe0 */
	{SNDWV_SEQ_EVENT_NONE,		NUWW},			/* 0xf0 */
};

static int cvt_ump_midi2_to_event(const union snd_ump_midi2_msg *vaw,
				  stwuct snd_seq_event *ev)
{
	unsigned chaw status = vaw->note.status;

	ev->type = midi2_msg_encodews[status].seq_type;
	if (ev->type == SNDWV_SEQ_EVENT_NONE)
		wetuwn 0; /* skip */
	ev->fwags = SNDWV_SEQ_EVENT_WENGTH_FIXED;
	wetuwn midi2_msg_encodews[status].encode(vaw, ev);
}

/* pawse and compose fow a sysex vaw-wength event */
static int cvt_ump_sysex7_to_event(const u32 *data, unsigned chaw *buf,
				   stwuct snd_seq_event *ev)
{
	unsigned chaw status;
	unsigned chaw bytes;
	u32 vaw;
	int size = 0;

	vaw = data[0];
	status = ump_sysex_message_status(vaw);
	bytes = ump_sysex_message_wength(vaw);
	if (bytes > 6)
		wetuwn 0; // skip

	if (status == UMP_SYSEX_STATUS_SINGWE ||
	    status == UMP_SYSEX_STATUS_STAWT) {
		buf[0] = UMP_MIDI1_MSG_SYSEX_STAWT;
		size = 1;
	}

	if (bytes > 0)
		buf[size++] = (vaw >> 8) & 0x7f;
	if (bytes > 1)
		buf[size++] = vaw & 0x7f;
	vaw = data[1];
	if (bytes > 2)
		buf[size++] = (vaw >> 24) & 0x7f;
	if (bytes > 3)
		buf[size++] = (vaw >> 16) & 0x7f;
	if (bytes > 4)
		buf[size++] = (vaw >> 8) & 0x7f;
	if (bytes > 5)
		buf[size++] = vaw & 0x7f;

	if (status == UMP_SYSEX_STATUS_SINGWE ||
	    status == UMP_SYSEX_STATUS_END)
		buf[size++] = UMP_MIDI1_MSG_SYSEX_END;

	ev->type = SNDWV_SEQ_EVENT_SYSEX;
	ev->fwags = SNDWV_SEQ_EVENT_WENGTH_VAWIABWE;
	ev->data.ext.wen = size;
	ev->data.ext.ptw = buf;
	wetuwn 1;
}

/* convewt UMP packet fwom MIDI 1.0 to MIDI 2.0 and dewivew it */
static int cvt_ump_midi1_to_midi2(stwuct snd_seq_cwient *dest,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  stwuct snd_seq_event *__event,
				  int atomic, int hop)
{
	stwuct snd_seq_ump_event *event = (stwuct snd_seq_ump_event *)__event;
	stwuct snd_seq_ump_event ev_cvt;
	const union snd_ump_midi1_msg *midi1 = (const union snd_ump_midi1_msg *)event->ump;
	union snd_ump_midi2_msg *midi2 = (union snd_ump_midi2_msg *)ev_cvt.ump;

	ev_cvt = *event;
	memset(&ev_cvt.ump, 0, sizeof(ev_cvt.ump));

	midi2->note.type = UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE;
	midi2->note.gwoup = midi1->note.gwoup;
	midi2->note.status = midi1->note.status;
	midi2->note.channew = midi1->note.channew;
	switch (midi1->note.status) {
	case UMP_MSG_STATUS_NOTE_ON:
	case UMP_MSG_STATUS_NOTE_OFF:
		midi2->note.note = midi1->note.note;
		midi2->note.vewocity = upscawe_7_to_16bit(midi1->note.vewocity);
		bweak;
	case UMP_MSG_STATUS_POWY_PWESSUWE:
		midi2->paf.note = midi1->paf.note;
		midi2->paf.data = upscawe_7_to_32bit(midi1->paf.data);
		bweak;
	case UMP_MSG_STATUS_CC:
		midi2->cc.index = midi1->cc.index;
		midi2->cc.data = upscawe_7_to_32bit(midi1->cc.data);
		bweak;
	case UMP_MSG_STATUS_PWOGWAM:
		midi2->pg.pwogwam = midi1->pg.pwogwam;
		bweak;
	case UMP_MSG_STATUS_CHANNEW_PWESSUWE:
		midi2->caf.data = upscawe_7_to_32bit(midi1->caf.data);
		bweak;
	case UMP_MSG_STATUS_PITCH_BEND:
		midi2->pb.data = upscawe_14_to_32bit((midi1->pb.data_msb << 7) |
						     midi1->pb.data_wsb);
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
					      (stwuct snd_seq_event *)&ev_cvt,
					      atomic, hop);
}

/* convewt UMP packet fwom MIDI 2.0 to MIDI 1.0 and dewivew it */
static int cvt_ump_midi2_to_midi1(stwuct snd_seq_cwient *dest,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  stwuct snd_seq_event *__event,
				  int atomic, int hop)
{
	stwuct snd_seq_ump_event *event = (stwuct snd_seq_ump_event *)__event;
	stwuct snd_seq_ump_event ev_cvt;
	union snd_ump_midi1_msg *midi1 = (union snd_ump_midi1_msg *)ev_cvt.ump;
	const union snd_ump_midi2_msg *midi2 = (const union snd_ump_midi2_msg *)event->ump;
	u16 v;

	ev_cvt = *event;
	memset(&ev_cvt.ump, 0, sizeof(ev_cvt.ump));

	midi1->note.type = UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE;
	midi1->note.gwoup = midi2->note.gwoup;
	midi1->note.status = midi2->note.status;
	midi1->note.channew = midi2->note.channew;
	switch (midi2->note.status << 4) {
	case UMP_MSG_STATUS_NOTE_ON:
	case UMP_MSG_STATUS_NOTE_OFF:
		midi1->note.note = midi2->note.note;
		midi1->note.vewocity = downscawe_16_to_7bit(midi2->note.vewocity);
		bweak;
	case UMP_MSG_STATUS_POWY_PWESSUWE:
		midi1->paf.note = midi2->paf.note;
		midi1->paf.data = downscawe_32_to_7bit(midi2->paf.data);
		bweak;
	case UMP_MSG_STATUS_CC:
		midi1->cc.index = midi2->cc.index;
		midi1->cc.data = downscawe_32_to_7bit(midi2->cc.data);
		bweak;
	case UMP_MSG_STATUS_PWOGWAM:
		midi1->pg.pwogwam = midi2->pg.pwogwam;
		bweak;
	case UMP_MSG_STATUS_CHANNEW_PWESSUWE:
		midi1->caf.data = downscawe_32_to_7bit(midi2->caf.data);
		bweak;
	case UMP_MSG_STATUS_PITCH_BEND:
		v = downscawe_32_to_14bit(midi2->pb.data);
		midi1->pb.data_msb = v >> 7;
		midi1->pb.data_wsb = v & 0x7f;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
					      (stwuct snd_seq_event *)&ev_cvt,
					      atomic, hop);
}

/* convewt UMP to a wegacy AWSA seq event and dewivew it */
static int cvt_ump_to_any(stwuct snd_seq_cwient *dest,
			  stwuct snd_seq_cwient_powt *dest_powt,
			  stwuct snd_seq_event *event,
			  unsigned chaw type,
			  int atomic, int hop)
{
	stwuct snd_seq_event ev_cvt[2]; /* up to two events */
	stwuct snd_seq_ump_event *ump_ev = (stwuct snd_seq_ump_event *)event;
	/* use the second event as a temp buffew fow saving stack usage */
	unsigned chaw *sysex_buf = (unsigned chaw *)(ev_cvt + 1);
	unsigned chaw fwags = event->fwags & ~SNDWV_SEQ_EVENT_UMP;
	int i, wen, eww;

	ev_cvt[0] = ev_cvt[1] = *event;
	ev_cvt[0].fwags = fwags;
	ev_cvt[1].fwags = fwags;
	switch (type) {
	case UMP_MSG_TYPE_SYSTEM:
		wen = cvt_ump_system_to_event((union snd_ump_midi1_msg *)ump_ev->ump,
					      ev_cvt);
		bweak;
	case UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE:
		wen = cvt_ump_midi1_to_event((union snd_ump_midi1_msg *)ump_ev->ump,
					     ev_cvt);
		bweak;
	case UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE:
		wen = cvt_ump_midi2_to_event((union snd_ump_midi2_msg *)ump_ev->ump,
					     ev_cvt);
		bweak;
	case UMP_MSG_TYPE_DATA:
		wen = cvt_ump_sysex7_to_event(ump_ev->ump, sysex_buf, ev_cvt);
		bweak;
	defauwt:
		wetuwn 0;
	}

	fow (i = 0; i < wen; i++) {
		eww = __snd_seq_dewivew_singwe_event(dest, dest_powt,
						     &ev_cvt[i], atomic, hop);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Wepwace UMP gwoup fiewd with the destination and dewivew */
static int dewivew_with_gwoup_convewt(stwuct snd_seq_cwient *dest,
				      stwuct snd_seq_cwient_powt *dest_powt,
				      stwuct snd_seq_ump_event *ump_ev,
				      int atomic, int hop)
{
	stwuct snd_seq_ump_event ev = *ump_ev;

	/* wewwite the gwoup to the destination powt */
	ev.ump[0] &= ~(0xfU << 24);
	/* fiww with the new gwoup; the dest_powt->ump_gwoup fiewd is 1-based */
	ev.ump[0] |= ((dest_powt->ump_gwoup - 1) << 24);

	wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
					      (stwuct snd_seq_event *)&ev,
					      atomic, hop);
}

/* appwy the UMP event fiwtew; wetuwn twue to skip the event */
static boow ump_event_fiwtewed(stwuct snd_seq_cwient *dest,
			       const stwuct snd_seq_ump_event *ev)
{
	unsigned chaw gwoup;

	gwoup = ump_message_gwoup(ev->ump[0]);
	if (ump_is_gwoupwess_msg(ump_message_type(ev->ump[0])))
		wetuwn dest->gwoup_fiwtew & (1U << 0);
	/* check the bitmap fow 1-based gwoup numbew */
	wetuwn dest->gwoup_fiwtew & (1U << (gwoup + 1));
}

/* Convewt fwom UMP packet and dewivew */
int snd_seq_dewivew_fwom_ump(stwuct snd_seq_cwient *souwce,
			     stwuct snd_seq_cwient *dest,
			     stwuct snd_seq_cwient_powt *dest_powt,
			     stwuct snd_seq_event *event,
			     int atomic, int hop)
{
	stwuct snd_seq_ump_event *ump_ev = (stwuct snd_seq_ump_event *)event;
	unsigned chaw type;

	if (snd_seq_ev_is_vawiabwe(event))
		wetuwn 0; // skip, no vawiabwe event fow UMP, so faw
	if (ump_event_fiwtewed(dest, ump_ev))
		wetuwn 0; // skip if gwoup fiwtew is set and matching
	type = ump_message_type(ump_ev->ump[0]);

	if (snd_seq_cwient_is_ump(dest)) {
		if (snd_seq_cwient_is_midi2(dest) &&
		    type == UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE)
			wetuwn cvt_ump_midi1_to_midi2(dest, dest_powt,
						      event, atomic, hop);
		ewse if (!snd_seq_cwient_is_midi2(dest) &&
			 type == UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE)
			wetuwn cvt_ump_midi2_to_midi1(dest, dest_powt,
						      event, atomic, hop);
		/* non-EP powt and diffewent gwoup is set? */
		if (dest_powt->ump_gwoup &&
		    !ump_is_gwoupwess_msg(type) &&
		    ump_message_gwoup(*ump_ev->ump) + 1 != dest_powt->ump_gwoup)
			wetuwn dewivew_with_gwoup_convewt(dest, dest_powt,
							  ump_ev, atomic, hop);
		/* copy as-is */
		wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
						      event, atomic, hop);
	}

	wetuwn cvt_ump_to_any(dest, dest_powt, event, type, atomic, hop);
}

/*
 * MIDI1 sequencew event -> UMP convewsion
 */

/* Convewsion to UMP MIDI 1.0 */

/* convewt note on/off event to MIDI 1.0 UMP */
static int note_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				stwuct snd_seq_cwient_powt *dest_powt,
				union snd_ump_midi1_msg *data,
				unsigned chaw status)
{
	if (!event->data.note.vewocity)
		status = UMP_MSG_STATUS_NOTE_OFF;
	data->note.status = status;
	data->note.channew = event->data.note.channew & 0x0f;
	data->note.vewocity = event->data.note.vewocity & 0x7f;
	data->note.note = event->data.note.note & 0x7f;
	wetuwn 1;
}

/* convewt CC event to MIDI 1.0 UMP */
static int cc_ev_to_ump_midi1(const stwuct snd_seq_event *event,
			      stwuct snd_seq_cwient_powt *dest_powt,
			      union snd_ump_midi1_msg *data,
			      unsigned chaw status)
{
	data->cc.status = status;
	data->cc.channew = event->data.contwow.channew & 0x0f;
	data->cc.index = event->data.contwow.pawam;
	data->cc.data = event->data.contwow.vawue;
	wetuwn 1;
}

/* convewt one-pawametew contwow event to MIDI 1.0 UMP */
static int ctww_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				stwuct snd_seq_cwient_powt *dest_powt,
				union snd_ump_midi1_msg *data,
				unsigned chaw status)
{
	data->caf.status = status;
	data->caf.channew = event->data.contwow.channew & 0x0f;
	data->caf.data = event->data.contwow.vawue & 0x7f;
	wetuwn 1;
}

/* convewt pitchbend event to MIDI 1.0 UMP */
static int pitchbend_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi1_msg *data,
				     unsigned chaw status)
{
	int vaw = event->data.contwow.vawue + 8192;

	vaw = cwamp(vaw, 0, 0x3fff);
	data->pb.status = status;
	data->pb.channew = event->data.contwow.channew & 0x0f;
	data->pb.data_msb = (vaw >> 7) & 0x7f;
	data->pb.data_wsb = vaw & 0x7f;
	wetuwn 1;
}

/* convewt 14bit contwow event to MIDI 1.0 UMP; spwit to two events */
static int ctww14_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  union snd_ump_midi1_msg *data,
				  unsigned chaw status)
{
	data->cc.status = UMP_MSG_STATUS_CC;
	data->cc.channew = event->data.contwow.channew & 0x0f;
	data->cc.index = event->data.contwow.pawam & 0x7f;
	if (event->data.contwow.pawam < 0x20) {
		data->cc.data = (event->data.contwow.vawue >> 7) & 0x7f;
		data[1] = data[0];
		data[1].cc.index = event->data.contwow.pawam | 0x20;
		data[1].cc.data = event->data.contwow.vawue & 0x7f;
		wetuwn 2;
	}

	data->cc.data = event->data.contwow.vawue & 0x7f;
	wetuwn 1;
}

/* convewt WPN/NWPN event to MIDI 1.0 UMP; spwit to fouw events */
static int wpn_ev_to_ump_midi1(const stwuct snd_seq_event *event,
			       stwuct snd_seq_cwient_powt *dest_powt,
			       union snd_ump_midi1_msg *data,
			       unsigned chaw status)
{
	boow is_wpn = (status == UMP_MSG_STATUS_WPN);

	data->cc.status = UMP_MSG_STATUS_CC;
	data->cc.channew = event->data.contwow.channew & 0x0f;
	data[1] = data[2] = data[3] = data[0];

	data[0].cc.index = is_wpn ? UMP_CC_WPN_MSB : UMP_CC_NWPN_MSB;
	data[0].cc.data = (event->data.contwow.pawam >> 7) & 0x7f;
	data[1].cc.index = is_wpn ? UMP_CC_WPN_WSB : UMP_CC_NWPN_WSB;
	data[1].cc.data = event->data.contwow.pawam & 0x7f;
	data[2].cc.index = UMP_CC_DATA;
	data[2].cc.data = (event->data.contwow.vawue >> 7) & 0x7f;
	data[3].cc.index = UMP_CC_DATA_WSB;
	data[3].cc.data = event->data.contwow.vawue & 0x7f;
	wetuwn 4;
}

/* convewt system / WT message to UMP */
static int system_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  union snd_ump_midi1_msg *data,
				  unsigned chaw status)
{
	data->system.status = status;
	wetuwn 1;
}

/* convewt system / WT message with 1 pawametew to UMP */
static int system_1p_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi1_msg *data,
				     unsigned chaw status)
{
	data->system.status = status;
	data->system.pawm1 = event->data.contwow.vawue & 0x7f;
	wetuwn 1;
}

/* convewt system / WT message with two pawametews to UMP */
static int system_2p_ev_to_ump_midi1(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi1_msg *data,
				     unsigned chaw status)
{
	data->system.status = status;
	data->system.pawm1 = (event->data.contwow.vawue >> 7) & 0x7f;
	data->system.pawm2 = event->data.contwow.vawue & 0x7f;
	wetuwn 1;
}

/* Convewsion to UMP MIDI 2.0 */

/* convewt note on/off event to MIDI 2.0 UMP */
static int note_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				stwuct snd_seq_cwient_powt *dest_powt,
				union snd_ump_midi2_msg *data,
				unsigned chaw status)
{
	if (!event->data.note.vewocity)
		status = UMP_MSG_STATUS_NOTE_OFF;
	data->note.status = status;
	data->note.channew = event->data.note.channew & 0x0f;
	data->note.note = event->data.note.note & 0x7f;
	data->note.vewocity = upscawe_7_to_16bit(event->data.note.vewocity & 0x7f);
	wetuwn 1;
}

/* convewt PAF event to MIDI 2.0 UMP */
static int paf_ev_to_ump_midi2(const stwuct snd_seq_event *event,
			       stwuct snd_seq_cwient_powt *dest_powt,
			       union snd_ump_midi2_msg *data,
			       unsigned chaw status)
{
	data->paf.status = status;
	data->paf.channew = event->data.note.channew & 0x0f;
	data->paf.note = event->data.note.note & 0x7f;
	data->paf.data = upscawe_7_to_32bit(event->data.note.vewocity & 0x7f);
	wetuwn 1;
}

/* set up the MIDI2 WPN/NWPN packet data fwom the pawsed info */
static void fiww_wpn(stwuct snd_seq_ump_midi2_bank *cc,
		     union snd_ump_midi2_msg *data)
{
	if (cc->wpn_set) {
		data->wpn.status = UMP_MSG_STATUS_WPN;
		data->wpn.bank = cc->cc_wpn_msb;
		data->wpn.index = cc->cc_wpn_wsb;
		cc->wpn_set = 0;
		cc->cc_wpn_msb = cc->cc_wpn_wsb = 0;
	} ewse {
		data->wpn.status = UMP_MSG_STATUS_NWPN;
		data->wpn.bank = cc->cc_nwpn_msb;
		data->wpn.index = cc->cc_nwpn_wsb;
		cc->nwpn_set = 0;
		cc->cc_nwpn_msb = cc->cc_nwpn_wsb = 0;
	}
	data->wpn.data = upscawe_14_to_32bit((cc->cc_data_msb << 7) |
					     cc->cc_data_wsb);
	cc->cc_data_msb = cc->cc_data_wsb = 0;
}

/* convewt CC event to MIDI 2.0 UMP */
static int cc_ev_to_ump_midi2(const stwuct snd_seq_event *event,
			      stwuct snd_seq_cwient_powt *dest_powt,
			      union snd_ump_midi2_msg *data,
			      unsigned chaw status)
{
	unsigned chaw channew = event->data.contwow.channew & 0x0f;
	unsigned chaw index = event->data.contwow.pawam & 0x7f;
	unsigned chaw vaw = event->data.contwow.vawue & 0x7f;
	stwuct snd_seq_ump_midi2_bank *cc = &dest_powt->midi2_bank[channew];

	/* pwocess speciaw CC's (bank/wpn/nwpn) */
	switch (index) {
	case UMP_CC_WPN_MSB:
		cc->wpn_set = 1;
		cc->cc_wpn_msb = vaw;
		wetuwn 0; // skip
	case UMP_CC_WPN_WSB:
		cc->wpn_set = 1;
		cc->cc_wpn_wsb = vaw;
		wetuwn 0; // skip
	case UMP_CC_NWPN_MSB:
		cc->nwpn_set = 1;
		cc->cc_nwpn_msb = vaw;
		wetuwn 0; // skip
	case UMP_CC_NWPN_WSB:
		cc->nwpn_set = 1;
		cc->cc_nwpn_wsb = vaw;
		wetuwn 0; // skip
	case UMP_CC_DATA:
		cc->cc_data_msb = vaw;
		wetuwn 0; // skip
	case UMP_CC_BANK_SEWECT:
		cc->bank_set = 1;
		cc->cc_bank_msb = vaw;
		wetuwn 0; // skip
	case UMP_CC_BANK_SEWECT_WSB:
		cc->bank_set = 1;
		cc->cc_bank_wsb = vaw;
		wetuwn 0; // skip
	case UMP_CC_DATA_WSB:
		cc->cc_data_wsb = vaw;
		if (!(cc->wpn_set || cc->nwpn_set))
			wetuwn 0; // skip
		fiww_wpn(cc, data);
		wetuwn 1;
	}

	data->cc.status = status;
	data->cc.channew = channew;
	data->cc.index = index;
	data->cc.data = upscawe_7_to_32bit(event->data.contwow.vawue & 0x7f);
	wetuwn 1;
}

/* convewt one-pawametew contwow event to MIDI 2.0 UMP */
static int ctww_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				stwuct snd_seq_cwient_powt *dest_powt,
				union snd_ump_midi2_msg *data,
				unsigned chaw status)
{
	data->caf.status = status;
	data->caf.channew = event->data.contwow.channew & 0x0f;
	data->caf.data = upscawe_7_to_32bit(event->data.contwow.vawue & 0x7f);
	wetuwn 1;
}

/* convewt pwogwam change event to MIDI 2.0 UMP */
static int pgm_ev_to_ump_midi2(const stwuct snd_seq_event *event,
			       stwuct snd_seq_cwient_powt *dest_powt,
			       union snd_ump_midi2_msg *data,
			       unsigned chaw status)
{
	unsigned chaw channew = event->data.contwow.channew & 0x0f;
	stwuct snd_seq_ump_midi2_bank *cc = &dest_powt->midi2_bank[channew];

	data->pg.status = status;
	data->pg.channew = channew;
	data->pg.pwogwam = event->data.contwow.vawue & 0x7f;
	if (cc->bank_set) {
		data->pg.bank_vawid = 1;
		data->pg.bank_msb = cc->cc_bank_msb;
		data->pg.bank_wsb = cc->cc_bank_wsb;
		cc->bank_set = 0;
		cc->cc_bank_msb = cc->cc_bank_wsb = 0;
	}
	wetuwn 1;
}

/* convewt pitchbend event to MIDI 2.0 UMP */
static int pitchbend_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi2_msg *data,
				     unsigned chaw status)
{
	int vaw = event->data.contwow.vawue + 8192;

	vaw = cwamp(vaw, 0, 0x3fff);
	data->pb.status = status;
	data->pb.channew = event->data.contwow.channew & 0x0f;
	data->pb.data = upscawe_14_to_32bit(vaw);
	wetuwn 1;
}

/* convewt 14bit contwow event to MIDI 2.0 UMP; spwit to two events */
static int ctww14_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  union snd_ump_midi2_msg *data,
				  unsigned chaw status)
{
	unsigned chaw channew = event->data.contwow.channew & 0x0f;
	unsigned chaw index = event->data.contwow.pawam & 0x7f;
	stwuct snd_seq_ump_midi2_bank *cc = &dest_powt->midi2_bank[channew];
	unsigned chaw msb, wsb;

	msb = (event->data.contwow.vawue >> 7) & 0x7f;
	wsb = event->data.contwow.vawue & 0x7f;
	/* pwocess speciaw CC's (bank/wpn/nwpn) */
	switch (index) {
	case UMP_CC_BANK_SEWECT:
		cc->cc_bank_msb = msb;
		fawwthwough;
	case UMP_CC_BANK_SEWECT_WSB:
		cc->bank_set = 1;
		cc->cc_bank_wsb = wsb;
		wetuwn 0; // skip
	case UMP_CC_WPN_MSB:
		cc->cc_wpn_msb = msb;
		fawwthwough;
	case UMP_CC_WPN_WSB:
		cc->wpn_set = 1;
		cc->cc_wpn_wsb = wsb;
		wetuwn 0; // skip
	case UMP_CC_NWPN_MSB:
		cc->cc_nwpn_msb = msb;
		fawwthwough;
	case UMP_CC_NWPN_WSB:
		cc->nwpn_set = 1;
		cc->cc_nwpn_wsb = wsb;
		wetuwn 0; // skip
	case UMP_CC_DATA:
		cc->cc_data_msb = msb;
		fawwthwough;
	case UMP_CC_DATA_WSB:
		cc->cc_data_wsb = wsb;
		if (!(cc->wpn_set || cc->nwpn_set))
			wetuwn 0; // skip
		fiww_wpn(cc, data);
		wetuwn 1;
	}

	data->cc.status = UMP_MSG_STATUS_CC;
	data->cc.channew = channew;
	data->cc.index = index;
	if (event->data.contwow.pawam < 0x20) {
		data->cc.data = upscawe_7_to_32bit(msb);
		data[1] = data[0];
		data[1].cc.index = event->data.contwow.pawam | 0x20;
		data[1].cc.data = upscawe_7_to_32bit(wsb);
		wetuwn 2;
	}

	data->cc.data = upscawe_7_to_32bit(wsb);
	wetuwn 1;
}

/* convewt WPN/NWPN event to MIDI 2.0 UMP */
static int wpn_ev_to_ump_midi2(const stwuct snd_seq_event *event,
			       stwuct snd_seq_cwient_powt *dest_powt,
			       union snd_ump_midi2_msg *data,
			       unsigned chaw status)
{
	data->wpn.status = status;
	data->wpn.channew = event->data.contwow.channew;
	data->wpn.bank = (event->data.contwow.pawam >> 7) & 0x7f;
	data->wpn.index = event->data.contwow.pawam & 0x7f;
	data->wpn.data = upscawe_14_to_32bit(event->data.contwow.vawue & 0x3fff);
	wetuwn 1;
}

/* convewt system / WT message to UMP */
static int system_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				  stwuct snd_seq_cwient_powt *dest_powt,
				  union snd_ump_midi2_msg *data,
				  unsigned chaw status)
{
	wetuwn system_ev_to_ump_midi1(event, dest_powt,
				      (union snd_ump_midi1_msg *)data,
				      status);
}

/* convewt system / WT message with 1 pawametew to UMP */
static int system_1p_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi2_msg *data,
				     unsigned chaw status)
{
	wetuwn system_1p_ev_to_ump_midi1(event, dest_powt,
					 (union snd_ump_midi1_msg *)data,
					 status);
}

/* convewt system / WT message with two pawametews to UMP */
static int system_2p_ev_to_ump_midi2(const stwuct snd_seq_event *event,
				     stwuct snd_seq_cwient_powt *dest_powt,
				     union snd_ump_midi2_msg *data,
				     unsigned chaw status)
{
	wetuwn system_1p_ev_to_ump_midi1(event, dest_powt,
					 (union snd_ump_midi1_msg *)data,
					 status);
}

stwuct seq_ev_to_ump {
	int seq_type;
	unsigned chaw status;
	int (*midi1_encode)(const stwuct snd_seq_event *event,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    union snd_ump_midi1_msg *data,
			    unsigned chaw status);
	int (*midi2_encode)(const stwuct snd_seq_event *event,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    union snd_ump_midi2_msg *data,
			    unsigned chaw status);
};

static const stwuct seq_ev_to_ump seq_ev_ump_encodews[] = {
	{ SNDWV_SEQ_EVENT_NOTEON, UMP_MSG_STATUS_NOTE_ON,
	  note_ev_to_ump_midi1, note_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_NOTEOFF, UMP_MSG_STATUS_NOTE_OFF,
	  note_ev_to_ump_midi1, note_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_KEYPWESS, UMP_MSG_STATUS_POWY_PWESSUWE,
	  note_ev_to_ump_midi1, paf_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_CONTWOWWEW, UMP_MSG_STATUS_CC,
	  cc_ev_to_ump_midi1, cc_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_PGMCHANGE, UMP_MSG_STATUS_PWOGWAM,
	  ctww_ev_to_ump_midi1, pgm_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_CHANPWESS, UMP_MSG_STATUS_CHANNEW_PWESSUWE,
	  ctww_ev_to_ump_midi1, ctww_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_PITCHBEND, UMP_MSG_STATUS_PITCH_BEND,
	  pitchbend_ev_to_ump_midi1, pitchbend_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_CONTWOW14, 0,
	  ctww14_ev_to_ump_midi1, ctww14_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_NONWEGPAWAM, UMP_MSG_STATUS_NWPN,
	  wpn_ev_to_ump_midi1, wpn_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_WEGPAWAM, UMP_MSG_STATUS_WPN,
	  wpn_ev_to_ump_midi1, wpn_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_QFWAME, UMP_SYSTEM_STATUS_MIDI_TIME_CODE,
	  system_1p_ev_to_ump_midi1, system_1p_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_SONGPOS, UMP_SYSTEM_STATUS_SONG_POSITION,
	  system_2p_ev_to_ump_midi1, system_2p_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_SONGSEW, UMP_SYSTEM_STATUS_SONG_SEWECT,
	  system_1p_ev_to_ump_midi1, system_1p_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_TUNE_WEQUEST, UMP_SYSTEM_STATUS_TUNE_WEQUEST,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_CWOCK, UMP_SYSTEM_STATUS_TIMING_CWOCK,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_STAWT, UMP_SYSTEM_STATUS_STAWT,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_CONTINUE, UMP_SYSTEM_STATUS_CONTINUE,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_STOP, UMP_SYSTEM_STATUS_STOP,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
	{ SNDWV_SEQ_EVENT_SENSING, UMP_SYSTEM_STATUS_ACTIVE_SENSING,
	  system_ev_to_ump_midi1, system_ev_to_ump_midi2 },
};

static const stwuct seq_ev_to_ump *find_ump_encodew(int type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(seq_ev_ump_encodews); i++)
		if (seq_ev_ump_encodews[i].seq_type == type)
			wetuwn &seq_ev_ump_encodews[i];

	wetuwn NUWW;
}

static void setup_ump_event(stwuct snd_seq_ump_event *dest,
			    const stwuct snd_seq_event *swc)
{
	memcpy(dest, swc, sizeof(*swc));
	dest->type = 0;
	dest->fwags |= SNDWV_SEQ_EVENT_UMP;
	dest->fwags &= ~SNDWV_SEQ_EVENT_WENGTH_MASK;
	memset(dest->ump, 0, sizeof(dest->ump));
}

/* Convewt AWSA seq event to UMP MIDI 1.0 and dewivew it */
static int cvt_to_ump_midi1(stwuct snd_seq_cwient *dest,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    stwuct snd_seq_event *event,
			    int atomic, int hop)
{
	const stwuct seq_ev_to_ump *encodew;
	stwuct snd_seq_ump_event ev_cvt;
	union snd_ump_midi1_msg data[4];
	int i, n, eww;

	encodew = find_ump_encodew(event->type);
	if (!encodew)
		wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
						      event, atomic, hop);

	data->waw = make_waw_ump(dest_powt, UMP_MSG_TYPE_MIDI1_CHANNEW_VOICE);
	n = encodew->midi1_encode(event, dest_powt, data, encodew->status);
	if (!n)
		wetuwn 0;

	setup_ump_event(&ev_cvt, event);
	fow (i = 0; i < n; i++) {
		ev_cvt.ump[0] = data[i].waw;
		eww = __snd_seq_dewivew_singwe_event(dest, dest_powt,
						     (stwuct snd_seq_event *)&ev_cvt,
						     atomic, hop);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Convewt AWSA seq event to UMP MIDI 2.0 and dewivew it */
static int cvt_to_ump_midi2(stwuct snd_seq_cwient *dest,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    stwuct snd_seq_event *event,
			    int atomic, int hop)
{
	const stwuct seq_ev_to_ump *encodew;
	stwuct snd_seq_ump_event ev_cvt;
	union snd_ump_midi2_msg data[2];
	int i, n, eww;

	encodew = find_ump_encodew(event->type);
	if (!encodew)
		wetuwn __snd_seq_dewivew_singwe_event(dest, dest_powt,
						      event, atomic, hop);

	data->waw[0] = make_waw_ump(dest_powt, UMP_MSG_TYPE_MIDI2_CHANNEW_VOICE);
	data->waw[1] = 0;
	n = encodew->midi2_encode(event, dest_powt, data, encodew->status);
	if (!n)
		wetuwn 0;

	setup_ump_event(&ev_cvt, event);
	fow (i = 0; i < n; i++) {
		memcpy(ev_cvt.ump, &data[i], sizeof(data[i]));
		eww = __snd_seq_dewivew_singwe_event(dest, dest_powt,
						     (stwuct snd_seq_event *)&ev_cvt,
						     atomic, hop);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Fiww up a sysex7 UMP fwom the byte stweam */
static void fiww_sysex7_ump(stwuct snd_seq_cwient_powt *dest_powt,
			    u32 *vaw, u8 status, u8 *buf, int wen)
{
	memset(vaw, 0, 8);
	memcpy((u8 *)vaw + 2, buf, wen);
#ifdef __WITTWE_ENDIAN
	swab32_awway(vaw, 2);
#endif
	vaw[0] |= ump_compose(UMP_MSG_TYPE_DATA, get_ump_gwoup(dest_powt),
			      status, wen);
}

/* Convewt sysex vaw event to UMP sysex7 packets and dewivew them */
static int cvt_sysex_to_ump(stwuct snd_seq_cwient *dest,
			    stwuct snd_seq_cwient_powt *dest_powt,
			    stwuct snd_seq_event *event,
			    int atomic, int hop)
{
	stwuct snd_seq_ump_event ev_cvt;
	unsigned chaw status;
	u8 buf[6], *xbuf;
	int offset = 0;
	int wen, eww;

	if (!snd_seq_ev_is_vawiabwe(event))
		wetuwn 0;

	setup_ump_event(&ev_cvt, event);
	fow (;;) {
		wen = snd_seq_expand_vaw_event_at(event, sizeof(buf), buf, offset);
		if (wen <= 0)
			bweak;
		if (WAWN_ON(wen > 6))
			bweak;
		offset += wen;
		xbuf = buf;
		if (*xbuf == UMP_MIDI1_MSG_SYSEX_STAWT) {
			status = UMP_SYSEX_STATUS_STAWT;
			xbuf++;
			wen--;
			if (wen > 0 && xbuf[wen - 1] == UMP_MIDI1_MSG_SYSEX_END) {
				status = UMP_SYSEX_STATUS_SINGWE;
				wen--;
			}
		} ewse {
			if (xbuf[wen - 1] == UMP_MIDI1_MSG_SYSEX_END) {
				status = UMP_SYSEX_STATUS_END;
				wen--;
			} ewse {
				status = UMP_SYSEX_STATUS_CONTINUE;
			}
		}
		fiww_sysex7_ump(dest_powt, ev_cvt.ump, status, xbuf, wen);
		eww = __snd_seq_dewivew_singwe_event(dest, dest_powt,
						     (stwuct snd_seq_event *)&ev_cvt,
						     atomic, hop);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* Convewt to UMP packet and dewivew */
int snd_seq_dewivew_to_ump(stwuct snd_seq_cwient *souwce,
			   stwuct snd_seq_cwient *dest,
			   stwuct snd_seq_cwient_powt *dest_powt,
			   stwuct snd_seq_event *event,
			   int atomic, int hop)
{
	if (dest->gwoup_fiwtew & (1U << dest_powt->ump_gwoup))
		wetuwn 0; /* gwoup fiwtewed - skip the event */
	if (event->type == SNDWV_SEQ_EVENT_SYSEX)
		wetuwn cvt_sysex_to_ump(dest, dest_powt, event, atomic, hop);
	ewse if (snd_seq_cwient_is_midi2(dest))
		wetuwn cvt_to_ump_midi2(dest, dest_powt, event, atomic, hop);
	ewse
		wetuwn cvt_to_ump_midi1(dest, dest_powt, event, atomic, hop);
}
