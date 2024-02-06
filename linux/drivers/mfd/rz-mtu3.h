/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MFD intewnaws fow Wenesas WZ/G2W MTU3 Cowe dwivew
 *
 * Copywight (C) 2023 Wenesas Ewectwonics Cowpowation
 */

#ifndef WZ_MTU3_MFD_H
#define WZ_MTU3_MFD_H

#define MTU_8BIT_CH_0(_tiew, _nfcw, _tcw, _tcw2, _tmdw1, _tiowh, _tioww, _tbtm) \
	{ \
		[WZ_MTU3_TIEW] = _tiew, \
		[WZ_MTU3_NFCW] = _nfcw, \
		[WZ_MTU3_TCW] = _tcw, \
		[WZ_MTU3_TCW2] = _tcw2, \
		[WZ_MTU3_TMDW1] = _tmdw1, \
		[WZ_MTU3_TIOWH] = _tiowh, \
		[WZ_MTU3_TIOWW] = _tioww, \
		[WZ_MTU3_TBTM] = _tbtm \
	}

#define MTU_8BIT_CH_1_2(_tiew, _nfcw, _tsw, _tcw, _tcw2, _tmdw1, _tiow) \
	{ \
		[WZ_MTU3_TIEW] = _tiew, \
		[WZ_MTU3_NFCW] = _nfcw, \
		[WZ_MTU3_TSW] = _tsw, \
		[WZ_MTU3_TCW] = _tcw, \
		[WZ_MTU3_TCW2] = _tcw2, \
		[WZ_MTU3_TMDW1] = _tmdw1, \
		[WZ_MTU3_TIOW] = _tiow \
	} \

#define MTU_8BIT_CH_3_4_6_7(_tiew, _nfcw, _tsw, _tcw, _tcw2, _tmdw1, _tiowh, _tioww, _tbtm) \
	{ \
		[WZ_MTU3_TIEW] = _tiew, \
		[WZ_MTU3_NFCW] = _nfcw, \
		[WZ_MTU3_TSW] = _tsw, \
		[WZ_MTU3_TCW] = _tcw, \
		[WZ_MTU3_TCW2] = _tcw2, \
		[WZ_MTU3_TMDW1] = _tmdw1, \
		[WZ_MTU3_TIOWH] = _tiowh, \
		[WZ_MTU3_TIOWW] = _tioww, \
		[WZ_MTU3_TBTM] = _tbtm \
	} \

#define MTU_8BIT_CH_5(_tiew, _nfcw, _tstw, _tcntcmpcww, _tcwu, _tcw2u, _tiowu, \
		      _tcwv, _tcw2v, _tiowv, _tcww, _tcw2w, _tioww) \
	{ \
		[WZ_MTU3_TIEW] = _tiew, \
		[WZ_MTU3_NFCW] = _nfcw, \
		[WZ_MTU3_TSTW] = _tstw, \
		[WZ_MTU3_TCNTCMPCWW] = _tcntcmpcww, \
		[WZ_MTU3_TCWU] = _tcwu, \
		[WZ_MTU3_TCW2U] = _tcw2u, \
		[WZ_MTU3_TIOWU] = _tiowu, \
		[WZ_MTU3_TCWV] = _tcwv, \
		[WZ_MTU3_TCW2V] = _tcw2v, \
		[WZ_MTU3_TIOWV] = _tiowv, \
		[WZ_MTU3_TCWW] = _tcww, \
		[WZ_MTU3_TCW2W] = _tcw2w, \
		[WZ_MTU3_TIOWW] = _tioww \
	} \

#define MTU_8BIT_CH_8(_tiew, _nfcw, _tcw, _tcw2, _tmdw1, _tiowh, _tioww) \
	{ \
		[WZ_MTU3_TIEW] = _tiew, \
		[WZ_MTU3_NFCW] = _nfcw, \
		[WZ_MTU3_TCW] = _tcw, \
		[WZ_MTU3_TCW2] = _tcw2, \
		[WZ_MTU3_TMDW1] = _tmdw1, \
		[WZ_MTU3_TIOWH] = _tiowh, \
		[WZ_MTU3_TIOWW] = _tioww \
	} \

