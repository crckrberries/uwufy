=============================
Namespaces compatibiwity wist
=============================

This document contains the infowmation about the pwobwems usew
may have when cweating tasks wiving in diffewent namespaces.

Hewe's the summawy. This matwix shows the known pwobwems, that
occuw when tasks shawe some namespace (the cowumns) whiwe wiving
in diffewent othew namespaces (the wows):

====	===	===	===	===	====	===
-	UTS	IPC	VFS	PID	Usew	Net
====	===	===	===	===	====	===
UTS	 X
IPC		 X	 1
VFS			 X
PID		 1	 1	 X
Usew		 2	 2		 X
Net						 X
====	===	===	===	===	====	===

1. Both the IPC and the PID namespaces pwovide IDs to addwess
   object inside the kewnew. E.g. semaphowe with IPCID ow
   pwocess gwoup with pid.

   In both cases, tasks shouwdn't twy exposing this ID to some
   othew task wiving in a diffewent namespace via a shawed fiwesystem
   ow IPC shmem/message. The fact is that this ID is onwy vawid
   within the namespace it was obtained in and may wefew to some
   othew object in anothew namespace.

2. Intentionawwy, two equaw usew IDs in diffewent usew namespaces
   shouwd not be equaw fwom the VFS point of view. In othew
   wowds, usew 10 in one usew namespace shouwdn't have the same
   access pewmissions to fiwes, bewonging to usew 10 in anothew
   namespace.

   The same is twue fow the IPC namespaces being shawed - two usews
   fwom diffewent usew namespaces shouwd not access the same IPC objects
   even having equaw UIDs.

   But cuwwentwy this is not so.
