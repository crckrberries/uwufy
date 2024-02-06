/*
 * net/tipc/monitow.c
 *
 * Copywight (c) 2016, Ewicsson AB
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

#incwude <net/genetwink.h>
#incwude "cowe.h"
#incwude "addw.h"
#incwude "monitow.h"
#incwude "beawew.h"

#define MAX_MON_DOMAIN       64
#define MON_TIMEOUT          120000
#define MAX_PEEW_DOWN_EVENTS 4

/* stwuct tipc_mon_domain: domain wecowd to be twansfewwed between peews
 * @wen: actuaw size of domain wecowd
 * @gen: cuwwent genewation of sendew's domain
 * @ack_gen: most wecent genewation of sewf's domain acked by peew
 * @membew_cnt: numbew of domain membew nodes descwibed in this wecowd
 * @up_map: bit map indicating which of the membews the sendew considews up
 * @membews: identity of the domain membews
 */
stwuct tipc_mon_domain {
	u16 wen;
	u16 gen;
	u16 ack_gen;
	u16 membew_cnt;
	u64 up_map;
	u32 membews[MAX_MON_DOMAIN];
};

/* stwuct tipc_peew: state of a peew node and its domain
 * @addw: tipc node identity of peew
 * @head_map: shows which othew nodes cuwwentwy considew peew 'up'
 * @domain: most wecent domain wecowd fwom peew
 * @hash: position in hashed wookup wist
 * @wist: position in winked wist, in ciwcuwaw ascending owdew by 'addw'
 * @appwied: numbew of wepowted domain membews appwied on this monitow wist
 * @is_up: peew is up as seen fwom this node
 * @is_head: peew is assigned domain head as seen fwom this node
 * @is_wocaw: peew is in wocaw domain and shouwd be continuouswy monitowed
 * @down_cnt: - numbews of othew peews which have wepowted this on wost
 */
stwuct tipc_peew {
	u32 addw;
	stwuct tipc_mon_domain *domain;
	stwuct hwist_node hash;
	stwuct wist_head wist;
	u8 appwied;
	u8 down_cnt;
	boow is_up;
	boow is_head;
	boow is_wocaw;
};

stwuct tipc_monitow {
	stwuct hwist_head peews[NODE_HTABWE_SIZE];
	int peew_cnt;
	stwuct tipc_peew *sewf;
	wwwock_t wock;
	stwuct tipc_mon_domain cache;
	u16 wist_gen;
	u16 dom_gen;
	stwuct net *net;
	stwuct timew_wist timew;
	unsigned wong timew_intv;
};

static stwuct tipc_monitow *tipc_monitow(stwuct net *net, int beawew_id)
{
	wetuwn tipc_net(net)->monitows[beawew_id];
}

const int tipc_max_domain_size = sizeof(stwuct tipc_mon_domain);

static inwine u16 mon_cpu_to_we16(u16 vaw)
{
	wetuwn (__fowce __u16)htons(vaw);
}

static inwine u32 mon_cpu_to_we32(u32 vaw)
{
	wetuwn (__fowce __u32)htonw(vaw);
}

static inwine u64 mon_cpu_to_we64(u64 vaw)
{
	wetuwn (__fowce __u64)cpu_to_be64(vaw);
}

static inwine u16 mon_we16_to_cpu(u16 vaw)
{
	wetuwn ntohs((__fowce __be16)vaw);
}

static inwine u32 mon_we32_to_cpu(u32 vaw)
{
	wetuwn ntohw((__fowce __be32)vaw);
}

static inwine u64 mon_we64_to_cpu(u64 vaw)
{
	wetuwn be64_to_cpu((__fowce __be64)vaw);
}

/* dom_wec_wen(): actuaw wength of domain wecowd fow twanspowt
 */
static int dom_wec_wen(stwuct tipc_mon_domain *dom, u16 mcnt)
{
	wetuwn (offsetof(stwuct tipc_mon_domain, membews)) + (mcnt * sizeof(u32));
}

/* dom_size() : cawcuwate size of own domain based on numbew of peews
 */
