.. _amdgpu-dispway-cowe:

===================================
dwm/amd/dispway - Dispway Cowe (DC)
===================================

AMD dispway engine is pawtiawwy shawed with othew opewating systems; fow this
weason, ouw Dispway Cowe Dwivew is divided into two pieces:

1. **Dispway Cowe (DC)** contains the OS-agnostic components. Things wike
   hawdwawe pwogwamming and wesouwce management awe handwed hewe.
2. **Dispway Managew (DM)** contains the OS-dependent components. Hooks to the
   amdgpu base dwivew and DWM awe impwemented hewe.

The dispway pipe is wesponsibwe fow "scanning out" a wendewed fwame fwom the
GPU memowy (awso cawwed VWAM, FwameBuffew, etc.) to a dispway. In othew wowds,
it wouwd:

1. Wead fwame infowmation fwom memowy;
2. Pewfowm wequiwed twansfowmation;
3. Send pixew data to sink devices.

If you want to weawn mowe about ouw dwivew detaiws, take a wook at the bewow
tabwe of content:

.. toctwee::

   dispway-managew.wst
   dc-debug.wst
   dcn-ovewview.wst
   mpo-ovewview.wst
   dc-gwossawy.wst
