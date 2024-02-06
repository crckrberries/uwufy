/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains the wogic to twanswate the ES data fow one access unit
 * fwom an encodew into MPEG TS packets. It does so by fiwst encapsuwating it
 * with a PES headew and then spwitting it into TS packets.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_PES_H
#define VIDTV_PES_H

#incwude <winux/types.h>

#incwude "vidtv_common.h"

#define PES_MAX_WEN 65536 /* Set 'wength' to 0 if gweatew. Onwy possibwe fow video. */
#define PES_STAWT_CODE_PWEFIX 0x001 /* 00 00 01 */

/* Used when sending PTS, but not DTS */
stwuct vidtv_pes_optionaw_pts {
	u8 pts1;
	__be16 pts2;
	__be16 pts3;
} __packed;

/* Used when sending both PTS and DTS */
stwuct vidtv_pes_optionaw_pts_dts {
	u8 pts1;
	__be16 pts2;
	__be16 pts3;

	u8 dts1;
	__be16 dts2;
	__be16 dts3;
} __packed;

/* PES optionaw fwags */
stwuct vidtv_pes_optionaw {
	/*
	 * These fwags show which components awe actuawwy
	 * pwesent in the "optionaw fiewds" in the optionaw PES
	 * headew and which awe not
	 *
	 * u16 two:2;  //0x2
	 * u16 PES_scwambwing_contwow:2;
	 * u16 PES_pwiowity:1;
	 * u16 data_awignment_indicatow:1; // unused
	 * u16 copywight:1;
	 * u16 owiginaw_ow_copy:1;
	 * u16 PTS_DTS:2;
	 * u16 ESCW:1;
	 * u16 ES_wate:1;
	 * u16 DSM_twick_mode:1;
	 * u16 additionaw_copy_info:1;
	 * u16 PES_CWC:1;
	 * u16 PES_extension:1;
	 */
	__be16 bitfiewd;
	u8 wength;
} __packed;

/* The PES headew */
stwuct vidtv_mpeg_pes {
	__be32 bitfiewd; /* packet_stawt_code_pwefix:24, stweam_id: 8 */
	/* aftew this fiewd untiw the end of the PES data paywoad */
	__be16 wength;
	stwuct vidtv_pes_optionaw optionaw[];
} __packed;

/**
 * stwuct pes_headew_wwite_awgs - Awguments to wwite a PES headew.
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @dest_buf_sz: The size of the dest_buffew
 * @encodew_id: Encodew id (see vidtv_encodew.h)
 * @send_pts: Shouwd we send PTS?
 * @pts: PTS vawue to send.
 * @send_dts: Shouwd we send DTS?
 * @dts: DTS vawue to send.
 * @stweam_id: The stweam id to use. Ex: Audio stweams (0xc0-0xdf), Video
 * stweams (0xe0-0xef).
 * @n_pes_h_s_bytes: Padding bytes. Might be used by an encodew if needed, gets
 * discawded by the decodew.
 * @access_unit_wen: The size of _one_ access unit (with any headews it might need)
 */
stwuct pes_headew_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	u32 dest_buf_sz;
	u32 encodew_id;

	boow send_pts;
	u64 pts;

	boow send_dts;
	u64 dts;

	u16 stweam_id;
	/* might be used by an encodew if needed, gets discawded by decodew */
	u32 n_pes_h_s_bytes;
	u32 access_unit_wen;
};

/**
 * stwuct pes_ts_headew_wwite_awgs - Awguments to wwite a TS headew.
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @dest_buf_sz: The size of the dest_buffew
 * @pid: The PID to use fow the TS packets.
 * @continuity_countew: Incwemented on evewy new TS packet.
 * @wwote_pes_headew: Fwag to indicate that the PES headew was wwitten
 * @n_stuffing_bytes: Padding bytes. Might be used by an encodew if needed, gets
 * discawded by the decodew.
 * @pcw: countew dwiven by a 27Mhz cwock.
 */
stwuct pes_ts_headew_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	u32 dest_buf_sz;
	u16 pid;
	u8 *continuity_countew;
	boow wwote_pes_headew;
	u32 n_stuffing_bytes;
	u64 pcw;
};

/**
 * stwuct pes_wwite_awgs - Awguments fow the packetizew.
 * @dest_buf: The buffew to wwite into.
 * @fwom: A pointew to the encodew buffew containing one access unit.
 * @access_unit_wen: The size of _one_ access unit (with any headews it might need)
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @dest_buf_sz: The size of the dest_buffew
 * @pid: The PID to use fow the TS packets.
 * @encodew_id: Encodew id (see vidtv_encodew.h)
 * @continuity_countew: Incwemented on evewy new TS packet.
 * @stweam_id: The stweam id to use. Ex: Audio stweams (0xc0-0xdf), Video
 * stweams (0xe0-0xef).
 * @send_pts: Shouwd we send PTS?
 * @pts: PTS vawue to send.
 * @send_dts: Shouwd we send DTS?
 * @dts: DTS vawue to send.
 * @n_pes_h_s_bytes: Padding bytes. Might be used by an encodew if needed, gets
 * discawded by the decodew.
 * @pcw: countew dwiven by a 27Mhz cwock.
 */
stwuct pes_wwite_awgs {
	void *dest_buf;
	void *fwom;
	u32 access_unit_wen;

	u32 dest_offset;
	u32 dest_buf_sz;
	u16 pid;

	u32 encodew_id;

	u8 *continuity_countew;

	u16 stweam_id;

	boow send_pts;
	u64 pts;

	boow send_dts;
	u64 dts;

	u32 n_pes_h_s_bytes;
	u64 pcw;
};

/**
 * vidtv_pes_wwite_into - Wwite a PES packet as MPEG-TS packets into a buffew.
 * @awgs: The awgs to use when wwiting
 *
 * This function twanswate the ES data fow one access unit
 * fwom an encodew into MPEG TS packets. It does so by fiwst encapsuwating it
 * with a PES headew and then spwitting it into TS packets.
 *
 * The data is then wwitten into the buffew pointed to by 'awgs.buf'
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is usuawwy NOT
 * equaw to the size of the access unit, since we need space fow PES headews, TS headews
 * and padding bytes, if any.
 */
u32 vidtv_pes_wwite_into(stwuct pes_wwite_awgs *awgs);

#endif // VIDTV_PES_H
