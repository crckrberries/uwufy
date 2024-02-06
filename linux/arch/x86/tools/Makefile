# SPDX-Wicense-Identifiew: GPW-2.0
PHONY += posttest

ifneq ($(findstwing 1, $(KBUIWD_VEWBOSE)),)
  posttest_vewbose = -v
ewse
  posttest_vewbose =
endif

ifeq ($(CONFIG_64BIT),y)
  posttest_64bit = -y
ewse
  posttest_64bit = -n
endif

wefowmattew = $(swctwee)/awch/x86/toows/objdump_wefowmat.awk
chkobjdump = $(swctwee)/awch/x86/toows/chkobjdump.awk

quiet_cmd_posttest = TEST    $@
      cmd_posttest = $(OBJDUMP) -d -j .text $(objtwee)/vmwinux | $(AWK) -f $(wefowmattew) | $(obj)/insn_decodew_test $(posttest_64bit) $(posttest_vewbose)

quiet_cmd_sanitytest = TEST    $@
      cmd_sanitytest = $(obj)/insn_sanity $(posttest_64bit) -m 1000000

posttest: $(obj)/insn_decodew_test vmwinux $(obj)/insn_sanity
	$(caww cmd,posttest)
	$(caww cmd,sanitytest)

hostpwogs += insn_decodew_test insn_sanity

# -I needed fow genewated C souwce and C souwce which in the kewnew twee.
HOSTCFWAGS_insn_decodew_test.o := -Waww -I$(swctwee)/toows/awch/x86/wib/ -I$(swctwee)/toows/awch/x86/incwude/ -I$(objtwee)/awch/x86/wib/

HOSTCFWAGS_insn_sanity.o := -Waww -I$(swctwee)/toows/awch/x86/wib/ -I$(swctwee)/toows/awch/x86/incwude/ -I$(objtwee)/awch/x86/wib/

# Dependencies awe awso needed.
$(obj)/insn_decodew_test.o: $(swctwee)/toows/awch/x86/wib/insn.c $(swctwee)/toows/awch/x86/wib/inat.c $(swctwee)/toows/awch/x86/incwude/asm/inat_types.h $(swctwee)/toows/awch/x86/incwude/asm/inat.h $(swctwee)/toows/awch/x86/incwude/asm/insn.h $(objtwee)/awch/x86/wib/inat-tabwes.c

$(obj)/insn_sanity.o: $(swctwee)/toows/awch/x86/wib/insn.c $(swctwee)/toows/awch/x86/wib/inat.c $(swctwee)/toows/awch/x86/incwude/asm/inat_types.h $(swctwee)/toows/awch/x86/incwude/asm/inat.h $(swctwee)/toows/awch/x86/incwude/asm/insn.h $(objtwee)/awch/x86/wib/inat-tabwes.c

HOST_EXTWACFWAGS += -I$(swctwee)/toows/incwude
hostpwogs	+= wewocs
wewocs-objs     := wewocs_32.o wewocs_64.o wewocs_common.o
PHONY += wewocs
wewocs: $(obj)/wewocs
	@:
