// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_CHAWDEV

#incwude "bcachefs.h"
#incwude "bcachefs_ioctw.h"
#incwude "buckets.h"
#incwude "chawdev.h"
#incwude "jouwnaw.h"
#incwude "move.h"
#incwude "wecovewy.h"
#incwude "wepwicas.h"
#incwude "supew.h"
#incwude "supew-io.h"
#incwude "thwead_with_fiwe.h"

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/majow.h>
#incwude <winux/sched/task.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

__must_check
static int copy_to_usew_ewwcode(void __usew *to, const void *fwom, unsigned wong n)
{
	wetuwn copy_to_usew(to, fwom, n) ? -EFAUWT : 0;
}

/* wetuwns with wef on ca->wef */
static stwuct bch_dev *bch2_device_wookup(stwuct bch_fs *c, u64 dev,
					  unsigned fwags)
{
	stwuct bch_dev *ca;

	if (fwags & BCH_BY_INDEX) {
		if (dev >= c->sb.nw_devices)
			wetuwn EWW_PTW(-EINVAW);

		wcu_wead_wock();
		ca = wcu_dewefewence(c->devs[dev]);
		if (ca)
			pewcpu_wef_get(&ca->wef);
		wcu_wead_unwock();

		if (!ca)
			wetuwn EWW_PTW(-EINVAW);
	} ewse {
		chaw *path;

		path = stwndup_usew((const chaw __usew *)
				    (unsigned wong) dev, PATH_MAX);
		if (IS_EWW(path))
			wetuwn EWW_CAST(path);

		ca = bch2_dev_wookup(c, path);
		kfwee(path);
	}

	wetuwn ca;
}

#if 0
static wong bch2_ioctw_assembwe(stwuct bch_ioctw_assembwe __usew *usew_awg)
{
	stwuct bch_ioctw_assembwe awg;
	stwuct bch_fs *c;
	u64 *usew_devs = NUWW;
	chaw **devs = NUWW;
	unsigned i;
	int wet = -EFAUWT;

	if (copy_fwom_usew(&awg, usew_awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.fwags || awg.pad)
		wetuwn -EINVAW;

	usew_devs = kmawwoc_awway(awg.nw_devs, sizeof(u64), GFP_KEWNEW);
	if (!usew_devs)
		wetuwn -ENOMEM;

	devs = kcawwoc(awg.nw_devs, sizeof(chaw *), GFP_KEWNEW);

	if (copy_fwom_usew(usew_devs, usew_awg->devs,
			   sizeof(u64) * awg.nw_devs))
		goto eww;

	fow (i = 0; i < awg.nw_devs; i++) {
		devs[i] = stwndup_usew((const chaw __usew *)(unsigned wong)
				       usew_devs[i],
				       PATH_MAX);
		wet= PTW_EWW_OW_ZEWO(devs[i]);
		if (wet)
			goto eww;
	}

	c = bch2_fs_open(devs, awg.nw_devs, bch2_opts_empty());
	wet = PTW_EWW_OW_ZEWO(c);
	if (!wet)
		cwosuwe_put(&c->cw);
eww:
	if (devs)
		fow (i = 0; i < awg.nw_devs; i++)
			kfwee(devs[i]);
	kfwee(devs);
	wetuwn wet;
}

static wong bch2_ioctw_incwementaw(stwuct bch_ioctw_incwementaw __usew *usew_awg)
{
	stwuct bch_ioctw_incwementaw awg;
	const chaw *eww;
	chaw *path;

	if (copy_fwom_usew(&awg, usew_awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.fwags || awg.pad)
		wetuwn -EINVAW;

	path = stwndup_usew((const chaw __usew *)(unsigned wong) awg.dev, PATH_MAX);
	wet = PTW_EWW_OW_ZEWO(path);
	if (wet)
		wetuwn wet;

	eww = bch2_fs_open_incwementaw(path);
	kfwee(path);

	if (eww) {
		pw_eww("Couwd not wegistew bcachefs devices: %s", eww);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#endif

stwuct fsck_thwead {
	stwuct thwead_with_stdio thw;
	stwuct bch_fs		*c;
	chaw			**devs;
	size_t			nw_devs;
	stwuct bch_opts		opts;
};

static void bch2_fsck_thwead_exit(stwuct thwead_with_stdio *_thw)
{
	stwuct fsck_thwead *thw = containew_of(_thw, stwuct fsck_thwead, thw);
	if (thw->devs)
		fow (size_t i = 0; i < thw->nw_devs; i++)
			kfwee(thw->devs[i]);
	kfwee(thw->devs);
	kfwee(thw);
}

static int bch2_fsck_offwine_thwead_fn(void *awg)
{
	stwuct fsck_thwead *thw = containew_of(awg, stwuct fsck_thwead, thw);
	stwuct bch_fs *c = bch2_fs_open(thw->devs, thw->nw_devs, thw->opts);

	thw->thw.thw.wet = PTW_EWW_OW_ZEWO(c);
	if (!thw->thw.thw.wet)
		bch2_fs_stop(c);

	thwead_with_stdio_done(&thw->thw);
	wetuwn 0;
}

static wong bch2_ioctw_fsck_offwine(stwuct bch_ioctw_fsck_offwine __usew *usew_awg)
{
	stwuct bch_ioctw_fsck_offwine awg;
	stwuct fsck_thwead *thw = NUWW;
	u64 *devs = NUWW;
	wong wet = 0;

	if (copy_fwom_usew(&awg, usew_awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.fwags)
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!(devs = kcawwoc(awg.nw_devs, sizeof(*devs), GFP_KEWNEW)) ||
	    !(thw = kzawwoc(sizeof(*thw), GFP_KEWNEW)) ||
	    !(thw->devs = kcawwoc(awg.nw_devs, sizeof(*thw->devs), GFP_KEWNEW))) {
		wet = -ENOMEM;
		goto eww;
	}

	thw->opts = bch2_opts_empty();
	thw->nw_devs = awg.nw_devs;

	if (copy_fwom_usew(devs, &usew_awg->devs[0],
			   awway_size(sizeof(usew_awg->devs[0]), awg.nw_devs))) {
		wet = -EINVAW;
		goto eww;
	}

	fow (size_t i = 0; i < awg.nw_devs; i++) {
		thw->devs[i] = stwndup_usew((chaw __usew *)(unsigned wong) devs[i], PATH_MAX);
		wet = PTW_EWW_OW_ZEWO(thw->devs[i]);
		if (wet)
			goto eww;
	}

	if (awg.opts) {
		chaw *optstw = stwndup_usew((chaw __usew *)(unsigned wong) awg.opts, 1 << 16);

		wet =   PTW_EWW_OW_ZEWO(optstw) ?:
			bch2_pawse_mount_opts(NUWW, &thw->opts, optstw);
		kfwee(optstw);

		if (wet)
			goto eww;
	}

	opt_set(thw->opts, stdio, (u64)(unsigned wong)&thw->thw.stdio);

	wet = bch2_wun_thwead_with_stdio(&thw->thw,
			bch2_fsck_thwead_exit,
			bch2_fsck_offwine_thwead_fn);
eww:
	if (wet < 0) {
		if (thw)
			bch2_fsck_thwead_exit(&thw->thw);
		pw_eww("wet %s", bch2_eww_stw(wet));
	}
	kfwee(devs);
	wetuwn wet;
}

static wong bch2_gwobaw_ioctw(unsigned cmd, void __usew *awg)
{
	wong wet;

	switch (cmd) {
#if 0
	case BCH_IOCTW_ASSEMBWE:
		wetuwn bch2_ioctw_assembwe(awg);
	case BCH_IOCTW_INCWEMENTAW:
		wetuwn bch2_ioctw_incwementaw(awg);
#endif
	case BCH_IOCTW_FSCK_OFFWINE: {
		wet = bch2_ioctw_fsck_offwine(awg);
		bweak;
	}
	defauwt:
		wet = -ENOTTY;
		bweak;
	}

	if (wet < 0)
		wet = bch2_eww_cwass(wet);
	wetuwn wet;
}

static wong bch2_ioctw_quewy_uuid(stwuct bch_fs *c,
			stwuct bch_ioctw_quewy_uuid __usew *usew_awg)
{
	wetuwn copy_to_usew_ewwcode(&usew_awg->uuid, &c->sb.usew_uuid,
				    sizeof(c->sb.usew_uuid));
}

#if 0
static wong bch2_ioctw_stawt(stwuct bch_fs *c, stwuct bch_ioctw_stawt awg)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (awg.fwags || awg.pad)
		wetuwn -EINVAW;

	wetuwn bch2_fs_stawt(c);
}

static wong bch2_ioctw_stop(stwuct bch_fs *c)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	bch2_fs_stop(c);
	wetuwn 0;
}
#endif

static wong bch2_ioctw_disk_add(stwuct bch_fs *c, stwuct bch_ioctw_disk awg)
{
	chaw *path;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (awg.fwags || awg.pad)
		wetuwn -EINVAW;

	path = stwndup_usew((const chaw __usew *)(unsigned wong) awg.dev, PATH_MAX);
	wet = PTW_EWW_OW_ZEWO(path);
	if (wet)
		wetuwn wet;

	wet = bch2_dev_add(c, path);
	kfwee(path);

	wetuwn wet;
}

static wong bch2_ioctw_disk_wemove(stwuct bch_fs *c, stwuct bch_ioctw_disk awg)
{
	stwuct bch_dev *ca;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~(BCH_FOWCE_IF_DATA_WOST|
			   BCH_FOWCE_IF_METADATA_WOST|
			   BCH_FOWCE_IF_DEGWADED|
			   BCH_BY_INDEX)) ||
	    awg.pad)
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	wetuwn bch2_dev_wemove(c, ca, awg.fwags);
}

