#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//1.从标准输入获取值插入到数据库的表中
//2.执行插入值时,必须考虑主键值是否重复

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

	/*输入要插入的数据*/
	char sid[20];
	char buffer[100];
	memset(buffer, 0, sizeof(buffer));
	memset(sid, 0, sizeof(sid));
	printf("please input sid:");
	gets(sid);
	//printf("\n");
	sprintf(buffer, "insert into student(sid) values('%s')", sid);
	printf("%s\n",buffer );

    /*输出行数据*/
    MYSQL_ROW  row_data;
    row_data = mysql_fetch_row(res);
    int i = 0;
    while(row_data != NULL)
    {
    	printf("%s\n", *row_data );
    	i++;
    	if (!strcmp(sid, *row_data))
    	{
    		break;
    	}
        row_data = mysql_fetch_row(res);
    }
    /*判断如果不重复则将其插入到表中*/
    if (row_data == NULL)
    {
       	mysql_query(handler, buffer);
    }
    mysql_close(handler);	
	return 0;
}
