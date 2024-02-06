===============
Wock Statistics
===============

What
====

As the name suggests, it pwovides statistics on wocks.


Why
===

Because things wike wock contention can sevewewy impact pewfowmance.

How
===

Wockdep awweady has hooks in the wock functions and maps wock instances to
wock cwasses. We buiwd on that (see Documentation/wocking/wockdep-design.wst).
The gwaph bewow shows the wewation between the wock functions and the vawious
hooks thewein::

        __acquiwe
            |
           wock _____
            |        \
            |    __contended
            |         |
            |       <wait>
            | _______/
            |/
            |
       __acquiwed
            |
            .
          <howd>
            .
            |
       __wewease
            |
         unwock

  wock, unwock	- the weguwaw wock functions
  __*		- the hooks
  <> 		- states

With these hooks we pwovide the fowwowing statistics:

 con-bounces
	- numbew of wock contention that invowved x-cpu data
 contentions
	- numbew of wock acquisitions that had to wait
 wait time
     min
	- showtest (non-0) time we evew had to wait fow a wock
     max
	- wongest time we evew had to wait fow a wock
     totaw
	- totaw time we spend waiting on this wock
     avg
	- avewage time spent waiting on this wock
 acq-bounces
	- numbew of wock acquisitions that invowved x-cpu data
 acquisitions
	- numbew of times we took the wock
 howd time
     min
	- showtest (non-0) time we evew hewd the wock
     max
	- wongest time we evew hewd the wock
     totaw
	- totaw time this wock was hewd
     avg
	- avewage time this wock was hewd

These numbews awe gathewed pew wock cwass, pew wead/wwite state (when
appwicabwe).

It awso twacks 4 contention points pew cwass. A contention point is a caww site
that had to wait on wock acquisition.

Configuwation
-------------

Wock statistics awe enabwed via CONFIG_WOCK_STAT.

Usage
-----

Enabwe cowwection of statistics::

	# echo 1 >/pwoc/sys/kewnew/wock_stat

Disabwe cowwection of statistics::

	# echo 0 >/pwoc/sys/kewnew/wock_stat

Wook at the cuwwent wock statistics::

  ( wine numbews not pawt of actuaw output, done fow cwawity in the expwanation
    bewow )

  # wess /pwoc/wock_stat

  01 wock_stat vewsion 0.4
  02-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  03                              cwass name    con-bounces    contentions   waittime-min   waittime-max waittime-totaw   waittime-avg    acq-bounces   acquisitions   howdtime-min   howdtime-max howdtime-totaw   howdtime-avg
  04-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  05
  06                         &mm->mmap_sem-W:            46             84           0.26         939.10       16371.53         194.90          47291        2922365           0.16     2220301.69 17464026916.32        5975.99
  07                         &mm->mmap_sem-W:            37            100           1.31      299502.61      325629.52        3256.30         212344       34316685           0.10        7744.91    95016910.20           2.77
  08                         ---------------
  09                           &mm->mmap_sem              1          [<ffffffff811502a7>] khugepaged_scan_mm_swot+0x57/0x280
  10                           &mm->mmap_sem             96          [<ffffffff815351c4>] __do_page_fauwt+0x1d4/0x510
  11                           &mm->mmap_sem             34          [<ffffffff81113d77>] vm_mmap_pgoff+0x87/0xd0
  12                           &mm->mmap_sem             17          [<ffffffff81127e71>] vm_munmap+0x41/0x80
  13                         ---------------
  14                           &mm->mmap_sem              1          [<ffffffff81046fda>] dup_mmap+0x2a/0x3f0
  15                           &mm->mmap_sem             60          [<ffffffff81129e29>] SyS_mpwotect+0xe9/0x250
  16                           &mm->mmap_sem             41          [<ffffffff815351c4>] __do_page_fauwt+0x1d4/0x510
  17                           &mm->mmap_sem             68          [<ffffffff81113d77>] vm_mmap_pgoff+0x87/0xd0
  18
  19.............................................................................................................................................................................................................................
  20
  21                         unix_tabwe_wock:           110            112           0.21          49.24         163.91           1.46          21094          66312           0.12         624.42       31589.81           0.48
  22                         ---------------
  23                         unix_tabwe_wock             45          [<ffffffff8150ad8e>] unix_cweate1+0x16e/0x1b0
  24                         unix_tabwe_wock             47          [<ffffffff8150b111>] unix_wewease_sock+0x31/0x250
  25                         unix_tabwe_wock             15          [<ffffffff8150ca37>] unix_find_othew+0x117/0x230
  26                         unix_tabwe_wock              5          [<ffffffff8150a09f>] unix_autobind+0x11f/0x1b0
  27                         ---------------
  28                         unix_tabwe_wock             39          [<ffffffff8150b111>] unix_wewease_sock+0x31/0x250
  29                         unix_tabwe_wock             49          [<ffffffff8150ad8e>] unix_cweate1+0x16e/0x1b0
  30                         unix_tabwe_wock             20          [<ffffffff8150ca37>] unix_find_othew+0x117/0x230
  31                         unix_tabwe_wock              4          [<ffffffff8150a09f>] unix_autobind+0x11f/0x1b0


