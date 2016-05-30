/*
 * 从文件中读取数据插入到数据库的表当中
 *
 */

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{	
	MYSQL *  handler;
	handler=mysql_init(NULL);
	if(handler==NULL)
	{
		printf("mysql_init error:\n");
		exit(-1);
	}
	if(mysql_real_connect(handler,"localhost","root","123456","904db",0,NULL,0)==NULL)
	{
		printf("%s\n",mysql_error(handler));
		exit(-1);
	}
	mysql_query(handler,"select * from student");
	MYSQL_RES * res=mysql_store_result(handler);

	MYSQL_ROW  row_data;
    row_data = mysql_fetch_row(res);

	int fd = open("data", O_RDWR);
	if (fd < 0)
	{
		perror("open error");
		exit(1);
	}

	char buffer[1024];
	char sid[10];
	char data[100];
	memset(data, 0, sizeof(data));
	memset(buffer, 0, sizeof(buffer));
	memset(sid, 0, sizeof(sid));
	int ret;
	ret = read(fd, buffer, sizeof(buffer)-1);
	if (ret < 0)
	{
		perror("read error");
		exit(1);
	}
	buffer[1023] = '\0';
	while(ret > 0)
	{
		int i = 0;
		char *tmp = buffer;
		char* tmp2 = buffer;
		while(*tmp != '\0')
		{
			i = 0;
			memset(sid, 0, sizeof(sid));
			while(*tmp2 != '\n' && *tmp2 != 0)
			{
				sid[i] = *tmp2;
				tmp2++;
				i++;
			}
			printf("%s\n",sid );
			sprintf(data, "insert into student(sid) values('%s')", sid);
			printf("%s\n", data);			
			mysql_query(handler, data);
			memset(data, 0, sizeof(data));
			memset(sid, 0, sizeof(sid));
			tmp = ++tmp2;
		}
		memset(buffer, 0, sizeof(buffer));
		ret = read(fd, buffer, sizeof(buffer));		
	}
    mysql_close(handler);	
	return 0;
}



