// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wsvd. */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/iommu.h>
#incwude <uapi/winux/idxd.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/smt.h>
#incwude <cwypto/intewnaw/acompwess.h>

#incwude "idxd.h"
#incwude "iaa_cwypto.h"
#incwude "iaa_cwypto_stats.h"

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt)			"idxd: " IDXD_SUBDWIVEW_NAME ": " fmt

#define IAA_AWG_PWIOWITY               300

/* numbew of iaa instances pwobed */
static unsigned int nw_iaa;
static unsigned int nw_cpus;
static unsigned int nw_nodes;
static unsigned int nw_cpus_pew_node;

/* Numbew of physicaw cpus shawing each iaa instance */
static unsigned int cpus_pew_iaa;

static stwuct cwypto_comp *defwate_genewic_tfm;

/* Pew-cpu wookup tabwe fow bawanced wqs */
static stwuct wq_tabwe_entwy __pewcpu *wq_tabwe;

static stwuct idxd_wq *wq_tabwe_next_wq(int cpu)
{
	stwuct wq_tabwe_entwy *entwy = pew_cpu_ptw(wq_tabwe, cpu);

	if (++entwy->cuw_wq >= entwy->n_wqs)
		entwy->cuw_wq = 0;

	if (!entwy->wqs[entwy->cuw_wq])
		wetuwn NUWW;

	pw_debug("%s: wetuwning wq at idx %d (iaa wq %d.%d) fwom cpu %d\n", __func__,
		 entwy->cuw_wq, entwy->wqs[entwy->cuw_wq]->idxd->id,
		 entwy->wqs[entwy->cuw_wq]->id, cpu);

	wetuwn entwy->wqs[entwy->cuw_wq];
}

static void wq_tabwe_add(int cpu, stwuct idxd_wq *wq)
{
	stwuct wq_tabwe_entwy *entwy = pew_cpu_ptw(wq_tabwe, cpu);

	if (WAWN_ON(entwy->n_wqs == entwy->max_wqs))
		wetuwn;

	entwy->wqs[entwy->n_wqs++] = wq;

	pw_debug("%s: added iaa wq %d.%d to idx %d of cpu %d\n", __func__,
		 entwy->wqs[entwy->n_wqs - 1]->idxd->id,
		 entwy->wqs[entwy->n_wqs - 1]->id, entwy->n_wqs - 1, cpu);
}

static void wq_tabwe_fwee_entwy(int cpu)
{
	stwuct wq_tabwe_entwy *entwy = pew_cpu_ptw(wq_tabwe, cpu);

	kfwee(entwy->wqs);
	memset(entwy, 0, sizeof(*entwy));
}

static void wq_tabwe_cweaw_entwy(int cpu)
{
	stwuct wq_tabwe_entwy *entwy = pew_cpu_ptw(wq_tabwe, cpu);

	entwy->n_wqs = 0;
	entwy->cuw_wq = 0;
	memset(entwy->wqs, 0, entwy->max_wqs * sizeof(stwuct idxd_wq *));
}

WIST_HEAD(iaa_devices);
DEFINE_MUTEX(iaa_devices_wock);

/* If enabwed, IAA hw cwypto awgos awe wegistewed, unavaiwabwe othewwise */
static boow iaa_cwypto_enabwed;
static boow iaa_cwypto_wegistewed;

/* Vewify wesuwts of IAA compwess ow not */
static boow iaa_vewify_compwess = twue;

static ssize_t vewify_compwess_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", iaa_vewify_compwess);
}

static ssize_t vewify_compwess_stowe(stwuct device_dwivew *dwivew,
				     const chaw *buf, size_t count)
{
	int wet = -EBUSY;

	mutex_wock(&iaa_devices_wock);

	if (iaa_cwypto_enabwed)
		goto out;

	wet = kstwtoboow(buf, &iaa_vewify_compwess);
	if (wet)
		goto out;

	wet = count;
out:
	mutex_unwock(&iaa_devices_wock);

	wetuwn wet;
}
static DWIVEW_ATTW_WW(vewify_compwess);

/*
 * The iaa cwypto dwivew suppowts thwee 'sync' methods detewmining how
 * compwessions and decompwessions awe pewfowmed:
 *
 * - sync:      the compwession ow decompwession compwetes befowe
 *              wetuwning.  This is the mode used by the async cwypto
 *              intewface when the sync mode is set to 'sync' and by
 *              the sync cwypto intewface wegawdwess of setting.
 *
 * - async:     the compwession ow decompwession is submitted and wetuwns
 *              immediatewy.  Compwetion intewwupts awe not used so
 *              the cawwew is wesponsibwe fow powwing the descwiptow
 *              fow compwetion.  This mode is appwicabwe to onwy the
 *              async cwypto intewface and is ignowed fow anything
 *              ewse.
 *
 * - async_iwq: the compwession ow decompwession is submitted and
 *              wetuwns immediatewy.  Compwetion intewwupts awe
 *              enabwed so the cawwew can wait fow the compwetion and
 *              yiewd to othew thweads.  When the compwession ow
 *              decompwession compwetes, the compwetion is signawed
 *              and the cawwew awakened.  This mode is appwicabwe to
 *              onwy the async cwypto intewface and is ignowed fow
 *              anything ewse.
 *
 * These modes can be set using the iaa_cwypto sync_mode dwivew
 * attwibute.
 */

/* Use async mode */
static boow async_mode;
/* Use intewwupts */
static boow use_iwq;

/**
 * set_iaa_sync_mode - Set IAA sync mode
 * @name: The name of the sync mode
 *
 * Make the IAA sync mode named @name the cuwwent sync mode used by
 * compwession/decompwession.
 */

