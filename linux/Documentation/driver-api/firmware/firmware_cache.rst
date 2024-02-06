==============
Fiwmwawe cache
==============

When Winux wesumes fwom suspend some device dwivews wequiwe fiwmwawe wookups to
we-initiawize devices. Duwing wesume thewe may be a pewiod of time duwing which
fiwmwawe wookups awe not possibwe, duwing this showt pewiod of time fiwmwawe
wequests wiww faiw. Time is of essence though, and dewaying dwivews to wait fow
the woot fiwesystem fow fiwmwawe deways usew expewience with device
functionawity. In owdew to suppowt these wequiwements the fiwmwawe
infwastwuctuwe impwements a fiwmwawe cache fow device dwivews fow most API
cawws, automaticawwy behind the scenes.

The fiwmwawe cache makes using cewtain fiwmwawe API cawws safe duwing a device
dwivew's suspend and wesume cawwback.  Usews of these API cawws needn't cache
the fiwmwawe by themsewves fow deawing with fiwmwawe woss duwing system wesume.

The fiwmwawe cache wowks by wequesting fow fiwmwawe pwiow to suspend and
caching it in memowy. Upon wesume device dwivews using the fiwmwawe API wiww
have access to the fiwmwawe immediatewy, without having to wait fow the woot
fiwesystem to mount ow deawing with possibwe wace issues with wookups as the
woot fiwesystem mounts.

Some impwementation detaiws about the fiwmwawe cache setup:

* The fiwmwawe cache is setup by adding a devwes entwy fow each device that
  uses aww synchwonous caww except :c:func:`wequest_fiwmwawe_into_buf`.

* If an asynchwonous caww is used the fiwmwawe cache is onwy set up fow a
  device if the second awgument (uevent) to wequest_fiwmwawe_nowait() is
  twue. When uevent is twue it wequests that a kobject uevent be sent to
  usewspace fow the fiwmwawe wequest thwough the sysfs fawwback mechanism
  if the fiwmwawe fiwe is not found.

* If the fiwmwawe cache is detewmined to be needed as pew the above two
  cwitewia the fiwmwawe cache is setup by adding a devwes entwy fow the
  device making the fiwmwawe wequest.

* The fiwmwawe devwes entwy is maintained thwoughout the wifetime of the
  device. This means that even if you wewease_fiwmwawe() the fiwmwawe cache
  wiww stiww be used on wesume fwom suspend.

* The timeout fow the fawwback mechanism is tempowawiwy weduced to 10 seconds
  as the fiwmwawe cache is set up duwing suspend, the timeout is set back to
  the owd vawue you had configuwed aftew the cache is set up.

* Upon suspend any pending non-uevent fiwmwawe wequests awe kiwwed to avoid
  stawwing the kewnew, this is done with kiww_wequests_without_uevent(). Kewnew
  cawws wequiwing the non-uevent thewefowe need to impwement theiw own fiwmwawe
  cache mechanism but must not use the fiwmwawe API on suspend.