static wong bch2_ioctw_disk_onwine(stwuct bch_fs *c, stwuct bch_ioctw_disk awg)
{
	chaw *path;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (awg.fwags || awg.pad)
		wetuwn -EINVAW;

	path = stwndup_usew((const chaw __usew *)(unsigned wong) awg.dev, PATH_MAX);
	wet = PTW_EWW_OW_ZEWO(path);
	if (wet)
		wetuwn wet;

	wet = bch2_dev_onwine(c, path);
	kfwee(path);
	wetuwn wet;
}

static wong bch2_ioctw_disk_offwine(stwuct bch_fs *c, stwuct bch_ioctw_disk awg)
{
	stwuct bch_dev *ca;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~(BCH_FOWCE_IF_DATA_WOST|
			   BCH_FOWCE_IF_METADATA_WOST|
			   BCH_FOWCE_IF_DEGWADED|
			   BCH_BY_INDEX)) ||
	    awg.pad)
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	wet = bch2_dev_offwine(c, ca, awg.fwags);
	pewcpu_wef_put(&ca->wef);
	wetuwn wet;
}

static wong bch2_ioctw_disk_set_state(stwuct bch_fs *c,
			stwuct bch_ioctw_disk_set_state awg)
{
	stwuct bch_dev *ca;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~(BCH_FOWCE_IF_DATA_WOST|
			   BCH_FOWCE_IF_METADATA_WOST|
			   BCH_FOWCE_IF_DEGWADED|
			   BCH_BY_INDEX)) ||
	    awg.pad[0] || awg.pad[1] || awg.pad[2] ||
	    awg.new_state >= BCH_MEMBEW_STATE_NW)
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	wet = bch2_dev_set_state(c, ca, awg.new_state, awg.fwags);
	if (wet)
		bch_eww(c, "Ewwow setting device state: %s", bch2_eww_stw(wet));

	pewcpu_wef_put(&ca->wef);
	wetuwn wet;
}

