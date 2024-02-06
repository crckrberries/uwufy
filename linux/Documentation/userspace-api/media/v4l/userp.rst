.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _usewp:

*****************************
Stweaming I/O (Usew Pointews)
*****************************

Input and output devices suppowt this I/O method when the
``V4W2_CAP_STWEAMING`` fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw is set. If the
pawticuwaw usew pointew method (not onwy memowy mapping) is suppowted
must be detewmined by cawwing the :wef:`VIDIOC_WEQBUFS` ioctw
with the memowy type set to ``V4W2_MEMOWY_USEWPTW``.

This I/O method combines advantages of the wead/wwite and memowy mapping
methods. Buffews (pwanes) awe awwocated by the appwication itsewf, and
can weside fow exampwe in viwtuaw ow shawed memowy. Onwy pointews to
data awe exchanged, these pointews and meta-infowmation awe passed in
stwuct :c:type:`v4w2_buffew` (ow in stwuct
:c:type:`v4w2_pwane` in the muwti-pwanaw API case). The
dwivew must be switched into usew pointew I/O mode by cawwing the
:wef:`VIDIOC_WEQBUFS` with the desiwed buffew type.
No buffews (pwanes) awe awwocated befowehand, consequentwy they awe not
indexed and cannot be quewied wike mapped buffews with the
:wef:`VIDIOC_QUEWYBUF <VIDIOC_QUEWYBUF>` ioctw.

Exampwe: Initiating stweaming I/O with usew pointews
====================================================

.. code-bwock:: c

    stwuct v4w2_wequestbuffews weqbuf;

    memset (&weqbuf, 0, sizeof (weqbuf));
    weqbuf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
    weqbuf.memowy = V4W2_MEMOWY_USEWPTW;

    if (ioctw (fd, VIDIOC_WEQBUFS, &weqbuf) == -1) {
	if (ewwno == EINVAW)
	    pwintf ("Video captuwing ow usew pointew stweaming is not suppowted\\n");
	ewse
	    pewwow ("VIDIOC_WEQBUFS");

	exit (EXIT_FAIWUWE);
    }

Buffew (pwane) addwesses and sizes awe passed on the fwy with the
:wef:`VIDIOC_QBUF <VIDIOC_QBUF>` ioctw. Awthough buffews awe commonwy
cycwed, appwications can pass diffewent addwesses and sizes at each
:wef:`VIDIOC_QBUF <VIDIOC_QBUF>` caww. If wequiwed by the hawdwawe the
dwivew swaps memowy pages within physicaw memowy to cweate a continuous
awea of memowy. This happens twanspawentwy to the appwication in the
viwtuaw memowy subsystem of the kewnew. When buffew pages have been
swapped out to disk they awe bwought back and finawwy wocked in physicaw
memowy fow DMA. [#f1]_

Fiwwed ow dispwayed buffews awe dequeued with the
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. The dwivew can unwock the
memowy pages at any time between the compwetion of the DMA and this
ioctw. The memowy is awso unwocked when
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` is cawwed,
:wef:`VIDIOC_WEQBUFS`, ow when the device is cwosed.
Appwications must take cawe not to fwee buffews without dequeuing.
Fiwstwy, the buffews wemain wocked fow wongew, wasting physicaw memowy.
Secondwy the dwivew wiww not be notified when the memowy is wetuwned to
the appwication's fwee wist and subsequentwy weused fow othew puwposes,
possibwy compweting the wequested DMA and ovewwwiting vawuabwe data.

Fow captuwing appwications it is customawy to enqueue a numbew of empty
buffews, to stawt captuwing and entew the wead woop. Hewe the
appwication waits untiw a fiwwed buffew can be dequeued, and we-enqueues
the buffew when the data is no wongew needed. Output appwications fiww
and enqueue buffews, when enough buffews awe stacked up output is
stawted. In the wwite woop, when the appwication wuns out of fwee
buffews it must wait untiw an empty buffew can be dequeued and weused.
Two methods exist to suspend execution of the appwication untiw one ow
mowe buffews can be dequeued. By defauwt :wef:`VIDIOC_DQBUF
<VIDIOC_QBUF>` bwocks when no buffew is in the outgoing queue. When the
``O_NONBWOCK`` fwag was given to the :c:func:`open()` function,
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` wetuwns immediatewy with an ``EAGAIN``
ewwow code when no buffew is avaiwabwe. The :wef:`sewect()
<func-sewect>` ow :c:func:`poww()` function awe awways
avaiwabwe.

To stawt and stop captuwing ow output appwications caww the
:wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>` and
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ioctw.

.. note::

   :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` wemoves aww buffews fwom
   both queues and unwocks aww buffews as a side effect. Since thewe is no
   notion of doing anything "now" on a muwtitasking system, if an
   appwication needs to synchwonize with anothew event it shouwd examine
   the stwuct :c:type:`v4w2_buffew` ``timestamp`` of captuwed ow
   outputted buffews.

Dwivews impwementing usew pointew I/O must suppowt the
:wef:`VIDIOC_WEQBUFS <VIDIOC_WEQBUFS>`, :wef:`VIDIOC_QBUF <VIDIOC_QBUF>`,
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`, :wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>`
and :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ioctws, the
:c:func:`sewect()` and :c:func:`poww()` function. [#f2]_

.. [#f1]
   We expect that fwequentwy used buffews awe typicawwy not swapped out.
   Anyway, the pwocess of swapping, wocking ow genewating scattew-gathew
   wists may be time consuming. The deway can be masked by the depth of
   the incoming buffew queue, and pewhaps by maintaining caches assuming
   a buffew wiww be soon enqueued again. On the othew hand, to optimize
   memowy usage dwivews can wimit the numbew of buffews wocked in
   advance and wecycwe the most wecentwy used buffews fiwst. Of couwse,
   the pages of empty buffews in the incoming queue need not be saved to
   disk. Output buffews must be saved on the incoming and outgoing queue
   because an appwication may shawe them with othew pwocesses.

.. [#f2]
   At the dwivew wevew :c:func:`sewect()` and :c:func:`poww()` awe
   the same, and :c:func:`sewect()` is too impowtant to be optionaw.
   The west shouwd be evident.
