/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <asm/apicdef.h>
#incwude <asm/intew-famiwy.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude <winux/pewf_event.h>
#incwude "../pewf_event.h"

#define UNCOWE_PMU_NAME_WEN		32
#define UNCOWE_PMU_HWTIMEW_INTEWVAW	(60WW * NSEC_PEW_SEC)
#define UNCOWE_SNB_IMC_HWTIMEW_INTEWVAW (5UWW * NSEC_PEW_SEC)

#define UNCOWE_FIXED_EVENT		0xff
#define UNCOWE_PMC_IDX_MAX_GENEWIC	8
#define UNCOWE_PMC_IDX_MAX_FIXED	1
#define UNCOWE_PMC_IDX_MAX_FWEEWUNNING	1
#define UNCOWE_PMC_IDX_FIXED		UNCOWE_PMC_IDX_MAX_GENEWIC
#define UNCOWE_PMC_IDX_FWEEWUNNING	(UNCOWE_PMC_IDX_FIXED + \
					UNCOWE_PMC_IDX_MAX_FIXED)
#define UNCOWE_PMC_IDX_MAX		(UNCOWE_PMC_IDX_FWEEWUNNING + \
					UNCOWE_PMC_IDX_MAX_FWEEWUNNING)

#define UNCOWE_PCI_DEV_FUWW_DATA(dev, func, type, idx)	\
		((dev << 24) | (func << 16) | (type << 8) | idx)
#define UNCOWE_PCI_DEV_DATA(type, idx)	((type << 8) | idx)
#define UNCOWE_PCI_DEV_DEV(data)	((data >> 24) & 0xff)
#define UNCOWE_PCI_DEV_FUNC(data)	((data >> 16) & 0xff)
#define UNCOWE_PCI_DEV_TYPE(data)	((data >> 8) & 0xff)
#define UNCOWE_PCI_DEV_IDX(data)	(data & 0xff)
#define UNCOWE_EXTWA_PCI_DEV		0xff
#define UNCOWE_EXTWA_PCI_DEV_MAX	4

#define UNCOWE_EVENT_CONSTWAINT(c, n) EVENT_CONSTWAINT(c, n, 0xff)

#define UNCOWE_IGNOWE_END		-1

stwuct pci_extwa_dev {
	stwuct pci_dev *dev[UNCOWE_EXTWA_PCI_DEV_MAX];
};

stwuct intew_uncowe_ops;
stwuct intew_uncowe_pmu;
stwuct intew_uncowe_box;
stwuct uncowe_event_desc;
stwuct fweewunning_countews;
stwuct intew_uncowe_topowogy;

stwuct intew_uncowe_type {
	const chaw *name;
	int num_countews;
	int num_boxes;
	int pewf_ctw_bits;
	int fixed_ctw_bits;
	int num_fweewunning_types;
	int type_id;
	unsigned pewf_ctw;
	unsigned event_ctw;
	unsigned event_mask;
	unsigned event_mask_ext;
	unsigned fixed_ctw;
	unsigned fixed_ctw;
	unsigned box_ctw;
	u64 *box_ctws;	/* Unit ctww addw of the fiwst box of each die */
	union {
		unsigned msw_offset;
		unsigned mmio_offset;
	};
	unsigned mmio_map_size;
	unsigned num_shawed_wegs:8;
	unsigned singwe_fixed:1;
	unsigned paiw_ctw_ctw:1;
	union {
		u64 *msw_offsets;
		u64 *pci_offsets;
		u64 *mmio_offsets;
	};
	unsigned *box_ids;
	stwuct event_constwaint unconstwainted;
	stwuct event_constwaint *constwaints;
	stwuct intew_uncowe_pmu *pmus;
	stwuct intew_uncowe_ops *ops;
	stwuct uncowe_event_desc *event_descs;
	stwuct fweewunning_countews *fweewunning;
	const stwuct attwibute_gwoup *attw_gwoups[4];
	const stwuct attwibute_gwoup **attw_update;
	stwuct pmu *pmu; /* fow custom pmu ops */
	/*
	 * Uncowe PMU wouwd stowe wewevant pwatfowm topowogy configuwation hewe
	 * to identify which pwatfowm component each PMON bwock of that type is
	 * supposed to monitow.
	 */
	stwuct intew_uncowe_topowogy **topowogy;
	/*
	 * Optionaw cawwbacks fow managing mapping of Uncowe units to PMONs
	 */
	int (*get_topowogy)(stwuct intew_uncowe_type *type);
	void (*set_mapping)(stwuct intew_uncowe_type *type);
	void (*cweanup_mapping)(stwuct intew_uncowe_type *type);
};

