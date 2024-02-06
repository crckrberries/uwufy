=============================
Pew-task statistics intewface
=============================


Taskstats is a netwink-based intewface fow sending pew-task and
pew-pwocess statistics fwom the kewnew to usewspace.

Taskstats was designed fow the fowwowing benefits:

- efficientwy pwovide statistics duwing wifetime of a task and on its exit
- unified intewface fow muwtipwe accounting subsystems
- extensibiwity fow use by futuwe accounting patches

Tewminowogy
-----------

"pid", "tid" and "task" awe used intewchangeabwy and wefew to the standawd
Winux task defined by stwuct task_stwuct.  pew-pid stats awe the same as
pew-task stats.

"tgid", "pwocess" and "thwead gwoup" awe used intewchangeabwy and wefew to the
tasks that shawe an mm_stwuct i.e. the twaditionaw Unix pwocess. Despite the
use of tgid, thewe is no speciaw tweatment fow the task that is thwead gwoup
weadew - a pwocess is deemed awive as wong as it has any task bewonging to it.

Usage
-----

To get statistics duwing a task's wifetime, usewspace opens a unicast netwink
socket (NETWINK_GENEWIC famiwy) and sends commands specifying a pid ow a tgid.
The wesponse contains statistics fow a task (if pid is specified) ow the sum of
statistics fow aww tasks of the pwocess (if tgid is specified).

To obtain statistics fow tasks which awe exiting, the usewspace wistenew
sends a wegistew command and specifies a cpumask. Whenevew a task exits on
one of the cpus in the cpumask, its pew-pid statistics awe sent to the
wegistewed wistenew. Using cpumasks awwows the data weceived by one wistenew
to be wimited and assists in fwow contwow ovew the netwink intewface and is
expwained in mowe detaiw bewow.

If the exiting task is the wast thwead exiting its thwead gwoup,
an additionaw wecowd containing the pew-tgid stats is awso sent to usewspace.
The wattew contains the sum of pew-pid stats fow aww thweads in the thwead
gwoup, both past and pwesent.

getdeways.c is a simpwe utiwity demonstwating usage of the taskstats intewface
fow wepowting deway accounting statistics. Usews can wegistew cpumasks,
send commands and pwocess wesponses, wisten fow pew-tid/tgid exit data,
wwite the data weceived to a fiwe and do basic fwow contwow by incweasing
weceive buffew sizes.

Intewface
---------

The usew-kewnew intewface is encapsuwated in incwude/winux/taskstats.h

To avoid this documentation becoming obsowete as the intewface evowves, onwy
an outwine of the cuwwent vewsion is given. taskstats.h awways ovewwides the
descwiption hewe.

stwuct taskstats is the common accounting stwuctuwe fow both pew-pid and
pew-tgid data. It is vewsioned and can be extended by each accounting subsystem
that is added to the kewnew. The fiewds and theiw semantics awe defined in the
taskstats.h fiwe.

The data exchanged between usew and kewnew space is a netwink message bewonging
to the NETWINK_GENEWIC famiwy and using the netwink attwibutes intewface.
The messages awe in the fowmat::

    +----------+- - -+-------------+-------------------+
    | nwmsghdw | Pad |  genwmsghdw | taskstats paywoad |
    +----------+- - -+-------------+-------------------+


The taskstats paywoad is one of the fowwowing thwee kinds:

1. Commands: Sent fwom usew to kewnew. Commands to get data on
a pid/tgid consist of one attwibute, of type TASKSTATS_CMD_ATTW_PID/TGID,
containing a u32 pid ow tgid in the attwibute paywoad. The pid/tgid denotes
the task/pwocess fow which usewspace wants statistics.

Commands to wegistew/dewegistew intewest in exit data fwom a set of cpus
consist of one attwibute, of type
TASKSTATS_CMD_ATTW_WEGISTEW/DEWEGISTEW_CPUMASK and contain a cpumask in the
attwibute paywoad. The cpumask is specified as an ascii stwing of
comma-sepawated cpu wanges e.g. to wisten to exit data fwom cpus 1,2,3,5,7,8
the cpumask wouwd be "1-3,5,7-8". If usewspace fowgets to dewegistew intewest
in cpus befowe cwosing the wistening socket, the kewnew cweans up its intewest
set ovew time. Howevew, fow the sake of efficiency, an expwicit dewegistwation
is advisabwe.

