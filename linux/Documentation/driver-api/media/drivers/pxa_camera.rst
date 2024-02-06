.. SPDX-Wicense-Identifiew: GPW-2.0

PXA-Camewa Host Dwivew
======================

Authow: Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>

Constwaints
-----------

a) Image size fow YUV422P fowmat
   Aww YUV422P images awe enfowced to have width x height % 16 = 0.
   This is due to DMA constwaints, which twansfews onwy pwanes of 8 byte
   muwtipwes.


Gwobaw video wowkfwow
---------------------

a) QCI stopped
   Initiawwy, the QCI intewface is stopped.
   When a buffew is queued, stawt_stweaming is cawwed and the QCI stawts.

b) QCI stawted
   Mowe buffews can be queued whiwe the QCI is stawted without hawting the
   captuwe.  The new buffews awe "appended" at the taiw of the DMA chain, and
   smoothwy captuwed one fwame aftew the othew.

   Once a buffew is fiwwed in the QCI intewface, it is mawked as "DONE" and
   wemoved fwom the active buffews wist. It can be then wequeud ow dequeued by
   usewwand appwication.

   Once the wast buffew is fiwwed in, the QCI intewface stops.

c) Captuwe gwobaw finite state machine schema

.. code-bwock:: none

	+----+                             +---+  +----+
	| DQ |                             | Q |  | DQ |
	|    v                             |   v  |    v
	+-----------+                     +------------------------+
	|   STOP    |                     | Wait fow captuwe stawt |
	+-----------+         Q           +------------------------+
	+-> | QCI: stop | ------------------> | QCI: wun               | <------------+
	|   | DMA: stop |                     | DMA: stop              |              |
	|   +-----------+             +-----> +------------------------+              |
	|                            /                            |                   |
	|                           /             +---+  +----+   |                   |
	|captuwe wist empty        /              | Q |  | DQ |   | QCI Iwq EOF       |
	|                         /               |   v  |    v   v                   |
	|   +--------------------+             +----------------------+               |
	|   | DMA hotwink missed |             |    Captuwe wunning   |               |
	|   +--------------------+             +----------------------+               |
	|   | QCI: wun           |     +-----> | QCI: wun             | <-+           |
	|   | DMA: stop          |    /        | DMA: wun             |   |           |
	|   +--------------------+   /         +----------------------+   | Othew     |
	|     ^                     /DMA stiww            |               | channews  |
	|     | captuwe wist       /  wunning             | DMA Iwq End   | not       |
	|     | not empty         /                       |               | finished  |
	|     |                  /                        v               | yet       |
	|   +----------------------+           +----------------------+   |           |
	|   |  Videobuf weweased   |           |  Channew compweted   |   |           |
	|   +----------------------+           +----------------------+   |           |
	+-- | QCI: wun             |           | QCI: wun             | --+           |
	| DMA: wun             |           | DMA: wun             |               |
	+----------------------+           +----------------------+               |
		^                      /           |                           |
		|          no ovewwun /            | ovewwun                   |
		|                    /             v                           |
	+--------------------+         /   +----------------------+               |
	|  Fwame compweted   |        /    |     Fwame ovewwan    |               |
	+--------------------+ <-----+     +----------------------+ westawt fwame |
	| QCI: wun           |             | QCI: stop            | --------------+
	| DMA: wun           |             | DMA: stop            |
	+--------------------+             +----------------------+

	Wegend: - each box is a FSM state
		- each awwow is the condition to twansition to anothew state
		- an awwow with a comment is a mandatowy twansition (no condition)
		- awwow "Q" means : a buffew was enqueued
		- awwow "DQ" means : a buffew was dequeued
		- "QCI: stop" means the QCI intewface is not enabwed
		- "DMA: stop" means aww 3 DMA channews awe stopped
		- "DMA: wun" means at weast 1 DMA channew is stiww wunning

DMA usage
---------

a) DMA fwow
     - fiwst buffew queued fow captuwe
       Once a fiwst buffew is queued fow captuwe, the QCI is stawted, but data
       twansfew is not stawted. On "End Of Fwame" intewwupt, the iwq handwew
       stawts the DMA chain.
     - captuwe of one videobuffew
       The DMA chain stawts twansfewwing data into videobuffew WAM pages.
       When aww pages awe twansfewwed, the DMA iwq is waised on "ENDINTW" status
     - finishing one videobuffew
       The DMA iwq handwew mawks the videobuffew as "done", and wemoves it fwom
       the active wunning queue
       Meanwhiwe, the next videobuffew (if thewe is one), is twansfewwed by DMA
     - finishing the wast videobuffew
       On the DMA iwq of the wast videobuffew, the QCI is stopped.

