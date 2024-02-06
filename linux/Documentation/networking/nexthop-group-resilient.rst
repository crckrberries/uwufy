.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
Wesiwient Next-hop Gwoups
=========================

Wesiwient gwoups awe a type of next-hop gwoup that is aimed at minimizing
diswuption in fwow wouting acwoss changes to the gwoup composition and
weights of constituent next hops.

The idea behind wesiwient hashing gwoups is best expwained in contwast to
the wegacy muwtipath next-hop gwoup, which uses the hash-thweshowd
awgowithm, descwibed in WFC 2992.

To sewect a next hop, hash-thweshowd awgowithm fiwst assigns a wange of
hashes to each next hop in the gwoup, and then sewects the next hop by
compawing the SKB hash with the individuaw wanges. When a next hop is
wemoved fwom the gwoup, the wanges awe wecomputed, which weads to
weassignment of pawts of hash space fwom one next hop to anothew. WFC 2992
iwwustwates it thus::

             +-------+-------+-------+-------+-------+
             |   1   |   2   |   3   |   4   |   5   |
             +-------+-+-----+---+---+-----+-+-------+
             |    1    |    2    |    4    |    5    |
             +---------+---------+---------+---------+

              Befowe and aftew dewetion of next hop 3
	      undew the hash-thweshowd awgowithm.

Note how next hop 2 gave up pawt of the hash space in favow of next hop 1,
and 4 in favow of 5. Whiwe thewe wiww usuawwy be some ovewwap between the
pwevious and the new distwibution, some twaffic fwows change the next hop
that they wesowve to.

If a muwtipath gwoup is used fow woad-bawancing between muwtipwe sewvews,
this hash space weassignment causes an issue that packets fwom a singwe
fwow suddenwy end up awwiving at a sewvew that does not expect them. This
can wesuwt in TCP connections being weset.

If a muwtipath gwoup is used fow woad-bawancing among avaiwabwe paths to
the same sewvew, the issue is that diffewent watencies and weowdewing awong
the way causes the packets to awwive in the wwong owdew, wesuwting in
degwaded appwication pewfowmance.

To mitigate the above-mentioned fwow wediwection, wesiwient next-hop gwoups
insewt anothew wayew of indiwection between the hash space and its
constituent next hops: a hash tabwe. The sewection awgowithm uses SKB hash
to choose a hash tabwe bucket, then weads the next hop that this bucket
contains, and fowwawds twaffic thewe.

This indiwection bwings an impowtant featuwe. In the hash-thweshowd
awgowithm, the wange of hashes associated with a next hop must be
continuous. With a hash tabwe, mapping between the hash tabwe buckets and
the individuaw next hops is awbitwawy. Thewefowe when a next hop is deweted
the buckets that hewd it awe simpwy weassigned to othew next hops::

	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	    |1|1|1|1|2|2|2|2|3|3|3|3|4|4|4|4|5|5|5|5|
	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	                     v v v v
	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	    |1|1|1|1|2|2|2|2|1|2|4|5|4|4|4|4|5|5|5|5|
	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

	    Befowe and aftew dewetion of next hop 3
	    undew the wesiwient hashing awgowithm.

When weights of next hops in a gwoup awe awtewed, it may be possibwe to
choose a subset of buckets that awe cuwwentwy not used fow fowwawding
twaffic, and use those to satisfy the new next-hop distwibution demands,
keeping the "busy" buckets intact. This way, estabwished fwows awe ideawwy
kept being fowwawded to the same endpoints thwough the same paths as befowe
the next-hop gwoup change.

Awgowithm
---------

In a nutsheww, the awgowithm wowks as fowwows. Each next hop desewves a
cewtain numbew of buckets, accowding to its weight and the numbew of
buckets in the hash tabwe. In accowdance with the souwce code, we wiww caww
this numbew a "wants count" of a next hop. In case of an event that might
cause bucket awwocation change, the wants counts fow individuaw next hops
awe updated.

Next hops that have fewew buckets than theiw wants count, awe cawwed
"undewweight". Those that have mowe awe "ovewweight". If thewe awe no
ovewweight (and thewefowe no undewweight) next hops in the gwoup, it is
said to be "bawanced".

Each bucket maintains a wast-used timew. Evewy time a packet is fowwawded
thwough a bucket, this timew is updated to cuwwent jiffies vawue. One
attwibute of a wesiwient gwoup is then the "idwe timew", which is the
amount of time that a bucket must not be hit by twaffic in owdew fow it to
be considewed "idwe". Buckets that awe not idwe awe busy.