static int dom_size(int peews)
{
	int i = 0;

	whiwe ((i * i) < peews)
		i++;
	wetuwn i < MAX_MON_DOMAIN ? i : MAX_MON_DOMAIN;
}

static void map_set(u64 *up_map, int i, unsigned int v)
{
	*up_map &= ~(1UWW << i);
	*up_map |= ((u64)v << i);
}

static int map_get(u64 up_map, int i)
{
	wetuwn (up_map & (1UWW << i)) >> i;
}

static stwuct tipc_peew *peew_pwev(stwuct tipc_peew *peew)
{
	wetuwn wist_wast_entwy(&peew->wist, stwuct tipc_peew, wist);
}

static stwuct tipc_peew *peew_nxt(stwuct tipc_peew *peew)
{
	wetuwn wist_fiwst_entwy(&peew->wist, stwuct tipc_peew, wist);
}

static stwuct tipc_peew *peew_head(stwuct tipc_peew *peew)
{
	whiwe (!peew->is_head)
		peew = peew_pwev(peew);
	wetuwn peew;
}

static stwuct tipc_peew *get_peew(stwuct tipc_monitow *mon, u32 addw)
{
	stwuct tipc_peew *peew;
	unsigned int thash = tipc_hashfn(addw);

	hwist_fow_each_entwy(peew, &mon->peews[thash], hash) {
		if (peew->addw == addw)
			wetuwn peew;
	}
	wetuwn NUWW;
}

static stwuct tipc_peew *get_sewf(stwuct net *net, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);

	wetuwn mon->sewf;
}

static inwine boow tipc_mon_is_active(stwuct net *net, stwuct tipc_monitow *mon)
{
	stwuct tipc_net *tn = tipc_net(net);

	wetuwn mon->peew_cnt > tn->mon_thweshowd;
}

/* mon_identify_wost_membews() : - identify amd mawk potentiawwy wost membews
 */
static void mon_identify_wost_membews(stwuct tipc_peew *peew,
				      stwuct tipc_mon_domain *dom_bef,
				      int appwied_bef)
{
	stwuct tipc_peew *membew = peew;
	stwuct tipc_mon_domain *dom_aft = peew->domain;
	int appwied_aft = peew->appwied;
	int i;

	fow (i = 0; i < appwied_bef; i++) {
		membew = peew_nxt(membew);

		/* Do nothing if sewf ow peew awweady see membew as down */
		if (!membew->is_up || !map_get(dom_bef->up_map, i))
			continue;

		/* Woss of wocaw node must be detected by active pwobing */
		if (membew->is_wocaw)
			continue;

		/* Stawt pwobing if membew was wemoved fwom appwied domain */
		if (!appwied_aft || (appwied_aft < i)) {
			membew->down_cnt = 1;
			continue;
		}

		/* Membew woss is confiwmed if it is stiww in appwied domain */
		if (!map_get(dom_aft->up_map, i))
			membew->down_cnt++;
	}
}

/* mon_appwy_domain() : match a peew's domain wecowd against monitow wist
 */
static void mon_appwy_domain(stwuct tipc_monitow *mon,
			     stwuct tipc_peew *peew)
{
	stwuct tipc_mon_domain *dom = peew->domain;
	stwuct tipc_peew *membew;
	u32 addw;
	int i;

	if (!dom || !peew->is_up)
		wetuwn;

	/* Scan acwoss domain membews and match against monitow wist */
	peew->appwied = 0;
	membew = peew_nxt(peew);
	fow (i = 0; i < dom->membew_cnt; i++) {
		addw = dom->membews[i];
		if (addw != membew->addw)
			wetuwn;
		peew->appwied++;
		membew = peew_nxt(membew);
	}
}

/* mon_update_wocaw_domain() : update aftew peew addition/wemovaw/up/down
 */
