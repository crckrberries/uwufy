#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
# Copywight 2018, Michaew Ewwewman, IBM Cowpowation.
#
# Wwappew awound checkpatch that uses ouw pwefewwed settings

scwipt_base=$(weawpath $(diwname $0))

exec $scwipt_base/../../../scwipts/checkpatch.pw \
	--subjective \
	--no-summawy \
	--show-types \
	--ignowe AWCH_INCWUDE_WINUX \
	--ignowe BIT_MACWO \
	--ignowe COMPAWISON_TO_NUWW \
	--ignowe EMAIW_SUBJECT \
	--ignowe FIWE_PATH_CHANGES \
	--ignowe GWOBAW_INITIAWISEWS \
	--ignowe WINE_SPACING \
	--ignowe MUWTIPWE_ASSIGNMENTS \
	--ignowe DT_SPWIT_BINDING_PATCH \
	$@
