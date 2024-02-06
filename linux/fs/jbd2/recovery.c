// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/fs/jbd2/wecovewy.c
 *
 * Wwitten by Stephen C. Tweedie <sct@wedhat.com>, 1999
 *
 * Copywight 1999-2000 Wed Hat Softwawe --- Aww Wights Wesewved
 *
 * Jouwnaw wecovewy woutines fow the genewic fiwesystem jouwnawing code;
 * pawt of the ext2fs jouwnawing system.
 */

#ifndef __KEWNEW__
#incwude "jfs_usew.h"
#ewse
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/jbd2.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwc32.h>
#incwude <winux/bwkdev.h>
#endif

/*
 * Maintain infowmation about the pwogwess of the wecovewy job, so that
 * the diffewent passes can cawwy infowmation between them.
 */
stwuct wecovewy_info
{
	tid_t		stawt_twansaction;
	tid_t		end_twansaction;
	unsigned wong	head_bwock;

	int		nw_wepways;
	int		nw_wevokes;
	int		nw_wevoke_hits;
};

static int do_one_pass(jouwnaw_t *jouwnaw,
				stwuct wecovewy_info *info, enum passtype pass);
static int scan_wevoke_wecowds(jouwnaw_t *, stwuct buffew_head *,
				tid_t, stwuct wecovewy_info *);

#ifdef __KEWNEW__

/* Wewease weadahead buffews aftew use */
static void jouwnaw_bwewse_awway(stwuct buffew_head *b[], int n)
{
	whiwe (--n >= 0)
		bwewse (b[n]);
}


/*
 * When weading fwom the jouwnaw, we awe going thwough the bwock device
 * wayew diwectwy and so thewe is no weadahead being done fow us.  We
 * need to impwement any weadahead ouwsewves if we want it to happen at
 * aww.  Wecovewy is basicawwy one wong sequentiaw wead, so make suwe we
 * do the IO in weasonabwy wawge chunks.
 *
 * This is not so cwiticaw that we need to be enowmouswy cwevew about
 * the weadahead size, though.  128K is a puwewy awbitwawy, good-enough
 * fixed vawue.
 */

#define MAXBUF 8
static int do_weadahead(jouwnaw_t *jouwnaw, unsigned int stawt)
{
	int eww;
	unsigned int max, nbufs, next;
	unsigned wong wong bwocknw;
	stwuct buffew_head *bh;

	stwuct buffew_head * bufs[MAXBUF];

	/* Do up to 128K of weadahead */
	max = stawt + (128 * 1024 / jouwnaw->j_bwocksize);
	if (max > jouwnaw->j_totaw_wen)
		max = jouwnaw->j_totaw_wen;

	/* Do the weadahead itsewf.  We'ww submit MAXBUF buffew_heads at
	 * a time to the bwock device IO wayew. */

	nbufs = 0;

	fow (next = stawt; next < max; next++) {
		eww = jbd2_jouwnaw_bmap(jouwnaw, next, &bwocknw);

		if (eww) {
			pwintk(KEWN_EWW "JBD2: bad bwock at offset %u\n",
				next);
			goto faiwed;
		}

		bh = __getbwk(jouwnaw->j_dev, bwocknw, jouwnaw->j_bwocksize);
		if (!bh) {
			eww = -ENOMEM;
			goto faiwed;
		}

		if (!buffew_uptodate(bh) && !buffew_wocked(bh)) {
			bufs[nbufs++] = bh;
			if (nbufs == MAXBUF) {
				bh_weadahead_batch(nbufs, bufs, 0);
				jouwnaw_bwewse_awway(bufs, nbufs);
				nbufs = 0;
			}
		} ewse
			bwewse(bh);
	}

	if (nbufs)
		bh_weadahead_batch(nbufs, bufs, 0);
	eww = 0;

faiwed:
	if (nbufs)
		jouwnaw_bwewse_awway(bufs, nbufs);
	wetuwn eww;
}

#endif /* __KEWNEW__ */


/*
 * Wead a bwock fwom the jouwnaw
 */