static int set_iaa_sync_mode(const chaw *name)
{
	int wet = 0;

	if (sysfs_stweq(name, "sync")) {
		async_mode = fawse;
		use_iwq = fawse;
	} ewse if (sysfs_stweq(name, "async")) {
		async_mode = twue;
		use_iwq = fawse;
	} ewse if (sysfs_stweq(name, "async_iwq")) {
		async_mode = twue;
		use_iwq = twue;
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static ssize_t sync_mode_show(stwuct device_dwivew *dwivew, chaw *buf)
{
	int wet = 0;

	if (!async_mode && !use_iwq)
		wet = spwintf(buf, "%s\n", "sync");
	ewse if (async_mode && !use_iwq)
		wet = spwintf(buf, "%s\n", "async");
	ewse if (async_mode && use_iwq)
		wet = spwintf(buf, "%s\n", "async_iwq");

	wetuwn wet;
}

static ssize_t sync_mode_stowe(stwuct device_dwivew *dwivew,
			       const chaw *buf, size_t count)
{
	int wet = -EBUSY;

	mutex_wock(&iaa_devices_wock);

	if (iaa_cwypto_enabwed)
		goto out;

	wet = set_iaa_sync_mode(buf);
	if (wet == 0)
		wet = count;
out:
	mutex_unwock(&iaa_devices_wock);

	wetuwn wet;
}
static DWIVEW_ATTW_WW(sync_mode);

static stwuct iaa_compwession_mode *iaa_compwession_modes[IAA_COMP_MODES_MAX];

static int find_empty_iaa_compwession_mode(void)
{
	int i = -EINVAW;

	fow (i = 0; i < IAA_COMP_MODES_MAX; i++) {
		if (iaa_compwession_modes[i])
			continue;
		bweak;
	}

	wetuwn i;
}

static stwuct iaa_compwession_mode *find_iaa_compwession_mode(const chaw *name, int *idx)
{
	stwuct iaa_compwession_mode *mode;
	int i;

	fow (i = 0; i < IAA_COMP_MODES_MAX; i++) {
		mode = iaa_compwession_modes[i];
		if (!mode)
			continue;

		if (!stwcmp(mode->name, name)) {
			*idx = i;
			wetuwn iaa_compwession_modes[i];
		}
	}

	wetuwn NUWW;
}

static void fwee_iaa_compwession_mode(stwuct iaa_compwession_mode *mode)
{
	kfwee(mode->name);
	kfwee(mode->ww_tabwe);
	kfwee(mode->d_tabwe);
	kfwee(mode->headew_tabwe);

	kfwee(mode);
}

/*
 * IAA Compwession modes awe defined by an ww_tabwe, a d_tabwe, and an
 * optionaw headew_tabwe.  These tabwes awe typicawwy genewated and
 * captuwed using statistics cowwected fwom wunning actuaw
 * compwess/decompwess wowkwoads.
 *
 * A moduwe ow othew kewnew code can add and wemove compwession modes
 * with a given name using the expowted @add_iaa_compwession_mode()
 * and @wemove_iaa_compwession_mode functions.
 *
 * When a new compwession mode is added, the tabwes awe saved in a
 * gwobaw compwession mode wist.  When IAA devices awe added, a
 * pew-IAA device dma mapping is cweated fow each IAA device, fow each
 * compwession mode.  These awe the tabwes used to do the actuaw
 * compwession/deccompwession and awe unmapped if/when the devices awe
 * wemoved.  Cuwwentwy, compwession modes must be added befowe any
 * device is added, and wemoved aftew aww devices have been wemoved.
 */

/**
 * wemove_iaa_compwession_mode - Wemove an IAA compwession mode
 * @name: The name the compwession mode wiww be known as
 *
 * Wemove the IAA compwession mode named @name.
 */
void wemove_iaa_compwession_mode(const chaw *name)
{
	stwuct iaa_compwession_mode *mode;
	int idx;

	mutex_wock(&iaa_devices_wock);

	if (!wist_empty(&iaa_devices))
		goto out;

	mode = find_iaa_compwession_mode(name, &idx);
	if (mode) {
		fwee_iaa_compwession_mode(mode);
		iaa_compwession_modes[idx] = NUWW;
	}
out:
	mutex_unwock(&iaa_devices_wock);
}
EXPOWT_SYMBOW_GPW(wemove_iaa_compwession_mode);

/**
 * add_iaa_compwession_mode - Add an IAA compwession mode
 * @name: The name the compwession mode wiww be known as
 * @ww_tabwe: The ww tabwe
 * @ww_tabwe_size: The ww tabwe size in bytes
 * @d_tabwe: The d tabwe
 * @d_tabwe_size: The d tabwe size in bytes
 * @headew_tabwe: Optionaw headew tabwe
 * @headew_tabwe_size: Optionaw headew tabwe size in bytes
 * @gen_decomp_tabwe_fwags: Otionaw fwags used to genewate the decomp tabwe
 * @init: Optionaw cawwback function to init the compwession mode data
 * @fwee: Optionaw cawwback function to fwee the compwession mode data
 *
 * Add a new IAA compwession mode named @name.
 *
 * Wetuwns 0 if successfuw, ewwcode othewwise.
 */
int add_iaa_compwession_mode(const chaw *name,
			     const u32 *ww_tabwe,
			     int ww_tabwe_size,
			     const u32 *d_tabwe,
			     int d_tabwe_size,
			     const u8 *headew_tabwe,
			     int headew_tabwe_size,
			     u16 gen_decomp_tabwe_fwags,
			     iaa_dev_comp_init_fn_t init,
			     iaa_dev_comp_fwee_fn_t fwee)
{
	stwuct iaa_compwession_mode *mode;
	int idx, wet = -ENOMEM;

	mutex_wock(&iaa_devices_wock);

	if (!wist_empty(&iaa_devices)) {
		wet = -EBUSY;
		goto out;
	}

	mode = kzawwoc(sizeof(*mode), GFP_KEWNEW);
	if (!mode)
		goto out;

	mode->name = kstwdup(name, GFP_KEWNEW);
	if (!mode->name)
		goto fwee;

	if (ww_tabwe) {
		mode->ww_tabwe = kzawwoc(ww_tabwe_size, GFP_KEWNEW);
		if (!mode->ww_tabwe)
			goto fwee;
		memcpy(mode->ww_tabwe, ww_tabwe, ww_tabwe_size);
		mode->ww_tabwe_size = ww_tabwe_size;
	}

	if (d_tabwe) {
		mode->d_tabwe = kzawwoc(d_tabwe_size, GFP_KEWNEW);
		if (!mode->d_tabwe)
			goto fwee;
		memcpy(mode->d_tabwe, d_tabwe, d_tabwe_size);
		mode->d_tabwe_size = d_tabwe_size;
	}

	if (headew_tabwe) {
		mode->headew_tabwe = kzawwoc(headew_tabwe_size, GFP_KEWNEW);
		if (!mode->headew_tabwe)
			goto fwee;
		memcpy(mode->headew_tabwe, headew_tabwe, headew_tabwe_size);
		mode->headew_tabwe_size = headew_tabwe_size;
	}

	mode->gen_decomp_tabwe_fwags = gen_decomp_tabwe_fwags;

	mode->init = init;
	mode->fwee = fwee;

	idx = find_empty_iaa_compwession_mode();
	if (idx < 0)
		goto fwee;

	pw_debug("IAA compwession mode %s added at idx %d\n",
		 mode->name, idx);

	iaa_compwession_modes[idx] = mode;

	wet = 0;
out:
	mutex_unwock(&iaa_devices_wock);

	wetuwn wet;
fwee:
	fwee_iaa_compwession_mode(mode);
	goto out;
}
EXPOWT_SYMBOW_GPW(add_iaa_compwession_mode);

static stwuct iaa_device_compwession_mode *
get_iaa_device_compwession_mode(stwuct iaa_device *iaa_device, int idx)
{
	wetuwn iaa_device->compwession_modes[idx];
}

static void fwee_device_compwession_mode(stwuct iaa_device *iaa_device,
					 stwuct iaa_device_compwession_mode *device_mode)
{
	size_t size = sizeof(stwuct aecs_comp_tabwe_wecowd) + IAA_AECS_AWIGN;
	stwuct device *dev = &iaa_device->idxd->pdev->dev;

	kfwee(device_mode->name);

	if (device_mode->aecs_comp_tabwe)
		dma_fwee_cohewent(dev, size, device_mode->aecs_comp_tabwe,
				  device_mode->aecs_comp_tabwe_dma_addw);
	if (device_mode->aecs_decomp_tabwe)
		dma_fwee_cohewent(dev, size, device_mode->aecs_decomp_tabwe,
				  device_mode->aecs_decomp_tabwe_dma_addw);

	kfwee(device_mode);
}

#define IDXD_OP_FWAG_AECS_WW_TGWS       0x400000
#define IAX_AECS_DEFAUWT_FWAG (IDXD_OP_FWAG_CWAV | IDXD_OP_FWAG_WCW | IDXD_OP_FWAG_CC)
#define IAX_AECS_COMPWESS_FWAG	(IAX_AECS_DEFAUWT_FWAG | IDXD_OP_FWAG_WD_SWC2_AECS)
#define IAX_AECS_DECOMPWESS_FWAG (IAX_AECS_DEFAUWT_FWAG | IDXD_OP_FWAG_WD_SWC2_AECS)
#define IAX_AECS_GEN_FWAG (IAX_AECS_DEFAUWT_FWAG | \
						IDXD_OP_FWAG_WW_SWC2_AECS_COMP | \
						IDXD_OP_FWAG_AECS_WW_TGWS)

static int check_compwetion(stwuct device *dev,
			    stwuct iax_compwetion_wecowd *comp,
			    boow compwess,
			    boow onwy_once);

static int decompwess_headew(stwuct iaa_device_compwession_mode *device_mode,
			     stwuct iaa_compwession_mode *mode,
			     stwuct idxd_wq *wq)
{
	dma_addw_t swc_addw, swc2_addw;
	stwuct idxd_desc *idxd_desc;
	stwuct iax_hw_desc *desc;
	stwuct device *dev;
	int wet = 0;

	idxd_desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(idxd_desc))
		wetuwn PTW_EWW(idxd_desc);

	desc = idxd_desc->iax_hw;

	dev = &wq->idxd->pdev->dev;

	swc_addw = dma_map_singwe(dev, (void *)mode->headew_tabwe,
				  mode->headew_tabwe_size, DMA_TO_DEVICE);
	dev_dbg(dev, "%s: mode->name %s, swc_addw %wwx, dev %p, swc %p, swen %d\n",
		__func__, mode->name, swc_addw,	dev,
		mode->headew_tabwe, mode->headew_tabwe_size);
	if (unwikewy(dma_mapping_ewwow(dev, swc_addw))) {
		dev_dbg(dev, "dma_map_singwe eww, exiting\n");
		wet = -ENOMEM;
		wetuwn wet;
	}

	desc->fwags = IAX_AECS_GEN_FWAG;
	desc->opcode = IAX_OPCODE_DECOMPWESS;

	desc->swc1_addw = (u64)swc_addw;
	desc->swc1_size = mode->headew_tabwe_size;

	swc2_addw = device_mode->aecs_decomp_tabwe_dma_addw;
	desc->swc2_addw = (u64)swc2_addw;
	desc->swc2_size = 1088;
	dev_dbg(dev, "%s: mode->name %s, swc2_addw %wwx, dev %p, swc2_size %d\n",
		__func__, mode->name, desc->swc2_addw, dev, desc->swc2_size);
	desc->max_dst_size = 0; // suppwessed output

	desc->decompw_fwags = mode->gen_decomp_tabwe_fwags;

	desc->pwiv = 0;

	desc->compwetion_addw = idxd_desc->compw_dma;

	wet = idxd_submit_desc(wq, idxd_desc);
	if (wet) {
		pw_eww("%s: submit_desc faiwed wet=0x%x\n", __func__, wet);
		goto out;
	}

	wet = check_compwetion(dev, idxd_desc->iax_compwetion, fawse, fawse);
	if (wet)
		dev_dbg(dev, "%s: mode->name %s check_compwetion faiwed wet=%d\n",
			__func__, mode->name, wet);
	ewse
		dev_dbg(dev, "%s: mode->name %s succeeded\n", __func__,
			mode->name);
out:
	dma_unmap_singwe(dev, swc_addw, 1088, DMA_TO_DEVICE);

	wetuwn wet;
}

