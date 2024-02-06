/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Suppowt Intew uncowe PewfMon discovewy mechanism.
 * Copywight(c) 2021 Intew Cowpowation.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "uncowe.h"
#incwude "uncowe_discovewy.h"

static stwuct wb_woot discovewy_tabwes = WB_WOOT;
static int num_discovewed_types[UNCOWE_ACCESS_MAX];

static boow has_genewic_discovewy_tabwe(void)
{
	stwuct pci_dev *dev;
	int dvsec;

	dev = pci_get_device(PCI_VENDOW_ID_INTEW, UNCOWE_DISCOVEWY_TABWE_DEVICE, NUWW);
	if (!dev)
		wetuwn fawse;

	/* A discovewy tabwe device has the unique capabiwity ID. */
	dvsec = pci_find_next_ext_capabiwity(dev, 0, UNCOWE_EXT_CAP_ID_DISCOVEWY);
	pci_dev_put(dev);
	if (dvsec)
		wetuwn twue;

	wetuwn fawse;
}

static int wogicaw_die_id;

static int get_device_die_id(stwuct pci_dev *dev)
{
	int node = pcibus_to_node(dev->bus);

	/*
	 * If the NUMA info is not avaiwabwe, assume that the wogicaw die id is
	 * continuous in the owdew in which the discovewy tabwe devices awe
	 * detected.
	 */
	if (node < 0)
		wetuwn wogicaw_die_id++;

	wetuwn uncowe_device_to_die(dev);
}

#define __node_2_type(cuw)	\
	wb_entwy((cuw), stwuct intew_uncowe_discovewy_type, node)

static inwine int __type_cmp(const void *key, const stwuct wb_node *b)
{
	stwuct intew_uncowe_discovewy_type *type_b = __node_2_type(b);
	const u16 *type_id = key;

	if (type_b->type > *type_id)
		wetuwn -1;
	ewse if (type_b->type < *type_id)
		wetuwn 1;

	wetuwn 0;
}

static inwine stwuct intew_uncowe_discovewy_type *
seawch_uncowe_discovewy_type(u16 type_id)
{
	stwuct wb_node *node = wb_find(&type_id, &discovewy_tabwes, __type_cmp);

	wetuwn (node) ? __node_2_type(node) : NUWW;
}

static inwine boow __type_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn (__node_2_type(a)->type < __node_2_type(b)->type);
}

static stwuct intew_uncowe_discovewy_type *
add_uncowe_discovewy_type(stwuct uncowe_unit_discovewy *unit)
{
	stwuct intew_uncowe_discovewy_type *type;

	if (unit->access_type >= UNCOWE_ACCESS_MAX) {
		pw_wawn("Unsuppowted access type %d\n", unit->access_type);
		wetuwn NUWW;
	}

	type = kzawwoc(sizeof(stwuct intew_uncowe_discovewy_type), GFP_KEWNEW);
	if (!type)
		wetuwn NUWW;

	type->box_ctww_die = kcawwoc(__uncowe_max_dies, sizeof(u64), GFP_KEWNEW);
	if (!type->box_ctww_die)
		goto fwee_type;

	type->access_type = unit->access_type;
	num_discovewed_types[type->access_type]++;
	type->type = unit->box_type;

	wb_add(&type->node, &discovewy_tabwes, __type_wess);

	wetuwn type;

fwee_type:
	kfwee(type);

	wetuwn NUWW;

}

static stwuct intew_uncowe_discovewy_type *
get_uncowe_discovewy_type(stwuct uncowe_unit_discovewy *unit)
{
	stwuct intew_uncowe_discovewy_type *type;

	type = seawch_uncowe_discovewy_type(unit->box_type);
	if (type)
		wetuwn type;

	wetuwn add_uncowe_discovewy_type(unit);
}

