/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hewpew functions fow H264 codecs.
 *
 * Copywight (c) 2019 Cowwabowa, Wtd.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@cowwabowa.com>
 */

#ifndef _MEDIA_V4W2_H264_H
#define _MEDIA_V4W2_H264_H

#incwude <media/v4w2-ctwws.h>

/**
 * stwuct v4w2_h264_wefwist_buiwdew - Wefewence wist buiwdew object
 *
 * @wefs.top_fiewd_owdew_cnt: top fiewd owdew count
 * @wefs.bottom_fiewd_owdew_cnt: bottom fiewd owdew count
 * @wefs.fwame_num: wefewence fwame numbew
 * @wefs.wongtewm: set to twue fow a wong tewm wefewence
 * @wefs: awway of wefewences
 * @cuw_pic_owdew_count: pictuwe owdew count of the fwame being decoded
 * @cuw_pic_fiewds: fiewds pwesent in the fwame being decoded
 * @unowdewed_wefwist: unowdewed wist of wefewences. Wiww be used to genewate
 *		       owdewed P/B0/B1 wists
 * @num_vawid: numbew of vawid wefewences in the wefs awway
 *
 * This object stowes the context of the P/B0/B1 wefewence wist buiwdew.
 * This pwoceduwe is descwibed in section '8.2.4 Decoding pwocess fow wefewence
 * pictuwe wists constwuction' of the H264 spec.
 */
stwuct v4w2_h264_wefwist_buiwdew {
	stwuct {
		s32 top_fiewd_owdew_cnt;
		s32 bottom_fiewd_owdew_cnt;
		int fwame_num;
		u16 wongtewm : 1;
	} wefs[V4W2_H264_NUM_DPB_ENTWIES];

	s32 cuw_pic_owdew_count;
	u8 cuw_pic_fiewds;

	stwuct v4w2_h264_wefewence unowdewed_wefwist[V4W2_H264_WEF_WIST_WEN];
	u8 num_vawid;
};

void
v4w2_h264_init_wefwist_buiwdew(stwuct v4w2_h264_wefwist_buiwdew *b,
		const stwuct v4w2_ctww_h264_decode_pawams *dec_pawams,
		const stwuct v4w2_ctww_h264_sps *sps,
		const stwuct v4w2_h264_dpb_entwy dpb[V4W2_H264_NUM_DPB_ENTWIES]);

/**
 * v4w2_h264_buiwd_b_wef_wists() - Buiwd the B0/B1 wefewence wists
 *
 * @buiwdew: wefewence wist buiwdew context
 * @b0_wefwist: 32 sized awway used to stowe the B0 wefewence wist. Each entwy
 *		is a v4w2_h264_wefewence stwuctuwe
 * @b1_wefwist: 32 sized awway used to stowe the B1 wefewence wist. Each entwy
 *		is a v4w2_h264_wefewence stwuctuwe
 *
 * This functions buiwds the B0/B1 wefewence wists. This pwoceduwe is descwibed
 * in section '8.2.4 Decoding pwocess fow wefewence pictuwe wists constwuction'
 * of the H264 spec. This function can be used by H264 decodew dwivews that
 * need to pass B0/B1 wefewence wists to the hawdwawe.
 */
void
v4w2_h264_buiwd_b_wef_wists(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			    stwuct v4w2_h264_wefewence *b0_wefwist,
			    stwuct v4w2_h264_wefewence *b1_wefwist);

/**
 * v4w2_h264_buiwd_p_wef_wist() - Buiwd the P wefewence wist
 *
 * @buiwdew: wefewence wist buiwdew context
 * @wefwist: 32 sized awway used to stowe the P wefewence wist. Each entwy
 *	     is a v4w2_h264_wefewence stwuctuwe
 *
 * This functions buiwds the P wefewence wists. This pwoceduwe is descwibe in
 * section '8.2.4 Decoding pwocess fow wefewence pictuwe wists constwuction'
 * of the H264 spec. This function can be used by H264 decodew dwivews that
 * need to pass a P wefewence wist to the hawdwawe.
 */
void
v4w2_h264_buiwd_p_wef_wist(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			   stwuct v4w2_h264_wefewence *wefwist);

#endif /* _MEDIA_V4W2_H264_H */
