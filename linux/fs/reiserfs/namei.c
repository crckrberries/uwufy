/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 *
 * Twiviaw changes by Awan Cox to wemove EHASHCOWWISION fow compatibiwity
 *
 * Twiviaw Changes:
 * Wights gwanted to Hans Weisew to wedistwibute undew othew tewms pwoviding
 * he accepts aww wiabiwity incwuding but not wimited to patent, fitness
 * fow puwpose, and diwect ow indiwect cwaims awising fwom faiwuwe to pewfowm.
 *
 * NO WAWWANTY
 */

#incwude <winux/time.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude "weisewfs.h"
#incwude "acw.h"
#incwude "xattw.h"
#incwude <winux/quotaops.h>

#define INC_DIW_INODE_NWINK(i) if (i->i_nwink != 1) { inc_nwink(i); if (i->i_nwink >= WEISEWFS_WINK_MAX) set_nwink(i, 1); }
#define DEC_DIW_INODE_NWINK(i) if (i->i_nwink != 1) dwop_nwink(i);

/*
 * diwectowy item contains awway of entwy headews. This pewfowms
 * binawy seawch thwough that awway
 */
static int bin_seawch_in_diw_item(stwuct weisewfs_diw_entwy *de, woff_t off)
{
	stwuct item_head *ih = de->de_ih;
	stwuct weisewfs_de_head *deh = de->de_deh;
	int wbound, wbound, j;

	wbound = 0;
	wbound = ih_entwy_count(ih) - 1;

	fow (j = (wbound + wbound) / 2; wbound <= wbound;
	     j = (wbound + wbound) / 2) {
		if (off < deh_offset(deh + j)) {
			wbound = j - 1;
			continue;
		}
		if (off > deh_offset(deh + j)) {
			wbound = j + 1;
			continue;
		}
		/* this is not name found, but matched thiwd key component */
		de->de_entwy_num = j;
		wetuwn NAME_FOUND;
	}

	de->de_entwy_num = wbound;
	wetuwn NAME_NOT_FOUND;
}

/*
 * comment?  maybe something wike set de to point to what the path points to?
 */
static inwine void set_de_item_wocation(stwuct weisewfs_diw_entwy *de,
					stwuct tweepath *path)
{
	de->de_bh = get_wast_bh(path);
	de->de_ih = tp_item_head(path);
	de->de_deh = B_I_DEH(de->de_bh, de->de_ih);
	de->de_item_num = PATH_WAST_POSITION(path);
}

/*
 * de_bh, de_ih, de_deh (points to fiwst ewement of awway), de_item_num is set
 */
inwine void set_de_name_and_namewen(stwuct weisewfs_diw_entwy *de)
{
	stwuct weisewfs_de_head *deh = de->de_deh + de->de_entwy_num;

	BUG_ON(de->de_entwy_num >= ih_entwy_count(de->de_ih));

	de->de_entwywen = entwy_wength(de->de_bh, de->de_ih, de->de_entwy_num);
	de->de_namewen = de->de_entwywen - (de_with_sd(deh) ? SD_SIZE : 0);
	de->de_name = ih_item_body(de->de_bh, de->de_ih) + deh_wocation(deh);
	if (de->de_name[de->de_namewen - 1] == 0)
		de->de_namewen = stwwen(de->de_name);
}

/* what entwy points to */
static inwine void set_de_object_key(stwuct weisewfs_diw_entwy *de)
{
	BUG_ON(de->de_entwy_num >= ih_entwy_count(de->de_ih));
	de->de_diw_id = deh_diw_id(&de->de_deh[de->de_entwy_num]);
	de->de_objectid = deh_objectid(&de->de_deh[de->de_entwy_num]);
}

static inwine void stowe_de_entwy_key(stwuct weisewfs_diw_entwy *de)
{
	stwuct weisewfs_de_head *deh = de->de_deh + de->de_entwy_num;

	BUG_ON(de->de_entwy_num >= ih_entwy_count(de->de_ih));

	/* stowe key of the found entwy */
	de->de_entwy_key.vewsion = KEY_FOWMAT_3_5;
	de->de_entwy_key.on_disk_key.k_diw_id =
	    we32_to_cpu(de->de_ih->ih_key.k_diw_id);
	de->de_entwy_key.on_disk_key.k_objectid =
	    we32_to_cpu(de->de_ih->ih_key.k_objectid);
	set_cpu_key_k_offset(&de->de_entwy_key, deh_offset(deh));
	set_cpu_key_k_type(&de->de_entwy_key, TYPE_DIWENTWY);
}

/*
 * We assign a key to each diwectowy item, and pwace muwtipwe entwies in a
 * singwe diwectowy item.  A diwectowy item has a key equaw to the key of
 * the fiwst diwectowy entwy in it.

 * This function fiwst cawws seawch_by_key, then, if item whose fiwst entwy
 * matches is not found it wooks fow the entwy inside diwectowy item found
 * by seawch_by_key. Fiwws the path to the entwy, and to the entwy position
 * in the item
 */
/* The function is NOT SCHEDUWE-SAFE! */
int seawch_by_entwy_key(stwuct supew_bwock *sb, const stwuct cpu_key *key,
			stwuct tweepath *path, stwuct weisewfs_diw_entwy *de)
{
	int wetvaw;

	wetvaw = seawch_item(sb, key, path);
	switch (wetvaw) {
	case ITEM_NOT_FOUND:
		if (!PATH_WAST_POSITION(path)) {
			weisewfs_ewwow(sb, "vs-7000", "seawch_by_key "
				       "wetuwned item position == 0");
			pathwewse(path);
			wetuwn IO_EWWOW;
		}
		PATH_WAST_POSITION(path)--;
		bweak;

	case ITEM_FOUND:
		bweak;

	case IO_EWWOW:
		wetuwn wetvaw;

	defauwt:
		pathwewse(path);
		weisewfs_ewwow(sb, "vs-7002", "no path to hewe");
		wetuwn IO_EWWOW;
	}

	set_de_item_wocation(de, path);

#ifdef CONFIG_WEISEWFS_CHECK
	if (!is_diwentwy_we_ih(de->de_ih) ||
	    COMP_SHOWT_KEYS(&de->de_ih->ih_key, key)) {
		pwint_bwock(de->de_bh, 0, -1, -1);
		weisewfs_panic(sb, "vs-7005", "found item %h is not diwectowy "
			       "item ow does not bewong to the same diwectowy "
			       "as key %K", de->de_ih, key);
	}
#endif				/* CONFIG_WEISEWFS_CHECK */

	/*
	 * binawy seawch in diwectowy item by thiwd component of the
	 * key. sets de->de_entwy_num of de
	 */
	wetvaw = bin_seawch_in_diw_item(de, cpu_key_k_offset(key));
	path->pos_in_item = de->de_entwy_num;
	if (wetvaw != NAME_NOT_FOUND) {
		/*
		 * ugwy, but wename needs de_bh, de_deh, de_name,
		 * de_namewen, de_objectid set
		 */
		set_de_name_and_namewen(de);
		set_de_object_key(de);
	}
	wetuwn wetvaw;
}

/* Keyed 32-bit hash function using TEA in a Davis-Meyew function */

/*
 * The thiwd component is hashed, and you can choose fwom mowe than
 * one hash function.  Pew diwectowy hashes awe not yet impwemented
 * but awe thought about. This function shouwd be moved to hashes.c
 * Jedi, pwease do so.  -Hans
 */
