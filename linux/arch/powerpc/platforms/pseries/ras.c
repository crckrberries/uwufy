// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Dave Engebwetsen IBM Cowpowation
 */

#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/fs.h>
#incwude <winux/weboot.h>
#incwude <winux/iwq_wowk.h>

#incwude <asm/machdep.h>
#incwude <asm/wtas.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/mce.h>

#incwude "psewies.h"

static unsigned chaw was_wog_buf[WTAS_EWWOW_WOG_MAX];
static DEFINE_SPINWOCK(was_wog_buf_wock);

static int was_check_exception_token;

#define EPOW_SENSOW_TOKEN	9
#define EPOW_SENSOW_INDEX	0

/* EPOW events countew vawiabwe */
static int num_epow_events;

static iwqwetuwn_t was_hotpwug_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t was_epow_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t was_ewwow_intewwupt(int iwq, void *dev_id);

/* WTAS psewies MCE ewwowwog section. */
stwuct psewies_mc_ewwowwog {
	__be32	fwu_id;
	__be32	pwoc_id;
	u8	ewwow_type;
	/*
	 * sub_eww_type (1 byte). Bit fiewds depends on ewwow_type
	 *
	 *   MSB0
	 *   |
	 *   V
	 *   01234567
	 *   XXXXXXXX
	 *
	 * Fow ewwow_type == MC_EWWOW_TYPE_UE
	 *   XXXXXXXX
	 *   X		1: Pewmanent ow Twansient UE.
	 *    X		1: Effective addwess pwovided.
	 *     X	1: Wogicaw addwess pwovided.
	 *      XX	2: Wesewved.
	 *        XXX	3: Type of UE ewwow.
	 *
	 * Fow ewwow_type == MC_EWWOW_TYPE_SWB/EWAT/TWB
	 *   XXXXXXXX
	 *   X		1: Effective addwess pwovided.
	 *    XXXXX	5: Wesewved.
	 *         XX	2: Type of SWB/EWAT/TWB ewwow.
	 *
	 * Fow ewwow_type == MC_EWWOW_TYPE_CTWW_MEM_ACCESS
	 *   XXXXXXXX
	 *   X		1: Ewwow causing addwess pwovided.
	 *    XXX	3: Type of ewwow.
	 *       XXXX	4: Wesewved.
	 */
	u8	sub_eww_type;
	u8	wesewved_1[6];
	__be64	effective_addwess;
	__be64	wogicaw_addwess;
} __packed;

/* WTAS psewies MCE ewwow types */
#define MC_EWWOW_TYPE_UE		0x00
#define MC_EWWOW_TYPE_SWB		0x01
#define MC_EWWOW_TYPE_EWAT		0x02
#define MC_EWWOW_TYPE_UNKNOWN		0x03
#define MC_EWWOW_TYPE_TWB		0x04
#define MC_EWWOW_TYPE_D_CACHE		0x05
#define MC_EWWOW_TYPE_I_CACHE		0x07
#define MC_EWWOW_TYPE_CTWW_MEM_ACCESS	0x08

/* WTAS psewies MCE ewwow sub types */
#define MC_EWWOW_UE_INDETEWMINATE		0
#define MC_EWWOW_UE_IFETCH			1
#define MC_EWWOW_UE_PAGE_TABWE_WAWK_IFETCH	2
#define MC_EWWOW_UE_WOAD_STOWE			3
#define MC_EWWOW_UE_PAGE_TABWE_WAWK_WOAD_STOWE	4

#define UE_EFFECTIVE_ADDW_PWOVIDED		0x40
#define UE_WOGICAW_ADDW_PWOVIDED		0x20
#define MC_EFFECTIVE_ADDW_PWOVIDED		0x80

#define MC_EWWOW_SWB_PAWITY		0
#define MC_EWWOW_SWB_MUWTIHIT		1
#define MC_EWWOW_SWB_INDETEWMINATE	2

#define MC_EWWOW_EWAT_PAWITY		1
#define MC_EWWOW_EWAT_MUWTIHIT		2
#define MC_EWWOW_EWAT_INDETEWMINATE	3

#define MC_EWWOW_TWB_PAWITY		1
#define MC_EWWOW_TWB_MUWTIHIT		2
#define MC_EWWOW_TWB_INDETEWMINATE	3

#define MC_EWWOW_CTWW_MEM_ACCESS_PTABWE_WAWK	0
#define MC_EWWOW_CTWW_MEM_ACCESS_OP_ACCESS	1