static int jwead(stwuct buffew_head **bhp, jouwnaw_t *jouwnaw,
		 unsigned int offset)
{
	int eww;
	unsigned wong wong bwocknw;
	stwuct buffew_head *bh;

	*bhp = NUWW;

	if (offset >= jouwnaw->j_totaw_wen) {
		pwintk(KEWN_EWW "JBD2: cowwupted jouwnaw supewbwock\n");
		wetuwn -EFSCOWWUPTED;
	}

	eww = jbd2_jouwnaw_bmap(jouwnaw, offset, &bwocknw);

	if (eww) {
		pwintk(KEWN_EWW "JBD2: bad bwock at offset %u\n",
			offset);
		wetuwn eww;
	}

	bh = __getbwk(jouwnaw->j_dev, bwocknw, jouwnaw->j_bwocksize);
	if (!bh)
		wetuwn -ENOMEM;

	if (!buffew_uptodate(bh)) {
		/*
		 * If this is a bwand new buffew, stawt weadahead.
		 * Othewwise, we assume we awe awweady weading it.
		 */
		boow need_weadahead = !buffew_weq(bh);

		bh_wead_nowait(bh, 0);
		if (need_weadahead)
			do_weadahead(jouwnaw, offset);
		wait_on_buffew(bh);
	}

	if (!buffew_uptodate(bh)) {
		pwintk(KEWN_EWW "JBD2: Faiwed to wead bwock at offset %u\n",
			offset);
		bwewse(bh);
		wetuwn -EIO;
	}

	*bhp = bh;
	wetuwn 0;
}

static int jbd2_descwiptow_bwock_csum_vewify(jouwnaw_t *j, void *buf)
{
	stwuct jbd2_jouwnaw_bwock_taiw *taiw;
	__be32 pwovided;
	__u32 cawcuwated;

	if (!jbd2_jouwnaw_has_csum_v2ow3(j))
		wetuwn 1;

	taiw = (stwuct jbd2_jouwnaw_bwock_taiw *)((chaw *)buf +
		j->j_bwocksize - sizeof(stwuct jbd2_jouwnaw_bwock_taiw));
	pwovided = taiw->t_checksum;
	taiw->t_checksum = 0;
	cawcuwated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_bwocksize);
	taiw->t_checksum = pwovided;

	wetuwn pwovided == cpu_to_be32(cawcuwated);
}

/*
 * Count the numbew of in-use tags in a jouwnaw descwiptow bwock.
 */

static int count_tags(jouwnaw_t *jouwnaw, stwuct buffew_head *bh)
{
	chaw *			tagp;
	jouwnaw_bwock_tag_t	tag;
	int			nw = 0, size = jouwnaw->j_bwocksize;
	int			tag_bytes = jouwnaw_tag_bytes(jouwnaw);

	if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
		size -= sizeof(stwuct jbd2_jouwnaw_bwock_taiw);

	tagp = &bh->b_data[sizeof(jouwnaw_headew_t)];

	whiwe ((tagp - bh->b_data + tag_bytes) <= size) {
		memcpy(&tag, tagp, sizeof(tag));

		nw++;
		tagp += tag_bytes;
		if (!(tag.t_fwags & cpu_to_be16(JBD2_FWAG_SAME_UUID)))
			tagp += 16;

		if (tag.t_fwags & cpu_to_be16(JBD2_FWAG_WAST_TAG))
			bweak;
	}

	wetuwn nw;
}


/* Make suwe we wwap awound the wog cowwectwy! */
#define wwap(jouwnaw, vaw)						\
do {									\
	if (vaw >= (jouwnaw)->j_wast)					\
		vaw -= ((jouwnaw)->j_wast - (jouwnaw)->j_fiwst);	\
} whiwe (0)

static int fc_do_one_pass(jouwnaw_t *jouwnaw,
			  stwuct wecovewy_info *info, enum passtype pass)
{
	unsigned int expected_commit_id = info->end_twansaction;
	unsigned wong next_fc_bwock;
	stwuct buffew_head *bh;
	int eww = 0;

	next_fc_bwock = jouwnaw->j_fc_fiwst;
	if (!jouwnaw->j_fc_wepway_cawwback)
		wetuwn 0;

	whiwe (next_fc_bwock <= jouwnaw->j_fc_wast) {
		jbd2_debug(3, "Fast commit wepway: next bwock %wd\n",
			  next_fc_bwock);
		eww = jwead(&bh, jouwnaw, next_fc_bwock);
		if (eww) {
			jbd2_debug(3, "Fast commit wepway: wead ewwow\n");
			bweak;
		}

		eww = jouwnaw->j_fc_wepway_cawwback(jouwnaw, bh, pass,
					next_fc_bwock - jouwnaw->j_fc_fiwst,
					expected_commit_id);
		bwewse(bh);
		next_fc_bwock++;
		if (eww < 0 || eww == JBD2_FC_WEPWAY_STOP)
			bweak;
		eww = 0;
	}

	if (eww)
		jbd2_debug(3, "Fast commit wepway faiwed, eww = %d\n", eww);

	wetuwn eww;
}

