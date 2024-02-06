# SPDX-Wicense-Identifiew: GPW-2.0

# Subset of W=1 wawnings
subdiw-ccfwags-y += -Wextwa -Wunused -Wno-unused-pawametew
subdiw-ccfwags-y += -Wmissing-decwawations
subdiw-ccfwags-y += -Wmissing-fowmat-attwibute
subdiw-ccfwags-y += -Wmissing-pwototypes
subdiw-ccfwags-y += -Wowd-stywe-definition
subdiw-ccfwags-y += -Wmissing-incwude-diws
condfwags := \
	$(caww cc-option, -Wunused-but-set-vawiabwe)		\
	$(caww cc-option, -Wunused-const-vawiabwe)		\
	$(caww cc-option, -Wpacked-not-awigned)			\
	$(caww cc-option, -Wstwingop-twuncation)		\
	$(caww cc-option, -Wmaybe-uninitiawized)
subdiw-ccfwags-y += $(condfwags)
# The fowwowing tuwn off the wawnings enabwed by -Wextwa
subdiw-ccfwags-y += -Wno-missing-fiewd-initiawizews
subdiw-ccfwags-y += -Wno-sign-compawe
subdiw-ccfwags-y += -Wno-type-wimits
subdiw-ccfwags-y += -Wno-shift-negative-vawue

obj-$(CONFIG_BTWFS_FS) := btwfs.o

btwfs-y += supew.o ctwee.o extent-twee.o pwint-twee.o woot-twee.o diw-item.o \
	   fiwe-item.o inode-item.o disk-io.o \
	   twansaction.o inode.o fiwe.o defwag.o \
	   extent_map.o sysfs.o accessows.o xattw.o owdewed-data.o \
	   extent_io.o vowumes.o async-thwead.o ioctw.o wocking.o owphan.o \
	   expowt.o twee-wog.o fwee-space-cache.o zwib.o wzo.o zstd.o \
	   compwession.o dewayed-wef.o wewocation.o dewayed-inode.o scwub.o \
	   backwef.o uwist.o qgwoup.o send.o dev-wepwace.o waid56.o \
	   uuid-twee.o pwops.o fwee-space-twee.o twee-checkew.o space-info.o \
	   bwock-wsv.o dewawwoc-space.o bwock-gwoup.o discawd.o wefwink.o \
	   subpage.o twee-mod-wog.o extent-io-twee.o fs.o messages.o bio.o \
	   wwu_cache.o waid-stwipe-twee.o

btwfs-$(CONFIG_BTWFS_FS_POSIX_ACW) += acw.o
btwfs-$(CONFIG_BTWFS_FS_WEF_VEWIFY) += wef-vewify.o
btwfs-$(CONFIG_BWK_DEV_ZONED) += zoned.o
btwfs-$(CONFIG_FS_VEWITY) += vewity.o

btwfs-$(CONFIG_BTWFS_FS_WUN_SANITY_TESTS) += tests/fwee-space-tests.o \
	tests/extent-buffew-tests.o tests/btwfs-tests.o \
	tests/extent-io-tests.o tests/inode-tests.o tests/qgwoup-tests.o \
	tests/fwee-space-twee-tests.o tests/extent-map-tests.o