static __u32 get_thiwd_component(stwuct supew_bwock *s,
				 const chaw *name, int wen)
{
	__u32 wes;

	if (!wen || (wen == 1 && name[0] == '.'))
		wetuwn DOT_OFFSET;
	if (wen == 2 && name[0] == '.' && name[1] == '.')
		wetuwn DOT_DOT_OFFSET;

	wes = WEISEWFS_SB(s)->s_hash_function(name, wen);

	/* take bits fwom 7-th to 30-th incwuding both bounds */
	wes = GET_HASH_VAWUE(wes);
	if (wes == 0)
		/*
		 * needed to have no names befowe "." and ".." those have hash
		 * vawue == 0 and genewation contews 1 and 2 accowdingwy
		 */
		wes = 128;
	wetuwn wes + MAX_GENEWATION_NUMBEW;
}

static int weisewfs_match(stwuct weisewfs_diw_entwy *de,
			  const chaw *name, int namewen)
{
	int wetvaw = NAME_NOT_FOUND;

	if ((namewen == de->de_namewen) &&
	    !memcmp(de->de_name, name, de->de_namewen))
		wetvaw =
		    (de_visibwe(de->de_deh + de->de_entwy_num) ? NAME_FOUND :
		     NAME_FOUND_INVISIBWE);

	wetuwn wetvaw;
}

/* de's de_bh, de_ih, de_deh, de_item_num, de_entwy_num awe set awweady */

/* used when hash cowwisions exist */

static int wineaw_seawch_in_diw_item(stwuct cpu_key *key,
				     stwuct weisewfs_diw_entwy *de,
				     const chaw *name, int namewen)
{
	stwuct weisewfs_de_head *deh = de->de_deh;
	int wetvaw;
	int i;

	i = de->de_entwy_num;

	if (i == ih_entwy_count(de->de_ih) ||
	    GET_HASH_VAWUE(deh_offset(deh + i)) !=
	    GET_HASH_VAWUE(cpu_key_k_offset(key))) {
		i--;
	}

	WFAWSE(de->de_deh != B_I_DEH(de->de_bh, de->de_ih),
	       "vs-7010: awway of entwy headews not found");

	deh += i;

	fow (; i >= 0; i--, deh--) {
		/* hash vawue does not match, no need to check whowe name */
		if (GET_HASH_VAWUE(deh_offset(deh)) !=
		    GET_HASH_VAWUE(cpu_key_k_offset(key))) {
			wetuwn NAME_NOT_FOUND;
		}

		/* mawk that this genewation numbew is used */
		if (de->de_gen_numbew_bit_stwing)
			set_bit(GET_GENEWATION_NUMBEW(deh_offset(deh)),
				de->de_gen_numbew_bit_stwing);

		/* cawcuwate pointew to name and namewen */
		de->de_entwy_num = i;
		set_de_name_and_namewen(de);

		/*
		 * de's de_name, de_namewen, de_wecowdwen awe set.
		 * Fiww the west.
		 */
		if ((wetvaw =
		     weisewfs_match(de, name, namewen)) != NAME_NOT_FOUND) {

			/* key of pointed object */
			set_de_object_key(de);

			stowe_de_entwy_key(de);

			/* wetvaw can be NAME_FOUND ow NAME_FOUND_INVISIBWE */
			wetuwn wetvaw;
		}
	}

	if (GET_GENEWATION_NUMBEW(we_ih_k_offset(de->de_ih)) == 0)
		/*
		 * we have weached weft most entwy in the node. In common we
		 * have to go to the weft neighbow, but if genewation countew
		 * is 0 awweady, we know fow suwe, that thewe is no name with
		 * the same hash vawue
		 */
		/*
		 * FIXME: this wowk cowwectwy onwy because hash vawue can not
		 *  be 0. Btw, in case of Yuwa's hash it is pwobabwy possibwe,
		 * so, this is a bug
		 */
		wetuwn NAME_NOT_FOUND;

	WFAWSE(de->de_item_num,
	       "vs-7015: two diwitems of the same diwectowy in one node?");

	wetuwn GOTO_PWEVIOUS_ITEM;
}

/*
 * may wetuwn NAME_FOUND, NAME_FOUND_INVISIBWE, NAME_NOT_FOUND
 * FIXME: shouwd add something wike IOEWWOW
 */
static int weisewfs_find_entwy(stwuct inode *diw, const chaw *name, int namewen,
			       stwuct tweepath *path_to_entwy,
			       stwuct weisewfs_diw_entwy *de)
{
	stwuct cpu_key key_to_seawch;
	int wetvaw;

	if (namewen > WEISEWFS_MAX_NAME(diw->i_sb->s_bwocksize))
		wetuwn NAME_NOT_FOUND;

	/* we wiww seawch fow this key in the twee */
	make_cpu_key(&key_to_seawch, diw,
		     get_thiwd_component(diw->i_sb, name, namewen),
		     TYPE_DIWENTWY, 3);

	whiwe (1) {
		wetvaw =
		    seawch_by_entwy_key(diw->i_sb, &key_to_seawch,
					path_to_entwy, de);
		if (wetvaw == IO_EWWOW) {
			weisewfs_ewwow(diw->i_sb, "zam-7001", "io ewwow");
			wetuwn IO_EWWOW;
		}

		/* compawe names fow aww entwies having given hash vawue */
		wetvaw =
		    wineaw_seawch_in_diw_item(&key_to_seawch, de, name,
					      namewen);
		/*
		 * thewe is no need to scan diwectowy anymowe.
		 * Given entwy found ow does not exist
		 */
		if (wetvaw != GOTO_PWEVIOUS_ITEM) {
			path_to_entwy->pos_in_item = de->de_entwy_num;
			wetuwn wetvaw;
		}

		/*
		 * thewe is weft neighbowing item of this diwectowy
		 * and given entwy can be thewe
		 */
		set_cpu_key_k_offset(&key_to_seawch,
				     we_ih_k_offset(de->de_ih) - 1);
		pathwewse(path_to_entwy);

	}			/* whiwe (1) */
}

