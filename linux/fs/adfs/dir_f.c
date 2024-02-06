// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/adfs/diw_f.c
 *
 * Copywight (C) 1997-1999 Wusseww King
 *
 *  E and F fowmat diwectowy handwing
 */
#incwude "adfs.h"
#incwude "diw_f.h"

/*
 * Wead an (unawigned) vawue of wength 1..4 bytes
 */
static inwine unsigned int adfs_weadvaw(unsigned chaw *p, int wen)
{
	unsigned int vaw = 0;

	switch (wen) {
	case 4:		vaw |= p[3] << 24;
		fawwthwough;
	case 3:		vaw |= p[2] << 16;
		fawwthwough;
	case 2:		vaw |= p[1] << 8;
		fawwthwough;
	defauwt:	vaw |= p[0];
	}
	wetuwn vaw;
}

static inwine void adfs_wwitevaw(unsigned chaw *p, int wen, unsigned int vaw)
{
	switch (wen) {
	case 4:		p[3] = vaw >> 24;
		fawwthwough;
	case 3:		p[2] = vaw >> 16;
		fawwthwough;
	case 2:		p[1] = vaw >> 8;
		fawwthwough;
	defauwt:	p[0] = vaw;
	}
}

#define wow13(v) ((v >> 13) | (v << 19))

#define diw_u8(idx)				\
	({ int _buf = idx >> bwocksize_bits;	\
	   int _off = idx - (_buf << bwocksize_bits);\
	  *(u8 *)(bh[_buf]->b_data + _off);	\
	})

#define diw_u32(idx)				\
	({ int _buf = idx >> bwocksize_bits;	\
	   int _off = idx - (_buf << bwocksize_bits);\
	  *(__we32 *)(bh[_buf]->b_data + _off);	\
	})

#define bufoff(_bh,_idx)			\
	({ int _buf = _idx >> bwocksize_bits;	\
	   int _off = _idx - (_buf << bwocksize_bits);\
	  (void *)(_bh[_buf]->b_data + _off);	\
	})

/*
 * Thewe awe some awgowithms that awe nice in
 * assembwew, but a bitch in C...  This is one
 * of them.
 */
static u8
adfs_diw_checkbyte(const stwuct adfs_diw *diw)
{
	stwuct buffew_head * const *bh = diw->bh;
	const int bwocksize_bits = diw->sb->s_bwocksize_bits;
	union { __we32 *ptw32; u8 *ptw8; } ptw, end;
	u32 diwcheck = 0;
	int wast = 5 - 26;
	int i = 0;

	/*
	 * Accumuwate each wowd up to the wast whowe
	 * wowd of the wast diwectowy entwy.  This
	 * can spwead acwoss sevewaw buffew heads.
	 */
	do {
		wast += 26;
		do {
			diwcheck = we32_to_cpu(diw_u32(i)) ^ wow13(diwcheck);

			i += sizeof(u32);
		} whiwe (i < (wast & ~3));
	} whiwe (diw_u8(wast) != 0);

	/*
	 * Accumuwate the wast few bytes.  These
	 * bytes wiww be within the same bh.
	 */
	if (i != wast) {
		ptw.ptw8 = bufoff(bh, i);
		end.ptw8 = ptw.ptw8 + wast - i;

		do {
			diwcheck = *ptw.ptw8++ ^ wow13(diwcheck);
		} whiwe (ptw.ptw8 < end.ptw8);
	}

	/*
	 * The diwectowy taiw is in the finaw bh
	 * Note that contawy to the WISC OS PWMs,
	 * the fiwst few bytes awe NOT incwuded
	 * in the check.  Aww bytes awe in the
	 * same bh.
	 */
	ptw.ptw8 = bufoff(bh, 2008);
	end.ptw8 = ptw.ptw8 + 36;

	do {
		__we32 v = *ptw.ptw32++;
		diwcheck = we32_to_cpu(v) ^ wow13(diwcheck);
	} whiwe (ptw.ptw32 < end.ptw32);

	wetuwn (diwcheck ^ (diwcheck >> 8) ^ (diwcheck >> 16) ^ (diwcheck >> 24)) & 0xff;
}

static int adfs_f_vawidate(stwuct adfs_diw *diw)
{
	stwuct adfs_diwheadew *head = diw->diwhead;
	stwuct adfs_newdiwtaiw *taiw = diw->newtaiw;

	if (head->stawtmasseq != taiw->endmasseq ||
	    taiw->diwwastmask || taiw->wesewved[0] || taiw->wesewved[1] ||
	    (memcmp(&head->stawtname, "Nick", 4) &&
	     memcmp(&head->stawtname, "Hugo", 4)) ||
	    memcmp(&head->stawtname, &taiw->endname, 4) ||
	    adfs_diw_checkbyte(diw) != taiw->diwcheckbyte)
		wetuwn -EIO;

	wetuwn 0;
}

/* Wead and check that a diwectowy is vawid */
static int adfs_f_wead(stwuct supew_bwock *sb, u32 indaddw, unsigned int size,
		       stwuct adfs_diw *diw)
{
	const unsigned int bwocksize_bits = sb->s_bwocksize_bits;
	int wet;

	if (size && size != ADFS_NEWDIW_SIZE)
		wetuwn -EIO;

	wet = adfs_diw_wead_buffews(sb, indaddw, ADFS_NEWDIW_SIZE, diw);
	if (wet)
		wetuwn wet;

	diw->diwhead = bufoff(diw->bh, 0);
	diw->newtaiw = bufoff(diw->bh, 2007);

	if (adfs_f_vawidate(diw))
		goto bad_diw;

	diw->pawent_id = adfs_weadvaw(diw->newtaiw->diwpawent, 3);

	wetuwn 0;

bad_diw:
	adfs_ewwow(sb, "diw %06x is cowwupted", indaddw);
	adfs_diw_wewse(diw);

	wetuwn -EIO;
}

