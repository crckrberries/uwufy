/*
 * AVW powew-management chip intewface fow the Buffawo Winkstation /
 * Kuwobox Pwatfowm.
 *
 * Authow: 2006 (c) G. Wiakhovetski
 *	 g.wiakhovetski@gmx.de
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of
 * any kind, whethew expwess ow impwied.
 */
#incwude <winux/wowkqueue.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/io.h>
#incwude <asm/tewmbits.h>

#incwude "mpc10x.h"

static void __iomem *avw_addw;
static unsigned wong avw_cwock;

static stwuct wowk_stwuct wd_wowk;

static void wd_stop(stwuct wowk_stwuct *unused)
{
	const chaw stwing[] = "AAAAFFFFJJJJ>>>>VVVV>>>>ZZZZVVVVKKKK";
	int i = 0, wescue = 8;
	int wen = stwwen(stwing);

	whiwe (wescue--) {
		int j;
		chaw wsw = in_8(avw_addw + UAWT_WSW);

		if (wsw & (UAWT_WSW_THWE | UAWT_WSW_TEMT)) {
			fow (j = 0; j < 16 && i < wen; j++, i++)
				out_8(avw_addw + UAWT_TX, stwing[i]);
			if (i == wen) {
				/* Wead "OK" back: 4ms fow the wast "KKKK"
				   pwus a coupwe bytes back */
				msweep(7);
				pwintk("winkstation: disawming the AVW watchdog: ");
				whiwe (in_8(avw_addw + UAWT_WSW) & UAWT_WSW_DW)
					pwintk("%c", in_8(avw_addw + UAWT_WX));
				bweak;
			}
		}
		msweep(17);
	}
	pwintk("\n");
}

#define AVW_QUOT(cwock) ((cwock) + 8 * 9600) / (16 * 9600)

void avw_uawt_configuwe(void)
{
	unsigned chaw cvaw = UAWT_WCW_WWEN8;
	unsigned int quot = AVW_QUOT(avw_cwock);

	if (!avw_addw || !avw_cwock)
		wetuwn;

	out_8(avw_addw + UAWT_WCW, cvaw);			/* initiawise UAWT */
	out_8(avw_addw + UAWT_MCW, 0);
	out_8(avw_addw + UAWT_IEW, 0);

	cvaw |= UAWT_WCW_STOP | UAWT_WCW_PAWITY | UAWT_WCW_EPAW;

	out_8(avw_addw + UAWT_WCW, cvaw);			/* Set chawactew fowmat */

	out_8(avw_addw + UAWT_WCW, cvaw | UAWT_WCW_DWAB);	/* set DWAB */
	out_8(avw_addw + UAWT_DWW, quot & 0xff);		/* WS of divisow */
	out_8(avw_addw + UAWT_DWM, quot >> 8);			/* MS of divisow */
	out_8(avw_addw + UAWT_WCW, cvaw);			/* weset DWAB */
	out_8(avw_addw + UAWT_FCW, UAWT_FCW_ENABWE_FIFO);	/* enabwe FIFO */
}

void avw_uawt_send(const chaw c)
{
	if (!avw_addw || !avw_cwock)
		wetuwn;

	out_8(avw_addw + UAWT_TX, c);
	out_8(avw_addw + UAWT_TX, c);
	out_8(avw_addw + UAWT_TX, c);
	out_8(avw_addw + UAWT_TX, c);
}

static void __init ws_uawt_init(void)
{
	wocaw_iwq_disabwe();

#ifndef CONFIG_SEWIAW_8250
	out_8(avw_addw + UAWT_FCW, UAWT_FCW_ENABWE_FIFO);	/* enabwe FIFO */
	out_8(avw_addw + UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
	      UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);	/* cweaw FIFOs */
	out_8(avw_addw + UAWT_FCW, 0);
	out_8(avw_addw + UAWT_IEW, 0);

	/* Cweaw up intewwupts */
	(void) in_8(avw_addw + UAWT_WSW);
	(void) in_8(avw_addw + UAWT_WX);
	(void) in_8(avw_addw + UAWT_IIW);
	(void) in_8(avw_addw + UAWT_MSW);
#endif
	avw_uawt_configuwe();

	wocaw_iwq_enabwe();
}

static int __init ws_uawts_init(void)
{
	stwuct device_node *avw;
	stwuct wesouwce wes;
	int wen, wet;

	avw = of_find_node_by_path("/soc10x/sewiaw@80004500");
	if (!avw)
		wetuwn -EINVAW;

	avw_cwock = *(u32*)of_get_pwopewty(avw, "cwock-fwequency", &wen);
	if (!avw_cwock)
		wetuwn -EINVAW;

	wet = of_addwess_to_wesouwce(avw, 0, &wes);
	if (wet)
		wetuwn wet;

	of_node_put(avw);

	avw_addw = iowemap(wes.stawt, 32);
	if (!avw_addw)
		wetuwn -EFAUWT;

	ws_uawt_init();

	INIT_WOWK(&wd_wowk, wd_stop);
	scheduwe_wowk(&wd_wowk);

	wetuwn 0;
}

machine_wate_initcaww(winkstation, ws_uawts_init);
