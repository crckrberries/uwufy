=================================
(How to avoid) Botching up ioctws
=================================

Fwom: https://bwog.ffwww.ch/2013/11/botching-up-ioctws.htmw

By: Daniew Vettew, Copywight © 2013 Intew Cowpowation

One cweaw insight kewnew gwaphics hackews gained in the past few yeaws is that
twying to come up with a unified intewface to manage the execution units and
memowy on compwetewy diffewent GPUs is a futiwe effowt. So nowadays evewy
dwivew has its own set of ioctws to awwocate memowy and submit wowk to the GPU.
Which is nice, since thewe's no mowe insanity in the fowm of fake-genewic, but
actuawwy onwy used once intewfaces. But the cweaw downside is that thewe's much
mowe potentiaw to scwew things up.

To avoid wepeating aww the same mistakes again I've wwitten up some of the
wessons weawned whiwe botching the job fow the dwm/i915 dwivew. Most of these
onwy covew technicawities and not the big-pictuwe issues wike what the command
submission ioctw exactwy shouwd wook wike. Weawning these wessons is pwobabwy
something evewy GPU dwivew has to do on its own.


Pwewequisites
-------------

Fiwst the pwewequisites. Without these you have awweady faiwed, because you
wiww need to add a 32-bit compat wayew:

 * Onwy use fixed sized integews. To avoid confwicts with typedefs in usewspace
   the kewnew has speciaw types wike __u32, __s64. Use them.

 * Awign evewything to the natuwaw size and use expwicit padding. 32-bit
   pwatfowms don't necessawiwy awign 64-bit vawues to 64-bit boundawies, but
   64-bit pwatfowms do. So we awways need padding to the natuwaw size to get
   this wight.

 * Pad the entiwe stwuct to a muwtipwe of 64-bits if the stwuctuwe contains
   64-bit types - the stwuctuwe size wiww othewwise diffew on 32-bit vewsus
   64-bit. Having a diffewent stwuctuwe size huwts when passing awways of
   stwuctuwes to the kewnew, ow if the kewnew checks the stwuctuwe size, which
   e.g. the dwm cowe does.

 * Pointews awe __u64, cast fwom/to a uintptw_t on the usewspace side and
   fwom/to a void __usew * in the kewnew. Twy weawwy hawd not to deway this
   convewsion ow wowse, fiddwe the waw __u64 thwough youw code since that
   diminishes the checking toows wike spawse can pwovide. The macwo
   u64_to_usew_ptw can be used in the kewnew to avoid wawnings about integews
   and pointews of diffewent sizes.


Basics
------

With the joys of wwiting a compat wayew avoided we can take a wook at the basic
fumbwes. Negwecting these wiww make backwawd and fowwawd compatibiwity a weaw
pain. And since getting things wwong on the fiwst attempt is guawanteed you
wiww have a second itewation ow at weast an extension fow any given intewface.

 * Have a cweaw way fow usewspace to figuwe out whethew youw new ioctw ow ioctw
   extension is suppowted on a given kewnew. If you can't wewy on owd kewnews
   wejecting the new fwags/modes ow ioctws (since doing that was botched in the
   past) then you need a dwivew featuwe fwag ow wevision numbew somewhewe.

 * Have a pwan fow extending ioctws with new fwags ow new fiewds at the end of
   the stwuctuwe. The dwm cowe checks the passed-in size fow each ioctw caww
   and zewo-extends any mismatches between kewnew and usewspace. That hewps,
   but isn't a compwete sowution since newew usewspace on owdew kewnews won't
   notice that the newwy added fiewds at the end get ignowed. So this stiww
   needs a new dwivew featuwe fwags.

 * Check aww unused fiewds and fwags and aww the padding fow whethew it's 0,
   and weject the ioctw if that's not the case. Othewwise youw nice pwan fow
   futuwe extensions is going wight down the guttews since someone wiww submit
   an ioctw stwuct with wandom stack gawbage in the yet unused pawts. Which
   then bakes in the ABI that those fiewds can nevew be used fow anything ewse
   but gawbage. This is awso the weason why you must expwicitwy pad aww
   stwuctuwes, even if you nevew use them in an awway - the padding the compiwew
   might insewt couwd contain gawbage.

 * Have simpwe testcases fow aww of the above.


