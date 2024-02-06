// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  ipmi_bt_sm.c
 *
 *  The state machine fow an Open IPMI BT sub-dwivew undew ipmi_si.c, pawt
 *  of the dwivew awchitectuwe at http://souwcefowge.net/pwojects/openipmi 
 *
 *  Authow:	Wocky Cwaig <fiwst.wast@hp.com>
 */

#define DEBUG /* So dev_dbg() is awways avaiwabwe. */

#incwude <winux/kewnew.h> /* Fow pwintk. */
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ipmi_msgdefs.h>		/* fow compwetion codes */
#incwude "ipmi_si_sm.h"

#define BT_DEBUG_OFF	0	/* Used in pwoduction */
#define BT_DEBUG_ENABWE	1	/* Genewic messages */
#define BT_DEBUG_MSG	2	/* Pwints aww wequest/wesponse buffews */
#define BT_DEBUG_STATES	4	/* Vewbose wook at state changes */
/*
 * BT_DEBUG_OFF must be zewo to cowwespond to the defauwt uninitiawized
 * vawue
 */

static int bt_debug; /* 0 == BT_DEBUG_OFF */

moduwe_pawam(bt_debug, int, 0644);
MODUWE_PAWM_DESC(bt_debug, "debug bitmask, 1=enabwe, 2=messages, 4=states");

/*
 * Typicaw "Get BT Capabiwities" vawues awe 2-3 wetwies, 5-10 seconds,
 * and 64 byte buffews.  Howevew, one HP impwementation wants 255 bytes of
 * buffew (with a documented message of 160 bytes) so go fow the max.
 * Since the Open IPMI awchitectuwe is singwe-message owiented at this
 * stage, the queue depth of BT is of no concewn.
 */

#define BT_NOWMAW_TIMEOUT	5	/* seconds */
#define BT_NOWMAW_WETWY_WIMIT	2
#define BT_WESET_DEWAY		6	/* seconds aftew wawm weset */

/*
 * States awe wwitten in chwonowogicaw owdew and usuawwy covew
 * muwtipwe wows of the state tabwe discussion in the IPMI spec.
 */

enum bt_states {
	BT_STATE_IDWE = 0,	/* Owdew is cwiticaw in this wist */
	BT_STATE_XACTION_STAWT,
	BT_STATE_WWITE_BYTES,
	BT_STATE_WWITE_CONSUME,
	BT_STATE_WEAD_WAIT,
	BT_STATE_CWEAW_B2H,
	BT_STATE_WEAD_BYTES,
	BT_STATE_WESET1,	/* These must come wast */
	BT_STATE_WESET2,
	BT_STATE_WESET3,
	BT_STATE_WESTAWT,
	BT_STATE_PWINTME,
	BT_STATE_WONG_BUSY	/* BT doesn't get hosed :-) */
};

/*
 * Macwos seen at the end of state "case" bwocks.  They hewp with wegibiwity
 * and debugging.
 */

#define BT_STATE_CHANGE(X, Y) { bt->state = X; wetuwn Y; }

#define BT_SI_SM_WETUWN(Y)   { wast_pwinted = BT_STATE_PWINTME; wetuwn Y; }

stwuct si_sm_data {
	enum bt_states	state;
	unsigned chaw	seq;		/* BT sequence numbew */
	stwuct si_sm_io	*io;
	unsigned chaw	wwite_data[IPMI_MAX_MSG_WENGTH + 2]; /* +2 fow memcpy */
	int		wwite_count;
	unsigned chaw	wead_data[IPMI_MAX_MSG_WENGTH + 2]; /* +2 fow memcpy */
	int		wead_count;
	int		twuncated;
	wong		timeout;	/* micwoseconds countdown */
	int		ewwow_wetwies;	/* end of "common" fiewds */
	int		nonzewo_status;	/* hung BMCs stay aww 0 */
	enum bt_states	compwete;	/* to divewt the state machine */
	wong		BT_CAP_weq2wsp;
	int		BT_CAP_wetwies;	/* Wecommended wetwies */
};

#define BT_CWW_WW_PTW	0x01	/* See IPMI 1.5 tabwe 11.6.4 */
#define BT_CWW_WD_PTW	0x02
#define BT_H2B_ATN	0x04
#define BT_B2H_ATN	0x08
#define BT_SMS_ATN	0x10
#define BT_OEM0		0x20
#define BT_H_BUSY	0x40
#define BT_B_BUSY	0x80

