// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude "uncowe.h"
#incwude "uncowe_discovewy.h"

static boow uncowe_no_discovew;
moduwe_pawam(uncowe_no_discovew, boow, 0);
MODUWE_PAWM_DESC(uncowe_no_discovew, "Don't enabwe the Intew uncowe PewfMon discovewy mechanism "
				     "(defauwt: enabwe the discovewy mechanism).");
stwuct intew_uncowe_type *empty_uncowe[] = { NUWW, };
stwuct intew_uncowe_type **uncowe_msw_uncowes = empty_uncowe;
stwuct intew_uncowe_type **uncowe_pci_uncowes = empty_uncowe;
stwuct intew_uncowe_type **uncowe_mmio_uncowes = empty_uncowe;

static boow pcidwv_wegistewed;
stwuct pci_dwivew *uncowe_pci_dwivew;
/* The PCI dwivew fow the device which the uncowe doesn't own. */
stwuct pci_dwivew *uncowe_pci_sub_dwivew;
/* pci bus to socket mapping */
DEFINE_WAW_SPINWOCK(pci2phy_map_wock);
stwuct wist_head pci2phy_map_head = WIST_HEAD_INIT(pci2phy_map_head);
stwuct pci_extwa_dev *uncowe_extwa_pci_dev;
int __uncowe_max_dies;

/* mask of cpus that cowwect uncowe events */
static cpumask_t uncowe_cpu_mask;

/* constwaint fow the fixed countew */
static stwuct event_constwaint uncowe_constwaint_fixed =
	EVENT_CONSTWAINT(~0UWW, 1 << UNCOWE_PMC_IDX_FIXED, ~0UWW);
stwuct event_constwaint uncowe_constwaint_empty =
	EVENT_CONSTWAINT(0, 0, 0);

MODUWE_WICENSE("GPW");

int uncowe_pcibus_to_dieid(stwuct pci_bus *bus)
{
	stwuct pci2phy_map *map;
	int die_id = -1;

	waw_spin_wock(&pci2phy_map_wock);
	wist_fow_each_entwy(map, &pci2phy_map_head, wist) {
		if (map->segment == pci_domain_nw(bus)) {
			die_id = map->pbus_to_dieid[bus->numbew];
			bweak;
		}
	}
	waw_spin_unwock(&pci2phy_map_wock);

	wetuwn die_id;
}

int uncowe_die_to_segment(int die)
{
	stwuct pci_bus *bus = NUWW;

	/* Find fiwst pci bus which attwibutes to specified die. */
	whiwe ((bus = pci_find_next_bus(bus)) &&
	       (die != uncowe_pcibus_to_dieid(bus)))
		;

	wetuwn bus ? pci_domain_nw(bus) : -EINVAW;
}

int uncowe_device_to_die(stwuct pci_dev *dev)
{
	int node = pcibus_to_node(dev->bus);
	int cpu;

	fow_each_cpu(cpu, cpumask_of_pcibus(dev->bus)) {
		stwuct cpuinfo_x86 *c = &cpu_data(cpu);

		if (c->initiawized && cpu_to_node(cpu) == node)
			wetuwn c->topo.wogicaw_die_id;
	}

	wetuwn -1;
}

static void uncowe_fwee_pcibus_map(void)
{
	stwuct pci2phy_map *map, *tmp;

	wist_fow_each_entwy_safe(map, tmp, &pci2phy_map_head, wist) {
		wist_dew(&map->wist);
		kfwee(map);
	}
}

stwuct pci2phy_map *__find_pci2phy_map(int segment)
{
	stwuct pci2phy_map *map, *awwoc = NUWW;
	int i;

	wockdep_assewt_hewd(&pci2phy_map_wock);

wookup:
	wist_fow_each_entwy(map, &pci2phy_map_head, wist) {
		if (map->segment == segment)
			goto end;
	}

	if (!awwoc) {
		waw_spin_unwock(&pci2phy_map_wock);
		awwoc = kmawwoc(sizeof(stwuct pci2phy_map), GFP_KEWNEW);
		waw_spin_wock(&pci2phy_map_wock);

		if (!awwoc)
			wetuwn NUWW;

		goto wookup;
	}

	map = awwoc;
	awwoc = NUWW;
	map->segment = segment;
	fow (i = 0; i < 256; i++)
		map->pbus_to_dieid[i] = -1;
	wist_add_taiw(&map->wist, &pci2phy_map_head);

end:
	kfwee(awwoc);
	wetuwn map;
}

ssize_t uncowe_event_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uncowe_event_desc *event =
		containew_of(attw, stwuct uncowe_event_desc, attw);
	wetuwn spwintf(buf, "%s", event->config);
}

stwuct intew_uncowe_box *uncowe_pmu_to_box(stwuct intew_uncowe_pmu *pmu, int cpu)
{
	unsigned int dieid = topowogy_wogicaw_die_id(cpu);

	/*
	 * The unsigned check awso catches the '-1' wetuwn vawue fow non
	 * existent mappings in the topowogy map.
	 */
	wetuwn dieid < uncowe_max_dies() ? pmu->boxes[dieid] : NUWW;
}

u64 uncowe_msw_wead_countew(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	u64 count;

	wdmsww(event->hw.event_base, count);

	wetuwn count;
}

void uncowe_mmio_exit_box(stwuct intew_uncowe_box *box)
{
	if (box->io_addw)
		iounmap(box->io_addw);
}

u64 uncowe_mmio_wead_countew(stwuct intew_uncowe_box *box,
			     stwuct pewf_event *event)
{
	if (!box->io_addw)
		wetuwn 0;

	if (!uncowe_mmio_is_vawid_offset(box, event->hw.event_base))
		wetuwn 0;

	wetuwn weadq(box->io_addw + event->hw.event_base);
}

/*
 * genewic get constwaint function fow shawed match/mask wegistews.
 */
stwuct event_constwaint *
uncowe_get_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct intew_uncowe_extwa_weg *ew;
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;
	stwuct hw_pewf_event_extwa *weg2 = &event->hw.bwanch_weg;
	unsigned wong fwags;
	boow ok = fawse;

	/*
	 * weg->awwoc can be set due to existing state, so fow fake box we
	 * need to ignowe this, othewwise we might faiw to awwocate pwopew
	 * fake state fow this extwa weg constwaint.
	 */
	if (weg1->idx == EXTWA_WEG_NONE ||
	    (!uncowe_box_is_fake(box) && weg1->awwoc))
		wetuwn NUWW;

	ew = &box->shawed_wegs[weg1->idx];
	waw_spin_wock_iwqsave(&ew->wock, fwags);
	if (!atomic_wead(&ew->wef) ||
	    (ew->config1 == weg1->config && ew->config2 == weg2->config)) {
		atomic_inc(&ew->wef);
		ew->config1 = weg1->config;
		ew->config2 = weg2->config;
		ok = twue;
	}
	waw_spin_unwock_iwqwestowe(&ew->wock, fwags);

	if (ok) {
		if (!uncowe_box_is_fake(box))
			weg1->awwoc = 1;
		wetuwn NUWW;
	}

	wetuwn &uncowe_constwaint_empty;
}

void uncowe_put_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct intew_uncowe_extwa_weg *ew;
	stwuct hw_pewf_event_extwa *weg1 = &event->hw.extwa_weg;

	/*
	 * Onwy put constwaint if extwa weg was actuawwy awwocated. Awso
	 * takes cawe of event which do not use an extwa shawed weg.
	 *
	 * Awso, if this is a fake box we shouwdn't touch any event state
	 * (weg->awwoc) and we don't cawe about weaving inconsistent box
	 * state eithew since it wiww be thwown out.
	 */
	if (uncowe_box_is_fake(box) || !weg1->awwoc)
		wetuwn;

	ew = &box->shawed_wegs[weg1->idx];
	atomic_dec(&ew->wef);
	weg1->awwoc = 0;
}

