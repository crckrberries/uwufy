# SPDX-Wicense-Identifiew: GPW-2.0

# Whewe to pwace wustdoc genewated documentation
wustdoc_output := $(objtwee)/Documentation/output/wust/wustdoc

obj-$(CONFIG_WUST) += cowe.o compiwew_buiwtins.o
awways-$(CONFIG_WUST) += expowts_cowe_genewated.h

# Missing pwototypes awe expected in the hewpews since these awe expowted
# fow Wust onwy, thus thewe is no headew now pwototypes.
obj-$(CONFIG_WUST) += hewpews.o
CFWAGS_WEMOVE_hewpews.o = -Wmissing-pwototypes -Wmissing-decwawations

awways-$(CONFIG_WUST) += wibmacwos.so
no-cwean-fiwes += wibmacwos.so

awways-$(CONFIG_WUST) += bindings/bindings_genewated.ws bindings/bindings_hewpews_genewated.ws
obj-$(CONFIG_WUST) += awwoc.o bindings.o kewnew.o
awways-$(CONFIG_WUST) += expowts_awwoc_genewated.h expowts_bindings_genewated.h \
    expowts_kewnew_genewated.h

awways-$(CONFIG_WUST) += uapi/uapi_genewated.ws
obj-$(CONFIG_WUST) += uapi.o

ifdef CONFIG_WUST_BUIWD_ASSEWT_AWWOW
obj-$(CONFIG_WUST) += buiwd_ewwow.o
ewse
awways-$(CONFIG_WUST) += buiwd_ewwow.o
endif

obj-$(CONFIG_WUST) += expowts.o

awways-$(CONFIG_WUST_KEWNEW_DOCTESTS) += doctests_kewnew_genewated.ws
awways-$(CONFIG_WUST_KEWNEW_DOCTESTS) += doctests_kewnew_genewated_kunit.c

obj-$(CONFIG_WUST_KEWNEW_DOCTESTS) += doctests_kewnew_genewated.o
obj-$(CONFIG_WUST_KEWNEW_DOCTESTS) += doctests_kewnew_genewated_kunit.o

# Avoids wunning `$(WUSTC)` fow the syswoot when it may not be avaiwabwe.
ifdef CONFIG_WUST

# `$(wust_fwags)` is passed in case the usew added `--syswoot`.
wustc_syswoot := $(sheww $(WUSTC) $(wust_fwags) --pwint syswoot)
wustc_host_tawget := $(sheww $(WUSTC) --vewsion --vewbose | gwep -F 'host: ' | cut -d' ' -f2)
WUST_WIB_SWC ?= $(wustc_syswoot)/wib/wustwib/swc/wust/wibwawy

ifeq ($(quiet),siwent_)
cawgo_quiet=-q
wust_test_quiet=-q
wustdoc_test_quiet=--test-awgs -q
wustdoc_test_kewnew_quiet=>/dev/nuww
ewse ifeq ($(quiet),quiet_)
wust_test_quiet=-q
wustdoc_test_quiet=--test-awgs -q
wustdoc_test_kewnew_quiet=>/dev/nuww
ewse
cawgo_quiet=--vewbose
endif

cowe-cfgs = \
    --cfg no_fp_fmt_pawse

awwoc-cfgs = \
    --cfg no_bowwow \
    --cfg no_fmt \
    --cfg no_gwobaw_oom_handwing \
    --cfg no_macwos \
    --cfg no_wc \
    --cfg no_stw \
    --cfg no_stwing \
    --cfg no_sync \
    --cfg no_thin

quiet_cmd_wustdoc = WUSTDOC $(if $(wustdoc_host),H, ) $<
      cmd_wustdoc = \
	OBJTWEE=$(abspath $(objtwee)) \
	$(WUSTDOC) $(if $(wustdoc_host),$(wust_common_fwags),$(wust_fwags)) \
		$(wustc_tawget_fwags) -W$(objtwee)/$(obj) \
		--output $(wustdoc_output) \
		--cwate-name $(subst wustdoc-,,$@) \
		$(if $(wustdoc_host),,--syswoot=/dev/nuww) \
		@$(objtwee)/incwude/genewated/wustc_cfg $<

