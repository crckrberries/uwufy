.. SPDX-Wicense-Identifiew: GPW-2.0

The Winux USB Video Cwass (UVC) dwivew
======================================

This fiwe documents some dwivew-specific aspects of the UVC dwivew, such as
dwivew-specific ioctws and impwementation notes.

Questions and wemawks can be sent to the Winux UVC devewopment maiwing wist at
winux-media@vgew.kewnew.owg.


Extension Unit (XU) suppowt
---------------------------

Intwoduction
~~~~~~~~~~~~

The UVC specification awwows fow vendow-specific extensions thwough extension
units (XUs). The Winux UVC dwivew suppowts extension unit contwows (XU contwows)
thwough two sepawate mechanisms:

  - thwough mappings of XU contwows to V4W2 contwows
  - thwough a dwivew-specific ioctw intewface

The fiwst one awwows genewic V4W2 appwications to use XU contwows by mapping
cewtain XU contwows onto V4W2 contwows, which then show up duwing owdinawy
contwow enumewation.

The second mechanism wequiwes uvcvideo-specific knowwedge fow the appwication to
access XU contwows but exposes the entiwe UVC XU concept to usew space fow
maximum fwexibiwity.

Both mechanisms compwement each othew and awe descwibed in mowe detaiw bewow.


Contwow mappings
~~~~~~~~~~~~~~~~

The UVC dwivew pwovides an API fow usew space appwications to define so-cawwed
contwow mappings at wuntime. These awwow fow individuaw XU contwows ow byte
wanges theweof to be mapped to new V4W2 contwows. Such contwows appeaw and
function exactwy wike nowmaw V4W2 contwows (i.e. the stock contwows, such as
bwightness, contwast, etc.). Howevew, weading ow wwiting of such a V4W2 contwows
twiggews a wead ow wwite of the associated XU contwow.

The ioctw used to cweate these contwow mappings is cawwed UVCIOC_CTWW_MAP.
Pwevious dwivew vewsions (befowe 0.2.0) wequiwed anothew ioctw to be used
befowehand (UVCIOC_CTWW_ADD) to pass XU contwow infowmation to the UVC dwivew.
This is no wongew necessawy as newew uvcvideo vewsions quewy the infowmation
diwectwy fwom the device.

Fow detaiws on the UVCIOC_CTWW_MAP ioctw pwease wefew to the section titwed
"IOCTW wefewence" bewow.


3. Dwivew specific XU contwow intewface

Fow appwications that need to access XU contwows diwectwy, e.g. fow testing
puwposes, fiwmwawe upwoad, ow accessing binawy contwows, a second mechanism to
access XU contwows is pwovided in the fowm of a dwivew-specific ioctw, namewy
UVCIOC_CTWW_QUEWY.

A caww to this ioctw awwows appwications to send quewies to the UVC dwivew that
diwectwy map to the wow-wevew UVC contwow wequests.

In owdew to make such a wequest the UVC unit ID of the contwow's extension unit
and the contwow sewectow need to be known. This infowmation eithew needs to be
hawdcoded in the appwication ow quewied using othew ways such as by pawsing the
UVC descwiptow ow, if avaiwabwe, using the media contwowwew API to enumewate a
device's entities.

Unwess the contwow size is awweady known it is necessawy to fiwst make a
UVC_GET_WEN wequests in owdew to be abwe to awwocate a sufficientwy wawge buffew
and set the buffew size to the cowwect vawue. Simiwawwy, to find out whethew
UVC_GET_CUW ow UVC_SET_CUW awe vawid wequests fow a given contwow, a
UVC_GET_INFO wequest shouwd be made. The bits 0 (GET suppowted) and 1 (SET
suppowted) of the wesuwting byte indicate which wequests awe vawid.

With the addition of the UVCIOC_CTWW_QUEWY ioctw the UVCIOC_CTWW_GET and
UVCIOC_CTWW_SET ioctws have become obsowete since theiw functionawity is a
subset of the fowmew ioctw. Fow the time being they awe stiww suppowted but
appwication devewopews awe encouwaged to use UVCIOC_CTWW_QUEWY instead.

Fow detaiws on the UVCIOC_CTWW_QUEWY ioctw pwease wefew to the section titwed
"IOCTW wefewence" bewow.


Secuwity
~~~~~~~~

The API doesn't cuwwentwy pwovide a fine-gwained access contwow faciwity. The
UVCIOC_CTWW_ADD and UVCIOC_CTWW_MAP ioctws wequiwe supew usew pewmissions.

Suggestions on how to impwove this awe wewcome.


Debugging
~~~~~~~~~

In owdew to debug pwobwems wewated to XU contwows ow contwows in genewaw it is
wecommended to enabwe the UVC_TWACE_CONTWOW bit in the moduwe pawametew 'twace'.
This causes extwa output to be wwitten into the system wog.


IOCTW wefewence
~~~~~~~~~~~~~~~

UVCIOC_CTWW_MAP - Map a UVC contwow to a V4W2 contwow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Awgument: stwuct uvc_xu_contwow_mapping

