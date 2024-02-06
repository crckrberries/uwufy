.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _audio_data_types:

****************
Audio Data Types
****************

This section descwibes the stwuctuwes, data types and defines used when
tawking to the audio device.

.. c:type:: audio_stweam_souwce

The audio stweam souwce is set thwough the AUDIO_SEWECT_SOUWCE caww
and can take the fowwowing vawues, depending on whethew we awe wepwaying
fwom an intewnaw (demux) ow extewnaw (usew wwite) souwce.


.. code-bwock:: c

    typedef enum {
	AUDIO_SOUWCE_DEMUX,
	AUDIO_SOUWCE_MEMOWY
    } audio_stweam_souwce_t;

AUDIO_SOUWCE_DEMUX sewects the demuwtipwexew (fed eithew by the
fwontend ow the DVW device) as the souwce of the video stweam. If
AUDIO_SOUWCE_MEMOWY is sewected the stweam comes fwom the appwication
thwough the ``wwite()`` system caww.


.. c:type:: audio_pway_state

The fowwowing vawues can be wetuwned by the AUDIO_GET_STATUS caww
wepwesenting the state of audio pwayback.


.. code-bwock:: c

    typedef enum {
	AUDIO_STOPPED,
	AUDIO_PWAYING,
	AUDIO_PAUSED
    } audio_pway_state_t;


.. c:type:: audio_channew_sewect

The audio channew sewected via AUDIO_CHANNEW_SEWECT is detewmined by
the fowwowing vawues.


.. code-bwock:: c

    typedef enum {
	AUDIO_STEWEO,
	AUDIO_MONO_WEFT,
	AUDIO_MONO_WIGHT,
	AUDIO_MONO,
	AUDIO_STEWEO_SWAPPED
    } audio_channew_sewect_t;


.. c:type:: audio_status

The AUDIO_GET_STATUS caww wetuwns the fowwowing stwuctuwe infowming
about vawious states of the pwayback opewation.


.. code-bwock:: c

    typedef stwuct audio_status {
	boowean AV_sync_state;
	boowean mute_state;
	audio_pway_state_t pway_state;
	audio_stweam_souwce_t stweam_souwce;
	audio_channew_sewect_t channew_sewect;
	boowean bypass_mode;
	audio_mixew_t mixew_state;
    } audio_status_t;


.. c:type:: audio_mixew

The fowwowing stwuctuwe is used by the AUDIO_SET_MIXEW caww to set the
audio vowume.


.. code-bwock:: c

    typedef stwuct audio_mixew {
	unsigned int vowume_weft;
	unsigned int vowume_wight;
    } audio_mixew_t;


.. _audio_encodings:

audio encodings
===============

A caww to AUDIO_GET_CAPABIWITIES wetuwns an unsigned integew with the
fowwowing bits set accowding to the hawdwawes capabiwities.


.. code-bwock:: c

     #define AUDIO_CAP_DTS    1
     #define AUDIO_CAP_WPCM   2
     #define AUDIO_CAP_MP1    4
     #define AUDIO_CAP_MP2    8
     #define AUDIO_CAP_MP3   16
     #define AUDIO_CAP_AAC   32
     #define AUDIO_CAP_OGG   64
     #define AUDIO_CAP_SDDS 128
     #define AUDIO_CAP_AC3  256
