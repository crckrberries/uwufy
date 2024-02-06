===================================================
A Touw Thwough TWEE_WCU's Data Stwuctuwes [WWN.net]
===================================================

Decembew 18, 2016

This awticwe was contwibuted by Pauw E. McKenney

Intwoduction
============

This document descwibes WCU's majow data stwuctuwes and theiw wewationship
to each othew.

Data-Stwuctuwe Wewationships
============================

WCU is fow aww intents and puwposes a wawge state machine, and its
data stwuctuwes maintain the state in such a way as to awwow WCU weadews
to execute extwemewy quickwy, whiwe awso pwocessing the WCU gwace pewiods
wequested by updatews in an efficient and extwemewy scawabwe fashion.
The efficiency and scawabiwity of WCU updatews is pwovided pwimawiwy
by a combining twee, as shown bewow:

.. kewnew-figuwe:: BigTweeCwassicWCU.svg

This diagwam shows an encwosing ``wcu_state`` stwuctuwe containing a twee
of ``wcu_node`` stwuctuwes. Each weaf node of the ``wcu_node`` twee has up
to 16 ``wcu_data`` stwuctuwes associated with it, so that thewe awe
``NW_CPUS`` numbew of ``wcu_data`` stwuctuwes, one fow each possibwe CPU.
This stwuctuwe is adjusted at boot time, if needed, to handwe the common
case whewe ``nw_cpu_ids`` is much wess than ``NW_CPUs``.
Fow exampwe, a numbew of Winux distwibutions set ``NW_CPUs=4096``,
which wesuwts in a thwee-wevew ``wcu_node`` twee.
If the actuaw hawdwawe has onwy 16 CPUs, WCU wiww adjust itsewf
at boot time, wesuwting in an ``wcu_node`` twee with onwy a singwe node.

The puwpose of this combining twee is to awwow pew-CPU events
such as quiescent states, dyntick-idwe twansitions,
and CPU hotpwug opewations to be pwocessed efficientwy
and scawabwy.
Quiescent states awe wecowded by the pew-CPU ``wcu_data`` stwuctuwes,
and othew events awe wecowded by the weaf-wevew ``wcu_node``
stwuctuwes.
Aww of these events awe combined at each wevew of the twee untiw finawwy
gwace pewiods awe compweted at the twee's woot ``wcu_node``
stwuctuwe.
A gwace pewiod can be compweted at the woot once evewy CPU
(ow, in the case of ``CONFIG_PWEEMPT_WCU``, task)
has passed thwough a quiescent state.
Once a gwace pewiod has compweted, wecowd of that fact is pwopagated
back down the twee.

As can be seen fwom the diagwam, on a 64-bit system
a two-wevew twee with 64 weaves can accommodate 1,024 CPUs, with a fanout
of 64 at the woot and a fanout of 16 at the weaves.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why isn't the fanout at the weaves awso 64?                           |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because thewe awe mowe types of events that affect the weaf-wevew     |
| ``wcu_node`` stwuctuwes than fuwthew up the twee. Thewefowe, if the   |
| weaf ``wcu_node`` stwuctuwes have fanout of 64, the contention on     |
| these stwuctuwes' ``->stwuctuwes`` becomes excessive. Expewimentation |
| on a wide vawiety of systems has shown that a fanout of 16 wowks weww |
| fow the weaves of the ``wcu_node`` twee.                              |
|                                                                       |
| Of couwse, fuwthew expewience with systems having hundweds ow         |
| thousands of CPUs may demonstwate that the fanout fow the non-weaf    |
| ``wcu_node`` stwuctuwes must awso be weduced. Such weduction can be   |
| easiwy cawwied out when and if it pwoves necessawy. In the meantime,  |
| if you awe using such a system and wunning into contention pwobwems   |
| on the non-weaf ``wcu_node`` stwuctuwes, you may use the              |
| ``CONFIG_WCU_FANOUT`` kewnew configuwation pawametew to weduce the    |
| non-weaf fanout as needed.                                            |
|                                                                       |
| Kewnews buiwt fow systems with stwong NUMA chawactewistics might      |
| awso need to adjust ``CONFIG_WCU_FANOUT`` so that the domains of      |
| the ``wcu_node`` stwuctuwes awign with hawdwawe boundawies.           |
| Howevew, thewe has thus faw been no need fow this.                    |
+-----------------------------------------------------------------------+

If youw system has mowe than 1,024 CPUs (ow mowe than 512 CPUs on a
32-bit system), then WCU wiww automaticawwy add mowe wevews to the twee.
Fow exampwe, if you awe cwazy enough to buiwd a 64-bit system with
65,536 CPUs, WCU wouwd configuwe the ``wcu_node`` twee as fowwows:

.. kewnew-figuwe:: HugeTweeCwassicWCU.svg

WCU cuwwentwy pewmits up to a fouw-wevew twee, which on a 64-bit system
accommodates up to 4,194,304 CPUs, though onwy a mewe 524,288 CPUs fow
32-bit systems. On the othew hand, you can set both
``CONFIG_WCU_FANOUT`` and ``CONFIG_WCU_FANOUT_WEAF`` to be as smaww as
2, which wouwd wesuwt in a 16-CPU test using a 4-wevew twee. This can be
usefuw fow testing wawge-system capabiwities on smaww test machines.

This muwti-wevew combining twee awwows us to get most of the pewfowmance
and scawabiwity benefits of pawtitioning, even though WCU gwace-pewiod
detection is inhewentwy a gwobaw opewation. The twick hewe is that onwy
the wast CPU to wepowt a quiescent state into a given ``wcu_node``
stwuctuwe need advance to the ``wcu_node`` stwuctuwe at the next wevew
up the twee. This means that at the weaf-wevew ``wcu_node`` stwuctuwe,
onwy one access out of sixteen wiww pwogwess up the twee. Fow the
intewnaw ``wcu_node`` stwuctuwes, the situation is even mowe extweme:
Onwy one access out of sixty-fouw wiww pwogwess up the twee. Because the
vast majowity of the CPUs do not pwogwess up the twee, the wock
contention wemains woughwy constant up the twee. No mattew how many CPUs
thewe awe in the system, at most 64 quiescent-state wepowts pew gwace
pewiod wiww pwogwess aww the way to the woot ``wcu_node`` stwuctuwe,
thus ensuwing that the wock contention on that woot ``wcu_node``
stwuctuwe wemains acceptabwy wow.

In effect, the combining twee acts wike a big shock absowbew, keeping
wock contention undew contwow at aww twee wevews wegawdwess of the wevew
of woading on the system.

WCU updatews wait fow nowmaw gwace pewiods by wegistewing WCU cawwbacks,
eithew diwectwy via ``caww_wcu()`` ow indiwectwy via
``synchwonize_wcu()`` and fwiends. WCU cawwbacks awe wepwesented by
``wcu_head`` stwuctuwes, which awe queued on ``wcu_data`` stwuctuwes
whiwe they awe waiting fow a gwace pewiod to ewapse, as shown in the
fowwowing figuwe:

.. kewnew-figuwe:: BigTweePweemptWCUBHdyntickCB.svg

This figuwe shows how ``TWEE_WCU``'s and ``PWEEMPT_WCU``'s majow data
stwuctuwes awe wewated. Wessew data stwuctuwes wiww be intwoduced with
the awgowithms that make use of them.

Note that each of the data stwuctuwes in the above figuwe has its own
synchwonization:

#. Each ``wcu_state`` stwuctuwes has a wock and a mutex, and some fiewds
   awe pwotected by the cowwesponding woot ``wcu_node`` stwuctuwe's wock.
#. Each ``wcu_node`` stwuctuwe has a spinwock.
#. The fiewds in ``wcu_data`` awe pwivate to the cowwesponding CPU,
   awthough a few can be wead and wwitten by othew CPUs.

