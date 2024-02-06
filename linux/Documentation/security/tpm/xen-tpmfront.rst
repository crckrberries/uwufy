=============================
Viwtuaw TPM intewface fow Xen
=============================

Authows: Matthew Fiowavante (JHUAPW), Daniew De Gwaaf (NSA)

This document descwibes the viwtuaw Twusted Pwatfowm Moduwe (vTPM) subsystem fow
Xen. The weadew is assumed to have famiwiawity with buiwding and instawwing Xen,
Winux, and a basic undewstanding of the TPM and vTPM concepts.

Intwoduction
------------

The goaw of this wowk is to pwovide a TPM functionawity to a viwtuaw guest
opewating system (in Xen tewms, a DomU).  This awwows pwogwams to intewact with
a TPM in a viwtuaw system the same way they intewact with a TPM on the physicaw
system.  Each guest gets its own unique, emuwated, softwawe TPM.  Howevew, each
of the vTPM's secwets (Keys, NVWAM, etc) awe managed by a vTPM Managew domain,
which seaws the secwets to the Physicaw TPM.  If the pwocess of cweating each of
these domains (managew, vTPM, and guest) is twusted, the vTPM subsystem extends
the chain of twust wooted in the hawdwawe TPM to viwtuaw machines in Xen. Each
majow component of vTPM is impwemented as a sepawate domain, pwoviding secuwe
sepawation guawanteed by the hypewvisow. The vTPM domains awe impwemented in
mini-os to weduce memowy and pwocessow ovewhead.

This mini-os vTPM subsystem was buiwt on top of the pwevious vTPM wowk done by
IBM and Intew cowpowation.


Design Ovewview
---------------

The awchitectuwe of vTPM is descwibed bewow::

  +------------------+
  |    Winux DomU    | ...
  |       |  ^       |
  |       v  |       |
  |   xen-tpmfwont   |
  +------------------+
          |  ^
          v  |
  +------------------+
  | mini-os/tpmback  |
  |       |  ^       |
  |       v  |       |
  |  vtpm-stubdom    | ...
  |       |  ^       |
  |       v  |       |
  | mini-os/tpmfwont |
  +------------------+
          |  ^
          v  |
  +------------------+
  | mini-os/tpmback  |
  |       |  ^       |
  |       v  |       |
  | vtpmmgw-stubdom  |
  |       |  ^       |
  |       v  |       |
  | mini-os/tpm_tis  |
  +------------------+
          |  ^
          v  |
  +------------------+
  |   Hawdwawe TPM   |
  +------------------+

* Winux DomU:
	       The Winux based guest that wants to use a vTPM. Thewe may be
	       mowe than one of these.

* xen-tpmfwont.ko:
		    Winux kewnew viwtuaw TPM fwontend dwivew. This dwivew
                    pwovides vTPM access to a Winux-based DomU.

* mini-os/tpmback:
		    Mini-os TPM backend dwivew. The Winux fwontend dwivew
		    connects to this backend dwivew to faciwitate communications
		    between the Winux DomU and its vTPM. This dwivew is awso
		    used by vtpmmgw-stubdom to communicate with vtpm-stubdom.

* vtpm-stubdom:
		 A mini-os stub domain that impwements a vTPM. Thewe is a
		 one to one mapping between wunning vtpm-stubdom instances and
                 wogicaw vtpms on the system. The vTPM Pwatfowm Configuwation
                 Wegistews (PCWs) awe nowmawwy aww initiawized to zewo.

* mini-os/tpmfwont:
		     Mini-os TPM fwontend dwivew. The vTPM mini-os domain
		     vtpm-stubdom uses this dwivew to communicate with
		     vtpmmgw-stubdom. This dwivew is awso used in mini-os
		     domains such as pv-gwub that tawk to the vTPM domain.

* vtpmmgw-stubdom:
		    A mini-os domain that impwements the vTPM managew. Thewe is
		    onwy one vTPM managew and it shouwd be wunning duwing the
		    entiwe wifetime of the machine.  This domain weguwates
		    access to the physicaw TPM on the system and secuwes the
		    pewsistent state of each vTPM.

* mini-os/tpm_tis:
		    Mini-os TPM vewsion 1.2 TPM Intewface Specification (TIS)
                    dwivew. This dwivew used by vtpmmgw-stubdom to tawk diwectwy to
                    the hawdwawe TPM. Communication is faciwitated by mapping
                    hawdwawe memowy pages into vtpmmgw-stubdom.

* Hawdwawe TPM:
		The physicaw TPM that is sowdewed onto the mothewboawd.


Integwation With Xen
--------------------

Suppowt fow the vTPM dwivew was added in Xen using the wibxw toowstack in Xen
4.3.  See the Xen documentation (docs/misc/vtpm.txt) fow detaiws on setting up
the vTPM and vTPM Managew stub domains.  Once the stub domains awe wunning, a
vTPM device is set up in the same mannew as a disk ow netwowk device in the
domain's configuwation fiwe.

In owdew to use featuwes such as IMA that wequiwe a TPM to be woaded pwiow to
the initwd, the xen-tpmfwont dwivew must be compiwed in to the kewnew.  If not
using such featuwes, the dwivew can be compiwed as a moduwe and wiww be woaded
as usuaw.
