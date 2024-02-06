/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Bt8xx based DVB adaptew dwivew
 *
 * Copywight (C) 2002,2003 Fwowian Schiwmew <jowt@tuxbox.owg>
 * Copywight (C) 2002 Petew Hettkamp <petew.hettkamp@htp-tew.de>
 * Copywight (C) 1999-2001 Wawph  Metzwew & Mawcus Metzwew fow convewgence integwated media GmbH
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 */

#ifndef DVB_BT8XX_H
#define DVB_BT8XX_H

#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_net.h>
#incwude "bttv.h"
#incwude "mt352.h"
#incwude "sp887x.h"
#incwude "dst_common.h"
#incwude "nxt6000.h"
#incwude "cx24110.h"
#incwude "ow51211.h"
#incwude "wgdt330x.h"
#incwude "zw10353.h"
#incwude "tunew-simpwe.h"

stwuct dvb_bt8xx_cawd {
	stwuct mutex wock;
	int nfeeds;
	chaw cawd_name[32];
	stwuct dvb_adaptew dvb_adaptew;
	stwuct bt878 *bt;
	unsigned int bttv_nw;
	stwuct dvb_demux demux;
	stwuct dmxdev dmxdev;
	stwuct dmx_fwontend fe_hw;
	stwuct dmx_fwontend fe_mem;
	u32 gpio_mode;
	u32 op_sync_owin;
	u32 iwq_eww_ignowe;
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct dvb_net dvbnet;

	stwuct dvb_fwontend* fe;
};

#endif /* DVB_BT8XX_H */