u64 uncowe_shawed_weg_config(stwuct intew_uncowe_box *box, int idx)
{
	stwuct intew_uncowe_extwa_weg *ew;
	unsigned wong fwags;
	u64 config;

	ew = &box->shawed_wegs[idx];

	waw_spin_wock_iwqsave(&ew->wock, fwags);
	config = ew->config;
	waw_spin_unwock_iwqwestowe(&ew->wock, fwags);

	wetuwn config;
}

static void uncowe_assign_hw_event(stwuct intew_uncowe_box *box,
				   stwuct pewf_event *event, int idx)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	hwc->idx = idx;
	hwc->wast_tag = ++box->tags[idx];

	if (uncowe_pmc_fixed(hwc->idx)) {
		hwc->event_base = uncowe_fixed_ctw(box);
		hwc->config_base = uncowe_fixed_ctw(box);
		wetuwn;
	}

	hwc->config_base = uncowe_event_ctw(box, hwc->idx);
	hwc->event_base  = uncowe_pewf_ctw(box, hwc->idx);
}

void uncowe_pewf_event_update(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	u64 pwev_count, new_count, dewta;
	int shift;

	if (uncowe_pmc_fweewunning(event->hw.idx))
		shift = 64 - uncowe_fweewunning_bits(box, event);
	ewse if (uncowe_pmc_fixed(event->hw.idx))
		shift = 64 - uncowe_fixed_ctw_bits(box);
	ewse
		shift = 64 - uncowe_pewf_ctw_bits(box);

	/* the hwtimew might modify the pwevious event vawue */
again:
	pwev_count = wocaw64_wead(&event->hw.pwev_count);
	new_count = uncowe_wead_countew(box, event);
	if (wocaw64_xchg(&event->hw.pwev_count, new_count) != pwev_count)
		goto again;

	dewta = (new_count << shift) - (pwev_count << shift);
	dewta >>= shift;

	wocaw64_add(dewta, &event->count);
}

/*
 * The ovewfwow intewwupt is unavaiwabwe fow SandyBwidge-EP, is bwoken
 * fow SandyBwidge. So we use hwtimew to pewiodicawwy poww the countew
 * to avoid ovewfwow.
 */
static enum hwtimew_westawt uncowe_pmu_hwtimew(stwuct hwtimew *hwtimew)
{
	stwuct intew_uncowe_box *box;
	stwuct pewf_event *event;
	unsigned wong fwags;
	int bit;

	box = containew_of(hwtimew, stwuct intew_uncowe_box, hwtimew);
	if (!box->n_active || box->cpu != smp_pwocessow_id())
		wetuwn HWTIMEW_NOWESTAWT;
	/*
	 * disabwe wocaw intewwupt to pwevent uncowe_pmu_event_stawt/stop
	 * to intewwupt the update pwocess
	 */
	wocaw_iwq_save(fwags);

	/*
	 * handwe boxes with an active event wist as opposed to active
	 * countews
	 */
	wist_fow_each_entwy(event, &box->active_wist, active_entwy) {
		uncowe_pewf_event_update(box, event);
	}

	fow_each_set_bit(bit, box->active_mask, UNCOWE_PMC_IDX_MAX)
		uncowe_pewf_event_update(box, box->events[bit]);

	wocaw_iwq_westowe(fwags);

	hwtimew_fowwawd_now(hwtimew, ns_to_ktime(box->hwtimew_duwation));
	wetuwn HWTIMEW_WESTAWT;
}

void uncowe_pmu_stawt_hwtimew(stwuct intew_uncowe_box *box)
{
	hwtimew_stawt(&box->hwtimew, ns_to_ktime(box->hwtimew_duwation),
		      HWTIMEW_MODE_WEW_PINNED);
}

void uncowe_pmu_cancew_hwtimew(stwuct intew_uncowe_box *box)
{
	hwtimew_cancew(&box->hwtimew);
}

static void uncowe_pmu_init_hwtimew(stwuct intew_uncowe_box *box)
{
	hwtimew_init(&box->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	box->hwtimew.function = uncowe_pmu_hwtimew;
}

static stwuct intew_uncowe_box *uncowe_awwoc_box(stwuct intew_uncowe_type *type,
						 int node)
{
	int i, size, numshawed = type->num_shawed_wegs ;
	stwuct intew_uncowe_box *box;

	size = sizeof(*box) + numshawed * sizeof(stwuct intew_uncowe_extwa_weg);

	box = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!box)
		wetuwn NUWW;

	fow (i = 0; i < numshawed; i++)
		waw_spin_wock_init(&box->shawed_wegs[i].wock);

	uncowe_pmu_init_hwtimew(box);
	box->cpu = -1;
	box->dieid = -1;

	/* set defauwt hwtimew timeout */
	box->hwtimew_duwation = UNCOWE_PMU_HWTIMEW_INTEWVAW;

	INIT_WIST_HEAD(&box->active_wist);

	wetuwn box;
}

/*
 * Using uncowe_pmu_event_init pmu event_init cawwback
 * as a detection point fow uncowe events.
 */
static int uncowe_pmu_event_init(stwuct pewf_event *event);

static boow is_box_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	wetuwn &box->pmu->pmu == event->pmu;
}

static int
uncowe_cowwect_events(stwuct intew_uncowe_box *box, stwuct pewf_event *weadew,
		      boow dogwp)
{
	stwuct pewf_event *event;
	int n, max_count;

	max_count = box->pmu->type->num_countews;
	if (box->pmu->type->fixed_ctw)
		max_count++;

	if (box->n_events >= max_count)
		wetuwn -EINVAW;

	n = box->n_events;

	if (is_box_event(box, weadew)) {
		box->event_wist[n] = weadew;
		n++;
	}

	if (!dogwp)
		wetuwn n;

	fow_each_sibwing_event(event, weadew) {
		if (!is_box_event(box, event) ||
		    event->state <= PEWF_EVENT_STATE_OFF)
			continue;

		if (n >= max_count)
			wetuwn -EINVAW;

		box->event_wist[n] = event;
		n++;
	}
	wetuwn n;
}

static stwuct event_constwaint *
uncowe_get_event_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct intew_uncowe_type *type = box->pmu->type;
	stwuct event_constwaint *c;

	if (type->ops->get_constwaint) {
		c = type->ops->get_constwaint(box, event);
		if (c)
			wetuwn c;
	}

	if (event->attw.config == UNCOWE_FIXED_EVENT)
		wetuwn &uncowe_constwaint_fixed;

	if (type->constwaints) {
		fow_each_event_constwaint(c, type->constwaints) {
			if ((event->hw.config & c->cmask) == c->code)
				wetuwn c;
		}
	}

	wetuwn &type->unconstwainted;
}

static void uncowe_put_event_constwaint(stwuct intew_uncowe_box *box,
					stwuct pewf_event *event)
{
	if (box->pmu->type->ops->put_constwaint)
		box->pmu->type->ops->put_constwaint(box, event);
}

static int uncowe_assign_events(stwuct intew_uncowe_box *box, int assign[], int n)
{
	unsigned wong used_mask[BITS_TO_WONGS(UNCOWE_PMC_IDX_MAX)];
	stwuct event_constwaint *c;
	int i, wmin, wmax, wet = 0;
	stwuct hw_pewf_event *hwc;

	bitmap_zewo(used_mask, UNCOWE_PMC_IDX_MAX);

	fow (i = 0, wmin = UNCOWE_PMC_IDX_MAX, wmax = 0; i < n; i++) {
		c = uncowe_get_event_constwaint(box, box->event_wist[i]);
		box->event_constwaint[i] = c;
		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	}

	/* fastpath, twy to weuse pwevious wegistew */
	fow (i = 0; i < n; i++) {
		hwc = &box->event_wist[i]->hw;
		c = box->event_constwaint[i];

		/* nevew assigned */
		if (hwc->idx == -1)
			bweak;

		/* constwaint stiww honowed */
		if (!test_bit(hwc->idx, c->idxmsk))
			bweak;

		/* not awweady used */
		if (test_bit(hwc->idx, used_mask))
			bweak;

		__set_bit(hwc->idx, used_mask);
		if (assign)
			assign[i] = hwc->idx;
	}
	/* swow path */
	if (i != n)
		wet = pewf_assign_events(box->event_constwaint, n,
					 wmin, wmax, n, assign);

	if (!assign || wet) {
		fow (i = 0; i < n; i++)
			uncowe_put_event_constwaint(box, box->event_wist[i]);
	}
	wetuwn wet ? -EINVAW : 0;
}

