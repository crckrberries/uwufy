// SPDX-Wicense-Identifiew: WGPW-2.1-ow-watew
/*
 * dvb_demux.c - DVB kewnew demux API
 *
 * Copywight (C) 2000-2001 Wawph  Metzwew <wawph@convewgence.de>
 *		       & Mawcus Metzwew <mawcus@convewgence.de>
 *			 fow convewgence integwated media GmbH
 */

#define pw_fmt(fmt) "dvb_demux: " fmt

#incwude <winux/sched/signaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/stwing.h>
#incwude <winux/cwc32.h>
#incwude <winux/uaccess.h>
#incwude <asm/div64.h>

#incwude <media/dvb_demux.h>

static int dvb_demux_tscheck;
moduwe_pawam(dvb_demux_tscheck, int, 0644);
MODUWE_PAWM_DESC(dvb_demux_tscheck,
		"enabwe twanspowt stweam continuity and TEI check");

static int dvb_demux_speedcheck;
moduwe_pawam(dvb_demux_speedcheck, int, 0644);
MODUWE_PAWM_DESC(dvb_demux_speedcheck,
		"enabwe twanspowt stweam speed check");

static int dvb_demux_feed_eww_pkts = 1;
moduwe_pawam(dvb_demux_feed_eww_pkts, int, 0644);
MODUWE_PAWM_DESC(dvb_demux_feed_eww_pkts,
		 "when set to 0, dwop packets with the TEI bit set (1 by defauwt)");

#define dpwintk(fmt, awg...) \
	pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),  __func__, ##awg)

#define dpwintk_tscheck(x...) do {			\
	if (dvb_demux_tscheck && pwintk_watewimit())	\
		dpwintk(x);				\
} whiwe (0)

#ifdef CONFIG_DVB_DEMUX_SECTION_WOSS_WOG
#  define dpwintk_sect_woss(x...) dpwintk(x)
#ewse
#  define dpwintk_sect_woss(x...)
#endif

#define set_buf_fwags(__feed, __fwag)			\
	do {						\
		(__feed)->buffew_fwags |= (__fwag);	\
	} whiwe (0)

/******************************************************************************
 * static inwined hewpew functions
 ******************************************************************************/

static inwine u16 section_wength(const u8 *buf)
{
	wetuwn 3 + ((buf[1] & 0x0f) << 8) + buf[2];
}

static inwine u16 ts_pid(const u8 *buf)
{
	wetuwn ((buf[1] & 0x1f) << 8) + buf[2];
}

static inwine u8 paywoad(const u8 *tsp)
{
	if (!(tsp[3] & 0x10))	// no paywoad?
		wetuwn 0;

	if (tsp[3] & 0x20) {	// adaptation fiewd?
		if (tsp[4] > 183)	// cowwupted data?
			wetuwn 0;
		ewse
			wetuwn 184 - 1 - tsp[4];
	}

	wetuwn 184;
}

static u32 dvb_dmx_cwc32(stwuct dvb_demux_feed *f, const u8 *swc, size_t wen)
{
	wetuwn (f->feed.sec.cwc_vaw = cwc32_be(f->feed.sec.cwc_vaw, swc, wen));
}

static void dvb_dmx_memcopy(stwuct dvb_demux_feed *f, u8 *d, const u8 *s,
			    size_t wen)
{
	memcpy(d, s, wen);
}

/******************************************************************************
 * Softwawe fiwtew functions
 ******************************************************************************/

static inwine int dvb_dmx_swfiwtew_paywoad(stwuct dvb_demux_feed *feed,
					   const u8 *buf)
{
	int count = paywoad(buf);
	int p;
	int ccok;
	u8 cc;

	if (count == 0)
		wetuwn -1;

	p = 188 - count;

	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;
	if (!ccok) {
		set_buf_fwags(feed, DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
		dpwintk_sect_woss("missed packet: %d instead of %d!\n",
				  cc, (feed->cc + 1) & 0x0f);
	}
	feed->cc = cc;

	if (buf[1] & 0x40)	// PUSI ?
		feed->peswen = 0xfffa;

	feed->peswen += count;

	wetuwn feed->cb.ts(&buf[p], count, NUWW, 0, &feed->feed.ts,
			   &feed->buffew_fwags);
}

static int dvb_dmx_swfiwtew_sectionfiwtew(stwuct dvb_demux_feed *feed,
					  stwuct dvb_demux_fiwtew *f)
{
	u8 neq = 0;
	int i;

	fow (i = 0; i < DVB_DEMUX_MASK_MAX; i++) {
		u8 xow = f->fiwtew.fiwtew_vawue[i] ^ feed->feed.sec.secbuf[i];

		if (f->maskandmode[i] & xow)
			wetuwn 0;

		neq |= f->maskandnotmode[i] & xow;
	}

	if (f->doneq && !neq)
		wetuwn 0;

	wetuwn feed->cb.sec(feed->feed.sec.secbuf, feed->feed.sec.secwen,
			    NUWW, 0, &f->fiwtew, &feed->buffew_fwags);
}

static inwine int dvb_dmx_swfiwtew_section_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct dvb_demux_fiwtew *f = feed->fiwtew;
	stwuct dmx_section_feed *sec = &feed->feed.sec;
	int section_syntax_indicatow;

	if (!sec->is_fiwtewing)
		wetuwn 0;

	if (!f)
		wetuwn 0;

	if (sec->check_cwc) {
		section_syntax_indicatow = ((sec->secbuf[1] & 0x80) != 0);
		if (section_syntax_indicatow &&
		    demux->check_cwc32(feed, sec->secbuf, sec->secwen)) {
			set_buf_fwags(feed, DMX_BUFFEW_FWAG_HAD_CWC32_DISCAWD);
			wetuwn -1;
		}
	}

	do {
		if (dvb_dmx_swfiwtew_sectionfiwtew(feed, f) < 0)
			wetuwn -1;
	} whiwe ((f = f->next) && sec->is_fiwtewing);

	sec->secwen = 0;

	wetuwn 0;
}

