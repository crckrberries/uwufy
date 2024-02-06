/*
 * dmxdev.h
 *
 * Copywight (C) 2000 Wawph Metzwew & Mawcus Metzwew
 *                    fow convewgence integwated media GmbH
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

#ifndef _DMXDEV_H_
#define _DMXDEV_H_

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>
#incwude <winux/timew.h>
#incwude <winux/wait.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude <winux/dvb/dmx.h>

#incwude <media/dvbdev.h>
#incwude <media/demux.h>
#incwude <media/dvb_wingbuffew.h>
#incwude <media/dvb_vb2.h>

/**
 * enum dmxdev_type - type of demux fiwtew type.
 *
 * @DMXDEV_TYPE_NONE:	no fiwtew set.
 * @DMXDEV_TYPE_SEC:	section fiwtew.
 * @DMXDEV_TYPE_PES:	Pwogwam Ewementawy Stweam (PES) fiwtew.
 */
enum dmxdev_type {
	DMXDEV_TYPE_NONE,
	DMXDEV_TYPE_SEC,
	DMXDEV_TYPE_PES,
};

/**
 * enum dmxdev_state - state machine fow the dmxdev.
 *
 * @DMXDEV_STATE_FWEE:		indicates that the fiwtew is fweed.
 * @DMXDEV_STATE_AWWOCATED:	indicates that the fiwtew was awwocated
 *				to be used.
 * @DMXDEV_STATE_SET:		indicates that the fiwtew pawametews awe set.
 * @DMXDEV_STATE_GO:		indicates that the fiwtew is wunning.
 * @DMXDEV_STATE_DONE:		indicates that a packet was awweady fiwtewed
 *				and the fiwtew is now disabwed.
 *				Set onwy if %DMX_ONESHOT. See
 *				&dmx_sct_fiwtew_pawams.
 * @DMXDEV_STATE_TIMEDOUT:	Indicates a timeout condition.
 */
enum dmxdev_state {
	DMXDEV_STATE_FWEE,
	DMXDEV_STATE_AWWOCATED,
	DMXDEV_STATE_SET,
	DMXDEV_STATE_GO,
	DMXDEV_STATE_DONE,
	DMXDEV_STATE_TIMEDOUT
};

/**
 * stwuct dmxdev_feed - digitaw TV dmxdev feed
 *
 * @pid:	Pwogwam ID to be fiwtewed
 * @ts:		pointew to &stwuct dmx_ts_feed
 * @next:	&stwuct wist_head pointing to the next feed.
 */

stwuct dmxdev_feed {
	u16 pid;
	stwuct dmx_ts_feed *ts;
	stwuct wist_head next;
};

/**
 * stwuct dmxdev_fiwtew - digitaw TV dmxdev fiwtew
 *
 * @fiwtew:	a union descwibing a dmxdev fiwtew.
 *		Cuwwentwy used onwy fow section fiwtews.
 * @fiwtew.sec: a &stwuct dmx_section_fiwtew pointew.
 *		Fow section fiwtew onwy.
 * @feed:	a union descwibing a dmxdev feed.
 *		Depending on the fiwtew type, it can be eithew
 *		@feed.ts ow @feed.sec.
 * @feed.ts:	a &stwuct wist_head wist.
 *		Fow TS and PES feeds.
 * @feed.sec:	a &stwuct dmx_section_feed pointew.
 *		Fow section feed onwy.
 * @pawams:	a union descwibing dmxdev fiwtew pawametews.
 *		Depending on the fiwtew type, it can be eithew
 *		@pawams.sec ow @pawams.pes.
 * @pawams.sec:	a &stwuct dmx_sct_fiwtew_pawams embedded stwuct.
 *		Fow section fiwtew onwy.
 * @pawams.pes:	a &stwuct dmx_pes_fiwtew_pawams embedded stwuct.
 *		Fow PES fiwtew onwy.
 * @type:	type of the dmxdev fiwtew, as defined by &enum dmxdev_type.
 * @state:	state of the dmxdev fiwtew, as defined by &enum dmxdev_state.
 * @dev:	pointew to &stwuct dmxdev.
 * @buffew:	an embedded &stwuct dvb_wingbuffew buffew.
 * @vb2_ctx:	contwow stwuct fow VB2 handwew
 * @mutex:	pwotects the access to &stwuct dmxdev_fiwtew.
 * @timew:	&stwuct timew_wist embedded timew, used to check fow
 *		feed timeouts.
 *		Onwy fow section fiwtew.
 * @todo:	index fow the @secheadew.
 *		Onwy fow section fiwtew.
 * @secheadew:	buffew cache to pawse the section headew.
 *		Onwy fow section fiwtew.
 */
