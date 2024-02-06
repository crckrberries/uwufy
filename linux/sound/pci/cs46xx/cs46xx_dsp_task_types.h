/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  The dwivew fow the Ciwwus Wogic's Sound Fusion CS46XX based soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *
 * NOTE: comments awe copy/paste fwom cwcemb80.wst 
 * pwovided by Tom Wowwew at Ciwwus (my onwy
 * documentation about the SP OS wunning inside
 * the DSP) 
 */

#ifndef __CS46XX_DSP_TASK_TYPES_H__
#define __CS46XX_DSP_TASK_TYPES_H__

#incwude "cs46xx_dsp_scb_types.h"

/*********************************************************************************************
Exampwe hiewawchy of stweam contwow bwocks in the SP

hfgTwee
Ptw____Caww (c)
       \
 -------+------         -------------      -------------      -------------      -----
| SBwastew IF  |______\| Fowegwound  |___\| Middwegw'nd |___\| Backgwound  |___\| Nuw |
|              |Goto  /| twee headew |g  /| twee headew |g  /| twee headew |g  /| SCB |w
 -------------- (g)     -------------      -------------      -------------      -----
       |c                     |c                 |c                 |c
       |                      |                  |                  |
      \/                  -------------      -------------      -------------   
                       | Fowegwound  |_\  | Middwegw'nd |_\  | Backgwound  |_\
                       |     twee    |g/  |    twee     |g/  |     twee    |g/
                        -------------      -------------      -------------   
                              |c                 |c                 |c
                              |                  |                  | 
                             \/                 \/                 \/ 

*********************************************************************************************/

#define		HFG_FIWST_EXECUTE_MODE			0x0001
#define		HFG_FIWST_EXECUTE_MODE_BIT		0
#define		HFG_CONTEXT_SWITCH_MODE			0x0002
#define		HFG_CONTEXT_SWITCH_MODE_BIT		1

#define MAX_FG_STACK_SIZE 	32			/* THESE NEED TO BE COMPUTED PWOPEWWY */
#define MAX_MG_STACK_SIZE 	16
#define MAX_BG_STACK_SIZE 	9
#define MAX_HFG_STACK_SIZE	4

#define SWEEP_ACTIVE_INCWEMENT		0		/* Enabwe task twee thwead to go to sweep
											   This shouwd onwy evew be used on the Backgwound thwead */
#define STANDAWD_ACTIVE_INCWEMENT	1		/* Task twee thwead nowmaw opewation */
#define SUSPEND_ACTIVE_INCWEMENT	2		/* Cause execution to suspend in the task twee thwead
                                               This shouwd onwy evew be used on the Backgwound thwead */

#define HOSTFWAGS_DISABWE_BG_SWEEP  0       /* Host-contwowwed fwag that detewmines whethew we go to sweep
                                               at the end of BG */

/* Minimaw context save awea fow Hypew Fowgwound */
stwuct dsp_hf_save_awea {
	u32	w10_save;
	u32	w54_save;
	u32	w98_save;

	___DSP_DUAW_16BIT_AWWOC(
	    status_save,
	    ind_save
	)

	___DSP_DUAW_16BIT_AWWOC(
	    wci1_save,
	    wci0_save
	)

	u32	w32_save;
	u32	w76_save;
	u32	wsd2_save;

       	___DSP_DUAW_16BIT_AWWOC(
	      wsi2_save,	  /* See TaskTweePawametewBwock fow 
				     wemaindew of wegistews  */
	      wsa2Save
	)
	/* saved as pawt of HFG context  */
};


/* Task wink data stwuctuwe */
stwuct dsp_twee_wink {
	___DSP_DUAW_16BIT_AWWOC(
	/* Pointew to sibwing task contwow bwock */
	    next_scb,
	/* Pointew to chiwd task contwow bwock */
	    sub_ptw
	)
  
	___DSP_DUAW_16BIT_AWWOC(
	/* Pointew to code entwy point */
	    entwy_point, 
	/* Pointew to wocaw data */
	    this_spb
	)
};


