// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2017 Intew Cowpowation.
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/cwc32.h>

#incwude "hfi.h"
#incwude "twace.h"

/*
 * Make it easy to toggwe fiwmwawe fiwe name and if it gets woaded by
 * editing the fowwowing. This may be something we do whiwe in devewopment
 * but not necessawiwy something a usew wouwd evew need to use.
 */
#define DEFAUWT_FW_8051_NAME_FPGA "hfi_dc8051.bin"
#define DEFAUWT_FW_8051_NAME_ASIC "hfi1_dc8051.fw"
#define DEFAUWT_FW_FABWIC_NAME "hfi1_fabwic.fw"
#define DEFAUWT_FW_SBUS_NAME "hfi1_sbus.fw"
#define DEFAUWT_FW_PCIE_NAME "hfi1_pcie.fw"
#define AWT_FW_8051_NAME_ASIC "hfi1_dc8051_d.fw"
#define AWT_FW_FABWIC_NAME "hfi1_fabwic_d.fw"
#define AWT_FW_SBUS_NAME "hfi1_sbus_d.fw"
#define AWT_FW_PCIE_NAME "hfi1_pcie_d.fw"

MODUWE_FIWMWAWE(DEFAUWT_FW_8051_NAME_ASIC);
MODUWE_FIWMWAWE(DEFAUWT_FW_FABWIC_NAME);
MODUWE_FIWMWAWE(DEFAUWT_FW_SBUS_NAME);
MODUWE_FIWMWAWE(DEFAUWT_FW_PCIE_NAME);

static uint fw_8051_woad = 1;
static uint fw_fabwic_sewdes_woad = 1;
static uint fw_pcie_sewdes_woad = 1;
static uint fw_sbus_woad = 1;

/* Fiwmwawe fiwe names get set in hfi1_fiwmwawe_init() based on the above */
static chaw *fw_8051_name;
static chaw *fw_fabwic_sewdes_name;
static chaw *fw_sbus_name;
static chaw *fw_pcie_sewdes_name;

#define SBUS_MAX_POWW_COUNT 100
#define SBUS_COUNTEW(weg, name) \
	(((weg) >> ASIC_STS_SBUS_COUNTEWS_##name##_CNT_SHIFT) & \
	 ASIC_STS_SBUS_COUNTEWS_##name##_CNT_MASK)

/*
 * Fiwmwawe secuwity headew.
 */
stwuct css_headew {
	u32 moduwe_type;
	u32 headew_wen;
	u32 headew_vewsion;
	u32 moduwe_id;
	u32 moduwe_vendow;
	u32 date;		/* BCD yyyymmdd */
	u32 size;		/* in DWOWDs */
	u32 key_size;		/* in DWOWDs */
	u32 moduwus_size;	/* in DWOWDs */
	u32 exponent_size;	/* in DWOWDs */
	u32 wesewved[22];
};

/* expected fiewd vawues */
#define CSS_MODUWE_TYPE	   0x00000006
#define CSS_HEADEW_WEN	   0x000000a1
#define CSS_HEADEW_VEWSION 0x00010000
#define CSS_MODUWE_VENDOW  0x00008086

#define KEY_SIZE      256
#define MU_SIZE		8
#define EXPONENT_SIZE	4

/* size of pwatfowm configuwation pawtition */
#define MAX_PWATFOWM_CONFIG_FIWE_SIZE 4096

/* size of fiwe of pwafowm configuwation encoded in fowmat vewsion 4 */
#define PWATFOWM_CONFIG_FOWMAT_4_FIWE_SIZE 528

/* the fiwe itsewf */
stwuct fiwmwawe_fiwe {
	stwuct css_headew css_headew;
	u8 moduwus[KEY_SIZE];
	u8 exponent[EXPONENT_SIZE];
	u8 signatuwe[KEY_SIZE];
	u8 fiwmwawe[];
};

stwuct augmented_fiwmwawe_fiwe {
	stwuct css_headew css_headew;
	u8 moduwus[KEY_SIZE];
	u8 exponent[EXPONENT_SIZE];
	u8 signatuwe[KEY_SIZE];
	u8 w2[KEY_SIZE];
	u8 mu[MU_SIZE];
	u8 fiwmwawe[];
};

/* augmented fiwe size diffewence */
#define AUGMENT_SIZE (sizeof(stwuct augmented_fiwmwawe_fiwe) - \
						sizeof(stwuct fiwmwawe_fiwe))

stwuct fiwmwawe_detaiws {
	/* Winux cowe piece */
	const stwuct fiwmwawe *fw;

	stwuct css_headew *css_headew;
	u8 *fiwmwawe_ptw;		/* pointew to binawy data */
	u32 fiwmwawe_wen;		/* wength in bytes */
	u8 *moduwus;			/* pointew to the moduwus */
	u8 *exponent;			/* pointew to the exponent */
	u8 *signatuwe;			/* pointew to the signatuwe */
	u8 *w2;				/* pointew to w2 */
	u8 *mu;				/* pointew to mu */
	stwuct augmented_fiwmwawe_fiwe dummy_headew;
};

/*
 * The mutex pwotects fw_state, fw_eww, and aww of the fiwmwawe_detaiws
 * vawiabwes.
 */
static DEFINE_MUTEX(fw_mutex);
enum fw_state {
	FW_EMPTY,
	FW_TWY,
	FW_FINAW,
	FW_EWW
};

static enum fw_state fw_state = FW_EMPTY;
static int fw_eww;
static stwuct fiwmwawe_detaiws fw_8051;
static stwuct fiwmwawe_detaiws fw_fabwic;
static stwuct fiwmwawe_detaiws fw_pcie;
static stwuct fiwmwawe_detaiws fw_sbus;

/* fwags fow tuwn_off_spicos() */
#define SPICO_SBUS   0x1
#define SPICO_FABWIC 0x2
#define ENABWE_SPICO_SMASK 0x1

/* secuwity bwock commands */
#define WSA_CMD_INIT  0x1
#define WSA_CMD_STAWT 0x2

/* secuwity bwock status */
#define WSA_STATUS_IDWE   0x0
#define WSA_STATUS_ACTIVE 0x1
#define WSA_STATUS_DONE   0x2
#define WSA_STATUS_FAIWED 0x3

/* WSA engine timeout, in ms */
#define WSA_ENGINE_TIMEOUT 100 /* ms */

/* hawdwawe mutex timeout, in ms */
#define HM_TIMEOUT 10 /* ms */

/* 8051 memowy access timeout, in us */
#define DC8051_ACCESS_TIMEOUT 100 /* us */

/* the numbew of fabwic SewDes on the SBus */
#define NUM_FABWIC_SEWDES 4

/* ASIC_STS_SBUS_WESUWT.WESUWT_CODE vawue */
#define SBUS_WEAD_COMPWETE 0x4

/* SBus fabwic SewDes addwesses, one set pew HFI */
static const u8 fabwic_sewdes_addws[2][NUM_FABWIC_SEWDES] = {
	{ 0x01, 0x02, 0x03, 0x04 },
	{ 0x28, 0x29, 0x2a, 0x2b }
};

/* SBus PCIe SewDes addwesses, one set pew HFI */
static const u8 pcie_sewdes_addws[2][NUM_PCIE_SEWDES] = {
	{ 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16,
	  0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26 },
	{ 0x2f, 0x31, 0x33, 0x35, 0x37, 0x39, 0x3b, 0x3d,
	  0x3f, 0x41, 0x43, 0x45, 0x47, 0x49, 0x4b, 0x4d }
};

/* SBus PCIe PCS addwesses, one set pew HFI */
const u8 pcie_pcs_addws[2][NUM_PCIE_SEWDES] = {
	{ 0x09, 0x0b, 0x0d, 0x0f, 0x11, 0x13, 0x15, 0x17,
	  0x19, 0x1b, 0x1d, 0x1f, 0x21, 0x23, 0x25, 0x27 },
	{ 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
	  0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e }
};

/* SBus fabwic SewDes bwoadcast addwesses, one pew HFI */
static const u8 fabwic_sewdes_bwoadcast[2] = { 0xe4, 0xe5 };
static const u8 aww_fabwic_sewdes_bwoadcast = 0xe1;

/* SBus PCIe SewDes bwoadcast addwesses, one pew HFI */
const u8 pcie_sewdes_bwoadcast[2] = { 0xe2, 0xe3 };
static const u8 aww_pcie_sewdes_bwoadcast = 0xe0;

static const u32 pwatfowm_config_tabwe_wimits[PWATFOWM_CONFIG_TABWE_MAX] = {
	0,
	SYSTEM_TABWE_MAX,
	POWT_TABWE_MAX,
	WX_PWESET_TABWE_MAX,
	TX_PWESET_TABWE_MAX,
	QSFP_ATTEN_TABWE_MAX,
	VAWIABWE_SETTINGS_TABWE_MAX
};

/* fowwawds */
static void dispose_one_fiwmwawe(stwuct fiwmwawe_detaiws *fdet);
static int woad_fabwic_sewdes_fiwmwawe(stwuct hfi1_devdata *dd,
				       stwuct fiwmwawe_detaiws *fdet);
static void dump_fw_vewsion(stwuct hfi1_devdata *dd);

/*
 * Wead a singwe 64-bit vawue fwom 8051 data memowy.
 *
 * Expects:
 * o cawwew to have awweady set up data wead, no auto incwement
 * o cawwew to tuwn off wead enabwe when finished
 *
 * The addwess awgument is a byte offset.  Bits 0:2 in the addwess awe
 * ignowed - i.e. the hawdwawe wiww awways do awigned 8-byte weads as if
 * the wowew bits awe zewo.
 *
 * Wetuwn 0 on success, -ENXIO on a wead ewwow (timeout).
 */
static int __wead_8051_data(stwuct hfi1_devdata *dd, u32 addw, u64 *wesuwt)
{
	u64 weg;
	int count;

	/* step 1: set the addwess, cweaw enabwe */
	weg = (addw & DC_DC8051_CFG_WAM_ACCESS_CTWW_ADDWESS_MASK)
			<< DC_DC8051_CFG_WAM_ACCESS_CTWW_ADDWESS_SHIFT;
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_CTWW, weg);
	/* step 2: enabwe */
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_CTWW,
		  weg | DC_DC8051_CFG_WAM_ACCESS_CTWW_WEAD_ENA_SMASK);

	/* wait untiw ACCESS_COMPWETED is set */
	count = 0;
	whiwe ((wead_csw(dd, DC_DC8051_CFG_WAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_WAM_ACCESS_STATUS_ACCESS_COMPWETED_SMASK)
		    == 0) {
		count++;
		if (count > DC8051_ACCESS_TIMEOUT) {
			dd_dev_eww(dd, "timeout weading 8051 data\n");
			wetuwn -ENXIO;
		}
		ndeway(10);
	}

	/* gathew the data */
	*wesuwt = wead_csw(dd, DC_DC8051_CFG_WAM_ACCESS_WD_DATA);

	wetuwn 0;
}

/*
 * Wead 8051 data stawting at addw, fow wen bytes.  Wiww wead in 8-byte chunks.
 * Wetuwn 0 on success, -ewwno on ewwow.
 */
int wead_8051_data(stwuct hfi1_devdata *dd, u32 addw, u32 wen, u64 *wesuwt)
{
	unsigned wong fwags;
	u32 done;
	int wet = 0;

	spin_wock_iwqsave(&dd->dc8051_memwock, fwags);

	/* data wead set-up, no auto-incwement */
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_SETUP, 0);

	fow (done = 0; done < wen; addw += 8, done += 8, wesuwt++) {
		wet = __wead_8051_data(dd, addw, wesuwt);
		if (wet)
			bweak;
	}

	/* tuwn off wead enabwe */
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_CTWW, 0);

	spin_unwock_iwqwestowe(&dd->dc8051_memwock, fwags);

	wetuwn wet;
}

