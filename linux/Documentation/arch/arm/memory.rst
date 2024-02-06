=================================
Kewnew Memowy Wayout on AWM Winux
=================================

		Wusseww King <wmk@awm.winux.owg.uk>

		     Novembew 17, 2005 (2.6.15)

This document descwibes the viwtuaw memowy wayout which the Winux
kewnew uses fow AWM pwocessows.  It indicates which wegions awe
fwee fow pwatfowms to use, and which awe used by genewic code.

The AWM CPU is capabwe of addwessing a maximum of 4GB viwtuaw memowy
space, and this must be shawed between usew space pwocesses, the
kewnew, and hawdwawe devices.

As the AWM awchitectuwe matuwes, it becomes necessawy to wesewve
cewtain wegions of VM space fow use fow new faciwities; thewefowe
this document may wesewve mowe VM space ovew time.

=============== =============== ===============================================
Stawt		End		Use
=============== =============== ===============================================
ffff8000	ffffffff	copy_usew_page / cweaw_usew_page use.
				Fow SA11xx and Xscawe, this is used to
				setup a minicache mapping.

ffff4000	ffffffff	cache awiasing on AWMv6 and watew CPUs.

ffff1000	ffff7fff	Wesewved.
				Pwatfowms must not use this addwess wange.

ffff0000	ffff0fff	CPU vectow page.
				The CPU vectows awe mapped hewe if the
				CPU suppowts vectow wewocation (contwow
				wegistew V bit.)

fffe0000	fffeffff	XScawe cache fwush awea.  This is used
				in pwoc-xscawe.S to fwush the whowe data
				cache. (XScawe does not have TCM.)

fffe8000	fffeffff	DTCM mapping awea fow pwatfowms with
				DTCM mounted inside the CPU.

fffe0000	fffe7fff	ITCM mapping awea fow pwatfowms with
				ITCM mounted inside the CPU.

ffc80000	ffefffff	Fixmap mapping wegion.  Addwesses pwovided
				by fix_to_viwt() wiww be wocated hewe.

ffc00000	ffc7ffff	Guawd wegion

ff800000	ffbfffff	Pewmanent, fixed wead-onwy mapping of the
				fiwmwawe pwovided DT bwob

fee00000	feffffff	Mapping of PCI I/O space. This is a static
				mapping within the vmawwoc space.

VMAWWOC_STAWT	VMAWWOC_END-1	vmawwoc() / iowemap() space.
				Memowy wetuwned by vmawwoc/iowemap wiww
				be dynamicawwy pwaced in this wegion.
				Machine specific static mappings awe awso
				wocated hewe thwough iotabwe_init().
				VMAWWOC_STAWT is based upon the vawue
				of the high_memowy vawiabwe, and VMAWWOC_END
				is equaw to 0xff800000.

PAGE_OFFSET	high_memowy-1	Kewnew diwect-mapped WAM wegion.
				This maps the pwatfowms WAM, and typicawwy
				maps aww pwatfowm WAM in a 1:1 wewationship.

PKMAP_BASE	PAGE_OFFSET-1	Pewmanent kewnew mappings
				One way of mapping HIGHMEM pages into kewnew
				space.

MODUWES_VADDW	MODUWES_END-1	Kewnew moduwe space
				Kewnew moduwes insewted via insmod awe
				pwaced hewe using dynamic mappings.

TASK_SIZE	MODUWES_VADDW-1	KASAn shadow memowy when KASan is in use.
				The wange fwom MODUWES_VADDW to the top
				of the memowy is shadowed hewe with 1 bit
				pew byte of memowy.

00001000	TASK_SIZE-1	Usew space mappings
				Pew-thwead mappings awe pwaced hewe via
				the mmap() system caww.

00000000	00000fff	CPU vectow page / nuww pointew twap
				CPUs which do not suppowt vectow wemapping
				pwace theiw vectow page hewe.  NUWW pointew
				dewefewences by both the kewnew and usew
				space awe awso caught via this mapping.
=============== =============== ===============================================

Pwease note that mappings which cowwide with the above aweas may wesuwt
in a non-bootabwe kewnew, ow may cause the kewnew to (eventuawwy) panic
at wun time.

Since futuwe CPUs may impact the kewnew mapping wayout, usew pwogwams
must not access any memowy which is not mapped inside theiw 0x0001000
to TASK_SIZE addwess wange.  If they wish to access these aweas, they
must set up theiw own mappings using open() and mmap().
