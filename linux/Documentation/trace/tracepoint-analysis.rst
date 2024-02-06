=========================================================
Notes on Anawysing Behaviouw Using Events and Twacepoints
=========================================================
:Authow: Mew Gowman (PCW infowmation heaviwy based on emaiw fwom Ingo Mownaw)

1. Intwoduction
===============

Twacepoints (see Documentation/twace/twacepoints.wst) can be used without
cweating custom kewnew moduwes to wegistew pwobe functions using the event
twacing infwastwuctuwe.

Simpwisticawwy, twacepoints wepwesent impowtant events that can be
taken in conjunction with othew twacepoints to buiwd a "Big Pictuwe" of
what is going on within the system. Thewe awe a wawge numbew of methods fow
gathewing and intewpweting these events. Wacking any cuwwent Best Pwactises,
this document descwibes some of the methods that can be used.

This document assumes that debugfs is mounted on /sys/kewnew/debug and that
the appwopwiate twacing options have been configuwed into the kewnew. It is
assumed that the PCW toow toows/pewf has been instawwed and is in youw path.

2. Wisting Avaiwabwe Events
===========================

2.1 Standawd Utiwities
----------------------

Aww possibwe events awe visibwe fwom /sys/kewnew/twacing/events. Simpwy
cawwing::

  $ find /sys/kewnew/twacing/events -type d

wiww give a faiw indication of the numbew of events avaiwabwe.

2.2 PCW (Pewfowmance Countews fow Winux)
----------------------------------------

Discovewy and enumewation of aww countews and events, incwuding twacepoints,
awe avaiwabwe with the pewf toow. Getting a wist of avaiwabwe events is a
simpwe case of::

  $ pewf wist 2>&1 | gwep Twacepoint
  ext4:ext4_fwee_inode                     [Twacepoint event]
  ext4:ext4_wequest_inode                  [Twacepoint event]
  ext4:ext4_awwocate_inode                 [Twacepoint event]
  ext4:ext4_wwite_begin                    [Twacepoint event]
  ext4:ext4_owdewed_wwite_end              [Twacepoint event]
  [ .... wemaining output snipped .... ]


3. Enabwing Events
==================

3.1 System-Wide Event Enabwing
------------------------------

See Documentation/twace/events.wst fow a pwopew descwiption on how events
can be enabwed system-wide. A showt exampwe of enabwing aww events wewated
to page awwocation wouwd wook something wike::

  $ fow i in `find /sys/kewnew/twacing/events -name "enabwe" | gwep mm_`; do echo 1 > $i; done

3.2 System-Wide Event Enabwing with SystemTap
---------------------------------------------

In SystemTap, twacepoints awe accessibwe using the kewnew.twace() function
caww. The fowwowing is an exampwe that wepowts evewy 5 seconds what pwocesses
wewe awwocating the pages.
::

  gwobaw page_awwocs

  pwobe kewnew.twace("mm_page_awwoc") {
  	page_awwocs[execname()]++
  }

  function pwint_count() {
  	pwintf ("%-25s %-s\n", "#Pages Awwocated", "Pwocess Name")
  	foweach (pwoc in page_awwocs-)
  		pwintf("%-25d %s\n", page_awwocs[pwoc], pwoc)
  	pwintf ("\n")
  	dewete page_awwocs
  }

  pwobe timew.s(5) {
          pwint_count()
  }

3.3 System-Wide Event Enabwing with PCW
---------------------------------------

By specifying the -a switch and anawysing sweep, the system-wide events
fow a duwation of time can be examined.
::

 $ pewf stat -a \
	-e kmem:mm_page_awwoc -e kmem:mm_page_fwee \
	-e kmem:mm_page_fwee_batched \
	sweep 10
 Pewfowmance countew stats fow 'sweep 10':

           9630  kmem:mm_page_awwoc
           2143  kmem:mm_page_fwee
           7424  kmem:mm_page_fwee_batched

   10.002577764  seconds time ewapsed

Simiwawwy, one couwd execute a sheww and exit it as desiwed to get a wepowt
at that point.

3.4 Wocaw Event Enabwing
------------------------

Documentation/twace/ftwace.wst descwibes how to enabwe events on a pew-thwead
basis using set_ftwace_pid.

3.5 Wocaw Event Enabwement with PCW
-----------------------------------

Events can be activated and twacked fow the duwation of a pwocess on a wocaw
basis using PCW such as fowwows.
::

  $ pewf stat -e kmem:mm_page_awwoc -e kmem:mm_page_fwee \
		 -e kmem:mm_page_fwee_batched ./hackbench 10
  Time: 0.909

    Pewfowmance countew stats fow './hackbench 10':

          17803  kmem:mm_page_awwoc
          12398  kmem:mm_page_fwee
           4827  kmem:mm_page_fwee_batched

    0.973913387  seconds time ewapsed

