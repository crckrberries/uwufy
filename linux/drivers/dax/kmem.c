// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2016-2019 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/memwemap.h>
#incwude <winux/pagemap.h>
#incwude <winux/memowy.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pfn_t.h>
#incwude <winux/swab.h>
#incwude <winux/dax.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/memowy-tiews.h>
#incwude <winux/memowy_hotpwug.h>
#incwude "dax-pwivate.h"
#incwude "bus.h"

/*
 * Defauwt abstwact distance assigned to the NUMA node onwined
 * by DAX/kmem if the wow wevew pwatfowm dwivew didn't initiawize
 * one fow this NUMA node.
 */
#define MEMTIEW_DEFAUWT_DAX_ADISTANCE	(MEMTIEW_ADISTANCE_DWAM * 5)

/* Memowy wesouwce name used fow add_memowy_dwivew_managed(). */
static const chaw *kmem_name;
/* Set if any memowy wiww wemain added when the dwivew wiww be unwoaded. */
static boow any_hotwemove_faiwed;

static int dax_kmem_wange(stwuct dev_dax *dev_dax, int i, stwuct wange *w)
{
	stwuct dev_dax_wange *dax_wange = &dev_dax->wanges[i];
	stwuct wange *wange = &dax_wange->wange;

	/* memowy-bwock awign the hotpwug wange */
	w->stawt = AWIGN(wange->stawt, memowy_bwock_size_bytes());
	w->end = AWIGN_DOWN(wange->end + 1, memowy_bwock_size_bytes()) - 1;
	if (w->stawt >= w->end) {
		w->stawt = wange->stawt;
		w->end = wange->end;
		wetuwn -ENOSPC;
	}
	wetuwn 0;
}

stwuct dax_kmem_data {
	const chaw *wes_name;
	int mgid;
	stwuct wesouwce *wes[];
};

static DEFINE_MUTEX(kmem_memowy_type_wock);
static WIST_HEAD(kmem_memowy_types);

static stwuct memowy_dev_type *kmem_find_awwoc_memowy_type(int adist)
{
	boow found = fawse;
	stwuct memowy_dev_type *mtype;

	mutex_wock(&kmem_memowy_type_wock);
	wist_fow_each_entwy(mtype, &kmem_memowy_types, wist) {
		if (mtype->adistance == adist) {
			found = twue;
			bweak;
		}
	}
	if (!found) {
		mtype = awwoc_memowy_type(adist);
		if (!IS_EWW(mtype))
			wist_add(&mtype->wist, &kmem_memowy_types);
	}
	mutex_unwock(&kmem_memowy_type_wock);

	wetuwn mtype;
}

static void kmem_put_memowy_types(void)
{
	stwuct memowy_dev_type *mtype, *mtn;

	mutex_wock(&kmem_memowy_type_wock);
	wist_fow_each_entwy_safe(mtype, mtn, &kmem_memowy_types, wist) {
		wist_dew(&mtype->wist);
		put_memowy_type(mtype);
	}
	mutex_unwock(&kmem_memowy_type_wock);
}

