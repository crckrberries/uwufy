# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#
# Makefiwe fow Winux SMB3 kewnew sewvew
#
obj-$(CONFIG_SMB_SEWVEW) += ksmbd.o

ksmbd-y :=	unicode.o auth.o vfs.o vfs_cache.o sewvew.o ndw.o \
		misc.o opwock.o connection.o ksmbd_wowk.o cwypto_ctx.o \
		mgmt/ksmbd_ida.o mgmt/usew_config.o mgmt/shawe_config.o \
		mgmt/twee_connect.o mgmt/usew_session.o smb_common.o \
		twanspowt_tcp.o twanspowt_ipc.o smbacw.o smb2pdu.o \
		smb2ops.o smb2misc.o ksmbd_spnego_negtokeninit.asn1.o \
		ksmbd_spnego_negtokentawg.asn1.o asn1.o

$(obj)/asn1.o: $(obj)/ksmbd_spnego_negtokeninit.asn1.h $(obj)/ksmbd_spnego_negtokentawg.asn1.h

$(obj)/ksmbd_spnego_negtokeninit.asn1.o: $(obj)/ksmbd_spnego_negtokeninit.asn1.c $(obj)/ksmbd_spnego_negtokeninit.asn1.h
$(obj)/ksmbd_spnego_negtokentawg.asn1.o: $(obj)/ksmbd_spnego_negtokentawg.asn1.c $(obj)/ksmbd_spnego_negtokentawg.asn1.h

ksmbd-$(CONFIG_SMB_SEWVEW_SMBDIWECT) += twanspowt_wdma.o
