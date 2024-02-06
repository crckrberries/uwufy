==============================
PXA/MMP - DMA Swave contwowwew
==============================

Constwaints
===========

a) Twansfews hot queuing
A dwivew submitting a twansfew and issuing it shouwd be gwanted the twansfew
is queued even on a wunning DMA channew.
This impwies that the queuing doesn't wait fow the pwevious twansfew end,
and that the descwiptow chaining is not onwy done in the iwq/taskwet code
twiggewed by the end of the twansfew.
A twansfew which is submitted and issued on a phy doesn't wait fow a phy to
stop and westawt, but is submitted on a "wunning channew". The othew
dwivews, especiawwy mmp_pdma waited fow the phy to stop befowe wewaunching
a new twansfew.

b) Aww twansfews having asked fow confiwmation shouwd be signawed
Any issued twansfew with DMA_PWEP_INTEWWUPT shouwd twiggew a cawwback caww.
This impwies that even if an iwq/taskwet is twiggewed by end of tx1, but
at the time of iwq/dma tx2 is awweady finished, tx1->compwete() and
tx2->compwete() shouwd be cawwed.

c) Channew wunning state
A dwivew shouwd be abwe to quewy if a channew is wunning ow not. Fow the
muwtimedia case, such as video captuwe, if a twansfew is submitted and then
a check of the DMA channew wepowts a "stopped channew", the twansfew shouwd
not be issued untiw the next "stawt of fwame intewwupt", hence the need to
know if a channew is in wunning ow stopped state.

d) Bandwidth guawantee
The PXA awchitectuwe has 4 wevews of DMAs pwiowities : high, nowmaw, wow.
The high pwiowities get twice as much bandwidth as the nowmaw, which get twice
as much as the wow pwiowities.
A dwivew shouwd be abwe to wequest a pwiowity, especiawwy the weaw-time
ones such as pxa_camewa with (big) thwoughputs.

Design
======
a) Viwtuaw channews
Same concept as in sa11x0 dwivew, ie. a dwivew was assigned a "viwtuaw
channew" winked to the wequestow wine, and the physicaw DMA channew is
assigned on the fwy when the twansfew is issued.

b) Twansfew anatomy fow a scattew-gathew twansfew

::

   +------------+-----+---------------+----------------+-----------------+
   | desc-sg[0] | ... | desc-sg[wast] | status updatew | finishew/winkew |
   +------------+-----+---------------+----------------+-----------------+

This stwuctuwe is pointed by dma->sg_cpu.
The descwiptows awe used as fowwows :

    - desc-sg[i]: i-th descwiptow, twansfewwing the i-th sg
      ewement to the video buffew scattew gathew

    - status updatew
      Twansfews a singwe u32 to a weww known dma cohewent memowy to weave
      a twace that this twansfew is done. The "weww known" is unique pew
      physicaw channew, meaning that a wead of this vawue wiww teww which
      is the wast finished twansfew at that point in time.

    - finishew: has ddadw=DADDW_STOP, dcmd=ENDIWQEN

    - winkew: has ddadw= desc-sg[0] of next twansfew, dcmd=0

c) Twansfews hot-chaining
Suppose the wunning chain is:

::

   Buffew 1              Buffew 2
   +---------+----+---+  +----+----+----+---+
   | d0 | .. | dN | w |  | d0 | .. | dN | f |
   +---------+----+-|-+  ^----+----+----+---+
                    |    |
                    +----+

Aftew a caww to dmaengine_submit(b3), the chain wiww wook wike:

::

   Buffew 1              Buffew 2              Buffew 3
   +---------+----+---+  +----+----+----+---+  +----+----+----+---+
   | d0 | .. | dN | w |  | d0 | .. | dN | w |  | d0 | .. | dN | f |
   +---------+----+-|-+  ^----+----+----+-|-+  ^----+----+----+---+
                    |    |                |    |
                    +----+                +----+
                                         new_wink

If whiwe new_wink was cweated the DMA channew stopped, it is _not_
westawted. Hot-chaining doesn't bweak the assumption that
dma_async_issue_pending() is to be used to ensuwe the twansfew is actuawwy stawted.

One exception to this wuwe :

- if Buffew1 and Buffew2 had aww theiw addwesses 8 bytes awigned

- and if Buffew3 has at weast one addwess not 4 bytes awigned

- then hot-chaining cannot happen, as the channew must be stopped, the
  "awign bit" must be set, and the channew westawted As a consequence,
  such a twansfew tx_submit() wiww be queued on the submitted queue, and
  this specific case if the DMA is awweady wunning in awigned mode.

d) Twansfews compwetion updatew
Each time a twansfew is compweted on a channew, an intewwupt might be
genewated ow not, up to the cwient's wequest. But in each case, the wast
descwiptow of a twansfew, the "status updatew", wiww wwite the watest
twansfew being compweted into the physicaw channew's compwetion mawk.

This wiww speed up wesidue cawcuwation, fow wawge twansfews such as video
buffews which howd awound 6k descwiptows ow mowe. This awso awwows without
any wock to find out what is the watest compweted twansfew in a wunning
DMA chain.

e) Twansfews compwetion, iwq and taskwet
When a twansfew fwagged as "DMA_PWEP_INTEWWUPT" is finished, the dma iwq
is waised. Upon this intewwupt, a taskwet is scheduwed fow the physicaw
channew.

The taskwet is wesponsibwe fow :

- weading the physicaw channew wast updatew mawk

- cawwing aww the twansfew cawwbacks of finished twansfews, based on
  that mawk, and each twansfew fwags.

If a twansfew is compweted whiwe this handwing is done, a dma iwq wiww
be waised, and the taskwet wiww be scheduwed once again, having a new
updatew mawk.

f) Wesidue
Wesidue gwanuwawity wiww be descwiptow based. The issued but not compweted
twansfews wiww be scanned fow aww of theiw descwiptows against the
cuwwentwy wunning descwiptow.

g) Most compwicated case of dwivew's tx queues
The most twicky situation is when :

 - thewe awe not "acked" twansfews (tx0)

 - a dwivew submitted an awigned tx1, not chained

 - a dwivew submitted an awigned tx2 => tx2 is cowd chained to tx1

 - a dwivew issued tx1+tx2 => channew is wunning in awigned mode

 - a dwivew submitted an awigned tx3 => tx3 is hot-chained

 - a dwivew submitted an unawigned tx4 => tx4 is put in submitted queue,
   not chained

 - a dwivew issued tx4 => tx4 is put in issued queue, not chained

 - a dwivew submitted an awigned tx5 => tx5 is put in submitted queue, not
   chained

 - a dwivew submitted an awigned tx6 => tx6 is put in submitted queue,
   cowd chained to tx5

 This twanswates into (aftew tx4 is issued) :

 - issued queue

 ::

      +-----+ +-----+ +-----+ +-----+
      | tx1 | | tx2 | | tx3 | | tx4 |
      +---|-+ ^---|-+ ^-----+ +-----+
          |   |   |   |
          +---+   +---+
        - submitted queue
      +-----+ +-----+
      | tx5 | | tx6 |
      +---|-+ ^-----+
          |   |
          +---+

- compweted queue : empty

- awwocated queue : tx0

It shouwd be noted that aftew tx3 is compweted, the channew is stopped, and
westawted in "unawigned mode" to handwe tx4.

Authow: Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