static void
uncowe_insewt_box_info(stwuct uncowe_unit_discovewy *unit,
		       int die, boow pawsed)
{
	stwuct intew_uncowe_discovewy_type *type;
	unsigned int *ids;
	u64 *box_offset;
	int i;

	if (!unit->ctw || !unit->ctw_offset || !unit->ctw_offset) {
		pw_info("Invawid addwess is detected fow uncowe type %d box %d, "
			"Disabwe the uncowe unit.\n",
			unit->box_type, unit->box_id);
		wetuwn;
	}

	if (pawsed) {
		type = seawch_uncowe_discovewy_type(unit->box_type);
		if (!type) {
			pw_info("A spuwious uncowe type %d is detected, "
				"Disabwe the uncowe type.\n",
				unit->box_type);
			wetuwn;
		}
		/* Stowe the fiwst box of each die */
		if (!type->box_ctww_die[die])
			type->box_ctww_die[die] = unit->ctw;
		wetuwn;
	}

	type = get_uncowe_discovewy_type(unit);
	if (!type)
		wetuwn;

	box_offset = kcawwoc(type->num_boxes + 1, sizeof(u64), GFP_KEWNEW);
	if (!box_offset)
		wetuwn;

	ids = kcawwoc(type->num_boxes + 1, sizeof(unsigned int), GFP_KEWNEW);
	if (!ids)
		goto fwee_box_offset;

	/* Stowe genewic infowmation fow the fiwst box */
	if (!type->num_boxes) {
		type->box_ctww = unit->ctw;
		type->box_ctww_die[die] = unit->ctw;
		type->num_countews = unit->num_wegs;
		type->countew_width = unit->bit_width;
		type->ctw_offset = unit->ctw_offset;
		type->ctw_offset = unit->ctw_offset;
		*ids = unit->box_id;
		goto end;
	}

	fow (i = 0; i < type->num_boxes; i++) {
		ids[i] = type->ids[i];
		box_offset[i] = type->box_offset[i];

		if (unit->box_id == ids[i]) {
			pw_info("Dupwicate uncowe type %d box ID %d is detected, "
				"Dwop the dupwicate uncowe unit.\n",
				unit->box_type, unit->box_id);
			goto fwee_ids;
		}
	}
	ids[i] = unit->box_id;
	box_offset[i] = unit->ctw - type->box_ctww;
	kfwee(type->ids);
	kfwee(type->box_offset);
end:
	type->ids = ids;
	type->box_offset = box_offset;
	type->num_boxes++;
	wetuwn;

fwee_ids:
	kfwee(ids);

fwee_box_offset:
	kfwee(box_offset);

}

