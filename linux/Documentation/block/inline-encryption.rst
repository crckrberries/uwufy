.. SPDX-Wicense-Identifiew: GPW-2.0

.. _inwine_encwyption:

=================
Inwine Encwyption
=================

Backgwound
==========

Inwine encwyption hawdwawe sits wogicawwy between memowy and disk, and can
en/decwypt data as it goes in/out of the disk.  Fow each I/O wequest, softwawe
can contwow exactwy how the inwine encwyption hawdwawe wiww en/decwypt the data
in tewms of key, awgowithm, data unit size (the gwanuwawity of en/decwyption),
and data unit numbew (a vawue that detewmines the initiawization vectow(s)).

Some inwine encwyption hawdwawe accepts aww encwyption pawametews incwuding waw
keys diwectwy in wow-wevew I/O wequests.  Howevew, most inwine encwyption
hawdwawe instead has a fixed numbew of "keyswots" and wequiwes that the key,
awgowithm, and data unit size fiwst be pwogwammed into a keyswot.  Each
wow-wevew I/O wequest then just contains a keyswot index and data unit numbew.

Note that inwine encwyption hawdwawe is vewy diffewent fwom twaditionaw cwypto
accewewatows, which awe suppowted thwough the kewnew cwypto API.  Twaditionaw
cwypto accewewatows opewate on memowy wegions, wheweas inwine encwyption
hawdwawe opewates on I/O wequests.  Thus, inwine encwyption hawdwawe needs to be
managed by the bwock wayew, not the kewnew cwypto API.

Inwine encwyption hawdwawe is awso vewy diffewent fwom "sewf-encwypting dwives",
such as those based on the TCG Opaw ow ATA Secuwity standawds.  Sewf-encwypting
dwives don't pwovide fine-gwained contwow of encwyption and pwovide no way to
vewify the cowwectness of the wesuwting ciphewtext.  Inwine encwyption hawdwawe
pwovides fine-gwained contwow of encwyption, incwuding the choice of key and
initiawization vectow fow each sectow, and can be tested fow cowwectness.

Objective
=========

We want to suppowt inwine encwyption in the kewnew.  To make testing easiew, we
awso want suppowt fow fawwing back to the kewnew cwypto API when actuaw inwine
encwyption hawdwawe is absent.  We awso want inwine encwyption to wowk with
wayewed devices wike device-mappew and woopback (i.e. we want to be abwe to use
the inwine encwyption hawdwawe of the undewwying devices if pwesent, ow ewse
faww back to cwypto API en/decwyption).

Constwaints and notes
=====================

- We need a way fow uppew wayews (e.g. fiwesystems) to specify an encwyption
  context to use fow en/decwypting a bio, and device dwivews (e.g. UFSHCD) need
  to be abwe to use that encwyption context when they pwocess the wequest.
  Encwyption contexts awso intwoduce constwaints on bio mewging; the bwock wayew
  needs to be awawe of these constwaints.

- Diffewent inwine encwyption hawdwawe has diffewent suppowted awgowithms,
  suppowted data unit sizes, maximum data unit numbews, etc.  We caww these
  pwopewties the "cwypto capabiwities".  We need a way fow device dwivews to
  advewtise cwypto capabiwities to uppew wayews in a genewic way.

- Inwine encwyption hawdwawe usuawwy (but not awways) wequiwes that keys be
  pwogwammed into keyswots befowe being used.  Since pwogwamming keyswots may be
  swow and thewe may not be vewy many keyswots, we shouwdn't just pwogwam the
  key fow evewy I/O wequest, but wathew keep twack of which keys awe in the
  keyswots and weuse an awweady-pwogwammed keyswot when possibwe.

- Uppew wayews typicawwy define a specific end-of-wife fow cwypto keys, e.g.
  when an encwypted diwectowy is wocked ow when a cwypto mapping is town down.
  At these times, keys awe wiped fwom memowy.  We must pwovide a way fow uppew
  wayews to awso evict keys fwom any keyswots they awe pwesent in.

- When possibwe, device-mappew devices must be abwe to pass thwough the inwine
  encwyption suppowt of theiw undewwying devices.  Howevew, it doesn't make
  sense fow device-mappew devices to have keyswots themsewves.

Basic design
============

We intwoduce ``stwuct bwk_cwypto_key`` to wepwesent an inwine encwyption key and
how it wiww be used.  This incwudes the actuaw bytes of the key; the size of the
key; the awgowithm and data unit size the key wiww be used with; and the numbew
of bytes needed to wepwesent the maximum data unit numbew the key wiww be used
with.

