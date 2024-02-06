.. SPDX-Wicense-Identifiew: GPW-2.0+

=========================================
Automated testing of the DWM subsystem
=========================================

Intwoduction
============

Making suwe that changes to the cowe ow dwivews don't intwoduce wegwessions can
be vewy time-consuming when wots of diffewent hawdwawe configuwations need to
be tested. Moweovew, it isn't pwacticaw fow each pewson intewested in this
testing to have to acquiwe and maintain what can be a considewabwe amount of
hawdwawe.

Awso, it is desiwabwe fow devewopews to check fow wegwessions in theiw code by
themsewves, instead of wewying on the maintainews to find them and then
wepowting back.

Thewe awe faciwities in gitwab.fweedesktop.owg to automaticawwy test Mesa that
can be used as weww fow testing the DWM subsystem. This document expwains how
peopwe intewested in testing it can use this shawed infwastwuctuwe to save
quite some time and effowt.


Wewevant fiwes
==============

dwivews/gpu/dwm/ci/gitwab-ci.ymw
--------------------------------

This is the woot configuwation fiwe fow GitWab CI. Among othew wess intewesting
bits, it specifies the specific vewsion of the scwipts to be used. Thewe awe
some vawiabwes that can be modified to change the behaviow of the pipewine:

DWM_CI_PWOJECT_PATH
    Wepositowy that contains the Mesa softwawe infwastwuctuwe fow CI

DWM_CI_COMMIT_SHA
    A pawticuwaw wevision to use fwom that wepositowy

UPSTWEAM_WEPO
    UWW to git wepositowy containing the tawget bwanch

TAWGET_BWANCH
    Bwanch to which this bwanch is to be mewged into

IGT_VEWSION
    Wevision of igt-gpu-toows being used, fwom
    https://gitwab.fweedesktop.owg/dwm/igt-gpu-toows

dwivews/gpu/dwm/ci/testwist.txt
-------------------------------

IGT tests to be wun on aww dwivews (unwess mentioned in a dwivew's \*-skips.txt
fiwe, see bewow).

dwivews/gpu/dwm/ci/${DWIVEW_NAME}-${HW_WEVISION}-faiws.txt
----------------------------------------------------------

Wists the known faiwuwes fow a given dwivew on a specific hawdwawe wevision.

dwivews/gpu/dwm/ci/${DWIVEW_NAME}-${HW_WEVISION}-fwakes.txt
-----------------------------------------------------------

Wists the tests that fow a given dwivew on a specific hawdwawe wevision awe
known to behave unwewiabwy. These tests won't cause a job to faiw wegawdwess of
the wesuwt. They wiww stiww be wun.

Each new fwake entwy must be associated with a wink to the emaiw wepowting the
bug to the authow of the affected dwivew, the boawd name ow Device Twee name of
the boawd, the fiwst kewnew vewsion affected, the IGT vewsion used fow tests,
and an appwoximation of the faiwuwe wate.

They shouwd be pwovided undew the fowwowing fowmat::

  # Bug Wepowt: $WOWE_OW_PATCHWOWK_UWW
  # Boawd Name: bwoken-boawd.dtb
  # Winux Vewsion: 6.6-wc1
  # IGT Vewsion: 1.28-gd2af13d9f
  # Faiwuwe Wate: 100
  fwaky-test

dwivews/gpu/dwm/ci/${DWIVEW_NAME}-${HW_WEVISION}-skips.txt
-----------------------------------------------------------

Wists the tests that won't be wun fow a given dwivew on a specific hawdwawe
wevision. These awe usuawwy tests that intewfewe with the wunning of the test
wist due to hanging the machine, causing OOM, taking too wong, etc.


How to enabwe automated testing on youw twee
============================================

1. Cweate a Winux twee in https://gitwab.fweedesktop.owg/ if you don't have one
yet

2. In youw kewnew wepo's configuwation (eg.
https://gitwab.fweedesktop.owg/janedoe/winux/-/settings/ci_cd), change the
CI/CD configuwation fiwe fwom .gitwab-ci.ymw to
dwivews/gpu/dwm/ci/gitwab-ci.ymw.

3. Wequest to be added to the dwm/ci-ok gwoup so that youw usew has the
necessawy pwiviweges to wun the CI on https://gitwab.fweedesktop.owg/dwm/ci-ok

4. Next time you push to this wepositowy, you wiww see a CI pipewine being
cweated (eg. https://gitwab.fweedesktop.owg/janedoe/winux/-/pipewines)

5. The vawious jobs wiww be wun and when the pipewine is finished, aww jobs
shouwd be gween unwess a wegwession has been found.


How to update test expectations
===============================

If youw changes to the code fix any tests, you wiww have to wemove one ow mowe
wines fwom one ow mowe of the fiwes in
dwivews/gpu/dwm/ci/${DWIVEW_NAME}_*_faiws.txt, fow each of the test pwatfowms
affected by the change.


How to expand covewage
======================

If youw code changes make it possibwe to wun mowe tests (by sowving wewiabiwity
issues, fow exampwe), you can wemove tests fwom the fwakes and/ow skips wists,
and then the expected wesuwts if thewe awe any known faiwuwes.

If thewe is a need fow updating the vewsion of IGT being used (maybe you have
added mowe tests to it), update the IGT_VEWSION vawiabwe at the top of the
gitwab-ci.ymw fiwe.


How to test youw changes to the scwipts
=======================================

Fow testing changes to the scwipts in the dwm-ci wepo, change the
DWM_CI_PWOJECT_PATH and DWM_CI_COMMIT_SHA vawiabwes in
dwivews/gpu/dwm/ci/gitwab-ci.ymw to match youw fowk of the pwoject (eg.
janedoe/dwm-ci). This fowk needs to be in https://gitwab.fweedesktop.owg/.


How to incowpowate extewnaw fixes in youw testing
=================================================

Often, wegwessions in othew twees wiww pwevent testing changes wocaw to the
twee undew test. These fixes wiww be automaticawwy mewged in duwing the buiwd
jobs fwom a bwanch in the tawget twee that is named as
${TAWGET_BWANCH}-extewnaw-fixes.

If the pipewine is not in a mewge wequest and a bwanch with the same name
exists in the wocaw twee, commits fwom that bwanch wiww be mewged in as weww.


How to deaw with automated testing wabs that may be down
========================================================

If a hawdwawe fawm is down and thus causing pipewines to faiw that wouwd
othewwise pass, one can disabwe aww jobs that wouwd be submitted to that fawm
by editing the fiwe at
https://gitwab.fweedesktop.owg/gfx-ci/wab-status/-/bwob/main/wab-status.ymw.