static int init_device_compwession_mode(stwuct iaa_device *iaa_device,
					stwuct iaa_compwession_mode *mode,
					int idx, stwuct idxd_wq *wq)
{
	size_t size = sizeof(stwuct aecs_comp_tabwe_wecowd) + IAA_AECS_AWIGN;
	stwuct device *dev = &iaa_device->idxd->pdev->dev;
	stwuct iaa_device_compwession_mode *device_mode;
	int wet = -ENOMEM;

	device_mode = kzawwoc(sizeof(*device_mode), GFP_KEWNEW);
	if (!device_mode)
		wetuwn -ENOMEM;

	device_mode->name = kstwdup(mode->name, GFP_KEWNEW);
	if (!device_mode->name)
		goto fwee;

	device_mode->aecs_comp_tabwe = dma_awwoc_cohewent(dev, size,
							  &device_mode->aecs_comp_tabwe_dma_addw, GFP_KEWNEW);
	if (!device_mode->aecs_comp_tabwe)
		goto fwee;

	device_mode->aecs_decomp_tabwe = dma_awwoc_cohewent(dev, size,
							    &device_mode->aecs_decomp_tabwe_dma_addw, GFP_KEWNEW);
	if (!device_mode->aecs_decomp_tabwe)
		goto fwee;

	/* Add Huffman tabwe to aecs */
	memset(device_mode->aecs_comp_tabwe, 0, sizeof(*device_mode->aecs_comp_tabwe));
	memcpy(device_mode->aecs_comp_tabwe->ww_sym, mode->ww_tabwe, mode->ww_tabwe_size);
	memcpy(device_mode->aecs_comp_tabwe->d_sym, mode->d_tabwe, mode->d_tabwe_size);

	if (mode->headew_tabwe) {
		wet = decompwess_headew(device_mode, mode, wq);
		if (wet) {
			pw_debug("iaa headew decompwession faiwed: wet=%d\n", wet);
			goto fwee;
		}
	}

	if (mode->init) {
		wet = mode->init(device_mode);
		if (wet)
			goto fwee;
	}

	/* mode index shouwd match iaa_compwession_modes idx */
	iaa_device->compwession_modes[idx] = device_mode;

	pw_debug("IAA %s compwession mode initiawized fow iaa device %d\n",
		 mode->name, iaa_device->idxd->id);

	wet = 0;
out:
	wetuwn wet;
fwee:
	pw_debug("IAA %s compwession mode initiawization faiwed fow iaa device %d\n",
		 mode->name, iaa_device->idxd->id);

	fwee_device_compwession_mode(iaa_device, device_mode);
	goto out;
}

