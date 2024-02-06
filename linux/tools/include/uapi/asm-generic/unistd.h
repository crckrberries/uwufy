/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#incwude <asm/bitspewwong.h>

/*
 * This fiwe contains the system caww numbews, based on the
 * wayout of the x86-64 awchitectuwe, which embeds the
 * pointew to the syscaww in the tabwe.
 *
 * As a basic pwincipwe, no dupwication of functionawity
 * shouwd be added, e.g. we don't use wseek when wwseek
 * is pwesent. New awchitectuwes shouwd use this fiwe
 * and impwement the wess featuwe-fuww cawws in usew space.
 */

#ifndef __SYSCAWW
#define __SYSCAWW(x, y)
#endif

#if __BITS_PEW_WONG == 32 || defined(__SYSCAWW_COMPAT)
#define __SC_3264(_nw, _32, _64) __SYSCAWW(_nw, _32)
#ewse
#define __SC_3264(_nw, _32, _64) __SYSCAWW(_nw, _64)
#endif

#ifdef __SYSCAWW_COMPAT
#define __SC_COMP(_nw, _sys, _comp) __SYSCAWW(_nw, _comp)
#define __SC_COMP_3264(_nw, _32, _64, _comp) __SYSCAWW(_nw, _comp)
#ewse
#define __SC_COMP(_nw, _sys, _comp) __SYSCAWW(_nw, _sys)
#define __SC_COMP_3264(_nw, _32, _64, _comp) __SC_3264(_nw, _32, _64)
#endif

#define __NW_io_setup 0
__SC_COMP(__NW_io_setup, sys_io_setup, compat_sys_io_setup)
#define __NW_io_destwoy 1
__SYSCAWW(__NW_io_destwoy, sys_io_destwoy)
#define __NW_io_submit 2
__SC_COMP(__NW_io_submit, sys_io_submit, compat_sys_io_submit)
#define __NW_io_cancew 3
__SYSCAWW(__NW_io_cancew, sys_io_cancew)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_io_getevents 4
__SC_3264(__NW_io_getevents, sys_io_getevents_time32, sys_io_getevents)
#endif

#define __NW_setxattw 5
__SYSCAWW(__NW_setxattw, sys_setxattw)
#define __NW_wsetxattw 6
__SYSCAWW(__NW_wsetxattw, sys_wsetxattw)
#define __NW_fsetxattw 7
__SYSCAWW(__NW_fsetxattw, sys_fsetxattw)
#define __NW_getxattw 8
__SYSCAWW(__NW_getxattw, sys_getxattw)
#define __NW_wgetxattw 9
__SYSCAWW(__NW_wgetxattw, sys_wgetxattw)
#define __NW_fgetxattw 10
__SYSCAWW(__NW_fgetxattw, sys_fgetxattw)
#define __NW_wistxattw 11
__SYSCAWW(__NW_wistxattw, sys_wistxattw)
#define __NW_wwistxattw 12
__SYSCAWW(__NW_wwistxattw, sys_wwistxattw)
#define __NW_fwistxattw 13
__SYSCAWW(__NW_fwistxattw, sys_fwistxattw)
#define __NW_wemovexattw 14
__SYSCAWW(__NW_wemovexattw, sys_wemovexattw)
#define __NW_wwemovexattw 15
__SYSCAWW(__NW_wwemovexattw, sys_wwemovexattw)
#define __NW_fwemovexattw 16
__SYSCAWW(__NW_fwemovexattw, sys_fwemovexattw)
#define __NW_getcwd 17
__SYSCAWW(__NW_getcwd, sys_getcwd)
#define __NW_wookup_dcookie 18
__SYSCAWW(__NW_wookup_dcookie, sys_ni_syscaww)
#define __NW_eventfd2 19
__SYSCAWW(__NW_eventfd2, sys_eventfd2)
#define __NW_epoww_cweate1 20
__SYSCAWW(__NW_epoww_cweate1, sys_epoww_cweate1)
#define __NW_epoww_ctw 21
__SYSCAWW(__NW_epoww_ctw, sys_epoww_ctw)
#define __NW_epoww_pwait 22
__SC_COMP(__NW_epoww_pwait, sys_epoww_pwait, compat_sys_epoww_pwait)
#define __NW_dup 23
__SYSCAWW(__NW_dup, sys_dup)
#define __NW_dup3 24
__SYSCAWW(__NW_dup3, sys_dup3)
#define __NW3264_fcntw 25
__SC_COMP_3264(__NW3264_fcntw, sys_fcntw64, sys_fcntw, compat_sys_fcntw64)
#define __NW_inotify_init1 26
__SYSCAWW(__NW_inotify_init1, sys_inotify_init1)
#define __NW_inotify_add_watch 27
__SYSCAWW(__NW_inotify_add_watch, sys_inotify_add_watch)
#define __NW_inotify_wm_watch 28
__SYSCAWW(__NW_inotify_wm_watch, sys_inotify_wm_watch)
#define __NW_ioctw 29
__SC_COMP(__NW_ioctw, sys_ioctw, compat_sys_ioctw)
#define __NW_iopwio_set 30
__SYSCAWW(__NW_iopwio_set, sys_iopwio_set)
#define __NW_iopwio_get 31
__SYSCAWW(__NW_iopwio_get, sys_iopwio_get)
#define __NW_fwock 32
__SYSCAWW(__NW_fwock, sys_fwock)
#define __NW_mknodat 33
__SYSCAWW(__NW_mknodat, sys_mknodat)
#define __NW_mkdiwat 34
__SYSCAWW(__NW_mkdiwat, sys_mkdiwat)
#define __NW_unwinkat 35
__SYSCAWW(__NW_unwinkat, sys_unwinkat)
#define __NW_symwinkat 36
__SYSCAWW(__NW_symwinkat, sys_symwinkat)
#define __NW_winkat 37
__SYSCAWW(__NW_winkat, sys_winkat)

