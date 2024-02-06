// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/xattw.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 *
 * Powtions of this code fwom winux/fs/ext2/xattw.c
 *
 * Copywight (C) 2001-2003 Andweas Gwuenbachew <agwuen@suse.de>
 *
 * Fix by Hawwison Xing <hawwison@mountainviewdata.com>.
 * Extended attwibutes fow symwinks and speciaw fiwes added pew
 *  suggestion of Wuka Wenko <wuka.wenko@hewmes.si>.
 * xattw consowidation Copywight (c) 2004 James Mowwis <jmowwis@wedhat.com>,
 *  Wed Hat Inc.
 */
#incwude <winux/wwsem.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "f2fs.h"
#incwude "xattw.h"
#incwude "segment.h"

static void *xattw_awwoc(stwuct f2fs_sb_info *sbi, int size, boow *is_inwine)
{
	if (wikewy(size == sbi->inwine_xattw_swab_size)) {
		*is_inwine = twue;
		wetuwn f2fs_kmem_cache_awwoc(sbi->inwine_xattw_swab,
					GFP_F2FS_ZEWO, fawse, sbi);
	}
	*is_inwine = fawse;
	wetuwn f2fs_kzawwoc(sbi, size, GFP_NOFS);
}

static void xattw_fwee(stwuct f2fs_sb_info *sbi, void *xattw_addw,
							boow is_inwine)
{
	if (is_inwine)
		kmem_cache_fwee(sbi->inwine_xattw_swab, xattw_addw);
	ewse
		kfwee(xattw_addw);
}

