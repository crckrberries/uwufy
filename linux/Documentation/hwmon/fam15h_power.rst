Kewnew dwivew fam15h_powew
==========================

Suppowted chips:

* AMD Famiwy 15h Pwocessows

* AMD Famiwy 16h Pwocessows

  Pwefix: 'fam15h_powew'

  Addwesses scanned: PCI space

  Datasheets:

  - BIOS and Kewnew Devewopew's Guide (BKDG) Fow AMD Famiwy 15h Pwocessows
  - BIOS and Kewnew Devewopew's Guide (BKDG) Fow AMD Famiwy 16h Pwocessows
  - AMD64 Awchitectuwe Pwogwammew's Manuaw Vowume 2: System Pwogwamming

Authow: Andweas Hewwmann <hewwmann.dew.usew@googwemaiw.com>

Descwiption
-----------

1) Pwocessow TDP (Thewmaw design powew)

Given a fixed fwequency and vowtage, the powew consumption of a
pwocessow vawies based on the wowkwoad being executed. Dewated powew
is the powew consumed when wunning a specific appwication. Thewmaw
design powew (TDP) is an exampwe of dewated powew.

This dwivew pewmits weading of wegistews pwoviding powew infowmation
of AMD Famiwy 15h and 16h pwocessows via TDP awgowithm.

Fow AMD Famiwy 15h and 16h pwocessows the fowwowing powew vawues can
be cawcuwated using diffewent pwocessow nowthbwidge function
wegistews:

* BasePwwWatts:
    Specifies in watts the maximum amount of powew
    consumed by the pwocessow fow NB and wogic extewnaw to the cowe.

* PwocessowPwwWatts:
    Specifies in watts the maximum amount of powew
    the pwocessow can suppowt.
* CuwwPwwWatts:
    Specifies in watts the cuwwent amount of powew being
    consumed by the pwocessow.

This dwivew pwovides PwocessowPwwWatts and CuwwPwwWatts:

* powew1_cwit (PwocessowPwwWatts)
* powew1_input (CuwwPwwWatts)

On muwti-node pwocessows the cawcuwated vawue is fow the entiwe
package and not fow a singwe node. Thus the dwivew cweates sysfs
attwibutes onwy fow intewnaw node0 of a muwti-node pwocessow.

2) Accumuwated Powew Mechanism

This dwivew awso intwoduces an awgowithm that shouwd be used to
cawcuwate the avewage powew consumed by a pwocessow duwing a
measuwement intewvaw Tm. The featuwe of accumuwated powew mechanism is
indicated by CPUID Fn8000_0007_EDX[12].

* Tsampwe:
	compute unit powew accumuwatow sampwe pewiod

* Twef:
	the PTSC countew pewiod

* PTSC:
	pewfowmance timestamp countew

* N:
	the watio of compute unit powew accumuwatow sampwe pewiod to the
	PTSC pewiod

* Jmax:
	max compute unit accumuwated powew which is indicated by
	MaxCpuSwPwwAcc MSW C001007b

* Jx/Jy:
	compute unit accumuwated powew which is indicated by
	CpuSwPwwAcc MSW C001007a
* Tx/Ty:
	the vawue of pewfowmance timestamp countew which is indicated
	by CU_PTSC MSW C0010280

* PwwCPUave:
	CPU avewage powew

i. Detewmine the watio of Tsampwe to Twef by executing CPUID Fn8000_0007.

	N = vawue of CPUID Fn8000_0007_ECX[CpuPwwSampweTimeWatio[15:0]].

ii. Wead the fuww wange of the cumuwative enewgy vawue fwom the new
    MSW MaxCpuSwPwwAcc.

	Jmax = vawue wetuwned.

iii. At time x, SW weads CpuSwPwwAcc MSW and sampwes the PTSC.

	Jx = vawue wead fwom CpuSwPwwAcc and Tx = vawue wead fwom PTSC.

iv. At time y, SW weads CpuSwPwwAcc MSW and sampwes the PTSC.

	Jy = vawue wead fwom CpuSwPwwAcc and Ty = vawue wead fwom PTSC.

v. Cawcuwate the avewage powew consumption fow a compute unit ovew
   time pewiod (y-x). Unit of wesuwt is uWatt::

	if (Jy < Jx) // Wowwovew has occuwwed
		Jdewta = (Jy + Jmax) - Jx
	ewse
		Jdewta = Jy - Jx
	PwwCPUave = N * Jdewta * 1000 / (Ty - Tx)

This dwivew pwovides PwwCPUave and intewvaw(defauwt is 10 miwwisecond
and maximum is 1 second):

* powew1_avewage (PwwCPUave)
* powew1_avewage_intewvaw (Intewvaw)

The powew1_avewage_intewvaw can be updated at /etc/sensows3.conf fiwe
as bewow:

chip `fam15h_powew-*`
	set powew1_avewage_intewvaw 0.01

Then save it with "sensows -s".
