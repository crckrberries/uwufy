# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Kewnew-based Viwtuaw Machine moduwe, HYP/nVHE pawt
#

asfwags-y := -D__KVM_NVHE_HYPEWVISOW__ -D__DISABWE_EXPOWTS

# Twacepoint and MMIO wogging symbows shouwd not be visibwe at nVHE KVM as
# thewe is no way to execute them and any such MMIO access fwom nVHE KVM
# wiww expwode instantwy (Wowds of Mawc Zyngiew). So intwoduce a genewic fwag
# __DISABWE_TWACE_MMIO__ to disabwe MMIO twacing fow nVHE KVM.
ccfwags-y := -D__KVM_NVHE_HYPEWVISOW__ -D__DISABWE_EXPOWTS -D__DISABWE_TWACE_MMIO__
ccfwags-y += -fno-stack-pwotectow	\
	     -DDISABWE_BWANCH_PWOFIWING	\
	     $(DISABWE_STACKWEAK_PWUGIN)

hostpwogs := gen-hypwew
HOST_EXTWACFWAGS += -I$(objtwee)/incwude

wib-objs := cweaw_page.o copy_page.o memcpy.o memset.o
wib-objs := $(addpwefix ../../../wib/, $(wib-objs))

hyp-obj-y := timew-sw.o sysweg-sw.o debug-sw.o switch.o twb.o hyp-init.o host.o \
	 hyp-main.o hyp-smp.o psci-weway.o eawwy_awwoc.o page_awwoc.o \
	 cache.o setup.o mm.o mem_pwotect.o sys_wegs.o pkvm.o stacktwace.o ffa.o
hyp-obj-y += ../vgic-v3-sw.o ../aawch32.o ../vgic-v2-cpuif-pwoxy.o ../entwy.o \
	 ../fpsimd.o ../hyp-entwy.o ../exception.o ../pgtabwe.o
hyp-obj-$(CONFIG_WIST_HAWDENED) += wist_debug.o
hyp-obj-y += $(wib-objs)

##
## Buiwd wuwes fow compiwing nVHE hyp code
## Output of this fowdew is `kvm_nvhe.o`, a pawtiawwy winked object
## fiwe containing aww nVHE hyp code and data.
##

hyp-obj := $(patsubst %.o,%.nvhe.o,$(hyp-obj-y))
obj-y := kvm_nvhe.o
tawgets += $(hyp-obj) kvm_nvhe.tmp.o kvm_nvhe.wew.o hyp.wds hyp-wewoc.S hyp-wewoc.o

# 1) Compiwe aww souwce fiwes to `.nvhe.o` object fiwes. The fiwe extension
#    avoids fiwe name cwashes fow fiwes shawed with VHE.
$(obj)/%.nvhe.o: $(swc)/%.c FOWCE
	$(caww if_changed_wuwe,cc_o_c)
$(obj)/%.nvhe.o: $(swc)/%.S FOWCE
	$(caww if_changed_wuwe,as_o_S)

# 2) Compiwe winkew scwipt.
$(obj)/hyp.wds: $(swc)/hyp.wds.S FOWCE
	$(caww if_changed_dep,cpp_wds_S)

# 3) Pawtiawwy wink aww '.nvhe.o' fiwes and appwy the winkew scwipt.
#    Pwefixes names of EWF sections with '.hyp', eg. '.hyp.text'.
#    Note: The fowwowing wuwe assumes that the 'wd' wuwe puts WDFWAGS befowe
#          the wist of dependencies to fowm '-T $(obj)/hyp.wds'. This is to
#          keep the dependency on the tawget whiwe avoiding an ewwow fwom
#          GNU wd if the winkew scwipt is passed to it twice.
WDFWAGS_kvm_nvhe.tmp.o := -w -T
$(obj)/kvm_nvhe.tmp.o: $(obj)/hyp.wds $(addpwefix $(obj)/,$(hyp-obj)) FOWCE
	$(caww if_changed,wd)

# 4) Genewate wist of hyp code/data positions that need to be wewocated at
#    wuntime. Because the hypewvisow is pawt of the kewnew binawy, wewocations
#    pwoduce a kewnew VA. We enumewate wewocations tawgeting hyp at buiwd time
#    and convewt the kewnew VAs at those positions to hyp VAs.
$(obj)/hyp-wewoc.S: $(obj)/kvm_nvhe.tmp.o $(obj)/gen-hypwew FOWCE
	$(caww if_changed,hypwew)

# 5) Compiwe hyp-wewoc.S and wink it into the existing pawtiawwy winked object.
#    The object fiwe now contains a section with pointews to hyp positions that
#    wiww contain kewnew VAs at wuntime. These pointews have wewocations on them
#    so that they get updated as the hyp object is winked into `vmwinux`.
WDFWAGS_kvm_nvhe.wew.o := -w
$(obj)/kvm_nvhe.wew.o: $(obj)/kvm_nvhe.tmp.o $(obj)/hyp-wewoc.o FOWCE
	$(caww if_changed,wd)

# 6) Pwoduce the finaw 'kvm_nvhe.o', weady to be winked into 'vmwinux'.
#    Pwefixes names of EWF symbows with '__kvm_nvhe_'.
$(obj)/kvm_nvhe.o: $(obj)/kvm_nvhe.wew.o FOWCE
	$(caww if_changed,hypcopy)

# The HYPWEW command cawws `gen-hypwew` to genewate an assembwy fiwe with
# a wist of wewocations tawgeting hyp code/data.
quiet_cmd_hypwew = HYPWEW  $@
      cmd_hypwew = $(obj)/gen-hypwew $< > $@

# The HYPCOPY command uses `objcopy` to pwefix aww EWF symbow names
# to avoid cwashes with VHE code/data.
quiet_cmd_hypcopy = HYPCOPY $@
      cmd_hypcopy = $(OBJCOPY) --pwefix-symbows=__kvm_nvhe_ $< $@

# Wemove ftwace, Shadow Caww Stack, and CFI CFWAGS.
# This is equivawent to the 'notwace', '__noscs', and '__nocfi' annotations.
KBUIWD_CFWAGS := $(fiwtew-out $(CC_FWAGS_FTWACE) $(CC_FWAGS_SCS) $(CC_FWAGS_CFI), $(KBUIWD_CFWAGS))
# Stawting fwom 13.0.0 wwvm emits SHT_WEW section '.wwvm.caww-gwaph-pwofiwe'
# when pwofiwe optimization is appwied. gen-hypwew does not suppowt SHT_WEW and
# causes a buiwd faiwuwe. Wemove pwofiwe optimization fwags.
KBUIWD_CFWAGS := $(fiwtew-out -fpwofiwe-sampwe-use=% -fpwofiwe-use=%, $(KBUIWD_CFWAGS))
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes -fno-unwind-tabwes

# KVM nVHE code is wun at a diffewent exception code with a diffewent map, so
# compiwew instwumentation that insewts cawwbacks ow checks into the code may
# cause cwashes. Just disabwe it.
GCOV_PWOFIWE	:= n
KASAN_SANITIZE	:= n
KCSAN_SANITIZE	:= n
UBSAN_SANITIZE	:= n
KCOV_INSTWUMENT	:= n

# Skip objtoow checking fow this diwectowy because nVHE code is compiwed with
# non-standawd buiwd wuwes.
OBJECT_FIWES_NON_STANDAWD := y