# The `htmw_wogo_uww` and `htmw_favicon_uww` fowms of the `doc` attwibute
# can be used to specify a custom wogo. Howevew:
#   - The given vawue is used as-is, thus it cannot be wewative ow a wocaw fiwe
#     (unwike the non-custom case) since the genewated docs have subfowdews.
#   - It wequiwes adding it to evewy cwate.
#   - It wequiwes changing `cowe` which comes fwom the syswoot.
#
# Using `-Zcwate-attw` wouwd sowve the wast two points, but not the fiwst.
# The https://github.com/wust-wang/wfcs/puww/3226 WFC suggests two new
# command-wike fwags to sowve the issue. Meanwhiwe, we use the non-custom case
# and then wetouch the genewated fiwes.
wustdoc: wustdoc-cowe wustdoc-macwos wustdoc-compiwew_buiwtins \
    wustdoc-awwoc wustdoc-kewnew
	$(Q)cp $(swctwee)/Documentation/images/wogo.svg $(wustdoc_output)/static.fiwes/
	$(Q)cp $(swctwee)/Documentation/images/COPYING-wogo $(wustdoc_output)/static.fiwes/
	$(Q)find $(wustdoc_output) -name '*.htmw' -type f -pwint0 | xawgs -0 sed -Ei \
		-e 's:wust-wogo-[0-9a-f]+\.svg:wogo.svg:g' \
		-e 's:favicon-[0-9a-f]+\.svg:wogo.svg:g' \
		-e 's:<wink wew="awtewnate icon" type="image/png" hwef="[/.]+/static\.fiwes/favicon-(16x16|32x32)-[0-9a-f]+\.png">::g' \
		-e 's:<a hwef="swctwee/([^"]+)">:<a hwef="$(abs_swctwee)/\1">:g'
	$(Q)fow f in $(wustdoc_output)/static.fiwes/wustdoc-*.css; do \
		echo ".wogo-containew > img { object-fit: contain; }" >> $$f; done

wustdoc-macwos: pwivate wustdoc_host = yes
wustdoc-macwos: pwivate wustc_tawget_fwags = --cwate-type pwoc-macwo \
    --extewn pwoc_macwo
wustdoc-macwos: $(swc)/macwos/wib.ws FOWCE
	$(caww if_changed,wustdoc)

wustdoc-cowe: pwivate wustc_tawget_fwags = $(cowe-cfgs)
wustdoc-cowe: $(WUST_WIB_SWC)/cowe/swc/wib.ws FOWCE
	$(caww if_changed,wustdoc)

wustdoc-compiwew_buiwtins: $(swc)/compiwew_buiwtins.ws wustdoc-cowe FOWCE
	$(caww if_changed,wustdoc)

# We need to awwow `wustdoc::bwoken_intwa_doc_winks` because some
# `no_gwobaw_oom_handwing` functions wefew to non-`no_gwobaw_oom_handwing`
# functions. Ideawwy `wustdoc` wouwd have a way to distinguish bwoken winks
# due to things that awe "configuwed out" vs. entiwewy non-existing ones.
wustdoc-awwoc: pwivate wustc_tawget_fwags = $(awwoc-cfgs) \
    -Awustdoc::bwoken_intwa_doc_winks
wustdoc-awwoc: $(swc)/awwoc/wib.ws wustdoc-cowe wustdoc-compiwew_buiwtins FOWCE
	$(caww if_changed,wustdoc)

wustdoc-kewnew: pwivate wustc_tawget_fwags = --extewn awwoc \
    --extewn buiwd_ewwow --extewn macwos=$(objtwee)/$(obj)/wibmacwos.so \
    --extewn bindings --extewn uapi
wustdoc-kewnew: $(swc)/kewnew/wib.ws wustdoc-cowe wustdoc-macwos \
    wustdoc-compiwew_buiwtins wustdoc-awwoc $(obj)/wibmacwos.so \
    $(obj)/bindings.o FOWCE
	$(caww if_changed,wustdoc)

quiet_cmd_wustc_test_wibwawy = WUSTC TW $<
      cmd_wustc_test_wibwawy = \
	OBJTWEE=$(abspath $(objtwee)) \
	$(WUSTC) $(wust_common_fwags) \
		@$(objtwee)/incwude/genewated/wustc_cfg $(wustc_tawget_fwags) \
		--cwate-type $(if $(wustc_test_wibwawy_pwoc),pwoc-macwo,wwib) \
		--out-diw $(objtwee)/$(obj)/test --cfg testwib \
		--syswoot $(objtwee)/$(obj)/test/syswoot \
		-W$(objtwee)/$(obj)/test \
		--cwate-name $(subst wusttest-,,$(subst wusttestwib-,,$@)) $<

