#ifndef __kcore_h__
#define __kcore_h__

#pragma once

#include <tchar.h>
#include <winsock2.h>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "sqlite3.h"

#pragma comment(lib, "ws2_32.lib")

#if _MSC_VER > 1500

#include <memory>

namespace std { namespace tr1 {
	using std::shared_ptr;
}
}
#endif


#define START_NAMESPACE_KCORE		namespace kcore {
#define END_NAMESPACE_KCORE			}
#define USE_NAMESPACE_KCORE			using namespace kcore;

START_NAMESPACE_KCORE

#ifdef _UNICODE
#define tstring std::wstring
#define tstringstream  std::wstringstream
#else
#define tstring std::string
#define tstringstream  std::stringstream
#endif

#define ROUND_SIZE(size, round)						(((size) + (round) - 1) / (round) * (round))
#define ROUND_SIZE_4K(size)							(ROUND_SIZE((size), 0x1000))
#define ROUND_SIZE_64K(size)						(ROUND_SIZE((size), 0x10000))

template <typename T> void Delete_Interface(T& t)	{ if ((t)) { (t)->Release(); (t) = NULL; } }
template <typename T> void Delete_Pointer(T& t)		{ if ((t)) { delete (t);     (t) = NULL; } }
template <typename T> void Delete_Array(T& t)		{ if ((t)) { delete [](t);   (t) = NULL; } }

//����EXE�ĵ�ʵ����������
#define KNBSERVICE_SINGLE_NAME				TEXT("Global\\YGX{87F4495C-8A1F-4f83-83CD-95B304F0170C}")
#define KNBUPDATE_SINGLE_NAME				TEXT("Global\\YGX{94CBEC72-CC62-4dc4-8035-388FCF5C7CD1}")
#define KNBVDISK_SINGLE_NAME				TEXT("Global\\YGX{D7362CE4-3FA4-4eb0-81A2-FCB4AD333A67}")
#define CONSOLE_SINGLE_NAME					TEXT("Global\\YGX{DBA3A10A-DCC8-4a66-A5B2-0A78BF12E5EE}")
#define KNBCLIENT_SINGLE_NAME				TEXT("Global\\YGX{E01770FE-6BE2-4024-9EA4-3462D5193D50}")
#define KNBMENU_SINGLE_NAME					TEXT("Global\\YGX{E3CDD1BA-5868-41e7-9A0D-02A5FD20E71F}")
#define KASSIST_SINGLE_NAME                 TEXT("Global\\YGX{E3FDG1BA-5868-4167-9AA4-02A5FB20EB1F}")
#define KASSISTHUB_SINGLE_NAME              TEXT("Global\\YGX{E3FDG1BA-78E8-4167-9AA4-02A5FB20EB1F}")


//����������ͻ������͵Ļ����¼���.
#define UPDATE_EVENT_NAME					TEXT("Global\\{8FC27450-DEF8-490a-9405-9A205853E8D8}")

//����ͬ������Ϸͬ���Ļ����¼���.
#define MIRROR_EVENT_NAME					TEXT("Global\\{77DB79A5-7295-4943-8691-989BF87157FC}")

//�ڵ������ʱ�ӹ��¼���
#define TAKEOVER_EVENT_NAME					TEXT("Global\\{D69F151A-DAC6-4795-9611-44DCF48395F5}")

//����ڲ��Զ����������������в���
#define AUTOUPDATE_PARAMETER				TEXT("-autoupdate")

//����Զ������ų�kvdisk
#define AUTOUPDATE_EXCLUDEVDISK				TEXT("-excludevdisk")

#define APP_TCP_PORT						5761
#define DB_TCP_PORT							5762
#define UPTSVR_TCP_PORT						5763
#define INUPT_TCP_PORT						5764
#define VDK_TCP_PORT						5765
#define UDK_TCP_PORT						5766
#define CLI_UDP_PORT						5767
#define CON_UDP_PORT						5768
#define SAFEDB_TCP_PORT						5769
#define VDK_TCP_BASEPORT					5770
#define IMG_TCP_BASEPORT					5870
#define CLI_TCP_PORT						5920
#define CHANNEL_TCP_PORT					5921
#define LOG_TCP_PORT						5922
#define DUMP_TCP_PORT						5923
#define DUMP_UDP_BASEPORT					5923
#define LOG_TCP_PORT_EX						5924
#define USERDISK_TCP_PORT					5925
#define CLEAER_TCP_PORT						5926

#define APP_BCAST_PORT						APP_TCP_PORT

inline WORD AfxGetVDiskPort(TCHAR szDriver) { return VDK_TCP_BASEPORT + _totupper(szDriver) - TEXT('C');}

#define DEF_AREA_GUID						TEXT("{0191103D-19D8-4F13-A647-BCD04DF9DE35}")
#define ALL_AREA_GUID						TEXT("{2579245B-7E08-46e2-9A66-24D3FBCC2829}")


inline bool AfxIsIdcAreaGuid(LPCTSTR guid);
//inline bool AfxIsIdcAreaName(LPCTSTR name);

#define CLASS_TOTAL_COUNT			17


#define CLASS_WL_GUID				TEXT("{1AF9A1A1-FF46-41B7-BC7A-D1FAE3E25B01}")	//������Ϸa
#define CLASS_DJ_GUID				TEXT("{2A687865-B630-4FA2-A5AC-EA9C9C4AABB2}")	//��Ʒ����b
#define CLASS_QP_GUID				TEXT("{3A761798-CD7D-4761-81CB-8513B17F69E3}")	//������Ϸc
#define CLASS_DZ_GUID				TEXT("{4E33B955-25C7-40e9-B391-EE4CE049A592}")	//��սƽ̨d
#define CLASS_LT_GUID				TEXT("{5AAAF78F-3FF2-4834-99AF-744233CEC6D4}")  //���콻��e
#define CLASS_WY_GUID				TEXT("{6A9363C6-EC57-4A65-9D71-043B80A38F05}")	//��ҳ��Ϸf
#define CLASS_XX_GUID				TEXT("{7AAD06BD-819C-48D1-9CB0-47DF498CF256}")	//��������g
#define CLASS_PL_GUID				TEXT("{8A999DC2-2676-4FF2-8D62-7AB625F02857}")	//��Ϸ����h
#define CLASS_CY_GUID				TEXT("{9A76073C-DDB1-4939-B85C-521F283B0198}")	//�������i
#define CLASS_YY_GUID				TEXT("{A258A554-6D7E-4369-8E67-4339CD7A0F59}")	//Ӱ������j
#define CLASS_GP_GUID				TEXT("{B3BAFF9D-5015-422A-A0CB-4CBC3DFAC49A}")	//��Ʊ֤ȯk
#define CLASS_GQ_GUID				TEXT("{C945C2D1-E039-4c14-9D40-8789059493FB}")	//����Ӱ��l
#define CLASS_ZX_GUID				TEXT("{DA2F5C0F-AC11-4720-A6CD-2C72EE891E6B}")	//��������m
#define CLASS_XC_GUID				TEXT("{E0B0A5D9-E267-4cdf-8E84-0E8CA13C16F5}")	//�㳡ֱ��n
#define CLASS_SJ_GUID				TEXT("{F566239D-B794-4751-8BE5-A09A994C15D1}")	//�ֻ���Ϸo
#define CLASS_BG_GUID				TEXT("{G6D14FF3-2EBC-4750-91C7-77C0284B090B}")	//�칫���p
#define CLASS_DPNP_GUID				TEXT("{4ADDE7DA-1AED-43BC-8803-93763DFF00EC}")	//�Կ�pnp q

//������ӵ���Ϸ���
#define CLASS_NB_GUID				TEXT("{39F925AE-5972-454C-86DD-5A554F2C73A2}")  //�����Զ�����Ϸ����

inline LPCTSTR AfxGetGUIDByAlpha(TCHAR alpha);

//�������������Ŀͻ��˶�������
#define OBJECT_UNKOWN					0			//δ֪
#define OBJECT_CONSOLE					1			//����̨
#define OBJECT_CLIENT					2			//�ͻ��˷���
#define OBJECT_MENU						3			//�ͻ�����Ϸ�˵�
#define OBJECT_UPDATE					4			//���·�����
#define OBJECT_VIDSK					5			//�����̷�����
#define OBJECT_DOWNLOAD					6			//����������������̨��

//��Ϸ���з�ʽ
#define GAME_RUNTYPE_UNKNOW				0			//δ����.������Ϸ���ڸ÷�����ʾ
#define GAME_RUNTYPE_VDISK				1			//�����̷�ʽ����
#define GAME_RUNTYPE_UPDATE				2			//���ظ��£�ͨ���������µ��ͻ�����������
#define GAME_RUNTYPE_DIRECT				3			//ֱ�����У�֧�ֵ����������̣�ֱ�����пͻ�������Ϸ

//��ݷ�ʽ����
#define SHORTCUT_TYPE_UNKNOWN			0			//δ֪
#define SHORTCUT_TYPE_GAME				1			//��Ϸ��ݷ�ʽ
#define SHORTCUT_TYPE_CLASS				2			//����ݷ�ʽ
#define SHORTCUT_TYPE_TOOL				3			//���߿�ݷ�ʽ
#define SHORTCUT_TYPE_EXE				4			//EXE��ݷ�ʽ
#define SHORTCUT_TYPE_URL				5			//��ҳ��ݷ�ʽ

//�������������
#define BOOT_TASK_UNKNOWN				0			//δ֪
#define BOOT_TASK_DOWNRUN				1			//���ز���ִ��
#define BOOT_TASK_RUNCLI				2			//ִ�пͻ������ļ�

//���̷�������
#define DISK_TYPE_UNKNOWN				0			//δ����
#define DISK_TYPE_GAME					1			//��Ϸ��
#define DISK_TYPE_WRITE					2			//��д��
#define DISK_TYPE_IMAGE					3			//������

//�ͻ���״̬�����ߡ�����
#define CLIENT_STATUS_ONLINE			1ul			//��ʾ�ͻ�������
#define CLIENT_STATUS_OFFLINE			0ul			//��ʾ�ͻ�������

//�ͻ���֪ͨӲ��״̬
#define CLIENT_HD_NORMAL				0ul			//��ʾ�ͻ��������ϱ���û�б��)
#define CLIENT_HD_NEW					1ul			//��ʾ�µĿͻ����ϱ�
#define CLIENT_HD_CHANGE				2ul			//��ʾ�ͻ���Ӳ�����

//�ͻ�����������
#define BOOT_TYPE_NODISK				0ul			//��ʾ�ͻ���������.
#define BOOT_TYPE_HARDDISK				1ul			//��ʾ�ͻ���������
#define BOOT_TYPE_SSD					2ul			//��ʾ�ͻ�����SSD

//֪ͨ����̨��־����
#define LOG_TYPE_APP					1			//����������־
#define LOG_TYPE_P2P					2			//����������־
#define LOG_TYPE_SYNC					3			//ͬ����־
#define LOG_TYPE_VDISK					4			//��������־
#define LOG_TYPE_CACHE					5			//������־
#define LOG_TYPE_SSD					6			//ssd��־


//��Ϸͬ����ʽ
#define GAME_SYNC_AUTO					0			//�Զ�ͬ�����Ƽ���
#define GAME_SYNC_DRIVER				1			//�̷�ͬ��
#define GAME_SYNC_SINGLE			    2			//����ͬ��

//����¼�ID
#define MEMORY_LACK						1			//�ڴ治��
#define DRIVER_LOST						2			//�̷���ʧ
#define DRIVER_LACK						3			//���̿ռ䲻��
#define ADAPTER_MODIFY					4			//�������ʷ����仯
#define PORT_BEUSED						5			//�˿ڱ�ռ��

//�ڵ������״̬
#define NODE_NORMAL						0			//����״̬(�ڵ������)
#define NODE_TAKEOVER					1			//�ӹ�״̬
#define NODE_ISMAIN						2			//�ڵ����������������
#define NODE_SVRIPNOTEXIST				3			//�ڵ����õ���������IP�뵱ǰ�����������
//////////////////////////////////////////////////////////////////////////
//�û�ѡ��
#define OPT_U_USERID					TEXT("uuserid")				//�û�id.
#define OPT_U_AGENTID					TEXT("uagentid")			//������id.
#define OPT_U_USERNAME					TEXT("uusername")			//�û���
#define OPT_U_PASSWORD					TEXT("uupassword")			//����
#define OPT_U_REGDATE					TEXT("uregdate")			//�û�ע������
#define OPT_U_DATEEND					TEXT("udateend")			//��������
#define OPT_U_PROVINCE					TEXT("uuserprovince")		//�û�����ʡ
#define OPT_U_CITY						TEXT("uusercity")			//�û����ڳ���
#define OPT_U_ERRINFO					TEXT("uErrInfo")			//���ڿ���̨��ʾ��½�Ĵ�����Ϣ
#define OPT_U_ERRORID					TEXT("uErrId")				//����֤�Ĵ���id
#define OPT_U_RAMDOMNUM					TEXT("uramdomnum")			//�û�û��¼һ�ε������
#define OPT_U_NETBARNAME				TEXT("unetbarname")			//��������
#define OPT_U_NETBARCONTACT				TEXT("unetbarcontact")		//������ϵ��ʽ
#define OPT_U_NETBARMOBILE				TEXT("unetbarmobile")		//�����ֻ�
#define OPT_U_NETBARADDRESS				TEXT("unetbaraddress")		//���ɵ�ַ
#define OPT_U_AGENTNAME					TEXT("uagentname")			//����������
#define OPT_U_AGENTCONTACT				TEXT("uagentcontact")		//��������ϵ��ʽ
#define OPT_U_AGENTMOBILE				TEXT("uagentmobile")		//�������ֻ�
#define OPT_U_INTERNETIP				TEXT("uinternetip")			//����IP
#define OPT_U_ISSSD						TEXT("isssd")				//��ssd�ͺ�
#define OPT_U_SHFLAG1					TEXT("shflag1")				//���㱾�ز�������
#define OPT_U_SHFLAG2					TEXT("shflag2")				//�����ƽ��������
#define OPT_U_LASTLOGINTIME				TEXT("lastlogintime")		//����¼ʱ��

#define OPT_U_BREAKPOINTPRO				TEXT("breakpointproenable")	//�Ƿ����öϵ籣��(1��,0��)


#define OPT_U_NOREMOTECONSOLE			TEXT("unoremoteconsole")	//��ֹ����̨Զ�̵�¼(1��ֹ,0����)
#define OPT_U_CTLPWD					TEXT("uctrlpassword")		//����̨����.�����crcֵ.

#define OPT_U_REMOTEPWD					TEXT("uctrlpassword")		//Զ������.�����crcֵ��Զ�̽ڵ㣬�ͻ�����.
#define OPT_U_DOWNVIEWPWD				TEXT("downviewpassword")	//���ز鿴����¼����.
#define OPT_U_KCONSOLELOGINPWD			TEXT("kconsoleloginpassword")	//����̨��¼����.


//����ѡ��
#define OPT_D_TEMPDIR					TEXT("dtempdir")			//��������:��Ϸ������ʱĿ¼
#define OPT_D_TASKNUM					TEXT("dtasknum")			//��������:ͬʱ���ص���������� (max:5,default:3)
#define OPT_D_FIBERMODE					TEXT("dfibermode")			//��������:����ģʽ,1��ʾ����ģʽ��0��ʾADSLģʽ.
#define OPT_D_SPEED						TEXT("dspeed")				//��������:�ٶ�����(n)(bytes/s)
#define OPT_D_TIMESPEED					TEXT("dtimespeed")			//��������:�Ƿ�������ʱ������.1��ʾ���á�
#define OPT_D_SYNCSPEED					TEXT("dsyncspeed")			//ͬ������(bytes/s).
#define OPT_D_PUSHSPEED					TEXT("dpushspeed")			//��������(bytes/s).
#define OPT_D_SYNCMODE					TEXT("dsyncmode")			//��Ϸͬ����ʽ(0.���ݽڵ������С�Զ�ͬ��;1.����ͬ������ͬ�̷�(Ĭ��))
#define OPT_D_P2PACCELERATE				TEXT("dp2paccelerate")		//��������:�Ƿ�����P2P����.1��ʾ���á�
#define OPT_D_MADSLOPTIMIZE				TEXT("dmadsloptimize")		//��������:�Ƿ���������adsl�Ż�.1��ʾ���á�

#define OPT_D_AUTOGAMECLEAR				TEXT("autogameclear")		//�Ƿ��Զ�������Ϸ(1.��;0��)
#define OPT_D_RATESPACE					TEXT("ratespace")			//ʣ��ٷ�֮���ٿռ�������Ϸ(0��ʾ������)

//�ͻ���ѡ����
#define OPT_M_POWEROFFEABLE				TEXT("meablepoweroffe")		//����̨:�ϵ籣��
#define OPT_M_SVRREMOTEEABLE			TEXT("meablesvrremote")		//����̨:���������Զ�̲���.1��ʾ����
#define OPT_M_LOGINEABLE				TEXT("meablelogin")			//����̨:�����¼.1��ʾ����
#define OPT_M_CONSOLEPWD				TEXT("mconpwd")				//����̨:�ͷ�������������.(�����CRC32�ַ���)
#define OPT_M_CLIPWD					TEXT("mclipwd")				//�ͻ���:�߼���������(�����CRC32�ַ���)
#define OPT_M_GAMEDISK					TEXT("mgamedisk")			//�ͻ���:�����Ϸ�Ĵ���.
#define OPT_M_RUNMENU					TEXT("mrunmenu")			//�ͻ���:���������˵�.
#define OPT_M_WINDOWMODE				TEXT("mwinmode")			//�ͻ���:���������˵���ģʽ:0ȫ����1����.
#define OPT_M_HIDEMENU					TEXT("mhidemenu")			//�ͻ���:������Ϸ���Ƿ����ز˵�.1��ʾ����.
#define OPT_M_SYNCTIME					TEXT("msyntime")			//�ͻ���:����ʱͬ��������ʱ��(0|1)
#define OPT_M_DELETEINDEXFILE			TEXT("mdeleteindexfile")	//�ͻ�������ǰ�Ƿ�ɾ�������ļ�
#define OPT_M_SAFECENTER				TEXT("msafecenter")			//�ͻ���:�Ƿ����ð�ȫ����(0|1)

#define OPT_M_DISPLAYPNP				TEXT("mdisplaypnp")			//�ͻ���:�Ƿ������Կ�PNP(0|1)

#define OPT_M_SHOWEXCEPTIONTEMPERATURE	TEXT("mshowexceptiontemperature")	//�ͻ���:����ʾ�쳣�¶ȵĿͻ���.1��ʾ����
#define OPT_M_TEMPERATUREENABLE			TEXT("mtemperatureeable")	//�ͻ���:�Ƿ������¶ȼ��.1��ʾ����
#define OPT_M_DUMPTUREENABLE			TEXT("mdumptureeable")		//�ͻ���:�Ƿ����������鿴.1��ʾ����
#define OPT_M_HARDWAREENABLE			TEXT("mhardwareenable")		//�ͻ���:�Ƿ�����Ӳ�����.1��ʾ����
#define OPT_M_SHOWEXCEPTIONCLIENT		TEXT("mshowexceptionclient")//�ͻ���:����ʾ�쳣Ӳ���Ŀͻ���.1��ʾ����

#define OPT_M_SEVENDAYCHECKENABLE		TEXT("sevendaycheckenable")	//�ͻ���:�Ƿ�7��������.1��ʾ����
#define OPT_M_TEMPERATURECPU			TEXT("mtemperaturecpu")		//�ͻ���:CPU����¶�
#define OPT_M_TEMPERATUREBOARD			TEXT("mtemperatureboard")	//�ͻ���:��������¶�
#define OPT_M_TEMPERATUREDISK			TEXT("mtemperaturedisk")	//�ͻ���:Ӳ������¶�
#define OPT_M_TEMPERATUREDISPLAY		TEXT("mtemperaturedisplay")	//�ͻ���:�Կ�����¶�
#define OPT_M_IEHISTORYENABLE			TEXT("miehistoryenable")	//�ͻ���:�Ƿ���IE��ʷ��¼
#define OPT_M_IEHISTORYSAVEDAY			TEXT("miehistorysaveday")	//�ͻ���:IE��ʷ��¼����ʱ��
#define OPT_M_RANDSELMENUBG				TEXT("mrandselmenubg")		//�ͻ���:���ѡ��˵�Ƥ����1.��;0��
#define OPT_M_MENUBG					TEXT("mmenubg")				//�ͻ���:��ǰѡ�в˵�Ƥ��
#define OPT_M_CUSTOMMENUBG				TEXT("mcustommenubg")		//�ͻ���:�Զ���˵�Ƥ����|�߷ָ
#define OPT_M_QQHISTORYENABLE			TEXT("mqqhistoryenable")	//�ͻ���:�Ƿ���QQ��¼��¼
#define OPT_M_QQHISTORYSAVEDAY			TEXT("miehistorysaveday")	//�ͻ���:QQ��¼��¼����ʱ��
#define OPT_M_CLICKSTARTGAME			TEXT("clickstartgame")		//�ͻ���:�Ƿ�˫��������Ϸ(0|1)
#define OPT_M_MENUANIMATION				TEXT("menuanimation")		//�ͻ���:�Ƿ����ò˵�����Ч��

#define OPT_M_MULTISYSTEMDISPTIME		TEXT("multisystemdisptime")	//����:��ϵͳ�ȴ�ѡ���ʱ��.
#define OPT_M_DHCPTFTPENABLE			TEXT("dhcptftpenable")		//����:�Ƿ���DHCP��TFTP������(���ֵ����0λ:0��ʾ��Ϊ���ã�1��ʾ��Ϊ����;��һλ��1��֤�ɹ���0��ʾ��֤ʧ��)
#define OPT_M_SHOWWIZARD				TEXT("showwizard")			//�Ƿ���ʾ������

#define OPT_M_ENABLEUDISK				TEXT("menableudisk")		//���˴���:������˴���(0,1)
#define OPT_M_UDISKVOL					TEXT("mudiskvol")			//���˴���:���صĸ��˴����̷�
#define OPT_M_UDISKSIZE					TEXT("mudisksize")			//���˴���:���˴��̴�С(M)
#define OPT_M_ARCHIVECOUNT				TEXT("marchivecount")		//���˴���:��Ϸ�浵����
#define OPT_M_UDISKDIR					TEXT("mudiskdir")			//���˴���:��Ÿ��˴����ļ���Ŀ¼
#define OPT_M_ENABLECLEAN				TEXT("menableclean")		//���˴���:������������˴���(0,1)
#define OPT_M_CLEANCYCLE				TEXT("mcleancycle")			//���˴���:�������������(��)

#define OPT_M_WRITEBACKLIMIT			TEXT("mwritebacklimit")		//��д����,��M��
#define OPT_M_MOUNTDISKATBOOT			TEXT("mmountdiskatboot")	//�Ƿ���������ǰˢ�̣�1��,0��)


#define OPT_M_PREREADENABLE				TEXT("prereadenable")		//�ͻ������Ƿ�����Ԥ����0��1�ǣ�
#define OPT_M_USBPNPENABLE				TEXT("usbpnpenable")		//�ͻ������Ƿ�����USBPNP��0��1�ǣ�
#define OPT_M_VIDEOPNPENABLE			TEXT("videopnpenable")		//�ͻ������Ƿ������Կ�PNP��0��1�ǣ�
#define OPT_M_DISPLAYPNPENABLE			TEXT("displaypnpenable")	//�ͻ������Ƿ�������ʾ��PNP��0��1�ǣ�
#define OPT_M_HDMIFORBIDDEN				TEXT("hdmiforbidden")		//�ͻ������Ƿ����HDMI������0��1�ǣ�

#define OPT_M_SHUTDOWNENABLE			TEXT("shutdownenable")		//�Ƿ����ÿ��ٹػ�
#define OPT_M_FORCEDSHUTDOWNENABLE		TEXT("forcedshutdown")		//�Ƿ�����ǿ�ƹػ�
#define	OPT_M_UPSUPERENABLE				TEXT("upsuperenable")		//�Ƿ�����ͻ����ϴ�ϵͳ��������
#define OPT_M_ASSISTENABLE				TEXT("assistenable")		//�ͻ������Ƿ����÷��ӷѣ�0��1�ǣ�
#define	OPT_M_VIEWERENABLE				TEXT("viewerenable")		//�Ƿ�������Ϸ���ز鿴��Զ�����ӣ�0��1�ǣ�

//ssdѡ��
#define OPT_S_DEPLOY_SYNGAME			TEXT("deploysyngame")		//ʩ��ģʽ�Ƿ�ͬ����Ϸ��0��1�ǣ�
#define OPT_S_NODEPLOY_SYNGAME			TEXT("nodeploysyngame")		//��ʩ��ģʽ�Ƿ�ͬ����Ϸ��0��1�ǣ�
#define OPT_S_SSDSYNSPEED				TEXT("ssddspeed")			//ssdͬ���ٶ�:�ٶ�����(n)(bytes/s)
#define OPT_S_WRITESIZE					TEXT("ssdwritesize")		//ssd��д��С��G��

//����·�����ͻ���ʶ��
#define	OPT_M_NETMOONENABLE				TEXT("netmoonenable")		//�Ƿ��������¿ͻ���ʶ��

//���������
#define OPT_S_CLOUDDESKTOP				TEXT("sclouddesktop")		//�Ƿ�ʹ��������(1��,0��)
#define OPT_S_CLOUDTOOLDLG				TEXT("scloudtooldlg")		//�Ƿ�ʹ�������湤�����(1��,0��)

#define OPT_S_SKIN						TEXT("sskin")				//Ƥ��
#define OPT_S_LAYER						TEXT("layer")
#define OPT_S_SW_COMNAME				TEXT("sswcomname")			//�Ƿ���ʾ�������(1��,0��)
#define OPT_S_SW_COMIP					TEXT("sswcomip")			//�Ƿ���ʾ�����ip(1��,0��)
#define OPT_S_COMNAME_TOPMARGIN			TEXT("scomnametopmargin")	//��������ϱ߾�
#define OPT_S_COMNAME_DIGITONLY			TEXT("scomnamedigitonly")	//ֻȡ��������е�����(1��,0��)
#define OPT_S_COMNAME_PREFIX			TEXT("scomnameprefix")		//�������ǰ׺
#define OPT_S_COMNAME_SURFIX			TEXT("scomnamesurfix")		//���������׺
#define OPT_S_COMNAME_FONT				TEXT("scomnamefont")		//�����������
#define OPT_S_COMNAME_FONTSIZE			TEXT("scomnamefontsize")	//��������ֺ�
#define OPT_S_COMNAME_FONTCOLOR			TEXT("scomnamefontcolor")	//�����������ɫ
#define OPT_S_COMNAME_FONTSHAPE			TEXT("scomnamefontshape")	//�������������״(0|0|0:�Ƿ����,б��,�»���)

#define OPT_M_NOTIEABLE					TEXT("mnoticeeable")			//�Ƿ����ù���
#define OPT_S_NOTICE_TITLE				TEXT("snoticetitle")			//�������
#define OPT_S_NOTICE_TITLE_FONTNAME		TEXT("snoticetitlefontname")	//�����������
#define OPT_S_NOTICE_TITLE_FONTSIZE		TEXT("snoticetitlefontsize")	//��������ֺ�
#define OPT_S_NOTICE_TITLE_FONTCOLOR	TEXT("snoticetitlefontcolor")	//�������������ɫ
#define OPT_S_NOTICE_TITLE_FONTSHAPE	TEXT("snoticetitlefontshape")	//�������������״


#define OPT_S_SW_WEATHER				TEXT("sswweather")				//�Ƿ���ʾ����(1��,0��)
#define OPT_S_WEATHER_AREAID			TEXT("sweatherareaid")			//�������
#define OPT_S_WEATHER_DATA				TEXT("sweatherdata")			//����Ԥ������

#define OPT_S_SW_CALENDAR				TEXT("sswcalendar")				//�Ƿ���ʾ����(1��,0��)
#define OPT_S_SW_LUNAR					TEXT("sshowlunar")				//�Ƿ���ʾũ��(1��,0��)
#define OPT_S_SW_ZODIAC					TEXT("sshowzodiac")				//�Ƿ���ʾ����(1��,0��)

#define OPT_S_SW_RATE					TEXT("sswrate")					//�Ƿ���ʾ����
#define OPT_S_RATE_TITLE_FONTNAME		TEXT("sratetitlefontname")		//���ʱ�����������
#define OPT_S_RATE_TITLE_FONTSIZE		TEXT("sratetitlefontsize")		//���ʱ����ֺ�
#define OPT_S_RATE_TITLE_FONTCOLOR		TEXT("sratetitlefontcolor")		//���ʱ���������ɫ
#define OPT_S_RATE_TITLE_FONTSHAPE		TEXT("sratetitlefontshape")		//���ʱ���������״
#define OPT_S_RATE_FONTNAME				TEXT("sratefontname")			//������������
#define OPT_S_RATE_FONTSIZE				TEXT("sratefontsize")			//�����ֺ�
#define OPT_S_RATE_FONTCOLOR			TEXT("sratefontcolor")			//����������ɫ
#define OPT_S_RATE_FONTSHAPE			TEXT("sratefontshape")			//����������״
#define OPT_S_CLIENT_LANGUAGEID			TEXT("sclanguageid")			//�ͻ�������ID


//����̨���ƿͻ������������������̨���������������������������ͨ��udp֪ͨ�ͻ��� //(data��������ݽ���)
#define CONTROL_CLINET_INSTPROT			1		//��װ������ָ������.string(Ҫ�����ķ���)+string(�������ķ���)
#define CONTROL_CLINET_REMOVEPROT		2		//ɾ����ԭ
#define CONTROL_CLINET_SHUTDOWN			3		//�ػ�����������dword��Ϊ0��ʾ�ػ���Ϊ1��ʾ����
#define CONTROL_CLINET_VIEWPROCLIST		4		//��ȡ�����б�. send(cmd + xmlstring)
#define CONTROL_CLINET_KILLPROC			5		//kill����,dword:pid.
#define CONTROL_CLIENT_RUNPROCESS		6		//���пͻ�������string:����ȫ·����.
#define CONTROL_CLIENT_RUNVNC			7		//���пͻ���VNC��
#define CONTROL_CLIENT_RAPIDSHUTDOWN	8		//���ٹػ�


//����ͨ������
#define CMD_DB_HEART					0x0101		//����������У��ޣ����У���.
#define CMD_DB_SQL						0x0102		//ִ��SQL���. ���У�sql���,���У�row, colomn, ��¼��
#define CMD_DB_TSQL						0x0103		//������ʽִ��SQL�����,�����᷵�ؼ�¼����
#define CMD_DB_ICON						0x0104		//���ݿ�ͼ�����.

#define CMD_DB_GETDHCPINFO				0x0105      //��ȡdhcp�ͻ�����Ϣ
#define CMD_DB_LOARDCLIENTINFO			0x0106      //��ȡloader�ͻ�����Ϣ


#define ICON_OP_GET						0			//��ȡ��Ϸ��ͼ������:gid.����ͼ������(gid + hash + length + data)
#define ICON_OP_SET						1			//������Ϸ��ͼ������(��ӻ��߸���):gid + length + data.���سɹ����
#define ICON_OP_DEL						2			//ɾ����Ϸ��ͼ��:count + gid���顣������ɾ��ͼ������).���سɹ����
#define ICON_OP_FILENAME				3			//����ͼ���ļ����޸�ͼ������.(gid, string(ͼ���ļ���)), ���سɹ����.
#define ICON_OP_GETLIST					4			//ȡ��ͼ���б�(count+gid,hash����)

#define CMD_USER_REGISTER				0x0201		//���˴����û�ע��
#define CMD_USER_LOGIN					0x0202		//���˴����û���¼
#define CMD_USER_MODIFYPASSWORD			0x0203		//���˴����޸�����
#define CMD_USER_DELUDFILE				0x0204		//ɾ�����˴����ļ�
#define CMD_USER_QUERYPWD				0X0205		//��ѯ�û�����,������Դ����Ŀ��2017.6.15 �����ţ�256

