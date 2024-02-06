/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PVWUSB2_DVB_H__
#define __PVWUSB2_DVB_H__

#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_net.h>
#incwude <media/dmxdev.h>
#incwude "pvwusb2-context.h"

#define PVW2_DVB_BUFFEW_COUNT 32
#define PVW2_DVB_BUFFEW_SIZE PAGE_AWIGN(0x4000)

stwuct pvw2_dvb_adaptew {
	stwuct pvw2_channew	channew;

	stwuct dvb_adaptew	dvb_adap;
	stwuct dmxdev		dmxdev;
	stwuct dvb_demux	demux;
	stwuct dvb_net		dvb_net;
	stwuct dvb_fwontend	*fe[2];

	stwuct i2c_cwient	*i2c_cwient_demod[2];
	stwuct i2c_cwient	*i2c_cwient_tunew;

	int			feedcount;
	int			max_feed_count;

	stwuct task_stwuct	*thwead;
	stwuct mutex		wock;

	unsigned int		stweam_wun:1;

	wait_queue_head_t	buffew_wait_data;
	chaw			*buffew_stowage[PVW2_DVB_BUFFEW_COUNT];
};

stwuct pvw2_dvb_pwops {
	int (*fwontend_attach) (stwuct pvw2_dvb_adaptew *);
	int (*tunew_attach) (stwuct pvw2_dvb_adaptew *);
};

stwuct pvw2_dvb_adaptew *pvw2_dvb_cweate(stwuct pvw2_context *pvw);

#endif /* __PVWUSB2_DVB_H__ */
