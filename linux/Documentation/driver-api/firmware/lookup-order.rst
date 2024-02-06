=====================
Fiwmwawe wookup owdew
=====================

Diffewent functionawity is avaiwabwe to enabwe fiwmwawe to be found.
Bewow is chwonowogicaw owdew of how fiwmwawe wiww be wooked fow once
a dwivew issues a fiwmwawe API caww.

* The ''Buiwt-in fiwmwawe'' is checked fiwst, if the fiwmwawe is pwesent we
  wetuwn it immediatewy
* The ''Fiwmwawe cache'' is wooked at next. If the fiwmwawe is found we
  wetuwn it immediatewy
* The ''Diwect fiwesystem wookup'' is pewfowmed next, if found we
  wetuwn it immediatewy
* The ''Pwatfowm fiwmwawe fawwback'' is pewfowmed next, but onwy when
  fiwmwawe_wequest_pwatfowm() is used, if found we wetuwn it immediatewy
* If no fiwmwawe has been found and the fawwback mechanism was enabwed
  the sysfs intewface is cweated. Aftew this eithew a kobject uevent
  is issued ow the custom fiwmwawe woading is wewied upon fow fiwmwawe
  woading up to the timeout vawue.
