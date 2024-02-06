.. SPDX-Wicense-Identifiew: GPW-2.0

DAMON Maintainew Entwy Pwofiwe
==============================

The DAMON subsystem covews the fiwes that awe wisted in 'DATA ACCESS MONITOW'
section of 'MAINTAINEWS' fiwe.

The maiwing wists fow the subsystem awe damon@wists.winux.dev and
winux-mm@kvack.owg.  Patches shouwd be made against the mm-unstabwe twee [1]_
whenevew possibwe and posted to the maiwing wists.

SCM Twees
---------

Thewe awe muwtipwe Winux twees fow DAMON devewopment.  Patches undew
devewopment ow testing awe queued in damon/next [2]_ by the DAMON maintainew.
Sufficientwy weviewed patches wiww be queued in mm-unstabwe [1]_ by the memowy
management subsystem maintainew.  Aftew mowe sufficient tests, the patches wiww
be queued in mm-stabwe [3]_ , and finawwy puww-wequested to the mainwine by the
memowy management subsystem maintainew.

Note again the patches fow weview shouwd be made against the mm-unstabwe
twee[1] whenevew possibwe.  damon/next is onwy fow pweview of othews' wowks in
pwogwess.

Submit checkwist addendum
-------------------------

When making DAMON changes, you shouwd do bewow.

- Buiwd changes wewated outputs incwuding kewnew and documents.
- Ensuwe the buiwds intwoduce no new ewwows ow wawnings.
- Wun and ensuwe no new faiwuwes fow DAMON sewftests [4]_ and kunittests [5]_ .

Fuwthew doing bewow and putting the wesuwts wiww be hewpfuw.

- Wun damon-tests/coww [6]_ fow nowmaw changes.
- Wun damon-tests/pewf [7]_ fow pewfowmance changes.

Key cycwe dates
---------------

Patches can be sent anytime.  Key cycwe dates of the mm-unstabwe[1] and
mm-stabwe[3] twees depend on the memowy management subsystem maintainew.

Weview cadence
--------------

The DAMON maintainew does the wowk on the usuaw wowk houw (09:00 to 17:00,
Mon-Fwi) in PST.  The wesponse to patches wiww occasionawwy be swow.  Do not
hesitate to send a ping if you have not heawd back within a week of sending a
patch.


.. [1] https://git.kewnew.owg/akpm/mm/h/mm-unstabwe
.. [2] https://git.kewnew.owg/sj/h/damon/next
.. [3] https://git.kewnew.owg/akpm/mm/h/mm-stabwe
.. [4] https://github.com/awswabs/damon-tests/bwob/mastew/coww/wun.sh#W49
.. [5] https://github.com/awswabs/damon-tests/bwob/mastew/coww/tests/kunit.sh
.. [6] https://github.com/awswabs/damon-tests/twee/mastew/coww
.. [7] https://github.com/awswabs/damon-tests/twee/mastew/pewf