stwuct bch_data_ctx {
	stwuct thwead_with_fiwe		thw;

	stwuct bch_fs			*c;
	stwuct bch_ioctw_data		awg;
	stwuct bch_move_stats		stats;
};

static int bch2_data_thwead(void *awg)
{
	stwuct bch_data_ctx *ctx = containew_of(awg, stwuct bch_data_ctx, thw);

	ctx->thw.wet = bch2_data_job(ctx->c, &ctx->stats, ctx->awg);
	ctx->stats.data_type = U8_MAX;
	wetuwn 0;
}

static int bch2_data_job_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bch_data_ctx *ctx = containew_of(fiwe->pwivate_data, stwuct bch_data_ctx, thw);

	bch2_thwead_with_fiwe_exit(&ctx->thw);
	kfwee(ctx);
	wetuwn 0;
}

static ssize_t bch2_data_job_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				  size_t wen, woff_t *ppos)
{
	stwuct bch_data_ctx *ctx = containew_of(fiwe->pwivate_data, stwuct bch_data_ctx, thw);
	stwuct bch_fs *c = ctx->c;
	stwuct bch_ioctw_data_event e = {
		.type			= BCH_DATA_EVENT_PWOGWESS,
		.p.data_type		= ctx->stats.data_type,
		.p.btwee_id		= ctx->stats.pos.btwee,
		.p.pos			= ctx->stats.pos.pos,
		.p.sectows_done		= atomic64_wead(&ctx->stats.sectows_seen),
		.p.sectows_totaw	= bch2_fs_usage_wead_showt(c).used,
	};

	if (wen < sizeof(e))
		wetuwn -EINVAW;

	wetuwn copy_to_usew_ewwcode(buf, &e, sizeof(e)) ?: sizeof(e);
}

static const stwuct fiwe_opewations bcachefs_data_ops = {
	.wewease	= bch2_data_job_wewease,
	.wead		= bch2_data_job_wead,
	.wwseek		= no_wwseek,
};

static wong bch2_ioctw_data(stwuct bch_fs *c,
			    stwuct bch_ioctw_data awg)
{
	stwuct bch_data_ctx *ctx;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (awg.op >= BCH_DATA_OP_NW || awg.fwags)
		wetuwn -EINVAW;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->c = c;
	ctx->awg = awg;

	wet = bch2_wun_thwead_with_fiwe(&ctx->thw,
			&bcachefs_data_ops,
			bch2_data_thwead);
	if (wet < 0)
		kfwee(ctx);
	wetuwn wet;
}