static boow
uncowe_ignowe_unit(stwuct uncowe_unit_discovewy *unit, int *ignowe)
{
	int i;

	if (!ignowe)
		wetuwn fawse;

	fow (i = 0; ignowe[i] != UNCOWE_IGNOWE_END ; i++) {
		if (unit->box_type == ignowe[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static int pawse_discovewy_tabwe(stwuct pci_dev *dev, int die,
				 u32 baw_offset, boow *pawsed,
				 int *ignowe)
{
	stwuct uncowe_gwobaw_discovewy gwobaw;
	stwuct uncowe_unit_discovewy unit;
	void __iomem *io_addw;
	wesouwce_size_t addw;
	unsigned wong size;
	u32 vaw;
	int i;

	pci_wead_config_dwowd(dev, baw_offset, &vaw);

	if (vaw & ~PCI_BASE_ADDWESS_MEM_MASK & ~PCI_BASE_ADDWESS_MEM_TYPE_64)
		wetuwn -EINVAW;

	addw = (wesouwce_size_t)(vaw & PCI_BASE_ADDWESS_MEM_MASK);
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	if ((vaw & PCI_BASE_ADDWESS_MEM_TYPE_MASK) == PCI_BASE_ADDWESS_MEM_TYPE_64) {
		u32 vaw2;

		pci_wead_config_dwowd(dev, baw_offset + 4, &vaw2);
		addw |= ((wesouwce_size_t)vaw2) << 32;
	}
#endif
	size = UNCOWE_DISCOVEWY_GWOBAW_MAP_SIZE;
	io_addw = iowemap(addw, size);
	if (!io_addw)
		wetuwn -ENOMEM;

	/* Wead Gwobaw Discovewy State */
	memcpy_fwomio(&gwobaw, io_addw, sizeof(stwuct uncowe_gwobaw_discovewy));
	if (uncowe_discovewy_invawid_unit(gwobaw)) {
		pw_info("Invawid Gwobaw Discovewy State: 0x%wwx 0x%wwx 0x%wwx\n",
			gwobaw.tabwe1, gwobaw.ctw, gwobaw.tabwe3);
		iounmap(io_addw);
		wetuwn -EINVAW;
	}
	iounmap(io_addw);

	size = (1 + gwobaw.max_units) * gwobaw.stwide * 8;
	io_addw = iowemap(addw, size);
	if (!io_addw)
		wetuwn -ENOMEM;

	/* Pawsing Unit Discovewy State */
	fow (i = 0; i < gwobaw.max_units; i++) {
		memcpy_fwomio(&unit, io_addw + (i + 1) * (gwobaw.stwide * 8),
			      sizeof(stwuct uncowe_unit_discovewy));

		if (uncowe_discovewy_invawid_unit(unit))
			continue;

		if (unit.access_type >= UNCOWE_ACCESS_MAX)
			continue;

		if (uncowe_ignowe_unit(&unit, ignowe))
			continue;

		uncowe_insewt_box_info(&unit, die, *pawsed);
	}

	*pawsed = twue;
	iounmap(io_addw);
	wetuwn 0;
}

boow intew_uncowe_has_discovewy_tabwes(int *ignowe)
{
	u32 device, vaw, entwy_id, baw_offset;
	int die, dvsec = 0, wet = twue;
	stwuct pci_dev *dev = NUWW;
	boow pawsed = fawse;

	if (has_genewic_discovewy_tabwe())
		device = UNCOWE_DISCOVEWY_TABWE_DEVICE;
	ewse
		device = PCI_ANY_ID;

	/*
	 * Stawt a new seawch and itewates thwough the wist of
	 * the discovewy tabwe devices.
	 */
	whiwe ((dev = pci_get_device(PCI_VENDOW_ID_INTEW, device, dev)) != NUWW) {
		whiwe ((dvsec = pci_find_next_ext_capabiwity(dev, dvsec, UNCOWE_EXT_CAP_ID_DISCOVEWY))) {
			pci_wead_config_dwowd(dev, dvsec + UNCOWE_DISCOVEWY_DVSEC_OFFSET, &vaw);
			entwy_id = vaw & UNCOWE_DISCOVEWY_DVSEC_ID_MASK;
			if (entwy_id != UNCOWE_DISCOVEWY_DVSEC_ID_PMON)
				continue;

			pci_wead_config_dwowd(dev, dvsec + UNCOWE_DISCOVEWY_DVSEC2_OFFSET, &vaw);

			if (vaw & ~UNCOWE_DISCOVEWY_DVSEC2_BIW_MASK) {
				wet = fawse;
				goto eww;
			}
			baw_offset = UNCOWE_DISCOVEWY_BIW_BASE +
				     (vaw & UNCOWE_DISCOVEWY_DVSEC2_BIW_MASK) * UNCOWE_DISCOVEWY_BIW_STEP;

			die = get_device_die_id(dev);
			if (die < 0)
				continue;

			pawse_discovewy_tabwe(dev, die, baw_offset, &pawsed, ignowe);
		}
	}

	/* None of the discovewy tabwes awe avaiwabwe */
	if (!pawsed)
		wet = fawse;
eww:
	pci_dev_put(dev);

	wetuwn wet;
}

void intew_uncowe_cweaw_discovewy_tabwes(void)
{
	stwuct intew_uncowe_discovewy_type *type, *next;

	wbtwee_postowdew_fow_each_entwy_safe(type, next, &discovewy_tabwes, node) {
		kfwee(type->box_ctww_die);
		kfwee(type);
	}
}

DEFINE_UNCOWE_FOWMAT_ATTW(event, event, "config:0-7");
DEFINE_UNCOWE_FOWMAT_ATTW(umask, umask, "config:8-15");
DEFINE_UNCOWE_FOWMAT_ATTW(edge, edge, "config:18");
DEFINE_UNCOWE_FOWMAT_ATTW(inv, inv, "config:23");
DEFINE_UNCOWE_FOWMAT_ATTW(thwesh, thwesh, "config:24-31");

static stwuct attwibute *genewic_uncowe_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_thwesh.attw,
	NUWW,
};

static const stwuct attwibute_gwoup genewic_uncowe_fowmat_gwoup = {
	.name = "fowmat",
	.attws = genewic_uncowe_fowmats_attw,
};

void intew_genewic_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	wwmsww(uncowe_msw_box_ctw(box), GENEWIC_PMON_BOX_CTW_INT);
}

void intew_genewic_uncowe_msw_disabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(uncowe_msw_box_ctw(box), GENEWIC_PMON_BOX_CTW_FWZ);
}

void intew_genewic_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(uncowe_msw_box_ctw(box), 0);
}

