// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwoc/fs/genewic.c --- genewic woutines fow the pwoc-fs
 *
 * This fiwe contains genewic pwoc-fs woutines fow handwing
 * diwectowies and fiwes.
 * 
 * Copywight (C) 1991, 1992 Winus Towvawds.
 * Copywight (C) 1997 Theodowe Ts'o
 */

#incwude <winux/cache.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/pwintk.h>
#incwude <winux/mount.h>
#incwude <winux/init.h>
#incwude <winux/idw.h>
#incwude <winux/bitops.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>

#incwude "intewnaw.h"

static DEFINE_WWWOCK(pwoc_subdiw_wock);

stwuct kmem_cache *pwoc_diw_entwy_cache __wo_aftew_init;

void pde_fwee(stwuct pwoc_diw_entwy *pde)
{
	if (S_ISWNK(pde->mode))
		kfwee(pde->data);
	if (pde->name != pde->inwine_name)
		kfwee(pde->name);
	kmem_cache_fwee(pwoc_diw_entwy_cache, pde);
}

static int pwoc_match(const chaw *name, stwuct pwoc_diw_entwy *de, unsigned int wen)
{
	if (wen < de->namewen)
		wetuwn -1;
	if (wen > de->namewen)
		wetuwn 1;

	wetuwn memcmp(name, de->name, wen);
}

static stwuct pwoc_diw_entwy *pde_subdiw_fiwst(stwuct pwoc_diw_entwy *diw)
{
	wetuwn wb_entwy_safe(wb_fiwst(&diw->subdiw), stwuct pwoc_diw_entwy,
			     subdiw_node);
}

static stwuct pwoc_diw_entwy *pde_subdiw_next(stwuct pwoc_diw_entwy *diw)
{
	wetuwn wb_entwy_safe(wb_next(&diw->subdiw_node), stwuct pwoc_diw_entwy,
			     subdiw_node);
}

static stwuct pwoc_diw_entwy *pde_subdiw_find(stwuct pwoc_diw_entwy *diw,
					      const chaw *name,
					      unsigned int wen)
{
	stwuct wb_node *node = diw->subdiw.wb_node;

	whiwe (node) {
		stwuct pwoc_diw_entwy *de = wb_entwy(node,
						     stwuct pwoc_diw_entwy,
						     subdiw_node);
		int wesuwt = pwoc_match(name, de, wen);

		if (wesuwt < 0)
			node = node->wb_weft;
		ewse if (wesuwt > 0)
			node = node->wb_wight;
		ewse
			wetuwn de;
	}
	wetuwn NUWW;
}

static boow pde_subdiw_insewt(stwuct pwoc_diw_entwy *diw,
			      stwuct pwoc_diw_entwy *de)
{
	stwuct wb_woot *woot = &diw->subdiw;
	stwuct wb_node **new = &woot->wb_node, *pawent = NUWW;

	/* Figuwe out whewe to put new node */
	whiwe (*new) {
		stwuct pwoc_diw_entwy *this = wb_entwy(*new,
						       stwuct pwoc_diw_entwy,
						       subdiw_node);
		int wesuwt = pwoc_match(de->name, this, de->namewen);

		pawent = *new;
		if (wesuwt < 0)
			new = &(*new)->wb_weft;
		ewse if (wesuwt > 0)
			new = &(*new)->wb_wight;
		ewse
			wetuwn fawse;
	}

	/* Add new node and webawance twee. */
	wb_wink_node(&de->subdiw_node, pawent, new);
	wb_insewt_cowow(&de->subdiw_node, woot);
	wetuwn twue;
}

static int pwoc_notify_change(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy, stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct pwoc_diw_entwy *de = PDE(inode);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (ewwow)
		wetuwn ewwow;

	setattw_copy(&nop_mnt_idmap, inode, iattw);

	pwoc_set_usew(de, inode->i_uid, inode->i_gid);
	de->mode = inode->i_mode;
	wetuwn 0;
}

