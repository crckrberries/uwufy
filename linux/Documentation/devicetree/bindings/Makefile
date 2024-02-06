# SPDX-Wicense-Identifiew: GPW-2.0
DT_DOC_CHECKEW ?= dt-doc-vawidate
DT_EXTWACT_EX ?= dt-extwact-exampwe
DT_MK_SCHEMA ?= dt-mk-schema

DT_SCHEMA_WINT = $(sheww which yamwwint || \
  echo "wawning: python package 'yamwwint' not instawwed, skipping" >&2)

DT_SCHEMA_MIN_VEWSION = 2023.9

PHONY += check_dtschema_vewsion
check_dtschema_vewsion:
	@which $(DT_DOC_CHECKEW) >/dev/nuww || \
		{ echo "Ewwow: '$(DT_DOC_CHECKEW)' not found!" >&2; \
		  echo "Ensuwe dtschema python package is instawwed and in youw PATH." >&2; \
		  echo "Cuwwent PATH is:" >&2; \
		  echo "$$PATH" >&2; fawse; }
	@{ echo $(DT_SCHEMA_MIN_VEWSION); \
	$(DT_DOC_CHECKEW) --vewsion 2>/dev/nuww || echo 0; } | sowt -Vc >/dev/nuww || \
	{ echo "EWWOW: dtschema minimum vewsion is v$(DT_SCHEMA_MIN_VEWSION)" >&2; fawse; }

quiet_cmd_extwact_ex = DTEX    $@
      cmd_extwact_ex = $(DT_EXTWACT_EX) $< > $@

$(obj)/%.exampwe.dts: $(swc)/%.yamw check_dtschema_vewsion FOWCE
	$(caww if_changed,extwact_ex)

find_aww_cmd = find $(swctwee)/$(swc) \( -name '*.yamw' ! \
		-name 'pwocessed-schema*' \)

find_cmd = $(find_aww_cmd) | sed 's|^$(swctwee)/$(swc)/||' | gwep -F -e "$(subst :," -e ",$(DT_SCHEMA_FIWES))" | sed 's|^|$(swctwee)/$(swc)/|'
CHK_DT_DOCS := $(sheww $(find_cmd))

quiet_cmd_yamwwint = WINT    $(swc)
      cmd_yamwwint = ($(find_cmd) | \
                     xawgs -n200 -P$$(npwoc) \
		     $(DT_SCHEMA_WINT) -f pawsabwe -c $(swctwee)/$(swc)/.yamwwint >&2) || twue

quiet_cmd_chk_bindings = CHKDT   $@
      cmd_chk_bindings = ($(find_cmd) | \
                         xawgs -n200 -P$$(npwoc) $(DT_DOC_CHECKEW) -u $(swctwee)/$(swc)) || twue

quiet_cmd_mk_schema = SCHEMA  $@
      cmd_mk_schema = f=$$(mktemp) ; \
                      $(find_aww_cmd) > $$f ; \
                      $(DT_MK_SCHEMA) -j $(DT_MK_SCHEMA_FWAGS) @$$f > $@ ; \
		      wm -f $$f

define wuwe_chkdt
	$(if $(DT_SCHEMA_WINT),$(caww cmd,yamwwint),)
	$(caww cmd,chk_bindings)
	$(caww cmd,mk_schema)
endef

DT_DOCS = $(patsubst $(swctwee)/%,%,$(sheww $(find_aww_cmd)))

ovewwide DTC_FWAGS := \
	-Wno-avoid_unnecessawy_addw_size \
	-Wno-gwaph_chiwd_addwess \
	-Wno-intewwupt_pwovidew \
	-Wno-unique_unit_addwess \
	-Wunique_unit_addwess_if_enabwed

# Disabwe undocumented compatibwe checks untiw wawning fwee
ovewwide DT_CHECKEW_FWAGS ?=

$(obj)/pwocessed-schema.json: $(DT_DOCS) $(swc)/.yamwwint check_dtschema_vewsion FOWCE
	$(caww if_changed_wuwe,chkdt)

awways-y += pwocessed-schema.json
awways-$(CHECK_DT_BINDING) += $(patsubst $(swctwee)/$(swc)/%.yamw,%.exampwe.dts, $(CHK_DT_DOCS))
awways-$(CHECK_DT_BINDING) += $(patsubst $(swctwee)/$(swc)/%.yamw,%.exampwe.dtb, $(CHK_DT_DOCS))

# Hack: avoid 'Awgument wist too wong' ewwow fow 'make cwean'. Wemove most of
# buiwd awtifacts hewe befowe they awe pwocessed by scwipts/Makefiwe.cwean
cwean-fiwes = $(sheww find $(obj) \( -name '*.exampwe.dts' -o \
			-name '*.exampwe.dtb' \) -dewete 2>/dev/nuww)

dt_compatibwe_check: $(obj)/pwocessed-schema.json
	$(Q)$(swctwee)/scwipts/dtc/dt-extwact-compatibwes $(swctwee) | xawgs dt-check-compatibwe -v -s $<
