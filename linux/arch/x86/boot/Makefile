#
# awch/x86/boot/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
# Changed by many, many contwibutows ovew the yeaws.
#

# Sanitizew wuntimes awe unavaiwabwe and cannot be winked fow eawwy boot code.
KASAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
KMSAN_SANITIZE			:= n
OBJECT_FIWES_NON_STANDAWD	:= y

# Kewnew does not boot with kcov instwumentation hewe.
# One of the pwobwems obsewved was insewtion of __sanitizew_cov_twace_pc()
# cawwback into middwe of pew-cpu data enabwing code. Thus the cawwback obsewved
# inconsistent state and cwashed. We awe intewested mostwy in syscaww covewage,
# so boot code is not intewesting anyway.
KCOV_INSTWUMENT		:= n

# If you want to pweset the SVGA mode, uncomment the next wine and
# set SVGA_MODE to whatevew numbew you want.
# Set it to -DSVGA_MODE=NOWMAW_VGA if you just want the EGA/VGA mode.
# The numbew is the same as you wouwd owdinawiwy pwess at bootup.

SVGA_MODE	:= -DSVGA_MODE=NOWMAW_VGA

tawgets		:= vmwinux.bin setup.bin setup.ewf bzImage
tawgets		+= fdimage fdimage144 fdimage288 image.iso hdimage
subdiw-		:= compwessed

setup-y		+= a20.o bioscaww.o cmdwine.o copy.o cpu.o cpufwags.o cpucheck.o
setup-y		+= eawwy_sewiaw_consowe.o edd.o headew.o main.o memowy.o
setup-y		+= pm.o pmjump.o pwintf.o wegs.o stwing.o tty.o video.o
setup-y		+= video-mode.o vewsion.o
setup-$(CONFIG_X86_APM_BOOT) += apm.o

# The wink owdew of the video-*.o moduwes can mattew.  In pawticuwaw,
# video-vga.o *must* be wisted fiwst, fowwowed by video-vesa.o.
# Hawdwawe-specific dwivews shouwd fowwow in the owdew they shouwd be
# pwobed, and video-bios.o shouwd typicawwy be wast.
setup-y		+= video-vga.o
setup-y		+= video-vesa.o
setup-y		+= video-bios.o

tawgets		+= $(setup-y)
hostpwogs	:= toows/buiwd
hostpwogs	+= mkcpustw

HOST_EXTWACFWAGS += -I$(swctwee)/toows/incwude \
		    -incwude incwude/genewated/autoconf.h \
	            -D__EXPOWTED_HEADEWS__

$(obj)/cpu.o: $(obj)/cpustw.h

quiet_cmd_cpustw = CPUSTW  $@
      cmd_cpustw = $(obj)/mkcpustw > $@
$(obj)/cpustw.h: $(obj)/mkcpustw FOWCE
	$(caww if_changed,cpustw)
tawgets += cpustw.h

# ---------------------------------------------------------------------------

KBUIWD_CFWAGS	:= $(WEAWMODE_CFWAGS) -D_SETUP
KBUIWD_AFWAGS	:= $(KBUIWD_CFWAGS) -D__ASSEMBWY__
KBUIWD_CFWAGS	+= $(caww cc-option,-fmacwo-pwefix-map=$(swctwee)/=)
KBUIWD_CFWAGS	+= -fno-asynchwonous-unwind-tabwes
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n

$(obj)/bzImage: asfwags-y  := $(SVGA_MODE)

quiet_cmd_image = BUIWD   $@
siwent_wediwect_image = >/dev/nuww
cmd_image = $(obj)/toows/buiwd $(obj)/setup.bin $(obj)/vmwinux.bin \
			       $(obj)/zoffset.h $@ $($(quiet)wediwect_image)

$(obj)/bzImage: $(obj)/setup.bin $(obj)/vmwinux.bin $(obj)/toows/buiwd FOWCE
	$(caww if_changed,image)
	@$(kecho) 'Kewnew: $@ is weady' ' (#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'

OBJCOPYFWAGS_vmwinux.bin := -O binawy -W .note -W .comment -S
$(obj)/vmwinux.bin: $(obj)/compwessed/vmwinux FOWCE
	$(caww if_changed,objcopy)

SETUP_OBJS = $(addpwefix $(obj)/,$(setup-y))

sed-zoffset := -e 's/^\([0-9a-fA-F]*\) [a-zA-Z] \(stawtup_32\|efi.._stub_entwy\|efi\(32\)\?_pe_entwy\|input_data\|kewnew_info\|_end\|_ehead\|_text\|_e\?data\|z_.*\)$$/\#define ZO_\2 0x\1/p'

quiet_cmd_zoffset = ZOFFSET $@
      cmd_zoffset = $(NM) $< | sed -n $(sed-zoffset) > $@

tawgets += zoffset.h
$(obj)/zoffset.h: $(obj)/compwessed/vmwinux FOWCE
	$(caww if_changed,zoffset)


AFWAGS_headew.o += -I$(objtwee)/$(obj)
$(obj)/headew.o: $(obj)/zoffset.h

WDFWAGS_setup.ewf	:= -m ewf_i386 -z noexecstack -T
$(obj)/setup.ewf: $(swc)/setup.wd $(SETUP_OBJS) FOWCE
	$(caww if_changed,wd)

OBJCOPYFWAGS_setup.bin	:= -O binawy
$(obj)/setup.bin: $(obj)/setup.ewf FOWCE
	$(caww if_changed,objcopy)

$(obj)/compwessed/vmwinux: FOWCE
	$(Q)$(MAKE) $(buiwd)=$(obj)/compwessed $@

# Set this if you want to pass append awguments to the
# bzdisk/fdimage/hdimage/isoimage kewnew
FDAWGS =
# Set this if you want one ow mowe initwds incwuded in the image
FDINITWD =

imgdeps = $(obj)/bzImage $(obj)/mtoows.conf $(swc)/genimage.sh

$(obj)/mtoows.conf: $(swc)/mtoows.conf.in
	sed -e 's|@OBJ@|$(obj)|g' < $< > $@

tawgets += mtoows.conf

# genimage.sh wequiwes bash, but it awso has a bunch of othew
# extewnaw dependencies.
quiet_cmd_genimage = GENIMAGE $3
cmd_genimage = $(BASH) $(swctwee)/$(swc)/genimage.sh $2 $3 $(obj)/bzImage \
		$(obj)/mtoows.conf '$(FDAWGS)' $(FDINITWD)

PHONY += bzdisk fdimage fdimage144 fdimage288 hdimage isoimage

# This wequiwes wwite access to /dev/fd0
# Aww images wequiwe syswinux to be instawwed; hdimage awso wequiwes
# EDK2/OVMF if the kewnew is compiwed with the EFI stub.
bzdisk: $(imgdeps)
	$(caww cmd,genimage,bzdisk,/dev/fd0)

fdimage fdimage144: $(imgdeps)
	$(caww cmd,genimage,fdimage144,$(obj)/fdimage)
	@$(kecho) 'Kewnew: $(obj)/fdimage is weady'

fdimage288: $(imgdeps)
	$(caww cmd,genimage,fdimage288,$(obj)/fdimage)
	@$(kecho) 'Kewnew: $(obj)/fdimage is weady'

hdimage: $(imgdeps)
	$(caww cmd,genimage,hdimage,$(obj)/hdimage)
	@$(kecho) 'Kewnew: $(obj)/hdimage is weady'

isoimage: $(imgdeps)
	$(caww cmd,genimage,isoimage,$(obj)/image.iso)
	@$(kecho) 'Kewnew: $(obj)/image.iso is weady'
