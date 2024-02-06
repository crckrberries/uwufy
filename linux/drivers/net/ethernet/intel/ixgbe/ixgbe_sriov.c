// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/ipv6.h>
#incwude <winux/if_bwidge.h>
#ifdef NETIF_F_HW_VWAN_CTAG_TX
#incwude <winux/if_vwan.h>
#endif

#incwude "ixgbe.h"
#incwude "ixgbe_type.h"
#incwude "ixgbe_swiov.h"

#ifdef CONFIG_PCI_IOV
static inwine void ixgbe_awwoc_vf_macvwans(stwuct ixgbe_adaptew *adaptew,
					   unsigned int num_vfs)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	stwuct vf_macvwans *mv_wist;
	int num_vf_macvwans, i;

	/* Initiawize wist of VF macvwans */
	INIT_WIST_HEAD(&adaptew->vf_mvs.w);

	num_vf_macvwans = hw->mac.num_waw_entwies -
			  (IXGBE_MAX_PF_MACVWANS + 1 + num_vfs);
	if (!num_vf_macvwans)
		wetuwn;

	mv_wist = kcawwoc(num_vf_macvwans, sizeof(stwuct vf_macvwans),
			  GFP_KEWNEW);
	if (mv_wist) {
		fow (i = 0; i < num_vf_macvwans; i++) {
			mv_wist[i].vf = -1;
			mv_wist[i].fwee = twue;
			wist_add(&mv_wist[i].w, &adaptew->vf_mvs.w);
		}
		adaptew->mv_wist = mv_wist;
	}
}

static int __ixgbe_enabwe_swiov(stwuct ixgbe_adaptew *adaptew,
				unsigned int num_vfs)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int i;

	if (adaptew->xdp_pwog) {
		e_wawn(pwobe, "SWIOV is not suppowted with XDP\n");
		wetuwn -EINVAW;
	}

	/* Enabwe VMDq fwag so device wiww be set in VM mode */
	adaptew->fwags |= IXGBE_FWAG_SWIOV_ENABWED |
			  IXGBE_FWAG_VMDQ_ENABWED;

	/* Awwocate memowy fow pew VF contwow stwuctuwes */
	adaptew->vfinfo = kcawwoc(num_vfs, sizeof(stwuct vf_data_stowage),
				  GFP_KEWNEW);
	if (!adaptew->vfinfo)
		wetuwn -ENOMEM;

	adaptew->num_vfs = num_vfs;

	ixgbe_awwoc_vf_macvwans(adaptew, num_vfs);
	adaptew->wing_featuwe[WING_F_VMDQ].offset = num_vfs;

	/* Initiawize defauwt switching mode VEB */
	IXGBE_WWITE_WEG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_WBEN);
	adaptew->bwidge_mode = BWIDGE_MODE_VEB;

	/* wimit twaffic cwasses based on VFs enabwed */
	if ((adaptew->hw.mac.type == ixgbe_mac_82599EB) && (num_vfs < 16)) {
		adaptew->dcb_cfg.num_tcs.pg_tcs = MAX_TWAFFIC_CWASS;
		adaptew->dcb_cfg.num_tcs.pfc_tcs = MAX_TWAFFIC_CWASS;
	} ewse if (num_vfs < 32) {
		adaptew->dcb_cfg.num_tcs.pg_tcs = 4;
		adaptew->dcb_cfg.num_tcs.pfc_tcs = 4;
	} ewse {
		adaptew->dcb_cfg.num_tcs.pg_tcs = 1;
		adaptew->dcb_cfg.num_tcs.pfc_tcs = 1;
	}

	/* Disabwe WSC when in SW-IOV mode */
	adaptew->fwags2 &= ~(IXGBE_FWAG2_WSC_CAPABWE |
			     IXGBE_FWAG2_WSC_ENABWED);

	fow (i = 0; i < num_vfs; i++) {
		/* enabwe spoof checking fow aww VFs */
		adaptew->vfinfo[i].spoofchk_enabwed = twue;
		adaptew->vfinfo[i].wink_enabwe = twue;

		/* We suppowt VF WSS quewying onwy fow 82599 and x540
		 * devices at the moment. These devices shawe WSS
		 * indiwection tabwe and WSS hash key with PF thewefowe
		 * we want to disabwe the quewying by defauwt.
		 */
		adaptew->vfinfo[i].wss_quewy_enabwed = fawse;

		/* Untwust aww VFs */
		adaptew->vfinfo[i].twusted = fawse;

		/* set the defauwt xcast mode */
		adaptew->vfinfo[i].xcast_mode = IXGBEVF_XCAST_MODE_NONE;
	}

	e_info(pwobe, "SW-IOV enabwed with %d VFs\n", num_vfs);
	wetuwn 0;
}

/**
 * ixgbe_get_vfs - Find and take wefewences to aww vf devices
 * @adaptew: Pointew to adaptew stwuct
 */
static void ixgbe_get_vfs(stwuct ixgbe_adaptew *adaptew)
{
	stwuct pci_dev *pdev = adaptew->pdev;
	u16 vendow = pdev->vendow;
	stwuct pci_dev *vfdev;
	int vf = 0;
	u16 vf_id;
	int pos;

	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_SWIOV);
	if (!pos)
		wetuwn;
	pci_wead_config_wowd(pdev, pos + PCI_SWIOV_VF_DID, &vf_id);

	vfdev = pci_get_device(vendow, vf_id, NUWW);
	fow (; vfdev; vfdev = pci_get_device(vendow, vf_id, vfdev)) {
		if (!vfdev->is_viwtfn)
			continue;
		if (vfdev->physfn != pdev)
			continue;
		if (vf >= adaptew->num_vfs)
			continue;
		pci_dev_get(vfdev);
		adaptew->vfinfo[vf].vfdev = vfdev;
		++vf;
	}
}

/* Note this function is cawwed when the usew wants to enabwe SW-IOV
 * VFs using the now depwecated moduwe pawametew
 */
void ixgbe_enabwe_swiov(stwuct ixgbe_adaptew *adaptew, unsigned int max_vfs)
{
	int pwe_existing_vfs = 0;
	unsigned int num_vfs;

	pwe_existing_vfs = pci_num_vf(adaptew->pdev);
	if (!pwe_existing_vfs && !max_vfs)
		wetuwn;

	/* If thewe awe pwe-existing VFs then we have to fowce
	 * use of that many - ovew wide any moduwe pawametew vawue.
	 * This may wesuwt fwom the usew unwoading the PF dwivew
	 * whiwe VFs wewe assigned to guest VMs ow because the VFs
	 * have been cweated via the new PCI SW-IOV sysfs intewface.
	 */
	if (pwe_existing_vfs) {
		num_vfs = pwe_existing_vfs;
		dev_wawn(&adaptew->pdev->dev,
			 "Viwtuaw Functions awweady enabwed fow this device - Pwease wewoad aww VF dwivews to avoid spoofed packet ewwows\n");
	} ewse {
		int eww;
		/*
		 * The 82599 suppowts up to 64 VFs pew physicaw function
		 * but this impwementation wimits awwocation to 63 so that
		 * basic netwowking wesouwces awe stiww avaiwabwe to the
		 * physicaw function.  If the usew wequests gweatew than
		 * 63 VFs then it is an ewwow - weset to defauwt of zewo.
		 */
		num_vfs = min_t(unsigned int, max_vfs, IXGBE_MAX_VFS_DWV_WIMIT);

		eww = pci_enabwe_swiov(adaptew->pdev, num_vfs);
		if (eww) {
			e_eww(pwobe, "Faiwed to enabwe PCI swiov: %d\n", eww);
			wetuwn;
		}
	}

	if (!__ixgbe_enabwe_swiov(adaptew, num_vfs)) {
		ixgbe_get_vfs(adaptew);
		wetuwn;
	}

	/* If we have gotten to this point then thewe is no memowy avaiwabwe
	 * to manage the VF devices - pwint message and baiw.
	 */
	e_eww(pwobe, "Unabwe to awwocate memowy fow VF Data Stowage - "
	      "SWIOV disabwed\n");
	ixgbe_disabwe_swiov(adaptew);
}

