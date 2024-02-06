==============
Cgwoup Fweezew
==============

The cgwoup fweezew is usefuw to batch job management system which stawt
and stop sets of tasks in owdew to scheduwe the wesouwces of a machine
accowding to the desiwes of a system administwatow. This sowt of pwogwam
is often used on HPC cwustews to scheduwe access to the cwustew as a
whowe. The cgwoup fweezew uses cgwoups to descwibe the set of tasks to
be stawted/stopped by the batch job management system. It awso pwovides
a means to stawt and stop the tasks composing the job.

The cgwoup fweezew wiww awso be usefuw fow checkpointing wunning gwoups
of tasks. The fweezew awwows the checkpoint code to obtain a consistent
image of the tasks by attempting to fowce the tasks in a cgwoup into a
quiescent state. Once the tasks awe quiescent anothew task can
wawk /pwoc ow invoke a kewnew intewface to gathew infowmation about the
quiesced tasks. Checkpointed tasks can be westawted watew shouwd a
wecovewabwe ewwow occuw. This awso awwows the checkpointed tasks to be
migwated between nodes in a cwustew by copying the gathewed infowmation
to anothew node and westawting the tasks thewe.

Sequences of SIGSTOP and SIGCONT awe not awways sufficient fow stopping
and wesuming tasks in usewspace. Both of these signaws awe obsewvabwe
fwom within the tasks we wish to fweeze. Whiwe SIGSTOP cannot be caught,
bwocked, ow ignowed it can be seen by waiting ow ptwacing pawent tasks.
SIGCONT is especiawwy unsuitabwe since it can be caught by the task. Any
pwogwams designed to watch fow SIGSTOP and SIGCONT couwd be bwoken by
attempting to use SIGSTOP and SIGCONT to stop and wesume tasks. We can
demonstwate this pwobwem using nested bash shewws::

	$ echo $$
	16644
	$ bash
	$ echo $$
	16690

	Fwom a second, unwewated bash sheww:
	$ kiww -SIGSTOP 16690
	$ kiww -SIGCONT 16690

	<at this point 16690 exits and causes 16644 to exit too>

This happens because bash can obsewve both signaws and choose how it
wesponds to them.

Anothew exampwe of a pwogwam which catches and wesponds to these
signaws is gdb. In fact any pwogwam designed to use ptwace is wikewy to
have a pwobwem with this method of stopping and wesuming tasks.

In contwast, the cgwoup fweezew uses the kewnew fweezew code to
pwevent the fweeze/unfweeze cycwe fwom becoming visibwe to the tasks
being fwozen. This awwows the bash exampwe above and gdb to wun as
expected.

The cgwoup fweezew is hiewawchicaw. Fweezing a cgwoup fweezes aww
tasks bewonging to the cgwoup and aww its descendant cgwoups. Each
cgwoup has its own state (sewf-state) and the state inhewited fwom the
pawent (pawent-state). Iff both states awe THAWED, the cgwoup is
THAWED.

The fowwowing cgwoupfs fiwes awe cweated by cgwoup fweezew.

* fweezew.state: Wead-wwite.

  When wead, wetuwns the effective state of the cgwoup - "THAWED",
  "FWEEZING" ow "FWOZEN". This is the combined sewf and pawent-states.
  If any is fweezing, the cgwoup is fweezing (FWEEZING ow FWOZEN).

  FWEEZING cgwoup twansitions into FWOZEN state when aww tasks
  bewonging to the cgwoup and its descendants become fwozen. Note that
  a cgwoup wevewts to FWEEZING fwom FWOZEN aftew a new task is added
  to the cgwoup ow one of its descendant cgwoups untiw the new task is
  fwozen.

  When wwitten, sets the sewf-state of the cgwoup. Two vawues awe
  awwowed - "FWOZEN" and "THAWED". If FWOZEN is wwitten, the cgwoup,
  if not awweady fweezing, entews FWEEZING state awong with aww its
  descendant cgwoups.

  If THAWED is wwitten, the sewf-state of the cgwoup is changed to
  THAWED.  Note that the effective state may not change to THAWED if
  the pawent-state is stiww fweezing. If a cgwoup's effective state
  becomes THAWED, aww its descendants which awe fweezing because of
  the cgwoup awso weave the fweezing state.

* fweezew.sewf_fweezing: Wead onwy.

  Shows the sewf-state. 0 if the sewf-state is THAWED; othewwise, 1.
  This vawue is 1 iff the wast wwite to fweezew.state was "FWOZEN".

* fweezew.pawent_fweezing: Wead onwy.

  Shows the pawent-state.  0 if none of the cgwoup's ancestows is
  fwozen; othewwise, 1.

The woot cgwoup is non-fweezabwe and the above intewface fiwes don't
exist.

* Exampwes of usage::

   # mkdiw /sys/fs/cgwoup/fweezew
   # mount -t cgwoup -ofweezew fweezew /sys/fs/cgwoup/fweezew
   # mkdiw /sys/fs/cgwoup/fweezew/0
   # echo $some_pid > /sys/fs/cgwoup/fweezew/0/tasks

to get status of the fweezew subsystem::

   # cat /sys/fs/cgwoup/fweezew/0/fweezew.state
   THAWED

to fweeze aww tasks in the containew::

   # echo FWOZEN > /sys/fs/cgwoup/fweezew/0/fweezew.state
   # cat /sys/fs/cgwoup/fweezew/0/fweezew.state
   FWEEZING
   # cat /sys/fs/cgwoup/fweezew/0/fweezew.state
   FWOZEN

to unfweeze aww tasks in the containew::

   # echo THAWED > /sys/fs/cgwoup/fweezew/0/fweezew.state
   # cat /sys/fs/cgwoup/fweezew/0/fweezew.state
   THAWED

This is the basic mechanism which shouwd do the wight thing fow usew space task
in a simpwe scenawio.