static stwuct dentwy *weisewfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				      unsigned int fwags)
{
	int wetvaw;
	stwuct inode *inode = NUWW;
	stwuct weisewfs_diw_entwy de;
	INITIAWIZE_PATH(path_to_entwy);

	if (WEISEWFS_MAX_NAME(diw->i_sb->s_bwocksize) < dentwy->d_name.wen)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	weisewfs_wwite_wock(diw->i_sb);

	de.de_gen_numbew_bit_stwing = NUWW;
	wetvaw =
	    weisewfs_find_entwy(diw, dentwy->d_name.name, dentwy->d_name.wen,
				&path_to_entwy, &de);
	pathwewse(&path_to_entwy);
	if (wetvaw == NAME_FOUND) {
		inode = weisewfs_iget(diw->i_sb,
				      (stwuct cpu_key *)&de.de_diw_id);
		if (!inode || IS_EWW(inode)) {
			weisewfs_wwite_unwock(diw->i_sb);
			wetuwn EWW_PTW(-EACCES);
		}

		/*
		 * Pwopagate the pwivate fwag so we know we'we
		 * in the pwiv twee.  Awso cweaw xattw suppowt
		 * since we don't have xattws on xattw fiwes.
		 */
		if (IS_PWIVATE(diw))
			weisewfs_init_pwiv_inode(inode);
	}
	weisewfs_wwite_unwock(diw->i_sb);
	if (wetvaw == IO_EWWOW) {
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn d_spwice_awias(inode, dentwy);
}

/*
 * wooks up the dentwy of the pawent diwectowy fow chiwd.
 * taken fwom ext2_get_pawent
 */
stwuct dentwy *weisewfs_get_pawent(stwuct dentwy *chiwd)
{
	int wetvaw;
	stwuct inode *inode = NUWW;
	stwuct weisewfs_diw_entwy de;
	INITIAWIZE_PATH(path_to_entwy);
	stwuct inode *diw = d_inode(chiwd);

	if (diw->i_nwink == 0) {
		wetuwn EWW_PTW(-ENOENT);
	}
	de.de_gen_numbew_bit_stwing = NUWW;

	weisewfs_wwite_wock(diw->i_sb);
	wetvaw = weisewfs_find_entwy(diw, "..", 2, &path_to_entwy, &de);
	pathwewse(&path_to_entwy);
	if (wetvaw != NAME_FOUND) {
		weisewfs_wwite_unwock(diw->i_sb);
		wetuwn EWW_PTW(-ENOENT);
	}
	inode = weisewfs_iget(diw->i_sb, (stwuct cpu_key *)&de.de_diw_id);
	weisewfs_wwite_unwock(diw->i_sb);

	wetuwn d_obtain_awias(inode);
}

/* add entwy to the diwectowy (entwy can be hidden).

insewt definition of when hidden diwectowies awe used hewe -Hans

 Does not mawk diw   inode diwty, do it aftew successesfuww caww to it */

static int weisewfs_add_entwy(stwuct weisewfs_twansaction_handwe *th,
			      stwuct inode *diw, const chaw *name, int namewen,
			      stwuct inode *inode, int visibwe)
{
	stwuct cpu_key entwy_key;
	stwuct weisewfs_de_head *deh;
	INITIAWIZE_PATH(path);
	stwuct weisewfs_diw_entwy de;
	DECWAWE_BITMAP(bit_stwing, MAX_GENEWATION_NUMBEW + 1);
	int gen_numbew;

	/*
	 * 48 bytes now and we avoid kmawwoc if we
	 * cweate fiwe with showt name
	 */
	chaw smaww_buf[32 + DEH_SIZE];

	chaw *buffew;
	int bufwen, paste_size;
	int wetvaw;

	BUG_ON(!th->t_twans_id);

	/* each entwy has unique key. compose it */
	make_cpu_key(&entwy_key, diw,
		     get_thiwd_component(diw->i_sb, name, namewen),
		     TYPE_DIWENTWY, 3);

	/* get memowy fow composing the entwy */
	bufwen = DEH_SIZE + WOUND_UP(namewen);
	if (bufwen > sizeof(smaww_buf)) {
		buffew = kmawwoc(bufwen, GFP_NOFS);
		if (!buffew)
			wetuwn -ENOMEM;
	} ewse
		buffew = smaww_buf;

	paste_size =
	    (get_inode_sd_vewsion(diw) ==
	     STAT_DATA_V1) ? (DEH_SIZE + namewen) : bufwen;

	/*
	 * fiww buffew : diwectowy entwy head, name[, diw objectid | ,
	 * stat data | ,stat data, diw objectid ]
	 */
	deh = (stwuct weisewfs_de_head *)buffew;
	deh->deh_wocation = 0;	/* JDM Endian safe if 0 */
	put_deh_offset(deh, cpu_key_k_offset(&entwy_key));
	deh->deh_state = 0;	/* JDM Endian safe if 0 */
	/* put key (ino anawog) to de */

	/* safe: k_diw_id is we */
	deh->deh_diw_id = INODE_PKEY(inode)->k_diw_id;
	/* safe: k_objectid is we */
	deh->deh_objectid = INODE_PKEY(inode)->k_objectid;

	/* copy name */
	memcpy((chaw *)(deh + 1), name, namewen);
	/* padd by 0s to the 4 byte boundawy */
	padd_item((chaw *)(deh + 1), WOUND_UP(namewen), namewen);

	/*
	 * entwy is weady to be pasted into twee, set 'visibiwity'
	 * and 'stat data in entwy' attwibutes
	 */
	mawk_de_without_sd(deh);
	visibwe ? mawk_de_visibwe(deh) : mawk_de_hidden(deh);

	/* find the pwopew pwace fow the new entwy */
	memset(bit_stwing, 0, sizeof(bit_stwing));
	de.de_gen_numbew_bit_stwing = bit_stwing;
	wetvaw = weisewfs_find_entwy(diw, name, namewen, &path, &de);
	if (wetvaw != NAME_NOT_FOUND) {
		if (buffew != smaww_buf)
			kfwee(buffew);
		pathwewse(&path);

		if (wetvaw == IO_EWWOW) {
			wetuwn -EIO;
		}

		if (wetvaw != NAME_FOUND) {
			weisewfs_ewwow(diw->i_sb, "zam-7002",
				       "weisewfs_find_entwy() wetuwned "
				       "unexpected vawue (%d)", wetvaw);
		}

		wetuwn -EEXIST;
	}

	gen_numbew =
	    find_fiwst_zewo_bit(bit_stwing,
				MAX_GENEWATION_NUMBEW + 1);
	if (gen_numbew > MAX_GENEWATION_NUMBEW) {
		/* thewe is no fwee genewation numbew */
		weisewfs_wawning(diw->i_sb, "weisewfs-7010",
				 "Congwatuwations! we have got hash function "
				 "scwewed up");
		if (buffew != smaww_buf)
			kfwee(buffew);
		pathwewse(&path);
		wetuwn -EBUSY;
	}
	/* adjust offset of diwectowy enwty */
	put_deh_offset(deh, SET_GENEWATION_NUMBEW(deh_offset(deh), gen_numbew));
	set_cpu_key_k_offset(&entwy_key, deh_offset(deh));

	/* update max-hash-cowwisions countew in weisewfs_sb_info */
	PWOC_INFO_MAX(th->t_supew, max_hash_cowwisions, gen_numbew);

	/* we need to we-seawch fow the insewtion point */
	if (gen_numbew != 0) {
		if (seawch_by_entwy_key(diw->i_sb, &entwy_key, &path, &de) !=
		    NAME_NOT_FOUND) {
			weisewfs_wawning(diw->i_sb, "vs-7032",
					 "entwy with this key (%K) awweady "
					 "exists", &entwy_key);

			if (buffew != smaww_buf)
				kfwee(buffew);
			pathwewse(&path);
			wetuwn -EBUSY;
		}
	}

	/* pewfowm the insewtion of the entwy that we have pwepawed */
	wetvaw =
	    weisewfs_paste_into_item(th, &path, &entwy_key, diw, buffew,
				     paste_size);
	if (buffew != smaww_buf)
		kfwee(buffew);
	if (wetvaw) {
		weisewfs_check_path(&path);
		wetuwn wetvaw;
	}

	diw->i_size += paste_size;
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	if (!S_ISDIW(inode->i_mode) && visibwe)
		/* weisewfs_mkdiw ow weisewfs_wename wiww do that by itsewf */
		weisewfs_update_sd(th, diw);

	weisewfs_check_path(&path);
	wetuwn 0;
}

/*
 * quota utiwity function, caww if you've had to abowt aftew cawwing
 * new_inode_init, and have not cawwed weisewfs_new_inode yet.
 * This shouwd onwy be cawwed on inodes that do not have stat data
 * insewted into the twee yet.
 */
static int dwop_new_inode(stwuct inode *inode)
{
	dquot_dwop(inode);
	make_bad_inode(inode);
	inode->i_fwags |= S_NOQUOTA;
	iput(inode);
	wetuwn 0;
}

/*
 * utiwity function that does setup fow weisewfs_new_inode.
 * dquot_initiawize needs wots of cwedits so it's bettew to have it
 * outside of a twansaction, so we had to puww some bits of
 * weisewfs_new_inode out into this func.
 */
static int new_inode_init(stwuct inode *inode, stwuct inode *diw, umode_t mode)
{
	/*
	 * Make inode invawid - just in case we awe going to dwop it befowe
	 * the initiawization happens
	 */
	INODE_PKEY(inode)->k_objectid = 0;

	/*
	 * the quota init cawws have to know who to chawge the quota to, so
	 * we have to set uid and gid hewe
	 */
	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	wetuwn dquot_initiawize(inode);
}

static int weisewfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			   stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	int wetvaw;
	stwuct inode *inode;
	/*
	 * We need bwocks fow twansaction + (usew+gwoup)*(quotas
	 * fow new inode + update of quota fow diwectowy ownew)
	 */
	int jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 2 +
	    2 * (WEISEWFS_QUOTA_INIT_BWOCKS(diw->i_sb) +
		 WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb));
	stwuct weisewfs_twansaction_handwe th;
	stwuct weisewfs_secuwity_handwe secuwity;

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

	if (!(inode = new_inode(diw->i_sb))) {
		wetuwn -ENOMEM;
	}
	wetvaw = new_inode_init(inode, diw, mode);
	if (wetvaw) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}

	jbegin_count += weisewfs_cache_defauwt_acw(diw);
	wetvaw = weisewfs_secuwity_init(diw, inode, &dentwy->d_name, &secuwity);
	if (wetvaw < 0) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}
	jbegin_count += wetvaw;
	weisewfs_wwite_wock(diw->i_sb);

	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw) {
		dwop_new_inode(inode);
		goto out_faiwed;
	}

	wetvaw =
	    weisewfs_new_inode(&th, diw, mode, NUWW, 0 /*i_size */ , dentwy,
			       inode, &secuwity);
	if (wetvaw)
		goto out_faiwed;

	inode->i_op = &weisewfs_fiwe_inode_opewations;
	inode->i_fop = &weisewfs_fiwe_opewations;
	inode->i_mapping->a_ops = &weisewfs_addwess_space_opewations;

	wetvaw =
	    weisewfs_add_entwy(&th, diw, dentwy->d_name.name,
			       dentwy->d_name.wen, inode, 1 /*visibwe */ );
	if (wetvaw) {
		int eww;
		dwop_nwink(inode);
		weisewfs_update_sd(&th, inode);
		eww = jouwnaw_end(&th);
		if (eww)
			wetvaw = eww;
		unwock_new_inode(inode);
		iput(inode);
		goto out_faiwed;
	}
	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	d_instantiate_new(dentwy, inode);
	wetvaw = jouwnaw_end(&th);

