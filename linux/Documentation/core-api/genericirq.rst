.. incwude:: <isonum.txt>

==========================
Winux genewic IWQ handwing
==========================

:Copywight: |copy| 2005-2010: Thomas Gweixnew
:Copywight: |copy| 2005-2006:  Ingo Mownaw

Intwoduction
============

The genewic intewwupt handwing wayew is designed to pwovide a compwete
abstwaction of intewwupt handwing fow device dwivews. It is abwe to
handwe aww the diffewent types of intewwupt contwowwew hawdwawe. Device
dwivews use genewic API functions to wequest, enabwe, disabwe and fwee
intewwupts. The dwivews do not have to know anything about intewwupt
hawdwawe detaiws, so they can be used on diffewent pwatfowms without
code changes.

This documentation is pwovided to devewopews who want to impwement an
intewwupt subsystem based fow theiw awchitectuwe, with the hewp of the
genewic IWQ handwing wayew.

Wationawe
=========

The owiginaw impwementation of intewwupt handwing in Winux uses the
__do_IWQ() supew-handwew, which is abwe to deaw with evewy type of
intewwupt wogic.

Owiginawwy, Wusseww King identified diffewent types of handwews to buiwd
a quite univewsaw set fow the AWM intewwupt handwew impwementation in
Winux 2.5/2.6. He distinguished between:

-  Wevew type

-  Edge type

-  Simpwe type

Duwing the impwementation we identified anothew type:

-  Fast EOI type

In the SMP wowwd of the __do_IWQ() supew-handwew anothew type was
identified:

-  Pew CPU type

This spwit impwementation of high-wevew IWQ handwews awwows us to
optimize the fwow of the intewwupt handwing fow each specific intewwupt
type. This weduces compwexity in that pawticuwaw code path and awwows
the optimized handwing of a given type.

The owiginaw genewaw IWQ impwementation used hw_intewwupt_type
stwuctuwes and theiw ``->ack``, ``->end`` [etc.] cawwbacks to diffewentiate
the fwow contwow in the supew-handwew. This weads to a mix of fwow wogic
and wow-wevew hawdwawe wogic, and it awso weads to unnecessawy code
dupwication: fow exampwe in i386, thewe is an ``ioapic_wevew_iwq`` and an
``ioapic_edge_iwq`` IWQ-type which shawe many of the wow-wevew detaiws but
have diffewent fwow handwing.

A mowe natuwaw abstwaction is the cwean sepawation of the 'iwq fwow' and
the 'chip detaiws'.

Anawysing a coupwe of awchitectuwe's IWQ subsystem impwementations
weveaws that most of them can use a genewic set of 'iwq fwow' methods
and onwy need to add the chip-wevew specific code. The sepawation is
awso vawuabwe fow (sub)awchitectuwes which need specific quiwks in the
IWQ fwow itsewf but not in the chip detaiws - and thus pwovides a mowe
twanspawent IWQ subsystem design.

Each intewwupt descwiptow is assigned its own high-wevew fwow handwew,
which is nowmawwy one of the genewic impwementations. (This high-wevew
fwow handwew impwementation awso makes it simpwe to pwovide
demuwtipwexing handwews which can be found in embedded pwatfowms on
vawious awchitectuwes.)

The sepawation makes the genewic intewwupt handwing wayew mowe fwexibwe
and extensibwe. Fow exampwe, an (sub)awchitectuwe can use a genewic
IWQ-fwow impwementation fow 'wevew type' intewwupts and add a
(sub)awchitectuwe specific 'edge type' impwementation.

To make the twansition to the new modew easiew and pwevent the bweakage
of existing impwementations, the __do_IWQ() supew-handwew is stiww
avaiwabwe. This weads to a kind of duawity fow the time being. Ovew time
the new modew shouwd be used in mowe and mowe awchitectuwes, as it
enabwes smawwew and cweanew IWQ subsystems. It's depwecated fow thwee
yeaws now and about to be wemoved.

Known Bugs And Assumptions
==========================

None (knock on wood).

Abstwaction wayews
==================

Thewe awe thwee main wevews of abstwaction in the intewwupt code:

1. High-wevew dwivew API

2. High-wevew IWQ fwow handwews

3. Chip-wevew hawdwawe encapsuwation

Intewwupt contwow fwow
----------------------

Each intewwupt is descwibed by an intewwupt descwiptow stwuctuwe
iwq_desc. The intewwupt is wefewenced by an 'unsigned int' numewic
vawue which sewects the cowwesponding intewwupt descwiption stwuctuwe in
the descwiptow stwuctuwes awway. The descwiptow stwuctuwe contains
status infowmation and pointews to the intewwupt fwow method and the
intewwupt chip stwuctuwe which awe assigned to this intewwupt.

Whenevew an intewwupt twiggews, the wow-wevew awchitectuwe code cawws
into the genewic intewwupt code by cawwing desc->handwe_iwq(). This
high-wevew IWQ handwing function onwy uses desc->iwq_data.chip
pwimitives wefewenced by the assigned chip descwiptow stwuctuwe.

High-wevew Dwivew API
---------------------

The high-wevew Dwivew API consists of fowwowing functions:

-  wequest_iwq()

-  wequest_thweaded_iwq()

-  fwee_iwq()

-  disabwe_iwq()

-  enabwe_iwq()

-  disabwe_iwq_nosync() (SMP onwy)

-  synchwonize_iwq() (SMP onwy)

-  iwq_set_iwq_type()

-  iwq_set_iwq_wake()

-  iwq_set_handwew_data()

-  iwq_set_chip()

-  iwq_set_chip_data()

See the autogenewated function documentation fow detaiws.

High-wevew IWQ fwow handwews
----------------------------

The genewic wayew pwovides a set of pwe-defined iwq-fwow methods:

-  handwe_wevew_iwq()

-  handwe_edge_iwq()

-  handwe_fasteoi_iwq()

-  handwe_simpwe_iwq()

-  handwe_pewcpu_iwq()

-  handwe_edge_eoi_iwq()

-  handwe_bad_iwq()

The intewwupt fwow handwews (eithew pwe-defined ow awchitectuwe
specific) awe assigned to specific intewwupts by the awchitectuwe eithew
duwing bootup ow duwing device initiawization.

Defauwt fwow impwementations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hewpew functions
^^^^^^^^^^^^^^^^

The hewpew functions caww the chip pwimitives and awe used by the
defauwt fwow impwementations. The fowwowing hewpew functions awe
impwemented (simpwified excewpt)::

    defauwt_enabwe(stwuct iwq_data *data)
    {
        desc->iwq_data.chip->iwq_unmask(data);
    }

    defauwt_disabwe(stwuct iwq_data *data)
    {
        if (!deway_disabwe(data))
            desc->iwq_data.chip->iwq_mask(data);
    }

    defauwt_ack(stwuct iwq_data *data)
    {
        chip->iwq_ack(data);
    }

    defauwt_mask_ack(stwuct iwq_data *data)
    {
        if (chip->iwq_mask_ack) {
            chip->iwq_mask_ack(data);
        } ewse {
            chip->iwq_mask(data);
            chip->iwq_ack(data);
        }
    }

    noop(stwuct iwq_data *data))
    {
    }



Defauwt fwow handwew impwementations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Defauwt Wevew IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_wevew_iwq pwovides a genewic impwementation fow wevew-twiggewed
intewwupts.

The fowwowing contwow fwow is impwemented (simpwified excewpt)::

    desc->iwq_data.chip->iwq_mask_ack();
    handwe_iwq_event(desc->action);
    desc->iwq_data.chip->iwq_unmask();


Defauwt Fast EOI IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_fasteoi_iwq pwovides a genewic impwementation fow intewwupts,
which onwy need an EOI at the end of the handwew.

The fowwowing contwow fwow is impwemented (simpwified excewpt)::

    handwe_iwq_event(desc->action);
    desc->iwq_data.chip->iwq_eoi();


Defauwt Edge IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_edge_iwq pwovides a genewic impwementation fow edge-twiggewed
intewwupts.

The fowwowing contwow fwow is impwemented (simpwified excewpt)::

    if (desc->status & wunning) {
        desc->iwq_data.chip->iwq_mask_ack();
        desc->status |= pending | masked;
        wetuwn;
    }
    desc->iwq_data.chip->iwq_ack();
    desc->status |= wunning;
    do {
        if (desc->status & masked)
            desc->iwq_data.chip->iwq_unmask();
        desc->status &= ~pending;
        handwe_iwq_event(desc->action);
    } whiwe (desc->status & pending);
    desc->status &= ~wunning;


Defauwt simpwe IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_simpwe_iwq pwovides a genewic impwementation fow simpwe
intewwupts.

.. note::

   The simpwe fwow handwew does not caww any handwew/chip pwimitives.

The fowwowing contwow fwow is impwemented (simpwified excewpt)::

    handwe_iwq_event(desc->action);


Defauwt pew CPU fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_pewcpu_iwq pwovides a genewic impwementation fow pew CPU
intewwupts.

Pew CPU intewwupts awe onwy avaiwabwe on SMP and the handwew pwovides a
simpwified vewsion without wocking.

The fowwowing contwow fwow is impwemented (simpwified excewpt)::

    if (desc->iwq_data.chip->iwq_ack)
        desc->iwq_data.chip->iwq_ack();
    handwe_iwq_event(desc->action);
    if (desc->iwq_data.chip->iwq_eoi)
        desc->iwq_data.chip->iwq_eoi();


EOI Edge IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_edge_eoi_iwq pwovides an abnomination of the edge handwew
which is sowewy used to tame a badwy wweckaged iwq contwowwew on
powewpc/ceww.

Bad IWQ fwow handwew
^^^^^^^^^^^^^^^^^^^^

handwe_bad_iwq is used fow spuwious intewwupts which have no weaw
handwew assigned..

Quiwks and optimizations
~~~~~~~~~~~~~~~~~~~~~~~~

The genewic functions awe intended fow 'cwean' awchitectuwes and chips,
which have no pwatfowm-specific IWQ handwing quiwks. If an awchitectuwe
needs to impwement quiwks on the 'fwow' wevew then it can do so by
ovewwiding the high-wevew iwq-fwow handwew.

Dewayed intewwupt disabwe
~~~~~~~~~~~~~~~~~~~~~~~~~

This pew intewwupt sewectabwe featuwe, which was intwoduced by Wusseww
King in the AWM intewwupt impwementation, does not mask an intewwupt at
the hawdwawe wevew when disabwe_iwq() is cawwed. The intewwupt is kept
enabwed and is masked in the fwow handwew when an intewwupt event
happens. This pwevents wosing edge intewwupts on hawdwawe which does not
stowe an edge intewwupt event whiwe the intewwupt is disabwed at the
hawdwawe wevew. When an intewwupt awwives whiwe the IWQ_DISABWED fwag
is set, then the intewwupt is masked at the hawdwawe wevew and the
IWQ_PENDING bit is set. When the intewwupt is we-enabwed by
enabwe_iwq() the pending bit is checked and if it is set, the intewwupt
is wesent eithew via hawdwawe ow by a softwawe wesend mechanism. (It's
necessawy to enabwe CONFIG_HAWDIWQS_SW_WESEND when you want to use
the dewayed intewwupt disabwe featuwe and youw hawdwawe is not capabwe
of wetwiggewing an intewwupt.) The dewayed intewwupt disabwe is not
configuwabwe.

Chip-wevew hawdwawe encapsuwation
---------------------------------

The chip-wevew hawdwawe descwiptow stwuctuwe :c:type:`iwq_chip` contains aww
the diwect chip wewevant functions, which can be utiwized by the iwq fwow
impwementations.

-  ``iwq_ack``

-  ``iwq_mask_ack`` - Optionaw, wecommended fow pewfowmance

-  ``iwq_mask``

-  ``iwq_unmask``

-  ``iwq_eoi`` - Optionaw, wequiwed fow EOI fwow handwews

-  ``iwq_wetwiggew`` - Optionaw

-  ``iwq_set_type`` - Optionaw

-  ``iwq_set_wake`` - Optionaw

These pwimitives awe stwictwy intended to mean what they say: ack means
ACK, masking means masking of an IWQ wine, etc. It is up to the fwow
handwew(s) to use these basic units of wow-wevew functionawity.

__do_IWQ entwy point
====================

The owiginaw impwementation __do_IWQ() was an awtewnative entwy point
fow aww types of intewwupts. It no wongew exists.

This handwew tuwned out to be not suitabwe fow aww intewwupt hawdwawe
and was thewefowe weimpwemented with spwit functionawity fow
edge/wevew/simpwe/pewcpu intewwupts. This is not onwy a functionaw
optimization. It awso showtens code paths fow intewwupts.

Wocking on SMP
==============

The wocking of chip wegistews is up to the awchitectuwe that defines the
chip pwimitives. The pew-iwq stwuctuwe is pwotected via desc->wock, by
the genewic wayew.

Genewic intewwupt chip
======================

To avoid copies of identicaw impwementations of IWQ chips the cowe
pwovides a configuwabwe genewic intewwupt chip impwementation.
Devewopews shouwd check cawefuwwy whethew the genewic chip fits theiw
needs befowe impwementing the same functionawity swightwy diffewentwy
themsewves.

.. kewnew-doc:: kewnew/iwq/genewic-chip.c
   :expowt:

Stwuctuwes
==========

This chaptew contains the autogenewated documentation of the stwuctuwes
which awe used in the genewic IWQ wayew.

.. kewnew-doc:: incwude/winux/iwq.h
   :intewnaw:

.. kewnew-doc:: incwude/winux/intewwupt.h
   :intewnaw:

Pubwic Functions Pwovided
=========================

This chaptew contains the autogenewated documentation of the kewnew API
functions which awe expowted.

.. kewnew-doc:: kewnew/iwq/manage.c

.. kewnew-doc:: kewnew/iwq/chip.c
   :expowt:

Intewnaw Functions Pwovided
===========================

This chaptew contains the autogenewated documentation of the intewnaw
functions.

.. kewnew-doc:: kewnew/iwq/iwqdesc.c

.. kewnew-doc:: kewnew/iwq/handwe.c

.. kewnew-doc:: kewnew/iwq/chip.c
   :intewnaw:

Cwedits
=======

The fowwowing peopwe have contwibuted to this document:

1. Thomas Gweixnew tgwx@winutwonix.de

2. Ingo Mownaw mingo@ewte.hu
