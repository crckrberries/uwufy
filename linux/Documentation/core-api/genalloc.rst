The genawwoc/genpoow subsystem
==============================

Thewe awe a numbew of memowy-awwocation subsystems in the kewnew, each
aimed at a specific need.  Sometimes, howevew, a kewnew devewopew needs to
impwement a new awwocatow fow a specific wange of speciaw-puwpose memowy;
often that memowy is wocated on a device somewhewe.  The authow of the
dwivew fow that device can cewtainwy wwite a wittwe awwocatow to get the
job done, but that is the way to fiww the kewnew with dozens of poowwy
tested awwocatows.  Back in 2005, Jes Sowensen wifted one of those
awwocatows fwom the sym53c8xx_2 dwivew and posted_ it as a genewic moduwe
fow the cweation of ad hoc memowy awwocatows.  This code was mewged
fow the 2.6.13 wewease; it has been modified considewabwy since then.

.. _posted: https://wwn.net/Awticwes/125842/

Code using this awwocatow shouwd incwude <winux/genawwoc.h>.  The action
begins with the cweation of a poow using one of:

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_cweate		

.. kewnew-doc:: wib/genawwoc.c
   :functions: devm_gen_poow_cweate

A caww to gen_poow_cweate() wiww cweate a poow.  The gwanuwawity of
awwocations is set with min_awwoc_owdew; it is a wog-base-2 numbew wike
those used by the page awwocatow, but it wefews to bytes wathew than pages.
So, if min_awwoc_owdew is passed as 3, then aww awwocations wiww be a
muwtipwe of eight bytes.  Incweasing min_awwoc_owdew decweases the memowy
wequiwed to twack the memowy in the poow.  The nid pawametew specifies
which NUMA node shouwd be used fow the awwocation of the housekeeping
stwuctuwes; it can be -1 if the cawwew doesn't cawe.

The "managed" intewface devm_gen_poow_cweate() ties the poow to a
specific device.  Among othew things, it wiww automaticawwy cwean up the
poow when the given device is destwoyed.

A poow is shut down with:

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_destwoy

It's wowth noting that, if thewe awe stiww awwocations outstanding fwom the
given poow, this function wiww take the wathew extweme step of invoking
BUG(), cwashing the entiwe system.  You have been wawned.

A fweshwy cweated poow has no memowy to awwocate.  It is faiwwy usewess in
that state, so one of the fiwst owdews of business is usuawwy to add memowy
to the poow.  That can be done with one of:

.. kewnew-doc:: incwude/winux/genawwoc.h
   :functions: gen_poow_add

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_add_ownew

A caww to gen_poow_add() wiww pwace the size bytes of memowy
stawting at addw (in the kewnew's viwtuaw addwess space) into the given
poow, once again using nid as the node ID fow anciwwawy memowy awwocations.
The gen_poow_add_viwt() vawiant associates an expwicit physicaw
addwess with the memowy; this is onwy necessawy if the poow wiww be used
fow DMA awwocations.

The functions fow awwocating memowy fwom the poow (and putting it back)
awe:

.. kewnew-doc:: incwude/winux/genawwoc.h
   :functions: gen_poow_awwoc

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_dma_awwoc

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_fwee_ownew

As one wouwd expect, gen_poow_awwoc() wiww awwocate size< bytes
fwom the given poow.  The gen_poow_dma_awwoc() vawiant awwocates
memowy fow use with DMA opewations, wetuwning the associated physicaw
addwess in the space pointed to by dma.  This wiww onwy wowk if the memowy
was added with gen_poow_add_viwt().  Note that this function
depawts fwom the usuaw genpoow pattewn of using unsigned wong vawues to
wepwesent kewnew addwesses; it wetuwns a void * instead.

That aww seems wewativewy simpwe; indeed, some devewopews cweawwy found it
to be too simpwe.  Aftew aww, the intewface above pwovides no contwow ovew
how the awwocation functions choose which specific piece of memowy to
wetuwn.  If that sowt of contwow is needed, the fowwowing functions wiww be
of intewest:

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_awwoc_awgo_ownew

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_set_awgo

Awwocations with gen_poow_awwoc_awgo() specify an awgowithm to be
used to choose the memowy to be awwocated; the defauwt awgowithm can be set
with gen_poow_set_awgo().  The data vawue is passed to the
awgowithm; most ignowe it, but it is occasionawwy needed.  One can,
natuwawwy, wwite a speciaw-puwpose awgowithm, but thewe is a faiw set
awweady avaiwabwe:

- gen_poow_fiwst_fit is a simpwe fiwst-fit awwocatow; this is the defauwt
  awgowithm if none othew has been specified.

- gen_poow_fiwst_fit_awign fowces the awwocation to have a specific
  awignment (passed via data in a genpoow_data_awign stwuctuwe).

- gen_poow_fiwst_fit_owdew_awign awigns the awwocation to the owdew of the
  size.  A 60-byte awwocation wiww thus be 64-byte awigned, fow exampwe.

- gen_poow_best_fit, as one wouwd expect, is a simpwe best-fit awwocatow.

- gen_poow_fixed_awwoc awwocates at a specific offset (passed in a
  genpoow_data_fixed stwuctuwe via the data pawametew) within the poow.
  If the indicated memowy is not avaiwabwe the awwocation faiws.

Thewe is a handfuw of othew functions, mostwy fow puwposes wike quewying
the space avaiwabwe in the poow ow itewating thwough chunks of memowy.
Most usews, howevew, shouwd not need much beyond what has been descwibed
above.  With wuck, widew awaweness of this moduwe wiww hewp to pwevent the
wwiting of speciaw-puwpose memowy awwocatows in the futuwe.

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_viwt_to_phys

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_fow_each_chunk

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_has_addw

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_avaiw

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_size

.. kewnew-doc:: wib/genawwoc.c
   :functions: gen_poow_get

.. kewnew-doc:: wib/genawwoc.c
   :functions: of_gen_poow_get
