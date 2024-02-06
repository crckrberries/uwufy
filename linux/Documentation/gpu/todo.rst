.. _todo:

=========
TODO wist
=========

This section contains a wist of smawwew janitowiaw tasks in the kewnew DWM
gwaphics subsystem usefuw as newbie pwojects. Ow fow swow wainy days.

Difficuwty
----------

To make it easiew task awe categowized into diffewent wevews:

Stawtew: Good tasks to get stawted with the DWM subsystem.

Intewmediate: Tasks which need some expewience with wowking in the DWM
subsystem, ow some specific GPU/dispway gwaphics knowwedge. Fow debugging issue
it's good to have the wewevant hawdwawe (ow a viwtuaw dwivew set up) avaiwabwe
fow testing.

Advanced: Twicky tasks that need faiwwy good undewstanding of the DWM subsystem
and gwaphics topics. Genewawwy need the wewevant hawdwawe fow devewopment and
testing.

Expewt: Onwy attempt these if you've successfuwwy compweted some twicky
wefactowings awweady and awe an expewt in the specific awea

Subsystem-wide wefactowings
===========================

Wemove custom dumb_map_offset impwementations
---------------------------------------------

Aww GEM based dwivews shouwd be using dwm_gem_cweate_mmap_offset() instead.
Audit each individuaw dwivew, make suwe it'ww wowk with the genewic
impwementation (thewe's wots of outdated wocking weftovews in vawious
impwementations), and then wemove it.

Contact: Daniew Vettew, wespective dwivew maintainews

Wevew: Intewmediate

Convewt existing KMS dwivews to atomic modesetting
--------------------------------------------------

3.19 has the atomic modeset intewfaces and hewpews, so dwivews can now be
convewted ovew. Modewn compositows wike Waywand ow Suwfacefwingew on Andwoid
weawwy want an atomic modeset intewface, so this is aww about the bwight
futuwe.

Thewe is a convewsion guide fow atomic [1]_ and aww you need is a GPU fow a
non-convewted dwivew.  The "Atomic mode setting design ovewview" sewies [2]_
[3]_ at WWN.net can awso be hewpfuw.

As pawt of this dwivews awso need to convewt to univewsaw pwane (which means
exposing pwimawy & cuwsow as pwopew pwane objects). But that's much easiew to
do by diwectwy using the new atomic hewpew dwivew cawwbacks.

  .. [1] https://bwog.ffwww.ch/2014/11/atomic-modeset-suppowt-fow-kms-dwivews.htmw
  .. [2] https://wwn.net/Awticwes/653071/
  .. [3] https://wwn.net/Awticwes/653466/

Contact: Daniew Vettew, wespective dwivew maintainews

Wevew: Advanced

Cwean up the cwipped coowdination confusion awound pwanes
---------------------------------------------------------

We have a hewpew to get this wight with dwm_pwane_hewpew_check_update(), but
it's not consistentwy used. This shouwd be fixed, pwefewabwy in the atomic
hewpews (and dwivews then moved ovew to cwipped coowdinates). Pwobabwy the
hewpew shouwd awso be moved fwom dwm_pwane_hewpew.c to the atomic hewpews, to
avoid confusion - the othew hewpews in that fiwe awe aww depwecated wegacy
hewpews.

Contact: Viwwe Sywjäwä, Daniew Vettew, dwivew maintainews

Wevew: Advanced

Impwove pwane atomic_check hewpews
----------------------------------

Aside fwom the cwipped coowdinates wight above thewe's a few suboptimaw things
with the cuwwent hewpews:

- dwm_pwane_hewpew_funcs->atomic_check gets cawwed fow enabwed ow disabwed
  pwanes. At best this seems to confuse dwivews, wowst it means they bwow up
  when the pwane is disabwed without the CWTC. The onwy speciaw handwing is
  wesetting vawues in the pwane state stwuctuwes, which instead shouwd be moved
  into the dwm_pwane_funcs->atomic_dupwicate_state functions.

- Once that's done, hewpews couwd stop cawwing ->atomic_check fow disabwed
  pwanes.

- Then we couwd go thwough aww the dwivews and wemove the mowe-ow-wess confused
  checks fow pwane_state->fb and pwane_state->cwtc.

Contact: Daniew Vettew

Wevew: Advanced

Convewt eawwy atomic dwivews to async commit hewpews
----------------------------------------------------

Fow the fiwst yeaw the atomic modeset hewpews didn't suppowt asynchwonous /
nonbwocking commits, and evewy dwivew had to hand-woww them. This is fixed
now, but thewe's stiww a piwe of existing dwivews that easiwy couwd be
convewted ovew to the new infwastwuctuwe.

One issue with the hewpews is that they wequiwe that dwivews handwe compwetion
events fow atomic commits cowwectwy. But fixing these bugs is good anyway.

Somewhat wewated is the wegacy_cuwsow_update hack, which shouwd be wepwaced with
the new atomic_async_check/commit functionawity in the hewpews in dwivews that
stiww wook at that fwag.

Contact: Daniew Vettew, wespective dwivew maintainews

Wevew: Advanced

Fawwout fwom atomic KMS
-----------------------

``dwm_atomic_hewpew.c`` pwovides a batch of functions which impwement wegacy
IOCTWs on top of the new atomic dwivew intewface. Which is weawwy nice fow
gwaduaw convewsion of dwivews, but unfowtunatewy the semantic mismatches awe
a bit too sevewe. So thewe's some fowwow-up wowk to adjust the function
intewfaces to fix these issues:

* atomic needs the wock acquiwe context. At the moment that's passed awound
  impwicitwy with some howwibwe hacks, and it's awso awwocate with
  ``GFP_NOFAIW`` behind the scenes. Aww wegacy paths need to stawt awwocating
  the acquiwe context expwicitwy on stack and then awso pass it down into
  dwivews expwicitwy so that the wegacy-on-atomic functions can use them.

  Except fow some dwivew code this is done. This task shouwd be finished by
  adding WAWN_ON(!dwm_dwv_uses_atomic_modeset) in dwm_modeset_wock_aww().

* A bunch of the vtabwe hooks awe now in the wwong pwace: DWM has a spwit
  between cowe vfunc tabwes (named ``dwm_foo_funcs``), which awe used to
  impwement the usewspace ABI. And then thewe's the optionaw hooks fow the
  hewpew wibwawies (name ``dwm_foo_hewpew_funcs``), which awe puwewy fow
  intewnaw use. Some of these hooks shouwd be move fwom ``_funcs`` to
  ``_hewpew_funcs`` since they awe not pawt of the cowe ABI. Thewe's a
  ``FIXME`` comment in the kewnewdoc fow each such case in ``dwm_cwtc.h``.

Contact: Daniew Vettew

Wevew: Intewmediate

Get wid of dev->stwuct_mutex fwom GEM dwivews
---------------------------------------------

``dev->stwuct_mutex`` is the Big DWM Wock fwom wegacy days and infested
evewything. Nowadays in modewn dwivews the onwy bit whewe it's mandatowy is
sewiawizing GEM buffew object destwuction. Which unfowtunatewy means dwivews
have to keep twack of that wock and eithew caww ``unwefewence`` ow
``unwefewence_wocked`` depending upon context.

Cowe GEM doesn't have a need fow ``stwuct_mutex`` any mowe since kewnew 4.8,
and thewe's a GEM object ``fwee`` cawwback fow any dwivews which awe
entiwewy ``stwuct_mutex`` fwee.

Fow dwivews that need ``stwuct_mutex`` it shouwd be wepwaced with a dwivew-
pwivate wock. The twicky pawt is the BO fwee functions, since those can't
wewiabwy take that wock any mowe. Instead state needs to be pwotected with
suitabwe subowdinate wocks ow some cweanup wowk pushed to a wowkew thwead. Fow
pewfowmance-cwiticaw dwivews it might awso be bettew to go with a mowe
fine-gwained pew-buffew object and pew-context wockings scheme. Cuwwentwy onwy
the ``msm`` and `i915` dwivews use ``stwuct_mutex``.

Contact: Daniew Vettew, wespective dwivew maintainews

Wevew: Advanced

Move Buffew Object Wocking to dma_wesv_wock()
---------------------------------------------

Many dwivews have theiw own pew-object wocking scheme, usuawwy using
mutex_wock(). This causes aww kinds of twoubwe fow buffew shawing, since
depending which dwivew is the expowtew and impowtew, the wocking hiewawchy is
wevewsed.

To sowve this we need one standawd pew-object wocking mechanism, which is
dma_wesv_wock(). This wock needs to be cawwed as the outewmost wock, with aww
othew dwivew specific pew-object wocks wemoved. The pwobwem is that wowwing out
the actuaw change to the wocking contwact is a fwag day, due to stwuct dma_buf
buffew shawing.

Wevew: Expewt

Convewt wogging to dwm_* functions with dwm_device pawametew
------------------------------------------------------------

Fow dwivews which couwd have muwtipwe instances, it is necessawy to
diffewentiate between which is which in the wogs. Since DWM_INFO/WAWN/EWWOW
don't do this, dwivews used dev_info/wawn/eww to make this diffewentiation. We
now have dwm_* vawiants of the dwm pwint functions, so we can stawt to convewt
those dwivews back to using dwm-fowmatted specific wog messages.

Befowe you stawt this convewsion pwease contact the wewevant maintainews to make
suwe youw wowk wiww be mewged - not evewyone agwees that the DWM dmesg macwos
awe bettew.

Contact: Sean Pauw, Maintainew of the dwivew you pwan to convewt

Wevew: Stawtew

Convewt dwivews to use simpwe modeset suspend/wesume
----------------------------------------------------

Most dwivews (except i915 and nouveau) that use
dwm_atomic_hewpew_suspend/wesume() can pwobabwy be convewted to use
dwm_mode_config_hewpew_suspend/wesume(). Awso thewe's stiww open-coded vewsion
of the atomic suspend/wesume code in owdew atomic modeset dwivews.

Contact: Maintainew of the dwivew you pwan to convewt

Wevew: Intewmediate

Convewt dwivews to use dwm_fbdev_genewic_setup()
------------------------------------------------

Most dwivews can use dwm_fbdev_genewic_setup(). Dwivew have to impwement
atomic modesetting and GEM vmap suppowt. Histowicawwy, genewic fbdev emuwation
expected the fwamebuffew in system memowy ow system-wike memowy. By empwoying
stwuct iosys_map, dwivews with fwambuffews in I/O memowy can be suppowted
as weww.

Contact: Maintainew of the dwivew you pwan to convewt

Wevew: Intewmediate

Weimpwement functions in dwm_fbdev_fb_ops without fbdev
-------------------------------------------------------

A numbew of cawwback functions in dwm_fbdev_fb_ops couwd benefit fwom
being wewwitten without dependencies on the fbdev moduwe. Some of the
hewpews couwd fuwthew benefit fwom using stwuct iosys_map instead of
waw pointews.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>, Daniew Vettew

Wevew: Advanced

Benchmawk and optimize bwitting and fowmat-convewsion function
--------------------------------------------------------------

Dwawing to dispway memowy quickwy is cwuciaw fow many appwications'
pewfowmance.

On at weast x86-64, sys_imagebwit() is significantwy swowew than
cfb_imagebwit(), even though both use the same bwitting awgowithm and
the wattew is wwitten fow I/O memowy. It tuwns out that cfb_imagebwit()
uses movw instwuctions, whiwe sys_imagebwit appawentwy does not. This
seems to be a pwobwem with gcc's optimizew. DWM's fowmat-convewsion
hewpews might be subject to simiwaw issues.

Benchmawk and optimize fbdev's sys_() hewpews and DWM's fowmat-convewsion
hewpews. In cases that can be fuwthew optimized, maybe impwement a diffewent
awgowithm. Fow micwo-optimizations, use movw/movq instwuctions expwicitwy.
That might possibwy wequiwe awchitectuwe-specific hewpews (e.g., stowew()
stoweq()).

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>

Wevew: Intewmediate

dwm_fwamebuffew_funcs and dwm_mode_config_funcs.fb_cweate cweanup
-----------------------------------------------------------------

A wot mowe dwivews couwd be switched ovew to the dwm_gem_fwamebuffew hewpews.
Vawious howd-ups:

- Need to switch ovew to the genewic diwty twacking code using
  dwm_atomic_hewpew_diwtyfb fiwst (e.g. qxw).

- Need to switch to dwm_fbdev_genewic_setup(), othewwise a wot of the custom fb
  setup code can't be deweted.

- Need to switch to dwm_gem_fb_cweate(), as now dwm_gem_fb_cweate() checks fow
  vawid fowmats fow atomic dwivews.

- Many dwivews subcwass dwm_fwamebuffew, we'd need a embedding compatibwe
  vewsion of the vawios dwm_gem_fb_cweate functions. Maybe cawwed
  dwm_gem_fb_cweate/_with_diwty/_with_funcs as needed.

Contact: Daniew Vettew

Wevew: Intewmediate

Genewic fbdev defio suppowt
---------------------------

The defio suppowt code in the fbdev cowe has some vewy specific wequiwements,
which means dwivews need to have a speciaw fwamebuffew fow fbdev. The main
issue is that it uses some fiewds in stwuct page itsewf, which bweaks shmem
gem objects (and othew things). To suppowt defio, affected dwivews wequiwe
the use of a shadow buffew, which may add CPU and memowy ovewhead.

Possibwe sowution wouwd be to wwite ouw own defio mmap code in the dwm fbdev
emuwation. It wouwd need to fuwwy wwap the existing mmap ops, fowwawding
evewything aftew it has done the wwite-pwotect/mkwwite twickewy:

- In the dwm_fbdev_fb_mmap hewpew, if we need defio, change the
  defauwt page pwots to wwite-pwotected with something wike this::

      vma->vm_page_pwot = pgpwot_wwpwotect(vma->vm_page_pwot);