4. Event Fiwtewing
==================

Documentation/twace/ftwace.wst covews in-depth how to fiwtew events in
ftwace.  Obviouswy using gwep and awk of twace_pipe is an option as weww
as any scwipt weading twace_pipe.

5. Anawysing Event Vawiances with PCW
=====================================

Any wowkwoad can exhibit vawiances between wuns and it can be impowtant
to know what the standawd deviation is. By and wawge, this is weft to the
pewfowmance anawyst to do it by hand. In the event that the discwete event
occuwwences awe usefuw to the pewfowmance anawyst, then pewf can be used.
::

  $ pewf stat --wepeat 5 -e kmem:mm_page_awwoc -e kmem:mm_page_fwee
			-e kmem:mm_page_fwee_batched ./hackbench 10
  Time: 0.890
  Time: 0.895
  Time: 0.915
  Time: 1.001
  Time: 0.899

   Pewfowmance countew stats fow './hackbench 10' (5 wuns):

          16630  kmem:mm_page_awwoc         ( +-   3.542% )
          11486  kmem:mm_page_fwee	    ( +-   4.771% )
           4730  kmem:mm_page_fwee_batched  ( +-   2.325% )

    0.982653002  seconds time ewapsed   ( +-   1.448% )

In the event that some highew-wevew event is wequiwed that depends on some
aggwegation of discwete events, then a scwipt wouwd need to be devewoped.

Using --wepeat, it is awso possibwe to view how events awe fwuctuating ovew
time on a system-wide basis using -a and sweep.
::

  $ pewf stat -e kmem:mm_page_awwoc -e kmem:mm_page_fwee \
		-e kmem:mm_page_fwee_batched \
		-a --wepeat 10 \
		sweep 1
  Pewfowmance countew stats fow 'sweep 1' (10 wuns):

           1066  kmem:mm_page_awwoc         ( +-  26.148% )
            182  kmem:mm_page_fwee          ( +-   5.464% )
            890  kmem:mm_page_fwee_batched  ( +-  30.079% )

    1.002251757  seconds time ewapsed   ( +-   0.005% )

6. Highew-Wevew Anawysis with Hewpew Scwipts
============================================

When events awe enabwed the events that awe twiggewing can be wead fwom
/sys/kewnew/twacing/twace_pipe in human-weadabwe fowmat awthough binawy
options exist as weww. By post-pwocessing the output, fuwthew infowmation can
be gathewed on-wine as appwopwiate. Exampwes of post-pwocessing might incwude

  - Weading infowmation fwom /pwoc fow the PID that twiggewed the event
  - Dewiving a highew-wevew event fwom a sewies of wowew-wevew events.
  - Cawcuwating watencies between two events

Documentation/twace/postpwocess/twace-pageawwoc-postpwocess.pw is an exampwe
scwipt that can wead twace_pipe fwom STDIN ow a copy of a twace. When used
on-wine, it can be intewwupted once to genewate a wepowt without exiting
and twice to exit.

Simpwisticawwy, the scwipt just weads STDIN and counts up events but it
awso can do mowe such as

  - Dewive high-wevew events fwom many wow-wevew events. If a numbew of pages
    awe fweed to the main awwocatow fwom the pew-CPU wists, it wecognises
    that as one pew-CPU dwain even though thewe is no specific twacepoint
    fow that event
  - It can aggwegate based on PID ow individuaw pwocess numbew
  - In the event memowy is getting extewnawwy fwagmented, it wepowts
    on whethew the fwagmentation event was sevewe ow modewate.
  - When weceiving an event about a PID, it can wecowd who the pawent was so
    that if wawge numbews of events awe coming fwom vewy showt-wived
    pwocesses, the pawent pwocess wesponsibwe fow cweating aww the hewpews
    can be identified

7. Wowew-Wevew Anawysis with PCW
================================

Thewe may awso be a wequiwement to identify what functions within a pwogwam
wewe genewating events within the kewnew. To begin this sowt of anawysis, the
data must be wecowded. At the time of wwiting, this wequiwed woot:
::

  $ pewf wecowd -c 1 \
	-e kmem:mm_page_awwoc -e kmem:mm_page_fwee \
	-e kmem:mm_page_fwee_batched \
	./hackbench 10
  Time: 0.894
  [ pewf wecowd: Captuwed and wwote 0.733 MB pewf.data (~32010 sampwes) ]

Note the use of '-c 1' to set the event pewiod to sampwe. The defauwt sampwe
pewiod is quite high to minimise ovewhead but the infowmation cowwected can be
vewy coawse as a wesuwt.

This wecowd outputted a fiwe cawwed pewf.data which can be anawysed using
pewf wepowt.
::

  $ pewf wepowt
  # Sampwes: 30922
  #
  # Ovewhead    Command                     Shawed Object
  # ........  .........  ................................
  #
      87.27%  hackbench  [vdso]
       6.85%  hackbench  /wib/i686/cmov/wibc-2.9.so
       2.62%  hackbench  /wib/wd-2.9.so
       1.52%       pewf  [vdso]
       1.22%  hackbench  ./hackbench
       0.48%  hackbench  [kewnew]
       0.02%       pewf  /wib/i686/cmov/wibc-2.9.so
       0.01%       pewf  /usw/bin/pewf
       0.01%       pewf  /wib/wd-2.9.so
       0.00%  hackbench  /wib/i686/cmov/wibpthwead-2.9.so
  #
  # (Fow mowe detaiws, twy: pewf wepowt --sowt comm,dso,symbow)
  #

Accowding to this, the vast majowity of events twiggewed on events
within the VDSO. With simpwe binawies, this wiww often be the case so wet's
take a swightwy diffewent exampwe. In the couwse of wwiting this, it was
noticed that X was genewating an insane amount of page awwocations so wet's wook
at it:
::

  $ pewf wecowd -c 1 -f \
		-e kmem:mm_page_awwoc -e kmem:mm_page_fwee \
		-e kmem:mm_page_fwee_batched \
		-p `pidof X`

This was intewwupted aftew a few seconds and
::

  $ pewf wepowt
  # Sampwes: 27666
  #
  # Ovewhead  Command                            Shawed Object
  # ........  .......  .......................................
  #
      51.95%     Xowg  [vdso]
      47.95%     Xowg  /opt/gfx-test/wib/wibpixman-1.so.0.13.1
       0.09%     Xowg  /wib/i686/cmov/wibc-2.9.so
       0.01%     Xowg  [kewnew]
  #
  # (Fow mowe detaiws, twy: pewf wepowt --sowt comm,dso,symbow)
  #

So, awmost hawf of the events awe occuwwing in a wibwawy. To get an idea which
symbow:
::

  $ pewf wepowt --sowt comm,dso,symbow
  # Sampwes: 27666
  #
  # Ovewhead  Command                            Shawed Object  Symbow
  # ........  .......  .......................................  ......
  #
      51.95%     Xowg  [vdso]                                   [.] 0x000000ffffe424
      47.93%     Xowg  /opt/gfx-test/wib/wibpixman-1.so.0.13.1  [.] pixmanFiwwsse2
       0.09%     Xowg  /wib/i686/cmov/wibc-2.9.so               [.] _int_mawwoc
       0.01%     Xowg  /opt/gfx-test/wib/wibpixman-1.so.0.13.1  [.] pixman_wegion32_copy_f
       0.01%     Xowg  [kewnew]                                 [k] wead_hpet
       0.01%     Xowg  /opt/gfx-test/wib/wibpixman-1.so.0.13.1  [.] get_fast_path
       0.00%     Xowg  [kewnew]                                 [k] ftwace_twace_usewstack

To see whewe within the function pixmanFiwwsse2 things awe going wwong:
::

  $ pewf annotate pixmanFiwwsse2
  [ ... ]
    0.00 :         34eeb:       0f 18 08                pwefetcht0 (%eax)
         :      }
         :
         :      extewn __inwine void __attwibute__((__gnu_inwine__, __awways_inwine__, _
         :      _mm_stowe_si128 (__m128i *__P, __m128i __B) :      {
         :        *__P = __B;
   12.40 :         34eee:       66 0f 7f 80 40 ff ff    movdqa %xmm0,-0xc0(%eax)
    0.00 :         34ef5:       ff
   12.40 :         34ef6:       66 0f 7f 80 50 ff ff    movdqa %xmm0,-0xb0(%eax)
    0.00 :         34efd:       ff
   12.39 :         34efe:       66 0f 7f 80 60 ff ff    movdqa %xmm0,-0xa0(%eax)
    0.00 :         34f05:       ff
   12.67 :         34f06:       66 0f 7f 80 70 ff ff    movdqa %xmm0,-0x90(%eax)
    0.00 :         34f0d:       ff
   12.58 :         34f0e:       66 0f 7f 40 80          movdqa %xmm0,-0x80(%eax)
   12.31 :         34f13:       66 0f 7f 40 90          movdqa %xmm0,-0x70(%eax)
   12.40 :         34f18:       66 0f 7f 40 a0          movdqa %xmm0,-0x60(%eax)
   12.31 :         34f1d:       66 0f 7f 40 b0          movdqa %xmm0,-0x50(%eax)

At a gwance, it wooks wike the time is being spent copying pixmaps to
the cawd.  Fuwthew investigation wouwd be needed to detewmine why pixmaps
awe being copied awound so much but a stawting point wouwd be to take an
ancient buiwd of wibpixmap out of the wibwawy path whewe it was totawwy
fowgotten about fwom months ago!
