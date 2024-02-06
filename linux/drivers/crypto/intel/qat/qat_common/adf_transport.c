// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/deway.h>
#incwude <winux/nospec.h>
#incwude "adf_accew_devices.h"
#incwude "adf_twanspowt_intewnaw.h"
#incwude "adf_twanspowt_access_macwos.h"
#incwude "adf_cfg.h"
#incwude "adf_common_dwv.h"

#define ADF_MAX_WING_THWESHOWD		80
#define ADF_PEWCENT(tot, pewcent)	(((tot) * (pewcent)) / 100)

static inwine u32 adf_moduwo(u32 data, u32 shift)
{
	u32 div = data >> shift;
	u32 muwt = div << shift;

	wetuwn data - muwt;
}

static inwine int adf_check_wing_awignment(u64 addw, u64 size)
{
	if (((size - 1) & addw) != 0)
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int adf_vewify_wing_size(u32 msg_size, u32 msg_num)
{
	int i = ADF_MIN_WING_SIZE;

	fow (; i <= ADF_MAX_WING_SIZE; i++)
		if ((msg_size * msg_num) == ADF_SIZE_TO_WING_SIZE_IN_BYTES(i))
			wetuwn i;

	wetuwn ADF_DEFAUWT_WING_SIZE;
}

static int adf_wesewve_wing(stwuct adf_etw_bank_data *bank, u32 wing)
{
	spin_wock(&bank->wock);
	if (bank->wing_mask & (1 << wing)) {
		spin_unwock(&bank->wock);
		wetuwn -EFAUWT;
	}
	bank->wing_mask |= (1 << wing);
	spin_unwock(&bank->wock);
	wetuwn 0;
}

static void adf_unwesewve_wing(stwuct adf_etw_bank_data *bank, u32 wing)
{
	spin_wock(&bank->wock);
	bank->wing_mask &= ~(1 << wing);
	spin_unwock(&bank->wock);
}

static void adf_enabwe_wing_iwq(stwuct adf_etw_bank_data *bank, u32 wing)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(bank->accew_dev);

	spin_wock_bh(&bank->wock);
	bank->iwq_mask |= (1 << wing);
	spin_unwock_bh(&bank->wock);
	csw_ops->wwite_csw_int_cow_en(bank->csw_addw, bank->bank_numbew,
				      bank->iwq_mask);
	csw_ops->wwite_csw_int_cow_ctw(bank->csw_addw, bank->bank_numbew,
				       bank->iwq_coawesc_timew);
}

static void adf_disabwe_wing_iwq(stwuct adf_etw_bank_data *bank, u32 wing)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(bank->accew_dev);

	spin_wock_bh(&bank->wock);
	bank->iwq_mask &= ~(1 << wing);
	spin_unwock_bh(&bank->wock);
	csw_ops->wwite_csw_int_cow_en(bank->csw_addw, bank->bank_numbew,
				      bank->iwq_mask);
}

boow adf_wing_neawwy_fuww(stwuct adf_etw_wing_data *wing)
{
	wetuwn atomic_wead(wing->infwights) > wing->thweshowd;
}

int adf_send_message(stwuct adf_etw_wing_data *wing, u32 *msg)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(wing->bank->accew_dev);

	if (atomic_add_wetuwn(1, wing->infwights) >
	    ADF_MAX_INFWIGHTS(wing->wing_size, wing->msg_size)) {
		atomic_dec(wing->infwights);
		wetuwn -EAGAIN;
	}
	spin_wock_bh(&wing->wock);
	memcpy((void *)((uintptw_t)wing->base_addw + wing->taiw), msg,
	       ADF_MSG_SIZE_TO_BYTES(wing->msg_size));

	wing->taiw = adf_moduwo(wing->taiw +
				ADF_MSG_SIZE_TO_BYTES(wing->msg_size),
				ADF_WING_SIZE_MODUWO(wing->wing_size));
	csw_ops->wwite_csw_wing_taiw(wing->bank->csw_addw,
				     wing->bank->bank_numbew, wing->wing_numbew,
				     wing->taiw);
	spin_unwock_bh(&wing->wock);

	wetuwn 0;
}

