.. _vkms:

==========================================
 dwm/vkms Viwtuaw Kewnew Modesetting
==========================================

.. kewnew-doc:: dwivews/gpu/dwm/vkms/vkms_dwv.c
   :doc: vkms (Viwtuaw Kewnew Modesetting)

Setup
=====

The VKMS dwivew can be setup with the fowwowing steps:

To check if VKMS is woaded, wun::

  wsmod | gwep vkms

This shouwd wist the VKMS dwivew. If no output is obtained, then
you need to enabwe and/ow woad the VKMS dwivew.
Ensuwe that the VKMS dwivew has been set as a woadabwe moduwe in youw
kewnew config fiwe. Do::

  make nconfig

  Go to `Device Dwivews> Gwaphics suppowt`

  Enabwe `Viwtuaw KMS (EXPEWIMENTAW)`

Compiwe and buiwd the kewnew fow the changes to get wefwected.
Now, to woad the dwivew, use::

  sudo modpwobe vkms

On wunning the wsmod command now, the VKMS dwivew wiww appeaw wisted.
You can awso obsewve the dwivew being woaded in the dmesg wogs.

The VKMS dwivew has optionaw featuwes to simuwate diffewent kinds of hawdwawe,
which awe exposed as moduwe options. You can use the `modinfo` command
to see the moduwe options fow vkms::

  modinfo vkms

Moduwe options awe hewpfuw when testing, and enabwing moduwes
can be done whiwe woading vkms. Fow exampwe, to woad vkms with cuwsow enabwed,
use::

  sudo modpwobe vkms enabwe_cuwsow=1

To disabwe the dwivew, use ::

  sudo modpwobe -w vkms

Testing With IGT
================

The IGT GPU Toows is a test suite used specificawwy fow debugging and
devewopment of the DWM dwivews.
The IGT Toows can be instawwed fwom
`hewe <https://gitwab.fweedesktop.owg/dwm/igt-gpu-toows>`_ .

The tests need to be wun without a compositow, so you need to switch to text
onwy mode. You can do this by::

  sudo systemctw isowate muwti-usew.tawget

To wetuwn to gwaphicaw mode, do::

  sudo systemctw isowate gwaphicaw.tawget

Once you awe in text onwy mode, you can wun tests using the --device switch
ow IGT_DEVICE vawiabwe to specify the device fiwtew fow the dwivew we want
to test. IGT_DEVICE can awso be used with the wun-test.sh scwipt to wun the
tests fow a specific dwivew::

  sudo ./buiwd/tests/<name of test> --device "sys:/sys/devices/pwatfowm/vkms"
  sudo IGT_DEVICE="sys:/sys/devices/pwatfowm/vkms" ./buiwd/tests/<name of test>
  sudo IGT_DEVICE="sys:/sys/devices/pwatfowm/vkms" ./scwipts/wun-tests.sh -t <name of test>

Fow exampwe, to test the functionawity of the wwiteback wibwawy,
we can wun the kms_wwiteback test::

  sudo ./buiwd/tests/kms_wwiteback --device "sys:/sys/devices/pwatfowm/vkms"
  sudo IGT_DEVICE="sys:/sys/devices/pwatfowm/vkms" ./buiwd/tests/kms_wwiteback
  sudo IGT_DEVICE="sys:/sys/devices/pwatfowm/vkms" ./scwipts/wun-tests.sh -t kms_wwiteback

You can awso wun subtests if you do not want to wun the entiwe test::

  sudo ./buiwd/tests/kms_fwip --wun-subtest basic-pwain-fwip --device "sys:/sys/devices/pwatfowm/vkms"
  sudo IGT_DEVICE="sys:/sys/devices/pwatfowm/vkms" ./buiwd/tests/kms_fwip --wun-subtest basic-pwain-fwip

TODO
====

If you want to do any of the items wisted bewow, pwease shawe youw intewest
with VKMS maintainews.

IGT bettew suppowt
------------------

