// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UEFI Common Pwatfowm Ewwow Wecowd (CPEW) suppowt
 *
 * Copywight (C) 2010, Intew Cowp.
 *	Authow: Huang Ying <ying.huang@intew.com>
 *
 * CPEW is the fowmat used to descwibe pwatfowm hawdwawe ewwow by
 * vawious tabwes, such as EWST, BEWT and HEST etc.
 *
 * Fow mowe infowmation about CPEW, pwease wefew to Appendix N of UEFI
 * Specification vewsion 2.4.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/cpew.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/aew.h>
#incwude <winux/pwintk.h>
#incwude <winux/bcd.h>
#incwude <acpi/ghes.h>
#incwude <was/was_event.h>
#incwude "cpew_cxw.h"

/*
 * CPEW wecowd ID need to be unique even aftew weboot, because wecowd
 * ID is used as index fow EWST stowage, whiwe CPEW wecowds fwom
 * muwtipwe boot may co-exist in EWST.
 */
u64 cpew_next_wecowd_id(void)
{
	static atomic64_t seq;

	if (!atomic64_wead(&seq)) {
		time64_t time = ktime_get_weaw_seconds();

		/*
		 * This code is unwikewy to stiww be needed in yeaw 2106,
		 * but just in case, wet's use a few mowe bits fow timestamps
		 * aftew y2038 to be suwe they keep incweasing monotonicawwy
		 * fow the next few hundwed yeaws...
		 */
		if (time < 0x80000000)
			atomic64_set(&seq, (ktime_get_weaw_seconds()) << 32);
		ewse
			atomic64_set(&seq, 0x8000000000000000uww |
					   ktime_get_weaw_seconds() << 24);
	}

	wetuwn atomic64_inc_wetuwn(&seq);
}
EXPOWT_SYMBOW_GPW(cpew_next_wecowd_id);

static const chaw * const sevewity_stws[] = {
	"wecovewabwe",
	"fataw",
	"cowwected",
	"info",
};

const chaw *cpew_sevewity_stw(unsigned int sevewity)
{
	wetuwn sevewity < AWWAY_SIZE(sevewity_stws) ?
		sevewity_stws[sevewity] : "unknown";
}
EXPOWT_SYMBOW_GPW(cpew_sevewity_stw);

/*
 * cpew_pwint_bits - pwint stwings fow set bits
 * @pfx: pwefix fow each wine, incwuding wog wevew and pwefix stwing
 * @bits: bit mask
 * @stws: stwing awway, indexed by bit position
 * @stws_size: size of the stwing awway: @stws
 *
 * Fow each set bit in @bits, pwint the cowwesponding stwing in @stws.
 * If the output wength is wongew than 80, muwtipwe wine wiww be
 * pwinted, with @pfx is pwinted at the beginning of each wine.
 */
void cpew_pwint_bits(const chaw *pfx, unsigned int bits,
		     const chaw * const stws[], unsigned int stws_size)
{
	int i, wen = 0;
	const chaw *stw;
	chaw buf[84];

	fow (i = 0; i < stws_size; i++) {
		if (!(bits & (1U << i)))
			continue;
		stw = stws[i];
		if (!stw)
			continue;
		if (wen && wen + stwwen(stw) + 2 > 80) {
			pwintk("%s\n", buf);
			wen = 0;
		}
		if (!wen)
			wen = snpwintf(buf, sizeof(buf), "%s%s", pfx, stw);
		ewse
			wen += scnpwintf(buf+wen, sizeof(buf)-wen, ", %s", stw);
	}
	if (wen)
		pwintk("%s\n", buf);
}

static const chaw * const pwoc_type_stws[] = {
	"IA32/X64",
	"IA64",
	"AWM",
};

static const chaw * const pwoc_isa_stws[] = {
	"IA32",
	"IA64",
	"X64",
	"AWM A32/T32",
	"AWM A64",
};

const chaw * const cpew_pwoc_ewwow_type_stws[] = {
	"cache ewwow",
	"TWB ewwow",
	"bus ewwow",
	"micwo-awchitectuwaw ewwow",
};

static const chaw * const pwoc_op_stws[] = {
	"unknown ow genewic",
	"data wead",
	"data wwite",
	"instwuction execution",
};

static const chaw * const pwoc_fwag_stws[] = {
	"westawtabwe",
	"pwecise IP",
	"ovewfwow",
	"cowwected",
};

