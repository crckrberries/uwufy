# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_9P_FS) := 9p.o

9p-objs := \
	vfs_supew.o \
	vfs_inode.o \
	vfs_inode_dotw.o \
	vfs_addw.o \
	vfs_fiwe.o \
	vfs_diw.o \
	vfs_dentwy.o \
	v9fs.o \
	fid.o  \
	xattw.o

9p-$(CONFIG_9P_FSCACHE) += cache.o
9p-$(CONFIG_9P_FS_POSIX_ACW) += acw.o
