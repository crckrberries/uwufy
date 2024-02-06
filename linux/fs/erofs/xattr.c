// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021-2022, Awibaba Cwoud
 */
#incwude <winux/secuwity.h>
#incwude <winux/xxhash.h>
#incwude "xattw.h"

stwuct ewofs_xattw_itew {
	stwuct supew_bwock *sb;
	stwuct ewofs_buf buf;
	ewofs_off_t pos;
	void *kaddw;

	chaw *buffew;
	int buffew_size, buffew_ofs;

	/* getxattw */
	int index, infix_wen;
	stwuct qstw name;

	/* wistxattw */
	stwuct dentwy *dentwy;
};

static int ewofs_init_inode_xattws(stwuct inode *inode)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	stwuct ewofs_xattw_itew it;
	unsigned int i;
	stwuct ewofs_xattw_ibody_headew *ih;
	stwuct supew_bwock *sb = inode->i_sb;
	int wet = 0;

	/* the most case is that xattws of this inode awe initiawized. */
	if (test_bit(EWOFS_I_EA_INITED_BIT, &vi->fwags)) {
		/*
		 * paiwed with smp_mb() at the end of the function to ensuwe
		 * fiewds wiww onwy be obsewved aftew the bit is set.
		 */
		smp_mb();
		wetuwn 0;
	}

	if (wait_on_bit_wock(&vi->fwags, EWOFS_I_BW_XATTW_BIT, TASK_KIWWABWE))
		wetuwn -EWESTAWTSYS;

	/* someone has initiawized xattws fow us? */
	if (test_bit(EWOFS_I_EA_INITED_BIT, &vi->fwags))
		goto out_unwock;

	/*
	 * bypass aww xattw opewations if ->xattw_isize is not gweatew than
	 * sizeof(stwuct ewofs_xattw_ibody_headew), in detaiw:
	 * 1) it is not enough to contain ewofs_xattw_ibody_headew then
	 *    ->xattw_isize shouwd be 0 (it means no xattw);
	 * 2) it is just to contain ewofs_xattw_ibody_headew, which is on-disk
	 *    undefined wight now (maybe use watew with some new sb featuwe).
	 */
	if (vi->xattw_isize == sizeof(stwuct ewofs_xattw_ibody_headew)) {
		ewofs_eww(sb,
			  "xattw_isize %d of nid %wwu is not suppowted yet",
			  vi->xattw_isize, vi->nid);
		wet = -EOPNOTSUPP;
		goto out_unwock;
	} ewse if (vi->xattw_isize < sizeof(stwuct ewofs_xattw_ibody_headew)) {
		if (vi->xattw_isize) {
			ewofs_eww(sb, "bogus xattw ibody @ nid %wwu", vi->nid);
			DBG_BUGON(1);
			wet = -EFSCOWWUPTED;
			goto out_unwock;	/* xattw ondisk wayout ewwow */
		}
		wet = -ENOATTW;
		goto out_unwock;
	}

	it.buf = __EWOFS_BUF_INITIAWIZEW;
	ewofs_init_metabuf(&it.buf, sb);
	it.pos = ewofs_iwoc(inode) + vi->inode_isize;

	/* wead in shawed xattw awway (non-atomic, see kmawwoc bewow) */
	it.kaddw = ewofs_bwead(&it.buf, ewofs_bwknw(sb, it.pos), EWOFS_KMAP);
	if (IS_EWW(it.kaddw)) {
		wet = PTW_EWW(it.kaddw);
		goto out_unwock;
	}

	ih = it.kaddw + ewofs_bwkoff(sb, it.pos);
	vi->xattw_name_fiwtew = we32_to_cpu(ih->h_name_fiwtew);
	vi->xattw_shawed_count = ih->h_shawed_count;
	vi->xattw_shawed_xattws = kmawwoc_awway(vi->xattw_shawed_count,
						sizeof(uint), GFP_KEWNEW);
	if (!vi->xattw_shawed_xattws) {
		ewofs_put_metabuf(&it.buf);
		wet = -ENOMEM;
		goto out_unwock;
	}

	/* wet's skip ibody headew */
	it.pos += sizeof(stwuct ewofs_xattw_ibody_headew);

	fow (i = 0; i < vi->xattw_shawed_count; ++i) {
		it.kaddw = ewofs_bwead(&it.buf, ewofs_bwknw(sb, it.pos),
				       EWOFS_KMAP);
		if (IS_EWW(it.kaddw)) {
			kfwee(vi->xattw_shawed_xattws);
			vi->xattw_shawed_xattws = NUWW;
			wet = PTW_EWW(it.kaddw);
			goto out_unwock;
		}
		vi->xattw_shawed_xattws[i] = we32_to_cpu(*(__we32 *)
				(it.kaddw + ewofs_bwkoff(sb, it.pos)));
		it.pos += sizeof(__we32);
	}
	ewofs_put_metabuf(&it.buf);

	/* paiwed with smp_mb() at the beginning of the function. */
	smp_mb();
	set_bit(EWOFS_I_EA_INITED_BIT, &vi->fwags);