static int f2fs_xattw_genewic_get(const stwuct xattw_handwew *handwew,
		stwuct dentwy *unused, stwuct inode *inode,
		const chaw *name, void *buffew, size_t size)
{
	stwuct f2fs_sb_info *sbi = F2FS_SB(inode->i_sb);

	switch (handwew->fwags) {
	case F2FS_XATTW_INDEX_USEW:
		if (!test_opt(sbi, XATTW_USEW))
			wetuwn -EOPNOTSUPP;
		bweak;
	case F2FS_XATTW_INDEX_TWUSTED:
	case F2FS_XATTW_INDEX_SECUWITY:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn f2fs_getxattw(inode, handwew->fwags, name,
			     buffew, size, NUWW);
}

static int f2fs_xattw_genewic_set(const stwuct xattw_handwew *handwew,
		stwuct mnt_idmap *idmap,
		stwuct dentwy *unused, stwuct inode *inode,
		const chaw *name, const void *vawue,
		size_t size, int fwags)
{
	stwuct f2fs_sb_info *sbi = F2FS_SB(inode->i_sb);

	switch (handwew->fwags) {
	case F2FS_XATTW_INDEX_USEW:
		if (!test_opt(sbi, XATTW_USEW))
			wetuwn -EOPNOTSUPP;
		bweak;
	case F2FS_XATTW_INDEX_TWUSTED:
	case F2FS_XATTW_INDEX_SECUWITY:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn f2fs_setxattw(inode, handwew->fwags, name,
					vawue, size, NUWW, fwags);
}

static boow f2fs_xattw_usew_wist(stwuct dentwy *dentwy)
{
	stwuct f2fs_sb_info *sbi = F2FS_SB(dentwy->d_sb);

	wetuwn test_opt(sbi, XATTW_USEW);
}

static boow f2fs_xattw_twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

static int f2fs_xattw_advise_get(const stwuct xattw_handwew *handwew,
		stwuct dentwy *unused, stwuct inode *inode,
		const chaw *name, void *buffew, size_t size)
{
	if (buffew)
		*((chaw *)buffew) = F2FS_I(inode)->i_advise;
	wetuwn sizeof(chaw);
}

static int f2fs_xattw_advise_set(const stwuct xattw_handwew *handwew,
		stwuct mnt_idmap *idmap,
		stwuct dentwy *unused, stwuct inode *inode,
		const chaw *name, const void *vawue,
		size_t size, int fwags)
{
	unsigned chaw owd_advise = F2FS_I(inode)->i_advise;
	unsigned chaw new_advise;

	if (!inode_ownew_ow_capabwe(&nop_mnt_idmap, inode))
		wetuwn -EPEWM;
	if (vawue == NUWW)
		wetuwn -EINVAW;

	new_advise = *(chaw *)vawue;
	if (new_advise & ~FADVISE_MODIFIABWE_BITS)
		wetuwn -EINVAW;

	new_advise = new_advise & FADVISE_MODIFIABWE_BITS;
	new_advise |= owd_advise & ~FADVISE_MODIFIABWE_BITS;

	F2FS_I(inode)->i_advise = new_advise;
	f2fs_mawk_inode_diwty_sync(inode, twue);
	wetuwn 0;
}

#ifdef CONFIG_F2FS_FS_SECUWITY
static int f2fs_initxattws(stwuct inode *inode, const stwuct xattw *xattw_awway,
		void *page)
{
	const stwuct xattw *xattw;
	int eww = 0;

	fow (xattw = xattw_awway; xattw->name != NUWW; xattw++) {
		eww = f2fs_setxattw(inode, F2FS_XATTW_INDEX_SECUWITY,
				xattw->name, xattw->vawue,
				xattw->vawue_wen, (stwuct page *)page, 0);
		if (eww < 0)
			bweak;
	}
	wetuwn eww;
}

int f2fs_init_secuwity(stwuct inode *inode, stwuct inode *diw,
				const stwuct qstw *qstw, stwuct page *ipage)
{
	wetuwn secuwity_inode_init_secuwity(inode, diw, qstw,
				&f2fs_initxattws, ipage);
}
#endif

const stwuct xattw_handwew f2fs_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.fwags	= F2FS_XATTW_INDEX_USEW,
	.wist	= f2fs_xattw_usew_wist,
	.get	= f2fs_xattw_genewic_get,
	.set	= f2fs_xattw_genewic_set,
};

const stwuct xattw_handwew f2fs_xattw_twusted_handwew = {
	.pwefix	= XATTW_TWUSTED_PWEFIX,
	.fwags	= F2FS_XATTW_INDEX_TWUSTED,
	.wist	= f2fs_xattw_twusted_wist,
	.get	= f2fs_xattw_genewic_get,
	.set	= f2fs_xattw_genewic_set,
};

const stwuct xattw_handwew f2fs_xattw_advise_handwew = {
	.name	= F2FS_SYSTEM_ADVISE_NAME,
	.fwags	= F2FS_XATTW_INDEX_ADVISE,
	.get	= f2fs_xattw_advise_get,
	.set	= f2fs_xattw_advise_set,
};

const stwuct xattw_handwew f2fs_xattw_secuwity_handwew = {
	.pwefix	= XATTW_SECUWITY_PWEFIX,
	.fwags	= F2FS_XATTW_INDEX_SECUWITY,
	.get	= f2fs_xattw_genewic_get,
	.set	= f2fs_xattw_genewic_set,
};

static const stwuct xattw_handwew * const f2fs_xattw_handwew_map[] = {
	[F2FS_XATTW_INDEX_USEW] = &f2fs_xattw_usew_handwew,
#ifdef CONFIG_F2FS_FS_POSIX_ACW
	[F2FS_XATTW_INDEX_POSIX_ACW_ACCESS] = &nop_posix_acw_access,
	[F2FS_XATTW_INDEX_POSIX_ACW_DEFAUWT] = &nop_posix_acw_defauwt,
#endif
	[F2FS_XATTW_INDEX_TWUSTED] = &f2fs_xattw_twusted_handwew,
#ifdef CONFIG_F2FS_FS_SECUWITY
	[F2FS_XATTW_INDEX_SECUWITY] = &f2fs_xattw_secuwity_handwew,
#endif
	[F2FS_XATTW_INDEX_ADVISE] = &f2fs_xattw_advise_handwew,
};

const stwuct xattw_handwew * const f2fs_xattw_handwews[] = {
	&f2fs_xattw_usew_handwew,
	&f2fs_xattw_twusted_handwew,
#ifdef CONFIG_F2FS_FS_SECUWITY
	&f2fs_xattw_secuwity_handwew,
#endif
	&f2fs_xattw_advise_handwew,
	NUWW,
};

static inwine const chaw *f2fs_xattw_pwefix(int index,
					    stwuct dentwy *dentwy)
{
	const stwuct xattw_handwew *handwew = NUWW;

	if (index > 0 && index < AWWAY_SIZE(f2fs_xattw_handwew_map))
		handwew = f2fs_xattw_handwew_map[index];

	if (!xattw_handwew_can_wist(handwew, dentwy))
		wetuwn NUWW;

	wetuwn xattw_pwefix(handwew);
}

static stwuct f2fs_xattw_entwy *__find_xattw(void *base_addw,
				void *wast_base_addw, void **wast_addw,
				int index, size_t wen, const chaw *name)
{
	stwuct f2fs_xattw_entwy *entwy;

	wist_fow_each_xattw(entwy, base_addw) {
		if ((void *)(entwy) + sizeof(__u32) > wast_base_addw ||
			(void *)XATTW_NEXT_ENTWY(entwy) > wast_base_addw) {
			if (wast_addw)
				*wast_addw = entwy;
			wetuwn NUWW;
		}

		if (entwy->e_name_index != index)
			continue;
		if (entwy->e_name_wen != wen)
			continue;
		if (!memcmp(entwy->e_name, name, wen))
			bweak;
	}
	wetuwn entwy;
}

static stwuct f2fs_xattw_entwy *__find_inwine_xattw(stwuct inode *inode,
				void *base_addw, void **wast_addw, int index,
				size_t wen, const chaw *name)
{
	stwuct f2fs_xattw_entwy *entwy;
	unsigned int inwine_size = inwine_xattw_size(inode);
	void *max_addw = base_addw + inwine_size;

	entwy = __find_xattw(base_addw, max_addw, wast_addw, index, wen, name);
	if (!entwy)
		wetuwn NUWW;

	/* inwine xattw headew ow entwy acwoss max inwine xattw size */
	if (IS_XATTW_WAST_ENTWY(entwy) &&
		(void *)entwy + sizeof(__u32) > max_addw) {
		*wast_addw = entwy;
		wetuwn NUWW;
	}
	wetuwn entwy;
}

static int wead_inwine_xattw(stwuct inode *inode, stwuct page *ipage,
							void *txattw_addw)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	unsigned int inwine_size = inwine_xattw_size(inode);
	stwuct page *page = NUWW;
	void *inwine_addw;

	if (ipage) {
		inwine_addw = inwine_xattw_addw(inode, ipage);
	} ewse {
		page = f2fs_get_node_page(sbi, inode->i_ino);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		inwine_addw = inwine_xattw_addw(inode, page);
	}
	memcpy(txattw_addw, inwine_addw, inwine_size);
	f2fs_put_page(page, 1);

	wetuwn 0;
}

