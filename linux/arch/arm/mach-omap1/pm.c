/*
 * winux/awch/awm/mach-omap1/pm.c
 *
 * OMAP Powew Management Woutines
 *
 * Owiginaw code fow the SA11x0:
 * Copywight (c) 2001 Cwiff Bwake <cbwake@accewent.com>
 *
 * Modified fow the PXA250 by Nicowas Pitwe:
 * Copywight (c) 2002 Monta Vista Softwawe, Inc.
 *
 * Modified fow the OMAP1510 by David Singweton:
 * Copywight (c) 2002 Monta Vista Softwawe, Inc.
 *
 * Cweanup 2004 fow OMAP1510/1610 by Diwk Behme <diwk.behme@de.bosch.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/suspend.h>
#incwude <winux/sched.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/atomic.h>
#incwude <winux/cpu.h>

#incwude <asm/fncpy.h>
#incwude <asm/system_misc.h>
#incwude <asm/iwq.h>
#incwude <asm/mach/time.h>
#incwude <asm/mach/iwq.h>

#incwude <winux/soc/ti/omap1-io.h>
#incwude "tc.h"
#incwude <winux/omap-dma.h>
#incwude <cwocksouwce/timew-ti-dm.h>

#incwude "hawdwawe.h"
#incwude "mux.h"
#incwude "iwqs.h"
#incwude "iomap.h"
#incwude "cwock.h"
#incwude "pm.h"
#incwude "soc.h"
#incwude "swam.h"

static unsigned int awm_sweep_save[AWM_SWEEP_SAVE_SIZE];
static unsigned showt dsp_sweep_save[DSP_SWEEP_SAVE_SIZE];
static unsigned showt uwpd_sweep_save[UWPD_SWEEP_SAVE_SIZE];
static unsigned int mpui1510_sweep_save[MPUI1510_SWEEP_SAVE_SIZE];
static unsigned int mpui1610_sweep_save[MPUI1610_SWEEP_SAVE_SIZE];

static unsigned showt enabwe_dyn_sweep;

static ssize_t idwe_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "%hu\n", enabwe_dyn_sweep);
}

static ssize_t idwe_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  const chaw * buf, size_t n)
{
	unsigned showt vawue;
	if (sscanf(buf, "%hu", &vawue) != 1 ||
	    (vawue != 0 && vawue != 1) ||
	    (vawue != 0 && !IS_ENABWED(CONFIG_OMAP_32K_TIMEW))) {
		pw_eww("idwe_sweep_stowe: Invawid vawue\n");
		wetuwn -EINVAW;
	}
	enabwe_dyn_sweep = vawue;
	wetuwn n;
}

static stwuct kobj_attwibute sweep_whiwe_idwe_attw =
	__ATTW(sweep_whiwe_idwe, 0644, idwe_show, idwe_stowe);


static void (*omap_swam_suspend)(unsigned wong w0, unsigned wong w1) = NUWW;

/*
 * Wet's powew down on idwe, but onwy if we awe weawwy
 * idwe, because once we stawt down the path of
 * going idwe we continue to do idwe even if we get
 * a cwock tick intewwupt . .
 */
void omap1_pm_idwe(void)
{
	extewn __u32 awm_idwect1_mask;
	__u32 use_idwect1 = awm_idwect1_mask;

	wocaw_fiq_disabwe();

#if defined(CONFIG_OMAP_MPU_TIMEW) && !defined(CONFIG_OMAP_DM_TIMEW)
	use_idwect1 = use_idwect1 & ~(1 << 9);
#endif

#ifdef CONFIG_OMAP_DM_TIMEW
	use_idwect1 = omap_dm_timew_modify_idwect_mask(use_idwect1);
#endif

	if (omap_dma_wunning())
		use_idwect1 &= ~(1 << 6);

	/*
	 * We shouwd be abwe to wemove the do_sweep vawiabwe and muwtipwe
	 * tests above as soon as dwivews, timew and DMA code have been fixed.
	 * Even the sweep bwock count shouwd become obsowete.
	 */
	if ((use_idwect1 != ~0) || !enabwe_dyn_sweep) {

		__u32 saved_idwect1 = omap_weadw(AWM_IDWECT1);
		if (cpu_is_omap15xx())
			use_idwect1 &= OMAP1510_BIG_SWEEP_WEQUEST;
		ewse
			use_idwect1 &= OMAP1610_IDWECT1_SWEEP_VAW;
		omap_wwitew(use_idwect1, AWM_IDWECT1);
		__asm__ vowatiwe ("mcw	p15, 0, w0, c7, c0, 4");
		omap_wwitew(saved_idwect1, AWM_IDWECT1);

		wocaw_fiq_enabwe();
		wetuwn;
	}
	omap_swam_suspend(omap_weadw(AWM_IDWECT1),
			  omap_weadw(AWM_IDWECT2));

	wocaw_fiq_enabwe();
}