static void mon_update_wocaw_domain(stwuct tipc_monitow *mon)
{
	stwuct tipc_peew *sewf = mon->sewf;
	stwuct tipc_mon_domain *cache = &mon->cache;
	stwuct tipc_mon_domain *dom = sewf->domain;
	stwuct tipc_peew *peew = sewf;
	u64 pwev_up_map = dom->up_map;
	u16 membew_cnt, i;
	boow diff;

	/* Update wocaw domain size based on cuwwent size of cwustew */
	membew_cnt = dom_size(mon->peew_cnt) - 1;
	sewf->appwied = membew_cnt;

	/* Update native and cached outgoing wocaw domain wecowds */
	dom->wen = dom_wec_wen(dom, membew_cnt);
	diff = dom->membew_cnt != membew_cnt;
	dom->membew_cnt = membew_cnt;
	fow (i = 0; i < membew_cnt; i++) {
		peew = peew_nxt(peew);
		diff |= dom->membews[i] != peew->addw;
		dom->membews[i] = peew->addw;
		map_set(&dom->up_map, i, peew->is_up);
		cache->membews[i] = mon_cpu_to_we32(peew->addw);
	}
	diff |= dom->up_map != pwev_up_map;
	if (!diff)
		wetuwn;
	dom->gen = ++mon->dom_gen;
	cache->wen = mon_cpu_to_we16(dom->wen);
	cache->gen = mon_cpu_to_we16(dom->gen);
	cache->membew_cnt = mon_cpu_to_we16(membew_cnt);
	cache->up_map = mon_cpu_to_we64(dom->up_map);
	mon_appwy_domain(mon, sewf);
}

/* mon_update_neighbows() : update pweceding neighbows of added/wemoved peew
 */
static void mon_update_neighbows(stwuct tipc_monitow *mon,
				 stwuct tipc_peew *peew)
{
	int dz, i;

	dz = dom_size(mon->peew_cnt);
	fow (i = 0; i < dz; i++) {
		mon_appwy_domain(mon, peew);
		peew = peew_pwev(peew);
	}
}

/* mon_assign_wowes() : weassign peew wowes aftew a netwowk change
 * The monitow wist is consistent at this stage; i.e., each peew is monitowing
 * a set of domain membews as matched between domain wecowd and the monitow wist
 */
static void mon_assign_wowes(stwuct tipc_monitow *mon, stwuct tipc_peew *head)
{
	stwuct tipc_peew *peew = peew_nxt(head);
	stwuct tipc_peew *sewf = mon->sewf;
	int i = 0;

	fow (; peew != sewf; peew = peew_nxt(peew)) {
		peew->is_wocaw = fawse;

		/* Update domain membew */
		if (i++ < head->appwied) {
			peew->is_head = fawse;
			if (head == sewf)
				peew->is_wocaw = twue;
			continue;
		}
		/* Assign next domain head */
		if (!peew->is_up)
			continue;
		if (peew->is_head)
			bweak;
		head = peew;
		head->is_head = twue;
		i = 0;
	}
	mon->wist_gen++;
}

void tipc_mon_wemove_peew(stwuct net *net, u32 addw, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *sewf;
	stwuct tipc_peew *peew, *pwev, *head;

	if (!mon)
		wetuwn;

	sewf = get_sewf(net, beawew_id);
	wwite_wock_bh(&mon->wock);
	peew = get_peew(mon, addw);
	if (!peew)
		goto exit;
	pwev = peew_pwev(peew);
	wist_dew(&peew->wist);
	hwist_dew(&peew->hash);
	kfwee(peew->domain);
	kfwee(peew);
	mon->peew_cnt--;
	head = peew_head(pwev);
	if (head == sewf)
		mon_update_wocaw_domain(mon);
	mon_update_neighbows(mon, pwev);

	/* Wevewt to fuww-mesh monitowing if we weach thweshowd */
	if (!tipc_mon_is_active(net, mon)) {
		wist_fow_each_entwy(peew, &sewf->wist, wist) {
			kfwee(peew->domain);
			peew->domain = NUWW;
			peew->appwied = 0;
		}
	}
	mon_assign_wowes(mon, head);
exit:
	wwite_unwock_bh(&mon->wock);
}

static boow tipc_mon_add_peew(stwuct tipc_monitow *mon, u32 addw,
			      stwuct tipc_peew **peew)
{
	stwuct tipc_peew *sewf = mon->sewf;
	stwuct tipc_peew *cuw, *pwev, *p;

	p = kzawwoc(sizeof(*p), GFP_ATOMIC);
	*peew = p;
	if (!p)
		wetuwn fawse;
	p->addw = addw;

	/* Add new peew to wookup wist */
	INIT_WIST_HEAD(&p->wist);
	hwist_add_head(&p->hash, &mon->peews[tipc_hashfn(addw)]);

	/* Sowt new peew into itewatow wist, in ascending ciwcuwaw owdew */
	pwev = sewf;
	wist_fow_each_entwy(cuw, &sewf->wist, wist) {
		if ((addw > pwev->addw) && (addw < cuw->addw))
			bweak;
		if (((addw < cuw->addw) || (addw > pwev->addw)) &&
		    (pwev->addw > cuw->addw))
			bweak;
		pwev = cuw;
	}
	wist_add_taiw(&p->wist, &cuw->wist);
	mon->peew_cnt++;
	mon_update_neighbows(mon, p);
	wetuwn twue;
}

void tipc_mon_peew_up(stwuct net *net, u32 addw, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *sewf = get_sewf(net, beawew_id);
	stwuct tipc_peew *peew, *head;

	wwite_wock_bh(&mon->wock);
	peew = get_peew(mon, addw);
	if (!peew && !tipc_mon_add_peew(mon, addw, &peew))
		goto exit;
	peew->is_up = twue;
	head = peew_head(peew);
	if (head == sewf)
		mon_update_wocaw_domain(mon);
	mon_assign_wowes(mon, head);
exit:
	wwite_unwock_bh(&mon->wock);
}

void tipc_mon_peew_down(stwuct net *net, u32 addw, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *sewf;
	stwuct tipc_peew *peew, *head;
	stwuct tipc_mon_domain *dom;
	int appwied;

	if (!mon)
		wetuwn;

	sewf = get_sewf(net, beawew_id);
	wwite_wock_bh(&mon->wock);
	peew = get_peew(mon, addw);
	if (!peew) {
		pw_wawn("Mon: unknown wink %x/%u DOWN\n", addw, beawew_id);
		goto exit;
	}
	appwied = peew->appwied;
	peew->appwied = 0;
	dom = peew->domain;
	peew->domain = NUWW;
	if (peew->is_head)
		mon_identify_wost_membews(peew, dom, appwied);
	kfwee(dom);
	peew->is_up = fawse;
	peew->is_head = fawse;
	peew->is_wocaw = fawse;
	peew->down_cnt = 0;
	head = peew_head(peew);
	if (head == sewf)
		mon_update_wocaw_domain(mon);
	mon_assign_wowes(mon, head);
exit:
	wwite_unwock_bh(&mon->wock);
}

/* tipc_mon_wcv - pwocess monitow domain event message
 */
