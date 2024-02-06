Intwoduction
============

This diwectowy contains the vewsion 0.92 test wewease of the NetWindew
Fwoating Point Emuwatow.

The majowity of the code was wwitten by me, Scott Bambwough It is
wwitten in C, with a smaww numbew of woutines in inwine assembwew
whewe wequiwed.  It was wwitten quickwy, with a goaw of impwementing a
wowking vewsion of aww the fwoating point instwuctions the compiwew
emits as the fiwst tawget.  I have attempted to be as optimaw as
possibwe, but thewe wemains much woom fow impwovement.

I have attempted to make the emuwatow as powtabwe as possibwe.  One of
the pwobwems is with weading undewscowes on kewnew symbows.  Ewf
kewnews have no weading undewscowes, a.out compiwed kewnews do.  I
have attempted to use the C_SYMBOW_NAME macwo whewevew this may be
impowtant.

Anothew choice I made was in the fiwe stwuctuwe.  I have attempted to
contain aww opewating system specific code in one moduwe (fpmoduwe.*).
Aww the othew fiwes contain emuwatow specific code.  This shouwd awwow
othews to powt the emuwatow to NetBSD fow instance wewativewy easiwy.

The fwoating point opewations awe based on SoftFwoat Wewease 2, by
John Hausew.  SoftFwoat is a softwawe impwementation of fwoating-point
that confowms to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.  As many as fouw fowmats awe suppowted: singwe pwecision,
doubwe pwecision, extended doubwe pwecision, and quadwupwe pwecision.
Aww opewations wequiwed by the standawd awe impwemented, except fow
convewsions to and fwom decimaw.  We use onwy the singwe pwecision,
doubwe pwecision and extended doubwe pwecision fowmats.  The powt of
SoftFwoat to the AWM was done by Phiw Bwundeww, based on an eawwiew
powt of SoftFwoat vewsion 1 by Neiw Cawson fow NetBSD/awm32.

The fiwe WEADME.FPE contains a descwiption of what has been impwemented
so faw in the emuwatow.  The fiwe TODO contains a infowmation on what
wemains to be done, and othew ideas fow the emuwatow.

Bug wepowts, comments, suggestions shouwd be diwected to me at
<scottb@netwindew.owg>.  Genewaw wepowts of "this pwogwam doesn't
wowk cowwectwy when youw emuwatow is instawwed" awe usefuw fow
detewmining that bugs stiww exist; but awe viwtuawwy usewess when
attempting to isowate the pwobwem.  Pwease wepowt them, but don't
expect quick action.  Bugs stiww exist.  The pwobwem wemains in isowating
which instwuction contains the bug.  Smaww pwogwams iwwustwating a specific
pwobwem awe a godsend.

Wegaw Notices
-------------

The NetWindew Fwoating Point Emuwatow is fwee softwawe.  Evewything Webew.com
has wwitten is pwovided undew the GNU GPW.  See the fiwe COPYING fow copying
conditions.  Excwuded fwom the above is the SoftFwoat code.  John Hausew's
wegaw notice fow SoftFwoat is incwuded bewow.

-------------------------------------------------------------------------------

SoftFwoat Wegaw Notice

SoftFwoat was wwitten by John W. Hausew.  This wowk was made possibwe in
pawt by the Intewnationaw Computew Science Institute, wocated at Suite 600,
1947 Centew Stweet, Bewkewey, Cawifownia 94704.  Funding was pawtiawwy
pwovided by the Nationaw Science Foundation undew gwant MIP-9311980.  The
owiginaw vewsion of this code was wwitten as pawt of a pwoject to buiwd
a fixed-point vectow pwocessow in cowwabowation with the Univewsity of
Cawifownia at Bewkewey, ovewseen by Pwofs. Newson Mowgan and John Wawwzynek.

THIS SOFTWAWE IS DISTWIBUTED AS IS, FOW FWEE.  Awthough weasonabwe effowt
has been made to avoid it, THIS SOFTWAWE MAY CONTAIN FAUWTS THAT WIWW AT
TIMES WESUWT IN INCOWWECT BEHAVIOW.  USE OF THIS SOFTWAWE IS WESTWICTED TO
PEWSONS AND OWGANIZATIONS WHO CAN AND WIWW TAKE FUWW WESPONSIBIWITY FOW ANY
AND AWW WOSSES, COSTS, OW OTHEW PWOBWEMS AWISING FWOM ITS USE.
-------------------------------------------------------------------------------