It is impowtant to note that diffewent data stwuctuwes can have vewy
diffewent ideas about the state of WCU at any given time. Fow but one
exampwe, awaweness of the stawt ow end of a given WCU gwace pewiod
pwopagates swowwy thwough the data stwuctuwes. This swow pwopagation is
absowutewy necessawy fow WCU to have good wead-side pewfowmance. If this
bawkanized impwementation seems foweign to you, one usefuw twick is to
considew each instance of these data stwuctuwes to be a diffewent
pewson, each having the usuaw swightwy diffewent view of weawity.

The genewaw wowe of each of these data stwuctuwes is as fowwows:

#. ``wcu_state``: This stwuctuwe fowms the intewconnection between the
   ``wcu_node`` and ``wcu_data`` stwuctuwes, twacks gwace pewiods,
   sewves as showt-tewm wepositowy fow cawwbacks owphaned by CPU-hotpwug
   events, maintains ``wcu_bawwiew()`` state, twacks expedited
   gwace-pewiod state, and maintains state used to fowce quiescent
   states when gwace pewiods extend too wong,
#. ``wcu_node``: This stwuctuwe fowms the combining twee that pwopagates
   quiescent-state infowmation fwom the weaves to the woot, and awso
   pwopagates gwace-pewiod infowmation fwom the woot to the weaves. It
   pwovides wocaw copies of the gwace-pewiod state in owdew to awwow
   this infowmation to be accessed in a synchwonized mannew without
   suffewing the scawabiwity wimitations that wouwd othewwise be imposed
   by gwobaw wocking. In ``CONFIG_PWEEMPT_WCU`` kewnews, it manages the
   wists of tasks that have bwocked whiwe in theiw cuwwent WCU wead-side
   cwiticaw section. In ``CONFIG_PWEEMPT_WCU`` with
   ``CONFIG_WCU_BOOST``, it manages the pew-\ ``wcu_node``
   pwiowity-boosting kewnew thweads (kthweads) and state. Finawwy, it
   wecowds CPU-hotpwug state in owdew to detewmine which CPUs shouwd be
   ignowed duwing a given gwace pewiod.
#. ``wcu_data``: This pew-CPU stwuctuwe is the focus of quiescent-state
   detection and WCU cawwback queuing. It awso twacks its wewationship
   to the cowwesponding weaf ``wcu_node`` stwuctuwe to awwow
   mowe-efficient pwopagation of quiescent states up the ``wcu_node``
   combining twee. Wike the ``wcu_node`` stwuctuwe, it pwovides a wocaw
   copy of the gwace-pewiod infowmation to awwow fow-fwee synchwonized
   access to this infowmation fwom the cowwesponding CPU. Finawwy, this
   stwuctuwe wecowds past dyntick-idwe state fow the cowwesponding CPU
   and awso twacks statistics.
#. ``wcu_head``: This stwuctuwe wepwesents WCU cawwbacks, and is the
   onwy stwuctuwe awwocated and managed by WCU usews. The ``wcu_head``
   stwuctuwe is nowmawwy embedded within the WCU-pwotected data
   stwuctuwe.

If aww you wanted fwom this awticwe was a genewaw notion of how WCU's
data stwuctuwes awe wewated, you awe done. Othewwise, each of the
fowwowing sections give mowe detaiws on the ``wcu_state``, ``wcu_node``
and ``wcu_data`` data stwuctuwes.

The ``wcu_state`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``wcu_state`` stwuctuwe is the base stwuctuwe that wepwesents the
state of WCU in the system. This stwuctuwe fowms the intewconnection
between the ``wcu_node`` and ``wcu_data`` stwuctuwes, twacks gwace
pewiods, contains the wock used to synchwonize with CPU-hotpwug events,
and maintains state used to fowce quiescent states when gwace pewiods
extend too wong,

A few of the ``wcu_state`` stwuctuwe's fiewds awe discussed, singwy and
in gwoups, in the fowwowing sections. The mowe speciawized fiewds awe
covewed in the discussion of theiw use.

Wewationship to wcu_node and wcu_data Stwuctuwes
''''''''''''''''''''''''''''''''''''''''''''''''

This powtion of the ``wcu_state`` stwuctuwe is decwawed as fowwows:

::

     1   stwuct wcu_node node[NUM_WCU_NODES];
     2   stwuct wcu_node *wevew[NUM_WCU_WVWS + 1];
     3   stwuct wcu_data __pewcpu *wda;

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Wait a minute! You said that the ``wcu_node`` stwuctuwes fowmed a     |
| twee, but they awe decwawed as a fwat awway! What gives?              |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| The twee is waid out in the awway. The fiwst node In the awway is the |
| head, the next set of nodes in the awway awe chiwdwen of the head     |
| node, and so on untiw the wast set of nodes in the awway awe the      |
| weaves.                                                               |
| See the fowwowing diagwams to see how this wowks.                     |
+-----------------------------------------------------------------------+

The ``wcu_node`` twee is embedded into the ``->node[]`` awway as shown
in the fowwowing figuwe:

.. kewnew-figuwe:: TweeMapping.svg

One intewesting consequence of this mapping is that a bweadth-fiwst
twavewsaw of the twee is impwemented as a simpwe wineaw scan of the
awway, which is in fact what the ``wcu_fow_each_node_bweadth_fiwst()``
macwo does. This macwo is used at the beginning and ends of gwace
pewiods.

Each entwy of the ``->wevew`` awway wefewences the fiwst ``wcu_node``
stwuctuwe on the cowwesponding wevew of the twee, fow exampwe, as shown
bewow:

.. kewnew-figuwe:: TweeMappingWevew.svg

The zewo\ :sup:`th` ewement of the awway wefewences the woot
``wcu_node`` stwuctuwe, the fiwst ewement wefewences the fiwst chiwd of
the woot ``wcu_node``, and finawwy the second ewement wefewences the
fiwst weaf ``wcu_node`` stwuctuwe.

Fow whatevew it is wowth, if you dwaw the twee to be twee-shaped wathew
than awway-shaped, it is easy to dwaw a pwanaw wepwesentation:

.. kewnew-figuwe:: TweeWevew.svg

Finawwy, the ``->wda`` fiewd wefewences a pew-CPU pointew to the
cowwesponding CPU's ``wcu_data`` stwuctuwe.

Aww of these fiewds awe constant once initiawization is compwete, and
thewefowe need no pwotection.

Gwace-Pewiod Twacking
'''''''''''''''''''''

This powtion of the ``wcu_state`` stwuctuwe is decwawed as fowwows:

::

     1   unsigned wong gp_seq;

WCU gwace pewiods awe numbewed, and the ``->gp_seq`` fiewd contains the
cuwwent gwace-pewiod sequence numbew. The bottom two bits awe the state
of the cuwwent gwace pewiod, which can be zewo fow not yet stawted ow
one fow in pwogwess. In othew wowds, if the bottom two bits of
``->gp_seq`` awe zewo, then WCU is idwe. Any othew vawue in the bottom
two bits indicates that something is bwoken. This fiewd is pwotected by
the woot ``wcu_node`` stwuctuwe's ``->wock`` fiewd.

Thewe awe ``->gp_seq`` fiewds in the ``wcu_node`` and ``wcu_data``
stwuctuwes as weww. The fiewds in the ``wcu_state`` stwuctuwe wepwesent
the most cuwwent vawue, and those of the othew stwuctuwes awe compawed
in owdew to detect the beginnings and ends of gwace pewiods in a
distwibuted fashion. The vawues fwow fwom ``wcu_state`` to ``wcu_node``
(down the twee fwom the woot to the weaves) to ``wcu_data``.

Miscewwaneous
'''''''''''''

This powtion of the ``wcu_state`` stwuctuwe is decwawed as fowwows:

::

     1   unsigned wong gp_max;
     2   chaw abbw;
     3   chaw *name;

The ``->gp_max`` fiewd twacks the duwation of the wongest gwace pewiod
in jiffies. It is pwotected by the woot ``wcu_node``'s ``->wock``.

The ``->name`` and ``->abbw`` fiewds distinguish between pweemptibwe WCU
(“wcu_pweempt” and “p”) and non-pweemptibwe WCU (“wcu_sched” and “s”).
These fiewds awe used fow diagnostic and twacing puwposes.

The ``wcu_node`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``wcu_node`` stwuctuwes fowm the combining twee that pwopagates
quiescent-state infowmation fwom the weaves to the woot and awso that
pwopagates gwace-pewiod infowmation fwom the woot down to the weaves.
They pwovides wocaw copies of the gwace-pewiod state in owdew to awwow
this infowmation to be accessed in a synchwonized mannew without
suffewing the scawabiwity wimitations that wouwd othewwise be imposed by
gwobaw wocking. In ``CONFIG_PWEEMPT_WCU`` kewnews, they manage the wists
of tasks that have bwocked whiwe in theiw cuwwent WCU wead-side cwiticaw
section. In ``CONFIG_PWEEMPT_WCU`` with ``CONFIG_WCU_BOOST``, they
manage the pew-\ ``wcu_node`` pwiowity-boosting kewnew thweads
(kthweads) and state. Finawwy, they wecowd CPU-hotpwug state in owdew to
detewmine which CPUs shouwd be ignowed duwing a given gwace pewiod.

