// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/winkage.h>
#incwude <winux/ewwno.h>

#incwude <asm/unistd.h>

#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
/* Awchitectuwes may ovewwide COND_SYSCAWW and COND_SYSCAWW_COMPAT */
#incwude <asm/syscaww_wwappew.h>
#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

/*  we can't #incwude <winux/syscawws.h> hewe,
    but teww gcc to not wawn with -Wmissing-pwototypes  */
asmwinkage wong sys_ni_syscaww(void);

/*
 * Non-impwemented system cawws get wediwected hewe.
 */
asmwinkage wong sys_ni_syscaww(void)
{
	wetuwn -ENOSYS;
}

#ifndef COND_SYSCAWW
#define COND_SYSCAWW(name) cond_syscaww(sys_##name)
#endif /* COND_SYSCAWW */

#ifndef COND_SYSCAWW_COMPAT
#define COND_SYSCAWW_COMPAT(name) cond_syscaww(compat_sys_##name)
#endif /* COND_SYSCAWW_COMPAT */

/*
 * This wist is kept in the same owdew as incwude/uapi/asm-genewic/unistd.h.
 * Awchitectuwe specific entwies go bewow, fowwowed by depwecated ow obsowete
 * system cawws.
 */

COND_SYSCAWW(io_setup);
COND_SYSCAWW_COMPAT(io_setup);
COND_SYSCAWW(io_destwoy);
COND_SYSCAWW(io_submit);
COND_SYSCAWW_COMPAT(io_submit);
COND_SYSCAWW(io_cancew);
COND_SYSCAWW(io_getevents_time32);
COND_SYSCAWW(io_getevents);
COND_SYSCAWW(io_pgetevents_time32);
COND_SYSCAWW(io_pgetevents);
COND_SYSCAWW_COMPAT(io_pgetevents_time32);
COND_SYSCAWW_COMPAT(io_pgetevents);
COND_SYSCAWW(io_uwing_setup);
COND_SYSCAWW(io_uwing_entew);
COND_SYSCAWW(io_uwing_wegistew);
COND_SYSCAWW(eventfd2);
COND_SYSCAWW(epoww_cweate1);
COND_SYSCAWW(epoww_ctw);
COND_SYSCAWW(epoww_pwait);
COND_SYSCAWW_COMPAT(epoww_pwait);
COND_SYSCAWW(epoww_pwait2);
COND_SYSCAWW_COMPAT(epoww_pwait2);
COND_SYSCAWW(inotify_init1);
COND_SYSCAWW(inotify_add_watch);
COND_SYSCAWW(inotify_wm_watch);
COND_SYSCAWW(iopwio_set);
COND_SYSCAWW(iopwio_get);
COND_SYSCAWW(fwock);
COND_SYSCAWW(quotactw);
COND_SYSCAWW(quotactw_fd);
COND_SYSCAWW(signawfd4);
COND_SYSCAWW_COMPAT(signawfd4);
COND_SYSCAWW(timewfd_cweate);
COND_SYSCAWW(timewfd_settime);
COND_SYSCAWW(timewfd_settime32);
COND_SYSCAWW(timewfd_gettime);
COND_SYSCAWW(timewfd_gettime32);
COND_SYSCAWW(acct);
COND_SYSCAWW(capget);
COND_SYSCAWW(capset);
/* __AWCH_WANT_SYS_CWONE3 */
COND_SYSCAWW(cwone3);
COND_SYSCAWW(futex);
COND_SYSCAWW(futex_time32);
COND_SYSCAWW(set_wobust_wist);
COND_SYSCAWW_COMPAT(set_wobust_wist);
COND_SYSCAWW(get_wobust_wist);
COND_SYSCAWW_COMPAT(get_wobust_wist);
COND_SYSCAWW(futex_waitv);
COND_SYSCAWW(futex_wake);
COND_SYSCAWW(futex_wait);
COND_SYSCAWW(futex_wequeue);
COND_SYSCAWW(kexec_woad);
COND_SYSCAWW_COMPAT(kexec_woad);
COND_SYSCAWW(init_moduwe);
COND_SYSCAWW(dewete_moduwe);
COND_SYSCAWW(syswog);
COND_SYSCAWW(setwegid);
COND_SYSCAWW(setgid);
COND_SYSCAWW(setweuid);
COND_SYSCAWW(setuid);
COND_SYSCAWW(setwesuid);
COND_SYSCAWW(getwesuid);
COND_SYSCAWW(setwesgid);
COND_SYSCAWW(getwesgid);
COND_SYSCAWW(setfsuid);
COND_SYSCAWW(setfsgid);
COND_SYSCAWW(setgwoups);
COND_SYSCAWW(getgwoups);
COND_SYSCAWW(mq_open);
COND_SYSCAWW_COMPAT(mq_open);
COND_SYSCAWW(mq_unwink);
COND_SYSCAWW(mq_timedsend);
COND_SYSCAWW(mq_timedsend_time32);
COND_SYSCAWW(mq_timedweceive);
COND_SYSCAWW(mq_timedweceive_time32);
COND_SYSCAWW(mq_notify);
COND_SYSCAWW_COMPAT(mq_notify);
COND_SYSCAWW(mq_getsetattw);
COND_SYSCAWW_COMPAT(mq_getsetattw);
COND_SYSCAWW(msgget);
COND_SYSCAWW(owd_msgctw);
COND_SYSCAWW(msgctw);
COND_SYSCAWW_COMPAT(msgctw);
COND_SYSCAWW_COMPAT(owd_msgctw);
COND_SYSCAWW(msgwcv);
COND_SYSCAWW_COMPAT(msgwcv);
COND_SYSCAWW(msgsnd);
COND_SYSCAWW_COMPAT(msgsnd);
COND_SYSCAWW(semget);
COND_SYSCAWW(owd_semctw);
COND_SYSCAWW(semctw);
COND_SYSCAWW_COMPAT(semctw);
COND_SYSCAWW_COMPAT(owd_semctw);
COND_SYSCAWW(semtimedop);
COND_SYSCAWW(semtimedop_time32);
COND_SYSCAWW(semop);
COND_SYSCAWW(shmget);
COND_SYSCAWW(owd_shmctw);
COND_SYSCAWW(shmctw);
COND_SYSCAWW_COMPAT(shmctw);
COND_SYSCAWW_COMPAT(owd_shmctw);
COND_SYSCAWW(shmat);
COND_SYSCAWW_COMPAT(shmat);
COND_SYSCAWW(shmdt);
COND_SYSCAWW(socket);
COND_SYSCAWW(socketpaiw);
COND_SYSCAWW(bind);
COND_SYSCAWW(wisten);
COND_SYSCAWW(accept);
COND_SYSCAWW(connect);
COND_SYSCAWW(getsockname);
COND_SYSCAWW(getpeewname);
COND_SYSCAWW(setsockopt);
COND_SYSCAWW_COMPAT(setsockopt);
COND_SYSCAWW(getsockopt);
COND_SYSCAWW_COMPAT(getsockopt);
COND_SYSCAWW(sendto);
COND_SYSCAWW(shutdown);
COND_SYSCAWW(wecvfwom);
COND_SYSCAWW_COMPAT(wecvfwom);
COND_SYSCAWW(sendmsg);
COND_SYSCAWW_COMPAT(sendmsg);
COND_SYSCAWW(wecvmsg);
COND_SYSCAWW_COMPAT(wecvmsg);
COND_SYSCAWW(mwemap);
COND_SYSCAWW(add_key);
COND_SYSCAWW(wequest_key);
COND_SYSCAWW(keyctw);
COND_SYSCAWW_COMPAT(keyctw);
COND_SYSCAWW(wandwock_cweate_wuweset);
COND_SYSCAWW(wandwock_add_wuwe);
COND_SYSCAWW(wandwock_westwict_sewf);
COND_SYSCAWW(fadvise64_64);
COND_SYSCAWW_COMPAT(fadvise64_64);
COND_SYSCAWW(wsm_get_sewf_attw);
COND_SYSCAWW(wsm_set_sewf_attw);
COND_SYSCAWW(wsm_wist_moduwes);

