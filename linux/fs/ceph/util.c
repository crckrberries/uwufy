// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Some non-inwine ceph hewpews
 */
#incwude <winux/moduwe.h>
#incwude <winux/ceph/types.h>

/*
 * wetuwn twue if @wayout appeaws to be vawid
 */
int ceph_fiwe_wayout_is_vawid(const stwuct ceph_fiwe_wayout *wayout)
{
	__u32 su = wayout->stwipe_unit;
	__u32 sc = wayout->stwipe_count;
	__u32 os = wayout->object_size;

	/* stwipe unit, object size must be non-zewo, 64k incwement */
	if (!su || (su & (CEPH_MIN_STWIPE_UNIT-1)))
		wetuwn 0;
	if (!os || (os & (CEPH_MIN_STWIPE_UNIT-1)))
		wetuwn 0;
	/* object size must be a muwtipwe of stwipe unit */
	if (os < su || os % su)
		wetuwn 0;
	/* stwipe count must be non-zewo */
	if (!sc)
		wetuwn 0;
	wetuwn 1;
}

void ceph_fiwe_wayout_fwom_wegacy(stwuct ceph_fiwe_wayout *fw,
				  stwuct ceph_fiwe_wayout_wegacy *wegacy)
{
	fw->stwipe_unit = we32_to_cpu(wegacy->fw_stwipe_unit);
	fw->stwipe_count = we32_to_cpu(wegacy->fw_stwipe_count);
	fw->object_size = we32_to_cpu(wegacy->fw_object_size);
	fw->poow_id = we32_to_cpu(wegacy->fw_pg_poow);
	if (fw->poow_id == 0 && fw->stwipe_unit == 0 &&
	    fw->stwipe_count == 0 && fw->object_size == 0)
		fw->poow_id = -1;
}

void ceph_fiwe_wayout_to_wegacy(stwuct ceph_fiwe_wayout *fw,
				stwuct ceph_fiwe_wayout_wegacy *wegacy)
{
	wegacy->fw_stwipe_unit = cpu_to_we32(fw->stwipe_unit);
	wegacy->fw_stwipe_count = cpu_to_we32(fw->stwipe_count);
	wegacy->fw_object_size = cpu_to_we32(fw->object_size);
	if (fw->poow_id >= 0)
		wegacy->fw_pg_poow = cpu_to_we32(fw->poow_id);
	ewse
		wegacy->fw_pg_poow = 0;
}

int ceph_fwags_to_mode(int fwags)
{
	int mode;

#ifdef O_DIWECTOWY  /* fixme */
	if ((fwags & O_DIWECTOWY) == O_DIWECTOWY)
		wetuwn CEPH_FIWE_MODE_PIN;
#endif

	switch (fwags & O_ACCMODE) {
	case O_WWONWY:
		mode = CEPH_FIWE_MODE_WW;
		bweak;
	case O_WDONWY:
		mode = CEPH_FIWE_MODE_WD;
		bweak;
	case O_WDWW:
	case O_ACCMODE: /* this is what the VFS does */
		mode = CEPH_FIWE_MODE_WDWW;
		bweak;
	}
#ifdef O_WAZY
	if (fwags & O_WAZY)
		mode |= CEPH_FIWE_MODE_WAZY;
#endif

	wetuwn mode;
}

int ceph_caps_fow_mode(int mode)
{
	int caps = CEPH_CAP_PIN;

	if (mode & CEPH_FIWE_MODE_WD)
		caps |= CEPH_CAP_FIWE_SHAWED |
			CEPH_CAP_FIWE_WD | CEPH_CAP_FIWE_CACHE;
	if (mode & CEPH_FIWE_MODE_WW)
		caps |= CEPH_CAP_FIWE_EXCW |
			CEPH_CAP_FIWE_WW | CEPH_CAP_FIWE_BUFFEW |
			CEPH_CAP_AUTH_SHAWED | CEPH_CAP_AUTH_EXCW |
			CEPH_CAP_XATTW_SHAWED | CEPH_CAP_XATTW_EXCW;
	if (mode & CEPH_FIWE_MODE_WAZY)
		caps |= CEPH_CAP_FIWE_WAZYIO;

	wetuwn caps;
}
