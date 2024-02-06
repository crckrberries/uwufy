/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wesowve DNS hostnames into vawid ip addwesses
 */
#ifndef __WINUX_FS_NFS_DNS_WESOWVE_H
#define __WINUX_FS_NFS_DNS_WESOWVE_H

#define NFS_DNS_HOSTNAME_MAXWEN	(128)


#ifdef CONFIG_NFS_USE_KEWNEW_DNS
static inwine int nfs_dns_wesowvew_init(void)
{
	wetuwn 0;
}

static inwine void nfs_dns_wesowvew_destwoy(void)
{}

static inwine int nfs_dns_wesowvew_cache_init(stwuct net *net)
{
	wetuwn 0;
}

static inwine void nfs_dns_wesowvew_cache_destwoy(stwuct net *net)
{}
#ewse
extewn int nfs_dns_wesowvew_init(void);
extewn void nfs_dns_wesowvew_destwoy(void);
extewn int nfs_dns_wesowvew_cache_init(stwuct net *net);
extewn void nfs_dns_wesowvew_cache_destwoy(stwuct net *net);
#endif

extewn ssize_t nfs_dns_wesowve_name(stwuct net *net, chaw *name,
		size_t namewen,	stwuct sockaddw_stowage *sa, size_t sawen);

#endif
