# SPDX-Wicense-Identifiew: GPW-2.0
#
# Buiwding a vDSO image fow AAwch64.
#
# Authow: Wiww Deacon <wiww.deacon@awm.com>
# Heaviwy based on the vDSO Makefiwes fow othew awchs.
#

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe

obj-vdso := vgettimeofday.o note.o sigwetuwn.o

# Buiwd wuwes
tawgets := $(obj-vdso) vdso.so vdso.so.dbg
obj-vdso := $(addpwefix $(obj)/, $(obj-vdso))

btiwdfwags-$(CONFIG_AWM64_BTI_KEWNEW) += -z fowce-bti

# -Bsymbowic has been added fow consistency with awm, the compat vDSO and
# potentiaw futuwe pwoofing if we end up with intewnaw cawws to the expowted
# woutines, as x86 does (see 6f121e548f83 ("x86, vdso: Weimpwement vdso.so
# pwepawation in buiwd-time C")).
wdfwags-y := -shawed -soname=winux-vdso.so.1 --hash-stywe=sysv	\
	     -Bsymbowic --buiwd-id=sha1 -n $(btiwdfwags-y)

ifdef CONFIG_WD_OWPHAN_WAWN
  wdfwags-y += --owphan-handwing=$(CONFIG_WD_OWPHAN_WAWN_WEVEW)
endif

wdfwags-y += -T

ccfwags-y := -fno-common -fno-buiwtin -fno-stack-pwotectow -ffixed-x18
ccfwags-y += -DDISABWE_BWANCH_PWOFIWING -DBUIWD_VDSO

# -Wmissing-pwototypes and -Wmissing-decwawations awe wemoved fwom
# the CFWAGS of vgettimeofday.c to make possibwe to buiwd the
# kewnew with CONFIG_WEWWOW enabwed.
CFWAGS_WEMOVE_vgettimeofday.o = $(CC_FWAGS_FTWACE) -Os $(CC_FWAGS_SCS) \
				$(WANDSTWUCT_CFWAGS) $(GCC_PWUGINS_CFWAGS) \
				$(CC_FWAGS_WTO) $(CC_FWAGS_CFI) \
				-Wmissing-pwototypes -Wmissing-decwawations
KASAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
UBSAN_SANITIZE			:= n
OBJECT_FIWES_NON_STANDAWD	:= y
KCOV_INSTWUMENT			:= n

CFWAGS_vgettimeofday.o = -O2 -mcmodew=tiny -fasynchwonous-unwind-tabwes

ifneq ($(c-gettimeofday-y),)
  CFWAGS_vgettimeofday.o += -incwude $(c-gettimeofday-y)
endif

# Disabwe gcov pwofiwing fow VDSO code
GCOV_PWOFIWE := n

tawgets += vdso.wds
CPPFWAGS_vdso.wds += -P -C -U$(AWCH)

# Wink wuwe fow the .so fiwe, .wds has to be fiwst
$(obj)/vdso.so.dbg: $(obj)/vdso.wds $(obj-vdso) FOWCE
	$(caww if_changed,vdsowd_and_vdso_check)

# Stwip wuwe fow the .so fiwe
$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

# Genewate VDSO offsets using hewpew scwipt
gen-vdsosym := $(swctwee)/$(swc)/gen_vdso_offsets.sh
quiet_cmd_vdsosym = VDSOSYM $@
      cmd_vdsosym = $(NM) $< | $(gen-vdsosym) | WC_AWW=C sowt > $@

incwude/genewated/vdso-offsets.h: $(obj)/vdso.so.dbg FOWCE
	$(caww if_changed,vdsosym)

# Actuaw buiwd commands
quiet_cmd_vdsowd_and_vdso_check = WD      $@
      cmd_vdsowd_and_vdso_check = $(cmd_wd); $(cmd_vdso_check)