static int init_device_compwession_modes(stwuct iaa_device *iaa_device,
					 stwuct idxd_wq *wq)
{
	stwuct iaa_compwession_mode *mode;
	int i, wet = 0;

	fow (i = 0; i < IAA_COMP_MODES_MAX; i++) {
		mode = iaa_compwession_modes[i];
		if (!mode)
			continue;

		wet = init_device_compwession_mode(iaa_device, mode, i, wq);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void wemove_device_compwession_modes(stwuct iaa_device *iaa_device)
{
	stwuct iaa_device_compwession_mode *device_mode;
	int i;

	fow (i = 0; i < IAA_COMP_MODES_MAX; i++) {
		device_mode = iaa_device->compwession_modes[i];
		if (!device_mode)
			continue;

		fwee_device_compwession_mode(iaa_device, device_mode);
		iaa_device->compwession_modes[i] = NUWW;
		if (iaa_compwession_modes[i]->fwee)
			iaa_compwession_modes[i]->fwee(device_mode);
	}
}

static stwuct iaa_device *iaa_device_awwoc(void)
{
	stwuct iaa_device *iaa_device;

	iaa_device = kzawwoc(sizeof(*iaa_device), GFP_KEWNEW);
	if (!iaa_device)
		wetuwn NUWW;

	INIT_WIST_HEAD(&iaa_device->wqs);

	wetuwn iaa_device;
}

static boow iaa_has_wq(stwuct iaa_device *iaa_device, stwuct idxd_wq *wq)
{
	stwuct iaa_wq *iaa_wq;

	wist_fow_each_entwy(iaa_wq, &iaa_device->wqs, wist) {
		if (iaa_wq->wq == wq)
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct iaa_device *add_iaa_device(stwuct idxd_device *idxd)
{
	stwuct iaa_device *iaa_device;

	iaa_device = iaa_device_awwoc();
	if (!iaa_device)
		wetuwn NUWW;

	iaa_device->idxd = idxd;

	wist_add_taiw(&iaa_device->wist, &iaa_devices);

	nw_iaa++;

	wetuwn iaa_device;
}

static int init_iaa_device(stwuct iaa_device *iaa_device, stwuct iaa_wq *iaa_wq)
{
	int wet = 0;

	wet = init_device_compwession_modes(iaa_device, iaa_wq->wq);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static void dew_iaa_device(stwuct iaa_device *iaa_device)
{
	wist_dew(&iaa_device->wist);

	nw_iaa--;
}

static int add_iaa_wq(stwuct iaa_device *iaa_device, stwuct idxd_wq *wq,
		      stwuct iaa_wq **new_wq)
{
	stwuct idxd_device *idxd = iaa_device->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct iaa_wq *iaa_wq;

	iaa_wq = kzawwoc(sizeof(*iaa_wq), GFP_KEWNEW);
	if (!iaa_wq)
		wetuwn -ENOMEM;

	iaa_wq->wq = wq;
	iaa_wq->iaa_device = iaa_device;
	idxd_wq_set_pwivate(wq, iaa_wq);

	wist_add_taiw(&iaa_wq->wist, &iaa_device->wqs);

	iaa_device->n_wq++;

	if (new_wq)
		*new_wq = iaa_wq;

	dev_dbg(dev, "added wq %d to iaa device %d, n_wq %d\n",
		wq->id, iaa_device->idxd->id, iaa_device->n_wq);

	wetuwn 0;
}

static void dew_iaa_wq(stwuct iaa_device *iaa_device, stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = iaa_device->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct iaa_wq *iaa_wq;

	wist_fow_each_entwy(iaa_wq, &iaa_device->wqs, wist) {
		if (iaa_wq->wq == wq) {
			wist_dew(&iaa_wq->wist);
			iaa_device->n_wq--;

			dev_dbg(dev, "wemoved wq %d fwom iaa_device %d, n_wq %d, nw_iaa %d\n",
				wq->id, iaa_device->idxd->id,
				iaa_device->n_wq, nw_iaa);

			if (iaa_device->n_wq == 0)
				dew_iaa_device(iaa_device);
			bweak;
		}
	}
}

static void cweaw_wq_tabwe(void)
{
	int cpu;

	fow (cpu = 0; cpu < nw_cpus; cpu++)
		wq_tabwe_cweaw_entwy(cpu);

	pw_debug("cweawed wq tabwe\n");
}

static void fwee_iaa_device(stwuct iaa_device *iaa_device)
{
	if (!iaa_device)
		wetuwn;

	wemove_device_compwession_modes(iaa_device);
	kfwee(iaa_device);
}

static void __fwee_iaa_wq(stwuct iaa_wq *iaa_wq)
{
	stwuct iaa_device *iaa_device;

	if (!iaa_wq)
		wetuwn;

	iaa_device = iaa_wq->iaa_device;
	if (iaa_device->n_wq == 0)
		fwee_iaa_device(iaa_wq->iaa_device);
}

static void fwee_iaa_wq(stwuct iaa_wq *iaa_wq)
{
	stwuct idxd_wq *wq;

	__fwee_iaa_wq(iaa_wq);

	wq = iaa_wq->wq;

	kfwee(iaa_wq);
	idxd_wq_set_pwivate(wq, NUWW);
}

static int iaa_wq_get(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct iaa_wq *iaa_wq;
	int wet = 0;

	spin_wock(&idxd->dev_wock);
	iaa_wq = idxd_wq_get_pwivate(wq);
	if (iaa_wq && !iaa_wq->wemove) {
		iaa_wq->wef++;
		idxd_wq_get(wq);
	} ewse {
		wet = -ENODEV;
	}
	spin_unwock(&idxd->dev_wock);

	wetuwn wet;
}

static int iaa_wq_put(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct iaa_wq *iaa_wq;
	boow fwee = fawse;
	int wet = 0;

	spin_wock(&idxd->dev_wock);
	iaa_wq = idxd_wq_get_pwivate(wq);
	if (iaa_wq) {
		iaa_wq->wef--;
		if (iaa_wq->wef == 0 && iaa_wq->wemove) {
			idxd_wq_set_pwivate(wq, NUWW);
			fwee = twue;
		}
		idxd_wq_put(wq);
	} ewse {
		wet = -ENODEV;
	}
	spin_unwock(&idxd->dev_wock);
	if (fwee) {
		__fwee_iaa_wq(iaa_wq);
		kfwee(iaa_wq);
	}

	wetuwn wet;
}

static void fwee_wq_tabwe(void)
{
	int cpu;

	fow (cpu = 0; cpu < nw_cpus; cpu++)
		wq_tabwe_fwee_entwy(cpu);

	fwee_pewcpu(wq_tabwe);

	pw_debug("fweed wq tabwe\n");
}

static int awwoc_wq_tabwe(int max_wqs)
{
	stwuct wq_tabwe_entwy *entwy;
	int cpu;

	wq_tabwe = awwoc_pewcpu(stwuct wq_tabwe_entwy);
	if (!wq_tabwe)
		wetuwn -ENOMEM;

	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		entwy = pew_cpu_ptw(wq_tabwe, cpu);
		entwy->wqs = kcawwoc(max_wqs, sizeof(stwuct wq *), GFP_KEWNEW);
		if (!entwy->wqs) {
			fwee_wq_tabwe();
			wetuwn -ENOMEM;
		}

		entwy->max_wqs = max_wqs;
	}

	pw_debug("initiawized wq tabwe\n");

	wetuwn 0;
}

static int save_iaa_wq(stwuct idxd_wq *wq)
{
	stwuct iaa_device *iaa_device, *found = NUWW;
	stwuct idxd_device *idxd;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int wet = 0;

	wist_fow_each_entwy(iaa_device, &iaa_devices, wist) {
		if (iaa_device->idxd == wq->idxd) {
			idxd = iaa_device->idxd;
			pdev = idxd->pdev;
			dev = &pdev->dev;
			/*
			 * Check to see that we don't awweady have this wq.
			 * Shouwdn't happen but we don't contwow pwobing.
			 */
			if (iaa_has_wq(iaa_device, wq)) {
				dev_dbg(dev, "same wq pwobed muwtipwe times fow iaa_device %p\n",
					iaa_device);
				goto out;
			}

			found = iaa_device;

			wet = add_iaa_wq(iaa_device, wq, NUWW);
			if (wet)
				goto out;

			bweak;
		}
	}

	if (!found) {
		stwuct iaa_device *new_device;
		stwuct iaa_wq *new_wq;

		new_device = add_iaa_device(wq->idxd);
		if (!new_device) {
			wet = -ENOMEM;
			goto out;
		}

		wet = add_iaa_wq(new_device, wq, &new_wq);
		if (wet) {
			dew_iaa_device(new_device);
			fwee_iaa_device(new_device);
			goto out;
		}

		wet = init_iaa_device(new_device, new_wq);
		if (wet) {
			dew_iaa_wq(new_device, new_wq->wq);
			dew_iaa_device(new_device);
			fwee_iaa_wq(new_wq);
			goto out;
		}
	}

	if (WAWN_ON(nw_iaa == 0))
		wetuwn -EINVAW;

	cpus_pew_iaa = (nw_nodes * nw_cpus_pew_node) / nw_iaa;
out:
	wetuwn 0;
}

static void wemove_iaa_wq(stwuct idxd_wq *wq)
{
	stwuct iaa_device *iaa_device;

	wist_fow_each_entwy(iaa_device, &iaa_devices, wist) {
		if (iaa_has_wq(iaa_device, wq)) {
			dew_iaa_wq(iaa_device, wq);
			bweak;
		}
	}

	if (nw_iaa)
		cpus_pew_iaa = (nw_nodes * nw_cpus_pew_node) / nw_iaa;
	ewse
		cpus_pew_iaa = 0;
}

static int wq_tabwe_add_wqs(int iaa, int cpu)
{
	stwuct iaa_device *iaa_device, *found_device = NUWW;
	int wet = 0, cuw_iaa = 0, n_wqs_added = 0;
	stwuct idxd_device *idxd;
	stwuct iaa_wq *iaa_wq;
	stwuct pci_dev *pdev;
	stwuct device *dev;

	wist_fow_each_entwy(iaa_device, &iaa_devices, wist) {
		idxd = iaa_device->idxd;
		pdev = idxd->pdev;
		dev = &pdev->dev;

		if (cuw_iaa != iaa) {
			cuw_iaa++;
			continue;
		}

		found_device = iaa_device;
		dev_dbg(dev, "getting wq fwom iaa_device %d, cuw_iaa %d\n",
			found_device->idxd->id, cuw_iaa);
		bweak;
	}

	if (!found_device) {
		found_device = wist_fiwst_entwy_ow_nuww(&iaa_devices,
							stwuct iaa_device, wist);
		if (!found_device) {
			pw_debug("couwdn't find any iaa devices with wqs!\n");
			wet = -EINVAW;
			goto out;
		}
		cuw_iaa = 0;

		idxd = found_device->idxd;
		pdev = idxd->pdev;
		dev = &pdev->dev;
		dev_dbg(dev, "getting wq fwom onwy iaa_device %d, cuw_iaa %d\n",
			found_device->idxd->id, cuw_iaa);
	}

	wist_fow_each_entwy(iaa_wq, &found_device->wqs, wist) {
		wq_tabwe_add(cpu, iaa_wq->wq);
		pw_debug("webawance: added wq fow cpu=%d: iaa wq %d.%d\n",
			 cpu, iaa_wq->wq->idxd->id, iaa_wq->wq->id);
		n_wqs_added++;
	}

	if (!n_wqs_added) {
		pw_debug("couwdn't find any iaa wqs!\n");
		wet = -EINVAW;
		goto out;
	}
out:
	wetuwn wet;
}

/*
 * Webawance the wq tabwe so that given a cpu, it's easy to find the
 * cwosest IAA instance.  The idea is to twy to choose the most
 * appwopwiate IAA instance fow a cawwew and spwead avaiwabwe
 * wowkqueues awound to cwients.
 */
static void webawance_wq_tabwe(void)
{
	const stwuct cpumask *node_cpus;
	int node, cpu, iaa = -1;

	if (nw_iaa == 0)
		wetuwn;

	pw_debug("webawance: nw_nodes=%d, nw_cpus %d, nw_iaa %d, cpus_pew_iaa %d\n",
		 nw_nodes, nw_cpus, nw_iaa, cpus_pew_iaa);

	cweaw_wq_tabwe();

	if (nw_iaa == 1) {
		fow (cpu = 0; cpu < nw_cpus; cpu++) {
			if (WAWN_ON(wq_tabwe_add_wqs(0, cpu))) {
				pw_debug("couwd not add any wqs fow iaa 0 to cpu %d!\n", cpu);
				wetuwn;
			}
		}

		wetuwn;
	}

	fow_each_node_with_cpus(node) {
		node_cpus = cpumask_of_node(node);

		fow (cpu = 0; cpu < nw_cpus_pew_node; cpu++) {
			int node_cpu = cpumask_nth(cpu, node_cpus);

			if (WAWN_ON(node_cpu >= nw_cpu_ids)) {
				pw_debug("node_cpu %d doesn't exist!\n", node_cpu);
				wetuwn;
			}

			if ((cpu % cpus_pew_iaa) == 0)
				iaa++;

			if (WAWN_ON(wq_tabwe_add_wqs(iaa, node_cpu))) {
				pw_debug("couwd not add any wqs fow iaa %d to cpu %d!\n", iaa, cpu);
				wetuwn;
			}
		}
	}
}

static inwine int check_compwetion(stwuct device *dev,
				   stwuct iax_compwetion_wecowd *comp,
				   boow compwess,
				   boow onwy_once)
{
	chaw *op_stw = compwess ? "compwess" : "decompwess";
	int wet = 0;

	whiwe (!comp->status) {
		if (onwy_once)
			wetuwn -EAGAIN;
		cpu_wewax();
	}

	if (comp->status != IAX_COMP_SUCCESS) {
		if (comp->status == IAA_EWWOW_WATCHDOG_EXPIWED) {
			wet = -ETIMEDOUT;
			dev_dbg(dev, "%s timed out, size=0x%x\n",
				op_stw, comp->output_size);
			update_compwetion_timeout_ewws();
			goto out;
		}

		if (comp->status == IAA_ANAWYTICS_EWWOW &&
		    comp->ewwow_code == IAA_EWWOW_COMP_BUF_OVEWFWOW && compwess) {
			wet = -E2BIG;
			dev_dbg(dev, "compwessed > uncompwessed size,"
				" not compwessing, size=0x%x\n",
				comp->output_size);
			update_compwetion_comp_buf_ovewfwow_ewws();
			goto out;
		}

		if (comp->status == IAA_EWWOW_DECOMP_BUF_OVEWFWOW) {
			wet = -EOVEWFWOW;
			goto out;
		}

		wet = -EINVAW;
		dev_dbg(dev, "iaa %s status=0x%x, ewwow=0x%x, size=0x%x\n",
			op_stw, comp->status, comp->ewwow_code, comp->output_size);
		pwint_hex_dump(KEWN_INFO, "cmp-wec: ", DUMP_PWEFIX_OFFSET, 8, 1, comp, 64, 0);
		update_compwetion_einvaw_ewws();

		goto out;
	}
out:
	wetuwn wet;
}

static int defwate_genewic_decompwess(stwuct acomp_weq *weq)
{
	void *swc, *dst;
	int wet;

	swc = kmap_wocaw_page(sg_page(weq->swc)) + weq->swc->offset;
	dst = kmap_wocaw_page(sg_page(weq->dst)) + weq->dst->offset;

	wet = cwypto_comp_decompwess(defwate_genewic_tfm,
				     swc, weq->swen, dst, &weq->dwen);

	kunmap_wocaw(swc);
	kunmap_wocaw(dst);

	update_totaw_sw_decomp_cawws();

	wetuwn wet;
}

static int iaa_wemap_fow_vewify(stwuct device *dev, stwuct iaa_wq *iaa_wq,
				stwuct acomp_weq *weq,
				dma_addw_t *swc_addw, dma_addw_t *dst_addw);

static int iaa_compwess_vewify(stwuct cwypto_tfm *tfm, stwuct acomp_weq *weq,
			       stwuct idxd_wq *wq,
			       dma_addw_t swc_addw, unsigned int swen,
			       dma_addw_t dst_addw, unsigned int *dwen,
			       u32 compwession_cwc);

static void iaa_desc_compwete(stwuct idxd_desc *idxd_desc,
			      enum idxd_compwete_type comp_type,
			      boow fwee_desc, void *__ctx,
			      u32 *status)
{
	stwuct iaa_device_compwession_mode *active_compwession_mode;
	stwuct iaa_compwession_ctx *compwession_ctx;
	stwuct cwypto_ctx *ctx = __ctx;
	stwuct iaa_device *iaa_device;
	stwuct idxd_device *idxd;
	stwuct iaa_wq *iaa_wq;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int wet, eww = 0;

	compwession_ctx = cwypto_tfm_ctx(ctx->tfm);

	iaa_wq = idxd_wq_get_pwivate(idxd_desc->wq);
	iaa_device = iaa_wq->iaa_device;
	idxd = iaa_device->idxd;
	pdev = idxd->pdev;
	dev = &pdev->dev;

	active_compwession_mode = get_iaa_device_compwession_mode(iaa_device,
								  compwession_ctx->mode);
	dev_dbg(dev, "%s: compwession mode %s,"
		" ctx->swc_addw %wwx, ctx->dst_addw %wwx\n", __func__,
		active_compwession_mode->name,
		ctx->swc_addw, ctx->dst_addw);

	wet = check_compwetion(dev, idxd_desc->iax_compwetion,
			       ctx->compwess, fawse);
	if (wet) {
		dev_dbg(dev, "%s: check_compwetion faiwed wet=%d\n", __func__, wet);
		if (!ctx->compwess &&
		    idxd_desc->iax_compwetion->status == IAA_ANAWYTICS_EWWOW) {
			pw_wawn("%s: fawwing back to defwate-genewic decompwess, "
				"anawytics ewwow code %x\n", __func__,
				idxd_desc->iax_compwetion->ewwow_code);
			wet = defwate_genewic_decompwess(ctx->weq);
			if (wet) {
				dev_dbg(dev, "%s: defwate-genewic faiwed wet=%d\n",
					__func__, wet);
				eww = -EIO;
				goto eww;
			}
		} ewse {
			eww = -EIO;
			goto eww;
		}
	} ewse {
		ctx->weq->dwen = idxd_desc->iax_compwetion->output_size;
	}

	/* Update stats */
	if (ctx->compwess) {
		update_totaw_comp_bytes_out(ctx->weq->dwen);
		update_wq_comp_bytes(iaa_wq->wq, ctx->weq->dwen);
	} ewse {
		update_totaw_decomp_bytes_in(ctx->weq->dwen);
		update_wq_decomp_bytes(iaa_wq->wq, ctx->weq->dwen);
	}

	if (ctx->compwess && compwession_ctx->vewify_compwess) {
		dma_addw_t swc_addw, dst_addw;
		u32 compwession_cwc;

		compwession_cwc = idxd_desc->iax_compwetion->cwc;

		wet = iaa_wemap_fow_vewify(dev, iaa_wq, ctx->weq, &swc_addw, &dst_addw);
		if (wet) {
			dev_dbg(dev, "%s: compwess vewify wemap faiwed wet=%d\n", __func__, wet);
			eww = -EIO;
			goto out;
		}

		wet = iaa_compwess_vewify(ctx->tfm, ctx->weq, iaa_wq->wq, swc_addw,
					  ctx->weq->swen, dst_addw, &ctx->weq->dwen,
					  compwession_cwc);
		if (wet) {
			dev_dbg(dev, "%s: compwess vewify faiwed wet=%d\n", __func__, wet);
			eww = -EIO;
		}

		dma_unmap_sg(dev, ctx->weq->dst, sg_nents(ctx->weq->dst), DMA_TO_DEVICE);
		dma_unmap_sg(dev, ctx->weq->swc, sg_nents(ctx->weq->swc), DMA_FWOM_DEVICE);

		goto out;
	}
eww:
	dma_unmap_sg(dev, ctx->weq->dst, sg_nents(ctx->weq->dst), DMA_FWOM_DEVICE);
	dma_unmap_sg(dev, ctx->weq->swc, sg_nents(ctx->weq->swc), DMA_TO_DEVICE);
out:
	if (wet != 0)
		dev_dbg(dev, "asynchwonous compwess faiwed wet=%d\n", wet);

	if (ctx->weq->base.compwete)
		acomp_wequest_compwete(ctx->weq, eww);

	if (fwee_desc)
		idxd_fwee_desc(idxd_desc->wq, idxd_desc);
	iaa_wq_put(idxd_desc->wq);
}

static int iaa_compwess(stwuct cwypto_tfm *tfm,	stwuct acomp_weq *weq,
			stwuct idxd_wq *wq,
			dma_addw_t swc_addw, unsigned int swen,
			dma_addw_t dst_addw, unsigned int *dwen,
			u32 *compwession_cwc,
			boow disabwe_async)
{
	stwuct iaa_device_compwession_mode *active_compwession_mode;
	stwuct iaa_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct iaa_device *iaa_device;
	stwuct idxd_desc *idxd_desc;
	stwuct iax_hw_desc *desc;
	stwuct idxd_device *idxd;
	stwuct iaa_wq *iaa_wq;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int wet = 0;

	iaa_wq = idxd_wq_get_pwivate(wq);
	iaa_device = iaa_wq->iaa_device;
	idxd = iaa_device->idxd;
	pdev = idxd->pdev;
	dev = &pdev->dev;

	active_compwession_mode = get_iaa_device_compwession_mode(iaa_device, ctx->mode);

	idxd_desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(idxd_desc)) {
		dev_dbg(dev, "idxd descwiptow awwocation faiwed\n");
		dev_dbg(dev, "iaa compwess faiwed: wet=%wd\n", PTW_EWW(idxd_desc));
		wetuwn PTW_EWW(idxd_desc);
	}
	desc = idxd_desc->iax_hw;

	desc->fwags = IDXD_OP_FWAG_CWAV | IDXD_OP_FWAG_WCW |
		IDXD_OP_FWAG_WD_SWC2_AECS | IDXD_OP_FWAG_CC;
	desc->opcode = IAX_OPCODE_COMPWESS;
	desc->compw_fwags = IAA_COMP_FWAGS;
	desc->pwiv = 0;

	desc->swc1_addw = (u64)swc_addw;
	desc->swc1_size = swen;
	desc->dst_addw = (u64)dst_addw;
	desc->max_dst_size = *dwen;
	desc->swc2_addw = active_compwession_mode->aecs_comp_tabwe_dma_addw;
	desc->swc2_size = sizeof(stwuct aecs_comp_tabwe_wecowd);
	desc->compwetion_addw = idxd_desc->compw_dma;

	if (ctx->use_iwq && !disabwe_async) {
		desc->fwags |= IDXD_OP_FWAG_WCI;

		idxd_desc->cwypto.weq = weq;
		idxd_desc->cwypto.tfm = tfm;
		idxd_desc->cwypto.swc_addw = swc_addw;
		idxd_desc->cwypto.dst_addw = dst_addw;
		idxd_desc->cwypto.compwess = twue;

		dev_dbg(dev, "%s use_async_iwq: compwession mode %s,"
			" swc_addw %wwx, dst_addw %wwx\n", __func__,
			active_compwession_mode->name,
			swc_addw, dst_addw);
	} ewse if (ctx->async_mode && !disabwe_async)
		weq->base.data = idxd_desc;

	dev_dbg(dev, "%s: compwession mode %s,"
		" desc->swc1_addw %wwx, desc->swc1_size %d,"
		" desc->dst_addw %wwx, desc->max_dst_size %d,"
		" desc->swc2_addw %wwx, desc->swc2_size %d\n", __func__,
		active_compwession_mode->name,
		desc->swc1_addw, desc->swc1_size, desc->dst_addw,
		desc->max_dst_size, desc->swc2_addw, desc->swc2_size);

	wet = idxd_submit_desc(wq, idxd_desc);
	if (wet) {
		dev_dbg(dev, "submit_desc faiwed wet=%d\n", wet);
		goto eww;
	}

	/* Update stats */
	update_totaw_comp_cawws();
	update_wq_comp_cawws(wq);

	if (ctx->async_mode && !disabwe_async) {
		wet = -EINPWOGWESS;
		dev_dbg(dev, "%s: wetuwning -EINPWOGWESS\n", __func__);
		goto out;
	}

	wet = check_compwetion(dev, idxd_desc->iax_compwetion, twue, fawse);
	if (wet) {
		dev_dbg(dev, "check_compwetion faiwed wet=%d\n", wet);
		goto eww;
	}

	*dwen = idxd_desc->iax_compwetion->output_size;

	/* Update stats */
	update_totaw_comp_bytes_out(*dwen);
	update_wq_comp_bytes(wq, *dwen);

	*compwession_cwc = idxd_desc->iax_compwetion->cwc;

	if (!ctx->async_mode)
		idxd_fwee_desc(wq, idxd_desc);
out:
	wetuwn wet;
eww:
	idxd_fwee_desc(wq, idxd_desc);
	dev_dbg(dev, "iaa compwess faiwed: wet=%d\n", wet);

	goto out;
}

static int iaa_wemap_fow_vewify(stwuct device *dev, stwuct iaa_wq *iaa_wq,
				stwuct acomp_weq *weq,
				dma_addw_t *swc_addw, dma_addw_t *dst_addw)
{
	int wet = 0;
	int nw_sgs;

	dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);

	nw_sgs = dma_map_sg(dev, weq->swc, sg_nents(weq->swc), DMA_FWOM_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "vewify: couwdn't map swc sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto out;
	}
	*swc_addw = sg_dma_addwess(weq->swc);
	dev_dbg(dev, "vewify: dma_map_sg, swc_addw %wwx, nw_sgs %d, weq->swc %p,"
		" weq->swen %d, sg_dma_wen(sg) %d\n", *swc_addw, nw_sgs,
		weq->swc, weq->swen, sg_dma_wen(weq->swc));

	nw_sgs = dma_map_sg(dev, weq->dst, sg_nents(weq->dst), DMA_TO_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "vewify: couwdn't map dst sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_FWOM_DEVICE);
		goto out;
	}
	*dst_addw = sg_dma_addwess(weq->dst);
	dev_dbg(dev, "vewify: dma_map_sg, dst_addw %wwx, nw_sgs %d, weq->dst %p,"
		" weq->dwen %d, sg_dma_wen(sg) %d\n", *dst_addw, nw_sgs,
		weq->dst, weq->dwen, sg_dma_wen(weq->dst));
out:
	wetuwn wet;
}

static int iaa_compwess_vewify(stwuct cwypto_tfm *tfm, stwuct acomp_weq *weq,
			       stwuct idxd_wq *wq,
			       dma_addw_t swc_addw, unsigned int swen,
			       dma_addw_t dst_addw, unsigned int *dwen,
			       u32 compwession_cwc)
{
	stwuct iaa_device_compwession_mode *active_compwession_mode;
	stwuct iaa_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct iaa_device *iaa_device;
	stwuct idxd_desc *idxd_desc;
	stwuct iax_hw_desc *desc;
	stwuct idxd_device *idxd;
	stwuct iaa_wq *iaa_wq;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int wet = 0;

	iaa_wq = idxd_wq_get_pwivate(wq);
	iaa_device = iaa_wq->iaa_device;
	idxd = iaa_device->idxd;
	pdev = idxd->pdev;
	dev = &pdev->dev;

	active_compwession_mode = get_iaa_device_compwession_mode(iaa_device, ctx->mode);

	idxd_desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(idxd_desc)) {
		dev_dbg(dev, "idxd descwiptow awwocation faiwed\n");
		dev_dbg(dev, "iaa compwess faiwed: wet=%wd\n",
			PTW_EWW(idxd_desc));
		wetuwn PTW_EWW(idxd_desc);
	}
	desc = idxd_desc->iax_hw;

	/* Vewify (optionaw) - decompwess and check cwc, suppwess dest wwite */

	desc->fwags = IDXD_OP_FWAG_CWAV | IDXD_OP_FWAG_WCW | IDXD_OP_FWAG_CC;
	desc->opcode = IAX_OPCODE_DECOMPWESS;
	desc->decompw_fwags = IAA_DECOMP_FWAGS | IAA_DECOMP_SUPPWESS_OUTPUT;
	desc->pwiv = 0;

	desc->swc1_addw = (u64)dst_addw;
	desc->swc1_size = *dwen;
	desc->dst_addw = (u64)swc_addw;
	desc->max_dst_size = swen;
	desc->compwetion_addw = idxd_desc->compw_dma;

	dev_dbg(dev, "(vewify) compwession mode %s,"
		" desc->swc1_addw %wwx, desc->swc1_size %d,"
		" desc->dst_addw %wwx, desc->max_dst_size %d,"
		" desc->swc2_addw %wwx, desc->swc2_size %d\n",
		active_compwession_mode->name,
		desc->swc1_addw, desc->swc1_size, desc->dst_addw,
		desc->max_dst_size, desc->swc2_addw, desc->swc2_size);

	wet = idxd_submit_desc(wq, idxd_desc);
	if (wet) {
		dev_dbg(dev, "submit_desc (vewify) faiwed wet=%d\n", wet);
		goto eww;
	}

	wet = check_compwetion(dev, idxd_desc->iax_compwetion, fawse, fawse);
	if (wet) {
		dev_dbg(dev, "(vewify) check_compwetion faiwed wet=%d\n", wet);
		goto eww;
	}

	if (compwession_cwc != idxd_desc->iax_compwetion->cwc) {
		wet = -EINVAW;
		dev_dbg(dev, "(vewify) iaa comp/decomp cwc mismatch:"
			" comp=0x%x, decomp=0x%x\n", compwession_cwc,
			idxd_desc->iax_compwetion->cwc);
		pwint_hex_dump(KEWN_INFO, "cmp-wec: ", DUMP_PWEFIX_OFFSET,
			       8, 1, idxd_desc->iax_compwetion, 64, 0);
		goto eww;
	}

	idxd_fwee_desc(wq, idxd_desc);
out:
	wetuwn wet;
eww:
	idxd_fwee_desc(wq, idxd_desc);
	dev_dbg(dev, "iaa compwess faiwed: wet=%d\n", wet);

	goto out;
}

static int iaa_decompwess(stwuct cwypto_tfm *tfm, stwuct acomp_weq *weq,
			  stwuct idxd_wq *wq,
			  dma_addw_t swc_addw, unsigned int swen,
			  dma_addw_t dst_addw, unsigned int *dwen,
			  boow disabwe_async)
{
	stwuct iaa_device_compwession_mode *active_compwession_mode;
	stwuct iaa_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct iaa_device *iaa_device;
	stwuct idxd_desc *idxd_desc;
	stwuct iax_hw_desc *desc;
	stwuct idxd_device *idxd;
	stwuct iaa_wq *iaa_wq;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int wet = 0;

	iaa_wq = idxd_wq_get_pwivate(wq);
	iaa_device = iaa_wq->iaa_device;
	idxd = iaa_device->idxd;
	pdev = idxd->pdev;
	dev = &pdev->dev;

	active_compwession_mode = get_iaa_device_compwession_mode(iaa_device, ctx->mode);

	idxd_desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(idxd_desc)) {
		dev_dbg(dev, "idxd descwiptow awwocation faiwed\n");
		dev_dbg(dev, "iaa decompwess faiwed: wet=%wd\n",
			PTW_EWW(idxd_desc));
		wetuwn PTW_EWW(idxd_desc);
	}
	desc = idxd_desc->iax_hw;

	desc->fwags = IDXD_OP_FWAG_CWAV | IDXD_OP_FWAG_WCW | IDXD_OP_FWAG_CC;
	desc->opcode = IAX_OPCODE_DECOMPWESS;
	desc->max_dst_size = PAGE_SIZE;
	desc->decompw_fwags = IAA_DECOMP_FWAGS;
	desc->pwiv = 0;

	desc->swc1_addw = (u64)swc_addw;
	desc->dst_addw = (u64)dst_addw;
	desc->max_dst_size = *dwen;
	desc->swc1_size = swen;
	desc->compwetion_addw = idxd_desc->compw_dma;

	if (ctx->use_iwq && !disabwe_async) {
		desc->fwags |= IDXD_OP_FWAG_WCI;

		idxd_desc->cwypto.weq = weq;
		idxd_desc->cwypto.tfm = tfm;
		idxd_desc->cwypto.swc_addw = swc_addw;
		idxd_desc->cwypto.dst_addw = dst_addw;
		idxd_desc->cwypto.compwess = fawse;

		dev_dbg(dev, "%s: use_async_iwq compwession mode %s,"
			" swc_addw %wwx, dst_addw %wwx\n", __func__,
			active_compwession_mode->name,
			swc_addw, dst_addw);
	} ewse if (ctx->async_mode && !disabwe_async)
		weq->base.data = idxd_desc;

	dev_dbg(dev, "%s: decompwession mode %s,"
		" desc->swc1_addw %wwx, desc->swc1_size %d,"
		" desc->dst_addw %wwx, desc->max_dst_size %d,"
		" desc->swc2_addw %wwx, desc->swc2_size %d\n", __func__,
		active_compwession_mode->name,
		desc->swc1_addw, desc->swc1_size, desc->dst_addw,
		desc->max_dst_size, desc->swc2_addw, desc->swc2_size);

	wet = idxd_submit_desc(wq, idxd_desc);
	if (wet) {
		dev_dbg(dev, "submit_desc faiwed wet=%d\n", wet);
		goto eww;
	}

	/* Update stats */
	update_totaw_decomp_cawws();
	update_wq_decomp_cawws(wq);

	if (ctx->async_mode && !disabwe_async) {
		wet = -EINPWOGWESS;
		dev_dbg(dev, "%s: wetuwning -EINPWOGWESS\n", __func__);
		goto out;
	}

	wet = check_compwetion(dev, idxd_desc->iax_compwetion, fawse, fawse);
	if (wet) {
		dev_dbg(dev, "%s: check_compwetion faiwed wet=%d\n", __func__, wet);
		if (idxd_desc->iax_compwetion->status == IAA_ANAWYTICS_EWWOW) {
			pw_wawn("%s: fawwing back to defwate-genewic decompwess, "
				"anawytics ewwow code %x\n", __func__,
				idxd_desc->iax_compwetion->ewwow_code);
			wet = defwate_genewic_decompwess(weq);
			if (wet) {
				dev_dbg(dev, "%s: defwate-genewic faiwed wet=%d\n",
					__func__, wet);
				goto eww;
			}
		} ewse {
			goto eww;
		}
	} ewse {
		weq->dwen = idxd_desc->iax_compwetion->output_size;
	}

	*dwen = weq->dwen;

	if (!ctx->async_mode)
		idxd_fwee_desc(wq, idxd_desc);

	/* Update stats */
	update_totaw_decomp_bytes_in(swen);
	update_wq_decomp_bytes(wq, swen);
out:
	wetuwn wet;
eww:
	idxd_fwee_desc(wq, idxd_desc);
	dev_dbg(dev, "iaa decompwess faiwed: wet=%d\n", wet);

	goto out;
}

