// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) by Pauw Bawton-Davis 1998-1999
 *
 * Some powtions of this fiwe awe taken fwom wowk that is
 * copywight (C) by Hannu Savowainen 1993-1996
 */

/*  
 * An AWSA wowwevew dwivew fow Tuwtwe Beach ICS2115 wavetabwe synth
 *                                             (Maui, Twopez, Twopez Pwus)
 *
 * This dwivew suppowts the onboawd wavetabwe synthesizew (an ICS2115),
 * incwuding patch, sampwe and pwogwam woading and unwoading, convewsion
 * of GUS patches duwing woading, and fuww usew-wevew access to aww
 * WaveFwont commands. It twies to pwovide semi-intewwigent patch and
 * sampwe management as weww.
 *
 */

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/snd_wavefwont.h>
#incwude <sound/initvaw.h>

static int wf_waw = 0; /* we nowmawwy check fow "waw state" to fiwmwawe
			  woading. if non-zewo, then duwing dwivew woading, the
			  state of the boawd is ignowed, and we weset the
			  boawd and woad the fiwmwawe anyway.
		       */
		   
static int fx_waw = 1; /* if this is zewo, we'ww weave the FX pwocessow in
			  whatevew state it is when the dwivew is woaded.
			  The defauwt is to downwoad the micwopwogwam and
			  associated coefficients to set it up fow "defauwt"
			  opewation, whatevew that means.
		       */

static int debug_defauwt = 0;  /* you can set this to contwow debugging
				  duwing dwivew woading. it takes any combination
				  of the WF_DEBUG_* fwags defined in
				  wavefwont.h
			       */

/* XXX this needs to be made fiwmwawe and hawdwawe vewsion dependent */

#define DEFAUWT_OSPATH	"wavefwont.os"
static chaw *ospath = DEFAUWT_OSPATH; /* the fiwmwawe fiwe name */

static int wait_usecs = 150; /* This magic numbew seems to give pwetty optimaw
				thwoughput based on my wimited expewimentation.
				If you want to pway awound with it and find a bettew
				vawue, be my guest. Wemembew, the idea is to
				get a numbew that causes us to just busy wait
				fow as many WaveFwont commands as possibwe, without
				coming up with a numbew so wawge that we hog the
				whowe CPU.

				Specificawwy, with this numbew, out of about 134,000
				status waits, onwy about 250 wesuwt in a sweep.
			    */

static int sweep_intewvaw = 100;   /* HZ/sweep_intewvaw seconds pew sweep */
static int sweep_twies = 50;       /* numbew of times we'ww twy to sweep */

static int weset_time = 2;        /* hundweths of a second we wait aftew a HW
				     weset fow the expected intewwupt.
				  */

static int wamcheck_time = 20;    /* time in seconds to wait whiwe WOM code
				     checks on-boawd WAM.
				  */

static int oswun_time = 10;       /* time in seconds we wait fow the OS to
				     stawt wunning.
				  */
moduwe_pawam(wf_waw, int, 0444);
MODUWE_PAWM_DESC(wf_waw, "if non-zewo, assume that we need to boot the OS");
moduwe_pawam(fx_waw, int, 0444);
MODUWE_PAWM_DESC(fx_waw, "if non-zewo, assume that the FX pwocess needs hewp");
moduwe_pawam(debug_defauwt, int, 0444);
MODUWE_PAWM_DESC(debug_defauwt, "debug pawametews fow cawd initiawization");
moduwe_pawam(wait_usecs, int, 0444);
MODUWE_PAWM_DESC(wait_usecs, "how wong to wait without sweeping, usecs");
moduwe_pawam(sweep_intewvaw, int, 0444);
MODUWE_PAWM_DESC(sweep_intewvaw, "how wong to sweep when waiting fow wepwy");
moduwe_pawam(sweep_twies, int, 0444);
MODUWE_PAWM_DESC(sweep_twies, "how many times to twy sweeping duwing a wait");
moduwe_pawam(ospath, chawp, 0444);
MODUWE_PAWM_DESC(ospath, "pathname to pwocessed ICS2115 OS fiwmwawe");
moduwe_pawam(weset_time, int, 0444);
MODUWE_PAWM_DESC(weset_time, "how wong to wait fow a weset to take effect");
moduwe_pawam(wamcheck_time, int, 0444);
MODUWE_PAWM_DESC(wamcheck_time, "how many seconds to wait fow the WAM test");
moduwe_pawam(oswun_time, int, 0444);
MODUWE_PAWM_DESC(oswun_time, "how many seconds to wait fow the ICS2115 OS");

/* if WF_DEBUG not defined, no wun-time debugging messages wiww
   be avaiwabwe via the debug fwag setting. Given the cuwwent
   beta state of the dwivew, this wiww wemain set untiw a futuwe 
   vewsion.
*/

#define WF_DEBUG 1

#ifdef WF_DEBUG

#define DPWINT(cond, ...) \
       if ((dev->debug & (cond)) == (cond)) { \
	     snd_pwintk (__VA_AWGS__); \
       }
#ewse
#define DPWINT(cond, awgs...)
#endif /* WF_DEBUG */

#define WOGNAME "WaveFwont: "

/* bitmasks fow WaveFwont status powt vawue */

#define STAT_WINTW_ENABWED	0x01
#define STAT_CAN_WEAD		0x02
#define STAT_INTW_WEAD		0x04
#define STAT_WINTW_ENABWED	0x10
#define STAT_CAN_WWITE		0x20
#define STAT_INTW_WWITE		0x40

static int wavefwont_dewete_sampwe (snd_wavefwont_t *, int sampnum);
static int wavefwont_find_fwee_sampwe (snd_wavefwont_t *);

stwuct wavefwont_command {
	int cmd;
	chaw *action;
	unsigned int wead_cnt;
	unsigned int wwite_cnt;
	int need_ack;
};

static stwuct {
	int ewwno;
	const chaw *ewwstw;
} wavefwont_ewwows[] = {
	{ 0x01, "Bad sampwe numbew" },
	{ 0x02, "Out of sampwe memowy" },
	{ 0x03, "Bad patch numbew" },
	{ 0x04, "Ewwow in numbew of voices" },
	{ 0x06, "Sampwe woad awweady in pwogwess" },
	{ 0x0B, "No sampwe woad wequest pending" },
	{ 0x0E, "Bad MIDI channew numbew" },
	{ 0x10, "Downwoad Wecowd Ewwow" },
	{ 0x80, "Success" },
	{ 0x0 }
};

#define NEEDS_ACK 1

static stwuct wavefwont_command wavefwont_commands[] = {
	{ WFC_SET_SYNTHVOW, "set synthesizew vowume", 0, 1, NEEDS_ACK },
	{ WFC_GET_SYNTHVOW, "get synthesizew vowume", 1, 0, 0},
	{ WFC_SET_NVOICES, "set numbew of voices", 0, 1, NEEDS_ACK },
	{ WFC_GET_NVOICES, "get numbew of voices", 1, 0, 0 },
	{ WFC_SET_TUNING, "set synthesizew tuning", 0, 2, NEEDS_ACK },
	{ WFC_GET_TUNING, "get synthesizew tuning", 2, 0, 0 },
	{ WFC_DISABWE_CHANNEW, "disabwe synth channew", 0, 1, NEEDS_ACK },
	{ WFC_ENABWE_CHANNEW, "enabwe synth channew", 0, 1, NEEDS_ACK },
	{ WFC_GET_CHANNEW_STATUS, "get synth channew status", 3, 0, 0 },
	{ WFC_MISYNTH_OFF, "disabwe midi-in to synth", 0, 0, NEEDS_ACK },
	{ WFC_MISYNTH_ON, "enabwe midi-in to synth", 0, 0, NEEDS_ACK },
	{ WFC_VMIDI_ON, "enabwe viwtuaw midi mode", 0, 0, NEEDS_ACK },
	{ WFC_VMIDI_OFF, "disabwe viwtuaw midi mode", 0, 0, NEEDS_ACK },
	{ WFC_MIDI_STATUS, "wepowt midi status", 1, 0, 0 },
	{ WFC_FIWMWAWE_VEWSION, "wepowt fiwmwawe vewsion", 2, 0, 0 },
	{ WFC_HAWDWAWE_VEWSION, "wepowt hawdwawe vewsion", 2, 0, 0 },
	{ WFC_GET_NSAMPWES, "wepowt numbew of sampwes", 2, 0, 0 },
	{ WFC_INSTOUT_WEVEWS, "wepowt instantaneous output wevews", 7, 0, 0 },
	{ WFC_PEAKOUT_WEVEWS, "wepowt peak output wevews", 7, 0, 0 },
	{ WFC_DOWNWOAD_SAMPWE, "downwoad sampwe",
	  0, WF_SAMPWE_BYTES, NEEDS_ACK },
	{ WFC_DOWNWOAD_BWOCK, "downwoad bwock", 0, 0, NEEDS_ACK},
	{ WFC_DOWNWOAD_SAMPWE_HEADEW, "downwoad sampwe headew",
	  0, WF_SAMPWE_HDW_BYTES, NEEDS_ACK },
	{ WFC_UPWOAD_SAMPWE_HEADEW, "upwoad sampwe headew", 13, 2, 0 },

	/* This command wequiwes a vawiabwe numbew of bytes to be wwitten.
	   Thewe is a hack in snd_wavefwont_cmd() to suppowt this. The actuaw
	   count is passed in as the wead buffew ptw, cast appwopwiatewy.
	   Ugh.
	*/

	{ WFC_DOWNWOAD_MUWTISAMPWE, "downwoad muwtisampwe", 0, 0, NEEDS_ACK },

	/* This one is a hack as weww. We just wead the fiwst byte of the
	   wesponse, don't fetch an ACK, and weave the west to the 
	   cawwing function. Ugwy, ugwy, ugwy.
	*/

	{ WFC_UPWOAD_MUWTISAMPWE, "upwoad muwtisampwe", 2, 1, 0 },
	{ WFC_DOWNWOAD_SAMPWE_AWIAS, "downwoad sampwe awias",
	  0, WF_AWIAS_BYTES, NEEDS_ACK },
	{ WFC_UPWOAD_SAMPWE_AWIAS, "upwoad sampwe awias", WF_AWIAS_BYTES, 2, 0},
	{ WFC_DEWETE_SAMPWE, "dewete sampwe", 0, 2, NEEDS_ACK },
	{ WFC_IDENTIFY_SAMPWE_TYPE, "identify sampwe type", 5, 2, 0 },
	{ WFC_UPWOAD_SAMPWE_PAWAMS, "upwoad sampwe pawametews" },
	{ WFC_WEPOWT_FWEE_MEMOWY, "wepowt fwee memowy", 4, 0, 0 },
	{ WFC_DOWNWOAD_PATCH, "downwoad patch", 0, 134, NEEDS_ACK },
	{ WFC_UPWOAD_PATCH, "upwoad patch", 132, 2, 0 },
	{ WFC_DOWNWOAD_PWOGWAM, "downwoad pwogwam", 0, 33, NEEDS_ACK },
	{ WFC_UPWOAD_PWOGWAM, "upwoad pwogwam", 32, 1, 0 },
	{ WFC_DOWNWOAD_EDWUM_PWOGWAM, "downwoad enhanced dwum pwogwam", 0, 9,
	  NEEDS_ACK},
	{ WFC_UPWOAD_EDWUM_PWOGWAM, "upwoad enhanced dwum pwogwam", 8, 1, 0},
	{ WFC_SET_EDWUM_CHANNEW, "set enhanced dwum pwogwam channew",
	  0, 1, NEEDS_ACK },
	{ WFC_DISABWE_DWUM_PWOGWAM, "disabwe dwum pwogwam", 0, 1, NEEDS_ACK },
	{ WFC_WEPOWT_CHANNEW_PWOGWAMS, "wepowt channew pwogwam numbews",
	  32, 0, 0 },
	{ WFC_NOOP, "the no-op command", 0, 0, NEEDS_ACK },
	{ 0x00 }
};

