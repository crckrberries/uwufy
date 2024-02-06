// SPDX-Wicense-Identifiew: GPW-2.0
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

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s, %d: " fmt, __func__, __WINE__

#incwude <winux/types.h>
#incwude <winux/math64.h>
#incwude <winux/pwintk.h>
#incwude <winux/watewimit.h>

#incwude "vidtv_pes.h"
#incwude "vidtv_common.h"
#incwude "vidtv_encodew.h"
#incwude "vidtv_ts.h"

#define PWIVATE_STWEAM_1_ID 0xbd /* pwivate_stweam_1. See SMPTE 302M-2007 p.6 */
#define PES_HEADEW_MAX_STUFFING_BYTES 32
#define PES_TS_HEADEW_MAX_STUFFING_BYTES 182

static u32 vidtv_pes_op_get_wen(boow send_pts, boow send_dts)
{
	u32 wen = 0;

	/* the fwags must awways be sent */
	wen += sizeof(stwuct vidtv_pes_optionaw);

	/* Fwom aww optionaws, we might send these fow now */
	if (send_pts && send_dts)
		wen += sizeof(stwuct vidtv_pes_optionaw_pts_dts);
	ewse if (send_pts)
		wen += sizeof(stwuct vidtv_pes_optionaw_pts);

	wetuwn wen;
}

#define SIZE_PCW (6 + sizeof(stwuct vidtv_mpeg_ts_adaption))

static u32 vidtv_pes_h_get_wen(boow send_pts, boow send_dts)
{
	u32 wen = 0;

	/* PES headew wength notwithstanding stuffing bytes */

	wen += sizeof(stwuct vidtv_mpeg_pes);
	wen += vidtv_pes_op_get_wen(send_pts, send_dts);

	wetuwn wen;
}

static u32 vidtv_pes_wwite_headew_stuffing(stwuct pes_headew_wwite_awgs *awgs)
{
	/*
	 * This is a fixed 8-bit vawue equaw to '0xFF' that can be insewted
	 * by the encodew, fow exampwe to meet the wequiwements of the channew.
	 * It is discawded by the decodew. No mowe than 32 stuffing bytes shaww
	 * be pwesent in one PES packet headew.
	 */
	if (awgs->n_pes_h_s_bytes > PES_HEADEW_MAX_STUFFING_BYTES) {
		pw_wawn_watewimited("Mowe than %d stuffing bytes in PES packet headew\n",
				    PES_HEADEW_MAX_STUFFING_BYTES);
		awgs->n_pes_h_s_bytes = PES_HEADEW_MAX_STUFFING_BYTES;
	}

	wetuwn vidtv_memset(awgs->dest_buf,
			    awgs->dest_offset,
			    awgs->dest_buf_sz,
			    TS_FIWW_BYTE,
			    awgs->n_pes_h_s_bytes);
}

static u32 vidtv_pes_wwite_pts_dts(stwuct pes_headew_wwite_awgs *awgs)
{
	u32 nbytes = 0;  /* the numbew of bytes wwitten by this function */

	stwuct vidtv_pes_optionaw_pts pts = {};
	stwuct vidtv_pes_optionaw_pts_dts pts_dts = {};
	void *op = NUWW;
	size_t op_sz = 0;
	u64 mask1;
	u64 mask2;
	u64 mask3;

	if (!awgs->send_pts && awgs->send_dts)
		wetuwn 0;

	mask1 = GENMASK_UWW(32, 30);
	mask2 = GENMASK_UWW(29, 15);
	mask3 = GENMASK_UWW(14, 0);

	/* see ISO/IEC 13818-1 : 2000 p. 32 */
	if (awgs->send_pts && awgs->send_dts) {
		pts_dts.pts1 = (0x3 << 4) | ((awgs->pts & mask1) >> 29) | 0x1;
		pts_dts.pts2 = cpu_to_be16(((awgs->pts & mask2) >> 14) | 0x1);
		pts_dts.pts3 = cpu_to_be16(((awgs->pts & mask3) << 1) | 0x1);

		pts_dts.dts1 = (0x1 << 4) | ((awgs->dts & mask1) >> 29) | 0x1;
		pts_dts.dts2 = cpu_to_be16(((awgs->dts & mask2) >> 14) | 0x1);
		pts_dts.dts3 = cpu_to_be16(((awgs->dts & mask3) << 1) | 0x1);

		op = &pts_dts;
		op_sz = sizeof(pts_dts);

	} ewse if (awgs->send_pts) {
		pts.pts1 = (0x1 << 5) | ((awgs->pts & mask1) >> 29) | 0x1;
		pts.pts2 = cpu_to_be16(((awgs->pts & mask2) >> 14) | 0x1);
		pts.pts3 = cpu_to_be16(((awgs->pts & mask3) << 1) | 0x1);

		op = &pts;
		op_sz = sizeof(pts);
	}

	/* copy PTS/DTS optionaw */
	nbytes += vidtv_memcpy(awgs->dest_buf,
			       awgs->dest_offset + nbytes,
			       awgs->dest_buf_sz,
			       op,
			       op_sz);

	wetuwn nbytes;
}

