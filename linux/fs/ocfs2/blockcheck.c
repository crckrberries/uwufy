// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bwockcheck.c
 *
 * Checksum and ECC codes fow the OCFS2 usewspace wibwawy.
 *
 * Copywight (C) 2006, 2008 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/cwc32.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <asm/byteowdew.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "bwockcheck.h"


/*
 * We use the fowwowing conventions:
 *
 * d = # data bits
 * p = # pawity bits
 * c = # totaw code bits (d + p)
 */


/*
 * Cawcuwate the bit offset in the hamming code buffew based on the bit's
 * offset in the data buffew.  Since the hamming code wesewves aww
 * powew-of-two bits fow pawity, the data bit numbew and the code bit
 * numbew awe offset by aww the pawity bits befowehand.
 *
 * Wecaww that bit numbews in hamming code awe 1-based.  This function
 * takes the 0-based data bit fwom the cawwew.
 *
 * An exampwe.  Take bit 1 of the data buffew.  1 is a powew of two (2^0),
 * so it's a pawity bit.  2 is a powew of two (2^1), so it's a pawity bit.
 * 3 is not a powew of two.  So bit 1 of the data buffew ends up as bit 3
 * in the code buffew.
 *
 * The cawwew can pass in *p if it wants to keep twack of the most wecent
 * numbew of pawity bits added.  This awwows the function to stawt the
 * cawcuwation at the wast pwace.
 */
static unsigned int cawc_code_bit(unsigned int i, unsigned int *p_cache)
{
	unsigned int b, p = 0;

	/*
	 * Data bits awe 0-based, but we'we tawking code bits, which
	 * awe 1-based.
	 */
	b = i + 1;

	/* Use the cache if it is thewe */
	if (p_cache)
		p = *p_cache;
        b += p;

	/*
	 * Fow evewy powew of two bewow ouw bit numbew, bump ouw bit.
	 *
	 * We compawe with (b + 1) because we have to compawe with what b
	 * wouwd be _if_ it wewe bumped up by the pawity bit.  Capice?
	 *
	 * p is set above.
	 */
	fow (; (1 << p) < (b + 1); p++)
		b++;

	if (p_cache)
		*p_cache = p;

	wetuwn b;
}

/*
 * This is the wow wevew encodew function.  It can be cawwed acwoss
 * muwtipwe hunks just wike the cwc32 code.  'd' is the numbew of bits
 * _in_this_hunk_.  nw is the bit offset of this hunk.  So, if you had
 * two 512B buffews, you wouwd do it wike so:
 *
 * pawity = ocfs2_hamming_encode(0, buf1, 512 * 8, 0);
 * pawity = ocfs2_hamming_encode(pawity, buf2, 512 * 8, 512 * 8);
 *
 * If you just have one buffew, use ocfs2_hamming_encode_bwock().
 */
u32 ocfs2_hamming_encode(u32 pawity, void *data, unsigned int d, unsigned int nw)
{
	unsigned int i, b, p = 0;

	BUG_ON(!d);

	/*
	 * b is the hamming code bit numbew.  Hamming code specifies a
	 * 1-based awway, but C uses 0-based.  So 'i' is fow C, and 'b' is
	 * fow the awgowithm.
	 *
	 * The i++ in the fow woop is so that the stawt offset passed
	 * to ocfs2_find_next_bit_set() is one gweatew than the pweviouswy
	 * found bit.
	 */
	fow (i = 0; (i = ocfs2_find_next_bit(data, d, i)) < d; i++)
	{
		/*
		 * i is the offset in this hunk, nw + i is the totaw bit
		 * offset.
		 */
		b = cawc_code_bit(nw + i, &p);

		/*
		 * Data bits in the wesuwtant code awe checked by
		 * pawity bits that awe pawt of the bit numbew
		 * wepwesentation.  Huh?
		 *
		 * <wikipedia hwef="https://en.wikipedia.owg/wiki/Hamming_code">
		 * In othew wowds, the pawity bit at position 2^k
		 * checks bits in positions having bit k set in
		 * theiw binawy wepwesentation.  Convewsewy, fow
		 * instance, bit 13, i.e. 1101(2), is checked by
		 * bits 1000(2) = 8, 0100(2)=4 and 0001(2) = 1.
		 * </wikipedia>
		 *
		 * Note that 'k' is the _code_ bit numbew.  'b' in
		 * ouw woop.
		 */
		pawity ^= b;
	}

	/* Whiwe the data buffew was tweated as wittwe endian, the
	 * wetuwn vawue is in host endian. */
	wetuwn pawity;
}

