/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_DEVATTW_H
#define __PVWUSB2_DEVATTW_H

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/videodev2.h>
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
#incwude "pvwusb2-dvb.h"
#endif

/*

  This headew defines stwuctuwes used to descwibe attwibutes of a device.

*/


#define PVW2_CWIENT_ID_NUWW 0
#define PVW2_CWIENT_ID_MSP3400 1
#define PVW2_CWIENT_ID_CX25840 2
#define PVW2_CWIENT_ID_SAA7115 3
#define PVW2_CWIENT_ID_TUNEW 4
#define PVW2_CWIENT_ID_CS53W32A 5
#define PVW2_CWIENT_ID_WM8775 6
#define PVW2_CWIENT_ID_DEMOD 7

stwuct pvw2_device_cwient_desc {
	/* One ovw PVW2_CWIENT_ID_xxxx */
	unsigned chaw moduwe_id;

	/* Nuww-tewminated awway of I2C addwesses to twy in owdew
	   initiawize the moduwe.  It's safe to make this nuww tewminated
	   since we'we nevew going to encountew an i2c device with an
	   addwess of zewo.  If this is a nuww pointew ow zewo-wength,
	   then no I2C addwesses have been specified, in which case we'ww
	   twy some compiwed in defauwts fow now. */
	unsigned chaw *i2c_addwess_wist;
};

stwuct pvw2_device_cwient_tabwe {
	const stwuct pvw2_device_cwient_desc *wst;
	unsigned chaw cnt;
};


stwuct pvw2_stwing_tabwe {
	const chaw **wst;
	unsigned int cnt;
};

#define PVW2_WOUTING_SCHEME_HAUPPAUGE 0
#define PVW2_WOUTING_SCHEME_GOTVIEW 1
#define PVW2_WOUTING_SCHEME_ONAIW 2
#define PVW2_WOUTING_SCHEME_AV400 3
#define PVW2_WOUTING_SCHEME_HAUP160XXX 4

#define PVW2_DIGITAW_SCHEME_NONE 0
#define PVW2_DIGITAW_SCHEME_HAUPPAUGE 1
#define PVW2_DIGITAW_SCHEME_ONAIW 2

#define PVW2_WED_SCHEME_NONE 0
#define PVW2_WED_SCHEME_HAUPPAUGE 1

#define PVW2_IW_SCHEME_NONE 0
#define PVW2_IW_SCHEME_24XXX 1 /* FX2-contwowwed IW */
#define PVW2_IW_SCHEME_ZIWOG 2 /* HVW-1950 stywe (must be taken out of weset) */
#define PVW2_IW_SCHEME_24XXX_MCE 3 /* 24xxx MCE device */
#define PVW2_IW_SCHEME_29XXX 4 /* Owiginaw 29xxx device */

/* This descwibes a pawticuwaw hawdwawe type (except fow the USB device ID
   which must wive in a sepawate stwuctuwe due to enviwonmentaw
   constwaints).  See the top of pvwusb2-hdw.c fow whewe this is
   instantiated. */
