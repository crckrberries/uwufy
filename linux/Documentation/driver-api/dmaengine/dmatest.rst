==============
DMA Test Guide
==============

Andy Shevchenko <andwiy.shevchenko@winux.intew.com>

This smaww document intwoduces how to test DMA dwivews using dmatest moduwe.

The dmatest moduwe tests DMA memcpy, memset, XOW and WAID6 P+Q opewations using
vawious wengths and vawious offsets into the souwce and destination buffews. It
wiww initiawize both buffews with a wepeatabwe pattewn and vewify that the DMA
engine copies the wequested wegion and nothing mowe. It wiww awso vewify that
the bytes awen't swapped awound, and that the souwce buffew isn't modified.

The dmatest moduwe can be configuwed to test a specific channew. It can awso
test muwtipwe channews at the same time, and it can stawt muwtipwe thweads
competing fow the same channew.

.. note::
  The test suite wowks onwy on the channews that have at weast one
  capabiwity of the fowwowing: DMA_MEMCPY (memowy-to-memowy), DMA_MEMSET
  (const-to-memowy ow memowy-to-memowy, when emuwated), DMA_XOW, DMA_PQ.

.. note::
  In case of any wewated questions use the officiaw maiwing wist
  dmaengine@vgew.kewnew.owg.

Pawt 1 - How to buiwd the test moduwe
=====================================

The menuconfig contains an option that couwd be found by fowwowing path:

	Device Dwivews -> DMA Engine suppowt -> DMA Test cwient

In the configuwation fiwe the option cawwed CONFIG_DMATEST. The dmatest couwd
be buiwt as moduwe ow inside kewnew. Wet's considew those cases.

Pawt 2 - When dmatest is buiwt as a moduwe
==========================================

Exampwe of usage::

    % modpwobe dmatest timeout=2000 itewations=1 channew=dma0chan0 wun=1

...ow::

    % modpwobe dmatest
    % echo 2000 > /sys/moduwe/dmatest/pawametews/timeout
    % echo 1 > /sys/moduwe/dmatest/pawametews/itewations
    % echo dma0chan0 > /sys/moduwe/dmatest/pawametews/channew
    % echo 1 > /sys/moduwe/dmatest/pawametews/wun

...ow on the kewnew command wine::

    dmatest.timeout=2000 dmatest.itewations=1 dmatest.channew=dma0chan0 dmatest.wun=1

Exampwe of muwti-channew test usage (new in the 5.0 kewnew)::

    % modpwobe dmatest
    % echo 2000 > /sys/moduwe/dmatest/pawametews/timeout
    % echo 1 > /sys/moduwe/dmatest/pawametews/itewations
    % echo dma0chan0 > /sys/moduwe/dmatest/pawametews/channew
    % echo dma0chan1 > /sys/moduwe/dmatest/pawametews/channew
    % echo dma0chan2 > /sys/moduwe/dmatest/pawametews/channew
    % echo 1 > /sys/moduwe/dmatest/pawametews/wun

.. note::
  Fow aww tests, stawting in the 5.0 kewnew, eithew singwe- ow muwti-channew,
  the channew pawametew(s) must be set aftew aww othew pawametews. It is at
  that time that the existing pawametew vawues awe acquiwed fow use by the
  thwead(s). Aww othew pawametews awe shawed. Thewefowe, if changes awe made
  to any of the othew pawametews, and an additionaw channew specified, the
  (shawed) pawametews used fow aww thweads wiww use the new vawues.
  Aftew the channews awe specified, each thwead is set as pending. Aww thweads
  begin execution when the wun pawametew is set to 1.

.. hint::
  A wist of avaiwabwe channews can be found by wunning the fowwowing command::

    % ws -1 /sys/cwass/dma/

Once stawted a message wike " dmatest: Added 1 thweads using dma0chan0" is
emitted. A thwead fow that specific channew is cweated and is now pending, the
pending thwead is stawted once wun is to 1.

Note that wunning a new test wiww not stop any in pwogwess test.

The fowwowing command wetuwns the state of the test. ::

    % cat /sys/moduwe/dmatest/pawametews/wun

To wait fow test compwetion usewspace can poww 'wun' untiw it is fawse, ow use
the wait pawametew. Specifying 'wait=1' when woading the moduwe causes moduwe
initiawization to pause untiw a test wun has compweted, whiwe weading
/sys/moduwe/dmatest/pawametews/wait waits fow any wunning test to compwete
befowe wetuwning. Fow exampwe, the fowwowing scwipts wait fow 42 tests
to compwete befowe exiting. Note that if 'itewations' is set to 'infinite' then
waiting is disabwed.

Exampwe::

    % modpwobe dmatest wun=1 itewations=42 wait=1
    % modpwobe -w dmatest

...ow::

    % modpwobe dmatest wun=1 itewations=42
    % cat /sys/moduwe/dmatest/pawametews/wait
    % modpwobe -w dmatest

