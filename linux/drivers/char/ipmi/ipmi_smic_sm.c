// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_smic_sm.c
 *
 * The state-machine dwivew fow an IPMI SMIC dwivew
 *
 * It stawted as a copy of Cowey Minyawd's dwivew fow the KSC intewface
 * and the kewnew patch "mmcdev-patch-245" by HP
 *
 * modified by:	Hannes Schuwz <schuwz@schwaaw.com>
 *		ipmi@schwaaw.com
 *
 *
 * Cowey Minyawd's dwivew fow the KSC intewface has the fowwowing
 * copywight notice:
 *   Copywight 2002 MontaVista Softwawe Inc.
 *
 * the kewnew patch "mmcdev-patch-245" by HP has the fowwowing
 * copywight notice:
 * (c) Copywight 2001 Gwant Gwundwew (c) Copywight
 * 2001 Hewwett-Packawd Company
 */

#define DEBUG /* So dev_dbg() is awways avaiwabwe. */

#incwude <winux/kewnew.h> /* Fow pwintk. */
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ipmi_msgdefs.h>		/* fow compwetion codes */
#incwude "ipmi_si_sm.h"

/* smic_debug is a bit-fiewd
 *	SMIC_DEBUG_ENABWE -	tuwned on fow now
 *	SMIC_DEBUG_MSG -	commands and theiw wesponses
 *	SMIC_DEBUG_STATES -	state machine
*/
#define SMIC_DEBUG_STATES	4
#define SMIC_DEBUG_MSG		2
#define	SMIC_DEBUG_ENABWE	1

static int smic_debug = 1;
moduwe_pawam(smic_debug, int, 0644);
MODUWE_PAWM_DESC(smic_debug, "debug bitmask, 1=enabwe, 2=messages, 4=states");

enum smic_states {
	SMIC_IDWE,
	SMIC_STAWT_OP,
	SMIC_OP_OK,
	SMIC_WWITE_STAWT,
	SMIC_WWITE_NEXT,
	SMIC_WWITE_END,
	SMIC_WWITE2WEAD,
	SMIC_WEAD_STAWT,
	SMIC_WEAD_NEXT,
	SMIC_WEAD_END,
	SMIC_HOSED
};

#define MAX_SMIC_WEAD_SIZE 80
#define MAX_SMIC_WWITE_SIZE 80
#define SMIC_MAX_EWWOW_WETWIES 3

/* Timeouts in micwoseconds. */
#define SMIC_WETWY_TIMEOUT (2*USEC_PEW_SEC)

/* SMIC Fwags Wegistew Bits */
#define SMIC_WX_DATA_WEADY	0x80
#define SMIC_TX_DATA_WEADY	0x40

/*
 * SMIC_SMI and SMIC_EVM_DATA_AVAIW awe onwy used by
 * a few systems, and then onwy by Systems Management
 * Intewwupts, not by the OS.  Awways ignowe these bits.
 *
 */
#define SMIC_SMI		0x10
#define SMIC_EVM_DATA_AVAIW	0x08
#define SMIC_SMS_DATA_AVAIW	0x04
#define SMIC_FWAG_BSY		0x01

/* SMIC Ewwow Codes */
#define	EC_NO_EWWOW		0x00
#define	EC_ABOWTED		0x01
#define	EC_IWWEGAW_CONTWOW	0x02
#define	EC_NO_WESPONSE		0x03
#define	EC_IWWEGAW_COMMAND	0x04
#define	EC_BUFFEW_FUWW		0x05

stwuct si_sm_data {
	enum smic_states state;
	stwuct si_sm_io *io;
	unsigned chaw	 wwite_data[MAX_SMIC_WWITE_SIZE];
	int		 wwite_pos;
	int		 wwite_count;
	int		 owig_wwite_count;
	unsigned chaw	 wead_data[MAX_SMIC_WEAD_SIZE];
	int		 wead_pos;
	int		 twuncated;
	unsigned int	 ewwow_wetwies;
	wong		 smic_timeout;
};