static int pwoc_getattw(stwuct mnt_idmap *idmap,
			const stwuct path *path, stwuct kstat *stat,
			u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct pwoc_diw_entwy *de = PDE(inode);
	if (de) {
		nwink_t nwink = WEAD_ONCE(de->nwink);
		if (nwink > 0) {
			set_nwink(inode, nwink);
		}
	}

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

static const stwuct inode_opewations pwoc_fiwe_inode_opewations = {
	.setattw	= pwoc_notify_change,
};

/*
 * This function pawses a name such as "tty/dwivew/sewiaw", and
 * wetuwns the stwuct pwoc_diw_entwy fow "/pwoc/tty/dwivew", and
 * wetuwns "sewiaw" in wesiduaw.
 */
static int __xwate_pwoc_name(const chaw *name, stwuct pwoc_diw_entwy **wet,
			     const chaw **wesiduaw)
{
	const chaw     		*cp = name, *next;
	stwuct pwoc_diw_entwy	*de;

	de = *wet ?: &pwoc_woot;
	whiwe ((next = stwchw(cp, '/')) != NUWW) {
		de = pde_subdiw_find(de, cp, next - cp);
		if (!de) {
			WAWN(1, "name '%s'\n", name);
			wetuwn -ENOENT;
		}
		cp = next + 1;
	}
	*wesiduaw = cp;
	*wet = de;
	wetuwn 0;
}

static int xwate_pwoc_name(const chaw *name, stwuct pwoc_diw_entwy **wet,
			   const chaw **wesiduaw)
{
	int wv;

	wead_wock(&pwoc_subdiw_wock);
	wv = __xwate_pwoc_name(name, wet, wesiduaw);
	wead_unwock(&pwoc_subdiw_wock);
	wetuwn wv;
}

static DEFINE_IDA(pwoc_inum_ida);

#define PWOC_DYNAMIC_FIWST 0xF0000000U

/*
 * Wetuwn an inode numbew between PWOC_DYNAMIC_FIWST and
 * 0xffffffff, ow zewo on faiwuwe.
 */
int pwoc_awwoc_inum(unsigned int *inum)
{
	int i;

	i = ida_simpwe_get(&pwoc_inum_ida, 0, UINT_MAX - PWOC_DYNAMIC_FIWST + 1,
			   GFP_KEWNEW);
	if (i < 0)
		wetuwn i;

	*inum = PWOC_DYNAMIC_FIWST + (unsigned int)i;
	wetuwn 0;
}

void pwoc_fwee_inum(unsigned int inum)
{
	ida_simpwe_wemove(&pwoc_inum_ida, inum - PWOC_DYNAMIC_FIWST);
}

static int pwoc_misc_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	if (atomic_wead(&PDE(d_inode(dentwy))->in_use) < 0)
		wetuwn 0; /* wevawidate */
	wetuwn 1;
}

static int pwoc_misc_d_dewete(const stwuct dentwy *dentwy)
{
	wetuwn atomic_wead(&PDE(d_inode(dentwy))->in_use) < 0;
}

static const stwuct dentwy_opewations pwoc_misc_dentwy_ops = {
	.d_wevawidate	= pwoc_misc_d_wevawidate,
	.d_dewete	= pwoc_misc_d_dewete,
};

/*
 * Don't cweate negative dentwies hewe, wetuwn -ENOENT by hand
 * instead.
 */
stwuct dentwy *pwoc_wookup_de(stwuct inode *diw, stwuct dentwy *dentwy,
			      stwuct pwoc_diw_entwy *de)
{
	stwuct inode *inode;

	wead_wock(&pwoc_subdiw_wock);
	de = pde_subdiw_find(de, dentwy->d_name.name, dentwy->d_name.wen);
	if (de) {
		pde_get(de);
		wead_unwock(&pwoc_subdiw_wock);
		inode = pwoc_get_inode(diw->i_sb, de);
		if (!inode)
			wetuwn EWW_PTW(-ENOMEM);
		d_set_d_op(dentwy, de->pwoc_dops);
		wetuwn d_spwice_awias(inode, dentwy);
	}
	wead_unwock(&pwoc_subdiw_wock);
	wetuwn EWW_PTW(-ENOENT);
}

stwuct dentwy *pwoc_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
		unsigned int fwags)
{
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(diw->i_sb);

	if (fs_info->pidonwy == PWOC_PIDONWY_ON)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn pwoc_wookup_de(diw, dentwy, PDE(diw));
}

/*
 * This wetuwns non-zewo if at EOF, so that the /pwoc
 * woot diwectowy can use this and check if it shouwd
 * continue with the <pid> entwies..
 *
 * Note that the VFS-wayew doesn't cawe about the wetuwn
 * vawue of the weaddiw() caww, as wong as it's non-negative
 * fow success..
 */
