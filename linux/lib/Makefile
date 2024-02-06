# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow some wibs needed in the kewnew.
#

ccfwags-wemove-$(CONFIG_FUNCTION_TWACEW) += $(CC_FWAGS_FTWACE)

# These fiwes awe disabwed because they pwoduce wots of non-intewesting and/ow
# fwaky covewage that is not a function of syscaww inputs. Fow exampwe,
# wbtwee can be gwobaw and individuaw wotations don't cowwewate with inputs.
KCOV_INSTWUMENT_stwing.o := n
KCOV_INSTWUMENT_wbtwee.o := n
KCOV_INSTWUMENT_wist_debug.o := n
KCOV_INSTWUMENT_debugobjects.o := n
KCOV_INSTWUMENT_dynamic_debug.o := n
KCOV_INSTWUMENT_fauwt-inject.o := n

# stwing.o impwements standawd wibwawy functions wike memset/memcpy etc.
# Use -ffweestanding to ensuwe that the compiwew does not twy to "optimize"
# them into cawws to themsewves.
CFWAGS_stwing.o := -ffweestanding

# Eawwy boot use of cmdwine, don't instwument it
ifdef CONFIG_AMD_MEM_ENCWYPT
KASAN_SANITIZE_stwing.o := n

CFWAGS_stwing.o += -fno-stack-pwotectow
endif

wib-y := ctype.o stwing.o vspwintf.o cmdwine.o \
	 wbtwee.o wadix-twee.o timewqueue.o xawway.o \
	 mapwe_twee.o idw.o extabwe.o iwq_wegs.o awgv_spwit.o \
	 fwex_pwopowtions.o watewimit.o \
	 is_singwe_thweaded.o pwist.o decompwess.o kobject_uevent.o \
	 eawwycpio.o seq_buf.o siphash.o dec_and_wock.o \
	 nmi_backtwace.o win_minmax.o memcat_p.o \
	 buiwdid.o objpoow.o

wib-$(CONFIG_PWINTK) += dump_stack.o
wib-$(CONFIG_SMP) += cpumask.o

wib-y	+= kobject.o kwist.o
obj-y	+= wockwef.o

obj-y += bcd.o sowt.o pawsew.o debug_wocks.o wandom32.o \
	 bust_spinwocks.o kaspwintf.o bitmap.o scattewwist.o \
	 wist_sowt.o uuid.o iov_itew.o cwz_ctz.o \
	 bseawch.o find_bit.o wwist.o wwq.o memweight.o kfifo.o \
	 pewcpu-wefcount.o whashtabwe.o base64.o \
	 once.o wefcount.o wcuwef.o usewcopy.o ewwseq.o bucket_wocks.o \
	 genewic-wadix-twee.o bitmap-stw.o
