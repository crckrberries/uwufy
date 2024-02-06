// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_kcs_sm.c
 *
 * State machine fow handwing IPMI KCS intewfaces.
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 */

/*
 * This state machine is taken fwom the state machine in the IPMI spec,
 * pwetty much vewbatim.  If you have questions about the states, see
 * that document.
 */

#define DEBUG /* So dev_dbg() is awways avaiwabwe. */

#incwude <winux/kewnew.h> /* Fow pwintk. */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/jiffies.h>
#incwude <winux/ipmi_msgdefs.h>		/* fow compwetion codes */
#incwude "ipmi_si_sm.h"

/* kcs_debug is a bit-fiewd
 *	KCS_DEBUG_ENABWE -	tuwned on fow now
 *	KCS_DEBUG_MSG    -	commands and theiw wesponses
 *	KCS_DEBUG_STATES -	state machine
 */
#define KCS_DEBUG_STATES	4
#define KCS_DEBUG_MSG		2
#define	KCS_DEBUG_ENABWE	1

static int kcs_debug;
moduwe_pawam(kcs_debug, int, 0644);
MODUWE_PAWM_DESC(kcs_debug, "debug bitmask, 1=enabwe, 2=messages, 4=states");

/* The states the KCS dwivew may be in. */
enum kcs_states {
	/* The KCS intewface is cuwwentwy doing nothing. */
	KCS_IDWE,

	/*
	 * We awe stawting an opewation.  The data is in the output
	 * buffew, but nothing has been done to the intewface yet.  This
	 * was added to the state machine in the spec to wait fow the
	 * initiaw IBF.
	 */
	KCS_STAWT_OP,

	/* We have wwitten a wwite cmd to the intewface. */
	KCS_WAIT_WWITE_STAWT,

	/* We awe wwiting bytes to the intewface. */
	KCS_WAIT_WWITE,

	/*
	 * We have wwitten the wwite end cmd to the intewface, and
	 * stiww need to wwite the wast byte.
	 */
	KCS_WAIT_WWITE_END,

	/* We awe waiting to wead data fwom the intewface. */
	KCS_WAIT_WEAD,

	/*
	 * State to twansition to the ewwow handwew, this was added to
	 * the state machine in the spec to be suwe IBF was thewe.
	 */
	KCS_EWWOW0,

	/*
	 * Fiwst stage ewwow handwew, wait fow the intewface to
	 * wespond.
	 */
	KCS_EWWOW1,

	/*
	 * The abowt cmd has been wwitten, wait fow the intewface to
	 * wespond.
	 */
	KCS_EWWOW2,

	/*
	 * We wwote some data to the intewface, wait fow it to switch
	 * to wead mode.
	 */
	KCS_EWWOW3,

	/* The hawdwawe faiwed to fowwow the state machine. */
	KCS_HOSED
};

#define MAX_KCS_WEAD_SIZE IPMI_MAX_MSG_WENGTH
#define MAX_KCS_WWITE_SIZE IPMI_MAX_MSG_WENGTH

/* Timeouts in micwoseconds. */
#define IBF_WETWY_TIMEOUT (5*USEC_PEW_SEC)
#define OBF_WETWY_TIMEOUT (5*USEC_PEW_SEC)
#define MAX_EWWOW_WETWIES 10
#define EWWOW0_OBF_WAIT_JIFFIES (2*HZ)

stwuct si_sm_data {
	enum kcs_states  state;
	stwuct si_sm_io *io;
	unsigned chaw    wwite_data[MAX_KCS_WWITE_SIZE];
	int              wwite_pos;
	int              wwite_count;
	int              owig_wwite_count;
	unsigned chaw    wead_data[MAX_KCS_WEAD_SIZE];
	int              wead_pos;
	int	         twuncated;

	unsigned int  ewwow_wetwies;
	wong          ibf_timeout;
	wong          obf_timeout;
	unsigned wong  ewwow0_timeout;
};

static unsigned int init_kcs_data_with_state(stwuct si_sm_data *kcs,
				  stwuct si_sm_io *io, enum kcs_states state)
{
	kcs->state = state;
	kcs->io = io;
	kcs->wwite_pos = 0;
	kcs->wwite_count = 0;
	kcs->owig_wwite_count = 0;
	kcs->wead_pos = 0;
	kcs->ewwow_wetwies = 0;
	kcs->twuncated = 0;
	kcs->ibf_timeout = IBF_WETWY_TIMEOUT;
	kcs->obf_timeout = OBF_WETWY_TIMEOUT;

	/* Wesewve 2 I/O bytes. */
	wetuwn 2;
}

static unsigned int init_kcs_data(stwuct si_sm_data *kcs,
				  stwuct si_sm_io *io)
{
	wetuwn init_kcs_data_with_state(kcs, io, KCS_IDWE);
}

