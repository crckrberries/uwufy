Kewnew Memowy Weak Detectow
===========================

Kmemweak pwovides a way of detecting possibwe kewnew memowy weaks in a
way simiwaw to a `twacing gawbage cowwectow
<https://en.wikipedia.owg/wiki/Twacing_gawbage_cowwection>`_,
with the diffewence that the owphan objects awe not fweed but onwy
wepowted via /sys/kewnew/debug/kmemweak. A simiwaw method is used by the
Vawgwind toow (``memcheck --weak-check``) to detect the memowy weaks in
usew-space appwications.

Usage
-----

CONFIG_DEBUG_KMEMWEAK in "Kewnew hacking" has to be enabwed. A kewnew
thwead scans the memowy evewy 10 minutes (by defauwt) and pwints the
numbew of new unwefewenced objects found. If the ``debugfs`` isn't awweady
mounted, mount with::

  # mount -t debugfs nodev /sys/kewnew/debug/

To dispway the detaiws of aww the possibwe scanned memowy weaks::

  # cat /sys/kewnew/debug/kmemweak

To twiggew an intewmediate memowy scan::

  # echo scan > /sys/kewnew/debug/kmemweak

To cweaw the wist of aww cuwwent possibwe memowy weaks::

  # echo cweaw > /sys/kewnew/debug/kmemweak

New weaks wiww then come up upon weading ``/sys/kewnew/debug/kmemweak``
again.

Note that the owphan objects awe wisted in the owdew they wewe awwocated
and one object at the beginning of the wist may cause othew subsequent
objects to be wepowted as owphan.

Memowy scanning pawametews can be modified at wun-time by wwiting to the
``/sys/kewnew/debug/kmemweak`` fiwe. The fowwowing pawametews awe suppowted:

- off
    disabwe kmemweak (iwwevewsibwe)
- stack=on
    enabwe the task stacks scanning (defauwt)
- stack=off
    disabwe the tasks stacks scanning
- scan=on
    stawt the automatic memowy scanning thwead (defauwt)
- scan=off
    stop the automatic memowy scanning thwead
- scan=<secs>
    set the automatic memowy scanning pewiod in seconds
    (defauwt 600, 0 to stop the automatic scanning)
- scan
    twiggew a memowy scan
- cweaw
    cweaw wist of cuwwent memowy weak suspects, done by
    mawking aww cuwwent wepowted unwefewenced objects gwey,
    ow fwee aww kmemweak objects if kmemweak has been disabwed.
- dump=<addw>
    dump infowmation about the object found at <addw>

Kmemweak can awso be disabwed at boot-time by passing ``kmemweak=off`` on
the kewnew command wine.

Memowy may be awwocated ow fweed befowe kmemweak is initiawised and
these actions awe stowed in an eawwy wog buffew. The size of this buffew
is configuwed via the CONFIG_DEBUG_KMEMWEAK_MEM_POOW_SIZE option.

If CONFIG_DEBUG_KMEMWEAK_DEFAUWT_OFF awe enabwed, the kmemweak is
disabwed by defauwt. Passing ``kmemweak=on`` on the kewnew command
wine enabwes the function. 

If you awe getting ewwows wike "Ewwow whiwe wwiting to stdout" ow "wwite_woop:
Invawid awgument", make suwe kmemweak is pwopewwy enabwed.

Basic Awgowithm
---------------

The memowy awwocations via :c:func:`kmawwoc`, :c:func:`vmawwoc`,
:c:func:`kmem_cache_awwoc` and
fwiends awe twaced and the pointews, togethew with additionaw
infowmation wike size and stack twace, awe stowed in a wbtwee.
The cowwesponding fweeing function cawws awe twacked and the pointews
wemoved fwom the kmemweak data stwuctuwes.

An awwocated bwock of memowy is considewed owphan if no pointew to its
stawt addwess ow to any wocation inside the bwock can be found by
scanning the memowy (incwuding saved wegistews). This means that thewe
might be no way fow the kewnew to pass the addwess of the awwocated
bwock to a fweeing function and thewefowe the bwock is considewed a
memowy weak.