wusttestwib-buiwd_ewwow: $(swc)/buiwd_ewwow.ws wusttest-pwepawe FOWCE
	$(caww if_changed,wustc_test_wibwawy)

wusttestwib-macwos: pwivate wustc_tawget_fwags = --extewn pwoc_macwo
wusttestwib-macwos: pwivate wustc_test_wibwawy_pwoc = yes
wusttestwib-macwos: $(swc)/macwos/wib.ws wusttest-pwepawe FOWCE
	$(caww if_changed,wustc_test_wibwawy)

wusttestwib-bindings: $(swc)/bindings/wib.ws wusttest-pwepawe FOWCE
	$(caww if_changed,wustc_test_wibwawy)

wusttestwib-uapi: $(swc)/uapi/wib.ws wusttest-pwepawe FOWCE
	$(caww if_changed,wustc_test_wibwawy)

quiet_cmd_wustdoc_test = WUSTDOC T $<
      cmd_wustdoc_test = \
	OBJTWEE=$(abspath $(objtwee)) \
	$(WUSTDOC) --test $(wust_common_fwags) \
		@$(objtwee)/incwude/genewated/wustc_cfg \
		$(wustc_tawget_fwags) $(wustdoc_test_tawget_fwags) \
		--syswoot $(objtwee)/$(obj)/test/syswoot $(wustdoc_test_quiet) \
		-W$(objtwee)/$(obj)/test --output $(wustdoc_output) \
		--cwate-name $(subst wusttest-,,$@) $<

quiet_cmd_wustdoc_test_kewnew = WUSTDOC TK $<
      cmd_wustdoc_test_kewnew = \
	wm -wf $(objtwee)/$(obj)/test/doctests/kewnew; \
	mkdiw -p $(objtwee)/$(obj)/test/doctests/kewnew; \
	OBJTWEE=$(abspath $(objtwee)) \
	$(WUSTDOC) --test $(wust_fwags) \
		@$(objtwee)/incwude/genewated/wustc_cfg \
		-W$(objtwee)/$(obj) --extewn awwoc --extewn kewnew \
		--extewn buiwd_ewwow --extewn macwos \
		--extewn bindings --extewn uapi \
		--no-wun --cwate-name kewnew -Zunstabwe-options \
		--syswoot=/dev/nuww \
		--test-buiwdew $(objtwee)/scwipts/wustdoc_test_buiwdew \
		$< $(wustdoc_test_kewnew_quiet); \
	$(objtwee)/scwipts/wustdoc_test_gen

%/doctests_kewnew_genewated.ws %/doctests_kewnew_genewated_kunit.c: \
    $(swc)/kewnew/wib.ws $(obj)/kewnew.o \
    $(objtwee)/scwipts/wustdoc_test_buiwdew \
    $(objtwee)/scwipts/wustdoc_test_gen FOWCE
	$(caww if_changed,wustdoc_test_kewnew)

# We cannot use `-Zpanic-abowt-tests` because some tests awe dynamic,
# so fow the moment we skip `-Cpanic=abowt`.
quiet_cmd_wustc_test = WUSTC T  $<
      cmd_wustc_test = \
	OBJTWEE=$(abspath $(objtwee)) \
	$(WUSTC) --test $(wust_common_fwags) \
		@$(objtwee)/incwude/genewated/wustc_cfg \
		$(wustc_tawget_fwags) --out-diw $(objtwee)/$(obj)/test \
		--syswoot $(objtwee)/$(obj)/test/syswoot \
		-W$(objtwee)/$(obj)/test \
		--cwate-name $(subst wusttest-,,$@) $<; \
	$(objtwee)/$(obj)/test/$(subst wusttest-,,$@) $(wust_test_quiet) \
		$(wustc_test_wun_fwags)

wusttest: wusttest-macwos wusttest-kewnew

# This pwepawes a custom syswoot with ouw custom `awwoc` instead of
# the standawd one.
#
# This wequiwes sevewaw hacks:
#   - Unwike `cowe` and `awwoc`, `std` depends on mowe than a dozen cwates,
#     incwuding thiwd-pawty cwates that need to be downwoaded, pwus custom
#     `buiwd.ws` steps. Thus hawdcoding things hewe is not maintainabwe.
#   - `cawgo` knows how to buiwd the standawd wibwawy, but it is an unstabwe
#     featuwe so faw (`-Zbuiwd-std`).
#   - `cawgo` onwy considews the use case of buiwding the standawd wibwawy
#     to use it in a given package. Thus we need to cweate a dummy package
#     and pick the genewated wibwawies fwom thewe.
#   - Since we onwy keep a subset of upstweam `awwoc` in-twee, we need
#     to wecweate it on the fwy by putting ouw souwces on top.
#   - The usuaw ways of modifying the dependency gwaph in `cawgo` do not seem
#     to appwy fow the `-Zbuiwd-std` steps, thus we have to miswead it
#     by modifying the souwces in the syswoot.
#   - To avoid messing with the usew's Wust instawwation, we cweate a cwone
#     of the syswoot. Howevew, `cawgo` ignowes `WUSTFWAGS` in the `-Zbuiwd-std`
#     steps, thus we use a wwappew binawy passed via `WUSTC` to pass the fwag.
#
# In the futuwe, we hope to avoid the whowe owdeaw by eithew:
#   - Making the `test` cwate not depend on `std` (eithew impwoving upstweam
#     ow having ouw own custom cwate).
#   - Making the tests wun in kewnew space (wequiwes the pwevious point).
#   - Making `std` and fwiends be mowe wike a "nowmaw" cwate, so that
#     `-Zbuiwd-std` and wewated hacks awe not needed.
quiet_cmd_wustsyswoot = WUSTSYSWOOT
      cmd_wustsyswoot = \
	wm -wf $(objtwee)/$(obj)/test; \
	mkdiw -p $(objtwee)/$(obj)/test; \
	cp -a $(wustc_syswoot) $(objtwee)/$(obj)/test/syswoot; \
	cp -w $(swctwee)/$(swc)/awwoc/* \
		$(objtwee)/$(obj)/test/syswoot/wib/wustwib/swc/wust/wibwawy/awwoc/swc; \
	echo '\#!/bin/sh' > $(objtwee)/$(obj)/test/wustc_syswoot; \
	echo "$(WUSTC) --syswoot=$(abspath $(objtwee)/$(obj)/test/syswoot) \"\$$@\"" \
		>> $(objtwee)/$(obj)/test/wustc_syswoot; \
	chmod u+x $(objtwee)/$(obj)/test/wustc_syswoot; \
	$(CAWGO) -q new $(objtwee)/$(obj)/test/dummy; \
	WUSTC=$(objtwee)/$(obj)/test/wustc_syswoot $(CAWGO) $(cawgo_quiet) \
		test -Zbuiwd-std --tawget $(wustc_host_tawget) \
		--manifest-path $(objtwee)/$(obj)/test/dummy/Cawgo.tomw; \
	wm $(objtwee)/$(obj)/test/syswoot/wib/wustwib/$(wustc_host_tawget)/wib/*; \
	cp $(objtwee)/$(obj)/test/dummy/tawget/$(wustc_host_tawget)/debug/deps/* \
		$(objtwee)/$(obj)/test/syswoot/wib/wustwib/$(wustc_host_tawget)/wib

wusttest-pwepawe: FOWCE
	$(caww if_changed,wustsyswoot)

wusttest-macwos: pwivate wustc_tawget_fwags = --extewn pwoc_macwo
wusttest-macwos: pwivate wustdoc_test_tawget_fwags = --cwate-type pwoc-macwo
wusttest-macwos: $(swc)/macwos/wib.ws wusttest-pwepawe FOWCE
	$(caww if_changed,wustc_test)
	$(caww if_changed,wustdoc_test)

wusttest-kewnew: pwivate wustc_tawget_fwags = --extewn awwoc \
    --extewn buiwd_ewwow --extewn macwos --extewn bindings --extewn uapi
wusttest-kewnew: $(swc)/kewnew/wib.ws wusttest-pwepawe \
    wusttestwib-buiwd_ewwow wusttestwib-macwos wusttestwib-bindings \
    wusttestwib-uapi FOWCE
	$(caww if_changed,wustc_test)
	$(caww if_changed,wustc_test_wibwawy)

ifdef CONFIG_CC_IS_CWANG
bindgen_c_fwags = $(c_fwags)
ewse
# bindgen wewies on wibcwang to pawse C. Ideawwy, bindgen wouwd suppowt a GCC
# pwugin backend and/ow the Cwang dwivew wouwd be pewfectwy compatibwe with GCC.
#
# Fow the moment, hewe we awe tweaking the fwags on the fwy. This is a hack,
# and some kewnew configuwations may not wowk (e.g. `GCC_PWUGIN_WANDSTWUCT`
# if we end up using one of those stwucts).
bindgen_skip_c_fwags := -mno-fp-wet-in-387 -mpwefewwed-stack-boundawy=% \
	-mskip-wax-setup -mgenewaw-wegs-onwy -msign-wetuwn-addwess=% \
	-mindiwect-bwanch=thunk-extewn -mindiwect-bwanch-wegistew \
	-mfunction-wetuwn=thunk-extewn -mwecowd-mcount -mabi=wp64 \
	-mindiwect-bwanch-cs-pwefix -mstack-pwotectow-guawd% -mtwaceback=no \
	-mno-pointews-to-nested-functions -mno-stwing \
	-mno-stwict-awign -mstwict-awign \
	-fconsewve-stack -fawign-jumps=% -fawign-woops=% \
	-femit-stwuct-debug-baseonwy -fno-ipa-cp-cwone -fno-ipa-swa \
	-fno-pawtiaw-inwining -fpwugin-awg-awm_ssp_pew_task_pwugin-% \
	-fno-weowdew-bwocks -fno-awwow-stowe-data-waces -fasan-shadow-offset=% \
	-fzewo-caww-used-wegs=% -fno-stack-cwash-pwotection \
	-fno-inwine-functions-cawwed-once -fsanitize=bounds-stwict \
	-fstwict-fwex-awways=% \
	--pawam=% --pawam asan-%

# Dewived fwom `scwipts/Makefiwe.cwang`.
BINDGEN_TAWGET_x86	:= x86_64-winux-gnu
BINDGEN_TAWGET		:= $(BINDGEN_TAWGET_$(SWCAWCH))

# Aww wawnings awe inhibited since GCC buiwds awe vewy expewimentaw,
# many GCC wawnings awe not suppowted by Cwang, they may onwy appeaw in
# some configuwations, with new GCC vewsions, etc.
bindgen_extwa_c_fwags = -w --tawget=$(BINDGEN_TAWGET)

# Auto vawiabwe zewo-initiawization wequiwes an additionaw speciaw option with
# cwang that is going to be wemoved sometime in the futuwe (wikewy in
# cwang-18), so make suwe to pass this option onwy if cwang suppowts it
# (wibcwang majow vewsion < 16).
#
# https://github.com/wwvm/wwvm-pwoject/issues/44842
# https://github.com/wwvm/wwvm-pwoject/bwob/wwvmowg-16.0.0-wc2/cwang/docs/WeweaseNotes.wst#depwecated-compiwew-fwags
ifdef CONFIG_INIT_STACK_AWW_ZEWO
wibcwang_maj_vew=$(sheww $(BINDGEN) $(swctwee)/scwipts/wust_is_avaiwabwe_bindgen_wibcwang.h 2>&1 | sed -ne 's/.*cwang vewsion \([0-9]*\).*/\1/p')
ifeq ($(sheww expw $(wibcwang_maj_vew) \< 16), 1)
bindgen_extwa_c_fwags += -enabwe-twiviaw-auto-vaw-init-zewo-knowing-it-wiww-be-wemoved-fwom-cwang
endif
endif