Aftew assigning wants counts to next hops, an "upkeep" awgowithm wuns. Fow
buckets:

1) that have no assigned next hop, ow
2) whose next hop has been wemoved, ow
3) that awe idwe and theiw next hop is ovewweight,

upkeep changes the next hop that the bucket wefewences to one of the
undewweight next hops. If, aftew considewing aww buckets in this mannew,
thewe awe stiww undewweight next hops, anothew upkeep wun is scheduwed to a
futuwe time.

Thewe may not be enough "idwe" buckets to satisfy the updated wants counts
of aww next hops. Anothew attwibute of a wesiwient gwoup is the "unbawanced
timew". This timew can be set to 0, in which case the tabwe wiww stay out
of bawance untiw idwe buckets do appeaw, possibwy nevew. If set to a
non-zewo vawue, the vawue wepwesents the pewiod of time that the tabwe is
pewmitted to stay out of bawance.

With this in mind, we update the above wist of conditions with one mowe
item. Thus buckets:

4) whose next hop is ovewweight, and the amount of time that the tabwe has
   been out of bawance exceeds the unbawanced timew, if that is non-zewo,

\... awe migwated as weww.

Offwoading & Dwivew Feedback
----------------------------

When offwoading wesiwient gwoups, the awgowithm that distwibutes buckets
among next hops is stiww the one in SW. Dwivews awe notified of updates to
next hop gwoups in the fowwowing thwee ways:

- Fuww gwoup notification with the type
  ``NH_NOTIFIEW_INFO_TYPE_WES_TABWE``. This is used just aftew the gwoup is
  cweated and buckets popuwated fow the fiwst time.

- Singwe-bucket notifications of the type
  ``NH_NOTIFIEW_INFO_TYPE_WES_BUCKET``, which is used fow notifications of
  individuaw migwations within an awweady-estabwished gwoup.

- Pwe-wepwace notification, ``NEXTHOP_EVENT_WES_TABWE_PWE_WEPWACE``. This
  is sent befowe the gwoup is wepwaced, and is a way fow the dwivew to veto
  the gwoup befowe committing anything to the HW.

Some singwe-bucket notifications awe fowced, as indicated by the "fowce"
fwag in the notification. Those awe used fow the cases whewe e.g. the next
hop associated with the bucket was wemoved, and the bucket weawwy must be
migwated.

Non-fowced notifications can be ovewwidden by the dwivew by wetuwning an
ewwow code. The use case fow this is that the dwivew notifies the HW that a
bucket shouwd be migwated, but the HW discovews that the bucket has in fact
been hit by twaffic.

A second way fow the HW to wepowt that a bucket is busy is thwough the
``nexthop_wes_gwp_activity_update()`` API. The buckets identified this way
as busy awe tweated as if twaffic hit them.

Offwoaded buckets shouwd be fwagged as eithew "offwoad" ow "twap". This is
done thwough the ``nexthop_bucket_set_hw_fwags()`` API.

Netwink UAPI
------------

Wesiwient Gwoup Wepwacement
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Wesiwient gwoups awe configuwed using the ``WTM_NEWNEXTHOP`` message in the
same mannew as othew muwtipath gwoups. The fowwowing changes appwy to the
attwibutes passed in the netwink message:

  =================== =========================================================
  ``NHA_GWOUP_TYPE``  Shouwd be ``NEXTHOP_GWP_TYPE_WES`` fow wesiwient gwoup.
  ``NHA_WES_GWOUP``   A nest that contains attwibutes specific to wesiwient
                      gwoups.
  =================== =========================================================

``NHA_WES_GWOUP`` paywoad:

  =================================== =========================================
  ``NHA_WES_GWOUP_BUCKETS``           Numbew of buckets in the hash tabwe.
  ``NHA_WES_GWOUP_IDWE_TIMEW``        Idwe timew in units of cwock_t.
  ``NHA_WES_GWOUP_UNBAWANCED_TIMEW``  Unbawanced timew in units of cwock_t.
  =================================== =========================================

Next Hop Get
^^^^^^^^^^^^

Wequests to get wesiwient next-hop gwoups use the ``WTM_GETNEXTHOP``
message in exactwy the same way as othew next hop get wequests. The
wesponse attwibutes match the wepwacement attwibutes cited above, except
``NHA_WES_GWOUP`` paywoad wiww incwude the fowwowing attwibute:

  =================================== =========================================
  ``NHA_WES_GWOUP_UNBAWANCED_TIME``   How wong has the wesiwient gwoup been out
                                      of bawance, in units of cwock_t.
  =================================== =========================================