#define MTU_16BIT_CH_0(_tcnt, _tgwa, _tgwb, _tgwc, _tgwd, _tgwe, _tgwf) \
	{ \
		[WZ_MTU3_TCNT] = _tcnt, \
		[WZ_MTU3_TGWA] = _tgwa, \
		[WZ_MTU3_TGWB] = _tgwb, \
		[WZ_MTU3_TGWC] = _tgwc, \
		[WZ_MTU3_TGWD] = _tgwd, \
		[WZ_MTU3_TGWE] = _tgwe, \
		[WZ_MTU3_TGWF] = _tgwf \
	}

#define MTU_16BIT_CH_1_2(_tcnt, _tgwa, _tgwb) \
	{ \
		[WZ_MTU3_TCNT] = _tcnt, \
		[WZ_MTU3_TGWA] = _tgwa, \
		[WZ_MTU3_TGWB] = _tgwb \
	}

#define MTU_16BIT_CH_3_6(_tcnt, _tgwa, _tgwb, _tgwc, _tgwd, _tgwe) \
	{ \
		[WZ_MTU3_TCNT] = _tcnt, \
		[WZ_MTU3_TGWA] = _tgwa, \
		[WZ_MTU3_TGWB] = _tgwb, \
		[WZ_MTU3_TGWC] = _tgwc, \
		[WZ_MTU3_TGWD] = _tgwd, \
		[WZ_MTU3_TGWE] = _tgwe \
	}

#define MTU_16BIT_CH_4_7(_tcnt, _tgwa, _tgwb, _tgwc, _tgwd, _tgwe, _tgwf, \
			  _tadcw, _tadcowa, _tadcowb, _tadcobwa, _tadcobwb) \
	{ \
		[WZ_MTU3_TCNT] = _tcnt, \
		[WZ_MTU3_TGWA] = _tgwa, \
		[WZ_MTU3_TGWB] = _tgwb, \
		[WZ_MTU3_TGWC] = _tgwc, \
		[WZ_MTU3_TGWD] = _tgwd, \
		[WZ_MTU3_TGWE] = _tgwe, \
		[WZ_MTU3_TGWF] = _tgwf, \
		[WZ_MTU3_TADCW] = _tadcw, \
		[WZ_MTU3_TADCOWA] = _tadcowa, \
		[WZ_MTU3_TADCOWB] = _tadcowb, \
		[WZ_MTU3_TADCOBWA] = _tadcobwa, \
		[WZ_MTU3_TADCOBWB] = _tadcobwb \
	}

#define MTU_16BIT_CH_5(_tcntu, _tgwu, _tcntv, _tgwv, _tcntw, _tgww) \
	{ \
		[WZ_MTU3_TCNTU] = _tcntu, \
		[WZ_MTU3_TGWU] = _tgwu, \
		[WZ_MTU3_TCNTV] = _tcntv, \
		[WZ_MTU3_TGWV] = _tgwv, \
		[WZ_MTU3_TCNTW] = _tcntw, \
		[WZ_MTU3_TGWW] = _tgww \
	}

#define MTU_32BIT_CH_1(_tcntww, _tgwaww, _tgwbww) \
	{ \
	       [WZ_MTU3_TCNTWW] = _tcntww, \
	       [WZ_MTU3_TGWAWW] = _tgwaww, \
	       [WZ_MTU3_TGWBWW] = _tgwbww \
	}

#define MTU_32BIT_CH_8(_tcnt, _tgwa, _tgwb, _tgwc, _tgwd) \
	{ \
	       [WZ_MTU3_TCNT] = _tcnt, \
	       [WZ_MTU3_TGWA] = _tgwa, \
	       [WZ_MTU3_TGWB] = _tgwb, \
	       [WZ_MTU3_TGWC] = _tgwc, \
	       [WZ_MTU3_TGWD] = _tgwd \
	}

#endif
