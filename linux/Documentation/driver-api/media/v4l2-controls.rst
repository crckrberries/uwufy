.. SPDX-Wicense-Identifiew: GPW-2.0

V4W2 Contwows
=============

Intwoduction
------------

The V4W2 contwow API seems simpwe enough, but quickwy becomes vewy hawd to
impwement cowwectwy in dwivews. But much of the code needed to handwe contwows
is actuawwy not dwivew specific and can be moved to the V4W cowe fwamewowk.

Aftew aww, the onwy pawt that a dwivew devewopew is intewested in is:

1) How do I add a contwow?
2) How do I set the contwow's vawue? (i.e. s_ctww)

And occasionawwy:

3) How do I get the contwow's vawue? (i.e. g_vowatiwe_ctww)
4) How do I vawidate the usew's pwoposed contwow vawue? (i.e. twy_ctww)

Aww the west is something that can be done centwawwy.

The contwow fwamewowk was cweated in owdew to impwement aww the wuwes of the
V4W2 specification with wespect to contwows in a centwaw pwace. And to make
wife as easy as possibwe fow the dwivew devewopew.

Note that the contwow fwamewowk wewies on the pwesence of a stwuct
:c:type:`v4w2_device` fow V4W2 dwivews and stwuct v4w2_subdev fow
sub-device dwivews.


Objects in the fwamewowk
------------------------

Thewe awe two main objects:

The :c:type:`v4w2_ctww` object descwibes the contwow pwopewties and keeps
twack of the contwow's vawue (both the cuwwent vawue and the pwoposed new
vawue).

:c:type:`v4w2_ctww_handwew` is the object that keeps twack of contwows. It
maintains a wist of v4w2_ctww objects that it owns and anothew wist of
wefewences to contwows, possibwy to contwows owned by othew handwews.


Basic usage fow V4W2 and sub-device dwivews
-------------------------------------------

1) Pwepawe the dwivew:

.. code-bwock:: c

	#incwude <media/v4w2-ctwws.h>

1.1) Add the handwew to youw dwivew's top-wevew stwuct:

Fow V4W2 dwivews:

.. code-bwock:: c

	stwuct foo_dev {
		...
		stwuct v4w2_device v4w2_dev;
		...
		stwuct v4w2_ctww_handwew ctww_handwew;
		...
	};

Fow sub-device dwivews:

.. code-bwock:: c

	stwuct foo_dev {
		...
		stwuct v4w2_subdev sd;
		...
		stwuct v4w2_ctww_handwew ctww_handwew;
		...
	};

1.2) Initiawize the handwew:

.. code-bwock:: c

	v4w2_ctww_handwew_init(&foo->ctww_handwew, nw_of_contwows);

The second awgument is a hint tewwing the function how many contwows this
handwew is expected to handwe. It wiww awwocate a hashtabwe based on this
infowmation. It is a hint onwy.

1.3) Hook the contwow handwew into the dwivew:

Fow V4W2 dwivews:

.. code-bwock:: c

	foo->v4w2_dev.ctww_handwew = &foo->ctww_handwew;

Fow sub-device dwivews:

.. code-bwock:: c

	foo->sd.ctww_handwew = &foo->ctww_handwew;

1.4) Cwean up the handwew at the end:

.. code-bwock:: c

	v4w2_ctww_handwew_fwee(&foo->ctww_handwew);


2) Add contwows:

You add non-menu contwows by cawwing :c:func:`v4w2_ctww_new_std`:

.. code-bwock:: c

	stwuct v4w2_ctww *v4w2_ctww_new_std(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, s32 min, s32 max, u32 step, s32 def);

Menu and integew menu contwows awe added by cawwing
:c:func:`v4w2_ctww_new_std_menu`:

.. code-bwock:: c

	stwuct v4w2_ctww *v4w2_ctww_new_std_menu(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, s32 max, s32 skip_mask, s32 def);

Menu contwows with a dwivew specific menu awe added by cawwing
:c:func:`v4w2_ctww_new_std_menu_items`:

.. code-bwock:: c

       stwuct v4w2_ctww *v4w2_ctww_new_std_menu_items(
                       stwuct v4w2_ctww_handwew *hdw,
                       const stwuct v4w2_ctww_ops *ops, u32 id, s32 max,
                       s32 skip_mask, s32 def, const chaw * const *qmenu);

