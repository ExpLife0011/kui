#ifndef __ksafecenter_h__
#define __ksafecenter_h__

#pragma once


#define OPT_SAFE_PCPROEABLE									_T("pcproeable")//�Ƿ����ÿͻ�������(0|1)
#define OPT_SAFE_LANPROEABLE								_T("lanproeable")//�Ƿ����þ���������(0|1)


#define OPT_M_PROCESSSTOPEABLE								_T("processstopeable")//�Ƿ����÷Ƿ���������(0|1)
#define OPT_M_PROCESSSPROEABLE								_T("processsproeable")//�Ƿ�������Ҫ���̱���(0|1)
#define OPT_M_ARPPROEABLE									_T("arpproeable")//�Ƿ�����ARP����(0|1)
#define OPT_M_AUTOBINDSVREABLE								_T("autobindsvreable")//�Ƿ������Զ����������ӷ�����(0|1)
#define OPT_M_DRIVERSTOPEABLE								_T("driverstopeable")//�Ƿ����÷Ƿ���������(0|1)
#define OPT_M_UNDLGEABLE									_T("undlgeable")//�Ƿ����÷Ƿ���������(0|1)
#define OPT_M_IPSTOPEABLE									_T("ipstopeable")
#define OPT_M_NETPROEABLE									_T("netproeable")
#define OPT_M_NETPORTEABLE									_T("netporteable")


#define PROCESS_CLOSE_RESTART								0//�رպ���������
#define PROCESS_CLOSE_REBOOT								1//�رպ������ͻ���

#define PROCESS_FROM_USER									0//���������û����	
#define PROCESS_FROM_IDC									1//����������Դ����	
#define PROCESS_FROM_AGENT									2//����������Դ������

#define UNPROCESS_WHITE										0//�Ƿ����̰�����	
#define UNPROCESS_BLACK										1//�Ƿ����̺�����	

#define UNPROCESS_TYPE_TRUST								0//�Ƿ���������
#define UNPROCESS_TYPE_STOP									1//�Ƿ���������	

#define ARP_ATTACK_PASSIVITY								0//ARP��������	
#define ARP_ATTACK_INITIATIVE								1//ARP��������	



#define CMD_SAFE_DB_HEART										0x0301		//����������У��ޣ����У���.
#define CMD_SAFE_DB_SQL											0x0302		//ִ��SQL���. ���У�sql���,���У�row, colomn, ��¼��
#define CMD_SAFE_DB_TSQL										0x0303		//������ʽִ��SQL�����,�����᷵�ؼ�¼����

#define LOG_TYPE_ARPPRO											0x01		//arp��־
#define LOG_TYPE_PROFILTER										0x02		//���̹�����־
#define LOG_TYPE_PROPROTECT										0x03		//���̱�����־
#define LOG_TYPE_DRIVER											0x04        //����������־
#define LOG_TYPE_UNDLG											0x05		//�Ƿ���������
#define LOG_TYPE_IPSTOP											0x06		//IP��ַ����
#define LOG_TYPE_NETSTOP										0x07		//�������
#define LOG_TYPE_NETPORT										0x08		//����˿�




//��ȫ����ͨѶ����
#define CMD_SC_NOTIFYIPMACBIND			0x0702		//֪ͨIP��MAC��ַ����Ϣ
#define CMD_SC_NOTIFYPROTECTINFO		0x0704		//֪ͨ���̱�����Ϣ
#define CMD_SC_NOTIFYPEFILTERINFO		0x0707		//֪ͨ���̹�����Ϣ

#define CMD_SC_QUERYIPMACBIND			0x0901		//��ȡIP��MAC��ַ����Ϣ
#define CMD_SC_QUERYPROTECTINFO			0x0903		//��ȡ���̱�����Ϣ
#define CMD_SC_QUERYPROTECTINFOEX		0x0904		//��ȡ���̱�����Ϣ��չ
#define CMD_SC_QUERYPEFILTERBLACKINFO	0x0905		//��ȡ���̹��˺�������Ϣ
#define CMD_SC_QUERYPEFILTERWHITEINFO	0x0906		//��ȡ���̹��˰�������Ϣ
#define CMD_SC_REPORTINFO				0x0908		//�ϱ���ȫ���Ĺ�����Ϣ



#define CMD_SC_QUERYDRIVERBLACK			0x090A		//��ȡ����������
#define CMD_SC_QUERYDRIVERWHITE			0x090B		//��ȡ����������
#define CMD_SC_QUERYUNDLG				0x090C		//��ȡ�Ƿ�����
#define CMD_SC_QUERYNETPRO				0x090D		//��ȡ�������
#define CMD_SC_QUERYNETPORT				0x090E		//��ȡ����˿�
#define CMD_SC_QUERYIPSTOP				0x090F		//��ȡIP����
#define CMD_SC_QUERYIPWHITE				0x0910		//��ȡ�������������


#define CMD_SC_QUERYPEFILTERBLACKINFOEX	0x0912		//��ȡ���̹��˺�������Ϣ��չ
#define CMD_SC_QUERYPEFILTERWHITEINFOEX	0x0913		//��ȡ���̹��˰�������Ϣ��չ
#define CMD_SC_QUERYDRIVERBLACKEX		0x0914		//��ȡ������������Ϣ��չ
#define CMD_SC_QUERYDRIVERWHITEEX		0x0915		//��ȡ������������Ϣ��չ







#endif