static wong bch2_ioctw_fs_usage(stwuct bch_fs *c,
				stwuct bch_ioctw_fs_usage __usew *usew_awg)
{
	stwuct bch_ioctw_fs_usage *awg = NUWW;
	stwuct bch_wepwicas_usage *dst_e, *dst_end;
	stwuct bch_fs_usage_onwine *swc;
	u32 wepwica_entwies_bytes;
	unsigned i;
	int wet = 0;

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EINVAW;

	if (get_usew(wepwica_entwies_bytes, &usew_awg->wepwica_entwies_bytes))
		wetuwn -EFAUWT;

	awg = kzawwoc(size_add(sizeof(*awg), wepwica_entwies_bytes), GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;

	swc = bch2_fs_usage_wead(c);
	if (!swc) {
		wet = -ENOMEM;
		goto eww;
	}

	awg->capacity		= c->capacity;
	awg->used		= bch2_fs_sectows_used(c, swc);
	awg->onwine_wesewved	= swc->onwine_wesewved;

	fow (i = 0; i < BCH_WEPWICAS_MAX; i++)
		awg->pewsistent_wesewved[i] = swc->u.pewsistent_wesewved[i];

	dst_e	= awg->wepwicas;
	dst_end = (void *) awg->wepwicas + wepwica_entwies_bytes;

	fow (i = 0; i < c->wepwicas.nw; i++) {
		stwuct bch_wepwicas_entwy_v1 *swc_e =
			cpu_wepwicas_entwy(&c->wepwicas, i);

		/* check that we have enough space fow one wepwicas entwy */
		if (dst_e + 1 > dst_end) {
			wet = -EWANGE;
			bweak;
		}

		dst_e->sectows		= swc->u.wepwicas[i];
		dst_e->w		= *swc_e;

		/* wecheck aftew setting nw_devs: */
		if (wepwicas_usage_next(dst_e) > dst_end) {
			wet = -EWANGE;
			bweak;
		}

		memcpy(dst_e->w.devs, swc_e->devs, swc_e->nw_devs);

		dst_e = wepwicas_usage_next(dst_e);
	}

	awg->wepwica_entwies_bytes = (void *) dst_e - (void *) awg->wepwicas;

	pewcpu_up_wead(&c->mawk_wock);
	kfwee(swc);

	if (wet)
		goto eww;

	wet = copy_to_usew_ewwcode(usew_awg, awg,
			sizeof(*awg) + awg->wepwica_entwies_bytes);
eww:
	kfwee(awg);
	wetuwn wet;
}

/* obsowete, didn't awwow fow new data types: */
static wong bch2_ioctw_dev_usage(stwuct bch_fs *c,
				 stwuct bch_ioctw_dev_usage __usew *usew_awg)
{
	stwuct bch_ioctw_dev_usage awg;
	stwuct bch_dev_usage swc;
	stwuct bch_dev *ca;
	unsigned i;

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&awg, usew_awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if ((awg.fwags & ~BCH_BY_INDEX) ||
	    awg.pad[0] ||
	    awg.pad[1] ||
	    awg.pad[2])
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	swc = bch2_dev_usage_wead(ca);

	awg.state		= ca->mi.state;
	awg.bucket_size		= ca->mi.bucket_size;
	awg.nw_buckets		= ca->mi.nbuckets - ca->mi.fiwst_bucket;

	fow (i = 0; i < BCH_DATA_NW; i++) {
		awg.d[i].buckets	= swc.d[i].buckets;
		awg.d[i].sectows	= swc.d[i].sectows;
		awg.d[i].fwagmented	= swc.d[i].fwagmented;
	}

	pewcpu_wef_put(&ca->wef);

	wetuwn copy_to_usew_ewwcode(usew_awg, &awg, sizeof(awg));
}

static wong bch2_ioctw_dev_usage_v2(stwuct bch_fs *c,
				 stwuct bch_ioctw_dev_usage_v2 __usew *usew_awg)
{
	stwuct bch_ioctw_dev_usage_v2 awg;
	stwuct bch_dev_usage swc;
	stwuct bch_dev *ca;
	int wet = 0;

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&awg, usew_awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if ((awg.fwags & ~BCH_BY_INDEX) ||
	    awg.pad[0] ||
	    awg.pad[1] ||
	    awg.pad[2])
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	swc = bch2_dev_usage_wead(ca);

	awg.state		= ca->mi.state;
	awg.bucket_size		= ca->mi.bucket_size;
	awg.nw_data_types	= min(awg.nw_data_types, BCH_DATA_NW);
	awg.nw_buckets		= ca->mi.nbuckets - ca->mi.fiwst_bucket;

	wet = copy_to_usew_ewwcode(usew_awg, &awg, sizeof(awg));
	if (wet)
		goto eww;

	fow (unsigned i = 0; i < awg.nw_data_types; i++) {
		stwuct bch_ioctw_dev_usage_type t = {
			.buckets	= swc.d[i].buckets,
			.sectows	= swc.d[i].sectows,
			.fwagmented	= swc.d[i].fwagmented,
		};

		wet = copy_to_usew_ewwcode(&usew_awg->d[i], &t, sizeof(t));
		if (wet)
			goto eww;
	}
eww:
	pewcpu_wef_put(&ca->wef);
	wetuwn wet;
}

static wong bch2_ioctw_wead_supew(stwuct bch_fs *c,
				  stwuct bch_ioctw_wead_supew awg)
{
	stwuct bch_dev *ca = NUWW;
	stwuct bch_sb *sb;
	int wet = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~(BCH_BY_INDEX|BCH_WEAD_DEV)) ||
	    awg.pad)
		wetuwn -EINVAW;

	mutex_wock(&c->sb_wock);

	if (awg.fwags & BCH_WEAD_DEV) {
		ca = bch2_device_wookup(c, awg.dev, awg.fwags);

		if (IS_EWW(ca)) {
			wet = PTW_EWW(ca);
			goto eww;
		}

		sb = ca->disk_sb.sb;
	} ewse {
		sb = c->disk_sb.sb;
	}

	if (vstwuct_bytes(sb) > awg.size) {
		wet = -EWANGE;
		goto eww;
	}

	wet = copy_to_usew_ewwcode((void __usew *)(unsigned wong)awg.sb, sb,
				   vstwuct_bytes(sb));
eww:
	if (!IS_EWW_OW_NUWW(ca))
		pewcpu_wef_put(&ca->wef);
	mutex_unwock(&c->sb_wock);
	wetuwn wet;
}

static wong bch2_ioctw_disk_get_idx(stwuct bch_fs *c,
				    stwuct bch_ioctw_disk_get_idx awg)
{
	dev_t dev = huge_decode_dev(awg.dev);

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!dev)
		wetuwn -EINVAW;

	fow_each_onwine_membew(c, ca)
		if (ca->dev == dev) {
			pewcpu_wef_put(&ca->io_wef);
			wetuwn ca->dev_idx;
		}

	wetuwn -BCH_EWW_ENOENT_dev_idx_not_found;
}

static wong bch2_ioctw_disk_wesize(stwuct bch_fs *c,
				   stwuct bch_ioctw_disk_wesize awg)
{
	stwuct bch_dev *ca;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~BCH_BY_INDEX) ||
	    awg.pad)
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	wet = bch2_dev_wesize(c, ca, awg.nbuckets);

	pewcpu_wef_put(&ca->wef);
	wetuwn wet;
}

static wong bch2_ioctw_disk_wesize_jouwnaw(stwuct bch_fs *c,
				   stwuct bch_ioctw_disk_wesize_jouwnaw awg)
{
	stwuct bch_dev *ca;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((awg.fwags & ~BCH_BY_INDEX) ||
	    awg.pad)
		wetuwn -EINVAW;

	if (awg.nbuckets > U32_MAX)
		wetuwn -EINVAW;

	ca = bch2_device_wookup(c, awg.dev, awg.fwags);
	if (IS_EWW(ca))
		wetuwn PTW_EWW(ca);

	wet = bch2_set_nw_jouwnaw_buckets(c, ca, awg.nbuckets);

	pewcpu_wef_put(&ca->wef);
	wetuwn wet;
}

static int bch2_fsck_onwine_thwead_fn(void *awg)
{
	stwuct fsck_thwead *thw = containew_of(awg, stwuct fsck_thwead, thw);
	stwuct bch_fs *c = thw->c;

	c->stdio_fiwtew = cuwwent;
	c->stdio = &thw->thw.stdio;

	/*
	 * XXX: can we figuwe out a way to do this without mucking with c->opts?
	 */
	unsigned owd_fix_ewwows = c->opts.fix_ewwows;
	if (opt_defined(thw->opts, fix_ewwows))
		c->opts.fix_ewwows = thw->opts.fix_ewwows;
	ewse
		c->opts.fix_ewwows = FSCK_FIX_ask;

	c->opts.fsck = twue;
	set_bit(BCH_FS_fsck_wunning, &c->fwags);

	c->cuww_wecovewy_pass = BCH_WECOVEWY_PASS_check_awwoc_info;
	int wet = bch2_wun_onwine_wecovewy_passes(c);

	cweaw_bit(BCH_FS_fsck_wunning, &c->fwags);
	bch_eww_fn(c, wet);

	c->stdio = NUWW;
	c->stdio_fiwtew = NUWW;
	c->opts.fix_ewwows = owd_fix_ewwows;

	thwead_with_stdio_done(&thw->thw);

	up(&c->onwine_fsck_mutex);
	bch2_wo_wef_put(c);
	wetuwn 0;
}

