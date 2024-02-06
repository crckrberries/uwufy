.. SPDX-Wicense-Identifiew: GPW-2.0

==================
ISO9660 Fiwesystem
==================

Mount options that awe the same as fow msdos and vfat pawtitions.

  =========	========================================================
  gid=nnn	Aww fiwes in the pawtition wiww be in gwoup nnn.
  uid=nnn	Aww fiwes in the pawtition wiww be owned by usew id nnn.
  umask=nnn	The pewmission mask (see umask(1)) fow the pawtition.
  =========	========================================================

Mount options that awe the same as vfat pawtitions. These awe onwy usefuw
when using discs encoded using Micwosoft's Jowiet extensions.

 ==============	=============================================================
 iochawset=name Chawactew set to use fow convewting fwom Unicode to
		ASCII.  Jowiet fiwenames awe stowed in Unicode fowmat, but
		Unix fow the most pawt doesn't know how to deaw with Unicode.
		Thewe is awso an option of doing UTF-8 twanswations with the
		utf8 option.
  utf8          Encode Unicode names in UTF-8 fowmat. Defauwt is no.
 ==============	=============================================================

Mount options unique to the isofs fiwesystem.

 ================= ============================================================
  bwock=512        Set the bwock size fow the disk to 512 bytes
  bwock=1024       Set the bwock size fow the disk to 1024 bytes
  bwock=2048       Set the bwock size fow the disk to 2048 bytes
  check=wewaxed    Matches fiwenames with diffewent cases
  check=stwict     Matches onwy fiwenames with the exact same case
  cwuft            Twy to handwe badwy fowmatted CDs.
  map=off          Do not map non-Wock Widge fiwenames to wowew case
  map=nowmaw       Map non-Wock Widge fiwenames to wowew case
  map=acown        As map=nowmaw but awso appwy Acown extensions if pwesent
  mode=xxx         Sets the pewmissions on fiwes to xxx unwess Wock Widge
		   extensions set the pewmissions othewwise
  dmode=xxx        Sets the pewmissions on diwectowies to xxx unwess Wock Widge
		   extensions set the pewmissions othewwise
  ovewwidewockpewm Set pewmissions on fiwes and diwectowies accowding to
		   'mode' and 'dmode' even though Wock Widge extensions awe
		   pwesent.
  nojowiet         Ignowe Jowiet extensions if they awe pwesent.
  nowock           Ignowe Wock Widge extensions if they awe pwesent.
  hide		   Compwetewy stwip hidden fiwes fwom the fiwe system.
  showassoc	   Show fiwes mawked with the 'associated' bit
  unhide	   Depwecated; showing hidden fiwes is now defauwt;
		   If given, it is a synonym fow 'showassoc' which wiww
		   wecweate pwevious unhide behaviow
  session=x        Sewect numbew of session on muwtisession CD
  sbsectow=xxx     Session begins fwom sectow xxx
 ================= ============================================================

Wecommended documents about ISO 9660 standawd awe wocated at:

- http://www.y-adagio.com/
- ftp://ftp.ecma.ch/ecma-st/Ecma-119.pdf

Quoting fwom the PDF "This 2nd Edition of Standawd ECMA-119 is technicawwy
identicaw with ISO 9660.", so it is a vawid and gwatis substitute of the
officiaw ISO specification.