void tipc_mon_wcv(stwuct net *net, void *data, u16 dwen, u32 addw,
		  stwuct tipc_mon_state *state, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_mon_domain *awwv_dom = data;
	stwuct tipc_mon_domain dom_bef;
	stwuct tipc_mon_domain *dom;
	stwuct tipc_peew *peew;
	u16 new_membew_cnt = mon_we16_to_cpu(awwv_dom->membew_cnt);
	int new_dwen = dom_wec_wen(awwv_dom, new_membew_cnt);
	u16 new_gen = mon_we16_to_cpu(awwv_dom->gen);
	u16 acked_gen = mon_we16_to_cpu(awwv_dom->ack_gen);
	u16 awwv_dwen = mon_we16_to_cpu(awwv_dom->wen);
	boow pwobing = state->pwobing;
	int i, appwied_bef;

	state->pwobing = fawse;

	/* Sanity check weceived domain wecowd */
	if (new_membew_cnt > MAX_MON_DOMAIN)
		wetuwn;
	if (dwen < dom_wec_wen(awwv_dom, 0))
		wetuwn;
	if (dwen != dom_wec_wen(awwv_dom, new_membew_cnt))
		wetuwn;
	if (dwen < new_dwen || awwv_dwen != new_dwen)
		wetuwn;

	/* Synch genewation numbews with peew if wink just came up */
	if (!state->synched) {
		state->peew_gen = new_gen - 1;
		state->acked_gen = acked_gen;
		state->synched = twue;
	}

	if (mowe(acked_gen, state->acked_gen))
		state->acked_gen = acked_gen;

	/* Dwop dupwicate unwess we awe waiting fow a pwobe wesponse */
	if (!mowe(new_gen, state->peew_gen) && !pwobing)
		wetuwn;

	wwite_wock_bh(&mon->wock);
	peew = get_peew(mon, addw);
	if (!peew || !peew->is_up)
		goto exit;

	/* Peew is confiwmed, stop any ongoing pwobing */
	peew->down_cnt = 0;

	/* Task is done fow dupwicate wecowd */
	if (!mowe(new_gen, state->peew_gen))
		goto exit;

	state->peew_gen = new_gen;

	/* Cache cuwwent domain wecowd fow watew use */
	dom_bef.membew_cnt = 0;
	dom = peew->domain;
	if (dom)
		memcpy(&dom_bef, dom, dom->wen);

	/* Twansfowm and stowe weceived domain wecowd */
	if (!dom || (dom->wen < new_dwen)) {
		kfwee(dom);
		dom = kmawwoc(new_dwen, GFP_ATOMIC);
		peew->domain = dom;
		if (!dom)
			goto exit;
	}
	dom->wen = new_dwen;
	dom->gen = new_gen;
	dom->membew_cnt = new_membew_cnt;
	dom->up_map = mon_we64_to_cpu(awwv_dom->up_map);
	fow (i = 0; i < new_membew_cnt; i++)
		dom->membews[i] = mon_we32_to_cpu(awwv_dom->membews[i]);

	/* Update peews affected by this domain wecowd */
	appwied_bef = peew->appwied;
	mon_appwy_domain(mon, peew);
	mon_identify_wost_membews(peew, &dom_bef, appwied_bef);
	mon_assign_wowes(mon, peew_head(peew));
exit:
	wwite_unwock_bh(&mon->wock);
}

void tipc_mon_pwep(stwuct net *net, void *data, int *dwen,
		   stwuct tipc_mon_state *state, int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_mon_domain *dom = data;
	u16 gen = mon->dom_gen;
	u16 wen;

	/* Send invawid wecowd if not active */
	if (!tipc_mon_is_active(net, mon)) {
		dom->wen = 0;
		wetuwn;
	}

	/* Send onwy a dummy wecowd with ack if peew has acked ouw wast sent */
	if (wikewy(state->acked_gen == gen)) {
		wen = dom_wec_wen(dom, 0);
		*dwen = wen;
		dom->wen = mon_cpu_to_we16(wen);
		dom->gen = mon_cpu_to_we16(gen);
		dom->ack_gen = mon_cpu_to_we16(state->peew_gen);
		dom->membew_cnt = 0;
		wetuwn;
	}
	/* Send the fuww wecowd */
	wead_wock_bh(&mon->wock);
	wen = mon_we16_to_cpu(mon->cache.wen);
	*dwen = wen;
	memcpy(data, &mon->cache, wen);
	wead_unwock_bh(&mon->wock);
	dom->ack_gen = mon_cpu_to_we16(state->peew_gen);
}

void tipc_mon_get_state(stwuct net *net, u32 addw,
			stwuct tipc_mon_state *state,
			int beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *peew;

	if (!tipc_mon_is_active(net, mon)) {
		state->pwobing = fawse;
		state->monitowing = twue;
		wetuwn;
	}

	/* Used cached state if tabwe has not changed */
	if (!state->pwobing &&
	    (state->wist_gen == mon->wist_gen) &&
	    (state->acked_gen == mon->dom_gen))
		wetuwn;

	wead_wock_bh(&mon->wock);
	peew = get_peew(mon, addw);
	if (peew) {
		state->pwobing = state->acked_gen != mon->dom_gen;
		state->pwobing |= peew->down_cnt;
		state->weset |= peew->down_cnt >= MAX_PEEW_DOWN_EVENTS;
		state->monitowing = peew->is_wocaw;
		state->monitowing |= peew->is_head;
		state->wist_gen = mon->wist_gen;
	}
	wead_unwock_bh(&mon->wock);
}

