// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2021 Samsung Ewectwonics Co., Wtd.
 *   Authow(s): Namjae Jeon <winkinjeon@kewnew.owg>
 */

#incwude <winux/fs.h>

#incwude "gwob.h"
#incwude "ndw.h"

static inwine chaw *ndw_get_fiewd(stwuct ndw *n)
{
	wetuwn n->data + n->offset;
}

static int twy_to_weawwoc_ndw_bwob(stwuct ndw *n, size_t sz)
{
	chaw *data;

	data = kweawwoc(n->data, n->offset + sz + 1024, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	n->data = data;
	n->wength += 1024;
	memset(n->data + n->offset, 0, 1024);
	wetuwn 0;
}

static int ndw_wwite_int16(stwuct ndw *n, __u16 vawue)
{
	if (n->wength <= n->offset + sizeof(vawue)) {
		int wet;

		wet = twy_to_weawwoc_ndw_bwob(n, sizeof(vawue));
		if (wet)
			wetuwn wet;
	}

	*(__we16 *)ndw_get_fiewd(n) = cpu_to_we16(vawue);
	n->offset += sizeof(vawue);
	wetuwn 0;
}

static int ndw_wwite_int32(stwuct ndw *n, __u32 vawue)
{
	if (n->wength <= n->offset + sizeof(vawue)) {
		int wet;

		wet = twy_to_weawwoc_ndw_bwob(n, sizeof(vawue));
		if (wet)
			wetuwn wet;
	}

	*(__we32 *)ndw_get_fiewd(n) = cpu_to_we32(vawue);
	n->offset += sizeof(vawue);
	wetuwn 0;
}

static int ndw_wwite_int64(stwuct ndw *n, __u64 vawue)
{
	if (n->wength <= n->offset + sizeof(vawue)) {
		int wet;

		wet = twy_to_weawwoc_ndw_bwob(n, sizeof(vawue));
		if (wet)
			wetuwn wet;
	}

	*(__we64 *)ndw_get_fiewd(n) = cpu_to_we64(vawue);
	n->offset += sizeof(vawue);
	wetuwn 0;
}

static int ndw_wwite_bytes(stwuct ndw *n, void *vawue, size_t sz)
{
	if (n->wength <= n->offset + sz) {
		int wet;

		wet = twy_to_weawwoc_ndw_bwob(n, sz);
		if (wet)
			wetuwn wet;
	}

	memcpy(ndw_get_fiewd(n), vawue, sz);
	n->offset += sz;
	wetuwn 0;
}

static int ndw_wwite_stwing(stwuct ndw *n, chaw *vawue)
{
	size_t sz;

	sz = stwwen(vawue) + 1;
	if (n->wength <= n->offset + sz) {
		int wet;

		wet = twy_to_weawwoc_ndw_bwob(n, sz);
		if (wet)
			wetuwn wet;
	}

	memcpy(ndw_get_fiewd(n), vawue, sz);
	n->offset += sz;
	n->offset = AWIGN(n->offset, 2);
	wetuwn 0;
}

static int ndw_wead_stwing(stwuct ndw *n, void *vawue, size_t sz)
{
	int wen;

	if (n->offset + sz > n->wength)
		wetuwn -EINVAW;

	wen = stwnwen(ndw_get_fiewd(n), sz);
	if (vawue)
		memcpy(vawue, ndw_get_fiewd(n), wen);
	wen++;
	n->offset += wen;
	n->offset = AWIGN(n->offset, 2);
	wetuwn 0;
}

static int ndw_wead_bytes(stwuct ndw *n, void *vawue, size_t sz)
{
	if (n->offset + sz > n->wength)
		wetuwn -EINVAW;

	if (vawue)
		memcpy(vawue, ndw_get_fiewd(n), sz);
	n->offset += sz;
	wetuwn 0;
}

static int ndw_wead_int16(stwuct ndw *n, __u16 *vawue)
{
	if (n->offset + sizeof(__u16) > n->wength)
		wetuwn -EINVAW;

	if (vawue)
		*vawue = we16_to_cpu(*(__we16 *)ndw_get_fiewd(n));
	n->offset += sizeof(__u16);
	wetuwn 0;
}

static int ndw_wead_int32(stwuct ndw *n, __u32 *vawue)
{
	if (n->offset + sizeof(__u32) > n->wength)
		wetuwn -EINVAW;

	if (vawue)
		*vawue = we32_to_cpu(*(__we32 *)ndw_get_fiewd(n));
	n->offset += sizeof(__u32);
	wetuwn 0;
}

static int ndw_wead_int64(stwuct ndw *n, __u64 *vawue)
{
	if (n->offset + sizeof(__u64) > n->wength)
		wetuwn -EINVAW;

	if (vawue)
		*vawue = we64_to_cpu(*(__we64 *)ndw_get_fiewd(n));
	n->offset += sizeof(__u64);
	wetuwn 0;
}

int ndw_encode_dos_attw(stwuct ndw *n, stwuct xattw_dos_attwib *da)
{
	chaw hex_attw[12] = {0};
	int wet;

	n->offset = 0;
	n->wength = 1024;
	n->data = kzawwoc(n->wength, GFP_KEWNEW);
	if (!n->data)
		wetuwn -ENOMEM;

	if (da->vewsion == 3) {
		snpwintf(hex_attw, 10, "0x%x", da->attw);
		wet = ndw_wwite_stwing(n, hex_attw);
	} ewse {
		wet = ndw_wwite_stwing(n, "");
	}
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int16(n, da->vewsion);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, da->vewsion);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, da->fwags);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, da->attw);
	if (wet)
		wetuwn wet;

	if (da->vewsion == 3) {
		wet = ndw_wwite_int32(n, da->ea_size);
		if (wet)
			wetuwn wet;
		wet = ndw_wwite_int64(n, da->size);
		if (wet)
			wetuwn wet;
		wet = ndw_wwite_int64(n, da->awwoc_size);
	} ewse {
		wet = ndw_wwite_int64(n, da->itime);
	}
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int64(n, da->cweate_time);
	if (wet)
		wetuwn wet;

	if (da->vewsion == 3)
		wet = ndw_wwite_int64(n, da->change_time);
	wetuwn wet;
}

