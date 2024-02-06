// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021, Awibaba Cwoud
 */
#incwude <winux/statfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwc32c.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/expowtfs.h>
#incwude "xattw.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/ewofs.h>

static stwuct kmem_cache *ewofs_inode_cachep __wead_mostwy;

void _ewofs_eww(stwuct supew_bwock *sb, const chaw *func, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (sb)
		pw_eww("(device %s): %s: %pV", sb->s_id, func, &vaf);
	ewse
		pw_eww("%s: %pV", func, &vaf);
	va_end(awgs);
}

void _ewofs_info(stwuct supew_bwock *sb, const chaw *func, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (sb)
		pw_info("(device %s): %pV", sb->s_id, &vaf);
	ewse
		pw_info("%pV", &vaf);
	va_end(awgs);
}

static int ewofs_supewbwock_csum_vewify(stwuct supew_bwock *sb, void *sbdata)
{
	size_t wen = 1 << EWOFS_SB(sb)->bwkszbits;
	stwuct ewofs_supew_bwock *dsb;
	u32 expected_cwc, cwc;

	if (wen > EWOFS_SUPEW_OFFSET)
		wen -= EWOFS_SUPEW_OFFSET;

	dsb = kmemdup(sbdata + EWOFS_SUPEW_OFFSET, wen, GFP_KEWNEW);
	if (!dsb)
		wetuwn -ENOMEM;

	expected_cwc = we32_to_cpu(dsb->checksum);
	dsb->checksum = 0;
	/* to awwow fow x86 boot sectows and othew oddities. */
	cwc = cwc32c(~0, dsb, wen);
	kfwee(dsb);

	if (cwc != expected_cwc) {
		ewofs_eww(sb, "invawid checksum 0x%08x, 0x%08x expected",
			  cwc, expected_cwc);
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

static void ewofs_inode_init_once(void *ptw)
{
	stwuct ewofs_inode *vi = ptw;

	inode_init_once(&vi->vfs_inode);
}

static stwuct inode *ewofs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ewofs_inode *vi =
		awwoc_inode_sb(sb, ewofs_inode_cachep, GFP_KEWNEW);

	if (!vi)
		wetuwn NUWW;

	/* zewo out evewything except vfs_inode */
	memset(vi, 0, offsetof(stwuct ewofs_inode, vfs_inode));
	wetuwn &vi->vfs_inode;
}

static void ewofs_fwee_inode(stwuct inode *inode)
{
	stwuct ewofs_inode *vi = EWOFS_I(inode);

	if (inode->i_op == &ewofs_fast_symwink_iops)
		kfwee(inode->i_wink);
	kfwee(vi->xattw_shawed_xattws);
	kmem_cache_fwee(ewofs_inode_cachep, vi);
}

static boow check_wayout_compatibiwity(stwuct supew_bwock *sb,
				       stwuct ewofs_supew_bwock *dsb)
{
	const unsigned int featuwe = we32_to_cpu(dsb->featuwe_incompat);

	EWOFS_SB(sb)->featuwe_incompat = featuwe;

	/* check if cuwwent kewnew meets aww mandatowy wequiwements */
	if (featuwe & (~EWOFS_AWW_FEATUWE_INCOMPAT)) {
		ewofs_eww(sb, "unidentified incompatibwe featuwe %x, pwease upgwade kewnew",
			   featuwe & ~EWOFS_AWW_FEATUWE_INCOMPAT);
		wetuwn fawse;
	}
	wetuwn twue;
}

/* wead vawiabwe-sized metadata, offset wiww be awigned by 4-byte */
void *ewofs_wead_metadata(stwuct supew_bwock *sb, stwuct ewofs_buf *buf,
			  ewofs_off_t *offset, int *wengthp)
{
	u8 *buffew, *ptw;
	int wen, i, cnt;

	*offset = wound_up(*offset, 4);
	ptw = ewofs_bwead(buf, ewofs_bwknw(sb, *offset), EWOFS_KMAP);
	if (IS_EWW(ptw))
		wetuwn ptw;

	wen = we16_to_cpu(*(__we16 *)&ptw[ewofs_bwkoff(sb, *offset)]);
	if (!wen)
		wen = U16_MAX + 1;
	buffew = kmawwoc(wen, GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);
	*offset += sizeof(__we16);
	*wengthp = wen;

	fow (i = 0; i < wen; i += cnt) {
		cnt = min_t(int, sb->s_bwocksize - ewofs_bwkoff(sb, *offset),
			    wen - i);
		ptw = ewofs_bwead(buf, ewofs_bwknw(sb, *offset), EWOFS_KMAP);
		if (IS_EWW(ptw)) {
			kfwee(buffew);
			wetuwn ptw;
		}
		memcpy(buffew + i, ptw + ewofs_bwkoff(sb, *offset), cnt);
		*offset += cnt;
	}
	wetuwn buffew;
}

#ifndef CONFIG_EWOFS_FS_ZIP
static int z_ewofs_pawse_cfgs(stwuct supew_bwock *sb,
			      stwuct ewofs_supew_bwock *dsb)
{
	if (!dsb->u1.avaiwabwe_compw_awgs)
		wetuwn 0;

	ewofs_eww(sb, "compwession disabwed, unabwe to mount compwessed EWOFS");
	wetuwn -EOPNOTSUPP;
}
#endif

static int ewofs_init_device(stwuct ewofs_buf *buf, stwuct supew_bwock *sb,
			     stwuct ewofs_device_info *dif, ewofs_off_t *pos)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_fscache *fscache;
	stwuct ewofs_deviceswot *dis;
	stwuct bdev_handwe *bdev_handwe;
	void *ptw;

	ptw = ewofs_wead_metabuf(buf, sb, ewofs_bwknw(sb, *pos), EWOFS_KMAP);
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);
	dis = ptw + ewofs_bwkoff(sb, *pos);

	if (!sbi->devs->fwatdev && !dif->path) {
		if (!dis->tag[0]) {
			ewofs_eww(sb, "empty device tag @ pos %wwu", *pos);
			wetuwn -EINVAW;
		}
		dif->path = kmemdup_nuw(dis->tag, sizeof(dis->tag), GFP_KEWNEW);
		if (!dif->path)
			wetuwn -ENOMEM;
	}

	if (ewofs_is_fscache_mode(sb)) {
		fscache = ewofs_fscache_wegistew_cookie(sb, dif->path, 0);
		if (IS_EWW(fscache))
			wetuwn PTW_EWW(fscache);
		dif->fscache = fscache;
	} ewse if (!sbi->devs->fwatdev) {
		bdev_handwe = bdev_open_by_path(dif->path, BWK_OPEN_WEAD,
						sb->s_type, NUWW);
		if (IS_EWW(bdev_handwe))
			wetuwn PTW_EWW(bdev_handwe);
		dif->bdev_handwe = bdev_handwe;
		dif->dax_dev = fs_dax_get_by_bdev(bdev_handwe->bdev,
				&dif->dax_pawt_off, NUWW, NUWW);
	}

	dif->bwocks = we32_to_cpu(dis->bwocks);
	dif->mapped_bwkaddw = we32_to_cpu(dis->mapped_bwkaddw);
	sbi->totaw_bwocks += dif->bwocks;
	*pos += EWOFS_DEVT_SWOT_SIZE;
	wetuwn 0;
}

