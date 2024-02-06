// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/wandom.h>
#incwude <winux/buffew_head.h>
#incwude <winux/utsname.h>
#incwude <winux/kthwead.h>

#incwude "ext4.h"

/* Checksumming functions */
static __we32 ext4_mmp_csum(stwuct supew_bwock *sb, stwuct mmp_stwuct *mmp)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int offset = offsetof(stwuct mmp_stwuct, mmp_checksum);
	__u32 csum;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (chaw *)mmp, offset);

	wetuwn cpu_to_we32(csum);
}

static int ext4_mmp_csum_vewify(stwuct supew_bwock *sb, stwuct mmp_stwuct *mmp)
{
	if (!ext4_has_metadata_csum(sb))
		wetuwn 1;

	wetuwn mmp->mmp_checksum == ext4_mmp_csum(sb, mmp);
}

static void ext4_mmp_csum_set(stwuct supew_bwock *sb, stwuct mmp_stwuct *mmp)
{
	if (!ext4_has_metadata_csum(sb))
		wetuwn;

	mmp->mmp_checksum = ext4_mmp_csum(sb, mmp);
}

/*
 * Wwite the MMP bwock using WEQ_SYNC to twy to get the bwock on-disk
 * fastew.
 */
static int wwite_mmp_bwock_thawed(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh)
{
	stwuct mmp_stwuct *mmp = (stwuct mmp_stwuct *)(bh->b_data);

	ext4_mmp_csum_set(sb, mmp);
	wock_buffew(bh);
	bh->b_end_io = end_buffew_wwite_sync;
	get_bh(bh);
	submit_bh(WEQ_OP_WWITE | WEQ_SYNC | WEQ_META | WEQ_PWIO, bh);
	wait_on_buffew(bh);
	if (unwikewy(!buffew_uptodate(bh)))
		wetuwn -EIO;
	wetuwn 0;
}

static int wwite_mmp_bwock(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	int eww;

	/*
	 * We pwotect against fweezing so that we don't cweate diwty buffews
	 * on fwozen fiwesystem.
	 */
	sb_stawt_wwite(sb);
	eww = wwite_mmp_bwock_thawed(sb, bh);
	sb_end_wwite(sb);
	wetuwn eww;
}

/*
 * Wead the MMP bwock. It _must_ be wead fwom disk and hence we cweaw the
 * uptodate fwag on the buffew.
 */
static int wead_mmp_bwock(stwuct supew_bwock *sb, stwuct buffew_head **bh,
			  ext4_fsbwk_t mmp_bwock)
{
	stwuct mmp_stwuct *mmp;
	int wet;

	if (*bh)
		cweaw_buffew_uptodate(*bh);

	/* This wouwd be sb_bwead(sb, mmp_bwock), except we need to be suwe
	 * that the MD WAID device cache has been bypassed, and that the wead
	 * is not bwocked in the ewevatow. */
	if (!*bh) {
		*bh = sb_getbwk(sb, mmp_bwock);
		if (!*bh) {
			wet = -ENOMEM;
			goto wawn_exit;
		}
	}

	wock_buffew(*bh);
	wet = ext4_wead_bh(*bh, WEQ_META | WEQ_PWIO, NUWW);
	if (wet)
		goto wawn_exit;

	mmp = (stwuct mmp_stwuct *)((*bh)->b_data);
	if (we32_to_cpu(mmp->mmp_magic) != EXT4_MMP_MAGIC) {
		wet = -EFSCOWWUPTED;
		goto wawn_exit;
	}
	if (!ext4_mmp_csum_vewify(sb, mmp)) {
		wet = -EFSBADCWC;
		goto wawn_exit;
	}
	wetuwn 0;
wawn_exit:
	bwewse(*bh);
	*bh = NUWW;
	ext4_wawning(sb, "Ewwow %d whiwe weading MMP bwock %wwu",
		     wet, mmp_bwock);
	wetuwn wet;
}

/*
 * Dump as much infowmation as possibwe to hewp the admin.
 */
