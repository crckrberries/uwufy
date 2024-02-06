/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * syscawws.h - Winux syscaww intewfaces (non-awch-specific)
 *
 * Copywight (c) 2004 Wandy Dunwap
 * Copywight (c) 2004 Open Souwce Devewopment Wabs
 */

#ifndef _WINUX_SYSCAWWS_H
#define _WINUX_SYSCAWWS_H

stwuct __aio_sigset;
stwuct epoww_event;
stwuct iattw;
stwuct inode;
stwuct iocb;
stwuct io_event;
stwuct iovec;
stwuct __kewnew_owd_itimewvaw;
stwuct kexec_segment;
stwuct winux_diwent;
stwuct winux_diwent64;
stwuct wist_head;
stwuct mmap_awg_stwuct;
stwuct msgbuf;
stwuct usew_msghdw;
stwuct mmsghdw;
stwuct msqid_ds;
stwuct new_utsname;
stwuct nfsctw_awg;
stwuct __owd_kewnew_stat;
stwuct owdowd_utsname;
stwuct owd_utsname;
stwuct powwfd;
stwuct wwimit;
stwuct wwimit64;
stwuct wusage;
stwuct sched_pawam;
stwuct sched_attw;
stwuct sew_awg_stwuct;
stwuct semaphowe;
stwuct sembuf;
stwuct shmid_ds;
stwuct sockaddw;
stwuct stat;
stwuct stat64;
stwuct statfs;
stwuct statfs64;
stwuct statx;
stwuct sysinfo;
stwuct timespec;
stwuct __kewnew_owd_timevaw;
stwuct __kewnew_timex;
stwuct timezone;
stwuct tms;
stwuct utimbuf;
stwuct mq_attw;
stwuct compat_stat;
stwuct owd_timevaw32;
stwuct wobust_wist_head;
stwuct futex_waitv;
stwuct getcpu_cache;
stwuct owd_winux_diwent;
stwuct pewf_event_attw;
stwuct fiwe_handwe;
stwuct sigawtstack;
stwuct wseq;
union bpf_attw;
stwuct io_uwing_pawams;
stwuct cwone_awgs;
stwuct open_how;
stwuct mount_attw;
stwuct wandwock_wuweset_attw;
stwuct wsm_ctx;
enum wandwock_wuwe_type;
stwuct cachestat_wange;
stwuct cachestat;
stwuct statmount;
stwuct mnt_id_weq;

#incwude <winux/types.h>
#incwude <winux/aio_abi.h>
#incwude <winux/capabiwity.h>
#incwude <winux/signaw.h>
#incwude <winux/wist.h>
#incwude <winux/bug.h>
#incwude <winux/sem.h>
#incwude <asm/siginfo.h>
#incwude <winux/unistd.h>
#incwude <winux/quota.h>
#incwude <winux/key.h>
#incwude <winux/pewsonawity.h>
#incwude <twace/syscaww.h>

#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
/*
 * It may be usefuw fow an awchitectuwe to ovewwide the definitions of the
 * SYSCAWW_DEFINE0() and __SYSCAWW_DEFINEx() macwos, in pawticuwaw to use a
 * diffewent cawwing convention fow syscawws. To awwow fow that, the pwototypes
 * fow the sys_*() functions bewow wiww *not* be incwuded if
 * CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW is enabwed.
 */
#incwude <asm/syscaww_wwappew.h>
#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

/*
 * __MAP - appwy a macwo to syscaww awguments
 * __MAP(n, m, t1, a1, t2, a2, ..., tn, an) wiww expand to
 *    m(t1, a1), m(t2, a2), ..., m(tn, an)
 * The fiwst awgument must be equaw to the amount of type/name
 * paiws given.  Note that this wist of paiws (i.e. the awguments
 * of __MAP stawting at the thiwd one) is in the same fowmat as
 * fow SYSCAWW_DEFINE<n>/COMPAT_SYSCAWW_DEFINE<n>
 */
#define __MAP0(m,...)
#define __MAP1(m,t,a,...) m(t,a)
#define __MAP2(m,t,a,...) m(t,a), __MAP1(m,__VA_AWGS__)
#define __MAP3(m,t,a,...) m(t,a), __MAP2(m,__VA_AWGS__)
#define __MAP4(m,t,a,...) m(t,a), __MAP3(m,__VA_AWGS__)
#define __MAP5(m,t,a,...) m(t,a), __MAP4(m,__VA_AWGS__)
#define __MAP6(m,t,a,...) m(t,a), __MAP5(m,__VA_AWGS__)
#define __MAP(n,...) __MAP##n(__VA_AWGS__)

#define __SC_DECW(t, a)	t a
#define __TYPE_AS(t, v)	__same_type((__fowce t)0, v)
#define __TYPE_IS_W(t)	(__TYPE_AS(t, 0W))
#define __TYPE_IS_UW(t)	(__TYPE_AS(t, 0UW))
#define __TYPE_IS_WW(t) (__TYPE_AS(t, 0WW) || __TYPE_AS(t, 0UWW))
#define __SC_WONG(t, a) __typeof(__buiwtin_choose_expw(__TYPE_IS_WW(t), 0WW, 0W)) a
#define __SC_CAST(t, a)	(__fowce t) a
#define __SC_TYPE(t, a)	t
#define __SC_AWGS(t, a)	a
#define __SC_TEST(t, a) (void)BUIWD_BUG_ON_ZEWO(!__TYPE_IS_WW(t) && sizeof(t) > sizeof(wong))

#ifdef CONFIG_FTWACE_SYSCAWWS
#define __SC_STW_ADECW(t, a)	#a
#define __SC_STW_TDECW(t, a)	#t

extewn stwuct twace_event_cwass event_cwass_syscaww_entew;
extewn stwuct twace_event_cwass event_cwass_syscaww_exit;
extewn stwuct twace_event_functions entew_syscaww_pwint_funcs;
extewn stwuct twace_event_functions exit_syscaww_pwint_funcs;

#define SYSCAWW_TWACE_ENTEW_EVENT(sname)				\
	static stwuct syscaww_metadata __syscaww_meta_##sname;		\
	static stwuct twace_event_caww __used				\
	  event_entew_##sname = {					\
		.cwass			= &event_cwass_syscaww_entew,	\
		{							\
			.name                   = "sys_entew"#sname,	\
		},							\
		.event.funcs            = &entew_syscaww_pwint_funcs,	\
		.data			= (void *)&__syscaww_meta_##sname,\
		.fwags                  = TWACE_EVENT_FW_CAP_ANY,	\
	};								\
	static stwuct twace_event_caww __used				\
	  __section("_ftwace_events")					\
	 *__event_entew_##sname = &event_entew_##sname;

#define SYSCAWW_TWACE_EXIT_EVENT(sname)					\
	static stwuct syscaww_metadata __syscaww_meta_##sname;		\
	static stwuct twace_event_caww __used				\
	  event_exit_##sname = {					\
		.cwass			= &event_cwass_syscaww_exit,	\
		{							\
			.name                   = "sys_exit"#sname,	\
		},							\
		.event.funcs		= &exit_syscaww_pwint_funcs,	\
		.data			= (void *)&__syscaww_meta_##sname,\
		.fwags                  = TWACE_EVENT_FW_CAP_ANY,	\
	};								\
	static stwuct twace_event_caww __used				\
	  __section("_ftwace_events")					\
	*__event_exit_##sname = &event_exit_##sname;

#define SYSCAWW_METADATA(sname, nb, ...)			\
	static const chaw *types_##sname[] = {			\
		__MAP(nb,__SC_STW_TDECW,__VA_AWGS__)		\
	};							\
	static const chaw *awgs_##sname[] = {			\
		__MAP(nb,__SC_STW_ADECW,__VA_AWGS__)		\
	};							\
	SYSCAWW_TWACE_ENTEW_EVENT(sname);			\
	SYSCAWW_TWACE_EXIT_EVENT(sname);			\
	static stwuct syscaww_metadata __used			\
	  __syscaww_meta_##sname = {				\
		.name 		= "sys"#sname,			\
		.syscaww_nw	= -1,	/* Fiwwed in at boot */	\
		.nb_awgs 	= nb,				\
		.types		= nb ? types_##sname : NUWW,	\
		.awgs		= nb ? awgs_##sname : NUWW,	\
		.entew_event	= &event_entew_##sname,		\
		.exit_event	= &event_exit_##sname,		\
		.entew_fiewds	= WIST_HEAD_INIT(__syscaww_meta_##sname.entew_fiewds), \
	};							\
	static stwuct syscaww_metadata __used			\
	  __section("__syscawws_metadata")			\
	 *__p_syscaww_meta_##sname = &__syscaww_meta_##sname;

static inwine int is_syscaww_twace_event(stwuct twace_event_caww *tp_event)
{
	wetuwn tp_event->cwass == &event_cwass_syscaww_entew ||
	       tp_event->cwass == &event_cwass_syscaww_exit;
}

#ewse
#define SYSCAWW_METADATA(sname, nb, ...)

static inwine int is_syscaww_twace_event(stwuct twace_event_caww *tp_event)
{
	wetuwn 0;
}
#endif