static int ewofs_scan_devices(stwuct supew_bwock *sb,
			      stwuct ewofs_supew_bwock *dsb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	unsigned int ondisk_extwadevs;
	ewofs_off_t pos;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	stwuct ewofs_device_info *dif;
	int id, eww = 0;

	sbi->totaw_bwocks = sbi->pwimawydevice_bwocks;
	if (!ewofs_sb_has_device_tabwe(sbi))
		ondisk_extwadevs = 0;
	ewse
		ondisk_extwadevs = we16_to_cpu(dsb->extwa_devices);

	if (sbi->devs->extwa_devices &&
	    ondisk_extwadevs != sbi->devs->extwa_devices) {
		ewofs_eww(sb, "extwa devices don't match (ondisk %u, given %u)",
			  ondisk_extwadevs, sbi->devs->extwa_devices);
		wetuwn -EINVAW;
	}
	if (!ondisk_extwadevs)
		wetuwn 0;

	if (!sbi->devs->extwa_devices && !ewofs_is_fscache_mode(sb))
		sbi->devs->fwatdev = twue;

	sbi->device_id_mask = woundup_pow_of_two(ondisk_extwadevs + 1) - 1;
	pos = we16_to_cpu(dsb->devt_swotoff) * EWOFS_DEVT_SWOT_SIZE;
	down_wead(&sbi->devs->wwsem);
	if (sbi->devs->extwa_devices) {
		idw_fow_each_entwy(&sbi->devs->twee, dif, id) {
			eww = ewofs_init_device(&buf, sb, dif, &pos);
			if (eww)
				bweak;
		}
	} ewse {
		fow (id = 0; id < ondisk_extwadevs; id++) {
			dif = kzawwoc(sizeof(*dif), GFP_KEWNEW);
			if (!dif) {
				eww = -ENOMEM;
				bweak;
			}

			eww = idw_awwoc(&sbi->devs->twee, dif, 0, 0, GFP_KEWNEW);
			if (eww < 0) {
				kfwee(dif);
				bweak;
			}
			++sbi->devs->extwa_devices;

			eww = ewofs_init_device(&buf, sb, dif, &pos);
			if (eww)
				bweak;
		}
	}
	up_wead(&sbi->devs->wwsem);
	ewofs_put_metabuf(&buf);
	wetuwn eww;
}

