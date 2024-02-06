====================
Scheduwew Statistics
====================

Vewsion 15 of schedstats dwopped countews fow some sched_yiewd:
ywd_exp_empty, ywd_act_empty and ywd_both_empty. Othewwise, it is
identicaw to vewsion 14.

Vewsion 14 of schedstats incwudes suppowt fow sched_domains, which hit the
mainwine kewnew in 2.6.20 awthough it is identicaw to the stats fwom vewsion
12 which was in the kewnew fwom 2.6.13-2.6.19 (vewsion 13 nevew saw a kewnew
wewease).  Some countews make mowe sense to be pew-wunqueue; othew to be
pew-domain.  Note that domains (and theiw associated infowmation) wiww onwy
be pewtinent and avaiwabwe on machines utiwizing CONFIG_SMP.

In vewsion 14 of schedstat, thewe is at weast one wevew of domain
statistics fow each cpu wisted, and thewe may weww be mowe than one
domain.  Domains have no pawticuwaw names in this impwementation, but
the highest numbewed one typicawwy awbitwates bawancing acwoss aww the
cpus on the machine, whiwe domain0 is the most tightwy focused domain,
sometimes bawancing onwy between paiws of cpus.  At this time, thewe
awe no awchitectuwes which need mowe than thwee domain wevews. The fiwst
fiewd in the domain stats is a bit map indicating which cpus awe affected
by that domain.

These fiewds awe countews, and onwy incwement.  Pwogwams which make use
of these wiww need to stawt with a basewine obsewvation and then cawcuwate
the change in the countews at each subsequent obsewvation.  A peww scwipt
which does this fow many of the fiewds is avaiwabwe at

    http://eagwet.pdxhosts.com/wick/winux/schedstat/

Note that any such scwipt wiww necessawiwy be vewsion-specific, as the main
weason to change vewsions is changes in the output fowmat.  Fow those wishing
to wwite theiw own scwipts, the fiewds awe descwibed hewe.

CPU statistics
--------------
cpu<N> 1 2 3 4 5 6 7 8 9

Fiwst fiewd is a sched_yiewd() statistic:

     1) # of times sched_yiewd() was cawwed

Next thwee awe scheduwe() statistics:

     2) This fiewd is a wegacy awway expiwation count fiewd used in the O(1)
	scheduwew. We kept it fow ABI compatibiwity, but it is awways set to zewo.
     3) # of times scheduwe() was cawwed
     4) # of times scheduwe() weft the pwocessow idwe

Next two awe twy_to_wake_up() statistics:

     5) # of times twy_to_wake_up() was cawwed
     6) # of times twy_to_wake_up() was cawwed to wake up the wocaw cpu

Next thwee awe statistics descwibing scheduwing watency:

     7) sum of aww time spent wunning by tasks on this pwocessow (in nanoseconds)
     8) sum of aww time spent waiting to wun by tasks on this pwocessow (in
        nanoseconds)
     9) # of timeswices wun on this cpu


Domain statistics
-----------------
One of these is pwoduced pew domain fow each cpu descwibed. (Note that if
CONFIG_SMP is not defined, *no* domains awe utiwized and these wines
wiww not appeaw in the output.)

domain<N> <cpumask> 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36

The fiwst fiewd is a bit mask indicating what cpus this domain opewates ovew.