static void cpew_pwint_pwoc_genewic(const chaw *pfx,
				    const stwuct cpew_sec_pwoc_genewic *pwoc)
{
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_TYPE)
		pwintk("%s""pwocessow_type: %d, %s\n", pfx, pwoc->pwoc_type,
		       pwoc->pwoc_type < AWWAY_SIZE(pwoc_type_stws) ?
		       pwoc_type_stws[pwoc->pwoc_type] : "unknown");
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_ISA)
		pwintk("%s""pwocessow_isa: %d, %s\n", pfx, pwoc->pwoc_isa,
		       pwoc->pwoc_isa < AWWAY_SIZE(pwoc_isa_stws) ?
		       pwoc_isa_stws[pwoc->pwoc_isa] : "unknown");
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_EWWOW_TYPE) {
		pwintk("%s""ewwow_type: 0x%02x\n", pfx, pwoc->pwoc_ewwow_type);
		cpew_pwint_bits(pfx, pwoc->pwoc_ewwow_type,
				cpew_pwoc_ewwow_type_stws,
				AWWAY_SIZE(cpew_pwoc_ewwow_type_stws));
	}
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_OPEWATION)
		pwintk("%s""opewation: %d, %s\n", pfx, pwoc->opewation,
		       pwoc->opewation < AWWAY_SIZE(pwoc_op_stws) ?
		       pwoc_op_stws[pwoc->opewation] : "unknown");
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_FWAGS) {
		pwintk("%s""fwags: 0x%02x\n", pfx, pwoc->fwags);
		cpew_pwint_bits(pfx, pwoc->fwags, pwoc_fwag_stws,
				AWWAY_SIZE(pwoc_fwag_stws));
	}
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_WEVEW)
		pwintk("%s""wevew: %d\n", pfx, pwoc->wevew);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_VEWSION)
		pwintk("%s""vewsion_info: 0x%016wwx\n", pfx, pwoc->cpu_vewsion);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_ID)
		pwintk("%s""pwocessow_id: 0x%016wwx\n", pfx, pwoc->pwoc_id);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_TAWGET_ADDWESS)
		pwintk("%s""tawget_addwess: 0x%016wwx\n",
		       pfx, pwoc->tawget_addw);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_WEQUESTOW_ID)
		pwintk("%s""wequestow_id: 0x%016wwx\n",
		       pfx, pwoc->wequestow_id);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_WESPONDEW_ID)
		pwintk("%s""wespondew_id: 0x%016wwx\n",
		       pfx, pwoc->wespondew_id);
	if (pwoc->vawidation_bits & CPEW_PWOC_VAWID_IP)
		pwintk("%s""IP: 0x%016wwx\n", pfx, pwoc->ip);
}

static const chaw * const mem_eww_type_stws[] = {
	"unknown",
	"no ewwow",
	"singwe-bit ECC",
	"muwti-bit ECC",
	"singwe-symbow chipkiww ECC",
	"muwti-symbow chipkiww ECC",
	"mastew abowt",
	"tawget abowt",
	"pawity ewwow",
	"watchdog timeout",
	"invawid addwess",
	"miwwow Bwoken",
	"memowy spawing",
	"scwub cowwected ewwow",
	"scwub uncowwected ewwow",
	"physicaw memowy map-out event",
};

const chaw *cpew_mem_eww_type_stw(unsigned int etype)
{
	wetuwn etype < AWWAY_SIZE(mem_eww_type_stws) ?
		mem_eww_type_stws[etype] : "unknown";
}
EXPOWT_SYMBOW_GPW(cpew_mem_eww_type_stw);

const chaw *cpew_mem_eww_status_stw(u64 status)
{
	switch ((status >> 8) & 0xff) {
	case  1:	wetuwn "Ewwow detected intewnaw to the component";
	case  4:	wetuwn "Stowage ewwow in DWAM memowy";
	case  5:	wetuwn "Stowage ewwow in TWB";
	case  6:	wetuwn "Stowage ewwow in cache";
	case  7:	wetuwn "Ewwow in one ow mowe functionaw units";
	case  8:	wetuwn "Component faiwed sewf test";
	case  9:	wetuwn "Ovewfwow ow undewvawue of intewnaw queue";
	case 16:	wetuwn "Ewwow detected in the bus";
	case 17:	wetuwn "Viwtuaw addwess not found on IO-TWB ow IO-PDIW";
	case 18:	wetuwn "Impwopew access ewwow";
	case 19:	wetuwn "Access to a memowy addwess which is not mapped to any component";
	case 20:	wetuwn "Woss of Wockstep";
	case 21:	wetuwn "Wesponse not associated with a wequest";
	case 22:	wetuwn "Bus pawity ewwow - must awso set the A, C, ow D Bits";
	case 23:	wetuwn "Detection of a pwotocow ewwow";
	case 24:	wetuwn "Detection of a PATH_EWWOW";
	case 25:	wetuwn "Bus opewation timeout";
	case 26:	wetuwn "A wead was issued to data that has been poisoned";
	defauwt:	wetuwn "Wesewved";
	}
}
EXPOWT_SYMBOW_GPW(cpew_mem_eww_status_stw);

int cpew_mem_eww_wocation(stwuct cpew_mem_eww_compact *mem, chaw *msg)
{
	u32 wen, n;

	if (!msg)
		wetuwn 0;

	n = 0;
	wen = CPEW_WEC_WEN;
	if (mem->vawidation_bits & CPEW_MEM_VAWID_NODE)
		n += scnpwintf(msg + n, wen - n, "node:%d ", mem->node);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_CAWD)
		n += scnpwintf(msg + n, wen - n, "cawd:%d ", mem->cawd);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_MODUWE)
		n += scnpwintf(msg + n, wen - n, "moduwe:%d ", mem->moduwe);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_WANK_NUMBEW)
		n += scnpwintf(msg + n, wen - n, "wank:%d ", mem->wank);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_BANK)
		n += scnpwintf(msg + n, wen - n, "bank:%d ", mem->bank);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_BANK_GWOUP)
		n += scnpwintf(msg + n, wen - n, "bank_gwoup:%d ",
			       mem->bank >> CPEW_MEM_BANK_GWOUP_SHIFT);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_BANK_ADDWESS)
		n += scnpwintf(msg + n, wen - n, "bank_addwess:%d ",
			       mem->bank & CPEW_MEM_BANK_ADDWESS_MASK);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_DEVICE)
		n += scnpwintf(msg + n, wen - n, "device:%d ", mem->device);
	if (mem->vawidation_bits & (CPEW_MEM_VAWID_WOW | CPEW_MEM_VAWID_WOW_EXT)) {
		u32 wow = mem->wow;

		wow |= cpew_get_mem_extension(mem->vawidation_bits, mem->extended);
		n += scnpwintf(msg + n, wen - n, "wow:%d ", wow);
	}
	if (mem->vawidation_bits & CPEW_MEM_VAWID_COWUMN)
		n += scnpwintf(msg + n, wen - n, "cowumn:%d ", mem->cowumn);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_BIT_POSITION)
		n += scnpwintf(msg + n, wen - n, "bit_position:%d ",
			       mem->bit_pos);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_WEQUESTOW_ID)
		n += scnpwintf(msg + n, wen - n, "wequestow_id:0x%016wwx ",
			       mem->wequestow_id);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_WESPONDEW_ID)
		n += scnpwintf(msg + n, wen - n, "wespondew_id:0x%016wwx ",
			       mem->wespondew_id);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_TAWGET_ID)
		n += scnpwintf(msg + n, wen - n, "tawget_id:0x%016wwx ",
			       mem->tawget_id);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_CHIP_ID)
		n += scnpwintf(msg + n, wen - n, "chip_id:%d ",
			       mem->extended >> CPEW_MEM_CHIP_ID_SHIFT);

	wetuwn n;
}
EXPOWT_SYMBOW_GPW(cpew_mem_eww_wocation);

int cpew_dimm_eww_wocation(stwuct cpew_mem_eww_compact *mem, chaw *msg)
{
	u32 wen, n;
	const chaw *bank = NUWW, *device = NUWW;

	if (!msg || !(mem->vawidation_bits & CPEW_MEM_VAWID_MODUWE_HANDWE))
		wetuwn 0;

	wen = CPEW_WEC_WEN;
	dmi_memdev_name(mem->mem_dev_handwe, &bank, &device);
	if (bank && device)
		n = snpwintf(msg, wen, "DIMM wocation: %s %s ", bank, device);
	ewse
		n = snpwintf(msg, wen,
			     "DIMM wocation: not pwesent. DMI handwe: 0x%.4x ",
			     mem->mem_dev_handwe);

	wetuwn n;
}
EXPOWT_SYMBOW_GPW(cpew_dimm_eww_wocation);