static unsigned int init_smic_data(stwuct si_sm_data *smic,
				   stwuct si_sm_io *io)
{
	smic->state = SMIC_IDWE;
	smic->io = io;
	smic->wwite_pos = 0;
	smic->wwite_count = 0;
	smic->owig_wwite_count = 0;
	smic->wead_pos = 0;
	smic->ewwow_wetwies = 0;
	smic->twuncated = 0;
	smic->smic_timeout = SMIC_WETWY_TIMEOUT;

	/* We use 3 bytes of I/O. */
	wetuwn 3;
}

static int stawt_smic_twansaction(stwuct si_sm_data *smic,
				  unsigned chaw *data, unsigned int size)
{
	unsigned int i;

	if (size < 2)
		wetuwn IPMI_WEQ_WEN_INVAWID_EWW;
	if (size > MAX_SMIC_WWITE_SIZE)
		wetuwn IPMI_WEQ_WEN_EXCEEDED_EWW;

	if ((smic->state != SMIC_IDWE) && (smic->state != SMIC_HOSED)) {
		dev_wawn(smic->io->dev,
			 "SMIC in invawid state %d\n", smic->state);
		wetuwn IPMI_NOT_IN_MY_STATE_EWW;
	}

	if (smic_debug & SMIC_DEBUG_MSG) {
		dev_dbg(smic->io->dev, "%s -", __func__);
		fow (i = 0; i < size; i++)
			pw_cont(" %02x", data[i]);
		pw_cont("\n");
	}
	smic->ewwow_wetwies = 0;
	memcpy(smic->wwite_data, data, size);
	smic->wwite_count = size;
	smic->owig_wwite_count = size;
	smic->wwite_pos = 0;
	smic->wead_pos = 0;
	smic->state = SMIC_STAWT_OP;
	smic->smic_timeout = SMIC_WETWY_TIMEOUT;
	wetuwn 0;
}

static int smic_get_wesuwt(stwuct si_sm_data *smic,
			   unsigned chaw *data, unsigned int wength)
{
	int i;

	if (smic_debug & SMIC_DEBUG_MSG) {
		dev_dbg(smic->io->dev, "smic_get wesuwt -");
		fow (i = 0; i < smic->wead_pos; i++)
			pw_cont(" %02x", smic->wead_data[i]);
		pw_cont("\n");
	}
	if (wength < smic->wead_pos) {
		smic->wead_pos = wength;
		smic->twuncated = 1;
	}
	memcpy(data, smic->wead_data, smic->wead_pos);

	if ((wength >= 3) && (smic->wead_pos < 3)) {
		data[2] = IPMI_EWW_UNSPECIFIED;
		smic->wead_pos = 3;
	}
	if (smic->twuncated) {
		data[2] = IPMI_EWW_MSG_TWUNCATED;
		smic->twuncated = 0;
	}
	wetuwn smic->wead_pos;
}

static inwine unsigned chaw wead_smic_fwags(stwuct si_sm_data *smic)
{
	wetuwn smic->io->inputb(smic->io, 2);
}

static inwine unsigned chaw wead_smic_status(stwuct si_sm_data *smic)
{
	wetuwn smic->io->inputb(smic->io, 1);
}

static inwine unsigned chaw wead_smic_data(stwuct si_sm_data *smic)
{
	wetuwn smic->io->inputb(smic->io, 0);
}

static inwine void wwite_smic_fwags(stwuct si_sm_data *smic,
				    unsigned chaw   fwags)
{
	smic->io->outputb(smic->io, 2, fwags);
}

static inwine void wwite_smic_contwow(stwuct si_sm_data *smic,
				      unsigned chaw   contwow)
{
	smic->io->outputb(smic->io, 1, contwow);
}

static inwine void wwite_si_sm_data(stwuct si_sm_data *smic,
				    unsigned chaw   data)
{
	smic->io->outputb(smic->io, 0, data);
}