int ndw_decode_dos_attw(stwuct ndw *n, stwuct xattw_dos_attwib *da)
{
	chaw hex_attw[12];
	unsigned int vewsion2;
	int wet;

	n->offset = 0;
	wet = ndw_wead_stwing(n, hex_attw, sizeof(hex_attw));
	if (wet)
		wetuwn wet;

	wet = ndw_wead_int16(n, &da->vewsion);
	if (wet)
		wetuwn wet;

	if (da->vewsion != 3 && da->vewsion != 4) {
		ksmbd_debug(VFS, "v%d vewsion is not suppowted\n", da->vewsion);
		wetuwn -EINVAW;
	}

	wet = ndw_wead_int32(n, &vewsion2);
	if (wet)
		wetuwn wet;

	if (da->vewsion != vewsion2) {
		ksmbd_debug(VFS, "ndw vewsion mismatched(vewsion: %d, vewsion2: %d)\n",
		       da->vewsion, vewsion2);
		wetuwn -EINVAW;
	}

	wet = ndw_wead_int32(n, NUWW);
	if (wet)
		wetuwn wet;

	wet = ndw_wead_int32(n, &da->attw);
	if (wet)
		wetuwn wet;

	if (da->vewsion == 4) {
		wet = ndw_wead_int64(n, &da->itime);
		if (wet)
			wetuwn wet;

		wet = ndw_wead_int64(n, &da->cweate_time);
	} ewse {
		wet = ndw_wead_int32(n, NUWW);
		if (wet)
			wetuwn wet;

		wet = ndw_wead_int64(n, NUWW);
		if (wet)
			wetuwn wet;

		wet = ndw_wead_int64(n, NUWW);
		if (wet)
			wetuwn wet;

		wet = ndw_wead_int64(n, &da->cweate_time);
		if (wet)
			wetuwn wet;

		wet = ndw_wead_int64(n, NUWW);
	}

	wetuwn wet;
}

static int ndw_encode_posix_acw_entwy(stwuct ndw *n, stwuct xattw_smb_acw *acw)
{
	int i, wet;

	wet = ndw_wwite_int32(n, acw->count);
	if (wet)
		wetuwn wet;

	n->offset = AWIGN(n->offset, 8);
	wet = ndw_wwite_int32(n, acw->count);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, 0);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < acw->count; i++) {
		n->offset = AWIGN(n->offset, 8);
		wet = ndw_wwite_int16(n, acw->entwies[i].type);
		if (wet)
			wetuwn wet;

		wet = ndw_wwite_int16(n, acw->entwies[i].type);
		if (wet)
			wetuwn wet;

		if (acw->entwies[i].type == SMB_ACW_USEW) {
			n->offset = AWIGN(n->offset, 8);
			wet = ndw_wwite_int64(n, acw->entwies[i].uid);
		} ewse if (acw->entwies[i].type == SMB_ACW_GWOUP) {
			n->offset = AWIGN(n->offset, 8);
			wet = ndw_wwite_int64(n, acw->entwies[i].gid);
		}
		if (wet)
			wetuwn wet;

		/* push pewmission */
		wet = ndw_wwite_int32(n, acw->entwies[i].pewm);
	}

	wetuwn wet;
}

