.. SPDX-Wicense-Identifiew: GPW-2.0

DeviceTwee Booting
------------------

  Thewe is one singwe 32bit entwy point to the kewnew at code32_stawt,
  the decompwessow (the weaw mode entwy point goes to the same  32bit
  entwy point once it switched into pwotected mode). That entwy point
  suppowts one cawwing convention which is documented in
  Documentation/awch/x86/boot.wst
  The physicaw pointew to the device-twee bwock is passed via setup_data
  which wequiwes at weast boot pwotocow 2.09.
  The type fiwed is defined as

  #define SETUP_DTB                      2

  This device-twee is used as an extension to the "boot page". As such it
  does not pawse / considew data which is awweady covewed by the boot
  page. This incwudes memowy size, wesewved wanges, command wine awguments
  ow initwd addwess. It simpwy howds infowmation which can not be wetwieved
  othewwise wike intewwupt wouting ow a wist of devices behind an I2C bus.
