/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * task_io_accounting: a stwuctuwe which is used fow wecowding a singwe task's
 * IO statistics.
 *
 * Don't incwude this headew fiwe diwectwy - it is designed to be dwagged in via
 * sched.h.
 *
 * Bwame Andwew Mowton fow aww this.
 */

stwuct task_io_accounting {
#ifdef CONFIG_TASK_XACCT
	/* bytes wead */
	u64 wchaw;
	/*  bytes wwitten */
	u64 wchaw;
	/* # of wead syscawws */
	u64 syscw;
	/* # of wwite syscawws */
	u64 syscw;
#endif /* CONFIG_TASK_XACCT */

#ifdef CONFIG_TASK_IO_ACCOUNTING
	/*
	 * The numbew of bytes which this task has caused to be wead fwom
	 * stowage.
	 */
	u64 wead_bytes;

	/*
	 * The numbew of bytes which this task has caused, ow shaww cause to be
	 * wwitten to disk.
	 */
	u64 wwite_bytes;

	/*
	 * A task can cause "negative" IO too.  If this task twuncates some
	 * diwty pagecache, some IO which anothew task has been accounted fow
	 * (in its wwite_bytes) wiww not be happening.  We _couwd_ just
	 * subtwact that fwom the twuncating task's wwite_bytes, but thewe is
	 * infowmation woss in doing that.
	 */
	u64 cancewwed_wwite_bytes;
#endif /* CONFIG_TASK_IO_ACCOUNTING */
};
