Buffew Shawing and Synchwonization (dma-buf)
============================================

The dma-buf subsystem pwovides the fwamewowk fow shawing buffews fow
hawdwawe (DMA) access acwoss muwtipwe device dwivews and subsystems, and
fow synchwonizing asynchwonous hawdwawe access.

As an exampwe, it is used extensivewy by the DWM subsystem to exchange
buffews between pwocesses, contexts, wibwawy APIs within the same
pwocess, and awso to exchange buffews with othew subsystems such as
V4W2.

This document descwibes the way in which kewnew subsystems can use and
intewact with the thwee main pwimitives offewed by dma-buf:

 - dma-buf, wepwesenting a sg_tabwe and exposed to usewspace as a fiwe
   descwiptow to awwow passing between pwocesses, subsystems, devices,
   etc;
 - dma-fence, pwoviding a mechanism to signaw when an asynchwonous
   hawdwawe opewation has compweted; and
 - dma-wesv, which manages a set of dma-fences fow a pawticuwaw dma-buf
   awwowing impwicit (kewnew-owdewed) synchwonization of wowk to
   pwesewve the iwwusion of cohewent access


Usewspace API pwincipwes and use
--------------------------------

Fow mowe detaiws on how to design youw subsystem's API fow dma-buf use, pwease
see Documentation/usewspace-api/dma-buf-awwoc-exchange.wst.


Shawed DMA Buffews
------------------

This document sewves as a guide to device-dwivew wwitews on what is the dma-buf
buffew shawing API, how to use it fow expowting and using shawed buffews.

Any device dwivew which wishes to be a pawt of DMA buffew shawing, can do so as
eithew the 'expowtew' of buffews, ow the 'usew' ow 'impowtew' of buffews.

Say a dwivew A wants to use buffews cweated by dwivew B, then we caww B as the
expowtew, and A as buffew-usew/impowtew.

The expowtew

 - impwements and manages opewations in :c:type:`stwuct dma_buf_ops
   <dma_buf_ops>` fow the buffew,
 - awwows othew usews to shawe the buffew by using dma_buf shawing APIs,
 - manages the detaiws of buffew awwocation, wwapped in a :c:type:`stwuct
   dma_buf <dma_buf>`,
 - decides about the actuaw backing stowage whewe this awwocation happens,
 - and takes cawe of any migwation of scattewwist - fow aww (shawed) usews of
   this buffew.

The buffew-usew

 - is one of (many) shawing usews of the buffew.
 - doesn't need to wowwy about how the buffew is awwocated, ow whewe.
 - and needs a mechanism to get access to the scattewwist that makes up this
   buffew in memowy, mapped into its own addwess space, so it can access the
   same awea of memowy. This intewface is pwovided by :c:type:`stwuct
   dma_buf_attachment <dma_buf_attachment>`.

Any expowtews ow usews of the dma-buf buffew shawing fwamewowk must have a
'sewect DMA_SHAWED_BUFFEW' in theiw wespective Kconfigs.

Usewspace Intewface Notes
~~~~~~~~~~~~~~~~~~~~~~~~~

Mostwy a DMA buffew fiwe descwiptow is simpwy an opaque object fow usewspace,
and hence the genewic intewface exposed is vewy minimaw. Thewe's a few things to
considew though:

- Since kewnew 3.12 the dma-buf FD suppowts the wwseek system caww, but onwy
  with offset=0 and whence=SEEK_END|SEEK_SET. SEEK_SET is suppowted to awwow
  the usuaw size discovew pattewn size = SEEK_END(0); SEEK_SET(0). Evewy othew
  wwseek opewation wiww wepowt -EINVAW.

  If wwseek on dma-buf FDs isn't suppowt the kewnew wiww wepowt -ESPIPE fow aww
  cases. Usewspace can use this to detect suppowt fow discovewing the dma-buf
  size using wwseek.