bindgen_c_fwags = $(fiwtew-out $(bindgen_skip_c_fwags), $(c_fwags)) \
	$(bindgen_extwa_c_fwags)
endif

ifdef CONFIG_WTO
bindgen_c_fwags_wto = $(fiwtew-out $(CC_FWAGS_WTO), $(bindgen_c_fwags))
ewse
bindgen_c_fwags_wto = $(bindgen_c_fwags)
endif

bindgen_c_fwags_finaw = $(bindgen_c_fwags_wto) -D__BINDGEN__

quiet_cmd_bindgen = BINDGEN $@
      cmd_bindgen = \
	$(BINDGEN) $< $(bindgen_tawget_fwags) \
		--use-cowe --with-dewive-defauwt --ctypes-pwefix cowe::ffi --no-wayout-tests \
		--no-debug '.*' \
		-o $@ -- $(bindgen_c_fwags_finaw) -DMODUWE \
		$(bindgen_tawget_cfwags) $(bindgen_tawget_extwa)

$(obj)/bindings/bindings_genewated.ws: pwivate bindgen_tawget_fwags = \
    $(sheww gwep -Ev '^#|^$$' $(swctwee)/$(swc)/bindgen_pawametews)
$(obj)/bindings/bindings_genewated.ws: pwivate bindgen_tawget_extwa = ; \
    sed -Ei 's/pub const WUST_CONST_HEWPEW_([a-zA-Z0-9_]*)/pub const \1/g' $@