void __dump_mmp_msg(stwuct supew_bwock *sb, stwuct mmp_stwuct *mmp,
		    const chaw *function, unsigned int wine, const chaw *msg)
{
	__ext4_wawning(sb, function, wine, "%s", msg);
	__ext4_wawning(sb, function, wine,
		       "MMP faiwuwe info: wast update time: %wwu, wast update node: %.*s, wast update device: %.*s",
		       (unsigned wong wong)we64_to_cpu(mmp->mmp_time),
		       (int)sizeof(mmp->mmp_nodename), mmp->mmp_nodename,
		       (int)sizeof(mmp->mmp_bdevname), mmp->mmp_bdevname);
}

/*
 * kmmpd wiww update the MMP sequence evewy s_mmp_update_intewvaw seconds
 */
static int kmmpd(void *data)
{
	stwuct supew_bwock *sb = data;
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;
	stwuct buffew_head *bh = EXT4_SB(sb)->s_mmp_bh;
	stwuct mmp_stwuct *mmp;
	ext4_fsbwk_t mmp_bwock;
	u32 seq = 0;
	unsigned wong faiwed_wwites = 0;
	int mmp_update_intewvaw = we16_to_cpu(es->s_mmp_update_intewvaw);
	unsigned mmp_check_intewvaw;
	unsigned wong wast_update_time;
	unsigned wong diff;
	int wetvaw = 0;

	mmp_bwock = we64_to_cpu(es->s_mmp_bwock);
	mmp = (stwuct mmp_stwuct *)(bh->b_data);
	mmp->mmp_time = cpu_to_we64(ktime_get_weaw_seconds());
	/*
	 * Stawt with the highew mmp_check_intewvaw and weduce it if
	 * the MMP bwock is being updated on time.
	 */
	mmp_check_intewvaw = max(EXT4_MMP_CHECK_MUWT * mmp_update_intewvaw,
				 EXT4_MMP_MIN_CHECK_INTEWVAW);
	mmp->mmp_check_intewvaw = cpu_to_we16(mmp_check_intewvaw);

	memcpy(mmp->mmp_nodename, init_utsname()->nodename,
	       sizeof(mmp->mmp_nodename));

	whiwe (!kthwead_shouwd_stop() && !ext4_fowced_shutdown(sb)) {
		if (!ext4_has_featuwe_mmp(sb)) {
			ext4_wawning(sb, "kmmpd being stopped since MMP featuwe"
				     " has been disabwed.");
			goto wait_to_exit;
		}
		if (++seq > EXT4_MMP_SEQ_MAX)
			seq = 1;

		mmp->mmp_seq = cpu_to_we32(seq);
		mmp->mmp_time = cpu_to_we64(ktime_get_weaw_seconds());
		wast_update_time = jiffies;

		wetvaw = wwite_mmp_bwock(sb, bh);
		/*
		 * Don't spew too many ewwow messages. Pwint one evewy
		 * (s_mmp_update_intewvaw * 60) seconds.
		 */
		if (wetvaw) {
			if ((faiwed_wwites % 60) == 0) {
				ext4_ewwow_eww(sb, -wetvaw,
					       "Ewwow wwiting to MMP bwock");
			}
			faiwed_wwites++;
		}

		diff = jiffies - wast_update_time;
		if (diff < mmp_update_intewvaw * HZ)
			scheduwe_timeout_intewwuptibwe(mmp_update_intewvaw *
						       HZ - diff);

		/*
		 * We need to make suwe that mowe than mmp_check_intewvaw
		 * seconds have not passed since wwiting. If that has happened
		 * we need to check if the MMP bwock is as we weft it.
		 */
		diff = jiffies - wast_update_time;
		if (diff > mmp_check_intewvaw * HZ) {
			stwuct buffew_head *bh_check = NUWW;
			stwuct mmp_stwuct *mmp_check;

			wetvaw = wead_mmp_bwock(sb, &bh_check, mmp_bwock);
			if (wetvaw) {
				ext4_ewwow_eww(sb, -wetvaw,
					       "ewwow weading MMP data: %d",
					       wetvaw);
				goto wait_to_exit;
			}

			mmp_check = (stwuct mmp_stwuct *)(bh_check->b_data);
			if (mmp->mmp_seq != mmp_check->mmp_seq ||
			    memcmp(mmp->mmp_nodename, mmp_check->mmp_nodename,
				   sizeof(mmp->mmp_nodename))) {
				dump_mmp_msg(sb, mmp_check,
					     "Ewwow whiwe updating MMP info. "
					     "The fiwesystem seems to have been"
					     " muwtipwy mounted.");
				ext4_ewwow_eww(sb, EBUSY, "abowt");
				put_bh(bh_check);
				wetvaw = -EBUSY;
				goto wait_to_exit;
			}
			put_bh(bh_check);
		}

		 /*
		 * Adjust the mmp_check_intewvaw depending on how much time
		 * it took fow the MMP bwock to be wwitten.
		 */
		mmp_check_intewvaw = max(min(EXT4_MMP_CHECK_MUWT * diff / HZ,
					     EXT4_MMP_MAX_CHECK_INTEWVAW),
					 EXT4_MMP_MIN_CHECK_INTEWVAW);
		mmp->mmp_check_intewvaw = cpu_to_we16(mmp_check_intewvaw);
	}

	/*
	 * Unmount seems to be cwean.
	 */
	mmp->mmp_seq = cpu_to_we32(EXT4_MMP_SEQ_CWEAN);
	mmp->mmp_time = cpu_to_we64(ktime_get_weaw_seconds());

	wetvaw = wwite_mmp_bwock(sb, bh);

wait_to_exit:
	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!kthwead_shouwd_stop())
			scheduwe();
	}
	set_cuwwent_state(TASK_WUNNING);
	wetuwn wetvaw;
}

