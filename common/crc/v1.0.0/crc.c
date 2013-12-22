#include "crc.h"

//����CRC32
#define UPDC32(octet, crc) (CRC32S_Tab[((crc)^ (octet)) & 0xff] ^ ((crc) >> 8))		//����CRC32���㹫ʽ
static unsigned int CRCSVAL = 0;		//����CRC32ֵ
static const unsigned int CRC32S_Tab[] = 	//����CRC32������
{ 
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/****************************************************************************
* ��	�ƣ�void CRC32S_Clear(void)
* ��	�ܣ���λ����CRC32ֵ	   
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void CRC32S_Clear(void)
{
	CRCSVAL = 0xFFFFFFFF;
}

/****************************************************************************
* ��	�ƣ�unsigned int CRC32S_Chack8(unsigned char flagC,unsigned char* pBuf, unsigned int nSize)		  //ȡCRC32Ч��ֵ
* ��	�ܣ�����CRC32Ч��
* ��ڲ�����unsigned char flagC	�Ƿ����CRC		0����λ	1��λ
			unsigned char* pBuf 	����8λ������
			unsigned int nSize	���ݸ���
* ���ڲ�����32λ��	CRC32Ч����
* ˵	����CRC polynomial 0xedb88320
****************************************************************************/
unsigned int CRC32S_Chack8(unsigned char flagC,unsigned char* pBuf, unsigned int nSize)
{
	unsigned int i;

	if(flagC == 1)
		CRC32S_Clear();		//��λCRC

	for(i = 0;i < nSize;i++) 
		CRCSVAL = UPDC32(pBuf[i], CRCSVAL);

	return CRCSVAL; 
}

static unsigned char nCRCHi = 0;		//CRC16������ֵ
static unsigned char nCRCLo = 0;		//CRC16������ֵ

unsigned char const auchCRC16Hi[256] =
{
	0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 		   
	0x81, 0x91, 0xa1, 0xb1, 0xc1, 0xd1, 0xe1, 0xf1, 
	0x12, 0x02, 0x32, 0x22, 0x52, 0x42, 0x72, 0x62, 
	0x93, 0x83, 0xb3, 0xa3, 0xd3, 0xc3, 0xf3, 0xe3, 
	0x24, 0x34, 0x04, 0x14, 0x64, 0x74, 0x44, 0x54, 
	0xa5, 0xb5, 0x85, 0x95, 0xe5, 0xf5, 0xc5, 0xd5, 
	0x36, 0x26, 0x16, 0x06, 0x76, 0x66, 0x56, 0x46, 
	0xb7, 0xa7, 0x97, 0x87, 0xf7, 0xe7, 0xd7, 0xc7, 
	0x48, 0x58, 0x68, 0x78, 0x08, 0x18, 0x28, 0x38, 
	0xc9, 0xd9, 0xe9, 0xf9, 0x89, 0x99, 0xa9, 0xb9, 
	0x5a, 0x4a, 0x7a, 0x6a, 0x1a, 0x0a, 0x3a, 0x2a, 
	0xdb, 0xcb, 0xfb, 0xeb, 0x9b, 0x8b, 0xbb, 0xab, 
	0x6c, 0x7c, 0x4c, 0x5c, 0x2c, 0x3c, 0x0c, 0x1c, 
	0xed, 0xfd, 0xcd, 0xdd, 0xad, 0xbd, 0x8d, 0x9d, 
	0x7e, 0x6e, 0x5e, 0x4e, 0x3e, 0x2e, 0x1e, 0x0e, 
	0xff, 0xef, 0xdf, 0xcf, 0xbf, 0xaf, 0x9f, 0x8f, 
	0x91, 0x81, 0xb1, 0xa1, 0xd1, 0xc1, 0xf1, 0xe1, 
	0x10, 0x00, 0x30, 0x20, 0x50, 0x40, 0x70, 0x60, 
	0x83, 0x93, 0xa3, 0xb3, 0xc3, 0xd3, 0xe3, 0xf3, 
	0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72, 
	0xb5, 0xa5, 0x95, 0x85, 0xf5, 0xe5, 0xd5, 0xc5, 
	0x34, 0x24, 0x14, 0x04, 0x74, 0x64, 0x54, 0x44, 
	0xa7, 0xb7, 0x87, 0x97, 0xe7, 0xf7, 0xc7, 0xd7, 
	0x26, 0x36, 0x06, 0x16, 0x66, 0x76, 0x46, 0x56, 
	0xd9, 0xc9, 0xf9, 0xe9, 0x99, 0x89, 0xb9, 0xa9, 
	0x58, 0x48, 0x78, 0x68, 0x18, 0x08, 0x38, 0x28, 
	0xcb, 0xdb, 0xeb, 0xfb, 0x8b, 0x9b, 0xab, 0xbb, 
	0x4a, 0x5a, 0x6a, 0x7a, 0x0a, 0x1a, 0x2a, 0x3a, 
	0xfd, 0xed, 0xdd, 0xcd, 0xbd, 0xad, 0x9d, 0x8d, 
	0x7c, 0x6c, 0x5c, 0x4c, 0x3c, 0x2c, 0x1c, 0x0c, 
	0xef, 0xff, 0xcf, 0xdf, 0xaf, 0xbf, 0x8f, 0x9f, 
	0x6e, 0x7e, 0x4e, 0x5e, 0x2e, 0x3e, 0x0e, 0x1e
};	//CRC16�߶�Keyֵ

unsigned char const auchCRC16Lo[256] =
{
	0x00, 0x21, 0x42, 0x63, 0x84, 0xa5, 0xc6, 0xe7, 
	0x08, 0x29, 0x4a, 0x6b, 0x8c, 0xad, 0xce, 0xef, 
	0x31, 0x10, 0x73, 0x52, 0xb5, 0x94, 0xf7, 0xd6, 
	0x39, 0x18, 0x7b, 0x5a, 0xbd, 0x9c, 0xff, 0xde, 
	0x62, 0x43, 0x20, 0x01, 0xe6, 0xc7, 0xa4, 0x85, 
	0x6a, 0x4b, 0x28, 0x09, 0xee, 0xcf, 0xac, 0x8d, 
	0x53, 0x72, 0x11, 0x30, 0xd7, 0xf6, 0x95, 0xb4, 
	0x5b, 0x7a, 0x19, 0x38, 0xdf, 0xfe, 0x9d, 0xbc, 
	0xc4, 0xe5, 0x86, 0xa7, 0x40, 0x61, 0x02, 0x23, 
	0xcc, 0xed, 0x8e, 0xaf, 0x48, 0x69, 0x0a, 0x2b, 
	0xf5, 0xd4, 0xb7, 0x96, 0x71, 0x50, 0x33, 0x12, 
	0xfd, 0xdc, 0xbf, 0x9e, 0x79, 0x58, 0x3b, 0x1a, 
	0xa6, 0x87, 0xe4, 0xc5, 0x22, 0x03, 0x60, 0x41, 
	0xae, 0x8f, 0xec, 0xcd, 0x2a, 0x0b, 0x68, 0x49, 
	0x97, 0xb6, 0xd5, 0xf4, 0x13, 0x32, 0x51, 0x70, 
	0x9f, 0xbe, 0xdd, 0xfc, 0x1b, 0x3a, 0x59, 0x78, 
	0x88, 0xa9, 0xca, 0xeb, 0x0c, 0x2d, 0x4e, 0x6f, 
	0x80, 0xa1, 0xc2, 0xe3, 0x04, 0x25, 0x46, 0x67, 
	0xb9, 0x98, 0xfb, 0xda, 0x3d, 0x1c, 0x7f, 0x5e, 
	0xb1, 0x90, 0xf3, 0xd2, 0x35, 0x14, 0x77, 0x56, 
	0xea, 0xcb, 0xa8, 0x89, 0x6e, 0x4f, 0x2c, 0x0d, 
	0xe2, 0xc3, 0xa0, 0x81, 0x66, 0x47, 0x24, 0x05, 
	0xdb, 0xfa, 0x99, 0xb8, 0x5f, 0x7e, 0x1d, 0x3c, 
	0xd3, 0xf2, 0x91, 0xb0, 0x57, 0x76, 0x15, 0x34, 
	0x4c, 0x6d, 0x0e, 0x2f, 0xc8, 0xe9, 0x8a, 0xab, 
	0x44, 0x65, 0x06, 0x27, 0xc0, 0xe1, 0x82, 0xa3, 
	0x7d, 0x5c, 0x3f, 0x1e, 0xf9, 0xd8, 0xbb, 0x9a, 
	0x75, 0x54, 0x37, 0x16, 0xf1, 0xd0, 0xb3, 0x92, 
	0x2e, 0x0f, 0x6c, 0x4d, 0xaa, 0x8b, 0xe8, 0xc9, 
	0x26, 0x07, 0x64, 0x45, 0xa2, 0x83, 0xe0, 0xc1, 
	0x1f, 0x3e, 0x5d, 0x7c, 0x9b, 0xba, 0xd9, 0xf8, 
	0x17, 0x36, 0x55, 0x74, 0x93, 0xb2, 0xd1, 0xf0
};	//CRC16�Ͷ�Keyֵ

/****************************************************************************
* ��	�ƣ�void CRC16_ResetDR(void)
* ��	�ܣ�CRC16Ч��ֵ��λ
* ��ڲ�������
* ���ڲ�������
* ˵	�������CRC16ֵ	
****************************************************************************/
void CRC16_ResetDR(void)
{
	nCRCHi = 0xFF;
	nCRCLo = 0xFF;
}

/****************************************************************************
* ��	�ƣ�unsigned short CRC16(unsigned char flag,unsigned char *pData, unsigned int nData)
* ��	�ܣ�CRC16Ч��
* ��ڲ�����unsigned char flag		�Ƿ�λCRC16ֵ		0����λ	1��λ
			unsigned char *pData	�����ݼ���У��ֵ
			unsigned int nData	���ݸ���
* ���ڲ�����unsigned short	CRC16У��ֵ
* ˵	����ÿ���Զ���λУ��ֵ	
****************************************************************************/
unsigned short CRC16(unsigned char flag,unsigned char *pData, unsigned int nData)
{
	unsigned char nIndex;

	if(flag == 1)
		CRC16_ResetDR();

	while(nData--)
	{
		nIndex = nCRCHi ^ *pData++;
		nCRCHi = nCRCLo ^ auchCRC16Hi[nIndex];
		nCRCLo = auchCRC16Lo[nIndex];
	}
	return (nCRCHi << 8 | nCRCLo);
}

/****************************************************************************
* ��	�ƣ�void PushCrc16Byte(unsigned char nData)
* ��	�ܣ�CRC16Ч��
* ��ڲ�����unsigned char nData	�����ݼ���У��ֵ
* ���ڲ�������
* ˵	����һ�����ݼ���У��ֵ������λУ��ֵ
			һ�����ݼ�����ɺ�����һ��У��ֵ���������У��ֵ�ڴ���˺����У����������Ϊ0
****************************************************************************/
void PushCrc16Byte(unsigned char nData)
{
	unsigned char nIndex;

	nIndex = nCRCHi ^ nData;
	nCRCHi = nCRCLo ^ auchCRC16Hi[nIndex];
	nCRCLo = auchCRC16Lo[nIndex];  
}

/****************************************************************************
* ��	�ƣ�unsigned short GetCrcCode(void)
* ��	�ܣ���ȡCRC16У��ֵ����֤����֤ͨ������0����֤ʧ�ܷ��ط�0
* ��ڲ�������
* ���ڲ�����unsigned short ��֤ͨ������0����֤ʧ�ܷ��ط�0
* ˵	������	
****************************************************************************/
unsigned short GetCrc16Code(void)
{
	return (nCRCHi << 8 | nCRCLo);		 //��ȡУ��ֵ
}







/*============================================================================*/
//CRC Tables
const unsigned char auchCRCHi_exp[] = {
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0,
   0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
   0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
   0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
   0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
   0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
   0x40
} ;

const unsigned char auchCRCLo_exp[] = {
   0x00, 0xc0, 0xc1, 0x01, 0xc3, 0x03, 0x02, 0xc2, 0xc6, 0x06, 0x07, 0xc7, 0x05, 0xc5, 0xc4,
   0x04, 0xcc, 0x0c, 0x0d, 0xcd, 0x0f, 0xcf, 0xce, 0x0e, 0x0a, 0xca, 0xcb, 0x0b, 0xc9, 0x09,
   0x08, 0xc8, 0xd8, 0x18, 0x19, 0xd9, 0x1b, 0xdb, 0xda, 0x1a, 0x1e, 0xde, 0xdf, 0x1f, 0xdd,
   0x1d, 0x1c, 0xdc, 0x14, 0xd4, 0xd5, 0x15, 0xd7, 0x17, 0x16, 0xd6, 0xd2, 0x12, 0x13, 0xd3,
   0x11, 0xd1, 0xd0, 0x10, 0xf0, 0x30, 0x31, 0xf1, 0x33, 0xf3, 0xf2, 0x32, 0x36, 0xf6, 0xf7,
   0x37, 0xf5, 0x35, 0x34, 0xf4, 0x3c, 0xfc, 0xfd, 0x3d, 0xff, 0x3f, 0x3e, 0xfe, 0xfa, 0x3a,
   0x3b, 0xfb, 0x39, 0xf9, 0xf8, 0x38, 0x28, 0xe8, 0xe9, 0x29, 0xeb, 0x2b, 0x2a, 0xea, 0xee,
   0x2e, 0x2f, 0xef, 0x2d, 0xed, 0xec, 0x2c, 0xe4, 0x24, 0x25, 0xe5, 0x27, 0xe7, 0xe6, 0x26,
   0x22, 0xe2, 0xe3, 0x23, 0xe1, 0x21, 0x20, 0xe0, 0xa0, 0x60, 0x61, 0xa1, 0x63, 0xa3, 0xa2,
   0x62, 0x66, 0xa6, 0xa7, 0x67, 0xa5, 0x65, 0x64, 0xa4, 0x6c, 0xac, 0xad, 0x6d, 0xaf, 0x6f,
   0x6e, 0xae, 0xaa, 0x6a, 0x6b, 0xab, 0x69, 0xa9, 0xa8, 0x68, 0x78, 0xb8, 0xb9, 0x79, 0xbb,
   0x7b, 0x7a, 0xba, 0xbe, 0x7e, 0x7f, 0xbf, 0x7d, 0xbd, 0xbc, 0x7c, 0xb4, 0x74, 0x75, 0xb5,
   0x77, 0xb7, 0xb6, 0x76, 0x72, 0xb2, 0xb3, 0x73, 0xb1, 0x71, 0x70, 0xb0, 0x50, 0x90, 0x91,
   0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9c, 0x5c,
   0x5d, 0x9d, 0x5f, 0x9f, 0x9e, 0x5e, 0x5a, 0x9a, 0x9b, 0x5b, 0x99, 0x59, 0x58, 0x98, 0x88,
   0x48, 0x49, 0x89, 0x4b, 0x8b, 0x8a, 0x4a, 0x4e, 0x8e, 0x8f, 0x4f, 0x8d, 0x4d, 0x4c, 0x8c,
   0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
   0x40
} ;

/*============================================================================*/
// Procedure to check the checksum of the message
unsigned int modrtuChecksum ( unsigned char *chkbuf, unsigned char len )
{

   unsigned char    uchCRCHi = 0xff ;
   unsigned char    uchCRCLo = 0xff ;
   unsigned int  uIndex ;
   unsigned int  temp_code;

   while ( len )
   {
      uIndex = (unsigned int) ( uchCRCHi ^ *chkbuf++ ) ;

      uchCRCHi = (unsigned char) ( uchCRCLo ^ auchCRCHi_exp[uIndex] ) ;
      uchCRCLo = auchCRCLo_exp[uIndex] ;
      len-- ;
   }
   temp_code = (unsigned int) uchCRCHi;
   temp_code = (unsigned int) (temp_code << 8);
   return(unsigned int) (  temp_code | uchCRCLo ) ;
}