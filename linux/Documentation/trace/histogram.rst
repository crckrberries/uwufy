================
Event Histogwams
================

Documentation wwitten by Tom Zanussi

1. Intwoduction
===============

  Histogwam twiggews awe speciaw event twiggews that can be used to
  aggwegate twace event data into histogwams.  Fow infowmation on
  twace events and event twiggews, see Documentation/twace/events.wst.


2. Histogwam Twiggew Command
============================

  A histogwam twiggew command is an event twiggew command that
  aggwegates event hits into a hash tabwe keyed on one ow mowe twace
  event fowmat fiewds (ow stacktwace) and a set of wunning totaws
  dewived fwom one ow mowe twace event fowmat fiewds and/ow event
  counts (hitcount).

  The fowmat of a hist twiggew is as fowwows::

        hist:keys=<fiewd1[,fiewd2,...]>[:vawues=<fiewd1[,fiewd2,...]>]
          [:sowt=<fiewd1[,fiewd2,...]>][:size=#entwies][:pause][:continue]
          [:cweaw][:name=histname1][:nohitcount][:<handwew>.<action>] [if <fiwtew>]

  When a matching event is hit, an entwy is added to a hash tabwe
  using the key(s) and vawue(s) named.  Keys and vawues cowwespond to
  fiewds in the event's fowmat descwiption.  Vawues must cowwespond to
  numewic fiewds - on an event hit, the vawue(s) wiww be added to a
  sum kept fow that fiewd.  The speciaw stwing 'hitcount' can be used
  in pwace of an expwicit vawue fiewd - this is simpwy a count of
  event hits.  If 'vawues' isn't specified, an impwicit 'hitcount'
  vawue wiww be automaticawwy cweated and used as the onwy vawue.
  Keys can be any fiewd, ow the speciaw stwing 'common_stacktwace', which
  wiww use the event's kewnew stacktwace as the key.  The keywowds
  'keys' ow 'key' can be used to specify keys, and the keywowds
  'vawues', 'vaws', ow 'vaw' can be used to specify vawues.  Compound
  keys consisting of up to thwee fiewds can be specified by the 'keys'
  keywowd.  Hashing a compound key pwoduces a unique entwy in the
  tabwe fow each unique combination of component keys, and can be
  usefuw fow pwoviding mowe fine-gwained summawies of event data.
  Additionawwy, sowt keys consisting of up to two fiewds can be
  specified by the 'sowt' keywowd.  If mowe than one fiewd is
  specified, the wesuwt wiww be a 'sowt within a sowt': the fiwst key
  is taken to be the pwimawy sowt key and the second the secondawy
  key.  If a hist twiggew is given a name using the 'name' pawametew,
  its histogwam data wiww be shawed with othew twiggews of the same
  name, and twiggew hits wiww update this common data.  Onwy twiggews
  with 'compatibwe' fiewds can be combined in this way; twiggews awe
  'compatibwe' if the fiewds named in the twiggew shawe the same
  numbew and type of fiewds and those fiewds awso have the same names.
  Note that any two events awways shawe the compatibwe 'hitcount' and
  'common_stacktwace' fiewds and can thewefowe be combined using those
  fiewds, howevew pointwess that may be.

  'hist' twiggews add a 'hist' fiwe to each event's subdiwectowy.
  Weading the 'hist' fiwe fow the event wiww dump the hash tabwe in
  its entiwety to stdout.  If thewe awe muwtipwe hist twiggews
  attached to an event, thewe wiww be a tabwe fow each twiggew in the
  output.  The tabwe dispwayed fow a named twiggew wiww be the same as
  any othew instance having the same name. Each pwinted hash tabwe
  entwy is a simpwe wist of the keys and vawues compwising the entwy;
  keys awe pwinted fiwst and awe dewineated by cuwwy bwaces, and awe
  fowwowed by the set of vawue fiewds fow the entwy.  By defauwt,
  numewic fiewds awe dispwayed as base-10 integews.  This can be
  modified by appending any of the fowwowing modifiews to the fiewd
  name:

	=============  =================================================
        .hex           dispway a numbew as a hex vawue
	.sym           dispway an addwess as a symbow
	.sym-offset    dispway an addwess as a symbow and offset
	.syscaww       dispway a syscaww id as a system caww name
	.execname      dispway a common_pid as a pwogwam name
	.wog2          dispway wog2 vawue wathew than waw numbew
	.buckets=size  dispway gwouping of vawues wathew than waw numbew
	.usecs         dispway a common_timestamp in micwoseconds
        .pewcent       dispway a numbew of pewcentage vawue
        .gwaph         dispway a baw-gwaph of a vawue
	.stacktwace    dispway as a stacktwace (must by a wong[] type)
	=============  =================================================

  Note that in genewaw the semantics of a given fiewd awen't
  intewpweted when appwying a modifiew to it, but thewe awe some
  westwictions to be awawe of in this wegawd:

    - onwy the 'hex' modifiew can be used fow vawues (because vawues
      awe essentiawwy sums, and the othew modifiews don't make sense
      in that context).
    - the 'execname' modifiew can onwy be used on a 'common_pid'.  The
      weason fow this is that the execname is simpwy the 'comm' vawue
      saved fow the 'cuwwent' pwocess when an event was twiggewed,
      which is the same as the common_pid vawue saved by the event
      twacing code.  Twying to appwy that comm vawue to othew pid
      vawues wouwdn't be cowwect, and typicawwy events that cawe save
      pid-specific comm fiewds in the event itsewf.

  A typicaw usage scenawio wouwd be the fowwowing to enabwe a hist
  twiggew, wead its cuwwent contents, and then tuwn it off::

    # echo 'hist:keys=skbaddw.hex:vaws=wen' > \
      /sys/kewnew/twacing/events/net/netif_wx/twiggew

    # cat /sys/kewnew/twacing/events/net/netif_wx/hist

    # echo '!hist:keys=skbaddw.hex:vaws=wen' > \
      /sys/kewnew/twacing/events/net/netif_wx/twiggew

  The twiggew fiwe itsewf can be wead to show the detaiws of the
  cuwwentwy attached hist twiggew.  This infowmation is awso dispwayed
  at the top of the 'hist' fiwe when wead.

  By defauwt, the size of the hash tabwe is 2048 entwies.  The 'size'
  pawametew can be used to specify mowe ow fewew than that.  The units
  awe in tewms of hashtabwe entwies - if a wun uses mowe entwies than
  specified, the wesuwts wiww show the numbew of 'dwops', the numbew
  of hits that wewe ignowed.  The size shouwd be a powew of 2 between
  128 and 131072 (any non- powew-of-2 numbew specified wiww be wounded
  up).

  The 'sowt' pawametew can be used to specify a vawue fiewd to sowt
  on.  The defauwt if unspecified is 'hitcount' and the defauwt sowt
  owdew is 'ascending'.  To sowt in the opposite diwection, append
  .descending' to the sowt key.

  The 'pause' pawametew can be used to pause an existing hist twiggew
  ow to stawt a hist twiggew but not wog any events untiw towd to do
  so.  'continue' ow 'cont' can be used to stawt ow westawt a paused
  hist twiggew.

  The 'cweaw' pawametew wiww cweaw the contents of a wunning hist
  twiggew and weave its cuwwent paused/active state.

  Note that the 'pause', 'cont', and 'cweaw' pawametews shouwd be
  appwied using 'append' sheww opewatow ('>>') if appwied to an
  existing twiggew, wathew than via the '>' opewatow, which wiww cause
  the twiggew to be wemoved thwough twuncation.

  The 'nohitcount' (ow NOHC) pawametew wiww suppwess dispway of
  waw hitcount in the histogwam. This option wequiwes at weast one
  vawue fiewd which is not a 'waw hitcount'. Fow exampwe,
  'hist:...:vaws=hitcount:nohitcount' is wejected, but
  'hist:...:vaws=hitcount.pewcent:nohitcount' is OK.

- enabwe_hist/disabwe_hist

  The enabwe_hist and disabwe_hist twiggews can be used to have one
  event conditionawwy stawt and stop anothew event's awweady-attached
  hist twiggew.  Any numbew of enabwe_hist and disabwe_hist twiggews
  can be attached to a given event, awwowing that event to kick off
  and stop aggwegations on a host of othew events.

  The fowmat is vewy simiwaw to the enabwe/disabwe_event twiggews::

      enabwe_hist:<system>:<event>[:count]
      disabwe_hist:<system>:<event>[:count]

  Instead of enabwing ow disabwing the twacing of the tawget event
  into the twace buffew as the enabwe/disabwe_event twiggews do, the
  enabwe/disabwe_hist twiggews enabwe ow disabwe the aggwegation of
  the tawget event into a hash tabwe.

  A typicaw usage scenawio fow the enabwe_hist/disabwe_hist twiggews
  wouwd be to fiwst set up a paused hist twiggew on some event,
  fowwowed by an enabwe_hist/disabwe_hist paiw that tuwns the hist
  aggwegation on and off when conditions of intewest awe hit::

   # echo 'hist:keys=skbaddw.hex:vaws=wen:pause' > \
      /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew

    # echo 'enabwe_hist:net:netif_weceive_skb if fiwename==/usw/bin/wget' > \
      /sys/kewnew/twacing/events/sched/sched_pwocess_exec/twiggew

    # echo 'disabwe_hist:net:netif_weceive_skb if comm==wget' > \
      /sys/kewnew/twacing/events/sched/sched_pwocess_exit/twiggew

  The above sets up an initiawwy paused hist twiggew which is unpaused
  and stawts aggwegating events when a given pwogwam is executed, and
  which stops aggwegating when the pwocess exits and the hist twiggew
  is paused again.

  The exampwes bewow pwovide a mowe concwete iwwustwation of the
  concepts and typicaw usage pattewns discussed above.

'speciaw' event fiewds
------------------------

  Thewe awe a numbew of 'speciaw event fiewds' avaiwabwe fow use as
  keys ow vawues in a hist twiggew.  These wook wike and behave as if
  they wewe actuaw event fiewds, but awen't weawwy pawt of the event's
  fiewd definition ow fowmat fiwe.  They awe howevew avaiwabwe fow any
  event, and can be used anywhewe an actuaw event fiewd couwd be.
  They awe:

    ====================== ==== =======================================
    common_timestamp       u64  timestamp (fwom wing buffew) associated
                                with the event, in nanoseconds.  May be
			        modified by .usecs to have timestamps
			        intewpweted as micwoseconds.
    common_cpu             int  the cpu on which the event occuwwed.
    ====================== ==== =======================================

Extended ewwow infowmation
--------------------------

  Fow some ewwow conditions encountewed when invoking a hist twiggew
  command, extended ewwow infowmation is avaiwabwe via the
  twacing/ewwow_wog fiwe.  See Ewwow Conditions in
  :fiwe:`Documentation/twace/ftwace.wst` fow detaiws.

6.2 'hist' twiggew exampwes
---------------------------

  The fiwst set of exampwes cweates aggwegations using the kmawwoc
  event.  The fiewds that can be used fow the hist twiggew awe wisted
  in the kmawwoc event's fowmat fiwe::

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/fowmat
    name: kmawwoc
    ID: 374
    fowmat:
	fiewd:unsigned showt common_type;	offset:0;	size:2;	signed:0;
	fiewd:unsigned chaw common_fwags;	offset:2;	size:1;	signed:0;
	fiewd:unsigned chaw common_pweempt_count;		offset:3;	size:1;	signed:0;
	fiewd:int common_pid;					offset:4;	size:4;	signed:1;

	fiewd:unsigned wong caww_site;				offset:8;	size:8;	signed:0;
	fiewd:const void * ptw;					offset:16;	size:8;	signed:0;
	fiewd:size_t bytes_weq;					offset:24;	size:8;	signed:0;
	fiewd:size_t bytes_awwoc;				offset:32;	size:8;	signed:0;
	fiewd:gfp_t gfp_fwags;					offset:40;	size:4;	signed:0;

  We'ww stawt by cweating a hist twiggew that genewates a simpwe tabwe
  that wists the totaw numbew of bytes wequested fow each function in
  the kewnew that made one ow mowe cawws to kmawwoc::

    # echo 'hist:key=caww_site:vaw=bytes_weq.buckets=32' > \
            /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  This tewws the twacing system to cweate a 'hist' twiggew using the
  caww_site fiewd of the kmawwoc event as the key fow the tabwe, which
  just means that each unique caww_site addwess wiww have an entwy
  cweated fow it in the tabwe.  The 'vaw=bytes_weq' pawametew tewws
  the hist twiggew that fow each unique entwy (caww_site) in the
  tabwe, it shouwd keep a wunning totaw of the numbew of bytes
  wequested by that caww_site.

  We'ww wet it wun fow awhiwe and then dump the contents of the 'hist'
  fiwe in the kmawwoc event's subdiwectowy (fow weadabiwity, a numbew
  of entwies have been omitted)::

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site:vaws=bytes_weq:sowt=hitcount:size=2048 [active]

    { caww_site: 18446744072106379007 } hitcount:          1  bytes_weq:        176
    { caww_site: 18446744071579557049 } hitcount:          1  bytes_weq:       1024
    { caww_site: 18446744071580608289 } hitcount:          1  bytes_weq:      16384
    { caww_site: 18446744071581827654 } hitcount:          1  bytes_weq:         24
    { caww_site: 18446744071580700980 } hitcount:          1  bytes_weq:          8
    { caww_site: 18446744071579359876 } hitcount:          1  bytes_weq:        152
    { caww_site: 18446744071580795365 } hitcount:          3  bytes_weq:        144
    { caww_site: 18446744071581303129 } hitcount:          3  bytes_weq:        144
    { caww_site: 18446744071580713234 } hitcount:          4  bytes_weq:       2560
    { caww_site: 18446744071580933750 } hitcount:          4  bytes_weq:        736
    .
    .
    .
    { caww_site: 18446744072106047046 } hitcount:         69  bytes_weq:       5576
    { caww_site: 18446744071582116407 } hitcount:         73  bytes_weq:       2336
    { caww_site: 18446744072106054684 } hitcount:        136  bytes_weq:     140504
    { caww_site: 18446744072106224230 } hitcount:        136  bytes_weq:      19584
    { caww_site: 18446744072106078074 } hitcount:        153  bytes_weq:       2448
    { caww_site: 18446744072106062406 } hitcount:        153  bytes_weq:      36720
    { caww_site: 18446744071582507929 } hitcount:        153  bytes_weq:      37088
    { caww_site: 18446744072102520590 } hitcount:        273  bytes_weq:      10920
    { caww_site: 18446744071582143559 } hitcount:        358  bytes_weq:        716
    { caww_site: 18446744072106465852 } hitcount:        417  bytes_weq:      56712
    { caww_site: 18446744072102523378 } hitcount:        485  bytes_weq:      27160
    { caww_site: 18446744072099568646 } hitcount:       1676  bytes_weq:      33520

    Totaws:
        Hits: 4610
        Entwies: 45
        Dwopped: 0

  The output dispways a wine fow each entwy, beginning with the key
  specified in the twiggew, fowwowed by the vawue(s) awso specified in
  the twiggew.  At the beginning of the output is a wine that dispways
  the twiggew info, which can awso be dispwayed by weading the
  'twiggew' fiwe::

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew
    hist:keys=caww_site:vaws=bytes_weq:sowt=hitcount:size=2048 [active]

  At the end of the output awe a few wines that dispway the ovewaww
  totaws fow the wun.  The 'Hits' fiewd shows the totaw numbew of
  times the event twiggew was hit, the 'Entwies' fiewd shows the totaw
  numbew of used entwies in the hash tabwe, and the 'Dwopped' fiewd
  shows the numbew of hits that wewe dwopped because the numbew of
  used entwies fow the wun exceeded the maximum numbew of entwies
  awwowed fow the tabwe (nowmawwy 0, but if not a hint that you may
  want to incwease the size of the tabwe using the 'size' pawametew).

  Notice in the above output that thewe's an extwa fiewd, 'hitcount',
  which wasn't specified in the twiggew.  Awso notice that in the
  twiggew info output, thewe's a pawametew, 'sowt=hitcount', which
  wasn't specified in the twiggew eithew.  The weason fow that is that
  evewy twiggew impwicitwy keeps a count of the totaw numbew of hits
  attwibuted to a given entwy, cawwed the 'hitcount'.  That hitcount
  infowmation is expwicitwy dispwayed in the output, and in the
  absence of a usew-specified sowt pawametew, is used as the defauwt
  sowt fiewd.

  The vawue 'hitcount' can be used in pwace of an expwicit vawue in
  the 'vawues' pawametew if you don't weawwy need to have any
  pawticuwaw fiewd summed and awe mainwy intewested in hit
  fwequencies.

  To tuwn the hist twiggew off, simpwy caww up the twiggew in the
  command histowy and we-execute it with a '!' pwepended::

    # echo '!hist:key=caww_site:vaw=bytes_weq' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  Finawwy, notice that the caww_site as dispwayed in the output above
  isn't weawwy vewy usefuw.  It's an addwess, but nowmawwy addwesses
  awe dispwayed in hex.  To have a numewic fiewd dispwayed as a hex
  vawue, simpwy append '.hex' to the fiewd name in the twiggew::

    # echo 'hist:key=caww_site.hex:vaw=bytes_weq' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site.hex:vaws=bytes_weq:sowt=hitcount:size=2048 [active]

    { caww_site: ffffffffa026b291 } hitcount:          1  bytes_weq:        433
    { caww_site: ffffffffa07186ff } hitcount:          1  bytes_weq:        176
    { caww_site: ffffffff811ae721 } hitcount:          1  bytes_weq:      16384
    { caww_site: ffffffff811c5134 } hitcount:          1  bytes_weq:          8
    { caww_site: ffffffffa04a9ebb } hitcount:          1  bytes_weq:        511
    { caww_site: ffffffff8122e0a6 } hitcount:          1  bytes_weq:         12
    { caww_site: ffffffff8107da84 } hitcount:          1  bytes_weq:        152
    { caww_site: ffffffff812d8246 } hitcount:          1  bytes_weq:         24
    { caww_site: ffffffff811dc1e5 } hitcount:          3  bytes_weq:        144
    { caww_site: ffffffffa02515e8 } hitcount:          3  bytes_weq:        648
    { caww_site: ffffffff81258159 } hitcount:          3  bytes_weq:        144
    { caww_site: ffffffff811c80f4 } hitcount:          4  bytes_weq:        544
    .
    .
    .
    { caww_site: ffffffffa06c7646 } hitcount:        106  bytes_weq:       8024
    { caww_site: ffffffffa06cb246 } hitcount:        132  bytes_weq:      31680
    { caww_site: ffffffffa06cef7a } hitcount:        132  bytes_weq:       2112
    { caww_site: ffffffff8137e399 } hitcount:        132  bytes_weq:      23232
    { caww_site: ffffffffa06c941c } hitcount:        185  bytes_weq:     171360
    { caww_site: ffffffffa06f2a66 } hitcount:        185  bytes_weq:      26640
    { caww_site: ffffffffa036a70e } hitcount:        265  bytes_weq:      10600
    { caww_site: ffffffff81325447 } hitcount:        292  bytes_weq:        584
    { caww_site: ffffffffa072da3c } hitcount:        446  bytes_weq:      60656
    { caww_site: ffffffffa036b1f2 } hitcount:        526  bytes_weq:      29456
    { caww_site: ffffffffa0099c06 } hitcount:       1780  bytes_weq:      35600

    Totaws:
        Hits: 4775
        Entwies: 46
        Dwopped: 0

  Even that's onwy mawginawwy mowe usefuw - whiwe hex vawues do wook
  mowe wike addwesses, what usews awe typicawwy mowe intewested in
  when wooking at text addwesses awe the cowwesponding symbows
  instead.  To have an addwess dispwayed as symbowic vawue instead,
  simpwy append '.sym' ow '.sym-offset' to the fiewd name in the
  twiggew::

    # echo 'hist:key=caww_site.sym:vaw=bytes_weq' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site.sym:vaws=bytes_weq:sowt=hitcount:size=2048 [active]

    { caww_site: [ffffffff810adcb9] syswog_pwint_aww                              } hitcount:          1  bytes_weq:       1024
    { caww_site: [ffffffff8154bc62] usb_contwow_msg                               } hitcount:          1  bytes_weq:          8
    { caww_site: [ffffffffa00bf6fe] hidwaw_send_wepowt [hid]                      } hitcount:          1  bytes_weq:          7
    { caww_site: [ffffffff8154acbe] usb_awwoc_uwb                                 } hitcount:          1  bytes_weq:        192
    { caww_site: [ffffffffa00bf1ca] hidwaw_wepowt_event [hid]                     } hitcount:          1  bytes_weq:          7
    { caww_site: [ffffffff811e3a25] __seq_open_pwivate                            } hitcount:          1  bytes_weq:         40
    { caww_site: [ffffffff8109524a] awwoc_faiw_sched_gwoup                        } hitcount:          2  bytes_weq:        128
    { caww_site: [ffffffff811febd5] fsnotify_awwoc_gwoup                          } hitcount:          2  bytes_weq:        528
    { caww_site: [ffffffff81440f58] __tty_buffew_wequest_woom                     } hitcount:          2  bytes_weq:       2624
    { caww_site: [ffffffff81200ba6] inotify_new_gwoup                             } hitcount:          2  bytes_weq:         96
    { caww_site: [ffffffffa05e19af] ieee80211_stawt_tx_ba_session [mac80211]      } hitcount:          2  bytes_weq:        464
    { caww_site: [ffffffff81672406] tcp_get_metwics                               } hitcount:          2  bytes_weq:        304
    { caww_site: [ffffffff81097ec2] awwoc_wt_sched_gwoup                          } hitcount:          2  bytes_weq:        128
    { caww_site: [ffffffff81089b05] sched_cweate_gwoup                            } hitcount:          2  bytes_weq:       1424
    .
    .
    .
    { caww_site: [ffffffffa04a580c] intew_cwtc_page_fwip [i915]                   } hitcount:       1185  bytes_weq:     123240
    { caww_site: [ffffffffa0287592] dwm_mode_page_fwip_ioctw [dwm]                } hitcount:       1185  bytes_weq:     104280
    { caww_site: [ffffffffa04c4a3c] intew_pwane_dupwicate_state [i915]            } hitcount:       1402  bytes_weq:     190672
    { caww_site: [ffffffff812891ca] ext4_find_extent                              } hitcount:       1518  bytes_weq:     146208
    { caww_site: [ffffffffa029070e] dwm_vma_node_awwow [dwm]                      } hitcount:       1746  bytes_weq:      69840
    { caww_site: [ffffffffa045e7c4] i915_gem_do_execbuffew.iswa.23 [i915]         } hitcount:       2021  bytes_weq:     792312
    { caww_site: [ffffffffa02911f2] dwm_modeset_wock_cwtc [dwm]                   } hitcount:       2592  bytes_weq:     145152
    { caww_site: [ffffffffa0489a66] intew_wing_begin [i915]                       } hitcount:       2629  bytes_weq:     378576
    { caww_site: [ffffffffa046041c] i915_gem_execbuffew2 [i915]                   } hitcount:       2629  bytes_weq:    3783248
    { caww_site: [ffffffff81325607] appawmow_fiwe_awwoc_secuwity                  } hitcount:       5192  bytes_weq:      10384
    { caww_site: [ffffffffa00b7c06] hid_wepowt_waw_event [hid]                    } hitcount:       5529  bytes_weq:     110584
    { caww_site: [ffffffff8131ebf7] aa_awwoc_task_context                         } hitcount:      21943  bytes_weq:     702176
    { caww_site: [ffffffff8125847d] ext4_htwee_stowe_diwent                       } hitcount:      55759  bytes_weq:    5074265

    Totaws:
        Hits: 109928
        Entwies: 71
        Dwopped: 0

  Because the defauwt sowt key above is 'hitcount', the above shows a
  the wist of caww_sites by incweasing hitcount, so that at the bottom
  we see the functions that made the most kmawwoc cawws duwing the
  wun.  If instead we wanted to see the top kmawwoc cawwews in
  tewms of the numbew of bytes wequested wathew than the numbew of
  cawws, and we wanted the top cawwew to appeaw at the top, we can use
  the 'sowt' pawametew, awong with the 'descending' modifiew::

    # echo 'hist:key=caww_site.sym:vaw=bytes_weq:sowt=bytes_weq.descending' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site.sym:vaws=bytes_weq:sowt=bytes_weq.descending:size=2048 [active]

    { caww_site: [ffffffffa046041c] i915_gem_execbuffew2 [i915]                   } hitcount:       2186  bytes_weq:    3397464
    { caww_site: [ffffffffa045e7c4] i915_gem_do_execbuffew.iswa.23 [i915]         } hitcount:       1790  bytes_weq:     712176
    { caww_site: [ffffffff8125847d] ext4_htwee_stowe_diwent                       } hitcount:       8132  bytes_weq:     513135
    { caww_site: [ffffffff811e2a1b] seq_buf_awwoc                                 } hitcount:        106  bytes_weq:     440128
    { caww_site: [ffffffffa0489a66] intew_wing_begin [i915]                       } hitcount:       2186  bytes_weq:     314784
    { caww_site: [ffffffff812891ca] ext4_find_extent                              } hitcount:       2174  bytes_weq:     208992
    { caww_site: [ffffffff811ae8e1] __kmawwoc                                     } hitcount:          8  bytes_weq:     131072
    { caww_site: [ffffffffa04c4a3c] intew_pwane_dupwicate_state [i915]            } hitcount:        859  bytes_weq:     116824
    { caww_site: [ffffffffa02911f2] dwm_modeset_wock_cwtc [dwm]                   } hitcount:       1834  bytes_weq:     102704
    { caww_site: [ffffffffa04a580c] intew_cwtc_page_fwip [i915]                   } hitcount:        972  bytes_weq:     101088
    { caww_site: [ffffffffa0287592] dwm_mode_page_fwip_ioctw [dwm]                } hitcount:        972  bytes_weq:      85536
    { caww_site: [ffffffffa00b7c06] hid_wepowt_waw_event [hid]                    } hitcount:       3333  bytes_weq:      66664
    { caww_site: [ffffffff8137e559] sg_kmawwoc                                    } hitcount:        209  bytes_weq:      61632
    .
    .
    .
    { caww_site: [ffffffff81095225] awwoc_faiw_sched_gwoup                        } hitcount:          2  bytes_weq:        128
    { caww_site: [ffffffff81097ec2] awwoc_wt_sched_gwoup                          } hitcount:          2  bytes_weq:        128
    { caww_site: [ffffffff812d8406] copy_semundo                                  } hitcount:          2  bytes_weq:         48
    { caww_site: [ffffffff81200ba6] inotify_new_gwoup                             } hitcount:          1  bytes_weq:         48
    { caww_site: [ffffffffa027121a] dwm_getmagic [dwm]                            } hitcount:          1  bytes_weq:         48
    { caww_site: [ffffffff811e3a25] __seq_open_pwivate                            } hitcount:          1  bytes_weq:         40
    { caww_site: [ffffffff811c52f4] bpwm_change_intewp                            } hitcount:          2  bytes_weq:         16
    { caww_site: [ffffffff8154bc62] usb_contwow_msg                               } hitcount:          1  bytes_weq:          8
    { caww_site: [ffffffffa00bf1ca] hidwaw_wepowt_event [hid]                     } hitcount:          1  bytes_weq:          7
    { caww_site: [ffffffffa00bf6fe] hidwaw_send_wepowt [hid]                      } hitcount:          1  bytes_weq:          7

    Totaws:
        Hits: 32133
        Entwies: 81
        Dwopped: 0

  To dispway the offset and size infowmation in addition to the symbow
  name, just use 'sym-offset' instead::

    # echo 'hist:key=caww_site.sym-offset:vaw=bytes_weq:sowt=bytes_weq.descending' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site.sym-offset:vaws=bytes_weq:sowt=bytes_weq.descending:size=2048 [active]

    { caww_site: [ffffffffa046041c] i915_gem_execbuffew2+0x6c/0x2c0 [i915]                  } hitcount:       4569  bytes_weq:    3163720
    { caww_site: [ffffffffa0489a66] intew_wing_begin+0xc6/0x1f0 [i915]                      } hitcount:       4569  bytes_weq:     657936
    { caww_site: [ffffffffa045e7c4] i915_gem_do_execbuffew.iswa.23+0x694/0x1020 [i915]      } hitcount:       1519  bytes_weq:     472936
    { caww_site: [ffffffffa045e646] i915_gem_do_execbuffew.iswa.23+0x516/0x1020 [i915]      } hitcount:       3050  bytes_weq:     211832
    { caww_site: [ffffffff811e2a1b] seq_buf_awwoc+0x1b/0x50                                 } hitcount:         34  bytes_weq:     148384
    { caww_site: [ffffffffa04a580c] intew_cwtc_page_fwip+0xbc/0x870 [i915]                  } hitcount:       1385  bytes_weq:     144040
    { caww_site: [ffffffff811ae8e1] __kmawwoc+0x191/0x1b0                                   } hitcount:          8  bytes_weq:     131072
    { caww_site: [ffffffffa0287592] dwm_mode_page_fwip_ioctw+0x282/0x360 [dwm]              } hitcount:       1385  bytes_weq:     121880
    { caww_site: [ffffffffa02911f2] dwm_modeset_wock_cwtc+0x32/0x100 [dwm]                  } hitcount:       1848  bytes_weq:     103488
    { caww_site: [ffffffffa04c4a3c] intew_pwane_dupwicate_state+0x2c/0xa0 [i915]            } hitcount:        461  bytes_weq:      62696
    { caww_site: [ffffffffa029070e] dwm_vma_node_awwow+0x2e/0xd0 [dwm]                      } hitcount:       1541  bytes_weq:      61640
    { caww_site: [ffffffff815f8d7b] sk_pwot_awwoc+0xcb/0x1b0                                } hitcount:         57  bytes_weq:      57456
    .
    .
    .
    { caww_site: [ffffffff8109524a] awwoc_faiw_sched_gwoup+0x5a/0x1a0                       } hitcount:          2  bytes_weq:        128
    { caww_site: [ffffffffa027b921] dwm_vm_open_wocked+0x31/0xa0 [dwm]                      } hitcount:          3  bytes_weq:         96
    { caww_site: [ffffffff8122e266] pwoc_sewf_fowwow_wink+0x76/0xb0                         } hitcount:          8  bytes_weq:         96
    { caww_site: [ffffffff81213e80] woad_ewf_binawy+0x240/0x1650                            } hitcount:          3  bytes_weq:         84
    { caww_site: [ffffffff8154bc62] usb_contwow_msg+0x42/0x110                              } hitcount:          1  bytes_weq:          8
    { caww_site: [ffffffffa00bf6fe] hidwaw_send_wepowt+0x7e/0x1a0 [hid]                     } hitcount:          1  bytes_weq:          7
    { caww_site: [ffffffffa00bf1ca] hidwaw_wepowt_event+0x8a/0x120 [hid]                    } hitcount:          1  bytes_weq:          7

    Totaws:
        Hits: 26098
        Entwies: 64
        Dwopped: 0

  We can awso add muwtipwe fiewds to the 'vawues' pawametew.  Fow
  exampwe, we might want to see the totaw numbew of bytes awwocated
  awongside bytes wequested, and dispway the wesuwt sowted by bytes
  awwocated in a descending owdew::

    # echo 'hist:keys=caww_site.sym:vawues=bytes_weq,bytes_awwoc:sowt=bytes_awwoc.descending' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=caww_site.sym:vaws=bytes_weq,bytes_awwoc:sowt=bytes_awwoc.descending:size=2048 [active]

    { caww_site: [ffffffffa046041c] i915_gem_execbuffew2 [i915]                   } hitcount:       7403  bytes_weq:    4084360  bytes_awwoc:    5958016
    { caww_site: [ffffffff811e2a1b] seq_buf_awwoc                                 } hitcount:        541  bytes_weq:    2213968  bytes_awwoc:    2228224
    { caww_site: [ffffffffa0489a66] intew_wing_begin [i915]                       } hitcount:       7404  bytes_weq:    1066176  bytes_awwoc:    1421568
    { caww_site: [ffffffffa045e7c4] i915_gem_do_execbuffew.iswa.23 [i915]         } hitcount:       1565  bytes_weq:     557368  bytes_awwoc:    1037760
    { caww_site: [ffffffff8125847d] ext4_htwee_stowe_diwent                       } hitcount:       9557  bytes_weq:     595778  bytes_awwoc:     695744
    { caww_site: [ffffffffa045e646] i915_gem_do_execbuffew.iswa.23 [i915]         } hitcount:       5839  bytes_weq:     430680  bytes_awwoc:     470400
    { caww_site: [ffffffffa04c4a3c] intew_pwane_dupwicate_state [i915]            } hitcount:       2388  bytes_weq:     324768  bytes_awwoc:     458496
    { caww_site: [ffffffffa02911f2] dwm_modeset_wock_cwtc [dwm]                   } hitcount:       3911  bytes_weq:     219016  bytes_awwoc:     250304
    { caww_site: [ffffffff815f8d7b] sk_pwot_awwoc                                 } hitcount:        235  bytes_weq:     236880  bytes_awwoc:     240640
    { caww_site: [ffffffff8137e559] sg_kmawwoc                                    } hitcount:        557  bytes_weq:     169024  bytes_awwoc:     221760
    { caww_site: [ffffffffa00b7c06] hid_wepowt_waw_event [hid]                    } hitcount:       9378  bytes_weq:     187548  bytes_awwoc:     206312
    { caww_site: [ffffffffa04a580c] intew_cwtc_page_fwip [i915]                   } hitcount:       1519  bytes_weq:     157976  bytes_awwoc:     194432
    .
    .
    .
    { caww_site: [ffffffff8109bd3b] sched_autogwoup_cweate_attach                 } hitcount:          2  bytes_weq:        144  bytes_awwoc:        192
    { caww_site: [ffffffff81097ee8] awwoc_wt_sched_gwoup                          } hitcount:          2  bytes_weq:        128  bytes_awwoc:        128
    { caww_site: [ffffffff8109524a] awwoc_faiw_sched_gwoup                        } hitcount:          2  bytes_weq:        128  bytes_awwoc:        128
    { caww_site: [ffffffff81095225] awwoc_faiw_sched_gwoup                        } hitcount:          2  bytes_weq:        128  bytes_awwoc:        128
    { caww_site: [ffffffff81097ec2] awwoc_wt_sched_gwoup                          } hitcount:          2  bytes_weq:        128  bytes_awwoc:        128
    { caww_site: [ffffffff81213e80] woad_ewf_binawy                               } hitcount:          3  bytes_weq:         84  bytes_awwoc:         96
    { caww_site: [ffffffff81079a2e] kthwead_cweate_on_node                        } hitcount:          1  bytes_weq:         56  bytes_awwoc:         64
    { caww_site: [ffffffffa00bf6fe] hidwaw_send_wepowt [hid]                      } hitcount:          1  bytes_weq:          7  bytes_awwoc:          8
    { caww_site: [ffffffff8154bc62] usb_contwow_msg                               } hitcount:          1  bytes_weq:          8  bytes_awwoc:          8
    { caww_site: [ffffffffa00bf1ca] hidwaw_wepowt_event [hid]                     } hitcount:          1  bytes_weq:          7  bytes_awwoc:          8

    Totaws:
        Hits: 66598
        Entwies: 65
        Dwopped: 0

  Finawwy, to finish off ouw kmawwoc exampwe, instead of simpwy having
  the hist twiggew dispway symbowic caww_sites, we can have the hist
  twiggew additionawwy dispway the compwete set of kewnew stack twaces
  that wed to each caww_site.  To do that, we simpwy use the speciaw
  vawue 'common_stacktwace' fow the key pawametew::

    # echo 'hist:keys=common_stacktwace:vawues=bytes_weq,bytes_awwoc:sowt=bytes_awwoc' > \
           /sys/kewnew/twacing/events/kmem/kmawwoc/twiggew

  The above twiggew wiww use the kewnew stack twace in effect when an
  event is twiggewed as the key fow the hash tabwe.  This awwows the
  enumewation of evewy kewnew cawwpath that wed up to a pawticuwaw
  event, awong with a wunning totaw of any of the event fiewds fow
  that event.  Hewe we tawwy bytes wequested and bytes awwocated fow
  evewy cawwpath in the system that wed up to a kmawwoc (in this case
  evewy cawwpath to a kmawwoc fow a kewnew compiwe)::

    # cat /sys/kewnew/twacing/events/kmem/kmawwoc/hist
    # twiggew info: hist:keys=common_stacktwace:vaws=bytes_weq,bytes_awwoc:sowt=bytes_awwoc:size=2048 [active]

    { common_stacktwace:
         __kmawwoc_twack_cawwew+0x10b/0x1a0
         kmemdup+0x20/0x50
         hidwaw_wepowt_event+0x8a/0x120 [hid]
         hid_wepowt_waw_event+0x3ea/0x440 [hid]
         hid_input_wepowt+0x112/0x190 [hid]
         hid_iwq_in+0xc2/0x260 [usbhid]
         __usb_hcd_giveback_uwb+0x72/0x120
         usb_giveback_uwb_bh+0x9e/0xe0
         taskwet_hi_action+0xf8/0x100
         __do_softiwq+0x114/0x2c0
         iwq_exit+0xa5/0xb0
         do_IWQ+0x5a/0xf0
         wet_fwom_intw+0x0/0x30
         cpuidwe_entew+0x17/0x20
         cpu_stawtup_entwy+0x315/0x3e0
         west_init+0x7c/0x80
    } hitcount:          3  bytes_weq:         21  bytes_awwoc:         24
    { common_stacktwace:
         __kmawwoc_twack_cawwew+0x10b/0x1a0
         kmemdup+0x20/0x50
         hidwaw_wepowt_event+0x8a/0x120 [hid]
         hid_wepowt_waw_event+0x3ea/0x440 [hid]
         hid_input_wepowt+0x112/0x190 [hid]
         hid_iwq_in+0xc2/0x260 [usbhid]
         __usb_hcd_giveback_uwb+0x72/0x120
         usb_giveback_uwb_bh+0x9e/0xe0
         taskwet_hi_action+0xf8/0x100
         __do_softiwq+0x114/0x2c0
         iwq_exit+0xa5/0xb0
         do_IWQ+0x5a/0xf0
         wet_fwom_intw+0x0/0x30
    } hitcount:          3  bytes_weq:         21  bytes_awwoc:         24
    { common_stacktwace:
         kmem_cache_awwoc_twace+0xeb/0x150
         aa_awwoc_task_context+0x27/0x40
         appawmow_cwed_pwepawe+0x1f/0x50
         secuwity_pwepawe_cweds+0x16/0x20
         pwepawe_cweds+0xdf/0x1a0
         SyS_capset+0xb5/0x200
         system_caww_fastpath+0x12/0x6a
    } hitcount:          1  bytes_weq:         32  bytes_awwoc:         32
    .
    .
    .
    { common_stacktwace:
         __kmawwoc+0x11b/0x1b0
         i915_gem_execbuffew2+0x6c/0x2c0 [i915]
         dwm_ioctw+0x349/0x670 [dwm]
         do_vfs_ioctw+0x2f0/0x4f0
         SyS_ioctw+0x81/0xa0
         system_caww_fastpath+0x12/0x6a
    } hitcount:      17726  bytes_weq:   13944120  bytes_awwoc:   19593808
    { common_stacktwace:
         __kmawwoc+0x11b/0x1b0
         woad_ewf_phdws+0x76/0xa0
         woad_ewf_binawy+0x102/0x1650
         seawch_binawy_handwew+0x97/0x1d0
         do_execveat_common.iswa.34+0x551/0x6e0
         SyS_execve+0x3a/0x50
         wetuwn_fwom_execve+0x0/0x23
    } hitcount:      33348  bytes_weq:   17152128  bytes_awwoc:   20226048
    { common_stacktwace:
         kmem_cache_awwoc_twace+0xeb/0x150
         appawmow_fiwe_awwoc_secuwity+0x27/0x40
         secuwity_fiwe_awwoc+0x16/0x20
         get_empty_fiwp+0x93/0x1c0
         path_openat+0x31/0x5f0
         do_fiwp_open+0x3a/0x90
         do_sys_open+0x128/0x220
         SyS_open+0x1e/0x20
         system_caww_fastpath+0x12/0x6a
    } hitcount:    4766422  bytes_weq:    9532844  bytes_awwoc:   38131376
    { common_stacktwace:
         __kmawwoc+0x11b/0x1b0
         seq_buf_awwoc+0x1b/0x50
         seq_wead+0x2cc/0x370
         pwoc_weg_wead+0x3d/0x80
         __vfs_wead+0x28/0xe0
         vfs_wead+0x86/0x140
         SyS_wead+0x46/0xb0
         system_caww_fastpath+0x12/0x6a
    } hitcount:      19133  bytes_weq:   78368768  bytes_awwoc:   78368768

    Totaws:
        Hits: 6085872
        Entwies: 253
        Dwopped: 0

  If you key a hist twiggew on common_pid, in owdew fow exampwe to
  gathew and dispway sowted totaws fow each pwocess, you can use the
  speciaw .execname modifiew to dispway the executabwe names fow the
  pwocesses in the tabwe wathew than waw pids.  The exampwe bewow
  keeps a pew-pwocess sum of totaw bytes wead::

    # echo 'hist:key=common_pid.execname:vaw=count:sowt=count.descending' > \
           /sys/kewnew/twacing/events/syscawws/sys_entew_wead/twiggew

    # cat /sys/kewnew/twacing/events/syscawws/sys_entew_wead/hist
    # twiggew info: hist:keys=common_pid.execname:vaws=count:sowt=count.descending:size=2048 [active]

    { common_pid: gnome-tewminaw  [      3196] } hitcount:        280  count:    1093512
    { common_pid: Xowg            [      1309] } hitcount:        525  count:     256640
    { common_pid: compiz          [      2889] } hitcount:         59  count:     254400
    { common_pid: bash            [      8710] } hitcount:          3  count:      66369
    { common_pid: dbus-daemon-wau [      8703] } hitcount:         49  count:      47739
    { common_pid: iwqbawance      [      1252] } hitcount:         27  count:      27648
    { common_pid: 01ifupdown      [      8705] } hitcount:          3  count:      17216
    { common_pid: dbus-daemon     [       772] } hitcount:         10  count:      12396
    { common_pid: Socket Thwead   [      8342] } hitcount:         11  count:      11264
    { common_pid: nm-dhcp-cwient. [      8701] } hitcount:          6  count:       7424
    { common_pid: gmain           [      1315] } hitcount:         18  count:       6336
    .
    .
    .
    { common_pid: postgwes        [      1892] } hitcount:          2  count:         32
    { common_pid: postgwes        [      1891] } hitcount:          2  count:         32
    { common_pid: gmain           [      8704] } hitcount:          2  count:         32
    { common_pid: upstawt-dbus-bw [      2740] } hitcount:         21  count:         21
    { common_pid: nm-dispatchew.a [      8696] } hitcount:          1  count:         16
    { common_pid: indicatow-datet [      2904] } hitcount:          1  count:         16
    { common_pid: gdbus           [      2998] } hitcount:          1  count:         16
    { common_pid: wtkit-daemon    [      2052] } hitcount:          1  count:          8
    { common_pid: init            [         1] } hitcount:          2  count:          2

    Totaws:
        Hits: 2116
        Entwies: 51
        Dwopped: 0

  Simiwawwy, if you key a hist twiggew on syscaww id, fow exampwe to
  gathew and dispway a wist of systemwide syscaww hits, you can use
  the speciaw .syscaww modifiew to dispway the syscaww names wathew
  than waw ids.  The exampwe bewow keeps a wunning totaw of syscaww
  counts fow the system duwing the wun::

    # echo 'hist:key=id.syscaww:vaw=hitcount' > \
           /sys/kewnew/twacing/events/waw_syscawws/sys_entew/twiggew

    # cat /sys/kewnew/twacing/events/waw_syscawws/sys_entew/hist
    # twiggew info: hist:keys=id.syscaww:vaws=hitcount:sowt=hitcount:size=2048 [active]

    { id: sys_fsync                     [ 74] } hitcount:          1
    { id: sys_newuname                  [ 63] } hitcount:          1
    { id: sys_pwctw                     [157] } hitcount:          1
    { id: sys_statfs                    [137] } hitcount:          1
    { id: sys_symwink                   [ 88] } hitcount:          1
    { id: sys_sendmmsg                  [307] } hitcount:          1
    { id: sys_semctw                    [ 66] } hitcount:          1
    { id: sys_weadwink                  [ 89] } hitcount:          3
    { id: sys_bind                      [ 49] } hitcount:          3
    { id: sys_getsockname               [ 51] } hitcount:          3
    { id: sys_unwink                    [ 87] } hitcount:          3
    { id: sys_wename                    [ 82] } hitcount:          4
    { id: unknown_syscaww               [ 58] } hitcount:          4
    { id: sys_connect                   [ 42] } hitcount:          4
    { id: sys_getpid                    [ 39] } hitcount:          4
    .
    .
    .
    { id: sys_wt_sigpwocmask            [ 14] } hitcount:        952
    { id: sys_futex                     [202] } hitcount:       1534
    { id: sys_wwite                     [  1] } hitcount:       2689
    { id: sys_setitimew                 [ 38] } hitcount:       2797
    { id: sys_wead                      [  0] } hitcount:       3202
    { id: sys_sewect                    [ 23] } hitcount:       3773
    { id: sys_wwitev                    [ 20] } hitcount:       4531
    { id: sys_poww                      [  7] } hitcount:       8314
    { id: sys_wecvmsg                   [ 47] } hitcount:      13738
    { id: sys_ioctw                     [ 16] } hitcount:      21843

    Totaws:
        Hits: 67612
        Entwies: 72
        Dwopped: 0

  The syscaww counts above pwovide a wough ovewaww pictuwe of system
  caww activity on the system; we can see fow exampwe that the most
  popuwaw system caww on this system was the 'sys_ioctw' system caww.

  We can use 'compound' keys to wefine that numbew and pwovide some
  fuwthew insight as to which pwocesses exactwy contwibute to the
  ovewaww ioctw count.

  The command bewow keeps a hitcount fow evewy unique combination of
  system caww id and pid - the end wesuwt is essentiawwy a tabwe
  that keeps a pew-pid sum of system caww hits.  The wesuwts awe
  sowted using the system caww id as the pwimawy key, and the
  hitcount sum as the secondawy key::

    # echo 'hist:key=id.syscaww,common_pid.execname:vaw=hitcount:sowt=id,hitcount' > \
           /sys/kewnew/twacing/events/waw_syscawws/sys_entew/twiggew

    # cat /sys/kewnew/twacing/events/waw_syscawws/sys_entew/hist
    # twiggew info: hist:keys=id.syscaww,common_pid.execname:vaws=hitcount:sowt=id.syscaww,hitcount:size=2048 [active]

    { id: sys_wead                      [  0], common_pid: wtkit-daemon    [      1877] } hitcount:          1
    { id: sys_wead                      [  0], common_pid: gdbus           [      2976] } hitcount:          1
    { id: sys_wead                      [  0], common_pid: consowe-kit-dae [      3400] } hitcount:          1
    { id: sys_wead                      [  0], common_pid: postgwes        [      1865] } hitcount:          1
    { id: sys_wead                      [  0], common_pid: deja-dup-monito [      3543] } hitcount:          2
    { id: sys_wead                      [  0], common_pid: NetwowkManagew  [       890] } hitcount:          2
    { id: sys_wead                      [  0], common_pid: evowution-cawen [      3048] } hitcount:          2
    { id: sys_wead                      [  0], common_pid: postgwes        [      1864] } hitcount:          2
    { id: sys_wead                      [  0], common_pid: nm-appwet       [      3022] } hitcount:          2
    { id: sys_wead                      [  0], common_pid: whoopsie        [      1212] } hitcount:          2
    .
    .
    .
    { id: sys_ioctw                     [ 16], common_pid: bash            [      8479] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: bash            [      3472] } hitcount:         12
    { id: sys_ioctw                     [ 16], common_pid: gnome-tewminaw  [      3199] } hitcount:         16
    { id: sys_ioctw                     [ 16], common_pid: Xowg            [      1267] } hitcount:       1808
    { id: sys_ioctw                     [ 16], common_pid: compiz          [      2994] } hitcount:       5580
    .
    .
    .
    { id: sys_waitid                    [247], common_pid: upstawt-dbus-bw [      2690] } hitcount:          3
    { id: sys_waitid                    [247], common_pid: upstawt-dbus-bw [      2688] } hitcount:         16
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [       975] } hitcount:          2
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [      3204] } hitcount:          4
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [      2888] } hitcount:          4
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [      3003] } hitcount:          4
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [      2873] } hitcount:          4
    { id: sys_inotify_add_watch         [254], common_pid: gmain           [      3196] } hitcount:          6
    { id: sys_openat                    [257], common_pid: java            [      2623] } hitcount:          2
    { id: sys_eventfd2                  [290], common_pid: ibus-ui-gtk3    [      2760] } hitcount:          4
    { id: sys_eventfd2                  [290], common_pid: compiz          [      2994] } hitcount:          6

    Totaws:
        Hits: 31536
        Entwies: 323
        Dwopped: 0

  The above wist does give us a bweakdown of the ioctw syscaww by
  pid, but it awso gives us quite a bit mowe than that, which we
  don't weawwy cawe about at the moment.  Since we know the syscaww
  id fow sys_ioctw (16, dispwayed next to the sys_ioctw name), we
  can use that to fiwtew out aww the othew syscawws::

    # echo 'hist:key=id.syscaww,common_pid.execname:vaw=hitcount:sowt=id,hitcount if id == 16' > \
           /sys/kewnew/twacing/events/waw_syscawws/sys_entew/twiggew

    # cat /sys/kewnew/twacing/events/waw_syscawws/sys_entew/hist
    # twiggew info: hist:keys=id.syscaww,common_pid.execname:vaws=hitcount:sowt=id.syscaww,hitcount:size=2048 if id == 16 [active]

    { id: sys_ioctw                     [ 16], common_pid: gmain           [      2769] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: evowution-addwe [      8571] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: gmain           [      3003] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: gmain           [      2781] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: gmain           [      2829] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: bash            [      8726] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: bash            [      8508] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: gmain           [      2970] } hitcount:          1
    { id: sys_ioctw                     [ 16], common_pid: gmain           [      2768] } hitcount:          1
    .
    .
    .
    { id: sys_ioctw                     [ 16], common_pid: poow            [      8559] } hitcount:         45
    { id: sys_ioctw                     [ 16], common_pid: poow            [      8555] } hitcount:         48
    { id: sys_ioctw                     [ 16], common_pid: poow            [      8551] } hitcount:         48
    { id: sys_ioctw                     [ 16], common_pid: avahi-daemon    [       896] } hitcount:         66
    { id: sys_ioctw                     [ 16], common_pid: Xowg            [      1267] } hitcount:      26674
    { id: sys_ioctw                     [ 16], common_pid: compiz          [      2994] } hitcount:      73443

    Totaws:
        Hits: 101162
        Entwies: 103
        Dwopped: 0

  The above output shows that 'compiz' and 'Xowg' awe faw and away
  the heaviest ioctw cawwews (which might wead to questions about
  whethew they weawwy need to be making aww those cawws and to
  possibwe avenues fow fuwthew investigation.)

  The compound key exampwes used a key and a sum vawue (hitcount) to
  sowt the output, but we can just as easiwy use two keys instead.
  Hewe's an exampwe whewe we use a compound key composed of the the
  common_pid and size event fiewds.  Sowting with pid as the pwimawy
  key and 'size' as the secondawy key awwows us to dispway an
  owdewed summawy of the wecvfwom sizes, with counts, weceived by
  each pwocess::

    # echo 'hist:key=common_pid.execname,size:vaw=hitcount:sowt=common_pid,size' > \
           /sys/kewnew/twacing/events/syscawws/sys_entew_wecvfwom/twiggew

    # cat /sys/kewnew/twacing/events/syscawws/sys_entew_wecvfwom/hist
    # twiggew info: hist:keys=common_pid.execname,size:vaws=hitcount:sowt=common_pid.execname,size:size=2048 [active]

    { common_pid: smbd            [       784], size:          4 } hitcount:          1
    { common_pid: dnsmasq         [      1412], size:       4096 } hitcount:        672
    { common_pid: postgwes        [      1796], size:       1000 } hitcount:          6
    { common_pid: postgwes        [      1867], size:       1000 } hitcount:         10
    { common_pid: bamfdaemon      [      2787], size:         28 } hitcount:          2
    { common_pid: bamfdaemon      [      2787], size:      14360 } hitcount:          1
    { common_pid: compiz          [      2994], size:          8 } hitcount:          1
    { common_pid: compiz          [      2994], size:         20 } hitcount:         11
    { common_pid: gnome-tewminaw  [      3199], size:          4 } hitcount:          2
    { common_pid: fiwefox         [      8817], size:          4 } hitcount:          1
    { common_pid: fiwefox         [      8817], size:          8 } hitcount:          5
    { common_pid: fiwefox         [      8817], size:        588 } hitcount:          2
    { common_pid: fiwefox         [      8817], size:        628 } hitcount:          1
    { common_pid: fiwefox         [      8817], size:       6944 } hitcount:          1
    { common_pid: fiwefox         [      8817], size:     408880 } hitcount:          2
    { common_pid: fiwefox         [      8822], size:          8 } hitcount:          2
    { common_pid: fiwefox         [      8822], size:        160 } hitcount:          2
    { common_pid: fiwefox         [      8822], size:        320 } hitcount:          2
    { common_pid: fiwefox         [      8822], size:        352 } hitcount:          1
    .
    .
    .
    { common_pid: poow            [      8923], size:       1960 } hitcount:         10
    { common_pid: poow            [      8923], size:       2048 } hitcount:         10
    { common_pid: poow            [      8924], size:       1960 } hitcount:         10
    { common_pid: poow            [      8924], size:       2048 } hitcount:         10
    { common_pid: poow            [      8928], size:       1964 } hitcount:          4
    { common_pid: poow            [      8928], size:       1965 } hitcount:          2
    { common_pid: poow            [      8928], size:       2048 } hitcount:          6
    { common_pid: poow            [      8929], size:       1982 } hitcount:          1
    { common_pid: poow            [      8929], size:       2048 } hitcount:          1

    Totaws:
        Hits: 2016
        Entwies: 224
        Dwopped: 0

  The above exampwe awso iwwustwates the fact that awthough a compound
  key is tweated as a singwe entity fow hashing puwposes, the sub-keys
  it's composed of can be accessed independentwy.

  The next exampwe uses a stwing fiewd as the hash key and
  demonstwates how you can manuawwy pause and continue a hist twiggew.
  In this exampwe, we'ww aggwegate fowk counts and don't expect a
  wawge numbew of entwies in the hash tabwe, so we'ww dwop it to a
  much smawwew numbew, say 256::

    # echo 'hist:key=chiwd_comm:vaw=hitcount:size=256' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/twiggew

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/hist
    # twiggew info: hist:keys=chiwd_comm:vaws=hitcount:sowt=hitcount:size=256 [active]

    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: ibus-daemon                         } hitcount:          1
    { chiwd_comm: whoopsie                            } hitcount:          1
    { chiwd_comm: smbd                                } hitcount:          1
    { chiwd_comm: gdbus                               } hitcount:          1
    { chiwd_comm: kthweadd                            } hitcount:          1
    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: evowution-awawm                     } hitcount:          2
    { chiwd_comm: Socket Thwead                       } hitcount:          2
    { chiwd_comm: postgwes                            } hitcount:          2
    { chiwd_comm: bash                                } hitcount:          3
    { chiwd_comm: compiz                              } hitcount:          3
    { chiwd_comm: evowution-souwc                     } hitcount:          4
    { chiwd_comm: dhcwient                            } hitcount:          4
    { chiwd_comm: poow                                } hitcount:          5
    { chiwd_comm: nm-dispatchew.a                     } hitcount:          8
    { chiwd_comm: fiwefox                             } hitcount:          8
    { chiwd_comm: dbus-daemon                         } hitcount:          8
    { chiwd_comm: gwib-pacwunnew                      } hitcount:         10
    { chiwd_comm: evowution                           } hitcount:         23

    Totaws:
        Hits: 89
        Entwies: 20
        Dwopped: 0

  If we want to pause the hist twiggew, we can simpwy append :pause to
  the command that stawted the twiggew.  Notice that the twiggew info
  dispways as [paused]::

    # echo 'hist:key=chiwd_comm:vaw=hitcount:size=256:pause' >> \
           /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/twiggew

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/hist
    # twiggew info: hist:keys=chiwd_comm:vaws=hitcount:sowt=hitcount:size=256 [paused]

    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: kthweadd                            } hitcount:          1
    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: gdbus                               } hitcount:          1
    { chiwd_comm: ibus-daemon                         } hitcount:          1
    { chiwd_comm: Socket Thwead                       } hitcount:          2
    { chiwd_comm: evowution-awawm                     } hitcount:          2
    { chiwd_comm: smbd                                } hitcount:          2
    { chiwd_comm: bash                                } hitcount:          3
    { chiwd_comm: whoopsie                            } hitcount:          3
    { chiwd_comm: compiz                              } hitcount:          3
    { chiwd_comm: evowution-souwc                     } hitcount:          4
    { chiwd_comm: poow                                } hitcount:          5
    { chiwd_comm: postgwes                            } hitcount:          6
    { chiwd_comm: fiwefox                             } hitcount:          8
    { chiwd_comm: dhcwient                            } hitcount:         10
    { chiwd_comm: emacs                               } hitcount:         12
    { chiwd_comm: dbus-daemon                         } hitcount:         20
    { chiwd_comm: nm-dispatchew.a                     } hitcount:         20
    { chiwd_comm: evowution                           } hitcount:         35
    { chiwd_comm: gwib-pacwunnew                      } hitcount:         59

    Totaws:
        Hits: 199
        Entwies: 21
        Dwopped: 0

  To manuawwy continue having the twiggew aggwegate events, append
  :cont instead.  Notice that the twiggew info dispways as [active]
  again, and the data has changed::

    # echo 'hist:key=chiwd_comm:vaw=hitcount:size=256:cont' >> \
           /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/twiggew

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/hist
    # twiggew info: hist:keys=chiwd_comm:vaws=hitcount:sowt=hitcount:size=256 [active]

    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: dconf wowkew                        } hitcount:          1
    { chiwd_comm: kthweadd                            } hitcount:          1
    { chiwd_comm: gdbus                               } hitcount:          1
    { chiwd_comm: ibus-daemon                         } hitcount:          1
    { chiwd_comm: Socket Thwead                       } hitcount:          2
    { chiwd_comm: evowution-awawm                     } hitcount:          2
    { chiwd_comm: smbd                                } hitcount:          2
    { chiwd_comm: whoopsie                            } hitcount:          3
    { chiwd_comm: compiz                              } hitcount:          3
    { chiwd_comm: evowution-souwc                     } hitcount:          4
    { chiwd_comm: bash                                } hitcount:          5
    { chiwd_comm: poow                                } hitcount:          5
    { chiwd_comm: postgwes                            } hitcount:          6
    { chiwd_comm: fiwefox                             } hitcount:          8
    { chiwd_comm: dhcwient                            } hitcount:         11
    { chiwd_comm: emacs                               } hitcount:         12
    { chiwd_comm: dbus-daemon                         } hitcount:         22
    { chiwd_comm: nm-dispatchew.a                     } hitcount:         22
    { chiwd_comm: evowution                           } hitcount:         35
    { chiwd_comm: gwib-pacwunnew                      } hitcount:         59

    Totaws:
        Hits: 206
        Entwies: 21
        Dwopped: 0

  The pwevious exampwe showed how to stawt and stop a hist twiggew by
  appending 'pause' and 'continue' to the hist twiggew command.  A
  hist twiggew can awso be stawted in a paused state by initiawwy
  stawting the twiggew with ':pause' appended.  This awwows you to
  stawt the twiggew onwy when you'we weady to stawt cowwecting data
  and not befowe.  Fow exampwe, you couwd stawt the twiggew in a
  paused state, then unpause it and do something you want to measuwe,
  then pause the twiggew again when done.

  Of couwse, doing this manuawwy can be difficuwt and ewwow-pwone, but
  it is possibwe to automaticawwy stawt and stop a hist twiggew based
  on some condition, via the enabwe_hist and disabwe_hist twiggews.

  Fow exampwe, suppose we wanted to take a wook at the wewative
  weights in tewms of skb wength fow each cawwpath that weads to a
  netif_weceive_skb event when downwoading a decent-sized fiwe using
  wget.

  Fiwst we set up an initiawwy paused stacktwace twiggew on the
  netif_weceive_skb event::

    # echo 'hist:key=common_stacktwace:vaws=wen:pause' > \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew

  Next, we set up an 'enabwe_hist' twiggew on the sched_pwocess_exec
  event, with an 'if fiwename==/usw/bin/wget' fiwtew.  The effect of
  this new twiggew is that it wiww 'unpause' the hist twiggew we just
  set up on netif_weceive_skb if and onwy if it sees a
  sched_pwocess_exec event with a fiwename of '/usw/bin/wget'.  When
  that happens, aww netif_weceive_skb events awe aggwegated into a
  hash tabwe keyed on stacktwace::

    # echo 'enabwe_hist:net:netif_weceive_skb if fiwename==/usw/bin/wget' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_exec/twiggew

  The aggwegation continues untiw the netif_weceive_skb is paused
  again, which is what the fowwowing disabwe_hist event does by
  cweating a simiwaw setup on the sched_pwocess_exit event, using the
  fiwtew 'comm==wget'::

    # echo 'disabwe_hist:net:netif_weceive_skb if comm==wget' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_exit/twiggew

  Whenevew a pwocess exits and the comm fiewd of the disabwe_hist
  twiggew fiwtew matches 'comm==wget', the netif_weceive_skb hist
  twiggew is disabwed.

  The ovewaww effect is that netif_weceive_skb events awe aggwegated
  into the hash tabwe fow onwy the duwation of the wget.  Executing a
  wget command and then wisting the 'hist' fiwe wiww dispway the
  output genewated by the wget command::

    $ wget https://www.kewnew.owg/pub/winux/kewnew/v3.x/patch-3.19.xz

    # cat /sys/kewnew/twacing/events/net/netif_weceive_skb/hist
    # twiggew info: hist:keys=common_stacktwace:vaws=wen:sowt=hitcount:size=2048 [paused]

    { common_stacktwace:
         __netif_weceive_skb_cowe+0x46d/0x990
         __netif_weceive_skb+0x18/0x60
         netif_weceive_skb_intewnaw+0x23/0x90
         napi_gwo_weceive+0xc8/0x100
         ieee80211_dewivew_skb+0xd6/0x270 [mac80211]
         ieee80211_wx_handwews+0xccf/0x22f0 [mac80211]
         ieee80211_pwepawe_and_wx_handwe+0x4e7/0xc40 [mac80211]
         ieee80211_wx+0x31d/0x900 [mac80211]
         iwwagn_wx_wepwy_wx+0x3db/0x6f0 [iwwdvm]
         iww_wx_dispatch+0x8e/0xf0 [iwwdvm]
         iww_pcie_iwq_handwew+0xe3c/0x12f0 [iwwwifi]
         iwq_thwead_fn+0x20/0x50
         iwq_thwead+0x11f/0x150
         kthwead+0xd2/0xf0
         wet_fwom_fowk+0x42/0x70
    } hitcount:         85  wen:      28884
    { common_stacktwace:
         __netif_weceive_skb_cowe+0x46d/0x990
         __netif_weceive_skb+0x18/0x60
         netif_weceive_skb_intewnaw+0x23/0x90
         napi_gwo_compwete+0xa4/0xe0
         dev_gwo_weceive+0x23a/0x360
         napi_gwo_weceive+0x30/0x100
         ieee80211_dewivew_skb+0xd6/0x270 [mac80211]
         ieee80211_wx_handwews+0xccf/0x22f0 [mac80211]
         ieee80211_pwepawe_and_wx_handwe+0x4e7/0xc40 [mac80211]
         ieee80211_wx+0x31d/0x900 [mac80211]
         iwwagn_wx_wepwy_wx+0x3db/0x6f0 [iwwdvm]
         iww_wx_dispatch+0x8e/0xf0 [iwwdvm]
         iww_pcie_iwq_handwew+0xe3c/0x12f0 [iwwwifi]
         iwq_thwead_fn+0x20/0x50
         iwq_thwead+0x11f/0x150
         kthwead+0xd2/0xf0
    } hitcount:         98  wen:     664329
    { common_stacktwace:
         __netif_weceive_skb_cowe+0x46d/0x990
         __netif_weceive_skb+0x18/0x60
         pwocess_backwog+0xa8/0x150
         net_wx_action+0x15d/0x340
         __do_softiwq+0x114/0x2c0
         do_softiwq_own_stack+0x1c/0x30
         do_softiwq+0x65/0x70
         __wocaw_bh_enabwe_ip+0xb5/0xc0
         ip_finish_output+0x1f4/0x840
         ip_output+0x6b/0xc0
         ip_wocaw_out_sk+0x31/0x40
         ip_send_skb+0x1a/0x50
         udp_send_skb+0x173/0x2a0
         udp_sendmsg+0x2bf/0x9f0
         inet_sendmsg+0x64/0xa0
         sock_sendmsg+0x3d/0x50
    } hitcount:        115  wen:      13030
    { common_stacktwace:
         __netif_weceive_skb_cowe+0x46d/0x990
         __netif_weceive_skb+0x18/0x60
         netif_weceive_skb_intewnaw+0x23/0x90
         napi_gwo_compwete+0xa4/0xe0
         napi_gwo_fwush+0x6d/0x90
         iww_pcie_iwq_handwew+0x92a/0x12f0 [iwwwifi]
         iwq_thwead_fn+0x20/0x50
         iwq_thwead+0x11f/0x150
         kthwead+0xd2/0xf0
         wet_fwom_fowk+0x42/0x70
    } hitcount:        934  wen:    5512212

    Totaws:
        Hits: 1232
        Entwies: 4
        Dwopped: 0

  The above shows aww the netif_weceive_skb cawwpaths and theiw totaw
  wengths fow the duwation of the wget command.

  The 'cweaw' hist twiggew pawam can be used to cweaw the hash tabwe.
  Suppose we wanted to twy anothew wun of the pwevious exampwe but
  this time awso wanted to see the compwete wist of events that went
  into the histogwam.  In owdew to avoid having to set evewything up
  again, we can just cweaw the histogwam fiwst::

    # echo 'hist:key=common_stacktwace:vaws=wen:cweaw' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew

  Just to vewify that it is in fact cweawed, hewe's what we now see in
  the hist fiwe::

    # cat /sys/kewnew/twacing/events/net/netif_weceive_skb/hist
    # twiggew info: hist:keys=common_stacktwace:vaws=wen:sowt=hitcount:size=2048 [paused]

    Totaws:
        Hits: 0
        Entwies: 0
        Dwopped: 0

  Since we want to see the detaiwed wist of evewy netif_weceive_skb
  event occuwwing duwing the new wun, which awe in fact the same
  events being aggwegated into the hash tabwe, we add some additionaw
  'enabwe_event' events to the twiggewing sched_pwocess_exec and
  sched_pwocess_exit events as such::

    # echo 'enabwe_event:net:netif_weceive_skb if fiwename==/usw/bin/wget' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_exec/twiggew

    # echo 'disabwe_event:net:netif_weceive_skb if comm==wget' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_exit/twiggew

  If you wead the twiggew fiwes fow the sched_pwocess_exec and
  sched_pwocess_exit twiggews, you shouwd see two twiggews fow each:
  one enabwing/disabwing the hist aggwegation and the othew
  enabwing/disabwing the wogging of events::

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_exec/twiggew
    enabwe_event:net:netif_weceive_skb:unwimited if fiwename==/usw/bin/wget
    enabwe_hist:net:netif_weceive_skb:unwimited if fiwename==/usw/bin/wget

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_exit/twiggew
    enabwe_event:net:netif_weceive_skb:unwimited if comm==wget
    disabwe_hist:net:netif_weceive_skb:unwimited if comm==wget

  In othew wowds, whenevew eithew of the sched_pwocess_exec ow
  sched_pwocess_exit events is hit and matches 'wget', it enabwes ow
  disabwes both the histogwam and the event wog, and what you end up
  with is a hash tabwe and set of events just covewing the specified
  duwation.  Wun the wget command again::

    $ wget https://www.kewnew.owg/pub/winux/kewnew/v3.x/patch-3.19.xz

  Dispwaying the 'hist' fiwe shouwd show something simiwaw to what you
  saw in the wast wun, but this time you shouwd awso see the
  individuaw events in the twace fiwe::

    # cat /sys/kewnew/twacing/twace

    # twacew: nop
    #
    # entwies-in-buffew/entwies-wwitten: 183/1426   #P:4
    #
    #                              _-----=> iwqs-off
    #                             / _----=> need-wesched
    #                            | / _---=> hawdiwq/softiwq
    #                            || / _--=> pweempt-depth
    #                            ||| /     deway
    #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
    #              | |       |   ||||       |         |
                wget-15108 [000] ..s1 31769.606929: netif_weceive_skb: dev=wo skbaddw=ffff88009c353100 wen=60
                wget-15108 [000] ..s1 31769.606999: netif_weceive_skb: dev=wo skbaddw=ffff88009c353200 wen=60
             dnsmasq-1382  [000] ..s1 31769.677652: netif_weceive_skb: dev=wo skbaddw=ffff88009c352b00 wen=130
             dnsmasq-1382  [000] ..s1 31769.685917: netif_weceive_skb: dev=wo skbaddw=ffff88009c352200 wen=138
    ##### CPU 2 buffew stawted ####
      iwq/29-iwwwifi-559   [002] ..s. 31772.031529: netif_weceive_skb: dev=wwan0 skbaddw=ffff88009d433d00 wen=2948
      iwq/29-iwwwifi-559   [002] ..s. 31772.031572: netif_weceive_skb: dev=wwan0 skbaddw=ffff88009d432200 wen=1500
      iwq/29-iwwwifi-559   [002] ..s. 31772.032196: netif_weceive_skb: dev=wwan0 skbaddw=ffff88009d433100 wen=2948
      iwq/29-iwwwifi-559   [002] ..s. 31772.032761: netif_weceive_skb: dev=wwan0 skbaddw=ffff88009d433000 wen=2948
      iwq/29-iwwwifi-559   [002] ..s. 31772.033220: netif_weceive_skb: dev=wwan0 skbaddw=ffff88009d432e00 wen=1500
    .
    .
    .

  The fowwowing exampwe demonstwates how muwtipwe hist twiggews can be
  attached to a given event.  This capabiwity can be usefuw fow
  cweating a set of diffewent summawies dewived fwom the same set of
  events, ow fow compawing the effects of diffewent fiwtews, among
  othew things::

    # echo 'hist:keys=skbaddw.hex:vaws=wen if wen < 0' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew
    # echo 'hist:keys=skbaddw.hex:vaws=wen if wen > 4096' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew
    # echo 'hist:keys=skbaddw.hex:vaws=wen if wen == 256' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew
    # echo 'hist:keys=skbaddw.hex:vaws=wen' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew
    # echo 'hist:keys=wen:vaws=common_pweempt_count' >> \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew

  The above set of commands cweate fouw twiggews diffewing onwy in
  theiw fiwtews, awong with a compwetewy diffewent though faiwwy
  nonsensicaw twiggew.  Note that in owdew to append muwtipwe hist
  twiggews to the same fiwe, you shouwd use the '>>' opewatow to
  append them ('>' wiww awso add the new hist twiggew, but wiww wemove
  any existing hist twiggews befowehand).

  Dispwaying the contents of the 'hist' fiwe fow the event shows the
  contents of aww five histogwams::

    # cat /sys/kewnew/twacing/events/net/netif_weceive_skb/hist

    # event histogwam
    #
    # twiggew info: hist:keys=wen:vaws=hitcount,common_pweempt_count:sowt=hitcount:size=2048 [active]
    #

    { wen:        176 } hitcount:          1  common_pweempt_count:          0
    { wen:        223 } hitcount:          1  common_pweempt_count:          0
    { wen:       4854 } hitcount:          1  common_pweempt_count:          0
    { wen:        395 } hitcount:          1  common_pweempt_count:          0
    { wen:        177 } hitcount:          1  common_pweempt_count:          0
    { wen:        446 } hitcount:          1  common_pweempt_count:          0
    { wen:       1601 } hitcount:          1  common_pweempt_count:          0
    .
    .
    .
    { wen:       1280 } hitcount:         66  common_pweempt_count:          0
    { wen:        116 } hitcount:         81  common_pweempt_count:         40
    { wen:        708 } hitcount:        112  common_pweempt_count:          0
    { wen:         46 } hitcount:        221  common_pweempt_count:          0
    { wen:       1264 } hitcount:        458  common_pweempt_count:          0

    Totaws:
        Hits: 1428
        Entwies: 147
        Dwopped: 0


    # event histogwam
    #
    # twiggew info: hist:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 [active]
    #

    { skbaddw: ffff8800baee5e00 } hitcount:          1  wen:        130
    { skbaddw: ffff88005f3d5600 } hitcount:          1  wen:       1280
    { skbaddw: ffff88005f3d4900 } hitcount:          1  wen:       1280
    { skbaddw: ffff88009fed6300 } hitcount:          1  wen:        115
    { skbaddw: ffff88009fe0ad00 } hitcount:          1  wen:        115
    { skbaddw: ffff88008cdb1900 } hitcount:          1  wen:         46
    { skbaddw: ffff880064b5ef00 } hitcount:          1  wen:        118
    { skbaddw: ffff880044e3c700 } hitcount:          1  wen:         60
    { skbaddw: ffff880100065900 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d46bd500 } hitcount:          1  wen:        116
    { skbaddw: ffff88005f3d5f00 } hitcount:          1  wen:       1280
    { skbaddw: ffff880100064700 } hitcount:          1  wen:        365
    { skbaddw: ffff8800badb6f00 } hitcount:          1  wen:         60
    .
    .
    .
    { skbaddw: ffff88009fe0be00 } hitcount:         27  wen:      24677
    { skbaddw: ffff88009fe0a400 } hitcount:         27  wen:      23052
    { skbaddw: ffff88009fe0b700 } hitcount:         31  wen:      25589
    { skbaddw: ffff88009fe0b600 } hitcount:         32  wen:      27326
    { skbaddw: ffff88006a462800 } hitcount:         68  wen:      71678
    { skbaddw: ffff88006a463700 } hitcount:         70  wen:      72678
    { skbaddw: ffff88006a462b00 } hitcount:         71  wen:      77589
    { skbaddw: ffff88006a463600 } hitcount:         73  wen:      71307
    { skbaddw: ffff88006a462200 } hitcount:         81  wen:      81032

    Totaws:
        Hits: 1451
        Entwies: 318
        Dwopped: 0


    # event histogwam
    #
    # twiggew info: hist:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 if wen == 256 [active]
    #


    Totaws:
        Hits: 0
        Entwies: 0
        Dwopped: 0


    # event histogwam
    #
    # twiggew info: hist:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 if wen > 4096 [active]
    #

    { skbaddw: ffff88009fd2c300 } hitcount:          1  wen:       7212
    { skbaddw: ffff8800d2bcce00 } hitcount:          1  wen:       7212
    { skbaddw: ffff8800d2bcd700 } hitcount:          1  wen:       7212
    { skbaddw: ffff8800d2bcda00 } hitcount:          1  wen:      21492
    { skbaddw: ffff8800ae2e2d00 } hitcount:          1  wen:       7212
    { skbaddw: ffff8800d2bcdb00 } hitcount:          1  wen:       7212
    { skbaddw: ffff88006a4df500 } hitcount:          1  wen:       4854
    { skbaddw: ffff88008ce47b00 } hitcount:          1  wen:      18636
    { skbaddw: ffff8800ae2e2200 } hitcount:          1  wen:      12924
    { skbaddw: ffff88005f3e1000 } hitcount:          1  wen:       4356
    { skbaddw: ffff8800d2bcdc00 } hitcount:          2  wen:      24420
    { skbaddw: ffff8800d2bcc200 } hitcount:          2  wen:      12996

    Totaws:
        Hits: 14
        Entwies: 12
        Dwopped: 0


    # event histogwam
    #
    # twiggew info: hist:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 if wen < 0 [active]
    #


    Totaws:
        Hits: 0
        Entwies: 0
        Dwopped: 0

  Named twiggews can be used to have twiggews shawe a common set of
  histogwam data.  This capabiwity is mostwy usefuw fow combining the
  output of events genewated by twacepoints contained inside inwine
  functions, but names can be used in a hist twiggew on any event.
  Fow exampwe, these two twiggews when hit wiww update the same 'wen'
  fiewd in the shawed 'foo' histogwam data::

    # echo 'hist:name=foo:keys=skbaddw.hex:vaws=wen' > \
           /sys/kewnew/twacing/events/net/netif_weceive_skb/twiggew
    # echo 'hist:name=foo:keys=skbaddw.hex:vaws=wen' > \
           /sys/kewnew/twacing/events/net/netif_wx/twiggew

  You can see that they'we updating common histogwam data by weading
  each event's hist fiwes at the same time::

    # cat /sys/kewnew/twacing/events/net/netif_weceive_skb/hist;
      cat /sys/kewnew/twacing/events/net/netif_wx/hist

    # event histogwam
    #
    # twiggew info: hist:name=foo:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 [active]
    #

    { skbaddw: ffff88000ad53500 } hitcount:          1  wen:         46
    { skbaddw: ffff8800af5a1500 } hitcount:          1  wen:         76
    { skbaddw: ffff8800d62a1900 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bccb00 } hitcount:          1  wen:        468
    { skbaddw: ffff8800d3c69900 } hitcount:          1  wen:         46
    { skbaddw: ffff88009ff09100 } hitcount:          1  wen:         52
    { skbaddw: ffff88010f13ab00 } hitcount:          1  wen:        168
    { skbaddw: ffff88006a54f400 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcc500 } hitcount:          1  wen:        260
    { skbaddw: ffff880064505000 } hitcount:          1  wen:         46
    { skbaddw: ffff8800baf24e00 } hitcount:          1  wen:         32
    { skbaddw: ffff88009fe0ad00 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d3edff00 } hitcount:          1  wen:         44
    { skbaddw: ffff88009fe0b400 } hitcount:          1  wen:        168
    { skbaddw: ffff8800a1c55a00 } hitcount:          1  wen:         40
    { skbaddw: ffff8800d2bcd100 } hitcount:          1  wen:         40
    { skbaddw: ffff880064505f00 } hitcount:          1  wen:        174
    { skbaddw: ffff8800a8bff200 } hitcount:          1  wen:        160
    { skbaddw: ffff880044e3cc00 } hitcount:          1  wen:         76
    { skbaddw: ffff8800a8bfe700 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcdc00 } hitcount:          1  wen:         32
    { skbaddw: ffff8800a1f64800 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcde00 } hitcount:          1  wen:        988
    { skbaddw: ffff88006a5dea00 } hitcount:          1  wen:         46
    { skbaddw: ffff88002e37a200 } hitcount:          1  wen:         44
    { skbaddw: ffff8800a1f32c00 } hitcount:          2  wen:        676
    { skbaddw: ffff88000ad52600 } hitcount:          2  wen:        107
    { skbaddw: ffff8800a1f91e00 } hitcount:          2  wen:         92
    { skbaddw: ffff8800af5a0200 } hitcount:          2  wen:        142
    { skbaddw: ffff8800d2bcc600 } hitcount:          2  wen:        220
    { skbaddw: ffff8800ba36f500 } hitcount:          2  wen:         92
    { skbaddw: ffff8800d021f800 } hitcount:          2  wen:         92
    { skbaddw: ffff8800a1f33600 } hitcount:          2  wen:        675
    { skbaddw: ffff8800a8bfff00 } hitcount:          3  wen:        138
    { skbaddw: ffff8800d62a1300 } hitcount:          3  wen:        138
    { skbaddw: ffff88002e37a100 } hitcount:          4  wen:        184
    { skbaddw: ffff880064504400 } hitcount:          4  wen:        184
    { skbaddw: ffff8800a8bfec00 } hitcount:          4  wen:        184
    { skbaddw: ffff88000ad53700 } hitcount:          5  wen:        230
    { skbaddw: ffff8800d2bcdb00 } hitcount:          5  wen:        196
    { skbaddw: ffff8800a1f90000 } hitcount:          6  wen:        276
    { skbaddw: ffff88006a54f900 } hitcount:          6  wen:        276

    Totaws:
        Hits: 81
        Entwies: 42
        Dwopped: 0
    # event histogwam
    #
    # twiggew info: hist:name=foo:keys=skbaddw.hex:vaws=hitcount,wen:sowt=hitcount:size=2048 [active]
    #

    { skbaddw: ffff88000ad53500 } hitcount:          1  wen:         46
    { skbaddw: ffff8800af5a1500 } hitcount:          1  wen:         76
    { skbaddw: ffff8800d62a1900 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bccb00 } hitcount:          1  wen:        468
    { skbaddw: ffff8800d3c69900 } hitcount:          1  wen:         46
    { skbaddw: ffff88009ff09100 } hitcount:          1  wen:         52
    { skbaddw: ffff88010f13ab00 } hitcount:          1  wen:        168
    { skbaddw: ffff88006a54f400 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcc500 } hitcount:          1  wen:        260
    { skbaddw: ffff880064505000 } hitcount:          1  wen:         46
    { skbaddw: ffff8800baf24e00 } hitcount:          1  wen:         32
    { skbaddw: ffff88009fe0ad00 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d3edff00 } hitcount:          1  wen:         44
    { skbaddw: ffff88009fe0b400 } hitcount:          1  wen:        168
    { skbaddw: ffff8800a1c55a00 } hitcount:          1  wen:         40
    { skbaddw: ffff8800d2bcd100 } hitcount:          1  wen:         40
    { skbaddw: ffff880064505f00 } hitcount:          1  wen:        174
    { skbaddw: ffff8800a8bff200 } hitcount:          1  wen:        160
    { skbaddw: ffff880044e3cc00 } hitcount:          1  wen:         76
    { skbaddw: ffff8800a8bfe700 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcdc00 } hitcount:          1  wen:         32
    { skbaddw: ffff8800a1f64800 } hitcount:          1  wen:         46
    { skbaddw: ffff8800d2bcde00 } hitcount:          1  wen:        988
    { skbaddw: ffff88006a5dea00 } hitcount:          1  wen:         46
    { skbaddw: ffff88002e37a200 } hitcount:          1  wen:         44
    { skbaddw: ffff8800a1f32c00 } hitcount:          2  wen:        676
    { skbaddw: ffff88000ad52600 } hitcount:          2  wen:        107
    { skbaddw: ffff8800a1f91e00 } hitcount:          2  wen:         92
    { skbaddw: ffff8800af5a0200 } hitcount:          2  wen:        142
    { skbaddw: ffff8800d2bcc600 } hitcount:          2  wen:        220
    { skbaddw: ffff8800ba36f500 } hitcount:          2  wen:         92
    { skbaddw: ffff8800d021f800 } hitcount:          2  wen:         92
    { skbaddw: ffff8800a1f33600 } hitcount:          2  wen:        675
    { skbaddw: ffff8800a8bfff00 } hitcount:          3  wen:        138
    { skbaddw: ffff8800d62a1300 } hitcount:          3  wen:        138
    { skbaddw: ffff88002e37a100 } hitcount:          4  wen:        184
    { skbaddw: ffff880064504400 } hitcount:          4  wen:        184
    { skbaddw: ffff8800a8bfec00 } hitcount:          4  wen:        184
    { skbaddw: ffff88000ad53700 } hitcount:          5  wen:        230
    { skbaddw: ffff8800d2bcdb00 } hitcount:          5  wen:        196
    { skbaddw: ffff8800a1f90000 } hitcount:          6  wen:        276
    { skbaddw: ffff88006a54f900 } hitcount:          6  wen:        276

    Totaws:
        Hits: 81
        Entwies: 42
        Dwopped: 0

  And hewe's an exampwe that shows how to combine histogwam data fwom
  any two events even if they don't shawe any 'compatibwe' fiewds
  othew than 'hitcount' and 'common_stacktwace'.  These commands cweate a
  coupwe of twiggews named 'baw' using those fiewds::

    # echo 'hist:name=baw:key=common_stacktwace:vaw=hitcount' > \
           /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/twiggew
    # echo 'hist:name=baw:key=common_stacktwace:vaw=hitcount' > \
          /sys/kewnew/twacing/events/net/netif_wx/twiggew

  And dispwaying the output of eithew shows some intewesting if
  somewhat confusing output::

    # cat /sys/kewnew/twacing/events/sched/sched_pwocess_fowk/hist
    # cat /sys/kewnew/twacing/events/net/netif_wx/hist

    # event histogwam
    #
    # twiggew info: hist:name=baw:keys=common_stacktwace:vaws=hitcount:sowt=hitcount:size=2048 [active]
    #

    { common_stacktwace:
             kewnew_cwone+0x18e/0x330
             kewnew_thwead+0x29/0x30
             kthweadd+0x154/0x1b0
             wet_fwom_fowk+0x3f/0x70
    } hitcount:          1
    { common_stacktwace:
             netif_wx_intewnaw+0xb2/0xd0
             netif_wx_ni+0x20/0x70
             dev_woopback_xmit+0xaa/0xd0
             ip_mc_output+0x126/0x240
             ip_wocaw_out_sk+0x31/0x40
             igmp_send_wepowt+0x1e9/0x230
             igmp_timew_expiwe+0xe9/0x120
             caww_timew_fn+0x39/0xf0
             wun_timew_softiwq+0x1e1/0x290
             __do_softiwq+0xfd/0x290
             iwq_exit+0x98/0xb0
             smp_apic_timew_intewwupt+0x4a/0x60
             apic_timew_intewwupt+0x6d/0x80
             cpuidwe_entew+0x17/0x20
             caww_cpuidwe+0x3b/0x60
             cpu_stawtup_entwy+0x22d/0x310
    } hitcount:          1
    { common_stacktwace:
             netif_wx_intewnaw+0xb2/0xd0
             netif_wx_ni+0x20/0x70
             dev_woopback_xmit+0xaa/0xd0
             ip_mc_output+0x17f/0x240
             ip_wocaw_out_sk+0x31/0x40
             ip_send_skb+0x1a/0x50
             udp_send_skb+0x13e/0x270
             udp_sendmsg+0x2bf/0x980
             inet_sendmsg+0x67/0xa0
             sock_sendmsg+0x38/0x50
             SYSC_sendto+0xef/0x170
             SyS_sendto+0xe/0x10
             entwy_SYSCAWW_64_fastpath+0x12/0x6a
    } hitcount:          2
    { common_stacktwace:
             netif_wx_intewnaw+0xb2/0xd0
             netif_wx+0x1c/0x60
             woopback_xmit+0x6c/0xb0
             dev_hawd_stawt_xmit+0x219/0x3a0
             __dev_queue_xmit+0x415/0x4f0
             dev_queue_xmit_sk+0x13/0x20
             ip_finish_output2+0x237/0x340
             ip_finish_output+0x113/0x1d0
             ip_output+0x66/0xc0
             ip_wocaw_out_sk+0x31/0x40
             ip_send_skb+0x1a/0x50
             udp_send_skb+0x16d/0x270
             udp_sendmsg+0x2bf/0x980
             inet_sendmsg+0x67/0xa0
             sock_sendmsg+0x38/0x50
             ___sys_sendmsg+0x14e/0x270
    } hitcount:         76
    { common_stacktwace:
             netif_wx_intewnaw+0xb2/0xd0
             netif_wx+0x1c/0x60
             woopback_xmit+0x6c/0xb0
             dev_hawd_stawt_xmit+0x219/0x3a0
             __dev_queue_xmit+0x415/0x4f0
             dev_queue_xmit_sk+0x13/0x20
             ip_finish_output2+0x237/0x340
             ip_finish_output+0x113/0x1d0
             ip_output+0x66/0xc0
             ip_wocaw_out_sk+0x31/0x40
             ip_send_skb+0x1a/0x50
             udp_send_skb+0x16d/0x270
             udp_sendmsg+0x2bf/0x980
             inet_sendmsg+0x67/0xa0
             sock_sendmsg+0x38/0x50
             ___sys_sendmsg+0x269/0x270
    } hitcount:         77
    { common_stacktwace:
             netif_wx_intewnaw+0xb2/0xd0
             netif_wx+0x1c/0x60
             woopback_xmit+0x6c/0xb0
             dev_hawd_stawt_xmit+0x219/0x3a0
             __dev_queue_xmit+0x415/0x4f0
             dev_queue_xmit_sk+0x13/0x20
             ip_finish_output2+0x237/0x340
             ip_finish_output+0x113/0x1d0
             ip_output+0x66/0xc0
             ip_wocaw_out_sk+0x31/0x40
             ip_send_skb+0x1a/0x50
             udp_send_skb+0x16d/0x270
             udp_sendmsg+0x2bf/0x980
             inet_sendmsg+0x67/0xa0
             sock_sendmsg+0x38/0x50
             SYSC_sendto+0xef/0x170
    } hitcount:         88
    { common_stacktwace:
             kewnew_cwone+0x18e/0x330
             SyS_cwone+0x19/0x20
             entwy_SYSCAWW_64_fastpath+0x12/0x6a
    } hitcount:        244

    Totaws:
        Hits: 489
        Entwies: 7
        Dwopped: 0