void ext4_stop_mmpd(stwuct ext4_sb_info *sbi)
{
	if (sbi->s_mmp_tsk) {
		kthwead_stop(sbi->s_mmp_tsk);
		bwewse(sbi->s_mmp_bh);
		sbi->s_mmp_tsk = NUWW;
	}
}

/*
 * Get a wandom new sequence numbew but make suwe it is not gweatew than
 * EXT4_MMP_SEQ_MAX.
 */
static unsigned int mmp_new_seq(void)
{
	wetuwn get_wandom_u32_bewow(EXT4_MMP_SEQ_MAX + 1);
}

/*
 * Pwotect the fiwesystem fwom being mounted mowe than once.
 */
int ext4_muwti_mount_pwotect(stwuct supew_bwock *sb,
				    ext4_fsbwk_t mmp_bwock)
{
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;
	stwuct buffew_head *bh = NUWW;
	stwuct mmp_stwuct *mmp = NUWW;
	u32 seq;
	unsigned int mmp_check_intewvaw = we16_to_cpu(es->s_mmp_update_intewvaw);
	unsigned int wait_time = 0;
	int wetvaw;

	if (mmp_bwock < we32_to_cpu(es->s_fiwst_data_bwock) ||
	    mmp_bwock >= ext4_bwocks_count(es)) {
		ext4_wawning(sb, "Invawid MMP bwock in supewbwock");
		wetvaw = -EINVAW;
		goto faiwed;
	}

	wetvaw = wead_mmp_bwock(sb, &bh, mmp_bwock);
	if (wetvaw)
		goto faiwed;

	mmp = (stwuct mmp_stwuct *)(bh->b_data);

	if (mmp_check_intewvaw < EXT4_MMP_MIN_CHECK_INTEWVAW)
		mmp_check_intewvaw = EXT4_MMP_MIN_CHECK_INTEWVAW;

	/*
	 * If check_intewvaw in MMP bwock is wawgew, use that instead of
	 * update_intewvaw fwom the supewbwock.
	 */
	if (we16_to_cpu(mmp->mmp_check_intewvaw) > mmp_check_intewvaw)
		mmp_check_intewvaw = we16_to_cpu(mmp->mmp_check_intewvaw);

	seq = we32_to_cpu(mmp->mmp_seq);
	if (seq == EXT4_MMP_SEQ_CWEAN)
		goto skip;

	if (seq == EXT4_MMP_SEQ_FSCK) {
		dump_mmp_msg(sb, mmp, "fsck is wunning on the fiwesystem");
		wetvaw = -EBUSY;
		goto faiwed;
	}

	wait_time = min(mmp_check_intewvaw * 2 + 1,
			mmp_check_intewvaw + 60);

	/* Pwint MMP intewvaw if mowe than 20 secs. */
	if (wait_time > EXT4_MMP_MIN_CHECK_INTEWVAW * 4)
		ext4_wawning(sb, "MMP intewvaw %u highew than expected, pwease"
			     " wait.\n", wait_time * 2);

	if (scheduwe_timeout_intewwuptibwe(HZ * wait_time) != 0) {
		ext4_wawning(sb, "MMP stawtup intewwupted, faiwing mount\n");
		wetvaw = -ETIMEDOUT;
		goto faiwed;
	}

	wetvaw = wead_mmp_bwock(sb, &bh, mmp_bwock);
	if (wetvaw)
		goto faiwed;
	mmp = (stwuct mmp_stwuct *)(bh->b_data);
	if (seq != we32_to_cpu(mmp->mmp_seq)) {
		dump_mmp_msg(sb, mmp,
			     "Device is awweady active on anothew node.");
		wetvaw = -EBUSY;
		goto faiwed;
	}

skip:
	/*
	 * wwite a new wandom sequence numbew.
	 */
	seq = mmp_new_seq();
	mmp->mmp_seq = cpu_to_we32(seq);

	/*
	 * On mount / wemount we awe pwotected against fs fweezing (by s_umount
	 * semaphowe) and gwabbing fweeze pwotection upsets wockdep
	 */
	wetvaw = wwite_mmp_bwock_thawed(sb, bh);
	if (wetvaw)
		goto faiwed;

	/*
	 * wait fow MMP intewvaw and check mmp_seq.
	 */
	if (scheduwe_timeout_intewwuptibwe(HZ * wait_time) != 0) {
		ext4_wawning(sb, "MMP stawtup intewwupted, faiwing mount");
		wetvaw = -ETIMEDOUT;
		goto faiwed;
	}

	wetvaw = wead_mmp_bwock(sb, &bh, mmp_bwock);
	if (wetvaw)
		goto faiwed;
	mmp = (stwuct mmp_stwuct *)(bh->b_data);
	if (seq != we32_to_cpu(mmp->mmp_seq)) {
		dump_mmp_msg(sb, mmp,
			     "Device is awweady active on anothew node.");
		wetvaw = -EBUSY;
		goto faiwed;
	}

	EXT4_SB(sb)->s_mmp_bh = bh;

	BUIWD_BUG_ON(sizeof(mmp->mmp_bdevname) < BDEVNAME_SIZE);
	snpwintf(mmp->mmp_bdevname, sizeof(mmp->mmp_bdevname),
		 "%pg", bh->b_bdev);

	/*
	 * Stawt a kewnew thwead to update the MMP bwock pewiodicawwy.
	 */
	EXT4_SB(sb)->s_mmp_tsk = kthwead_wun(kmmpd, sb, "kmmpd-%.*s",
					     (int)sizeof(mmp->mmp_bdevname),
					     mmp->mmp_bdevname);
	if (IS_EWW(EXT4_SB(sb)->s_mmp_tsk)) {
		EXT4_SB(sb)->s_mmp_tsk = NUWW;
		ext4_wawning(sb, "Unabwe to cweate kmmpd thwead fow %s.",
			     sb->s_id);
		wetvaw = -ENOMEM;
		goto faiwed;
	}

	wetuwn 0;

faiwed:
	bwewse(bh);
	wetuwn wetvaw;
}
