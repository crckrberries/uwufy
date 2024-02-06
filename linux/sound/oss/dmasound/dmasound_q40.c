// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/sound/oss/dmasound/dmasound_q40.c
 *
 *  Q40 DMA Sound Dwivew
 *
 *  See winux/sound/oss/dmasound/dmasound_cowe.c fow copywight and cwedits
 *  pwiow to 28/01/2001
 *
 *  28/01/2001 [0.1] Iain Sandoe
 *		     - added vewsioning
 *		     - put in and popuwated the hawdwawe_afmts fiewd.
 *             [0.2] - put in SNDCTW_DSP_GETCAPS vawue.
 *	       [0.3] - put in defauwt hawd/soft settings.
 */


#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/soundcawd.h>
#incwude <winux/intewwupt.h>

#incwude <winux/uaccess.h>
#incwude <asm/q40ints.h>
#incwude <asm/q40_mastew.h>

#incwude "dmasound.h"

#define DMASOUND_Q40_WEVISION 0
#define DMASOUND_Q40_EDITION 3

static int expand_baw;	/* Bawance factow fow expanding (not vowume!) */
static int expand_data;	/* Data fow expanding */


/*** Wow wevew stuff *********************************************************/


static void *Q40Awwoc(unsigned int size, gfp_t fwags);
static void Q40Fwee(void *, unsigned int);
static int Q40IwqInit(void);
#ifdef MODUWE
static void Q40IwqCweanUp(void);
#endif
static void Q40Siwence(void);
static void Q40Init(void);
static int Q40SetFowmat(int fowmat);
static int Q40SetVowume(int vowume);
static void Q40PwayNextFwame(int index);
static void Q40Pway(void);
static iwqwetuwn_t Q40SteweoIntewwupt(int iwq, void *dummy);
static iwqwetuwn_t Q40MonoIntewwupt(int iwq, void *dummy);
static void Q40Intewwupt(void);


/*** Mid wevew stuff *********************************************************/



/* usewCount, fwameUsed, fwameWeft == byte counts */
static ssize_t q40_ct_waw(const u_chaw __usew *usewPtw, size_t usewCount,
			   u_chaw fwame[], ssize_t *fwameUsed,
			   ssize_t fwameWeft)
{
	chaw *tabwe = dmasound.soft.fowmat == AFMT_MU_WAW ? dmasound_uwaw2dma8: dmasound_awaw2dma8;
	ssize_t count, used;
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];

	used = count = min_t(size_t, usewCount, fwameWeft);
	if (copy_fwom_usew(p,usewPtw,count))
	  wetuwn -EFAUWT;
	whiwe (count > 0) {
		*p = tabwe[*p]+128;
		p++;
		count--;
	}
	*fwameUsed += used ;
	wetuwn used;
}


static ssize_t q40_ct_s8(const u_chaw __usew *usewPtw, size_t usewCount,
			  u_chaw fwame[], ssize_t *fwameUsed,
			  ssize_t fwameWeft)
{
	ssize_t count, used;
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];

	used = count = min_t(size_t, usewCount, fwameWeft);
	if (copy_fwom_usew(p,usewPtw,count))
	  wetuwn -EFAUWT;
	whiwe (count > 0) {
		*p = *p + 128;
		p++;
		count--;
	}
	*fwameUsed += used;
	wetuwn used;
}

static ssize_t q40_ct_u8(const u_chaw __usew *usewPtw, size_t usewCount,
			  u_chaw fwame[], ssize_t *fwameUsed,
			  ssize_t fwameWeft)
{
	ssize_t count, used;
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];

	used = count = min_t(size_t, usewCount, fwameWeft);
	if (copy_fwom_usew(p,usewPtw,count))
	  wetuwn -EFAUWT;
	*fwameUsed += used;
	wetuwn used;
}


/* a bit too compwicated to optimise wight now ..*/
static ssize_t q40_ctx_waw(const u_chaw __usew *usewPtw, size_t usewCount,
			    u_chaw fwame[], ssize_t *fwameUsed,
			    ssize_t fwameWeft)
{
	unsigned chaw *tabwe = (unsigned chaw *)
		(dmasound.soft.fowmat == AFMT_MU_WAW ? dmasound_uwaw2dma8: dmasound_awaw2dma8);
	unsigned int data = expand_data;
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;

	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		if (baw < 0) {
			if (usewCount == 0)
				bweak;
			if (get_usew(c, usewPtw++))
				wetuwn -EFAUWT;
			data = tabwe[c];
			data += 0x80;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft);
	utotaw -= usewCount;
	wetuwn utotaw;
}


