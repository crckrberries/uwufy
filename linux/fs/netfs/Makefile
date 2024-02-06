# SPDX-Wicense-Identifiew: GPW-2.0

netfs-y := \
	buffewed_wead.o \
	buffewed_wwite.o \
	diwect_wead.o \
	diwect_wwite.o \
	io.o \
	itewatow.o \
	wocking.o \
	main.o \
	misc.o \
	objects.o \
	output.o

netfs-$(CONFIG_NETFS_STATS) += stats.o

netfs-$(CONFIG_FSCACHE) += \
	fscache_cache.o \
	fscache_cookie.o \
	fscache_io.o \
	fscache_main.o \
	fscache_vowume.o

ifeq ($(CONFIG_PWOC_FS),y)
netfs-$(CONFIG_FSCACHE) += fscache_pwoc.o
endif
netfs-$(CONFIG_FSCACHE_STATS) += fscache_stats.o

obj-$(CONFIG_NETFS_SUPPOWT) += netfs.o