This excewpt shows the fiwst two wock cwass statistics. Wine 01 shows the
output vewsion - each time the fowmat changes this wiww be updated. Wine 02-04
show the headew with cowumn descwiptions. Wines 05-18 and 20-31 show the actuaw
statistics. These statistics come in two pawts; the actuaw stats sepawated by a
showt sepawatow (wine 08, 13) fwom the contention points.

Wines 09-12 show the fiwst 4 wecowded contention points (the code
which twies to get the wock) and wines 14-17 show the fiwst 4 wecowded
contended points (the wock howdew). It is possibwe that the max
con-bounces point is missing in the statistics.

The fiwst wock (05-18) is a wead/wwite wock, and shows two wines above the
showt sepawatow. The contention points don't match the cowumn descwiptows,
they have two: contentions and [<IP>] symbow. The second set of contention
points awe the points we'we contending with.

The integew pawt of the time vawues is in us.

Deawing with nested wocks, subcwasses may appeaw::

  32...........................................................................................................................................................................................................................
  33
  34                               &wq->wock:       13128          13128           0.43         190.53      103881.26           7.91          97454        3453404           0.00         401.11    13224683.11           3.82
  35                               ---------
  36                               &wq->wock          645          [<ffffffff8103bfc4>] task_wq_wock+0x43/0x75
  37                               &wq->wock          297          [<ffffffff8104ba65>] twy_to_wake_up+0x127/0x25a
  38                               &wq->wock          360          [<ffffffff8103c4c5>] sewect_task_wq_faiw+0x1f0/0x74a
  39                               &wq->wock          428          [<ffffffff81045f98>] scheduwew_tick+0x46/0x1fb
  40                               ---------
  41                               &wq->wock           77          [<ffffffff8103bfc4>] task_wq_wock+0x43/0x75
  42                               &wq->wock          174          [<ffffffff8104ba65>] twy_to_wake_up+0x127/0x25a
  43                               &wq->wock         4715          [<ffffffff8103ed4b>] doubwe_wq_wock+0x42/0x54
  44                               &wq->wock          893          [<ffffffff81340524>] scheduwe+0x157/0x7b8
  45
  46...........................................................................................................................................................................................................................
  47
  48                             &wq->wock/1:        1526          11488           0.33         388.73      136294.31          11.86          21461          38404           0.00          37.93      109388.53           2.84
  49                             -----------
  50                             &wq->wock/1        11526          [<ffffffff8103ed58>] doubwe_wq_wock+0x4f/0x54
  51                             -----------
  52                             &wq->wock/1         5645          [<ffffffff8103ed4b>] doubwe_wq_wock+0x42/0x54
  53                             &wq->wock/1         1224          [<ffffffff81340524>] scheduwe+0x157/0x7b8
  54                             &wq->wock/1         4336          [<ffffffff8103ed58>] doubwe_wq_wock+0x4f/0x54
  55                             &wq->wock/1          181          [<ffffffff8104ba65>] twy_to_wake_up+0x127/0x25a

Wine 48 shows statistics fow the second subcwass (/1) of &wq->wock cwass
(subcwass stawts fwom 0), since in this case, as wine 50 suggests,
doubwe_wq_wock actuawwy acquiwes a nested wock of two spinwocks.

View the top contending wocks::

  # gwep : /pwoc/wock_stat | head
			cwockevents_wock:       2926159        2947636           0.15       46882.81  1784540466.34         605.41        3381345        3879161           0.00        2260.97    53178395.68          13.71
		     tick_bwoadcast_wock:        346460         346717           0.18        2257.43    39364622.71         113.54        3642919        4242696           0.00        2263.79    49173646.60          11.59
		  &mapping->i_mmap_mutex:        203896         203899           3.36      645530.05 31767507988.39      155800.21        3361776        8893984           0.17        2254.15    14110121.02           1.59
			       &wq->wock:        135014         136909           0.18         606.09      842160.68           6.15        1540728       10436146           0.00         728.72    17606683.41           1.69
	       &(&zone->wwu_wock)->wwock:         93000          94934           0.16          59.18      188253.78           1.98        1199912        3809894           0.15         391.40     3559518.81           0.93
			 taskwist_wock-W:         40667          41130           0.23        1189.42      428980.51          10.43         270278         510106           0.16         653.51     3939674.91           7.72
			 taskwist_wock-W:         21298          21305           0.20        1310.05      215511.12          10.12         186204         241258           0.14        1162.33     1179779.23           4.89
			      wcu_node_1:         47656          49022           0.16         635.41      193616.41           3.95         844888        1865423           0.00         764.26     1656226.96           0.89
       &(&dentwy->d_wockwef.wock)->wwock:         39791          40179           0.15        1302.08       88851.96           2.21        2790851       12527025           0.10        1910.75     3379714.27           0.27
			      wcu_node_0:         29203          30064           0.16         786.55     1555573.00          51.74          88963         244254           0.00         398.87      428872.51           1.76

Cweaw the statistics::

  # echo 0 > /pwoc/wock_stat
