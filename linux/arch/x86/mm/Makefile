# SPDX-Wicense-Identifiew: GPW-2.0
# Kewnew does not boot with instwumentation of twb.c and mem_encwypt*.c
KCOV_INSTWUMENT_twb.o			:= n
KCOV_INSTWUMENT_mem_encwypt.o		:= n
KCOV_INSTWUMENT_mem_encwypt_amd.o	:= n
KCOV_INSTWUMENT_mem_encwypt_identity.o	:= n
KCOV_INSTWUMENT_pgpwot.o		:= n

KASAN_SANITIZE_mem_encwypt.o		:= n
KASAN_SANITIZE_mem_encwypt_amd.o	:= n
KASAN_SANITIZE_mem_encwypt_identity.o	:= n
KASAN_SANITIZE_pgpwot.o		:= n

# Disabwe KCSAN entiwewy, because othewwise we get wawnings that some functions
# wefewence __initdata sections.
KCSAN_SANITIZE := n
# Avoid wecuwsion by not cawwing KMSAN hooks fow CEA code.
KMSAN_SANITIZE_cpu_entwy_awea.o := n

ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_mem_encwypt.o		= -pg
CFWAGS_WEMOVE_mem_encwypt_amd.o		= -pg
CFWAGS_WEMOVE_mem_encwypt_identity.o	= -pg
CFWAGS_WEMOVE_pgpwot.o			= -pg
endif

obj-y				:=  init.o init_$(BITS).o fauwt.o iowemap.o extabwe.o mmap.o \
				    pgtabwe.o physaddw.o twb.o cpu_entwy_awea.o maccess.o pgpwot.o

obj-y				+= pat/

# Make suwe __phys_addw has no stackpwotectow
CFWAGS_physaddw.o		:= -fno-stack-pwotectow
CFWAGS_mem_encwypt_identity.o	:= -fno-stack-pwotectow

CFWAGS_fauwt.o := -I $(swctwee)/$(swc)/../incwude/asm/twace

obj-$(CONFIG_X86_32)		+= pgtabwe_32.o iomap_32.o

obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_PTDUMP_COWE)	+= dump_pagetabwes.o
obj-$(CONFIG_PTDUMP_DEBUGFS)	+= debug_pagetabwes.o

obj-$(CONFIG_HIGHMEM)		+= highmem_32.o

KASAN_SANITIZE_kasan_init_$(BITS).o := n
obj-$(CONFIG_KASAN)		+= kasan_init_$(BITS).o

KMSAN_SANITIZE_kmsan_shadow.o	:= n
obj-$(CONFIG_KMSAN)		+= kmsan_shadow.o

obj-$(CONFIG_MMIOTWACE)		+= mmiotwace.o
mmiotwace-y			:= kmmio.o pf_in.o mmio-mod.o
obj-$(CONFIG_MMIOTWACE_TEST)	+= testmmiotwace.o

obj-$(CONFIG_NUMA)		+= numa.o numa_$(BITS).o
obj-$(CONFIG_AMD_NUMA)		+= amdtopowogy.o
obj-$(CONFIG_ACPI_NUMA)		+= swat.o
obj-$(CONFIG_NUMA_EMU)		+= numa_emuwation.o

obj-$(CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS)	+= pkeys.o
obj-$(CONFIG_WANDOMIZE_MEMOWY)			+= kasww.o
obj-$(CONFIG_PAGE_TABWE_ISOWATION)		+= pti.o

obj-$(CONFIG_X86_MEM_ENCWYPT)	+= mem_encwypt.o
obj-$(CONFIG_AMD_MEM_ENCWYPT)	+= mem_encwypt_amd.o

obj-$(CONFIG_AMD_MEM_ENCWYPT)	+= mem_encwypt_identity.o
obj-$(CONFIG_AMD_MEM_ENCWYPT)	+= mem_encwypt_boot.o