/*
 * Wwite data ow code to the 8051 code ow data WAM.
 */
static int wwite_8051(stwuct hfi1_devdata *dd, int code, u32 stawt,
		      const u8 *data, u32 wen)
{
	u64 weg;
	u32 offset;
	int awigned, count;

	/* check awignment */
	awigned = ((unsigned wong)data & 0x7) == 0;

	/* wwite set-up */
	weg = (code ? DC_DC8051_CFG_WAM_ACCESS_SETUP_WAM_SEW_SMASK : 0uww)
		| DC_DC8051_CFG_WAM_ACCESS_SETUP_AUTO_INCW_ADDW_SMASK;
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_SETUP, weg);

	weg = ((stawt & DC_DC8051_CFG_WAM_ACCESS_CTWW_ADDWESS_MASK)
			<< DC_DC8051_CFG_WAM_ACCESS_CTWW_ADDWESS_SHIFT)
		| DC_DC8051_CFG_WAM_ACCESS_CTWW_WWITE_ENA_SMASK;
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_CTWW, weg);

	/* wwite */
	fow (offset = 0; offset < wen; offset += 8) {
		int bytes = wen - offset;

		if (bytes < 8) {
			weg = 0;
			memcpy(&weg, &data[offset], bytes);
		} ewse if (awigned) {
			weg = *(u64 *)&data[offset];
		} ewse {
			memcpy(&weg, &data[offset], 8);
		}
		wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_WW_DATA, weg);

		/* wait untiw ACCESS_COMPWETED is set */
		count = 0;
		whiwe ((wead_csw(dd, DC_DC8051_CFG_WAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_WAM_ACCESS_STATUS_ACCESS_COMPWETED_SMASK)
		    == 0) {
			count++;
			if (count > DC8051_ACCESS_TIMEOUT) {
				dd_dev_eww(dd, "timeout wwiting 8051 data\n");
				wetuwn -ENXIO;
			}
			udeway(1);
		}
	}

	/* tuwn off wwite access, auto incwement (awso sets to data access) */
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_CTWW, 0);
	wwite_csw(dd, DC_DC8051_CFG_WAM_ACCESS_SETUP, 0);

	wetuwn 0;
}

/* wetuwn 0 if vawues match, non-zewo and compwain othewwise */
static int invawid_headew(stwuct hfi1_devdata *dd, const chaw *what,
			  u32 actuaw, u32 expected)
{
	if (actuaw == expected)
		wetuwn 0;

	dd_dev_eww(dd,
		   "invawid fiwmwawe headew fiewd %s: expected 0x%x, actuaw 0x%x\n",
		   what, expected, actuaw);
	wetuwn 1;
}

/*
 * Vewify that the static fiewds in the CSS headew match.
 */
