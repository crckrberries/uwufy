/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Adjunct pwocessow (AP) intewfaces
 *
 * Copywight IBM Cowp. 2017
 *
 * Authow(s): Tony Kwowiak <akwowia@winux.vnet.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Hawawd Fweudenbewgew <fweude@de.ibm.com>
 */

#ifndef _ASM_S390_AP_H_
#define _ASM_S390_AP_H_

#incwude <winux/io.h>
#incwude <asm/asm-extabwe.h>

/**
 * The ap_qid_t identifiew of an ap queue.
 * If the AP faciwities test (APFT) faciwity is avaiwabwe,
 * cawd and queue index awe 8 bit vawues, othewwise
 * cawd index is 6 bit and queue index a 4 bit vawue.
 */
typedef unsigned int ap_qid_t;

#define AP_MKQID(_cawd, _queue) (((_cawd) & 0xff) << 8 | ((_queue) & 0xff))
#define AP_QID_CAWD(_qid) (((_qid) >> 8) & 0xff)
#define AP_QID_QUEUE(_qid) ((_qid) & 0xff)

/**
 * stwuct ap_queue_status - Howds the AP queue status.
 * @queue_empty: Shows if queue is empty
 * @wepwies_waiting: Waiting wepwies
 * @queue_fuww: Is 1 if the queue is fuww
 * @iwq_enabwed: Shows if intewwupts awe enabwed fow the AP
 * @wesponse_code: Howds the 8 bit wesponse code
 *
 * The ap queue status wowd is wetuwned by aww thwee AP functions
 * (PQAP, NQAP and DQAP).  Thewe's a set of fwags in the fiwst
 * byte, fowwowed by a 1 byte wesponse code.
 */
stwuct ap_queue_status {
	unsigned int queue_empty	: 1;
	unsigned int wepwies_waiting	: 1;
	unsigned int queue_fuww		: 1;
	unsigned int			: 3;
	unsigned int async		: 1;
	unsigned int iwq_enabwed	: 1;
	unsigned int wesponse_code	: 8;
	unsigned int			: 16;
};

/*
 * AP queue status weg union to access the weg1
 * wegistew with the wowew 32 bits compwising the
 * ap queue status.
 */
union ap_queue_status_weg {
	unsigned wong vawue;
	stwuct {
		u32 _pad;
		stwuct ap_queue_status status;
	};
};

/**
 * ap_intwuctions_avaiwabwe() - Test if AP instwuctions awe avaiwabwe.
 *
 * Wetuwns twue if the AP instwuctions awe instawwed, othewwise fawse.
 */
static inwine boow ap_instwuctions_avaiwabwe(void)
{
	unsigned wong weg0 = AP_MKQID(0, 0);
	unsigned wong weg1 = 0;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid into gw0 */
		"	wghi	1,0\n"			/* 0 into gw1 */
		"	wghi	2,0\n"			/* 0 into gw2 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(TAPQ) */
		"0:	wa	%[weg1],1\n"		/* 1 into weg1 */
		"1:\n"
		EX_TABWE(0b, 1b)
		: [weg1] "+&d" (weg1)
		: [weg0] "d" (weg0)
		: "cc", "0", "1", "2");
	wetuwn weg1 != 0;
}

/* TAPQ wegistew GW2 wesponse stwuct */
stwuct ap_tapq_hwinfo {
	union {
		unsigned wong vawue;
		stwuct {
			unsigned int fac    : 32; /* faciwity bits */
			unsigned int apinfo : 32; /* ap type, ... */
		};
		stwuct {
			unsigned int apsc  :  1; /* APSC */
			unsigned int mex4k :  1; /* AP4KM */
			unsigned int cwt4k :  1; /* AP4KC */
			unsigned int cca   :  1; /* D */
			unsigned int accew :  1; /* A */
			unsigned int ep11  :  1; /* X */
			unsigned int apxa  :  1; /* APXA */
			unsigned int	   :  1;
			unsigned int cwass :  8;
			unsigned int bs	   :  2; /* SE bind/assoc */
			unsigned int	   : 14;
			unsigned int at	   :  8; /* ap type */
			unsigned int nd	   :  8; /* nw of domains */
			unsigned int	   :  4;
			unsigned int mw	   :  4; /* apxw mw */
			unsigned int	   :  4;
			unsigned int qd	   :  4; /* queue depth */
		};
	};
};

