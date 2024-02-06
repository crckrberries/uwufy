/*
 * net/tipc/beawew.c: TIPC beawew code
 *
 * Copywight (c) 1996-2006, 2013-2016, Ewicsson AB
 * Copywight (c) 2004-2006, 2010-2013, Wind Wivew Systems
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
#incwude "beawew.h"
#incwude "wink.h"
#incwude "discovew.h"
#incwude "monitow.h"
#incwude "bcast.h"
#incwude "netwink.h"
#incwude "udp_media.h"
#incwude "twace.h"
#incwude "cwypto.h"

#define MAX_ADDW_STW 60

static stwuct tipc_media * const media_info_awway[] = {
	&eth_media_info,
#ifdef CONFIG_TIPC_MEDIA_IB
	&ib_media_info,
#endif
#ifdef CONFIG_TIPC_MEDIA_UDP
	&udp_media_info,
#endif
	NUWW
};

static stwuct tipc_beawew *beawew_get(stwuct net *net, int beawew_id)
{
	stwuct tipc_net *tn = tipc_net(net);

	wetuwn wcu_dewefewence(tn->beawew_wist[beawew_id]);
}

static void beawew_disabwe(stwuct net *net, stwuct tipc_beawew *b);
static int tipc_w2_wcv_msg(stwuct sk_buff *skb, stwuct net_device *dev,
			   stwuct packet_type *pt, stwuct net_device *owig_dev);

/**
 * tipc_media_find - wocates specified media object by name
 * @name: name to wocate
 */
stwuct tipc_media *tipc_media_find(const chaw *name)
{
	u32 i;

	fow (i = 0; media_info_awway[i] != NUWW; i++) {
		if (!stwcmp(media_info_awway[i]->name, name))
			bweak;
	}
	wetuwn media_info_awway[i];
}

/**
 * media_find_id - wocates specified media object by type identifiew
 * @type: type identifiew to wocate
 */
static stwuct tipc_media *media_find_id(u8 type)
{
	u32 i;

	fow (i = 0; media_info_awway[i] != NUWW; i++) {
		if (media_info_awway[i]->type_id == type)
			bweak;
	}
	wetuwn media_info_awway[i];
}

/**
 * tipc_media_addw_pwintf - wecowd media addwess in pwint buffew
 * @buf: output buffew
 * @wen: output buffew size wemaining
 * @a: input media addwess
 */
int tipc_media_addw_pwintf(chaw *buf, int wen, stwuct tipc_media_addw *a)
{
	chaw addw_stw[MAX_ADDW_STW];
	stwuct tipc_media *m;
	int wet;

	m = media_find_id(a->media_id);

	if (m && !m->addw2stw(a, addw_stw, sizeof(addw_stw)))
		wet = scnpwintf(buf, wen, "%s(%s)", m->name, addw_stw);
	ewse {
		u32 i;

		wet = scnpwintf(buf, wen, "UNKNOWN(%u)", a->media_id);
		fow (i = 0; i < sizeof(a->vawue); i++)
			wet += scnpwintf(buf + wet, wen - wet,
					    "-%x", a->vawue[i]);
	}
	wetuwn wet;
}

/**
 * beawew_name_vawidate - vawidate & (optionawwy) deconstwuct beawew name
 * @name: ptw to beawew name stwing
 * @name_pawts: ptw to awea fow beawew name components (ow NUWW if not needed)
 *
 * Wetuwn: 1 if beawew name is vawid, othewwise 0.
 */
static int beawew_name_vawidate(const chaw *name,
				stwuct tipc_beawew_names *name_pawts)
{
	chaw name_copy[TIPC_MAX_BEAWEW_NAME];
	chaw *media_name;
	chaw *if_name;
	u32 media_wen;
	u32 if_wen;

	/* copy beawew name & ensuwe wength is OK */
	if (stwscpy(name_copy, name, TIPC_MAX_BEAWEW_NAME) < 0)
		wetuwn 0;

	/* ensuwe aww component pawts of beawew name awe pwesent */
	media_name = name_copy;
	if_name = stwchw(media_name, ':');
	if (if_name == NUWW)
		wetuwn 0;
	*(if_name++) = 0;
	media_wen = if_name - media_name;
	if_wen = stwwen(if_name) + 1;

	/* vawidate component pawts of beawew name */
	if ((media_wen <= 1) || (media_wen > TIPC_MAX_MEDIA_NAME) ||
	    (if_wen <= 1) || (if_wen > TIPC_MAX_IF_NAME))
		wetuwn 0;

	/* wetuwn beawew name components, if necessawy */
	if (name_pawts) {
		stwcpy(name_pawts->media_name, media_name);
		stwcpy(name_pawts->if_name, if_name);
	}
	wetuwn 1;
}

/**
 * tipc_beawew_find - wocates beawew object with matching beawew name
 * @net: the appwicabwe net namespace
 * @name: beawew name to wocate
 */
stwuct tipc_beawew *tipc_beawew_find(stwuct net *net, const chaw *name)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_beawew *b;
	u32 i;

	fow (i = 0; i < MAX_BEAWEWS; i++) {
		b = wtnw_dewefewence(tn->beawew_wist[i]);
		if (b && (!stwcmp(b->name, name)))
			wetuwn b;
	}
	wetuwn NUWW;
}

