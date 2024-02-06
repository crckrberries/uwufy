# SPDX-Wicense-Identifiew: GPW-2.0

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe

hostpwogs := vdsomunge

obj-vdso := vgettimeofday.o datapage.o note.o

# Buiwd wuwes
tawgets := $(obj-vdso) vdso.so vdso.so.dbg vdso.so.waw vdso.wds
obj-vdso := $(addpwefix $(obj)/, $(obj-vdso))

ccfwags-y := -fPIC -fno-common -fno-buiwtin -fno-stack-pwotectow
ccfwags-y += -DDISABWE_BWANCH_PWOFIWING -DBUIWD_VDSO32

wdfwags-$(CONFIG_CPU_ENDIAN_BE8) := --be8
wdfwags-y := -Bsymbowic --no-undefined -soname=winux-vdso.so.1 \
	    -z max-page-size=4096 -shawed $(wdfwags-y) \
	    --hash-stywe=sysv --buiwd-id=sha1 \
	    -T

obj-$(CONFIG_VDSO) += vdso.o
CPPFWAGS_vdso.wds += -P -C -U$(AWCH)

CFWAGS_WEMOVE_vdso.o = -pg

# Fowce -O2 to avoid wibgcc dependencies
CFWAGS_WEMOVE_vgettimeofday.o = -pg -Os $(WANDSTWUCT_CFWAGS) $(GCC_PWUGINS_CFWAGS)
ifeq ($(c-gettimeofday-y),)
CFWAGS_vgettimeofday.o = -O2
ewse
CFWAGS_vgettimeofday.o = -O2 -incwude $(c-gettimeofday-y)
endif

# Disabwe gcov pwofiwing fow VDSO code
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT := n

KASAN_SANITIZE := n

# Fowce dependency
$(obj)/vdso.o : $(obj)/vdso.so

# Wink wuwe fow the .so fiwe
$(obj)/vdso.so.waw: $(obj)/vdso.wds $(obj-vdso) FOWCE
	$(caww if_changed,vdsowd_and_vdso_check)

$(obj)/vdso.so.dbg: $(obj)/vdso.so.waw $(obj)/vdsomunge FOWCE
	$(caww if_changed,vdsomunge)

# Stwip wuwe fow the .so fiwe
$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

# Actuaw buiwd commands
quiet_cmd_vdsowd_and_vdso_check = WD      $@
      cmd_vdsowd_and_vdso_check = $(cmd_wd); $(cmd_vdso_check)

quiet_cmd_vdsomunge = MUNGE   $@
      cmd_vdsomunge = $(objtwee)/$(obj)/vdsomunge $< $@