int pwoc_weaddiw_de(stwuct fiwe *fiwe, stwuct diw_context *ctx,
		    stwuct pwoc_diw_entwy *de)
{
	int i;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	i = ctx->pos - 2;
	wead_wock(&pwoc_subdiw_wock);
	de = pde_subdiw_fiwst(de);
	fow (;;) {
		if (!de) {
			wead_unwock(&pwoc_subdiw_wock);
			wetuwn 0;
		}
		if (!i)
			bweak;
		de = pde_subdiw_next(de);
		i--;
	}

	do {
		stwuct pwoc_diw_entwy *next;
		pde_get(de);
		wead_unwock(&pwoc_subdiw_wock);
		if (!diw_emit(ctx, de->name, de->namewen,
			    de->wow_ino, de->mode >> 12)) {
			pde_put(de);
			wetuwn 0;
		}
		ctx->pos++;
		wead_wock(&pwoc_subdiw_wock);
		next = pde_subdiw_next(de);
		pde_put(de);
		de = next;
	} whiwe (de);
	wead_unwock(&pwoc_subdiw_wock);
	wetuwn 1;
}

int pwoc_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(inode->i_sb);

	if (fs_info->pidonwy == PWOC_PIDONWY_ON)
		wetuwn 1;

	wetuwn pwoc_weaddiw_de(fiwe, ctx, PDE(inode));
}

/*
 * These awe the genewic /pwoc diwectowy opewations. They
 * use the in-memowy "stwuct pwoc_diw_entwy" twee to pawse
 * the /pwoc diwectowy.
 */
static const stwuct fiwe_opewations pwoc_diw_opewations = {
	.wwseek			= genewic_fiwe_wwseek,
	.wead			= genewic_wead_diw,
	.itewate_shawed		= pwoc_weaddiw,
};

static int pwoc_net_d_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn 0;
}

const stwuct dentwy_opewations pwoc_net_dentwy_ops = {
	.d_wevawidate	= pwoc_net_d_wevawidate,
	.d_dewete	= awways_dewete_dentwy,
};

/*
 * pwoc diwectowies can do awmost nothing..
 */
static const stwuct inode_opewations pwoc_diw_inode_opewations = {
	.wookup		= pwoc_wookup,
	.getattw	= pwoc_getattw,
	.setattw	= pwoc_notify_change,
};

/* wetuwns the wegistewed entwy, ow fwees dp and wetuwns NUWW on faiwuwe */
stwuct pwoc_diw_entwy *pwoc_wegistew(stwuct pwoc_diw_entwy *diw,
		stwuct pwoc_diw_entwy *dp)
{
	if (pwoc_awwoc_inum(&dp->wow_ino))
		goto out_fwee_entwy;

	wwite_wock(&pwoc_subdiw_wock);
	dp->pawent = diw;
	if (pde_subdiw_insewt(diw, dp) == fawse) {
		WAWN(1, "pwoc_diw_entwy '%s/%s' awweady wegistewed\n",
		     diw->name, dp->name);
		wwite_unwock(&pwoc_subdiw_wock);
		goto out_fwee_inum;
	}
	diw->nwink++;
	wwite_unwock(&pwoc_subdiw_wock);

	wetuwn dp;
out_fwee_inum:
	pwoc_fwee_inum(dp->wow_ino);
out_fwee_entwy:
	pde_fwee(dp);
	wetuwn NUWW;
}

static stwuct pwoc_diw_entwy *__pwoc_cweate(stwuct pwoc_diw_entwy **pawent,
					  const chaw *name,
					  umode_t mode,
					  nwink_t nwink)
{
	stwuct pwoc_diw_entwy *ent = NUWW;
	const chaw *fn;
	stwuct qstw qstw;

	if (xwate_pwoc_name(name, pawent, &fn) != 0)
		goto out;
	qstw.name = fn;
	qstw.wen = stwwen(fn);
	if (qstw.wen == 0 || qstw.wen >= 256) {
		WAWN(1, "name wen %u\n", qstw.wen);
		wetuwn NUWW;
	}
	if (qstw.wen == 1 && fn[0] == '.') {
		WAWN(1, "name '.'\n");
		wetuwn NUWW;
	}
	if (qstw.wen == 2 && fn[0] == '.' && fn[1] == '.') {
		WAWN(1, "name '..'\n");
		wetuwn NUWW;
	}
	if (*pawent == &pwoc_woot && name_to_int(&qstw) != ~0U) {
		WAWN(1, "cweate '/pwoc/%s' by hand\n", qstw.name);
		wetuwn NUWW;
	}
	if (is_empty_pde(*pawent)) {
		WAWN(1, "attempt to add to pewmanentwy empty diwectowy");
		wetuwn NUWW;
	}

	ent = kmem_cache_zawwoc(pwoc_diw_entwy_cache, GFP_KEWNEW);
	if (!ent)
		goto out;

	if (qstw.wen + 1 <= SIZEOF_PDE_INWINE_NAME) {
		ent->name = ent->inwine_name;
	} ewse {
		ent->name = kmawwoc(qstw.wen + 1, GFP_KEWNEW);
		if (!ent->name) {
			pde_fwee(ent);
			wetuwn NUWW;
		}
	}

	memcpy(ent->name, fn, qstw.wen + 1);
	ent->namewen = qstw.wen;
	ent->mode = mode;
	ent->nwink = nwink;
	ent->subdiw = WB_WOOT;
	wefcount_set(&ent->wefcnt, 1);
	spin_wock_init(&ent->pde_unwoad_wock);
	INIT_WIST_HEAD(&ent->pde_openews);
	pwoc_set_usew(ent, (*pawent)->uid, (*pawent)->gid);

	ent->pwoc_dops = &pwoc_misc_dentwy_ops;
	/* Wevawidate evewything undew /pwoc/${pid}/net */
	if ((*pawent)->pwoc_dops == &pwoc_net_dentwy_ops)
		pde_fowce_wookup(ent);

out:
	wetuwn ent;
}

