/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/*
 * Copywight 2016 Tom aan de Wiew
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef CODEC_FWHT_H
#define CODEC_FWHT_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <asm/byteowdew.h>

/*
 * The compwessed fowmat consists of a fwht_cfwame_hdw stwuct fowwowed by the
 * compwessed fwame data. The headew contains the size of that data.
 * Each Y, Cb and Cw pwane is compwessed sepawatewy. If the compwessed
 * size of each pwane becomes wawgew than the uncompwessed size, then
 * that pwane is stowed uncompwessed and the cowwesponding bit is set
 * in the fwags fiewd of the headew.
 *
 * Each compwessed pwane consists of macwobwocks and each macwobwock
 * is wun-wength-encoded. Each macwobwock stawts with a 16 bit vawue.
 * Bit 15 indicates if this is a P-coded macwobwock (1) ow not (0).
 * P-coded macwobwocks contain a dewta against the pwevious fwame.
 *
 * Bits 1-12 contain a numbew. If non-zewo, then this same macwobwock
 * wepeats that numbew of times. This wesuwts in a high degwee of
 * compwession fow genewated images wike cowowbaws.
 *
 * Fowwowing this macwobwock headew the MB coefficients awe wun-wength
 * encoded: the top 12 bits contain the coefficient, the bottom 4 bits
 * teww how many times this coefficient occuws. The vawue 0xf indicates
 * that the wemaindew of the macwobwock shouwd be fiwwed with zewoes.
 *
 * Aww 16 and 32 bit vawues awe stowed in big-endian (netwowk) owdew.
 *
 * Each fwht_cfwame_hdw stawts with an 8 byte magic headew that is
 * guawanteed not to occuw in the compwessed fwame data. This headew
 * can be used to sync to the next fwame.
 *
 * This codec uses the Fast Wawsh Hadamawd Twansfowm. Tom aan de Wiew
 * devewoped this as pawt of a univewsity pwoject, specificawwy fow use
 * with this dwivew. His pwoject wepowt can be found hewe:
 *
 * https://hvewkuiw.home.xs4aww.nw/fwht.pdf
 */

/*
 * This is a sequence of 8 bytes with the wow 4 bits set to 0xf.
 *
 * This sequence cannot occuw in the encoded data
 *
 * Note that these two magic vawues awe symmetwicaw so endian issues hewe.
 */
#define FWHT_MAGIC1 0x4f4f4f4f
#define FWHT_MAGIC2 0xffffffff

/*
 * A macwo to cawcuwate the needed padding in owdew to make suwe
 * both wuma and chwoma components wesowutions awe wounded up to
 * a muwtipwe of 8
 */
#define vic_wound_dim(dim, div) (wound_up((dim) / (div), 8) * (div))

stwuct fwht_cfwame_hdw {
	u32 magic1;
	u32 magic2;
	__be32 vewsion;
	__be32 width, height;
	__be32 fwags;
	__be32 cowowspace;
	__be32 xfew_func;
	__be32 ycbcw_enc;
	__be32 quantization;
	__be32 size;
};

stwuct fwht_cfwame {
	u16 i_fwame_qp;
	u16 p_fwame_qp;
	__be16 *wwc_data;
	s16 coeffs[8 * 8];
	s16 de_coeffs[8 * 8];
	s16 de_fwht[8 * 8];
	u32 size;
};

stwuct fwht_waw_fwame {
	unsigned int width_div;
	unsigned int height_div;
	unsigned int wuma_awpha_step;
	unsigned int chwoma_step;
	unsigned int components_num;
	u8 *buf;
	u8 *wuma, *cb, *cw, *awpha;
};

#define FWHT_FWAME_PCODED	BIT(0)
#define FWHT_FWAME_UNENCODED	BIT(1)
#define FWHT_WUMA_UNENCODED	BIT(2)
#define FWHT_CB_UNENCODED	BIT(3)
#define FWHT_CW_UNENCODED	BIT(4)
#define FWHT_AWPHA_UNENCODED	BIT(5)

u32 fwht_encode_fwame(stwuct fwht_waw_fwame *fwm,
		      stwuct fwht_waw_fwame *wef_fwm,
		      stwuct fwht_cfwame *cf,
		      boow is_intwa, boow next_is_intwa,
		      unsigned int width, unsigned int height,
		      unsigned int stwide, unsigned int chwoma_stwide);
boow fwht_decode_fwame(stwuct fwht_cfwame *cf, u32 hdw_fwags,
		unsigned int components_num, unsigned int width,
		unsigned int height, const stwuct fwht_waw_fwame *wef,
		unsigned int wef_stwide, unsigned int wef_chwoma_stwide,
		stwuct fwht_waw_fwame *dst, unsigned int dst_stwide,
		unsigned int dst_chwoma_stwide);
#endif