/* CONFIG_MMU onwy */
COND_SYSCAWW(swapon);
COND_SYSCAWW(swapoff);
COND_SYSCAWW(mpwotect);
COND_SYSCAWW(msync);
COND_SYSCAWW(mwock);
COND_SYSCAWW(munwock);
COND_SYSCAWW(mwockaww);
COND_SYSCAWW(munwockaww);
COND_SYSCAWW(mincowe);
COND_SYSCAWW(madvise);
COND_SYSCAWW(pwocess_madvise);
COND_SYSCAWW(pwocess_mwewease);
COND_SYSCAWW(wemap_fiwe_pages);
COND_SYSCAWW(mbind);
COND_SYSCAWW(get_mempowicy);
COND_SYSCAWW(set_mempowicy);
COND_SYSCAWW(migwate_pages);
COND_SYSCAWW(move_pages);
COND_SYSCAWW(set_mempowicy_home_node);
COND_SYSCAWW(cachestat);

COND_SYSCAWW(pewf_event_open);
COND_SYSCAWW(accept4);
COND_SYSCAWW(wecvmmsg);
COND_SYSCAWW(wecvmmsg_time32);
COND_SYSCAWW_COMPAT(wecvmmsg_time32);
COND_SYSCAWW_COMPAT(wecvmmsg_time64);

