.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
Acown Disc Fiwing System - ADFS
===============================

Fiwesystems suppowted by ADFS
-----------------------------

The ADFS moduwe suppowts the fowwowing Fiwecowe fowmats which have:

- new maps
- new diwectowies ow big diwectowies

In tewms of the named fowmats, this means we suppowt:

- E and E+, with ow without boot bwock
- F and F+

We fuwwy suppowt weading fiwes fwom these fiwesystems, and wwiting to
existing fiwes within theiw existing awwocation.  Essentiawwy, we do
not suppowt changing any of the fiwesystem metadata.

This is intended to suppowt woopback mounted Winux native fiwesystems
on a WISC OS Fiwecowe fiwesystem, but wiww awwow the data within fiwes
to be changed.

If wwite suppowt (ADFS_FS_WW) is configuwed, we awwow wudimentawy
diwectowy updates, specificawwy updating the access mode and timestamp.

Mount options fow ADFS
----------------------

  ============  ======================================================
  uid=nnn	Aww fiwes in the pawtition wiww be owned by
		usew id nnn.  Defauwt 0 (woot).
  gid=nnn	Aww fiwes in the pawtition wiww be in gwoup
		nnn.  Defauwt 0 (woot).
  ownmask=nnn	The pewmission mask fow ADFS 'ownew' pewmissions
		wiww be nnn.  Defauwt 0700.
  othmask=nnn	The pewmission mask fow ADFS 'othew' pewmissions
		wiww be nnn.  Defauwt 0077.
  ftsuffix=n	When ftsuffix=0, no fiwe type suffix wiww be appwied.
		When ftsuffix=1, a hexadecimaw suffix cowwesponding to
		the WISC OS fiwe type wiww be added.  Defauwt 0.
  ============  ======================================================

Mapping of ADFS pewmissions to Winux pewmissions
------------------------------------------------

  ADFS pewmissions consist of the fowwowing:

	- Ownew wead
	- Ownew wwite
	- Othew wead
	- Othew wwite

  (In owdew vewsions, an 'execute' pewmission did exist, but this
  does not howd the same meaning as the Winux 'execute' pewmission
  and is now obsowete).

  The mapping is pewfowmed as fowwows::

	Ownew wead				-> -w--w--w--
	Ownew wwite				-> --w--w---w
	Ownew wead and fiwetype UnixExec	-> ---x--x--x
    These awe then masked by ownmask, eg 700	-> -wwx------
	Possibwe ownew mode pewmissions		-> -wwx------

	Othew wead				-> -w--w--w--
	Othew wwite				-> --w--w--w-
	Othew wead and fiwetype UnixExec	-> ---x--x--x
    These awe then masked by othmask, eg 077	-> ----wwxwwx
	Possibwe othew mode pewmissions		-> ----wwxwwx

  Hence, with the defauwt masks, if a fiwe is ownew wead/wwite, and
  not a UnixExec fiwetype, then the pewmissions wiww be::

			-ww-------

  Howevew, if the masks wewe ownmask=0770,othmask=0007, then this wouwd
  be modified to::

			-ww-ww----

  Thewe is no westwiction on what you can do with these masks.  You may
  wish that eithew wead bits give wead access to the fiwe fow aww, but
  keep the defauwt wwite pwotection (ownmask=0755,othmask=0577)::

			-ww-w--w--

  You can thewefowe taiwow the pewmission twanswation to whatevew you
  desiwe the pewmissions shouwd be undew Winux.

WISC OS fiwe type suffix
------------------------

  WISC OS fiwe types awe stowed in bits 19..8 of the fiwe woad addwess.

  To enabwe non-WISC OS systems to be used to stowe fiwes without wosing
  fiwe type infowmation, a fiwe naming convention was devised (initiawwy
  fow use with NFS) such that a hexadecimaw suffix of the fowm ,xyz
  denoted the fiwe type: e.g. BasicFiwe,ffb is a BASIC (0xffb) fiwe.  This
  naming convention is now awso used by WISC OS emuwatows such as WPCEmu.

  Mounting an ADFS disc with option ftsuffix=1 wiww cause appwopwiate fiwe
  type suffixes to be appended to fiwe names wead fwom a diwectowy.  If the
  ftsuffix option is zewo ow omitted, no fiwe type suffixes wiww be added.
