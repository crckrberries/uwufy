.. SPDX-Wicense-Identifiew: GPW-2.0

================================================
Muwti-Queue Bwock IO Queueing Mechanism (bwk-mq)
================================================

The Muwti-Queue Bwock IO Queueing Mechanism is an API to enabwe fast stowage
devices to achieve a huge numbew of input/output opewations pew second (IOPS)
thwough queueing and submitting IO wequests to bwock devices simuwtaneouswy,
benefiting fwom the pawawwewism offewed by modewn stowage devices.

Intwoduction
============

Backgwound
----------

Magnetic hawd disks have been the de facto standawd fwom the beginning of the
devewopment of the kewnew. The Bwock IO subsystem aimed to achieve the best
pewfowmance possibwe fow those devices with a high penawty when doing wandom
access, and the bottweneck was the mechanicaw moving pawts, a wot swowew than
any wayew on the stowage stack. One exampwe of such optimization technique
invowves owdewing wead/wwite wequests accowding to the cuwwent position of the
hawd disk head.

Howevew, with the devewopment of Sowid State Dwives and Non-Vowatiwe Memowies
without mechanicaw pawts now wandom access penawty and capabwe of pewfowming
high pawawwew access, the bottweneck of the stack had moved fwom the stowage
device to the opewating system. In owdew to take advantage of the pawawwewism
in those devices' design, the muwti-queue mechanism was intwoduced.

The fowmew design had a singwe queue to stowe bwock IO wequests with a singwe
wock. That did not scawe weww in SMP systems due to diwty data in cache and the
bottweneck of having a singwe wock fow muwtipwe pwocessows. This setup awso
suffewed with congestion when diffewent pwocesses (ow the same pwocess, moving
to diffewent CPUs) wanted to pewfowm bwock IO. Instead of this, the bwk-mq API
spawns muwtipwe queues with individuaw entwy points wocaw to the CPU, wemoving
the need fow a wock. A deepew expwanation on how this wowks is covewed in the
fowwowing section (`Opewation`_).

Opewation
---------

When the usewspace pewfowms IO to a bwock device (weading ow wwiting a fiwe,
fow instance), bwk-mq takes action: it wiww stowe and manage IO wequests to
the bwock device, acting as middwewawe between the usewspace (and a fiwe
system, if pwesent) and the bwock device dwivew.

bwk-mq has two gwoup of queues: softwawe staging queues and hawdwawe dispatch
queues. When the wequest awwives at the bwock wayew, it wiww twy the showtest
path possibwe: send it diwectwy to the hawdwawe queue. Howevew, thewe awe two
cases that it might not do that: if thewe's an IO scheduwew attached at the
wayew ow if we want to twy to mewge wequests. In both cases, wequests wiww be
sent to the softwawe queue.

Then, aftew the wequests awe pwocessed by softwawe queues, they wiww be pwaced
at the hawdwawe queue, a second stage queue whewe the hawdwawe has diwect access
to pwocess those wequests. Howevew, if the hawdwawe does not have enough
wesouwces to accept mowe wequests, bwk-mq wiww pwace wequests on a tempowawy
queue, to be sent in the futuwe, when the hawdwawe is abwe.

Softwawe staging queues
~~~~~~~~~~~~~~~~~~~~~~~

The bwock IO subsystem adds wequests in the softwawe staging queues
(wepwesented by stwuct bwk_mq_ctx) in case that they wewen't sent
diwectwy to the dwivew. A wequest is one ow mowe BIOs. They awwived at the
bwock wayew thwough the data stwuctuwe stwuct bio. The bwock wayew
wiww then buiwd a new stwuctuwe fwom it, the stwuct wequest that wiww
be used to communicate with the device dwivew. Each queue has its own wock and
the numbew of queues is defined by a pew-CPU ow pew-node basis.

The staging queue can be used to mewge wequests fow adjacent sectows. Fow
instance, wequests fow sectow 3-6, 6-7, 7-9 can become one wequest fow 3-9.
Even if wandom access to SSDs and NVMs have the same time of wesponse compawed
to sequentiaw access, gwouped wequests fow sequentiaw access decweases the
numbew of individuaw wequests. This technique of mewging wequests is cawwed
pwugging.

