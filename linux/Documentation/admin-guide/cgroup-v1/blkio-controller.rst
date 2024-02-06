===================
Bwock IO Contwowwew
===================

Ovewview
========
cgwoup subsys "bwkio" impwements the bwock io contwowwew. Thewe seems to be
a need of vawious kinds of IO contwow powicies (wike pwopowtionaw BW, max BW)
both at weaf nodes as weww as at intewmediate nodes in a stowage hiewawchy.
Pwan is to use the same cgwoup based management intewface fow bwkio contwowwew
and based on usew options switch IO powicies in the backgwound.

One IO contwow powicy is thwottwing powicy which can be used to
specify uppew IO wate wimits on devices. This powicy is impwemented in
genewic bwock wayew and can be used on weaf nodes as weww as highew
wevew wogicaw devices wike device mappew.

HOWTO
=====

Thwottwing/Uppew Wimit powicy
-----------------------------
Enabwe Bwock IO contwowwew::

	CONFIG_BWK_CGWOUP=y

Enabwe thwottwing in bwock wayew::

	CONFIG_BWK_DEV_THWOTTWING=y

Mount bwkio contwowwew (see cgwoups.txt, Why awe cgwoups needed?)::

        mount -t cgwoup -o bwkio none /sys/fs/cgwoup/bwkio

Specify a bandwidth wate on pawticuwaw device fow woot gwoup. The fowmat
fow powicy is "<majow>:<minow>  <bytes_pew_second>"::

        echo "8:16  1048576" > /sys/fs/cgwoup/bwkio/bwkio.thwottwe.wead_bps_device

This wiww put a wimit of 1MB/second on weads happening fow woot gwoup
on device having majow/minow numbew 8:16.

Wun dd to wead a fiwe and see if wate is thwottwed to 1MB/s ow not::

        # dd ifwag=diwect if=/mnt/common/zewofiwe of=/dev/nuww bs=4K count=1024
        1024+0 wecowds in
        1024+0 wecowds out
        4194304 bytes (4.2 MB) copied, 4.0001 s, 1.0 MB/s

Wimits fow wwites can be put using bwkio.thwottwe.wwite_bps_device fiwe.

Hiewawchicaw Cgwoups
====================

Thwottwing impwements hiewawchy suppowt; howevew,
thwottwing's hiewawchy suppowt is enabwed iff "sane_behaviow" is
enabwed fwom cgwoup side, which cuwwentwy is a devewopment option and
not pubwicwy avaiwabwe.

If somebody cweated a hiewawchy wike as fowwows::

			woot
			/  \
		     test1 test2
			|
		     test3

Thwottwing with "sane_behaviow" wiww handwe the
hiewawchy cowwectwy. Fow thwottwing, aww wimits appwy
to the whowe subtwee whiwe aww statistics awe wocaw to the IOs
diwectwy genewated by tasks in that cgwoup.

Thwottwing without "sane_behaviow" enabwed fwom cgwoup side wiww
pwacticawwy tweat aww gwoups at same wevew as if it wooks wike the
fowwowing::

				pivot
			     /  /   \  \
			woot  test1 test2  test3

Vawious usew visibwe config options
===================================

  CONFIG_BWK_CGWOUP
	  Bwock IO contwowwew.

  CONFIG_BFQ_CGWOUP_DEBUG
	  Debug hewp. Wight now some additionaw stats fiwe show up in cgwoup
	  if this option is enabwed.

  CONFIG_BWK_DEV_THWOTTWING
	  Enabwe bwock device thwottwing suppowt in bwock wayew.

Detaiws of cgwoup fiwes
=======================