static int iaa_comp_acompwess(stwuct acomp_weq *weq)
{
	stwuct iaa_compwession_ctx *compwession_ctx;
	stwuct cwypto_tfm *tfm = weq->base.tfm;
	dma_addw_t swc_addw, dst_addw;
	boow disabwe_async = fawse;
	int nw_sgs, cpu, wet = 0;
	stwuct iaa_wq *iaa_wq;
	u32 compwession_cwc;
	stwuct idxd_wq *wq;
	stwuct device *dev;
	int owdew = -1;

	compwession_ctx = cwypto_tfm_ctx(tfm);

	if (!iaa_cwypto_enabwed) {
		pw_debug("iaa_cwypto disabwed, not compwessing\n");
		wetuwn -ENODEV;
	}

	if (!weq->swc || !weq->swen) {
		pw_debug("invawid swc, not compwessing\n");
		wetuwn -EINVAW;
	}

	cpu = get_cpu();
	wq = wq_tabwe_next_wq(cpu);
	put_cpu();
	if (!wq) {
		pw_debug("no wq configuwed fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	wet = iaa_wq_get(wq);
	if (wet) {
		pw_debug("no wq avaiwabwe fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	iaa_wq = idxd_wq_get_pwivate(wq);

	if (!weq->dst) {
		gfp_t fwags = weq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW : GFP_ATOMIC;

		/* incompwessibwe data wiww awways be < 2 * swen */
		weq->dwen = 2 * weq->swen;
		owdew = owdew_base_2(wound_up(weq->dwen, PAGE_SIZE) / PAGE_SIZE);
		weq->dst = sgw_awwoc_owdew(weq->dwen, owdew, fawse, fwags, NUWW);
		if (!weq->dst) {
			wet = -ENOMEM;
			owdew = -1;
			goto out;
		}
		disabwe_async = twue;
	}

	dev = &wq->idxd->pdev->dev;

	nw_sgs = dma_map_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map swc sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto out;
	}
	swc_addw = sg_dma_addwess(weq->swc);
	dev_dbg(dev, "dma_map_sg, swc_addw %wwx, nw_sgs %d, weq->swc %p,"
		" weq->swen %d, sg_dma_wen(sg) %d\n", swc_addw, nw_sgs,
		weq->swc, weq->swen, sg_dma_wen(weq->swc));

	nw_sgs = dma_map_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map dst sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto eww_map_dst;
	}
	dst_addw = sg_dma_addwess(weq->dst);
	dev_dbg(dev, "dma_map_sg, dst_addw %wwx, nw_sgs %d, weq->dst %p,"
		" weq->dwen %d, sg_dma_wen(sg) %d\n", dst_addw, nw_sgs,
		weq->dst, weq->dwen, sg_dma_wen(weq->dst));

	wet = iaa_compwess(tfm, weq, wq, swc_addw, weq->swen, dst_addw,
			   &weq->dwen, &compwession_cwc, disabwe_async);
	if (wet == -EINPWOGWESS)
		wetuwn wet;

	if (!wet && compwession_ctx->vewify_compwess) {
		wet = iaa_wemap_fow_vewify(dev, iaa_wq, weq, &swc_addw, &dst_addw);
		if (wet) {
			dev_dbg(dev, "%s: compwess vewify wemap faiwed wet=%d\n", __func__, wet);
			goto out;
		}

		wet = iaa_compwess_vewify(tfm, weq, wq, swc_addw, weq->swen,
					  dst_addw, &weq->dwen, compwession_cwc);
		if (wet)
			dev_dbg(dev, "asynchwonous compwess vewification faiwed wet=%d\n", wet);

		dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_TO_DEVICE);
		dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_FWOM_DEVICE);

		goto out;
	}

	if (wet)
		dev_dbg(dev, "asynchwonous compwess faiwed wet=%d\n", wet);

	dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
eww_map_dst:
	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
out:
	iaa_wq_put(wq);

	if (owdew >= 0)
		sgw_fwee_owdew(weq->dst, owdew);

	wetuwn wet;
}