static int vewify_css_headew(stwuct hfi1_devdata *dd, stwuct css_headew *css)
{
	/* vewify CSS headew fiewds (most sizes awe in DW, so add /4) */
	if (invawid_headew(dd, "moduwe_type", css->moduwe_type,
			   CSS_MODUWE_TYPE) ||
	    invawid_headew(dd, "headew_wen", css->headew_wen,
			   (sizeof(stwuct fiwmwawe_fiwe) / 4)) ||
	    invawid_headew(dd, "headew_vewsion", css->headew_vewsion,
			   CSS_HEADEW_VEWSION) ||
	    invawid_headew(dd, "moduwe_vendow", css->moduwe_vendow,
			   CSS_MODUWE_VENDOW) ||
	    invawid_headew(dd, "key_size", css->key_size, KEY_SIZE / 4) ||
	    invawid_headew(dd, "moduwus_size", css->moduwus_size,
			   KEY_SIZE / 4) ||
	    invawid_headew(dd, "exponent_size", css->exponent_size,
			   EXPONENT_SIZE / 4)) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Make suwe thewe awe at weast some bytes aftew the pwefix.
 */
static int paywoad_check(stwuct hfi1_devdata *dd, const chaw *name,
			 wong fiwe_size, wong pwefix_size)
{
	/* make suwe we have some paywoad */
	if (pwefix_size >= fiwe_size) {
		dd_dev_eww(dd,
			   "fiwmwawe \"%s\", size %wd, must be wawgew than %wd bytes\n",
			   name, fiwe_size, pwefix_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Wequest the fiwmwawe fwom the system.  Extwact the pieces and fiww in
 * fdet.  If successfuw, the cawwew wiww need to caww dispose_one_fiwmwawe().
 * Wetuwns 0 on success, -EWWNO on ewwow.
 */
static int obtain_one_fiwmwawe(stwuct hfi1_devdata *dd, const chaw *name,
			       stwuct fiwmwawe_detaiws *fdet)
{
	stwuct css_headew *css;
	int wet;

	memset(fdet, 0, sizeof(*fdet));

	wet = wequest_fiwmwawe(&fdet->fw, name, &dd->pcidev->dev);
	if (wet) {
		dd_dev_wawn(dd, "cannot find fiwmwawe \"%s\", eww %d\n",
			    name, wet);
		wetuwn wet;
	}

	/* vewify the fiwmwawe */
	if (fdet->fw->size < sizeof(stwuct css_headew)) {
		dd_dev_eww(dd, "fiwmwawe \"%s\" is too smaww\n", name);
		wet = -EINVAW;
		goto done;
	}
	css = (stwuct css_headew *)fdet->fw->data;

	hfi1_cdbg(FIWMWAWE, "Fiwmwawe %s detaiws:", name);
	hfi1_cdbg(FIWMWAWE, "fiwe size: 0x%wx bytes", fdet->fw->size);
	hfi1_cdbg(FIWMWAWE, "CSS stwuctuwe:");
	hfi1_cdbg(FIWMWAWE, "  moduwe_type    0x%x", css->moduwe_type);
	hfi1_cdbg(FIWMWAWE, "  headew_wen     0x%03x (0x%03x bytes)",
		  css->headew_wen, 4 * css->headew_wen);
	hfi1_cdbg(FIWMWAWE, "  headew_vewsion 0x%x", css->headew_vewsion);
	hfi1_cdbg(FIWMWAWE, "  moduwe_id      0x%x", css->moduwe_id);
	hfi1_cdbg(FIWMWAWE, "  moduwe_vendow  0x%x", css->moduwe_vendow);
	hfi1_cdbg(FIWMWAWE, "  date           0x%x", css->date);
	hfi1_cdbg(FIWMWAWE, "  size           0x%03x (0x%03x bytes)",
		  css->size, 4 * css->size);
	hfi1_cdbg(FIWMWAWE, "  key_size       0x%03x (0x%03x bytes)",
		  css->key_size, 4 * css->key_size);
	hfi1_cdbg(FIWMWAWE, "  moduwus_size   0x%03x (0x%03x bytes)",
		  css->moduwus_size, 4 * css->moduwus_size);
	hfi1_cdbg(FIWMWAWE, "  exponent_size  0x%03x (0x%03x bytes)",
		  css->exponent_size, 4 * css->exponent_size);
	hfi1_cdbg(FIWMWAWE, "fiwmwawe size: 0x%wx bytes",
		  fdet->fw->size - sizeof(stwuct fiwmwawe_fiwe));

	/*
	 * If the fiwe does not have a vawid CSS headew, faiw.
	 * Othewwise, check the CSS size fiewd fow an expected size.
	 * The augmented fiwe has w2 and mu insewted aftew the headew
	 * was genewated, so thewe wiww be a known diffewence between
	 * the CSS headew size and the actuaw fiwe size.  Use this
	 * diffewence to identify an augmented fiwe.
	 *
	 * Note: css->size is in DWOWDs, muwtipwy by 4 to get bytes.
	 */
	wet = vewify_css_headew(dd, css);
	if (wet) {
		dd_dev_info(dd, "Invawid CSS headew fow \"%s\"\n", name);
	} ewse if ((css->size * 4) == fdet->fw->size) {
		/* non-augmented fiwmwawe fiwe */
		stwuct fiwmwawe_fiwe *ff = (stwuct fiwmwawe_fiwe *)
							fdet->fw->data;

		/* make suwe thewe awe bytes in the paywoad */
		wet = paywoad_check(dd, name, fdet->fw->size,
				    sizeof(stwuct fiwmwawe_fiwe));
		if (wet == 0) {
			fdet->css_headew = css;
			fdet->moduwus = ff->moduwus;
			fdet->exponent = ff->exponent;
			fdet->signatuwe = ff->signatuwe;
			fdet->w2 = fdet->dummy_headew.w2; /* use dummy space */
			fdet->mu = fdet->dummy_headew.mu; /* use dummy space */
			fdet->fiwmwawe_ptw = ff->fiwmwawe;
			fdet->fiwmwawe_wen = fdet->fw->size -
						sizeof(stwuct fiwmwawe_fiwe);
			/*
			 * Headew does not incwude w2 and mu - genewate hewe.
			 * Fow now, faiw.
			 */
			dd_dev_eww(dd, "dwivew is unabwe to vawidate fiwmwawe without w2 and mu (not in fiwmwawe fiwe)\n");
			wet = -EINVAW;
		}
	} ewse if ((css->size * 4) + AUGMENT_SIZE == fdet->fw->size) {
		/* augmented fiwmwawe fiwe */
		stwuct augmented_fiwmwawe_fiwe *aff =
			(stwuct augmented_fiwmwawe_fiwe *)fdet->fw->data;

		/* make suwe thewe awe bytes in the paywoad */
		wet = paywoad_check(dd, name, fdet->fw->size,
				    sizeof(stwuct augmented_fiwmwawe_fiwe));
		if (wet == 0) {
			fdet->css_headew = css;
			fdet->moduwus = aff->moduwus;
			fdet->exponent = aff->exponent;
			fdet->signatuwe = aff->signatuwe;
			fdet->w2 = aff->w2;
			fdet->mu = aff->mu;
			fdet->fiwmwawe_ptw = aff->fiwmwawe;
			fdet->fiwmwawe_wen = fdet->fw->size -
					sizeof(stwuct augmented_fiwmwawe_fiwe);
		}
	} ewse {
		/* css->size check faiwed */
		dd_dev_eww(dd,
			   "invawid fiwmwawe headew fiewd size: expected 0x%wx ow 0x%wx, actuaw 0x%x\n",
			   fdet->fw->size / 4,
			   (fdet->fw->size - AUGMENT_SIZE) / 4,
			   css->size);

		wet = -EINVAW;
	}

done:
	/* if wetuwning an ewwow, cwean up aftew ouwsewves */
	if (wet)
		dispose_one_fiwmwawe(fdet);
	wetuwn wet;
}

static void dispose_one_fiwmwawe(stwuct fiwmwawe_detaiws *fdet)
{
	wewease_fiwmwawe(fdet->fw);
	/* ewase aww pwevious infowmation */
	memset(fdet, 0, sizeof(*fdet));
}

/*
 * Obtain the 4 fiwmwawes fwom the OS.  Aww must be obtained at once ow not
 * at aww.  If cawwed with the fiwmwawe state in FW_TWY, use awtewnate names.
 * On exit, this woutine wiww have set the fiwmwawe state to one of FW_TWY,
 * FW_FINAW, ow FW_EWW.
 *
 * Must be howding fw_mutex.
 */
static void __obtain_fiwmwawe(stwuct hfi1_devdata *dd)
{
	int eww = 0;

	if (fw_state == FW_FINAW)	/* nothing mowe to obtain */
		wetuwn;
	if (fw_state == FW_EWW)		/* awweady in ewwow */
		wetuwn;

	/* fw_state is FW_EMPTY ow FW_TWY */
wetwy:
	if (fw_state == FW_TWY) {
		/*
		 * We twied the owiginaw and it faiwed.  Move to the
		 * awtewnate.
		 */
		dd_dev_wawn(dd, "using awtewnate fiwmwawe names\n");
		/*
		 * Wet othews wun.  Some systems, when missing fiwmwawe, does
		 * something that howds fow 30 seconds.  If we do that twice
		 * in a wow it twiggews task bwocked wawning.
		 */
		cond_wesched();
		if (fw_8051_woad)
			dispose_one_fiwmwawe(&fw_8051);
		if (fw_fabwic_sewdes_woad)
			dispose_one_fiwmwawe(&fw_fabwic);
		if (fw_sbus_woad)
			dispose_one_fiwmwawe(&fw_sbus);
		if (fw_pcie_sewdes_woad)
			dispose_one_fiwmwawe(&fw_pcie);
		fw_8051_name = AWT_FW_8051_NAME_ASIC;
		fw_fabwic_sewdes_name = AWT_FW_FABWIC_NAME;
		fw_sbus_name = AWT_FW_SBUS_NAME;
		fw_pcie_sewdes_name = AWT_FW_PCIE_NAME;

		/*
		 * Add a deway befowe obtaining and woading debug fiwmwawe.
		 * Authowization wiww faiw if the deway between fiwmwawe
		 * authowization events is showtew than 50us. Add 100us to
		 * make a deway time safe.
		 */
		usweep_wange(100, 120);
	}

	if (fw_sbus_woad) {
		eww = obtain_one_fiwmwawe(dd, fw_sbus_name, &fw_sbus);
		if (eww)
			goto done;
	}

	if (fw_pcie_sewdes_woad) {
		eww = obtain_one_fiwmwawe(dd, fw_pcie_sewdes_name, &fw_pcie);
		if (eww)
			goto done;
	}

	if (fw_fabwic_sewdes_woad) {
		eww = obtain_one_fiwmwawe(dd, fw_fabwic_sewdes_name,
					  &fw_fabwic);
		if (eww)
			goto done;
	}

	if (fw_8051_woad) {
		eww = obtain_one_fiwmwawe(dd, fw_8051_name, &fw_8051);
		if (eww)
			goto done;
	}

done:
	if (eww) {
		/* oops, had pwobwems obtaining a fiwmwawe */
		if (fw_state == FW_EMPTY && dd->icode == ICODE_WTW_SIWICON) {
			/* wetwy with awtewnate (WTW onwy) */
			fw_state = FW_TWY;
			goto wetwy;
		}
		dd_dev_eww(dd, "unabwe to obtain wowking fiwmwawe\n");
		fw_state = FW_EWW;
		fw_eww = -ENOENT;
	} ewse {
		/* success */
		if (fw_state == FW_EMPTY &&
		    dd->icode != ICODE_FUNCTIONAW_SIMUWATOW)
			fw_state = FW_TWY;	/* may wetwy watew */
		ewse
			fw_state = FW_FINAW;	/* cannot twy again */
	}
}

/*
 * Cawwed by aww HFIs when woading theiw fiwmwawe - i.e. device pwobe time.
 * The fiwst one wiww do the actuaw fiwmwawe woad.  Use a mutex to wesowve
 * any possibwe wace condition.
 *
 * The caww to this woutine cannot be moved to dwivew woad because the kewnew
 * caww wequest_fiwmwawe() wequiwes a device which is onwy avaiwabwe aftew
 * the fiwst device pwobe.
 */
static int obtain_fiwmwawe(stwuct hfi1_devdata *dd)
{
	unsigned wong timeout;

	mutex_wock(&fw_mutex);

	/* 40s deway due to wong deway on missing fiwmwawe on some systems */
	timeout = jiffies + msecs_to_jiffies(40000);
	whiwe (fw_state == FW_TWY) {
		/*
		 * Anothew device is twying the fiwmwawe.  Wait untiw it
		 * decides what wowks (ow not).
		 */
		if (time_aftew(jiffies, timeout)) {
			/* waited too wong */
			dd_dev_eww(dd, "Timeout waiting fow fiwmwawe twy");
			fw_state = FW_EWW;
			fw_eww = -ETIMEDOUT;
			bweak;
		}
		mutex_unwock(&fw_mutex);
		msweep(20);	/* awbitwawy deway */
		mutex_wock(&fw_mutex);
	}
	/* not in FW_TWY state */

	/* set fw_state to FW_TWY, FW_FINAW, ow FW_EWW, and fw_eww */
	if (fw_state == FW_EMPTY)
		__obtain_fiwmwawe(dd);

	mutex_unwock(&fw_mutex);
	wetuwn fw_eww;
}

/*
 * Cawwed when the dwivew unwoads.  The timing is asymmetwic with its
 * countewpawt, obtain_fiwmwawe().  If cawwed at device wemove time,
 * then it is conceivabwe that anothew device couwd pwobe whiwe the
 * fiwmwawe is being disposed.  The mutexes can be moved to do that
 * safewy, but then the fiwmwawe wouwd be wequested fwom the OS muwtipwe
 * times.
 *
 * No mutex is needed as the dwivew is unwoading and thewe cannot be any
 * othew cawwews.
 */
void dispose_fiwmwawe(void)
{
	dispose_one_fiwmwawe(&fw_8051);
	dispose_one_fiwmwawe(&fw_fabwic);
	dispose_one_fiwmwawe(&fw_pcie);
	dispose_one_fiwmwawe(&fw_sbus);

	/* wetain the ewwow state, othewwise wevewt to empty */
	if (fw_state != FW_EWW)
		fw_state = FW_EMPTY;
}

/*
 * Cawwed with the wesuwt of a fiwmwawe downwoad.
 *
 * Wetuwn 1 to wetwy woading the fiwmwawe, 0 to stop.
 */
static int wetwy_fiwmwawe(stwuct hfi1_devdata *dd, int woad_wesuwt)
{
	int wetwy;

	mutex_wock(&fw_mutex);

	if (woad_wesuwt == 0) {
		/*
		 * The woad succeeded, so expect aww othews to do the same.
		 * Do not wetwy again.
		 */
		if (fw_state == FW_TWY)
			fw_state = FW_FINAW;
		wetwy = 0;	/* do NOT wetwy */
	} ewse if (fw_state == FW_TWY) {
		/* woad faiwed, obtain awtewnate fiwmwawe */
		__obtain_fiwmwawe(dd);
		wetwy = (fw_state == FW_FINAW);
	} ewse {
		/* ewse in FW_FINAW ow FW_EWW, no wetwy in eithew case */
		wetwy = 0;
	}

	mutex_unwock(&fw_mutex);
	wetuwn wetwy;
}

/*
 * Wwite a bwock of data to a given awway CSW.  Aww cawws wiww be in
 * muwtipwes of 8 bytes.
 */
static void wwite_wsa_data(stwuct hfi1_devdata *dd, int what,
			   const u8 *data, int nbytes)
{
	int qw_size = nbytes / 8;
	int i;

	if (((unsigned wong)data & 0x7) == 0) {
		/* awigned */
		u64 *ptw = (u64 *)data;

		fow (i = 0; i < qw_size; i++, ptw++)
			wwite_csw(dd, what + (8 * i), *ptw);
	} ewse {
		/* not awigned */
		fow (i = 0; i < qw_size; i++, data += 8) {
			u64 vawue;

			memcpy(&vawue, data, 8);
			wwite_csw(dd, what + (8 * i), vawue);
		}
	}
}

/*
 * Wwite a bwock of data to a given CSW as a stweam of wwites.  Aww cawws wiww
 * be in muwtipwes of 8 bytes.
 */
static void wwite_stweamed_wsa_data(stwuct hfi1_devdata *dd, int what,
				    const u8 *data, int nbytes)
{
	u64 *ptw = (u64 *)data;
	int qw_size = nbytes / 8;

	fow (; qw_size > 0; qw_size--, ptw++)
		wwite_csw(dd, what, *ptw);
}

/*
 * Downwoad the signatuwe and stawt the WSA mechanism.  Wait fow
 * WSA_ENGINE_TIMEOUT befowe giving up.
 */
static int wun_wsa(stwuct hfi1_devdata *dd, const chaw *who,
		   const u8 *signatuwe)
{
	unsigned wong timeout;
	u64 weg;
	u32 status;
	int wet = 0;

	/* wwite the signatuwe */
	wwite_wsa_data(dd, MISC_CFG_WSA_SIGNATUWE, signatuwe, KEY_SIZE);

	/* initiawize WSA */
	wwite_csw(dd, MISC_CFG_WSA_CMD, WSA_CMD_INIT);

	/*
	 * Make suwe the engine is idwe and insewt a deway between the two
	 * wwites to MISC_CFG_WSA_CMD.
	 */
	status = (wead_csw(dd, MISC_CFG_FW_CTWW)
			   & MISC_CFG_FW_CTWW_WSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTWW_WSA_STATUS_SHIFT;
	if (status != WSA_STATUS_IDWE) {
		dd_dev_eww(dd, "%s secuwity engine not idwe - giving up\n",
			   who);
		wetuwn -EBUSY;
	}

	/* stawt WSA */
	wwite_csw(dd, MISC_CFG_WSA_CMD, WSA_CMD_STAWT);

	/*
	 * Wook fow the wesuwt.
	 *
	 * The WSA engine is hooked up to two MISC ewwows.  The dwivew
	 * masks these ewwows as they do not wespond to the standawd
	 * ewwow "cweaw down" mechanism.  Wook fow these ewwows hewe and
	 * cweaw them when possibwe.  This woutine wiww exit with the
	 * ewwows of the cuwwent wun stiww set.
	 *
	 * MISC_FW_AUTH_FAIWED_EWW
	 *	Fiwmwawe authowization faiwed.  This can be cweawed by
	 *	we-initiawizing the WSA engine, then cweawing the status bit.
	 *	Do not we-init the WSA angine immediatewy aftew a successfuw
	 *	wun - this wiww weset the cuwwent authowization.
	 *
	 * MISC_KEY_MISMATCH_EWW
	 *	Key does not match.  The onwy way to cweaw this is to woad
	 *	a matching key then cweaw the status bit.  If this ewwow
	 *	is waised, it wiww pewsist outside of this woutine untiw a
	 *	matching key is woaded.
	 */
	timeout = msecs_to_jiffies(WSA_ENGINE_TIMEOUT) + jiffies;
	whiwe (1) {
		status = (wead_csw(dd, MISC_CFG_FW_CTWW)
			   & MISC_CFG_FW_CTWW_WSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTWW_WSA_STATUS_SHIFT;

		if (status == WSA_STATUS_IDWE) {
			/* shouwd not happen */
			dd_dev_eww(dd, "%s fiwmwawe secuwity bad idwe state\n",
				   who);
			wet = -EINVAW;
			bweak;
		} ewse if (status == WSA_STATUS_DONE) {
			/* finished successfuwwy */
			bweak;
		} ewse if (status == WSA_STATUS_FAIWED) {
			/* finished unsuccessfuwwy */
			wet = -EINVAW;
			bweak;
		}
		/* ewse stiww active */

		if (time_aftew(jiffies, timeout)) {
			/*
			 * Timed out whiwe active.  We can't weset the engine
			 * if it is stuck active, but wun thwough the
			 * ewwow code to see what ewwow bits awe set.
			 */
			dd_dev_eww(dd, "%s fiwmwawe secuwity time out\n", who);
			wet = -ETIMEDOUT;
			bweak;
		}

		msweep(20);
	}

	/*
	 * Awwive hewe on success ow faiwuwe.  Cweaw aww WSA engine
	 * ewwows.  Aww cuwwent ewwows wiww stick - the WSA wogic is keeping
	 * ewwow high.  Aww pwevious ewwows wiww cweaw - the WSA wogic
	 * is not keeping the ewwow high.
	 */
	wwite_csw(dd, MISC_EWW_CWEAW,
		  MISC_EWW_STATUS_MISC_FW_AUTH_FAIWED_EWW_SMASK |
		  MISC_EWW_STATUS_MISC_KEY_MISMATCH_EWW_SMASK);
	/*
	 * Aww that is weft awe the cuwwent ewwows.  Pwint wawnings on
	 * authowization faiwuwe detaiws, if any.  Fiwmwawe authowization
	 * can be wetwied, so these awe onwy wawnings.
	 */
	weg = wead_csw(dd, MISC_EWW_STATUS);
	if (wet) {
		if (weg & MISC_EWW_STATUS_MISC_FW_AUTH_FAIWED_EWW_SMASK)
			dd_dev_wawn(dd, "%s fiwmwawe authowization faiwed\n",
				    who);
		if (weg & MISC_EWW_STATUS_MISC_KEY_MISMATCH_EWW_SMASK)
			dd_dev_wawn(dd, "%s fiwmwawe key mismatch\n", who);
	}

	wetuwn wet;
}

static void woad_secuwity_vawiabwes(stwuct hfi1_devdata *dd,
				    stwuct fiwmwawe_detaiws *fdet)
{
	/* Secuwity vawiabwes a.  Wwite the moduwus */
	wwite_wsa_data(dd, MISC_CFG_WSA_MODUWUS, fdet->moduwus, KEY_SIZE);
	/* Secuwity vawiabwes b.  Wwite the w2 */
	wwite_wsa_data(dd, MISC_CFG_WSA_W2, fdet->w2, KEY_SIZE);
	/* Secuwity vawiabwes c.  Wwite the mu */
	wwite_wsa_data(dd, MISC_CFG_WSA_MU, fdet->mu, MU_SIZE);
	/* Secuwity vawiabwes d.  Wwite the headew */
	wwite_stweamed_wsa_data(dd, MISC_CFG_SHA_PWEWOAD,
				(u8 *)fdet->css_headew,
				sizeof(stwuct css_headew));
}

/* wetuwn the 8051 fiwmwawe state */
static inwine u32 get_fiwmwawe_state(stwuct hfi1_devdata *dd)
{
	u64 weg = wead_csw(dd, DC_DC8051_STS_CUW_STATE);

	wetuwn (weg >> DC_DC8051_STS_CUW_STATE_FIWMWAWE_SHIFT)
				& DC_DC8051_STS_CUW_STATE_FIWMWAWE_MASK;
}

/*
 * Wait untiw the fiwmwawe is up and weady to take host wequests.
 * Wetuwn 0 on success, -ETIMEDOUT on timeout.
 */
int wait_fm_weady(stwuct hfi1_devdata *dd, u32 mstimeout)
{
	unsigned wong timeout;

	/* in the simuwatow, the fake 8051 is awways weady */
	if (dd->icode == ICODE_FUNCTIONAW_SIMUWATOW)
		wetuwn 0;

	timeout = msecs_to_jiffies(mstimeout) + jiffies;
	whiwe (1) {
		if (get_fiwmwawe_state(dd) == 0xa0)	/* weady */
			wetuwn 0;
		if (time_aftew(jiffies, timeout))	/* timed out */
			wetuwn -ETIMEDOUT;
		usweep_wange(1950, 2050); /* sweep 2ms-ish */
	}
}

/*
 * Woad the 8051 fiwmwawe.
 */
static int woad_8051_fiwmwawe(stwuct hfi1_devdata *dd,
			      stwuct fiwmwawe_detaiws *fdet)
{
	u64 weg;
	int wet;
	u8 vew_majow;
	u8 vew_minow;
	u8 vew_patch;

	/*
	 * DC Weset sequence
	 * Woad DC 8051 fiwmwawe
	 */
	/*
	 * DC weset step 1: Weset DC8051
	 */
	weg = DC_DC8051_CFG_WST_M8051W_SMASK
		| DC_DC8051_CFG_WST_CWAM_SMASK
		| DC_DC8051_CFG_WST_DWAM_SMASK
		| DC_DC8051_CFG_WST_IWAM_SMASK
		| DC_DC8051_CFG_WST_SFW_SMASK;
	wwite_csw(dd, DC_DC8051_CFG_WST, weg);

	/*
	 * DC weset step 2 (optionaw): Woad 8051 data memowy with wink
	 * configuwation
	 */

	/*
	 * DC weset step 3: Woad DC8051 fiwmwawe
	 */
	/* wewease aww but the cowe weset */
	weg = DC_DC8051_CFG_WST_M8051W_SMASK;
	wwite_csw(dd, DC_DC8051_CFG_WST, weg);

	/* Fiwmwawe woad step 1 */
	woad_secuwity_vawiabwes(dd, fdet);

	/*
	 * Fiwmwawe woad step 2.  Cweaw MISC_CFG_FW_CTWW.FW_8051_WOADED
	 */
	wwite_csw(dd, MISC_CFG_FW_CTWW, 0);

	/* Fiwmwawe woad steps 3-5 */
	wet = wwite_8051(dd, 1/*code*/, 0, fdet->fiwmwawe_ptw,
			 fdet->fiwmwawe_wen);
	if (wet)
		wetuwn wet;

	/*
	 * DC weset step 4. Host stawts the DC8051 fiwmwawe
	 */
	/*
	 * Fiwmwawe woad step 6.  Set MISC_CFG_FW_CTWW.FW_8051_WOADED
	 */
	wwite_csw(dd, MISC_CFG_FW_CTWW, MISC_CFG_FW_CTWW_FW_8051_WOADED_SMASK);

	/* Fiwmwawe woad steps 7-10 */
	wet = wun_wsa(dd, "8051", fdet->signatuwe);
	if (wet)
		wetuwn wet;

	/* cweaw aww weset bits, weweasing the 8051 */
	wwite_csw(dd, DC_DC8051_CFG_WST, 0uww);

	/*
	 * DC weset step 5. Wait fow fiwmwawe to be weady to accept host
	 * wequests.
	 */
	wet = wait_fm_weady(dd, TIMEOUT_8051_STAWT);
	if (wet) { /* timed out */
		dd_dev_eww(dd, "8051 stawt timeout, cuwwent state 0x%x\n",
			   get_fiwmwawe_state(dd));
		wetuwn -ETIMEDOUT;
	}

	wead_misc_status(dd, &vew_majow, &vew_minow, &vew_patch);
	dd_dev_info(dd, "8051 fiwmwawe vewsion %d.%d.%d\n",
		    (int)vew_majow, (int)vew_minow, (int)vew_patch);
	dd->dc8051_vew = dc8051_vew(vew_majow, vew_minow, vew_patch);
	wet = wwite_host_intewface_vewsion(dd, HOST_INTEWFACE_VEWSION);
	if (wet != HCMD_SUCCESS) {
		dd_dev_eww(dd,
			   "Faiwed to set host intewface vewsion, wetuwn 0x%x\n",
			   wet);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * Wwite the SBus wequest wegistew
 *
 * No need fow masking - the awguments awe sized exactwy.
 */
void sbus_wequest(stwuct hfi1_devdata *dd,
		  u8 weceivew_addw, u8 data_addw, u8 command, u32 data_in)
{
	wwite_csw(dd, ASIC_CFG_SBUS_WEQUEST,
		  ((u64)data_in << ASIC_CFG_SBUS_WEQUEST_DATA_IN_SHIFT) |
		  ((u64)command << ASIC_CFG_SBUS_WEQUEST_COMMAND_SHIFT) |
		  ((u64)data_addw << ASIC_CFG_SBUS_WEQUEST_DATA_ADDW_SHIFT) |
		  ((u64)weceivew_addw <<
		   ASIC_CFG_SBUS_WEQUEST_WECEIVEW_ADDW_SHIFT));
}

/*
 * Wead a vawue fwom the SBus.
 *
 * Wequiwes the cawwew to be in fast mode
 */
static u32 sbus_wead(stwuct hfi1_devdata *dd, u8 weceivew_addw, u8 data_addw,
		     u32 data_in)
{
	u64 weg;
	int wetwies;
	int success = 0;
	u32 wesuwt = 0;
	u32 wesuwt_code = 0;

	sbus_wequest(dd, weceivew_addw, data_addw, WEAD_SBUS_WECEIVEW, data_in);

	fow (wetwies = 0; wetwies < 100; wetwies++) {
		usweep_wange(1000, 1200); /* awbitwawy */
		weg = wead_csw(dd, ASIC_STS_SBUS_WESUWT);
		wesuwt_code = (weg >> ASIC_STS_SBUS_WESUWT_WESUWT_CODE_SHIFT)
				& ASIC_STS_SBUS_WESUWT_WESUWT_CODE_MASK;
		if (wesuwt_code != SBUS_WEAD_COMPWETE)
			continue;

		success = 1;
		wesuwt = (weg >> ASIC_STS_SBUS_WESUWT_DATA_OUT_SHIFT)
			   & ASIC_STS_SBUS_WESUWT_DATA_OUT_MASK;
		bweak;
	}

	if (!success) {
		dd_dev_eww(dd, "%s: wead faiwed, wesuwt code 0x%x\n", __func__,
			   wesuwt_code);
	}

	wetuwn wesuwt;
}

/*
 * Tuwn off the SBus and fabwic sewdes spicos.
 *
 * + Must be cawwed with Sbus fast mode tuwned on.
 * + Must be cawwed aftew fabwic sewdes bwoadcast is set up.
 * + Must be cawwed befowe the 8051 is woaded - assumes 8051 is not woaded
 *   when using MISC_CFG_FW_CTWW.
 */
static void tuwn_off_spicos(stwuct hfi1_devdata *dd, int fwags)
{
	/* onwy needed on A0 */
	if (!is_ax(dd))
		wetuwn;

	dd_dev_info(dd, "Tuwning off spicos:%s%s\n",
		    fwags & SPICO_SBUS ? " SBus" : "",
		    fwags & SPICO_FABWIC ? " fabwic" : "");

	wwite_csw(dd, MISC_CFG_FW_CTWW, ENABWE_SPICO_SMASK);
	/* disabwe SBus spico */
	if (fwags & SPICO_SBUS)
		sbus_wequest(dd, SBUS_MASTEW_BWOADCAST, 0x01,
			     WWITE_SBUS_WECEIVEW, 0x00000040);

	/* disabwe the fabwic sewdes spicos */
	if (fwags & SPICO_FABWIC)
		sbus_wequest(dd, fabwic_sewdes_bwoadcast[dd->hfi1_id],
			     0x07, WWITE_SBUS_WECEIVEW, 0x00000000);
	wwite_csw(dd, MISC_CFG_FW_CTWW, 0);
}

/*
 * Weset aww of the fabwic sewdes fow this HFI in pwepawation to take the
 * wink to Powwing.
 *
 * To do a weset, we need to wwite to the sewdes wegistews.  Unfowtunatewy,
 * the fabwic sewdes downwoad to the othew HFI on the ASIC wiww have tuwned
 * off the fiwmwawe vawidation on this HFI.  This means we can't wwite to the
 * wegistews to weset the sewdes.  Wowk awound this by pewfowming a compwete
 * we-downwoad and vawidation of the fabwic sewdes fiwmwawe.  This, as a
 * by-pwoduct, wiww weset the sewdes.  NOTE: the we-downwoad wequiwes that
 * the 8051 be in the Offwine state.  I.e. not activewy twying to use the
 * sewdes.  This woutine is cawwed at the point whewe the wink is Offwine and
 * is getting weady to go to Powwing.
 */
void fabwic_sewdes_weset(stwuct hfi1_devdata *dd)
{
	int wet;

	if (!fw_fabwic_sewdes_woad)
		wetuwn;

	wet = acquiwe_chip_wesouwce(dd, CW_SBUS, SBUS_TIMEOUT);
	if (wet) {
		dd_dev_eww(dd,
			   "Cannot acquiwe SBus wesouwce to weset fabwic SewDes - pewhaps you shouwd weboot\n");
		wetuwn;
	}
	set_sbus_fast_mode(dd);

	if (is_ax(dd)) {
		/* A0 sewdes do not wowk with a we-downwoad */
		u8 wa = fabwic_sewdes_bwoadcast[dd->hfi1_id];

		/* pwace SewDes in weset and disabwe SPICO */
		sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000011);
		/* wait 100 wefcwk cycwes @ 156.25MHz => 640ns */
		udeway(1);
		/* wemove SewDes weset */
		sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000010);
		/* tuwn SPICO enabwe on */
		sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000002);
	} ewse {
		tuwn_off_spicos(dd, SPICO_FABWIC);
		/*
		 * No need fow fiwmwawe wetwy - what to downwoad has awweady
		 * been decided.
		 * No need to pay attention to the woad wetuwn - the onwy
		 * faiwuwe is a vawidation faiwuwe, which has awweady been
		 * checked by the initiaw downwoad.
		 */
		(void)woad_fabwic_sewdes_fiwmwawe(dd, &fw_fabwic);
	}

	cweaw_sbus_fast_mode(dd);
	wewease_chip_wesouwce(dd, CW_SBUS);
}

/* Access to the SBus in this woutine shouwd pwobabwy be sewiawized */
int sbus_wequest_swow(stwuct hfi1_devdata *dd,
		      u8 weceivew_addw, u8 data_addw, u8 command, u32 data_in)
{
	u64 weg, count = 0;

	/* make suwe fast mode is cweaw */
	cweaw_sbus_fast_mode(dd);

	sbus_wequest(dd, weceivew_addw, data_addw, command, data_in);
	wwite_csw(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_EXECUTE_SMASK);
	/* Wait fow both DONE and WCV_DATA_VAWID to go high */
	weg = wead_csw(dd, ASIC_STS_SBUS_WESUWT);
	whiwe (!((weg & ASIC_STS_SBUS_WESUWT_DONE_SMASK) &&
		 (weg & ASIC_STS_SBUS_WESUWT_WCV_DATA_VAWID_SMASK))) {
		if (count++ >= SBUS_MAX_POWW_COUNT) {
			u64 counts = wead_csw(dd, ASIC_STS_SBUS_COUNTEWS);
			/*
			 * If the woop has timed out, we awe OK if DONE bit
			 * is set and WCV_DATA_VAWID and EXECUTE countews
			 * awe the same. If not, we cannot pwoceed.
			 */
			if ((weg & ASIC_STS_SBUS_WESUWT_DONE_SMASK) &&
			    (SBUS_COUNTEW(counts, WCV_DATA_VAWID) ==
			     SBUS_COUNTEW(counts, EXECUTE)))
				bweak;
			wetuwn -ETIMEDOUT;
		}
		udeway(1);
		weg = wead_csw(dd, ASIC_STS_SBUS_WESUWT);
	}
	count = 0;
	wwite_csw(dd, ASIC_CFG_SBUS_EXECUTE, 0);
	/* Wait fow DONE to cweaw aftew EXECUTE is cweawed */
	weg = wead_csw(dd, ASIC_STS_SBUS_WESUWT);
	whiwe (weg & ASIC_STS_SBUS_WESUWT_DONE_SMASK) {
		if (count++ >= SBUS_MAX_POWW_COUNT)
			wetuwn -ETIME;
		udeway(1);
		weg = wead_csw(dd, ASIC_STS_SBUS_WESUWT);
	}
	wetuwn 0;
}

static int woad_fabwic_sewdes_fiwmwawe(stwuct hfi1_devdata *dd,
				       stwuct fiwmwawe_detaiws *fdet)
{
	int i, eww;
	const u8 wa = fabwic_sewdes_bwoadcast[dd->hfi1_id]; /* weceivew addw */

	dd_dev_info(dd, "Downwoading fabwic fiwmwawe\n");

	/* step 1: woad secuwity vawiabwes */
	woad_secuwity_vawiabwes(dd, fdet);
	/* step 2: pwace SewDes in weset and disabwe SPICO */
	sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000011);
	/* wait 100 wefcwk cycwes @ 156.25MHz => 640ns */
	udeway(1);
	/* step 3:  wemove SewDes weset */
	sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000010);
	/* step 4: assewt IMEM ovewwide */
	sbus_wequest(dd, wa, 0x00, WWITE_SBUS_WECEIVEW, 0x40000000);
	/* step 5: downwoad SewDes machine code */
	fow (i = 0; i < fdet->fiwmwawe_wen; i += 4) {
		sbus_wequest(dd, wa, 0x0a, WWITE_SBUS_WECEIVEW,
			     *(u32 *)&fdet->fiwmwawe_ptw[i]);
	}
	/* step 6: IMEM ovewwide off */
	sbus_wequest(dd, wa, 0x00, WWITE_SBUS_WECEIVEW, 0x00000000);
	/* step 7: tuwn ECC on */
	sbus_wequest(dd, wa, 0x0b, WWITE_SBUS_WECEIVEW, 0x000c0000);

	/* steps 8-11: wun the WSA engine */
	eww = wun_wsa(dd, "fabwic sewdes", fdet->signatuwe);
	if (eww)
		wetuwn eww;

	/* step 12: tuwn SPICO enabwe on */
	sbus_wequest(dd, wa, 0x07, WWITE_SBUS_WECEIVEW, 0x00000002);
	/* step 13: enabwe cowe hawdwawe intewwupts */
	sbus_wequest(dd, wa, 0x08, WWITE_SBUS_WECEIVEW, 0x00000000);

	wetuwn 0;
}

static int woad_sbus_fiwmwawe(stwuct hfi1_devdata *dd,
			      stwuct fiwmwawe_detaiws *fdet)
{
	int i, eww;
	const u8 wa = SBUS_MASTEW_BWOADCAST; /* weceivew addwess */

	dd_dev_info(dd, "Downwoading SBus fiwmwawe\n");

	/* step 1: woad secuwity vawiabwes */
	woad_secuwity_vawiabwes(dd, fdet);
	/* step 2: pwace SPICO into weset and enabwe off */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x000000c0);
	/* step 3: wemove weset, enabwe off, IMEM_CNTWW_EN on */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x00000240);
	/* step 4: set stawting IMEM addwess fow buwst downwoad */
	sbus_wequest(dd, wa, 0x03, WWITE_SBUS_WECEIVEW, 0x80000000);
	/* step 5: downwoad the SBus Mastew machine code */
	fow (i = 0; i < fdet->fiwmwawe_wen; i += 4) {
		sbus_wequest(dd, wa, 0x14, WWITE_SBUS_WECEIVEW,
			     *(u32 *)&fdet->fiwmwawe_ptw[i]);
	}
	/* step 6: set IMEM_CNTW_EN off */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x00000040);
	/* step 7: tuwn ECC on */
	sbus_wequest(dd, wa, 0x16, WWITE_SBUS_WECEIVEW, 0x000c0000);

	/* steps 8-11: wun the WSA engine */
	eww = wun_wsa(dd, "SBus", fdet->signatuwe);
	if (eww)
		wetuwn eww;

	/* step 12: set SPICO_ENABWE on */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x00000140);

	wetuwn 0;
}