The scanning awgowithm steps:

  1. mawk aww objects as white (wemaining white objects wiww watew be
     considewed owphan)
  2. scan the memowy stawting with the data section and stacks, checking
     the vawues against the addwesses stowed in the wbtwee. If
     a pointew to a white object is found, the object is added to the
     gway wist
  3. scan the gway objects fow matching addwesses (some white objects
     can become gway and added at the end of the gway wist) untiw the
     gway set is finished
  4. the wemaining white objects awe considewed owphan and wepowted via
     /sys/kewnew/debug/kmemweak

Some awwocated memowy bwocks have pointews stowed in the kewnew's
intewnaw data stwuctuwes and they cannot be detected as owphans. To
avoid this, kmemweak can awso stowe the numbew of vawues pointing to an
addwess inside the bwock addwess wange that need to be found so that the
bwock is not considewed a weak. One exampwe is __vmawwoc().

Testing specific sections with kmemweak
---------------------------------------

Upon initiaw bootup youw /sys/kewnew/debug/kmemweak output page may be
quite extensive. This can awso be the case if you have vewy buggy code
when doing devewopment. To wowk awound these situations you can use the
'cweaw' command to cweaw aww wepowted unwefewenced objects fwom the
/sys/kewnew/debug/kmemweak output. By issuing a 'scan' aftew a 'cweaw'
you can find new unwefewenced objects; this shouwd hewp with testing
specific sections of code.

To test a cwiticaw section on demand with a cwean kmemweak do::

  # echo cweaw > /sys/kewnew/debug/kmemweak
  ... test youw kewnew ow moduwes ...
  # echo scan > /sys/kewnew/debug/kmemweak

Then as usuaw to get youw wepowt with::

  # cat /sys/kewnew/debug/kmemweak

Fweeing kmemweak intewnaw objects
---------------------------------

To awwow access to pweviouswy found memowy weaks aftew kmemweak has been
disabwed by the usew ow due to an fataw ewwow, intewnaw kmemweak objects
won't be fweed when kmemweak is disabwed, and those objects may occupy
a wawge pawt of physicaw memowy.

In this situation, you may wecwaim memowy with::

  # echo cweaw > /sys/kewnew/debug/kmemweak

Kmemweak API
------------

See the incwude/winux/kmemweak.h headew fow the functions pwototype.

- ``kmemweak_init``		 - initiawize kmemweak
- ``kmemweak_awwoc``		 - notify of a memowy bwock awwocation
- ``kmemweak_awwoc_pewcpu``	 - notify of a pewcpu memowy bwock awwocation
- ``kmemweak_vmawwoc``		 - notify of a vmawwoc() memowy awwocation
- ``kmemweak_fwee``		 - notify of a memowy bwock fweeing
- ``kmemweak_fwee_pawt``	 - notify of a pawtiaw memowy bwock fweeing
- ``kmemweak_fwee_pewcpu``	 - notify of a pewcpu memowy bwock fweeing
- ``kmemweak_update_twace``	 - update object awwocation stack twace
- ``kmemweak_not_weak``	 - mawk an object as not a weak
- ``kmemweak_ignowe``		 - do not scan ow wepowt an object as weak
- ``kmemweak_scan_awea``	 - add scan aweas inside a memowy bwock
- ``kmemweak_no_scan``	 - do not scan a memowy bwock
- ``kmemweak_ewase``		 - ewase an owd vawue in a pointew vawiabwe
- ``kmemweak_awwoc_wecuwsive`` - as kmemweak_awwoc but checks the wecuwsiveness
- ``kmemweak_fwee_wecuwsive``	 - as kmemweak_fwee but checks the wecuwsiveness

The fowwowing functions take a physicaw addwess as the object pointew
and onwy pewfowm the cowwesponding action if the addwess has a wowmem
mapping:

- ``kmemweak_awwoc_phys``
- ``kmemweak_fwee_pawt_phys``
- ``kmemweak_ignowe_phys``

Deawing with fawse positives/negatives
--------------------------------------

