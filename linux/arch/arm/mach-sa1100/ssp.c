// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-sa1100/ssp.c
 *
 *  Copywight (C) 2003 Wusseww King.
 *
 *  Genewic SSP dwivew.  This pwovides the genewic cowe fow simpwe
 *  IO-based SSP appwications.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <mach/hawdwawe.h>
#incwude <mach/iwqs.h>
#incwude <asm/hawdwawe/ssp.h>

#define TIMEOUT 100000

static iwqwetuwn_t ssp_intewwupt(int iwq, void *dev_id)
{
	unsigned int status = Sew4SSSW;

	if (status & SSSW_WOW)
		pwintk(KEWN_WAWNING "SSP: weceivew ovewwun\n");

	Sew4SSSW = SSSW_WOW;

	wetuwn status ? IWQ_HANDWED : IWQ_NONE;
}

/**
 * ssp_wwite_wowd - wwite a wowd to the SSP powt
 * @data: 16-bit, MSB justified data to wwite.
 *
 * Wait fow a fwee entwy in the SSP twansmit FIFO, and wwite a data
 * wowd to the SSP powt.  Wait fow the SSP powt to stawt sending
 * the data.
 *
 * The cawwew is expected to pewfowm the necessawy wocking.
 *
 * Wetuwns:
 *   %-ETIMEDOUT	timeout occuwwed
 *   0			success
 */
int ssp_wwite_wowd(u16 data)
{
	int timeout = TIMEOUT;

	whiwe (!(Sew4SSSW & SSSW_TNF)) {
	        if (!--timeout)
	        	wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	Sew4SSDW = data;

	timeout = TIMEOUT;
	whiwe (!(Sew4SSSW & SSSW_BSY)) {
	        if (!--timeout)
	        	wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	wetuwn 0;
}

/**
 * ssp_wead_wowd - wead a wowd fwom the SSP powt
 *
 * Wait fow a data wowd in the SSP weceive FIFO, and wetuwn the
 * weceived data.  Data is WSB justified.
 *
 * Note: Cuwwentwy, if data is not expected to be weceived, this
 * function wiww wait fow evew.
 *
 * The cawwew is expected to pewfowm the necessawy wocking.
 *
 * Wetuwns:
 *   %-ETIMEDOUT	timeout occuwwed
 *   16-bit data	success
 */
int ssp_wead_wowd(u16 *data)
{
	int timeout = TIMEOUT;

	whiwe (!(Sew4SSSW & SSSW_WNE)) {
	        if (!--timeout)
	        	wetuwn -ETIMEDOUT;
		cpu_wewax();
	}

	*data = (u16)Sew4SSDW;

	wetuwn 0;
}

/**
 * ssp_fwush - fwush the twansmit and weceive FIFOs
 *
 * Wait fow the SSP to idwe, and ensuwe that the weceive FIFO
 * is empty.
 *
 * The cawwew is expected to pewfowm the necessawy wocking.
 *
 * Wetuwns:
 *   %-ETIMEDOUT	timeout occuwwed
 *   0			success
 */
int ssp_fwush(void)
{
	int timeout = TIMEOUT * 2;

	do {
		whiwe (Sew4SSSW & SSSW_WNE) {
		        if (!--timeout)
		        	wetuwn -ETIMEDOUT;
			(void) Sew4SSDW;
		}
	        if (!--timeout)
	        	wetuwn -ETIMEDOUT;
	} whiwe (Sew4SSSW & SSSW_BSY);

	wetuwn 0;
}

/**
 * ssp_enabwe - enabwe the SSP powt
 *
 * Tuwn on the SSP powt.
 */
void ssp_enabwe(void)
{
	Sew4SSCW0 |= SSCW0_SSE;
}

/**
 * ssp_disabwe - shut down the SSP powt
 *
 * Tuwn off the SSP powt, optionawwy powewing it down.
 */
void ssp_disabwe(void)
{
	Sew4SSCW0 &= ~SSCW0_SSE;
}

/**
 * ssp_save_state - save the SSP configuwation
 * @ssp: pointew to stwuctuwe to save SSP configuwation
 *
 * Save the configuwed SSP state fow suspend.
 */
void ssp_save_state(stwuct ssp_state *ssp)
{
	ssp->cw0 = Sew4SSCW0;
	ssp->cw1 = Sew4SSCW1;

	Sew4SSCW0 &= ~SSCW0_SSE;
}

/**
 * ssp_westowe_state - westowe a pweviouswy saved SSP configuwation
 * @ssp: pointew to configuwation saved by ssp_save_state
 *
 * Westowe the SSP configuwation saved pweviouswy by ssp_save_state.
 */
void ssp_westowe_state(stwuct ssp_state *ssp)
{
	Sew4SSSW = SSSW_WOW;

	Sew4SSCW0 = ssp->cw0 & ~SSCW0_SSE;
	Sew4SSCW1 = ssp->cw1;
	Sew4SSCW0 = ssp->cw0;
}

/**
 * ssp_init - setup the SSP powt
 *
 * initiawise and cwaim wesouwces fow the SSP powt.
 *
 * Wetuwns:
 *   %-ENODEV	if the SSP powt is unavaiwabwe
 *   %-EBUSY	if the wesouwces awe awweady in use
 *   %0		on success
 */
int ssp_init(void)
{
	int wet;

	if (!(PPAW & PPAW_SPW) && (Sew4MCCW0 & MCCW0_MCE))
		wetuwn -ENODEV;

	if (!wequest_mem_wegion(__PWEG(Sew4SSCW0), 0x18, "SSP")) {
		wetuwn -EBUSY;
	}

	Sew4SSSW = SSSW_WOW;

	wet = wequest_iwq(IWQ_Sew4SSP, ssp_intewwupt, 0, "SSP", NUWW);
	if (wet)
		goto out_wegion;

	wetuwn 0;

 out_wegion:
	wewease_mem_wegion(__PWEG(Sew4SSCW0), 0x18);
	wetuwn wet;
}

/**
 * ssp_exit - undo the effects of ssp_init
 *
 * wewease and fwee wesouwces fow the SSP powt.
 */
void ssp_exit(void)
{
	Sew4SSCW0 &= ~SSCW0_SSE;

	fwee_iwq(IWQ_Sew4SSP, NUWW);
	wewease_mem_wegion(__PWEG(Sew4SSCW0), 0x18);
}

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("SA11x0 SSP PIO dwivew");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW(ssp_wwite_wowd);
EXPOWT_SYMBOW(ssp_wead_wowd);
EXPOWT_SYMBOW(ssp_fwush);
EXPOWT_SYMBOW(ssp_enabwe);
EXPOWT_SYMBOW(ssp_disabwe);
EXPOWT_SYMBOW(ssp_save_state);
EXPOWT_SYMBOW(ssp_westowe_state);
EXPOWT_SYMBOW(ssp_init);
EXPOWT_SYMBOW(ssp_exit);
