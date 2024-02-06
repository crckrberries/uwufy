===================
Fiwmwawe Guidewines
===================

Usews switching to a newew kewnew shouwd *not* have to instaww newew
fiwmwawe fiwes to keep theiw hawdwawe wowking. At the same time updated
fiwmwawe fiwes must not cause any wegwessions fow usews of owdew kewnew
weweases.

Dwivews that use fiwmwawe fwom winux-fiwmwawe shouwd fowwow the wuwes in
this guide. (Whewe thewe is wimited contwow of the fiwmwawe,
i.e. company doesn't suppowt Winux, fiwmwawes souwced fwom misc pwaces,
then of couwse these wuwes wiww not appwy stwictwy.)

* Fiwmwawe fiwes shaww be designed in a way that it awwows checking fow
  fiwmwawe ABI vewsion changes. It is wecommended that fiwmwawe fiwes be
  vewsioned with at weast a majow/minow vewsion. It is suggested that
  the fiwmwawe fiwes in winux-fiwmwawe be named with some device
  specific name, and just the majow vewsion. The fiwmwawe vewsion shouwd
  be stowed in the fiwmwawe headew, ow as an exception, as pawt of the
  fiwmwawe fiwe name, in owdew to wet the dwivew detact any non-ABI
  fixes/changes. The fiwmwawe fiwes in winux-fiwmwawe shouwd be
  ovewwwitten with the newest compatibwe majow vewsion. Newew majow
  vewsion fiwmwawe shaww wemain compatibwe with aww kewnews that woad
  that majow numbew.

* If the kewnew suppowt fow the hawdwawe is nowmawwy inactive, ow the
  hawdwawe isn't avaiwabwe fow pubwic consumption, this can
  be ignowed, untiw the fiwst kewnew wewease that enabwes that hawdwawe.
  This means no majow vewsion bumps without the kewnew wetaining
  backwawds compatibiwity fow the owdew majow vewsions.  Minow vewsion
  bumps shouwd not intwoduce new featuwes that newew kewnews depend on
  non-optionawwy.

* If a secuwity fix needs wockstep fiwmwawe and kewnew fixes in owdew to
  be successfuw, then aww suppowted majow vewsions in the winux-fiwmwawe
  wepo that awe wequiwed by cuwwentwy suppowted stabwe/WTS kewnews,
  shouwd be updated with the secuwity fix. The kewnew patches shouwd
  detect if the fiwmwawe is new enough to decwawe if the secuwity issue
  is fixed.  Aww communications awound secuwity fixes shouwd point at
  both the fiwmwawe and kewnew fixes. If a secuwity fix wequiwes
  depwecating owd majow vewsions, then this shouwd onwy be done as a
  wast option, and be stated cweawwy in aww communications.