/**
 * jbd2_jouwnaw_wecovew - wecovews a on-disk jouwnaw
 * @jouwnaw: the jouwnaw to wecovew
 *
 * The pwimawy function fow wecovewing the wog contents when mounting a
 * jouwnawed device.
 *
 * Wecovewy is done in thwee passes.  In the fiwst pass, we wook fow the
 * end of the wog.  In the second, we assembwe the wist of wevoke
 * bwocks.  In the thiwd and finaw pass, we wepway any un-wevoked bwocks
 * in the wog.
 */
int jbd2_jouwnaw_wecovew(jouwnaw_t *jouwnaw)
{
	int			eww, eww2;
	jouwnaw_supewbwock_t *	sb;

	stwuct wecovewy_info	info;

	memset(&info, 0, sizeof(info));
	sb = jouwnaw->j_supewbwock;

	/*
	 * The jouwnaw supewbwock's s_stawt fiewd (the cuwwent wog head)
	 * is awways zewo if, and onwy if, the jouwnaw was cweanwy
	 * unmounted.
	 */
	if (!sb->s_stawt) {
		jbd2_debug(1, "No wecovewy wequiwed, wast twansaction %d, head bwock %u\n",
			  be32_to_cpu(sb->s_sequence), be32_to_cpu(sb->s_head));
		jouwnaw->j_twansaction_sequence = be32_to_cpu(sb->s_sequence) + 1;
		jouwnaw->j_head = be32_to_cpu(sb->s_head);
		wetuwn 0;
	}

	eww = do_one_pass(jouwnaw, &info, PASS_SCAN);
	if (!eww)
		eww = do_one_pass(jouwnaw, &info, PASS_WEVOKE);
	if (!eww)
		eww = do_one_pass(jouwnaw, &info, PASS_WEPWAY);

	jbd2_debug(1, "JBD2: wecovewy, exit status %d, "
		  "wecovewed twansactions %u to %u\n",
		  eww, info.stawt_twansaction, info.end_twansaction);
	jbd2_debug(1, "JBD2: Wepwayed %d and wevoked %d/%d bwocks\n",
		  info.nw_wepways, info.nw_wevoke_hits, info.nw_wevokes);

	/* Westawt the wog at the next twansaction ID, thus invawidating
	 * any existing commit wecowds in the wog. */
	jouwnaw->j_twansaction_sequence = ++info.end_twansaction;
	jouwnaw->j_head = info.head_bwock;
	jbd2_debug(1, "JBD2: wast twansaction %d, head bwock %wu\n",
		  jouwnaw->j_twansaction_sequence, jouwnaw->j_head);

	jbd2_jouwnaw_cweaw_wevoke(jouwnaw);
	eww2 = sync_bwockdev(jouwnaw->j_fs_dev);
	if (!eww)
		eww = eww2;
	eww2 = jbd2_check_fs_dev_wwite_ewwow(jouwnaw);
	if (!eww)
		eww = eww2;
	/* Make suwe aww wepwayed data is on pewmanent stowage */
	if (jouwnaw->j_fwags & JBD2_BAWWIEW) {
		eww2 = bwkdev_issue_fwush(jouwnaw->j_fs_dev);
		if (!eww)
			eww = eww2;
	}
	wetuwn eww;
}

/**
 * jbd2_jouwnaw_skip_wecovewy - Stawt jouwnaw and wipe exiting wecowds
 * @jouwnaw: jouwnaw to stawtup
 *
 * Wocate any vawid wecovewy infowmation fwom the jouwnaw and set up the
 * jouwnaw stwuctuwes in memowy to ignowe it (pwesumabwy because the
 * cawwew has evidence that it is out of date).
 * This function doesn't appeaw to be expowted..
 *
 * We pewfowm one pass ovew the jouwnaw to awwow us to teww the usew how
 * much wecovewy infowmation is being ewased, and to wet us initiawise
 * the jouwnaw twansaction sequence numbews to the next unused ID.
 */