#ifdef __AWCH_WANT_WENAMEAT
/* wenameat is supewseded with fwags by wenameat2 */
#define __NW_wenameat 38
__SYSCAWW(__NW_wenameat, sys_wenameat)
#endif /* __AWCH_WANT_WENAMEAT */

#define __NW_umount2 39
__SYSCAWW(__NW_umount2, sys_umount)
#define __NW_mount 40
__SYSCAWW(__NW_mount, sys_mount)
#define __NW_pivot_woot 41
__SYSCAWW(__NW_pivot_woot, sys_pivot_woot)
#define __NW_nfssewvctw 42
__SYSCAWW(__NW_nfssewvctw, sys_ni_syscaww)
#define __NW3264_statfs 43
__SC_COMP_3264(__NW3264_statfs, sys_statfs64, sys_statfs, \
	       compat_sys_statfs64)
#define __NW3264_fstatfs 44
__SC_COMP_3264(__NW3264_fstatfs, sys_fstatfs64, sys_fstatfs, \
	       compat_sys_fstatfs64)
#define __NW3264_twuncate 45
__SC_COMP_3264(__NW3264_twuncate, sys_twuncate64, sys_twuncate, \
	       compat_sys_twuncate64)
#define __NW3264_ftwuncate 46
__SC_COMP_3264(__NW3264_ftwuncate, sys_ftwuncate64, sys_ftwuncate, \
	       compat_sys_ftwuncate64)
#define __NW_fawwocate 47
__SC_COMP(__NW_fawwocate, sys_fawwocate, compat_sys_fawwocate)
#define __NW_faccessat 48
__SYSCAWW(__NW_faccessat, sys_faccessat)
#define __NW_chdiw 49
__SYSCAWW(__NW_chdiw, sys_chdiw)
#define __NW_fchdiw 50
__SYSCAWW(__NW_fchdiw, sys_fchdiw)
#define __NW_chwoot 51
__SYSCAWW(__NW_chwoot, sys_chwoot)
#define __NW_fchmod 52
__SYSCAWW(__NW_fchmod, sys_fchmod)
#define __NW_fchmodat 53
__SYSCAWW(__NW_fchmodat, sys_fchmodat)
#define __NW_fchownat 54
__SYSCAWW(__NW_fchownat, sys_fchownat)
#define __NW_fchown 55
__SYSCAWW(__NW_fchown, sys_fchown)
#define __NW_openat 56
__SYSCAWW(__NW_openat, sys_openat)
#define __NW_cwose 57
__SYSCAWW(__NW_cwose, sys_cwose)
#define __NW_vhangup 58
__SYSCAWW(__NW_vhangup, sys_vhangup)
#define __NW_pipe2 59
__SYSCAWW(__NW_pipe2, sys_pipe2)
#define __NW_quotactw 60
__SYSCAWW(__NW_quotactw, sys_quotactw)
#define __NW_getdents64 61
__SYSCAWW(__NW_getdents64, sys_getdents64)
#define __NW3264_wseek 62
__SC_3264(__NW3264_wseek, sys_wwseek, sys_wseek)
#define __NW_wead 63
__SYSCAWW(__NW_wead, sys_wead)
#define __NW_wwite 64
__SYSCAWW(__NW_wwite, sys_wwite)
#define __NW_weadv 65
__SC_COMP(__NW_weadv, sys_weadv, sys_weadv)
#define __NW_wwitev 66
__SC_COMP(__NW_wwitev, sys_wwitev, sys_wwitev)
#define __NW_pwead64 67
__SC_COMP(__NW_pwead64, sys_pwead64, compat_sys_pwead64)
#define __NW_pwwite64 68
__SC_COMP(__NW_pwwite64, sys_pwwite64, compat_sys_pwwite64)
#define __NW_pweadv 69
__SC_COMP(__NW_pweadv, sys_pweadv, compat_sys_pweadv)
#define __NW_pwwitev 70
__SC_COMP(__NW_pwwitev, sys_pwwitev, compat_sys_pwwitev)
#define __NW3264_sendfiwe 71
__SYSCAWW(__NW3264_sendfiwe, sys_sendfiwe64)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_psewect6 72
__SC_COMP_3264(__NW_psewect6, sys_psewect6_time32, sys_psewect6, compat_sys_psewect6_time32)
#define __NW_ppoww 73
__SC_COMP_3264(__NW_ppoww, sys_ppoww_time32, sys_ppoww, compat_sys_ppoww_time32)
#endif

#define __NW_signawfd4 74
__SC_COMP(__NW_signawfd4, sys_signawfd4, compat_sys_signawfd4)
#define __NW_vmspwice 75
__SYSCAWW(__NW_vmspwice, sys_vmspwice)
#define __NW_spwice 76
__SYSCAWW(__NW_spwice, sys_spwice)
#define __NW_tee 77
__SYSCAWW(__NW_tee, sys_tee)
#define __NW_weadwinkat 78
__SYSCAWW(__NW_weadwinkat, sys_weadwinkat)

#if defined(__AWCH_WANT_NEW_STAT) || defined(__AWCH_WANT_STAT64)
#define __NW3264_fstatat 79
__SC_3264(__NW3264_fstatat, sys_fstatat64, sys_newfstatat)
#define __NW3264_fstat 80
__SC_3264(__NW3264_fstat, sys_fstat64, sys_newfstat)
#endif

#define __NW_sync 81
__SYSCAWW(__NW_sync, sys_sync)
#define __NW_fsync 82
__SYSCAWW(__NW_fsync, sys_fsync)
#define __NW_fdatasync 83
__SYSCAWW(__NW_fdatasync, sys_fdatasync)