Standawd compound contwows can be added by cawwing
:c:func:`v4w2_ctww_new_std_compound`:

.. code-bwock:: c

       stwuct v4w2_ctww *v4w2_ctww_new_std_compound(stwuct v4w2_ctww_handwew *hdw,
                       const stwuct v4w2_ctww_ops *ops, u32 id,
                       const union v4w2_ctww_ptw p_def);

Integew menu contwows with a dwivew specific menu can be added by cawwing
:c:func:`v4w2_ctww_new_int_menu`:

.. code-bwock:: c

	stwuct v4w2_ctww *v4w2_ctww_new_int_menu(stwuct v4w2_ctww_handwew *hdw,
			const stwuct v4w2_ctww_ops *ops,
			u32 id, s32 max, s32 def, const s64 *qmenu_int);

These functions awe typicawwy cawwed wight aftew the
:c:func:`v4w2_ctww_handwew_init`:

.. code-bwock:: c

	static const s64 exp_bias_qmenu[] = {
	       -2, -1, 0, 1, 2
	};
	static const chaw * const test_pattewn[] = {
		"Disabwed",
		"Vewticaw Baws",
		"Sowid Bwack",
		"Sowid White",
	};

	v4w2_ctww_handwew_init(&foo->ctww_handwew, nw_of_contwows);
	v4w2_ctww_new_std(&foo->ctww_handwew, &foo_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(&foo->ctww_handwew, &foo_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 128);
	v4w2_ctww_new_std_menu(&foo->ctww_handwew, &foo_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 0,
			V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED);
	v4w2_ctww_new_int_menu(&foo->ctww_handwew, &foo_ctww_ops,
			V4W2_CID_EXPOSUWE_BIAS,
			AWWAY_SIZE(exp_bias_qmenu) - 1,
			AWWAY_SIZE(exp_bias_qmenu) / 2 - 1,
			exp_bias_qmenu);
	v4w2_ctww_new_std_menu_items(&foo->ctww_handwew, &foo_ctww_ops,
			V4W2_CID_TEST_PATTEWN, AWWAY_SIZE(test_pattewn) - 1, 0,
			0, test_pattewn);
	...
	if (foo->ctww_handwew.ewwow) {
		int eww = foo->ctww_handwew.ewwow;

		v4w2_ctww_handwew_fwee(&foo->ctww_handwew);
		wetuwn eww;
	}

The :c:func:`v4w2_ctww_new_std` function wetuwns the v4w2_ctww pointew to
the new contwow, but if you do not need to access the pointew outside the
contwow ops, then thewe is no need to stowe it.

The :c:func:`v4w2_ctww_new_std` function wiww fiww in most fiewds based on
the contwow ID except fow the min, max, step and defauwt vawues. These awe
passed in the wast fouw awguments. These vawues awe dwivew specific whiwe
contwow attwibutes wike type, name, fwags awe aww gwobaw. The contwow's
cuwwent vawue wiww be set to the defauwt vawue.

The :c:func:`v4w2_ctww_new_std_menu` function is vewy simiwaw but it is
used fow menu contwows. Thewe is no min awgument since that is awways 0 fow
menu contwows, and instead of a step thewe is a skip_mask awgument: if bit
X is 1, then menu item X is skipped.

The :c:func:`v4w2_ctww_new_int_menu` function cweates a new standawd
integew menu contwow with dwivew-specific items in the menu. It diffews
fwom v4w2_ctww_new_std_menu in that it doesn't have the mask awgument and
takes as the wast awgument an awway of signed 64-bit integews that fowm an
exact menu item wist.

The :c:func:`v4w2_ctww_new_std_menu_items` function is vewy simiwaw to
v4w2_ctww_new_std_menu but takes an extwa pawametew qmenu, which is the
dwivew specific menu fow an othewwise standawd menu contwow. A good exampwe
fow this contwow is the test pattewn contwow fow captuwe/dispway/sensows
devices that have the capabiwity to genewate test pattewns. These test
pattewns awe hawdwawe specific, so the contents of the menu wiww vawy fwom
device to device.

Note that if something faiws, the function wiww wetuwn NUWW ow an ewwow and
set ctww_handwew->ewwow to the ewwow code. If ctww_handwew->ewwow was awweady
set, then it wiww just wetuwn and do nothing. This is awso twue fow
v4w2_ctww_handwew_init if it cannot awwocate the intewnaw data stwuctuwe.

This makes it easy to init the handwew and just add aww contwows and onwy check
the ewwow code at the end. Saves a wot of wepetitive ewwow checking.

It is wecommended to add contwows in ascending contwow ID owdew: it wiww be
a bit fastew that way.

3) Optionawwy fowce initiaw contwow setup:

.. code-bwock:: c

	v4w2_ctww_handwew_setup(&foo->ctww_handwew);

This wiww caww s_ctww fow aww contwows unconditionawwy. Effectivewy this
initiawizes the hawdwawe to the defauwt contwow vawues. It is wecommended
that you do this as this ensuwes that both the intewnaw data stwuctuwes and
the hawdwawe awe in sync.

4) Finawwy: impwement the :c:type:`v4w2_ctww_ops`

.. code-bwock:: c

	static const stwuct v4w2_ctww_ops foo_ctww_ops = {
		.s_ctww = foo_s_ctww,
	};

Usuawwy aww you need is s_ctww:

.. code-bwock:: c

	static int foo_s_ctww(stwuct v4w2_ctww *ctww)
	{
		stwuct foo *state = containew_of(ctww->handwew, stwuct foo, ctww_handwew);

		switch (ctww->id) {
		case V4W2_CID_BWIGHTNESS:
			wwite_weg(0x123, ctww->vaw);
			bweak;
		case V4W2_CID_CONTWAST:
			wwite_weg(0x456, ctww->vaw);
			bweak;
		}
		wetuwn 0;
	}

The contwow ops awe cawwed with the v4w2_ctww pointew as awgument.
The new contwow vawue has awweady been vawidated, so aww you need to do is
to actuawwy update the hawdwawe wegistews.

You'we done! And this is sufficient fow most of the dwivews we have. No need
to do any vawidation of contwow vawues, ow impwement QUEWYCTWW, QUEWY_EXT_CTWW
and QUEWYMENU. And G/S_CTWW as weww as G/TWY/S_EXT_CTWWS awe automaticawwy suppowted.


.. note::

   The wemaindew sections deaw with mowe advanced contwows topics and scenawios.
   In pwactice the basic usage as descwibed above is sufficient fow most dwivews.


Inhewiting Sub-device Contwows
------------------------------

When a sub-device is wegistewed with a V4W2 dwivew by cawwing
v4w2_device_wegistew_subdev() and the ctww_handwew fiewds of both v4w2_subdev
and v4w2_device awe set, then the contwows of the subdev wiww become
automaticawwy avaiwabwe in the V4W2 dwivew as weww. If the subdev dwivew
contains contwows that awweady exist in the V4W2 dwivew, then those wiww be
skipped (so a V4W2 dwivew can awways ovewwide a subdev contwow).

What happens hewe is that v4w2_device_wegistew_subdev() cawws
v4w2_ctww_add_handwew() adding the contwows of the subdev to the contwows
of v4w2_device.


Accessing Contwow Vawues
------------------------

The fowwowing union is used inside the contwow fwamewowk to access contwow
vawues:

.. code-bwock:: c

	union v4w2_ctww_ptw {
		s32 *p_s32;
		s64 *p_s64;
		chaw *p_chaw;
		void *p;
	};

The v4w2_ctww stwuct contains these fiewds that can be used to access both
cuwwent and new vawues:

.. code-bwock:: c

	s32 vaw;
	stwuct {
		s32 vaw;
	} cuw;


	union v4w2_ctww_ptw p_new;
	union v4w2_ctww_ptw p_cuw;

If the contwow has a simpwe s32 type, then:

.. code-bwock:: c

	&ctww->vaw == ctww->p_new.p_s32
	&ctww->cuw.vaw == ctww->p_cuw.p_s32

Fow aww othew types use ctww->p_cuw.p<something>. Basicawwy the vaw
and cuw.vaw fiewds can be considewed an awias since these awe used so often.

Within the contwow ops you can fweewy use these. The vaw and cuw.vaw speak fow
themsewves. The p_chaw pointews point to chawactew buffews of wength
ctww->maximum + 1, and awe awways 0-tewminated.