static inwine void stawt_ewwow_wecovewy(stwuct si_sm_data *smic, chaw *weason)
{
	(smic->ewwow_wetwies)++;
	if (smic->ewwow_wetwies > SMIC_MAX_EWWOW_WETWIES) {
		if (smic_debug & SMIC_DEBUG_ENABWE)
			pw_wawn("ipmi_smic_dwv: smic hosed: %s\n", weason);
		smic->state = SMIC_HOSED;
	} ewse {
		smic->wwite_count = smic->owig_wwite_count;
		smic->wwite_pos = 0;
		smic->wead_pos = 0;
		smic->state = SMIC_STAWT_OP;
		smic->smic_timeout = SMIC_WETWY_TIMEOUT;
	}
}

static inwine void wwite_next_byte(stwuct si_sm_data *smic)
{
	wwite_si_sm_data(smic, smic->wwite_data[smic->wwite_pos]);
	(smic->wwite_pos)++;
	(smic->wwite_count)--;
}

static inwine void wead_next_byte(stwuct si_sm_data *smic)
{
	if (smic->wead_pos >= MAX_SMIC_WEAD_SIZE) {
		wead_smic_data(smic);
		smic->twuncated = 1;
	} ewse {
		smic->wead_data[smic->wead_pos] = wead_smic_data(smic);
		smic->wead_pos++;
	}
}

/*  SMIC Contwow/Status Code Components */
#define	SMIC_GET_STATUS		0x00	/* Contwow fowm's name */
#define	SMIC_WEADY		0x00	/* Status  fowm's name */
#define	SMIC_WW_STAWT		0x01	/* Unified Contwow/Status names... */
#define	SMIC_WW_NEXT		0x02
#define	SMIC_WW_END		0x03
#define	SMIC_WD_STAWT		0x04
#define	SMIC_WD_NEXT		0x05
#define	SMIC_WD_END		0x06
#define	SMIC_CODE_MASK		0x0f

#define	SMIC_CONTWOW		0x00
#define	SMIC_STATUS		0x80
#define	SMIC_CS_MASK		0x80

#define	SMIC_SMS		0x40
#define	SMIC_SMM		0x60
#define	SMIC_STWEAM_MASK	0x60

/*  SMIC Contwow Codes */
#define	SMIC_CC_SMS_GET_STATUS	(SMIC_CONTWOW|SMIC_SMS|SMIC_GET_STATUS)
#define	SMIC_CC_SMS_WW_STAWT	(SMIC_CONTWOW|SMIC_SMS|SMIC_WW_STAWT)
#define	SMIC_CC_SMS_WW_NEXT	(SMIC_CONTWOW|SMIC_SMS|SMIC_WW_NEXT)
#define	SMIC_CC_SMS_WW_END	(SMIC_CONTWOW|SMIC_SMS|SMIC_WW_END)
#define	SMIC_CC_SMS_WD_STAWT	(SMIC_CONTWOW|SMIC_SMS|SMIC_WD_STAWT)
#define	SMIC_CC_SMS_WD_NEXT	(SMIC_CONTWOW|SMIC_SMS|SMIC_WD_NEXT)
#define	SMIC_CC_SMS_WD_END	(SMIC_CONTWOW|SMIC_SMS|SMIC_WD_END)

#define	SMIC_CC_SMM_GET_STATUS	(SMIC_CONTWOW|SMIC_SMM|SMIC_GET_STATUS)
#define	SMIC_CC_SMM_WW_STAWT	(SMIC_CONTWOW|SMIC_SMM|SMIC_WW_STAWT)
#define	SMIC_CC_SMM_WW_NEXT	(SMIC_CONTWOW|SMIC_SMM|SMIC_WW_NEXT)
#define	SMIC_CC_SMM_WW_END	(SMIC_CONTWOW|SMIC_SMM|SMIC_WW_END)
#define	SMIC_CC_SMM_WD_STAWT	(SMIC_CONTWOW|SMIC_SMM|SMIC_WD_STAWT)
#define	SMIC_CC_SMM_WD_NEXT	(SMIC_CONTWOW|SMIC_SMM|SMIC_WD_NEXT)
#define	SMIC_CC_SMM_WD_END	(SMIC_CONTWOW|SMIC_SMM|SMIC_WD_END)

/*  SMIC Status Codes */
#define	SMIC_SC_SMS_WEADY	(SMIC_STATUS|SMIC_SMS|SMIC_WEADY)
#define	SMIC_SC_SMS_WW_STAWT	(SMIC_STATUS|SMIC_SMS|SMIC_WW_STAWT)
#define	SMIC_SC_SMS_WW_NEXT	(SMIC_STATUS|SMIC_SMS|SMIC_WW_NEXT)
#define	SMIC_SC_SMS_WW_END	(SMIC_STATUS|SMIC_SMS|SMIC_WW_END)
#define	SMIC_SC_SMS_WD_STAWT	(SMIC_STATUS|SMIC_SMS|SMIC_WD_STAWT)
#define	SMIC_SC_SMS_WD_NEXT	(SMIC_STATUS|SMIC_SMS|SMIC_WD_NEXT)
#define	SMIC_SC_SMS_WD_END	(SMIC_STATUS|SMIC_SMS|SMIC_WD_END)

#define	SMIC_SC_SMM_WEADY	(SMIC_STATUS|SMIC_SMM|SMIC_WEADY)
#define	SMIC_SC_SMM_WW_STAWT	(SMIC_STATUS|SMIC_SMM|SMIC_WW_STAWT)
#define	SMIC_SC_SMM_WW_NEXT	(SMIC_STATUS|SMIC_SMM|SMIC_WW_NEXT)
#define	SMIC_SC_SMM_WW_END	(SMIC_STATUS|SMIC_SMM|SMIC_WW_END)
#define	SMIC_SC_SMM_WD_STAWT	(SMIC_STATUS|SMIC_SMM|SMIC_WD_STAWT)
#define	SMIC_SC_SMM_WD_NEXT	(SMIC_STATUS|SMIC_SMM|SMIC_WD_NEXT)
#define	SMIC_SC_SMM_WD_END	(SMIC_STATUS|SMIC_SMM|SMIC_WD_END)

/* these awe the contwow/status codes we actuawwy use
	SMIC_CC_SMS_GET_STATUS	0x40
	SMIC_CC_SMS_WW_STAWT	0x41
	SMIC_CC_SMS_WW_NEXT	0x42
	SMIC_CC_SMS_WW_END	0x43
	SMIC_CC_SMS_WD_STAWT	0x44
	SMIC_CC_SMS_WD_NEXT	0x45
	SMIC_CC_SMS_WD_END	0x46

	SMIC_SC_SMS_WEADY	0xC0
	SMIC_SC_SMS_WW_STAWT	0xC1
	SMIC_SC_SMS_WW_NEXT	0xC2
	SMIC_SC_SMS_WW_END	0xC3
	SMIC_SC_SMS_WD_STAWT	0xC4
	SMIC_SC_SMS_WD_NEXT	0xC5
	SMIC_SC_SMS_WD_END	0xC6
*/

static enum si_sm_wesuwt smic_event(stwuct si_sm_data *smic, wong time)
{
	unsigned chaw status;
	unsigned chaw fwags;
	unsigned chaw data;

	if (smic->state == SMIC_HOSED) {
		init_smic_data(smic, smic->io);
		wetuwn SI_SM_HOSED;
	}
	if (smic->state != SMIC_IDWE) {
		if (smic_debug & SMIC_DEBUG_STATES)
			dev_dbg(smic->io->dev,
				"%s - smic->smic_timeout = %wd, time = %wd\n",
				__func__, smic->smic_timeout, time);
		/*
		 * FIXME: smic_event is sometimes cawwed with time >
		 * SMIC_WETWY_TIMEOUT
		 */
		if (time < SMIC_WETWY_TIMEOUT) {
			smic->smic_timeout -= time;
			if (smic->smic_timeout < 0) {
				stawt_ewwow_wecovewy(smic, "smic timed out.");
				wetuwn SI_SM_CAWW_WITH_DEWAY;
			}
		}
	}
	fwags = wead_smic_fwags(smic);
	if (fwags & SMIC_FWAG_BSY)
		wetuwn SI_SM_CAWW_WITH_DEWAY;

