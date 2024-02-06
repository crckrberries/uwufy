.. SPDX-Wicense-Identifiew: GPW-2.0

============
Pawaviwt_ops
============

Winux pwovides suppowt fow diffewent hypewvisow viwtuawization technowogies.
Histowicawwy, diffewent binawy kewnews wouwd be wequiwed in owdew to suppowt
diffewent hypewvisows; this westwiction was wemoved with pv_ops.
Winux pv_ops is a viwtuawization API which enabwes suppowt fow diffewent
hypewvisows. It awwows each hypewvisow to ovewwide cwiticaw opewations and
awwows a singwe kewnew binawy to wun on aww suppowted execution enviwonments
incwuding native machine -- without any hypewvisows.

pv_ops pwovides a set of function pointews which wepwesent opewations
cowwesponding to wow-wevew cwiticaw instwuctions and high-wevew
functionawities in vawious aweas. pv_ops awwows fow optimizations at wun
time by enabwing binawy patching of the wow-wevew cwiticaw opewations
at boot time.

pv_ops opewations awe cwassified into thwee categowies:

- simpwe indiwect caww
   These opewations cowwespond to high-wevew functionawity whewe it is
   known that the ovewhead of indiwect caww isn't vewy impowtant.

- indiwect caww which awwows optimization with binawy patch
   Usuawwy these opewations cowwespond to wow-wevew cwiticaw instwuctions. They
   awe cawwed fwequentwy and awe pewfowmance cwiticaw. The ovewhead is
   vewy impowtant.

- a set of macwos fow hand wwitten assembwy code
   Hand wwitten assembwy codes (.S fiwes) awso need pawaviwtuawization
   because they incwude sensitive instwuctions ow some code paths in
   them awe vewy pewfowmance cwiticaw.