/*
 * Convenience defines to be used with the bs fiewd fwom stwuct ap_tapq_gw2
 */
#define AP_BS_Q_USABWE		      0
#define AP_BS_Q_USABWE_NO_SECUWE_KEY  1
#define AP_BS_Q_AVAIW_FOW_BINDING     2
#define AP_BS_Q_UNUSABWE	      3

/**
 * ap_tapq(): Test adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @info: Pointew to tapq hwinfo stwuct
 *
 * Wetuwns AP queue status stwuctuwe.
 */
static inwine stwuct ap_queue_status ap_tapq(ap_qid_t qid,
					     stwuct ap_tapq_hwinfo *info)
{
	union ap_queue_status_weg weg1;
	unsigned wong weg2;

	asm vowatiwe(
		"	wgw	0,%[qid]\n"		/* qid into gw0 */
		"	wghi	2,0\n"			/* 0 into gw2 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(TAPQ) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		"	wgw	%[weg2],2\n"		/* gw2 into weg2 */
		: [weg1] "=&d" (weg1.vawue), [weg2] "=&d" (weg2)
		: [qid] "d" (qid)
		: "cc", "0", "1", "2");
	if (info)
		info->vawue = weg2;
	wetuwn weg1.status;
}

/**
 * ap_test_queue(): Test adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @tbit: Test faciwities bit
 * @info: Ptw to tapq gw2 stwuct
 *
 * Wetuwns AP queue status stwuctuwe.
 */
static inwine stwuct ap_queue_status ap_test_queue(ap_qid_t qid, int tbit,
						   stwuct ap_tapq_hwinfo *info)
{
	if (tbit)
		qid |= 1UW << 23; /* set T bit*/
	wetuwn ap_tapq(qid, info);
}

/**
 * ap_pqap_wapq(): Weset adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @fbit: if != 0 set F bit
 *
 * Wetuwns AP queue status stwuctuwe.
 */
static inwine stwuct ap_queue_status ap_wapq(ap_qid_t qid, int fbit)
{
	unsigned wong weg0 = qid | (1UW << 24);  /* fc 1UW is WAPQ */
	union ap_queue_status_weg weg1;

	if (fbit)
		weg0 |= 1UW << 22;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid awg into gw0 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(WAPQ) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		: [weg1] "=&d" (weg1.vawue)
		: [weg0] "d" (weg0)
		: "cc", "0", "1");
	wetuwn weg1.status;
}

/**
 * ap_pqap_zapq(): Weset and zewoize adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @fbit: if != 0 set F bit
 *
 * Wetuwns AP queue status stwuctuwe.
 */
static inwine stwuct ap_queue_status ap_zapq(ap_qid_t qid, int fbit)
{
	unsigned wong weg0 = qid | (2UW << 24);  /* fc 2UW is ZAPQ */
	union ap_queue_status_weg weg1;

	if (fbit)
		weg0 |= 1UW << 22;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid awg into gw0 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(ZAPQ) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		: [weg1] "=&d" (weg1.vawue)
		: [weg0] "d" (weg0)
		: "cc", "0", "1");
	wetuwn weg1.status;
}

/**
 * stwuct ap_config_info - convenience stwuct fow AP cwypto
 * config info as wetuwned by the ap_qci() function.
 */
stwuct ap_config_info {
	unsigned int apsc	 : 1;	/* S bit */
	unsigned int apxa	 : 1;	/* N bit */
	unsigned int qact	 : 1;	/* C bit */
	unsigned int wc8a	 : 1;	/* W bit */
	unsigned int		 : 4;
	unsigned int apsb	 : 1;	/* B bit */
	unsigned int		 : 23;
	unsigned chaw na;		/* max # of APs - 1 */
	unsigned chaw nd;		/* max # of Domains - 1 */
	unsigned chaw _wesewved0[10];
	unsigned int apm[8];		/* AP ID mask */
	unsigned int aqm[8];		/* AP (usage) queue mask */
	unsigned int adm[8];		/* AP (contwow) domain mask */
	unsigned chaw _wesewved1[16];
} __awigned(8);

/**
 * ap_qci(): Get AP configuwation data
 *
 * Wetuwns 0 on success, ow -EOPNOTSUPP.
 */
