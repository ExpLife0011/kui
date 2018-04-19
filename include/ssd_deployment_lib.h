// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SSD_DEPLOYMENT_LIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SSD_DEPLOYMENT_LIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once


#ifdef SSD_DEPLOYMENT_LIB_EXPORTS
#define SSD_DEPLOYMENT_LIB_API __declspec(dllexport)
#else
#define SSD_DEPLOYMENT_LIB_API __declspec(dllimport)
#endif

typedef void *ssd_handle_t;

// ��־�ص��ӿڣ��ص�����/����
typedef void (__stdcall *log_handler_t)(void *, const wchar_t *msg, unsigned __int32 msg_len);

// �����ܴ�С/���Ȼص����ص�����/��С/�ٶ�(kb/m)
typedef void (__stdcall *total_size_handler_t)(void *, unsigned __int64 size);
typedef void (__stdcall *progress_handler_t)(void *, unsigned __int64 size, unsigned __int32 speed);

// ʩ�����
typedef void(__stdcall *deployment_complete_handler_t)(void *);

// SSD��Ϸ�̷�
typedef void(__stdcall *ssd_game_disk_handler_t)(void *, wchar_t);



struct callback_t
{
	log_handler_t log_handler_;

	total_size_handler_t total_size_handler_;
	progress_handler_t progress_handler_;

	deployment_complete_handler_t complete_handler_;
	ssd_game_disk_handler_t ssd_game_disk_handler_;
};

enum class initssd_t
{
	init_alldisk = 1,
	init_imagedisk,
	init_gamedisk
};

struct param_t
{
	bool is_deployment_;
	int  force_init_type;
	bool is_create_process_;

	bool is_deploy_mode_need_update_game_;
	bool is_none_deploy_mode_need_update_game_;
	bool is_check_vendor_;
	unsigned __int32 none_deploy_mode_limit_update_speed_;
	unsigned __int64 writecallback_disk_size_;
};

// ����ssd���, �ص��ӿ�/�ص�����
SSD_DEPLOYMENT_LIB_API ssd_handle_t __stdcall create_ssd_handle(const callback_t &, void *param);
SSD_DEPLOYMENT_LIB_API void __stdcall destroy_ssd_handle(ssd_handle_t handle);

// ����ssd���
SSD_DEPLOYMENT_LIB_API bool __stdcall start_ssd(ssd_handle_t handle, const param_t &);

// ֹͣssd���
SSD_DEPLOYMENT_LIB_API void __stdcall stop_ssd(ssd_handle_t handle);




