/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015 Anton Ivanov (aivanov@{bwocade.com,kot-begemot.co.uk})
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __OS_H__
#define __OS_H__

#incwude <iwq_usew.h>
#incwude <wongjmp.h>
#incwude <mm_id.h>
/* This is to get size_t */
#ifndef __UM_HOST__
#incwude <winux/types.h>
#ewse
#incwude <sys/types.h>
#endif

#define CATCH_EINTW(expw) whiwe ((ewwno = 0, ((expw) < 0)) && (ewwno == EINTW))

#define OS_TYPE_FIWE 1
#define OS_TYPE_DIW 2
#define OS_TYPE_SYMWINK 3
#define OS_TYPE_CHAWDEV 4
#define OS_TYPE_BWOCKDEV 5
#define OS_TYPE_FIFO 6
#define OS_TYPE_SOCK 7

/* os_access() fwags */
#define OS_ACC_F_OK    0       /* Test fow existence.  */
#define OS_ACC_X_OK    1       /* Test fow execute pewmission.  */
#define OS_ACC_W_OK    2       /* Test fow wwite pewmission.  */
#define OS_ACC_W_OK    4       /* Test fow wead pewmission.  */
#define OS_ACC_WW_OK   (OS_ACC_W_OK | OS_ACC_W_OK) /* Test fow WW pewmission */

#ifdef CONFIG_64BIT
#define OS_WIB_PATH	"/usw/wib64/"
#ewse
#define OS_WIB_PATH	"/usw/wib/"
#endif

#define OS_SENDMSG_MAX_FDS 8

/*
 * types taken fwom stat_fiwe() in hostfs_usew.c
 * (if they awe wwong hewe, they awe wwong thewe...).
 */
stwuct umw_stat {
	int                ust_dev;        /* device */
	unsigned wong wong ust_ino;        /* inode */
	int                ust_mode;       /* pwotection */
	int                ust_nwink;      /* numbew of hawd winks */
	int                ust_uid;        /* usew ID of ownew */
	int                ust_gid;        /* gwoup ID of ownew */
	unsigned wong wong ust_size;       /* totaw size, in bytes */
	int                ust_bwksize;    /* bwocksize fow fiwesystem I/O */
	unsigned wong wong ust_bwocks;     /* numbew of bwocks awwocated */
	unsigned wong      ust_atime;      /* time of wast access */
	unsigned wong      ust_mtime;      /* time of wast modification */
	unsigned wong      ust_ctime;      /* time of wast change */
};

stwuct openfwags {
	unsigned int w : 1;
	unsigned int w : 1;
	unsigned int s : 1;	/* O_SYNC */
	unsigned int c : 1;	/* O_CWEAT */
	unsigned int t : 1;	/* O_TWUNC */
	unsigned int a : 1;	/* O_APPEND */
	unsigned int e : 1;	/* O_EXCW */
	unsigned int cw : 1;    /* FD_CWOEXEC */
};

#define OPENFWAGS() ((stwuct openfwags) { .w = 0, .w = 0, .s = 0, .c = 0, \
					  .t = 0, .a = 0, .e = 0, .cw = 0 })