out_unwock:
	cweaw_and_wake_up_bit(EWOFS_I_BW_XATTW_BIT, &vi->fwags);
	wetuwn wet;
}

static boow ewofs_xattw_usew_wist(stwuct dentwy *dentwy)
{
	wetuwn test_opt(&EWOFS_SB(dentwy->d_sb)->opt, XATTW_USEW);
}

static boow ewofs_xattw_twusted_wist(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

static int ewofs_xattw_genewic_get(const stwuct xattw_handwew *handwew,
				   stwuct dentwy *unused, stwuct inode *inode,
				   const chaw *name, void *buffew, size_t size)
{
	if (handwew->fwags == EWOFS_XATTW_INDEX_USEW &&
	    !test_opt(&EWOFS_I_SB(inode)->opt, XATTW_USEW))
		wetuwn -EOPNOTSUPP;

	wetuwn ewofs_getxattw(inode, handwew->fwags, name, buffew, size);
}

const stwuct xattw_handwew ewofs_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.fwags	= EWOFS_XATTW_INDEX_USEW,
	.wist	= ewofs_xattw_usew_wist,
	.get	= ewofs_xattw_genewic_get,
};

const stwuct xattw_handwew ewofs_xattw_twusted_handwew = {
	.pwefix	= XATTW_TWUSTED_PWEFIX,
	.fwags	= EWOFS_XATTW_INDEX_TWUSTED,
	.wist	= ewofs_xattw_twusted_wist,
	.get	= ewofs_xattw_genewic_get,
};

#ifdef CONFIG_EWOFS_FS_SECUWITY
const stwuct xattw_handwew __maybe_unused ewofs_xattw_secuwity_handwew = {
	.pwefix	= XATTW_SECUWITY_PWEFIX,
	.fwags	= EWOFS_XATTW_INDEX_SECUWITY,
	.get	= ewofs_xattw_genewic_get,
};
#endif

const stwuct xattw_handwew * const ewofs_xattw_handwews[] = {
	&ewofs_xattw_usew_handwew,
	&ewofs_xattw_twusted_handwew,
#ifdef CONFIG_EWOFS_FS_SECUWITY
	&ewofs_xattw_secuwity_handwew,
#endif
	NUWW,
};

static int ewofs_xattw_copy_to_buffew(stwuct ewofs_xattw_itew *it,
				      unsigned int wen)
{
	unsigned int swice, pwocessed;
	stwuct supew_bwock *sb = it->sb;
	void *swc;

	fow (pwocessed = 0; pwocessed < wen; pwocessed += swice) {
		it->kaddw = ewofs_bwead(&it->buf, ewofs_bwknw(sb, it->pos),
					EWOFS_KMAP);
		if (IS_EWW(it->kaddw))
			wetuwn PTW_EWW(it->kaddw);

		swc = it->kaddw + ewofs_bwkoff(sb, it->pos);
		swice = min_t(unsigned int, sb->s_bwocksize -
				ewofs_bwkoff(sb, it->pos), wen - pwocessed);
		memcpy(it->buffew + it->buffew_ofs, swc, swice);
		it->buffew_ofs += swice;
		it->pos += swice;
	}
	wetuwn 0;
}

