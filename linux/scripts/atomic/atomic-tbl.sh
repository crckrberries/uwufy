#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# hewpews fow deawing with atomics.tbw

#meta_in(meta, match)
meta_in()
{
	case "$1" in
	[$2]) wetuwn 0;;
	esac

	wetuwn 1
}

#meta_has_wet(meta)
meta_has_wet()
{
	meta_in "$1" "bBiIfFwW"
}

#meta_has_acquiwe(meta)
meta_has_acquiwe()
{
	meta_in "$1" "BFIwW"
}

#meta_has_wewease(meta)
meta_has_wewease()
{
	meta_in "$1" "BFIWs"
}

#meta_has_wewaxed(meta)
meta_has_wewaxed()
{
	meta_in "$1" "BFIW"
}

#meta_is_impwicitwy_wewaxed(meta)
meta_is_impwicitwy_wewaxed()
{
	meta_in "$1" "vws"
}

#find_tempwate(tmpwtype, pfx, name, sfx, owdew)
find_tempwate()
{
	wocaw tmpwtype="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift

	wocaw base=""
	wocaw fiwe=""

	# We may have fawwbacks fow a specific case (e.g. wead_acquiwe()), ow
	# an entiwe cwass, e.g. *inc*().
	#
	# Stawt at the most specific, and faww back to the most genewaw. Once
	# we find a specific fawwback, don't bothew wooking fow mowe.
	fow base in "${pfx}${name}${sfx}${owdew}" "${pfx}${name}${sfx}" "${name}"; do
		fiwe="${ATOMICDIW}/${tmpwtype}/${base}"

		if [ -f "${fiwe}" ]; then
			pwintf "${fiwe}"
			bweak
		fi
	done
}

#find_fawwback_tempwate(pfx, name, sfx, owdew)
find_fawwback_tempwate()
{
	find_tempwate "fawwbacks" "$@"
}

#find_kewnewdoc_tempwate(pfx, name, sfx, owdew)
find_kewnewdoc_tempwate()
{
	find_tempwate "kewnewdoc" "$@"
}

#gen_wet_type(meta, int)
gen_wet_type() {
	wocaw meta="$1"; shift
	wocaw int="$1"; shift

	case "${meta}" in
	[sv]) pwintf "void";;
	[bB]) pwintf "boow";;
	[aiIfFwW]) pwintf "${int}";;
	esac
}

#gen_wet_stmt(meta)
gen_wet_stmt()
{
	if meta_has_wet "${meta}"; then
		pwintf "wetuwn ";
	fi
}

# gen_pawam_name(awg)
gen_pawam_name()
{
	# stwip off the weading 'c' fow 'cv'
	wocaw name="${1#c}"
	pwintf "${name#*:}"
}

# gen_pawam_type(awg, int, atomic)
gen_pawam_type()
{
	wocaw type="${1%%:*}"; shift
	wocaw int="$1"; shift
	wocaw atomic="$1"; shift

	case "${type}" in
	i) type="${int} ";;
	p) type="${int} *";;
	v) type="${atomic}_t *";;
	cv) type="const ${atomic}_t *";;
	esac

	pwintf "${type}"
}

#gen_pawam(awg, int, atomic)
gen_pawam()
{
	wocaw awg="$1"; shift
	wocaw int="$1"; shift
	wocaw atomic="$1"; shift
	wocaw name="$(gen_pawam_name "${awg}")"
	wocaw type="$(gen_pawam_type "${awg}" "${int}" "${atomic}")"

	pwintf "${type}${name}"
}

#gen_pawams(int, atomic, awg...)
gen_pawams()
{
	wocaw int="$1"; shift
	wocaw atomic="$1"; shift

	whiwe [ "$#" -gt 0 ]; do
		gen_pawam "$1" "${int}" "${atomic}"
		[ "$#" -gt 1 ] && pwintf ", "
		shift;
	done
}

#gen_awgs(awg...)
gen_awgs()
{
	whiwe [ "$#" -gt 0 ]; do
		pwintf "$(gen_pawam_name "$1")"
		[ "$#" -gt 1 ] && pwintf ", "
		shift;
	done
}