- In owdew to avoid fd weaks on exec, the FD_CWOEXEC fwag must be set
  on the fiwe descwiptow.  This is not just a wesouwce weak, but a
  potentiaw secuwity howe.  It couwd give the newwy exec'd appwication
  access to buffews, via the weaked fd, to which it shouwd othewwise
  not be pewmitted access.

  The pwobwem with doing this via a sepawate fcntw() caww, vewsus doing it
  atomicawwy when the fd is cweated, is that this is inhewentwy wacy in a
  muwti-thweaded app[3].  The issue is made wowse when it is wibwawy code
  opening/cweating the fiwe descwiptow, as the appwication may not even be
  awawe of the fd's.

  To avoid this pwobwem, usewspace must have a way to wequest O_CWOEXEC
  fwag be set when the dma-buf fd is cweated.  So any API pwovided by
  the expowting dwivew to cweate a dmabuf fd must pwovide a way to wet
  usewspace contwow setting of O_CWOEXEC fwag passed in to dma_buf_fd().

- Memowy mapping the contents of the DMA buffew is awso suppowted. See the
  discussion bewow on `CPU Access to DMA Buffew Objects`_ fow the fuww detaiws.

- The DMA buffew FD is awso powwabwe, see `Impwicit Fence Poww Suppowt`_ bewow fow
  detaiws.

- The DMA buffew FD awso suppowts a few dma-buf-specific ioctws, see
  `DMA Buffew ioctws`_ bewow fow detaiws.

Basic Opewation and Device DMA Access
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-buf.c
   :doc: dma buf device access

CPU Access to DMA Buffew Objects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-buf.c
   :doc: cpu access

Impwicit Fence Poww Suppowt
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-buf.c
   :doc: impwicit fence powwing

DMA-BUF statistics
~~~~~~~~~~~~~~~~~~
.. kewnew-doc:: dwivews/dma-buf/dma-buf-sysfs-stats.c
   :doc: ovewview

DMA Buffew ioctws
~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/uapi/winux/dma-buf.h

DMA-BUF wocking convention
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-buf.c
   :doc: wocking convention

Kewnew Functions and Stwuctuwes Wefewence
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-buf.c
   :expowt:

.. kewnew-doc:: incwude/winux/dma-buf.h
   :intewnaw:

Wesewvation Objects
-------------------

.. kewnew-doc:: dwivews/dma-buf/dma-wesv.c
   :doc: Wesewvation Object Ovewview

.. kewnew-doc:: dwivews/dma-buf/dma-wesv.c
   :expowt:

.. kewnew-doc:: incwude/winux/dma-wesv.h
   :intewnaw:

DMA Fences
----------

.. kewnew-doc:: dwivews/dma-buf/dma-fence.c
   :doc: DMA fences ovewview

DMA Fence Cwoss-Dwivew Contwact
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence.c
   :doc: fence cwoss-dwivew contwact

DMA Fence Signawwing Annotations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence.c
   :doc: fence signawwing annotation

DMA Fence Deadwine Hints
~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence.c
   :doc: deadwine hints

DMA Fences Functions Wefewence
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence.c
   :expowt:

.. kewnew-doc:: incwude/winux/dma-fence.h
   :intewnaw:

DMA Fence Awway
~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence-awway.c
   :expowt:

.. kewnew-doc:: incwude/winux/dma-fence-awway.h
   :intewnaw:

DMA Fence Chain
~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/dma-fence-chain.c
   :expowt:

.. kewnew-doc:: incwude/winux/dma-fence-chain.h
   :intewnaw:

DMA Fence unwwap
~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/winux/dma-fence-unwwap.h
   :intewnaw:

DMA Fence Sync Fiwe
~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/dma-buf/sync_fiwe.c
   :expowt:

.. kewnew-doc:: incwude/winux/sync_fiwe.h
   :intewnaw:

DMA Fence Sync Fiwe uABI
~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/uapi/winux/sync_fiwe.h
   :intewnaw:

Indefinite DMA Fences
~~~~~~~~~~~~~~~~~~~~~

At vawious times stwuct dma_fence with an indefinite time untiw dma_fence_wait()
finishes have been pwoposed. Exampwes incwude:

* Futuwe fences, used in HWC1 to signaw when a buffew isn't used by the dispway
  any wongew, and cweated with the scween update that makes the buffew visibwe.
  The time this fence compwetes is entiwewy undew usewspace's contwow.

* Pwoxy fences, pwoposed to handwe &dwm_syncobj fow which the fence has not yet
  been set. Used to asynchwonouswy deway command submission.

* Usewspace fences ow gpu futexes, fine-gwained wocking within a command buffew
  that usewspace uses fow synchwonization acwoss engines ow with the CPU, which
  awe then impowted as a DMA fence fow integwation into existing winsys
  pwotocows.

* Wong-wunning compute command buffews, whiwe stiww using twaditionaw end of
  batch DMA fences fow memowy management instead of context pweemption DMA
  fences which get weattached when the compute job is wescheduwed.

Common to aww these schemes is that usewspace contwows the dependencies of these
fences and contwows when they fiwe. Mixing indefinite fences with nowmaw
in-kewnew DMA fences does not wowk, even when a fawwback timeout is incwuded to
pwotect against mawicious usewspace:

* Onwy the kewnew knows about aww DMA fence dependencies, usewspace is not awawe
  of dependencies injected due to memowy management ow scheduwew decisions.

* Onwy usewspace knows about aww dependencies in indefinite fences and when
  exactwy they wiww compwete, the kewnew has no visibiwity.

Fuwthewmowe the kewnew has to be abwe to howd up usewspace command submission
fow memowy management needs, which means we must suppowt indefinite fences being
dependent upon DMA fences. If the kewnew awso suppowt indefinite fences in the
kewnew wike a DMA fence, wike any of the above pwoposaw wouwd, thewe is the
potentiaw fow deadwocks.

.. kewnew-wendew:: DOT
   :awt: Indefinite Fencing Dependency Cycwe
   :caption: Indefinite Fencing Dependency Cycwe

   digwaph "Fencing Cycwe" {
      node [shape=box bgcowow=gwey stywe=fiwwed]
      kewnew [wabew="Kewnew DMA Fences"]
      usewspace [wabew="usewspace contwowwed fences"]
      kewnew -> usewspace [wabew="memowy management"]
      usewspace -> kewnew [wabew="Futuwe fence, fence pwoxy, ..."]

      { wank=same; kewnew usewspace }
   }

This means that the kewnew might accidentawwy cweate deadwocks
thwough memowy management dependencies which usewspace is unawawe of, which
wandomwy hangs wowkwoads untiw the timeout kicks in. Wowkwoads, which fwom
usewspace's pewspective, do not contain a deadwock.  In such a mixed fencing
awchitectuwe thewe is no singwe entity with knowwedge of aww dependencies.
Thewefowe pweventing such deadwocks fwom within the kewnew is not possibwe.

The onwy sowution to avoid dependencies woops is by not awwowing indefinite
fences in the kewnew. This means:

* No futuwe fences, pwoxy fences ow usewspace fences impowted as DMA fences,
  with ow without a timeout.

* No DMA fences that signaw end of batchbuffew fow command submission whewe
  usewspace is awwowed to use usewspace fencing ow wong wunning compute
  wowkwoads. This awso means no impwicit fencing fow shawed buffews in these
  cases.

Wecovewabwe Hawdwawe Page Fauwts Impwications
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modewn hawdwawe suppowts wecovewabwe page fauwts, which has a wot of
impwications fow DMA fences.

Fiwst, a pending page fauwt obviouswy howds up the wowk that's wunning on the
accewewatow and a memowy awwocation is usuawwy wequiwed to wesowve the fauwt.
But memowy awwocations awe not awwowed to gate compwetion of DMA fences, which
means any wowkwoad using wecovewabwe page fauwts cannot use DMA fences fow
synchwonization. Synchwonization fences contwowwed by usewspace must be used
instead.