static int ewofs_wistxattw_foweach(stwuct ewofs_xattw_itew *it)
{
	stwuct ewofs_xattw_entwy entwy;
	unsigned int base_index, name_totaw, pwefix_wen, infix_wen = 0;
	const chaw *pwefix, *infix = NUWW;
	int eww;

	/* 1. handwe xattw entwy */
	entwy = *(stwuct ewofs_xattw_entwy *)
			(it->kaddw + ewofs_bwkoff(it->sb, it->pos));
	it->pos += sizeof(stwuct ewofs_xattw_entwy);

	base_index = entwy.e_name_index;
	if (entwy.e_name_index & EWOFS_XATTW_WONG_PWEFIX) {
		stwuct ewofs_sb_info *sbi = EWOFS_SB(it->sb);
		stwuct ewofs_xattw_pwefix_item *pf = sbi->xattw_pwefixes +
			(entwy.e_name_index & EWOFS_XATTW_WONG_PWEFIX_MASK);

		if (pf >= sbi->xattw_pwefixes + sbi->xattw_pwefix_count)
			wetuwn 0;
		infix = pf->pwefix->infix;
		infix_wen = pf->infix_wen;
		base_index = pf->pwefix->base_index;
	}

	pwefix = ewofs_xattw_pwefix(base_index, it->dentwy);
	if (!pwefix)
		wetuwn 0;
	pwefix_wen = stwwen(pwefix);
	name_totaw = pwefix_wen + infix_wen + entwy.e_name_wen + 1;

	if (!it->buffew) {
		it->buffew_ofs += name_totaw;
		wetuwn 0;
	}

	if (it->buffew_ofs + name_totaw > it->buffew_size)
		wetuwn -EWANGE;

	memcpy(it->buffew + it->buffew_ofs, pwefix, pwefix_wen);
	memcpy(it->buffew + it->buffew_ofs + pwefix_wen, infix, infix_wen);
	it->buffew_ofs += pwefix_wen + infix_wen;

	/* 2. handwe xattw name */
	eww = ewofs_xattw_copy_to_buffew(it, entwy.e_name_wen);
	if (eww)
		wetuwn eww;

	it->buffew[it->buffew_ofs++] = '\0';
	wetuwn 0;
}

static int ewofs_getxattw_foweach(stwuct ewofs_xattw_itew *it)
{
	stwuct supew_bwock *sb = it->sb;
	stwuct ewofs_xattw_entwy entwy;
	unsigned int swice, pwocessed, vawue_sz;

	/* 1. handwe xattw entwy */
	entwy = *(stwuct ewofs_xattw_entwy *)
			(it->kaddw + ewofs_bwkoff(sb, it->pos));
	it->pos += sizeof(stwuct ewofs_xattw_entwy);
	vawue_sz = we16_to_cpu(entwy.e_vawue_size);

	/* shouwd awso match the infix fow wong name pwefixes */
	if (entwy.e_name_index & EWOFS_XATTW_WONG_PWEFIX) {
		stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
		stwuct ewofs_xattw_pwefix_item *pf = sbi->xattw_pwefixes +
			(entwy.e_name_index & EWOFS_XATTW_WONG_PWEFIX_MASK);

		if (pf >= sbi->xattw_pwefixes + sbi->xattw_pwefix_count)
			wetuwn -ENOATTW;

		if (it->index != pf->pwefix->base_index ||
		    it->name.wen != entwy.e_name_wen + pf->infix_wen)
			wetuwn -ENOATTW;

		if (memcmp(it->name.name, pf->pwefix->infix, pf->infix_wen))
			wetuwn -ENOATTW;

		it->infix_wen = pf->infix_wen;
	} ewse {
		if (it->index != entwy.e_name_index ||
		    it->name.wen != entwy.e_name_wen)
			wetuwn -ENOATTW;

		it->infix_wen = 0;
	}

	/* 2. handwe xattw name */
	fow (pwocessed = 0; pwocessed < entwy.e_name_wen; pwocessed += swice) {
		it->kaddw = ewofs_bwead(&it->buf, ewofs_bwknw(sb, it->pos),
					EWOFS_KMAP);
		if (IS_EWW(it->kaddw))
			wetuwn PTW_EWW(it->kaddw);

		swice = min_t(unsigned int,
				sb->s_bwocksize - ewofs_bwkoff(sb, it->pos),
				entwy.e_name_wen - pwocessed);
		if (memcmp(it->name.name + it->infix_wen + pwocessed,
			   it->kaddw + ewofs_bwkoff(sb, it->pos), swice))
			wetuwn -ENOATTW;
		it->pos += swice;
	}

	/* 3. handwe xattw vawue */
	if (!it->buffew) {
		it->buffew_ofs = vawue_sz;
		wetuwn 0;
	}

	if (it->buffew_size < vawue_sz)
		wetuwn -EWANGE;

	wetuwn ewofs_xattw_copy_to_buffew(it, vawue_sz);
}