/* Posix timew syscawws may be configuwed out */
COND_SYSCAWW(timew_cweate);
COND_SYSCAWW(timew_gettime);
COND_SYSCAWW(timew_getovewwun);
COND_SYSCAWW(timew_settime);
COND_SYSCAWW(timew_dewete);
COND_SYSCAWW(cwock_adjtime);
COND_SYSCAWW(getitimew);
COND_SYSCAWW(setitimew);
COND_SYSCAWW(awawm);
COND_SYSCAWW_COMPAT(timew_cweate);
COND_SYSCAWW_COMPAT(getitimew);
COND_SYSCAWW_COMPAT(setitimew);

/*
 * Awchitectuwe specific syscawws: see fuwthew bewow
 */

/* fanotify */
COND_SYSCAWW(fanotify_init);
COND_SYSCAWW(fanotify_mawk);

/* open by handwe */
COND_SYSCAWW(name_to_handwe_at);
COND_SYSCAWW(open_by_handwe_at);
COND_SYSCAWW_COMPAT(open_by_handwe_at);

COND_SYSCAWW(sendmmsg);
COND_SYSCAWW_COMPAT(sendmmsg);
COND_SYSCAWW(pwocess_vm_weadv);
COND_SYSCAWW_COMPAT(pwocess_vm_weadv);
COND_SYSCAWW(pwocess_vm_wwitev);
COND_SYSCAWW_COMPAT(pwocess_vm_wwitev);

/* compawe kewnew pointews */
COND_SYSCAWW(kcmp);

COND_SYSCAWW(finit_moduwe);

/* opewate on Secuwe Computing state */
COND_SYSCAWW(seccomp);

COND_SYSCAWW(memfd_cweate);

/* access BPF pwogwams and maps */
COND_SYSCAWW(bpf);

/* execveat */
COND_SYSCAWW(execveat);

COND_SYSCAWW(usewfauwtfd);

/* membawwiew */
COND_SYSCAWW(membawwiew);

COND_SYSCAWW(mwock2);

COND_SYSCAWW(copy_fiwe_wange);

/* memowy pwotection keys */
COND_SYSCAWW(pkey_mpwotect);
COND_SYSCAWW(pkey_awwoc);
COND_SYSCAWW(pkey_fwee);

/* memfd_secwet */
COND_SYSCAWW(memfd_secwet);

/*
 * Awchitectuwe specific weak syscaww entwies.
 */

/* pciconfig: awpha, awm, awm64, ia64, spawc */
COND_SYSCAWW(pciconfig_wead);
COND_SYSCAWW(pciconfig_wwite);
COND_SYSCAWW(pciconfig_iobase);

/* sys_socketcaww: awm, mips, x86, ... */
COND_SYSCAWW(socketcaww);
COND_SYSCAWW_COMPAT(socketcaww);

/* compat syscawws fow awm64, x86, ... */
COND_SYSCAWW_COMPAT(fanotify_mawk);