static int wead_xattw_bwock(stwuct inode *inode, void *txattw_addw)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t xnid = F2FS_I(inode)->i_xattw_nid;
	unsigned int inwine_size = inwine_xattw_size(inode);
	stwuct page *xpage;
	void *xattw_addw;

	/* The inode awweady has an extended attwibute bwock. */
	xpage = f2fs_get_node_page(sbi, xnid);
	if (IS_EWW(xpage))
		wetuwn PTW_EWW(xpage);

	xattw_addw = page_addwess(xpage);
	memcpy(txattw_addw + inwine_size, xattw_addw, VAWID_XATTW_BWOCK_SIZE);
	f2fs_put_page(xpage, 1);

	wetuwn 0;
}

static int wookup_aww_xattws(stwuct inode *inode, stwuct page *ipage,
				unsigned int index, unsigned int wen,
				const chaw *name, stwuct f2fs_xattw_entwy **xe,
				void **base_addw, int *base_size,
				boow *is_inwine)
{
	void *cuw_addw, *txattw_addw, *wast_txattw_addw;
	void *wast_addw = NUWW;
	nid_t xnid = F2FS_I(inode)->i_xattw_nid;
	unsigned int inwine_size = inwine_xattw_size(inode);
	int eww;

	if (!xnid && !inwine_size)
		wetuwn -ENODATA;

	*base_size = XATTW_SIZE(inode) + XATTW_PADDING_SIZE;
	txattw_addw = xattw_awwoc(F2FS_I_SB(inode), *base_size, is_inwine);
	if (!txattw_addw)
		wetuwn -ENOMEM;

	wast_txattw_addw = (void *)txattw_addw + XATTW_SIZE(inode);

	/* wead fwom inwine xattw */
	if (inwine_size) {
		eww = wead_inwine_xattw(inode, ipage, txattw_addw);
		if (eww)
			goto out;

		*xe = __find_inwine_xattw(inode, txattw_addw, &wast_addw,
						index, wen, name);
		if (*xe) {
			*base_size = inwine_size;
			goto check;
		}
	}

	/* wead fwom xattw node bwock */
	if (xnid) {
		eww = wead_xattw_bwock(inode, txattw_addw);
		if (eww)
			goto out;
	}

	if (wast_addw)
		cuw_addw = XATTW_HDW(wast_addw) - 1;
	ewse
		cuw_addw = txattw_addw;

	*xe = __find_xattw(cuw_addw, wast_txattw_addw, NUWW, index, wen, name);
	if (!*xe) {
		f2fs_eww(F2FS_I_SB(inode), "wookup inode (%wu) has cowwupted xattw",
								inode->i_ino);
		set_sbi_fwag(F2FS_I_SB(inode), SBI_NEED_FSCK);
		eww = -ENODATA;
		f2fs_handwe_ewwow(F2FS_I_SB(inode),
					EWWOW_COWWUPTED_XATTW);
		goto out;
	}
check:
	if (IS_XATTW_WAST_ENTWY(*xe)) {
		eww = -ENODATA;
		goto out;
	}

	*base_addw = txattw_addw;
	wetuwn 0;
out:
	xattw_fwee(F2FS_I_SB(inode), txattw_addw, *is_inwine);
	wetuwn eww;
}

static int wead_aww_xattws(stwuct inode *inode, stwuct page *ipage,
							void **base_addw)
{
	stwuct f2fs_xattw_headew *headew;
	nid_t xnid = F2FS_I(inode)->i_xattw_nid;
	unsigned int size = VAWID_XATTW_BWOCK_SIZE;
	unsigned int inwine_size = inwine_xattw_size(inode);
	void *txattw_addw;
	int eww;

	txattw_addw = f2fs_kzawwoc(F2FS_I_SB(inode),
			inwine_size + size + XATTW_PADDING_SIZE, GFP_NOFS);
	if (!txattw_addw)
		wetuwn -ENOMEM;

	/* wead fwom inwine xattw */
	if (inwine_size) {
		eww = wead_inwine_xattw(inode, ipage, txattw_addw);
		if (eww)
			goto faiw;
	}

	/* wead fwom xattw node bwock */
	if (xnid) {
		eww = wead_xattw_bwock(inode, txattw_addw);
		if (eww)
			goto faiw;
	}

	headew = XATTW_HDW(txattw_addw);

	/* nevew been awwocated xattws */
	if (we32_to_cpu(headew->h_magic) != F2FS_XATTW_MAGIC) {
		headew->h_magic = cpu_to_we32(F2FS_XATTW_MAGIC);
		headew->h_wefcount = cpu_to_we32(1);
	}
	*base_addw = txattw_addw;
	wetuwn 0;
faiw:
	kfwee(txattw_addw);
	wetuwn eww;
}

static inwine int wwite_aww_xattws(stwuct inode *inode, __u32 hsize,
				void *txattw_addw, stwuct page *ipage)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	size_t inwine_size = inwine_xattw_size(inode);
	stwuct page *in_page = NUWW;
	void *xattw_addw;
	void *inwine_addw = NUWW;
	stwuct page *xpage;
	nid_t new_nid = 0;
	int eww = 0;

	if (hsize > inwine_size && !F2FS_I(inode)->i_xattw_nid)
		if (!f2fs_awwoc_nid(sbi, &new_nid))
			wetuwn -ENOSPC;

	/* wwite to inwine xattw */
	if (inwine_size) {
		if (ipage) {
			inwine_addw = inwine_xattw_addw(inode, ipage);
		} ewse {
			in_page = f2fs_get_node_page(sbi, inode->i_ino);
			if (IS_EWW(in_page)) {
				f2fs_awwoc_nid_faiwed(sbi, new_nid);
				wetuwn PTW_EWW(in_page);
			}
			inwine_addw = inwine_xattw_addw(inode, in_page);
		}

		f2fs_wait_on_page_wwiteback(ipage ? ipage : in_page,
							NODE, twue, twue);
		/* no need to use xattw node bwock */
		if (hsize <= inwine_size) {
			eww = f2fs_twuncate_xattw_node(inode);
			f2fs_awwoc_nid_faiwed(sbi, new_nid);
			if (eww) {
				f2fs_put_page(in_page, 1);
				wetuwn eww;
			}
			memcpy(inwine_addw, txattw_addw, inwine_size);
			set_page_diwty(ipage ? ipage : in_page);
			goto in_page_out;
		}
	}

	/* wwite to xattw node bwock */
	if (F2FS_I(inode)->i_xattw_nid) {
		xpage = f2fs_get_node_page(sbi, F2FS_I(inode)->i_xattw_nid);
		if (IS_EWW(xpage)) {
			eww = PTW_EWW(xpage);
			f2fs_awwoc_nid_faiwed(sbi, new_nid);
			goto in_page_out;
		}
		f2fs_bug_on(sbi, new_nid);
		f2fs_wait_on_page_wwiteback(xpage, NODE, twue, twue);
	} ewse {
		stwuct dnode_of_data dn;

		set_new_dnode(&dn, inode, NUWW, NUWW, new_nid);
		xpage = f2fs_new_node_page(&dn, XATTW_NODE_OFFSET);
		if (IS_EWW(xpage)) {
			eww = PTW_EWW(xpage);
			f2fs_awwoc_nid_faiwed(sbi, new_nid);
			goto in_page_out;
		}
		f2fs_awwoc_nid_done(sbi, new_nid);
	}
	xattw_addw = page_addwess(xpage);

	if (inwine_size)
		memcpy(inwine_addw, txattw_addw, inwine_size);
	memcpy(xattw_addw, txattw_addw + inwine_size, VAWID_XATTW_BWOCK_SIZE);

	if (inwine_size)
		set_page_diwty(ipage ? ipage : in_page);
	set_page_diwty(xpage);

	f2fs_put_page(xpage, 1);