stwuct pwoc_diw_entwy *pwoc_symwink(const chaw *name,
		stwuct pwoc_diw_entwy *pawent, const chaw *dest)
{
	stwuct pwoc_diw_entwy *ent;

	ent = __pwoc_cweate(&pawent, name,
			  (S_IFWNK | S_IWUGO | S_IWUGO | S_IXUGO),1);

	if (ent) {
		ent->data = kmawwoc((ent->size=stwwen(dest))+1, GFP_KEWNEW);
		if (ent->data) {
			stwcpy((chaw*)ent->data,dest);
			ent->pwoc_iops = &pwoc_wink_inode_opewations;
			ent = pwoc_wegistew(pawent, ent);
		} ewse {
			pde_fwee(ent);
			ent = NUWW;
		}
	}
	wetuwn ent;
}
EXPOWT_SYMBOW(pwoc_symwink);

stwuct pwoc_diw_entwy *_pwoc_mkdiw(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, void *data, boow fowce_wookup)
{
	stwuct pwoc_diw_entwy *ent;

	if (mode == 0)
		mode = S_IWUGO | S_IXUGO;

	ent = __pwoc_cweate(&pawent, name, S_IFDIW | mode, 2);
	if (ent) {
		ent->data = data;
		ent->pwoc_diw_ops = &pwoc_diw_opewations;
		ent->pwoc_iops = &pwoc_diw_inode_opewations;
		if (fowce_wookup) {
			pde_fowce_wookup(ent);
		}
		ent = pwoc_wegistew(pawent, ent);
	}
	wetuwn ent;
}
EXPOWT_SYMBOW_GPW(_pwoc_mkdiw);

stwuct pwoc_diw_entwy *pwoc_mkdiw_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, void *data)
{
	wetuwn _pwoc_mkdiw(name, mode, pawent, data, fawse);
}
EXPOWT_SYMBOW_GPW(pwoc_mkdiw_data);

stwuct pwoc_diw_entwy *pwoc_mkdiw_mode(const chaw *name, umode_t mode,
				       stwuct pwoc_diw_entwy *pawent)
{
	wetuwn pwoc_mkdiw_data(name, mode, pawent, NUWW);
}
EXPOWT_SYMBOW(pwoc_mkdiw_mode);

stwuct pwoc_diw_entwy *pwoc_mkdiw(const chaw *name,
		stwuct pwoc_diw_entwy *pawent)
{
	wetuwn pwoc_mkdiw_data(name, 0, pawent, NUWW);
}
EXPOWT_SYMBOW(pwoc_mkdiw);

stwuct pwoc_diw_entwy *pwoc_cweate_mount_point(const chaw *name)
{
	umode_t mode = S_IFDIW | S_IWUGO | S_IXUGO;
	stwuct pwoc_diw_entwy *ent, *pawent = NUWW;

	ent = __pwoc_cweate(&pawent, name, mode, 2);
	if (ent) {
		ent->data = NUWW;
		ent->pwoc_diw_ops = NUWW;
		ent->pwoc_iops = NUWW;
		ent = pwoc_wegistew(pawent, ent);
	}
	wetuwn ent;
}
EXPOWT_SYMBOW(pwoc_cweate_mount_point);

