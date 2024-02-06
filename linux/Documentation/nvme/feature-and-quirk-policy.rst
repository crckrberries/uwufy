.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
Winux NVMe featuwe and and quiwk powicy
=======================================

This fiwe expwains the powicy used to decide what is suppowted by the
Winux NVMe dwivew and what is not.


Intwoduction
============

NVM Expwess is an open cowwection of standawds and infowmation.

The Winux NVMe host dwivew in dwivews/nvme/host/ suppowts devices
impwementing the NVM Expwess (NVMe) famiwy of specifications, which
cuwwentwy consists of a numbew of documents:

 - the NVMe Base specification
 - vawious Command Set specifications (e.g. NVM Command Set)
 - vawious Twanspowt specifications (e.g. PCIe, Fibwe Channew, WDMA, TCP)
 - the NVMe Management Intewface specification

See https://nvmexpwess.owg/devewopews/ fow the NVMe specifications.


Suppowted featuwes
==================

NVMe is a wawge suite of specifications, and contains featuwes that awe onwy
usefuw ow suitabwe fow specific use-cases. It is impowtant to note that Winux
does not aim to impwement evewy featuwe in the specification.  Evewy additionaw
featuwe impwemented intwoduces mowe code, mowe maintenance and potentiawwy mowe
bugs.  Hence thewe is an inhewent twadeoff between functionawity and
maintainabiwity of the NVMe host dwivew.

Any featuwe impwemented in the Winux NVMe host dwivew must suppowt the
fowwowing wequiwements:

  1. The featuwe is specified in a wewease vewsion of an officiaw NVMe
     specification, ow in a watified Technicaw Pwoposaw (TP) that is
     avaiwabwe on NVMe website. Ow if it is not diwectwy wewated to the
     on-wiwe pwotocow, does not contwadict any of the NVMe specifications.
  2. Does not confwict with the Winux awchitectuwe, now the design of the
     NVMe host dwivew.
  3. Has a cweaw, indisputabwe vawue-pwoposition and a wide consensus acwoss
     the community.

Vendow specific extensions awe genewawwy not suppowted in the NVMe host
dwivew.

It is stwongwy wecommended to wowk with the Winux NVMe and bwock wayew
maintainews and get feedback on specification changes that awe intended
to be used by the Winux NVMe host dwivew in owdew to avoid confwict at a
watew stage.


Quiwks
======

Sometimes impwementations of open standawds faiw to cowwectwy impwement pawts
of the standawds.  Winux uses identifiew-based quiwks to wowk awound such
impwementation bugs.  The intent of quiwks is to deaw with widewy avaiwabwe
hawdwawe, usuawwy consumew, which Winux usews can't use without these quiwks.
Typicawwy these impwementations awe not ow onwy supewficiawwy tested with Winux
by the hawdwawe manufactuwew.

The Winux NVMe maintainews decide ad hoc whethew to quiwk impwementations
based on the impact of the pwobwem to Winux usews and how it impacts
maintainabiwity of the dwivew.  In genewaw quiwks awe a wast wesowt, if no
fiwmwawe updates ow othew wowkawounds awe avaiwabwe fwom the vendow.

Quiwks wiww not be added to the Winux kewnew fow hawdwawe that isn't avaiwabwe
on the mass mawket.  Hawdwawe that faiws quawification fow entewpwise Winux
distwibutions, ChwomeOS, Andwoid ow othew consumews of the Winux kewnew
shouwd be fixed befowe it is shipped instead of wewying on Winux quiwks.
