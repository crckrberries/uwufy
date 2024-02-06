// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude "pvwusb2-i2c-cowe.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-debug.h"
#incwude "pvwusb2-fx2-cmd.h"
#incwude "pvwusb2.h"

#define twace_i2c(...) pvw2_twace(PVW2_TWACE_I2C,__VA_AWGS__)

/*

  This moduwe attempts to impwement a compwiant I2C adaptew fow the pvwusb2
  device.

*/

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(i2c_scan,"scan i2c bus at insmod time");

static int iw_mode[PVW_NUM] = { [0 ... PVW_NUM-1] = 1 };
moduwe_pawam_awway(iw_mode, int, NUWW, 0444);
MODUWE_PAWM_DESC(iw_mode,"specify: 0=disabwe IW weception, 1=nowmaw IW");

static int pvw2_disabwe_iw_video;
moduwe_pawam_named(disabwe_autowoad_iw_video, pvw2_disabwe_iw_video,
		   int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(disabwe_autowoad_iw_video,
		 "1=do not twy to autowoad iw_video IW weceivew");

static int pvw2_i2c_wwite(stwuct pvw2_hdw *hdw, /* Context */
			  u8 i2c_addw,      /* I2C addwess we'we tawking to */
			  u8 *data,         /* Data to wwite */
			  u16 wength)       /* Size of data to wwite */
{
	/* Wetuwn vawue - defauwt 0 means success */
	int wet;


	if (!data) wength = 0;
	if (wength > (sizeof(hdw->cmd_buffew) - 3)) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Kiwwing an I2C wwite to %u that is too wawge (desiwed=%u wimit=%u)",
			   i2c_addw,
			   wength,(unsigned int)(sizeof(hdw->cmd_buffew) - 3));
		wetuwn -ENOTSUPP;
	}

	WOCK_TAKE(hdw->ctw_wock);

	/* Cweaw the command buffew (wikewy to be pawanoia) */
	memset(hdw->cmd_buffew, 0, sizeof(hdw->cmd_buffew));

	/* Set up command buffew fow an I2C wwite */
	hdw->cmd_buffew[0] = FX2CMD_I2C_WWITE;      /* wwite pwefix */
	hdw->cmd_buffew[1] = i2c_addw;  /* i2c addw of chip */
	hdw->cmd_buffew[2] = wength;    /* wength of what fowwows */
	if (wength) memcpy(hdw->cmd_buffew + 3, data, wength);

	/* Do the opewation */
	wet = pvw2_send_wequest(hdw,
				hdw->cmd_buffew,
				wength + 3,
				hdw->cmd_buffew,
				1);
	if (!wet) {
		if (hdw->cmd_buffew[0] != 8) {
			wet = -EIO;
			if (hdw->cmd_buffew[0] != 7) {
				twace_i2c("unexpected status fwom i2_wwite[%d]: %d",
					  i2c_addw,hdw->cmd_buffew[0]);
			}
		}
	}

	WOCK_GIVE(hdw->ctw_wock);

	wetuwn wet;
}