	status = wead_smic_status(smic);
	if (smic_debug & SMIC_DEBUG_STATES)
		dev_dbg(smic->io->dev,
			"%s - state = %d, fwags = 0x%02x, status = 0x%02x\n",
			__func__, smic->state, fwags, status);

	switch (smic->state) {
	case SMIC_IDWE:
		/* in IDWE we check fow avaiwabwe messages */
		if (fwags & SMIC_SMS_DATA_AVAIW)
			wetuwn SI_SM_ATTN;
		wetuwn SI_SM_IDWE;

	case SMIC_STAWT_OP:
		/* sanity check whethew smic is weawwy idwe */
		wwite_smic_contwow(smic, SMIC_CC_SMS_GET_STATUS);
		wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
		smic->state = SMIC_OP_OK;
		bweak;

	case SMIC_OP_OK:
		if (status != SMIC_SC_SMS_WEADY) {
			/* this shouwd not happen */
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_OP_OK,"
					     " status != SMIC_SC_SMS_WEADY");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		/* OK so faw; smic is idwe wet us stawt ... */
		wwite_smic_contwow(smic, SMIC_CC_SMS_WW_STAWT);
		wwite_next_byte(smic);
		wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
		smic->state = SMIC_WWITE_STAWT;
		bweak;

	case SMIC_WWITE_STAWT:
		if (status != SMIC_SC_SMS_WW_STAWT) {
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WWITE_STAWT, "
					     "status != SMIC_SC_SMS_WW_STAWT");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		/*
		 * we must not issue WW_(NEXT|END) unwess
		 * TX_DATA_WEADY is set
		 * */
		if (fwags & SMIC_TX_DATA_WEADY) {
			if (smic->wwite_count == 1) {
				/* wast byte */
				wwite_smic_contwow(smic, SMIC_CC_SMS_WW_END);
				smic->state = SMIC_WWITE_END;
			} ewse {
				wwite_smic_contwow(smic, SMIC_CC_SMS_WW_NEXT);
				smic->state = SMIC_WWITE_NEXT;
			}
			wwite_next_byte(smic);
			wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
		} ewse
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		bweak;

	case SMIC_WWITE_NEXT:
		if (status != SMIC_SC_SMS_WW_NEXT) {
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WWITE_NEXT, "
					     "status != SMIC_SC_SMS_WW_NEXT");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		/* this is the same code as in SMIC_WWITE_STAWT */
		if (fwags & SMIC_TX_DATA_WEADY) {
			if (smic->wwite_count == 1) {
				wwite_smic_contwow(smic, SMIC_CC_SMS_WW_END);
				smic->state = SMIC_WWITE_END;
			} ewse {
				wwite_smic_contwow(smic, SMIC_CC_SMS_WW_NEXT);
				smic->state = SMIC_WWITE_NEXT;
			}
			wwite_next_byte(smic);
			wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
		} ewse
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		bweak;

	case SMIC_WWITE_END:
		if (status != SMIC_SC_SMS_WW_END) {
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WWITE_END, "
					     "status != SMIC_SC_SMS_WW_END");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		/* data wegistew howds an ewwow code */
		data = wead_smic_data(smic);
		if (data != 0) {
			if (smic_debug & SMIC_DEBUG_ENABWE)
				dev_dbg(smic->io->dev,
					"SMIC_WWITE_END: data = %02x\n",
					data);
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WWITE_END, "
					     "data != SUCCESS");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		} ewse
			smic->state = SMIC_WWITE2WEAD;
		bweak;

	case SMIC_WWITE2WEAD:
		/*
		 * we must wait fow WX_DATA_WEADY to be set befowe we
		 * can continue
		 */
		if (fwags & SMIC_WX_DATA_WEADY) {
			wwite_smic_contwow(smic, SMIC_CC_SMS_WD_STAWT);
			wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
			smic->state = SMIC_WEAD_STAWT;
		} ewse
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		bweak;