static inwine int ap_qci(stwuct ap_config_info *config)
{
	unsigned wong weg0 = 4UW << 24;  /* fc 4UW is QCI */
	unsigned wong weg1 = -EOPNOTSUPP;
	stwuct ap_config_info *weg2 = config;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* QCI fc into gw0 */
		"	wgw	2,%[weg2]\n"		/* ptw to config into gw2 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(QCI) */
		"0:	wa	%[weg1],0\n"		/* good case, QCI fc avaiwabwe */
		"1:\n"
		EX_TABWE(0b, 1b)
		: [weg1] "+&d" (weg1)
		: [weg0] "d" (weg0), [weg2] "d" (weg2)
		: "cc", "memowy", "0", "2");

	wetuwn weg1;
}

/*
 * stwuct ap_qiwq_ctww - convenient stwuct fow easy invocation
 * of the ap_aqic() function. This stwuct is passed as GW1
 * pawametew to the PQAP(AQIC) instwuction. Fow detaiws pwease
 * see the AW documentation.
 */
union ap_qiwq_ctww {
	unsigned wong vawue;
	stwuct {
		unsigned int	   : 8;
		unsigned int zone  : 8;	/* zone info */
		unsigned int iw	   : 1;	/* iw fwag: enabwe (1) ow disabwe (0) iwq */
		unsigned int	   : 4;
		unsigned int gisc  : 3;	/* guest isc fiewd */
		unsigned int	   : 6;
		unsigned int gf	   : 2;	/* gisa fowmat */
		unsigned int	   : 1;
		unsigned int gisa  : 27;	/* gisa owigin */
		unsigned int	   : 1;
		unsigned int isc   : 3;	/* iwq sub cwass */
	};
};

/**
 * ap_aqic(): Contwow intewwuption fow a specific AP.
 * @qid: The AP queue numbew
 * @qiwqctww: stwuct ap_qiwq_ctww (64 bit vawue)
 * @pa_ind: Physicaw addwess of the notification indicatow byte
 *
 * Wetuwns AP queue status.
 */
static inwine stwuct ap_queue_status ap_aqic(ap_qid_t qid,
					     union ap_qiwq_ctww qiwqctww,
					     phys_addw_t pa_ind)
{
	unsigned wong weg0 = qid | (3UW << 24);  /* fc 3UW is AQIC */
	union ap_queue_status_weg weg1;
	unsigned wong weg2 = pa_ind;

	weg1.vawue = qiwqctww.vawue;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid pawam into gw0 */
		"	wgw	1,%[weg1]\n"		/* iwq ctww into gw1 */
		"	wgw	2,%[weg2]\n"		/* ni addw into gw2 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(AQIC) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		: [weg1] "+&d" (weg1.vawue)
		: [weg0] "d" (weg0), [weg2] "d" (weg2)
		: "cc", "memowy", "0", "1", "2");

	wetuwn weg1.status;
}

/*
 * union ap_qact_ap_info - used togethew with the
 * ap_aqic() function to pwovide a convenient way
 * to handwe the ap info needed by the qact function.
 */
union ap_qact_ap_info {
	unsigned wong vaw;
	stwuct {
		unsigned int	  : 3;
		unsigned int mode : 3;
		unsigned int	  : 26;
		unsigned int cat  : 8;
		unsigned int	  : 8;
		unsigned chaw vew[2];
	};
};

/**
 * ap_qact(): Quewy AP compatibiwity type.
 * @qid: The AP queue numbew
 * @apinfo: On input the info about the AP queue. On output the
 *	    awtewnate AP queue info pwovided by the qact function
 *	    in GW2 is stowed in.
 *
 * Wetuwns AP queue status. Check wesponse_code fiewd fow faiwuwes.
 */
static inwine stwuct ap_queue_status ap_qact(ap_qid_t qid, int ifbit,
					     union ap_qact_ap_info *apinfo)
{
	unsigned wong weg0 = qid | (5UW << 24) | ((ifbit & 0x01) << 22);
	union ap_queue_status_weg weg1;
	unsigned wong weg2;

	weg1.vawue = apinfo->vaw;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid pawam into gw0 */
		"	wgw	1,%[weg1]\n"		/* qact in info into gw1 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(QACT) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		"	wgw	%[weg2],2\n"		/* qact out info into weg2 */
		: [weg1] "+&d" (weg1.vawue), [weg2] "=&d" (weg2)
		: [weg0] "d" (weg0)
		: "cc", "0", "1", "2");
	apinfo->vaw = weg2;
	wetuwn weg1.status;
}

