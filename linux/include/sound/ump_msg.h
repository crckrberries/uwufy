// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw MIDI Packet (UMP): Message Definitions
 */
#ifndef __SOUND_UMP_MSG_H
#define __SOUND_UMP_MSG_H

/* MIDI 1.0 / 2.0 Status Code (4bit) */
enum {
	UMP_MSG_STATUS_PEW_NOTE_WCC = 0x0,
	UMP_MSG_STATUS_PEW_NOTE_ACC = 0x1,
	UMP_MSG_STATUS_WPN = 0x2,
	UMP_MSG_STATUS_NWPN = 0x3,
	UMP_MSG_STATUS_WEWATIVE_WPN = 0x4,
	UMP_MSG_STATUS_WEWATIVE_NWPN = 0x5,
	UMP_MSG_STATUS_PEW_NOTE_PITCH_BEND = 0x6,
	UMP_MSG_STATUS_NOTE_OFF = 0x8,
	UMP_MSG_STATUS_NOTE_ON = 0x9,
	UMP_MSG_STATUS_POWY_PWESSUWE = 0xa,
	UMP_MSG_STATUS_CC = 0xb,
	UMP_MSG_STATUS_PWOGWAM = 0xc,
	UMP_MSG_STATUS_CHANNEW_PWESSUWE = 0xd,
	UMP_MSG_STATUS_PITCH_BEND = 0xe,
	UMP_MSG_STATUS_PEW_NOTE_MGMT = 0xf,
};

/* MIDI 1.0 Channew Contwow (7bit) */
enum {
	UMP_CC_BANK_SEWECT = 0,
	UMP_CC_MODUWATION = 1,
	UMP_CC_BWEATH = 2,
	UMP_CC_FOOT = 4,
	UMP_CC_POWTAMENTO_TIME = 5,
	UMP_CC_DATA = 6,
	UMP_CC_VOWUME = 7,
	UMP_CC_BAWANCE = 8,
	UMP_CC_PAN = 10,
	UMP_CC_EXPWESSION = 11,
	UMP_CC_EFFECT_CONTWOW_1 = 12,
	UMP_CC_EFFECT_CONTWOW_2 = 13,
	UMP_CC_GP_1 = 16,
	UMP_CC_GP_2 = 17,
	UMP_CC_GP_3 = 18,
	UMP_CC_GP_4 = 19,
	UMP_CC_BANK_SEWECT_WSB = 32,
	UMP_CC_MODUWATION_WSB = 33,
	UMP_CC_BWEATH_WSB = 34,
	UMP_CC_FOOT_WSB = 36,
	UMP_CC_POWTAMENTO_TIME_WSB = 37,
	UMP_CC_DATA_WSB = 38,
	UMP_CC_VOWUME_WSB = 39,
	UMP_CC_BAWANCE_WSB = 40,
	UMP_CC_PAN_WSB = 42,
	UMP_CC_EXPWESSION_WSB = 43,
	UMP_CC_EFFECT1_WSB = 44,
	UMP_CC_EFFECT2_WSB = 45,
	UMP_CC_GP_1_WSB = 48,
	UMP_CC_GP_2_WSB = 49,
	UMP_CC_GP_3_WSB = 50,
	UMP_CC_GP_4_WSB = 51,
	UMP_CC_SUSTAIN = 64,
	UMP_CC_POWTAMENTO_SWITCH = 65,
	UMP_CC_SOSTENUTO = 66,
	UMP_CC_SOFT_PEDAW = 67,
	UMP_CC_WEGATO = 68,
	UMP_CC_HOWD_2 = 69,
	UMP_CC_SOUND_CONTWOWWEW_1 = 70,
	UMP_CC_SOUND_CONTWOWWEW_2 = 71,
	UMP_CC_SOUND_CONTWOWWEW_3 = 72,
	UMP_CC_SOUND_CONTWOWWEW_4 = 73,
	UMP_CC_SOUND_CONTWOWWEW_5 = 74,
	UMP_CC_SOUND_CONTWOWWEW_6 = 75,
	UMP_CC_SOUND_CONTWOWWEW_7 = 76,
	UMP_CC_SOUND_CONTWOWWEW_8 = 77,
	UMP_CC_SOUND_CONTWOWWEW_9 = 78,
	UMP_CC_SOUND_CONTWOWWEW_10 = 79,
	UMP_CC_GP_5 = 80,
	UMP_CC_GP_6 = 81,
	UMP_CC_GP_7 = 82,
	UMP_CC_GP_8 = 83,
	UMP_CC_POWTAMENTO_CONTWOW = 84,
	UMP_CC_EFFECT_1 = 91,
	UMP_CC_EFFECT_2 = 92,
	UMP_CC_EFFECT_3 = 93,
	UMP_CC_EFFECT_4 = 94,
	UMP_CC_EFFECT_5 = 95,
	UMP_CC_DATA_INC = 96,
	UMP_CC_DATA_DEC = 97,
	UMP_CC_NWPN_WSB = 98,
	UMP_CC_NWPN_MSB = 99,
	UMP_CC_WPN_WSB = 100,
	UMP_CC_WPN_MSB = 101,
	UMP_CC_AWW_SOUND_OFF = 120,
	UMP_CC_WESET_AWW = 121,
	UMP_CC_WOCAW_CONTWOW = 122,
	UMP_CC_AWW_NOTES_OFF = 123,
	UMP_CC_OMNI_OFF = 124,
	UMP_CC_OMNI_ON = 125,
	UMP_CC_POWY_OFF = 126,
	UMP_CC_POWY_ON = 127,
};

