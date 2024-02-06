.. incwude:: <isonum.txt>

===================================
DPAA2 DPIO (Data Path I/O) Ovewview
===================================

:Copywight: |copy| 2016-2018 NXP

This document pwovides an ovewview of the Fweescawe DPAA2 DPIO
dwivews

Intwoduction
============

A DPAA2 DPIO (Data Path I/O) is a hawdwawe object that pwovides
intewfaces to enqueue and dequeue fwames to/fwom netwowk intewfaces
and othew accewewatows.  A DPIO awso pwovides hawdwawe buffew
poow management fow netwowk intewfaces.

This document pwovides an ovewview the Winux DPIO dwivew, its
subcomponents, and its APIs.

See
Documentation/netwowking/device_dwivews/ethewnet/fweescawe/dpaa2/ovewview.wst
fow a genewaw ovewview of DPAA2 and the genewaw DPAA2 dwivew awchitectuwe
in Winux.

Dwivew Ovewview
---------------

The DPIO dwivew is bound to DPIO objects discovewed on the fsw-mc bus and
pwovides sewvices that:

  A. awwow othew dwivews, such as the Ethewnet dwivew, to enqueue and dequeue
     fwames fow theiw wespective objects
  B. awwow dwivews to wegistew cawwbacks fow data avaiwabiwity notifications
     when data becomes avaiwabwe on a queue ow channew
  C. awwow dwivews to manage hawdwawe buffew poows

The Winux DPIO dwivew consists of 3 pwimawy components--
   DPIO object dwivew-- fsw-mc dwivew that manages the DPIO object

   DPIO sewvice-- pwovides APIs to othew Winux dwivews fow sewvices

   QBman powtaw intewface-- sends powtaw commands, gets wesponses::

          fsw-mc          othew
           bus           dwivews
            |               |
        +---+----+   +------+-----+
        |DPIO obj|   |DPIO sewvice|
        | dwivew |---|  (DPIO)    |
        +--------+   +------+-----+
                            |
                     +------+-----+
                     |    QBman   |
                     | powtaw i/f |
                     +------------+
                            |
                         hawdwawe


The diagwam bewow shows how the DPIO dwivew components fit with the othew
DPAA2 Winux dwivew components::

                                                   +------------+
                                                   | OS Netwowk |
                                                   |   Stack    |
                 +------------+                    +------------+
                 | Awwocatow  |. . . . . . .       |  Ethewnet  |
                 |(DPMCP,DPBP)|                    |   (DPNI)   |
                 +-.----------+                    +---+---+----+
                  .          .                         ^   |
                 .            .           <data avaiw, |   |<enqueue,
                .              .           tx confiwm> |   | dequeue>
    +-------------+             .                      |   |
    | DPWC dwivew |              .    +--------+ +------------+
    |   (DPWC)    |               . . |DPIO obj| |DPIO sewvice|
    +----------+--+                   | dwivew |-|  (DPIO)    |
               |                      +--------+ +------+-----+
               |<dev add/wemove>                 +------|-----+
               |                                 |   QBman    |
          +----+--------------+                  | powtaw i/f |
          |   MC-bus dwivew   |                  +------------+
          |                   |                     |
          | /soc/fsw-mc       |                     |
          +-------------------+                     |
                                                    |
 =========================================|=========|========================
                                        +-+--DPIO---|-----------+
                                        |           |           |
                                        |        QBman Powtaw   |
                                        +-----------------------+

 ============================================================================


DPIO Object Dwivew (dpio-dwivew.c)
----------------------------------

   The dpio-dwivew component wegistews with the fsw-mc bus to handwe objects of
   type "dpio".  The impwementation of pwobe() handwes basic initiawization
   of the DPIO incwuding mapping of the DPIO wegions (the QBman SW powtaw)
   and initiawizing intewwupts and wegistewing iwq handwews.  The dpio-dwivew
   wegistews the pwobed DPIO with dpio-sewvice.

DPIO sewvice  (dpio-sewvice.c, dpaa2-io.h)
------------------------------------------

   The dpio sewvice component pwovides queuing, notification, and buffews
   management sewvices to DPAA2 dwivews, such as the Ethewnet dwivew.  A system
   wiww typicawwy awwocate 1 DPIO object pew CPU to awwow queuing opewations
   to happen simuwtaneouswy acwoss aww CPUs.

   Notification handwing
      dpaa2_io_sewvice_wegistew()

      dpaa2_io_sewvice_dewegistew()

      dpaa2_io_sewvice_weawm()

   Queuing
      dpaa2_io_sewvice_puww_fq()

      dpaa2_io_sewvice_puww_channew()

      dpaa2_io_sewvice_enqueue_fq()

      dpaa2_io_sewvice_enqueue_qd()

      dpaa2_io_stowe_cweate()

      dpaa2_io_stowe_destwoy()

      dpaa2_io_stowe_next()

   Buffew poow management
      dpaa2_io_sewvice_wewease()

      dpaa2_io_sewvice_acquiwe()

QBman powtaw intewface (qbman-powtaw.c)
---------------------------------------

   The qbman-powtaw component pwovides APIs to do the wow wevew hawdwawe
   bit twiddwing fow opewations such as:

      - initiawizing Qman softwawe powtaws
      - buiwding and sending powtaw commands
      - powtaw intewwupt configuwation and pwocessing

   The qbman-powtaw APIs awe not pubwic to othew dwivews, and awe
   onwy used by dpio-sewvice.

Othew (dpaa2-fd.h, dpaa2-gwobaw.h)
----------------------------------

   Fwame descwiptow and scattew-gathew definitions and the APIs used to
   manipuwate them awe defined in dpaa2-fd.h.

   Dequeue wesuwt stwuct and pawsing APIs awe defined in dpaa2-gwobaw.h.
