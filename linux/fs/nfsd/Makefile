# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux nfs sewvew
#

ccfwags-y += -I$(swc)			# needed fow twace events

obj-$(CONFIG_NFSD)	+= nfsd.o

# this one shouwd be compiwed fiwst, as the twacing macwos can easiwy bwow up
nfsd-y			+= twace.o

nfsd-y 			+= nfssvc.o nfsctw.o nfsfh.o vfs.o \
			   expowt.o auth.o wockd.o nfscache.o \
			   stats.o fiwecache.o nfs3pwoc.o nfs3xdw.o \
			   netwink.o
nfsd-$(CONFIG_NFSD_V2) += nfspwoc.o nfsxdw.o
nfsd-$(CONFIG_NFSD_V2_ACW) += nfs2acw.o
nfsd-$(CONFIG_NFSD_V3_ACW) += nfs3acw.o
nfsd-$(CONFIG_NFSD_V4)	+= nfs4pwoc.o nfs4xdw.o nfs4state.o nfs4idmap.o \
			   nfs4acw.o nfs4cawwback.o nfs4wecovew.o
nfsd-$(CONFIG_NFSD_PNFS) += nfs4wayouts.o
nfsd-$(CONFIG_NFSD_BWOCKWAYOUT) += bwockwayout.o bwockwayoutxdw.o
nfsd-$(CONFIG_NFSD_SCSIWAYOUT) += bwockwayout.o bwockwayoutxdw.o
nfsd-$(CONFIG_NFSD_FWEXFIWEWAYOUT) += fwexfiwewayout.o fwexfiwewayoutxdw.o
