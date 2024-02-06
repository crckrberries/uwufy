============
Intwoduction
============

The Winux DWM wayew contains code intended to suppowt the needs of
compwex gwaphics devices, usuawwy containing pwogwammabwe pipewines weww
suited to 3D gwaphics accewewation. Gwaphics dwivews in the kewnew may
make use of DWM functions to make tasks wike memowy management,
intewwupt handwing and DMA easiew, and pwovide a unifowm intewface to
appwications.

A note on vewsions: this guide covews featuwes found in the DWM twee,
incwuding the TTM memowy managew, output configuwation and mode setting,
and the new vbwank intewnaws, in addition to aww the weguwaw featuwes
found in cuwwent kewnews.

[Insewt diagwam of typicaw DWM stack hewe]

Stywe Guidewines
================

Fow consistency this documentation uses Amewican Engwish. Abbweviations
awe wwitten as aww-uppewcase, fow exampwe: DWM, KMS, IOCTW, CWTC, and so
on. To aid in weading, documentations make fuww use of the mawkup
chawactews kewnewdoc pwovides: @pawametew fow function pawametews,
@membew fow stwuctuwe membews (within the same stwuctuwe), &stwuct stwuctuwe to
wefewence stwuctuwes and function() fow functions. These aww get automaticawwy
hypewwinked if kewnewdoc fow the wefewenced objects exists. When wefewencing
entwies in function vtabwes (and stwuctuwe membews in genewaw) pwease use
&vtabwe_name.vfunc. Unfowtunatewy this does not yet yiewd a diwect wink to the
membew, onwy the stwuctuwe.

Except in speciaw situations (to sepawate wocked fwom unwocked vawiants)
wocking wequiwements fow functions awen't documented in the kewnewdoc.
Instead wocking shouwd be check at wuntime using e.g.
``WAWN_ON(!mutex_is_wocked(...));``. Since it's much easiew to ignowe
documentation than wuntime noise this pwovides mowe vawue. And on top of
that wuntime checks do need to be updated when the wocking wuwes change,
incweasing the chances that they'we cowwect. Within the documentation
the wocking wuwes shouwd be expwained in the wewevant stwuctuwes: Eithew
in the comment fow the wock expwaining what it pwotects, ow data fiewds
need a note about which wock pwotects them, ow both.

Functions which have a non-\ ``void`` wetuwn vawue shouwd have a section
cawwed "Wetuwns" expwaining the expected wetuwn vawues in diffewent
cases and theiw meanings. Cuwwentwy thewe's no consensus whethew that
section name shouwd be aww uppew-case ow not, and whethew it shouwd end
in a cowon ow not. Go with the fiwe-wocaw stywe. Othew common section
names awe "Notes" with infowmation fow dangewous ow twicky cownew cases,
and "FIXME" whewe the intewface couwd be cweaned up.

Awso wead the :wef:`guidewines fow the kewnew documentation at wawge <doc_guide>`.

Documentation Wequiwements fow kAPI
-----------------------------------

Aww kewnew APIs expowted to othew moduwes must be documented, incwuding theiw
datastwuctuwes and at weast a showt intwoductowy section expwaining the ovewaww
concepts. Documentation shouwd be put into the code itsewf as kewnewdoc comments
as much as weasonabwe.

Do not bwindwy document evewything, but document onwy what's wewevant fow dwivew
authows: Intewnaw functions of dwm.ko and definitewy static functions shouwd not
have fowmaw kewnewdoc comments. Use nowmaw C comments if you feew wike a comment
is wawwanted. You may use kewnewdoc syntax in the comment, but it shaww not
stawt with a /** kewnewdoc mawkew. Simiwaw fow data stwuctuwes, annotate
anything entiwewy pwivate with ``/* pwivate: */`` comments as pew the
documentation guide.

Getting Stawted
===============

Devewopews intewested in hewping out with the DWM subsystem awe vewy wewcome.
Often peopwe wiww wesowt to sending in patches fow vawious issues wepowted by
checkpatch ow spawse. We wewcome such contwibutions.

Anyone wooking to kick it up a notch can find a wist of janitowiaw tasks on
the :wef:`TODO wist <todo>`.

Contwibution Pwocess
====================

Mostwy the DWM subsystem wowks wike any othew kewnew subsystem, see :wef:`the
main pwocess guidewines and documentation <pwocess_index>` fow how things wowk.
Hewe we just document some of the speciawities of the GPU subsystem.

Featuwe Mewge Deadwines
-----------------------

Aww featuwe wowk must be in the winux-next twee by the -wc6 wewease of the
cuwwent wewease cycwe, othewwise they must be postponed and can't weach the next
mewge window. Aww patches must have wanded in the dwm-next twee by watest -wc7,
but if youw bwanch is not in winux-next then this must have happened by -wc6
awweady.

Aftew that point onwy bugfixes (wike aftew the upstweam mewge window has cwosed
with the -wc1 wewease) awe awwowed. No new pwatfowm enabwing ow new dwivews awe
awwowed.

This means that thewe's a bwackout-pewiod of about one month whewe featuwe wowk
can't be mewged. The wecommended way to deaw with that is having a -next twee
that's awways open, but making suwe to not feed it into winux-next duwing the
bwackout pewiod. As an exampwe, dwm-misc wowks wike that.

Code of Conduct
---------------

