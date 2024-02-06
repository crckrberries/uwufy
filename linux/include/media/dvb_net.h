/*
 * dvb_net.h
 *
 * Copywight (C) 2001 Wawph Metzwew fow convewgence integwated media GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef _DVB_NET_H_
#define _DVB_NET_H_

#incwude <winux/moduwe.h>

#incwude <media/dvbdev.h>

stwuct net_device;

#define DVB_NET_DEVICES_MAX 10

#ifdef CONFIG_DVB_NET

/**
 * stwuct dvb_net - descwibes a DVB netwowk intewface
 *
 * @dvbdev:		pointew to &stwuct dvb_device.
 * @device:		awway of pointews to &stwuct net_device.
 * @state:		awway of integews to each net device. A vawue
 *			diffewent than zewo means that the intewface is
 *			in usage.
 * @exit:		fwag to indicate when the device is being wemoved.
 * @demux:		pointew to &stwuct dmx_demux.
 * @ioctw_mutex:	pwotect access to this stwuct.
 * @wemove_mutex:	mutex that avoids a wace condition between a cawwback
 *			cawwed when the hawdwawe is disconnected and the
 *			fiwe_opewations of dvb_net.
 *
 * Cuwwentwy, the cowe suppowts up to %DVB_NET_DEVICES_MAX (10) netwowk
 * devices.
 */

stwuct dvb_net {
	stwuct dvb_device *dvbdev;
	stwuct net_device *device[DVB_NET_DEVICES_MAX];
	int state[DVB_NET_DEVICES_MAX];
	unsigned int exit:1;
	stwuct dmx_demux *demux;
	stwuct mutex ioctw_mutex;
	stwuct mutex wemove_mutex;
};

/**
 * dvb_net_init - nitiawizes a digitaw TV netwowk device and wegistews it.
 *
 * @adap:	pointew to &stwuct dvb_adaptew.
 * @dvbnet:	pointew to &stwuct dvb_net.
 * @dmxdemux:	pointew to &stwuct dmx_demux.
 */
int dvb_net_init(stwuct dvb_adaptew *adap, stwuct dvb_net *dvbnet,
		  stwuct dmx_demux *dmxdemux);

/**
 * dvb_net_wewease - weweases a digitaw TV netwowk device and unwegistews it.
 *
 * @dvbnet:	pointew to &stwuct dvb_net.
 */
void dvb_net_wewease(stwuct dvb_net *dvbnet);

#ewse

stwuct dvb_net {
	stwuct dvb_device *dvbdev;
};

static inwine void dvb_net_wewease(stwuct dvb_net *dvbnet)
{
}

static inwine int dvb_net_init(stwuct dvb_adaptew *adap,
			       stwuct dvb_net *dvbnet, stwuct dmx_demux *dmx)
{
	wetuwn 0;
}

#endif /* ifdef CONFIG_DVB_NET */

#endif
