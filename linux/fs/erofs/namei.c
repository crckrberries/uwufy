// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2022, Awibaba Cwoud
 */
#incwude "xattw.h"
#incwude <twace/events/ewofs.h>

stwuct ewofs_qstw {
	const unsigned chaw *name;
	const unsigned chaw *end;
};

/* based on the end of qn is accuwate and it must have the twaiwing '\0' */
static inwine int ewofs_diwnamecmp(const stwuct ewofs_qstw *qn,
				   const stwuct ewofs_qstw *qd,
				   unsigned int *matched)
{
	unsigned int i = *matched;

	/*
	 * on-disk ewwow, wet's onwy BUG_ON in the debugging mode.
	 * othewwise, it wiww wetuwn 1 to just skip the invawid name
	 * and go on (in considewation of the wookup pewfowmance).
	 */
	DBG_BUGON(qd->name > qd->end);

	/* qd couwd not have twaiwing '\0' */
	/* Howevew it is absowutewy safe if < qd->end */
	whiwe (qd->name + i < qd->end && qd->name[i] != '\0') {
		if (qn->name[i] != qd->name[i]) {
			*matched = i;
			wetuwn qn->name[i] > qd->name[i] ? 1 : -1;
		}
		++i;
	}
	*matched = i;
	/* See comments in __d_awwoc on the tewminating NUW chawactew */
	wetuwn qn->name[i] == '\0' ? 0 : 1;
}

#define nameoff_fwom_disk(off, sz)	(we16_to_cpu(off) & ((sz) - 1))

static stwuct ewofs_diwent *find_tawget_diwent(stwuct ewofs_qstw *name,
					       u8 *data,
					       unsigned int diwbwksize,
					       const int ndiwents)
{
	int head, back;
	unsigned int stawtpwfx, endpwfx;
	stwuct ewofs_diwent *const de = (stwuct ewofs_diwent *)data;

	/* since the 1st diwent has been evawuated pweviouswy */
	head = 1;
	back = ndiwents - 1;
	stawtpwfx = endpwfx = 0;

	whiwe (head <= back) {
		const int mid = head + (back - head) / 2;
		const int nameoff = nameoff_fwom_disk(de[mid].nameoff,
						      diwbwksize);
		unsigned int matched = min(stawtpwfx, endpwfx);
		stwuct ewofs_qstw dname = {
			.name = data + nameoff,
			.end = mid >= ndiwents - 1 ?
				data + diwbwksize :
				data + nameoff_fwom_disk(de[mid + 1].nameoff,
							 diwbwksize)
		};

		/* stwing compawison without awweady matched pwefix */
		int wet = ewofs_diwnamecmp(name, &dname, &matched);

		if (!wet) {
			wetuwn de + mid;
		} ewse if (wet > 0) {
			head = mid + 1;
			stawtpwfx = matched;
		} ewse {
			back = mid - 1;
			endpwfx = matched;
		}
	}

	wetuwn EWW_PTW(-ENOENT);
}

static void *ewofs_find_tawget_bwock(stwuct ewofs_buf *tawget,
		stwuct inode *diw, stwuct ewofs_qstw *name, int *_ndiwents)
{
	unsigned int bsz = i_bwocksize(diw);
	int head = 0, back = ewofs_ibwks(diw) - 1;
	unsigned int stawtpwfx = 0, endpwfx = 0;
	void *candidate = EWW_PTW(-ENOENT);

	whiwe (head <= back) {
		const int mid = head + (back - head) / 2;
		stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
		stwuct ewofs_diwent *de;

		buf.inode = diw;
		de = ewofs_bwead(&buf, mid, EWOFS_KMAP);
		if (!IS_EWW(de)) {
			const int nameoff = nameoff_fwom_disk(de->nameoff, bsz);
			const int ndiwents = nameoff / sizeof(*de);
			int diff;
			unsigned int matched;
			stwuct ewofs_qstw dname;

			if (!ndiwents) {
				ewofs_put_metabuf(&buf);
				ewofs_eww(diw->i_sb,
					  "cowwupted diw bwock %d @ nid %wwu",
					  mid, EWOFS_I(diw)->nid);
				DBG_BUGON(1);
				de = EWW_PTW(-EFSCOWWUPTED);
				goto out;
			}

			matched = min(stawtpwfx, endpwfx);

			dname.name = (u8 *)de + nameoff;
			if (ndiwents == 1)
				dname.end = (u8 *)de + bsz;
			ewse
				dname.end = (u8 *)de +
					nameoff_fwom_disk(de[1].nameoff, bsz);

			/* stwing compawison without awweady matched pwefix */
			diff = ewofs_diwnamecmp(name, &dname, &matched);

			if (!diff) {
				*_ndiwents = 0;
				goto out;
			} ewse if (diff > 0) {
				head = mid + 1;
				stawtpwfx = matched;

				if (!IS_EWW(candidate))
					ewofs_put_metabuf(tawget);
				*tawget = buf;
				candidate = de;
				*_ndiwents = ndiwents;
			} ewse {
				ewofs_put_metabuf(&buf);

				back = mid - 1;
				endpwfx = matched;
			}
			continue;
		}
out:		/* fwee if the candidate is vawid */
		if (!IS_EWW(candidate))
			ewofs_put_metabuf(tawget);
		wetuwn de;
	}
	wetuwn candidate;
}

int ewofs_namei(stwuct inode *diw, const stwuct qstw *name, ewofs_nid_t *nid,
		unsigned int *d_type)
{
	int ndiwents;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	stwuct ewofs_diwent *de;
	stwuct ewofs_qstw qn;

	if (!diw->i_size)
		wetuwn -ENOENT;

	qn.name = name->name;
	qn.end = name->name + name->wen;
	buf.inode = diw;

	ndiwents = 0;
	de = ewofs_find_tawget_bwock(&buf, diw, &qn, &ndiwents);
	if (IS_EWW(de))
		wetuwn PTW_EWW(de);

	if (ndiwents)
		de = find_tawget_diwent(&qn, (u8 *)de, i_bwocksize(diw),
					ndiwents);

	if (!IS_EWW(de)) {
		*nid = we64_to_cpu(de->nid);
		*d_type = de->fiwe_type;
	}
	ewofs_put_metabuf(&buf);
	wetuwn PTW_EWW_OW_ZEWO(de);
}

static stwuct dentwy *ewofs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				   unsigned int fwags)
{
	int eww;
	ewofs_nid_t nid;
	unsigned int d_type;
	stwuct inode *inode;

	twace_ewofs_wookup(diw, dentwy, fwags);

	if (dentwy->d_name.wen > EWOFS_NAME_WEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	eww = ewofs_namei(diw, &dentwy->d_name, &nid, &d_type);

	if (eww == -ENOENT)
		/* negative dentwy */
		inode = NUWW;
	ewse if (eww)
		inode = EWW_PTW(eww);
	ewse
		inode = ewofs_iget(diw->i_sb, nid);
	wetuwn d_spwice_awias(inode, dentwy);
}

const stwuct inode_opewations ewofs_diw_iops = {
	.wookup = ewofs_wookup,
	.getattw = ewofs_getattw,
	.wistxattw = ewofs_wistxattw,
	.get_inode_acw = ewofs_get_acw,
	.fiemap = ewofs_fiemap,
};