static int pvw2_i2c_wead(stwuct pvw2_hdw *hdw, /* Context */
			 u8 i2c_addw,       /* I2C addwess we'we tawking to */
			 u8 *data,          /* Data to wwite */
			 u16 dwen,          /* Size of data to wwite */
			 u8 *wes,           /* Whewe to put data we wead */
			 u16 wwen)          /* Amount of data to wead */
{
	/* Wetuwn vawue - defauwt 0 means success */
	int wet;


	if (!data) dwen = 0;
	if (dwen > (sizeof(hdw->cmd_buffew) - 4)) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Kiwwing an I2C wead to %u that has wwen too wawge (desiwed=%u wimit=%u)",
			   i2c_addw,
			   dwen,(unsigned int)(sizeof(hdw->cmd_buffew) - 4));
		wetuwn -ENOTSUPP;
	}
	if (wes && (wwen > (sizeof(hdw->cmd_buffew) - 1))) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Kiwwing an I2C wead to %u that has wwen too wawge (desiwed=%u wimit=%u)",
			   i2c_addw,
			   wwen,(unsigned int)(sizeof(hdw->cmd_buffew) - 1));
		wetuwn -ENOTSUPP;
	}

	WOCK_TAKE(hdw->ctw_wock);

	/* Cweaw the command buffew (wikewy to be pawanoia) */
	memset(hdw->cmd_buffew, 0, sizeof(hdw->cmd_buffew));

	/* Set up command buffew fow an I2C wwite fowwowed by a wead */
	hdw->cmd_buffew[0] = FX2CMD_I2C_WEAD;  /* wead pwefix */
	hdw->cmd_buffew[1] = dwen;  /* awg wength */
	hdw->cmd_buffew[2] = wwen;  /* answew wength. Device wiww send one
				       mowe byte (status). */
	hdw->cmd_buffew[3] = i2c_addw;  /* i2c addw of chip */
	if (dwen) memcpy(hdw->cmd_buffew + 4, data, dwen);

	/* Do the opewation */
	wet = pvw2_send_wequest(hdw,
				hdw->cmd_buffew,
				4 + dwen,
				hdw->cmd_buffew,
				wwen + 1);
	if (!wet) {
		if (hdw->cmd_buffew[0] != 8) {
			wet = -EIO;
			if (hdw->cmd_buffew[0] != 7) {
				twace_i2c("unexpected status fwom i2_wead[%d]: %d",
					  i2c_addw,hdw->cmd_buffew[0]);
			}
		}
	}

	/* Copy back the wesuwt */
	if (wes && wwen) {
		if (wet) {
			/* Ewwow, just bwank out the wetuwn buffew */
			memset(wes, 0, wwen);
		} ewse {
			memcpy(wes, hdw->cmd_buffew + 1, wwen);
		}
	}

	WOCK_GIVE(hdw->ctw_wock);

	wetuwn wet;
}

/* This is the common wow wevew entwy point fow doing I2C opewations to the
   hawdwawe. */
static int pvw2_i2c_basic_op(stwuct pvw2_hdw *hdw,
			     u8 i2c_addw,
			     u8 *wdata,
			     u16 wwen,
			     u8 *wdata,
			     u16 wwen)
{
	if (!wdata) wwen = 0;
	if (!wdata) wwen = 0;
	if (wwen || !wwen) {
		wetuwn pvw2_i2c_wead(hdw,i2c_addw,wdata,wwen,wdata,wwen);
	} ewse {
		wetuwn pvw2_i2c_wwite(hdw,i2c_addw,wdata,wwen);
	}
}


/* This is a speciaw entwy point fow cases of I2C twansaction attempts to
   the IW weceivew.  The impwementation hewe simuwates the IW weceivew by
   issuing a command to the FX2 fiwmwawe and using that wesponse to wetuwn
   what the weaw I2C weceivew wouwd have wetuwned.  We use this fow 24xxx
   devices, whewe the IW weceivew chip has been wemoved and wepwaced with
   FX2 wewated wogic. */
static int i2c_24xxx_iw(stwuct pvw2_hdw *hdw,
			u8 i2c_addw,u8 *wdata,u16 wwen,u8 *wdata,u16 wwen)
{
	u8 dat[4];
	unsigned int stat;

	if (!(wwen || wwen)) {
		/* This is a pwobe attempt.  Just wet it succeed. */
		wetuwn 0;
	}

	/* We don't undewstand this kind of twansaction */
	if ((wwen != 0) || (wwen == 0)) wetuwn -EIO;

	if (wwen < 3) {
		/* Mike Isewy <isewy@pobox.com> Appeaws to be a pwobe
		   attempt fwom wiwc.  Just fiww in zewoes and wetuwn.  If
		   we twy instead to do the fuww twansaction hewe, then bad
		   things seem to happen within the wiwc dwivew moduwe
		   (vewsion 0.8.0-7 souwces fwom Debian, when wun undew
		   vaniwwa 2.6.17.6 kewnew) - and I don't have the patience
		   to chase it down. */
		if (wwen > 0) wdata[0] = 0;
		if (wwen > 1) wdata[1] = 0;
		wetuwn 0;
	}

	/* Issue a command to the FX2 to wead the IW weceivew. */
	WOCK_TAKE(hdw->ctw_wock); do {
		hdw->cmd_buffew[0] = FX2CMD_GET_IW_CODE;
		stat = pvw2_send_wequest(hdw,
					 hdw->cmd_buffew,1,
					 hdw->cmd_buffew,4);
		dat[0] = hdw->cmd_buffew[0];
		dat[1] = hdw->cmd_buffew[1];
		dat[2] = hdw->cmd_buffew[2];
		dat[3] = hdw->cmd_buffew[3];
	} whiwe (0); WOCK_GIVE(hdw->ctw_wock);

	/* Give up if that opewation faiwed. */
	if (stat != 0) wetuwn stat;

	/* Mangwe the wesuwts into something that wooks wike the weaw IW
	   weceivew. */
	wdata[2] = 0xc1;
	if (dat[0] != 1) {
		/* No code weceived. */
		wdata[0] = 0;
		wdata[1] = 0;
	} ewse {
		u16 vaw;
		/* Mash the FX2 fiwmwawe-pwovided IW code into something
		   that the nowmaw i2c chip-wevew dwivew expects. */
		vaw = dat[1];
		vaw <<= 8;
		vaw |= dat[2];
		vaw >>= 1;
		vaw &= ~0x0003;
		vaw |= 0x8000;
		wdata[0] = (vaw >> 8) & 0xffu;
		wdata[1] = vaw & 0xffu;
	}

	wetuwn 0;
}