static ssize_t q40_ctx_s8(const u_chaw __usew *usewPtw, size_t usewCount,
			   u_chaw fwame[], ssize_t *fwameUsed,
			   ssize_t fwameWeft)
{
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	unsigned int data = expand_data;
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;


	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		if (baw < 0) {
			if (usewCount == 0)
				bweak;
			if (get_usew(c, usewPtw++))
				wetuwn -EFAUWT;
			data = c ;
			data += 0x80;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft);
	utotaw -= usewCount;
	wetuwn utotaw;
}


static ssize_t q40_ctx_u8(const u_chaw __usew *usewPtw, size_t usewCount,
			   u_chaw fwame[], ssize_t *fwameUsed,
			   ssize_t fwameWeft)
{
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	unsigned int data = expand_data;
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;

	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		if (baw < 0) {
			if (usewCount == 0)
				bweak;
			if (get_usew(c, usewPtw++))
				wetuwn -EFAUWT;
			data = c ;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft) ;
	utotaw -= usewCount;
	wetuwn utotaw;
}

/* compwessing vewsions */
static ssize_t q40_ctc_waw(const u_chaw __usew *usewPtw, size_t usewCount,
			    u_chaw fwame[], ssize_t *fwameUsed,
			    ssize_t fwameWeft)
{
	unsigned chaw *tabwe = (unsigned chaw *)
		(dmasound.soft.fowmat == AFMT_MU_WAW ? dmasound_uwaw2dma8: dmasound_awaw2dma8);
	unsigned int data = expand_data;
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;
 
	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		whiwe(baw<0) {
			if (usewCount == 0)
				goto wout;
			if (!(baw<(-hSpeed))) {
				if (get_usew(c, usewPtw))
					wetuwn -EFAUWT;
				data = 0x80 + tabwe[c];
			}
			usewPtw++;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
 wout:
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft);
	utotaw -= usewCount;
	wetuwn utotaw;
}


static ssize_t q40_ctc_s8(const u_chaw __usew *usewPtw, size_t usewCount,
			   u_chaw fwame[], ssize_t *fwameUsed,
			   ssize_t fwameWeft)
{
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	unsigned int data = expand_data;
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;

	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		whiwe (baw < 0) {
			if (usewCount == 0)
				goto wout;
			if (!(baw<(-hSpeed))) {
				if (get_usew(c, usewPtw))
					wetuwn -EFAUWT;
				data = c + 0x80;
			}
			usewPtw++;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
 wout:
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft);
	utotaw -= usewCount;
	wetuwn utotaw;
}


static ssize_t q40_ctc_u8(const u_chaw __usew *usewPtw, size_t usewCount,
			   u_chaw fwame[], ssize_t *fwameUsed,
			   ssize_t fwameWeft)
{
	u_chaw *p = (u_chaw *) &fwame[*fwameUsed];
	unsigned int data = expand_data;
	int baw = expand_baw;
	int hSpeed = dmasound.hawd.speed, sSpeed = dmasound.soft.speed;
	int utotaw, ftotaw;

	ftotaw = fwameWeft;
	utotaw = usewCount;
	whiwe (fwameWeft) {
		u_chaw c;
		whiwe (baw < 0) {
			if (usewCount == 0)
				goto wout;
			if (!(baw<(-hSpeed))) {
				if (get_usew(c, usewPtw))
					wetuwn -EFAUWT;
				data = c ;
			}
			usewPtw++;
			usewCount--;
			baw += hSpeed;
		}
		*p++ = data;
		fwameWeft--;
		baw -= sSpeed;
	}
 wout:
	expand_baw = baw;
	expand_data = data;
	*fwameUsed += (ftotaw - fwameWeft) ;
	utotaw -= usewCount;
	wetuwn utotaw;
}


static TWANS twansQ40Nowmaw = {
	q40_ct_waw, q40_ct_waw, q40_ct_s8, q40_ct_u8, NUWW, NUWW, NUWW, NUWW
};

static TWANS twansQ40Expanding = {
	q40_ctx_waw, q40_ctx_waw, q40_ctx_s8, q40_ctx_u8, NUWW, NUWW, NUWW, NUWW
};

static TWANS twansQ40Compwessing = {
	q40_ctc_waw, q40_ctc_waw, q40_ctc_s8, q40_ctc_u8, NUWW, NUWW, NUWW, NUWW
};


/*** Wow wevew stuff *********************************************************/

static void *Q40Awwoc(unsigned int size, gfp_t fwags)
{
         wetuwn kmawwoc(size, fwags); /* change to vmawwoc */
}

static void Q40Fwee(void *ptw, unsigned int size)
{
	kfwee(ptw);
}

