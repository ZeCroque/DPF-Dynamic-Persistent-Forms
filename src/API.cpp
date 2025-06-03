#include "DPF/API.h"

#include "FormCreator.h"
#include "DPF/FileSystem.h"
#include "FormRecordSerializer.h"

namespace DPF
{
	std::string coSaveExtension = "dpf";

	bool Init(RE::FormID inFormId, const std::string& inPluginName, const std::string& inCoSaveExtension)
	{
	    firstFormId = lastFormId = ReadFirstFormIdFromESP(inFormId, inPluginName);
		coSaveExtension = inCoSaveExtension;

		return firstFormId != 0xFF >> 24;
	}

	std::unique_ptr<FileWriter> fileWriter;
	FileWriter* SaveCache(const SKSE::MessagingInterface::Message* inMessage, bool inKeepFileOpen) {
		std::string name = static_cast<char*>(inMessage->data);
		name = name.append("." + coSaveExtension);

	    fileWriter.reset(new FileWriter(name, std::ios::out | std::ios::binary | std::ios::trunc));
	    if (!fileWriter->IsOpen()) {
	        return nullptr;
	    }

	    StoreAllFormRecords(fileWriter.get());

		if(!inKeepFileOpen)
		{
			fileWriter.release();
		}

		return fileWriter.get();
	}

	std::unique_ptr<FileReader> fileReader;
	FileReader* LoadCache(const SKSE::MessagingInterface::Message* inMessage) {
		formData.clear();

		std::string name = static_cast<char*>(inMessage->data);
		name = name.substr(0, name.size() - 3).append(coSaveExtension);
		fileReader.reset(new FileReader(name, std::ios::in | std::ios::binary));

	    if (!fileReader->IsOpen()) {
	        return nullptr;
	    }
	    RestoreAllFormRecords(fileReader.get());

	    UpdateId();
		return fileReader.get();
	}

	void DeleteCache(const SKSE::MessagingInterface::Message* inMessage) {
		std::string name = static_cast<char*>(inMessage->data);
		name = name.append("." + coSaveExtension);
	    Delete(name);
	}

	RE::TESForm* CreateForm(RE::TESForm* inModelForm)
	{
		return AddForm(inModelForm);
	}

	RE::TESForm* GetForm(RE::FormID inFormId)
	{
		return GetDynamicForm(inFormId);
	}
}