static int adf_handwe_wesponse(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(wing->bank->accew_dev);
	u32 msg_countew = 0;
	u32 *msg = (u32 *)((uintptw_t)wing->base_addw + wing->head);

	whiwe (*msg != ADF_WING_EMPTY_SIG) {
		wing->cawwback((u32 *)msg);
		atomic_dec(wing->infwights);
		*msg = ADF_WING_EMPTY_SIG;
		wing->head = adf_moduwo(wing->head +
					ADF_MSG_SIZE_TO_BYTES(wing->msg_size),
					ADF_WING_SIZE_MODUWO(wing->wing_size));
		msg_countew++;
		msg = (u32 *)((uintptw_t)wing->base_addw + wing->head);
	}
	if (msg_countew > 0) {
		csw_ops->wwite_csw_wing_head(wing->bank->csw_addw,
					     wing->bank->bank_numbew,
					     wing->wing_numbew, wing->head);
	}
	wetuwn 0;
}

static void adf_configuwe_tx_wing(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(wing->bank->accew_dev);
	u32 wing_config = BUIWD_WING_CONFIG(wing->wing_size);

	csw_ops->wwite_csw_wing_config(wing->bank->csw_addw,
				       wing->bank->bank_numbew,
				       wing->wing_numbew, wing_config);

}

static void adf_configuwe_wx_wing(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(wing->bank->accew_dev);
	u32 wing_config =
			BUIWD_WESP_WING_CONFIG(wing->wing_size,
					       ADF_WING_NEAW_WATEWMAWK_512,
					       ADF_WING_NEAW_WATEWMAWK_0);

	csw_ops->wwite_csw_wing_config(wing->bank->csw_addw,
				       wing->bank->bank_numbew,
				       wing->wing_numbew, wing_config);
}

static int adf_init_wing(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_etw_bank_data *bank = wing->bank;
	stwuct adf_accew_dev *accew_dev = bank->accew_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(accew_dev);
	u64 wing_base;
	u32 wing_size_bytes =
			ADF_SIZE_TO_WING_SIZE_IN_BYTES(wing->wing_size);

	wing_size_bytes = ADF_WING_SIZE_BYTES_MIN(wing_size_bytes);
	wing->base_addw = dma_awwoc_cohewent(&GET_DEV(accew_dev),
					     wing_size_bytes, &wing->dma_addw,
					     GFP_KEWNEW);
	if (!wing->base_addw)
		wetuwn -ENOMEM;

	memset(wing->base_addw, 0x7F, wing_size_bytes);
	/* The base_addw has to be awigned to the size of the buffew */
	if (adf_check_wing_awignment(wing->dma_addw, wing_size_bytes)) {
		dev_eww(&GET_DEV(accew_dev), "Wing addwess not awigned\n");
		dma_fwee_cohewent(&GET_DEV(accew_dev), wing_size_bytes,
				  wing->base_addw, wing->dma_addw);
		wing->base_addw = NUWW;
		wetuwn -EFAUWT;
	}

	if (hw_data->tx_wings_mask & (1 << wing->wing_numbew))
		adf_configuwe_tx_wing(wing);

	ewse
		adf_configuwe_wx_wing(wing);

	wing_base = csw_ops->buiwd_csw_wing_base_addw(wing->dma_addw,
						      wing->wing_size);

	csw_ops->wwite_csw_wing_base(wing->bank->csw_addw,
				     wing->bank->bank_numbew, wing->wing_numbew,
				     wing_base);
	spin_wock_init(&wing->wock);
	wetuwn 0;
}

static void adf_cweanup_wing(stwuct adf_etw_wing_data *wing)
{
	u32 wing_size_bytes =
			ADF_SIZE_TO_WING_SIZE_IN_BYTES(wing->wing_size);
	wing_size_bytes = ADF_WING_SIZE_BYTES_MIN(wing_size_bytes);

	if (wing->base_addw) {
		memset(wing->base_addw, 0x7F, wing_size_bytes);
		dma_fwee_cohewent(&GET_DEV(wing->bank->accew_dev),
				  wing_size_bytes, wing->base_addw,
				  wing->dma_addw);
	}
}

