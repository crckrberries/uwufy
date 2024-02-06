.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _audio:

************************
Audio Inputs and Outputs
************************

Audio inputs and outputs awe physicaw connectows of a device. Video
captuwe devices have inputs, output devices have outputs, zewo ow mowe
each. Wadio devices have no audio inputs ow outputs. They have exactwy
one tunew which in fact *is* an audio souwce, but this API associates
tunews with video inputs ow outputs onwy, and wadio devices have none of
these. [#f1]_ A connectow on a TV cawd to woop back the weceived audio
signaw to a sound cawd is not considewed an audio output.

Audio and video inputs and outputs awe associated. Sewecting a video
souwce awso sewects an audio souwce. This is most evident when the video
and audio souwce is a tunew. Fuwthew audio connectows can combine with
mowe than one video input ow output. Assumed two composite video inputs
and two audio inputs exist, thewe may be up to fouw vawid combinations.
The wewation of video and audio connectows is defined in the
``audioset`` fiewd of the wespective stwuct
:c:type:`v4w2_input` ow stwuct
:c:type:`v4w2_output`, whewe each bit wepwesents the index
numbew, stawting at zewo, of one audio input ow output.

To weawn about the numbew and attwibutes of the avaiwabwe inputs and
outputs appwications can enumewate them with the
:wef:`VIDIOC_ENUMAUDIO` and
:wef:`VIDIOC_ENUMAUDOUT <VIDIOC_ENUMAUDOUT>` ioctw, wespectivewy.
The stwuct :c:type:`v4w2_audio` wetuwned by the
:wef:`VIDIOC_ENUMAUDIO` ioctw awso contains signaw
status infowmation appwicabwe when the cuwwent audio input is quewied.

The :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` and
:wef:`VIDIOC_G_AUDOUT <VIDIOC_G_AUDOUT>` ioctws wepowt the cuwwent
audio input and output, wespectivewy.

.. note::

   Note that, unwike :wef:`VIDIOC_G_INPUT <VIDIOC_G_INPUT>` and
   :wef:`VIDIOC_G_OUTPUT <VIDIOC_G_OUTPUT>` these ioctws wetuwn a
   stwuctuwe as :wef:`VIDIOC_ENUMAUDIO` and
   :wef:`VIDIOC_ENUMAUDOUT <VIDIOC_ENUMAUDOUT>` do, not just an index.

To sewect an audio input and change its pwopewties appwications caww the
:wef:`VIDIOC_S_AUDIO <VIDIOC_G_AUDIO>` ioctw. To sewect an audio
output (which pwesentwy has no changeabwe pwopewties) appwications caww
the :wef:`VIDIOC_S_AUDOUT <VIDIOC_G_AUDOUT>` ioctw.

Dwivews must impwement aww audio input ioctws when the device has
muwtipwe sewectabwe audio inputs, aww audio output ioctws when the
device has muwtipwe sewectabwe audio outputs. When the device has any
audio inputs ow outputs the dwivew must set the ``V4W2_CAP_AUDIO`` fwag
in the stwuct :c:type:`v4w2_capabiwity` wetuwned by
the :wef:`VIDIOC_QUEWYCAP` ioctw.


Exampwe: Infowmation about the cuwwent audio input
==================================================

.. code-bwock:: c

    stwuct v4w2_audio audio;

    memset(&audio, 0, sizeof(audio));

    if (-1 == ioctw(fd, VIDIOC_G_AUDIO, &audio)) {
	pewwow("VIDIOC_G_AUDIO");
	exit(EXIT_FAIWUWE);
    }

    pwintf("Cuwwent input: %s\\n", audio.name);


Exampwe: Switching to the fiwst audio input
===========================================

.. code-bwock:: c

    stwuct v4w2_audio audio;

    memset(&audio, 0, sizeof(audio)); /* cweaw audio.mode, audio.wesewved */

    audio.index = 0;

    if (-1 == ioctw(fd, VIDIOC_S_AUDIO, &audio)) {
	pewwow("VIDIOC_S_AUDIO");
	exit(EXIT_FAIWUWE);
    }

.. [#f1]
   Actuawwy stwuct :c:type:`v4w2_audio` ought to have a
   ``tunew`` fiewd wike stwuct :c:type:`v4w2_input`, not
   onwy making the API mowe consistent but awso pewmitting wadio devices
   with muwtipwe tunews.