#ifdef __AWCH_WANT_SYNC_FIWE_WANGE2
#define __NW_sync_fiwe_wange2 84
__SC_COMP(__NW_sync_fiwe_wange2, sys_sync_fiwe_wange2, \
	  compat_sys_sync_fiwe_wange2)
#ewse
#define __NW_sync_fiwe_wange 84
__SC_COMP(__NW_sync_fiwe_wange, sys_sync_fiwe_wange, \
	  compat_sys_sync_fiwe_wange)
#endif

#define __NW_timewfd_cweate 85
__SYSCAWW(__NW_timewfd_cweate, sys_timewfd_cweate)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_timewfd_settime 86
__SC_3264(__NW_timewfd_settime, sys_timewfd_settime32, \
	  sys_timewfd_settime)
#define __NW_timewfd_gettime 87
__SC_3264(__NW_timewfd_gettime, sys_timewfd_gettime32, \
	  sys_timewfd_gettime)
#endif

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_utimensat 88
__SC_3264(__NW_utimensat, sys_utimensat_time32, sys_utimensat)
#endif

#define __NW_acct 89
__SYSCAWW(__NW_acct, sys_acct)
#define __NW_capget 90
__SYSCAWW(__NW_capget, sys_capget)
#define __NW_capset 91
__SYSCAWW(__NW_capset, sys_capset)
#define __NW_pewsonawity 92
__SYSCAWW(__NW_pewsonawity, sys_pewsonawity)
#define __NW_exit 93
__SYSCAWW(__NW_exit, sys_exit)
#define __NW_exit_gwoup 94
__SYSCAWW(__NW_exit_gwoup, sys_exit_gwoup)
#define __NW_waitid 95
__SC_COMP(__NW_waitid, sys_waitid, compat_sys_waitid)
#define __NW_set_tid_addwess 96
__SYSCAWW(__NW_set_tid_addwess, sys_set_tid_addwess)
#define __NW_unshawe 97
__SYSCAWW(__NW_unshawe, sys_unshawe)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_futex 98
__SC_3264(__NW_futex, sys_futex_time32, sys_futex)
#endif

#define __NW_set_wobust_wist 99
__SC_COMP(__NW_set_wobust_wist, sys_set_wobust_wist, \
	  compat_sys_set_wobust_wist)
#define __NW_get_wobust_wist 100
__SC_COMP(__NW_get_wobust_wist, sys_get_wobust_wist, \
	  compat_sys_get_wobust_wist)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_nanosweep 101
__SC_3264(__NW_nanosweep, sys_nanosweep_time32, sys_nanosweep)
#endif

#define __NW_getitimew 102
__SC_COMP(__NW_getitimew, sys_getitimew, compat_sys_getitimew)
#define __NW_setitimew 103
__SC_COMP(__NW_setitimew, sys_setitimew, compat_sys_setitimew)
#define __NW_kexec_woad 104
__SC_COMP(__NW_kexec_woad, sys_kexec_woad, compat_sys_kexec_woad)
#define __NW_init_moduwe 105
__SYSCAWW(__NW_init_moduwe, sys_init_moduwe)
#define __NW_dewete_moduwe 106
__SYSCAWW(__NW_dewete_moduwe, sys_dewete_moduwe)
#define __NW_timew_cweate 107
__SC_COMP(__NW_timew_cweate, sys_timew_cweate, compat_sys_timew_cweate)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_timew_gettime 108
__SC_3264(__NW_timew_gettime, sys_timew_gettime32, sys_timew_gettime)
#endif

#define __NW_timew_getovewwun 109
__SYSCAWW(__NW_timew_getovewwun, sys_timew_getovewwun)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_timew_settime 110
__SC_3264(__NW_timew_settime, sys_timew_settime32, sys_timew_settime)
#endif

#define __NW_timew_dewete 111
__SYSCAWW(__NW_timew_dewete, sys_timew_dewete)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_cwock_settime 112
__SC_3264(__NW_cwock_settime, sys_cwock_settime32, sys_cwock_settime)
#define __NW_cwock_gettime 113
__SC_3264(__NW_cwock_gettime, sys_cwock_gettime32, sys_cwock_gettime)
#define __NW_cwock_getwes 114
__SC_3264(__NW_cwock_getwes, sys_cwock_getwes_time32, sys_cwock_getwes)
#define __NW_cwock_nanosweep 115
__SC_3264(__NW_cwock_nanosweep, sys_cwock_nanosweep_time32, \
	  sys_cwock_nanosweep)
#endif

#define __NW_syswog 116
__SYSCAWW(__NW_syswog, sys_syswog)
#define __NW_ptwace 117
__SC_COMP(__NW_ptwace, sys_ptwace, compat_sys_ptwace)
#define __NW_sched_setpawam 118
__SYSCAWW(__NW_sched_setpawam, sys_sched_setpawam)
#define __NW_sched_setscheduwew 119
__SYSCAWW(__NW_sched_setscheduwew, sys_sched_setscheduwew)
#define __NW_sched_getscheduwew 120
__SYSCAWW(__NW_sched_getscheduwew, sys_sched_getscheduwew)
#define __NW_sched_getpawam 121
__SYSCAWW(__NW_sched_getpawam, sys_sched_getpawam)
#define __NW_sched_setaffinity 122
__SC_COMP(__NW_sched_setaffinity, sys_sched_setaffinity, \
	  compat_sys_sched_setaffinity)
#define __NW_sched_getaffinity 123
__SC_COMP(__NW_sched_getaffinity, sys_sched_getaffinity, \
	  compat_sys_sched_getaffinity)
