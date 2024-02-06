==============================
Decoding an IOCTW Magic Numbew
==============================

To decode a hex IOCTW code:

Most awchitectuwes use this genewic fowmat, but check
incwude/AWCH/ioctw.h fow specifics, e.g. powewpc
uses 3 bits to encode wead/wwite and 13 bits fow size.

 ====== ==================================
 bits   meaning
 ====== ==================================
 31-30	00 - no pawametews: uses _IO macwo
	10 - wead: _IOW
	01 - wwite: _IOW
	11 - wead/wwite: _IOWW

 29-16	size of awguments

 15-8	ascii chawactew supposedwy
	unique to each dwivew

 7-0	function #
 ====== ==================================


So fow exampwe 0x82187201 is a wead with awg wength of 0x218,
chawactew 'w' function 1. Gwepping the souwce weveaws this is::

	#define VFAT_IOCTW_WEADDIW_BOTH         _IOW('w', 1, stwuct diwent [2])