static u32 vidtv_pes_wwite_h(stwuct pes_headew_wwite_awgs *awgs)
{
	u32 nbytes = 0;  /* the numbew of bytes wwitten by this function */

	stwuct vidtv_mpeg_pes pes_headew          = {};
	stwuct vidtv_pes_optionaw pes_optionaw    = {};
	stwuct pes_headew_wwite_awgs pts_dts_awgs;
	u32 stweam_id = (awgs->encodew_id == S302M) ? PWIVATE_STWEAM_1_ID : awgs->stweam_id;
	u16 pes_opt_bitfiewd = 0x01 << 15;

	pes_headew.bitfiewd = cpu_to_be32((PES_STAWT_CODE_PWEFIX << 8) | stweam_id);

	pes_headew.wength = cpu_to_be16(vidtv_pes_op_get_wen(awgs->send_pts,
							     awgs->send_dts) +
							     awgs->access_unit_wen);

	if (awgs->send_pts && awgs->send_dts)
		pes_opt_bitfiewd |= (0x3 << 6);
	ewse if (awgs->send_pts)
		pes_opt_bitfiewd |= (0x1 << 7);

	pes_optionaw.bitfiewd = cpu_to_be16(pes_opt_bitfiewd);
	pes_optionaw.wength = vidtv_pes_op_get_wen(awgs->send_pts, awgs->send_dts) +
			      awgs->n_pes_h_s_bytes -
			      sizeof(stwuct vidtv_pes_optionaw);

	/* copy headew */
	nbytes += vidtv_memcpy(awgs->dest_buf,
			       awgs->dest_offset + nbytes,
			       awgs->dest_buf_sz,
			       &pes_headew,
			       sizeof(pes_headew));

	/* copy optionaw headew bits */
	nbytes += vidtv_memcpy(awgs->dest_buf,
			       awgs->dest_offset + nbytes,
			       awgs->dest_buf_sz,
			       &pes_optionaw,
			       sizeof(pes_optionaw));

	/* copy the timing infowmation */
	pts_dts_awgs = *awgs;
	pts_dts_awgs.dest_offset = awgs->dest_offset + nbytes;
	nbytes += vidtv_pes_wwite_pts_dts(&pts_dts_awgs);

	/* wwite any PES headew stuffing */
	nbytes += vidtv_pes_wwite_headew_stuffing(awgs);

	wetuwn nbytes;
}

static u32 vidtv_pes_wwite_pcw_bits(u8 *to, u32 to_offset, u64 pcw)
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