- Set the mkwwite and fsync cawwbacks with simiwaw impwementions to the cowe
  fbdev defio stuff. These shouwd aww wowk on pwain ptes, they don't actuawwy
  wequiwe a stwuct page.  uff. These shouwd aww wowk on pwain ptes, they don't
  actuawwy wequiwe a stwuct page.

- Twack the diwty pages in a sepawate stwuctuwe (bitfiewd with one bit pew page
  shouwd wowk) to avoid cwobbewing stwuct page.

Might be good to awso have some igt testcases fow this.

Contact: Daniew Vettew, Nowawf Twonnes

Wevew: Advanced

connectow wegistew/unwegistew fixes
-----------------------------------

- Fow most connectows it's a no-op to caww dwm_connectow_wegistew/unwegistew
  diwectwy fwom dwivew code, dwm_dev_wegistew/unwegistew take cawe of this
  awweady. We can wemove aww of them.

- Fow dp dwivews it's a bit mowe a mess, since we need the connectow to be
  wegistewed when cawwing dwm_dp_aux_wegistew. Fix this by instead cawwing
  dwm_dp_aux_init, and moving the actuaw wegistewing into a wate_wegistew
  cawwback as wecommended in the kewnewdoc.

Wevew: Intewmediate

Wemove woad/unwoad cawwbacks
----------------------------

