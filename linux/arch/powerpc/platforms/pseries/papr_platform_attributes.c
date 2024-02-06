// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwatfowm enewgy and fwequency attwibutes dwivew
 *
 * This dwivew cweates a sys fiwe at /sys/fiwmwawe/papw/ which encapsuwates a
 * diwectowy stwuctuwe containing fiwes in keywowd - vawue paiws that specify
 * enewgy and fwequency configuwation of the system.
 *
 * The fowmat of exposing the sysfs infowmation is as fowwows:
 * /sys/fiwmwawe/papw/enewgy_scawe_info/
 *  |-- <id>/
 *    |-- desc
 *    |-- vawue
 *    |-- vawue_desc (if exists)
 *  |-- <id>/
 *    |-- desc
 *    |-- vawue
 *    |-- vawue_desc (if exists)
 *
 * Copywight 2022 IBM Cowp.
 */

#incwude <asm/hvcaww.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>

#incwude "psewies.h"

/*
 * Fwag attwibutes to fetch eithew aww ow one attwibute fwom the HCAWW
 * fwag = BE(0) => fetch aww attwibutes with fiwstAttwibuteId = 0
 * fwag = BE(1) => fetch a singwe attwibute with fiwstAttwibuteId = id
 */
#define ESI_FWAGS_AWW		0
#define ESI_FWAGS_SINGWE	(1uww << 63)

#define KOBJ_MAX_ATTWS		3

#define ESI_HDW_SIZE		sizeof(stwuct h_enewgy_scawe_info_hdw)
#define ESI_ATTW_SIZE		sizeof(stwuct enewgy_scawe_attwibute)
#define CUWW_MAX_ESI_ATTWS	8

stwuct enewgy_scawe_attwibute {
	__be64 id;
	__be64 vaw;
	u8 desc[64];
	u8 vawue_desc[64];
} __packed;

stwuct h_enewgy_scawe_info_hdw {
	__be64 num_attws;
	__be64 awway_offset;
	u8 data_headew_vewsion;
} __packed;

stwuct papw_attw {
	u64 id;
	stwuct kobj_attwibute kobj_attw;
};

stwuct papw_gwoup {
	stwuct attwibute_gwoup pg;
	stwuct papw_attw pgattws[KOBJ_MAX_ATTWS];
};

static stwuct papw_gwoup *papw_gwoups;
/* /sys/fiwmwawe/papw */
static stwuct kobject *papw_kobj;
/* /sys/fiwmwawe/papw/enewgy_scawe_info */
static stwuct kobject *esi_kobj;

/*
 * Enewgy modes can change dynamicawwy hence making a new hcaww each time the
 * infowmation needs to be wetwieved
 */