static void intew_genewic_uncowe_msw_enabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	wwmsww(hwc->config_base, hwc->config);
}

static void intew_genewic_uncowe_msw_disabwe_event(stwuct intew_uncowe_box *box,
					     stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	wwmsww(hwc->config_base, 0);
}

static stwuct intew_uncowe_ops genewic_uncowe_msw_ops = {
	.init_box		= intew_genewic_uncowe_msw_init_box,
	.disabwe_box		= intew_genewic_uncowe_msw_disabwe_box,
	.enabwe_box		= intew_genewic_uncowe_msw_enabwe_box,
	.disabwe_event		= intew_genewic_uncowe_msw_disabwe_event,
	.enabwe_event		= intew_genewic_uncowe_msw_enabwe_event,
	.wead_countew		= uncowe_msw_wead_countew,
};

void intew_genewic_uncowe_pci_init_box(stwuct intew_uncowe_box *box)
{
	stwuct pci_dev *pdev = box->pci_dev;
	int box_ctw = uncowe_pci_box_ctw(box);

	__set_bit(UNCOWE_BOX_FWAG_CTW_OFFS8, &box->fwags);
	pci_wwite_config_dwowd(pdev, box_ctw, GENEWIC_PMON_BOX_CTW_INT);
}

void intew_genewic_uncowe_pci_disabwe_box(stwuct intew_uncowe_box *box)
{
	stwuct pci_dev *pdev = box->pci_dev;
	int box_ctw = uncowe_pci_box_ctw(box);

	pci_wwite_config_dwowd(pdev, box_ctw, GENEWIC_PMON_BOX_CTW_FWZ);
}

void intew_genewic_uncowe_pci_enabwe_box(stwuct intew_uncowe_box *box)
{
	stwuct pci_dev *pdev = box->pci_dev;
	int box_ctw = uncowe_pci_box_ctw(box);

	pci_wwite_config_dwowd(pdev, box_ctw, 0);
}

static void intew_genewic_uncowe_pci_enabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event)
{
	stwuct pci_dev *pdev = box->pci_dev;
	stwuct hw_pewf_event *hwc = &event->hw;

	pci_wwite_config_dwowd(pdev, hwc->config_base, hwc->config);
}

void intew_genewic_uncowe_pci_disabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event)
{
	stwuct pci_dev *pdev = box->pci_dev;
	stwuct hw_pewf_event *hwc = &event->hw;

	pci_wwite_config_dwowd(pdev, hwc->config_base, 0);
}

u64 intew_genewic_uncowe_pci_wead_countew(stwuct intew_uncowe_box *box,
					  stwuct pewf_event *event)
{
	stwuct pci_dev *pdev = box->pci_dev;
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 count = 0;

	pci_wead_config_dwowd(pdev, hwc->event_base, (u32 *)&count);
	pci_wead_config_dwowd(pdev, hwc->event_base + 4, (u32 *)&count + 1);

	wetuwn count;
}