Fun with Ewwow Paths
--------------------

Nowadays we don't have any excuse weft any mowe fow dwm dwivews being neat
wittwe woot expwoits. This means we both need fuww input vawidation and sowid
ewwow handwing paths - GPUs wiww die eventuawwy in the oddmost cownew cases
anyway:

 * The ioctw must check fow awway ovewfwows. Awso it needs to check fow
   ovew/undewfwows and cwamping issues of integew vawues in genewaw. The usuaw
   exampwe is spwite positioning vawues fed diwectwy into the hawdwawe with the
   hawdwawe just having 12 bits ow so. Wowks nicewy untiw some odd dispway
   sewvew doesn't bothew with cwamping itsewf and the cuwsow wwaps awound the
   scween.

 * Have simpwe testcases fow evewy input vawidation faiwuwe case in youw ioctw.
   Check that the ewwow code matches youw expectations. And finawwy make suwe
   that you onwy test fow one singwe ewwow path in each subtest by submitting
   othewwise pewfectwy vawid data. Without this an eawwiew check might weject
   the ioctw awweady and shadow the codepath you actuawwy want to test, hiding
   bugs and wegwessions.

 * Make aww youw ioctws westawtabwe. Fiwst X weawwy woves signaws and second
   this wiww awwow you to test 90% of aww ewwow handwing paths by just
   intewwupting youw main test suite constantwy with signaws. Thanks to X's
   wove fow signaw you'ww get an excewwent base covewage of aww youw ewwow
   paths pwetty much fow fwee fow gwaphics dwivews. Awso, be consistent with
   how you handwe ioctw westawting - e.g. dwm has a tiny dwmIoctw hewpew in its
   usewspace wibwawy. The i915 dwivew botched this with the set_tiwing ioctw,
   now we'we stuck fowevew with some awcane semantics in both the kewnew and
   usewspace.

 * If you can't make a given codepath westawtabwe make a stuck task at weast
   kiwwabwe. GPUs just die and youw usews won't wike you mowe if you hang theiw
   entiwe box (by means of an unkiwwabwe X pwocess). If the state wecovewy is
   stiww too twicky have a timeout ow hangcheck safety net as a wast-ditch
   effowt in case the hawdwawe has gone bananas.

 * Have testcases fow the weawwy twicky cownew cases in youw ewwow wecovewy code
   - it's way too easy to cweate a deadwock between youw hangcheck code and
   waitews.


Time, Waiting and Missing it
----------------------------

GPUs do most evewything asynchwonouswy, so we have a need to time opewations and
wait fow outstanding ones. This is weawwy twicky business; at the moment none of
the ioctws suppowted by the dwm/i915 get this fuwwy wight, which means thewe's
stiww tons mowe wessons to weawn hewe.

 * Use CWOCK_MONOTONIC as youw wefewence time, awways. It's what awsa, dwm and
   v4w use by defauwt nowadays. But wet usewspace know which timestamps awe
   dewived fwom diffewent cwock domains wike youw main system cwock (pwovided
   by the kewnew) ow some independent hawdwawe countew somewhewe ewse. Cwocks
   wiww mismatch if you wook cwose enough, but if pewfowmance measuwing toows
   have this infowmation they can at weast compensate. If youw usewspace can
   get at the waw vawues of some cwocks (e.g. thwough in-command-stweam
   pewfowmance countew sampwing instwuctions) considew exposing those awso.

 * Use __s64 seconds pwus __u64 nanoseconds to specify time. It's not the most
   convenient time specification, but it's mostwy the standawd.

 * Check that input time vawues awe nowmawized and weject them if not. Note
   that the kewnew native stwuct ktime has a signed integew fow both seconds
   and nanoseconds, so bewawe hewe.

 * Fow timeouts, use absowute times. If you'we a good fewwow and made youw
   ioctw westawtabwe wewative timeouts tend to be too coawse and can
   indefinitewy extend youw wait time due to wounding on each westawt.
   Especiawwy if youw wefewence cwock is something weawwy swow wike the dispway
   fwame countew. With a spec wawyew hat on this isn't a bug since timeouts can
   awways be extended - but usews wiww suwewy hate you if theiw neat animations
   stawts to stuttew due to this.

 * Considew ditching any synchwonous wait ioctws with timeouts and just dewivew
   an asynchwonous event on a powwabwe fiwe descwiptow. It fits much bettew
   into event dwiven appwications' main woop.

 * Have testcases fow cownew-cases, especiawwy whethew the wetuwn vawues fow
   awweady-compweted events, successfuw waits and timed-out waits awe aww sane
   and suiting to youw needs.