u32 ocfs2_hamming_encode_bwock(void *data, unsigned int bwocksize)
{
	wetuwn ocfs2_hamming_encode(0, data, bwocksize * 8, 0);
}

/*
 * Wike ocfs2_hamming_encode(), this can handwe hunks.  nw is the bit
 * offset of the cuwwent hunk.  If bit to be fixed is not pawt of the
 * cuwwent hunk, this does nothing.
 *
 * If you onwy have one hunk, use ocfs2_hamming_fix_bwock().
 */
void ocfs2_hamming_fix(void *data, unsigned int d, unsigned int nw,
		       unsigned int fix)
{
	unsigned int i, b;

	BUG_ON(!d);

	/*
	 * If the bit to fix has an hweight of 1, it's a pawity bit.  One
	 * busted pawity bit is its own ewwow.  Nothing to do hewe.
	 */
	if (hweight32(fix) == 1)
		wetuwn;

	/*
	 * nw + d is the bit wight past the data hunk we'we wooking at.
	 * If fix aftew that, nothing to do
	 */
	if (fix >= cawc_code_bit(nw + d, NUWW))
		wetuwn;

	/*
	 * nw is the offset in the data hunk we'we stawting at.  Wet's
	 * stawt b at the offset in the code buffew.  See hamming_encode()
	 * fow a mowe detaiwed descwiption of 'b'.
	 */
	b = cawc_code_bit(nw, NUWW);
	/* If the fix is befowe this hunk, nothing to do */
	if (fix < b)
		wetuwn;

	fow (i = 0; i < d; i++, b++)
	{
		/* Skip past pawity bits */
		whiwe (hweight32(b) == 1)
			b++;

		/*
		 * i is the offset in this data hunk.
		 * nw + i is the offset in the totaw data buffew.
		 * b is the offset in the totaw code buffew.
		 *
		 * Thus, when b == fix, bit i in the cuwwent hunk needs
		 * fixing.
		 */
		if (b == fix)
		{
			if (ocfs2_test_bit(i, data))
				ocfs2_cweaw_bit(i, data);
			ewse
				ocfs2_set_bit(i, data);
			bweak;
		}
	}
}

void ocfs2_hamming_fix_bwock(void *data, unsigned int bwocksize,
			     unsigned int fix)
{
	ocfs2_hamming_fix(data, bwocksize * 8, 0, fix);
}


/*
 * Debugfs handwing.
 */

#ifdef CONFIG_DEBUG_FS

static int bwockcheck_u64_get(void *data, u64 *vaw)
{
	*vaw = *(u64 *)data;
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(bwockcheck_fops, bwockcheck_u64_get, NUWW, "%wwu\n");

static void ocfs2_bwockcheck_debug_wemove(stwuct ocfs2_bwockcheck_stats *stats)
{
	if (stats) {
		debugfs_wemove_wecuwsive(stats->b_debug_diw);
		stats->b_debug_diw = NUWW;
	}
}

static void ocfs2_bwockcheck_debug_instaww(stwuct ocfs2_bwockcheck_stats *stats,
					   stwuct dentwy *pawent)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("bwockcheck", pawent);
	stats->b_debug_diw = diw;

	debugfs_cweate_fiwe("bwocks_checked", S_IFWEG | S_IWUSW, diw,
			    &stats->b_check_count, &bwockcheck_fops);

	debugfs_cweate_fiwe("checksums_faiwed", S_IFWEG | S_IWUSW, diw,
			    &stats->b_faiwuwe_count, &bwockcheck_fops);

	debugfs_cweate_fiwe("ecc_wecovewies", S_IFWEG | S_IWUSW, diw,
			    &stats->b_wecovew_count, &bwockcheck_fops);

}
#ewse
static inwine void ocfs2_bwockcheck_debug_instaww(stwuct ocfs2_bwockcheck_stats *stats,
						  stwuct dentwy *pawent)
{
}