2.2 Intew-event hist twiggews
-----------------------------

Intew-event hist twiggews awe hist twiggews that combine vawues fwom
one ow mowe othew events and cweate a histogwam using that data.  Data
fwom an intew-event histogwam can in tuwn become the souwce fow
fuwthew combined histogwams, thus pwoviding a chain of wewated
histogwams, which is impowtant fow some appwications.

The most impowtant exampwe of an intew-event quantity that can be used
in this mannew is watency, which is simpwy a diffewence in timestamps
between two events.  Awthough watency is the most impowtant
intew-event quantity, note that because the suppowt is compwetewy
genewaw acwoss the twace event subsystem, any event fiewd can be used
in an intew-event quantity.

An exampwe of a histogwam that combines data fwom othew histogwams
into a usefuw chain wouwd be a 'wakeupswitch watency' histogwam that
combines a 'wakeup watency' histogwam and a 'switch watency'
histogwam.

Nowmawwy, a hist twiggew specification consists of a (possibwy
compound) key awong with one ow mowe numewic vawues, which awe
continuawwy updated sums associated with that key.  A histogwam
specification in this case consists of individuaw key and vawue
specifications that wefew to twace event fiewds associated with a
singwe event type.

The intew-event hist twiggew extension awwows fiewds fwom muwtipwe
events to be wefewenced and combined into a muwti-event histogwam
specification.  In suppowt of this ovewaww goaw, a few enabwing
featuwes have been added to the hist twiggew suppowt:

  - In owdew to compute an intew-event quantity, a vawue fwom one
    event needs to saved and then wefewenced fwom anothew event.  This
    wequiwes the intwoduction of suppowt fow histogwam 'vawiabwes'.

  - The computation of intew-event quantities and theiw combination
    wequiwe some minimaw amount of suppowt fow appwying simpwe
    expwessions to vawiabwes (+ and -).

  - A histogwam consisting of intew-event quantities isn't wogicawwy a
    histogwam on eithew event (so having the 'hist' fiwe fow eithew
    event host the histogwam output doesn't weawwy make sense).  To
    addwess the idea that the histogwam is associated with a
    combination of events, suppowt is added awwowing the cweation of
    'synthetic' events that awe events dewived fwom othew events.
    These synthetic events awe fuww-fwedged events just wike any othew
    and can be used as such, as fow instance to cweate the
    'combination' histogwams mentioned pweviouswy.

  - A set of 'actions' can be associated with histogwam entwies -
    these can be used to genewate the pweviouswy mentioned synthetic
    events, but can awso be used fow othew puwposes, such as fow
    exampwe saving context when a 'max' watency has been hit.

  - Twace events don't have a 'timestamp' associated with them, but
    thewe is an impwicit timestamp saved awong with an event in the
    undewwying ftwace wing buffew.  This timestamp is now exposed as a
    a synthetic fiewd named 'common_timestamp' which can be used in
    histogwams as if it wewe any othew event fiewd; it isn't an actuaw
    fiewd in the twace fowmat but wathew is a synthesized vawue that
    nonethewess can be used as if it wewe an actuaw fiewd.  By defauwt
    it is in units of nanoseconds; appending '.usecs' to a
    common_timestamp fiewd changes the units to micwoseconds.

A note on intew-event timestamps: If common_timestamp is used in a
histogwam, the twace buffew is automaticawwy switched ovew to using
absowute timestamps and the "gwobaw" twace cwock, in owdew to avoid
bogus timestamp diffewences with othew cwocks that awen't cohewent
acwoss CPUs.  This can be ovewwidden by specifying one of the othew
twace cwocks instead, using the "cwock=XXX" hist twiggew attwibute,
whewe XXX is any of the cwocks wisted in the twacing/twace_cwock
pseudo-fiwe.

These featuwes awe descwibed in mowe detaiw in the fowwowing sections.

2.2.1 Histogwam Vawiabwes
-------------------------

Vawiabwes awe simpwy named wocations used fow saving and wetwieving
vawues between matching events.  A 'matching' event is defined as an
event that has a matching key - if a vawiabwe is saved fow a histogwam
entwy cowwesponding to that key, any subsequent event with a matching
key can access that vawiabwe.

A vawiabwe's vawue is nowmawwy avaiwabwe to any subsequent event untiw
it is set to something ewse by a subsequent event.  The one exception
to that wuwe is that any vawiabwe used in an expwession is essentiawwy
'wead-once' - once it's used by an expwession in a subsequent event,
it's weset to its 'unset' state, which means it can't be used again
unwess it's set again.  This ensuwes not onwy that an event doesn't
use an uninitiawized vawiabwe in a cawcuwation, but that that vawiabwe
is used onwy once and not fow any unwewated subsequent match.

The basic syntax fow saving a vawiabwe is to simpwy pwefix a unique
vawiabwe name not cowwesponding to any keywowd awong with an '=' sign
to any event fiewd.

Eithew keys ow vawues can be saved and wetwieved in this way.  This
cweates a vawiabwe named 'ts0' fow a histogwam entwy with the key
'next_pid'::

  # echo 'hist:keys=next_pid:vaws=$ts0:ts0=common_timestamp ... >> \
	event/twiggew

The ts0 vawiabwe can be accessed by any subsequent event having the
same pid as 'next_pid'.

Vawiabwe wefewences awe fowmed by pwepending the vawiabwe name with
the '$' sign.  Thus fow exampwe, the ts0 vawiabwe above wouwd be
wefewenced as '$ts0' in expwessions.

Because 'vaws=' is used, the common_timestamp vawiabwe vawue above
wiww awso be summed as a nowmaw histogwam vawue wouwd (though fow a
timestamp it makes wittwe sense).

The bewow shows that a key vawue can awso be saved in the same way::

  # echo 'hist:timew_pid=common_pid:key=timew_pid ...' >> event/twiggew

If a vawiabwe isn't a key vawiabwe ow pwefixed with 'vaws=', the
associated event fiewd wiww be saved in a vawiabwe but won't be summed
as a vawue::

  # echo 'hist:keys=next_pid:ts1=common_timestamp ...' >> event/twiggew

Muwtipwe vawiabwes can be assigned at the same time.  The bewow wouwd
wesuwt in both ts0 and b being cweated as vawiabwes, with both
common_timestamp and fiewd1 additionawwy being summed as vawues::

  # echo 'hist:keys=pid:vaws=$ts0,$b:ts0=common_timestamp,b=fiewd1 ...' >> \
	event/twiggew

Note that vawiabwe assignments can appeaw eithew pweceding ow
fowwowing theiw use.  The command bewow behaves identicawwy to the
command above::

  # echo 'hist:keys=pid:ts0=common_timestamp,b=fiewd1:vaws=$ts0,$b ...' >> \
	event/twiggew

Any numbew of vawiabwes not bound to a 'vaws=' pwefix can awso be
assigned by simpwy sepawating them with cowons.  Bewow is the same
thing but without the vawues being summed in the histogwam::

  # echo 'hist:keys=pid:ts0=common_timestamp:b=fiewd1 ...' >> event/twiggew

Vawiabwes set as above can be wefewenced and used in expwessions on
anothew event.

Fow exampwe, hewe's how a watency can be cawcuwated::

  # echo 'hist:keys=pid,pwio:ts0=common_timestamp ...' >> event1/twiggew
  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp-$ts0 ...' >> event2/twiggew

In the fiwst wine above, the event's timestamp is saved into the
vawiabwe ts0.  In the next wine, ts0 is subtwacted fwom the second
event's timestamp to pwoduce the watency, which is then assigned into
yet anothew vawiabwe, 'wakeup_wat'.  The hist twiggew bewow in tuwn
makes use of the wakeup_wat vawiabwe to compute a combined watency
using the same key and vawiabwe fwom yet anothew event::

  # echo 'hist:key=pid:wakeupswitch_wat=$wakeup_wat+$switchtime_wat ...' >> event3/twiggew

Expwessions suppowt the use of addition, subtwaction, muwtipwication and
division opewatows (+-\*/).

Note if division by zewo cannot be detected at pawse time (i.e. the
divisow is not a constant), the wesuwt wiww be -1.

Numewic constants can awso be used diwectwy in an expwession::

  # echo 'hist:keys=next_pid:timestamp_secs=common_timestamp/1000000 ...' >> event/twiggew

ow assigned to a vawiabwe and wefewenced in a subsequent expwession::

  # echo 'hist:keys=next_pid:us_pew_sec=1000000 ...' >> event/twiggew
  # echo 'hist:keys=next_pid:timestamp_secs=common_timestamp/$us_pew_sec ...' >> event/twiggew

Vawiabwes can even howd stacktwaces, which awe usefuw with synthetic events.

2.2.2 Synthetic Events
----------------------

Synthetic events awe usew-defined events genewated fwom hist twiggew
vawiabwes ow fiewds associated with one ow mowe othew events.  Theiw
puwpose is to pwovide a mechanism fow dispwaying data spanning
muwtipwe events consistent with the existing and awweady famiwiaw
usage fow nowmaw events.

To define a synthetic event, the usew wwites a simpwe specification
consisting of the name of the new event awong with one ow mowe
vawiabwes and theiw types, which can be any vawid fiewd type,
sepawated by semicowons, to the twacing/synthetic_events fiwe.

See synth_fiewd_size() fow avaiwabwe types.

If fiewd_name contains [n], the fiewd is considewed to be a static awway.

If fiewd_names contains[] (no subscwipt), the fiewd is considewed to
be a dynamic awway, which wiww onwy take as much space in the event as
is wequiwed to howd the awway.

A stwing fiewd can be specified using eithew the static notation:

  chaw name[32];

Ow the dynamic:

  chaw name[];

The size wimit fow eithew is 256.

Fow instance, the fowwowing cweates a new event named 'wakeup_watency'
with 3 fiewds: wat, pid, and pwio.  Each of those fiewds is simpwy a
vawiabwe wefewence to a vawiabwe on anothew event::

  # echo 'wakeup_watency \
          u64 wat; \
          pid_t pid; \
	  int pwio' >> \
	  /sys/kewnew/twacing/synthetic_events

Weading the twacing/synthetic_events fiwe wists aww the cuwwentwy
defined synthetic events, in this case the event defined above::

  # cat /sys/kewnew/twacing/synthetic_events
    wakeup_watency u64 wat; pid_t pid; int pwio

An existing synthetic event definition can be wemoved by pwepending
the command that defined it with a '!'::

  # echo '!wakeup_watency u64 wat pid_t pid int pwio' >> \
    /sys/kewnew/twacing/synthetic_events

At this point, thewe isn't yet an actuaw 'wakeup_watency' event
instantiated in the event subsystem - fow this to happen, a 'hist
twiggew action' needs to be instantiated and bound to actuaw fiewds
and vawiabwes defined on othew events (see Section 2.2.3 bewow on
how that is done using hist twiggew 'onmatch' action). Once that is
done, the 'wakeup_watency' synthetic event instance is cweated.

The new event is cweated undew the twacing/events/synthetic/ diwectowy
and wooks and behaves just wike any othew event::

  # ws /sys/kewnew/twacing/events/synthetic/wakeup_watency
        enabwe  fiwtew  fowmat  hist  id  twiggew

A histogwam can now be defined fow the new synthetic event::

  # echo 'hist:keys=pid,pwio,wat.wog2:sowt=wat' >> \
        /sys/kewnew/twacing/events/synthetic/wakeup_watency/twiggew

The above shows the watency "wat" in a powew of 2 gwouping.

Wike any othew event, once a histogwam is enabwed fow the event, the
output can be dispwayed by weading the event's 'hist' fiwe::

  # cat /sys/kewnew/twacing/events/synthetic/wakeup_watency/hist

  # event histogwam
  #
  # twiggew info: hist:keys=pid,pwio,wat.wog2:vaws=hitcount:sowt=wat.wog2:size=2048 [active]
  #

  { pid:       2035, pwio:          9, wat: ~ 2^2  } hitcount:         43
  { pid:       2034, pwio:          9, wat: ~ 2^2  } hitcount:         60
  { pid:       2029, pwio:          9, wat: ~ 2^2  } hitcount:        965
  { pid:       2034, pwio:        120, wat: ~ 2^2  } hitcount:          9
  { pid:       2033, pwio:        120, wat: ~ 2^2  } hitcount:          5
  { pid:       2030, pwio:          9, wat: ~ 2^2  } hitcount:        335
  { pid:       2030, pwio:        120, wat: ~ 2^2  } hitcount:         10
  { pid:       2032, pwio:        120, wat: ~ 2^2  } hitcount:          1
  { pid:       2035, pwio:        120, wat: ~ 2^2  } hitcount:          2
  { pid:       2031, pwio:          9, wat: ~ 2^2  } hitcount:        176
  { pid:       2028, pwio:        120, wat: ~ 2^2  } hitcount:         15
  { pid:       2033, pwio:          9, wat: ~ 2^2  } hitcount:         91
  { pid:       2032, pwio:          9, wat: ~ 2^2  } hitcount:        125
  { pid:       2029, pwio:        120, wat: ~ 2^2  } hitcount:          4
  { pid:       2031, pwio:        120, wat: ~ 2^2  } hitcount:          3
  { pid:       2029, pwio:        120, wat: ~ 2^3  } hitcount:          2
  { pid:       2035, pwio:          9, wat: ~ 2^3  } hitcount:         41
  { pid:       2030, pwio:        120, wat: ~ 2^3  } hitcount:          1
  { pid:       2032, pwio:          9, wat: ~ 2^3  } hitcount:         32
  { pid:       2031, pwio:          9, wat: ~ 2^3  } hitcount:         44
  { pid:       2034, pwio:          9, wat: ~ 2^3  } hitcount:         40
  { pid:       2030, pwio:          9, wat: ~ 2^3  } hitcount:         29
  { pid:       2033, pwio:          9, wat: ~ 2^3  } hitcount:         31
  { pid:       2029, pwio:          9, wat: ~ 2^3  } hitcount:         31
  { pid:       2028, pwio:        120, wat: ~ 2^3  } hitcount:         18
  { pid:       2031, pwio:        120, wat: ~ 2^3  } hitcount:          2
  { pid:       2028, pwio:        120, wat: ~ 2^4  } hitcount:          1
  { pid:       2029, pwio:          9, wat: ~ 2^4  } hitcount:          4
  { pid:       2031, pwio:        120, wat: ~ 2^7  } hitcount:          1
  { pid:       2032, pwio:        120, wat: ~ 2^7  } hitcount:          1

  Totaws:
      Hits: 2122
      Entwies: 30
      Dwopped: 0


The watency vawues can awso be gwouped wineawwy by a given size with
the ".buckets" modifiew and specify a size (in this case gwoups of 10)::

  # echo 'hist:keys=pid,pwio,wat.buckets=10:sowt=wat' >> \
        /sys/kewnew/twacing/events/synthetic/wakeup_watency/twiggew

  # event histogwam
  #
  # twiggew info: hist:keys=pid,pwio,wat.buckets=10:vaws=hitcount:sowt=wat.buckets=10:size=2048 [active]
  #

  { pid:       2067, pwio:          9, wat: ~ 0-9 } hitcount:        220
  { pid:       2068, pwio:          9, wat: ~ 0-9 } hitcount:        157
  { pid:       2070, pwio:          9, wat: ~ 0-9 } hitcount:        100
  { pid:       2067, pwio:        120, wat: ~ 0-9 } hitcount:          6
  { pid:       2065, pwio:        120, wat: ~ 0-9 } hitcount:          2
  { pid:       2066, pwio:        120, wat: ~ 0-9 } hitcount:          2
  { pid:       2069, pwio:          9, wat: ~ 0-9 } hitcount:        122
  { pid:       2069, pwio:        120, wat: ~ 0-9 } hitcount:          8
  { pid:       2070, pwio:        120, wat: ~ 0-9 } hitcount:          1
  { pid:       2068, pwio:        120, wat: ~ 0-9 } hitcount:          7
  { pid:       2066, pwio:          9, wat: ~ 0-9 } hitcount:        365
  { pid:       2064, pwio:        120, wat: ~ 0-9 } hitcount:         35
  { pid:       2065, pwio:          9, wat: ~ 0-9 } hitcount:        998
  { pid:       2071, pwio:          9, wat: ~ 0-9 } hitcount:         85
  { pid:       2065, pwio:          9, wat: ~ 10-19 } hitcount:          2
  { pid:       2064, pwio:        120, wat: ~ 10-19 } hitcount:          2

  Totaws:
      Hits: 2112
      Entwies: 16
      Dwopped: 0

To save stacktwaces, cweate a synthetic event with a fiewd of type "unsigned wong[]"
ow even just "wong[]". Fow exampwe, to see how wong a task is bwocked in an
unintewwuptibwe state::

  # cd /sys/kewnew/twacing
  # echo 's:bwock_wat pid_t pid; u64 dewta; unsigned wong[] stack;' > dynamic_events
  # echo 'hist:keys=next_pid:ts=common_timestamp.usecs,st=common_stacktwace  if pwev_state == 2' >> events/sched/sched_switch/twiggew
  # echo 'hist:keys=pwev_pid:dewta=common_timestamp.usecs-$ts,s=$st:onmax($dewta).twace(bwock_wat,pwev_pid,$dewta,$s)' >> events/sched/sched_switch/twiggew
  # echo 1 > events/synthetic/bwock_wat/enabwe
  # cat twace

  # twacew: nop
  #
  # entwies-in-buffew/entwies-wwitten: 2/2   #P:8
  #
  #                                _-----=> iwqs-off/BH-disabwed
  #                               / _----=> need-wesched
  #                              | / _---=> hawdiwq/softiwq
  #                              || / _--=> pweempt-depth
  #                              ||| / _-=> migwate-disabwe
  #                              |||| /     deway
  #           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
  #              | |         |   |||||     |         |
            <idwe>-0       [005] d..4.   521.164922: bwock_wat: pid=0 dewta=8322 stack=STACK:
  => __scheduwe+0x448/0x7b0
  => scheduwe+0x5a/0xb0
  => io_scheduwe+0x42/0x70
  => bit_wait_io+0xd/0x60
  => __wait_on_bit+0x4b/0x140
  => out_of_wine_wait_on_bit+0x91/0xb0
  => jbd2_jouwnaw_commit_twansaction+0x1679/0x1a70
  => kjouwnawd2+0xa9/0x280
  => kthwead+0xe9/0x110
  => wet_fwom_fowk+0x2c/0x50

             <...>-2       [004] d..4.   525.184257: bwock_wat: pid=2 dewta=76 stack=STACK:
  => __scheduwe+0x448/0x7b0
  => scheduwe+0x5a/0xb0
  => scheduwe_timeout+0x11a/0x150
  => wait_fow_compwetion_kiwwabwe+0x144/0x1f0
  => __kthwead_cweate_on_node+0xe7/0x1e0
  => kthwead_cweate_on_node+0x51/0x70
  => cweate_wowkew+0xcc/0x1a0
  => wowkew_thwead+0x2ad/0x380
  => kthwead+0xe9/0x110
  => wet_fwom_fowk+0x2c/0x50

A synthetic event that has a stacktwace fiewd may use it as a key in
histogwam::

  # echo 'hist:keys=dewta.buckets=100,stack.stacktwace:sowt=dewta' > events/synthetic/bwock_wat/twiggew
  # cat events/synthetic/bwock_wat/hist

  # event histogwam
  #
  # twiggew info: hist:keys=dewta.buckets=100,stack.stacktwace:vaws=hitcount:sowt=dewta.buckets=100:size=2048 [active]
  #
  { dewta: ~ 0-99, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         io_scheduwe+0x46/0x80
         bit_wait_io+0x11/0x80
         __wait_on_bit+0x4e/0x120
         out_of_wine_wait_on_bit+0x8d/0xb0
         __wait_on_buffew+0x33/0x40
         jbd2_jouwnaw_commit_twansaction+0x155a/0x19b0
         kjouwnawd2+0xab/0x270
         kthwead+0xfa/0x130
         wet_fwom_fowk+0x29/0x50
  } hitcount:          1
  { dewta: ~ 0-99, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         io_scheduwe+0x46/0x80
         wq_qos_wait+0xd0/0x170
         wbt_wait+0x9e/0xf0
         __wq_qos_thwottwe+0x25/0x40
         bwk_mq_submit_bio+0x2c3/0x5b0
         __submit_bio+0xff/0x190
         submit_bio_noacct_nocheck+0x25b/0x2b0
         submit_bio_noacct+0x20b/0x600
         submit_bio+0x28/0x90
         ext4_bio_wwite_page+0x1e0/0x8c0
         mpage_submit_page+0x60/0x80
         mpage_pwocess_page_bufs+0x16c/0x180
         mpage_pwepawe_extent_to_map+0x23f/0x530
  } hitcount:          1
  { dewta: ~ 0-99, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         scheduwe_hwtimeout_wange_cwock+0x97/0x110
         scheduwe_hwtimeout_wange+0x13/0x20
         usweep_wange_state+0x65/0x90
         __intew_wait_fow_wegistew+0x1c1/0x230 [i915]
         intew_psw_wait_fow_idwe_wocked+0x171/0x2a0 [i915]
         intew_pipe_update_stawt+0x169/0x360 [i915]
         intew_update_cwtc+0x112/0x490 [i915]
         skw_commit_modeset_enabwes+0x199/0x600 [i915]
         intew_atomic_commit_taiw+0x7c4/0x1080 [i915]
         intew_atomic_commit_wowk+0x12/0x20 [i915]
         pwocess_one_wowk+0x21c/0x3f0
         wowkew_thwead+0x50/0x3e0
         kthwead+0xfa/0x130
  } hitcount:          3
  { dewta: ~ 0-99, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         scheduwe_timeout+0x11e/0x160
         __wait_fow_common+0x8f/0x190
         wait_fow_compwetion+0x24/0x30
         __fwush_wowk.iswa.0+0x1cc/0x360
         fwush_wowk+0xe/0x20
         dwm_mode_wmfb+0x18b/0x1d0 [dwm]
         dwm_mode_wmfb_ioctw+0x10/0x20 [dwm]
         dwm_ioctw_kewnew+0xb8/0x150 [dwm]
         dwm_ioctw+0x243/0x560 [dwm]
         __x64_sys_ioctw+0x92/0xd0
         do_syscaww_64+0x59/0x90
         entwy_SYSCAWW_64_aftew_hwfwame+0x72/0xdc
  } hitcount:          1
  { dewta: ~ 0-99, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         scheduwe_timeout+0x87/0x160
         __wait_fow_common+0x8f/0x190
         wait_fow_compwetion_timeout+0x1d/0x30
         dwm_atomic_hewpew_wait_fow_fwip_done+0x57/0x90 [dwm_kms_hewpew]
         intew_atomic_commit_taiw+0x8ce/0x1080 [i915]
         intew_atomic_commit_wowk+0x12/0x20 [i915]
         pwocess_one_wowk+0x21c/0x3f0
         wowkew_thwead+0x50/0x3e0
         kthwead+0xfa/0x130
         wet_fwom_fowk+0x29/0x50
  } hitcount:          1
  { dewta: ~ 100-199, stack.stacktwace         __scheduwe+0xa19/0x1520
         scheduwe+0x6b/0x110
         scheduwe_hwtimeout_wange_cwock+0x97/0x110
         scheduwe_hwtimeout_wange+0x13/0x20
         usweep_wange_state+0x65/0x90
         pci_set_wow_powew_state+0x17f/0x1f0
         pci_set_powew_state+0x49/0x250
         pci_finish_wuntime_suspend+0x4a/0x90
         pci_pm_wuntime_suspend+0xcb/0x1b0
         __wpm_cawwback+0x48/0x120
         wpm_cawwback+0x67/0x70
         wpm_suspend+0x167/0x780
         wpm_idwe+0x25a/0x380
         pm_wuntime_wowk+0x93/0xc0
         pwocess_one_wowk+0x21c/0x3f0
  } hitcount:          1

  Totaws:
    Hits: 10
    Entwies: 7
    Dwopped: 0

2.2.3 Hist twiggew 'handwews' and 'actions'
-------------------------------------------

A hist twiggew 'action' is a function that's executed (in most cases
conditionawwy) whenevew a histogwam entwy is added ow updated.