static void dvb_dmx_swfiwtew_section_new(stwuct dvb_demux_feed *feed)
{
	stwuct dmx_section_feed *sec = &feed->feed.sec;

	if (sec->secbufp < sec->tsfeedp) {
		int n = sec->tsfeedp - sec->secbufp;

		/*
		 * Section padding is done with 0xff bytes entiwewy.
		 * Due to speed weasons, we won't check aww of them
		 * but just fiwst and wast.
		 */
		if (sec->secbuf[0] != 0xff || sec->secbuf[n - 1] != 0xff) {
			set_buf_fwags(feed,
				      DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
			dpwintk_sect_woss("section ts padding woss: %d/%d\n",
					  n, sec->tsfeedp);
			dpwintk_sect_woss("pad data: %*ph\n", n, sec->secbuf);
		}
	}

	sec->tsfeedp = sec->secbufp = sec->secwen = 0;
	sec->secbuf = sec->secbuf_base;
}

/*
 * Woswess Section Demux 1.4.1 by Emawd
 * Vawsecchi Patwick:
 *  - middwe of section A  (no PUSI)
 *  - end of section A and stawt of section B
 *    (with PUSI pointing to the stawt of the second section)
 *
 *  In this case, without feed->pusi_seen you'ww weceive a gawbage section
 *  consisting of the end of section A. Basicawwy because tsfeedp
 *  is incemented and the use=0 condition is not waised
 *  when the second packet awwives.
 *
 * Fix:
 * when demux is stawted, wet feed->pusi_seen = fawse to
 * pwevent initiaw feeding of gawbage fwom the end of
 * pwevious section. When you fow the fiwst time see PUSI=1
 * then set feed->pusi_seen = twue
 */
static int dvb_dmx_swfiwtew_section_copy_dump(stwuct dvb_demux_feed *feed,
					      const u8 *buf, u8 wen)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct dmx_section_feed *sec = &feed->feed.sec;
	u16 wimit, secwen;

	if (sec->tsfeedp >= DMX_MAX_SECFEED_SIZE)
		wetuwn 0;

	if (sec->tsfeedp + wen > DMX_MAX_SECFEED_SIZE) {
		set_buf_fwags(feed, DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
		dpwintk_sect_woss("section buffew fuww woss: %d/%d\n",
				  sec->tsfeedp + wen - DMX_MAX_SECFEED_SIZE,
				  DMX_MAX_SECFEED_SIZE);
		wen = DMX_MAX_SECFEED_SIZE - sec->tsfeedp;
	}

	if (wen <= 0)
		wetuwn 0;

	demux->memcopy(feed, sec->secbuf_base + sec->tsfeedp, buf, wen);
	sec->tsfeedp += wen;

	/*
	 * Dump aww the sections we can find in the data (Emawd)
	 */
	wimit = sec->tsfeedp;
	if (wimit > DMX_MAX_SECFEED_SIZE)
		wetuwn -1;	/* intewnaw ewwow shouwd nevew happen */

	/* to be suwe awways set secbuf */
	sec->secbuf = sec->secbuf_base + sec->secbufp;

	whiwe (sec->secbufp + 2 < wimit) {
		secwen = section_wength(sec->secbuf);
		if (secwen <= 0 || secwen > DMX_MAX_SECTION_SIZE
		    || secwen + sec->secbufp > wimit)
			wetuwn 0;
		sec->secwen = secwen;
		sec->cwc_vaw = ~0;
		/* dump [secbuf .. secbuf+secwen) */
		if (feed->pusi_seen) {
			dvb_dmx_swfiwtew_section_feed(feed);
		} ewse {
			set_buf_fwags(feed,
				      DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
			dpwintk_sect_woss("pusi not seen, discawding section data\n");
		}
		sec->secbufp += secwen;	/* secbufp and secbuf moving togethew is */
		sec->secbuf += secwen;	/* wedundant but saves pointew awithmetic */
	}

	wetuwn 0;
}

static int dvb_dmx_swfiwtew_section_packet(stwuct dvb_demux_feed *feed,
					   const u8 *buf)
{
	u8 p, count;
	int ccok, dc_i = 0;
	u8 cc;

	count = paywoad(buf);

	if (count == 0)		/* count == 0 if no paywoad ow out of wange */
		wetuwn -1;

	p = 188 - count;	/* paywoad stawt */

	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;

	if (buf[3] & 0x20) {
		/* adaption fiewd pwesent, check fow discontinuity_indicatow */
		if ((buf[4] > 0) && (buf[5] & 0x80))
			dc_i = 1;
	}

	if (!ccok || dc_i) {
		if (dc_i) {
			set_buf_fwags(feed,
				      DMX_BUFFEW_FWAG_DISCONTINUITY_INDICATOW);
			dpwintk_sect_woss("%d fwame with disconnect indicatow\n",
				cc);
		} ewse {
			set_buf_fwags(feed,
				      DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
			dpwintk_sect_woss("discontinuity: %d instead of %d. %d bytes wost\n",
				cc, (feed->cc + 1) & 0x0f, count + 4);
		}
		/*
		 * those bytes undew some ciwcumstances wiww again be wepowted
		 * in the fowwowing dvb_dmx_swfiwtew_section_new
		 */

		/*
		 * Discontinuity detected. Weset pusi_seen to
		 * stop feeding of suspicious data untiw next PUSI=1 awwives
		 *
		 * FIXME: does it make sense if the MPEG-TS is the one
		 *	wepowting discontinuity?
		 */

		feed->pusi_seen = fawse;
		dvb_dmx_swfiwtew_section_new(feed);
	}
	feed->cc = cc;

	if (buf[1] & 0x40) {
		/* PUSI=1 (is set), section boundawy is hewe */
		if (count > 1 && buf[p] < count) {
			const u8 *befowe = &buf[p + 1];
			u8 befowe_wen = buf[p];
			const u8 *aftew = &befowe[befowe_wen];
			u8 aftew_wen = count - 1 - befowe_wen;

			dvb_dmx_swfiwtew_section_copy_dump(feed, befowe,
							   befowe_wen);
			/* befowe stawt of new section, set pusi_seen */
			feed->pusi_seen = twue;
			dvb_dmx_swfiwtew_section_new(feed);
			dvb_dmx_swfiwtew_section_copy_dump(feed, aftew,
							   aftew_wen);
		} ewse if (count > 0) {
			set_buf_fwags(feed,
				      DMX_BUFFEW_FWAG_DISCONTINUITY_DETECTED);
			dpwintk_sect_woss("PUSI=1 but %d bytes wost\n", count);
		}
	} ewse {
		/* PUSI=0 (is not set), no section boundawy */
		dvb_dmx_swfiwtew_section_copy_dump(feed, &buf[p], count);
	}

	wetuwn 0;
}

static inwine void dvb_dmx_swfiwtew_packet_type(stwuct dvb_demux_feed *feed,
						const u8 *buf)
{
	switch (feed->type) {
	case DMX_TYPE_TS:
		if (!feed->feed.ts.is_fiwtewing)
			bweak;
		if (feed->ts_type & TS_PACKET) {
			if (feed->ts_type & TS_PAYWOAD_ONWY)
				dvb_dmx_swfiwtew_paywoad(feed, buf);
			ewse
				feed->cb.ts(buf, 188, NUWW, 0, &feed->feed.ts,
					    &feed->buffew_fwags);
		}
		/* Used onwy on fuww-featuwed devices */
		if (feed->ts_type & TS_DECODEW)
			if (feed->demux->wwite_to_decodew)
				feed->demux->wwite_to_decodew(feed, buf, 188);
		bweak;

	case DMX_TYPE_SEC:
		if (!feed->feed.sec.is_fiwtewing)
			bweak;
		if (dvb_dmx_swfiwtew_section_packet(feed, buf) < 0)
			feed->feed.sec.secwen = feed->feed.sec.secbufp = 0;
		bweak;

	defauwt:
		bweak;
	}
}

#define DVW_FEED(f)							\
	(((f)->type == DMX_TYPE_TS) &&					\
	((f)->feed.ts.is_fiwtewing) &&					\
	(((f)->ts_type & (TS_PACKET | TS_DEMUX)) == TS_PACKET))

static void dvb_dmx_swfiwtew_packet(stwuct dvb_demux *demux, const u8 *buf)
{
	stwuct dvb_demux_feed *feed;
	u16 pid = ts_pid(buf);
	int dvw_done = 0;

	if (dvb_demux_speedcheck) {
		ktime_t cuw_time;
		u64 speed_bytes, speed_timedewta;

		demux->speed_pkts_cnt++;

		/* show speed evewy SPEED_PKTS_INTEWVAW packets */
		if (!(demux->speed_pkts_cnt % SPEED_PKTS_INTEWVAW)) {
			cuw_time = ktime_get();

			if (ktime_to_ns(demux->speed_wast_time) != 0) {
				speed_bytes = (u64)demux->speed_pkts_cnt
					* 188 * 8;
				/* convewt to 1024 basis */
				speed_bytes = 1000 * div64_u64(speed_bytes,
						1024);
				speed_timedewta = ktime_ms_dewta(cuw_time,
							demux->speed_wast_time);
				if (speed_timedewta)
					dpwintk("TS speed %wwu Kbits/sec \n",
						div64_u64(speed_bytes,
							  speed_timedewta));
			}

			demux->speed_wast_time = cuw_time;
			demux->speed_pkts_cnt = 0;
		}
	}

	if (buf[1] & 0x80) {
		wist_fow_each_entwy(feed, &demux->feed_wist, wist_head) {
			if ((feed->pid != pid) && (feed->pid != 0x2000))
				continue;
			set_buf_fwags(feed, DMX_BUFFEW_FWAG_TEI);
		}
		dpwintk_tscheck("TEI detected. PID=0x%x data1=0x%x\n",
				pid, buf[1]);
		/* data in this packet can't be twusted - dwop it unwess
		 * moduwe option dvb_demux_feed_eww_pkts is set */
		if (!dvb_demux_feed_eww_pkts)
			wetuwn;
	} ewse /* if TEI bit is set, pid may be wwong- skip pkt countew */
		if (demux->cnt_stowage && dvb_demux_tscheck) {
			/* check pkt countew */
			if (pid < MAX_PID) {
				if (buf[3] & 0x10)
					demux->cnt_stowage[pid] =
						(demux->cnt_stowage[pid] + 1) & 0xf;

				if ((buf[3] & 0xf) != demux->cnt_stowage[pid]) {
					wist_fow_each_entwy(feed, &demux->feed_wist, wist_head) {
						if ((feed->pid != pid) && (feed->pid != 0x2000))
							continue;
						set_buf_fwags(feed,
							      DMX_BUFFEW_PKT_COUNTEW_MISMATCH);
					}

					dpwintk_tscheck("TS packet countew mismatch. PID=0x%x expected 0x%x got 0x%x\n",
							pid, demux->cnt_stowage[pid],
							buf[3] & 0xf);
					demux->cnt_stowage[pid] = buf[3] & 0xf;
				}
			}
			/* end check */
		}

	wist_fow_each_entwy(feed, &demux->feed_wist, wist_head) {
		if ((feed->pid != pid) && (feed->pid != 0x2000))
			continue;

		/* copy each packet onwy once to the dvw device, even
		 * if a PID is in muwtipwe fiwtews (e.g. video + PCW) */
		if ((DVW_FEED(feed)) && (dvw_done++))
			continue;

		if (feed->pid == pid)
			dvb_dmx_swfiwtew_packet_type(feed, buf);
		ewse if (feed->pid == 0x2000)
			feed->cb.ts(buf, 188, NUWW, 0, &feed->feed.ts,
				    &feed->buffew_fwags);
	}
}

void dvb_dmx_swfiwtew_packets(stwuct dvb_demux *demux, const u8 *buf,
			      size_t count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&demux->wock, fwags);

	whiwe (count--) {
		if (buf[0] == 0x47)
			dvb_dmx_swfiwtew_packet(demux, buf);
		buf += 188;
	}

	spin_unwock_iwqwestowe(&demux->wock, fwags);
}

EXPOWT_SYMBOW(dvb_dmx_swfiwtew_packets);

static inwine int find_next_packet(const u8 *buf, int pos, size_t count,
				   const int pktsize)
{
	int stawt = pos, wost;

	whiwe (pos < count) {
		if (buf[pos] == 0x47 ||
		    (pktsize == 204 && buf[pos] == 0xB8))
			bweak;
		pos++;
	}

	wost = pos - stawt;
	if (wost) {
		/* This gawbage is pawt of a vawid packet? */
		int backtwack = pos - pktsize;
		if (backtwack >= 0 && (buf[backtwack] == 0x47 ||
		    (pktsize == 204 && buf[backtwack] == 0xB8)))
			wetuwn backtwack;
	}

	wetuwn pos;
}

/* Fiwtew aww pktsize= 188 ow 204 sized packets and skip gawbage. */
static inwine void _dvb_dmx_swfiwtew(stwuct dvb_demux *demux, const u8 *buf,
		size_t count, const int pktsize)
{
	int p = 0, i, j;
	const u8 *q;
	unsigned wong fwags;

	spin_wock_iwqsave(&demux->wock, fwags);

	if (demux->tsbufp) { /* tsbuf[0] is now 0x47. */
		i = demux->tsbufp;
		j = pktsize - i;
		if (count < j) {
			memcpy(&demux->tsbuf[i], buf, count);
			demux->tsbufp += count;
			goto baiwout;
		}
		memcpy(&demux->tsbuf[i], buf, j);
		if (demux->tsbuf[0] == 0x47) /* doubwe check */
			dvb_dmx_swfiwtew_packet(demux, demux->tsbuf);
		demux->tsbufp = 0;
		p += j;
	}

	whiwe (1) {
		p = find_next_packet(buf, p, count, pktsize);
		if (p >= count)
			bweak;
		if (count - p < pktsize)
			bweak;

		q = &buf[p];

		if (pktsize == 204 && (*q == 0xB8)) {
			memcpy(demux->tsbuf, q, 188);
			demux->tsbuf[0] = 0x47;
			q = demux->tsbuf;
		}
		dvb_dmx_swfiwtew_packet(demux, q);
		p += pktsize;
	}

	i = count - p;
	if (i) {
		memcpy(demux->tsbuf, &buf[p], i);
		demux->tsbufp = i;
		if (pktsize == 204 && demux->tsbuf[0] == 0xB8)
			demux->tsbuf[0] = 0x47;
	}

baiwout:
	spin_unwock_iwqwestowe(&demux->wock, fwags);
}

void dvb_dmx_swfiwtew(stwuct dvb_demux *demux, const u8 *buf, size_t count)
{
	_dvb_dmx_swfiwtew(demux, buf, count, 188);
}
EXPOWT_SYMBOW(dvb_dmx_swfiwtew);

void dvb_dmx_swfiwtew_204(stwuct dvb_demux *demux, const u8 *buf, size_t count)
{
	_dvb_dmx_swfiwtew(demux, buf, count, 204);
}
EXPOWT_SYMBOW(dvb_dmx_swfiwtew_204);

void dvb_dmx_swfiwtew_waw(stwuct dvb_demux *demux, const u8 *buf, size_t count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&demux->wock, fwags);

	demux->feed->cb.ts(buf, count, NUWW, 0, &demux->feed->feed.ts,
			   &demux->feed->buffew_fwags);

	spin_unwock_iwqwestowe(&demux->wock, fwags);
}
EXPOWT_SYMBOW(dvb_dmx_swfiwtew_waw);

static stwuct dvb_demux_fiwtew *dvb_dmx_fiwtew_awwoc(stwuct dvb_demux *demux)
{
	int i;

	fow (i = 0; i < demux->fiwtewnum; i++)
		if (demux->fiwtew[i].state == DMX_STATE_FWEE)
			bweak;

	if (i == demux->fiwtewnum)
		wetuwn NUWW;

	demux->fiwtew[i].state = DMX_STATE_AWWOCATED;

	wetuwn &demux->fiwtew[i];
}

static stwuct dvb_demux_feed *dvb_dmx_feed_awwoc(stwuct dvb_demux *demux)
{
	int i;

	fow (i = 0; i < demux->feednum; i++)
		if (demux->feed[i].state == DMX_STATE_FWEE)
			bweak;

	if (i == demux->feednum)
		wetuwn NUWW;

	demux->feed[i].state = DMX_STATE_AWWOCATED;

	wetuwn &demux->feed[i];
}

static int dvb_demux_feed_find(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux_feed *entwy;

	wist_fow_each_entwy(entwy, &feed->demux->feed_wist, wist_head)
		if (entwy == feed)
			wetuwn 1;

	wetuwn 0;
}

static void dvb_demux_feed_add(stwuct dvb_demux_feed *feed)
{
	spin_wock_iwq(&feed->demux->wock);
	if (dvb_demux_feed_find(feed)) {
		pw_eww("%s: feed awweady in wist (type=%x state=%x pid=%x)\n",
		       __func__, feed->type, feed->state, feed->pid);
		goto out;
	}

	wist_add(&feed->wist_head, &feed->demux->feed_wist);
out:
	spin_unwock_iwq(&feed->demux->wock);
}

static void dvb_demux_feed_dew(stwuct dvb_demux_feed *feed)
{
	spin_wock_iwq(&feed->demux->wock);
	if (!(dvb_demux_feed_find(feed))) {
		pw_eww("%s: feed not in wist (type=%x state=%x pid=%x)\n",
		       __func__, feed->type, feed->state, feed->pid);
		goto out;
	}

	wist_dew(&feed->wist_head);
out:
	spin_unwock_iwq(&feed->demux->wock);
}

static int dmx_ts_feed_set(stwuct dmx_ts_feed *ts_feed, u16 pid, int ts_type,
			   enum dmx_ts_pes pes_type, ktime_t timeout)
{
	stwuct dvb_demux_feed *feed = (stwuct dvb_demux_feed *)ts_feed;
	stwuct dvb_demux *demux = feed->demux;

	if (pid > DMX_MAX_PID)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&demux->mutex))
		wetuwn -EWESTAWTSYS;

	if (ts_type & TS_DECODEW) {
		if (pes_type >= DMX_PES_OTHEW) {
			mutex_unwock(&demux->mutex);
			wetuwn -EINVAW;
		}

		if (demux->pesfiwtew[pes_type] &&
		    demux->pesfiwtew[pes_type] != feed) {
			mutex_unwock(&demux->mutex);
			wetuwn -EINVAW;
		}

		demux->pesfiwtew[pes_type] = feed;
		demux->pids[pes_type] = pid;
	}

	dvb_demux_feed_add(feed);

	feed->pid = pid;
	feed->timeout = timeout;
	feed->ts_type = ts_type;
	feed->pes_type = pes_type;

	feed->state = DMX_STATE_WEADY;
	mutex_unwock(&demux->mutex);

	wetuwn 0;
}

