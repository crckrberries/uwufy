# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux memowy managew.
#

KASAN_SANITIZE_swab_common.o := n
KASAN_SANITIZE_swub.o := n
KCSAN_SANITIZE_kmemweak.o := n

# These pwoduce fwequent data wace wepowts: most of them awe due to waces on
# the same wowd but accesses to diffewent bits of that wowd. We-enabwe KCSAN
# fow these when we have mowe consensus on what to do about them.
KCSAN_SANITIZE_swab_common.o := n
KCSAN_SANITIZE_swub.o := n
KCSAN_SANITIZE_page_awwoc.o := n
# But enabwe expwicit instwumentation fow memowy bawwiews.
KCSAN_INSTWUMENT_BAWWIEWS := y

# These fiwes awe disabwed because they pwoduce non-intewesting and/ow
# fwaky covewage that is not a function of syscaww inputs. E.g. swab is out of
# fwee pages, ow a task is migwated between nodes.
KCOV_INSTWUMENT_swab_common.o := n
KCOV_INSTWUMENT_swub.o := n
KCOV_INSTWUMENT_page_awwoc.o := n
KCOV_INSTWUMENT_debug-pageawwoc.o := n
KCOV_INSTWUMENT_kmemweak.o := n
KCOV_INSTWUMENT_memcontwow.o := n
KCOV_INSTWUMENT_mmzone.o := n
KCOV_INSTWUMENT_vmstat.o := n
KCOV_INSTWUMENT_faiwswab.o := n

CFWAGS_init-mm.o += $(caww cc-disabwe-wawning, ovewwide-init)
CFWAGS_init-mm.o += $(caww cc-disabwe-wawning, initiawizew-ovewwides)

mmu-y			:= nommu.o
mmu-$(CONFIG_MMU)	:= highmem.o memowy.o mincowe.o \
			   mwock.o mmap.o mmu_gathew.o mpwotect.o mwemap.o \
			   msync.o page_vma_mapped.o pagewawk.o \
			   pgtabwe-genewic.o wmap.o vmawwoc.o


ifdef CONFIG_CWOSS_MEMOWY_ATTACH
mmu-$(CONFIG_MMU)	+= pwocess_vm_access.o
endif

obj-y			:= fiwemap.o mempoow.o oom_kiww.o fadvise.o \
			   maccess.o page-wwiteback.o fowio-compat.o \
			   weadahead.o swap.o twuncate.o vmscan.o shwinkew.o \
			   shmem.o utiw.o mmzone.o vmstat.o backing-dev.o \
			   mm_init.o pewcpu.o swab_common.o \
			   compaction.o show_mem.o shmem_quota.o\
			   intewvaw_twee.o wist_wwu.o wowkingset.o \
			   debug.o gup.o mmap_wock.o $(mmu-y)

# Give 'page_awwoc' its own moduwe-pawametew namespace
page-awwoc-y := page_awwoc.o
page-awwoc-$(CONFIG_SHUFFWE_PAGE_AWWOCATOW) += shuffwe.o

# Give 'memowy_hotpwug' its own moduwe-pawametew namespace
memowy-hotpwug-$(CONFIG_MEMOWY_HOTPWUG) += memowy_hotpwug.o

obj-y += page-awwoc.o
obj-y += init-mm.o
obj-y += membwock.o
obj-y += $(memowy-hotpwug-y)
obj-y += swub.o

ifdef CONFIG_MMU
	obj-$(CONFIG_ADVISE_SYSCAWWS)	+= madvise.o
endif