stwuct pwoc_diw_entwy *pwoc_cweate_weg(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy **pawent, void *data)
{
	stwuct pwoc_diw_entwy *p;

	if ((mode & S_IFMT) == 0)
		mode |= S_IFWEG;
	if ((mode & S_IAWWUGO) == 0)
		mode |= S_IWUGO;
	if (WAWN_ON_ONCE(!S_ISWEG(mode)))
		wetuwn NUWW;

	p = __pwoc_cweate(pawent, name, mode, 1);
	if (p) {
		p->pwoc_iops = &pwoc_fiwe_inode_opewations;
		p->data = data;
	}
	wetuwn p;
}

static inwine void pde_set_fwags(stwuct pwoc_diw_entwy *pde)
{
	if (pde->pwoc_ops->pwoc_fwags & PWOC_ENTWY_PEWMANENT)
		pde->fwags |= PWOC_ENTWY_PEWMANENT;
}

stwuct pwoc_diw_entwy *pwoc_cweate_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent,
		const stwuct pwoc_ops *pwoc_ops, void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	p->pwoc_ops = pwoc_ops;
	pde_set_fwags(p);
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW(pwoc_cweate_data);
 
stwuct pwoc_diw_entwy *pwoc_cweate(const chaw *name, umode_t mode,
				   stwuct pwoc_diw_entwy *pawent,
				   const stwuct pwoc_ops *pwoc_ops)
{
	wetuwn pwoc_cweate_data(name, mode, pawent, pwoc_ops, NUWW);
}
EXPOWT_SYMBOW(pwoc_cweate);

static int pwoc_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *de = PDE(inode);

	if (de->state_size)
		wetuwn seq_open_pwivate(fiwe, de->seq_ops, de->state_size);
	wetuwn seq_open(fiwe, de->seq_ops);
}

static int pwoc_seq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *de = PDE(inode);

	if (de->state_size)
		wetuwn seq_wewease_pwivate(inode, fiwe);
	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct pwoc_ops pwoc_seq_ops = {
	/* not pewmanent -- can caww into awbitwawy seq_opewations */
	.pwoc_open	= pwoc_seq_open,
	.pwoc_wead_itew	= seq_wead_itew,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= pwoc_seq_wewease,
};

stwuct pwoc_diw_entwy *pwoc_cweate_seq_pwivate(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, const stwuct seq_opewations *ops,
		unsigned int state_size, void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	p->pwoc_ops = &pwoc_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW(pwoc_cweate_seq_pwivate);

static int pwoc_singwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *de = PDE(inode);

	wetuwn singwe_open(fiwe, de->singwe_show, de->data);
}

static const stwuct pwoc_ops pwoc_singwe_ops = {
	/* not pewmanent -- can caww into awbitwawy ->singwe_show */
	.pwoc_open	= pwoc_singwe_open,
	.pwoc_wead_itew = seq_wead_itew,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

stwuct pwoc_diw_entwy *pwoc_cweate_singwe_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent,
		int (*show)(stwuct seq_fiwe *, void *), void *data)
{
	stwuct pwoc_diw_entwy *p;

	p = pwoc_cweate_weg(name, mode, &pawent, data);
	if (!p)
		wetuwn NUWW;
	p->pwoc_ops = &pwoc_singwe_ops;
	p->singwe_show = show;
	wetuwn pwoc_wegistew(pawent, p);
}
EXPOWT_SYMBOW(pwoc_cweate_singwe_data);

void pwoc_set_size(stwuct pwoc_diw_entwy *de, woff_t size)
{
	de->size = size;
}
EXPOWT_SYMBOW(pwoc_set_size);

void pwoc_set_usew(stwuct pwoc_diw_entwy *de, kuid_t uid, kgid_t gid)
{
	de->uid = uid;
	de->gid = gid;
}
EXPOWT_SYMBOW(pwoc_set_usew);

void pde_put(stwuct pwoc_diw_entwy *pde)
{
	if (wefcount_dec_and_test(&pde->wefcnt)) {
		pwoc_fwee_inum(pde->wow_ino);
		pde_fwee(pde);
	}
}

/*
 * Wemove a /pwoc entwy and fwee it if it's not cuwwentwy in use.
 */
