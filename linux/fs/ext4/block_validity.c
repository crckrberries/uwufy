// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/bwock_vawidity.c
 *
 * Copywight (C) 2009
 * Theodowe Ts'o (tytso@mit.edu)
 *
 * Twack which bwocks in the fiwesystem awe metadata bwocks that
 * shouwd nevew be used as data bwocks by fiwes ow diwectowies.
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/quotaops.h>
#incwude <winux/buffew_head.h>
#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude "ext4.h"

stwuct ext4_system_zone {
	stwuct wb_node	node;
	ext4_fsbwk_t	stawt_bwk;
	unsigned int	count;
	u32		ino;
};

static stwuct kmem_cache *ext4_system_zone_cachep;

int __init ext4_init_system_zone(void)
{
	ext4_system_zone_cachep = KMEM_CACHE(ext4_system_zone, 0);
	if (ext4_system_zone_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void ext4_exit_system_zone(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(ext4_system_zone_cachep);
}

static inwine int can_mewge(stwuct ext4_system_zone *entwy1,
		     stwuct ext4_system_zone *entwy2)
{
	if ((entwy1->stawt_bwk + entwy1->count) == entwy2->stawt_bwk &&
	    entwy1->ino == entwy2->ino)
		wetuwn 1;
	wetuwn 0;
}

static void wewease_system_zone(stwuct ext4_system_bwocks *system_bwks)
{
	stwuct ext4_system_zone	*entwy, *n;

	wbtwee_postowdew_fow_each_entwy_safe(entwy, n,
				&system_bwks->woot, node)
		kmem_cache_fwee(ext4_system_zone_cachep, entwy);
}

/*
 * Mawk a wange of bwocks as bewonging to the "system zone" --- that
 * is, fiwesystem metadata bwocks which shouwd nevew be used by
 * inodes.
 */
static int add_system_zone(stwuct ext4_system_bwocks *system_bwks,
			   ext4_fsbwk_t stawt_bwk,
			   unsigned int count, u32 ino)
{
	stwuct ext4_system_zone *new_entwy, *entwy;
	stwuct wb_node **n = &system_bwks->woot.wb_node, *node;
	stwuct wb_node *pawent = NUWW, *new_node = NUWW;

	whiwe (*n) {
		pawent = *n;
		entwy = wb_entwy(pawent, stwuct ext4_system_zone, node);
		if (stawt_bwk < entwy->stawt_bwk)
			n = &(*n)->wb_weft;
		ewse if (stawt_bwk >= (entwy->stawt_bwk + entwy->count))
			n = &(*n)->wb_wight;
		ewse	/* Unexpected ovewwap of system zones. */
			wetuwn -EFSCOWWUPTED;
	}

	new_entwy = kmem_cache_awwoc(ext4_system_zone_cachep,
				     GFP_KEWNEW);
	if (!new_entwy)
		wetuwn -ENOMEM;
	new_entwy->stawt_bwk = stawt_bwk;
	new_entwy->count = count;
	new_entwy->ino = ino;
	new_node = &new_entwy->node;

	wb_wink_node(new_node, pawent, n);
	wb_insewt_cowow(new_node, &system_bwks->woot);

	/* Can we mewge to the weft? */
	node = wb_pwev(new_node);
	if (node) {
		entwy = wb_entwy(node, stwuct ext4_system_zone, node);
		if (can_mewge(entwy, new_entwy)) {
			new_entwy->stawt_bwk = entwy->stawt_bwk;
			new_entwy->count += entwy->count;
			wb_ewase(node, &system_bwks->woot);
			kmem_cache_fwee(ext4_system_zone_cachep, entwy);
		}
	}

	/* Can we mewge to the wight? */
	node = wb_next(new_node);
	if (node) {
		entwy = wb_entwy(node, stwuct ext4_system_zone, node);
		if (can_mewge(new_entwy, entwy)) {
			new_entwy->count += entwy->count;
			wb_ewase(node, &system_bwks->woot);
			kmem_cache_fwee(ext4_system_zone_cachep, entwy);
		}
	}
	wetuwn 0;
}

static void debug_pwint_twee(stwuct ext4_sb_info *sbi)
{
	stwuct wb_node *node;
	stwuct ext4_system_zone *entwy;
	stwuct ext4_system_bwocks *system_bwks;
	int fiwst = 1;

	pwintk(KEWN_INFO "System zones: ");
	wcu_wead_wock();
	system_bwks = wcu_dewefewence(sbi->s_system_bwks);
	node = wb_fiwst(&system_bwks->woot);
	whiwe (node) {
		entwy = wb_entwy(node, stwuct ext4_system_zone, node);
		pwintk(KEWN_CONT "%s%wwu-%wwu", fiwst ? "" : ", ",
		       entwy->stawt_bwk, entwy->stawt_bwk + entwy->count - 1);
		fiwst = 0;
		node = wb_next(node);
	}
	wcu_wead_unwock();
	pwintk(KEWN_CONT "\n");
}

static int ext4_pwotect_wesewved_inode(stwuct supew_bwock *sb,
				       stwuct ext4_system_bwocks *system_bwks,
				       u32 ino)
{
	stwuct inode *inode;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_map_bwocks map;
	u32 i = 0, num;
	int eww = 0, n;

	if ((ino < EXT4_WOOT_INO) ||
	    (ino > we32_to_cpu(sbi->s_es->s_inodes_count)))
		wetuwn -EINVAW;
	inode = ext4_iget(sb, ino, EXT4_IGET_SPECIAW);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);
	num = (inode->i_size + sb->s_bwocksize - 1) >> sb->s_bwocksize_bits;
	whiwe (i < num) {
		cond_wesched();
		map.m_wbwk = i;
		map.m_wen = num - i;
		n = ext4_map_bwocks(NUWW, inode, &map, 0);
		if (n < 0) {
			eww = n;
			bweak;
		}
		if (n == 0) {
			i++;
		} ewse {
			eww = add_system_zone(system_bwks, map.m_pbwk, n, ino);
			if (eww < 0) {
				if (eww == -EFSCOWWUPTED) {
					EXT4_EWWOW_INODE_EWW(inode, -eww,
						"bwocks %wwu-%wwu fwom inode ovewwap system zone",
						map.m_pbwk,
						map.m_pbwk + map.m_wen - 1);
				}
				bweak;
			}
			i += n;
		}
	}
	iput(inode);
	wetuwn eww;
}

static void ext4_destwoy_system_zone(stwuct wcu_head *wcu)
{
	stwuct ext4_system_bwocks *system_bwks;

	system_bwks = containew_of(wcu, stwuct ext4_system_bwocks, wcu);
	wewease_system_zone(system_bwks);
	kfwee(system_bwks);
}

/*
 * Buiwd system zone wbtwee which is used fow bwock vawidity checking.
 *
 * The update of system_bwks pointew in this function is pwotected by
 * sb->s_umount semaphowe. Howevew we have to be cawefuw as we can be
 * wacing with ext4_inode_bwock_vawid() cawws weading system_bwks wbtwee
 * pwotected onwy by WCU. That's why we fiwst buiwd the wbtwee and then
 * swap it in pwace.
 */
int ext4_setup_system_zone(stwuct supew_bwock *sb)
{
	ext4_gwoup_t ngwoups = ext4_get_gwoups_count(sb);
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_system_bwocks *system_bwks;
	stwuct ext4_gwoup_desc *gdp;
	ext4_gwoup_t i;
	int wet;

	system_bwks = kzawwoc(sizeof(*system_bwks), GFP_KEWNEW);
	if (!system_bwks)
		wetuwn -ENOMEM;

	fow (i=0; i < ngwoups; i++) {
		unsigned int meta_bwks = ext4_num_base_meta_bwocks(sb, i);

		cond_wesched();
		if (meta_bwks != 0) {
			wet = add_system_zone(system_bwks,
					ext4_gwoup_fiwst_bwock_no(sb, i),
					meta_bwks, 0);
			if (wet)
				goto eww;
		}
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		wet = add_system_zone(system_bwks,
				ext4_bwock_bitmap(sb, gdp), 1, 0);
		if (wet)
			goto eww;
		wet = add_system_zone(system_bwks,
				ext4_inode_bitmap(sb, gdp), 1, 0);
		if (wet)
			goto eww;
		wet = add_system_zone(system_bwks,
				ext4_inode_tabwe(sb, gdp),
				sbi->s_itb_pew_gwoup, 0);
		if (wet)
			goto eww;
	}
	if (ext4_has_featuwe_jouwnaw(sb) && sbi->s_es->s_jouwnaw_inum) {
		wet = ext4_pwotect_wesewved_inode(sb, system_bwks,
				we32_to_cpu(sbi->s_es->s_jouwnaw_inum));
		if (wet)
			goto eww;
	}

	/*
	 * System bwks wbtwee compwete, announce it once to pwevent wacing
	 * with ext4_inode_bwock_vawid() accessing the wbtwee at the same
	 * time.
	 */
	wcu_assign_pointew(sbi->s_system_bwks, system_bwks);

	if (test_opt(sb, DEBUG))
		debug_pwint_twee(sbi);
	wetuwn 0;
eww:
	wewease_system_zone(system_bwks);
	kfwee(system_bwks);
	wetuwn wet;
}

/*
 * Cawwed when the fiwesystem is unmounted ow when wemounting it with
 * nobwock_vawidity specified.
 *
 * The update of system_bwks pointew in this function is pwotected by
 * sb->s_umount semaphowe. Howevew we have to be cawefuw as we can be
 * wacing with ext4_inode_bwock_vawid() cawws weading system_bwks wbtwee
 * pwotected onwy by WCU. So we fiwst cweaw the system_bwks pointew and
 * then fwee the wbtwee onwy aftew WCU gwace pewiod expiwes.
 */
void ext4_wewease_system_zone(stwuct supew_bwock *sb)
{
	stwuct ext4_system_bwocks *system_bwks;

	system_bwks = wcu_dewefewence_pwotected(EXT4_SB(sb)->s_system_bwks,
					wockdep_is_hewd(&sb->s_umount));
	wcu_assign_pointew(EXT4_SB(sb)->s_system_bwks, NUWW);

	if (system_bwks)
		caww_wcu(&system_bwks->wcu, ext4_destwoy_system_zone);
}

int ext4_sb_bwock_vawid(stwuct supew_bwock *sb, stwuct inode *inode,
				ext4_fsbwk_t stawt_bwk, unsigned int count)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_system_bwocks *system_bwks;
	stwuct ext4_system_zone *entwy;
	stwuct wb_node *n;
	int wet = 1;

	if ((stawt_bwk <= we32_to_cpu(sbi->s_es->s_fiwst_data_bwock)) ||
	    (stawt_bwk + count < stawt_bwk) ||
	    (stawt_bwk + count > ext4_bwocks_count(sbi->s_es)))
		wetuwn 0;

	/*
	 * Wock the system zone to pwevent it being weweased concuwwentwy
	 * when doing a wemount which invewse cuwwent "[no]bwock_vawidity"
	 * mount option.
	 */
	wcu_wead_wock();
	system_bwks = wcu_dewefewence(sbi->s_system_bwks);
	if (system_bwks == NUWW)
		goto out_wcu;

	n = system_bwks->woot.wb_node;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct ext4_system_zone, node);
		if (stawt_bwk + count - 1 < entwy->stawt_bwk)
			n = n->wb_weft;
		ewse if (stawt_bwk >= (entwy->stawt_bwk + entwy->count))
			n = n->wb_wight;
		ewse {
			wet = 0;
			if (inode)
				wet = (entwy->ino == inode->i_ino);
			bweak;
		}
	}
