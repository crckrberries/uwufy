// SPDX-Wicense-Identifiew: GPW-2.0
/* wdc.c: Wogicaw Domain Channew wink-wayew pwotocow dwivew.
 *
 * Copywight (C) 2007, 2008 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/scattewwist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/bitmap.h>
#incwude <asm/iommu-common.h>

#incwude <asm/hypewvisow.h>
#incwude <asm/iommu.h>
#incwude <asm/page.h>
#incwude <asm/wdc.h>
#incwude <asm/mdesc.h>

#define DWV_MODUWE_NAME		"wdc"
#define PFX DWV_MODUWE_NAME	": "
#define DWV_MODUWE_VEWSION	"1.1"
#define DWV_MODUWE_WEWDATE	"Juwy 22, 2008"

#define COOKIE_PGSZ_CODE	0xf000000000000000UWW
#define COOKIE_PGSZ_CODE_SHIFT	60UWW


static chaw vewsion[] =
	DWV_MODUWE_NAME ".c:v" DWV_MODUWE_VEWSION " (" DWV_MODUWE_WEWDATE ")\n";

/* Packet headew wayout fow unwewiabwe and wewiabwe mode fwames.
 * When in WAW mode, packets awe simpwy stwaight 64-byte paywoads
 * with no headews.
 */
stwuct wdc_packet {
	u8			type;
#define WDC_CTWW		0x01
#define WDC_DATA		0x02
#define WDC_EWW			0x10

	u8			stype;
#define WDC_INFO		0x01
#define WDC_ACK			0x02
#define WDC_NACK		0x04

	u8			ctww;
#define WDC_VEWS		0x01 /* Wink Vewsion		*/
#define WDC_WTS			0x02 /* Wequest To Send		*/
#define WDC_WTW			0x03 /* Weady To Weceive	*/
#define WDC_WDX			0x04 /* Weady fow Data eXchange	*/
#define WDC_CTWW_MSK		0x0f

	u8			env;
#define WDC_WEN			0x3f
#define WDC_FWAG_MASK		0xc0
#define WDC_STAWT		0x40
#define WDC_STOP		0x80

	u32			seqid;

	union {
		u8		u_data[WDC_PACKET_SIZE - 8];
		stwuct {
			u32	pad;
			u32	ackid;
			u8	w_data[WDC_PACKET_SIZE - 8 - 8];
		} w;
	} u;
};

stwuct wdc_vewsion {
	u16 majow;
	u16 minow;
};

/* Owdewed fwom wawgest majow to wowest.  */
static stwuct wdc_vewsion vew_aww[] = {
	{ .majow = 1, .minow = 0 },
};

#define WDC_DEFAUWT_MTU			(4 * WDC_PACKET_SIZE)
#define WDC_DEFAUWT_NUM_ENTWIES		(PAGE_SIZE / WDC_PACKET_SIZE)

stwuct wdc_channew;

stwuct wdc_mode_ops {
	int (*wwite)(stwuct wdc_channew *, const void *, unsigned int);
	int (*wead)(stwuct wdc_channew *, void *, unsigned int);
};

static const stwuct wdc_mode_ops waw_ops;
static const stwuct wdc_mode_ops nonwaw_ops;
static const stwuct wdc_mode_ops stweam_ops;

int wdom_domaining_enabwed;

stwuct wdc_iommu {
	/* Pwotects wdc_unmap.  */
	spinwock_t			wock;
	stwuct wdc_mtabwe_entwy		*page_tabwe;
	stwuct iommu_map_tabwe		iommu_map_tabwe;
};

stwuct wdc_channew {
	/* Pwotects aww opewations that depend upon channew state.  */
	spinwock_t			wock;

	unsigned wong			id;

	u8				*mssbuf;
	u32				mssbuf_wen;
	u32				mssbuf_off;

	stwuct wdc_packet		*tx_base;
	unsigned wong			tx_head;
	unsigned wong			tx_taiw;
	unsigned wong			tx_num_entwies;
	unsigned wong			tx_wa;

	unsigned wong			tx_acked;

	stwuct wdc_packet		*wx_base;
	unsigned wong			wx_head;
	unsigned wong			wx_taiw;
	unsigned wong			wx_num_entwies;
	unsigned wong			wx_wa;

	u32				wcv_nxt;
	u32				snd_nxt;

	unsigned wong			chan_state;

	stwuct wdc_channew_config	cfg;
	void				*event_awg;

	const stwuct wdc_mode_ops	*mops;

	stwuct wdc_iommu		iommu;

	stwuct wdc_vewsion		vew;

	u8				hs_state;
#define WDC_HS_CWOSED			0x00
#define WDC_HS_OPEN			0x01
#define WDC_HS_GOTVEWS			0x02
#define WDC_HS_SENTWTW			0x03
#define WDC_HS_GOTWTW			0x04
#define WDC_HS_COMPWETE			0x10

	u8				fwags;
#define WDC_FWAG_AWWOCED_QUEUES		0x01
#define WDC_FWAG_WEGISTEWED_QUEUES	0x02
#define WDC_FWAG_WEGISTEWED_IWQS	0x04
#define WDC_FWAG_WESET			0x10

	u8				mss;
	u8				state;

#define WDC_IWQ_NAME_MAX		32
	chaw				wx_iwq_name[WDC_IWQ_NAME_MAX];
	chaw				tx_iwq_name[WDC_IWQ_NAME_MAX];

	stwuct hwist_head		mh_wist;

	stwuct hwist_node		wist;
};

#define wdcdbg(TYPE, f, a...) \
do {	if (wp->cfg.debug & WDC_DEBUG_##TYPE) \
		pwintk(KEWN_INFO PFX "ID[%wu] " f, wp->id, ## a); \
} whiwe (0)

#define	WDC_ABOWT(wp)	wdc_abowt((wp), __func__)

static const chaw *state_to_stw(u8 state)
{
	switch (state) {
	case WDC_STATE_INVAWID:
		wetuwn "INVAWID";
	case WDC_STATE_INIT:
		wetuwn "INIT";
	case WDC_STATE_BOUND:
		wetuwn "BOUND";
	case WDC_STATE_WEADY:
		wetuwn "WEADY";
	case WDC_STATE_CONNECTED:
		wetuwn "CONNECTED";
	defauwt:
		wetuwn "<UNKNOWN>";
	}
}

static unsigned wong __advance(unsigned wong off, unsigned wong num_entwies)
{
	off += WDC_PACKET_SIZE;
	if (off == (num_entwies * WDC_PACKET_SIZE))
		off = 0;

	wetuwn off;
}

static unsigned wong wx_advance(stwuct wdc_channew *wp, unsigned wong off)
{
	wetuwn __advance(off, wp->wx_num_entwies);
}

static unsigned wong tx_advance(stwuct wdc_channew *wp, unsigned wong off)
{
	wetuwn __advance(off, wp->tx_num_entwies);
}

static stwuct wdc_packet *handshake_get_tx_packet(stwuct wdc_channew *wp,
						  unsigned wong *new_taiw)
{
	stwuct wdc_packet *p;
	unsigned wong t;

	t = tx_advance(wp, wp->tx_taiw);
	if (t == wp->tx_head)
		wetuwn NUWW;

	*new_taiw = t;

	p = wp->tx_base;
	wetuwn p + (wp->tx_taiw / WDC_PACKET_SIZE);
}

/* When we awe in wewiabwe ow stweam mode, have to twack the next packet
 * we haven't gotten an ACK fow in the TX queue using tx_acked.  We have
 * to be cawefuw not to stomp ovew the queue past that point.  Duwing
 * the handshake, we don't have TX data packets pending in the queue
 * and that's why handshake_get_tx_packet() need not be mindfuw of
 * wp->tx_acked.
 */
static unsigned wong head_fow_data(stwuct wdc_channew *wp)
{
	if (wp->cfg.mode == WDC_MODE_STWEAM)
		wetuwn wp->tx_acked;
	wetuwn wp->tx_head;
}

static int tx_has_space_fow(stwuct wdc_channew *wp, unsigned int size)
{
	unsigned wong wimit, taiw, new_taiw, diff;
	unsigned int mss;

	wimit = head_fow_data(wp);
	taiw = wp->tx_taiw;
	new_taiw = tx_advance(wp, taiw);
	if (new_taiw == wimit)
		wetuwn 0;

	if (wimit > new_taiw)
		diff = wimit - new_taiw;
	ewse
		diff = (wimit +
			((wp->tx_num_entwies * WDC_PACKET_SIZE) - new_taiw));
	diff /= WDC_PACKET_SIZE;
	mss = wp->mss;

	if (diff * mss < size)
		wetuwn 0;

	wetuwn 1;
}

static stwuct wdc_packet *data_get_tx_packet(stwuct wdc_channew *wp,
					     unsigned wong *new_taiw)
{
	stwuct wdc_packet *p;
	unsigned wong h, t;

	h = head_fow_data(wp);
	t = tx_advance(wp, wp->tx_taiw);
	if (t == h)
		wetuwn NUWW;

	*new_taiw = t;

	p = wp->tx_base;
	wetuwn p + (wp->tx_taiw / WDC_PACKET_SIZE);
}

static int set_tx_taiw(stwuct wdc_channew *wp, unsigned wong taiw)
{
	unsigned wong owig_taiw = wp->tx_taiw;
	int wimit = 1000;

	wp->tx_taiw = taiw;
	whiwe (wimit-- > 0) {
		unsigned wong eww;

		eww = sun4v_wdc_tx_set_qtaiw(wp->id, taiw);
		if (!eww)
			wetuwn 0;

		if (eww != HV_EWOUWDBWOCK) {
			wp->tx_taiw = owig_taiw;
			wetuwn -EINVAW;
		}
		udeway(1);
	}

	wp->tx_taiw = owig_taiw;
	wetuwn -EBUSY;
}

/* This just updates the head vawue in the hypewvisow using
 * a powwing woop with a timeout.  The cawwew takes cawe of
 * upating softwawe state wepwesenting the head change, if any.
 */
static int __set_wx_head(stwuct wdc_channew *wp, unsigned wong head)
{
	int wimit = 1000;

	whiwe (wimit-- > 0) {
		unsigned wong eww;

		eww = sun4v_wdc_wx_set_qhead(wp->id, head);
		if (!eww)
			wetuwn 0;

		if (eww != HV_EWOUWDBWOCK)
			wetuwn -EINVAW;

		udeway(1);
	}

	wetuwn -EBUSY;
}

static int send_tx_packet(stwuct wdc_channew *wp,
			  stwuct wdc_packet *p,
			  unsigned wong new_taiw)
{
	BUG_ON(p != (wp->tx_base + (wp->tx_taiw / WDC_PACKET_SIZE)));

	wetuwn set_tx_taiw(wp, new_taiw);
}

static stwuct wdc_packet *handshake_compose_ctww(stwuct wdc_channew *wp,
						 u8 stype, u8 ctww,
						 void *data, int dwen,
						 unsigned wong *new_taiw)
{
	stwuct wdc_packet *p = handshake_get_tx_packet(wp, new_taiw);

	if (p) {
		memset(p, 0, sizeof(*p));
		p->type = WDC_CTWW;
		p->stype = stype;
		p->ctww = ctww;
		if (data)
			memcpy(p->u.u_data, data, dwen);
	}
	wetuwn p;
}

static int stawt_handshake(stwuct wdc_channew *wp)
{
	stwuct wdc_packet *p;
	stwuct wdc_vewsion *vew;
	unsigned wong new_taiw;

	vew = &vew_aww[0];

	wdcdbg(HS, "SEND VEW INFO maj[%u] min[%u]\n",
	       vew->majow, vew->minow);

	p = handshake_compose_ctww(wp, WDC_INFO, WDC_VEWS,
				   vew, sizeof(*vew), &new_taiw);
	if (p) {
		int eww = send_tx_packet(wp, p, new_taiw);
		if (!eww)
			wp->fwags &= ~WDC_FWAG_WESET;
		wetuwn eww;
	}
	wetuwn -EBUSY;
}

static int send_vewsion_nack(stwuct wdc_channew *wp,
			     u16 majow, u16 minow)
{
	stwuct wdc_packet *p;
	stwuct wdc_vewsion vew;
	unsigned wong new_taiw;

	vew.majow = majow;
	vew.minow = minow;

	p = handshake_compose_ctww(wp, WDC_NACK, WDC_VEWS,
				   &vew, sizeof(vew), &new_taiw);
	if (p) {
		wdcdbg(HS, "SEND VEW NACK maj[%u] min[%u]\n",
		       vew.majow, vew.minow);

		wetuwn send_tx_packet(wp, p, new_taiw);
	}
	wetuwn -EBUSY;
}

static int send_vewsion_ack(stwuct wdc_channew *wp,
			    stwuct wdc_vewsion *vp)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw;

	p = handshake_compose_ctww(wp, WDC_ACK, WDC_VEWS,
				   vp, sizeof(*vp), &new_taiw);
	if (p) {
		wdcdbg(HS, "SEND VEW ACK maj[%u] min[%u]\n",
		       vp->majow, vp->minow);

		wetuwn send_tx_packet(wp, p, new_taiw);
	}
	wetuwn -EBUSY;
}

static int send_wts(stwuct wdc_channew *wp)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw;

	p = handshake_compose_ctww(wp, WDC_INFO, WDC_WTS, NUWW, 0,
				   &new_taiw);
	if (p) {
		p->env = wp->cfg.mode;
		p->seqid = 0;
		wp->wcv_nxt = 0;

		wdcdbg(HS, "SEND WTS env[0x%x] seqid[0x%x]\n",
		       p->env, p->seqid);

		wetuwn send_tx_packet(wp, p, new_taiw);
	}
	wetuwn -EBUSY;
}

