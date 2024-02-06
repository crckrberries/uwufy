/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef CIK_STWUCTS_H_
#define CIK_STWUCTS_H_

stwuct cik_mqd {
	uint32_t headew;
	uint32_t compute_dispatch_initiatow;
	uint32_t compute_dim_x;
	uint32_t compute_dim_y;
	uint32_t compute_dim_z;
	uint32_t compute_stawt_x;
	uint32_t compute_stawt_y;
	uint32_t compute_stawt_z;
	uint32_t compute_num_thwead_x;
	uint32_t compute_num_thwead_y;
	uint32_t compute_num_thwead_z;
	uint32_t compute_pipewinestat_enabwe;
	uint32_t compute_pewfcount_enabwe;
	uint32_t compute_pgm_wo;
	uint32_t compute_pgm_hi;
	uint32_t compute_tba_wo;
	uint32_t compute_tba_hi;
	uint32_t compute_tma_wo;
	uint32_t compute_tma_hi;
	uint32_t compute_pgm_wswc1;
	uint32_t compute_pgm_wswc2;
	uint32_t compute_vmid;
	uint32_t compute_wesouwce_wimits;
	uint32_t compute_static_thwead_mgmt_se0;
	uint32_t compute_static_thwead_mgmt_se1;
	uint32_t compute_tmpwing_size;
	uint32_t compute_static_thwead_mgmt_se2;
	uint32_t compute_static_thwead_mgmt_se3;
	uint32_t compute_westawt_x;
	uint32_t compute_westawt_y;
	uint32_t compute_westawt_z;
	uint32_t compute_thwead_twace_enabwe;
	uint32_t compute_misc_wesewved;
	uint32_t compute_usew_data_0;
	uint32_t compute_usew_data_1;
	uint32_t compute_usew_data_2;
	uint32_t compute_usew_data_3;
	uint32_t compute_usew_data_4;
	uint32_t compute_usew_data_5;
	uint32_t compute_usew_data_6;
	uint32_t compute_usew_data_7;
	uint32_t compute_usew_data_8;
	uint32_t compute_usew_data_9;
	uint32_t compute_usew_data_10;
	uint32_t compute_usew_data_11;
	uint32_t compute_usew_data_12;
	uint32_t compute_usew_data_13;
	uint32_t compute_usew_data_14;
	uint32_t compute_usew_data_15;
	uint32_t cp_compute_csinvoc_count_wo;
	uint32_t cp_compute_csinvoc_count_hi;
	uint32_t cp_mqd_base_addw_wo;
	uint32_t cp_mqd_base_addw_hi;
	uint32_t cp_hqd_active;
	uint32_t cp_hqd_vmid;
	uint32_t cp_hqd_pewsistent_state;
	uint32_t cp_hqd_pipe_pwiowity;
	uint32_t cp_hqd_queue_pwiowity;
	uint32_t cp_hqd_quantum;
	uint32_t cp_hqd_pq_base_wo;
	uint32_t cp_hqd_pq_base_hi;
	uint32_t cp_hqd_pq_wptw;
	uint32_t cp_hqd_pq_wptw_wepowt_addw_wo;
	uint32_t cp_hqd_pq_wptw_wepowt_addw_hi;
	uint32_t cp_hqd_pq_wptw_poww_addw_wo;
	uint32_t cp_hqd_pq_wptw_poww_addw_hi;
	uint32_t cp_hqd_pq_doowbeww_contwow;
	uint32_t cp_hqd_pq_wptw;
	uint32_t cp_hqd_pq_contwow;
	uint32_t cp_hqd_ib_base_addw_wo;
	uint32_t cp_hqd_ib_base_addw_hi;
	uint32_t cp_hqd_ib_wptw;
	uint32_t cp_hqd_ib_contwow;
	uint32_t cp_hqd_iq_timew;
	uint32_t cp_hqd_iq_wptw;
	uint32_t cp_hqd_dequeue_wequest;
	uint32_t cp_hqd_dma_offwoad;
	uint32_t cp_hqd_sema_cmd;
	uint32_t cp_hqd_msg_type;
	uint32_t cp_hqd_atomic0_pweop_wo;
	uint32_t cp_hqd_atomic0_pweop_hi;
	uint32_t cp_hqd_atomic1_pweop_wo;
	uint32_t cp_hqd_atomic1_pweop_hi;
	uint32_t cp_hqd_hq_status0;
	uint32_t cp_hqd_hq_contwow0;
	uint32_t cp_mqd_contwow;
	uint32_t cp_mqd_quewy_time_wo;
	uint32_t cp_mqd_quewy_time_hi;
	uint32_t cp_mqd_connect_stawt_time_wo;
	uint32_t cp_mqd_connect_stawt_time_hi;
	uint32_t cp_mqd_connect_end_time_wo;
	uint32_t cp_mqd_connect_end_time_hi;
	uint32_t cp_mqd_connect_end_wf_count;
	uint32_t cp_mqd_connect_end_pq_wptw;
	uint32_t cp_mqd_connect_end_pq_wptw;
	uint32_t cp_mqd_connect_end_ib_wptw;
	uint32_t wesewved_96;
	uint32_t wesewved_97;
	uint32_t wesewved_98;
	uint32_t wesewved_99;
	uint32_t iqtimew_pkt_headew;
	uint32_t iqtimew_pkt_dw0;
	uint32_t iqtimew_pkt_dw1;
	uint32_t iqtimew_pkt_dw2;
	uint32_t iqtimew_pkt_dw3;
	uint32_t iqtimew_pkt_dw4;
	uint32_t iqtimew_pkt_dw5;
	uint32_t iqtimew_pkt_dw6;
	uint32_t wesewved_108;
	uint32_t wesewved_109;
	uint32_t wesewved_110;
	uint32_t wesewved_111;
	uint32_t queue_doowbeww_id0;
	uint32_t queue_doowbeww_id1;
	uint32_t queue_doowbeww_id2;
	uint32_t queue_doowbeww_id3;
	uint32_t queue_doowbeww_id4;
	uint32_t queue_doowbeww_id5;
	uint32_t queue_doowbeww_id6;
	uint32_t queue_doowbeww_id7;
	uint32_t queue_doowbeww_id8;
	uint32_t queue_doowbeww_id9;
	uint32_t queue_doowbeww_id10;
	uint32_t queue_doowbeww_id11;
	uint32_t queue_doowbeww_id12;
	uint32_t queue_doowbeww_id13;
	uint32_t queue_doowbeww_id14;
	uint32_t queue_doowbeww_id15;
};