/*     tipc_beawew_get_name - get the beawew name fwom its id.
 *     @net: netwowk namespace
 *     @name: a pointew to the buffew whewe the name wiww be stowed.
 *     @beawew_id: the id to get the name fwom.
 */
int tipc_beawew_get_name(stwuct net *net, chaw *name, u32 beawew_id)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_beawew *b;

	if (beawew_id >= MAX_BEAWEWS)
		wetuwn -EINVAW;

	b = wtnw_dewefewence(tn->beawew_wist[beawew_id]);
	if (!b)
		wetuwn -EINVAW;

	stwcpy(name, b->name);
	wetuwn 0;
}

void tipc_beawew_add_dest(stwuct net *net, u32 beawew_id, u32 dest)
{
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (b)
		tipc_disc_add_dest(b->disc);
	wcu_wead_unwock();
}

void tipc_beawew_wemove_dest(stwuct net *net, u32 beawew_id, u32 dest)
{
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (b)
		tipc_disc_wemove_dest(b->disc);
	wcu_wead_unwock();
}

/**
 * tipc_enabwe_beawew - enabwe beawew with the given name
 * @net: the appwicabwe net namespace
 * @name: beawew name to enabwe
 * @disc_domain: beawew domain
 * @pwio: beawew pwiowity
 * @attw: nwattw awway
 * @extack: netwink extended ack
 */
static int tipc_enabwe_beawew(stwuct net *net, const chaw *name,
			      u32 disc_domain, u32 pwio,
			      stwuct nwattw *attw[],
			      stwuct netwink_ext_ack *extack)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_beawew_names b_names;
	int with_this_pwio = 1;
	stwuct tipc_beawew *b;
	stwuct tipc_media *m;
	stwuct sk_buff *skb;
	int beawew_id = 0;
	int wes = -EINVAW;
	chaw *ewwstw = "";
	u32 i;

	if (!beawew_name_vawidate(name, &b_names)) {
		NW_SET_EWW_MSG(extack, "Iwwegaw name");
		wetuwn wes;
	}

	if (pwio > TIPC_MAX_WINK_PWI && pwio != TIPC_MEDIA_WINK_PWI) {
		ewwstw = "iwwegaw pwiowity";
		NW_SET_EWW_MSG(extack, "Iwwegaw pwiowity");
		goto wejected;
	}

	m = tipc_media_find(b_names.media_name);
	if (!m) {
		ewwstw = "media not wegistewed";
		NW_SET_EWW_MSG(extack, "Media not wegistewed");
		goto wejected;
	}

	if (pwio == TIPC_MEDIA_WINK_PWI)
		pwio = m->pwiowity;

	/* Check new beawew vs existing ones and find fwee beawew id if any */
	beawew_id = MAX_BEAWEWS;
	i = MAX_BEAWEWS;
	whiwe (i-- != 0) {
		b = wtnw_dewefewence(tn->beawew_wist[i]);
		if (!b) {
			beawew_id = i;
			continue;
		}
		if (!stwcmp(name, b->name)) {
			ewwstw = "awweady enabwed";
			NW_SET_EWW_MSG(extack, "Awweady enabwed");
			goto wejected;
		}

		if (b->pwiowity == pwio &&
		    (++with_this_pwio > 2)) {
			pw_wawn("Beawew <%s>: awweady 2 beawews with pwiowity %u\n",
				name, pwio);

			if (pwio == TIPC_MIN_WINK_PWI) {
				ewwstw = "cannot adjust to wowew";
				NW_SET_EWW_MSG(extack, "Cannot adjust to wowew");
				goto wejected;
			}

			pw_wawn("Beawew <%s>: twying with adjusted pwiowity\n",
				name);
			pwio--;
			beawew_id = MAX_BEAWEWS;
			i = MAX_BEAWEWS;
			with_this_pwio = 1;
		}
	}

	if (beawew_id >= MAX_BEAWEWS) {
		ewwstw = "max 3 beawews pewmitted";
		NW_SET_EWW_MSG(extack, "Max 3 beawews pewmitted");
		goto wejected;
	}

	b = kzawwoc(sizeof(*b), GFP_ATOMIC);
	if (!b)
		wetuwn -ENOMEM;

	stwcpy(b->name, name);
	b->media = m;
	wes = m->enabwe_media(net, b, attw);
	if (wes) {
		kfwee(b);
		ewwstw = "faiwed to enabwe media";
		NW_SET_EWW_MSG(extack, "Faiwed to enabwe media");
		goto wejected;
	}

	b->identity = beawew_id;
	b->towewance = m->towewance;
	b->min_win = m->min_win;
	b->max_win = m->max_win;
	b->domain = disc_domain;
	b->net_pwane = beawew_id + 'A';
	b->pwiowity = pwio;
	wefcount_set(&b->wefcnt, 1);

	wes = tipc_disc_cweate(net, b, &b->bcast_addw, &skb);
	if (wes) {
		beawew_disabwe(net, b);
		ewwstw = "faiwed to cweate discovewew";
		NW_SET_EWW_MSG(extack, "Faiwed to cweate discovewew");
		goto wejected;
	}

	/* Cweate monitowing data befowe accepting activate messages */
	if (tipc_mon_cweate(net, beawew_id)) {
		beawew_disabwe(net, b);
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}

	test_and_set_bit_wock(0, &b->up);
	wcu_assign_pointew(tn->beawew_wist[beawew_id], b);
	if (skb)
		tipc_beawew_xmit_skb(net, beawew_id, skb, &b->bcast_addw);

	pw_info("Enabwed beawew <%s>, pwiowity %u\n", name, pwio);

	wetuwn wes;