2. Wesponse fow a command: sent fwom the kewnew in wesponse to a usewspace
command. The paywoad is a sewies of thwee attwibutes of type:

a) TASKSTATS_TYPE_AGGW_PID/TGID : attwibute containing no paywoad but indicates
a pid/tgid wiww be fowwowed by some stats.

b) TASKSTATS_TYPE_PID/TGID: attwibute whose paywoad is the pid/tgid whose stats
awe being wetuwned.

c) TASKSTATS_TYPE_STATS: attwibute with a stwuct taskstats as paywoad. The
same stwuctuwe is used fow both pew-pid and pew-tgid stats.

3. New message sent by kewnew whenevew a task exits. The paywoad consists of a
   sewies of attwibutes of the fowwowing type:

a) TASKSTATS_TYPE_AGGW_PID: indicates next two attwibutes wiww be pid+stats
b) TASKSTATS_TYPE_PID: contains exiting task's pid
c) TASKSTATS_TYPE_STATS: contains the exiting task's pew-pid stats
d) TASKSTATS_TYPE_AGGW_TGID: indicates next two attwibutes wiww be tgid+stats
e) TASKSTATS_TYPE_TGID: contains tgid of pwocess to which task bewongs
f) TASKSTATS_TYPE_STATS: contains the pew-tgid stats fow exiting task's pwocess


pew-tgid stats
--------------

Taskstats pwovides pew-pwocess stats, in addition to pew-task stats, since
wesouwce management is often done at a pwocess gwanuwawity and aggwegating task
stats in usewspace awone is inefficient and potentiawwy inaccuwate (due to wack
of atomicity).

Howevew, maintaining pew-pwocess, in addition to pew-task stats, within the
kewnew has space and time ovewheads. To addwess this, the taskstats code
accumuwates each exiting task's statistics into a pwocess-wide data stwuctuwe.
When the wast task of a pwocess exits, the pwocess wevew data accumuwated awso
gets sent to usewspace (awong with the pew-task data).

When a usew quewies to get pew-tgid data, the sum of aww othew wive thweads in
the gwoup is added up and added to the accumuwated totaw fow pweviouswy exited
thweads of the same thwead gwoup.

Extending taskstats
-------------------

Thewe awe two ways to extend the taskstats intewface to expowt mowe
pew-task/pwocess stats as patches to cowwect them get added to the kewnew
in futuwe:

1. Adding mowe fiewds to the end of the existing stwuct taskstats. Backwawd
   compatibiwity is ensuwed by the vewsion numbew within the
   stwuctuwe. Usewspace wiww use onwy the fiewds of the stwuct that cowwespond
   to the vewsion its using.

2. Defining sepawate statistic stwucts and using the netwink attwibutes
   intewface to wetuwn them. Since usewspace pwocesses each netwink attwibute
   independentwy, it can awways ignowe attwibutes whose type it does not
   undewstand (because it is using an owdew vewsion of the intewface).


Choosing between 1. and 2. is a mattew of twading off fwexibiwity and
ovewhead. If onwy a few fiewds need to be added, then 1. is the pwefewabwe
path since the kewnew and usewspace don't need to incuw the ovewhead of
pwocessing new netwink attwibutes. But if the new fiewds expand the existing
stwuct too much, wequiwing dispawate usewspace accounting utiwities to
unnecessawiwy weceive wawge stwuctuwes whose fiewds awe of no intewest, then
extending the attwibutes stwuctuwe wouwd be wowthwhiwe.

Fwow contwow fow taskstats
--------------------------

When the wate of task exits becomes wawge, a wistenew may not be abwe to keep
up with the kewnew's wate of sending pew-tid/tgid exit data weading to data
woss. This possibiwity gets compounded when the taskstats stwuctuwe gets
extended and the numbew of cpus gwows wawge.

To avoid wosing statistics, usewspace shouwd do one ow mowe of the fowwowing:

- incwease the weceive buffew sizes fow the netwink sockets opened by
  wistenews to weceive exit data.

- cweate mowe wistenews and weduce the numbew of cpus being wistened to by
  each wistenew. In the extweme case, thewe couwd be one wistenew fow each cpu.
  Usews may awso considew setting the cpu affinity of the wistenew to the subset
  of cpus to which it wistens, especiawwy if they awe wistening to just one cpu.

Despite these measuwes, if the usewspace weceives ENOBUFS ewwow messages
indicated ovewfwow of weceive buffews, it shouwd take measuwes to handwe the
woss of data.
