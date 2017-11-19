// TestApiSet.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



int main()
{
	_TEB* teb = NtCurrentTeb();
	printf("TEB:%p\n", teb);
	PMY_PEB peb = (PMY_PEB)*(ULONG_PTR*)((ULONG_PTR)teb + PEB_OFFSET);
	printf("PEB:%p\n", peb);
	printf("API SETMAP:%p\n", (PVOID)peb->ApiSetMap);

#ifdef  WIN7
	PAPI_SET_NAMESPACE ApiSetMap = (PAPI_SET_NAMESPACE)peb->ApiSetMap;
	ULONG_PTR ApiSetMapAddress = (ULONG_PTR)ApiSetMap;

	UNICODE_STRING nameString;
	UNICODE_STRING dataString;
	printf("Count:%d\n", ApiSetMap->Count);
	Sleep(1000);
	for (auto i = 0u; i < ApiSetMap->Count; i++)
	{
		API_SET_VALUE_ENTRY Entry = ApiSetMap->Array[i];

		nameString.MaximumLength = static_cast<USHORT>(Entry.NameLength - 2);
		nameString.Length = static_cast<USHORT>(Entry.NameLength - 2);
		nameString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + Entry.NameOffset);

		PAPI_SET_UNKNOWN_ENTRY unEntry = reinterpret_cast<PAPI_SET_UNKNOWN_ENTRY>(ApiSetMapAddress + Entry.DataOffset);
		dataString.Length = static_cast<USHORT>(unEntry->NameLength);
		dataString.MaximumLength = static_cast<USHORT>(unEntry->NameLength);
		dataString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + unEntry->ModuleNameOffset);

		printf("%wZ----->", &nameString);
		printf("%wZ\n", &dataString);
	}

#endif //  WIN7
#ifdef WIN8
    PAPI_SET_NAMESPACE ApiSetMap = (PAPI_SET_NAMESPACE)peb->ApiSetMap;
    ULONG_PTR ApiSetMapAddress = (ULONG_PTR)ApiSetMap;

    UNICODE_STRING nameString;
    UNICODE_STRING aliasString;
    UNICODE_STRING dataString;
    printf("Count:%d\n", ApiSetMap->Count);
    for (auto i = 0u; i < ApiSetMap->Count; i++)
    {
        API_SET_VALUE_ENTRY Entry = ApiSetMap->Array[i];

        nameString.MaximumLength = static_cast<USHORT>(Entry.NameLength);
        nameString.Length = static_cast<USHORT>(Entry.NameLength);
        nameString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + Entry.NameOffset);

        aliasString.MaximumLength = static_cast<USHORT>(Entry.AliasLength);
        aliasString.Length = static_cast<USHORT>(Entry.AliasLength);
        aliasString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + Entry.AliasOffset);

        PAPI_SET_UNKNOWN_ENTRY unEntry = reinterpret_cast<PAPI_SET_UNKNOWN_ENTRY>(ApiSetMapAddress + Entry.DataOffset);
        dataString.Length = static_cast<USHORT>(unEntry->NameLength);
        dataString.MaximumLength = static_cast<USHORT>(unEntry->NameLength);
        dataString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + unEntry->ModuleNameOffset);

        printf("%wZ(%wZ)----->%wZ\n", &nameString,&aliasString,&dataString);
    }
#endif

#ifdef WIN10
    PAPI_SET_NAMESPACE ApiSetMap = (PAPI_SET_NAMESPACE)peb->ApiSetMap;
    ULONG_PTR ApiSetMapAddress = (ULONG_PTR)ApiSetMap;
    PAPI_SET_NAMESPACE_ENTRY nsEntry = (PAPI_SET_NAMESPACE_ENTRY)((ULONG_PTR)ApiSetMap->EntryOffset + ApiSetMapAddress);

    UNICODE_STRING nameString;
	UNICODE_STRING valueString;
	UNICODE_STRING aliasString;
    printf("Count:%d\n", ApiSetMap->Count);
	Sleep(1000);
    for (auto i = 0u; i < ApiSetMap->Count; i++)
    {
        nameString.MaximumLength = static_cast<USHORT>(nsEntry->NameLength);
        nameString.Length = static_cast<USHORT>(nsEntry->NameLength);
        nameString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + nsEntry->NameOffset);
        printf("%56wZ.dll -> {", &nameString);

        auto valueEntry = reinterpret_cast<PAPI_SET_VALUE_ENTRY>(ApiSetMapAddress + nsEntry->ValueOffset);
        for (auto j = 0u; j < nsEntry->ValueCount; j++)
        {
            valueString.Buffer = (PWCHAR)((ULONG_PTR)ApiSetMapAddress + valueEntry->ValueOffset);
            valueString.Length = (USHORT)valueEntry->ValueLength;
            valueString.MaximumLength = (USHORT)valueEntry->ValueLength;

            printf("%wZ", &valueString);

            if (nsEntry->ValueCount > 1)
            {
                printf(" ");
            }

            if (valueEntry->NameLength != 0)
            {
                //
                // Build a UNICODE_STRING for it
                //
				aliasString.MaximumLength = static_cast<USHORT>(valueEntry->NameLength);
				aliasString.Length = static_cast<USHORT>(valueEntry->NameLength);
				aliasString.Buffer = reinterpret_cast<PWCHAR>(ApiSetMapAddress + valueEntry->NameOffset);
                printf(" [%wZ]", &aliasString);
            }
            valueEntry++;
        }
        printf("}\n");
		Sleep(1000);
        nsEntry++;
    }
#endif
    Sleep(INFINITE);
    return 0;
}