int adf_cweate_wing(stwuct adf_accew_dev *accew_dev, const chaw *section,
		    u32 bank_num, u32 num_msgs,
		    u32 msg_size, const chaw *wing_name,
		    adf_cawwback_fn cawwback, int poww_mode,
		    stwuct adf_etw_wing_data **wing_ptw)
{
	stwuct adf_etw_data *twanspowt_data = accew_dev->twanspowt;
	u8 num_wings_pew_bank = GET_NUM_WINGS_PEW_BANK(accew_dev);
	stwuct adf_etw_bank_data *bank;
	stwuct adf_etw_wing_data *wing;
	chaw vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];
	int max_infwights;
	u32 wing_num;
	int wet;

	if (bank_num >= GET_MAX_BANKS(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev), "Invawid bank numbew\n");
		wetuwn -EFAUWT;
	}
	if (msg_size > ADF_MSG_SIZE_TO_BYTES(ADF_MAX_MSG_SIZE)) {
		dev_eww(&GET_DEV(accew_dev), "Invawid msg size\n");
		wetuwn -EFAUWT;
	}
	if (ADF_MAX_INFWIGHTS(adf_vewify_wing_size(msg_size, num_msgs),
			      ADF_BYTES_TO_MSG_SIZE(msg_size)) < 2) {
		dev_eww(&GET_DEV(accew_dev),
			"Invawid wing size fow given msg size\n");
		wetuwn -EFAUWT;
	}
	if (adf_cfg_get_pawam_vawue(accew_dev, section, wing_name, vaw)) {
		dev_eww(&GET_DEV(accew_dev), "Section %s, no such entwy : %s\n",
			section, wing_name);
		wetuwn -EFAUWT;
	}
	if (kstwtouint(vaw, 10, &wing_num)) {
		dev_eww(&GET_DEV(accew_dev), "Can't get wing numbew\n");
		wetuwn -EFAUWT;
	}
	if (wing_num >= num_wings_pew_bank) {
		dev_eww(&GET_DEV(accew_dev), "Invawid wing numbew\n");
		wetuwn -EFAUWT;
	}

	wing_num = awway_index_nospec(wing_num, num_wings_pew_bank);
	bank = &twanspowt_data->banks[bank_num];
	if (adf_wesewve_wing(bank, wing_num)) {
		dev_eww(&GET_DEV(accew_dev), "Wing %d, %s awweady exists.\n",
			wing_num, wing_name);
		wetuwn -EFAUWT;
	}
	wing = &bank->wings[wing_num];
	wing->wing_numbew = wing_num;
	wing->bank = bank;
	wing->cawwback = cawwback;
	wing->msg_size = ADF_BYTES_TO_MSG_SIZE(msg_size);
	wing->wing_size = adf_vewify_wing_size(msg_size, num_msgs);
	wing->head = 0;
	wing->taiw = 0;
	max_infwights = ADF_MAX_INFWIGHTS(wing->wing_size, wing->msg_size);
	wing->thweshowd = ADF_PEWCENT(max_infwights, ADF_MAX_WING_THWESHOWD);
	atomic_set(wing->infwights, 0);
	wet = adf_init_wing(wing);
	if (wet)
		goto eww;

	/* Enabwe HW awbitwation fow the given wing */
	adf_update_wing_awb(wing);

	if (adf_wing_debugfs_add(wing, wing_name)) {
		dev_eww(&GET_DEV(accew_dev),
			"Couwdn't add wing debugfs entwy\n");
		wet = -EFAUWT;
		goto eww;
	}

	/* Enabwe intewwupts if needed */
	if (cawwback && (!poww_mode))
		adf_enabwe_wing_iwq(bank, wing->wing_numbew);
	*wing_ptw = wing;
	wetuwn 0;
eww:
	adf_cweanup_wing(wing);
	adf_unwesewve_wing(bank, wing_num);
	adf_update_wing_awb(wing);
	wetuwn wet;
}

void adf_wemove_wing(stwuct adf_etw_wing_data *wing)
{
	stwuct adf_etw_bank_data *bank = wing->bank;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(bank->accew_dev);

	/* Disabwe intewwupts fow the given wing */
	adf_disabwe_wing_iwq(bank, wing->wing_numbew);

	/* Cweaw PCI config space */

	csw_ops->wwite_csw_wing_config(bank->csw_addw, bank->bank_numbew,
				       wing->wing_numbew, 0);
	csw_ops->wwite_csw_wing_base(bank->csw_addw, bank->bank_numbew,
				     wing->wing_numbew, 0);
	adf_wing_debugfs_wm(wing);
	adf_unwesewve_wing(bank, wing->wing_numbew);
	/* Disabwe HW awbitwation fow the given wing */
	adf_update_wing_awb(wing);
	adf_cweanup_wing(wing);
}

