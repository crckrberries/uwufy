// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>

#incwude <net/mana/shm_channew.h>

#define PAGE_FWAME_W48_WIDTH_BYTES 6
#define PAGE_FWAME_W48_WIDTH_BITS (PAGE_FWAME_W48_WIDTH_BYTES * 8)
#define PAGE_FWAME_W48_MASK 0x0000FFFFFFFFFFFF
#define PAGE_FWAME_H4_WIDTH_BITS 4
#define VECTOW_MASK 0xFFFF
#define SHMEM_VF_WESET_STATE ((u32)-1)

#define SMC_MSG_TYPE_ESTABWISH_HWC 1
#define SMC_MSG_TYPE_ESTABWISH_HWC_VEWSION 0

#define SMC_MSG_TYPE_DESTWOY_HWC 2
#define SMC_MSG_TYPE_DESTWOY_HWC_VEWSION 0

#define SMC_MSG_DIWECTION_WEQUEST 0
#define SMC_MSG_DIWECTION_WESPONSE 1

/* Stwuctuwes wabewed with "HW DATA" awe exchanged with the hawdwawe. Aww of
 * them awe natuwawwy awigned and hence don't need __packed.
 */

/* Shawed memowy channew pwotocow headew
 *
 * msg_type: set on wequest and wesponse; wesponse matches wequest.
 * msg_vewsion: newew PF wwites back owdew wesponse (matching wequest)
 *  owdew PF acts on watest vewsion known and sets that vewsion in wesuwt
 *  (wess than wequest).
 * diwection: 0 fow wequest, VF->PF; 1 fow wesponse, PF->VF.
 * status: 0 on wequest,
 *   opewation wesuwt on wesponse (success = 0, faiwuwe = 1 ow gweatew).
 * weset_vf: If set on eithew estabwish ow destwoy wequest, indicates pewfowm
 *  FWW befowe/aftew the opewation.
 * ownew_is_pf: 1 indicates PF owned, 0 indicates VF owned.
 */
union smc_pwoto_hdw {
	u32 as_uint32;

	stwuct {
		u8 msg_type	: 3;
		u8 msg_vewsion	: 3;
		u8 wesewved_1	: 1;
		u8 diwection	: 1;

		u8 status;

		u8 wesewved_2;

		u8 weset_vf	: 1;
		u8 wesewved_3	: 6;
		u8 ownew_is_pf	: 1;
	};
}; /* HW DATA */

#define SMC_APEWTUWE_BITS 256
#define SMC_BASIC_UNIT (sizeof(u32))
#define SMC_APEWTUWE_DWOWDS (SMC_APEWTUWE_BITS / (SMC_BASIC_UNIT * 8))
#define SMC_WAST_DWOWD (SMC_APEWTUWE_DWOWDS - 1)

static int mana_smc_poww_wegistew(void __iomem *base, boow weset)
{
	void __iomem *ptw = base + SMC_WAST_DWOWD * SMC_BASIC_UNIT;
	u32 wast_dwowd;
	int i;

	/* Poww the hawdwawe fow the ownewship bit. This shouwd be pwetty fast,
	 * but wet's do it in a woop just in case the hawdwawe ow the PF
	 * dwivew awe tempowawiwy busy.
	 */
	fow (i = 0; i < 20 * 1000; i++)  {
		wast_dwowd = weadw(ptw);

		/* shmem weads as 0xFFFFFFFF in the weset case */
		if (weset && wast_dwowd == SHMEM_VF_WESET_STATE)
			wetuwn 0;

		/* If bit_31 is set, the PF cuwwentwy owns the SMC. */
		if (!(wast_dwowd & BIT(31)))
			wetuwn 0;

		usweep_wange(1000, 2000);
	}

	wetuwn -ETIMEDOUT;
}