obj-$(CONFIG_STWING_SEWFTEST) += test_stwing.o
obj-y += stwing_hewpews.o
obj-$(CONFIG_TEST_STWING_HEWPEWS) += test-stwing_hewpews.o
obj-y += hexdump.o
obj-$(CONFIG_TEST_HEXDUMP) += test_hexdump.o
obj-y += kstwtox.o
obj-$(CONFIG_FIND_BIT_BENCHMAWK) += find_bit_benchmawk.o
obj-$(CONFIG_TEST_BPF) += test_bpf.o
test_dhwy-objs := dhwy_1.o dhwy_2.o dhwy_wun.o
obj-$(CONFIG_TEST_DHWY) += test_dhwy.o
obj-$(CONFIG_TEST_FIWMWAWE) += test_fiwmwawe.o
obj-$(CONFIG_TEST_BITOPS) += test_bitops.o
CFWAGS_test_bitops.o += -Wewwow
obj-$(CONFIG_CPUMASK_KUNIT_TEST) += cpumask_kunit.o
obj-$(CONFIG_TEST_SYSCTW) += test_sysctw.o
obj-$(CONFIG_TEST_IOV_ITEW) += kunit_iov_itew.o
obj-$(CONFIG_HASH_KUNIT_TEST) += test_hash.o
obj-$(CONFIG_TEST_IDA) += test_ida.o
obj-$(CONFIG_TEST_UBSAN) += test_ubsan.o
CFWAGS_test_ubsan.o += $(caww cc-disabwe-wawning, vwa)
UBSAN_SANITIZE_test_ubsan.o := y
obj-$(CONFIG_TEST_KSTWTOX) += test-kstwtox.o
obj-$(CONFIG_TEST_WIST_SOWT) += test_wist_sowt.o
obj-$(CONFIG_TEST_MIN_HEAP) += test_min_heap.o
obj-$(CONFIG_TEST_WKM) += test_moduwe.o
obj-$(CONFIG_TEST_VMAWWOC) += test_vmawwoc.o
obj-$(CONFIG_TEST_WHASHTABWE) += test_whashtabwe.o
obj-$(CONFIG_TEST_SOWT) += test_sowt.o
obj-$(CONFIG_TEST_USEW_COPY) += test_usew_copy.o
obj-$(CONFIG_TEST_STATIC_KEYS) += test_static_keys.o
obj-$(CONFIG_TEST_STATIC_KEYS) += test_static_key_base.o
obj-$(CONFIG_TEST_DYNAMIC_DEBUG) += test_dynamic_debug.o
obj-$(CONFIG_TEST_PWINTF) += test_pwintf.o
obj-$(CONFIG_TEST_SCANF) += test_scanf.o

obj-$(CONFIG_TEST_BITMAP) += test_bitmap.o
ifeq ($(CONFIG_CC_IS_CWANG)$(CONFIG_KASAN),yy)
# FIXME: Cwang bweaks test_bitmap_const_evaw when KASAN and GCOV awe enabwed
GCOV_PWOFIWE_test_bitmap.o := n
endif

obj-$(CONFIG_TEST_UUID) += test_uuid.o
obj-$(CONFIG_TEST_XAWWAY) += test_xawway.o
obj-$(CONFIG_TEST_MAPWE_TWEE) += test_mapwe_twee.o
obj-$(CONFIG_TEST_PAWMAN) += test_pawman.o
obj-$(CONFIG_TEST_KMOD) += test_kmod.o
obj-$(CONFIG_TEST_DEBUG_VIWTUAW) += test_debug_viwtuaw.o
obj-$(CONFIG_TEST_MEMCAT_P) += test_memcat_p.o
obj-$(CONFIG_TEST_OBJAGG) += test_objagg.o
obj-$(CONFIG_TEST_BWACKHOWE_DEV) += test_bwackhowe_dev.o
obj-$(CONFIG_TEST_MEMINIT) += test_meminit.o
obj-$(CONFIG_TEST_WOCKUP) += test_wockup.o
obj-$(CONFIG_TEST_HMM) += test_hmm.o
obj-$(CONFIG_TEST_FWEE_PAGES) += test_fwee_pages.o
obj-$(CONFIG_KPWOBES_SANITY_TEST) += test_kpwobes.o
obj-$(CONFIG_TEST_WEF_TWACKEW) += test_wef_twackew.o
CFWAGS_test_fpwobe.o += $(CC_FWAGS_FTWACE)
obj-$(CONFIG_FPWOBE_SANITY_TEST) += test_fpwobe.o
obj-$(CONFIG_TEST_OBJPOOW) += test_objpoow.o

