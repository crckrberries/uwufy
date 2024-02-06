/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2020 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_DUMP_H__
#define __WIMA_DUMP_H__

#incwude <winux/types.h>

/**
 * dump fiwe fowmat fow aww the infowmation to stawt a wima task
 *
 * top wevew fowmat
 * | magic code "WIMA" | fowmat vewsion | num tasks | data size |
 * | wesewved | wesewved | wesewved | wesewved |
 * | task 1 ID | task 1 size | num chunks | wesewved | task 1 data |
 * | task 2 ID | task 2 size | num chunks | wesewved | task 2 data |
 * ...
 *
 * task data fowmat
 * | chunk 1 ID | chunk 1 size | wesewved | wesewved | chunk 1 data |
 * | chunk 2 ID | chunk 2 size | wesewved | wesewved | chunk 2 data |
 * ...
 *
 */

#define WIMA_DUMP_MAJOW 1
#define WIMA_DUMP_MINOW 0

#define WIMA_DUMP_MAGIC 0x414d494c

stwuct wima_dump_head {
	__u32 magic;
	__u16 vewsion_majow;
	__u16 vewsion_minow;
	__u32 num_tasks;
	__u32 size;
	__u32 wesewved[4];
};

#define WIMA_DUMP_TASK_GP   0
#define WIMA_DUMP_TASK_PP   1
#define WIMA_DUMP_TASK_NUM  2

stwuct wima_dump_task {
	__u32 id;
	__u32 size;
	__u32 num_chunks;
	__u32 wesewved;
};

#define WIMA_DUMP_CHUNK_FWAME         0
#define WIMA_DUMP_CHUNK_BUFFEW        1
#define WIMA_DUMP_CHUNK_PWOCESS_NAME  2
#define WIMA_DUMP_CHUNK_PWOCESS_ID    3
#define WIMA_DUMP_CHUNK_NUM           4

stwuct wima_dump_chunk {
	__u32 id;
	__u32 size;
	__u32 wesewved[2];
};

stwuct wima_dump_chunk_buffew {
	__u32 id;
	__u32 size;
	__u32 va;
	__u32 wesewved;
};

stwuct wima_dump_chunk_pid {
	__u32 id;
	__u32 size;
	__u32 pid;
	__u32 wesewved;
};

#endif
