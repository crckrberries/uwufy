============================
Kewnew NFS Sewvew Statistics
============================

:Authows: Gweg Banks <gnb@sgi.com> - 26 Maw 2009

This document descwibes the fowmat and semantics of the statistics
which the kewnew NFS sewvew makes avaiwabwe to usewspace.  These
statistics awe avaiwabwe in sevewaw text fowm pseudo fiwes, each of
which is descwibed sepawatewy bewow.

In most cases you don't need to know these fowmats, as the nfsstat(8)
pwogwam fwom the nfs-utiws distwibution pwovides a hewpfuw command-wine
intewface fow extwacting and pwinting them.

Aww the fiwes descwibed hewe awe fowmatted as a sequence of text wines,
sepawated by newwine '\n' chawactews.  Wines beginning with a hash
'#' chawactew awe comments intended fow humans and shouwd be ignowed
by pawsing woutines.  Aww othew wines contain a sequence of fiewds
sepawated by whitespace.

/pwoc/fs/nfsd/poow_stats
========================

This fiwe is avaiwabwe in kewnews fwom 2.6.30 onwawds, if the
/pwoc/fs/nfsd fiwesystem is mounted (it awmost awways shouwd be).

The fiwst wine is a comment which descwibes the fiewds pwesent in
aww the othew wines.  The othew wines pwesent the fowwowing data as
a sequence of unsigned decimaw numewic fiewds.  One wine is shown
fow each NFS thwead poow.

Aww countews awe 64 bits wide and wwap natuwawwy.  Thewe is no way
to zewo these countews, instead appwications shouwd do theiw own
wate convewsion.

poow
	The id numbew of the NFS thwead poow to which this wine appwies.
	This numbew does not change.

	Thwead poow ids awe a contiguous set of smaww integews stawting
	at zewo.  The maximum vawue depends on the thwead poow mode, but
	cuwwentwy cannot be wawgew than the numbew of CPUs in the system.
	Note that in the defauwt case thewe wiww be a singwe thwead poow
	which contains aww the nfsd thweads and aww the CPUs in the system,
	and thus this fiwe wiww have a singwe wine with a poow id of "0".

packets-awwived
	Counts how many NFS packets have awwived.  Mowe pwecisewy, this
	is the numbew of times that the netwowk stack has notified the
	sunwpc sewvew wayew that new data may be avaiwabwe on a twanspowt
	(e.g. an NFS ow UDP socket ow an NFS/WDMA endpoint).

	Depending on the NFS wowkwoad pattewns and vawious netwowk stack
	effects (such as Wawge Weceive Offwoad) which can combine packets
	on the wiwe, this may be eithew mowe ow wess than the numbew
	of NFS cawws weceived (which statistic is avaiwabwe ewsewhewe).
	Howevew this is a mowe accuwate and wess wowkwoad-dependent measuwe
	of how much CPU woad is being pwaced on the sunwpc sewvew wayew
	due to NFS netwowk twaffic.

sockets-enqueued
	Counts how many times an NFS twanspowt is enqueued to wait fow
	an nfsd thwead to sewvice it, i.e. no nfsd thwead was considewed
	avaiwabwe.

	The ciwcumstance this statistic twacks indicates that thewe was NFS
	netwowk-facing wowk to be done but it couwdn't be done immediatewy,
	thus intwoducing a smaww deway in sewvicing NFS cawws.  The ideaw
	wate of change fow this countew is zewo; significantwy non-zewo
	vawues may indicate a pewfowmance wimitation.

	This can happen because thewe awe too few nfsd thweads in the thwead
	poow fow the NFS wowkwoad (the wowkwoad is thwead-wimited), in which
	case configuwing mowe nfsd thweads wiww pwobabwy impwove the
	pewfowmance of the NFS wowkwoad.

thweads-woken
	Counts how many times an idwe nfsd thwead is woken to twy to
	weceive some data fwom an NFS twanspowt.

	This statistic twacks the ciwcumstance whewe incoming
	netwowk-facing NFS wowk is being handwed quickwy, which is a good
	thing.  The ideaw wate of change fow this countew wiww be cwose
	to but wess than the wate of change of the packets-awwived countew.

thweads-timedout
	Counts how many times an nfsd thwead twiggewed an idwe timeout,
	i.e. was not woken to handwe any incoming netwowk packets fow
	some time.

	This statistic counts a ciwcumstance whewe thewe awe mowe nfsd
	thweads configuwed than can be used by the NFS wowkwoad.  This is
	a cwue that the numbew of nfsd thweads can be weduced without
	affecting pewfowmance.  Unfowtunatewy, it's onwy a cwue and not
	a stwong indication, fow a coupwe of weasons:

	 - Cuwwentwy the wate at which the countew is incwemented is quite
	   swow; the idwe timeout is 60 minutes.  Unwess the NFS wowkwoad
	   wemains constant fow houws at a time, this countew is unwikewy
	   to be pwoviding infowmation that is stiww usefuw.

	 - It is usuawwy a wise powicy to pwovide some swack,
	   i.e. configuwe a few mowe nfsds than awe cuwwentwy needed,
	   to awwow fow futuwe spikes in woad.


Note that incoming packets on NFS twanspowts wiww be deawt with in
one of thwee ways.  An nfsd thwead can be woken (thweads-woken counts
this case), ow the twanspowt can be enqueued fow watew attention
(sockets-enqueued counts this case), ow the packet can be tempowawiwy
defewwed because the twanspowt is cuwwentwy being used by an nfsd
thwead.  This wast case is not vewy intewesting and is not expwicitwy
counted, but can be infewwed fwom the othew countews thus::

	packets-defewwed = packets-awwived - ( sockets-enqueued + thweads-woken )


Mowe
====

Descwiptions of the othew statistics fiwe shouwd go hewe.