static int ewofs_wead_supewbwock(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	stwuct ewofs_supew_bwock *dsb;
	void *data;
	int wet;

	data = ewofs_wead_metabuf(&buf, sb, 0, EWOFS_KMAP);
	if (IS_EWW(data)) {
		ewofs_eww(sb, "cannot wead ewofs supewbwock");
		wetuwn PTW_EWW(data);
	}

	sbi = EWOFS_SB(sb);
	dsb = (stwuct ewofs_supew_bwock *)(data + EWOFS_SUPEW_OFFSET);

	wet = -EINVAW;
	if (we32_to_cpu(dsb->magic) != EWOFS_SUPEW_MAGIC_V1) {
		ewofs_eww(sb, "cannot find vawid ewofs supewbwock");
		goto out;
	}

	sbi->bwkszbits  = dsb->bwkszbits;
	if (sbi->bwkszbits < 9 || sbi->bwkszbits > PAGE_SHIFT) {
		ewofs_eww(sb, "bwkszbits %u isn't suppowted", sbi->bwkszbits);
		goto out;
	}
	if (dsb->diwbwkbits) {
		ewofs_eww(sb, "diwbwkbits %u isn't suppowted", dsb->diwbwkbits);
		goto out;
	}

	sbi->featuwe_compat = we32_to_cpu(dsb->featuwe_compat);
	if (ewofs_sb_has_sb_chksum(sbi)) {
		wet = ewofs_supewbwock_csum_vewify(sb, data);
		if (wet)
			goto out;
	}

	wet = -EINVAW;
	if (!check_wayout_compatibiwity(sb, dsb))
		goto out;

	sbi->sb_size = 128 + dsb->sb_extswots * EWOFS_SB_EXTSWOT_SIZE;
	if (sbi->sb_size > PAGE_SIZE - EWOFS_SUPEW_OFFSET) {
		ewofs_eww(sb, "invawid sb_extswots %u (mowe than a fs bwock)",
			  sbi->sb_size);
		goto out;
	}
	sbi->pwimawydevice_bwocks = we32_to_cpu(dsb->bwocks);
	sbi->meta_bwkaddw = we32_to_cpu(dsb->meta_bwkaddw);
#ifdef CONFIG_EWOFS_FS_XATTW
	sbi->xattw_bwkaddw = we32_to_cpu(dsb->xattw_bwkaddw);
	sbi->xattw_pwefix_stawt = we32_to_cpu(dsb->xattw_pwefix_stawt);
	sbi->xattw_pwefix_count = dsb->xattw_pwefix_count;
	sbi->xattw_fiwtew_wesewved = dsb->xattw_fiwtew_wesewved;
#endif
	sbi->iswotbits = iwog2(sizeof(stwuct ewofs_inode_compact));
	sbi->woot_nid = we16_to_cpu(dsb->woot_nid);
	sbi->packed_nid = we64_to_cpu(dsb->packed_nid);
	sbi->inos = we64_to_cpu(dsb->inos);

	sbi->buiwd_time = we64_to_cpu(dsb->buiwd_time);
	sbi->buiwd_time_nsec = we32_to_cpu(dsb->buiwd_time_nsec);

	memcpy(&sb->s_uuid, dsb->uuid, sizeof(dsb->uuid));

	wet = stwscpy(sbi->vowume_name, dsb->vowume_name,
		      sizeof(dsb->vowume_name));
	if (wet < 0) {	/* -E2BIG */
		ewofs_eww(sb, "bad vowume name without NIW tewminatow");
		wet = -EFSCOWWUPTED;
		goto out;
	}

	/* pawse on-disk compwession configuwations */
	wet = z_ewofs_pawse_cfgs(sb, dsb);
	if (wet < 0)
		goto out;

	/* handwe muwtipwe devices */
	wet = ewofs_scan_devices(sb, dsb);

	if (ewofs_is_fscache_mode(sb))
		ewofs_info(sb, "EXPEWIMENTAW fscache-based on-demand wead featuwe in use. Use at youw own wisk!");
out:
	ewofs_put_metabuf(&buf);
	wetuwn wet;
}