#define CMD_CLI_HEART					0x0301		//�ͻ�������
#define CMD_CLI_CLIENTUPDATEINDEX		0x0302		//�ͻ�����ѯ�����ļ��б�.
//#define CMD_CLI_NODEUPDATEINDEX			0x0303		//�ڵ��ѯ�����ļ��б�.
#define CMD_CLI_QUERYDIRINFO			0x0304		//��ѯĿ¼��Ϣ.
#define CMD_CLI_QUERYFILEINFO			0x0305		//�ͻ�����ѯ�ļ���Ϣ
#define CMD_CLI_DOWNFILEBLOCK			0x0306		//�ͻ��������ļ��顣
#define CMD_CLI_RPTCLIENTINFO			0x0307		//�ϱ��ͻ���������Ϣ.
#define CMD_CLI_RPTHARDINFO				0x0308		//�ϱ��ͻ���Ӳ����Ϣ
#define CMD_CLI_RPTTEMPRATURE			0x0309		//�ϱ��ͻ����¶���Ϣ
#define CMD_CLI_RPTGAMEMENUCLICK		0x030A		//�˵��ϱ���Ϸ�����,�˵����д���
#define CMD_CLI_CONSOLE2CLIENT			0x030B		//�����ת������̨����ͻ���.  //���ڿ��ƿͻ�����ԭ���������ػ�������.
#define CMD_CLI_CLIENT2CONSOLE			0x030C		//�����ת���ͻ��˷��������̨	 //���ڿͻ����ϱ���Ϣ������̨.
#define CMD_CLI_RPTGAMEMENUCLICKEX		0x030D		//15��˵��ϱ���Ϸ�����,�˵����д���
#define CMD_CLI_NODEUPDATEINDEXEX		0x030E		//�ڵ��ѯ�����ļ��б�(��չ)64λ�汾.

// V2017.6.15�汾����
//�ӽڵ��ϴ����ݿ⣬�������ڵ�ͬ����
//���������CMD_CLI_UPLOADFILE�������ʹ��
//���ڴӽڵ������ڵ��ϴ�ͬ������
#define CMD_CLI_CHECKUPLOADENABLE		0x030F		//�ӽڵ����Ƿ����������ڵ��ϴ�ͬ�����ݣ����ڵ㲻����
#define CMD_CLI_CHECKUPLOADOVER			0x0310		//�ͻ��˼��ӽڵ������ڵ��ϴ�ͬ�������Ƿ�������ӽڵ㴦��
#define CMD_CLI_SLAVESYNCDB2MASTER		0x0311		//�ͻ�����ӽڵ㷢��ͬ�����ݣ��ӽڵ�ʹ��CMD_CLI_UPLOADFILE���������ڵ㷢�����ݣ����ڵ㲻���������
//

// ���ڴӿͻ�����ȡ�ͻ�����Ϣ
#define CONTROL_CLINET_BASEINFO			0x0901		//������Ϣ��ѯ
#define CONTROL_CLINET_PING				0x0902		//ping
#define CONTROL_CLINET_DRIVERINFO		0x0903

#define CMD_CLI_GETSYSOPTION			0x0401		//��ȡϵͳѡ���б�
#define CMD_CLI_GETSERVERLIST			0x0402		//��ȡ�������б�
#define CMD_CLI_GETVDISKLIST			0x0403		//��ȡ�������б�
#define CMD_CLI_GETSERVERTIME			0x0404		//��ȡ������ʱ��
#define CMD_CLI_GETGAMELIST				0x0405		//��ȡ��Ϸ�б�����
#define CMD_CLI_GETGAMEINFO				0x0406		//������Ϸ
#define CMD_CLI_GETICONLIST				0x0407		//��ȡͼ���б�����
#define CMD_CLI_GETICONINFO				0x0408		//����ͼ��
#define CMD_CLI_GETSHORTCUT				0x0409		//��ȡ��ݷ�ʽ
#define CMD_CLI_GETWALLPAPER			0x040A		//��ȡ��������ǽֽ��Ϣ
#define CMD_CLI_GETTASKLIST				0x040B		//��ȡ��������
#define CMD_CLI_GETIPLIST				0x040C		//��ȡ�ͻ����б�
#define CMD_CLI_SENDDUMP				0x040D		//���Ϳͻ���dump
#define CMD_CLI_QUERYRATE				0x040E		//��ȡ��������
#define CMD_CLI_QUERYKMEAUXML			0x040F		//��ȡ�˵�XML
#define CMD_CLI_QUERYGAMEICOPATH		0x0410		//��ȡ��Ϸ�����ݷ�ʽͼ��·��
#define CMD_CLI_QUERYALLGAMESVR			0x0411		//��ѯ������Ϸ�������б�
#define CMD_CLI_QUERYALLGAMESVRDRIVER	0x0412		//��ѯ������Ϸ��������Ϸ����Ϣ�б�
#define CMD_CLI_QUERYTASKLIST			0x0413		//��ѯͨ�������Ϣ
#define CMD_CLI_DOWNTASKZIP				0x0414		//����ͨ�����
#define CMD_CLI_GETREPORTSTYLE			0x0415		//ȡ�Ƿ��ϱ���־����
#define CMD_CLI_GETSSDWORKMODE			0x0416      //ȡ�Ƿ����ʩ��ģʽ
#define CMD_CLI_GETSSDGAMEINFO			0x0417		//ȡSSD����Ϸ��Ϣ
#define CMD_CLI_UPLOADFILE				0x0418		//�ϴ��ļ�
#define CMD_CLI_ADDGAMECONFIG			0x0419		//�����Ϸ����
#define CMD_CLI_REPORTSSDINFO			0x041A		//SSDʩ����Ϣ
#define CMD_CLI_MODIFYSSDINIT			0x041B		//�޸�SSD��ʼ��
#define CMD_CLI_MODIFYSSDDEPLOY			0x041C		//�޸�SSDʩ��ģʽ
#define CMD_CLI_QUERYGAMECONFIG			0x041D		//��ȡ��Ϸ����
#define CMD_CLI_REPORTSSDIMAGE			0x041E		//�ϱ��ͻ���SSD����
#define CMD_CLI_MODIFYTOPTION			0x041F		//�޸�ϵͳѡ��
#define CMD_CLI_GETSSDGAMEINFOEX		0x0420		//ȡSSD����Ϸ��Ϣ��չ
#define CMD_CLI_GETSSDGAMEINFOEXEX		0x0421		//ȡSSD����Ϸ��Ϣ��չ(�ӷ���˰汾��)
#define CMD_CLI_GETGAMEINFOEX			0x0422		//������Ϸ��չ

#define CMD_CLI_LOGTOSVR				0x0422		//�ͻ���������д��־(����:type(DWORD����)+level(DWORD)+ MSG(string))
#define CMD_CLI_GETTASKLISTEX			0x0423		//��ȡ��������������չ����ȡimageid
#define CMD_CLI_QUERYALLGAMESVREXEX		0x0424      //��Ϸ�̾���
#define CMD_CLI_QUERYKMEAUXMLEX			0x0425		//��ȡ�²˵�XML

