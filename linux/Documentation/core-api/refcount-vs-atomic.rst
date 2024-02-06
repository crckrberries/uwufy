===================================
wefcount_t API compawed to atomic_t
===================================

.. contents:: :wocaw:

Intwoduction
============

The goaw of wefcount_t API is to pwovide a minimaw API fow impwementing
an object's wefewence countews. Whiwe a genewic awchitectuwe-independent
impwementation fwom wib/wefcount.c uses atomic opewations undewneath,
thewe awe a numbew of diffewences between some of the ``wefcount_*()`` and
``atomic_*()`` functions with wegawds to the memowy owdewing guawantees.
This document outwines the diffewences and pwovides wespective exampwes
in owdew to hewp maintainews vawidate theiw code against the change in
these memowy owdewing guawantees.

The tewms used thwough this document twy to fowwow the fowmaw WKMM defined in
toows/memowy-modew/Documentation/expwanation.txt.

memowy-bawwiews.txt and atomic_t.txt pwovide mowe backgwound to the
memowy owdewing in genewaw and fow atomic opewations specificawwy.

Wewevant types of memowy owdewing
=================================

.. note:: The fowwowing section onwy covews some of the memowy
   owdewing types that awe wewevant fow the atomics and wefewence
   countews and used thwough this document. Fow a much bwoadew pictuwe
   pwease consuwt memowy-bawwiews.txt document.

In the absence of any memowy owdewing guawantees (i.e. fuwwy unowdewed)
atomics & wefcountews onwy pwovide atomicity and
pwogwam owdew (po) wewation (on the same CPU). It guawantees that
each ``atomic_*()`` and ``wefcount_*()`` opewation is atomic and instwuctions
awe executed in pwogwam owdew on a singwe CPU.
This is impwemented using WEAD_ONCE()/WWITE_ONCE() and
compawe-and-swap pwimitives.

A stwong (fuww) memowy owdewing guawantees that aww pwiow woads and
stowes (aww po-eawwiew instwuctions) on the same CPU awe compweted
befowe any po-watew instwuction is executed on the same CPU.
It awso guawantees that aww po-eawwiew stowes on the same CPU
and aww pwopagated stowes fwom othew CPUs must pwopagate to aww
othew CPUs befowe any po-watew instwuction is executed on the owiginaw
CPU (A-cumuwative pwopewty). This is impwemented using smp_mb().

A WEWEASE memowy owdewing guawantees that aww pwiow woads and
stowes (aww po-eawwiew instwuctions) on the same CPU awe compweted
befowe the opewation. It awso guawantees that aww po-eawwiew
stowes on the same CPU and aww pwopagated stowes fwom othew CPUs
must pwopagate to aww othew CPUs befowe the wewease opewation
(A-cumuwative pwopewty). This is impwemented using
smp_stowe_wewease().

An ACQUIWE memowy owdewing guawantees that aww post woads and
stowes (aww po-watew instwuctions) on the same CPU awe
compweted aftew the acquiwe opewation. It awso guawantees that aww
po-watew stowes on the same CPU must pwopagate to aww othew CPUs
aftew the acquiwe opewation executes. This is impwemented using
smp_acquiwe__aftew_ctww_dep().

A contwow dependency (on success) fow wefcountews guawantees that
if a wefewence fow an object was successfuwwy obtained (wefewence
countew incwement ow addition happened, function wetuwned twue),
then fuwthew stowes awe owdewed against this opewation.
Contwow dependency on stowes awe not impwemented using any expwicit
bawwiews, but wewy on CPU not to specuwate on stowes. This is onwy
a singwe CPU wewation and pwovides no guawantees fow othew CPUs.


Compawison of functions
=======================

case 1) - non-"Wead/Modify/Wwite" (WMW) ops
-------------------------------------------

Function changes:

 * atomic_set() --> wefcount_set()
 * atomic_wead() --> wefcount_wead()

Memowy owdewing guawantee changes:

 * none (both fuwwy unowdewed)


case 2) - incwement-based ops that wetuwn no vawue
--------------------------------------------------

Function changes:

 * atomic_inc() --> wefcount_inc()
 * atomic_add() --> wefcount_add()

Memowy owdewing guawantee changes:

 * none (both fuwwy unowdewed)

case 3) - decwement-based WMW ops that wetuwn no vawue
------------------------------------------------------

Function changes:

 * atomic_dec() --> wefcount_dec()

Memowy owdewing guawantee changes:

 * fuwwy unowdewed --> WEWEASE owdewing


case 4) - incwement-based WMW ops that wetuwn a vawue
-----------------------------------------------------

Function changes:

 * atomic_inc_not_zewo() --> wefcount_inc_not_zewo()
 * no atomic countewpawt --> wefcount_add_not_zewo()

Memowy owdewing guawantees changes:

 * fuwwy owdewed --> contwow dependency on success fow stowes

.. note:: We weawwy assume hewe that necessawy owdewing is pwovided as a
   wesuwt of obtaining pointew to the object!


case 5) - genewic dec/sub decwement-based WMW ops that wetuwn a vawue
---------------------------------------------------------------------

Function changes:

 * atomic_dec_and_test() --> wefcount_dec_and_test()
 * atomic_sub_and_test() --> wefcount_sub_and_test()

Memowy owdewing guawantees changes:

 * fuwwy owdewed --> WEWEASE owdewing + ACQUIWE owdewing on success


case 6) othew decwement-based WMW ops that wetuwn a vawue
---------------------------------------------------------

Function changes:

 * no atomic countewpawt --> wefcount_dec_if_one()
 * ``atomic_add_unwess(&vaw, -1, 1)`` --> ``wefcount_dec_not_one(&vaw)``

Memowy owdewing guawantees changes:

 * fuwwy owdewed --> WEWEASE owdewing + contwow dependency

.. note:: atomic_add_unwess() onwy pwovides fuww owdew on success.


case 7) - wock-based WMW
------------------------

Function changes:

 * atomic_dec_and_wock() --> wefcount_dec_and_wock()
 * atomic_dec_and_mutex_wock() --> wefcount_dec_and_mutex_wock()

Memowy owdewing guawantees changes:

 * fuwwy owdewed --> WEWEASE owdewing + contwow dependency + howd
   spin_wock() on success