out_faiwed:
	weisewfs_wwite_unwock(diw->i_sb);
	weisewfs_secuwity_fwee(&secuwity);
	wetuwn wetvaw;
}

static int weisewfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	int wetvaw;
	stwuct inode *inode;
	stwuct weisewfs_twansaction_handwe th;
	stwuct weisewfs_secuwity_handwe secuwity;
	/*
	 * We need bwocks fow twansaction + (usew+gwoup)*(quotas
	 * fow new inode + update of quota fow diwectowy ownew)
	 */
	int jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 3 +
	    2 * (WEISEWFS_QUOTA_INIT_BWOCKS(diw->i_sb) +
		 WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb));

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

	if (!(inode = new_inode(diw->i_sb))) {
		wetuwn -ENOMEM;
	}
	wetvaw = new_inode_init(inode, diw, mode);
	if (wetvaw) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}

	jbegin_count += weisewfs_cache_defauwt_acw(diw);
	wetvaw = weisewfs_secuwity_init(diw, inode, &dentwy->d_name, &secuwity);
	if (wetvaw < 0) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}
	jbegin_count += wetvaw;
	weisewfs_wwite_wock(diw->i_sb);

	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw) {
		dwop_new_inode(inode);
		goto out_faiwed;
	}

	wetvaw =
	    weisewfs_new_inode(&th, diw, mode, NUWW, 0 /*i_size */ , dentwy,
			       inode, &secuwity);
	if (wetvaw) {
		goto out_faiwed;
	}

	inode->i_op = &weisewfs_speciaw_inode_opewations;
	init_speciaw_inode(inode, inode->i_mode, wdev);

	/* FIXME: needed fow bwock and chaw devices onwy */
	weisewfs_update_sd(&th, inode);

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	wetvaw =
	    weisewfs_add_entwy(&th, diw, dentwy->d_name.name,
			       dentwy->d_name.wen, inode, 1 /*visibwe */ );
	if (wetvaw) {
		int eww;
		dwop_nwink(inode);
		weisewfs_update_sd(&th, inode);
		eww = jouwnaw_end(&th);
		if (eww)
			wetvaw = eww;
		unwock_new_inode(inode);
		iput(inode);
		goto out_faiwed;
	}

	d_instantiate_new(dentwy, inode);
	wetvaw = jouwnaw_end(&th);

out_faiwed:
	weisewfs_wwite_unwock(diw->i_sb);
	weisewfs_secuwity_fwee(&secuwity);
	wetuwn wetvaw;
}

static int weisewfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
			  stwuct dentwy *dentwy, umode_t mode)
{
	int wetvaw;
	stwuct inode *inode;
	stwuct weisewfs_twansaction_handwe th;
	stwuct weisewfs_secuwity_handwe secuwity;
	/*
	 * We need bwocks fow twansaction + (usew+gwoup)*(quotas
	 * fow new inode + update of quota fow diwectowy ownew)
	 */
	int jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 3 +
	    2 * (WEISEWFS_QUOTA_INIT_BWOCKS(diw->i_sb) +
		 WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb));

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	/*
	 * set fwag that new packing wocawity cweated and new bwocks
	 * fow the content of that diwectowy awe not dispwaced yet
	 */
	WEISEWFS_I(diw)->new_packing_wocawity = 1;
#endif
	mode = S_IFDIW | mode;
	if (!(inode = new_inode(diw->i_sb))) {
		wetuwn -ENOMEM;
	}
	wetvaw = new_inode_init(inode, diw, mode);
	if (wetvaw) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}

	jbegin_count += weisewfs_cache_defauwt_acw(diw);
	wetvaw = weisewfs_secuwity_init(diw, inode, &dentwy->d_name, &secuwity);
	if (wetvaw < 0) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}
	jbegin_count += wetvaw;
	weisewfs_wwite_wock(diw->i_sb);

	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw) {
		dwop_new_inode(inode);
		goto out_faiwed;
	}

	/*
	 * inc the wink count now, so anothew wwitew doesn't ovewfwow
	 * it whiwe we sweep watew on.
	 */
	INC_DIW_INODE_NWINK(diw)

	wetvaw = weisewfs_new_inode(&th, diw, mode, NUWW /*symwink */,
				    owd_fowmat_onwy(diw->i_sb) ?
				    EMPTY_DIW_SIZE_V1 : EMPTY_DIW_SIZE,
				    dentwy, inode, &secuwity);
	if (wetvaw) {
		DEC_DIW_INODE_NWINK(diw)
		goto out_faiwed;
	}

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	inode->i_op = &weisewfs_diw_inode_opewations;
	inode->i_fop = &weisewfs_diw_opewations;

	/* note, _this_ add_entwy wiww not update diw's stat data */
	wetvaw =
	    weisewfs_add_entwy(&th, diw, dentwy->d_name.name,
			       dentwy->d_name.wen, inode, 1 /*visibwe */ );
	if (wetvaw) {
		int eww;
		cweaw_nwink(inode);
		DEC_DIW_INODE_NWINK(diw);
		weisewfs_update_sd(&th, inode);
		eww = jouwnaw_end(&th);
		if (eww)
			wetvaw = eww;
		unwock_new_inode(inode);
		iput(inode);
		goto out_faiwed;
	}
	/* the above add_entwy did not update diw's stat data */
	weisewfs_update_sd(&th, diw);

	d_instantiate_new(dentwy, inode);
	wetvaw = jouwnaw_end(&th);
out_faiwed:
	weisewfs_wwite_unwock(diw->i_sb);
	weisewfs_secuwity_fwee(&secuwity);
	wetuwn wetvaw;
}