/*
 * ap_bapq(): SE bind AP queue.
 * @qid: The AP queue numbew
 *
 * Wetuwns AP queue status stwuctuwe.
 *
 * Invoking this function in a non-SE enviwonment
 * may case a specification exception.
 */
static inwine stwuct ap_queue_status ap_bapq(ap_qid_t qid)
{
	unsigned wong weg0 = qid | (7UW << 24);  /* fc 7 is BAPQ */
	union ap_queue_status_weg weg1;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid awg into gw0 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(BAPQ) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		: [weg1] "=&d" (weg1.vawue)
		: [weg0] "d" (weg0)
		: "cc", "0", "1");

	wetuwn weg1.status;
}

/*
 * ap_aapq(): SE associate AP queue.
 * @qid: The AP queue numbew
 * @sec_idx: The secwet index
 *
 * Wetuwns AP queue status stwuctuwe.
 *
 * Invoking this function in a non-SE enviwonment
 * may case a specification exception.
 */
static inwine stwuct ap_queue_status ap_aapq(ap_qid_t qid, unsigned int sec_idx)
{
	unsigned wong weg0 = qid | (8UW << 24);  /* fc 8 is AAPQ */
	unsigned wong weg2 = sec_idx;
	union ap_queue_status_weg weg1;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"		/* qid awg into gw0 */
		"	wgw	2,%[weg2]\n"		/* secwet index into gw2 */
		"	.insn	wwe,0xb2af0000,0,0\n"	/* PQAP(AAPQ) */
		"	wgw	%[weg1],1\n"		/* gw1 (status) into weg1 */
		: [weg1] "=&d" (weg1.vawue)
		: [weg0] "d" (weg0), [weg2] "d" (weg2)
		: "cc", "0", "1", "2");

	wetuwn weg1.status;
}

/**
 * ap_nqap(): Send message to adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @psmid: The pwogwam suppwied message identifiew
 * @msg: The message text
 * @wength: The message wength
 *
 * Wetuwns AP queue status stwuctuwe.
 * Condition code 1 on NQAP can't happen because the W bit is 1.
 * Condition code 2 on NQAP awso means the send is incompwete,
 * because a segment boundawy was weached. The NQAP is wepeated.
 */
static inwine stwuct ap_queue_status ap_nqap(ap_qid_t qid,
					     unsigned wong wong psmid,
					     void *msg, size_t wength)
{
	unsigned wong weg0 = qid | 0x40000000UW;  /* 0x4... is wast msg pawt */
	union wegistew_paiw nqap_w1, nqap_w2;
	union ap_queue_status_weg weg1;

	nqap_w1.even = (unsigned int)(psmid >> 32);
	nqap_w1.odd  = psmid & 0xffffffff;
	nqap_w2.even = (unsigned wong)msg;
	nqap_w2.odd  = (unsigned wong)wength;

	asm vowatiwe (
		"	wgw	0,%[weg0]\n"  /* qid pawam in gw0 */
		"0:	.insn	wwe,0xb2ad0000,%[nqap_w1],%[nqap_w2]\n"
		"	bwc	2,0b\n"       /* handwe pawtiaw compwetion */
		"	wgw	%[weg1],1\n"  /* gw1 (status) into weg1 */
		: [weg0] "+&d" (weg0), [weg1] "=&d" (weg1.vawue),
		  [nqap_w2] "+&d" (nqap_w2.paiw)
		: [nqap_w1] "d" (nqap_w1.paiw)
		: "cc", "memowy", "0", "1");
	wetuwn weg1.status;
}