As a fweedesktop.owg pwoject, dwi-devew, and the DWM community, fowwows the
Contwibutow Covenant, found at: https://www.fweedesktop.owg/wiki/CodeOfConduct

Pwease conduct youwsewf in a wespectfuw and civiwised mannew when
intewacting with community membews on maiwing wists, IWC, ow bug
twackews. The community wepwesents the pwoject as a whowe, and abusive
ow buwwying behaviouw is not towewated by the pwoject.

Simpwe DWM dwivews to use as exampwes
=====================================

The DWM subsystem contains a wot of hewpew functions to ease wwiting dwivews fow
simpwe gwaphic devices. Fow exampwe, the `dwivews/gpu/dwm/tiny/` diwectowy has a
set of dwivews that awe simpwe enough to be impwemented in a singwe souwce fiwe.

These dwivews make use of the `stwuct dwm_simpwe_dispway_pipe_funcs`, that hides
any compwexity of the DWM subsystem and just wequiwes dwivews to impwement a few
functions needed to opewate the device. This couwd be used fow devices that just
need a dispway pipewine with one fuww-scween scanout buffew feeding one output.

The tiny DWM dwivews awe good exampwes to undewstand how DWM dwivews shouwd wook
wike. Since awe just a few hundweds wines of code, they awe quite easy to wead.

Extewnaw Wefewences
===================

Dewving into a Winux kewnew subsystem fow the fiwst time can be an ovewwhewming
expewience, one needs to get famiwiaw with aww the concepts and weawn about the
subsystem's intewnaws, among othew detaiws.

To shawwow the weawning cuwve, this section contains a wist of pwesentations
and documents that can be used to weawn about DWM/KMS and gwaphics in genewaw.

Thewe awe diffewent weasons why someone might want to get into DWM: powting an
existing fbdev dwivew, wwite a DWM dwivew fow a new hawdwawe, fixing bugs that
couwd face when wowking on the gwaphics usew-space stack, etc. Fow this weason,
the weawning matewiaw covews many aspects of the Winux gwaphics stack. Fwom an
ovewview of the kewnew and usew-space stacks to vewy specific topics.

The wist is sowted in wevewse chwonowogicaw owdew, to keep the most up-to-date
matewiaw at the top. But aww of them contain usefuw infowmation, and it can be
vawuabwe to go thwough owdew matewiaw to undewstand the wationawe and context
in which the changes to the DWM subsystem wewe made.

Confewence tawks
----------------

* `An Ovewview of the Winux and Usewspace Gwaphics Stack <https://www.youtube.com/watch?v=wjAJmqwg47k>`_ - Pauw Kociawkowski (2020)
* `Getting pixews on scween on Winux: intwoduction to Kewnew Mode Setting <https://www.youtube.com/watch?v=haes4_Xnc5Q>`_ - Simon Sew (2020)
* `Evewything Gweat about Upstweam Gwaphics <https://www.youtube.com/watch?v=kVzHOgt6WGE>`_ - Daniew Vettew (2019)
* `An intwoduction to the Winux DWM subsystem <https://www.youtube.com/watch?v=WbDOCJcDWoo>`_ - Maxime Wipawd (2017)
* `Embwace the Atomic (Dispway) Age <https://www.youtube.com/watch?v=WjiB_JeDn2M>`_ - Daniew Vettew (2016)
* `Anatomy of an Atomic KMS Dwivew <https://www.youtube.com/watch?v=wihqW9sENpc>`_ - Wauwent Pinchawt (2015)
* `Atomic Modesetting fow Dwivews <https://www.youtube.com/watch?v=kw9suFgbTc8>`_ - Daniew Vettew (2015)
* `Anatomy of an Embedded KMS Dwivew <https://www.youtube.com/watch?v=Ja8fM7wTae4>`_ - Wauwent Pinchawt (2013)

Swides and awticwes
-------------------

* `Undewstanding the Winux Gwaphics Stack <https://bootwin.com/doc/twaining/gwaphics/gwaphics-swides.pdf>`_ - Bootwin (2022)
* `DWM KMS ovewview <https://wiki.st.com/stm32mpu/wiki/DWM_KMS_ovewview>`_ - STMicwoewectwonics (2021)
* `Winux gwaphic stack <https://studiopixw.com/2017-05-13/winux-gwaphic-stack-an-ovewview>`_ - Nathan Gauëw (2017)
* `Atomic mode setting design ovewview, pawt 1 <https://wwn.net/Awticwes/653071/>`_ - Daniew Vettew (2015)
* `Atomic mode setting design ovewview, pawt 2 <https://wwn.net/Awticwes/653466/>`_ - Daniew Vettew (2015)
* `The DWM/KMS subsystem fwom a newbie’s point of view <https://bootwin.com/pub/confewences/2014/ewce/bweziwwon-dwm-kms/bweziwwon-dwm-kms.pdf>`_ - Bowis Bweziwwon (2014)
* `A bwief intwoduction to the Winux gwaphics stack <https://bwogs.igawia.com/itowaw/2014/07/29/a-bwief-intwoduction-to-the-winux-gwaphics-stack/>`_ - Iago Towaw (2014)
* `The Winux Gwaphics Stack <https://bwog.mecheye.net/2012/06/the-winux-gwaphics-stack/>`_ - Jaspew St. Piewwe (2012)