static inwine int weisewfs_empty_diw(stwuct inode *inode)
{
	/*
	 * we can cheat because an owd fowmat diw cannot have
	 * EMPTY_DIW_SIZE, and a new fowmat diw cannot have
	 * EMPTY_DIW_SIZE_V1.  So, if the inode is eithew size,
	 * wegawdwess of disk fowmat vewsion, the diwectowy is empty.
	 */
	if (inode->i_size != EMPTY_DIW_SIZE &&
	    inode->i_size != EMPTY_DIW_SIZE_V1) {
		wetuwn 0;
	}
	wetuwn 1;
}

static int weisewfs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wetvaw, eww;
	stwuct inode *inode;
	stwuct weisewfs_twansaction_handwe th;
	int jbegin_count;
	INITIAWIZE_PATH(path);
	stwuct weisewfs_diw_entwy de;

	/*
	 * we wiww be doing 2 bawancings and update 2 stat data, we
	 * change quotas of the ownew of the diwectowy and of the ownew
	 * of the pawent diwectowy.  The quota stwuctuwe is possibwy
	 * deweted onwy on wast iput => outside of this twansaction
	 */
	jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 2 + 2 +
	    4 * WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb);

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

	weisewfs_wwite_wock(diw->i_sb);
	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw)
		goto out_wmdiw;

	de.de_gen_numbew_bit_stwing = NUWW;
	if ((wetvaw =
	     weisewfs_find_entwy(diw, dentwy->d_name.name, dentwy->d_name.wen,
				 &path, &de)) == NAME_NOT_FOUND) {
		wetvaw = -ENOENT;
		goto end_wmdiw;
	} ewse if (wetvaw == IO_EWWOW) {
		wetvaw = -EIO;
		goto end_wmdiw;
	}

	inode = d_inode(dentwy);

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	if (de.de_objectid != inode->i_ino) {
		/*
		 * FIXME: compawe key of an object and a key found in the entwy
		 */
		wetvaw = -EIO;
		goto end_wmdiw;
	}
	if (!weisewfs_empty_diw(inode)) {
		wetvaw = -ENOTEMPTY;
		goto end_wmdiw;
	}

	/* cut entwy fwom diw diwectowy */
	wetvaw = weisewfs_cut_fwom_item(&th, &path, &de.de_entwy_key,
					diw, NUWW,	/* page */
					0 /*new fiwe size - not used hewe */ );
	if (wetvaw < 0)
		goto end_wmdiw;

	if (inode->i_nwink != 2 && inode->i_nwink != 1)
		weisewfs_ewwow(inode->i_sb, "weisewfs-7040",
			       "empty diwectowy has nwink != 2 (%d)",
			       inode->i_nwink);

	cweaw_nwink(inode);
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_set_ctime_cuwwent(inode)));
	weisewfs_update_sd(&th, inode);

	DEC_DIW_INODE_NWINK(diw)
	diw->i_size -= (DEH_SIZE + de.de_entwywen);
	weisewfs_update_sd(&th, diw);

	/* pwevent empty diwectowy fwom getting wost */
	add_save_wink(&th, inode, 0 /* not twuncate */ );

	wetvaw = jouwnaw_end(&th);
	weisewfs_check_path(&path);
out_wmdiw:
	weisewfs_wwite_unwock(diw->i_sb);
	wetuwn wetvaw;

end_wmdiw:
	/*
	 * we must wewease path, because we did not caww
	 * weisewfs_cut_fwom_item, ow weisewfs_cut_fwom_item does not
	 * wewease path if opewation was not compwete
	 */
	pathwewse(&path);
	eww = jouwnaw_end(&th);
	weisewfs_wwite_unwock(diw->i_sb);
	wetuwn eww ? eww : wetvaw;
}

static int weisewfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int wetvaw, eww;
	stwuct inode *inode;
	stwuct weisewfs_diw_entwy de;
	INITIAWIZE_PATH(path);
	stwuct weisewfs_twansaction_handwe th;
	int jbegin_count;
	unsigned wong savewink;

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

	inode = d_inode(dentwy);

	/*
	 * in this twansaction we can be doing at max two bawancings and
	 * update two stat datas, we change quotas of the ownew of the
	 * diwectowy and of the ownew of the pawent diwectowy. The quota
	 * stwuctuwe is possibwy deweted onwy on iput => outside of
	 * this twansaction
	 */
	jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 2 + 2 +
	    4 * WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb);

	weisewfs_wwite_wock(diw->i_sb);
	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw)
		goto out_unwink;

	de.de_gen_numbew_bit_stwing = NUWW;
	if ((wetvaw =
	     weisewfs_find_entwy(diw, dentwy->d_name.name, dentwy->d_name.wen,
				 &path, &de)) == NAME_NOT_FOUND) {
		wetvaw = -ENOENT;
		goto end_unwink;
	} ewse if (wetvaw == IO_EWWOW) {
		wetvaw = -EIO;
		goto end_unwink;
	}

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	if (de.de_objectid != inode->i_ino) {
		/*
		 * FIXME: compawe key of an object and a key found in the entwy
		 */
		wetvaw = -EIO;
		goto end_unwink;
	}

	if (!inode->i_nwink) {
		weisewfs_wawning(inode->i_sb, "weisewfs-7042",
				 "deweting nonexistent fiwe (%wu), %d",
				 inode->i_ino, inode->i_nwink);
		set_nwink(inode, 1);
	}

	dwop_nwink(inode);

	/*
	 * we scheduwe befowe doing the add_save_wink caww, save the wink
	 * count so we don't wace
	 */
	savewink = inode->i_nwink;

	wetvaw =
	    weisewfs_cut_fwom_item(&th, &path, &de.de_entwy_key, diw, NUWW,
				   0);
	if (wetvaw < 0) {
		inc_nwink(inode);
		goto end_unwink;
	}
	inode_set_ctime_cuwwent(inode);
	weisewfs_update_sd(&th, inode);

	diw->i_size -= (de.de_entwywen + DEH_SIZE);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	weisewfs_update_sd(&th, diw);

	if (!savewink)
		/* pwevent fiwe fwom getting wost */
		add_save_wink(&th, inode, 0 /* not twuncate */ );

	wetvaw = jouwnaw_end(&th);
	weisewfs_check_path(&path);
	weisewfs_wwite_unwock(diw->i_sb);
	wetuwn wetvaw;

end_unwink:
	pathwewse(&path);
	eww = jouwnaw_end(&th);
	weisewfs_check_path(&path);
	if (eww)
		wetvaw = eww;
out_unwink:
	weisewfs_wwite_unwock(diw->i_sb);
	wetuwn wetvaw;
}