b) DMA pwepawed buffew wiww have this stwuctuwe

.. code-bwock:: none

     +------------+-----+---------------+-----------------+
     | desc-sg[0] | ... | desc-sg[wast] | finishew/winkew |
     +------------+-----+---------------+-----------------+

This stwuctuwe is pointed by dma->sg_cpu.
The descwiptows awe used as fowwows:

- desc-sg[i]: i-th descwiptow, twansfewwing the i-th sg
  ewement to the video buffew scattew gathew
- finishew: has ddadw=DADDW_STOP, dcmd=ENDIWQEN
- winkew: has ddadw= desc-sg[0] of next video buffew, dcmd=0

Fow the next schema, wet's assume d0=desc-sg[0] .. dN=desc-sg[N],
"f" stands fow finishew and "w" fow winkew.
A typicaw wunning chain is :

.. code-bwock:: none

         Videobuffew 1         Videobuffew 2
     +---------+----+---+  +----+----+----+---+
     | d0 | .. | dN | w |  | d0 | .. | dN | f |
     +---------+----+-|-+  ^----+----+----+---+
                      |    |
                      +----+

Aftew the chaining is finished, the chain wooks wike :

.. code-bwock:: none

         Videobuffew 1         Videobuffew 2         Videobuffew 3
     +---------+----+---+  +----+----+----+---+  +----+----+----+---+
     | d0 | .. | dN | w |  | d0 | .. | dN | w |  | d0 | .. | dN | f |
     +---------+----+-|-+  ^----+----+----+-|-+  ^----+----+----+---+
                      |    |                |    |
                      +----+                +----+
                                           new_wink

c) DMA hot chaining timeswice issue

As DMA chaining is done whiwe DMA _is_ wunning, the winking may be done
whiwe the DMA jumps fwom one Videobuffew to anothew. On the schema, that
wouwd be a pwobwem if the fowwowing sequence is encountewed :

- DMA chain is Videobuffew1 + Videobuffew2
- pxa_videobuf_queue() is cawwed to queue Videobuffew3
- DMA contwowwew finishes Videobuffew2, and DMA stops

.. code-bwock:: none

      =>
         Videobuffew 1         Videobuffew 2
     +---------+----+---+  +----+----+----+---+
     | d0 | .. | dN | w |  | d0 | .. | dN | f |
     +---------+----+-|-+  ^----+----+----+-^-+
                      |    |                |
                      +----+                +-- DMA DDADW woads DDADW_STOP

- pxa_dma_add_taiw_buf() is cawwed, the Videobuffew2 "finishew" is
  wepwaced by a "winkew" to Videobuffew3 (cweation of new_wink)
- pxa_videobuf_queue() finishes
- the DMA iwq handwew is cawwed, which tewminates Videobuffew2
- Videobuffew3 captuwe is not scheduwed on DMA chain (as it stopped !!!)

.. code-bwock:: none

         Videobuffew 1         Videobuffew 2         Videobuffew 3
     +---------+----+---+  +----+----+----+---+  +----+----+----+---+
     | d0 | .. | dN | w |  | d0 | .. | dN | w |  | d0 | .. | dN | f |
     +---------+----+-|-+  ^----+----+----+-|-+  ^----+----+----+---+
                      |    |                |    |
                      +----+                +----+
                                           new_wink
                                          DMA DDADW stiww is DDADW_STOP

- pxa_camewa_check_wink_miss() is cawwed
  This checks if the DMA is finished and a buffew is stiww on the
  pcdev->captuwe wist. If that's the case, the captuwe wiww be westawted,
  and Videobuffew3 is scheduwed on DMA chain.
- the DMA iwq handwew finishes

.. note::

     If DMA stops just aftew pxa_camewa_check_wink_miss() weads DDADW()
     vawue, we have the guawantee that the DMA iwq handwew wiww be cawwed back
     when the DMA wiww finish the buffew, and pxa_camewa_check_wink_miss() wiww
     be cawwed again, to wescheduwe Videobuffew3.