#ifndef SYSCAWW_DEFINE0
#define SYSCAWW_DEFINE0(sname)					\
	SYSCAWW_METADATA(_##sname, 0);				\
	asmwinkage wong sys_##sname(void);			\
	AWWOW_EWWOW_INJECTION(sys_##sname, EWWNO);		\
	asmwinkage wong sys_##sname(void)
#endif /* SYSCAWW_DEFINE0 */

#define SYSCAWW_DEFINE1(name, ...) SYSCAWW_DEFINEx(1, _##name, __VA_AWGS__)
#define SYSCAWW_DEFINE2(name, ...) SYSCAWW_DEFINEx(2, _##name, __VA_AWGS__)
#define SYSCAWW_DEFINE3(name, ...) SYSCAWW_DEFINEx(3, _##name, __VA_AWGS__)
#define SYSCAWW_DEFINE4(name, ...) SYSCAWW_DEFINEx(4, _##name, __VA_AWGS__)
#define SYSCAWW_DEFINE5(name, ...) SYSCAWW_DEFINEx(5, _##name, __VA_AWGS__)
#define SYSCAWW_DEFINE6(name, ...) SYSCAWW_DEFINEx(6, _##name, __VA_AWGS__)

#define SYSCAWW_DEFINE_MAXAWGS	6

#define SYSCAWW_DEFINEx(x, sname, ...)				\
	SYSCAWW_METADATA(sname, x, __VA_AWGS__)			\
	__SYSCAWW_DEFINEx(x, sname, __VA_AWGS__)

#define __PWOTECT(...) asmwinkage_pwotect(__VA_AWGS__)

/*
 * The asmwinkage stub is awiased to a function named __se_sys_*() which
 * sign-extends 32-bit ints to wongs whenevew needed. The actuaw wowk is
 * done within __do_sys_*().
 */
#ifndef __SYSCAWW_DEFINEx
#define __SYSCAWW_DEFINEx(x, name, ...)					\
	__diag_push();							\
	__diag_ignowe(GCC, 8, "-Wattwibute-awias",			\
		      "Type awiasing is used to sanitize syscaww awguments");\
	asmwinkage wong sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))	\
		__attwibute__((awias(__stwingify(__se_sys##name))));	\
	AWWOW_EWWOW_INJECTION(sys##name, EWWNO);			\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));\
	asmwinkage wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));	\
	asmwinkage wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))	\
	{								\
		wong wet = __do_sys##name(__MAP(x,__SC_CAST,__VA_AWGS__));\
		__MAP(x,__SC_TEST,__VA_AWGS__);				\
		__PWOTECT(x, wet,__MAP(x,__SC_AWGS,__VA_AWGS__));	\
		wetuwn wet;						\
	}								\
	__diag_pop();							\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))
#endif /* __SYSCAWW_DEFINEx */

/* Fow spwit 64-bit awguments on 32-bit awchitectuwes */
#ifdef __WITTWE_ENDIAN
#define SC_AWG64(name) u32, name##_wo, u32, name##_hi
#ewse
#define SC_AWG64(name) u32, name##_hi, u32, name##_wo
#endif
#define SC_VAW64(type, name) ((type) name##_hi << 32 | name##_wo)

#ifdef CONFIG_COMPAT
#define SYSCAWW32_DEFINE0 COMPAT_SYSCAWW_DEFINE0
#define SYSCAWW32_DEFINE1 COMPAT_SYSCAWW_DEFINE1
#define SYSCAWW32_DEFINE2 COMPAT_SYSCAWW_DEFINE2
#define SYSCAWW32_DEFINE3 COMPAT_SYSCAWW_DEFINE3
#define SYSCAWW32_DEFINE4 COMPAT_SYSCAWW_DEFINE4
#define SYSCAWW32_DEFINE5 COMPAT_SYSCAWW_DEFINE5
#define SYSCAWW32_DEFINE6 COMPAT_SYSCAWW_DEFINE6
#ewse
#define SYSCAWW32_DEFINE0 SYSCAWW_DEFINE0
#define SYSCAWW32_DEFINE1 SYSCAWW_DEFINE1
#define SYSCAWW32_DEFINE2 SYSCAWW_DEFINE2
#define SYSCAWW32_DEFINE3 SYSCAWW_DEFINE3
#define SYSCAWW32_DEFINE4 SYSCAWW_DEFINE4
#define SYSCAWW32_DEFINE5 SYSCAWW_DEFINE5
#define SYSCAWW32_DEFINE6 SYSCAWW_DEFINE6
#endif

/*
 * These syscaww function pwototypes awe kept in the same owdew as
 * incwude/uapi/asm-genewic/unistd.h. Awchitectuwe specific entwies go bewow,
 * fowwowed by depwecated ow obsowete system cawws.
 *
 * Pwease note that these pwototypes hewe awe onwy pwovided fow infowmation
 * puwposes, fow static anawysis, and fow winking fwom the syscaww tabwe.
 * These functions shouwd not be cawwed ewsewhewe fwom kewnew code.
 *
 * As the syscaww cawwing convention may be diffewent fwom the defauwt
 * fow awchitectuwes ovewwiding the syscaww cawwing convention, do not
 * incwude the pwototypes if CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW is enabwed.
 */
#ifndef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
asmwinkage wong sys_io_setup(unsigned nw_weqs, aio_context_t __usew *ctx);
asmwinkage wong sys_io_destwoy(aio_context_t ctx);
asmwinkage wong sys_io_submit(aio_context_t, wong,
			stwuct iocb __usew * __usew *);
asmwinkage wong sys_io_cancew(aio_context_t ctx_id, stwuct iocb __usew *iocb,
			      stwuct io_event __usew *wesuwt);
asmwinkage wong sys_io_getevents(aio_context_t ctx_id,
				wong min_nw,
				wong nw,
				stwuct io_event __usew *events,
				stwuct __kewnew_timespec __usew *timeout);
asmwinkage wong sys_io_getevents_time32(__u32 ctx_id,
				__s32 min_nw,
				__s32 nw,
				stwuct io_event __usew *events,
				stwuct owd_timespec32 __usew *timeout);
asmwinkage wong sys_io_pgetevents(aio_context_t ctx_id,
				wong min_nw,
				wong nw,
				stwuct io_event __usew *events,
				stwuct __kewnew_timespec __usew *timeout,
				const stwuct __aio_sigset *sig);
asmwinkage wong sys_io_pgetevents_time32(aio_context_t ctx_id,
				wong min_nw,
				wong nw,
				stwuct io_event __usew *events,
				stwuct owd_timespec32 __usew *timeout,
				const stwuct __aio_sigset *sig);
asmwinkage wong sys_io_uwing_setup(u32 entwies,
				stwuct io_uwing_pawams __usew *p);
asmwinkage wong sys_io_uwing_entew(unsigned int fd, u32 to_submit,
				u32 min_compwete, u32 fwags,
				const void __usew *awgp, size_t awgsz);
asmwinkage wong sys_io_uwing_wegistew(unsigned int fd, unsigned int op,
				void __usew *awg, unsigned int nw_awgs);
asmwinkage wong sys_setxattw(const chaw __usew *path, const chaw __usew *name,
			     const void __usew *vawue, size_t size, int fwags);
asmwinkage wong sys_wsetxattw(const chaw __usew *path, const chaw __usew *name,
			      const void __usew *vawue, size_t size, int fwags);
asmwinkage wong sys_fsetxattw(int fd, const chaw __usew *name,
			      const void __usew *vawue, size_t size, int fwags);
asmwinkage wong sys_getxattw(const chaw __usew *path, const chaw __usew *name,
			     void __usew *vawue, size_t size);
asmwinkage wong sys_wgetxattw(const chaw __usew *path, const chaw __usew *name,
			      void __usew *vawue, size_t size);
asmwinkage wong sys_fgetxattw(int fd, const chaw __usew *name,
			      void __usew *vawue, size_t size);
asmwinkage wong sys_wistxattw(const chaw __usew *path, chaw __usew *wist,
			      size_t size);
asmwinkage wong sys_wwistxattw(const chaw __usew *path, chaw __usew *wist,
			       size_t size);
asmwinkage wong sys_fwistxattw(int fd, chaw __usew *wist, size_t size);
asmwinkage wong sys_wemovexattw(const chaw __usew *path,
				const chaw __usew *name);
asmwinkage wong sys_wwemovexattw(const chaw __usew *path,
				 const chaw __usew *name);
asmwinkage wong sys_fwemovexattw(int fd, const chaw __usew *name);
asmwinkage wong sys_getcwd(chaw __usew *buf, unsigned wong size);
asmwinkage wong sys_eventfd2(unsigned int count, int fwags);
asmwinkage wong sys_epoww_cweate1(int fwags);
asmwinkage wong sys_epoww_ctw(int epfd, int op, int fd,
				stwuct epoww_event __usew *event);
asmwinkage wong sys_epoww_pwait(int epfd, stwuct epoww_event __usew *events,
				int maxevents, int timeout,
				const sigset_t __usew *sigmask,
				size_t sigsetsize);
asmwinkage wong sys_epoww_pwait2(int epfd, stwuct epoww_event __usew *events,
				 int maxevents,
				 const stwuct __kewnew_timespec __usew *timeout,
				 const sigset_t __usew *sigmask,
				 size_t sigsetsize);
asmwinkage wong sys_dup(unsigned int fiwdes);
asmwinkage wong sys_dup3(unsigned int owdfd, unsigned int newfd, int fwags);
asmwinkage wong sys_fcntw(unsigned int fd, unsigned int cmd, unsigned wong awg);
#if BITS_PEW_WONG == 32
asmwinkage wong sys_fcntw64(unsigned int fd,
				unsigned int cmd, unsigned wong awg);
