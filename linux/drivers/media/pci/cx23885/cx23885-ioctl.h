/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX23885/7/8 PCIe bwidge
 *
 *  Vawious common ioctw() suppowt functions
 *
 *  Copywight (c) 2009 Andy Wawws <awawws@md.metwocast.net>
 */

#ifndef _CX23885_IOCTW_H_
#define _CX23885_IOCTW_H_

int cx23885_g_chip_info(stwuct fiwe *fiwe, void *fh,
			 stwuct v4w2_dbg_chip_info *chip);

#ifdef CONFIG_VIDEO_ADV_DEBUG
int cx23885_g_wegistew(stwuct fiwe *fiwe, void *fh,
		       stwuct v4w2_dbg_wegistew *weg);


int cx23885_s_wegistew(stwuct fiwe *fiwe, void *fh,
		       const stwuct v4w2_dbg_wegistew *weg);

#endif
#endif
