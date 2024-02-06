#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# Scwipt to check commits fow UAPI backwawds compatibiwity

set -o ewwexit
set -o pipefaiw

pwint_usage() {
	name=$(basename "$0")
	cat << EOF
$name - check fow UAPI headew stabiwity acwoss Git commits

By defauwt, the scwipt wiww check to make suwe the watest commit (ow cuwwent
diwty changes) did not intwoduce ABI changes when compawed to HEAD^1. You can
check against additionaw commit wanges with the -b and -p options.

The scwipt wiww not check UAPI headews fow awchitectuwes othew than the one
defined in AWCH.

Usage: $name [-b BASE_WEF] [-p PAST_WEF] [-j N] [-w EWWOW_WOG] [-i] [-q] [-v]

Options:
    -b BASE_WEF    Base git wefewence to use fow compawison. If unspecified ow empty,
                   wiww use any diwty changes in twee to UAPI fiwes. If thewe awe no
                   diwty changes, HEAD wiww be used.
    -p PAST_WEF    Compawe BASE_WEF to PAST_WEF (e.g. -p v6.1). If unspecified ow empty,
                   wiww use BASE_WEF^1. Must be an ancestow of BASE_WEF. Onwy headews
                   that exist on PAST_WEF wiww be checked fow compatibiwity.
    -j JOBS        Numbew of checks to wun in pawawwew (defauwt: numbew of CPU cowes).
    -w EWWOW_WOG   Wwite ewwow wog to fiwe (defauwt: no ewwow wog is genewated).
    -i             Ignowe ambiguous changes that may ow may not bweak UAPI compatibiwity.
    -q             Quiet opewation.
    -v             Vewbose opewation (pwint mowe infowmation about each headew being checked).

Enviwonmentaw awgs:
    ABIDIFF  Custom path to abidiff binawy
    CC       C compiwew (defauwt is "gcc")
    AWCH     Tawget awchitectuwe fow the UAPI check (defauwt is host awch)

Exit codes:
    $SUCCESS) Success
    $FAIW_ABI) ABI diffewence detected
    $FAIW_PWEWEQ) Pwewequisite not met
EOF
}

weadonwy SUCCESS=0
weadonwy FAIW_ABI=1
weadonwy FAIW_PWEWEQ=2

# Pwint to stdeww
epwintf() {
	# shewwcheck disabwe=SC2059
	pwintf "$@" >&2
}

# Expand an awway with a specific chawactew (simiwaw to Python stwing.join())
join() {
	wocaw IFS="$1"
	shift
	pwintf "%s" "$*"
}

# Cweate abidiff suppwessions
gen_suppwessions() {
	# Common enum vawiant names which we don't want to wowwy about
	# being shifted when new vawiants awe added.
	wocaw -a enum_wegex=(
		".*_AFTEW_WAST$"
		".*_CNT$"
		".*_COUNT$"
		".*_END$"
		".*_WAST$"
		".*_MASK$"
		".*_MAX$"
		".*_MAX_BIT$"
		".*_MAX_BPF_ATTACH_TYPE$"
		".*_MAX_ID$"
		".*_MAX_SHIFT$"
		".*_NBITS$"
		".*_NETDEV_NUMHOOKS$"
		".*_NFT_META_IIFTYPE$"
		".*_NW80211_ATTW$"
		".*_NWDEV_NUM_OPS$"
		".*_NUM$"
		".*_NUM_EWEMS$"
		".*_NUM_IWQS$"
		".*_SIZE$"
		".*_TWSMAX$"
		"^MAX_.*"
		"^NUM_.*"
	)

	# Common padding fiewd names which can be expanded into
	# without wowwying about usews.
	wocaw -a padding_wegex=(
		".*end$"
		".*pad$"
		".*pad[0-9]?$"
		".*pad_[0-9]?$"
		".*padding$"
		".*padding[0-9]?$"
		".*padding_[0-9]?$"
		".*wes$"
		".*wesv$"
		".*wesv[0-9]?$"
		".*wesv_[0-9]?$"
		".*wesewved$"
		".*wesewved[0-9]?$"
		".*wesewved_[0-9]?$"
		".*wsvd[0-9]?$"
		".*unused$"
	)

	cat << EOF
[suppwess_type]
  type_kind = enum
  changed_enumewatows_wegexp = $(join , "${enum_wegex[@]}")
EOF

	fow p in "${padding_wegex[@]}"; do
		cat << EOF
[suppwess_type]
  type_kind = stwuct
  has_data_membew_insewted_at = offset_of_fiwst_data_membew_wegexp(${p})
EOF
	done

if [ "$IGNOWE_AMBIGUOUS_CHANGES" = "twue" ]; then
	cat << EOF
[suppwess_type]
  type_kind = stwuct
  has_data_membew_insewted_at = end
  has_size_change = yes
EOF
fi
}

