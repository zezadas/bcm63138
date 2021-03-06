/*
 * Copyright 2014 Trend Micro Incorporated
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software without 
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

#include "udb/shell/shell_ioctl.h"

#include "ioc_common.h"
#include "ioc_wrs.h"

#ifdef __INTERNAL__
#include "ioc_internal.h"
#endif

int get_fw_user_domain_list(void **output, unsigned int *buf_used_len, int flag)
{
	const int buf_len = (sizeof(udb_dn_ioctl_entry_t) * UDB_DOMAIN_LOG_SIZE) +
		(sizeof(udb_dn_ioctl_mac_t) * DEVID_MAX_USER) +
		(sizeof(udb_dn_ioctl_list_t)); //max

	udb_shell_ioctl_t msg;

	*output = calloc(buf_len, sizeof(char));
	if (!*output)
	{
		DBG("Cannot allocate buffer space %u bytes", buf_len);
		return -1;
	}

	/* prepare and do ioctl */
	udb_shell_init_ioctl_entry(&msg);
	msg.nr = UDB_IOCTL_NR_WRS;
	switch (flag)
	{
	case 0:
		msg.op = UDB_IOCTL_WRS_OP_GET_DN_LOG;
		break;
	case 1:
		msg.op = UDB_IOCTL_WRS_OP_GET_DN_LOG_RESET;
		break;
	}

	udb_shell_ioctl_set_out_buf(&msg, (*output), buf_len, buf_used_len);

	return run_ioctl(UDB_SHELL_IOCTL_CHRDEV_PATH, UDB_SHELL_IOCTL_CMD_WRS, &msg);
}

int set_fw_user_domain_clear(void)
{
	udb_shell_ioctl_t msg;
	uint32_t buf_used_len = 0;

	/* prepare and do ioctl */
	udb_shell_init_ioctl_entry(&msg);
	msg.nr = UDB_IOCTL_NR_WRS;
	msg.op = UDB_IOCTL_WRS_OP_RESET_DN_LOG;

	(&msg)->out = 0;
	(&msg)->out_len = 0;
	(&msg)->out_used_len = (uintptr_t)&buf_used_len;

	return run_ioctl(UDB_SHELL_IOCTL_CHRDEV_PATH, UDB_SHELL_IOCTL_CMD_WRS, &msg);
}

int get_fw_wrs_url_list(void **output, unsigned int *buf_used_len)
{
	const int buf_len = (sizeof(udb_url_ioctl_entry_t) * UDB_URL_LOG_SIZE) +
		(sizeof(udb_url_ioctl_list_t)); //max

	udb_shell_ioctl_t msg;

	*output = calloc(buf_len, sizeof(char));
	if (!*output)
	{
		DBG("Cannot allocate buffer space %u bytes", buf_len);
		return -1;
	}

	/* prepare and do ioctl */
	udb_shell_init_ioctl_entry(&msg);
	msg.nr = UDB_IOCTL_NR_WRS;
	msg.op = UDB_IOCTL_WRS_OP_GET_LOG;
	udb_shell_ioctl_set_out_buf(&msg, (*output), buf_len, buf_used_len);

	return run_ioctl(UDB_SHELL_IOCTL_CHRDEV_PATH, UDB_SHELL_IOCTL_CMD_WRS, &msg);
}

////////////////////////////////////////////////////////////////////////////////

static int _get_user_domain(int flag)
{
	int ret = 0;
	unsigned int m, d, buf_pos, ioc_buf;
	char *buf = NULL;

	udb_dn_ioctl_list_t *dmn = NULL;
	udb_dn_ioctl_mac_t *mac = NULL;
	udb_dn_ioctl_entry_t *ent = NULL;

	//process ioctl request & response
	ret = get_fw_user_domain_list((void **) &buf, &ioc_buf, flag);
	if (ret)
	{
		DBG("Error: get user!(%d)\n", ret);
	}

	if (buf)
	{
		//printf("Debug: ioc buf len: %u \n", ioc_buf);
		dmn = (udb_dn_ioctl_list_t *) buf;
		buf_pos = sizeof(udb_dn_ioctl_list_t);

		printf("---mac_count = %u ---\n", dmn->mac_cnt);
		for (m = 0; m < dmn->mac_cnt; m++)
		{
			mac = (udb_dn_ioctl_mac_t *) (buf + buf_pos);
			printf("---------------------------------\n");
			printf("mac : " MAC_OCTET_FMT "\n", MAC_OCTET_EXPAND(mac->mac));

			buf_pos += sizeof(udb_dn_ioctl_mac_t);
			printf("---domain_count = %u ---\n", mac->domain_cnt);
			printf("\ttime------------domain-----------\n");
			for (d = 0; d < mac->domain_cnt; d++)
			{
				//ent = (udb_dn_ioctl_entry_t *)(buf + buf_pos);
				ent = &mac->entry[d];
				printf("\t%llu", ent->time);
				printf("\t%s\n", ent->domain);

				//buf_pos += sizeof(udb_dn_ioctl_entry_t);
			}
			buf_pos += (sizeof(udb_dn_ioctl_entry_t) * mac->domain_cnt);
		}

		free(buf);
	}

	return ret;
}

