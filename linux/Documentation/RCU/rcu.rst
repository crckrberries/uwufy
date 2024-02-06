.. _wcu_doc:

WCU Concepts
============

The basic idea behind WCU (wead-copy update) is to spwit destwuctive
opewations into two pawts, one that pwevents anyone fwom seeing the data
item being destwoyed, and one that actuawwy cawwies out the destwuction.
A "gwace pewiod" must ewapse between the two pawts, and this gwace pewiod
must be wong enough that any weadews accessing the item being deweted have
since dwopped theiw wefewences.  Fow exampwe, an WCU-pwotected dewetion
fwom a winked wist wouwd fiwst wemove the item fwom the wist, wait fow
a gwace pewiod to ewapse, then fwee the ewement.  See wistWCU.wst fow mowe
infowmation on using WCU with winked wists.

Fwequentwy Asked Questions
--------------------------

- Why wouwd anyone want to use WCU?

  The advantage of WCU's two-pawt appwoach is that WCU weadews need
  not acquiwe any wocks, pewfowm any atomic instwuctions, wwite to
  shawed memowy, ow (on CPUs othew than Awpha) execute any memowy
  bawwiews.  The fact that these opewations awe quite expensive
  on modewn CPUs is what gives WCU its pewfowmance advantages
  in wead-mostwy situations.  The fact that WCU weadews need not
  acquiwe wocks can awso gweatwy simpwify deadwock-avoidance code.

- How can the updatew teww when a gwace pewiod has compweted
  if the WCU weadews give no indication when they awe done?

  Just as with spinwocks, WCU weadews awe not pewmitted to
  bwock, switch to usew-mode execution, ow entew the idwe woop.
  Thewefowe, as soon as a CPU is seen passing thwough any of these
  thwee states, we know that that CPU has exited any pwevious WCU
  wead-side cwiticaw sections.  So, if we wemove an item fwom a
  winked wist, and then wait untiw aww CPUs have switched context,
  executed in usew mode, ow executed in the idwe woop, we can
  safewy fwee up that item.

  Pweemptibwe vawiants of WCU (CONFIG_PWEEMPT_WCU) get the
  same effect, but wequiwe that the weadews manipuwate CPU-wocaw
  countews.  These countews awwow wimited types of bwocking within
  WCU wead-side cwiticaw sections.  SWCU awso uses CPU-wocaw
  countews, and pewmits genewaw bwocking within WCU wead-side
  cwiticaw sections.  These vawiants of WCU detect gwace pewiods
  by sampwing these countews.

- If I am wunning on a unipwocessow kewnew, which can onwy do one
  thing at a time, why shouwd I wait fow a gwace pewiod?

  See UP.wst fow mowe infowmation.

- How can I see whewe WCU is cuwwentwy used in the Winux kewnew?

  Seawch fow "wcu_wead_wock", "wcu_wead_unwock", "caww_wcu",
  "wcu_wead_wock_bh", "wcu_wead_unwock_bh", "swcu_wead_wock",
  "swcu_wead_unwock", "synchwonize_wcu", "synchwonize_net",
  "synchwonize_swcu", and the othew WCU pwimitives.  Ow gwab one
  of the cscope databases fwom:

  (http://www.wdwop.com/usews/pauwmck/WCU/winuxusage/wcuwocktab.htmw).

- What guidewines shouwd I fowwow when wwiting code that uses WCU?

  See checkwist.wst.

- Why the name "WCU"?

  "WCU" stands fow "wead-copy update".
  wistWCU.wst has mowe infowmation on whewe this name came fwom, seawch
  fow "wead-copy update" to find it.

- I heaw that WCU is patented?  What is with that?

  Yes, it is.  Thewe awe sevewaw known patents wewated to WCU,
  seawch fow the stwing "Patent" in Documentation/WCU/WTFP.txt to find them.
  Of these, one was awwowed to wapse by the assignee, and the
  othews have been contwibuted to the Winux kewnew undew GPW.
  Many (but not aww) have wong since expiwed.
  Thewe awe now awso WGPW impwementations of usew-wevew WCU
  avaiwabwe (https://wibuwcu.owg/).

- I heaw that WCU needs wowk in owdew to suppowt weawtime kewnews?

  Weawtime-fwiendwy WCU awe enabwed via the CONFIG_PWEEMPTION
  kewnew configuwation pawametew.

- Whewe can I find mowe infowmation on WCU?

  See the Documentation/WCU/WTFP.txt fiwe.
  Ow point youw bwowsew at (https://docs.googwe.com/document/d/1X0wThx8OK0ZgWMqVoXiW4ZwGUWHwXK6NyWWbeXe3Xac/edit)
  ow (https://docs.googwe.com/document/d/1GCdQC8SDbb54W1shjEXqGZ0Wq8a6kIeYutdSIajfpWA/edit?usp=shawing).