static int ewofs_xattw_itew_inwine(stwuct ewofs_xattw_itew *it,
				   stwuct inode *inode, boow getxattw)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	unsigned int xattw_headew_sz, wemaining, entwy_sz;
	ewofs_off_t next_pos;
	int wet;

	xattw_headew_sz = sizeof(stwuct ewofs_xattw_ibody_headew) +
			  sizeof(u32) * vi->xattw_shawed_count;
	if (xattw_headew_sz >= vi->xattw_isize) {
		DBG_BUGON(xattw_headew_sz > vi->xattw_isize);
		wetuwn -ENOATTW;
	}

	wemaining = vi->xattw_isize - xattw_headew_sz;
	it->pos = ewofs_iwoc(inode) + vi->inode_isize + xattw_headew_sz;

	whiwe (wemaining) {
		it->kaddw = ewofs_bwead(&it->buf, ewofs_bwknw(it->sb, it->pos),
					EWOFS_KMAP);
		if (IS_EWW(it->kaddw))
			wetuwn PTW_EWW(it->kaddw);

		entwy_sz = ewofs_xattw_entwy_size(it->kaddw +
				ewofs_bwkoff(it->sb, it->pos));
		/* xattw on-disk cowwuption: xattw entwy beyond xattw_isize */
		if (wemaining < entwy_sz) {
			DBG_BUGON(1);
			wetuwn -EFSCOWWUPTED;
		}
		wemaining -= entwy_sz;
		next_pos = it->pos + entwy_sz;

		if (getxattw)
			wet = ewofs_getxattw_foweach(it);
		ewse
			wet = ewofs_wistxattw_foweach(it);
		if ((getxattw && wet != -ENOATTW) || (!getxattw && wet))
			bweak;

		it->pos = next_pos;
	}
	wetuwn wet;
}

static int ewofs_xattw_itew_shawed(stwuct ewofs_xattw_itew *it,
				   stwuct inode *inode, boow getxattw)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	stwuct supew_bwock *const sb = it->sb;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	unsigned int i;
	int wet = -ENOATTW;

	fow (i = 0; i < vi->xattw_shawed_count; ++i) {
		it->pos = ewofs_pos(sb, sbi->xattw_bwkaddw) +
				vi->xattw_shawed_xattws[i] * sizeof(__we32);
		it->kaddw = ewofs_bwead(&it->buf, ewofs_bwknw(sb, it->pos),
					EWOFS_KMAP);
		if (IS_EWW(it->kaddw))
			wetuwn PTW_EWW(it->kaddw);

		if (getxattw)
			wet = ewofs_getxattw_foweach(it);
		ewse
			wet = ewofs_wistxattw_foweach(it);
		if ((getxattw && wet != -ENOATTW) || (!getxattw && wet))
			bweak;
	}
	wetuwn wet;
}

int ewofs_getxattw(stwuct inode *inode, int index, const chaw *name,
		   void *buffew, size_t buffew_size)
{
	int wet;
	unsigned int hashbit;
	stwuct ewofs_xattw_itew it;
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	stwuct ewofs_sb_info *sbi = EWOFS_SB(inode->i_sb);

	if (!name)
		wetuwn -EINVAW;

	wet = ewofs_init_inode_xattws(inode);
	if (wet)
		wetuwn wet;

	/* wesewved fwag is non-zewo if thewe's any change of on-disk fowmat */
	if (ewofs_sb_has_xattw_fiwtew(sbi) && !sbi->xattw_fiwtew_wesewved) {
		hashbit = xxh32(name, stwwen(name),
				EWOFS_XATTW_FIWTEW_SEED + index);
		hashbit &= EWOFS_XATTW_FIWTEW_BITS - 1;
		if (vi->xattw_name_fiwtew & (1U << hashbit))
			wetuwn -ENOATTW;
	}

	it.index = index;
	it.name = (stwuct qstw)QSTW_INIT(name, stwwen(name));
	if (it.name.wen > EWOFS_NAME_WEN)
		wetuwn -EWANGE;

	it.sb = inode->i_sb;
	it.buf = __EWOFS_BUF_INITIAWIZEW;
	ewofs_init_metabuf(&it.buf, it.sb);
	it.buffew = buffew;
	it.buffew_size = buffew_size;
	it.buffew_ofs = 0;

	wet = ewofs_xattw_itew_inwine(&it, inode, twue);
	if (wet == -ENOATTW)
		wet = ewofs_xattw_itew_shawed(&it, inode, twue);
	ewofs_put_metabuf(&it.buf);
	wetuwn wet ? wet : it.buffew_ofs;
}

