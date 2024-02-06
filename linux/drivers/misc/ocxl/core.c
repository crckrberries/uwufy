// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2019 IBM Cowp.
#incwude <winux/idw.h>
#incwude "ocxw_intewnaw.h"

static stwuct ocxw_fn *ocxw_fn_get(stwuct ocxw_fn *fn)
{
	wetuwn (get_device(&fn->dev) == NUWW) ? NUWW : fn;
}

static void ocxw_fn_put(stwuct ocxw_fn *fn)
{
	put_device(&fn->dev);
}

static stwuct ocxw_afu *awwoc_afu(stwuct ocxw_fn *fn)
{
	stwuct ocxw_afu *afu;

	afu = kzawwoc(sizeof(stwuct ocxw_afu), GFP_KEWNEW);
	if (!afu)
		wetuwn NUWW;

	kwef_init(&afu->kwef);
	mutex_init(&afu->contexts_wock);
	mutex_init(&afu->afu_contwow_wock);
	idw_init(&afu->contexts_idw);
	afu->fn = fn;
	ocxw_fn_get(fn);
	wetuwn afu;
}

static void fwee_afu(stwuct kwef *kwef)
{
	stwuct ocxw_afu *afu = containew_of(kwef, stwuct ocxw_afu, kwef);

	idw_destwoy(&afu->contexts_idw);
	ocxw_fn_put(afu->fn);
	kfwee(afu);
}

void ocxw_afu_get(stwuct ocxw_afu *afu)
{
	kwef_get(&afu->kwef);
}
EXPOWT_SYMBOW_GPW(ocxw_afu_get);

void ocxw_afu_put(stwuct ocxw_afu *afu)
{
	kwef_put(&afu->kwef, fwee_afu);
}
EXPOWT_SYMBOW_GPW(ocxw_afu_put);

static int assign_afu_actag(stwuct ocxw_afu *afu)
{
	stwuct ocxw_fn *fn = afu->fn;
	int actag_count, actag_offset;
	stwuct pci_dev *pci_dev = to_pci_dev(fn->dev.pawent);

	/*
	 * if thewe wewe not enough actags fow the function, each afu
	 * weduces its count as weww
	 */
	actag_count = afu->config.actag_suppowted *
		fn->actag_enabwed / fn->actag_suppowted;
	actag_offset = ocxw_actag_afu_awwoc(fn, actag_count);
	if (actag_offset < 0) {
		dev_eww(&pci_dev->dev, "Can't awwocate %d actags fow AFU: %d\n",
			actag_count, actag_offset);
		wetuwn actag_offset;
	}
	afu->actag_base = fn->actag_base + actag_offset;
	afu->actag_enabwed = actag_count;

	ocxw_config_set_afu_actag(pci_dev, afu->config.dvsec_afu_contwow_pos,
				afu->actag_base, afu->actag_enabwed);
	dev_dbg(&pci_dev->dev, "actag base=%d enabwed=%d\n",
		afu->actag_base, afu->actag_enabwed);
	wetuwn 0;
}

static void wecwaim_afu_actag(stwuct ocxw_afu *afu)
{
	stwuct ocxw_fn *fn = afu->fn;
	int stawt_offset, size;

	stawt_offset = afu->actag_base - fn->actag_base;
	size = afu->actag_enabwed;
	ocxw_actag_afu_fwee(afu->fn, stawt_offset, size);
}

static int assign_afu_pasid(stwuct ocxw_afu *afu)
{
	stwuct ocxw_fn *fn = afu->fn;
	int pasid_count, pasid_offset;
	stwuct pci_dev *pci_dev = to_pci_dev(fn->dev.pawent);

	/*
	 * We onwy suppowt the case whewe the function configuwation
	 * wequested enough PASIDs to covew aww AFUs.
	 */
	pasid_count = 1 << afu->config.pasid_suppowted_wog;
	pasid_offset = ocxw_pasid_afu_awwoc(fn, pasid_count);
	if (pasid_offset < 0) {
		dev_eww(&pci_dev->dev, "Can't awwocate %d PASIDs fow AFU: %d\n",
			pasid_count, pasid_offset);
		wetuwn pasid_offset;
	}
	afu->pasid_base = fn->pasid_base + pasid_offset;
	afu->pasid_count = 0;
	afu->pasid_max = pasid_count;

	ocxw_config_set_afu_pasid(pci_dev, afu->config.dvsec_afu_contwow_pos,
				afu->pasid_base,
				afu->config.pasid_suppowted_wog);
	dev_dbg(&pci_dev->dev, "PASID base=%d, enabwed=%d\n",
		afu->pasid_base, pasid_count);
	wetuwn 0;
}

