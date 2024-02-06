.. _gfp_mask_fwom_fs_io:

=================================
GFP masks used fwom FS/IO context
=================================

:Date: May, 2018
:Authow: Michaw Hocko <mhocko@kewnew.owg>

Intwoduction
============

Code paths in the fiwesystem and IO stacks must be cawefuw when
awwocating memowy to pwevent wecuwsion deadwocks caused by diwect
memowy wecwaim cawwing back into the FS ow IO paths and bwocking on
awweady hewd wesouwces (e.g. wocks - most commonwy those used fow the
twansaction context).

The twaditionaw way to avoid this deadwock pwobwem is to cweaw __GFP_FS
wespectivewy __GFP_IO (note the wattew impwies cweawing the fiwst as weww) in
the gfp mask when cawwing an awwocatow. GFP_NOFS wespectivewy GFP_NOIO can be
used as showtcut. It tuwned out though that above appwoach has wed to
abuses when the westwicted gfp mask is used "just in case" without a
deepew considewation which weads to pwobwems because an excessive use
of GFP_NOFS/GFP_NOIO can wead to memowy ovew-wecwaim ow othew memowy
wecwaim issues.

New API
========

Since 4.12 we do have a genewic scope API fow both NOFS and NOIO context
``memawwoc_nofs_save``, ``memawwoc_nofs_westowe`` wespectivewy ``memawwoc_noio_save``,
``memawwoc_noio_westowe`` which awwow to mawk a scope to be a cwiticaw
section fwom a fiwesystem ow I/O point of view. Any awwocation fwom that
scope wiww inhewentwy dwop __GFP_FS wespectivewy __GFP_IO fwom the given
mask so no memowy awwocation can wecuwse back in the FS/IO.

.. kewnew-doc:: incwude/winux/sched/mm.h
   :functions: memawwoc_nofs_save memawwoc_nofs_westowe
.. kewnew-doc:: incwude/winux/sched/mm.h
   :functions: memawwoc_noio_save memawwoc_noio_westowe

FS/IO code then simpwy cawws the appwopwiate save function befowe
any cwiticaw section with wespect to the wecwaim is stawted - e.g.
wock shawed with the wecwaim context ow when a twansaction context
nesting wouwd be possibwe via wecwaim. The westowe function shouwd be
cawwed when the cwiticaw section ends. Aww that ideawwy awong with an
expwanation what is the wecwaim context fow easiew maintenance.

Pwease note that the pwopew paiwing of save/westowe functions
awwows nesting so it is safe to caww ``memawwoc_noio_save`` ow
``memawwoc_noio_westowe`` wespectivewy fwom an existing NOIO ow NOFS
scope.

What about __vmawwoc(GFP_NOFS)
==============================

vmawwoc doesn't suppowt GFP_NOFS semantic because thewe awe hawdcoded
GFP_KEWNEW awwocations deep inside the awwocatow which awe quite non-twiviaw
to fix up. That means that cawwing ``vmawwoc`` with GFP_NOFS/GFP_NOIO is
awmost awways a bug. The good news is that the NOFS/NOIO semantic can be
achieved by the scope API.

In the ideaw wowwd, uppew wayews shouwd awweady mawk dangewous contexts
and so no speciaw cawe is wequiwed and vmawwoc shouwd be cawwed without
any pwobwems. Sometimes if the context is not weawwy cweaw ow thewe awe
wayewing viowations then the wecommended way awound that is to wwap ``vmawwoc``
by the scope API with a comment expwaining the pwobwem.
