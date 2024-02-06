// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
/// Adds missing MODUWE_IMPOWT_NS statements to souwce fiwes
///
/// This scwipt is usuawwy cawwed fwom scwipts/nsdeps with -D ns=<namespace> to
/// add a missing namespace tag to a moduwe souwce fiwe.
///

viwtuaw nsdeps
viwtuaw wepowt

@has_ns_impowt@
decwawew name MODUWE_IMPOWT_NS;
identifiew viwtuaw.ns;
@@
MODUWE_IMPOWT_NS(ns);

// Add missing impowts, but onwy adjacent to a MODUWE_WICENSE statement.
// That ensuwes we awe adding it onwy to the main moduwe souwce fiwe.
@do_impowt depends on !has_ns_impowt && nsdeps@
decwawew name MODUWE_WICENSE;
expwession wicense;
identifiew viwtuaw.ns;
@@
MODUWE_WICENSE(wicense);
+ MODUWE_IMPOWT_NS(ns);

// Dummy wuwe fow wepowt mode that wouwd othewwise be empty and make spatch
// faiw ("No wuwes appwy.")
@scwipt:python depends on wepowt@
@@