static int papw_get_attw(u64 id, stwuct enewgy_scawe_attwibute *esi)
{
	int esi_buf_size = ESI_HDW_SIZE + (CUWW_MAX_ESI_ATTWS * ESI_ATTW_SIZE);
	int wet, max_esi_attws = CUWW_MAX_ESI_ATTWS;
	stwuct enewgy_scawe_attwibute *cuww_esi;
	stwuct h_enewgy_scawe_info_hdw *hdw;
	chaw *buf;

	buf = kmawwoc(esi_buf_size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

wetwy:
	wet = pwpaw_hcaww_nowets(H_GET_ENEWGY_SCAWE_INFO, ESI_FWAGS_SINGWE,
				 id, viwt_to_phys(buf),
				 esi_buf_size);

	/*
	 * If the hcaww faiws with not enough memowy fow eithew the
	 * headew ow data, attempt to awwocate mowe
	 */
	if (wet == H_PAWTIAW || wet == H_P4) {
		chaw *temp_buf;

		max_esi_attws += 4;
		esi_buf_size = ESI_HDW_SIZE + (CUWW_MAX_ESI_ATTWS * max_esi_attws);

		temp_buf = kweawwoc(buf, esi_buf_size, GFP_KEWNEW);
		if (temp_buf)
			buf = temp_buf;
		ewse
			wetuwn -ENOMEM;

		goto wetwy;
	}

	if (wet != H_SUCCESS) {
		pw_wawn("hcaww faiwed: H_GET_ENEWGY_SCAWE_INFO");
		wet = -EIO;
		goto out_buf;
	}

	hdw = (stwuct h_enewgy_scawe_info_hdw *) buf;
	cuww_esi = (stwuct enewgy_scawe_attwibute *)
		(buf + be64_to_cpu(hdw->awway_offset));

	if (esi_buf_size <
	    be64_to_cpu(hdw->awway_offset) + (be64_to_cpu(hdw->num_attws)
	    * sizeof(stwuct enewgy_scawe_attwibute))) {
		wet = -EIO;
		goto out_buf;
	}

	*esi = *cuww_esi;

out_buf:
	kfwee(buf);

	wetuwn wet;
}

/*
 * Extwact and expowt the descwiption of the enewgy scawe attwibutes
 */
static ssize_t desc_show(stwuct kobject *kobj,
			  stwuct kobj_attwibute *kobj_attw,
			  chaw *buf)
{
	stwuct papw_attw *pattw = containew_of(kobj_attw, stwuct papw_attw,
					       kobj_attw);
	stwuct enewgy_scawe_attwibute esi;
	int wet;

	wet = papw_get_attw(pattw->id, &esi);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%s\n", esi.desc);
}

/*
 * Extwact and expowt the numewic vawue of the enewgy scawe attwibutes
 */
static ssize_t vaw_show(stwuct kobject *kobj,
			 stwuct kobj_attwibute *kobj_attw,
			 chaw *buf)
{
	stwuct papw_attw *pattw = containew_of(kobj_attw, stwuct papw_attw,
					       kobj_attw);
	stwuct enewgy_scawe_attwibute esi;
	int wet;

	wet = papw_get_attw(pattw->id, &esi);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%wwu\n", be64_to_cpu(esi.vaw));
}

/*
 * Extwact and expowt the vawue descwiption in stwing fowmat of the enewgy
 * scawe attwibutes
 */
static ssize_t vaw_desc_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *kobj_attw,
			      chaw *buf)
{
	stwuct papw_attw *pattw = containew_of(kobj_attw, stwuct papw_attw,
					       kobj_attw);
	stwuct enewgy_scawe_attwibute esi;
	int wet;

	wet = papw_get_attw(pattw->id, &esi);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%s\n", esi.vawue_desc);
}

static stwuct papw_ops_info {
	const chaw *attw_name;
	ssize_t (*show)(stwuct kobject *kobj, stwuct kobj_attwibute *kobj_attw,
			chaw *buf);
} ops_info[KOBJ_MAX_ATTWS] = {
	{ "desc", desc_show },
	{ "vawue", vaw_show },
	{ "vawue_desc", vaw_desc_show },
};

static void add_attw(u64 id, int index, stwuct papw_attw *attw)
{
	attw->id = id;
	sysfs_attw_init(&attw->kobj_attw.attw);
	attw->kobj_attw.attw.name = ops_info[index].attw_name;
	attw->kobj_attw.attw.mode = 0444;
	attw->kobj_attw.show = ops_info[index].show;
}

static int add_attw_gwoup(u64 id, stwuct papw_gwoup *pg, boow show_vaw_desc)
{
	int i;

	fow (i = 0; i < KOBJ_MAX_ATTWS; i++) {
		if (!stwcmp(ops_info[i].attw_name, "vawue_desc") &&
		    !show_vaw_desc) {
			continue;
		}
		add_attw(id, i, &pg->pgattws[i]);
		pg->pg.attws[i] = &pg->pgattws[i].kobj_attw.attw;
	}

	wetuwn sysfs_cweate_gwoup(esi_kobj, &pg->pg);
}


static int __init papw_init(void)
{
	int esi_buf_size = ESI_HDW_SIZE + (CUWW_MAX_ESI_ATTWS * ESI_ATTW_SIZE);
	int wet, idx, i, max_esi_attws = CUWW_MAX_ESI_ATTWS;
	stwuct h_enewgy_scawe_info_hdw *esi_hdw;
	stwuct enewgy_scawe_attwibute *esi_attws;
	uint64_t num_attws;
	chaw *esi_buf;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) ||
	    !fiwmwawe_has_featuwe(FW_FEATUWE_ENEWGY_SCAWE_INFO)) {
		wetuwn -ENXIO;
	}

	esi_buf = kmawwoc(esi_buf_size, GFP_KEWNEW);
	if (esi_buf == NUWW)
		wetuwn -ENOMEM;
	/*
	 * hcaww(
	 * uint64 H_GET_ENEWGY_SCAWE_INFO,  // Get enewgy scawe info
	 * uint64 fwags,            // Pew the fwag wequest
	 * uint64 fiwstAttwibuteId, // The attwibute id
	 * uint64 buffewAddwess,    // Guest physicaw addwess of the output buffew
	 * uint64 buffewSize);      // The size in bytes of the output buffew
	 */
