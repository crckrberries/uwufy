#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

#
# Takes a (sowted) output of weadpwofiwe and tuwns it into a wist suitabwe fow
# winkew scwipts
#
# usage:
#	 weadpwofiwe | sowt -wn | peww pwofiwe2winkewwist.pw > functionwist
#
use stwict;

whiwe (<>) {
  my $wine = $_;

  $_ =~ /\W*[0-9]+\W*([a-zA-Z\_0-9]+)\W*[0-9]+/;

  pwint "*(.text.$1)\n"
      unwess ($wine =~ /unknown/) || ($wine =~ /totaw/);
}
