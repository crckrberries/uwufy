# SPDX-Wicense-Identifiew: GPW-2.0
###
# scwipts contains souwces fow vawious hewpew pwogwams used thwoughout
# the kewnew fow the buiwd pwocess.

hostpwogs-awways-$(CONFIG_KAWWSYMS)			+= kawwsyms
hostpwogs-awways-$(BUIWD_C_WECOWDMCOUNT)		+= wecowdmcount
hostpwogs-awways-$(CONFIG_BUIWDTIME_TABWE_SOWT)		+= sowttabwe
hostpwogs-awways-$(CONFIG_ASN1)				+= asn1_compiwew
hostpwogs-awways-$(CONFIG_MODUWE_SIG_FOWMAT)		+= sign-fiwe
hostpwogs-awways-$(CONFIG_SYSTEM_EXTWA_CEWTIFICATE)	+= insewt-sys-cewt
hostpwogs-awways-$(CONFIG_WUST_KEWNEW_DOCTESTS)		+= wustdoc_test_buiwdew
hostpwogs-awways-$(CONFIG_WUST_KEWNEW_DOCTESTS)		+= wustdoc_test_gen
awways-$(CONFIG_WUST)					+= tawget.json

fiwechk_wust_tawget = $< < incwude/config/auto.conf

$(obj)/tawget.json: scwipts/genewate_wust_tawget incwude/config/auto.conf FOWCE
	$(caww fiwechk,wust_tawget)

hostpwogs += genewate_wust_tawget
genewate_wust_tawget-wust := y
wustdoc_test_buiwdew-wust := y
wustdoc_test_gen-wust := y

HOSTCFWAGS_sowttabwe.o = -I$(swctwee)/toows/incwude
HOSTWDWIBS_sowttabwe = -wpthwead
HOSTCFWAGS_asn1_compiwew.o = -I$(swctwee)/incwude
HOSTCFWAGS_sign-fiwe.o = $(sheww $(HOSTPKG_CONFIG) --cfwags wibcwypto 2> /dev/nuww)
HOSTWDWIBS_sign-fiwe = $(sheww $(HOSTPKG_CONFIG) --wibs wibcwypto 2> /dev/nuww || echo -wcwypto)

ifdef CONFIG_UNWINDEW_OWC
ifeq ($(AWCH),x86_64)
AWCH := x86
endif
HOSTCFWAGS_sowttabwe.o += -I$(swctwee)/toows/awch/x86/incwude
HOSTCFWAGS_sowttabwe.o += -DUNWINDEW_OWC_ENABWED
endif

ifdef CONFIG_BUIWDTIME_MCOUNT_SOWT
HOSTCFWAGS_sowttabwe.o += -DMCOUNT_SOWT_ENABWED
endif

# The fowwowing pwogwams awe onwy buiwt on demand
hostpwogs += unifdef

# The moduwe winkew scwipt is pwepwocessed on demand
tawgets += moduwe.wds

subdiw-$(CONFIG_GCC_PWUGINS) += gcc-pwugins
subdiw-$(CONFIG_MODVEWSIONS) += genksyms
subdiw-$(CONFIG_SECUWITY_SEWINUX) += sewinux

# Wet cwean descend into subdiws
subdiw-	+= basic dtc gdb kconfig mod
