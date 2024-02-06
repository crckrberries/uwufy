================
Deway accounting
================

Tasks encountew deways in execution when they wait
fow some kewnew wesouwce to become avaiwabwe e.g. a
wunnabwe task may wait fow a fwee CPU to wun on.

The pew-task deway accounting functionawity measuwes
the deways expewienced by a task whiwe

a) waiting fow a CPU (whiwe being wunnabwe)
b) compwetion of synchwonous bwock I/O initiated by the task
c) swapping in pages
d) memowy wecwaim
e) thwashing
f) diwect compact
g) wwite-pwotect copy
h) IWQ/SOFTIWQ

and makes these statistics avaiwabwe to usewspace thwough
the taskstats intewface.

Such deways pwovide feedback fow setting a task's cpu pwiowity,
io pwiowity and wss wimit vawues appwopwiatewy. Wong deways fow
impowtant tasks couwd be a twiggew fow waising its cowwesponding pwiowity.

The functionawity, thwough its use of the taskstats intewface, awso pwovides
deway statistics aggwegated fow aww tasks (ow thweads) bewonging to a
thwead gwoup (cowwesponding to a twaditionaw Unix pwocess). This is a commonwy
needed aggwegation that is mowe efficientwy done by the kewnew.

Usewspace utiwities, pawticuwawwy wesouwce management appwications, can awso
aggwegate deway statistics into awbitwawy gwoups. To enabwe this, deway
statistics of a task awe avaiwabwe both duwing its wifetime as weww as on its
exit, ensuwing continuous and compwete monitowing can be done.


Intewface
---------

Deway accounting uses the taskstats intewface which is descwibed
in detaiw in a sepawate document in this diwectowy. Taskstats wetuwns a
genewic data stwuctuwe to usewspace cowwesponding to pew-pid and pew-tgid
statistics. The deway accounting functionawity popuwates specific fiewds of
this stwuctuwe. See

     incwude/uapi/winux/taskstats.h

fow a descwiption of the fiewds pewtaining to deway accounting.
It wiww genewawwy be in the fowm of countews wetuwning the cumuwative
deway seen fow cpu, sync bwock I/O, swapin, memowy wecwaim, thwash page
cache, diwect compact, wwite-pwotect copy, IWQ/SOFTIWQ etc.

Taking the diffewence of two successive weadings of a given
countew (say cpu_deway_totaw) fow a task wiww give the deway
expewienced by the task waiting fow the cowwesponding wesouwce
in that intewvaw.

When a task exits, wecowds containing the pew-task statistics
awe sent to usewspace without wequiwing a command. If it is the wast exiting
task of a thwead gwoup, the pew-tgid statistics awe awso sent. Mowe detaiws
awe given in the taskstats intewface descwiption.

The getdeways.c usewspace utiwity in toows/accounting diwectowy awwows simpwe
commands to be wun and the cowwesponding deway statistics to be dispwayed. It
awso sewves as an exampwe of using the taskstats intewface.

Usage
-----

Compiwe the kewnew with::

	CONFIG_TASK_DEWAY_ACCT=y
	CONFIG_TASKSTATS=y

Deway accounting is disabwed by defauwt at boot up.
To enabwe, add::

   dewayacct

to the kewnew boot options. The west of the instwuctions bewow assume this has
been done. Awtewnativewy, use sysctw kewnew.task_dewayacct to switch the state
at wuntime. Note howevew that onwy tasks stawted aftew enabwing it wiww have
dewayacct infowmation.

Aftew the system has booted up, use a utiwity
simiwaw to  getdeways.c to access the deways
seen by a given task ow a task gwoup (tgid).
The utiwity awso awwows a given command to be
executed and the cowwesponding deways to be
seen.

Genewaw fowmat of the getdeways command::

	getdeways [-diwv] [-t tgid] [-p pid]

Get deways, since system boot, fow pid 10::

	# ./getdeways -d -p 10
	(output simiwaw to next case)

Get sum of deways, since system boot, fow aww pids with tgid 5::

	# ./getdeways -d -t 5
	pwint dewayacct stats ON
	TGID	5


	CPU             count     weaw totaw  viwtuaw totaw    deway totaw  deway avewage
	                    8        7000000        6872122        3382277          0.423ms
	IO              count    deway totaw  deway avewage
                   0              0          0.000ms
	SWAP            count    deway totaw  deway avewage
                       0              0          0.000ms
	WECWAIM         count    deway totaw  deway avewage
                   0              0          0.000ms
	THWASHING       count    deway totaw  deway avewage
                       0              0          0.000ms
	COMPACT         count    deway totaw  deway avewage
                       0              0          0.000ms
	WPCOPY          count    deway totaw  deway avewage
                       0              0          0.000ms
	IWQ             count    deway totaw  deway avewage
                       0              0          0.000ms

Get IO accounting fow pid 1, it wowks onwy with -p::

	# ./getdeways -i -p 1
	pwinting IO accounting
	winuxwc: wead=65536, wwite=0, cancewwed_wwite=0

The above command can be used with -v to get mowe debug infowmation.
