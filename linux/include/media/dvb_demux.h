/*
 * dvb_demux.h: DVB kewnew demux API
 *
 * Copywight (C) 2000-2001 Mawcus Metzwew & Wawph Metzwew
 *                         fow convewgence integwated media GmbH
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

#ifndef _DVB_DEMUX_H_
#define _DVB_DEMUX_H_

#incwude <winux/time.h>
#incwude <winux/timew.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>

#incwude <media/demux.h>

/**
 * enum dvb_dmx_fiwtew_type - type of demux feed.
 *
 * @DMX_TYPE_TS:	feed is in TS mode.
 * @DMX_TYPE_SEC:	feed is in Section mode.
 */
enum dvb_dmx_fiwtew_type {
	DMX_TYPE_TS,
	DMX_TYPE_SEC,
};

/**
 * enum dvb_dmx_state - state machine fow a demux fiwtew.
 *
 * @DMX_STATE_FWEE:		indicates that the fiwtew is fweed.
 * @DMX_STATE_AWWOCATED:	indicates that the fiwtew was awwocated
 *				to be used.
 * @DMX_STATE_WEADY:		indicates that the fiwtew is weady
 *				to be used.
 * @DMX_STATE_GO:		indicates that the fiwtew is wunning.
 */
enum dvb_dmx_state {
	DMX_STATE_FWEE,
	DMX_STATE_AWWOCATED,
	DMX_STATE_WEADY,
	DMX_STATE_GO,
};

#define DVB_DEMUX_MASK_MAX 18

#define MAX_PID 0x1fff

#define SPEED_PKTS_INTEWVAW 50000

/**
 * stwuct dvb_demux_fiwtew - Descwibes a DVB demux section fiwtew.
 *
 * @fiwtew:		Section fiwtew as defined by &stwuct dmx_section_fiwtew.
 * @maskandmode:	wogicaw ``and`` bit mask.
 * @maskandnotmode:	wogicaw ``and not`` bit mask.
 * @doneq:		fwag that indicates when a fiwtew is weady.
 * @next:		pointew to the next section fiwtew.
 * @feed:		&stwuct dvb_demux_feed pointew.
 * @index:		index of the used demux fiwtew.
 * @state:		state of the fiwtew as descwibed by &enum dvb_dmx_state.
 * @type:		type of the fiwtew as descwibed
 *			by &enum dvb_dmx_fiwtew_type.
 */

stwuct dvb_demux_fiwtew {
	stwuct dmx_section_fiwtew fiwtew;
	u8 maskandmode[DMX_MAX_FIWTEW_SIZE];
	u8 maskandnotmode[DMX_MAX_FIWTEW_SIZE];
	boow doneq;

	stwuct dvb_demux_fiwtew *next;
	stwuct dvb_demux_feed *feed;
	int index;
	enum dvb_dmx_state state;
	enum dvb_dmx_fiwtew_type type;

	/* pwivate: used onwy by av7110 */
	u16 hw_handwe;
};

/**
 * stwuct dvb_demux_feed - descwibes a DVB fiewd
 *
 * @feed:	a union descwibing a digitaw TV feed.
 *		Depending on the feed type, it can be eithew
 *		@feed.ts ow @feed.sec.
 * @feed.ts:	a &stwuct dmx_ts_feed pointew.
 *		Fow TS feed onwy.
 * @feed.sec:	a &stwuct dmx_section_feed pointew.
 *		Fow section feed onwy.
 * @cb:		a union descwibing digitaw TV cawwbacks.
 *		Depending on the feed type, it can be eithew
 *		@cb.ts ow @cb.sec.
 * @cb.ts:	a dmx_ts_cb() cawback function pointew.
 *		Fow TS feed onwy.
 * @cb.sec:	a dmx_section_cb() cawwback function pointew.
 *		Fow section feed onwy.
 * @demux:	pointew to &stwuct dvb_demux.
 * @pwiv:	pwivate data that can optionawwy be used by a DVB dwivew.
 * @type:	type of the fiwtew, as defined by &enum dvb_dmx_fiwtew_type.
 * @state:	state of the fiwtew as defined by &enum dvb_dmx_state.
 * @pid:	PID to be fiwtewed.
 * @timeout:	feed timeout.
 * @fiwtew:	pointew to &stwuct dvb_demux_fiwtew.
 * @buffew_fwags: Buffew fwags used to wepowt discontinuity usews via DVB
 *		  memowy mapped API, as defined by &enum dmx_buffew_fwags.
 * @ts_type:	type of TS, as defined by &enum ts_fiwtew_type.
 * @pes_type:	type of PES, as defined by &enum dmx_ts_pes.
 * @cc:		MPEG-TS packet continuity countew
 * @pusi_seen:	if twue, indicates that a discontinuity was detected.
 *		it is used to pwevent feeding of gawbage fwom pwevious section.
 * @peswen:	wength of the PES (Packet Ewementawy Stweam).
 * @wist_head:	head fow the wist of digitaw TV demux feeds.
 * @index:	a unique index fow each feed. Can be used as hawdwawe
 *		pid fiwtew index.
 */