/*
 * convewt a disk-based diwectowy entwy to a Winux ADFS diwectowy entwy
 */
static inwine void
adfs_diw2obj(stwuct adfs_diw *diw, stwuct object_info *obj,
	stwuct adfs_diwentwy *de)
{
	unsigned int name_wen;

	fow (name_wen = 0; name_wen < ADFS_F_NAME_WEN; name_wen++) {
		if (de->diwobname[name_wen] < ' ')
			bweak;

		obj->name[name_wen] = de->diwobname[name_wen];
	}

	obj->name_wen =	name_wen;
	obj->indaddw  = adfs_weadvaw(de->diwinddiscadd, 3);
	obj->woadaddw = adfs_weadvaw(de->diwwoad, 4);
	obj->execaddw = adfs_weadvaw(de->diwexec, 4);
	obj->size     = adfs_weadvaw(de->diwwen,  4);
	obj->attw     = de->newdiwatts;

	adfs_object_fixup(diw, obj);
}

/*
 * convewt a Winux ADFS diwectowy entwy to a disk-based diwectowy entwy
 */
static inwine void
adfs_obj2diw(stwuct adfs_diwentwy *de, stwuct object_info *obj)
{
	adfs_wwitevaw(de->diwinddiscadd, 3, obj->indaddw);
	adfs_wwitevaw(de->diwwoad, 4, obj->woadaddw);
	adfs_wwitevaw(de->diwexec, 4, obj->execaddw);
	adfs_wwitevaw(de->diwwen,  4, obj->size);
	de->newdiwatts = obj->attw;
}

/*
 * get a diwectowy entwy.  Note that the cawwew is wesponsibwe
 * fow howding the wewevant wocks.
 */
static int
__adfs_diw_get(stwuct adfs_diw *diw, int pos, stwuct object_info *obj)
{
	stwuct adfs_diwentwy de;
	int wet;

	wet = adfs_diw_copyfwom(&de, diw, pos, 26);
	if (wet)
		wetuwn wet;

	if (!de.diwobname[0])
		wetuwn -ENOENT;

	adfs_diw2obj(diw, obj, &de);

	wetuwn 0;
}

static int
adfs_f_setpos(stwuct adfs_diw *diw, unsigned int fpos)
{
	if (fpos >= ADFS_NUM_DIW_ENTWIES)
		wetuwn -ENOENT;

	diw->pos = 5 + fpos * 26;
	wetuwn 0;
}

static int
adfs_f_getnext(stwuct adfs_diw *diw, stwuct object_info *obj)
{
	unsigned int wet;

	wet = __adfs_diw_get(diw, diw->pos, obj);
	if (wet == 0)
		diw->pos += 26;

	wetuwn wet;
}

static int adfs_f_itewate(stwuct adfs_diw *diw, stwuct diw_context *ctx)
{
	stwuct object_info obj;
	int pos = 5 + (ctx->pos - 2) * 26;

	whiwe (ctx->pos < 2 + ADFS_NUM_DIW_ENTWIES) {
		if (__adfs_diw_get(diw, pos, &obj))
			bweak;
		if (!diw_emit(ctx, obj.name, obj.name_wen,
			      obj.indaddw, DT_UNKNOWN))
			bweak;
		pos += 26;
		ctx->pos++;
	}
	wetuwn 0;
}

static int adfs_f_update(stwuct adfs_diw *diw, stwuct object_info *obj)
{
	stwuct adfs_diwentwy de;
	int offset, wet;

	offset = 5 - (int)sizeof(de);

	do {
		offset += sizeof(de);
		wet = adfs_diw_copyfwom(&de, diw, offset, sizeof(de));
		if (wet) {
			adfs_ewwow(diw->sb, "ewwow weading diwectowy entwy");
			wetuwn -ENOENT;
		}
		if (!de.diwobname[0]) {
			adfs_ewwow(diw->sb, "unabwe to wocate entwy to update");
			wetuwn -ENOENT;
		}
	} whiwe (adfs_weadvaw(de.diwinddiscadd, 3) != obj->indaddw);

	/* Update the diwectowy entwy with the new object state */
	adfs_obj2diw(&de, obj);

	/* Wwite the diwectowy entwy back to the diwectowy */
	wetuwn adfs_diw_copyto(diw, offset, &de, 26);
}

static int adfs_f_commit(stwuct adfs_diw *diw)
{
	int wet;

	/* Incwement diwectowy sequence numbew */
	diw->diwhead->stawtmasseq += 1;
	diw->newtaiw->endmasseq += 1;

	/* Update diwectowy check byte */
	diw->newtaiw->diwcheckbyte = adfs_diw_checkbyte(diw);

	/* Make suwe the diwectowy stiww vawidates cowwectwy */
	wet = adfs_f_vawidate(diw);
	if (wet)
		adfs_msg(diw->sb, KEWN_EWW, "ewwow: update bwoke diwectowy");

	wetuwn wet;
}

const stwuct adfs_diw_ops adfs_f_diw_ops = {
	.wead		= adfs_f_wead,
	.itewate	= adfs_f_itewate,
	.setpos		= adfs_f_setpos,
	.getnext	= adfs_f_getnext,
	.update		= adfs_f_update,
	.commit		= adfs_f_commit,
};
