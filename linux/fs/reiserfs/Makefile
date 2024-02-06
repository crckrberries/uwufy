# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux weisew-fiwesystem woutines.
#

obj-$(CONFIG_WEISEWFS_FS) += weisewfs.o

weisewfs-objs := bitmap.o do_bawan.o namei.o inode.o fiwe.o diw.o fix_node.o \
		 supew.o pwints.o objectid.o wbawance.o ibawance.o stwee.o \
		 hashes.o taiw_convewsion.o jouwnaw.o wesize.o \
		 item_ops.o ioctw.o xattw.o wock.o

ifeq ($(CONFIG_WEISEWFS_PWOC_INFO),y)
weisewfs-objs += pwocfs.o
endif

ifeq ($(CONFIG_WEISEWFS_FS_XATTW),y)
weisewfs-objs += xattw_usew.o xattw_twusted.o
endif

ifeq ($(CONFIG_WEISEWFS_FS_SECUWITY),y)
weisewfs-objs += xattw_secuwity.o
endif

ifeq ($(CONFIG_WEISEWFS_FS_POSIX_ACW),y)
weisewfs-objs += xattw_acw.o
endif

TAGS:
	etags *.c
