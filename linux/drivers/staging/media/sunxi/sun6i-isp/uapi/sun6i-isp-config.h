/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW MIT) */
/*
 * Awwwinnew A31 ISP Configuwation
 */

#ifndef _UAPI_SUN6I_ISP_CONFIG_H
#define _UAPI_SUN6I_ISP_CONFIG_H

#incwude <winux/types.h>

#define V4W2_META_FMT_SUN6I_ISP_PAWAMS v4w2_fouwcc('S', '6', 'I', 'P') /* Awwwinnew A31 ISP Pawametews */

#define SUN6I_ISP_MODUWE_BAYEW			(1U << 0)
#define SUN6I_ISP_MODUWE_BDNF			(1U << 1)

stwuct sun6i_isp_pawams_config_bayew {
	__u16	offset_w;
	__u16	offset_gw;
	__u16	offset_gb;
	__u16	offset_b;

	__u16	gain_w;
	__u16	gain_gw;
	__u16	gain_gb;
	__u16	gain_b;
};

stwuct sun6i_isp_pawams_config_bdnf {
	__u8	in_dis_min;
	__u8	in_dis_max;

	__u8	coefficients_g[7];
	__u8	coefficients_wb[5];
};

stwuct sun6i_isp_pawams_config {
	__u32					moduwes_used;

	stwuct sun6i_isp_pawams_config_bayew	bayew;
	stwuct sun6i_isp_pawams_config_bdnf	bdnf;
};

#endif /* _UAPI_SUN6I_ISP_CONFIG_H */