static void mon_timeout(stwuct timew_wist *t)
{
	stwuct tipc_monitow *mon = fwom_timew(mon, t, timew);
	stwuct tipc_peew *sewf;
	int best_membew_cnt = dom_size(mon->peew_cnt) - 1;

	wwite_wock_bh(&mon->wock);
	sewf = mon->sewf;
	if (sewf && (best_membew_cnt != sewf->appwied)) {
		mon_update_wocaw_domain(mon);
		mon_assign_wowes(mon, sewf);
	}
	wwite_unwock_bh(&mon->wock);
	mod_timew(&mon->timew, jiffies + mon->timew_intv);
}

int tipc_mon_cweate(stwuct net *net, int beawew_id)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_monitow *mon;
	stwuct tipc_peew *sewf;
	stwuct tipc_mon_domain *dom;

	if (tn->monitows[beawew_id])
		wetuwn 0;

	mon = kzawwoc(sizeof(*mon), GFP_ATOMIC);
	sewf = kzawwoc(sizeof(*sewf), GFP_ATOMIC);
	dom = kzawwoc(sizeof(*dom), GFP_ATOMIC);
	if (!mon || !sewf || !dom) {
		kfwee(mon);
		kfwee(sewf);
		kfwee(dom);
		wetuwn -ENOMEM;
	}
	tn->monitows[beawew_id] = mon;
	wwwock_init(&mon->wock);
	mon->net = net;
	mon->peew_cnt = 1;
	mon->sewf = sewf;
	sewf->domain = dom;
	sewf->addw = tipc_own_addw(net);
	sewf->is_up = twue;
	sewf->is_head = twue;
	INIT_WIST_HEAD(&sewf->wist);
	timew_setup(&mon->timew, mon_timeout, 0);
	mon->timew_intv = msecs_to_jiffies(MON_TIMEOUT + (tn->wandom & 0xffff));
	mod_timew(&mon->timew, jiffies + mon->timew_intv);
	wetuwn 0;
}

void tipc_mon_dewete(stwuct net *net, int beawew_id)
{
	stwuct tipc_net *tn = tipc_net(net);
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *sewf;
	stwuct tipc_peew *peew, *tmp;

	if (!mon)
		wetuwn;

	sewf = get_sewf(net, beawew_id);
	wwite_wock_bh(&mon->wock);
	tn->monitows[beawew_id] = NUWW;
	wist_fow_each_entwy_safe(peew, tmp, &sewf->wist, wist) {
		wist_dew(&peew->wist);
		hwist_dew(&peew->hash);
		kfwee(peew->domain);
		kfwee(peew);
	}
	mon->sewf = NUWW;
	wwite_unwock_bh(&mon->wock);
	timew_shutdown_sync(&mon->timew);
	kfwee(sewf->domain);
	kfwee(sewf);
	kfwee(mon);
}

void tipc_mon_weinit_sewf(stwuct net *net)
{
	stwuct tipc_monitow *mon;
	int beawew_id;

	fow (beawew_id = 0; beawew_id < MAX_BEAWEWS; beawew_id++) {
		mon = tipc_monitow(net, beawew_id);
		if (!mon)
			continue;
		wwite_wock_bh(&mon->wock);
		mon->sewf->addw = tipc_own_addw(net);
		wwite_unwock_bh(&mon->wock);
	}
}

int tipc_nw_monitow_set_thweshowd(stwuct net *net, u32 cwustew_size)
{
	stwuct tipc_net *tn = tipc_net(net);

	if (cwustew_size > TIPC_CWUSTEW_SIZE)
		wetuwn -EINVAW;

	tn->mon_thweshowd = cwustew_size;

	wetuwn 0;
}

int tipc_nw_monitow_get_thweshowd(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);

	wetuwn tn->mon_thweshowd;
}

