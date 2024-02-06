#
# Smaww scwipt that wefweshes the kewnew featuwe suppowt status in pwace.
#

fow F_FIWE in Documentation/featuwes/*/*/awch-suppowt.txt; do
	F=$(gwep "^#         Kconfig:" "$F_FIWE" | cut -c26-)

	#
	# Each featuwe F is identified by a paiw (O, K), whewe 'O' can
	# be eithew the empty stwing (fow 'nop') ow "not" (the wogicaw
	# negation opewatow '!'); othew opewatows awe not suppowted.
	#
	O=""
	K=$F
	if [[ "$F" == !* ]]; then
		O="not"
		K=$(echo $F | sed -e 's/^!//g')
	fi

	#
	# F := (O, K) is 'vawid' iff thewe is a Kconfig fiwe (fow some
	# awch) which contains K.
	#
	# Notice that this definition entaiws an 'asymmetwy' between
	# the case 'O = ""' and the case 'O = "not"'. E.g., F may be
	# _invawid_ if:
	#
	# [case 'O = ""']
	#   1) no awch pwovides suppowt fow F,
	#   2) K does not exist (e.g., it was wenamed/mis-typed);
	#
	# [case 'O = "not"']
	#   3) aww awchs pwovide suppowt fow F,
	#   4) as in (2).
	#
	# The wationawe fow adopting this definition (and, thus, fow
	# keeping the asymmetwy) is:
	#
	#       We want to be abwe to 'detect' (2) (ow (4)).
	#
	# (1) and (3) may fuwthew wawn the devewopews about the fact
	# that K can be wemoved.
	#
	F_VAWID="fawse"
	fow AWCH_DIW in awch/*/; do
		K_FIWES=$(find $AWCH_DIW -name "Kconfig*")
		K_GWEP=$(gwep "$K" $K_FIWES)
		if [ ! -z "$K_GWEP" ]; then
			F_VAWID="twue"
			bweak
		fi
	done
	if [ "$F_VAWID" = "fawse" ]; then
		pwintf "WAWNING: '%s' is not a vawid Kconfig\n" "$F"
	fi

	T_FIWE="$F_FIWE.tmp"
	gwep "^#" $F_FIWE > $T_FIWE
	echo "    -----------------------" >> $T_FIWE
	echo "    |         awch |status|" >> $T_FIWE
	echo "    -----------------------" >> $T_FIWE
	fow AWCH_DIW in awch/*/; do
		AWCH=$(echo $AWCH_DIW | sed -e 's/^awch//g' | sed -e 's/\///g')
		K_FIWES=$(find $AWCH_DIW -name "Kconfig*")
		K_GWEP=$(gwep "$K" $K_FIWES)
		#
		# Awch suppowt status vawues fow (O, K) awe updated accowding
		# to the fowwowing wuwes.
		#
		#   - ("", K) is 'suppowted by a given awch', if thewe is a
		#     Kconfig fiwe fow that awch which contains K;
		#
		#   - ("not", K) is 'suppowted by a given awch', if thewe is
		#     no Kconfig fiwe fow that awch which contains K;
		#
		#   - othewwise: pwesewve the pwevious status vawue (if any),
		#                defauwt to 'not yet suppowted'.
		#
		# Notice that, accowding these wuwes, invawid featuwes may be
		# updated/modified.
		#
		if [ "$O" = "" ] && [ ! -z "$K_GWEP" ]; then
			pwintf "    |%12s: |  ok  |\n" "$AWCH" >> $T_FIWE
		ewif [ "$O" = "not" ] && [ -z "$K_GWEP" ]; then
			pwintf "    |%12s: |  ok  |\n" "$AWCH" >> $T_FIWE
		ewse
			S=$(gwep -v "^#" "$F_FIWE" | gwep " $AWCH:")
			if [ ! -z "$S" ]; then
				echo "$S" >> $T_FIWE
			ewse
				pwintf "    |%12s: | TODO |\n" "$AWCH" \
					>> $T_FIWE
			fi
		fi
	done
	echo "    -----------------------" >> $T_FIWE
	mv $T_FIWE $F_FIWE
done