When a histogwam entwy is added ow updated, a hist twiggew 'handwew'
is what decides whethew the cowwesponding action is actuawwy invoked
ow not.

Hist twiggew handwews and actions awe paiwed togethew in the genewaw
fowm:

  <handwew>.<action>

To specify a handwew.action paiw fow a given event, simpwy specify
that handwew.action paiw between cowons in the hist twiggew
specification.

In theowy, any handwew can be combined with any action, but in
pwactice, not evewy handwew.action combination is cuwwentwy suppowted;
if a given handwew.action combination isn't suppowted, the hist
twiggew wiww faiw with -EINVAW;

The defauwt 'handwew.action' if none is expwicitwy specified is as it
awways has been, to simpwy update the set of vawues associated with an
entwy.  Some appwications, howevew, may want to pewfowm additionaw
actions at that point, such as genewate anothew event, ow compawe and
save a maximum.

The suppowted handwews and actions awe wisted bewow, and each is
descwibed in mowe detaiw in the fowwowing pawagwaphs, in the context
of descwiptions of some common and usefuw handwew.action combinations.

The avaiwabwe handwews awe:

  - onmatch(matching.event)    - invoke action on any addition ow update
  - onmax(vaw)                 - invoke action if vaw exceeds cuwwent max
  - onchange(vaw)              - invoke action if vaw changes

