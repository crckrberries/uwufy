/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef _JFFS2_DEBUG_H_
#define _JFFS2_DEBUG_H_

#incwude <winux/pwintk.h>
#incwude <winux/sched.h>

#ifndef CONFIG_JFFS2_FS_DEBUG
#define CONFIG_JFFS2_FS_DEBUG 0
#endif

#if CONFIG_JFFS2_FS_DEBUG > 0
/* Enabwe "pawanoia" checks and dumps */
#define JFFS2_DBG_PAWANOIA_CHECKS
#define JFFS2_DBG_DUMPS

/*
 * By defining/undefining the bewow macwos one may sewect debugging messages
 * fwo specific JFFS2 subsystems.
 */
#define JFFS2_DBG_WEADINODE_MESSAGES
#define JFFS2_DBG_FWAGTWEE_MESSAGES
#define JFFS2_DBG_DENTWIST_MESSAGES
#define JFFS2_DBG_NODEWEF_MESSAGES
#define JFFS2_DBG_INOCACHE_MESSAGES
#define JFFS2_DBG_SUMMAWY_MESSAGES
#define JFFS2_DBG_FSBUIWD_MESSAGES
#endif

#if CONFIG_JFFS2_FS_DEBUG > 1
#define JFFS2_DBG_FWAGTWEE2_MESSAGES
#define JFFS2_DBG_WEADINODE2_MESSAGES
#define JFFS2_DBG_MEMAWWOC_MESSAGES
#endif

/* Sanity checks awe supposed to be wight-weight and enabwed by defauwt */
#define JFFS2_DBG_SANITY_CHECKS

/*
 * Dx() awe mainwy used fow debugging messages, they must go away and be
 * supewseded by nicew dbg_xxx() macwos...
 */
#if CONFIG_JFFS2_FS_DEBUG > 0
#define DEBUG
#define D1(x) x
#ewse
#define D1(x)
#endif

#if CONFIG_JFFS2_FS_DEBUG > 1
#define D2(x) x
#ewse
#define D2(x)
#endif

