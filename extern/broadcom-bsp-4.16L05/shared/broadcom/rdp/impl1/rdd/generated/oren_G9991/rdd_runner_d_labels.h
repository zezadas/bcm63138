#ifndef RUNNER_D_CODE_ADDRESSES
#define RUNNER_D_CODE_ADDRESSES

#define runner_d_start_task_initialization_task		(0x14)
#define runner_d_initialization_task		(0x14)
#define runner_d_start_task_timer_scheduler_set		(0x21C8)
#define runner_d_timer_scheduler_set		(0x21C8)
#define runner_d_start_task_cpu_tx_wakeup_request		(0x1EB8)
#define runner_d_cpu_tx_wakeup_request		(0x1EB8)
#define runner_d_start_task_lan_cpu_wakeup_request		(0x47C)
#define runner_d_lan_cpu_wakeup_request		(0x47C)
#define runner_d_start_task_lan_broadcom_switch_wakeup_request		(0x4B4)
#define runner_d_lan_broadcom_switch_wakeup_request		(0x4B4)
#define runner_d_start_task_lan_normal_wakeup_request		(0x1CC)
#define runner_d_lan_normal_wakeup_request		(0x1CC)
#define runner_d_start_task_upstream_flooding_wakeup_request		(0x23BC)
#define runner_d_upstream_flooding_wakeup_request		(0x23BC)
#define runner_d_start_task_debug_routine		(0xE4)
#define runner_d_debug_routine		(0xE4)
#define runner_d_start_task_lan_direct_to_cpu_wakeup_request		(0x450)
#define runner_d_lan_direct_to_cpu_wakeup_request		(0x450)
#define runner_d_ingress_classification_key_src_ip		(0x1A00)
#define runner_d_ingress_classification_key_dst_ip		(0x1A4C)
#define runner_d_ingress_classification_key_ipv6_flow_label		(0x1A98)
#define runner_d_ingress_classification_key_generic_rule_1		(0x1AC0)
#define runner_d_ingress_classification_key_generic_rule_2		(0x1AC8)
#define runner_d_ingress_classification_key_outer_tpid		(0x1B34)
#define runner_d_ingress_classification_key_inner_tpid		(0x1B40)
#define runner_d_ingress_classification_key_src_port		(0x1B60)
#define runner_d_ingress_classification_key_dst_port		(0x1B80)
#define runner_d_ingress_classification_key_outer_vlan		(0x1BA0)
#define runner_d_ingress_classification_key_inner_vlan		(0x1BB8)
#define runner_d_ingress_classification_key_dst_mac		(0x1BD4)
#define runner_d_ingress_classification_key_src_mac		(0x1BDC)
#define runner_d_ingress_classification_key_ether_type		(0x1C04)
#define runner_d_ingress_classification_key_ip_protocol		(0x1C18)
#define runner_d_ingress_classification_key_dscp		(0x1C3C)
#define runner_d_ingress_classification_key_ssid		(0x1C58)
#define runner_d_ingress_classification_key_ingress_port		(0x1C70)
#define runner_d_ingress_classification_key_outer_pbits		(0x1C80)
#define runner_d_ingress_classification_key_inner_pbits		(0x1C98)
#define runner_d_ingress_classification_key_number_of_vlans		(0x1CB4)
#define runner_d_ingress_classification_key_layer3_protocol		(0x1CC4)
#define runner_d_global_register_update_r0		(0x2188)
#define runner_d_global_register_update_r1		(0x2190)
#define runner_d_global_register_update_r2		(0x2198)
#define runner_d_global_register_update_r3		(0x21A0)
#define runner_d_global_register_update_r4		(0x21A8)
#define runner_d_global_register_update_r5		(0x21B0)
#define runner_d_global_register_update_r6		(0x21B8)
#define runner_d_global_register_update_r7		(0x21C0)
#define runner_d_upstream_ingress_rate_limiter_budget_allocate		(0x2248)
#define runner_d_upstream_quasi_budget_allocate		(0x22C8)

#endif