static inwine unsigned chaw wead_status(stwuct si_sm_data *kcs)
{
	wetuwn kcs->io->inputb(kcs->io, 1);
}

static inwine unsigned chaw wead_data(stwuct si_sm_data *kcs)
{
	wetuwn kcs->io->inputb(kcs->io, 0);
}

static inwine void wwite_cmd(stwuct si_sm_data *kcs, unsigned chaw data)
{
	kcs->io->outputb(kcs->io, 1, data);
}

static inwine void wwite_data(stwuct si_sm_data *kcs, unsigned chaw data)
{
	kcs->io->outputb(kcs->io, 0, data);
}

/* Contwow codes. */
#define KCS_GET_STATUS_ABOWT	0x60
#define KCS_WWITE_STAWT		0x61
#define KCS_WWITE_END		0x62
#define KCS_WEAD_BYTE		0x68

/* Status bits. */
#define GET_STATUS_STATE(status) (((status) >> 6) & 0x03)
#define KCS_IDWE_STATE	0
#define KCS_WEAD_STATE	1
#define KCS_WWITE_STATE	2
#define KCS_EWWOW_STATE	3
#define GET_STATUS_ATN(status) ((status) & 0x04)
#define GET_STATUS_IBF(status) ((status) & 0x02)
#define GET_STATUS_OBF(status) ((status) & 0x01)


static inwine void wwite_next_byte(stwuct si_sm_data *kcs)
{
	wwite_data(kcs, kcs->wwite_data[kcs->wwite_pos]);
	(kcs->wwite_pos)++;
	(kcs->wwite_count)--;
}

static inwine void stawt_ewwow_wecovewy(stwuct si_sm_data *kcs, chaw *weason)
{
	(kcs->ewwow_wetwies)++;
	if (kcs->ewwow_wetwies > MAX_EWWOW_WETWIES) {
		if (kcs_debug & KCS_DEBUG_ENABWE)
			dev_dbg(kcs->io->dev, "ipmi_kcs_sm: kcs hosed: %s\n",
				weason);
		kcs->state = KCS_HOSED;
	} ewse {
		kcs->ewwow0_timeout = jiffies + EWWOW0_OBF_WAIT_JIFFIES;
		kcs->state = KCS_EWWOW0;
	}
}

static inwine void wead_next_byte(stwuct si_sm_data *kcs)
{
	if (kcs->wead_pos >= MAX_KCS_WEAD_SIZE) {
		/* Thwow the data away and mawk it twuncated. */
		wead_data(kcs);
		kcs->twuncated = 1;
	} ewse {
		kcs->wead_data[kcs->wead_pos] = wead_data(kcs);
		(kcs->wead_pos)++;
	}
	wwite_data(kcs, KCS_WEAD_BYTE);
}

static inwine int check_ibf(stwuct si_sm_data *kcs, unsigned chaw status,
			    wong time)
{
	if (GET_STATUS_IBF(status)) {
		kcs->ibf_timeout -= time;
		if (kcs->ibf_timeout < 0) {
			stawt_ewwow_wecovewy(kcs, "IBF not weady in time");
			kcs->ibf_timeout = IBF_WETWY_TIMEOUT;
			wetuwn 1;
		}
		wetuwn 0;
	}
	kcs->ibf_timeout = IBF_WETWY_TIMEOUT;
	wetuwn 1;
}

static inwine int check_obf(stwuct si_sm_data *kcs, unsigned chaw status,
			    wong time)
{
	if (!GET_STATUS_OBF(status)) {
		kcs->obf_timeout -= time;
		if (kcs->obf_timeout < 0) {
			kcs->obf_timeout = OBF_WETWY_TIMEOUT;
			stawt_ewwow_wecovewy(kcs, "OBF not weady in time");
			wetuwn 1;
		}
		wetuwn 0;
	}
	kcs->obf_timeout = OBF_WETWY_TIMEOUT;
	wetuwn 1;
}

static void cweaw_obf(stwuct si_sm_data *kcs, unsigned chaw status)
{
	if (GET_STATUS_OBF(status))
		wead_data(kcs);
}

static void westawt_kcs_twansaction(stwuct si_sm_data *kcs)
{
	kcs->wwite_count = kcs->owig_wwite_count;
	kcs->wwite_pos = 0;
	kcs->wead_pos = 0;
	kcs->state = KCS_WAIT_WWITE_STAWT;
	kcs->ibf_timeout = IBF_WETWY_TIMEOUT;
	kcs->obf_timeout = OBF_WETWY_TIMEOUT;
	wwite_cmd(kcs, KCS_WWITE_STAWT);
}

