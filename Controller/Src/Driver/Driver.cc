#include "Driver.hh"
#include "../Dbg/Dbg.hh"
#include "Data/Definitions.hh"

NTSTATUS Driver::Init()
{
	m_Status = LoadDriver(szDriverPath.c_str(), DRIVER_NAMEC);
	if (!NT_SUCCESS(m_Status))
	{
		DBG::Print(LogType::Err, "Failed to load driver!!");
		return m_Status;
	}

	m_Status = InitCom();
	if (!NT_SUCCESS(m_Status))
	{
		DBG::Print(LogType::Err, "Failed to init driver connection!");
		return m_Status;
	}

	return STATUS_SUCCESS;
}

NTSTATUS Driver::ShutDown()
{
	m_Status = RemoveCom();
	if (!NT_SUCCESS(m_Status))
	{
		DBG::Print(LogType::Err, "Failed to remove com!");
		return m_Status;
	}

	m_Status = UnloadDriver(DRIVER_NAMEC);
	if (!NT_SUCCESS(m_Status))
	{
		DBG::Print(LogType::Err, "Failed to unload driver!");
		return m_Status;
	}

	return STATUS_SUCCESS;
}

NTSTATUS Driver::LoadDriver(LPCSTR szDriverPath, LPCSTR szService)
{
	SC_HANDLE scManager;
	SC_HANDLE srvHandle;

	if (!szDriverPath || !szService)
	{
		DBG::Print(LogType::Err, "LoadDriver parameters are empty");
		return STATUS_INVALID_PARAMETER;
	}

	scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!scManager)
	{
		DBG::PrintLastErr("OpenSCManagerA");
		return STATUS_UNSUCCESSFUL;
	}

	srvHandle = CreateServiceA(scManager, szService, szService, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
				SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, szDriverPath, NULL, NULL, NULL, NULL, NULL);

	if (!srvHandle)
	{
		if (GetLastError() == ERROR_SERVICE_EXISTS)
		{
			DBG::PrintLastErr("CreateServiceA");

			srvHandle = OpenServiceA(scManager, szService, SERVICE_ALL_ACCESS);
			if (!srvHandle)
			{
				DBG::PrintLastErr("OpenServiceA");
				CloseServiceHandle(scManager);

				return STATUS_OPEN_FAILED;
			}
		}
		else
		{
			CloseServiceHandle(scManager);
			DBG::PrintLastErr("OpenServiceA");

			return STATUS_OPEN_FAILED;
		}

		CloseServiceHandle(scManager);

		return STATUS_UNSUCCESSFUL;
	}

	DBG::Print(LogType::Info, "Service Created!");

	if (!StartServiceA(srvHandle, 0, NULL))
	{
		if (GetLastError() != ERROR_SERVICE_ALREADY_RUNNING)
		{
			DBG::PrintLastErr("StartServiceA");
			CloseServiceHandle(srvHandle);
			CloseServiceHandle(scManager);

			return STATUS_UNSUCCESSFUL;
		}
	}

	DBG::Print(LogType::Info, "Service Started!");

	CloseServiceHandle(srvHandle);
	CloseServiceHandle(scManager);

	return STATUS_SUCCESS;
}

NTSTATUS Driver::InitCom()
{
	if (m_hDriver)
		return m_Status = STATUS_SUCCESS;

	if ((m_hDriver = CreateFileW(DRIVER_LINK, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE || m_hDriver == NULL)
	{
		DBG::PrintLastErr("CreateFileW");
		return m_Status = STATUS_UNSUCCESSFUL;
	}

	return m_Status = STATUS_SUCCESS;
}

NTSTATUS Driver::RemoveCom()
{
	CloseHandle(m_hDriver);

	if (!DeleteFileW(DRIVER_LINK))
		STATUS_UNSUCCESSFUL;

	return STATUS_SUCCESS;
}

NTSTATUS Driver::UnloadDriver(LPCSTR szService)
{
	SC_HANDLE scManager		= NULL;
	SC_HANDLE srvHandle		= NULL;
	SERVICE_STATUS SvrSta	= { 0 };

	if (!szService)
	{
		DBG::Print(LogType::Err, "UnloadDriver parameters are empty");
		return STATUS_INVALID_PARAMETER;
	}

	scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!scManager)
	{
		DBG::PrintLastErr("OpenSCManagerA");
		return STATUS_UNSUCCESSFUL;
	}

	srvHandle = OpenServiceA(scManager, szService, SERVICE_ALL_ACCESS);
	if (!srvHandle)
	{
		DBG::PrintLastErr("OpenServiceA");
		CloseServiceHandle(scManager);

		return STATUS_OPEN_FAILED;
	}

	if (!ControlService(srvHandle, SERVICE_CONTROL_STOP, &SvrSta))
	{
		DBG::PrintLastErr("ControlService");
	}

	if (!DeleteService(srvHandle))
	{
		DBG::PrintLastErr("ControlService");
	}

	DBG::Print(LogType::Info, "Unloaded Driver!");
	CloseServiceHandle(srvHandle);
	CloseServiceHandle(scManager);

	return STATUS_SUCCESS;
}