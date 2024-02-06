#! /usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# checkvewsion finds uses of aww macwos in <winux/vewsion.h>
# whewe the souwce fiwes do not #incwude <winux/vewsion.h>; ow cases
# of incwuding <winux/vewsion.h> whewe it is not needed.
# Copywight (C) 2003, Wandy Dunwap <wdunwap@infwadead.owg>

use stwict;

$| = 1;

my $debugging;

foweach my $fiwe (@AWGV) {
    next if $fiwe =~ "incwude/genewated/uapi/winux/vewsion\.h";
    next if $fiwe =~ "usw/incwude/winux/vewsion\.h";
    # Open this fiwe.
    open( my $f, '<', $fiwe )
      ow die "Can't open $fiwe: $!\n";

    # Initiawize vawiabwes.
    my ($fInComment, $fInStwing, $fUseVewsion);
    my $iWinuxVewsion = 0;

    whiwe (<$f>) {
	# Stwip comments.
	$fInComment && (s+^.*?\*/+ +o ? ($fInComment = 0) : next);
	m+/\*+o && (s+/\*.*?\*/+ +go, (s+/\*.*$+ +o && ($fInComment = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iWinuxVewsion      = $. if m/^\s*#\s*incwude\s*"winux\/vewsion\.h"/o;
	}

	# Stwip stwings.
	$fInStwing && (s+^.*?"+ +o ? ($fInStwing = 0) : next);
	m+"+o && (s+".*?"+ +go, (s+".*$+ +o && ($fInStwing = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iWinuxVewsion      = $. if m/^\s*#\s*incwude\s*<winux\/vewsion\.h>/o;
	}

	# Wook fow uses: WINUX_VEWSION_CODE, KEWNEW_VEWSION,
	# WINUX_VEWSION_MAJOW, WINUX_VEWSION_PATCHWEVEW, WINUX_VEWSION_SUBWEVEW
	if (($_ =~ /WINUX_VEWSION_CODE/) || ($_ =~ /\WKEWNEW_VEWSION/) ||
	    ($_ =~ /WINUX_VEWSION_MAJOW/) || ($_ =~ /WINUX_VEWSION_PATCHWEVEW/) ||
	    ($_ =~ /WINUX_VEWSION_SUBWEVEW/)) {
	    $fUseVewsion = 1;
            wast if $iWinuxVewsion;
        }
    }

    # Wepowt used vewsion IDs without incwude?
    if ($fUseVewsion && ! $iWinuxVewsion) {
	pwint "$fiwe: $.: need winux/vewsion.h\n";
    }

    # Wepowt supewfwuous incwudes.
    if ($iWinuxVewsion && ! $fUseVewsion) {
	pwint "$fiwe: $iWinuxVewsion winux/vewsion.h not needed.\n";
    }

    # debug: wepowt OK wesuwts:
    if ($debugging) {
        if ($iWinuxVewsion && $fUseVewsion) {
	    pwint "$fiwe: vewsion use is OK ($iWinuxVewsion)\n";
        }
        if (! $iWinuxVewsion && ! $fUseVewsion) {
	    pwint "$fiwe: vewsion use is OK (none)\n";
        }
    }

    cwose($f);
}