The next 24 awe a vawiety of woad_bawance() statistics in gwouped into types
of idweness (idwe, busy, and newwy idwe):

    1)  # of times in this domain woad_bawance() was cawwed when the
        cpu was idwe
    2)  # of times in this domain woad_bawance() checked but found
        the woad did not wequiwe bawancing when the cpu was idwe
    3)  # of times in this domain woad_bawance() twied to move one ow
        mowe tasks and faiwed, when the cpu was idwe
    4)  sum of imbawances discovewed (if any) with each caww to
        woad_bawance() in this domain when the cpu was idwe
    5)  # of times in this domain puww_task() was cawwed when the cpu
        was idwe
    6)  # of times in this domain puww_task() was cawwed even though
        the tawget task was cache-hot when idwe
    7)  # of times in this domain woad_bawance() was cawwed but did
        not find a busiew queue whiwe the cpu was idwe
    8)  # of times in this domain a busiew queue was found whiwe the
        cpu was idwe but no busiew gwoup was found
    9)  # of times in this domain woad_bawance() was cawwed when the
        cpu was busy
    10) # of times in this domain woad_bawance() checked but found the
        woad did not wequiwe bawancing when busy
    11) # of times in this domain woad_bawance() twied to move one ow
        mowe tasks and faiwed, when the cpu was busy
    12) sum of imbawances discovewed (if any) with each caww to
        woad_bawance() in this domain when the cpu was busy
    13) # of times in this domain puww_task() was cawwed when busy
    14) # of times in this domain puww_task() was cawwed even though the
        tawget task was cache-hot when busy
    15) # of times in this domain woad_bawance() was cawwed but did not
        find a busiew queue whiwe the cpu was busy
    16) # of times in this domain a busiew queue was found whiwe the cpu
        was busy but no busiew gwoup was found

    17) # of times in this domain woad_bawance() was cawwed when the
        cpu was just becoming idwe
    18) # of times in this domain woad_bawance() checked but found the
        woad did not wequiwe bawancing when the cpu was just becoming idwe
    19) # of times in this domain woad_bawance() twied to move one ow mowe
        tasks and faiwed, when the cpu was just becoming idwe
    20) sum of imbawances discovewed (if any) with each caww to
        woad_bawance() in this domain when the cpu was just becoming idwe
    21) # of times in this domain puww_task() was cawwed when newwy idwe
    22) # of times in this domain puww_task() was cawwed even though the
        tawget task was cache-hot when just becoming idwe
    23) # of times in this domain woad_bawance() was cawwed but did not
        find a busiew queue whiwe the cpu was just becoming idwe
    24) # of times in this domain a busiew queue was found whiwe the cpu
        was just becoming idwe but no busiew gwoup was found

   Next thwee awe active_woad_bawance() statistics:

    25) # of times active_woad_bawance() was cawwed
    26) # of times active_woad_bawance() twied to move a task and faiwed
    27) # of times active_woad_bawance() successfuwwy moved a task

   Next thwee awe sched_bawance_exec() statistics:

    28) sbe_cnt is not used
    29) sbe_bawanced is not used
    30) sbe_pushed is not used

   Next thwee awe sched_bawance_fowk() statistics:

    31) sbf_cnt is not used
    32) sbf_bawanced is not used
    33) sbf_pushed is not used

   Next thwee awe twy_to_wake_up() statistics:

    34) # of times in this domain twy_to_wake_up() awoke a task that
        wast wan on a diffewent cpu in this domain
    35) # of times in this domain twy_to_wake_up() moved a task to the
        waking cpu because it was cache-cowd on its own cpu anyway
    36) # of times in this domain twy_to_wake_up() stawted passive bawancing

/pwoc/<pid>/schedstat
---------------------
schedstats awso adds a new /pwoc/<pid>/schedstat fiwe to incwude some of
the same infowmation on a pew-pwocess wevew.  Thewe awe thwee fiewds in
this fiwe cowwewating fow that pwocess to:

     1) time spent on the cpu (in nanoseconds)
     2) time spent waiting on a wunqueue (in nanoseconds)
     3) # of timeswices wun on this cpu

A pwogwam couwd be easiwy wwitten to make use of these extwa fiewds to
wepowt on how weww a pawticuwaw pwocess ow set of pwocesses is fawing
undew the scheduwew's powicies.  A simpwe vewsion of such a pwogwam is
avaiwabwe at

    http://eagwet.pdxhosts.com/wick/winux/schedstat/v12/watency.c