#define CMD_CON_REFRESHGAMELIST			0x0501		//����̨֪ͨˢ����Դ�б�
#define CMD_CON_QUERYONLINEMACHINE		0x0502		//����̨��ѯ���߿ͻ���
#define CMD_CON_QUERYTEMPRATURE			0x0503		//����̨��ѯ�����¶���Ϣ.
#define CMD_CON_NOTIFYONLINE			0x0504		//֪ͨ����̨���ͻ����Ƿ�����
#define CMD_CON_NOTIFYHARDWARE			0x0505		//֪ͨ����̨���ͻ���Ӳ����Ϣ
#define CMD_CON_ACCEPTHARDWARE			0x0506		//����̨ȷ��Ӳ�����
#define CMD_CON_QUERYSVRINFO			0x0507		//����̨ȡ������������Ϣ
#define CMD_CON_QUERYDISKLIST			0x0508		//����̨ȡ���̷����б���Ϣ
#define CMD_CON_NOTIFYLOGINFO			0x0509		//֪ͨ����̨����־��Ϣ.
#define CMD_CON_QUERYIPINFO				0x050A		//��ѯ�������,ip
#define CMD_CON_QUERYCHECK				0x050B		//��ѯ��֤�Ƿ�ɹ�
#define CMD_CON_QUERYWEATHER			0x050C		//��ѯ����
#define CMD_CON_REMOTENODESVR			0x050D		//Զ�̽ڵ�
#define CMD_CON_QUERYNODESTATUS			0x050E		//��ѯ�ڵ�״̬(�贫��������������IP)
#define CMD_CON_NOTIFYSYNCDATA			0x050F		//����̨֪ͨˢ��(��ݷ�ʽ��������������ǽֽ)
#define CMD_CON_QUERYSSDIMAGESYNCINFO	0x0510		//���ƻ�ȡSSD����ͬ����Ϣ
#define CMD_CON_QUERYNODENEEDUP			0x0511      //��ȡ�ڵ��Ƿ���Ҫ����
#define CMD_CON_NOTIFYNODEUP			0x0512      //֪ͨ�ڵ�����
#define CMD_CON_QUERYMASKGAME			0x0513		//����̨��ȡ��Ϸ������
#define CMD_CON_LOGIN					0x0514		//����̨��¼��֤
#define CMD_CON_CHECK_VER				0x0515		//����̨��ȡ�������
#define CMD_CON_DEL_DUMP_FILE			0x0516		//��̨ɾ��dump�ļ�
#define CMD_CON_QUERYONLINEMACHINEEX	0x0517		//����̨��ѯ���߿ͻ�����չ(��������ʱ��)
#define CMD_CONSOLE_REPLACE_DATA		0x0518		//����̨�����޸�tOption����

#define CMD_MGR_TAKEOVER				0x0601		//�ֶ��ӹ�(�޲���)
#define CMD_MGR_CANCELTAKEOVER			0x0602		//�ֶ�ȡ���ӹ�(�޲���)
#define CMD_MGR_NOTIFYTAKEOVER			0x0603		//֪ͨ�ӹ�(�Ƿ�ӹܱ�־+��������+ip����)
#define CMD_MGR_QUERYTAKEOVER			0x0604		//��ѯ�ӹ�(�ӹ��߱�־+�Ƿ�ӹܱ�־+��������+ip����)
#define CMD_MGR_ISINSERVERLIST			0x0605		//��ѯ�ڵ��Ƿ��ڷ������б���(�ڵ��������)
#define CMD_MGR_QUERYMAIN				0x0606		//��ѯ��������
#define CMD_MGR_UPNODEDISKDRIVER		0x0607		//���½ڵ��̷���Ϣ
#define CMD_MGR_REPORTSVRHARDWARE		0x0608		//�ϱ�������Ӳ����Ϣ
#define CMD_MGR_GETUPGRADEINFO			0x0609      //��ȡ�������ļ���Ϣ���ж��Ƿ��������
#define CMD_MGR_REPORTSVRIPINFO			0x060A		//�ϱ�������ip��Ϣ
#define CMD_MGR_REPORTSVRIPINFOEX		0x060B		//�ϱ�������ip��MASK����Ϣ

#define CMD_SVRMONITOR_DISKCPUMEM		0x0701		//��ȡ�̷�����,CPUռ��,�ڴ�ʹ��(cpu+�̷�����+����(�̸�+ʹ����)+�ڴ��ܴ�С+�����ڴ�+��������+����(����+ʹ����)))
#define CMD_IEQQ_QUERYNETBARINFO		0x0801		//IE��QQ��¼��ȡ����ID�����ƣ�����������(ID,NAME,USER,���ն�,�����ն�)
#define CMD_DOWNLOAD_VIEWER_FILES		0x0901      //�ͻ����������ز鿴�����ļ��б�
#define CMD_PLDOWNFAILEDCOUNT			0X0902		//PL����ʧ�ܵĴ���

class CLock
{
private:
	CRITICAL_SECTION m_lock;
public:
	CLock()			{ InitializeCriticalSection(&m_lock);	}
	~CLock()		{ DeleteCriticalSection(&m_lock);		}
	void Lock()		{ EnterCriticalSection(&m_lock);		}
	void UnLock()	{ LeaveCriticalSection(&m_lock);		}
};

template <typename T>
class ObjectLock
{
private:
	T& _lock;
public:
	ObjectLock(T& lock): _lock(lock) { _lock.Lock(); }
	~ObjectLock()	{ _lock.UnLock(); }
};

#define OBJECT_LOCK(lock) ObjectLock<CLock> __xlock__(lock)

//return is 64bit operation system.
bool __stdcall AfxIs64BitOpertionSystem();

//generate exception dump file. 
LONG __stdcall AfxUnHandledExceptionFilter(PEXCEPTION_POINTERS pExcept);

inline void AfxSetExptHandle() { SetUnhandledExceptionFilter(AfxUnHandledExceptionFilter); }

//get application root path with "\\"
LPTSTR __stdcall AfxGetAppPath(LPTSTR szPath, DWORD dwSize = MAX_PATH, LPCTSTR szAppend = NULL);

//create directory tree.
void __stdcall AfxCreateDirectory(LPCTSTR szDirectory, size_t offset = 0);

//delete all file and sub dir.
void AfxDeleteDirectory(LPCTSTR szDirectory, HANDLE hExit = NULL);

//delete all match file and sub dir 's file.
void AfxDeleteMatchFile(LPCTSTR szDirectory, LPCTSTR szFilter, HANDLE hExit = NULL);

//get windows system error text.
LPTSTR __stdcall AfxGetWinErrorText(LPTSTR buf, DWORD dwSize, DWORD dwError);

//get file version.x.x.x.x
LPTSTR __stdcall AfxGetFileVersion(LPCTSTR pFileName, LPTSTR pVersion);

//get current user registry key.
LPTSTR __stdcall AfxGetCurUserHKeyRoot(LPTSTR HkeyRoot, DWORD dwSize);

//read application config.
LPTSTR __stdcall AfxGetSysString(LPCTSTR Section, LPCTSTR Key, LPTSTR Value, DWORD dwSize = MAX_PATH, LPCTSTR Default = TEXT(""));
DWORD  __stdcall AfxGetSysLong(LPCTSTR Section, LPCTSTR Key, long Default = 0);

//read application config for language
LPTSTR __stdcall AfxGetLangString(LPCTSTR Section, LPCTSTR Key, LPTSTR Value, 
	DWORD dwSize = MAX_PATH, LPCTSTR Default = TEXT(""));
LPTSTR __stdcall AfxGetLangStringEx(HANDLE hInstance, UINT uID, LPTSTR Value,
	DWORD dwSize, LPCTSTR Default = TEXT(""));

//read application config for language dll path name 
LPTSTR __stdcall AfxGetLangDll(LPTSTR pPath, DWORD dwSize = MAX_PATH);

//get url use CPkgHelper
LPSTR __stdcall AfxGetUrlString(LPSTR lpBuffer, DWORD dwSize, int nUrl);

//set language id
void __stdcall AfxSetLangId(WORD wLangID);

//get idc class name
LPTSTR __stdcall AfxGetIdcClassName(LPCTSTR szGuid, LPTSTR szName, DWORD dwSize = MAX_PATH);

//get idc area name
LPTSTR __stdcall AfxGetIdcAreaName(LPCTSTR szGuid, LPTSTR szName, DWORD dwSize = MAX_PATH);


//write application config.
void   __stdcall AfxSetSysString(LPCTSTR Section, LPCTSTR Key, LPCTSTR Value);
void   __stdcall AfxSetSysLong(LPCTSTR Section, LPCTSTR Key, long Value);

//create a new guid.
LPTSTR __stdcall AfxCreateGuidString(LPTSTR guid);

//format time32_t to date time string.
LPTSTR __stdcall AfxFormatTimeString(DWORD time, LPTSTR buffer, DWORD dwSize);

//format ip(network order) to string.
LPTSTR __stdcall AfxFormatIpString(DWORD ip, LPTSTR buffer, DWORD dwSize);

//convert filetime to time_t.
DWORD  __stdcall AfxFileTime2UtcTime(FILETIME& ft);