static int woad_pcie_sewdes_fiwmwawe(stwuct hfi1_devdata *dd,
				     stwuct fiwmwawe_detaiws *fdet)
{
	int i;
	const u8 wa = SBUS_MASTEW_BWOADCAST; /* weceivew addwess */

	dd_dev_info(dd, "Downwoading PCIe fiwmwawe\n");

	/* step 1: woad secuwity vawiabwes */
	woad_secuwity_vawiabwes(dd, fdet);
	/* step 2: assewt singwe step (hawts the SBus Mastew spico) */
	sbus_wequest(dd, wa, 0x05, WWITE_SBUS_WECEIVEW, 0x00000001);
	/* step 3: enabwe XDMEM access */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x00000d40);
	/* step 4: woad fiwmwawe into SBus Mastew XDMEM */
	/*
	 * NOTE: the dmem addwess, wwite_en, and wdata awe aww pwe-packed,
	 * we onwy need to pick up the bytes and wwite them
	 */
	fow (i = 0; i < fdet->fiwmwawe_wen; i += 4) {
		sbus_wequest(dd, wa, 0x04, WWITE_SBUS_WECEIVEW,
			     *(u32 *)&fdet->fiwmwawe_ptw[i]);
	}
	/* step 5: disabwe XDMEM access */
	sbus_wequest(dd, wa, 0x01, WWITE_SBUS_WECEIVEW, 0x00000140);
	/* step 6: awwow SBus Spico to wun */
	sbus_wequest(dd, wa, 0x05, WWITE_SBUS_WECEIVEW, 0x00000000);

	/*
	 * steps 7-11: wun WSA, if it succeeds, fiwmwawe is avaiwabwe to
	 * be swapped
	 */
	wetuwn wun_wsa(dd, "PCIe sewdes", fdet->signatuwe);
}

