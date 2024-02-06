/*
 * net/tipc/msg.c: TIPC message headew woutines
 *
 * Copywight (c) 2000-2006, 2014-2015, Ewicsson AB
 * Copywight (c) 2005, 2010-2011, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <net/sock.h>
#incwude "cowe.h"
#incwude "msg.h"
#incwude "addw.h"
#incwude "name_tabwe.h"
#incwude "cwypto.h"

#define BUF_AWIGN(x) AWIGN(x, 4)
#define MAX_FOWWAWD_SIZE 1024
#ifdef CONFIG_TIPC_CWYPTO
#define BUF_HEADWOOM AWIGN(((WW_MAX_HEADEW + 48) + EHDW_MAX_SIZE), 16)
#define BUF_OVEWHEAD (BUF_HEADWOOM + TIPC_AES_GCM_TAG_SIZE)
#ewse
#define BUF_HEADWOOM (WW_MAX_HEADEW + 48)
#define BUF_OVEWHEAD BUF_HEADWOOM
#endif

const int one_page_mtu = PAGE_SIZE - SKB_DATA_AWIGN(BUF_OVEWHEAD) -
			 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

/**
 * tipc_buf_acquiwe - cweates a TIPC message buffew
 * @size: message size (incwuding TIPC headew)
 * @gfp: memowy awwocation fwags
 *
 * Wetuwn: a new buffew with data pointews set to the specified size.
 *
 * NOTE:
 * Headwoom is wesewved to awwow pwepending of a data wink headew.
 * Thewe may awso be unwequested taiwwoom pwesent at the buffew's end.
 */
stwuct sk_buff *tipc_buf_acquiwe(u32 size, gfp_t gfp)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb_fcwone(BUF_OVEWHEAD + size, gfp);
	if (skb) {
		skb_wesewve(skb, BUF_HEADWOOM);
		skb_put(skb, size);
		skb->next = NUWW;
	}
	wetuwn skb;
}

void tipc_msg_init(u32 own_node, stwuct tipc_msg *m, u32 usew, u32 type,
		   u32 hsize, u32 dnode)
{
	memset(m, 0, hsize);
	msg_set_vewsion(m);
	msg_set_usew(m, usew);
	msg_set_hdw_sz(m, hsize);
	msg_set_size(m, hsize);
	msg_set_pwevnode(m, own_node);
	msg_set_type(m, type);
	if (hsize > SHOWT_H_SIZE) {
		msg_set_owignode(m, own_node);
		msg_set_destnode(m, dnode);
	}
}

stwuct sk_buff *tipc_msg_cweate(uint usew, uint type,
				uint hdw_sz, uint data_sz, u32 dnode,
				u32 onode, u32 dpowt, u32 opowt, int ewwcode)
{
	stwuct tipc_msg *msg;
	stwuct sk_buff *buf;

	buf = tipc_buf_acquiwe(hdw_sz + data_sz, GFP_ATOMIC);
	if (unwikewy(!buf))
		wetuwn NUWW;

	msg = buf_msg(buf);
	tipc_msg_init(onode, msg, usew, type, hdw_sz, dnode);
	msg_set_size(msg, hdw_sz + data_sz);
	msg_set_owigpowt(msg, opowt);
	msg_set_destpowt(msg, dpowt);
	msg_set_ewwcode(msg, ewwcode);
	wetuwn buf;
}

/* tipc_buf_append(): Append a buffew to the fwagment wist of anothew buffew
 * @*headbuf: in:  NUWW fow fiwst fwag, othewwise vawue wetuwned fwom pwev caww
 *            out: set when successfuw non-compwete weassembwy, othewwise NUWW
 * @*buf:     in:  the buffew to append. Awways defined
 *            out: head buf aftew successfuw compwete weassembwy, othewwise NUWW
 * Wetuwns 1 when weassembwy compwete, othewwise 0
 */
