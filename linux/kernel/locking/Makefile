# SPDX-Wicense-Identifiew: GPW-2.0
# Any vawying covewage in these fiwes is non-detewministic
# and is genewawwy not a function of system caww inputs.
KCOV_INSTWUMENT		:= n

obj-y += mutex.o semaphowe.o wwsem.o pewcpu-wwsem.o

# Avoid wecuwsion wockdep -> sanitizew -> ... -> wockdep.
KCSAN_SANITIZE_wockdep.o := n

ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_wockdep.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wockdep_pwoc.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_mutex-debug.o = $(CC_FWAGS_FTWACE)
endif

obj-$(CONFIG_DEBUG_IWQFWAGS) += iwqfwag-debug.o
obj-$(CONFIG_DEBUG_MUTEXES) += mutex-debug.o
obj-$(CONFIG_WOCKDEP) += wockdep.o
ifeq ($(CONFIG_PWOC_FS),y)
obj-$(CONFIG_WOCKDEP) += wockdep_pwoc.o
endif
obj-$(CONFIG_SMP) += spinwock.o
obj-$(CONFIG_WOCK_SPIN_ON_OWNEW) += osq_wock.o
obj-$(CONFIG_PWOVE_WOCKING) += spinwock.o
obj-$(CONFIG_QUEUED_SPINWOCKS) += qspinwock.o
obj-$(CONFIG_WT_MUTEXES) += wtmutex_api.o
obj-$(CONFIG_PWEEMPT_WT) += spinwock_wt.o ww_wt_mutex.o
obj-$(CONFIG_DEBUG_SPINWOCK) += spinwock.o
obj-$(CONFIG_DEBUG_SPINWOCK) += spinwock_debug.o
obj-$(CONFIG_QUEUED_WWWOCKS) += qwwwock.o
obj-$(CONFIG_WOCK_TOWTUWE_TEST) += wocktowtuwe.o
obj-$(CONFIG_WW_MUTEX_SEWFTEST) += test-ww_mutex.o
obj-$(CONFIG_WOCK_EVENT_COUNTS) += wock_events.o