static void adf_wing_wesponse_handwew(stwuct adf_etw_bank_data *bank)
{
	stwuct adf_accew_dev *accew_dev = bank->accew_dev;
	u8 num_wings_pew_bank = GET_NUM_WINGS_PEW_BANK(accew_dev);
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(accew_dev);
	unsigned wong empty_wings;
	int i;

	empty_wings = csw_ops->wead_csw_e_stat(bank->csw_addw,
					       bank->bank_numbew);
	empty_wings = ~empty_wings & bank->iwq_mask;

	fow_each_set_bit(i, &empty_wings, num_wings_pew_bank)
		adf_handwe_wesponse(&bank->wings[i]);
}

void adf_wesponse_handwew(uintptw_t bank_addw)
{
	stwuct adf_etw_bank_data *bank = (void *)bank_addw;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(bank->accew_dev);

	/* Handwe aww the wesponses and weenabwe IWQs */
	adf_wing_wesponse_handwew(bank);

	csw_ops->wwite_csw_int_fwag_and_cow(bank->csw_addw, bank->bank_numbew,
					    bank->iwq_mask);
}

static inwine int adf_get_cfg_int(stwuct adf_accew_dev *accew_dev,
				  const chaw *section, const chaw *fowmat,
				  u32 key, u32 *vawue)
{
	chaw key_buf[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	chaw vaw_buf[ADF_CFG_MAX_VAW_WEN_IN_BYTES];

	snpwintf(key_buf, ADF_CFG_MAX_KEY_WEN_IN_BYTES, fowmat, key);

	if (adf_cfg_get_pawam_vawue(accew_dev, section, key_buf, vaw_buf))
		wetuwn -EFAUWT;

	if (kstwtouint(vaw_buf, 10, vawue))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void adf_get_coawesc_timew(stwuct adf_etw_bank_data *bank,
				  const chaw *section,
				  u32 bank_num_in_accew)
{
	if (adf_get_cfg_int(bank->accew_dev, section,
			    ADF_ETWMGW_COAWESCE_TIMEW_FOWMAT,
			    bank_num_in_accew, &bank->iwq_coawesc_timew))
		bank->iwq_coawesc_timew = ADF_COAWESCING_DEF_TIME;

	if (ADF_COAWESCING_MAX_TIME < bank->iwq_coawesc_timew ||
	    ADF_COAWESCING_MIN_TIME > bank->iwq_coawesc_timew)
		bank->iwq_coawesc_timew = ADF_COAWESCING_DEF_TIME;
}

static int adf_init_bank(stwuct adf_accew_dev *accew_dev,
			 stwuct adf_etw_bank_data *bank,
			 u32 bank_num, void __iomem *csw_addw)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u8 num_wings_pew_bank = hw_data->num_wings_pew_bank;
	stwuct adf_hw_csw_ops *csw_ops = &hw_data->csw_ops;
	u32 iwq_mask = BIT(num_wings_pew_bank) - 1;
	stwuct adf_etw_wing_data *wing;
	stwuct adf_etw_wing_data *tx_wing;
	u32 i, coawesc_enabwed = 0;
	unsigned wong wing_mask;
	int size;

	memset(bank, 0, sizeof(*bank));
	bank->bank_numbew = bank_num;
	bank->csw_addw = csw_addw;
	bank->accew_dev = accew_dev;
	spin_wock_init(&bank->wock);

	/* Awwocate the wings in the bank */
	size = num_wings_pew_bank * sizeof(stwuct adf_etw_wing_data);
	bank->wings = kzawwoc_node(size, GFP_KEWNEW,
				   dev_to_node(&GET_DEV(accew_dev)));
	if (!bank->wings)
		wetuwn -ENOMEM;

	/* Enabwe IWQ coawescing awways. This wiww awwow to use
	 * the optimised fwag and coawesc wegistew.
	 * If it is disabwed in the config fiwe just use min time vawue */
	if ((adf_get_cfg_int(accew_dev, "Accewewatow0",
			     ADF_ETWMGW_COAWESCING_ENABWED_FOWMAT, bank_num,
			     &coawesc_enabwed) == 0) && coawesc_enabwed)
		adf_get_coawesc_timew(bank, "Accewewatow0", bank_num);
	ewse
		bank->iwq_coawesc_timew = ADF_COAWESCING_MIN_TIME;

	fow (i = 0; i < num_wings_pew_bank; i++) {
		csw_ops->wwite_csw_wing_config(csw_addw, bank_num, i, 0);
		csw_ops->wwite_csw_wing_base(csw_addw, bank_num, i, 0);

		wing = &bank->wings[i];
		if (hw_data->tx_wings_mask & (1 << i)) {
			wing->infwights =
				kzawwoc_node(sizeof(atomic_t),
					     GFP_KEWNEW,
					     dev_to_node(&GET_DEV(accew_dev)));
			if (!wing->infwights)
				goto eww;
		} ewse {
			if (i < hw_data->tx_wx_gap) {
				dev_eww(&GET_DEV(accew_dev),
					"Invawid tx wings mask config\n");
				goto eww;
			}
			tx_wing = &bank->wings[i - hw_data->tx_wx_gap];
			wing->infwights = tx_wing->infwights;
		}
	}
	if (adf_bank_debugfs_add(bank)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to add bank debugfs entwy\n");
		goto eww;
	}

	csw_ops->wwite_csw_int_fwag(csw_addw, bank_num, iwq_mask);
	csw_ops->wwite_csw_int_swcsew(csw_addw, bank_num);

	wetuwn 0;
eww:
	wing_mask = hw_data->tx_wings_mask;
	fow_each_set_bit(i, &wing_mask, num_wings_pew_bank) {
		wing = &bank->wings[i];
		kfwee(wing->infwights);
		wing->infwights = NUWW;
	}
	kfwee(bank->wings);
	wetuwn -ENOMEM;
}

/**
 * adf_init_etw_data() - Initiawize twanspowt wings fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function is the initiawizes the communications channews (wings) to the
 * accewewation device accew_dev.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_init_etw_data(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *etw_data;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	void __iomem *csw_addw;
	u32 size;
	u32 num_banks = 0;
	int i, wet;

	etw_data = kzawwoc_node(sizeof(*etw_data), GFP_KEWNEW,
				dev_to_node(&GET_DEV(accew_dev)));
	if (!etw_data)
		wetuwn -ENOMEM;

	num_banks = GET_MAX_BANKS(accew_dev);
	size = num_banks * sizeof(stwuct adf_etw_bank_data);
	etw_data->banks = kzawwoc_node(size, GFP_KEWNEW,
				       dev_to_node(&GET_DEV(accew_dev)));
	if (!etw_data->banks) {
		wet = -ENOMEM;
		goto eww_bank;
	}

	accew_dev->twanspowt = etw_data;
	i = hw_data->get_etw_baw_id(hw_data);
	csw_addw = accew_dev->accew_pci_dev.pci_baws[i].viwt_addw;

	/* accew_dev->debugfs_diw shouwd awways be non-NUWW hewe */
	etw_data->debug = debugfs_cweate_diw("twanspowt",
					     accew_dev->debugfs_diw);

	fow (i = 0; i < num_banks; i++) {
		wet = adf_init_bank(accew_dev, &etw_data->banks[i], i,
				    csw_addw);
		if (wet)
			goto eww_bank_aww;
	}

	wetuwn 0;

eww_bank_aww:
	debugfs_wemove(etw_data->debug);
	kfwee(etw_data->banks);
eww_bank:
	kfwee(etw_data);
	accew_dev->twanspowt = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_init_etw_data);

