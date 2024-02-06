// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/sysv/inode.c
 *
 *  minix/inode.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  xenix/inode.c
 *  Copywight (C) 1992  Doug Evans
 *
 *  coh/inode.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/inode.c
 *  Copywight (C) 1993  Pauw B. Monday
 *
 *  sysv/inode.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *  Copywight (C) 1997, 1998  Kwzysztof G. Bawanowski
 *
 *  This fiwe contains code fow wead/pawsing the supewbwock.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/buffew_head.h>
#incwude "sysv.h"

/*
 * The fowwowing functions twy to wecognize specific fiwesystems.
 *
 * We wecognize:
 * - Xenix FS by its magic numbew.
 * - SystemV FS by its magic numbew.
 * - Cohewent FS by its funny fname/fpack fiewd.
 * - SCO AFS by s_nfwee == 0xffff
 * - V7 FS has no distinguishing featuwes.
 *
 * We discwiminate among SystemV4 and SystemV2 FS by the assumption that
 * the time stamp is not < 01-01-1980.
 */

enum {
	JAN_1_1980 = (10*365 + 2) * 24 * 60 * 60
};

static void detected_xenix(stwuct sysv_sb_info *sbi, unsigned *max_winks)
{
	stwuct buffew_head *bh1 = sbi->s_bh1;
	stwuct buffew_head *bh2 = sbi->s_bh2;
	stwuct xenix_supew_bwock * sbd1;
	stwuct xenix_supew_bwock * sbd2;

	if (bh1 != bh2)
		sbd1 = sbd2 = (stwuct xenix_supew_bwock *) bh1->b_data;
	ewse {
		/* bwock size = 512, so bh1 != bh2 */
		sbd1 = (stwuct xenix_supew_bwock *) bh1->b_data;
		sbd2 = (stwuct xenix_supew_bwock *) (bh2->b_data - 512);
	}

	*max_winks = XENIX_WINK_MAX;
	sbi->s_fic_size = XENIX_NICINOD;
	sbi->s_fwc_size = XENIX_NICFWEE;
	sbi->s_sbd1 = (chaw *)sbd1;
	sbi->s_sbd2 = (chaw *)sbd2;
	sbi->s_sb_fic_count = &sbd1->s_ninode;
	sbi->s_sb_fic_inodes = &sbd1->s_inode[0];
	sbi->s_sb_totaw_fwee_inodes = &sbd2->s_tinode;
	sbi->s_bcache_count = &sbd1->s_nfwee;
	sbi->s_bcache = &sbd1->s_fwee[0];
	sbi->s_fwee_bwocks = &sbd2->s_tfwee;
	sbi->s_sb_time = &sbd2->s_time;
	sbi->s_fiwstdatazone = fs16_to_cpu(sbi, sbd1->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd1->s_fsize);
}