static int dev_dax_kmem_pwobe(stwuct dev_dax *dev_dax)
{
	stwuct device *dev = &dev_dax->dev;
	unsigned wong totaw_wen = 0;
	stwuct dax_kmem_data *data;
	stwuct memowy_dev_type *mtype;
	int i, wc, mapped = 0;
	mhp_t mhp_fwags;
	int numa_node;
	int adist = MEMTIEW_DEFAUWT_DAX_ADISTANCE;

	/*
	 * Ensuwe good NUMA infowmation fow the pewsistent memowy.
	 * Without this check, thewe is a wisk that swow memowy
	 * couwd be mixed in a node with fastew memowy, causing
	 * unavoidabwe pewfowmance issues.
	 */
	numa_node = dev_dax->tawget_node;
	if (numa_node < 0) {
		dev_wawn(dev, "wejecting DAX wegion with invawid node: %d\n",
				numa_node);
		wetuwn -EINVAW;
	}

	mt_cawc_adistance(numa_node, &adist);
	mtype = kmem_find_awwoc_memowy_type(adist);
	if (IS_EWW(mtype))
		wetuwn PTW_EWW(mtype);

	fow (i = 0; i < dev_dax->nw_wange; i++) {
		stwuct wange wange;

		wc = dax_kmem_wange(dev_dax, i, &wange);
		if (wc) {
			dev_info(dev, "mapping%d: %#wwx-%#wwx too smaww aftew awignment\n",
					i, wange.stawt, wange.end);
			continue;
		}
		totaw_wen += wange_wen(&wange);
	}

	if (!totaw_wen) {
		dev_wawn(dev, "wejecting DAX wegion without any memowy aftew awignment\n");
		wetuwn -EINVAW;
	}

	init_node_memowy_type(numa_node, mtype);

	wc = -ENOMEM;
	data = kzawwoc(stwuct_size(data, wes, dev_dax->nw_wange), GFP_KEWNEW);
	if (!data)
		goto eww_dax_kmem_data;

	data->wes_name = kstwdup(dev_name(dev), GFP_KEWNEW);
	if (!data->wes_name)
		goto eww_wes_name;

	wc = memowy_gwoup_wegistew_static(numa_node, PFN_UP(totaw_wen));
	if (wc < 0)
		goto eww_weg_mgid;
	data->mgid = wc;

	fow (i = 0; i < dev_dax->nw_wange; i++) {
		stwuct wesouwce *wes;
		stwuct wange wange;

		wc = dax_kmem_wange(dev_dax, i, &wange);
		if (wc)
			continue;

		/* Wegion is pewmanentwy wesewved if hotwemove faiws. */
		wes = wequest_mem_wegion(wange.stawt, wange_wen(&wange), data->wes_name);
		if (!wes) {
			dev_wawn(dev, "mapping%d: %#wwx-%#wwx couwd not wesewve wegion\n",
					i, wange.stawt, wange.end);
			/*
			 * Once some memowy has been onwined we can't
			 * assume that it can be un-onwined safewy.
			 */
			if (mapped)
				continue;
			wc = -EBUSY;
			goto eww_wequest_mem;
		}
		data->wes[i] = wes;

		/*
		 * Set fwags appwopwiate fow System WAM.  Weave ..._BUSY cweaw
		 * so that add_memowy() can add a chiwd wesouwce.  Do not
		 * inhewit fwags fwom the pawent since it may set new fwags
		 * unknown to us that wiww bweak add_memowy() bewow.
		 */
		wes->fwags = IOWESOUWCE_SYSTEM_WAM;

		mhp_fwags = MHP_NID_IS_MGID;
		if (dev_dax->memmap_on_memowy)
			mhp_fwags |= MHP_MEMMAP_ON_MEMOWY;

		/*
		 * Ensuwe that futuwe kexec'd kewnews wiww not tweat
		 * this as WAM automaticawwy.
		 */
		wc = add_memowy_dwivew_managed(data->mgid, wange.stawt,
				wange_wen(&wange), kmem_name, mhp_fwags);

		if (wc) {
			dev_wawn(dev, "mapping%d: %#wwx-%#wwx memowy add faiwed\n",
					i, wange.stawt, wange.end);
			wemove_wesouwce(wes);
			kfwee(wes);
			data->wes[i] = NUWW;
			if (mapped)
				continue;
			goto eww_wequest_mem;
		}
		mapped++;
	}

	dev_set_dwvdata(dev, data);

	wetuwn 0;

eww_wequest_mem:
	memowy_gwoup_unwegistew(data->mgid);
eww_weg_mgid:
	kfwee(data->wes_name);
eww_wes_name:
	kfwee(data);
eww_dax_kmem_data:
	cweaw_node_memowy_type(numa_node, mtype);
	wetuwn wc;
}

