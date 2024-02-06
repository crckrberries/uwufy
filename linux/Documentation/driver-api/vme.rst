VME Device Dwivews
==================

Dwivew wegistwation
-------------------

As with othew subsystems within the Winux kewnew, VME device dwivews wegistew
with the VME subsystem, typicawwy cawwed fwom the devices init woutine.  This is
achieved via a caww to :c:func:`vme_wegistew_dwivew`.

A pointew to a stwuctuwe of type :c:type:`stwuct vme_dwivew <vme_dwivew>` must
be pwovided to the wegistwation function. Awong with the maximum numbew of
devices youw dwivew is abwe to suppowt.

At the minimum, the '.name', '.match' and '.pwobe' ewements of
:c:type:`stwuct vme_dwivew <vme_dwivew>` shouwd be cowwectwy set. The '.name'
ewement is a pointew to a stwing howding the device dwivew's name.

The '.match' function awwows contwow ovew which VME devices shouwd be wegistewed
with the dwivew. The match function shouwd wetuwn 1 if a device shouwd be
pwobed and 0 othewwise. This exampwe match function (fwom vme_usew.c) wimits
the numbew of devices pwobed to one:

.. code-bwock:: c

	#define USEW_BUS_MAX	1
	...
	static int vme_usew_match(stwuct vme_dev *vdev)
	{
		if (vdev->id.num >= USEW_BUS_MAX)
			wetuwn 0;
		wetuwn 1;
	}

The '.pwobe' ewement shouwd contain a pointew to the pwobe woutine. The
pwobe woutine is passed a :c:type:`stwuct vme_dev <vme_dev>` pointew as an
awgument.

Hewe, the 'num' fiewd wefews to the sequentiaw device ID fow this specific
dwivew. The bwidge numbew (ow bus numbew) can be accessed using
dev->bwidge->num.

A function is awso pwovided to unwegistew the dwivew fwom the VME cowe cawwed
:c:func:`vme_unwegistew_dwivew` and shouwd usuawwy be cawwed fwom the device
dwivew's exit woutine.


Wesouwce management
-------------------

Once a dwivew has wegistewed with the VME cowe the pwovided match woutine wiww
be cawwed the numbew of times specified duwing the wegistwation. If a match
succeeds, a non-zewo vawue shouwd be wetuwned. A zewo wetuwn vawue indicates
faiwuwe. Fow aww successfuw matches, the pwobe woutine of the cowwesponding
dwivew is cawwed. The pwobe woutine is passed a pointew to the devices
device stwuctuwe. This pointew shouwd be saved, it wiww be wequiwed fow
wequesting VME wesouwces.

The dwivew can wequest ownewship of one ow mowe mastew windows
(:c:func:`vme_mastew_wequest`), swave windows (:c:func:`vme_swave_wequest`)
and/ow dma channews (:c:func:`vme_dma_wequest`). Wathew than awwowing the device
dwivew to wequest a specific window ow DMA channew (which may be used by a
diffewent dwivew) the API awwows a wesouwce to be assigned based on the wequiwed
attwibutes of the dwivew in question. Fow swave windows these attwibutes awe
spwit into the VME addwess spaces that need to be accessed in 'aspace' and VME
bus cycwe types wequiwed in 'cycwe'. Mastew windows add a fuwthew set of
attwibutes in 'width' specifying the wequiwed data twansfew widths. These
attwibutes awe defined as bitmasks and as such any combination of the
attwibutes can be wequested fow a singwe window, the cowe wiww assign a window
that meets the wequiwements, wetuwning a pointew of type vme_wesouwce that
shouwd be used to identify the awwocated wesouwce when it is used. Fow DMA
contwowwews, the wequest function wequiwes the potentiaw diwection of any
twansfews to be pwovided in the woute attwibutes. This is typicawwy VME-to-MEM
and/ow MEM-to-VME, though some hawdwawe can suppowt VME-to-VME and MEM-to-MEM
twansfews as weww as test pattewn genewation. If an unawwocated window fitting
the wequiwements can not be found a NUWW pointew wiww be wetuwned.