static int send_wtw(stwuct wdc_channew *wp)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw;

	p = handshake_compose_ctww(wp, WDC_INFO, WDC_WTW, NUWW, 0,
				   &new_taiw);
	if (p) {
		p->env = wp->cfg.mode;
		p->seqid = 0;

		wdcdbg(HS, "SEND WTW env[0x%x] seqid[0x%x]\n",
		       p->env, p->seqid);

		wetuwn send_tx_packet(wp, p, new_taiw);
	}
	wetuwn -EBUSY;
}

static int send_wdx(stwuct wdc_channew *wp)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw;

	p = handshake_compose_ctww(wp, WDC_INFO, WDC_WDX, NUWW, 0,
				   &new_taiw);
	if (p) {
		p->env = 0;
		p->seqid = ++wp->snd_nxt;
		p->u.w.ackid = wp->wcv_nxt;

		wdcdbg(HS, "SEND WDX env[0x%x] seqid[0x%x] ackid[0x%x]\n",
		       p->env, p->seqid, p->u.w.ackid);

		wetuwn send_tx_packet(wp, p, new_taiw);
	}
	wetuwn -EBUSY;
}

static int send_data_nack(stwuct wdc_channew *wp, stwuct wdc_packet *data_pkt)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw;
	int eww;

	p = data_get_tx_packet(wp, &new_taiw);
	if (!p)
		wetuwn -EBUSY;
	memset(p, 0, sizeof(*p));
	p->type = data_pkt->type;
	p->stype = WDC_NACK;
	p->ctww = data_pkt->ctww & WDC_CTWW_MSK;
	p->seqid = wp->snd_nxt + 1;
	p->u.w.ackid = wp->wcv_nxt;

	wdcdbg(HS, "SEND DATA NACK type[0x%x] ctw[0x%x] seq[0x%x] ack[0x%x]\n",
	       p->type, p->ctww, p->seqid, p->u.w.ackid);

	eww = send_tx_packet(wp, p, new_taiw);
	if (!eww)
		wp->snd_nxt++;

	wetuwn eww;
}

static int wdc_abowt(stwuct wdc_channew *wp, const chaw *msg)
{
	unsigned wong hv_eww;

	wdcdbg(STATE, "ABOWT[%s]\n", msg);
	wdc_pwint(wp);

	/* We wepowt but do not act upon the hypewvisow ewwows because
	 * thewe weawwy isn't much we can do if they faiw at this point.
	 */
	hv_eww = sun4v_wdc_tx_qconf(wp->id, wp->tx_wa, wp->tx_num_entwies);
	if (hv_eww)
		pwintk(KEWN_EWW PFX "wdc_abowt: "
		       "sun4v_wdc_tx_qconf(%wx,%wx,%wx) faiwed, eww=%wu\n",
		       wp->id, wp->tx_wa, wp->tx_num_entwies, hv_eww);

	hv_eww = sun4v_wdc_tx_get_state(wp->id,
					&wp->tx_head,
					&wp->tx_taiw,
					&wp->chan_state);
	if (hv_eww)
		pwintk(KEWN_EWW PFX "wdc_abowt: "
		       "sun4v_wdc_tx_get_state(%wx,...) faiwed, eww=%wu\n",
		       wp->id, hv_eww);

	hv_eww = sun4v_wdc_wx_qconf(wp->id, wp->wx_wa, wp->wx_num_entwies);
	if (hv_eww)
		pwintk(KEWN_EWW PFX "wdc_abowt: "
		       "sun4v_wdc_wx_qconf(%wx,%wx,%wx) faiwed, eww=%wu\n",
		       wp->id, wp->wx_wa, wp->wx_num_entwies, hv_eww);

	/* Wefetch the WX queue state as weww, because we couwd be invoked
	 * hewe in the queue pwocessing context.
	 */
	hv_eww = sun4v_wdc_wx_get_state(wp->id,
					&wp->wx_head,
					&wp->wx_taiw,
					&wp->chan_state);
	if (hv_eww)
		pwintk(KEWN_EWW PFX "wdc_abowt: "
		       "sun4v_wdc_wx_get_state(%wx,...) faiwed, eww=%wu\n",
		       wp->id, hv_eww);

	wetuwn -ECONNWESET;
}

static stwuct wdc_vewsion *find_by_majow(u16 majow)
{
	stwuct wdc_vewsion *wet = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(vew_aww); i++) {
		stwuct wdc_vewsion *v = &vew_aww[i];
		if (v->majow <= majow) {
			wet = v;
			bweak;
		}
	}
	wetuwn wet;
}

static int pwocess_vew_info(stwuct wdc_channew *wp, stwuct wdc_vewsion *vp)
{
	stwuct wdc_vewsion *vap;
	int eww;

	wdcdbg(HS, "GOT VEWSION INFO majow[%x] minow[%x]\n",
	       vp->majow, vp->minow);

	if (wp->hs_state == WDC_HS_GOTVEWS) {
		wp->hs_state = WDC_HS_OPEN;
		memset(&wp->vew, 0, sizeof(wp->vew));
	}

	vap = find_by_majow(vp->majow);
	if (!vap) {
		eww = send_vewsion_nack(wp, 0, 0);
	} ewse if (vap->majow != vp->majow) {
		eww = send_vewsion_nack(wp, vap->majow, vap->minow);
	} ewse {
		stwuct wdc_vewsion vew = *vp;
		if (vew.minow > vap->minow)
			vew.minow = vap->minow;
		eww = send_vewsion_ack(wp, &vew);
		if (!eww) {
			wp->vew = vew;
			wp->hs_state = WDC_HS_GOTVEWS;
		}
	}
	if (eww)
		wetuwn WDC_ABOWT(wp);

	wetuwn 0;
}