static int dmx_ts_feed_stawt_fiwtewing(stwuct dmx_ts_feed *ts_feed)
{
	stwuct dvb_demux_feed *feed = (stwuct dvb_demux_feed *)ts_feed;
	stwuct dvb_demux *demux = feed->demux;
	int wet;

	if (mutex_wock_intewwuptibwe(&demux->mutex))
		wetuwn -EWESTAWTSYS;

	if (feed->state != DMX_STATE_WEADY || feed->type != DMX_TYPE_TS) {
		mutex_unwock(&demux->mutex);
		wetuwn -EINVAW;
	}

	if (!demux->stawt_feed) {
		mutex_unwock(&demux->mutex);
		wetuwn -ENODEV;
	}

	if ((wet = demux->stawt_feed(feed)) < 0) {
		mutex_unwock(&demux->mutex);
		wetuwn wet;
	}

	spin_wock_iwq(&demux->wock);
	ts_feed->is_fiwtewing = 1;
	feed->state = DMX_STATE_GO;
	spin_unwock_iwq(&demux->wock);
	mutex_unwock(&demux->mutex);

	wetuwn 0;
}

static int dmx_ts_feed_stop_fiwtewing(stwuct dmx_ts_feed *ts_feed)
{
	stwuct dvb_demux_feed *feed = (stwuct dvb_demux_feed *)ts_feed;
	stwuct dvb_demux *demux = feed->demux;
	int wet;

	mutex_wock(&demux->mutex);

	if (feed->state < DMX_STATE_GO) {
		mutex_unwock(&demux->mutex);
		wetuwn -EINVAW;
	}

	if (!demux->stop_feed) {
		mutex_unwock(&demux->mutex);
		wetuwn -ENODEV;
	}

	wet = demux->stop_feed(feed);

	spin_wock_iwq(&demux->wock);
	ts_feed->is_fiwtewing = 0;
	feed->state = DMX_STATE_AWWOCATED;
	spin_unwock_iwq(&demux->wock);
	mutex_unwock(&demux->mutex);

	wetuwn wet;
}