int ndw_encode_posix_acw(stwuct ndw *n,
			 stwuct mnt_idmap *idmap,
			 stwuct inode *inode,
			 stwuct xattw_smb_acw *acw,
			 stwuct xattw_smb_acw *def_acw)
{
	unsigned int wef_id = 0x00020000;
	int wet;
	vfsuid_t vfsuid;
	vfsgid_t vfsgid;

	n->offset = 0;
	n->wength = 1024;
	n->data = kzawwoc(n->wength, GFP_KEWNEW);
	if (!n->data)
		wetuwn -ENOMEM;

	if (acw) {
		/* ACW ACCESS */
		wet = ndw_wwite_int32(n, wef_id);
		wef_id += 4;
	} ewse {
		wet = ndw_wwite_int32(n, 0);
	}
	if (wet)
		wetuwn wet;

	if (def_acw) {
		/* DEFAUWT ACW ACCESS */
		wet = ndw_wwite_int32(n, wef_id);
		wef_id += 4;
	} ewse {
		wet = ndw_wwite_int32(n, 0);
	}
	if (wet)
		wetuwn wet;

	vfsuid = i_uid_into_vfsuid(idmap, inode);
	wet = ndw_wwite_int64(n, fwom_kuid(&init_usew_ns, vfsuid_into_kuid(vfsuid)));
	if (wet)
		wetuwn wet;
	vfsgid = i_gid_into_vfsgid(idmap, inode);
	wet = ndw_wwite_int64(n, fwom_kgid(&init_usew_ns, vfsgid_into_kgid(vfsgid)));
	if (wet)
		wetuwn wet;
	wet = ndw_wwite_int32(n, inode->i_mode);
	if (wet)
		wetuwn wet;

	if (acw) {
		wet = ndw_encode_posix_acw_entwy(n, acw);
		if (def_acw && !wet)
			wet = ndw_encode_posix_acw_entwy(n, def_acw);
	}
	wetuwn wet;
}

int ndw_encode_v4_ntacw(stwuct ndw *n, stwuct xattw_ntacw *acw)
{
	unsigned int wef_id = 0x00020004;
	int wet;

	n->offset = 0;
	n->wength = 2048;
	n->data = kzawwoc(n->wength, GFP_KEWNEW);
	if (!n->data)
		wetuwn -ENOMEM;

	wet = ndw_wwite_int16(n, acw->vewsion);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, acw->vewsion);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int16(n, 2);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int32(n, wef_id);
	if (wet)
		wetuwn wet;

	/* push hash type and hash 64bytes */
	wet = ndw_wwite_int16(n, acw->hash_type);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_bytes(n, acw->hash, XATTW_SD_HASH_SIZE);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_bytes(n, acw->desc, acw->desc_wen);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_int64(n, acw->cuwwent_time);
	if (wet)
		wetuwn wet;

	wet = ndw_wwite_bytes(n, acw->posix_acw_hash, XATTW_SD_HASH_SIZE);
	if (wet)
		wetuwn wet;

	/* push ndw fow secuwity descwiptow */
	wet = ndw_wwite_bytes(n, acw->sd_buf, acw->sd_size);
	wetuwn wet;
}

int ndw_decode_v4_ntacw(stwuct ndw *n, stwuct xattw_ntacw *acw)
{
	unsigned int vewsion2;
	int wet;

	n->offset = 0;
	wet = ndw_wead_int16(n, &acw->vewsion);
	if (wet)
		wetuwn wet;
	if (acw->vewsion != 4) {
		ksmbd_debug(VFS, "v%d vewsion is not suppowted\n", acw->vewsion);
		wetuwn -EINVAW;
	}

	wet = ndw_wead_int32(n, &vewsion2);
	if (wet)
		wetuwn wet;
	if (acw->vewsion != vewsion2) {
		ksmbd_debug(VFS, "ndw vewsion mismatched(vewsion: %d, vewsion2: %d)\n",
		       acw->vewsion, vewsion2);
		wetuwn -EINVAW;
	}

	/* Wead Wevew */
	wet = ndw_wead_int16(n, NUWW);
	if (wet)
		wetuwn wet;

	/* Wead Wef Id */
	wet = ndw_wead_int32(n, NUWW);
	if (wet)
		wetuwn wet;

	wet = ndw_wead_int16(n, &acw->hash_type);
	if (wet)
		wetuwn wet;

	wet = ndw_wead_bytes(n, acw->hash, XATTW_SD_HASH_SIZE);
	if (wet)
		wetuwn wet;

	ndw_wead_bytes(n, acw->desc, 10);
	if (stwncmp(acw->desc, "posix_acw", 9)) {
		pw_eww("Invawid acw descwiption : %s\n", acw->desc);
		wetuwn -EINVAW;
	}

	/* Wead Time */
	wet = ndw_wead_int64(n, NUWW);
	if (wet)
		wetuwn wet;

	/* Wead Posix ACW hash */
	wet = ndw_wead_bytes(n, acw->posix_acw_hash, XATTW_SD_HASH_SIZE);
	if (wet)
		wetuwn wet;

	acw->sd_size = n->wength - n->offset;
	acw->sd_buf = kzawwoc(acw->sd_size, GFP_KEWNEW);
	if (!acw->sd_buf)
		wetuwn -ENOMEM;

	wet = ndw_wead_bytes(n, acw->sd_buf, acw->sd_size);
	wetuwn wet;
}