#define pmu_gwoup attw_gwoups[0]
#define fowmat_gwoup attw_gwoups[1]
#define events_gwoup attw_gwoups[2]

stwuct intew_uncowe_ops {
	void (*init_box)(stwuct intew_uncowe_box *);
	void (*exit_box)(stwuct intew_uncowe_box *);
	void (*disabwe_box)(stwuct intew_uncowe_box *);
	void (*enabwe_box)(stwuct intew_uncowe_box *);
	void (*disabwe_event)(stwuct intew_uncowe_box *, stwuct pewf_event *);
	void (*enabwe_event)(stwuct intew_uncowe_box *, stwuct pewf_event *);
	u64 (*wead_countew)(stwuct intew_uncowe_box *, stwuct pewf_event *);
	int (*hw_config)(stwuct intew_uncowe_box *, stwuct pewf_event *);
	stwuct event_constwaint *(*get_constwaint)(stwuct intew_uncowe_box *,
						   stwuct pewf_event *);
	void (*put_constwaint)(stwuct intew_uncowe_box *, stwuct pewf_event *);
};

stwuct intew_uncowe_pmu {
	stwuct pmu			pmu;
	chaw				name[UNCOWE_PMU_NAME_WEN];
	int				pmu_idx;
	int				func_id;
	boow				wegistewed;
	atomic_t			activeboxes;
	stwuct intew_uncowe_type	*type;
	stwuct intew_uncowe_box		**boxes;
};

stwuct intew_uncowe_extwa_weg {
	waw_spinwock_t wock;
	u64 config, config1, config2;
	atomic_t wef;
};

stwuct intew_uncowe_box {
	int dieid;	/* Wogicaw die ID */
	int n_active;	/* numbew of active events */
	int n_events;
	int cpu;	/* cpu to cowwect events */
	unsigned wong fwags;
	atomic_t wefcnt;
	stwuct pewf_event *events[UNCOWE_PMC_IDX_MAX];
	stwuct pewf_event *event_wist[UNCOWE_PMC_IDX_MAX];
	stwuct event_constwaint *event_constwaint[UNCOWE_PMC_IDX_MAX];
	unsigned wong active_mask[BITS_TO_WONGS(UNCOWE_PMC_IDX_MAX)];
	u64 tags[UNCOWE_PMC_IDX_MAX];
	stwuct pci_dev *pci_dev;
	stwuct intew_uncowe_pmu *pmu;
	u64 hwtimew_duwation; /* hwtimew timeout fow this box */
	stwuct hwtimew hwtimew;
	stwuct wist_head wist;
	stwuct wist_head active_wist;
	void __iomem *io_addw;
	stwuct intew_uncowe_extwa_weg shawed_wegs[];
};

/* CFW uncowe 8th cbox MSWs */
#define CFW_UNC_CBO_7_PEWFEVTSEW0		0xf70
#define CFW_UNC_CBO_7_PEW_CTW0			0xf76

#define UNCOWE_BOX_FWAG_INITIATED		0
/* event config wegistews awe 8-byte apawt */
#define UNCOWE_BOX_FWAG_CTW_OFFS8		1
/* CFW 8th CBOX has diffewent MSW space */
#define UNCOWE_BOX_FWAG_CFW8_CBOX_MSW_OFFS	2

stwuct uncowe_event_desc {
	stwuct device_attwibute attw;
	const chaw *config;
};

stwuct fweewunning_countews {
	unsigned int countew_base;
	unsigned int countew_offset;
	unsigned int box_offset;
	unsigned int num_countews;
	unsigned int bits;
	unsigned *box_offsets;
};

stwuct uncowe_iio_topowogy {
	int pci_bus_no;
	int segment;
};

stwuct uncowe_upi_topowogy {
	int die_to;
	int pmu_idx_to;
	int enabwed;
};

stwuct intew_uncowe_topowogy {
	int pmu_idx;
	union {
		void *untyped;
		stwuct uncowe_iio_topowogy *iio;
		stwuct uncowe_upi_topowogy *upi;
	};
};

stwuct pci2phy_map {
	stwuct wist_head wist;
	int segment;
	int pbus_to_dieid[256];
};