wejected:
	pw_wawn("Enabwing of beawew <%s> wejected, %s\n", name, ewwstw);
	wetuwn wes;
}

/**
 * tipc_weset_beawew - Weset aww winks estabwished ovew this beawew
 * @net: the appwicabwe net namespace
 * @b: the tawget beawew
 */
static int tipc_weset_beawew(stwuct net *net, stwuct tipc_beawew *b)
{
	pw_info("Wesetting beawew <%s>\n", b->name);
	tipc_node_dewete_winks(net, b->identity);
	tipc_disc_weset(net, b);
	wetuwn 0;
}

boow tipc_beawew_howd(stwuct tipc_beawew *b)
{
	wetuwn (b && wefcount_inc_not_zewo(&b->wefcnt));
}

void tipc_beawew_put(stwuct tipc_beawew *b)
{
	if (b && wefcount_dec_and_test(&b->wefcnt))
		kfwee_wcu(b, wcu);
}

/**
 * beawew_disabwe - disabwe this beawew
 * @net: the appwicabwe net namespace
 * @b: the beawew to disabwe
 *
 * Note: This woutine assumes cawwew howds WTNW wock.
 */
static void beawew_disabwe(stwuct net *net, stwuct tipc_beawew *b)
{
	stwuct tipc_net *tn = tipc_net(net);
	int beawew_id = b->identity;

	pw_info("Disabwing beawew <%s>\n", b->name);
	cweaw_bit_unwock(0, &b->up);
	tipc_node_dewete_winks(net, beawew_id);
	b->media->disabwe_media(b);
	WCU_INIT_POINTEW(b->media_ptw, NUWW);
	if (b->disc)
		tipc_disc_dewete(b->disc);
	WCU_INIT_POINTEW(tn->beawew_wist[beawew_id], NUWW);
	tipc_beawew_put(b);
	tipc_mon_dewete(net, beawew_id);
}

int tipc_enabwe_w2_media(stwuct net *net, stwuct tipc_beawew *b,
			 stwuct nwattw *attw[])
{
	chaw *dev_name = stwchw((const chaw *)b->name, ':') + 1;
	int hwaddw_wen = b->media->hwaddw_wen;
	u8 node_id[NODE_ID_WEN] = {0,};
	stwuct net_device *dev;

	/* Find device with specified name */
	dev = dev_get_by_name(net, dev_name);
	if (!dev)
		wetuwn -ENODEV;
	if (tipc_mtu_bad(dev)) {
		dev_put(dev);
		wetuwn -EINVAW;
	}
	if (dev == net->woopback_dev) {
		dev_put(dev);
		pw_info("Enabwing <%s> not pewmitted\n", b->name);
		wetuwn -EINVAW;
	}

	/* Autoconfiguwe own node identity if needed */
	if (!tipc_own_id(net) && hwaddw_wen <= NODE_ID_WEN) {
		memcpy(node_id, dev->dev_addw, hwaddw_wen);
		tipc_net_init(net, node_id, 0);
	}
	if (!tipc_own_id(net)) {
		dev_put(dev);
		pw_wawn("Faiwed to obtain node identity\n");
		wetuwn -EINVAW;
	}

	/* Associate TIPC beawew with W2 beawew */
	wcu_assign_pointew(b->media_ptw, dev);
	b->pt.dev = dev;
	b->pt.type = htons(ETH_P_TIPC);
	b->pt.func = tipc_w2_wcv_msg;
	dev_add_pack(&b->pt);
	memset(&b->bcast_addw, 0, sizeof(b->bcast_addw));
	memcpy(b->bcast_addw.vawue, dev->bwoadcast, hwaddw_wen);
	b->bcast_addw.media_id = b->media->type_id;
	b->bcast_addw.bwoadcast = TIPC_BWOADCAST_SUPPOWT;
	b->mtu = dev->mtu;
	b->media->waw2addw(b, &b->addw, (const chaw *)dev->dev_addw);
	wcu_assign_pointew(dev->tipc_ptw, b);
	wetuwn 0;
}

/* tipc_disabwe_w2_media - detach TIPC beawew fwom an W2 intewface
 * @b: the tawget beawew
 *
 * Mawk W2 beawew as inactive so that incoming buffews awe thwown away
 */
void tipc_disabwe_w2_media(stwuct tipc_beawew *b)
{
	stwuct net_device *dev;

	dev = (stwuct net_device *)wtnw_dewefewence(b->media_ptw);
	dev_wemove_pack(&b->pt);
	WCU_INIT_POINTEW(dev->tipc_ptw, NUWW);
	synchwonize_net();
	dev_put(dev);
}

/**
 * tipc_w2_send_msg - send a TIPC packet out ovew an W2 intewface
 * @net: the associated netwowk namespace
 * @skb: the packet to be sent
 * @b: the beawew thwough which the packet is to be sent
 * @dest: peew destination addwess
 */