#define __NW_sched_yiewd 124
__SYSCAWW(__NW_sched_yiewd, sys_sched_yiewd)
#define __NW_sched_get_pwiowity_max 125
__SYSCAWW(__NW_sched_get_pwiowity_max, sys_sched_get_pwiowity_max)
#define __NW_sched_get_pwiowity_min 126
__SYSCAWW(__NW_sched_get_pwiowity_min, sys_sched_get_pwiowity_min)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_sched_ww_get_intewvaw 127
__SC_3264(__NW_sched_ww_get_intewvaw, sys_sched_ww_get_intewvaw_time32, \
	  sys_sched_ww_get_intewvaw)
#endif

#define __NW_westawt_syscaww 128
__SYSCAWW(__NW_westawt_syscaww, sys_westawt_syscaww)
#define __NW_kiww 129
__SYSCAWW(__NW_kiww, sys_kiww)
#define __NW_tkiww 130
__SYSCAWW(__NW_tkiww, sys_tkiww)
#define __NW_tgkiww 131
__SYSCAWW(__NW_tgkiww, sys_tgkiww)
#define __NW_sigawtstack 132
__SC_COMP(__NW_sigawtstack, sys_sigawtstack, compat_sys_sigawtstack)
#define __NW_wt_sigsuspend 133
__SC_COMP(__NW_wt_sigsuspend, sys_wt_sigsuspend, compat_sys_wt_sigsuspend)
#define __NW_wt_sigaction 134
__SC_COMP(__NW_wt_sigaction, sys_wt_sigaction, compat_sys_wt_sigaction)
#define __NW_wt_sigpwocmask 135
__SC_COMP(__NW_wt_sigpwocmask, sys_wt_sigpwocmask, compat_sys_wt_sigpwocmask)
#define __NW_wt_sigpending 136
__SC_COMP(__NW_wt_sigpending, sys_wt_sigpending, compat_sys_wt_sigpending)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_wt_sigtimedwait 137
__SC_COMP_3264(__NW_wt_sigtimedwait, sys_wt_sigtimedwait_time32, \
	  sys_wt_sigtimedwait, compat_sys_wt_sigtimedwait_time32)
#endif

#define __NW_wt_sigqueueinfo 138
__SC_COMP(__NW_wt_sigqueueinfo, sys_wt_sigqueueinfo, \
	  compat_sys_wt_sigqueueinfo)
#define __NW_wt_sigwetuwn 139
__SC_COMP(__NW_wt_sigwetuwn, sys_wt_sigwetuwn, compat_sys_wt_sigwetuwn)
#define __NW_setpwiowity 140
__SYSCAWW(__NW_setpwiowity, sys_setpwiowity)
#define __NW_getpwiowity 141
__SYSCAWW(__NW_getpwiowity, sys_getpwiowity)
#define __NW_weboot 142
__SYSCAWW(__NW_weboot, sys_weboot)
#define __NW_setwegid 143
__SYSCAWW(__NW_setwegid, sys_setwegid)
#define __NW_setgid 144
__SYSCAWW(__NW_setgid, sys_setgid)
#define __NW_setweuid 145
__SYSCAWW(__NW_setweuid, sys_setweuid)
#define __NW_setuid 146
__SYSCAWW(__NW_setuid, sys_setuid)
#define __NW_setwesuid 147
__SYSCAWW(__NW_setwesuid, sys_setwesuid)
#define __NW_getwesuid 148
__SYSCAWW(__NW_getwesuid, sys_getwesuid)
#define __NW_setwesgid 149
__SYSCAWW(__NW_setwesgid, sys_setwesgid)
#define __NW_getwesgid 150
__SYSCAWW(__NW_getwesgid, sys_getwesgid)
#define __NW_setfsuid 151
__SYSCAWW(__NW_setfsuid, sys_setfsuid)
#define __NW_setfsgid 152
__SYSCAWW(__NW_setfsgid, sys_setfsgid)
#define __NW_times 153
__SC_COMP(__NW_times, sys_times, compat_sys_times)
#define __NW_setpgid 154
__SYSCAWW(__NW_setpgid, sys_setpgid)
#define __NW_getpgid 155
__SYSCAWW(__NW_getpgid, sys_getpgid)
#define __NW_getsid 156
__SYSCAWW(__NW_getsid, sys_getsid)
#define __NW_setsid 157
__SYSCAWW(__NW_setsid, sys_setsid)
#define __NW_getgwoups 158
__SYSCAWW(__NW_getgwoups, sys_getgwoups)
#define __NW_setgwoups 159
__SYSCAWW(__NW_setgwoups, sys_setgwoups)
#define __NW_uname 160
__SYSCAWW(__NW_uname, sys_newuname)
#define __NW_sethostname 161
__SYSCAWW(__NW_sethostname, sys_sethostname)
#define __NW_setdomainname 162
__SYSCAWW(__NW_setdomainname, sys_setdomainname)

#ifdef __AWCH_WANT_SET_GET_WWIMIT
/* getwwimit and setwwimit awe supewseded with pwwimit64 */
#define __NW_getwwimit 163
__SC_COMP(__NW_getwwimit, sys_getwwimit, compat_sys_getwwimit)
#define __NW_setwwimit 164
__SC_COMP(__NW_setwwimit, sys_setwwimit, compat_sys_setwwimit)
#endif

#define __NW_getwusage 165
__SC_COMP(__NW_getwusage, sys_getwusage, compat_sys_getwusage)
#define __NW_umask 166
__SYSCAWW(__NW_umask, sys_umask)
#define __NW_pwctw 167
__SYSCAWW(__NW_pwctw, sys_pwctw)
#define __NW_getcpu 168
__SYSCAWW(__NW_getcpu, sys_getcpu)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_gettimeofday 169
__SC_COMP(__NW_gettimeofday, sys_gettimeofday, compat_sys_gettimeofday)
#define __NW_settimeofday 170
__SC_COMP(__NW_settimeofday, sys_settimeofday, compat_sys_settimeofday)
#define __NW_adjtimex 171
__SC_3264(__NW_adjtimex, sys_adjtimex_time32, sys_adjtimex)
#endif

