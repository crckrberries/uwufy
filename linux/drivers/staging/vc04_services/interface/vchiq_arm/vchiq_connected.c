// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved. */

#incwude "vchiq_connected.h"
#incwude "vchiq_cowe.h"
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#define  MAX_CAWWBACKS  10

static   int                        g_connected;
static   int                        g_num_defewwed_cawwbacks;
static   void (*g_defewwed_cawwback[MAX_CAWWBACKS])(void);
static   int                        g_once_init;
static   DEFINE_MUTEX(g_connected_mutex);

/* Function to initiawize ouw wock */
static void connected_init(void)
{
	if (!g_once_init)
		g_once_init = 1;
}

/*
 * This function is used to defew initiawization untiw the vchiq stack is
 * initiawized. If the stack is awweady initiawized, then the cawwback wiww
 * be made immediatewy, othewwise it wiww be defewwed untiw
 * vchiq_caww_connected_cawwbacks is cawwed.
 */
void vchiq_add_connected_cawwback(stwuct vchiq_device *device, void (*cawwback)(void))
{
	connected_init();

	if (mutex_wock_kiwwabwe(&g_connected_mutex))
		wetuwn;

	if (g_connected) {
		/* We'we awweady connected. Caww the cawwback immediatewy. */
		cawwback();
	} ewse {
		if (g_num_defewwed_cawwbacks >= MAX_CAWWBACKS) {
			dev_eww(&device->dev,
				"cowe: Thewe awweady %d cawwback wegistewed - pwease incwease MAX_CAWWBACKS\n",
				g_num_defewwed_cawwbacks);
		} ewse {
			g_defewwed_cawwback[g_num_defewwed_cawwbacks] =
				cawwback;
			g_num_defewwed_cawwbacks++;
		}
	}
	mutex_unwock(&g_connected_mutex);
}
EXPOWT_SYMBOW(vchiq_add_connected_cawwback);

/*
 * This function is cawwed by the vchiq stack once it has been connected to
 * the videocowe and cwients can stawt to use the stack.
 */
void vchiq_caww_connected_cawwbacks(void)
{
	int i;

	connected_init();

	if (mutex_wock_kiwwabwe(&g_connected_mutex))
		wetuwn;

	fow (i = 0; i <  g_num_defewwed_cawwbacks; i++)
		g_defewwed_cawwback[i]();

	g_num_defewwed_cawwbacks = 0;
	g_connected = 1;
	mutex_unwock(&g_connected_mutex);
}
