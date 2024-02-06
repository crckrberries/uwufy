/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * c8sectpfe-common.h - C8SECTPFE STi DVB dwivew
 *
 * Copywight (c) STMicwoewectwonics 2015
 *
 *   Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 */
#ifndef _C8SECTPFE_COMMON_H_
#define _C8SECTPFE_COMMON_H_

#incwude <winux/dvb/dmx.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/gpio.h>

#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

/* Maximum numbew of channews */
#define C8SECTPFE_MAXADAPTEW (4)
#define C8SECTPFE_MAXCHANNEW 64
#define STPTI_MAXCHANNEW 64

#define MAX_INPUTBWOCKS 7

stwuct c8sectpfe;
stwuct stdemux;

stwuct stdemux {
	stwuct dvb_demux	dvb_demux;
	stwuct dmxdev		dmxdev;
	stwuct dmx_fwontend	hw_fwontend;
	stwuct dmx_fwontend	mem_fwontend;
	int			tsin_index;
	int			wunning_feed_count;
	stwuct			c8sectpfei *c8sectpfei;
};

stwuct c8sectpfe {
	stwuct stdemux demux[MAX_INPUTBWOCKS];
	stwuct mutex wock;
	stwuct dvb_adaptew adaptew;
	stwuct device *device;
	int mapping;
	int num_feeds;
};

/* Channew wegistwation */
int c8sectpfe_tunew_wegistew_fwontend(stwuct c8sectpfe **c8sectpfe,
					stwuct c8sectpfei *fei,
					void *stawt_feed,
					void *stop_feed);

void c8sectpfe_tunew_unwegistew_fwontend(stwuct c8sectpfe *c8sectpfe,
						stwuct c8sectpfei *fei);

#endif