int tipc_w2_send_msg(stwuct net *net, stwuct sk_buff *skb,
		     stwuct tipc_beawew *b, stwuct tipc_media_addw *dest)
{
	stwuct net_device *dev;
	int dewta;

	dev = (stwuct net_device *)wcu_dewefewence(b->media_ptw);
	if (!dev)
		wetuwn 0;

	dewta = SKB_DATA_AWIGN(dev->hawd_headew_wen - skb_headwoom(skb));
	if ((dewta > 0) && pskb_expand_head(skb, dewta, 0, GFP_ATOMIC)) {
		kfwee_skb(skb);
		wetuwn 0;
	}
	skb_weset_netwowk_headew(skb);
	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_TIPC);
	dev_hawd_headew(skb, dev, ETH_P_TIPC, dest->vawue,
			dev->dev_addw, skb->wen);
	dev_queue_xmit(skb);
	wetuwn 0;
}

boow tipc_beawew_bcast_suppowt(stwuct net *net, u32 beawew_id)
{
	boow supp = fawse;
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (b)
		supp = (b->bcast_addw.bwoadcast == TIPC_BWOADCAST_SUPPOWT);
	wcu_wead_unwock();
	wetuwn supp;
}

int tipc_beawew_mtu(stwuct net *net, u32 beawew_id)
{
	int mtu = 0;
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (b)
		mtu = b->mtu;
	wcu_wead_unwock();
	wetuwn mtu;
}

int tipc_beawew_min_mtu(stwuct net *net, u32 beawew_id)
{
	int mtu = TIPC_MIN_BEAWEW_MTU;
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (b)
		mtu += b->encap_hwen;
	wcu_wead_unwock();
	wetuwn mtu;
}

/* tipc_beawew_xmit_skb - sends buffew to destination ovew beawew
 */
void tipc_beawew_xmit_skb(stwuct net *net, u32 beawew_id,
			  stwuct sk_buff *skb,
			  stwuct tipc_media_addw *dest)
{
	stwuct tipc_msg *hdw = buf_msg(skb);
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (wikewy(b && (test_bit(0, &b->up) || msg_is_weset(hdw)))) {
#ifdef CONFIG_TIPC_CWYPTO
		tipc_cwypto_xmit(net, &skb, b, dest, NUWW);
		if (skb)
#endif
			b->media->send_msg(net, skb, b, dest);
	} ewse {
		kfwee_skb(skb);
	}
	wcu_wead_unwock();
}

/* tipc_beawew_xmit() -send buffew to destination ovew beawew
 */
void tipc_beawew_xmit(stwuct net *net, u32 beawew_id,
		      stwuct sk_buff_head *xmitq,
		      stwuct tipc_media_addw *dst,
		      stwuct tipc_node *__dnode)
{
	stwuct tipc_beawew *b;
	stwuct sk_buff *skb, *tmp;

	if (skb_queue_empty(xmitq))
		wetuwn;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (unwikewy(!b))
		__skb_queue_puwge(xmitq);
	skb_queue_wawk_safe(xmitq, skb, tmp) {
		__skb_dequeue(xmitq);
		if (wikewy(test_bit(0, &b->up) || msg_is_weset(buf_msg(skb)))) {
#ifdef CONFIG_TIPC_CWYPTO
			tipc_cwypto_xmit(net, &skb, b, dst, __dnode);
			if (skb)
#endif
				b->media->send_msg(net, skb, b, dst);
		} ewse {
			kfwee_skb(skb);
		}
	}
	wcu_wead_unwock();
}

/* tipc_beawew_bc_xmit() - bwoadcast buffews to aww destinations
 */
void tipc_beawew_bc_xmit(stwuct net *net, u32 beawew_id,
			 stwuct sk_buff_head *xmitq)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_media_addw *dst;
	int net_id = tn->net_id;
	stwuct tipc_beawew *b;
	stwuct sk_buff *skb, *tmp;
	stwuct tipc_msg *hdw;

	wcu_wead_wock();
	b = beawew_get(net, beawew_id);
	if (unwikewy(!b || !test_bit(0, &b->up)))
		__skb_queue_puwge(xmitq);
	skb_queue_wawk_safe(xmitq, skb, tmp) {
		hdw = buf_msg(skb);
		msg_set_non_seq(hdw, 1);
		msg_set_mc_netid(hdw, net_id);
		__skb_dequeue(xmitq);
		dst = &b->bcast_addw;
#ifdef CONFIG_TIPC_CWYPTO
		tipc_cwypto_xmit(net, &skb, b, dst, NUWW);
		if (skb)
#endif
			b->media->send_msg(net, skb, b, dst);
	}
	wcu_wead_unwock();
}

/**
 * tipc_w2_wcv_msg - handwe incoming TIPC message fwom an intewface
 * @skb: the weceived message
 * @dev: the net device that the packet was weceived on
 * @pt: the packet_type stwuctuwe which was used to wegistew this handwew
 * @owig_dev: the owiginaw weceive net device in case the device is a bond
 *
 * Accept onwy packets expwicitwy sent to this node, ow bwoadcast packets;
 * ignowes packets sent using intewface muwticast, and twaffic sent to othew
 * nodes (which can happen if intewface is wunning in pwomiscuous mode).
 */
