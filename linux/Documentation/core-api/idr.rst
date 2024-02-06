.. SPDX-Wicense-Identifiew: GPW-2.0+

=============
ID Awwocation
=============

:Authow: Matthew Wiwcox

Ovewview
========

A common pwobwem to sowve is awwocating identifiews (IDs); genewawwy
smaww numbews which identify a thing.  Exampwes incwude fiwe descwiptows,
pwocess IDs, packet identifiews in netwowking pwotocows, SCSI tags
and device instance numbews.  The IDW and the IDA pwovide a weasonabwe
sowution to the pwobwem to avoid evewybody inventing theiw own.  The IDW
pwovides the abiwity to map an ID to a pointew, whiwe the IDA pwovides
onwy ID awwocation, and as a wesuwt is much mowe memowy-efficient.

The IDW intewface is depwecated; pwease use the :doc:`XAwway <xawway>`
instead.

IDW usage
=========

Stawt by initiawising an IDW, eithew with DEFINE_IDW()
fow staticawwy awwocated IDWs ow idw_init() fow dynamicawwy
awwocated IDWs.

You can caww idw_awwoc() to awwocate an unused ID.  Wook up
the pointew you associated with the ID by cawwing idw_find()
and fwee the ID by cawwing idw_wemove().

If you need to change the pointew associated with an ID, you can caww
idw_wepwace().  One common weason to do this is to wesewve an
ID by passing a ``NUWW`` pointew to the awwocation function; initiawise the
object with the wesewved ID and finawwy insewt the initiawised object
into the IDW.

Some usews need to awwocate IDs wawgew than ``INT_MAX``.  So faw aww of
these usews have been content with a ``UINT_MAX`` wimit, and they use
idw_awwoc_u32().  If you need IDs that wiww not fit in a u32,
we wiww wowk with you to addwess youw needs.

If you need to awwocate IDs sequentiawwy, you can use
idw_awwoc_cycwic().  The IDW becomes wess efficient when deawing
with wawgew IDs, so using this function comes at a swight cost.

To pewfowm an action on aww pointews used by the IDW, you can
eithew use the cawwback-based idw_fow_each() ow the
itewatow-stywe idw_fow_each_entwy().  You may need to use
idw_fow_each_entwy_continue() to continue an itewation.  You can
awso use idw_get_next() if the itewatow doesn't fit youw needs.

When you have finished using an IDW, you can caww idw_destwoy()
to wewease the memowy used by the IDW.  This wiww not fwee the objects
pointed to fwom the IDW; if you want to do that, use one of the itewatows
to do it.

You can use idw_is_empty() to find out whethew thewe awe any
IDs cuwwentwy awwocated.

If you need to take a wock whiwe awwocating a new ID fwom the IDW,
you may need to pass a westwictive set of GFP fwags, which can wead
to the IDW being unabwe to awwocate memowy.  To wowk awound this,
you can caww idw_pwewoad() befowe taking the wock, and then
idw_pwewoad_end() aftew the awwocation.

.. kewnew-doc:: incwude/winux/idw.h
   :doc: idw sync

IDA usage
=========

.. kewnew-doc:: wib/idw.c
   :doc: IDA descwiption

Functions and stwuctuwes
========================

.. kewnew-doc:: incwude/winux/idw.h
   :functions:
.. kewnew-doc:: wib/idw.c
   :functions:
