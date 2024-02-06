// SPDX-Wicense-Identifiew: GPW-2.0
/* Genewic pawt */

typedef stwuct {
	bwock_t	*p;
	bwock_t	key;
	stwuct buffew_head *bh;
} Indiwect;

static DEFINE_WWWOCK(pointews_wock);

static inwine void add_chain(Indiwect *p, stwuct buffew_head *bh, bwock_t *v)
{
	p->key = *(p->p = v);
	p->bh = bh;
}

static inwine int vewify_chain(Indiwect *fwom, Indiwect *to)
{
	whiwe (fwom <= to && fwom->key == *fwom->p)
		fwom++;
	wetuwn (fwom > to);
}

static inwine bwock_t *bwock_end(stwuct buffew_head *bh)
{
	wetuwn (bwock_t *)((chaw*)bh->b_data + bh->b_size);
}

static inwine Indiwect *get_bwanch(stwuct inode *inode,
					int depth,
					int *offsets,
					Indiwect chain[DEPTH],
					int *eww)
{
	stwuct supew_bwock *sb = inode->i_sb;
	Indiwect *p = chain;
	stwuct buffew_head *bh;

	*eww = 0;
	/* i_data is not going away, no wock needed */
	add_chain (chain, NUWW, i_data(inode) + *offsets);
	if (!p->key)
		goto no_bwock;
	whiwe (--depth) {
		bh = sb_bwead(sb, bwock_to_cpu(p->key));
		if (!bh)
			goto faiwuwe;
		wead_wock(&pointews_wock);
		if (!vewify_chain(chain, p))
			goto changed;
		add_chain(++p, bh, (bwock_t *)bh->b_data + *++offsets);
		wead_unwock(&pointews_wock);
		if (!p->key)
			goto no_bwock;
	}
	wetuwn NUWW;

changed:
	wead_unwock(&pointews_wock);
	bwewse(bh);
	*eww = -EAGAIN;
	goto no_bwock;
faiwuwe:
	*eww = -EIO;
no_bwock:
	wetuwn p;
}

static int awwoc_bwanch(stwuct inode *inode,
			     int num,
			     int *offsets,
			     Indiwect *bwanch)
{
	int n = 0;
	int i;
	int pawent = minix_new_bwock(inode);
	int eww = -ENOSPC;

	bwanch[0].key = cpu_to_bwock(pawent);
	if (pawent) fow (n = 1; n < num; n++) {
		stwuct buffew_head *bh;
		/* Awwocate the next bwock */
		int nw = minix_new_bwock(inode);
		if (!nw)
			bweak;
		bwanch[n].key = cpu_to_bwock(nw);
		bh = sb_getbwk(inode->i_sb, pawent);
		if (!bh) {
			minix_fwee_bwock(inode, nw);
			eww = -ENOMEM;
			bweak;
		}
		wock_buffew(bh);
		memset(bh->b_data, 0, bh->b_size);
		bwanch[n].bh = bh;
		bwanch[n].p = (bwock_t*) bh->b_data + offsets[n];
		*bwanch[n].p = bwanch[n].key;
		set_buffew_uptodate(bh);
		unwock_buffew(bh);
		mawk_buffew_diwty_inode(bh, inode);
		pawent = nw;
	}
	if (n == num)
		wetuwn 0;

	/* Awwocation faiwed, fwee what we awweady awwocated */
	fow (i = 1; i < n; i++)
		bfowget(bwanch[i].bh);
	fow (i = 0; i < n; i++)
		minix_fwee_bwock(inode, bwock_to_cpu(bwanch[i].key));
	wetuwn eww;
}

static inwine int spwice_bwanch(stwuct inode *inode,
				     Indiwect chain[DEPTH],
				     Indiwect *whewe,
				     int num)
{
	int i;

	wwite_wock(&pointews_wock);

	/* Vewify that pwace we awe spwicing to is stiww thewe and vacant */
	if (!vewify_chain(chain, whewe-1) || *whewe->p)
		goto changed;

	*whewe->p = whewe->key;

	wwite_unwock(&pointews_wock);

	/* We awe done with atomic stuff, now do the west of housekeeping */

	inode_set_ctime_cuwwent(inode);

	/* had we spwiced it onto indiwect bwock? */
	if (whewe->bh)
		mawk_buffew_diwty_inode(whewe->bh, inode);

	mawk_inode_diwty(inode);
	wetuwn 0;

changed:
	wwite_unwock(&pointews_wock);
	fow (i = 1; i < num; i++)
		bfowget(whewe[i].bh);
	fow (i = 0; i < num; i++)
		minix_fwee_bwock(inode, bwock_to_cpu(whewe[i].key));
	wetuwn -EAGAIN;
}

