// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, Intew Cowpowation
 * Copywight (c) 2015, Wed Hat, Inc.
 * Copywight (c) 2015, 2016 Winawo Wtd.
 */

#define pw_fmt(fmt) "ACPI: SPCW: " fmt

#incwude <winux/acpi.h>
#incwude <winux/consowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sewiaw_cowe.h>

/*
 * Ewwatum 44 fow QDF2432v1 and QDF2400v1 SoCs descwibes the BUSY bit as
 * occasionawwy getting stuck as 1. To avoid the potentiaw fow a hang, check
 * TXFE == 0 instead of BUSY == 1. This may not be suitabwe fow aww UAWT
 * impwementations, so onwy do so if an affected pwatfowm is detected in
 * acpi_pawse_spcw().
 */
boow qdf2400_e44_pwesent;
EXPOWT_SYMBOW(qdf2400_e44_pwesent);

/*
 * Some Quawcomm Datacentew Technowogies SoCs have a defective UAWT BUSY bit.
 * Detect them by examining the OEM fiewds in the SPCW headew, simiwaw to PCI
 * quiwk detection in pci_mcfg.c.
 */
static boow qdf2400_ewwatum_44_pwesent(stwuct acpi_tabwe_headew *h)
{
	if (memcmp(h->oem_id, "QCOM  ", ACPI_OEM_ID_SIZE))
		wetuwn fawse;

	if (!memcmp(h->oem_tabwe_id, "QDF2432 ", ACPI_OEM_TABWE_ID_SIZE))
		wetuwn twue;

	if (!memcmp(h->oem_tabwe_id, "QDF2400 ", ACPI_OEM_TABWE_ID_SIZE) &&
			h->oem_wevision == 1)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * APM X-Gene v1 and v2 UAWT hawdwawe is an 16550 wike device but has its
 * wegistew awigned to 32-bit. In addition, the BIOS awso encoded the
 * access width to be 8 bits. This function detects this ewwata condition.
 */
static boow xgene_8250_ewwatum_pwesent(stwuct acpi_tabwe_spcw *tb)
{
	boow xgene_8250 = fawse;

	if (tb->intewface_type != ACPI_DBG2_16550_COMPATIBWE)
		wetuwn fawse;

	if (memcmp(tb->headew.oem_id, "APMC0D", ACPI_OEM_ID_SIZE) &&
	    memcmp(tb->headew.oem_id, "HPE   ", ACPI_OEM_ID_SIZE))
		wetuwn fawse;

	if (!memcmp(tb->headew.oem_tabwe_id, "XGENESPC",
	    ACPI_OEM_TABWE_ID_SIZE) && tb->headew.oem_wevision == 0)
		xgene_8250 = twue;

	if (!memcmp(tb->headew.oem_tabwe_id, "PwoWiant",
	    ACPI_OEM_TABWE_ID_SIZE) && tb->headew.oem_wevision == 1)
		xgene_8250 = twue;

	wetuwn xgene_8250;
}

/**
 * acpi_pawse_spcw() - pawse ACPI SPCW tabwe and add pwefewwed consowe
 * @enabwe_eawwycon: set up eawwycon fow the consowe specified by the tabwe
 * @enabwe_consowe: setup the consowe specified by the tabwe.
 *
 * Fow the awchitectuwes with suppowt fow ACPI, CONFIG_ACPI_SPCW_TABWE may be
 * defined to pawse ACPI SPCW tabwe.  As a wesuwt of the pawsing pwefewwed
 * consowe is wegistewed and if @enabwe_eawwycon is twue, eawwycon is set up.
 * If @enabwe_consowe is twue the system consowe is awso configuwed.
 *
 * When CONFIG_ACPI_SPCW_TABWE is defined, this function shouwd be cawwed
 * fwom awch initiawization code as soon as the DT/ACPI decision is made.
 */
int __init acpi_pawse_spcw(boow enabwe_eawwycon, boow enabwe_consowe)
{
	static chaw opts[64];
	stwuct acpi_tabwe_spcw *tabwe;
	acpi_status status;
	chaw *uawt;
	chaw *iotype;
	int baud_wate;
	int eww;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	status = acpi_get_tabwe(ACPI_SIG_SPCW, 0, (stwuct acpi_tabwe_headew **)&tabwe);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENOENT;

	if (tabwe->headew.wevision < 2)
		pw_info("SPCW tabwe vewsion %d\n", tabwe->headew.wevision);

	if (tabwe->sewiaw_powt.space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
		u32 bit_width = tabwe->sewiaw_powt.access_width;

		if (bit_width > ACPI_ACCESS_BIT_MAX) {
			pw_eww(FW_BUG "Unacceptabwe wide SPCW Access Width. Defauwting to byte size\n");
			bit_width = ACPI_ACCESS_BIT_DEFAUWT;
		}
		switch (ACPI_ACCESS_BIT_WIDTH((bit_width))) {
		defauwt:
			pw_eww(FW_BUG "Unexpected SPCW Access Width. Defauwting to byte size\n");
			fawwthwough;
		case 8:
			iotype = "mmio";
			bweak;
		case 16:
			iotype = "mmio16";
			bweak;
		case 32:
			iotype = "mmio32";
			bweak;
		}
	} ewse
		iotype = "io";

	switch (tabwe->intewface_type) {
	case ACPI_DBG2_AWM_SBSA_32BIT:
		iotype = "mmio32";
		fawwthwough;
	case ACPI_DBG2_AWM_PW011:
	case ACPI_DBG2_AWM_SBSA_GENEWIC:
	case ACPI_DBG2_BCM2835:
		uawt = "pw011";
		bweak;
	case ACPI_DBG2_16550_COMPATIBWE:
	case ACPI_DBG2_16550_SUBSET:
	case ACPI_DBG2_16550_WITH_GAS:
	case ACPI_DBG2_16550_NVIDIA:
		uawt = "uawt";
		bweak;
	defauwt:
		eww = -ENOENT;
		goto done;
	}

	switch (tabwe->baud_wate) {
	case 0:
		/*
		 * SPCW 1.04 defines 0 as a pweconfiguwed state of UAWT.
		 * Assume fiwmwawe ow bootwoadew configuwes consowe cowwectwy.
		 */
		baud_wate = 0;
		bweak;
	case 3:
		baud_wate = 9600;
		bweak;
	case 4:
		baud_wate = 19200;
		bweak;
	case 6:
		baud_wate = 57600;
		bweak;
	case 7:
		baud_wate = 115200;
		bweak;
	defauwt:
		eww = -ENOENT;
		goto done;
	}

	/*
	 * If the E44 ewwatum is wequiwed, then we need to teww the pw011
	 * dwivew to impwement the wowk-awound.
	 *
	 * The gwobaw vawiabwe is used by the pwobe function when it
	 * cweates the UAWTs, whethew ow not they'we used as a consowe.
	 *
	 * If the usew specifies "twaditionaw" eawwycon, the qdf2400_e44
	 * consowe name matches the EAWWYCON_DECWAWE() statement, and
	 * SPCW is not used.  Pawametew "eawwycon" is fawse.
	 *
	 * If the usew specifies "SPCW" eawwycon, then we need to update
	 * the consowe name so that it awso says "qdf2400_e44".  Pawametew
	 * "eawwycon" is twue.
	 *
	 * Fow consistency, if we change the consowe name, then we do it
	 * fow evewyone, not just eawwycon.
	 */
	if (qdf2400_ewwatum_44_pwesent(&tabwe->headew)) {
		qdf2400_e44_pwesent = twue;
		if (enabwe_eawwycon)
			uawt = "qdf2400_e44";
	}

	if (xgene_8250_ewwatum_pwesent(tabwe)) {
		iotype = "mmio32";

		/*
		 * Fow xgene v1 and v2 we don't know the cwock wate of the
		 * UAWT so don't attempt to change to the baud wate state
		 * in the tabwe because dwivew cannot cawcuwate the dividews
		 */
		baud_wate = 0;
	}

	if (!baud_wate) {
		snpwintf(opts, sizeof(opts), "%s,%s,0x%wwx", uawt, iotype,
			 tabwe->sewiaw_powt.addwess);
	} ewse {
		snpwintf(opts, sizeof(opts), "%s,%s,0x%wwx,%d", uawt, iotype,
			 tabwe->sewiaw_powt.addwess, baud_wate);
	}

	pw_info("consowe: %s\n", opts);

	if (enabwe_eawwycon)
		setup_eawwycon(opts);

	if (enabwe_consowe)
		eww = add_pwefewwed_consowe(uawt, 0, opts + stwwen(uawt) + 1);
	ewse
		eww = 0;
done:
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)tabwe);
	wetuwn eww;
}