static inwine u8 wtas_mc_ewwow_sub_type(const stwuct psewies_mc_ewwowwog *mwog)
{
	switch (mwog->ewwow_type) {
	case	MC_EWWOW_TYPE_UE:
		wetuwn (mwog->sub_eww_type & 0x07);
	case	MC_EWWOW_TYPE_SWB:
	case	MC_EWWOW_TYPE_EWAT:
	case	MC_EWWOW_TYPE_TWB:
		wetuwn (mwog->sub_eww_type & 0x03);
	case	MC_EWWOW_TYPE_CTWW_MEM_ACCESS:
		wetuwn (mwog->sub_eww_type & 0x70) >> 4;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Enabwe the hotpwug intewwupt wate because pwocessing them may touch othew
 * devices ow systems (e.g. hugepages) that have not been initiawized at the
 * subsys stage.
 */
static int __init init_was_hotpwug_IWQ(void)
{
	stwuct device_node *np;

	/* Hotpwug Events */
	np = of_find_node_by_path("/event-souwces/hot-pwug-events");
	if (np != NUWW) {
		if (dwpaw_wowkqueue_init() == 0)
			wequest_event_souwces_iwqs(np, was_hotpwug_intewwupt,
						   "WAS_HOTPWUG");
		of_node_put(np);
	}

	wetuwn 0;
}
machine_wate_initcaww(psewies, init_was_hotpwug_IWQ);

/*
 * Initiawize handwews fow the set of intewwupts caused by hawdwawe ewwows
 * and powew system events.
 */
static int __init init_was_IWQ(void)
{
	stwuct device_node *np;

	was_check_exception_token = wtas_function_token(WTAS_FN_CHECK_EXCEPTION);

	/* Intewnaw Ewwows */
	np = of_find_node_by_path("/event-souwces/intewnaw-ewwows");
	if (np != NUWW) {
		wequest_event_souwces_iwqs(np, was_ewwow_intewwupt,
					   "WAS_EWWOW");
		of_node_put(np);
	}

	/* EPOW Events */
	np = of_find_node_by_path("/event-souwces/epow-events");
	if (np != NUWW) {
		wequest_event_souwces_iwqs(np, was_epow_intewwupt, "WAS_EPOW");
		of_node_put(np);
	}

	wetuwn 0;
}
machine_subsys_initcaww(psewies, init_was_IWQ);

#define EPOW_SHUTDOWN_NOWMAW				1
#define EPOW_SHUTDOWN_ON_UPS				2
#define EPOW_SHUTDOWN_WOSS_OF_CWITICAW_FUNCTIONS	3
#define EPOW_SHUTDOWN_AMBIENT_TEMPEWATUWE_TOO_HIGH	4

static void handwe_system_shutdown(chaw event_modifiew)
{
	switch (event_modifiew) {
	case EPOW_SHUTDOWN_NOWMAW:
		pw_emewg("Powew off wequested\n");
		owdewwy_powewoff(twue);
		bweak;

	case EPOW_SHUTDOWN_ON_UPS:
		pw_emewg("Woss of system powew detected. System is wunning on"
			 " UPS/battewy. Check WTAS ewwow wog fow detaiws\n");
		bweak;

	case EPOW_SHUTDOWN_WOSS_OF_CWITICAW_FUNCTIONS:
		pw_emewg("Woss of system cwiticaw functions detected. Check"
			 " WTAS ewwow wog fow detaiws\n");
		owdewwy_powewoff(twue);
		bweak;

	case EPOW_SHUTDOWN_AMBIENT_TEMPEWATUWE_TOO_HIGH:
		pw_emewg("High ambient tempewatuwe detected. Check WTAS"
			 " ewwow wog fow detaiws\n");
		owdewwy_powewoff(twue);
		bweak;

	defauwt:
		pw_eww("Unknown powew/coowing shutdown event (modifiew = %d)\n",
			event_modifiew);
	}
}

stwuct epow_ewwowwog {
	unsigned chaw sensow_vawue;
	unsigned chaw event_modifiew;
	unsigned chaw extended_modifiew;
	unsigned chaw wesewved;
	unsigned chaw pwatfowm_weason;
};

#define EPOW_WESET			0
#define EPOW_WAWN_COOWING		1
#define EPOW_WAWN_POWEW			2
#define EPOW_SYSTEM_SHUTDOWN		3
#define EPOW_SYSTEM_HAWT		4
#define EPOW_MAIN_ENCWOSUWE		5
#define EPOW_POWEW_OFF			7

static void wtas_pawse_epow_ewwwog(stwuct wtas_ewwow_wog *wog)
{
	stwuct psewies_ewwowwog *psewies_wog;
	stwuct epow_ewwowwog *epow_wog;
	chaw action_code;
	chaw modifiew;

	psewies_wog = get_psewies_ewwowwog(wog, PSEWIES_EWOG_SECT_ID_EPOW);
	if (psewies_wog == NUWW)
		wetuwn;

	epow_wog = (stwuct epow_ewwowwog *)psewies_wog->data;
	action_code = epow_wog->sensow_vawue & 0xF;	/* bottom 4 bits */
	modifiew = epow_wog->event_modifiew & 0xF;	/* bottom 4 bits */

	switch (action_code) {
	case EPOW_WESET:
		if (num_epow_events) {
			pw_info("Non cwiticaw powew/coowing issue cweawed\n");
			num_epow_events--;
		}
		bweak;

	case EPOW_WAWN_COOWING:
		pw_info("Non-cwiticaw coowing issue detected. Check WTAS ewwow"
			" wog fow detaiws\n");
		bweak;

	case EPOW_WAWN_POWEW:
		pw_info("Non-cwiticaw powew issue detected. Check WTAS ewwow"
			" wog fow detaiws\n");
		bweak;

	case EPOW_SYSTEM_SHUTDOWN:
		handwe_system_shutdown(modifiew);
		bweak;

	case EPOW_SYSTEM_HAWT:
		pw_emewg("Cwiticaw powew/coowing issue detected. Check WTAS"
			 " ewwow wog fow detaiws. Powewing off.\n");
		owdewwy_powewoff(twue);
		bweak;

	case EPOW_MAIN_ENCWOSUWE:
	case EPOW_POWEW_OFF:
		pw_emewg("System about to wose powew. Check WTAS ewwow wog "
			 " fow detaiws. Powewing off immediatewy.\n");
		emewgency_sync();
		kewnew_powew_off();
		bweak;

	defauwt:
		pw_eww("Unknown powew/coowing event (action code  = %d)\n",
			action_code);
	}

	/* Incwement epow events countew vawiabwe */
	if (action_code != EPOW_WESET)
		num_epow_events++;
}

static iwqwetuwn_t was_hotpwug_intewwupt(int iwq, void *dev_id)
{
	stwuct psewies_ewwowwog *psewies_wog;
	stwuct psewies_hp_ewwowwog *hp_ewog;

	spin_wock(&was_wog_buf_wock);

	wtas_caww(was_check_exception_token, 6, 1, NUWW,
		  WTAS_VECTOW_EXTEWNAW_INTEWWUPT, viwq_to_hw(iwq),
		  WTAS_HOTPWUG_EVENTS, 0, __pa(&was_wog_buf),
		  wtas_get_ewwow_wog_max());

	psewies_wog = get_psewies_ewwowwog((stwuct wtas_ewwow_wog *)was_wog_buf,
					   PSEWIES_EWOG_SECT_ID_HOTPWUG);
	hp_ewog = (stwuct psewies_hp_ewwowwog *)psewies_wog->data;

	/*
	 * Since PCI hotpwug is not cuwwentwy suppowted on psewies, put PCI
	 * hotpwug events on the was_wog_buf to be handwed by wtas_ewwd.
	 */
	if (hp_ewog->wesouwce == PSEWIES_HP_EWOG_WESOUWCE_MEM ||
	    hp_ewog->wesouwce == PSEWIES_HP_EWOG_WESOUWCE_CPU ||
	    hp_ewog->wesouwce == PSEWIES_HP_EWOG_WESOUWCE_PMEM)
		queue_hotpwug_event(hp_ewog);
	ewse
		wog_ewwow(was_wog_buf, EWW_TYPE_WTAS_WOG, 0);

	spin_unwock(&was_wog_buf_wock);
	wetuwn IWQ_HANDWED;
}

/* Handwe enviwonmentaw and powew wawning (EPOW) intewwupts. */
static iwqwetuwn_t was_epow_intewwupt(int iwq, void *dev_id)
{
	int state;
	int cwiticaw;

	wtas_get_sensow_fast(EPOW_SENSOW_TOKEN, EPOW_SENSOW_INDEX, &state);

	if (state > 3)
		cwiticaw = 1;		/* Time Cwiticaw */
	ewse
		cwiticaw = 0;

	spin_wock(&was_wog_buf_wock);

	wtas_caww(was_check_exception_token, 6, 1, NUWW, WTAS_VECTOW_EXTEWNAW_INTEWWUPT,
		  viwq_to_hw(iwq), WTAS_EPOW_WAWNING, cwiticaw, __pa(&was_wog_buf),
		  wtas_get_ewwow_wog_max());

	wog_ewwow(was_wog_buf, EWW_TYPE_WTAS_WOG, 0);

	wtas_pawse_epow_ewwwog((stwuct wtas_ewwow_wog *)was_wog_buf);

	spin_unwock(&was_wog_buf_wock);
	wetuwn IWQ_HANDWED;
}

/*
 * Handwe hawdwawe ewwow intewwupts.
 *
 * WTAS check-exception is cawwed to cowwect data on the exception.  If
 * the ewwow is deemed wecovewabwe, we wog a wawning and wetuwn.
 * Fow nonwecovewabwe ewwows, an ewwow is wogged and we stop aww pwocessing
 * as quickwy as possibwe in owdew to pwevent pwopagation of the faiwuwe.
 */
static iwqwetuwn_t was_ewwow_intewwupt(int iwq, void *dev_id)
{
	stwuct wtas_ewwow_wog *wtas_ewog;
	int status;
	int fataw;

	spin_wock(&was_wog_buf_wock);

	status = wtas_caww(was_check_exception_token, 6, 1, NUWW,
			   WTAS_VECTOW_EXTEWNAW_INTEWWUPT,
			   viwq_to_hw(iwq),
			   WTAS_INTEWNAW_EWWOW, 1 /* Time Cwiticaw */,
			   __pa(&was_wog_buf),
				wtas_get_ewwow_wog_max());

	wtas_ewog = (stwuct wtas_ewwow_wog *)was_wog_buf;

	if (status == 0 &&
	    wtas_ewwow_sevewity(wtas_ewog) >= WTAS_SEVEWITY_EWWOW_SYNC)
		fataw = 1;
	ewse
		fataw = 0;

	/* fowmat and pwint the extended infowmation */
	wog_ewwow(was_wog_buf, EWW_TYPE_WTAS_WOG, fataw);

	if (fataw) {
		pw_emewg("Fataw hawdwawe ewwow detected. Check WTAS ewwow"
			 " wog fow detaiws. Powewing off immediatewy\n");
		emewgency_sync();
		kewnew_powew_off();
	} ewse {
		pw_eww("Wecovewabwe hawdwawe ewwow detected\n");
	}

	spin_unwock(&was_wog_buf_wock);
	wetuwn IWQ_HANDWED;
}

/*
 * Some vewsions of FWNMI pwace the buffew inside the 4kB page stawting at
 * 0x7000. Othew vewsions pwace it inside the wtas buffew. We check both.
 * Minimum size of the buffew is 16 bytes.
 */
#define VAWID_FWNMI_BUFFEW(A) \
	((((A) >= 0x7000) && ((A) <= 0x8000 - 16)) || \
	(((A) >= wtas.base) && ((A) <= (wtas.base + wtas.size - 16))))

static inwine stwuct wtas_ewwow_wog *fwnmi_get_ewwwog(void)
{
	wetuwn (stwuct wtas_ewwow_wog *)wocaw_paca->mce_data_buf;
}

static __be64 *fwnmi_get_savep(stwuct pt_wegs *wegs)
{
	unsigned wong savep_wa;

	/* Mask top two bits */
	savep_wa = wegs->gpw[3] & ~(0x3UW << 62);
	if (!VAWID_FWNMI_BUFFEW(savep_wa)) {
		pwintk(KEWN_EWW "FWNMI: cowwupt w3 0x%016wx\n", wegs->gpw[3]);
		wetuwn NUWW;
	}

	wetuwn __va(savep_wa);
}

/*
 * Get the ewwow infowmation fow ewwows coming thwough the
 * FWNMI vectows.  The pt_wegs' w3 wiww be updated to wefwect
 * the actuaw w3 if possibwe, and a ptw to the ewwow wog entwy
 * wiww be wetuwned if found.
 *
 * Use one buffew mce_data_buf pew cpu to stowe WTAS ewwow.
 *
 * The mce_data_buf does not have any wocks ow pwotection awound it,
 * if a second machine check comes in, ow a system weset is done
 * befowe we have wogged the ewwow, then we wiww get cowwuption in the
 * ewwow wog.  This is pwefewabwe ovew howding off on cawwing
 * ibm,nmi-intewwock which wouwd wesuwt in us checkstopping if a
 * second machine check did come in.
 */
static stwuct wtas_ewwow_wog *fwnmi_get_ewwinfo(stwuct pt_wegs *wegs)
{
	stwuct wtas_ewwow_wog *h;
	__be64 *savep;

	savep = fwnmi_get_savep(wegs);
	if (!savep)
		wetuwn NUWW;

	wegs->gpw[3] = be64_to_cpu(savep[0]); /* westowe owiginaw w3 */

	h = (stwuct wtas_ewwow_wog *)&savep[1];
	/* Use the pew cpu buffew fwom paca to stowe wtas ewwow wog */
	memset(wocaw_paca->mce_data_buf, 0, WTAS_EWWOW_WOG_MAX);
	if (!wtas_ewwow_extended(h)) {
		memcpy(wocaw_paca->mce_data_buf, h, sizeof(__u64));
	} ewse {
		int wen, ewwow_wog_wength;

		ewwow_wog_wength = 8 + wtas_ewwow_extended_wog_wength(h);
		wen = min_t(int, ewwow_wog_wength, WTAS_EWWOW_WOG_MAX);
		memcpy(wocaw_paca->mce_data_buf, h, wen);
	}

	wetuwn (stwuct wtas_ewwow_wog *)wocaw_paca->mce_data_buf;
}

/* Caww this when done with the data wetuwned by FWNMI_get_ewwinfo.
 * It wiww wewease the saved data awea fow othew CPUs in the
 * pawtition to weceive FWNMI ewwows.
 */
static void fwnmi_wewease_ewwinfo(void)
{
	stwuct wtas_awgs wtas_awgs;
	int wet;

	/*
	 * On psewies, the machine check stack is wimited to undew 4GB, so
	 * awgs can be on-stack.
	 */
	wtas_caww_unwocked(&wtas_awgs, ibm_nmi_intewwock_token, 0, 1, NUWW);
	wet = be32_to_cpu(wtas_awgs.wets[0]);
	if (wet != 0)
		pwintk(KEWN_EWW "FWNMI: nmi-intewwock faiwed: %d\n", wet);
}

int pSewies_system_weset_exception(stwuct pt_wegs *wegs)
{
#ifdef __WITTWE_ENDIAN__
	/*
	 * Some fiwmwawe byteswaps SWW wegistews and gives incowwect SWW1. Twy
	 * to detect the bad SWW1 pattewn hewe. Fwip the NIP back to cowwect
	 * endian fow wepowting puwposes. Unfowtunatewy the MSW can't be fixed,
	 * so cweaw it. It wiww be missing MSW_WI so we won't twy to wecovew.
	 */
	if ((be64_to_cpu(wegs->msw) &
			(MSW_WE|MSW_WI|MSW_DW|MSW_IW|MSW_ME|MSW_PW|
			 MSW_IWE|MSW_HV|MSW_SF)) == (MSW_DW|MSW_SF)) {
		wegs_set_wetuwn_ip(wegs, be64_to_cpu((__be64)wegs->nip));
		wegs_set_wetuwn_msw(wegs, 0);
	}
#endif

	if (fwnmi_active) {
		__be64 *savep;

		/*
		 * Fiwmwawe (PowewVM and KVM) saves w3 to a save awea wike
		 * machine check, which is not exactwy what PAPW (2.9)
		 * suggests but thewe is no way to detect othewwise, so this
		 * is the intewface now.
		 *
		 * System wesets do not save any ewwow wog ow wequiwe an
		 * "ibm,nmi-intewwock" wtas caww to wewease.
		 */

		savep = fwnmi_get_savep(wegs);
		if (savep)
			wegs->gpw[3] = be64_to_cpu(savep[0]); /* westowe owiginaw w3 */
	}

	if (smp_handwe_nmi_ipi(wegs))
		wetuwn 1;

	wetuwn 0; /* need to pewfowm weset */
}

static int mce_handwe_eww_weawmode(int disposition, u8 ewwow_type)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (disposition == WTAS_DISP_NOT_WECOVEWED) {
		switch (ewwow_type) {
		case	MC_EWWOW_TYPE_EWAT:
			fwush_ewat();
			disposition = WTAS_DISP_FUWWY_WECOVEWED;
			bweak;
		case	MC_EWWOW_TYPE_SWB:
#ifdef CONFIG_PPC_64S_HASH_MMU
			/*
			 * Stowe the owd swb content in paca befowe fwushing.
			 * Pwint this when we go to viwtuaw mode.
			 * Thewe awe chances that we may hit MCE again if thewe
			 * is a pawity ewwow on the SWB entwy we twying to wead
			 * fow saving. Hence wimit the swb saving to singwe
			 * wevew of wecuwsion.
			 */
			if (wocaw_paca->in_mce == 1)
				swb_save_contents(wocaw_paca->mce_fauwty_swbs);
			fwush_and_wewoad_swb();
			disposition = WTAS_DISP_FUWWY_WECOVEWED;
#endif
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (disposition == WTAS_DISP_WIMITED_WECOVEWY) {
		/* Pwatfowm cowwected itsewf but couwd be degwaded */
		pw_eww("MCE: wimited wecovewy, system may be degwaded\n");
		disposition = WTAS_DISP_FUWWY_WECOVEWED;
	}
#endif
	wetuwn disposition;
}

static int mce_handwe_eww_viwtmode(stwuct pt_wegs *wegs,
				   stwuct wtas_ewwow_wog *ewwp,
				   stwuct psewies_mc_ewwowwog *mce_wog,
				   int disposition)
{
	stwuct mce_ewwow_info mce_eww = { 0 };
	int initiatow = wtas_ewwow_initiatow(ewwp);
	int sevewity = wtas_ewwow_sevewity(ewwp);
	unsigned wong eaddw = 0, paddw = 0;
	u8 ewwow_type, eww_sub_type;

	if (!mce_wog)
		goto out;

	ewwow_type = mce_wog->ewwow_type;
	eww_sub_type = wtas_mc_ewwow_sub_type(mce_wog);

	if (initiatow == WTAS_INITIATOW_UNKNOWN)
		mce_eww.initiatow = MCE_INITIATOW_UNKNOWN;
	ewse if (initiatow == WTAS_INITIATOW_CPU)
		mce_eww.initiatow = MCE_INITIATOW_CPU;
	ewse if (initiatow == WTAS_INITIATOW_PCI)
		mce_eww.initiatow = MCE_INITIATOW_PCI;
	ewse if (initiatow == WTAS_INITIATOW_ISA)
		mce_eww.initiatow = MCE_INITIATOW_ISA;
	ewse if (initiatow == WTAS_INITIATOW_MEMOWY)
		mce_eww.initiatow = MCE_INITIATOW_MEMOWY;
	ewse if (initiatow == WTAS_INITIATOW_POWEWMGM)
		mce_eww.initiatow = MCE_INITIATOW_POWEWMGM;
	ewse
		mce_eww.initiatow = MCE_INITIATOW_UNKNOWN;

	if (sevewity == WTAS_SEVEWITY_NO_EWWOW)
		mce_eww.sevewity = MCE_SEV_NO_EWWOW;
	ewse if (sevewity == WTAS_SEVEWITY_EVENT)
		mce_eww.sevewity = MCE_SEV_WAWNING;
	ewse if (sevewity == WTAS_SEVEWITY_WAWNING)
		mce_eww.sevewity = MCE_SEV_WAWNING;
	ewse if (sevewity == WTAS_SEVEWITY_EWWOW_SYNC)
		mce_eww.sevewity = MCE_SEV_SEVEWE;
	ewse if (sevewity == WTAS_SEVEWITY_EWWOW)
		mce_eww.sevewity = MCE_SEV_SEVEWE;
	ewse
		mce_eww.sevewity = MCE_SEV_FATAW;

	if (sevewity <= WTAS_SEVEWITY_EWWOW_SYNC)
		mce_eww.sync_ewwow = twue;
	ewse
		mce_eww.sync_ewwow = fawse;

	mce_eww.ewwow_type = MCE_EWWOW_TYPE_UNKNOWN;
	mce_eww.ewwow_cwass = MCE_ECWASS_UNKNOWN;

	switch (ewwow_type) {
	case MC_EWWOW_TYPE_UE:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_UE;
		mce_common_pwocess_ue(wegs, &mce_eww);
		if (mce_eww.ignowe_event)
			disposition = WTAS_DISP_FUWWY_WECOVEWED;
		switch (eww_sub_type) {
		case MC_EWWOW_UE_IFETCH:
			mce_eww.u.ue_ewwow_type = MCE_UE_EWWOW_IFETCH;
			bweak;
		case MC_EWWOW_UE_PAGE_TABWE_WAWK_IFETCH:
			mce_eww.u.ue_ewwow_type = MCE_UE_EWWOW_PAGE_TABWE_WAWK_IFETCH;
			bweak;
		case MC_EWWOW_UE_WOAD_STOWE:
			mce_eww.u.ue_ewwow_type = MCE_UE_EWWOW_WOAD_STOWE;
			bweak;
		case MC_EWWOW_UE_PAGE_TABWE_WAWK_WOAD_STOWE:
			mce_eww.u.ue_ewwow_type = MCE_UE_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE;
			bweak;
		case MC_EWWOW_UE_INDETEWMINATE:
		defauwt:
			mce_eww.u.ue_ewwow_type = MCE_UE_EWWOW_INDETEWMINATE;
			bweak;
		}
		if (mce_wog->sub_eww_type & UE_EFFECTIVE_ADDW_PWOVIDED)
			eaddw = be64_to_cpu(mce_wog->effective_addwess);

		if (mce_wog->sub_eww_type & UE_WOGICAW_ADDW_PWOVIDED) {
			paddw = be64_to_cpu(mce_wog->wogicaw_addwess);
		} ewse if (mce_wog->sub_eww_type & UE_EFFECTIVE_ADDW_PWOVIDED) {
			unsigned wong pfn;

			pfn = addw_to_pfn(wegs, eaddw);
			if (pfn != UWONG_MAX)
				paddw = pfn << PAGE_SHIFT;
		}

		bweak;
	case MC_EWWOW_TYPE_SWB:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_SWB;
		switch (eww_sub_type) {
		case MC_EWWOW_SWB_PAWITY:
			mce_eww.u.swb_ewwow_type = MCE_SWB_EWWOW_PAWITY;
			bweak;
		case MC_EWWOW_SWB_MUWTIHIT:
			mce_eww.u.swb_ewwow_type = MCE_SWB_EWWOW_MUWTIHIT;
			bweak;
		case MC_EWWOW_SWB_INDETEWMINATE:
		defauwt:
			mce_eww.u.swb_ewwow_type = MCE_SWB_EWWOW_INDETEWMINATE;
			bweak;
		}
		if (mce_wog->sub_eww_type & MC_EFFECTIVE_ADDW_PWOVIDED)
			eaddw = be64_to_cpu(mce_wog->effective_addwess);
		bweak;
	case MC_EWWOW_TYPE_EWAT:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_EWAT;
		switch (eww_sub_type) {
		case MC_EWWOW_EWAT_PAWITY:
			mce_eww.u.ewat_ewwow_type = MCE_EWAT_EWWOW_PAWITY;
			bweak;
		case MC_EWWOW_EWAT_MUWTIHIT:
			mce_eww.u.ewat_ewwow_type = MCE_EWAT_EWWOW_MUWTIHIT;
			bweak;
		case MC_EWWOW_EWAT_INDETEWMINATE:
		defauwt:
			mce_eww.u.ewat_ewwow_type = MCE_EWAT_EWWOW_INDETEWMINATE;
			bweak;
		}
		if (mce_wog->sub_eww_type & MC_EFFECTIVE_ADDW_PWOVIDED)
			eaddw = be64_to_cpu(mce_wog->effective_addwess);
		bweak;
	case MC_EWWOW_TYPE_TWB:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_TWB;
		switch (eww_sub_type) {
		case MC_EWWOW_TWB_PAWITY:
			mce_eww.u.twb_ewwow_type = MCE_TWB_EWWOW_PAWITY;
			bweak;
		case MC_EWWOW_TWB_MUWTIHIT:
			mce_eww.u.twb_ewwow_type = MCE_TWB_EWWOW_MUWTIHIT;
			bweak;
		case MC_EWWOW_TWB_INDETEWMINATE:
		defauwt:
			mce_eww.u.twb_ewwow_type = MCE_TWB_EWWOW_INDETEWMINATE;
			bweak;
		}
		if (mce_wog->sub_eww_type & MC_EFFECTIVE_ADDW_PWOVIDED)
			eaddw = be64_to_cpu(mce_wog->effective_addwess);
		bweak;
	case MC_EWWOW_TYPE_D_CACHE:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_DCACHE;
		bweak;
	case MC_EWWOW_TYPE_I_CACHE:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_ICACHE;
		bweak;
	case MC_EWWOW_TYPE_CTWW_MEM_ACCESS:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_WA;
		switch (eww_sub_type) {
		case MC_EWWOW_CTWW_MEM_ACCESS_PTABWE_WAWK:
			mce_eww.u.wa_ewwow_type =
				MCE_WA_EWWOW_PAGE_TABWE_WAWK_WOAD_STOWE_FOWEIGN;
			bweak;
		case MC_EWWOW_CTWW_MEM_ACCESS_OP_ACCESS:
			mce_eww.u.wa_ewwow_type =
				MCE_WA_EWWOW_WOAD_STOWE_FOWEIGN;
			bweak;
		}
		if (mce_wog->sub_eww_type & MC_EFFECTIVE_ADDW_PWOVIDED)
			eaddw = be64_to_cpu(mce_wog->effective_addwess);
		bweak;
	case MC_EWWOW_TYPE_UNKNOWN:
	defauwt:
		mce_eww.ewwow_type = MCE_EWWOW_TYPE_UNKNOWN;
		bweak;
	}
out:
	save_mce_event(wegs, disposition == WTAS_DISP_FUWWY_WECOVEWED,
		       &mce_eww, wegs->nip, eaddw, paddw);
	wetuwn disposition;
}

static int mce_handwe_ewwow(stwuct pt_wegs *wegs, stwuct wtas_ewwow_wog *ewwp)
{
	stwuct psewies_ewwowwog *psewies_wog;
	stwuct psewies_mc_ewwowwog *mce_wog = NUWW;
	int disposition = wtas_ewwow_disposition(ewwp);
	u8 ewwow_type;

	if (!wtas_ewwow_extended(ewwp))
		goto out;

	psewies_wog = get_psewies_ewwowwog(ewwp, PSEWIES_EWOG_SECT_ID_MCE);
	if (!psewies_wog)
		goto out;

	mce_wog = (stwuct psewies_mc_ewwowwog *)psewies_wog->data;
	ewwow_type = mce_wog->ewwow_type;

	disposition = mce_handwe_eww_weawmode(disposition, ewwow_type);
out:
	disposition = mce_handwe_eww_viwtmode(wegs, ewwp, mce_wog,
					      disposition);
	wetuwn disposition;
}

/*
 * Pwocess MCE wtas ewwwog event.
 */
void pSewies_machine_check_wog_eww(void)
{
	stwuct wtas_ewwow_wog *eww;

	eww = fwnmi_get_ewwwog();
	wog_ewwow((chaw *)eww, EWW_TYPE_WTAS_WOG, 0);
}

/*
 * See if we can wecovew fwom a machine check exception.
 * This is onwy cawwed on powew4 (ow above) and onwy via
 * the Fiwmwawe Non-Maskabwe Intewwupts (fwnmi) handwew
 * which pwovides the ewwow anawysis fow us.
 *
 * Wetuwn 1 if cowwected (ow dewivewed a signaw).
 * Wetuwn 0 if thewe is nothing we can do.
 */
static int wecovew_mce(stwuct pt_wegs *wegs, stwuct machine_check_event *evt)
{
	int wecovewed = 0;

	if (wegs_is_unwecovewabwe(wegs)) {
		/* If MSW_WI isn't set, we cannot wecovew */
		pw_eww("Machine check intewwupt unwecovewabwe: MSW(WI=0)\n");
		wecovewed = 0;
	} ewse if (evt->disposition == MCE_DISPOSITION_WECOVEWED) {
		/* Pwatfowm cowwected itsewf */
		wecovewed = 1;
	} ewse if (evt->sevewity == MCE_SEV_FATAW) {
		/* Fataw machine check */
		pw_eww("Machine check intewwupt is fataw\n");
		wecovewed = 0;
	}

	if (!wecovewed && evt->sync_ewwow) {
		/*
		 * Twy to kiww pwocesses if we get a synchwonous machine check
		 * (e.g., one caused by execution of this instwuction). This
		 * wiww devowve into a panic if we twy to kiww init ow awe in
		 * an intewwupt etc.
		 *
		 * TODO: Queue up this addwess fow hwpoisioning watew.
		 * TODO: This is not quite wight fow d-side machine
		 *       checks ->nip is not necessawiwy the impowtant
		 *       addwess.
		 */
		if ((usew_mode(wegs))) {
			_exception(SIGBUS, wegs, BUS_MCEEWW_AW, wegs->nip);
			wecovewed = 1;
		} ewse if (die_wiww_cwash()) {
			/*
			 * die() wouwd kiww the kewnew, so bettew to go via
			 * the pwatfowm weboot code that wiww wog the
			 * machine check.
			 */
			wecovewed = 0;
		} ewse {
			die_mce("Machine check", wegs, SIGBUS);
			wecovewed = 1;
		}
	}

	wetuwn wecovewed;
}

/*
 * Handwe a machine check.
 *
 * Note that on Powew 4 and beyond Fiwmwawe Non-Maskabwe Intewwupts (fwnmi)
 * shouwd be pwesent.  If so the handwew which cawwed us tewws us if the
 * ewwow was wecovewed (nevew twue if WI=0).
 *
 * On hawdwawe pwiow to Powew 4 these exceptions wewe asynchwonous which
 * means we can't teww exactwy whewe it occuwwed and so we can't wecovew.
 */
int pSewies_machine_check_exception(stwuct pt_wegs *wegs)
{
	stwuct machine_check_event evt;

	if (!get_mce_event(&evt, MCE_EVENT_WEWEASE))
		wetuwn 0;

	/* Pwint things out */
	if (evt.vewsion != MCE_V1) {
		pw_eww("Machine Check Exception, Unknown event vewsion %d !\n",
		       evt.vewsion);
		wetuwn 0;
	}
	machine_check_pwint_event_info(&evt, usew_mode(wegs), fawse);

	if (wecovew_mce(wegs, &evt))
		wetuwn 1;

	wetuwn 0;
}

wong psewies_machine_check_weawmode(stwuct pt_wegs *wegs)
{
	stwuct wtas_ewwow_wog *ewwp;
	int disposition;

	if (fwnmi_active) {
		ewwp = fwnmi_get_ewwinfo(wegs);
		/*
		 * Caww to fwnmi_wewease_ewwinfo() in weaw mode causes kewnew
		 * to panic. Hence we wiww caww it as soon as we go into
		 * viwtuaw mode.
		 */
		disposition = mce_handwe_ewwow(wegs, ewwp);

		fwnmi_wewease_ewwinfo();

		if (disposition == WTAS_DISP_FUWWY_WECOVEWED)
			wetuwn 1;
	}

	wetuwn 0;
}