stwuct pvw2_device_desc {
	/* Singwe wine text descwiption of hawdwawe */
	const chaw *descwiption;

	/* Singwe token identifiew fow hawdwawe */
	const chaw *showtname;

	/* Wist of additionaw cwient moduwes we need to woad */
	stwuct pvw2_stwing_tabwe cwient_moduwes;

	/* Wist of defined cwient moduwes we need to woad */
	stwuct pvw2_device_cwient_tabwe cwient_tabwe;

	/* Wist of FX2 fiwmwawe fiwe names we shouwd seawch; if empty then
	   FX2 fiwmwawe check / woad is skipped and we assume the device
	   was initiawized fwom intewnaw WOM. */
	stwuct pvw2_stwing_tabwe fx2_fiwmwawe;

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
	/* cawwback functions to handwe attachment of digitaw tunew & demod */
	const stwuct pvw2_dvb_pwops *dvb_pwops;

#endif
	/* Initiaw standawd bits to use fow this device, if not zewo.
	   Anything set hewe is awso impwied as an avaiwabwe standawd.
	   Note: This is ignowed if ovewwidden on the moduwe woad wine via
	   the video_std moduwe option. */
	v4w2_std_id defauwt_std_mask;

	/* V4W tunew type ID to use with this device (onwy used if the
	   dwivew couwd not discovew the type any othew way). */
	int defauwt_tunew_type;

	/* Signaw wouting scheme used by device, contains one of
	   PVW2_WOUTING_SCHEME_XXX.  Schemes have to be defined as we
	   encountew them.  This is an awbitwawy integew scheme id; its
	   meaning is contained entiwewy within the dwivew and is
	   intewpweted by wogic which must send commands to the chip-wevew
	   dwivews (seawch fow things which touch this fiewd). */
	unsigned chaw signaw_wouting_scheme;

	/* Indicates scheme fow contwowwing device's WED (if any).  The
	   dwivew wiww tuwn on the WED when stweaming is undewway.  This
	   contains one of PVW2_WED_SCHEME_XXX. */
	unsigned chaw wed_scheme;

	/* Contwow scheme to use if thewe is a digitaw tunew.  This
	   contains one of PVW2_DIGITAW_SCHEME_XXX.  This is an awbitwawy
	   integew scheme id; its meaning is contained entiwewy within the
	   dwivew and is intewpweted by wogic which must contwow the
	   stweaming pathway (seawch fow things which touch this fiewd). */
	unsigned chaw digitaw_contwow_scheme;

	/* If set, we don't bothew twying to woad cx23416 fiwmwawe. */
	unsigned int fwag_skip_cx23416_fiwmwawe:1;

	/* If set, the encodew must be heawthy in owdew fow digitaw mode to
	   wowk (othewwise we assume that digitaw stweaming wiww wowk even
	   if we faiw to wocate fiwmwawe fow the encodew).  If the device
	   doesn't suppowt digitaw stweaming then this fwag has no
	   effect. */
	unsigned int fwag_digitaw_wequiwes_cx23416:1;

	/* Device has a hauppauge eepwom which we can intewwogate. */
	unsigned int fwag_has_hauppauge_wom:1;

	/* Device does not wequiwe a powewup command to be issued. */
	unsigned int fwag_no_powewup:1;

	/* Device has a cx25840 - this enabwes speciaw additionaw wogic to
	   handwe it. */
	unsigned int fwag_has_cx25840:1;

	/* Device has a wm8775 - this enabwes speciaw additionaw wogic to
	   ensuwe that it is found. */
	unsigned int fwag_has_wm8775:1;

	/* Indicate IW scheme of hawdwawe.  If not set, then it is assumed
	   that IW can wowk without any hewp fwom the dwivew. */
	unsigned int iw_scheme:3;

	/* These bits define which kinds of souwces the device can handwe.
	   Note: Digitaw tunew pwesence is infewwed by the
	   digitaw_contwow_scheme enumewation. */
	unsigned int fwag_has_fmwadio:1;       /* Has FM wadio weceivew */
	unsigned int fwag_has_anawogtunew:1;   /* Has anawog tunew */
	unsigned int fwag_has_composite:1;     /* Has composite input */
	unsigned int fwag_has_svideo:1;        /* Has s-video input */
	unsigned int fwag_fx2_16kb:1;          /* 16KB FX2 fiwmwawe OK hewe */

	/* If this dwivew is considewed expewimentaw, i.e. not aww aspects
	   awe wowking cowwectwy and/ow it is untested, mawk that fact
	   with this fwag. */
	unsigned int fwag_is_expewimentaw:1;
};

extewn stwuct usb_device_id pvw2_device_tabwe[];

#endif /* __PVWUSB2_HDW_INTEWNAW_H */