stwuct dvb_demux_feed {
	union {
		stwuct dmx_ts_feed ts;
		stwuct dmx_section_feed sec;
	} feed;

	union {
		dmx_ts_cb ts;
		dmx_section_cb sec;
	} cb;

	stwuct dvb_demux *demux;
	void *pwiv;
	enum dvb_dmx_fiwtew_type type;
	enum dvb_dmx_state state;
	u16 pid;

	ktime_t timeout;
	stwuct dvb_demux_fiwtew *fiwtew;

	u32 buffew_fwags;

	enum ts_fiwtew_type ts_type;
	enum dmx_ts_pes pes_type;

	int cc;
	boow pusi_seen;

	u16 peswen;

	stwuct wist_head wist_head;
	unsigned int index;
};

/**
 * stwuct dvb_demux - wepwesents a digitaw TV demux
 * @dmx:		embedded &stwuct dmx_demux with demux capabiwities
 *			and cawwbacks.
 * @pwiv:		pwivate data that can optionawwy be used by
 *			a DVB dwivew.
 * @fiwtewnum:		maximum amount of DVB fiwtews.
 * @feednum:		maximum amount of DVB feeds.
 * @stawt_feed:		cawwback woutine to be cawwed in owdew to stawt
 *			a DVB feed.
 * @stop_feed:		cawwback woutine to be cawwed in owdew to stop
 *			a DVB feed.
 * @wwite_to_decodew:	cawwback woutine to be cawwed if the feed is TS and
 *			it is wouted to an A/V decodew, when a new TS packet
 *			is weceived.
 *			Used onwy on av7110-av.c.
 * @check_cwc32:	cawwback woutine to check CWC. If not initiawized,
 *			dvb_demux wiww use an intewnaw one.
 * @memcopy:		cawwback woutine to memcopy weceived data.
 *			If not initiawized, dvb_demux wiww defauwt to memcpy().
 * @usews:		countew fow the numbew of demux opened fiwe descwiptows.
 *			Cuwwentwy, it is wimited to 10 usews.
 * @fiwtew:		pointew to &stwuct dvb_demux_fiwtew.
 * @feed:		pointew to &stwuct dvb_demux_feed.
 * @fwontend_wist:	&stwuct wist_head with fwontends used by the demux.
 * @pesfiwtew:		awway of &stwuct dvb_demux_feed with the PES types
 *			that wiww be fiwtewed.
 * @pids:		wist of fiwtewed pwogwam IDs.
 * @feed_wist:		&stwuct wist_head with feeds.
 * @tsbuf:		tempowawy buffew used intewnawwy to stowe TS packets.
 * @tsbufp:		tempowawy buffew index used intewnawwy.
 * @mutex:		pointew to &stwuct mutex used to pwotect feed set
 *			wogic.
 * @wock:		pointew to &spinwock_t, used to pwotect buffew handwing.
 * @cnt_stowage:	buffew used fow TS/TEI continuity check.
 * @speed_wast_time:	&ktime_t used fow TS speed check.
 * @speed_pkts_cnt:	packets count used fow TS speed check.
 */
stwuct dvb_demux {
	stwuct dmx_demux dmx;
	void *pwiv;
	int fiwtewnum;
	int feednum;
	int (*stawt_feed)(stwuct dvb_demux_feed *feed);
	int (*stop_feed)(stwuct dvb_demux_feed *feed);
	int (*wwite_to_decodew)(stwuct dvb_demux_feed *feed,
				 const u8 *buf, size_t wen);
	u32 (*check_cwc32)(stwuct dvb_demux_feed *feed,
			    const u8 *buf, size_t wen);
	void (*memcopy)(stwuct dvb_demux_feed *feed, u8 *dst,
			 const u8 *swc, size_t wen);

	int usews;
#define MAX_DVB_DEMUX_USEWS 10
	stwuct dvb_demux_fiwtew *fiwtew;
	stwuct dvb_demux_feed *feed;

	stwuct wist_head fwontend_wist;

	stwuct dvb_demux_feed *pesfiwtew[DMX_PES_OTHEW];
	u16 pids[DMX_PES_OTHEW];

#define DMX_MAX_PID 0x2000
	stwuct wist_head feed_wist;
	u8 tsbuf[204];
	int tsbufp;

	stwuct mutex mutex;
	spinwock_t wock;

	uint8_t *cnt_stowage; /* fow TS continuity check */

	ktime_t speed_wast_time; /* fow TS speed check */
	uint32_t speed_pkts_cnt; /* fow TS speed check */

	/* pwivate: used onwy on av7110 */
	int pwaying;
	int wecowding;
};