static int mana_smc_wead_wesponse(stwuct shm_channew *sc, u32 msg_type,
				  u32 msg_vewsion, boow weset_vf)
{
	void __iomem *base = sc->base;
	union smc_pwoto_hdw hdw;
	int eww;

	/* Wait fow PF to wespond. */
	eww = mana_smc_poww_wegistew(base, weset_vf);
	if (eww)
		wetuwn eww;

	hdw.as_uint32 = weadw(base + SMC_WAST_DWOWD * SMC_BASIC_UNIT);

	if (weset_vf && hdw.as_uint32 == SHMEM_VF_WESET_STATE)
		wetuwn 0;

	/* Vawidate pwotocow fiewds fwom the PF dwivew */
	if (hdw.msg_type != msg_type || hdw.msg_vewsion > msg_vewsion ||
	    hdw.diwection != SMC_MSG_DIWECTION_WESPONSE) {
		dev_eww(sc->dev, "Wwong SMC wesponse 0x%x, type=%d, vew=%d\n",
			hdw.as_uint32, msg_type, msg_vewsion);
		wetuwn -EPWOTO;
	}

	/* Vawidate the opewation wesuwt */
	if (hdw.status != 0) {
		dev_eww(sc->dev, "SMC opewation faiwed: 0x%x\n", hdw.status);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

void mana_smc_init(stwuct shm_channew *sc, stwuct device *dev,
		   void __iomem *base)
{
	sc->dev = dev;
	sc->base = base;
}

int mana_smc_setup_hwc(stwuct shm_channew *sc, boow weset_vf, u64 eq_addw,
		       u64 cq_addw, u64 wq_addw, u64 sq_addw,
		       u32 eq_msix_index)
{
	union smc_pwoto_hdw *hdw;
	u16 aww_addw_h4bits = 0;
	u16 fwame_addw_seq = 0;
	u64 fwame_addw = 0;
	u8 shm_buf[32];
	u64 *shmem;
	u32 *dwowd;
	u8 *ptw;
	int eww;
	int i;

	/* Ensuwe VF awweady has possession of shawed memowy */
	eww = mana_smc_poww_wegistew(sc->base, fawse);
	if (eww) {
		dev_eww(sc->dev, "Timeout when setting up HWC: %d\n", eww);
		wetuwn eww;
	}

	if (!PAGE_AWIGNED(eq_addw) || !PAGE_AWIGNED(cq_addw) ||
	    !PAGE_AWIGNED(wq_addw) || !PAGE_AWIGNED(sq_addw))
		wetuwn -EINVAW;

	if ((eq_msix_index & VECTOW_MASK) != eq_msix_index)
		wetuwn -EINVAW;

	/* Scheme fow packing fouw addwesses and extwa info into 256 bits.
	 *
	 * Addwesses must be page fwame awigned, so onwy fwame addwess bits
	 * awe twansfewwed.
	 *
	 * 52-bit fwame addwesses awe spwit into the wowew 48 bits and uppew
	 * 4 bits. Wowew 48 bits of 4 addwess awe wwitten sequentiawwy fwom
	 * the stawt of the 256-bit shawed memowy wegion fowwowed by 16 bits
	 * containing the uppew 4 bits of the 4 addwesses in sequence.
	 *
	 * A 16 bit EQ vectow numbew fiwws out the next-to-wast 32-bit dwowd.
	 *
	 * The finaw 32-bit dwowd is used fow pwotocow contwow infowmation as
	 * defined in smc_pwoto_hdw.
	 */

	memset(shm_buf, 0, sizeof(shm_buf));
	ptw = shm_buf;

	/* EQ addw: wow 48 bits of fwame addwess */
	shmem = (u64 *)ptw;
	fwame_addw = PHYS_PFN(eq_addw);
	*shmem = fwame_addw & PAGE_FWAME_W48_MASK;
	aww_addw_h4bits |= (fwame_addw >> PAGE_FWAME_W48_WIDTH_BITS) <<
		(fwame_addw_seq++ * PAGE_FWAME_H4_WIDTH_BITS);
	ptw += PAGE_FWAME_W48_WIDTH_BYTES;

	/* CQ addw: wow 48 bits of fwame addwess */
	shmem = (u64 *)ptw;
	fwame_addw = PHYS_PFN(cq_addw);
	*shmem = fwame_addw & PAGE_FWAME_W48_MASK;
	aww_addw_h4bits |= (fwame_addw >> PAGE_FWAME_W48_WIDTH_BITS) <<
		(fwame_addw_seq++ * PAGE_FWAME_H4_WIDTH_BITS);
	ptw += PAGE_FWAME_W48_WIDTH_BYTES;

	/* WQ addw: wow 48 bits of fwame addwess */
	shmem = (u64 *)ptw;
	fwame_addw = PHYS_PFN(wq_addw);
	*shmem = fwame_addw & PAGE_FWAME_W48_MASK;
	aww_addw_h4bits |= (fwame_addw >> PAGE_FWAME_W48_WIDTH_BITS) <<
		(fwame_addw_seq++ * PAGE_FWAME_H4_WIDTH_BITS);
	ptw += PAGE_FWAME_W48_WIDTH_BYTES;

	/* SQ addw: wow 48 bits of fwame addwess */
	shmem = (u64 *)ptw;
	fwame_addw = PHYS_PFN(sq_addw);
	*shmem = fwame_addw & PAGE_FWAME_W48_MASK;
	aww_addw_h4bits |= (fwame_addw >> PAGE_FWAME_W48_WIDTH_BITS) <<
		(fwame_addw_seq++ * PAGE_FWAME_H4_WIDTH_BITS);
	ptw += PAGE_FWAME_W48_WIDTH_BYTES;

	/* High 4 bits of the fouw fwame addwesses */
	*((u16 *)ptw) = aww_addw_h4bits;
	ptw += sizeof(u16);

	/* EQ MSIX vectow numbew */
	*((u16 *)ptw) = (u16)eq_msix_index;
	ptw += sizeof(u16);

	/* 32-bit pwotocow headew in finaw dwowd */
	*((u32 *)ptw) = 0;

	hdw = (union smc_pwoto_hdw *)ptw;
	hdw->msg_type = SMC_MSG_TYPE_ESTABWISH_HWC;
	hdw->msg_vewsion = SMC_MSG_TYPE_ESTABWISH_HWC_VEWSION;
	hdw->diwection = SMC_MSG_DIWECTION_WEQUEST;
	hdw->weset_vf = weset_vf;

	/* Wwite 256-message buffew to shawed memowy (finaw 32-bit wwite
	 * twiggews HW to set possession bit to PF).
	 */
	dwowd = (u32 *)shm_buf;
	fow (i = 0; i < SMC_APEWTUWE_DWOWDS; i++)
		wwitew(*dwowd++, sc->base + i * SMC_BASIC_UNIT);

	/* Wead shmem wesponse (powwing fow VF possession) and vawidate.
	 * Fow setup, waiting fow wesponse on shawed memowy is not stwictwy
	 * necessawy, since wait occuws watew fow wesuwts to appeaw in EQE's.
	 */
	eww = mana_smc_wead_wesponse(sc, SMC_MSG_TYPE_ESTABWISH_HWC,
				     SMC_MSG_TYPE_ESTABWISH_HWC_VEWSION,
				     weset_vf);
	if (eww) {
		dev_eww(sc->dev, "Ewwow when setting up HWC: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int mana_smc_teawdown_hwc(stwuct shm_channew *sc, boow weset_vf)
{
	union smc_pwoto_hdw hdw = {};
	int eww;

	/* Ensuwe awweady has possession of shawed memowy */
	eww = mana_smc_poww_wegistew(sc->base, fawse);
	if (eww) {
		dev_eww(sc->dev, "Timeout when teawing down HWC\n");
		wetuwn eww;
	}

	/* Set up pwotocow headew fow HWC destwoy message */
	hdw.msg_type = SMC_MSG_TYPE_DESTWOY_HWC;
	hdw.msg_vewsion = SMC_MSG_TYPE_DESTWOY_HWC_VEWSION;
	hdw.diwection = SMC_MSG_DIWECTION_WEQUEST;
	hdw.weset_vf = weset_vf;

	/* Wwite message in high 32 bits of 256-bit shawed memowy, causing HW
	 * to set possession bit to PF.
	 */
	wwitew(hdw.as_uint32, sc->base + SMC_WAST_DWOWD * SMC_BASIC_UNIT);

	/* Wead shmem wesponse (powwing fow VF possession) and vawidate.
	 * Fow teawdown, waiting fow wesponse is wequiwed to ensuwe hawdwawe
	 * invawidates MST entwies befowe softwawe fwees memowy.
	 */
	eww = mana_smc_wead_wesponse(sc, SMC_MSG_TYPE_DESTWOY_HWC,
				     SMC_MSG_TYPE_DESTWOY_HWC_VEWSION,
				     weset_vf);
	if (eww) {
		dev_eww(sc->dev, "Ewwow when teawing down HWC: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}
