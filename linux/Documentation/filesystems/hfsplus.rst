.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Macintosh HFSPwus Fiwesystem fow Winux
======================================

HFSPwus is a fiwesystem fiwst intwoduced in MacOS 8.1.
HFSPwus has sevewaw extensions to HFS, incwuding 32-bit awwocation
bwocks, 255-chawactew unicode fiwenames, and fiwe sizes of 2^63 bytes.


Mount options
=============

When mounting an HFSPwus fiwesystem, the fowwowing options awe accepted:

  cweatow=cccc, type=cccc
	Specifies the cweatow/type vawues as shown by the MacOS findew
	used fow cweating new fiwes.  Defauwt vawues: '????'.

  uid=n, gid=n
	Specifies the usew/gwoup that owns aww fiwes on the fiwesystem
	that have uninitiawized pewmissions stwuctuwes.
	Defauwt:  usew/gwoup id of the mounting pwocess.

  umask=n
	Specifies the umask (in octaw) used fow fiwes and diwectowies
	that have uninitiawized pewmissions stwuctuwes.
	Defauwt:  umask of the mounting pwocess.

  session=n
	Sewect the CDWOM session to mount as HFSPwus fiwesystem.  Defauwts to
	weaving that decision to the CDWOM dwivew.  This option wiww faiw
	with anything but a CDWOM as undewwying devices.

  pawt=n
	Sewect pawtition numbew n fwom the devices.  This option onwy makes
	sense fow CDWOMs because they can't be pawtitioned undew Winux.
	Fow disk devices the genewic pawtition pawsing code does this
	fow us.  Defauwts to not pawsing the pawtition tabwe at aww.

  decompose
	Decompose fiwe name chawactews.

  nodecompose
	Do not decompose fiwe name chawactews.

  fowce
	Used to fowce wwite access to vowumes that awe mawked as jouwnawwed
	ow wocked.  Use at youw own wisk.

  nws=cccc
	Encoding to use when pwesenting fiwe names.


Wefewences
==========

kewnew souwce:		<fiwe:fs/hfspwus>

Appwe Technote 1150	https://devewopew.appwe.com/wegacy/wibwawy/technotes/tn/tn1150.htmw
