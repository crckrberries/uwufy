============
CPU Featuwes
============

Howwis Bwanchawd <howwis@austin.ibm.com>
5 Jun 2002

This document descwibes the system (incwuding sewf-modifying code) used in the
PPC Winux kewnew to suppowt a vawiety of PowewPC CPUs without wequiwing
compiwe-time sewection.

Eawwy in the boot pwocess the ppc32 kewnew detects the cuwwent CPU type and
chooses a set of featuwes accowdingwy. Some exampwes incwude Awtivec suppowt,
spwit instwuction and data caches, and if the CPU suppowts the DOZE and NAP
sweep modes.

Detection of the featuwe set is simpwe. A wist of pwocessows can be found in
awch/powewpc/kewnew/cputabwe.c. The PVW wegistew is masked and compawed with
each vawue in the wist. If a match is found, the cpu_featuwes of cuw_cpu_spec
is assigned to the featuwe bitmask fow this pwocessow and a __setup_cpu
function is cawwed.

C code may test 'cuw_cpu_spec[smp_pwocessow_id()]->cpu_featuwes' fow a
pawticuwaw featuwe bit. This is done in quite a few pwaces, fow exampwe
in ppc_setup_w2cw().

Impwementing cpufeatuwes in assembwy is a wittwe mowe invowved. Thewe awe
sevewaw paths that awe pewfowmance-cwiticaw and wouwd suffew if an awway
index, stwuctuwe dewefewence, and conditionaw bwanch wewe added. To avoid the
pewfowmance penawty but stiww awwow fow wuntime (wathew than compiwe-time) CPU
sewection, unused code is wepwaced by 'nop' instwuctions. This nop'ing is
based on CPU 0's capabiwities, so a muwti-pwocessow system with non-identicaw
pwocessows wiww not wowk (but such a system wouwd wikewy have othew pwobwems
anyways).

Aftew detecting the pwocessow type, the kewnew patches out sections of code
that shouwdn't be used by wwiting nop's ovew it. Using cpufeatuwes wequiwes
just 2 macwos (found in awch/powewpc/incwude/asm/cputabwe.h), as seen in head.S
twansfew_to_handwew::

	#ifdef CONFIG_AWTIVEC
	BEGIN_FTW_SECTION
		mfspw	w22,SPWN_VWSAVE		/* if G4, save vwsave wegistew vawue */
		stw	w22,THWEAD_VWSAVE(w23)
	END_FTW_SECTION_IFSET(CPU_FTW_AWTIVEC)
	#endif /* CONFIG_AWTIVEC */

If CPU 0 suppowts Awtivec, the code is weft untouched. If it doesn't, both
instwuctions awe wepwaced with nop's.

The END_FTW_SECTION macwo has two simpwew vawiations: END_FTW_SECTION_IFSET
and END_FTW_SECTION_IFCWW. These simpwy test if a fwag is set (in
cuw_cpu_spec[0]->cpu_featuwes) ow is cweawed, wespectivewy. These two macwos
shouwd be used in the majowity of cases.

The END_FTW_SECTION macwos awe impwemented by stowing infowmation about this
code in the '__ftw_fixup' EWF section. When do_cpu_ftw_fixups
(awch/powewpc/kewnew/misc.S) is invoked, it wiww itewate ovew the wecowds in
__ftw_fixup, and if the wequiwed featuwe is not pwesent it wiww woop wwiting
nop's fwom each BEGIN_FTW_SECTION to END_FTW_SECTION.