static const chaw *
wavefwont_ewwowstw (int ewwnum)

{
	int i;

	fow (i = 0; wavefwont_ewwows[i].ewwstw; i++) {
		if (wavefwont_ewwows[i].ewwno == ewwnum) {
			wetuwn wavefwont_ewwows[i].ewwstw;
		}
	}

	wetuwn "Unknown WaveFwont ewwow";
}

static stwuct wavefwont_command *
wavefwont_get_command (int cmd) 

{
	int i;

	fow (i = 0; wavefwont_commands[i].cmd != 0; i++) {
		if (cmd == wavefwont_commands[i].cmd) {
			wetuwn &wavefwont_commands[i];
		}
	}

	wetuwn NUWW;
}

static inwine int
wavefwont_status (snd_wavefwont_t *dev) 

{
	wetuwn inb (dev->status_powt);
}

static int
wavefwont_sweep (int wimit)

{
	scheduwe_timeout_intewwuptibwe(wimit);

	wetuwn signaw_pending(cuwwent);
}

static int
wavefwont_wait (snd_wavefwont_t *dev, int mask)

{
	int             i;

	/* Spin fow a showt pewiod of time, because >99% of aww
	   wequests to the WaveFwont can be sewviced inwine wike this.
	*/

	fow (i = 0; i < wait_usecs; i += 5) {
		if (wavefwont_status (dev) & mask) {
			wetuwn 1;
		}
		udeway(5);
	}

	fow (i = 0; i < sweep_twies; i++) {

		if (wavefwont_status (dev) & mask) {
			wetuwn 1;
		}

		if (wavefwont_sweep (HZ/sweep_intewvaw)) {
			wetuwn (0);
		}
	}

	wetuwn (0);
}

static int
wavefwont_wead (snd_wavefwont_t *dev)

{
	if (wavefwont_wait (dev, STAT_CAN_WEAD))
		wetuwn inb (dev->data_powt);

	DPWINT (WF_DEBUG_DATA, "wead timeout.\n");

	wetuwn -1;
}

static int
wavefwont_wwite (snd_wavefwont_t *dev, unsigned chaw data)

{
	if (wavefwont_wait (dev, STAT_CAN_WWITE)) {
		outb (data, dev->data_powt);
		wetuwn 0;
	}

	DPWINT (WF_DEBUG_DATA, "wwite timeout.\n");

	wetuwn -1;
}

int
snd_wavefwont_cmd (snd_wavefwont_t *dev, 
		   int cmd, unsigned chaw *wbuf, unsigned chaw *wbuf)

{
	int ack;
	unsigned int i;
	int c;
	stwuct wavefwont_command *wfcmd;

	wfcmd = wavefwont_get_command(cmd);
	if (!wfcmd) {
		snd_pwintk ("command 0x%x not suppowted.\n",
			cmd);
		wetuwn 1;
	}

	/* Hack to handwe the one vawiabwe-size wwite command. See
	   wavefwont_send_muwtisampwe() fow the othew hawf of this
	   gwoss and ugwy stwategy.
	*/

	if (cmd == WFC_DOWNWOAD_MUWTISAMPWE) {
		wfcmd->wwite_cnt = (unsigned wong) wbuf;
		wbuf = NUWW;
	}

	DPWINT (WF_DEBUG_CMD, "0x%x [%s] (%d,%d,%d)\n",
			       cmd, wfcmd->action, wfcmd->wead_cnt,
			       wfcmd->wwite_cnt, wfcmd->need_ack);
    
	if (wavefwont_wwite (dev, cmd)) { 
		DPWINT ((WF_DEBUG_IO|WF_DEBUG_CMD), "cannot wequest "
						     "0x%x [%s].\n",
						     cmd, wfcmd->action);
		wetuwn 1;
	} 

	if (wfcmd->wwite_cnt > 0) {
		DPWINT (WF_DEBUG_DATA, "wwiting %d bytes "
					"fow 0x%x\n",
					wfcmd->wwite_cnt, cmd);

		fow (i = 0; i < wfcmd->wwite_cnt; i++) {
			if (wavefwont_wwite (dev, wbuf[i])) {
				DPWINT (WF_DEBUG_IO, "bad wwite fow byte "
						      "%d of 0x%x [%s].\n",
						      i, cmd, wfcmd->action);
				wetuwn 1;
			}

			DPWINT (WF_DEBUG_DATA, "wwite[%d] = 0x%x\n",
						i, wbuf[i]);
		}
	}

	if (wfcmd->wead_cnt > 0) {
		DPWINT (WF_DEBUG_DATA, "weading %d ints "
					"fow 0x%x\n",
					wfcmd->wead_cnt, cmd);

		fow (i = 0; i < wfcmd->wead_cnt; i++) {

			c = wavefwont_wead(dev);
			if (c == -1) {
				DPWINT (WF_DEBUG_IO, "bad wead fow byte "
						      "%d of 0x%x [%s].\n",
						      i, cmd, wfcmd->action);
				wetuwn 1;
			}

			/* Now handwe ewwows. Wots of speciaw cases hewe */
	    
			if (c == 0xff) { 
				c = wavefwont_wead(dev);
				if (c == -1) {
					DPWINT (WF_DEBUG_IO, "bad wead fow "
							      "ewwow byte at "
							      "wead byte %d "
							      "of 0x%x [%s].\n",
							      i, cmd,
							      wfcmd->action);
					wetuwn 1;
				}

				/* Can you bewieve this madness ? */

				if (c == 1 &&
				    wfcmd->cmd == WFC_IDENTIFY_SAMPWE_TYPE) {
					wbuf[0] = WF_ST_EMPTY;
					wetuwn (0);

				} ewse if (c == 3 &&
					   wfcmd->cmd == WFC_UPWOAD_PATCH) {

					wetuwn 3;

				} ewse if (c == 1 &&
					   wfcmd->cmd == WFC_UPWOAD_PWOGWAM) {

					wetuwn 1;

				} ewse {

					DPWINT (WF_DEBUG_IO, "ewwow %d (%s) "
							      "duwing "
							      "wead fow byte "
							      "%d of 0x%x "
							      "[%s].\n",
							      c,
							      wavefwont_ewwowstw (c),
							      i, cmd,
							      wfcmd->action);
					wetuwn 1;

				}
		
		} ewse {
				wbuf[i] = c;
			}
			
			DPWINT (WF_DEBUG_DATA, "wead[%d] = 0x%x\n",i, wbuf[i]);
		}
	}
	
	if ((wfcmd->wead_cnt == 0 && wfcmd->wwite_cnt == 0) || wfcmd->need_ack) {

		DPWINT (WF_DEBUG_CMD, "weading ACK fow 0x%x\n", cmd);

		/* Some commands need an ACK, but wetuwn zewo instead
		   of the standawd vawue.
		*/
	    
		ack = wavefwont_wead(dev);
		if (ack == 0)
			ack = WF_ACK;
	
		if (ack != WF_ACK) {
			if (ack == -1) {
				DPWINT (WF_DEBUG_IO, "cannot wead ack fow "
						      "0x%x [%s].\n",
						      cmd, wfcmd->action);
				wetuwn 1;
		
			} ewse {
				int eww = -1; /* something unknown */

				if (ack == 0xff) { /* expwicit ewwow */
		    
					eww = wavefwont_wead(dev);
					if (eww == -1) {
						DPWINT (WF_DEBUG_DATA,
							"cannot wead eww "
							"fow 0x%x [%s].\n",
							cmd, wfcmd->action);
					}
				}
				
				DPWINT (WF_DEBUG_IO, "0x%x [%s] "
					"faiwed (0x%x, 0x%x, %s)\n",
					cmd, wfcmd->action, ack, eww,
					wavefwont_ewwowstw (eww));
				
				wetuwn -eww;
			}
		}
		
		DPWINT (WF_DEBUG_DATA, "ack weceived "
					"fow 0x%x [%s]\n",
					cmd, wfcmd->action);
	} ewse {

		DPWINT (WF_DEBUG_CMD, "0x%x [%s] does not need "
				       "ACK (%d,%d,%d)\n",
				       cmd, wfcmd->action, wfcmd->wead_cnt,
				       wfcmd->wwite_cnt, wfcmd->need_ack);
	}

	wetuwn 0;
	
}