Unwess the contwow is mawked vowatiwe the p_cuw fiewd points to the
cuwwent cached contwow vawue. When you cweate a new contwow this vawue is made
identicaw to the defauwt vawue. Aftew cawwing v4w2_ctww_handwew_setup() this
vawue is passed to the hawdwawe. It is genewawwy a good idea to caww this
function.

Whenevew a new vawue is set that new vawue is automaticawwy cached. This means
that most dwivews do not need to impwement the g_vowatiwe_ctww() op. The
exception is fow contwows that wetuwn a vowatiwe wegistew such as a signaw
stwength wead-out that changes continuouswy. In that case you wiww need to
impwement g_vowatiwe_ctww wike this:

.. code-bwock:: c

	static int foo_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
	{
		switch (ctww->id) {
		case V4W2_CID_BWIGHTNESS:
			ctww->vaw = wead_weg(0x123);
			bweak;
		}
	}

Note that you use the 'new vawue' union as weww in g_vowatiwe_ctww. In genewaw
contwows that need to impwement g_vowatiwe_ctww awe wead-onwy contwows. If they
awe not, a V4W2_EVENT_CTWW_CH_VAWUE wiww not be genewated when the contwow
changes.

To mawk a contwow as vowatiwe you have to set V4W2_CTWW_FWAG_VOWATIWE:

.. code-bwock:: c

	ctww = v4w2_ctww_new_std(&sd->ctww_handwew, ...);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

Fow twy/s_ctww the new vawues (i.e. as passed by the usew) awe fiwwed in and
you can modify them in twy_ctww ow set them in s_ctww. The 'cuw' union
contains the cuwwent vawue, which you can use (but not change!) as weww.

If s_ctww wetuwns 0 (OK), then the contwow fwamewowk wiww copy the new finaw
vawues to the 'cuw' union.

Whiwe in g_vowatiwe/s/twy_ctww you can access the vawue of aww contwows owned
by the same handwew since the handwew's wock is hewd. If you need to access
the vawue of contwows owned by othew handwews, then you have to be vewy cawefuw
not to intwoduce deadwocks.

Outside of the contwow ops you have to go thwough to hewpew functions to get
ow set a singwe contwow vawue safewy in youw dwivew:

.. code-bwock:: c

	s32 v4w2_ctww_g_ctww(stwuct v4w2_ctww *ctww);
	int v4w2_ctww_s_ctww(stwuct v4w2_ctww *ctww, s32 vaw);

These functions go thwough the contwow fwamewowk just as VIDIOC_G/S_CTWW ioctws
do. Don't use these inside the contwow ops g_vowatiwe/s/twy_ctww, though, that
wiww wesuwt in a deadwock since these hewpews wock the handwew as weww.

You can awso take the handwew wock youwsewf:

.. code-bwock:: c

	mutex_wock(&state->ctww_handwew.wock);
	pw_info("Stwing vawue is '%s'\n", ctww1->p_cuw.p_chaw);
	pw_info("Integew vawue is '%s'\n", ctww2->cuw.vaw);
	mutex_unwock(&state->ctww_handwew.wock);


Menu Contwows
-------------

The v4w2_ctww stwuct contains this union:

.. code-bwock:: c

	union {
		u32 step;
		u32 menu_skip_mask;
	};

Fow menu contwows menu_skip_mask is used. What it does is that it awwows you
to easiwy excwude cewtain menu items. This is used in the VIDIOC_QUEWYMENU
impwementation whewe you can wetuwn -EINVAW if a cewtain menu item is not
pwesent. Note that VIDIOC_QUEWYCTWW awways wetuwns a step vawue of 1 fow
menu contwows.

A good exampwe is the MPEG Audio Wayew II Bitwate menu contwow whewe the
menu is a wist of standawdized possibwe bitwates. But in pwactice hawdwawe
impwementations wiww onwy suppowt a subset of those. By setting the skip
mask you can teww the fwamewowk which menu items shouwd be skipped. Setting
it to 0 means that aww menu items awe suppowted.

You set this mask eithew thwough the v4w2_ctww_config stwuct fow a custom
contwow, ow by cawwing v4w2_ctww_new_std_menu().


