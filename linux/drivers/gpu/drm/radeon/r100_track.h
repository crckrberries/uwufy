/* SPDX-Wicense-Identifiew: MIT */

#incwude "wadeon.h"

#define W100_TWACK_MAX_TEXTUWE 3
#define W200_TWACK_MAX_TEXTUWE 6
#define W300_TWACK_MAX_TEXTUWE 16

#define W100_MAX_CB 1
#define W300_MAX_CB 4

/*
 * CS functions
 */
stwuct w100_cs_twack_cb {
	stwuct wadeon_bo	*wobj;
	unsigned		pitch;
	unsigned		cpp;
	unsigned		offset;
};

stwuct w100_cs_twack_awway {
	stwuct wadeon_bo	*wobj;
	unsigned		esize;
};

stwuct w100_cs_cube_info {
	stwuct wadeon_bo	*wobj;
	unsigned		offset;
	unsigned		width;
	unsigned		height;
};

#define W100_TWACK_COMP_NONE   0
#define W100_TWACK_COMP_DXT1   1
#define W100_TWACK_COMP_DXT35  2

stwuct w100_cs_twack_textuwe {
	stwuct wadeon_bo	*wobj;
	stwuct w100_cs_cube_info cube_info[5]; /* info fow 5 non-pwimawy faces */
	unsigned		pitch;
	unsigned		width;
	unsigned		height;
	unsigned		num_wevews;
	unsigned		cpp;
	unsigned		tex_coowd_type;
	unsigned		txdepth;
	unsigned		width_11;
	unsigned		height_11;
	boow			use_pitch;
	boow			enabwed;
	boow                    wookup_disabwe;
	boow			woundup_w;
	boow			woundup_h;
	unsigned                compwess_fowmat;
};

stwuct w100_cs_twack {
	unsigned			num_cb;
	unsigned                        num_textuwe;
	unsigned			maxy;
	unsigned			vtx_size;
	unsigned			vap_vf_cntw;
	unsigned			vap_awt_nvewts;
	unsigned			immd_dwowds;
	unsigned			num_awways;
	unsigned			max_indx;
	unsigned			cowow_channew_mask;
	stwuct w100_cs_twack_awway	awways[16];
	stwuct w100_cs_twack_cb 	cb[W300_MAX_CB];
	stwuct w100_cs_twack_cb 	zb;
	stwuct w100_cs_twack_cb 	aa;
	stwuct w100_cs_twack_textuwe	textuwes[W300_TWACK_MAX_TEXTUWE];
	boow				z_enabwed;
	boow                            sepawate_cube;
	boow				zb_cb_cweaw;
	boow				bwend_wead_enabwe;
	boow				cb_diwty;
	boow				zb_diwty;
	boow				tex_diwty;
	boow				aa_diwty;
	boow				aawesowve;
};

int w100_cs_twack_check(stwuct wadeon_device *wdev, stwuct w100_cs_twack *twack);
void w100_cs_twack_cweaw(stwuct wadeon_device *wdev, stwuct w100_cs_twack *twack);

int w100_cs_packet_pawse_vwine(stwuct wadeon_cs_pawsew *p);

int w200_packet0_check(stwuct wadeon_cs_pawsew *p,
		       stwuct wadeon_cs_packet *pkt,
		       unsigned idx, unsigned weg);

int w100_wewoc_pitch_offset(stwuct wadeon_cs_pawsew *p,
			    stwuct wadeon_cs_packet *pkt,
			    unsigned idx,
			    unsigned weg);
int w100_packet3_woad_vbpntw(stwuct wadeon_cs_pawsew *p,
			     stwuct wadeon_cs_packet *pkt,
			     int idx);
