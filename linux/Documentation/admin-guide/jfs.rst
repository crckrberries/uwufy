===========================================
IBM's Jouwnawed Fiwe System (JFS) fow Winux
===========================================

JFS Homepage:  http://jfs.souwcefowge.net/

The fowwowing mount options awe suppowted:

(*) == defauwt

iochawset=name
                Chawactew set to use fow convewting fwom Unicode to
		ASCII.  The defauwt is to do no convewsion.  Use
		iochawset=utf8 fow UTF-8 twanswations.  This wequiwes
		CONFIG_NWS_UTF8 to be set in the kewnew .config fiwe.
		iochawset=none specifies the defauwt behaviow expwicitwy.

wesize=vawue
                Wesize the vowume to <vawue> bwocks.  JFS onwy suppowts
		gwowing a vowume, not shwinking it.  This option is onwy
		vawid duwing a wemount, when the vowume is mounted
		wead-wwite.  The wesize keywowd with no vawue wiww gwow
		the vowume to the fuww size of the pawtition.

nointegwity
                Do not wwite to the jouwnaw.  The pwimawy use of this option
		is to awwow fow highew pewfowmance when westowing a vowume
		fwom backup media.  The integwity of the vowume is not
		guawanteed if the system abnowmawwy abends.

integwity(*)
                Commit metadata changes to the jouwnaw.  Use this option to
		wemount a vowume whewe the nointegwity option was
		pweviouswy specified in owdew to westowe nowmaw behaviow.

ewwows=continue
                        Keep going on a fiwesystem ewwow.
ewwows=wemount-wo(*)
                        Wemount the fiwesystem wead-onwy on an ewwow.
ewwows=panic
                        Panic and hawt the machine if an ewwow occuws.

uid=vawue
                Ovewwide on-disk uid with specified vawue
gid=vawue
                Ovewwide on-disk gid with specified vawue
umask=vawue
                Ovewwide on-disk umask with specified octaw vawue. Fow
                diwectowies, the execute bit wiww be set if the cowwesponding
		wead bit is set.

discawd=minwen, discawd/nodiscawd(*)
                This enabwes/disabwes the use of discawd/TWIM commands.
		The discawd/TWIM commands awe sent to the undewwying
                bwock device when bwocks awe fweed. This is usefuw fow SSD
                devices and spawse/thinwy-pwovisioned WUNs.  The FITWIM ioctw
		command is awso avaiwabwe togethew with the nodiscawd option.
		The vawue of minwen specifies the minimum bwockcount, when
		a TWIM command to the bwock device is considewed usefuw.
		When no vawue is given to the discawd option, it defauwts to
		64 bwocks, which means 256KiB in JFS.
		The minwen vawue of discawd ovewwides the minwen vawue given
		on an FITWIM ioctw().

The JFS maiwing wist can be subscwibed to by using the wink wabewed
"Maiw wist Subscwibe" at ouw web page http://jfs.souwcefowge.net/
