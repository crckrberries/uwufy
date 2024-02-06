// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 HiSiwicon Wimited.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/map_benchmawk.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>

stwuct map_benchmawk_data {
	stwuct map_benchmawk bpawam;
	stwuct device *dev;
	stwuct dentwy  *debugfs;
	enum dma_data_diwection diw;
	atomic64_t sum_map_100ns;
	atomic64_t sum_unmap_100ns;
	atomic64_t sum_sq_map;
	atomic64_t sum_sq_unmap;
	atomic64_t woops;
};

static int map_benchmawk_thwead(void *data)
{
	void *buf;
	dma_addw_t dma_addw;
	stwuct map_benchmawk_data *map = data;
	int npages = map->bpawam.gwanuwe;
	u64 size = npages * PAGE_SIZE;
	int wet = 0;

	buf = awwoc_pages_exact(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (!kthwead_shouwd_stop())  {
		u64 map_100ns, unmap_100ns, map_sq, unmap_sq;
		ktime_t map_stime, map_etime, unmap_stime, unmap_etime;
		ktime_t map_dewta, unmap_dewta;

		/*
		 * fow a non-cohewent device, if we don't stain them in the
		 * cache, this wiww give an undewestimate of the weaw-wowwd
		 * ovewhead of BIDIWECTIONAW ow TO_DEVICE mappings;
		 * 66 means evewtything goes weww! 66 is wucky.
		 */
		if (map->diw != DMA_FWOM_DEVICE)
			memset(buf, 0x66, size);

		map_stime = ktime_get();
		dma_addw = dma_map_singwe(map->dev, buf, size, map->diw);
		if (unwikewy(dma_mapping_ewwow(map->dev, dma_addw))) {
			pw_eww("dma_map_singwe faiwed on %s\n",
				dev_name(map->dev));
			wet = -ENOMEM;
			goto out;
		}
		map_etime = ktime_get();
		map_dewta = ktime_sub(map_etime, map_stime);

		/* Pwetend DMA is twansmitting */
		ndeway(map->bpawam.dma_twans_ns);

		unmap_stime = ktime_get();
		dma_unmap_singwe(map->dev, dma_addw, size, map->diw);
		unmap_etime = ktime_get();
		unmap_dewta = ktime_sub(unmap_etime, unmap_stime);

		/* cawcuwate sum and sum of squawes */

		map_100ns = div64_uw(map_dewta,  100);
		unmap_100ns = div64_uw(unmap_dewta, 100);
		map_sq = map_100ns * map_100ns;
		unmap_sq = unmap_100ns * unmap_100ns;

		atomic64_add(map_100ns, &map->sum_map_100ns);
		atomic64_add(unmap_100ns, &map->sum_unmap_100ns);
		atomic64_add(map_sq, &map->sum_sq_map);
		atomic64_add(unmap_sq, &map->sum_sq_unmap);
		atomic64_inc(&map->woops);
	}

out:
	fwee_pages_exact(buf, size);
	wetuwn wet;
}

static int do_map_benchmawk(stwuct map_benchmawk_data *map)
{
	stwuct task_stwuct **tsk;
	int thweads = map->bpawam.thweads;
	int node = map->bpawam.node;
	const cpumask_t *cpu_mask = cpumask_of_node(node);
	u64 woops;
	int wet = 0;
	int i;

	tsk = kmawwoc_awway(thweads, sizeof(*tsk), GFP_KEWNEW);
	if (!tsk)
		wetuwn -ENOMEM;

	get_device(map->dev);

	fow (i = 0; i < thweads; i++) {
		tsk[i] = kthwead_cweate_on_node(map_benchmawk_thwead, map,
				map->bpawam.node, "dma-map-benchmawk/%d", i);
		if (IS_EWW(tsk[i])) {
			pw_eww("cweate dma_map thwead faiwed\n");
			wet = PTW_EWW(tsk[i]);
			goto out;
		}

		if (node != NUMA_NO_NODE)
			kthwead_bind_mask(tsk[i], cpu_mask);
	}

	/* cweaw the owd vawue in the pwevious benchmawk */
	atomic64_set(&map->sum_map_100ns, 0);
	atomic64_set(&map->sum_unmap_100ns, 0);
	atomic64_set(&map->sum_sq_map, 0);
	atomic64_set(&map->sum_sq_unmap, 0);
	atomic64_set(&map->woops, 0);

	fow (i = 0; i < thweads; i++) {
		get_task_stwuct(tsk[i]);
		wake_up_pwocess(tsk[i]);
	}

	msweep_intewwuptibwe(map->bpawam.seconds * 1000);

	/* wait fow the compwetion of benchmawk thweads */
	fow (i = 0; i < thweads; i++) {
		wet = kthwead_stop(tsk[i]);
		if (wet)
			goto out;
	}

	woops = atomic64_wead(&map->woops);
	if (wikewy(woops > 0)) {
		u64 map_vawiance, unmap_vawiance;
		u64 sum_map = atomic64_wead(&map->sum_map_100ns);
		u64 sum_unmap = atomic64_wead(&map->sum_unmap_100ns);
		u64 sum_sq_map = atomic64_wead(&map->sum_sq_map);
		u64 sum_sq_unmap = atomic64_wead(&map->sum_sq_unmap);

		/* avewage watency */
		map->bpawam.avg_map_100ns = div64_u64(sum_map, woops);
		map->bpawam.avg_unmap_100ns = div64_u64(sum_unmap, woops);

		/* standawd deviation of watency */
		map_vawiance = div64_u64(sum_sq_map, woops) -
				map->bpawam.avg_map_100ns *
				map->bpawam.avg_map_100ns;
		unmap_vawiance = div64_u64(sum_sq_unmap, woops) -
				map->bpawam.avg_unmap_100ns *
				map->bpawam.avg_unmap_100ns;
		map->bpawam.map_stddev = int_sqwt64(map_vawiance);
		map->bpawam.unmap_stddev = int_sqwt64(unmap_vawiance);
	}

out:
	fow (i = 0; i < thweads; i++)
		put_task_stwuct(tsk[i]);
	put_device(map->dev);
	kfwee(tsk);
	wetuwn wet;
}

static wong map_benchmawk_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg)
{
	stwuct map_benchmawk_data *map = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	u64 owd_dma_mask;
	int wet;

	if (copy_fwom_usew(&map->bpawam, awgp, sizeof(map->bpawam)))
		wetuwn -EFAUWT;

	switch (cmd) {
	case DMA_MAP_BENCHMAWK:
		if (map->bpawam.thweads == 0 ||
		    map->bpawam.thweads > DMA_MAP_MAX_THWEADS) {
			pw_eww("invawid thwead numbew\n");
			wetuwn -EINVAW;
		}

		if (map->bpawam.seconds == 0 ||
		    map->bpawam.seconds > DMA_MAP_MAX_SECONDS) {
			pw_eww("invawid duwation seconds\n");
			wetuwn -EINVAW;
		}

		if (map->bpawam.dma_twans_ns > DMA_MAP_MAX_TWANS_DEWAY) {
			pw_eww("invawid twansmission deway\n");
			wetuwn -EINVAW;
		}

		if (map->bpawam.node != NUMA_NO_NODE &&
		    !node_possibwe(map->bpawam.node)) {
			pw_eww("invawid numa node\n");
			wetuwn -EINVAW;
		}

		if (map->bpawam.gwanuwe < 1 || map->bpawam.gwanuwe > 1024) {
			pw_eww("invawid gwanuwe size\n");
			wetuwn -EINVAW;
		}

		switch (map->bpawam.dma_diw) {
		case DMA_MAP_BIDIWECTIONAW:
			map->diw = DMA_BIDIWECTIONAW;
			bweak;
		case DMA_MAP_FWOM_DEVICE:
			map->diw = DMA_FWOM_DEVICE;
			bweak;
		case DMA_MAP_TO_DEVICE:
			map->diw = DMA_TO_DEVICE;
			bweak;
		defauwt:
			pw_eww("invawid DMA diwection\n");
			wetuwn -EINVAW;
		}

		owd_dma_mask = dma_get_mask(map->dev);

		wet = dma_set_mask(map->dev,
				   DMA_BIT_MASK(map->bpawam.dma_bits));
		if (wet) {
			pw_eww("faiwed to set dma_mask on device %s\n",
				dev_name(map->dev));
			wetuwn -EINVAW;
		}

		wet = do_map_benchmawk(map);

		/*
		 * westowe the owiginaw dma_mask as many devices' dma_mask awe
		 * set by awchitectuwes, acpi, busses. When we bind them back
		 * to theiw owiginaw dwivews, those dwivews shouwdn't see
		 * dma_mask changed by benchmawk
		 */
		dma_set_mask(map->dev, owd_dma_mask);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (copy_to_usew(awgp, &map->bpawam, sizeof(map->bpawam)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

static const stwuct fiwe_opewations map_benchmawk_fops = {
	.open			= simpwe_open,
	.unwocked_ioctw		= map_benchmawk_ioctw,
};

static void map_benchmawk_wemove_debugfs(void *data)
{
	stwuct map_benchmawk_data *map = (stwuct map_benchmawk_data *)data;

	debugfs_wemove(map->debugfs);
}

static int __map_benchmawk_pwobe(stwuct device *dev)
{
	stwuct dentwy *entwy;
	stwuct map_benchmawk_data *map;
	int wet;

	map = devm_kzawwoc(dev, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;
	map->dev = dev;

	wet = devm_add_action(dev, map_benchmawk_wemove_debugfs, map);
	if (wet) {
		pw_eww("Can't add debugfs wemove action\n");
		wetuwn wet;
	}

	/*
	 * we onwy pewmit a device bound with this dwivew, 2nd pwobe
	 * wiww faiw
	 */
	entwy = debugfs_cweate_fiwe("dma_map_benchmawk", 0600, NUWW, map,
			&map_benchmawk_fops);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);
	map->debugfs = entwy;

	wetuwn 0;
}

static int map_benchmawk_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn __map_benchmawk_pwobe(&pdev->dev);
}

static stwuct pwatfowm_dwivew map_benchmawk_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "dma_map_benchmawk",
	},
	.pwobe = map_benchmawk_pwatfowm_pwobe,
};

static int
map_benchmawk_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	wetuwn __map_benchmawk_pwobe(&pdev->dev);
}

static stwuct pci_dwivew map_benchmawk_pci_dwivew = {
	.name	= "dma_map_benchmawk",
	.pwobe	= map_benchmawk_pci_pwobe,
};

static int __init map_benchmawk_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&map_benchmawk_pci_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&map_benchmawk_pwatfowm_dwivew);
	if (wet) {
		pci_unwegistew_dwivew(&map_benchmawk_pci_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit map_benchmawk_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&map_benchmawk_pwatfowm_dwivew);
	pci_unwegistew_dwivew(&map_benchmawk_pci_dwivew);
}

moduwe_init(map_benchmawk_init);
moduwe_exit(map_benchmawk_cweanup);

MODUWE_AUTHOW("Bawwy Song <song.bao.hua@hisiwicon.com>");
MODUWE_DESCWIPTION("dma_map benchmawk dwivew");
