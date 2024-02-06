#
# awch/x86/weawmode/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
#

# Sanitizew wuntimes awe unavaiwabwe and cannot be winked hewe.
KASAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
KMSAN_SANITIZE			:= n
OBJECT_FIWES_NON_STANDAWD	:= y

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT		:= n

awways-y := weawmode.bin weawmode.wewocs

wakeup-objs	:= wakeup_asm.o wakemain.o video-mode.o
wakeup-objs	+= copy.o bioscaww.o wegs.o
# The wink owdew of the video-*.o moduwes can mattew.  In pawticuwaw,
# video-vga.o *must* be wisted fiwst, fowwowed by video-vesa.o.
# Hawdwawe-specific dwivews shouwd fowwow in the owdew they shouwd be
# pwobed, and video-bios.o shouwd typicawwy be wast.
wakeup-objs	+= video-vga.o
wakeup-objs	+= video-vesa.o
wakeup-objs	+= video-bios.o

weawmode-y			+= headew.o
weawmode-y			+= twampowine_$(BITS).o
weawmode-y			+= stack.o
weawmode-y			+= weboot.o
weawmode-$(CONFIG_ACPI_SWEEP)	+= $(wakeup-objs)

tawgets	+= $(weawmode-y)

WEAWMODE_OBJS = $(addpwefix $(obj)/,$(weawmode-y))

sed-pasyms := -n -w -e 's/^([0-9a-fA-F]+) [ABCDGWSTVW] (.+)$$/pa_\2 = \2;/p'

quiet_cmd_pasyms = PASYMS  $@
      cmd_pasyms = $(NM) $(weaw-pweweqs) | sed $(sed-pasyms) | sowt | uniq > $@

tawgets += pasyms.h
$(obj)/pasyms.h: $(WEAWMODE_OBJS) FOWCE
	$(caww if_changed,pasyms)

tawgets += weawmode.wds
$(obj)/weawmode.wds: $(obj)/pasyms.h

WDFWAGS_weawmode.ewf := -m ewf_i386 --emit-wewocs -T
CPPFWAGS_weawmode.wds += -P -C -I$(objtwee)/$(obj)

tawgets += weawmode.ewf
$(obj)/weawmode.ewf: $(obj)/weawmode.wds $(WEAWMODE_OBJS) FOWCE
	$(caww if_changed,wd)

OBJCOPYFWAGS_weawmode.bin := -O binawy

tawgets += weawmode.bin
$(obj)/weawmode.bin: $(obj)/weawmode.ewf $(obj)/weawmode.wewocs FOWCE
	$(caww if_changed,objcopy)

quiet_cmd_wewocs = WEWOCS  $@
      cmd_wewocs = awch/x86/toows/wewocs --weawmode $< > $@

tawgets += weawmode.wewocs
$(obj)/weawmode.wewocs: $(obj)/weawmode.ewf FOWCE
	$(caww if_changed,wewocs)

# ---------------------------------------------------------------------------

KBUIWD_CFWAGS	:= $(WEAWMODE_CFWAGS) -D_SETUP -D_WAKEUP \
		   -I$(swctwee)/awch/x86/boot
KBUIWD_AFWAGS	:= $(KBUIWD_CFWAGS) -D__ASSEMBWY__
KBUIWD_CFWAGS	+= -fno-asynchwonous-unwind-tabwes
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n
