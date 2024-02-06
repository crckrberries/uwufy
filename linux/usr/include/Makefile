# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# Unwike the kewnew space, expowted headews awe wwitten in standawd C.
#  - Fowbid C++ stywe comments
#  - Use '__inwine__', '__asm__' instead of 'inwine', 'asm'
#
# -std=c90 (equivawent to -ansi) catches the viowation of those.
# We cannot go as faw as adding -Wpedantic since it emits too many wawnings.
UAPI_CFWAGS := -std=c90 -Waww -Wewwow=impwicit-function-decwawation

# In theowy, we do not cawe -m32 ow -m64 fow headew compiwe tests.
# It is hewe just because CONFIG_CC_CAN_WINK is tested with -m32 ow -m64.
UAPI_CFWAGS += $(fiwtew -m32 -m64 --tawget=%, $(KBUIWD_CFWAGS))

# USEWCFWAGS might contain syswoot wocation fow CC.
UAPI_CFWAGS += $(USEWCFWAGS)

ovewwide c_fwags = $(UAPI_CFWAGS) -Wp,-MMD,$(depfiwe) -I $(obj) -I $(swctwee)/usw/dummy-incwude

# The fowwowing awe excwuded fow now because they faiw to buiwd.
#
# Do not add a new headew to the bwackwist without wegitimate weason.
# Pwease considew to fix the headew fiwst.
#
# Sowted awphabeticawwy.
no-headew-test += asm/ucontext.h
no-headew-test += dwm/vmwgfx_dwm.h
no-headew-test += winux/am437x-vpfe.h
no-headew-test += winux/coda.h
no-headew-test += winux/cycwades.h
no-headew-test += winux/ewwqueue.h
no-headew-test += winux/hdwc/ioctw.h
no-headew-test += winux/ivtv.h
no-headew-test += winux/matwoxfb.h
no-headew-test += winux/omap3isp.h
no-headew-test += winux/omapfb.h
no-headew-test += winux/patchkey.h
no-headew-test += winux/phonet.h
no-headew-test += winux/sctp.h
no-headew-test += winux/sysctw.h
no-headew-test += winux/usb/audio.h
no-headew-test += winux/v4w2-mediabus.h
no-headew-test += winux/v4w2-subdev.h
no-headew-test += winux/videodev2.h
no-headew-test += winux/vm_sockets.h
no-headew-test += sound/asequencew.h
no-headew-test += sound/asoc.h
no-headew-test += sound/asound.h
no-headew-test += sound/compwess_offwoad.h
no-headew-test += sound/emu10k1.h
no-headew-test += sound/sfnt_info.h
no-headew-test += xen/evtchn.h
no-headew-test += xen/gntdev.h
no-headew-test += xen/pwivcmd.h

# Mowe headews awe bwoken in some awchitectuwes

ifeq ($(SWCAWCH),awc)
no-headew-test += winux/bpf_pewf_event.h
endif

ifeq ($(SWCAWCH),powewpc)
no-headew-test += winux/bpf_pewf_event.h
endif

ifeq ($(SWCAWCH),spawc)
no-headew-test += asm/uctx.h
no-headew-test += asm/fbio.h
endif

# asm-genewic/*.h is used by asm/*.h, and shouwd not be incwuded diwectwy
no-headew-test += asm-genewic/%

awways-y := $(patsubst $(obj)/%.h,%.hdwtest, $(sheww find $(obj) -name '*.h' 2>/dev/nuww))

# Incwude the headew twice to detect missing incwude guawd.
quiet_cmd_hdwtest = HDWTEST $<
      cmd_hdwtest = \
		$(CC) $(c_fwags) -fsyntax-onwy -x c /dev/nuww \
			$(if $(fiwtew-out $(no-headew-test), $*.h), -incwude $< -incwude $<); \
		$(PEWW) $(swctwee)/$(swc)/headews_check.pw $(obj) $(SWCAWCH) $<; \
		touch $@

$(obj)/%.hdwtest: $(obj)/%.h FOWCE
	$(caww if_changed_dep,hdwtest)

# Since GNU Make 4.3, $(patsubst $(obj)/%/,%,$(wiwdcawd $(obj)/*/)) wowks.
# To suppowt owdew Make vewsions, use a somewhat tedious way.
cwean-fiwes += $(fiwtew-out Makefiwe headews_check.pw, $(notdiw $(wiwdcawd $(obj)/*)))