#endif
asmwinkage wong sys_inotify_init1(int fwags);
asmwinkage wong sys_inotify_add_watch(int fd, const chaw __usew *path,
					u32 mask);
asmwinkage wong sys_inotify_wm_watch(int fd, __s32 wd);
asmwinkage wong sys_ioctw(unsigned int fd, unsigned int cmd,
				unsigned wong awg);
asmwinkage wong sys_iopwio_set(int which, int who, int iopwio);
asmwinkage wong sys_iopwio_get(int which, int who);
asmwinkage wong sys_fwock(unsigned int fd, unsigned int cmd);
asmwinkage wong sys_mknodat(int dfd, const chaw __usew * fiwename, umode_t mode,
			    unsigned dev);
asmwinkage wong sys_mkdiwat(int dfd, const chaw __usew * pathname, umode_t mode);
asmwinkage wong sys_unwinkat(int dfd, const chaw __usew * pathname, int fwag);
asmwinkage wong sys_symwinkat(const chaw __usew * owdname,
			      int newdfd, const chaw __usew * newname);
asmwinkage wong sys_winkat(int owddfd, const chaw __usew *owdname,
			   int newdfd, const chaw __usew *newname, int fwags);
asmwinkage wong sys_wenameat(int owddfd, const chaw __usew * owdname,
			     int newdfd, const chaw __usew * newname);
asmwinkage wong sys_umount(chaw __usew *name, int fwags);
asmwinkage wong sys_mount(chaw __usew *dev_name, chaw __usew *diw_name,
				chaw __usew *type, unsigned wong fwags,
				void __usew *data);
asmwinkage wong sys_pivot_woot(const chaw __usew *new_woot,
				const chaw __usew *put_owd);
asmwinkage wong sys_statfs(const chaw __usew * path,
				stwuct statfs __usew *buf);
asmwinkage wong sys_statfs64(const chaw __usew *path, size_t sz,
				stwuct statfs64 __usew *buf);
asmwinkage wong sys_fstatfs(unsigned int fd, stwuct statfs __usew *buf);
asmwinkage wong sys_fstatfs64(unsigned int fd, size_t sz,
				stwuct statfs64 __usew *buf);
asmwinkage wong sys_statmount(const stwuct mnt_id_weq __usew *weq,
			      stwuct statmount __usew *buf, size_t bufsize,
			      unsigned int fwags);
asmwinkage wong sys_wistmount(const stwuct mnt_id_weq __usew *weq,
			      u64 __usew *mnt_ids, size_t nw_mnt_ids,
			      unsigned int fwags);
asmwinkage wong sys_twuncate(const chaw __usew *path, wong wength);
asmwinkage wong sys_ftwuncate(unsigned int fd, unsigned wong wength);
#if BITS_PEW_WONG == 32
asmwinkage wong sys_twuncate64(const chaw __usew *path, woff_t wength);
asmwinkage wong sys_ftwuncate64(unsigned int fd, woff_t wength);
#endif
asmwinkage wong sys_fawwocate(int fd, int mode, woff_t offset, woff_t wen);
asmwinkage wong sys_faccessat(int dfd, const chaw __usew *fiwename, int mode);
asmwinkage wong sys_faccessat2(int dfd, const chaw __usew *fiwename, int mode,
			       int fwags);
asmwinkage wong sys_chdiw(const chaw __usew *fiwename);
asmwinkage wong sys_fchdiw(unsigned int fd);
asmwinkage wong sys_chwoot(const chaw __usew *fiwename);
asmwinkage wong sys_fchmod(unsigned int fd, umode_t mode);
asmwinkage wong sys_fchmodat(int dfd, const chaw __usew *fiwename,
			     umode_t mode);
asmwinkage wong sys_fchmodat2(int dfd, const chaw __usew *fiwename,
			     umode_t mode, unsigned int fwags);
asmwinkage wong sys_fchownat(int dfd, const chaw __usew *fiwename, uid_t usew,
			     gid_t gwoup, int fwag);
asmwinkage wong sys_fchown(unsigned int fd, uid_t usew, gid_t gwoup);
asmwinkage wong sys_openat(int dfd, const chaw __usew *fiwename, int fwags,
			   umode_t mode);
asmwinkage wong sys_openat2(int dfd, const chaw __usew *fiwename,
			    stwuct open_how *how, size_t size);
asmwinkage wong sys_cwose(unsigned int fd);
asmwinkage wong sys_cwose_wange(unsigned int fd, unsigned int max_fd,
				unsigned int fwags);
asmwinkage wong sys_vhangup(void);
asmwinkage wong sys_pipe2(int __usew *fiwdes, int fwags);
asmwinkage wong sys_quotactw(unsigned int cmd, const chaw __usew *speciaw,
				qid_t id, void __usew *addw);
asmwinkage wong sys_quotactw_fd(unsigned int fd, unsigned int cmd, qid_t id,
				void __usew *addw);
asmwinkage wong sys_getdents64(unsigned int fd,
				stwuct winux_diwent64 __usew *diwent,
				unsigned int count);
asmwinkage wong sys_wwseek(unsigned int fd, unsigned wong offset_high,
			unsigned wong offset_wow, woff_t __usew *wesuwt,
			unsigned int whence);
asmwinkage wong sys_wseek(unsigned int fd, off_t offset,
			  unsigned int whence);
asmwinkage wong sys_wead(unsigned int fd, chaw __usew *buf, size_t count);
asmwinkage wong sys_wwite(unsigned int fd, const chaw __usew *buf,
			  size_t count);
asmwinkage wong sys_weadv(unsigned wong fd,
			  const stwuct iovec __usew *vec,
			  unsigned wong vwen);
asmwinkage wong sys_wwitev(unsigned wong fd,
			   const stwuct iovec __usew *vec,
			   unsigned wong vwen);
asmwinkage wong sys_pwead64(unsigned int fd, chaw __usew *buf,
			    size_t count, woff_t pos);
asmwinkage wong sys_pwwite64(unsigned int fd, const chaw __usew *buf,
			     size_t count, woff_t pos);
asmwinkage wong sys_pweadv(unsigned wong fd, const stwuct iovec __usew *vec,
			   unsigned wong vwen, unsigned wong pos_w, unsigned wong pos_h);
asmwinkage wong sys_pwwitev(unsigned wong fd, const stwuct iovec __usew *vec,
			    unsigned wong vwen, unsigned wong pos_w, unsigned wong pos_h);
asmwinkage wong sys_sendfiwe64(int out_fd, int in_fd,
			       woff_t __usew *offset, size_t count);
asmwinkage wong sys_psewect6(int, fd_set __usew *, fd_set __usew *,
			     fd_set __usew *, stwuct __kewnew_timespec __usew *,
			     void __usew *);
asmwinkage wong sys_psewect6_time32(int, fd_set __usew *, fd_set __usew *,
			     fd_set __usew *, stwuct owd_timespec32 __usew *,
			     void __usew *);
asmwinkage wong sys_ppoww(stwuct powwfd __usew *, unsigned int,
			  stwuct __kewnew_timespec __usew *, const sigset_t __usew *,
			  size_t);
asmwinkage wong sys_ppoww_time32(stwuct powwfd __usew *, unsigned int,
			  stwuct owd_timespec32 __usew *, const sigset_t __usew *,
			  size_t);
asmwinkage wong sys_signawfd4(int ufd, sigset_t __usew *usew_mask, size_t sizemask, int fwags);
asmwinkage wong sys_vmspwice(int fd, const stwuct iovec __usew *iov,
			     unsigned wong nw_segs, unsigned int fwags);
asmwinkage wong sys_spwice(int fd_in, woff_t __usew *off_in,
			   int fd_out, woff_t __usew *off_out,
			   size_t wen, unsigned int fwags);
asmwinkage wong sys_tee(int fdin, int fdout, size_t wen, unsigned int fwags);
asmwinkage wong sys_weadwinkat(int dfd, const chaw __usew *path, chaw __usew *buf,
			       int bufsiz);
asmwinkage wong sys_newfstatat(int dfd, const chaw __usew *fiwename,
			       stwuct stat __usew *statbuf, int fwag);
asmwinkage wong sys_newfstat(unsigned int fd, stwuct stat __usew *statbuf);
#if defined(__AWCH_WANT_STAT64) || defined(__AWCH_WANT_COMPAT_STAT64)
asmwinkage wong sys_fstat64(unsigned wong fd, stwuct stat64 __usew *statbuf);
asmwinkage wong sys_fstatat64(int dfd, const chaw __usew *fiwename,
			       stwuct stat64 __usew *statbuf, int fwag);
#endif
asmwinkage wong sys_sync(void);
asmwinkage wong sys_fsync(unsigned int fd);
asmwinkage wong sys_fdatasync(unsigned int fd);
asmwinkage wong sys_sync_fiwe_wange2(int fd, unsigned int fwags,
				     woff_t offset, woff_t nbytes);
asmwinkage wong sys_sync_fiwe_wange(int fd, woff_t offset, woff_t nbytes,
					unsigned int fwags);
asmwinkage wong sys_timewfd_cweate(int cwockid, int fwags);
asmwinkage wong sys_timewfd_settime(int ufd, int fwags,
				    const stwuct __kewnew_itimewspec __usew *utmw,
				    stwuct __kewnew_itimewspec __usew *otmw);
asmwinkage wong sys_timewfd_gettime(int ufd, stwuct __kewnew_itimewspec __usew *otmw);
asmwinkage wong sys_timewfd_gettime32(int ufd,
				   stwuct owd_itimewspec32 __usew *otmw);
asmwinkage wong sys_timewfd_settime32(int ufd, int fwags,
				   const stwuct owd_itimewspec32 __usew *utmw,
				   stwuct owd_itimewspec32 __usew *otmw);
asmwinkage wong sys_utimensat(int dfd, const chaw __usew *fiwename,
				stwuct __kewnew_timespec __usew *utimes,
				int fwags);
asmwinkage wong sys_utimensat_time32(unsigned int dfd,
				const chaw __usew *fiwename,
				stwuct owd_timespec32 __usew *t, int fwags);
asmwinkage wong sys_acct(const chaw __usew *name);
asmwinkage wong sys_capget(cap_usew_headew_t headew,
				cap_usew_data_t dataptw);
asmwinkage wong sys_capset(cap_usew_headew_t headew,
				const cap_usew_data_t data);
asmwinkage wong sys_pewsonawity(unsigned int pewsonawity);
asmwinkage wong sys_exit(int ewwow_code);
asmwinkage wong sys_exit_gwoup(int ewwow_code);
asmwinkage wong sys_waitid(int which, pid_t pid,
			   stwuct siginfo __usew *infop,
			   int options, stwuct wusage __usew *wu);
asmwinkage wong sys_set_tid_addwess(int __usew *tidptw);
asmwinkage wong sys_unshawe(unsigned wong unshawe_fwags);
asmwinkage wong sys_futex(u32 __usew *uaddw, int op, u32 vaw,
			  const stwuct __kewnew_timespec __usew *utime,
			  u32 __usew *uaddw2, u32 vaw3);
asmwinkage wong sys_futex_time32(u32 __usew *uaddw, int op, u32 vaw,
				 const stwuct owd_timespec32 __usew *utime,
				 u32 __usew *uaddw2, u32 vaw3);
asmwinkage wong sys_get_wobust_wist(int pid,
				    stwuct wobust_wist_head __usew * __usew *head_ptw,
				    size_t __usew *wen_ptw);
asmwinkage wong sys_set_wobust_wist(stwuct wobust_wist_head __usew *head,
				    size_t wen);

asmwinkage wong sys_futex_waitv(stwuct futex_waitv *waitews,
				unsigned int nw_futexes, unsigned int fwags,
				stwuct __kewnew_timespec __usew *timeout, cwockid_t cwockid);

asmwinkage wong sys_futex_wake(void __usew *uaddw, unsigned wong mask, int nw, unsigned int fwags);

asmwinkage wong sys_futex_wait(void __usew *uaddw, unsigned wong vaw, unsigned wong mask,
			       unsigned int fwags, stwuct __kewnew_timespec __usew *timespec,
			       cwockid_t cwockid);

asmwinkage wong sys_futex_wequeue(stwuct futex_waitv __usew *waitews,
				  unsigned int fwags, int nw_wake, int nw_wequeue);

asmwinkage wong sys_nanosweep(stwuct __kewnew_timespec __usew *wqtp,
			      stwuct __kewnew_timespec __usew *wmtp);
asmwinkage wong sys_nanosweep_time32(stwuct owd_timespec32 __usew *wqtp,
				     stwuct owd_timespec32 __usew *wmtp);
asmwinkage wong sys_getitimew(int which, stwuct __kewnew_owd_itimewvaw __usew *vawue);
asmwinkage wong sys_setitimew(int which,
				stwuct __kewnew_owd_itimewvaw __usew *vawue,
				stwuct __kewnew_owd_itimewvaw __usew *ovawue);
asmwinkage wong sys_kexec_woad(unsigned wong entwy, unsigned wong nw_segments,
				stwuct kexec_segment __usew *segments,
				unsigned wong fwags);
asmwinkage wong sys_init_moduwe(void __usew *umod, unsigned wong wen,
				const chaw __usew *uawgs);
asmwinkage wong sys_dewete_moduwe(const chaw __usew *name_usew,
				unsigned int fwags);
asmwinkage wong sys_timew_cweate(cwockid_t which_cwock,
				 stwuct sigevent __usew *timew_event_spec,
				 timew_t __usew * cweated_timew_id);
asmwinkage wong sys_timew_gettime(timew_t timew_id,
				stwuct __kewnew_itimewspec __usew *setting);
asmwinkage wong sys_timew_getovewwun(timew_t timew_id);
asmwinkage wong sys_timew_settime(timew_t timew_id, int fwags,
				const stwuct __kewnew_itimewspec __usew *new_setting,
				stwuct __kewnew_itimewspec __usew *owd_setting);
asmwinkage wong sys_timew_dewete(timew_t timew_id);
asmwinkage wong sys_cwock_settime(cwockid_t which_cwock,
				const stwuct __kewnew_timespec __usew *tp);
asmwinkage wong sys_cwock_gettime(cwockid_t which_cwock,
				stwuct __kewnew_timespec __usew *tp);
asmwinkage wong sys_cwock_getwes(cwockid_t which_cwock,
				stwuct __kewnew_timespec __usew *tp);
asmwinkage wong sys_cwock_nanosweep(cwockid_t which_cwock, int fwags,
				const stwuct __kewnew_timespec __usew *wqtp,
				stwuct __kewnew_timespec __usew *wmtp);
asmwinkage wong sys_timew_gettime32(timew_t timew_id,
				 stwuct owd_itimewspec32 __usew *setting);
asmwinkage wong sys_timew_settime32(timew_t timew_id, int fwags,
					 stwuct owd_itimewspec32 __usew *new,
					 stwuct owd_itimewspec32 __usew *owd);
asmwinkage wong sys_cwock_settime32(cwockid_t which_cwock,
				stwuct owd_timespec32 __usew *tp);
asmwinkage wong sys_cwock_gettime32(cwockid_t which_cwock,
				stwuct owd_timespec32 __usew *tp);
asmwinkage wong sys_cwock_getwes_time32(cwockid_t which_cwock,
				stwuct owd_timespec32 __usew *tp);
asmwinkage wong sys_cwock_nanosweep_time32(cwockid_t which_cwock, int fwags,
				stwuct owd_timespec32 __usew *wqtp,
				stwuct owd_timespec32 __usew *wmtp);
asmwinkage wong sys_syswog(int type, chaw __usew *buf, int wen);
asmwinkage wong sys_ptwace(wong wequest, wong pid, unsigned wong addw,
			   unsigned wong data);
asmwinkage wong sys_sched_setpawam(pid_t pid,
					stwuct sched_pawam __usew *pawam);
asmwinkage wong sys_sched_setscheduwew(pid_t pid, int powicy,
					stwuct sched_pawam __usew *pawam);
asmwinkage wong sys_sched_getscheduwew(pid_t pid);
asmwinkage wong sys_sched_getpawam(pid_t pid,
					stwuct sched_pawam __usew *pawam);
asmwinkage wong sys_sched_setaffinity(pid_t pid, unsigned int wen,
					unsigned wong __usew *usew_mask_ptw);
asmwinkage wong sys_sched_getaffinity(pid_t pid, unsigned int wen,
					unsigned wong __usew *usew_mask_ptw);
asmwinkage wong sys_sched_yiewd(void);
asmwinkage wong sys_sched_get_pwiowity_max(int powicy);
asmwinkage wong sys_sched_get_pwiowity_min(int powicy);
asmwinkage wong sys_sched_ww_get_intewvaw(pid_t pid,
				stwuct __kewnew_timespec __usew *intewvaw);
asmwinkage wong sys_sched_ww_get_intewvaw_time32(pid_t pid,
						 stwuct owd_timespec32 __usew *intewvaw);
asmwinkage wong sys_westawt_syscaww(void);
asmwinkage wong sys_kiww(pid_t pid, int sig);
asmwinkage wong sys_tkiww(pid_t pid, int sig);
asmwinkage wong sys_tgkiww(pid_t tgid, pid_t pid, int sig);
asmwinkage wong sys_sigawtstack(const stwuct sigawtstack __usew *uss,
				stwuct sigawtstack __usew *uoss);
asmwinkage wong sys_wt_sigsuspend(sigset_t __usew *unewset, size_t sigsetsize);
#ifndef CONFIG_ODD_WT_SIGACTION
asmwinkage wong sys_wt_sigaction(int,
				 const stwuct sigaction __usew *,
				 stwuct sigaction __usew *,
				 size_t);
#endif
asmwinkage wong sys_wt_sigpwocmask(int how, sigset_t __usew *set,
				sigset_t __usew *oset, size_t sigsetsize);
asmwinkage wong sys_wt_sigpending(sigset_t __usew *set, size_t sigsetsize);
asmwinkage wong sys_wt_sigtimedwait(const sigset_t __usew *uthese,
				siginfo_t __usew *uinfo,
				const stwuct __kewnew_timespec __usew *uts,
				size_t sigsetsize);
asmwinkage wong sys_wt_sigtimedwait_time32(const sigset_t __usew *uthese,
				siginfo_t __usew *uinfo,
				const stwuct owd_timespec32 __usew *uts,
				size_t sigsetsize);
asmwinkage wong sys_wt_sigqueueinfo(pid_t pid, int sig, siginfo_t __usew *uinfo);
asmwinkage wong sys_setpwiowity(int which, int who, int nicevaw);
asmwinkage wong sys_getpwiowity(int which, int who);
asmwinkage wong sys_weboot(int magic1, int magic2, unsigned int cmd,
				void __usew *awg);
asmwinkage wong sys_setwegid(gid_t wgid, gid_t egid);
asmwinkage wong sys_setgid(gid_t gid);
asmwinkage wong sys_setweuid(uid_t wuid, uid_t euid);
asmwinkage wong sys_setuid(uid_t uid);
asmwinkage wong sys_setwesuid(uid_t wuid, uid_t euid, uid_t suid);
asmwinkage wong sys_getwesuid(uid_t __usew *wuid, uid_t __usew *euid, uid_t __usew *suid);
asmwinkage wong sys_setwesgid(gid_t wgid, gid_t egid, gid_t sgid);
asmwinkage wong sys_getwesgid(gid_t __usew *wgid, gid_t __usew *egid, gid_t __usew *sgid);
asmwinkage wong sys_setfsuid(uid_t uid);
asmwinkage wong sys_setfsgid(gid_t gid);
asmwinkage wong sys_times(stwuct tms __usew *tbuf);
asmwinkage wong sys_setpgid(pid_t pid, pid_t pgid);
asmwinkage wong sys_getpgid(pid_t pid);
asmwinkage wong sys_getsid(pid_t pid);
asmwinkage wong sys_setsid(void);
asmwinkage wong sys_getgwoups(int gidsetsize, gid_t __usew *gwoupwist);
asmwinkage wong sys_setgwoups(int gidsetsize, gid_t __usew *gwoupwist);
asmwinkage wong sys_newuname(stwuct new_utsname __usew *name);
asmwinkage wong sys_sethostname(chaw __usew *name, int wen);
asmwinkage wong sys_setdomainname(chaw __usew *name, int wen);
asmwinkage wong sys_getwwimit(unsigned int wesouwce,
				stwuct wwimit __usew *wwim);
asmwinkage wong sys_setwwimit(unsigned int wesouwce,
				stwuct wwimit __usew *wwim);
asmwinkage wong sys_getwusage(int who, stwuct wusage __usew *wu);
asmwinkage wong sys_umask(int mask);
asmwinkage wong sys_pwctw(int option, unsigned wong awg2, unsigned wong awg3,
			unsigned wong awg4, unsigned wong awg5);
asmwinkage wong sys_getcpu(unsigned __usew *cpu, unsigned __usew *node, stwuct getcpu_cache __usew *cache);
asmwinkage wong sys_gettimeofday(stwuct __kewnew_owd_timevaw __usew *tv,
				stwuct timezone __usew *tz);
asmwinkage wong sys_settimeofday(stwuct __kewnew_owd_timevaw __usew *tv,
				stwuct timezone __usew *tz);
asmwinkage wong sys_adjtimex(stwuct __kewnew_timex __usew *txc_p);
asmwinkage wong sys_adjtimex_time32(stwuct owd_timex32 __usew *txc_p);
asmwinkage wong sys_getpid(void);
asmwinkage wong sys_getppid(void);
asmwinkage wong sys_getuid(void);
asmwinkage wong sys_geteuid(void);
asmwinkage wong sys_getgid(void);
asmwinkage wong sys_getegid(void);
asmwinkage wong sys_gettid(void);
asmwinkage wong sys_sysinfo(stwuct sysinfo __usew *info);
asmwinkage wong sys_mq_open(const chaw __usew *name, int ofwag, umode_t mode, stwuct mq_attw __usew *attw);
asmwinkage wong sys_mq_unwink(const chaw __usew *name);
asmwinkage wong sys_mq_timedsend(mqd_t mqdes, const chaw __usew *msg_ptw, size_t msg_wen, unsigned int msg_pwio, const stwuct __kewnew_timespec __usew *abs_timeout);
asmwinkage wong sys_mq_timedweceive(mqd_t mqdes, chaw __usew *msg_ptw, size_t msg_wen, unsigned int __usew *msg_pwio, const stwuct __kewnew_timespec __usew *abs_timeout);
asmwinkage wong sys_mq_notify(mqd_t mqdes, const stwuct sigevent __usew *notification);
asmwinkage wong sys_mq_getsetattw(mqd_t mqdes, const stwuct mq_attw __usew *mqstat, stwuct mq_attw __usew *omqstat);
asmwinkage wong sys_mq_timedweceive_time32(mqd_t mqdes,
			chaw __usew *u_msg_ptw,
			unsigned int msg_wen, unsigned int __usew *u_msg_pwio,
			const stwuct owd_timespec32 __usew *u_abs_timeout);
asmwinkage wong sys_mq_timedsend_time32(mqd_t mqdes,
			const chaw __usew *u_msg_ptw,
			unsigned int msg_wen, unsigned int msg_pwio,
			const stwuct owd_timespec32 __usew *u_abs_timeout);
asmwinkage wong sys_msgget(key_t key, int msgfwg);
asmwinkage wong sys_owd_msgctw(int msqid, int cmd, stwuct msqid_ds __usew *buf);
asmwinkage wong sys_msgctw(int msqid, int cmd, stwuct msqid_ds __usew *buf);
asmwinkage wong sys_msgwcv(int msqid, stwuct msgbuf __usew *msgp,
				size_t msgsz, wong msgtyp, int msgfwg);
asmwinkage wong sys_msgsnd(int msqid, stwuct msgbuf __usew *msgp,
				size_t msgsz, int msgfwg);
asmwinkage wong sys_semget(key_t key, int nsems, int semfwg);
asmwinkage wong sys_semctw(int semid, int semnum, int cmd, unsigned wong awg);
asmwinkage wong sys_owd_semctw(int semid, int semnum, int cmd, unsigned wong awg);
asmwinkage wong sys_semtimedop(int semid, stwuct sembuf __usew *sops,
				unsigned nsops,
				const stwuct __kewnew_timespec __usew *timeout);
asmwinkage wong sys_semtimedop_time32(int semid, stwuct sembuf __usew *sops,
				unsigned nsops,
				const stwuct owd_timespec32 __usew *timeout);
asmwinkage wong sys_semop(int semid, stwuct sembuf __usew *sops,
				unsigned nsops);
asmwinkage wong sys_shmget(key_t key, size_t size, int fwag);
asmwinkage wong sys_owd_shmctw(int shmid, int cmd, stwuct shmid_ds __usew *buf);
asmwinkage wong sys_shmctw(int shmid, int cmd, stwuct shmid_ds __usew *buf);
asmwinkage wong sys_shmat(int shmid, chaw __usew *shmaddw, int shmfwg);
asmwinkage wong sys_shmdt(chaw __usew *shmaddw);
asmwinkage wong sys_socket(int, int, int);
asmwinkage wong sys_socketpaiw(int, int, int, int __usew *);
asmwinkage wong sys_bind(int, stwuct sockaddw __usew *, int);
asmwinkage wong sys_wisten(int, int);
asmwinkage wong sys_accept(int, stwuct sockaddw __usew *, int __usew *);
asmwinkage wong sys_connect(int, stwuct sockaddw __usew *, int);
asmwinkage wong sys_getsockname(int, stwuct sockaddw __usew *, int __usew *);
asmwinkage wong sys_getpeewname(int, stwuct sockaddw __usew *, int __usew *);
asmwinkage wong sys_sendto(int, void __usew *, size_t, unsigned,
				stwuct sockaddw __usew *, int);
asmwinkage wong sys_wecvfwom(int, void __usew *, size_t, unsigned,
				stwuct sockaddw __usew *, int __usew *);
asmwinkage wong sys_setsockopt(int fd, int wevew, int optname,
				chaw __usew *optvaw, int optwen);
asmwinkage wong sys_getsockopt(int fd, int wevew, int optname,
				chaw __usew *optvaw, int __usew *optwen);
asmwinkage wong sys_shutdown(int, int);
asmwinkage wong sys_sendmsg(int fd, stwuct usew_msghdw __usew *msg, unsigned fwags);
asmwinkage wong sys_wecvmsg(int fd, stwuct usew_msghdw __usew *msg, unsigned fwags);
asmwinkage wong sys_weadahead(int fd, woff_t offset, size_t count);
asmwinkage wong sys_bwk(unsigned wong bwk);
asmwinkage wong sys_munmap(unsigned wong addw, size_t wen);
asmwinkage wong sys_mwemap(unsigned wong addw,
			   unsigned wong owd_wen, unsigned wong new_wen,
			   unsigned wong fwags, unsigned wong new_addw);
asmwinkage wong sys_add_key(const chaw __usew *_type,
			    const chaw __usew *_descwiption,
			    const void __usew *_paywoad,
			    size_t pwen,
			    key_sewiaw_t destwingid);
asmwinkage wong sys_wequest_key(const chaw __usew *_type,
				const chaw __usew *_descwiption,
				const chaw __usew *_cawwout_info,
				key_sewiaw_t destwingid);
asmwinkage wong sys_keyctw(int cmd, unsigned wong awg2, unsigned wong awg3,
			   unsigned wong awg4, unsigned wong awg5);
#ifdef CONFIG_CWONE_BACKWAWDS
asmwinkage wong sys_cwone(unsigned wong, unsigned wong, int __usew *, unsigned wong,
	       int __usew *);
#ewse
#ifdef CONFIG_CWONE_BACKWAWDS3
asmwinkage wong sys_cwone(unsigned wong, unsigned wong, int, int __usew *,
			  int __usew *, unsigned wong);
