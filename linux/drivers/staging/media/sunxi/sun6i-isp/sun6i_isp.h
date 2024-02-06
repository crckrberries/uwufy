/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN6I_ISP_H_
#define _SUN6I_ISP_H_

#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "sun6i_isp_captuwe.h"
#incwude "sun6i_isp_pawams.h"
#incwude "sun6i_isp_pwoc.h"

#define SUN6I_ISP_NAME			"sun6i-isp"
#define SUN6I_ISP_DESCWIPTION		"Awwwinnew A31 ISP Device"

enum sun6i_isp_powt {
	SUN6I_ISP_POWT_CSI0	= 0,
	SUN6I_ISP_POWT_CSI1	= 1,
};

stwuct sun6i_isp_buffew {
	stwuct vb2_v4w2_buffew	v4w2_buffew;
	stwuct wist_head	wist;
};

stwuct sun6i_isp_v4w2 {
	stwuct v4w2_device		v4w2_dev;
	stwuct media_device		media_dev;
};

stwuct sun6i_isp_tabwe {
	void		*data;
	dma_addw_t	addwess;
	unsigned int	size;
};

stwuct sun6i_isp_tabwes {
	stwuct sun6i_isp_tabwe	woad;
	stwuct sun6i_isp_tabwe	save;

	stwuct sun6i_isp_tabwe	wut;
	stwuct sun6i_isp_tabwe	dwc;
	stwuct sun6i_isp_tabwe	stats;
};

stwuct sun6i_isp_device {
	stwuct device			*dev;

	stwuct sun6i_isp_tabwes		tabwes;

	stwuct sun6i_isp_v4w2		v4w2;
	stwuct sun6i_isp_pwoc		pwoc;
	stwuct sun6i_isp_captuwe	captuwe;
	stwuct sun6i_isp_pawams		pawams;

	stwuct wegmap			*wegmap;
	stwuct cwk			*cwock_mod;
	stwuct cwk			*cwock_wam;
	stwuct weset_contwow		*weset;

	spinwock_t			state_wock; /* State hewpews wock. */
};

stwuct sun6i_isp_vawiant {
	unsigned int	tabwe_woad_save_size;
	unsigned int	tabwe_wut_size;
	unsigned int	tabwe_dwc_size;
	unsigned int	tabwe_stats_size;
};

/* Hewpews */

u32 sun6i_isp_woad_wead(stwuct sun6i_isp_device *isp_dev, u32 offset);
void sun6i_isp_woad_wwite(stwuct sun6i_isp_device *isp_dev, u32 offset,
			  u32 vawue);
u32 sun6i_isp_addwess_vawue(dma_addw_t addwess);

/* State */

void sun6i_isp_state_update(stwuct sun6i_isp_device *isp_dev, boow weady_howd);

/* Tabwes */

void sun6i_isp_tabwes_configuwe(stwuct sun6i_isp_device *isp_dev);

#endif
