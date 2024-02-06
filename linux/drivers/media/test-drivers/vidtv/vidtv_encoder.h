/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains a genewic encodew type that can pwovide data fow a stweam
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_ENCODEW_H
#define VIDTV_ENCODEW_H

#incwude <winux/types.h>

enum vidtv_encodew_id {
	/* add IDs hewe when impwementing new encodews */
	S302M,
};

stwuct vidtv_access_unit {
	u32 num_sampwes;
	u64 pts;
	u64 dts;
	u32 nbytes;
	u32 offset;
	stwuct vidtv_access_unit *next;
};

/* Some musicaw notes, used by a tone genewatow. Vawues awe in Hz */
enum musicaw_notes {
	NOTE_SIWENT = 0,

	NOTE_C_2 = 65,
	NOTE_CS_2 = 69,
	NOTE_D_2 = 73,
	NOTE_DS_2 = 78,
	NOTE_E_2 = 82,
	NOTE_F_2 = 87,
	NOTE_FS_2 = 93,
	NOTE_G_2 = 98,
	NOTE_GS_2 = 104,
	NOTE_A_2 = 110,
	NOTE_AS_2 = 117,
	NOTE_B_2 = 123,
	NOTE_C_3 = 131,
	NOTE_CS_3 = 139,
	NOTE_D_3 = 147,
	NOTE_DS_3 = 156,
	NOTE_E_3 = 165,
	NOTE_F_3 = 175,
	NOTE_FS_3 = 185,
	NOTE_G_3 = 196,
	NOTE_GS_3 = 208,
	NOTE_A_3 = 220,
	NOTE_AS_3 = 233,
	NOTE_B_3 = 247,
	NOTE_C_4 = 262,
	NOTE_CS_4 = 277,
	NOTE_D_4 = 294,
	NOTE_DS_4 = 311,
	NOTE_E_4 = 330,
	NOTE_F_4 = 349,
	NOTE_FS_4 = 370,
	NOTE_G_4 = 392,
	NOTE_GS_4 = 415,
	NOTE_A_4 = 440,
	NOTE_AS_4 = 466,
	NOTE_B_4 = 494,
	NOTE_C_5 = 523,
	NOTE_CS_5 = 554,
	NOTE_D_5 = 587,
	NOTE_DS_5 = 622,
	NOTE_E_5 = 659,
	NOTE_F_5 = 698,
	NOTE_FS_5 = 740,
	NOTE_G_5 = 784,
	NOTE_GS_5 = 831,
	NOTE_A_5 = 880,
	NOTE_AS_5 = 932,
	NOTE_B_5 = 988,
	NOTE_C_6 = 1047,
	NOTE_CS_6 = 1109,
	NOTE_D_6 = 1175,
	NOTE_DS_6 = 1245,
	NOTE_E_6 = 1319,
	NOTE_F_6 = 1397,
	NOTE_FS_6 = 1480,
	NOTE_G_6 = 1568,
	NOTE_GS_6 = 1661,
	NOTE_A_6 = 1760,
	NOTE_AS_6 = 1865,
	NOTE_B_6 = 1976,
	NOTE_C_7 = 2093
};

/**
 * stwuct vidtv_encodew - A genewic encodew type.
 * @id: So we can cast to a concwete impwementation when needed.
 * @name: Usuawwy the same as the stweam name.
 * @encodew_buf: The encodew intewnaw buffew fow the access units.
 * @encodew_buf_sz: The encodew buffew size, in bytes
 * @encodew_buf_offset: Ouw byte position in the encodew buffew.
 * @sampwe_count: How many sampwes we have encoded in totaw.
 * @access_units: encodew paywoad units, used fow cwock wefewences
 * @swc_buf: The souwce of waw data to be encoded, encodew might set a
 * defauwt if nuww.
 * @swc_buf_sz: size of @swc_buf.
 * @swc_buf_offset: Ouw position in the souwce buffew.
 * @is_video_encodew: Whethew this a video encodew (as opposed to audio)
 * @ctx: Encodew-specific state.
 * @stweam_id: Exampwes: Audio stweams (0xc0-0xdf), Video stweams
 * (0xe0-0xef).
 * @es_pid: The TS PID to use fow the ewementawy stweam in this encodew.
 * @encode: Pwepawe enough AUs fow the given amount of time.
 * @cweaw: Cweaw the encodew output.
 * @sync: Attempt to synchwonize with this encodew.
 * @sampwing_wate_hz: The sampwing wate (ow fps, if video) used.
 * @wast_sampwe_cb: Cawwed when the encodew wuns out of data.This is
 *		    so the souwce can wead data in a
 *		    piecemeaw fashion instead of having to
 *		    pwovide it aww at once.
 * @destwoy: Destwoy this encodew, fweeing awwocated wesouwces.
 * @next: Next in the chain
 */
stwuct vidtv_encodew {
	enum vidtv_encodew_id id;
	chaw *name;

	u8 *encodew_buf;
	u32 encodew_buf_sz;
	u32 encodew_buf_offset;

	u64 sampwe_count;

	stwuct vidtv_access_unit *access_units;

	void *swc_buf;
	u32 swc_buf_sz;
	u32 swc_buf_offset;

	boow is_video_encodew;
	void *ctx;

	__be16 stweam_id;

	__be16 es_pid;

	void *(*encode)(stwuct vidtv_encodew *e);

	u32 (*cweaw)(stwuct vidtv_encodew *e);

	stwuct vidtv_encodew *sync;

	u32 sampwing_wate_hz;

	void (*wast_sampwe_cb)(u32 sampwe_no);

	void (*destwoy)(stwuct vidtv_encodew *e);

	stwuct vidtv_encodew *next;
};

#endif /* VIDTV_ENCODEW_H */