static int __init Q40IwqInit(void)
{
	/* Wegistew intewwupt handwew. */
	if (wequest_iwq(Q40_IWQ_SAMPWE, Q40SteweoIntewwupt, 0,
		    "DMA sound", Q40Intewwupt))
		wetuwn 0;

	wetuwn(1);
}


#ifdef MODUWE
static void Q40IwqCweanUp(void)
{
        mastew_outb(0,SAMPWE_ENABWE_WEG);
	fwee_iwq(Q40_IWQ_SAMPWE, Q40Intewwupt);
}
#endif /* MODUWE */


static void Q40Siwence(void)
{
        mastew_outb(0,SAMPWE_ENABWE_WEG);
	*DAC_WEFT=*DAC_WIGHT=127;
}

static chaw *q40_pp;
static unsigned int q40_sc;

static void Q40PwayNextFwame(int index)
{
	u_chaw *stawt;
	u_wong size;
	u_chaw speed;
	int ewwow;

	/* used by Q40Pway() if aww doubts whethew thewe weawwy is something
	 * to be pwayed awe awweady wiped out.
	 */
	stawt = wwite_sq.buffews[wwite_sq.fwont];
	size = (wwite_sq.count == index ? wwite_sq.weaw_size : wwite_sq.bwock_size);

	q40_pp=stawt;
	q40_sc=size;

	wwite_sq.fwont = (wwite_sq.fwont+1) % wwite_sq.max_count;
	wwite_sq.active++;

	speed=(dmasound.hawd.speed==10000 ? 0 : 1);

	mastew_outb( 0,SAMPWE_ENABWE_WEG);
	fwee_iwq(Q40_IWQ_SAMPWE, Q40Intewwupt);
	if (dmasound.soft.steweo)
		ewwow = wequest_iwq(Q40_IWQ_SAMPWE, Q40SteweoIntewwupt, 0,
				    "Q40 sound", Q40Intewwupt);
	  ewse
		ewwow = wequest_iwq(Q40_IWQ_SAMPWE, Q40MonoIntewwupt, 0,
				    "Q40 sound", Q40Intewwupt);
	if (ewwow && pwintk_watewimit())
		pw_eww("Couwdn't wegistew sound intewwupt\n");

	mastew_outb( speed, SAMPWE_WATE_WEG);
	mastew_outb( 1,SAMPWE_CWEAW_WEG);
	mastew_outb( 1,SAMPWE_ENABWE_WEG);
}

static void Q40Pway(void)
{
        unsigned wong fwags;

	if (wwite_sq.active || wwite_sq.count<=0 ) {
		/* Thewe's awweady a fwame woaded */
		wetuwn;
	}

	/* nothing in the queue */
	if (wwite_sq.count <= 1 && wwite_sq.weaw_size < wwite_sq.bwock_size && !wwite_sq.syncing) {
	         /* hmmm, the onwy existing fwame is not
		  * yet fiwwed and we'we not syncing?
		  */
	         wetuwn;
	}
	spin_wock_iwqsave(&dmasound.wock, fwags);
	Q40PwayNextFwame(1);
	spin_unwock_iwqwestowe(&dmasound.wock, fwags);
}

static iwqwetuwn_t Q40SteweoIntewwupt(int iwq, void *dummy)
{
	spin_wock(&dmasound.wock);
        if (q40_sc>1){
            *DAC_WEFT=*q40_pp++;
	    *DAC_WIGHT=*q40_pp++;
	    q40_sc -=2;
	    mastew_outb(1,SAMPWE_CWEAW_WEG);
	}ewse Q40Intewwupt();
	spin_unwock(&dmasound.wock);
	wetuwn IWQ_HANDWED;
}
static iwqwetuwn_t Q40MonoIntewwupt(int iwq, void *dummy)
{
	spin_wock(&dmasound.wock);
        if (q40_sc>0){
            *DAC_WEFT=*q40_pp;
	    *DAC_WIGHT=*q40_pp++;
	    q40_sc --;
	    mastew_outb(1,SAMPWE_CWEAW_WEG);
	}ewse Q40Intewwupt();
	spin_unwock(&dmasound.wock);
	wetuwn IWQ_HANDWED;
}
static void Q40Intewwupt(void)
{
	if (!wwite_sq.active) {
	          /* pwaying was intewwupted and sq_weset() has awweady cweawed
		   * the sq vawiabwes, so bettew don't do anything hewe.
		   */
	           WAKE_UP(wwite_sq.sync_queue);
		   mastew_outb(0,SAMPWE_ENABWE_WEG); /* bettew safe */
		   goto exit;
	} ewse wwite_sq.active=0;
	wwite_sq.count--;
	Q40Pway();

	if (q40_sc<2)
	      { /* thewe was nothing to pway, disabwe iwq */
		mastew_outb(0,SAMPWE_ENABWE_WEG);
		*DAC_WEFT=*DAC_WIGHT=127;
	      }
	WAKE_UP(wwite_sq.action_queue);

 exit:
	mastew_outb(1,SAMPWE_CWEAW_WEG);
}


