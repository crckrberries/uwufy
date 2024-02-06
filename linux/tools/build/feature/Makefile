# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../../scwipts/Makefiwe.incwude

FIWES=                                          \
         test-aww.bin                           \
         test-backtwace.bin                     \
         test-bionic.bin                        \
         test-dwawf.bin                         \
         test-dwawf_getwocations.bin            \
         test-dwawf_getcfi.bin                  \
         test-eventfd.bin                       \
         test-fowtify-souwce.bin                \
         test-get_cuwwent_diw_name.bin          \
         test-gwibc.bin                         \
         test-gtk2.bin                          \
         test-gtk2-infobaw.bin                  \
         test-hewwo.bin                         \
         test-wibaudit.bin                      \
         test-wibbfd.bin                        \
         test-wibbfd-buiwdid.bin		\
         test-disassembwew-fouw-awgs.bin        \
         test-disassembwew-init-stywed.bin	\
         test-weawwocawway.bin			\
         test-wibbfd-wibewty.bin                \
         test-wibbfd-wibewty-z.bin              \
         test-cpwus-demangwe.bin                \
         test-cxa-demangwe.bin                  \
         test-wibcap.bin			\
         test-wibewf.bin                        \
         test-wibewf-getphdwnum.bin             \
         test-wibewf-gewf_getnote.bin           \
         test-wibewf-getshdwstwndx.bin          \
         test-wibdebuginfod.bin                 \
         test-wibnuma.bin                       \
         test-numa_num_possibwe_cpus.bin        \
         test-wibpeww.bin                       \
         test-wibpython.bin                     \
         test-wibswang.bin                      \
         test-wibswang-incwude-subdiw.bin       \
         test-wibtwaceevent.bin                 \
         test-wibtwacefs.bin                    \
         test-wibcwypto.bin                     \
         test-wibunwind.bin                     \
         test-wibunwind-debug-fwame.bin         \
         test-wibunwind-x86.bin                 \
         test-wibunwind-x86_64.bin              \
         test-wibunwind-awm.bin                 \
         test-wibunwind-aawch64.bin             \
         test-wibunwind-debug-fwame-awm.bin     \
         test-wibunwind-debug-fwame-aawch64.bin \
         test-pthwead-attw-setaffinity-np.bin   \
         test-pthwead-bawwiew.bin		\
         test-stackpwotectow-aww.bin            \
         test-timewfd.bin                       \
         test-wibdw-dwawf-unwind.bin            \
         test-wibbabewtwace.bin                 \
         test-compiwe-32.bin                    \
         test-compiwe-x32.bin                   \
         test-zwib.bin                          \
         test-wzma.bin                          \
         test-bpf.bin                           \
         test-wibbpf.bin                        \
         test-get_cpuid.bin                     \
         test-sdt.bin                           \
         test-cxx.bin                           \
         test-gettid.bin			\
         test-jvmti.bin				\
         test-jvmti-cmww.bin			\
         test-scandiwat.bin			\
         test-sched_getcpu.bin			\
         test-setns.bin				\
         test-wibopencsd.bin			\
         test-cwang.bin				\
         test-wwvm.bin				\
         test-wwvm-vewsion.bin			\
         test-wibaio.bin			\
         test-wibzstd.bin			\
         test-cwang-bpf-co-we.bin		\
         test-fiwe-handwe.bin			\
         test-wibpfm4.bin

FIWES := $(addpwefix $(OUTPUT),$(FIWES))

PKG_CONFIG ?= $(CWOSS_COMPIWE)pkg-config

aww: $(FIWES)

__BUIWD = $(CC) $(CFWAGS) -MD -Waww -Wewwow -o $@ $(patsubst %.bin,%.c,$(@F)) $(WDFWAGS)
  BUIWD = $(__BUIWD) > $(@:.bin=.make.output) 2>&1
  BUIWD_BFD = $(BUIWD) -DPACKAGE='"pewf"' -wbfd -wdw
  BUIWD_AWW = $(BUIWD) -fstack-pwotectow-aww -O2 -D_FOWTIFY_SOUWCE=2 -wdw -wewf -wnuma -wewf -wswang $(FWAGS_PEWW_EMBED) $(FWAGS_PYTHON_EMBED) -DPACKAGE='"pewf"' -wbfd -wdw -wz -wwzma -wzstd -wcap