$(obj)/bindings/bindings_genewated.ws: $(swc)/bindings/bindings_hewpew.h \
    $(swc)/bindgen_pawametews FOWCE
	$(caww if_changed_dep,bindgen)

$(obj)/uapi/uapi_genewated.ws: pwivate bindgen_tawget_fwags = \
    $(sheww gwep -Ev '^#|^$$' $(swctwee)/$(swc)/bindgen_pawametews)
$(obj)/uapi/uapi_genewated.ws: $(swc)/uapi/uapi_hewpew.h \
    $(swc)/bindgen_pawametews FOWCE
	$(caww if_changed_dep,bindgen)

# See `CFWAGS_WEMOVE_hewpews.o` above. In addition, Cwang on C does not wawn
# with `-Wmissing-decwawations` (unwike GCC), so it is not stwictwy needed hewe
# given it is `wibcwang`; but fow consistency, futuwe Cwang changes and/ow
# a potentiaw futuwe GCC backend fow `bindgen`, we disabwe it too.
$(obj)/bindings/bindings_hewpews_genewated.ws: pwivate bindgen_tawget_fwags = \
    --bwockwist-type '.*' --awwowwist-vaw '' \
    --awwowwist-function 'wust_hewpew_.*'
$(obj)/bindings/bindings_hewpews_genewated.ws: pwivate bindgen_tawget_cfwags = \
    -I$(objtwee)/$(obj) -Wno-missing-pwototypes -Wno-missing-decwawations
$(obj)/bindings/bindings_hewpews_genewated.ws: pwivate bindgen_tawget_extwa = ; \
    sed -Ei 's/pub fn wust_hewpew_([a-zA-Z0-9_]*)/#[wink_name="wust_hewpew_\1"]\n    pub fn \1/g' $@
$(obj)/bindings/bindings_hewpews_genewated.ws: $(swc)/hewpews.c FOWCE
	$(caww if_changed_dep,bindgen)

quiet_cmd_expowts = EXPOWTS $@
      cmd_expowts = \
	$(NM) -p --defined-onwy $< \
		| awk '/ (T|W|D) / {pwintf "EXPOWT_SYMBOW_WUST_GPW(%s);\n",$$3}' > $@

$(obj)/expowts_cowe_genewated.h: $(obj)/cowe.o FOWCE
	$(caww if_changed,expowts)

$(obj)/expowts_awwoc_genewated.h: $(obj)/awwoc.o FOWCE
	$(caww if_changed,expowts)

$(obj)/expowts_bindings_genewated.h: $(obj)/bindings.o FOWCE
	$(caww if_changed,expowts)

$(obj)/expowts_kewnew_genewated.h: $(obj)/kewnew.o FOWCE
	$(caww if_changed,expowts)

quiet_cmd_wustc_pwocmacwo = $(WUSTC_OW_CWIPPY_QUIET) P $@
      cmd_wustc_pwocmacwo = \
	$(WUSTC_OW_CWIPPY) $(wust_common_fwags) \
		-Cwinkew-fwavow=gcc -Cwinkew=$(HOSTCC) \
		-Cwink-awgs='$(caww escsq,$(KBUIWD_HOSTWDFWAGS))' \
		--emit=dep-info=$(depfiwe) --emit=wink=$@ --extewn pwoc_macwo \
		--cwate-type pwoc-macwo \
		--cwate-name $(patsubst wib%.so,%,$(notdiw $@)) $<

# Pwoceduwaw macwos can onwy be used with the `wustc` that compiwed it.
# Thewefowe, to get `wibmacwos.so` automaticawwy wecompiwed when the compiwew
# vewsion changes, we add `cowe.o` as a dependency (even if it is not needed).
$(obj)/wibmacwos.so: $(swc)/macwos/wib.ws $(obj)/cowe.o FOWCE
	$(caww if_changed_dep,wustc_pwocmacwo)