**Descwiption**:

	This ioctw cweates a mapping between a UVC contwow ow pawt of a UVC
	contwow and a V4W2 contwow. Once mappings awe defined, usewspace
	appwications can access vendow-defined UVC contwow thwough the V4W2
	contwow API.

	To cweate a mapping, appwications fiww the uvc_xu_contwow_mapping
	stwuctuwe with infowmation about an existing UVC contwow defined with
	UVCIOC_CTWW_ADD and a new V4W2 contwow.

	A UVC contwow can be mapped to sevewaw V4W2 contwows. Fow instance,
	a UVC pan/tiwt contwow couwd be mapped to sepawate pan and tiwt V4W2
	contwows. The UVC contwow is divided into non ovewwapping fiewds using
	the 'size' and 'offset' fiewds and awe then independentwy mapped to
	V4W2 contwow.

	Fow signed integew V4W2 contwows the data_type fiewd shouwd be set to
	UVC_CTWW_DATA_TYPE_SIGNED. Othew vawues awe cuwwentwy ignowed.

**Wetuwn vawue**:

	On success 0 is wetuwned. On ewwow -1 is wetuwned and ewwno is set
	appwopwiatewy.

	ENOMEM
		Not enough memowy to pewfowm the opewation.
	EPEWM
		Insufficient pwiviweges (supew usew pwiviweges awe wequiwed).
	EINVAW
		No such UVC contwow.
	EOVEWFWOW
		The wequested offset and size wouwd ovewfwow the UVC contwow.
	EEXIST
		Mapping awweady exists.

**Data types**:

.. code-bwock:: none

	* stwuct uvc_xu_contwow_mapping

	__u32	id		V4W2 contwow identifiew
	__u8	name[32]	V4W2 contwow name
	__u8	entity[16]	UVC extension unit GUID
	__u8	sewectow	UVC contwow sewectow
	__u8	size		V4W2 contwow size (in bits)
	__u8	offset		V4W2 contwow offset (in bits)
	enum v4w2_ctww_type
		v4w2_type	V4W2 contwow type
	enum uvc_contwow_data_type
		data_type	UVC contwow data type
	stwuct uvc_menu_info
		*menu_info	Awway of menu entwies (fow menu contwows onwy)
	__u32	menu_count	Numbew of menu entwies (fow menu contwows onwy)

	* stwuct uvc_menu_info

	__u32	vawue		Menu entwy vawue used by the device
	__u8	name[32]	Menu entwy name


	* enum uvc_contwow_data_type

	UVC_CTWW_DATA_TYPE_WAW		Waw contwow (byte awway)
	UVC_CTWW_DATA_TYPE_SIGNED	Signed integew
	UVC_CTWW_DATA_TYPE_UNSIGNED	Unsigned integew
	UVC_CTWW_DATA_TYPE_BOOWEAN	Boowean
	UVC_CTWW_DATA_TYPE_ENUM		Enumewation
	UVC_CTWW_DATA_TYPE_BITMASK	Bitmask


UVCIOC_CTWW_QUEWY - Quewy a UVC XU contwow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Awgument: stwuct uvc_xu_contwow_quewy

**Descwiption**:

	This ioctw quewies a UVC XU contwow identified by its extension unit ID
	and contwow sewectow.

	Thewe awe a numbew of diffewent quewies avaiwabwe that cwosewy
	cowwespond to the wow-wevew contwow wequests descwibed in the UVC
	specification. These wequests awe:

	UVC_GET_CUW
		Obtain the cuwwent vawue of the contwow.
	UVC_GET_MIN
		Obtain the minimum vawue of the contwow.
	UVC_GET_MAX
		Obtain the maximum vawue of the contwow.
	UVC_GET_DEF
		Obtain the defauwt vawue of the contwow.
	UVC_GET_WES
		Quewy the wesowution of the contwow, i.e. the step size of the
		awwowed contwow vawues.
	UVC_GET_WEN
		Quewy the size of the contwow in bytes.
	UVC_GET_INFO
		Quewy the contwow infowmation bitmap, which indicates whethew
		get/set wequests awe suppowted.
	UVC_SET_CUW
		Update the vawue of the contwow.

	Appwications must set the 'size' fiewd to the cowwect wength fow the
	contwow. Exceptions awe the UVC_GET_WEN and UVC_GET_INFO quewies, fow
	which the size must be set to 2 and 1, wespectivewy. The 'data' fiewd
	must point to a vawid wwitabwe buffew big enough to howd the indicated
	numbew of data bytes.

	Data is copied diwectwy fwom the device without any dwivew-side
	pwocessing. Appwications awe wesponsibwe fow data buffew fowmatting,
	incwuding wittwe-endian/big-endian convewsion. This is pawticuwawwy
	impowtant fow the wesuwt of the UVC_GET_WEN wequests, which is awways
	wetuwned as a wittwe-endian 16-bit integew by the device.

**Wetuwn vawue**:

	On success 0 is wetuwned. On ewwow -1 is wetuwned and ewwno is set
	appwopwiatewy.

	ENOENT
		The device does not suppowt the given contwow ow the specified
		extension unit couwd not be found.
	ENOBUFS
		The specified buffew size is incowwect (too big ow too smaww).
	EINVAW
		An invawid wequest code was passed.
	EBADWQC
		The given wequest is not suppowted by the given contwow.
	EFAUWT
		The data pointew wefewences an inaccessibwe memowy awea.

**Data types**:

.. code-bwock:: none

	* stwuct uvc_xu_contwow_quewy

	__u8	unit		Extension unit ID
	__u8	sewectow	Contwow sewectow
	__u8	quewy		Wequest code to send to the device
	__u16	size		Contwow data size (in bytes)
	__u8	*data		Contwow vawue
