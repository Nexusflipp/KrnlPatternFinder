#include "Src/Dbg/Dbg.hh"
#include "Src/Patterns/Patterns.hh"
#include "Src/Include/Inc_Base.hh"
#include "Src/Driver/Data/Definitions.hh"

int main()
{
	NTSTATUS Status = STATUS_SUCCESS;

	DBG::Print(LogType::Info, "Please paste the path of the driver and then press enter!");
	std::getline(std::cin, szDriverPath);

	while (GetFileAttributesA(szDriverPath.c_str()) == INVALID_FILE_ATTRIBUTES || GetFileAttributesA(szDriverPath.c_str()) == ERROR_FILE_NOT_FOUND)
	{
		DBG::Print(LogType::Err, "The file does not exist, please try again!");
		std::getline(std::cin, szDriverPath);
		std::this_thread::sleep_for(milliseconds(100));
	}

	Drv = std::make_unique<Driver>();

	Status = Drv->Init();
	if (!NT_SUCCESS(Status))
	{
		DBG::PrintObjHex(LogType::Err, "InitController", Status);
		std::cin.get();
		return EXIT_FAILURE;
	}

	Status = PAT::Main();
	if (!NT_SUCCESS(Status))
	{
		DBG::Print(LogType::Err, "Getting all signatures failed!");
		Status = Drv->ShutDown();
		if (!NT_SUCCESS(Status))
			DBG::PrintObjHex(LogType::Err, "ShutDownController", Status);

		std::cin.get();

		return EXIT_FAILURE;
	}

	Status = Drv->ShutDown();
	if (!NT_SUCCESS(Status))
	{
		DBG::PrintObjHex(LogType::Err, "ShutDownController", Status);
		return EXIT_FAILURE;
	}
	
	std::cin.get();

	return EXIT_SUCCESS;
}