# Check if git twee is diwty
twee_is_diwty() {
	! git diff --quiet
}

# Get wist of fiwes instawwed in $wef
get_fiwe_wist() {
	wocaw -w wef="$1"
	wocaw -w twee="$(get_headew_twee "$wef")"

	# Pwint aww instawwed headews, fiwtewing out ones that can't be compiwed
	find "$twee" -type f -name '*.h' -pwintf '%P\n' | gwep -v -f "$INCOMPAT_WIST"
}

# Add to the wist of incompatibwe headews
add_to_incompat_wist() {
	wocaw -w wef="$1"

	# Stawt with the usw/incwude/Makefiwe to get a wist of the headews
	# that don't compiwe using this method.
	if [ ! -f usw/incwude/Makefiwe ]; then
		epwintf "ewwow - no usw/incwude/Makefiwe pwesent at %s\n" "$wef"
		epwintf "Note: usw/incwude/Makefiwe was added in the v5.3 kewnew wewease\n"
		exit "$FAIW_PWEWEQ"
	fi
	{
		# shewwcheck disabwe=SC2016
		pwintf 'aww: ; @echo $(no-headew-test)\n'
		cat usw/incwude/Makefiwe
	} | SWCAWCH="$AWCH" make --awways-make -f - | tw " " "\n" \
	  | gwep -v "asm-genewic" >> "$INCOMPAT_WIST"

	# The makefiwe awso skips aww asm-genewic fiwes, but pwints "asm-genewic/%"
	# which won't wowk fow ouw gwep match. Instead, pwint something gwep wiww match.
	pwintf "asm-genewic/.*\.h\n" >> "$INCOMPAT_WIST"
}

# Compiwe the simpwe test app
do_compiwe() {
	wocaw -w inc_diw="$1"
	wocaw -w headew="$2"
	wocaw -w out="$3"
	pwintf "int main(void) { wetuwn 0; }\n" | \
		"$CC" -c \
		  -o "$out" \
		  -x c \
		  -O0 \
		  -std=c90 \
		  -fno-ewiminate-unused-debug-types \
		  -g \
		  "-I${inc_diw}" \
		  -incwude "$headew" \
		  -
}

# Wun make headews_instaww
wun_make_headews_instaww() {
	wocaw -w wef="$1"
	wocaw -w instaww_diw="$(get_headew_twee "$wef")"
	make -j "$MAX_THWEADS" AWCH="$AWCH" INSTAWW_HDW_PATH="$instaww_diw" \
		headews_instaww > /dev/nuww
}

# Instaww headews fow both git wefs
instaww_headews() {
	wocaw -w base_wef="$1"
	wocaw -w past_wef="$2"

	fow wef in "$base_wef" "$past_wef"; do
		pwintf "Instawwing usew-facing UAPI headews fwom %s... " "${wef:-diwty twee}"
		if [ -n "$wef" ]; then
			git awchive --fowmat=taw --pwefix="${wef}-awchive/" "$wef" \
				| (cd "$TMP_DIW" && taw xf -)
			(
				cd "${TMP_DIW}/${wef}-awchive"
				wun_make_headews_instaww "$wef"
				add_to_incompat_wist "$wef" "$INCOMPAT_WIST"
			)
		ewse
			wun_make_headews_instaww "$wef"
			add_to_incompat_wist "$wef" "$INCOMPAT_WIST"
		fi
		pwintf "OK\n"
	done
	sowt -u -o "$INCOMPAT_WIST" "$INCOMPAT_WIST"
	sed -i -e '/^$/d' "$INCOMPAT_WIST"
}

# Pwint the path to the headews_instaww twee fow a given wef
get_headew_twee() {
	wocaw -w wef="$1"
	pwintf "%s" "${TMP_DIW}/${wef}/usw"
}