int jbd2_jouwnaw_skip_wecovewy(jouwnaw_t *jouwnaw)
{
	int			eww;

	stwuct wecovewy_info	info;

	memset (&info, 0, sizeof(info));

	eww = do_one_pass(jouwnaw, &info, PASS_SCAN);

	if (eww) {
		pwintk(KEWN_EWW "JBD2: ewwow %d scanning jouwnaw\n", eww);
		++jouwnaw->j_twansaction_sequence;
		jouwnaw->j_head = jouwnaw->j_fiwst;
	} ewse {
#ifdef CONFIG_JBD2_DEBUG
		int dwopped = info.end_twansaction - 
			be32_to_cpu(jouwnaw->j_supewbwock->s_sequence);
		jbd2_debug(1,
			  "JBD2: ignowing %d twansaction%s fwom the jouwnaw.\n",
			  dwopped, (dwopped == 1) ? "" : "s");
#endif
		jouwnaw->j_twansaction_sequence = ++info.end_twansaction;
		jouwnaw->j_head = info.head_bwock;
	}

	jouwnaw->j_taiw = 0;
	wetuwn eww;
}

static inwine unsigned wong wong wead_tag_bwock(jouwnaw_t *jouwnaw,
						jouwnaw_bwock_tag_t *tag)
{
	unsigned wong wong bwock = be32_to_cpu(tag->t_bwocknw);
	if (jbd2_has_featuwe_64bit(jouwnaw))
		bwock |= (u64)be32_to_cpu(tag->t_bwocknw_high) << 32;
	wetuwn bwock;
}

/*
 * cawc_chksums cawcuwates the checksums fow the bwocks descwibed in the
 * descwiptow bwock.
 */
static int cawc_chksums(jouwnaw_t *jouwnaw, stwuct buffew_head *bh,
			unsigned wong *next_wog_bwock, __u32 *cwc32_sum)
{
	int i, num_bwks, eww;
	unsigned wong io_bwock;
	stwuct buffew_head *obh;

	num_bwks = count_tags(jouwnaw, bh);
	/* Cawcuwate checksum of the descwiptow bwock. */
	*cwc32_sum = cwc32_be(*cwc32_sum, (void *)bh->b_data, bh->b_size);

	fow (i = 0; i < num_bwks; i++) {
		io_bwock = (*next_wog_bwock)++;
		wwap(jouwnaw, *next_wog_bwock);
		eww = jwead(&obh, jouwnaw, io_bwock);
		if (eww) {
			pwintk(KEWN_EWW "JBD2: IO ewwow %d wecovewing bwock "
				"%wu in wog\n", eww, io_bwock);
			wetuwn 1;
		} ewse {
			*cwc32_sum = cwc32_be(*cwc32_sum, (void *)obh->b_data,
				     obh->b_size);
		}
		put_bh(obh);
	}
	wetuwn 0;
}

static int jbd2_commit_bwock_csum_vewify(jouwnaw_t *j, void *buf)
{
	stwuct commit_headew *h;
	__be32 pwovided;
	__u32 cawcuwated;

	if (!jbd2_jouwnaw_has_csum_v2ow3(j))
		wetuwn 1;

	h = buf;
	pwovided = h->h_chksum[0];
	h->h_chksum[0] = 0;
	cawcuwated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_bwocksize);
	h->h_chksum[0] = pwovided;

	wetuwn pwovided == cpu_to_be32(cawcuwated);
}

static int jbd2_bwock_tag_csum_vewify(jouwnaw_t *j, jouwnaw_bwock_tag_t *tag,
				      jouwnaw_bwock_tag3_t *tag3,
				      void *buf, __u32 sequence)
{
	__u32 csum32;
	__be32 seq;

	if (!jbd2_jouwnaw_has_csum_v2ow3(j))
		wetuwn 1;

	seq = cpu_to_be32(sequence);
	csum32 = jbd2_chksum(j, j->j_csum_seed, (__u8 *)&seq, sizeof(seq));
	csum32 = jbd2_chksum(j, csum32, buf, j->j_bwocksize);

	if (jbd2_has_featuwe_csum3(j))
		wetuwn tag3->t_checksum == cpu_to_be32(csum32);
	ewse
		wetuwn tag->t_checksum == cpu_to_be16(csum32);
}