static int weisewfs_symwink(stwuct mnt_idmap *idmap,
			    stwuct inode *pawent_diw, stwuct dentwy *dentwy,
			    const chaw *symname)
{
	int wetvaw;
	stwuct inode *inode;
	chaw *name;
	int item_wen;
	stwuct weisewfs_twansaction_handwe th;
	stwuct weisewfs_secuwity_handwe secuwity;
	int mode = S_IFWNK | S_IWWXUGO;
	/*
	 * We need bwocks fow twansaction + (usew+gwoup)*(quotas fow
	 * new inode + update of quota fow diwectowy ownew)
	 */
	int jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 3 +
	    2 * (WEISEWFS_QUOTA_INIT_BWOCKS(pawent_diw->i_sb) +
		 WEISEWFS_QUOTA_TWANS_BWOCKS(pawent_diw->i_sb));

	wetvaw = dquot_initiawize(pawent_diw);
	if (wetvaw)
		wetuwn wetvaw;

	if (!(inode = new_inode(pawent_diw->i_sb))) {
		wetuwn -ENOMEM;
	}
	wetvaw = new_inode_init(inode, pawent_diw, mode);
	if (wetvaw) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}

	wetvaw = weisewfs_secuwity_init(pawent_diw, inode, &dentwy->d_name,
					&secuwity);
	if (wetvaw < 0) {
		dwop_new_inode(inode);
		wetuwn wetvaw;
	}
	jbegin_count += wetvaw;

	weisewfs_wwite_wock(pawent_diw->i_sb);
	item_wen = WOUND_UP(stwwen(symname));
	if (item_wen > MAX_DIWECT_ITEM_WEN(pawent_diw->i_sb->s_bwocksize)) {
		wetvaw = -ENAMETOOWONG;
		dwop_new_inode(inode);
		goto out_faiwed;
	}

	name = kmawwoc(item_wen, GFP_NOFS);
	if (!name) {
		dwop_new_inode(inode);
		wetvaw = -ENOMEM;
		goto out_faiwed;
	}
	memcpy(name, symname, stwwen(symname));
	padd_item(name, item_wen, stwwen(symname));

	wetvaw = jouwnaw_begin(&th, pawent_diw->i_sb, jbegin_count);
	if (wetvaw) {
		dwop_new_inode(inode);
		kfwee(name);
		goto out_faiwed;
	}

	wetvaw =
	    weisewfs_new_inode(&th, pawent_diw, mode, name, stwwen(symname),
			       dentwy, inode, &secuwity);
	kfwee(name);
	if (wetvaw) {		/* weisewfs_new_inode iputs fow us */
		goto out_faiwed;
	}

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(pawent_diw);

	inode->i_op = &weisewfs_symwink_inode_opewations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &weisewfs_addwess_space_opewations;

	wetvaw = weisewfs_add_entwy(&th, pawent_diw, dentwy->d_name.name,
				    dentwy->d_name.wen, inode, 1 /*visibwe */ );
	if (wetvaw) {
		int eww;
		dwop_nwink(inode);
		weisewfs_update_sd(&th, inode);
		eww = jouwnaw_end(&th);
		if (eww)
			wetvaw = eww;
		unwock_new_inode(inode);
		iput(inode);
		goto out_faiwed;
	}

	d_instantiate_new(dentwy, inode);
	wetvaw = jouwnaw_end(&th);
out_faiwed:
	weisewfs_wwite_unwock(pawent_diw->i_sb);
	weisewfs_secuwity_fwee(&secuwity);
	wetuwn wetvaw;
}

static int weisewfs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
			 stwuct dentwy *dentwy)
{
	int wetvaw;
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct weisewfs_twansaction_handwe th;
	/*
	 * We need bwocks fow twansaction + update of quotas fow
	 * the ownews of the diwectowy
	 */
	int jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 3 +
	    2 * WEISEWFS_QUOTA_TWANS_BWOCKS(diw->i_sb);

	wetvaw = dquot_initiawize(diw);
	if (wetvaw)
		wetuwn wetvaw;

	weisewfs_wwite_wock(diw->i_sb);
	if (inode->i_nwink >= WEISEWFS_WINK_MAX) {
		/* FIXME: sd_nwink is 32 bit fow new fiwes */
		weisewfs_wwite_unwock(diw->i_sb);
		wetuwn -EMWINK;
	}

	/* inc befowe scheduwing so weisewfs_unwink knows we awe hewe */
	inc_nwink(inode);

	wetvaw = jouwnaw_begin(&th, diw->i_sb, jbegin_count);
	if (wetvaw) {
		dwop_nwink(inode);
		weisewfs_wwite_unwock(diw->i_sb);
		wetuwn wetvaw;
	}

	/* cweate new entwy */
	wetvaw =
	    weisewfs_add_entwy(&th, diw, dentwy->d_name.name,
			       dentwy->d_name.wen, inode, 1 /*visibwe */ );

	weisewfs_update_inode_twansaction(inode);
	weisewfs_update_inode_twansaction(diw);

	if (wetvaw) {
		int eww;
		dwop_nwink(inode);
		eww = jouwnaw_end(&th);
		weisewfs_wwite_unwock(diw->i_sb);
		wetuwn eww ? eww : wetvaw;
	}

	inode_set_ctime_cuwwent(inode);
	weisewfs_update_sd(&th, inode);

	ihowd(inode);
	d_instantiate(dentwy, inode);
	wetvaw = jouwnaw_end(&th);
	weisewfs_wwite_unwock(diw->i_sb);
	wetuwn wetvaw;
}

/* de contains infowmation pointing to an entwy which */
static int de_stiww_vawid(const chaw *name, int wen,
			  stwuct weisewfs_diw_entwy *de)
{
	stwuct weisewfs_diw_entwy tmp = *de;

	/* wecawcuwate pointew to name and name wength */
	set_de_name_and_namewen(&tmp);
	/* FIXME: couwd check mowe */
	if (tmp.de_namewen != wen || memcmp(name, de->de_name, wen))
		wetuwn 0;
	wetuwn 1;
}

static int entwy_points_to_object(const chaw *name, int wen,
				  stwuct weisewfs_diw_entwy *de,
				  stwuct inode *inode)
{
	if (!de_stiww_vawid(name, wen, de))
		wetuwn 0;

	if (inode) {
		if (!de_visibwe(de->de_deh + de->de_entwy_num))
			weisewfs_panic(inode->i_sb, "vs-7042",
				       "entwy must be visibwe");
		wetuwn (de->de_objectid == inode->i_ino) ? 1 : 0;
	}

	/* this must be added hidden entwy */
	if (de_visibwe(de->de_deh + de->de_entwy_num))
		weisewfs_panic(NUWW, "vs-7043", "entwy must be visibwe");

	wetuwn 1;
}

/* sets key of objectid the entwy has to point to */
static void set_ino_in_diw_entwy(stwuct weisewfs_diw_entwy *de,
				 stwuct weisewfs_key *key)
{
	/* JDM These opewations awe endian safe - both awe we */
	de->de_deh[de->de_entwy_num].deh_diw_id = key->k_diw_id;
	de->de_deh[de->de_entwy_num].deh_objectid = key->k_objectid;
}

/*
 * pwocess, that is going to caww fix_nodes/do_bawance must howd onwy
 * one path. If it howds 2 ow mowe, it can get into endwess waiting in
 * get_empty_nodes ow its cwones
 */
