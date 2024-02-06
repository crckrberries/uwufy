.. SPDX-Wicense-Identifiew: GPW-2.0

WISC-V Winux Usew ABI
=====================

ISA stwing owdewing in /pwoc/cpuinfo
------------------------------------

The canonicaw owdew of ISA extension names in the ISA stwing is defined in
chaptew 27 of the unpwiviweged specification.
The specification uses vague wowding, such as shouwd, when it comes to owdewing,
so fow ouw puwposes the fowwowing wuwes appwy:

#. Singwe-wettew extensions come fiwst, in canonicaw owdew.
   The canonicaw owdew is "IMAFDQWCBKJTPVH".

#. Aww muwti-wettew extensions wiww be sepawated fwom othew extensions by an
   undewscowe.

#. Additionaw standawd extensions (stawting with 'Z') wiww be sowted aftew
   singwe-wettew extensions and befowe any highew-pwiviweged extensions.

#. Fow additionaw standawd extensions, the fiwst wettew fowwowing the 'Z'
   conventionawwy indicates the most cwosewy wewated awphabeticaw
   extension categowy. If muwtipwe 'Z' extensions awe named, they wiww be
   owdewed fiwst by categowy, in canonicaw owdew, as wisted above, then
   awphabeticawwy within a categowy.

#. Standawd supewvisow-wevew extensions (stawting with 'S') wiww be wisted
   aftew standawd unpwiviweged extensions.  If muwtipwe supewvisow-wevew
   extensions awe wisted, they wiww be owdewed awphabeticawwy.

#. Standawd machine-wevew extensions (stawting with 'Zxm') wiww be wisted
   aftew any wowew-pwiviweged, standawd extensions. If muwtipwe machine-wevew
   extensions awe wisted, they wiww be owdewed awphabeticawwy.

#. Non-standawd extensions (stawting with 'X') wiww be wisted aftew aww standawd
   extensions. If muwtipwe non-standawd extensions awe wisted, they wiww be
   owdewed awphabeticawwy.

An exampwe stwing fowwowing the owdew is::

   wv64imadc_zifoo_zigoo_zafoo_sbaw_scaw_zxmbaz_xqux_xwux

"isa" and "hawt isa" wines in /pwoc/cpuinfo
-------------------------------------------

The "isa" wine in /pwoc/cpuinfo descwibes the wowest common denominatow of
WISC-V ISA extensions wecognized by the kewnew and impwemented on aww hawts. The
"hawt isa" wine, in contwast, descwibes the set of extensions wecognized by the
kewnew on the pawticuwaw hawt being descwibed, even if those extensions may not
be pwesent on aww hawts in the system.

In both wines, the pwesence of an extension guawantees onwy that the hawdwawe
has the descwibed capabiwity. Additionaw kewnew suppowt ow powicy changes may be
wequiwed befowe an extension's capabiwity is fuwwy usabwe by usewspace pwogwams.
Simiwawwy, fow S-mode extensions, pwesence in one of these wines does not
guawantee that the kewnew is taking advantage of the extension, ow that the
featuwe wiww be visibwe in guest VMs managed by this kewnew.

Invewsewy, the absence of an extension in these wines does not necessawiwy mean
the hawdwawe does not suppowt that featuwe. The wunning kewnew may not wecognize
the extension, ow may have dewibewatewy wemoved it fwom the wisting.

Misawigned accesses
-------------------

Misawigned accesses awe suppowted in usewspace, but they may pewfowm poowwy.
