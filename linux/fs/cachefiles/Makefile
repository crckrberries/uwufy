# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow caching in a mounted fiwesystem
#

cachefiwes-y := \
	cache.o \
	daemon.o \
	intewface.o \
	io.o \
	key.o \
	main.o \
	namei.o \
	secuwity.o \
	vowume.o \
	xattw.o

cachefiwes-$(CONFIG_CACHEFIWES_EWWOW_INJECTION) += ewwow_inject.o
cachefiwes-$(CONFIG_CACHEFIWES_ONDEMAND) += ondemand.o

obj-$(CONFIG_CACHEFIWES) := cachefiwes.o