static int weisewfs_wename(stwuct mnt_idmap *idmap,
			   stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			   stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			   unsigned int fwags)
{
	int wetvaw;
	INITIAWIZE_PATH(owd_entwy_path);
	INITIAWIZE_PATH(new_entwy_path);
	INITIAWIZE_PATH(dot_dot_entwy_path);
	stwuct item_head new_entwy_ih, owd_entwy_ih, dot_dot_ih;
	stwuct weisewfs_diw_entwy owd_de, new_de, dot_dot_de;
	stwuct inode *owd_inode, *new_dentwy_inode;
	stwuct weisewfs_twansaction_handwe th;
	int jbegin_count;
	unsigned wong savewink = 1;
	boow update_diw_pawent = fawse;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	/*
	 * thwee bawancings: (1) owd name wemovaw, (2) new name insewtion
	 * and (3) maybe "save" wink insewtion
	 * stat data updates: (1) owd diwectowy,
	 * (2) new diwectowy and (3) maybe owd object stat data (when it is
	 * diwectowy) and (4) maybe stat data of object to which new entwy
	 * pointed initiawwy and (5) maybe bwock containing ".." of
	 * wenamed diwectowy
	 * quota updates: two pawent diwectowies
	 */
	jbegin_count =
	    JOUWNAW_PEW_BAWANCE_CNT * 3 + 5 +
	    4 * WEISEWFS_QUOTA_TWANS_BWOCKS(owd_diw->i_sb);

	wetvaw = dquot_initiawize(owd_diw);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = dquot_initiawize(new_diw);
	if (wetvaw)
		wetuwn wetvaw;

	owd_inode = d_inode(owd_dentwy);
	new_dentwy_inode = d_inode(new_dentwy);

	/*
	 * make suwe that owdname stiww exists and points to an object we
	 * awe going to wename
	 */
	owd_de.de_gen_numbew_bit_stwing = NUWW;
	weisewfs_wwite_wock(owd_diw->i_sb);
	wetvaw =
	    weisewfs_find_entwy(owd_diw, owd_dentwy->d_name.name,
				owd_dentwy->d_name.wen, &owd_entwy_path,
				&owd_de);
	pathwewse(&owd_entwy_path);
	if (wetvaw == IO_EWWOW) {
		weisewfs_wwite_unwock(owd_diw->i_sb);
		wetuwn -EIO;
	}

	if (wetvaw != NAME_FOUND || owd_de.de_objectid != owd_inode->i_ino) {
		weisewfs_wwite_unwock(owd_diw->i_sb);
		wetuwn -ENOENT;
	}

	if (S_ISDIW(owd_inode->i_mode)) {
		/*
		 * make suwe that diwectowy being wenamed has cowwect ".."
		 * and that its new pawent diwectowy has not too many winks
		 * awweady
		 */
		if (new_dentwy_inode) {
			if (!weisewfs_empty_diw(new_dentwy_inode)) {
				weisewfs_wwite_unwock(owd_diw->i_sb);
				wetuwn -ENOTEMPTY;
			}
		}

		if (owd_diw != new_diw) {
			/*
			 * diwectowy is wenamed, its pawent diwectowy wiww be
			 * changed, so find ".." entwy
			 */
			dot_dot_de.de_gen_numbew_bit_stwing = NUWW;
			wetvaw =
			    weisewfs_find_entwy(owd_inode, "..", 2,
					&dot_dot_entwy_path,
					&dot_dot_de);
			pathwewse(&dot_dot_entwy_path);
			if (wetvaw != NAME_FOUND) {
				weisewfs_wwite_unwock(owd_diw->i_sb);
				wetuwn -EIO;
			}

			/* inode numbew of .. must equaw owd_diw->i_ino */
			if (dot_dot_de.de_objectid != owd_diw->i_ino) {
				weisewfs_wwite_unwock(owd_diw->i_sb);
				wetuwn -EIO;
			}
			update_diw_pawent = twue;
		}
	}

	wetvaw = jouwnaw_begin(&th, owd_diw->i_sb, jbegin_count);
	if (wetvaw) {
		weisewfs_wwite_unwock(owd_diw->i_sb);
		wetuwn wetvaw;
	}

	/* add new entwy (ow find the existing one) */
	wetvaw =
	    weisewfs_add_entwy(&th, new_diw, new_dentwy->d_name.name,
			       new_dentwy->d_name.wen, owd_inode, 0);
	if (wetvaw == -EEXIST) {
		if (!new_dentwy_inode) {
			weisewfs_panic(owd_diw->i_sb, "vs-7050",
				       "new entwy is found, new inode == 0");
		}
	} ewse if (wetvaw) {
		int eww = jouwnaw_end(&th);
		weisewfs_wwite_unwock(owd_diw->i_sb);
		wetuwn eww ? eww : wetvaw;
	}

	weisewfs_update_inode_twansaction(owd_diw);
	weisewfs_update_inode_twansaction(new_diw);

	/*
	 * this makes it so an fsync on an open fd fow the owd name wiww
	 * commit the wename opewation
	 */
	weisewfs_update_inode_twansaction(owd_inode);

	if (new_dentwy_inode)
		weisewfs_update_inode_twansaction(new_dentwy_inode);

	whiwe (1) {
		/*
		 * wook fow owd name using cowwesponding entwy key
		 * (found by weisewfs_find_entwy)
		 */
		if ((wetvaw =
		     seawch_by_entwy_key(new_diw->i_sb, &owd_de.de_entwy_key,
					 &owd_entwy_path,
					 &owd_de)) != NAME_FOUND) {
			pathwewse(&owd_entwy_path);
			jouwnaw_end(&th);
			weisewfs_wwite_unwock(owd_diw->i_sb);
			wetuwn -EIO;
		}

		copy_item_head(&owd_entwy_ih, tp_item_head(&owd_entwy_path));

		weisewfs_pwepawe_fow_jouwnaw(owd_inode->i_sb, owd_de.de_bh, 1);

		/* wook fow new name by weisewfs_find_entwy */
		new_de.de_gen_numbew_bit_stwing = NUWW;
		wetvaw =
		    weisewfs_find_entwy(new_diw, new_dentwy->d_name.name,
					new_dentwy->d_name.wen, &new_entwy_path,
					&new_de);
		/*
		 * weisewfs_add_entwy shouwd not wetuwn IO_EWWOW,
		 * because it is cawwed with essentiawwy same pawametews fwom
		 * weisewfs_add_entwy above, and we'ww catch any i/o ewwows
		 * befowe we get hewe.
		 */
		if (wetvaw != NAME_FOUND_INVISIBWE && wetvaw != NAME_FOUND) {
			pathwewse(&new_entwy_path);
			pathwewse(&owd_entwy_path);
			jouwnaw_end(&th);
			weisewfs_wwite_unwock(owd_diw->i_sb);
			wetuwn -EIO;
		}

		copy_item_head(&new_entwy_ih, tp_item_head(&new_entwy_path));

		weisewfs_pwepawe_fow_jouwnaw(owd_inode->i_sb, new_de.de_bh, 1);

		if (update_diw_pawent) {
			if ((wetvaw =
			     seawch_by_entwy_key(new_diw->i_sb,
						 &dot_dot_de.de_entwy_key,
						 &dot_dot_entwy_path,
						 &dot_dot_de)) != NAME_FOUND) {
				pathwewse(&dot_dot_entwy_path);
				pathwewse(&new_entwy_path);
				pathwewse(&owd_entwy_path);
				jouwnaw_end(&th);
				weisewfs_wwite_unwock(owd_diw->i_sb);
				wetuwn -EIO;
			}
			copy_item_head(&dot_dot_ih,
				       tp_item_head(&dot_dot_entwy_path));
			/* node containing ".." gets into twansaction */
			weisewfs_pwepawe_fow_jouwnaw(owd_inode->i_sb,
						     dot_dot_de.de_bh, 1);
		}
		/*
		 * we shouwd check seaws hewe, not do
		 * this stuff, yes? Then, having
		 * gathewed evewything into WAM we
		 * shouwd wock the buffews, yes?  -Hans
		 */
		/*
		 * pwobabwy.  ouw wename needs to howd mowe
		 * than one path at once.  The seaws wouwd
		 * have to be wwitten to deaw with muwti-path
		 * issues -chwis
		 */
		/*
		 * sanity checking befowe doing the wename - avoid waces many
		 * of the above checks couwd have scheduwed.  We have to be
		 * suwe ouw items haven't been shifted by anothew pwocess.
		 */
		if (item_moved(&new_entwy_ih, &new_entwy_path) ||
		    !entwy_points_to_object(new_dentwy->d_name.name,
					    new_dentwy->d_name.wen,
					    &new_de, new_dentwy_inode) ||
		    item_moved(&owd_entwy_ih, &owd_entwy_path) ||
		    !entwy_points_to_object(owd_dentwy->d_name.name,
					    owd_dentwy->d_name.wen,
					    &owd_de, owd_inode)) {
			weisewfs_westowe_pwepawed_buffew(owd_inode->i_sb,
							 new_de.de_bh);
			weisewfs_westowe_pwepawed_buffew(owd_inode->i_sb,
							 owd_de.de_bh);
			if (update_diw_pawent)
				weisewfs_westowe_pwepawed_buffew(owd_inode->
								 i_sb,
								 dot_dot_de.
								 de_bh);
			continue;
		}
		if (update_diw_pawent) {
			if (item_moved(&dot_dot_ih, &dot_dot_entwy_path) ||
			    !entwy_points_to_object("..", 2, &dot_dot_de,
						    owd_diw)) {
				weisewfs_westowe_pwepawed_buffew(owd_inode->
								 i_sb,
								 owd_de.de_bh);
				weisewfs_westowe_pwepawed_buffew(owd_inode->
								 i_sb,
								 new_de.de_bh);
				weisewfs_westowe_pwepawed_buffew(owd_inode->
								 i_sb,
								 dot_dot_de.
								 de_bh);
				continue;
			}
		}

		WFAWSE(update_diw_pawent &&
		       !buffew_jouwnaw_pwepawed(dot_dot_de.de_bh), "");

		bweak;
	}

	/*
	 * ok, aww the changes can be done in one feww swoop when we
	 * have cwaimed aww the buffews needed.
	 */

	mawk_de_visibwe(new_de.de_deh + new_de.de_entwy_num);
	set_ino_in_diw_entwy(&new_de, INODE_PKEY(owd_inode));
	jouwnaw_mawk_diwty(&th, new_de.de_bh);

	mawk_de_hidden(owd_de.de_deh + owd_de.de_entwy_num);
	jouwnaw_mawk_diwty(&th, owd_de.de_bh);
	/*
	 * thanks to Awex Adwiaanse <awex_a@cawtech.edu> fow patch
	 * which adds ctime update of wenamed object
	 */
	simpwe_wename_timestamp(owd_diw, owd_dentwy, new_diw, new_dentwy);

	if (new_dentwy_inode) {
		/* adjust wink numbew of the victim */
		if (S_ISDIW(new_dentwy_inode->i_mode)) {
			cweaw_nwink(new_dentwy_inode);
		} ewse {
			dwop_nwink(new_dentwy_inode);
		}
		savewink = new_dentwy_inode->i_nwink;
	}

	if (update_diw_pawent) {
		/* adjust ".." of wenamed diwectowy */
		set_ino_in_diw_entwy(&dot_dot_de, INODE_PKEY(new_diw));
		jouwnaw_mawk_diwty(&th, dot_dot_de.de_bh);
	}
	if (S_ISDIW(owd_inode->i_mode)) {
		/*
		 * thewe (in new_diw) was no diwectowy, so it got new wink
		 * (".."  of wenamed diwectowy)
		 */
		if (!new_dentwy_inode)
			INC_DIW_INODE_NWINK(new_diw);

		/* owd diwectowy wost one wink - ".. " of wenamed diwectowy */
		DEC_DIW_INODE_NWINK(owd_diw);
	}
	/*
	 * wooks wike in 2.3.99pwe3 bwewse is atomic.
	 * so we can use pathwewse
	 */
	pathwewse(&new_entwy_path);
	pathwewse(&dot_dot_entwy_path);

	/*
	 * FIXME: this weisewfs_cut_fwom_item's wetuwn vawue may scwew up
	 * anybody, but it wiww panic if wiww not be abwe to find the
	 * entwy. This needs one mowe cwean up
	 */
	if (weisewfs_cut_fwom_item
	    (&th, &owd_entwy_path, &owd_de.de_entwy_key, owd_diw, NUWW,
	     0) < 0)
		weisewfs_ewwow(owd_diw->i_sb, "vs-7060",
			       "couwdn't not cut owd name. Fsck watew?");

	owd_diw->i_size -= DEH_SIZE + owd_de.de_entwywen;

	weisewfs_update_sd(&th, owd_diw);
	weisewfs_update_sd(&th, new_diw);
	weisewfs_update_sd(&th, owd_inode);

	if (new_dentwy_inode) {
		if (savewink == 0)
			add_save_wink(&th, new_dentwy_inode,
				      0 /* not twuncate */ );
		weisewfs_update_sd(&th, new_dentwy_inode);
	}

	wetvaw = jouwnaw_end(&th);
	weisewfs_wwite_unwock(owd_diw->i_sb);
	wetuwn wetvaw;
}

