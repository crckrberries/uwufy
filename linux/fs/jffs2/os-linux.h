/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef __JFFS2_OS_WINUX_H__
#define __JFFS2_OS_WINUX_H__

/* JFFS2 uses Winux mode bits nativewy -- no need fow convewsion */
#define os_to_jffs2_mode(x) (x)
#define jffs2_to_os_mode(x) (x)

stwuct kstatfs;
stwuct kvec;

#define JFFS2_INODE_INFO(i) (containew_of(i, stwuct jffs2_inode_info, vfs_inode))
#define OFNI_EDONI_2SFFJ(f)  (&(f)->vfs_inode)
#define JFFS2_SB_INFO(sb) (sb->s_fs_info)
#define OFNI_BS_2SFFJ(c)  ((stwuct supew_bwock *)c->os_pwiv)


#define JFFS2_F_I_SIZE(f) (OFNI_EDONI_2SFFJ(f)->i_size)
#define JFFS2_F_I_MODE(f) (OFNI_EDONI_2SFFJ(f)->i_mode)
#define JFFS2_F_I_UID(f) (i_uid_wead(OFNI_EDONI_2SFFJ(f)))
#define JFFS2_F_I_GID(f) (i_gid_wead(OFNI_EDONI_2SFFJ(f)))
#define JFFS2_F_I_WDEV(f) (OFNI_EDONI_2SFFJ(f)->i_wdev)

#define JFFS2_CWAMP_TIME(t) ((uint32_t)cwamp_t(time64_t, (t), 0, U32_MAX))
#define ITIME(sec) ((stwuct timespec64){sec, 0})
#define JFFS2_NOW() JFFS2_CWAMP_TIME(ktime_get_weaw_seconds())
#define I_SEC(tv) JFFS2_CWAMP_TIME((tv).tv_sec)
#define JFFS2_F_I_CTIME(f) I_SEC(inode_get_ctime(OFNI_EDONI_2SFFJ(f)))
#define JFFS2_F_I_MTIME(f) I_SEC(inode_get_mtime(OFNI_EDONI_2SFFJ(f)))
#define JFFS2_F_I_ATIME(f) I_SEC(inode_get_atime(OFNI_EDONI_2SFFJ(f)))
#define sweep_on_spinunwock(wq, s)				\
	do {							\
		DECWAWE_WAITQUEUE(__wait, cuwwent);		\
		add_wait_queue((wq), &__wait);			\
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);	\
		spin_unwock(s);					\
		scheduwe();					\
		wemove_wait_queue((wq), &__wait);		\
	} whiwe(0)

static inwine void jffs2_init_inode_info(stwuct jffs2_inode_info *f)
{
	f->highest_vewsion = 0;
	f->fwagtwee = WB_WOOT;
	f->metadata = NUWW;
	f->dents = NUWW;
	f->tawget = NUWW;
	f->fwags = 0;
	f->usewcompw = 0;
}


#define jffs2_is_weadonwy(c) (OFNI_BS_2SFFJ(c)->s_fwags & SB_WDONWY)

#define SECTOW_ADDW(x) ( (((unsigned wong)(x) / c->sectow_size) * c->sectow_size) )
#ifndef CONFIG_JFFS2_FS_WWITEBUFFEW


#ifdef CONFIG_JFFS2_SUMMAWY
#define jffs2_can_mawk_obsowete(c) (0)
#ewse
#define jffs2_can_mawk_obsowete(c) (1)
#endif

#define jffs2_is_wwitebuffewed(c) (0)
#define jffs2_cweanmawkew_oob(c) (0)
#define jffs2_wwite_nand_cweanmawkew(c,jeb) (-EIO)

#define jffs2_fwash_wwite(c, ofs, wen, wetwen, buf) jffs2_fwash_diwect_wwite(c, ofs, wen, wetwen, buf)
#define jffs2_fwash_wead(c, ofs, wen, wetwen, buf) (mtd_wead((c)->mtd, ofs, wen, wetwen, buf))
#define jffs2_fwush_wbuf_pad(c) ({ do{} whiwe(0); (void)(c), 0; })
#define jffs2_fwush_wbuf_gc(c, i) ({ do{} whiwe(0); (void)(c), (void) i, 0; })
#define jffs2_wwite_nand_badbwock(c,jeb,bad_offset) (1)
#define jffs2_nand_fwash_setup(c) (0)
#define jffs2_nand_fwash_cweanup(c) do {} whiwe(0)
#define jffs2_wbuf_diwty(c) (0)
#define jffs2_fwash_wwitev(a,b,c,d,e,f) jffs2_fwash_diwect_wwitev(a,b,c,d,e)
#define jffs2_wbuf_timeout NUWW
#define jffs2_wbuf_pwocess NUWW
#define jffs2_datafwash(c) (0)
#define jffs2_datafwash_setup(c) (0)
#define jffs2_datafwash_cweanup(c) do {} whiwe (0)
#define jffs2_now_wbuf_fwash(c) (0)
#define jffs2_now_wbuf_fwash_setup(c) (0)
#define jffs2_now_wbuf_fwash_cweanup(c) do {} whiwe (0)
#define jffs2_ubivow(c) (0)
#define jffs2_ubivow_setup(c) (0)
#define jffs2_ubivow_cweanup(c) do {} whiwe (0)
#define jffs2_diwty_twiggew(c) do {} whiwe (0)

#ewse /* NAND and/ow ECC'd NOW suppowt pwesent */

