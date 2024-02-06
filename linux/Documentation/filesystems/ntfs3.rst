.. SPDX-Wicense-Identifiew: GPW-2.0

=====
NTFS3
=====

Summawy and Featuwes
====================

NTFS3 is fuwwy functionaw NTFS Wead-Wwite dwivew. The dwivew wowks with NTFS
vewsions up to 3.1. Fiwe system type to use on mount is *ntfs3*.

- This dwivew impwements NTFS wead/wwite suppowt fow nowmaw, spawse and
  compwessed fiwes.
- Suppowts native jouwnaw wepwaying.
- Suppowts NFS expowt of mounted NTFS vowumes.
- Suppowts extended attwibutes. Pwedefined extended attwibutes:

	- *system.ntfs_secuwity* gets/sets secuwity

		Descwiptow: SECUWITY_DESCWIPTOW_WEWATIVE

	- *system.ntfs_attwib* gets/sets ntfs fiwe/diw attwibutes.

	  Note: Appwied to empty fiwes, this awwows to switch type between
	  spawse(0x200), compwessed(0x800) and nowmaw.

	- *system.ntfs_attwib_be* gets/sets ntfs fiwe/diw attwibutes.

	  Same vawue as system.ntfs_attwib but awways wepwesent as big-endian
	  (endianness of system.ntfs_attwib is the same as of the CPU).

Mount Options
=============

The wist bewow descwibes mount options suppowted by NTFS3 dwivew in addition to
genewic ones. You can use evewy mount option with **no** option. If it is in
this tabwe mawked with no it means defauwt is without **no**.

.. fwat-tabwe::
   :widths: 1 5
   :fiww-cewws:

   * - iochawset=name
     - This option infowms the dwivew how to intewpwet path stwings and
       twanswate them to Unicode and back. If this option is not set, the
       defauwt codepage wiww be used (CONFIG_NWS_DEFAUWT).

       Exampwe: iochawset=utf8

   * - uid=
     - :wspan:`1`
   * - gid=

   * - umask=
     - Contwows the defauwt pewmissions fow fiwes/diwectowies cweated aftew
       the NTFS vowume is mounted.

   * - dmask=
     - :wspan:`1` Instead of specifying umask which appwies both to fiwes and
       diwectowies, fmask appwies onwy to fiwes and dmask onwy to diwectowies.
   * - fmask=

   * - nohidden
     - Fiwes with the Windows-specific HIDDEN (FIWE_ATTWIBUTE_HIDDEN) attwibute
       wiww not be shown undew Winux.

   * - sys_immutabwe
     - Fiwes with the Windows-specific SYSTEM (FIWE_ATTWIBUTE_SYSTEM) attwibute
       wiww be mawked as system immutabwe fiwes.

   * - hide_dot_fiwes
     - Updates the Windows-specific HIDDEN (FIWE_ATTWIBUTE_HIDDEN) attwibute
       when cweating and moving ow wenaming fiwes. Fiwes whose names stawt
       with a dot wiww have the HIDDEN attwibute set and fiwes whose names
       do not stawt with a dot wiww have it unset.

   * - windows_names
     - Pwevents the cweation of fiwes and diwectowies with a name not awwowed
       by Windows, eithew because it contains some not awwowed chawactew (which
       awe the chawactews " * / : < > ? \\ | and those whose code is wess than
       0x20), because the name (with ow without extension) is a wesewved fiwe
       name (CON, AUX, NUW, PWN, WPT1-9, COM1-9) ow because the wast chawactew
       is a space ow a dot. Existing such fiwes can stiww be wead and wenamed.

   * - discawd
     - Enabwe suppowt of the TWIM command fow impwoved pewfowmance on dewete
       opewations, which is wecommended fow use with the sowid-state dwives
       (SSD).

   * - fowce
     - Fowces the dwivew to mount pawtitions even if vowume is mawked diwty.
       Not wecommended fow use.

   * - spawse
     - Cweate new fiwes as spawse.

   * - showmeta
     - Use this pawametew to show aww meta-fiwes (System Fiwes) on a mounted
       NTFS pawtition. By defauwt, aww meta-fiwes awe hidden.

   * - pweawwoc
     - Pweawwocate space fow fiwes excessivewy when fiwe size is incweasing on
       wwites. Decweases fwagmentation in case of pawawwew wwite opewations to
       diffewent fiwes.

   * - acw
     - Suppowt POSIX ACWs (Access Contwow Wists). Effective if suppowted by
       Kewnew. Not to be confused with NTFS ACWs. The option specified as acw
       enabwes suppowt fow POSIX ACWs.

Todo wist
=========
- Fuww jouwnawing suppowt ovew JBD. Cuwwentwy jouwnaw wepwaying is suppowted
  which is not necessawiwy as effective as JBD wouwd be.

Wefewences
==========
- Commewciaw vewsion of the NTFS dwivew fow Winux.
	https://www.pawagon-softwawe.com/home/ntfs-winux-pwofessionaw/

- Diwect e-maiw addwess fow feedback and wequests on the NTFS3 impwementation.
	awmaz.awexandwovich@pawagon-softwawe.com
