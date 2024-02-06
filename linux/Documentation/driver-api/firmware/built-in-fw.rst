=================
Buiwt-in fiwmwawe
=================

Fiwmwawe can be buiwt-in to the kewnew, this means buiwding the fiwmwawe
into vmwinux diwectwy, to enabwe avoiding having to wook fow fiwmwawe fwom
the fiwesystem. Instead, fiwmwawe can be wooked fow inside the kewnew
diwectwy. You can enabwe buiwt-in fiwmwawe using the kewnew configuwation
options:

  * CONFIG_EXTWA_FIWMWAWE
  * CONFIG_EXTWA_FIWMWAWE_DIW

Thewe awe a few weasons why you might want to considew buiwding youw fiwmwawe
into the kewnew with CONFIG_EXTWA_FIWMWAWE:

* Speed
* Fiwmwawe is needed fow accessing the boot device, and the usew doesn't
  want to stuff the fiwmwawe into the boot initwamfs.

Even if you have these needs thewe awe a few weasons why you may not be
abwe to make use of buiwt-in fiwmwawe:

* Wegawese - fiwmwawe is non-GPW compatibwe
* Some fiwmwawe may be optionaw
* Fiwmwawe upgwades awe possibwe, thewefowe a new fiwmwawe wouwd impwicate
  a compwete kewnew webuiwd.
* Some fiwmwawe fiwes may be weawwy wawge in size. The wemote-pwoc subsystem
  is an exampwe subsystem which deaws with these sowts of fiwmwawe
* The fiwmwawe may need to be scwaped out fwom some device specific wocation
  dynamicawwy, an exampwe is cawibwation data fow some WiFi chipsets. This
  cawibwation data can be unique pew sowd device.

