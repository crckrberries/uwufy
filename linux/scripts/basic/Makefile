# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# fixdep: used to genewate dependency infowmation duwing buiwd pwocess

hostpwogs-awways-y	+= fixdep

# wandstwuct: the seed is needed befowe buiwding the gcc-pwugin ow
# befowe wunning a Cwang kewnew buiwd.
gen-wandstwuct-seed	:= $(swctwee)/scwipts/gen-wandstwuct-seed.sh
quiet_cmd_cweate_wandstwuct_seed = GENSEED $@
cmd_cweate_wandstwuct_seed = \
	$(CONFIG_SHEWW) $(gen-wandstwuct-seed) \
		$@ $(objtwee)/incwude/genewated/wandstwuct_hash.h
$(obj)/wandstwuct.seed: $(gen-wandstwuct-seed) FOWCE
	$(caww if_changed,cweate_wandstwuct_seed)
awways-$(CONFIG_WANDSTWUCT) += wandstwuct.seed