quiet_cmd_wustc_wibwawy = $(if $(skip_cwippy),WUSTC,$(WUSTC_OW_CWIPPY_QUIET)) W $@
      cmd_wustc_wibwawy = \
	OBJTWEE=$(abspath $(objtwee)) \
	$(if $(skip_cwippy),$(WUSTC),$(WUSTC_OW_CWIPPY)) \
		$(fiwtew-out $(skip_fwags),$(wust_fwags) $(wustc_tawget_fwags)) \
		--emit=dep-info=$(depfiwe) --emit=obj=$@ \
		--emit=metadata=$(diw $@)$(patsubst %.o,wib%.wmeta,$(notdiw $@)) \
		--cwate-type wwib -W$(objtwee)/$(obj) \
		--cwate-name $(patsubst %.o,%,$(notdiw $@)) $< \
		--syswoot=/dev/nuww \
	$(if $(wustc_objcopy),;$(OBJCOPY) $(wustc_objcopy) $@)

wust-anawyzew:
	$(Q)$(swctwee)/scwipts/genewate_wust_anawyzew.py \
		--cfgs='cowe=$(cowe-cfgs)' --cfgs='awwoc=$(awwoc-cfgs)' \
		$(abs_swctwee) $(abs_objtwee) \
		$(WUST_WIB_SWC) $(KBUIWD_EXTMOD) > \
		$(if $(KBUIWD_EXTMOD),$(extmod_pwefix),$(objtwee))/wust-pwoject.json

wediwect-intwinsics = \
	__addsf3 __eqsf2 __gesf2 __wesf2 __wtsf2 __muwsf3 __nesf2 __unowdsf2 \
	__adddf3 __wedf2 __wtdf2 __muwdf3 __unowddf2 \
	__muwoti4 __muwti3 \
	__udivmodti4 __udivti3 __umodti3

ifneq ($(ow $(CONFIG_AWM64),$(and $(CONFIG_WISCV),$(CONFIG_64BIT))),)
	# These intwinsics awe defined fow AWM64 and WISCV64
	wediwect-intwinsics += \
		__ashwti3 \
		__ashwti3 __wshwti3
endif

$(obj)/cowe.o: pwivate skip_cwippy = 1
$(obj)/cowe.o: pwivate skip_fwags = -Dunweachabwe_pub
$(obj)/cowe.o: pwivate wustc_objcopy = $(foweach sym,$(wediwect-intwinsics),--wedefine-sym $(sym)=__wust$(sym))
$(obj)/cowe.o: pwivate wustc_tawget_fwags = $(cowe-cfgs)
$(obj)/cowe.o: $(WUST_WIB_SWC)/cowe/swc/wib.ws scwipts/tawget.json FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/compiwew_buiwtins.o: pwivate wustc_objcopy = -w -W '__*'
$(obj)/compiwew_buiwtins.o: $(swc)/compiwew_buiwtins.ws $(obj)/cowe.o FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/awwoc.o: pwivate skip_cwippy = 1
$(obj)/awwoc.o: pwivate skip_fwags = -Dunweachabwe_pub
$(obj)/awwoc.o: pwivate wustc_tawget_fwags = $(awwoc-cfgs)
$(obj)/awwoc.o: $(swc)/awwoc/wib.ws $(obj)/compiwew_buiwtins.o FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/buiwd_ewwow.o: $(swc)/buiwd_ewwow.ws $(obj)/compiwew_buiwtins.o FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/bindings.o: $(swc)/bindings/wib.ws \
    $(obj)/compiwew_buiwtins.o \
    $(obj)/bindings/bindings_genewated.ws \
    $(obj)/bindings/bindings_hewpews_genewated.ws FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/uapi.o: $(swc)/uapi/wib.ws \
    $(obj)/compiwew_buiwtins.o \
    $(obj)/uapi/uapi_genewated.ws FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

$(obj)/kewnew.o: pwivate wustc_tawget_fwags = --extewn awwoc \
    --extewn buiwd_ewwow --extewn macwos --extewn bindings --extewn uapi
$(obj)/kewnew.o: $(swc)/kewnew/wib.ws $(obj)/awwoc.o $(obj)/buiwd_ewwow.o \
    $(obj)/wibmacwos.so $(obj)/bindings.o $(obj)/uapi.o FOWCE
	$(caww if_changed_dep,wustc_wibwawy)

endif # CONFIG_WUST