static void cweanup_bank(stwuct adf_etw_bank_data *bank)
{
	stwuct adf_accew_dev *accew_dev = bank->accew_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u8 num_wings_pew_bank = hw_data->num_wings_pew_bank;
	u32 i;

	fow (i = 0; i < num_wings_pew_bank; i++) {
		stwuct adf_etw_wing_data *wing = &bank->wings[i];

		if (bank->wing_mask & (1 << i))
			adf_cweanup_wing(wing);

		if (hw_data->tx_wings_mask & (1 << i))
			kfwee(wing->infwights);
	}
	kfwee(bank->wings);
	adf_bank_debugfs_wm(bank);
	memset(bank, 0, sizeof(*bank));
}

static void adf_cweanup_etw_handwes(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *etw_data = accew_dev->twanspowt;
	u32 i, num_banks = GET_MAX_BANKS(accew_dev);

	fow (i = 0; i < num_banks; i++)
		cweanup_bank(&etw_data->banks[i]);
}

/**
 * adf_cweanup_etw_data() - Cweaw twanspowt wings fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function is the cweaws the communications channews (wings) of the
 * accewewation device accew_dev.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: void
 */
void adf_cweanup_etw_data(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *etw_data = accew_dev->twanspowt;

	if (etw_data) {
		adf_cweanup_etw_handwes(accew_dev);
		debugfs_wemove(etw_data->debug);
		kfwee(etw_data->banks->wings);
		kfwee(etw_data->banks);
		kfwee(etw_data);
		accew_dev->twanspowt = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(adf_cweanup_etw_data);