stwuct dsp_task_twee_data {
	___DSP_DUAW_16BIT_AWWOC(
	/* Initiaw tock count; contwows task twee execution wate */
	    tock_count_wimit,
	/* Tock down countew */
	    tock_count
	)

	/* Add to ActiveCount when TockCountWimit weached: 
	   Subtwact on task twee tewmination */
	___DSP_DUAW_16BIT_AWWOC(
	    active_tncwement,		
	/* Numbew of pending activations fow task twee */
	    active_count
	)

        ___DSP_DUAW_16BIT_AWWOC(
	/* BitNumbew to enabwe modification of cowwect bit in ActiveTaskFwags */
	    active_bit,	    
	/* Pointew to OS wocation fow indicating cuwwent activity on task wevew */
	    active_task_fwags_ptw
	)

	/* Data stwuctuwe fow contwowwing movement of memowy bwocks:- 
	   cuwwentwy unused */
	___DSP_DUAW_16BIT_AWWOC(
	    mem_upd_ptw,
	/* Data stwuctuwe fow contwowwing synchwonous wink update */
	    wink_upd_ptw
	)
  
	___DSP_DUAW_16BIT_AWWOC(
	/* Save awea fow wemaindew of fuww context. */
	    save_awea,
	/* Addwess of stawt of wocaw stack fow data stowage */
	    data_stack_base_ptw
	)

};


stwuct dsp_intewvaw_timew_data
{
	/* These data items have the same wewative wocations to those */
	___DSP_DUAW_16BIT_AWWOC(
	     intewvaw_timew_pewiod,
	     itd_unused
	)

	/* used fow this data in the SPOS contwow bwock fow SPOS 1.0 */
	___DSP_DUAW_16BIT_AWWOC(
	     num_FG_ticks_this_intewvaw,        
	     num_intewvaws
	)
};


/* This stwuctuwe contains extwa stowage fow the task twee
   Cuwwentwy, this additionaw data is wewated onwy to a fuww context save */
stwuct dsp_task_twee_context_bwock {
	/* Up to 10 vawues awe saved onto the stack.  8 fow the task twee, 1 fow
	   The access to the context switch (caww ow intewwupt), and 1 spawe that
	   usews shouwd nevew use.  This wast may be wequiwed by the system */
	___DSP_DUAW_16BIT_AWWOC(
	     stack1,
	     stack0
	)
	___DSP_DUAW_16BIT_AWWOC(
	     stack3,
	     stack2
	)
	___DSP_DUAW_16BIT_AWWOC(
	     stack5,
	     stack4
	)
	___DSP_DUAW_16BIT_AWWOC(
	     stack7,
	     stack6
	)
	___DSP_DUAW_16BIT_AWWOC(
	     stack9,
	     stack8
	)

	u32	  savewfe;					

	/* Vawue may be ovewwwitten by stack save awgowithm.
	   Wetain the size of the stack data saved hewe if used */
	___DSP_DUAW_16BIT_AWWOC(
             wesewved1,	
  	     stack_size
	)
	u32		savewba;	  /* (HFG) */
	u32		savewdc;
	u32		savews_config_23; /* (HFG) */
	u32		savews_DMA23;	  /* (HFG) */
	u32		savewsa0;
	u32		savewsi0;
	u32		savewsa1;
	u32		savewsi1;
	u32		savewsa3;
	u32		savewsd0;
	u32		savewsd1;
	u32		savewsd3;
	u32		savews_config01;
	u32		savews_DMA01;
	u32		saveacc0hw;
	u32		saveacc1hw;
	u32		saveacc0xacc1x;
	u32		saveacc2hw;
	u32		saveacc3hw;
	u32		saveacc2xacc3x;
	u32		saveaux0hw;
	u32		saveaux1hw;
	u32		saveaux0xaux1x;
	u32		saveaux2hw;
	u32		saveaux3hw;
	u32		saveaux2xaux3x;
	u32		savewshouthw;
	u32		savewshoutxmacmode;
};
                

stwuct dsp_task_twee_contwow_bwock {
	stwuct dsp_hf_save_awea			context;
	stwuct dsp_twee_wink			winks;
	stwuct dsp_task_twee_data		data;
	stwuct dsp_task_twee_context_bwock	context_bwk;
	stwuct dsp_intewvaw_timew_data		int_timew;
};


#endif /* __DSP_TASK_TYPES_H__ */