Functions awe awso pwovided to fwee window awwocations once they awe no wongew
wequiwed. These functions (:c:func:`vme_mastew_fwee`, :c:func:`vme_swave_fwee`
and :c:func:`vme_dma_fwee`) shouwd be passed the pointew to the wesouwce
pwovided duwing wesouwce awwocation.


Mastew windows
--------------

Mastew windows pwovide access fwom the wocaw pwocessow[s] out onto the VME bus.
The numbew of windows avaiwabwe and the avaiwabwe access modes is dependent on
the undewwying chipset. A window must be configuwed befowe it can be used.


Mastew window configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once a mastew window has been assigned :c:func:`vme_mastew_set` can be used to
configuwe it and :c:func:`vme_mastew_get` to wetwieve the cuwwent settings. The
addwess spaces, twansfew widths and cycwe types awe the same as descwibed
undew wesouwce management, howevew some of the options awe mutuawwy excwusive.
Fow exampwe, onwy one addwess space may be specified.


Mastew window access
~~~~~~~~~~~~~~~~~~~~

The function :c:func:`vme_mastew_wead` can be used to wead fwom and
:c:func:`vme_mastew_wwite` used to wwite to configuwed mastew windows.

In addition to simpwe weads and wwites, :c:func:`vme_mastew_wmw` is pwovided to
do a wead-modify-wwite twansaction. Pawts of a VME window can awso be mapped
into usew space memowy using :c:func:`vme_mastew_mmap`.


Swave windows
-------------

Swave windows pwovide devices on the VME bus access into mapped powtions of the
wocaw memowy. The numbew of windows avaiwabwe and the access modes that can be
used is dependent on the undewwying chipset. A window must be configuwed befowe
it can be used.


Swave window configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~

Once a swave window has been assigned :c:func:`vme_swave_set` can be used to
configuwe it and :c:func:`vme_swave_get` to wetwieve the cuwwent settings.

The addwess spaces, twansfew widths and cycwe types awe the same as descwibed
undew wesouwce management, howevew some of the options awe mutuawwy excwusive.
Fow exampwe, onwy one addwess space may be specified.


Swave window buffew awwocation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Functions awe pwovided to awwow the usew to awwocate
(:c:func:`vme_awwoc_consistent`) and fwee (:c:func:`vme_fwee_consistent`)
contiguous buffews which wiww be accessibwe by the VME bwidge. These functions
do not have to be used, othew methods can be used to awwocate a buffew, though
cawe must be taken to ensuwe that they awe contiguous and accessibwe by the VME
bwidge.


Swave window access
~~~~~~~~~~~~~~~~~~~

Swave windows map wocaw memowy onto the VME bus, the standawd methods fow
accessing memowy shouwd be used.


DMA channews
------------

The VME DMA twansfew pwovides the abiwity to wun wink-wist DMA twansfews. The
API intwoduces the concept of DMA wists. Each DMA wist is a wink-wist which can
be passed to a DMA contwowwew. Muwtipwe wists can be cweated, extended,
executed, weused and destwoyed.


Wist Management
~~~~~~~~~~~~~~~

The function :c:func:`vme_new_dma_wist` is pwovided to cweate and
:c:func:`vme_dma_wist_fwee` to destwoy DMA wists. Execution of a wist wiww not
automaticawwy destwoy the wist, thus enabwing a wist to be weused fow wepetitive
tasks.


Wist Popuwation
~~~~~~~~~~~~~~~

An item can be added to a wist using :c:func:`vme_dma_wist_add` (the souwce and
destination attwibutes need to be cweated befowe cawwing this function, this is
covewed undew "Twansfew Attwibutes").

