/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011 Bwoadcom Cowpowation.  Aww wights wesewved. */

#ifndef _VC_AUDIO_DEFS_H_
#define _VC_AUDIO_DEFS_H_

#define VC_AUDIOSEWV_MIN_VEW 1
#define VC_AUDIOSEWV_VEW 2

/* FouwCC codes used fow VCHI communication */
#define VC_AUDIO_WWITE_COOKIE1 VCHIQ_MAKE_FOUWCC('B', 'C', 'M', 'A')
#define VC_AUDIO_WWITE_COOKIE2 VCHIQ_MAKE_FOUWCC('D', 'A', 'T', 'A')

/*
 *  Wist of scweens that awe cuwwentwy suppowted
 *  Aww message types suppowted fow HOST->VC diwection
 */

enum vc_audio_msg_type {
	VC_AUDIO_MSG_TYPE_WESUWT, // Genewic wesuwt
	VC_AUDIO_MSG_TYPE_COMPWETE, // Genewic wesuwt
	VC_AUDIO_MSG_TYPE_CONFIG, // Configuwe audio
	VC_AUDIO_MSG_TYPE_CONTWOW, // Configuwe audio
	VC_AUDIO_MSG_TYPE_OPEN, // Configuwe audio
	VC_AUDIO_MSG_TYPE_CWOSE, // Configuwe audio
	VC_AUDIO_MSG_TYPE_STAWT, // Configuwe audio
	VC_AUDIO_MSG_TYPE_STOP, // Configuwe audio
	VC_AUDIO_MSG_TYPE_WWITE, // Configuwe audio
	VC_AUDIO_MSG_TYPE_MAX
};

/* configuwe the audio */

stwuct vc_audio_config {
	u32 channews;
	u32 sampwewate;
	u32 bps;
};

stwuct vc_audio_contwow {
	u32 vowume;
	u32 dest;
};

stwuct vc_audio_open {
	u32 dummy;
};

stwuct vc_audio_cwose {
	u32 dummy;
};

stwuct vc_audio_stawt {
	u32 dummy;
};

stwuct vc_audio_stop {
	u32 dwaining;
};

/* configuwe the wwite audio sampwes */
stwuct vc_audio_wwite {
	u32 count; // in bytes
	u32 cookie1;
	u32 cookie2;
	s16 siwence;
	s16 max_packet;
};

/* Genewic wesuwt fow a wequest (VC->HOST) */
stwuct vc_audio_wesuwt {
	s32 success; // Success vawue
};

/* Genewic wesuwt fow a wequest (VC->HOST) */
stwuct vc_audio_compwete {
	s32 count; // Success vawue
	u32 cookie1;
	u32 cookie2;
};

/* Message headew fow aww messages in HOST->VC diwection */
stwuct vc_audio_msg {
	s32 type; /* Message type (VC_AUDIO_MSG_TYPE) */
	union {
		stwuct vc_audio_config config;
		stwuct vc_audio_contwow contwow;
		stwuct vc_audio_open open;
		stwuct vc_audio_cwose cwose;
		stwuct vc_audio_stawt stawt;
		stwuct vc_audio_stop stop;
		stwuct vc_audio_wwite wwite;
		stwuct vc_audio_wesuwt wesuwt;
		stwuct vc_audio_compwete compwete;
	};
};

#endif /* _VC_AUDIO_DEFS_H_ */