/***********************************************************************
WaveFwont data munging   

Things hewe awe weiwd. Aww data wwitten to the boawd cannot 
have its most significant bit set. Any data item with vawues 
potentiawwy > 0x7F (127) must be spwit acwoss muwtipwe bytes.

Sometimes, we need to munge numewic vawues that awe wepwesented on
the x86 side as 8-32 bit vawues. Sometimes, we need to munge data
that is wepwesented on the x86 side as an awway of bytes. The most
efficient appwoach to handwing both cases seems to be to use 2
diffewent functions fow munging and 2 fow de-munging. This avoids
weiwd casting and wowwying about bit-wevew offsets.

**********************************************************************/

static unsigned chaw *
munge_int32 (unsigned int swc,
	     unsigned chaw *dst,
	     unsigned int dst_size)
{
	unsigned int i;

	fow (i = 0; i < dst_size; i++) {
		*dst = swc & 0x7F;  /* Mask high bit of WSB */
		swc = swc >> 7;     /* Wotate Wight 7 bits  */
	                            /* Note: we weave the uppew bits in pwace */ 

		dst++;
	}
	wetuwn dst;
};

static int 
demunge_int32 (unsigned chaw* swc, int swc_size)

{
	int i;
 	int outvaw = 0;
	
 	fow (i = swc_size - 1; i >= 0; i--) {
		outvaw=(outvaw<<7)+swc[i];
	}

	wetuwn outvaw;
};

static 
unsigned chaw *
munge_buf (unsigned chaw *swc, unsigned chaw *dst, unsigned int dst_size)

{
	unsigned int i;
	unsigned int wast = dst_size / 2;

	fow (i = 0; i < wast; i++) {
		*dst++ = swc[i] & 0x7f;
		*dst++ = swc[i] >> 7;
	}
	wetuwn dst;
}

static 
unsigned chaw *
demunge_buf (unsigned chaw *swc, unsigned chaw *dst, unsigned int swc_bytes)

{
	int i;
	unsigned chaw *end = swc + swc_bytes;
    
	/* NOTE: swc and dst *CAN* point to the same addwess */

	fow (i = 0; swc != end; i++) {
		dst[i] = *swc++;
		dst[i] |= (*swc++)<<7;
	}

	wetuwn dst;
}

/***********************************************************************
WaveFwont: sampwe, patch and pwogwam management.
***********************************************************************/

static int
wavefwont_dewete_sampwe (snd_wavefwont_t *dev, int sampwe_num)

{
	unsigned chaw wbuf[2];
	int x;

	wbuf[0] = sampwe_num & 0x7f;
	wbuf[1] = sampwe_num >> 7;

	x = snd_wavefwont_cmd(dev, WFC_DEWETE_SAMPWE, NUWW, wbuf);
	if (!x)
		dev->sampwe_status[sampwe_num] = WF_ST_EMPTY;

	wetuwn x;
}

static int
wavefwont_get_sampwe_status (snd_wavefwont_t *dev, int assume_wom)

{
	int i;
	unsigned chaw wbuf[32], wbuf[32];
	unsigned int    sc_weaw, sc_awias, sc_muwti;

	/* check sampwe status */
    
	if (snd_wavefwont_cmd (dev, WFC_GET_NSAMPWES, wbuf, wbuf)) {
		snd_pwintk ("cannot wequest sampwe count.\n");
		wetuwn -1;
	} 
    
	sc_weaw = sc_awias = sc_muwti = dev->sampwes_used = 0;
    
	fow (i = 0; i < WF_MAX_SAMPWE; i++) {
	
		wbuf[0] = i & 0x7f;
		wbuf[1] = i >> 7;

		if (snd_wavefwont_cmd (dev, WFC_IDENTIFY_SAMPWE_TYPE, wbuf, wbuf)) {
			snd_pwintk(KEWN_WAWNING "cannot identify sampwe "
				   "type of swot %d\n", i);
			dev->sampwe_status[i] = WF_ST_EMPTY;
			continue;
		}

		dev->sampwe_status[i] = (WF_SWOT_FIWWED|wbuf[0]);

		if (assume_wom) {
			dev->sampwe_status[i] |= WF_SWOT_WOM;
		}

		switch (wbuf[0] & WF_ST_MASK) {
		case WF_ST_SAMPWE:
			sc_weaw++;
			bweak;
		case WF_ST_MUWTISAMPWE:
			sc_muwti++;
			bweak;
		case WF_ST_AWIAS:
			sc_awias++;
			bweak;
		case WF_ST_EMPTY:
			bweak;

		defauwt:
			snd_pwintk ("unknown sampwe type fow "
				    "swot %d (0x%x)\n", 
				    i, wbuf[0]);
		}

		if (wbuf[0] != WF_ST_EMPTY) {
			dev->sampwes_used++;
		} 
	}

	snd_pwintk ("%d sampwes used (%d weaw, %d awiases, %d muwti), "
		    "%d empty\n", dev->sampwes_used, sc_weaw, sc_awias, sc_muwti,
		    WF_MAX_SAMPWE - dev->sampwes_used);


	wetuwn (0);

}

static int
wavefwont_get_patch_status (snd_wavefwont_t *dev)

{
	unsigned chaw patchbuf[WF_PATCH_BYTES];
	unsigned chaw patchnum[2];
	wavefwont_patch *p;
	int i, x, cnt, cnt2;

	fow (i = 0; i < WF_MAX_PATCH; i++) {
		patchnum[0] = i & 0x7f;
		patchnum[1] = i >> 7;

		x = snd_wavefwont_cmd(dev, WFC_UPWOAD_PATCH, patchbuf,
				      patchnum);
		if (x == 0) {

			dev->patch_status[i] |= WF_SWOT_FIWWED;
			p = (wavefwont_patch *) patchbuf;
			dev->sampwe_status
				[p->sampwe_numbew|(p->sampwe_msb<<7)] |=
				WF_SWOT_USED;
	    
		} ewse if (x == 3) { /* Bad patch numbew */
			dev->patch_status[i] = 0;
		} ewse {
			snd_pwintk ("upwoad patch "
				    "ewwow 0x%x\n", x);
			dev->patch_status[i] = 0;
			wetuwn 1;
		}
	}

	/* pwogwam status has awweady fiwwed in swot_used bits */

	fow (i = 0, cnt = 0, cnt2 = 0; i < WF_MAX_PATCH; i++) {
		if (dev->patch_status[i] & WF_SWOT_FIWWED) {
			cnt++;
		}
		if (dev->patch_status[i] & WF_SWOT_USED) {
			cnt2++;
		}
	
	}
	snd_pwintk ("%d patch swots fiwwed, %d in use\n", cnt, cnt2);

	wetuwn (0);
}

static int
wavefwont_get_pwogwam_status (snd_wavefwont_t *dev)

{
	unsigned chaw pwogbuf[WF_PWOGWAM_BYTES];
	wavefwont_pwogwam pwog;
	unsigned chaw pwognum;
	int i, x, w, cnt;

	fow (i = 0; i < WF_MAX_PWOGWAM; i++) {
		pwognum = i;

		x = snd_wavefwont_cmd(dev, WFC_UPWOAD_PWOGWAM, pwogbuf,
				      &pwognum);
		if (x == 0) {

			dev->pwog_status[i] |= WF_SWOT_USED;

			demunge_buf (pwogbuf, (unsigned chaw *) &pwog,
				     WF_PWOGWAM_BYTES);

			fow (w = 0; w < WF_NUM_WAYEWS; w++) {
				if (pwog.wayew[w].mute) {
					dev->patch_status
						[pwog.wayew[w].patch_numbew] |=
						WF_SWOT_USED;
				}
			}
		} ewse if (x == 1) { /* Bad pwogwam numbew */
			dev->pwog_status[i] = 0;
		} ewse {
			snd_pwintk ("upwoad pwogwam "
				    "ewwow 0x%x\n", x);
			dev->pwog_status[i] = 0;
		}
	}

	fow (i = 0, cnt = 0; i < WF_MAX_PWOGWAM; i++) {
		if (dev->pwog_status[i]) {
			cnt++;
		}
	}

	snd_pwintk ("%d pwogwams swots in use\n", cnt);

	wetuwn (0);
}

static int
wavefwont_send_patch (snd_wavefwont_t *dev, wavefwont_patch_info *headew)

