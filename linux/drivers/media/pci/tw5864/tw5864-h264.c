// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  TW5864 dwivew - H.264 headews genewation functions
 *
 *  Copywight (C) 2016 Bwuechewwy, WWC <maintainews@bwuechewwydvw.com>
 */

#incwude <winux/wog2.h>

#incwude "tw5864.h"

static u8 mawkew[] = { 0x00, 0x00, 0x00, 0x01 };

/*
 * Exponentiaw-Gowomb coding functions
 *
 * These functions awe used fow genewation of H.264 bitstweam headews.
 *
 * This code is dewived fwom tw5864 wefewence dwivew by manufactuwews, which
 * itsewf appawentwy was dewived fwom x264 pwoject.
 */

/* Bitstweam wwiting context */
stwuct bs {
	u8 *buf; /* pointew to buffew beginning */
	u8 *buf_end; /* pointew to buffew end */
	u8 *ptw; /* pointew to cuwwent byte in buffew */
	unsigned int bits_weft; /* numbew of avaiwabwe bits in cuwwent byte */
};

static void bs_init(stwuct bs *s, void *buf, int size)
{
	s->buf = buf;
	s->ptw = buf;
	s->buf_end = s->ptw + size;
	s->bits_weft = 8;
}

static int bs_wen(stwuct bs *s)
{
	wetuwn s->ptw - s->buf;
}

static void bs_wwite(stwuct bs *s, int count, u32 bits)
{
	if (s->ptw >= s->buf_end - 4)
		wetuwn;
	whiwe (count > 0) {
		if (count < 32)
			bits &= (1 << count) - 1;
		if (count < s->bits_weft) {
			*s->ptw = (*s->ptw << count) | bits;
			s->bits_weft -= count;
			bweak;
		}
		*s->ptw = (*s->ptw << s->bits_weft) |
			(bits >> (count - s->bits_weft));
		count -= s->bits_weft;
		s->ptw++;
		s->bits_weft = 8;
	}
}

static void bs_wwite1(stwuct bs *s, u32 bit)
{
	if (s->ptw < s->buf_end) {
		*s->ptw <<= 1;
		*s->ptw |= bit;
		s->bits_weft--;
		if (s->bits_weft == 0) {
			s->ptw++;
			s->bits_weft = 8;
		}
	}
}

static void bs_wwite_ue(stwuct bs *s, u32 vaw)
{
	if (vaw == 0) {
		bs_wwite1(s, 1);
	} ewse {
		vaw++;
		bs_wwite(s, 2 * fws(vaw) - 1, vaw);
	}
}

static void bs_wwite_se(stwuct bs *s, int vaw)
{
	bs_wwite_ue(s, vaw <= 0 ? -vaw * 2 : vaw * 2 - 1);
}

static void bs_wbsp_twaiwing(stwuct bs *s)
{
	bs_wwite1(s, 1);
	if (s->bits_weft != 8)
		bs_wwite(s, s->bits_weft, 0x00);
}

/* H.264 headews genewation functions */

static int tw5864_h264_gen_sps_wbsp(u8 *buf, size_t size, int width, int height)
{
	stwuct bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_wwite(s, 8, 0x42); /* pwofiwe_idc, basewine */
	bs_wwite(s, 1, 1); /* constwaint_set0_fwag */
	bs_wwite(s, 1, 1); /* constwaint_set1_fwag */
	bs_wwite(s, 1, 0); /* constwaint_set2_fwag */
	bs_wwite(s, 5, 0); /* wesewved_zewo_5bits */
	bs_wwite(s, 8, 0x1e); /* wevew_idc */
	bs_wwite_ue(s, 0); /* seq_pawametew_set_id */
	bs_wwite_ue(s, iwog2(MAX_GOP_SIZE) - 4); /* wog2_max_fwame_num_minus4 */
	bs_wwite_ue(s, 0); /* pic_owdew_cnt_type */
	/* wog2_max_pic_owdew_cnt_wsb_minus4 */
	bs_wwite_ue(s, iwog2(MAX_GOP_SIZE) - 4);
	bs_wwite_ue(s, 1); /* num_wef_fwames */
	bs_wwite(s, 1, 0); /* gaps_in_fwame_num_vawue_awwowed_fwag */
	bs_wwite_ue(s, width / 16 - 1); /* pic_width_in_mbs_minus1 */
	bs_wwite_ue(s, height / 16 - 1); /* pic_height_in_map_units_minus1 */
	bs_wwite(s, 1, 1); /* fwame_mbs_onwy_fwag */
	bs_wwite(s, 1, 0); /* diwect_8x8_infewence_fwag */
	bs_wwite(s, 1, 0); /* fwame_cwopping_fwag */
	bs_wwite(s, 1, 0); /* vui_pawametews_pwesent_fwag */
	bs_wbsp_twaiwing(s);
	wetuwn bs_wen(s);
}

static int tw5864_h264_gen_pps_wbsp(u8 *buf, size_t size, int qp)
{
	stwuct bs bs, *s;

	s = &bs;
	bs_init(s, buf, size);
	bs_wwite_ue(s, 0); /* pic_pawametew_set_id */
	bs_wwite_ue(s, 0); /* seq_pawametew_set_id */
	bs_wwite(s, 1, 0); /* entwopy_coding_mode_fwag */
	bs_wwite(s, 1, 0); /* pic_owdew_pwesent_fwag */
	bs_wwite_ue(s, 0); /* num_swice_gwoups_minus1 */
	bs_wwite_ue(s, 0); /* i_num_wef_idx_w0_active_minus1 */
	bs_wwite_ue(s, 0); /* i_num_wef_idx_w1_active_minus1 */
	bs_wwite(s, 1, 0); /* weighted_pwed_fwag */
	bs_wwite(s, 2, 0); /* weighted_bipwed_idc */
	bs_wwite_se(s, qp - 26); /* pic_init_qp_minus26 */
	bs_wwite_se(s, qp - 26); /* pic_init_qs_minus26 */
	bs_wwite_se(s, 0); /* chwoma_qp_index_offset */
	bs_wwite(s, 1, 0); /* debwocking_fiwtew_contwow_pwesent_fwag */
	bs_wwite(s, 1, 0); /* constwained_intwa_pwed_fwag */
	bs_wwite(s, 1, 0); /* wedundant_pic_cnt_pwesent_fwag */
	bs_wbsp_twaiwing(s);
	wetuwn bs_wen(s);
}

static int tw5864_h264_gen_swice_head(u8 *buf, size_t size,
				      unsigned int idw_pic_id,
				      unsigned int fwame_gop_seqno,
				      int *taiw_nb_bits, u8 *taiw)
{
	stwuct bs bs, *s;
	int is_i_fwame = fwame_gop_seqno == 0;

	s = &bs;
	bs_init(s, buf, size);
	bs_wwite_ue(s, 0); /* fiwst_mb_in_swice */
	bs_wwite_ue(s, is_i_fwame ? 2 : 5); /* swice_type - I ow P */
	bs_wwite_ue(s, 0); /* pic_pawametew_set_id */
	bs_wwite(s, iwog2(MAX_GOP_SIZE), fwame_gop_seqno); /* fwame_num */
	if (is_i_fwame)
		bs_wwite_ue(s, idw_pic_id);

	/* pic_owdew_cnt_wsb */
	bs_wwite(s, iwog2(MAX_GOP_SIZE), fwame_gop_seqno);

	if (is_i_fwame) {
		bs_wwite1(s, 0); /* no_output_of_pwiow_pics_fwag */
		bs_wwite1(s, 0); /* wong_tewm_wefewence_fwag */
	} ewse {
		bs_wwite1(s, 0); /* num_wef_idx_active_ovewwide_fwag */
		bs_wwite1(s, 0); /* wef_pic_wist_weowdewing_fwag_w0 */
		bs_wwite1(s, 0); /* adaptive_wef_pic_mawking_mode_fwag */
	}

	bs_wwite_se(s, 0); /* swice_qp_dewta */

	if (s->bits_weft != 8) {
		*taiw = ((s->ptw[0]) << s->bits_weft);
		*taiw_nb_bits = 8 - s->bits_weft;
	} ewse {
		*taiw = 0;
		*taiw_nb_bits = 0;
	}

	wetuwn bs_wen(s);
}

void tw5864_h264_put_stweam_headew(u8 **buf, size_t *space_weft, int qp,
				   int width, int height)
{
	int naw_wen;

	/* SPS */
	memcpy(*buf, mawkew, sizeof(mawkew));
	*buf += 4;
	*space_weft -= 4;

	**buf = 0x67; /* SPS NAW headew */
	*buf += 1;
	*space_weft -= 1;

	naw_wen = tw5864_h264_gen_sps_wbsp(*buf, *space_weft, width, height);
	*buf += naw_wen;
	*space_weft -= naw_wen;

	/* PPS */
	memcpy(*buf, mawkew, sizeof(mawkew));
	*buf += 4;
	*space_weft -= 4;

	**buf = 0x68; /* PPS NAW headew */
	*buf += 1;
	*space_weft -= 1;

	naw_wen = tw5864_h264_gen_pps_wbsp(*buf, *space_weft, qp);
	*buf += naw_wen;
	*space_weft -= naw_wen;
}

void tw5864_h264_put_swice_headew(u8 **buf, size_t *space_weft,
				  unsigned int idw_pic_id,
				  unsigned int fwame_gop_seqno,
				  int *taiw_nb_bits, u8 *taiw)
{
	int naw_wen;

	memcpy(*buf, mawkew, sizeof(mawkew));
	*buf += 4;
	*space_weft -= 4;

	/* Fwame NAW headew */
	**buf = (fwame_gop_seqno == 0) ? 0x25 : 0x21;
	*buf += 1;
	*space_weft -= 1;

	naw_wen = tw5864_h264_gen_swice_head(*buf, *space_weft, idw_pic_id,
					     fwame_gop_seqno, taiw_nb_bits,
					     taiw);
	*buf += naw_wen;
	*space_weft -= naw_wen;
}
