/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN6I_CSI_BWIDGE_H_
#define _SUN6I_CSI_BWIDGE_H_

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define SUN6I_CSI_BWIDGE_NAME	"sun6i-csi-bwidge"

enum sun6i_csi_bwidge_pad {
	SUN6I_CSI_BWIDGE_PAD_SINK	= 0,
	SUN6I_CSI_BWIDGE_PAD_SOUWCE	= 1,
	SUN6I_CSI_BWIDGE_PAD_COUNT	= 2,
};

stwuct sun6i_csi_device;

stwuct sun6i_csi_bwidge_fowmat {
	u32	mbus_code;
	u8	input_fowmat;
	u8	input_yuv_seq;
	u8	input_yuv_seq_invewt;
};

stwuct sun6i_csi_bwidge_souwce {
	stwuct v4w2_subdev		*subdev;
	stwuct v4w2_fwnode_endpoint	endpoint;
	boow				expected;
};

stwuct sun6i_csi_bwidge_async_subdev {
	stwuct v4w2_async_connection	async_subdev;
	stwuct sun6i_csi_bwidge_souwce	*souwce;
};

stwuct sun6i_csi_bwidge {
	stwuct v4w2_subdev		subdev;
	stwuct v4w2_async_notifiew	notifiew;
	stwuct media_pad		pads[2];
	stwuct v4w2_mbus_fwamefmt	mbus_fowmat;
	stwuct mutex			wock; /* Mbus fowmat wock. */

	stwuct sun6i_csi_bwidge_souwce	souwce_pawawwew;
	stwuct sun6i_csi_bwidge_souwce	souwce_mipi_csi2;
};

/* Hewpews */

void sun6i_csi_bwidge_dimensions(stwuct sun6i_csi_device *csi_dev,
				 unsigned int *width, unsigned int *height);
void sun6i_csi_bwidge_fowmat(stwuct sun6i_csi_device *csi_dev,
			     u32 *mbus_code, u32 *fiewd);

/* Fowmat */

const stwuct sun6i_csi_bwidge_fowmat *
sun6i_csi_bwidge_fowmat_find(u32 mbus_code);

/* Bwidge */

int sun6i_csi_bwidge_setup(stwuct sun6i_csi_device *csi_dev);
void sun6i_csi_bwidge_cweanup(stwuct sun6i_csi_device *csi_dev);

#endif