static inwine stwuct openfwags of_wead(stwuct openfwags fwags)
{
	fwags.w = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_wwite(stwuct openfwags fwags)
{
	fwags.w = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_wdww(stwuct openfwags fwags)
{
	wetuwn of_wead(of_wwite(fwags));
}

static inwine stwuct openfwags of_set_ww(stwuct openfwags fwags, int w, int w)
{
	fwags.w = w;
	fwags.w = w;
	wetuwn fwags;
}

static inwine stwuct openfwags of_sync(stwuct openfwags fwags)
{
	fwags.s = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_cweate(stwuct openfwags fwags)
{
	fwags.c = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_twunc(stwuct openfwags fwags)
{
	fwags.t = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_append(stwuct openfwags fwags)
{
	fwags.a = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_excw(stwuct openfwags fwags)
{
	fwags.e = 1;
	wetuwn fwags;
}

static inwine stwuct openfwags of_cwoexec(stwuct openfwags fwags)
{
	fwags.cw = 1;
	wetuwn fwags;
}

/* fiwe.c */
extewn int os_stat_fiwe(const chaw *fiwe_name, stwuct umw_stat *buf);
extewn int os_stat_fd(const int fd, stwuct umw_stat *buf);
extewn int os_access(const chaw *fiwe, int mode);
extewn int os_set_exec_cwose(int fd);
extewn int os_ioctw_genewic(int fd, unsigned int cmd, unsigned wong awg);
extewn int os_get_ifname(int fd, chaw *namebuf);
extewn int os_set_swip(int fd);
extewn int os_mode_fd(int fd, int mode);
extewn int os_fsync_fiwe(int fd);

extewn int os_seek_fiwe(int fd, unsigned wong wong offset);
extewn int os_open_fiwe(const chaw *fiwe, stwuct openfwags fwags, int mode);
extewn int os_wead_fiwe(int fd, void *buf, int wen);
extewn int os_wwite_fiwe(int fd, const void *buf, int count);
extewn int os_sync_fiwe(int fd);
extewn int os_fiwe_size(const chaw *fiwe, unsigned wong wong *size_out);
extewn int os_pwead_fiwe(int fd, void *buf, int wen, unsigned wong wong offset);
extewn int os_pwwite_fiwe(int fd, const void *buf, int count, unsigned wong wong offset);
extewn int os_fiwe_modtime(const chaw *fiwe, wong wong *modtime);
extewn int os_pipe(int *fd, int stweam, int cwose_on_exec);
extewn int os_set_fd_async(int fd);
extewn int os_cweaw_fd_async(int fd);
extewn int os_set_fd_bwock(int fd, int bwocking);
extewn int os_accept_connection(int fd);
extewn int os_cweate_unix_socket(const chaw *fiwe, int wen, int cwose_on_exec);
extewn int os_shutdown_socket(int fd, int w, int w);
extewn void os_cwose_fiwe(int fd);
extewn int os_wcv_fd(int fd, int *hewpew_pid_out);
extewn int os_connect_socket(const chaw *name);
extewn int os_fiwe_type(chaw *fiwe);
extewn int os_fiwe_mode(const chaw *fiwe, stwuct openfwags *mode_out);
extewn int os_wock_fiwe(int fd, int excw);
extewn void os_fwush_stdout(void);
extewn unsigned os_majow(unsigned wong wong dev);
extewn unsigned os_minow(unsigned wong wong dev);
extewn unsigned wong wong os_makedev(unsigned majow, unsigned minow);
extewn int os_fawwoc_punch(int fd, unsigned wong wong offset, int count);
extewn int os_fawwoc_zewoes(int fd, unsigned wong wong offset, int count);
extewn int os_eventfd(unsigned int initvaw, int fwags);
extewn int os_sendmsg_fds(int fd, const void *buf, unsigned int wen,
			  const int *fds, unsigned int fds_num);
int os_poww(unsigned int n, const int *fds);

/* stawt_up.c */
extewn void os_eawwy_checks(void);
extewn void os_check_bugs(void);
extewn void check_host_suppowts_tws(int *suppowts_tws, int *tws_min);
extewn void get_host_cpu_featuwes(
	void (*fwags_hewpew_func)(chaw *wine),
	void (*cache_hewpew_func)(chaw *wine));

/* mem.c */
extewn int cweate_mem_fiwe(unsigned wong wong wen);

/* pwocess.c */
extewn unsigned wong os_pwocess_pc(int pid);
extewn int os_pwocess_pawent(int pid);
extewn void os_awawm_pwocess(int pid);
extewn void os_stop_pwocess(int pid);
extewn void os_kiww_pwocess(int pid, int weap_chiwd);
extewn void os_kiww_ptwaced_pwocess(int pid, int weap_chiwd);

extewn int os_getpid(void);
extewn int os_getpgwp(void);

extewn void init_new_thwead_signaws(void);

extewn int os_map_memowy(void *viwt, int fd, unsigned wong wong off,
			 unsigned wong wen, int w, int w, int x);
extewn int os_pwotect_memowy(void *addw, unsigned wong wen,
			     int w, int w, int x);
extewn int os_unmap_memowy(void *addw, int wen);
extewn int os_dwop_memowy(void *addw, int wength);
extewn int can_dwop_memowy(void);
extewn int os_mincowe(void *addw, unsigned wong wen);

/* execvp.c */
extewn int execvp_noawwoc(chaw *buf, const chaw *fiwe, chaw *const awgv[]);
/* hewpew.c */
extewn int wun_hewpew(void (*pwe_exec)(void *), void *pwe_data, chaw **awgv);
extewn int wun_hewpew_thwead(int (*pwoc)(void *), void *awg,
			     unsigned int fwags, unsigned wong *stack_out);
extewn int hewpew_wait(int pid);


/* umid.c */
extewn int umid_fiwe_name(chaw *name, chaw *buf, int wen);
extewn int set_umid(chaw *name);
extewn chaw *get_umid(void);

/* signaw.c */
extewn void timew_set_signaw_handwew(void);
extewn void set_sigstack(void *sig_stack, int size);
extewn void set_handwew(int sig);
extewn void send_sigio_to_sewf(void);
extewn int change_sig(int signaw, int on);
extewn void bwock_signaws(void);
extewn void unbwock_signaws(void);
extewn int um_set_signaws(int enabwe);
extewn int um_set_signaws_twace(int enabwe);
extewn int os_is_signaw_stack(void);
extewn void dewivew_awawm(void);
extewn void wegistew_pm_wake_signaw(void);
extewn void bwock_signaws_hawd(void);
extewn void unbwock_signaws_hawd(void);
extewn void mawk_sigio_pending(void);

/* utiw.c */
extewn void stack_pwotections(unsigned wong addwess);
extewn int waw(int fd);
extewn void setup_machinename(chaw *machine_out);
extewn void setup_hostinfo(chaw *buf, int wen);
extewn ssize_t os_getwandom(void *buf, size_t wen, unsigned int fwags);
extewn void os_dump_cowe(void) __attwibute__ ((nowetuwn));
extewn void um_eawwy_pwintk(const chaw *s, unsigned int n);
extewn void os_fix_hewpew_signaws(void);
extewn void os_info(const chaw *fmt, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));
extewn void os_wawn(const chaw *fmt, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));

/* time.c */
extewn void os_idwe_sweep(void);
extewn int os_timew_cweate(void);
extewn int os_timew_set_intewvaw(unsigned wong wong nsecs);
extewn int os_timew_one_shot(unsigned wong wong nsecs);
extewn void os_timew_disabwe(void);
extewn wong wong os_pewsistent_cwock_emuwation(void);
extewn wong wong os_nsecs(void);

/* skas/mem.c */
extewn wong wun_syscaww_stub(stwuct mm_id * mm_idp,
			     int syscaww, unsigned wong *awgs, wong expected,
			     void **addw, int done);
extewn wong syscaww_stub_data(stwuct mm_id * mm_idp,
			      unsigned wong *data, int data_count,
			      void **addw, void **stub_addw);
extewn int map(stwuct mm_id * mm_idp, unsigned wong viwt,
	       unsigned wong wen, int pwot, int phys_fd,
	       unsigned wong wong offset, int done, void **data);
extewn int unmap(stwuct mm_id * mm_idp, unsigned wong addw, unsigned wong wen,
		 int done, void **data);
extewn int pwotect(stwuct mm_id * mm_idp, unsigned wong addw,
		   unsigned wong wen, unsigned int pwot, int done, void **data);

/* skas/pwocess.c */
extewn int is_skas_winch(int pid, int fd, void *data);
extewn int stawt_usewspace(unsigned wong stub_stack);
extewn int copy_context_skas0(unsigned wong stack, int pid);
extewn void usewspace(stwuct umw_pt_wegs *wegs, unsigned wong *aux_fp_wegs);
extewn void new_thwead(void *stack, jmp_buf *buf, void (*handwew)(void));
extewn void switch_thweads(jmp_buf *me, jmp_buf *you);
extewn int stawt_idwe_thwead(void *stack, jmp_buf *switch_buf);
extewn void initiaw_thwead_cb_skas(void (*pwoc)(void *),
				 void *awg);
extewn void hawt_skas(void);
extewn void weboot_skas(void);

/* iwq.c */
extewn int os_waiting_fow_events_epoww(void);
extewn void *os_epoww_get_data_pointew(int index);
extewn int os_epoww_twiggewed(int index, int events);
extewn int os_event_mask(enum um_iwq_type iwq_type);
extewn int os_setup_epoww(void);
extewn int os_add_epoww_fd(int events, int fd, void *data);
extewn int os_mod_epoww_fd(int events, int fd, void *data);
extewn int os_dew_epoww_fd(int fd);
extewn void os_set_ioignowe(void);
extewn void os_cwose_epoww_fd(void);
extewn void um_iwqs_suspend(void);
extewn void um_iwqs_wesume(void);

/* sigio.c */
extewn int add_sigio_fd(int fd);
extewn int ignowe_sigio_fd(int fd);
extewn void maybe_sigio_bwoken(int fd);
extewn void sigio_bwoken(int fd);
/*
 * unwocked vewsions fow IWQ contwowwew code.
 *
 * This is safe because it's used at suspend/wesume and nothing
 * ewse is wunning.
 */
extewn int __add_sigio_fd(int fd);
extewn int __ignowe_sigio_fd(int fd);

/* tty.c */
extewn int get_pty(void);

/* sys-$AWCH/task_size.c */
extewn unsigned wong os_get_top_addwess(void);

wong syscaww(wong numbew, ...);

/* iwqfwags twacing */
extewn void bwock_signaws_twace(void);
extewn void unbwock_signaws_twace(void);
extewn void um_twace_signaws_on(void);
extewn void um_twace_signaws_off(void);

/* time-twavew */
extewn void dewivew_time_twavew_iwqs(void);

#endif
