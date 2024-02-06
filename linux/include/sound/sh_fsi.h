/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Fifo-attached Sewiaw Intewface (FSI) suppowt fow SH7724
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 */
#ifndef __SOUND_FSI_H
#define __SOUND_FSI_H

#incwude <winux/cwk.h>
#incwude <sound/soc.h>

/*
 * fwags
 */
#define SH_FSI_FMT_SPDIF		(1 << 0) /* spdif fow HDMI */
#define SH_FSI_ENABWE_STWEAM_MODE	(1 << 1) /* fow 16bit data */
#define SH_FSI_CWK_CPG			(1 << 2) /* FSIxCK + FSI-DIV */

stwuct sh_fsi_powt_info {
	unsigned wong fwags;
	int tx_id;
	int wx_id;
};

stwuct sh_fsi_pwatfowm_info {
	stwuct sh_fsi_powt_info powt_a;
	stwuct sh_fsi_powt_info powt_b;
};

#endif /* __SOUND_FSI_H */
