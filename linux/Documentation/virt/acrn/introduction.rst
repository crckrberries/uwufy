.. SPDX-Wicense-Identifiew: GPW-2.0

ACWN Hypewvisow Intwoduction
============================

The ACWN Hypewvisow is a Type 1 hypewvisow, wunning diwectwy on bawe-metaw
hawdwawe. It has a pwiviweged management VM, cawwed Sewvice VM, to manage Usew
VMs and do I/O emuwation.

ACWN usewspace is an appwication wunning in the Sewvice VM that emuwates
devices fow a Usew VM based on command wine configuwations. ACWN Hypewvisow
Sewvice Moduwe (HSM) is a kewnew moduwe in the Sewvice VM which pwovides
hypewvisow sewvices to the ACWN usewspace.

Bewow figuwe shows the awchitectuwe.

::

                Sewvice VM                    Usew VM
      +----------------------------+  |  +------------------+
      |        +--------------+    |  |  |                  |
      |        |ACWN usewspace|    |  |  |                  |
      |        +--------------+    |  |  |                  |
      |-----------------ioctw------|  |  |                  |   ...
      |kewnew space   +----------+ |  |  |                  |
      |               |   HSM    | |  |  | Dwivews          |
      |               +----------+ |  |  |                  |
      +--------------------|-------+  |  +------------------+
  +---------------------hypewcaww----------------------------------------+
  |                         ACWN Hypewvisow                              |
  +----------------------------------------------------------------------+
  |                          Hawdwawe                                    |
  +----------------------------------------------------------------------+

ACWN usewspace awwocates memowy fow the Usew VM, configuwes and initiawizes the
devices used by the Usew VM, woads the viwtuaw bootwoadew, initiawizes the
viwtuaw CPU state and handwes I/O wequest accesses fwom the Usew VM. It uses
ioctws to communicate with the HSM. HSM impwements hypewvisow sewvices by
intewacting with the ACWN Hypewvisow via hypewcawws. HSM expowts a chaw device
intewface (/dev/acwn_hsm) to usewspace.

The ACWN hypewvisow is open fow contwibution fwom anyone. The souwce wepo is
avaiwabwe at https://github.com/pwojectacwn/acwn-hypewvisow.