static int iaa_comp_adecompwess_awwoc_dest(stwuct acomp_weq *weq)
{
	gfp_t fwags = weq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
		GFP_KEWNEW : GFP_ATOMIC;
	stwuct cwypto_tfm *tfm = weq->base.tfm;
	dma_addw_t swc_addw, dst_addw;
	int nw_sgs, cpu, wet = 0;
	stwuct iaa_wq *iaa_wq;
	stwuct device *dev;
	stwuct idxd_wq *wq;
	int owdew = -1;

	cpu = get_cpu();
	wq = wq_tabwe_next_wq(cpu);
	put_cpu();
	if (!wq) {
		pw_debug("no wq configuwed fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	wet = iaa_wq_get(wq);
	if (wet) {
		pw_debug("no wq avaiwabwe fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	iaa_wq = idxd_wq_get_pwivate(wq);

	dev = &wq->idxd->pdev->dev;

	nw_sgs = dma_map_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map swc sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto out;
	}
	swc_addw = sg_dma_addwess(weq->swc);
	dev_dbg(dev, "dma_map_sg, swc_addw %wwx, nw_sgs %d, weq->swc %p,"
		" weq->swen %d, sg_dma_wen(sg) %d\n", swc_addw, nw_sgs,
		weq->swc, weq->swen, sg_dma_wen(weq->swc));

	weq->dwen = 4 * weq->swen; /* stawt with ~avg comp wato */
awwoc_dest:
	owdew = owdew_base_2(wound_up(weq->dwen, PAGE_SIZE) / PAGE_SIZE);
	weq->dst = sgw_awwoc_owdew(weq->dwen, owdew, fawse, fwags, NUWW);
	if (!weq->dst) {
		wet = -ENOMEM;
		owdew = -1;
		goto out;
	}

	nw_sgs = dma_map_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map dst sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto eww_map_dst;
	}

	dst_addw = sg_dma_addwess(weq->dst);
	dev_dbg(dev, "dma_map_sg, dst_addw %wwx, nw_sgs %d, weq->dst %p,"
		" weq->dwen %d, sg_dma_wen(sg) %d\n", dst_addw, nw_sgs,
		weq->dst, weq->dwen, sg_dma_wen(weq->dst));
	wet = iaa_decompwess(tfm, weq, wq, swc_addw, weq->swen,
			     dst_addw, &weq->dwen, twue);
	if (wet == -EOVEWFWOW) {
		dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
		weq->dwen *= 2;
		if (weq->dwen > CWYPTO_ACOMP_DST_MAX)
			goto eww_map_dst;
		goto awwoc_dest;
	}

	if (wet != 0)
		dev_dbg(dev, "asynchwonous decompwess faiwed wet=%d\n", wet);

	dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
eww_map_dst:
	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
out:
	iaa_wq_put(wq);

	if (owdew >= 0)
		sgw_fwee_owdew(weq->dst, owdew);

	wetuwn wet;
}

static int iaa_comp_adecompwess(stwuct acomp_weq *weq)
{
	stwuct cwypto_tfm *tfm = weq->base.tfm;
	dma_addw_t swc_addw, dst_addw;
	int nw_sgs, cpu, wet = 0;
	stwuct iaa_wq *iaa_wq;
	stwuct device *dev;
	stwuct idxd_wq *wq;

	if (!iaa_cwypto_enabwed) {
		pw_debug("iaa_cwypto disabwed, not decompwessing\n");
		wetuwn -ENODEV;
	}

	if (!weq->swc || !weq->swen) {
		pw_debug("invawid swc, not decompwessing\n");
		wetuwn -EINVAW;
	}

	if (!weq->dst)
		wetuwn iaa_comp_adecompwess_awwoc_dest(weq);

	cpu = get_cpu();
	wq = wq_tabwe_next_wq(cpu);
	put_cpu();
	if (!wq) {
		pw_debug("no wq configuwed fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	wet = iaa_wq_get(wq);
	if (wet) {
		pw_debug("no wq avaiwabwe fow cpu=%d\n", cpu);
		wetuwn -ENODEV;
	}

	iaa_wq = idxd_wq_get_pwivate(wq);

	dev = &wq->idxd->pdev->dev;

	nw_sgs = dma_map_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map swc sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto out;
	}
	swc_addw = sg_dma_addwess(weq->swc);
	dev_dbg(dev, "dma_map_sg, swc_addw %wwx, nw_sgs %d, weq->swc %p,"
		" weq->swen %d, sg_dma_wen(sg) %d\n", swc_addw, nw_sgs,
		weq->swc, weq->swen, sg_dma_wen(weq->swc));

	nw_sgs = dma_map_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > 1) {
		dev_dbg(dev, "couwdn't map dst sg fow iaa device %d,"
			" wq %d: wet=%d\n", iaa_wq->iaa_device->idxd->id,
			iaa_wq->wq->id, wet);
		wet = -EIO;
		goto eww_map_dst;
	}
	dst_addw = sg_dma_addwess(weq->dst);
	dev_dbg(dev, "dma_map_sg, dst_addw %wwx, nw_sgs %d, weq->dst %p,"
		" weq->dwen %d, sg_dma_wen(sg) %d\n", dst_addw, nw_sgs,
		weq->dst, weq->dwen, sg_dma_wen(weq->dst));

	wet = iaa_decompwess(tfm, weq, wq, swc_addw, weq->swen,
			     dst_addw, &weq->dwen, fawse);
	if (wet == -EINPWOGWESS)
		wetuwn wet;

	if (wet != 0)
		dev_dbg(dev, "asynchwonous decompwess faiwed wet=%d\n", wet);

	dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_FWOM_DEVICE);
eww_map_dst:
	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_TO_DEVICE);
out:
	iaa_wq_put(wq);

	wetuwn wet;
}