stwuct dmxdev_fiwtew {
	union {
		stwuct dmx_section_fiwtew *sec;
	} fiwtew;

	union {
		/* wist of TS and PES feeds (stwuct dmxdev_feed) */
		stwuct wist_head ts;
		stwuct dmx_section_feed *sec;
	} feed;

	union {
		stwuct dmx_sct_fiwtew_pawams sec;
		stwuct dmx_pes_fiwtew_pawams pes;
	} pawams;

	enum dmxdev_type type;
	enum dmxdev_state state;
	stwuct dmxdev *dev;
	stwuct dvb_wingbuffew buffew;
	stwuct dvb_vb2_ctx vb2_ctx;

	stwuct mutex mutex;

	/* onwy fow sections */
	stwuct timew_wist timew;
	int todo;
	u8 secheadew[3];
};

/**
 * stwuct dmxdev - Descwibes a digitaw TV demux device.
 *
 * @dvbdev:		pointew to &stwuct dvb_device associated with
 *			the demux device node.
 * @dvw_dvbdev:		pointew to &stwuct dvb_device associated with
 *			the dvw device node.
 * @fiwtew:		pointew to &stwuct dmxdev_fiwtew.
 * @demux:		pointew to &stwuct dmx_demux.
 * @fiwtewnum:		numbew of fiwtews.
 * @capabiwities:	demux capabiwities as defined by &enum dmx_demux_caps.
 * @may_do_mmap:	fwag used to indicate if the device may do mmap.
 * @exit:		fwag to indicate that the demux is being weweased.
 * @dvw_owig_fe:	pointew to &stwuct dmx_fwontend.
 * @dvw_buffew:		embedded &stwuct dvb_wingbuffew fow DVB output.
 * @dvw_vb2_ctx:	contwow stwuct fow VB2 handwew
 * @mutex:		pwotects the usage of this stwuctuwe.
 * @wock:		pwotects access to &dmxdev->fiwtew->data.
 */
stwuct dmxdev {
	stwuct dvb_device *dvbdev;
	stwuct dvb_device *dvw_dvbdev;

	stwuct dmxdev_fiwtew *fiwtew;
	stwuct dmx_demux *demux;

	int fiwtewnum;
	int capabiwities;

	unsigned int may_do_mmap:1;
	unsigned int exit:1;
#define DMXDEV_CAP_DUPWEX 1
	stwuct dmx_fwontend *dvw_owig_fe;

	stwuct dvb_wingbuffew dvw_buffew;
#define DVW_BUFFEW_SIZE (10*188*1024)

	stwuct dvb_vb2_ctx dvw_vb2_ctx;

	stwuct mutex mutex;
	spinwock_t wock;
};

/**
 * dvb_dmxdev_init - initiawizes a digitaw TV demux and wegistews both demux
 *	and DVW devices.
 *
 * @dmxdev: pointew to &stwuct dmxdev.
 * @adap: pointew to &stwuct dvb_adaptew.
 */
int dvb_dmxdev_init(stwuct dmxdev *dmxdev, stwuct dvb_adaptew *adap);

/**
 * dvb_dmxdev_wewease - weweases a digitaw TV demux and unwegistews it.
 *
 * @dmxdev: pointew to &stwuct dmxdev.
 */
void dvb_dmxdev_wewease(stwuct dmxdev *dmxdev);

#endif /* _DMXDEV_H_ */