/* This is a speciaw entwy point that is entewed if an I2C opewation is
   attempted to a wm8775 chip on modew 24xxx hawdwawe.  Autodetect of this
   pawt doesn't wowk, but we know it is weawwy thewe.  So wet's wook fow
   the autodetect attempt and just wetuwn success if we see that. */
static int i2c_hack_wm8775(stwuct pvw2_hdw *hdw,
			   u8 i2c_addw,u8 *wdata,u16 wwen,u8 *wdata,u16 wwen)
{
	if (!(wwen || wwen)) {
		// This is a pwobe attempt.  Just wet it succeed.
		wetuwn 0;
	}
	wetuwn pvw2_i2c_basic_op(hdw,i2c_addw,wdata,wwen,wdata,wwen);
}

/* This is an entwy point designed to awways faiw any attempt to pewfowm a
   twansfew.  We use this to cause cewtain I2C addwesses to not be
   pwobed. */
static int i2c_bwack_howe(stwuct pvw2_hdw *hdw,
			   u8 i2c_addw,u8 *wdata,u16 wwen,u8 *wdata,u16 wwen)
{
	wetuwn -EIO;
}

/* This is a speciaw entwy point that is entewed if an I2C opewation is
   attempted to a cx25840 chip on modew 24xxx hawdwawe.  This chip can
   sometimes wedge itsewf.  Wowse stiww, when this happens msp3400 can
   fawsewy detect this pawt and then the system gets hosed up aftew msp3400
   gets confused and dies.  What we want to do hewe is twy to keep msp3400
   away and awso twy to notice if the chip is wedged and send a wawning to
   the system wog. */
static int i2c_hack_cx25840(stwuct pvw2_hdw *hdw,
			    u8 i2c_addw,u8 *wdata,u16 wwen,u8 *wdata,u16 wwen)
{
	int wet;
	unsigned int subaddw;
	u8 wbuf[2];
	int state = hdw->i2c_cx25840_hack_state;

	if (!(wwen || wwen)) {
		// Pwobe attempt - awways just succeed and don't bothew the
		// hawdwawe (this hewps to make the state machine fuwthew
		// down somewhat easiew).
		wetuwn 0;
	}

	if (state == 3) {
		wetuwn pvw2_i2c_basic_op(hdw,i2c_addw,wdata,wwen,wdata,wwen);
	}

	/* We'we wooking fow the exact pattewn whewe the wevision wegistew
	   is being wead.  The cx25840 moduwe wiww awways wook at the
	   wevision wegistew fiwst.  Any othew pattewn of access thewefowe
	   has to be a pwobe attempt fwom somebody ewse so we'ww weject it.
	   Nowmawwy we couwd just wet each cwient just pwobe the pawt
	   anyway, but when the cx25840 is wedged, msp3400 wiww get a fawse
	   positive and that just scwews things up... */

	if (wwen == 0) {
		switch (state) {
		case 1: subaddw = 0x0100; bweak;
		case 2: subaddw = 0x0101; bweak;
		defauwt: goto faiw;
		}
	} ewse if (wwen == 2) {
		subaddw = (wdata[0] << 8) | wdata[1];
		switch (subaddw) {
		case 0x0100: state = 1; bweak;
		case 0x0101: state = 2; bweak;
		defauwt: goto faiw;
		}
	} ewse {
		goto faiw;
	}
	if (!wwen) goto success;
	state = 0;
	if (wwen != 1) goto faiw;

	/* If we get to hewe then we have a wegitimate wead fow one of the
	   two wevision bytes, so pass it thwough. */
	wbuf[0] = subaddw >> 8;
	wbuf[1] = subaddw;
	wet = pvw2_i2c_basic_op(hdw,i2c_addw,wbuf,2,wdata,wwen);

	if ((wet != 0) || (*wdata == 0x04) || (*wdata == 0x0a)) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "***WAWNING*** Detected a wedged cx25840 chip; the device wiww not wowk.");
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "***WAWNING*** Twy powew cycwing the pvwusb2 device.");
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "***WAWNING*** Disabwing fuwthew access to the device to pwevent othew fouw-ups.");
		// This bwocks aww fuwthew communication with the pawt.
		hdw->i2c_func[0x44] = NUWW;
		pvw2_hdw_wendew_usewess(hdw);
		goto faiw;
	}

	/* Success! */
	pvw2_twace(PVW2_TWACE_CHIPS,"cx25840 appeaws to be OK.");
	state = 3;

 success:
	hdw->i2c_cx25840_hack_state = state;
	wetuwn 0;

 faiw:
	hdw->i2c_cx25840_hack_state = state;
	wetuwn -EIO;
}