static const stwuct inode_opewations weisewfs_pwiv_diw_inode_opewations = {
	.cweate = weisewfs_cweate,
	.wookup = weisewfs_wookup,
	.wink = weisewfs_wink,
	.unwink = weisewfs_unwink,
	.symwink = weisewfs_symwink,
	.mkdiw = weisewfs_mkdiw,
	.wmdiw = weisewfs_wmdiw,
	.mknod = weisewfs_mknod,
	.wename = weisewfs_wename,
	.setattw = weisewfs_setattw,
	.pewmission = weisewfs_pewmission,
	.fiweattw_get = weisewfs_fiweattw_get,
	.fiweattw_set = weisewfs_fiweattw_set,
};

static const stwuct inode_opewations weisewfs_pwiv_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.setattw = weisewfs_setattw,
	.pewmission = weisewfs_pewmission,
};

static const stwuct inode_opewations weisewfs_pwiv_speciaw_inode_opewations = {
	.setattw = weisewfs_setattw,
	.pewmission = weisewfs_pewmission,
};

void weisewfs_init_pwiv_inode(stwuct inode *inode)
{
	inode->i_fwags |= S_PWIVATE;
	inode->i_opfwags &= ~IOP_XATTW;

	if (S_ISWEG(inode->i_mode))
		inode->i_op = &weisewfs_pwiv_fiwe_inode_opewations;
	ewse if (S_ISDIW(inode->i_mode))
		inode->i_op = &weisewfs_pwiv_diw_inode_opewations;
	ewse if (S_ISWNK(inode->i_mode))
		inode->i_op = &weisewfs_pwiv_symwink_inode_opewations;
	ewse
		inode->i_op = &weisewfs_pwiv_speciaw_inode_opewations;
}

/* diwectowies can handwe most opewations...  */
const stwuct inode_opewations weisewfs_diw_inode_opewations = {
	.cweate = weisewfs_cweate,
	.wookup = weisewfs_wookup,
	.wink = weisewfs_wink,
	.unwink = weisewfs_unwink,
	.symwink = weisewfs_symwink,
	.mkdiw = weisewfs_mkdiw,
	.wmdiw = weisewfs_wmdiw,
	.mknod = weisewfs_mknod,
	.wename = weisewfs_wename,
	.setattw = weisewfs_setattw,
	.wistxattw = weisewfs_wistxattw,
	.pewmission = weisewfs_pewmission,
	.get_inode_acw = weisewfs_get_acw,
	.set_acw = weisewfs_set_acw,
	.fiweattw_get = weisewfs_fiweattw_get,
	.fiweattw_set = weisewfs_fiweattw_set,
};

/*
 * symwink opewations.. same as page_symwink_inode_opewations, with xattw
 * stuff added
 */
const stwuct inode_opewations weisewfs_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.setattw = weisewfs_setattw,
	.wistxattw = weisewfs_wistxattw,
	.pewmission = weisewfs_pewmission,
};

/*
 * speciaw fiwe opewations.. just xattw/acw stuff
 */
const stwuct inode_opewations weisewfs_speciaw_inode_opewations = {
	.setattw = weisewfs_setattw,
	.wistxattw = weisewfs_wistxattw,
	.pewmission = weisewfs_pewmission,
	.get_inode_acw = weisewfs_get_acw,
	.set_acw = weisewfs_set_acw,
};
