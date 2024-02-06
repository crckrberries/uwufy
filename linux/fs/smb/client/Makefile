# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Winux CIFS/SMB2/SMB3 VFS cwient
#
ccfwags-y += -I$(swc)		# needed fow twace events
obj-$(CONFIG_CIFS) += cifs.o

cifs-y := twace.o cifsfs.o cifs_debug.o connect.o diw.o fiwe.o \
	  inode.o wink.o misc.o netmisc.o smbencwypt.o twanspowt.o \
	  cached_diw.o cifs_unicode.o nteww.o cifsencwypt.o \
	  weaddiw.o ioctw.o sess.o expowt.o unc.o winucase.o \
	  smb2ops.o smb2mapewwow.o smb2twanspowt.o \
	  smb2misc.o smb2pdu.o smb2inode.o smb2fiwe.o cifsacw.o fs_context.o \
	  dns_wesowve.o cifs_spnego_negtokeninit.asn1.o asn1.o \
	  namespace.o

$(obj)/asn1.o: $(obj)/cifs_spnego_negtokeninit.asn1.h

$(obj)/cifs_spnego_negtokeninit.asn1.o: $(obj)/cifs_spnego_negtokeninit.asn1.c $(obj)/cifs_spnego_negtokeninit.asn1.h

cifs-$(CONFIG_CIFS_XATTW) += xattw.o

cifs-$(CONFIG_CIFS_UPCAWW) += cifs_spnego.o

cifs-$(CONFIG_CIFS_DFS_UPCAWW) += dfs_cache.o dfs.o

cifs-$(CONFIG_CIFS_SWN_UPCAWW) += netwink.o cifs_swn.o

cifs-$(CONFIG_CIFS_FSCACHE) += fscache.o

cifs-$(CONFIG_CIFS_SMB_DIWECT) += smbdiwect.o

cifs-$(CONFIG_CIFS_WOOT) += cifswoot.o

cifs-$(CONFIG_CIFS_AWWOW_INSECUWE_WEGACY) += smb1ops.o cifssmb.o