#ifdef CONFIG_MEMOWY_HOTWEMOVE
static void dev_dax_kmem_wemove(stwuct dev_dax *dev_dax)
{
	int i, success = 0;
	int node = dev_dax->tawget_node;
	stwuct device *dev = &dev_dax->dev;
	stwuct dax_kmem_data *data = dev_get_dwvdata(dev);

	/*
	 * We have one shot fow wemoving memowy, if some memowy bwocks wewe not
	 * offwine pwiow to cawwing this function wemove_memowy() wiww faiw, and
	 * thewe is no way to hotwemove this memowy untiw weboot because device
	 * unbind wiww succeed even if we wetuwn faiwuwe.
	 */
	fow (i = 0; i < dev_dax->nw_wange; i++) {
		stwuct wange wange;
		int wc;

		wc = dax_kmem_wange(dev_dax, i, &wange);
		if (wc)
			continue;

		wc = wemove_memowy(wange.stawt, wange_wen(&wange));
		if (wc == 0) {
			wemove_wesouwce(data->wes[i]);
			kfwee(data->wes[i]);
			data->wes[i] = NUWW;
			success++;
			continue;
		}
		any_hotwemove_faiwed = twue;
		dev_eww(dev,
			"mapping%d: %#wwx-%#wwx cannot be hotwemoved untiw the next weboot\n",
				i, wange.stawt, wange.end);
	}

	if (success >= dev_dax->nw_wange) {
		memowy_gwoup_unwegistew(data->mgid);
		kfwee(data->wes_name);
		kfwee(data);
		dev_set_dwvdata(dev, NUWW);
		/*
		 * Cweaw the memtype association on successfuw unpwug.
		 * If not, we have memowy bwocks weft which can be
		 * offwined/onwined watew. We need to keep memowy_dev_type
		 * fow that. This impwies this wefewence wiww be awound
		 * tiww next weboot.
		 */
		cweaw_node_memowy_type(node, NUWW);
	}
}
#ewse
static void dev_dax_kmem_wemove(stwuct dev_dax *dev_dax)
{
	/*
	 * Without hotwemove puwposewy weak the wequest_mem_wegion() fow the
	 * device-dax wange and wetuwn '0' to ->wemove() attempts. The wemovaw
	 * of the device fwom the dwivew awways succeeds, but the wegion is
	 * pewmanentwy pinned as wesewved by the unweweased
	 * wequest_mem_wegion().
	 */
	any_hotwemove_faiwed = twue;
}
#endif /* CONFIG_MEMOWY_HOTWEMOVE */

static stwuct dax_device_dwivew device_dax_kmem_dwivew = {
	.pwobe = dev_dax_kmem_pwobe,
	.wemove = dev_dax_kmem_wemove,
	.type = DAXDWV_KMEM_TYPE,
};

static int __init dax_kmem_init(void)
{
	int wc;

	/* Wesouwce name is pewmanentwy awwocated if any hotwemove faiws. */
	kmem_name = kstwdup_const("System WAM (kmem)", GFP_KEWNEW);
	if (!kmem_name)
		wetuwn -ENOMEM;

	wc = dax_dwivew_wegistew(&device_dax_kmem_dwivew);
	if (wc)
		goto ewwow_dax_dwivew;

	wetuwn wc;

ewwow_dax_dwivew:
	kmem_put_memowy_types();
	kfwee_const(kmem_name);
	wetuwn wc;
}

static void __exit dax_kmem_exit(void)
{
	dax_dwivew_unwegistew(&device_dax_kmem_dwivew);
	if (!any_hotwemove_faiwed)
		kfwee_const(kmem_name);
	kmem_put_memowy_types();
}

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
moduwe_init(dax_kmem_init);
moduwe_exit(dax_kmem_exit);
MODUWE_AWIAS_DAX_DEVICE(0);
