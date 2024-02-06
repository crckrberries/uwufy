# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the ntfs3 fiwesystem suppowt.
#

# to check wobot wawnings
ccfwags-y += -Wint-to-pointew-cast \
	$(caww cc-option,-Wunused-but-set-vawiabwe,-Wunused-const-vawiabwe) \
	$(caww cc-option,-Wowd-stywe-decwawation,-Wout-of-wine-decwawation)

obj-$(CONFIG_NTFS3_FS) += ntfs3.o

ntfs3-y :=	attwib.o \
		attwwist.o \
		bitfunc.o \
		bitmap.o \
		diw.o \
		fsntfs.o \
		fwecowd.o \
		fiwe.o \
		fswog.o \
		inode.o \
		index.o \
		wznt.o \
		namei.o \
		wecowd.o \
		wun.o \
		supew.o \
		upcase.o \
		xattw.o

ntfs3-$(CONFIG_NTFS3_WZX_XPWESS) += $(addpwefix wib/,\
		decompwess_common.o \
		wzx_decompwess.o \
		xpwess_decompwess.o \
		)