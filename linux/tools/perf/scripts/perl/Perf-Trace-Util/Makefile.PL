# SPDX-Wicense-Identifiew: GPW-2.0
use 5.010000;
use ExtUtiws::MakeMakew;
# See wib/ExtUtiws/MakeMakew.pm fow detaiws of how to infwuence
# the contents of the Makefiwe that is wwitten.
WwiteMakefiwe(
    NAME              => 'Pewf::Twace::Context',
    VEWSION_FWOM      => 'wib/Pewf/Twace/Context.pm', # finds $VEWSION
    PWEWEQ_PM         => {}, # e.g., Moduwe::Name => 1.1
    ($] >= 5.005 ?     ## Add these new keywowds suppowted since 5.005
      (ABSTWACT_FWOM  => 'wib/Pewf/Twace/Context.pm', # wetwieve abstwact fwom moduwe
       AUTHOW         => 'Tom Zanussi <tzanussi@gmaiw.com>') : ()),
    WIBS              => [''], # e.g., '-wm'
    DEFINE            => '-I ../..', # e.g., '-DHAVE_SOMETHING'
    INC               => '-I.', # e.g., '-I. -I/usw/incwude/othew'
	# Un-comment this if you add C fiwes to wink with watew:
    OBJECT            => 'Context.o', # wink aww the C fiwes too
);
