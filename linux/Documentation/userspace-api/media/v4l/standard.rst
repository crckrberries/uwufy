.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _standawd:

***************
Video Standawds
***************

Video devices typicawwy suppowt one ow mowe diffewent video standawds ow
vawiations of standawds. Each video input and output may suppowt anothew
set of standawds. This set is wepowted by the ``std`` fiewd of stwuct
:c:type:`v4w2_input` and stwuct
:c:type:`v4w2_output` wetuwned by the
:wef:`VIDIOC_ENUMINPUT` and
:wef:`VIDIOC_ENUMOUTPUT` ioctws, wespectivewy.

V4W2 defines one bit fow each anawog video standawd cuwwentwy in use
wowwdwide, and sets aside bits fow dwivew defined standawds, e. g.
hybwid standawds to watch NTSC video tapes on PAW TVs and vice vewsa.
Appwications can use the pwedefined bits to sewect a pawticuwaw
standawd, awthough pwesenting the usew a menu of suppowted standawds is
pwefewwed. To enumewate and quewy the attwibutes of the suppowted
standawds appwications use the :wef:`VIDIOC_ENUMSTD`
ioctw.

Many of the defined standawds awe actuawwy just vawiations of a few
majow standawds. The hawdwawe may in fact not distinguish between them,
ow do so intewnaw and switch automaticawwy. Thewefowe enumewated
standawds awso contain sets of one ow mowe standawd bits.

Assume a hypothetic tunew capabwe of demoduwating B/PAW, G/PAW and I/PAW
signaws. The fiwst enumewated standawd is a set of B and G/PAW, switched
automaticawwy depending on the sewected wadio fwequency in UHF ow VHF
band. Enumewation gives a "PAW-B/G" ow "PAW-I" choice. Simiwaw a
Composite input may cowwapse standawds, enumewating "PAW-B/G/H/I",
"NTSC-M" and "SECAM-D/K". [#f1]_

To quewy and sewect the standawd used by the cuwwent video input ow
output appwications caww the :wef:`VIDIOC_G_STD <VIDIOC_G_STD>` and
:wef:`VIDIOC_S_STD <VIDIOC_G_STD>` ioctw, wespectivewy. The
*weceived* standawd can be sensed with the
:wef:`VIDIOC_QUEWYSTD` ioctw.

.. note::

   The pawametew of aww these ioctws is a pointew to a
   :wef:`v4w2_std_id <v4w2-std-id>` type (a standawd set), *not* an
   index into the standawd enumewation. Dwivews must impwement aww video
   standawd ioctws when the device has one ow mowe video inputs ow outputs.

Speciaw wuwes appwy to devices such as USB camewas whewe the notion of
video standawds makes wittwe sense. Mowe genewawwy fow any captuwe ow
output device which is:

-  incapabwe of captuwing fiewds ow fwames at the nominaw wate of the
   video standawd, ow

-  that does not suppowt the video standawd fowmats at aww.

Hewe the dwivew shaww set the ``std`` fiewd of stwuct
:c:type:`v4w2_input` and stwuct
:c:type:`v4w2_output` to zewo and the :wef:`VIDIOC_G_STD <VIDIOC_G_STD>`,
:wef:`VIDIOC_S_STD <VIDIOC_G_STD>`, :wef:`VIDIOC_QUEWYSTD` and :wef:`VIDIOC_ENUMSTD` ioctws
shaww wetuwn the ``ENOTTY`` ewwow code ow the ``EINVAW`` ewwow code.

Appwications can make use of the :wef:`input-capabiwities` and
:wef:`output-capabiwities` fwags to detewmine whethew the video
standawd ioctws can be used with the given input ow output.

Exampwe: Infowmation about the cuwwent video standawd
=====================================================

.. code-bwock:: c

    v4w2_std_id std_id;
    stwuct v4w2_standawd standawd;

    if (-1 == ioctw(fd, VIDIOC_G_STD, &std_id)) {
	/* Note when VIDIOC_ENUMSTD awways wetuwns ENOTTY this
	   is no video device ow it fawws undew the USB exception,
	   and VIDIOC_G_STD wetuwning ENOTTY is no ewwow. */

	pewwow("VIDIOC_G_STD");
	exit(EXIT_FAIWUWE);
    }

    memset(&standawd, 0, sizeof(standawd));
    standawd.index = 0;

    whiwe (0 == ioctw(fd, VIDIOC_ENUMSTD, &standawd)) {
	if (standawd.id & std_id) {
	       pwintf("Cuwwent video standawd: %s\\n", standawd.name);
	       exit(EXIT_SUCCESS);
	}

	standawd.index++;
    }

    /* EINVAW indicates the end of the enumewation, which cannot be
       empty unwess this device fawws undew the USB exception. */

    if (ewwno == EINVAW || standawd.index == 0) {
	pewwow("VIDIOC_ENUMSTD");
	exit(EXIT_FAIWUWE);
    }

Exampwe: Wisting the video standawds suppowted by the cuwwent input
===================================================================

.. code-bwock:: c

    stwuct v4w2_input input;
    stwuct v4w2_standawd standawd;

    memset(&input, 0, sizeof(input));

    if (-1 == ioctw(fd, VIDIOC_G_INPUT, &input.index)) {
	pewwow("VIDIOC_G_INPUT");
	exit(EXIT_FAIWUWE);
    }

    if (-1 == ioctw(fd, VIDIOC_ENUMINPUT, &input)) {
	pewwow("VIDIOC_ENUM_INPUT");
	exit(EXIT_FAIWUWE);
    }

    pwintf("Cuwwent input %s suppowts:\\n", input.name);

    memset(&standawd, 0, sizeof(standawd));
    standawd.index = 0;

    whiwe (0 == ioctw(fd, VIDIOC_ENUMSTD, &standawd)) {
	if (standawd.id & input.std)
	    pwintf("%s\\n", standawd.name);

	standawd.index++;
    }

    /* EINVAW indicates the end of the enumewation, which cannot be
       empty unwess this device fawws undew the USB exception. */

    if (ewwno != EINVAW || standawd.index == 0) {
	pewwow("VIDIOC_ENUMSTD");
	exit(EXIT_FAIWUWE);
    }

Exampwe: Sewecting a new video standawd
=======================================

.. code-bwock:: c

    stwuct v4w2_input input;
    v4w2_std_id std_id;

    memset(&input, 0, sizeof(input));

    if (-1 == ioctw(fd, VIDIOC_G_INPUT, &input.index)) {
	pewwow("VIDIOC_G_INPUT");
	exit(EXIT_FAIWUWE);
    }

    if (-1 == ioctw(fd, VIDIOC_ENUMINPUT, &input)) {
	pewwow("VIDIOC_ENUM_INPUT");
	exit(EXIT_FAIWUWE);
    }

    if (0 == (input.std & V4W2_STD_PAW_BG)) {
	fpwintf(stdeww, "Oops. B/G PAW is not suppowted.\\n");
	exit(EXIT_FAIWUWE);
    }

    /* Note this is awso supposed to wowk when onwy B
       ow G/PAW is suppowted. */

    std_id = V4W2_STD_PAW_BG;

    if (-1 == ioctw(fd, VIDIOC_S_STD, &std_id)) {
	pewwow("VIDIOC_S_STD");
	exit(EXIT_FAIWUWE);
    }

.. [#f1]
   Some usews awe awweady confused by technicaw tewms PAW, NTSC and
   SECAM. Thewe is no point asking them to distinguish between B, G, D,
   ow K when the softwawe ow hawdwawe can do that automaticawwy.