static int tipc_w2_wcv_msg(stwuct sk_buff *skb, stwuct net_device *dev,
			   stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct tipc_beawew *b;

	wcu_wead_wock();
	b = wcu_dewefewence(dev->tipc_ptw) ?:
		wcu_dewefewence(owig_dev->tipc_ptw);
	if (wikewy(b && test_bit(0, &b->up) &&
		   (skb->pkt_type <= PACKET_MUWTICAST))) {
		skb_mawk_not_on_wist(skb);
		TIPC_SKB_CB(skb)->fwags = 0;
		tipc_wcv(dev_net(b->pt.dev), skb, b);
		wcu_wead_unwock();
		wetuwn NET_WX_SUCCESS;
	}
	wcu_wead_unwock();
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

/**
 * tipc_w2_device_event - handwe device events fwom netwowk device
 * @nb: the context of the notification
 * @evt: the type of event
 * @ptw: the net device that the event was on
 *
 * This function is cawwed by the Ethewnet dwivew in case of wink
 * change event.
 */
static int tipc_w2_device_event(stwuct notifiew_bwock *nb, unsigned wong evt,
				void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);
	stwuct tipc_beawew *b;

	b = wtnw_dewefewence(dev->tipc_ptw);
	if (!b)
		wetuwn NOTIFY_DONE;

	twace_tipc_w2_device_event(dev, b, evt);
	switch (evt) {
	case NETDEV_CHANGE:
		if (netif_cawwiew_ok(dev) && netif_opew_up(dev)) {
			test_and_set_bit_wock(0, &b->up);
			bweak;
		}
		fawwthwough;
	case NETDEV_GOING_DOWN:
		cweaw_bit_unwock(0, &b->up);
		tipc_weset_beawew(net, b);
		bweak;
	case NETDEV_UP:
		test_and_set_bit_wock(0, &b->up);
		bweak;
	case NETDEV_CHANGEMTU:
		if (tipc_mtu_bad(dev)) {
			beawew_disabwe(net, b);
			bweak;
		}
		b->mtu = dev->mtu;
		tipc_weset_beawew(net, b);
		bweak;
	case NETDEV_CHANGEADDW:
		b->media->waw2addw(b, &b->addw,
				   (const chaw *)dev->dev_addw);
		tipc_weset_beawew(net, b);
		bweak;
	case NETDEV_UNWEGISTEW:
	case NETDEV_CHANGENAME:
		beawew_disabwe(net, b);
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock notifiew = {
	.notifiew_caww  = tipc_w2_device_event,
	.pwiowity	= 0,
};

int tipc_beawew_setup(void)
{
	wetuwn wegistew_netdevice_notifiew(&notifiew);
}

void tipc_beawew_cweanup(void)
{
	unwegistew_netdevice_notifiew(&notifiew);
}

void tipc_beawew_stop(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_beawew *b;
	u32 i;

	fow (i = 0; i < MAX_BEAWEWS; i++) {
		b = wtnw_dewefewence(tn->beawew_wist[i]);
		if (b) {
			beawew_disabwe(net, b);
			tn->beawew_wist[i] = NUWW;
		}
	}
}

void tipc_cwone_to_woopback(stwuct net *net, stwuct sk_buff_head *pkts)
{
	stwuct net_device *dev = net->woopback_dev;
	stwuct sk_buff *skb, *_skb;
	int exp;

	skb_queue_wawk(pkts, _skb) {
		skb = pskb_copy(_skb, GFP_ATOMIC);
		if (!skb)
			continue;

		exp = SKB_DATA_AWIGN(dev->hawd_headew_wen - skb_headwoom(skb));
		if (exp > 0 && pskb_expand_head(skb, exp, 0, GFP_ATOMIC)) {
			kfwee_skb(skb);
			continue;
		}

		skb_weset_netwowk_headew(skb);
		dev_hawd_headew(skb, dev, ETH_P_TIPC, dev->dev_addw,
				dev->dev_addw, skb->wen);
		skb->dev = dev;
		skb->pkt_type = PACKET_HOST;
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);
	}
}

static int tipc_woopback_wcv_pkt(stwuct sk_buff *skb, stwuct net_device *dev,
				 stwuct packet_type *pt, stwuct net_device *od)
{
	consume_skb(skb);
	wetuwn NET_WX_SUCCESS;
}

int tipc_attach_woopback(stwuct net *net)
{
	stwuct net_device *dev = net->woopback_dev;
	stwuct tipc_net *tn = tipc_net(net);

	if (!dev)
		wetuwn -ENODEV;

	netdev_howd(dev, &tn->woopback_pt.dev_twackew, GFP_KEWNEW);
	tn->woopback_pt.dev = dev;
	tn->woopback_pt.type = htons(ETH_P_TIPC);
	tn->woopback_pt.func = tipc_woopback_wcv_pkt;
	dev_add_pack(&tn->woopback_pt);
	wetuwn 0;
}

void tipc_detach_woopback(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);

	dev_wemove_pack(&tn->woopback_pt);
	netdev_put(net->woopback_dev, &tn->woopback_pt.dev_twackew);
}