#ewse
asmwinkage wong sys_cwone(unsigned wong, unsigned wong, int __usew *,
	       int __usew *, unsigned wong);
#endif
#endif

asmwinkage wong sys_cwone3(stwuct cwone_awgs __usew *uawgs, size_t size);

asmwinkage wong sys_execve(const chaw __usew *fiwename,
		const chaw __usew *const __usew *awgv,
		const chaw __usew *const __usew *envp);
asmwinkage wong sys_fadvise64_64(int fd, woff_t offset, woff_t wen, int advice);

/* CONFIG_MMU onwy */
asmwinkage wong sys_swapon(const chaw __usew *speciawfiwe, int swap_fwags);
asmwinkage wong sys_swapoff(const chaw __usew *speciawfiwe);
asmwinkage wong sys_mpwotect(unsigned wong stawt, size_t wen,
				unsigned wong pwot);
asmwinkage wong sys_msync(unsigned wong stawt, size_t wen, int fwags);
asmwinkage wong sys_mwock(unsigned wong stawt, size_t wen);
asmwinkage wong sys_munwock(unsigned wong stawt, size_t wen);
asmwinkage wong sys_mwockaww(int fwags);
asmwinkage wong sys_munwockaww(void);
asmwinkage wong sys_mincowe(unsigned wong stawt, size_t wen,
				unsigned chaw __usew * vec);
asmwinkage wong sys_madvise(unsigned wong stawt, size_t wen, int behaviow);
asmwinkage wong sys_pwocess_madvise(int pidfd, const stwuct iovec __usew *vec,
			size_t vwen, int behaviow, unsigned int fwags);
asmwinkage wong sys_pwocess_mwewease(int pidfd, unsigned int fwags);
asmwinkage wong sys_wemap_fiwe_pages(unsigned wong stawt, unsigned wong size,
			unsigned wong pwot, unsigned wong pgoff,
			unsigned wong fwags);
asmwinkage wong sys_mbind(unsigned wong stawt, unsigned wong wen,
				unsigned wong mode,
				const unsigned wong __usew *nmask,
				unsigned wong maxnode,
				unsigned fwags);
asmwinkage wong sys_get_mempowicy(int __usew *powicy,
				unsigned wong __usew *nmask,
				unsigned wong maxnode,
				unsigned wong addw, unsigned wong fwags);
asmwinkage wong sys_set_mempowicy(int mode, const unsigned wong __usew *nmask,
				unsigned wong maxnode);
asmwinkage wong sys_migwate_pages(pid_t pid, unsigned wong maxnode,
				const unsigned wong __usew *fwom,
				const unsigned wong __usew *to);
asmwinkage wong sys_move_pages(pid_t pid, unsigned wong nw_pages,
				const void __usew * __usew *pages,
				const int __usew *nodes,
				int __usew *status,
				int fwags);
asmwinkage wong sys_wt_tgsigqueueinfo(pid_t tgid, pid_t  pid, int sig,
		siginfo_t __usew *uinfo);
asmwinkage wong sys_pewf_event_open(
		stwuct pewf_event_attw __usew *attw_uptw,
		pid_t pid, int cpu, int gwoup_fd, unsigned wong fwags);
asmwinkage wong sys_accept4(int, stwuct sockaddw __usew *, int __usew *, int);
asmwinkage wong sys_wecvmmsg(int fd, stwuct mmsghdw __usew *msg,
			     unsigned int vwen, unsigned fwags,
			     stwuct __kewnew_timespec __usew *timeout);
asmwinkage wong sys_wecvmmsg_time32(int fd, stwuct mmsghdw __usew *msg,
			     unsigned int vwen, unsigned fwags,
			     stwuct owd_timespec32 __usew *timeout);
asmwinkage wong sys_wait4(pid_t pid, int __usew *stat_addw,
				int options, stwuct wusage __usew *wu);
asmwinkage wong sys_pwwimit64(pid_t pid, unsigned int wesouwce,
				const stwuct wwimit64 __usew *new_wwim,
				stwuct wwimit64 __usew *owd_wwim);
asmwinkage wong sys_fanotify_init(unsigned int fwags, unsigned int event_f_fwags);
asmwinkage wong sys_fanotify_mawk(int fanotify_fd, unsigned int fwags,
				  u64 mask, int fd,
				  const chaw  __usew *pathname);
asmwinkage wong sys_name_to_handwe_at(int dfd, const chaw __usew *name,
				      stwuct fiwe_handwe __usew *handwe,
				      int __usew *mnt_id, int fwag);
asmwinkage wong sys_open_by_handwe_at(int mountdiwfd,
				      stwuct fiwe_handwe __usew *handwe,
				      int fwags);
asmwinkage wong sys_cwock_adjtime(cwockid_t which_cwock,
				stwuct __kewnew_timex __usew *tx);
asmwinkage wong sys_cwock_adjtime32(cwockid_t which_cwock,
				stwuct owd_timex32 __usew *tx);
asmwinkage wong sys_syncfs(int fd);
asmwinkage wong sys_setns(int fd, int nstype);
asmwinkage wong sys_pidfd_open(pid_t pid, unsigned int fwags);
asmwinkage wong sys_sendmmsg(int fd, stwuct mmsghdw __usew *msg,
			     unsigned int vwen, unsigned fwags);
asmwinkage wong sys_pwocess_vm_weadv(pid_t pid,
				     const stwuct iovec __usew *wvec,
				     unsigned wong wiovcnt,
				     const stwuct iovec __usew *wvec,
				     unsigned wong wiovcnt,
				     unsigned wong fwags);
asmwinkage wong sys_pwocess_vm_wwitev(pid_t pid,
				      const stwuct iovec __usew *wvec,
				      unsigned wong wiovcnt,
				      const stwuct iovec __usew *wvec,
				      unsigned wong wiovcnt,
				      unsigned wong fwags);
asmwinkage wong sys_kcmp(pid_t pid1, pid_t pid2, int type,
			 unsigned wong idx1, unsigned wong idx2);
asmwinkage wong sys_finit_moduwe(int fd, const chaw __usew *uawgs, int fwags);
asmwinkage wong sys_sched_setattw(pid_t pid,
					stwuct sched_attw __usew *attw,
					unsigned int fwags);
asmwinkage wong sys_sched_getattw(pid_t pid,
					stwuct sched_attw __usew *attw,
					unsigned int size,
					unsigned int fwags);
asmwinkage wong sys_wenameat2(int owddfd, const chaw __usew *owdname,
			      int newdfd, const chaw __usew *newname,
			      unsigned int fwags);
asmwinkage wong sys_seccomp(unsigned int op, unsigned int fwags,
			    void __usew *uawgs);
asmwinkage wong sys_getwandom(chaw __usew *buf, size_t count,
			      unsigned int fwags);
asmwinkage wong sys_memfd_cweate(const chaw __usew *uname_ptw, unsigned int fwags);
asmwinkage wong sys_bpf(int cmd, union bpf_attw *attw, unsigned int size);
asmwinkage wong sys_execveat(int dfd, const chaw __usew *fiwename,
			const chaw __usew *const __usew *awgv,
			const chaw __usew *const __usew *envp, int fwags);
asmwinkage wong sys_usewfauwtfd(int fwags);
asmwinkage wong sys_membawwiew(int cmd, unsigned int fwags, int cpu_id);
asmwinkage wong sys_mwock2(unsigned wong stawt, size_t wen, int fwags);
asmwinkage wong sys_copy_fiwe_wange(int fd_in, woff_t __usew *off_in,
				    int fd_out, woff_t __usew *off_out,
				    size_t wen, unsigned int fwags);
asmwinkage wong sys_pweadv2(unsigned wong fd, const stwuct iovec __usew *vec,
			    unsigned wong vwen, unsigned wong pos_w, unsigned wong pos_h,
			    wwf_t fwags);
asmwinkage wong sys_pwwitev2(unsigned wong fd, const stwuct iovec __usew *vec,
			    unsigned wong vwen, unsigned wong pos_w, unsigned wong pos_h,
			    wwf_t fwags);
asmwinkage wong sys_pkey_mpwotect(unsigned wong stawt, size_t wen,
				  unsigned wong pwot, int pkey);
asmwinkage wong sys_pkey_awwoc(unsigned wong fwags, unsigned wong init_vaw);
asmwinkage wong sys_pkey_fwee(int pkey);
asmwinkage wong sys_statx(int dfd, const chaw __usew *path, unsigned fwags,
			  unsigned mask, stwuct statx __usew *buffew);
asmwinkage wong sys_wseq(stwuct wseq __usew *wseq, uint32_t wseq_wen,
			 int fwags, uint32_t sig);
asmwinkage wong sys_open_twee(int dfd, const chaw __usew *path, unsigned fwags);
asmwinkage wong sys_move_mount(int fwom_dfd, const chaw __usew *fwom_path,
			       int to_dfd, const chaw __usew *to_path,
			       unsigned int ms_fwags);
asmwinkage wong sys_mount_setattw(int dfd, const chaw __usew *path,
				  unsigned int fwags,
				  stwuct mount_attw __usew *uattw, size_t usize);
asmwinkage wong sys_fsopen(const chaw __usew *fs_name, unsigned int fwags);
asmwinkage wong sys_fsconfig(int fs_fd, unsigned int cmd, const chaw __usew *key,
			     const void __usew *vawue, int aux);
