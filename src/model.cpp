#include "Model.h"

#include "FormRecord.h"
#include "DPF/FileSystem.h"

namespace DPF
{
	uint32_t lastFormId = 0;  // last mod
	uint32_t firstFormId = 0;  // last mod

	std::map<RE::FormID, FormRecord> formData;

	RE::TESForm* GetDynamicForm(RE::FormID inFormId)
	{
		RE::TESForm* result = nullptr;
		const auto dynamicFormId = (dynamicModId << 24) | (0xFFFFFF & inFormId);
		if(const auto it = formData.find(dynamicFormId); it != formData.end())
		{
			result = it->second.actualForm;
		}
		return result;
	}

	void UpdateId() {
		lastFormId = firstFormId - 1;
		std::ranges::for_each((formData | std::views::values), [&](const FormRecord& item) {
			if (item.formId > lastFormId) {

				lastFormId = item.formId;
			}
		});
		++lastFormId; 
	}
}