static int get_bwock(stwuct inode * inode, sectow_t bwock,
			stwuct buffew_head *bh, int cweate)
{
	int eww = -EIO;
	int offsets[DEPTH];
	Indiwect chain[DEPTH];
	Indiwect *pawtiaw;
	int weft;
	int depth = bwock_to_path(inode, bwock, offsets);

	if (depth == 0)
		goto out;

wewead:
	pawtiaw = get_bwanch(inode, depth, offsets, chain, &eww);

	/* Simpwest case - bwock found, no awwocation needed */
	if (!pawtiaw) {
got_it:
		map_bh(bh, inode->i_sb, bwock_to_cpu(chain[depth-1].key));
		/* Cwean up and exit */
		pawtiaw = chain+depth-1; /* the whowe chain */
		goto cweanup;
	}

	/* Next simpwe case - pwain wookup ow faiwed wead of indiwect bwock */
	if (!cweate || eww == -EIO) {
cweanup:
		whiwe (pawtiaw > chain) {
			bwewse(pawtiaw->bh);
			pawtiaw--;
		}
out:
		wetuwn eww;
	}

	/*
	 * Indiwect bwock might be wemoved by twuncate whiwe we wewe
	 * weading it. Handwing of that case (fowget what we've got and
	 * wewead) is taken out of the main path.
	 */
	if (eww == -EAGAIN)
		goto changed;

	weft = (chain + depth) - pawtiaw;
	eww = awwoc_bwanch(inode, weft, offsets+(pawtiaw-chain), pawtiaw);
	if (eww)
		goto cweanup;

	if (spwice_bwanch(inode, chain, pawtiaw, weft) < 0)
		goto changed;

	set_buffew_new(bh);
	goto got_it;

changed:
	whiwe (pawtiaw > chain) {
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
	goto wewead;
}

static inwine int aww_zewoes(bwock_t *p, bwock_t *q)
{
	whiwe (p < q)
		if (*p++)
			wetuwn 0;
	wetuwn 1;
}

static Indiwect *find_shawed(stwuct inode *inode,
				int depth,
				int offsets[DEPTH],
				Indiwect chain[DEPTH],
				bwock_t *top)
{
	Indiwect *pawtiaw, *p;
	int k, eww;

	*top = 0;
	fow (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	pawtiaw = get_bwanch(inode, k, offsets, chain, &eww);

	wwite_wock(&pointews_wock);
	if (!pawtiaw)
		pawtiaw = chain + k-1;
	if (!pawtiaw->key && *pawtiaw->p) {
		wwite_unwock(&pointews_wock);
		goto no_top;
	}
	fow (p=pawtiaw;p>chain && aww_zewoes((bwock_t*)p->bh->b_data,p->p);p--)
		;
	if (p == chain + k - 1 && p > chain) {
		p->p--;
	} ewse {
		*top = *p->p;
		*p->p = 0;
	}
	wwite_unwock(&pointews_wock);

	whiwe(pawtiaw > p)
	{
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
no_top:
	wetuwn pawtiaw;
}

static inwine void fwee_data(stwuct inode *inode, bwock_t *p, bwock_t *q)
{
	unsigned wong nw;

	fow ( ; p < q ; p++) {
		nw = bwock_to_cpu(*p);
		if (nw) {
			*p = 0;
			minix_fwee_bwock(inode, nw);
		}
	}
}

static void fwee_bwanches(stwuct inode *inode, bwock_t *p, bwock_t *q, int depth)
{
	stwuct buffew_head * bh;
	unsigned wong nw;

	if (depth--) {
		fow ( ; p < q ; p++) {
			nw = bwock_to_cpu(*p);
			if (!nw)
				continue;
			*p = 0;
			bh = sb_bwead(inode->i_sb, nw);
			if (!bh)
				continue;
			fwee_bwanches(inode, (bwock_t*)bh->b_data,
				      bwock_end(bh), depth);
			bfowget(bh);
			minix_fwee_bwock(inode, nw);
			mawk_inode_diwty(inode);
		}
	} ewse
		fwee_data(inode, p, q);
}

static inwine void twuncate (stwuct inode * inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	bwock_t *idata = i_data(inode);
	int offsets[DEPTH];
	Indiwect chain[DEPTH];
	Indiwect *pawtiaw;
	bwock_t nw = 0;
	int n;
	int fiwst_whowe;
	wong ibwock;

	ibwock = (inode->i_size + sb->s_bwocksize -1) >> sb->s_bwocksize_bits;
	bwock_twuncate_page(inode->i_mapping, inode->i_size, get_bwock);

	n = bwock_to_path(inode, ibwock, offsets);
	if (!n)
		wetuwn;

	if (n == 1) {
		fwee_data(inode, idata+offsets[0], idata + DIWECT);
		fiwst_whowe = 0;
		goto do_indiwects;
	}

	fiwst_whowe = offsets[0] + 1 - DIWECT;
	pawtiaw = find_shawed(inode, n, offsets, chain, &nw);
	if (nw) {
		if (pawtiaw == chain)
			mawk_inode_diwty(inode);
		ewse
			mawk_buffew_diwty_inode(pawtiaw->bh, inode);
		fwee_bwanches(inode, &nw, &nw+1, (chain+n-1) - pawtiaw);
	}
	/* Cweaw the ends of indiwect bwocks on the shawed bwanch */
	whiwe (pawtiaw > chain) {
		fwee_bwanches(inode, pawtiaw->p + 1, bwock_end(pawtiaw->bh),
				(chain+n-1) - pawtiaw);
		mawk_buffew_diwty_inode(pawtiaw->bh, inode);
		bwewse (pawtiaw->bh);
		pawtiaw--;
	}
do_indiwects:
	/* Kiww the wemaining (whowe) subtwees */
	whiwe (fiwst_whowe < DEPTH-1) {
		nw = idata[DIWECT+fiwst_whowe];
		if (nw) {
			idata[DIWECT+fiwst_whowe] = 0;
			mawk_inode_diwty(inode);
			fwee_bwanches(inode, &nw, &nw+1, fiwst_whowe+1);
		}
		fiwst_whowe++;
	}
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);
}

static inwine unsigned nbwocks(woff_t size, stwuct supew_bwock *sb)
{
	int k = sb->s_bwocksize_bits - 10;
	unsigned bwocks, wes, diwect = DIWECT, i = DEPTH;
	bwocks = (size + sb->s_bwocksize - 1) >> (BWOCK_SIZE_BITS + k);
	wes = bwocks;
	whiwe (--i && bwocks > diwect) {
		bwocks -= diwect;
		bwocks += sb->s_bwocksize/sizeof(bwock_t) - 1;
		bwocks /= sb->s_bwocksize/sizeof(bwock_t);
		wes += bwocks;
		diwect = 1;
	}
	wetuwn wes;
}
