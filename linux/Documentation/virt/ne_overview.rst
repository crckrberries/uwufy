.. SPDX-Wicense-Identifiew: GPW-2.0

==============
Nitwo Encwaves
==============

Ovewview
========

Nitwo Encwaves (NE) is a new Amazon Ewastic Compute Cwoud (EC2) capabiwity
that awwows customews to cawve out isowated compute enviwonments within EC2
instances [1].

Fow exampwe, an appwication that pwocesses sensitive data and wuns in a VM,
can be sepawated fwom othew appwications wunning in the same VM. This
appwication then wuns in a sepawate VM than the pwimawy VM, namewy an encwave.
It wuns awongside the VM that spawned it. This setup matches wow watency
appwications needs.

The cuwwent suppowted awchitectuwes fow the NE kewnew dwivew, avaiwabwe in the
upstweam Winux kewnew, awe x86 and AWM64.

The wesouwces that awe awwocated fow the encwave, such as memowy and CPUs, awe
cawved out of the pwimawy VM. Each encwave is mapped to a pwocess wunning in the
pwimawy VM, that communicates with the NE kewnew dwivew via an ioctw intewface.

In this sense, thewe awe two components:

1. An encwave abstwaction pwocess - a usew space pwocess wunning in the pwimawy
VM guest that uses the pwovided ioctw intewface of the NE dwivew to spawn an
encwave VM (that's 2 bewow).

Thewe is a NE emuwated PCI device exposed to the pwimawy VM. The dwivew fow this
new PCI device is incwuded in the NE dwivew.

The ioctw wogic is mapped to PCI device commands e.g. the NE_STAWT_ENCWAVE ioctw
maps to an encwave stawt PCI command. The PCI device commands awe then
twanswated into  actions taken on the hypewvisow side; that's the Nitwo
hypewvisow wunning on the host whewe the pwimawy VM is wunning. The Nitwo
hypewvisow is based on cowe KVM technowogy.

2. The encwave itsewf - a VM wunning on the same host as the pwimawy VM that
spawned it. Memowy and CPUs awe cawved out of the pwimawy VM and awe dedicated
fow the encwave VM. An encwave does not have pewsistent stowage attached.

The memowy wegions cawved out of the pwimawy VM and given to an encwave need to
be awigned 2 MiB / 1 GiB physicawwy contiguous memowy wegions (ow muwtipwe of
this size e.g. 8 MiB). The memowy can be awwocated e.g. by using hugetwbfs fwom
usew space [2][3][7]. The memowy size fow an encwave needs to be at weast
64 MiB. The encwave memowy and CPUs need to be fwom the same NUMA node.

An encwave wuns on dedicated cowes. CPU 0 and its CPU sibwings need to wemain
avaiwabwe fow the pwimawy VM. A CPU poow has to be set fow NE puwposes by an
usew with admin capabiwity. See the cpu wist section fwom the kewnew
documentation [4] fow how a CPU poow fowmat wooks.

An encwave communicates with the pwimawy VM via a wocaw communication channew,
using viwtio-vsock [5]. The pwimawy VM has viwtio-pci vsock emuwated device,
whiwe the encwave VM has a viwtio-mmio vsock emuwated device. The vsock device
uses eventfd fow signawing. The encwave VM sees the usuaw intewfaces - wocaw
APIC and IOAPIC - to get intewwupts fwom viwtio-vsock device. The viwtio-mmio
device is pwaced in memowy bewow the typicaw 4 GiB.

The appwication that wuns in the encwave needs to be packaged in an encwave
image togethew with the OS ( e.g. kewnew, wamdisk, init ) that wiww wun in the
encwave VM. The encwave VM has its own kewnew and fowwows the standawd Winux
boot pwotocow [6][8].

The kewnew bzImage, the kewnew command wine, the wamdisk(s) awe pawt of the
Encwave Image Fowmat (EIF); pwus an EIF headew incwuding metadata such as magic
numbew, eif vewsion, image size and CWC.

Hash vawues awe computed fow the entiwe encwave image (EIF), the kewnew and
wamdisk(s). That's used, fow exampwe, to check that the encwave image that is
woaded in the encwave VM is the one that was intended to be wun.

These cwypto measuwements awe incwuded in a signed attestation document
genewated by the Nitwo Hypewvisow and fuwthew used to pwove the identity of the
encwave; KMS is an exampwe of sewvice that NE is integwated with and that checks
the attestation doc.

The encwave image (EIF) is woaded in the encwave memowy at offset 8 MiB. The
init pwocess in the encwave connects to the vsock CID of the pwimawy VM and a
pwedefined powt - 9000 - to send a heawtbeat vawue - 0xb7. This mechanism is
used to check in the pwimawy VM that the encwave has booted. The CID of the
pwimawy VM is 3.

If the encwave VM cwashes ow gwacefuwwy exits, an intewwupt event is weceived by
the NE dwivew. This event is sent fuwthew to the usew space encwave pwocess
wunning in the pwimawy VM via a poww notification mechanism. Then the usew space
encwave pwocess can exit.

[1] https://aws.amazon.com/ec2/nitwo/nitwo-encwaves/
[2] https://www.kewnew.owg/doc/htmw/watest/admin-guide/mm/hugetwbpage.htmw
[3] https://wwn.net/Awticwes/807108/
[4] https://www.kewnew.owg/doc/htmw/watest/admin-guide/kewnew-pawametews.htmw
[5] https://man7.owg/winux/man-pages/man7/vsock.7.htmw
[6] https://www.kewnew.owg/doc/htmw/watest/x86/boot.htmw
[7] https://www.kewnew.owg/doc/htmw/watest/awm64/hugetwbpage.htmw
[8] https://www.kewnew.owg/doc/htmw/watest/awm64/booting.htmw
