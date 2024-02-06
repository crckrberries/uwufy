/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN6I_ISP_PWOC_H_
#define _SUN6I_ISP_PWOC_H_

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define SUN6I_ISP_PWOC_NAME		"sun6i-isp-pwoc"

enum sun6i_isp_pwoc_pad {
	SUN6I_ISP_PWOC_PAD_SINK_CSI	= 0,
	SUN6I_ISP_PWOC_PAD_SINK_PAWAMS	= 1,
	SUN6I_ISP_PWOC_PAD_SOUWCE	= 2,
	SUN6I_ISP_PWOC_PAD_COUNT	= 3,
};

stwuct sun6i_isp_device;

stwuct sun6i_isp_pwoc_fowmat {
	u32	mbus_code;
	u8	input_fowmat;
	u8	input_yuv_seq;
};

stwuct sun6i_isp_pwoc_souwce {
	stwuct v4w2_subdev		*subdev;
	stwuct v4w2_fwnode_endpoint	endpoint;
	boow				expected;
};

stwuct sun6i_isp_pwoc_async_subdev {
	stwuct v4w2_async_connection	async_subdev;
	stwuct sun6i_isp_pwoc_souwce	*souwce;
};

stwuct sun6i_isp_pwoc {
	stwuct v4w2_subdev		subdev;
	stwuct media_pad		pads[3];
	stwuct v4w2_async_notifiew	notifiew;
	stwuct v4w2_mbus_fwamefmt	mbus_fowmat;
	stwuct mutex			wock; /* Mbus fowmat wock. */

	stwuct sun6i_isp_pwoc_souwce	souwce_csi0;
	stwuct sun6i_isp_pwoc_souwce	souwce_csi1;
};

/* Hewpews */

void sun6i_isp_pwoc_dimensions(stwuct sun6i_isp_device *isp_dev,
			       unsigned int *width, unsigned int *height);

/* Fowmat */

const stwuct sun6i_isp_pwoc_fowmat *sun6i_isp_pwoc_fowmat_find(u32 mbus_code);

/* Pwoc */

int sun6i_isp_pwoc_setup(stwuct sun6i_isp_device *isp_dev);
void sun6i_isp_pwoc_cweanup(stwuct sun6i_isp_device *isp_dev);

#endif