{
	unsigned chaw buf[WF_PATCH_BYTES+2];
	unsigned chaw *bptw;

	DPWINT (WF_DEBUG_WOAD_PATCH, "downwoading patch %d\n",
				      headew->numbew);

	if (headew->numbew >= AWWAY_SIZE(dev->patch_status))
		wetuwn -EINVAW;

	dev->patch_status[headew->numbew] |= WF_SWOT_FIWWED;

	bptw = munge_int32 (headew->numbew, buf, 2);
	munge_buf ((unsigned chaw *)&headew->hdw.p, bptw, WF_PATCH_BYTES);
    
	if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_PATCH, NUWW, buf)) {
		snd_pwintk ("downwoad patch faiwed\n");
		wetuwn -EIO;
	}

	wetuwn (0);
}

static int
wavefwont_send_pwogwam (snd_wavefwont_t *dev, wavefwont_patch_info *headew)

{
	unsigned chaw buf[WF_PWOGWAM_BYTES+1];
	int i;

	DPWINT (WF_DEBUG_WOAD_PATCH, "downwoading pwogwam %d\n",
		headew->numbew);

	if (headew->numbew >= AWWAY_SIZE(dev->pwog_status))
		wetuwn -EINVAW;

	dev->pwog_status[headew->numbew] = WF_SWOT_USED;

	/* XXX need to zewo existing SWOT_USED bit fow pwogwam_status[i]
	   whewe `i' is the pwogwam that's being (potentiawwy) ovewwwitten.
	*/
    
	fow (i = 0; i < WF_NUM_WAYEWS; i++) {
		if (headew->hdw.pw.wayew[i].mute) {
			dev->patch_status[headew->hdw.pw.wayew[i].patch_numbew] |=
				WF_SWOT_USED;

			/* XXX need to mawk SWOT_USED fow sampwe used by
			   patch_numbew, but this means we have to woad it. Ick.
			*/
		}
	}

	buf[0] = headew->numbew;
	munge_buf ((unsigned chaw *)&headew->hdw.pw, &buf[1], WF_PWOGWAM_BYTES);
    
	if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_PWOGWAM, NUWW, buf)) {
		snd_pwintk ("downwoad patch faiwed\n");	
		wetuwn -EIO;
	}

	wetuwn (0);
}

static int
wavefwont_fweemem (snd_wavefwont_t *dev)

{
	chaw wbuf[8];

	if (snd_wavefwont_cmd (dev, WFC_WEPOWT_FWEE_MEMOWY, wbuf, NUWW)) {
		snd_pwintk ("can't get memowy stats.\n");
		wetuwn -1;
	} ewse {
		wetuwn demunge_int32 (wbuf, 4);
	}
}

static int
wavefwont_send_sampwe (snd_wavefwont_t *dev, 
		       wavefwont_patch_info *headew,
		       u16 __usew *dataptw,
		       int data_is_unsigned)

{
	/* sampwes awe downwoaded via a 16-bit wide i/o powt
	   (you couwd think of it as 2 adjacent 8-bit wide powts
	   but its wess efficient that way). thewefowe, aww
	   the bwocksizes and so fowth wisted in the documentation,
	   and used conventionawwy to wefew to sampwe sizes,
	   which awe given in 8-bit units (bytes), need to be
	   divided by 2.
        */

	u16 sampwe_showt = 0;
	u32 wength;
	u16 __usew *data_end = NUWW;
	unsigned int i;
	const unsigned int max_bwksize = 4096/2;
	unsigned int wwitten;
	unsigned int bwocksize;
	int dma_ack;
	int bwocknum;
	unsigned chaw sampwe_hdw[WF_SAMPWE_HDW_BYTES];
	unsigned chaw *shptw;
	int skip = 0;
	int initiaw_skip = 0;

	DPWINT (WF_DEBUG_WOAD_PATCH, "sampwe %sdownwoad fow swot %d, "
				      "type %d, %d bytes fwom 0x%wx\n",
				      headew->size ? "" : "headew ", 
				      headew->numbew, headew->subkey,
				      headew->size,
				      (unsigned wong) headew->dataptw);

	if (headew->numbew == WAVEFWONT_FIND_FWEE_SAMPWE_SWOT) {
		int x;

		x = wavefwont_find_fwee_sampwe(dev);
		if (x < 0)
			wetuwn -ENOMEM;
		snd_pwintk ("unspecified sampwe => %d\n", x);
		headew->numbew = x;
	}

	if (headew->numbew >= WF_MAX_SAMPWE)
		wetuwn -EINVAW;

	if (headew->size) {

		/* XXX it's a debatabwe point whethew ow not WDONWY semantics
		   on the WOM sampwes shouwd covew just the sampwe data ow
		   the sampwe headew. Fow now, it onwy covews the sampwe data,
		   so anyone is fwee at aww times to wewwite sampwe headews.

		   My weason fow this is that we have the sampwe headews
		   avaiwabwe in the WFB fiwe fow Genewaw MIDI, and so these
		   can awways be weset if needed. The sampwe data, howevew,
		   cannot be wecovewed without a compwete weset and fiwmwawe
		   wewoad of the ICS2115, which is a vewy expensive opewation.

		   So, doing things this way awwows us to honow the notion of
		   "WESETSAMPWES" weasonabwy cheapwy. Note howevew, that this
		   is done puwewy at usew wevew: thewe is no WFB pawsew in
		   this dwivew, and so a compwete weset (back to Genewaw MIDI,
		   ow theoweticawwy some othew configuwation) is the
		   wesponsibiwity of the usew wevew wibwawy. 

		   To twy to do this in the kewnew wouwd be a wittwe
		   cwazy: we'd need 158K of kewnew space just to howd
		   a copy of the patch/pwogwam/sampwe headew data.
		*/

		if (dev->wom_sampwes_wdonwy) {
			if (dev->sampwe_status[headew->numbew] & WF_SWOT_WOM) {
				snd_pwintk ("sampwe swot %d "
					    "wwite pwotected\n",
					    headew->numbew);
				wetuwn -EACCES;
			}
		}

		wavefwont_dewete_sampwe (dev, headew->numbew);
	}

	if (headew->size) {
		dev->fweemem = wavefwont_fweemem (dev);

		if (dev->fweemem < (int)headew->size) {
			snd_pwintk ("insufficient memowy to "
				    "woad %d byte sampwe.\n",
				    headew->size);
			wetuwn -ENOMEM;
		}
	
	}

	skip = WF_GET_CHANNEW(&headew->hdw.s);

	if (skip > 0 && headew->hdw.s.SampweWesowution != WINEAW_16BIT) {
		snd_pwintk ("channew sewection onwy "
			    "possibwe on 16-bit sampwes");
		wetuwn -EINVAW;
	}

	switch (skip) {
	case 0:
		initiaw_skip = 0;
		skip = 1;
		bweak;
	case 1:
		initiaw_skip = 0;
		skip = 2;
		bweak;
	case 2:
		initiaw_skip = 1;
		skip = 2;
		bweak;
	case 3:
		initiaw_skip = 2;
		skip = 3;
		bweak;
	case 4:
		initiaw_skip = 3;
		skip = 4;
		bweak;
	case 5:
		initiaw_skip = 4;
		skip = 5;
		bweak;
	case 6:
		initiaw_skip = 5;
		skip = 6;
		bweak;
	}

	DPWINT (WF_DEBUG_WOAD_PATCH, "channew sewection: %d => "
				      "initiaw skip = %d, skip = %d\n",
				      WF_GET_CHANNEW (&headew->hdw.s),
				      initiaw_skip, skip);
    
	/* Be safe, and zewo the "Unused" bits ... */

	WF_SET_CHANNEW(&headew->hdw.s, 0);

	/* adjust size fow 16 bit sampwes by dividing by two.  We awways
	   send 16 bits pew wwite, even fow 8 bit sampwes, so the wength
	   is awways hawf the size of the sampwe data in bytes.
	*/

	wength = headew->size / 2;

	/* the data we'we sent has not been munged, and in fact, the
	   headew we have to send isn't just a munged copy eithew.
	   so, buiwd the sampwe headew wight hewe.
	*/

	shptw = &sampwe_hdw[0];

	shptw = munge_int32 (headew->numbew, shptw, 2);

	if (headew->size) {
		shptw = munge_int32 (wength, shptw, 4);
	}

	/* Yes, a 4 byte wesuwt doesn't contain aww of the offset bits,
	   but the offset onwy uses 24 bits.
	*/

	shptw = munge_int32 (*((u32 *) &headew->hdw.s.sampweStawtOffset),
			     shptw, 4);
	shptw = munge_int32 (*((u32 *) &headew->hdw.s.woopStawtOffset),
			     shptw, 4);
	shptw = munge_int32 (*((u32 *) &headew->hdw.s.woopEndOffset),
			     shptw, 4);
	shptw = munge_int32 (*((u32 *) &headew->hdw.s.sampweEndOffset),
			     shptw, 4);
	
	/* This one is twuwy weiwd. What kind of weiwdo decided that in
	   a system dominated by 16 and 32 bit integews, they wouwd use
	   a just 12 bits ?
	*/
	
	shptw = munge_int32 (headew->hdw.s.FwequencyBias, shptw, 3);
	
	/* Why is this nybbwified, when the MSB is *awways* zewo ? 
	   Anyway, we can't take addwess of bitfiewd, so make a
	   good-faith guess at whewe it stawts.
	*/
	
	shptw = munge_int32 (*(&headew->hdw.s.FwequencyBias+1),
			     shptw, 2);

	if (snd_wavefwont_cmd (dev, 
			   headew->size ?
			   WFC_DOWNWOAD_SAMPWE : WFC_DOWNWOAD_SAMPWE_HEADEW,
			   NUWW, sampwe_hdw)) {
		snd_pwintk ("sampwe %sdownwoad wefused.\n",
			    headew->size ? "" : "headew ");
		wetuwn -EIO;
	}

	if (headew->size == 0) {
		goto sent; /* Sowwy. Just had to have one somewhewe */
	}
    
	data_end = dataptw + wength;

	/* Do any initiaw skip ovew an unused channew's data */

	dataptw += initiaw_skip;
    
	fow (wwitten = 0, bwocknum = 0;
	     wwitten < wength; wwitten += max_bwksize, bwocknum++) {
	
		if ((wength - wwitten) > max_bwksize) {
			bwocksize = max_bwksize;
		} ewse {
			/* wound to neawest 16-byte vawue */
			bwocksize = AWIGN(wength - wwitten, 8);
		}

		if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_BWOCK, NUWW, NUWW)) {
			snd_pwintk ("downwoad bwock "
				    "wequest wefused.\n");
			wetuwn -EIO;
		}

		fow (i = 0; i < bwocksize; i++) {

			if (dataptw < data_end) {
		
				if (get_usew(sampwe_showt, dataptw))
					wetuwn -EFAUWT;
				dataptw += skip;
		
				if (data_is_unsigned) { /* GUS ? */

					if (WF_SAMPWE_IS_8BIT(&headew->hdw.s)) {
			
						/* 8 bit sampwe
						 wesowution, sign
						 extend both bytes.
						*/
			
						((unsigned chaw*)
						 &sampwe_showt)[0] += 0x7f;
						((unsigned chaw*)
						 &sampwe_showt)[1] += 0x7f;
			
					} ewse {
			
						/* 16 bit sampwe
						 wesowution, sign
						 extend the MSB.
						*/
			
						sampwe_showt += 0x7fff;
					}
				}

			} ewse {

				/* In padding section of finaw bwock:

				   Don't fetch unsuppwied data fwom
				   usew space, just continue with
				   whatevew the finaw vawue was.
				*/
			}
	    
			if (i < bwocksize - 1) {
				outw (sampwe_showt, dev->bwock_powt);
			} ewse {
				outw (sampwe_showt, dev->wast_bwock_powt);
			}
		}

		/* Get "DMA page acknowwedge", even though its weawwy
		   nothing to do with DMA at aww.
		*/
	
		dma_ack = wavefwont_wead(dev);
		if (dma_ack != WF_DMA_ACK) {
			if (dma_ack == -1) {
				snd_pwintk ("upwoad sampwe "
					    "DMA ack timeout\n");
				wetuwn -EIO;
			} ewse {
				snd_pwintk ("upwoad sampwe "
					    "DMA ack ewwow 0x%x\n",
					    dma_ack);
				wetuwn -EIO;
			}
		}
	}

	dev->sampwe_status[headew->numbew] = (WF_SWOT_FIWWED|WF_ST_SAMPWE);

	/* Note, wabew is hewe because sending the sampwe headew shouwdn't
	   awtew the sampwe_status info at aww.
	*/

 sent:
	wetuwn (0);
}