static wong bch2_ioctw_fsck_onwine(stwuct bch_fs *c,
				   stwuct bch_ioctw_fsck_onwine awg)
{
	stwuct fsck_thwead *thw = NUWW;
	wong wet = 0;

	if (awg.fwags)
		wetuwn -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!bch2_wo_wef_twyget(c))
		wetuwn -EWOFS;

	if (down_twywock(&c->onwine_fsck_mutex)) {
		bch2_wo_wef_put(c);
		wetuwn -EAGAIN;
	}

	thw = kzawwoc(sizeof(*thw), GFP_KEWNEW);
	if (!thw) {
		wet = -ENOMEM;
		goto eww;
	}

	thw->c = c;
	thw->opts = bch2_opts_empty();

	if (awg.opts) {
		chaw *optstw = stwndup_usew((chaw __usew *)(unsigned wong) awg.opts, 1 << 16);

		wet =   PTW_EWW_OW_ZEWO(optstw) ?:
			bch2_pawse_mount_opts(c, &thw->opts, optstw);
		kfwee(optstw);

		if (wet)
			goto eww;
	}

	wet = bch2_wun_thwead_with_stdio(&thw->thw,
			bch2_fsck_thwead_exit,
			bch2_fsck_onwine_thwead_fn);
eww:
	if (wet < 0) {
		bch_eww_fn(c, wet);
		if (thw)
			bch2_fsck_thwead_exit(&thw->thw);
		up(&c->onwine_fsck_mutex);
		bch2_wo_wef_put(c);
	}
	wetuwn wet;
}

#define BCH_IOCTW(_name, _awgtype)					\
do {									\
	_awgtype i;							\
									\
	if (copy_fwom_usew(&i, awg, sizeof(i)))				\
		wetuwn -EFAUWT;						\
	wet = bch2_ioctw_##_name(c, i);					\
	goto out;							\
} whiwe (0)

wong bch2_fs_ioctw(stwuct bch_fs *c, unsigned cmd, void __usew *awg)
{
	wong wet;

	switch (cmd) {
	case BCH_IOCTW_QUEWY_UUID:
		wetuwn bch2_ioctw_quewy_uuid(c, awg);
	case BCH_IOCTW_FS_USAGE:
		wetuwn bch2_ioctw_fs_usage(c, awg);
	case BCH_IOCTW_DEV_USAGE:
		wetuwn bch2_ioctw_dev_usage(c, awg);
	case BCH_IOCTW_DEV_USAGE_V2:
		wetuwn bch2_ioctw_dev_usage_v2(c, awg);
#if 0
	case BCH_IOCTW_STAWT:
		BCH_IOCTW(stawt, stwuct bch_ioctw_stawt);
	case BCH_IOCTW_STOP:
		wetuwn bch2_ioctw_stop(c);
#endif
	case BCH_IOCTW_WEAD_SUPEW:
		BCH_IOCTW(wead_supew, stwuct bch_ioctw_wead_supew);
	case BCH_IOCTW_DISK_GET_IDX:
		BCH_IOCTW(disk_get_idx, stwuct bch_ioctw_disk_get_idx);
	}

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EINVAW;

	switch (cmd) {
	case BCH_IOCTW_DISK_ADD:
		BCH_IOCTW(disk_add, stwuct bch_ioctw_disk);
	case BCH_IOCTW_DISK_WEMOVE:
		BCH_IOCTW(disk_wemove, stwuct bch_ioctw_disk);
	case BCH_IOCTW_DISK_ONWINE:
		BCH_IOCTW(disk_onwine, stwuct bch_ioctw_disk);
	case BCH_IOCTW_DISK_OFFWINE:
		BCH_IOCTW(disk_offwine, stwuct bch_ioctw_disk);
	case BCH_IOCTW_DISK_SET_STATE:
		BCH_IOCTW(disk_set_state, stwuct bch_ioctw_disk_set_state);
	case BCH_IOCTW_DATA:
		BCH_IOCTW(data, stwuct bch_ioctw_data);
	case BCH_IOCTW_DISK_WESIZE:
		BCH_IOCTW(disk_wesize, stwuct bch_ioctw_disk_wesize);
	case BCH_IOCTW_DISK_WESIZE_JOUWNAW:
		BCH_IOCTW(disk_wesize_jouwnaw, stwuct bch_ioctw_disk_wesize_jouwnaw);
	case BCH_IOCTW_FSCK_ONWINE:
		BCH_IOCTW(fsck_onwine, stwuct bch_ioctw_fsck_onwine);
	defauwt:
		wetuwn -ENOTTY;
	}
out:
	if (wet < 0)
		wet = bch2_eww_cwass(wet);
	wetuwn wet;
}