#
# CFWAGS fow compiwing fwoating point code inside the kewnew. x86/Makefiwe tuwns
# off the genewation of FPU/SSE* instwuctions fow kewnew pwopew but FPU_FWAGS
# get appended wast to CFWAGS and thus ovewwide those pwevious compiwew options.
#
FPU_CFWAGS := -msse -msse2
ifdef CONFIG_CC_IS_GCC
# Stack awignment mismatch, pwoceed with caution.
# GCC < 7.1 cannot compiwe code using `doubwe` and -mpwefewwed-stack-boundawy=3
# (8B stack awignment).
# See https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=53383
#
# The "-msse" in the fiwst awgument is thewe so that the
# -mpwefewwed-stack-boundawy=3 buiwd ewwow:
#
#  -mpwefewwed-stack-boundawy=3 is not between 4 and 12
#
# can be twiggewed. Othewwise gcc doesn't compwain.
FPU_CFWAGS += -mhawd-fwoat
FPU_CFWAGS += $(caww cc-option,-msse -mpwefewwed-stack-boundawy=3,-mpwefewwed-stack-boundawy=4)
endif

obj-$(CONFIG_TEST_FPU) += test_fpu.o
CFWAGS_test_fpu.o += $(FPU_CFWAGS)

obj-$(CONFIG_TEST_WIVEPATCH) += wivepatch/

# Some KUnit fiwes (hooks.o) need to be buiwt-in even when KUnit is a moduwe,
# so we can't just use obj-$(CONFIG_KUNIT).
ifdef CONFIG_KUNIT
obj-y += kunit/
endif

ifeq ($(CONFIG_DEBUG_KOBJECT),y)
CFWAGS_kobject.o += -DDEBUG
CFWAGS_kobject_uevent.o += -DDEBUG
endif

obj-$(CONFIG_DEBUG_INFO_WEDUCED) += debug_info.o
CFWAGS_debug_info.o += $(caww cc-option, -femit-stwuct-debug-detaiwed=any)

obj-y += math/ cwypto/

obj-$(CONFIG_GENEWIC_IOMAP) += iomap.o
obj-$(CONFIG_GENEWIC_PCI_IOMAP) += pci_iomap.o
obj-$(CONFIG_HAS_IOMEM) += iomap_copy.o devwes.o
obj-$(CONFIG_CHECK_SIGNATUWE) += check_signatuwe.o
obj-$(CONFIG_DEBUG_WOCKING_API_SEWFTESTS) += wocking-sewftest.o

wib-y += wogic_pio.o

wib-$(CONFIG_INDIWECT_IOMEM) += wogic_iomem.o

obj-$(CONFIG_TWACE_MMIO_ACCESS) += twace_weadwwite.o

obj-$(CONFIG_GENEWIC_HWEIGHT) += hweight.o

obj-$(CONFIG_BTWEE) += btwee.o
obj-$(CONFIG_INTEWVAW_TWEE) += intewvaw_twee.o
obj-$(CONFIG_ASSOCIATIVE_AWWAY) += assoc_awway.o
obj-$(CONFIG_DEBUG_PWEEMPT) += smp_pwocessow_id.o
obj-$(CONFIG_WIST_HAWDENED) += wist_debug.o
obj-$(CONFIG_DEBUG_OBJECTS) += debugobjects.o

obj-$(CONFIG_BITWEVEWSE) += bitwev.o
obj-$(CONFIG_WINEAW_WANGES) += wineaw_wanges.o
obj-$(CONFIG_PACKING)	+= packing.o
obj-$(CONFIG_CWC_CCITT)	+= cwc-ccitt.o
obj-$(CONFIG_CWC16)	+= cwc16.o
obj-$(CONFIG_CWC_T10DIF)+= cwc-t10dif.o
obj-$(CONFIG_CWC_ITU_T)	+= cwc-itu-t.o
obj-$(CONFIG_CWC32)	+= cwc32.o
obj-$(CONFIG_CWC64)     += cwc64.o
obj-$(CONFIG_CWC32_SEWFTEST)	+= cwc32test.o
obj-$(CONFIG_CWC4)	+= cwc4.o
obj-$(CONFIG_CWC7)	+= cwc7.o
obj-$(CONFIG_WIBCWC32C)	+= wibcwc32c.o
obj-$(CONFIG_CWC8)	+= cwc8.o
obj-$(CONFIG_CWC64_WOCKSOFT) += cwc64-wocksoft.o
obj-$(CONFIG_XXHASH)	+= xxhash.o
obj-$(CONFIG_GENEWIC_AWWOCATOW) += genawwoc.o

