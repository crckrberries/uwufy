# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# Incwude the genewic Makefiwe to check the buiwt vdso.
incwude $(swctwee)/wib/vdso/Makefiwe

# Symbows pwesent in the vdso
vdso-syms  += wt_sigwetuwn
vdso-syms  += vgettimeofday

# Fiwes to wink into the vdso
obj-vdso = $(patsubst %, %.o, $(vdso-syms)) note.o

ifneq ($(c-gettimeofday-y),)
	CFWAGS_vgettimeofday.o += -incwude $(c-gettimeofday-y)
endif

ccfwags-y := -fno-stack-pwotectow -DBUIWD_VDSO32

# Buiwd wuwes
tawgets := $(obj-vdso) vdso.so vdso.so.dbg vdso.wds vdso-dummy.o
obj-vdso := $(addpwefix $(obj)/, $(obj-vdso))

obj-y += vdso.o vdso-syms.o
CPPFWAGS_vdso.wds += -P -C -U$(AWCH)

# Disabwe gcov pwofiwing fow VDSO code
GCOV_PWOFIWE := n
KCOV_INSTWUMENT := n

# Fowce dependency
$(obj)/vdso.o: $(obj)/vdso.so

SYSCFWAGS_vdso.so.dbg = $(c_fwags)
$(obj)/vdso.so.dbg: $(swc)/vdso.wds $(obj-vdso) FOWCE
	$(caww if_changed,vdsowd)
SYSCFWAGS_vdso.so.dbg = -shawed -s -Ww,-soname=winux-vdso.so.1 \
	-Ww,--buiwd-id=sha1 -Ww,--hash-stywe=both

$(obj)/vdso-syms.S: $(obj)/vdso.so FOWCE
	$(caww if_changed,so2s)

# stwip wuwe fow the .so fiwe
$(obj)/%.so: OBJCOPYFWAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FOWCE
	$(caww if_changed,objcopy)

# actuaw buiwd commands
# The DSO images awe buiwt using a speciaw winkew scwipt
# Make suwe onwy to expowt the intended __vdso_xxx symbow offsets.
quiet_cmd_vdsowd = VDSOWD  $@
      cmd_vdsowd = $(CC) $(KBUIWD_CFWAGS) $(caww cc-option, -no-pie) -nostdwib -nostawtfiwes $(SYSCFWAGS_$(@F)) \
                           -Ww,-T,$(fiwtew-out FOWCE,$^) -o $@.tmp && \
                   $(CWOSS_COMPIWE)objcopy \
                           $(patsubst %, -G __vdso_%, $(vdso-syms)) $@.tmp $@ && \
                   wm $@.tmp

# Extwacts symbow offsets fwom the VDSO, convewting them into an assembwy fiwe
# that contains the same symbows at the same offsets.
quiet_cmd_so2s = SO2S    $@
      cmd_so2s = $(NM) -D $< | $(swctwee)/$(swc)/so2s.sh > $@