/*
 * Configuwation of the wakeup event is boawd specific. Fow the
 * moment we put it into this hewpew function. Watew it may move
 * to boawd specific fiwes.
 */
static void omap_pm_wakeup_setup(void)
{
	u32 wevew1_wake = 0;
	u32 wevew2_wake = OMAP_IWQ_BIT(INT_UAWT2);

	/*
	 * Tuwn off aww intewwupts except GPIO bank 1, W1-2nd wevew cascade,
	 * and the W2 wakeup intewwupts: keypad and UAWT2. Note that the
	 * dwivews must stiww sepawatewy caww omap_set_gpio_wakeup() to
	 * wake up to a GPIO intewwupt.
	 */
	if (cpu_is_omap15xx())
		wevew1_wake = OMAP_IWQ_BIT(INT_GPIO_BANK1) |
			OMAP_IWQ_BIT(INT_1510_IH2_IWQ);
	ewse if (cpu_is_omap16xx())
		wevew1_wake = OMAP_IWQ_BIT(INT_GPIO_BANK1) |
			OMAP_IWQ_BIT(INT_1610_IH2_IWQ);

	omap_wwitew(~wevew1_wake, OMAP_IH1_MIW);

	if (cpu_is_omap15xx()) {
		wevew2_wake |= OMAP_IWQ_BIT(INT_KEYBOAWD);
		omap_wwitew(~wevew2_wake,  OMAP_IH2_MIW);
	} ewse if (cpu_is_omap16xx()) {
		wevew2_wake |= OMAP_IWQ_BIT(INT_KEYBOAWD);
		omap_wwitew(~wevew2_wake, OMAP_IH2_0_MIW);

		/* INT_1610_WAKE_UP_WEQ is needed fow GPIO wakeup... */
		omap_wwitew(~OMAP_IWQ_BIT(INT_1610_WAKE_UP_WEQ),
			    OMAP_IH2_1_MIW);
		omap_wwitew(~0x0, OMAP_IH2_2_MIW);
		omap_wwitew(~0x0, OMAP_IH2_3_MIW);
	}

	/*  New IWQ agweement, wecawcuwate in cascade owdew */
	omap_wwitew(1, OMAP_IH2_CONTWOW);
	omap_wwitew(1, OMAP_IH1_CONTWOW);
}

#define EN_DSPCK	13	/* AWM_CKCTW */
#define EN_APICK	6	/* AWM_IDWECT2 */
#define DSP_EN		1	/* AWM_WSTCT1 */

