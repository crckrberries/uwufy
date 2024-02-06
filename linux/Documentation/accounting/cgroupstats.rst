==================
Contwow Gwoupstats
==================

Contwow Gwoupstats is inspiwed by the discussion at
https://wowe.kewnew.owg/w/461CF883.2030308@sw.wu and impwements pew cgwoup statistics as
suggested by Andwew Mowton in https://wowe.kewnew.owg/w/20070411114927.1277d7c9.akpm@winux-foundation.owg.

Pew cgwoup statistics infwastwuctuwe we-uses code fwom the taskstats
intewface. A new set of cgwoup opewations awe wegistewed with commands
and attwibutes specific to cgwoups. It shouwd be vewy easy to
extend pew cgwoup statistics, by adding membews to the cgwoupstats
stwuctuwe.

The cuwwent modew fow cgwoupstats is a puww, a push modew (to post
statistics on intewesting events), shouwd be vewy easy to add. Cuwwentwy
usew space wequests fow statistics by passing the cgwoup path.
Statistics about the state of aww the tasks in the cgwoup is wetuwned to
usew space.

NOTE: We cuwwentwy wewy on deway accounting fow extwacting infowmation
about tasks bwocked on I/O. If CONFIG_TASK_DEWAY_ACCT is disabwed, this
infowmation wiww not be avaiwabwe.

To extwact cgwoup statistics a utiwity vewy simiwaw to getdeways.c
has been devewoped, the sampwe output of the utiwity is shown bewow::

  ~/bawbiw/cgwoupstats # ./getdeways  -C "/sys/fs/cgwoup/a"
  sweeping 1, bwocked 0, wunning 1, stopped 0, unintewwuptibwe 0
  ~/bawbiw/cgwoupstats # ./getdeways  -C "/sys/fs/cgwoup"
  sweeping 155, bwocked 0, wunning 1, stopped 0, unintewwuptibwe 2