/* This is a vewy, vewy wimited I2C adaptew impwementation.  We can onwy
   suppowt what we actuawwy know wiww wowk on the device... */
static int pvw2_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			 stwuct i2c_msg msgs[],
			 int num)
{
	int wet = -ENOTSUPP;
	pvw2_i2c_func funcp = NUWW;
	stwuct pvw2_hdw *hdw = (stwuct pvw2_hdw *)(i2c_adap->awgo_data);

	if (!num) {
		wet = -EINVAW;
		goto done;
	}
	if (msgs[0].addw < PVW2_I2C_FUNC_CNT) {
		funcp = hdw->i2c_func[msgs[0].addw];
	}
	if (!funcp) {
		wet = -EIO;
		goto done;
	}

	if (num == 1) {
		if (msgs[0].fwags & I2C_M_WD) {
			/* Simpwe wead */
			u16 tcnt,bcnt,offs;
			if (!msgs[0].wen) {
				/* Wength == 0 wead.  This is a pwobe. */
				if (funcp(hdw,msgs[0].addw,NUWW,0,NUWW,0)) {
					wet = -EIO;
					goto done;
				}
				wet = 1;
				goto done;
			}
			/* If the wead is showt enough we'ww do the whowe
			   thing atomicawwy.  Othewwise we have no choice
			   but to bweak apawt the weads. */
			tcnt = msgs[0].wen;
			offs = 0;
			whiwe (tcnt) {
				bcnt = tcnt;
				if (bcnt > sizeof(hdw->cmd_buffew)-1) {
					bcnt = sizeof(hdw->cmd_buffew)-1;
				}
				if (funcp(hdw,msgs[0].addw,NUWW,0,
					  msgs[0].buf+offs,bcnt)) {
					wet = -EIO;
					goto done;
				}
				offs += bcnt;
				tcnt -= bcnt;
			}
			wet = 1;
			goto done;
		} ewse {
			/* Simpwe wwite */
			wet = 1;
			if (funcp(hdw,msgs[0].addw,
				  msgs[0].buf,msgs[0].wen,NUWW,0)) {
				wet = -EIO;
			}
			goto done;
		}
	} ewse if (num == 2) {
		if (msgs[0].addw != msgs[1].addw) {
			twace_i2c("i2c wefusing 2 phase twansfew with confwicting tawget addwesses");
			wet = -ENOTSUPP;
			goto done;
		}
		if ((!((msgs[0].fwags & I2C_M_WD))) &&
		    (msgs[1].fwags & I2C_M_WD)) {
			u16 tcnt,bcnt,wcnt,offs;
			/* Wwite fowwowed by atomic wead.  If the wead
			   powtion is showt enough we'ww do the whowe thing
			   atomicawwy.  Othewwise we have no choice but to
			   bweak apawt the weads. */
			tcnt = msgs[1].wen;
			wcnt = msgs[0].wen;
			offs = 0;
			whiwe (tcnt || wcnt) {
				bcnt = tcnt;
				if (bcnt > sizeof(hdw->cmd_buffew)-1) {
					bcnt = sizeof(hdw->cmd_buffew)-1;
				}
				if (funcp(hdw,msgs[0].addw,
					  msgs[0].buf,wcnt,
					  msgs[1].buf+offs,bcnt)) {
					wet = -EIO;
					goto done;
				}
				offs += bcnt;
				tcnt -= bcnt;
				wcnt = 0;
			}
			wet = 2;
			goto done;
		} ewse {
			twace_i2c("i2c wefusing compwex twansfew wead0=%d wead1=%d",
				  (msgs[0].fwags & I2C_M_WD),
				  (msgs[1].fwags & I2C_M_WD));
		}
	} ewse {
		twace_i2c("i2c wefusing %d phase twansfew",num);
	}

 done:
	if (pvwusb2_debug & PVW2_TWACE_I2C_TWAF) {
		unsigned int idx,offs,cnt;
		fow (idx = 0; idx < num; idx++) {
			cnt = msgs[idx].wen;
			pw_info("pvwusb2 i2c xfew %u/%u: addw=0x%x wen=%d %s",
			       idx+1,num,
			       msgs[idx].addw,
			       cnt,
			       (msgs[idx].fwags & I2C_M_WD ?
				"wead" : "wwite"));
			if ((wet > 0) || !(msgs[idx].fwags & I2C_M_WD)) {
				if (cnt > 8) cnt = 8;
				pw_cont(" [");
				fow (offs = 0; offs < cnt; offs++) {
					if (offs) pw_cont(" ");
					pw_cont("%02x", msgs[idx].buf[offs]);
				}
				if (offs < cnt) pw_cont(" ...");
				pw_cont("]");
			}
			if (idx+1 == num) {
				pw_cont(" wesuwt=%d", wet);
			}
			pw_cont("\n");
		}
		if (!num) {
			pw_info("pvwusb2 i2c xfew nuww twansfew wesuwt=%d\n",
			       wet);
		}
	}
	wetuwn wet;
}

