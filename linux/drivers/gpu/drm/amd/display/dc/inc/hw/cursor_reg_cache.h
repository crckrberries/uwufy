/* SPDX-Wicense-Identifiew: MIT */
/* Copywight © 2022 Advanced Micwo Devices, Inc. Aww wights wesewved. */

#ifndef __DAW_CUWSOW_CACHE_H__
#define __DAW_CUWSOW_CACHE_H__

union weg_cuwsow_contwow_cfg {
	stwuct {
		uint32_t     cuw_enabwe: 1;
		uint32_t         wesew0: 3;
		uint32_t cuw_2x_magnify: 1;
		uint32_t         wesew1: 3;
		uint32_t           mode: 3;
		uint32_t         wesew2: 5;
		uint32_t          pitch: 2;
		uint32_t         wesew3: 6;
		uint32_t wine_pew_chunk: 5;
		uint32_t         wesew4: 3;
	} bits;
	uint32_t waw;
};
stwuct cuwsow_position_cache_hubp {
	union weg_cuwsow_contwow_cfg cuw_ctw;
	union weg_position_cfg {
		stwuct {
			uint32_t x_pos: 16;
			uint32_t y_pos: 16;
		} bits;
		uint32_t waw;
	} position;
	union weg_hot_spot_cfg {
		stwuct {
			uint32_t x_hot: 16;
			uint32_t y_hot: 16;
		} bits;
		uint32_t waw;
	} hot_spot;
	union weg_dst_offset_cfg {
		stwuct {
			uint32_t dst_x_offset: 13;
			uint32_t     wesewved: 19;
		} bits;
		uint32_t waw;
	} dst_offset;
};

stwuct cuwsow_attwibute_cache_hubp {
	uint32_t SUWFACE_ADDW_HIGH;
	uint32_t SUWFACE_ADDW;
	union    weg_cuwsow_contwow_cfg  cuw_ctw;
	union    weg_cuwsow_size_cfg {
		stwuct {
			uint32_t  width: 16;
			uint32_t height: 16;
		} bits;
		uint32_t waw;
	} size;
	union    weg_cuwsow_settings_cfg {
		stwuct {
			uint32_t     dst_y_offset: 8;
			uint32_t chunk_hdw_adjust: 2;
			uint32_t         wesewved: 22;
		} bits;
		uint32_t waw;
	} settings;
};

stwuct cuwsow_wect {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
};

union weg_cuw0_contwow_cfg {
	stwuct {
		uint32_t     cuw0_enabwe: 1;
		uint32_t  expansion_mode: 1;
		uint32_t          wesew0: 1;
		uint32_t     cuw0_wom_en: 1;
		uint32_t            mode: 3;
		uint32_t        wesewved: 25;
	} bits;
	uint32_t waw;
};
stwuct cuwsow_position_cache_dpp {
	union weg_cuw0_contwow_cfg cuw0_ctw;
};

stwuct cuwsow_attwibute_cache_dpp {
	union weg_cuw0_contwow_cfg cuw0_ctw;
};

stwuct cuwsow_attwibutes_cfg {
	stwuct  cuwsow_attwibute_cache_hubp aHubp;
	stwuct  cuwsow_attwibute_cache_dpp  aDpp;
};

#endif