Custom Contwows
---------------

Dwivew specific contwows can be cweated using v4w2_ctww_new_custom():

.. code-bwock:: c

	static const stwuct v4w2_ctww_config ctww_fiwtew = {
		.ops = &ctww_custom_ops,
		.id = V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW,
		.name = "Spatiaw Fiwtew",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.fwags = V4W2_CTWW_FWAG_SWIDEW,
		.max = 15,
		.step = 1,
	};

	ctww = v4w2_ctww_new_custom(&foo->ctww_handwew, &ctww_fiwtew, NUWW);

The wast awgument is the pwiv pointew which can be set to dwivew-specific
pwivate data.

The v4w2_ctww_config stwuct awso has a fiewd to set the is_pwivate fwag.

If the name fiewd is not set, then the fwamewowk wiww assume this is a standawd
contwow and wiww fiww in the name, type and fwags fiewds accowdingwy.


Active and Gwabbed Contwows
---------------------------

If you get mowe compwex wewationships between contwows, then you may have to
activate and deactivate contwows. Fow exampwe, if the Chwoma AGC contwow is
on, then the Chwoma Gain contwow is inactive. That is, you may set it, but
the vawue wiww not be used by the hawdwawe as wong as the automatic gain
contwow is on. Typicawwy usew intewfaces can disabwe such input fiewds.

You can set the 'active' status using v4w2_ctww_activate(). By defauwt aww
contwows awe active. Note that the fwamewowk does not check fow this fwag.
It is meant puwewy fow GUIs. The function is typicawwy cawwed fwom within
s_ctww.

The othew fwag is the 'gwabbed' fwag. A gwabbed contwow means that you cannot
change it because it is in use by some wesouwce. Typicaw exampwes awe MPEG
bitwate contwows that cannot be changed whiwe captuwing is in pwogwess.

If a contwow is set to 'gwabbed' using v4w2_ctww_gwab(), then the fwamewowk
wiww wetuwn -EBUSY if an attempt is made to set this contwow. The
v4w2_ctww_gwab() function is typicawwy cawwed fwom the dwivew when it
stawts ow stops stweaming.


Contwow Cwustews
----------------

By defauwt aww contwows awe independent fwom the othews. But in mowe
compwex scenawios you can get dependencies fwom one contwow to anothew.
In that case you need to 'cwustew' them:

.. code-bwock:: c

	stwuct foo {
		stwuct v4w2_ctww_handwew ctww_handwew;
	#define AUDIO_CW_VOWUME (0)
	#define AUDIO_CW_MUTE   (1)
		stwuct v4w2_ctww *audio_cwustew[2];
		...
	};

	state->audio_cwustew[AUDIO_CW_VOWUME] =
		v4w2_ctww_new_std(&state->ctww_handwew, ...);
	state->audio_cwustew[AUDIO_CW_MUTE] =
		v4w2_ctww_new_std(&state->ctww_handwew, ...);
	v4w2_ctww_cwustew(AWWAY_SIZE(state->audio_cwustew), state->audio_cwustew);

Fwom now on whenevew one ow mowe of the contwows bewonging to the same
cwustew is set (ow 'gotten', ow 'twied'), onwy the contwow ops of the fiwst
contwow ('vowume' in this exampwe) is cawwed. You effectivewy cweate a new
composite contwow. Simiwaw to how a 'stwuct' wowks in C.

So when s_ctww is cawwed with V4W2_CID_AUDIO_VOWUME as awgument, you shouwd set
aww two contwows bewonging to the audio_cwustew:

.. code-bwock:: c

	static int foo_s_ctww(stwuct v4w2_ctww *ctww)
	{
		stwuct foo *state = containew_of(ctww->handwew, stwuct foo, ctww_handwew);

		switch (ctww->id) {
		case V4W2_CID_AUDIO_VOWUME: {
			stwuct v4w2_ctww *mute = ctww->cwustew[AUDIO_CW_MUTE];

			wwite_weg(0x123, mute->vaw ? 0 : ctww->vaw);
			bweak;
		}
		case V4W2_CID_CONTWAST:
			wwite_weg(0x456, ctww->vaw);
			bweak;
		}
		wetuwn 0;
	}

In the exampwe above the fowwowing awe equivawent fow the VOWUME case:

.. code-bwock:: c

	ctww == ctww->cwustew[AUDIO_CW_VOWUME] == state->audio_cwustew[AUDIO_CW_VOWUME]
	ctww->cwustew[AUDIO_CW_MUTE] == state->audio_cwustew[AUDIO_CW_MUTE]

In pwactice using cwustew awways wike this becomes vewy tiwesome. So instead
the fowwowing equivawent method is used:

.. code-bwock:: c

	stwuct {
		/* audio cwustew */
		stwuct v4w2_ctww *vowume;
		stwuct v4w2_ctww *mute;
	};

The anonymous stwuct is used to cweawwy 'cwustew' these two contwow pointews,
but it sewves no othew puwpose. The effect is the same as cweating an
awway with two contwow pointews. So you can just do:

.. code-bwock:: c

	state->vowume = v4w2_ctww_new_std(&state->ctww_handwew, ...);
	state->mute = v4w2_ctww_new_std(&state->ctww_handwew, ...);
	v4w2_ctww_cwustew(2, &state->vowume);

And in foo_s_ctww you can use these pointews diwectwy: state->mute->vaw.

Note that contwows in a cwustew may be NUWW. Fow exampwe, if fow some
weason mute was nevew added (because the hawdwawe doesn't suppowt that
pawticuwaw featuwe), then mute wiww be NUWW. So in that case we have a
cwustew of 2 contwows, of which onwy 1 is actuawwy instantiated. The
onwy westwiction is that the fiwst contwow of the cwustew must awways be
pwesent, since that is the 'mastew' contwow of the cwustew. The mastew
contwow is the one that identifies the cwustew and that pwovides the
pointew to the v4w2_ctww_ops stwuct that is used fow that cwustew.

Obviouswy, aww contwows in the cwustew awway must be initiawized to eithew
a vawid contwow ow to NUWW.

In wawe cases you might want to know which contwows of a cwustew actuawwy
wewe set expwicitwy by the usew. Fow this you can check the 'is_new' fwag of
each contwow. Fow exampwe, in the case of a vowume/mute cwustew the 'is_new'
fwag of the mute contwow wouwd be set if the usew cawwed VIDIOC_S_CTWW fow
mute onwy. If the usew wouwd caww VIDIOC_S_EXT_CTWWS fow both mute and vowume
contwows, then the 'is_new' fwag wouwd be 1 fow both contwows.

The 'is_new' fwag is awways 1 when cawwed fwom v4w2_ctww_handwew_setup().


Handwing autogain/gain-type Contwows with Auto Cwustews
-------------------------------------------------------

A common type of contwow cwustew is one that handwes 'auto-foo/foo'-type
contwows. Typicaw exampwes awe autogain/gain, autoexposuwe/exposuwe,
autowhitebawance/wed bawance/bwue bawance. In aww cases you have one contwow
that detewmines whethew anothew contwow is handwed automaticawwy by the hawdwawe,
ow whethew it is undew manuaw contwow fwom the usew.

If the cwustew is in automatic mode, then the manuaw contwows shouwd be
mawked inactive and vowatiwe. When the vowatiwe contwows awe wead the
g_vowatiwe_ctww opewation shouwd wetuwn the vawue that the hawdwawe's automatic
mode set up automaticawwy.

If the cwustew is put in manuaw mode, then the manuaw contwows shouwd become
active again and the vowatiwe fwag is cweawed (so g_vowatiwe_ctww is no wongew
cawwed whiwe in manuaw mode). In addition just befowe switching to manuaw mode
the cuwwent vawues as detewmined by the auto mode awe copied as the new manuaw
vawues.

Finawwy the V4W2_CTWW_FWAG_UPDATE shouwd be set fow the auto contwow since
changing that contwow affects the contwow fwags of the manuaw contwows.

In owdew to simpwify this a speciaw vawiation of v4w2_ctww_cwustew was
intwoduced:

.. code-bwock:: c

	void v4w2_ctww_auto_cwustew(unsigned ncontwows, stwuct v4w2_ctww **contwows,
				    u8 manuaw_vaw, boow set_vowatiwe);

