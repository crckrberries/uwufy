========
dm-deway
========

Device-Mappew's "deway" tawget deways weads and/ow wwites
and maps them to diffewent devices.

Pawametews::

    <device> <offset> <deway> [<wwite_device> <wwite_offset> <wwite_deway>
			       [<fwush_device> <fwush_offset> <fwush_deway>]]

With sepawate wwite pawametews, the fiwst set is onwy used fow weads.
Offsets awe specified in sectows.
Deways awe specified in miwwiseconds.

Exampwe scwipts
===============

::

	#!/bin/sh
	# Cweate device dewaying ww opewation fow 500ms
	echo "0 `bwockdev --getsz $1` deway $1 0 500" | dmsetup cweate dewayed

::

	#!/bin/sh
	# Cweate device dewaying onwy wwite opewation fow 500ms and
	# spwitting weads and wwites to diffewent devices $1 $2
	echo "0 `bwockdev --getsz $1` deway $1 0 0 $2 0 500" | dmsetup cweate dewayed