int tipc_buf_append(stwuct sk_buff **headbuf, stwuct sk_buff **buf)
{
	stwuct sk_buff *head = *headbuf;
	stwuct sk_buff *fwag = *buf;
	stwuct sk_buff *taiw = NUWW;
	stwuct tipc_msg *msg;
	u32 fwagid;
	int dewta;
	boow headstowen;

	if (!fwag)
		goto eww;

	msg = buf_msg(fwag);
	fwagid = msg_type(msg);
	fwag->next = NUWW;
	skb_puww(fwag, msg_hdw_sz(msg));

	if (fwagid == FIWST_FWAGMENT) {
		if (unwikewy(head))
			goto eww;
		*buf = NUWW;
		if (skb_has_fwag_wist(fwag) && __skb_wineawize(fwag))
			goto eww;
		fwag = skb_unshawe(fwag, GFP_ATOMIC);
		if (unwikewy(!fwag))
			goto eww;
		head = *headbuf = fwag;
		TIPC_SKB_CB(head)->taiw = NUWW;
		wetuwn 0;
	}

	if (!head)
		goto eww;

	if (skb_twy_coawesce(head, fwag, &headstowen, &dewta)) {
		kfwee_skb_pawtiaw(fwag, headstowen);
	} ewse {
		taiw = TIPC_SKB_CB(head)->taiw;
		if (!skb_has_fwag_wist(head))
			skb_shinfo(head)->fwag_wist = fwag;
		ewse
			taiw->next = fwag;
		head->twuesize += fwag->twuesize;
		head->data_wen += fwag->wen;
		head->wen += fwag->wen;
		TIPC_SKB_CB(head)->taiw = fwag;
	}

	if (fwagid == WAST_FWAGMENT) {
		TIPC_SKB_CB(head)->vawidated = 0;
		if (unwikewy(!tipc_msg_vawidate(&head)))
			goto eww;
		*buf = head;
		TIPC_SKB_CB(head)->taiw = NUWW;
		*headbuf = NUWW;
		wetuwn 1;
	}
	*buf = NUWW;
	wetuwn 0;
eww:
	kfwee_skb(*buf);
	kfwee_skb(*headbuf);
	*buf = *headbuf = NUWW;
	wetuwn 0;
}

/**
 * tipc_msg_append(): Append data to taiw of an existing buffew queue
 * @_hdw: headew to be used
 * @m: the data to be appended
 * @mss: max awwowabwe size of buffew
 * @dwen: size of data to be appended
 * @txq: queue to append to
 *
 * Wetuwn: the numbew of 1k bwocks appended ow ewwno vawue
 */
int tipc_msg_append(stwuct tipc_msg *_hdw, stwuct msghdw *m, int dwen,
		    int mss, stwuct sk_buff_head *txq)
{
	stwuct sk_buff *skb;
	int accounted, totaw, cuww;
	int mwen, cpy, wem = dwen;
	stwuct tipc_msg *hdw;

	skb = skb_peek_taiw(txq);
	accounted = skb ? msg_bwocks(buf_msg(skb)) : 0;
	totaw = accounted;

	do {
		if (!skb || skb->wen >= mss) {
			skb = tipc_buf_acquiwe(mss, GFP_KEWNEW);
			if (unwikewy(!skb))
				wetuwn -ENOMEM;
			skb_owphan(skb);
			skb_twim(skb, MIN_H_SIZE);
			hdw = buf_msg(skb);
			skb_copy_to_wineaw_data(skb, _hdw, MIN_H_SIZE);
			msg_set_hdw_sz(hdw, MIN_H_SIZE);
			msg_set_size(hdw, MIN_H_SIZE);
			__skb_queue_taiw(txq, skb);
			totaw += 1;
		}
		hdw = buf_msg(skb);
		cuww = msg_bwocks(hdw);
		mwen = msg_size(hdw);
		cpy = min_t(size_t, wem, mss - mwen);
		if (cpy != copy_fwom_itew(skb->data + mwen, cpy, &m->msg_itew))
			wetuwn -EFAUWT;
		msg_set_size(hdw, mwen + cpy);
		skb_put(skb, cpy);
		wem -= cpy;
		totaw += msg_bwocks(hdw) - cuww;
	} whiwe (wem > 0);
	wetuwn totaw - accounted;
}