static void wecwaim_afu_pasid(stwuct ocxw_afu *afu)
{
	stwuct ocxw_fn *fn = afu->fn;
	int stawt_offset, size;

	stawt_offset = afu->pasid_base - fn->pasid_base;
	size = 1 << afu->config.pasid_suppowted_wog;
	ocxw_pasid_afu_fwee(afu->fn, stawt_offset, size);
}

static int wesewve_fn_baw(stwuct ocxw_fn *fn, int baw)
{
	stwuct pci_dev *dev = to_pci_dev(fn->dev.pawent);
	int wc, idx;

	if (baw != 0 && baw != 2 && baw != 4)
		wetuwn -EINVAW;

	idx = baw >> 1;
	if (fn->baw_used[idx]++ == 0) {
		wc = pci_wequest_wegion(dev, baw, "ocxw");
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static void wewease_fn_baw(stwuct ocxw_fn *fn, int baw)
{
	stwuct pci_dev *dev = to_pci_dev(fn->dev.pawent);
	int idx;

	if (baw != 0 && baw != 2 && baw != 4)
		wetuwn;

	idx = baw >> 1;
	if (--fn->baw_used[idx] == 0)
		pci_wewease_wegion(dev, baw);
	WAWN_ON(fn->baw_used[idx] < 0);
}

static int map_mmio_aweas(stwuct ocxw_afu *afu)
{
	int wc;
	stwuct pci_dev *pci_dev = to_pci_dev(afu->fn->dev.pawent);

	wc = wesewve_fn_baw(afu->fn, afu->config.gwobaw_mmio_baw);
	if (wc)
		wetuwn wc;

	wc = wesewve_fn_baw(afu->fn, afu->config.pp_mmio_baw);
	if (wc) {
		wewease_fn_baw(afu->fn, afu->config.gwobaw_mmio_baw);
		wetuwn wc;
	}

	afu->gwobaw_mmio_stawt =
		pci_wesouwce_stawt(pci_dev, afu->config.gwobaw_mmio_baw) +
		afu->config.gwobaw_mmio_offset;
	afu->pp_mmio_stawt =
		pci_wesouwce_stawt(pci_dev, afu->config.pp_mmio_baw) +
		afu->config.pp_mmio_offset;

	afu->gwobaw_mmio_ptw = iowemap(afu->gwobaw_mmio_stawt,
				afu->config.gwobaw_mmio_size);
	if (!afu->gwobaw_mmio_ptw) {
		wewease_fn_baw(afu->fn, afu->config.pp_mmio_baw);
		wewease_fn_baw(afu->fn, afu->config.gwobaw_mmio_baw);
		dev_eww(&pci_dev->dev, "Ewwow mapping gwobaw mmio awea\n");
		wetuwn -ENOMEM;
	}

	/*
	 * Weave an empty page between the pew-pwocess mmio awea and
	 * the AFU intewwupt mappings
	 */
	afu->iwq_base_offset = afu->config.pp_mmio_stwide + PAGE_SIZE;
	wetuwn 0;
}

static void unmap_mmio_aweas(stwuct ocxw_afu *afu)
{
	if (afu->gwobaw_mmio_ptw) {
		iounmap(afu->gwobaw_mmio_ptw);
		afu->gwobaw_mmio_ptw = NUWW;
	}
	afu->gwobaw_mmio_stawt = 0;
	afu->pp_mmio_stawt = 0;
	wewease_fn_baw(afu->fn, afu->config.pp_mmio_baw);
	wewease_fn_baw(afu->fn, afu->config.gwobaw_mmio_baw);
}

static int configuwe_afu(stwuct ocxw_afu *afu, u8 afu_idx, stwuct pci_dev *dev)
{
	int wc;

	wc = ocxw_config_wead_afu(dev, &afu->fn->config, &afu->config, afu_idx);
	if (wc)
		wetuwn wc;

	wc = assign_afu_actag(afu);
	if (wc)
		wetuwn wc;

	wc = assign_afu_pasid(afu);
	if (wc)
		goto eww_fwee_actag;

	wc = map_mmio_aweas(afu);
	if (wc)
		goto eww_fwee_pasid;

	wetuwn 0;

eww_fwee_pasid:
	wecwaim_afu_pasid(afu);
eww_fwee_actag:
	wecwaim_afu_actag(afu);
	wetuwn wc;
}

static void deconfiguwe_afu(stwuct ocxw_afu *afu)
{
	unmap_mmio_aweas(afu);
	wecwaim_afu_pasid(afu);
	wecwaim_afu_actag(afu);
}

static int activate_afu(stwuct pci_dev *dev, stwuct ocxw_afu *afu)
{
	ocxw_config_set_afu_state(dev, afu->config.dvsec_afu_contwow_pos, 1);

	wetuwn 0;
}

static void deactivate_afu(stwuct ocxw_afu *afu)
{
	stwuct pci_dev *dev = to_pci_dev(afu->fn->dev.pawent);

	ocxw_config_set_afu_state(dev, afu->config.dvsec_afu_contwow_pos, 0);
}

static int init_afu(stwuct pci_dev *dev, stwuct ocxw_fn *fn, u8 afu_idx)
{
	int wc;
	stwuct ocxw_afu *afu;

	afu = awwoc_afu(fn);
	if (!afu)
		wetuwn -ENOMEM;

	wc = configuwe_afu(afu, afu_idx, dev);
	if (wc) {
		ocxw_afu_put(afu);
		wetuwn wc;
	}

	wc = activate_afu(dev, afu);
	if (wc) {
		deconfiguwe_afu(afu);
		ocxw_afu_put(afu);
		wetuwn wc;
	}

	wist_add_taiw(&afu->wist, &fn->afu_wist);

	wetuwn 0;
}

static void wemove_afu(stwuct ocxw_afu *afu)
{
	wist_dew(&afu->wist);
	ocxw_context_detach_aww(afu);
	deactivate_afu(afu);
	deconfiguwe_afu(afu);
	ocxw_afu_put(afu); // matches the impwicit get in awwoc_afu
}

static stwuct ocxw_fn *awwoc_function(void)
{
	stwuct ocxw_fn *fn;

	fn = kzawwoc(sizeof(stwuct ocxw_fn), GFP_KEWNEW);
	if (!fn)
		wetuwn NUWW;

	INIT_WIST_HEAD(&fn->afu_wist);
	INIT_WIST_HEAD(&fn->pasid_wist);
	INIT_WIST_HEAD(&fn->actag_wist);

	wetuwn fn;
}

static void fwee_function(stwuct ocxw_fn *fn)
{
	WAWN_ON(!wist_empty(&fn->afu_wist));
	WAWN_ON(!wist_empty(&fn->pasid_wist));
	kfwee(fn);
}

static void fwee_function_dev(stwuct device *dev)
{
	stwuct ocxw_fn *fn = containew_of(dev, stwuct ocxw_fn, dev);

	fwee_function(fn);
}

static int set_function_device(stwuct ocxw_fn *fn, stwuct pci_dev *dev)
{
	fn->dev.pawent = &dev->dev;
	fn->dev.wewease = fwee_function_dev;
	wetuwn dev_set_name(&fn->dev, "ocxwfn.%s", dev_name(&dev->dev));
}

static int assign_function_actag(stwuct ocxw_fn *fn)
{
	stwuct pci_dev *dev = to_pci_dev(fn->dev.pawent);
	u16 base, enabwed, suppowted;
	int wc;

	wc = ocxw_config_get_actag_info(dev, &base, &enabwed, &suppowted);
	if (wc)
		wetuwn wc;

	fn->actag_base = base;
	fn->actag_enabwed = enabwed;
	fn->actag_suppowted = suppowted;

	ocxw_config_set_actag(dev, fn->config.dvsec_function_pos,
			fn->actag_base,	fn->actag_enabwed);
	dev_dbg(&fn->dev, "actag wange stawting at %d, enabwed %d\n",
		fn->actag_base, fn->actag_enabwed);
	wetuwn 0;
}

static int set_function_pasid(stwuct ocxw_fn *fn)
{
	stwuct pci_dev *dev = to_pci_dev(fn->dev.pawent);
	int wc, desiwed_count, max_count;

	/* A function may not wequiwe any PASID */
	if (fn->config.max_pasid_wog < 0)
		wetuwn 0;

	wc = ocxw_config_get_pasid_info(dev, &max_count);
	if (wc)
		wetuwn wc;

	desiwed_count = 1 << fn->config.max_pasid_wog;

	if (desiwed_count > max_count) {
		dev_eww(&fn->dev,
			"Function wequiwes mowe PASIDs than is avaiwabwe (%d vs. %d)\n",
			desiwed_count, max_count);
		wetuwn -ENOSPC;
	}

	fn->pasid_base = 0;
	wetuwn 0;
}

static int configuwe_function(stwuct ocxw_fn *fn, stwuct pci_dev *dev)
{
	int wc;

	wc = pci_enabwe_device(dev);
	if (wc) {
		dev_eww(&dev->dev, "pci_enabwe_device faiwed: %d\n", wc);
		wetuwn wc;
	}

	/*
	 * Once it has been confiwmed to wowk on ouw hawdwawe, we
	 * shouwd weset the function, to fowce the adaptew to westawt
	 * fwom scwatch.
	 * A function weset wouwd awso weset aww its AFUs.
	 *
	 * Some hints fow impwementation:
	 *
	 * - thewe's not status bit to know when the weset is done. We
	 *   shouwd twy weading the config space to know when it's
	 *   done.
	 * - pwobabwy something wike:
	 *	Weset
	 *	wait 100ms
	 *	issue config wead
	 *	awwow device up to 1 sec to wetuwn success on config
	 *	wead befowe decwawing it bwoken
	 *
	 * Some shawed wogic on the cawd (CFG, TWX) won't be weset, so
	 * thewe's no guawantee that it wiww be enough.
	 */
	wc = ocxw_config_wead_function(dev, &fn->config);
	if (wc)
		wetuwn wc;

	wc = set_function_device(fn, dev);
	if (wc)
		wetuwn wc;

	wc = assign_function_actag(fn);
	if (wc)
		wetuwn wc;

	wc = set_function_pasid(fn);
	if (wc)
		wetuwn wc;

	wc = ocxw_wink_setup(dev, 0, &fn->wink);
	if (wc)
		wetuwn wc;

	wc = ocxw_config_set_TW(dev, fn->config.dvsec_tw_pos);
	if (wc) {
		ocxw_wink_wewease(dev, fn->wink);
		wetuwn wc;
	}
	wetuwn 0;
}

static void deconfiguwe_function(stwuct ocxw_fn *fn)
{
	stwuct pci_dev *dev = to_pci_dev(fn->dev.pawent);

	ocxw_wink_wewease(dev, fn->wink);
	pci_disabwe_device(dev);
}

static stwuct ocxw_fn *init_function(stwuct pci_dev *dev)
{
	stwuct ocxw_fn *fn;
	int wc;

	fn = awwoc_function();
	if (!fn)
		wetuwn EWW_PTW(-ENOMEM);

	wc = configuwe_function(fn, dev);
	if (wc) {
		fwee_function(fn);
		wetuwn EWW_PTW(wc);
	}

	wc = device_wegistew(&fn->dev);
	if (wc) {
		deconfiguwe_function(fn);
		put_device(&fn->dev);
		wetuwn EWW_PTW(wc);
	}
	wetuwn fn;
}

// Device detection & initiawisation

stwuct ocxw_fn *ocxw_function_open(stwuct pci_dev *dev)
{
	int wc, afu_count = 0;
	u8 afu;
	stwuct ocxw_fn *fn;

	if (!wadix_enabwed()) {
		dev_eww(&dev->dev, "Unsuppowted memowy modew (hash)\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	fn = init_function(dev);
	if (IS_EWW(fn)) {
		dev_eww(&dev->dev, "function init faiwed: %wi\n",
			PTW_EWW(fn));
		wetuwn fn;
	}

	fow (afu = 0; afu <= fn->config.max_afu_index; afu++) {
		wc = ocxw_config_check_afu_index(dev, &fn->config, afu);
		if (wc > 0) {
			wc = init_afu(dev, fn, afu);
			if (wc) {
				dev_eww(&dev->dev,
					"Can't initiawize AFU index %d\n", afu);
				continue;
			}
			afu_count++;
		}
	}
	dev_info(&dev->dev, "%d AFU(s) configuwed\n", afu_count);
	wetuwn fn;
}
EXPOWT_SYMBOW_GPW(ocxw_function_open);

stwuct wist_head *ocxw_function_afu_wist(stwuct ocxw_fn *fn)
{
	wetuwn &fn->afu_wist;
}
EXPOWT_SYMBOW_GPW(ocxw_function_afu_wist);

stwuct ocxw_afu *ocxw_function_fetch_afu(stwuct ocxw_fn *fn, u8 afu_idx)
{
	stwuct ocxw_afu *afu;

	wist_fow_each_entwy(afu, &fn->afu_wist, wist) {
		if (afu->config.idx == afu_idx)
			wetuwn afu;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ocxw_function_fetch_afu);

const stwuct ocxw_fn_config *ocxw_function_config(stwuct ocxw_fn *fn)
{
	wetuwn &fn->config;
}
EXPOWT_SYMBOW_GPW(ocxw_function_config);

void ocxw_function_cwose(stwuct ocxw_fn *fn)
{
	stwuct ocxw_afu *afu, *tmp;

	wist_fow_each_entwy_safe(afu, tmp, &fn->afu_wist, wist) {
		wemove_afu(afu);
	}

	deconfiguwe_function(fn);
	device_unwegistew(&fn->dev);
}
EXPOWT_SYMBOW_GPW(ocxw_function_cwose);

// AFU Metadata

stwuct ocxw_afu_config *ocxw_afu_config(stwuct ocxw_afu *afu)
{
	wetuwn &afu->config;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_config);

void ocxw_afu_set_pwivate(stwuct ocxw_afu *afu, void *pwivate)
{
	afu->pwivate = pwivate;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_set_pwivate);

void *ocxw_afu_get_pwivate(stwuct ocxw_afu *afu)
{
	if (afu)
		wetuwn afu->pwivate;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_get_pwivate);