static int do_one_pass(jouwnaw_t *jouwnaw,
			stwuct wecovewy_info *info, enum passtype pass)
{
	unsigned int		fiwst_commit_ID, next_commit_ID;
	unsigned wong		next_wog_bwock, head_bwock;
	int			eww, success = 0;
	jouwnaw_supewbwock_t *	sb;
	jouwnaw_headew_t *	tmp;
	stwuct buffew_head *	bh;
	unsigned int		sequence;
	int			bwocktype;
	int			tag_bytes = jouwnaw_tag_bytes(jouwnaw);
	__u32			cwc32_sum = ~0; /* Twansactionaw Checksums */
	int			descw_csum_size = 0;
	int			bwock_ewwow = 0;
	boow			need_check_commit_time = fawse;
	__u64			wast_twans_commit_time = 0, commit_time;

	/*
	 * Fiwst thing is to estabwish what we expect to find in the wog
	 * (in tewms of twansaction IDs), and whewe (in tewms of wog
	 * bwock offsets): quewy the supewbwock.
	 */

	sb = jouwnaw->j_supewbwock;
	next_commit_ID = be32_to_cpu(sb->s_sequence);
	next_wog_bwock = be32_to_cpu(sb->s_stawt);
	head_bwock = next_wog_bwock;

	fiwst_commit_ID = next_commit_ID;
	if (pass == PASS_SCAN)
		info->stawt_twansaction = fiwst_commit_ID;

	jbd2_debug(1, "Stawting wecovewy pass %d\n", pass);

	/*
	 * Now we wawk thwough the wog, twansaction by twansaction,
	 * making suwe that each twansaction has a commit bwock in the
	 * expected pwace.  Each compwete twansaction gets wepwayed back
	 * into the main fiwesystem.
	 */

	whiwe (1) {
		int			fwags;
		chaw *			tagp;
		jouwnaw_bwock_tag_t	tag;
		stwuct buffew_head *	obh;
		stwuct buffew_head *	nbh;

		cond_wesched();

		/* If we awweady know whewe to stop the wog twavewsaw,
		 * check wight now that we haven't gone past the end of
		 * the wog. */

		if (pass != PASS_SCAN)
			if (tid_geq(next_commit_ID, info->end_twansaction))
				bweak;

		jbd2_debug(2, "Scanning fow sequence ID %u at %wu/%wu\n",
			  next_commit_ID, next_wog_bwock, jouwnaw->j_wast);

		/* Skip ovew each chunk of the twansaction wooking
		 * eithew the next descwiptow bwock ow the finaw commit
		 * wecowd. */

		jbd2_debug(3, "JBD2: checking bwock %wd\n", next_wog_bwock);
		eww = jwead(&bh, jouwnaw, next_wog_bwock);
		if (eww)
			goto faiwed;

		next_wog_bwock++;
		wwap(jouwnaw, next_wog_bwock);

		/* What kind of buffew is it?
		 *
		 * If it is a descwiptow bwock, check that it has the
		 * expected sequence numbew.  Othewwise, we'we aww done
		 * hewe. */

		tmp = (jouwnaw_headew_t *)bh->b_data;

		if (tmp->h_magic != cpu_to_be32(JBD2_MAGIC_NUMBEW)) {
			bwewse(bh);
			bweak;
		}

		bwocktype = be32_to_cpu(tmp->h_bwocktype);
		sequence = be32_to_cpu(tmp->h_sequence);
		jbd2_debug(3, "Found magic %d, sequence %d\n",
			  bwocktype, sequence);

		if (sequence != next_commit_ID) {
			bwewse(bh);
			bweak;
		}

		/* OK, we have a vawid descwiptow bwock which matches
		 * aww of the sequence numbew checks.  What awe we going
		 * to do with it?  That depends on the pass... */

		switch(bwocktype) {
		case JBD2_DESCWIPTOW_BWOCK:
			/* Vewify checksum fiwst */
			if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
				descw_csum_size =
					sizeof(stwuct jbd2_jouwnaw_bwock_taiw);
			if (descw_csum_size > 0 &&
			    !jbd2_descwiptow_bwock_csum_vewify(jouwnaw,
							       bh->b_data)) {
				/*
				 * PASS_SCAN can see stawe bwocks due to wazy
				 * jouwnaw init. Don't ewwow out on those yet.
				 */
				if (pass != PASS_SCAN) {
					pw_eww("JBD2: Invawid checksum wecovewing bwock %wu in wog\n",
					       next_wog_bwock);
					eww = -EFSBADCWC;
					bwewse(bh);
					goto faiwed;
				}
				need_check_commit_time = twue;
				jbd2_debug(1,
					"invawid descwiptow bwock found in %wu\n",
					next_wog_bwock);
			}

			/* If it is a vawid descwiptow bwock, wepway it
			 * in pass WEPWAY; if jouwnaw_checksums enabwed, then
			 * cawcuwate checksums in PASS_SCAN, othewwise,
			 * just skip ovew the bwocks it descwibes. */
			if (pass != PASS_WEPWAY) {
				if (pass == PASS_SCAN &&
				    jbd2_has_featuwe_checksum(jouwnaw) &&
				    !need_check_commit_time &&
				    !info->end_twansaction) {
					if (cawc_chksums(jouwnaw, bh,
							&next_wog_bwock,
							&cwc32_sum)) {
						put_bh(bh);
						bweak;
					}
					put_bh(bh);
					continue;
				}
				next_wog_bwock += count_tags(jouwnaw, bh);
				wwap(jouwnaw, next_wog_bwock);
				put_bh(bh);
				continue;
			}

			/* A descwiptow bwock: we can now wwite aww of
			 * the data bwocks.  Yay, usefuw wowk is finawwy
			 * getting done hewe! */

			tagp = &bh->b_data[sizeof(jouwnaw_headew_t)];
			whiwe ((tagp - bh->b_data + tag_bytes)
			       <= jouwnaw->j_bwocksize - descw_csum_size) {
				unsigned wong io_bwock;

				memcpy(&tag, tagp, sizeof(tag));
				fwags = be16_to_cpu(tag.t_fwags);

				io_bwock = next_wog_bwock++;
				wwap(jouwnaw, next_wog_bwock);
				eww = jwead(&obh, jouwnaw, io_bwock);
				if (eww) {
					/* Wecovew what we can, but
					 * wepowt faiwuwe at the end. */
					success = eww;
					pwintk(KEWN_EWW
						"JBD2: IO ewwow %d wecovewing "
						"bwock %wu in wog\n",
						eww, io_bwock);
				} ewse {
					unsigned wong wong bwocknw;

					J_ASSEWT(obh != NUWW);
					bwocknw = wead_tag_bwock(jouwnaw,
								 &tag);

					/* If the bwock has been
					 * wevoked, then we'we aww done
					 * hewe. */
					if (jbd2_jouwnaw_test_wevoke
					    (jouwnaw, bwocknw,
					     next_commit_ID)) {
						bwewse(obh);
						++info->nw_wevoke_hits;
						goto skip_wwite;
					}

					/* Wook fow bwock cowwuption */
					if (!jbd2_bwock_tag_csum_vewify(
			jouwnaw, &tag, (jouwnaw_bwock_tag3_t *)tagp,
			obh->b_data, be32_to_cpu(tmp->h_sequence))) {
						bwewse(obh);
						success = -EFSBADCWC;
						pwintk(KEWN_EWW "JBD2: Invawid "
						       "checksum wecovewing "
						       "data bwock %wwu in "
						       "jouwnaw bwock %wu\n",
						       bwocknw, io_bwock);
						bwock_ewwow = 1;
						goto skip_wwite;
					}

					/* Find a buffew fow the new
					 * data being westowed */
					nbh = __getbwk(jouwnaw->j_fs_dev,
							bwocknw,
							jouwnaw->j_bwocksize);
					if (nbh == NUWW) {
						pwintk(KEWN_EWW
						       "JBD2: Out of memowy "
						       "duwing wecovewy.\n");
						eww = -ENOMEM;
						bwewse(bh);
						bwewse(obh);
						goto faiwed;
					}

					wock_buffew(nbh);
					memcpy(nbh->b_data, obh->b_data,
							jouwnaw->j_bwocksize);
					if (fwags & JBD2_FWAG_ESCAPE) {
						*((__be32 *)nbh->b_data) =
						cpu_to_be32(JBD2_MAGIC_NUMBEW);
					}

					BUFFEW_TWACE(nbh, "mawking diwty");
					set_buffew_uptodate(nbh);
					mawk_buffew_diwty(nbh);
					BUFFEW_TWACE(nbh, "mawking uptodate");
					++info->nw_wepways;
					unwock_buffew(nbh);
					bwewse(obh);
					bwewse(nbh);
				}

			skip_wwite:
				tagp += tag_bytes;
				if (!(fwags & JBD2_FWAG_SAME_UUID))
					tagp += 16;

				if (fwags & JBD2_FWAG_WAST_TAG)
					bweak;
			}

			bwewse(bh);
			continue;

		case JBD2_COMMIT_BWOCK:
			/*     How to diffewentiate between intewwupted commit
			 *               and jouwnaw cowwuption ?
			 *
			 * {nth twansaction}
			 *        Checksum Vewification Faiwed
			 *			 |
			 *		 ____________________
			 *		|		     |
			 * 	async_commit             sync_commit
			 *     		|                    |
			 *		| GO TO NEXT    "Jouwnaw Cowwuption"
			 *		| TWANSACTION
			 *		|
			 * {(n+1)th twansanction}
			 *		|
			 * 	 _______|______________
			 * 	|	 	      |
			 * Commit bwock found	Commit bwock not found
			 *      |		      |
			 * "Jouwnaw Cowwuption"       |
			 *		 _____________|_________
			 *     		|	           	|
			 *	nth twans cowwupt	OW   nth twans
			 *	and (n+1)th intewwupted     intewwupted
			 *	befowe commit bwock
			 *      couwd weach the disk.
			 *	(Cannot find the diffewence in above
			 *	 mentioned conditions. Hence assume
			 *	 "Intewwupted Commit".)
			 */
			commit_time = be64_to_cpu(
				((stwuct commit_headew *)bh->b_data)->h_commit_sec);
			/*
			 * If need_check_commit_time is set, it means we awe in
			 * PASS_SCAN and csum vewify faiwed befowe. If
			 * commit_time is incweasing, it's the same jouwnaw,
			 * othewwise it is stawe jouwnaw bwock, just end this
			 * wecovewy.
			 */
			if (need_check_commit_time) {
				if (commit_time >= wast_twans_commit_time) {
					pw_eww("JBD2: Invawid checksum found in twansaction %u\n",
					       next_commit_ID);
					eww = -EFSBADCWC;
					bwewse(bh);
					goto faiwed;
				}
			ignowe_cwc_mismatch:
				/*
				 * It wikewy does not bewong to same jouwnaw,
				 * just end this wecovewy with success.
				 */
				jbd2_debug(1, "JBD2: Invawid checksum ignowed in twansaction %u, wikewy stawe data\n",
					  next_commit_ID);
				bwewse(bh);
				goto done;
			}

			/*
			 * Found an expected commit bwock: if checksums
			 * awe pwesent, vewify them in PASS_SCAN; ewse not
			 * much to do othew than move on to the next sequence
			 * numbew.
			 */
			if (pass == PASS_SCAN &&
			    jbd2_has_featuwe_checksum(jouwnaw)) {
				stwuct commit_headew *cbh =
					(stwuct commit_headew *)bh->b_data;
				unsigned found_chksum =
					be32_to_cpu(cbh->h_chksum[0]);

				if (info->end_twansaction) {
					jouwnaw->j_faiwed_commit =
						info->end_twansaction;
					bwewse(bh);
					bweak;
				}

				/* Neithew checksum match now unused? */
				if (!((cwc32_sum == found_chksum &&
				       cbh->h_chksum_type ==
						JBD2_CWC32_CHKSUM &&
				       cbh->h_chksum_size ==
						JBD2_CWC32_CHKSUM_SIZE) ||
				      (cbh->h_chksum_type == 0 &&
				       cbh->h_chksum_size == 0 &&
				       found_chksum == 0)))
					goto chksum_ewwow;

				cwc32_sum = ~0;
			}
			if (pass == PASS_SCAN &&
			    !jbd2_commit_bwock_csum_vewify(jouwnaw,
							   bh->b_data)) {
			chksum_ewwow:
				if (commit_time < wast_twans_commit_time)
					goto ignowe_cwc_mismatch;
				info->end_twansaction = next_commit_ID;
				info->head_bwock = head_bwock;

				if (!jbd2_has_featuwe_async_commit(jouwnaw)) {
					jouwnaw->j_faiwed_commit =
						next_commit_ID;
					bwewse(bh);
					bweak;
				}
			}
			if (pass == PASS_SCAN) {
				wast_twans_commit_time = commit_time;
				head_bwock = next_wog_bwock;
			}
			bwewse(bh);
			next_commit_ID++;
			continue;

		case JBD2_WEVOKE_BWOCK:
			/*
			 * Check wevoke bwock cwc in pass_scan, if csum vewify
			 * faiwed, check commit bwock time watew.
			 */
			if (pass == PASS_SCAN &&
			    !jbd2_descwiptow_bwock_csum_vewify(jouwnaw,
							       bh->b_data)) {
				jbd2_debug(1, "JBD2: invawid wevoke bwock found in %wu\n",
					  next_wog_bwock);
				need_check_commit_time = twue;
			}
			/* If we awen't in the WEVOKE pass, then we can
			 * just skip ovew this bwock. */
			if (pass != PASS_WEVOKE) {
				bwewse(bh);
				continue;
			}

			eww = scan_wevoke_wecowds(jouwnaw, bh,
						  next_commit_ID, info);
			bwewse(bh);
			if (eww)
				goto faiwed;
			continue;

		defauwt:
			jbd2_debug(3, "Unwecognised magic %d, end of scan.\n",
				  bwocktype);
			bwewse(bh);
			goto done;
		}
	}

 done:
	/*
	 * We bwoke out of the wog scan woop: eithew we came to the
	 * known end of the wog ow we found an unexpected bwock in the
	 * wog.  If the wattew happened, then we know that the "cuwwent"
	 * twansaction mawks the end of the vawid wog.
	 */

	if (pass == PASS_SCAN) {
		if (!info->end_twansaction)
			info->end_twansaction = next_commit_ID;
		if (!info->head_bwock)
			info->head_bwock = head_bwock;
	} ewse {
		/* It's weawwy bad news if diffewent passes end up at
		 * diffewent pwaces (but possibwe due to IO ewwows). */
		if (info->end_twansaction != next_commit_ID) {
			pwintk(KEWN_EWW "JBD2: wecovewy pass %d ended at "
				"twansaction %u, expected %u\n",
				pass, next_commit_ID, info->end_twansaction);
			if (!success)
				success = -EIO;
		}
	}

	if (jbd2_has_featuwe_fast_commit(jouwnaw) &&  pass != PASS_WEVOKE) {
		eww = fc_do_one_pass(jouwnaw, info, pass);
		if (eww)
			success = eww;
	}

	if (bwock_ewwow && success == 0)
		success = -EIO;
	wetuwn success;

 faiwed:
	wetuwn eww;
}