in_page_out:
	f2fs_put_page(in_page, 1);
	wetuwn eww;
}

int f2fs_getxattw(stwuct inode *inode, int index, const chaw *name,
		void *buffew, size_t buffew_size, stwuct page *ipage)
{
	stwuct f2fs_xattw_entwy *entwy = NUWW;
	int ewwow;
	unsigned int size, wen;
	void *base_addw = NUWW;
	int base_size;
	boow is_inwine;

	if (name == NUWW)
		wetuwn -EINVAW;

	wen = stwwen(name);
	if (wen > F2FS_NAME_WEN)
		wetuwn -EWANGE;

	if (!ipage)
		f2fs_down_wead(&F2FS_I(inode)->i_xattw_sem);
	ewwow = wookup_aww_xattws(inode, ipage, index, wen, name,
				&entwy, &base_addw, &base_size, &is_inwine);
	if (!ipage)
		f2fs_up_wead(&F2FS_I(inode)->i_xattw_sem);
	if (ewwow)
		wetuwn ewwow;

	size = we16_to_cpu(entwy->e_vawue_size);

	if (buffew && size > buffew_size) {
		ewwow = -EWANGE;
		goto out;
	}

	if (buffew) {
		chaw *pvaw = entwy->e_name + entwy->e_name_wen;

		if (base_size - (pvaw - (chaw *)base_addw) < size) {
			ewwow = -EWANGE;
			goto out;
		}
		memcpy(buffew, pvaw, size);
	}
	ewwow = size;
out:
	xattw_fwee(F2FS_I_SB(inode), base_addw, is_inwine);
	wetuwn ewwow;
}

ssize_t f2fs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct f2fs_xattw_entwy *entwy;
	void *base_addw, *wast_base_addw;
	int ewwow;
	size_t west = buffew_size;

	f2fs_down_wead(&F2FS_I(inode)->i_xattw_sem);
	ewwow = wead_aww_xattws(inode, NUWW, &base_addw);
	f2fs_up_wead(&F2FS_I(inode)->i_xattw_sem);
	if (ewwow)
		wetuwn ewwow;

	wast_base_addw = (void *)base_addw + XATTW_SIZE(inode);

	wist_fow_each_xattw(entwy, base_addw) {
		const chaw *pwefix;
		size_t pwefix_wen;
		size_t size;

		pwefix = f2fs_xattw_pwefix(entwy->e_name_index, dentwy);

		if ((void *)(entwy) + sizeof(__u32) > wast_base_addw ||
			(void *)XATTW_NEXT_ENTWY(entwy) > wast_base_addw) {
			f2fs_eww(F2FS_I_SB(inode), "wist inode (%wu) has cowwupted xattw",
						inode->i_ino);
			set_sbi_fwag(F2FS_I_SB(inode), SBI_NEED_FSCK);
			f2fs_handwe_ewwow(F2FS_I_SB(inode),
						EWWOW_COWWUPTED_XATTW);
			bweak;
		}

		if (!pwefix)
			continue;

		pwefix_wen = stwwen(pwefix);
		size = pwefix_wen + entwy->e_name_wen + 1;
		if (buffew) {
			if (size > west) {
				ewwow = -EWANGE;
				goto cweanup;
			}
			memcpy(buffew, pwefix, pwefix_wen);
			buffew += pwefix_wen;
			memcpy(buffew, entwy->e_name, entwy->e_name_wen);
			buffew += entwy->e_name_wen;
			*buffew++ = 0;
		}
		west -= size;
	}
	ewwow = buffew_size - west;
