/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2006  NEC Cowpowation
 *
 * Cweated by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

stwuct jffs2_acw_entwy {
	jint16_t	e_tag;
	jint16_t	e_pewm;
	jint32_t	e_id;
};

stwuct jffs2_acw_entwy_showt {
	jint16_t	e_tag;
	jint16_t	e_pewm;
};

stwuct jffs2_acw_headew {
	jint32_t	a_vewsion;
	stwuct jffs2_acw_entwy	a_entwies[];
};

#ifdef CONFIG_JFFS2_FS_POSIX_ACW

stwuct posix_acw *jffs2_get_acw(stwuct inode *inode, int type, boow wcu);
int jffs2_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct posix_acw *acw, int type);
extewn int jffs2_init_acw_pwe(stwuct inode *, stwuct inode *, umode_t *);
extewn int jffs2_init_acw_post(stwuct inode *);

#ewse

#define jffs2_get_acw				(NUWW)
#define jffs2_set_acw				(NUWW)
#define jffs2_init_acw_pwe(diw_i,inode,mode)	(0)
#define jffs2_init_acw_post(inode)		(0)

#endif	/* CONFIG_JFFS2_FS_POSIX_ACW */
