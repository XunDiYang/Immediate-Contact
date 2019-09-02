#include "include/server.h"

/*
void save_offline_message(struct Message msg) {
	cJSON *root = cJSON_Parse(msg.message);
	char *type = cJSON_GetObjectItem(root, "type")->valuestring;
	//ALL MESSAGE SHOULD BE CHAT MESSAGE!!!
	if (!(strcmp(type, "message/text") == 0 || strcmp(type, "message/text/group") == 0)) {

		free(root);
		return;
	}
	free(root);
	//
	/*

	char sqlcmd[4096];
	memset(sqlcmd, '\0', sizeof(sqlcmd));
	sprintf(sqlcmd, "insert into offlinemsg values(\'%s\', \'%s\')", msg.username, msg.message);
	sqlite3_exec(db, sqlcmd, NULL, NULL, NULL);
	*/
// }

/*

void send_offline_message(int userid) {
	
	char sqlcmd[4096];
	sprintf(sqlcmd, "select msg from offlinemsg where sendto=\'%s\'", username);
	char **res; char *errmsg; int nrow; int ncol;
	if (SQLITE_OK != sqlite3_get_table(db, sqlcmd, &res, &nrow, &ncol, &errmsg)) {
		printf("error while reading offline message: %s\n", errmsg);
		return;
	}
	char message[BUFFER_SIZE];
	int i, j; int nindex = ncol;
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			strcpy(message, res[nindex]);
			send_message_by_username(username, copy_string(message));
			nindex++;
		}
	}

	sprintf(sqlcmd, "delete from offlinemsg where sendto=\'%s\'", username);
	sqlite3_exec(db, sqlcmd, NULL, NULL, NULL);
}
*/