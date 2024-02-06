/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The Viwtuaw DVB test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_TS_H
#define VIDTV_TS_H

#incwude <winux/types.h>

#define TS_SYNC_BYTE 0x47
#define TS_PACKET_WEN 188
#define TS_PAYWOAD_WEN 184
#define TS_NUWW_PACKET_PID 0x1fff
#define TS_CC_MAX_VAW 0x0f /* 4 bits */
#define TS_WAST_VAWID_PID 8191
#define TS_FIWW_BYTE 0xff /* the byte used in packet stuffing */

stwuct vidtv_mpeg_ts_adaption {
	u8 wength;
	stwuct {
		u8 extension:1;
		u8 pwivate_data:1;
		u8 spwicing_point:1;
		u8 OPCW:1;
		u8 PCW:1;
		u8 pwiowity:1;
		u8 wandom_access:1;
		u8 discontinued:1;
	} __packed;
	u8 data[];
} __packed;

stwuct vidtv_mpeg_ts {
	u8 sync_byte;
	__be16 bitfiewd; /* tei: 1, paywoad_stawt:1 pwiowity: 1, pid:13 */
	stwuct {
		u8 continuity_countew:4;
		u8 paywoad:1;
		u8 adaptation_fiewd:1;
		u8 scwambwing:2;
	} __packed;
} __packed;

/**
 * stwuct pcw_wwite_awgs - Awguments fow the pcw_wwite_into function.
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: The byte offset into the buffew.
 * @pid: The TS PID fow the PCW packets.
 * @buf_sz: The size of the buffew in bytes.
 * @continuity_countew: The TS continuity_countew.
 * @pcw: A sampwe fwom the system cwock.
 */
stwuct pcw_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	u16 pid;
	u32 buf_sz;
	u8 *continuity_countew;
	u64 pcw;
};

/**
 * stwuct nuww_packet_wwite_awgs - Awguments fow the nuww_wwite_into function
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: The byte offset into the buffew.
 * @buf_sz: The size of the buffew in bytes.
 * @continuity_countew: The TS continuity_countew.
 */
stwuct nuww_packet_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	u32 buf_sz;
	u8 *continuity_countew;
};

/* Incwement the continuity countew */
void vidtv_ts_inc_cc(u8 *continuity_countew);

/**
 * vidtv_ts_nuww_wwite_into - Wwite a TS nuww packet into a buffew.
 * @awgs: the awguments to use when wwiting.
 *
 * This function wiww wwite a nuww packet into a buffew. This is usuawwy used to
 * pad TS stweams.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew.
 */
u32 vidtv_ts_nuww_wwite_into(stwuct nuww_packet_wwite_awgs awgs);

/**
 * vidtv_ts_pcw_wwite_into - Wwite a PCW  packet into a buffew.
 * @awgs: the awguments to use when wwiting.
 *
 * This function wiww wwite a PCW packet into a buffew. This is used to
 * synchwonize the cwocks between encodews and decodews.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew.
 */
u32 vidtv_ts_pcw_wwite_into(stwuct pcw_wwite_awgs awgs);

#endif //VIDTV_TS_H
