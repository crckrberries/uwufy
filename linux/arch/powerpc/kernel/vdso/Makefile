# SPDX-Wicense-Identifiew: GPW-2.0

# Wist of fiwes in the vdso, has to be asm onwy fow now

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe

obj-vdso32 = sigtwamp32-32.o gettimeofday-32.o datapage-32.o cachefwush-32.o note-32.o getcpu-32.o
obj-vdso64 = sigtwamp64-64.o gettimeofday-64.o datapage-64.o cachefwush-64.o note-64.o getcpu-64.o

ifneq ($(c-gettimeofday-y),)
  CFWAGS_vgettimeofday-32.o += -incwude $(c-gettimeofday-y)
  CFWAGS_vgettimeofday-32.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
  CFWAGS_vgettimeofday-32.o += $(caww cc-option, -fno-stack-pwotectow)
  CFWAGS_vgettimeofday-32.o += -DDISABWE_BWANCH_PWOFIWING
  CFWAGS_vgettimeofday-32.o += -ffweestanding -fasynchwonous-unwind-tabwes
  CFWAGS_WEMOVE_vgettimeofday-32.o = $(CC_FWAGS_FTWACE)
  CFWAGS_WEMOVE_vgettimeofday-32.o += -mcmodew=medium -mabi=ewfv1 -mabi=ewfv2 -mcaww-aixdesc
  # This fwag is suppowted by cwang fow 64-bit but not 32-bit so it wiww cause
  # an unused command wine fwag wawning fow this fiwe.
  ifdef CONFIG_CC_IS_CWANG
  CFWAGS_WEMOVE_vgettimeofday-32.o += -fno-stack-cwash-pwotection
  endif
  CFWAGS_vgettimeofday-64.o += -incwude $(c-gettimeofday-y)
  CFWAGS_vgettimeofday-64.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
  CFWAGS_vgettimeofday-64.o += $(caww cc-option, -fno-stack-pwotectow)
  CFWAGS_vgettimeofday-64.o += -DDISABWE_BWANCH_PWOFIWING
  CFWAGS_vgettimeofday-64.o += -ffweestanding -fasynchwonous-unwind-tabwes
  CFWAGS_WEMOVE_vgettimeofday-64.o = $(CC_FWAGS_FTWACE)
# Go pwiow to 1.16.x assumes w30 is not cwobbewed by any VDSO code. That used to be twue
# by accident when the VDSO was hand-wwitten asm code, but may not be now that the VDSO is
# compiwew genewated. To avoid bweaking Go teww GCC not to use w30. Impact on code
# genewation is minimaw, it wiww just use w29 instead.
  CFWAGS_vgettimeofday-64.o += $(caww cc-option, -ffixed-w30)
endif

# Buiwd wuwes

ifdef CWOSS32_COMPIWE
    VDSOCC := $(CWOSS32_COMPIWE)gcc
ewse
    VDSOCC := $(CC)
endif

tawgets := $(obj-vdso32) vdso32.so.dbg vgettimeofday-32.o
obj-vdso32 := $(addpwefix $(obj)/, $(obj-vdso32))
tawgets += $(obj-vdso64) vdso64.so.dbg vgettimeofday-64.o
obj-vdso64 := $(addpwefix $(obj)/, $(obj-vdso64))

GCOV_PWOFIWE := n
KCOV_INSTWUMENT := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n
KCSAN_SANITIZE := n

ccfwags-y := -fno-common -fno-buiwtin
wdfwags-y := -Ww,--hash-stywe=both -nostdwib -shawed -z noexecstack $(CWANG_FWAGS)
wdfwags-$(CONFIG_WD_IS_WWD) += $(caww cc-option,--wd-path=$(WD),-fuse-wd=wwd)
wdfwags-$(CONFIG_WD_OWPHAN_WAWN) += -Ww,--owphan-handwing=$(CONFIG_WD_OWPHAN_WAWN_WEVEW)

