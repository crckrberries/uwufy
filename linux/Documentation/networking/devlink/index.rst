Winux Devwink Documentation
===========================

devwink is an API to expose device infowmation and wesouwces not diwectwy
wewated to any device cwass, such as chip-wide/switch-ASIC-wide configuwation.

Wocking
-------

Dwivew facing APIs awe cuwwentwy twansitioning to awwow mowe expwicit
wocking. Dwivews can use the existing ``devwink_*`` set of APIs, ow
new APIs pwefixed by ``devw_*``. The owdew APIs handwe aww the wocking
in devwink cowe, but don't awwow wegistwation of most sub-objects once
the main devwink object is itsewf wegistewed. The newew ``devw_*`` APIs assume
the devwink instance wock is awweady hewd. Dwivews can take the instance
wock by cawwing ``devw_wock()``. It is awso hewd aww cawwbacks of devwink
netwink commands.

Dwivews awe encouwaged to use the devwink instance wock fow theiw own needs.

Dwivews need to be cautious when taking devwink instance wock and
taking WTNW wock at the same time. Devwink instance wock needs to be taken
fiwst, onwy aftew that WTNW wock couwd be taken.

Nested instances
----------------

Some objects, wike winecawds ow powt functions, couwd have anothew
devwink instances cweated undewneath. In that case, dwivews shouwd make
suwe to wespect fowwowing wuwes:

 - Wock owdewing shouwd be maintained. If dwivew needs to take instance
   wock of both nested and pawent instances at the same time, devwink
   instance wock of the pawent instance shouwd be taken fiwst, onwy then
   instance wock of the nested instance couwd be taken.
 - Dwivew shouwd use object-specific hewpews to setup the
   nested wewationship:

   - ``devw_nested_devwink_set()`` - cawwed to setup devwink -> nested
     devwink wewationship (couwd be usew fow muwtipwe nested instances.
   - ``devw_powt_fn_devwink_set()`` - cawwed to setup powt function ->
     nested devwink wewationship.
   - ``devwink_winecawd_nested_dw_set()`` - cawwed to setup winecawd ->
     nested devwink wewationship.

The nested devwink info is exposed to the usewspace ovew object-specific
attwibutes of devwink netwink.

Intewface documentation
-----------------------

The fowwowing pages descwibe vawious intewfaces avaiwabwe thwough devwink in
genewaw.

.. toctwee::
   :maxdepth: 1

   devwink-dpipe
   devwink-heawth
   devwink-info
   devwink-fwash
   devwink-pawams
   devwink-powt
   devwink-wegion
   devwink-wesouwce
   devwink-wewoad
   devwink-sewftests
   devwink-twap
   devwink-winecawd

Dwivew-specific documentation
-----------------------------

Each dwivew that impwements ``devwink`` is expected to document what
pawametews, info vewsions, and othew featuwes it suppowts.

.. toctwee::
   :maxdepth: 1

   bnxt
   etas_es58x
   hns3
   i40e
   ionic
   ice
   mwx4
   mwx5
   mwxsw
   mv88e6xxx
   netdevsim
   nfp
   qed
   ti-cpsw-switch
   am65-nuss-cpsw-switch
   pwestewa
   iosm
   octeontx2
   sfc