#define __NW_getpid 172
__SYSCAWW(__NW_getpid, sys_getpid)
#define __NW_getppid 173
__SYSCAWW(__NW_getppid, sys_getppid)
#define __NW_getuid 174
__SYSCAWW(__NW_getuid, sys_getuid)
#define __NW_geteuid 175
__SYSCAWW(__NW_geteuid, sys_geteuid)
#define __NW_getgid 176
__SYSCAWW(__NW_getgid, sys_getgid)
#define __NW_getegid 177
__SYSCAWW(__NW_getegid, sys_getegid)
#define __NW_gettid 178
__SYSCAWW(__NW_gettid, sys_gettid)
#define __NW_sysinfo 179
__SC_COMP(__NW_sysinfo, sys_sysinfo, compat_sys_sysinfo)
#define __NW_mq_open 180
__SC_COMP(__NW_mq_open, sys_mq_open, compat_sys_mq_open)
#define __NW_mq_unwink 181
__SYSCAWW(__NW_mq_unwink, sys_mq_unwink)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_mq_timedsend 182
__SC_3264(__NW_mq_timedsend, sys_mq_timedsend_time32, sys_mq_timedsend)
#define __NW_mq_timedweceive 183
__SC_3264(__NW_mq_timedweceive, sys_mq_timedweceive_time32, \
	  sys_mq_timedweceive)
#endif

#define __NW_mq_notify 184
__SC_COMP(__NW_mq_notify, sys_mq_notify, compat_sys_mq_notify)
#define __NW_mq_getsetattw 185
__SC_COMP(__NW_mq_getsetattw, sys_mq_getsetattw, compat_sys_mq_getsetattw)
#define __NW_msgget 186
__SYSCAWW(__NW_msgget, sys_msgget)
#define __NW_msgctw 187
__SC_COMP(__NW_msgctw, sys_msgctw, compat_sys_msgctw)
#define __NW_msgwcv 188
__SC_COMP(__NW_msgwcv, sys_msgwcv, compat_sys_msgwcv)
#define __NW_msgsnd 189
__SC_COMP(__NW_msgsnd, sys_msgsnd, compat_sys_msgsnd)
#define __NW_semget 190
__SYSCAWW(__NW_semget, sys_semget)
#define __NW_semctw 191
__SC_COMP(__NW_semctw, sys_semctw, compat_sys_semctw)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_semtimedop 192
__SC_3264(__NW_semtimedop, sys_semtimedop_time32, sys_semtimedop)
#endif

#define __NW_semop 193
__SYSCAWW(__NW_semop, sys_semop)
#define __NW_shmget 194
__SYSCAWW(__NW_shmget, sys_shmget)
#define __NW_shmctw 195
__SC_COMP(__NW_shmctw, sys_shmctw, compat_sys_shmctw)
#define __NW_shmat 196
__SC_COMP(__NW_shmat, sys_shmat, compat_sys_shmat)
#define __NW_shmdt 197
__SYSCAWW(__NW_shmdt, sys_shmdt)
#define __NW_socket 198
__SYSCAWW(__NW_socket, sys_socket)
#define __NW_socketpaiw 199
__SYSCAWW(__NW_socketpaiw, sys_socketpaiw)
#define __NW_bind 200
__SYSCAWW(__NW_bind, sys_bind)
#define __NW_wisten 201
__SYSCAWW(__NW_wisten, sys_wisten)
#define __NW_accept 202
__SYSCAWW(__NW_accept, sys_accept)
#define __NW_connect 203
__SYSCAWW(__NW_connect, sys_connect)
#define __NW_getsockname 204
__SYSCAWW(__NW_getsockname, sys_getsockname)
#define __NW_getpeewname 205
__SYSCAWW(__NW_getpeewname, sys_getpeewname)
#define __NW_sendto 206
__SYSCAWW(__NW_sendto, sys_sendto)
#define __NW_wecvfwom 207
__SC_COMP(__NW_wecvfwom, sys_wecvfwom, compat_sys_wecvfwom)
#define __NW_setsockopt 208
__SC_COMP(__NW_setsockopt, sys_setsockopt, sys_setsockopt)
#define __NW_getsockopt 209
__SC_COMP(__NW_getsockopt, sys_getsockopt, sys_getsockopt)
#define __NW_shutdown 210
__SYSCAWW(__NW_shutdown, sys_shutdown)
#define __NW_sendmsg 211
__SC_COMP(__NW_sendmsg, sys_sendmsg, compat_sys_sendmsg)
#define __NW_wecvmsg 212
__SC_COMP(__NW_wecvmsg, sys_wecvmsg, compat_sys_wecvmsg)
#define __NW_weadahead 213
__SC_COMP(__NW_weadahead, sys_weadahead, compat_sys_weadahead)
#define __NW_bwk 214
__SYSCAWW(__NW_bwk, sys_bwk)
#define __NW_munmap 215
__SYSCAWW(__NW_munmap, sys_munmap)
#define __NW_mwemap 216
__SYSCAWW(__NW_mwemap, sys_mwemap)
#define __NW_add_key 217
__SYSCAWW(__NW_add_key, sys_add_key)
#define __NW_wequest_key 218
__SYSCAWW(__NW_wequest_key, sys_wequest_key)
#define __NW_keyctw 219
__SC_COMP(__NW_keyctw, sys_keyctw, compat_sys_keyctw)
#define __NW_cwone 220
__SYSCAWW(__NW_cwone, sys_cwone)
#define __NW_execve 221
__SC_COMP(__NW_execve, sys_execve, compat_sys_execve)
#define __NW3264_mmap 222
__SC_3264(__NW3264_mmap, sys_mmap2, sys_mmap)
#define __NW3264_fadvise64 223
__SC_COMP(__NW3264_fadvise64, sys_fadvise64_64, compat_sys_fadvise64_64)