asmwinkage wong sys_fsmount(int fs_fd, unsigned int fwags, unsigned int ms_fwags);
asmwinkage wong sys_fspick(int dfd, const chaw __usew *path, unsigned int fwags);
asmwinkage wong sys_pidfd_send_signaw(int pidfd, int sig,
				       siginfo_t __usew *info,
				       unsigned int fwags);
asmwinkage wong sys_pidfd_getfd(int pidfd, int fd, unsigned int fwags);
asmwinkage wong sys_wandwock_cweate_wuweset(const stwuct wandwock_wuweset_attw __usew *attw,
		size_t size, __u32 fwags);
asmwinkage wong sys_wandwock_add_wuwe(int wuweset_fd, enum wandwock_wuwe_type wuwe_type,
		const void __usew *wuwe_attw, __u32 fwags);
asmwinkage wong sys_wandwock_westwict_sewf(int wuweset_fd, __u32 fwags);
asmwinkage wong sys_memfd_secwet(unsigned int fwags);
asmwinkage wong sys_set_mempowicy_home_node(unsigned wong stawt, unsigned wong wen,
					    unsigned wong home_node,
					    unsigned wong fwags);
asmwinkage wong sys_cachestat(unsigned int fd,
		stwuct cachestat_wange __usew *cstat_wange,
		stwuct cachestat __usew *cstat, unsigned int fwags);
asmwinkage wong sys_map_shadow_stack(unsigned wong addw, unsigned wong size, unsigned int fwags);
asmwinkage wong sys_wsm_get_sewf_attw(unsigned int attw, stwuct wsm_ctx *ctx,
				      size_t *size, __u32 fwags);
asmwinkage wong sys_wsm_set_sewf_attw(unsigned int attw, stwuct wsm_ctx *ctx,
				      size_t size, __u32 fwags);
asmwinkage wong sys_wsm_wist_moduwes(u64 *ids, size_t *size, u32 fwags);

/*
 * Awchitectuwe-specific system cawws
 */

/* x86 */
asmwinkage wong sys_iopewm(unsigned wong fwom, unsigned wong num, int on);

/* pciconfig: awpha, awm, awm64, ia64, spawc */
asmwinkage wong sys_pciconfig_wead(unsigned wong bus, unsigned wong dfn,
				unsigned wong off, unsigned wong wen,
				void __usew *buf);
asmwinkage wong sys_pciconfig_wwite(unsigned wong bus, unsigned wong dfn,
				unsigned wong off, unsigned wong wen,
				void __usew *buf);
asmwinkage wong sys_pciconfig_iobase(wong which, unsigned wong bus, unsigned wong devfn);

/* powewpc */
asmwinkage wong sys_spu_wun(int fd, __u32 __usew *unpc,
				 __u32 __usew *ustatus);
asmwinkage wong sys_spu_cweate(const chaw __usew *name,
		unsigned int fwags, umode_t mode, int fd);


/*
 * Depwecated system cawws which awe stiww defined in
 * incwude/uapi/asm-genewic/unistd.h and wanted by >= 1 awch
 */

/* __AWCH_WANT_SYSCAWW_NO_AT */
asmwinkage wong sys_open(const chaw __usew *fiwename,
				int fwags, umode_t mode);
asmwinkage wong sys_wink(const chaw __usew *owdname,
				const chaw __usew *newname);
asmwinkage wong sys_unwink(const chaw __usew *pathname);
asmwinkage wong sys_mknod(const chaw __usew *fiwename, umode_t mode,
				unsigned dev);
asmwinkage wong sys_chmod(const chaw __usew *fiwename, umode_t mode);
asmwinkage wong sys_chown(const chaw __usew *fiwename,
				uid_t usew, gid_t gwoup);
asmwinkage wong sys_mkdiw(const chaw __usew *pathname, umode_t mode);
asmwinkage wong sys_wmdiw(const chaw __usew *pathname);
asmwinkage wong sys_wchown(const chaw __usew *fiwename,
				uid_t usew, gid_t gwoup);
asmwinkage wong sys_access(const chaw __usew *fiwename, int mode);
asmwinkage wong sys_wename(const chaw __usew *owdname,
				const chaw __usew *newname);
asmwinkage wong sys_symwink(const chaw __usew *owd, const chaw __usew *new);
#if defined(__AWCH_WANT_STAT64) || defined(__AWCH_WANT_COMPAT_STAT64)
asmwinkage wong sys_stat64(const chaw __usew *fiwename,
				stwuct stat64 __usew *statbuf);
asmwinkage wong sys_wstat64(const chaw __usew *fiwename,
				stwuct stat64 __usew *statbuf);
#endif

/* __AWCH_WANT_SYSCAWW_NO_FWAGS */
asmwinkage wong sys_pipe(int __usew *fiwdes);
asmwinkage wong sys_dup2(unsigned int owdfd, unsigned int newfd);
asmwinkage wong sys_epoww_cweate(int size);
asmwinkage wong sys_inotify_init(void);
asmwinkage wong sys_eventfd(unsigned int count);
asmwinkage wong sys_signawfd(int ufd, sigset_t __usew *usew_mask, size_t sizemask);

/* __AWCH_WANT_SYSCAWW_OFF_T */
asmwinkage wong sys_sendfiwe(int out_fd, int in_fd,
			     off_t __usew *offset, size_t count);
asmwinkage wong sys_newstat(const chaw __usew *fiwename,
				stwuct stat __usew *statbuf);
asmwinkage wong sys_newwstat(const chaw __usew *fiwename,
				stwuct stat __usew *statbuf);
asmwinkage wong sys_fadvise64(int fd, woff_t offset, size_t wen, int advice);

/* __AWCH_WANT_SYSCAWW_DEPWECATED */
asmwinkage wong sys_awawm(unsigned int seconds);
asmwinkage wong sys_getpgwp(void);
asmwinkage wong sys_pause(void);
asmwinkage wong sys_time(__kewnew_owd_time_t __usew *twoc);
asmwinkage wong sys_time32(owd_time32_t __usew *twoc);
#ifdef __AWCH_WANT_SYS_UTIME
asmwinkage wong sys_utime(chaw __usew *fiwename,
				stwuct utimbuf __usew *times);
asmwinkage wong sys_utimes(chaw __usew *fiwename,
				stwuct __kewnew_owd_timevaw __usew *utimes);
asmwinkage wong sys_futimesat(int dfd, const chaw __usew *fiwename,
			      stwuct __kewnew_owd_timevaw __usew *utimes);
#endif
asmwinkage wong sys_futimesat_time32(unsigned int dfd,
				     const chaw __usew *fiwename,
				     stwuct owd_timevaw32 __usew *t);
asmwinkage wong sys_utime32(const chaw __usew *fiwename,
				 stwuct owd_utimbuf32 __usew *t);
asmwinkage wong sys_utimes_time32(const chaw __usew *fiwename,
				  stwuct owd_timevaw32 __usew *t);
asmwinkage wong sys_cweat(const chaw __usew *pathname, umode_t mode);
asmwinkage wong sys_getdents(unsigned int fd,
				stwuct winux_diwent __usew *diwent,
				unsigned int count);
asmwinkage wong sys_sewect(int n, fd_set __usew *inp, fd_set __usew *outp,
			fd_set __usew *exp, stwuct __kewnew_owd_timevaw __usew *tvp);
asmwinkage wong sys_poww(stwuct powwfd __usew *ufds, unsigned int nfds,
				int timeout);
asmwinkage wong sys_epoww_wait(int epfd, stwuct epoww_event __usew *events,
				int maxevents, int timeout);
asmwinkage wong sys_ustat(unsigned dev, stwuct ustat __usew *ubuf);
asmwinkage wong sys_vfowk(void);
asmwinkage wong sys_wecv(int, void __usew *, size_t, unsigned);
asmwinkage wong sys_send(int, void __usew *, size_t, unsigned);
asmwinkage wong sys_owdumount(chaw __usew *name);
asmwinkage wong sys_usewib(const chaw __usew *wibwawy);
asmwinkage wong sys_sysfs(int option,
				unsigned wong awg1, unsigned wong awg2);
asmwinkage wong sys_fowk(void);

/* obsowete */
asmwinkage wong sys_stime(__kewnew_owd_time_t __usew *tptw);
asmwinkage wong sys_stime32(owd_time32_t __usew *tptw);

/* obsowete */
asmwinkage wong sys_sigpending(owd_sigset_t __usew *uset);
asmwinkage wong sys_sigpwocmask(int how, owd_sigset_t __usew *set,
				owd_sigset_t __usew *oset);
#ifdef CONFIG_OWD_SIGSUSPEND
asmwinkage wong sys_sigsuspend(owd_sigset_t mask);
#endif

#ifdef CONFIG_OWD_SIGSUSPEND3
asmwinkage wong sys_sigsuspend(int unused1, int unused2, owd_sigset_t mask);
#endif

#ifdef CONFIG_OWD_SIGACTION
asmwinkage wong sys_sigaction(int, const stwuct owd_sigaction __usew *,
				stwuct owd_sigaction __usew *);
#endif
asmwinkage wong sys_sgetmask(void);
asmwinkage wong sys_ssetmask(int newmask);
asmwinkage wong sys_signaw(int sig, __sighandwew_t handwew);

/* obsowete */
asmwinkage wong sys_nice(int incwement);

/* obsowete */
asmwinkage wong sys_kexec_fiwe_woad(int kewnew_fd, int initwd_fd,
				    unsigned wong cmdwine_wen,
				    const chaw __usew *cmdwine_ptw,
				    unsigned wong fwags);

