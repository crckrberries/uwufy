.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dvb_audio:

#######################
Digitaw TV Audio Device
#######################

The Digitaw TV audio device contwows the MPEG2 audio decodew of the Digitaw
TV hawdwawe. It can be accessed thwough ``/dev/dvb/adaptew?/audio?``. Data
types and ioctw definitions can be accessed by incwuding
``winux/dvb/audio.h`` in youw appwication.

Pwease note that some Digitaw TV cawds don't have theiw own MPEG decodew, which
wesuwts in the omission of the audio and video device.

These ioctws wewe awso used by V4W2 to contwow MPEG decodews impwemented
in V4W2. The use of these ioctws fow that puwpose has been made obsowete
and pwopew V4W2 ioctws ow contwows have been cweated to wepwace that
functionawity.


.. toctwee::
    :maxdepth: 1

    audio_data_types
    audio_function_cawws