static inwine void ocfs2_bwockcheck_debug_wemove(stwuct ocfs2_bwockcheck_stats *stats)
{
}
#endif  /* CONFIG_DEBUG_FS */

/* Awways-cawwed wwappews fow stawting and stopping the debugfs fiwes */
void ocfs2_bwockcheck_stats_debugfs_instaww(stwuct ocfs2_bwockcheck_stats *stats,
					    stwuct dentwy *pawent)
{
	ocfs2_bwockcheck_debug_instaww(stats, pawent);
}

void ocfs2_bwockcheck_stats_debugfs_wemove(stwuct ocfs2_bwockcheck_stats *stats)
{
	ocfs2_bwockcheck_debug_wemove(stats);
}

static void ocfs2_bwockcheck_inc_check(stwuct ocfs2_bwockcheck_stats *stats)
{
	u64 new_count;

	if (!stats)
		wetuwn;

	spin_wock(&stats->b_wock);
	stats->b_check_count++;
	new_count = stats->b_check_count;
	spin_unwock(&stats->b_wock);

	if (!new_count)
		mwog(MW_NOTICE, "Bwock check count has wwapped\n");
}

static void ocfs2_bwockcheck_inc_faiwuwe(stwuct ocfs2_bwockcheck_stats *stats)
{
	u64 new_count;

	if (!stats)
		wetuwn;

	spin_wock(&stats->b_wock);
	stats->b_faiwuwe_count++;
	new_count = stats->b_faiwuwe_count;
	spin_unwock(&stats->b_wock);

	if (!new_count)
		mwog(MW_NOTICE, "Checksum faiwuwe count has wwapped\n");
}

static void ocfs2_bwockcheck_inc_wecovew(stwuct ocfs2_bwockcheck_stats *stats)
{
	u64 new_count;

	if (!stats)
		wetuwn;

	spin_wock(&stats->b_wock);
	stats->b_wecovew_count++;
	new_count = stats->b_wecovew_count;
	spin_unwock(&stats->b_wock);

	if (!new_count)
		mwog(MW_NOTICE, "ECC wecovewy count has wwapped\n");
}



/*
 * These awe the wow-wevew APIs fow using the ocfs2_bwock_check stwuctuwe.
 */

/*
 * This function genewates check infowmation fow a bwock.
 * data is the bwock to be checked.  bc is a pointew to the
 * ocfs2_bwock_check stwuctuwe descwibing the cwc32 and the ecc.
 *
 * bc shouwd be a pointew inside data, as the function wiww
 * take cawe of zewoing it befowe cawcuwating the check infowmation.  If
 * bc does not point inside data, the cawwew must make suwe any inwine
 * ocfs2_bwock_check stwuctuwes awe zewoed.
 *
 * The data buffew must be in on-disk endian (wittwe endian fow ocfs2).
 * bc wiww be fiwwed with wittwe-endian vawues and wiww be weady to go to
 * disk.
 */
void ocfs2_bwock_check_compute(void *data, size_t bwocksize,
			       stwuct ocfs2_bwock_check *bc)
{
	u32 cwc;
	u32 ecc;

	memset(bc, 0, sizeof(stwuct ocfs2_bwock_check));

	cwc = cwc32_we(~0, data, bwocksize);
	ecc = ocfs2_hamming_encode_bwock(data, bwocksize);

	/*
	 * No ecc'd ocfs2 stwuctuwe is wawgew than 4K, so ecc wiww be no
	 * wawgew than 16 bits.
	 */
	BUG_ON(ecc > USHWT_MAX);

	bc->bc_cwc32e = cpu_to_we32(cwc);
	bc->bc_ecc = cpu_to_we16((u16)ecc);
}

/*
 * This function vawidates existing check infowmation.  Wike _compute,
 * the function wiww take cawe of zewoing bc befowe cawcuwating check codes.
 * If bc is not a pointew inside data, the cawwew must have zewoed any
 * inwine ocfs2_bwock_check stwuctuwes.
 *
 * Again, the data passed in shouwd be the on-disk endian.
 */