//convert time_t to filetime.
void   __stdcall AfxUtcTime2FileTime(DWORD time, FILETIME& ft);

//get process id.
DWORD __stdcall  AfxGetProcIdByName(LPCTSTR szProcName);

//get parent process id.
DWORD __stdcall  AfxGetParentProcessId();

//return process token by process name.
HANDLE __stdcall AfxGetTokenByProcName(LPCTSTR lpName);

//run process by "explore.exe" token.(current user.)
bool __stdcall AfxRunProcess(LPCTSTR lpProcess, LPCTSTR lpParameter = NULL);

//kill process by process name.
bool __stdcall AfxKillProcess(LPCTSTR lpProcess);

//adjust process privilege.
void __stdcall AfxSetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);

//split string.
inline void	AfxSplitString(const tstring& source, std::vector<tstring>& subs, TCHAR chr = TEXT('|'));

//network connect with timeout(second).
SOCKET __stdcall AfxSocketConnect(LPCTSTR ip, WORD port, DWORD timeout = 2);

//socket listen port with bind ip.
SOCKET __stdcall AfxSocketListen(WORD port, LPCTSTR ip = NULL);

//socket communication.(by pkgheader).
DWORD  __stdcall AfxSocketExecute(SOCKET sck, LPCSTR pOutData, int outLength, LPSTR pInData, int inLength);
DWORD  __stdcall AfxSocketExecuteEx(SOCKET sck, LPCSTR pOutData, int outLength, LPSTR pInData, int inLength, int try_max);

//socket close.
void   __stdcall AfxSocketClose(SOCKET& sck);

//send udp data.
bool   __stdcall AfxSendUdpNotify(LPCSTR pdata, DWORD length, LPCTSTR ip, WORD port);

//send log to console.
void   __cdecl	 AfxSendLogToConsole(LPCTSTR ip, DWORD logtype, LPCTSTR format, ...);

//get device name by device class id.
LPCTSTR __stdcall AfxGetFirstDevName(const GUID& devclassguid, LPTSTR szDevName, DWORD dwSize,LPTSTR szDevId = NULL, DWORD dwIdSize = 0);
LPCTSTR __stdcall AfxGetDevNameByWmi(LPCTSTR szWql, LPCTSTR szFiled, LPTSTR szDevName, DWORD dwSize);

//save icon to buffer.
DWORD __stdcall AfxSaveHICONToData(HICON hIcon, LPCSTR data, DWORD length);

//load icon from buffer.
HICON __stdcall	AfxLoadHICONFromData(LPCSTR data, DWORD length);

//determine if a ip is one of local host's ips
bool __stdcall AfxIsLocalIP(DWORD ip, bool b127IsLocalMachine=true);

//broadcast detect takeover server
bool __stdcall AfxDetectTakeover(DWORD bcAddr, LPDWORD lpServerIPs,int tmo = 1, int nMaxRetry = 5);
bool __stdcall AfxDetectTakeoverEx(int main_or_takeover, DWORD bcAddr, LPDWORD lpServerIPs,int tmo = 1, int nMaxRetry = 5);


//service helper function.
//max_path/ERROR_SUCCESS/guid(single instance)	//AfxGetServiceInfo
typedef DWORD (__stdcall* AFXGETSERVICEINFO)(LPTSTR SvrName, LPTSTR SvrDescription, LPTSTR guid);	
//AfxSeviceProc:service main function. service exit if the function exit.
typedef DWORD (__stdcall* AFXSEVICEPROC)(HANDLE hExit);

bool  __stdcall AfxIsServiceExist(LPCTSTR lpszSvrName);
DWORD __stdcall AfxInstallService(LPCTSTR lpszSvrName, LPCTSTR lpszSvrDicription, LPCTSTR path);
DWORD __stdcall AfxRemoveService(LPCTSTR lpszSvrName);
DWORD __stdcall AfxGetServiceState(LPCTSTR lpszSvrName);
DWORD __stdcall AfxStartService(LPCTSTR lpszSvrName);
DWORD __stdcall AfxStopService(LPCTSTR lpszSvrName);
DWORD __stdcall AfxRunAsService(LPCTSTR SvrExePath, int argc, _TCHAR* argv[]);


//encode function.
DWORD  __stdcall AfxCrc32Encode(DWORD crc, const void* data, DWORD ByteLen);
DWORD  __stdcall AfxGetFileCrc32(LPCTSTR szFile);
LPTSTR __stdcall AfxMD5Encode(const void* data, DWORD ByteLen, LPTSTR md5);
void* __stdcall AfxMD5EncodeEx(const void* data, DWORD ByteLen, void *md5);
LPTSTR __stdcall AfxGetFileMd5(LPCTSTR szFile, LPTSTR md5);
LPTSTR __stdcall AfxUriEncode(LPCTSTR source, LPTSTR dest, int nSize);
LPWSTR __stdcall AfxUTF82StrW(LPCSTR  pUTF8, LPWSTR pUnicode, int& nSize);
LPSTR  __stdcall AfxUTF82StrA(LPCSTR  pUTF8, LPSTR pChar, int& nSize);
LPSTR  __stdcall AfxStrW2UTF8(LPCWSTR pUnicode, LPSTR pUtf8, int& nSize);
LPSTR  __stdcall AfxStrA2UTF8(LPCSTR pChar, LPSTR pUtf8, int& nSize);

#ifdef _UNICODE
#define AfxUTF82Str			AfxUTF82StrW
#define AfxStr2UTF8			AfxStrW2UTF8
#else
#define AfxUTF82Str			AfxUTF82StrA
#define AfxStr2UTF8			AfxStrA2UTF8
#endif

//write log function.
HANDLE __stdcall AfxCreateLogger(LPCTSTR szModuleName);
void  __cdecl AfxWriteLogger(HANDLE hLogger, LPCTSTR formater, ...);
void  __stdcall AfxCloseLogger(HANDLE& hLogger);
void __cdecl AfxWriteDbgLog(LPCTSTR formater, ...);

//////////////////////////////////////////////////////////////////////////
//scsi disk driver function.

#pragma pack(push, 1)
typedef struct DisklessInfo
{
	ULONG is_admin;			//admin or not
	ULONG server_ip;		//mirror server ip
	ULONG diskless;			//diskless or not
	ULONG dhcp_server_ip;	//dhcp server ip
	ULONG mode_flag;		//ssd boot or not
	ULONG got_volume_pos;	//$volume file record pos got or not(for cache driver)
	LONGLONG volume_pos;	//$volume file record pos (absolute)(for cache driver)
	ULONG reserved[8];
}DISKLESS_INFO, *PDISKLESS_INFO;
#pragma pack()

DWORD __stdcall ScsiDiskInstallDriver();

//����һ�������̷���.ip, port:������,DriverLetter,ָ���Ŀͻ����̷�,TempDirNameָ����ʱ�ļ���Ŀ¼
DWORD __stdcall ScsiDiskMount(DWORD Ip, WORD Port, TCHAR DriverLetter, TCHAR TmpFileDriverLetter, BOOL bMirrorDisk = FALSE, int nDiskNum = 100, BOOL bIsAdmin = FALSE);

//ж�ؼ��ص������̷�����DriverLetter:�����̷�.
DWORD __stdcall ScsiDiskUnmount(TCHAR DriverLetter, BOOL bMirrorDisk = FALSE, int nDiskNum = 100, BOOL IsAdmin = FALSE);

DWORD __stdcall ScsiDiskQueryDisklessInfo(PDWORD DiskLess, PDWORD IsAdmin, PDWORD ServerIp);
DWORD __stdcall ScsiDiskQueryDisklessInfoEx(PDISKLESS_INFO pDiskLessInfo);

//����diskpart.exe���³�ʼ������
DWORD __stdcall ScsiDiskReinitImage(int nDiskNum, TCHAR cVol, DWORD nSizeInMb);

//����format.exe���¸�ʽ������
DWORD __stdcall ScsiDiskReformatImage(TCHAR szVol);


//////////////////////////////////////////////////////////////////////////
//file disk driver function.
DWORD __stdcall FileDiskInstallDriver();