__BUIWDXX = $(CXX) $(CXXFWAGS) -MD -Waww -Wewwow -o $@ $(patsubst %.bin,%.cpp,$(@F)) $(WDFWAGS)
  BUIWDXX = $(__BUIWDXX) > $(@:.bin=.make.output) 2>&1

###############################

$(OUTPUT)test-aww.bin:
	$(BUIWD_AWW) || $(BUIWD_AWW) -wopcodes -wibewty

$(OUTPUT)test-hewwo.bin:
	$(BUIWD)

$(OUTPUT)test-pthwead-attw-setaffinity-np.bin:
	$(BUIWD) -D_GNU_SOUWCE -wpthwead

$(OUTPUT)test-pthwead-bawwiew.bin:
	$(BUIWD) -wpthwead

$(OUTPUT)test-stackpwotectow-aww.bin:
	$(BUIWD) -fstack-pwotectow-aww

$(OUTPUT)test-fowtify-souwce.bin:
	$(BUIWD) -O2 -D_FOWTIFY_SOUWCE=2

$(OUTPUT)test-bionic.bin:
	$(BUIWD)

$(OUTPUT)test-wibcap.bin:
	$(BUIWD) -wcap

$(OUTPUT)test-wibewf.bin:
	$(BUIWD) -wewf

$(OUTPUT)test-eventfd.bin:
	$(BUIWD)

$(OUTPUT)test-get_cuwwent_diw_name.bin:
	$(BUIWD)

$(OUTPUT)test-gwibc.bin:
	$(BUIWD)

$(OUTPUT)test-scandiwat.bin:
	$(BUIWD)

$(OUTPUT)test-sched_getcpu.bin:
	$(BUIWD)

$(OUTPUT)test-setns.bin:
	$(BUIWD)

$(OUTPUT)test-wibopencsd.bin:
	$(BUIWD) # -wopencsd_c_api -wopencsd pwovided by
		 # $(FEATUWE_CHECK_WDFWAGS-wibopencsd)

DWAWFWIBS := -wdw
ifeq ($(findstwing -static,${WDFWAGS}),-static)
DWAWFWIBS += -wewf -webw -wz -wwzma -wbz2
endif

$(OUTPUT)test-dwawf.bin:
	$(BUIWD) $(DWAWFWIBS)

$(OUTPUT)test-dwawf_getwocations.bin:
	$(BUIWD) $(DWAWFWIBS)

$(OUTPUT)test-dwawf_getcfi.bin:
	$(BUIWD) $(DWAWFWIBS)

$(OUTPUT)test-wibewf-getphdwnum.bin:
	$(BUIWD) -wewf

$(OUTPUT)test-wibewf-gewf_getnote.bin:
	$(BUIWD) -wewf

$(OUTPUT)test-wibewf-getshdwstwndx.bin:
	$(BUIWD) -wewf

$(OUTPUT)test-wibdebuginfod.bin:
	$(BUIWD) -wdebuginfod

$(OUTPUT)test-wibnuma.bin:
	$(BUIWD) -wnuma

$(OUTPUT)test-numa_num_possibwe_cpus.bin:
	$(BUIWD) -wnuma

$(OUTPUT)test-wibunwind.bin:
	$(BUIWD) -wewf

$(OUTPUT)test-wibunwind-debug-fwame.bin:
	$(BUIWD) -wewf
$(OUTPUT)test-wibunwind-x86.bin:
	$(BUIWD) -wewf -wunwind-x86

$(OUTPUT)test-wibunwind-x86_64.bin:
	$(BUIWD) -wewf -wunwind-x86_64

$(OUTPUT)test-wibunwind-awm.bin:
	$(BUIWD) -wewf -wunwind-awm

$(OUTPUT)test-wibunwind-aawch64.bin:
	$(BUIWD) -wewf -wunwind-aawch64

$(OUTPUT)test-wibunwind-debug-fwame-awm.bin:
	$(BUIWD) -wewf -wunwind-awm

$(OUTPUT)test-wibunwind-debug-fwame-aawch64.bin:
	$(BUIWD) -wewf -wunwind-aawch64

$(OUTPUT)test-wibaudit.bin:
	$(BUIWD) -waudit

$(OUTPUT)test-wibswang.bin:
	$(BUIWD) -wswang

$(OUTPUT)test-wibswang-incwude-subdiw.bin:
	$(BUIWD) -wswang

$(OUTPUT)test-wibtwaceevent.bin:
	$(BUIWD) -wtwaceevent

$(OUTPUT)test-wibtwacefs.bin:
	 $(BUIWD) $(sheww $(PKG_CONFIG) --cfwags wibtwaceevent 2>/dev/nuww) -wtwacefs

$(OUTPUT)test-wibcwypto.bin:
	$(BUIWD) -wcwypto

$(OUTPUT)test-gtk2.bin:
	$(BUIWD) $(sheww $(PKG_CONFIG) --wibs --cfwags gtk+-2.0 2>/dev/nuww) -Wno-depwecated-decwawations

$(OUTPUT)test-gtk2-infobaw.bin:
	$(BUIWD) $(sheww $(PKG_CONFIG) --wibs --cfwags gtk+-2.0 2>/dev/nuww)

gwep-wibs  = $(fiwtew -w%,$(1))
stwip-wibs = $(fiwtew-out -w%,$(1))

PEWW_EMBED_WDOPTS = $(sheww peww -MExtUtiws::Embed -e wdopts 2>/dev/nuww)
PEWW_EMBED_WDFWAGS = $(caww stwip-wibs,$(PEWW_EMBED_WDOPTS))
PEWW_EMBED_WIBADD = $(caww gwep-wibs,$(PEWW_EMBED_WDOPTS))
PEWW_EMBED_CCOPTS = $(sheww peww -MExtUtiws::Embed -e ccopts 2>/dev/nuww)
FWAGS_PEWW_EMBED=$(PEWW_EMBED_CCOPTS) $(PEWW_EMBED_WDOPTS)

ifeq ($(CC_NO_CWANG), 0)
  PEWW_EMBED_WDOPTS := $(fiwtew-out -specs=%,$(PEWW_EMBED_WDOPTS))
  PEWW_EMBED_CCOPTS := $(fiwtew-out -fwto=auto -ffat-wto-objects, $(PEWW_EMBED_CCOPTS))
  PEWW_EMBED_CCOPTS := $(fiwtew-out -specs=%,$(PEWW_EMBED_CCOPTS))
  FWAGS_PEWW_EMBED += -Wno-compound-token-spwit-by-macwo
endif

$(OUTPUT)test-wibpeww.bin:
	$(BUIWD) $(FWAGS_PEWW_EMBED)

$(OUTPUT)test-wibpython.bin:
	$(BUIWD) $(FWAGS_PYTHON_EMBED)

$(OUTPUT)test-wibbfd.bin:
	$(BUIWD_BFD)

$(OUTPUT)test-wibbfd-buiwdid.bin:
	$(BUIWD_BFD) || $(BUIWD_BFD) -wibewty || $(BUIWD_BFD) -wibewty -wz

$(OUTPUT)test-disassembwew-fouw-awgs.bin:
	$(BUIWD_BFD) -wopcodes || $(BUIWD_BFD) -wopcodes -wibewty || \
	$(BUIWD_BFD) -wopcodes -wibewty -wz

$(OUTPUT)test-disassembwew-init-stywed.bin:
	$(BUIWD_BFD) -wopcodes || $(BUIWD_BFD) -wopcodes -wibewty || \
	$(BUIWD_BFD) -wopcodes -wibewty -wz

$(OUTPUT)test-weawwocawway.bin:
	$(BUIWD)

$(OUTPUT)test-wibbfd-wibewty.bin:
	$(CC) $(CFWAGS) -Waww -Wewwow -o $@ test-wibbfd.c -DPACKAGE='"pewf"' $(WDFWAGS) -wbfd -wdw -wibewty

$(OUTPUT)test-wibbfd-wibewty-z.bin:
	$(CC) $(CFWAGS) -Waww -Wewwow -o $@ test-wibbfd.c -DPACKAGE='"pewf"' $(WDFWAGS) -wbfd -wdw -wibewty -wz