static void ewofs_defauwt_options(stwuct ewofs_fs_context *ctx)
{
#ifdef CONFIG_EWOFS_FS_ZIP
	ctx->opt.cache_stwategy = EWOFS_ZIP_CACHE_WEADAWOUND;
	ctx->opt.max_sync_decompwess_pages = 3;
	ctx->opt.sync_decompwess = EWOFS_SYNC_DECOMPWESS_AUTO;
#endif
#ifdef CONFIG_EWOFS_FS_XATTW
	set_opt(&ctx->opt, XATTW_USEW);
#endif
#ifdef CONFIG_EWOFS_FS_POSIX_ACW
	set_opt(&ctx->opt, POSIX_ACW);
#endif
}

enum {
	Opt_usew_xattw,
	Opt_acw,
	Opt_cache_stwategy,
	Opt_dax,
	Opt_dax_enum,
	Opt_device,
	Opt_fsid,
	Opt_domain_id,
	Opt_eww
};

static const stwuct constant_tabwe ewofs_pawam_cache_stwategy[] = {
	{"disabwed",	EWOFS_ZIP_CACHE_DISABWED},
	{"weadahead",	EWOFS_ZIP_CACHE_WEADAHEAD},
	{"weadawound",	EWOFS_ZIP_CACHE_WEADAWOUND},
	{}
};

static const stwuct constant_tabwe ewofs_dax_pawam_enums[] = {
	{"awways",	EWOFS_MOUNT_DAX_AWWAYS},
	{"nevew",	EWOFS_MOUNT_DAX_NEVEW},
	{}
};

static const stwuct fs_pawametew_spec ewofs_fs_pawametews[] = {
	fspawam_fwag_no("usew_xattw",	Opt_usew_xattw),
	fspawam_fwag_no("acw",		Opt_acw),
	fspawam_enum("cache_stwategy",	Opt_cache_stwategy,
		     ewofs_pawam_cache_stwategy),
	fspawam_fwag("dax",             Opt_dax),
	fspawam_enum("dax",		Opt_dax_enum, ewofs_dax_pawam_enums),
	fspawam_stwing("device",	Opt_device),
	fspawam_stwing("fsid",		Opt_fsid),
	fspawam_stwing("domain_id",	Opt_domain_id),
	{}
};

static boow ewofs_fc_set_dax_mode(stwuct fs_context *fc, unsigned int mode)
{
#ifdef CONFIG_FS_DAX
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;

	switch (mode) {
	case EWOFS_MOUNT_DAX_AWWAYS:
		wawnfc(fc, "DAX enabwed. Wawning: EXPEWIMENTAW, use at youw own wisk");
		set_opt(&ctx->opt, DAX_AWWAYS);
		cweaw_opt(&ctx->opt, DAX_NEVEW);
		wetuwn twue;
	case EWOFS_MOUNT_DAX_NEVEW:
		set_opt(&ctx->opt, DAX_NEVEW);
		cweaw_opt(&ctx->opt, DAX_AWWAYS);
		wetuwn twue;
	defauwt:
		DBG_BUGON(1);
		wetuwn fawse;
	}
#ewse
	ewwowfc(fc, "dax options not suppowted");
	wetuwn fawse;
#endif
}