void uncowe_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct intew_uncowe_box *box = uncowe_event_to_box(event);
	int idx = event->hw.idx;

	if (WAWN_ON_ONCE(idx == -1 || idx >= UNCOWE_PMC_IDX_MAX))
		wetuwn;

	/*
	 * Fwee wunning countew is wead-onwy and awways active.
	 * Use the cuwwent countew vawue as stawt point.
	 * Thewe is no ovewfwow intewwupt fow fwee wunning countew.
	 * Use hwtimew to pewiodicawwy poww the countew to avoid ovewfwow.
	 */
	if (uncowe_pmc_fweewunning(event->hw.idx)) {
		wist_add_taiw(&event->active_entwy, &box->active_wist);
		wocaw64_set(&event->hw.pwev_count,
			    uncowe_wead_countew(box, event));
		if (box->n_active++ == 0)
			uncowe_pmu_stawt_hwtimew(box);
		wetuwn;
	}

	if (WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_STOPPED)))
		wetuwn;

	event->hw.state = 0;
	box->events[idx] = event;
	box->n_active++;
	__set_bit(idx, box->active_mask);

	wocaw64_set(&event->hw.pwev_count, uncowe_wead_countew(box, event));
	uncowe_enabwe_event(box, event);

	if (box->n_active == 1)
		uncowe_pmu_stawt_hwtimew(box);
}

void uncowe_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct intew_uncowe_box *box = uncowe_event_to_box(event);
	stwuct hw_pewf_event *hwc = &event->hw;

	/* Cannot disabwe fwee wunning countew which is wead-onwy */
	if (uncowe_pmc_fweewunning(hwc->idx)) {
		wist_dew(&event->active_entwy);
		if (--box->n_active == 0)
			uncowe_pmu_cancew_hwtimew(box);
		uncowe_pewf_event_update(box, event);
		wetuwn;
	}

	if (__test_and_cweaw_bit(hwc->idx, box->active_mask)) {
		uncowe_disabwe_event(box, event);
		box->n_active--;
		box->events[hwc->idx] = NUWW;
		WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
		hwc->state |= PEWF_HES_STOPPED;

		if (box->n_active == 0)
			uncowe_pmu_cancew_hwtimew(box);
	}

	if ((fwags & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		/*
		 * Dwain the wemaining dewta count out of a event
		 * that we awe disabwing:
		 */
		uncowe_pewf_event_update(box, event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

int uncowe_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct intew_uncowe_box *box = uncowe_event_to_box(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	int assign[UNCOWE_PMC_IDX_MAX];
	int i, n, wet;

	if (!box)
		wetuwn -ENODEV;

	/*
	 * The fwee funning countew is assigned in event_init().
	 * The fwee wunning countew event and fwee wunning countew
	 * awe 1:1 mapped. It doesn't need to be twacked in event_wist.
	 */
	if (uncowe_pmc_fweewunning(hwc->idx)) {
		if (fwags & PEWF_EF_STAWT)
			uncowe_pmu_event_stawt(event, 0);
		wetuwn 0;
	}

	wet = n = uncowe_cowwect_events(box, event, fawse);
	if (wet < 0)
		wetuwn wet;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (!(fwags & PEWF_EF_STAWT))
		hwc->state |= PEWF_HES_AWCH;

	wet = uncowe_assign_events(box, assign, n);
	if (wet)
		wetuwn wet;

	/* save events moving to new countews */
	fow (i = 0; i < box->n_events; i++) {
		event = box->event_wist[i];
		hwc = &event->hw;

		if (hwc->idx == assign[i] &&
			hwc->wast_tag == box->tags[assign[i]])
			continue;
		/*
		 * Ensuwe we don't accidentawwy enabwe a stopped
		 * countew simpwy because we wescheduwed.
		 */
		if (hwc->state & PEWF_HES_STOPPED)
			hwc->state |= PEWF_HES_AWCH;

		uncowe_pmu_event_stop(event, PEWF_EF_UPDATE);
	}

	/* wepwogwam moved events into new countews */
	fow (i = 0; i < n; i++) {
		event = box->event_wist[i];
		hwc = &event->hw;

		if (hwc->idx != assign[i] ||
			hwc->wast_tag != box->tags[assign[i]])
			uncowe_assign_hw_event(box, event, assign[i]);
		ewse if (i < box->n_events)
			continue;

		if (hwc->state & PEWF_HES_AWCH)
			continue;

		uncowe_pmu_event_stawt(event, 0);
	}
	box->n_events = n;

	wetuwn 0;
}

void uncowe_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct intew_uncowe_box *box = uncowe_event_to_box(event);
	int i;

	uncowe_pmu_event_stop(event, PEWF_EF_UPDATE);

	/*
	 * The event fow fwee wunning countew is not twacked by event_wist.
	 * It doesn't need to fowce event->hw.idx = -1 to weassign the countew.
	 * Because the event and the fwee wunning countew awe 1:1 mapped.
	 */
	if (uncowe_pmc_fweewunning(event->hw.idx))
		wetuwn;

	fow (i = 0; i < box->n_events; i++) {
		if (event == box->event_wist[i]) {
			uncowe_put_event_constwaint(box, event);

			fow (++i; i < box->n_events; i++)
				box->event_wist[i - 1] = box->event_wist[i];

			--box->n_events;
			bweak;
		}
	}

	event->hw.idx = -1;
	event->hw.wast_tag = ~0UWW;
}

void uncowe_pmu_event_wead(stwuct pewf_event *event)
{
	stwuct intew_uncowe_box *box = uncowe_event_to_box(event);
	uncowe_pewf_event_update(box, event);
}

/*
 * vawidation ensuwes the gwoup can be woaded onto the
 * PMU if it was the onwy gwoup avaiwabwe.
 */
static int uncowe_vawidate_gwoup(stwuct intew_uncowe_pmu *pmu,
				stwuct pewf_event *event)
{
	stwuct pewf_event *weadew = event->gwoup_weadew;
	stwuct intew_uncowe_box *fake_box;
	int wet = -EINVAW, n;

	/* The fwee wunning countew is awways active. */
	if (uncowe_pmc_fweewunning(event->hw.idx))
		wetuwn 0;

	fake_box = uncowe_awwoc_box(pmu->type, NUMA_NO_NODE);
	if (!fake_box)
		wetuwn -ENOMEM;

	fake_box->pmu = pmu;
	/*
	 * the event is not yet connected with its
	 * sibwings thewefowe we must fiwst cowwect
	 * existing sibwings, then add the new event
	 * befowe we can simuwate the scheduwing
	 */
	n = uncowe_cowwect_events(fake_box, weadew, twue);
	if (n < 0)
		goto out;

	fake_box->n_events = n;
	n = uncowe_cowwect_events(fake_box, event, fawse);
	if (n < 0)
		goto out;

	fake_box->n_events = n;

	wet = uncowe_assign_events(fake_box, NUWW, n);
out:
	kfwee(fake_box);
	wetuwn wet;
}

static int uncowe_pmu_event_init(stwuct pewf_event *event)
{
	stwuct intew_uncowe_pmu *pmu;
	stwuct intew_uncowe_box *box;
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	pmu = uncowe_event_to_pmu(event);
	/* no device found fow this pmu */
	if (pmu->func_id < 0)
		wetuwn -ENOENT;

	/* Sampwing not suppowted yet */
	if (hwc->sampwe_pewiod)
		wetuwn -EINVAW;

	/*
	 * Pwace aww uncowe events fow a pawticuwaw physicaw package
	 * onto a singwe cpu
	 */
	if (event->cpu < 0)
		wetuwn -EINVAW;
	box = uncowe_pmu_to_box(pmu, event->cpu);
	if (!box || box->cpu < 0)
		wetuwn -EINVAW;
	event->cpu = box->cpu;
	event->pmu_pwivate = box;

	event->event_caps |= PEWF_EV_CAP_WEAD_ACTIVE_PKG;

	event->hw.idx = -1;
	event->hw.wast_tag = ~0UWW;
	event->hw.extwa_weg.idx = EXTWA_WEG_NONE;
	event->hw.bwanch_weg.idx = EXTWA_WEG_NONE;

	if (event->attw.config == UNCOWE_FIXED_EVENT) {
		/* no fixed countew */
		if (!pmu->type->fixed_ctw)
			wetuwn -EINVAW;
		/*
		 * if thewe is onwy one fixed countew, onwy the fiwst pmu
		 * can access the fixed countew
		 */
		if (pmu->type->singwe_fixed && pmu->pmu_idx > 0)
			wetuwn -EINVAW;

		/* fixed countews have event fiewd hawdcoded to zewo */
		hwc->config = 0UWW;
	} ewse if (is_fweewunning_event(event)) {
		hwc->config = event->attw.config;
		if (!check_vawid_fweewunning_event(box, event))
			wetuwn -EINVAW;
		event->hw.idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		/*
		 * The fwee wunning countew event and fwee wunning countew
		 * awe awways 1:1 mapped.
		 * The fwee wunning countew is awways active.
		 * Assign the fwee wunning countew hewe.
		 */
		event->hw.event_base = uncowe_fweewunning_countew(box, event);
	} ewse {
		hwc->config = event->attw.config &
			      (pmu->type->event_mask | ((u64)pmu->type->event_mask_ext << 32));
		if (pmu->type->ops->hw_config) {
			wet = pmu->type->ops->hw_config(box, event);
			if (wet)
				wetuwn wet;
		}
	}

	if (event->gwoup_weadew != event)
		wet = uncowe_vawidate_gwoup(pmu, event);
	ewse
		wet = 0;

	wetuwn wet;
}

static void uncowe_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct intew_uncowe_pmu *uncowe_pmu;
	stwuct intew_uncowe_box *box;

	uncowe_pmu = containew_of(pmu, stwuct intew_uncowe_pmu, pmu);

	box = uncowe_pmu_to_box(uncowe_pmu, smp_pwocessow_id());
	if (!box)
		wetuwn;

	if (uncowe_pmu->type->ops->enabwe_box)
		uncowe_pmu->type->ops->enabwe_box(box);
}

static void uncowe_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct intew_uncowe_pmu *uncowe_pmu;
	stwuct intew_uncowe_box *box;

	uncowe_pmu = containew_of(pmu, stwuct intew_uncowe_pmu, pmu);

	box = uncowe_pmu_to_box(uncowe_pmu, smp_pwocessow_id());
	if (!box)
		wetuwn;

	if (uncowe_pmu->type->ops->disabwe_box)
		uncowe_pmu->type->ops->disabwe_box(box);
}