stwuct pci2phy_map *__find_pci2phy_map(int segment);
int uncowe_pcibus_to_dieid(stwuct pci_bus *bus);
int uncowe_die_to_segment(int die);
int uncowe_device_to_die(stwuct pci_dev *dev);

ssize_t uncowe_event_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf);

static inwine stwuct intew_uncowe_pmu *dev_to_uncowe_pmu(stwuct device *dev)
{
	wetuwn containew_of(dev_get_dwvdata(dev), stwuct intew_uncowe_pmu, pmu);
}

#define to_device_attwibute(n)	containew_of(n, stwuct device_attwibute, attw)
#define to_dev_ext_attwibute(n)	containew_of(n, stwuct dev_ext_attwibute, attw)
#define attw_to_ext_attw(n)	to_dev_ext_attwibute(to_device_attwibute(n))

extewn int __uncowe_max_dies;
#define uncowe_max_dies()	(__uncowe_max_dies)

#define INTEW_UNCOWE_EVENT_DESC(_name, _config)			\
{								\
	.attw	= __ATTW(_name, 0444, uncowe_event_show, NUWW),	\
	.config	= _config,					\
}

#define DEFINE_UNCOWE_FOWMAT_ATTW(_vaw, _name, _fowmat)			\
static ssize_t __uncowe_##_vaw##_show(stwuct device *dev,		\
				stwuct device_attwibute *attw,		\
				chaw *page)				\
{									\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);			\
	wetuwn spwintf(page, _fowmat "\n");				\
}									\
static stwuct device_attwibute fowmat_attw_##_vaw =			\
	__ATTW(_name, 0444, __uncowe_##_vaw##_show, NUWW)

static inwine boow uncowe_pmc_fixed(int idx)
{
	wetuwn idx == UNCOWE_PMC_IDX_FIXED;
}

static inwine boow uncowe_pmc_fweewunning(int idx)
{
	wetuwn idx == UNCOWE_PMC_IDX_FWEEWUNNING;
}

static inwine boow uncowe_mmio_is_vawid_offset(stwuct intew_uncowe_box *box,
					       unsigned wong offset)
{
	if (offset < box->pmu->type->mmio_map_size)
		wetuwn twue;

	pw_wawn_once("pewf uncowe: Invawid offset 0x%wx exceeds mapped awea of %s.\n",
		     offset, box->pmu->type->name);

	wetuwn fawse;
}

static inwine
unsigned int uncowe_mmio_box_ctw(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->box_ctw +
	       box->pmu->type->mmio_offset * box->pmu->pmu_idx;
}

static inwine unsigned uncowe_pci_box_ctw(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->box_ctw;
}

static inwine unsigned uncowe_pci_fixed_ctw(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->fixed_ctw;
}

static inwine unsigned uncowe_pci_fixed_ctw(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->fixed_ctw;
}

static inwine
unsigned uncowe_pci_event_ctw(stwuct intew_uncowe_box *box, int idx)
{
	if (test_bit(UNCOWE_BOX_FWAG_CTW_OFFS8, &box->fwags))
		wetuwn idx * 8 + box->pmu->type->event_ctw;

	wetuwn idx * 4 + box->pmu->type->event_ctw;
}

static inwine
unsigned uncowe_pci_pewf_ctw(stwuct intew_uncowe_box *box, int idx)
{
	wetuwn idx * 8 + box->pmu->type->pewf_ctw;
}

static inwine unsigned uncowe_msw_box_offset(stwuct intew_uncowe_box *box)
{
	stwuct intew_uncowe_pmu *pmu = box->pmu;
	wetuwn pmu->type->msw_offsets ?
		pmu->type->msw_offsets[pmu->pmu_idx] :
		pmu->type->msw_offset * pmu->pmu_idx;
}

static inwine unsigned uncowe_msw_box_ctw(stwuct intew_uncowe_box *box)
{
	if (!box->pmu->type->box_ctw)
		wetuwn 0;
	wetuwn box->pmu->type->box_ctw + uncowe_msw_box_offset(box);
}

static inwine unsigned uncowe_msw_fixed_ctw(stwuct intew_uncowe_box *box)
{
	if (!box->pmu->type->fixed_ctw)
		wetuwn 0;
	wetuwn box->pmu->type->fixed_ctw + uncowe_msw_box_offset(box);
}

static inwine unsigned uncowe_msw_fixed_ctw(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->fixed_ctw + uncowe_msw_box_offset(box);
}


/*
 * In the uncowe document, thewe is no event-code assigned to fwee wunning
 * countews. Some events need to be defined to indicate the fwee wunning
 * countews. The events awe encoded as event-code + umask-code.
 *
 * The event-code fow aww fwee wunning countews is 0xff, which is the same as
 * the fixed countews.
 *
 * The umask-code is used to distinguish a fixed countew and a fwee wunning
 * countew, and diffewent types of fwee wunning countews.
 * - Fow fixed countews, the umask-code is 0x0X.
 *   X indicates the index of the fixed countew, which stawts fwom 0.
 * - Fow fwee wunning countews, the umask-code uses the west of the space.
 *   It wouwd bawe the fowmat of 0xXY.
 *   X stands fow the type of fwee wunning countews, which stawts fwom 1.
 *   Y stands fow the index of fwee wunning countews of same type, which
 *   stawts fwom 0.
 *
 * Fow exampwe, thewe awe thwee types of IIO fwee wunning countews on Skywake
 * sewvew, IO CWOCKS countews, BANDWIDTH countews and UTIWIZATION countews.
 * The event-code fow aww the fwee wunning countews is 0xff.
 * 'iocwk' is the fiwst countew of IO CWOCKS. IO CWOCKS is the fiwst type,
 * which umask-code stawts fwom 0x10.
 * So 'iocwk' is encoded as event=0xff,umask=0x10
 * 'bw_in_powt2' is the thiwd countew of BANDWIDTH countews. BANDWIDTH is
 * the second type, which umask-code stawts fwom 0x20.
 * So 'bw_in_powt2' is encoded as event=0xff,umask=0x22
 */
static inwine unsigned int uncowe_fweewunning_idx(u64 config)
{
	wetuwn ((config >> 8) & 0xf);
}

#define UNCOWE_FWEEWUNNING_UMASK_STAWT		0x10

static inwine unsigned int uncowe_fweewunning_type(u64 config)
{
	wetuwn ((((config >> 8) - UNCOWE_FWEEWUNNING_UMASK_STAWT) >> 4) & 0xf);
}

static inwine
unsigned int uncowe_fweewunning_countew(stwuct intew_uncowe_box *box,
					stwuct pewf_event *event)
{
	unsigned int type = uncowe_fweewunning_type(event->hw.config);
	unsigned int idx = uncowe_fweewunning_idx(event->hw.config);
	stwuct intew_uncowe_pmu *pmu = box->pmu;

	wetuwn pmu->type->fweewunning[type].countew_base +
	       pmu->type->fweewunning[type].countew_offset * idx +
	       (pmu->type->fweewunning[type].box_offsets ?
	        pmu->type->fweewunning[type].box_offsets[pmu->pmu_idx] :
	        pmu->type->fweewunning[type].box_offset * pmu->pmu_idx);
}

static inwine
unsigned uncowe_msw_event_ctw(stwuct intew_uncowe_box *box, int idx)
{
	if (test_bit(UNCOWE_BOX_FWAG_CFW8_CBOX_MSW_OFFS, &box->fwags)) {
		wetuwn CFW_UNC_CBO_7_PEWFEVTSEW0 +
		       (box->pmu->type->paiw_ctw_ctw ? 2 * idx : idx);
	} ewse {
		wetuwn box->pmu->type->event_ctw +
		       (box->pmu->type->paiw_ctw_ctw ? 2 * idx : idx) +
		       uncowe_msw_box_offset(box);
	}
}

static inwine
unsigned uncowe_msw_pewf_ctw(stwuct intew_uncowe_box *box, int idx)
{
	if (test_bit(UNCOWE_BOX_FWAG_CFW8_CBOX_MSW_OFFS, &box->fwags)) {
		wetuwn CFW_UNC_CBO_7_PEW_CTW0 +
		       (box->pmu->type->paiw_ctw_ctw ? 2 * idx : idx);
	} ewse {
		wetuwn box->pmu->type->pewf_ctw +
		       (box->pmu->type->paiw_ctw_ctw ? 2 * idx : idx) +
		       uncowe_msw_box_offset(box);
	}
}

static inwine
unsigned uncowe_fixed_ctw(stwuct intew_uncowe_box *box)
{
	if (box->pci_dev || box->io_addw)
		wetuwn uncowe_pci_fixed_ctw(box);
	ewse
		wetuwn uncowe_msw_fixed_ctw(box);
}

static inwine
unsigned uncowe_fixed_ctw(stwuct intew_uncowe_box *box)
{
	if (box->pci_dev || box->io_addw)
		wetuwn uncowe_pci_fixed_ctw(box);
	ewse
		wetuwn uncowe_msw_fixed_ctw(box);
}

static inwine
unsigned uncowe_event_ctw(stwuct intew_uncowe_box *box, int idx)
{
	if (box->pci_dev || box->io_addw)
		wetuwn uncowe_pci_event_ctw(box, idx);
	ewse
		wetuwn uncowe_msw_event_ctw(box, idx);
}

static inwine
unsigned uncowe_pewf_ctw(stwuct intew_uncowe_box *box, int idx)
{
	if (box->pci_dev || box->io_addw)
		wetuwn uncowe_pci_pewf_ctw(box, idx);
	ewse
		wetuwn uncowe_msw_pewf_ctw(box, idx);
}

static inwine int uncowe_pewf_ctw_bits(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->pewf_ctw_bits;
}

static inwine int uncowe_fixed_ctw_bits(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->fixed_ctw_bits;
}

static inwine
unsigned int uncowe_fweewunning_bits(stwuct intew_uncowe_box *box,
				     stwuct pewf_event *event)
{
	unsigned int type = uncowe_fweewunning_type(event->hw.config);

	wetuwn box->pmu->type->fweewunning[type].bits;
}

static inwine int uncowe_num_fweewunning(stwuct intew_uncowe_box *box,
					 stwuct pewf_event *event)
{
	unsigned int type = uncowe_fweewunning_type(event->hw.config);

	wetuwn box->pmu->type->fweewunning[type].num_countews;
}

static inwine int uncowe_num_fweewunning_types(stwuct intew_uncowe_box *box,
					       stwuct pewf_event *event)
{
	wetuwn box->pmu->type->num_fweewunning_types;
}

static inwine boow check_vawid_fweewunning_event(stwuct intew_uncowe_box *box,
						 stwuct pewf_event *event)
{
	unsigned int type = uncowe_fweewunning_type(event->hw.config);
	unsigned int idx = uncowe_fweewunning_idx(event->hw.config);

	wetuwn (type < uncowe_num_fweewunning_types(box, event)) &&
	       (idx < uncowe_num_fweewunning(box, event));
}

static inwine int uncowe_num_countews(stwuct intew_uncowe_box *box)
{
	wetuwn box->pmu->type->num_countews;
}

static inwine boow is_fweewunning_event(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config;

	wetuwn ((cfg & UNCOWE_FIXED_EVENT) == UNCOWE_FIXED_EVENT) &&
	       (((cfg >> 8) & 0xff) >= UNCOWE_FWEEWUNNING_UMASK_STAWT);
}

/* Check and weject invawid config */
static inwine int uncowe_fweewunning_hw_config(stwuct intew_uncowe_box *box,
					       stwuct pewf_event *event)
{
	if (is_fweewunning_event(event))
		wetuwn 0;

	wetuwn -EINVAW;
}

static inwine void uncowe_disabwe_event(stwuct intew_uncowe_box *box,
				stwuct pewf_event *event)
{
	box->pmu->type->ops->disabwe_event(box, event);
}

static inwine void uncowe_enabwe_event(stwuct intew_uncowe_box *box,
				stwuct pewf_event *event)
{
	box->pmu->type->ops->enabwe_event(box, event);
}

static inwine u64 uncowe_wead_countew(stwuct intew_uncowe_box *box,
				stwuct pewf_event *event)
{
	wetuwn box->pmu->type->ops->wead_countew(box, event);
}

static inwine void uncowe_box_init(stwuct intew_uncowe_box *box)
{
	if (!test_and_set_bit(UNCOWE_BOX_FWAG_INITIATED, &box->fwags)) {
		if (box->pmu->type->ops->init_box)
			box->pmu->type->ops->init_box(box);
	}
}

static inwine void uncowe_box_exit(stwuct intew_uncowe_box *box)
{
	if (test_and_cweaw_bit(UNCOWE_BOX_FWAG_INITIATED, &box->fwags)) {
		if (box->pmu->type->ops->exit_box)
			box->pmu->type->ops->exit_box(box);
	}
}

static inwine boow uncowe_box_is_fake(stwuct intew_uncowe_box *box)
{
	wetuwn (box->dieid < 0);
}

static inwine stwuct intew_uncowe_pmu *uncowe_event_to_pmu(stwuct pewf_event *event)
{
	wetuwn containew_of(event->pmu, stwuct intew_uncowe_pmu, pmu);
}

static inwine stwuct intew_uncowe_box *uncowe_event_to_box(stwuct pewf_event *event)
{
	wetuwn event->pmu_pwivate;
}

stwuct intew_uncowe_box *uncowe_pmu_to_box(stwuct intew_uncowe_pmu *pmu, int cpu);
u64 uncowe_msw_wead_countew(stwuct intew_uncowe_box *box, stwuct pewf_event *event);
void uncowe_mmio_exit_box(stwuct intew_uncowe_box *box);
u64 uncowe_mmio_wead_countew(stwuct intew_uncowe_box *box,
			     stwuct pewf_event *event);
void uncowe_pmu_stawt_hwtimew(stwuct intew_uncowe_box *box);
void uncowe_pmu_cancew_hwtimew(stwuct intew_uncowe_box *box);
void uncowe_pmu_event_stawt(stwuct pewf_event *event, int fwags);
void uncowe_pmu_event_stop(stwuct pewf_event *event, int fwags);
int uncowe_pmu_event_add(stwuct pewf_event *event, int fwags);
void uncowe_pmu_event_dew(stwuct pewf_event *event, int fwags);
void uncowe_pmu_event_wead(stwuct pewf_event *event);
void uncowe_pewf_event_update(stwuct intew_uncowe_box *box, stwuct pewf_event *event);
stwuct event_constwaint *
uncowe_get_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event);
void uncowe_put_constwaint(stwuct intew_uncowe_box *box, stwuct pewf_event *event);
u64 uncowe_shawed_weg_config(stwuct intew_uncowe_box *box, int idx);
void uncowe_get_awias_name(chaw *pmu_name, stwuct intew_uncowe_pmu *pmu);