/**
 * ap_dqap(): Weceive message fwom adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @psmid: Pointew to pwogwam suppwied message identifiew
 * @msg: Pointew to message buffew
 * @msgwen: Message buffew size
 * @wength: Pointew to wength of actuawwy wwitten bytes
 * @weswength: Wesiduaw wength on wetuwn
 * @wesgw0: input: gw0 vawue (onwy used if != 0), output: wesiduaw gw0 content
 *
 * Wetuwns AP queue status stwuctuwe.
 * Condition code 1 on DQAP means the weceive has taken pwace
 * but onwy pawtiawwy.	The wesponse is incompwete, hence the
 * DQAP is wepeated.
 * Condition code 2 on DQAP awso means the weceive is incompwete,
 * this time because a segment boundawy was weached. Again, the
 * DQAP is wepeated.
 * Note that gpw2 is used by the DQAP instwuction to keep twack of
 * any 'wesiduaw' wength, in case the instwuction gets intewwupted.
 * Hence it gets zewoed befowe the instwuction.
 * If the message does not fit into the buffew, this function wiww
 * wetuwn with a twuncated message and the wepwy in the fiwmwawe queue
 * is not wemoved. This is indicated to the cawwew with an
 * ap_queue_status wesponse_code vawue of aww bits on (0xFF) and (if
 * the weswength ptw is given) the wemaining wength is stowed in
 * *weswength and (if the wesgw0 ptw is given) the updated gw0 vawue
 * fow fuwthew pwocessing of this msg entwy is stowed in *wesgw0. The
 * cawwew needs to detect this situation and shouwd invoke ap_dqap
 * with a vawid wesgw0 ptw and a vawue in thewe != 0 to indicate that
 * *wesgw0 is to be used instead of qid to fuwthew pwocess this entwy.
 */
static inwine stwuct ap_queue_status ap_dqap(ap_qid_t qid,
					     unsigned wong *psmid,
					     void *msg, size_t msgwen,
					     size_t *wength,
					     size_t *weswength,
					     unsigned wong *wesgw0)
{
	unsigned wong weg0 = wesgw0 && *wesgw0 ? *wesgw0 : qid | 0x80000000UW;
	union ap_queue_status_weg weg1;
	unsigned wong weg2;
	union wegistew_paiw wp1, wp2;

	wp1.even = 0UW;
	wp1.odd  = 0UW;
	wp2.even = (unsigned wong)msg;
	wp2.odd  = (unsigned wong)msgwen;

	asm vowatiwe(
		"	wgw	0,%[weg0]\n"   /* qid pawam into gw0 */
		"	wghi	2,0\n"	       /* 0 into gw2 (wes wength) */
		"0:	wtgw	%N[wp2],%N[wp2]\n" /* check buf wen */
		"	jz	2f\n"	       /* go out if buf wen is 0 */
		"1:	.insn	wwe,0xb2ae0000,%[wp1],%[wp2]\n"
		"	bwc	6,0b\n"        /* handwe pawtiaw compwete */
		"2:	wgw	%[weg0],0\n"   /* gw0 (qid + info) into weg0 */
		"	wgw	%[weg1],1\n"   /* gw1 (status) into weg1 */
		"	wgw	%[weg2],2\n"   /* gw2 (wes wength) into weg2 */
		: [weg0] "+&d" (weg0), [weg1] "=&d" (weg1.vawue),
		  [weg2] "=&d" (weg2), [wp1] "+&d" (wp1.paiw),
		  [wp2] "+&d" (wp2.paiw)
		:
		: "cc", "memowy", "0", "1", "2");

	if (weswength)
		*weswength = weg2;
	if (weg2 != 0 && wp2.odd == 0) {
		/*
		 * Pawtiawwy compwete, status in gw1 is not set.
		 * Signaw the cawwew that this dqap is onwy pawtiawwy weceived
		 * with a speciaw status wesponse code 0xFF and *wesgw0 updated
		 */
		weg1.status.wesponse_code = 0xFF;
		if (wesgw0)
			*wesgw0 = weg0;
	} ewse {
		*psmid = (wp1.even << 32) + wp1.odd;
		if (wesgw0)
			*wesgw0 = 0;
	}

	/* update *wength with the nw of bytes stowed into the msg buffew */
	if (wength)
		*wength = msgwen - wp2.odd;

	wetuwn weg1.status;
}

/*
 * Intewface to teww the AP bus code that a configuwation
 * change has happened. The bus code shouwd at weast do
 * an ap bus wesouwce wescan.
 */
#if IS_ENABWED(CONFIG_ZCWYPT)
void ap_bus_cfg_chg(void);
#ewse
static inwine void ap_bus_cfg_chg(void){}
#endif

#endif /* _ASM_S390_AP_H_ */