int get_user_domain(void)
{
	return _get_user_domain(0);
}

int get_user_domain_clear(void)
{
	return _get_user_domain(1);
}

int clear_user_domain(void)
{
	int ret = 0;

	ret = set_fw_user_domain_clear();
	if (ret)
	{
		DBG("Error: clear domain!(%d)\n", ret);
	}
	printf("result: %s\n", ret ? "NG" : "OK");

	return ret;
}

int get_wrs_url(void)
{
	int ret = 0;
	unsigned int e, buf_pos, ioc_buf;
	char *buf = NULL;

	udb_url_ioctl_list_t *tbl = NULL;

	//process ioctl request & response
	ret = get_fw_wrs_url_list((void **) &buf, &ioc_buf);
	if (ret)
	{
		DBG("Error: get user!(%d)\n", ret);
	}

	if (buf)
	{
		tbl = (udb_url_ioctl_list_t *) buf;
		buf_pos = sizeof(udb_url_ioctl_list_t);

		printf("---entry_cnt = %u ---\n", tbl->entry_cnt);
		printf("%-10s\t%-18s\t%-10s%-13s%s\n", "time", "mac", "cat_id", "action", "url");
		printf("---------------------------------------------------------------------------\n");
		for (e = 0; e < tbl->entry_cnt; e++)
		{

			printf("%-10llu\t", tbl->entry[e].time);
			printf(MAC_OCTET_FMT"\t", MAC_OCTET_EXPAND(tbl->entry[e].mac));
			/* 10 (fixed width) = 6 (strlen("cat_id")) + 4 (reserved) */
			printf("%-10d", tbl->entry[e].cat_id);
			/* 13 (fixed width) = 9 (strlen("2-Monitor")) + 4 (reserved) */
			printf("%-13s", tbl->entry[e].action == 1 ? "1-Block" : tbl->entry[e].action == 2 ? "2-Monitor" : "0-Accept");
			printf("%s\n", tbl->entry[e].domain);
		}

		free(buf);
	}

	return ret;
}

int wrs_options_init(struct cmd_option *cmd)
{
#define HELP_LEN_MAX 1024
	int i = 0, j;
	static char help[HELP_LEN_MAX];
	int len = 0;

	cmd->opts[i].action = ACT_WRS_GET_USR_DOMAIN;
	cmd->opts[i].name = "get_user_domain";
	cmd->opts[i].cb = get_user_domain;
	OPTS_IDX_INC(i);

	cmd->opts[i].action = ACT_WRS_CLR_USR_DOMAIN;
	cmd->opts[i].name = "clear_user_domain";
	cmd->opts[i].cb = clear_user_domain;
	OPTS_IDX_INC(i);

	cmd->opts[i].action = ACT_WRS_GET_USR_DOMAIN_CLEAR;
	cmd->opts[i].name = "get_user_domain_clear";
	cmd->opts[i].cb = get_user_domain_clear;
	OPTS_IDX_INC(i);

	cmd->opts[i].action = ACT_WRS_GET_WRS_URL;
	cmd->opts[i].name = "get_wrs_url";
	cmd->opts[i].cb = get_wrs_url;
	OPTS_IDX_INC(i);

#ifdef __INTERNAL__
	if (0 > (i = wrs_internal_opts_init(cmd, i)))
	{
		return -1;
	}
#endif

	len += snprintf(help + len, HELP_LEN_MAX - len, "%*s \n",
		HELP_INDENT_L, "");

	for (j = 0; j < i; j++)
	{
		len += snprintf(help + len, HELP_LEN_MAX - len, "%*s %s\n",
			HELP_INDENT_L, (j == 0) ? "wrs actions:" : "",
			cmd->opts[j].name);
	}

	cmd->help = help;

	return 0;
}