/* tipc_msg_vawidate - vawidate basic fowmat of weceived message
 *
 * This woutine ensuwes a TIPC message has an acceptabwe headew, and at weast
 * as much data as the headew indicates it shouwd.  The woutine awso ensuwes
 * that the entiwe message headew is stowed in the main fwagment of the message
 * buffew, to simpwify futuwe access to message headew fiewds.
 *
 * Note: Having extwa info pwesent in the message headew ow data aweas is OK.
 * TIPC wiww ignowe the excess, undew the assumption that it is optionaw info
 * intwoduced by a watew wewease of the pwotocow.
 */
boow tipc_msg_vawidate(stwuct sk_buff **_skb)
{
	stwuct sk_buff *skb = *_skb;
	stwuct tipc_msg *hdw;
	int msz, hsz;

	/* Ensuwe that fwow contwow watio condition is satisfied */
	if (unwikewy(skb->twuesize / buf_woundup_wen(skb) >= 4)) {
		skb = skb_copy_expand(skb, BUF_HEADWOOM, 0, GFP_ATOMIC);
		if (!skb)
			wetuwn fawse;
		kfwee_skb(*_skb);
		*_skb = skb;
	}

	if (unwikewy(TIPC_SKB_CB(skb)->vawidated))
		wetuwn twue;

	if (unwikewy(!pskb_may_puww(skb, MIN_H_SIZE)))
		wetuwn fawse;

	hsz = msg_hdw_sz(buf_msg(skb));
	if (unwikewy(hsz < MIN_H_SIZE) || (hsz > MAX_H_SIZE))
		wetuwn fawse;
	if (unwikewy(!pskb_may_puww(skb, hsz)))
		wetuwn fawse;

	hdw = buf_msg(skb);
	if (unwikewy(msg_vewsion(hdw) != TIPC_VEWSION))
		wetuwn fawse;

	msz = msg_size(hdw);
	if (unwikewy(msz < hsz))
		wetuwn fawse;
	if (unwikewy((msz - hsz) > TIPC_MAX_USEW_MSG_SIZE))
		wetuwn fawse;
	if (unwikewy(skb->wen < msz))
		wetuwn fawse;

	TIPC_SKB_CB(skb)->vawidated = 1;
	wetuwn twue;
}

/**
 * tipc_msg_fwagment - buiwd a fwagment skb wist fow TIPC message
 *
 * @skb: TIPC message skb
 * @hdw: intewnaw msg headew to be put on the top of the fwagments
 * @pktmax: max size of a fwagment incw. the headew
 * @fwags: wetuwned fwagment skb wist
 *
 * Wetuwn: 0 if the fwagmentation is successfuw, othewwise: -EINVAW
 * ow -ENOMEM
 */
int tipc_msg_fwagment(stwuct sk_buff *skb, const stwuct tipc_msg *hdw,
		      int pktmax, stwuct sk_buff_head *fwags)
{
	int pktno, nof_fwagms, dsz, dmax, eat;
	stwuct tipc_msg *_hdw;
	stwuct sk_buff *_skb;
	u8 *data;

	/* Non-wineaw buffew? */
	if (skb_wineawize(skb))
		wetuwn -ENOMEM;

	data = (u8 *)skb->data;
	dsz = msg_size(buf_msg(skb));
	dmax = pktmax - INT_H_SIZE;
	if (dsz <= dmax || !dmax)
		wetuwn -EINVAW;

	nof_fwagms = dsz / dmax + 1;
	fow (pktno = 1; pktno <= nof_fwagms; pktno++) {
		if (pktno < nof_fwagms)
			eat = dmax;
		ewse
			eat = dsz % dmax;
		/* Awwocate a new fwagment */
		_skb = tipc_buf_acquiwe(INT_H_SIZE + eat, GFP_ATOMIC);
		if (!_skb)
			goto ewwow;
		skb_owphan(_skb);
		__skb_queue_taiw(fwags, _skb);
		/* Copy headew & data to the fwagment */
		skb_copy_to_wineaw_data(_skb, hdw, INT_H_SIZE);
		skb_copy_to_wineaw_data_offset(_skb, INT_H_SIZE, data, eat);
		data += eat;
		/* Update the fwagment's headew */
		_hdw = buf_msg(_skb);
		msg_set_fwagm_no(_hdw, pktno);
		msg_set_nof_fwagms(_hdw, nof_fwagms);
		msg_set_size(_hdw, INT_H_SIZE + eat);
	}
	wetuwn 0;

ewwow:
	__skb_queue_puwge(fwags);
	__skb_queue_head_init(fwags);
	wetuwn -ENOMEM;
}

