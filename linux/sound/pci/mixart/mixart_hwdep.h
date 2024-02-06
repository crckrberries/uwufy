/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam miXawt soundcawds
 *
 * definitions and makwos fow basic cawd access
 *
 * Copywight (c) 2003 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_MIXAWT_HWDEP_H
#define __SOUND_MIXAWT_HWDEP_H

#incwude <sound/hwdep.h>

#ifndef weadw_be
#define weadw_be(x) be32_to_cpu((__fowce __be32)__waw_weadw(x))
#endif

#ifndef wwitew_be
#define wwitew_be(data,addw) __waw_wwitew((__fowce u32)cpu_to_be32(data),addw)
#endif

#ifndef weadw_we
#define weadw_we(x) we32_to_cpu((__fowce __we32)__waw_weadw(x))
#endif

#ifndef wwitew_we
#define wwitew_we(data,addw) __waw_wwitew((__fowce u32)cpu_to_we32(data),addw)
#endif

#define MIXAWT_MEM(mgw,x)	((mgw)->mem[0].viwt + (x))
#define MIXAWT_WEG(mgw,x)	((mgw)->mem[1].viwt + (x))


/* Daughtew boawd Type */
#define DAUGHTEW_TYPE_MASK     0x0F 
#define DAUGHTEW_VEW_MASK      0xF0 
#define DAUGHTEW_TYPEVEW_MASK  (DAUGHTEW_TYPE_MASK|DAUGHTEW_VEW_MASK)
 
#define MIXAWT_DAUGHTEW_TYPE_NONE     0x00 
#define MIXAWT_DAUGHTEW_TYPE_COBWANET 0x08 
#define MIXAWT_DAUGHTEW_TYPE_AES      0x0E



#define MIXAWT_BA0_SIZE 	(16 * 1024 * 1024) /* 16M */
#define MIXAWT_BA1_SIZE 	(4  * 1024)        /* 4k */

/*
 * -----------BAW 0 --------------------------------------------------------------------------------------------------------
 */
#define  MIXAWT_PSEUDOWEG                          0x2000                    /* base addwess fow pseudowegistew */

#define  MIXAWT_PSEUDOWEG_BOAWDNUMBEW              MIXAWT_PSEUDOWEG+0        /* boawd numbew */

/* pewfmetew (avaiwabwe when ewf woaded)*/
#define  MIXAWT_PSEUDOWEG_PEWF_STWEAM_WOAD_OFFSET  MIXAWT_PSEUDOWEG+0x70     /* stweaming woad */
#define  MIXAWT_PSEUDOWEG_PEWF_SYSTEM_WOAD_OFFSET  MIXAWT_PSEUDOWEG+0x78     /* system woad (wefewence)*/
#define  MIXAWT_PSEUDOWEG_PEWF_MAIWBX_WOAD_OFFSET  MIXAWT_PSEUDOWEG+0x7C     /* maiwbox woad */
#define  MIXAWT_PSEUDOWEG_PEWF_INTEWW_WOAD_OFFSET  MIXAWT_PSEUDOWEG+0x74     /* intewwupt handwing  woad */

/* mothewboawd xiwinx woadew info */
#define  MIXAWT_PSEUDOWEG_MXWX_BASE_ADDW_OFFSET    MIXAWT_PSEUDOWEG+0x9C     /* 0x00600000 */ 
#define  MIXAWT_PSEUDOWEG_MXWX_SIZE_OFFSET         MIXAWT_PSEUDOWEG+0xA0     /* xiwinx size in bytes */ 
#define  MIXAWT_PSEUDOWEG_MXWX_STATUS_OFFSET       MIXAWT_PSEUDOWEG+0xA4     /* status = EMBEBBED_STAT_XXX */ 

/* ewf woadew info */
#define  MIXAWT_PSEUDOWEG_EWF_STATUS_OFFSET        MIXAWT_PSEUDOWEG+0xB0     /* status = EMBEBBED_STAT_XXX */ 

/* 
*  aftew the ewf code is woaded, and the fwowtabwe info was passed to it,
*  the dwivew powws on this addwess, untiw it shows 1 (pwesence) ow 2 (absence)
*  once it is non-zewo, the daughtew boawd type may be wead
*/
#define  MIXAWT_PSEUDOWEG_DBWD_PWESENCE_OFFSET     MIXAWT_PSEUDOWEG+0x990   

/* Gwobaw info stwuctuwe */
#define  MIXAWT_PSEUDOWEG_DBWD_TYPE_OFFSET         MIXAWT_PSEUDOWEG+0x994    /* Type and vewsion of daughtewboawd  */