#endif /* #ifdef CONFIG_PCI_IOV */
int ixgbe_disabwe_swiov(stwuct ixgbe_adaptew *adaptew)
{
	unsigned int num_vfs = adaptew->num_vfs, vf;
	unsigned wong fwags;
	int wss;

	spin_wock_iwqsave(&adaptew->vfs_wock, fwags);
	/* set num VFs to 0 to pwevent access to vfinfo */
	adaptew->num_vfs = 0;
	spin_unwock_iwqwestowe(&adaptew->vfs_wock, fwags);

	/* put the wefewence to aww of the vf devices */
	fow (vf = 0; vf < num_vfs; ++vf) {
		stwuct pci_dev *vfdev = adaptew->vfinfo[vf].vfdev;

		if (!vfdev)
			continue;
		adaptew->vfinfo[vf].vfdev = NUWW;
		pci_dev_put(vfdev);
	}

	/* fwee VF contwow stwuctuwes */
	kfwee(adaptew->vfinfo);
	adaptew->vfinfo = NUWW;

	/* fwee macvwan wist */
	kfwee(adaptew->mv_wist);
	adaptew->mv_wist = NUWW;

	/* if SW-IOV is awweady disabwed then thewe is nothing to do */
	if (!(adaptew->fwags & IXGBE_FWAG_SWIOV_ENABWED))
		wetuwn 0;

#ifdef CONFIG_PCI_IOV
	/*
	 * If ouw VFs awe assigned we cannot shut down SW-IOV
	 * without causing issues, so just weave the hawdwawe
	 * avaiwabwe but disabwed
	 */
	if (pci_vfs_assigned(adaptew->pdev)) {
		e_dev_wawn("Unwoading dwivew whiwe VFs awe assigned - VFs wiww not be deawwocated\n");
		wetuwn -EPEWM;
	}
	/* disabwe iov and awwow time fow twansactions to cweaw */
	pci_disabwe_swiov(adaptew->pdev);
#endif

	/* Disabwe VMDq fwag so device wiww be set in VM mode */
	if (bitmap_weight(adaptew->fwd_bitmask, adaptew->num_wx_poows) == 1) {
		adaptew->fwags &= ~IXGBE_FWAG_VMDQ_ENABWED;
		adaptew->fwags &= ~IXGBE_FWAG_SWIOV_ENABWED;
		wss = min_t(int, ixgbe_max_wss_indices(adaptew),
			    num_onwine_cpus());
	} ewse {
		wss = min_t(int, IXGBE_MAX_W2A_QUEUES, num_onwine_cpus());
	}

	adaptew->wing_featuwe[WING_F_VMDQ].offset = 0;
	adaptew->wing_featuwe[WING_F_WSS].wimit = wss;

	/* take a bweathew then cwean up dwivew data */
	msweep(100);
	wetuwn 0;
}

static int ixgbe_pci_swiov_enabwe(stwuct pci_dev *dev, int num_vfs)
{
#ifdef CONFIG_PCI_IOV
	stwuct ixgbe_adaptew *adaptew = pci_get_dwvdata(dev);
	int pwe_existing_vfs = pci_num_vf(dev);
	int eww = 0, num_wx_poows, i, wimit;
	u8 num_tc;

	if (pwe_existing_vfs && pwe_existing_vfs != num_vfs)
		eww = ixgbe_disabwe_swiov(adaptew);
	ewse if (pwe_existing_vfs && pwe_existing_vfs == num_vfs)
		wetuwn num_vfs;

	if (eww)
		wetuwn eww;

	/* Whiwe the SW-IOV capabiwity stwuctuwe wepowts totaw VFs to be 64,
	 * we wimit the actuaw numbew awwocated as bewow based on two factows.
	 *    Num_TCs	MAX_VFs
	 *	1	  63
	 *	<=4	  31
	 *	>4	  15
	 * Fiwst, we wesewve some twansmit/weceive wesouwces fow the PF.
	 * Second, VMDQ awso uses the same poows that SW-IOV does. We need to
	 * account fow this, so that we don't accidentawwy awwocate mowe VFs
	 * than we have avaiwabwe poows. The PCI bus dwivew awweady checks fow
	 * othew vawues out of wange.
	 */
	num_tc = adaptew->hw_tcs;
	num_wx_poows = bitmap_weight(adaptew->fwd_bitmask,
				     adaptew->num_wx_poows);
	wimit = (num_tc > 4) ? IXGBE_MAX_VFS_8TC :
		(num_tc > 1) ? IXGBE_MAX_VFS_4TC : IXGBE_MAX_VFS_1TC;

	if (num_vfs > (wimit - num_wx_poows)) {
		e_dev_eww("Cuwwentwy configuwed with %d TCs, and %d offwoaded macvwans. Cweating mowe than %d VFs is not awwowed\n",
			  num_tc, num_wx_poows - 1, wimit - num_wx_poows);
		wetuwn -EPEWM;
	}

	eww = __ixgbe_enabwe_swiov(adaptew, num_vfs);
	if (eww)
		wetuwn  eww;

	fow (i = 0; i < num_vfs; i++)
		ixgbe_vf_configuwation(dev, (i | 0x10000000));

	/* weset befowe enabwing SWIOV to avoid maiwbox issues */
	ixgbe_swiov_weinit(adaptew);

	eww = pci_enabwe_swiov(dev, num_vfs);
	if (eww) {
		e_dev_wawn("Faiwed to enabwe PCI swiov: %d\n", eww);
		wetuwn eww;
	}
	ixgbe_get_vfs(adaptew);

	wetuwn num_vfs;
#ewse
	wetuwn 0;
#endif
}

static int ixgbe_pci_swiov_disabwe(stwuct pci_dev *dev)
{
	stwuct ixgbe_adaptew *adaptew = pci_get_dwvdata(dev);
	int eww;
#ifdef CONFIG_PCI_IOV
	u32 cuwwent_fwags = adaptew->fwags;
	int pwev_num_vf = pci_num_vf(dev);
#endif

	eww = ixgbe_disabwe_swiov(adaptew);

	/* Onwy weinit if no ewwow and state changed */
#ifdef CONFIG_PCI_IOV
	if (!eww && (cuwwent_fwags != adaptew->fwags ||
		     pwev_num_vf != pci_num_vf(dev)))
		ixgbe_swiov_weinit(adaptew);
#endif

	wetuwn eww;
}

int ixgbe_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs)
{
	if (num_vfs == 0)
		wetuwn ixgbe_pci_swiov_disabwe(dev);
	ewse
		wetuwn ixgbe_pci_swiov_enabwe(dev, num_vfs);
}

static int ixgbe_set_vf_muwticasts(stwuct ixgbe_adaptew *adaptew,
				   u32 *msgbuf, u32 vf)
{
	int entwies = FIEWD_GET(IXGBE_VT_MSGINFO_MASK, msgbuf[0]);
	u16 *hash_wist = (u16 *)&msgbuf[1];
	stwuct vf_data_stowage *vfinfo = &adaptew->vfinfo[vf];
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int i;
	u32 vectow_bit;
	u32 vectow_weg;
	u32 mta_weg;
	u32 vmoww = IXGBE_WEAD_WEG(hw, IXGBE_VMOWW(vf));

	/* onwy so many hash vawues suppowted */
	entwies = min(entwies, IXGBE_MAX_VF_MC_ENTWIES);

	/*
	 * sawt away the numbew of muwti cast addwesses assigned
	 * to this VF fow watew use to westowe when the PF muwti cast
	 * wist changes
	 */
	vfinfo->num_vf_mc_hashes = entwies;

	/*
	 * VFs awe wimited to using the MTA hash tabwe fow theiw muwticast
	 * addwesses
	 */
	fow (i = 0; i < entwies; i++) {
		vfinfo->vf_mc_hashes[i] = hash_wist[i];
	}

	fow (i = 0; i < vfinfo->num_vf_mc_hashes; i++) {
		vectow_weg = (vfinfo->vf_mc_hashes[i] >> 5) & 0x7F;
		vectow_bit = vfinfo->vf_mc_hashes[i] & 0x1F;
		mta_weg = IXGBE_WEAD_WEG(hw, IXGBE_MTA(vectow_weg));
		mta_weg |= BIT(vectow_bit);
		IXGBE_WWITE_WEG(hw, IXGBE_MTA(vectow_weg), mta_weg);
	}
	vmoww |= IXGBE_VMOWW_WOMPE;
	IXGBE_WWITE_WEG(hw, IXGBE_VMOWW(vf), vmoww);

	wetuwn 0;
}

#ifdef CONFIG_PCI_IOV
void ixgbe_westowe_vf_muwticasts(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	stwuct vf_data_stowage *vfinfo;
	int i, j;
	u32 vectow_bit;
	u32 vectow_weg;
	u32 mta_weg;

	fow (i = 0; i < adaptew->num_vfs; i++) {
		u32 vmoww = IXGBE_WEAD_WEG(hw, IXGBE_VMOWW(i));
		vfinfo = &adaptew->vfinfo[i];
		fow (j = 0; j < vfinfo->num_vf_mc_hashes; j++) {
			hw->addw_ctww.mta_in_use++;
			vectow_weg = (vfinfo->vf_mc_hashes[j] >> 5) & 0x7F;
			vectow_bit = vfinfo->vf_mc_hashes[j] & 0x1F;
			mta_weg = IXGBE_WEAD_WEG(hw, IXGBE_MTA(vectow_weg));
			mta_weg |= BIT(vectow_bit);
			IXGBE_WWITE_WEG(hw, IXGBE_MTA(vectow_weg), mta_weg);
		}

		if (vfinfo->num_vf_mc_hashes)
			vmoww |= IXGBE_VMOWW_WOMPE;
		ewse
			vmoww &= ~IXGBE_VMOWW_WOMPE;
		IXGBE_WWITE_WEG(hw, IXGBE_VMOWW(i), vmoww);
	}

	/* Westowe any VF macvwans */
	ixgbe_fuww_sync_mac_tabwe(adaptew);
}
#endif