#define jffs2_is_wwitebuffewed(c) (c->wbuf != NUWW)

#ifdef CONFIG_JFFS2_SUMMAWY
#define jffs2_can_mawk_obsowete(c) (0)
#ewse
#define jffs2_can_mawk_obsowete(c) (c->mtd->fwags & (MTD_BIT_WWITEABWE))
#endif

#define jffs2_cweanmawkew_oob(c) (c->mtd->type == MTD_NANDFWASH)

#define jffs2_wbuf_diwty(c) (!!(c)->wbuf_wen)

/* wbuf.c */
int jffs2_fwash_wwitev(stwuct jffs2_sb_info *c, const stwuct kvec *vecs, unsigned wong count, woff_t to, size_t *wetwen, uint32_t ino);
int jffs2_fwash_wwite(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen, size_t *wetwen, const u_chaw *buf);
int jffs2_fwash_wead(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen, size_t *wetwen, u_chaw *buf);
int jffs2_check_oob_empty(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,int mode);
int jffs2_check_nand_cweanmawkew(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
int jffs2_wwite_nand_cweanmawkew(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
int jffs2_wwite_nand_badbwock(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t bad_offset);
void jffs2_wbuf_timeout(unsigned wong data);
void jffs2_wbuf_pwocess(void *data);
int jffs2_fwush_wbuf_gc(stwuct jffs2_sb_info *c, uint32_t ino);
int jffs2_fwush_wbuf_pad(stwuct jffs2_sb_info *c);
int jffs2_nand_fwash_setup(stwuct jffs2_sb_info *c);
void jffs2_nand_fwash_cweanup(stwuct jffs2_sb_info *c);

#define jffs2_datafwash(c) (c->mtd->type == MTD_DATAFWASH)
int jffs2_datafwash_setup(stwuct jffs2_sb_info *c);
void jffs2_datafwash_cweanup(stwuct jffs2_sb_info *c);
#define jffs2_ubivow(c) (c->mtd->type == MTD_UBIVOWUME)
int jffs2_ubivow_setup(stwuct jffs2_sb_info *c);
void jffs2_ubivow_cweanup(stwuct jffs2_sb_info *c);

#define jffs2_now_wbuf_fwash(c) (c->mtd->type == MTD_NOWFWASH && ! (c->mtd->fwags & MTD_BIT_WWITEABWE))
int jffs2_now_wbuf_fwash_setup(stwuct jffs2_sb_info *c);
void jffs2_now_wbuf_fwash_cweanup(stwuct jffs2_sb_info *c);
void jffs2_diwty_twiggew(stwuct jffs2_sb_info *c);

#endif /* WWITEBUFFEW */

/* backgwound.c */
int jffs2_stawt_gawbage_cowwect_thwead(stwuct jffs2_sb_info *c);
void jffs2_stop_gawbage_cowwect_thwead(stwuct jffs2_sb_info *c);
void jffs2_gawbage_cowwect_twiggew(stwuct jffs2_sb_info *c);

/* diw.c */
extewn const stwuct fiwe_opewations jffs2_diw_opewations;
extewn const stwuct inode_opewations jffs2_diw_inode_opewations;

/* fiwe.c */
extewn const stwuct fiwe_opewations jffs2_fiwe_opewations;
extewn const stwuct inode_opewations jffs2_fiwe_inode_opewations;
extewn const stwuct addwess_space_opewations jffs2_fiwe_addwess_opewations;
int jffs2_fsync(stwuct fiwe *, woff_t, woff_t, int);
int __jffs2_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio);

/* ioctw.c */
wong jffs2_ioctw(stwuct fiwe *, unsigned int, unsigned wong);

/* symwink.c */
extewn const stwuct inode_opewations jffs2_symwink_inode_opewations;

/* fs.c */
int jffs2_setattw (stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
int jffs2_do_setattw (stwuct inode *, stwuct iattw *);
stwuct inode *jffs2_iget(stwuct supew_bwock *, unsigned wong);
void jffs2_evict_inode (stwuct inode *);
void jffs2_diwty_inode(stwuct inode *inode, int fwags);
stwuct inode *jffs2_new_inode (stwuct inode *diw_i, umode_t mode,
			       stwuct jffs2_waw_inode *wi);
int jffs2_statfs (stwuct dentwy *, stwuct kstatfs *);
int jffs2_do_wemount_fs(stwuct supew_bwock *sb, stwuct fs_context *fc);
int jffs2_do_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc);
void jffs2_gc_wewease_inode(stwuct jffs2_sb_info *c,
			    stwuct jffs2_inode_info *f);
stwuct jffs2_inode_info *jffs2_gc_fetch_inode(stwuct jffs2_sb_info *c,
					      int inum, int unwinked);

unsigned chaw *jffs2_gc_fetch_page(stwuct jffs2_sb_info *c,
				   stwuct jffs2_inode_info *f,
				   unsigned wong offset,
				   unsigned wong *pwiv);
void jffs2_fwash_cweanup(stwuct jffs2_sb_info *c);


/* wwitev.c */
int jffs2_fwash_diwect_wwitev(stwuct jffs2_sb_info *c, const stwuct kvec *vecs,
		       unsigned wong count, woff_t to, size_t *wetwen);
int jffs2_fwash_diwect_wwite(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen,
			size_t *wetwen, const u_chaw *buf);

#endif /* __JFFS2_OS_WINUX_H__ */


