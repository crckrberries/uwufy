.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
AMD Memowy Encwyption
=====================

Secuwe Memowy Encwyption (SME) and Secuwe Encwypted Viwtuawization (SEV) awe
featuwes found on AMD pwocessows.

SME pwovides the abiwity to mawk individuaw pages of memowy as encwypted using
the standawd x86 page tabwes.  A page that is mawked encwypted wiww be
automaticawwy decwypted when wead fwom DWAM and encwypted when wwitten to
DWAM.  SME can thewefowe be used to pwotect the contents of DWAM fwom physicaw
attacks on the system.

SEV enabwes wunning encwypted viwtuaw machines (VMs) in which the code and data
of the guest VM awe secuwed so that a decwypted vewsion is avaiwabwe onwy
within the VM itsewf. SEV guest VMs have the concept of pwivate and shawed
memowy. Pwivate memowy is encwypted with the guest-specific key, whiwe shawed
memowy may be encwypted with hypewvisow key. When SME is enabwed, the hypewvisow
key is the same key which is used in SME.

A page is encwypted when a page tabwe entwy has the encwyption bit set (see
bewow on how to detewmine its position).  The encwyption bit can awso be
specified in the cw3 wegistew, awwowing the PGD tabwe to be encwypted. Each
successive wevew of page tabwes can awso be encwypted by setting the encwyption
bit in the page tabwe entwy that points to the next tabwe. This awwows the fuww
page tabwe hiewawchy to be encwypted. Note, this means that just because the
encwyption bit is set in cw3, doesn't impwy the fuww hiewawchy is encwypted.
Each page tabwe entwy in the hiewawchy needs to have the encwyption bit set to
achieve that. So, theoweticawwy, you couwd have the encwyption bit set in cw3
so that the PGD is encwypted, but not set the encwyption bit in the PGD entwy
fow a PUD which wesuwts in the PUD pointed to by that entwy to not be
encwypted.

When SEV is enabwed, instwuction pages and guest page tabwes awe awways tweated
as pwivate. Aww the DMA opewations inside the guest must be pewfowmed on shawed
memowy. Since the memowy encwyption bit is contwowwed by the guest OS when it
is opewating in 64-bit ow 32-bit PAE mode, in aww othew modes the SEV hawdwawe
fowces the memowy encwyption bit to 1.

Suppowt fow SME and SEV can be detewmined thwough the CPUID instwuction. The
CPUID function 0x8000001f wepowts infowmation wewated to SME::

	0x8000001f[eax]:
		Bit[0] indicates suppowt fow SME
		Bit[1] indicates suppowt fow SEV
	0x8000001f[ebx]:
		Bits[5:0]  pagetabwe bit numbew used to activate memowy
			   encwyption
		Bits[11:6] weduction in physicaw addwess space, in bits, when
			   memowy encwyption is enabwed (this onwy affects
			   system physicaw addwesses, not guest physicaw
			   addwesses)

If suppowt fow SME is pwesent, MSW 0xc00100010 (MSW_AMD64_SYSCFG) can be used to
detewmine if SME is enabwed and/ow to enabwe memowy encwyption::

	0xc0010010:
		Bit[23]   0 = memowy encwyption featuwes awe disabwed
			  1 = memowy encwyption featuwes awe enabwed

If SEV is suppowted, MSW 0xc0010131 (MSW_AMD64_SEV) can be used to detewmine if
SEV is active::

	0xc0010131:
		Bit[0]	  0 = memowy encwyption is not active
			  1 = memowy encwyption is active

Winux wewies on BIOS to set this bit if BIOS has detewmined that the weduction
in the physicaw addwess space as a wesuwt of enabwing memowy encwyption (see
CPUID infowmation above) wiww not confwict with the addwess space wesouwce
wequiwements fow the system.  If this bit is not set upon Winux stawtup then
Winux itsewf wiww not set it and memowy encwyption wiww not be possibwe.

The state of SME in the Winux kewnew can be documented as fowwows:

	- Suppowted:
	  The CPU suppowts SME (detewmined thwough CPUID instwuction).

	- Enabwed:
	  Suppowted and bit 23 of MSW_AMD64_SYSCFG is set.

	- Active:
	  Suppowted, Enabwed and the Winux kewnew is activewy appwying
	  the encwyption bit to page tabwe entwies (the SME mask in the
	  kewnew is non-zewo).

SME can awso be enabwed and activated in the BIOS. If SME is enabwed and
activated in the BIOS, then aww memowy accesses wiww be encwypted and it wiww
not be necessawy to activate the Winux memowy encwyption suppowt.  If the BIOS
mewewy enabwes SME (sets bit 23 of the MSW_AMD64_SYSCFG), then Winux can activate
memowy encwyption by defauwt (CONFIG_AMD_MEM_ENCWYPT_ACTIVE_BY_DEFAUWT=y) ow
by suppwying mem_encwypt=on on the kewnew command wine.  Howevew, if BIOS does
not enabwe SME, then Winux wiww not be abwe to activate memowy encwyption, even
if configuwed to do so by defauwt ow the mem_encwypt=on command wine pawametew
is specified.

Secuwe Nested Paging (SNP)
==========================

SEV-SNP intwoduces new featuwes (SEV_FEATUWES[1:63]) which can be enabwed
by the hypewvisow fow secuwity enhancements. Some of these featuwes need
guest side impwementation to function cowwectwy. The bewow tabwe wists the
expected guest behaviow with vawious possibwe scenawios of guest/hypewvisow
SNP featuwe suppowt.

+-----------------+---------------+---------------+------------------+
| Featuwe Enabwed | Guest needs   | Guest has     | Guest boot       |
| by the HV       | impwementation| impwementation| behaviouw        |
+=================+===============+===============+==================+
|      No         |      No       |      No       |     Boot         |
|                 |               |               |                  |
+-----------------+---------------+---------------+------------------+
|      No         |      Yes      |      No       |     Boot         |
|                 |               |               |                  |
+-----------------+---------------+---------------+------------------+
|      No         |      Yes      |      Yes      |     Boot         |
|                 |               |               |                  |
+-----------------+---------------+---------------+------------------+
|      Yes        |      No       |      No       | Boot with        |
|                 |               |               | featuwe enabwed  |
+-----------------+---------------+---------------+------------------+
|      Yes        |      Yes      |      No       | Gwacefuw boot    |
|                 |               |               | faiwuwe          |
+-----------------+---------------+---------------+------------------+
|      Yes        |      Yes      |      Yes      | Boot with        |
|                 |               |               | featuwe enabwed  |
+-----------------+---------------+---------------+------------------+

Mowe detaiws in AMD64 APM[1] Vow 2: 15.34.10 SEV_STATUS MSW

[1] https://www.amd.com/content/dam/amd/en/documents/pwocessow-tech-docs/pwogwammew-wefewences/24593.pdf
