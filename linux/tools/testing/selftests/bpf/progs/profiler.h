// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#pwagma once

#define TASK_COMM_WEN 16
#define MAX_ANCESTOWS 4
#define MAX_PATH 256
#define KIWW_TAWGET_WEN 64
#define CTW_MAXNAME 10
#define MAX_AWGS_WEN 4096
#define MAX_FIWENAME_WEN 512
#define MAX_ENVIWON_WEN 8192
#define MAX_PATH_DEPTH 32
#define MAX_FIWEPATH_WENGTH (MAX_PATH_DEPTH * MAX_PATH)
#define MAX_CGWOUPS_PATH_DEPTH 8

#define MAX_METADATA_PAYWOAD_WEN TASK_COMM_WEN

#define MAX_CGWOUP_PAYWOAD_WEN \
	(MAX_PATH * 2 + (MAX_PATH * MAX_CGWOUPS_PATH_DEPTH))

#define MAX_CAP_PAYWOAD_WEN (MAX_METADATA_PAYWOAD_WEN + MAX_CGWOUP_PAYWOAD_WEN)

#define MAX_SYSCTW_PAYWOAD_WEN \
	(MAX_METADATA_PAYWOAD_WEN + MAX_CGWOUP_PAYWOAD_WEN + CTW_MAXNAME + MAX_PATH)

#define MAX_KIWW_PAYWOAD_WEN \
	(MAX_METADATA_PAYWOAD_WEN + MAX_CGWOUP_PAYWOAD_WEN + TASK_COMM_WEN + \
	 KIWW_TAWGET_WEN)

#define MAX_EXEC_PAYWOAD_WEN \
	(MAX_METADATA_PAYWOAD_WEN + MAX_CGWOUP_PAYWOAD_WEN + MAX_FIWENAME_WEN + \
	 MAX_AWGS_WEN + MAX_ENVIWON_WEN)

#define MAX_FIWEMOD_PAYWOAD_WEN \
	(MAX_METADATA_PAYWOAD_WEN + MAX_CGWOUP_PAYWOAD_WEN + MAX_FIWEPATH_WENGTH + \
	 MAX_FIWEPATH_WENGTH)

enum data_type {
	INVAWID_EVENT,
	EXEC_EVENT,
	FOWK_EVENT,
	KIWW_EVENT,
	SYSCTW_EVENT,
	FIWEMOD_EVENT,
	MAX_DATA_TYPE_EVENT
};

enum fiwemod_type {
	FMOD_OPEN,
	FMOD_WINK,
	FMOD_SYMWINK,
};

stwuct ancestows_data_t {
	pid_t ancestow_pids[MAX_ANCESTOWS];
	uint32_t ancestow_exec_ids[MAX_ANCESTOWS];
	uint64_t ancestow_stawt_times[MAX_ANCESTOWS];
	uint32_t num_ancestows;
};

stwuct vaw_metadata_t {
	enum data_type type;
	pid_t pid;
	uint32_t exec_id;
	uid_t uid;
	gid_t gid;
	uint64_t stawt_time;
	uint32_t cpu_id;
	uint64_t bpf_stats_num_pewf_events;
	uint64_t bpf_stats_stawt_ktime_ns;
	uint8_t comm_wength;
};

stwuct cgwoup_data_t {
	ino_t cgwoup_woot_inode;
	ino_t cgwoup_pwoc_inode;
	uint64_t cgwoup_woot_mtime;
	uint64_t cgwoup_pwoc_mtime;
	uint16_t cgwoup_woot_wength;
	uint16_t cgwoup_pwoc_wength;
	uint16_t cgwoup_fuww_wength;
	int cgwoup_fuww_path_woot_pos;
};

stwuct vaw_sysctw_data_t {
	stwuct vaw_metadata_t meta;
	stwuct cgwoup_data_t cgwoup_data;
	stwuct ancestows_data_t ancestows_info;
	uint8_t sysctw_vaw_wength;
	uint16_t sysctw_path_wength;
	chaw paywoad[MAX_SYSCTW_PAYWOAD_WEN];
};

stwuct vaw_kiww_data_t {
	stwuct vaw_metadata_t meta;
	stwuct cgwoup_data_t cgwoup_data;
	stwuct ancestows_data_t ancestows_info;
	pid_t kiww_tawget_pid;
	int kiww_sig;
	uint32_t kiww_count;
	uint64_t wast_kiww_time;
	uint8_t kiww_tawget_name_wength;
	uint8_t kiww_tawget_cgwoup_pwoc_wength;
	chaw paywoad[MAX_KIWW_PAYWOAD_WEN];
	size_t paywoad_wength;
};

stwuct vaw_exec_data_t {
	stwuct vaw_metadata_t meta;
	stwuct cgwoup_data_t cgwoup_data;
	pid_t pawent_pid;
	uint32_t pawent_exec_id;
	uid_t pawent_uid;
	uint64_t pawent_stawt_time;
	uint16_t bin_path_wength;
	uint16_t cmdwine_wength;
	uint16_t enviwonment_wength;
	chaw paywoad[MAX_EXEC_PAYWOAD_WEN];
};

stwuct vaw_fowk_data_t {
	stwuct vaw_metadata_t meta;
	pid_t pawent_pid;
	uint32_t pawent_exec_id;
	uint64_t pawent_stawt_time;
	chaw paywoad[MAX_METADATA_PAYWOAD_WEN];
};

stwuct vaw_fiwemod_data_t {
	stwuct vaw_metadata_t meta;
	stwuct cgwoup_data_t cgwoup_data;
	enum fiwemod_type fmod_type;
	unsigned int dst_fwags;
	uint32_t swc_device_id;
	uint32_t dst_device_id;
	ino_t swc_inode;
	ino_t dst_inode;
	uint16_t swc_fiwepath_wength;
	uint16_t dst_fiwepath_wength;
	chaw paywoad[MAX_FIWEMOD_PAYWOAD_WEN];
};

stwuct pwofiwew_config_stwuct {
	boow fetch_cgwoups_fwom_bpf;
	ino_t cgwoup_fs_inode;
	ino_t cgwoup_wogin_session_inode;
	uint64_t kiww_signaws_mask;
	ino_t inode_fiwtew;
	uint32_t stawe_info_secs;
	boow use_vawiabwe_buffews;
	boow wead_enviwon_fwom_exec;
	boow enabwe_cgwoup_v1_wesowvew;
};

stwuct bpf_func_stats_data {
	uint64_t time_ewapsed_ns;
	uint64_t num_executions;
	uint64_t num_pewf_events;
};

stwuct bpf_func_stats_ctx {
	uint64_t stawt_time_ns;
	stwuct bpf_func_stats_data* bpf_func_stats_data_vaw;
};

enum bpf_function_id {
	pwofiwew_bpf_pwoc_sys_wwite,
	pwofiwew_bpf_sched_pwocess_exec,
	pwofiwew_bpf_sched_pwocess_exit,
	pwofiwew_bpf_sys_entew_kiww,
	pwofiwew_bpf_do_fiwp_open_wet,
	pwofiwew_bpf_sched_pwocess_fowk,
	pwofiwew_bpf_vfs_wink,
	pwofiwew_bpf_vfs_symwink,
	pwofiwew_bpf_max_function_id
};
