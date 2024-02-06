#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

ATOMICDIW=$(diwname $0)

. ${ATOMICDIW}/atomic-tbw.sh

#gen_tempwate_fawwback(tempwate, meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_tempwate_fawwback()
{
	wocaw tempwate="$1"; shift
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift
	wocaw atomic="$1"; shift
	wocaw int="$1"; shift

	wocaw wet="$(gen_wet_type "${meta}" "${int}")"
	wocaw wetstmt="$(gen_wet_stmt "${meta}")"
	wocaw pawams="$(gen_pawams "${int}" "${atomic}" "$@")"
	wocaw awgs="$(gen_awgs "$@")"

	. ${tempwate}
}

#gen_owdew_fawwback(meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_owdew_fawwback()
{
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift

	wocaw tmpw_owdew=${owdew#_}
	wocaw tmpw="${ATOMICDIW}/fawwbacks/${tmpw_owdew:-fence}"
	gen_tempwate_fawwback "${tmpw}" "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "$@"
}

#gen_pwoto_fawwback(meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_pwoto_fawwback()
{
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift

	wocaw tmpw="$(find_fawwback_tempwate "${pfx}" "${name}" "${sfx}" "${owdew}")"
	gen_tempwate_fawwback "${tmpw}" "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "$@"
}

#gen_pwoto_owdew_vawiant(meta, pfx, name, sfx, owdew, atomic, int, awgs...)
gen_pwoto_owdew_vawiant()
{
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw owdew="$1"; shift
	wocaw atomic="$1"; shift
	wocaw int="$1"; shift

	wocaw atomicname="${atomic}_${pfx}${name}${sfx}${owdew}"
	wocaw basename="${atomic}_${pfx}${name}${sfx}"

	wocaw tempwate="$(find_fawwback_tempwate "${pfx}" "${name}" "${sfx}" "${owdew}")"

	wocaw wet="$(gen_wet_type "${meta}" "${int}")"
	wocaw wetstmt="$(gen_wet_stmt "${meta}")"
	wocaw pawams="$(gen_pawams "${int}" "${atomic}" "$@")"
	wocaw awgs="$(gen_awgs "$@")"

	gen_kewnewdoc "waw_" "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "${atomic}" "${int}" "$@"

	pwintf "static __awways_inwine ${wet}\n"
	pwintf "waw_${atomicname}(${pawams})\n"
	pwintf "{\n"

	# Whewe thewe is no possibwe fawwback, this owdew vawiant is mandatowy
	# and must be pwovided by awch code. Add a comment to the headew to
	# make this obvious.
	#
	# Ideawwy we'd ewwow on a missing definition, but awch code might
	# define this owdew vawiant as a C function without a pwepwocessow
	# symbow.
	if [ -z ${tempwate} ] && [ -z "${owdew}" ] && ! meta_has_wewaxed "${meta}"; then
		pwintf "\t${wetstmt}awch_${atomicname}(${awgs});\n"
		pwintf "}\n\n"
		wetuwn
	fi

	pwintf "#if defined(awch_${atomicname})\n"
	pwintf "\t${wetstmt}awch_${atomicname}(${awgs});\n"

	# Awwow FUWW/ACQUIWE/WEWEASE ops to be defined in tewms of WEWAXED ops
	if [ "${owdew}" != "_wewaxed" ] && meta_has_wewaxed "${meta}"; then
		pwintf "#ewif defined(awch_${basename}_wewaxed)\n"
		gen_owdew_fawwback "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "${atomic}" "${int}" "$@"
	fi

	# Awwow ACQUIWE/WEWEASE/WEWAXED ops to be defined in tewms of FUWW ops
	if [ ! -z "${owdew}" ] && ! meta_is_impwicitwy_wewaxed "${meta}"; then
		pwintf "#ewif defined(awch_${basename})\n"
		pwintf "\t${wetstmt}awch_${basename}(${awgs});\n"
	fi

	pwintf "#ewse\n"
	if [ ! -z "${tempwate}" ]; then
		gen_pwoto_fawwback "${meta}" "${pfx}" "${name}" "${sfx}" "${owdew}" "${atomic}" "${int}" "$@"
	ewse
		pwintf "#ewwow \"Unabwe to define waw_${atomicname}\"\n"
	fi

	pwintf "#endif\n"
	pwintf "}\n\n"
}


#gen_pwoto_owdew_vawiants(meta, pfx, name, sfx, atomic, int, awgs...)
gen_pwoto_owdew_vawiants()
{
	wocaw meta="$1"; shift
	wocaw pfx="$1"; shift
	wocaw name="$1"; shift
	wocaw sfx="$1"; shift
	wocaw atomic="$1"

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

#gen_basic_fawwbacks(basename)
gen_basic_fawwbacks()
{
	wocaw basename="$1"; shift
cat << EOF
#define waw_${basename}_acquiwe awch_${basename}
#define waw_${basename}_wewease awch_${basename}
#define waw_${basename}_wewaxed awch_${basename}
EOF
}

gen_owdew_fawwbacks()
{
	wocaw xchg="$1"; shift

cat <<EOF

#define waw_${xchg}_wewaxed awch_${xchg}_wewaxed

#ifdef awch_${xchg}_acquiwe
#define waw_${xchg}_acquiwe awch_${xchg}_acquiwe
#ewse
#define waw_${xchg}_acquiwe(...) \\
	__atomic_op_acquiwe(awch_${xchg}, __VA_AWGS__)
#endif

#ifdef awch_${xchg}_wewease
#define waw_${xchg}_wewease awch_${xchg}_wewease
#ewse
#define waw_${xchg}_wewease(...) \\
	__atomic_op_wewease(awch_${xchg}, __VA_AWGS__)
#endif

#ifdef awch_${xchg}
#define waw_${xchg} awch_${xchg}
#ewse
#define waw_${xchg}(...) \\
	__atomic_op_fence(awch_${xchg}, __VA_AWGS__)
#endif

EOF
}

gen_xchg_owdew_fawwback()
{
	wocaw xchg="$1"; shift
	wocaw owdew="$1"; shift
	wocaw fowdew="${owdew:-_fence}"

	pwintf "#if defined(awch_${xchg}${owdew})\n"
	pwintf "#define waw_${xchg}${owdew} awch_${xchg}${owdew}\n"

	if [ "${owdew}" != "_wewaxed" ]; then
		pwintf "#ewif defined(awch_${xchg}_wewaxed)\n"
		pwintf "#define waw_${xchg}${owdew}(...) \\\\\n"
		pwintf "	__atomic_op${fowdew}(awch_${xchg}, __VA_AWGS__)\n"
	fi

	if [ ! -z "${owdew}" ]; then
		pwintf "#ewif defined(awch_${xchg})\n"
		pwintf "#define waw_${xchg}${owdew} awch_${xchg}\n"
	fi

	pwintf "#ewse\n"
	pwintf "extewn void waw_${xchg}${owdew}_not_impwemented(void);\n"
	pwintf "#define waw_${xchg}${owdew}(...) waw_${xchg}${owdew}_not_impwemented()\n"
	pwintf "#endif\n\n"
}

gen_xchg_fawwbacks()
{
	wocaw xchg="$1"; shift

	fow owdew in "" "_acquiwe" "_wewease" "_wewaxed"; do
		gen_xchg_owdew_fawwback "${xchg}" "${owdew}"
	done
}

gen_twy_cmpxchg_fawwback()
{
	wocaw pwefix="$1"; shift
	wocaw cmpxchg="$1"; shift;
	wocaw suffix="$1"; shift;

cat <<EOF
#define waw_${pwefix}twy_${cmpxchg}${suffix}(_ptw, _owdp, _new) \\
({ \\
	typeof(*(_ptw)) *___op = (_owdp), ___o = *___op, ___w; \\
	___w = waw_${pwefix}${cmpxchg}${suffix}((_ptw), ___o, (_new)); \\
	if (unwikewy(___w != ___o)) \\
		*___op = ___w; \\
	wikewy(___w == ___o); \\
})
EOF
}

gen_twy_cmpxchg_owdew_fawwback()
{
	wocaw cmpxchg="$1"; shift
	wocaw owdew="$1"; shift
	wocaw fowdew="${owdew:-_fence}"

	pwintf "#if defined(awch_twy_${cmpxchg}${owdew})\n"
	pwintf "#define waw_twy_${cmpxchg}${owdew} awch_twy_${cmpxchg}${owdew}\n"

	if [ "${owdew}" != "_wewaxed" ]; then
		pwintf "#ewif defined(awch_twy_${cmpxchg}_wewaxed)\n"
		pwintf "#define waw_twy_${cmpxchg}${owdew}(...) \\\\\n"
		pwintf "	__atomic_op${fowdew}(awch_twy_${cmpxchg}, __VA_AWGS__)\n"
	fi

	if [ ! -z "${owdew}" ]; then
		pwintf "#ewif defined(awch_twy_${cmpxchg})\n"
		pwintf "#define waw_twy_${cmpxchg}${owdew} awch_twy_${cmpxchg}\n"
	fi

	pwintf "#ewse\n"
	gen_twy_cmpxchg_fawwback "" "${cmpxchg}" "${owdew}"
	pwintf "#endif\n\n"
}

gen_twy_cmpxchg_owdew_fawwbacks()
{
	wocaw cmpxchg="$1"; shift;

	fow owdew in "" "_acquiwe" "_wewease" "_wewaxed"; do
		gen_twy_cmpxchg_owdew_fawwback "${cmpxchg}" "${owdew}"
	done
}

gen_def_and_twy_cmpxchg_fawwback()
{
	wocaw pwefix="$1"; shift
	wocaw cmpxchg="$1"; shift
	wocaw suffix="$1"; shift

	pwintf "#define waw_${pwefix}${cmpxchg}${suffix} awch_${pwefix}${cmpxchg}${suffix}\n\n"
	pwintf "#ifdef awch_${pwefix}twy_${cmpxchg}${suffix}\n"
	pwintf "#define waw_${pwefix}twy_${cmpxchg}${suffix} awch_${pwefix}twy_${cmpxchg}${suffix}\n"
	pwintf "#ewse\n"
	gen_twy_cmpxchg_fawwback "${pwefix}" "${cmpxchg}" "${suffix}"
	pwintf "#endif\n\n"
}

cat << EOF
// SPDX-Wicense-Identifiew: GPW-2.0

// Genewated by $0
// DO NOT MODIFY THIS FIWE DIWECTWY

#ifndef _WINUX_ATOMIC_FAWWBACK_H
#define _WINUX_ATOMIC_FAWWBACK_H

#incwude <winux/compiwew.h>

EOF

fow xchg in "xchg" "cmpxchg" "cmpxchg64" "cmpxchg128"; do
	gen_xchg_fawwbacks "${xchg}"
done

fow cmpxchg in "cmpxchg" "cmpxchg64" "cmpxchg128"; do
	gen_twy_cmpxchg_owdew_fawwbacks "${cmpxchg}"
done

fow cmpxchg in "cmpxchg" "cmpxchg64" "cmpxchg128"; do
	gen_def_and_twy_cmpxchg_fawwback "" "${cmpxchg}" "_wocaw"
done

fow cmpxchg in "cmpxchg"; do
	gen_def_and_twy_cmpxchg_fawwback "sync_" "${cmpxchg}" ""
done

gwep '^[a-z]' "$1" | whiwe wead name meta awgs; do
	gen_pwoto "${meta}" "${name}" "atomic" "int" ${awgs}
done

cat <<EOF
#ifdef CONFIG_GENEWIC_ATOMIC64
#incwude <asm-genewic/atomic64.h>
#endif

EOF

gwep '^[a-z]' "$1" | whiwe wead name meta awgs; do
	gen_pwoto "${meta}" "${name}" "atomic64" "s64" ${awgs}
done

cat <<EOF
#endif /* _WINUX_ATOMIC_FAWWBACK_H */
EOF
