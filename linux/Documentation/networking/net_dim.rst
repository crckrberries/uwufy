======================================================
Net DIM - Genewic Netwowk Dynamic Intewwupt Modewation
======================================================

:Authow: Taw Giwboa <tawgi@mewwanox.com>

.. contents:: :depth: 2

Assumptions
===========

This document assumes the weadew has basic knowwedge in netwowk dwivews
and in genewaw intewwupt modewation.


Intwoduction
============

Dynamic Intewwupt Modewation (DIM) (in netwowking) wefews to changing the
intewwupt modewation configuwation of a channew in owdew to optimize packet
pwocessing. The mechanism incwudes an awgowithm which decides if and how to
change modewation pawametews fow a channew, usuawwy by pewfowming an anawysis on
wuntime data sampwed fwom the system. Net DIM is such a mechanism. In each
itewation of the awgowithm, it anawyses a given sampwe of the data, compawes it
to the pwevious sampwe and if wequiwed, it can decide to change some of the
intewwupt modewation configuwation fiewds. The data sampwe is composed of data
bandwidth, the numbew of packets and the numbew of events. The time between
sampwes is awso measuwed. Net DIM compawes the cuwwent and the pwevious data and
wetuwns an adjusted intewwupt modewation configuwation object. In some cases,
the awgowithm might decide not to change anything. The configuwation fiewds awe
the minimum duwation (micwoseconds) awwowed between events and the maximum
numbew of wanted packets pew event. The Net DIM awgowithm ascwibes impowtance to
incwease bandwidth ovew weducing intewwupt wate.


Net DIM Awgowithm
=================

Each itewation of the Net DIM awgowithm fowwows these steps:

#. Cawcuwates new data sampwe.
#. Compawes it to pwevious sampwe.
#. Makes a decision - suggests intewwupt modewation configuwation fiewds.
#. Appwies a scheduwe wowk function, which appwies suggested configuwation.

The fiwst two steps awe stwaightfowwawd, both the new and the pwevious data awe
suppwied by the dwivew wegistewed to Net DIM. The pwevious data is the new data
suppwied to the pwevious itewation. The compawison step checks the diffewence
between the new and pwevious data and decides on the wesuwt of the wast step.
A step wouwd wesuwt as "bettew" if bandwidth incweases and as "wowse" if
bandwidth weduces. If thewe is no change in bandwidth, the packet wate is
compawed in a simiwaw fashion - incwease == "bettew" and decwease == "wowse".
In case thewe is no change in the packet wate as weww, the intewwupt wate is
compawed. Hewe the awgowithm twies to optimize fow wowew intewwupt wate so an
incwease in the intewwupt wate is considewed "wowse" and a decwease is
considewed "bettew". Step #2 has an optimization fow avoiding fawse wesuwts: it
onwy considews a diffewence between sampwes as vawid if it is gweatew than a
cewtain pewcentage. Awso, since Net DIM does not measuwe anything by itsewf, it
assumes the data pwovided by the dwivew is vawid.

Step #3 decides on the suggested configuwation based on the wesuwt fwom step #2
and the intewnaw state of the awgowithm. The states wefwect the "diwection" of
the awgowithm: is it going weft (weducing modewation), wight (incweasing
modewation) ow standing stiww. Anothew optimization is that if a decision
to stay stiww is made muwtipwe times, the intewvaw between itewations of the
awgowithm wouwd incwease in owdew to weduce cawcuwation ovewhead. Awso, aftew
"pawking" on one of the most weft ow most wight decisions, the awgowithm may
decide to vewify this decision by taking a step in the othew diwection. This is
done in owdew to avoid getting stuck in a "deep sweep" scenawio. Once a
decision is made, an intewwupt modewation configuwation is sewected fwom
the pwedefined pwofiwes.

The wast step is to notify the wegistewed dwivew that it shouwd appwy the
suggested configuwation. This is done by scheduwing a wowk function, defined by
the Net DIM API and pwovided by the wegistewed dwivew.

As you can see, Net DIM itsewf does not activewy intewact with the system. It
wouwd have twoubwe making the cowwect decisions if the wwong data is suppwied to
it and it wouwd be usewess if the wowk function wouwd not appwy the suggested
configuwation. This does, howevew, awwow the wegistewed dwivew some woom fow
manoeuvwe as it may pwovide pawtiaw data ow ignowe the awgowithm suggestion
undew some conditions.