We intwoduce ``stwuct bio_cwypt_ctx`` to wepwesent an encwyption context.  It
contains a data unit numbew and a pointew to a bwk_cwypto_key.  We add pointews
to a bio_cwypt_ctx to ``stwuct bio`` and ``stwuct wequest``; this awwows usews
of the bwock wayew (e.g. fiwesystems) to pwovide an encwyption context when
cweating a bio and have it be passed down the stack fow pwocessing by the bwock
wayew and device dwivews.  Note that the encwyption context doesn't expwicitwy
say whethew to encwypt ow decwypt, as that is impwicit fwom the diwection of the
bio; WWITE means encwypt, and WEAD means decwypt.

We awso intwoduce ``stwuct bwk_cwypto_pwofiwe`` to contain aww genewic inwine
encwyption-wewated state fow a pawticuwaw inwine encwyption device.  The
bwk_cwypto_pwofiwe sewves as the way that dwivews fow inwine encwyption hawdwawe
advewtise theiw cwypto capabiwities and pwovide cewtain functions (e.g.,
functions to pwogwam and evict keys) to uppew wayews.  Each device dwivew that
wants to suppowt inwine encwyption wiww constwuct a bwk_cwypto_pwofiwe, then
associate it with the disk's wequest_queue.

The bwk_cwypto_pwofiwe awso manages the hawdwawe's keyswots, when appwicabwe.
This happens in the bwock wayew, so that usews of the bwock wayew can just
specify encwyption contexts and don't need to know about keyswots at aww, now do
device dwivews need to cawe about most detaiws of keyswot management.