DWORD __stdcall FileDiskMount(DWORD DiskType, DWORD Ip, WORD Port, TCHAR DriverLetter, LPCTSTR UserId);

DWORD __stdcall FileDiskUnmount(TCHAR DriverLetter);


//////////////////////////////////////////////////////////////////////////
//net function.
#define PKG_VERSION				0x0100		//1.0
#define PKG_SIG					'.pkg'
#define PKG_MAXLENGTH			0x10000
#define PKG_STA_SUCCESS			0
#define PKG_STA_ERROR			1

#pragma warning(disable:4200)
struct PkgHeader
{
	DWORD sig;					//package start flag.	
	DWORD length;				//total length, include package header
	DWORD command;				//command.
	DWORD type;					//object type.OBJECT_
	DWORD version;				//version.
	DWORD status;				//status.
	DWORD reserved[4];			//reserved, fill 0.
	char  data[0];				//data.
};
#pragma warning(default:4200)

#include "kcore.inl"

class CPkgHelper;
struct INetModule;

struct INetCallback
{
	virtual void Release() = 0;

	//disconnect socket if return is not error_success.
	virtual long OnAccept(INetModule* pNetModule, DWORD_PTR Id) = 0;
	virtual long OnSend(INetModule* pNetModule, DWORD_PTR Id) = 0;
	virtual long OnReceive(INetModule* pNetModule, DWORD_PTR Id, LPCSTR pRecvBuf, LPSTR pSendBuf) = 0;

	virtual void OnClose(INetModule* pNetModule, DWORD_PTR Id) = 0;
};

struct INetModule
{
	virtual void Release() = 0;

	virtual DWORD Start(WORD port, DWORD_PTR reserved = 0) = 0;
	virtual void Stop() = 0;

	virtual unsigned short GetListPort() = 0;
	virtual void SetNetCallback(INetCallback* pNetCallback) = 0;

	virtual bool GetPeerInfo(DWORD_PTR Id, SOCKET& sck, DWORD& peerip) = 0;
};

bool __stdcall AfxCreateINetModule(INetModule*& pINetModule);


//memory database support.
//open database.
bool __stdcall AfxOpenSqliteMemory(LPCTSTR szDbFileName, sqlite3*& pSqlite, DWORD_PTR& cookie);

//flush database(save).
void __stdcall AfxFlushSqliteMemory(DWORD_PTR cookie);

//close database.
void __stdcall AfxCloseSqliteMemory(DWORD_PTR cookie);

//////////////////////////////////////////////////////////////////////////
//zip helper function.
DECLARE_HANDLE(HZIP);
typedef DWORD ZRESULT;

//ZIP FILE FLAG
#define ZIP_HANDLE   1
#define ZIP_FILENAME 2
#define ZIP_MEMORY   3
#define ZIP_FOLDER   4

#define ZR_OK         0x00000000     // nb. the pseudo-code zr-recent is never returned,
#define ZR_RECENT     0x00000001     // but can be passed to FormatZipMessage.
#define ZR_GENMASK    0x0000FF00
#define ZR_NODUPH     0x00000100     // couldn't duplicate the handle
#define ZR_NOFILE     0x00000200     // couldn't create/open the file
#define ZR_NOALLOC    0x00000300     // failed to allocate some resource
#define ZR_WRITE      0x00000400     // a general error writing to the file
#define ZR_NOTFOUND   0x00000500     // couldn't find that file in the zip
#define ZR_MORE       0x00000600     // there's still more data to be unzipped
#define ZR_CORRUPT    0x00000700     // the zipfile is corrupt or not a zipfile
#define ZR_READ       0x00000800     // a general error reading the file
#define ZR_CALLERMASK 0x00FF0000
#define ZR_ARGS       0x00010000     // general mistake with the arguments
#define ZR_NOTMMAP    0x00020000     // tried to ZipGetMemory, but that only works on mmap zipfiles, which yours wasn't
#define ZR_MEMSIZE    0x00030000     // the memory size is too small
#define ZR_FAILED     0x00040000     // the thing was already failed when you called this function
#define ZR_ENDED      0x00050000     // the zip creation has already been closed
#define ZR_MISSIZE    0x00060000     // the indicated input file size turned out mistaken
#define ZR_PARTIALUNZ 0x00070000     // the file had already been partially unzipped
#define ZR_ZMODE      0x00080000     // tried to mix creating/opening a zip 
#define ZR_BUGMASK    0xFF000000
#define ZR_NOTINITED  0x01000000     // initialisation didn't work
#define ZR_SEEK       0x02000000     // trying to seek in an unseekable file
#define ZR_NOCHANGE   0x04000000     // changed its mind on storage, but not allowed
#define ZR_FLATE      0x05000000     // an internal error in the de/inflation code

typedef struct
{
	int index;
	char name[MAX_PATH];
	DWORD attr;
	FILETIME atime,ctime,mtime;
	long comp_size;
	long unc_size;
} ZIPENTRYA;

typedef struct
{
	int index;
	WCHAR name[MAX_PATH];
	DWORD attr;
	FILETIME atime,ctime,mtime;
	long comp_size;
	long unc_size;
} ZIPENTRYW;

HZIP	AfxCreateZipZ(void *z, unsigned int len, DWORD flags);
ZRESULT AfxZipAddZ(HZIP hz, const TCHAR *dstzn, void *src, unsigned int len, DWORD flags);
ZRESULT AfxCloseZipZ(HZIP hz);
ZRESULT AfxZipGetMemoryZ(HZIP hz, void **buf, unsigned long *len);
DWORD	AfxFormatZipMessageZ(ZRESULT code, char *buf,unsigned int len);
BOOL	AfxAddFolderContentZ(HZIP hZip, TCHAR* AbsolutePath, TCHAR* DirToAdd);
DWORD	AfxFormatZipMessageZ(ZRESULT code, char *buf, DWORD len);

HZIP	AfxOpenZipU(void *z, unsigned int len, DWORD flags);
ZRESULT AfxGetZipItemA(HZIP hz, int index, ZIPENTRYA *ze);
ZRESULT AfxGetZipItemW(HZIP hz, int index, ZIPENTRYW *ze);
ZRESULT AfxFindZipItemA(HZIP hz, const TCHAR *name, bool ic, int *index, ZIPENTRYA *ze);
ZRESULT AfxFindZipItemW(HZIP hz, const TCHAR *name, bool ic, int *index, ZIPENTRYW *ze);
ZRESULT AfxUnzipItem(HZIP hz, int index, void* dst, unsigned int len, DWORD flags);
ZRESULT AfxCloseZipU(HZIP hz);
DWORD	AfxFormatZipMessageU(ZRESULT code, char *buf,DWORD len);

#ifdef _UNICODE
#define ZIPENTRY	ZIPENTRYW
#define AfxGetZipItem	AfxGetZipItemW
#define AfxFindZipItem	AfxFindZipItemW
#else
#define ZIPENTRY ZIPENTRYA
#define AfxGetZipItem	AfxGetZipItemA
#define AfxFindZipItem	AfxFindZipItemA
#endif // _UNICODE


bool AfxEncryptVnc(char* plain,int len, unsigned char* crypted);
bool AfxDecryptVnc(unsigned char* crypted, char* plain, int len);

//pkey(8���ֽ�) nKeyLength=4
void AfxEncryTea(TCHAR* plain,int nlainlength,TCHAR* pkey,int nKeyLength,TCHAR* pCrypt,int& nCryptLength,int round = 32, bool isNetByte = false);
void AfxDecryTea(TCHAR* pCrypt,int nCryptLength,TCHAR* pkey,int nKeyLength,TCHAR* plain,int nlainlength,int round = 32, bool isNetByte = false);

BOOL __stdcall AfxDisableFsRedirection(PVOID* pOldValue);
BOOL __stdcall AfxRevertFsRedirection(PVOID oldValue);

bool __stdcall AfxOnlineBackupDb(sqlite3* pSrcDb, LPSTR pBackupName);
bool __stdcall AfxRunProcessAsAdmin(LPCTSTR lpProcess, LPCTSTR lpParameter);

// SSD��ʼ��ģʽ
typedef enum {INITALLDISK=1,INITIMAGEDISK,INITGAMEDISK}INITSSD;

//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_KCORE

#endif