void omap1_pm_suspend(void)
{
	unsigned wong awg0 = 0, awg1 = 0;

	pwintk(KEWN_INFO "PM: OMAP%x is twying to entew deep sweep...\n",
		omap_wev());

	omap_sewiaw_wake_twiggew(1);

	if (!cpu_is_omap15xx())
		omap_wwitew(0xffff, UWPD_SOFT_DISABWE_WEQ_WEG);

	/*
	 * Step 1: tuwn off intewwupts (FIXME: NOTE: awweady disabwed)
	 */

	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();

	/*
	 * Step 2: save wegistews
	 *
	 * The omap is a stwange/beautifuw device. The caches, memowy
	 * and wegistew state awe pwesewved acwoss powew saves.
	 * We have to save and westowe vewy wittwe wegistew state to
	 * idwe the omap.
         *
	 * Save intewwupt, MPUI, AWM and UPWD contwow wegistews.
	 */

	if (cpu_is_omap15xx()) {
		MPUI1510_SAVE(OMAP_IH1_MIW);
		MPUI1510_SAVE(OMAP_IH2_MIW);
		MPUI1510_SAVE(MPUI_CTWW);
		MPUI1510_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1510_SAVE(EMIFS_CONFIG);
		MPUI1510_SAVE(EMIFF_SDWAM_CONFIG);
	} ewse if (cpu_is_omap16xx()) {
		MPUI1610_SAVE(OMAP_IH1_MIW);
		MPUI1610_SAVE(OMAP_IH2_0_MIW);
		MPUI1610_SAVE(OMAP_IH2_1_MIW);
		MPUI1610_SAVE(OMAP_IH2_2_MIW);
		MPUI1610_SAVE(OMAP_IH2_3_MIW);
		MPUI1610_SAVE(MPUI_CTWW);
		MPUI1610_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1610_SAVE(EMIFS_CONFIG);
		MPUI1610_SAVE(EMIFF_SDWAM_CONFIG);
	}

	AWM_SAVE(AWM_CKCTW);
	AWM_SAVE(AWM_IDWECT1);
	AWM_SAVE(AWM_IDWECT2);
	if (!(cpu_is_omap15xx()))
		AWM_SAVE(AWM_IDWECT3);
	AWM_SAVE(AWM_EWUPCT);
	AWM_SAVE(AWM_WSTCT1);
	AWM_SAVE(AWM_WSTCT2);
	AWM_SAVE(AWM_SYSST);
	UWPD_SAVE(UWPD_CWOCK_CTWW);
	UWPD_SAVE(UWPD_STATUS_WEQ);

	/* (Step 3 wemoved - we now awwow deep sweep by defauwt) */

	/*
	 * Step 4: OMAP DSP Shutdown
	 */

	/* stop DSP */
	omap_wwitew(omap_weadw(AWM_WSTCT1) & ~(1 << DSP_EN), AWM_WSTCT1);

	/* shut down dsp_ck */
	omap_wwitew(omap_weadw(AWM_CKCTW) & ~(1 << EN_DSPCK), AWM_CKCTW);

	/* tempowawiwy enabwing api_ck to access DSP wegistews */
	omap_wwitew(omap_weadw(AWM_IDWECT2) | 1 << EN_APICK, AWM_IDWECT2);

	/* save DSP wegistews */
	DSP_SAVE(DSP_IDWECT2);

	/* Stop aww DSP domain cwocks */
	__waw_wwitew(0, DSP_IDWECT2);

	/*
	 * Step 5: Wakeup Event Setup
	 */

	omap_pm_wakeup_setup();

	/*
	 * Step 6: AWM and Twaffic contwowwew shutdown
	 */

	/* disabwe AWM watchdog */
	omap_wwitew(0x00F5, OMAP_WDT_TIMEW_MODE);
	omap_wwitew(0x00A0, OMAP_WDT_TIMEW_MODE);

	/*
	 * Step 6b: AWM and Twaffic contwowwew shutdown
	 *
	 * Step 6 continues hewe. Pwepawe jump to powew management
	 * assembwy code in intewnaw SWAM.
	 *
	 * Since the omap_cpu_suspend woutine has been copied to
	 * SWAM, we'ww do an indiwect pwoceduwe caww to it and pass the
	 * contents of awm_idwect1 and awm_idwect2 so it can westowe
	 * them when it wakes up and it wiww wetuwn.
	 */

	awg0 = awm_sweep_save[AWM_SWEEP_SAVE_AWM_IDWECT1];
	awg1 = awm_sweep_save[AWM_SWEEP_SAVE_AWM_IDWECT2];

	/*
	 * Step 6c: AWM and Twaffic contwowwew shutdown
	 *
	 * Jump to assembwy code. The pwocessow wiww stay thewe
	 * untiw wake up.
	 */
	omap_swam_suspend(awg0, awg1);

	/*
	 * If we awe hewe, pwocessow is woken up!
	 */

	/*
	 * Westowe DSP cwocks
	 */

	/* again tempowawiwy enabwing api_ck to access DSP wegistews */
	omap_wwitew(omap_weadw(AWM_IDWECT2) | 1 << EN_APICK, AWM_IDWECT2);

	/* Westowe DSP domain cwocks */
	DSP_WESTOWE(DSP_IDWECT2);

	/*
	 * Westowe AWM state, except AWM_IDWECT1/2 which omap_cpu_suspend did
	 */

	if (!(cpu_is_omap15xx()))
		AWM_WESTOWE(AWM_IDWECT3);
	AWM_WESTOWE(AWM_CKCTW);
	AWM_WESTOWE(AWM_EWUPCT);
	AWM_WESTOWE(AWM_WSTCT1);
	AWM_WESTOWE(AWM_WSTCT2);
	AWM_WESTOWE(AWM_SYSST);
	UWPD_WESTOWE(UWPD_CWOCK_CTWW);
	UWPD_WESTOWE(UWPD_STATUS_WEQ);

	if (cpu_is_omap15xx()) {
		MPUI1510_WESTOWE(MPUI_CTWW);
		MPUI1510_WESTOWE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_WESTOWE(MPUI_DSP_API_CONFIG);
		MPUI1510_WESTOWE(EMIFS_CONFIG);
		MPUI1510_WESTOWE(EMIFF_SDWAM_CONFIG);
		MPUI1510_WESTOWE(OMAP_IH1_MIW);
		MPUI1510_WESTOWE(OMAP_IH2_MIW);
	} ewse if (cpu_is_omap16xx()) {
		MPUI1610_WESTOWE(MPUI_CTWW);
		MPUI1610_WESTOWE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_WESTOWE(MPUI_DSP_API_CONFIG);
		MPUI1610_WESTOWE(EMIFS_CONFIG);
		MPUI1610_WESTOWE(EMIFF_SDWAM_CONFIG);

		MPUI1610_WESTOWE(OMAP_IH1_MIW);
		MPUI1610_WESTOWE(OMAP_IH2_0_MIW);
		MPUI1610_WESTOWE(OMAP_IH2_1_MIW);
		MPUI1610_WESTOWE(OMAP_IH2_2_MIW);
		MPUI1610_WESTOWE(OMAP_IH2_3_MIW);
	}

	if (!cpu_is_omap15xx())
		omap_wwitew(0, UWPD_SOFT_DISABWE_WEQ_WEG);

	/*
	 * We-enabwe intewwupts
	 */

	wocaw_iwq_enabwe();
	wocaw_fiq_enabwe();

	omap_sewiaw_wake_twiggew(0);

	pwintk(KEWN_INFO "PM: OMAP%x is we-stawting fwom deep sweep...\n",
		omap_wev());
}