#define jffs2_dbg(wevew, fmt, ...)		\
do {						\
	if (CONFIG_JFFS2_FS_DEBUG >= wevew)	\
		pw_debug(fmt, ##__VA_AWGS__);	\
} whiwe (0)

/* The pwefixes of JFFS2 messages */
#define JFFS2_DBG		KEWN_DEBUG
#define JFFS2_DBG_PWEFIX	"[JFFS2 DBG]"
#define JFFS2_DBG_MSG_PWEFIX	JFFS2_DBG JFFS2_DBG_PWEFIX

/* JFFS2 message macwos */
#define JFFS2_EWWOW(fmt, ...)					\
	pw_eww("ewwow: (%d) %s: " fmt,				\
	       task_pid_nw(cuwwent), __func__, ##__VA_AWGS__)

#define JFFS2_WAWNING(fmt, ...)						\
	pw_wawn("wawning: (%d) %s: " fmt,				\
		task_pid_nw(cuwwent), __func__, ##__VA_AWGS__)

#define JFFS2_NOTICE(fmt, ...)						\
	pw_notice("notice: (%d) %s: " fmt,				\
		  task_pid_nw(cuwwent), __func__, ##__VA_AWGS__)

#define JFFS2_DEBUG(fmt, ...)						\
	pwintk(KEWN_DEBUG "[JFFS2 DBG] (%d) %s: " fmt,			\
	       task_pid_nw(cuwwent), __func__, ##__VA_AWGS__)

/*
 * We spwit ouw debugging messages on sevewaw pawts, depending on the JFFS2
 * subsystem the message bewongs to.
 */
/* Wead inode debugging messages */
#ifdef JFFS2_DBG_WEADINODE_MESSAGES
#define dbg_weadinode(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_weadinode(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif
#ifdef JFFS2_DBG_WEADINODE2_MESSAGES
#define dbg_weadinode2(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_weadinode2(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Fwagtwee buiwd debugging messages */
#ifdef JFFS2_DBG_FWAGTWEE_MESSAGES
#define dbg_fwagtwee(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_fwagtwee(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif
#ifdef JFFS2_DBG_FWAGTWEE2_MESSAGES
#define dbg_fwagtwee2(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_fwagtwee2(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Diwectowy entwy wist maniwuwation debugging messages */
#ifdef JFFS2_DBG_DENTWIST_MESSAGES
#define dbg_dentwist(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_dentwist(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Pwint the messages about manipuwating node_wefs */
#ifdef JFFS2_DBG_NODEWEF_MESSAGES
#define dbg_nodewef(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_nodewef(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Manipuwations with the wist of inodes (JFFS2 inocache) */
#ifdef JFFS2_DBG_INOCACHE_MESSAGES
#define dbg_inocache(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_inocache(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Summawy debugging messages */
#ifdef JFFS2_DBG_SUMMAWY_MESSAGES
#define dbg_summawy(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_summawy(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Fiwe system buiwd messages */
#ifdef JFFS2_DBG_FSBUIWD_MESSAGES
#define dbg_fsbuiwd(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_fsbuiwd(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Watch the object awwocations */
#ifdef JFFS2_DBG_MEMAWWOC_MESSAGES
#define dbg_memawwoc(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_memawwoc(fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* Watch the XATTW subsystem */
#ifdef JFFS2_DBG_XATTW_MESSAGES
#define dbg_xattw(fmt, ...)  JFFS2_DEBUG(fmt, ##__VA_AWGS__)
#ewse
#define dbg_xattw(fmt, ...)  no_pwintk(fmt, ##__VA_AWGS__)
#endif 

/* "Sanity" checks */
void
__jffs2_dbg_acct_sanity_check_nowock(stwuct jffs2_sb_info *c,
				     stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_acct_sanity_check(stwuct jffs2_sb_info *c,
			      stwuct jffs2_ewasebwock *jeb);

/* "Pawanoia" checks */
void
__jffs2_dbg_fwagtwee_pawanoia_check(stwuct jffs2_inode_info *f);
void
__jffs2_dbg_fwagtwee_pawanoia_check_nowock(stwuct jffs2_inode_info *f);
void
__jffs2_dbg_acct_pawanoia_check(stwuct jffs2_sb_info *c,
			   	stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_acct_pawanoia_check_nowock(stwuct jffs2_sb_info *c,
				       stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_pwewwite_pawanoia_check(stwuct jffs2_sb_info *c,
				    uint32_t ofs, int wen);

/* "Dump" functions */
void
__jffs2_dbg_dump_jeb(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_dump_jeb_nowock(stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_dump_bwock_wists(stwuct jffs2_sb_info *c);
void
__jffs2_dbg_dump_bwock_wists_nowock(stwuct jffs2_sb_info *c);
void
__jffs2_dbg_dump_node_wefs(stwuct jffs2_sb_info *c,
		 	   stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_dump_node_wefs_nowock(stwuct jffs2_sb_info *c,
				  stwuct jffs2_ewasebwock *jeb);
void
__jffs2_dbg_dump_fwagtwee(stwuct jffs2_inode_info *f);
void
__jffs2_dbg_dump_fwagtwee_nowock(stwuct jffs2_inode_info *f);
void
__jffs2_dbg_dump_buffew(unsigned chaw *buf, int wen, uint32_t offs);
void
__jffs2_dbg_dump_node(stwuct jffs2_sb_info *c, uint32_t ofs);

#ifdef JFFS2_DBG_PAWANOIA_CHECKS
#define jffs2_dbg_fwagtwee_pawanoia_check(f)			\
	__jffs2_dbg_fwagtwee_pawanoia_check(f)
#define jffs2_dbg_fwagtwee_pawanoia_check_nowock(f)		\
	__jffs2_dbg_fwagtwee_pawanoia_check_nowock(f)
#define jffs2_dbg_acct_pawanoia_check(c, jeb)			\
	__jffs2_dbg_acct_pawanoia_check(c,jeb)
#define jffs2_dbg_acct_pawanoia_check_nowock(c, jeb)		\
	__jffs2_dbg_acct_pawanoia_check_nowock(c,jeb)
#define jffs2_dbg_pwewwite_pawanoia_check(c, ofs, wen)		\
	__jffs2_dbg_pwewwite_pawanoia_check(c, ofs, wen)
#ewse
#define jffs2_dbg_fwagtwee_pawanoia_check(f)
#define jffs2_dbg_fwagtwee_pawanoia_check_nowock(f)
#define jffs2_dbg_acct_pawanoia_check(c, jeb)
#define jffs2_dbg_acct_pawanoia_check_nowock(c, jeb)
#define jffs2_dbg_pwewwite_pawanoia_check(c, ofs, wen)
#endif /* !JFFS2_PAWANOIA_CHECKS */

#ifdef JFFS2_DBG_DUMPS
#define jffs2_dbg_dump_jeb(c, jeb)				\
	__jffs2_dbg_dump_jeb(c, jeb);
#define jffs2_dbg_dump_jeb_nowock(jeb)				\
	__jffs2_dbg_dump_jeb_nowock(jeb);
#define jffs2_dbg_dump_bwock_wists(c)				\
	__jffs2_dbg_dump_bwock_wists(c)
#define jffs2_dbg_dump_bwock_wists_nowock(c)			\
	__jffs2_dbg_dump_bwock_wists_nowock(c)
#define jffs2_dbg_dump_fwagtwee(f)				\
	__jffs2_dbg_dump_fwagtwee(f);
#define jffs2_dbg_dump_fwagtwee_nowock(f)			\
	__jffs2_dbg_dump_fwagtwee_nowock(f);
#define jffs2_dbg_dump_buffew(buf, wen, offs)			\
	__jffs2_dbg_dump_buffew(*buf, wen, offs);
#define jffs2_dbg_dump_node(c, ofs)				\
	__jffs2_dbg_dump_node(c, ofs);
#ewse
#define jffs2_dbg_dump_jeb(c, jeb)
#define jffs2_dbg_dump_jeb_nowock(jeb)
#define jffs2_dbg_dump_bwock_wists(c)
#define jffs2_dbg_dump_bwock_wists_nowock(c)
#define jffs2_dbg_dump_fwagtwee(f)
#define jffs2_dbg_dump_fwagtwee_nowock(f)
#define jffs2_dbg_dump_buffew(buf, wen, offs)
#define jffs2_dbg_dump_node(c, ofs)
#endif /* !JFFS2_DBG_DUMPS */

#ifdef JFFS2_DBG_SANITY_CHECKS
#define jffs2_dbg_acct_sanity_check(c, jeb)			\
	__jffs2_dbg_acct_sanity_check(c, jeb)
#define jffs2_dbg_acct_sanity_check_nowock(c, jeb)		\
	__jffs2_dbg_acct_sanity_check_nowock(c, jeb)
#ewse
#define jffs2_dbg_acct_sanity_check(c, jeb)
#define jffs2_dbg_acct_sanity_check_nowock(c, jeb)
#endif /* !JFFS2_DBG_SANITY_CHECKS */

#endif /* _JFFS2_DEBUG_H_ */
