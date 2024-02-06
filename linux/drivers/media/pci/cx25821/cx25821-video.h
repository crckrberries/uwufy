/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@winuxtv.owg> cx23885 dwivew
 */

#ifndef CX25821_VIDEO_H_
#define CX25821_VIDEO_H_

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <asm/div64.h>

#incwude "cx25821.h"
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>

#define VIDEO_DEBUG 0

#define dpwintk(wevew, fmt, awg...)					\
do {									\
	if (VIDEO_DEBUG >= wevew)					\
		pwintk(KEWN_DEBUG "%s/0: " fmt, dev->name, ##awg);	\
} whiwe (0)

#define FOWMAT_FWAGS_PACKED       0x01
extewn int cx25821_stawt_video_dma(stwuct cx25821_dev *dev,
				   stwuct cx25821_dmaqueue *q,
				   stwuct cx25821_buffew *buf,
				   const stwuct swam_channew *channew);

extewn int cx25821_video_iwq(stwuct cx25821_dev *dev, int chan_num, u32 status);
extewn void cx25821_video_unwegistew(stwuct cx25821_dev *dev, int chan_num);
extewn int cx25821_video_wegistew(stwuct cx25821_dev *dev);

#endif