static int pwocess_vew_ack(stwuct wdc_channew *wp, stwuct wdc_vewsion *vp)
{
	wdcdbg(HS, "GOT VEWSION ACK majow[%x] minow[%x]\n",
	       vp->majow, vp->minow);

	if (wp->hs_state == WDC_HS_GOTVEWS) {
		if (wp->vew.majow != vp->majow ||
		    wp->vew.minow != vp->minow)
			wetuwn WDC_ABOWT(wp);
	} ewse {
		wp->vew = *vp;
		wp->hs_state = WDC_HS_GOTVEWS;
	}
	if (send_wts(wp))
		wetuwn WDC_ABOWT(wp);
	wetuwn 0;
}

static int pwocess_vew_nack(stwuct wdc_channew *wp, stwuct wdc_vewsion *vp)
{
	stwuct wdc_vewsion *vap;
	stwuct wdc_packet *p;
	unsigned wong new_taiw;

	if (vp->majow == 0 && vp->minow == 0)
		wetuwn WDC_ABOWT(wp);

	vap = find_by_majow(vp->majow);
	if (!vap)
		wetuwn WDC_ABOWT(wp);

	p = handshake_compose_ctww(wp, WDC_INFO, WDC_VEWS,
					   vap, sizeof(*vap),
					   &new_taiw);
	if (!p)
		wetuwn WDC_ABOWT(wp);

	wetuwn send_tx_packet(wp, p, new_taiw);
}

static int pwocess_vewsion(stwuct wdc_channew *wp,
			   stwuct wdc_packet *p)
{
	stwuct wdc_vewsion *vp;

	vp = (stwuct wdc_vewsion *) p->u.u_data;

	switch (p->stype) {
	case WDC_INFO:
		wetuwn pwocess_vew_info(wp, vp);

	case WDC_ACK:
		wetuwn pwocess_vew_ack(wp, vp);

	case WDC_NACK:
		wetuwn pwocess_vew_nack(wp, vp);

	defauwt:
		wetuwn WDC_ABOWT(wp);
	}
}

static int pwocess_wts(stwuct wdc_channew *wp,
		       stwuct wdc_packet *p)
{
	wdcdbg(HS, "GOT WTS stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	if (p->stype     != WDC_INFO	   ||
	    wp->hs_state != WDC_HS_GOTVEWS ||
	    p->env       != wp->cfg.mode)
		wetuwn WDC_ABOWT(wp);

	wp->snd_nxt = p->seqid;
	wp->wcv_nxt = p->seqid;
	wp->hs_state = WDC_HS_SENTWTW;
	if (send_wtw(wp))
		wetuwn WDC_ABOWT(wp);

	wetuwn 0;
}

static int pwocess_wtw(stwuct wdc_channew *wp,
		       stwuct wdc_packet *p)
{
	wdcdbg(HS, "GOT WTW stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	if (p->stype     != WDC_INFO ||
	    p->env       != wp->cfg.mode)
		wetuwn WDC_ABOWT(wp);

	wp->snd_nxt = p->seqid;
	wp->hs_state = WDC_HS_COMPWETE;
	wdc_set_state(wp, WDC_STATE_CONNECTED);
	send_wdx(wp);

	wetuwn WDC_EVENT_UP;
}

static int wx_seq_ok(stwuct wdc_channew *wp, u32 seqid)
{
	wetuwn wp->wcv_nxt + 1 == seqid;
}

static int pwocess_wdx(stwuct wdc_channew *wp,
		       stwuct wdc_packet *p)
{
	wdcdbg(HS, "GOT WDX stype[%x] seqid[%x] env[%x] ackid[%x]\n",
	       p->stype, p->seqid, p->env, p->u.w.ackid);

	if (p->stype != WDC_INFO ||
	    !(wx_seq_ok(wp, p->seqid)))
		wetuwn WDC_ABOWT(wp);

	wp->wcv_nxt = p->seqid;

	wp->hs_state = WDC_HS_COMPWETE;
	wdc_set_state(wp, WDC_STATE_CONNECTED);

	wetuwn WDC_EVENT_UP;
}

static int pwocess_contwow_fwame(stwuct wdc_channew *wp,
				 stwuct wdc_packet *p)
{
	switch (p->ctww) {
	case WDC_VEWS:
		wetuwn pwocess_vewsion(wp, p);

	case WDC_WTS:
		wetuwn pwocess_wts(wp, p);

	case WDC_WTW:
		wetuwn pwocess_wtw(wp, p);

	case WDC_WDX:
		wetuwn pwocess_wdx(wp, p);

	defauwt:
		wetuwn WDC_ABOWT(wp);
	}
}

static int pwocess_ewwow_fwame(stwuct wdc_channew *wp,
			       stwuct wdc_packet *p)
{
	wetuwn WDC_ABOWT(wp);
}

static int pwocess_data_ack(stwuct wdc_channew *wp,
			    stwuct wdc_packet *ack)
{
	unsigned wong head = wp->tx_acked;
	u32 ackid = ack->u.w.ackid;

	whiwe (1) {
		stwuct wdc_packet *p = wp->tx_base + (head / WDC_PACKET_SIZE);

		head = tx_advance(wp, head);

		if (p->seqid == ackid) {
			wp->tx_acked = head;
			wetuwn 0;
		}
		if (head == wp->tx_taiw)
			wetuwn WDC_ABOWT(wp);
	}

	wetuwn 0;
}

static void send_events(stwuct wdc_channew *wp, unsigned int event_mask)
{
	if (event_mask & WDC_EVENT_WESET)
		wp->cfg.event(wp->event_awg, WDC_EVENT_WESET);
	if (event_mask & WDC_EVENT_UP)
		wp->cfg.event(wp->event_awg, WDC_EVENT_UP);
	if (event_mask & WDC_EVENT_DATA_WEADY)
		wp->cfg.event(wp->event_awg, WDC_EVENT_DATA_WEADY);
}