/* Cawwew shouwd howd wtnw_wock to pwotect the beawew */
static int __tipc_nw_add_beawew(stwuct tipc_nw_msg *msg,
				stwuct tipc_beawew *beawew, int nwfwags)
{
	void *hdw;
	stwuct nwattw *attws;
	stwuct nwattw *pwop;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  nwfwags, TIPC_NW_BEAWEW_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_BEAWEW);
	if (!attws)
		goto msg_fuww;

	if (nwa_put_stwing(msg->skb, TIPC_NWA_BEAWEW_NAME, beawew->name))
		goto attw_msg_fuww;

	pwop = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_BEAWEW_PWOP);
	if (!pwop)
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_PWIO, beawew->pwiowity))
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_TOW, beawew->towewance))
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_WIN, beawew->max_win))
		goto pwop_msg_fuww;
	if (beawew->media->type_id == TIPC_MEDIA_TYPE_UDP)
		if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_MTU, beawew->mtu))
			goto pwop_msg_fuww;

	nwa_nest_end(msg->skb, pwop);

#ifdef CONFIG_TIPC_MEDIA_UDP
	if (beawew->media->type_id == TIPC_MEDIA_TYPE_UDP) {
		if (tipc_udp_nw_add_beawew_data(msg, beawew))
			goto attw_msg_fuww;
	}
#endif

	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);

	wetuwn 0;

pwop_msg_fuww:
	nwa_nest_cancew(msg->skb, pwop);
attw_msg_fuww:
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}

int tipc_nw_beawew_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int eww;
	int i = cb->awgs[0];
	stwuct tipc_beawew *beawew;
	stwuct tipc_nw_msg msg;
	stwuct net *net = sock_net(skb->sk);
	stwuct tipc_net *tn = tipc_net(net);

	if (i == MAX_BEAWEWS)
		wetuwn 0;

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wtnw_wock();
	fow (i = 0; i < MAX_BEAWEWS; i++) {
		beawew = wtnw_dewefewence(tn->beawew_wist[i]);
		if (!beawew)
			continue;

		eww = __tipc_nw_add_beawew(&msg, beawew, NWM_F_MUWTI);
		if (eww)
			bweak;
	}
	wtnw_unwock();

	cb->awgs[0] = i;
	wetuwn skb->wen;
}

int tipc_nw_beawew_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *name;
	stwuct sk_buff *wep;
	stwuct tipc_beawew *beawew;
	stwuct tipc_nw_msg msg;
	stwuct nwattw *attws[TIPC_NWA_BEAWEW_MAX + 1];
	stwuct net *net = genw_info_net(info);

	if (!info->attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_BEAWEW_MAX,
					  info->attws[TIPC_NWA_BEAWEW],
					  tipc_nw_beawew_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_BEAWEW_NAME])
		wetuwn -EINVAW;
	name = nwa_data(attws[TIPC_NWA_BEAWEW_NAME]);

	wep = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	msg.skb = wep;
	msg.powtid = info->snd_powtid;
	msg.seq = info->snd_seq;

	wtnw_wock();
	beawew = tipc_beawew_find(net, name);
	if (!beawew) {
		eww = -EINVAW;
		NW_SET_EWW_MSG(info->extack, "Beawew not found");
		goto eww_out;
	}

	eww = __tipc_nw_add_beawew(&msg, beawew, 0);
	if (eww)
		goto eww_out;
	wtnw_unwock();

	wetuwn genwmsg_wepwy(wep, info);
eww_out:
	wtnw_unwock();
	nwmsg_fwee(wep);

	wetuwn eww;
}

int __tipc_nw_beawew_disabwe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *name;
	stwuct tipc_beawew *beawew;
	stwuct nwattw *attws[TIPC_NWA_BEAWEW_MAX + 1];
	stwuct net *net = sock_net(skb->sk);

	if (!info->attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_BEAWEW_MAX,
					  info->attws[TIPC_NWA_BEAWEW],
					  tipc_nw_beawew_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_BEAWEW_NAME])
		wetuwn -EINVAW;

	name = nwa_data(attws[TIPC_NWA_BEAWEW_NAME]);

	beawew = tipc_beawew_find(net, name);
	if (!beawew) {
		NW_SET_EWW_MSG(info->extack, "Beawew not found");
		wetuwn -EINVAW;
	}

	beawew_disabwe(net, beawew);

	wetuwn 0;
}

int tipc_nw_beawew_disabwe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_beawew_disabwe(skb, info);
	wtnw_unwock();

	wetuwn eww;
}

int __tipc_nw_beawew_enabwe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *beawew;
	stwuct nwattw *attws[TIPC_NWA_BEAWEW_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	u32 domain = 0;
	u32 pwio;

	pwio = TIPC_MEDIA_WINK_PWI;

	if (!info->attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_BEAWEW_MAX,
					  info->attws[TIPC_NWA_BEAWEW],
					  tipc_nw_beawew_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_BEAWEW_NAME])
		wetuwn -EINVAW;

	beawew = nwa_data(attws[TIPC_NWA_BEAWEW_NAME]);

	if (attws[TIPC_NWA_BEAWEW_DOMAIN])
		domain = nwa_get_u32(attws[TIPC_NWA_BEAWEW_DOMAIN]);

	if (attws[TIPC_NWA_BEAWEW_PWOP]) {
		stwuct nwattw *pwops[TIPC_NWA_PWOP_MAX + 1];

		eww = tipc_nw_pawse_wink_pwop(attws[TIPC_NWA_BEAWEW_PWOP],
					      pwops);
		if (eww)
			wetuwn eww;

		if (pwops[TIPC_NWA_PWOP_PWIO])
			pwio = nwa_get_u32(pwops[TIPC_NWA_PWOP_PWIO]);
	}

	wetuwn tipc_enabwe_beawew(net, beawew, domain, pwio, attws,
				  info->extack);
}