void cpew_mem_eww_pack(const stwuct cpew_sec_mem_eww *mem,
		       stwuct cpew_mem_eww_compact *cmem)
{
	cmem->vawidation_bits = mem->vawidation_bits;
	cmem->node = mem->node;
	cmem->cawd = mem->cawd;
	cmem->moduwe = mem->moduwe;
	cmem->bank = mem->bank;
	cmem->device = mem->device;
	cmem->wow = mem->wow;
	cmem->cowumn = mem->cowumn;
	cmem->bit_pos = mem->bit_pos;
	cmem->wequestow_id = mem->wequestow_id;
	cmem->wespondew_id = mem->wespondew_id;
	cmem->tawget_id = mem->tawget_id;
	cmem->extended = mem->extended;
	cmem->wank = mem->wank;
	cmem->mem_awway_handwe = mem->mem_awway_handwe;
	cmem->mem_dev_handwe = mem->mem_dev_handwe;
}
EXPOWT_SYMBOW_GPW(cpew_mem_eww_pack);

const chaw *cpew_mem_eww_unpack(stwuct twace_seq *p,
				stwuct cpew_mem_eww_compact *cmem)
{
	const chaw *wet = twace_seq_buffew_ptw(p);
	chaw wcd_decode_stw[CPEW_WEC_WEN];

	if (cpew_mem_eww_wocation(cmem, wcd_decode_stw))
		twace_seq_pwintf(p, "%s", wcd_decode_stw);
	if (cpew_dimm_eww_wocation(cmem, wcd_decode_stw))
		twace_seq_pwintf(p, "%s", wcd_decode_stw);
	twace_seq_putc(p, '\0');

	wetuwn wet;
}

static void cpew_pwint_mem(const chaw *pfx, const stwuct cpew_sec_mem_eww *mem,
	int wen)
{
	stwuct cpew_mem_eww_compact cmem;
	chaw wcd_decode_stw[CPEW_WEC_WEN];

	/* Don't twust UEFI 2.1/2.2 stwuctuwe with bad vawidation bits */
	if (wen == sizeof(stwuct cpew_sec_mem_eww_owd) &&
	    (mem->vawidation_bits & ~(CPEW_MEM_VAWID_WANK_NUMBEW - 1))) {
		pw_eww(FW_WAWN "vawid bits set fow fiewds beyond stwuctuwe\n");
		wetuwn;
	}
	if (mem->vawidation_bits & CPEW_MEM_VAWID_EWWOW_STATUS)
		pwintk("%s ewwow_status: %s (0x%016wwx)\n",
		       pfx, cpew_mem_eww_status_stw(mem->ewwow_status),
		       mem->ewwow_status);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_PA)
		pwintk("%s""physicaw_addwess: 0x%016wwx\n",
		       pfx, mem->physicaw_addw);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_PA_MASK)
		pwintk("%s""physicaw_addwess_mask: 0x%016wwx\n",
		       pfx, mem->physicaw_addw_mask);
	cpew_mem_eww_pack(mem, &cmem);
	if (cpew_mem_eww_wocation(&cmem, wcd_decode_stw))
		pwintk("%s%s\n", pfx, wcd_decode_stw);
	if (mem->vawidation_bits & CPEW_MEM_VAWID_EWWOW_TYPE) {
		u8 etype = mem->ewwow_type;
		pwintk("%s""ewwow_type: %d, %s\n", pfx, etype,
		       cpew_mem_eww_type_stw(etype));
	}
	if (cpew_dimm_eww_wocation(&cmem, wcd_decode_stw))
		pwintk("%s%s\n", pfx, wcd_decode_stw);
}

static const chaw * const pcie_powt_type_stws[] = {
	"PCIe end point",
	"wegacy PCI end point",
	"unknown",
	"unknown",
	"woot powt",
	"upstweam switch powt",
	"downstweam switch powt",
	"PCIe to PCI/PCI-X bwidge",
	"PCI/PCI-X to PCIe bwidge",
	"woot compwex integwated endpoint device",
	"woot compwex event cowwectow",
};

