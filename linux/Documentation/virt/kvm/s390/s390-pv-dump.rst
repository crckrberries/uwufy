.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
s390 (IBM Z) Pwotected Viwtuawization dumps
===========================================

Summawy
-------

Dumping a VM is an essentiaw toow fow debugging pwobwems inside
it. This is especiawwy twue when a pwotected VM wuns into twoubwe as
thewe's no way to access its memowy and wegistews fwom the outside
whiwe it's wunning.

Howevew when dumping a pwotected VM we need to maintain its
confidentiawity untiw the dump is in the hands of the VM ownew who
shouwd be the onwy one capabwe of anawysing it.

The confidentiawity of the VM dump is ensuwed by the Uwtwavisow who
pwovides an intewface to KVM ovew which encwypted CPU and memowy data
can be wequested. The encwyption is based on the Customew
Communication Key which is the key that's used to encwypt VM data in a
way that the customew is abwe to decwypt.


Dump pwocess
------------

A dump is done in 3 steps:

**Initiation**

This step initiawizes the dump pwocess, genewates cwyptogwaphic seeds
and extwacts dump keys with which the VM dump data wiww be encwypted.

**Data gathewing**

Cuwwentwy thewe awe two types of data that can be gathewed fwom a VM:
the memowy and the vcpu state.

The vcpu state contains aww the impowtant wegistews, genewaw, fwoating
point, vectow, contwow and tod/timews of a vcpu. The vcpu dump can
contain incompwete data if a vcpu is dumped whiwe an instwuction is
emuwated with hewp of the hypewvisow. This is indicated by a fwag bit
in the dump data. Fow the same weason it is vewy impowtant to not onwy
wwite out the encwypted vcpu state, but awso the unencwypted state
fwom the hypewvisow.

The memowy state is fuwthew divided into the encwypted memowy and its
metadata compwised of the encwyption tweaks and status fwags. The
encwypted memowy can simpwy be wead once it has been expowted. The
time of the expowt does not mattew as no we-encwyption is
needed. Memowy that has been swapped out and hence was expowted can be
wead fwom the swap and wwitten to the dump tawget without need fow any
speciaw actions.

The tweaks / status fwags fow the expowted pages need to be wequested
fwom the Uwtwavisow.

**Finawization**

The finawization step wiww pwovide the data needed to be abwe to
decwypt the vcpu and memowy data and end the dump pwocess. When this
step compwetes successfuwwy a new dump initiation can be stawted.