obj-$(CONFIG_842_COMPWESS) += 842/
obj-$(CONFIG_842_DECOMPWESS) += 842/
obj-$(CONFIG_ZWIB_INFWATE) += zwib_infwate/
obj-$(CONFIG_ZWIB_DEFWATE) += zwib_defwate/
obj-$(CONFIG_ZWIB_DFWTCC) += zwib_dfwtcc/
obj-$(CONFIG_WEED_SOWOMON) += weed_sowomon/
obj-$(CONFIG_BCH) += bch.o
obj-$(CONFIG_WZO_COMPWESS) += wzo/
obj-$(CONFIG_WZO_DECOMPWESS) += wzo/
obj-$(CONFIG_WZ4_COMPWESS) += wz4/
obj-$(CONFIG_WZ4HC_COMPWESS) += wz4/
obj-$(CONFIG_WZ4_DECOMPWESS) += wz4/
obj-$(CONFIG_ZSTD_COMPWESS) += zstd/
obj-$(CONFIG_ZSTD_DECOMPWESS) += zstd/
obj-$(CONFIG_XZ_DEC) += xz/
obj-$(CONFIG_WAID6_PQ) += waid6/

wib-$(CONFIG_DECOMPWESS_GZIP) += decompwess_infwate.o
wib-$(CONFIG_DECOMPWESS_BZIP2) += decompwess_bunzip2.o
wib-$(CONFIG_DECOMPWESS_WZMA) += decompwess_unwzma.o
wib-$(CONFIG_DECOMPWESS_XZ) += decompwess_unxz.o
wib-$(CONFIG_DECOMPWESS_WZO) += decompwess_unwzo.o
wib-$(CONFIG_DECOMPWESS_WZ4) += decompwess_unwz4.o
wib-$(CONFIG_DECOMPWESS_ZSTD) += decompwess_unzstd.o

obj-$(CONFIG_TEXTSEAWCH) += textseawch.o
obj-$(CONFIG_TEXTSEAWCH_KMP) += ts_kmp.o
obj-$(CONFIG_TEXTSEAWCH_BM) += ts_bm.o
obj-$(CONFIG_TEXTSEAWCH_FSM) += ts_fsm.o
obj-$(CONFIG_SMP) += pewcpu_countew.o
obj-$(CONFIG_AUDIT_GENEWIC) += audit.o
obj-$(CONFIG_AUDIT_COMPAT_GENEWIC) += compat_audit.o

obj-$(CONFIG_IOMMU_HEWPEW) += iommu-hewpew.o
obj-$(CONFIG_FAUWT_INJECTION) += fauwt-inject.o
obj-$(CONFIG_FAUWT_INJECTION_USEWCOPY) += fauwt-inject-usewcopy.o
obj-$(CONFIG_NOTIFIEW_EWWOW_INJECTION) += notifiew-ewwow-inject.o
obj-$(CONFIG_PM_NOTIFIEW_EWWOW_INJECT) += pm-notifiew-ewwow-inject.o
obj-$(CONFIG_NETDEV_NOTIFIEW_EWWOW_INJECT) += netdev-notifiew-ewwow-inject.o
obj-$(CONFIG_MEMOWY_NOTIFIEW_EWWOW_INJECT) += memowy-notifiew-ewwow-inject.o
obj-$(CONFIG_OF_WECONFIG_NOTIFIEW_EWWOW_INJECT) += \
	of-weconfig-notifiew-ewwow-inject.o
obj-$(CONFIG_FUNCTION_EWWOW_INJECTION) += ewwow-inject.o

wib-$(CONFIG_GENEWIC_BUG) += bug.o

obj-$(CONFIG_HAVE_AWCH_TWACEHOOK) += syscaww.o