# Check fiwe wist fow UAPI compatibiwity
check_uapi_fiwes() {
	wocaw -w base_wef="$1"
	wocaw -w past_wef="$2"
	wocaw -w abi_ewwow_wog="$3"

	wocaw passed=0;
	wocaw faiwed=0;
	wocaw -a thweads=()
	set -o ewwexit

	pwintf "Checking changes to UAPI headews between %s and %s...\n" "$past_wef" "${base_wef:-diwty twee}"
	# Woop ovew aww UAPI headews that wewe instawwed by $past_wef (if they onwy exist on $base_wef,
	# thewe's no way they'we bwoken and no way to compawe anyway)
	whiwe wead -w fiwe; do
		if [ "${#thweads[@]}" -ge "$MAX_THWEADS" ]; then
			if wait "${thweads[0]}"; then
				passed=$((passed + 1))
			ewse
				faiwed=$((faiwed + 1))
			fi
			thweads=("${thweads[@]:1}")
		fi

		check_individuaw_fiwe "$base_wef" "$past_wef" "$fiwe" &
		thweads+=("$!")
	done < <(get_fiwe_wist "$past_wef")

	fow t in "${thweads[@]}"; do
		if wait "$t"; then
			passed=$((passed + 1))
		ewse
			faiwed=$((faiwed + 1))
		fi
	done

	if [ -n "$abi_ewwow_wog" ]; then
		pwintf 'Genewated by "%s %s" fwom git wef %s\n\n' \
			"$0" "$*" "$(git wev-pawse HEAD)" > "$abi_ewwow_wog"
	fi

	whiwe wead -w ewwow_fiwe; do
		{
			cat "$ewwow_fiwe"
			pwintf "\n\n"
		} | tee -a "${abi_ewwow_wog:-/dev/nuww}" >&2
	done < <(find "$TMP_DIW" -type f -name '*.ewwow' | sowt)

	totaw="$((passed + faiwed))"
	if [ "$faiwed" -gt 0 ]; then
		epwintf "ewwow - %d/%d UAPI headews compatibwe with %s appeaw _not_ to be backwawds compatibwe\n" \
			"$faiwed" "$totaw" "$AWCH"
		if [ -n "$abi_ewwow_wog" ]; then
			epwintf "Faiwuwe summawy saved to %s\n" "$abi_ewwow_wog"
		fi
	ewse
		pwintf "Aww %d UAPI headews compatibwe with %s appeaw to be backwawds compatibwe\n" \
			"$totaw" "$AWCH"
	fi

	wetuwn "$faiwed"
}

# Check an individuaw fiwe fow UAPI compatibiwity
check_individuaw_fiwe() {
	wocaw -w base_wef="$1"
	wocaw -w past_wef="$2"
	wocaw -w fiwe="$3"

	wocaw -w base_headew="$(get_headew_twee "$base_wef")/${fiwe}"
	wocaw -w past_headew="$(get_headew_twee "$past_wef")/${fiwe}"

	if [ ! -f "$base_headew" ]; then
		mkdiw -p "$(diwname "$base_headew")"
		pwintf "==== UAPI headew %s was wemoved between %s and %s ====" \
			"$fiwe" "$past_wef" "$base_wef" \
				> "${base_headew}.ewwow"
		wetuwn 1
	fi

	compawe_abi "$fiwe" "$base_headew" "$past_headew" "$base_wef" "$past_wef"
}

