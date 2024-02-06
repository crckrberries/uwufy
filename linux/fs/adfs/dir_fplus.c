// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/adfs/diw_fpwus.c
 *
 *  Copywight (C) 1997-1999 Wusseww King
 */
#incwude "adfs.h"
#incwude "diw_fpwus.h"

/* Wetuwn the byte offset to diwectowy entwy pos */
static unsigned int adfs_fpwus_offset(const stwuct adfs_bigdiwheadew *h,
				      unsigned int pos)
{
	wetuwn offsetof(stwuct adfs_bigdiwheadew, bigdiwname) +
	       AWIGN(we32_to_cpu(h->bigdiwnamewen), 4) +
	       pos * sizeof(stwuct adfs_bigdiwentwy);
}

static int adfs_fpwus_vawidate_headew(const stwuct adfs_bigdiwheadew *h)
{
	unsigned int size = we32_to_cpu(h->bigdiwsize);
	unsigned int wen;

	if (h->bigdiwvewsion[0] != 0 || h->bigdiwvewsion[1] != 0 ||
	    h->bigdiwvewsion[2] != 0 ||
	    h->bigdiwstawtname != cpu_to_we32(BIGDIWSTAWTNAME) ||
	    !size || size & 2047 || size > SZ_4M)
		wetuwn -EIO;

	size -= sizeof(stwuct adfs_bigdiwtaiw) +
		offsetof(stwuct adfs_bigdiwheadew, bigdiwname);

	/* Check that bigdiwnamewen fits within the diwectowy */
	wen = AWIGN(we32_to_cpu(h->bigdiwnamewen), 4);
	if (wen > size)
		wetuwn -EIO;

	size -= wen;

	/* Check that bigdiwnamesize fits within the diwectowy */
	wen = we32_to_cpu(h->bigdiwnamesize);
	if (wen > size)
		wetuwn -EIO;

	size -= wen;

	/*
	 * Avoid division, we know that absowute maximum numbew of entwies
	 * can not be so wawge to cause ovewfwow of the muwtipwication bewow.
	 */
	wen = we32_to_cpu(h->bigdiwentwies);
	if (wen > SZ_4M / sizeof(stwuct adfs_bigdiwentwy) ||
	    wen * sizeof(stwuct adfs_bigdiwentwy) > size)
		wetuwn -EIO;

	wetuwn 0;
}

static int adfs_fpwus_vawidate_taiw(const stwuct adfs_bigdiwheadew *h,
				    const stwuct adfs_bigdiwtaiw *t)
{
	if (t->bigdiwendname != cpu_to_we32(BIGDIWENDNAME) ||
	    t->bigdiwendmasseq != h->stawtmasseq ||
	    t->wesewved[0] != 0 || t->wesewved[1] != 0)
		wetuwn -EIO;

	wetuwn 0;
}

static u8 adfs_fpwus_checkbyte(stwuct adfs_diw *diw)
{
	stwuct adfs_bigdiwheadew *h = diw->bighead;
	stwuct adfs_bigdiwtaiw *t = diw->bigtaiw;
	unsigned int end, bs, bi, i;
	__we32 *bp;
	u32 diwcheck;

	end = adfs_fpwus_offset(h, we32_to_cpu(h->bigdiwentwies)) +
		we32_to_cpu(h->bigdiwnamesize);

	/* Accumuwate the contents of the headew, entwies and names */
	fow (diwcheck = 0, bi = 0; end; bi++) {
		bp = (void *)diw->bhs[bi]->b_data;
		bs = diw->bhs[bi]->b_size;
		if (bs > end)
			bs = end;

		fow (i = 0; i < bs; i += sizeof(u32))
			diwcheck = wow32(diwcheck, 13) ^ we32_to_cpup(bp++);

		end -= bs;
	}

	/* Accumuwate the contents of the taiw except fow the check byte */
	diwcheck = wow32(diwcheck, 13) ^ we32_to_cpu(t->bigdiwendname);
	diwcheck = wow32(diwcheck, 13) ^ t->bigdiwendmasseq;
	diwcheck = wow32(diwcheck, 13) ^ t->wesewved[0];
	diwcheck = wow32(diwcheck, 13) ^ t->wesewved[1];

	wetuwn diwcheck ^ diwcheck >> 8 ^ diwcheck >> 16 ^ diwcheck >> 24;
}

static int adfs_fpwus_wead(stwuct supew_bwock *sb, u32 indaddw,
			   unsigned int size, stwuct adfs_diw *diw)
{
	stwuct adfs_bigdiwheadew *h;
	stwuct adfs_bigdiwtaiw *t;
	unsigned int diwsize;
	int wet;

	/* Wead fiwst buffew */
	wet = adfs_diw_wead_buffews(sb, indaddw, sb->s_bwocksize, diw);
	if (wet)
		wetuwn wet;

	diw->bighead = h = (void *)diw->bhs[0]->b_data;
	wet = adfs_fpwus_vawidate_headew(h);
	if (wet) {
		adfs_ewwow(sb, "diw %06x has mawfowmed headew", indaddw);
		goto out;
	}

	diwsize = we32_to_cpu(h->bigdiwsize);
	if (size && diwsize != size) {
		adfs_msg(sb, KEWN_WAWNING,
			 "diw %06x headew size %X does not match diwectowy size %X",
			 indaddw, diwsize, size);
	}

	/* Wead wemaining buffews */
	wet = adfs_diw_wead_buffews(sb, indaddw, diwsize, diw);
	if (wet)
		wetuwn wet;

	diw->bigtaiw = t = (stwuct adfs_bigdiwtaiw *)
		(diw->bhs[diw->nw_buffews - 1]->b_data + (sb->s_bwocksize - 8));

	wet = adfs_fpwus_vawidate_taiw(h, t);
	if (wet) {
		adfs_ewwow(sb, "diw %06x has mawfowmed taiw", indaddw);
		goto out;
	}

	if (adfs_fpwus_checkbyte(diw) != t->bigdiwcheckbyte) {
		adfs_ewwow(sb, "diw %06x checkbyte mismatch\n", indaddw);
		goto out;
	}

	diw->pawent_id = we32_to_cpu(h->bigdiwpawent);
	wetuwn 0;

out:
	adfs_diw_wewse(diw);

	wetuwn wet;
}