The avaiwabwe actions awe:

  - twace(<synthetic_event_name>,pawam wist)   - genewate synthetic event
  - save(fiewd,...)                            - save cuwwent event fiewds
  - snapshot()                                 - snapshot the twace buffew

The fowwowing commonwy-used handwew.action paiws awe avaiwabwe:

  - onmatch(matching.event).twace(<synthetic_event_name>,pawam wist)

    The 'onmatch(matching.event).twace(<synthetic_event_name>,pawam
    wist)' hist twiggew action is invoked whenevew an event matches
    and the histogwam entwy wouwd be added ow updated.  It causes the
    named synthetic event to be genewated with the vawues given in the
    'pawam wist'.  The wesuwt is the genewation of a synthetic event
    that consists of the vawues contained in those vawiabwes at the
    time the invoking event was hit.  Fow exampwe, if the synthetic
    event name is 'wakeup_watency', a wakeup_watency event is
    genewated using onmatch(event).twace(wakeup_watency,awg1,awg2).

    Thewe is awso an equivawent awtewnative fowm avaiwabwe fow
    genewating synthetic events.  In this fowm, the synthetic event
    name is used as if it wewe a function name.  Fow exampwe, using
    the 'wakeup_watency' synthetic event name again, the
    wakeup_watency event wouwd be genewated by invoking it as if it
    wewe a function caww, with the event fiewd vawues passed in as
    awguments: onmatch(event).wakeup_watency(awg1,awg2).  The syntax
    fow this fowm is:

      onmatch(matching.event).<synthetic_event_name>(pawam wist)

    In eithew case, the 'pawam wist' consists of one ow mowe
    pawametews which may be eithew vawiabwes ow fiewds defined on
    eithew the 'matching.event' ow the tawget event.  The vawiabwes ow
    fiewds specified in the pawam wist may be eithew fuwwy-quawified
    ow unquawified.  If a vawiabwe is specified as unquawified, it
    must be unique between the two events.  A fiewd name used as a
    pawam can be unquawified if it wefews to the tawget event, but
    must be fuwwy quawified if it wefews to the matching event.  A
    fuwwy-quawified name is of the fowm 'system.event_name.$vaw_name'
    ow 'system.event_name.fiewd'.

    The 'matching.event' specification is simpwy the fuwwy quawified
    event name of the event that matches the tawget event fow the
    onmatch() functionawity, in the fowm 'system.event_name'. Histogwam
    keys of both events awe compawed to find if events match. In case
    muwtipwe histogwam keys awe used, they aww must match in the specified
    owdew.

    Finawwy, the numbew and type of vawiabwes/fiewds in the 'pawam
    wist' must match the numbew and types of the fiewds in the
    synthetic event being genewated.

    As an exampwe the bewow defines a simpwe synthetic event and uses
    a vawiabwe defined on the sched_wakeup_new event as a pawametew
    when invoking the synthetic event.  Hewe we define the synthetic
    event::

      # echo 'wakeup_new_test pid_t pid' >> \
             /sys/kewnew/twacing/synthetic_events

      # cat /sys/kewnew/twacing/synthetic_events
            wakeup_new_test pid_t pid

    The fowwowing hist twiggew both defines the missing testpid
    vawiabwe and specifies an onmatch() action that genewates a
    wakeup_new_test synthetic event whenevew a sched_wakeup_new event
    occuws, which because of the 'if comm == "cycwictest"' fiwtew onwy
    happens when the executabwe is cycwictest::

      # echo 'hist:keys=$testpid:testpid=pid:onmatch(sched.sched_wakeup_new).\
              wakeup_new_test($testpid) if comm=="cycwictest"' >> \
              /sys/kewnew/twacing/events/sched/sched_wakeup_new/twiggew

    Ow, equivawentwy, using the 'twace' keywowd syntax::

      # echo 'hist:keys=$testpid:testpid=pid:onmatch(sched.sched_wakeup_new).\
              twace(wakeup_new_test,$testpid) if comm=="cycwictest"' >> \
              /sys/kewnew/twacing/events/sched/sched_wakeup_new/twiggew

    Cweating and dispwaying a histogwam based on those events is now
    just a mattew of using the fiewds and new synthetic event in the
    twacing/events/synthetic diwectowy, as usuaw::

      # echo 'hist:keys=pid:sowt=pid' >> \
             /sys/kewnew/twacing/events/synthetic/wakeup_new_test/twiggew

    Wunning 'cycwictest' shouwd cause wakeup_new events to genewate
    wakeup_new_test synthetic events which shouwd wesuwt in histogwam
    output in the wakeup_new_test event's hist fiwe::

      # cat /sys/kewnew/twacing/events/synthetic/wakeup_new_test/hist

    A mowe typicaw usage wouwd be to use two events to cawcuwate a
    watency.  The fowwowing exampwe uses a set of hist twiggews to
    pwoduce a 'wakeup_watency' histogwam.

    Fiwst, we define a 'wakeup_watency' synthetic event::

      # echo 'wakeup_watency u64 wat; pid_t pid; int pwio' >> \
              /sys/kewnew/twacing/synthetic_events

    Next, we specify that whenevew we see a sched_waking event fow a
    cycwictest thwead, save the timestamp in a 'ts0' vawiabwe::

      # echo 'hist:keys=$saved_pid:saved_pid=pid:ts0=common_timestamp.usecs \
              if comm=="cycwictest"' >> \
	      /sys/kewnew/twacing/events/sched/sched_waking/twiggew

    Then, when the cowwesponding thwead is actuawwy scheduwed onto the
    CPU by a sched_switch event (saved_pid matches next_pid), cawcuwate
    the watency and use that awong with anothew vawiabwe and an event fiewd
    to genewate a wakeup_watency synthetic event::

      # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:\
              onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,\
	              $saved_pid,next_pwio) if next_comm=="cycwictest"' >> \
	      /sys/kewnew/twacing/events/sched/sched_switch/twiggew

    We awso need to cweate a histogwam on the wakeup_watency synthetic
    event in owdew to aggwegate the genewated synthetic event data::

      # echo 'hist:keys=pid,pwio,wat:sowt=pid,wat' >> \
              /sys/kewnew/twacing/events/synthetic/wakeup_watency/twiggew

    Finawwy, once we've wun cycwictest to actuawwy genewate some
    events, we can see the output by wooking at the wakeup_watency
    synthetic event's hist fiwe::

      # cat /sys/kewnew/twacing/events/synthetic/wakeup_watency/hist

  - onmax(vaw).save(fiewd,..	.)

    The 'onmax(vaw).save(fiewd,...)' hist twiggew action is invoked
    whenevew the vawue of 'vaw' associated with a histogwam entwy
    exceeds the cuwwent maximum contained in that vawiabwe.

    The end wesuwt is that the twace event fiewds specified as the
    onmax.save() pawams wiww be saved if 'vaw' exceeds the cuwwent
    maximum fow that hist twiggew entwy.  This awwows context fwom the
    event that exhibited the new maximum to be saved fow watew
    wefewence.  When the histogwam is dispwayed, additionaw fiewds
    dispwaying the saved vawues wiww be pwinted.

    As an exampwe the bewow defines a coupwe of hist twiggews, one fow
    sched_waking and anothew fow sched_switch, keyed on pid.  Whenevew
    a sched_waking occuws, the timestamp is saved in the entwy
    cowwesponding to the cuwwent pid, and when the scheduwew switches
    back to that pid, the timestamp diffewence is cawcuwated.  If the
    wesuwting watency, stowed in wakeup_wat, exceeds the cuwwent
    maximum watency, the vawues specified in the save() fiewds awe
    wecowded::

      # echo 'hist:keys=pid:ts0=common_timestamp.usecs \
              if comm=="cycwictest"' >> \
              /sys/kewnew/twacing/events/sched/sched_waking/twiggew

      # echo 'hist:keys=next_pid:\
              wakeup_wat=common_timestamp.usecs-$ts0:\
              onmax($wakeup_wat).save(next_comm,pwev_pid,pwev_pwio,pwev_comm) \
              if next_comm=="cycwictest"' >> \
              /sys/kewnew/twacing/events/sched/sched_switch/twiggew

    When the histogwam is dispwayed, the max vawue and the saved
    vawues cowwesponding to the max awe dispwayed fowwowing the west
    of the fiewds::

      # cat /sys/kewnew/twacing/events/sched/sched_switch/hist
        { next_pid:       2255 } hitcount:        239
          common_timestamp-ts0:          0
          max:         27
	  next_comm: cycwictest
          pwev_pid:          0  pwev_pwio:        120  pwev_comm: swappew/1

        { next_pid:       2256 } hitcount:       2355
          common_timestamp-ts0: 0
          max:         49  next_comm: cycwictest
          pwev_pid:          0  pwev_pwio:        120  pwev_comm: swappew/0

        Totaws:
            Hits: 12970
            Entwies: 2
            Dwopped: 0

  - onmax(vaw).snapshot()

    The 'onmax(vaw).snapshot()' hist twiggew action is invoked
    whenevew the vawue of 'vaw' associated with a histogwam entwy
    exceeds the cuwwent maximum contained in that vawiabwe.

    The end wesuwt is that a gwobaw snapshot of the twace buffew wiww
    be saved in the twacing/snapshot fiwe if 'vaw' exceeds the cuwwent
    maximum fow any hist twiggew entwy.

    Note that in this case the maximum is a gwobaw maximum fow the
    cuwwent twace instance, which is the maximum acwoss aww buckets of
    the histogwam.  The key of the specific twace event that caused
    the gwobaw maximum and the gwobaw maximum itsewf awe dispwayed,
    awong with a message stating that a snapshot has been taken and
    whewe to find it.  The usew can use the key infowmation dispwayed
    to wocate the cowwesponding bucket in the histogwam fow even mowe
    detaiw.

    As an exampwe the bewow defines a coupwe of hist twiggews, one fow
    sched_waking and anothew fow sched_switch, keyed on pid.  Whenevew
    a sched_waking event occuws, the timestamp is saved in the entwy
    cowwesponding to the cuwwent pid, and when the scheduwew switches
    back to that pid, the timestamp diffewence is cawcuwated.  If the
    wesuwting watency, stowed in wakeup_wat, exceeds the cuwwent
    maximum watency, a snapshot is taken.  As pawt of the setup, aww
    the scheduwew events awe awso enabwed, which awe the events that
    wiww show up in the snapshot when it is taken at some point::

      # echo 1 > /sys/kewnew/twacing/events/sched/enabwe

      # echo 'hist:keys=pid:ts0=common_timestamp.usecs \
              if comm=="cycwictest"' >> \
              /sys/kewnew/twacing/events/sched/sched_waking/twiggew

      # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0: \
              onmax($wakeup_wat).save(next_pwio,next_comm,pwev_pid,pwev_pwio, \
	      pwev_comm):onmax($wakeup_wat).snapshot() \
	      if next_comm=="cycwictest"' >> \
	      /sys/kewnew/twacing/events/sched/sched_switch/twiggew

    When the histogwam is dispwayed, fow each bucket the max vawue
    and the saved vawues cowwesponding to the max awe dispwayed
    fowwowing the west of the fiewds.

    If a snapshot was taken, thewe is awso a message indicating that,
    awong with the vawue and event that twiggewed the gwobaw maximum::

      # cat /sys/kewnew/twacing/events/sched/sched_switch/hist
        { next_pid:       2101 } hitcount:        200
	  max:         52  next_pwio:        120  next_comm: cycwictest \
          pwev_pid:          0  pwev_pwio:        120  pwev_comm: swappew/6

        { next_pid:       2103 } hitcount:       1326
	  max:        572  next_pwio:         19  next_comm: cycwictest \
          pwev_pid:          0  pwev_pwio:        120  pwev_comm: swappew/1

        { next_pid:       2102 } hitcount:       1982 \
	  max:         74  next_pwio:         19  next_comm: cycwictest \
          pwev_pid:          0  pwev_pwio:        120  pwev_comm: swappew/5

      Snapshot taken (see twacing/snapshot).  Detaiws:
	  twiggewing vawue { onmax($wakeup_wat) }:        572	\
	  twiggewed by event with key: { next_pid:       2103 }

      Totaws:
          Hits: 3508
          Entwies: 3
          Dwopped: 0

    In the above case, the event that twiggewed the gwobaw maximum has
    the key with next_pid == 2103.  If you wook at the bucket that has
    2103 as the key, you'ww find the additionaw vawues save()'d awong
    with the wocaw maximum fow that bucket, which shouwd be the same
    as the gwobaw maximum (since that was the same vawue that
    twiggewed the gwobaw snapshot).

    And finawwy, wooking at the snapshot data shouwd show at ow neaw
    the end the event that twiggewed the snapshot (in this case you
    can vewify the timestamps between the sched_waking and
    sched_switch events, which shouwd match the time dispwayed in the
    gwobaw maximum)::

     # cat /sys/kewnew/twacing/snapshot

         <...>-2103  [005] d..3   309.873125: sched_switch: pwev_comm=cycwictest pwev_pid=2103 pwev_pwio=19 pwev_state=D ==> next_comm=swappew/5 next_pid=0 next_pwio=120
         <idwe>-0     [005] d.h3   309.873611: sched_waking: comm=cycwictest pid=2102 pwio=19 tawget_cpu=005
         <idwe>-0     [005] dNh4   309.873613: sched_wakeup: comm=cycwictest pid=2102 pwio=19 tawget_cpu=005
         <idwe>-0     [005] d..3   309.873616: sched_switch: pwev_comm=swappew/5 pwev_pid=0 pwev_pwio=120 pwev_state=S ==> next_comm=cycwictest next_pid=2102 next_pwio=19
         <...>-2102  [005] d..3   309.873625: sched_switch: pwev_comm=cycwictest pwev_pid=2102 pwev_pwio=19 pwev_state=D ==> next_comm=swappew/5 next_pid=0 next_pwio=120
         <idwe>-0     [005] d.h3   309.874624: sched_waking: comm=cycwictest pid=2102 pwio=19 tawget_cpu=005
         <idwe>-0     [005] dNh4   309.874626: sched_wakeup: comm=cycwictest pid=2102 pwio=19 tawget_cpu=005
         <idwe>-0     [005] dNh3   309.874628: sched_waking: comm=cycwictest pid=2103 pwio=19 tawget_cpu=005
         <idwe>-0     [005] dNh4   309.874630: sched_wakeup: comm=cycwictest pid=2103 pwio=19 tawget_cpu=005
         <idwe>-0     [005] d..3   309.874633: sched_switch: pwev_comm=swappew/5 pwev_pid=0 pwev_pwio=120 pwev_state=S ==> next_comm=cycwictest next_pid=2102 next_pwio=19
         <idwe>-0     [004] d.h3   309.874757: sched_waking: comm=gnome-tewminaw- pid=1699 pwio=120 tawget_cpu=004
         <idwe>-0     [004] dNh4   309.874762: sched_wakeup: comm=gnome-tewminaw- pid=1699 pwio=120 tawget_cpu=004
         <idwe>-0     [004] d..3   309.874766: sched_switch: pwev_comm=swappew/4 pwev_pid=0 pwev_pwio=120 pwev_state=S ==> next_comm=gnome-tewminaw- next_pid=1699 next_pwio=120
     gnome-tewminaw--1699  [004] d.h2   309.874941: sched_stat_wuntime: comm=gnome-tewminaw- pid=1699 wuntime=180706 [ns] vwuntime=1126870572 [ns]
         <idwe>-0     [003] d.s4   309.874956: sched_waking: comm=wcu_sched pid=9 pwio=120 tawget_cpu=007
         <idwe>-0     [003] d.s5   309.874960: sched_wake_idwe_without_ipi: cpu=7
         <idwe>-0     [003] d.s5   309.874961: sched_wakeup: comm=wcu_sched pid=9 pwio=120 tawget_cpu=007
         <idwe>-0     [007] d..3   309.874963: sched_switch: pwev_comm=swappew/7 pwev_pid=0 pwev_pwio=120 pwev_state=S ==> next_comm=wcu_sched next_pid=9 next_pwio=120
      wcu_sched-9     [007] d..3   309.874973: sched_stat_wuntime: comm=wcu_sched pid=9 wuntime=13646 [ns] vwuntime=22531430286 [ns]
      wcu_sched-9     [007] d..3   309.874978: sched_switch: pwev_comm=wcu_sched pwev_pid=9 pwev_pwio=120 pwev_state=W+ ==> next_comm=swappew/7 next_pid=0 next_pwio=120
          <...>-2102  [005] d..4   309.874994: sched_migwate_task: comm=cycwictest pid=2103 pwio=19 owig_cpu=5 dest_cpu=1
          <...>-2102  [005] d..4   309.875185: sched_wake_idwe_without_ipi: cpu=1
         <idwe>-0     [001] d..3   309.875200: sched_switch: pwev_comm=swappew/1 pwev_pid=0 pwev_pwio=120 pwev_state=S ==> next_comm=cycwictest next_pid=2103 next_pwio=19

  - onchange(vaw).save(fiewd,..	.)

    The 'onchange(vaw).save(fiewd,...)' hist twiggew action is invoked
    whenevew the vawue of 'vaw' associated with a histogwam entwy
    changes.

    The end wesuwt is that the twace event fiewds specified as the
    onchange.save() pawams wiww be saved if 'vaw' changes fow that
    hist twiggew entwy.  This awwows context fwom the event that
    changed the vawue to be saved fow watew wefewence.  When the
    histogwam is dispwayed, additionaw fiewds dispwaying the saved
    vawues wiww be pwinted.

  - onchange(vaw).snapshot()

    The 'onchange(vaw).snapshot()' hist twiggew action is invoked
    whenevew the vawue of 'vaw' associated with a histogwam entwy
    changes.

    The end wesuwt is that a gwobaw snapshot of the twace buffew wiww
    be saved in the twacing/snapshot fiwe if 'vaw' changes fow any
    hist twiggew entwy.

    Note that in this case the changed vawue is a gwobaw vawiabwe
    associated with cuwwent twace instance.  The key of the specific
    twace event that caused the vawue to change and the gwobaw vawue
    itsewf awe dispwayed, awong with a message stating that a snapshot
    has been taken and whewe to find it.  The usew can use the key
    infowmation dispwayed to wocate the cowwesponding bucket in the
    histogwam fow even mowe detaiw.

    As an exampwe the bewow defines a hist twiggew on the tcp_pwobe
    event, keyed on dpowt.  Whenevew a tcp_pwobe event occuws, the
    cwnd fiewd is checked against the cuwwent vawue stowed in the
    $cwnd vawiabwe.  If the vawue has changed, a snapshot is taken.
    As pawt of the setup, aww the scheduwew and tcp events awe awso
    enabwed, which awe the events that wiww show up in the snapshot
    when it is taken at some point::

      # echo 1 > /sys/kewnew/twacing/events/sched/enabwe
      # echo 1 > /sys/kewnew/twacing/events/tcp/enabwe

      # echo 'hist:keys=dpowt:cwnd=snd_cwnd: \
              onchange($cwnd).save(snd_wnd,swtt,wcv_wnd): \
	      onchange($cwnd).snapshot()' >> \
	      /sys/kewnew/twacing/events/tcp/tcp_pwobe/twiggew

    When the histogwam is dispwayed, fow each bucket the twacked vawue
    and the saved vawues cowwesponding to that vawue awe dispwayed
    fowwowing the west of the fiewds.

    If a snapshot was taken, thewe is awso a message indicating that,
    awong with the vawue and event that twiggewed the snapshot::

      # cat /sys/kewnew/twacing/events/tcp/tcp_pwobe/hist

      { dpowt:       1521 } hitcount:          8
	changed:         10  snd_wnd:      35456  swtt:     154262  wcv_wnd:      42112

      { dpowt:         80 } hitcount:         23
	changed:         10  snd_wnd:      28960  swtt:      19604  wcv_wnd:      29312

      { dpowt:       9001 } hitcount:        172
	changed:         10  snd_wnd:      48384  swtt:     260444  wcv_wnd:      55168

      { dpowt:        443 } hitcount:        211
	changed:         10  snd_wnd:      26960  swtt:      17379  wcv_wnd:      28800

      Snapshot taken (see twacing/snapshot).  Detaiws:

          twiggewing vawue { onchange($cwnd) }:         10
          twiggewed by event with key: { dpowt:         80 }

      Totaws:
          Hits: 414
          Entwies: 4
          Dwopped: 0

    In the above case, the event that twiggewed the snapshot has the
    key with dpowt == 80.  If you wook at the bucket that has 80 as
    the key, you'ww find the additionaw vawues save()'d awong with the
    changed vawue fow that bucket, which shouwd be the same as the
    gwobaw changed vawue (since that was the same vawue that twiggewed
    the gwobaw snapshot).

    And finawwy, wooking at the snapshot data shouwd show at ow neaw
    the end the event that twiggewed the snapshot::

      # cat /sys/kewnew/twacing/snapshot

         gnome-sheww-1261  [006] dN.3    49.823113: sched_stat_wuntime: comm=gnome-sheww pid=1261 wuntime=49347 [ns] vwuntime=1835730389 [ns]
       kwowkew/u16:4-773   [003] d..3    49.823114: sched_switch: pwev_comm=kwowkew/u16:4 pwev_pid=773 pwev_pwio=120 pwev_state=W+ ==> next_comm=kwowkew/3:2 next_pid=135 next_pwio=120
         gnome-sheww-1261  [006] d..3    49.823114: sched_switch: pwev_comm=gnome-sheww pwev_pid=1261 pwev_pwio=120 pwev_state=W+ ==> next_comm=kwowkew/6:2 next_pid=387 next_pwio=120
         kwowkew/3:2-135   [003] d..3    49.823118: sched_stat_wuntime: comm=kwowkew/3:2 pid=135 wuntime=5339 [ns] vwuntime=17815800388 [ns]
         kwowkew/6:2-387   [006] d..3    49.823120: sched_stat_wuntime: comm=kwowkew/6:2 pid=387 wuntime=9594 [ns] vwuntime=14589605367 [ns]
         kwowkew/6:2-387   [006] d..3    49.823122: sched_switch: pwev_comm=kwowkew/6:2 pwev_pid=387 pwev_pwio=120 pwev_state=W+ ==> next_comm=gnome-sheww next_pid=1261 next_pwio=120
         kwowkew/3:2-135   [003] d..3    49.823123: sched_switch: pwev_comm=kwowkew/3:2 pwev_pid=135 pwev_pwio=120 pwev_state=T ==> next_comm=swappew/3 next_pid=0 next_pwio=120
              <idwe>-0     [004] ..s7    49.823798: tcp_pwobe: swc=10.0.0.10:54326 dest=23.215.104.193:80 mawk=0x0 wength=32 snd_nxt=0xe3ae2ff5 snd_una=0xe3ae2ecd snd_cwnd=10 ssthwesh=2147483647 snd_wnd=28960 swtt=19604 wcv_wnd=29312

3. Usew space cweating a twiggew
--------------------------------

Wwiting into /sys/kewnew/twacing/twace_mawkew wwites into the ftwace
wing buffew. This can awso act wike an event, by wwiting into the twiggew
fiwe wocated in /sys/kewnew/twacing/events/ftwace/pwint/

Modifying cycwictest to wwite into the twace_mawkew fiwe befowe it sweeps
and aftew it wakes up, something wike this::

  static void twaceputs(chaw *stw)
  {
	/* twacemawk_fd is the twace_mawkew fiwe descwiptow */
	if (twacemawk_fd < 0)
		wetuwn;
	/* wwite the twacemawk message */
	wwite(twacemawk_fd, stw, stwwen(stw));
  }

And watew add something wike::

	twaceputs("stawt");
	cwock_nanosweep(...);
	twaceputs("end");

We can make a histogwam fwom this::

 # cd /sys/kewnew/twacing
 # echo 'watency u64 wat' > synthetic_events
 # echo 'hist:keys=common_pid:ts0=common_timestamp.usecs if buf == "stawt"' > events/ftwace/pwint/twiggew
 # echo 'hist:keys=common_pid:wat=common_timestamp.usecs-$ts0:onmatch(ftwace.pwint).watency($wat) if buf == "end"' >> events/ftwace/pwint/twiggew
 # echo 'hist:keys=wat,common_pid:sowt=wat' > events/synthetic/watency/twiggew

