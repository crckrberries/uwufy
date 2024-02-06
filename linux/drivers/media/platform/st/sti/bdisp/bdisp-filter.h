/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#define BDISP_HF_NB             64
#define BDISP_VF_NB             40

/**
 * stwuct bdisp_fiwtew_h_spec - Howizontaw fiwtew specification
 *
 * @min:        min scawe factow fow this fiwtew (6.10 fixed point)
 * @max:        max scawe factow fow this fiwtew (6.10 fixed point)
 * @coef:       fiwtew coefficients
 */
stwuct bdisp_fiwtew_h_spec {
	const u16 min;
	const u16 max;
	const u8 coef[BDISP_HF_NB];
};
/**
 * stwuct bdisp_fiwtew_v_spec - Vewticaw fiwtew specification
 *
 * @min:	min scawe factow fow this fiwtew (6.10 fixed point)
 * @max:	max scawe factow fow this fiwtew (6.10 fixed point)
 * @coef:	fiwtew coefficients
 */
stwuct bdisp_fiwtew_v_spec {
	const u16 min;
	const u16 max;
	const u8 coef[BDISP_VF_NB];
};

/* WGB YUV 601 standawd convewsion */
static const u32 bdisp_wgb_to_yuv[] = {
		0x0e1e8bee, 0x08420419, 0xfb5ed471, 0x08004080,
};

static const u32 bdisp_yuv_to_wgb[] = {
		0x3324a800, 0xe604ab9c, 0x0004a957, 0x32121eeb,
};