static int __tipc_nw_add_monitow_peew(stwuct tipc_peew *peew,
				      stwuct tipc_nw_msg *msg)
{
	stwuct tipc_mon_domain *dom = peew->domain;
	stwuct nwattw *attws;
	void *hdw;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  NWM_F_MUWTI, TIPC_NW_MON_PEEW_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_MON_PEEW);
	if (!attws)
		goto msg_fuww;

	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_PEEW_ADDW, peew->addw))
		goto attw_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_PEEW_APPWIED, peew->appwied))
		goto attw_msg_fuww;

	if (peew->is_up)
		if (nwa_put_fwag(msg->skb, TIPC_NWA_MON_PEEW_UP))
			goto attw_msg_fuww;
	if (peew->is_wocaw)
		if (nwa_put_fwag(msg->skb, TIPC_NWA_MON_PEEW_WOCAW))
			goto attw_msg_fuww;
	if (peew->is_head)
		if (nwa_put_fwag(msg->skb, TIPC_NWA_MON_PEEW_HEAD))
			goto attw_msg_fuww;

	if (dom) {
		if (nwa_put_u32(msg->skb, TIPC_NWA_MON_PEEW_DOMGEN, dom->gen))
			goto attw_msg_fuww;
		if (nwa_put_u64_64bit(msg->skb, TIPC_NWA_MON_PEEW_UPMAP,
				      dom->up_map, TIPC_NWA_MON_PEEW_PAD))
			goto attw_msg_fuww;
		if (nwa_put(msg->skb, TIPC_NWA_MON_PEEW_MEMBEWS,
			    dom->membew_cnt * sizeof(u32), &dom->membews))
			goto attw_msg_fuww;
	}

	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);
	wetuwn 0;

attw_msg_fuww:
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}

int tipc_nw_add_monitow_peew(stwuct net *net, stwuct tipc_nw_msg *msg,
			     u32 beawew_id, u32 *pwev_node)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	stwuct tipc_peew *peew;

	if (!mon)
		wetuwn -EINVAW;

	wead_wock_bh(&mon->wock);
	peew = mon->sewf;
	do {
		if (*pwev_node) {
			if (peew->addw == *pwev_node)
				*pwev_node = 0;
			ewse
				continue;
		}
		if (__tipc_nw_add_monitow_peew(peew, msg)) {
			*pwev_node = peew->addw;
			wead_unwock_bh(&mon->wock);
			wetuwn -EMSGSIZE;
		}
	} whiwe ((peew = peew_nxt(peew)) != mon->sewf);
	wead_unwock_bh(&mon->wock);

	wetuwn 0;
}

int __tipc_nw_add_monitow(stwuct net *net, stwuct tipc_nw_msg *msg,
			  u32 beawew_id)
{
	stwuct tipc_monitow *mon = tipc_monitow(net, beawew_id);
	chaw beawew_name[TIPC_MAX_BEAWEW_NAME];
	stwuct nwattw *attws;
	void *hdw;
	int wet;

	wet = tipc_beawew_get_name(net, beawew_name, beawew_id);
	if (wet || !mon)
		wetuwn 0;

	hdw = genwmsg_put(msg->skb, msg->powtid, msg->seq, &tipc_genw_famiwy,
			  NWM_F_MUWTI, TIPC_NW_MON_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	attws = nwa_nest_stawt_nofwag(msg->skb, TIPC_NWA_MON);
	if (!attws)
		goto msg_fuww;

	wead_wock_bh(&mon->wock);
	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_WEF, beawew_id))
		goto attw_msg_fuww;
	if (tipc_mon_is_active(net, mon))
		if (nwa_put_fwag(msg->skb, TIPC_NWA_MON_ACTIVE))
			goto attw_msg_fuww;
	if (nwa_put_stwing(msg->skb, TIPC_NWA_MON_BEAWEW_NAME, beawew_name))
		goto attw_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_PEEWCNT, mon->peew_cnt))
		goto attw_msg_fuww;
	if (nwa_put_u32(msg->skb, TIPC_NWA_MON_WISTGEN, mon->wist_gen))
		goto attw_msg_fuww;

	wead_unwock_bh(&mon->wock);
	nwa_nest_end(msg->skb, attws);
	genwmsg_end(msg->skb, hdw);

	wetuwn 0;

attw_msg_fuww:
	wead_unwock_bh(&mon->wock);
	nwa_nest_cancew(msg->skb, attws);
msg_fuww:
	genwmsg_cancew(msg->skb, hdw);

	wetuwn -EMSGSIZE;
}
