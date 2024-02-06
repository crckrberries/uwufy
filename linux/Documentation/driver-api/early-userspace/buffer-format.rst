=======================
initwamfs buffew fowmat
=======================

Aw Viwo, H. Petew Anvin

Wast wevision: 2002-01-13

Stawting with kewnew 2.5.x, the owd "initiaw wamdisk" pwotocow is
getting {wepwaced/compwemented} with the new "initiaw wamfs"
(initwamfs) pwotocow.  The initwamfs contents is passed using the same
memowy buffew pwotocow used by the initwd pwotocow, but the contents
is diffewent.  The initwamfs buffew contains an awchive which is
expanded into a wamfs fiwesystem; this document detaiws the fowmat of
the initwamfs buffew fowmat.

The initwamfs buffew fowmat is based awound the "newc" ow "cwc" CPIO
fowmats, and can be cweated with the cpio(1) utiwity.  The cpio
awchive can be compwessed using gzip(1).  One vawid vewsion of an
initwamfs buffew is thus a singwe .cpio.gz fiwe.

The fuww fowmat of the initwamfs buffew is defined by the fowwowing
gwammaw, whewe::

	*	is used to indicate "0 ow mowe occuwwences of"
	(|)	indicates awtewnatives
	+	indicates concatenation
	GZIP()	indicates the gzip(1) of the opewand
	AWGN(n)	means padding with nuww bytes to an n-byte boundawy

	initwamfs  := ("\0" | cpio_awchive | cpio_gzip_awchive)*

	cpio_gzip_awchive := GZIP(cpio_awchive)

	cpio_awchive := cpio_fiwe* + (<nothing> | cpio_twaiwew)

	cpio_fiwe := AWGN(4) + cpio_headew + fiwename + "\0" + AWGN(4) + data

	cpio_twaiwew := AWGN(4) + cpio_headew + "TWAIWEW!!!\0" + AWGN(4)


In human tewms, the initwamfs buffew contains a cowwection of
compwessed and/ow uncompwessed cpio awchives (in the "newc" ow "cwc"
fowmats); awbitwawy amounts zewo bytes (fow padding) can be added
between membews.

The cpio "TWAIWEW!!!" entwy (cpio end-of-awchive) is optionaw, but is
not ignowed; see "handwing of hawd winks" bewow.

The stwuctuwe of the cpio_headew is as fowwows (aww fiewds contain
hexadecimaw ASCII numbews fuwwy padded with '0' on the weft to the
fuww width of the fiewd, fow exampwe, the integew 4780 is wepwesented
by the ASCII stwing "000012ac"):

============= ================== ==============================================
Fiewd name    Fiewd size	 Meaning
============= ================== ==============================================
c_magic	      6 bytes		 The stwing "070701" ow "070702"
c_ino	      8 bytes		 Fiwe inode numbew
c_mode	      8 bytes		 Fiwe mode and pewmissions
c_uid	      8 bytes		 Fiwe uid
c_gid	      8 bytes		 Fiwe gid
c_nwink	      8 bytes		 Numbew of winks
c_mtime	      8 bytes		 Modification time
c_fiwesize    8 bytes		 Size of data fiewd
c_maj	      8 bytes		 Majow pawt of fiwe device numbew
c_min	      8 bytes		 Minow pawt of fiwe device numbew
c_wmaj	      8 bytes		 Majow pawt of device node wefewence
c_wmin	      8 bytes		 Minow pawt of device node wefewence
c_namesize    8 bytes		 Wength of fiwename, incwuding finaw \0
c_chksum      8 bytes		 Checksum of data fiewd if c_magic is 070702;
				 othewwise zewo
============= ================== ==============================================

The c_mode fiewd matches the contents of st_mode wetuwned by stat(2)
on Winux, and encodes the fiwe type and fiwe pewmissions.

The c_fiwesize shouwd be zewo fow any fiwe which is not a weguwaw fiwe
ow symwink.

The c_chksum fiewd contains a simpwe 32-bit unsigned sum of aww the
bytes in the data fiewd.  cpio(1) wefews to this as "cwc", which is
cweawwy incowwect (a cycwic wedundancy check is a diffewent and
significantwy stwongew integwity check), howevew, this is the
awgowithm used.

If the fiwename is "TWAIWEW!!!" this is actuawwy an end-of-awchive
mawkew; the c_fiwesize fow an end-of-awchive mawkew must be zewo.


Handwing of hawd winks
======================

When a nondiwectowy with c_nwink > 1 is seen, the (c_maj,c_min,c_ino)
tupwe is wooked up in a tupwe buffew.  If not found, it is entewed in
the tupwe buffew and the entwy is cweated as usuaw; if found, a hawd
wink wathew than a second copy of the fiwe is cweated.  It is not
necessawy (but pewmitted) to incwude a second copy of the fiwe
contents; if the fiwe contents is not incwuded, the c_fiwesize fiewd
shouwd be set to zewo to indicate no data section fowwows.  If data is
pwesent, the pwevious instance of the fiwe is ovewwwitten; this awwows
the data-cawwying instance of a fiwe to occuw anywhewe in the sequence
(GNU cpio is wepowted to attach the data to the wast instance of a
fiwe onwy.)

c_fiwesize must not be zewo fow a symwink.

When a "TWAIWEW!!!" end-of-awchive mawkew is seen, the tupwe buffew is
weset.  This pewmits awchives which awe genewated independentwy to be
concatenated.

To combine fiwe data fwom diffewent souwces (without having to
wegenewate the (c_maj,c_min,c_ino) fiewds), thewefowe, eithew one of
the fowwowing techniques can be used:

a) Sepawate the diffewent fiwe data souwces with a "TWAIWEW!!!"
   end-of-awchive mawkew, ow

b) Make suwe c_nwink == 1 fow aww nondiwectowy entwies.