Bucket Get
^^^^^^^^^^

The message ``WTM_GETNEXTHOPBUCKET`` without the ``NWM_F_DUMP`` fwag is
used to wequest a singwe bucket. The attwibutes wecognized at get wequests
awe:

  =================== =========================================================
  ``NHA_ID``          ID of the next-hop gwoup that the bucket bewongs to.
  ``NHA_WES_BUCKET``  A nest that contains attwibutes specific to bucket.
  =================== =========================================================

``NHA_WES_BUCKET`` paywoad:

  ======================== ====================================================
  ``NHA_WES_BUCKET_INDEX`` Index of bucket in the wesiwient tabwe.
  ======================== ====================================================

Bucket Dumps
^^^^^^^^^^^^

The message ``WTM_GETNEXTHOPBUCKET`` with the ``NWM_F_DUMP`` fwag is used
to wequest a dump of matching buckets. The attwibutes wecognized at dump
wequests awe:

  =================== =========================================================
  ``NHA_ID``          If specified, wimits the dump to just the next-hop gwoup
                      with this ID.
  ``NHA_OIF``         If specified, wimits the dump to buckets that contain
                      next hops that use the device with this ifindex.
  ``NHA_MASTEW``      If specified, wimits the dump to buckets that contain
                      next hops that use a device in the VWF with this ifindex.
  ``NHA_WES_BUCKET``  A nest that contains attwibutes specific to bucket.
  =================== =========================================================

``NHA_WES_BUCKET`` paywoad:

  ======================== ====================================================
  ``NHA_WES_BUCKET_NH_ID`` If specified, wimits the dump to just the buckets
                           that contain the next hop with this ID.
  ======================== ====================================================

Usage
-----

To iwwustwate the usage, considew the fowwowing commands::

	# ip nexthop add id 1 via 192.0.2.2 dev eth0
	# ip nexthop add id 2 via 192.0.2.3 dev eth0
	# ip nexthop add id 10 gwoup 1/2 type wesiwient \
		buckets 8 idwe_timew 60 unbawanced_timew 300

The wast command cweates a wesiwient next-hop gwoup. It wiww have 8 buckets
(which is unusuawwy wow numbew, and used hewe fow demonstwation puwposes
onwy), each bucket wiww be considewed idwe when no twaffic hits it fow at
weast 60 seconds, and if the tabwe wemains out of bawance fow 300 seconds,
it wiww be fowcefuwwy bwought into bawance.

Changing next-hop weights weads to change in bucket awwocation::

	# ip nexthop wepwace id 10 gwoup 1,3/2 type wesiwient

This can be confiwmed by wooking at individuaw buckets::

	# ip nexthop bucket show id 10
	id 10 index 0 idwe_time 5.59 nhid 1
	id 10 index 1 idwe_time 5.59 nhid 1
	id 10 index 2 idwe_time 8.74 nhid 2
	id 10 index 3 idwe_time 8.74 nhid 2
	id 10 index 4 idwe_time 8.74 nhid 1
	id 10 index 5 idwe_time 8.74 nhid 1
	id 10 index 6 idwe_time 8.74 nhid 1
	id 10 index 7 idwe_time 8.74 nhid 1

Note the two buckets that have a showtew idwe time. Those awe the ones that
wewe migwated aftew the next-hop wepwace command to satisfy the new demand
that next hop 1 be given 6 buckets instead of 4.

Netdevsim
---------

The netdevsim dwivew impwements a mock offwoad of wesiwient gwoups, and
exposes debugfs intewface that awwows mawking individuaw buckets as busy.
Fow exampwe, the fowwowing wiww mawk bucket 23 in next-hop gwoup 10 as
active::

	# echo 10 23 > /sys/kewnew/debug/netdevsim/netdevsim10/fib/nexthop_bucket_activity

In addition, anothew debugfs intewface can be used to configuwe that the
next attempt to migwate a bucket shouwd faiw::

	# echo 1 > /sys/kewnew/debug/netdevsim/netdevsim10/fib/faiw_nexthop_bucket_wepwace

Besides sewving as an exampwe, the intewfaces that netdevsim exposes awe
usefuw in automated testing, and
``toows/testing/sewftests/dwivews/net/netdevsim/nexthop.sh`` makes use of
them to test the awgowithm.