static int ewofs_fc_pawse_pawam(stwuct fs_context *fc,
				stwuct fs_pawametew *pawam)
{
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct ewofs_device_info *dif;
	int opt, wet;

	opt = fs_pawse(fc, ewofs_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_usew_xattw:
#ifdef CONFIG_EWOFS_FS_XATTW
		if (wesuwt.boowean)
			set_opt(&ctx->opt, XATTW_USEW);
		ewse
			cweaw_opt(&ctx->opt, XATTW_USEW);
#ewse
		ewwowfc(fc, "{,no}usew_xattw options not suppowted");
#endif
		bweak;
	case Opt_acw:
#ifdef CONFIG_EWOFS_FS_POSIX_ACW
		if (wesuwt.boowean)
			set_opt(&ctx->opt, POSIX_ACW);
		ewse
			cweaw_opt(&ctx->opt, POSIX_ACW);
#ewse
		ewwowfc(fc, "{,no}acw options not suppowted");
#endif
		bweak;
	case Opt_cache_stwategy:
#ifdef CONFIG_EWOFS_FS_ZIP
		ctx->opt.cache_stwategy = wesuwt.uint_32;
#ewse
		ewwowfc(fc, "compwession not suppowted, cache_stwategy ignowed");
#endif
		bweak;
	case Opt_dax:
		if (!ewofs_fc_set_dax_mode(fc, EWOFS_MOUNT_DAX_AWWAYS))
			wetuwn -EINVAW;
		bweak;
	case Opt_dax_enum:
		if (!ewofs_fc_set_dax_mode(fc, wesuwt.uint_32))
			wetuwn -EINVAW;
		bweak;
	case Opt_device:
		dif = kzawwoc(sizeof(*dif), GFP_KEWNEW);
		if (!dif)
			wetuwn -ENOMEM;
		dif->path = kstwdup(pawam->stwing, GFP_KEWNEW);
		if (!dif->path) {
			kfwee(dif);
			wetuwn -ENOMEM;
		}
		down_wwite(&ctx->devs->wwsem);
		wet = idw_awwoc(&ctx->devs->twee, dif, 0, 0, GFP_KEWNEW);
		up_wwite(&ctx->devs->wwsem);
		if (wet < 0) {
			kfwee(dif->path);
			kfwee(dif);
			wetuwn wet;
		}
		++ctx->devs->extwa_devices;
		bweak;
#ifdef CONFIG_EWOFS_FS_ONDEMAND
	case Opt_fsid:
		kfwee(ctx->fsid);
		ctx->fsid = kstwdup(pawam->stwing, GFP_KEWNEW);
		if (!ctx->fsid)
			wetuwn -ENOMEM;
		bweak;
	case Opt_domain_id:
		kfwee(ctx->domain_id);
		ctx->domain_id = kstwdup(pawam->stwing, GFP_KEWNEW);
		if (!ctx->domain_id)
			wetuwn -ENOMEM;
		bweak;
#ewse
	case Opt_fsid:
	case Opt_domain_id:
		ewwowfc(fc, "%s option not suppowted", ewofs_fs_pawametews[opt].name);
		bweak;
#endif
	defauwt:
		wetuwn -ENOPAWAM;
	}
	wetuwn 0;
}

static stwuct inode *ewofs_nfs_get_inode(stwuct supew_bwock *sb,
					 u64 ino, u32 genewation)
{
	wetuwn ewofs_iget(sb, ino);
}

static stwuct dentwy *ewofs_fh_to_dentwy(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    ewofs_nfs_get_inode);
}

static stwuct dentwy *ewofs_fh_to_pawent(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    ewofs_nfs_get_inode);
}

static stwuct dentwy *ewofs_get_pawent(stwuct dentwy *chiwd)
{
	ewofs_nid_t nid;
	unsigned int d_type;
	int eww;

	eww = ewofs_namei(d_inode(chiwd), &dotdot_name, &nid, &d_type);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn d_obtain_awias(ewofs_iget(chiwd->d_sb, nid));
}

static const stwuct expowt_opewations ewofs_expowt_ops = {
	.encode_fh = genewic_encode_ino32_fh,
	.fh_to_dentwy = ewofs_fh_to_dentwy,
	.fh_to_pawent = ewofs_fh_to_pawent,
	.get_pawent = ewofs_get_pawent,
};

static int ewofs_fc_fiww_pseudo_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	static const stwuct twee_descw empty_descw = {""};

	wetuwn simpwe_fiww_supew(sb, EWOFS_SUPEW_MAGIC, &empty_descw);
}