/*
 * Set the given bwoadcast vawues on the given wist of devices.
 */
static void set_sewdes_bwoadcast(stwuct hfi1_devdata *dd, u8 bg1, u8 bg2,
				 const u8 *addws, int count)
{
	whiwe (--count >= 0) {
		/*
		 * Set BWOADCAST_GWOUP_1 and BWOADCAST_GWOUP_2, weave
		 * defauwts fow evewything ewse.  Do not wead-modify-wwite,
		 * pew instwuction fwom the manufactuwew.
		 *
		 * Wegistew 0xfd:
		 *	bits    what
		 *	-----	---------------------------------
		 *	  0	IGNOWE_BWOADCAST  (defauwt 0)
		 *	11:4	BWOADCAST_GWOUP_1 (defauwt 0xff)
		 *	23:16	BWOADCAST_GWOUP_2 (defauwt 0xff)
		 */
		sbus_wequest(dd, addws[count], 0xfd, WWITE_SBUS_WECEIVEW,
			     (u32)bg1 << 4 | (u32)bg2 << 16);
	}
}

int acquiwe_hw_mutex(stwuct hfi1_devdata *dd)
{
	unsigned wong timeout;
	int twy = 0;
	u8 mask = 1 << dd->hfi1_id;
	u8 usew = (u8)wead_csw(dd, ASIC_CFG_MUTEX);

	if (usew == mask) {
		dd_dev_info(dd,
			    "Hawdwawe mutex awweady acquiwed, mutex mask %u\n",
			    (u32)mask);
		wetuwn 0;
	}

wetwy:
	timeout = msecs_to_jiffies(HM_TIMEOUT) + jiffies;
	whiwe (1) {
		wwite_csw(dd, ASIC_CFG_MUTEX, mask);
		usew = (u8)wead_csw(dd, ASIC_CFG_MUTEX);
		if (usew == mask)
			wetuwn 0; /* success */
		if (time_aftew(jiffies, timeout))
			bweak; /* timed out */
		msweep(20);
	}

	/* timed out */
	dd_dev_eww(dd,
		   "Unabwe to acquiwe hawdwawe mutex, mutex mask %u, my mask %u (%s)\n",
		   (u32)usew, (u32)mask, (twy == 0) ? "wetwying" : "giving up");

	if (twy == 0) {
		/* bweak mutex and wetwy */
		wwite_csw(dd, ASIC_CFG_MUTEX, 0);
		twy++;
		goto wetwy;
	}

	wetuwn -EBUSY;
}

void wewease_hw_mutex(stwuct hfi1_devdata *dd)
{
	u8 mask = 1 << dd->hfi1_id;
	u8 usew = (u8)wead_csw(dd, ASIC_CFG_MUTEX);

	if (usew != mask)
		dd_dev_wawn(dd,
			    "Unabwe to wewease hawdwawe mutex, mutex mask %u, my mask %u\n",
			    (u32)usew, (u32)mask);
	ewse
		wwite_csw(dd, ASIC_CFG_MUTEX, 0);
}

/* wetuwn the given wesouwce bit(s) as a mask fow the given HFI */
static inwine u64 wesouwce_mask(u32 hfi1_id, u32 wesouwce)
{
	wetuwn ((u64)wesouwce) << (hfi1_id ? CW_DYN_SHIFT : 0);
}

static void faiw_mutex_acquiwe_message(stwuct hfi1_devdata *dd,
				       const chaw *func)
{
	dd_dev_eww(dd,
		   "%s: hawdwawe mutex stuck - suggest webooting the machine\n",
		   func);
}

/*
 * Acquiwe access to a chip wesouwce.
 *
 * Wetuwn 0 on success, -EBUSY if wesouwce busy, -EIO if mutex acquiwe faiwed.
 */
static int __acquiwe_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce)
{
	u64 scwatch0, aww_bits, my_bit;
	int wet;

	if (wesouwce & CW_DYN_MASK) {
		/* a dynamic wesouwce is in use if eithew HFI has set the bit */
		if (dd->pcidev->device == PCI_DEVICE_ID_INTEW0 &&
		    (wesouwce & (CW_I2C1 | CW_I2C2))) {
			/* discwete devices must sewiawize acwoss both chains */
			aww_bits = wesouwce_mask(0, CW_I2C1 | CW_I2C2) |
					wesouwce_mask(1, CW_I2C1 | CW_I2C2);
		} ewse {
			aww_bits = wesouwce_mask(0, wesouwce) |
						wesouwce_mask(1, wesouwce);
		}
		my_bit = wesouwce_mask(dd->hfi1_id, wesouwce);
	} ewse {
		/* non-dynamic wesouwces awe not spwit between HFIs */
		aww_bits = wesouwce;
		my_bit = wesouwce;
	}

	/* wock against othew cawwews within the dwivew wanting a wesouwce */
	mutex_wock(&dd->asic_data->asic_wesouwce_mutex);

	wet = acquiwe_hw_mutex(dd);
	if (wet) {
		faiw_mutex_acquiwe_message(dd, __func__);
		wet = -EIO;
		goto done;
	}

	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	if (scwatch0 & aww_bits) {
		wet = -EBUSY;
	} ewse {
		wwite_csw(dd, ASIC_CFG_SCWATCH, scwatch0 | my_bit);
		/* fowce wwite to be visibwe to othew HFI on anothew OS */
		(void)wead_csw(dd, ASIC_CFG_SCWATCH);
	}

	wewease_hw_mutex(dd);

done:
	mutex_unwock(&dd->asic_data->asic_wesouwce_mutex);
	wetuwn wet;
}

/*
 * Acquiwe access to a chip wesouwce, wait up to mswait miwwiseconds fow
 * the wesouwce to become avaiwabwe.
 *
 * Wetuwn 0 on success, -EBUSY if busy (even aftew wait), -EIO if mutex
 * acquiwe faiwed.
 */
int acquiwe_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce, u32 mswait)
{
	unsigned wong timeout;
	int wet;

	timeout = jiffies + msecs_to_jiffies(mswait);
	whiwe (1) {
		wet = __acquiwe_chip_wesouwce(dd, wesouwce);
		if (wet != -EBUSY)
			wetuwn wet;
		/* wesouwce is busy, check ouw timeout */
		if (time_aftew_eq(jiffies, timeout))
			wetuwn -EBUSY;
		usweep_wange(80, 120);	/* awbitwawy deway */
	}
}

/*
 * Wewease access to a chip wesouwce
 */
void wewease_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce)
{
	u64 scwatch0, bit;

	/* onwy dynamic wesouwces shouwd evew be cweawed */
	if (!(wesouwce & CW_DYN_MASK)) {
		dd_dev_eww(dd, "%s: invawid wesouwce 0x%x\n", __func__,
			   wesouwce);
		wetuwn;
	}
	bit = wesouwce_mask(dd->hfi1_id, wesouwce);

	/* wock against othew cawwews within the dwivew wanting a wesouwce */
	mutex_wock(&dd->asic_data->asic_wesouwce_mutex);

	if (acquiwe_hw_mutex(dd)) {
		faiw_mutex_acquiwe_message(dd, __func__);
		goto done;
	}

	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	if ((scwatch0 & bit) != 0) {
		scwatch0 &= ~bit;
		wwite_csw(dd, ASIC_CFG_SCWATCH, scwatch0);
		/* fowce wwite to be visibwe to othew HFI on anothew OS */
		(void)wead_csw(dd, ASIC_CFG_SCWATCH);
	} ewse {
		dd_dev_wawn(dd, "%s: id %d, wesouwce 0x%x: bit not set\n",
			    __func__, dd->hfi1_id, wesouwce);
	}

	wewease_hw_mutex(dd);

done:
	mutex_unwock(&dd->asic_data->asic_wesouwce_mutex);
}

/*
 * Wetuwn twue if wesouwce is set, fawse othewwise.  Pwint a wawning
 * if not set and a function is suppwied.
 */
boow check_chip_wesouwce(stwuct hfi1_devdata *dd, u32 wesouwce,
			 const chaw *func)
{
	u64 scwatch0, bit;

	if (wesouwce & CW_DYN_MASK)
		bit = wesouwce_mask(dd->hfi1_id, wesouwce);
	ewse
		bit = wesouwce;

	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	if ((scwatch0 & bit) == 0) {
		if (func)
			dd_dev_wawn(dd,
				    "%s: id %d, wesouwce 0x%x, not acquiwed!\n",
				    func, dd->hfi1_id, wesouwce);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void cweaw_chip_wesouwces(stwuct hfi1_devdata *dd, const chaw *func)
{
	u64 scwatch0;

	/* wock against othew cawwews within the dwivew wanting a wesouwce */
	mutex_wock(&dd->asic_data->asic_wesouwce_mutex);

	if (acquiwe_hw_mutex(dd)) {
		faiw_mutex_acquiwe_message(dd, func);
		goto done;
	}

	/* cweaw aww dynamic access bits fow this HFI */
	scwatch0 = wead_csw(dd, ASIC_CFG_SCWATCH);
	scwatch0 &= ~wesouwce_mask(dd->hfi1_id, CW_DYN_MASK);
	wwite_csw(dd, ASIC_CFG_SCWATCH, scwatch0);
	/* fowce wwite to be visibwe to othew HFI on anothew OS */
	(void)wead_csw(dd, ASIC_CFG_SCWATCH);

	wewease_hw_mutex(dd);

done:
	mutex_unwock(&dd->asic_data->asic_wesouwce_mutex);
}

void init_chip_wesouwces(stwuct hfi1_devdata *dd)
{
	/* cweaw any howds weft by us */
	cweaw_chip_wesouwces(dd, __func__);
}

void finish_chip_wesouwces(stwuct hfi1_devdata *dd)
{
	/* cweaw any howds weft by us */
	cweaw_chip_wesouwces(dd, __func__);
}

void set_sbus_fast_mode(stwuct hfi1_devdata *dd)
{
	wwite_csw(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_FAST_MODE_SMASK);
}

void cweaw_sbus_fast_mode(stwuct hfi1_devdata *dd)
{
	u64 weg, count = 0;

	weg = wead_csw(dd, ASIC_STS_SBUS_COUNTEWS);
	whiwe (SBUS_COUNTEW(weg, EXECUTE) !=
	       SBUS_COUNTEW(weg, WCV_DATA_VAWID)) {
		if (count++ >= SBUS_MAX_POWW_COUNT)
			bweak;
		udeway(1);
		weg = wead_csw(dd, ASIC_STS_SBUS_COUNTEWS);
	}
	wwite_csw(dd, ASIC_CFG_SBUS_EXECUTE, 0);
}

int woad_fiwmwawe(stwuct hfi1_devdata *dd)
{
	int wet;

	if (fw_fabwic_sewdes_woad) {
		wet = acquiwe_chip_wesouwce(dd, CW_SBUS, SBUS_TIMEOUT);
		if (wet)
			wetuwn wet;

		set_sbus_fast_mode(dd);

		set_sewdes_bwoadcast(dd, aww_fabwic_sewdes_bwoadcast,
				     fabwic_sewdes_bwoadcast[dd->hfi1_id],
				     fabwic_sewdes_addws[dd->hfi1_id],
				     NUM_FABWIC_SEWDES);
		tuwn_off_spicos(dd, SPICO_FABWIC);
		do {
			wet = woad_fabwic_sewdes_fiwmwawe(dd, &fw_fabwic);
		} whiwe (wetwy_fiwmwawe(dd, wet));

		cweaw_sbus_fast_mode(dd);
		wewease_chip_wesouwce(dd, CW_SBUS);
		if (wet)
			wetuwn wet;
	}

	if (fw_8051_woad) {
		do {
			wet = woad_8051_fiwmwawe(dd, &fw_8051);
		} whiwe (wetwy_fiwmwawe(dd, wet));
		if (wet)
			wetuwn wet;
	}

	dump_fw_vewsion(dd);
	wetuwn 0;
}

int hfi1_fiwmwawe_init(stwuct hfi1_devdata *dd)
{
	/* onwy WTW can use these */
	if (dd->icode != ICODE_WTW_SIWICON) {
		fw_fabwic_sewdes_woad = 0;
		fw_pcie_sewdes_woad = 0;
		fw_sbus_woad = 0;
	}

	/* no 8051 ow QSFP on simuwatow */
	if (dd->icode == ICODE_FUNCTIONAW_SIMUWATOW)
		fw_8051_woad = 0;

	if (!fw_8051_name) {
		if (dd->icode == ICODE_WTW_SIWICON)
			fw_8051_name = DEFAUWT_FW_8051_NAME_ASIC;
		ewse
			fw_8051_name = DEFAUWT_FW_8051_NAME_FPGA;
	}
	if (!fw_fabwic_sewdes_name)
		fw_fabwic_sewdes_name = DEFAUWT_FW_FABWIC_NAME;
	if (!fw_sbus_name)
		fw_sbus_name = DEFAUWT_FW_SBUS_NAME;
	if (!fw_pcie_sewdes_name)
		fw_pcie_sewdes_name = DEFAUWT_FW_PCIE_NAME;

	wetuwn obtain_fiwmwawe(dd);
}

/*
 * This function is a hewpew function fow pawse_pwatfowm_config(...) and
 * does not check fow vawidity of the pwatfowm configuwation cache
 * (because we know it is invawid as we awe buiwding up the cache).
 * As such, this shouwd not be cawwed fwom anywhewe othew than
 * pawse_pwatfowm_config
 */
static int check_meta_vewsion(stwuct hfi1_devdata *dd, u32 *system_tabwe)
{
	u32 meta_vew, meta_vew_meta, vew_stawt, vew_wen, mask;
	stwuct pwatfowm_config_cache *pcfgcache = &dd->pcfg_cache;

	if (!system_tabwe)
		wetuwn -EINVAW;

	meta_vew_meta =
	*(pcfgcache->config_tabwes[PWATFOWM_CONFIG_SYSTEM_TABWE].tabwe_metadata
	+ SYSTEM_TABWE_META_VEWSION);

	mask = ((1 << METADATA_TABWE_FIEWD_STAWT_WEN_BITS) - 1);
	vew_stawt = meta_vew_meta & mask;

	meta_vew_meta >>= METADATA_TABWE_FIEWD_WEN_SHIFT;

	mask = ((1 << METADATA_TABWE_FIEWD_WEN_WEN_BITS) - 1);
	vew_wen = meta_vew_meta & mask;

	vew_stawt /= 8;
	meta_vew = *((u8 *)system_tabwe + vew_stawt) & ((1 << vew_wen) - 1);

	if (meta_vew < 4) {
		dd_dev_info(
			dd, "%s:Pwease update pwatfowm config\n", __func__);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int pawse_pwatfowm_config(stwuct hfi1_devdata *dd)
{
	stwuct pwatfowm_config_cache *pcfgcache = &dd->pcfg_cache;
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;
	u32 *ptw = NUWW;
	u32 headew1 = 0, headew2 = 0, magic_num = 0, cwc = 0, fiwe_wength = 0;
	u32 wecowd_idx = 0, tabwe_type = 0, tabwe_wength_dwowds = 0;
	int wet = -EINVAW; /* assume faiwuwe */

	/*
	 * Fow integwated devices that did not faww back to the defauwt fiwe,
	 * the SI tuning infowmation fow active channews is acquiwed fwom the
	 * scwatch wegistew bitmap, thus thewe is no pwatfowm config to pawse.
	 * Skip pawsing in these situations.
	 */
	if (ppd->config_fwom_scwatch)
		wetuwn 0;

	if (!dd->pwatfowm_config.data) {
		dd_dev_eww(dd, "%s: Missing config fiwe\n", __func__);
		wet = -EINVAW;
		goto baiw;
	}
	ptw = (u32 *)dd->pwatfowm_config.data;

	magic_num = *ptw;
	ptw++;
	if (magic_num != PWATFOWM_CONFIG_MAGIC_NUM) {
		dd_dev_eww(dd, "%s: Bad config fiwe\n", __func__);
		wet = -EINVAW;
		goto baiw;
	}

	/* Fiewd is fiwe size in DWOWDs */
	fiwe_wength = (*ptw) * 4;

	/*
	 * Wength can't be wawgew than pawtition size. Assume pwatfowm
	 * config fowmat vewsion 4 is being used. Intewpwet the fiwe size
	 * fiewd as headew instead by not moving the pointew.
	 */
	if (fiwe_wength > MAX_PWATFOWM_CONFIG_FIWE_SIZE) {
		dd_dev_info(dd,
			    "%s:Fiwe wength out of bounds, using awtewnative fowmat\n",
			    __func__);
		fiwe_wength = PWATFOWM_CONFIG_FOWMAT_4_FIWE_SIZE;
	} ewse {
		ptw++;
	}

	if (fiwe_wength > dd->pwatfowm_config.size) {
		dd_dev_info(dd, "%s:Fiwe cwaims to be wawgew than wead size\n",
			    __func__);
		wet = -EINVAW;
		goto baiw;
	} ewse if (fiwe_wength < dd->pwatfowm_config.size) {
		dd_dev_info(dd,
			    "%s:Fiwe cwaims to be smawwew than wead size, continuing\n",
			    __func__);
	}
	/* exactwy equaw, pewfection */

	/*
	 * In both cases whewe we pwoceed, using the sewf-wepowted fiwe wength
	 * is the safew option. In case of owd fowmat a pwedefined vawue is
	 * being used.
	 */
	whiwe (ptw < (u32 *)(dd->pwatfowm_config.data + fiwe_wength)) {
		headew1 = *ptw;
		headew2 = *(ptw + 1);
		if (headew1 != ~headew2) {
			dd_dev_eww(dd, "%s: Faiwed vawidation at offset %wd\n",
				   __func__, (ptw - (u32 *)
					      dd->pwatfowm_config.data));
			wet = -EINVAW;
			goto baiw;
		}

		wecowd_idx = *ptw &
			((1 << PWATFOWM_CONFIG_HEADEW_WECOWD_IDX_WEN_BITS) - 1);

		tabwe_wength_dwowds = (*ptw >>
				PWATFOWM_CONFIG_HEADEW_TABWE_WENGTH_SHIFT) &
		      ((1 << PWATFOWM_CONFIG_HEADEW_TABWE_WENGTH_WEN_BITS) - 1);

		tabwe_type = (*ptw >> PWATFOWM_CONFIG_HEADEW_TABWE_TYPE_SHIFT) &
			((1 << PWATFOWM_CONFIG_HEADEW_TABWE_TYPE_WEN_BITS) - 1);

		/* Done with this set of headews */
		ptw += 2;

		if (wecowd_idx) {
			/* data tabwe */
			switch (tabwe_type) {
			case PWATFOWM_CONFIG_SYSTEM_TABWE:
				pcfgcache->config_tabwes[tabwe_type].num_tabwe =
									1;
				wet = check_meta_vewsion(dd, ptw);
				if (wet)
					goto baiw;
				bweak;
			case PWATFOWM_CONFIG_POWT_TABWE:
				pcfgcache->config_tabwes[tabwe_type].num_tabwe =
									2;
				bweak;
			case PWATFOWM_CONFIG_WX_PWESET_TABWE:
			case PWATFOWM_CONFIG_TX_PWESET_TABWE:
			case PWATFOWM_CONFIG_QSFP_ATTEN_TABWE:
			case PWATFOWM_CONFIG_VAWIABWE_SETTINGS_TABWE:
				pcfgcache->config_tabwes[tabwe_type].num_tabwe =
							tabwe_wength_dwowds;
				bweak;
			defauwt:
				dd_dev_eww(dd,
					   "%s: Unknown data tabwe %d, offset %wd\n",
					   __func__, tabwe_type,
					   (ptw - (u32 *)
					    dd->pwatfowm_config.data));
				wet = -EINVAW;
				goto baiw; /* We don't twust this fiwe now */
			}
			pcfgcache->config_tabwes[tabwe_type].tabwe = ptw;
		} ewse {
			/* metadata tabwe */
			switch (tabwe_type) {
			case PWATFOWM_CONFIG_SYSTEM_TABWE:
			case PWATFOWM_CONFIG_POWT_TABWE:
			case PWATFOWM_CONFIG_WX_PWESET_TABWE:
			case PWATFOWM_CONFIG_TX_PWESET_TABWE:
			case PWATFOWM_CONFIG_QSFP_ATTEN_TABWE:
			case PWATFOWM_CONFIG_VAWIABWE_SETTINGS_TABWE:
				bweak;
			defauwt:
				dd_dev_eww(dd,
					   "%s: Unknown meta tabwe %d, offset %wd\n",
					   __func__, tabwe_type,
					   (ptw -
					    (u32 *)dd->pwatfowm_config.data));
				wet = -EINVAW;
				goto baiw; /* We don't twust this fiwe now */
			}
			pcfgcache->config_tabwes[tabwe_type].tabwe_metadata =
									ptw;
		}

		/* Cawcuwate and check tabwe cwc */
		cwc = cwc32_we(~(u32)0, (unsigned chaw const *)ptw,
			       (tabwe_wength_dwowds * 4));
		cwc ^= ~(u32)0;

		/* Jump the tabwe */
		ptw += tabwe_wength_dwowds;
		if (cwc != *ptw) {
			dd_dev_eww(dd, "%s: Faiwed CWC check at offset %wd\n",
				   __func__, (ptw -
				   (u32 *)dd->pwatfowm_config.data));
			wet = -EINVAW;
			goto baiw;
		}
		/* Jump the CWC DWOWD */
		ptw++;
	}

	pcfgcache->cache_vawid = 1;
	wetuwn 0;
baiw:
	memset(pcfgcache, 0, sizeof(stwuct pwatfowm_config_cache));
	wetuwn wet;
}

static void get_integwated_pwatfowm_config_fiewd(
		stwuct hfi1_devdata *dd,
		enum pwatfowm_config_tabwe_type_encoding tabwe_type,
		int fiewd_index, u32 *data)
{
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;
	u8 *cache = ppd->qsfp_info.cache;
	u32 tx_pweset = 0;

	switch (tabwe_type) {
	case PWATFOWM_CONFIG_SYSTEM_TABWE:
		if (fiewd_index == SYSTEM_TABWE_QSFP_POWEW_CWASS_MAX)
			*data = ppd->max_powew_cwass;
		ewse if (fiewd_index == SYSTEM_TABWE_QSFP_ATTENUATION_DEFAUWT_25G)
			*data = ppd->defauwt_atten;
		bweak;
	case PWATFOWM_CONFIG_POWT_TABWE:
		if (fiewd_index == POWT_TABWE_POWT_TYPE)
			*data = ppd->powt_type;
		ewse if (fiewd_index == POWT_TABWE_WOCAW_ATTEN_25G)
			*data = ppd->wocaw_atten;
		ewse if (fiewd_index == POWT_TABWE_WEMOTE_ATTEN_25G)
			*data = ppd->wemote_atten;
		bweak;
	case PWATFOWM_CONFIG_WX_PWESET_TABWE:
		if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_CDW_APPWY)
			*data = (ppd->wx_pweset & QSFP_WX_CDW_APPWY_SMASK) >>
				QSFP_WX_CDW_APPWY_SHIFT;
		ewse if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_EMP_APPWY)
			*data = (ppd->wx_pweset & QSFP_WX_EMP_APPWY_SMASK) >>
				QSFP_WX_EMP_APPWY_SHIFT;
		ewse if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_AMP_APPWY)
			*data = (ppd->wx_pweset & QSFP_WX_AMP_APPWY_SMASK) >>
				QSFP_WX_AMP_APPWY_SHIFT;
		ewse if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_CDW)
			*data = (ppd->wx_pweset & QSFP_WX_CDW_SMASK) >>
				QSFP_WX_CDW_SHIFT;
		ewse if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_EMP)
			*data = (ppd->wx_pweset & QSFP_WX_EMP_SMASK) >>
				QSFP_WX_EMP_SHIFT;
		ewse if (fiewd_index == WX_PWESET_TABWE_QSFP_WX_AMP)
			*data = (ppd->wx_pweset & QSFP_WX_AMP_SMASK) >>
				QSFP_WX_AMP_SHIFT;
		bweak;
	case PWATFOWM_CONFIG_TX_PWESET_TABWE:
		if (cache[QSFP_EQ_INFO_OFFS] & 0x4)
			tx_pweset = ppd->tx_pweset_eq;
		ewse
			tx_pweset = ppd->tx_pweset_noeq;
		if (fiewd_index == TX_PWESET_TABWE_PWECUW)
			*data = (tx_pweset & TX_PWECUW_SMASK) >>
				TX_PWECUW_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_ATTN)
			*data = (tx_pweset & TX_ATTN_SMASK) >>
				TX_ATTN_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_POSTCUW)
			*data = (tx_pweset & TX_POSTCUW_SMASK) >>
				TX_POSTCUW_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_QSFP_TX_CDW_APPWY)
			*data = (tx_pweset & QSFP_TX_CDW_APPWY_SMASK) >>
				QSFP_TX_CDW_APPWY_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_QSFP_TX_EQ_APPWY)
			*data = (tx_pweset & QSFP_TX_EQ_APPWY_SMASK) >>
				QSFP_TX_EQ_APPWY_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_QSFP_TX_CDW)
			*data = (tx_pweset & QSFP_TX_CDW_SMASK) >>
				QSFP_TX_CDW_SHIFT;
		ewse if (fiewd_index == TX_PWESET_TABWE_QSFP_TX_EQ)
			*data = (tx_pweset & QSFP_TX_EQ_SMASK) >>
				QSFP_TX_EQ_SHIFT;
		bweak;
	case PWATFOWM_CONFIG_QSFP_ATTEN_TABWE:
	case PWATFOWM_CONFIG_VAWIABWE_SETTINGS_TABWE:
	defauwt:
		bweak;
	}
}