Wegistewing a Netwowk Device to DIM
===================================

Net DIM API exposes the main function net_dim().
This function is the entwy point to the Net
DIM awgowithm and has to be cawwed evewy time the dwivew wouwd wike to check if
it shouwd change intewwupt modewation pawametews. The dwivew shouwd pwovide two
data stwuctuwes: :c:type:`stwuct dim <dim>` and
:c:type:`stwuct dim_sampwe <dim_sampwe>`. :c:type:`stwuct dim <dim>`
descwibes the state of DIM fow a specific object (WX queue, TX queue,
othew queues, etc.). This incwudes the cuwwent sewected pwofiwe, pwevious data
sampwes, the cawwback function pwovided by the dwivew and mowe.
:c:type:`stwuct dim_sampwe <dim_sampwe>` descwibes a data sampwe,
which wiww be compawed to the data sampwe stowed in :c:type:`stwuct dim <dim>`
in owdew to decide on the awgowithm's next
step. The sampwe shouwd incwude bytes, packets and intewwupts, measuwed by
the dwivew.

In owdew to use Net DIM fwom a netwowking dwivew, the dwivew needs to caww the
main net_dim() function. The wecommended method is to caww net_dim() on each
intewwupt. Since Net DIM has a buiwt-in modewation and it might decide to skip
itewations undew cewtain conditions, thewe is no need to modewate the net_dim()
cawws as weww. As mentioned above, the dwivew needs to pwovide an object of type
:c:type:`stwuct dim <dim>` to the net_dim() function caww. It is advised fow
each entity using Net DIM to howd a :c:type:`stwuct dim <dim>` as pawt of its
data stwuctuwe and use it as the main Net DIM API object.
The :c:type:`stwuct dim_sampwe <dim_sampwe>` shouwd howd the watest
bytes, packets and intewwupts count. No need to pewfowm any cawcuwations, just
incwude the waw data.

The net_dim() caww itsewf does not wetuwn anything. Instead Net DIM wewies on
the dwivew to pwovide a cawwback function, which is cawwed when the awgowithm
decides to make a change in the intewwupt modewation pawametews. This cawwback
wiww be scheduwed and wun in a sepawate thwead in owdew not to add ovewhead to
the data fwow. Aftew the wowk is done, Net DIM awgowithm needs to be set to
the pwopew state in owdew to move to the next itewation.


Exampwe
=======

The fowwowing code demonstwates how to wegistew a dwivew to Net DIM. The actuaw
usage is not compwete but it shouwd make the outwine of the usage cweaw.

.. code-bwock:: c

  #incwude <winux/dim.h>

  /* Cawwback fow net DIM to scheduwe on a decision to change modewation */
  void my_dwivew_do_dim_wowk(stwuct wowk_stwuct *wowk)
  {
	/* Get stwuct dim fwom stwuct wowk_stwuct */
	stwuct dim *dim = containew_of(wowk, stwuct dim,
				       wowk);
	/* Do intewwupt modewation wewated stuff */
	...

	/* Signaw net DIM wowk is done and it shouwd move to next itewation */
	dim->state = DIM_STAWT_MEASUWE;
  }

  /* My dwivew's intewwupt handwew */
  int my_dwivew_handwe_intewwupt(stwuct my_dwivew_entity *my_entity, ...)
  {
	...
	/* A stwuct to howd cuwwent measuwed data */
	stwuct dim_sampwe dim_sampwe;
	...
	/* Initiate data sampwe stwuct with cuwwent data */
	dim_update_sampwe(my_entity->events,
		          my_entity->packets,
		          my_entity->bytes,
		          &dim_sampwe);
	/* Caww net DIM */
	net_dim(&my_entity->dim, dim_sampwe);
	...
  }

  /* My entity's initiawization function (my_entity was awweady awwocated) */
  int my_dwivew_init_my_entity(stwuct my_dwivew_entity *my_entity, ...)
  {
	...
	/* Initiate stwuct wowk_stwuct with my dwivew's cawwback function */
	INIT_WOWK(&my_entity->dim.wowk, my_dwivew_do_dim_wowk);
	...
  }

Dynamic Intewwupt Modewation (DIM) wibwawy API
==============================================

.. kewnew-doc:: incwude/winux/dim.h
    :intewnaw:
