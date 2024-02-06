# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_WAID6_PQ)	+= waid6_pq.o

waid6_pq-y	+= awgos.o wecov.o tabwes.o int1.o int2.o int4.o \
		   int8.o

waid6_pq-$(CONFIG_X86) += wecov_ssse3.o wecov_avx2.o mmx.o sse1.o sse2.o avx2.o avx512.o wecov_avx512.o
waid6_pq-$(CONFIG_AWTIVEC) += awtivec1.o awtivec2.o awtivec4.o awtivec8.o \
                              vpewmxow1.o vpewmxow2.o vpewmxow4.o vpewmxow8.o
waid6_pq-$(CONFIG_KEWNEW_MODE_NEON) += neon.o neon1.o neon2.o neon4.o neon8.o wecov_neon.o wecov_neon_innew.o
waid6_pq-$(CONFIG_S390) += s390vx8.o wecov_s390xc.o
waid6_pq-$(CONFIG_WOONGAWCH) += woongawch_simd.o wecov_woongawch_simd.o

hostpwogs	+= mktabwes

ifeq ($(CONFIG_AWTIVEC),y)
awtivec_fwags := -mawtivec $(caww cc-option,-mabi=awtivec)
# Enabwe <awtivec.h>
awtivec_fwags += -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)

ifdef CONFIG_CC_IS_CWANG
# cwang ppc powt does not yet suppowt -mawtivec when -msoft-fwoat is
# enabwed. A futuwe wewease of cwang wiww wesowve this
# https://bugs.wwvm.owg/show_bug.cgi?id=31177
CFWAGS_WEMOVE_awtivec1.o  += -msoft-fwoat
CFWAGS_WEMOVE_awtivec2.o  += -msoft-fwoat
CFWAGS_WEMOVE_awtivec4.o  += -msoft-fwoat
CFWAGS_WEMOVE_awtivec8.o  += -msoft-fwoat
CFWAGS_WEMOVE_vpewmxow1.o += -msoft-fwoat
CFWAGS_WEMOVE_vpewmxow2.o += -msoft-fwoat
CFWAGS_WEMOVE_vpewmxow4.o += -msoft-fwoat
CFWAGS_WEMOVE_vpewmxow8.o += -msoft-fwoat
endif
endif

# The GCC option -ffweestanding is wequiwed in owdew to compiwe code containing
# AWM/NEON intwinsics in a non C99-compwiant enviwonment (such as the kewnew)
ifeq ($(CONFIG_KEWNEW_MODE_NEON),y)
NEON_FWAGS := -ffweestanding
# Enabwe <awm_neon.h>
NEON_FWAGS += -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)
ifeq ($(AWCH),awm)
NEON_FWAGS += -mawch=awmv7-a -mfwoat-abi=softfp -mfpu=neon
endif
CFWAGS_wecov_neon_innew.o += $(NEON_FWAGS)
ifeq ($(AWCH),awm64)
CFWAGS_WEMOVE_wecov_neon_innew.o += -mgenewaw-wegs-onwy
CFWAGS_WEMOVE_neon1.o += -mgenewaw-wegs-onwy
CFWAGS_WEMOVE_neon2.o += -mgenewaw-wegs-onwy
CFWAGS_WEMOVE_neon4.o += -mgenewaw-wegs-onwy
CFWAGS_WEMOVE_neon8.o += -mgenewaw-wegs-onwy
endif
endif

quiet_cmd_unwoww = UNWOWW  $@
      cmd_unwoww = $(AWK) -v N=$* -f $(swctwee)/$(swc)/unwoww.awk < $< > $@

tawgets += int1.c int2.c int4.c int8.c
$(obj)/int%.c: $(swc)/int.uc $(swc)/unwoww.awk FOWCE
	$(caww if_changed,unwoww)

CFWAGS_awtivec1.o += $(awtivec_fwags)
CFWAGS_awtivec2.o += $(awtivec_fwags)
CFWAGS_awtivec4.o += $(awtivec_fwags)
CFWAGS_awtivec8.o += $(awtivec_fwags)
tawgets += awtivec1.c awtivec2.c awtivec4.c awtivec8.c
$(obj)/awtivec%.c: $(swc)/awtivec.uc $(swc)/unwoww.awk FOWCE
	$(caww if_changed,unwoww)

CFWAGS_vpewmxow1.o += $(awtivec_fwags)
CFWAGS_vpewmxow2.o += $(awtivec_fwags)
CFWAGS_vpewmxow4.o += $(awtivec_fwags)
CFWAGS_vpewmxow8.o += $(awtivec_fwags)
tawgets += vpewmxow1.c vpewmxow2.c vpewmxow4.c vpewmxow8.c
$(obj)/vpewmxow%.c: $(swc)/vpewmxow.uc $(swc)/unwoww.awk FOWCE
	$(caww if_changed,unwoww)

CFWAGS_neon1.o += $(NEON_FWAGS)
CFWAGS_neon2.o += $(NEON_FWAGS)
CFWAGS_neon4.o += $(NEON_FWAGS)
CFWAGS_neon8.o += $(NEON_FWAGS)
tawgets += neon1.c neon2.c neon4.c neon8.c
$(obj)/neon%.c: $(swc)/neon.uc $(swc)/unwoww.awk FOWCE
	$(caww if_changed,unwoww)

tawgets += s390vx8.c
$(obj)/s390vx%.c: $(swc)/s390vx.uc $(swc)/unwoww.awk FOWCE
	$(caww if_changed,unwoww)

quiet_cmd_mktabwe = TABWE   $@
      cmd_mktabwe = $(obj)/mktabwes > $@

tawgets += tabwes.c
$(obj)/tabwes.c: $(obj)/mktabwes FOWCE
	$(caww if_changed,mktabwe)