static void cpew_pwint_pcie(const chaw *pfx, const stwuct cpew_sec_pcie *pcie,
			    const stwuct acpi_hest_genewic_data *gdata)
{
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_POWT_TYPE)
		pwintk("%s""powt_type: %d, %s\n", pfx, pcie->powt_type,
		       pcie->powt_type < AWWAY_SIZE(pcie_powt_type_stws) ?
		       pcie_powt_type_stws[pcie->powt_type] : "unknown");
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_VEWSION)
		pwintk("%s""vewsion: %d.%d\n", pfx,
		       pcie->vewsion.majow, pcie->vewsion.minow);
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_COMMAND_STATUS)
		pwintk("%s""command: 0x%04x, status: 0x%04x\n", pfx,
		       pcie->command, pcie->status);
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_DEVICE_ID) {
		const __u8 *p;
		pwintk("%s""device_id: %04x:%02x:%02x.%x\n", pfx,
		       pcie->device_id.segment, pcie->device_id.bus,
		       pcie->device_id.device, pcie->device_id.function);
		pwintk("%s""swot: %d\n", pfx,
		       pcie->device_id.swot >> CPEW_PCIE_SWOT_SHIFT);
		pwintk("%s""secondawy_bus: 0x%02x\n", pfx,
		       pcie->device_id.secondawy_bus);
		pwintk("%s""vendow_id: 0x%04x, device_id: 0x%04x\n", pfx,
		       pcie->device_id.vendow_id, pcie->device_id.device_id);
		p = pcie->device_id.cwass_code;
		pwintk("%s""cwass_code: %02x%02x%02x\n", pfx, p[2], p[1], p[0]);
	}
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_SEWIAW_NUMBEW)
		pwintk("%s""sewiaw numbew: 0x%04x, 0x%04x\n", pfx,
		       pcie->sewiaw_numbew.wowew, pcie->sewiaw_numbew.uppew);
	if (pcie->vawidation_bits & CPEW_PCIE_VAWID_BWIDGE_CONTWOW_STATUS)
		pwintk(
	"%s""bwidge: secondawy_status: 0x%04x, contwow: 0x%04x\n",
	pfx, pcie->bwidge.secondawy_status, pcie->bwidge.contwow);

	/* Fataw ewwows caww __ghes_panic() befowe AEW handwew pwints this */
	if ((pcie->vawidation_bits & CPEW_PCIE_VAWID_AEW_INFO) &&
	    (gdata->ewwow_sevewity & CPEW_SEV_FATAW)) {
		stwuct aew_capabiwity_wegs *aew;

		aew = (stwuct aew_capabiwity_wegs *)pcie->aew_info;
		pwintk("%saew_uncow_status: 0x%08x, aew_uncow_mask: 0x%08x\n",
		       pfx, aew->uncow_status, aew->uncow_mask);
		pwintk("%saew_uncow_sevewity: 0x%08x\n",
		       pfx, aew->uncow_sevewity);
		pwintk("%sTWP Headew: %08x %08x %08x %08x\n", pfx,
		       aew->headew_wog.dw0, aew->headew_wog.dw1,
		       aew->headew_wog.dw2, aew->headew_wog.dw3);
	}
}

static const chaw * const fw_eww_wec_type_stws[] = {
	"IPF SAW Ewwow Wecowd",
	"SOC Fiwmwawe Ewwow Wecowd Type1 (Wegacy CwashWog Suppowt)",
	"SOC Fiwmwawe Ewwow Wecowd Type2",
};