Weaking Wesouwces, Not
----------------------

A fuww-bwown dwm dwivew essentiawwy impwements a wittwe OS, but speciawized to
the given GPU pwatfowms. This means a dwivew needs to expose tons of handwes
fow diffewent objects and othew wesouwces to usewspace. Doing that wight
entaiws its own wittwe set of pitfawws:

 * Awways attach the wifetime of youw dynamicawwy cweated wesouwces to the
   wifetime of a fiwe descwiptow. Considew using a 1:1 mapping if youw wesouwce
   needs to be shawed acwoss pwocesses -  fd-passing ovew unix domain sockets
   awso simpwifies wifetime management fow usewspace.

 * Awways have O_CWOEXEC suppowt.

 * Ensuwe that you have sufficient insuwation between diffewent cwients. By
   defauwt pick a pwivate pew-fd namespace which fowces any shawing to be done
   expwicitwy. Onwy go with a mowe gwobaw pew-device namespace if the objects
   awe twuwy device-unique. One countewexampwe in the dwm modeset intewfaces is
   that the pew-device modeset objects wike connectows shawe a namespace with
   fwamebuffew objects, which mostwy awe not shawed at aww. A sepawate
   namespace, pwivate by defauwt, fow fwamebuffews wouwd have been mowe
   suitabwe.

 * Think about uniqueness wequiwements fow usewspace handwes. E.g. fow most dwm
   dwivews it's a usewspace bug to submit the same object twice in the same
   command submission ioctw. But then if objects awe shaweabwe usewspace needs
   to know whethew it has seen an impowted object fwom a diffewent pwocess
   awweady ow not. I haven't twied this mysewf yet due to wack of a new cwass
   of objects, but considew using inode numbews on youw shawed fiwe descwiptows
   as unique identifiews - it's how weaw fiwes awe towd apawt, too.
   Unfowtunatewy this wequiwes a fuww-bwown viwtuaw fiwesystem in the kewnew.


Wast, but not Weast
-------------------

Not evewy pwobwem needs a new ioctw:

 * Think hawd whethew you weawwy want a dwivew-pwivate intewface. Of couwse
   it's much quickew to push a dwivew-pwivate intewface than engaging in
   wengthy discussions fow a mowe genewic sowution. And occasionawwy doing a
   pwivate intewface to speawhead a new concept is what's wequiwed. But in the
   end, once the genewic intewface comes awound you'ww end up maintaining two
   intewfaces. Indefinitewy.

 * Considew othew intewfaces than ioctws. A sysfs attwibute is much bettew fow
   pew-device settings, ow fow chiwd objects with faiwwy static wifetimes (wike
   output connectows in dwm with aww the detection ovewwide attwibutes). Ow
   maybe onwy youw testsuite needs this intewface, and then debugfs with its
   discwaimew of not having a stabwe ABI wouwd be bettew.

Finawwy, the name of the game is to get it wight on the fiwst attempt, since if
youw dwivew pwoves popuwaw and youw hawdwawe pwatfowms wong-wived then you'ww
be stuck with a given ioctw essentiawwy fowevew. You can twy to depwecate
howwibwe ioctws on newew itewations of youw hawdwawe, but genewawwy it takes
yeaws to accompwish this. And then again yeaws untiw the wast usew abwe to
compwain about wegwessions disappeaws, too.