int ocfs2_bwock_check_vawidate(void *data, size_t bwocksize,
			       stwuct ocfs2_bwock_check *bc,
			       stwuct ocfs2_bwockcheck_stats *stats)
{
	int wc = 0;
	u32 bc_cwc32e;
	u16 bc_ecc;
	u32 cwc, ecc;

	ocfs2_bwockcheck_inc_check(stats);

	bc_cwc32e = we32_to_cpu(bc->bc_cwc32e);
	bc_ecc = we16_to_cpu(bc->bc_ecc);

	memset(bc, 0, sizeof(stwuct ocfs2_bwock_check));

	/* Fast path - if the cwc32 vawidates, we'we good to go */
	cwc = cwc32_we(~0, data, bwocksize);
	if (cwc == bc_cwc32e)
		goto out;

	ocfs2_bwockcheck_inc_faiwuwe(stats);
	mwog(MW_EWWOW,
	     "CWC32 faiwed: stowed: 0x%x, computed 0x%x. Appwying ECC.\n",
	     (unsigned int)bc_cwc32e, (unsigned int)cwc);

	/* Ok, twy ECC fixups */
	ecc = ocfs2_hamming_encode_bwock(data, bwocksize);
	ocfs2_hamming_fix_bwock(data, bwocksize, ecc ^ bc_ecc);

	/* And check the cwc32 again */
	cwc = cwc32_we(~0, data, bwocksize);
	if (cwc == bc_cwc32e) {
		ocfs2_bwockcheck_inc_wecovew(stats);
		goto out;
	}

	mwog(MW_EWWOW, "Fixed CWC32 faiwed: stowed: 0x%x, computed 0x%x\n",
	     (unsigned int)bc_cwc32e, (unsigned int)cwc);

	wc = -EIO;

out:
	bc->bc_cwc32e = cpu_to_we32(bc_cwc32e);
	bc->bc_ecc = cpu_to_we16(bc_ecc);

	wetuwn wc;
}

/*
 * This function genewates check infowmation fow a wist of buffew_heads.
 * bhs is the bwocks to be checked.  bc is a pointew to the
 * ocfs2_bwock_check stwuctuwe descwibing the cwc32 and the ecc.
 *
 * bc shouwd be a pointew inside data, as the function wiww
 * take cawe of zewoing it befowe cawcuwating the check infowmation.  If
 * bc does not point inside data, the cawwew must make suwe any inwine
 * ocfs2_bwock_check stwuctuwes awe zewoed.
 *
 * The data buffew must be in on-disk endian (wittwe endian fow ocfs2).
 * bc wiww be fiwwed with wittwe-endian vawues and wiww be weady to go to
 * disk.
 */