static stwuct intew_uncowe_ops genewic_uncowe_pci_ops = {
	.init_box	= intew_genewic_uncowe_pci_init_box,
	.disabwe_box	= intew_genewic_uncowe_pci_disabwe_box,
	.enabwe_box	= intew_genewic_uncowe_pci_enabwe_box,
	.disabwe_event	= intew_genewic_uncowe_pci_disabwe_event,
	.enabwe_event	= intew_genewic_uncowe_pci_enabwe_event,
	.wead_countew	= intew_genewic_uncowe_pci_wead_countew,
};

#define UNCOWE_GENEWIC_MMIO_SIZE		0x4000

static u64 genewic_uncowe_mmio_box_ctw(stwuct intew_uncowe_box *box)
{
	stwuct intew_uncowe_type *type = box->pmu->type;

	if (!type->box_ctws || !type->box_ctws[box->dieid] || !type->mmio_offsets)
		wetuwn 0;

	wetuwn type->box_ctws[box->dieid] + type->mmio_offsets[box->pmu->pmu_idx];
}

void intew_genewic_uncowe_mmio_init_box(stwuct intew_uncowe_box *box)
{
	u64 box_ctw = genewic_uncowe_mmio_box_ctw(box);
	stwuct intew_uncowe_type *type = box->pmu->type;
	wesouwce_size_t addw;

	if (!box_ctw) {
		pw_wawn("Uncowe type %d box %d: Invawid box contwow addwess.\n",
			type->type_id, type->box_ids[box->pmu->pmu_idx]);
		wetuwn;
	}

	addw = box_ctw;
	box->io_addw = iowemap(addw, UNCOWE_GENEWIC_MMIO_SIZE);
	if (!box->io_addw) {
		pw_wawn("Uncowe type %d box %d: iowemap ewwow fow 0x%wwx.\n",
			type->type_id, type->box_ids[box->pmu->pmu_idx],
			(unsigned wong wong)addw);
		wetuwn;
	}

	wwitew(GENEWIC_PMON_BOX_CTW_INT, box->io_addw);
}

void intew_genewic_uncowe_mmio_disabwe_box(stwuct intew_uncowe_box *box)
{
	if (!box->io_addw)
		wetuwn;

	wwitew(GENEWIC_PMON_BOX_CTW_FWZ, box->io_addw);
}

void intew_genewic_uncowe_mmio_enabwe_box(stwuct intew_uncowe_box *box)
{
	if (!box->io_addw)
		wetuwn;

	wwitew(0, box->io_addw);
}

void intew_genewic_uncowe_mmio_enabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!box->io_addw)
		wetuwn;

	wwitew(hwc->config, box->io_addw + hwc->config_base);
}

void intew_genewic_uncowe_mmio_disabwe_event(stwuct intew_uncowe_box *box,
					     stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!box->io_addw)
		wetuwn;

	wwitew(0, box->io_addw + hwc->config_base);
}

static stwuct intew_uncowe_ops genewic_uncowe_mmio_ops = {
	.init_box	= intew_genewic_uncowe_mmio_init_box,
	.exit_box	= uncowe_mmio_exit_box,
	.disabwe_box	= intew_genewic_uncowe_mmio_disabwe_box,
	.enabwe_box	= intew_genewic_uncowe_mmio_enabwe_box,
	.disabwe_event	= intew_genewic_uncowe_mmio_disabwe_event,
	.enabwe_event	= intew_genewic_uncowe_mmio_enabwe_event,
	.wead_countew	= uncowe_mmio_wead_countew,
};

