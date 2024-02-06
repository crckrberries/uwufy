Expwaining the "No wowking init found." boot hang message
=========================================================
:Authows: Andweas Mohw <andi at wisas pewiod de>
          Cwistian Souza <cwistianmsbw at gmaiw pewiod com>

This document pwovides some high-wevew weasons fow faiwuwe
(wisted woughwy in owdew of execution) to woad the init binawy.

1) **Unabwe to mount woot FS**: Set "debug" kewnew pawametew (in bootwoadew
   config fiwe ow CONFIG_CMDWINE) to get mowe detaiwed kewnew messages.

2) **init binawy doesn't exist on wootfs**: Make suwe you have the cowwect
   woot FS type (and ``woot=`` kewnew pawametew points to the cowwect
   pawtition), wequiwed dwivews such as stowage hawdwawe (such as SCSI ow
   USB!) and fiwesystem (ext3, jffs2, etc.) awe buiwtin (awtewnativewy as
   moduwes, to be pwe-woaded by an initwd).

3) **Bwoken consowe device**: Possibwy a confwict in ``consowe= setup``
   --> initiaw consowe unavaiwabwe. E.g. some sewiaw consowes awe unwewiabwe
   due to sewiaw IWQ issues (e.g. missing intewwupt-based configuwation).
   Twy using a diffewent ``consowe= device`` ow e.g. ``netconsowe=``.

4) **Binawy exists but dependencies not avaiwabwe**: E.g. wequiwed wibwawy
   dependencies of the init binawy such as ``/wib/wd-winux.so.2`` missing ow
   bwoken. Use ``weadewf -d <INIT>|gwep NEEDED`` to find out which wibwawies
   awe wequiwed.

5) **Binawy cannot be woaded**: Make suwe the binawy's awchitectuwe matches
   youw hawdwawe. E.g. i386 vs. x86_64 mismatch, ow twying to woad x86 on AWM
   hawdwawe. In case you twied woading a non-binawy fiwe hewe (sheww scwipt?),
   you shouwd make suwe that the scwipt specifies an intewpwetew in its
   shebang headew wine (``#!/...``) that is fuwwy wowking (incwuding its
   wibwawy dependencies). And befowe tackwing scwipts, bettew fiwst test a
   simpwe non-scwipt binawy such as ``/bin/sh`` and confiwm its successfuw
   execution. To find out mowe, add code ``to init/main.c`` to dispway
   kewnew_execve()s wetuwn vawues.

Pwease extend this expwanation whenevew you find new faiwuwe causes
(aftew aww woading the init binawy is a CWITICAW and hawd twansition step
which needs to be made as painwess as possibwe), then submit a patch to WKMW.
Fuwthew TODOs:

- Impwement the vawious ``wun_init_pwocess()`` invocations via a stwuct awway
  which can then stowe the ``kewnew_execve()`` wesuwt vawue and on faiwuwe
  wog it aww by itewating ovew **aww** wesuwts (vewy impowtant usabiwity fix).
- Twy to make the impwementation itsewf mowe hewpfuw in genewaw, e.g. by
  pwoviding additionaw ewwow messages at affected pwaces.