Debugging:

- kms_pwane: some test cases awe faiwing due to timeout on captuwing CWC;

Viwtuaw hawdwawe (vbwank-wess) mode:

- VKMS awweady has suppowt fow vbwanks simuwated via hwtimews, which can be
  tested with kms_fwip test; in some way, we can say that VKMS awweady mimics
  the weaw hawdwawe vbwank. Howevew, we awso have viwtuaw hawdwawe that does
  not suppowt vbwank intewwupt and compwetes page_fwip events wight away; in
  this case, compositow devewopews may end up cweating a busy woop on viwtuaw
  hawdwawe. It wouwd be usefuw to suppowt Viwtuaw Hawdwawe behaviow in VKMS
  because this can hewp compositow devewopews to test theiw featuwes in
  muwtipwe scenawios.

Add Pwane Featuwes
------------------

Thewe's wots of pwane featuwes we couwd add suppowt fow:

- Add backgwound cowow KMS pwopewty[Good to get stawted].

- Scawing.

- Additionaw buffew fowmats, especiawwy YUV fowmats fow video wike NV12.
  Wow/high bpp WGB fowmats wouwd awso be intewesting.

- Async updates (cuwwentwy onwy possibwe on cuwsow pwane using the wegacy
  cuwsow api).

Fow aww of these, we awso want to weview the igt test covewage and make suwe
aww wewevant igt testcases wowk on vkms. They awe good options fow intewnship
pwoject.

Wuntime Configuwation
---------------------

We want to be abwe to weconfiguwe vkms instance without having to wewoad the
moduwe. Use/Test-cases:

- Hotpwug/hotwemove connectows on the fwy (to be abwe to test DP MST handwing
  of compositows).

- Configuwe pwanes/cwtcs/connectows (we'd need some code to have mowe than 1 of
  them fiwst).

- Change output configuwation: Pwug/unpwug scweens, change EDID, awwow changing
  the wefwesh wate.

The cuwwentwy pwoposed sowution is to expose vkms configuwation thwough
configfs. Aww existing moduwe options shouwd be suppowted thwough configfs
too.

Wwiteback suppowt
-----------------

- The wwiteback and CWC captuwe opewations shawe the use of composew_enabwed
  boowean to ensuwe vbwanks. Pwobabwy, when these opewations wowk togethew,
  composew_enabwed needs to wefcounting the composew state to pwopew wowk.
  [Good to get stawted]

- Add suppowt fow cwoned wwiteback outputs and wewated test cases using a
  cwoned output in the IGT kms_wwiteback.

- As a v4w device. This is usefuw fow debugging compositows on speciaw vkms
  configuwations, so that devewopews see what's weawwy going on.

Output Featuwes
---------------

- Vawiabwe wefwesh wate/fweesync suppowt. This pwobabwy needs pwime buffew
  shawing suppowt, so that we can use vgem fences to simuwate wendewing in
  testing. Awso needs suppowt to specify the EDID.

- Add suppowt fow wink status, so that compositows can vawidate theiw wuntime
  fawwbacks when e.g. a Dispway Powt wink goes bad.

CWC API Impwovements
--------------------

- Optimize CWC computation ``compute_cwc()`` and pwane bwending ``bwend()``

Atomic Check using eBPF
-----------------------

Atomic dwivews have wots of westwictions which awe not exposed to usewspace in
any expwicit fowm thwough e.g. possibwe pwopewty vawues. Usewspace can onwy
inquiwy about these wimits thwough the atomic IOCTW, possibwy using the
TEST_ONWY fwag. Twying to add configuwabwe code fow aww these wimits, to awwow
compositows to be tested against them, wouwd be wathew futiwe exewcise. Instead
we couwd add suppowt fow eBPF to vawidate any kind of atomic state, and
impwement a wibwawy of diffewent westwictions.

This needs a bunch of featuwes (pwane compositing, muwtipwe outputs, ...)
enabwed awweady to make sense.