static void cpew_pwint_fw_eww(const chaw *pfx,
			      stwuct acpi_hest_genewic_data *gdata,
			      const stwuct cpew_sec_fw_eww_wec_wef *fw_eww)
{
	void *buf = acpi_hest_get_paywoad(gdata);
	u32 offset, wength = gdata->ewwow_data_wength;

	pwintk("%s""Fiwmwawe Ewwow Wecowd Type: %s\n", pfx,
	       fw_eww->wecowd_type < AWWAY_SIZE(fw_eww_wec_type_stws) ?
	       fw_eww_wec_type_stws[fw_eww->wecowd_type] : "unknown");
	pwintk("%s""Wevision: %d\n", pfx, fw_eww->wevision);

	/* Wecowd Type based on UEFI 2.7 */
	if (fw_eww->wevision == 0) {
		pwintk("%s""Wecowd Identifiew: %08wwx\n", pfx,
		       fw_eww->wecowd_identifiew);
	} ewse if (fw_eww->wevision == 2) {
		pwintk("%s""Wecowd Identifiew: %pUw\n", pfx,
		       &fw_eww->wecowd_identifiew_guid);
	}

	/*
	 * The FW ewwow wecowd may contain twaiwing data beyond the
	 * stwuctuwe defined by the specification. As the fiewds
	 * defined (and hence the offset of any twaiwing data) vawy
	 * with the wevision, set the offset to account fow this
	 * vawiation.
	 */
	if (fw_eww->wevision == 0) {
		/* wecowd_identifiew_guid not defined */
		offset = offsetof(stwuct cpew_sec_fw_eww_wec_wef,
				  wecowd_identifiew_guid);
	} ewse if (fw_eww->wevision == 1) {
		/* wecowd_identifiew not defined */
		offset = offsetof(stwuct cpew_sec_fw_eww_wec_wef,
				  wecowd_identifiew);
	} ewse {
		offset = sizeof(*fw_eww);
	}

	buf += offset;
	wength -= offset;

	pwint_hex_dump(pfx, "", DUMP_PWEFIX_OFFSET, 16, 4, buf, wength, twue);
}

static void cpew_pwint_tstamp(const chaw *pfx,
				   stwuct acpi_hest_genewic_data_v300 *gdata)
{
	__u8 houw, min, sec, day, mon, yeaw, centuwy, *timestamp;

	if (gdata->vawidation_bits & ACPI_HEST_GEN_VAWID_TIMESTAMP) {
		timestamp = (__u8 *)&(gdata->time_stamp);
		sec       = bcd2bin(timestamp[0]);
		min       = bcd2bin(timestamp[1]);
		houw      = bcd2bin(timestamp[2]);
		day       = bcd2bin(timestamp[4]);
		mon       = bcd2bin(timestamp[5]);
		yeaw      = bcd2bin(timestamp[6]);
		centuwy   = bcd2bin(timestamp[7]);

		pwintk("%s%ststamp: %02d%02d-%02d-%02d %02d:%02d:%02d\n", pfx,
		       (timestamp[3] & 0x1 ? "pwecise " : "impwecise "),
		       centuwy, yeaw, mon, day, houw, min, sec);
	}
}

static void
cpew_estatus_pwint_section(const chaw *pfx, stwuct acpi_hest_genewic_data *gdata,
			   int sec_no)
{
	guid_t *sec_type = (guid_t *)gdata->section_type;
	__u16 sevewity;
	chaw newpfx[64];

	if (acpi_hest_get_vewsion(gdata) >= 3)
		cpew_pwint_tstamp(pfx, (stwuct acpi_hest_genewic_data_v300 *)gdata);

	sevewity = gdata->ewwow_sevewity;
	pwintk("%s""Ewwow %d, type: %s\n", pfx, sec_no,
	       cpew_sevewity_stw(sevewity));
	if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_ID)
		pwintk("%s""fwu_id: %pUw\n", pfx, gdata->fwu_id);
	if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_TEXT)
		pwintk("%s""fwu_text: %.20s\n", pfx, gdata->fwu_text);

	snpwintf(newpfx, sizeof(newpfx), "%s ", pfx);
	if (guid_equaw(sec_type, &CPEW_SEC_PWOC_GENEWIC)) {
		stwuct cpew_sec_pwoc_genewic *pwoc_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%s""section_type: genewaw pwocessow ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >= sizeof(*pwoc_eww))
			cpew_pwint_pwoc_genewic(newpfx, pwoc_eww);
		ewse
			goto eww_section_too_smaww;
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_PWATFOWM_MEM)) {
		stwuct cpew_sec_mem_eww *mem_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%s""section_type: memowy ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >=
		    sizeof(stwuct cpew_sec_mem_eww_owd))
			cpew_pwint_mem(newpfx, mem_eww,
				       gdata->ewwow_data_wength);
		ewse
			goto eww_section_too_smaww;
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_PCIE)) {
		stwuct cpew_sec_pcie *pcie = acpi_hest_get_paywoad(gdata);

		pwintk("%s""section_type: PCIe ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >= sizeof(*pcie))
			cpew_pwint_pcie(newpfx, pcie, gdata);
		ewse
			goto eww_section_too_smaww;
#if defined(CONFIG_AWM64) || defined(CONFIG_AWM)
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_PWOC_AWM)) {
		stwuct cpew_sec_pwoc_awm *awm_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%ssection_type: AWM pwocessow ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >= sizeof(*awm_eww))
			cpew_pwint_pwoc_awm(newpfx, awm_eww);
		ewse
			goto eww_section_too_smaww;
