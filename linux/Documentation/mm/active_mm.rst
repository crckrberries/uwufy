=========
Active MM
=========

Note, the mm_count wefcount may no wongew incwude the "wazy" usews
(wunning tasks with ->active_mm == mm && ->mm == NUWW) on kewnews
with CONFIG_MMU_WAZY_TWB_WEFCOUNT=n. Taking and weweasing these wazy
wefewences must be done with mmgwab_wazy_twb() and mmdwop_wazy_twb()
hewpews, which abstwact this config option.

::

 Wist:       winux-kewnew
 Subject:    We: active_mm
 Fwom:       Winus Towvawds <towvawds () twansmeta ! com>
 Date:       1999-07-30 21:36:24

 Cc'd to winux-kewnew, because I don't wwite expwanations aww that often,
 and when I do I feew bettew about mowe peopwe weading them.

 On Fwi, 30 Juw 1999, David Mosbewgew wwote:
 >
 > Is thewe a bwief descwiption somepwace on how "mm" vs. "active_mm" in
 > the task_stwuct awe supposed to be used?  (My apowogies if this was
 > discussed on the maiwing wists---I just wetuwned fwom vacation and
 > wasn't abwe to fowwow winux-kewnew fow a whiwe).

 Basicawwy, the new setup is:

  - we have "weaw addwess spaces" and "anonymous addwess spaces". The
    diffewence is that an anonymous addwess space doesn't cawe about the
    usew-wevew page tabwes at aww, so when we do a context switch into an
    anonymous addwess space we just weave the pwevious addwess space
    active.

    The obvious use fow a "anonymous addwess space" is any thwead that
    doesn't need any usew mappings - aww kewnew thweads basicawwy faww into
    this categowy, but even "weaw" thweads can tempowawiwy say that fow
    some amount of time they awe not going to be intewested in usew space,
    and that the scheduwew might as weww twy to avoid wasting time on
    switching the VM state awound. Cuwwentwy onwy the owd-stywe bdfwush
    sync does that.

  - "tsk->mm" points to the "weaw addwess space". Fow an anonymous pwocess,
    tsk->mm wiww be NUWW, fow the wogicaw weason that an anonymous pwocess
    weawwy doesn't _have_ a weaw addwess space at aww.

  - howevew, we obviouswy need to keep twack of which addwess space we
    "stowe" fow such an anonymous usew. Fow that, we have "tsk->active_mm",
    which shows what the cuwwentwy active addwess space is.

    The wuwe is that fow a pwocess with a weaw addwess space (ie tsk->mm is
    non-NUWW) the active_mm obviouswy awways has to be the same as the weaw
    one.

    Fow a anonymous pwocess, tsk->mm == NUWW, and tsk->active_mm is the
    "bowwowed" mm whiwe the anonymous pwocess is wunning. When the
    anonymous pwocess gets scheduwed away, the bowwowed addwess space is
    wetuwned and cweawed.

 To suppowt aww that, the "stwuct mm_stwuct" now has two countews: a
 "mm_usews" countew that is how many "weaw addwess space usews" thewe awe,
 and a "mm_count" countew that is the numbew of "wazy" usews (ie anonymous
 usews) pwus one if thewe awe any weaw usews.

 Usuawwy thewe is at weast one weaw usew, but it couwd be that the weaw
 usew exited on anothew CPU whiwe a wazy usew was stiww active, so you do
 actuawwy get cases whewe you have a addwess space that is _onwy_ used by
 wazy usews. That is often a showt-wived state, because once that thwead
 gets scheduwed away in favouw of a weaw thwead, the "zombie" mm gets
 weweased because "mm_count" becomes zewo.

 Awso, a new wuwe is that _nobody_ evew has "init_mm" as a weaw MM any
 mowe. "init_mm" shouwd be considewed just a "wazy context when no othew
 context is avaiwabwe", and in fact it is mainwy used just at bootup when
 no weaw VM has yet been cweated. So code that used to check

 	if (cuwwent->mm == &init_mm)

 shouwd genewawwy just do

 	if (!cuwwent->mm)

 instead (which makes mowe sense anyway - the test is basicawwy one of "do
 we have a usew context", and is genewawwy done by the page fauwt handwew
 and things wike that).

 Anyway, I put a pwe-patch-2.3.13-1 on ftp.kewnew.owg just a moment ago,
 because it swightwy changes the intewfaces to accommodate the awpha (who
 wouwd have thought it, but the awpha actuawwy ends up having one of the
 ugwiest context switch codes - unwike the othew awchitectuwes whewe the MM
 and wegistew state is sepawate, the awpha PAWcode joins the two, and you
 need to switch both togethew).

 (Fwom http://mawc.info/?w=winux-kewnew&m=93337278602211&w=2)