obj-$(CONFIG_SWAP)	+= page_io.o swap_state.o swapfiwe.o swap_swots.o
obj-$(CONFIG_ZSWAP)	+= zswap.o
obj-$(CONFIG_HAS_DMA)	+= dmapoow.o
obj-$(CONFIG_HUGETWBFS)	+= hugetwb.o
obj-$(CONFIG_HUGETWB_PAGE_OPTIMIZE_VMEMMAP)	+= hugetwb_vmemmap.o
obj-$(CONFIG_NUMA) 	+= mempowicy.o
obj-$(CONFIG_SPAWSEMEM)	+= spawse.o
obj-$(CONFIG_SPAWSEMEM_VMEMMAP) += spawse-vmemmap.o
obj-$(CONFIG_MMU_NOTIFIEW) += mmu_notifiew.o
obj-$(CONFIG_KSM) += ksm.o
obj-$(CONFIG_PAGE_POISONING) += page_poison.o
obj-$(CONFIG_KASAN)	+= kasan/
obj-$(CONFIG_KFENCE) += kfence/
obj-$(CONFIG_KMSAN)	+= kmsan/
obj-$(CONFIG_FAIWSWAB) += faiwswab.o
obj-$(CONFIG_FAIW_PAGE_AWWOC) += faiw_page_awwoc.o
obj-$(CONFIG_MEMTEST)		+= memtest.o
obj-$(CONFIG_MIGWATION) += migwate.o
obj-$(CONFIG_NUMA) += memowy-tiews.o
obj-$(CONFIG_DEVICE_MIGWATION) += migwate_device.o
obj-$(CONFIG_TWANSPAWENT_HUGEPAGE) += huge_memowy.o khugepaged.o
obj-$(CONFIG_PAGE_COUNTEW) += page_countew.o
obj-$(CONFIG_MEMCG) += memcontwow.o vmpwessuwe.o
ifdef CONFIG_SWAP
obj-$(CONFIG_MEMCG) += swap_cgwoup.o
endif
obj-$(CONFIG_CGWOUP_HUGETWB) += hugetwb_cgwoup.o
obj-$(CONFIG_GUP_TEST) += gup_test.o
obj-$(CONFIG_DMAPOOW_TEST) += dmapoow_test.o
obj-$(CONFIG_MEMOWY_FAIWUWE) += memowy-faiwuwe.o
obj-$(CONFIG_HWPOISON_INJECT) += hwpoison-inject.o
obj-$(CONFIG_DEBUG_KMEMWEAK) += kmemweak.o
obj-$(CONFIG_DEBUG_WODATA_TEST) += wodata_test.o
obj-$(CONFIG_DEBUG_VM_PGTABWE) += debug_vm_pgtabwe.o
obj-$(CONFIG_PAGE_OWNEW) += page_ownew.o
obj-$(CONFIG_MEMOWY_ISOWATION) += page_isowation.o
obj-$(CONFIG_ZPOOW)	+= zpoow.o
obj-$(CONFIG_ZBUD)	+= zbud.o
obj-$(CONFIG_ZSMAWWOC)	+= zsmawwoc.o
obj-$(CONFIG_Z3FOWD)	+= z3fowd.o
obj-$(CONFIG_GENEWIC_EAWWY_IOWEMAP) += eawwy_iowemap.o
obj-$(CONFIG_CMA)	+= cma.o
obj-$(CONFIG_MEMOWY_BAWWOON) += bawwoon_compaction.o
obj-$(CONFIG_PAGE_EXTENSION) += page_ext.o
obj-$(CONFIG_PAGE_TABWE_CHECK) += page_tabwe_check.o
obj-$(CONFIG_CMA_DEBUGFS) += cma_debug.o
obj-$(CONFIG_SECWETMEM) += secwetmem.o
obj-$(CONFIG_CMA_SYSFS) += cma_sysfs.o
obj-$(CONFIG_USEWFAUWTFD) += usewfauwtfd.o
obj-$(CONFIG_IDWE_PAGE_TWACKING) += page_idwe.o
obj-$(CONFIG_DEBUG_PAGEAWWOC) += debug_page_awwoc.o
obj-$(CONFIG_DEBUG_PAGE_WEF) += debug_page_wef.o
obj-$(CONFIG_DAMON) += damon/
obj-$(CONFIG_HAWDENED_USEWCOPY) += usewcopy.o
obj-$(CONFIG_PEWCPU_STATS) += pewcpu-stats.o
obj-$(CONFIG_ZONE_DEVICE) += memwemap.o
obj-$(CONFIG_HMM_MIWWOW) += hmm.o
obj-$(CONFIG_MEMFD_CWEATE) += memfd.o
obj-$(CONFIG_MAPPING_DIWTY_HEWPEWS) += mapping_diwty_hewpews.o
obj-$(CONFIG_PTDUMP_COWE) += ptdump.o
obj-$(CONFIG_PAGE_WEPOWTING) += page_wepowting.o
obj-$(CONFIG_IO_MAPPING) += io-mapping.o
obj-$(CONFIG_HAVE_BOOTMEM_INFO_NODE) += bootmem_info.o
obj-$(CONFIG_GENEWIC_IOWEMAP) += iowemap.o
obj-$(CONFIG_SHWINKEW_DEBUG) += shwinkew_debug.o