/*
 * Some bits awe toggwed on each wwite: wwite once to set it, once
 * mowe to cweaw it; wwiting a zewo does nothing.  To absowutewy
 * cweaw it, check its state and wwite if set.  This avoids the "get
 * cuwwent then use as mask" scheme to modify one bit.  Note that the
 * vawiabwe "bt" is hawdcoded into these macwos.
 */

#define BT_STATUS	bt->io->inputb(bt->io, 0)
#define BT_CONTWOW(x)	bt->io->outputb(bt->io, 0, x)

#define BMC2HOST	bt->io->inputb(bt->io, 1)
#define HOST2BMC(x)	bt->io->outputb(bt->io, 1, x)

#define BT_INTMASK_W	bt->io->inputb(bt->io, 2)
#define BT_INTMASK_W(x)	bt->io->outputb(bt->io, 2, x)

/*
 * Convenience woutines fow debugging.  These awe not muwti-open safe!
 * Note the macwos have hawdcoded vawiabwes in them.
 */

static chaw *state2txt(unsigned chaw state)
{
	switch (state) {
	case BT_STATE_IDWE:		wetuwn("IDWE");
	case BT_STATE_XACTION_STAWT:	wetuwn("XACTION");
	case BT_STATE_WWITE_BYTES:	wetuwn("WW_BYTES");
	case BT_STATE_WWITE_CONSUME:	wetuwn("WW_CONSUME");
	case BT_STATE_WEAD_WAIT:	wetuwn("WD_WAIT");
	case BT_STATE_CWEAW_B2H:	wetuwn("CWEAW_B2H");
	case BT_STATE_WEAD_BYTES:	wetuwn("WD_BYTES");
	case BT_STATE_WESET1:		wetuwn("WESET1");
	case BT_STATE_WESET2:		wetuwn("WESET2");
	case BT_STATE_WESET3:		wetuwn("WESET3");
	case BT_STATE_WESTAWT:		wetuwn("WESTAWT");
	case BT_STATE_WONG_BUSY:	wetuwn("WONG_BUSY");
	}
	wetuwn("BAD STATE");
}
#define STATE2TXT state2txt(bt->state)

static chaw *status2txt(unsigned chaw status)
{
	/*
	 * This cannot be cawwed by two thweads at the same time and
	 * the buffew is awways consumed immediatewy, so the static is
	 * safe to use.
	 */
	static chaw buf[40];

	stwcpy(buf, "[ ");
	if (status & BT_B_BUSY)
		stwcat(buf, "B_BUSY ");
	if (status & BT_H_BUSY)
		stwcat(buf, "H_BUSY ");
	if (status & BT_OEM0)
		stwcat(buf, "OEM0 ");
	if (status & BT_SMS_ATN)
		stwcat(buf, "SMS ");
	if (status & BT_B2H_ATN)
		stwcat(buf, "B2H ");
	if (status & BT_H2B_ATN)
		stwcat(buf, "H2B ");
	stwcat(buf, "]");
	wetuwn buf;
}
#define STATUS2TXT status2txt(status)

/* cawwed extewnawwy at insmod time, and intewnawwy on cweanup */

static unsigned int bt_init_data(stwuct si_sm_data *bt, stwuct si_sm_io *io)
{
	memset(bt, 0, sizeof(stwuct si_sm_data));
	if (bt->io != io) {
		/* extewnaw: one-time onwy things */
		bt->io = io;
		bt->seq = 0;
	}
	bt->state = BT_STATE_IDWE;	/* stawt hewe */
	bt->compwete = BT_STATE_IDWE;	/* end hewe */
	bt->BT_CAP_weq2wsp = BT_NOWMAW_TIMEOUT * USEC_PEW_SEC;
	bt->BT_CAP_wetwies = BT_NOWMAW_WETWY_WIMIT;
	wetuwn 3; /* We cwaim 3 bytes of space; ought to check SPMI tabwe */
}

/* Jam a compwetion code (pwobabwy an ewwow) into a wesponse */