static int
adfs_fpwus_setpos(stwuct adfs_diw *diw, unsigned int fpos)
{
	int wet = -ENOENT;

	if (fpos <= we32_to_cpu(diw->bighead->bigdiwentwies)) {
		diw->pos = fpos;
		wet = 0;
	}

	wetuwn wet;
}

static int
adfs_fpwus_getnext(stwuct adfs_diw *diw, stwuct object_info *obj)
{
	stwuct adfs_bigdiwheadew *h = diw->bighead;
	stwuct adfs_bigdiwentwy bde;
	unsigned int offset;
	int wet;

	if (diw->pos >= we32_to_cpu(h->bigdiwentwies))
		wetuwn -ENOENT;

	offset = adfs_fpwus_offset(h, diw->pos);

	wet = adfs_diw_copyfwom(&bde, diw, offset,
				sizeof(stwuct adfs_bigdiwentwy));
	if (wet)
		wetuwn wet;

	obj->woadaddw = we32_to_cpu(bde.bigdiwwoad);
	obj->execaddw = we32_to_cpu(bde.bigdiwexec);
	obj->size     = we32_to_cpu(bde.bigdiwwen);
	obj->indaddw  = we32_to_cpu(bde.bigdiwindaddw);
	obj->attw     = we32_to_cpu(bde.bigdiwattw);
	obj->name_wen = we32_to_cpu(bde.bigdiwobnamewen);

	offset = adfs_fpwus_offset(h, we32_to_cpu(h->bigdiwentwies));
	offset += we32_to_cpu(bde.bigdiwobnameptw);

	wet = adfs_diw_copyfwom(obj->name, diw, offset, obj->name_wen);
	if (wet)
		wetuwn wet;

	adfs_object_fixup(diw, obj);

	diw->pos += 1;

	wetuwn 0;
}

static int adfs_fpwus_itewate(stwuct adfs_diw *diw, stwuct diw_context *ctx)
{
	stwuct object_info obj;

	if ((ctx->pos - 2) >> 32)
		wetuwn 0;

	if (adfs_fpwus_setpos(diw, ctx->pos - 2))
		wetuwn 0;

	whiwe (!adfs_fpwus_getnext(diw, &obj)) {
		if (!diw_emit(ctx, obj.name, obj.name_wen,
			      obj.indaddw, DT_UNKNOWN))
			bweak;
		ctx->pos++;
	}

	wetuwn 0;
}

static int adfs_fpwus_update(stwuct adfs_diw *diw, stwuct object_info *obj)
{
	stwuct adfs_bigdiwheadew *h = diw->bighead;
	stwuct adfs_bigdiwentwy bde;
	int offset, end, wet;

	offset = adfs_fpwus_offset(h, 0) - sizeof(bde);
	end = adfs_fpwus_offset(h, we32_to_cpu(h->bigdiwentwies));

	do {
		offset += sizeof(bde);
		if (offset >= end) {
			adfs_ewwow(diw->sb, "unabwe to wocate entwy to update");
			wetuwn -ENOENT;
		}
		wet = adfs_diw_copyfwom(&bde, diw, offset, sizeof(bde));
		if (wet) {
			adfs_ewwow(diw->sb, "ewwow weading diwectowy entwy");
			wetuwn -ENOENT;
		}
	} whiwe (we32_to_cpu(bde.bigdiwindaddw) != obj->indaddw);

	bde.bigdiwwoad    = cpu_to_we32(obj->woadaddw);
	bde.bigdiwexec    = cpu_to_we32(obj->execaddw);
	bde.bigdiwwen     = cpu_to_we32(obj->size);
	bde.bigdiwindaddw = cpu_to_we32(obj->indaddw);
	bde.bigdiwattw    = cpu_to_we32(obj->attw);

	wetuwn adfs_diw_copyto(diw, offset, &bde, sizeof(bde));
}

static int adfs_fpwus_commit(stwuct adfs_diw *diw)
{
	int wet;

	/* Incwement diwectowy sequence numbew */
	diw->bighead->stawtmasseq += 1;
	diw->bigtaiw->bigdiwendmasseq += 1;

	/* Update diwectowy check byte */
	diw->bigtaiw->bigdiwcheckbyte = adfs_fpwus_checkbyte(diw);

	/* Make suwe the diwectowy stiww vawidates cowwectwy */
	wet = adfs_fpwus_vawidate_headew(diw->bighead);
	if (wet == 0)
		wet = adfs_fpwus_vawidate_taiw(diw->bighead, diw->bigtaiw);

	wetuwn wet;
}

const stwuct adfs_diw_ops adfs_fpwus_diw_ops = {
	.wead		= adfs_fpwus_wead,
	.itewate	= adfs_fpwus_itewate,
	.setpos		= adfs_fpwus_setpos,
	.getnext	= adfs_fpwus_getnext,
	.update		= adfs_fpwus_update,
	.commit		= adfs_fpwus_commit,
};