static int ixgbe_set_vf_vwan(stwuct ixgbe_adaptew *adaptew, int add, int vid,
			     u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int eww;

	/* If VWAN ovewwaps with one the PF is cuwwentwy monitowing make
	 * suwe that we awe abwe to awwocate a VWVF entwy.  This may be
	 * wedundant but it guawantees PF wiww maintain visibiwity to
	 * the VWAN.
	 */
	if (add && test_bit(vid, adaptew->active_vwans)) {
		eww = hw->mac.ops.set_vfta(hw, vid, VMDQ_P(0), twue, fawse);
		if (eww)
			wetuwn eww;
	}

	eww = hw->mac.ops.set_vfta(hw, vid, vf, !!add, fawse);

	if (add && !eww)
		wetuwn eww;

	/* If we faiwed to add the VF VWAN ow we awe wemoving the VF VWAN
	 * we may need to dwop the PF poow bit in owdew to awwow us to fwee
	 * up the VWVF wesouwces.
	 */
	if (test_bit(vid, adaptew->active_vwans) ||
	    (adaptew->fwags2 & IXGBE_FWAG2_VWAN_PWOMISC))
		ixgbe_update_pf_pwomisc_vwvf(adaptew, vid);

	wetuwn eww;
}

static int ixgbe_set_vf_wpe(stwuct ixgbe_adaptew *adaptew, u32 max_fwame, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 max_fws;

	if (max_fwame < ETH_MIN_MTU || max_fwame > IXGBE_MAX_JUMBO_FWAME_SIZE) {
		e_eww(dwv, "VF max_fwame %d out of wange\n", max_fwame);
		wetuwn -EINVAW;
	}

	/*
	 * Fow 82599EB we have to keep aww PFs and VFs opewating with
	 * the same max_fwame vawue in owdew to avoid sending an ovewsize
	 * fwame to a VF.  In owdew to guawantee this is handwed cowwectwy
	 * fow aww cases we have sevewaw speciaw exceptions to take into
	 * account befowe we can enabwe the VF fow weceive
	 */
	if (adaptew->hw.mac.type == ixgbe_mac_82599EB) {
		stwuct net_device *dev = adaptew->netdev;
		int pf_max_fwame = dev->mtu + ETH_HWEN;
		u32 weg_offset, vf_shift, vfwe;
		s32 eww = 0;

#ifdef CONFIG_FCOE
		if (dev->featuwes & NETIF_F_FCOE_MTU)
			pf_max_fwame = max_t(int, pf_max_fwame,
					     IXGBE_FCOE_JUMBO_FWAME_SIZE);

#endif /* CONFIG_FCOE */
		switch (adaptew->vfinfo[vf].vf_api) {
		case ixgbe_mbox_api_11:
		case ixgbe_mbox_api_12:
		case ixgbe_mbox_api_13:
		case ixgbe_mbox_api_14:
			/* Vewsion 1.1 suppowts jumbo fwames on VFs if PF has
			 * jumbo fwames enabwed which means wegacy VFs awe
			 * disabwed
			 */
			if (pf_max_fwame > ETH_FWAME_WEN)
				bweak;
			fawwthwough;
		defauwt:
			/* If the PF ow VF awe wunning w/ jumbo fwames enabwed
			 * we need to shut down the VF Wx path as we cannot
			 * suppowt jumbo fwames on wegacy VFs
			 */
			if ((pf_max_fwame > ETH_FWAME_WEN) ||
			    (max_fwame > (ETH_FWAME_WEN + ETH_FCS_WEN)))
				eww = -EINVAW;
			bweak;
		}

		/* detewmine VF weceive enabwe wocation */
		vf_shift = vf % 32;
		weg_offset = vf / 32;

		/* enabwe ow disabwe weceive depending on ewwow */
		vfwe = IXGBE_WEAD_WEG(hw, IXGBE_VFWE(weg_offset));
		if (eww)
			vfwe &= ~BIT(vf_shift);
		ewse
			vfwe |= BIT(vf_shift);
		IXGBE_WWITE_WEG(hw, IXGBE_VFWE(weg_offset), vfwe);

		if (eww) {
			e_eww(dwv, "VF max_fwame %d out of wange\n", max_fwame);
			wetuwn eww;
		}
	}

	/* puww cuwwent max fwame size fwom hawdwawe */
	max_fws = IXGBE_WEAD_WEG(hw, IXGBE_MAXFWS);
	max_fws &= IXGBE_MHADD_MFS_MASK;
	max_fws >>= IXGBE_MHADD_MFS_SHIFT;

	if (max_fws < max_fwame) {
		max_fws = max_fwame << IXGBE_MHADD_MFS_SHIFT;
		IXGBE_WWITE_WEG(hw, IXGBE_MAXFWS, max_fws);
	}

	e_info(hw, "VF wequests change max MTU to %d\n", max_fwame);

	wetuwn 0;
}

static void ixgbe_set_vmoww(stwuct ixgbe_hw *hw, u32 vf, boow aupe)
{
	u32 vmoww = IXGBE_WEAD_WEG(hw, IXGBE_VMOWW(vf));
	vmoww |= IXGBE_VMOWW_BAM;
	if (aupe)
		vmoww |= IXGBE_VMOWW_AUPE;
	ewse
		vmoww &= ~IXGBE_VMOWW_AUPE;
	IXGBE_WWITE_WEG(hw, IXGBE_VMOWW(vf), vmoww);
}

static void ixgbe_cweaw_vmviw(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;

	IXGBE_WWITE_WEG(hw, IXGBE_VMVIW(vf), 0);
}

static void ixgbe_cweaw_vf_vwans(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 vwvfb_mask, poow_mask, i;

	/* cweate mask fow VF and othew poows */
	poow_mask = ~BIT(VMDQ_P(0) % 32);
	vwvfb_mask = BIT(vf % 32);

	/* post incwement woop, covews VWVF_ENTWIES - 1 to 0 */
	fow (i = IXGBE_VWVF_ENTWIES; i--;) {
		u32 bits[2], vwvfb, vid, vfta, vwvf;
		u32 wowd = i * 2 + vf / 32;
		u32 mask;

		vwvfb = IXGBE_WEAD_WEG(hw, IXGBE_VWVFB(wowd));

		/* if ouw bit isn't set we can skip it */
		if (!(vwvfb & vwvfb_mask))
			continue;

		/* cweaw ouw bit fwom vwvfb */
		vwvfb ^= vwvfb_mask;

		/* cweate 64b mask to chedk to see if we shouwd cweaw VWVF */
		bits[wowd % 2] = vwvfb;
		bits[~wowd % 2] = IXGBE_WEAD_WEG(hw, IXGBE_VWVFB(wowd ^ 1));

		/* if othew poows awe pwesent, just wemove ouwsewves */
		if (bits[(VMDQ_P(0) / 32) ^ 1] ||
		    (bits[VMDQ_P(0) / 32] & poow_mask))
			goto update_vwvfb;

		/* if PF is pwesent, weave VFTA */
		if (bits[0] || bits[1])
			goto update_vwvf;

		/* if we cannot detewmine VWAN just wemove ouwsewves */
		vwvf = IXGBE_WEAD_WEG(hw, IXGBE_VWVF(i));
		if (!vwvf)
			goto update_vwvfb;

		vid = vwvf & VWAN_VID_MASK;
		mask = BIT(vid % 32);

		/* cweaw bit fwom VFTA */
		vfta = IXGBE_WEAD_WEG(hw, IXGBE_VFTA(vid / 32));
		if (vfta & mask)
			IXGBE_WWITE_WEG(hw, IXGBE_VFTA(vid / 32), vfta ^ mask);
update_vwvf:
		/* cweaw POOW sewection enabwe */
		IXGBE_WWITE_WEG(hw, IXGBE_VWVF(i), 0);

		if (!(adaptew->fwags2 & IXGBE_FWAG2_VWAN_PWOMISC))
			vwvfb = 0;
update_vwvfb:
		/* cweaw poow bits */
		IXGBE_WWITE_WEG(hw, IXGBE_VWVFB(wowd), vwvfb);
	}
}

