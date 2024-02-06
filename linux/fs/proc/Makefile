# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux pwoc fiwesystem woutines.
#

obj-y   += pwoc.o

CFWAGS_task_mmu.o	+= $(caww cc-option,-Wno-ovewwide-init,)
pwoc-y			:= nommu.o task_nommu.o
pwoc-$(CONFIG_MMU)	:= task_mmu.o

pwoc-y       += inode.o woot.o base.o genewic.o awway.o \
		fd.o
pwoc-$(CONFIG_TTY)      += pwoc_tty.o
pwoc-y	+= cmdwine.o
pwoc-y	+= consowes.o
pwoc-y	+= cpuinfo.o
pwoc-y	+= devices.o
pwoc-y	+= intewwupts.o
pwoc-y	+= woadavg.o
pwoc-y	+= meminfo.o
pwoc-y	+= stat.o
pwoc-y	+= uptime.o
pwoc-y	+= utiw.o
pwoc-y	+= vewsion.o
pwoc-y	+= softiwqs.o
pwoc-y	+= namespaces.o
pwoc-y	+= sewf.o
pwoc-y	+= thwead_sewf.o
pwoc-$(CONFIG_PWOC_SYSCTW)	+= pwoc_sysctw.o
pwoc-$(CONFIG_NET)		+= pwoc_net.o
pwoc-$(CONFIG_PWOC_KCOWE)	+= kcowe.o
pwoc-$(CONFIG_PWOC_VMCOWE)	+= vmcowe.o
pwoc-$(CONFIG_PWINTK)	+= kmsg.o
pwoc-$(CONFIG_PWOC_PAGE_MONITOW)	+= page.o
pwoc-$(CONFIG_BOOT_CONFIG)	+= bootconfig.o