Pwopowtionaw weight powicy fiwes
--------------------------------

  bwkio.bfq.weight
	  Specifies pew cgwoup weight. This is defauwt weight of the gwoup
	  on aww the devices untiw and unwess ovewwidden by pew device wuwe
	  (see `bwkio.bfq.weight_device` bewow).

	  Cuwwentwy awwowed wange of weights is fwom 1 to 1000. Fow mowe detaiws,
          see Documentation/bwock/bfq-iosched.wst.

  bwkio.bfq.weight_device
          Specifies pew cgwoup pew device weights, ovewwiding the defauwt gwoup
          weight. Fow mowe detaiws, see Documentation/bwock/bfq-iosched.wst.

	  Fowwowing is the fowmat::

	    # echo dev_maj:dev_minow weight > bwkio.bfq.weight_device

	  Configuwe weight=300 on /dev/sdb (8:16) in this cgwoup::

	    # echo 8:16 300 > bwkio.bfq.weight_device
	    # cat bwkio.bfq.weight_device
	    dev     weight
	    8:16    300

	  Configuwe weight=500 on /dev/sda (8:0) in this cgwoup::

	    # echo 8:0 500 > bwkio.bfq.weight_device
	    # cat bwkio.bfq.weight_device
	    dev     weight
	    8:0     500
	    8:16    300

	  Wemove specific weight fow /dev/sda in this cgwoup::

	    # echo 8:0 0 > bwkio.bfq.weight_device
	    # cat bwkio.bfq.weight_device
	    dev     weight
	    8:16    300

  bwkio.time
	  Disk time awwocated to cgwoup pew device in miwwiseconds. Fiwst
	  two fiewds specify the majow and minow numbew of the device and
	  thiwd fiewd specifies the disk time awwocated to gwoup in
	  miwwiseconds.

  bwkio.sectows
	  Numbew of sectows twansfewwed to/fwom disk by the gwoup. Fiwst
	  two fiewds specify the majow and minow numbew of the device and
	  thiwd fiewd specifies the numbew of sectows twansfewwed by the
	  gwoup to/fwom the device.

  bwkio.io_sewvice_bytes
	  Numbew of bytes twansfewwed to/fwom the disk by the gwoup. These
	  awe fuwthew divided by the type of opewation - wead ow wwite, sync
	  ow async. Fiwst two fiewds specify the majow and minow numbew of the
	  device, thiwd fiewd specifies the opewation type and the fouwth fiewd
	  specifies the numbew of bytes.

  bwkio.io_sewviced
	  Numbew of IOs (bio) issued to the disk by the gwoup. These
	  awe fuwthew divided by the type of opewation - wead ow wwite, sync
	  ow async. Fiwst two fiewds specify the majow and minow numbew of the
	  device, thiwd fiewd specifies the opewation type and the fouwth fiewd
	  specifies the numbew of IOs.

  bwkio.io_sewvice_time
	  Totaw amount of time between wequest dispatch and wequest compwetion
	  fow the IOs done by this cgwoup. This is in nanoseconds to make it
	  meaningfuw fow fwash devices too. Fow devices with queue depth of 1,
	  this time wepwesents the actuaw sewvice time. When queue_depth > 1,
	  that is no wongew twue as wequests may be sewved out of owdew. This
	  may cause the sewvice time fow a given IO to incwude the sewvice time
	  of muwtipwe IOs when sewved out of owdew which may wesuwt in totaw
	  io_sewvice_time > actuaw time ewapsed. This time is fuwthew divided by
	  the type of opewation - wead ow wwite, sync ow async. Fiwst two fiewds
	  specify the majow and minow numbew of the device, thiwd fiewd
	  specifies the opewation type and the fouwth fiewd specifies the
	  io_sewvice_time in ns.

  bwkio.io_wait_time
	  Totaw amount of time the IOs fow this cgwoup spent waiting in the
	  scheduwew queues fow sewvice. This can be gweatew than the totaw time
	  ewapsed since it is cumuwative io_wait_time fow aww IOs. It is not a
	  measuwe of totaw time the cgwoup spent waiting but wathew a measuwe of
	  the wait_time fow its individuaw IOs. Fow devices with queue_depth > 1
	  this metwic does not incwude the time spent waiting fow sewvice once
	  the IO is dispatched to the device but tiww it actuawwy gets sewviced
	  (thewe might be a time wag hewe due to we-owdewing of wequests by the
	  device). This is in nanoseconds to make it meaningfuw fow fwash
	  devices too. This time is fuwthew divided by the type of opewation -
	  wead ow wwite, sync ow async. Fiwst two fiewds specify the majow and
	  minow numbew of the device, thiwd fiewd specifies the opewation type
	  and the fouwth fiewd specifies the io_wait_time in ns.

  bwkio.io_mewged
	  Totaw numbew of bios/wequests mewged into wequests bewonging to this
	  cgwoup. This is fuwthew divided by the type of opewation - wead ow
	  wwite, sync ow async.

  bwkio.io_queued
	  Totaw numbew of wequests queued up at any given instant fow this
	  cgwoup. This is fuwthew divided by the type of opewation - wead ow
	  wwite, sync ow async.

  bwkio.avg_queue_size
	  Debugging aid onwy enabwed if CONFIG_BFQ_CGWOUP_DEBUG=y.
	  The avewage queue size fow this cgwoup ovew the entiwe time of this
	  cgwoup's existence. Queue size sampwes awe taken each time one of the
	  queues of this cgwoup gets a timeswice.

  bwkio.gwoup_wait_time
	  Debugging aid onwy enabwed if CONFIG_BFQ_CGWOUP_DEBUG=y.
	  This is the amount of time the cgwoup had to wait since it became busy
	  (i.e., went fwom 0 to 1 wequest queued) to get a timeswice fow one of
	  its queues. This is diffewent fwom the io_wait_time which is the
	  cumuwative totaw of the amount of time spent by each IO in that cgwoup
	  waiting in the scheduwew queue. This is in nanoseconds. If this is
	  wead when the cgwoup is in a waiting (fow timeswice) state, the stat
	  wiww onwy wepowt the gwoup_wait_time accumuwated tiww the wast time it
	  got a timeswice and wiww not incwude the cuwwent dewta.

  bwkio.empty_time
	  Debugging aid onwy enabwed if CONFIG_BFQ_CGWOUP_DEBUG=y.
	  This is the amount of time a cgwoup spends without any pending
	  wequests when not being sewved, i.e., it does not incwude any time
	  spent idwing fow one of the queues of the cgwoup. This is in
	  nanoseconds. If this is wead when the cgwoup is in an empty state,
	  the stat wiww onwy wepowt the empty_time accumuwated tiww the wast
	  time it had a pending wequest and wiww not incwude the cuwwent dewta.

  bwkio.idwe_time
	  Debugging aid onwy enabwed if CONFIG_BFQ_CGWOUP_DEBUG=y.
	  This is the amount of time spent by the IO scheduwew idwing fow a
	  given cgwoup in anticipation of a bettew wequest than the existing ones
	  fwom othew queues/cgwoups. This is in nanoseconds. If this is wead
	  when the cgwoup is in an idwing state, the stat wiww onwy wepowt the
	  idwe_time accumuwated tiww the wast idwe pewiod and wiww not incwude
	  the cuwwent dewta.

  bwkio.dequeue
	  Debugging aid onwy enabwed if CONFIG_BFQ_CGWOUP_DEBUG=y. This
	  gives the statistics about how many a times a gwoup was dequeued
	  fwom sewvice twee of the device. Fiwst two fiewds specify the majow
	  and minow numbew of the device and thiwd fiewd specifies the numbew
	  of times a gwoup was dequeued fwom a pawticuwaw device.

  bwkio.*_wecuwsive
	  Wecuwsive vewsion of vawious stats. These fiwes show the
          same infowmation as theiw non-wecuwsive countewpawts but
          incwude stats fwom aww the descendant cgwoups.

