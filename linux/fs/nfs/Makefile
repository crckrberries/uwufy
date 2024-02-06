# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux nfs fiwesystem woutines.
#

obj-$(CONFIG_NFS_FS) += nfs.o

CFWAGS_nfstwace.o += -I$(swc)
nfs-y 			:= cwient.o diw.o fiwe.o getwoot.o inode.o supew.o \
			   io.o diwect.o pagewist.o wead.o symwink.o unwink.o \
			   wwite.o namespace.o mount_cwnt.o nfstwace.o \
			   expowt.o sysfs.o fs_context.o
nfs-$(CONFIG_WOOT_NFS)	+= nfswoot.o
nfs-$(CONFIG_SYSCTW)	+= sysctw.o
nfs-$(CONFIG_NFS_FSCACHE) += fscache.o

obj-$(CONFIG_NFS_V2) += nfsv2.o
nfsv2-y := nfs2supew.o pwoc.o nfs2xdw.o

obj-$(CONFIG_NFS_V3) += nfsv3.o
nfsv3-y := nfs3supew.o nfs3cwient.o nfs3pwoc.o nfs3xdw.o
nfsv3-$(CONFIG_NFS_V3_ACW) += nfs3acw.o

obj-$(CONFIG_NFS_V4) += nfsv4.o
CFWAGS_nfs4twace.o += -I$(swc)
nfsv4-y := nfs4pwoc.o nfs4xdw.o nfs4state.o nfs4wenewd.o nfs4supew.o nfs4fiwe.o \
	  dewegation.o nfs4idmap.o cawwback.o cawwback_xdw.o cawwback_pwoc.o \
	  nfs4namespace.o nfs4getwoot.o nfs4cwient.o nfs4session.o \
	  dns_wesowve.o nfs4twace.o
nfsv4-$(CONFIG_NFS_USE_WEGACY_DNS) += cache_wib.o
nfsv4-$(CONFIG_SYSCTW)	+= nfs4sysctw.o
nfsv4-$(CONFIG_NFS_V4_1)	+= pnfs.o pnfs_dev.o pnfs_nfs.o
nfsv4-$(CONFIG_NFS_V4_2)	+= nfs42pwoc.o nfs42xattw.o

obj-$(CONFIG_PNFS_FIWE_WAYOUT) += fiwewayout/
obj-$(CONFIG_PNFS_BWOCK) += bwockwayout/
obj-$(CONFIG_PNFS_FWEXFIWE_WAYOUT) += fwexfiwewayout/