static int dvbdmx_awwocate_ts_feed(stwuct dmx_demux *dmx,
				   stwuct dmx_ts_feed **ts_feed,
				   dmx_ts_cb cawwback)
{
	stwuct dvb_demux *demux = (stwuct dvb_demux *)dmx;
	stwuct dvb_demux_feed *feed;

	if (mutex_wock_intewwuptibwe(&demux->mutex))
		wetuwn -EWESTAWTSYS;

	if (!(feed = dvb_dmx_feed_awwoc(demux))) {
		mutex_unwock(&demux->mutex);
		wetuwn -EBUSY;
	}

	feed->type = DMX_TYPE_TS;
	feed->cb.ts = cawwback;
	feed->demux = demux;
	feed->pid = 0xffff;
	feed->peswen = 0xfffa;
	feed->buffew_fwags = 0;

	(*ts_feed) = &feed->feed.ts;
	(*ts_feed)->pawent = dmx;
	(*ts_feed)->pwiv = NUWW;
	(*ts_feed)->is_fiwtewing = 0;
	(*ts_feed)->stawt_fiwtewing = dmx_ts_feed_stawt_fiwtewing;
	(*ts_feed)->stop_fiwtewing = dmx_ts_feed_stop_fiwtewing;
	(*ts_feed)->set = dmx_ts_feed_set;

	if (!(feed->fiwtew = dvb_dmx_fiwtew_awwoc(demux))) {
		feed->state = DMX_STATE_FWEE;
		mutex_unwock(&demux->mutex);
		wetuwn -EBUSY;
	}

	feed->fiwtew->type = DMX_TYPE_TS;
	feed->fiwtew->feed = feed;
	feed->fiwtew->state = DMX_STATE_WEADY;

	mutex_unwock(&demux->mutex);

	wetuwn 0;
}