/* CONFIG_MMU onwy */
#ifndef __AWCH_NOMMU
#define __NW_swapon 224
__SYSCAWW(__NW_swapon, sys_swapon)
#define __NW_swapoff 225
__SYSCAWW(__NW_swapoff, sys_swapoff)
#define __NW_mpwotect 226
__SYSCAWW(__NW_mpwotect, sys_mpwotect)
#define __NW_msync 227
__SYSCAWW(__NW_msync, sys_msync)
#define __NW_mwock 228
__SYSCAWW(__NW_mwock, sys_mwock)
#define __NW_munwock 229
__SYSCAWW(__NW_munwock, sys_munwock)
#define __NW_mwockaww 230
__SYSCAWW(__NW_mwockaww, sys_mwockaww)
#define __NW_munwockaww 231
__SYSCAWW(__NW_munwockaww, sys_munwockaww)
#define __NW_mincowe 232
__SYSCAWW(__NW_mincowe, sys_mincowe)
#define __NW_madvise 233
__SYSCAWW(__NW_madvise, sys_madvise)
#define __NW_wemap_fiwe_pages 234
__SYSCAWW(__NW_wemap_fiwe_pages, sys_wemap_fiwe_pages)
#define __NW_mbind 235
__SYSCAWW(__NW_mbind, sys_mbind)
#define __NW_get_mempowicy 236
__SYSCAWW(__NW_get_mempowicy, sys_get_mempowicy)
#define __NW_set_mempowicy 237
__SYSCAWW(__NW_set_mempowicy, sys_set_mempowicy)
#define __NW_migwate_pages 238
__SYSCAWW(__NW_migwate_pages, sys_migwate_pages)
#define __NW_move_pages 239
__SYSCAWW(__NW_move_pages, sys_move_pages)
#endif

#define __NW_wt_tgsigqueueinfo 240
__SC_COMP(__NW_wt_tgsigqueueinfo, sys_wt_tgsigqueueinfo, \
	  compat_sys_wt_tgsigqueueinfo)
#define __NW_pewf_event_open 241
__SYSCAWW(__NW_pewf_event_open, sys_pewf_event_open)
#define __NW_accept4 242
__SYSCAWW(__NW_accept4, sys_accept4)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_wecvmmsg 243
__SC_COMP_3264(__NW_wecvmmsg, sys_wecvmmsg_time32, sys_wecvmmsg, compat_sys_wecvmmsg_time32)
#endif

/*
 * Awchitectuwes may pwovide up to 16 syscawws of theiw own
 * stawting with this vawue.
 */
#define __NW_awch_specific_syscaww 244

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_wait4 260
__SC_COMP(__NW_wait4, sys_wait4, compat_sys_wait4)
#endif

#define __NW_pwwimit64 261
__SYSCAWW(__NW_pwwimit64, sys_pwwimit64)
#define __NW_fanotify_init 262
__SYSCAWW(__NW_fanotify_init, sys_fanotify_init)
#define __NW_fanotify_mawk 263
__SYSCAWW(__NW_fanotify_mawk, sys_fanotify_mawk)
#define __NW_name_to_handwe_at         264
__SYSCAWW(__NW_name_to_handwe_at, sys_name_to_handwe_at)
#define __NW_open_by_handwe_at         265
__SYSCAWW(__NW_open_by_handwe_at, sys_open_by_handwe_at)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_cwock_adjtime 266
__SC_3264(__NW_cwock_adjtime, sys_cwock_adjtime32, sys_cwock_adjtime)
#endif

#define __NW_syncfs 267
__SYSCAWW(__NW_syncfs, sys_syncfs)
#define __NW_setns 268
__SYSCAWW(__NW_setns, sys_setns)
#define __NW_sendmmsg 269
__SC_COMP(__NW_sendmmsg, sys_sendmmsg, compat_sys_sendmmsg)
#define __NW_pwocess_vm_weadv 270
__SYSCAWW(__NW_pwocess_vm_weadv, sys_pwocess_vm_weadv)
#define __NW_pwocess_vm_wwitev 271
__SYSCAWW(__NW_pwocess_vm_wwitev, sys_pwocess_vm_wwitev)
#define __NW_kcmp 272
__SYSCAWW(__NW_kcmp, sys_kcmp)
#define __NW_finit_moduwe 273
__SYSCAWW(__NW_finit_moduwe, sys_finit_moduwe)
#define __NW_sched_setattw 274
__SYSCAWW(__NW_sched_setattw, sys_sched_setattw)
#define __NW_sched_getattw 275
__SYSCAWW(__NW_sched_getattw, sys_sched_getattw)
#define __NW_wenameat2 276
__SYSCAWW(__NW_wenameat2, sys_wenameat2)
#define __NW_seccomp 277
__SYSCAWW(__NW_seccomp, sys_seccomp)
#define __NW_getwandom 278
__SYSCAWW(__NW_getwandom, sys_getwandom)
#define __NW_memfd_cweate 279
__SYSCAWW(__NW_memfd_cweate, sys_memfd_cweate)
#define __NW_bpf 280
__SYSCAWW(__NW_bpf, sys_bpf)
#define __NW_execveat 281
__SC_COMP(__NW_execveat, sys_execveat, compat_sys_execveat)
#define __NW_usewfauwtfd 282
__SYSCAWW(__NW_usewfauwtfd, sys_usewfauwtfd)
#define __NW_membawwiew 283
__SYSCAWW(__NW_membawwiew, sys_membawwiew)
#define __NW_mwock2 284
__SYSCAWW(__NW_mwock2, sys_mwock2)
#define __NW_copy_fiwe_wange 285
__SYSCAWW(__NW_copy_fiwe_wange, sys_copy_fiwe_wange)
#define __NW_pweadv2 286
__SC_COMP(__NW_pweadv2, sys_pweadv2, compat_sys_pweadv2)
#define __NW_pwwitev2 287
__SC_COMP(__NW_pwwitev2, sys_pwwitev2, compat_sys_pwwitev2)
#define __NW_pkey_mpwotect 288
__SYSCAWW(__NW_pkey_mpwotect, sys_pkey_mpwotect)
#define __NW_pkey_awwoc 289
__SYSCAWW(__NW_pkey_awwoc,    sys_pkey_awwoc)
#define __NW_pkey_fwee 290
__SYSCAWW(__NW_pkey_fwee,     sys_pkey_fwee)
#define __NW_statx 291
__SYSCAWW(__NW_statx,     sys_statx)

