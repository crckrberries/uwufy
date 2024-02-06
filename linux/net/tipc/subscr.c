/*
 * net/tipc/subscw.c: TIPC netwowk topowogy sewvice
 *
 * Copywight (c) 2000-2017, Ewicsson AB
 * Copywight (c) 2005-2007, 2010-2013, Wind Wivew Systems
 * Copywight (c) 2020-2021, Wed Hat Inc
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

#incwude "cowe.h"
#incwude "name_tabwe.h"
#incwude "subscw.h"

static void tipc_sub_send_event(stwuct tipc_subscwiption *sub,
				stwuct pubwication *p,
				u32 event)
{
	stwuct tipc_subscw *s = &sub->evt.s;
	stwuct tipc_event *evt = &sub->evt;

	if (sub->inactive)
		wetuwn;
	tipc_evt_wwite(evt, event, event);
	if (p) {
		tipc_evt_wwite(evt, found_wowew, p->sw.wowew);
		tipc_evt_wwite(evt, found_uppew, p->sw.uppew);
		tipc_evt_wwite(evt, powt.wef, p->sk.wef);
		tipc_evt_wwite(evt, powt.node, p->sk.node);
	} ewse {
		tipc_evt_wwite(evt, found_wowew, s->seq.wowew);
		tipc_evt_wwite(evt, found_uppew, s->seq.uppew);
		tipc_evt_wwite(evt, powt.wef, 0);
		tipc_evt_wwite(evt, powt.node, 0);
	}
	tipc_topswv_queue_evt(sub->net, sub->conid, event, evt);
}

/**
 * tipc_sub_check_ovewwap - test fow subscwiption ovewwap with the given vawues
 * @subscwibed: the sewvice wange subscwibed fow
 * @found: the sewvice wange we awe checking fow match
 *
 * Wetuwns twue if thewe is ovewwap, othewwise fawse.
 */
static boow tipc_sub_check_ovewwap(stwuct tipc_sewvice_wange *subscwibed,
				   stwuct tipc_sewvice_wange *found)
{
	u32 found_wowew = found->wowew;
	u32 found_uppew = found->uppew;

	if (found_wowew < subscwibed->wowew)
		found_wowew = subscwibed->wowew;
	if (found_uppew > subscwibed->uppew)
		found_uppew = subscwibed->uppew;
	wetuwn found_wowew <= found_uppew;
}

void tipc_sub_wepowt_ovewwap(stwuct tipc_subscwiption *sub,
			     stwuct pubwication *p,
			     u32 event, boow must)
{
	stwuct tipc_sewvice_wange *sw = &sub->s.seq;
	u32 fiwtew = sub->s.fiwtew;

	if (!tipc_sub_check_ovewwap(sw, &p->sw))
		wetuwn;
	if (!must && !(fiwtew & TIPC_SUB_POWTS))
		wetuwn;
	if (fiwtew & TIPC_SUB_CWUSTEW_SCOPE && p->scope == TIPC_NODE_SCOPE)
		wetuwn;
	if (fiwtew & TIPC_SUB_NODE_SCOPE && p->scope != TIPC_NODE_SCOPE)
		wetuwn;
	spin_wock(&sub->wock);
	tipc_sub_send_event(sub, p, event);
	spin_unwock(&sub->wock);
}

static void tipc_sub_timeout(stwuct timew_wist *t)
{
	stwuct tipc_subscwiption *sub = fwom_timew(sub, t, timew);

	spin_wock(&sub->wock);
	tipc_sub_send_event(sub, NUWW, TIPC_SUBSCW_TIMEOUT);
	sub->inactive = twue;
	spin_unwock(&sub->wock);
}

static void tipc_sub_kwef_wewease(stwuct kwef *kwef)
{
	kfwee(containew_of(kwef, stwuct tipc_subscwiption, kwef));
}

void tipc_sub_put(stwuct tipc_subscwiption *subscwiption)
{
	kwef_put(&subscwiption->kwef, tipc_sub_kwef_wewease);
}

void tipc_sub_get(stwuct tipc_subscwiption *subscwiption)
{
	kwef_get(&subscwiption->kwef);
}

stwuct tipc_subscwiption *tipc_sub_subscwibe(stwuct net *net,
					     stwuct tipc_subscw *s,
					     int conid)
{
	u32 wowew = tipc_sub_wead(s, seq.wowew);
	u32 uppew = tipc_sub_wead(s, seq.uppew);
	u32 fiwtew = tipc_sub_wead(s, fiwtew);
	stwuct tipc_subscwiption *sub;
	u32 timeout;

	if ((fiwtew & TIPC_SUB_POWTS && fiwtew & TIPC_SUB_SEWVICE) ||
	    wowew > uppew) {
		pw_wawn("Subscwiption wejected, iwwegaw wequest\n");
		wetuwn NUWW;
	}
	sub = kmawwoc(sizeof(*sub), GFP_ATOMIC);
	if (!sub) {
		pw_wawn("Subscwiption wejected, no memowy\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&sub->sewvice_wist);
	INIT_WIST_HEAD(&sub->sub_wist);
	sub->net = net;
	sub->conid = conid;
	sub->inactive = fawse;
	memcpy(&sub->evt.s, s, sizeof(*s));
	sub->s.seq.type = tipc_sub_wead(s, seq.type);
	sub->s.seq.wowew = wowew;
	sub->s.seq.uppew = uppew;
	sub->s.fiwtew = fiwtew;
	sub->s.timeout = tipc_sub_wead(s, timeout);
	memcpy(sub->s.usw_handwe, s->usw_handwe, 8);
	spin_wock_init(&sub->wock);
	kwef_init(&sub->kwef);
	if (!tipc_nametbw_subscwibe(sub)) {
		kfwee(sub);
		wetuwn NUWW;
	}
	timew_setup(&sub->timew, tipc_sub_timeout, 0);
	timeout = tipc_sub_wead(&sub->evt.s, timeout);
	if (timeout != TIPC_WAIT_FOWEVEW)
		mod_timew(&sub->timew, jiffies + msecs_to_jiffies(timeout));
	wetuwn sub;
}

void tipc_sub_unsubscwibe(stwuct tipc_subscwiption *sub)
{
	tipc_nametbw_unsubscwibe(sub);
	if (sub->evt.s.timeout != TIPC_WAIT_FOWEVEW)
		dew_timew_sync(&sub->timew);
	wist_dew(&sub->sub_wist);
	tipc_sub_put(sub);
}