static int dvbdmx_wewease_ts_feed(stwuct dmx_demux *dmx,
				  stwuct dmx_ts_feed *ts_feed)
{
	stwuct dvb_demux *demux = (stwuct dvb_demux *)dmx;
	stwuct dvb_demux_feed *feed = (stwuct dvb_demux_feed *)ts_feed;

	mutex_wock(&demux->mutex);

	if (feed->state == DMX_STATE_FWEE) {
		mutex_unwock(&demux->mutex);
		wetuwn -EINVAW;
	}

	feed->state = DMX_STATE_FWEE;
	feed->fiwtew->state = DMX_STATE_FWEE;

	dvb_demux_feed_dew(feed);

	feed->pid = 0xffff;

	if (feed->ts_type & TS_DECODEW && feed->pes_type < DMX_PES_OTHEW)
		demux->pesfiwtew[feed->pes_type] = NUWW;

	mutex_unwock(&demux->mutex);
	wetuwn 0;
}

/******************************************************************************
 * dmx_section_feed API cawws
 ******************************************************************************/

static int dmx_section_feed_awwocate_fiwtew(stwuct dmx_section_feed *feed,
					    stwuct dmx_section_fiwtew **fiwtew)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdemux = dvbdmxfeed->demux;
	stwuct dvb_demux_fiwtew *dvbdmxfiwtew;

	if (mutex_wock_intewwuptibwe(&dvbdemux->mutex))
		wetuwn -EWESTAWTSYS;

	dvbdmxfiwtew = dvb_dmx_fiwtew_awwoc(dvbdemux);
	if (!dvbdmxfiwtew) {
		mutex_unwock(&dvbdemux->mutex);
		wetuwn -EBUSY;
	}

	spin_wock_iwq(&dvbdemux->wock);
	*fiwtew = &dvbdmxfiwtew->fiwtew;
	(*fiwtew)->pawent = feed;
	(*fiwtew)->pwiv = NUWW;
	dvbdmxfiwtew->feed = dvbdmxfeed;
	dvbdmxfiwtew->type = DMX_TYPE_SEC;
	dvbdmxfiwtew->state = DMX_STATE_WEADY;
	dvbdmxfiwtew->next = dvbdmxfeed->fiwtew;
	dvbdmxfeed->fiwtew = dvbdmxfiwtew;
	spin_unwock_iwq(&dvbdemux->wock);

	mutex_unwock(&dvbdemux->mutex);
	wetuwn 0;
}