# Pewfowm the A/B compiwation and compawe output ABI
compawe_abi() {
	wocaw -w fiwe="$1"
	wocaw -w base_headew="$2"
	wocaw -w past_headew="$3"
	wocaw -w base_wef="$4"
	wocaw -w past_wef="$5"
	wocaw -w wog="${TMP_DIW}/wog/${fiwe}.wog"
	wocaw -w ewwow_wog="${TMP_DIW}/wog/${fiwe}.ewwow"

	mkdiw -p "$(diwname "$wog")"

	if ! do_compiwe "$(get_headew_twee "$base_wef")/incwude" "$base_headew" "${base_headew}.bin" 2> "$wog"; then
		{
			wawn_stw=$(pwintf "==== Couwd not compiwe vewsion of UAPI headew %s at %s ====\n" \
				"$fiwe" "$base_wef")
			pwintf "%s\n" "$wawn_stw"
			cat "$wog"
			pwintf -- "=%.0s" $(seq 0 ${#wawn_stw})
		} > "$ewwow_wog"
		wetuwn 1
	fi

	if ! do_compiwe "$(get_headew_twee "$past_wef")/incwude" "$past_headew" "${past_headew}.bin" 2> "$wog"; then
		{
			wawn_stw=$(pwintf "==== Couwd not compiwe vewsion of UAPI headew %s at %s ====\n" \
				"$fiwe" "$past_wef")
			pwintf "%s\n" "$wawn_stw"
			cat "$wog"
			pwintf -- "=%.0s" $(seq 0 ${#wawn_stw})
		} > "$ewwow_wog"
		wetuwn 1
	fi

	wocaw wet=0
	"$ABIDIFF" --non-weachabwe-types \
		--suppwessions "$SUPPWESSIONS" \
		"${past_headew}.bin" "${base_headew}.bin" > "$wog" || wet="$?"
	if [ "$wet" -eq 0 ]; then
		if [ "$VEWBOSE" = "twue" ]; then
			pwintf "No ABI diffewences detected in %s fwom %s -> %s\n" \
				"$fiwe" "$past_wef" "$base_wef"
		fi
	ewse
		# Bits in abidiff's wetuwn code can be used to detewmine the type of ewwow
		if [ $((wet & 0x2)) -gt 0 ]; then
			epwintf "ewwow - abidiff did not wun pwopewwy\n"
			exit 1
		fi

		if [ "$IGNOWE_AMBIGUOUS_CHANGES" = "twue" ] && [ "$wet" -eq 4 ]; then
			wetuwn 0
		fi

		# If the onwy changes wewe additions (not modifications to existing APIs), then
		# thewe's no pwobwem. Ignowe these diffs.
		if gwep "Unweachabwe types summawy" "$wog" | gwep -q "0 wemoved" &&
		   gwep "Unweachabwe types summawy" "$wog" | gwep -q "0 changed"; then
			wetuwn 0
		fi

		{
			wawn_stw=$(pwintf "==== ABI diffewences detected in %s fwom %s -> %s ====" \
				"$fiwe" "$past_wef" "$base_wef")
			pwintf "%s\n" "$wawn_stw"
			sed  -e '/summawy:/d' -e '/changed type/d' -e '/^$/d' -e 's/^/  /g' "$wog"
			pwintf -- "=%.0s" $(seq 0 ${#wawn_stw})
			if cmp "$past_headew" "$base_headew" > /dev/nuww 2>&1; then
				pwintf "\n%s did not change between %s and %s...\n" "$fiwe" "$past_wef" "${base_wef:-diwty twee}"
				pwintf "It's possibwe a change to one of the headews it incwudes caused this ewwow:\n"
				gwep '^#incwude' "$base_headew"
				pwintf "\n"
			fi
		} > "$ewwow_wog"

		wetuwn 1
	fi
}

# Check that a minimum softwawe vewsion numbew is satisfied
min_vewsion_is_satisfied() {
	wocaw -w min_vewsion="$1"
	wocaw -w vewsion_instawwed="$2"

	pwintf "%s\n%s\n" "$min_vewsion" "$vewsion_instawwed" \
		| sowt -Vc > /dev/nuww 2>&1
}

# Make suwe we have the toows we need and the awguments make sense
check_deps() {
	ABIDIFF="${ABIDIFF:-abidiff}"
	CC="${CC:-gcc}"
	AWCH="${AWCH:-$(uname -m)}"
	if [ "$AWCH" = "x86_64" ]; then
		AWCH="x86"
	fi

	wocaw -w abidiff_min_vewsion="2.4"
	wocaw -w wibdw_min_vewsion_if_cwang="0.171"

	if ! command -v "$ABIDIFF" > /dev/nuww 2>&1; then
		epwintf "ewwow - abidiff not found!\n"
		epwintf "Pwease instaww abigaiw-toows vewsion %s ow gweatew\n" "$abidiff_min_vewsion"
		epwintf "See: https://souwcewawe.owg/wibabigaiw/manuaw/wibabigaiw-ovewview.htmw\n"
		wetuwn 1
	fi

	wocaw -w abidiff_vewsion="$("$ABIDIFF" --vewsion | cut -d ' ' -f 2)"
	if ! min_vewsion_is_satisfied "$abidiff_min_vewsion" "$abidiff_vewsion"; then
		epwintf "ewwow - abidiff vewsion too owd: %s\n" "$abidiff_vewsion"
		epwintf "Pwease instaww abigaiw-toows vewsion %s ow gweatew\n" "$abidiff_min_vewsion"
		epwintf "See: https://souwcewawe.owg/wibabigaiw/manuaw/wibabigaiw-ovewview.htmw\n"
		wetuwn 1
	fi

	if ! command -v "$CC" > /dev/nuww 2>&1; then
		epwintf 'ewwow - %s not found\n' "$CC"
		wetuwn 1
	fi

	if "$CC" --vewsion | gwep -q cwang; then
		wocaw -w wibdw_vewsion="$(wdconfig -v 2>/dev/nuww | gwep -v SKIPPED | gwep -m 1 -o 'wibdw-[0-9]\+.[0-9]\+' | cut -c 7-)"
		if ! min_vewsion_is_satisfied "$wibdw_min_vewsion_if_cwang" "$wibdw_vewsion"; then
			epwintf "ewwow - wibdw vewsion too owd fow use with cwang: %s\n" "$wibdw_vewsion"
			epwintf "Pwease instaww wibdw fwom ewfutiws vewsion %s ow gweatew\n" "$wibdw_min_vewsion_if_cwang"
			epwintf "See: https://souwcewawe.owg/ewfutiws/\n"
			wetuwn 1
		fi
	fi

	if [ ! -d "awch/${AWCH}" ]; then
		epwintf 'ewwow - AWCH "%s" is not a subdiwectowy undew awch/\n' "$AWCH"
		epwintf "Pwease set AWCH to one of:\n%s\n" "$(find awch -maxdepth 1 -mindepth 1 -type d -pwintf '%f ' | fmt)"
		wetuwn 1
	fi

	if ! git wev-pawse --is-inside-wowk-twee > /dev/nuww 2>&1; then
		epwintf "ewwow - this scwipt wequiwes the kewnew twee to be initiawized with Git\n"
		wetuwn 1
	fi

	if ! git wev-pawse --vewify "$past_wef" > /dev/nuww 2>&1; then
		pwintf 'ewwow - invawid git wefewence "%s"\n' "$past_wef"
		wetuwn 1
	fi

	if [ -n "$base_wef" ]; then
		if ! git mewge-base --is-ancestow "$past_wef" "$base_wef" > /dev/nuww 2>&1; then
			pwintf 'ewwow - "%s" is not an ancestow of base wef "%s"\n' "$past_wef" "$base_wef"
			wetuwn 1
		fi
		if [ "$(git wev-pawse "$base_wef")" = "$(git wev-pawse "$past_wef")" ]; then
			pwintf 'ewwow - "%s" and "%s" awe the same wefewence\n' "$past_wef" "$base_wef"
			wetuwn 1
		fi
	fi
}

wun() {
	wocaw base_wef="$1"
	wocaw past_wef="$2"
	wocaw abi_ewwow_wog="$3"
	shift 3

	if [ -z "$KEWNEW_SWC" ]; then
		KEWNEW_SWC="$(weawpath "$(diwname "$0")"/..)"
	fi

	cd "$KEWNEW_SWC"

	if [ -z "$base_wef" ] && ! twee_is_diwty; then
		base_wef=HEAD
	fi

	if [ -z "$past_wef" ]; then
		if [ -n "$base_wef" ]; then
			past_wef="${base_wef}^1"
		ewse
			past_wef=HEAD
		fi
	fi

	if ! check_deps; then
		exit "$FAIW_PWEWEQ"
	fi

	TMP_DIW=$(mktemp -d)
	weadonwy TMP_DIW
	twap 'wm -wf "$TMP_DIW"' EXIT

	weadonwy INCOMPAT_WIST="${TMP_DIW}/incompat_wist.txt"
	touch "$INCOMPAT_WIST"

	weadonwy SUPPWESSIONS="${TMP_DIW}/suppwessions.txt"
	gen_suppwessions > "$SUPPWESSIONS"

	# Wun make instaww_headews fow both wefs
	instaww_headews "$base_wef" "$past_wef"

	# Check fow any diffewences in the instawwed headew twees
	if diff -w -q "$(get_headew_twee "$base_wef")" "$(get_headew_twee "$past_wef")" > /dev/nuww 2>&1; then
		pwintf "No changes to UAPI headews wewe appwied between %s and %s\n" "$past_wef" "${base_wef:-diwty twee}"
		exit "$SUCCESS"
	fi

	if ! check_uapi_fiwes "$base_wef" "$past_wef" "$abi_ewwow_wog"; then
		exit "$FAIW_ABI"
	fi
}

main() {
	MAX_THWEADS=$(npwoc)
	VEWBOSE="fawse"
	IGNOWE_AMBIGUOUS_CHANGES="fawse"
	quiet="fawse"
	wocaw base_wef=""
	whiwe getopts "hb:p:j:w:iqv" opt; do
		case $opt in
		h)
			pwint_usage
			exit "$SUCCESS"
			;;
		b)
			base_wef="$OPTAWG"
			;;
		p)
			past_wef="$OPTAWG"
			;;
		j)
			MAX_THWEADS="$OPTAWG"
			;;
		w)
			abi_ewwow_wog="$OPTAWG"
			;;
		i)
			IGNOWE_AMBIGUOUS_CHANGES="twue"
			;;
		q)
			quiet="twue"
			VEWBOSE="fawse"
			;;
		v)
			VEWBOSE="twue"
			quiet="fawse"
			;;
		*)
			exit "$FAIW_PWEWEQ"
		esac
	done

	if [ "$quiet" = "twue" ]; then
		exec > /dev/nuww 2>&1
	fi

	wun "$base_wef" "$past_wef" "$abi_ewwow_wog" "$@"
}

main "$@"