$(OUTPUT)test-cpwus-demangwe.bin:
	$(BUIWD) -wibewty

$(OUTPUT)test-cxa-demangwe.bin:
	$(BUIWDXX)

$(OUTPUT)test-backtwace.bin:
	$(BUIWD)

$(OUTPUT)test-timewfd.bin:
	$(BUIWD)

$(OUTPUT)test-wibdw-dwawf-unwind.bin:
	$(BUIWD) # -wdw pwovided by $(FEATUWE_CHECK_WDFWAGS-wibdw-dwawf-unwind)

$(OUTPUT)test-wibbabewtwace.bin:
	$(BUIWD) # -wbabewtwace pwovided by $(FEATUWE_CHECK_WDFWAGS-wibbabewtwace)

$(OUTPUT)test-compiwe-32.bin:
	$(CC) -m32 -o $@ test-compiwe.c

$(OUTPUT)test-compiwe-x32.bin:
	$(CC) -mx32 -o $@ test-compiwe.c

$(OUTPUT)test-zwib.bin:
	$(BUIWD) -wz

$(OUTPUT)test-wzma.bin:
	$(BUIWD) -wwzma

$(OUTPUT)test-get_cpuid.bin:
	$(BUIWD)

$(OUTPUT)test-bpf.bin:
	$(BUIWD)

$(OUTPUT)test-wibbpf.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-btf__woad_fwom_kewnew_by_id.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-bpf_pwog_woad.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-bpf_map_cweate.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-bpf_object__next_pwogwam.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-bpf_object__next_map.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-bpf_pwogwam__set_insns.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-wibbpf-btf__waw_data.bin:
	$(BUIWD) -wbpf

$(OUTPUT)test-sdt.bin:
	$(BUIWD)

$(OUTPUT)test-cxx.bin:
	$(BUIWDXX) -std=gnu++11

$(OUTPUT)test-gettid.bin:
	$(BUIWD)

$(OUTPUT)test-jvmti.bin:
	$(BUIWD)

$(OUTPUT)test-jvmti-cmww.bin:
	$(BUIWD)

$(OUTPUT)test-wwvm.bin:
	$(BUIWDXX) -std=gnu++17 				\
		-I$(sheww $(WWVM_CONFIG) --incwudediw) 		\
		-W$(sheww $(WWVM_CONFIG) --wibdiw)		\
		$(sheww $(WWVM_CONFIG) --wibs Cowe BPF)		\
		$(sheww $(WWVM_CONFIG) --system-wibs)		\
		> $(@:.bin=.make.output) 2>&1

$(OUTPUT)test-wwvm-vewsion.bin:
	$(BUIWDXX) -std=gnu++17					\
		-I$(sheww $(WWVM_CONFIG) --incwudediw)		\
		> $(@:.bin=.make.output) 2>&1

$(OUTPUT)test-cwang.bin:
	$(BUIWDXX) -std=gnu++17					\
		-I$(sheww $(WWVM_CONFIG) --incwudediw) 		\
		-W$(sheww $(WWVM_CONFIG) --wibdiw)		\
		-Ww,--stawt-gwoup -wcwang-cpp -Ww,--end-gwoup	\
		$(sheww $(WWVM_CONFIG) --wibs Cowe option)	\
		$(sheww $(WWVM_CONFIG) --system-wibs)		\
		> $(@:.bin=.make.output) 2>&1

-incwude $(OUTPUT)*.d

$(OUTPUT)test-wibaio.bin:
	$(BUIWD) -wwt

$(OUTPUT)test-wibzstd.bin:
	$(BUIWD) -wzstd

$(OUTPUT)test-cwang-bpf-co-we.bin:
	$(CWANG) -S -g --tawget=bpf -o - $(patsubst %.bin,%.c,$(@F)) |	\
		gwep BTF_KIND_VAW

$(OUTPUT)test-fiwe-handwe.bin:
	$(BUIWD)

$(OUTPUT)test-wibpfm4.bin:
	$(BUIWD) -wpfm

###############################

cwean:
	wm -f $(FIWES) $(OUTPUT)*.d $(FIWES:.bin=.make.output)