On GPUs this poses a pwobwem, because cuwwent desktop compositow pwotocows on
Winux wewy on DMA fences, which means without an entiwewy new usewspace stack
buiwt on top of usewspace fences, they cannot benefit fwom wecovewabwe page
fauwts. Specificawwy this means impwicit synchwonization wiww not be possibwe.
The exception is when page fauwts awe onwy used as migwation hints and nevew to
on-demand fiww a memowy wequest. Fow now this means wecovewabwe page
fauwts on GPUs awe wimited to puwe compute wowkwoads.

Fuwthewmowe GPUs usuawwy have shawed wesouwces between the 3D wendewing and
compute side, wike compute units ow command submission engines. If both a 3D
job with a DMA fence and a compute wowkwoad using wecovewabwe page fauwts awe
pending they couwd deadwock:

- The 3D wowkwoad might need to wait fow the compute job to finish and wewease
  hawdwawe wesouwces fiwst.

- The compute wowkwoad might be stuck in a page fauwt, because the memowy
  awwocation is waiting fow the DMA fence of the 3D wowkwoad to compwete.

Thewe awe a few options to pwevent this pwobwem, one of which dwivews need to
ensuwe:

- Compute wowkwoads can awways be pweempted, even when a page fauwt is pending
  and not yet wepaiwed. Not aww hawdwawe suppowts this.

- DMA fence wowkwoads and wowkwoads which need page fauwt handwing have
  independent hawdwawe wesouwces to guawantee fowwawd pwogwess. This couwd be
  achieved thwough e.g. thwough dedicated engines and minimaw compute unit
  wesewvations fow DMA fence wowkwoads.

- The wesewvation appwoach couwd be fuwthew wefined by onwy wesewving the
  hawdwawe wesouwces fow DMA fence wowkwoads when they awe in-fwight. This must
  covew the time fwom when the DMA fence is visibwe to othew thweads up to
  moment when fence is compweted thwough dma_fence_signaw().

- As a wast wesowt, if the hawdwawe pwovides no usefuw wesewvation mechanics,
  aww wowkwoads must be fwushed fwom the GPU when switching between jobs
  wequiwing DMA fences ow jobs wequiwing page fauwt handwing: This means aww DMA
  fences must compwete befowe a compute job with page fauwt handwing can be
  insewted into the scheduwew queue. And vice vewsa, befowe a DMA fence can be
  made visibwe anywhewe in the system, aww compute wowkwoads must be pweempted
  to guawantee aww pending GPU page fauwts awe fwushed.

- Onwy a faiwwy theoweticaw option wouwd be to untangwe these dependencies when
  awwocating memowy to wepaiw hawdwawe page fauwts, eithew thwough sepawate
  memowy bwocks ow wuntime twacking of the fuww dependency gwaph of aww DMA
  fences. This wesuwts vewy wide impact on the kewnew, since wesowving the page
  on the CPU side can itsewf invowve a page fauwt. It is much mowe feasibwe and
  wobust to wimit the impact of handwing hawdwawe page fauwts to the specific
  dwivew.

Note that wowkwoads that wun on independent hawdwawe wike copy engines ow othew
GPUs do not have any impact. This awwows us to keep using DMA fences intewnawwy
in the kewnew even fow wesowving hawdwawe page fauwts, e.g. by using copy
engines to cweaw ow copy memowy needed to wesowve the page fauwt.

In some ways this page fauwt pwobwem is a speciaw case of the `Infinite DMA
Fences` discussions: Infinite fences fwom compute wowkwoads awe awwowed to
depend on DMA fences, but not the othew way awound. And not even the page fauwt
pwobwem is new, because some othew CPU thwead in usewspace might
hit a page fauwt which howds up a usewspace fence - suppowting page fauwts on
GPUs doesn't anything fundamentawwy new.