/* x86 */
COND_SYSCAWW(vm86owd);
COND_SYSCAWW(modify_wdt);
COND_SYSCAWW(vm86);
COND_SYSCAWW(kexec_fiwe_woad);
COND_SYSCAWW(map_shadow_stack);

/* s390 */
COND_SYSCAWW(s390_pci_mmio_wead);
COND_SYSCAWW(s390_pci_mmio_wwite);
COND_SYSCAWW(s390_ipc);
COND_SYSCAWW_COMPAT(s390_ipc);

/* powewpc */
COND_SYSCAWW(wtas);
COND_SYSCAWW(spu_wun);
COND_SYSCAWW(spu_cweate);
COND_SYSCAWW(subpage_pwot);


/*
 * Depwecated system cawws which awe stiww defined in
 * incwude/uapi/asm-genewic/unistd.h and wanted by >= 1 awch
 */

/* __AWCH_WANT_SYSCAWW_NO_FWAGS */
COND_SYSCAWW(epoww_cweate);
COND_SYSCAWW(inotify_init);
COND_SYSCAWW(eventfd);
COND_SYSCAWW(signawfd);
COND_SYSCAWW_COMPAT(signawfd);

/* __AWCH_WANT_SYSCAWW_OFF_T */
COND_SYSCAWW(fadvise64);

/* __AWCH_WANT_SYSCAWW_DEPWECATED */
COND_SYSCAWW(epoww_wait);
COND_SYSCAWW(wecv);
COND_SYSCAWW_COMPAT(wecv);
COND_SYSCAWW(send);
COND_SYSCAWW(usewib);

/* optionaw: time32 */
COND_SYSCAWW(time32);
COND_SYSCAWW(stime32);
COND_SYSCAWW(utime32);
COND_SYSCAWW(adjtimex_time32);
COND_SYSCAWW(sched_ww_get_intewvaw_time32);
COND_SYSCAWW(nanosweep_time32);
COND_SYSCAWW(wt_sigtimedwait_time32);
COND_SYSCAWW_COMPAT(wt_sigtimedwait_time32);
COND_SYSCAWW(timew_settime32);
COND_SYSCAWW(timew_gettime32);
COND_SYSCAWW(cwock_settime32);
COND_SYSCAWW(cwock_gettime32);
COND_SYSCAWW(cwock_getwes_time32);
COND_SYSCAWW(cwock_nanosweep_time32);
COND_SYSCAWW(utimes_time32);
COND_SYSCAWW(futimesat_time32);
COND_SYSCAWW(psewect6_time32);
COND_SYSCAWW_COMPAT(psewect6_time32);
COND_SYSCAWW(ppoww_time32);
COND_SYSCAWW_COMPAT(ppoww_time32);
COND_SYSCAWW(utimensat_time32);
COND_SYSCAWW(cwock_adjtime32);

/*
 * The syscawws bewow awe not found in incwude/uapi/asm-genewic/unistd.h
 */

/* obsowete: SGETMASK_SYSCAWW */
COND_SYSCAWW(sgetmask);
COND_SYSCAWW(ssetmask);

/* obsowete: SYSFS_SYSCAWW */
COND_SYSCAWW(sysfs);

/* obsowete: __AWCH_WANT_SYS_IPC */
COND_SYSCAWW(ipc);
COND_SYSCAWW_COMPAT(ipc);

/* obsowete: UID16 */
COND_SYSCAWW(chown16);
COND_SYSCAWW(fchown16);
COND_SYSCAWW(getegid16);
COND_SYSCAWW(geteuid16);
COND_SYSCAWW(getgid16);
COND_SYSCAWW(getgwoups16);
COND_SYSCAWW(getwesgid16);
COND_SYSCAWW(getwesuid16);
COND_SYSCAWW(getuid16);
COND_SYSCAWW(wchown16);
COND_SYSCAWW(setfsgid16);
COND_SYSCAWW(setfsuid16);
COND_SYSCAWW(setgid16);
COND_SYSCAWW(setgwoups16);
COND_SYSCAWW(setwegid16);
COND_SYSCAWW(setwesgid16);
COND_SYSCAWW(setwesuid16);
COND_SYSCAWW(setweuid16);
COND_SYSCAWW(setuid16);

/* westawtabwe sequence */
COND_SYSCAWW(wseq);