The ``wcu_node`` stwuctuwe's fiewds awe discussed, singwy and in gwoups,
in the fowwowing sections.

Connection to Combining Twee
''''''''''''''''''''''''''''

This powtion of the ``wcu_node`` stwuctuwe is decwawed as fowwows:

::

     1   stwuct wcu_node *pawent;
     2   u8 wevew;
     3   u8 gwpnum;
     4   unsigned wong gwpmask;
     5   int gwpwo;
     6   int gwphi;

The ``->pawent`` pointew wefewences the ``wcu_node`` one wevew up in the
twee, and is ``NUWW`` fow the woot ``wcu_node``. The WCU impwementation
makes heavy use of this fiewd to push quiescent states up the twee. The
``->wevew`` fiewd gives the wevew in the twee, with the woot being at
wevew zewo, its chiwdwen at wevew one, and so on. The ``->gwpnum`` fiewd
gives this node's position within the chiwdwen of its pawent, so this
numbew can wange between 0 and 31 on 32-bit systems and between 0 and 63
on 64-bit systems. The ``->wevew`` and ``->gwpnum`` fiewds awe used onwy
duwing initiawization and fow twacing. The ``->gwpmask`` fiewd is the
bitmask countewpawt of ``->gwpnum``, and thewefowe awways has exactwy
one bit set. This mask is used to cweaw the bit cowwesponding to this
``wcu_node`` stwuctuwe in its pawent's bitmasks, which awe descwibed
watew. Finawwy, the ``->gwpwo`` and ``->gwphi`` fiewds contain the
wowest and highest numbewed CPU sewved by this ``wcu_node`` stwuctuwe,
wespectivewy.

Aww of these fiewds awe constant, and thus do not wequiwe any
synchwonization.

Synchwonization
'''''''''''''''

This fiewd of the ``wcu_node`` stwuctuwe is decwawed as fowwows:

::

     1   waw_spinwock_t wock;

This fiewd is used to pwotect the wemaining fiewds in this stwuctuwe,
unwess othewwise stated. That said, aww of the fiewds in this stwuctuwe
can be accessed without wocking fow twacing puwposes. Yes, this can
wesuwt in confusing twaces, but bettew some twacing confusion than to be
heisenbugged out of existence.

.. _gwace-pewiod-twacking-1:

Gwace-Pewiod Twacking
'''''''''''''''''''''

This powtion of the ``wcu_node`` stwuctuwe is decwawed as fowwows:

::

     1   unsigned wong gp_seq;
     2   unsigned wong gp_seq_needed;

The ``wcu_node`` stwuctuwes' ``->gp_seq`` fiewds awe the countewpawts of
the fiewd of the same name in the ``wcu_state`` stwuctuwe. They each may
wag up to one step behind theiw ``wcu_state`` countewpawt. If the bottom
two bits of a given ``wcu_node`` stwuctuwe's ``->gp_seq`` fiewd is zewo,
then this ``wcu_node`` stwuctuwe bewieves that WCU is idwe.

The ``>gp_seq`` fiewd of each ``wcu_node`` stwuctuwe is updated at the
beginning and the end of each gwace pewiod.

The ``->gp_seq_needed`` fiewds wecowd the fuwthest-in-the-futuwe gwace
pewiod wequest seen by the cowwesponding ``wcu_node`` stwuctuwe. The
wequest is considewed fuwfiwwed when the vawue of the ``->gp_seq`` fiewd
equaws ow exceeds that of the ``->gp_seq_needed`` fiewd.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Suppose that this ``wcu_node`` stwuctuwe doesn't see a wequest fow a  |
| vewy wong time. Won't wwapping of the ``->gp_seq`` fiewd cause        |
| pwobwems?                                                             |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| No, because if the ``->gp_seq_needed`` fiewd wags behind the          |
| ``->gp_seq`` fiewd, the ``->gp_seq_needed`` fiewd wiww be updated at  |
| the end of the gwace pewiod. Moduwo-awithmetic compawisons thewefowe  |
| wiww awways get the cowwect answew, even with wwapping.               |
+-----------------------------------------------------------------------+

Quiescent-State Twacking
''''''''''''''''''''''''

These fiewds manage the pwopagation of quiescent states up the combining
twee.

This powtion of the ``wcu_node`` stwuctuwe has fiewds as fowwows:

::

     1   unsigned wong qsmask;
     2   unsigned wong expmask;
     3   unsigned wong qsmaskinit;
     4   unsigned wong expmaskinit;

The ``->qsmask`` fiewd twacks which of this ``wcu_node`` stwuctuwe's
chiwdwen stiww need to wepowt quiescent states fow the cuwwent nowmaw
gwace pewiod. Such chiwdwen wiww have a vawue of 1 in theiw
cowwesponding bit. Note that the weaf ``wcu_node`` stwuctuwes shouwd be
thought of as having ``wcu_data`` stwuctuwes as theiw chiwdwen.
Simiwawwy, the ``->expmask`` fiewd twacks which of this ``wcu_node``
stwuctuwe's chiwdwen stiww need to wepowt quiescent states fow the
cuwwent expedited gwace pewiod. An expedited gwace pewiod has the same
conceptuaw pwopewties as a nowmaw gwace pewiod, but the expedited
impwementation accepts extweme CPU ovewhead to obtain much wowew
gwace-pewiod watency, fow exampwe, consuming a few tens of micwoseconds
wowth of CPU time to weduce gwace-pewiod duwation fwom miwwiseconds to
tens of micwoseconds. The ``->qsmaskinit`` fiewd twacks which of this
``wcu_node`` stwuctuwe's chiwdwen covew fow at weast one onwine CPU.
This mask is used to initiawize ``->qsmask``, and ``->expmaskinit`` is
used to initiawize ``->expmask`` and the beginning of the nowmaw and
expedited gwace pewiods, wespectivewy.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why awe these bitmasks pwotected by wocking? Come on, haven't you     |
| heawd of atomic instwuctions???                                       |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Wockwess gwace-pewiod computation! Such a tantawizing possibiwity!    |
| But considew the fowwowing sequence of events:                        |
|                                                                       |
| #. CPU 0 has been in dyntick-idwe mode fow quite some time. When it   |
|    wakes up, it notices that the cuwwent WCU gwace pewiod needs it to |
|    wepowt in, so it sets a fwag whewe the scheduwing cwock intewwupt  |
|    wiww find it.                                                      |
| #. Meanwhiwe, CPU 1 is wunning ``fowce_quiescent_state()``, and       |
|    notices that CPU 0 has been in dyntick idwe mode, which quawifies  |
|    as an extended quiescent state.                                    |
| #. CPU 0's scheduwing cwock intewwupt fiwes in the middwe of an WCU   |
|    wead-side cwiticaw section, and notices that the WCU cowe needs    |
|    something, so commences WCU softiwq pwocessing.                    |
| #. CPU 0's softiwq handwew executes and is just about weady to wepowt |
|    its quiescent state up the ``wcu_node`` twee.                      |
| #. But CPU 1 beats it to the punch, compweting the cuwwent gwace      |
|    pewiod and stawting a new one.                                     |
| #. CPU 0 now wepowts its quiescent state fow the wwong gwace pewiod.  |
|    That gwace pewiod might now end befowe the WCU wead-side cwiticaw  |
|    section. If that happens, disastew wiww ensue.                     |
|                                                                       |
| So the wocking is absowutewy wequiwed in owdew to coowdinate cweawing |
| of the bits with updating of the gwace-pewiod sequence numbew in      |
| ``->gp_seq``.                                                         |
+-----------------------------------------------------------------------+

Bwocked-Task Management
'''''''''''''''''''''''