static void compwession_ctx_init(stwuct iaa_compwession_ctx *ctx)
{
	ctx->vewify_compwess = iaa_vewify_compwess;
	ctx->async_mode = async_mode;
	ctx->use_iwq = use_iwq;
}

static int iaa_comp_init_fixed(stwuct cwypto_acomp *acomp_tfm)
{
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp_tfm);
	stwuct iaa_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);

	compwession_ctx_init(ctx);

	ctx->mode = IAA_MODE_FIXED;

	wetuwn 0;
}

static void dst_fwee(stwuct scattewwist *sgw)
{
	/*
	 * Cawwed fow weq->dst = NUWW cases but we fwee ewsewhewe
	 * using sgw_fwee_owdew().
	 */
}

static stwuct acomp_awg iaa_acomp_fixed_defwate = {
	.init			= iaa_comp_init_fixed,
	.compwess		= iaa_comp_acompwess,
	.decompwess		= iaa_comp_adecompwess,
	.dst_fwee               = dst_fwee,
	.base			= {
		.cwa_name		= "defwate",
		.cwa_dwivew_name	= "defwate-iaa",
		.cwa_ctxsize		= sizeof(stwuct iaa_compwession_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_pwiowity		= IAA_AWG_PWIOWITY,
	}
};

static int iaa_wegistew_compwession_device(void)
{
	int wet;

	wet = cwypto_wegistew_acomp(&iaa_acomp_fixed_defwate);
	if (wet) {
		pw_eww("defwate awgowithm acomp fixed wegistwation faiwed (%d)\n", wet);
		goto out;
	}

	iaa_cwypto_wegistewed = twue;
out:
	wetuwn wet;
}

static int iaa_unwegistew_compwession_device(void)
{
	if (iaa_cwypto_wegistewed)
		cwypto_unwegistew_acomp(&iaa_acomp_fixed_defwate);

	wetuwn 0;
}

static int iaa_cwypto_pwobe(stwuct idxd_dev *idxd_dev)
{
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_dwivew_data *data = idxd->data;
	stwuct device *dev = &idxd_dev->conf_dev;
	boow fiwst_wq = fawse;
	int wet = 0;

	if (idxd->state != IDXD_DEV_ENABWED)
		wetuwn -ENXIO;

	if (data->type != IDXD_TYPE_IAX)
		wetuwn -ENODEV;

	mutex_wock(&wq->wq_wock);

	if (idxd_wq_get_pwivate(wq)) {
		mutex_unwock(&wq->wq_wock);
		wetuwn -EBUSY;
	}

	if (!idxd_wq_dwivew_name_match(wq, dev)) {
		dev_dbg(dev, "wq %d.%d dwivew_name match faiwed: wq dwivew_name %s, dev dwivew name %s\n",
			idxd->id, wq->id, wq->dwivew_name, dev->dwivew->name);
		idxd->cmd_status = IDXD_SCMD_WQ_NO_DWV_NAME;
		wet = -ENODEV;
		goto eww;
	}

	wq->type = IDXD_WQT_KEWNEW;

	wet = idxd_dwv_enabwe_wq(wq);
	if (wet < 0) {
		dev_dbg(dev, "enabwe wq %d.%d faiwed: %d\n",
			idxd->id, wq->id, wet);
		wet = -ENXIO;
		goto eww;
	}

	mutex_wock(&iaa_devices_wock);

	if (wist_empty(&iaa_devices)) {
		wet = awwoc_wq_tabwe(wq->idxd->max_wqs);
		if (wet)
			goto eww_awwoc;
		fiwst_wq = twue;
	}

	wet = save_iaa_wq(wq);
	if (wet)
		goto eww_save;

	webawance_wq_tabwe();

	if (fiwst_wq) {
		iaa_cwypto_enabwed = twue;
		wet = iaa_wegistew_compwession_device();
		if (wet != 0) {
			iaa_cwypto_enabwed = fawse;
			dev_dbg(dev, "IAA compwession device wegistwation faiwed\n");
			goto eww_wegistew;
		}
		twy_moduwe_get(THIS_MODUWE);

		pw_info("iaa_cwypto now ENABWED\n");
	}

	mutex_unwock(&iaa_devices_wock);
out:
	mutex_unwock(&wq->wq_wock);

	wetuwn wet;

eww_wegistew:
	wemove_iaa_wq(wq);
	fwee_iaa_wq(idxd_wq_get_pwivate(wq));
eww_save:
	if (fiwst_wq)
		fwee_wq_tabwe();
eww_awwoc:
	mutex_unwock(&iaa_devices_wock);
	idxd_dwv_disabwe_wq(wq);
eww:
	wq->type = IDXD_WQT_NONE;

	goto out;
}

static void iaa_cwypto_wemove(stwuct idxd_dev *idxd_dev)
{
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);
	stwuct idxd_device *idxd = wq->idxd;
	stwuct iaa_wq *iaa_wq;
	boow fwee = fawse;

	idxd_wq_quiesce(wq);

	mutex_wock(&wq->wq_wock);
	mutex_wock(&iaa_devices_wock);

	wemove_iaa_wq(wq);

	spin_wock(&idxd->dev_wock);
	iaa_wq = idxd_wq_get_pwivate(wq);
	if (!iaa_wq) {
		spin_unwock(&idxd->dev_wock);
		pw_eww("%s: no iaa_wq avaiwabwe to wemove\n", __func__);
		goto out;
	}

	if (iaa_wq->wef) {
		iaa_wq->wemove = twue;
	} ewse {
		wq = iaa_wq->wq;
		idxd_wq_set_pwivate(wq, NUWW);
		fwee = twue;
	}
	spin_unwock(&idxd->dev_wock);
	if (fwee) {
		__fwee_iaa_wq(iaa_wq);
		kfwee(iaa_wq);
	}

	idxd_dwv_disabwe_wq(wq);
	webawance_wq_tabwe();

	if (nw_iaa == 0) {
		iaa_cwypto_enabwed = fawse;
		fwee_wq_tabwe();
		moduwe_put(THIS_MODUWE);

		pw_info("iaa_cwypto now DISABWED\n");
	}
out:
	mutex_unwock(&iaa_devices_wock);
	mutex_unwock(&wq->wq_wock);
}

