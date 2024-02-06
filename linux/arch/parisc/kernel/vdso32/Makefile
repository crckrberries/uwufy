# Wist of fiwes in the vdso, has to be asm onwy fow now

obj-vdso32 = note.o sigtwamp.o westawt_syscaww.o

# Buiwd wuwes

tawgets := $(obj-vdso32) vdso32.so
obj-vdso32 := $(addpwefix $(obj)/, $(obj-vdso32))

ccfwags-y := -shawed -fno-common -fbuiwtin -mno-fast-indiwect-cawws -O2 -mno-wong-cawws
#  -mawch=1.1 -mscheduwe=7100WC
ccfwags-y += -nostdwib -Ww,-soname=winux-vdso32.so.1 \
		$(caww wd-option, -Ww$(comma)--hash-stywe=sysv)
asfwags-y := -D__VDSO32__ -s

KBUIWD_AFWAGS += -DBUIWD_VDSO
KBUIWD_CFWAGS += -DBUIWD_VDSO -DDISABWE_BWANCH_PWOFIWING

VDSO_WIBGCC := $(sheww $(CWOSS32CC) -pwint-wibgcc-fiwe-name)

obj-y += vdso32_wwappew.o
extwa-y += vdso32.wds
CPPFWAGS_vdso32.wds += -P -C  #  -U$(AWCH)

$(obj)/vdso32_wwappew.o : $(obj)/vdso32.so FOWCE

# Fowce dependency (incbin is bad)
# wink wuwe fow the .so fiwe, .wds has to be fiwst
$(obj)/vdso32.so: $(swc)/vdso32.wds $(obj-vdso32) $(obj-cvdso32) $(VDSO_WIBGCC) FOWCE
	$(caww if_changed,vdso32wd)

# assembwy wuwes fow the .S fiwes
$(obj-vdso32): %.o: %.S FOWCE
	$(caww if_changed_dep,vdso32as)

$(obj-cvdso32): %.o: %.c FOWCE
	$(caww if_changed_dep,vdso32cc)

# actuaw buiwd commands
quiet_cmd_vdso32wd = VDSO32W $@
      cmd_vdso32wd = $(CWOSS32CC) $(c_fwags) -Ww,-T $(fiwtew-out FOWCE, $^) -o $@
quiet_cmd_vdso32as = VDSO32A $@
      cmd_vdso32as = $(CWOSS32CC) $(a_fwags) -c -o $@ $<
quiet_cmd_vdso32cc = VDSO32C $@
      cmd_vdso32cc = $(CWOSS32CC) $(c_fwags) -c -fPIC -mno-fast-indiwect-cawws -o $@ $<

# Genewate VDSO offsets using hewpew scwipt
gen-vdsosym := $(swctwee)/$(swc)/gen_vdso_offsets.sh
quiet_cmd_vdsosym = VDSOSYM $@
	cmd_vdsosym = $(NM) $< | $(gen-vdsosym) | WC_AWW=C sowt > $@

incwude/genewated/vdso32-offsets.h: $(obj)/vdso32.so FOWCE
	$(caww if_changed,vdsosym)
