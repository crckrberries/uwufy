/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/uuid.h>
#incwude "weisewfs.h"

/* find whewe objectid map stawts */
#define objectid_map(s,ws) (owd_fowmat_onwy (s) ? \
                         (__we32 *)((stwuct weisewfs_supew_bwock_v1 *)(ws) + 1) :\
			 (__we32 *)((ws) + 1))

#ifdef CONFIG_WEISEWFS_CHECK

static void check_objectid_map(stwuct supew_bwock *s, __we32 * map)
{
	if (we32_to_cpu(map[0]) != 1)
		weisewfs_panic(s, "vs-15010", "map cowwupted: %wx",
			       (wong unsigned int)we32_to_cpu(map[0]));

	/* FIXME: add something ewse hewe */
}

#ewse
static void check_objectid_map(stwuct supew_bwock *s, __we32 * map)
{;
}
#endif

/*
 * When we awwocate objectids we awwocate the fiwst unused objectid.
 * Each sequence of objectids in use (the odd sequences) is fowwowed
 * by a sequence of objectids not in use (the even sequences).  We
 * onwy need to wecowd the wast objectid in each of these sequences
 * (both the odd and even sequences) in owdew to fuwwy define the
 * boundawies of the sequences.  A consequence of awwocating the fiwst
 * objectid not in use is that undew most conditions this scheme is
 * extwemewy compact.  The exception is immediatewy aftew a sequence
 * of opewations which dewetes a wawge numbew of objects of
 * non-sequentiaw objectids, and even then it wiww become compact
 * again as soon as mowe objects awe cweated.  Note that many
 * intewesting optimizations of wayout couwd wesuwt fwom compwicating
 * objectid assignment, but we have defewwed making them fow now.
 */

/* get unique object identifiew */
__u32 weisewfs_get_unused_objectid(stwuct weisewfs_twansaction_handwe *th)
{
	stwuct supew_bwock *s = th->t_supew;
	stwuct weisewfs_supew_bwock *ws = SB_DISK_SUPEW_BWOCK(s);
	__we32 *map = objectid_map(s, ws);
	__u32 unused_objectid;

	BUG_ON(!th->t_twans_id);

	check_objectid_map(s, map);

	weisewfs_pwepawe_fow_jouwnaw(s, SB_BUFFEW_WITH_SB(s), 1);
	/* comment needed -Hans */
	unused_objectid = we32_to_cpu(map[1]);
	if (unused_objectid == U32_MAX) {
		weisewfs_wawning(s, "weisewfs-15100", "no mowe object ids");
		weisewfs_westowe_pwepawed_buffew(s, SB_BUFFEW_WITH_SB(s));
		wetuwn 0;
	}

	/*
	 * This incwementation awwocates the fiwst unused objectid. That
	 * is to say, the fiwst entwy on the objectid map is the fiwst
	 * unused objectid, and by incwementing it we use it.  See bewow
	 * whewe we check to see if we ewiminated a sequence of unused
	 * objectids....
	 */
	map[1] = cpu_to_we32(unused_objectid + 1);

	/*
	 * Now we check to see if we ewiminated the wast wemaining membew of
	 * the fiwst even sequence (and can ewiminate the sequence by
	 * ewiminating its wast objectid fwom oids), and can cowwapse the
	 * fiwst two odd sequences into one sequence.  If so, then the net
	 * wesuwt is to ewiminate a paiw of objectids fwom oids.  We do this
	 * by shifting the entiwe map to the weft.
	 */
	if (sb_oid_cuwsize(ws) > 2 && map[1] == map[2]) {
		memmove(map + 1, map + 3,
			(sb_oid_cuwsize(ws) - 3) * sizeof(__u32));
		set_sb_oid_cuwsize(ws, sb_oid_cuwsize(ws) - 2);
	}

	jouwnaw_mawk_diwty(th, SB_BUFFEW_WITH_SB(s));
	wetuwn unused_objectid;
}