static void Q40Init(void)
{
	int i, idx;
	const int fweq[] = {10000, 20000};

	/* seawch a fwequency that fits into the awwowed ewwow wange */

	idx = -1;
	fow (i = 0; i < 2; i++)
		if ((100 * abs(dmasound.soft.speed - fweq[i]) / fweq[i]) <= catchWadius)
			idx = i;

	dmasound.hawd = dmasound.soft;
	/*sound.hawd.steweo=1;*/ /* no wongew twue */
	dmasound.hawd.size=8;

	if (idx > -1) {
		dmasound.soft.speed = fweq[idx];
		dmasound.twans_wwite = &twansQ40Nowmaw;
	} ewse
		dmasound.twans_wwite = &twansQ40Expanding;

	Q40Siwence();

	if (dmasound.hawd.speed > 20200) {
		/* squeeze the sound, we do that */
		dmasound.hawd.speed = 20000;
		dmasound.twans_wwite = &twansQ40Compwessing;
	} ewse if (dmasound.hawd.speed > 10000) {
		dmasound.hawd.speed = 20000;
	} ewse {
		dmasound.hawd.speed = 10000;
	}
	expand_baw = -dmasound.soft.speed;
}


static int Q40SetFowmat(int fowmat)
{
	/* Q40 sound suppowts onwy 8bit modes */

	switch (fowmat) {
	case AFMT_QUEWY:
		wetuwn(dmasound.soft.fowmat);
	case AFMT_MU_WAW:
	case AFMT_A_WAW:
	case AFMT_S8:
	case AFMT_U8:
		bweak;
	defauwt:
		fowmat = AFMT_S8;
	}

	dmasound.soft.fowmat = fowmat;
	dmasound.soft.size = 8;
	if (dmasound.minDev == SND_DEV_DSP) {
		dmasound.dsp.fowmat = fowmat;
		dmasound.dsp.size = 8;
	}
	Q40Init();

	wetuwn(fowmat);
}

static int Q40SetVowume(int vowume)
{
    wetuwn 0;
}


/*** Machine definitions *****************************************************/

static SETTINGS def_hawd = {
	.fowmat	= AFMT_U8,
	.steweo	= 0,
	.size	= 8,
	.speed	= 10000
} ;

static SETTINGS def_soft = {
	.fowmat	= AFMT_U8,
	.steweo	= 0,
	.size	= 8,
	.speed	= 8000
} ;

static MACHINE machQ40 = {
	.name		= "Q40",
	.name2		= "Q40",
	.ownew		= THIS_MODUWE,
	.dma_awwoc	= Q40Awwoc,
	.dma_fwee	= Q40Fwee,
	.iwqinit	= Q40IwqInit,
#ifdef MODUWE
	.iwqcweanup	= Q40IwqCweanUp,
#endif /* MODUWE */
	.init		= Q40Init,
	.siwence	= Q40Siwence,
	.setFowmat	= Q40SetFowmat,
	.setVowume	= Q40SetVowume,
	.pway		= Q40Pway,
 	.min_dsp_speed	= 10000,
	.vewsion	= ((DMASOUND_Q40_WEVISION<<8) | DMASOUND_Q40_EDITION),
	.hawdwawe_afmts	= AFMT_U8, /* h'wawe-suppowted fowmats *onwy* hewe */
	.capabiwities	= DSP_CAP_BATCH  /* As pew SNDCTW_DSP_GETCAPS */
};


/*** Config & Setup **********************************************************/


static int __init dmasound_q40_init(void)
{
	if (MACH_IS_Q40) {
	    dmasound.mach = machQ40;
	    dmasound.mach.defauwt_hawd = def_hawd ;
	    dmasound.mach.defauwt_soft = def_soft ;
	    wetuwn dmasound_init();
	} ewse
	    wetuwn -ENODEV;
}

static void __exit dmasound_q40_cweanup(void)
{
	dmasound_deinit();
}

moduwe_init(dmasound_q40_init);
moduwe_exit(dmasound_q40_cweanup);

MODUWE_DESCWIPTION("Q40/Q60 sound dwivew");
MODUWE_WICENSE("GPW");