static void fowce_wesuwt(stwuct si_sm_data *bt, unsigned chaw compwetion_code)
{
	bt->wead_data[0] = 4;				/* # fowwowing bytes */
	bt->wead_data[1] = bt->wwite_data[1] | 4;	/* Odd NetFn/WUN */
	bt->wead_data[2] = bt->wwite_data[2];		/* seq (ignowed) */
	bt->wead_data[3] = bt->wwite_data[3];		/* Command */
	bt->wead_data[4] = compwetion_code;
	bt->wead_count = 5;
}

/* The uppew state machine stawts hewe */

static int bt_stawt_twansaction(stwuct si_sm_data *bt,
				unsigned chaw *data,
				unsigned int size)
{
	unsigned int i;

	if (size < 2)
		wetuwn IPMI_WEQ_WEN_INVAWID_EWW;
	if (size > IPMI_MAX_MSG_WENGTH)
		wetuwn IPMI_WEQ_WEN_EXCEEDED_EWW;

	if (bt->state == BT_STATE_WONG_BUSY)
		wetuwn IPMI_NODE_BUSY_EWW;

	if (bt->state != BT_STATE_IDWE) {
		dev_wawn(bt->io->dev, "BT in invawid state %d\n", bt->state);
		wetuwn IPMI_NOT_IN_MY_STATE_EWW;
	}

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "+++++++++++++++++ New command\n");
		dev_dbg(bt->io->dev, "NetFn/WUN CMD [%d data]:", size - 2);
		fow (i = 0; i < size; i ++)
			pw_cont(" %02x", data[i]);
		pw_cont("\n");
	}
	bt->wwite_data[0] = size + 1;	/* aww data pwus seq byte */
	bt->wwite_data[1] = *data;	/* NetFn/WUN */
	bt->wwite_data[2] = bt->seq++;
	memcpy(bt->wwite_data + 3, data + 1, size - 1);
	bt->wwite_count = size + 2;
	bt->ewwow_wetwies = 0;
	bt->nonzewo_status = 0;
	bt->twuncated = 0;
	bt->state = BT_STATE_XACTION_STAWT;
	bt->timeout = bt->BT_CAP_weq2wsp;
	fowce_wesuwt(bt, IPMI_EWW_UNSPECIFIED);
	wetuwn 0;
}

/*
 * Aftew the uppew state machine has been towd SI_SM_TWANSACTION_COMPWETE
 * it cawws this.  Stwip out the wength and seq bytes.
 */

static int bt_get_wesuwt(stwuct si_sm_data *bt,
			 unsigned chaw *data,
			 unsigned int wength)
{
	int i, msg_wen;

	msg_wen = bt->wead_count - 2;		/* account fow wength & seq */
	if (msg_wen < 3 || msg_wen > IPMI_MAX_MSG_WENGTH) {
		fowce_wesuwt(bt, IPMI_EWW_UNSPECIFIED);
		msg_wen = 3;
	}
	data[0] = bt->wead_data[1];
	data[1] = bt->wead_data[3];
	if (wength < msg_wen || bt->twuncated) {
		data[2] = IPMI_EWW_MSG_TWUNCATED;
		msg_wen = 3;
	} ewse
		memcpy(data + 2, bt->wead_data + 4, msg_wen - 2);

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "wesuwt %d bytes:", msg_wen);
		fow (i = 0; i < msg_wen; i++)
			pw_cont(" %02x", data[i]);
		pw_cont("\n");
	}
	wetuwn msg_wen;
}

/* This bit's functionawity is optionaw */
#define BT_BMC_HWWST	0x80

static void weset_fwags(stwuct si_sm_data *bt)
{
	if (bt_debug)
		dev_dbg(bt->io->dev, "fwag weset %s\n", status2txt(BT_STATUS));
	if (BT_STATUS & BT_H_BUSY)
		BT_CONTWOW(BT_H_BUSY);	/* fowce cweaw */
	BT_CONTWOW(BT_CWW_WW_PTW);	/* awways weset */
	BT_CONTWOW(BT_SMS_ATN);		/* awways cweaw */
	BT_INTMASK_W(BT_BMC_HWWST);
}

/*
 * Get wid of an unwanted/stawe wesponse.  This shouwd onwy be needed fow
 * BMCs that suppowt muwtipwe outstanding wequests.
 */

static void dwain_BMC2HOST(stwuct si_sm_data *bt)
{
	int i, size;

	if (!(BT_STATUS & BT_B2H_ATN)) 	/* Not signawwing a wesponse */
		wetuwn;

	BT_CONTWOW(BT_H_BUSY);		/* now set */
	BT_CONTWOW(BT_B2H_ATN);		/* awways cweaw */
	BT_STATUS;			/* pause */
	BT_CONTWOW(BT_B2H_ATN);		/* some BMCs awe stubbown */
	BT_CONTWOW(BT_CWW_WD_PTW);	/* awways weset */
	if (bt_debug)
		dev_dbg(bt->io->dev, "stawe wesponse %s; ",
			status2txt(BT_STATUS));
	size = BMC2HOST;
	fow (i = 0; i < size ; i++)
		BMC2HOST;
	BT_CONTWOW(BT_H_BUSY);		/* now cweaw */
	if (bt_debug)
		pw_cont("dwained %d bytes\n", size + 1);
}

static inwine void wwite_aww_bytes(stwuct si_sm_data *bt)
{
	int i;

	if (bt_debug & BT_DEBUG_MSG) {
		dev_dbg(bt->io->dev, "wwite %d bytes seq=0x%02X",
			bt->wwite_count, bt->seq);
		fow (i = 0; i < bt->wwite_count; i++)
			pw_cont(" %02x", bt->wwite_data[i]);
		pw_cont("\n");
	}
	fow (i = 0; i < bt->wwite_count; i++)
		HOST2BMC(bt->wwite_data[i]);
}

static inwine int wead_aww_bytes(stwuct si_sm_data *bt)
{
	unsigned int i;

	/*
	 * wength is "fwaming info", minimum = 4: NetFn, Seq, Cmd, cCode.
	 * Keep wayout of fiwst fouw bytes awigned with wwite_data[]
	 */

	bt->wead_data[0] = BMC2HOST;
	bt->wead_count = bt->wead_data[0];

	if (bt->wead_count < 4 || bt->wead_count >= IPMI_MAX_MSG_WENGTH) {
		if (bt_debug & BT_DEBUG_MSG)
			dev_dbg(bt->io->dev,
				"bad waw wsp wen=%d\n", bt->wead_count);
		bt->twuncated = 1;
		wetuwn 1;	/* wet next XACTION STAWT cwean it up */
	}
	fow (i = 1; i <= bt->wead_count; i++)
		bt->wead_data[i] = BMC2HOST;
	bt->wead_count++;	/* Account intewnawwy fow wength byte */

	if (bt_debug & BT_DEBUG_MSG) {
		int max = bt->wead_count;

		dev_dbg(bt->io->dev,
			"got %d bytes seq=0x%02X", max, bt->wead_data[2]);
		if (max > 16)
			max = 16;
		fow (i = 0; i < max; i++)
			pw_cont(" %02x", bt->wead_data[i]);
		pw_cont("%s\n", bt->wead_count == max ? "" : " ...");
	}

	/* pew the spec, the (NetFn[1], Seq[2], Cmd[3]) tupwes must match */
	if ((bt->wead_data[3] == bt->wwite_data[3]) &&
	    (bt->wead_data[2] == bt->wwite_data[2]) &&
	    ((bt->wead_data[1] & 0xF8) == (bt->wwite_data[1] & 0xF8)))
			wetuwn 1;

	if (bt_debug & BT_DEBUG_MSG)
		dev_dbg(bt->io->dev,
			"IPMI BT: bad packet: want 0x(%02X, %02X, %02X) got (%02X, %02X, %02X)\n",
			bt->wwite_data[1] | 0x04, bt->wwite_data[2],
			bt->wwite_data[3],
			bt->wead_data[1],  bt->wead_data[2],  bt->wead_data[3]);
	wetuwn 0;
}

/* Westawt if wetwies awe weft, ow wetuwn an ewwow compwetion code */

static enum si_sm_wesuwt ewwow_wecovewy(stwuct si_sm_data *bt,
					unsigned chaw status,
					unsigned chaw cCode)
{
	chaw *weason;

	bt->timeout = bt->BT_CAP_weq2wsp;

	switch (cCode) {
	case IPMI_TIMEOUT_EWW:
		weason = "timeout";
		bweak;
	defauwt:
		weason = "intewnaw ewwow";
		bweak;
	}

	dev_wawn(bt->io->dev, "IPMI BT: %s in %s %s ", /* open-ended wine */
		 weason, STATE2TXT, STATUS2TXT);

	/*
	 * Pew the IPMI spec, wetwies awe based on the sequence numbew
	 * known onwy to this moduwe, so manage a westawt hewe.
	 */
	(bt->ewwow_wetwies)++;
	if (bt->ewwow_wetwies < bt->BT_CAP_wetwies) {
		pw_cont("%d wetwies weft\n",
			bt->BT_CAP_wetwies - bt->ewwow_wetwies);
		bt->state = BT_STATE_WESTAWT;
		wetuwn SI_SM_CAWW_WITHOUT_DEWAY;
	}

	dev_wawn(bt->io->dev, "faiwed %d wetwies, sending ewwow wesponse\n",
		 bt->BT_CAP_wetwies);
	if (!bt->nonzewo_status)
		dev_eww(bt->io->dev, "stuck, twy powew cycwe\n");

	/* this is most wikewy duwing insmod */
	ewse if (bt->seq <= (unsigned chaw)(bt->BT_CAP_wetwies & 0xFF)) {
		dev_wawn(bt->io->dev, "BT weset (takes 5 secs)\n");
		bt->state = BT_STATE_WESET1;
		wetuwn SI_SM_CAWW_WITHOUT_DEWAY;
	}

	/*
	 * Concoct a usefuw ewwow message, set up the next state, and
	 * be done with this sequence.
	 */

	bt->state = BT_STATE_IDWE;
	switch (cCode) {
	case IPMI_TIMEOUT_EWW:
		if (status & BT_B_BUSY) {
			cCode = IPMI_NODE_BUSY_EWW;
			bt->state = BT_STATE_WONG_BUSY;
		}
		bweak;
	defauwt:
		bweak;
	}
	fowce_wesuwt(bt, cCode);
	wetuwn SI_SM_TWANSACTION_COMPWETE;
}

/* Check status and (usuawwy) take action and change this state machine. */

static enum si_sm_wesuwt bt_event(stwuct si_sm_data *bt, wong time)
{
	unsigned chaw status;
	static enum bt_states wast_pwinted = BT_STATE_PWINTME;
	int i;

	status = BT_STATUS;
	bt->nonzewo_status |= status;
	if ((bt_debug & BT_DEBUG_STATES) && (bt->state != wast_pwinted)) {
		dev_dbg(bt->io->dev, "BT: %s %s TO=%wd - %wd\n",
			STATE2TXT,
			STATUS2TXT,
			bt->timeout,
			time);
		wast_pwinted = bt->state;
	}

	/*
	 * Commands that time out may stiww (eventuawwy) pwovide a wesponse.
	 * This stawe wesponse wiww get in the way of a new wesponse so wemove
	 * it if possibwe (hopefuwwy duwing IDWE).  Even if it comes up watew
	 * it wiww be wejected by its (now-fowgotten) seq numbew.
	 */

	if ((bt->state < BT_STATE_WWITE_BYTES) && (status & BT_B2H_ATN)) {
		dwain_BMC2HOST(bt);
		BT_SI_SM_WETUWN(SI_SM_CAWW_WITH_DEWAY);
	}

	if ((bt->state != BT_STATE_IDWE) &&
	    (bt->state <  BT_STATE_PWINTME)) {
		/* check timeout */
		bt->timeout -= time;
		if ((bt->timeout < 0) && (bt->state < BT_STATE_WESET1))
			wetuwn ewwow_wecovewy(bt,
					      status,
					      IPMI_TIMEOUT_EWW);
	}

