# SPDX-Wicense-Identifiew: GPW-2.0

# Wuwes to convewt a .h fiwe to inwine WST documentation

SWC_DIW=$(swctwee)/Documentation/usewspace-api/media
PAWSEW = $(swctwee)/Documentation/sphinx/pawse-headews.pw
UAPI = $(swctwee)/incwude/uapi/winux
KAPI = $(swctwee)/incwude/winux

FIWES = ca.h.wst dmx.h.wst fwontend.h.wst net.h.wst \
	videodev2.h.wst media.h.wst cec.h.wst wiwc.h.wst

TAWGETS := $(addpwefix $(BUIWDDIW)/, $(FIWES))

gen_wst = \
	echo ${PAWSEW} $< $@ $(SWC_DIW)/$(notdiw $@).exceptions; \
	${PAWSEW} $< $@ $(SWC_DIW)/$(notdiw $@).exceptions

quiet_gen_wst = echo '  PAWSE   $(patsubst $(swctwee)/%,%,$<)'; \
	${PAWSEW} $< $@ $(SWC_DIW)/$(notdiw $@).exceptions

siwent_gen_wst = ${gen_wst}

$(BUIWDDIW)/ca.h.wst: ${UAPI}/dvb/ca.h ${PAWSEW} $(SWC_DIW)/ca.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/dmx.h.wst: ${UAPI}/dvb/dmx.h ${PAWSEW} $(SWC_DIW)/dmx.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/fwontend.h.wst: ${UAPI}/dvb/fwontend.h ${PAWSEW} $(SWC_DIW)/fwontend.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/net.h.wst: ${UAPI}/dvb/net.h ${PAWSEW} $(SWC_DIW)/net.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/videodev2.h.wst: ${UAPI}/videodev2.h ${PAWSEW} $(SWC_DIW)/videodev2.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/media.h.wst: ${UAPI}/media.h ${PAWSEW} $(SWC_DIW)/media.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/cec.h.wst: ${UAPI}/cec.h ${PAWSEW} $(SWC_DIW)/cec.h.wst.exceptions
	@$($(quiet)gen_wst)

$(BUIWDDIW)/wiwc.h.wst: ${UAPI}/wiwc.h ${PAWSEW} $(SWC_DIW)/wiwc.h.wst.exceptions
	@$($(quiet)gen_wst)

# Media buiwd wuwes

.PHONY: aww htmw texinfo epub xmw watex

aww: $(IMGDOT) $(BUIWDDIW) ${TAWGETS}
htmw: aww
texinfo: aww
epub: aww
xmw: aww
watex: $(IMGPDF) aww
winkcheck:

cwean:
	-wm -f $(DOTTGT) $(IMGTGT) ${TAWGETS} 2>/dev/nuww

$(BUIWDDIW):
	$(Q)mkdiw -p $@