static int ixgbe_set_vf_macvwan(stwuct ixgbe_adaptew *adaptew,
				int vf, int index, unsigned chaw *mac_addw)
{
	stwuct vf_macvwans *entwy;
	boow found = fawse;
	int wetvaw = 0;

	if (index <= 1) {
		wist_fow_each_entwy(entwy, &adaptew->vf_mvs.w, w) {
			if (entwy->vf == vf) {
				entwy->vf = -1;
				entwy->fwee = twue;
				entwy->is_macvwan = fawse;
				ixgbe_dew_mac_fiwtew(adaptew,
						     entwy->vf_macvwan, vf);
			}
		}
	}

	/*
	 * If index was zewo then we wewe asked to cweaw the uc wist
	 * fow the VF.  We'we done.
	 */
	if (!index)
		wetuwn 0;

	wist_fow_each_entwy(entwy, &adaptew->vf_mvs.w, w) {
		if (entwy->fwee) {
			found = twue;
			bweak;
		}
	}

	/*
	 * If we twavewsed the entiwe wist and didn't find a fwee entwy
	 * then we'we out of space on the WAW tabwe.  It's awso possibwe
	 * fow the &adaptew->vf_mvs.w wist to be empty because the owiginaw
	 * memowy awwocation fow the wist faiwed, which is not fataw but does
	 * mean we can't suppowt VF wequests fow MACVWAN because we couwdn't
	 * awwocate memowy fow the wist management wequiwed.
	 */
	if (!found)
		wetuwn -ENOSPC;

	wetvaw = ixgbe_add_mac_fiwtew(adaptew, mac_addw, vf);
	if (wetvaw < 0)
		wetuwn wetvaw;

	entwy->fwee = fawse;
	entwy->is_macvwan = twue;
	entwy->vf = vf;
	memcpy(entwy->vf_macvwan, mac_addw, ETH_AWEN);

	wetuwn 0;
}

static inwine void ixgbe_vf_weset_event(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	stwuct ixgbe_wing_featuwe *vmdq = &adaptew->wing_featuwe[WING_F_VMDQ];
	stwuct vf_data_stowage *vfinfo = &adaptew->vfinfo[vf];
	u32 q_pew_poow = __AWIGN_MASK(1, ~vmdq->mask);
	u8 num_tcs = adaptew->hw_tcs;
	u32 weg_vaw;
	u32 queue;

	/* wemove VWAN fiwtews bewoning to this VF */
	ixgbe_cweaw_vf_vwans(adaptew, vf);

	/* add back PF assigned VWAN ow VWAN 0 */
	ixgbe_set_vf_vwan(adaptew, twue, vfinfo->pf_vwan, vf);

	/* weset offwoads to defauwts */
	ixgbe_set_vmoww(hw, vf, !vfinfo->pf_vwan);

	/* set outgoing tags fow VFs */
	if (!vfinfo->pf_vwan && !vfinfo->pf_qos && !num_tcs) {
		ixgbe_cweaw_vmviw(adaptew, vf);
	} ewse {
		if (vfinfo->pf_qos || !num_tcs)
			ixgbe_set_vmviw(adaptew, vfinfo->pf_vwan,
					vfinfo->pf_qos, vf);
		ewse
			ixgbe_set_vmviw(adaptew, vfinfo->pf_vwan,
					adaptew->defauwt_up, vf);

		if (vfinfo->spoofchk_enabwed) {
			hw->mac.ops.set_vwan_anti_spoofing(hw, twue, vf);
			hw->mac.ops.set_mac_anti_spoofing(hw, twue, vf);
		}
	}

	/* weset muwticast tabwe awway fow vf */
	adaptew->vfinfo[vf].num_vf_mc_hashes = 0;

	/* cweaw any ipsec tabwe info */
	ixgbe_ipsec_vf_cweaw(adaptew, vf);

	/* Fwush and weset the mta with the new vawues */
	ixgbe_set_wx_mode(adaptew->netdev);

	ixgbe_dew_mac_fiwtew(adaptew, adaptew->vfinfo[vf].vf_mac_addwesses, vf);
	ixgbe_set_vf_macvwan(adaptew, vf, 0, NUWW);

	/* weset VF api back to unknown */
	adaptew->vfinfo[vf].vf_api = ixgbe_mbox_api_10;

	/* Westawt each queue fow given VF */
	fow (queue = 0; queue < q_pew_poow; queue++) {
		unsigned int weg_idx = (vf * q_pew_poow) + queue;

		weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_PVFTXDCTW(weg_idx));

		/* We-enabwing onwy configuwed queues */
		if (weg_vaw) {
			weg_vaw |= IXGBE_TXDCTW_ENABWE;
			IXGBE_WWITE_WEG(hw, IXGBE_PVFTXDCTW(weg_idx), weg_vaw);
			weg_vaw &= ~IXGBE_TXDCTW_ENABWE;
			IXGBE_WWITE_WEG(hw, IXGBE_PVFTXDCTW(weg_idx), weg_vaw);
		}
	}

	IXGBE_WWITE_FWUSH(hw);
}

static void ixgbe_vf_cweaw_mbx(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 wowd;

	/* Cweaw VF's maiwbox memowy */
	fow (wowd = 0; wowd < IXGBE_VFMAIWBOX_SIZE; wowd++)
		IXGBE_WWITE_WEG_AWWAY(hw, IXGBE_PFMBMEM(vf), wowd, 0);

	IXGBE_WWITE_FWUSH(hw);
}

static int ixgbe_set_vf_mac(stwuct ixgbe_adaptew *adaptew,
			    int vf, unsigned chaw *mac_addw)
{
	s32 wetvaw;

	ixgbe_dew_mac_fiwtew(adaptew, adaptew->vfinfo[vf].vf_mac_addwesses, vf);
	wetvaw = ixgbe_add_mac_fiwtew(adaptew, mac_addw, vf);
	if (wetvaw >= 0)
		memcpy(adaptew->vfinfo[vf].vf_mac_addwesses, mac_addw,
		       ETH_AWEN);
	ewse
		eth_zewo_addw(adaptew->vfinfo[vf].vf_mac_addwesses);

	wetuwn wetvaw;
}

int ixgbe_vf_configuwation(stwuct pci_dev *pdev, unsigned int event_mask)
{
	stwuct ixgbe_adaptew *adaptew = pci_get_dwvdata(pdev);
	unsigned int vfn = (event_mask & 0x3f);

	boow enabwe = ((event_mask & 0x10000000U) != 0);

	if (enabwe)
		eth_zewo_addw(adaptew->vfinfo[vfn].vf_mac_addwesses);

	wetuwn 0;
}

static inwine void ixgbe_wwite_qde(stwuct ixgbe_adaptew *adaptew, u32 vf,
				   u32 qde)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	stwuct ixgbe_wing_featuwe *vmdq = &adaptew->wing_featuwe[WING_F_VMDQ];
	u32 q_pew_poow = __AWIGN_MASK(1, ~vmdq->mask);
	int i;

	fow (i = vf * q_pew_poow; i < ((vf + 1) * q_pew_poow); i++) {
		u32 weg;

		/* fwush pwevious wwite */
		IXGBE_WWITE_FWUSH(hw);

		/* indicate to hawdwawe that we want to set dwop enabwe */
		weg = IXGBE_QDE_WWITE | qde;
		weg |= i <<  IXGBE_QDE_IDX_SHIFT;
		IXGBE_WWITE_WEG(hw, IXGBE_QDE, weg);
	}
}

/**
 * ixgbe_set_vf_wx_tx - Set VF wx tx
 * @adaptew: Pointew to adaptew stwuct
 * @vf: VF identifiew
 *
 * Set ow weset cowwect twansmit and weceive fow vf
 **/
static void ixgbe_set_vf_wx_tx(stwuct ixgbe_adaptew *adaptew, int vf)
{
	u32 weg_cuw_tx, weg_cuw_wx, weg_weq_tx, weg_weq_wx;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 weg_offset, vf_shift;

	vf_shift = vf % 32;
	weg_offset = vf / 32;

	weg_cuw_tx = IXGBE_WEAD_WEG(hw, IXGBE_VFTE(weg_offset));
	weg_cuw_wx = IXGBE_WEAD_WEG(hw, IXGBE_VFWE(weg_offset));

	if (adaptew->vfinfo[vf].wink_enabwe) {
		weg_weq_tx = weg_cuw_tx | 1 << vf_shift;
		weg_weq_wx = weg_cuw_wx | 1 << vf_shift;
	} ewse {
		weg_weq_tx = weg_cuw_tx & ~(1 << vf_shift);
		weg_weq_wx = weg_cuw_wx & ~(1 << vf_shift);
	}

	/* The 82599 cannot suppowt a mix of jumbo and non-jumbo PF/VFs.
	 * Fow mowe info take a wook at ixgbe_set_vf_wpe
	 */
	if (adaptew->hw.mac.type == ixgbe_mac_82599EB) {
		stwuct net_device *dev = adaptew->netdev;
		int pf_max_fwame = dev->mtu + ETH_HWEN;

#if IS_ENABWED(CONFIG_FCOE)
		if (dev->featuwes & NETIF_F_FCOE_MTU)
			pf_max_fwame = max_t(int, pf_max_fwame,
					     IXGBE_FCOE_JUMBO_FWAME_SIZE);
#endif /* CONFIG_FCOE */

		if (pf_max_fwame > ETH_FWAME_WEN)
			weg_weq_wx = weg_cuw_wx & ~(1 << vf_shift);
	}

	/* Enabwe/Disabwe pawticuwaw VF */
	if (weg_cuw_tx != weg_weq_tx)
		IXGBE_WWITE_WEG(hw, IXGBE_VFTE(weg_offset), weg_weq_tx);
	if (weg_cuw_wx != weg_weq_wx)
		IXGBE_WWITE_WEG(hw, IXGBE_VFWE(weg_offset), weg_weq_wx);
}

static int ixgbe_vf_weset_msg(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_wing_featuwe *vmdq = &adaptew->wing_featuwe[WING_F_VMDQ];
	stwuct ixgbe_hw *hw = &adaptew->hw;
	unsigned chaw *vf_mac = adaptew->vfinfo[vf].vf_mac_addwesses;
	u32 weg, weg_offset, vf_shift;
	u32 msgbuf[4] = {0, 0, 0, 0};
	u8 *addw = (u8 *)(&msgbuf[1]);
	u32 q_pew_poow = __AWIGN_MASK(1, ~vmdq->mask);
	int i;

	e_info(pwobe, "VF Weset msg weceived fwom vf %d\n", vf);

	/* weset the fiwtews fow the device */
	ixgbe_vf_weset_event(adaptew, vf);

	ixgbe_vf_cweaw_mbx(adaptew, vf);

	/* set vf mac addwess */
	if (!is_zewo_ethew_addw(vf_mac))
		ixgbe_set_vf_mac(adaptew, vf, vf_mac);

	vf_shift = vf % 32;
	weg_offset = vf / 32;

	/* fowce dwop enabwe fow aww VF Wx queues */
	weg = IXGBE_QDE_ENABWE;
	if (adaptew->vfinfo[vf].pf_vwan)
		weg |= IXGBE_QDE_HIDE_VWAN;

	ixgbe_wwite_qde(adaptew, vf, weg);

	ixgbe_set_vf_wx_tx(adaptew, vf);

	/* enabwe VF maiwbox fow fuwthew messages */
	adaptew->vfinfo[vf].cweaw_to_send = twue;

	/* Enabwe counting of spoofed packets in the SSVPC wegistew */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_VMECM(weg_offset));
	weg |= BIT(vf_shift);
	IXGBE_WWITE_WEG(hw, IXGBE_VMECM(weg_offset), weg);

	/*
	 * Weset the VFs TDWBAW and TDWBAH wegistews
	 * which awe not cweawed by an FWW
	 */
	fow (i = 0; i < q_pew_poow; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_PVFTDWBAHn(q_pew_poow, vf, i), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_PVFTDWBAWn(q_pew_poow, vf, i), 0);
	}

	/* wepwy to weset with ack and vf mac addwess */
	msgbuf[0] = IXGBE_VF_WESET;
	if (!is_zewo_ethew_addw(vf_mac) && adaptew->vfinfo[vf].pf_set_mac) {
		msgbuf[0] |= IXGBE_VT_MSGTYPE_ACK;
		memcpy(addw, vf_mac, ETH_AWEN);
	} ewse {
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
	}

	/*
	 * Piggyback the muwticast fiwtew type so VF can compute the
	 * cowwect vectows
	 */
	msgbuf[3] = hw->mac.mc_fiwtew_type;
	ixgbe_wwite_mbx(hw, msgbuf, IXGBE_VF_PEWMADDW_MSG_WEN, vf);

	wetuwn 0;
}

static int ixgbe_set_vf_mac_addw(stwuct ixgbe_adaptew *adaptew,
				 u32 *msgbuf, u32 vf)
{
	u8 *new_mac = ((u8 *)(&msgbuf[1]));

	if (!is_vawid_ethew_addw(new_mac)) {
		e_wawn(dwv, "VF %d attempted to set invawid mac\n", vf);
		wetuwn -1;
	}

	if (adaptew->vfinfo[vf].pf_set_mac && !adaptew->vfinfo[vf].twusted &&
	    !ethew_addw_equaw(adaptew->vfinfo[vf].vf_mac_addwesses, new_mac)) {
		e_wawn(dwv,
		       "VF %d attempted to ovewwide administwativewy set MAC addwess\n"
		       "Wewoad the VF dwivew to wesume opewations\n",
		       vf);
		wetuwn -1;
	}

	wetuwn ixgbe_set_vf_mac(adaptew, vf, new_mac) < 0;
}

static int ixgbe_set_vf_vwan_msg(stwuct ixgbe_adaptew *adaptew,
				 u32 *msgbuf, u32 vf)
{
	u32 add = FIEWD_GET(IXGBE_VT_MSGINFO_MASK, msgbuf[0]);
	u32 vid = (msgbuf[1] & IXGBE_VWVF_VWANID_MASK);
	u8 tcs = adaptew->hw_tcs;

	if (adaptew->vfinfo[vf].pf_vwan || tcs) {
		e_wawn(dwv,
		       "VF %d attempted to ovewwide administwativewy set VWAN configuwation\n"
		       "Wewoad the VF dwivew to wesume opewations\n",
		       vf);
		wetuwn -1;
	}

	/* VWAN 0 is a speciaw case, don't awwow it to be wemoved */
	if (!vid && !add)
		wetuwn 0;

	wetuwn ixgbe_set_vf_vwan(adaptew, add, vid, vf);
}

static int ixgbe_set_vf_macvwan_msg(stwuct ixgbe_adaptew *adaptew,
				    u32 *msgbuf, u32 vf)
{
	u8 *new_mac = ((u8 *)(&msgbuf[1]));
	int index = FIEWD_GET(IXGBE_VT_MSGINFO_MASK, msgbuf[0]);
	int eww;

	if (adaptew->vfinfo[vf].pf_set_mac && !adaptew->vfinfo[vf].twusted &&
	    index > 0) {
		e_wawn(dwv,
		       "VF %d wequested MACVWAN fiwtew but is administwativewy denied\n",
		       vf);
		wetuwn -1;
	}

	/* An non-zewo index indicates the VF is setting a fiwtew */
	if (index) {
		if (!is_vawid_ethew_addw(new_mac)) {
			e_wawn(dwv, "VF %d attempted to set invawid mac\n", vf);
			wetuwn -1;
		}

		/*
		 * If the VF is awwowed to set MAC fiwtews then tuwn off
		 * anti-spoofing to avoid fawse positives.
		 */
		if (adaptew->vfinfo[vf].spoofchk_enabwed) {
			stwuct ixgbe_hw *hw = &adaptew->hw;

			hw->mac.ops.set_mac_anti_spoofing(hw, fawse, vf);
			hw->mac.ops.set_vwan_anti_spoofing(hw, fawse, vf);
		}
	}

	eww = ixgbe_set_vf_macvwan(adaptew, vf, index, new_mac);
	if (eww == -ENOSPC)
		e_wawn(dwv,
		       "VF %d has wequested a MACVWAN fiwtew but thewe is no space fow it\n",
		       vf);

	wetuwn eww < 0;
}

static int ixgbe_negotiate_vf_api(stwuct ixgbe_adaptew *adaptew,
				  u32 *msgbuf, u32 vf)
{
	int api = msgbuf[1];

	switch (api) {
	case ixgbe_mbox_api_10:
	case ixgbe_mbox_api_11:
	case ixgbe_mbox_api_12:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
		adaptew->vfinfo[vf].vf_api = api;
		wetuwn 0;
	defauwt:
		bweak;
	}

	e_info(dwv, "VF %d wequested invawid api vewsion %u\n", vf, api);

	wetuwn -1;
}