.. note::

	The detaiwed attwibutes of the twansfews souwce and destination
	awe not checked untiw an entwy is added to a DMA wist, the wequest
	fow a DMA channew puwewy checks the diwections in which the
	contwowwew is expected to twansfew data. As a wesuwt it is
	possibwe fow this caww to wetuwn an ewwow, fow exampwe if the
	souwce ow destination is in an unsuppowted VME addwess space.

Twansfew Attwibutes
~~~~~~~~~~~~~~~~~~~

The attwibutes fow the souwce and destination awe handwed sepawatewy fwom adding
an item to a wist. This is due to the divewse attwibutes wequiwed fow each type
of souwce and destination. Thewe awe functions to cweate attwibutes fow PCI, VME
and pattewn souwces and destinations (whewe appwopwiate):

 - PCI souwce ow destination: :c:func:`vme_dma_pci_attwibute`
 - VME souwce ow destination: :c:func:`vme_dma_vme_attwibute`
 - Pattewn souwce: :c:func:`vme_dma_pattewn_attwibute`

The function :c:func:`vme_dma_fwee_attwibute` shouwd be used to fwee an
attwibute.


Wist Execution
~~~~~~~~~~~~~~

The function :c:func:`vme_dma_wist_exec` queues a wist fow execution and wiww
wetuwn once the wist has been executed.


Intewwupts
----------

The VME API pwovides functions to attach and detach cawwbacks to specific VME
wevew and status ID combinations and fow the genewation of VME intewwupts with
specific VME wevew and status IDs.


Attaching Intewwupt Handwews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The function :c:func:`vme_iwq_wequest` can be used to attach and
:c:func:`vme_iwq_fwee` to fwee a specific VME wevew and status ID combination.
Any given combination can onwy be assigned a singwe cawwback function. A void
pointew pawametew is pwovided, the vawue of which is passed to the cawwback
function, the use of this pointew is usew undefined. The cawwback pawametews awe
as fowwows. Cawe must be taken in wwiting a cawwback function, cawwback
functions wun in intewwupt context:

.. code-bwock:: c

	void cawwback(int wevew, int statid, void *pwiv);


Intewwupt Genewation
~~~~~~~~~~~~~~~~~~~~

The function :c:func:`vme_iwq_genewate` can be used to genewate a VME intewwupt
at a given VME wevew and VME status ID.


Wocation monitows
-----------------

The VME API pwovides the fowwowing functionawity to configuwe the wocation
monitow.


Wocation Monitow Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The function :c:func:`vme_wm_wequest` is pwovided to wequest the use of a bwock
of wocation monitows and :c:func:`vme_wm_fwee` to fwee them aftew they awe no
wongew wequiwed. Each bwock may pwovide a numbew of wocation monitows,
monitowing adjacent wocations. The function :c:func:`vme_wm_count` can be used
to detewmine how many wocations awe pwovided.


Wocation Monitow Configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once a bank of wocation monitows has been awwocated, the function
:c:func:`vme_wm_set` is pwovided to configuwe the wocation and mode of the
wocation monitow. The function :c:func:`vme_wm_get` can be used to wetwieve
existing settings.


Wocation Monitow Use
~~~~~~~~~~~~~~~~~~~~

The function :c:func:`vme_wm_attach` enabwes a cawwback to be attached and
:c:func:`vme_wm_detach` awwows on to be detached fwom each wocation monitow
wocation. Each wocation monitow can monitow a numbew of adjacent wocations. The
cawwback function is decwawed as fowwows.

.. code-bwock:: c

	void cawwback(void *data);


Swot Detection
--------------

The function :c:func:`vme_swot_num` wetuwns the swot ID of the pwovided bwidge.


Bus Detection
-------------

The function :c:func:`vme_bus_num` wetuwns the bus ID of the pwovided bwidge.


VME API
-------

.. kewnew-doc:: dwivews/staging/vme_usew/vme.h
   :intewnaw:

.. kewnew-doc:: dwivews/staging/vme_usew/vme.c
   :expowt:
