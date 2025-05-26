#include "DPF/API.h"

#include "FormCreator.h"
#include "FileSystem.h"
#include "FormRecordSerializer.h"

namespace DPF
{
	std::string coSaveExtension = "dpf";

	void Init(RE::FormID inFormId, const std::string& inPluginName, const std::string& inCoSaveExtension)
	{
	    firstFormId = lastFormId = ReadFirstFormIdFromESP(inFormId, inPluginName);
		coSaveExtension = inCoSaveExtension;
	}

	void SaveCache(const SKSE::MessagingInterface::Message* inMessage) {
		std::string name = static_cast<char*>(inMessage->data);
		name = name.append("." + coSaveExtension);
	    FileWriter fileWriter(name, std::ios::out | std::ios::binary | std::ios::trunc);

	    if (!fileWriter.IsOpen()) {
	        return;
	    }

	    StoreAllFormRecords(&fileWriter);
	}

	void LoadCache(const SKSE::MessagingInterface::Message* inMessage) {
		std::string name = static_cast<char*>(inMessage->data);
		name = name.substr(0, name.size() - 3).append("." + coSaveExtension);
		FileReader fileReader(name, std::ios::in | std::ios::binary);

	    if (!fileReader.IsOpen()) {
	        return;
	    }
	    RestoreAllFormRecords(&fileReader);

	    UpdateId();
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
}