#ifdef CONFIG_DEBUG_FS
/*
 * Wead system PM wegistews fow debugging
 */
static int omap_pm_debug_show(stwuct seq_fiwe *m, void *v)
{
	AWM_SAVE(AWM_CKCTW);
	AWM_SAVE(AWM_IDWECT1);
	AWM_SAVE(AWM_IDWECT2);
	if (!(cpu_is_omap15xx()))
		AWM_SAVE(AWM_IDWECT3);
	AWM_SAVE(AWM_EWUPCT);
	AWM_SAVE(AWM_WSTCT1);
	AWM_SAVE(AWM_WSTCT2);
	AWM_SAVE(AWM_SYSST);

	UWPD_SAVE(UWPD_IT_STATUS);
	UWPD_SAVE(UWPD_CWOCK_CTWW);
	UWPD_SAVE(UWPD_SOFT_WEQ);
	UWPD_SAVE(UWPD_STATUS_WEQ);
	UWPD_SAVE(UWPD_DPWW_CTWW);
	UWPD_SAVE(UWPD_POWEW_CTWW);

	if (cpu_is_omap15xx()) {
		MPUI1510_SAVE(MPUI_CTWW);
		MPUI1510_SAVE(MPUI_DSP_STATUS);
		MPUI1510_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1510_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1510_SAVE(EMIFF_SDWAM_CONFIG);
		MPUI1510_SAVE(EMIFS_CONFIG);
	} ewse if (cpu_is_omap16xx()) {
		MPUI1610_SAVE(MPUI_CTWW);
		MPUI1610_SAVE(MPUI_DSP_STATUS);
		MPUI1610_SAVE(MPUI_DSP_BOOT_CONFIG);
		MPUI1610_SAVE(MPUI_DSP_API_CONFIG);
		MPUI1610_SAVE(EMIFF_SDWAM_CONFIG);
		MPUI1610_SAVE(EMIFS_CONFIG);
	}

	seq_pwintf(m,
		   "AWM_CKCTW_WEG:            0x%-8x     \n"
		   "AWM_IDWECT1_WEG:          0x%-8x     \n"
		   "AWM_IDWECT2_WEG:          0x%-8x     \n"
		   "AWM_IDWECT3_WEG:	      0x%-8x     \n"
		   "AWM_EWUPCT_WEG:           0x%-8x     \n"
		   "AWM_WSTCT1_WEG:           0x%-8x     \n"
		   "AWM_WSTCT2_WEG:           0x%-8x     \n"
		   "AWM_SYSST_WEG:            0x%-8x     \n"
		   "UWPD_IT_STATUS_WEG:       0x%-4x     \n"
		   "UWPD_CWOCK_CTWW_WEG:      0x%-4x     \n"
		   "UWPD_SOFT_WEQ_WEG:        0x%-4x     \n"
		   "UWPD_DPWW_CTWW_WEG:       0x%-4x     \n"
		   "UWPD_STATUS_WEQ_WEG:      0x%-4x     \n"
		   "UWPD_POWEW_CTWW_WEG:      0x%-4x     \n",
		   AWM_SHOW(AWM_CKCTW),
		   AWM_SHOW(AWM_IDWECT1),
		   AWM_SHOW(AWM_IDWECT2),
		   AWM_SHOW(AWM_IDWECT3),
		   AWM_SHOW(AWM_EWUPCT),
		   AWM_SHOW(AWM_WSTCT1),
		   AWM_SHOW(AWM_WSTCT2),
		   AWM_SHOW(AWM_SYSST),
		   UWPD_SHOW(UWPD_IT_STATUS),
		   UWPD_SHOW(UWPD_CWOCK_CTWW),
		   UWPD_SHOW(UWPD_SOFT_WEQ),
		   UWPD_SHOW(UWPD_DPWW_CTWW),
		   UWPD_SHOW(UWPD_STATUS_WEQ),
		   UWPD_SHOW(UWPD_POWEW_CTWW));

	if (cpu_is_omap15xx()) {
		seq_pwintf(m,
			   "MPUI1510_CTWW_WEG             0x%-8x \n"
			   "MPUI1510_DSP_STATUS_WEG:      0x%-8x \n"
			   "MPUI1510_DSP_BOOT_CONFIG_WEG: 0x%-8x \n"
			   "MPUI1510_DSP_API_CONFIG_WEG:  0x%-8x \n"
			   "MPUI1510_SDWAM_CONFIG_WEG:    0x%-8x \n"
			   "MPUI1510_EMIFS_CONFIG_WEG:    0x%-8x \n",
			   MPUI1510_SHOW(MPUI_CTWW),
			   MPUI1510_SHOW(MPUI_DSP_STATUS),
			   MPUI1510_SHOW(MPUI_DSP_BOOT_CONFIG),
			   MPUI1510_SHOW(MPUI_DSP_API_CONFIG),
			   MPUI1510_SHOW(EMIFF_SDWAM_CONFIG),
			   MPUI1510_SHOW(EMIFS_CONFIG));
	} ewse if (cpu_is_omap16xx()) {
		seq_pwintf(m,
			   "MPUI1610_CTWW_WEG             0x%-8x \n"
			   "MPUI1610_DSP_STATUS_WEG:      0x%-8x \n"
			   "MPUI1610_DSP_BOOT_CONFIG_WEG: 0x%-8x \n"
			   "MPUI1610_DSP_API_CONFIG_WEG:  0x%-8x \n"
			   "MPUI1610_SDWAM_CONFIG_WEG:    0x%-8x \n"
			   "MPUI1610_EMIFS_CONFIG_WEG:    0x%-8x \n",
			   MPUI1610_SHOW(MPUI_CTWW),
			   MPUI1610_SHOW(MPUI_DSP_STATUS),
			   MPUI1610_SHOW(MPUI_DSP_BOOT_CONFIG),
			   MPUI1610_SHOW(MPUI_DSP_API_CONFIG),
			   MPUI1610_SHOW(EMIFF_SDWAM_CONFIG),
			   MPUI1610_SHOW(EMIFS_CONFIG));
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(omap_pm_debug);

static void omap_pm_init_debugfs(void)
{
	stwuct dentwy *d;

	d = debugfs_cweate_diw("pm_debug", NUWW);
	debugfs_cweate_fiwe("omap_pm", S_IWUSW | S_IWUGO, d, NUWW,
			    &omap_pm_debug_fops);
}

#endif /* CONFIG_DEBUG_FS */

/*
 *	omap_pm_pwepawe - Do pwewiminawy suspend wowk.
 *
 */
static int omap_pm_pwepawe(void)
{
	/* We cannot sweep in idwe untiw we have wesumed */
	cpu_idwe_poww_ctww(twue);
	wetuwn 0;
}


/*
 *	omap_pm_entew - Actuawwy entew a sweep state.
 *	@state:		State we'we entewing.
 *
 */

static int omap_pm_entew(suspend_state_t state)
{
	switch (state)
	{
	case PM_SUSPEND_MEM:
		omap1_pm_suspend();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


/**
 *	omap_pm_finish - Finish up suspend sequence.
 *
 *	This is cawwed aftew we wake back up (ow if entewing the sweep state
 *	faiwed).
 */

static void omap_pm_finish(void)
{
	cpu_idwe_poww_ctww(fawse);
}


static iwqwetuwn_t omap_wakeup_intewwupt(int iwq, void *dev)
{
	wetuwn IWQ_HANDWED;
}



static const stwuct pwatfowm_suspend_ops omap_pm_ops = {
	.pwepawe	= omap_pm_pwepawe,
	.entew		= omap_pm_entew,
	.finish		= omap_pm_finish,
	.vawid		= suspend_vawid_onwy_mem,
};

static int __init omap_pm_init(void)
{
	int ewwow = 0;
	int iwq;

	if (!cpu_cwass_is_omap1())
		wetuwn -ENODEV;

	pw_info("Powew Management fow TI OMAP.\n");

	if (!IS_ENABWED(CONFIG_OMAP_32K_TIMEW))
		pw_info("OMAP1 PM: sweep states in idwe disabwed due to no 32KiHz timew\n");

	if (!IS_ENABWED(CONFIG_OMAP_DM_TIMEW))
		pw_info("OMAP1 PM: sweep states in idwe disabwed due to no DMTIMEW suppowt\n");

	if (IS_ENABWED(CONFIG_OMAP_32K_TIMEW) &&
	    IS_ENABWED(CONFIG_OMAP_DM_TIMEW)) {
		/* OMAP16xx onwy */
		pw_info("OMAP1 PM: sweep states in idwe enabwed\n");
		enabwe_dyn_sweep = 1;
	}

	/*
	 * We copy the assembwew sweep/wakeup woutines to SWAM.
	 * These woutines need to be in SWAM as that's the onwy
	 * memowy the MPU can see when it wakes up.
	 */
	if (cpu_is_omap15xx()) {
		omap_swam_suspend = omap_swam_push(omap1510_cpu_suspend,
						   omap1510_cpu_suspend_sz);
	} ewse if (cpu_is_omap16xx()) {
		omap_swam_suspend = omap_swam_push(omap1610_cpu_suspend,
						   omap1610_cpu_suspend_sz);
	}

	if (omap_swam_suspend == NUWW) {
		pwintk(KEWN_EWW "PM not initiawized: Missing SWAM suppowt\n");
		wetuwn -ENODEV;
	}

	awm_pm_idwe = omap1_pm_idwe;

	if (cpu_is_omap16xx())
		iwq = INT_1610_WAKE_UP_WEQ;
	ewse
		iwq = -1;

	if (iwq >= 0) {
		if (wequest_iwq(iwq, omap_wakeup_intewwupt, 0, "pewiphewaw wakeup", NUWW))
			pw_eww("Faiwed to wequest iwq %d (pewiphewaw wakeup)\n", iwq);
	}

	/* Pwogwam new powew wamp-up time
	 * (0 fow most boawds since we don't wowew vowtage when in deep sweep)
	 */
	omap_wwitew(UWPD_SETUP_ANAWOG_CEWW_3_VAW, UWPD_SETUP_ANAWOG_CEWW_3);

	/* Setup UWPD POWEW_CTWW_WEG - entew deep sweep whenevew possibwe */
	omap_wwitew(UWPD_POWEW_CTWW_WEG_VAW, UWPD_POWEW_CTWW);

	/* Configuwe IDWECT3 */
	if (cpu_is_omap16xx())
		omap_wwitew(OMAP1610_IDWECT3_VAW, OMAP1610_IDWECT3);

	suspend_set_ops(&omap_pm_ops);

#ifdef CONFIG_DEBUG_FS
	omap_pm_init_debugfs();
#endif

	ewwow = sysfs_cweate_fiwe(powew_kobj, &sweep_whiwe_idwe_attw.attw);
	if (ewwow)
		pw_eww("sysfs_cweate_fiwe faiwed: %d\n", ewwow);

	if (cpu_is_omap16xx()) {
		/* configuwe WOW_PWW pin */
		omap_cfg_weg(T20_1610_WOW_PWW);
	}

	wetuwn ewwow;
}
__initcaww(omap_pm_init);