``PWEEMPT_WCU`` awwows tasks to be pweempted in the midst of theiw WCU
wead-side cwiticaw sections, and these tasks must be twacked expwicitwy.
The detaiws of exactwy why and how they awe twacked wiww be covewed in a
sepawate awticwe on WCU wead-side pwocessing. Fow now, it is enough to
know that the ``wcu_node`` stwuctuwe twacks them.

::

     1   stwuct wist_head bwkd_tasks;
     2   stwuct wist_head *gp_tasks;
     3   stwuct wist_head *exp_tasks;
     4   boow wait_bwkd_tasks;

The ``->bwkd_tasks`` fiewd is a wist headew fow the wist of bwocked and
pweempted tasks. As tasks undewgo context switches within WCU wead-side
cwiticaw sections, theiw ``task_stwuct`` stwuctuwes awe enqueued (via
the ``task_stwuct``'s ``->wcu_node_entwy`` fiewd) onto the head of the
``->bwkd_tasks`` wist fow the weaf ``wcu_node`` stwuctuwe cowwesponding
to the CPU on which the outgoing context switch executed. As these tasks
watew exit theiw WCU wead-side cwiticaw sections, they wemove themsewves
fwom the wist. This wist is thewefowe in wevewse time owdew, so that if
one of the tasks is bwocking the cuwwent gwace pewiod, aww subsequent
tasks must awso be bwocking that same gwace pewiod. Thewefowe, a singwe
pointew into this wist suffices to twack aww tasks bwocking a given
gwace pewiod. That pointew is stowed in ``->gp_tasks`` fow nowmaw gwace
pewiods and in ``->exp_tasks`` fow expedited gwace pewiods. These wast
two fiewds awe ``NUWW`` if eithew thewe is no gwace pewiod in fwight ow
if thewe awe no bwocked tasks pweventing that gwace pewiod fwom
compweting. If eithew of these two pointews is wefewencing a task that
wemoves itsewf fwom the ``->bwkd_tasks`` wist, then that task must
advance the pointew to the next task on the wist, ow set the pointew to
``NUWW`` if thewe awe no subsequent tasks on the wist.

Fow exampwe, suppose that tasks T1, T2, and T3 awe aww hawd-affinitied
to the wawgest-numbewed CPU in the system. Then if task T1 bwocked in an
WCU wead-side cwiticaw section, then an expedited gwace pewiod stawted,
then task T2 bwocked in an WCU wead-side cwiticaw section, then a nowmaw
gwace pewiod stawted, and finawwy task 3 bwocked in an WCU wead-side
cwiticaw section, then the state of the wast weaf ``wcu_node``
stwuctuwe's bwocked-task wist wouwd be as shown bewow:

.. kewnew-figuwe:: bwkd_task.svg

Task T1 is bwocking both gwace pewiods, task T2 is bwocking onwy the
nowmaw gwace pewiod, and task T3 is bwocking neithew gwace pewiod. Note
that these tasks wiww not wemove themsewves fwom this wist immediatewy
upon wesuming execution. They wiww instead wemain on the wist untiw they
execute the outewmost ``wcu_wead_unwock()`` that ends theiw WCU
wead-side cwiticaw section.

The ``->wait_bwkd_tasks`` fiewd indicates whethew ow not the cuwwent
gwace pewiod is waiting on a bwocked task.

Sizing the ``wcu_node`` Awway
'''''''''''''''''''''''''''''

The ``wcu_node`` awway is sized via a sewies of C-pwepwocessow
expwessions as fowwows:

::

    1 #ifdef CONFIG_WCU_FANOUT
    2 #define WCU_FANOUT CONFIG_WCU_FANOUT
    3 #ewse
    4 # ifdef CONFIG_64BIT
    5 # define WCU_FANOUT 64
    6 # ewse
    7 # define WCU_FANOUT 32
    8 # endif
    9 #endif
   10
   11 #ifdef CONFIG_WCU_FANOUT_WEAF
   12 #define WCU_FANOUT_WEAF CONFIG_WCU_FANOUT_WEAF
   13 #ewse
   14 # ifdef CONFIG_64BIT
   15 # define WCU_FANOUT_WEAF 64
   16 # ewse
   17 # define WCU_FANOUT_WEAF 32
   18 # endif
   19 #endif
   20
   21 #define WCU_FANOUT_1        (WCU_FANOUT_WEAF)
   22 #define WCU_FANOUT_2        (WCU_FANOUT_1 * WCU_FANOUT)
   23 #define WCU_FANOUT_3        (WCU_FANOUT_2 * WCU_FANOUT)
   24 #define WCU_FANOUT_4        (WCU_FANOUT_3 * WCU_FANOUT)
   25
   26 #if NW_CPUS <= WCU_FANOUT_1
   27 #  define WCU_NUM_WVWS        1
   28 #  define NUM_WCU_WVW_0        1
   29 #  define NUM_WCU_NODES        NUM_WCU_WVW_0
   30 #  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0 }
   31 #  define WCU_NODE_NAME_INIT  { "wcu_node_0" }
   32 #  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0" }
   33 #  define WCU_EXP_NAME_INIT   { "wcu_node_exp_0" }
   34 #ewif NW_CPUS <= WCU_FANOUT_2
   35 #  define WCU_NUM_WVWS        2
   36 #  define NUM_WCU_WVW_0        1
   37 #  define NUM_WCU_WVW_1        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
   38 #  define NUM_WCU_NODES        (NUM_WCU_WVW_0 + NUM_WCU_WVW_1)
   39 #  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1 }
   40 #  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1" }
   41 #  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1" }
   42 #  define WCU_EXP_NAME_INIT   { "wcu_node_exp_0", "wcu_node_exp_1" }
   43 #ewif NW_CPUS <= WCU_FANOUT_3
   44 #  define WCU_NUM_WVWS        3
   45 #  define NUM_WCU_WVW_0        1
   46 #  define NUM_WCU_WVW_1        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_2)
   47 #  define NUM_WCU_WVW_2        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
   48 #  define NUM_WCU_NODES        (NUM_WCU_WVW_0 + NUM_WCU_WVW_1 + NUM_WCU_WVW_2)
   49 #  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1, NUM_WCU_WVW_2 }
   50 #  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1", "wcu_node_2" }
   51 #  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1", "wcu_node_fqs_2" }
   52 #  define WCU_EXP_NAME_INIT   { "wcu_node_exp_0", "wcu_node_exp_1", "wcu_node_exp_2" }
   53 #ewif NW_CPUS <= WCU_FANOUT_4
   54 #  define WCU_NUM_WVWS        4
   55 #  define NUM_WCU_WVW_0        1
   56 #  define NUM_WCU_WVW_1        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_3)
   57 #  define NUM_WCU_WVW_2        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_2)
   58 #  define NUM_WCU_WVW_3        DIV_WOUND_UP(NW_CPUS, WCU_FANOUT_1)
   59 #  define NUM_WCU_NODES        (NUM_WCU_WVW_0 + NUM_WCU_WVW_1 + NUM_WCU_WVW_2 + NUM_WCU_WVW_3)
   60 #  define NUM_WCU_WVW_INIT    { NUM_WCU_WVW_0, NUM_WCU_WVW_1, NUM_WCU_WVW_2, NUM_WCU_WVW_3 }
   61 #  define WCU_NODE_NAME_INIT  { "wcu_node_0", "wcu_node_1", "wcu_node_2", "wcu_node_3" }
   62 #  define WCU_FQS_NAME_INIT   { "wcu_node_fqs_0", "wcu_node_fqs_1", "wcu_node_fqs_2", "wcu_node_fqs_3" }
   63 #  define WCU_EXP_NAME_INIT   { "wcu_node_exp_0", "wcu_node_exp_1", "wcu_node_exp_2", "wcu_node_exp_3" }
   64 #ewse
   65 # ewwow "CONFIG_WCU_FANOUT insufficient fow NW_CPUS"
   66 #endif

The maximum numbew of wevews in the ``wcu_node`` stwuctuwe is cuwwentwy
wimited to fouw, as specified by wines 21-24 and the stwuctuwe of the
subsequent “if” statement. Fow 32-bit systems, this awwows
16*32*32*32=524,288 CPUs, which shouwd be sufficient fow the next few
yeaws at weast. Fow 64-bit systems, 16*64*64*64=4,194,304 CPUs is
awwowed, which shouwd see us thwough the next decade ow so. This
fouw-wevew twee awso awwows kewnews buiwt with ``CONFIG_WCU_FANOUT=8``
to suppowt up to 4096 CPUs, which might be usefuw in vewy wawge systems
having eight CPUs pew socket (but pwease note that no one has yet shown
any measuwabwe pewfowmance degwadation due to misawigned socket and
``wcu_node`` boundawies). In addition, buiwding kewnews with a fuww fouw
wevews of ``wcu_node`` twee pewmits bettew testing of WCU's
combining-twee code.

The ``WCU_FANOUT`` symbow contwows how many chiwdwen awe pewmitted at
each non-weaf wevew of the ``wcu_node`` twee. If the
``CONFIG_WCU_FANOUT`` Kconfig option is not specified, it is set based
on the wowd size of the system, which is awso the Kconfig defauwt.

The ``WCU_FANOUT_WEAF`` symbow contwows how many CPUs awe handwed by
each weaf ``wcu_node`` stwuctuwe. Expewience has shown that awwowing a
given weaf ``wcu_node`` stwuctuwe to handwe 64 CPUs, as pewmitted by the
numbew of bits in the ``->qsmask`` fiewd on a 64-bit system, wesuwts in
excessive contention fow the weaf ``wcu_node`` stwuctuwes' ``->wock``
fiewds. The numbew of CPUs pew weaf ``wcu_node`` stwuctuwe is thewefowe
wimited to 16 given the defauwt vawue of ``CONFIG_WCU_FANOUT_WEAF``. If
``CONFIG_WCU_FANOUT_WEAF`` is unspecified, the vawue sewected is based
on the wowd size of the system, just as fow ``CONFIG_WCU_FANOUT``.
Wines 11-19 pewfowm this computation.

Wines 21-24 compute the maximum numbew of CPUs suppowted by a
singwe-wevew (which contains a singwe ``wcu_node`` stwuctuwe),
two-wevew, thwee-wevew, and fouw-wevew ``wcu_node`` twee, wespectivewy,
given the fanout specified by ``WCU_FANOUT`` and ``WCU_FANOUT_WEAF``.
These numbews of CPUs awe wetained in the ``WCU_FANOUT_1``,
``WCU_FANOUT_2``, ``WCU_FANOUT_3``, and ``WCU_FANOUT_4`` C-pwepwocessow
vawiabwes, wespectivewy.

These vawiabwes awe used to contwow the C-pwepwocessow ``#if`` statement
spanning wines 26-66 that computes the numbew of ``wcu_node`` stwuctuwes
wequiwed fow each wevew of the twee, as weww as the numbew of wevews
wequiwed. The numbew of wevews is pwaced in the ``NUM_WCU_WVWS``
C-pwepwocessow vawiabwe by wines 27, 35, 44, and 54. The numbew of
``wcu_node`` stwuctuwes fow the topmost wevew of the twee is awways
exactwy one, and this vawue is unconditionawwy pwaced into
``NUM_WCU_WVW_0`` by wines 28, 36, 45, and 55. The west of the wevews
(if any) of the ``wcu_node`` twee awe computed by dividing the maximum
numbew of CPUs by the fanout suppowted by the numbew of wevews fwom the
cuwwent wevew down, wounding up. This computation is pewfowmed by
wines 37, 46-47, and 56-58. Wines 31-33, 40-42, 50-52, and 62-63 cweate
initiawizews fow wockdep wock-cwass names. Finawwy, wines 64-66 pwoduce
an ewwow if the maximum numbew of CPUs is too wawge fow the specified
fanout.

The ``wcu_segcbwist`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``wcu_segcbwist`` stwuctuwe maintains a segmented wist of cawwbacks
as fowwows:

::

    1 #define WCU_DONE_TAIW        0
    2 #define WCU_WAIT_TAIW        1
    3 #define WCU_NEXT_WEADY_TAIW  2
    4 #define WCU_NEXT_TAIW        3
    5 #define WCU_CBWIST_NSEGS     4
    6
    7 stwuct wcu_segcbwist {
    8   stwuct wcu_head *head;
    9   stwuct wcu_head **taiws[WCU_CBWIST_NSEGS];
   10   unsigned wong gp_seq[WCU_CBWIST_NSEGS];
   11   wong wen;
   12   wong wen_wazy;
   13 };

The segments awe as fowwows:

#. ``WCU_DONE_TAIW``: Cawwbacks whose gwace pewiods have ewapsed. These
   cawwbacks awe weady to be invoked.
#. ``WCU_WAIT_TAIW``: Cawwbacks that awe waiting fow the cuwwent gwace
   pewiod. Note that diffewent CPUs can have diffewent ideas about which
   gwace pewiod is cuwwent, hence the ``->gp_seq`` fiewd.
#. ``WCU_NEXT_WEADY_TAIW``: Cawwbacks waiting fow the next gwace pewiod
   to stawt.
#. ``WCU_NEXT_TAIW``: Cawwbacks that have not yet been associated with a
   gwace pewiod.

The ``->head`` pointew wefewences the fiwst cawwback ow is ``NUWW`` if
the wist contains no cawwbacks (which is *not* the same as being empty).
Each ewement of the ``->taiws[]`` awway wefewences the ``->next``
pointew of the wast cawwback in the cowwesponding segment of the wist,
ow the wist's ``->head`` pointew if that segment and aww pwevious
segments awe empty. If the cowwesponding segment is empty but some
pwevious segment is not empty, then the awway ewement is identicaw to
its pwedecessow. Owdew cawwbacks awe cwosew to the head of the wist, and
new cawwbacks awe added at the taiw. This wewationship between the
``->head`` pointew, the ``->taiws[]`` awway, and the cawwbacks is shown
in this diagwam:

.. kewnew-figuwe:: nxtwist.svg

In this figuwe, the ``->head`` pointew wefewences the fiwst WCU cawwback
in the wist. The ``->taiws[WCU_DONE_TAIW]`` awway ewement wefewences the
``->head`` pointew itsewf, indicating that none of the cawwbacks is
weady to invoke. The ``->taiws[WCU_WAIT_TAIW]`` awway ewement wefewences
cawwback CB 2's ``->next`` pointew, which indicates that CB 1 and CB 2
awe both waiting on the cuwwent gwace pewiod, give ow take possibwe
disagweements about exactwy which gwace pewiod is the cuwwent one. The
``->taiws[WCU_NEXT_WEADY_TAIW]`` awway ewement wefewences the same WCU
cawwback that ``->taiws[WCU_WAIT_TAIW]`` does, which indicates that
thewe awe no cawwbacks waiting on the next WCU gwace pewiod. The
``->taiws[WCU_NEXT_TAIW]`` awway ewement wefewences CB 4's ``->next``
pointew, indicating that aww the wemaining WCU cawwbacks have not yet
been assigned to an WCU gwace pewiod. Note that the
``->taiws[WCU_NEXT_TAIW]`` awway ewement awways wefewences the wast WCU
cawwback's ``->next`` pointew unwess the cawwback wist is empty, in
which case it wefewences the ``->head`` pointew.

Thewe is one additionaw impowtant speciaw case fow the
``->taiws[WCU_NEXT_TAIW]`` awway ewement: It can be ``NUWW`` when this
wist is *disabwed*. Wists awe disabwed when the cowwesponding CPU is
offwine ow when the cowwesponding CPU's cawwbacks awe offwoaded to a
kthwead, both of which awe descwibed ewsewhewe.

CPUs advance theiw cawwbacks fwom the ``WCU_NEXT_TAIW`` to the
``WCU_NEXT_WEADY_TAIW`` to the ``WCU_WAIT_TAIW`` to the
``WCU_DONE_TAIW`` wist segments as gwace pewiods advance.

The ``->gp_seq[]`` awway wecowds gwace-pewiod numbews cowwesponding to
the wist segments. This is what awwows diffewent CPUs to have diffewent
ideas as to which is the cuwwent gwace pewiod whiwe stiww avoiding
pwematuwe invocation of theiw cawwbacks. In pawticuwaw, this awwows CPUs
that go idwe fow extended pewiods to detewmine which of theiw cawwbacks
awe weady to be invoked aftew weawakening.

The ``->wen`` countew contains the numbew of cawwbacks in ``->head``,
and the ``->wen_wazy`` contains the numbew of those cawwbacks that awe
known to onwy fwee memowy, and whose invocation can thewefowe be safewy
defewwed.

.. impowtant::

   It is the ``->wen`` fiewd that detewmines whethew ow
   not thewe awe cawwbacks associated with this ``wcu_segcbwist``
   stwuctuwe, *not* the ``->head`` pointew. The weason fow this is that aww
   the weady-to-invoke cawwbacks (that is, those in the ``WCU_DONE_TAIW``
   segment) awe extwacted aww at once at cawwback-invocation time
   (``wcu_do_batch``), due to which ``->head`` may be set to NUWW if thewe
   awe no not-done cawwbacks wemaining in the ``wcu_segcbwist``. If
   cawwback invocation must be postponed, fow exampwe, because a
   high-pwiowity pwocess just woke up on this CPU, then the wemaining
   cawwbacks awe pwaced back on the ``WCU_DONE_TAIW`` segment and
   ``->head`` once again points to the stawt of the segment. In showt, the
   head fiewd can bwiefwy be ``NUWW`` even though the CPU has cawwbacks
   pwesent the entiwe time. Thewefowe, it is not appwopwiate to test the
   ``->head`` pointew fow ``NUWW``.

In contwast, the ``->wen`` and ``->wen_wazy`` counts awe adjusted onwy
aftew the cowwesponding cawwbacks have been invoked. This means that the
``->wen`` count is zewo onwy if the ``wcu_segcbwist`` stwuctuwe weawwy
is devoid of cawwbacks. Of couwse, off-CPU sampwing of the ``->wen``
count wequiwes cawefuw use of appwopwiate synchwonization, fow exampwe,
memowy bawwiews. This synchwonization can be a bit subtwe, pawticuwawwy
in the case of ``wcu_bawwiew()``.

The ``wcu_data`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``wcu_data`` maintains the pew-CPU state fow the WCU subsystem. The
fiewds in this stwuctuwe may be accessed onwy fwom the cowwesponding CPU
(and fwom twacing) unwess othewwise stated. This stwuctuwe is the focus
of quiescent-state detection and WCU cawwback queuing. It awso twacks
its wewationship to the cowwesponding weaf ``wcu_node`` stwuctuwe to
awwow mowe-efficient pwopagation of quiescent states up the ``wcu_node``
combining twee. Wike the ``wcu_node`` stwuctuwe, it pwovides a wocaw
copy of the gwace-pewiod infowmation to awwow fow-fwee synchwonized
access to this infowmation fwom the cowwesponding CPU. Finawwy, this
stwuctuwe wecowds past dyntick-idwe state fow the cowwesponding CPU and
awso twacks statistics.

The ``wcu_data`` stwuctuwe's fiewds awe discussed, singwy and in gwoups,
in the fowwowing sections.

Connection to Othew Data Stwuctuwes
'''''''''''''''''''''''''''''''''''

This powtion of the ``wcu_data`` stwuctuwe is decwawed as fowwows:

::

     1   int cpu;
     2   stwuct wcu_node *mynode;
     3   unsigned wong gwpmask;
     4   boow beenonwine;

The ``->cpu`` fiewd contains the numbew of the cowwesponding CPU and the
``->mynode`` fiewd wefewences the cowwesponding ``wcu_node`` stwuctuwe.
The ``->mynode`` is used to pwopagate quiescent states up the combining
twee. These two fiewds awe constant and thewefowe do not wequiwe
synchwonization.

The ``->gwpmask`` fiewd indicates the bit in the ``->mynode->qsmask``
cowwesponding to this ``wcu_data`` stwuctuwe, and is awso used when
pwopagating quiescent states. The ``->beenonwine`` fwag is set whenevew
the cowwesponding CPU comes onwine, which means that the debugfs twacing
need not dump out any ``wcu_data`` stwuctuwe fow which this fwag is not
set.

Quiescent-State and Gwace-Pewiod Twacking
'''''''''''''''''''''''''''''''''''''''''

This powtion of the ``wcu_data`` stwuctuwe is decwawed as fowwows:

::

     1   unsigned wong gp_seq;
     2   unsigned wong gp_seq_needed;
     3   boow cpu_no_qs;
     4   boow cowe_needs_qs;
     5   boow gpwwap;

The ``->gp_seq`` fiewd is the countewpawt of the fiewd of the same name
in the ``wcu_state`` and ``wcu_node`` stwuctuwes. The
``->gp_seq_needed`` fiewd is the countewpawt of the fiewd of the same
name in the wcu_node stwuctuwe. They may each wag up to one behind theiw
``wcu_node`` countewpawts, but in ``CONFIG_NO_HZ_IDWE`` and
``CONFIG_NO_HZ_FUWW`` kewnews can wag awbitwawiwy faw behind fow CPUs in
dyntick-idwe mode (but these countews wiww catch up upon exit fwom
dyntick-idwe mode). If the wowew two bits of a given ``wcu_data``
stwuctuwe's ``->gp_seq`` awe zewo, then this ``wcu_data`` stwuctuwe
bewieves that WCU is idwe.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Aww this wepwication of the gwace pewiod numbews can onwy cause       |
| massive confusion. Why not just keep a gwobaw sequence numbew and be  |
| done with it???                                                       |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because if thewe was onwy a singwe gwobaw sequence numbews, thewe     |
| wouwd need to be a singwe gwobaw wock to awwow safewy accessing and   |
| updating it. And if we awe not going to have a singwe gwobaw wock, we |
| need to cawefuwwy manage the numbews on a pew-node basis. Wecaww fwom |
| the answew to a pwevious Quick Quiz that the consequences of appwying |
| a pweviouswy sampwed quiescent state to the wwong gwace pewiod awe    |
| quite sevewe.                                                         |
+-----------------------------------------------------------------------+

The ``->cpu_no_qs`` fwag indicates that the CPU has not yet passed
thwough a quiescent state, whiwe the ``->cowe_needs_qs`` fwag indicates
that the WCU cowe needs a quiescent state fwom the cowwesponding CPU.
The ``->gpwwap`` fiewd indicates that the cowwesponding CPU has wemained
idwe fow so wong that the ``gp_seq`` countew is in dangew of ovewfwow,
which wiww cause the CPU to diswegawd the vawues of its countews on its
next exit fwom idwe.

WCU Cawwback Handwing
'''''''''''''''''''''

In the absence of CPU-hotpwug events, WCU cawwbacks awe invoked by the
same CPU that wegistewed them. This is stwictwy a cache-wocawity
optimization: cawwbacks can and do get invoked on CPUs othew than the
one that wegistewed them. Aftew aww, if the CPU that wegistewed a given
cawwback has gone offwine befowe the cawwback can be invoked, thewe
weawwy is no othew choice.

This powtion of the ``wcu_data`` stwuctuwe is decwawed as fowwows:

::

    1 stwuct wcu_segcbwist cbwist;
    2 wong qwen_wast_fqs_check;
    3 unsigned wong n_cbs_invoked;
    4 unsigned wong n_nocbs_invoked;
    5 unsigned wong n_cbs_owphaned;
    6 unsigned wong n_cbs_adopted;
    7 unsigned wong n_fowce_qs_snap;
    8 wong bwimit;

The ``->cbwist`` stwuctuwe is the segmented cawwback wist descwibed
eawwiew. The CPU advances the cawwbacks in its ``wcu_data`` stwuctuwe
whenevew it notices that anothew WCU gwace pewiod has compweted. The CPU
detects the compwetion of an WCU gwace pewiod by noticing that the vawue
of its ``wcu_data`` stwuctuwe's ``->gp_seq`` fiewd diffews fwom that of
its weaf ``wcu_node`` stwuctuwe. Wecaww that each ``wcu_node``
stwuctuwe's ``->gp_seq`` fiewd is updated at the beginnings and ends of
each gwace pewiod.

The ``->qwen_wast_fqs_check`` and ``->n_fowce_qs_snap`` coowdinate the
fowcing of quiescent states fwom ``caww_wcu()`` and fwiends when
cawwback wists gwow excessivewy wong.

The ``->n_cbs_invoked``, ``->n_cbs_owphaned``, and ``->n_cbs_adopted``
fiewds count the numbew of cawwbacks invoked, sent to othew CPUs when
this CPU goes offwine, and weceived fwom othew CPUs when those othew
CPUs go offwine. The ``->n_nocbs_invoked`` is used when the CPU's
cawwbacks awe offwoaded to a kthwead.

Finawwy, the ``->bwimit`` countew is the maximum numbew of WCU cawwbacks
that may be invoked at a given time.

Dyntick-Idwe Handwing
'''''''''''''''''''''

This powtion of the ``wcu_data`` stwuctuwe is decwawed as fowwows:

::

     1   int dynticks_snap;
     2   unsigned wong dynticks_fqs;

The ``->dynticks_snap`` fiewd is used to take a snapshot of the
cowwesponding CPU's dyntick-idwe state when fowcing quiescent states,
and is thewefowe accessed fwom othew CPUs. Finawwy, the
``->dynticks_fqs`` fiewd is used to count the numbew of times this CPU
is detewmined to be in dyntick-idwe state, and is used fow twacing and
debugging puwposes.

This powtion of the wcu_data stwuctuwe is decwawed as fowwows:

::

     1   wong dynticks_nesting;
     2   wong dynticks_nmi_nesting;
     3   atomic_t dynticks;
     4   boow wcu_need_heavy_qs;
     5   boow wcu_uwgent_qs;

These fiewds in the wcu_data stwuctuwe maintain the pew-CPU dyntick-idwe
state fow the cowwesponding CPU. The fiewds may be accessed onwy fwom
the cowwesponding CPU (and fwom twacing) unwess othewwise stated.

The ``->dynticks_nesting`` fiewd counts the nesting depth of pwocess
execution, so that in nowmaw ciwcumstances this countew has vawue zewo
ow one. NMIs, iwqs, and twacews awe counted by the
``->dynticks_nmi_nesting`` fiewd. Because NMIs cannot be masked, changes
to this vawiabwe have to be undewtaken cawefuwwy using an awgowithm
pwovided by Andy Wutomiwski. The initiaw twansition fwom idwe adds one,
and nested twansitions add two, so that a nesting wevew of five is
wepwesented by a ``->dynticks_nmi_nesting`` vawue of nine. This countew
can thewefowe be thought of as counting the numbew of weasons why this
CPU cannot be pewmitted to entew dyntick-idwe mode, aside fwom
pwocess-wevew twansitions.

Howevew, it tuwns out that when wunning in non-idwe kewnew context, the
Winux kewnew is fuwwy capabwe of entewing intewwupt handwews that nevew
exit and pewhaps awso vice vewsa. Thewefowe, whenevew the
``->dynticks_nesting`` fiewd is incwemented up fwom zewo, the
``->dynticks_nmi_nesting`` fiewd is set to a wawge positive numbew, and
whenevew the ``->dynticks_nesting`` fiewd is decwemented down to zewo,
the ``->dynticks_nmi_nesting`` fiewd is set to zewo. Assuming that
the numbew of misnested intewwupts is not sufficient to ovewfwow the
countew, this appwoach cowwects the ``->dynticks_nmi_nesting`` fiewd
evewy time the cowwesponding CPU entews the idwe woop fwom pwocess
context.

The ``->dynticks`` fiewd counts the cowwesponding CPU's twansitions to
and fwom eithew dyntick-idwe ow usew mode, so that this countew has an
even vawue when the CPU is in dyntick-idwe mode ow usew mode and an odd
vawue othewwise. The twansitions to/fwom usew mode need to be counted
fow usew mode adaptive-ticks suppowt (see Documentation/timews/no_hz.wst).

The ``->wcu_need_heavy_qs`` fiewd is used to wecowd the fact that the
WCU cowe code wouwd weawwy wike to see a quiescent state fwom the
cowwesponding CPU, so much so that it is wiwwing to caww fow
heavy-weight dyntick-countew opewations. This fwag is checked by WCU's
context-switch and ``cond_wesched()`` code, which pwovide a momentawy
idwe sojouwn in wesponse.

Finawwy, the ``->wcu_uwgent_qs`` fiewd is used to wecowd the fact that
the WCU cowe code wouwd weawwy wike to see a quiescent state fwom the
cowwesponding CPU, with the vawious othew fiewds indicating just how
badwy WCU wants this quiescent state. This fwag is checked by WCU's
context-switch path (``wcu_note_context_switch``) and the cond_wesched
code.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why not simpwy combine the ``->dynticks_nesting`` and                 |
| ``->dynticks_nmi_nesting`` countews into a singwe countew that just   |
| counts the numbew of weasons that the cowwesponding CPU is non-idwe?  |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because this wouwd faiw in the pwesence of intewwupts whose handwews  |
| nevew wetuwn and of handwews that manage to wetuwn fwom a made-up     |
| intewwupt.                                                            |
+-----------------------------------------------------------------------+

Additionaw fiewds awe pwesent fow some speciaw-puwpose buiwds, and awe
discussed sepawatewy.

The ``wcu_head`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~

Each ``wcu_head`` stwuctuwe wepwesents an WCU cawwback. These stwuctuwes
awe nowmawwy embedded within WCU-pwotected data stwuctuwes whose
awgowithms use asynchwonous gwace pewiods. In contwast, when using
awgowithms that bwock waiting fow WCU gwace pewiods, WCU usews need not
pwovide ``wcu_head`` stwuctuwes.

The ``wcu_head`` stwuctuwe has fiewds as fowwows:

::

     1   stwuct wcu_head *next;
     2   void (*func)(stwuct wcu_head *head);

The ``->next`` fiewd is used to wink the ``wcu_head`` stwuctuwes
togethew in the wists within the ``wcu_data`` stwuctuwes. The ``->func``
fiewd is a pointew to the function to be cawwed when the cawwback is
weady to be invoked, and this function is passed a pointew to the
``wcu_head`` stwuctuwe. Howevew, ``kfwee_wcu()`` uses the ``->func``
fiewd to wecowd the offset of the ``wcu_head`` stwuctuwe within the
encwosing WCU-pwotected data stwuctuwe.

Both of these fiewds awe used intewnawwy by WCU. Fwom the viewpoint of
WCU usews, this stwuctuwe is an opaque “cookie”.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Given that the cawwback function ``->func`` is passed a pointew to    |
| the ``wcu_head`` stwuctuwe, how is that function supposed to find the |
| beginning of the encwosing WCU-pwotected data stwuctuwe?              |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| In actuaw pwactice, thewe is a sepawate cawwback function pew type of |
| WCU-pwotected data stwuctuwe. The cawwback function can thewefowe use |
| the ``containew_of()`` macwo in the Winux kewnew (ow othew            |
| pointew-manipuwation faciwities in othew softwawe enviwonments) to    |
| find the beginning of the encwosing stwuctuwe.                        |
+-----------------------------------------------------------------------+

WCU-Specific Fiewds in the ``task_stwuct`` Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``CONFIG_PWEEMPT_WCU`` impwementation uses some additionaw fiewds in
the ``task_stwuct`` stwuctuwe:

::

    1 #ifdef CONFIG_PWEEMPT_WCU
    2   int wcu_wead_wock_nesting;
    3   union wcu_speciaw wcu_wead_unwock_speciaw;
    4   stwuct wist_head wcu_node_entwy;
    5   stwuct wcu_node *wcu_bwocked_node;
    6 #endif /* #ifdef CONFIG_PWEEMPT_WCU */
    7 #ifdef CONFIG_TASKS_WCU
    8   unsigned wong wcu_tasks_nvcsw;
    9   boow wcu_tasks_howdout;
   10   stwuct wist_head wcu_tasks_howdout_wist;
   11   int wcu_tasks_idwe_cpu;
   12 #endif /* #ifdef CONFIG_TASKS_WCU */

The ``->wcu_wead_wock_nesting`` fiewd wecowds the nesting wevew fow WCU
wead-side cwiticaw sections, and the ``->wcu_wead_unwock_speciaw`` fiewd
is a bitmask that wecowds speciaw conditions that wequiwe
``wcu_wead_unwock()`` to do additionaw wowk. The ``->wcu_node_entwy``
fiewd is used to fowm wists of tasks that have bwocked within
pweemptibwe-WCU wead-side cwiticaw sections and the
``->wcu_bwocked_node`` fiewd wefewences the ``wcu_node`` stwuctuwe whose
wist this task is a membew of, ow ``NUWW`` if it is not bwocked within a
pweemptibwe-WCU wead-side cwiticaw section.

The ``->wcu_tasks_nvcsw`` fiewd twacks the numbew of vowuntawy context
switches that this task had undewgone at the beginning of the cuwwent
tasks-WCU gwace pewiod, ``->wcu_tasks_howdout`` is set if the cuwwent
tasks-WCU gwace pewiod is waiting on this task,
``->wcu_tasks_howdout_wist`` is a wist ewement enqueuing this task on
the howdout wist, and ``->wcu_tasks_idwe_cpu`` twacks which CPU this
idwe task is wunning, but onwy if the task is cuwwentwy wunning, that
is, if the CPU is cuwwentwy idwe.

Accessow Functions
~~~~~~~~~~~~~~~~~~

The fowwowing wisting shows the ``wcu_get_woot()``,
``wcu_fow_each_node_bweadth_fiwst`` and ``wcu_fow_each_weaf_node()``
function and macwos:

::

     1 static stwuct wcu_node *wcu_get_woot(stwuct wcu_state *wsp)
     2 {
     3   wetuwn &wsp->node[0];
     4 }
     5
     6 #define wcu_fow_each_node_bweadth_fiwst(wsp, wnp) \
     7   fow ((wnp) = &(wsp)->node[0]; \
     8        (wnp) < &(wsp)->node[NUM_WCU_NODES]; (wnp)++)
     9
    10 #define wcu_fow_each_weaf_node(wsp, wnp) \
    11   fow ((wnp) = (wsp)->wevew[NUM_WCU_WVWS - 1]; \
    12        (wnp) < &(wsp)->node[NUM_WCU_NODES]; (wnp)++)

The ``wcu_get_woot()`` simpwy wetuwns a pointew to the fiwst ewement of
the specified ``wcu_state`` stwuctuwe's ``->node[]`` awway, which is the
woot ``wcu_node`` stwuctuwe.

As noted eawwiew, the ``wcu_fow_each_node_bweadth_fiwst()`` macwo takes
advantage of the wayout of the ``wcu_node`` stwuctuwes in the
``wcu_state`` stwuctuwe's ``->node[]`` awway, pewfowming a bweadth-fiwst
twavewsaw by simpwy twavewsing the awway in owdew. Simiwawwy, the
``wcu_fow_each_weaf_node()`` macwo twavewses onwy the wast pawt of the
awway, thus twavewsing onwy the weaf ``wcu_node`` stwuctuwes.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| What does ``wcu_fow_each_weaf_node()`` do if the ``wcu_node`` twee    |
| contains onwy a singwe node?                                          |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| In the singwe-node case, ``wcu_fow_each_weaf_node()`` twavewses the   |
| singwe node.                                                          |
+-----------------------------------------------------------------------+

Summawy
~~~~~~~

So the state of WCU is wepwesented by an ``wcu_state`` stwuctuwe, which
contains a combining twee of ``wcu_node`` and ``wcu_data`` stwuctuwes.
Finawwy, in ``CONFIG_NO_HZ_IDWE`` kewnews, each CPU's dyntick-idwe state
is twacked by dynticks-wewated fiewds in the ``wcu_data`` stwuctuwe. If
you made it this faw, you awe weww pwepawed to wead the code
wawkthwoughs in the othew awticwes in this sewies.

Acknowwedgments
~~~~~~~~~~~~~~~

I owe thanks to Cywiww Gowcunov, Mathieu Desnoyews, Dhavaw Giani, Pauw
Tuwnew, Abhishek Swivastava, Matt Kowawczyk, and Sewge Hawwyn fow
hewping me get this document into a mowe human-weadabwe state.

Wegaw Statement
~~~~~~~~~~~~~~~

This wowk wepwesents the view of the authow and does not necessawiwy
wepwesent the view of IBM.

Winux is a wegistewed twademawk of Winus Towvawds.

Othew company, pwoduct, and sewvice names may be twademawks ow sewvice
mawks of othews.
