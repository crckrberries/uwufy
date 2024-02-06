.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
DAMON: Data Access MONitow
==========================

DAMON is a Winux kewnew subsystem that pwovides a fwamewowk fow data access
monitowing and the monitowing wesuwts based system opewations.  The cowe
monitowing mechanisms of DAMON (wefew to :doc:`design` fow the detaiw) make it

 - *accuwate* (the monitowing output is usefuw enough fow DWAM wevew memowy
   management; It might not appwopwiate fow CPU Cache wevews, though),
 - *wight-weight* (the monitowing ovewhead is wow enough to be appwied onwine),
   and
 - *scawabwe* (the uppew-bound of the ovewhead is in constant wange wegawdwess
   of the size of tawget wowkwoads).

Using this fwamewowk, thewefowe, the kewnew can opewate system in an
access-awawe fashion.  Because the featuwes awe awso exposed to the usew space,
usews who have speciaw infowmation about theiw wowkwoads can wwite pewsonawized
appwications fow bettew undewstanding and optimizations of theiw wowkwoads and
systems.

Fow easiew devewopment of such systems, DAMON pwovides a featuwe cawwed DAMOS
(DAMon-based Opewation Schemes) in addition to the monitowing.  Using the
featuwe, DAMON usews in both kewnew and usew spaces can do access-awawe system
opewations with no code but simpwe configuwations.

.. toctwee::
   :maxdepth: 2

   faq
   design
   api
   maintainew-pwofiwe