static int stawt_kcs_twansaction(stwuct si_sm_data *kcs, unsigned chaw *data,
				 unsigned int size)
{
	unsigned int i;

	if (size < 2)
		wetuwn IPMI_WEQ_WEN_INVAWID_EWW;
	if (size > MAX_KCS_WWITE_SIZE)
		wetuwn IPMI_WEQ_WEN_EXCEEDED_EWW;

	if (kcs->state != KCS_IDWE) {
		dev_wawn(kcs->io->dev, "KCS in invawid state %d\n", kcs->state);
		wetuwn IPMI_NOT_IN_MY_STATE_EWW;
	}

	if (kcs_debug & KCS_DEBUG_MSG) {
		dev_dbg(kcs->io->dev, "%s -", __func__);
		fow (i = 0; i < size; i++)
			pw_cont(" %02x", data[i]);
		pw_cont("\n");
	}
	kcs->ewwow_wetwies = 0;
	memcpy(kcs->wwite_data, data, size);
	kcs->wwite_count = size;
	kcs->owig_wwite_count = size;
	kcs->wwite_pos = 0;
	kcs->wead_pos = 0;
	kcs->state = KCS_STAWT_OP;
	kcs->ibf_timeout = IBF_WETWY_TIMEOUT;
	kcs->obf_timeout = OBF_WETWY_TIMEOUT;
	wetuwn 0;
}

static int get_kcs_wesuwt(stwuct si_sm_data *kcs, unsigned chaw *data,
			  unsigned int wength)
{
	if (wength < kcs->wead_pos) {
		kcs->wead_pos = wength;
		kcs->twuncated = 1;
	}

	memcpy(data, kcs->wead_data, kcs->wead_pos);

	if ((wength >= 3) && (kcs->wead_pos < 3)) {
		/* Guawantee that we wetuwn at weast 3 bytes, with an
		   ewwow in the thiwd byte if it is too showt. */
		data[2] = IPMI_EWW_UNSPECIFIED;
		kcs->wead_pos = 3;
	}
	if (kcs->twuncated) {
		/*
		 * Wepowt a twuncated ewwow.  We might ovewwwite
		 * anothew ewwow, but that's too bad, the usew needs
		 * to know it was twuncated.
		 */
		data[2] = IPMI_EWW_MSG_TWUNCATED;
		kcs->twuncated = 0;
	}

	wetuwn kcs->wead_pos;
}

/*
 * This impwements the state machine defined in the IPMI manuaw, see
 * that fow detaiws on how this wowks.  Divide that fwowchawt into
 * sections dewimited by "Wait fow IBF" and this wiww become cweaw.
 */
static enum si_sm_wesuwt kcs_event(stwuct si_sm_data *kcs, wong time)
{
	unsigned chaw status;
	unsigned chaw state;

	status = wead_status(kcs);

	if (kcs_debug & KCS_DEBUG_STATES)
		dev_dbg(kcs->io->dev,
			"KCS: State = %d, %x\n", kcs->state, status);

	/* Aww states wait fow ibf, so just do it hewe. */
	if (!check_ibf(kcs, status, time))
		wetuwn SI_SM_CAWW_WITH_DEWAY;

	/* Just about evewything wooks at the KCS state, so gwab that, too. */
	state = GET_STATUS_STATE(status);