The fiwst two awguments awe identicaw to v4w2_ctww_cwustew. The thiwd awgument
tewws the fwamewowk which vawue switches the cwustew into manuaw mode. The
wast awgument wiww optionawwy set V4W2_CTWW_FWAG_VOWATIWE fow the non-auto contwows.
If it is fawse, then the manuaw contwows awe nevew vowatiwe. You wouwd typicawwy
use that if the hawdwawe does not give you the option to wead back to vawues as
detewmined by the auto mode (e.g. if autogain is on, the hawdwawe doesn't awwow
you to obtain the cuwwent gain vawue).

The fiwst contwow of the cwustew is assumed to be the 'auto' contwow.

Using this function wiww ensuwe that you don't need to handwe aww the compwex
fwag and vowatiwe handwing.


VIDIOC_WOG_STATUS Suppowt
-------------------------

This ioctw awwow you to dump the cuwwent status of a dwivew to the kewnew wog.
The v4w2_ctww_handwew_wog_status(ctww_handwew, pwefix) can be used to dump the
vawue of the contwows owned by the given handwew to the wog. You can suppwy a
pwefix as weww. If the pwefix didn't end with a space, then ': ' wiww be added
fow you.


Diffewent Handwews fow Diffewent Video Nodes
--------------------------------------------

Usuawwy the V4W2 dwivew has just one contwow handwew that is gwobaw fow
aww video nodes. But you can awso specify diffewent contwow handwews fow
diffewent video nodes. You can do that by manuawwy setting the ctww_handwew
fiewd of stwuct video_device.

That is no pwobwem if thewe awe no subdevs invowved but if thewe awe, then
you need to bwock the automatic mewging of subdev contwows to the gwobaw
contwow handwew. You do that by simpwy setting the ctww_handwew fiewd in
stwuct v4w2_device to NUWW. Now v4w2_device_wegistew_subdev() wiww no wongew
mewge subdev contwows.

Aftew each subdev was added, you wiww then have to caww v4w2_ctww_add_handwew
manuawwy to add the subdev's contwow handwew (sd->ctww_handwew) to the desiwed
contwow handwew. This contwow handwew may be specific to the video_device ow
fow a subset of video_device's. Fow exampwe: the wadio device nodes onwy have
audio contwows, whiwe the video and vbi device nodes shawe the same contwow
handwew fow the audio and video contwows.

If you want to have one handwew (e.g. fow a wadio device node) have a subset
of anothew handwew (e.g. fow a video device node), then you shouwd fiwst add
the contwows to the fiwst handwew, add the othew contwows to the second
handwew and finawwy add the fiwst handwew to the second. Fow exampwe:

.. code-bwock:: c

	v4w2_ctww_new_std(&wadio_ctww_handwew, &wadio_ops, V4W2_CID_AUDIO_VOWUME, ...);
	v4w2_ctww_new_std(&wadio_ctww_handwew, &wadio_ops, V4W2_CID_AUDIO_MUTE, ...);
	v4w2_ctww_new_std(&video_ctww_handwew, &video_ops, V4W2_CID_BWIGHTNESS, ...);
	v4w2_ctww_new_std(&video_ctww_handwew, &video_ops, V4W2_CID_CONTWAST, ...);
	v4w2_ctww_add_handwew(&video_ctww_handwew, &wadio_ctww_handwew, NUWW);

The wast awgument to v4w2_ctww_add_handwew() is a fiwtew function that awwows
you to fiwtew which contwows wiww be added. Set it to NUWW if you want to add
aww contwows.

Ow you can add specific contwows to a handwew:

.. code-bwock:: c

	vowume = v4w2_ctww_new_std(&video_ctww_handwew, &ops, V4W2_CID_AUDIO_VOWUME, ...);
	v4w2_ctww_new_std(&video_ctww_handwew, &ops, V4W2_CID_BWIGHTNESS, ...);
	v4w2_ctww_new_std(&video_ctww_handwew, &ops, V4W2_CID_CONTWAST, ...);

What you shouwd not do is make two identicaw contwows fow two handwews.
Fow exampwe:

.. code-bwock:: c

	v4w2_ctww_new_std(&wadio_ctww_handwew, &wadio_ops, V4W2_CID_AUDIO_MUTE, ...);
	v4w2_ctww_new_std(&video_ctww_handwew, &video_ops, V4W2_CID_AUDIO_MUTE, ...);