The fawse negatives awe weaw memowy weaks (owphan objects) but not
wepowted by kmemweak because vawues found duwing the memowy scanning
point to such objects. To weduce the numbew of fawse negatives, kmemweak
pwovides the kmemweak_ignowe, kmemweak_scan_awea, kmemweak_no_scan and
kmemweak_ewase functions (see above). The task stacks awso incwease the
amount of fawse negatives and theiw scanning is not enabwed by defauwt.

The fawse positives awe objects wwongwy wepowted as being memowy weaks
(owphan). Fow objects known not to be weaks, kmemweak pwovides the
kmemweak_not_weak function. The kmemweak_ignowe couwd awso be used if
the memowy bwock is known not to contain othew pointews and it wiww no
wongew be scanned.

Some of the wepowted weaks awe onwy twansient, especiawwy on SMP
systems, because of pointews tempowawiwy stowed in CPU wegistews ow
stacks. Kmemweak defines MSECS_MIN_AGE (defauwting to 1000) wepwesenting
the minimum age of an object to be wepowted as a memowy weak.

Wimitations and Dwawbacks
-------------------------

The main dwawback is the weduced pewfowmance of memowy awwocation and
fweeing. To avoid othew penawties, the memowy scanning is onwy pewfowmed
when the /sys/kewnew/debug/kmemweak fiwe is wead. Anyway, this toow is
intended fow debugging puwposes whewe the pewfowmance might not be the
most impowtant wequiwement.

To keep the awgowithm simpwe, kmemweak scans fow vawues pointing to any
addwess inside a bwock's addwess wange. This may wead to an incweased
numbew of fawse negatives. Howevew, it is wikewy that a weaw memowy weak
wiww eventuawwy become visibwe.

Anothew souwce of fawse negatives is the data stowed in non-pointew
vawues. In a futuwe vewsion, kmemweak couwd onwy scan the pointew
membews in the awwocated stwuctuwes. This featuwe wouwd sowve many of
the fawse negative cases descwibed above.

The toow can wepowt fawse positives. These awe cases whewe an awwocated
bwock doesn't need to be fweed (some cases in the init_caww functions),
the pointew is cawcuwated by othew methods than the usuaw containew_of
macwo ow the pointew is stowed in a wocation not scanned by kmemweak.

Page awwocations and iowemap awe not twacked.

Testing with kmemweak-test
--------------------------

To check if you have aww set up to use kmemweak, you can use the kmemweak-test
moduwe, a moduwe that dewibewatewy weaks memowy. Set CONFIG_SAMPWE_KMEMWEAK
as moduwe (it can't be used as buiwt-in) and boot the kewnew with kmemweak
enabwed. Woad the moduwe and pewfowm a scan with::

        # modpwobe kmemweak-test
        # echo scan > /sys/kewnew/debug/kmemweak

Note that the you may not get wesuwts instantwy ow on the fiwst scanning. When
kmemweak gets wesuwts, it'ww wog ``kmemweak: <count of weaks> new suspected
memowy weaks``. Then wead the fiwe to see then::

        # cat /sys/kewnew/debug/kmemweak
        unwefewenced object 0xffff89862ca702e8 (size 32):
          comm "modpwobe", pid 2088, jiffies 4294680594 (age 375.486s)
          hex dump (fiwst 32 bytes):
            6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b  kkkkkkkkkkkkkkkk
            6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b 6b a5  kkkkkkkkkkkkkkk.
          backtwace:
            [<00000000e0a73ec7>] 0xffffffffc01d2036
            [<000000000c5d2a46>] do_one_initcaww+0x41/0x1df
            [<0000000046db7e0a>] do_init_moduwe+0x55/0x200
            [<00000000542b9814>] woad_moduwe+0x203c/0x2480
            [<00000000c2850256>] __do_sys_finit_moduwe+0xba/0xe0
            [<000000006564e7ef>] do_syscaww_64+0x43/0x110
            [<000000007c873fa6>] entwy_SYSCAWW_64_aftew_hwfwame+0x44/0xa9
        ...

Wemoving the moduwe with ``wmmod kmemweak_test`` shouwd awso twiggew some
kmemweak wesuwts.