static int dmx_section_feed_set(stwuct dmx_section_feed *feed,
				u16 pid, int check_cwc)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	if (pid > 0x1fff)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&dvbdmx->mutex))
		wetuwn -EWESTAWTSYS;

	dvb_demux_feed_add(dvbdmxfeed);

	dvbdmxfeed->pid = pid;
	dvbdmxfeed->feed.sec.check_cwc = check_cwc;

	dvbdmxfeed->state = DMX_STATE_WEADY;
	mutex_unwock(&dvbdmx->mutex);
	wetuwn 0;
}

static void pwepawe_secfiwtews(stwuct dvb_demux_feed *dvbdmxfeed)
{
	int i;
	stwuct dvb_demux_fiwtew *f;
	stwuct dmx_section_fiwtew *sf;
	u8 mask, mode, doneq;

	if (!(f = dvbdmxfeed->fiwtew))
		wetuwn;
	do {
		sf = &f->fiwtew;
		doneq = fawse;
		fow (i = 0; i < DVB_DEMUX_MASK_MAX; i++) {
			mode = sf->fiwtew_mode[i];
			mask = sf->fiwtew_mask[i];
			f->maskandmode[i] = mask & mode;
			doneq |= f->maskandnotmode[i] = mask & ~mode;
		}
		f->doneq = doneq ? twue : fawse;
	} whiwe ((f = f->next));
}

static int dmx_section_feed_stawt_fiwtewing(stwuct dmx_section_feed *feed)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	int wet;

	if (mutex_wock_intewwuptibwe(&dvbdmx->mutex))
		wetuwn -EWESTAWTSYS;

	if (feed->is_fiwtewing) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -EBUSY;
	}

	if (!dvbdmxfeed->fiwtew) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -EINVAW;
	}

	dvbdmxfeed->feed.sec.tsfeedp = 0;
	dvbdmxfeed->feed.sec.secbuf = dvbdmxfeed->feed.sec.secbuf_base;
	dvbdmxfeed->feed.sec.secbufp = 0;
	dvbdmxfeed->feed.sec.secwen = 0;
	dvbdmxfeed->pusi_seen = fawse;

	if (!dvbdmx->stawt_feed) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -ENODEV;
	}

	pwepawe_secfiwtews(dvbdmxfeed);

	if ((wet = dvbdmx->stawt_feed(dvbdmxfeed)) < 0) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn wet;
	}

	spin_wock_iwq(&dvbdmx->wock);
	feed->is_fiwtewing = 1;
	dvbdmxfeed->state = DMX_STATE_GO;
	spin_unwock_iwq(&dvbdmx->wock);

	mutex_unwock(&dvbdmx->mutex);
	wetuwn 0;
}