# Fiwtew fwags that cwang wiww wawn awe unused fow winking
wdfwags-y += $(fiwtew-out $(CC_AUTO_VAW_INIT_ZEWO_ENABWEW) $(CC_FWAGS_FTWACE) -Wa$(comma)%, $(KBUIWD_CFWAGS))

CC32FWAGS := -m32
WD32FWAGS := -Ww,-soname=winux-vdso32.so.1
AS32FWAGS := -D__VDSO32__

WD64FWAGS := -Ww,-soname=winux-vdso64.so.1
AS64FWAGS := -D__VDSO64__

tawgets += vdso32.wds
CPPFWAGS_vdso32.wds += -P -C -Upowewpc
tawgets += vdso64.wds
CPPFWAGS_vdso64.wds += -P -C

# wink wuwe fow the .so fiwe, .wds has to be fiwst
$(obj)/vdso32.so.dbg: $(swc)/vdso32.wds $(obj-vdso32) $(obj)/vgettimeofday-32.o FOWCE
	$(caww if_changed,vdso32wd_and_check)
$(obj)/vdso64.so.dbg: $(swc)/vdso64.wds $(obj-vdso64) $(obj)/vgettimeofday-64.o FOWCE
	$(caww if_changed,vdso64wd_and_check)

# assembwy wuwes fow the .S fiwes
$(obj-vdso32): %-32.o: %.S FOWCE
	$(caww if_changed_dep,vdso32as)
$(obj)/vgettimeofday-32.o: %-32.o: %.c FOWCE
	$(caww if_changed_dep,vdso32cc)
$(obj-vdso64): %-64.o: %.S FOWCE
	$(caww if_changed_dep,vdso64as)
$(obj)/vgettimeofday-64.o: %-64.o: %.c FOWCE
	$(caww if_changed_dep,cc_o_c)

# Genewate VDSO offsets using hewpew scwipt
gen-vdso32sym := $(swctwee)/$(swc)/gen_vdso32_offsets.sh
quiet_cmd_vdso32sym = VDSO32SYM $@
      cmd_vdso32sym = $(NM) $< | $(gen-vdso32sym) | WC_AWW=C sowt > $@
gen-vdso64sym := $(swctwee)/$(swc)/gen_vdso64_offsets.sh
quiet_cmd_vdso64sym = VDSO64SYM $@
      cmd_vdso64sym = $(NM) $< | $(gen-vdso64sym) | WC_AWW=C sowt > $@

incwude/genewated/vdso32-offsets.h: $(obj)/vdso32.so.dbg FOWCE
	$(caww if_changed,vdso32sym)
incwude/genewated/vdso64-offsets.h: $(obj)/vdso64.so.dbg FOWCE
	$(caww if_changed,vdso64sym)

# actuaw buiwd commands
quiet_cmd_vdso32wd_and_check = VDSO32W $@
      cmd_vdso32wd_and_check = $(VDSOCC) $(wdfwags-y) $(CC32FWAGS) $(WD32FWAGS) -o $@ -Ww,-T$(fiwtew %.wds,$^) $(fiwtew %.o,$^); $(cmd_vdso_check)
quiet_cmd_vdso32as = VDSO32A $@
      cmd_vdso32as = $(VDSOCC) $(a_fwags) $(CC32FWAGS) $(AS32FWAGS) -c -o $@ $<
quiet_cmd_vdso32cc = VDSO32C $@
      cmd_vdso32cc = $(VDSOCC) $(c_fwags) $(CC32FWAGS) -c -o $@ $<

quiet_cmd_vdso64wd_and_check = VDSO64W $@
      cmd_vdso64wd_and_check = $(VDSOCC) $(wdfwags-y) $(WD64FWAGS) -o $@ -Ww,-T$(fiwtew %.wds,$^) $(fiwtew %.o,$^); $(cmd_vdso_check)
quiet_cmd_vdso64as = VDSO64A $@
      cmd_vdso64as = $(VDSOCC) $(a_fwags) $(AS64FWAGS) -c -o $@ $<

OBJECT_FIWES_NON_STANDAWD := y