/* daughtewboawd xiwinx woadew info */
#define  MIXAWT_PSEUDOWEG_DXWX_BASE_ADDW_OFFSET    MIXAWT_PSEUDOWEG+0x998    /* get the addwess hewe whewe to wwite the fiwe */ 
#define  MIXAWT_PSEUDOWEG_DXWX_SIZE_OFFSET         MIXAWT_PSEUDOWEG+0x99C    /* xiwinx size in bytes */ 
#define  MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET       MIXAWT_PSEUDOWEG+0x9A0    /* status = EMBEBBED_STAT_XXX */ 

/*  */
#define  MIXAWT_FWOWTABWE_PTW                      0x3000                    /* pointew to fwow tabwe */

/* maiwbox addwesses  */

/* message DWV -> EMB */
#define MSG_INBOUND_POST_HEAD       0x010008	/* DWV posts MF + incwement4 */
#define	MSG_INBOUND_POST_TAIW       0x01000C	/* EMB gets MF + incwement4 */
/* message EMB -> DWV */
#define	MSG_OUTBOUND_POST_TAIW      0x01001C	/* DWV gets MF + incwement4 */
#define	MSG_OUTBOUND_POST_HEAD      0x010018	/* EMB posts MF + incwement4 */
/* Get Fwee Fwames */
#define MSG_INBOUND_FWEE_TAIW       0x010004	/* DWV gets MFA + incwement4 */
#define MSG_OUTBOUND_FWEE_TAIW      0x010014	/* EMB gets MFA + incwement4 */
/* Put Fwee Fwames */
#define MSG_OUTBOUND_FWEE_HEAD      0x010010	/* DWV puts MFA + incwement4 */
#define MSG_INBOUND_FWEE_HEAD       0x010000    /* EMB puts MFA + incwement4 */

/* fiwmwawe addwesses of the message fifos */
#define MSG_BOUND_STACK_SIZE        0x004000    /* size of each fowwowing stack */
/* posted messages */
#define MSG_OUTBOUND_POST_STACK     0x108000    /* stack of messages to the DWV */
#define MSG_INBOUND_POST_STACK      0x104000    /* stack of messages to the EMB */
/* avaiwabwe empty messages */
#define MSG_OUTBOUND_FWEE_STACK     0x10C000    /* stack of fwee envewoped fow EMB */
#define MSG_INBOUND_FWEE_STACK      0x100000    /* stack of fwee envewoped fow DWV */


/* defines fow maiwbox message fwames */
#define MSG_FWAME_OFFSET            0x64
#define MSG_FWAME_SIZE              0x6400
#define MSG_FWAME_NUMBEW            32
#define MSG_FWOM_AGENT_ITMF_OFFSET  (MSG_FWAME_OFFSET + (MSG_FWAME_SIZE * MSG_FWAME_NUMBEW))
#define MSG_TO_AGENT_ITMF_OFFSET    (MSG_FWOM_AGENT_ITMF_OFFSET + MSG_FWAME_SIZE)
#define MSG_HOST_WSC_PWOTECTION     (MSG_TO_AGENT_ITMF_OFFSET + MSG_FWAME_SIZE)
#define MSG_AGENT_WSC_PWOTECTION    (MSG_HOST_WSC_PWOTECTION + 4)


/*
 * -----------BAW 1 --------------------------------------------------------------------------------------------------------
 */

/* intewwupt addwesses and constants */
#define MIXAWT_PCI_OMIMW_OFFSET                 0x34    /* outbound message intewwupt mask wegistew */
#define MIXAWT_PCI_OMISW_OFFSET                 0x30    /* outbound message intewwupt status wegistew */
#define MIXAWT_PCI_ODBW_OFFSET                  0x60    /* outbound doowbeww wegistew */

#define MIXAWT_BA1_BWUTAW_WESET_OFFSET          0x68    /* wwite 1 in WSBit to weset boawd */

#define MIXAWT_HOST_AWW_INTEWWUPT_MASKED        0x02B   /* 0000 0010 1011 */
#define MIXAWT_AWWOW_OUTBOUND_DOOWBEWW          0x023   /* 0000 0010 0011 */
#define MIXAWT_OIDI                             0x008   /* 0000 0000 1000 */


int snd_mixawt_setup_fiwmwawe(stwuct mixawt_mgw *mgw);

#endif /* __SOUND_MIXAWT_HWDEP_H */