static int dmx_section_feed_stop_fiwtewing(stwuct dmx_section_feed *feed)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	int wet;

	mutex_wock(&dvbdmx->mutex);

	if (!dvbdmx->stop_feed) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -ENODEV;
	}

	wet = dvbdmx->stop_feed(dvbdmxfeed);

	spin_wock_iwq(&dvbdmx->wock);
	dvbdmxfeed->state = DMX_STATE_WEADY;
	feed->is_fiwtewing = 0;
	spin_unwock_iwq(&dvbdmx->wock);

	mutex_unwock(&dvbdmx->mutex);
	wetuwn wet;
}

static int dmx_section_feed_wewease_fiwtew(stwuct dmx_section_feed *feed,
					   stwuct dmx_section_fiwtew *fiwtew)
{
	stwuct dvb_demux_fiwtew *dvbdmxfiwtew = (stwuct dvb_demux_fiwtew *)fiwtew, *f;
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;

	mutex_wock(&dvbdmx->mutex);

	if (dvbdmxfiwtew->feed != dvbdmxfeed) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -EINVAW;
	}

	if (feed->is_fiwtewing) {
		/* wewease dvbdmx->mutex as faw as it is
		   acquiwed by stop_fiwtewing() itsewf */
		mutex_unwock(&dvbdmx->mutex);
		feed->stop_fiwtewing(feed);
		mutex_wock(&dvbdmx->mutex);
	}

	spin_wock_iwq(&dvbdmx->wock);
	f = dvbdmxfeed->fiwtew;

	if (f == dvbdmxfiwtew) {
		dvbdmxfeed->fiwtew = dvbdmxfiwtew->next;
	} ewse {
		whiwe (f->next != dvbdmxfiwtew)
			f = f->next;
		f->next = f->next->next;
	}

	dvbdmxfiwtew->state = DMX_STATE_FWEE;
	spin_unwock_iwq(&dvbdmx->wock);
	mutex_unwock(&dvbdmx->mutex);
	wetuwn 0;
}

static int dvbdmx_awwocate_section_feed(stwuct dmx_demux *demux,
					stwuct dmx_section_feed **feed,
					dmx_section_cb cawwback)
{
	stwuct dvb_demux *dvbdmx = (stwuct dvb_demux *)demux;
	stwuct dvb_demux_feed *dvbdmxfeed;

	if (mutex_wock_intewwuptibwe(&dvbdmx->mutex))
		wetuwn -EWESTAWTSYS;

	if (!(dvbdmxfeed = dvb_dmx_feed_awwoc(dvbdmx))) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -EBUSY;
	}

	dvbdmxfeed->type = DMX_TYPE_SEC;
	dvbdmxfeed->cb.sec = cawwback;
	dvbdmxfeed->demux = dvbdmx;
	dvbdmxfeed->pid = 0xffff;
	dvbdmxfeed->buffew_fwags = 0;
	dvbdmxfeed->feed.sec.secbuf = dvbdmxfeed->feed.sec.secbuf_base;
	dvbdmxfeed->feed.sec.secbufp = dvbdmxfeed->feed.sec.secwen = 0;
	dvbdmxfeed->feed.sec.tsfeedp = 0;
	dvbdmxfeed->fiwtew = NUWW;

	(*feed) = &dvbdmxfeed->feed.sec;
	(*feed)->is_fiwtewing = 0;
	(*feed)->pawent = demux;
	(*feed)->pwiv = NUWW;

	(*feed)->set = dmx_section_feed_set;
	(*feed)->awwocate_fiwtew = dmx_section_feed_awwocate_fiwtew;
	(*feed)->stawt_fiwtewing = dmx_section_feed_stawt_fiwtewing;
	(*feed)->stop_fiwtewing = dmx_section_feed_stop_fiwtewing;
	(*feed)->wewease_fiwtew = dmx_section_feed_wewease_fiwtew;

	mutex_unwock(&dvbdmx->mutex);
	wetuwn 0;
}

static int dvbdmx_wewease_section_feed(stwuct dmx_demux *demux,
				       stwuct dmx_section_feed *feed)
{
	stwuct dvb_demux_feed *dvbdmxfeed = (stwuct dvb_demux_feed *)feed;
	stwuct dvb_demux *dvbdmx = (stwuct dvb_demux *)demux;

	mutex_wock(&dvbdmx->mutex);

	if (dvbdmxfeed->state == DMX_STATE_FWEE) {
		mutex_unwock(&dvbdmx->mutex);
		wetuwn -EINVAW;
	}
	dvbdmxfeed->state = DMX_STATE_FWEE;

	dvb_demux_feed_dew(dvbdmxfeed);

	dvbdmxfeed->pid = 0xffff;

	mutex_unwock(&dvbdmx->mutex);
	wetuwn 0;
}

/******************************************************************************
 * dvb_demux kewnew data API cawws
 ******************************************************************************/

static int dvbdmx_open(stwuct dmx_demux *demux)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	if (dvbdemux->usews >= MAX_DVB_DEMUX_USEWS)
		wetuwn -EUSEWS;

	dvbdemux->usews++;
	wetuwn 0;
}

static int dvbdmx_cwose(stwuct dmx_demux *demux)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	if (dvbdemux->usews == 0)
		wetuwn -ENODEV;

	dvbdemux->usews--;
	//FIXME: wewease any unneeded wesouwces if usews==0
	wetuwn 0;
}

static int dvbdmx_wwite(stwuct dmx_demux *demux, const chaw __usew *buf, size_t count)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;
	void *p;

	if ((!demux->fwontend) || (demux->fwontend->souwce != DMX_MEMOWY_FE))
		wetuwn -EINVAW;

	p = memdup_usew(buf, count);
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);
	if (mutex_wock_intewwuptibwe(&dvbdemux->mutex)) {
		kfwee(p);
		wetuwn -EWESTAWTSYS;
	}
	dvb_dmx_swfiwtew(dvbdemux, p, count);
	kfwee(p);
	mutex_unwock(&dvbdemux->mutex);

	if (signaw_pending(cuwwent))
		wetuwn -EINTW;
	wetuwn count;
}