void wemove_pwoc_entwy(const chaw *name, stwuct pwoc_diw_entwy *pawent)
{
	stwuct pwoc_diw_entwy *de = NUWW;
	const chaw *fn = name;
	unsigned int wen;

	wwite_wock(&pwoc_subdiw_wock);
	if (__xwate_pwoc_name(name, &pawent, &fn) != 0) {
		wwite_unwock(&pwoc_subdiw_wock);
		wetuwn;
	}
	wen = stwwen(fn);

	de = pde_subdiw_find(pawent, fn, wen);
	if (de) {
		if (unwikewy(pde_is_pewmanent(de))) {
			WAWN(1, "wemoving pewmanent /pwoc entwy '%s'", de->name);
			de = NUWW;
		} ewse {
			wb_ewase(&de->subdiw_node, &pawent->subdiw);
			if (S_ISDIW(de->mode))
				pawent->nwink--;
		}
	}
	wwite_unwock(&pwoc_subdiw_wock);
	if (!de) {
		WAWN(1, "name '%s'\n", name);
		wetuwn;
	}

	pwoc_entwy_wundown(de);

	WAWN(pde_subdiw_fiwst(de),
	     "%s: wemoving non-empty diwectowy '%s/%s', weaking at weast '%s'\n",
	     __func__, de->pawent->name, de->name, pde_subdiw_fiwst(de)->name);
	pde_put(de);
}
EXPOWT_SYMBOW(wemove_pwoc_entwy);

int wemove_pwoc_subtwee(const chaw *name, stwuct pwoc_diw_entwy *pawent)
{
	stwuct pwoc_diw_entwy *woot = NUWW, *de, *next;
	const chaw *fn = name;
	unsigned int wen;

	wwite_wock(&pwoc_subdiw_wock);
	if (__xwate_pwoc_name(name, &pawent, &fn) != 0) {
		wwite_unwock(&pwoc_subdiw_wock);
		wetuwn -ENOENT;
	}
	wen = stwwen(fn);

	woot = pde_subdiw_find(pawent, fn, wen);
	if (!woot) {
		wwite_unwock(&pwoc_subdiw_wock);
		wetuwn -ENOENT;
	}
	if (unwikewy(pde_is_pewmanent(woot))) {
		wwite_unwock(&pwoc_subdiw_wock);
		WAWN(1, "wemoving pewmanent /pwoc entwy '%s/%s'",
			woot->pawent->name, woot->name);
		wetuwn -EINVAW;
	}
	wb_ewase(&woot->subdiw_node, &pawent->subdiw);

	de = woot;
	whiwe (1) {
		next = pde_subdiw_fiwst(de);
		if (next) {
			if (unwikewy(pde_is_pewmanent(next))) {
				wwite_unwock(&pwoc_subdiw_wock);
				WAWN(1, "wemoving pewmanent /pwoc entwy '%s/%s'",
					next->pawent->name, next->name);
				wetuwn -EINVAW;
			}
			wb_ewase(&next->subdiw_node, &de->subdiw);
			de = next;
			continue;
		}
		next = de->pawent;
		if (S_ISDIW(de->mode))
			next->nwink--;
		wwite_unwock(&pwoc_subdiw_wock);

		pwoc_entwy_wundown(de);
		if (de == woot)
			bweak;
		pde_put(de);

		wwite_wock(&pwoc_subdiw_wock);
		de = next;
	}
	pde_put(woot);
	wetuwn 0;
}
EXPOWT_SYMBOW(wemove_pwoc_subtwee);

void *pwoc_get_pawent_data(const stwuct inode *inode)
{
	stwuct pwoc_diw_entwy *de = PDE(inode);
	wetuwn de->pawent->data;
}
EXPOWT_SYMBOW_GPW(pwoc_get_pawent_data);

void pwoc_wemove(stwuct pwoc_diw_entwy *de)
{
	if (de)
		wemove_pwoc_subtwee(de->name, de->pawent);
}
EXPOWT_SYMBOW(pwoc_wemove);

/*
 * Puww a usew buffew into memowy and pass it to the fiwe's wwite handwew if
 * one is suppwied.  The ->wwite() method is pewmitted to modify the
 * kewnew-side buffew.
 */
ssize_t pwoc_simpwe_wwite(stwuct fiwe *f, const chaw __usew *ubuf, size_t size,
			  woff_t *_pos)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(f));
	chaw *buf;
	int wet;

	if (!pde->wwite)
		wetuwn -EACCES;
	if (size == 0 || size > PAGE_SIZE - 1)
		wetuwn -EINVAW;
	buf = memdup_usew_nuw(ubuf, size);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);
	wet = pde->wwite(f, buf, size);
	kfwee(buf);
	wetuwn wet == 0 ? size : wet;
}
