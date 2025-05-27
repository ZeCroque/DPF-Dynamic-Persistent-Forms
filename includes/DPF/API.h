#pragma once

#include "FileSystem.h"

namespace DPF
{
	void Init(RE::FormID inFormId, const std::string& inPluginName, const std::string& inCoSaveExtension);

	FileWriter* SaveCache(const SKSE::MessagingInterface::Message* inMessage, bool inKeepFileOpen = false);

	FileReader* LoadCache(const SKSE::MessagingInterface::Message* inMessage);

	void DeleteCache(const SKSE::MessagingInterface::Message* inMessage);

	RE::TESForm* CreateForm(RE::TESForm* inModelForm);

	RE::TESForm* GetForm(RE::FormID inFormId);

	extern std::unique_ptr<FileWriter> fileWriter;

	template <typename T> T* CreateForm(T* inModelForm)
	{
		return CreateForm(static_cast<RE::TESForm*>(inModelForm))->As<T>();
	}

	template <typename T> T* GetForm(RE::FormID inFormId)
	{
		return GetForm(inFormId)->As<T>();
	}
}