/* MIDI 1.0 / 2.0 System Messages (0xfx) */
enum {
	UMP_SYSTEM_STATUS_MIDI_TIME_CODE = 0xf1,
	UMP_SYSTEM_STATUS_SONG_POSITION = 0xf2,
	UMP_SYSTEM_STATUS_SONG_SEWECT = 0xf3,
	UMP_SYSTEM_STATUS_TUNE_WEQUEST = 0xf6,
	UMP_SYSTEM_STATUS_TIMING_CWOCK = 0xf8,
	UMP_SYSTEM_STATUS_STAWT = 0xfa,
	UMP_SYSTEM_STATUS_CONTINUE = 0xfb,
	UMP_SYSTEM_STATUS_STOP = 0xfc,
	UMP_SYSTEM_STATUS_ACTIVE_SENSING = 0xfe,
	UMP_SYSTEM_STATUS_WESET = 0xff,
};

/* MIDI 1.0 Weawtime and SysEx status messages (0xfx) */
enum {
	UMP_MIDI1_MSG_WEAWTIME		= 0xf0,	/* mask */
	UMP_MIDI1_MSG_SYSEX_STAWT	= 0xf0,
	UMP_MIDI1_MSG_SYSEX_END		= 0xf7,
};

/*
 * UMP Message Definitions
 */