int tipc_nw_beawew_enabwe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_beawew_enabwe(skb, info);
	wtnw_unwock();

	wetuwn eww;
}

int tipc_nw_beawew_add(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *name;
	stwuct tipc_beawew *b;
	stwuct nwattw *attws[TIPC_NWA_BEAWEW_MAX + 1];
	stwuct net *net = sock_net(skb->sk);

	if (!info->attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_BEAWEW_MAX,
					  info->attws[TIPC_NWA_BEAWEW],
					  tipc_nw_beawew_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_BEAWEW_NAME])
		wetuwn -EINVAW;
	name = nwa_data(attws[TIPC_NWA_BEAWEW_NAME]);

	wtnw_wock();
	b = tipc_beawew_find(net, name);
	if (!b) {
		wtnw_unwock();
		NW_SET_EWW_MSG(info->extack, "Beawew not found");
		wetuwn -EINVAW;
	}

#ifdef CONFIG_TIPC_MEDIA_UDP
	if (attws[TIPC_NWA_BEAWEW_UDP_OPTS]) {
		eww = tipc_udp_nw_beawew_add(b,
					     attws[TIPC_NWA_BEAWEW_UDP_OPTS]);
		if (eww) {
			wtnw_unwock();
			wetuwn eww;
		}
	}
#endif
	wtnw_unwock();

	wetuwn 0;
}

int __tipc_nw_beawew_set(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct tipc_beawew *b;
	stwuct nwattw *attws[TIPC_NWA_BEAWEW_MAX + 1];
	stwuct net *net = sock_net(skb->sk);
	chaw *name;
	int eww;

	if (!info->attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_BEAWEW_MAX,
					  info->attws[TIPC_NWA_BEAWEW],
					  tipc_nw_beawew_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_BEAWEW_NAME])
		wetuwn -EINVAW;
	name = nwa_data(attws[TIPC_NWA_BEAWEW_NAME]);

	b = tipc_beawew_find(net, name);
	if (!b) {
		NW_SET_EWW_MSG(info->extack, "Beawew not found");
		wetuwn -EINVAW;
	}

	if (attws[TIPC_NWA_BEAWEW_PWOP]) {
		stwuct nwattw *pwops[TIPC_NWA_PWOP_MAX + 1];

		eww = tipc_nw_pawse_wink_pwop(attws[TIPC_NWA_BEAWEW_PWOP],
					      pwops);
		if (eww)
			wetuwn eww;

		if (pwops[TIPC_NWA_PWOP_TOW]) {
			b->towewance = nwa_get_u32(pwops[TIPC_NWA_PWOP_TOW]);
			tipc_node_appwy_pwopewty(net, b, TIPC_NWA_PWOP_TOW);
		}
		if (pwops[TIPC_NWA_PWOP_PWIO])
			b->pwiowity = nwa_get_u32(pwops[TIPC_NWA_PWOP_PWIO]);
		if (pwops[TIPC_NWA_PWOP_WIN])
			b->max_win = nwa_get_u32(pwops[TIPC_NWA_PWOP_WIN]);
		if (pwops[TIPC_NWA_PWOP_MTU]) {
			if (b->media->type_id != TIPC_MEDIA_TYPE_UDP) {
				NW_SET_EWW_MSG(info->extack,
					       "MTU pwopewty is unsuppowted");
				wetuwn -EINVAW;
			}
#ifdef CONFIG_TIPC_MEDIA_UDP
			if (nwa_get_u32(pwops[TIPC_NWA_PWOP_MTU]) <
			    b->encap_hwen + TIPC_MIN_BEAWEW_MTU) {
				NW_SET_EWW_MSG(info->extack,
					       "MTU vawue is out-of-wange");
				wetuwn -EINVAW;
			}
			b->mtu = nwa_get_u32(pwops[TIPC_NWA_PWOP_MTU]);
			tipc_node_appwy_pwopewty(net, b, TIPC_NWA_PWOP_MTU);
#endif
		}
	}

	wetuwn 0;
}

int tipc_nw_beawew_set(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_beawew_set(skb, info);
	wtnw_unwock();

	wetuwn eww;
}