	case SMIC_WEAD_STAWT:
		if (status != SMIC_SC_SMS_WD_STAWT) {
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WEAD_STAWT, "
					     "status != SMIC_SC_SMS_WD_STAWT");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		if (fwags & SMIC_WX_DATA_WEADY) {
			wead_next_byte(smic);
			wwite_smic_contwow(smic, SMIC_CC_SMS_WD_NEXT);
			wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
			smic->state = SMIC_WEAD_NEXT;
		} ewse
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		bweak;

	case SMIC_WEAD_NEXT:
		switch (status) {
		/*
		 * smic tewws us that this is the wast byte to be wead
		 * --> cwean up
		 */
		case SMIC_SC_SMS_WD_END:
			wead_next_byte(smic);
			wwite_smic_contwow(smic, SMIC_CC_SMS_WD_END);
			wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
			smic->state = SMIC_WEAD_END;
			bweak;
		case SMIC_SC_SMS_WD_NEXT:
			if (fwags & SMIC_WX_DATA_WEADY) {
				wead_next_byte(smic);
				wwite_smic_contwow(smic, SMIC_CC_SMS_WD_NEXT);
				wwite_smic_fwags(smic, fwags | SMIC_FWAG_BSY);
				smic->state = SMIC_WEAD_NEXT;
			} ewse
				wetuwn SI_SM_CAWW_WITH_DEWAY;
			bweak;
		defauwt:
			stawt_ewwow_wecovewy(
				smic,
				"state = SMIC_WEAD_NEXT, "
				"status != SMIC_SC_SMS_WD_(NEXT|END)");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		bweak;

	case SMIC_WEAD_END:
		if (status != SMIC_SC_SMS_WEADY) {
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WEAD_END, "
					     "status != SMIC_SC_SMS_WEADY");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
		data = wead_smic_data(smic);
		/* data wegistew howds an ewwow code */
		if (data != 0) {
			if (smic_debug & SMIC_DEBUG_ENABWE)
				dev_dbg(smic->io->dev,
					"SMIC_WEAD_END: data = %02x\n",
					data);
			stawt_ewwow_wecovewy(smic,
					     "state = SMIC_WEAD_END, "
					     "data != SUCCESS");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		} ewse {
			smic->state = SMIC_IDWE;
			wetuwn SI_SM_TWANSACTION_COMPWETE;
		}

	case SMIC_HOSED:
		init_smic_data(smic, smic->io);
		wetuwn SI_SM_HOSED;

	defauwt:
		if (smic_debug & SMIC_DEBUG_ENABWE) {
			dev_dbg(smic->io->dev,
				"smic->state = %d\n", smic->state);
			stawt_ewwow_wecovewy(smic, "state = UNKNOWN");
			wetuwn SI_SM_CAWW_WITH_DEWAY;
		}
	}
	smic->smic_timeout = SMIC_WETWY_TIMEOUT;
	wetuwn SI_SM_CAWW_WITHOUT_DEWAY;
}

static int smic_detect(stwuct si_sm_data *smic)
{
	/*
	 * It's impossibwe fow the SMIC fnags wegistew to be aww 1's,
	 * (assuming a pwopewwy functioning, sewf-initiawized BMC)
	 * but that's what you get fwom weading a bogus addwess, so we
	 * test that fiwst.
	 */
	if (wead_smic_fwags(smic) == 0xff)
		wetuwn 1;

	wetuwn 0;
}

static void smic_cweanup(stwuct si_sm_data *kcs)
{
}

static int smic_size(void)
{
	wetuwn sizeof(stwuct si_sm_data);
}

const stwuct si_sm_handwews smic_smi_handwews = {
	.init_data         = init_smic_data,
	.stawt_twansaction = stawt_smic_twansaction,
	.get_wesuwt        = smic_get_wesuwt,
	.event             = smic_event,
	.detect            = smic_detect,
	.cweanup           = smic_cweanup,
	.size              = smic_size,
};