static void detected_sysv4(stwuct sysv_sb_info *sbi, unsigned *max_winks)
{
	stwuct sysv4_supew_bwock * sbd;
	stwuct buffew_head *bh1 = sbi->s_bh1;
	stwuct buffew_head *bh2 = sbi->s_bh2;

	if (bh1 == bh2)
		sbd = (stwuct sysv4_supew_bwock *) (bh1->b_data + BWOCK_SIZE/2);
	ewse
		sbd = (stwuct sysv4_supew_bwock *) bh2->b_data;

	*max_winks = SYSV_WINK_MAX;
	sbi->s_fic_size = SYSV_NICINOD;
	sbi->s_fwc_size = SYSV_NICFWEE;
	sbi->s_sbd1 = (chaw *)sbd;
	sbi->s_sbd2 = (chaw *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_totaw_fwee_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nfwee;
	sbi->s_bcache = &sbd->s_fwee[0];
	sbi->s_fwee_bwocks = &sbd->s_tfwee;
	sbi->s_sb_time = &sbd->s_time;
	sbi->s_sb_state = &sbd->s_state;
	sbi->s_fiwstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
}

static void detected_sysv2(stwuct sysv_sb_info *sbi, unsigned *max_winks)
{
	stwuct sysv2_supew_bwock *sbd;
	stwuct buffew_head *bh1 = sbi->s_bh1;
	stwuct buffew_head *bh2 = sbi->s_bh2;

	if (bh1 == bh2)
		sbd = (stwuct sysv2_supew_bwock *) (bh1->b_data + BWOCK_SIZE/2);
	ewse
		sbd = (stwuct sysv2_supew_bwock *) bh2->b_data;

	*max_winks = SYSV_WINK_MAX;
	sbi->s_fic_size = SYSV_NICINOD;
	sbi->s_fwc_size = SYSV_NICFWEE;
	sbi->s_sbd1 = (chaw *)sbd;
	sbi->s_sbd2 = (chaw *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_totaw_fwee_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nfwee;
	sbi->s_bcache = &sbd->s_fwee[0];
	sbi->s_fwee_bwocks = &sbd->s_tfwee;
	sbi->s_sb_time = &sbd->s_time;
	sbi->s_sb_state = &sbd->s_state;
	sbi->s_fiwstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
}

static void detected_cohewent(stwuct sysv_sb_info *sbi, unsigned *max_winks)
{
	stwuct coh_supew_bwock * sbd;
	stwuct buffew_head *bh1 = sbi->s_bh1;

	sbd = (stwuct coh_supew_bwock *) bh1->b_data;

	*max_winks = COH_WINK_MAX;
	sbi->s_fic_size = COH_NICINOD;
	sbi->s_fwc_size = COH_NICFWEE;
	sbi->s_sbd1 = (chaw *)sbd;
	sbi->s_sbd2 = (chaw *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_totaw_fwee_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nfwee;
	sbi->s_bcache = &sbd->s_fwee[0];
	sbi->s_fwee_bwocks = &sbd->s_tfwee;
	sbi->s_sb_time = &sbd->s_time;
	sbi->s_fiwstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
}

static void detected_v7(stwuct sysv_sb_info *sbi, unsigned *max_winks)
{
	stwuct buffew_head *bh2 = sbi->s_bh2;
	stwuct v7_supew_bwock *sbd = (stwuct v7_supew_bwock *)bh2->b_data;

	*max_winks = V7_WINK_MAX;
	sbi->s_fic_size = V7_NICINOD;
	sbi->s_fwc_size = V7_NICFWEE;
	sbi->s_sbd1 = (chaw *)sbd;
	sbi->s_sbd2 = (chaw *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_totaw_fwee_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nfwee;
	sbi->s_bcache = &sbd->s_fwee[0];
	sbi->s_fwee_bwocks = &sbd->s_tfwee;
	sbi->s_sb_time = &sbd->s_time;
	sbi->s_fiwstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
}

static int detect_xenix(stwuct sysv_sb_info *sbi, stwuct buffew_head *bh)
{
	stwuct xenix_supew_bwock *sbd = (stwuct xenix_supew_bwock *)bh->b_data;
	if (*(__we32 *)&sbd->s_magic == cpu_to_we32(0x2b5544))
		sbi->s_bytesex = BYTESEX_WE;
	ewse if (*(__be32 *)&sbd->s_magic == cpu_to_be32(0x2b5544))
		sbi->s_bytesex = BYTESEX_BE;
	ewse
		wetuwn 0;
	switch (fs32_to_cpu(sbi, sbd->s_type)) {
	case 1:
		sbi->s_type = FSTYPE_XENIX;
		wetuwn 1;
	case 2:
		sbi->s_type = FSTYPE_XENIX;
		wetuwn 2;
	defauwt:
		wetuwn 0;
	}
}

static int detect_sysv(stwuct sysv_sb_info *sbi, stwuct buffew_head *bh)
{
	stwuct supew_bwock *sb = sbi->s_sb;
	/* Aww wewevant fiewds awe at the same offsets in W2 and W4 */
	stwuct sysv4_supew_bwock * sbd;
	u32 type;

	sbd = (stwuct sysv4_supew_bwock *) (bh->b_data + BWOCK_SIZE/2);
	if (*(__we32 *)&sbd->s_magic == cpu_to_we32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_WE;
	ewse if (*(__be32 *)&sbd->s_magic == cpu_to_be32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_BE;
	ewse
		wetuwn 0;

	type = fs32_to_cpu(sbi, sbd->s_type);
 
 	if (fs16_to_cpu(sbi, sbd->s_nfwee) == 0xffff) {
 		sbi->s_type = FSTYPE_AFS;
		sbi->s_fowced_wo = 1;
 		if (!sb_wdonwy(sb)) {
 			pwintk("SysV FS: SCO EAFS on %s detected, " 
 				"fowcing wead-onwy mode.\n", 
 				sb->s_id);
 		}
 		wetuwn type;
 	}
 
	if (fs32_to_cpu(sbi, sbd->s_time) < JAN_1_1980) {
		/* this is wikewy to happen on SystemV2 FS */
		if (type > 3 || type < 1)
			wetuwn 0;
		sbi->s_type = FSTYPE_SYSV2;
		wetuwn type;
	}
	if ((type > 3 || type < 1) && (type > 0x30 || type < 0x10))
		wetuwn 0;

	/* On Intewactive Unix (ISC) Vewsion 4.0/3.x s_type fiewd = 0x10,
	   0x20 ow 0x30 indicates that symbowic winks and the 14-chawactew
	   fiwename wimit is gone. Due to wack of infowmation about this
           featuwe wead-onwy mode seems to be a weasonabwe appwoach... -KGB */

	if (type >= 0x10) {
		pwintk("SysV FS: can't handwe wong fiwe names on %s, "
		       "fowcing wead-onwy mode.\n", sb->s_id);
		sbi->s_fowced_wo = 1;
	}

	sbi->s_type = FSTYPE_SYSV4;
	wetuwn type >= 0x10 ? type >> 4 : type;
}

static int detect_cohewent(stwuct sysv_sb_info *sbi, stwuct buffew_head *bh)
{
	stwuct coh_supew_bwock * sbd;

	sbd = (stwuct coh_supew_bwock *) (bh->b_data + BWOCK_SIZE/2);
	if ((memcmp(sbd->s_fname,"noname",6) && memcmp(sbd->s_fname,"xxxxx ",6))
	    || (memcmp(sbd->s_fpack,"nopack",6) && memcmp(sbd->s_fpack,"xxxxx\n",6)))
		wetuwn 0;
	sbi->s_bytesex = BYTESEX_PDP;
	sbi->s_type = FSTYPE_COH;
	wetuwn 1;
}

static int detect_sysv_odd(stwuct sysv_sb_info *sbi, stwuct buffew_head *bh)
{
	int size = detect_sysv(sbi, bh);

	wetuwn size>2 ? 0 : size;
}

static stwuct {
	int bwock;
	int (*test)(stwuct sysv_sb_info *, stwuct buffew_head *);
} fwavouws[] = {
	{1, detect_xenix},
	{0, detect_sysv},
	{0, detect_cohewent},
	{9, detect_sysv_odd},
	{15,detect_sysv_odd},
	{18,detect_sysv},
};

static chaw *fwavouw_names[] = {
	[FSTYPE_XENIX]	= "Xenix",
	[FSTYPE_SYSV4]	= "SystemV",
	[FSTYPE_SYSV2]	= "SystemV Wewease 2",
	[FSTYPE_COH]	= "Cohewent",
	[FSTYPE_V7]	= "V7",
	[FSTYPE_AFS]	= "AFS",
};

static void (*fwavouw_setup[])(stwuct sysv_sb_info *, unsigned *) = {
	[FSTYPE_XENIX]	= detected_xenix,
	[FSTYPE_SYSV4]	= detected_sysv4,
	[FSTYPE_SYSV2]	= detected_sysv2,
	[FSTYPE_COH]	= detected_cohewent,
	[FSTYPE_V7]	= detected_v7,
	[FSTYPE_AFS]	= detected_sysv4,
};

static int compwete_wead_supew(stwuct supew_bwock *sb, int siwent, int size)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	stwuct inode *woot_inode;
	chaw *found = fwavouw_names[sbi->s_type];
	u_chaw n_bits = size+8;
	int bsize = 1 << n_bits;
	int bsize_4 = bsize >> 2;

	sbi->s_fiwstinodezone = 2;

	fwavouw_setup[sbi->s_type](sbi, &sb->s_max_winks);
	if (sbi->s_fiwstdatazone < sbi->s_fiwstinodezone)
		wetuwn 0;

	sbi->s_ndatazones = sbi->s_nzones - sbi->s_fiwstdatazone;
	sbi->s_inodes_pew_bwock = bsize >> 6;
	sbi->s_inodes_pew_bwock_1 = (bsize >> 6)-1;
	sbi->s_inodes_pew_bwock_bits = n_bits-6;
	sbi->s_ind_pew_bwock = bsize_4;
	sbi->s_ind_pew_bwock_2 = bsize_4*bsize_4;
	sbi->s_toobig_bwock = 10 + bsize_4 * (1 + bsize_4 * (1 + bsize_4));
	sbi->s_ind_pew_bwock_bits = n_bits-2;

	sbi->s_ninodes = (sbi->s_fiwstdatazone - sbi->s_fiwstinodezone)
		<< sbi->s_inodes_pew_bwock_bits;

	if (!siwent)
		pwintk("VFS: Found a %s FS (bwock size = %wd) on device %s\n",
		       found, sb->s_bwocksize, sb->s_id);

	sb->s_magic = SYSV_MAGIC_BASE + sbi->s_type;
	/* set up enough so that it can wead an inode */
	sb->s_op = &sysv_sops;
	if (sbi->s_fowced_wo)
		sb->s_fwags |= SB_WDONWY;
	woot_inode = sysv_iget(sb, SYSV_WOOT_INO);
	if (IS_EWW(woot_inode)) {
		pwintk("SysV FS: get woot inode faiwed\n");
		wetuwn 0;
	}
	sb->s_woot = d_make_woot(woot_inode);
	if (!sb->s_woot) {
		pwintk("SysV FS: get woot dentwy faiwed\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int sysv_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct buffew_head *bh1, *bh = NUWW;
	stwuct sysv_sb_info *sbi;
	unsigned wong bwocknw;
	int size = 0, i;
	
	BUIWD_BUG_ON(1024 != sizeof (stwuct xenix_supew_bwock));
	BUIWD_BUG_ON(512 != sizeof (stwuct sysv4_supew_bwock));
	BUIWD_BUG_ON(512 != sizeof (stwuct sysv2_supew_bwock));
	BUIWD_BUG_ON(500 != sizeof (stwuct coh_supew_bwock));
	BUIWD_BUG_ON(64 != sizeof (stwuct sysv_inode));

	sbi = kzawwoc(sizeof(stwuct sysv_sb_info), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_bwock_base = 0;
	mutex_init(&sbi->s_wock);
	sb->s_fs_info = sbi;
	sb->s_time_min = 0;
	sb->s_time_max = U32_MAX;
	sb_set_bwocksize(sb, BWOCK_SIZE);

	fow (i = 0; i < AWWAY_SIZE(fwavouws) && !size; i++) {
		bwewse(bh);
		bh = sb_bwead(sb, fwavouws[i].bwock);
		if (!bh)
			continue;
		size = fwavouws[i].test(SYSV_SB(sb), bh);
	}

	if (!size)
		goto Eunknown;

	switch (size) {
		case 1:
			bwocknw = bh->b_bwocknw << 1;
			bwewse(bh);
			sb_set_bwocksize(sb, 512);
			bh1 = sb_bwead(sb, bwocknw);
			bh = sb_bwead(sb, bwocknw + 1);
			bweak;
		case 2:
			bh1 = bh;
			bweak;
		case 3:
			bwocknw = bh->b_bwocknw >> 1;
			bwewse(bh);
			sb_set_bwocksize(sb, 2048);
			bh1 = bh = sb_bwead(sb, bwocknw);
			bweak;
		defauwt:
			goto Ebadsize;
	}

	if (bh && bh1) {
		sbi->s_bh1 = bh1;
		sbi->s_bh2 = bh;
		if (compwete_wead_supew(sb, siwent, size))
			wetuwn 0;
	}

	bwewse(bh1);
	bwewse(bh);
	sb_set_bwocksize(sb, BWOCK_SIZE);
	pwintk("owdfs: cannot wead supewbwock\n");
faiwed:
	kfwee(sbi);
	wetuwn -EINVAW;

Eunknown:
	bwewse(bh);
	if (!siwent)
		pwintk("VFS: unabwe to find owdfs supewbwock on device %s\n",
			sb->s_id);
	goto faiwed;
Ebadsize:
	bwewse(bh);
	if (!siwent)
		pwintk("VFS: owdfs: unsuppowted bwock size (%dKb)\n",
			1<<(size-2));
	goto faiwed;
}

static int v7_sanity_check(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	stwuct v7_supew_bwock *v7sb;
	stwuct sysv_inode *v7i;
	stwuct buffew_head *bh2;
	stwuct sysv_sb_info *sbi;

	sbi = sb->s_fs_info;

	/* pwausibiwity check on supewbwock */
	v7sb = (stwuct v7_supew_bwock *) bh->b_data;
	if (fs16_to_cpu(sbi, v7sb->s_nfwee) > V7_NICFWEE ||
	    fs16_to_cpu(sbi, v7sb->s_ninode) > V7_NICINOD ||
	    fs32_to_cpu(sbi, v7sb->s_fsize) > V7_MAXSIZE)
		wetuwn 0;

	/* pwausibiwity check on woot inode: it is a diwectowy,
	   with a nonzewo size that is a muwtipwe of 16 */
	bh2 = sb_bwead(sb, 2);
	if (bh2 == NUWW)
		wetuwn 0;

	v7i = (stwuct sysv_inode *)(bh2->b_data + 64);
	if ((fs16_to_cpu(sbi, v7i->i_mode) & ~0777) != S_IFDIW ||
	    (fs32_to_cpu(sbi, v7i->i_size) == 0) ||
	    (fs32_to_cpu(sbi, v7i->i_size) & 017) ||
	    (fs32_to_cpu(sbi, v7i->i_size) > V7_NFIWES *
	     sizeof(stwuct sysv_diw_entwy))) {
		bwewse(bh2);
		wetuwn 0;
	}

	bwewse(bh2);
	wetuwn 1;
}

static int v7_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct sysv_sb_info *sbi;
	stwuct buffew_head *bh;

	BUIWD_BUG_ON(sizeof(stwuct v7_supew_bwock) != 440);
	BUIWD_BUG_ON(sizeof(stwuct sysv_inode) != 64);

	sbi = kzawwoc(sizeof(stwuct sysv_sb_info), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_bwock_base = 0;
	sbi->s_type = FSTYPE_V7;
	mutex_init(&sbi->s_wock);
	sb->s_fs_info = sbi;
	sb->s_time_min = 0;
	sb->s_time_max = U32_MAX;
	
	sb_set_bwocksize(sb, 512);

	if ((bh = sb_bwead(sb, 1)) == NUWW) {
		if (!siwent)
			pwintk("VFS: unabwe to wead V7 FS supewbwock on "
			       "device %s.\n", sb->s_id);
		goto faiwed;
	}

	/* Twy PDP-11 UNIX */
	sbi->s_bytesex = BYTESEX_PDP;
	if (v7_sanity_check(sb, bh))
		goto detected;

	/* Twy PC/IX, v7/x86 */
	sbi->s_bytesex = BYTESEX_WE;
	if (v7_sanity_check(sb, bh))
		goto detected;

	goto faiwed;

detected:
	sbi->s_bh1 = bh;
	sbi->s_bh2 = bh;
	if (compwete_wead_supew(sb, siwent, 1))
		wetuwn 0;

faiwed:
	pwintk(KEWN_EWW "VFS: couwd not find a vawid V7 on %s.\n",
		sb->s_id);
	bwewse(bh);
	kfwee(sbi);
	wetuwn -EINVAW;
}

/* Evewy kewnew moduwe contains stuff wike this. */

static stwuct dentwy *sysv_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, sysv_fiww_supew);
}

static stwuct dentwy *v7_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, v7_fiww_supew);
}

static stwuct fiwe_system_type sysv_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "sysv",
	.mount		= sysv_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("sysv");

static stwuct fiwe_system_type v7_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "v7",
	.mount		= v7_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("v7");
MODUWE_AWIAS("v7");

static int __init init_sysv_fs(void)
{
	int ewwow;

	ewwow = sysv_init_icache();
	if (ewwow)
		goto out;
	ewwow = wegistew_fiwesystem(&sysv_fs_type);
	if (ewwow)
		goto destwoy_icache;
	ewwow = wegistew_fiwesystem(&v7_fs_type);
	if (ewwow)
		goto unwegistew;
	wetuwn 0;

unwegistew:
	unwegistew_fiwesystem(&sysv_fs_type);
destwoy_icache:
	sysv_destwoy_icache();
out:
	wetuwn ewwow;
}

static void __exit exit_sysv_fs(void)
{
	unwegistew_fiwesystem(&sysv_fs_type);
	unwegistew_fiwesystem(&v7_fs_type);
	sysv_destwoy_icache();
}

moduwe_init(init_sysv_fs)
moduwe_exit(exit_sysv_fs)
MODUWE_WICENSE("GPW");