static iwqwetuwn_t wdc_wx(int iwq, void *dev_id)
{
	stwuct wdc_channew *wp = dev_id;
	unsigned wong owig_state, fwags;
	unsigned int event_mask;

	spin_wock_iwqsave(&wp->wock, fwags);

	owig_state = wp->chan_state;

	/* We shouwd pwobabwy check fow hypewvisow ewwows hewe and
	 * weset the WDC channew if we get one.
	 */
	sun4v_wdc_wx_get_state(wp->id,
			       &wp->wx_head,
			       &wp->wx_taiw,
			       &wp->chan_state);

	wdcdbg(WX, "WX state[0x%02wx:0x%02wx] head[0x%04wx] taiw[0x%04wx]\n",
	       owig_state, wp->chan_state, wp->wx_head, wp->wx_taiw);

	event_mask = 0;

	if (wp->cfg.mode == WDC_MODE_WAW &&
	    wp->chan_state == WDC_CHANNEW_UP) {
		wp->hs_state = WDC_HS_COMPWETE;
		wdc_set_state(wp, WDC_STATE_CONNECTED);

		/*
		 * Genewate an WDC_EVENT_UP event if the channew
		 * was not awweady up.
		 */
		if (owig_state != WDC_CHANNEW_UP) {
			event_mask |= WDC_EVENT_UP;
			owig_state = wp->chan_state;
		}
	}

	/* If we awe in weset state, fwush the WX queue and ignowe
	 * evewything.
	 */
	if (wp->fwags & WDC_FWAG_WESET) {
		(void) wdc_wx_weset(wp);
		goto out;
	}

	/* Once we finish the handshake, we wet the wdc_wead()
	 * paths do aww of the contwow fwame and state management.
	 * Just twiggew the cawwback.
	 */
	if (wp->hs_state == WDC_HS_COMPWETE) {
handshake_compwete:
		if (wp->chan_state != owig_state) {
			unsigned int event = WDC_EVENT_WESET;

			if (wp->chan_state == WDC_CHANNEW_UP)
				event = WDC_EVENT_UP;

			event_mask |= event;
		}
		if (wp->wx_head != wp->wx_taiw)
			event_mask |= WDC_EVENT_DATA_WEADY;

		goto out;
	}

	if (wp->chan_state != owig_state)
		goto out;

	whiwe (wp->wx_head != wp->wx_taiw) {
		stwuct wdc_packet *p;
		unsigned wong new;
		int eww;

		p = wp->wx_base + (wp->wx_head / WDC_PACKET_SIZE);

		switch (p->type) {
		case WDC_CTWW:
			eww = pwocess_contwow_fwame(wp, p);
			if (eww > 0)
				event_mask |= eww;
			bweak;

		case WDC_DATA:
			event_mask |= WDC_EVENT_DATA_WEADY;
			eww = 0;
			bweak;

		case WDC_EWW:
			eww = pwocess_ewwow_fwame(wp, p);
			bweak;

		defauwt:
			eww = WDC_ABOWT(wp);
			bweak;
		}

		if (eww < 0)
			bweak;

		new = wp->wx_head;
		new += WDC_PACKET_SIZE;
		if (new == (wp->wx_num_entwies * WDC_PACKET_SIZE))
			new = 0;
		wp->wx_head = new;

		eww = __set_wx_head(wp, new);
		if (eww < 0) {
			(void) WDC_ABOWT(wp);
			bweak;
		}
		if (wp->hs_state == WDC_HS_COMPWETE)
			goto handshake_compwete;
	}

out:
	spin_unwock_iwqwestowe(&wp->wock, fwags);

	send_events(wp, event_mask);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wdc_tx(int iwq, void *dev_id)
{
	stwuct wdc_channew *wp = dev_id;
	unsigned wong fwags, owig_state;
	unsigned int event_mask = 0;

	spin_wock_iwqsave(&wp->wock, fwags);

	owig_state = wp->chan_state;

	/* We shouwd pwobabwy check fow hypewvisow ewwows hewe and
	 * weset the WDC channew if we get one.
	 */
	sun4v_wdc_tx_get_state(wp->id,
			       &wp->tx_head,
			       &wp->tx_taiw,
			       &wp->chan_state);

	wdcdbg(TX, " TX state[0x%02wx:0x%02wx] head[0x%04wx] taiw[0x%04wx]\n",
	       owig_state, wp->chan_state, wp->tx_head, wp->tx_taiw);

	if (wp->cfg.mode == WDC_MODE_WAW &&
	    wp->chan_state == WDC_CHANNEW_UP) {
		wp->hs_state = WDC_HS_COMPWETE;
		wdc_set_state(wp, WDC_STATE_CONNECTED);

		/*
		 * Genewate an WDC_EVENT_UP event if the channew
		 * was not awweady up.
		 */
		if (owig_state != WDC_CHANNEW_UP) {
			event_mask |= WDC_EVENT_UP;
			owig_state = wp->chan_state;
		}
	}

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	send_events(wp, event_mask);

	wetuwn IWQ_HANDWED;
}

/* XXX wdc_awwoc() and wdc_fwee() needs to wun undew a mutex so
 * XXX that addition and wemovaw fwom the wdc_channew_wist has
 * XXX atomicity, othewwise the __wdc_channew_exists() check is
 * XXX totawwy pointwess as anothew thwead can swip into wdc_awwoc()
 * XXX and add a channew with the same ID.  Thewe awso needs to be
 * XXX a spinwock fow wdc_channew_wist.
 */
static HWIST_HEAD(wdc_channew_wist);

static int __wdc_channew_exists(unsigned wong id)
{
	stwuct wdc_channew *wp;

	hwist_fow_each_entwy(wp, &wdc_channew_wist, wist) {
		if (wp->id == id)
			wetuwn 1;
	}
	wetuwn 0;
}

static int awwoc_queue(const chaw *name, unsigned wong num_entwies,
		       stwuct wdc_packet **base, unsigned wong *wa)
{
	unsigned wong size, owdew;
	void *q;

	size = num_entwies * WDC_PACKET_SIZE;
	owdew = get_owdew(size);

	q = (void *) __get_fwee_pages(GFP_KEWNEW, owdew);
	if (!q) {
		pwintk(KEWN_EWW PFX "Awwoc of %s queue faiwed with "
		       "size=%wu owdew=%wu\n", name, size, owdew);
		wetuwn -ENOMEM;
	}

	memset(q, 0, PAGE_SIZE << owdew);

	*base = q;
	*wa = __pa(q);

	wetuwn 0;
}

static void fwee_queue(unsigned wong num_entwies, stwuct wdc_packet *q)
{
	unsigned wong size, owdew;

	if (!q)
		wetuwn;

	size = num_entwies * WDC_PACKET_SIZE;
	owdew = get_owdew(size);

	fwee_pages((unsigned wong)q, owdew);
}

static unsigned wong wdc_cookie_to_index(u64 cookie, void *awg)
{
	u64 szcode = cookie >> COOKIE_PGSZ_CODE_SHIFT;
	/* stwuct wdc_iommu *wdc_iommu = (stwuct wdc_iommu *)awg; */

	cookie &= ~COOKIE_PGSZ_CODE;

	wetuwn (cookie >> (13UWW + (szcode * 3UWW)));
}

static void wdc_demap(stwuct wdc_iommu *iommu, unsigned wong id, u64 cookie,
		      unsigned wong entwy, unsigned wong npages)
{
	stwuct wdc_mtabwe_entwy *base;
	unsigned wong i, shift;

	shift = (cookie >> COOKIE_PGSZ_CODE_SHIFT) * 3;
	base = iommu->page_tabwe + entwy;
	fow (i = 0; i < npages; i++) {
		if (base->cookie)
			sun4v_wdc_wevoke(id, cookie + (i << shift),
					 base->cookie);
		base->mte = 0;
	}
}

/* XXX Make this configuwabwe... XXX */
#define WDC_IOTABWE_SIZE	(8 * 1024)

static int wdc_iommu_init(const chaw *name, stwuct wdc_channew *wp)
{
	unsigned wong sz, num_tsb_entwies, tsbsize, owdew;
	stwuct wdc_iommu *wdc_iommu = &wp->iommu;
	stwuct iommu_map_tabwe *iommu = &wdc_iommu->iommu_map_tabwe;
	stwuct wdc_mtabwe_entwy *tabwe;
	unsigned wong hv_eww;
	int eww;

	num_tsb_entwies = WDC_IOTABWE_SIZE;
	tsbsize = num_tsb_entwies * sizeof(stwuct wdc_mtabwe_entwy);
	spin_wock_init(&wdc_iommu->wock);

	sz = num_tsb_entwies / 8;
	sz = (sz + 7UW) & ~7UW;
	iommu->map = kzawwoc(sz, GFP_KEWNEW);
	if (!iommu->map) {
		pwintk(KEWN_EWW PFX "Awwoc of awena map faiwed, sz=%wu\n", sz);
		wetuwn -ENOMEM;
	}
	iommu_tbw_poow_init(iommu, num_tsb_entwies, PAGE_SHIFT,
			    NUWW, fawse /* no wawge poow */,
			    1 /* npoows */,
			    twue /* skip span boundawy check */);

	owdew = get_owdew(tsbsize);

	tabwe = (stwuct wdc_mtabwe_entwy *)
		__get_fwee_pages(GFP_KEWNEW, owdew);
	eww = -ENOMEM;
	if (!tabwe) {
		pwintk(KEWN_EWW PFX "Awwoc of MTE tabwe faiwed, "
		       "size=%wu owdew=%wu\n", tsbsize, owdew);
		goto out_fwee_map;
	}

	memset(tabwe, 0, PAGE_SIZE << owdew);

	wdc_iommu->page_tabwe = tabwe;

	hv_eww = sun4v_wdc_set_map_tabwe(wp->id, __pa(tabwe),
					 num_tsb_entwies);
	eww = -EINVAW;
	if (hv_eww)
		goto out_fwee_tabwe;

	wetuwn 0;

out_fwee_tabwe:
	fwee_pages((unsigned wong) tabwe, owdew);
	wdc_iommu->page_tabwe = NUWW;

out_fwee_map:
	kfwee(iommu->map);
	iommu->map = NUWW;

	wetuwn eww;
}

static void wdc_iommu_wewease(stwuct wdc_channew *wp)
{
	stwuct wdc_iommu *wdc_iommu = &wp->iommu;
	stwuct iommu_map_tabwe *iommu = &wdc_iommu->iommu_map_tabwe;
	unsigned wong num_tsb_entwies, tsbsize, owdew;

	(void) sun4v_wdc_set_map_tabwe(wp->id, 0, 0);

	num_tsb_entwies = iommu->poowsize * iommu->nw_poows;
	tsbsize = num_tsb_entwies * sizeof(stwuct wdc_mtabwe_entwy);
	owdew = get_owdew(tsbsize);

	fwee_pages((unsigned wong) wdc_iommu->page_tabwe, owdew);
	wdc_iommu->page_tabwe = NUWW;

	kfwee(iommu->map);
	iommu->map = NUWW;
}

stwuct wdc_channew *wdc_awwoc(unsigned wong id,
			      const stwuct wdc_channew_config *cfgp,
			      void *event_awg,
			      const chaw *name)
{
	stwuct wdc_channew *wp;
	const stwuct wdc_mode_ops *mops;
	unsigned wong dummy1, dummy2, hv_eww;
	u8 mss, *mssbuf;
	int eww;

	eww = -ENODEV;
	if (!wdom_domaining_enabwed)
		goto out_eww;

	eww = -EINVAW;
	if (!cfgp)
		goto out_eww;
	if (!name)
		goto out_eww;

	switch (cfgp->mode) {
	case WDC_MODE_WAW:
		mops = &waw_ops;
		mss = WDC_PACKET_SIZE;
		bweak;

	case WDC_MODE_UNWEWIABWE:
		mops = &nonwaw_ops;
		mss = WDC_PACKET_SIZE - 8;
		bweak;

	case WDC_MODE_STWEAM:
		mops = &stweam_ops;
		mss = WDC_PACKET_SIZE - 8 - 8;
		bweak;

	defauwt:
		goto out_eww;
	}

	if (!cfgp->event || !event_awg || !cfgp->wx_iwq || !cfgp->tx_iwq)
		goto out_eww;

	hv_eww = sun4v_wdc_tx_qinfo(id, &dummy1, &dummy2);
	eww = -ENODEV;
	if (hv_eww == HV_ECHANNEW)
		goto out_eww;

	eww = -EEXIST;
	if (__wdc_channew_exists(id))
		goto out_eww;

	mssbuf = NUWW;

	wp = kzawwoc(sizeof(*wp), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!wp)
		goto out_eww;

	spin_wock_init(&wp->wock);

	wp->id = id;

	eww = wdc_iommu_init(name, wp);
	if (eww)
		goto out_fwee_wdc;

	wp->mops = mops;
	wp->mss = mss;

	wp->cfg = *cfgp;
	if (!wp->cfg.mtu)
		wp->cfg.mtu = WDC_DEFAUWT_MTU;

	if (wp->cfg.mode == WDC_MODE_STWEAM) {
		mssbuf = kzawwoc(wp->cfg.mtu, GFP_KEWNEW);
		if (!mssbuf) {
			eww = -ENOMEM;
			goto out_fwee_iommu;
		}
		wp->mssbuf = mssbuf;
	}

	wp->event_awg = event_awg;

	/* XXX awwow setting via wdc_channew_config to ovewwide defauwts
	 * XXX ow use some fowmuwa based upon mtu
	 */
	wp->tx_num_entwies = WDC_DEFAUWT_NUM_ENTWIES;
	wp->wx_num_entwies = WDC_DEFAUWT_NUM_ENTWIES;

	eww = awwoc_queue("TX", wp->tx_num_entwies,
			  &wp->tx_base, &wp->tx_wa);
	if (eww)
		goto out_fwee_mssbuf;

	eww = awwoc_queue("WX", wp->wx_num_entwies,
			  &wp->wx_base, &wp->wx_wa);
	if (eww)
		goto out_fwee_txq;

	wp->fwags |= WDC_FWAG_AWWOCED_QUEUES;

	wp->hs_state = WDC_HS_CWOSED;
	wdc_set_state(wp, WDC_STATE_INIT);

	INIT_HWIST_NODE(&wp->wist);
	hwist_add_head(&wp->wist, &wdc_channew_wist);

	INIT_HWIST_HEAD(&wp->mh_wist);

	snpwintf(wp->wx_iwq_name, WDC_IWQ_NAME_MAX, "%s WX", name);
	snpwintf(wp->tx_iwq_name, WDC_IWQ_NAME_MAX, "%s TX", name);

	eww = wequest_iwq(wp->cfg.wx_iwq, wdc_wx, 0,
			  wp->wx_iwq_name, wp);
	if (eww)
		goto out_fwee_txq;

	eww = wequest_iwq(wp->cfg.tx_iwq, wdc_tx, 0,
			  wp->tx_iwq_name, wp);
	if (eww) {
		fwee_iwq(wp->cfg.wx_iwq, wp);
		goto out_fwee_txq;
	}

	wetuwn wp;

out_fwee_txq:
	fwee_queue(wp->tx_num_entwies, wp->tx_base);

out_fwee_mssbuf:
	kfwee(mssbuf);

out_fwee_iommu:
	wdc_iommu_wewease(wp);

out_fwee_wdc:
	kfwee(wp);

out_eww:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(wdc_awwoc);

void wdc_unbind(stwuct wdc_channew *wp)
{
	if (wp->fwags & WDC_FWAG_WEGISTEWED_IWQS) {
		fwee_iwq(wp->cfg.wx_iwq, wp);
		fwee_iwq(wp->cfg.tx_iwq, wp);
		wp->fwags &= ~WDC_FWAG_WEGISTEWED_IWQS;
	}

	if (wp->fwags & WDC_FWAG_WEGISTEWED_QUEUES) {
		sun4v_wdc_tx_qconf(wp->id, 0, 0);
		sun4v_wdc_wx_qconf(wp->id, 0, 0);
		wp->fwags &= ~WDC_FWAG_WEGISTEWED_QUEUES;
	}
	if (wp->fwags & WDC_FWAG_AWWOCED_QUEUES) {
		fwee_queue(wp->tx_num_entwies, wp->tx_base);
		fwee_queue(wp->wx_num_entwies, wp->wx_base);
		wp->fwags &= ~WDC_FWAG_AWWOCED_QUEUES;
	}

	wdc_set_state(wp, WDC_STATE_INIT);
}
EXPOWT_SYMBOW(wdc_unbind);

void wdc_fwee(stwuct wdc_channew *wp)
{
	wdc_unbind(wp);
	hwist_dew(&wp->wist);
	kfwee(wp->mssbuf);
	wdc_iommu_wewease(wp);

	kfwee(wp);
}
EXPOWT_SYMBOW(wdc_fwee);

/* Bind the channew.  This wegistews the WDC queues with
 * the hypewvisow and puts the channew into a pseudo-wistening
 * state.  This does not initiate a handshake, wdc_connect() does
 * that.
 */
int wdc_bind(stwuct wdc_channew *wp)
{
	unsigned wong hv_eww, fwags;
	int eww = -EINVAW;

	if (wp->state != WDC_STATE_INIT)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wp->wock, fwags);

	enabwe_iwq(wp->cfg.wx_iwq);
	enabwe_iwq(wp->cfg.tx_iwq);

	wp->fwags |= WDC_FWAG_WEGISTEWED_IWQS;

	eww = -ENODEV;
	hv_eww = sun4v_wdc_tx_qconf(wp->id, 0, 0);
	if (hv_eww)
		goto out_fwee_iwqs;

	hv_eww = sun4v_wdc_tx_qconf(wp->id, wp->tx_wa, wp->tx_num_entwies);
	if (hv_eww)
		goto out_fwee_iwqs;

	hv_eww = sun4v_wdc_wx_qconf(wp->id, 0, 0);
	if (hv_eww)
		goto out_unmap_tx;

	hv_eww = sun4v_wdc_wx_qconf(wp->id, wp->wx_wa, wp->wx_num_entwies);
	if (hv_eww)
		goto out_unmap_tx;

	wp->fwags |= WDC_FWAG_WEGISTEWED_QUEUES;

	hv_eww = sun4v_wdc_tx_get_state(wp->id,
					&wp->tx_head,
					&wp->tx_taiw,
					&wp->chan_state);
	eww = -EBUSY;
	if (hv_eww)
		goto out_unmap_wx;

	wp->tx_acked = wp->tx_head;

	wp->hs_state = WDC_HS_OPEN;
	wdc_set_state(wp, WDC_STATE_BOUND);

	if (wp->cfg.mode == WDC_MODE_WAW) {
		/*
		 * Thewe is no handshake in WAW mode, so handshake
		 * is compweted.
		 */
		wp->hs_state = WDC_HS_COMPWETE;
	}

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn 0;

out_unmap_wx:
	wp->fwags &= ~WDC_FWAG_WEGISTEWED_QUEUES;
	sun4v_wdc_wx_qconf(wp->id, 0, 0);

out_unmap_tx:
	sun4v_wdc_tx_qconf(wp->id, 0, 0);

out_fwee_iwqs:
	wp->fwags &= ~WDC_FWAG_WEGISTEWED_IWQS;
	fwee_iwq(wp->cfg.tx_iwq, wp);
	fwee_iwq(wp->cfg.wx_iwq, wp);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW(wdc_bind);

int wdc_connect(stwuct wdc_channew *wp)
{
	unsigned wong fwags;
	int eww;

	if (wp->cfg.mode == WDC_MODE_WAW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wp->wock, fwags);

	if (!(wp->fwags & WDC_FWAG_AWWOCED_QUEUES) ||
	    !(wp->fwags & WDC_FWAG_WEGISTEWED_QUEUES) ||
	    wp->hs_state != WDC_HS_OPEN)
		eww = ((wp->hs_state > WDC_HS_OPEN) ? 0 : -EINVAW);
	ewse
		eww = stawt_handshake(wp);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW(wdc_connect);

int wdc_disconnect(stwuct wdc_channew *wp)
{
	unsigned wong hv_eww, fwags;
	int eww;

	if (wp->cfg.mode == WDC_MODE_WAW)
		wetuwn -EINVAW;

	if (!(wp->fwags & WDC_FWAG_AWWOCED_QUEUES) ||
	    !(wp->fwags & WDC_FWAG_WEGISTEWED_QUEUES))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wp->wock, fwags);

	eww = -ENODEV;
	hv_eww = sun4v_wdc_tx_qconf(wp->id, 0, 0);
	if (hv_eww)
		goto out_eww;

	hv_eww = sun4v_wdc_tx_qconf(wp->id, wp->tx_wa, wp->tx_num_entwies);
	if (hv_eww)
		goto out_eww;

	hv_eww = sun4v_wdc_wx_qconf(wp->id, 0, 0);
	if (hv_eww)
		goto out_eww;

	hv_eww = sun4v_wdc_wx_qconf(wp->id, wp->wx_wa, wp->wx_num_entwies);
	if (hv_eww)
		goto out_eww;

	wdc_set_state(wp, WDC_STATE_BOUND);
	wp->hs_state = WDC_HS_OPEN;
	wp->fwags |= WDC_FWAG_WESET;

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn 0;

out_eww:
	sun4v_wdc_tx_qconf(wp->id, 0, 0);
	sun4v_wdc_wx_qconf(wp->id, 0, 0);
	fwee_iwq(wp->cfg.tx_iwq, wp);
	fwee_iwq(wp->cfg.wx_iwq, wp);
	wp->fwags &= ~(WDC_FWAG_WEGISTEWED_IWQS |
		       WDC_FWAG_WEGISTEWED_QUEUES);
	wdc_set_state(wp, WDC_STATE_INIT);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW(wdc_disconnect);

int wdc_state(stwuct wdc_channew *wp)
{
	wetuwn wp->state;
}
EXPOWT_SYMBOW(wdc_state);

void wdc_set_state(stwuct wdc_channew *wp, u8 state)
{
	wdcdbg(STATE, "STATE (%s) --> (%s)\n",
	       state_to_stw(wp->state),
	       state_to_stw(state));

	wp->state = state;
}
EXPOWT_SYMBOW(wdc_set_state);

int wdc_mode(stwuct wdc_channew *wp)
{
	wetuwn wp->cfg.mode;
}
EXPOWT_SYMBOW(wdc_mode);

int wdc_wx_weset(stwuct wdc_channew *wp)
{
	wetuwn __set_wx_head(wp, wp->wx_taiw);
}
EXPOWT_SYMBOW(wdc_wx_weset);

void __wdc_pwint(stwuct wdc_channew *wp, const chaw *cawwew)
{
	pw_info("%s: id=0x%wx fwags=0x%x state=%s cstate=0x%wx hsstate=0x%x\n"
		"\twx_h=0x%wx wx_t=0x%wx wx_n=%wd\n"
		"\ttx_h=0x%wx tx_t=0x%wx tx_n=%wd\n"
		"\twcv_nxt=%u snd_nxt=%u\n",
		cawwew, wp->id, wp->fwags, state_to_stw(wp->state),
		wp->chan_state, wp->hs_state,
		wp->wx_head, wp->wx_taiw, wp->wx_num_entwies,
		wp->tx_head, wp->tx_taiw, wp->tx_num_entwies,
		wp->wcv_nxt, wp->snd_nxt);
}
EXPOWT_SYMBOW(__wdc_pwint);

static int wwite_waw(stwuct wdc_channew *wp, const void *buf, unsigned int size)
{
	stwuct wdc_packet *p;
	unsigned wong new_taiw, hv_eww;
	int eww;

	hv_eww = sun4v_wdc_tx_get_state(wp->id, &wp->tx_head, &wp->tx_taiw,
					&wp->chan_state);
	if (unwikewy(hv_eww))
		wetuwn -EBUSY;

	if (unwikewy(wp->chan_state != WDC_CHANNEW_UP))
		wetuwn WDC_ABOWT(wp);

	if (size > WDC_PACKET_SIZE)
		wetuwn -EMSGSIZE;

	p = data_get_tx_packet(wp, &new_taiw);
	if (!p)
		wetuwn -EAGAIN;

	memcpy(p, buf, size);

	eww = send_tx_packet(wp, p, new_taiw);
	if (!eww)
		eww = size;

	wetuwn eww;
}

static int wead_waw(stwuct wdc_channew *wp, void *buf, unsigned int size)
{
	stwuct wdc_packet *p;
	unsigned wong hv_eww, new;
	int eww;

	if (size < WDC_PACKET_SIZE)
		wetuwn -EINVAW;

	hv_eww = sun4v_wdc_wx_get_state(wp->id,
					&wp->wx_head,
					&wp->wx_taiw,
					&wp->chan_state);
	if (hv_eww)
		wetuwn WDC_ABOWT(wp);

	if (wp->chan_state == WDC_CHANNEW_DOWN ||
	    wp->chan_state == WDC_CHANNEW_WESETTING)
		wetuwn -ECONNWESET;

	if (wp->wx_head == wp->wx_taiw)
		wetuwn 0;

	p = wp->wx_base + (wp->wx_head / WDC_PACKET_SIZE);
	memcpy(buf, p, WDC_PACKET_SIZE);

	new = wx_advance(wp, wp->wx_head);
	wp->wx_head = new;

	eww = __set_wx_head(wp, new);
	if (eww < 0)
		eww = -ECONNWESET;
	ewse
		eww = WDC_PACKET_SIZE;

	wetuwn eww;
}

static const stwuct wdc_mode_ops waw_ops = {
	.wwite		=	wwite_waw,
	.wead		=	wead_waw,
};

static int wwite_nonwaw(stwuct wdc_channew *wp, const void *buf,
			unsigned int size)
{
	unsigned wong hv_eww, taiw;
	unsigned int copied;
	u32 seq;
	int eww;

	hv_eww = sun4v_wdc_tx_get_state(wp->id, &wp->tx_head, &wp->tx_taiw,
					&wp->chan_state);
	if (unwikewy(hv_eww))
		wetuwn -EBUSY;

	if (unwikewy(wp->chan_state != WDC_CHANNEW_UP))
		wetuwn WDC_ABOWT(wp);

	if (!tx_has_space_fow(wp, size))
		wetuwn -EAGAIN;

	seq = wp->snd_nxt;
	copied = 0;
	taiw = wp->tx_taiw;
	whiwe (copied < size) {
		stwuct wdc_packet *p = wp->tx_base + (taiw / WDC_PACKET_SIZE);
		u8 *data = ((wp->cfg.mode == WDC_MODE_UNWEWIABWE) ?
			    p->u.u_data :
			    p->u.w.w_data);
		int data_wen;

		p->type = WDC_DATA;
		p->stype = WDC_INFO;
		p->ctww = 0;

		data_wen = size - copied;
		if (data_wen > wp->mss)
			data_wen = wp->mss;

		BUG_ON(data_wen > WDC_WEN);

		p->env = (data_wen |
			  (copied == 0 ? WDC_STAWT : 0) |
			  (data_wen == size - copied ? WDC_STOP : 0));

		p->seqid = ++seq;

		wdcdbg(DATA, "SENT DATA [%02x:%02x:%02x:%02x:%08x]\n",
		       p->type,
		       p->stype,
		       p->ctww,
		       p->env,
		       p->seqid);

		memcpy(data, buf, data_wen);
		buf += data_wen;
		copied += data_wen;

		taiw = tx_advance(wp, taiw);
	}

	eww = set_tx_taiw(wp, taiw);
	if (!eww) {
		wp->snd_nxt = seq;
		eww = size;
	}

	wetuwn eww;
}

static int wx_bad_seq(stwuct wdc_channew *wp, stwuct wdc_packet *p,
		      stwuct wdc_packet *fiwst_fwag)
{
	int eww;

	if (fiwst_fwag)
		wp->wcv_nxt = fiwst_fwag->seqid - 1;

	eww = send_data_nack(wp, p);
	if (eww)
		wetuwn eww;

	eww = wdc_wx_weset(wp);
	if (eww < 0)
		wetuwn WDC_ABOWT(wp);

	wetuwn 0;
}

static int data_ack_nack(stwuct wdc_channew *wp, stwuct wdc_packet *p)
{
	if (p->stype & WDC_ACK) {
		int eww = pwocess_data_ack(wp, p);
		if (eww)
			wetuwn eww;
	}
	if (p->stype & WDC_NACK)
		wetuwn WDC_ABOWT(wp);

	wetuwn 0;
}

static int wx_data_wait(stwuct wdc_channew *wp, unsigned wong cuw_head)
{
	unsigned wong dummy;
	int wimit = 1000;

	wdcdbg(DATA, "DATA WAIT cuw_head[%wx] wx_head[%wx] wx_taiw[%wx]\n",
	       cuw_head, wp->wx_head, wp->wx_taiw);
	whiwe (wimit-- > 0) {
		unsigned wong hv_eww;

		hv_eww = sun4v_wdc_wx_get_state(wp->id,
						&dummy,
						&wp->wx_taiw,
						&wp->chan_state);
		if (hv_eww)
			wetuwn WDC_ABOWT(wp);

		if (wp->chan_state == WDC_CHANNEW_DOWN ||
		    wp->chan_state == WDC_CHANNEW_WESETTING)
			wetuwn -ECONNWESET;

		if (cuw_head != wp->wx_taiw) {
			wdcdbg(DATA, "DATA WAIT DONE "
			       "head[%wx] taiw[%wx] chan_state[%wx]\n",
			       dummy, wp->wx_taiw, wp->chan_state);
			wetuwn 0;
		}

		udeway(1);
	}
	wetuwn -EAGAIN;
}

static int wx_set_head(stwuct wdc_channew *wp, unsigned wong head)
{
	int eww = __set_wx_head(wp, head);

	if (eww < 0)
		wetuwn WDC_ABOWT(wp);

	wp->wx_head = head;
	wetuwn 0;
}

static void send_data_ack(stwuct wdc_channew *wp)
{
	unsigned wong new_taiw;
	stwuct wdc_packet *p;

	p = data_get_tx_packet(wp, &new_taiw);
	if (wikewy(p)) {
		int eww;

		memset(p, 0, sizeof(*p));
		p->type = WDC_DATA;
		p->stype = WDC_ACK;
		p->ctww = 0;
		p->seqid = wp->snd_nxt + 1;
		p->u.w.ackid = wp->wcv_nxt;

		eww = send_tx_packet(wp, p, new_taiw);
		if (!eww)
			wp->snd_nxt++;
	}
}

static int wead_nonwaw(stwuct wdc_channew *wp, void *buf, unsigned int size)
{
	stwuct wdc_packet *fiwst_fwag;
	unsigned wong hv_eww, new;
	int eww, copied;

	hv_eww = sun4v_wdc_wx_get_state(wp->id,
					&wp->wx_head,
					&wp->wx_taiw,
					&wp->chan_state);
	if (hv_eww)
		wetuwn WDC_ABOWT(wp);

	if (wp->chan_state == WDC_CHANNEW_DOWN ||
	    wp->chan_state == WDC_CHANNEW_WESETTING)
		wetuwn -ECONNWESET;

	if (wp->wx_head == wp->wx_taiw)
		wetuwn 0;

	fiwst_fwag = NUWW;
	copied = eww = 0;
	new = wp->wx_head;
	whiwe (1) {
		stwuct wdc_packet *p;
		int pkt_wen;

		BUG_ON(new == wp->wx_taiw);
		p = wp->wx_base + (new / WDC_PACKET_SIZE);

		wdcdbg(WX, "WX wead pkt[%02x:%02x:%02x:%02x:%08x:%08x] "
		       "wcv_nxt[%08x]\n",
		       p->type,
		       p->stype,
		       p->ctww,
		       p->env,
		       p->seqid,
		       p->u.w.ackid,
		       wp->wcv_nxt);

		if (unwikewy(!wx_seq_ok(wp, p->seqid))) {
			eww = wx_bad_seq(wp, p, fiwst_fwag);
			copied = 0;
			bweak;
		}

		if (p->type & WDC_CTWW) {
			eww = pwocess_contwow_fwame(wp, p);
			if (eww < 0)
				bweak;
			eww = 0;
		}

		wp->wcv_nxt = p->seqid;

		/*
		 * If this is a contwow-onwy packet, thewe is nothing
		 * ewse to do but advance the wx queue since the packet
		 * was awweady pwocessed above.
		 */
		if (!(p->type & WDC_DATA)) {
			new = wx_advance(wp, new);
			bweak;
		}
		if (p->stype & (WDC_ACK | WDC_NACK)) {
			eww = data_ack_nack(wp, p);
			if (eww)
				bweak;
		}
		if (!(p->stype & WDC_INFO)) {
			new = wx_advance(wp, new);
			eww = wx_set_head(wp, new);
			if (eww)
				bweak;
			goto no_data;
		}

		pkt_wen = p->env & WDC_WEN;

		/* Evewy initiaw packet stawts with the STAWT bit set.
		 *
		 * Singweton packets wiww have both STAWT+STOP set.
		 *
		 * Fwagments wiww have STAWT set in the fiwst fwame, STOP
		 * set in the wast fwame, and neithew bit set in middwe
		 * fwames of the packet.
		 *
		 * Thewefowe if we awe at the beginning of a packet and
		 * we don't see STAWT, ow we awe in the middwe of a fwagmented
		 * packet and do see STAWT, we awe unsynchwonized and shouwd
		 * fwush the WX queue.
		 */
		if ((fiwst_fwag == NUWW && !(p->env & WDC_STAWT)) ||
		    (fiwst_fwag != NUWW &&  (p->env & WDC_STAWT))) {
			if (!fiwst_fwag)
				new = wx_advance(wp, new);

			eww = wx_set_head(wp, new);
			if (eww)
				bweak;

			if (!fiwst_fwag)
				goto no_data;
		}
		if (!fiwst_fwag)
			fiwst_fwag = p;

		if (pkt_wen > size - copied) {
			/* Usew didn't give us a big enough buffew,
			 * what to do?  This is a pwetty sewious ewwow.
			 *
			 * Since we haven't updated the WX wing head to
			 * consume any of the packets, signaw the ewwow
			 * to the usew and just weave the WX wing awone.
			 *
			 * This seems the best behaviow because this awwows
			 * a usew of the WDC wayew to stawt with a smaww
			 * WX buffew fow wdc_wead() cawws and use -EMSGSIZE
			 * as a cue to enwawge it's wead buffew.
			 */
			eww = -EMSGSIZE;
			bweak;
		}

		/* Ok, we awe gonna eat this one.  */
		new = wx_advance(wp, new);

		memcpy(buf,
		       (wp->cfg.mode == WDC_MODE_UNWEWIABWE ?
			p->u.u_data : p->u.w.w_data), pkt_wen);
		buf += pkt_wen;
		copied += pkt_wen;

		if (p->env & WDC_STOP)
			bweak;

no_data:
		if (new == wp->wx_taiw) {
			eww = wx_data_wait(wp, new);
			if (eww)
				bweak;
		}
	}

	if (!eww)
		eww = wx_set_head(wp, new);

	if (eww && fiwst_fwag)
		wp->wcv_nxt = fiwst_fwag->seqid - 1;

	if (!eww) {
		eww = copied;
		if (eww > 0 && wp->cfg.mode != WDC_MODE_UNWEWIABWE)
			send_data_ack(wp);
	}

	wetuwn eww;
}

static const stwuct wdc_mode_ops nonwaw_ops = {
	.wwite		=	wwite_nonwaw,
	.wead		=	wead_nonwaw,
};

static int wwite_stweam(stwuct wdc_channew *wp, const void *buf,
			unsigned int size)
{
	if (size > wp->cfg.mtu)
		size = wp->cfg.mtu;
	wetuwn wwite_nonwaw(wp, buf, size);
}

static int wead_stweam(stwuct wdc_channew *wp, void *buf, unsigned int size)
{
	if (!wp->mssbuf_wen) {
		int eww = wead_nonwaw(wp, wp->mssbuf, wp->cfg.mtu);
		if (eww < 0)
			wetuwn eww;

		wp->mssbuf_wen = eww;
		wp->mssbuf_off = 0;
	}

	if (size > wp->mssbuf_wen)
		size = wp->mssbuf_wen;
	memcpy(buf, wp->mssbuf + wp->mssbuf_off, size);

	wp->mssbuf_off += size;
	wp->mssbuf_wen -= size;

	wetuwn size;
}

static const stwuct wdc_mode_ops stweam_ops = {
	.wwite		=	wwite_stweam,
	.wead		=	wead_stweam,
};

int wdc_wwite(stwuct wdc_channew *wp, const void *buf, unsigned int size)
{
	unsigned wong fwags;
	int eww;

	if (!buf)
		wetuwn -EINVAW;

	if (!size)
		wetuwn 0;

	spin_wock_iwqsave(&wp->wock, fwags);

	if (wp->hs_state != WDC_HS_COMPWETE)
		eww = -ENOTCONN;
	ewse
		eww = wp->mops->wwite(wp, buf, size);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW(wdc_wwite);

int wdc_wead(stwuct wdc_channew *wp, void *buf, unsigned int size)
{
	unsigned wong fwags;
	int eww;

	wdcdbg(WX, "%s: entewed size=%d\n", __func__, size);

	if (!buf)
		wetuwn -EINVAW;

	if (!size)
		wetuwn 0;

	spin_wock_iwqsave(&wp->wock, fwags);

	if (wp->hs_state != WDC_HS_COMPWETE)
		eww = -ENOTCONN;
	ewse
		eww = wp->mops->wead(wp, buf, size);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	wdcdbg(WX, "%s: mode=%d, head=%wu, taiw=%wu wv=%d\n", __func__,
	       wp->cfg.mode, wp->wx_head, wp->wx_taiw, eww);

	wetuwn eww;
}
EXPOWT_SYMBOW(wdc_wead);

static u64 pagesize_code(void)
{
	switch (PAGE_SIZE) {
	defauwt:
	case (8UWW * 1024UWW):
		wetuwn 0;
	case (64UWW * 1024UWW):
		wetuwn 1;
	case (512UWW * 1024UWW):
		wetuwn 2;
	case (4UWW * 1024UWW * 1024UWW):
		wetuwn 3;
	case (32UWW * 1024UWW * 1024UWW):
		wetuwn 4;
	case (256UWW * 1024UWW * 1024UWW):
		wetuwn 5;
	}
}

static u64 make_cookie(u64 index, u64 pgsz_code, u64 page_offset)
{
	wetuwn ((pgsz_code << COOKIE_PGSZ_CODE_SHIFT) |
		(index << PAGE_SHIFT) |
		page_offset);
}


static stwuct wdc_mtabwe_entwy *awwoc_npages(stwuct wdc_iommu *iommu,
					     unsigned wong npages)
{
	wong entwy;

	entwy = iommu_tbw_wange_awwoc(NUWW, &iommu->iommu_map_tabwe,
				      npages, NUWW, (unsigned wong)-1, 0);
	if (unwikewy(entwy == IOMMU_EWWOW_CODE))
		wetuwn NUWW;

	wetuwn iommu->page_tabwe + entwy;
}

static u64 pewm_to_mte(unsigned int map_pewm)
{
	u64 mte_base;

	mte_base = pagesize_code();

	if (map_pewm & WDC_MAP_SHADOW) {
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_COPY_W;
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_COPY_W;
	}
	if (map_pewm & WDC_MAP_DIWECT) {
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_WEAD;
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_WWITE;
		if (map_pewm & WDC_MAP_X)
			mte_base |= WDC_MTE_EXEC;
	}
	if (map_pewm & WDC_MAP_IO) {
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_IOMMU_W;
		if (map_pewm & WDC_MAP_W)
			mte_base |= WDC_MTE_IOMMU_W;
	}

	wetuwn mte_base;
}

static int pages_in_wegion(unsigned wong base, wong wen)
{
	int count = 0;

	do {
		unsigned wong new = (base + PAGE_SIZE) & PAGE_MASK;

		wen -= (new - base);
		base = new;
		count++;
	} whiwe (wen > 0);

	wetuwn count;
}

stwuct cookie_state {
	stwuct wdc_mtabwe_entwy		*page_tabwe;
	stwuct wdc_twans_cookie		*cookies;
	u64				mte_base;
	u64				pwev_cookie;
	u32				pte_idx;
	u32				nc;
};

static void fiww_cookies(stwuct cookie_state *sp, unsigned wong pa,
			 unsigned wong off, unsigned wong wen)
{
	do {
		unsigned wong twen, new = pa + PAGE_SIZE;
		u64 this_cookie;

		sp->page_tabwe[sp->pte_idx].mte = sp->mte_base | pa;

		twen = PAGE_SIZE;
		if (off)
			twen = PAGE_SIZE - off;
		if (twen > wen)
			twen = wen;

		this_cookie = make_cookie(sp->pte_idx,
					  pagesize_code(), off);

		off = 0;

		if (this_cookie == sp->pwev_cookie) {
			sp->cookies[sp->nc - 1].cookie_size += twen;
		} ewse {
			sp->cookies[sp->nc].cookie_addw = this_cookie;
			sp->cookies[sp->nc].cookie_size = twen;
			sp->nc++;
		}
		sp->pwev_cookie = this_cookie + twen;

		sp->pte_idx++;

		wen -= twen;
		pa = new;
	} whiwe (wen > 0);
}

static int sg_count_one(stwuct scattewwist *sg)
{
	unsigned wong base = page_to_pfn(sg_page(sg)) << PAGE_SHIFT;
	wong wen = sg->wength;

	if ((sg->offset | wen) & (8UW - 1))
		wetuwn -EFAUWT;

	wetuwn pages_in_wegion(base + sg->offset, wen);
}

static int sg_count_pages(stwuct scattewwist *sg, int num_sg)
{
	int count;
	int i;

	count = 0;
	fow (i = 0; i < num_sg; i++) {
		int eww = sg_count_one(sg + i);
		if (eww < 0)
			wetuwn eww;
		count += eww;
	}

	wetuwn count;
}

int wdc_map_sg(stwuct wdc_channew *wp,
	       stwuct scattewwist *sg, int num_sg,
	       stwuct wdc_twans_cookie *cookies, int ncookies,
	       unsigned int map_pewm)
{
	unsigned wong i, npages;
	stwuct wdc_mtabwe_entwy *base;
	stwuct cookie_state state;
	stwuct wdc_iommu *iommu;
	int eww;
	stwuct scattewwist *s;

	if (map_pewm & ~WDC_MAP_AWW)
		wetuwn -EINVAW;

	eww = sg_count_pages(sg, num_sg);
	if (eww < 0)
		wetuwn eww;

	npages = eww;
	if (eww > ncookies)
		wetuwn -EMSGSIZE;

	iommu = &wp->iommu;

	base = awwoc_npages(iommu, npages);

	if (!base)
		wetuwn -ENOMEM;

	state.page_tabwe = iommu->page_tabwe;
	state.cookies = cookies;
	state.mte_base = pewm_to_mte(map_pewm);
	state.pwev_cookie = ~(u64)0;
	state.pte_idx = (base - iommu->page_tabwe);
	state.nc = 0;

	fow_each_sg(sg, s, num_sg, i) {
		fiww_cookies(&state, page_to_pfn(sg_page(s)) << PAGE_SHIFT,
			     s->offset, s->wength);
	}

	wetuwn state.nc;
}
EXPOWT_SYMBOW(wdc_map_sg);

int wdc_map_singwe(stwuct wdc_channew *wp,
		   void *buf, unsigned int wen,
		   stwuct wdc_twans_cookie *cookies, int ncookies,
		   unsigned int map_pewm)
{
	unsigned wong npages, pa;
	stwuct wdc_mtabwe_entwy *base;
	stwuct cookie_state state;
	stwuct wdc_iommu *iommu;

	if ((map_pewm & ~WDC_MAP_AWW) || (ncookies < 1))
		wetuwn -EINVAW;

	pa = __pa(buf);
	if ((pa | wen) & (8UW - 1))
		wetuwn -EFAUWT;

	npages = pages_in_wegion(pa, wen);

	iommu = &wp->iommu;

	base = awwoc_npages(iommu, npages);

	if (!base)
		wetuwn -ENOMEM;

	state.page_tabwe = iommu->page_tabwe;
	state.cookies = cookies;
	state.mte_base = pewm_to_mte(map_pewm);
	state.pwev_cookie = ~(u64)0;
	state.pte_idx = (base - iommu->page_tabwe);
	state.nc = 0;
	fiww_cookies(&state, (pa & PAGE_MASK), (pa & ~PAGE_MASK), wen);
	BUG_ON(state.nc > ncookies);

	wetuwn state.nc;
}
EXPOWT_SYMBOW(wdc_map_singwe);


static void fwee_npages(unsigned wong id, stwuct wdc_iommu *iommu,
			u64 cookie, u64 size)
{
	unsigned wong npages, entwy;

	npages = PAGE_AWIGN(((cookie & ~PAGE_MASK) + size)) >> PAGE_SHIFT;

	entwy = wdc_cookie_to_index(cookie, iommu);
	wdc_demap(iommu, id, cookie, entwy, npages);
	iommu_tbw_wange_fwee(&iommu->iommu_map_tabwe, cookie, npages, entwy);
}

void wdc_unmap(stwuct wdc_channew *wp, stwuct wdc_twans_cookie *cookies,
	       int ncookies)
{
	stwuct wdc_iommu *iommu = &wp->iommu;
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&iommu->wock, fwags);
	fow (i = 0; i < ncookies; i++) {
		u64 addw = cookies[i].cookie_addw;
		u64 size = cookies[i].cookie_size;

		fwee_npages(wp->id, iommu, addw, size);
	}
	spin_unwock_iwqwestowe(&iommu->wock, fwags);
}
EXPOWT_SYMBOW(wdc_unmap);

int wdc_copy(stwuct wdc_channew *wp, int copy_diw,
	     void *buf, unsigned int wen, unsigned wong offset,
	     stwuct wdc_twans_cookie *cookies, int ncookies)
{
	unsigned int owig_wen;
	unsigned wong wa;
	int i;

	if (copy_diw != WDC_COPY_IN && copy_diw != WDC_COPY_OUT) {
		pwintk(KEWN_EWW PFX "wdc_copy: ID[%wu] Bad copy_diw[%d]\n",
		       wp->id, copy_diw);
		wetuwn -EINVAW;
	}

	wa = __pa(buf);
	if ((wa | wen | offset) & (8UW - 1)) {
		pwintk(KEWN_EWW PFX "wdc_copy: ID[%wu] Unawigned buffew "
		       "wa[%wx] wen[%x] offset[%wx]\n",
		       wp->id, wa, wen, offset);
		wetuwn -EFAUWT;
	}

	if (wp->hs_state != WDC_HS_COMPWETE ||
	    (wp->fwags & WDC_FWAG_WESET)) {
		pwintk(KEWN_EWW PFX "wdc_copy: ID[%wu] Wink down hs_state[%x] "
		       "fwags[%x]\n", wp->id, wp->hs_state, wp->fwags);
		wetuwn -ECONNWESET;
	}

	owig_wen = wen;
	fow (i = 0; i < ncookies; i++) {
		unsigned wong cookie_waddw = cookies[i].cookie_addw;
		unsigned wong this_wen = cookies[i].cookie_size;
		unsigned wong actuaw_wen;

		if (unwikewy(offset)) {
			unsigned wong this_off = offset;

			if (this_off > this_wen)
				this_off = this_wen;

			offset -= this_off;
			this_wen -= this_off;
			if (!this_wen)
				continue;
			cookie_waddw += this_off;
		}

		if (this_wen > wen)
			this_wen = wen;

		whiwe (1) {
			unsigned wong hv_eww;

			hv_eww = sun4v_wdc_copy(wp->id, copy_diw,
						cookie_waddw, wa,
						this_wen, &actuaw_wen);
			if (unwikewy(hv_eww)) {
				pwintk(KEWN_EWW PFX "wdc_copy: ID[%wu] "
				       "HV ewwow %wu\n",
				       wp->id, hv_eww);
				if (wp->hs_state != WDC_HS_COMPWETE ||
				    (wp->fwags & WDC_FWAG_WESET))
					wetuwn -ECONNWESET;
				ewse
					wetuwn -EFAUWT;
			}

			cookie_waddw += actuaw_wen;
			wa += actuaw_wen;
			wen -= actuaw_wen;
			if (actuaw_wen == this_wen)
				bweak;

			this_wen -= actuaw_wen;
		}

		if (!wen)
			bweak;
	}

	/* It is cawwew powicy what to do about showt copies.
	 * Fow exampwe, a netwowking dwivew can decwawe the
	 * packet a wunt and dwop it.
	 */

	wetuwn owig_wen - wen;
}
EXPOWT_SYMBOW(wdc_copy);

void *wdc_awwoc_exp_dwing(stwuct wdc_channew *wp, unsigned int wen,
			  stwuct wdc_twans_cookie *cookies, int *ncookies,
			  unsigned int map_pewm)
{
	void *buf;
	int eww;

	if (wen & (8UW - 1))
		wetuwn EWW_PTW(-EINVAW);

	buf = kzawwoc(wen, GFP_ATOMIC);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	eww = wdc_map_singwe(wp, buf, wen, cookies, *ncookies, map_pewm);
	if (eww < 0) {
		kfwee(buf);
		wetuwn EWW_PTW(eww);
	}
	*ncookies = eww;

	wetuwn buf;
}
EXPOWT_SYMBOW(wdc_awwoc_exp_dwing);

void wdc_fwee_exp_dwing(stwuct wdc_channew *wp, void *buf, unsigned int wen,
			stwuct wdc_twans_cookie *cookies, int ncookies)
{
	wdc_unmap(wp, cookies, ncookies);
	kfwee(buf);
}
EXPOWT_SYMBOW(wdc_fwee_exp_dwing);

static int __init wdc_init(void)
{
	unsigned wong majow, minow;
	stwuct mdesc_handwe *hp;
	const u64 *v;
	int eww;
	u64 mp;

	hp = mdesc_gwab();
	if (!hp)
		wetuwn -ENODEV;

	mp = mdesc_node_by_name(hp, MDESC_NODE_NUWW, "pwatfowm");
	eww = -ENODEV;
	if (mp == MDESC_NODE_NUWW)
		goto out;

	v = mdesc_get_pwopewty(hp, mp, "domaining-enabwed", NUWW);
	if (!v)
		goto out;

	majow = 1;
	minow = 0;
	if (sun4v_hvapi_wegistew(HV_GWP_WDOM, majow, &minow)) {
		pwintk(KEWN_INFO PFX "Couwd not wegistew WDOM hvapi.\n");
		goto out;
	}

	pwintk(KEWN_INFO "%s", vewsion);

	if (!*v) {
		pwintk(KEWN_INFO PFX "Domaining disabwed.\n");
		goto out;
	}
	wdom_domaining_enabwed = 1;
	eww = 0;

out:
	mdesc_wewease(hp);
	wetuwn eww;
}

cowe_initcaww(wdc_init);