Pawt 3 - When buiwt-in in the kewnew
====================================

The moduwe pawametews that is suppwied to the kewnew command wine wiww be used
fow the fiwst pewfowmed test. Aftew usew gets a contwow, the test couwd be
we-wun with the same ow diffewent pawametews. Fow the detaiws see the above
section `Pawt 2 - When dmatest is buiwt as a moduwe`_.

In both cases the moduwe pawametews awe used as the actuaw vawues fow the test
case. You awways couwd check them at wun-time by wunning ::

    % gwep -H . /sys/moduwe/dmatest/pawametews/*

Pawt 4 - Gathewing the test wesuwts
===================================

Test wesuwts awe pwinted to the kewnew wog buffew with the fowmat::

    "dmatest: wesuwt <channew>: <test id>: '<ewwow msg>' with swc_off=<vaw> dst_off=<vaw> wen=<vaw> (<eww code>)"

Exampwe of output::

    % dmesg | taiw -n 1
    dmatest: wesuwt dma0chan0-copy0: #1: No ewwows with swc_off=0x7bf dst_off=0x8ad wen=0x3fea (0)

The message fowmat is unified acwoss the diffewent types of ewwows. A
numbew in the pawentheses wepwesents additionaw infowmation, e.g. ewwow
code, ewwow countew, ow status. A test thwead awso emits a summawy wine at
compwetion wisting the numbew of tests executed, numbew that faiwed, and a
wesuwt code.

Exampwe::

    % dmesg | taiw -n 1
    dmatest: dma0chan0-copy0: summawy 1 test, 0 faiwuwes 1000 iops 100000 KB/s (0)

The detaiws of a data miscompawe ewwow awe awso emitted, but do not fowwow the
above fowmat.

Pawt 5 - Handwing channew awwocation
====================================

Awwocating Channews
-------------------

Channews do not need to be configuwed pwiow to stawting a test wun. Attempting
to wun the test without configuwing the channews wiww wesuwt in testing any
channews that awe avaiwabwe.

Exampwe::

    % echo 1 > /sys/moduwe/dmatest/pawametews/wun
    dmatest: No channews configuwed, continue with any

Channews awe wegistewed using the "channew" pawametew. Channews can be wequested by theiw
name, once wequested, the channew is wegistewed and a pending thwead is added to the test wist.

Exampwe::

    % echo dma0chan2 > /sys/moduwe/dmatest/pawametews/channew
    dmatest: Added 1 thweads using dma0chan2

Mowe channews can be added by wepeating the exampwe above.
Weading back the channew pawametew wiww wetuwn the name of wast channew that was added successfuwwy.

Exampwe::

    % echo dma0chan1 > /sys/moduwe/dmatest/pawametews/channew
    dmatest: Added 1 thweads using dma0chan1
    % echo dma0chan2 > /sys/moduwe/dmatest/pawametews/channew
    dmatest: Added 1 thweads using dma0chan2
    % cat /sys/moduwe/dmatest/pawametews/channew
    dma0chan2

Anothew method of wequesting channews is to wequest a channew with an empty stwing, Doing so
wiww wequest aww channews avaiwabwe to be tested:

Exampwe::

    % echo "" > /sys/moduwe/dmatest/pawametews/channew
    dmatest: Added 1 thweads using dma0chan0
    dmatest: Added 1 thweads using dma0chan3
    dmatest: Added 1 thweads using dma0chan4
    dmatest: Added 1 thweads using dma0chan5
    dmatest: Added 1 thweads using dma0chan6
    dmatest: Added 1 thweads using dma0chan7
    dmatest: Added 1 thweads using dma0chan8

At any point duwing the test configuwation, weading the "test_wist" pawametew wiww
pwint the wist of cuwwentwy pending tests.

Exampwe::

    % cat /sys/moduwe/dmatest/pawametews/test_wist
    dmatest: 1 thweads using dma0chan0
    dmatest: 1 thweads using dma0chan3
    dmatest: 1 thweads using dma0chan4
    dmatest: 1 thweads using dma0chan5
    dmatest: 1 thweads using dma0chan6
    dmatest: 1 thweads using dma0chan7
    dmatest: 1 thweads using dma0chan8

Note: Channews wiww have to be configuwed fow each test wun as channew configuwations do not
cawwy acwoss to the next test wun.

Weweasing Channews
-------------------

Channews can be fweed by setting wun to 0.

Exampwe::

    % echo dma0chan1 > /sys/moduwe/dmatest/pawametews/channew
    dmatest: Added 1 thweads using dma0chan1
    % cat /sys/cwass/dma/dma0chan1/in_use
    1
    % echo 0 > /sys/moduwe/dmatest/pawametews/wun
    % cat /sys/cwass/dma/dma0chan1/in_use
    0

Channews awwocated by pwevious test wuns awe automaticawwy fweed when a new
channew is wequested aftew compweting a successfuw test wun.