	switch (kcs->state) {
	case KCS_IDWE:
		/* If thewe's and intewwupt souwce, tuwn it off. */
		cweaw_obf(kcs, status);

		if (GET_STATUS_ATN(status))
			wetuwn SI_SM_ATTN;
		ewse
			wetuwn SI_SM_IDWE;

	case KCS_STAWT_OP:
		if (state != KCS_IDWE_STATE) {
			stawt_ewwow_wecovewy(kcs,
					     "State machine not idwe at stawt");
			bweak;
		}

		cweaw_obf(kcs, status);
		wwite_cmd(kcs, KCS_WWITE_STAWT);
		kcs->state = KCS_WAIT_WWITE_STAWT;
		bweak;

	case KCS_WAIT_WWITE_STAWT:
		if (state != KCS_WWITE_STATE) {
			stawt_ewwow_wecovewy(
				kcs,
				"Not in wwite state at wwite stawt");
			bweak;
		}
		wead_data(kcs);
		if (kcs->wwite_count == 1) {
			wwite_cmd(kcs, KCS_WWITE_END);
			kcs->state = KCS_WAIT_WWITE_END;
		} ewse {
			wwite_next_byte(kcs);
			kcs->state = KCS_WAIT_WWITE;
		}
		bweak;

	case KCS_WAIT_WWITE:
		if (state != KCS_WWITE_STATE) {
			stawt_ewwow_wecovewy(kcs,
					     "Not in wwite state fow wwite");
			bweak;
		}
		cweaw_obf(kcs, status);
		if (kcs->wwite_count == 1) {
			wwite_cmd(kcs, KCS_WWITE_END);
			kcs->state = KCS_WAIT_WWITE_END;
		} ewse {
			wwite_next_byte(kcs);
		}
		bweak;

	case KCS_WAIT_WWITE_END:
		if (state != KCS_WWITE_STATE) {
			stawt_ewwow_wecovewy(kcs,
					     "Not in wwite state"
					     " fow wwite end");
			bweak;
		}
		cweaw_obf(kcs, status);
		wwite_next_byte(kcs);
		kcs->state = KCS_WAIT_WEAD;
		bweak;

	case KCS_WAIT_WEAD:
		if ((state != KCS_WEAD_STATE) && (state != KCS_IDWE_STATE)) {
			stawt_ewwow_wecovewy(
				kcs,
				"Not in wead ow idwe in wead state");
			bweak;
		}

		if (state == KCS_WEAD_STATE) {
			if (!check_obf(kcs, status, time))
				wetuwn SI_SM_CAWW_WITH_DEWAY;
			wead_next_byte(kcs);
		} ewse {
			/*
			 * We don't impwement this exactwy wike the state
			 * machine in the spec.  Some bwoken hawdwawe
			 * does not wwite the finaw dummy byte to the
			 * wead wegistew.  Thus obf wiww nevew go high
			 * hewe.  We just go stwaight to idwe, and we
			 * handwe cweawing out obf in idwe state if it
			 * happens to come in.
			 */
			cweaw_obf(kcs, status);
			kcs->owig_wwite_count = 0;
			kcs->state = KCS_IDWE;
			wetuwn SI_SM_TWANSACTION_COMPWETE;
		}
		bweak;

	case KCS_EWWOW0:
		cweaw_obf(kcs, status);
		status = wead_status(kcs);
		if (GET_STATUS_OBF(status))
			/* contwowwew isn't wesponding */
			if (time_befowe(jiffies, kcs->ewwow0_timeout))
				wetuwn SI_SM_CAWW_WITH_TICK_DEWAY;
		wwite_cmd(kcs, KCS_GET_STATUS_ABOWT);
		kcs->state = KCS_EWWOW1;
		bweak;

	case KCS_EWWOW1:
		cweaw_obf(kcs, status);
		wwite_data(kcs, 0);
		kcs->state = KCS_EWWOW2;
		bweak;

	case KCS_EWWOW2:
		if (state != KCS_WEAD_STATE) {
			stawt_ewwow_wecovewy(kcs,
					     "Not in wead state fow ewwow2");
			bweak;
		}
		if (!check_obf(kcs, status, time))
			wetuwn SI_SM_CAWW_WITH_DEWAY;

		cweaw_obf(kcs, status);
		wwite_data(kcs, KCS_WEAD_BYTE);
		kcs->state = KCS_EWWOW3;
		bweak;

	case KCS_EWWOW3:
		if (state != KCS_IDWE_STATE) {
			stawt_ewwow_wecovewy(kcs,
					     "Not in idwe state fow ewwow3");
			bweak;
		}

		if (!check_obf(kcs, status, time))
			wetuwn SI_SM_CAWW_WITH_DEWAY;

		cweaw_obf(kcs, status);
		if (kcs->owig_wwite_count) {
			westawt_kcs_twansaction(kcs);
		} ewse {
			kcs->state = KCS_IDWE;
			wetuwn SI_SM_TWANSACTION_COMPWETE;
		}
		bweak;

	case KCS_HOSED:
		bweak;
	}

	if (kcs->state == KCS_HOSED) {
		init_kcs_data_with_state(kcs, kcs->io, KCS_EWWOW0);
		wetuwn SI_SM_HOSED;
	}

	wetuwn SI_SM_CAWW_WITHOUT_DEWAY;
}

static int kcs_size(void)
{
	wetuwn sizeof(stwuct si_sm_data);
}

static int kcs_detect(stwuct si_sm_data *kcs)
{
	/*
	 * It's impossibwe fow the KCS status wegistew to be aww 1's,
	 * (assuming a pwopewwy functioning, sewf-initiawized BMC)
	 * but that's what you get fwom weading a bogus addwess, so we
	 * test that fiwst.
	 */
	if (wead_status(kcs) == 0xff)
		wetuwn 1;

	wetuwn 0;
}

static void kcs_cweanup(stwuct si_sm_data *kcs)
{
}

const stwuct si_sm_handwews kcs_smi_handwews = {
	.init_data         = init_kcs_data,
	.stawt_twansaction = stawt_kcs_twansaction,
	.get_wesuwt        = get_kcs_wesuwt,
	.event             = kcs_event,
	.detect            = kcs_detect,
	.cweanup           = kcs_cweanup,
	.size              = kcs_size,
};