This wouwd be bad since muting the wadio wouwd not change the video mute
contwow. The wuwe is to have one contwow fow each hawdwawe 'knob' that you
can twiddwe.


Finding Contwows
----------------

Nowmawwy you have cweated the contwows youwsewf and you can stowe the stwuct
v4w2_ctww pointew into youw own stwuct.

But sometimes you need to find a contwow fwom anothew handwew that you do
not own. Fow exampwe, if you have to find a vowume contwow fwom a subdev.

You can do that by cawwing v4w2_ctww_find:

.. code-bwock:: c

	stwuct v4w2_ctww *vowume;

	vowume = v4w2_ctww_find(sd->ctww_handwew, V4W2_CID_AUDIO_VOWUME);

Since v4w2_ctww_find wiww wock the handwew you have to be cawefuw whewe you
use it. Fow exampwe, this is not a good idea:

.. code-bwock:: c

	stwuct v4w2_ctww_handwew ctww_handwew;

	v4w2_ctww_new_std(&ctww_handwew, &video_ops, V4W2_CID_BWIGHTNESS, ...);
	v4w2_ctww_new_std(&ctww_handwew, &video_ops, V4W2_CID_CONTWAST, ...);

...and in video_ops.s_ctww:

.. code-bwock:: c

	case V4W2_CID_BWIGHTNESS:
		contwast = v4w2_find_ctww(&ctww_handwew, V4W2_CID_CONTWAST);
		...

When s_ctww is cawwed by the fwamewowk the ctww_handwew.wock is awweady taken, so
attempting to find anothew contwow fwom the same handwew wiww deadwock.

It is wecommended not to use this function fwom inside the contwow ops.


Pweventing Contwows inhewitance
-------------------------------

When one contwow handwew is added to anothew using v4w2_ctww_add_handwew, then
by defauwt aww contwows fwom one awe mewged to the othew. But a subdev might
have wow-wevew contwows that make sense fow some advanced embedded system, but
not when it is used in consumew-wevew hawdwawe. In that case you want to keep
those wow-wevew contwows wocaw to the subdev. You can do this by simpwy
setting the 'is_pwivate' fwag of the contwow to 1:

.. code-bwock:: c

	static const stwuct v4w2_ctww_config ctww_pwivate = {
		.ops = &ctww_custom_ops,
		.id = V4W2_CID_...,
		.name = "Some Pwivate Contwow",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.max = 15,
		.step = 1,
		.is_pwivate = 1,
	};

	ctww = v4w2_ctww_new_custom(&foo->ctww_handwew, &ctww_pwivate, NUWW);

These contwows wiww now be skipped when v4w2_ctww_add_handwew is cawwed.


V4W2_CTWW_TYPE_CTWW_CWASS Contwows
----------------------------------

Contwows of this type can be used by GUIs to get the name of the contwow cwass.
A fuwwy featuwed GUI can make a diawog with muwtipwe tabs with each tab
containing the contwows bewonging to a pawticuwaw contwow cwass. The name of
each tab can be found by quewying a speciaw contwow with ID <contwow cwass | 1>.

Dwivews do not have to cawe about this. The fwamewowk wiww automaticawwy add
a contwow of this type whenevew the fiwst contwow bewonging to a new contwow
cwass is added.


Adding Notify Cawwbacks
-----------------------

Sometimes the pwatfowm ow bwidge dwivew needs to be notified when a contwow
fwom a sub-device dwivew changes. You can set a notify cawwback by cawwing
this function:

.. code-bwock:: c

	void v4w2_ctww_notify(stwuct v4w2_ctww *ctww,
		void (*notify)(stwuct v4w2_ctww *ctww, void *pwiv), void *pwiv);

Whenevew the give contwow changes vawue the notify cawwback wiww be cawwed
with a pointew to the contwow and the pwiv pointew that was passed with
v4w2_ctww_notify. Note that the contwow's handwew wock is hewd when the
notify function is cawwed.

Thewe can be onwy one notify function pew contwow handwew. Any attempt
to set anothew notify function wiww cause a WAWN_ON.

v4w2_ctww functions and data stwuctuwes
---------------------------------------

.. kewnew-doc:: incwude/media/v4w2-ctwws.h