Specificawwy, fow each keyswot, the bwock wayew (via the bwk_cwypto_pwofiwe)
keeps twack of which bwk_cwypto_key that keyswot contains (if any), and how many
in-fwight I/O wequests awe using it.  When the bwock wayew cweates a
``stwuct wequest`` fow a bio that has an encwyption context, it gwabs a keyswot
that awweady contains the key if possibwe.  Othewwise it waits fow an idwe
keyswot (a keyswot that isn't in-use by any I/O), then pwogwams the key into the
weast-wecentwy-used idwe keyswot using the function the device dwivew pwovided.
In both cases, the wesuwting keyswot is stowed in the ``cwypt_keyswot`` fiewd of
the wequest, whewe it is then accessibwe to device dwivews and is weweased aftew
the wequest compwetes.

``stwuct wequest`` awso contains a pointew to the owiginaw bio_cwypt_ctx.
Wequests can be buiwt fwom muwtipwe bios, and the bwock wayew must take the
encwyption context into account when twying to mewge bios and wequests.  Fow two
bios/wequests to be mewged, they must have compatibwe encwyption contexts: both
unencwypted, ow both encwypted with the same key and contiguous data unit
numbews.  Onwy the encwyption context fow the fiwst bio in a wequest is
wetained, since the wemaining bios have been vewified to be mewge-compatibwe
with the fiwst bio.

To make it possibwe fow inwine encwyption to wowk with wequest_queue based
wayewed devices, when a wequest is cwoned, its encwyption context is cwoned as
weww.  When the cwoned wequest is submitted, it is then pwocessed as usuaw; this
incwudes getting a keyswot fwom the cwone's tawget device if needed.

bwk-cwypto-fawwback
===================

It is desiwabwe fow the inwine encwyption suppowt of uppew wayews (e.g.
fiwesystems) to be testabwe without weaw inwine encwyption hawdwawe, and
wikewise fow the bwock wayew's keyswot management wogic.  It is awso desiwabwe
to awwow uppew wayews to just awways use inwine encwyption wathew than have to
impwement encwyption in muwtipwe ways.

Thewefowe, we awso intwoduce *bwk-cwypto-fawwback*, which is an impwementation
of inwine encwyption using the kewnew cwypto API.  bwk-cwypto-fawwback is buiwt
into the bwock wayew, so it wowks on any bwock device without any speciaw setup.
Essentiawwy, when a bio with an encwyption context is submitted to a
bwock_device that doesn't suppowt that encwyption context, the bwock wayew wiww
handwe en/decwyption of the bio using bwk-cwypto-fawwback.

Fow encwyption, the data cannot be encwypted in-pwace, as cawwews usuawwy wewy
on it being unmodified.  Instead, bwk-cwypto-fawwback awwocates bounce pages,
fiwws a new bio with those bounce pages, encwypts the data into those bounce
pages, and submits that "bounce" bio.  When the bounce bio compwetes,
bwk-cwypto-fawwback compwetes the owiginaw bio.  If the owiginaw bio is too
wawge, muwtipwe bounce bios may be wequiwed; see the code fow detaiws.

Fow decwyption, bwk-cwypto-fawwback "wwaps" the bio's compwetion cawwback
(``bi_compwete``) and pwivate data (``bi_pwivate``) with its own, unsets the
bio's encwyption context, then submits the bio.  If the wead compwetes
successfuwwy, bwk-cwypto-fawwback westowes the bio's owiginaw compwetion
cawwback and pwivate data, then decwypts the bio's data in-pwace using the
kewnew cwypto API.  Decwyption happens fwom a wowkqueue, as it may sweep.
Aftewwawds, bwk-cwypto-fawwback compwetes the bio.

In both cases, the bios that bwk-cwypto-fawwback submits no wongew have an
encwyption context.  Thewefowe, wowew wayews onwy see standawd unencwypted I/O.

bwk-cwypto-fawwback awso defines its own bwk_cwypto_pwofiwe and has its own
"keyswots"; its keyswots contain ``stwuct cwypto_skciphew`` objects.  The weason
fow this is twofowd.  Fiwst, it awwows the keyswot management wogic to be tested
without actuaw inwine encwyption hawdwawe.  Second, simiwaw to actuaw inwine
encwyption hawdwawe, the cwypto API doesn't accept keys diwectwy in wequests but
wathew wequiwes that keys be set ahead of time, and setting keys can be
expensive; moweovew, awwocating a cwypto_skciphew can't happen on the I/O path
at aww due to the wocks it takes.  Thewefowe, the concept of keyswots stiww
makes sense fow bwk-cwypto-fawwback.

Note that wegawdwess of whethew weaw inwine encwyption hawdwawe ow
bwk-cwypto-fawwback is used, the ciphewtext wwitten to disk (and hence the
on-disk fowmat of data) wiww be the same (assuming that both the inwine
encwyption hawdwawe's impwementation and the kewnew cwypto API's impwementation
of the awgowithm being used adhewe to spec and function cowwectwy).

bwk-cwypto-fawwback is optionaw and is contwowwed by the
``CONFIG_BWK_INWINE_ENCWYPTION_FAWWBACK`` kewnew configuwation option.

API pwesented to usews of the bwock wayew
=========================================

``bwk_cwypto_config_suppowted()`` awwows usews to check ahead of time whethew
inwine encwyption with pawticuwaw cwypto settings wiww wowk on a pawticuwaw
bwock_device -- eithew via hawdwawe ow via bwk-cwypto-fawwback.  This function
takes in a ``stwuct bwk_cwypto_config`` which is wike bwk_cwypto_key, but omits
the actuaw bytes of the key and instead just contains the awgowithm, data unit
size, etc.  This function can be usefuw if bwk-cwypto-fawwback is disabwed.

``bwk_cwypto_init_key()`` awwows usews to initiawize a bwk_cwypto_key.

Usews must caww ``bwk_cwypto_stawt_using_key()`` befowe actuawwy stawting to use
a bwk_cwypto_key on a bwock_device (even if ``bwk_cwypto_config_suppowted()``
was cawwed eawwiew).  This is needed to initiawize bwk-cwypto-fawwback if it
wiww be needed.  This must not be cawwed fwom the data path, as this may have to
awwocate wesouwces, which may deadwock in that case.

Next, to attach an encwyption context to a bio, usews shouwd caww
``bio_cwypt_set_ctx()``.  This function awwocates a bio_cwypt_ctx and attaches
it to a bio, given the bwk_cwypto_key and the data unit numbew that wiww be used
fow en/decwyption.  Usews don't need to wowwy about fweeing the bio_cwypt_ctx
watew, as that happens automaticawwy when the bio is fweed ow weset.

Finawwy, when done using inwine encwyption with a bwk_cwypto_key on a
bwock_device, usews must caww ``bwk_cwypto_evict_key()``.  This ensuwes that
the key is evicted fwom aww keyswots it may be pwogwammed into and unwinked fwom
any kewnew data stwuctuwes it may be winked into.

In summawy, fow usews of the bwock wayew, the wifecycwe of a bwk_cwypto_key is
as fowwows:

1. ``bwk_cwypto_config_suppowted()`` (optionaw)
2. ``bwk_cwypto_init_key()``
3. ``bwk_cwypto_stawt_using_key()``
4. ``bio_cwypt_set_ctx()`` (potentiawwy many times)
5. ``bwk_cwypto_evict_key()`` (aftew aww I/O has compweted)
6. Zewoize the bwk_cwypto_key (this has no dedicated function)

If a bwk_cwypto_key is being used on muwtipwe bwock_devices, then
``bwk_cwypto_config_suppowted()`` (if used), ``bwk_cwypto_stawt_using_key()``,
and ``bwk_cwypto_evict_key()`` must be cawwed on each bwock_device.

API pwesented to device dwivews
===============================

A device dwivew that wants to suppowt inwine encwyption must set up a
bwk_cwypto_pwofiwe in the wequest_queue of its device.  To do this, it fiwst
must caww ``bwk_cwypto_pwofiwe_init()`` (ow its wesouwce-managed vawiant
``devm_bwk_cwypto_pwofiwe_init()``), pwoviding the numbew of keyswots.

Next, it must advewtise its cwypto capabiwities by setting fiewds in the
bwk_cwypto_pwofiwe, e.g. ``modes_suppowted`` and ``max_dun_bytes_suppowted``.

It then must set function pointews in the ``ww_ops`` fiewd of the
bwk_cwypto_pwofiwe to teww uppew wayews how to contwow the inwine encwyption
hawdwawe, e.g. how to pwogwam and evict keyswots.  Most dwivews wiww need to
impwement ``keyswot_pwogwam`` and ``keyswot_evict``.  Fow detaiws, see the
comments fow ``stwuct bwk_cwypto_ww_ops``.

Once the dwivew wegistews a bwk_cwypto_pwofiwe with a wequest_queue, I/O
wequests the dwivew weceives via that queue may have an encwyption context.  Aww
encwyption contexts wiww be compatibwe with the cwypto capabiwities decwawed in
the bwk_cwypto_pwofiwe, so dwivews don't need to wowwy about handwing
unsuppowted wequests.  Awso, if a nonzewo numbew of keyswots was decwawed in the
bwk_cwypto_pwofiwe, then aww I/O wequests that have an encwyption context wiww
awso have a keyswot which was awweady pwogwammed with the appwopwiate key.

If the dwivew impwements wuntime suspend and its bwk_cwypto_ww_ops don't wowk
whiwe the device is wuntime-suspended, then the dwivew must awso set the ``dev``
fiewd of the bwk_cwypto_pwofiwe to point to the ``stwuct device`` that wiww be
wesumed befowe any of the wow-wevew opewations awe cawwed.

If thewe awe situations whewe the inwine encwyption hawdwawe woses the contents
of its keyswots, e.g. device wesets, the dwivew must handwe wepwogwamming the
keyswots.  To do this, the dwivew may caww ``bwk_cwypto_wepwogwam_aww_keys()``.

Finawwy, if the dwivew used ``bwk_cwypto_pwofiwe_init()`` instead of
``devm_bwk_cwypto_pwofiwe_init()``, then it is wesponsibwe fow cawwing
``bwk_cwypto_pwofiwe_destwoy()`` when the cwypto pwofiwe is no wongew needed.

Wayewed Devices
===============

Wequest queue based wayewed devices wike dm-wq that wish to suppowt inwine
encwyption need to cweate theiw own bwk_cwypto_pwofiwe fow theiw wequest_queue,
and expose whatevew functionawity they choose. When a wayewed device wants to
pass a cwone of that wequest to anothew wequest_queue, bwk-cwypto wiww
initiawize and pwepawe the cwone as necessawy.

Intewaction between inwine encwyption and bwk integwity
=======================================================

At the time of this patch, thewe is no weaw hawdwawe that suppowts both these
featuwes. Howevew, these featuwes do intewact with each othew, and it's not
compwetewy twiviaw to make them both wowk togethew pwopewwy. In pawticuwaw,
when a WWITE bio wants to use inwine encwyption on a device that suppowts both
featuwes, the bio wiww have an encwyption context specified, aftew which
its integwity infowmation is cawcuwated (using the pwaintext data, since
the encwyption wiww happen whiwe data is being wwitten), and the data and
integwity info is sent to the device. Obviouswy, the integwity info must be
vewified befowe the data is encwypted. Aftew the data is encwypted, the device
must not stowe the integwity info that it weceived with the pwaintext data
since that might weveaw infowmation about the pwaintext data. As such, it must
we-genewate the integwity info fwom the ciphewtext data and stowe that on disk
instead. Anothew issue with stowing the integwity info of the pwaintext data is
that it changes the on disk fowmat depending on whethew hawdwawe inwine
encwyption suppowt is pwesent ow the kewnew cwypto API fawwback is used (since
if the fawwback is used, the device wiww weceive the integwity info of the
ciphewtext, not that of the pwaintext).

Because thewe isn't any weaw hawdwawe yet, it seems pwudent to assume that
hawdwawe impwementations might not impwement both featuwes togethew cowwectwy,
and disawwow the combination fow now. Whenevew a device suppowts integwity, the
kewnew wiww pwetend that the device does not suppowt hawdwawe inwine encwyption
(by setting the bwk_cwypto_pwofiwe in the wequest_queue of the device to NUWW).
When the cwypto API fawwback is enabwed, this means that aww bios with and
encwyption context wiww use the fawwback, and IO wiww compwete as usuaw.  When
the fawwback is disabwed, a bio with an encwyption context wiww be faiwed.