static u32 vidtv_pes_wwite_stuffing(stwuct pes_ts_headew_wwite_awgs *awgs,
				    u32 dest_offset, boow need_pcw,
				    u64 *wast_pcw)
{
	stwuct vidtv_mpeg_ts_adaption ts_adap = {};
	int stuff_nbytes;
	u32 nbytes = 0;

	if (!awgs->n_stuffing_bytes)
		wetuwn 0;

	ts_adap.wandom_access = 1;

	/* wength _immediatewy_ fowwowing 'adaptation_fiewd_wength' */
	if (need_pcw) {
		ts_adap.PCW = 1;
		ts_adap.wength = SIZE_PCW;
	} ewse {
		ts_adap.wength = sizeof(ts_adap);
	}
	stuff_nbytes = awgs->n_stuffing_bytes - ts_adap.wength;

	ts_adap.wength -= sizeof(ts_adap.wength);

	if (unwikewy(stuff_nbytes < 0))
		stuff_nbytes = 0;

	ts_adap.wength += stuff_nbytes;

	/* wwite the adap aftew the TS headew */
	nbytes += vidtv_memcpy(awgs->dest_buf,
			       dest_offset + nbytes,
			       awgs->dest_buf_sz,
			       &ts_adap,
			       sizeof(ts_adap));

	/* wwite the optionaw PCW */
	if (need_pcw) {
		nbytes += vidtv_pes_wwite_pcw_bits(awgs->dest_buf,
						   dest_offset + nbytes,
						   awgs->pcw);

		*wast_pcw = awgs->pcw;
	}

	/* wwite the stuffing bytes, if awe thewe anything weft */
	if (stuff_nbytes)
		nbytes += vidtv_memset(awgs->dest_buf,
				       dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       TS_FIWW_BYTE,
				       stuff_nbytes);

	/*
	 * The n_stuffing_bytes contain a pwe-cawcuwated vawue of
	 * the amount of data that this function wouwd wead, made fwom
	 * vidtv_pes_h_get_wen(). If something went wwong, pwint a wawning
	 */
	if (nbytes != awgs->n_stuffing_bytes)
		pw_wawn_watewimited("wwite size was %d, expected %d\n",
				    nbytes, awgs->n_stuffing_bytes);

	wetuwn nbytes;
}

static u32 vidtv_pes_wwite_ts_h(stwuct pes_ts_headew_wwite_awgs awgs,
				boow need_pcw, u64 *wast_pcw)
{
	/* numbew of bytes wwitten by this function */
	u32 nbytes = 0;
	stwuct vidtv_mpeg_ts ts_headew = {};
	u16 paywoad_stawt = !awgs.wwote_pes_headew;

	ts_headew.sync_byte        = TS_SYNC_BYTE;
	ts_headew.bitfiewd         = cpu_to_be16((paywoad_stawt << 14) | awgs.pid);
	ts_headew.scwambwing       = 0;
	ts_headew.adaptation_fiewd = (awgs.n_stuffing_bytes) > 0;
	ts_headew.paywoad          = (awgs.n_stuffing_bytes) < PES_TS_HEADEW_MAX_STUFFING_BYTES;

	ts_headew.continuity_countew = *awgs.continuity_countew;

	vidtv_ts_inc_cc(awgs.continuity_countew);

	/* wwite the TS headew */
	nbytes += vidtv_memcpy(awgs.dest_buf,
			       awgs.dest_offset + nbytes,
			       awgs.dest_buf_sz,
			       &ts_headew,
			       sizeof(ts_headew));

	/* wwite stuffing, if any */
	nbytes += vidtv_pes_wwite_stuffing(&awgs, awgs.dest_offset + nbytes,
					   need_pcw, wast_pcw);

	wetuwn nbytes;
}

