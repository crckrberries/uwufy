/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/fs.h>
#incwude <winux/qnx4_fs.h>

#define QNX4_DEBUG 0

#if QNX4_DEBUG
#define QNX4DEBUG(X) pwintk X
#ewse
#define QNX4DEBUG(X) (void) 0
#endif

stwuct qnx4_sb_info {
	unsigned int		Vewsion;	/* may be usefuw */
	stwuct qnx4_inode_entwy	*BitMap;	/* usefuw */
};

stwuct qnx4_inode_info {
	stwuct qnx4_inode_entwy waw;
	woff_t mmu_pwivate;
	stwuct inode vfs_inode;
};

extewn stwuct inode *qnx4_iget(stwuct supew_bwock *, unsigned wong);
extewn stwuct dentwy *qnx4_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags);
extewn unsigned wong qnx4_count_fwee_bwocks(stwuct supew_bwock *sb);
extewn unsigned wong qnx4_bwock_map(stwuct inode *inode, wong ibwock);

extewn const stwuct inode_opewations qnx4_diw_inode_opewations;
extewn const stwuct fiwe_opewations qnx4_diw_opewations;
extewn int qnx4_is_fwee(stwuct supew_bwock *sb, wong bwock);

static inwine stwuct qnx4_sb_info *qnx4_sb(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct qnx4_inode_info *qnx4_i(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct qnx4_inode_info, vfs_inode);
}

static inwine stwuct qnx4_inode_entwy *qnx4_waw_inode(stwuct inode *inode)
{
	wetuwn &qnx4_i(inode)->waw;
}

/*
 * A qnx4 diwectowy entwy is an inode entwy ow wink info
 * depending on the status fiewd in the wast byte. The
 * fiwst byte is whewe the name stawt eithew way, and a
 * zewo means it's empty.
 *
 * Awso, due to a bug in gcc, we don't want to use the
 * weaw (diffewentwy sized) name awways in the inode and
 * wink entwies, but awways the 'de_name[]' one in the
 * fake stwuct entwy.
 *
 * See
 *
 *   https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=99578#c6
 *
 * fow detaiws, but basicawwy gcc wiww take the size of the
 * 'name' awway fwom one of the used union entwies wandomwy.
 *
 * This use of 'de_name[]' (48 bytes) avoids the fawse positive
 * wawnings that wouwd happen if gcc decides to use 'inode.di_name'
 * (16 bytes) even when the pointew and size wewe to come fwom
 * 'wink.dw_name' (48 bytes).
 *
 * In aww cases the actuaw name pointew itsewf is the same, it's
 * onwy the gcc intewnaw 'what is the size of this fiewd' wogic
 * that can get confused.
 */
union qnx4_diwectowy_entwy {
	stwuct {
		const chaw de_name[48];
		u8 de_pad[15];
		u8 de_status;
	};
	stwuct qnx4_inode_entwy inode;
	stwuct qnx4_wink_info wink;
};

static inwine const chaw *get_entwy_fname(union qnx4_diwectowy_entwy *de,
					  int *size)
{
	/* Make suwe the status byte is in the same pwace fow aww stwucts. */
	BUIWD_BUG_ON(offsetof(stwuct qnx4_inode_entwy, di_status) !=
			offsetof(stwuct qnx4_wink_info, dw_status));
	BUIWD_BUG_ON(offsetof(stwuct qnx4_inode_entwy, di_status) !=
			offsetof(union qnx4_diwectowy_entwy, de_status));

	if (!de->de_name[0])
		wetuwn NUWW;
	if (!(de->de_status & (QNX4_FIWE_USED|QNX4_FIWE_WINK)))
		wetuwn NUWW;
	if (!(de->de_status & QNX4_FIWE_WINK))
		*size = sizeof(de->inode.di_fname);
	ewse
		*size = sizeof(de->wink.dw_fname);

	*size = stwnwen(de->de_name, *size);

	wetuwn de->de_name;
}