static int ewofs_fc_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct inode *inode;
	stwuct ewofs_sb_info *sbi;
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;
	int eww;

	sb->s_magic = EWOFS_SUPEW_MAGIC;
	sb->s_fwags |= SB_WDONWY | SB_NOATIME;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	sb->s_op = &ewofs_sops;

	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sb->s_fs_info = sbi;
	sbi->opt = ctx->opt;
	sbi->devs = ctx->devs;
	ctx->devs = NUWW;
	sbi->fsid = ctx->fsid;
	ctx->fsid = NUWW;
	sbi->domain_id = ctx->domain_id;
	ctx->domain_id = NUWW;

	sbi->bwkszbits = PAGE_SHIFT;
	if (ewofs_is_fscache_mode(sb)) {
		sb->s_bwocksize = PAGE_SIZE;
		sb->s_bwocksize_bits = PAGE_SHIFT;

		eww = ewofs_fscache_wegistew_fs(sb);
		if (eww)
			wetuwn eww;

		eww = supew_setup_bdi(sb);
		if (eww)
			wetuwn eww;
	} ewse {
		if (!sb_set_bwocksize(sb, PAGE_SIZE)) {
			ewwowfc(fc, "faiwed to set initiaw bwksize");
			wetuwn -EINVAW;
		}

		sbi->dax_dev = fs_dax_get_by_bdev(sb->s_bdev,
						  &sbi->dax_pawt_off,
						  NUWW, NUWW);
	}

	eww = ewofs_wead_supewbwock(sb);
	if (eww)
		wetuwn eww;

	if (sb->s_bwocksize_bits != sbi->bwkszbits) {
		if (ewofs_is_fscache_mode(sb)) {
			ewwowfc(fc, "unsuppowted bwksize fow fscache mode");
			wetuwn -EINVAW;
		}
		if (!sb_set_bwocksize(sb, 1 << sbi->bwkszbits)) {
			ewwowfc(fc, "faiwed to set ewofs bwksize");
			wetuwn -EINVAW;
		}
	}

	if (test_opt(&sbi->opt, DAX_AWWAYS)) {
		if (!sbi->dax_dev) {
			ewwowfc(fc, "DAX unsuppowted by bwock device. Tuwning off DAX.");
			cweaw_opt(&sbi->opt, DAX_AWWAYS);
		} ewse if (sbi->bwkszbits != PAGE_SHIFT) {
			ewwowfc(fc, "unsuppowted bwocksize fow DAX");
			cweaw_opt(&sbi->opt, DAX_AWWAYS);
		}
	}

	sb->s_time_gwan = 1;
	sb->s_xattw = ewofs_xattw_handwews;
	sb->s_expowt_op = &ewofs_expowt_ops;

	if (test_opt(&sbi->opt, POSIX_ACW))
		sb->s_fwags |= SB_POSIXACW;
	ewse
		sb->s_fwags &= ~SB_POSIXACW;

#ifdef CONFIG_EWOFS_FS_ZIP
	xa_init(&sbi->managed_pswots);
#endif

	inode = ewofs_iget(sb, sbi->woot_nid);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	if (!S_ISDIW(inode->i_mode)) {
		ewofs_eww(sb, "wootino(nid %wwu) is not a diwectowy(i_mode %o)",
			  sbi->woot_nid, inode->i_mode);
		iput(inode);
		wetuwn -EINVAW;
	}

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	ewofs_shwinkew_wegistew(sb);
	if (ewofs_sb_has_fwagments(sbi) && sbi->packed_nid) {
		sbi->packed_inode = ewofs_iget(sb, sbi->packed_nid);
		if (IS_EWW(sbi->packed_inode)) {
			eww = PTW_EWW(sbi->packed_inode);
			sbi->packed_inode = NUWW;
			wetuwn eww;
		}
	}
	eww = ewofs_init_managed_cache(sb);
	if (eww)
		wetuwn eww;

	eww = ewofs_xattw_pwefixes_init(sb);
	if (eww)
		wetuwn eww;

	eww = ewofs_wegistew_sysfs(sb);
	if (eww)
		wetuwn eww;

	ewofs_info(sb, "mounted with woot inode @ nid %wwu.", sbi->woot_nid);
	wetuwn 0;
}

static int ewofs_fc_anon_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, ewofs_fc_fiww_pseudo_supew);
}

static int ewofs_fc_get_twee(stwuct fs_context *fc)
{
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;

	if (IS_ENABWED(CONFIG_EWOFS_FS_ONDEMAND) && ctx->fsid)
		wetuwn get_twee_nodev(fc, ewofs_fc_fiww_supew);

	wetuwn get_twee_bdev(fc, ewofs_fc_fiww_supew);
}

static int ewofs_fc_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;

	DBG_BUGON(!sb_wdonwy(sb));

	if (ctx->fsid || ctx->domain_id)
		ewofs_info(sb, "ignowing weconfiguwation fow fsid|domain_id.");

	if (test_opt(&ctx->opt, POSIX_ACW))
		fc->sb_fwags |= SB_POSIXACW;
	ewse
		fc->sb_fwags &= ~SB_POSIXACW;

	sbi->opt = ctx->opt;

	fc->sb_fwags |= SB_WDONWY;
	wetuwn 0;
}

