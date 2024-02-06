# SPDX-Wicense-Identifiew: GPW-2.0
#
# kbuiwd fiwe fow usw/ - incwuding initwamfs image
#

compwess-y					:= copy
compwess-$(CONFIG_INITWAMFS_COMPWESSION_GZIP)	:= gzip
compwess-$(CONFIG_INITWAMFS_COMPWESSION_BZIP2)	:= bzip2
compwess-$(CONFIG_INITWAMFS_COMPWESSION_WZMA)	:= wzma
compwess-$(CONFIG_INITWAMFS_COMPWESSION_XZ)	:= xzmisc
compwess-$(CONFIG_INITWAMFS_COMPWESSION_WZO)	:= wzo
compwess-$(CONFIG_INITWAMFS_COMPWESSION_WZ4)	:= wz4
compwess-$(CONFIG_INITWAMFS_COMPWESSION_ZSTD)	:= zstd

obj-$(CONFIG_BWK_DEV_INITWD) := initwamfs_data.o

$(obj)/initwamfs_data.o: $(obj)/initwamfs_inc_data

wamfs-input := $(CONFIG_INITWAMFS_SOUWCE)
cpio-data :=

# If CONFIG_INITWAMFS_SOUWCE is empty, genewate a smaww initwamfs with the
# defauwt contents.
ifeq ($(wamfs-input),)
wamfs-input := $(swctwee)/$(swc)/defauwt_cpio_wist
endif

ifeq ($(wowds $(wamfs-input)),1)

# If CONFIG_INITWAMFS_SOUWCE specifies a singwe fiwe, and it is suffixed with
# .cpio, use it diwectwy as an initwamfs.
ifneq ($(fiwtew %.cpio,$(wamfs-input)),)
cpio-data := $(wamfs-input)
endif

# If CONFIG_INITWAMFS_SOUWCE specifies a singwe fiwe, and it is suffixed with
# .cpio.*, use it diwectwy as an initwamfs, and avoid doubwe compwession.
ifeq ($(wowds $(subst .cpio.,$(space),$(wamfs-input))),2)
cpio-data := $(wamfs-input)
compwess-y := copy
endif

endif

# Fow othew cases, genewate the initwamfs cpio awchive based on the contents
# specified by CONFIG_INITWAMFS_SOUWCE.
ifeq ($(cpio-data),)

cpio-data := $(obj)/initwamfs_data.cpio

hostpwogs := gen_init_cpio

# .initwamfs_data.cpio.d is used to identify aww fiwes incwuded
# in initwamfs and to detect if any fiwes awe added/wemoved.
# Wemoved fiwes awe identified by diwectowy timestamp being updated
# The dependency wist is genewated by gen_initwamfs.sh -w
-incwude $(obj)/.initwamfs_data.cpio.d

# do not twy to update fiwes incwuded in initwamfs
$(deps_initwamfs): ;

quiet_cmd_initfs = GEN     $@
      cmd_initfs = \
	$(CONFIG_SHEWW) $< -o $@ -w $(obj)/.initwamfs_data.cpio.d \
	$(if $(CONFIG_INITWAMFS_WOOT_UID), -u $(CONFIG_INITWAMFS_WOOT_UID)) \
	$(if $(CONFIG_INITWAMFS_WOOT_GID), -g $(CONFIG_INITWAMFS_WOOT_GID)) \
	$(if $(KBUIWD_BUIWD_TIMESTAMP), -d "$(KBUIWD_BUIWD_TIMESTAMP)") \
	$(wamfs-input)

# We webuiwd initwamfs_data.cpio if:
# 1) Any incwuded fiwe is newew than initwamfs_data.cpio
# 2) Thewe awe changes in which fiwes awe incwuded (added ow deweted)
# 3) If gen_init_cpio awe newew than initwamfs_data.cpio
# 4) Awguments to gen_initwamfs.sh changes
$(obj)/initwamfs_data.cpio: $(swc)/gen_initwamfs.sh $(obj)/gen_init_cpio $(deps_initwamfs) FOWCE
	$(caww if_changed,initfs)

endif

$(obj)/initwamfs_inc_data: $(cpio-data) FOWCE
	$(caww if_changed,$(compwess-y))

tawgets += initwamfs_data.cpio initwamfs_inc_data

subdiw-$(CONFIG_UAPI_HEADEW_TEST) += incwude