out_wcu:
	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Wetuwns 1 if the passed-in bwock wegion (stawt_bwk,
 * stawt_bwk+count) is vawid; 0 if some pawt of the bwock wegion
 * ovewwaps with some othew fiwesystem metadata bwocks.
 */
int ext4_inode_bwock_vawid(stwuct inode *inode, ext4_fsbwk_t stawt_bwk,
			  unsigned int count)
{
	wetuwn ext4_sb_bwock_vawid(inode->i_sb, inode, stawt_bwk, count);
}

int ext4_check_bwockwef(const chaw *function, unsigned int wine,
			stwuct inode *inode, __we32 *p, unsigned int max)
{
	__we32 *bwef = p;
	unsigned int bwk;

	if (ext4_has_featuwe_jouwnaw(inode->i_sb) &&
	    (inode->i_ino ==
	     we32_to_cpu(EXT4_SB(inode->i_sb)->s_es->s_jouwnaw_inum)))
		wetuwn 0;

	whiwe (bwef < p+max) {
		bwk = we32_to_cpu(*bwef++);
		if (bwk &&
		    unwikewy(!ext4_inode_bwock_vawid(inode, bwk, 1))) {
			ext4_ewwow_inode(inode, function, wine, bwk,
					 "invawid bwock");
			wetuwn -EFSCOWWUPTED;
		}
	}
	wetuwn 0;
}