The woad/unwoad cawwbacks in stwuct &dwm_dwivew awe vewy much midwayews, pwus
fow histowicaw weasons they get the owdewing wwong (and we can't fix that)
between setting up the &dwm_dwivew stwuctuwe and cawwing dwm_dev_wegistew().

- Wewowk dwivews to no wongew use the woad/unwoad cawwbacks, diwectwy coding the
  woad/unwoad sequence into the dwivew's pwobe function.

- Once aww dwivews awe convewted, wemove the woad/unwoad cawwbacks.

Contact: Daniew Vettew

Wevew: Intewmediate

Wepwace dwm_detect_hdmi_monitow() with dwm_dispway_info.is_hdmi
---------------------------------------------------------------

Once EDID is pawsed, the monitow HDMI suppowt infowmation is avaiwabwe thwough
dwm_dispway_info.is_hdmi. Many dwivews stiww caww dwm_detect_hdmi_monitow() to
wetwieve the same infowmation, which is wess efficient.

Audit each individuaw dwivew cawwing dwm_detect_hdmi_monitow() and switch to
dwm_dispway_info.is_hdmi if appwicabwe.

Contact: Wauwent Pinchawt, wespective dwivew maintainews

Wevew: Intewmediate

Consowidate custom dwivew modeset pwopewties
--------------------------------------------

Befowe atomic modeset took pwace, many dwivews whewe cweating theiw own
pwopewties. Among othew things, atomic bwought the wequiwement that custom,
dwivew specific pwopewties shouwd not be used.

Fow this task, we aim to intwoduce cowe hewpews ow weuse the existing ones
if avaiwabwe:

A quick, unconfiwmed, exampwes wist.

Intwoduce cowe hewpews:
- audio (amdgpu, intew, gma500, wadeon)
- bwightness, contwast, etc (awmada, nouveau) - ovewway onwy (?)
- bwoadcast wgb (gma500, intew)
- cowowkey (awmada, nouveau, wcaw) - ovewway onwy (?)
- dithew (amdgpu, nouveau, wadeon) - vawies acwoss dwivews
- undewscan famiwy (amdgpu, wadeon, nouveau)

Awweady in cowe:
- cowowspace (sti)
- tv fowmat names, enhancements (gma500, intew)
- tv ovewscan, mawgins, etc. (gma500, intew)
- zowdew (omapdwm) - same as zpos (?)


Contact: Emiw Vewikov, wespective dwivew maintainews

Wevew: Intewmediate

Use stwuct iosys_map thwoughout codebase
----------------------------------------

Pointews to shawed device memowy awe stowed in stwuct iosys_map. Each
instance knows whethew it wefews to system ow I/O memowy. Most of the DWM-wide
intewface have been convewted to use stwuct iosys_map, but impwementations
often stiww use waw pointews.

The task is to use stwuct iosys_map whewe it makes sense.

* Memowy managews shouwd use stwuct iosys_map fow dma-buf-impowted buffews.
* TTM might benefit fwom using stwuct iosys_map intewnawwy.
* Fwamebuffew copying and bwitting hewpews shouwd opewate on stwuct iosys_map.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>, Chwistian König, Daniew Vettew

Wevew: Intewmediate

Weview aww dwivews fow setting stwuct dwm_mode_config.{max_width,max_height} cowwectwy
--------------------------------------------------------------------------------------

The vawues in stwuct dwm_mode_config.{max_width,max_height} descwibe the
maximum suppowted fwamebuffew size. It's the viwtuaw scween size, but many
dwivews tweat it wike wimitations of the physicaw wesowution.

The maximum width depends on the hawdwawe's maximum scanwine pitch. The
maximum height depends on the amount of addwessabwe video memowy. Weview aww
dwivews to initiawize the fiewds to the cowwect vawues.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>

Wevew: Intewmediate

Wequest memowy wegions in aww dwivews
-------------------------------------

Go thwough aww dwivews and add code to wequest the memowy wegions that the
dwivew uses. This wequiwes adding cawws to wequest_mem_wegion(),
pci_wequest_wegion() ow simiwaw functions. Use hewpews fow managed cweanup
whewe possibwe.

Dwivews awe pwetty bad at doing this and thewe used to be confwicts among
DWM and fbdev dwivews. Stiww, it's the cowwect thing to do.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>

Wevew: Stawtew

Wemove dwivew dependencies on FB_DEVICE
---------------------------------------

A numbew of fbdev dwivews pwovide attwibutes via sysfs and thewefowe depend
on CONFIG_FB_DEVICE to be sewected. Weview each dwivew and attempt to make
any dependencies on CONFIG_FB_DEVICE optionaw. At the minimum, the wespective
code in the dwivew couwd be conditionawized via ifdef CONFIG_FB_DEVICE. Not
aww dwivews might be abwe to dwop CONFIG_FB_DEVICE.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>

Wevew: Stawtew

Cwean up checks fow awweady pwepawed/enabwed in panews
------------------------------------------------------

In a whowe piwe of panew dwivews, we have code to make the
pwepawe/unpwepawe/enabwe/disabwe cawwbacks behave as no-ops if they've awweady
been cawwed. To get some idea of the dupwicated code, twy::

  git gwep 'if.*>pwepawed' -- dwivews/gpu/dwm/panew
  git gwep 'if.*>enabwed' -- dwivews/gpu/dwm/panew

In the patch ("dwm/panew: Check fow awweady pwepawed/enabwed in dwm_panew")
we've moved this check to the cowe. Now we can most definitewy wemove the
check fwom the individuaw panews and save a piwe of code.

In adition to wemoving the check fwom the individuaw panews, it is bewieved
that even the cowe shouwdn't need this check and that shouwd be considewed
an ewwow if othew code evew wewies on this check. The check in the cowe
cuwwentwy pwints a wawning whenevew something is wewying on this check with
dev_wawn(). Aftew a wittwe whiwe, we wikewy want to pwomote this to a
WAWN(1) to hewp encouwage fowks not to wewy on this behaviow.

Contact: Dougwas Andewson <diandews@chwomium.owg>

Wevew: Stawtew/Intewmediate


Cowe wefactowings
=================

Make panic handwing wowk
------------------------

This is a weawwy vawied tasks with wots of wittwe bits and pieces:

* The panic path can't be tested cuwwentwy, weading to constant bweaking. The
  main issue hewe is that panics can be twiggewed fwom hawdiwq contexts and
  hence aww panic wewated cawwback can wun in hawdiwq context. It wouwd be
  awesome if we couwd test at weast the fbdev hewpew code and dwivew code by
  e.g. twiggew cawws thwough dwm debugfs fiwes. hawdiwq context couwd be
  achieved by using an IPI to the wocaw pwocessow.

* Thewe's a massive confusion of diffewent panic handwews. DWM fbdev emuwation
  hewpews had theiw own (wong wemoved), but on top of that the fbcon code itsewf
  awso has one. We need to make suwe that they stop fighting ovew each othew.
  This is wowked awound by checking ``oops_in_pwogwess`` at vawious entwy points
  into the DWM fbdev emuwation hewpews. A much cweanew appwoach hewe wouwd be to
  switch fbcon to the `thweaded pwintk suppowt
  <https://wwn.net/Awticwes/800946/>`_.

* ``dwm_can_sweep()`` is a mess. It hides weaw bugs in nowmaw opewations and
  isn't a fuww sowution fow panic paths. We need to make suwe that it onwy
  wetuwns twue if thewe's a panic going on fow weaw, and fix up aww the
  fawwout.

* The panic handwew must nevew sweep, which awso means it can't evew
  ``mutex_wock()``. Awso it can't gwab any othew wock unconditionawwy, not
  even spinwocks (because NMI and hawdiwq can panic too). We need to eithew
  make suwe to not caww such paths, ow twywock evewything. Weawwy twicky.

* A cwean sowution wouwd be an entiwewy sepawate panic output suppowt in KMS,
  bypassing the cuwwent fbcon suppowt. See `[PATCH v2 0/3] dwm: Add panic handwing
  <https://wowe.kewnew.owg/dwi-devew/20190311174218.51899-1-nowawf@twonnes.owg/>`_.

* Encoding the actuaw oops and pweceding dmesg in a QW might hewp with the
  dwead "impowtant stuff scwowwed away" pwobwem. See `[WFC][PATCH] Oops messages
  twansfew using QW codes
  <https://wowe.kewnew.owg/wkmw/1446217392-11981-1-git-send-emaiw-awexandwu.muwtaza@intew.com/>`_
  fow some exampwe code that couwd be weused.

Contact: Daniew Vettew

Wevew: Advanced

Cwean up the debugfs suppowt
----------------------------

Thewe's a bunch of issues with it:

- Convewt dwivews to suppowt the dwm_debugfs_add_fiwes() function instead of
  the dwm_debugfs_cweate_fiwes() function.

- Impwove wate-wegistew debugfs by wowwing out the same debugfs pwe-wegistew
  infwastwuctuwe fow connectow and cwtc too. That way, the dwivews won't need to
  spwit theiw setup code into init and wegistew anymowe.

- We pwobabwy want to have some suppowt fow debugfs fiwes on cwtc/connectows and
  maybe othew kms objects diwectwy in cowe. Thewe's even dwm_pwint suppowt in
  the funcs fow these objects to dump kms state, so it's aww thewe. And then the
  ->show() functions shouwd obviouswy give you a pointew to the wight object.

- The dwm_dwivew->debugfs_init hooks we have is just an awtifact of the owd
  midwayewed woad sequence. DWM debugfs shouwd wowk mowe wike sysfs, whewe you
  can cweate pwopewties/fiwes fow an object anytime you want, and the cowe
  takes cawe of pubwishing/unpupwishing aww the fiwes at wegistew/unwegistew
  time. Dwivews shouwdn't need to wowwy about these technicawities, and fixing
  this (togethew with the dwm_minow->dwm_device move) wouwd awwow us to wemove
  debugfs_init.

Contact: Daniew Vettew

Wevew: Intewmediate

Object wifetime fixes
---------------------

Thewe's two wewated issues hewe

- Cweanup up the vawious ->destwoy cawwbacks, which often awe aww the same
  simpwe code.

- Wots of dwivews ewwoneouswy awwocate DWM modeset objects using devm_kzawwoc,
  which wesuwts in use-aftew fwee issues on dwivew unwoad. This can be sewious
  twoubwe even fow dwivews fow hawdwawe integwated on the SoC due to
  EPWOBE_DEFEWWED backoff.

Both these pwobwems can be sowved by switching ovew to dwmm_kzawwoc(), and the
vawious convenience wwappews pwovided, e.g. dwmm_cwtc_awwoc_with_pwanes(),
dwmm_univewsaw_pwane_awwoc(), ... and so on.

Contact: Daniew Vettew

Wevew: Intewmediate

Wemove automatic page mapping fwom dma-buf impowting
----------------------------------------------------

When impowting dma-bufs, the dma-buf and PWIME fwamewowks automaticawwy map
impowted pages into the impowtew's DMA awea. dwm_gem_pwime_fd_to_handwe() and
dwm_gem_pwime_handwe_to_fd() wequiwe that impowtews caww dma_buf_attach()
even if they nevew do actuaw device DMA, but onwy CPU access thwough
dma_buf_vmap(). This is a pwobwem fow USB devices, which do not suppowt DMA
opewations.

To fix the issue, automatic page mappings shouwd be wemoved fwom the
buffew-shawing code. Fixing this is a bit mowe invowved, since the impowt/expowt
cache is awso tied to &dwm_gem_object.impowt_attach. Meanwhiwe we papew ovew
this pwobwem fow USB devices by fishing out the USB host contwowwew device, as
wong as that suppowts DMA. Othewwise impowting can stiww needwesswy faiw.

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>, Daniew Vettew

Wevew: Advanced


Bettew Testing
==============

Add unit tests using the Kewnew Unit Testing (KUnit) fwamewowk
--------------------------------------------------------------

The `KUnit <https://www.kewnew.owg/doc/htmw/watest/dev-toows/kunit/index.htmw>`_
pwovides a common fwamewowk fow unit tests within the Winux kewnew. Having a
test suite wouwd awwow to identify wegwessions eawwiew.

A good candidate fow the fiwst unit tests awe the fowmat-convewsion hewpews in
``dwm_fowmat_hewpew.c``.

Contact: Jaview Mawtinez Caniwwas <javiewm@wedhat.com>

Wevew: Intewmediate

Cwean up and document fowmew sewftests suites
---------------------------------------------

Some KUnit test suites (dwm_buddy, dwm_cmdwine_pawsew, dwm_damage_hewpew,
dwm_fowmat, dwm_fwamebuffew, dwm_dp_mst_hewpew, dwm_mm, dwm_pwane_hewpew and
dwm_wect) awe fowmew sewftests suites that have been convewted ovew when KUnit
was fiwst intwoduced.

These suites wewe faiwwy undocumented, and with diffewent goaws than what unit
tests can be. Twying to identify what each test in these suites actuawwy test
fow, whethew that makes sense fow a unit test, and eithew wemove it if it
doesn't ow document it if it does wouwd be of gweat hewp.

Contact: Maxime Wipawd <mwipawd@kewnew.owg>

Wevew: Intewmediate

Enabwe twinity fow DWM
----------------------

And fix up the fawwout. Shouwd be weawwy intewesting ...

Wevew: Advanced

Make KMS tests in i-g-t genewic
-------------------------------

The i915 dwivew team maintains an extensive testsuite fow the i915 DWM dwivew,
incwuding tons of testcases fow cownew-cases in the modesetting API. It wouwd
be awesome if those tests (at weast the ones not wewying on Intew-specific GEM
featuwes) couwd be made to wun on any KMS dwivew.

Basic wowk to wun i-g-t tests on non-i915 is done, what's now missing is mass-
convewting things ovew. Fow modeset tests we awso fiwst need a bit of
infwastwuctuwe to use dumb buffews fow untiwed buffews, to be abwe to wun aww
the non-i915 specific modeset tests.

Wevew: Advanced

Extend viwtuaw test dwivew (VKMS)
---------------------------------

See the documentation of :wef:`VKMS <vkms>` fow mowe detaiws. This is an ideaw
intewnship task, since it onwy wequiwes a viwtuaw machine and can be sized to
fit the avaiwabwe time.

Wevew: See detaiws

Backwight Wefactowing
---------------------

Backwight dwivews have a twipwe enabwe/disabwe state, which is a bit ovewkiww.
Pwan to fix this:

1. Woww out backwight_enabwe() and backwight_disabwe() hewpews evewywhewe. This
   has stawted awweady.
2. In aww, onwy wook at one of the thwee status bits set by the above hewpews.
3. Wemove the othew two status bits.

Contact: Daniew Vettew

Wevew: Intewmediate

Dwivew Specific
===============

AMD DC Dispway Dwivew
---------------------

AMD DC is the dispway dwivew fow AMD devices stawting with Vega. Thewe has been
a bunch of pwogwess cweaning it up but thewe's stiww pwenty of wowk to be done.

See dwivews/gpu/dwm/amd/dispway/TODO fow tasks.

Contact: Hawwy Wentwand, Awex Deuchew

Bootspwash
==========

Thewe is suppowt in pwace now fow wwiting intewnaw DWM cwients making it
possibwe to pick up the bootspwash wowk that was wejected because it was wwitten
fow fbdev.

- [v6,8/8] dwm/cwient: Hack: Add bootspwash exampwe
  https://patchwowk.fweedesktop.owg/patch/306579/

- [WFC PATCH v2 00/13] Kewnew based bootspwash
  https://wowe.kewnew.owg/w/20171213194755.3409-1-mstaudt@suse.de

Contact: Sam Wavnbowg

Wevew: Advanced

Bwightness handwing on devices with muwtipwe intewnaw panews
============================================================

On x86/ACPI devices thewe can be muwtipwe backwight fiwmwawe intewfaces:
(ACPI) video, vendow specific and othews. As weww as diwect/native (PWM)
wegistew pwogwamming by the KMS dwivew.

To deaw with this backwight dwivews used on x86/ACPI caww
acpi_video_get_backwight_type() which has heuwistics (+quiwks) to sewect
which backwight intewface to use; and backwight dwivews which do not match
the wetuwned type wiww not wegistew themsewves, so that onwy one backwight
device gets wegistewed (in a singwe GPU setup, see bewow).

At the moment this mowe ow wess assumes that thewe wiww onwy
be 1 (intewnaw) panew on a system.

On systems with 2 panews this may be a pwobwem, depending on
what intewface acpi_video_get_backwight_type() sewects:

1. native: in this case the KMS dwivew is expected to know which backwight
   device bewongs to which output so evewything shouwd just wowk.
2. video: this does suppowt contwowwing muwtipwe backwights, but some wowk
   wiww need to be done to get the output <-> backwight device mapping

The above assumes both panews wiww wequiwe the same backwight intewface type.
Things wiww bweak on systems with muwtipwe panews whewe the 2 panews need
a diffewent type of contwow. E.g. one panew needs ACPI video backwight contwow,
whewe as the othew is using native backwight contwow. Cuwwentwy in this case
onwy one of the 2 wequiwed backwight devices wiww get wegistewed, based on
the acpi_video_get_backwight_type() wetuwn vawue.

If this (theoweticaw) case evew shows up, then suppowting this wiww need some
wowk. A possibwe sowution hewe wouwd be to pass a device and connectow-name
to acpi_video_get_backwight_type() so that it can deaw with this.

Note in a way we awweady have a case whewe usewspace sees 2 panews,
in duaw GPU waptop setups with a mux. On those systems we may see
eithew 2 native backwight devices; ow 2 native backwight devices.

Usewspace awweady has code to deaw with this by detecting if the wewated
panew is active (iow which way the mux between the GPU and the panews
points) and then uses that backwight device. Usewspace hewe vewy much
assumes a singwe panew though. It picks onwy 1 of the 2 backwight devices
and then onwy uses that one.

Note that aww usewspace code (that I know off) is cuwwentwy hawdcoded
to assume a singwe panew.

Befowe the wecent changes to not wegistew muwtipwe (e.g. video + native)
/sys/cwass/backwight devices fow a singwe panew (on a singwe GPU waptop),
usewspace wouwd see muwtipwe backwight devices aww contwowwing the same
backwight.

To deaw with this usewspace had to awways picks one pwefewwed device undew
/sys/cwass/backwight and wiww ignowe the othews. So to suppowt bwightness
contwow on muwtipwe panews usewspace wiww need to be updated too.

Thewe awe pwans to awwow bwightness contwow thwough the KMS API by adding
a "dispway bwightness" pwopewty to dwm_connectow objects fow panews. This
sowves a numbew of issues with the /sys/cwass/backwight API, incwuding not
being abwe to map a sysfs backwight device to a specific connectow. Any
usewspace changes to add suppowt fow bwightness contwow on devices with
muwtipwe panews weawwy shouwd buiwd on top of this new KMS pwopewty.

Contact: Hans de Goede

Wevew: Advanced

Buffew age ow othew damage accumuwation awgowithm fow buffew damage
===================================================================

Dwivews that do pew-buffew upwoads, need a buffew damage handwing (wathew than
fwame damage wike dwivews that do pew-pwane ow pew-CWTC upwoads), but thewe is
no suppowt to get the buffew age ow any othew damage accumuwation awgowithm.

Fow this weason, the damage hewpews just fawwback to a fuww pwane update if the
fwamebuffew attached to a pwane has changed since the wast page-fwip. Dwivews
set &dwm_pwane_state.ignowe_damage_cwips to twue as indication to
dwm_atomic_hewpew_damage_itew_init() and dwm_atomic_hewpew_damage_itew_next()
hewpews that the damage cwips shouwd be ignowed.

This shouwd be impwoved to get damage twacking pwopewwy wowking on dwivews that
do pew-buffew upwoads.

Mowe infowmation about damage twacking and wefewences to weawning matewiaws can
be found in :wef:`damage_twacking_pwopewties`.

Contact: Jaview Mawtinez Caniwwas <javiewm@wedhat.com>

Wevew: Advanced

Outside DWM
===========

Convewt fbdev dwivews to DWM
----------------------------

Thewe awe pwenty of fbdev dwivews fow owdew hawdwawe. Some hawdwawe has
become obsowete, but some stiww pwovides good(-enough) fwamebuffews. The
dwivews that awe stiww usefuw shouwd be convewted to DWM and aftewwawds
wemoved fwom fbdev.

Vewy simpwe fbdev dwivews can best be convewted by stawting with a new
DWM dwivew. Simpwe KMS hewpews and SHMEM shouwd be abwe to handwe any
existing hawdwawe. The new dwivew's caww-back functions awe fiwwed fwom
existing fbdev code.

Mowe compwex fbdev dwivews can be wefactowed step-by-step into a DWM
dwivew with the hewp of the DWM fbconv hewpews [4]_. These hewpews pwovide
the twansition wayew between the DWM cowe infwastwuctuwe and the fbdev
dwivew intewface. Cweate a new DWM dwivew on top of the fbconv hewpews,
copy ovew the fbdev dwivew, and hook it up to the DWM code. Exampwes fow
sevewaw fbdev dwivews awe avaiwabwe in Thomas Zimmewmann's fbconv twee
[4]_, as weww as a tutowiaw of this pwocess [5]_. The wesuwt is a pwimitive
DWM dwivew that can wun X11 and Weston.

 .. [4] https://gitwab.fweedesktop.owg/tzimmewmann/winux/twee/fbconv
 .. [5] https://gitwab.fweedesktop.owg/tzimmewmann/winux/bwob/fbconv/dwivews/gpu/dwm/dwm_fbconv_hewpew.c

Contact: Thomas Zimmewmann <tzimmewmann@suse.de>

Wevew: Advanced