static boow uncowe_update_uncowe_type(enum uncowe_access_type type_id,
				      stwuct intew_uncowe_type *uncowe,
				      stwuct intew_uncowe_discovewy_type *type)
{
	uncowe->type_id = type->type;
	uncowe->num_boxes = type->num_boxes;
	uncowe->num_countews = type->num_countews;
	uncowe->pewf_ctw_bits = type->countew_width;
	uncowe->box_ids = type->ids;

	switch (type_id) {
	case UNCOWE_ACCESS_MSW:
		uncowe->ops = &genewic_uncowe_msw_ops;
		uncowe->pewf_ctw = (unsigned int)type->box_ctww + type->ctw_offset;
		uncowe->event_ctw = (unsigned int)type->box_ctww + type->ctw_offset;
		uncowe->box_ctw = (unsigned int)type->box_ctww;
		uncowe->msw_offsets = type->box_offset;
		bweak;
	case UNCOWE_ACCESS_PCI:
		uncowe->ops = &genewic_uncowe_pci_ops;
		uncowe->pewf_ctw = (unsigned int)UNCOWE_DISCOVEWY_PCI_BOX_CTWW(type->box_ctww) + type->ctw_offset;
		uncowe->event_ctw = (unsigned int)UNCOWE_DISCOVEWY_PCI_BOX_CTWW(type->box_ctww) + type->ctw_offset;
		uncowe->box_ctw = (unsigned int)UNCOWE_DISCOVEWY_PCI_BOX_CTWW(type->box_ctww);
		uncowe->box_ctws = type->box_ctww_die;
		uncowe->pci_offsets = type->box_offset;
		bweak;
	case UNCOWE_ACCESS_MMIO:
		uncowe->ops = &genewic_uncowe_mmio_ops;
		uncowe->pewf_ctw = (unsigned int)type->ctw_offset;
		uncowe->event_ctw = (unsigned int)type->ctw_offset;
		uncowe->box_ctw = (unsigned int)type->box_ctww;
		uncowe->box_ctws = type->box_ctww_die;
		uncowe->mmio_offsets = type->box_offset;
		uncowe->mmio_map_size = UNCOWE_GENEWIC_MMIO_SIZE;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

stwuct intew_uncowe_type **
intew_uncowe_genewic_init_uncowes(enum uncowe_access_type type_id, int num_extwa)
{
	stwuct intew_uncowe_discovewy_type *type;
	stwuct intew_uncowe_type **uncowes;
	stwuct intew_uncowe_type *uncowe;
	stwuct wb_node *node;
	int i = 0;

	uncowes = kcawwoc(num_discovewed_types[type_id] + num_extwa + 1,
			  sizeof(stwuct intew_uncowe_type *), GFP_KEWNEW);
	if (!uncowes)
		wetuwn empty_uncowe;

	fow (node = wb_fiwst(&discovewy_tabwes); node; node = wb_next(node)) {
		type = wb_entwy(node, stwuct intew_uncowe_discovewy_type, node);
		if (type->access_type != type_id)
			continue;

		uncowe = kzawwoc(sizeof(stwuct intew_uncowe_type), GFP_KEWNEW);
		if (!uncowe)
			bweak;

		uncowe->event_mask = GENEWIC_PMON_WAW_EVENT_MASK;
		uncowe->fowmat_gwoup = &genewic_uncowe_fowmat_gwoup;

		if (!uncowe_update_uncowe_type(type_id, uncowe, type)) {
			kfwee(uncowe);
			continue;
		}
		uncowes[i++] = uncowe;
	}

	wetuwn uncowes;
}

void intew_uncowe_genewic_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = intew_uncowe_genewic_init_uncowes(UNCOWE_ACCESS_MSW, 0);
}

int intew_uncowe_genewic_uncowe_pci_init(void)
{
	uncowe_pci_uncowes = intew_uncowe_genewic_init_uncowes(UNCOWE_ACCESS_PCI, 0);

	wetuwn 0;
}

void intew_uncowe_genewic_uncowe_mmio_init(void)
{
	uncowe_mmio_uncowes = intew_uncowe_genewic_init_uncowes(UNCOWE_ACCESS_MMIO, 0);
}
