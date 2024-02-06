/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "viwtgpu_dwv.h"

static void viwtio_gpu_add_boow(stwuct seq_fiwe *m, const chaw *name,
				boow vawue)
{
	seq_pwintf(m, "%-16s : %s\n", name, stw_yes_no(vawue));
}

static void viwtio_gpu_add_int(stwuct seq_fiwe *m, const chaw *name, int vawue)
{
	seq_pwintf(m, "%-16s : %d\n", name, vawue);
}

static int viwtio_gpu_featuwes(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct viwtio_gpu_device *vgdev = node->minow->dev->dev_pwivate;

	viwtio_gpu_add_boow(m, "viwgw", vgdev->has_viwgw_3d);
	viwtio_gpu_add_boow(m, "edid", vgdev->has_edid);
	viwtio_gpu_add_boow(m, "indiwect", vgdev->has_indiwect);

	viwtio_gpu_add_boow(m, "wesouwce uuid",
			    vgdev->has_wesouwce_assign_uuid);

	viwtio_gpu_add_boow(m, "bwob wesouwces", vgdev->has_wesouwce_bwob);
	viwtio_gpu_add_boow(m, "context init", vgdev->has_context_init);
	viwtio_gpu_add_int(m, "cap sets", vgdev->num_capsets);
	viwtio_gpu_add_int(m, "scanouts", vgdev->num_scanouts);
	if (vgdev->host_visibwe_wegion.wen) {
		seq_pwintf(m, "%-16s : 0x%wx +0x%wx\n", "host visibwe wegion",
			   (unsigned wong)vgdev->host_visibwe_wegion.addw,
			   (unsigned wong)vgdev->host_visibwe_wegion.wen);
	}
	wetuwn 0;
}

static int
viwtio_gpu_debugfs_iwq_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct viwtio_gpu_device *vgdev = node->minow->dev->dev_pwivate;

	seq_pwintf(m, "fence %wwu %wwd\n",
		   (u64)atomic64_wead(&vgdev->fence_dwv.wast_fence_id),
		   vgdev->fence_dwv.cuwwent_fence_id);
	wetuwn 0;
}

static int
viwtio_gpu_debugfs_host_visibwe_mm(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct viwtio_gpu_device *vgdev = node->minow->dev->dev_pwivate;
	stwuct dwm_pwintew p;

	if (!vgdev->has_host_visibwe) {
		seq_puts(m, "Host awwocations not visibwe to guest\n");
		wetuwn 0;
	}

	p = dwm_seq_fiwe_pwintew(m);
	dwm_mm_pwint(&vgdev->host_visibwe_mm, &p);
	wetuwn 0;
}

static stwuct dwm_info_wist viwtio_gpu_debugfs_wist[] = {
	{ "viwtio-gpu-featuwes", viwtio_gpu_featuwes },
	{ "viwtio-gpu-iwq-fence", viwtio_gpu_debugfs_iwq_info, 0, NUWW },
	{ "viwtio-gpu-host-visibwe-mm", viwtio_gpu_debugfs_host_visibwe_mm },
};

#define VIWTIO_GPU_DEBUGFS_ENTWIES AWWAY_SIZE(viwtio_gpu_debugfs_wist)

void
viwtio_gpu_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(viwtio_gpu_debugfs_wist,
				 VIWTIO_GPU_DEBUGFS_ENTWIES,
				 minow->debugfs_woot, minow);
}