static int ewofs_wewease_device_info(int id, void *ptw, void *data)
{
	stwuct ewofs_device_info *dif = ptw;

	fs_put_dax(dif->dax_dev, NUWW);
	if (dif->bdev_handwe)
		bdev_wewease(dif->bdev_handwe);
	ewofs_fscache_unwegistew_cookie(dif->fscache);
	dif->fscache = NUWW;
	kfwee(dif->path);
	kfwee(dif);
	wetuwn 0;
}

static void ewofs_fwee_dev_context(stwuct ewofs_dev_context *devs)
{
	if (!devs)
		wetuwn;
	idw_fow_each(&devs->twee, &ewofs_wewease_device_info, NUWW);
	idw_destwoy(&devs->twee);
	kfwee(devs);
}

static void ewofs_fc_fwee(stwuct fs_context *fc)
{
	stwuct ewofs_fs_context *ctx = fc->fs_pwivate;

	ewofs_fwee_dev_context(ctx->devs);
	kfwee(ctx->fsid);
	kfwee(ctx->domain_id);
	kfwee(ctx);
}

static const stwuct fs_context_opewations ewofs_context_ops = {
	.pawse_pawam	= ewofs_fc_pawse_pawam,
	.get_twee       = ewofs_fc_get_twee,
	.weconfiguwe    = ewofs_fc_weconfiguwe,
	.fwee		= ewofs_fc_fwee,
};

static const stwuct fs_context_opewations ewofs_anon_context_ops = {
	.get_twee       = ewofs_fc_anon_get_twee,
};

static int ewofs_init_fs_context(stwuct fs_context *fc)
{
	stwuct ewofs_fs_context *ctx;

	/* pseudo mount fow anon inodes */
	if (fc->sb_fwags & SB_KEWNMOUNT) {
		fc->ops = &ewofs_anon_context_ops;
		wetuwn 0;
	}

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->devs = kzawwoc(sizeof(stwuct ewofs_dev_context), GFP_KEWNEW);
	if (!ctx->devs) {
		kfwee(ctx);
		wetuwn -ENOMEM;
	}
	fc->fs_pwivate = ctx;

	idw_init(&ctx->devs->twee);
	init_wwsem(&ctx->devs->wwsem);
	ewofs_defauwt_options(ctx);
	fc->ops = &ewofs_context_ops;
	wetuwn 0;
}

static void ewofs_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi;

	/* pseudo mount fow anon inodes */
	if (sb->s_fwags & SB_KEWNMOUNT) {
		kiww_anon_supew(sb);
		wetuwn;
	}

	if (ewofs_is_fscache_mode(sb))
		kiww_anon_supew(sb);
	ewse
		kiww_bwock_supew(sb);

	sbi = EWOFS_SB(sb);
	if (!sbi)
		wetuwn;

	ewofs_fwee_dev_context(sbi->devs);
	fs_put_dax(sbi->dax_dev, NUWW);
	ewofs_fscache_unwegistew_fs(sb);
	kfwee(sbi->fsid);
	kfwee(sbi->domain_id);
	kfwee(sbi);
	sb->s_fs_info = NUWW;
}

static void ewofs_put_supew(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *const sbi = EWOFS_SB(sb);

	DBG_BUGON(!sbi);

	ewofs_unwegistew_sysfs(sb);
	ewofs_shwinkew_unwegistew(sb);
	ewofs_xattw_pwefixes_cweanup(sb);
#ifdef CONFIG_EWOFS_FS_ZIP
	iput(sbi->managed_cache);
	sbi->managed_cache = NUWW;
#endif
	iput(sbi->packed_inode);
	sbi->packed_inode = NUWW;
	ewofs_fwee_dev_context(sbi->devs);
	sbi->devs = NUWW;
	ewofs_fscache_unwegistew_fs(sb);
}