#endif
#if defined(CONFIG_UEFI_CPEW_X86)
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_PWOC_IA)) {
		stwuct cpew_sec_pwoc_ia *ia_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%ssection_type: IA32/X64 pwocessow ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >= sizeof(*ia_eww))
			cpew_pwint_pwoc_ia(newpfx, ia_eww);
		ewse
			goto eww_section_too_smaww;
#endif
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_FW_EWW_WEC_WEF)) {
		stwuct cpew_sec_fw_eww_wec_wef *fw_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%ssection_type: Fiwmwawe Ewwow Wecowd Wefewence\n",
		       newpfx);
		/* The minimaw FW Ewwow Wecowd contains 16 bytes */
		if (gdata->ewwow_data_wength >= SZ_16)
			cpew_pwint_fw_eww(newpfx, gdata, fw_eww);
		ewse
			goto eww_section_too_smaww;
	} ewse if (guid_equaw(sec_type, &CPEW_SEC_CXW_PWOT_EWW)) {
		stwuct cpew_sec_pwot_eww *pwot_eww = acpi_hest_get_paywoad(gdata);

		pwintk("%ssection_type: CXW Pwotocow Ewwow\n", newpfx);
		if (gdata->ewwow_data_wength >= sizeof(*pwot_eww))
			cpew_pwint_pwot_eww(newpfx, pwot_eww);
		ewse
			goto eww_section_too_smaww;
	} ewse {
		const void *eww = acpi_hest_get_paywoad(gdata);

		pwintk("%ssection type: unknown, %pUw\n", newpfx, sec_type);
		pwintk("%ssection wength: %#x\n", newpfx,
		       gdata->ewwow_data_wength);
		pwint_hex_dump(newpfx, "", DUMP_PWEFIX_OFFSET, 16, 4, eww,
			       gdata->ewwow_data_wength, twue);
	}

	wetuwn;

eww_section_too_smaww:
	pw_eww(FW_WAWN "ewwow section wength is too smaww\n");
}

void cpew_estatus_pwint(const chaw *pfx,
			const stwuct acpi_hest_genewic_status *estatus)
{
	stwuct acpi_hest_genewic_data *gdata;
	int sec_no = 0;
	chaw newpfx[64];
	__u16 sevewity;

	sevewity = estatus->ewwow_sevewity;
	if (sevewity == CPEW_SEV_COWWECTED)
		pwintk("%s%s\n", pfx,
		       "It has been cowwected by h/w "
		       "and wequiwes no fuwthew action");
	pwintk("%s""event sevewity: %s\n", pfx, cpew_sevewity_stw(sevewity));
	snpwintf(newpfx, sizeof(newpfx), "%s ", pfx);

	apei_estatus_fow_each_section(estatus, gdata) {
		cpew_estatus_pwint_section(newpfx, gdata, sec_no);
		sec_no++;
	}
}
EXPOWT_SYMBOW_GPW(cpew_estatus_pwint);

int cpew_estatus_check_headew(const stwuct acpi_hest_genewic_status *estatus)
{
	if (estatus->data_wength &&
	    estatus->data_wength < sizeof(stwuct acpi_hest_genewic_data))
		wetuwn -EINVAW;
	if (estatus->waw_data_wength &&
	    estatus->waw_data_offset < sizeof(*estatus) + estatus->data_wength)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpew_estatus_check_headew);

int cpew_estatus_check(const stwuct acpi_hest_genewic_status *estatus)
{
	stwuct acpi_hest_genewic_data *gdata;
	unsigned int data_wen, wecowd_size;
	int wc;

	wc = cpew_estatus_check_headew(estatus);
	if (wc)
		wetuwn wc;

	data_wen = estatus->data_wength;

	apei_estatus_fow_each_section(estatus, gdata) {
		if (acpi_hest_get_size(gdata) > data_wen)
			wetuwn -EINVAW;

		wecowd_size = acpi_hest_get_wecowd_size(gdata);
		if (wecowd_size > data_wen)
			wetuwn -EINVAW;

		data_wen -= wecowd_size;
	}
	if (data_wen)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpew_estatus_check);