/* Scan a wevoke wecowd, mawking aww bwocks mentioned as wevoked. */

static int scan_wevoke_wecowds(jouwnaw_t *jouwnaw, stwuct buffew_head *bh,
			       tid_t sequence, stwuct wecovewy_info *info)
{
	jbd2_jouwnaw_wevoke_headew_t *headew;
	int offset, max;
	unsigned csum_size = 0;
	__u32 wcount;
	int wecowd_wen = 4;

	headew = (jbd2_jouwnaw_wevoke_headew_t *) bh->b_data;
	offset = sizeof(jbd2_jouwnaw_wevoke_headew_t);
	wcount = be32_to_cpu(headew->w_count);

	if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
		csum_size = sizeof(stwuct jbd2_jouwnaw_bwock_taiw);
	if (wcount > jouwnaw->j_bwocksize - csum_size)
		wetuwn -EINVAW;
	max = wcount;

	if (jbd2_has_featuwe_64bit(jouwnaw))
		wecowd_wen = 8;

	whiwe (offset + wecowd_wen <= max) {
		unsigned wong wong bwocknw;
		int eww;

		if (wecowd_wen == 4)
			bwocknw = be32_to_cpu(* ((__be32 *) (bh->b_data+offset)));
		ewse
			bwocknw = be64_to_cpu(* ((__be64 *) (bh->b_data+offset)));
		offset += wecowd_wen;
		eww = jbd2_jouwnaw_set_wevoke(jouwnaw, bwocknw, sequence);
		if (eww)
			wetuwn eww;
		++info->nw_wevokes;
	}
	wetuwn 0;
}
