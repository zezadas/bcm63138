#ifndef _WINBINDD_PROTO_H_
#define _WINBINDD_PROTO_H_

/* This file is automatically generated with "make proto". DO NOT EDIT */


/* The following definitions come from nsswitch/winbindd.c  */

struct event_context *winbind_event_context(void);
void add_fd_event(struct fd_event *ev);
void remove_fd_event(struct fd_event *ev);
void setup_async_read(struct fd_event *event, void *data, size_t length,
		      void (*finished)(void *private_data, BOOL success),
		      void *private_data);
void setup_async_write(struct fd_event *event, void *data, size_t length,
		       void (*finished)(void *private_data, BOOL success),
		       void *private_data);
void request_error(struct winbindd_cli_state *state);
void request_ok(struct winbindd_cli_state *state);
void request_finished_cont(void *private_data, BOOL success);
void winbind_check_sighup(const char *logfile);
void winbind_check_sigterm(bool in_parent);
int main(int argc, char **argv, char **envp);

/* The following definitions come from nsswitch/winbindd_ads.c  */


/* The following definitions come from nsswitch/winbindd_async.c  */

void do_async_domain(TALLOC_CTX *mem_ctx, struct winbindd_domain *domain,
		     const struct winbindd_request *request,
		     void (*cont)(TALLOC_CTX *mem_ctx, BOOL success,
				  struct winbindd_response *response,
				  void *c, void *private_data),
		     void *c, void *private_data);
void winbindd_set_mapping_async(TALLOC_CTX *mem_ctx, const struct id_map *map,
			     void (*cont)(void *private_data, BOOL success),
			     void *private_data);