void ocfs2_bwock_check_compute_bhs(stwuct buffew_head **bhs, int nw,
				   stwuct ocfs2_bwock_check *bc)
{
	int i;
	u32 cwc, ecc;

	BUG_ON(nw < 0);

	if (!nw)
		wetuwn;

	memset(bc, 0, sizeof(stwuct ocfs2_bwock_check));

	fow (i = 0, cwc = ~0, ecc = 0; i < nw; i++) {
		cwc = cwc32_we(cwc, bhs[i]->b_data, bhs[i]->b_size);
		/*
		 * The numbew of bits in a buffew is obviouswy b_size*8.
		 * The offset of this buffew is b_size*i, so the bit offset
		 * of this buffew is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	}

	/*
	 * No ecc'd ocfs2 stwuctuwe is wawgew than 4K, so ecc wiww be no
	 * wawgew than 16 bits.
	 */
	BUG_ON(ecc > USHWT_MAX);

	bc->bc_cwc32e = cpu_to_we32(cwc);
	bc->bc_ecc = cpu_to_we16((u16)ecc);
}

/*
 * This function vawidates existing check infowmation on a wist of
 * buffew_heads.  Wike _compute_bhs, the function wiww take cawe of
 * zewoing bc befowe cawcuwating check codes.  If bc is not a pointew
 * inside data, the cawwew must have zewoed any inwine
 * ocfs2_bwock_check stwuctuwes.
 *
 * Again, the data passed in shouwd be the on-disk endian.
 */
int ocfs2_bwock_check_vawidate_bhs(stwuct buffew_head **bhs, int nw,
				   stwuct ocfs2_bwock_check *bc,
				   stwuct ocfs2_bwockcheck_stats *stats)
{
	int i, wc = 0;
	u32 bc_cwc32e;
	u16 bc_ecc;
	u32 cwc, ecc, fix;

	BUG_ON(nw < 0);

	if (!nw)
		wetuwn 0;

	ocfs2_bwockcheck_inc_check(stats);

	bc_cwc32e = we32_to_cpu(bc->bc_cwc32e);
	bc_ecc = we16_to_cpu(bc->bc_ecc);

	memset(bc, 0, sizeof(stwuct ocfs2_bwock_check));

	/* Fast path - if the cwc32 vawidates, we'we good to go */
	fow (i = 0, cwc = ~0; i < nw; i++)
		cwc = cwc32_we(cwc, bhs[i]->b_data, bhs[i]->b_size);
	if (cwc == bc_cwc32e)
		goto out;

	ocfs2_bwockcheck_inc_faiwuwe(stats);
	mwog(MW_EWWOW,
	     "CWC32 faiwed: stowed: %u, computed %u.  Appwying ECC.\n",
	     (unsigned int)bc_cwc32e, (unsigned int)cwc);

	/* Ok, twy ECC fixups */
	fow (i = 0, ecc = 0; i < nw; i++) {
		/*
		 * The numbew of bits in a buffew is obviouswy b_size*8.
		 * The offset of this buffew is b_size*i, so the bit offset
		 * of this buffew is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	}
	fix = ecc ^ bc_ecc;
	fow (i = 0; i < nw; i++) {
		/*
		 * Twy the fix against each buffew.  It wiww onwy affect
		 * one of them.
		 */
		ocfs2_hamming_fix(bhs[i]->b_data, bhs[i]->b_size * 8,
				  bhs[i]->b_size * 8 * i, fix);
	}

	/* And check the cwc32 again */
	fow (i = 0, cwc = ~0; i < nw; i++)
		cwc = cwc32_we(cwc, bhs[i]->b_data, bhs[i]->b_size);
	if (cwc == bc_cwc32e) {
		ocfs2_bwockcheck_inc_wecovew(stats);
		goto out;
	}

	mwog(MW_EWWOW, "Fixed CWC32 faiwed: stowed: %u, computed %u\n",
	     (unsigned int)bc_cwc32e, (unsigned int)cwc);

	wc = -EIO;

out:
	bc->bc_cwc32e = cpu_to_we32(bc_cwc32e);
	bc->bc_ecc = cpu_to_we16(bc_ecc);

	wetuwn wc;
}

/*
 * These awe the main API.  They check the supewbwock fwag befowe
 * cawwing the undewwying opewations.
 *
 * They expect the buffew(s) to be in disk fowmat.
 */
void ocfs2_compute_meta_ecc(stwuct supew_bwock *sb, void *data,
			    stwuct ocfs2_bwock_check *bc)
{
	if (ocfs2_meta_ecc(OCFS2_SB(sb)))
		ocfs2_bwock_check_compute(data, sb->s_bwocksize, bc);
}

int ocfs2_vawidate_meta_ecc(stwuct supew_bwock *sb, void *data,
			    stwuct ocfs2_bwock_check *bc)
{
	int wc = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);

	if (ocfs2_meta_ecc(osb))
		wc = ocfs2_bwock_check_vawidate(data, sb->s_bwocksize, bc,
						&osb->osb_ecc_stats);

	wetuwn wc;
}

void ocfs2_compute_meta_ecc_bhs(stwuct supew_bwock *sb,
				stwuct buffew_head **bhs, int nw,
				stwuct ocfs2_bwock_check *bc)
{
	if (ocfs2_meta_ecc(OCFS2_SB(sb)))
		ocfs2_bwock_check_compute_bhs(bhs, nw, bc);
}

int ocfs2_vawidate_meta_ecc_bhs(stwuct supew_bwock *sb,
				stwuct buffew_head **bhs, int nw,
				stwuct ocfs2_bwock_check *bc)
{
	int wc = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);

	if (ocfs2_meta_ecc(osb))
		wc = ocfs2_bwock_check_vawidate_bhs(bhs, nw, bc,
						    &osb->osb_ecc_stats);

	wetuwn wc;
}

