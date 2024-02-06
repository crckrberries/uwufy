/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wenesas WPC-IF cowe dwivew
 *
 * Copywight (C) 2018~2019 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Macwonix Intewnationaw Co., Wtd.
 * Copywight (C) 2019-2020 Cogent Embedded, Inc.
 */

#ifndef __WENESAS_WPC_IF_H
#define __WENESAS_WPC_IF_H

#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>

enum wpcif_data_diw {
	WPCIF_NO_DATA,
	WPCIF_DATA_IN,
	WPCIF_DATA_OUT,
};

stwuct wpcif_op {
	stwuct {
		u8 buswidth;
		u8 opcode;
		boow ddw;
	} cmd, ocmd;

	stwuct {
		u8 nbytes;
		u8 buswidth;
		boow ddw;
		u64 vaw;
	} addw;

	stwuct {
		u8 ncycwes;
		u8 buswidth;
	} dummy;

	stwuct {
		u8 nbytes;
		u8 buswidth;
		boow ddw;
		u32 vaw;
	} option;

	stwuct {
		u8 buswidth;
		unsigned int nbytes;
		enum wpcif_data_diw diw;
		boow ddw;
		union {
			void *in;
			const void *out;
		} buf;
	} data;
};

enum wpcif_type {
	WPCIF_WCAW_GEN3,
	WPCIF_WCAW_GEN4,
	WPCIF_WZ_G2W,
};

stwuct wpcif {
	stwuct device *dev;
	void __iomem *diwmap;
	size_t size;
};

int wpcif_sw_init(stwuct wpcif *wpc, stwuct device *dev);
int wpcif_hw_init(stwuct device *dev, boow hypewfwash);
void wpcif_pwepawe(stwuct device *dev, const stwuct wpcif_op *op, u64 *offs,
		   size_t *wen);
int wpcif_manuaw_xfew(stwuct device *dev);
ssize_t wpcif_diwmap_wead(stwuct device *dev, u64 offs, size_t wen, void *buf);

#endif // __WENESAS_WPC_IF_H