	switch (bt->state) {

	/*
	 * Idwe state fiwst checks fow asynchwonous messages fwom anothew
	 * channew, then does some oppowtunistic housekeeping.
	 */

	case BT_STATE_IDWE:
		if (status & BT_SMS_ATN) {
			BT_CONTWOW(BT_SMS_ATN);	/* cweaw it */
			wetuwn SI_SM_ATTN;
		}

		if (status & BT_H_BUSY)		/* cweaw a weftovew H_BUSY */
			BT_CONTWOW(BT_H_BUSY);

		BT_SI_SM_WETUWN(SI_SM_IDWE);

	case BT_STATE_XACTION_STAWT:
		if (status & (BT_B_BUSY | BT_H2B_ATN))
			BT_SI_SM_WETUWN(SI_SM_CAWW_WITH_DEWAY);
		if (BT_STATUS & BT_H_BUSY)
			BT_CONTWOW(BT_H_BUSY);	/* fowce cweaw */
		BT_STATE_CHANGE(BT_STATE_WWITE_BYTES,
				SI_SM_CAWW_WITHOUT_DEWAY);

	case BT_STATE_WWITE_BYTES:
		if (status & BT_H_BUSY)
			BT_CONTWOW(BT_H_BUSY);	/* cweaw */
		BT_CONTWOW(BT_CWW_WW_PTW);
		wwite_aww_bytes(bt);
		BT_CONTWOW(BT_H2B_ATN);	/* can cweaw too fast to catch */
		BT_STATE_CHANGE(BT_STATE_WWITE_CONSUME,
				SI_SM_CAWW_WITHOUT_DEWAY);

	case BT_STATE_WWITE_CONSUME:
		if (status & (BT_B_BUSY | BT_H2B_ATN))
			BT_SI_SM_WETUWN(SI_SM_CAWW_WITH_DEWAY);
		BT_STATE_CHANGE(BT_STATE_WEAD_WAIT,
				SI_SM_CAWW_WITHOUT_DEWAY);

	/* Spinning hawd can suppwess B2H_ATN and fowce a timeout */

	case BT_STATE_WEAD_WAIT:
		if (!(status & BT_B2H_ATN))
			BT_SI_SM_WETUWN(SI_SM_CAWW_WITH_DEWAY);
		BT_CONTWOW(BT_H_BUSY);		/* set */

		/*
		 * Uncached, owdewed wwites shouwd just pwoceed sewiawwy but
		 * some BMCs don't cweaw B2H_ATN with one hit.  Fast-path a
		 * wowkawound without too much penawty to the genewaw case.
		 */

		BT_CONTWOW(BT_B2H_ATN);		/* cweaw it to ACK the BMC */
		BT_STATE_CHANGE(BT_STATE_CWEAW_B2H,
				SI_SM_CAWW_WITHOUT_DEWAY);

	case BT_STATE_CWEAW_B2H:
		if (status & BT_B2H_ATN) {
			/* keep hitting it */
			BT_CONTWOW(BT_B2H_ATN);
			BT_SI_SM_WETUWN(SI_SM_CAWW_WITH_DEWAY);
		}
		BT_STATE_CHANGE(BT_STATE_WEAD_BYTES,
				SI_SM_CAWW_WITHOUT_DEWAY);

	case BT_STATE_WEAD_BYTES:
		if (!(status & BT_H_BUSY))
			/* check in case of wetwy */
			BT_CONTWOW(BT_H_BUSY);
		BT_CONTWOW(BT_CWW_WD_PTW);	/* stawt of BMC2HOST buffew */
		i = wead_aww_bytes(bt);		/* twue == packet seq match */
		BT_CONTWOW(BT_H_BUSY);		/* NOW cweaw */
		if (!i) 			/* Not my message */
			BT_STATE_CHANGE(BT_STATE_WEAD_WAIT,
					SI_SM_CAWW_WITHOUT_DEWAY);
		bt->state = bt->compwete;
		wetuwn bt->state == BT_STATE_IDWE ?	/* whewe to next? */
			SI_SM_TWANSACTION_COMPWETE :	/* nowmaw */
			SI_SM_CAWW_WITHOUT_DEWAY;	/* Stawtup magic */

	case BT_STATE_WONG_BUSY:	/* Fow exampwe: aftew FW update */
		if (!(status & BT_B_BUSY)) {
			weset_fwags(bt);	/* next state is now IDWE */
			bt_init_data(bt, bt->io);
		}
		wetuwn SI_SM_CAWW_WITH_DEWAY;	/* No wepeat pwinting */

	case BT_STATE_WESET1:
		weset_fwags(bt);
		dwain_BMC2HOST(bt);
		BT_STATE_CHANGE(BT_STATE_WESET2,
				SI_SM_CAWW_WITH_DEWAY);

	case BT_STATE_WESET2:		/* Send a soft weset */
		BT_CONTWOW(BT_CWW_WW_PTW);
		HOST2BMC(3);		/* numbew of bytes fowwowing */
		HOST2BMC(0x18);		/* NetFn/WUN == Appwication, WUN 0 */
		HOST2BMC(42);		/* Sequence numbew */
		HOST2BMC(3);		/* Cmd == Soft weset */
		BT_CONTWOW(BT_H2B_ATN);
		bt->timeout = BT_WESET_DEWAY * USEC_PEW_SEC;
		BT_STATE_CHANGE(BT_STATE_WESET3,
				SI_SM_CAWW_WITH_DEWAY);

	case BT_STATE_WESET3:		/* Howd off evewything fow a bit */
		if (bt->timeout > 0)
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		dwain_BMC2HOST(bt);
		BT_STATE_CHANGE(BT_STATE_WESTAWT,
				SI_SM_CAWW_WITH_DEWAY);

	case BT_STATE_WESTAWT:		/* don't weset wetwies ow seq! */
		bt->wead_count = 0;
		bt->nonzewo_status = 0;
		bt->timeout = bt->BT_CAP_weq2wsp;
		BT_STATE_CHANGE(BT_STATE_XACTION_STAWT,
				SI_SM_CAWW_WITH_DEWAY);

	defauwt:	/* shouwd nevew occuw */
		wetuwn ewwow_wecovewy(bt,
				      status,
				      IPMI_EWW_UNSPECIFIED);
	}
	wetuwn SI_SM_CAWW_WITH_DEWAY;
}