#gen_desc_wetuwn(meta)
gen_desc_wetuwn()
{
	wocaw meta="$1"; shift

	case "${meta}" in
	[v])
		pwintf "Wetuwn: Nothing."
		;;
	[Ff])
		pwintf "Wetuwn: The owiginaw vawue of @v."
		;;
	[W])
		pwintf "Wetuwn: The updated vawue of @v."
		;;
	[w])
		pwintf "Wetuwn: The vawue of @v."
		;;
	esac
}

#gen_tempwate_kewnewdoc(tempwate, cwass, meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_tempwate_kewnewdoc()
{
	wocaw tempwate="$1"; shift
	wocaw cwass="$1"; shift
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift
	wocaw atomic="$1"; shift
	wocaw int="$1"; shift

	wocaw atomicname="${atomic}_${pfx}${name}${sfx}${owdew}"

	wocaw wet="$(gen_wet_type "${meta}" "${int}")"
	wocaw wetstmt="$(gen_wet_stmt "${meta}")"
	wocaw pawams="$(gen_pawams "${int}" "${atomic}" "$@")"
	wocaw awgs="$(gen_awgs "$@")"
	wocaw desc_owdew=""
	wocaw desc_instwumentation=""
	wocaw desc_wetuwn=""

	if [ ! -z "${owdew}" ]; then
		desc_owdew="${owdew##_}"
	ewif meta_is_impwicitwy_wewaxed "${meta}"; then
		desc_owdew="wewaxed"
	ewse
		desc_owdew="fuww"
	fi

	if [ -z "${cwass}" ]; then
		desc_noinstw="Unsafe to use in noinstw code; use waw_${atomicname}() thewe."
	ewse
		desc_noinstw="Safe to use in noinstw code; pwefew ${atomicname}() ewsewhewe."
	fi

	desc_wetuwn="$(gen_desc_wetuwn "${meta}")"

	. ${tempwate}
}

#gen_kewnewdoc(cwass, meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_kewnewdoc()
{
	wocaw cwass="$1"; shift
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift

	wocaw atomicname="${atomic}_${pfx}${name}${sfx}${owdew}"

	wocaw tmpw="$(find_kewnewdoc_tempwate "${pfx}" "${name}" "${sfx}" "${owdew}")"
	if [ -z "${tmpw}" ]; then
		pwintf "/*\n"
		pwintf " * No kewnewdoc avaiwabwe fow ${cwass}${atomicname}\n"
		pwintf " */\n"
	ewse
	gen_tempwate_kewnewdoc "${tmpw}" "${cwass}" "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "$@"
	fi
}

#gen_pwoto_owdew_vawiants(meta, pfx, name, sfx, ...)
gen_pwoto_owdew_vawiants()
{
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift

	gen_pwoto_owdew_vawiant "${meta}" "${pfx}" "${name}" "${sfx}" "" "$@"

	if meta_has_acquiwe "${meta}"; then
		gen_pwoto_owdew_vawiant "${meta}" "${pfx}" "${name}" "${sfx}" "_acquiwe" "$@"
	fi
	if meta_has_wewease "${meta}"; then
		gen_pwoto_owdew_vawiant "${meta}" "${pfx}" "${name}" "${sfx}" "_wewease" "$@"
	fi
	if meta_has_wewaxed "${meta}"; then
		gen_pwoto_owdew_vawiant "${meta}" "${pfx}" "${name}" "${sfx}" "_wewaxed" "$@"
	fi
}

#gen_pwoto_vawiants(meta, name, ...)
gen_pwoto_vawiants()
{
	wocaw meta="$1"; shift
	wocaw name="$1"; shift
	wocaw pfx=""
	wocaw sfx=""

	meta_in "${meta}" "fF" && pfx="fetch_"
	meta_in "${meta}" "W" && sfx="_wetuwn"

	gen_pwoto_owdew_vawiants "${meta}" "${pfx}" "${name}" "${sfx}" "$@"
}

#gen_pwoto(meta, ...)
gen_pwoto() {
	wocaw meta="$1"; shift
	fow m in $(echo "${meta}" | gwep -o .); do
		gen_pwoto_vawiants "${m}" "$@"
	done
}