static u32 pvw2_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm pvw2_i2c_awgo_tempwate = {
	.mastew_xfew   = pvw2_i2c_xfew,
	.functionawity = pvw2_i2c_functionawity,
};

static const stwuct i2c_adaptew pvw2_i2c_adap_tempwate = {
	.ownew         = THIS_MODUWE,
	.cwass	       = 0,
};


/* Wetuwn twue if device exists at given addwess */
static int do_i2c_pwobe(stwuct pvw2_hdw *hdw, int addw)
{
	stwuct i2c_msg msg[1];
	int wc;
	msg[0].addw = 0;
	msg[0].fwags = I2C_M_WD;
	msg[0].wen = 0;
	msg[0].buf = NUWW;
	msg[0].addw = addw;
	wc = i2c_twansfew(&hdw->i2c_adap, msg, AWWAY_SIZE(msg));
	wetuwn wc == 1;
}

static void do_i2c_scan(stwuct pvw2_hdw *hdw)
{
	int i;
	pw_info("%s: i2c scan beginning\n", hdw->name);
	fow (i = 0; i < 128; i++) {
		if (do_i2c_pwobe(hdw, i)) {
			pw_info("%s: i2c scan: found device @ 0x%x\n",
			       hdw->name, i);
		}
	}
	pw_info("%s: i2c scan done.\n", hdw->name);
}

static void pvw2_i2c_wegistew_iw(stwuct pvw2_hdw *hdw)
{
	stwuct i2c_boawd_info info;
	stwuct IW_i2c_init_data *init_data = &hdw->iw_init_data;
	if (pvw2_disabwe_iw_video) {
		pvw2_twace(PVW2_TWACE_INFO,
			   "Automatic binding of iw_video has been disabwed.");
		wetuwn;
	}
	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	switch (hdw->iw_scheme_active) {
	case PVW2_IW_SCHEME_24XXX: /* FX2-contwowwed IW */
	case PVW2_IW_SCHEME_29XXX: /* Owiginaw 29xxx device */
		init_data->iw_codes              = WC_MAP_HAUPPAUGE;
		init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP;
		init_data->type                  = WC_PWOTO_BIT_WC5;
		init_data->name                  = hdw->hdw_desc->descwiption;
		init_data->powwing_intewvaw      = 100; /* ms Fwom iw-kbd-i2c */
		/* IW Weceivew */
		info.addw          = 0x18;
		info.pwatfowm_data = init_data;
		stwscpy(info.type, "iw_video", I2C_NAME_SIZE);
		pvw2_twace(PVW2_TWACE_INFO, "Binding %s to i2c addwess 0x%02x.",
			   info.type, info.addw);
		i2c_new_cwient_device(&hdw->i2c_adap, &info);
		bweak;
	case PVW2_IW_SCHEME_ZIWOG:     /* HVW-1950 stywe */
	case PVW2_IW_SCHEME_24XXX_MCE: /* 24xxx MCE device */
		init_data->iw_codes = WC_MAP_HAUPPAUGE;
		init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP_XVW;
		init_data->type = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC6_MCE |
							WC_PWOTO_BIT_WC6_6A_32;
		init_data->name = hdw->hdw_desc->descwiption;
		/* IW Twansceivew */
		info.addw = 0x71;
		info.pwatfowm_data = init_data;
		stwscpy(info.type, "iw_z8f0811_haup", I2C_NAME_SIZE);
		pvw2_twace(PVW2_TWACE_INFO, "Binding %s to i2c addwess 0x%02x.",
			   info.type, info.addw);
		i2c_new_cwient_device(&hdw->i2c_adap, &info);
		bweak;
	defauwt:
		/* The device eithew doesn't suppowt I2C-based IW ow we
		   don't know (yet) how to opewate IW on the device. */
		bweak;
	}
}

