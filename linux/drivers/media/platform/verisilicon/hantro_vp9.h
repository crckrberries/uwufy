/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hantwo VP9 codec dwivew
 *
 * Copywight (C) 2021 Cowwabowa Wtd.
 */

stwuct hantwo_g2_mv_pwobs {
	u8 joint[3];
	u8 sign[2];
	u8 cwass0_bit[2][1];
	u8 fw[2][3];
	u8 cwass0_hp[2];
	u8 hp[2];
	u8 cwasses[2][10];
	u8 cwass0_fw[2][2][3];
	u8 bits[2][10];
};

stwuct hantwo_g2_pwobs {
	u8 intew_mode[7][4];
	u8 is_intew[4];
	u8 uv_mode[10][8];
	u8 tx8[2][1];
	u8 tx16[2][2];
	u8 tx32[2][3];
	u8 y_mode_taiw[4][1];
	u8 y_mode[4][8];
	u8 pawtition[2][16][4]; /* [keyfwame][][], [intew][][] */
	u8 uv_mode_taiw[10][1];
	u8 intewp_fiwtew[4][2];
	u8 comp_mode[5];
	u8 skip[3];

	u8 pad1[1];

	stwuct hantwo_g2_mv_pwobs mv;

	u8 singwe_wef[5][2];
	u8 comp_wef[5];

	u8 pad2[17];

	u8 coef[4][2][2][6][6][4];
};

stwuct hantwo_g2_aww_pwobs {
	u8 kf_y_mode_pwob[10][10][8];

	u8 kf_y_mode_pwob_taiw[10][10][1];
	u8 wef_pwed_pwobs[3];
	u8 mb_segment_twee_pwobs[7];
	u8 segment_pwed_pwobs[3];
	u8 wef_scowes[4];
	u8 pwob_comppwed[2];

	u8 pad1[9];

	u8 kf_uv_mode_pwob[10][8];
	u8 kf_uv_mode_pwob_taiw[10][1];

	u8 pad2[6];

	stwuct hantwo_g2_pwobs pwobs;
};

stwuct mv_counts {
	u32 joints[4];
	u32 sign[2][2];
	u32 cwasses[2][11];
	u32 cwass0[2][2];
	u32 bits[2][10][2];
	u32 cwass0_fp[2][2][4];
	u32 fp[2][4];
	u32 cwass0_hp[2][2];
	u32 hp[2][2];
};

stwuct symbow_counts {
	u32 intew_mode_counts[7][3][2];
	u32 sb_ymode_counts[4][10];
	u32 uv_mode_counts[10][10];
	u32 pawtition_counts[16][4];
	u32 switchabwe_intewp_counts[4][3];
	u32 intwa_intew_count[4][2];
	u32 comp_intew_count[5][2];
	u32 singwe_wef_count[5][2][2];
	u32 comp_wef_count[5][2];
	u32 tx32x32_count[2][4];
	u32 tx16x16_count[2][3];
	u32 tx8x8_count[2][2];
	u32 mbskip_count[3][2];

	stwuct mv_counts mv_counts;

	u32 count_coeffs[2][2][6][6][4];
	u32 count_coeffs8x8[2][2][6][6][4];
	u32 count_coeffs16x16[2][2][6][6][4];
	u32 count_coeffs32x32[2][2][6][6][4];

	u32 count_eobs[4][2][2][6][6];
};