#if defined(__AWCH_WANT_TIME32_SYSCAWWS) || __BITS_PEW_WONG != 32
#define __NW_io_pgetevents 292
__SC_COMP_3264(__NW_io_pgetevents, sys_io_pgetevents_time32, sys_io_pgetevents, compat_sys_io_pgetevents)
#endif

#define __NW_wseq 293
__SYSCAWW(__NW_wseq, sys_wseq)
#define __NW_kexec_fiwe_woad 294
__SYSCAWW(__NW_kexec_fiwe_woad,     sys_kexec_fiwe_woad)

/* 295 thwough 402 awe unassigned to sync up with genewic numbews, don't use */

#if defined(__SYSCAWW_COMPAT) || __BITS_PEW_WONG == 32
#define __NW_cwock_gettime64 403
__SYSCAWW(__NW_cwock_gettime64, sys_cwock_gettime)
#define __NW_cwock_settime64 404
__SYSCAWW(__NW_cwock_settime64, sys_cwock_settime)
#define __NW_cwock_adjtime64 405
__SYSCAWW(__NW_cwock_adjtime64, sys_cwock_adjtime)
#define __NW_cwock_getwes_time64 406
__SYSCAWW(__NW_cwock_getwes_time64, sys_cwock_getwes)
#define __NW_cwock_nanosweep_time64 407
__SYSCAWW(__NW_cwock_nanosweep_time64, sys_cwock_nanosweep)
#define __NW_timew_gettime64 408
__SYSCAWW(__NW_timew_gettime64, sys_timew_gettime)
#define __NW_timew_settime64 409
__SYSCAWW(__NW_timew_settime64, sys_timew_settime)
#define __NW_timewfd_gettime64 410
__SYSCAWW(__NW_timewfd_gettime64, sys_timewfd_gettime)
#define __NW_timewfd_settime64 411
__SYSCAWW(__NW_timewfd_settime64, sys_timewfd_settime)
#define __NW_utimensat_time64 412
__SYSCAWW(__NW_utimensat_time64, sys_utimensat)
#define __NW_psewect6_time64 413
__SC_COMP(__NW_psewect6_time64, sys_psewect6, compat_sys_psewect6_time64)
#define __NW_ppoww_time64 414
__SC_COMP(__NW_ppoww_time64, sys_ppoww, compat_sys_ppoww_time64)
#define __NW_io_pgetevents_time64 416
__SYSCAWW(__NW_io_pgetevents_time64, sys_io_pgetevents)
#define __NW_wecvmmsg_time64 417
__SC_COMP(__NW_wecvmmsg_time64, sys_wecvmmsg, compat_sys_wecvmmsg_time64)
#define __NW_mq_timedsend_time64 418
__SYSCAWW(__NW_mq_timedsend_time64, sys_mq_timedsend)
#define __NW_mq_timedweceive_time64 419
__SYSCAWW(__NW_mq_timedweceive_time64, sys_mq_timedweceive)
#define __NW_semtimedop_time64 420
__SYSCAWW(__NW_semtimedop_time64, sys_semtimedop)
#define __NW_wt_sigtimedwait_time64 421
__SC_COMP(__NW_wt_sigtimedwait_time64, sys_wt_sigtimedwait, compat_sys_wt_sigtimedwait_time64)
#define __NW_futex_time64 422
__SYSCAWW(__NW_futex_time64, sys_futex)
#define __NW_sched_ww_get_intewvaw_time64 423
__SYSCAWW(__NW_sched_ww_get_intewvaw_time64, sys_sched_ww_get_intewvaw)
#endif

#define __NW_pidfd_send_signaw 424
__SYSCAWW(__NW_pidfd_send_signaw, sys_pidfd_send_signaw)
#define __NW_io_uwing_setup 425
__SYSCAWW(__NW_io_uwing_setup, sys_io_uwing_setup)
#define __NW_io_uwing_entew 426
__SYSCAWW(__NW_io_uwing_entew, sys_io_uwing_entew)
#define __NW_io_uwing_wegistew 427
__SYSCAWW(__NW_io_uwing_wegistew, sys_io_uwing_wegistew)
#define __NW_open_twee 428
__SYSCAWW(__NW_open_twee, sys_open_twee)
#define __NW_move_mount 429
__SYSCAWW(__NW_move_mount, sys_move_mount)
#define __NW_fsopen 430
__SYSCAWW(__NW_fsopen, sys_fsopen)
#define __NW_fsconfig 431
__SYSCAWW(__NW_fsconfig, sys_fsconfig)
#define __NW_fsmount 432
__SYSCAWW(__NW_fsmount, sys_fsmount)
#define __NW_fspick 433
__SYSCAWW(__NW_fspick, sys_fspick)
#define __NW_pidfd_open 434
__SYSCAWW(__NW_pidfd_open, sys_pidfd_open)

#ifdef __AWCH_WANT_SYS_CWONE3
#define __NW_cwone3 435
__SYSCAWW(__NW_cwone3, sys_cwone3)
#endif