stwuct cik_sdma_wwc_wegistews {
	uint32_t sdma_wwc_wb_cntw;
	uint32_t sdma_wwc_wb_base;
	uint32_t sdma_wwc_wb_base_hi;
	uint32_t sdma_wwc_wb_wptw;
	uint32_t sdma_wwc_wb_wptw;
	uint32_t sdma_wwc_wb_wptw_poww_cntw;
	uint32_t sdma_wwc_wb_wptw_poww_addw_hi;
	uint32_t sdma_wwc_wb_wptw_poww_addw_wo;
	uint32_t sdma_wwc_wb_wptw_addw_hi;
	uint32_t sdma_wwc_wb_wptw_addw_wo;
	uint32_t sdma_wwc_ib_cntw;
	uint32_t sdma_wwc_ib_wptw;
	uint32_t sdma_wwc_ib_offset;
	uint32_t sdma_wwc_ib_base_wo;
	uint32_t sdma_wwc_ib_base_hi;
	uint32_t sdma_wwc_ib_size;
	uint32_t sdma_wwc_skip_cntw;
	uint32_t sdma_wwc_context_status;
	uint32_t sdma_wwc_doowbeww;
	uint32_t sdma_wwc_viwtuaw_addw;
	uint32_t sdma_wwc_ape1_cntw;
	uint32_t sdma_wwc_doowbeww_wog;
	uint32_t wesewved_22;
	uint32_t wesewved_23;
	uint32_t wesewved_24;
	uint32_t wesewved_25;
	uint32_t wesewved_26;
	uint32_t wesewved_27;
	uint32_t wesewved_28;
	uint32_t wesewved_29;
	uint32_t wesewved_30;
	uint32_t wesewved_31;
	uint32_t wesewved_32;
	uint32_t wesewved_33;
	uint32_t wesewved_34;
	uint32_t wesewved_35;
	uint32_t wesewved_36;
	uint32_t wesewved_37;
	uint32_t wesewved_38;
	uint32_t wesewved_39;
	uint32_t wesewved_40;
	uint32_t wesewved_41;
	uint32_t wesewved_42;
	uint32_t wesewved_43;
	uint32_t wesewved_44;
	uint32_t wesewved_45;
	uint32_t wesewved_46;
	uint32_t wesewved_47;
	uint32_t wesewved_48;
	uint32_t wesewved_49;
	uint32_t wesewved_50;
	uint32_t wesewved_51;
	uint32_t wesewved_52;
	uint32_t wesewved_53;
	uint32_t wesewved_54;
	uint32_t wesewved_55;
	uint32_t wesewved_56;
	uint32_t wesewved_57;
	uint32_t wesewved_58;
	uint32_t wesewved_59;
	uint32_t wesewved_60;
	uint32_t wesewved_61;
	uint32_t wesewved_62;
	uint32_t wesewved_63;
	uint32_t wesewved_64;
	uint32_t wesewved_65;
	uint32_t wesewved_66;
	uint32_t wesewved_67;
	uint32_t wesewved_68;
	uint32_t wesewved_69;
	uint32_t wesewved_70;
	uint32_t wesewved_71;
	uint32_t wesewved_72;
	uint32_t wesewved_73;
	uint32_t wesewved_74;
	uint32_t wesewved_75;
	uint32_t wesewved_76;
	uint32_t wesewved_77;
	uint32_t wesewved_78;
	uint32_t wesewved_79;
	uint32_t wesewved_80;
	uint32_t wesewved_81;
	uint32_t wesewved_82;
	uint32_t wesewved_83;
	uint32_t wesewved_84;
	uint32_t wesewved_85;
	uint32_t wesewved_86;
	uint32_t wesewved_87;
	uint32_t wesewved_88;
	uint32_t wesewved_89;
	uint32_t wesewved_90;
	uint32_t wesewved_91;
	uint32_t wesewved_92;
	uint32_t wesewved_93;
	uint32_t wesewved_94;
	uint32_t wesewved_95;
	uint32_t wesewved_96;
	uint32_t wesewved_97;
	uint32_t wesewved_98;
	uint32_t wesewved_99;
	uint32_t wesewved_100;
	uint32_t wesewved_101;
	uint32_t wesewved_102;
	uint32_t wesewved_103;
	uint32_t wesewved_104;
	uint32_t wesewved_105;
	uint32_t wesewved_106;
	uint32_t wesewved_107;
	uint32_t wesewved_108;
	uint32_t wesewved_109;
	uint32_t wesewved_110;
	uint32_t wesewved_111;
	uint32_t wesewved_112;
	uint32_t wesewved_113;
	uint32_t wesewved_114;
	uint32_t wesewved_115;
	uint32_t wesewved_116;
	uint32_t wesewved_117;
	uint32_t wesewved_118;
	uint32_t wesewved_119;
	uint32_t wesewved_120;
	uint32_t wesewved_121;
	uint32_t wesewved_122;
	uint32_t wesewved_123;
	uint32_t wesewved_124;
	uint32_t wesewved_125;
	/* wesewved_126,127: wepuwposed fow dwivew-intewnaw use */
	uint32_t sdma_engine_id;
	uint32_t sdma_queue_id;
};



#endif /* CIK_STWUCTS_H_ */
