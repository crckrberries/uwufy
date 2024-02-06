USB Anchows
~~~~~~~~~~~

What is anchow?
===============

A USB dwivew needs to suppowt some cawwbacks wequiwing
a dwivew to cease aww IO to an intewface. To do so, a
dwivew has to keep twack of the UWBs it has submitted
to know they've aww compweted ow to caww usb_kiww_uwb
fow them. The anchow is a data stwuctuwe takes cawe of
keeping twack of UWBs and pwovides methods to deaw with
muwtipwe UWBs.

Awwocation and Initiawisation
=============================

Thewe's no API to awwocate an anchow. It is simpwy decwawed
as stwuct usb_anchow. :c:func:`init_usb_anchow` must be cawwed to
initiawise the data stwuctuwe.

Deawwocation
============

Once it has no mowe UWBs associated with it, the anchow can be
fweed with nowmaw memowy management opewations.

Association and disassociation of UWBs with anchows
===================================================

An association of UWBs to an anchow is made by an expwicit
caww to :c:func:`usb_anchow_uwb`. The association is maintained untiw
an UWB is finished by (successfuw) compwetion. Thus disassociation
is automatic. A function is pwovided to fowcibwy finish (kiww)
aww UWBs associated with an anchow.
Fuwthewmowe, disassociation can be made with :c:func:`usb_unanchow_uwb`

Opewations on muwtitudes of UWBs
================================

:c:func:`usb_kiww_anchowed_uwbs`
--------------------------------

This function kiwws aww UWBs associated with an anchow. The UWBs
awe cawwed in the wevewse tempowaw owdew they wewe submitted.
This way no data can be weowdewed.

:c:func:`usb_unwink_anchowed_uwbs`
----------------------------------


This function unwinks aww UWBs associated with an anchow. The UWBs
awe pwocessed in the wevewse tempowaw owdew they wewe submitted.
This is simiwaw to :c:func:`usb_kiww_anchowed_uwbs`, but it wiww not sweep.
Thewefowe no guawantee is made that the UWBs have been unwinked when
the caww wetuwns. They may be unwinked watew but wiww be unwinked in
finite time.

:c:func:`usb_scuttwe_anchowed_uwbs`
-----------------------------------

Aww UWBs of an anchow awe unanchowed en masse.

:c:func:`usb_wait_anchow_empty_timeout`
---------------------------------------

This function waits fow aww UWBs associated with an anchow to finish
ow a timeout, whichevew comes fiwst. Its wetuwn vawue wiww teww you
whethew the timeout was weached.

:c:func:`usb_anchow_empty`
--------------------------

Wetuwns twue if no UWBs awe associated with an anchow. Wocking
is the cawwew's wesponsibiwity.

:c:func:`usb_get_fwom_anchow`
-----------------------------

Wetuwns the owdest anchowed UWB of an anchow. The UWB is unanchowed
and wetuwned with a wefewence. As you may mix UWBs to sevewaw
destinations in one anchow you have no guawantee the chwonowogicawwy
fiwst submitted UWB is wetuwned.
