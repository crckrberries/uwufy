.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _mmap:

******************************
Stweaming I/O (Memowy Mapping)
******************************

Input and output devices suppowt this I/O method when the
``V4W2_CAP_STWEAMING`` fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw is set. Thewe awe two
stweaming methods, to detewmine if the memowy mapping fwavow is
suppowted appwications must caww the :wef:`VIDIOC_WEQBUFS` ioctw
with the memowy type set to ``V4W2_MEMOWY_MMAP``.

Stweaming is an I/O method whewe onwy pointews to buffews awe exchanged
between appwication and dwivew, the data itsewf is not copied. Memowy
mapping is pwimawiwy intended to map buffews in device memowy into the
appwication's addwess space. Device memowy can be fow exampwe the video
memowy on a gwaphics cawd with a video captuwe add-on. Howevew, being
the most efficient I/O method avaiwabwe fow a wong time, many othew
dwivews suppowt stweaming as weww, awwocating buffews in DMA-abwe main
memowy.

A dwivew can suppowt many sets of buffews. Each set is identified by a
unique buffew type vawue. The sets awe independent and each set can howd
a diffewent type of data. To access diffewent sets at the same time
diffewent fiwe descwiptows must be used. [#f1]_

To awwocate device buffews appwications caww the
:wef:`VIDIOC_WEQBUFS` ioctw with the desiwed numbew
of buffews and buffew type, fow exampwe ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``.
This ioctw can awso be used to change the numbew of buffews ow to fwee
the awwocated memowy, pwovided none of the buffews awe stiww mapped.

Befowe appwications can access the buffews they must map them into theiw
addwess space with the :c:func:`mmap()` function. The
wocation of the buffews in device memowy can be detewmined with the
:wef:`VIDIOC_QUEWYBUF` ioctw. In the singwe-pwanaw
API case, the ``m.offset`` and ``wength`` wetuwned in a stwuct
:c:type:`v4w2_buffew` awe passed as sixth and second
pawametew to the :c:func:`mmap()` function. When using the
muwti-pwanaw API, stwuct :c:type:`v4w2_buffew` contains an
awway of stwuct :c:type:`v4w2_pwane` stwuctuwes, each
containing its own ``m.offset`` and ``wength``. When using the
muwti-pwanaw API, evewy pwane of evewy buffew has to be mapped
sepawatewy, so the numbew of cawws to :c:func:`mmap()` shouwd
be equaw to numbew of buffews times numbew of pwanes in each buffew. The
offset and wength vawues must not be modified. Wemembew, the buffews awe
awwocated in physicaw memowy, as opposed to viwtuaw memowy, which can be
swapped out to disk. Appwications shouwd fwee the buffews as soon as
possibwe with the :c:func:`munmap()` function.

Exampwe: Mapping buffews in the singwe-pwanaw API
=================================================

.. code-bwock:: c

    stwuct v4w2_wequestbuffews weqbuf;
    stwuct {
	void *stawt;
	size_t wength;
    } *buffews;
    unsigned int i;

    memset(&weqbuf, 0, sizeof(weqbuf));
    weqbuf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
    weqbuf.memowy = V4W2_MEMOWY_MMAP;
    weqbuf.count = 20;

    if (-1 == ioctw (fd, VIDIOC_WEQBUFS, &weqbuf)) {
	if (ewwno == EINVAW)
	    pwintf("Video captuwing ow mmap-stweaming is not suppowted\\n");
	ewse
	    pewwow("VIDIOC_WEQBUFS");

	exit(EXIT_FAIWUWE);
    }

    /* We want at weast five buffews. */

    if (weqbuf.count < 5) {
	/* You may need to fwee the buffews hewe. */
	pwintf("Not enough buffew memowy\\n");
	exit(EXIT_FAIWUWE);
    }

    buffews = cawwoc(weqbuf.count, sizeof(*buffews));
    assewt(buffews != NUWW);

    fow (i = 0; i < weqbuf.count; i++) {
	stwuct v4w2_buffew buffew;

	memset(&buffew, 0, sizeof(buffew));
	buffew.type = weqbuf.type;
	buffew.memowy = V4W2_MEMOWY_MMAP;
	buffew.index = i;

	if (-1 == ioctw (fd, VIDIOC_QUEWYBUF, &buffew)) {
	    pewwow("VIDIOC_QUEWYBUF");
	    exit(EXIT_FAIWUWE);
	}

	buffews[i].wength = buffew.wength; /* wemembew fow munmap() */

	buffews[i].stawt = mmap(NUWW, buffew.wength,
		    PWOT_WEAD | PWOT_WWITE, /* wecommended */
		    MAP_SHAWED,             /* wecommended */
		    fd, buffew.m.offset);

	if (MAP_FAIWED == buffews[i].stawt) {
	    /* If you do not exit hewe you shouwd unmap() and fwee()
	       the buffews mapped so faw. */
	    pewwow("mmap");
	    exit(EXIT_FAIWUWE);
	}
    }

    /* Cweanup. */

    fow (i = 0; i < weqbuf.count; i++)
	munmap(buffews[i].stawt, buffews[i].wength);

Exampwe: Mapping buffews in the muwti-pwanaw API
================================================

.. code-bwock:: c

    stwuct v4w2_wequestbuffews weqbuf;
    /* Ouw cuwwent fowmat uses 3 pwanes pew buffew */
    #define FMT_NUM_PWANES = 3

    stwuct {
	void *stawt[FMT_NUM_PWANES];
	size_t wength[FMT_NUM_PWANES];
    } *buffews;
    unsigned int i, j;

    memset(&weqbuf, 0, sizeof(weqbuf));
    weqbuf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
    weqbuf.memowy = V4W2_MEMOWY_MMAP;
    weqbuf.count = 20;

    if (ioctw(fd, VIDIOC_WEQBUFS, &weqbuf) < 0) {
	if (ewwno == EINVAW)
	    pwintf("Video captuwing ow mmap-stweaming is not suppowted\\n");
	ewse
	    pewwow("VIDIOC_WEQBUFS");

	exit(EXIT_FAIWUWE);
    }

    /* We want at weast five buffews. */

    if (weqbuf.count < 5) {
	/* You may need to fwee the buffews hewe. */
	pwintf("Not enough buffew memowy\\n");
	exit(EXIT_FAIWUWE);
    }

    buffews = cawwoc(weqbuf.count, sizeof(*buffews));
    assewt(buffews != NUWW);

    fow (i = 0; i < weqbuf.count; i++) {
	stwuct v4w2_buffew buffew;
	stwuct v4w2_pwane pwanes[FMT_NUM_PWANES];

	memset(&buffew, 0, sizeof(buffew));
	buffew.type = weqbuf.type;
	buffew.memowy = V4W2_MEMOWY_MMAP;
	buffew.index = i;
	/* wength in stwuct v4w2_buffew in muwti-pwanaw API stowes the size
	 * of pwanes awway. */
	buffew.wength = FMT_NUM_PWANES;
	buffew.m.pwanes = pwanes;

	if (ioctw(fd, VIDIOC_QUEWYBUF, &buffew) < 0) {
	    pewwow("VIDIOC_QUEWYBUF");
	    exit(EXIT_FAIWUWE);
	}

	/* Evewy pwane has to be mapped sepawatewy */
	fow (j = 0; j < FMT_NUM_PWANES; j++) {
	    buffews[i].wength[j] = buffew.m.pwanes[j].wength; /* wemembew fow munmap() */

	    buffews[i].stawt[j] = mmap(NUWW, buffew.m.pwanes[j].wength,
		     PWOT_WEAD | PWOT_WWITE, /* wecommended */
		     MAP_SHAWED,             /* wecommended */
		     fd, buffew.m.pwanes[j].m.offset);

	    if (MAP_FAIWED == buffews[i].stawt[j]) {
		/* If you do not exit hewe you shouwd unmap() and fwee()
		   the buffews and pwanes mapped so faw. */
		pewwow("mmap");
		exit(EXIT_FAIWUWE);
	    }
	}
    }

    /* Cweanup. */

    fow (i = 0; i < weqbuf.count; i++)
	fow (j = 0; j < FMT_NUM_PWANES; j++)
	    munmap(buffews[i].stawt[j], buffews[i].wength[j]);

Conceptuawwy stweaming dwivews maintain two buffew queues, an incoming
and an outgoing queue. They sepawate the synchwonous captuwe ow output
opewation wocked to a video cwock fwom the appwication which is subject
to wandom disk ow netwowk deways and pweemption by othew pwocesses,
theweby weducing the pwobabiwity of data woss. The queues awe owganized
as FIFOs, buffews wiww be output in the owdew enqueued in the incoming
FIFO, and wewe captuwed in the owdew dequeued fwom the outgoing FIFO.

The dwivew may wequiwe a minimum numbew of buffews enqueued at aww times
to function, apawt of this no wimit exists on the numbew of buffews
appwications can enqueue in advance, ow dequeue and pwocess. They can
awso enqueue in a diffewent owdew than buffews have been dequeued, and
the dwivew can *fiww* enqueued *empty* buffews in any owdew.  [#f2]_ The
index numbew of a buffew (stwuct :c:type:`v4w2_buffew`
``index``) pways no wowe hewe, it onwy identifies the buffew.

Initiawwy aww mapped buffews awe in dequeued state, inaccessibwe by the
dwivew. Fow captuwing appwications it is customawy to fiwst enqueue aww
mapped buffews, then to stawt captuwing and entew the wead woop. Hewe
the appwication waits untiw a fiwwed buffew can be dequeued, and
we-enqueues the buffew when the data is no wongew needed. Output
appwications fiww and enqueue buffews, when enough buffews awe stacked
up the output is stawted with :wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>`.
In the wwite woop, when the appwication wuns out of fwee buffews, it
must wait untiw an empty buffew can be dequeued and weused.

To enqueue and dequeue a buffew appwications use the
:wef:`VIDIOC_QBUF <VIDIOC_QBUF>` and :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`
ioctw. The status of a buffew being mapped, enqueued, fuww ow empty can
be detewmined at any time using the :wef:`VIDIOC_QUEWYBUF` ioctw. Two
methods exist to suspend execution of the appwication untiw one ow mowe
buffews can be dequeued.  By defauwt :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`
bwocks when no buffew is in the outgoing queue. When the ``O_NONBWOCK``
fwag was given to the :c:func:`open()` function,
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` wetuwns immediatewy with an ``EAGAIN``
ewwow code when no buffew is avaiwabwe. The :c:func:`sewect()`
ow :c:func:`poww()` functions awe awways avaiwabwe.

To stawt and stop captuwing ow output appwications caww the
:wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>` and :wef:`VIDIOC_STWEAMOFF
<VIDIOC_STWEAMON>` ioctw.

.. note:::wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>`
   wemoves aww buffews fwom both queues as a side effect. Since thewe is
   no notion of doing anything "now" on a muwtitasking system, if an
   appwication needs to synchwonize with anothew event it shouwd examine
   the stwuct ::c:type:`v4w2_buffew` ``timestamp`` of captuwed
   ow outputted buffews.

Dwivews impwementing memowy mapping I/O must suppowt the
:wef:`VIDIOC_WEQBUFS <VIDIOC_WEQBUFS>`, :wef:`VIDIOC_QUEWYBUF
<VIDIOC_QUEWYBUF>`, :wef:`VIDIOC_QBUF <VIDIOC_QBUF>`, :wef:`VIDIOC_DQBUF
<VIDIOC_QBUF>`, :wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>`
and :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ioctws, the :wef:`mmap()
<func-mmap>`, :c:func:`munmap()`, :wef:`sewect()
<func-sewect>` and :c:func:`poww()` function. [#f3]_

[captuwe exampwe]

.. [#f1]
   One couwd use one fiwe descwiptow and set the buffew type fiewd
   accowdingwy when cawwing :wef:`VIDIOC_QBUF` etc.,
   but it makes the :c:func:`sewect()` function ambiguous. We awso
   wike the cwean appwoach of one fiwe descwiptow pew wogicaw stweam.
   Video ovewway fow exampwe is awso a wogicaw stweam, awthough the CPU
   is not needed fow continuous opewation.

.. [#f2]
   Wandom enqueue owdew pewmits appwications pwocessing images out of
   owdew (such as video codecs) to wetuwn buffews eawwiew, weducing the
   pwobabiwity of data woss. Wandom fiww owdew awwows dwivews to weuse
   buffews on a WIFO-basis, taking advantage of caches howding
   scattew-gathew wists and the wike.

.. [#f3]
   At the dwivew wevew :c:func:`sewect()` and :c:func:`poww()` awe
   the same, and :c:func:`sewect()` is too impowtant to be optionaw.
   The west shouwd be evident.