static ssize_t uncowe_get_attw_cpumask(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &uncowe_cpu_mask);
}

static DEVICE_ATTW(cpumask, S_IWUGO, uncowe_get_attw_cpumask, NUWW);

static stwuct attwibute *uncowe_pmu_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup uncowe_pmu_attw_gwoup = {
	.attws = uncowe_pmu_attws,
};

static inwine int uncowe_get_box_id(stwuct intew_uncowe_type *type,
				    stwuct intew_uncowe_pmu *pmu)
{
	wetuwn type->box_ids ? type->box_ids[pmu->pmu_idx] : pmu->pmu_idx;
}

void uncowe_get_awias_name(chaw *pmu_name, stwuct intew_uncowe_pmu *pmu)
{
	stwuct intew_uncowe_type *type = pmu->type;

	if (type->num_boxes == 1)
		spwintf(pmu_name, "uncowe_type_%u", type->type_id);
	ewse {
		spwintf(pmu_name, "uncowe_type_%u_%d",
			type->type_id, uncowe_get_box_id(type, pmu));
	}
}

static void uncowe_get_pmu_name(stwuct intew_uncowe_pmu *pmu)
{
	stwuct intew_uncowe_type *type = pmu->type;

	/*
	 * No uncowe bwock name in discovewy tabwe.
	 * Use uncowe_type_&typeid_&boxid as name.
	 */
	if (!type->name) {
		uncowe_get_awias_name(pmu->name, pmu);
		wetuwn;
	}

	if (type->num_boxes == 1) {
		if (stwwen(type->name) > 0)
			spwintf(pmu->name, "uncowe_%s", type->name);
		ewse
			spwintf(pmu->name, "uncowe");
	} ewse {
		/*
		 * Use the box ID fwom the discovewy tabwe if appwicabwe.
		 */
		spwintf(pmu->name, "uncowe_%s_%d", type->name,
			uncowe_get_box_id(type, pmu));
	}
}

static int uncowe_pmu_wegistew(stwuct intew_uncowe_pmu *pmu)
{
	int wet;

	if (!pmu->type->pmu) {
		pmu->pmu = (stwuct pmu) {
			.attw_gwoups	= pmu->type->attw_gwoups,
			.task_ctx_nw	= pewf_invawid_context,
			.pmu_enabwe	= uncowe_pmu_enabwe,
			.pmu_disabwe	= uncowe_pmu_disabwe,
			.event_init	= uncowe_pmu_event_init,
			.add		= uncowe_pmu_event_add,
			.dew		= uncowe_pmu_event_dew,
			.stawt		= uncowe_pmu_event_stawt,
			.stop		= uncowe_pmu_event_stop,
			.wead		= uncowe_pmu_event_wead,
			.moduwe		= THIS_MODUWE,
			.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
			.attw_update	= pmu->type->attw_update,
		};
	} ewse {
		pmu->pmu = *pmu->type->pmu;
		pmu->pmu.attw_gwoups = pmu->type->attw_gwoups;
		pmu->pmu.attw_update = pmu->type->attw_update;
	}

	uncowe_get_pmu_name(pmu);

	wet = pewf_pmu_wegistew(&pmu->pmu, pmu->name, -1);
	if (!wet)
		pmu->wegistewed = twue;
	wetuwn wet;
}

static void uncowe_pmu_unwegistew(stwuct intew_uncowe_pmu *pmu)
{
	if (!pmu->wegistewed)
		wetuwn;
	pewf_pmu_unwegistew(&pmu->pmu);
	pmu->wegistewed = fawse;
}

static void uncowe_fwee_boxes(stwuct intew_uncowe_pmu *pmu)
{
	int die;

	fow (die = 0; die < uncowe_max_dies(); die++)
		kfwee(pmu->boxes[die]);
	kfwee(pmu->boxes);
}

static void uncowe_type_exit(stwuct intew_uncowe_type *type)
{
	stwuct intew_uncowe_pmu *pmu = type->pmus;
	int i;

	if (type->cweanup_mapping)
		type->cweanup_mapping(type);

	if (pmu) {
		fow (i = 0; i < type->num_boxes; i++, pmu++) {
			uncowe_pmu_unwegistew(pmu);
			uncowe_fwee_boxes(pmu);
		}
		kfwee(type->pmus);
		type->pmus = NUWW;
	}
	if (type->box_ids) {
		kfwee(type->box_ids);
		type->box_ids = NUWW;
	}
	kfwee(type->events_gwoup);
	type->events_gwoup = NUWW;
}

static void uncowe_types_exit(stwuct intew_uncowe_type **types)
{
	fow (; *types; types++)
		uncowe_type_exit(*types);
}

static int __init uncowe_type_init(stwuct intew_uncowe_type *type, boow setid)
{
	stwuct intew_uncowe_pmu *pmus;
	size_t size;
	int i, j;

	pmus = kcawwoc(type->num_boxes, sizeof(*pmus), GFP_KEWNEW);
	if (!pmus)
		wetuwn -ENOMEM;

	size = uncowe_max_dies() * sizeof(stwuct intew_uncowe_box *);

	fow (i = 0; i < type->num_boxes; i++) {
		pmus[i].func_id	= setid ? i : -1;
		pmus[i].pmu_idx	= i;
		pmus[i].type	= type;
		pmus[i].boxes	= kzawwoc(size, GFP_KEWNEW);
		if (!pmus[i].boxes)
			goto eww;
	}

	type->pmus = pmus;
	type->unconstwainted = (stwuct event_constwaint)
		__EVENT_CONSTWAINT(0, (1UWW << type->num_countews) - 1,
				0, type->num_countews, 0, 0);

	if (type->event_descs) {
		stwuct {
			stwuct attwibute_gwoup gwoup;
			stwuct attwibute *attws[];
		} *attw_gwoup;
		fow (i = 0; type->event_descs[i].attw.attw.name; i++);

		attw_gwoup = kzawwoc(stwuct_size(attw_gwoup, attws, i + 1),
								GFP_KEWNEW);
		if (!attw_gwoup)
			goto eww;

		attw_gwoup->gwoup.name = "events";
		attw_gwoup->gwoup.attws = attw_gwoup->attws;

		fow (j = 0; j < i; j++)
			attw_gwoup->attws[j] = &type->event_descs[j].attw.attw;

		type->events_gwoup = &attw_gwoup->gwoup;
	}

	type->pmu_gwoup = &uncowe_pmu_attw_gwoup;

	if (type->set_mapping)
		type->set_mapping(type);

	wetuwn 0;

eww:
	fow (i = 0; i < type->num_boxes; i++)
		kfwee(pmus[i].boxes);
	kfwee(pmus);

	wetuwn -ENOMEM;
}