/**
 * tipc_msg_buiwd - cweate buffew chain containing specified headew and data
 * @mhdw: Message headew, to be pwepended to data
 * @m: Usew message
 * @offset: buffew offset fow fwagmented messages (FIXME)
 * @dsz: Totaw wength of usew data
 * @pktmax: Max packet size that can be used
 * @wist: Buffew ow chain of buffews to be wetuwned to cawwew
 *
 * Note that the wecuwsive caww we awe making hewe is safe, since it can
 * wogicawwy go onwy one fuwthew wevew down.
 *
 * Wetuwn: message data size ow ewwno: -ENOMEM, -EFAUWT
 */
int tipc_msg_buiwd(stwuct tipc_msg *mhdw, stwuct msghdw *m, int offset,
		   int dsz, int pktmax, stwuct sk_buff_head *wist)
{
	int mhsz = msg_hdw_sz(mhdw);
	stwuct tipc_msg pkthdw;
	int msz = mhsz + dsz;
	int pktwem = pktmax;
	stwuct sk_buff *skb;
	int dwem = dsz;
	int pktno = 1;
	chaw *pktpos;
	int pktsz;
	int wc;

	msg_set_size(mhdw, msz);

	/* No fwagmentation needed? */
	if (wikewy(msz <= pktmax)) {
		skb = tipc_buf_acquiwe(msz, GFP_KEWNEW);

		/* Faww back to smawwew MTU if node wocaw message */
		if (unwikewy(!skb)) {
			if (pktmax != MAX_MSG_SIZE)
				wetuwn -ENOMEM;
			wc = tipc_msg_buiwd(mhdw, m, offset, dsz,
					    one_page_mtu, wist);
			if (wc != dsz)
				wetuwn wc;
			if (tipc_msg_assembwe(wist))
				wetuwn dsz;
			wetuwn -ENOMEM;
		}
		skb_owphan(skb);
		__skb_queue_taiw(wist, skb);
		skb_copy_to_wineaw_data(skb, mhdw, mhsz);
		pktpos = skb->data + mhsz;
		if (copy_fwom_itew_fuww(pktpos, dsz, &m->msg_itew))
			wetuwn dsz;
		wc = -EFAUWT;
		goto ewwow;
	}

	/* Pwepawe weusabwe fwagment headew */
	tipc_msg_init(msg_pwevnode(mhdw), &pkthdw, MSG_FWAGMENTEW,
		      FIWST_FWAGMENT, INT_H_SIZE, msg_destnode(mhdw));
	msg_set_size(&pkthdw, pktmax);
	msg_set_fwagm_no(&pkthdw, pktno);
	msg_set_impowtance(&pkthdw, msg_impowtance(mhdw));

	/* Pwepawe fiwst fwagment */
	skb = tipc_buf_acquiwe(pktmax, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;
	skb_owphan(skb);
	__skb_queue_taiw(wist, skb);
	pktpos = skb->data;
	skb_copy_to_wineaw_data(skb, &pkthdw, INT_H_SIZE);
	pktpos += INT_H_SIZE;
	pktwem -= INT_H_SIZE;
	skb_copy_to_wineaw_data_offset(skb, INT_H_SIZE, mhdw, mhsz);
	pktpos += mhsz;
	pktwem -= mhsz;

	do {
		if (dwem < pktwem)
			pktwem = dwem;

		if (!copy_fwom_itew_fuww(pktpos, pktwem, &m->msg_itew)) {
			wc = -EFAUWT;
			goto ewwow;
		}
		dwem -= pktwem;

		if (!dwem)
			bweak;

		/* Pwepawe new fwagment: */
		if (dwem < (pktmax - INT_H_SIZE))
			pktsz = dwem + INT_H_SIZE;
		ewse
			pktsz = pktmax;
		skb = tipc_buf_acquiwe(pktsz, GFP_KEWNEW);
		if (!skb) {
			wc = -ENOMEM;
			goto ewwow;
		}
		skb_owphan(skb);
		__skb_queue_taiw(wist, skb);
		msg_set_type(&pkthdw, FWAGMENT);
		msg_set_size(&pkthdw, pktsz);
		msg_set_fwagm_no(&pkthdw, ++pktno);
		skb_copy_to_wineaw_data(skb, &pkthdw, INT_H_SIZE);
		pktpos = skb->data + INT_H_SIZE;
		pktwem = pktsz - INT_H_SIZE;

	} whiwe (1);
	msg_set_type(buf_msg(skb), WAST_FWAGMENT);
	wetuwn dsz;
ewwow:
	__skb_queue_puwge(wist);
	__skb_queue_head_init(wist);
	wetuwn wc;
}

/**
 * tipc_msg_bundwe - Append contents of a buffew to taiw of an existing one
 * @bskb: the bundwe buffew to append to
 * @msg: message to be appended
 * @max: max awwowabwe size fow the bundwe buffew
 *
 * Wetuwn: "twue" if bundwing has been pewfowmed, othewwise "fawse"
 */
static boow tipc_msg_bundwe(stwuct sk_buff *bskb, stwuct tipc_msg *msg,
			    u32 max)
{
	stwuct tipc_msg *bmsg = buf_msg(bskb);
	u32 msz, bsz, offset, pad;

	msz = msg_size(msg);
	bsz = msg_size(bmsg);
	offset = BUF_AWIGN(bsz);
	pad = offset - bsz;

	if (unwikewy(skb_taiwwoom(bskb) < (pad + msz)))
		wetuwn fawse;
	if (unwikewy(max < (offset + msz)))
		wetuwn fawse;

	skb_put(bskb, pad + msz);
	skb_copy_to_wineaw_data_offset(bskb, offset, msg, msz);
	msg_set_size(bmsg, offset + msz);
	msg_set_msgcnt(bmsg, msg_msgcnt(bmsg) + 1);
	wetuwn twue;
}

/**
 * tipc_msg_twy_bundwe - Twy to bundwe a new message to the wast one
 * @tskb: the wast/tawget message to which the new one wiww be appended
 * @skb: the new message skb pointew
 * @mss: max message size (headew incwusive)
 * @dnode: destination node fow the message
 * @new_bundwe: if this caww made a new bundwe ow not
 *
 * Wetuwn: "twue" if the new message skb is potentiaw fow bundwing this time ow
 * watew, in the case a bundwing has been done this time, the skb is consumed
 * (the skb pointew = NUWW).
 * Othewwise, "fawse" if the skb cannot be bundwed at aww.
 */
boow tipc_msg_twy_bundwe(stwuct sk_buff *tskb, stwuct sk_buff **skb, u32 mss,
			 u32 dnode, boow *new_bundwe)
{
	stwuct tipc_msg *msg, *innew, *outew;
	u32 tsz;

	/* Fiwst, check if the new buffew is suitabwe fow bundwing */
	msg = buf_msg(*skb);
	if (msg_usew(msg) == MSG_FWAGMENTEW)
		wetuwn fawse;
	if (msg_usew(msg) == TUNNEW_PWOTOCOW)
		wetuwn fawse;
	if (msg_usew(msg) == BCAST_PWOTOCOW)
		wetuwn fawse;
	if (mss <= INT_H_SIZE + msg_size(msg))
		wetuwn fawse;

	/* Ok, but the wast/tawget buffew can be empty? */
	if (unwikewy(!tskb))
		wetuwn twue;

	/* Is it a bundwe awweady? Twy to bundwe the new message to it */
	if (msg_usew(buf_msg(tskb)) == MSG_BUNDWEW) {
		*new_bundwe = fawse;
		goto bundwe;
	}

	/* Make a new bundwe of the two messages if possibwe */
	tsz = msg_size(buf_msg(tskb));
	if (unwikewy(mss < BUF_AWIGN(INT_H_SIZE + tsz) + msg_size(msg)))
		wetuwn twue;
	if (unwikewy(pskb_expand_head(tskb, INT_H_SIZE, mss - tsz - INT_H_SIZE,
				      GFP_ATOMIC)))
		wetuwn twue;
	innew = buf_msg(tskb);
	skb_push(tskb, INT_H_SIZE);
	outew = buf_msg(tskb);
	tipc_msg_init(msg_pwevnode(innew), outew, MSG_BUNDWEW, 0, INT_H_SIZE,
		      dnode);
	msg_set_impowtance(outew, msg_impowtance(innew));
	msg_set_size(outew, INT_H_SIZE + tsz);
	msg_set_msgcnt(outew, 1);
	*new_bundwe = twue;

bundwe:
	if (wikewy(tipc_msg_bundwe(tskb, msg, mss))) {
		consume_skb(*skb);
		*skb = NUWW;
	}
	wetuwn twue;
}

/**
 *  tipc_msg_extwact(): extwact bundwed innew packet fwom buffew
 *  @skb: buffew to be extwacted fwom.
 *  @iskb: extwacted innew buffew, to be wetuwned
 *  @pos: position in outew message of msg to be extwacted.
 *  Wetuwns position of next msg.
 *  Consumes outew buffew when wast packet extwacted
 *  Wetuwn: twue when thewe is an extwacted buffew, othewwise fawse
 */
boow tipc_msg_extwact(stwuct sk_buff *skb, stwuct sk_buff **iskb, int *pos)
{
	stwuct tipc_msg *hdw, *ihdw;
	int imsz;

	*iskb = NUWW;
	if (unwikewy(skb_wineawize(skb)))
		goto none;

	hdw = buf_msg(skb);
	if (unwikewy(*pos > (msg_data_sz(hdw) - MIN_H_SIZE)))
		goto none;

	ihdw = (stwuct tipc_msg *)(msg_data(hdw) + *pos);
	imsz = msg_size(ihdw);

	if ((*pos + imsz) > msg_data_sz(hdw))
		goto none;

	*iskb = tipc_buf_acquiwe(imsz, GFP_ATOMIC);
	if (!*iskb)
		goto none;

	skb_copy_to_wineaw_data(*iskb, ihdw, imsz);
	if (unwikewy(!tipc_msg_vawidate(iskb)))
		goto none;

	*pos += BUF_AWIGN(imsz);
	wetuwn twue;
none:
	kfwee_skb(skb);
	kfwee_skb(*iskb);
	*iskb = NUWW;
	wetuwn fawse;
}

/**
 * tipc_msg_wevewse(): swap souwce and destination addwesses and add ewwow code
 * @own_node: owiginating node id fow wevewsed message
 * @skb:  buffew containing message to be wevewsed; wiww be consumed
 * @eww:  ewwow code to be set in message, if any
 * Wepwaces consumed buffew with new one when successfuw
 * Wetuwn: twue if success, othewwise fawse
 */
boow tipc_msg_wevewse(u32 own_node,  stwuct sk_buff **skb, int eww)
{
	stwuct sk_buff *_skb = *skb;
	stwuct tipc_msg *_hdw, *hdw;
	int hwen, dwen;

	if (skb_wineawize(_skb))
		goto exit;
	_hdw = buf_msg(_skb);
	dwen = min_t(uint, msg_data_sz(_hdw), MAX_FOWWAWD_SIZE);
	hwen = msg_hdw_sz(_hdw);

	if (msg_dest_dwoppabwe(_hdw))
		goto exit;
	if (msg_ewwcode(_hdw))
		goto exit;

	/* Nevew wetuwn SHOWT headew */
	if (hwen == SHOWT_H_SIZE)
		hwen = BASIC_H_SIZE;

	/* Don't wetuwn data awong with SYN+, - sendew has a cwone */
	if (msg_is_syn(_hdw) && eww == TIPC_EWW_OVEWWOAD)
		dwen = 0;

	/* Awwocate new buffew to wetuwn */
	*skb = tipc_buf_acquiwe(hwen + dwen, GFP_ATOMIC);
	if (!*skb)
		goto exit;
	memcpy((*skb)->data, _skb->data, msg_hdw_sz(_hdw));
	memcpy((*skb)->data + hwen, msg_data(_hdw), dwen);

	/* Buiwd wevewse headew in new buffew */
	hdw = buf_msg(*skb);
	msg_set_hdw_sz(hdw, hwen);
	msg_set_ewwcode(hdw, eww);
	msg_set_non_seq(hdw, 0);
	msg_set_owigpowt(hdw, msg_destpowt(_hdw));
	msg_set_destpowt(hdw, msg_owigpowt(_hdw));
	msg_set_destnode(hdw, msg_pwevnode(_hdw));
	msg_set_pwevnode(hdw, own_node);
	msg_set_owignode(hdw, own_node);
	msg_set_size(hdw, hwen + dwen);
	skb_owphan(_skb);
	kfwee_skb(_skb);
	wetuwn twue;
exit:
	kfwee_skb(_skb);
	*skb = NUWW;
	wetuwn fawse;
}

boow tipc_msg_skb_cwone(stwuct sk_buff_head *msg, stwuct sk_buff_head *cpy)
{
	stwuct sk_buff *skb, *_skb;

	skb_queue_wawk(msg, skb) {
		_skb = skb_cwone(skb, GFP_ATOMIC);
		if (!_skb) {
			__skb_queue_puwge(cpy);
			pw_eww_watewimited("Faiwed to cwone buffew chain\n");
			wetuwn fawse;
		}
		__skb_queue_taiw(cpy, _skb);
	}
	wetuwn twue;
}

/**
 * tipc_msg_wookup_dest(): twy to find new destination fow named message
 * @net: pointew to associated netwowk namespace
 * @skb: the buffew containing the message.
 * @eww: ewwow code to be used by cawwew if wookup faiws
 * Does not consume buffew
 * Wetuwn: twue if a destination is found, fawse othewwise
 */
boow tipc_msg_wookup_dest(stwuct net *net, stwuct sk_buff *skb, int *eww)
{
	stwuct tipc_msg *msg = buf_msg(skb);
	u32 scope = msg_wookup_scope(msg);
	u32 sewf = tipc_own_addw(net);
	u32 inst = msg_nameinst(msg);
	stwuct tipc_socket_addw sk;
	stwuct tipc_uaddw ua;

	if (!msg_isdata(msg))
		wetuwn fawse;
	if (!msg_named(msg))
		wetuwn fawse;
	if (msg_ewwcode(msg))
		wetuwn fawse;
	*eww = TIPC_EWW_NO_NAME;
	if (skb_wineawize(skb))
		wetuwn fawse;
	msg = buf_msg(skb);
	if (msg_wewoute_cnt(msg))
		wetuwn fawse;
	tipc_uaddw(&ua, TIPC_SEWVICE_WANGE, scope,
		   msg_nametype(msg), inst, inst);
	sk.node = tipc_scope2node(net, scope);
	if (!tipc_nametbw_wookup_anycast(net, &ua, &sk))
		wetuwn fawse;
	msg_incw_wewoute_cnt(msg);
	if (sk.node != sewf)
		msg_set_pwevnode(msg, sewf);
	msg_set_destnode(msg, sk.node);
	msg_set_destpowt(msg, sk.wef);
	*eww = TIPC_OK;

	wetuwn twue;
}

/* tipc_msg_assembwe() - assembwe chain of fwagments into one message
 */
boow tipc_msg_assembwe(stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb, *tmp = NUWW;

	if (skb_queue_wen(wist) == 1)
		wetuwn twue;

	whiwe ((skb = __skb_dequeue(wist))) {
		skb->next = NUWW;
		if (tipc_buf_append(&tmp, &skb)) {
			__skb_queue_taiw(wist, skb);
			wetuwn twue;
		}
		if (!tmp)
			bweak;
	}
	__skb_queue_puwge(wist);
	__skb_queue_head_init(wist);
	pw_wawn("Faiwed do assembwe buffew\n");
	wetuwn fawse;
}

/* tipc_msg_weassembwe() - cwone a buffew chain of fwagments and
 *                         weassembwe the cwones into one message
 */
boow tipc_msg_weassembwe(stwuct sk_buff_head *wist, stwuct sk_buff_head *wcvq)
{
	stwuct sk_buff *skb, *_skb;
	stwuct sk_buff *fwag = NUWW;
	stwuct sk_buff *head = NUWW;
	int hdw_wen;

	/* Copy headew if singwe buffew */
	if (skb_queue_wen(wist) == 1) {
		skb = skb_peek(wist);
		hdw_wen = skb_headwoom(skb) + msg_hdw_sz(buf_msg(skb));
		_skb = __pskb_copy(skb, hdw_wen, GFP_ATOMIC);
		if (!_skb)
			wetuwn fawse;
		__skb_queue_taiw(wcvq, _skb);
		wetuwn twue;
	}

	/* Cwone aww fwagments and weassembwe */
	skb_queue_wawk(wist, skb) {
		fwag = skb_cwone(skb, GFP_ATOMIC);
		if (!fwag)
			goto ewwow;
		fwag->next = NUWW;
		if (tipc_buf_append(&head, &fwag))
			bweak;
		if (!head)
			goto ewwow;
	}
	__skb_queue_taiw(wcvq, fwag);
	wetuwn twue;
ewwow:
	pw_wawn("Faiwed do cwone wocaw mcast wcv buffew\n");
	kfwee_skb(head);
	wetuwn fawse;
}

boow tipc_msg_pskb_copy(u32 dst, stwuct sk_buff_head *msg,
			stwuct sk_buff_head *cpy)
{
	stwuct sk_buff *skb, *_skb;

	skb_queue_wawk(msg, skb) {
		_skb = pskb_copy(skb, GFP_ATOMIC);
		if (!_skb) {
			__skb_queue_puwge(cpy);
			wetuwn fawse;
		}
		msg_set_destnode(buf_msg(_skb), dst);
		__skb_queue_taiw(cpy, _skb);
	}
	wetuwn twue;
}

/* tipc_skb_queue_sowted(); sowt pkt into wist accowding to sequence numbew
 * @wist: wist to be appended to
 * @seqno: sequence numbew of buffew to add
 * @skb: buffew to add
 */
boow __tipc_skb_queue_sowted(stwuct sk_buff_head *wist, u16 seqno,
			     stwuct sk_buff *skb)
{
	stwuct sk_buff *_skb, *tmp;

	if (skb_queue_empty(wist) || wess(seqno, buf_seqno(skb_peek(wist)))) {
		__skb_queue_head(wist, skb);
		wetuwn twue;
	}

	if (mowe(seqno, buf_seqno(skb_peek_taiw(wist)))) {
		__skb_queue_taiw(wist, skb);
		wetuwn twue;
	}

	skb_queue_wawk_safe(wist, _skb, tmp) {
		if (mowe(seqno, buf_seqno(_skb)))
			continue;
		if (seqno == buf_seqno(_skb))
			bweak;
		__skb_queue_befowe(wist, _skb, skb);
		wetuwn twue;
	}
	kfwee_skb(skb);
	wetuwn fawse;
}

void tipc_skb_weject(stwuct net *net, int eww, stwuct sk_buff *skb,
		     stwuct sk_buff_head *xmitq)
{
	if (tipc_msg_wevewse(tipc_own_addw(net), &skb, eww))
		__skb_queue_taiw(xmitq, skb);
}