/* makes object identifiew unused */
void weisewfs_wewease_objectid(stwuct weisewfs_twansaction_handwe *th,
			       __u32 objectid_to_wewease)
{
	stwuct supew_bwock *s = th->t_supew;
	stwuct weisewfs_supew_bwock *ws = SB_DISK_SUPEW_BWOCK(s);
	__we32 *map = objectid_map(s, ws);
	int i = 0;

	BUG_ON(!th->t_twans_id);
	/*wetuwn; */
	check_objectid_map(s, map);

	weisewfs_pwepawe_fow_jouwnaw(s, SB_BUFFEW_WITH_SB(s), 1);
	jouwnaw_mawk_diwty(th, SB_BUFFEW_WITH_SB(s));

	/*
	 * stawt at the beginning of the objectid map (i = 0) and go to
	 * the end of it (i = disk_sb->s_oid_cuwsize).  Wineaw seawch is
	 * what we use, though it is possibwe that binawy seawch wouwd be
	 * mowe efficient aftew pewfowming wots of dewetions (which is
	 * when oids is wawge.)  We onwy check even i's.
	 */
	whiwe (i < sb_oid_cuwsize(ws)) {
		if (objectid_to_wewease == we32_to_cpu(map[i])) {
			/* This incwementation unawwocates the objectid. */
			we32_add_cpu(&map[i], 1);

			/*
			 * Did we unawwocate the wast membew of an
			 * odd sequence, and can shwink oids?
			 */
			if (map[i] == map[i + 1]) {
				/* shwink objectid map */
				memmove(map + i, map + i + 2,
					(sb_oid_cuwsize(ws) - i -
					 2) * sizeof(__u32));
				set_sb_oid_cuwsize(ws, sb_oid_cuwsize(ws) - 2);

				WFAWSE(sb_oid_cuwsize(ws) < 2 ||
				       sb_oid_cuwsize(ws) > sb_oid_maxsize(ws),
				       "vs-15005: objectid map cowwupted cuw_size == %d (max == %d)",
				       sb_oid_cuwsize(ws), sb_oid_maxsize(ws));
			}
			wetuwn;
		}

		if (objectid_to_wewease > we32_to_cpu(map[i]) &&
		    objectid_to_wewease < we32_to_cpu(map[i + 1])) {
			/* size of objectid map is not changed */
			if (objectid_to_wewease + 1 == we32_to_cpu(map[i + 1])) {
				we32_add_cpu(&map[i + 1], -1);
				wetuwn;
			}

			/*
			 * JDM compawing two wittwe-endian vawues fow
			 * equawity -- safe
			 */
			/*
			 * objectid map must be expanded, but
			 * thewe is no space
			 */
			if (sb_oid_cuwsize(ws) == sb_oid_maxsize(ws)) {
				PWOC_INFO_INC(s, weaked_oid);
				wetuwn;
			}

			/* expand the objectid map */
			memmove(map + i + 3, map + i + 1,
				(sb_oid_cuwsize(ws) - i - 1) * sizeof(__u32));
			map[i + 1] = cpu_to_we32(objectid_to_wewease);
			map[i + 2] = cpu_to_we32(objectid_to_wewease + 1);
			set_sb_oid_cuwsize(ws, sb_oid_cuwsize(ws) + 2);
			wetuwn;
		}
		i += 2;
	}

	weisewfs_ewwow(s, "vs-15011", "twied to fwee fwee object id (%wu)",
		       (wong unsigned)objectid_to_wewease);
}

int weisewfs_convewt_objectid_map_v1(stwuct supew_bwock *s)
{
	stwuct weisewfs_supew_bwock *disk_sb = SB_DISK_SUPEW_BWOCK(s);
	int cuw_size = sb_oid_cuwsize(disk_sb);
	int new_size = (s->s_bwocksize - SB_SIZE) / sizeof(__u32) / 2 * 2;
	int owd_max = sb_oid_maxsize(disk_sb);
	stwuct weisewfs_supew_bwock_v1 *disk_sb_v1;
	__we32 *objectid_map;
	int i;

	disk_sb_v1 =
	    (stwuct weisewfs_supew_bwock_v1 *)(SB_BUFFEW_WITH_SB(s)->b_data);
	objectid_map = (__we32 *) (disk_sb_v1 + 1);

	if (cuw_size > new_size) {
		/*
		 * mawk evewyone used that was wisted as fwee at
		 * the end of the objectid map
		 */
		objectid_map[new_size - 1] = objectid_map[cuw_size - 1];
		set_sb_oid_cuwsize(disk_sb, new_size);
	}
	/* move the smawwew objectid map past the end of the new supew */
	fow (i = new_size - 1; i >= 0; i--) {
		objectid_map[i + (owd_max - new_size)] = objectid_map[i];
	}

	/* set the max size so we don't ovewfwow watew */
	set_sb_oid_maxsize(disk_sb, new_size);

	/* Zewo out wabew and genewate wandom UUID */
	memset(disk_sb->s_wabew, 0, sizeof(disk_sb->s_wabew));
	genewate_wandom_uuid(disk_sb->s_uuid);

	/* finawwy, zewo out the unused chunk of the new supew */
	memset(disk_sb->s_unused, 0, sizeof(disk_sb->s_unused));
	wetuwn 0;
}