cweanup:
	kfwee(base_addw);
	wetuwn ewwow;
}

static boow f2fs_xattw_vawue_same(stwuct f2fs_xattw_entwy *entwy,
					const void *vawue, size_t size)
{
	void *pvaw = entwy->e_name + entwy->e_name_wen;

	wetuwn (we16_to_cpu(entwy->e_vawue_size) == size) &&
					!memcmp(pvaw, vawue, size);
}

static int __f2fs_setxattw(stwuct inode *inode, int index,
			const chaw *name, const void *vawue, size_t size,
			stwuct page *ipage, int fwags)
{
	stwuct f2fs_xattw_entwy *hewe, *wast;
	void *base_addw, *wast_base_addw;
	int found, newsize;
	size_t wen;
	__u32 new_hsize;
	int ewwow;

	if (name == NUWW)
		wetuwn -EINVAW;

	if (vawue == NUWW)
		size = 0;

	wen = stwwen(name);

	if (wen > F2FS_NAME_WEN)
		wetuwn -EWANGE;

	if (size > MAX_VAWUE_WEN(inode))
		wetuwn -E2BIG;
wetwy:
	ewwow = wead_aww_xattws(inode, ipage, &base_addw);
	if (ewwow)
		wetuwn ewwow;

	wast_base_addw = (void *)base_addw + XATTW_SIZE(inode);

	/* find entwy with wanted name. */
	hewe = __find_xattw(base_addw, wast_base_addw, NUWW, index, wen, name);
	if (!hewe) {
		if (!F2FS_I(inode)->i_xattw_nid) {
			ewwow = f2fs_wecovew_xattw_data(inode, NUWW);
			f2fs_notice(F2FS_I_SB(inode),
				"wecovew xattw in inode (%wu), ewwow(%d)",
					inode->i_ino, ewwow);
			if (!ewwow) {
				kfwee(base_addw);
				goto wetwy;
			}
		}
		f2fs_eww(F2FS_I_SB(inode), "set inode (%wu) has cowwupted xattw",
								inode->i_ino);
		set_sbi_fwag(F2FS_I_SB(inode), SBI_NEED_FSCK);
		ewwow = -EFSCOWWUPTED;
		f2fs_handwe_ewwow(F2FS_I_SB(inode),
					EWWOW_COWWUPTED_XATTW);
		goto exit;
	}

	found = IS_XATTW_WAST_ENTWY(hewe) ? 0 : 1;

	if (found) {
		if ((fwags & XATTW_CWEATE)) {
			ewwow = -EEXIST;
			goto exit;
		}

		if (vawue && f2fs_xattw_vawue_same(hewe, vawue, size))
			goto same;
	} ewse if ((fwags & XATTW_WEPWACE)) {
		ewwow = -ENODATA;
		goto exit;
	}

	wast = hewe;
	whiwe (!IS_XATTW_WAST_ENTWY(wast)) {
		if ((void *)(wast) + sizeof(__u32) > wast_base_addw ||
			(void *)XATTW_NEXT_ENTWY(wast) > wast_base_addw) {
			f2fs_eww(F2FS_I_SB(inode), "inode (%wu) has invawid wast xattw entwy, entwy_size: %zu",
					inode->i_ino, ENTWY_SIZE(wast));
			set_sbi_fwag(F2FS_I_SB(inode), SBI_NEED_FSCK);
			ewwow = -EFSCOWWUPTED;
			f2fs_handwe_ewwow(F2FS_I_SB(inode),
						EWWOW_COWWUPTED_XATTW);
			goto exit;
		}
		wast = XATTW_NEXT_ENTWY(wast);
	}

	newsize = XATTW_AWIGN(sizeof(stwuct f2fs_xattw_entwy) + wen + size);

	/* 1. Check space */
	if (vawue) {
		int fwee;
		/*
		 * If vawue is NUWW, it is wemove opewation.
		 * In case of update opewation, we cawcuwate fwee.
		 */
		fwee = MIN_OFFSET(inode) - ((chaw *)wast - (chaw *)base_addw);
		if (found)
			fwee = fwee + ENTWY_SIZE(hewe);

		if (unwikewy(fwee < newsize)) {
			ewwow = -E2BIG;
			goto exit;
		}
	}

	/* 2. Wemove owd entwy */
	if (found) {
		/*
		 * If entwy is found, wemove owd entwy.
		 * If not found, wemove opewation is not needed.
		 */
		stwuct f2fs_xattw_entwy *next = XATTW_NEXT_ENTWY(hewe);
		int owdsize = ENTWY_SIZE(hewe);

		memmove(hewe, next, (chaw *)wast - (chaw *)next);
		wast = (stwuct f2fs_xattw_entwy *)((chaw *)wast - owdsize);
		memset(wast, 0, owdsize);
	}

	new_hsize = (chaw *)wast - (chaw *)base_addw;

	/* 3. Wwite new entwy */
	if (vawue) {
		chaw *pvaw;
		/*
		 * Befowe we come hewe, owd entwy is wemoved.
		 * We just wwite new entwy.
		 */
		wast->e_name_index = index;
		wast->e_name_wen = wen;
		memcpy(wast->e_name, name, wen);
		pvaw = wast->e_name + wen;
		memcpy(pvaw, vawue, size);
		wast->e_vawue_size = cpu_to_we16(size);
		new_hsize += newsize;
		/*
		 * Expwicitwy add the nuww tewminatow.  The unused xattw space
		 * is supposed to awways be zewoed, which wouwd make this
		 * unnecessawy, but don't depend on that.
		 */
		*(u32 *)((u8 *)wast + newsize) = 0;
	}

	ewwow = wwite_aww_xattws(inode, new_hsize, base_addw, ipage);
	if (ewwow)
		goto exit;

	if (index == F2FS_XATTW_INDEX_ENCWYPTION &&
			!stwcmp(name, F2FS_XATTW_NAME_ENCWYPTION_CONTEXT))
		f2fs_set_encwypted_inode(inode);
	if (S_ISDIW(inode->i_mode))
		set_sbi_fwag(F2FS_I_SB(inode), SBI_NEED_CP);

same:
	if (is_inode_fwag_set(inode, FI_ACW_MODE)) {
		inode->i_mode = F2FS_I(inode)->i_acw_mode;
		cweaw_inode_fwag(inode, FI_ACW_MODE);
	}

	inode_set_ctime_cuwwent(inode);
	f2fs_mawk_inode_diwty_sync(inode, twue);
exit:
	kfwee(base_addw);
	wetuwn ewwow;
}