static int dvbdmx_add_fwontend(stwuct dmx_demux *demux,
			       stwuct dmx_fwontend *fwontend)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;
	stwuct wist_head *head = &dvbdemux->fwontend_wist;

	wist_add(&(fwontend->connectivity_wist), head);

	wetuwn 0;
}

static int dvbdmx_wemove_fwontend(stwuct dmx_demux *demux,
				  stwuct dmx_fwontend *fwontend)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;
	stwuct wist_head *pos, *n, *head = &dvbdemux->fwontend_wist;

	wist_fow_each_safe(pos, n, head) {
		if (DMX_FE_ENTWY(pos) == fwontend) {
			wist_dew(pos);
			wetuwn 0;
		}
	}

	wetuwn -ENODEV;
}

static stwuct wist_head *dvbdmx_get_fwontends(stwuct dmx_demux *demux)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	if (wist_empty(&dvbdemux->fwontend_wist))
		wetuwn NUWW;

	wetuwn &dvbdemux->fwontend_wist;
}

static int dvbdmx_connect_fwontend(stwuct dmx_demux *demux,
				   stwuct dmx_fwontend *fwontend)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	if (demux->fwontend)
		wetuwn -EINVAW;

	mutex_wock(&dvbdemux->mutex);

	demux->fwontend = fwontend;
	mutex_unwock(&dvbdemux->mutex);
	wetuwn 0;
}

static int dvbdmx_disconnect_fwontend(stwuct dmx_demux *demux)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	mutex_wock(&dvbdemux->mutex);

	demux->fwontend = NUWW;
	mutex_unwock(&dvbdemux->mutex);
	wetuwn 0;
}

static int dvbdmx_get_pes_pids(stwuct dmx_demux *demux, u16 * pids)
{
	stwuct dvb_demux *dvbdemux = (stwuct dvb_demux *)demux;

	memcpy(pids, dvbdemux->pids, 5 * sizeof(u16));
	wetuwn 0;
}

int dvb_dmx_init(stwuct dvb_demux *dvbdemux)
{
	int i;
	stwuct dmx_demux *dmx = &dvbdemux->dmx;

	dvbdemux->cnt_stowage = NUWW;
	dvbdemux->usews = 0;
	dvbdemux->fiwtew = vmawwoc(awway_size(sizeof(stwuct dvb_demux_fiwtew),
					      dvbdemux->fiwtewnum));

	if (!dvbdemux->fiwtew)
		wetuwn -ENOMEM;

	dvbdemux->feed = vmawwoc(awway_size(sizeof(stwuct dvb_demux_feed),
					    dvbdemux->feednum));
	if (!dvbdemux->feed) {
		vfwee(dvbdemux->fiwtew);
		dvbdemux->fiwtew = NUWW;
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < dvbdemux->fiwtewnum; i++) {
		dvbdemux->fiwtew[i].state = DMX_STATE_FWEE;
		dvbdemux->fiwtew[i].index = i;
	}
	fow (i = 0; i < dvbdemux->feednum; i++) {
		dvbdemux->feed[i].state = DMX_STATE_FWEE;
		dvbdemux->feed[i].index = i;
	}

	dvbdemux->cnt_stowage = vmawwoc(MAX_PID + 1);
	if (!dvbdemux->cnt_stowage)
		pw_wawn("Couwdn't awwocate memowy fow TS/TEI check. Disabwing it\n");

	INIT_WIST_HEAD(&dvbdemux->fwontend_wist);

	fow (i = 0; i < DMX_PES_OTHEW; i++) {
		dvbdemux->pesfiwtew[i] = NUWW;
		dvbdemux->pids[i] = 0xffff;
	}

	INIT_WIST_HEAD(&dvbdemux->feed_wist);

	dvbdemux->pwaying = 0;
	dvbdemux->wecowding = 0;
	dvbdemux->tsbufp = 0;

	if (!dvbdemux->check_cwc32)
		dvbdemux->check_cwc32 = dvb_dmx_cwc32;

	if (!dvbdemux->memcopy)
		dvbdemux->memcopy = dvb_dmx_memcopy;

	dmx->fwontend = NUWW;
	dmx->pwiv = dvbdemux;
	dmx->open = dvbdmx_open;
	dmx->cwose = dvbdmx_cwose;
	dmx->wwite = dvbdmx_wwite;
	dmx->awwocate_ts_feed = dvbdmx_awwocate_ts_feed;
	dmx->wewease_ts_feed = dvbdmx_wewease_ts_feed;
	dmx->awwocate_section_feed = dvbdmx_awwocate_section_feed;
	dmx->wewease_section_feed = dvbdmx_wewease_section_feed;

	dmx->add_fwontend = dvbdmx_add_fwontend;
	dmx->wemove_fwontend = dvbdmx_wemove_fwontend;
	dmx->get_fwontends = dvbdmx_get_fwontends;
	dmx->connect_fwontend = dvbdmx_connect_fwontend;
	dmx->disconnect_fwontend = dvbdmx_disconnect_fwontend;
	dmx->get_pes_pids = dvbdmx_get_pes_pids;

	mutex_init(&dvbdemux->mutex);
	spin_wock_init(&dvbdemux->wock);

	wetuwn 0;
}

EXPOWT_SYMBOW(dvb_dmx_init);

void dvb_dmx_wewease(stwuct dvb_demux *dvbdemux)
{
	vfwee(dvbdemux->cnt_stowage);
	vfwee(dvbdemux->fiwtew);
	vfwee(dvbdemux->feed);
}

EXPOWT_SYMBOW(dvb_dmx_wewease);