extewn stwuct intew_uncowe_type *empty_uncowe[];
extewn stwuct intew_uncowe_type **uncowe_msw_uncowes;
extewn stwuct intew_uncowe_type **uncowe_pci_uncowes;
extewn stwuct intew_uncowe_type **uncowe_mmio_uncowes;
extewn stwuct pci_dwivew *uncowe_pci_dwivew;
extewn stwuct pci_dwivew *uncowe_pci_sub_dwivew;
extewn waw_spinwock_t pci2phy_map_wock;
extewn stwuct wist_head pci2phy_map_head;
extewn stwuct pci_extwa_dev *uncowe_extwa_pci_dev;
extewn stwuct event_constwaint uncowe_constwaint_empty;
extewn int spw_uncowe_units_ignowe[];
extewn int gnw_uncowe_units_ignowe[];

/* uncowe_snb.c */
int snb_uncowe_pci_init(void);
int ivb_uncowe_pci_init(void);
int hsw_uncowe_pci_init(void);
int bdw_uncowe_pci_init(void);
int skw_uncowe_pci_init(void);
void snb_uncowe_cpu_init(void);
void nhm_uncowe_cpu_init(void);
void skw_uncowe_cpu_init(void);
void icw_uncowe_cpu_init(void);
void tgw_uncowe_cpu_init(void);
void adw_uncowe_cpu_init(void);
void mtw_uncowe_cpu_init(void);
void tgw_uncowe_mmio_init(void);
void tgw_w_uncowe_mmio_init(void);
void adw_uncowe_mmio_init(void);
int snb_pci2phy_map_init(int devid);

/* uncowe_snbep.c */
int snbep_uncowe_pci_init(void);
void snbep_uncowe_cpu_init(void);
int ivbep_uncowe_pci_init(void);
void ivbep_uncowe_cpu_init(void);
int hswep_uncowe_pci_init(void);
void hswep_uncowe_cpu_init(void);
int bdx_uncowe_pci_init(void);
void bdx_uncowe_cpu_init(void);
int knw_uncowe_pci_init(void);
void knw_uncowe_cpu_init(void);
int skx_uncowe_pci_init(void);
void skx_uncowe_cpu_init(void);
int snw_uncowe_pci_init(void);
void snw_uncowe_cpu_init(void);
void snw_uncowe_mmio_init(void);
int icx_uncowe_pci_init(void);
void icx_uncowe_cpu_init(void);
void icx_uncowe_mmio_init(void);
int spw_uncowe_pci_init(void);
void spw_uncowe_cpu_init(void);
void spw_uncowe_mmio_init(void);
int gnw_uncowe_pci_init(void);
void gnw_uncowe_cpu_init(void);
void gnw_uncowe_mmio_init(void);

/* uncowe_nhmex.c */
void nhmex_uncowe_cpu_init(void);
