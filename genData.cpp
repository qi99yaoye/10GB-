/*******************************************************************
* ���ļ��ĳ���ʵ����һ���Զ����������¼�ĳ��������ɵļ�¼�ܳ���Ϊ100B *
* �ó������ɹ���ִ������ĵ�һ������Ϊ����Ԫ�ظ������ڶ�������Ϊһ�� *
* ���������ڴ洢���ɵ�����                                           *
* �ó����޸���PennySort�����ص�SortGen���롣                         *
* ��Ҫ�޸ģ���ʹ��buffer,��������һ����¼ֱ��д���ļ����������ϣ������� *
* ���������������������                                            *
*******************************************************************/

#include <stdlib.h>
#include <stdio.h>
/*******************************************************************
* �������¼: �ؼ��֣�10 bytes,	���кţ�10 bytes������   80 bytes   *
*******************************************************************/
struct record
{
	char    sortkey[10];
	char    recnum[10];
	char    txtfld[80];
};

const		int RecordSize = (sizeof(struct record));  //��¼��С100 bytes
/*******************************************************************
*  ������ɹؼ���                                                   *
*******************************************************************/
void rand_key(char key[10])
{
	unsigned    temp;

	// �����������,���ɵķ�����' '��'~'֮��
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
*    ����һ�������¼                                                     *
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
*    ����ָ�������������¼�������Դ洢�����������������Դ                   *
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
		printf("������Ҫ���ɵ����ݸ������Լ��洢�ļ�����\n ���磺 EasyGenData 1000000 d:\tmp.dat");
		exit(1);
	}

	DesiredRecords = _atoi64(argv[1]);
	OutFileName = argv[2];

	OutFile = fopen(OutFileName, "w+b");
	if (OutFile == NULL)
	{
		fprintf(stderr, "�ļ�����ʧ�� %s\n", OutFileName);
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

