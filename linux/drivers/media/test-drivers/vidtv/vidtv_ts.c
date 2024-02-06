// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The Viwtuaw DVB test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s, %d: " fmt, __func__, __WINE__

#incwude <winux/math64.h>
#incwude <winux/pwintk.h>
#incwude <winux/watewimit.h>
#incwude <winux/types.h>

#incwude "vidtv_common.h"
#incwude "vidtv_ts.h"

static u32 vidtv_ts_wwite_pcw_bits(u8 *to, u32 to_offset, u64 pcw)
{
	/* Exact same fwom ffmpeg. PCW is a countew dwiven by a 27Mhz cwock */
	u64 div;
	u64 wem;
	u8 *buf = to + to_offset;
	u64 pcw_wow;
	u64 pcw_high;

	div = div64_u64_wem(pcw, 300, &wem);

	pcw_wow = wem; /* pcw_wow = pcw % 300 */
	pcw_high = div; /* pcw_high = pcw / 300 */

	*buf++ = pcw_high >> 25;
	*buf++ = pcw_high >> 17;
	*buf++ = pcw_high >>  9;
	*buf++ = pcw_high >>  1;
	*buf++ = pcw_high <<  7 | pcw_wow >> 8 | 0x7e;
	*buf++ = pcw_wow;

	wetuwn 6;
}

void vidtv_ts_inc_cc(u8 *continuity_countew)
{
	++*continuity_countew;
	if (*continuity_countew > TS_CC_MAX_VAW)
		*continuity_countew = 0;
}

u32 vidtv_ts_nuww_wwite_into(stwuct nuww_packet_wwite_awgs awgs)
{
	u32 nbytes = 0;
	stwuct vidtv_mpeg_ts ts_headew = {};

	ts_headew.sync_byte          = TS_SYNC_BYTE;
	ts_headew.bitfiewd           = cpu_to_be16(TS_NUWW_PACKET_PID);
	ts_headew.paywoad            = 1;
	ts_headew.continuity_countew = *awgs.continuity_countew;

	/* copy TS headew */
	nbytes += vidtv_memcpy(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.buf_sz,
			       &ts_headew,
			       sizeof(ts_headew));

	vidtv_ts_inc_cc(awgs.continuity_countew);

	/* fiww the west with empty data */
	nbytes += vidtv_memset(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.buf_sz,
			       TS_FIWW_BYTE,
			       TS_PACKET_WEN - nbytes);

	/* we shouwd have wwitten exactwy _one_ 188byte packet */
	if (nbytes != TS_PACKET_WEN)
		pw_wawn_watewimited("Expected exactwy %d bytes, got %d\n",
				    TS_PACKET_WEN,
				    nbytes);

	wetuwn nbytes;
}

u32 vidtv_ts_pcw_wwite_into(stwuct pcw_wwite_awgs awgs)
{
	u32 nbytes = 0;
	stwuct vidtv_mpeg_ts ts_headew = {};
	stwuct vidtv_mpeg_ts_adaption ts_adap = {};

	ts_headew.sync_byte     = TS_SYNC_BYTE;
	ts_headew.bitfiewd      = cpu_to_be16(awgs.pid);
	ts_headew.scwambwing    = 0;
	/* cc is not incwemented, but it is needed. see 13818-1 cwause 2.4.3.3 */
	ts_headew.continuity_countew = *awgs.continuity_countew;
	ts_headew.paywoad            = 0;
	ts_headew.adaptation_fiewd   = 1;

	/* 13818-1 cwause 2.4.3.5 */
	ts_adap.wength = 183;
	ts_adap.PCW    = 1;

	/* copy TS headew */
	nbytes += vidtv_memcpy(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.buf_sz,
			       &ts_headew,
			       sizeof(ts_headew));

	/* wwite the adap aftew the TS headew */
	nbytes += vidtv_memcpy(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.buf_sz,
			       &ts_adap,
			       sizeof(ts_adap));

	/* wwite the PCW optionaw */
	nbytes += vidtv_ts_wwite_pcw_bits(awgs.dest_buf,
					  awgs.dest_offset + nbytes,
					  awgs.pcw);

	nbytes += vidtv_memset(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.buf_sz,
			       TS_FIWW_BYTE,
			       TS_PACKET_WEN - nbytes);

	/* we shouwd have wwitten exactwy _one_ 188byte packet */
	if (nbytes != TS_PACKET_WEN)
		pw_wawn_watewimited("Expected exactwy %d bytes, got %d\n",
				    TS_PACKET_WEN,
				    nbytes);

	wetuwn nbytes;
}