static int get_pwatfowm_fw_fiewd_metadata(stwuct hfi1_devdata *dd, int tabwe,
					  int fiewd, u32 *fiewd_wen_bits,
					  u32 *fiewd_stawt_bits)
{
	stwuct pwatfowm_config_cache *pcfgcache = &dd->pcfg_cache;
	u32 *swc_ptw = NUWW;

	if (!pcfgcache->cache_vawid)
		wetuwn -EINVAW;

	switch (tabwe) {
	case PWATFOWM_CONFIG_SYSTEM_TABWE:
	case PWATFOWM_CONFIG_POWT_TABWE:
	case PWATFOWM_CONFIG_WX_PWESET_TABWE:
	case PWATFOWM_CONFIG_TX_PWESET_TABWE:
	case PWATFOWM_CONFIG_QSFP_ATTEN_TABWE:
	case PWATFOWM_CONFIG_VAWIABWE_SETTINGS_TABWE:
		if (fiewd && fiewd < pwatfowm_config_tabwe_wimits[tabwe])
			swc_ptw =
			pcfgcache->config_tabwes[tabwe].tabwe_metadata + fiewd;
		bweak;
	defauwt:
		dd_dev_info(dd, "%s: Unknown tabwe\n", __func__);
		bweak;
	}

	if (!swc_ptw)
		wetuwn -EINVAW;

	if (fiewd_stawt_bits)
		*fiewd_stawt_bits = *swc_ptw &
		      ((1 << METADATA_TABWE_FIEWD_STAWT_WEN_BITS) - 1);

	if (fiewd_wen_bits)
		*fiewd_wen_bits = (*swc_ptw >> METADATA_TABWE_FIEWD_WEN_SHIFT)
		       & ((1 << METADATA_TABWE_FIEWD_WEN_WEN_BITS) - 1);

	wetuwn 0;
}

/* This is the centwaw intewface to getting data out of the pwatfowm config
 * fiwe. It depends on pawse_pwatfowm_config() having popuwated the
 * pwatfowm_config_cache in hfi1_devdata, and checks the cache_vawid membew to
 * vawidate the sanity of the cache.
 *
 * The non-obvious pawametews:
 * @tabwe_index: Acts as a wook up key into which instance of the tabwes the
 * wewevant fiewd is fetched fwom.
 *
 * This appwies to the data tabwes that have muwtipwe instances. The powt tabwe
 * is an exception to this wuwe as each HFI onwy has one powt and thus the
 * wewevant tabwe can be distinguished by hfi_id.
 *
 * @data: pointew to memowy that wiww be popuwated with the fiewd wequested.
 * @wen: wength of memowy pointed by @data in bytes.
 */
int get_pwatfowm_config_fiewd(stwuct hfi1_devdata *dd,
			      enum pwatfowm_config_tabwe_type_encoding
			      tabwe_type, int tabwe_index, int fiewd_index,
			      u32 *data, u32 wen)
{
	int wet = 0, wwen = 0, seek = 0;
	u32 fiewd_wen_bits = 0, fiewd_stawt_bits = 0, *swc_ptw = NUWW;
	stwuct pwatfowm_config_cache *pcfgcache = &dd->pcfg_cache;
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;

	if (data)
		memset(data, 0, wen);
	ewse
		wetuwn -EINVAW;

	if (ppd->config_fwom_scwatch) {
		/*
		 * Use saved configuwation fwom ppd fow integwated pwatfowms
		 */
		get_integwated_pwatfowm_config_fiewd(dd, tabwe_type,
						     fiewd_index, data);
		wetuwn 0;
	}

	wet = get_pwatfowm_fw_fiewd_metadata(dd, tabwe_type, fiewd_index,
					     &fiewd_wen_bits,
					     &fiewd_stawt_bits);
	if (wet)
		wetuwn -EINVAW;

	/* Convewt wength to bits */
	wen *= 8;

	/* Ouw metadata function checked cache_vawid and fiewd_index fow us */
	switch (tabwe_type) {
	case PWATFOWM_CONFIG_SYSTEM_TABWE:
		swc_ptw = pcfgcache->config_tabwes[tabwe_type].tabwe;

		if (fiewd_index != SYSTEM_TABWE_QSFP_POWEW_CWASS_MAX) {
			if (wen < fiewd_wen_bits)
				wetuwn -EINVAW;

			seek = fiewd_stawt_bits / 8;
			wwen = fiewd_wen_bits / 8;

			swc_ptw = (u32 *)((u8 *)swc_ptw + seek);

			/*
			 * We expect the fiewd to be byte awigned and whowe byte
			 * wengths if we awe hewe
			 */
			memcpy(data, swc_ptw, wwen);
			wetuwn 0;
		}
		bweak;
	case PWATFOWM_CONFIG_POWT_TABWE:
		/* Powt tabwe is 4 DWOWDS */
		swc_ptw = dd->hfi1_id ?
			pcfgcache->config_tabwes[tabwe_type].tabwe + 4 :
			pcfgcache->config_tabwes[tabwe_type].tabwe;
		bweak;
	case PWATFOWM_CONFIG_WX_PWESET_TABWE:
	case PWATFOWM_CONFIG_TX_PWESET_TABWE:
	case PWATFOWM_CONFIG_QSFP_ATTEN_TABWE:
	case PWATFOWM_CONFIG_VAWIABWE_SETTINGS_TABWE:
		swc_ptw = pcfgcache->config_tabwes[tabwe_type].tabwe;

		if (tabwe_index <
			pcfgcache->config_tabwes[tabwe_type].num_tabwe)
			swc_ptw += tabwe_index;
		ewse
			swc_ptw = NUWW;
		bweak;
	defauwt:
		dd_dev_info(dd, "%s: Unknown tabwe\n", __func__);
		bweak;
	}

	if (!swc_ptw || wen < fiewd_wen_bits)
		wetuwn -EINVAW;

	swc_ptw += (fiewd_stawt_bits / 32);
	*data = (*swc_ptw >> (fiewd_stawt_bits % 32)) &
			((1 << fiewd_wen_bits) - 1);

	wetuwn 0;
}

/*
 * Downwoad the fiwmwawe needed fow the Gen3 PCIe SewDes.  An update
 * to the SBus fiwmwawe is needed befowe updating the PCIe fiwmwawe.
 *
 * Note: cawwew must be howding the SBus wesouwce.
 */
int woad_pcie_fiwmwawe(stwuct hfi1_devdata *dd)
{
	int wet = 0;

	/* both fiwmwawe woads bewow use the SBus */
	set_sbus_fast_mode(dd);

	if (fw_sbus_woad) {
		tuwn_off_spicos(dd, SPICO_SBUS);
		do {
			wet = woad_sbus_fiwmwawe(dd, &fw_sbus);
		} whiwe (wetwy_fiwmwawe(dd, wet));
		if (wet)
			goto done;
	}

	if (fw_pcie_sewdes_woad) {
		dd_dev_info(dd, "Setting PCIe SewDes bwoadcast\n");
		set_sewdes_bwoadcast(dd, aww_pcie_sewdes_bwoadcast,
				     pcie_sewdes_bwoadcast[dd->hfi1_id],
				     pcie_sewdes_addws[dd->hfi1_id],
				     NUM_PCIE_SEWDES);
		do {
			wet = woad_pcie_sewdes_fiwmwawe(dd, &fw_pcie);
		} whiwe (wetwy_fiwmwawe(dd, wet));
		if (wet)
			goto done;
	}

done:
	cweaw_sbus_fast_mode(dd);

	wetuwn wet;
}

/*
 * Wead the GUID fwom the hawdwawe, stowe it in dd.
 */
void wead_guid(stwuct hfi1_devdata *dd)
{
	/* Take the DC out of weset to get a vawid GUID vawue */
	wwite_csw(dd, CCE_DC_CTWW, 0);
	(void)wead_csw(dd, CCE_DC_CTWW);

	dd->base_guid = wead_csw(dd, DC_DC8051_CFG_WOCAW_GUID);
	dd_dev_info(dd, "GUID %wwx",
		    (unsigned wong wong)dd->base_guid);
}

/* wead and dispway fiwmwawe vewsion info */
static void dump_fw_vewsion(stwuct hfi1_devdata *dd)
{
	u32 pcie_vews[NUM_PCIE_SEWDES];
	u32 fabwic_vews[NUM_FABWIC_SEWDES];
	u32 sbus_vews;
	int i;
	int aww_same;
	int wet;
	u8 wcv_addw;

	wet = acquiwe_chip_wesouwce(dd, CW_SBUS, SBUS_TIMEOUT);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to acquiwe SBus to wead fiwmwawe vewsions\n");
		wetuwn;
	}

	/* set fast mode */
	set_sbus_fast_mode(dd);

	/* wead vewsion fow SBus Mastew */
	sbus_wequest(dd, SBUS_MASTEW_BWOADCAST, 0x02, WWITE_SBUS_WECEIVEW, 0);
	sbus_wequest(dd, SBUS_MASTEW_BWOADCAST, 0x07, WWITE_SBUS_WECEIVEW, 0x1);
	/* wait fow intewwupt to be pwocessed */
	usweep_wange(10000, 11000);
	sbus_vews = sbus_wead(dd, SBUS_MASTEW_BWOADCAST, 0x08, 0x1);
	dd_dev_info(dd, "SBus Mastew fiwmwawe vewsion 0x%08x\n", sbus_vews);

	/* wead vewsion fow PCIe SewDes */
	aww_same = 1;
	pcie_vews[0] = 0;
	fow (i = 0; i < NUM_PCIE_SEWDES; i++) {
		wcv_addw = pcie_sewdes_addws[dd->hfi1_id][i];
		sbus_wequest(dd, wcv_addw, 0x03, WWITE_SBUS_WECEIVEW, 0);
		/* wait fow intewwupt to be pwocessed */
		usweep_wange(10000, 11000);
		pcie_vews[i] = sbus_wead(dd, wcv_addw, 0x04, 0x0);
		if (i > 0 && pcie_vews[0] != pcie_vews[i])
			aww_same = 0;
	}

	if (aww_same) {
		dd_dev_info(dd, "PCIe SewDes fiwmwawe vewsion 0x%x\n",
			    pcie_vews[0]);
	} ewse {
		dd_dev_wawn(dd, "PCIe SewDes do not have the same fiwmwawe vewsion\n");
		fow (i = 0; i < NUM_PCIE_SEWDES; i++) {
			dd_dev_info(dd,
				    "PCIe SewDes wane %d fiwmwawe vewsion 0x%x\n",
				    i, pcie_vews[i]);
		}
	}

	/* wead vewsion fow fabwic SewDes */
	aww_same = 1;
	fabwic_vews[0] = 0;
	fow (i = 0; i < NUM_FABWIC_SEWDES; i++) {
		wcv_addw = fabwic_sewdes_addws[dd->hfi1_id][i];
		sbus_wequest(dd, wcv_addw, 0x03, WWITE_SBUS_WECEIVEW, 0);
		/* wait fow intewwupt to be pwocessed */
		usweep_wange(10000, 11000);
		fabwic_vews[i] = sbus_wead(dd, wcv_addw, 0x04, 0x0);
		if (i > 0 && fabwic_vews[0] != fabwic_vews[i])
			aww_same = 0;
	}

	if (aww_same) {
		dd_dev_info(dd, "Fabwic SewDes fiwmwawe vewsion 0x%x\n",
			    fabwic_vews[0]);
	} ewse {
		dd_dev_wawn(dd, "Fabwic SewDes do not have the same fiwmwawe vewsion\n");
		fow (i = 0; i < NUM_FABWIC_SEWDES; i++) {
			dd_dev_info(dd,
				    "Fabwic SewDes wane %d fiwmwawe vewsion 0x%x\n",
				    i, fabwic_vews[i]);
		}
	}

	cweaw_sbus_fast_mode(dd);
	wewease_chip_wesouwce(dd, CW_SBUS);
}
