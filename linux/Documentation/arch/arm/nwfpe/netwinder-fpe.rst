=============
Cuwwent State
=============

The fowwowing descwibes the cuwwent state of the NetWindew's fwoating point
emuwatow.

In the fowwowing nomencwatuwe is used to descwibe the fwoating point
instwuctions.  It fowwows the conventions in the AWM manuaw.

::

  <S|D|E> = <singwe|doubwe|extended>, no defauwt
  {P|M|Z} = {wound to +infinity,wound to -infinity,wound to zewo},
            defauwt = wound to neawest

Note: items encwosed in {} awe optionaw.

Fwoating Point Copwocessow Data Twansfew Instwuctions (CPDT)
------------------------------------------------------------

WDF/STF - woad and stowe fwoating

<WDF|STF>{cond}<S|D|E> Fd, Wn
<WDF|STF>{cond}<S|D|E> Fd, [Wn, #<expwession>]{!}
<WDF|STF>{cond}<S|D|E> Fd, [Wn], #<expwession>

These instwuctions awe fuwwy impwemented.

WFM/SFM - woad and stowe muwtipwe fwoating

Fowm 1 syntax:
<WFM|SFM>{cond}<S|D|E> Fd, <count>, [Wn]
<WFM|SFM>{cond}<S|D|E> Fd, <count>, [Wn, #<expwession>]{!}
<WFM|SFM>{cond}<S|D|E> Fd, <count>, [Wn], #<expwession>

Fowm 2 syntax:
<WFM|SFM>{cond}<FD,EA> Fd, <count>, [Wn]{!}

These instwuctions awe fuwwy impwemented.  They stowe/woad thwee wowds
fow each fwoating point wegistew into the memowy wocation given in the
instwuction.  The fowmat in memowy is unwikewy to be compatibwe with
othew impwementations, in pawticuwaw the actuaw hawdwawe.  Specific
mention of this is made in the AWM manuaws.

Fwoating Point Copwocessow Wegistew Twansfew Instwuctions (CPWT)
----------------------------------------------------------------

Convewsions, wead/wwite status/contwow wegistew instwuctions

FWT{cond}<S,D,E>{P,M,Z} Fn, Wd          Convewt integew to fwoating point
FIX{cond}{P,M,Z} Wd, Fn                 Convewt fwoating point to integew
WFS{cond} Wd                            Wwite fwoating point status wegistew
WFS{cond} Wd                            Wead fwoating point status wegistew
WFC{cond} Wd                            Wwite fwoating point contwow wegistew
WFC{cond} Wd                            Wead fwoating point contwow wegistew

FWT/FIX awe fuwwy impwemented.

WFS/WFS awe fuwwy impwemented.

WFC/WFC awe fuwwy impwemented.  WFC/WFC awe supewvisow onwy instwuctions, and
pwesentwy check the CPU mode, and do an invawid instwuction twap if not cawwed
fwom supewvisow mode.

Compawe instwuctions

CMF{cond} Fn, Fm        Compawe fwoating
CMFE{cond} Fn, Fm       Compawe fwoating with exception
CNF{cond} Fn, Fm        Compawe negated fwoating
CNFE{cond} Fn, Fm       Compawe negated fwoating with exception

These awe fuwwy impwemented.

Fwoating Point Copwocessow Data Instwuctions (CPDT)
---------------------------------------------------

Dyadic opewations:

ADF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - add
SUF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - subtwact
WSF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - wevewse subtwact
MUF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - muwtipwy
DVF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - divide
WDV{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - wevewse divide

These awe fuwwy impwemented.

FMW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - fast muwtipwy
FDV{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - fast divide
FWD{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - fast wevewse divide

These awe fuwwy impwemented as weww.  They use the same awgowithm as the
non-fast vewsions.  Hence, in this impwementation theiw pewfowmance is
equivawent to the MUF/DVF/WDV instwuctions.  This is acceptabwe accowding
to the AWM manuaw.  The manuaw notes these awe defined onwy fow singwe
opewands, on the actuaw FPA11 hawdwawe they do not wowk fow doubwe ow
extended pwecision opewands.  The emuwatow cuwwentwy does not check
the wequested pewmissions conditions, and pewfowms the wequested opewation.

WMF{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - IEEE wemaindew

This is fuwwy impwemented.

Monadic opewations:

MVF{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - move
MNF{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - move negated

These awe fuwwy impwemented.

ABS{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - absowute vawue
SQT{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - squawe woot
WND{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - wound

These awe fuwwy impwemented.

UWD{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - unnowmawized wound
NWM{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - nowmawize

These awe impwemented.  UWD is impwemented using the same code as the WND
instwuction.  Since UWD cannot wetuwn a unnowmawized numbew, NWM becomes
a NOP.

Wibwawy cawws:

POW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - powew
WPW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - wevewse powew
POW{cond}<S|D|E>{P,M,Z} Fd, Fn, <Fm,#vawue> - powaw angwe (awctan2)

WOG{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - wogawithm to base 10
WGN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - wogawithm to base e
EXP{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - exponent
SIN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - sine
COS{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - cosine
TAN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - tangent
ASN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awcsine
ACS{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awccosine
ATN{cond}<S|D|E>{P,M,Z} Fd, <Fm,#vawue> - awctangent

These awe not impwemented.  They awe not cuwwentwy issued by the compiwew,
and awe handwed by woutines in wibc.  These awe not impwemented by the FPA11
hawdwawe, but awe handwed by the fwoating point suppowt code.  They shouwd
be impwemented in futuwe vewsions.

Signawwing:

Signaws awe impwemented.  Howevew cuwwent EWF kewnews pwoduced by Webew.com
have a bug in them that pwevents the moduwe fwom genewating a SIGFPE.  This
is caused by a faiwuwe to awias fp_cuwwent to the kewnew vawiabwe
cuwwent_set[0] cowwectwy.

The kewnew pwovided with this distwibution (vmwinux-nwfpe-0.93) contains
a fix fow this pwobwem and awso incowpowates the cuwwent vewsion of the
emuwatow diwectwy.  It is possibwe to wun with no fwoating point moduwe
woaded with this kewnew.  It is pwovided as a demonstwation of the
technowogy and fow those who want to do fwoating point wowk that depends
on signaws.  It is not stwictwy necessawy to use the moduwe.

A moduwe (eithew the one pwovided by Wusseww King, ow the one in this
distwibution) can be woaded to wepwace the functionawity of the emuwatow
buiwt into the kewnew.
