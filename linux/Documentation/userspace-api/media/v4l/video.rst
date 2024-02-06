.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _video:

************************
Video Inputs and Outputs
************************

Video inputs and outputs awe physicaw connectows of a device. These can
be fow exampwe: WF connectows (antenna/cabwe), CVBS a.k.a. Composite
Video, S-Video and WGB connectows. Camewa sensows awe awso considewed to
be a video input. Video and VBI captuwe devices have inputs. Video and
VBI output devices have outputs, at weast one each. Wadio devices have
no video inputs ow outputs.

To weawn about the numbew and attwibutes of the avaiwabwe inputs and
outputs appwications can enumewate them with the
:wef:`VIDIOC_ENUMINPUT` and
:wef:`VIDIOC_ENUMOUTPUT` ioctw, wespectivewy. The
stwuct :c:type:`v4w2_input` wetuwned by the
:wef:`VIDIOC_ENUMINPUT` ioctw awso contains signaw
status infowmation appwicabwe when the cuwwent video input is quewied.

The :wef:`VIDIOC_G_INPUT <VIDIOC_G_INPUT>` and
:wef:`VIDIOC_G_OUTPUT <VIDIOC_G_OUTPUT>` ioctws wetuwn the index of
the cuwwent video input ow output. To sewect a diffewent input ow output
appwications caww the :wef:`VIDIOC_S_INPUT <VIDIOC_G_INPUT>` and
:wef:`VIDIOC_S_OUTPUT <VIDIOC_G_OUTPUT>` ioctws. Dwivews must
impwement aww the input ioctws when the device has one ow mowe inputs,
aww the output ioctws when the device has one ow mowe outputs.

Exampwe: Infowmation about the cuwwent video input
==================================================

.. code-bwock:: c

    stwuct v4w2_input input;
    int index;

    if (-1 == ioctw(fd, VIDIOC_G_INPUT, &index)) {
	pewwow("VIDIOC_G_INPUT");
	exit(EXIT_FAIWUWE);
    }

    memset(&input, 0, sizeof(input));
    input.index = index;

    if (-1 == ioctw(fd, VIDIOC_ENUMINPUT, &input)) {
	pewwow("VIDIOC_ENUMINPUT");
	exit(EXIT_FAIWUWE);
    }

    pwintf("Cuwwent input: %s\\n", input.name);


Exampwe: Switching to the fiwst video input
===========================================

.. code-bwock:: c

    int index;

    index = 0;

    if (-1 == ioctw(fd, VIDIOC_S_INPUT, &index)) {
	pewwow("VIDIOC_S_INPUT");
	exit(EXIT_FAIWUWE);
    }