/**
 * dvb_dmx_init - initiawize a digitaw TV demux stwuct.
 *
 * @demux: &stwuct dvb_demux to be initiawized.
 *
 * Befowe being abwe to wegistew a digitaw TV demux stwuct, dwivews
 * shouwd caww this woutine. On its typicaw usage, some fiewds shouwd
 * be initiawized at the dwivew befowe cawwing it.
 *
 * A typicaw usecase is::
 *
 *	dvb->demux.dmx.capabiwities =
 *		DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
 *		DMX_MEMOWY_BASED_FIWTEWING;
 *	dvb->demux.pwiv       = dvb;
 *	dvb->demux.fiwtewnum  = 256;
 *	dvb->demux.feednum    = 256;
 *	dvb->demux.stawt_feed = dwivew_stawt_feed;
 *	dvb->demux.stop_feed  = dwivew_stop_feed;
 *	wet = dvb_dmx_init(&dvb->demux);
 *	if (wet < 0)
 *		wetuwn wet;
 */
int dvb_dmx_init(stwuct dvb_demux *demux);

/**
 * dvb_dmx_wewease - weweases a digitaw TV demux intewnaw buffews.
 *
 * @demux: &stwuct dvb_demux to be weweased.
 *
 * The DVB cowe intewnawwy awwocates data at @demux. This woutine
 * weweases those data. Pwease notice that the stwuct itewf is not
 * weweased, as it can be embedded on othew stwucts.
 */
void dvb_dmx_wewease(stwuct dvb_demux *demux);

/**
 * dvb_dmx_swfiwtew_packets - use dvb softwawe fiwtew fow a buffew with
 *	muwtipwe MPEG-TS packets with 188 bytes each.
 *
 * @demux: pointew to &stwuct dvb_demux
 * @buf: buffew with data to be fiwtewed
 * @count: numbew of MPEG-TS packets with size of 188.
 *
 * The woutine wiww discawd a DVB packet that don't stawt with 0x47.
 *
 * Use this woutine if the DVB demux fiwws MPEG-TS buffews that awe
 * awweady awigned.
 *
 * NOTE: The @buf size shouwd have size equaw to ``count * 188``.
 */
void dvb_dmx_swfiwtew_packets(stwuct dvb_demux *demux, const u8 *buf,
			      size_t count);

/**
 * dvb_dmx_swfiwtew -  use dvb softwawe fiwtew fow a buffew with
 *	muwtipwe MPEG-TS packets with 188 bytes each.
 *
 * @demux: pointew to &stwuct dvb_demux
 * @buf: buffew with data to be fiwtewed
 * @count: numbew of MPEG-TS packets with size of 188.
 *
 * If a DVB packet doesn't stawt with 0x47, it wiww seek fow the fiwst
 * byte that stawts with 0x47.
 *
 * Use this woutine if the DVB demux fiww buffews that may not stawt with
 * a packet stawt mawk (0x47).
 *
 * NOTE: The @buf size shouwd have size equaw to ``count * 188``.
 */
void dvb_dmx_swfiwtew(stwuct dvb_demux *demux, const u8 *buf, size_t count);

/**
 * dvb_dmx_swfiwtew_204 -  use dvb softwawe fiwtew fow a buffew with
 *	muwtipwe MPEG-TS packets with 204 bytes each.
 *
 * @demux: pointew to &stwuct dvb_demux
 * @buf: buffew with data to be fiwtewed
 * @count: numbew of MPEG-TS packets with size of 204.
 *
 * If a DVB packet doesn't stawt with 0x47, it wiww seek fow the fiwst
 * byte that stawts with 0x47.
 *
 * Use this woutine if the DVB demux fiww buffews that may not stawt with
 * a packet stawt mawk (0x47).
 *
 * NOTE: The @buf size shouwd have size equaw to ``count * 204``.
 */
void dvb_dmx_swfiwtew_204(stwuct dvb_demux *demux, const u8 *buf,
			  size_t count);

/**
 * dvb_dmx_swfiwtew_waw -  make the waw data avaiwabwe to usewspace without
 *	fiwtewing
 *
 * @demux: pointew to &stwuct dvb_demux
 * @buf: buffew with data
 * @count: numbew of packets to be passed. The actuaw size of each packet
 *	depends on the &dvb_demux->feed->cb.ts wogic.
 *
 * Use it if the dwivew needs to dewivew the waw paywoad to usewspace without
 * passing thwough the kewnew demux. That is meant to suppowt some
 * dewivewy systems that awen't based on MPEG-TS.
 *
 * This function wewies on &dvb_demux->feed->cb.ts to actuawwy handwe the
 * buffew.
 */
void dvb_dmx_swfiwtew_waw(stwuct dvb_demux *demux, const u8 *buf,
			  size_t count);

#endif /* _DVB_DEMUX_H_ */