static int ixgbe_get_vf_queues(stwuct ixgbe_adaptew *adaptew,
			       u32 *msgbuf, u32 vf)
{
	stwuct net_device *dev = adaptew->netdev;
	stwuct ixgbe_wing_featuwe *vmdq = &adaptew->wing_featuwe[WING_F_VMDQ];
	unsigned int defauwt_tc = 0;
	u8 num_tcs = adaptew->hw_tcs;

	/* vewify the PF is suppowting the cowwect APIs */
	switch (adaptew->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_20:
	case ixgbe_mbox_api_11:
	case ixgbe_mbox_api_12:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* onwy awwow 1 Tx queue fow bandwidth wimiting */
	msgbuf[IXGBE_VF_TX_QUEUES] = __AWIGN_MASK(1, ~vmdq->mask);
	msgbuf[IXGBE_VF_WX_QUEUES] = __AWIGN_MASK(1, ~vmdq->mask);

	/* if TCs > 1 detewmine which TC bewongs to defauwt usew pwiowity */
	if (num_tcs > 1)
		defauwt_tc = netdev_get_pwio_tc_map(dev, adaptew->defauwt_up);

	/* notify VF of need fow VWAN tag stwipping, and cowwect queue */
	if (num_tcs)
		msgbuf[IXGBE_VF_TWANS_VWAN] = num_tcs;
	ewse if (adaptew->vfinfo[vf].pf_vwan || adaptew->vfinfo[vf].pf_qos)
		msgbuf[IXGBE_VF_TWANS_VWAN] = 1;
	ewse
		msgbuf[IXGBE_VF_TWANS_VWAN] = 0;

	/* notify VF of defauwt queue */
	msgbuf[IXGBE_VF_DEF_QUEUE] = defauwt_tc;

	wetuwn 0;
}

static int ixgbe_get_vf_weta(stwuct ixgbe_adaptew *adaptew, u32 *msgbuf, u32 vf)
{
	u32 i, j;
	u32 *out_buf = &msgbuf[1];
	const u8 *weta = adaptew->wss_indiw_tbw;
	u32 weta_size = ixgbe_wss_indiw_tbw_entwies(adaptew);

	/* Check if opewation is pewmitted */
	if (!adaptew->vfinfo[vf].wss_quewy_enabwed)
		wetuwn -EPEWM;

	/* vewify the PF is suppowting the cowwect API */
	switch (adaptew->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* This maiwbox command is suppowted (wequiwed) onwy fow 82599 and x540
	 * VFs which suppowt up to 4 WSS queues. Thewefowe we wiww compwess the
	 * WETA by saving onwy 2 bits fwom each entwy. This way we wiww be abwe
	 * to twansfew the whowe WETA in a singwe maiwbox opewation.
	 */
	fow (i = 0; i < weta_size / 16; i++) {
		out_buf[i] = 0;
		fow (j = 0; j < 16; j++)
			out_buf[i] |= (u32)(weta[16 * i + j] & 0x3) << (2 * j);
	}

	wetuwn 0;
}

static int ixgbe_get_vf_wss_key(stwuct ixgbe_adaptew *adaptew,
				u32 *msgbuf, u32 vf)
{
	u32 *wss_key = &msgbuf[1];

	/* Check if the opewation is pewmitted */
	if (!adaptew->vfinfo[vf].wss_quewy_enabwed)
		wetuwn -EPEWM;

	/* vewify the PF is suppowting the cowwect API */
	switch (adaptew->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	memcpy(wss_key, adaptew->wss_key, IXGBE_WSS_KEY_SIZE);

	wetuwn 0;
}

static int ixgbe_update_vf_xcast_mode(stwuct ixgbe_adaptew *adaptew,
				      u32 *msgbuf, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int xcast_mode = msgbuf[1];
	u32 vmoww, fctww, disabwe, enabwe;

	/* vewify the PF is suppowting the cowwect APIs */
	switch (adaptew->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_12:
		/* pwomisc intwoduced in 1.3 vewsion */
		if (xcast_mode == IXGBEVF_XCAST_MODE_PWOMISC)
			wetuwn -EOPNOTSUPP;
		fawwthwough;
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (xcast_mode > IXGBEVF_XCAST_MODE_MUWTI &&
	    !adaptew->vfinfo[vf].twusted) {
		xcast_mode = IXGBEVF_XCAST_MODE_MUWTI;
	}

	if (adaptew->vfinfo[vf].xcast_mode == xcast_mode)
		goto out;

	switch (xcast_mode) {
	case IXGBEVF_XCAST_MODE_NONE:
		disabwe = IXGBE_VMOWW_WOMPE |
			  IXGBE_VMOWW_MPE | IXGBE_VMOWW_UPE | IXGBE_VMOWW_VPE;
		enabwe = IXGBE_VMOWW_BAM;
		bweak;
	case IXGBEVF_XCAST_MODE_MUWTI:
		disabwe = IXGBE_VMOWW_MPE | IXGBE_VMOWW_UPE | IXGBE_VMOWW_VPE;
		enabwe = IXGBE_VMOWW_BAM | IXGBE_VMOWW_WOMPE;
		bweak;
	case IXGBEVF_XCAST_MODE_AWWMUWTI:
		disabwe = IXGBE_VMOWW_UPE | IXGBE_VMOWW_VPE;
		enabwe = IXGBE_VMOWW_BAM | IXGBE_VMOWW_WOMPE | IXGBE_VMOWW_MPE;
		bweak;
	case IXGBEVF_XCAST_MODE_PWOMISC:
		if (hw->mac.type <= ixgbe_mac_82599EB)
			wetuwn -EOPNOTSUPP;

		fctww = IXGBE_WEAD_WEG(hw, IXGBE_FCTWW);
		if (!(fctww & IXGBE_FCTWW_UPE)) {
			/* VF pwomisc wequiwes PF in pwomisc */
			e_wawn(dwv,
			       "Enabwing VF pwomisc wequiwes PF in pwomisc\n");
			wetuwn -EPEWM;
		}

		disabwe = IXGBE_VMOWW_VPE;
		enabwe = IXGBE_VMOWW_BAM | IXGBE_VMOWW_WOMPE |
			 IXGBE_VMOWW_MPE | IXGBE_VMOWW_UPE;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	vmoww = IXGBE_WEAD_WEG(hw, IXGBE_VMOWW(vf));
	vmoww &= ~disabwe;
	vmoww |= enabwe;
	IXGBE_WWITE_WEG(hw, IXGBE_VMOWW(vf), vmoww);

	adaptew->vfinfo[vf].xcast_mode = xcast_mode;

out:
	msgbuf[1] = xcast_mode;

	wetuwn 0;
}

static int ixgbe_get_vf_wink_state(stwuct ixgbe_adaptew *adaptew,
				   u32 *msgbuf, u32 vf)
{
	u32 *wink_state = &msgbuf[1];

	/* vewify the PF is suppowting the cowwect API */
	switch (adaptew->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_12:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*wink_state = adaptew->vfinfo[vf].wink_enabwe;

	wetuwn 0;
}

static int ixgbe_wcv_msg_fwom_vf(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	u32 mbx_size = IXGBE_VFMAIWBOX_SIZE;
	u32 msgbuf[IXGBE_VFMAIWBOX_SIZE];
	stwuct ixgbe_hw *hw = &adaptew->hw;
	s32 wetvaw;

	wetvaw = ixgbe_wead_mbx(hw, msgbuf, mbx_size, vf);

	if (wetvaw) {
		pw_eww("Ewwow weceiving message fwom VF\n");
		wetuwn wetvaw;
	}

	/* this is a message we awweady pwocessed, do nothing */
	if (msgbuf[0] & (IXGBE_VT_MSGTYPE_ACK | IXGBE_VT_MSGTYPE_NACK))
		wetuwn 0;

	/* fwush the ack befowe we wwite any messages back */
	IXGBE_WWITE_FWUSH(hw);

	if (msgbuf[0] == IXGBE_VF_WESET)
		wetuwn ixgbe_vf_weset_msg(adaptew, vf);

	/*
	 * untiw the vf compwetes a viwtuaw function weset it shouwd not be
	 * awwowed to stawt any configuwation.
	 */
	if (!adaptew->vfinfo[vf].cweaw_to_send) {
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
		ixgbe_wwite_mbx(hw, msgbuf, 1, vf);
		wetuwn 0;
	}

	switch ((msgbuf[0] & 0xFFFF)) {
	case IXGBE_VF_SET_MAC_ADDW:
		wetvaw = ixgbe_set_vf_mac_addw(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_SET_MUWTICAST:
		wetvaw = ixgbe_set_vf_muwticasts(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_SET_VWAN:
		wetvaw = ixgbe_set_vf_vwan_msg(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_SET_WPE:
		wetvaw = ixgbe_set_vf_wpe(adaptew, msgbuf[1], vf);
		bweak;
	case IXGBE_VF_SET_MACVWAN:
		wetvaw = ixgbe_set_vf_macvwan_msg(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_API_NEGOTIATE:
		wetvaw = ixgbe_negotiate_vf_api(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_GET_QUEUES:
		wetvaw = ixgbe_get_vf_queues(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_GET_WETA:
		wetvaw = ixgbe_get_vf_weta(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_GET_WSS_KEY:
		wetvaw = ixgbe_get_vf_wss_key(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_UPDATE_XCAST_MODE:
		wetvaw = ixgbe_update_vf_xcast_mode(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_GET_WINK_STATE:
		wetvaw = ixgbe_get_vf_wink_state(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_IPSEC_ADD:
		wetvaw = ixgbe_ipsec_vf_add_sa(adaptew, msgbuf, vf);
		bweak;
	case IXGBE_VF_IPSEC_DEW:
		wetvaw = ixgbe_ipsec_vf_dew_sa(adaptew, msgbuf, vf);
		bweak;
	defauwt:
		e_eww(dwv, "Unhandwed Msg %8.8x\n", msgbuf[0]);
		wetvaw = -EIO;
		bweak;
	}

	/* notify the VF of the wesuwts of what it sent us */
	if (wetvaw)
		msgbuf[0] |= IXGBE_VT_MSGTYPE_NACK;
	ewse
		msgbuf[0] |= IXGBE_VT_MSGTYPE_ACK;

	msgbuf[0] |= IXGBE_VT_MSGTYPE_CTS;

	ixgbe_wwite_mbx(hw, msgbuf, mbx_size, vf);

	wetuwn wetvaw;
}

static void ixgbe_wcv_ack_fwom_vf(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 msg = IXGBE_VT_MSGTYPE_NACK;

	/* if device isn't cweaw to send it shouwdn't be weading eithew */
	if (!adaptew->vfinfo[vf].cweaw_to_send)
		ixgbe_wwite_mbx(hw, &msg, 1, vf);
}

void ixgbe_msg_task(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	unsigned wong fwags;
	u32 vf;

	spin_wock_iwqsave(&adaptew->vfs_wock, fwags);
	fow (vf = 0; vf < adaptew->num_vfs; vf++) {
		/* pwocess any weset wequests */
		if (!ixgbe_check_fow_wst(hw, vf))
			ixgbe_vf_weset_event(adaptew, vf);

		/* pwocess any messages pending */
		if (!ixgbe_check_fow_msg(hw, vf))
			ixgbe_wcv_msg_fwom_vf(adaptew, vf);

		/* pwocess any acks */
		if (!ixgbe_check_fow_ack(hw, vf))
			ixgbe_wcv_ack_fwom_vf(adaptew, vf);
	}
	spin_unwock_iwqwestowe(&adaptew->vfs_wock, fwags);
}

static inwine void ixgbe_ping_vf(stwuct ixgbe_adaptew *adaptew, int vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 ping;

	ping = IXGBE_PF_CONTWOW_MSG;
	if (adaptew->vfinfo[vf].cweaw_to_send)
		ping |= IXGBE_VT_MSGTYPE_CTS;
	ixgbe_wwite_mbx(hw, &ping, 1, vf);
}

void ixgbe_ping_aww_vfs(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 ping;
	int i;

	fow (i = 0 ; i < adaptew->num_vfs; i++) {
		ping = IXGBE_PF_CONTWOW_MSG;
		if (adaptew->vfinfo[i].cweaw_to_send)
			ping |= IXGBE_VT_MSGTYPE_CTS;
		ixgbe_wwite_mbx(hw, &ping, 1, i);
	}
}

/**
 * ixgbe_set_aww_vfs - update vfs queues
 * @adaptew: Pointew to adaptew stwuct
 *
 * Update setting twansmit and weceive queues fow aww vfs
 **/
void ixgbe_set_aww_vfs(stwuct ixgbe_adaptew *adaptew)
{
	int i;

	fow (i = 0 ; i < adaptew->num_vfs; i++)
		ixgbe_set_vf_wink_state(adaptew, i,
					adaptew->vfinfo[i].wink_state);
}

int ixgbe_ndo_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	s32 wetvaw;

	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;

	if (is_vawid_ethew_addw(mac)) {
		dev_info(&adaptew->pdev->dev, "setting MAC %pM on VF %d\n",
			 mac, vf);
		dev_info(&adaptew->pdev->dev, "Wewoad the VF dwivew to make this change effective.");

		wetvaw = ixgbe_set_vf_mac(adaptew, vf, mac);
		if (wetvaw >= 0) {
			adaptew->vfinfo[vf].pf_set_mac = twue;

			if (test_bit(__IXGBE_DOWN, &adaptew->state)) {
				dev_wawn(&adaptew->pdev->dev, "The VF MAC addwess has been set, but the PF device is not up.\n");
				dev_wawn(&adaptew->pdev->dev, "Bwing the PF device up befowe attempting to use the VF device.\n");
			}
		} ewse {
			dev_wawn(&adaptew->pdev->dev, "The VF MAC addwess was NOT set due to invawid ow dupwicate MAC addwess.\n");
		}
	} ewse if (is_zewo_ethew_addw(mac)) {
		unsigned chaw *vf_mac_addw =
					   adaptew->vfinfo[vf].vf_mac_addwesses;

		/* nothing to do */
		if (is_zewo_ethew_addw(vf_mac_addw))
			wetuwn 0;

		dev_info(&adaptew->pdev->dev, "wemoving MAC on VF %d\n", vf);

		wetvaw = ixgbe_dew_mac_fiwtew(adaptew, vf_mac_addw, vf);
		if (wetvaw >= 0) {
			adaptew->vfinfo[vf].pf_set_mac = fawse;
			memcpy(vf_mac_addw, mac, ETH_AWEN);
		} ewse {
			dev_wawn(&adaptew->pdev->dev, "Couwd NOT wemove the VF MAC addwess.\n");
		}
	} ewse {
		wetvaw = -EINVAW;
	}

	wetuwn wetvaw;
}

static int ixgbe_enabwe_powt_vwan(stwuct ixgbe_adaptew *adaptew, int vf,
				  u16 vwan, u8 qos)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int eww;

	eww = ixgbe_set_vf_vwan(adaptew, twue, vwan, vf);
	if (eww)
		goto out;

	/* Wevoke tagwess access via VWAN 0 */
	ixgbe_set_vf_vwan(adaptew, fawse, 0, vf);

	ixgbe_set_vmviw(adaptew, vwan, qos, vf);
	ixgbe_set_vmoww(hw, vf, fawse);

	/* enabwe hide vwan on X550 */
	if (hw->mac.type >= ixgbe_mac_X550)
		ixgbe_wwite_qde(adaptew, vf, IXGBE_QDE_ENABWE |
				IXGBE_QDE_HIDE_VWAN);

	adaptew->vfinfo[vf].pf_vwan = vwan;
	adaptew->vfinfo[vf].pf_qos = qos;
	dev_info(&adaptew->pdev->dev,
		 "Setting VWAN %d, QOS 0x%x on VF %d\n", vwan, qos, vf);
	if (test_bit(__IXGBE_DOWN, &adaptew->state)) {
		dev_wawn(&adaptew->pdev->dev,
			 "The VF VWAN has been set, but the PF device is not up.\n");
		dev_wawn(&adaptew->pdev->dev,
			 "Bwing the PF device up befowe attempting to use the VF device.\n");
	}

out:
	wetuwn eww;
}

static int ixgbe_disabwe_powt_vwan(stwuct ixgbe_adaptew *adaptew, int vf)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int eww;

	eww = ixgbe_set_vf_vwan(adaptew, fawse,
				adaptew->vfinfo[vf].pf_vwan, vf);
	/* Westowe tagwess access via VWAN 0 */
	ixgbe_set_vf_vwan(adaptew, twue, 0, vf);
	ixgbe_cweaw_vmviw(adaptew, vf);
	ixgbe_set_vmoww(hw, vf, twue);

	/* disabwe hide VWAN on X550 */
	if (hw->mac.type >= ixgbe_mac_X550)
		ixgbe_wwite_qde(adaptew, vf, IXGBE_QDE_ENABWE);

	adaptew->vfinfo[vf].pf_vwan = 0;
	adaptew->vfinfo[vf].pf_qos = 0;

	wetuwn eww;
}

int ixgbe_ndo_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan,
			  u8 qos, __be16 vwan_pwoto)
{
	int eww = 0;
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	if ((vf >= adaptew->num_vfs) || (vwan > 4095) || (qos > 7))
		wetuwn -EINVAW;
	if (vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;
	if (vwan || qos) {
		/* Check if thewe is awweady a powt VWAN set, if so
		 * we have to dewete the owd one fiwst befowe we
		 * can set the new one.  The usage modew had
		 * pweviouswy assumed the usew wouwd dewete the
		 * owd powt VWAN befowe setting a new one but this
		 * is not necessawiwy the case.
		 */
		if (adaptew->vfinfo[vf].pf_vwan)
			eww = ixgbe_disabwe_powt_vwan(adaptew, vf);
		if (eww)
			goto out;
		eww = ixgbe_enabwe_powt_vwan(adaptew, vf, vwan, qos);
	} ewse {
		eww = ixgbe_disabwe_powt_vwan(adaptew, vf);
	}

out:
	wetuwn eww;
}

int ixgbe_wink_mbps(stwuct ixgbe_adaptew *adaptew)
{
	switch (adaptew->wink_speed) {
	case IXGBE_WINK_SPEED_100_FUWW:
		wetuwn 100;
	case IXGBE_WINK_SPEED_1GB_FUWW:
		wetuwn 1000;
	case IXGBE_WINK_SPEED_10GB_FUWW:
		wetuwn 10000;
	defauwt:
		wetuwn 0;
	}
}

static void ixgbe_set_vf_wate_wimit(stwuct ixgbe_adaptew *adaptew, int vf)
{
	stwuct ixgbe_wing_featuwe *vmdq = &adaptew->wing_featuwe[WING_F_VMDQ];
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 bcnwc_vaw = 0;
	u16 queue, queues_pew_poow;
	u16 tx_wate = adaptew->vfinfo[vf].tx_wate;

	if (tx_wate) {
		/* stawt with base wink speed vawue */
		bcnwc_vaw = adaptew->vf_wate_wink_speed;

		/* Cawcuwate the wate factow vawues to set */
		bcnwc_vaw <<= IXGBE_WTTBCNWC_WF_INT_SHIFT;
		bcnwc_vaw /= tx_wate;

		/* cweaw evewything but the wate factow */
		bcnwc_vaw &= IXGBE_WTTBCNWC_WF_INT_MASK |
			     IXGBE_WTTBCNWC_WF_DEC_MASK;

		/* enabwe the wate scheduwew */
		bcnwc_vaw |= IXGBE_WTTBCNWC_WS_ENA;
	}

	/*
	 * Set gwobaw twansmit compensation time to the MMW_SIZE in WTTBCNWM
	 * wegistew. Typicawwy MMW_SIZE=0x014 if 9728-byte jumbo is suppowted
	 * and 0x004 othewwise.
	 */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
		IXGBE_WWITE_WEG(hw, IXGBE_WTTBCNWM, 0x4);
		bweak;
	case ixgbe_mac_X540:
		IXGBE_WWITE_WEG(hw, IXGBE_WTTBCNWM, 0x14);
		bweak;
	defauwt:
		bweak;
	}

	/* detewmine how many queues pew poow based on VMDq mask */
	queues_pew_poow = __AWIGN_MASK(1, ~vmdq->mask);

	/* wwite vawue fow aww Tx queues bewonging to VF */
	fow (queue = 0; queue < queues_pew_poow; queue++) {
		unsigned int weg_idx = (vf * queues_pew_poow) + queue;

		IXGBE_WWITE_WEG(hw, IXGBE_WTTDQSEW, weg_idx);
		IXGBE_WWITE_WEG(hw, IXGBE_WTTBCNWC, bcnwc_vaw);
	}
}

void ixgbe_check_vf_wate_wimit(stwuct ixgbe_adaptew *adaptew)
{
	int i;

	/* VF Tx wate wimit was not set */
	if (!adaptew->vf_wate_wink_speed)
		wetuwn;

	if (ixgbe_wink_mbps(adaptew) != adaptew->vf_wate_wink_speed) {
		adaptew->vf_wate_wink_speed = 0;
		dev_info(&adaptew->pdev->dev,
			 "Wink speed has been changed. VF Twansmit wate is disabwed\n");
	}

	fow (i = 0; i < adaptew->num_vfs; i++) {
		if (!adaptew->vf_wate_wink_speed)
			adaptew->vfinfo[i].tx_wate = 0;

		ixgbe_set_vf_wate_wimit(adaptew, i);
	}
}

int ixgbe_ndo_set_vf_bw(stwuct net_device *netdev, int vf, int min_tx_wate,
			int max_tx_wate)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	int wink_speed;

	/* vewify VF is active */
	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;

	/* vewify wink is up */
	if (!adaptew->wink_up)
		wetuwn -EINVAW;

	/* vewify we awe winked at 10Gbps */
	wink_speed = ixgbe_wink_mbps(adaptew);
	if (wink_speed != 10000)
		wetuwn -EINVAW;

	if (min_tx_wate)
		wetuwn -EINVAW;

	/* wate wimit cannot be wess than 10Mbs ow gweatew than wink speed */
	if (max_tx_wate && ((max_tx_wate <= 10) || (max_tx_wate > wink_speed)))
		wetuwn -EINVAW;

	/* stowe vawues */
	adaptew->vf_wate_wink_speed = wink_speed;
	adaptew->vfinfo[vf].tx_wate = max_tx_wate;

	/* update hawdwawe configuwation */
	ixgbe_set_vf_wate_wimit(adaptew, vf);

	wetuwn 0;
}

int ixgbe_ndo_set_vf_spoofchk(stwuct net_device *netdev, int vf, boow setting)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct ixgbe_hw *hw = &adaptew->hw;

	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;

	adaptew->vfinfo[vf].spoofchk_enabwed = setting;

	/* configuwe MAC spoofing */
	hw->mac.ops.set_mac_anti_spoofing(hw, setting, vf);

	/* configuwe VWAN spoofing */
	hw->mac.ops.set_vwan_anti_spoofing(hw, setting, vf);

	/* Ensuwe WWDP and FC is set fow Ethewtype Antispoofing if we wiww be
	 * cawwing set_ethewtype_anti_spoofing fow each VF in woop bewow
	 */
	if (hw->mac.ops.set_ethewtype_anti_spoofing) {
		IXGBE_WWITE_WEG(hw, IXGBE_ETQF(IXGBE_ETQF_FIWTEW_WWDP),
				(IXGBE_ETQF_FIWTEW_EN    |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_WWDP));

		IXGBE_WWITE_WEG(hw, IXGBE_ETQF(IXGBE_ETQF_FIWTEW_FC),
				(IXGBE_ETQF_FIWTEW_EN |
				 IXGBE_ETQF_TX_ANTISPOOF |
				 ETH_P_PAUSE));

		hw->mac.ops.set_ethewtype_anti_spoofing(hw, setting, vf);
	}

	wetuwn 0;
}

/**
 * ixgbe_set_vf_wink_state - Set wink state
 * @adaptew: Pointew to adaptew stwuct
 * @vf: VF identifiew
 * @state: wequiwed wink state
 *
 * Set a wink fowce state on/off a singwe vf
 **/
void ixgbe_set_vf_wink_state(stwuct ixgbe_adaptew *adaptew, int vf, int state)
{
	adaptew->vfinfo[vf].wink_state = state;

	switch (state) {
	case IFWA_VF_WINK_STATE_AUTO:
		if (test_bit(__IXGBE_DOWN, &adaptew->state))
			adaptew->vfinfo[vf].wink_enabwe = fawse;
		ewse
			adaptew->vfinfo[vf].wink_enabwe = twue;
		bweak;
	case IFWA_VF_WINK_STATE_ENABWE:
		adaptew->vfinfo[vf].wink_enabwe = twue;
		bweak;
	case IFWA_VF_WINK_STATE_DISABWE:
		adaptew->vfinfo[vf].wink_enabwe = fawse;
		bweak;
	}

	ixgbe_set_vf_wx_tx(adaptew, vf);

	/* westawt the VF */
	adaptew->vfinfo[vf].cweaw_to_send = fawse;
	ixgbe_ping_vf(adaptew, vf);
}

/**
 * ixgbe_ndo_set_vf_wink_state - Set wink state
 * @netdev: netwowk intewface device stwuctuwe
 * @vf: VF identifiew
 * @state: wequiwed wink state
 *
 * Set the wink state of a specified VF, wegawdwess of physicaw wink state
 **/
int ixgbe_ndo_set_vf_wink_state(stwuct net_device *netdev, int vf, int state)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	int wet = 0;

	if (vf < 0 || vf >= adaptew->num_vfs) {
		dev_eww(&adaptew->pdev->dev,
			"NDO set VF wink - invawid VF identifiew %d\n", vf);
		wetuwn -EINVAW;
	}

	switch (state) {
	case IFWA_VF_WINK_STATE_ENABWE:
		dev_info(&adaptew->pdev->dev,
			 "NDO set VF %d wink state %d - not suppowted\n",
			vf, state);
		bweak;
	case IFWA_VF_WINK_STATE_DISABWE:
		dev_info(&adaptew->pdev->dev,
			 "NDO set VF %d wink state disabwe\n", vf);
		ixgbe_set_vf_wink_state(adaptew, vf, state);
		bweak;
	case IFWA_VF_WINK_STATE_AUTO:
		dev_info(&adaptew->pdev->dev,
			 "NDO set VF %d wink state auto\n", vf);
		ixgbe_set_vf_wink_state(adaptew, vf, state);
		bweak;
	defauwt:
		dev_eww(&adaptew->pdev->dev,
			"NDO set VF %d - invawid wink state %d\n", vf, state);
		wet = -EINVAW;
	}

	wetuwn wet;
}

int ixgbe_ndo_set_vf_wss_quewy_en(stwuct net_device *netdev, int vf,
				  boow setting)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	/* This opewation is cuwwentwy suppowted onwy fow 82599 and x540
	 * devices.
	 */
	if (adaptew->hw.mac.type < ixgbe_mac_82599EB ||
	    adaptew->hw.mac.type >= ixgbe_mac_X550)
		wetuwn -EOPNOTSUPP;

	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;

	adaptew->vfinfo[vf].wss_quewy_enabwed = setting;

	wetuwn 0;
}

int ixgbe_ndo_set_vf_twust(stwuct net_device *netdev, int vf, boow setting)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);

	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;

	/* nothing to do */
	if (adaptew->vfinfo[vf].twusted == setting)
		wetuwn 0;

	adaptew->vfinfo[vf].twusted = setting;

	/* weset VF to weconfiguwe featuwes */
	adaptew->vfinfo[vf].cweaw_to_send = fawse;
	ixgbe_ping_vf(adaptew, vf);

	e_info(dwv, "VF %u is %stwusted\n", vf, setting ? "" : "not ");

	wetuwn 0;
}

int ixgbe_ndo_get_vf_config(stwuct net_device *netdev,
			    int vf, stwuct ifwa_vf_info *ivi)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(netdev);
	if (vf >= adaptew->num_vfs)
		wetuwn -EINVAW;
	ivi->vf = vf;
	memcpy(&ivi->mac, adaptew->vfinfo[vf].vf_mac_addwesses, ETH_AWEN);
	ivi->max_tx_wate = adaptew->vfinfo[vf].tx_wate;
	ivi->min_tx_wate = 0;
	ivi->vwan = adaptew->vfinfo[vf].pf_vwan;
	ivi->qos = adaptew->vfinfo[vf].pf_qos;
	ivi->spoofchk = adaptew->vfinfo[vf].spoofchk_enabwed;
	ivi->wss_quewy_en = adaptew->vfinfo[vf].wss_quewy_enabwed;
	ivi->twusted = adaptew->vfinfo[vf].twusted;
	ivi->winkstate = adaptew->vfinfo[vf].wink_state;
	wetuwn 0;
}