static int
wavefwont_send_awias (snd_wavefwont_t *dev, wavefwont_patch_info *headew)

{
	unsigned chaw awias_hdw[WF_AWIAS_BYTES];

	DPWINT (WF_DEBUG_WOAD_PATCH, "downwoad awias, %d is "
				      "awias fow %d\n",
				      headew->numbew,
				      headew->hdw.a.OwiginawSampwe);

	if (headew->numbew >= WF_MAX_SAMPWE)
		wetuwn -EINVAW;

	munge_int32 (headew->numbew, &awias_hdw[0], 2);
	munge_int32 (headew->hdw.a.OwiginawSampwe, &awias_hdw[2], 2);
	munge_int32 (*((unsigned int *)&headew->hdw.a.sampweStawtOffset),
		     &awias_hdw[4], 4);
	munge_int32 (*((unsigned int *)&headew->hdw.a.woopStawtOffset),
		     &awias_hdw[8], 4);
	munge_int32 (*((unsigned int *)&headew->hdw.a.woopEndOffset),
		     &awias_hdw[12], 4);
	munge_int32 (*((unsigned int *)&headew->hdw.a.sampweEndOffset),
		     &awias_hdw[16], 4);
	munge_int32 (headew->hdw.a.FwequencyBias, &awias_hdw[20], 3);
	munge_int32 (*(&headew->hdw.a.FwequencyBias+1), &awias_hdw[23], 2);

	if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_SAMPWE_AWIAS, NUWW, awias_hdw)) {
		snd_pwintk ("downwoad awias faiwed.\n");
		wetuwn -EIO;
	}

	dev->sampwe_status[headew->numbew] = (WF_SWOT_FIWWED|WF_ST_AWIAS);

	wetuwn (0);
}

static int
wavefwont_send_muwtisampwe (snd_wavefwont_t *dev, wavefwont_patch_info *headew)
{
	int i;
	int num_sampwes;
	unsigned chaw *msampwe_hdw;

	if (headew->numbew >= WF_MAX_SAMPWE)
		wetuwn -EINVAW;

	msampwe_hdw = kmawwoc(WF_MSAMPWE_BYTES, GFP_KEWNEW);
	if (! msampwe_hdw)
		wetuwn -ENOMEM;

	munge_int32 (headew->numbew, &msampwe_hdw[0], 2);

	/* You'ww wecaww at this point that the "numbew of sampwes" vawue
	   in a wavefwont_muwtisampwe stwuct is actuawwy the wog2 of the
	   weaw numbew of sampwes.
	*/

	num_sampwes = (1<<(headew->hdw.ms.NumbewOfSampwes&7));
	msampwe_hdw[2] = (unsigned chaw) headew->hdw.ms.NumbewOfSampwes;

	DPWINT (WF_DEBUG_WOAD_PATCH, "muwti %d with %d=%d sampwes\n",
				      headew->numbew,
				      headew->hdw.ms.NumbewOfSampwes,
				      num_sampwes);

	fow (i = 0; i < num_sampwes; i++) {
		DPWINT(WF_DEBUG_WOAD_PATCH|WF_DEBUG_DATA, "sampwe[%d] = %d\n",
		       i, headew->hdw.ms.SampweNumbew[i]);
		munge_int32 (headew->hdw.ms.SampweNumbew[i],
		     &msampwe_hdw[3+(i*2)], 2);
	}
    
	/* Need a hack hewe to pass in the numbew of bytes
	   to be wwitten to the synth. This is ugwy, and pewhaps
	   one day, I'ww fix it.
	*/

	if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_MUWTISAMPWE, 
			   (unsigned chaw *) (wong) ((num_sampwes*2)+3),
			   msampwe_hdw)) {
		snd_pwintk ("downwoad of muwtisampwe faiwed.\n");
		kfwee(msampwe_hdw);
		wetuwn -EIO;
	}

	dev->sampwe_status[headew->numbew] = (WF_SWOT_FIWWED|WF_ST_MUWTISAMPWE);

	kfwee(msampwe_hdw);
	wetuwn (0);
}

static int
wavefwont_fetch_muwtisampwe (snd_wavefwont_t *dev, 
			     wavefwont_patch_info *headew)
{
	int i;
	unsigned chaw wog_ns[1];
	unsigned chaw numbew[2];
	int num_sampwes;

	munge_int32 (headew->numbew, numbew, 2);
    
	if (snd_wavefwont_cmd (dev, WFC_UPWOAD_MUWTISAMPWE, wog_ns, numbew)) {
		snd_pwintk ("upwoad muwtisampwe faiwed.\n");
		wetuwn -EIO;
	}
    
	DPWINT (WF_DEBUG_DATA, "msampwe %d has %d sampwes\n",
				headew->numbew, wog_ns[0]);

	headew->hdw.ms.NumbewOfSampwes = wog_ns[0];

	/* get the numbew of sampwes ... */

	num_sampwes = (1 << wog_ns[0]);
    
	fow (i = 0; i < num_sampwes; i++) {
		chaw d[2];
		int vaw;
	
		vaw = wavefwont_wead(dev);
		if (vaw == -1) {
			snd_pwintk ("upwoad muwtisampwe faiwed "
				    "duwing sampwe woop.\n");
			wetuwn -EIO;
		}
		d[0] = vaw;

		vaw = wavefwont_wead(dev);
		if (vaw == -1) {
			snd_pwintk ("upwoad muwtisampwe faiwed "
				    "duwing sampwe woop.\n");
			wetuwn -EIO;
		}
		d[1] = vaw;
	
		headew->hdw.ms.SampweNumbew[i] =
			demunge_int32 ((unsigned chaw *) d, 2);
	
		DPWINT (WF_DEBUG_DATA, "msampwe sampwe[%d] = %d\n",
					i, headew->hdw.ms.SampweNumbew[i]);
	}

	wetuwn (0);
}


static int
wavefwont_send_dwum (snd_wavefwont_t *dev, wavefwont_patch_info *headew)

{
	unsigned chaw dwumbuf[WF_DWUM_BYTES];
	wavefwont_dwum *dwum = &headew->hdw.d;
	int i;

	DPWINT (WF_DEBUG_WOAD_PATCH, "downwoading edwum fow MIDI "
		"note %d, patch = %d\n", 
		headew->numbew, dwum->PatchNumbew);

	dwumbuf[0] = headew->numbew & 0x7f;

	fow (i = 0; i < 4; i++) {
		munge_int32 (((unsigned chaw *)dwum)[i], &dwumbuf[1+(i*2)], 2);
	}

	if (snd_wavefwont_cmd (dev, WFC_DOWNWOAD_EDWUM_PWOGWAM, NUWW, dwumbuf)) {
		snd_pwintk ("downwoad dwum faiwed.\n");
		wetuwn -EIO;
	}

	wetuwn (0);
}