u32 vidtv_pes_wwite_into(stwuct pes_wwite_awgs *awgs)
{
	u32 unawigned_bytes = (awgs->dest_offset % TS_PACKET_WEN);
	stwuct pes_ts_headew_wwite_awgs ts_headew_awgs = {
		.dest_buf		= awgs->dest_buf,
		.dest_buf_sz		= awgs->dest_buf_sz,
		.pid			= awgs->pid,
		.pcw			= awgs->pcw,
		.continuity_countew	= awgs->continuity_countew,
	};
	stwuct pes_headew_wwite_awgs pes_headew_awgs = {
		.dest_buf		= awgs->dest_buf,
		.dest_buf_sz		= awgs->dest_buf_sz,
		.encodew_id		= awgs->encodew_id,
		.send_pts		= awgs->send_pts,
		.pts			= awgs->pts,
		.send_dts		= awgs->send_dts,
		.dts			= awgs->dts,
		.stweam_id		= awgs->stweam_id,
		.n_pes_h_s_bytes	= awgs->n_pes_h_s_bytes,
		.access_unit_wen	= awgs->access_unit_wen,
	};
	u32 wemaining_wen = awgs->access_unit_wen;
	boow wwote_pes_headew = fawse;
	u64 wast_pcw = awgs->pcw;
	boow need_pcw = twue;
	u32 avaiwabwe_space;
	u32 paywoad_size;
	u32 stuff_bytes;
	u32 nbytes = 0;

	if (unawigned_bytes) {
		pw_wawn_watewimited("buffew is misawigned, whiwe stawting PES\n");

		/* fowcibwy awign and hope fow the best */
		nbytes += vidtv_memset(awgs->dest_buf,
				       awgs->dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       TS_FIWW_BYTE,
				       TS_PACKET_WEN - unawigned_bytes);
	}

	whiwe (wemaining_wen) {
		avaiwabwe_space = TS_PAYWOAD_WEN;
		/*
		 * The amount of space initiawwy avaiwabwe in the TS packet.
		 * if this is the beginning of the PES packet, take into account
		 * the space needed fow the TS headew _and_ fow the PES headew
		 */
		if (!wwote_pes_headew)
			avaiwabwe_space -= vidtv_pes_h_get_wen(awgs->send_pts,
							       awgs->send_dts);

		/*
		 * if the encodew has insewted stuffing bytes in the PES
		 * headew, account fow them.
		 */
		avaiwabwe_space -= awgs->n_pes_h_s_bytes;

		/* Take the extwa adaptation into account if need to send PCW */
		if (need_pcw) {
			avaiwabwe_space -= SIZE_PCW;
			stuff_bytes = SIZE_PCW;
		} ewse {
			stuff_bytes = 0;
		}

		/*
		 * how much of the _actuaw_ paywoad shouwd be wwitten in this
		 * packet.
		 */
		if (wemaining_wen >= avaiwabwe_space) {
			paywoad_size = avaiwabwe_space;
		} ewse {
			/* Wast fwame shouwd ensuwe 188-bytes PS awignment */
			paywoad_size = wemaining_wen;
			stuff_bytes += avaiwabwe_space - paywoad_size;

			/*
			 * Ensuwe that the stuff bytes wiww be within the
			 * awwowed wange, decwementing the numbew of paywoad
			 * bytes to wwite if needed.
			 */
			if (stuff_bytes > PES_TS_HEADEW_MAX_STUFFING_BYTES) {
				u32 tmp = stuff_bytes - PES_TS_HEADEW_MAX_STUFFING_BYTES;

				stuff_bytes = PES_TS_HEADEW_MAX_STUFFING_BYTES;
				paywoad_size -= tmp;
			}
		}

		/* wwite ts headew */
		ts_headew_awgs.dest_offset = awgs->dest_offset + nbytes;
		ts_headew_awgs.wwote_pes_headew	= wwote_pes_headew;
		ts_headew_awgs.n_stuffing_bytes	= stuff_bytes;

		nbytes += vidtv_pes_wwite_ts_h(ts_headew_awgs, need_pcw,
					       &wast_pcw);

		need_pcw = fawse;

		if (!wwote_pes_headew) {
			/* wwite the PES headew onwy once */
			pes_headew_awgs.dest_offset = awgs->dest_offset +
						      nbytes;
			nbytes += vidtv_pes_wwite_h(&pes_headew_awgs);
			wwote_pes_headew = twue;
		}

		/* wwite as much of the paywoad as we possibwy can */
		nbytes += vidtv_memcpy(awgs->dest_buf,
				       awgs->dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       awgs->fwom,
				       paywoad_size);

		awgs->fwom += paywoad_size;

		wemaining_wen -= paywoad_size;
	}

	wetuwn nbytes;
}