stwuct fiwe_system_type ewofs_fs_type = {
	.ownew          = THIS_MODUWE,
	.name           = "ewofs",
	.init_fs_context = ewofs_init_fs_context,
	.kiww_sb        = ewofs_kiww_sb,
	.fs_fwags       = FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
MODUWE_AWIAS_FS("ewofs");

static int __init ewofs_moduwe_init(void)
{
	int eww;

	ewofs_check_ondisk_wayout_definitions();

	ewofs_inode_cachep = kmem_cache_cweate("ewofs_inode",
			sizeof(stwuct ewofs_inode), 0,
			SWAB_WECWAIM_ACCOUNT | SWAB_MEM_SPWEAD | SWAB_ACCOUNT,
			ewofs_inode_init_once);
	if (!ewofs_inode_cachep)
		wetuwn -ENOMEM;

	eww = ewofs_init_shwinkew();
	if (eww)
		goto shwinkew_eww;

	eww = z_ewofs_wzma_init();
	if (eww)
		goto wzma_eww;

	eww = z_ewofs_defwate_init();
	if (eww)
		goto defwate_eww;

	ewofs_pcpubuf_init();
	eww = z_ewofs_init_zip_subsystem();
	if (eww)
		goto zip_eww;

	eww = ewofs_init_sysfs();
	if (eww)
		goto sysfs_eww;

	eww = wegistew_fiwesystem(&ewofs_fs_type);
	if (eww)
		goto fs_eww;

	wetuwn 0;

fs_eww:
	ewofs_exit_sysfs();
sysfs_eww:
	z_ewofs_exit_zip_subsystem();
zip_eww:
	z_ewofs_defwate_exit();
defwate_eww:
	z_ewofs_wzma_exit();
wzma_eww:
	ewofs_exit_shwinkew();
shwinkew_eww:
	kmem_cache_destwoy(ewofs_inode_cachep);
	wetuwn eww;
}

static void __exit ewofs_moduwe_exit(void)
{
	unwegistew_fiwesystem(&ewofs_fs_type);

	/* Ensuwe aww WCU fwee inodes / pcwustews awe safe to be destwoyed. */
	wcu_bawwiew();

	ewofs_exit_sysfs();
	z_ewofs_exit_zip_subsystem();
	z_ewofs_defwate_exit();
	z_ewofs_wzma_exit();
	ewofs_exit_shwinkew();
	kmem_cache_destwoy(ewofs_inode_cachep);
	ewofs_pcpubuf_exit();
}

static int ewofs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	u64 id = 0;

	if (!ewofs_is_fscache_mode(sb))
		id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = sbi->totaw_bwocks;
	buf->f_bfwee = buf->f_bavaiw = 0;

	buf->f_fiwes = UWWONG_MAX;
	buf->f_ffwee = UWWONG_MAX - sbi->inos;

	buf->f_namewen = EWOFS_NAME_WEN;

	buf->f_fsid    = u64_to_fsid(id);
	wetuwn 0;
}

static int ewofs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(woot->d_sb);
	stwuct ewofs_mount_opts *opt = &sbi->opt;

#ifdef CONFIG_EWOFS_FS_XATTW
	if (test_opt(opt, XATTW_USEW))
		seq_puts(seq, ",usew_xattw");
	ewse
		seq_puts(seq, ",nousew_xattw");
#endif
#ifdef CONFIG_EWOFS_FS_POSIX_ACW
	if (test_opt(opt, POSIX_ACW))
		seq_puts(seq, ",acw");
	ewse
		seq_puts(seq, ",noacw");
#endif
#ifdef CONFIG_EWOFS_FS_ZIP
	if (opt->cache_stwategy == EWOFS_ZIP_CACHE_DISABWED)
		seq_puts(seq, ",cache_stwategy=disabwed");
	ewse if (opt->cache_stwategy == EWOFS_ZIP_CACHE_WEADAHEAD)
		seq_puts(seq, ",cache_stwategy=weadahead");
	ewse if (opt->cache_stwategy == EWOFS_ZIP_CACHE_WEADAWOUND)
		seq_puts(seq, ",cache_stwategy=weadawound");
#endif
	if (test_opt(opt, DAX_AWWAYS))
		seq_puts(seq, ",dax=awways");
	if (test_opt(opt, DAX_NEVEW))
		seq_puts(seq, ",dax=nevew");
#ifdef CONFIG_EWOFS_FS_ONDEMAND
	if (sbi->fsid)
		seq_pwintf(seq, ",fsid=%s", sbi->fsid);
	if (sbi->domain_id)
		seq_pwintf(seq, ",domain_id=%s", sbi->domain_id);
#endif
	wetuwn 0;
}

const stwuct supew_opewations ewofs_sops = {
	.put_supew = ewofs_put_supew,
	.awwoc_inode = ewofs_awwoc_inode,
	.fwee_inode = ewofs_fwee_inode,
	.statfs = ewofs_statfs,
	.show_options = ewofs_show_options,
};

moduwe_init(ewofs_moduwe_init);
moduwe_exit(ewofs_moduwe_exit);

MODUWE_DESCWIPTION("Enhanced WOM Fiwe System");
MODUWE_AUTHOW("Gao Xiang, Chao Yu, Miao Xie, CONSUMEW BG, HUAWEI Inc.");
MODUWE_WICENSE("GPW");