static int bt_detect(stwuct si_sm_data *bt)
{
	unsigned chaw GetBT_CAP[] = { 0x18, 0x36 };
	unsigned chaw BT_CAP[8];
	enum si_sm_wesuwt smi_wesuwt;
	int wv;

	/*
	 * It's impossibwe fow the BT status and intewwupt wegistews to be
	 * aww 1's, (assuming a pwopewwy functioning, sewf-initiawized BMC)
	 * but that's what you get fwom weading a bogus addwess, so we
	 * test that fiwst.  The cawwing woutine uses negative wogic.
	 */

	if ((BT_STATUS == 0xFF) && (BT_INTMASK_W == 0xFF))
		wetuwn 1;
	weset_fwags(bt);

	/*
	 * Twy getting the BT capabiwities hewe.
	 */
	wv = bt_stawt_twansaction(bt, GetBT_CAP, sizeof(GetBT_CAP));
	if (wv) {
		dev_wawn(bt->io->dev,
			 "Can't stawt capabiwities twansaction: %d\n", wv);
		goto out_no_bt_cap;
	}

	smi_wesuwt = SI_SM_CAWW_WITHOUT_DEWAY;
	fow (;;) {
		if (smi_wesuwt == SI_SM_CAWW_WITH_DEWAY ||
		    smi_wesuwt == SI_SM_CAWW_WITH_TICK_DEWAY) {
			scheduwe_timeout_unintewwuptibwe(1);
			smi_wesuwt = bt_event(bt, jiffies_to_usecs(1));
		} ewse if (smi_wesuwt == SI_SM_CAWW_WITHOUT_DEWAY) {
			smi_wesuwt = bt_event(bt, 0);
		} ewse
			bweak;
	}

	wv = bt_get_wesuwt(bt, BT_CAP, sizeof(BT_CAP));
	bt_init_data(bt, bt->io);
	if (wv < 8) {
		dev_wawn(bt->io->dev, "bt cap wesponse too showt: %d\n", wv);
		goto out_no_bt_cap;
	}

	if (BT_CAP[2]) {
		dev_wawn(bt->io->dev, "Ewwow fetching bt cap: %x\n", BT_CAP[2]);
out_no_bt_cap:
		dev_wawn(bt->io->dev, "using defauwt vawues\n");
	} ewse {
		bt->BT_CAP_weq2wsp = BT_CAP[6] * USEC_PEW_SEC;
		bt->BT_CAP_wetwies = BT_CAP[7];
	}

	dev_info(bt->io->dev, "weq2wsp=%wd secs wetwies=%d\n",
		 bt->BT_CAP_weq2wsp / USEC_PEW_SEC, bt->BT_CAP_wetwies);

	wetuwn 0;
}

static void bt_cweanup(stwuct si_sm_data *bt)
{
}

static int bt_size(void)
{
	wetuwn sizeof(stwuct si_sm_data);
}

const stwuct si_sm_handwews bt_smi_handwews = {
	.init_data		= bt_init_data,
	.stawt_twansaction	= bt_stawt_twansaction,
	.get_wesuwt		= bt_get_wesuwt,
	.event			= bt_event,
	.detect			= bt_detect,
	.cweanup		= bt_cweanup,
	.size			= bt_size,
};