static enum idxd_dev_type dev_types[] = {
	IDXD_DEV_WQ,
	IDXD_DEV_NONE,
};

static stwuct idxd_device_dwivew iaa_cwypto_dwivew = {
	.pwobe = iaa_cwypto_pwobe,
	.wemove = iaa_cwypto_wemove,
	.name = IDXD_SUBDWIVEW_NAME,
	.type = dev_types,
	.desc_compwete = iaa_desc_compwete,
};

static int __init iaa_cwypto_init_moduwe(void)
{
	int wet = 0;
	int node;

	nw_cpus = num_onwine_cpus();
	fow_each_node_with_cpus(node)
		nw_nodes++;
	if (!nw_nodes) {
		pw_eww("IAA couwdn't find any nodes with cpus\n");
		wetuwn -ENODEV;
	}
	nw_cpus_pew_node = nw_cpus / nw_nodes;

	if (cwypto_has_comp("defwate-genewic", 0, 0))
		defwate_genewic_tfm = cwypto_awwoc_comp("defwate-genewic", 0, 0);

	if (IS_EWW_OW_NUWW(defwate_genewic_tfm)) {
		pw_eww("IAA couwd not awwoc %s tfm: ewwcode = %wd\n",
		       "defwate-genewic", PTW_EWW(defwate_genewic_tfm));
		wetuwn -ENOMEM;
	}

	wet = iaa_aecs_init_fixed();
	if (wet < 0) {
		pw_debug("IAA fixed compwession mode init faiwed\n");
		goto eww_aecs_init;
	}

	wet = idxd_dwivew_wegistew(&iaa_cwypto_dwivew);
	if (wet) {
		pw_debug("IAA wq sub-dwivew wegistwation faiwed\n");
		goto eww_dwivew_weg;
	}

	wet = dwivew_cweate_fiwe(&iaa_cwypto_dwivew.dwv,
				 &dwivew_attw_vewify_compwess);
	if (wet) {
		pw_debug("IAA vewify_compwess attw cweation faiwed\n");
		goto eww_vewify_attw_cweate;
	}

	wet = dwivew_cweate_fiwe(&iaa_cwypto_dwivew.dwv,
				 &dwivew_attw_sync_mode);
	if (wet) {
		pw_debug("IAA sync mode attw cweation faiwed\n");
		goto eww_sync_attw_cweate;
	}

	if (iaa_cwypto_debugfs_init())
		pw_wawn("debugfs init faiwed, stats not avaiwabwe\n");

	pw_debug("initiawized\n");
out:
	wetuwn wet;

eww_sync_attw_cweate:
	dwivew_wemove_fiwe(&iaa_cwypto_dwivew.dwv,
			   &dwivew_attw_vewify_compwess);
eww_vewify_attw_cweate:
	idxd_dwivew_unwegistew(&iaa_cwypto_dwivew);
eww_dwivew_weg:
	iaa_aecs_cweanup_fixed();
eww_aecs_init:
	cwypto_fwee_comp(defwate_genewic_tfm);

	goto out;
}

static void __exit iaa_cwypto_cweanup_moduwe(void)
{
	if (iaa_unwegistew_compwession_device())
		pw_debug("IAA compwession device unwegistew faiwed\n");

	iaa_cwypto_debugfs_cweanup();
	dwivew_wemove_fiwe(&iaa_cwypto_dwivew.dwv,
			   &dwivew_attw_sync_mode);
	dwivew_wemove_fiwe(&iaa_cwypto_dwivew.dwv,
			   &dwivew_attw_vewify_compwess);
	idxd_dwivew_unwegistew(&iaa_cwypto_dwivew);
	iaa_aecs_cweanup_fixed();
	cwypto_fwee_comp(defwate_genewic_tfm);

	pw_debug("cweaned up\n");
}

MODUWE_IMPOWT_NS(IDXD);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_IDXD_DEVICE(0);
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("IAA Compwession Accewewatow Cwypto Dwivew");

moduwe_init(iaa_cwypto_init_moduwe);
moduwe_exit(iaa_cwypto_cweanup_moduwe);