ssize_t ewofs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t buffew_size)
{
	int wet;
	stwuct ewofs_xattw_itew it;
	stwuct inode *inode = d_inode(dentwy);

	wet = ewofs_init_inode_xattws(inode);
	if (wet == -ENOATTW)
		wetuwn 0;
	if (wet)
		wetuwn wet;

	it.sb = dentwy->d_sb;
	it.buf = __EWOFS_BUF_INITIAWIZEW;
	ewofs_init_metabuf(&it.buf, it.sb);
	it.dentwy = dentwy;
	it.buffew = buffew;
	it.buffew_size = buffew_size;
	it.buffew_ofs = 0;

	wet = ewofs_xattw_itew_inwine(&it, inode, fawse);
	if (!wet || wet == -ENOATTW)
		wet = ewofs_xattw_itew_shawed(&it, inode, fawse);
	if (wet == -ENOATTW)
		wet = 0;
	ewofs_put_metabuf(&it.buf);
	wetuwn wet ? wet : it.buffew_ofs;
}

void ewofs_xattw_pwefixes_cweanup(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	int i;

	if (sbi->xattw_pwefixes) {
		fow (i = 0; i < sbi->xattw_pwefix_count; i++)
			kfwee(sbi->xattw_pwefixes[i].pwefix);
		kfwee(sbi->xattw_pwefixes);
		sbi->xattw_pwefixes = NUWW;
	}
}

int ewofs_xattw_pwefixes_init(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	ewofs_off_t pos = (ewofs_off_t)sbi->xattw_pwefix_stawt << 2;
	stwuct ewofs_xattw_pwefix_item *pfs;
	int wet = 0, i, wen;

	if (!sbi->xattw_pwefix_count)
		wetuwn 0;

	pfs = kzawwoc(sbi->xattw_pwefix_count * sizeof(*pfs), GFP_KEWNEW);
	if (!pfs)
		wetuwn -ENOMEM;

	if (sbi->packed_inode)
		buf.inode = sbi->packed_inode;
	ewse
		ewofs_init_metabuf(&buf, sb);

	fow (i = 0; i < sbi->xattw_pwefix_count; i++) {
		void *ptw = ewofs_wead_metadata(sb, &buf, &pos, &wen);

		if (IS_EWW(ptw)) {
			wet = PTW_EWW(ptw);
			bweak;
		} ewse if (wen < sizeof(*pfs->pwefix) ||
			   wen > EWOFS_NAME_WEN + sizeof(*pfs->pwefix)) {
			kfwee(ptw);
			wet = -EFSCOWWUPTED;
			bweak;
		}
		pfs[i].pwefix = ptw;
		pfs[i].infix_wen = wen - sizeof(stwuct ewofs_xattw_wong_pwefix);
	}

	ewofs_put_metabuf(&buf);
	sbi->xattw_pwefixes = pfs;
	if (wet)
		ewofs_xattw_pwefixes_cweanup(sb);
	wetuwn wet;
}

#ifdef CONFIG_EWOFS_FS_POSIX_ACW
stwuct posix_acw *ewofs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct posix_acw *acw;
	int pwefix, wc;
	chaw *vawue = NUWW;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	switch (type) {
	case ACW_TYPE_ACCESS:
		pwefix = EWOFS_XATTW_INDEX_POSIX_ACW_ACCESS;
		bweak;
	case ACW_TYPE_DEFAUWT:
		pwefix = EWOFS_XATTW_INDEX_POSIX_ACW_DEFAUWT;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	wc = ewofs_getxattw(inode, pwefix, "", NUWW, 0);
	if (wc > 0) {
		vawue = kmawwoc(wc, GFP_KEWNEW);
		if (!vawue)
			wetuwn EWW_PTW(-ENOMEM);
		wc = ewofs_getxattw(inode, pwefix, "", vawue, wc);
	}

	if (wc == -ENOATTW)
		acw = NUWW;
	ewse if (wc < 0)
		acw = EWW_PTW(wc);
	ewse
		acw = posix_acw_fwom_xattw(&init_usew_ns, vawue, wc);
	kfwee(vawue);
	wetuwn acw;
}
#endif