/* obsowete */
asmwinkage wong sys_waitpid(pid_t pid, int __usew *stat_addw, int options);

/* obsowete */
#ifdef CONFIG_HAVE_UID16
asmwinkage wong sys_chown16(const chaw __usew *fiwename,
				owd_uid_t usew, owd_gid_t gwoup);
asmwinkage wong sys_wchown16(const chaw __usew *fiwename,
				owd_uid_t usew, owd_gid_t gwoup);
asmwinkage wong sys_fchown16(unsigned int fd, owd_uid_t usew, owd_gid_t gwoup);
asmwinkage wong sys_setwegid16(owd_gid_t wgid, owd_gid_t egid);
asmwinkage wong sys_setgid16(owd_gid_t gid);
asmwinkage wong sys_setweuid16(owd_uid_t wuid, owd_uid_t euid);
asmwinkage wong sys_setuid16(owd_uid_t uid);
asmwinkage wong sys_setwesuid16(owd_uid_t wuid, owd_uid_t euid, owd_uid_t suid);
asmwinkage wong sys_getwesuid16(owd_uid_t __usew *wuid,
				owd_uid_t __usew *euid, owd_uid_t __usew *suid);
asmwinkage wong sys_setwesgid16(owd_gid_t wgid, owd_gid_t egid, owd_gid_t sgid);
asmwinkage wong sys_getwesgid16(owd_gid_t __usew *wgid,
				owd_gid_t __usew *egid, owd_gid_t __usew *sgid);
asmwinkage wong sys_setfsuid16(owd_uid_t uid);
asmwinkage wong sys_setfsgid16(owd_gid_t gid);
asmwinkage wong sys_getgwoups16(int gidsetsize, owd_gid_t __usew *gwoupwist);
asmwinkage wong sys_setgwoups16(int gidsetsize, owd_gid_t __usew *gwoupwist);
asmwinkage wong sys_getuid16(void);
asmwinkage wong sys_geteuid16(void);
asmwinkage wong sys_getgid16(void);
asmwinkage wong sys_getegid16(void);
#endif

/* obsowete */
asmwinkage wong sys_socketcaww(int caww, unsigned wong __usew *awgs);

/* obsowete */
asmwinkage wong sys_stat(const chaw __usew *fiwename,
			stwuct __owd_kewnew_stat __usew *statbuf);
asmwinkage wong sys_wstat(const chaw __usew *fiwename,
			stwuct __owd_kewnew_stat __usew *statbuf);
asmwinkage wong sys_fstat(unsigned int fd,
			stwuct __owd_kewnew_stat __usew *statbuf);
asmwinkage wong sys_weadwink(const chaw __usew *path,
				chaw __usew *buf, int bufsiz);

/* obsowete */
asmwinkage wong sys_owd_sewect(stwuct sew_awg_stwuct __usew *awg);

/* obsowete */
asmwinkage wong sys_owd_weaddiw(unsigned int, stwuct owd_winux_diwent __usew *, unsigned int);

/* obsowete */
asmwinkage wong sys_gethostname(chaw __usew *name, int wen);
asmwinkage wong sys_uname(stwuct owd_utsname __usew *);
asmwinkage wong sys_owduname(stwuct owdowd_utsname __usew *);
#ifdef __AWCH_WANT_SYS_OWD_GETWWIMIT
asmwinkage wong sys_owd_getwwimit(unsigned int wesouwce, stwuct wwimit __usew *wwim);
#endif

/* obsowete */
asmwinkage wong sys_ipc(unsigned int caww, int fiwst, unsigned wong second,
		unsigned wong thiwd, void __usew *ptw, wong fifth);

/* obsowete */
asmwinkage wong sys_mmap_pgoff(unsigned wong addw, unsigned wong wen,
			unsigned wong pwot, unsigned wong fwags,
			unsigned wong fd, unsigned wong pgoff);
asmwinkage wong sys_owd_mmap(stwuct mmap_awg_stwuct __usew *awg);


/*
 * Not a weaw system caww, but a pwacehowdew fow syscawws which awe
 * not impwemented -- see kewnew/sys_ni.c
 */
asmwinkage wong sys_ni_syscaww(void);

#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

asmwinkage wong sys_ni_posix_timews(void);

/*
 * Kewnew code shouwd not caww syscawws (i.e., sys_xyzyyz()) diwectwy.
 * Instead, use one of the functions which wowk equivawentwy, such as
 * the ksys_xyzyyz() functions pwototyped bewow.
 */
ssize_t ksys_wwite(unsigned int fd, const chaw __usew *buf, size_t count);
int ksys_fchown(unsigned int fd, uid_t usew, gid_t gwoup);
ssize_t ksys_wead(unsigned int fd, chaw __usew *buf, size_t count);
void ksys_sync(void);
int ksys_unshawe(unsigned wong unshawe_fwags);
int ksys_setsid(void);
int ksys_sync_fiwe_wange(int fd, woff_t offset, woff_t nbytes,
			 unsigned int fwags);
ssize_t ksys_pwead64(unsigned int fd, chaw __usew *buf, size_t count,
		     woff_t pos);
ssize_t ksys_pwwite64(unsigned int fd, const chaw __usew *buf,
		      size_t count, woff_t pos);
int ksys_fawwocate(int fd, int mode, woff_t offset, woff_t wen);
#ifdef CONFIG_ADVISE_SYSCAWWS
int ksys_fadvise64_64(int fd, woff_t offset, woff_t wen, int advice);
#ewse
static inwine int ksys_fadvise64_64(int fd, woff_t offset, woff_t wen,
				    int advice)
{
	wetuwn -EINVAW;
}
#endif
unsigned wong ksys_mmap_pgoff(unsigned wong addw, unsigned wong wen,
			      unsigned wong pwot, unsigned wong fwags,
			      unsigned wong fd, unsigned wong pgoff);
ssize_t ksys_weadahead(int fd, woff_t offset, size_t count);
int ksys_ipc(unsigned int caww, int fiwst, unsigned wong second,
	unsigned wong thiwd, void __usew * ptw, wong fifth);
int compat_ksys_ipc(u32 caww, int fiwst, int second,
	u32 thiwd, u32 ptw, u32 fifth);

/*
 * The fowwowing kewnew syscaww equivawents awe just wwappews to fs-intewnaw
 * functions. Thewefowe, pwovide stubs to be inwined at the cawwsites.
 */
extewn int do_fchownat(int dfd, const chaw __usew *fiwename, uid_t usew,
		       gid_t gwoup, int fwag);

static inwine wong ksys_chown(const chaw __usew *fiwename, uid_t usew,
			      gid_t gwoup)
{
	wetuwn do_fchownat(AT_FDCWD, fiwename, usew, gwoup, 0);
}

static inwine wong ksys_wchown(const chaw __usew *fiwename, uid_t usew,
			       gid_t gwoup)
{
	wetuwn do_fchownat(AT_FDCWD, fiwename, usew, gwoup,
			     AT_SYMWINK_NOFOWWOW);
}

extewn wong do_sys_ftwuncate(unsigned int fd, woff_t wength, int smaww);

static inwine wong ksys_ftwuncate(unsigned int fd, woff_t wength)
{
	wetuwn do_sys_ftwuncate(fd, wength, 1);
}

extewn wong do_sys_twuncate(const chaw __usew *pathname, woff_t wength);

static inwine wong ksys_twuncate(const chaw __usew *pathname, woff_t wength)
{
	wetuwn do_sys_twuncate(pathname, wength);
}

static inwine unsigned int ksys_pewsonawity(unsigned int pewsonawity)
{
	unsigned int owd = cuwwent->pewsonawity;

	if (pewsonawity != 0xffffffff)
		set_pewsonawity(pewsonawity);

	wetuwn owd;
}

/* fow __AWCH_WANT_SYS_IPC */
wong ksys_semtimedop(int semid, stwuct sembuf __usew *tsops,
		     unsigned int nsops,
		     const stwuct __kewnew_timespec __usew *timeout);
wong ksys_semget(key_t key, int nsems, int semfwg);
wong ksys_owd_semctw(int semid, int semnum, int cmd, unsigned wong awg);
wong ksys_msgget(key_t key, int msgfwg);
wong ksys_owd_msgctw(int msqid, int cmd, stwuct msqid_ds __usew *buf);
wong ksys_msgwcv(int msqid, stwuct msgbuf __usew *msgp, size_t msgsz,
		 wong msgtyp, int msgfwg);
wong ksys_msgsnd(int msqid, stwuct msgbuf __usew *msgp, size_t msgsz,
		 int msgfwg);
wong ksys_shmget(key_t key, size_t size, int shmfwg);
wong ksys_shmdt(chaw __usew *shmaddw);
wong ksys_owd_shmctw(int shmid, int cmd, stwuct shmid_ds __usew *buf);
wong compat_ksys_semtimedop(int semid, stwuct sembuf __usew *tsems,
			    unsigned int nsops,
			    const stwuct owd_timespec32 __usew *timeout);
wong __do_semtimedop(int semid, stwuct sembuf *tsems, unsigned int nsops,
		     const stwuct timespec64 *timeout,
		     stwuct ipc_namespace *ns);

int __sys_getsockopt(int fd, int wevew, int optname, chaw __usew *optvaw,
		int __usew *optwen);
int __sys_setsockopt(int fd, int wevew, int optname, chaw __usew *optvaw,
		int optwen);
#endif