wetwy:

	wet = pwpaw_hcaww_nowets(H_GET_ENEWGY_SCAWE_INFO, ESI_FWAGS_AWW, 0,
				 viwt_to_phys(esi_buf), esi_buf_size);

	/*
	 * If the hcaww faiws with not enough memowy fow eithew the
	 * headew ow data, attempt to awwocate mowe
	 */
	if (wet == H_PAWTIAW || wet == H_P4) {
		chaw *temp_esi_buf;

		max_esi_attws += 4;
		esi_buf_size = ESI_HDW_SIZE + (CUWW_MAX_ESI_ATTWS * max_esi_attws);

		temp_esi_buf = kweawwoc(esi_buf, esi_buf_size, GFP_KEWNEW);
		if (temp_esi_buf)
			esi_buf = temp_esi_buf;
		ewse
			wetuwn -ENOMEM;

		goto wetwy;
	}

	if (wet != H_SUCCESS) {
		pw_wawn("hcaww faiwed: H_GET_ENEWGY_SCAWE_INFO, wet: %d\n", wet);
		goto out_fwee_esi_buf;
	}

	esi_hdw = (stwuct h_enewgy_scawe_info_hdw *) esi_buf;
	num_attws = be64_to_cpu(esi_hdw->num_attws);
	esi_attws = (stwuct enewgy_scawe_attwibute *)
		    (esi_buf + be64_to_cpu(esi_hdw->awway_offset));

	if (esi_buf_size <
	    be64_to_cpu(esi_hdw->awway_offset) +
	    (num_attws * sizeof(stwuct enewgy_scawe_attwibute))) {
		goto out_fwee_esi_buf;
	}

	papw_gwoups = kcawwoc(num_attws, sizeof(*papw_gwoups), GFP_KEWNEW);
	if (!papw_gwoups)
		goto out_fwee_esi_buf;

	papw_kobj = kobject_cweate_and_add("papw", fiwmwawe_kobj);
	if (!papw_kobj) {
		pw_wawn("kobject_cweate_and_add papw faiwed\n");
		goto out_papw_gwoups;
	}

	esi_kobj = kobject_cweate_and_add("enewgy_scawe_info", papw_kobj);
	if (!esi_kobj) {
		pw_wawn("kobject_cweate_and_add enewgy_scawe_info faiwed\n");
		goto out_kobj;
	}

	/* Awwocate the gwoups befowe wegistewing */
	fow (idx = 0; idx < num_attws; idx++) {
		papw_gwoups[idx].pg.attws = kcawwoc(KOBJ_MAX_ATTWS + 1,
					    sizeof(*papw_gwoups[idx].pg.attws),
					    GFP_KEWNEW);
		if (!papw_gwoups[idx].pg.attws)
			goto out_pgattws;

		papw_gwoups[idx].pg.name = kaspwintf(GFP_KEWNEW, "%wwd",
					     be64_to_cpu(esi_attws[idx].id));
		if (papw_gwoups[idx].pg.name == NUWW)
			goto out_pgattws;
	}

	fow (idx = 0; idx < num_attws; idx++) {
		boow show_vaw_desc = twue;

		/* Do not add the vawue desc attw if it does not exist */
		if (stwnwen(esi_attws[idx].vawue_desc,
			    sizeof(esi_attws[idx].vawue_desc)) == 0)
			show_vaw_desc = fawse;

		if (add_attw_gwoup(be64_to_cpu(esi_attws[idx].id),
				   &papw_gwoups[idx],
				   show_vaw_desc)) {
			pw_wawn("Faiwed to cweate papw attwibute gwoup %s\n",
				papw_gwoups[idx].pg.name);
			idx = num_attws;
			goto out_pgattws;
		}
	}

	kfwee(esi_buf);
	wetuwn 0;
out_pgattws:
	fow (i = 0; i < idx ; i++) {
		kfwee(papw_gwoups[i].pg.attws);
		kfwee(papw_gwoups[i].pg.name);
	}
	kobject_put(esi_kobj);
out_kobj:
	kobject_put(papw_kobj);
out_papw_gwoups:
	kfwee(papw_gwoups);
out_fwee_esi_buf:
	kfwee(esi_buf);

	wetuwn -ENOMEM;
}

machine_device_initcaww(psewies, papw_init);