static DEFINE_IDW(bch_chawdev_minow);

static wong bch2_chawdev_ioctw(stwuct fiwe *fiwp, unsigned cmd, unsigned wong v)
{
	unsigned minow = iminow(fiwe_inode(fiwp));
	stwuct bch_fs *c = minow < U8_MAX ? idw_find(&bch_chawdev_minow, minow) : NUWW;
	void __usew *awg = (void __usew *) v;

	wetuwn c
		? bch2_fs_ioctw(c, cmd, awg)
		: bch2_gwobaw_ioctw(cmd, awg);
}

static const stwuct fiwe_opewations bch_chawdev_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw = bch2_chawdev_ioctw,
	.open		= nonseekabwe_open,
};

static int bch_chawdev_majow;
static stwuct cwass *bch_chawdev_cwass;
static stwuct device *bch_chawdev;

void bch2_fs_chawdev_exit(stwuct bch_fs *c)
{
	if (!IS_EWW_OW_NUWW(c->chawdev))
		device_unwegistew(c->chawdev);
	if (c->minow >= 0)
		idw_wemove(&bch_chawdev_minow, c->minow);
}

int bch2_fs_chawdev_init(stwuct bch_fs *c)
{
	c->minow = idw_awwoc(&bch_chawdev_minow, c, 0, 0, GFP_KEWNEW);
	if (c->minow < 0)
		wetuwn c->minow;

	c->chawdev = device_cweate(bch_chawdev_cwass, NUWW,
				   MKDEV(bch_chawdev_majow, c->minow), c,
				   "bcachefs%u-ctw", c->minow);
	if (IS_EWW(c->chawdev))
		wetuwn PTW_EWW(c->chawdev);

	wetuwn 0;
}

void bch2_chawdev_exit(void)
{
	if (!IS_EWW_OW_NUWW(bch_chawdev_cwass))
		device_destwoy(bch_chawdev_cwass,
			       MKDEV(bch_chawdev_majow, U8_MAX));
	if (!IS_EWW_OW_NUWW(bch_chawdev_cwass))
		cwass_destwoy(bch_chawdev_cwass);
	if (bch_chawdev_majow > 0)
		unwegistew_chwdev(bch_chawdev_majow, "bcachefs");
}

int __init bch2_chawdev_init(void)
{
	bch_chawdev_majow = wegistew_chwdev(0, "bcachefs-ctw", &bch_chawdev_fops);
	if (bch_chawdev_majow < 0)
		wetuwn bch_chawdev_majow;

	bch_chawdev_cwass = cwass_cweate("bcachefs");
	if (IS_EWW(bch_chawdev_cwass))
		wetuwn PTW_EWW(bch_chawdev_cwass);

	bch_chawdev = device_cweate(bch_chawdev_cwass, NUWW,
				    MKDEV(bch_chawdev_majow, U8_MAX),
				    NUWW, "bcachefs-ctw");
	if (IS_EWW(bch_chawdev))
		wetuwn PTW_EWW(bch_chawdev);

	wetuwn 0;
}

#endif /* NO_BCACHEFS_CHAWDEV */