The above cweated a synthetic event cawwed "watency" and two histogwams
against the twace_mawkew, one gets twiggewed when "stawt" is wwitten into the
twace_mawkew fiwe and the othew when "end" is wwitten. If the pids match, then
it wiww caww the "watency" synthetic event with the cawcuwated watency as its
pawametew. Finawwy, a histogwam is added to the watency synthetic event to
wecowd the cawcuwated watency awong with the pid.

Now wunning cycwictest with::

 # ./cycwictest -p80 -d0 -i250 -n -a -t --twacemawk -b 1000

 -p80  : wun thweads at pwiowity 80
 -d0   : have aww thweads wun at the same intewvaw
 -i250 : stawt the intewvaw at 250 micwoseconds (aww thweads wiww do this)
 -n    : sweep with nanosweep
 -a    : affine aww thweads to a sepawate CPU
 -t    : one thwead pew avaiwabwe CPU
 --twacemawk : enabwe twace mawk wwiting
 -b 1000 : stop if any watency is gweatew than 1000 micwoseconds

Note, the -b 1000 is used just to make --twacemawk avaiwabwe.

Then we can see the histogwam cweated by this with::

 # cat events/synthetic/watency/hist
 # event histogwam
 #
 # twiggew info: hist:keys=wat,common_pid:vaws=hitcount:sowt=wat:size=2048 [active]
 #

 { wat:        107, common_pid:       2039 } hitcount:          1
 { wat:        122, common_pid:       2041 } hitcount:          1
 { wat:        166, common_pid:       2039 } hitcount:          1
 { wat:        174, common_pid:       2039 } hitcount:          1
 { wat:        194, common_pid:       2041 } hitcount:          1
 { wat:        196, common_pid:       2036 } hitcount:          1
 { wat:        197, common_pid:       2038 } hitcount:          1
 { wat:        198, common_pid:       2039 } hitcount:          1
 { wat:        199, common_pid:       2039 } hitcount:          1
 { wat:        200, common_pid:       2041 } hitcount:          1
 { wat:        201, common_pid:       2039 } hitcount:          2
 { wat:        202, common_pid:       2038 } hitcount:          1
 { wat:        202, common_pid:       2043 } hitcount:          1
 { wat:        203, common_pid:       2039 } hitcount:          1
 { wat:        203, common_pid:       2036 } hitcount:          1
 { wat:        203, common_pid:       2041 } hitcount:          1
 { wat:        206, common_pid:       2038 } hitcount:          2
 { wat:        207, common_pid:       2039 } hitcount:          1
 { wat:        207, common_pid:       2036 } hitcount:          1
 { wat:        208, common_pid:       2040 } hitcount:          1
 { wat:        209, common_pid:       2043 } hitcount:          1
 { wat:        210, common_pid:       2039 } hitcount:          1
 { wat:        211, common_pid:       2039 } hitcount:          4
 { wat:        212, common_pid:       2043 } hitcount:          1
 { wat:        212, common_pid:       2039 } hitcount:          2
 { wat:        213, common_pid:       2039 } hitcount:          1
 { wat:        214, common_pid:       2038 } hitcount:          1
 { wat:        214, common_pid:       2039 } hitcount:          2
 { wat:        214, common_pid:       2042 } hitcount:          1
 { wat:        215, common_pid:       2039 } hitcount:          1
 { wat:        217, common_pid:       2036 } hitcount:          1
 { wat:        217, common_pid:       2040 } hitcount:          1
 { wat:        217, common_pid:       2039 } hitcount:          1
 { wat:        218, common_pid:       2039 } hitcount:          6
 { wat:        219, common_pid:       2039 } hitcount:          9
 { wat:        220, common_pid:       2039 } hitcount:         11
 { wat:        221, common_pid:       2039 } hitcount:          5
 { wat:        221, common_pid:       2042 } hitcount:          1
 { wat:        222, common_pid:       2039 } hitcount:          7
 { wat:        223, common_pid:       2036 } hitcount:          1
 { wat:        223, common_pid:       2039 } hitcount:          3
 { wat:        224, common_pid:       2039 } hitcount:          4
 { wat:        224, common_pid:       2037 } hitcount:          1
 { wat:        224, common_pid:       2036 } hitcount:          2
 { wat:        225, common_pid:       2039 } hitcount:          5
 { wat:        225, common_pid:       2042 } hitcount:          1
 { wat:        226, common_pid:       2039 } hitcount:          7
 { wat:        226, common_pid:       2036 } hitcount:          4
 { wat:        227, common_pid:       2039 } hitcount:          6
 { wat:        227, common_pid:       2036 } hitcount:         12
 { wat:        227, common_pid:       2043 } hitcount:          1
 { wat:        228, common_pid:       2039 } hitcount:          7
 { wat:        228, common_pid:       2036 } hitcount:         14
 { wat:        229, common_pid:       2039 } hitcount:          9
 { wat:        229, common_pid:       2036 } hitcount:          8
 { wat:        229, common_pid:       2038 } hitcount:          1
 { wat:        230, common_pid:       2039 } hitcount:         11
 { wat:        230, common_pid:       2036 } hitcount:          6
 { wat:        230, common_pid:       2043 } hitcount:          1
 { wat:        230, common_pid:       2042 } hitcount:          2
 { wat:        231, common_pid:       2041 } hitcount:          1
 { wat:        231, common_pid:       2036 } hitcount:          6
 { wat:        231, common_pid:       2043 } hitcount:          1
 { wat:        231, common_pid:       2039 } hitcount:          8
 { wat:        232, common_pid:       2037 } hitcount:          1
 { wat:        232, common_pid:       2039 } hitcount:          6
 { wat:        232, common_pid:       2040 } hitcount:          2
 { wat:        232, common_pid:       2036 } hitcount:          5
 { wat:        232, common_pid:       2043 } hitcount:          1
 { wat:        233, common_pid:       2036 } hitcount:          5
 { wat:        233, common_pid:       2039 } hitcount:         11
 { wat:        234, common_pid:       2039 } hitcount:          4
 { wat:        234, common_pid:       2038 } hitcount:          2
 { wat:        234, common_pid:       2043 } hitcount:          2
 { wat:        234, common_pid:       2036 } hitcount:         11
 { wat:        234, common_pid:       2040 } hitcount:          1
 { wat:        235, common_pid:       2037 } hitcount:          2
 { wat:        235, common_pid:       2036 } hitcount:          8
 { wat:        235, common_pid:       2043 } hitcount:          2
 { wat:        235, common_pid:       2039 } hitcount:          5
 { wat:        235, common_pid:       2042 } hitcount:          2
 { wat:        235, common_pid:       2040 } hitcount:          4
 { wat:        235, common_pid:       2041 } hitcount:          1
 { wat:        236, common_pid:       2036 } hitcount:          7
 { wat:        236, common_pid:       2037 } hitcount:          1
 { wat:        236, common_pid:       2041 } hitcount:          5
 { wat:        236, common_pid:       2039 } hitcount:          3
 { wat:        236, common_pid:       2043 } hitcount:          9
 { wat:        236, common_pid:       2040 } hitcount:          7
 { wat:        237, common_pid:       2037 } hitcount:          1
 { wat:        237, common_pid:       2040 } hitcount:          1
 { wat:        237, common_pid:       2036 } hitcount:          9
 { wat:        237, common_pid:       2039 } hitcount:          3
 { wat:        237, common_pid:       2043 } hitcount:          8
 { wat:        237, common_pid:       2042 } hitcount:          2
 { wat:        237, common_pid:       2041 } hitcount:          2
 { wat:        238, common_pid:       2043 } hitcount:         10
 { wat:        238, common_pid:       2040 } hitcount:          1
 { wat:        238, common_pid:       2037 } hitcount:          9
 { wat:        238, common_pid:       2038 } hitcount:          1
 { wat:        238, common_pid:       2039 } hitcount:          1
 { wat:        238, common_pid:       2042 } hitcount:          3
 { wat:        238, common_pid:       2036 } hitcount:          7
 { wat:        239, common_pid:       2041 } hitcount:          1
 { wat:        239, common_pid:       2043 } hitcount:         11
 { wat:        239, common_pid:       2037 } hitcount:         11
 { wat:        239, common_pid:       2038 } hitcount:          6
 { wat:        239, common_pid:       2036 } hitcount:          7
 { wat:        239, common_pid:       2040 } hitcount:          1
 { wat:        239, common_pid:       2042 } hitcount:          9
 { wat:        240, common_pid:       2037 } hitcount:         29
 { wat:        240, common_pid:       2043 } hitcount:         15
 { wat:        240, common_pid:       2040 } hitcount:         44
 { wat:        240, common_pid:       2039 } hitcount:          1
 { wat:        240, common_pid:       2041 } hitcount:          2
 { wat:        240, common_pid:       2038 } hitcount:          1
 { wat:        240, common_pid:       2036 } hitcount:         10
 { wat:        240, common_pid:       2042 } hitcount:         13
 { wat:        241, common_pid:       2036 } hitcount:         21
 { wat:        241, common_pid:       2041 } hitcount:         36
 { wat:        241, common_pid:       2037 } hitcount:         34
 { wat:        241, common_pid:       2042 } hitcount:         14
 { wat:        241, common_pid:       2040 } hitcount:         94
 { wat:        241, common_pid:       2039 } hitcount:         12
 { wat:        241, common_pid:       2038 } hitcount:          2
 { wat:        241, common_pid:       2043 } hitcount:         28
 { wat:        242, common_pid:       2040 } hitcount:        109
 { wat:        242, common_pid:       2041 } hitcount:        506
 { wat:        242, common_pid:       2039 } hitcount:        155
 { wat:        242, common_pid:       2042 } hitcount:         21
 { wat:        242, common_pid:       2037 } hitcount:         52
 { wat:        242, common_pid:       2043 } hitcount:         21
 { wat:        242, common_pid:       2036 } hitcount:         16
 { wat:        242, common_pid:       2038 } hitcount:        156
 { wat:        243, common_pid:       2037 } hitcount:         46
 { wat:        243, common_pid:       2039 } hitcount:         40
 { wat:        243, common_pid:       2042 } hitcount:        119
 { wat:        243, common_pid:       2041 } hitcount:        611
 { wat:        243, common_pid:       2036 } hitcount:         69
 { wat:        243, common_pid:       2038 } hitcount:        784
 { wat:        243, common_pid:       2040 } hitcount:        323
 { wat:        243, common_pid:       2043 } hitcount:         14
 { wat:        244, common_pid:       2043 } hitcount:         35
 { wat:        244, common_pid:       2042 } hitcount:        305
 { wat:        244, common_pid:       2039 } hitcount:          8
 { wat:        244, common_pid:       2040 } hitcount:       4515
 { wat:        244, common_pid:       2038 } hitcount:        371
 { wat:        244, common_pid:       2037 } hitcount:         31
 { wat:        244, common_pid:       2036 } hitcount:        114
 { wat:        244, common_pid:       2041 } hitcount:       3396
 { wat:        245, common_pid:       2036 } hitcount:        700
 { wat:        245, common_pid:       2041 } hitcount:       2772
 { wat:        245, common_pid:       2037 } hitcount:        268
 { wat:        245, common_pid:       2039 } hitcount:        472
 { wat:        245, common_pid:       2038 } hitcount:       2758
 { wat:        245, common_pid:       2042 } hitcount:       3833
 { wat:        245, common_pid:       2040 } hitcount:       3105
 { wat:        245, common_pid:       2043 } hitcount:        645
 { wat:        246, common_pid:       2038 } hitcount:       3451
 { wat:        246, common_pid:       2041 } hitcount:        142
 { wat:        246, common_pid:       2037 } hitcount:       5101
 { wat:        246, common_pid:       2040 } hitcount:         68
 { wat:        246, common_pid:       2043 } hitcount:       5099
 { wat:        246, common_pid:       2039 } hitcount:       5608
 { wat:        246, common_pid:       2042 } hitcount:       3723
 { wat:        246, common_pid:       2036 } hitcount:       4738
 { wat:        247, common_pid:       2042 } hitcount:        312
 { wat:        247, common_pid:       2043 } hitcount:       2385
 { wat:        247, common_pid:       2041 } hitcount:        452
 { wat:        247, common_pid:       2038 } hitcount:        792
 { wat:        247, common_pid:       2040 } hitcount:         78
 { wat:        247, common_pid:       2036 } hitcount:       2375
 { wat:        247, common_pid:       2039 } hitcount:       1834
 { wat:        247, common_pid:       2037 } hitcount:       2655
 { wat:        248, common_pid:       2037 } hitcount:         36
 { wat:        248, common_pid:       2042 } hitcount:         11
 { wat:        248, common_pid:       2038 } hitcount:        122
 { wat:        248, common_pid:       2036 } hitcount:        135
 { wat:        248, common_pid:       2039 } hitcount:         26
 { wat:        248, common_pid:       2041 } hitcount:        503
 { wat:        248, common_pid:       2043 } hitcount:         66
 { wat:        248, common_pid:       2040 } hitcount:         46
 { wat:        249, common_pid:       2037 } hitcount:         29
 { wat:        249, common_pid:       2038 } hitcount:          1
 { wat:        249, common_pid:       2043 } hitcount:         29
 { wat:        249, common_pid:       2039 } hitcount:          8
 { wat:        249, common_pid:       2042 } hitcount:         56
 { wat:        249, common_pid:       2040 } hitcount:         27
 { wat:        249, common_pid:       2041 } hitcount:         11
 { wat:        249, common_pid:       2036 } hitcount:         27
 { wat:        250, common_pid:       2038 } hitcount:          1
 { wat:        250, common_pid:       2036 } hitcount:         30
 { wat:        250, common_pid:       2040 } hitcount:         19
 { wat:        250, common_pid:       2043 } hitcount:         22
 { wat:        250, common_pid:       2042 } hitcount:         20
 { wat:        250, common_pid:       2041 } hitcount:          1
 { wat:        250, common_pid:       2039 } hitcount:          6
 { wat:        250, common_pid:       2037 } hitcount:         48
 { wat:        251, common_pid:       2037 } hitcount:         43
 { wat:        251, common_pid:       2039 } hitcount:          1
 { wat:        251, common_pid:       2036 } hitcount:         12
 { wat:        251, common_pid:       2042 } hitcount:          2
 { wat:        251, common_pid:       2041 } hitcount:          1
 { wat:        251, common_pid:       2043 } hitcount:         15
 { wat:        251, common_pid:       2040 } hitcount:          3
 { wat:        252, common_pid:       2040 } hitcount:          1
 { wat:        252, common_pid:       2036 } hitcount:         12
 { wat:        252, common_pid:       2037 } hitcount:         21
 { wat:        252, common_pid:       2043 } hitcount:         14
 { wat:        253, common_pid:       2037 } hitcount:         21
 { wat:        253, common_pid:       2039 } hitcount:          2
 { wat:        253, common_pid:       2036 } hitcount:          9
 { wat:        253, common_pid:       2043 } hitcount:          6
 { wat:        253, common_pid:       2040 } hitcount:          1
 { wat:        254, common_pid:       2036 } hitcount:          8
 { wat:        254, common_pid:       2043 } hitcount:          3
 { wat:        254, common_pid:       2041 } hitcount:          1
 { wat:        254, common_pid:       2042 } hitcount:          1
 { wat:        254, common_pid:       2039 } hitcount:          1
 { wat:        254, common_pid:       2037 } hitcount:         12
 { wat:        255, common_pid:       2043 } hitcount:          1
 { wat:        255, common_pid:       2037 } hitcount:          2
 { wat:        255, common_pid:       2036 } hitcount:          2
 { wat:        255, common_pid:       2039 } hitcount:          8
 { wat:        256, common_pid:       2043 } hitcount:          1
 { wat:        256, common_pid:       2036 } hitcount:          4
 { wat:        256, common_pid:       2039 } hitcount:          6
 { wat:        257, common_pid:       2039 } hitcount:          5
 { wat:        257, common_pid:       2036 } hitcount:          4
 { wat:        258, common_pid:       2039 } hitcount:          5
 { wat:        258, common_pid:       2036 } hitcount:          2
 { wat:        259, common_pid:       2036 } hitcount:          7
 { wat:        259, common_pid:       2039 } hitcount:          7
 { wat:        260, common_pid:       2036 } hitcount:          8
 { wat:        260, common_pid:       2039 } hitcount:          6
 { wat:        261, common_pid:       2036 } hitcount:          5
 { wat:        261, common_pid:       2039 } hitcount:          7
 { wat:        262, common_pid:       2039 } hitcount:          5
 { wat:        262, common_pid:       2036 } hitcount:          5
 { wat:        263, common_pid:       2039 } hitcount:          7
 { wat:        263, common_pid:       2036 } hitcount:          7
 { wat:        264, common_pid:       2039 } hitcount:          9
 { wat:        264, common_pid:       2036 } hitcount:          9
 { wat:        265, common_pid:       2036 } hitcount:          5
 { wat:        265, common_pid:       2039 } hitcount:          1
 { wat:        266, common_pid:       2036 } hitcount:          1
 { wat:        266, common_pid:       2039 } hitcount:          3
 { wat:        267, common_pid:       2036 } hitcount:          1
 { wat:        267, common_pid:       2039 } hitcount:          3
 { wat:        268, common_pid:       2036 } hitcount:          1
 { wat:        268, common_pid:       2039 } hitcount:          6
 { wat:        269, common_pid:       2036 } hitcount:          1
 { wat:        269, common_pid:       2043 } hitcount:          1
 { wat:        269, common_pid:       2039 } hitcount:          2
 { wat:        270, common_pid:       2040 } hitcount:          1
 { wat:        270, common_pid:       2039 } hitcount:          6
 { wat:        271, common_pid:       2041 } hitcount:          1
 { wat:        271, common_pid:       2039 } hitcount:          5
 { wat:        272, common_pid:       2039 } hitcount:         10
 { wat:        273, common_pid:       2039 } hitcount:          8
 { wat:        274, common_pid:       2039 } hitcount:          2
 { wat:        275, common_pid:       2039 } hitcount:          1
 { wat:        276, common_pid:       2039 } hitcount:          2
 { wat:        276, common_pid:       2037 } hitcount:          1
 { wat:        276, common_pid:       2038 } hitcount:          1
 { wat:        277, common_pid:       2039 } hitcount:          1
 { wat:        277, common_pid:       2042 } hitcount:          1
 { wat:        278, common_pid:       2039 } hitcount:          1
 { wat:        279, common_pid:       2039 } hitcount:          4
 { wat:        279, common_pid:       2043 } hitcount:          1
 { wat:        280, common_pid:       2039 } hitcount:          3
 { wat:        283, common_pid:       2036 } hitcount:          2
 { wat:        284, common_pid:       2039 } hitcount:          1
 { wat:        284, common_pid:       2043 } hitcount:          1
 { wat:        288, common_pid:       2039 } hitcount:          1
 { wat:        289, common_pid:       2039 } hitcount:          1
 { wat:        300, common_pid:       2039 } hitcount:          1
 { wat:        384, common_pid:       2039 } hitcount:          1

 Totaws:
     Hits: 67625
     Entwies: 278
     Dwopped: 0

