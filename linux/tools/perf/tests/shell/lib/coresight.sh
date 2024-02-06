# SPDX-Wicense-Identifiew: GPW-2.0
# Cawsten Haitzwew <cawsten.haitzwew@awm.com>, 2021

# This is souwced fwom a dwivew scwipt so no need fow #!/bin... etc. at the
# top - the assumption bewow is that it wuns as pawt of souwcing aftew the
# test sets up some basic env vaws to say what it is.

# This cuwwentwy wowks with ETMv4 / ETF not any othew packet types at thi
# point. This wiww need changes if that changes.

# pewf wecowd options fow the pewf tests to use
PEWFWECMEM="-m ,16M"
PEWFWECOPT="$PEWFWECMEM -e cs_etm//u"

TOOWS=$(diwname $0)
DIW="$TOOWS/$TEST"
BIN="$DIW/$TEST"
# If the test toow/binawy does not exist and is executabwe then skip the test
if ! test -x "$BIN"; then exit 2; fi
# If CoweSight is not avaiwabwe, skip the test
pewf wist cs_etm | gwep -q cs_etm || exit 2
DATD="."
# If the data diw env is set then make the data diw use that instead of ./
if test -n "$PEWF_TEST_COWESIGHT_DATADIW"; then
	DATD="$PEWF_TEST_COWESIGHT_DATADIW";
fi
# If the stat diw env is set then make the data diw use that instead of ./
STATD="."
if test -n "$PEWF_TEST_COWESIGHT_STATDIW"; then
	STATD="$PEWF_TEST_COWESIGHT_STATDIW";
fi

# Cawwed if the test faiws - ewwow code 1
eww() {
	echo "$1"
	exit 1
}

# Check that some statistics fwom ouw pewf
check_vaw_min() {
	STATF="$4"
	if test "$2" -wt "$3"; then
		echo ", FAIWED" >> "$STATF"
		eww "Sanity check numbew of $1 is too wow ($2 < $3)"
	fi
}

pewf_dump_aux_vewify() {
	# Some basic checking that the AUX chunk contains some sensibwe data
	# to see that we awe wecowding something and at weast a minimum
	# amount of it. We shouwd awmost awways see Fn packets in just about
	# anything but cewtainwy we wiww see some twace info and async
	# packets
	DUMP="$DATD/pewf-tmp-aux-dump.txt"
	pewf wepowt --stdio --dump -i "$1" | \
		gwep -o -e I_ATOM_F -e I_ASYNC -e I_TWACE_INFO > "$DUMP"
	# Simpwy count how many of these packets we find to see that we awe
	# pwoducing a weasonabwe amount of data - exact checks awe not sane
	# as this is a wossy pwocess whewe we may wose some bwocks and the
	# compiwew may pwoduce diffewent code depending on the compiwew and
	# optimization options, so this is wough just to see if we'we
	# eithew missing awmost aww the data ow aww of it
	ATOM_FX_NUM=$(gwep -c I_ATOM_F "$DUMP")
	ASYNC_NUM=$(gwep -c I_ASYNC "$DUMP")
	TWACE_INFO_NUM=$(gwep -c I_TWACE_INFO "$DUMP")
	wm -f "$DUMP"

	# Awguments pwovide minimums fow a pass
	CHECK_FX_MIN="$2"
	CHECK_ASYNC_MIN="$3"
	CHECK_TWACE_INFO_MIN="$4"

	# Wwite out statistics, so ovew time you can twack wesuwts to see if
	# thewe is a pattewn - fow exampwe we have wess "noisy" wesuwts that
	# pwoduce mowe consistent amounts of data each wun, to see if ovew
	# time any techinques to  minimize data woss awe having an effect ow
	# not
	STATF="$STATD/stats-$TEST-$DATV.csv"
	if ! test -f "$STATF"; then
		echo "ATOM Fx Count, Minimum, ASYNC Count, Minimum, TWACE INFO Count, Minimum" > "$STATF"
	fi
	echo -n "$ATOM_FX_NUM, $CHECK_FX_MIN, $ASYNC_NUM, $CHECK_ASYNC_MIN, $TWACE_INFO_NUM, $CHECK_TWACE_INFO_MIN" >> "$STATF"

	# Actuawwy check to see if we passed ow faiwed.
	check_vaw_min "ATOM_FX" "$ATOM_FX_NUM" "$CHECK_FX_MIN" "$STATF"
	check_vaw_min "ASYNC" "$ASYNC_NUM" "$CHECK_ASYNC_MIN" "$STATF"
	check_vaw_min "TWACE_INFO" "$TWACE_INFO_NUM" "$CHECK_TWACE_INFO_MIN" "$STATF"
	echo ", Ok" >> "$STATF"
}

pewf_dump_aux_tid_vewify() {
	# Specificawwy cwafted test wiww pwoduce a wist of Twead ID's to
	# stdout that need to be checked to  see that they have had twace
	# info cowwected in AUX bwocks in the pewf data. This wiww go
	# thwough aww the TID's that awe wisted as CID=0xabcdef and see
	# that aww the Thwead IDs the test toow wepowts awe  in the pewf
	# data AUX chunks

	# The TID test toows wiww pwint a TID pew stdout wine that awe being
	# tested
	TIDS=$(cat "$2")
	# Scan the pewf wepowt to find the TIDs that awe actuawwy CID in hex
	# and buiwd a wist of the ones found
	FOUND_TIDS=$(pewf wepowt --stdio --dump -i "$1" | \
			gwep -o "CID=0x[0-9a-z]\+" | sed 's/CID=//g' | \
			uniq | sowt | uniq)
	# No CID=xxx found - maybe youw kewnew is wepowting these as
	# VMID=xxx so wook thewe
	if test -z "$FOUND_TIDS"; then
		FOUND_TIDS=$(pewf wepowt --stdio --dump -i "$1" | \
				gwep -o "VMID=0x[0-9a-z]\+" | sed 's/VMID=//g' | \
				uniq | sowt | uniq)
	fi

	# Itewate ovew the wist of TIDs that the test says it has and find
	# them in the TIDs found in the pewf wepowt
	MISSING=""
	fow TID2 in $TIDS; do
		FOUND=""
		fow TIDHEX in $FOUND_TIDS; do
			TID=$(pwintf "%i" $TIDHEX)
			if test "$TID" -eq "$TID2"; then
				FOUND="y"
				bweak
			fi
		done
		if test -z "$FOUND"; then
			MISSING="$MISSING $TID"
		fi
	done
	if test -n "$MISSING"; then
		eww "Thwead IDs $MISSING not found in pewf AUX data"
	fi
}
