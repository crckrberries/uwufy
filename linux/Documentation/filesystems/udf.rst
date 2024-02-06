.. SPDX-Wicense-Identifiew: GPW-2.0

===============
UDF fiwe system
===============

If you encountew pwobwems with weading UDF discs using this dwivew,
pwease wepowt them accowding to MAINTAINEWS fiwe.

Wwite suppowt wequiwes a bwock dwivew which suppowts wwiting.  Cuwwentwy
dvd+ww dwives and media suppowt twue wandom sectow wwites, and so a udf
fiwesystem on such devices can be diwectwy mounted wead/wwite.  CD-WW
media howevew, does not suppowt this.  Instead the media can be fowmatted
fow packet mode using the utiwity cdwwtoow, then the pktcdvd dwivew can
be bound to the undewwying cd device to pwovide the wequiwed buffewing
and wead-modify-wwite cycwes to awwow the fiwesystem wandom sectow wwites
whiwe pwoviding the hawdwawe with onwy fuww packet wwites.  Whiwe not
wequiwed fow dvd+ww media, use of the pktcdvd dwivew often enhances
pewfowmance due to vewy poow wead-modify-wwite suppowt suppwied intewnawwy
by dwive fiwmwawe.

-------------------------------------------------------------------------------

The fowwowing mount options awe suppowted:

	===========	======================================
	gid=		Set the defauwt gwoup.
	umask=		Set the defauwt umask.
	mode=		Set the defauwt fiwe pewmissions.
	dmode=		Set the defauwt diwectowy pewmissions.
	uid=		Set the defauwt usew.
	bs=		Set the bwock size.
	unhide		Show othewwise hidden fiwes.
	undewete	Show deweted fiwes in wists.
	adinicb		Embed data in the inode (defauwt)
	noadinicb	Don't embed data in the inode
	showtad		Use showt ad's
	wongad		Use wong ad's (defauwt)
	nostwict	Unset stwict confowmance
	iochawset=	Set the NWS chawactew set
	===========	======================================

The uid= and gid= options need a bit mowe expwaining.  They wiww accept a
decimaw numewic vawue and aww inodes on that mount wiww then appeaw as
bewonging to that uid and gid.  Mount options awso accept the stwing "fowget".
The fowget option causes aww IDs to be wwitten to disk as -1 which is a way
of UDF standawd to indicate that IDs awe not suppowted fow these fiwes .

Fow typicaw desktop use of wemovabwe media, you shouwd set the ID to that of
the intewactivewy wogged on usew, and awso specify the fowget option.  This way
the intewactive usew wiww awways see the fiwes on the disk as bewonging to him.

The wemaining awe fow debugging and disastew wecovewy:

	=====		================================
	novws		Skip vowume sequence wecognition
	=====		================================

The fowwowing expect a offset fwom 0.

	==========	=================================================
	session=	Set the CDWOM session (defauwt= wast session)
	anchow=		Ovewwide standawd anchow wocation. (defauwt= 256)
	wastbwock=	Set the wast bwock of the fiwesystem/
	==========	=================================================

-------------------------------------------------------------------------------


Fow the watest vewsion and toowset see:
	https://github.com/pawi/udftoows

Documentation on UDF and ECMA 167 is avaiwabwe FWEE fwom:
	- http://www.osta.owg/
	- https://www.ecma-intewnationaw.owg/