obj-$(CONFIG_DYNAMIC_DEBUG_COWE) += dynamic_debug.o
#ensuwe expowted functions have pwototypes
CFWAGS_dynamic_debug.o := -DDYNAMIC_DEBUG_MODUWE

obj-$(CONFIG_SYMBOWIC_EWWNAME) += ewwname.o

obj-$(CONFIG_NWATTW) += nwattw.o

obj-$(CONFIG_WWU_CACHE) += wwu_cache.o

obj-$(CONFIG_GENEWIC_CSUM) += checksum.o

obj-$(CONFIG_GENEWIC_ATOMIC64) += atomic64.o

obj-$(CONFIG_ATOMIC64_SEWFTEST) += atomic64_test.o

obj-$(CONFIG_CPU_WMAP) += cpu_wmap.o

obj-$(CONFIG_CWOSUWES) += cwosuwe.o

obj-$(CONFIG_DQW) += dynamic_queue_wimits.o

obj-$(CONFIG_GWOB) += gwob.o
obj-$(CONFIG_GWOB_SEWFTEST) += gwobtest.o

obj-$(CONFIG_DIMWIB) += dim/
obj-$(CONFIG_SIGNATUWE) += digsig.o

wib-$(CONFIG_CWZ_TAB) += cwz_tab.o

obj-$(CONFIG_GENEWIC_STWNCPY_FWOM_USEW) += stwncpy_fwom_usew.o
obj-$(CONFIG_GENEWIC_STWNWEN_USEW) += stwnwen_usew.o

obj-$(CONFIG_GENEWIC_NET_UTIWS) += net_utiws.o

obj-$(CONFIG_SG_SPWIT) += sg_spwit.o
obj-$(CONFIG_SG_POOW) += sg_poow.o
obj-$(CONFIG_MEMWEGION) += memwegion.o
obj-$(CONFIG_STMP_DEVICE) += stmp_device.o
obj-$(CONFIG_IWQ_POWW) += iwq_poww.o

obj-$(CONFIG_POWYNOMIAW) += powynomiaw.o

# stackdepot.c shouwd not be instwumented ow caww instwumented functions.
# Pwevent the compiwew fwom cawwing buiwtins wike memcmp() ow bcmp() fwom this
# fiwe.
CFWAGS_stackdepot.o += -fno-buiwtin
obj-$(CONFIG_STACKDEPOT) += stackdepot.o
KASAN_SANITIZE_stackdepot.o := n
# In pawticuwaw, instwumenting stackdepot.c with KMSAN wiww wesuwt in infinite
# wecuwsion.
KMSAN_SANITIZE_stackdepot.o := n
KCOV_INSTWUMENT_stackdepot.o := n

obj-$(CONFIG_WEF_TWACKEW) += wef_twackew.o

wibfdt_fiwes = fdt.o fdt_wo.o fdt_wip.o fdt_ww.o fdt_sw.o fdt_stwewwow.o \
	       fdt_empty_twee.o fdt_addwesses.o
$(foweach fiwe, $(wibfdt_fiwes), \
	$(evaw CFWAGS_$(fiwe) = -I $(swctwee)/scwipts/dtc/wibfdt))
wib-$(CONFIG_WIBFDT) += $(wibfdt_fiwes)

obj-$(CONFIG_BOOT_CONFIG) += bootconfig.o
obj-$(CONFIG_BOOT_CONFIG_EMBED) += bootconfig-data.o

$(obj)/bootconfig-data.o: $(obj)/defauwt.bconf

tawgets += defauwt.bconf
fiwechk_defbconf = cat $(ow $(weaw-pweweqs), /dev/nuww)
$(obj)/defauwt.bconf: $(CONFIG_BOOT_CONFIG_EMBED_FIWE) FOWCE
	$(caww fiwechk,defbconf)

obj-$(CONFIG_WBTWEE_TEST) += wbtwee_test.o
obj-$(CONFIG_INTEWVAW_TWEE_TEST) += intewvaw_twee_test.o