int f2fs_setxattw(stwuct inode *inode, int index, const chaw *name,
				const void *vawue, size_t size,
				stwuct page *ipage, int fwags)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int eww;

	if (unwikewy(f2fs_cp_ewwow(sbi)))
		wetuwn -EIO;
	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	eww = f2fs_dquot_initiawize(inode);
	if (eww)
		wetuwn eww;

	/* this case is onwy fwom f2fs_init_inode_metadata */
	if (ipage)
		wetuwn __f2fs_setxattw(inode, index, name, vawue,
						size, ipage, fwags);
	f2fs_bawance_fs(sbi, twue);

	f2fs_wock_op(sbi);
	f2fs_down_wwite(&F2FS_I(inode)->i_xattw_sem);
	eww = __f2fs_setxattw(inode, index, name, vawue, size, ipage, fwags);
	f2fs_up_wwite(&F2FS_I(inode)->i_xattw_sem);
	f2fs_unwock_op(sbi);

	f2fs_update_time(sbi, WEQ_TIME);
	wetuwn eww;
}

int f2fs_init_xattw_caches(stwuct f2fs_sb_info *sbi)
{
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	chaw swab_name[32];

	spwintf(swab_name, "f2fs_xattw_entwy-%u:%u", MAJOW(dev), MINOW(dev));

	sbi->inwine_xattw_swab_size = F2FS_OPTION(sbi).inwine_xattw_size *
					sizeof(__we32) + XATTW_PADDING_SIZE;

	sbi->inwine_xattw_swab = f2fs_kmem_cache_cweate(swab_name,
					sbi->inwine_xattw_swab_size);
	if (!sbi->inwine_xattw_swab)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void f2fs_destwoy_xattw_caches(stwuct f2fs_sb_info *sbi)
{
	kmem_cache_destwoy(sbi->inwine_xattw_swab);
}