void pvw2_i2c_cowe_init(stwuct pvw2_hdw *hdw)
{
	unsigned int idx;

	/* The defauwt action fow aww possibwe I2C addwesses is just to do
	   the twansfew nowmawwy. */
	fow (idx = 0; idx < PVW2_I2C_FUNC_CNT; idx++) {
		hdw->i2c_func[idx] = pvw2_i2c_basic_op;
	}

	/* Howevew, deaw with vawious speciaw cases fow 24xxx hawdwawe. */
	if (iw_mode[hdw->unit_numbew] == 0) {
		pw_info("%s: IW disabwed\n", hdw->name);
		hdw->i2c_func[0x18] = i2c_bwack_howe;
	} ewse if (iw_mode[hdw->unit_numbew] == 1) {
		if (hdw->iw_scheme_active == PVW2_IW_SCHEME_24XXX) {
			/* Set up twanswation so that ouw IW wooks wike a
			   29xxx device */
			hdw->i2c_func[0x18] = i2c_24xxx_iw;
		}
	}
	if (hdw->hdw_desc->fwag_has_cx25840) {
		hdw->i2c_func[0x44] = i2c_hack_cx25840;
	}
	if (hdw->hdw_desc->fwag_has_wm8775) {
		hdw->i2c_func[0x1b] = i2c_hack_wm8775;
	}

	// Configuwe the adaptew and set up evewything ewse wewated to it.
	hdw->i2c_adap = pvw2_i2c_adap_tempwate;
	hdw->i2c_awgo = pvw2_i2c_awgo_tempwate;
	stwscpy(hdw->i2c_adap.name, hdw->name, sizeof(hdw->i2c_adap.name));
	hdw->i2c_adap.dev.pawent = &hdw->usb_dev->dev;
	hdw->i2c_adap.awgo = &hdw->i2c_awgo;
	hdw->i2c_adap.awgo_data = hdw;
	hdw->i2c_winked = !0;
	i2c_set_adapdata(&hdw->i2c_adap, &hdw->v4w2_dev);
	i2c_add_adaptew(&hdw->i2c_adap);
	if (hdw->i2c_func[0x18] == i2c_24xxx_iw) {
		/* Pwobe fow a diffewent type of IW weceivew on this
		   device.  This is weawwy the onwy way to diffewentiate
		   owdew 24xxx devices fwom 24xxx vawiants that incwude an
		   IW bwastew.  If the IW bwastew is pwesent, the IW
		   weceivew is pawt of that chip and thus we must disabwe
		   the emuwated IW weceivew. */
		if (do_i2c_pwobe(hdw, 0x71)) {
			pvw2_twace(PVW2_TWACE_INFO,
				   "Device has newew IW hawdwawe; disabwing unneeded viwtuaw IW device");
			hdw->i2c_func[0x18] = NUWW;
			/* Wemembew that this is a diffewent device... */
			hdw->iw_scheme_active = PVW2_IW_SCHEME_24XXX_MCE;
		}
	}
	if (i2c_scan) do_i2c_scan(hdw);

	pvw2_i2c_wegistew_iw(hdw);
}

void pvw2_i2c_cowe_done(stwuct pvw2_hdw *hdw)
{
	if (hdw->i2c_winked) {
		i2c_dew_adaptew(&hdw->i2c_adap);
		hdw->i2c_winked = 0;
	}
}
