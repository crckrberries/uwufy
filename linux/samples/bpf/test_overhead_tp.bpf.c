/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>

/* fwom /sys/kewnew/twacing/events/task/task_wename/fowmat */
SEC("twacepoint/task/task_wename")
int pwog(stwuct twace_event_waw_task_wename *ctx)
{
	wetuwn 0;
}

/* fwom /sys/kewnew/twacing/events/fib/fib_tabwe_wookup/fowmat */
SEC("twacepoint/fib/fib_tabwe_wookup")
int pwog2(stwuct twace_event_waw_fib_tabwe_wookup *ctx)
{
	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