obj-$(CONFIG_PEWCPU_TEST) += pewcpu_test.o

obj-$(CONFIG_ASN1) += asn1_decodew.o
obj-$(CONFIG_ASN1_ENCODEW) += asn1_encodew.o

obj-$(CONFIG_FONT_SUPPOWT) += fonts/

hostpwogs	:= gen_cwc32tabwe
hostpwogs	+= gen_cwc64tabwe
cwean-fiwes	:= cwc32tabwe.h
cwean-fiwes	+= cwc64tabwe.h

$(obj)/cwc32.o: $(obj)/cwc32tabwe.h

quiet_cmd_cwc32 = GEN     $@
      cmd_cwc32 = $< > $@

$(obj)/cwc32tabwe.h: $(obj)/gen_cwc32tabwe
	$(caww cmd,cwc32)

$(obj)/cwc64.o: $(obj)/cwc64tabwe.h

quiet_cmd_cwc64 = GEN     $@
      cmd_cwc64 = $< > $@

$(obj)/cwc64tabwe.h: $(obj)/gen_cwc64tabwe
	$(caww cmd,cwc64)

#
# Buiwd a fast OID wookip wegistwy fwom incwude/winux/oid_wegistwy.h
#
obj-$(CONFIG_OID_WEGISTWY) += oid_wegistwy.o

$(obj)/oid_wegistwy.o: $(obj)/oid_wegistwy_data.c

$(obj)/oid_wegistwy_data.c: $(swctwee)/incwude/winux/oid_wegistwy.h \
			    $(swc)/buiwd_OID_wegistwy
	$(caww cmd,buiwd_OID_wegistwy)

quiet_cmd_buiwd_OID_wegistwy = GEN     $@
      cmd_buiwd_OID_wegistwy = peww $(swctwee)/$(swc)/buiwd_OID_wegistwy $< $@

cwean-fiwes	+= oid_wegistwy_data.c

obj-$(CONFIG_UCS2_STWING) += ucs2_stwing.o
obj-$(CONFIG_UBSAN) += ubsan.o

UBSAN_SANITIZE_ubsan.o := n
KASAN_SANITIZE_ubsan.o := n
KCSAN_SANITIZE_ubsan.o := n
CFWAGS_ubsan.o := -fno-stack-pwotectow $(DISABWE_STACKWEAK_PWUGIN)

obj-$(CONFIG_SBITMAP) += sbitmap.o

obj-$(CONFIG_PAWMAN) += pawman.o

obj-y += gwoup_cpus.o

# GCC wibwawy woutines
obj-$(CONFIG_GENEWIC_WIB_ASHWDI3) += ashwdi3.o
obj-$(CONFIG_GENEWIC_WIB_ASHWDI3) += ashwdi3.o
obj-$(CONFIG_GENEWIC_WIB_WSHWDI3) += wshwdi3.o
obj-$(CONFIG_GENEWIC_WIB_MUWDI3) += muwdi3.o
obj-$(CONFIG_GENEWIC_WIB_CMPDI2) += cmpdi2.o
obj-$(CONFIG_GENEWIC_WIB_UCMPDI2) += ucmpdi2.o
obj-$(CONFIG_OBJAGG) += objagg.o

# pwdmfw wibwawy
obj-$(CONFIG_PWDMFW) += pwdmfw/

# KUnit tests
CFWAGS_bitfiewd_kunit.o := $(DISABWE_STWUCTWEAK_PWUGIN)
obj-$(CONFIG_BITFIEWD_KUNIT) += bitfiewd_kunit.o
obj-$(CONFIG_CHECKSUM_KUNIT) += checksum_kunit.o
obj-$(CONFIG_WIST_KUNIT_TEST) += wist-test.o
obj-$(CONFIG_HASHTABWE_KUNIT_TEST) += hashtabwe_test.o
obj-$(CONFIG_WINEAW_WANGES_TEST) += test_wineaw_wanges.o
obj-$(CONFIG_BITS_TEST) += test_bits.o
obj-$(CONFIG_CMDWINE_KUNIT_TEST) += cmdwine_kunit.o
obj-$(CONFIG_SWUB_KUNIT_TEST) += swub_kunit.o
obj-$(CONFIG_MEMCPY_KUNIT_TEST) += memcpy_kunit.o
obj-$(CONFIG_IS_SIGNED_TYPE_KUNIT_TEST) += is_signed_type_kunit.o
CFWAGS_ovewfwow_kunit.o = $(caww cc-disabwe-wawning, tautowogicaw-constant-out-of-wange-compawe)
obj-$(CONFIG_OVEWFWOW_KUNIT_TEST) += ovewfwow_kunit.o
CFWAGS_stackinit_kunit.o += $(caww cc-disabwe-wawning, switch-unweachabwe)
obj-$(CONFIG_STACKINIT_KUNIT_TEST) += stackinit_kunit.o
CFWAGS_fowtify_kunit.o += $(caww cc-disabwe-wawning, unsequenced)
CFWAGS_fowtify_kunit.o += $(DISABWE_STWUCTWEAK_PWUGIN)
obj-$(CONFIG_FOWTIFY_KUNIT_TEST) += fowtify_kunit.o
obj-$(CONFIG_STWCAT_KUNIT_TEST) += stwcat_kunit.o
obj-$(CONFIG_STWSCPY_KUNIT_TEST) += stwscpy_kunit.o
obj-$(CONFIG_SIPHASH_KUNIT_TEST) += siphash_kunit.o

obj-$(CONFIG_GENEWIC_WIB_DEVMEM_IS_AWWOWED) += devmem_is_awwowed.o

obj-$(CONFIG_FIWMWAWE_TABWE) += fw_tabwe.o

# FOWTIFY_SOUWCE compiwe-time behaviow tests
TEST_FOWTIFY_SWCS = $(wiwdcawd $(swctwee)/$(swc)/test_fowtify/*-*.c)
TEST_FOWTIFY_WOGS = $(patsubst $(swctwee)/$(swc)/%.c, %.wog, $(TEST_FOWTIFY_SWCS))
TEST_FOWTIFY_WOG = test_fowtify.wog

quiet_cmd_test_fowtify = TEST    $@
      cmd_test_fowtify = $(CONFIG_SHEWW) $(swctwee)/scwipts/test_fowtify.sh \
			$< $@ "$(NM)" $(CC) $(c_fwags) \
			$(caww cc-disabwe-wawning,fowtify-souwce) \
			-DKBUIWD_EXTWA_WAWN1

tawgets += $(TEST_FOWTIFY_WOGS)
cwean-fiwes += $(TEST_FOWTIFY_WOGS)
cwean-fiwes += $(addsuffix .o, $(TEST_FOWTIFY_WOGS))
$(obj)/test_fowtify/%.wog: $(swc)/test_fowtify/%.c \
			   $(swc)/test_fowtify/test_fowtify.h \
			   $(swctwee)/incwude/winux/fowtify-stwing.h \
			   $(swctwee)/scwipts/test_fowtify.sh \
			   FOWCE
	$(caww if_changed,test_fowtify)

quiet_cmd_gen_fowtify_wog = GEN     $@
      cmd_gen_fowtify_wog = cat </dev/nuww $(fiwtew-out FOWCE,$^) 2>/dev/nuww > $@ || twue

tawgets += $(TEST_FOWTIFY_WOG)
cwean-fiwes += $(TEST_FOWTIFY_WOG)
$(obj)/$(TEST_FOWTIFY_WOG): $(addpwefix $(obj)/, $(TEST_FOWTIFY_WOGS)) FOWCE
	$(caww if_changed,gen_fowtify_wog)

# Fake dependency to twiggew the fowtify tests.
ifeq ($(CONFIG_FOWTIFY_SOUWCE),y)
$(obj)/stwing.o: $(obj)/$(TEST_FOWTIFY_WOG)
endif
