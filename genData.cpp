/*******************************************************************
* 该文件的程序实现了一个自动生成随机记录的程序，所生成的记录总长度为100B *
* 该程序编译成功后，执行输入的第一个参数为生成元素个数，第二个参数为一文 *
* 件名，用于存储生成的数据                                           *
* 该程序修改自PennySort上下载的SortGen代码。                         *
* 主要修改：不使用buffer,而是生成一个记录直接写入文件。在性能上，若生成 *
* 大批量数据则会有所降低                                            *
*******************************************************************/

#include <stdlib.h>
#include <stdio.h>
/*******************************************************************
* 待排序记录: 关键字：10 bytes,	序列号：10 bytes，数据   80 bytes   *
*******************************************************************/
struct record
{
	char    sortkey[10];
	char    recnum[10];
	char    txtfld[80];
};

const		int RecordSize = (sizeof(struct record));  //记录大小100 bytes
/*******************************************************************
*  随机生成关键字                                                   *
*******************************************************************/
void rand_key(char key[10])
{
	unsigned    temp;

	// 生成随机符号,生成的符号在' '到'~'之间
	temp = rand()*rand();
	key[3] = ' ' + (temp % 95);
	temp /= 95;
	key[2] = ' ' + (temp % 95);
	temp /= 95;
	key[1] = ' ' + (temp % 95);
	temp /= 95;
	key[0] = ' ' + (temp % 95);

	temp = rand()*rand();
	temp /= 52;                            
	key[7] = ' ' + (temp % 95);
	temp /= 95;
	key[6] = ' ' + (temp % 95);
	temp /= 95;
	key[5] = ' ' + (temp % 95);
	temp /= 95;
	key[4] = ' ' + (temp % 95);

	temp = rand()*rand();
	temp /= 52 * 95 * 95;                    
	key[9] = ' ' + (temp % 95);
	temp /= 95;
	key[8] = ' ' + (temp % 95);
}
/*************************************************************************
*    生成一个随机记录                                                     *
*************************************************************************/
void gen_rec(struct record *rp)
{
	static   int   current;
	char        *sptr;
	static char nxtchar = 'A';
	int         i, j;

	rand_key(rp->sortkey);                    
	sprintf(rp->recnum, "%10d", current++);
	sptr = rp->txtfld;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 10; j++)
			*sptr++ = nxtchar;
		nxtchar++;
		if (nxtchar > 'Z') nxtchar = 'A';
	}
	sptr[-2] = '\r';
	sptr[-1] = '\n';
}

/*************************************************************************
*    生成指定个数的随机记录，并加以存储，用作排序的数据来源                   *
*************************************************************************/
int main(int argc, char * argv[])
{
	__int64   GeneratedRecords = 0;       // Records generated so far
	__int64   DesiredRecords = 0;       // Target number of records
	char		*OutFileName;
	FILE        * OutFile;			// Output file
	struct record rec;

	if (argc < 2)
	{
		printf("请输入要生成的数据个数，以及存储文件名称\n 例如： EasyGenData 1000000 d:\tmp.dat");
		exit(1);
	}

	DesiredRecords = _atoi64(argv[1]);
	OutFileName = argv[2];

	OutFile = fopen(OutFileName, "w+b");
	if (OutFile == NULL)
	{
		fprintf(stderr, "文件创建失败 %s\n", OutFileName);
		exit(2);
	}
	while (GeneratedRecords < DesiredRecords)
	{
		gen_rec(&rec);
		fwrite((void*)&rec, RecordSize, 1, OutFile);
		GeneratedRecords++;
	}
	fclose(OutFile);
}