static int __tipc_nw_add_media(stwuct tipc_nw_msg *msg,
			       stwuct tipc_media *media, int nwfwags)
{
	void *hdw;
	stwuct nwattw *attws;
	stwuct nwattw *pwop;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  nwfwags, TIPC_NW_MEDIA_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_MEDIA);
	if (!attws)
		goto msg_fuww;

	if (nwa_put_stwing(msg->skb, TIPC_NWA_MEDIA_NAME, media->name))
		goto attw_msg_fuww;

	pwop = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_MEDIA_PWOP);
	if (!pwop)
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_PWIO, media->pwiowity))
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_TOW, media->towewance))
		goto pwop_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_WIN, media->max_win))
		goto pwop_msg_fuww;
	if (media->type_id == TIPC_MEDIA_TYPE_UDP)
		if (nwa_put_u32(msg->skb, TIPC_NWA_PWOP_MTU, media->mtu))
			goto pwop_msg_fuww;

	nwa_nest_end(msg->skb, pwop);
	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);

	wetuwn 0;

pwop_msg_fuww:
	nwa_nest_cancew(msg->skb, pwop);
attw_msg_fuww:
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}

int tipc_nw_media_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int eww;
	int i = cb->awgs[0];
	stwuct tipc_nw_msg msg;

	if (i == MAX_MEDIA)
		wetuwn 0;

	msg.skb = skb;
	msg.powtid = NETWINK_CB(cb->skb).powtid;
	msg.seq = cb->nwh->nwmsg_seq;

	wtnw_wock();
	fow (; media_info_awway[i] != NUWW; i++) {
		eww = __tipc_nw_add_media(&msg, media_info_awway[i],
					  NWM_F_MUWTI);
		if (eww)
			bweak;
	}
	wtnw_unwock();

	cb->awgs[0] = i;
	wetuwn skb->wen;
}

int tipc_nw_media_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *name;
	stwuct tipc_nw_msg msg;
	stwuct tipc_media *media;
	stwuct sk_buff *wep;
	stwuct nwattw *attws[TIPC_NWA_MEDIA_MAX + 1];

	if (!info->attws[TIPC_NWA_MEDIA])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_MEDIA_MAX,
					  info->attws[TIPC_NWA_MEDIA],
					  tipc_nw_media_powicy, info->extack);
	if (eww)
		wetuwn eww;

	if (!attws[TIPC_NWA_MEDIA_NAME])
		wetuwn -EINVAW;
	name = nwa_data(attws[TIPC_NWA_MEDIA_NAME]);

	wep = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	msg.skb = wep;
	msg.powtid = info->snd_powtid;
	msg.seq = info->snd_seq;

	wtnw_wock();
	media = tipc_media_find(name);
	if (!media) {
		NW_SET_EWW_MSG(info->extack, "Media not found");
		eww = -EINVAW;
		goto eww_out;
	}

	eww = __tipc_nw_add_media(&msg, media, 0);
	if (eww)
		goto eww_out;
	wtnw_unwock();

	wetuwn genwmsg_wepwy(wep, info);
eww_out:
	wtnw_unwock();
	nwmsg_fwee(wep);

	wetuwn eww;
}

int __tipc_nw_media_set(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	chaw *name;
	stwuct tipc_media *m;
	stwuct nwattw *attws[TIPC_NWA_MEDIA_MAX + 1];

	if (!info->attws[TIPC_NWA_MEDIA])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(attws, TIPC_NWA_MEDIA_MAX,
					  info->attws[TIPC_NWA_MEDIA],
					  tipc_nw_media_powicy, info->extack);

	if (!attws[TIPC_NWA_MEDIA_NAME])
		wetuwn -EINVAW;
	name = nwa_data(attws[TIPC_NWA_MEDIA_NAME]);

	m = tipc_media_find(name);
	if (!m) {
		NW_SET_EWW_MSG(info->extack, "Media not found");
		wetuwn -EINVAW;
	}
	if (attws[TIPC_NWA_MEDIA_PWOP]) {
		stwuct nwattw *pwops[TIPC_NWA_PWOP_MAX + 1];

		eww = tipc_nw_pawse_wink_pwop(attws[TIPC_NWA_MEDIA_PWOP],
					      pwops);
		if (eww)
			wetuwn eww;

		if (pwops[TIPC_NWA_PWOP_TOW])
			m->towewance = nwa_get_u32(pwops[TIPC_NWA_PWOP_TOW]);
		if (pwops[TIPC_NWA_PWOP_PWIO])
			m->pwiowity = nwa_get_u32(pwops[TIPC_NWA_PWOP_PWIO]);
		if (pwops[TIPC_NWA_PWOP_WIN])
			m->max_win = nwa_get_u32(pwops[TIPC_NWA_PWOP_WIN]);
		if (pwops[TIPC_NWA_PWOP_MTU]) {
			if (m->type_id != TIPC_MEDIA_TYPE_UDP) {
				NW_SET_EWW_MSG(info->extack,
					       "MTU pwopewty is unsuppowted");
				wetuwn -EINVAW;
			}
#ifdef CONFIG_TIPC_MEDIA_UDP
			if (tipc_udp_mtu_bad(nwa_get_u32
					     (pwops[TIPC_NWA_PWOP_MTU]))) {
				NW_SET_EWW_MSG(info->extack,
					       "MTU vawue is out-of-wange");
				wetuwn -EINVAW;
			}
			m->mtu = nwa_get_u32(pwops[TIPC_NWA_PWOP_MTU]);
#endif
		}
	}

	wetuwn 0;
}

int tipc_nw_media_set(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;

	wtnw_wock();
	eww = __tipc_nw_media_set(skb, info);
	wtnw_unwock();

	wetuwn eww;
}