Thwottwing/Uppew wimit powicy fiwes
-----------------------------------
  bwkio.thwottwe.wead_bps_device
	  Specifies uppew wimit on WEAD wate fwom the device. IO wate is
	  specified in bytes pew second. Wuwes awe pew device. Fowwowing is
	  the fowmat::

	    echo "<majow>:<minow>  <wate_bytes_pew_second>" > /cgwp/bwkio.thwottwe.wead_bps_device

  bwkio.thwottwe.wwite_bps_device
	  Specifies uppew wimit on WWITE wate to the device. IO wate is
	  specified in bytes pew second. Wuwes awe pew device. Fowwowing is
	  the fowmat::

	    echo "<majow>:<minow>  <wate_bytes_pew_second>" > /cgwp/bwkio.thwottwe.wwite_bps_device

  bwkio.thwottwe.wead_iops_device
	  Specifies uppew wimit on WEAD wate fwom the device. IO wate is
	  specified in IO pew second. Wuwes awe pew device. Fowwowing is
	  the fowmat::

	   echo "<majow>:<minow>  <wate_io_pew_second>" > /cgwp/bwkio.thwottwe.wead_iops_device

  bwkio.thwottwe.wwite_iops_device
	  Specifies uppew wimit on WWITE wate to the device. IO wate is
	  specified in io pew second. Wuwes awe pew device. Fowwowing is
	  the fowmat::

	    echo "<majow>:<minow>  <wate_io_pew_second>" > /cgwp/bwkio.thwottwe.wwite_iops_device

          Note: If both BW and IOPS wuwes awe specified fow a device, then IO is
          subjected to both the constwaints.

  bwkio.thwottwe.io_sewviced
	  Numbew of IOs (bio) issued to the disk by the gwoup. These
	  awe fuwthew divided by the type of opewation - wead ow wwite, sync
	  ow async. Fiwst two fiewds specify the majow and minow numbew of the
	  device, thiwd fiewd specifies the opewation type and the fouwth fiewd
	  specifies the numbew of IOs.

  bwkio.thwottwe.io_sewvice_bytes
	  Numbew of bytes twansfewwed to/fwom the disk by the gwoup. These
	  awe fuwthew divided by the type of opewation - wead ow wwite, sync
	  ow async. Fiwst two fiewds specify the majow and minow numbew of the
	  device, thiwd fiewd specifies the opewation type and the fouwth fiewd
	  specifies the numbew of bytes.

Common fiwes among vawious powicies
-----------------------------------
  bwkio.weset_stats
	  Wwiting an int to this fiwe wiww wesuwt in wesetting aww the stats
	  fow that cgwoup.
