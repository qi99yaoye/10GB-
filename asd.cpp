#include<bits/stdc++.h>
using namespace std;
/*******************************************************************
* 待排序记录: 关键字：10 bytes,	序列号：10 bytes，数据   80 bytes   *
*******************************************************************/
struct record
{
	char    sortkey[10];
	char    recnum[10];
	char    txtfld[80];
};
const   int RecordSize          = 100;  
const   int  filesizenum=100000000;                      // 100 bytes
char	*sourceFileName, *destinyFileName;
char	*sortType;
#define readsize 100


/***********************************************************************/
//QuickSort是快速排序，该排序由两个函数组成，Partition和QuickSort
/***********************************************************************/
long Partition(record *data, long Low, long High)
{
	record pivotkey;
	pivotkey=data[Low];

	while(Low<High)
	{
		while((Low<High)&& strnicmp((char*)&data[High],(char*)&pivotkey,RecordSize)>=0)
			High--;
		data[Low] = data[High];
		
		while((Low<High) && strnicmp((char*)&data[Low], (char*)&pivotkey, RecordSize) <=0)
			Low++;
		data[High]=data[Low];
	}
	data[Low]=pivotkey;
	return Low;
}

void QuickSort(record *data, long Low, long High)
{
	int mid;
	if (Low>=High) return;
	else
	{
		mid=Partition(data, Low,High);
		QuickSort(data,Low,mid-1);
		QuickSort(data,mid+1,High);
	}
}

void split(char *filePath)
{

	FILE *in, *out=nullptr;
	char newFilePath[250];
	char midfile[250]; 
    string filepath;
	in = fopen(filePath, "r");
	if(in == nullptr){
	        printf("打开源文件失败\n");
	        exit(0);
	    }
	filepath = filePath;
	char tmp[readsize];
	char buf[readsize];
	int countNum = 0;
	int partNum = 1;
	while( fgets(buf, readsize, in) != NULL){
		if(countNum > filesizenum){
			countNum = 0;
			partNum++;
			fclose(out);
			out = nullptr;
		}
	    strcpy (tmp, buf);
		if( out == nullptr){
			string name =filepath.substr(0,filepath.rfind("."));   
			name = name + "-";
			strcpy (midfile, name.c_str());
			sprintf(newFilePath, "%s%d%s", midfile , partNum ,".txt");
			out = fopen(newFilePath , "a+");	
		}
		fputs(tmp,out);
		countNum += strlen(tmp);			     
	}
	fclose(in);
	fclose(out);
	cout<<"分割了"<<partNum<<"个文件"<<endl; 
	  	
}


void mergefile(string file1,string file2, string file3)
 {
 	char sfile1[255];
 	char sfile2[255];
 	char sfile3[255];
 	strcpy (sfile1, file1.c_str());
 	strcpy (sfile2, file2.c_str());
 	strcpy (sfile3, file3.c_str());
 	FILE *in1=fopen(sfile1,"rb");
 	FILE *in2=fopen(sfile2,"rb");
 	FILE *out=fopen(sfile3,"wb");
 	if(in1 == nullptr)
 	{
 		printf("打开源文件失败\n");
 		exit(0);
 	}
 	if(in2 == nullptr)
 	{
 		printf("打开源文件失败\n");
 		exit(0);
 	}
 	if(out == nullptr)
 	{
 		printf("打开源文件失败\n");
 		exit(0);
 	}
 	record *m_pData1 =(record*) new char[100];
 	record *m_pData2 =(record*) new char[100];
 	fgets((char*)(m_pData1), readsize, in1);
 	fgets((char*)(m_pData2), readsize, in2);
    while(!feof(in1) && !feof(in2))
	{
		
 	if(strnicmp((char*)m_pData1, (char*)m_pData2, RecordSize) <=0 ) 
	{
	 	fputs((char*)m_pData1,out);
	 
	 	fgets((char*)(m_pData1), readsize, in1);
	}
	else
	{
		fputs((char*)m_pData2,out);
		
		fgets((char*)(m_pData2), readsize, in2);
	} 
	}
	while(!feof(in1))
	{
		fputs((char*)m_pData1,out);
		
		fgets((char*)(m_pData1), readsize, in1);
	}
	while(!feof(in2))
	{
		fputs((char*)m_pData2,out);
		
		fgets((char*)(m_pData2), readsize, in2);
	}
 	fclose( in1 );
 	fclose( in2 );
 	fclose( out );
 }



int main(){
	
		printf("请输入要分割的文件完整路径:");
		char filePath[250];
		char midfile[250];
		char newFilePath[250];
		string p[30];
		string str ="D:\\X\\shiyan\\hui.txt";
	    strcpy (filePath, str.c_str());
	    split(filePath);
	    string name = str.substr(0,str.rfind("."));   
        name = name + "-";
        for(int i=0 ;i<30 ;i++)
		{
	      strcpy (midfile, name.c_str());
	      sprintf(newFilePath, "%s%d%s", midfile , i+1,".txt");
 	      p[i]=newFilePath;
         } 
        
       for(int i=0 ;i<10 ;i++){
	   FILE *fin=fopen(p[i].c_str(),"rb");
	   FILE *fout=fopen(p[i+10].c_str(),"wb");
	      
	      //获取文件长度
	   fseek( fin, 0, SEEK_END );
	   __int64 lFileLen = _ftelli64( fin );
	   rewind( fin );
	      
	    //申请数据空间
	    record *m_pData =(record*) new char[lFileLen+RecordSize];
	    __int64 recordCount=lFileLen/RecordSize;
	    fread((char*)(m_pData+1), RecordSize, recordCount, fin );
	    //关闭文件 
	    fclose( fin );
	      
	    QuickSort(m_pData,1, recordCount);
	    fwrite(m_pData+1, RecordSize, recordCount,fout);
	   	fclose(fout);
	   	delete[] m_pData;
	    }
	    
	    mergefile(p[10],p[11],p[20]);   
		for(int i=12;i <20; i++)
		{
		 	mergefile(p[i],p[i+8],p[i+9]);
		}	
          
}