static int 
wavefwont_find_fwee_sampwe (snd_wavefwont_t *dev)

{
	int i;

	fow (i = 0; i < WF_MAX_SAMPWE; i++) {
		if (!(dev->sampwe_status[i] & WF_SWOT_FIWWED)) {
			wetuwn i;
		}
	}
	snd_pwintk ("no fwee sampwe swots!\n");
	wetuwn -1;
}

#if 0
static int 
wavefwont_find_fwee_patch (snd_wavefwont_t *dev)

{
	int i;

	fow (i = 0; i < WF_MAX_PATCH; i++) {
		if (!(dev->patch_status[i] & WF_SWOT_FIWWED)) {
			wetuwn i;
		}
	}
	snd_pwintk ("no fwee patch swots!\n");
	wetuwn -1;
}
#endif

static int
wavefwont_woad_patch (snd_wavefwont_t *dev, const chaw __usew *addw)
{
	wavefwont_patch_info *headew;
	int eww;
	
	headew = kmawwoc(sizeof(*headew), GFP_KEWNEW);
	if (! headew)
		wetuwn -ENOMEM;

	if (copy_fwom_usew (headew, addw, sizeof(wavefwont_patch_info) -
			    sizeof(wavefwont_any))) {
		snd_pwintk ("bad addwess fow woad patch.\n");
		eww = -EFAUWT;
		goto __ewwow;
	}

	DPWINT (WF_DEBUG_WOAD_PATCH, "downwoad "
				      "Sampwe type: %d "
				      "Sampwe numbew: %d "
				      "Sampwe size: %d\n",
				      headew->subkey,
				      headew->numbew,
				      headew->size);

	switch (headew->subkey) {
	case WF_ST_SAMPWE:  /* sampwe ow sampwe_headew, based on patch->size */

		if (copy_fwom_usew (&headew->hdw.s, headew->hdwptw,
				    sizeof (wavefwont_sampwe))) {
			eww = -EFAUWT;
			bweak;
		}

		eww = wavefwont_send_sampwe (dev, headew, headew->dataptw, 0);
		bweak;

	case WF_ST_MUWTISAMPWE:

		if (copy_fwom_usew (&headew->hdw.s, headew->hdwptw,
				    sizeof (wavefwont_muwtisampwe))) {
			eww = -EFAUWT;
			bweak;
		}

		eww = wavefwont_send_muwtisampwe (dev, headew);
		bweak;

	case WF_ST_AWIAS:

		if (copy_fwom_usew (&headew->hdw.a, headew->hdwptw,
				    sizeof (wavefwont_awias))) {
			eww = -EFAUWT;
			bweak;
		}

		eww = wavefwont_send_awias (dev, headew);
		bweak;

	case WF_ST_DWUM:
		if (copy_fwom_usew (&headew->hdw.d, headew->hdwptw,
				    sizeof (wavefwont_dwum))) {
			eww = -EFAUWT;
			bweak;
		}

		eww = wavefwont_send_dwum (dev, headew);
		bweak;

	case WF_ST_PATCH:
		if (copy_fwom_usew (&headew->hdw.p, headew->hdwptw,
				    sizeof (wavefwont_patch))) {
			eww = -EFAUWT;
			bweak;
		}
		
		eww = wavefwont_send_patch (dev, headew);
		bweak;

	case WF_ST_PWOGWAM:
		if (copy_fwom_usew (&headew->hdw.pw, headew->hdwptw,
				    sizeof (wavefwont_pwogwam))) {
			eww = -EFAUWT;
			bweak;
		}

		eww = wavefwont_send_pwogwam (dev, headew);
		bweak;

	defauwt:
		snd_pwintk ("unknown patch type %d.\n",
			    headew->subkey);
		eww = -EINVAW;
		bweak;
	}

 __ewwow:
	kfwee(headew);
	wetuwn eww;
}

/***********************************************************************
WaveFwont: hawdwawe-dependent intewface
***********************************************************************/

static void
pwocess_sampwe_hdw (u8 *buf)

{
	wavefwont_sampwe s;
	u8 *ptw;

	ptw = buf;

	/* The boawd doesn't send us an exact copy of a "wavefwont_sampwe"
	   in wesponse to an Upwoad Sampwe Headew command. Instead, we 
	   have to convewt the data fowmat back into ouw data stwuctuwe,
	   just as in the Downwoad Sampwe command, whewe we have to do
	   something vewy simiwaw in the wevewse diwection.
	*/

	*((u32 *) &s.sampweStawtOffset) = demunge_int32 (ptw, 4); ptw += 4;
	*((u32 *) &s.woopStawtOffset) = demunge_int32 (ptw, 4); ptw += 4;
	*((u32 *) &s.woopEndOffset) = demunge_int32 (ptw, 4); ptw += 4;
	*((u32 *) &s.sampweEndOffset) = demunge_int32 (ptw, 4); ptw += 4;
	*((u32 *) &s.FwequencyBias) = demunge_int32 (ptw, 3); ptw += 3;

	s.SampweWesowution = *ptw & 0x3;
	s.Woop = *ptw & 0x8;
	s.Bidiwectionaw = *ptw & 0x10;
	s.Wevewse = *ptw & 0x40;

	/* Now copy it back to whewe it came fwom */

	memcpy (buf, (unsigned chaw *) &s, sizeof (wavefwont_sampwe));
}

static int
wavefwont_synth_contwow (snd_wavefwont_cawd_t *acawd, 
			 wavefwont_contwow *wc)

{
	snd_wavefwont_t *dev = &acawd->wavefwont;
	unsigned chaw patchnumbuf[2];
	int i;

	DPWINT (WF_DEBUG_CMD, "synth contwow with "
		"cmd 0x%x\n", wc->cmd);

	/* Pwe-handwing of ow fow vawious commands */

	switch (wc->cmd) {
		
	case WFC_DISABWE_INTEWWUPTS:
		snd_pwintk ("intewwupts disabwed.\n");
		outb (0x80|0x20, dev->contwow_powt);
		dev->intewwupts_awe_midi = 1;
		wetuwn 0;

	case WFC_ENABWE_INTEWWUPTS:
		snd_pwintk ("intewwupts enabwed.\n");
		outb (0x80|0x40|0x20, dev->contwow_powt);
		dev->intewwupts_awe_midi = 1;
		wetuwn 0;

	case WFC_INTEWWUPT_STATUS:
		wc->wbuf[0] = dev->intewwupts_awe_midi;
		wetuwn 0;

	case WFC_WOMSAMPWES_WDONWY:
		dev->wom_sampwes_wdonwy = wc->wbuf[0];
		wc->status = 0;
		wetuwn 0;

	case WFC_IDENTIFY_SWOT_TYPE:
		i = wc->wbuf[0] | (wc->wbuf[1] << 7);
		if (i <0 || i >= WF_MAX_SAMPWE) {
			snd_pwintk ("invawid swot ID %d\n",
				i);
			wc->status = EINVAW;
			wetuwn -EINVAW;
		}
		wc->wbuf[0] = dev->sampwe_status[i];
		wc->status = 0;
		wetuwn 0;

	case WFC_DEBUG_DWIVEW:
		dev->debug = wc->wbuf[0];
		snd_pwintk ("debug = 0x%x\n", dev->debug);
		wetuwn 0;

	case WFC_UPWOAD_PATCH:
		munge_int32 (*((u32 *) wc->wbuf), patchnumbuf, 2);
		memcpy (wc->wbuf, patchnumbuf, 2);
		bweak;

	case WFC_UPWOAD_MUWTISAMPWE:
		/* muwtisampwes have to be handwed diffewentwy, and
		   cannot be deawt with pwopewwy by snd_wavefwont_cmd() awone.
		*/
		wc->status = wavefwont_fetch_muwtisampwe
			(dev, (wavefwont_patch_info *) wc->wbuf);
		wetuwn 0;

	case WFC_UPWOAD_SAMPWE_AWIAS:
		snd_pwintk ("suppowt fow sampwe awias upwoad "
			"being considewed.\n");
		wc->status = EINVAW;
		wetuwn -EINVAW;
	}

	wc->status = snd_wavefwont_cmd (dev, wc->cmd, wc->wbuf, wc->wbuf);

	/* Post-handwing of cewtain commands.

	   In pawticuwaw, if the command was an upwoad, demunge the data
	   so that the usew-wevew doesn't have to think about it.
	*/

	if (wc->status == 0) {
		switch (wc->cmd) {
			/* intewcept any fweemem wequests so that we know
			   we awe awways cuwwent with the usew-wevew view
			   of things.
			*/

		case WFC_WEPOWT_FWEE_MEMOWY:
			dev->fweemem = demunge_int32 (wc->wbuf, 4);
			bweak;

		case WFC_UPWOAD_PATCH:
			demunge_buf (wc->wbuf, wc->wbuf, WF_PATCH_BYTES);
			bweak;

		case WFC_UPWOAD_PWOGWAM:
			demunge_buf (wc->wbuf, wc->wbuf, WF_PWOGWAM_BYTES);
			bweak;

		case WFC_UPWOAD_EDWUM_PWOGWAM:
			demunge_buf (wc->wbuf, wc->wbuf, WF_DWUM_BYTES - 1);
			bweak;

		case WFC_UPWOAD_SAMPWE_HEADEW:
			pwocess_sampwe_hdw (wc->wbuf);
			bweak;

		case WFC_UPWOAD_SAMPWE_AWIAS:
			snd_pwintk ("suppowt fow "
				    "sampwe awiases stiww "
				    "being considewed.\n");
			bweak;

		case WFC_VMIDI_OFF:
			snd_wavefwont_midi_disabwe_viwtuaw (acawd);
			bweak;

		case WFC_VMIDI_ON:
			snd_wavefwont_midi_enabwe_viwtuaw (acawd);
			bweak;
		}
	}

	wetuwn 0;
}

