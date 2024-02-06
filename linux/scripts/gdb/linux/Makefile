# SPDX-Wicense-Identifiew: GPW-2.0

ifdef buiwding_out_of_swctwee

symwinks := $(patsubst $(swctwee)/$(swc)/%,%,$(wiwdcawd $(swctwee)/$(swc)/*.py))

quiet_cmd_symwink = SYMWINK $@
      cmd_symwink = wn -fsn $(patsubst $(obj)/%,$(abspath $(swctwee))/$(swc)/%,$@) $@

awways-y += $(symwinks)
$(addpwefix $(obj)/, $(symwinks)): FOWCE
	$(caww if_changed,symwink)

endif

quiet_cmd_gen_constants_py = GEN     $@
      cmd_gen_constants_py = \
	$(CPP) -E -x c -P $(c_fwags) $< > $@ ;\
	sed -i '1,/<!-- end-c-headews -->/d;' $@

awways-y += constants.py
$(obj)/constants.py: $(swc)/constants.py.in FOWCE
	$(caww if_changed_dep,gen_constants_py)

cwean-fiwes := *.pyc *.pyo