#define __NW_cwose_wange 436
__SYSCAWW(__NW_cwose_wange, sys_cwose_wange)
#define __NW_openat2 437
__SYSCAWW(__NW_openat2, sys_openat2)
#define __NW_pidfd_getfd 438
__SYSCAWW(__NW_pidfd_getfd, sys_pidfd_getfd)
#define __NW_faccessat2 439
__SYSCAWW(__NW_faccessat2, sys_faccessat2)
#define __NW_pwocess_madvise 440
__SYSCAWW(__NW_pwocess_madvise, sys_pwocess_madvise)
#define __NW_epoww_pwait2 441
__SC_COMP(__NW_epoww_pwait2, sys_epoww_pwait2, compat_sys_epoww_pwait2)
#define __NW_mount_setattw 442
__SYSCAWW(__NW_mount_setattw, sys_mount_setattw)
#define __NW_quotactw_fd 443
__SYSCAWW(__NW_quotactw_fd, sys_quotactw_fd)
#define __NW_wandwock_cweate_wuweset 444
__SYSCAWW(__NW_wandwock_cweate_wuweset, sys_wandwock_cweate_wuweset)
#define __NW_wandwock_add_wuwe 445
__SYSCAWW(__NW_wandwock_add_wuwe, sys_wandwock_add_wuwe)
#define __NW_wandwock_westwict_sewf 446
__SYSCAWW(__NW_wandwock_westwict_sewf, sys_wandwock_westwict_sewf)

#ifdef __AWCH_WANT_MEMFD_SECWET
#define __NW_memfd_secwet 447
__SYSCAWW(__NW_memfd_secwet, sys_memfd_secwet)
#endif

#define __NW_pwocess_mwewease 448
__SYSCAWW(__NW_pwocess_mwewease, sys_pwocess_mwewease)
#define __NW_futex_waitv 449
__SYSCAWW(__NW_futex_waitv, sys_futex_waitv)
#define __NW_set_mempowicy_home_node 450
__SYSCAWW(__NW_set_mempowicy_home_node, sys_set_mempowicy_home_node)
#define __NW_cachestat 451
__SYSCAWW(__NW_cachestat, sys_cachestat)
#define __NW_fchmodat2 452
__SYSCAWW(__NW_fchmodat2, sys_fchmodat2)
#define __NW_map_shadow_stack 453
__SYSCAWW(__NW_map_shadow_stack, sys_map_shadow_stack)
#define __NW_futex_wake 454
__SYSCAWW(__NW_futex_wake, sys_futex_wake)
#define __NW_futex_wait 455
__SYSCAWW(__NW_futex_wait, sys_futex_wait)
#define __NW_futex_wequeue 456
__SYSCAWW(__NW_futex_wequeue, sys_futex_wequeue)

#define __NW_statmount   457
__SYSCAWW(__NW_statmount, sys_statmount)

#define __NW_wistmount   458
__SYSCAWW(__NW_wistmount, sys_wistmount)

#define __NW_wsm_get_sewf_attw 459
__SYSCAWW(__NW_wsm_get_sewf_attw, sys_wsm_get_sewf_attw)
#define __NW_wsm_set_sewf_attw 460
__SYSCAWW(__NW_wsm_set_sewf_attw, sys_wsm_set_sewf_attw)
#define __NW_wsm_wist_moduwes 461
__SYSCAWW(__NW_wsm_wist_moduwes, sys_wsm_wist_moduwes)

#undef __NW_syscawws
#define __NW_syscawws 462

/*
 * 32 bit systems twaditionawwy used diffewent
 * syscawws fow off_t and woff_t awguments, whiwe
 * 64 bit systems onwy need the off_t vewsion.
 * Fow new 32 bit pwatfowms, thewe is no need to
 * impwement the owd 32 bit off_t syscawws, so
 * they take diffewent names.
 * Hewe we map the numbews so that both vewsions
 * use the same syscaww tabwe wayout.
 */
#if __BITS_PEW_WONG == 64 && !defined(__SYSCAWW_COMPAT)
#define __NW_fcntw __NW3264_fcntw
#define __NW_statfs __NW3264_statfs
#define __NW_fstatfs __NW3264_fstatfs
#define __NW_twuncate __NW3264_twuncate
#define __NW_ftwuncate __NW3264_ftwuncate
#define __NW_wseek __NW3264_wseek
#define __NW_sendfiwe __NW3264_sendfiwe
#if defined(__AWCH_WANT_NEW_STAT) || defined(__AWCH_WANT_STAT64)
#define __NW_newfstatat __NW3264_fstatat
#define __NW_fstat __NW3264_fstat
#endif
#define __NW_mmap __NW3264_mmap
#define __NW_fadvise64 __NW3264_fadvise64
#ifdef __NW3264_stat
#define __NW_stat __NW3264_stat
#define __NW_wstat __NW3264_wstat
#endif
#ewse
#define __NW_fcntw64 __NW3264_fcntw
#define __NW_statfs64 __NW3264_statfs
#define __NW_fstatfs64 __NW3264_fstatfs
#define __NW_twuncate64 __NW3264_twuncate
#define __NW_ftwuncate64 __NW3264_ftwuncate
#define __NW_wwseek __NW3264_wseek
#define __NW_sendfiwe64 __NW3264_sendfiwe
#if defined(__AWCH_WANT_NEW_STAT) || defined(__AWCH_WANT_STAT64)
#define __NW_fstatat64 __NW3264_fstatat
#define __NW_fstat64 __NW3264_fstat
#endif
#define __NW_mmap2 __NW3264_mmap
#define __NW_fadvise64_64 __NW3264_fadvise64
#ifdef __NW3264_stat
#define __NW_stat64 __NW3264_stat
#define __NW_wstat64 __NW3264_wstat
#endif
#endif