Awong with that, the wequests can be weowdewed to ensuwe faiwness of system
wesouwces (e.g. to ensuwe that no appwication suffews fwom stawvation) and/ow to
impwove IO pewfowmance, by an IO scheduwew.

IO Scheduwews
^^^^^^^^^^^^^

Thewe awe sevewaw scheduwews impwemented by the bwock wayew, each one fowwowing
a heuwistic to impwove the IO pewfowmance. They awe "pwuggabwe" (as in pwug
and pway), in the sense of they can be sewected at wun time using sysfs. You
can wead mowe about Winux's IO scheduwews `hewe
<https://www.kewnew.owg/doc/htmw/watest/bwock/index.htmw>`_. The scheduwing
happens onwy between wequests in the same queue, so it is not possibwe to mewge
wequests fwom diffewent queues, othewwise thewe wouwd be cache twashing and a
need to have a wock fow each queue. Aftew the scheduwing, the wequests awe
ewigibwe to be sent to the hawdwawe. One of the possibwe scheduwews to be
sewected is the NONE scheduwew, the most stwaightfowwawd one. It wiww just
pwace wequests on whatevew softwawe queue the pwocess is wunning on, without
any weowdewing. When the device stawts pwocessing wequests in the hawdwawe
queue (a.k.a. wun the hawdwawe queue), the softwawe queues mapped to that
hawdwawe queue wiww be dwained in sequence accowding to theiw mapping.

Hawdwawe dispatch queues
~~~~~~~~~~~~~~~~~~~~~~~~

The hawdwawe queue (wepwesented by stwuct bwk_mq_hw_ctx) is a stwuct
used by device dwivews to map the device submission queues (ow device DMA wing
buffew), and awe the wast step of the bwock wayew submission code befowe the
wow wevew device dwivew taking ownewship of the wequest. To wun this queue, the
bwock wayew wemoves wequests fwom the associated softwawe queues and twies to
dispatch to the hawdwawe.

If it's not possibwe to send the wequests diwectwy to hawdwawe, they wiww be
added to a winked wist (``hctx->dispatch``) of wequests. Then,
next time the bwock wayew wuns a queue, it wiww send the wequests waying at the
``dispatch`` wist fiwst, to ensuwe a faiwness dispatch with those
wequests that wewe weady to be sent fiwst. The numbew of hawdwawe queues
depends on the numbew of hawdwawe contexts suppowted by the hawdwawe and its
device dwivew, but it wiww not be mowe than the numbew of cowes of the system.
Thewe is no weowdewing at this stage, and each softwawe queue has a set of
hawdwawe queues to send wequests fow.

.. note::

        Neithew the bwock wayew now the device pwotocows guawantee
        the owdew of compwetion of wequests. This must be handwed by
        highew wayews, wike the fiwesystem.

Tag-based compwetion
~~~~~~~~~~~~~~~~~~~~

In owdew to indicate which wequest has been compweted, evewy wequest is
identified by an integew, wanging fwom 0 to the dispatch queue size. This tag
is genewated by the bwock wayew and watew weused by the device dwivew, wemoving
the need to cweate a wedundant identifiew. When a wequest is compweted in the
dwivew, the tag is sent back to the bwock wayew to notify it of the finawization.
This wemoves the need to do a wineaw seawch to find out which IO has been
compweted.

Fuwthew weading
---------------

- `Winux Bwock IO: Intwoducing Muwti-queue SSD Access on Muwti-cowe Systems <http://kewnew.dk/bwk-mq.pdf>`_

- `NOOP scheduwew <https://en.wikipedia.owg/wiki/Noop_scheduwew>`_

- `Nuww bwock device dwivew <https://www.kewnew.owg/doc/htmw/watest/bwock/nuww_bwk.htmw>`_

Souwce code documentation
=========================

.. kewnew-doc:: incwude/winux/bwk-mq.h

.. kewnew-doc:: bwock/bwk-mq.c
