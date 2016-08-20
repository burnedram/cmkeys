#include "stdafx.h"
#include "fullrandom.h"

using namespace std;

namespace effects {

	FullRandomEffect::FullRandomEffect() :
			Effect(L"FullRandomEffect")
	{
		if (!SetAllLedColor(mColorMatrix))
			Log(L"Unable to set background");
		if (!RefreshLed(true))
			Log(L"Unable to enable auto refresh");
	}

	static bool fillWithRandom(void *pBuffer, size_t bufferSize) {
		HCRYPTPROV hProv;
		if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
			DWORD error = GetLastError();
			if (error == NTE_BAD_KEYSET) {
				if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_NEWKEYSET)) {
					wcout << "Unable to acquire cryptographic context" << endl;
					return false;
				}
			} else {
				wcout << "Unknown error " << error << " while acquiring cryptographic context" << endl;
				LPTSTR errorText = nullptr;
				FormatMessage(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					error,
					MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
					(LPTSTR)&errorText,
					0,
					NULL);
				wcout << errorText << endl;
				LocalFree(errorText);
				return false;
			}
		}
		bool ok = CryptGenRandom(hProv, static_cast<DWORD>(bufferSize), static_cast<BYTE *>(pBuffer)) == TRUE; // BOOL to bool
		CryptReleaseContext(hProv, 0);
		return ok;
	}

	void FullRandomEffect::KeyEvent(int iRow, int iColumn, bool isPressed) {
		fillWithRandom(&mColorMatrix, sizeof(COLOR_MATRIX));
		SetAllLedColor(mColorMatrix);
	}

}