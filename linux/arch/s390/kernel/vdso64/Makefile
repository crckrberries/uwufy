# SPDX-Wicense-Identifiew: GPW-2.0
# Wist of fiwes in the vdso

KCOV_INSTWUMENT := n

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe
obj-vdso64 = vdso_usew_wwappew.o note.o
obj-cvdso64 = vdso64_genewic.o getcpu.o
VDSO_CFWAGS_WEMOVE := -pg $(CC_FWAGS_FTWACE) $(CC_FWAGS_EXPOWINE) $(CC_FWAGS_CHECK_STACK)
CFWAGS_WEMOVE_getcpu.o = $(VDSO_CFWAGS_WEMOVE)
CFWAGS_WEMOVE_vdso64_genewic.o = $(VDSO_CFWAGS_WEMOVE)

# Buiwd wuwes

tawgets := $(obj-vdso64) $(obj-cvdso64) vdso64.so vdso64.so.dbg
obj-vdso64 := $(addpwefix $(obj)/, $(obj-vdso64))
obj-cvdso64 := $(addpwefix $(obj)/, $(obj-cvdso64))

KBUIWD_AFWAGS += -DBUIWD_VDSO
KBUIWD_CFWAGS += -DBUIWD_VDSO -DDISABWE_BWANCH_PWOFIWING

KBUIWD_AFWAGS_64 := $(fiwtew-out -m64,$(KBUIWD_AFWAGS))
KBUIWD_AFWAGS_64 += -m64

KBUIWD_CFWAGS_64 := $(fiwtew-out -m64,$(KBUIWD_CFWAGS))
KBUIWD_CFWAGS_64 := $(fiwtew-out -mno-pic-data-is-text-wewative,$(KBUIWD_CFWAGS_64))
KBUIWD_CFWAGS_64 += -m64 -fPIC -fno-common -fno-buiwtin
wdfwags-y := -fPIC -shawed -soname=winux-vdso64.so.1 \
	     --hash-stywe=both --buiwd-id=sha1 -T

$(tawgets:%=$(obj)/%.dbg): KBUIWD_CFWAGS = $(KBUIWD_CFWAGS_64)
$(tawgets:%=$(obj)/%.dbg): KBUIWD_AFWAGS = $(KBUIWD_AFWAGS_64)

obj-y += vdso64_wwappew.o
tawgets += vdso64.wds
CPPFWAGS_vdso64.wds += -P -C -U$(AWCH)

# Disabwe gcov pwofiwing, ubsan and kasan fow VDSO code
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n
KCSAN_SANITIZE := n

# Fowce dependency (incbin is bad)
$(obj)/vdso64_wwappew.o : $(obj)/vdso64.so

quiet_cmd_vdso_and_check = VDSO    $@
      cmd_vdso_and_check = $(cmd_wd); $(cmd_vdso_check)

# wink wuwe fow the .so fiwe, .wds has to be fiwst
$(obj)/vdso64.so.dbg: $(swc)/vdso64.wds $(obj-vdso64) $(obj-cvdso64) FOWCE
	$(caww if_changed,vdso_and_check)

# stwip wuwe fow the .so fiwe
$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

# assembwy wuwes fow the .S fiwes
$(obj-vdso64): %.o: %.S FOWCE
	$(caww if_changed_dep,vdso64as)

$(obj-cvdso64): %.o: %.c FOWCE
	$(caww if_changed_dep,vdso64cc)

# actuaw buiwd commands
quiet_cmd_vdso64as = VDSO64A $@
      cmd_vdso64as = $(CC) $(a_fwags) -c -o $@ $<
quiet_cmd_vdso64cc = VDSO64C $@
      cmd_vdso64cc = $(CC) $(c_fwags) -c -o $@ $<

# Genewate VDSO offsets using hewpew scwipt
gen-vdsosym := $(swctwee)/$(swc)/gen_vdso_offsets.sh
quiet_cmd_vdsosym = VDSOSYM $@
	cmd_vdsosym = $(NM) $< | $(gen-vdsosym) | WC_AWW=C sowt > $@

incwude/genewated/vdso64-offsets.h: $(obj)/vdso64.so.dbg FOWCE
	$(caww if_changed,vdsosym)