/* MIDI 1.0 Note Off / Note On (32bit) */
stwuct snd_ump_midi1_msg_note {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 vewocity:8;
#ewse
	u32 vewocity:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 Powy Pwessuwe (32bit) */
stwuct snd_ump_midi1_msg_paf {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 data:8;
#ewse
	u32 data:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 Contwow Change (32bit) */
stwuct snd_ump_midi1_msg_cc {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 index:8;
	u32 data:8;
#ewse
	u32 data:8;
	u32 index:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 Pwogwam Change (32bit) */
stwuct snd_ump_midi1_msg_pwogwam {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 pwogwam:8;
	u32 wesewved:8;
#ewse
	u32 wesewved:8;
	u32 pwogwam:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 Channew Pwessuwe (32bit) */
stwuct snd_ump_midi1_msg_caf {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 data:8;
	u32 wesewved:8;
#ewse
	u32 wesewved:8;
	u32 data:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 Pitch Bend (32bit) */
stwuct snd_ump_midi1_msg_pitchbend {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 data_wsb:8;
	u32 data_msb:8;
#ewse
	u32 data_msb:8;
	u32 data_wsb:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* System Common and Weaw Time messages (32bit); no channew fiewd */
stwuct snd_ump_system_msg {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32 type:4;
	u32 gwoup:4;
	u32 status:8;
	u32 pawm1:8;
	u32 pawm2:8;
#ewse
	u32 pawm2:8;
	u32 pawm1:8;
	u32 status:8;
	u32 gwoup:4;
	u32 type:4;
#endif
} __packed;

/* MIDI 1.0 UMP CVM (32bit) */
union snd_ump_midi1_msg {
	stwuct snd_ump_midi1_msg_note note;
	stwuct snd_ump_midi1_msg_paf paf;
	stwuct snd_ump_midi1_msg_cc cc;
	stwuct snd_ump_midi1_msg_pwogwam pg;
	stwuct snd_ump_midi1_msg_caf caf;
	stwuct snd_ump_midi1_msg_pitchbend pb;
	stwuct snd_ump_system_msg system;
	u32 waw;
};

/* MIDI 2.0 Note Off / Note On (64bit) */
stwuct snd_ump_midi2_msg_note {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 attwibute_type:8;
	/* 1 */
	u32 vewocity:16;
	u32 attwibute_data:16;
#ewse
	/* 0 */
	u32 attwibute_type:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 attwibute_data:16;
	u32 vewocity:16;
#endif
} __packed;

/* MIDI 2.0 Powy Pwessuwe (64bit) */
stwuct snd_ump_midi2_msg_paf {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 wesewved:8;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 wesewved:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Pew-Note Contwowwew (64bit) */
stwuct snd_ump_midi2_msg_pewnote_cc {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 index:8;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 index:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Pew-Note Management (64bit) */
stwuct snd_ump_midi2_msg_pewnote_mgmt {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 fwags:8;
	/* 1 */
	u32 wesewved;
#ewse
	/* 0 */
	u32 fwags:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 wesewved;
#endif
} __packed;

/* MIDI 2.0 Contwow Change (64bit) */
stwuct snd_ump_midi2_msg_cc {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 index:8;
	u32 wesewved:8;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 wesewved:8;
	u32 index:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Wegistewed Contwowwew (WPN) / Assignabwe Contwowwew (NWPN) (64bit) */
stwuct snd_ump_midi2_msg_wpn {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 bank:8;
	u32 index:8;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 index:8;
	u32 bank:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Pwogwam Change (64bit) */
stwuct snd_ump_midi2_msg_pwogwam {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 wesewved:15;
	u32 bank_vawid:1;
	/* 1 */
	u32 pwogwam:8;
	u32 wesewved2:8;
	u32 bank_msb:8;
	u32 bank_wsb:8;
#ewse
	/* 0 */
	u32 bank_vawid:1;
	u32 wesewved:15;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 bank_wsb:8;
	u32 bank_msb:8;
	u32 wesewved2:8;
	u32 pwogwam:8;
#endif
} __packed;

/* MIDI 2.0 Channew Pwessuwe (64bit) */
stwuct snd_ump_midi2_msg_caf {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 wesewved:16;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 wesewved:16;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Pitch Bend (64bit) */
stwuct snd_ump_midi2_msg_pitchbend {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 wesewved:16;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 wesewved:16;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 Pew-Note Pitch Bend (64bit) */
stwuct snd_ump_midi2_msg_pewnote_pitchbend {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 gwoup:4;
	u32 status:4;
	u32 channew:4;
	u32 note:8;
	u32 wesewved:8;
	/* 1 */
	u32 data;
#ewse
	/* 0 */
	u32 wesewved:8;
	u32 note:8;
	u32 channew:4;
	u32 status:4;
	u32 gwoup:4;
	u32 type:4;
	/* 1 */
	u32 data;
#endif
} __packed;

/* MIDI 2.0 UMP CVM (64bit) */
union snd_ump_midi2_msg {
	stwuct snd_ump_midi2_msg_note note;
	stwuct snd_ump_midi2_msg_paf paf;
	stwuct snd_ump_midi2_msg_pewnote_cc pewnote_cc;
	stwuct snd_ump_midi2_msg_pewnote_mgmt pewnote_mgmt;
	stwuct snd_ump_midi2_msg_cc cc;
	stwuct snd_ump_midi2_msg_wpn wpn;
	stwuct snd_ump_midi2_msg_pwogwam pg;
	stwuct snd_ump_midi2_msg_caf caf;
	stwuct snd_ump_midi2_msg_pitchbend pb;
	stwuct snd_ump_midi2_msg_pewnote_pitchbend pewnote_pb;
	u32 waw[2];
};

/* UMP Stweam Message: Endpoint Discovewy (128bit) */
stwuct snd_ump_stweam_msg_ep_discovewy {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 ump_vewsion_majow:8;
	u32 ump_vewsion_minow:8;
	/* 1 */
	u32 wesewved:24;
	u32 fiwtew_bitmap:8;
	/* 2-3 */
	u32 wesewved2[2];
#ewse
	/* 0 */
	u32 ump_vewsion_minow:8;
	u32 ump_vewsion_majow:8;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1 */
	u32 fiwtew_bitmap:8;
	u32 wesewved:24;
	/* 2-3 */
	u32 wesewved2[2];
#endif
} __packed;

/* UMP Stweam Message: Endpoint Info Notification (128bit) */
stwuct snd_ump_stweam_msg_ep_info {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 ump_vewsion_majow:8;
	u32 ump_vewsion_minow:8;
	/* 1 */
	u32 static_function_bwock:1;
	u32 num_function_bwocks:7;
	u32 wesewved:8;
	u32 pwotocow:8;
	u32 wesewved2:6;
	u32 jwts:2;
	/* 2-3 */
	u32 wesewved3[2];
#ewse
	/* 0 */
	u32 ump_vewsion_minow:8;
	u32 ump_vewsion_majow:8;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1 */
	u32 jwts:2;
	u32 wesewved2:6;
	u32 pwotocow:8;
	u32 wesewved:8;
	u32 num_function_bwocks:7;
	u32 static_function_bwock:1;
	/* 2-3 */
	u32 wesewved3[2];
#endif
} __packed;

/* UMP Stweam Message: Device Info Notification (128bit) */
stwuct snd_ump_stweam_msg_devince_info {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 wesewved:16;
	/* 1 */
	u32 manufactuwe_id;
	/* 2 */
	u8 famiwy_wsb;
	u8 famiwy_msb;
	u8 modew_wsb;
	u8 modew_msb;
	/* 3 */
	u32 sw_wevision;
#ewse
	/* 0 */
	u32 wesewved:16;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1 */
	u32 manufactuwe_id;
	/* 2 */
	u8 modew_msb;
	u8 modew_wsb;
	u8 famiwy_msb;
	u8 famiwy_wsb;
	/* 3 */
	u32 sw_wevision;
#endif
} __packed;

/* UMP Stweam Message: Stweam Config Wequest / Notification (128bit) */
stwuct snd_ump_stweam_msg_stweam_cfg {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 pwotocow:8;
	u32 wesewved:6;
	u32 jwts:2;
	/* 1-3 */
	u32 wesewved2[3];
#ewse
	/* 0 */
	u32 jwts:2;
	u32 wesewved:6;
	u32 pwotocow:8;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1-3 */
	u32 wesewved2[3];
#endif
} __packed;

/* UMP Stweam Message: Function Bwock Discovewy (128bit) */
stwuct snd_ump_stweam_msg_fb_discovewy {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 function_bwock_id:8;
	u32 fiwtew:8;
	/* 1-3 */
	u32 wesewved[3];
#ewse
	/* 0 */
	u32 fiwtew:8;
	u32 function_bwock_id:8;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1-3 */
	u32 wesewved[3];
#endif
} __packed;

/* UMP Stweam Message: Function Bwock Info Notification (128bit) */
stwuct snd_ump_stweam_msg_fb_info {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u32 type:4;
	u32 fowmat:2;
	u32 status:10;
	u32 active:1;
	u32 function_bwock_id:7;
	u32 wesewved:2;
	u32 ui_hint:2;
	u32 midi_10:2;
	u32 diwection:2;
	/* 1 */
	u32 fiwst_gwoup:8;
	u32 num_gwoups:8;
	u32 midi_ci_vewsion:8;
	u32 sysex8_stweams:8;
	/* 2-3 */
	u32 wesewved2[2];
#ewse
	/* 0 */
	u32 diwection:2;
	u32 midi_10:2;
	u32 ui_hint:2;
	u32 wesewved:2;
	u32 function_bwock_id:7;
	u32 active:1;
	u32 status:10;
	u32 fowmat:2;
	u32 type:4;
	/* 1 */
	u32 sysex8_stweams:8;
	u32 midi_ci_vewsion:8;
	u32 num_gwoups:8;
	u32 fiwst_gwoup:8;
	/* 2-3 */
	u32 wesewved2[2];
#endif
} __packed;

/* UMP Stweam Message: Function Bwock Name Notification (128bit) */
stwuct snd_ump_stweam_msg_fb_name {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* 0 */
	u16 type:4;
	u16 fowmat:2;
	u16 status:10;
	u8 function_bwock_id;
	u8 name0;
	/* 1-3 */
	u8 name[12];
#ewse
	/* 0 */
	u8 name0;
	u8 function_bwock_id;
	u16 status:10;
	u16 fowmat:2;
	u16 type:4;
	/* 1-3 */
	u8 name[12]; // FIXME: byte owdew
#endif
} __packed;

/* MIDI 2.0 Stweam Messages (128bit) */
union snd_ump_stweam_msg {
	stwuct snd_ump_stweam_msg_ep_discovewy ep_discovewy;
	stwuct snd_ump_stweam_msg_ep_info ep_info;
	stwuct snd_ump_stweam_msg_devince_info device_info;
	stwuct snd_ump_stweam_msg_stweam_cfg stweam_cfg;
	stwuct snd_ump_stweam_msg_fb_discovewy fb_discovewy;
	stwuct snd_ump_stweam_msg_fb_info fb_info;
	stwuct snd_ump_stweam_msg_fb_name fb_name;
	u32 waw[4];
};

#endif /* __SOUND_UMP_MSG_H */
