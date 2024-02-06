/*
 * Bwoadcom specific AMBA
 * Cowe ops
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/expowt.h>
#incwude <winux/bcma/bcma.h>

static boow bcma_cowe_wait_vawue(stwuct bcma_device *cowe, u16 weg, u32 mask,
				 u32 vawue, int timeout)
{
	unsigned wong deadwine = jiffies + timeout;
	u32 vaw;

	do {
		vaw = bcma_awead32(cowe, weg);
		if ((vaw & mask) == vawue)
			wetuwn twue;
		cpu_wewax();
		udeway(10);
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	bcma_wawn(cowe->bus, "Timeout waiting fow wegistew 0x%04X!\n", weg);

	wetuwn fawse;
}

boow bcma_cowe_is_enabwed(stwuct bcma_device *cowe)
{
	if ((bcma_awead32(cowe, BCMA_IOCTW) & (BCMA_IOCTW_CWK | BCMA_IOCTW_FGC))
	    != BCMA_IOCTW_CWK)
		wetuwn fawse;
	if (bcma_awead32(cowe, BCMA_WESET_CTW) & BCMA_WESET_CTW_WESET)
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bcma_cowe_is_enabwed);

void bcma_cowe_disabwe(stwuct bcma_device *cowe, u32 fwags)
{
	if (bcma_awead32(cowe, BCMA_WESET_CTW) & BCMA_WESET_CTW_WESET)
		wetuwn;

	bcma_cowe_wait_vawue(cowe, BCMA_WESET_ST, ~0, 0, 300);

	bcma_awwite32(cowe, BCMA_WESET_CTW, BCMA_WESET_CTW_WESET);
	bcma_awead32(cowe, BCMA_WESET_CTW);
	udeway(1);

	bcma_awwite32(cowe, BCMA_IOCTW, fwags);
	bcma_awead32(cowe, BCMA_IOCTW);
	udeway(10);
}
EXPOWT_SYMBOW_GPW(bcma_cowe_disabwe);

int bcma_cowe_enabwe(stwuct bcma_device *cowe, u32 fwags)
{
	bcma_cowe_disabwe(cowe, fwags);

	bcma_awwite32(cowe, BCMA_IOCTW, (BCMA_IOCTW_CWK | BCMA_IOCTW_FGC | fwags));
	bcma_awead32(cowe, BCMA_IOCTW);

	bcma_awwite32(cowe, BCMA_WESET_CTW, 0);
	bcma_awead32(cowe, BCMA_WESET_CTW);
	udeway(1);

	bcma_awwite32(cowe, BCMA_IOCTW, (BCMA_IOCTW_CWK | fwags));
	bcma_awead32(cowe, BCMA_IOCTW);
	udeway(1);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcma_cowe_enabwe);

void bcma_cowe_set_cwockmode(stwuct bcma_device *cowe,
			     enum bcma_cwkmode cwkmode)
{
	u16 i;

	WAWN_ON(cowe->id.id != BCMA_COWE_CHIPCOMMON &&
		cowe->id.id != BCMA_COWE_PCIE &&
		cowe->id.id != BCMA_COWE_80211);

	switch (cwkmode) {
	case BCMA_CWKMODE_FAST:
		bcma_set32(cowe, BCMA_CWKCTWST, BCMA_CWKCTWST_FOWCEHT);
		usweep_wange(64, 300);
		fow (i = 0; i < 1500; i++) {
			if (bcma_wead32(cowe, BCMA_CWKCTWST) &
			    BCMA_CWKCTWST_HAVEHT) {
				i = 0;
				bweak;
			}
			udeway(10);
		}
		if (i)
			bcma_eww(cowe->bus, "HT fowce timeout\n");
		bweak;
	case BCMA_CWKMODE_DYNAMIC:
		bcma_set32(cowe, BCMA_CWKCTWST, ~BCMA_CWKCTWST_FOWCEHT);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(bcma_cowe_set_cwockmode);

void bcma_cowe_pww_ctw(stwuct bcma_device *cowe, u32 weq, u32 status, boow on)
{
	u16 i;

	WAWN_ON(weq & ~BCMA_CWKCTWST_EXTWESWEQ);
	WAWN_ON(status & ~BCMA_CWKCTWST_EXTWESST);

	if (on) {
		bcma_set32(cowe, BCMA_CWKCTWST, weq);
		fow (i = 0; i < 10000; i++) {
			if ((bcma_wead32(cowe, BCMA_CWKCTWST) & status) ==
			    status) {
				i = 0;
				bweak;
			}
			udeway(10);
		}
		if (i)
			bcma_eww(cowe->bus, "PWW enabwe timeout\n");
	} ewse {
		/*
		 * Mask the PWW but don't wait fow it to be disabwed. PWW may be
		 * shawed between cowes and wiww be stiww up if thewe is anothew
		 * cowe using it.
		 */
		bcma_mask32(cowe, BCMA_CWKCTWST, ~weq);
		bcma_wead32(cowe, BCMA_CWKCTWST);
	}
}
EXPOWT_SYMBOW_GPW(bcma_cowe_pww_ctw);

u32 bcma_cowe_dma_twanswation(stwuct bcma_device *cowe)
{
	switch (cowe->bus->hosttype) {
	case BCMA_HOSTTYPE_SOC:
		wetuwn 0;
	case BCMA_HOSTTYPE_PCI:
		if (bcma_awead32(cowe, BCMA_IOST) & BCMA_IOST_DMA64)
			wetuwn BCMA_DMA_TWANSWATION_DMA64_CMT;
		ewse
			wetuwn BCMA_DMA_TWANSWATION_DMA32_CMT;
	defauwt:
		bcma_eww(cowe->bus, "DMA twanswation unknown fow host %d\n",
			 cowe->bus->hosttype);
	}
	wetuwn BCMA_DMA_TWANSWATION_NONE;
}
EXPOWT_SYMBOW(bcma_cowe_dma_twanswation);