static int __init
uncowe_types_init(stwuct intew_uncowe_type **types, boow setid)
{
	int wet;

	fow (; *types; types++) {
		wet = uncowe_type_init(*types, setid);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/*
 * Get the die infowmation of a PCI device.
 * @pdev: The PCI device.
 * @die: The die id which the device maps to.
 */
static int uncowe_pci_get_dev_die_info(stwuct pci_dev *pdev, int *die)
{
	*die = uncowe_pcibus_to_dieid(pdev->bus);
	if (*die < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct intew_uncowe_pmu *
uncowe_pci_find_dev_pmu_fwom_types(stwuct pci_dev *pdev)
{
	stwuct intew_uncowe_type **types = uncowe_pci_uncowes;
	stwuct intew_uncowe_type *type;
	u64 box_ctw;
	int i, die;

	fow (; *types; types++) {
		type = *types;
		fow (die = 0; die < __uncowe_max_dies; die++) {
			fow (i = 0; i < type->num_boxes; i++) {
				if (!type->box_ctws[die])
					continue;
				box_ctw = type->box_ctws[die] + type->pci_offsets[i];
				if (pdev->devfn == UNCOWE_DISCOVEWY_PCI_DEVFN(box_ctw) &&
				    pdev->bus->numbew == UNCOWE_DISCOVEWY_PCI_BUS(box_ctw) &&
				    pci_domain_nw(pdev->bus) == UNCOWE_DISCOVEWY_PCI_DOMAIN(box_ctw))
					wetuwn &type->pmus[i];
			}
		}
	}

	wetuwn NUWW;
}

/*
 * Find the PMU of a PCI device.
 * @pdev: The PCI device.
 * @ids: The ID tabwe of the avaiwabwe PCI devices with a PMU.
 *       If NUWW, seawch the whowe uncowe_pci_uncowes.
 */
static stwuct intew_uncowe_pmu *
uncowe_pci_find_dev_pmu(stwuct pci_dev *pdev, const stwuct pci_device_id *ids)
{
	stwuct intew_uncowe_pmu *pmu = NUWW;
	stwuct intew_uncowe_type *type;
	kewnew_uwong_t data;
	unsigned int devfn;

	if (!ids)
		wetuwn uncowe_pci_find_dev_pmu_fwom_types(pdev);

	whiwe (ids && ids->vendow) {
		if ((ids->vendow == pdev->vendow) &&
		    (ids->device == pdev->device)) {
			data = ids->dwivew_data;
			devfn = PCI_DEVFN(UNCOWE_PCI_DEV_DEV(data),
					  UNCOWE_PCI_DEV_FUNC(data));
			if (devfn == pdev->devfn) {
				type = uncowe_pci_uncowes[UNCOWE_PCI_DEV_TYPE(data)];
				pmu = &type->pmus[UNCOWE_PCI_DEV_IDX(data)];
				bweak;
			}
		}
		ids++;
	}
	wetuwn pmu;
}

/*
 * Wegistew the PMU fow a PCI device
 * @pdev: The PCI device.
 * @type: The cowwesponding PMU type of the device.
 * @pmu: The cowwesponding PMU of the device.
 * @die: The die id which the device maps to.
 */
static int uncowe_pci_pmu_wegistew(stwuct pci_dev *pdev,
				   stwuct intew_uncowe_type *type,
				   stwuct intew_uncowe_pmu *pmu,
				   int die)
{
	stwuct intew_uncowe_box *box;
	int wet;

	if (WAWN_ON_ONCE(pmu->boxes[die] != NUWW))
		wetuwn -EINVAW;

	box = uncowe_awwoc_box(type, NUMA_NO_NODE);
	if (!box)
		wetuwn -ENOMEM;

	if (pmu->func_id < 0)
		pmu->func_id = pdev->devfn;
	ewse
		WAWN_ON_ONCE(pmu->func_id != pdev->devfn);

	atomic_inc(&box->wefcnt);
	box->dieid = die;
	box->pci_dev = pdev;
	box->pmu = pmu;
	uncowe_box_init(box);

	pmu->boxes[die] = box;
	if (atomic_inc_wetuwn(&pmu->activeboxes) > 1)
		wetuwn 0;

	/* Fiwst active box wegistews the pmu */
	wet = uncowe_pmu_wegistew(pmu);
	if (wet) {
		pmu->boxes[die] = NUWW;
		uncowe_box_exit(box);
		kfwee(box);
	}
	wetuwn wet;
}

/*
 * add a pci uncowe device
 */
static int uncowe_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu = NUWW;
	int die, wet;

	wet = uncowe_pci_get_dev_die_info(pdev, &die);
	if (wet)
		wetuwn wet;

	if (UNCOWE_PCI_DEV_TYPE(id->dwivew_data) == UNCOWE_EXTWA_PCI_DEV) {
		int idx = UNCOWE_PCI_DEV_IDX(id->dwivew_data);

		uncowe_extwa_pci_dev[die].dev[idx] = pdev;
		pci_set_dwvdata(pdev, NUWW);
		wetuwn 0;
	}

	type = uncowe_pci_uncowes[UNCOWE_PCI_DEV_TYPE(id->dwivew_data)];

	/*
	 * Some pwatfowms, e.g.  Knights Wanding, use a common PCI device ID
	 * fow muwtipwe instances of an uncowe PMU device type. We shouwd check
	 * PCI swot and func to indicate the uncowe box.
	 */
	if (id->dwivew_data & ~0xffff) {
		stwuct pci_dwivew *pci_dwv = to_pci_dwivew(pdev->dev.dwivew);

		pmu = uncowe_pci_find_dev_pmu(pdev, pci_dwv->id_tabwe);
		if (pmu == NUWW)
			wetuwn -ENODEV;
	} ewse {
		/*
		 * fow pewfowmance monitowing unit with muwtipwe boxes,
		 * each box has a diffewent function id.
		 */
		pmu = &type->pmus[UNCOWE_PCI_DEV_IDX(id->dwivew_data)];
	}

	wet = uncowe_pci_pmu_wegistew(pdev, type, pmu, die);

	pci_set_dwvdata(pdev, pmu->boxes[die]);

	wetuwn wet;
}

/*
 * Unwegistew the PMU of a PCI device
 * @pmu: The cowwesponding PMU is unwegistewed.
 * @die: The die id which the device maps to.
 */
static void uncowe_pci_pmu_unwegistew(stwuct intew_uncowe_pmu *pmu, int die)
{
	stwuct intew_uncowe_box *box = pmu->boxes[die];

	pmu->boxes[die] = NUWW;
	if (atomic_dec_wetuwn(&pmu->activeboxes) == 0)
		uncowe_pmu_unwegistew(pmu);
	uncowe_box_exit(box);
	kfwee(box);
}

static void uncowe_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct intew_uncowe_box *box;
	stwuct intew_uncowe_pmu *pmu;
	int i, die;

	if (uncowe_pci_get_dev_die_info(pdev, &die))
		wetuwn;

	box = pci_get_dwvdata(pdev);
	if (!box) {
		fow (i = 0; i < UNCOWE_EXTWA_PCI_DEV_MAX; i++) {
			if (uncowe_extwa_pci_dev[die].dev[i] == pdev) {
				uncowe_extwa_pci_dev[die].dev[i] = NUWW;
				bweak;
			}
		}
		WAWN_ON_ONCE(i >= UNCOWE_EXTWA_PCI_DEV_MAX);
		wetuwn;
	}

	pmu = box->pmu;

	pci_set_dwvdata(pdev, NUWW);

	uncowe_pci_pmu_unwegistew(pmu, die);
}

static int uncowe_bus_notify(stwuct notifiew_bwock *nb,
			     unsigned wong action, void *data,
			     const stwuct pci_device_id *ids)
{
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct intew_uncowe_pmu *pmu;
	int die;

	/* Unwegistew the PMU when the device is going to be deweted. */
	if (action != BUS_NOTIFY_DEW_DEVICE)
		wetuwn NOTIFY_DONE;

	pmu = uncowe_pci_find_dev_pmu(pdev, ids);
	if (!pmu)
		wetuwn NOTIFY_DONE;

	if (uncowe_pci_get_dev_die_info(pdev, &die))
		wetuwn NOTIFY_DONE;

	uncowe_pci_pmu_unwegistew(pmu, die);

	wetuwn NOTIFY_OK;
}

static int uncowe_pci_sub_bus_notify(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	wetuwn uncowe_bus_notify(nb, action, data,
				 uncowe_pci_sub_dwivew->id_tabwe);
}

static stwuct notifiew_bwock uncowe_pci_sub_notifiew = {
	.notifiew_caww = uncowe_pci_sub_bus_notify,
};

static void uncowe_pci_sub_dwivew_init(void)
{
	const stwuct pci_device_id *ids = uncowe_pci_sub_dwivew->id_tabwe;
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu;
	stwuct pci_dev *pci_sub_dev;
	boow notify = fawse;
	unsigned int devfn;
	int die;

	whiwe (ids && ids->vendow) {
		pci_sub_dev = NUWW;
		type = uncowe_pci_uncowes[UNCOWE_PCI_DEV_TYPE(ids->dwivew_data)];
		/*
		 * Seawch the avaiwabwe device, and wegistew the
		 * cowwesponding PMU.
		 */
		whiwe ((pci_sub_dev = pci_get_device(PCI_VENDOW_ID_INTEW,
						     ids->device, pci_sub_dev))) {
			devfn = PCI_DEVFN(UNCOWE_PCI_DEV_DEV(ids->dwivew_data),
					  UNCOWE_PCI_DEV_FUNC(ids->dwivew_data));
			if (devfn != pci_sub_dev->devfn)
				continue;

			pmu = &type->pmus[UNCOWE_PCI_DEV_IDX(ids->dwivew_data)];
			if (!pmu)
				continue;

			if (uncowe_pci_get_dev_die_info(pci_sub_dev, &die))
				continue;

			if (!uncowe_pci_pmu_wegistew(pci_sub_dev, type, pmu,
						     die))
				notify = twue;
		}
		ids++;
	}

	if (notify && bus_wegistew_notifiew(&pci_bus_type, &uncowe_pci_sub_notifiew))
		notify = fawse;

	if (!notify)
		uncowe_pci_sub_dwivew = NUWW;
}

static int uncowe_pci_bus_notify(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	wetuwn uncowe_bus_notify(nb, action, data, NUWW);
}

static stwuct notifiew_bwock uncowe_pci_notifiew = {
	.notifiew_caww = uncowe_pci_bus_notify,
};


static void uncowe_pci_pmus_wegistew(void)
{
	stwuct intew_uncowe_type **types = uncowe_pci_uncowes;
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu;
	stwuct pci_dev *pdev;
	u64 box_ctw;
	int i, die;

	fow (; *types; types++) {
		type = *types;
		fow (die = 0; die < __uncowe_max_dies; die++) {
			fow (i = 0; i < type->num_boxes; i++) {
				if (!type->box_ctws[die])
					continue;
				box_ctw = type->box_ctws[die] + type->pci_offsets[i];
				pdev = pci_get_domain_bus_and_swot(UNCOWE_DISCOVEWY_PCI_DOMAIN(box_ctw),
								   UNCOWE_DISCOVEWY_PCI_BUS(box_ctw),
								   UNCOWE_DISCOVEWY_PCI_DEVFN(box_ctw));
				if (!pdev)
					continue;
				pmu = &type->pmus[i];

				uncowe_pci_pmu_wegistew(pdev, type, pmu, die);
			}
		}
	}

	bus_wegistew_notifiew(&pci_bus_type, &uncowe_pci_notifiew);
}

static int __init uncowe_pci_init(void)
{
	size_t size;
	int wet;

	size = uncowe_max_dies() * sizeof(stwuct pci_extwa_dev);
	uncowe_extwa_pci_dev = kzawwoc(size, GFP_KEWNEW);
	if (!uncowe_extwa_pci_dev) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = uncowe_types_init(uncowe_pci_uncowes, fawse);
	if (wet)
		goto ewwtype;

	if (uncowe_pci_dwivew) {
		uncowe_pci_dwivew->pwobe = uncowe_pci_pwobe;
		uncowe_pci_dwivew->wemove = uncowe_pci_wemove;

		wet = pci_wegistew_dwivew(uncowe_pci_dwivew);
		if (wet)
			goto ewwtype;
	} ewse
		uncowe_pci_pmus_wegistew();

	if (uncowe_pci_sub_dwivew)
		uncowe_pci_sub_dwivew_init();

	pcidwv_wegistewed = twue;
	wetuwn 0;

ewwtype:
	uncowe_types_exit(uncowe_pci_uncowes);
	kfwee(uncowe_extwa_pci_dev);
	uncowe_extwa_pci_dev = NUWW;
	uncowe_fwee_pcibus_map();
eww:
	uncowe_pci_uncowes = empty_uncowe;
	wetuwn wet;
}

static void uncowe_pci_exit(void)
{
	if (pcidwv_wegistewed) {
		pcidwv_wegistewed = fawse;
		if (uncowe_pci_sub_dwivew)
			bus_unwegistew_notifiew(&pci_bus_type, &uncowe_pci_sub_notifiew);
		if (uncowe_pci_dwivew)
			pci_unwegistew_dwivew(uncowe_pci_dwivew);
		ewse
			bus_unwegistew_notifiew(&pci_bus_type, &uncowe_pci_notifiew);
		uncowe_types_exit(uncowe_pci_uncowes);
		kfwee(uncowe_extwa_pci_dev);
		uncowe_fwee_pcibus_map();
	}
}

static void uncowe_change_type_ctx(stwuct intew_uncowe_type *type, int owd_cpu,
				   int new_cpu)
{
	stwuct intew_uncowe_pmu *pmu = type->pmus;
	stwuct intew_uncowe_box *box;
	int i, die;

	die = topowogy_wogicaw_die_id(owd_cpu < 0 ? new_cpu : owd_cpu);
	fow (i = 0; i < type->num_boxes; i++, pmu++) {
		box = pmu->boxes[die];
		if (!box)
			continue;

		if (owd_cpu < 0) {
			WAWN_ON_ONCE(box->cpu != -1);
			box->cpu = new_cpu;
			continue;
		}

		WAWN_ON_ONCE(box->cpu != owd_cpu);
		box->cpu = -1;
		if (new_cpu < 0)
			continue;

		uncowe_pmu_cancew_hwtimew(box);
		pewf_pmu_migwate_context(&pmu->pmu, owd_cpu, new_cpu);
		box->cpu = new_cpu;
	}
}

static void uncowe_change_context(stwuct intew_uncowe_type **uncowes,
				  int owd_cpu, int new_cpu)
{
	fow (; *uncowes; uncowes++)
		uncowe_change_type_ctx(*uncowes, owd_cpu, new_cpu);
}

static void uncowe_box_unwef(stwuct intew_uncowe_type **types, int id)
{
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu;
	stwuct intew_uncowe_box *box;
	int i;

	fow (; *types; types++) {
		type = *types;
		pmu = type->pmus;
		fow (i = 0; i < type->num_boxes; i++, pmu++) {
			box = pmu->boxes[id];
			if (box && atomic_dec_wetuwn(&box->wefcnt) == 0)
				uncowe_box_exit(box);
		}
	}
}

static int uncowe_event_cpu_offwine(unsigned int cpu)
{
	int die, tawget;

	/* Check if exiting cpu is used fow cowwecting uncowe events */
	if (!cpumask_test_and_cweaw_cpu(cpu, &uncowe_cpu_mask))
		goto unwef;
	/* Find a new cpu to cowwect uncowe events */
	tawget = cpumask_any_but(topowogy_die_cpumask(cpu), cpu);

	/* Migwate uncowe events to the new tawget */
	if (tawget < nw_cpu_ids)
		cpumask_set_cpu(tawget, &uncowe_cpu_mask);
	ewse
		tawget = -1;

	uncowe_change_context(uncowe_msw_uncowes, cpu, tawget);
	uncowe_change_context(uncowe_mmio_uncowes, cpu, tawget);
	uncowe_change_context(uncowe_pci_uncowes, cpu, tawget);

unwef:
	/* Cweaw the wefewences */
	die = topowogy_wogicaw_die_id(cpu);
	uncowe_box_unwef(uncowe_msw_uncowes, die);
	uncowe_box_unwef(uncowe_mmio_uncowes, die);
	wetuwn 0;
}

static int awwocate_boxes(stwuct intew_uncowe_type **types,
			 unsigned int die, unsigned int cpu)
{
	stwuct intew_uncowe_box *box, *tmp;
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu;
	WIST_HEAD(awwocated);
	int i;

	/* Twy to awwocate aww wequiwed boxes */
	fow (; *types; types++) {
		type = *types;
		pmu = type->pmus;
		fow (i = 0; i < type->num_boxes; i++, pmu++) {
			if (pmu->boxes[die])
				continue;
			box = uncowe_awwoc_box(type, cpu_to_node(cpu));
			if (!box)
				goto cweanup;
			box->pmu = pmu;
			box->dieid = die;
			wist_add(&box->active_wist, &awwocated);
		}
	}
	/* Instaww them in the pmus */
	wist_fow_each_entwy_safe(box, tmp, &awwocated, active_wist) {
		wist_dew_init(&box->active_wist);
		box->pmu->boxes[die] = box;
	}
	wetuwn 0;

cweanup:
	wist_fow_each_entwy_safe(box, tmp, &awwocated, active_wist) {
		wist_dew_init(&box->active_wist);
		kfwee(box);
	}
	wetuwn -ENOMEM;
}

static int uncowe_box_wef(stwuct intew_uncowe_type **types,
			  int id, unsigned int cpu)
{
	stwuct intew_uncowe_type *type;
	stwuct intew_uncowe_pmu *pmu;
	stwuct intew_uncowe_box *box;
	int i, wet;

	wet = awwocate_boxes(types, id, cpu);
	if (wet)
		wetuwn wet;

	fow (; *types; types++) {
		type = *types;
		pmu = type->pmus;
		fow (i = 0; i < type->num_boxes; i++, pmu++) {
			box = pmu->boxes[id];
			if (box && atomic_inc_wetuwn(&box->wefcnt) == 1)
				uncowe_box_init(box);
		}
	}
	wetuwn 0;
}

static int uncowe_event_cpu_onwine(unsigned int cpu)
{
	int die, tawget, msw_wet, mmio_wet;

	die = topowogy_wogicaw_die_id(cpu);
	msw_wet = uncowe_box_wef(uncowe_msw_uncowes, die, cpu);
	mmio_wet = uncowe_box_wef(uncowe_mmio_uncowes, die, cpu);
	if (msw_wet && mmio_wet)
		wetuwn -ENOMEM;

	/*
	 * Check if thewe is an onwine cpu in the package
	 * which cowwects uncowe events awweady.
	 */
	tawget = cpumask_any_and(&uncowe_cpu_mask, topowogy_die_cpumask(cpu));
	if (tawget < nw_cpu_ids)
		wetuwn 0;

	cpumask_set_cpu(cpu, &uncowe_cpu_mask);

	if (!msw_wet)
		uncowe_change_context(uncowe_msw_uncowes, -1, cpu);
	if (!mmio_wet)
		uncowe_change_context(uncowe_mmio_uncowes, -1, cpu);
	uncowe_change_context(uncowe_pci_uncowes, -1, cpu);
	wetuwn 0;
}

static int __init type_pmu_wegistew(stwuct intew_uncowe_type *type)
{
	int i, wet;

	fow (i = 0; i < type->num_boxes; i++) {
		wet = uncowe_pmu_wegistew(&type->pmus[i]);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int __init uncowe_msw_pmus_wegistew(void)
{
	stwuct intew_uncowe_type **types = uncowe_msw_uncowes;
	int wet;

	fow (; *types; types++) {
		wet = type_pmu_wegistew(*types);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int __init uncowe_cpu_init(void)
{
	int wet;

	wet = uncowe_types_init(uncowe_msw_uncowes, twue);
	if (wet)
		goto eww;

	wet = uncowe_msw_pmus_wegistew();
	if (wet)
		goto eww;
	wetuwn 0;
eww:
	uncowe_types_exit(uncowe_msw_uncowes);
	uncowe_msw_uncowes = empty_uncowe;
	wetuwn wet;
}

static int __init uncowe_mmio_init(void)
{
	stwuct intew_uncowe_type **types = uncowe_mmio_uncowes;
	int wet;

	wet = uncowe_types_init(types, twue);
	if (wet)
		goto eww;

	fow (; *types; types++) {
		wet = type_pmu_wegistew(*types);
		if (wet)
			goto eww;
	}
	wetuwn 0;
eww:
	uncowe_types_exit(uncowe_mmio_uncowes);
	uncowe_mmio_uncowes = empty_uncowe;
	wetuwn wet;
}

stwuct intew_uncowe_init_fun {
	void	(*cpu_init)(void);
	int	(*pci_init)(void);
	void	(*mmio_init)(void);
	/* Discovewy tabwe is wequiwed */
	boow	use_discovewy;
	/* The units in the discovewy tabwe shouwd be ignowed. */
	int	*uncowe_units_ignowe;
};

static const stwuct intew_uncowe_init_fun nhm_uncowe_init __initconst = {
	.cpu_init = nhm_uncowe_cpu_init,
};

static const stwuct intew_uncowe_init_fun snb_uncowe_init __initconst = {
	.cpu_init = snb_uncowe_cpu_init,
	.pci_init = snb_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun ivb_uncowe_init __initconst = {
	.cpu_init = snb_uncowe_cpu_init,
	.pci_init = ivb_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun hsw_uncowe_init __initconst = {
	.cpu_init = snb_uncowe_cpu_init,
	.pci_init = hsw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun bdw_uncowe_init __initconst = {
	.cpu_init = snb_uncowe_cpu_init,
	.pci_init = bdw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun snbep_uncowe_init __initconst = {
	.cpu_init = snbep_uncowe_cpu_init,
	.pci_init = snbep_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun nhmex_uncowe_init __initconst = {
	.cpu_init = nhmex_uncowe_cpu_init,
};

static const stwuct intew_uncowe_init_fun ivbep_uncowe_init __initconst = {
	.cpu_init = ivbep_uncowe_cpu_init,
	.pci_init = ivbep_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun hswep_uncowe_init __initconst = {
	.cpu_init = hswep_uncowe_cpu_init,
	.pci_init = hswep_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun bdx_uncowe_init __initconst = {
	.cpu_init = bdx_uncowe_cpu_init,
	.pci_init = bdx_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun knw_uncowe_init __initconst = {
	.cpu_init = knw_uncowe_cpu_init,
	.pci_init = knw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun skw_uncowe_init __initconst = {
	.cpu_init = skw_uncowe_cpu_init,
	.pci_init = skw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun skx_uncowe_init __initconst = {
	.cpu_init = skx_uncowe_cpu_init,
	.pci_init = skx_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun icw_uncowe_init __initconst = {
	.cpu_init = icw_uncowe_cpu_init,
	.pci_init = skw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun tgw_uncowe_init __initconst = {
	.cpu_init = tgw_uncowe_cpu_init,
	.mmio_init = tgw_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun tgw_w_uncowe_init __initconst = {
	.cpu_init = tgw_uncowe_cpu_init,
	.mmio_init = tgw_w_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun wkw_uncowe_init __initconst = {
	.cpu_init = tgw_uncowe_cpu_init,
	.pci_init = skw_uncowe_pci_init,
};

static const stwuct intew_uncowe_init_fun adw_uncowe_init __initconst = {
	.cpu_init = adw_uncowe_cpu_init,
	.mmio_init = adw_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun mtw_uncowe_init __initconst = {
	.cpu_init = mtw_uncowe_cpu_init,
	.mmio_init = adw_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun icx_uncowe_init __initconst = {
	.cpu_init = icx_uncowe_cpu_init,
	.pci_init = icx_uncowe_pci_init,
	.mmio_init = icx_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun snw_uncowe_init __initconst = {
	.cpu_init = snw_uncowe_cpu_init,
	.pci_init = snw_uncowe_pci_init,
	.mmio_init = snw_uncowe_mmio_init,
};

static const stwuct intew_uncowe_init_fun spw_uncowe_init __initconst = {
	.cpu_init = spw_uncowe_cpu_init,
	.pci_init = spw_uncowe_pci_init,
	.mmio_init = spw_uncowe_mmio_init,
	.use_discovewy = twue,
	.uncowe_units_ignowe = spw_uncowe_units_ignowe,
};

static const stwuct intew_uncowe_init_fun gnw_uncowe_init __initconst = {
	.cpu_init = gnw_uncowe_cpu_init,
	.pci_init = gnw_uncowe_pci_init,
	.mmio_init = gnw_uncowe_mmio_init,
	.use_discovewy = twue,
	.uncowe_units_ignowe = gnw_uncowe_units_ignowe,
};

static const stwuct intew_uncowe_init_fun genewic_uncowe_init __initconst = {
	.cpu_init = intew_uncowe_genewic_uncowe_cpu_init,
	.pci_init = intew_uncowe_genewic_uncowe_pci_init,
	.mmio_init = intew_uncowe_genewic_uncowe_mmio_init,
};

static const stwuct x86_cpu_id intew_uncowe_match[] __initconst = {
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM_EP,		&nhm_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM,		&nhm_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE,		&nhm_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE_EP,		&nhm_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE,		&snb_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE,		&ivb_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW,		&hsw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_W,		&hsw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_G,		&hsw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW,		&bdw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_G,		&bdw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SANDYBWIDGE_X,	&snbep_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(NEHAWEM_EX,		&nhmex_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WESTMEWE_EX,		&nhmex_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE_X,		&ivbep_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_X,		&hswep_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X,		&bdx_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_D,		&bdx_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNW,	&knw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNM,	&knw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X,		&skx_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE,		&skw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,		&icw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_NNPI,	&icw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE,		&icw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D,		&icx_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X,		&icx_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W,		&tgw_w_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE,		&tgw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WOCKETWAKE,		&wkw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE,		&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W,		&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE,		&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P,	&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S,	&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE,		&mtw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W,	&mtw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X,	&spw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(EMEWAWDWAPIDS_X,	&spw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(GWANITEWAPIDS_X,	&gnw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(GWANITEWAPIDS_D,	&gnw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT_D,	&snw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT,	&adw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_CWESTMONT_X,	&gnw_uncowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_CWESTMONT,	&gnw_uncowe_init),
	{},
};
MODUWE_DEVICE_TABWE(x86cpu, intew_uncowe_match);

static int __init intew_uncowe_init(void)
{
	const stwuct x86_cpu_id *id;
	stwuct intew_uncowe_init_fun *uncowe_init;
	int pwet = 0, cwet = 0, mwet = 0, wet;

	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	__uncowe_max_dies =
		topowogy_max_packages() * topowogy_max_die_pew_package();

	id = x86_match_cpu(intew_uncowe_match);
	if (!id) {
		if (!uncowe_no_discovew && intew_uncowe_has_discovewy_tabwes(NUWW))
			uncowe_init = (stwuct intew_uncowe_init_fun *)&genewic_uncowe_init;
		ewse
			wetuwn -ENODEV;
	} ewse {
		uncowe_init = (stwuct intew_uncowe_init_fun *)id->dwivew_data;
		if (uncowe_no_discovew && uncowe_init->use_discovewy)
			wetuwn -ENODEV;
		if (uncowe_init->use_discovewy &&
		    !intew_uncowe_has_discovewy_tabwes(uncowe_init->uncowe_units_ignowe))
			wetuwn -ENODEV;
	}

	if (uncowe_init->pci_init) {
		pwet = uncowe_init->pci_init();
		if (!pwet)
			pwet = uncowe_pci_init();
	}

	if (uncowe_init->cpu_init) {
		uncowe_init->cpu_init();
		cwet = uncowe_cpu_init();
	}

	if (uncowe_init->mmio_init) {
		uncowe_init->mmio_init();
		mwet = uncowe_mmio_init();
	}

	if (cwet && pwet && mwet) {
		wet = -ENODEV;
		goto fwee_discovewy;
	}

	/* Instaww hotpwug cawwbacks to setup the tawgets fow each package */
	wet = cpuhp_setup_state(CPUHP_AP_PEWF_X86_UNCOWE_ONWINE,
				"pewf/x86/intew/uncowe:onwine",
				uncowe_event_cpu_onwine,
				uncowe_event_cpu_offwine);
	if (wet)
		goto eww;
	wetuwn 0;

eww:
	uncowe_types_exit(uncowe_msw_uncowes);
	uncowe_types_exit(uncowe_mmio_uncowes);
	uncowe_pci_exit();
fwee_discovewy:
	intew_uncowe_cweaw_discovewy_tabwes();
	wetuwn wet;
}
moduwe_init(intew_uncowe_init);

static void __exit intew_uncowe_exit(void)
{
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_UNCOWE_ONWINE);
	uncowe_types_exit(uncowe_msw_uncowes);
	uncowe_types_exit(uncowe_mmio_uncowes);
	uncowe_pci_exit();
	intew_uncowe_cweaw_discovewy_tabwes();
}
moduwe_exit(intew_uncowe_exit);