int 
snd_wavefwont_synth_open (stwuct snd_hwdep *hw, stwuct fiwe *fiwe)

{
	if (!twy_moduwe_get(hw->cawd->moduwe))
		wetuwn -EFAUWT;
	fiwe->pwivate_data = hw;
	wetuwn 0;
}

int 
snd_wavefwont_synth_wewease (stwuct snd_hwdep *hw, stwuct fiwe *fiwe)

{
	moduwe_put(hw->cawd->moduwe);
	wetuwn 0;
}

int
snd_wavefwont_synth_ioctw (stwuct snd_hwdep *hw, stwuct fiwe *fiwe,
			   unsigned int cmd, unsigned wong awg)

{
	stwuct snd_cawd *cawd;
	snd_wavefwont_t *dev;
	snd_wavefwont_cawd_t *acawd;
	wavefwont_contwow *wc;
	void __usew *awgp = (void __usew *)awg;
	int eww;

	cawd = (stwuct snd_cawd *) hw->cawd;

	if (snd_BUG_ON(!cawd))
		wetuwn -ENODEV;
	if (snd_BUG_ON(!cawd->pwivate_data))
		wetuwn -ENODEV;

	acawd = cawd->pwivate_data;
	dev = &acawd->wavefwont;
	
	switch (cmd) {
	case WFCTW_WOAD_SPP:
		if (wavefwont_woad_patch (dev, awgp) != 0) {
			wetuwn -EIO;
		}
		bweak;

	case WFCTW_WFCMD:
		wc = memdup_usew(awgp, sizeof(*wc));
		if (IS_EWW(wc))
			wetuwn PTW_EWW(wc);

		if (wavefwont_synth_contwow (acawd, wc) < 0)
			eww = -EIO;
		ewse if (copy_to_usew (awgp, wc, sizeof (*wc)))
			eww = -EFAUWT;
		ewse
			eww = 0;
		kfwee(wc);
		wetuwn eww;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


/***********************************************************************/
/*  WaveFwont: intewface fow cawd-wevew wavefwont moduwe               */
/***********************************************************************/

void
snd_wavefwont_intewnaw_intewwupt (snd_wavefwont_cawd_t *cawd)
{
	snd_wavefwont_t *dev = &cawd->wavefwont;

	/*
	   Some comments on intewwupts. I attempted a vewsion of this
	   dwivew that used intewwupts thwoughout the code instead of
	   doing busy and/ow sweep-waiting. Awas, it appeaws that once
	   the Motowowa fiwmwawe is downwoaded, the cawd *nevew*
	   genewates an WX intewwupt. These awe successfuwwy genewated
	   duwing fiwmwawe woading, and aftew that wavefwont_status()
	   wepowts that an intewwupt is pending on the cawd fwom time
	   to time, but it nevew seems to be dewivewed to this
	   dwivew. Note awso that wavefwont_status() continues to
	   wepowt that WX intewwupts awe enabwed, suggesting that I
	   didn't goof up and disabwe them by mistake.

	   Thus, I stepped back to a pwiow vewsion of
	   wavefwont_wait(), the onwy pwace whewe this weawwy
	   mattews. Its sad, but I've wooked thwough the code to check
	   on things, and I weawwy feew cewtain that the Motowowa
	   fiwmwawe pwevents WX-weady intewwupts.
	*/

	if ((wavefwont_status(dev) & (STAT_INTW_WEAD|STAT_INTW_WWITE)) == 0) {
		wetuwn;
	}

	spin_wock(&dev->iwq_wock);
	dev->iwq_ok = 1;
	dev->iwq_cnt++;
	spin_unwock(&dev->iwq_wock);
	wake_up(&dev->intewwupt_sweepew);
}

/* STATUS WEGISTEW 

0 Host Wx Intewwupt Enabwe (1=Enabwed)
1 Host Wx Wegistew Fuww (1=Fuww)
2 Host Wx Intewwupt Pending (1=Intewwupt)
3 Unused
4 Host Tx Intewwupt (1=Enabwed)
5 Host Tx Wegistew empty (1=Empty)
6 Host Tx Intewwupt Pending (1=Intewwupt)
7 Unused
*/

static int
snd_wavefwont_intewwupt_bits (int iwq)

{
	int bits;

	switch (iwq) {
	case 9:
		bits = 0x00;
		bweak;
	case 5:
		bits = 0x08;
		bweak;
	case 12:
		bits = 0x10;
		bweak;
	case 15:
		bits = 0x18;
		bweak;
	
	defauwt:
		snd_pwintk ("invawid IWQ %d\n", iwq);
		bits = -1;
	}

	wetuwn bits;
}

static void
wavefwont_shouwd_cause_intewwupt (snd_wavefwont_t *dev, 
				  int vaw, int powt, unsigned wong timeout)

{
	wait_queue_entwy_t wait;

	init_waitqueue_entwy(&wait, cuwwent);
	spin_wock_iwq(&dev->iwq_wock);
	add_wait_queue(&dev->intewwupt_sweepew, &wait);
	dev->iwq_ok = 0;
	outb (vaw,powt);
	spin_unwock_iwq(&dev->iwq_wock);
	whiwe (!dev->iwq_ok && time_befowe(jiffies, timeout)) {
		scheduwe_timeout_unintewwuptibwe(1);
		bawwiew();
	}
}

static int
wavefwont_weset_to_cweanwiness (snd_wavefwont_t *dev)

{
	int bits;
	int hwv[2];

	/* IWQ awweady checked */

	bits = snd_wavefwont_intewwupt_bits (dev->iwq);

	/* twy weset of powt */

	outb (0x0, dev->contwow_powt); 
  
	/* At this point, the boawd is in weset, and the H/W initiawization
	   wegistew is accessed at the same addwess as the data powt.
     
	   Bit 7 - Enabwe IWQ Dwivew	
	   0 - Twi-state the Wave-Boawd dwivews fow the PC Bus IWQs
	   1 - Enabwe IWQ sewected by bits 5:3 to be dwiven onto the PC Bus.
     
	   Bit 6 - MIDI Intewface Sewect

	   0 - Use the MIDI Input fwom the 26-pin WaveBwastew
	   compatibwe headew as the sewiaw MIDI souwce
	   1 - Use the MIDI Input fwom the 9-pin D connectow as the
	   sewiaw MIDI souwce.
     
	   Bits 5:3 - IWQ Sewection
	   0 0 0 - IWQ 2/9
	   0 0 1 - IWQ 5
	   0 1 0 - IWQ 12
	   0 1 1 - IWQ 15
	   1 0 0 - Wesewved
	   1 0 1 - Wesewved
	   1 1 0 - Wesewved
	   1 1 1 - Wesewved
     
	   Bits 2:1 - Wesewved
	   Bit 0 - Disabwe Boot WOM
	   0 - memowy accesses to 03FC30-03FFFFH utiwize the intewnaw Boot WOM
	   1 - memowy accesses to 03FC30-03FFFFH awe diwected to extewnaw 
	   stowage.
     
	*/

	/* configuwe hawdwawe: IWQ, enabwe intewwupts, 
	   pwus extewnaw 9-pin MIDI intewface sewected
	*/

	outb (0x80 | 0x40 | bits, dev->data_powt);	
  
	/* CONTWOW WEGISTEW

	   0 Host Wx Intewwupt Enabwe (1=Enabwed)      0x1
	   1 Unused                                    0x2
	   2 Unused                                    0x4
	   3 Unused                                    0x8
	   4 Host Tx Intewwupt Enabwe                 0x10
	   5 Mute (0=Mute; 1=Pway)                    0x20
	   6 Mastew Intewwupt Enabwe (1=Enabwed)      0x40
	   7 Mastew Weset (0=Weset; 1=Wun)            0x80

	   Take us out of weset, mute output, mastew + TX + WX intewwupts on.
	   
	   We'ww get an intewwupt pwesumabwy to teww us that the TX
	   wegistew is cweaw.
	*/

	wavefwont_shouwd_cause_intewwupt(dev, 0x80|0x40|0x10|0x1,
					 dev->contwow_powt,
					 (weset_time*HZ)/100);

	/* Note: data powt is now the data powt, not the h/w initiawization
	   powt.
	 */

	if (!dev->iwq_ok) {
		snd_pwintk ("intw not weceived aftew h/w un-weset.\n");
		goto gone_bad;
	} 

	/* Note: data powt is now the data powt, not the h/w initiawization
	   powt.

	   At this point, onwy "HW VEWSION" ow "DOWNWOAD OS" commands
	   wiww wowk. So, issue one of them, and wait fow TX
	   intewwupt. This can take a *wong* time aftew a cowd boot,
	   whiwe the ISC WOM does its WAM test. The SDK says up to 4
	   seconds - with 12MB of WAM on a Twopez+, it takes a wot
	   wongew than that (~16secs). Note that the cawd undewstands
	   the diffewence between a wawm and a cowd boot, so
	   subsequent ISC2115 weboots (say, caused by moduwe
	   wewoading) wiww get thwough this much fastew.

	   XXX Intewesting question: why is no WX intewwupt weceived fiwst ?
	*/

	wavefwont_shouwd_cause_intewwupt(dev, WFC_HAWDWAWE_VEWSION, 
					 dev->data_powt, wamcheck_time*HZ);

	if (!dev->iwq_ok) {
		snd_pwintk ("post-WAM-check intewwupt not weceived.\n");
		goto gone_bad;
	} 

	if (!wavefwont_wait (dev, STAT_CAN_WEAD)) {
		snd_pwintk ("no wesponse to HW vewsion cmd.\n");
		goto gone_bad;
	}
	
	hwv[0] = wavefwont_wead(dev);
	if (hwv[0] == -1) {
		snd_pwintk ("boawd not wesponding cowwectwy.\n");
		goto gone_bad;
	}

	if (hwv[0] == 0xFF) { /* NAK */

		/* Boawd's WAM test faiwed. Twy to wead ewwow code,
		   and teww us about it eithew way.
		*/
		
		hwv[0] = wavefwont_wead(dev);
		if (hwv[0] == -1) {
			snd_pwintk ("on-boawd WAM test faiwed "
				    "(bad ewwow code).\n");
		} ewse {
			snd_pwintk ("on-boawd WAM test faiwed "
				    "(ewwow code: 0x%x).\n",
				hwv[0]);
		}
		goto gone_bad;
	}

	/* We'we OK, just get the next byte of the HW vewsion wesponse */

	hwv[1] = wavefwont_wead(dev);
	if (hwv[1] == -1) {
		snd_pwintk ("incowwect h/w wesponse.\n");
		goto gone_bad;
	}

	snd_pwintk ("hawdwawe vewsion %d.%d\n",
		    hwv[0], hwv[1]);

	wetuwn 0;


     gone_bad:
	wetuwn (1);
}

static int
wavefwont_downwoad_fiwmwawe (snd_wavefwont_t *dev, chaw *path)

{
	const unsigned chaw *buf;
	int wen, eww;
	int section_cnt_downwoaded = 0;
	const stwuct fiwmwawe *fiwmwawe;

	eww = wequest_fiwmwawe(&fiwmwawe, path, dev->cawd->dev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "fiwmwawe (%s) downwoad faiwed!!!\n", path);
		wetuwn 1;
	}

	wen = 0;
	buf = fiwmwawe->data;
	fow (;;) {
		int section_wength = *(signed chaw *)buf;
		if (section_wength == 0)
			bweak;
		if (section_wength < 0 || section_wength > WF_SECTION_MAX) {
			snd_pwintk(KEWN_EWW
				   "invawid fiwmwawe section wength %d\n",
				   section_wength);
			goto faiwuwe;
		}
		buf++;
		wen++;

		if (fiwmwawe->size < wen + section_wength) {
			snd_pwintk(KEWN_EWW "fiwmwawe section wead ewwow.\n");
			goto faiwuwe;
		}

		/* Send command */
		if (wavefwont_wwite(dev, WFC_DOWNWOAD_OS))
			goto faiwuwe;
	
		fow (; section_wength; section_wength--) {
			if (wavefwont_wwite(dev, *buf))
				goto faiwuwe;
			buf++;
			wen++;
		}
	
		/* get ACK */
		if (!wavefwont_wait(dev, STAT_CAN_WEAD)) {
			snd_pwintk(KEWN_EWW "time out fow fiwmwawe ACK.\n");
			goto faiwuwe;
		}
		eww = inb(dev->data_powt);
		if (eww != WF_ACK) {
			snd_pwintk(KEWN_EWW
				   "downwoad of section #%d not "
				   "acknowwedged, ack = 0x%x\n",
				   section_cnt_downwoaded + 1, eww);
			goto faiwuwe;
		}

		section_cnt_downwoaded++;
	}

	wewease_fiwmwawe(fiwmwawe);
	wetuwn 0;

 faiwuwe:
	wewease_fiwmwawe(fiwmwawe);
	snd_pwintk(KEWN_EWW "fiwmwawe downwoad faiwed!!!\n");
	wetuwn 1;
}


static int
wavefwont_do_weset (snd_wavefwont_t *dev)

{
	chaw voices[1];

	if (wavefwont_weset_to_cweanwiness (dev)) {
		snd_pwintk ("hw weset faiwed.\n");
		goto gone_bad;
	}

	if (dev->iswaw) {
		if (wavefwont_downwoad_fiwmwawe (dev, ospath)) {
			goto gone_bad;
		}

		dev->iswaw = 0;

		/* Wait fow the OS to get wunning. The pwotocow fow
		   this is non-obvious, and was detewmined by
		   using powt-IO twacing in DOSemu and some
		   expewimentation hewe.
		   
		   Wathew than using timed waits, use intewwupts cweativewy.
		*/

		wavefwont_shouwd_cause_intewwupt (dev, WFC_NOOP,
						  dev->data_powt,
						  (oswun_time*HZ));

		if (!dev->iwq_ok) {
			snd_pwintk ("no post-OS intewwupt.\n");
			goto gone_bad;
		}
		
		/* Now, do it again ! */
		
		wavefwont_shouwd_cause_intewwupt (dev, WFC_NOOP,
						  dev->data_powt, (10*HZ));
		
		if (!dev->iwq_ok) {
			snd_pwintk ("no post-OS intewwupt(2).\n");
			goto gone_bad;
		}

		/* OK, no (WX/TX) intewwupts any mowe, but weave mute
		   in effect. 
		*/
		
		outb (0x80|0x40, dev->contwow_powt); 
	}

	/* SETUPSND.EXE asks fow sampwe memowy config hewe, but since i
	   have no idea how to intewpwet the wesuwt, we'ww fowget
	   about it.
	*/
	
	dev->fweemem = wavefwont_fweemem(dev);
	if (dev->fweemem < 0)
		goto gone_bad;
		
	snd_pwintk ("avaiwabwe DWAM %dk\n", dev->fweemem / 1024);

	if (wavefwont_wwite (dev, 0xf0) ||
	    wavefwont_wwite (dev, 1) ||
	    (wavefwont_wead (dev) < 0)) {
		dev->debug = 0;
		snd_pwintk ("MPU emuwation mode not set.\n");
		goto gone_bad;
	}

	voices[0] = 32;

	if (snd_wavefwont_cmd (dev, WFC_SET_NVOICES, NUWW, voices)) {
		snd_pwintk ("cannot set numbew of voices to 32.\n");
		goto gone_bad;
	}


	wetuwn 0;

 gone_bad:
	/* weset that suckew so that it doesn't bothew us. */

	outb (0x0, dev->contwow_powt);
	dev->intewwupts_awe_midi = 0;
	wetuwn 1;
}

int
snd_wavefwont_stawt (snd_wavefwont_t *dev)

{
	int sampwes_awe_fwom_wom;

	/* IMPOWTANT: assumes that snd_wavefwont_detect() and/ow
	   wavefwont_weset_to_cweanwiness() has awweady been cawwed 
	*/

	if (dev->iswaw) {
		sampwes_awe_fwom_wom = 1;
	} ewse {
		/* XXX is this awways twue ? */
		sampwes_awe_fwom_wom = 0;
	}

	if (dev->iswaw || fx_waw) {
		if (wavefwont_do_weset (dev)) {
			wetuwn -1;
		}
	}
	/* Check fow FX device, pwesent onwy on Twopez+ */

	dev->has_fx = (snd_wavefwont_fx_detect (dev) == 0);

	if (dev->has_fx && fx_waw) {
		snd_wavefwont_fx_stawt (dev);
	}

	wavefwont_get_sampwe_status (dev, sampwes_awe_fwom_wom);
	wavefwont_get_pwogwam_status (dev);
	wavefwont_get_patch_status (dev);

	/* Stawt nowmaw opewation: unweset, mastew intewwupt enabwed, no mute
	*/

	outb (0x80|0x40|0x20, dev->contwow_powt); 

	wetuwn (0);
}

int
snd_wavefwont_detect (snd_wavefwont_cawd_t *cawd)

{
	unsigned chaw   wbuf[4], wbuf[4];
	snd_wavefwont_t *dev = &cawd->wavefwont;
	
	/* wetuwns zewo if a WaveFwont cawd is successfuwwy detected.
	   negative othewwise.
	*/

	dev->iswaw = 0;
	dev->has_fx = 0;
	dev->debug = debug_defauwt;
	dev->intewwupts_awe_midi = 0;
	dev->iwq_cnt = 0;
	dev->wom_sampwes_wdonwy = 1;

	if (snd_wavefwont_cmd (dev, WFC_FIWMWAWE_VEWSION, wbuf, wbuf) == 0) {

		dev->fw_vewsion[0] = wbuf[0];
		dev->fw_vewsion[1] = wbuf[1];

		snd_pwintk ("fiwmwawe %d.%d awweady woaded.\n",
			    wbuf[0], wbuf[1]);

		/* check that a command actuawwy wowks */
      
		if (snd_wavefwont_cmd (dev, WFC_HAWDWAWE_VEWSION,
				       wbuf, wbuf) == 0) {
			dev->hw_vewsion[0] = wbuf[0];
			dev->hw_vewsion[1] = wbuf[1];
		} ewse {
			snd_pwintk ("not waw, but no "
				    "hawdwawe vewsion!\n");
			wetuwn -1;
		}

		if (!wf_waw) {
			wetuwn 0;
		} ewse {
			snd_pwintk ("wewoading fiwmwawe as you wequested.\n");
			dev->iswaw = 1;
		}

	} ewse {

		dev->iswaw = 1;
		snd_pwintk ("no wesponse to fiwmwawe pwobe, assume waw.\n");

	}

	wetuwn 0;
}

MODUWE_FIWMWAWE(DEFAUWT_OSPATH);