enum winbindd_result winbindd_dual_set_mapping(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
void winbindd_set_hwm_async(TALLOC_CTX *mem_ctx, const struct unixid *xid,
			     void (*cont)(void *private_data, BOOL success),
			     void *private_data);
enum winbindd_result winbindd_dual_set_hwm(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
void winbindd_sids2xids_async(TALLOC_CTX *mem_ctx, void *sids, int size,
			 void (*cont)(void *private_data, BOOL success, void *data, int len),
			 void *private_data);
enum winbindd_result winbindd_dual_sids2xids(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);
void winbindd_sid2uid_async(TALLOC_CTX *mem_ctx, const DOM_SID *sid,
			 void (*cont)(void *private_data, BOOL success, uid_t uid),
			 void *private_data);
enum winbindd_result winbindd_dual_sid2uid(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);
void winbindd_uid2name_async(TALLOC_CTX *mem_ctx, uid_t uid,
			     void (*cont)(void *private_data, BOOL success,
					  const char *name),
			     void *private_data);
enum winbindd_result winbindd_dual_uid2name(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_name2uid(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
void winbindd_sid2gid_async(TALLOC_CTX *mem_ctx, const DOM_SID *sid,
			 void (*cont)(void *private_data, BOOL success, gid_t gid),
			 void *private_data);
enum winbindd_result winbindd_dual_sid2gid(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);
void winbindd_gid2name_async(TALLOC_CTX *mem_ctx, gid_t gid,
			     void (*cont)(void *private_data, BOOL success,
					  const char *name),
			     void *private_data);
enum winbindd_result winbindd_dual_gid2name(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_name2gid(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
void winbindd_lookupsid_async(TALLOC_CTX *mem_ctx, const DOM_SID *sid,
			      void (*cont)(void *private_data, BOOL success,
					   const char *dom_name,
					   const char *name,
					   enum lsa_SidType type),
			      void *private_data);
enum winbindd_result winbindd_dual_lookupsid(struct winbindd_domain *domain,
					     struct winbindd_cli_state *state);
void winbindd_lookupname_async(TALLOC_CTX *mem_ctx,
			       const char *dom_name, const char *name,
			       void (*cont)(void *private_data, BOOL success,
					    const DOM_SID *sid,
					    enum lsa_SidType type),
			       void *private_data);
enum winbindd_result winbindd_dual_lookupname(struct winbindd_domain *domain,
					      struct winbindd_cli_state *state);
BOOL print_sidlist(TALLOC_CTX *mem_ctx, const DOM_SID *sids,
		   size_t num_sids, char **result, ssize_t *len);
enum winbindd_result winbindd_dual_lookuprids(struct winbindd_domain *domain,
					      struct winbindd_cli_state *state);
void winbindd_getsidaliases_async(struct winbindd_domain *domain,
				  TALLOC_CTX *mem_ctx,
				  const DOM_SID *sids, size_t num_sids,
			 	  void (*cont)(void *private_data,
				 	       BOOL success,
					       const DOM_SID *aliases,
					       size_t num_aliases),
				  void *private_data);
enum winbindd_result winbindd_dual_getsidaliases(struct winbindd_domain *domain,
						 struct winbindd_cli_state *state);
void winbindd_gettoken_async(TALLOC_CTX *mem_ctx, const DOM_SID *user_sid,
			     void (*cont)(void *private_data, BOOL success,
					  DOM_SID *sids, size_t num_sids),
			     void *private_data);
void query_user_async(TALLOC_CTX *mem_ctx, struct winbindd_domain *domain,
		      const DOM_SID *sid,
		      void (*cont)(void *private_data, BOOL success,
				   const char *acct_name,
				   const char *full_name,
				   const char *homedir,
				   const char *shell,
				   gid_t gid,
				   uint32 group_rid),
		      void *private_data);
void winbindd_uid2sid_async(TALLOC_CTX *mem_ctx, uid_t uid,
			    void (*cont)(void *private_data, BOOL success, const char *sid),
			    void *private_data);
enum winbindd_result winbindd_dual_uid2sid(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);
void winbindd_gid2sid_async(TALLOC_CTX *mem_ctx, gid_t gid,
			    void (*cont)(void *private_data, BOOL success, const char *sid),
			    void *private_data);
enum winbindd_result winbindd_dual_gid2sid(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);
void winbindd_dump_maps_async(TALLOC_CTX *mem_ctx, void *data, int size,
			 void (*cont)(void *private_data, BOOL success),
			 void *private_data);
enum winbindd_result winbindd_dual_dump_maps(struct winbindd_domain *domain,
					   struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_cache.c  */

void winbindd_check_cache_size(time_t t);
struct cache_entry *centry_start(struct winbindd_domain *domain, NTSTATUS status);
NTSTATUS wcache_cached_creds_exist(struct winbindd_domain *domain, const DOM_SID *sid);
NTSTATUS wcache_get_creds(struct winbindd_domain *domain, 
			  TALLOC_CTX *mem_ctx, 
			  const DOM_SID *sid,
			  const uint8 **cached_nt_pass,
			  const uint8 **cached_salt);
NTSTATUS wcache_save_creds(struct winbindd_domain *domain, 
			   TALLOC_CTX *mem_ctx, 
			   const DOM_SID *sid, 
			   const uint8 nt_pass[NT_HASH_LEN]);
void wcache_invalidate_samlogon(struct winbindd_domain *domain, 
				NET_USER_INFO_3 *info3);
void wcache_invalidate_cache(void);
BOOL initialize_winbindd_cache(void);
void cache_store_response(pid_t pid, struct winbindd_response *response);
BOOL cache_retrieve_response(pid_t pid, struct winbindd_response * response);
void cache_cleanup_response(pid_t pid);
BOOL lookup_cached_sid(TALLOC_CTX *mem_ctx, const DOM_SID *sid,
		       const char **domain_name, const char **name,
		       enum lsa_SidType *type);
BOOL lookup_cached_name(TALLOC_CTX *mem_ctx,
			const char *domain_name,
			const char *name,
			DOM_SID *sid,
			enum lsa_SidType *type);
void cache_name2sid(struct winbindd_domain *domain, 
		    const char *domain_name, const char *name,
		    enum lsa_SidType type, const DOM_SID *sid);
void wcache_flush_cache(void);
NTSTATUS wcache_count_cached_creds(struct winbindd_domain *domain, int *count);
NTSTATUS wcache_remove_oldest_cached_creds(struct winbindd_domain *domain, const DOM_SID *sid) ;
BOOL set_global_winbindd_state_offline(void);
void set_global_winbindd_state_online(void);
BOOL get_global_winbindd_state_offline(void);

/* The following definitions come from nsswitch/winbindd_ccache_access.c  */

void winbindd_ccache_ntlm_auth(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_ccache_ntlm_auth(struct winbindd_domain *domain,
						struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_cm.c  */

void set_domain_offline(struct winbindd_domain *domain);
void set_domain_online_request(struct winbindd_domain *domain);
void winbind_add_failed_connection_entry(const struct winbindd_domain *domain,
					const char *server,
					NTSTATUS result);
void invalidate_cm_connection(struct winbindd_cm_conn *conn);
void close_conns_after_fork(void);
NTSTATUS init_dc_connection(struct winbindd_domain *domain);
NTSTATUS cm_connect_sam(struct winbindd_domain *domain, TALLOC_CTX *mem_ctx,
			struct rpc_pipe_client **cli, POLICY_HND *sam_handle);
NTSTATUS cm_connect_lsa(struct winbindd_domain *domain, TALLOC_CTX *mem_ctx,
			struct rpc_pipe_client **cli, POLICY_HND *lsa_policy);
NTSTATUS cm_connect_netlogon(struct winbindd_domain *domain,
			     struct rpc_pipe_client **cli);

/* The following definitions come from nsswitch/winbindd_cred_cache.c  */

void ccache_remove_all_after_fork(void);
void ccache_regain_all_now(void);
BOOL ccache_entry_exists(const char *username);
BOOL ccache_entry_identical(const char *username, uid_t uid, const char *ccname);
NTSTATUS add_ccache_to_list(const char *princ_name,
			    const char *ccname,
			    const char *service,
			    const char *username, 
			    const char *realm,
			    uid_t uid,
			    time_t create_time, 
			    time_t ticket_end, 
			    time_t renew_until, 
			    BOOL postponed_request);
NTSTATUS remove_ccache(const char *username);
struct WINBINDD_MEMORY_CREDS *find_memory_creds_by_name(const char *username);
NTSTATUS winbindd_add_memory_creds(const char *username, uid_t uid, const char *pass);
NTSTATUS winbindd_delete_memory_creds(const char *username);
NTSTATUS winbindd_replace_memory_creds(const char *username, const char *pass);

/* The following definitions come from nsswitch/winbindd_creds.c  */

NTSTATUS winbindd_get_creds(struct winbindd_domain *domain,
			    TALLOC_CTX *mem_ctx,
			    const DOM_SID *sid,
			    NET_USER_INFO_3 **info3,
			    const uint8 *cached_nt_pass[NT_HASH_LEN],
			    const uint8 *cred_salt[NT_HASH_LEN]);
NTSTATUS winbindd_store_creds(struct winbindd_domain *domain,
			      TALLOC_CTX *mem_ctx, 
			      const char *user, 
			      const char *pass, 
			      NET_USER_INFO_3 *info3,
			      const DOM_SID *user_sid);
NTSTATUS winbindd_update_creds_by_info3(struct winbindd_domain *domain,
				        TALLOC_CTX *mem_ctx,
				        const char *user,
				        const char *pass,
				        NET_USER_INFO_3 *info3);
NTSTATUS winbindd_update_creds_by_sid(struct winbindd_domain *domain,
				      TALLOC_CTX *mem_ctx,
				      const DOM_SID *sid,
				      const char *pass);
NTSTATUS winbindd_update_creds_by_name(struct winbindd_domain *domain,
				       TALLOC_CTX *mem_ctx,
				       const char *user,
				       const char *pass);

/* The following definitions come from nsswitch/winbindd_dual.c  */

void async_request(TALLOC_CTX *mem_ctx, struct winbindd_child *child,
		   struct winbindd_request *request,
		   struct winbindd_response *response,
		   void (*continuation)(void *private_data, BOOL success),
		   void *private_data);
void async_domain_request(TALLOC_CTX *mem_ctx,
			  struct winbindd_domain *domain,
			  struct winbindd_request *request,
			  struct winbindd_response *response,
			  void (*continuation)(void *private_data_data, BOOL success),
			  void *private_data_data);
void sendto_child(struct winbindd_cli_state *state,
		  struct winbindd_child *child);
void sendto_domain(struct winbindd_cli_state *state,
		   struct winbindd_domain *domain);
void setup_domain_child(struct winbindd_domain *domain,
			struct winbindd_child *child,
			const char *explicit_logfile);
void winbind_child_died(pid_t pid);
void winbindd_flush_negative_conn_cache(struct winbindd_domain *domain);
void winbind_msg_offline(int msg_type, struct process_id src,
			 void *buf, size_t len, void *private_data);
void winbind_msg_online(int msg_type, struct process_id src,
			void *buf, size_t len, void *private_data);
void winbind_msg_onlinestatus(int msg_type, struct process_id src,
			      void *buf, size_t len, void *private_data);

/* The following definitions come from nsswitch/winbindd_group.c  */

void winbindd_getgrnam(struct winbindd_cli_state *state);
void winbindd_getgrgid(struct winbindd_cli_state *state);
void winbindd_setgrent(struct winbindd_cli_state *state);
void winbindd_endgrent(struct winbindd_cli_state *state);
void winbindd_getgrent(struct winbindd_cli_state *state);
void winbindd_list_groups(struct winbindd_cli_state *state);
void winbindd_getgroups(struct winbindd_cli_state *state);
void winbindd_getusersids(struct winbindd_cli_state *state);
void winbindd_getuserdomgroups(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_getuserdomgroups(struct winbindd_domain *domain,
						    struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_misc.c  */

void winbindd_check_machine_acct(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_check_machine_acct(struct winbindd_domain *domain,
						      struct winbindd_cli_state *state);
void winbindd_list_trusted_domains(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_list_trusted_domains(struct winbindd_domain *domain,
							struct winbindd_cli_state *state);
void winbindd_getdcname(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_getdcname(struct winbindd_domain *domain,
					     struct winbindd_cli_state *state);
void winbindd_show_sequence(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_show_sequence(struct winbindd_domain *domain,
						 struct winbindd_cli_state *state);
void winbindd_domain_info(struct winbindd_cli_state *state);
void winbindd_ping(struct winbindd_cli_state *state);
void winbindd_info(struct winbindd_cli_state *state);
void winbindd_interface_version(struct winbindd_cli_state *state);
void winbindd_domain_name(struct winbindd_cli_state *state);
void winbindd_netbios_name(struct winbindd_cli_state *state);
void winbindd_priv_pipe_dir(struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_pam.c  */

struct winbindd_domain *find_auth_domain(struct winbindd_cli_state *state, 
					const char *domain_name);
void winbindd_pam_auth(struct winbindd_cli_state *state);
NTSTATUS winbindd_dual_pam_auth_cached(struct winbindd_domain *domain,
				       struct winbindd_cli_state *state,
				       NET_USER_INFO_3 **info3);
NTSTATUS winbindd_dual_pam_auth_kerberos(struct winbindd_domain *domain,
					 struct winbindd_cli_state *state, 
					 NET_USER_INFO_3 **info3);
NTSTATUS winbindd_dual_pam_auth_samlogon(struct winbindd_domain *domain,
					 struct winbindd_cli_state *state,
					 NET_USER_INFO_3 **info3);
enum winbindd_result winbindd_dual_pam_auth(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state) ;
void winbindd_pam_auth_crap(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_pam_auth_crap(struct winbindd_domain *domain,
						 struct winbindd_cli_state *state) ;
void winbindd_pam_chauthtok(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_pam_chauthtok(struct winbindd_domain *contact_domain,
						 struct winbindd_cli_state *state);
void winbindd_pam_logoff(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_pam_logoff(struct winbindd_domain *domain,
					      struct winbindd_cli_state *state) ;
void winbindd_pam_chng_pswd_auth_crap(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_pam_chng_pswd_auth_crap(struct winbindd_domain *domainSt, struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_passdb.c  */


/* The following definitions come from nsswitch/winbindd_reconnect.c  */


/* The following definitions come from nsswitch/winbindd_rpc.c  */


/* The following definitions come from nsswitch/winbindd_sid.c  */

void winbindd_lookupsid(struct winbindd_cli_state *state);
void winbindd_lookupname(struct winbindd_cli_state *state);
void winbindd_lookuprids(struct winbindd_cli_state *state);
void init_idmap_child(void);
struct winbindd_child *idmap_child(void);
void winbindd_sid_to_uid(struct winbindd_cli_state *state);
void winbindd_sid_to_gid(struct winbindd_cli_state *state);
void winbindd_sids_to_unixids(struct winbindd_cli_state *state);
void winbindd_set_mapping(struct winbindd_cli_state *state);
void winbindd_set_hwm(struct winbindd_cli_state *state);
void winbindd_uid_to_sid(struct winbindd_cli_state *state);
void winbindd_gid_to_sid(struct winbindd_cli_state *state);
void winbindd_allocate_uid(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_allocate_uid(struct winbindd_domain *domain,
						struct winbindd_cli_state *state);
void winbindd_allocate_gid(struct winbindd_cli_state *state);
enum winbindd_result winbindd_dual_allocate_gid(struct winbindd_domain *domain,
						struct winbindd_cli_state *state);
void winbindd_dump_maps(struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_user.c  */

enum winbindd_result winbindd_dual_userinfo(struct winbindd_domain *domain,
					    struct winbindd_cli_state *state);
void winbindd_getpwnam(struct winbindd_cli_state *state);
void winbindd_getpwuid(struct winbindd_cli_state *state);
void winbindd_setpwent(struct winbindd_cli_state *state);
void winbindd_endpwent(struct winbindd_cli_state *state);
void winbindd_getpwent(struct winbindd_cli_state *state);
void winbindd_list_users(struct winbindd_cli_state *state);

/* The following definitions come from nsswitch/winbindd_util.c  */

struct winbindd_domain *domain_list(void);
void free_domain_list(void);
void rescan_trusted_domains( void );
enum winbindd_result init_child_connection(struct winbindd_domain *domain,
					   void (*continuation)(void *private_data,
								BOOL success),
					   void *private_data);
enum winbindd_result winbindd_dual_init_connection(struct winbindd_domain *domain,
						   struct winbindd_cli_state *state);
BOOL init_domain_list(void);
struct winbindd_domain *find_domain_from_name_noinit(const char *domain_name);
struct winbindd_domain *find_domain_from_name(const char *domain_name);
struct winbindd_domain *find_domain_from_sid_noinit(const DOM_SID *sid);
struct winbindd_domain *find_domain_from_sid(const DOM_SID *sid);
struct winbindd_domain *find_our_domain(void);
struct winbindd_domain *find_root_domain(void);
struct winbindd_domain *find_builtin_domain(void);
struct winbindd_domain *find_lookup_domain_from_sid(const DOM_SID *sid);
struct winbindd_domain *find_lookup_domain_from_name(const char *domain_name);
BOOL winbindd_lookup_sid_by_name(TALLOC_CTX *mem_ctx,
				 struct winbindd_domain *domain, 
				 const char *domain_name,
				 const char *name, DOM_SID *sid, 
				 enum lsa_SidType *type);
BOOL winbindd_lookup_name_by_sid(TALLOC_CTX *mem_ctx,
				 DOM_SID *sid,
				 char **dom_name,
				 char **name,
				 enum lsa_SidType *type);
void free_getent_state(struct getent_state *state);
BOOL parse_domain_user(const char *domuser, fstring domain, fstring user);
BOOL parse_domain_user_talloc(TALLOC_CTX *mem_ctx, const char *domuser,
			      char **domain, char **user);
BOOL canonicalize_username(fstring username_inout, fstring domain, fstring user);
void fill_domain_username(fstring name, const char *domain, const char *user, BOOL can_assume);
char *get_winbind_priv_pipe_dir(void) ;
int open_winbindd_socket(void);
int open_winbindd_priv_socket(void);
void close_winbindd_socket(void);
struct winbindd_cli_state *winbindd_client_list(void);
void winbindd_add_client(struct winbindd_cli_state *cli);
void winbindd_remove_client(struct winbindd_cli_state *cli);
void winbindd_kill_all_clients(void);
int winbindd_num_clients(void);
NTSTATUS lookup_usergroups_cached(struct winbindd_domain *domain,
				  TALLOC_CTX *mem_ctx,
				  const DOM_SID *user_sid,
				  uint32 *p_num_groups, DOM_SID **user_sids);
void ws_name_replace( char *name, char replace );
void ws_name_return( char *name, char replace );

/* The following definitions come from nsswitch/winbindd_wins.c  */

void winbindd_wins_byip(struct winbindd_cli_state *state);
void winbindd_wins_byname(struct winbindd_cli_state *state);

#endif /*  _WINBINDD_PROTO_H_  */