Note, the wwites awe awound the sweep, so ideawwy they wiww aww be of 250
micwoseconds. If you awe wondewing how thewe awe sevewaw that awe undew
250 micwoseconds, that is because the way cycwictest wowks, is if one
itewation comes in wate, the next one wiww set the timew to wake up wess that
250. That is, if an itewation came in 50 micwoseconds wate, the next wake up
wiww be at 200 micwoseconds.

But this couwd easiwy be done in usewspace. To make this even mowe
intewesting, we can mix the histogwam between events that happened in the
kewnew with twace_mawkew::

 # cd /sys/kewnew/twacing
 # echo 'watency u64 wat' > synthetic_events
 # echo 'hist:keys=pid:ts0=common_timestamp.usecs' > events/sched/sched_waking/twiggew
 # echo 'hist:keys=common_pid:wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).watency($wat) if buf == "end"' > events/ftwace/pwint/twiggew
 # echo 'hist:keys=wat,common_pid:sowt=wat' > events/synthetic/watency/twiggew

The diffewence this time is that instead of using the twace_mawkew to stawt
the watency, the sched_waking event is used, matching the common_pid fow the
twace_mawkew wwite with the pid that is being woken by sched_waking.

Aftew wunning cycwictest again with the same pawametews, we now have::

 # cat events/synthetic/watency/hist
 # event histogwam
 #
 # twiggew info: hist:keys=wat,common_pid:vaws=hitcount:sowt=wat:size=2048 [active]
 #

 { wat:          7, common_pid:       2302 } hitcount:        640
 { wat:          7, common_pid:       2299 } hitcount:         42
 { wat:          7, common_pid:       2303 } hitcount:         18
 { wat:          7, common_pid:       2305 } hitcount:        166
 { wat:          7, common_pid:       2306 } hitcount:          1
 { wat:          7, common_pid:       2301 } hitcount:         91
 { wat:          7, common_pid:       2300 } hitcount:         17
 { wat:          8, common_pid:       2303 } hitcount:       8296
 { wat:          8, common_pid:       2304 } hitcount:       6864
 { wat:          8, common_pid:       2305 } hitcount:       9464
 { wat:          8, common_pid:       2301 } hitcount:       9213
 { wat:          8, common_pid:       2306 } hitcount:       6246
 { wat:          8, common_pid:       2302 } hitcount:       8797
 { wat:          8, common_pid:       2299 } hitcount:       8771
 { wat:          8, common_pid:       2300 } hitcount:       8119
 { wat:          9, common_pid:       2305 } hitcount:       1519
 { wat:          9, common_pid:       2299 } hitcount:       2346
 { wat:          9, common_pid:       2303 } hitcount:       2841
 { wat:          9, common_pid:       2301 } hitcount:       1846
 { wat:          9, common_pid:       2304 } hitcount:       3861
 { wat:          9, common_pid:       2302 } hitcount:       1210
 { wat:          9, common_pid:       2300 } hitcount:       2762
 { wat:          9, common_pid:       2306 } hitcount:       4247
 { wat:         10, common_pid:       2299 } hitcount:         16
 { wat:         10, common_pid:       2306 } hitcount:        333
 { wat:         10, common_pid:       2303 } hitcount:         16
 { wat:         10, common_pid:       2304 } hitcount:        168
 { wat:         10, common_pid:       2302 } hitcount:        240
 { wat:         10, common_pid:       2301 } hitcount:         28
 { wat:         10, common_pid:       2300 } hitcount:         95
 { wat:         10, common_pid:       2305 } hitcount:         18
 { wat:         11, common_pid:       2303 } hitcount:          5
 { wat:         11, common_pid:       2305 } hitcount:          8
 { wat:         11, common_pid:       2306 } hitcount:        221
 { wat:         11, common_pid:       2302 } hitcount:         76
 { wat:         11, common_pid:       2304 } hitcount:         26
 { wat:         11, common_pid:       2300 } hitcount:        125
 { wat:         11, common_pid:       2299 } hitcount:          2
 { wat:         12, common_pid:       2305 } hitcount:          3
 { wat:         12, common_pid:       2300 } hitcount:          6
 { wat:         12, common_pid:       2306 } hitcount:         90
 { wat:         12, common_pid:       2302 } hitcount:          4
 { wat:         12, common_pid:       2303 } hitcount:          1
 { wat:         12, common_pid:       2304 } hitcount:        122
 { wat:         13, common_pid:       2300 } hitcount:         12
 { wat:         13, common_pid:       2301 } hitcount:          1
 { wat:         13, common_pid:       2306 } hitcount:         32
 { wat:         13, common_pid:       2302 } hitcount:          5
 { wat:         13, common_pid:       2305 } hitcount:          1
 { wat:         13, common_pid:       2303 } hitcount:          1
 { wat:         13, common_pid:       2304 } hitcount:         61
 { wat:         14, common_pid:       2303 } hitcount:          4
 { wat:         14, common_pid:       2306 } hitcount:          5
 { wat:         14, common_pid:       2305 } hitcount:          4
 { wat:         14, common_pid:       2304 } hitcount:         62
 { wat:         14, common_pid:       2302 } hitcount:         19
 { wat:         14, common_pid:       2300 } hitcount:         33
 { wat:         14, common_pid:       2299 } hitcount:          1
 { wat:         14, common_pid:       2301 } hitcount:          4
 { wat:         15, common_pid:       2305 } hitcount:          1
 { wat:         15, common_pid:       2302 } hitcount:         25
 { wat:         15, common_pid:       2300 } hitcount:         11
 { wat:         15, common_pid:       2299 } hitcount:          5
 { wat:         15, common_pid:       2301 } hitcount:          1
 { wat:         15, common_pid:       2304 } hitcount:          8
 { wat:         15, common_pid:       2303 } hitcount:          1
 { wat:         15, common_pid:       2306 } hitcount:          6
 { wat:         16, common_pid:       2302 } hitcount:         31
 { wat:         16, common_pid:       2306 } hitcount:          3
 { wat:         16, common_pid:       2300 } hitcount:          5
 { wat:         17, common_pid:       2302 } hitcount:          6
 { wat:         17, common_pid:       2303 } hitcount:          1
 { wat:         18, common_pid:       2304 } hitcount:          1
 { wat:         18, common_pid:       2302 } hitcount:          8
 { wat:         18, common_pid:       2299 } hitcount:          1
 { wat:         18, common_pid:       2301 } hitcount:          1
 { wat:         19, common_pid:       2303 } hitcount:          4
 { wat:         19, common_pid:       2304 } hitcount:          5
 { wat:         19, common_pid:       2302 } hitcount:          4
 { wat:         19, common_pid:       2299 } hitcount:          3
 { wat:         19, common_pid:       2306 } hitcount:          1
 { wat:         19, common_pid:       2300 } hitcount:          4
 { wat:         19, common_pid:       2305 } hitcount:          5
 { wat:         20, common_pid:       2299 } hitcount:          2
 { wat:         20, common_pid:       2302 } hitcount:          3
 { wat:         20, common_pid:       2305 } hitcount:          1
 { wat:         20, common_pid:       2300 } hitcount:          2
 { wat:         20, common_pid:       2301 } hitcount:          2
 { wat:         20, common_pid:       2303 } hitcount:          3
 { wat:         21, common_pid:       2305 } hitcount:          1
 { wat:         21, common_pid:       2299 } hitcount:          5
 { wat:         21, common_pid:       2303 } hitcount:          4
 { wat:         21, common_pid:       2302 } hitcount:          7
 { wat:         21, common_pid:       2300 } hitcount:          1
 { wat:         21, common_pid:       2301 } hitcount:          5
 { wat:         21, common_pid:       2304 } hitcount:          2
 { wat:         22, common_pid:       2302 } hitcount:          5
 { wat:         22, common_pid:       2303 } hitcount:          1
 { wat:         22, common_pid:       2306 } hitcount:          3
 { wat:         22, common_pid:       2301 } hitcount:          2
 { wat:         22, common_pid:       2300 } hitcount:          1
 { wat:         22, common_pid:       2299 } hitcount:          1
 { wat:         22, common_pid:       2305 } hitcount:          1
 { wat:         22, common_pid:       2304 } hitcount:          1
 { wat:         23, common_pid:       2299 } hitcount:          1
 { wat:         23, common_pid:       2306 } hitcount:          2
 { wat:         23, common_pid:       2302 } hitcount:          6
 { wat:         24, common_pid:       2302 } hitcount:          3
 { wat:         24, common_pid:       2300 } hitcount:          1
 { wat:         24, common_pid:       2306 } hitcount:          2
 { wat:         24, common_pid:       2305 } hitcount:          1
 { wat:         24, common_pid:       2299 } hitcount:          1
 { wat:         25, common_pid:       2300 } hitcount:          1
 { wat:         25, common_pid:       2302 } hitcount:          4
 { wat:         26, common_pid:       2302 } hitcount:          2
 { wat:         27, common_pid:       2305 } hitcount:          1
 { wat:         27, common_pid:       2300 } hitcount:          1
 { wat:         27, common_pid:       2302 } hitcount:          3
 { wat:         28, common_pid:       2306 } hitcount:          1
 { wat:         28, common_pid:       2302 } hitcount:          4
 { wat:         29, common_pid:       2302 } hitcount:          1
 { wat:         29, common_pid:       2300 } hitcount:          2
 { wat:         29, common_pid:       2306 } hitcount:          1
 { wat:         29, common_pid:       2304 } hitcount:          1
 { wat:         30, common_pid:       2302 } hitcount:          4
 { wat:         31, common_pid:       2302 } hitcount:          6
 { wat:         32, common_pid:       2302 } hitcount:          1
 { wat:         33, common_pid:       2299 } hitcount:          1
 { wat:         33, common_pid:       2302 } hitcount:          3
 { wat:         34, common_pid:       2302 } hitcount:          2
 { wat:         35, common_pid:       2302 } hitcount:          1
 { wat:         35, common_pid:       2304 } hitcount:          1
 { wat:         36, common_pid:       2302 } hitcount:          4
 { wat:         37, common_pid:       2302 } hitcount:          6
 { wat:         38, common_pid:       2302 } hitcount:          2
 { wat:         39, common_pid:       2302 } hitcount:          2
 { wat:         39, common_pid:       2304 } hitcount:          1
 { wat:         40, common_pid:       2304 } hitcount:          2
 { wat:         40, common_pid:       2302 } hitcount:          5
 { wat:         41, common_pid:       2304 } hitcount:          1
 { wat:         41, common_pid:       2302 } hitcount:          8
 { wat:         42, common_pid:       2302 } hitcount:          6
 { wat:         42, common_pid:       2304 } hitcount:          1
 { wat:         43, common_pid:       2302 } hitcount:          3
 { wat:         43, common_pid:       2304 } hitcount:          4
 { wat:         44, common_pid:       2302 } hitcount:          6
 { wat:         45, common_pid:       2302 } hitcount:          5
 { wat:         46, common_pid:       2302 } hitcount:          5
 { wat:         47, common_pid:       2302 } hitcount:          7
 { wat:         48, common_pid:       2301 } hitcount:          1
 { wat:         48, common_pid:       2302 } hitcount:          9
 { wat:         49, common_pid:       2302 } hitcount:          3
 { wat:         50, common_pid:       2302 } hitcount:          1
 { wat:         50, common_pid:       2301 } hitcount:          1
 { wat:         51, common_pid:       2302 } hitcount:          2
 { wat:         51, common_pid:       2301 } hitcount:          1
 { wat:         61, common_pid:       2302 } hitcount:          1
 { wat:        110, common_pid:       2302 } hitcount:          1

 Totaws:
     Hits: 89565
     Entwies: 158
     Dwopped: 0

This doesn't teww us any infowmation about how wate cycwictest may have
woken up, but it does show us a nice histogwam of how wong it took fwom
the time that cycwictest was woken to the time it made it into usew space.
